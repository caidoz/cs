// 신분증(JWT)을 안 주는 발급처들.
//
// 이쪽은 불투명한 토큰이나 인가 코드를 준다. 우리가 서명을 확인할 수 없으니
// 그쪽에 물어봐야 하고, 그래서 로그인마다 왕복이 하나 붙는다. provider.go
// 머리주석에 왜 이렇게 갈리는지 적었다.
//
// 여기서 절대 빠뜨리면 안 되는 것은 "우리 앱에 발급된 토큰인가" 다.
// 그것을 확인할 방법이 없으면 그 발급처는 켜지 않는다.
package main

import (
	"context"
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"net/url"
	"strconv"
	"strings"
	"time"
)

// 그쪽 서버를 기다리는 시간. 로그인 한 번이 이보다 오래 걸리면 유저는
// 이미 떠났다.
const oauthTimeout = 8 * time.Second

// apiProvider 는 물어봐서 확인하는 발급처 하나다.
type apiProvider struct {
	name string

	// ---- 토큰을 그대로 받는 경우(kindIntrospect) ----
	//
	// checkURL 은 "이 토큰 누구 것이고 어느 앱에 줬나" 를 알려주는 곳이다.
	// %s 자리에 토큰이 들어간다. appPath 와 uidPath 는 그 답에서 값을 꺼낼
	// 자리다 ("data.app_id" 처럼 점으로 잇는다).
	checkURL string
	appPath  string
	uidPath  string
	bearer   bool // 토큰을 헤더로 보내는가

	// ---- 인가 코드를 받는 경우(kindCode) ----
	//
	// 코드를 우리 비밀로 토큰으로 바꾼 뒤, 그 토큰으로 사용자를 묻는다.
	// 우리 비밀로 바꾼 것이라 "우리 앱 것" 임이 정의상 보장된다.
	tokenURL string
	userURL  string

	// ---- 설정 ----
	clientID     string
	clientSecret string
}

var apiProviders = map[Provider]*apiProvider{
	// 페이스북은 debug_token 이 app_id 를 알려준다. 그래서 토큰을 그대로
	// 받아도 우리 앱 것인지 확인할 수 있다.
	ProviderFacebook: {
		name:     "facebook",
		checkURL: "https://graph.facebook.com/debug_token?input_token=%s&access_token=%s",
		appPath:  "data.app_id",
		uidPath:  "data.user_id",
	},

	// 네이버는 토큰만으로 "어느 앱 것인가" 를 알 방법이 없다. 그래서 코드를
	// 받아 우리 비밀로 바꾼다. 남의 앱 토큰을 들이미는 길을 아예 없앤다.
	ProviderNaver: {
		name:     "naver",
		tokenURL: "https://nid.naver.com/oauth2.0/token",
		userURL:  "https://openapi.naver.com/v1/nid/me",
		uidPath:  "response.id",
		bearer:   true,
	},
}

// SetAPIClient 는 발급처의 앱 정보를 넣는다. 없으면 그 발급처는 안 켜진다.
func SetAPIClient(p Provider, id, secret string) {
	ap := apiProviders[p]

	if ap == nil {
		return
	}

	ap.clientID = strings.TrimSpace(id)
	ap.clientSecret = strings.TrimSpace(secret)
}

// apiEnabled 는 물어보는 부류가 쓸 수 있는지 본다.
func apiEnabled(p Provider) bool {
	ap := apiProviders[p]

	if ap == nil {
		return false
	}

	// 코드를 바꾸는 쪽은 비밀이 있어야 한다. 물어보는 쪽도 앱 비밀이 있어야
	// debug_token 을 부를 수 있다.
	return ap.clientID != "" && ap.clientSecret != ""
}

// VerifyAPIToken 은 토큰이나 코드를 확인하고 그쪽 계정 번호를 준다.
func VerifyAPIToken(ctx context.Context, p Provider, cred string) (string, error) {
	ap := apiProviders[p]

	if ap == nil || !apiEnabled(p) {
		return "", fmt.Errorf("%s 는 아직 안 켰다", p.Name())
	}

	if p.Kind() == kindCode {
		return ap.byCode(ctx, cred)
	}

	return ap.byToken(ctx, cred)
}

// byToken 은 받은 토큰을 그대로 들고 물어본다.
func (ap *apiProvider) byToken(ctx context.Context, tok string) (string, error) {
	// 앱 토큰은 "<앱ID>|<앱비밀>" 꼴이다. 우리가 우리 자격으로 묻는 것이다.
	appTok := ap.clientID + "|" + ap.clientSecret
	u := fmt.Sprintf(ap.checkURL, url.QueryEscape(tok), url.QueryEscape(appTok))

	body, err := ap.get(ctx, u, "")

	if err != nil {
		return "", err
	}

	// 여기가 급소다. 우리 앱에 발급된 토큰이 아니면 남의 앱에서 받아온
	// 남의 토큰이다. 그대로 받으면 계정이 넘어간다.
	gotApp, _ := digString(body, ap.appPath)

	if gotApp == "" || gotApp != ap.clientID {
		return "", fmt.Errorf("%s: 우리 앱 토큰이 아니다", ap.name)
	}

	uid, ok := digString(body, ap.uidPath)

	if !ok || uid == "" {
		return "", fmt.Errorf("%s: 사용자 번호가 없다", ap.name)
	}

	return uid, nil
}

// byCode 는 인가 코드를 우리 비밀로 토큰으로 바꾼 뒤 사용자를 묻는다.
func (ap *apiProvider) byCode(ctx context.Context, code string) (string, error) {
	q := url.Values{}
	q.Set("grant_type", "authorization_code")
	q.Set("client_id", ap.clientID)
	q.Set("client_secret", ap.clientSecret)
	q.Set("code", code)

	body, err := ap.get(ctx, ap.tokenURL+"?"+q.Encode(), "")

	if err != nil {
		return "", err
	}

	tok, ok := digString(body, "access_token")

	if !ok || tok == "" {
		msg, _ := digString(body, "error_description")
		return "", fmt.Errorf("%s: 코드를 토큰으로 못 바꿨다 (%s)", ap.name, msg)
	}

	who, err := ap.get(ctx, ap.userURL, tok)

	if err != nil {
		return "", err
	}

	uid, ok := digString(who, ap.uidPath)

	if !ok || uid == "" {
		return "", fmt.Errorf("%s: 사용자 번호가 없다", ap.name)
	}

	return uid, nil
}

func (ap *apiProvider) get(ctx context.Context, u, bearerTok string) (map[string]any, error) {
	req, err := http.NewRequestWithContext(ctx, http.MethodGet, u, nil)

	if err != nil {
		return nil, err
	}

	if bearerTok != "" {
		req.Header.Set("Authorization", "Bearer "+bearerTok)
	}

	cli := &http.Client{Timeout: oauthTimeout}
	res, err := cli.Do(req)

	if err != nil {
		return nil, fmt.Errorf("%s 에 못 물어봤다: %w", ap.name, err)
	}

	defer res.Body.Close()

	raw, err := io.ReadAll(io.LimitReader(res.Body, 64<<10))

	if err != nil {
		return nil, err
	}

	var out map[string]any

	if err := json.Unmarshal(raw, &out); err != nil {
		return nil, fmt.Errorf("%s 가 이상한 답을 준다", ap.name)
	}

	if res.StatusCode != http.StatusOK {
		return nil, fmt.Errorf("%s HTTP %d", ap.name, res.StatusCode)
	}

	return out, nil
}

// digString 은 "data.app_id" 처럼 점으로 이은 자리에서 값을 꺼낸다.
//
// 숫자로 오는 곳이 있어서(네이버·페이스북이 섞여 있다) 숫자도 글자로 바꿔 준다.
func digString(m map[string]any, path string) (string, bool) {
	if path == "" {
		return "", false
	}

	var cur any = m

	for _, key := range strings.Split(path, ".") {
		obj, ok := cur.(map[string]any)

		if !ok {
			return "", false
		}

		cur, ok = obj[key]

		if !ok {
			return "", false
		}
	}

	switch v := cur.(type) {
	case string:
		return v, true
	case float64:
		return strconv.FormatInt(int64(v), 10), true
	case json.Number:
		return v.String(), true
	}

	return "", false
}
