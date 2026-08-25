package main

import (
	"crypto"
	"crypto/ecdsa"
	"crypto/elliptic"
	"crypto/rand"
	"crypto/rsa"
	"crypto/sha256"
	"encoding/base64"
	"encoding/json"
	"fmt"
	"math/big"
	"net/http"
	"net/http/httptest"
	"testing"
	"time"
)

// 구글 흉내를 낸다. 우리 손으로 만든 열쇠로 서명하고, 그 공개키를 내주는
// 주소를 세운 뒤, 발급처가 거기를 보게 한다.
//
// 이렇게까지 하는 이유는 이 검증이 계정의 자물쇠이기 때문이다. 여기가 뚫리면
// 남의 계정으로 그냥 들어온다. 눈으로 읽어서 맞다고 넘길 자리가 아니다.
type fakeIssuer struct {
	key *rsa.PrivateKey
	srv *httptest.Server
	kid string
}

func newFakeIssuer(t *testing.T) *fakeIssuer {
	t.Helper()

	key, err := rsa.GenerateKey(rand.Reader, 2048)

	if err != nil {
		t.Fatal(err)
	}

	f := &fakeIssuer{key: key, kid: "test-kid-1"}

	f.srv = httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		n := base64.RawURLEncoding.EncodeToString(key.N.Bytes())
		e := base64.RawURLEncoding.EncodeToString(big.NewInt(int64(key.E)).Bytes())

		fmt.Fprintf(w, `{"keys":[{"kty":"RSA","kid":%q,"n":%q,"e":%q}]}`, f.kid, n, e)
	}))

	t.Cleanup(f.srv.Close)

	return f
}

// sign 은 머리와 몸통을 받아 JWT 한 장을 만든다.
func (f *fakeIssuer) sign(t *testing.T, head, claims map[string]any) string {
	t.Helper()

	seg := func(v any) string {
		b, err := json.Marshal(v)

		if err != nil {
			t.Fatal(err)
		}

		return base64.RawURLEncoding.EncodeToString(b)
	}

	body := seg(head) + "." + seg(claims)
	sum := sha256.Sum256([]byte(body))
	sig, err := rsa.SignPKCS1v15(rand.Reader, f.key, crypto.SHA256, sum[:])

	if err != nil {
		t.Fatal(err)
	}

	return body + "." + base64.RawURLEncoding.EncodeToString(sig)
}

// 시험하는 동안만 구글 발급처를 우리 흉내로 바꿔 끼운다.
func useFake(t *testing.T, f *fakeIssuer, aud string) {
	t.Helper()

	is := issuers[ProviderGoogle]
	oldURL, oldIss, oldAud := is.jwksURL, is.iss, is.aud
	oldKeys, oldFetched := is.keys, is.fetched

	is.jwksURL = f.srv.URL
	is.iss = []string{"https://accounts.google.com"}
	is.aud = []string{aud}
	is.keys = nil
	is.fetched = time.Time{}

	t.Cleanup(func() {
		is.jwksURL, is.iss, is.aud = oldURL, oldIss, oldAud
		is.keys, is.fetched = oldKeys, oldFetched
	})
}

func goodClaims(now time.Time, aud string) map[string]any {
	return map[string]any{
		"iss": "https://accounts.google.com",
		"sub": "1234567890",
		"aud": aud,
		"exp": now.Add(time.Hour).Unix(),
		"iat": now.Unix(),
	}
}

func TestVerifyGoodToken(t *testing.T) {
	f := newFakeIssuer(t)
	useFake(t, f, "우리앱.apps.googleusercontent.com")

	now := time.Now()
	tok := f.sign(t, map[string]any{"alg": "RS256", "kid": f.kid},
		goodClaims(now, "우리앱.apps.googleusercontent.com"))

	sub, err := VerifyIDToken(ProviderGoogle, tok, now)

	if err != nil {
		t.Fatalf("멀쩡한 신분증을 거절했다: %v", err)
	}

	if sub != "1234567890" {
		t.Fatalf("sub 가 %q 다", sub)
	}
}

// 여기가 제일 중요하다. aud 를 안 보면 남의 앱에서 받은 구글 토큰으로
// 우리 서버에 들어올 수 있다.
func TestRejectOtherAppToken(t *testing.T) {
	f := newFakeIssuer(t)
	useFake(t, f, "우리앱.apps.googleusercontent.com")

	now := time.Now()
	tok := f.sign(t, map[string]any{"alg": "RS256", "kid": f.kid},
		goodClaims(now, "남의앱.apps.googleusercontent.com"))

	if _, err := VerifyIDToken(ProviderGoogle, tok, now); err == nil {
		t.Fatal("남의 앱 토큰을 받아들였다")
	}
}

// alg 를 안 보면 "none" 을 적어 서명 없이 들어오는 길이 열린다.
func TestRejectAlgNone(t *testing.T) {
	f := newFakeIssuer(t)
	useFake(t, f, "우리앱")

	now := time.Now()
	tok := f.sign(t, map[string]any{"alg": "none", "kid": f.kid},
		goodClaims(now, "우리앱"))

	if _, err := VerifyIDToken(ProviderGoogle, tok, now); err == nil {
		t.Fatal("alg=none 을 받아들였다")
	}
}

func TestRejectTamperedSignature(t *testing.T) {
	f := newFakeIssuer(t)
	useFake(t, f, "우리앱")

	now := time.Now()
	tok := f.sign(t, map[string]any{"alg": "RS256", "kid": f.kid},
		goodClaims(now, "우리앱"))

	if _, err := VerifyIDToken(ProviderGoogle, tok[:len(tok)-2]+"AA", now); err == nil {
		t.Fatal("서명이 다른데 받아들였다")
	}
}

// 몸통만 바꿔치기해도 서명이 안 맞아야 한다.
func TestRejectSwappedBody(t *testing.T) {
	f := newFakeIssuer(t)
	useFake(t, f, "우리앱")

	now := time.Now()
	good := f.sign(t, map[string]any{"alg": "RS256", "kid": f.kid}, goodClaims(now, "우리앱"))

	other := goodClaims(now, "우리앱")
	other["sub"] = "9999999999"
	evil := f.sign(t, map[string]any{"alg": "RS256", "kid": f.kid}, other)

	// 좋은 것의 서명에 나쁜 몸통을 붙인다.
	parts := func(s string) []string {
		out := []string{}
		at := 0

		for i := 0; i < len(s); i++ {
			if s[i] == '.' {
				out = append(out, s[at:i])
				at = i + 1
			}
		}

		return append(out, s[at:])
	}

	g, e := parts(good), parts(evil)
	mixed := g[0] + "." + e[1] + "." + g[2]

	if _, err := VerifyIDToken(ProviderGoogle, mixed, now); err == nil {
		t.Fatal("몸통을 바꿔치기했는데 받아들였다")
	}
}

func TestRejectExpired(t *testing.T) {
	f := newFakeIssuer(t)
	useFake(t, f, "우리앱")

	now := time.Now()
	c := goodClaims(now, "우리앱")
	c["exp"] = now.Add(-time.Minute).Unix()

	tok := f.sign(t, map[string]any{"alg": "RS256", "kid": f.kid}, c)

	if _, err := VerifyIDToken(ProviderGoogle, tok, now); err == nil {
		t.Fatal("만료된 것을 받아들였다")
	}
}

func TestRejectWrongIssuer(t *testing.T) {
	f := newFakeIssuer(t)
	useFake(t, f, "우리앱")

	now := time.Now()
	c := goodClaims(now, "우리앱")
	c["iss"] = "https://evil.example.com"

	tok := f.sign(t, map[string]any{"alg": "RS256", "kid": f.kid}, c)

	if _, err := VerifyIDToken(ProviderGoogle, tok, now); err == nil {
		t.Fatal("발급처가 다른데 받아들였다")
	}
}

// aud 가 목록으로 오는 경우도 있다. 그 안에 우리가 있으면 통과여야 한다.
func TestAudienceList(t *testing.T) {
	f := newFakeIssuer(t)
	useFake(t, f, "우리앱")

	now := time.Now()
	c := goodClaims(now, "")
	c["aud"] = []string{"남의앱", "우리앱"}

	tok := f.sign(t, map[string]any{"alg": "RS256", "kid": f.kid}, c)

	if _, err := VerifyIDToken(ProviderGoogle, tok, now); err != nil {
		t.Fatalf("목록 안에 우리가 있는데 거절했다: %v", err)
	}
}

// 클라이언트 ID 를 안 넣었으면 아예 안 켜져야 한다. aud 를 확인 못 하는 채로
// 받아주면 남의 앱 토큰이 그대로 통과한다.
func TestDisabledWithoutAudience(t *testing.T) {
	f := newFakeIssuer(t)
	useFake(t, f, "우리앱")

	issuers[ProviderGoogle].aud = nil

	if Enabled(ProviderGoogle) {
		t.Fatal("클라이언트 ID 가 없는데 켜져 있다")
	}

	now := time.Now()
	tok := f.sign(t, map[string]any{"alg": "RS256", "kid": f.kid}, goodClaims(now, "우리앱"))

	if _, err := VerifyIDToken(ProviderGoogle, tok, now); err == nil {
		t.Fatal("안 켰는데 확인해줬다")
	}
}

func TestSplitCred(t *testing.T) {
	cases := []struct {
		in   string
		want Provider
		cred string
	}{
		{"6da1e647-d01f-47ba-bbd5-1f31e14a07b5", ProviderGuest, "6da1e647-d01f-47ba-bbd5-1f31e14a07b5"},
		{"guest\t6da1e647", ProviderGuest, "6da1e647"},
		{"google\teyJhbGc", ProviderGoogle, "eyJhbGc"},
		{"apple\teyJhbGc", ProviderApple, "eyJhbGc"},
		{"GOOGLE\teyJhbGc", ProviderGoogle, "eyJhbGc"},
		{"몰라\t뭔가", ProviderGuest, "몰라\t뭔가"},
	}

	for _, c := range cases {
		p, cred := splitCred(c.in)

		if p != c.want || cred != c.cred {
			t.Fatalf("%q -> (%d, %q), 바란 것은 (%d, %q)", c.in, p, cred, c.want, c.cred)
		}
	}
}

// -----------------------------------------------------------------------------
// 라인은 ES256 으로 서명한다
// -----------------------------------------------------------------------------

type fakeECIssuer struct {
	key *ecdsa.PrivateKey
	srv *httptest.Server
	kid string
}

func newFakeEC(t *testing.T) *fakeECIssuer {
	t.Helper()

	key, err := ecdsa.GenerateKey(elliptic.P256(), rand.Reader)

	if err != nil {
		t.Fatal(err)
	}

	f := &fakeECIssuer{key: key, kid: "ec-kid-1"}

	f.srv = httptest.NewServer(http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		pad := func(b []byte) string {
			out := make([]byte, 32)
			copy(out[32-len(b):], b)

			return base64.RawURLEncoding.EncodeToString(out)
		}

		fmt.Fprintf(w, `{"keys":[{"kty":"EC","crv":"P-256","kid":%q,"x":%q,"y":%q}]}`,
			f.kid, pad(key.X.Bytes()), pad(key.Y.Bytes()))
	}))

	t.Cleanup(f.srv.Close)

	return f
}

func (f *fakeECIssuer) sign(t *testing.T, alg string, claims map[string]any) string {
	t.Helper()

	seg := func(v any) string {
		b, err := json.Marshal(v)

		if err != nil {
			t.Fatal(err)
		}

		return base64.RawURLEncoding.EncodeToString(b)
	}

	body := seg(map[string]any{"alg": alg, "kid": f.kid}) + "." + seg(claims)
	sum := sha256.Sum256([]byte(body))

	r, s, err := ecdsa.Sign(rand.Reader, f.key, sum[:])

	if err != nil {
		t.Fatal(err)
	}

	// r 과 s 를 32바이트씩 이어 붙인다. 이게 ES256 서명 꼴이다.
	sig := make([]byte, 64)
	r.FillBytes(sig[:32])
	s.FillBytes(sig[32:])

	return body + "." + base64.RawURLEncoding.EncodeToString(sig)
}

func useFakeLine(t *testing.T, f *fakeECIssuer, aud string) {
	t.Helper()

	is := issuers[ProviderLine]

	// 통째로 복사하면 안 된다. 안에 잠금이 들어 있어서 복사본이 그 상태를
	// 같이 들고 간다. 필요한 칸만 따로 빼둔다.
	oldURL, oldIss, oldAud := is.jwksURL, is.iss, is.aud
	oldKeys, oldFetched := is.keys, is.fetched

	is.jwksURL = f.srv.URL
	is.iss = []string{"https://access.line.me"}
	is.aud = []string{aud}
	is.keys = nil
	is.fetched = time.Time{}

	t.Cleanup(func() {
		is.jwksURL, is.iss, is.aud = oldURL, oldIss, oldAud
		is.keys, is.fetched = oldKeys, oldFetched
	})
}

func TestLineES256(t *testing.T) {
	f := newFakeEC(t)
	useFakeLine(t, f, "line-channel-id")

	now := time.Now()
	tok := f.sign(t, "ES256", map[string]any{
		"iss": "https://access.line.me",
		"sub": "U1234567890",
		"aud": "line-channel-id",
		"exp": now.Add(time.Hour).Unix(),
	})

	sub, err := VerifyIDToken(ProviderLine, tok, now)

	if err != nil {
		t.Fatalf("멀쩡한 라인 신분증을 거절했다: %v", err)
	}

	if sub != "U1234567890" {
		t.Fatalf("sub 가 %q 다", sub)
	}
}

// alg 와 열쇠 종류가 어긋나면 거절해야 한다. 이것을 안 보면 오래된
// 수법(공개키를 다른 알고리즘의 열쇠인 척)이 통한다.
func TestLineRejectAlgMismatch(t *testing.T) {
	f := newFakeEC(t)
	useFakeLine(t, f, "line-channel-id")

	now := time.Now()
	tok := f.sign(t, "RS256", map[string]any{
		"iss": "https://access.line.me",
		"sub": "U1234567890",
		"aud": "line-channel-id",
		"exp": now.Add(time.Hour).Unix(),
	})

	if _, err := VerifyIDToken(ProviderLine, tok, now); err == nil {
		t.Fatal("EC 열쇠인데 RS256 이라고 적은 것을 받아들였다")
	}
}

func TestLineRejectOtherChannel(t *testing.T) {
	f := newFakeEC(t)
	useFakeLine(t, f, "line-channel-id")

	now := time.Now()
	tok := f.sign(t, "ES256", map[string]any{
		"iss": "https://access.line.me",
		"sub": "U1234567890",
		"aud": "남의채널",
		"exp": now.Add(time.Hour).Unix(),
	})

	if _, err := VerifyIDToken(ProviderLine, tok, now); err == nil {
		t.Fatal("남의 채널 토큰을 받아들였다")
	}
}

func TestProviderNames(t *testing.T) {
	for _, name := range []string{"google", "apple", "kakao", "line", "facebook", "naver", "guest"} {
		p, ok := ProviderByName(name)

		if !ok {
			t.Fatalf("%s 를 모른다", name)
		}

		if p.Name() != name {
			t.Fatalf("%s -> %d -> %s", name, p, p.Name())
		}
	}

	if _, ok := ProviderByName("몰라"); ok {
		t.Fatal("모르는 이름을 안다고 한다")
	}
}
