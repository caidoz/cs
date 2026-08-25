// 계정 잇기.
//
// 계정은 언제나 게스트로 시작한다 — 첫 실행에 기기가 만든 UUID 가 열쇠다
// (account.guest_key 가 NOT NULL 인 이유다). 구글·애플은 그 계정을 "만드는"
// 것이 아니라 "붙는" 것이다. 그래서 두 길이 있다.
//
//	POST /v1/link    지금 로그인한 계정에 구글을 붙인다
//	POST /v1/login   구글로 로그인한다 = 붙어 있는 계정을 찾아 돌려준다
//
// 앱을 지우고 다시 깔면 기기 열쇠가 새로 생겨 새 계정이 된다. 거기서 구글로
// 로그인하면 예전 계정이 돌아온다. 그것이 이 기능의 목적이다.
//
// 합치지는 않는다. 이미 다른 계정에 붙어 있는 구글로 또 붙이려 하면 거절한다.
// 두 세이브를 어떻게 합칠지는 코드가 정할 일이 아니라 게임이 정할 일이다.
package main

import (
	"context"
	"database/sql"
	"errors"

	"github.com/go-sql-driver/mysql"
)

// ErrNoLink 는 그 구글 계정에 붙은 것이 없다는 뜻이다.
var ErrNoLink = errors.New("연동된 계정이 없다")

// ErrLinkTaken 은 그 구글 계정이 이미 다른 유저에게 붙어 있다는 뜻이다.
var ErrLinkTaken = errors.New("이미 다른 계정에 붙어 있다")

// FindLinked 는 그 발급처 계정에 붙은 유저를 찾는다.
func (s *Store) FindLinked(ctx context.Context, p Provider, uid string) (int64, error) {
	var userID int64

	err := s.db.QueryRowContext(ctx,
		`SELECT user_id FROM account_link WHERE provider = ? AND provider_uid = ?`,
		int(p), uid).Scan(&userID)

	if err == sql.ErrNoRows {
		return 0, ErrNoLink
	}

	if err != nil {
		return 0, err
	}

	// 차단된 계정인지 본다. 게스트 로그인과 같은 잣대여야 한다.
	var banned bool

	if err := s.db.QueryRowContext(ctx,
		`SELECT IFNULL(banned_until > NOW(), 0) FROM account WHERE user_id = ?`,
		userID).Scan(&banned); err == nil && banned {
		return 0, ErrBanned
	}

	if _, err := s.db.ExecContext(ctx,
		`UPDATE account SET last_login_at = NOW() WHERE user_id = ?`, userID); err != nil {
		return 0, err
	}

	return userID, nil
}

// Link 는 지금 계정에 발급처 계정을 붙인다.
//
// 같은 것을 두 번 붙이는 것은 성공으로 친다. 클라이언트가 답을 못 받고
// 다시 보내는 일이 흔하고, 그때마다 실패로 보이면 붙일 방법이 없다.
func (s *Store) Link(ctx context.Context, userID int64, p Provider, uid string) error {
	_, err := s.db.ExecContext(ctx,
		`INSERT INTO account_link (user_id, provider, provider_uid) VALUES (?, ?, ?)`,
		userID, int(p), uid)

	if err == nil {
		return nil
	}

	var me *mysql.MySQLError

	if !errors.As(err, &me) || me.Number != 1062 {
		return err
	}

	// 1062 는 같은 것이 이미 있다는 뜻이다. 누구에게 붙어 있는지를 봐야
	// "이미 내 것" 인지 "남의 것" 인지 갈린다.
	var owner int64

	qerr := s.db.QueryRowContext(ctx,
		`SELECT user_id FROM account_link WHERE provider = ? AND provider_uid = ?`,
		int(p), uid).Scan(&owner)

	if qerr == nil && owner == userID {
		return nil
	}

	if qerr == nil {
		return ErrLinkTaken
	}

	// provider_uid 는 안 겹치는데 (user_id, provider) 가 겹친다.
	// 이 계정에 이미 다른 구글이 붙어 있다는 뜻이다.
	return ErrLinkTaken
}

// Links 는 그 계정에 무엇이 붙어 있는지 준다. 화면에 보여줄 때 쓴다.
func (s *Store) Links(ctx context.Context, userID int64) ([]Provider, error) {
	rows, err := s.db.QueryContext(ctx,
		`SELECT provider FROM account_link WHERE user_id = ? ORDER BY provider`, userID)

	if err != nil {
		return nil, err
	}

	defer rows.Close()

	var out []Provider

	for rows.Next() {
		var p int

		if err := rows.Scan(&p); err != nil {
			return nil, err
		}

		out = append(out, Provider(p))
	}

	return out, rows.Err()
}
