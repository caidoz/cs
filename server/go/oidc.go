// 구글·애플이 준 신분증(id_token)을 확인한다.
//
// 둘 다 RS256 으로 서명한 JWT 를 준다. 확인하는 방법이 두 가지다.
//
//	tokeninfo 같은 확인용 주소에 물어본다   — 코드는 짧지만 로그인마다 왕복이
//	                                          하나 더 붙고 남의 한도에 매인다
//	서명을 직접 확인한다                    — 공개키만 받아두면 왕복이 없다
//
// 뒤쪽을 골랐다. 백만 명이 로그인하는데 그때마다 구글에 물어볼 이유가 없다.
// 공개키(JWKS)는 한 번 받아 얼마간 들고 있는다.
//
// 확인하는 것은 넷이다. 하나라도 빠지면 확인이 아니다.
//
//	서명    남이 지어낸 것이 아닌가
//	iss     정말 구글/애플이 발급했는가
//	aud     "우리 앱" 에게 준 것인가 — 이게 없으면 남의 앱 토큰으로 들어온다
//	exp     아직 살아 있는가
package main

import (
	"crypto"
	"crypto/rsa"
	"crypto/sha256"
	"crypto/subtle"
	"encoding/base64"
	"encoding/json"
	"errors"
	"fmt"
	"math/big"
	"net/http"
	"strings"
	"sync"
	"time"
)

var ErrBadIDToken = errors.New("신분증이 아니다")

// 공개키를 이만큼 들고 있는다. 구글은 자주 바꾸지 않지만 영영 두면 안 된다.
const jwksLife = 6 * time.Hour

// Provider 는 어느 쪽이 발급했는지다. LoginDef.h 의 값과 같아야 한다.
type Provider int

const (
	ProviderGuest  Provider = 1
	ProviderGoogle Provider = 2
	ProviderApple  Provider = 3
)

// issuer 는 발급처 하나에 대한 설정이다.
type issuer struct {
	name    string
	jwksURL string
	iss     []string
	aud     []string // 우리 앱의 클라이언트 ID. 여러 플랫폼이면 여러 개다.

	mu      sync.Mutex
	keys    map[string]*rsa.PublicKey
	fetched time.Time
}

var issuers = map[Provider]*issuer{
	ProviderGoogle: {
		name:    "google",
		jwksURL: "https://www.googleapis.com/oauth2/v3/certs",
		iss:     []string{"accounts.google.com", "https://accounts.google.com"},
	},
	ProviderApple: {
		name:    "apple",
		jwksURL: "https://appleid.apple.com/auth/keys",
		iss:     []string{"https://appleid.apple.com"},
	},
}

// SetAudiences 는 우리 앱의 클라이언트 ID 를 넣는다. 비어 있으면 그 발급처는
// 아예 안 쓴다 — aud 를 확인하지 못하면 남의 앱 토큰으로 들어올 수 있어서,
// 모르는 채로 받아주느니 막는 편이 낫다.
func SetAudiences(p Provider, list string) {
	is := issuers[p]

	if is == nil {
		return
	}

	is.aud = nil

	for _, a := range strings.Split(list, ",") {
		if a = strings.TrimSpace(a); a != "" {
			is.aud = append(is.aud, a)
		}
	}
}

// Enabled 는 그 발급처를 쓸 수 있는지 본다.
func Enabled(p Provider) bool {
	is := issuers[p]

	return is != nil && len(is.aud) > 0
}

// VerifyIDToken 은 신분증을 확인하고 그쪽 계정 번호(sub)를 준다.
func VerifyIDToken(p Provider, tok string, now time.Time) (string, error) {
	is := issuers[p]

	if is == nil || len(is.aud) == 0 {
		return "", fmt.Errorf("%v 는 아직 안 켰다", p)
	}

	f := strings.Split(tok, ".")

	if len(f) != 3 {
		return "", ErrBadIDToken
	}

	head, err := decodeSeg(f[0])

	if err != nil {
		return "", ErrBadIDToken
	}

	var h struct {
		Alg string `json:"alg"`
		Kid string `json:"kid"`
	}

	if json.Unmarshal(head, &h) != nil || h.Alg != "RS256" {
		// alg 를 안 보면 "none" 을 적어 서명 없이 들어오는 길이 열린다.
		return "", ErrBadIDToken
	}

	key, err := is.key(h.Kid)

	if err != nil {
		return "", err
	}

	sig, err := decodeSeg(f[2])

	if err != nil {
		return "", ErrBadIDToken
	}

	sum := sha256.Sum256([]byte(f[0] + "." + f[1]))

	if rsa.VerifyPKCS1v15(key, crypto.SHA256, sum[:], sig) != nil {
		return "", ErrBadIDToken
	}

	body, err := decodeSeg(f[1])

	if err != nil {
		return "", ErrBadIDToken
	}

	var c struct {
		Iss string          `json:"iss"`
		Sub string          `json:"sub"`
		Aud json.RawMessage `json:"aud"`
		Exp int64           `json:"exp"`
		Nbf int64           `json:"nbf"`
	}

	if json.Unmarshal(body, &c) != nil || c.Sub == "" {
		return "", ErrBadIDToken
	}

	if !oneOf(is.iss, c.Iss) {
		return "", ErrBadIDToken
	}

	if c.Exp <= now.Unix() {
		return "", ErrBadIDToken
	}

	if c.Nbf != 0 && c.Nbf > now.Unix()+60 {
		return "", ErrBadIDToken
	}

	// aud 는 문자열일 수도, 문자열 목록일 수도 있다.
	auds, err := readAud(c.Aud)

	if err != nil {
		return "", ErrBadIDToken
	}

	ok := false

	for _, a := range auds {
		if oneOfConst(is.aud, a) {
			ok = true
			break
		}
	}

	if !ok {
		return "", ErrBadIDToken
	}

	return c.Sub, nil
}

// key 는 kid 에 맞는 공개키를 준다. 없으면 한 번 다시 받아본다.
func (is *issuer) key(kid string) (*rsa.PublicKey, error) {
	is.mu.Lock()
	defer is.mu.Unlock()

	if k, ok := is.keys[kid]; ok && time.Since(is.fetched) < jwksLife {
		return k, nil
	}

	// 없거나 오래됐다. 다시 받는다. 열쇠가 도는 중일 수 있다.
	if err := is.refresh(); err != nil {
		return nil, err
	}

	if k, ok := is.keys[kid]; ok {
		return k, nil
	}

	return nil, ErrBadIDToken
}

func (is *issuer) refresh() error {
	cli := &http.Client{Timeout: 10 * time.Second}
	res, err := cli.Get(is.jwksURL)

	if err != nil {
		return fmt.Errorf("%s 공개키를 못 받았다: %w", is.name, err)
	}

	defer res.Body.Close()

	if res.StatusCode != http.StatusOK {
		return fmt.Errorf("%s 공개키 HTTP %d", is.name, res.StatusCode)
	}

	var set struct {
		Keys []struct {
			Kty string `json:"kty"`
			Kid string `json:"kid"`
			N   string `json:"n"`
			E   string `json:"e"`
		} `json:"keys"`
	}

	if err := json.NewDecoder(res.Body).Decode(&set); err != nil {
		return fmt.Errorf("%s 공개키 형식이 다르다: %w", is.name, err)
	}

	keys := map[string]*rsa.PublicKey{}

	for _, k := range set.Keys {
		if k.Kty != "RSA" {
			continue
		}

		n, err1 := decodeSeg(k.N)
		e, err2 := decodeSeg(k.E)

		if err1 != nil || err2 != nil {
			continue
		}

		ev := 0

		for _, b := range e {
			ev = ev<<8 | int(b)
		}

		if ev == 0 {
			continue
		}

		keys[k.Kid] = &rsa.PublicKey{N: new(big.Int).SetBytes(n), E: ev}
	}

	if len(keys) == 0 {
		return fmt.Errorf("%s 공개키가 하나도 없다", is.name)
	}

	is.keys = keys
	is.fetched = time.Now()

	return nil
}

func decodeSeg(s string) ([]byte, error) {
	return base64.RawURLEncoding.DecodeString(s)
}

func oneOf(list []string, v string) bool {
	for _, x := range list {
		if x == v {
			return true
		}
	}

	return false
}

// oneOfConst 는 걸린 시간으로 값을 알아내지 못하게 끝까지 견준다.
func oneOfConst(list []string, v string) bool {
	ok := false

	for _, x := range list {
		if subtle.ConstantTimeCompare([]byte(x), []byte(v)) == 1 {
			ok = true
		}
	}

	return ok
}

func readAud(raw json.RawMessage) ([]string, error) {
	if len(raw) == 0 {
		return nil, ErrBadIDToken
	}

	var one string

	if json.Unmarshal(raw, &one) == nil {
		return []string{one}, nil
	}

	var many []string

	if json.Unmarshal(raw, &many) == nil {
		return many, nil
	}

	return nil, ErrBadIDToken
}
