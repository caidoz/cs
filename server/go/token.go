// 세션 토큰.
//
// 1단계에서는 게스트 열쇠를 매 요청에 그대로 실어 보냈다. 그 열쇠는 계정
// 자체라, 한 번 새면 계정을 통째로 잃는다 — schema.sql 의 account.guest_key
// 주석이 이미 그렇게 경고하고 있다. 로그인 때만 쓰고, 그 뒤로는 기한이 있는
// 토큰을 쓰는 것이 이 파일의 목적이다.
//
// 토큰을 표에 담지 않는다. 서명만으로 진짜인지 알 수 있게 만든다.
//
//	v1.<user_id>.<만료 unix초>.<서명>
//
// 서명은 앞의 세 토막에 대한 HMAC-SHA256 이다. 그래서
//
//   - 요청마다 DB 를 찾지 않아도 된다. 백만 명이면 이 차이가 크다.
//   - 표를 새로 만들지 않아도 된다. 스키마는 더하기만 하는 것이 규칙이다.
//
// 대신 "지금 당장 무효로 만들기"가 안 된다. 필요해지면 account 에 토큰 세대를
// 하나 더해서 서명에 섞으면 된다. 그때 가서 컬럼 하나 더하는 일이다.
package main

import (
	"crypto/hmac"
	"crypto/sha256"
	"crypto/subtle"
	"encoding/base64"
	"errors"
	"fmt"
	"strconv"
	"strings"
	"time"
)

// 토큰이 사는 기간. 짧으면 자주 다시 로그인해야 하고, 길면 샜을 때 오래 쓴다.
// 게임을 며칠 안 켜도 그대로 이어지는 편이 나아서 넉넉히 준다.
const tokenLife = 30 * 24 * time.Hour

// 만료가 이만큼 남았으면 답할 때 새것을 끼워 준다. 쓰는 도중에 끊기지 않게.
const tokenRenewBefore = 7 * 24 * time.Hour

var ErrBadToken = errors.New("토큰이 아니다")

// tokenKey 는 서명에 쓰는 비밀이다. 기동할 때 채운다.
var tokenKey []byte

// MakeToken 은 그 유저의 토큰을 만든다.
func MakeToken(userID int64, now time.Time) (string, int64) {
	exp := now.Add(tokenLife).Unix()
	body := fmt.Sprintf("v1.%d.%d", userID, exp)

	return body + "." + sign(body), exp
}

// ReadToken 은 토큰에서 유저를 꺼낸다. 서명이나 기한이 안 맞으면 거절한다.
func ReadToken(tok string, now time.Time) (userID int64, exp int64, err error) {
	f := strings.Split(tok, ".")

	if len(f) != 4 || f[0] != "v1" {
		return 0, 0, ErrBadToken
	}

	body := f[0] + "." + f[1] + "." + f[2]

	// 서명부터 본다. 안쪽 값을 믿기 전에 확인해야 한다.
	//
	// 같은지 볼 때 == 를 쓰면 안 된다. 앞에서부터 다른 자리가 나오면 바로
	// 돌아오기 때문에, 걸린 시간으로 서명을 한 글자씩 맞춰갈 수 있다.
	if subtle.ConstantTimeCompare([]byte(f[3]), []byte(sign(body))) != 1 {
		return 0, 0, ErrBadToken
	}

	userID, err = strconv.ParseInt(f[1], 10, 64)

	if err != nil || userID <= 0 {
		return 0, 0, ErrBadToken
	}

	exp, err = strconv.ParseInt(f[2], 10, 64)

	if err != nil {
		return 0, 0, ErrBadToken
	}

	if now.Unix() >= exp {
		return 0, 0, ErrBadToken
	}

	return userID, exp, nil
}

// NeedsRenew 는 곧 만료되는지 본다.
func NeedsRenew(exp int64, now time.Time) bool {
	return time.Unix(exp, 0).Sub(now) < tokenRenewBefore
}

func sign(body string) string {
	m := hmac.New(sha256.New, tokenKey)
	m.Write([]byte(body))

	return base64.RawURLEncoding.EncodeToString(m.Sum(nil))
}
