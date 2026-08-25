// 약관 동의와 탈퇴.
//
// 둘 다 "게임"이 아니라 "계정"에 얽힌 일이라 한 곳에 둔다.
//
// -----------------------------------------------------------------------------
// 순서가 중요하다
// -----------------------------------------------------------------------------
//
// 동의는 계정을 만들기 전에 받아야 한다. 게스트 계정도 기기가 만든 UUID 를
// 서버에 남기는 것이라 개인정보 처리에 해당한다. 그래서 흐름이 이렇게 된다.
//
//	1. CDN 의 terms.tsv 로 "지금 약관이 몇 판인가" 를 본다  (계정이 필요 없다)
//	2. 동의를 받는다                                        (아직 계정이 없다)
//	3. 로그인한다                                           (여기서 계정이 생긴다)
//	4. 받은 동의를 서버에 남긴다                            (증빙)
//
// 4번이 3번 뒤인 것이 이상해 보이지만, 남길 자리(user_id)가 3번에서야 생긴다.
// 클라이언트는 2번에서 받은 것을 들고 있다가 4번에 보낸다.
//
// -----------------------------------------------------------------------------
// 탈퇴는 예약한다
// -----------------------------------------------------------------------------
//
// 곧바로 지우지 않는다. 되돌릴 수 없는 일인데 잘못 누르는 일이 실제로 있다.
// 며칠 뒤로 예약해 두고 그동안 다시 들어오면 취소할 수 있게 한다.
// 앱 안에서 탈퇴를 시작할 수 있어야 한다는 애플 심사지침 5.1.1(v)은 이
// 방식으로도 충족된다.
package main

import (
	"context"
	"database/sql"
	"strconv"
	"strings"
	"time"
)

// 탈퇴를 예약하고 실제로 지우기까지 두는 시간.
const deleteGrace = 7 * 24 * time.Hour

// Consent 는 한 번의 동의다.
type Consent struct {
	Terms          int64
	AgeOK          bool
	Marketing      bool
	MarketingNight bool
}

// SaveConsent 는 동의를 남긴다.
//
// 판마다 한 행이고, 같은 판을 다시 보내면 덮어쓴다 — 선택 항목은 나중에
// 바꿀 수 있어야 하기 때문이다. 판이 다르면 새 행이라 지난 동의가 남는다.
func (s *Store) SaveConsent(ctx context.Context, userID int64, c Consent) error {
	_, err := s.db.ExecContext(ctx, `
		INSERT INTO account_consent
			(user_id, terms_version, age_ok, marketing, marketing_night)
		VALUES (?, ?, ?, ?, ?)
		ON DUPLICATE KEY UPDATE
			age_ok = VALUES(age_ok),
			marketing = VALUES(marketing),
			marketing_night = VALUES(marketing_night),
			agreed_at = NOW()`,
		userID, c.Terms, boolToInt(c.AgeOK), boolToInt(c.Marketing),
		boolToInt(c.MarketingNight))

	return err
}

// AgreedTerms 는 이 유저가 동의한 가장 높은 약관 판을 준다. 없으면 0.
//
// 클라이언트는 이 값과 지금 판을 견줘서, 낮으면 약관을 다시 띄운다.
func (s *Store) AgreedTerms(ctx context.Context, userID int64) (int64, error) {
	var v sql.NullInt64

	err := s.db.QueryRowContext(ctx,
		`SELECT MAX(terms_version) FROM account_consent WHERE user_id = ?`,
		userID).Scan(&v)

	if err != nil {
		return 0, err
	}

	return v.Int64, nil
}

// -----------------------------------------------------------------------------
// 탈퇴
// -----------------------------------------------------------------------------

// RequestDelete 는 탈퇴를 예약한다. 예약된 시각을 준다.
func (s *Store) RequestDelete(ctx context.Context, userID int64) (time.Time, error) {
	when := time.Now().Add(deleteGrace)

	_, err := s.db.ExecContext(ctx,
		`UPDATE account SET delete_at = ? WHERE user_id = ?`, when, userID)

	return when, err
}

// CancelDelete 는 예약을 무른다.
func (s *Store) CancelDelete(ctx context.Context, userID int64) error {
	_, err := s.db.ExecContext(ctx,
		`UPDATE account SET delete_at = NULL WHERE user_id = ?`, userID)

	return err
}

// PendingDelete 는 예약된 시각을 준다. 없으면 zero.
//
// DATETIME 을 그대로 받지 않고 숫자로 바꿔 받는다. DSN 에 parseTime 을 안
// 켜두었기 때문이다. 그 옵션은 모든 시각 컬럼의 읽는 방식을 바꾸는데,
// 덤프 쪽은 시각을 통째로 바이트로 읽고 있어서 켜면 그쪽이 흔들린다.
// 여기 한 줄만 숫자로 받는 편이 안전하다.
func (s *Store) PendingDelete(ctx context.Context, userID int64) (time.Time, error) {
	var at sql.NullInt64

	err := s.db.QueryRowContext(ctx,
		`SELECT UNIX_TIMESTAMP(delete_at) FROM account WHERE user_id = ?`,
		userID).Scan(&at)

	if err != nil || !at.Valid {
		return time.Time{}, err
	}

	return time.Unix(at.Int64, 0), nil
}

// PurgeDeleted 는 때가 된 계정을 실제로 지운다.
//
// 외래키가 전부 ON DELETE CASCADE 라 account 한 행만 지우면 그 유저의
// 모든 것이 같이 사라진다.
func (s *Store) PurgeDeleted(ctx context.Context) (int64, error) {
	res, err := s.db.ExecContext(ctx,
		`DELETE FROM account WHERE delete_at IS NOT NULL AND delete_at <= NOW()`)

	if err != nil {
		return 0, err
	}

	return res.RowsAffected()
}

// -----------------------------------------------------------------------------
// 거들이
// -----------------------------------------------------------------------------

// readMetaRows 는 "#키<탭>값" 줄들을 읽는다.
//
// 덤프의 머리와 같은 꼴이다. 형식을 하나 더 만들지 않으려고 그대로 쓴다 —
// 클라이언트에도 이미 이 줄을 읽는 코드가 있다.
func readMetaRows(text string) map[string]string {
	out := map[string]string{}

	for _, line := range strings.Split(text, "\n") {
		line = strings.TrimRight(line, "\r")

		if !strings.HasPrefix(line, "#") {
			continue
		}

		at := strings.IndexByte(line, '\t')

		if at < 0 {
			continue
		}

		out[line[1:at]] = strings.TrimSpace(line[at+1:])
	}

	return out
}

func metaInt(m map[string]string, key string) int64 {
	v, _ := strconv.ParseInt(strings.TrimSpace(m[key]), 10, 64)

	return v
}

func metaBool(m map[string]string, key string) bool {
	return metaInt(m, key) != 0
}

func boolToInt(v bool) int {
	if v {
		return 1
	}

	return 0
}
