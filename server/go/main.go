// 인삼남 게임 서버.
//
// 하는 일은 하나다. 덤프 텍스트를 받아 표에 넣고, 표에서 덤프 텍스트를 만들어
// 돌려준다. 새 규격을 만들지 않는다 — 파서가 이미 클라이언트와 tools/ 양쪽에
// 있고, 그 형식이 곧 LOAD DATA INFILE 이기 때문이다.
//
// 엔드포인트는 셋이다. 클라이언트의 요청 종류가 NETREQ_LOGIN / LOAD / SAVE
// 셋뿐이라 그렇다.
//
//	POST /v1/login   guest_key 한 줄  ->  메타행 덤프
//	GET  /v1/save    (헤더로 인증)    ->  덤프 전문
//	POST /v1/save    덤프 전문        ->  아직 없다 (다음 작업)
package main

import (
	"context"
	"database/sql"
	"errors"
	"flag"
	"io"
	"log"
	"net/http"
	"os"
	"os/signal"
	"regexp"
	"strings"
	"syscall"
	"time"

	_ "github.com/go-sql-driver/mysql"
)

// 저장 본문의 상한. 유저 한 명분이 수 KB 라 넉넉하게 잡아도 이 정도면 된다.
// 이 값을 넘기 시작하면 부분 갱신을 고민할 때라는 신호이기도 하다.
const maxBodyBytes = 4 << 20 // 4MB

// guest_key 는 UUID 다. account.guest_key 가 CHAR(36) 이라 길이도 여기서 막는다.
var guestKeyRe = regexp.MustCompile(`^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}$`)

type server struct {
	store *Store
}

func main() {
	addr := flag.String("addr", "127.0.0.1:8080", "들을 주소")
	dsn := flag.String("dsn", os.Getenv("INSAM_DSN"), "MariaDB DSN (또는 INSAM_DSN 환경변수)")
	dbName := flag.String("db", "insam", "스키마를 읽을 DB 이름")
	purge := flag.Bool("purge", false,
		"때가 된 탈퇴 예약을 실제로 지우고 끝낸다. 타이머가 부른다")
	epoch := flag.Int64("epoch", GameEpoch,
		"게임 타임스탬프 기준점의 unix 초. 클라이언트와 같아야 한다 (dump.go 주석 참고)")
	flag.Parse()

	GameEpoch = *epoch

	// 세션 토큰 서명에 쓰는 비밀. 바뀌면 돌아다니던 토큰이 전부 무효가 되고
	// 클라이언트는 401 을 받아 다시 로그인한다. 죽지는 않지만 다들 한 번씩
	// 다시 붙으므로, 한 번 넣고 안 바꾸는 것이 낫다.
	tokenKey = []byte(os.Getenv("INSAM_TOKEN_KEY"))

	if len(tokenKey) < 32 {
		log.Fatal("INSAM_TOKEN_KEY 가 없거나 너무 짧다 (32글자 이상)")
	}

	// 구글·애플 연동. 우리 앱의 클라이언트 ID 를 넣어야 켜진다.
	// 안 넣으면 그 연동은 501 로 답한다 — aud 를 확인하지 못하면 남의 앱
	// 토큰으로 들어올 수 있어서, 모르는 채로 받아주느니 막는 편이 낫다.
	//
	// 신분증(JWT)을 주는 곳은 클라이언트 ID 만 있으면 된다.
	SetAudiences(ProviderGoogle, os.Getenv("INSAM_GOOGLE_AUD"))
	SetAudiences(ProviderApple, os.Getenv("INSAM_APPLE_AUD"))
	SetAudiences(ProviderKakao, os.Getenv("INSAM_KAKAO_AUD"))
	SetAudiences(ProviderLine, os.Getenv("INSAM_LINE_AUD"))

	// 물어봐야 하는 곳은 앱 비밀도 있어야 한다. 우리 자격으로 물어야
	// "우리 앱에 준 토큰인가" 를 확인할 수 있기 때문이다.
	SetAPIClient(ProviderFacebook,
		os.Getenv("INSAM_FACEBOOK_ID"), os.Getenv("INSAM_FACEBOOK_SECRET"))
	SetAPIClient(ProviderNaver,
		os.Getenv("INSAM_NAVER_ID"), os.Getenv("INSAM_NAVER_SECRET"))

	for _, p := range []Provider{ProviderGoogle, ProviderApple, ProviderKakao,
		ProviderLine, ProviderFacebook, ProviderNaver} {
		log.Printf("연동 %-9s %v", p.Name(), ProviderEnabled(p))
	}

	if *dsn == "" {
		log.Fatal("DSN 이 없다. -dsn 이나 INSAM_DSN 을 준다")
	}

	db, err := sql.Open("mysql", *dsn)

	if err != nil {
		log.Fatalf("DB 를 못 열었다: %v", err)
	}

	defer db.Close()

	// 914Mi 짜리 기계다. 연결을 많이 벌려둘 이유가 없다.
	db.SetMaxOpenConns(16)
	db.SetMaxIdleConns(4)
	db.SetConnMaxLifetime(time.Hour)

	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	if err := db.PingContext(ctx); err != nil {
		log.Fatalf("DB 에 못 붙었다: %v", err)
	}

	st := NewStore(db)

	if err := st.LoadSchema(ctx, *dbName); err != nil {
		log.Fatalf("스키마를 못 읽었다: %v", err)
	}

	log.Printf("스키마 %d, 표 %d개를 읽었다", st.Schema().Version, len(st.Schema().Tables))

	// 탈퇴 예약을 치우는 일. 서버로 안 뜨고 한 번 돌고 끝난다.
	//
	// 같은 프로그램 안에 두는 이유는, 지우는 규칙이 SQL 한 줄이라도 그
	// 규칙이 코드와 따로 떨어지면 어긋나기 때문이다.
	if *purge {
		n, err := st.PurgeDeleted(ctx)

		if err != nil {
			log.Fatalf("탈퇴 처리 실패: %v", err)
		}

		log.Printf("탈퇴 예약 %d개를 지웠다", n)
		return
	}

	s := &server{store: st}
	mux := http.NewServeMux()

	mux.HandleFunc("/healthz", s.handleHealth)
	mux.HandleFunc("/v1/login", s.handleLogin)
	mux.HandleFunc("/v1/save", s.handleSave)
	mux.HandleFunc("/v1/link", s.handleLink)
	mux.HandleFunc("/v1/consent", s.handleConsent)
	mux.HandleFunc("/v1/account", s.handleAccount)

	srv := &http.Server{
		Addr:              *addr,
		Handler:           logging(mux),
		ReadHeaderTimeout: 5 * time.Second,
		ReadTimeout:       30 * time.Second,
		WriteTimeout:      30 * time.Second,
		IdleTimeout:       60 * time.Second,
	}

	// TLS 는 앞의 nginx 가 끊는다. 여기는 평문 HTTP 로 로컬만 듣는다.
	go func() {
		log.Printf("듣는다: %s", *addr)

		if err := srv.ListenAndServe(); err != nil && err != http.ErrServerClosed {
			log.Fatalf("못 들었다: %v", err)
		}
	}()

	stop := make(chan os.Signal, 1)
	signal.Notify(stop, os.Interrupt, syscall.SIGTERM)
	<-stop

	log.Print("내려간다")

	down, downCancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer downCancel()

	_ = srv.Shutdown(down)
}

// -----------------------------------------------------------------------------
// 길목
// -----------------------------------------------------------------------------

func (s *server) handleHealth(w http.ResponseWriter, r *http.Request) {
	writeText(w, http.StatusOK, "ok\n")
}

// POST /v1/login — 본문은 guest_key 한 줄이다.
//
// 답은 메타행만 있는 덤프다. 표가 없을 뿐 형식은 같으므로 클라이언트가 같은
// 파서로 읽는다.
func (s *server) handleLogin(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		writeText(w, http.StatusMethodNotAllowed, "POST 만 받는다\n")
		return
	}

	body, err := io.ReadAll(http.MaxBytesReader(w, r.Body, 1024))

	if err != nil {
		writeText(w, http.StatusBadRequest, "본문을 못 읽었다\n")
		return
	}

	kind, cred := splitCred(string(body))

	// 구글·애플로 왔다. 붙어 있는 계정을 찾아 돌려준다.
	if kind != ProviderGuest {
		s.loginByProvider(w, r, kind, cred)
		return
	}

	key := cred

	if !guestKeyRe.MatchString(key) {
		// 열쇠를 서버가 지어내지 않는다. 그것을 만들고 보관하는 것은
		// 클라이언트의 일이고 (첫 실행에 UUID 하나), 서버가 지어내면
		// 그 값을 돌려줄 자리가 메타행에 없다.
		writeText(w, http.StatusBadRequest, "guest_key 가 UUID 꼴이 아니다\n")
		return
	}

	userID, revision, err := s.store.Login(r.Context(), key)

	if errors.Is(err, ErrBanned) {
		writeText(w, http.StatusForbidden, "차단된 계정이다\n")
		return
	}

	if err != nil {
		log.Printf("login: %v", err)
		writeText(w, http.StatusInternalServerError, "서버가 잘못됐다\n")
		return
	}

	writeText(w, http.StatusOK, s.loginMeta(r.Context(), userID, revision))
}

// loginMeta 는 로그인 답을 만든다.
//
// 토큰 말고도 클라이언트가 곧바로 알아야 하는 것이 둘 있다.
//
//	#terms_ok   이 유저가 동의한 약관 판. 지금 판보다 낮으면 다시 받아야 한다
//	#delete_at  탈퇴 예약이 걸려 있으면 그 시각. 취소할 기회를 줘야 한다
func (s *server) loginMeta(ctx context.Context, userID, revision int64) string {
	tok, exp := MakeToken(userID, time.Now())

	d := &Dump{
		Schema:   s.store.Schema().Version,
		User:     userID,
		Revision: revision,
		Now:      gameNow(),
		Token:    tok,
		TokenExp: exp,
	}

	if v, err := s.store.AgreedTerms(ctx, userID); err == nil {
		d.TermsOK = v
	}

	if t, err := s.store.PendingDelete(ctx, userID); err == nil && !t.IsZero() {
		d.DeleteAt = t.Unix() - GameEpoch
	}

	return d.BuildMeta()
}

// POST /v1/consent — 받은 동의를 남긴다.
//
// 동의 자체는 계정이 생기기 전에 받는다. 여기는 그것을 증빙으로 남기는
// 자리라 로그인 뒤에 온다. 자세한 순서는 consent.go 머리주석에 있다.
func (s *server) handleConsent(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		writeText(w, http.StatusMethodNotAllowed, "POST 만 받는다\n")
		return
	}

	userID, ok := s.auth(w, r)

	if !ok {
		return
	}

	body, err := io.ReadAll(http.MaxBytesReader(w, r.Body, 4096))

	if err != nil {
		writeText(w, http.StatusBadRequest, "본문을 못 읽었다\n")
		return
	}

	m := readMetaRows(string(body))
	c := Consent{
		Terms:          metaInt(m, "terms"),
		AgeOK:          metaBool(m, "age_ok"),
		Marketing:      metaBool(m, "marketing"),
		MarketingNight: metaBool(m, "marketing_night"),
	}

	if c.Terms <= 0 {
		writeText(w, http.StatusBadRequest, "#terms 가 없다\n")
		return
	}

	// 만 14세 미만은 법정대리인 동의가 따로 필요하다. 그 흐름을 만들기
	// 전까지는 받지 않는다. 조용히 통과시키면 나중에 되돌릴 수 없다.
	if !c.AgeOK {
		writeText(w, http.StatusForbidden, "만 14세 이상 확인이 필요하다\n")
		return
	}

	if err := s.store.SaveConsent(r.Context(), userID, c); err != nil {
		log.Printf("consent: user=%d %v", userID, err)
		writeText(w, http.StatusInternalServerError, "서버가 잘못됐다\n")
		return
	}

	log.Printf("consent: user=%d 약관 %d 동의 (마케팅 %d/%d)",
		userID, c.Terms, boolToInt(c.Marketing), boolToInt(c.MarketingNight))

	d := &Dump{
		Schema:  s.store.Schema().Version,
		User:    userID,
		Now:     gameNow(),
		TermsOK: c.Terms,
	}

	writeText(w, http.StatusOK, d.BuildMeta())
}

// /v1/account — 탈퇴 예약과 취소.
//
//	DELETE  예약한다. 며칠 뒤에 실제로 지운다
//	POST    예약을 무른다
func (s *server) handleAccount(w http.ResponseWriter, r *http.Request) {
	userID, ok := s.auth(w, r)

	if !ok {
		return
	}

	switch r.Method {
	case http.MethodDelete:
		when, err := s.store.RequestDelete(r.Context(), userID)

		if err != nil {
			log.Printf("account: user=%d %v", userID, err)
			writeText(w, http.StatusInternalServerError, "서버가 잘못됐다\n")
			return
		}

		log.Printf("account: user=%d 탈퇴 예약 (%s)", userID, when.Format("2006-01-02 15:04"))

		d := &Dump{
			Schema:   s.store.Schema().Version,
			User:     userID,
			Now:      gameNow(),
			DeleteAt: when.Unix() - GameEpoch,
		}

		writeText(w, http.StatusOK, d.BuildMeta())

	case http.MethodPost:
		if err := s.store.CancelDelete(r.Context(), userID); err != nil {
			log.Printf("account: user=%d %v", userID, err)
			writeText(w, http.StatusInternalServerError, "서버가 잘못됐다\n")
			return
		}

		log.Printf("account: user=%d 탈퇴 예약을 물렀다", userID)

		d := &Dump{
			Schema: s.store.Schema().Version,
			User:   userID,
			Now:    gameNow(),
		}

		writeText(w, http.StatusOK, d.BuildMeta())

	default:
		writeText(w, http.StatusMethodNotAllowed, "DELETE 나 POST 만 받는다\n")
	}
}

// GET  /v1/save — 덤프 전문을 내려준다.
// POST /v1/save — 아직 없다.
func (s *server) handleSave(w http.ResponseWriter, r *http.Request) {
	switch r.Method {
	case http.MethodGet:
		s.getSave(w, r)

	case http.MethodPost:
		s.postSave(w, r)

	default:
		writeText(w, http.StatusMethodNotAllowed, "GET 이나 POST 만 받는다\n")
	}
}

func (s *server) getSave(w http.ResponseWriter, r *http.Request) {
	userID, ok := s.auth(w, r)

	if !ok {
		return
	}

	d, err := s.store.LoadDump(r.Context(), userID)

	if errors.Is(err, ErrNoSave) {
		// 계정은 있는데 세이브가 없다. 클라이언트는 새 게임을 시작한다.
		writeText(w, http.StatusNotFound, "세이브가 없다\n")
		return
	}

	if err != nil {
		log.Printf("load: user=%d %v", userID, err)
		writeText(w, http.StatusInternalServerError, "서버가 잘못됐다\n")
		return
	}

	d.Now = gameNow()

	writeText(w, http.StatusOK, d.Build())
}

// POST /v1/save — 덤프 전문을 받아 그 유저의 행을 갈아끼운다.
//
// 거절(409)에 서버가 들고 있는 덤프를 같이 실어 보낸다. 그러면 클라이언트가
// 따로 다시 받는 왕복이 사라지고, "거절당한 순간의 서버 상태" 와 "다시 받은
// 상태" 가 어긋날 여지도 없어진다.
func (s *server) postSave(w http.ResponseWriter, r *http.Request) {
	userID, ok := s.auth(w, r)

	if !ok {
		return
	}

	body, err := io.ReadAll(http.MaxBytesReader(w, r.Body, maxBodyBytes))

	if err != nil {
		writeText(w, http.StatusBadRequest, "본문을 못 읽었다\n")
		return
	}

	d, err := ParseDump(string(body))

	if err != nil {
		// 체크섬·행수·컬럼명이 규격에 안 맞는다. 잘린 요청이거나 클라이언트
		// 버전과 스키마가 어긋나기 시작한 신호다.
		log.Printf("save: user=%d 규격 위반 %v", userID, err)
		writeText(w, http.StatusBadRequest, err.Error()+"\n")
		return
	}

	if d.Schema != s.store.Schema().Version {
		// 컬럼은 더하기만 하고 빼지 않는 것이 규칙이라, 버전이 달라도
		// 넣을 수는 있다. 다만 남겨둔다.
		log.Printf("save: user=%d 스키마가 %d 인데 서버는 %d 다",
			userID, d.Schema, s.store.Schema().Version)
	}

	newRev, serverRev, err := s.store.SaveDump(r.Context(), userID, d)

	switch {
	case errors.Is(err, ErrConflict):
		s.store.LogConflict(r.Context(), userID, d.Revision, serverRev,
			r.Header.Get("User-Agent"))

		cur, lerr := s.store.LoadDump(r.Context(), userID)

		if lerr != nil {
			log.Printf("save: 충돌인데 현재 덤프를 못 만들었다: %v", lerr)
			writeText(w, http.StatusConflict, "다른 기기가 먼저 저장했다\n")
			return
		}

		cur.Now = gameNow()

		writeText(w, http.StatusConflict, cur.Build())
		return

	case errors.Is(err, ErrNotYours):
		writeText(w, http.StatusForbidden, "자기 것이 아닌 세이브다\n")
		return

	case err != nil:
		var de *DumpError

		if errors.As(err, &de) {
			log.Printf("save: user=%d 규격 위반 %v", userID, err)
			writeText(w, http.StatusBadRequest, err.Error()+"\n")
			return
		}

		log.Printf("save: user=%d %v", userID, err)
		writeText(w, http.StatusInternalServerError, "서버가 잘못됐다\n")
		return
	}

	out := &Dump{
		Schema:   s.store.Schema().Version,
		User:     userID,
		Revision: newRev,
		Now:      gameNow(),
	}

	writeText(w, http.StatusOK, out.BuildMeta())
}

// auth 는 헤더의 guest_key 로 유저를 찾는다.
//
// 1단계는 이 열쇠를 그대로 보낸다. 3단계에서 세션 토큰으로 바뀌고, 그때
// 클라이언트에 NETRESULT_ERR_AUTH 도 같이 생긴다. 지금은 401 이 클라이언트
// 쪽에서 ERR_NETWORK 로 뭉개져 "못 붙었다" 로 보인다.
func (s *server) auth(w http.ResponseWriter, r *http.Request) (int64, bool) {
	// 토큰이 정식 길이다. 로그인 답에 실려 온 것을 그대로 보내면 된다.
	if tok := bearer(r); tok != "" {
		userID, _, err := ReadToken(tok, time.Now())

		if err != nil {
			writeText(w, http.StatusUnauthorized, "토큰이 만료됐거나 아니다\n")
			return 0, false
		}

		return userID, true
	}

	// 게스트 열쇠도 아직 받는다. 옛 클라이언트가 남아 있을 수 있어서다.
	// 다들 토큰으로 넘어가면 이 갈래를 없앤다 — 열쇠는 로그인 때만 쓰는
	// 것이 맞고, 매 요청에 실어 보낼 물건이 아니다.
	key := strings.TrimSpace(r.Header.Get("X-Guest-Key"))

	if !guestKeyRe.MatchString(key) {
		writeText(w, http.StatusUnauthorized, "자격증명이 없다\n")
		return 0, false
	}

	log.Printf("auth: 아직 guest_key 로 온다 (%s)", r.URL.Path)

	userID, _, err := s.store.Login(r.Context(), key)

	if errors.Is(err, ErrBanned) {
		writeText(w, http.StatusForbidden, "차단된 계정이다\n")
		return 0, false
	}

	if err != nil {
		log.Printf("auth: %v", err)
		writeText(w, http.StatusInternalServerError, "서버가 잘못됐다\n")
		return 0, false
	}

	return userID, true
}

// -----------------------------------------------------------------------------
// 거들이
// -----------------------------------------------------------------------------

// splitCred 는 로그인 본문을 발급처와 자격증명으로 가른다.
//
//	<발급처>\t<자격증명>   google / apple / guest
//	<uuid>                 발급처를 안 적으면 게스트로 본다 (옛 클라이언트)
func splitCred(body string) (Provider, string) {
	body = strings.TrimSpace(body)
	at := strings.IndexAny(body, "\t ")

	if at < 0 {
		return ProviderGuest, body
	}

	cred := strings.TrimSpace(body[at+1:])

	if p, ok := ProviderByName(body[:at]); ok {
		return p, cred
	}

	// 모르는 이름이면 통째로 게스트 열쇠로 본다. 옛 클라이언트가 UUID 만
	// 보내던 것과 같은 취급이다.
	return ProviderGuest, body
}

// loginByProvider 는 구글·애플로 로그인한다.
//
// 계정을 만들지 않는다. 계정은 언제나 게스트로 먼저 생기고, 여기는 이미
// 붙어 있는 것을 찾아 돌려줄 뿐이다. 없으면 404 — 클라이언트는 "연동된
// 계정이 없습니다" 를 띄우고 게스트로 계속하면 된다.
func (s *server) loginByProvider(w http.ResponseWriter, r *http.Request,
	p Provider, idToken string) {

	if !Enabled(p) {
		writeText(w, http.StatusNotImplemented, "이 연동은 아직 안 켰다\n")
		return
	}

	uid, err := VerifyCredential(r.Context(), p, idToken, time.Now())

	if err != nil {
		log.Printf("login: %s 신분증을 못 믿겠다 (%v)", p.Name(), err)
		writeText(w, http.StatusUnauthorized, "신분증이 아니다\n")
		return
	}

	userID, err := s.store.FindLinked(r.Context(), p, uid)

	switch {
	case errors.Is(err, ErrNoLink):
		writeText(w, http.StatusNotFound, "연동된 계정이 없다\n")
		return

	case errors.Is(err, ErrBanned):
		writeText(w, http.StatusForbidden, "차단된 계정이다\n")
		return

	case err != nil:
		log.Printf("login: %v", err)
		writeText(w, http.StatusInternalServerError, "서버가 잘못됐다\n")
		return
	}

	var revision int64

	_ = s.store.db.QueryRowContext(r.Context(),
		`SELECT revision FROM player WHERE user_id = ?`, userID).Scan(&revision)

	writeText(w, http.StatusOK, s.loginMeta(r.Context(), userID, revision))
}

// POST /v1/link — 지금 로그인한 계정에 구글·애플을 붙인다.
//
// 합치지 않는다. 그 구글이 이미 다른 계정에 붙어 있으면 409 다. 두 세이브를
// 어떻게 합칠지는 코드가 아니라 게임이 정할 일이다.
func (s *server) handleLink(w http.ResponseWriter, r *http.Request) {
	if r.Method != http.MethodPost {
		writeText(w, http.StatusMethodNotAllowed, "POST 만 받는다\n")
		return
	}

	userID, ok := s.auth(w, r)

	if !ok {
		return
	}

	body, err := io.ReadAll(http.MaxBytesReader(w, r.Body, 8192))

	if err != nil {
		writeText(w, http.StatusBadRequest, "본문을 못 읽었다\n")
		return
	}

	p, idToken := splitCred(string(body))

	if p == ProviderGuest {
		writeText(w, http.StatusBadRequest, "어느 쪽인지 적어야 한다 (google/apple)\n")
		return
	}

	if !Enabled(p) {
		writeText(w, http.StatusNotImplemented, "이 연동은 아직 안 켰다\n")
		return
	}

	uid, err := VerifyIDToken(p, idToken, time.Now())

	if err != nil {
		log.Printf("link: %s 신분증을 못 믿겠다 (%v)", p.Name(), err)
		writeText(w, http.StatusUnauthorized, "신분증이 아니다\n")
		return
	}

	err = s.store.Link(r.Context(), userID, p, uid)

	switch {
	case errors.Is(err, ErrLinkTaken):
		writeText(w, http.StatusConflict, "이미 다른 계정에 붙어 있다\n")
		return

	case err != nil:
		log.Printf("link: user=%d %v", userID, err)
		writeText(w, http.StatusInternalServerError, "서버가 잘못됐다\n")
		return
	}

	log.Printf("link: user=%d 에 %d 를 붙였다", userID, int(p))

	d := &Dump{
		Schema: s.store.Schema().Version,
		User:   userID,
		Now:    gameNow(),
	}

	writeText(w, http.StatusOK, d.BuildMeta())
}

// bearer 는 Authorization 헤더에서 토큰을 꺼낸다.
func bearer(r *http.Request) string {
	v := strings.TrimSpace(r.Header.Get("Authorization"))

	if len(v) > 7 && strings.EqualFold(v[:7], "Bearer ") {
		return strings.TrimSpace(v[7:])
	}

	return ""
}

// gameNow 는 게임 안 타임스탬프로 본 지금이다. 2000-01-01 부터의 초.
func gameNow() int64 {
	return time.Now().Unix() - GameEpoch
}

func writeText(w http.ResponseWriter, code int, body string) {
	w.Header().Set("Content-Type", "text/plain; charset=utf-8")
	w.WriteHeader(code)
	_, _ = io.WriteString(w, body)
}

// logging 은 한 줄씩 남긴다. 계획서가 보라고 한 지표들이 여기서 나온다 —
// 저장 본문 크기, 400 비율, 응답 시간.
func logging(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		started := time.Now()
		rec := &recorder{ResponseWriter: w, code: http.StatusOK}

		next.ServeHTTP(rec, r)

		log.Printf("%s %s %d 보냄=%dB 받음=%s %.1fms",
			r.Method, r.URL.Path, rec.code, rec.wrote, lengthOf(r),
			float64(time.Since(started).Microseconds())/1000)
	})
}

func lengthOf(r *http.Request) string {
	if r.ContentLength < 0 {
		return "?"
	}

	return itoa(r.ContentLength) + "B"
}

func itoa(v int64) string {
	if v == 0 {
		return "0"
	}

	var b [24]byte
	i := len(b)

	for v > 0 {
		i--
		b[i] = byte('0' + v%10)
		v /= 10
	}

	return string(b[i:])
}

type recorder struct {
	http.ResponseWriter
	code  int
	wrote int
}

func (r *recorder) WriteHeader(code int) {
	r.code = code
	r.ResponseWriter.WriteHeader(code)
}

func (r *recorder) Write(b []byte) (int, error) {
	n, err := r.ResponseWriter.Write(b)
	r.wrote += n
	return n, err
}
