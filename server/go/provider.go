// 발급처 목록과, 그것을 어떻게 믿을 것인가.
//
// 소셜 로그인은 다 비슷해 보이지만 "이 사람이 맞다"를 확인하는 방법이
// 셋으로 갈리고, 그 차이가 안전과 비용을 다 정한다.
//
//	kindOIDC       서명된 신분증(JWT)을 준다. 공개키만 받아두면 우리가
//	               직접 확인한다. 로그인마다 외부 왕복이 없다.
//	               구글 · 애플 · 라인 · 카카오(OIDC)
//
//	kindIntrospect 불투명한 토큰을 준다. 그쪽에 "이거 우리 앱에 준 것 맞나"를
//	               물어봐야 한다. 왕복이 하나 붙고 그쪽 가동률에 매인다.
//	               페이스북 · 카카오(옛 방식)
//
//	kindCode       인가 코드를 받아 우리 비밀로 직접 바꾼다. 바꿔진 토큰은
//	               정의상 우리 것이라 가장 안전하다. 대신 클라이언트가
//	               코드를 넘겨줘야 한다.
//	               네이버
//
// -----------------------------------------------------------------------------
// 왜 "우리 앱에 발급된 것인가" 를 반드시 봐야 하는가
// -----------------------------------------------------------------------------
//
// 이것이 소셜 로그인에서 제일 자주 빠지는 자리다.
//
// 공격자가 자기 앱을 하나 만들고, 피해자가 거기에 소셜 로그인을 한다. 그러면
// 공격자는 피해자 이름으로 발급된 멀쩡한 토큰을 손에 넣는다. 그것을 우리
// 서버에 그대로 들이밀면, 우리가 "누구 것인가"만 보고 "누구에게 준 것인가"를
// 안 보는 한 그대로 피해자 계정에 들어온다.
//
// 그래서 부류마다 그 확인이 반드시 들어간다.
//
//	kindOIDC        aud 가 우리 클라이언트 ID 인지 본다
//	kindIntrospect  그쪽이 알려주는 app_id 가 우리 것인지 본다
//	kindCode        우리 비밀로 바꾼 것이라 따로 볼 것이 없다
//
// 확인할 방법이 없는 발급처는 켜지 않는다. 모르는 채로 받아주느니 막는다.
package main

import "strings"

// Provider 는 LoginDef.h 의 값과 같아야 한다. 뒤에만 더한다 — 가운데에
// 끼우면 이미 붙어 있는 account_link 행이 딴 곳을 가리킨다.
const (
	ProviderFacebook Provider = 4
	ProviderKakao    Provider = 5
	ProviderLine     Provider = 6
	ProviderNaver    Provider = 7
)

type verifyKind int

const (
	kindOIDC verifyKind = iota
	kindIntrospect
	kindCode
)

// provider 는 발급처 하나에 대해 알아야 할 전부다.
type provider struct {
	name string
	kind verifyKind

	// 화면에 먼저 보일 곳. 서버는 안 쓰고 기록용이다.
	region string
}

var providerInfo = map[Provider]provider{
	ProviderGoogle:   {name: "google", kind: kindOIDC, region: "전세계"},
	ProviderApple:    {name: "apple", kind: kindOIDC, region: "전세계"},
	ProviderLine:     {name: "line", kind: kindOIDC, region: "일본·대만·태국"},
	ProviderKakao:    {name: "kakao", kind: kindOIDC, region: "한국"},
	ProviderFacebook: {name: "facebook", kind: kindIntrospect, region: "동남아·중남미"},
	ProviderNaver:    {name: "naver", kind: kindCode, region: "한국"},
}

// ProviderByName 은 클라이언트가 보낸 이름을 번호로 바꾼다.
func ProviderByName(s string) (Provider, bool) {
	s = strings.ToLower(strings.TrimSpace(s))

	if s == "guest" {
		return ProviderGuest, true
	}

	for p, info := range providerInfo {
		if info.name == s {
			return p, true
		}
	}

	return ProviderGuest, false
}

// Name 은 기록에 쓸 이름이다.
func (p Provider) Name() string {
	if info, ok := providerInfo[p]; ok {
		return info.name
	}

	if p == ProviderGuest {
		return "guest"
	}

	return "?"
}

// Kind 는 이 발급처를 어떻게 믿는지다.
func (p Provider) Kind() verifyKind {
	if info, ok := providerInfo[p]; ok {
		return info.kind
	}

	return kindOIDC
}
