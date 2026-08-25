#pragma once

#ifndef _DEF_LOGIN_H_
#define _DEF_LOGIN_H_

//로그인 수단.
//
//이 숫자가 그대로 account_link.provider 에 들어간다. 그래서 가운데에 끼우면
//안 된다 — 이미 붙어 있는 행이 딴 곳을 가리키게 된다. 늘 뒤에만 더한다.
//
//서버가 확인하는 방법은 셋으로 갈린다. 자세한 것은 server/go/provider.go.
//  신분증(JWT)을 준다   구글 · 애플 · 라인 · 카카오
//  물어봐야 한다        페이스북
//  코드를 바꿔야 한다   네이버
typedef enum _loginDef {
	VERIFY_GUEST = 1,
	VERIFY_GOOGLE,
	VERIFY_APPLE,
	VERIFY_FACEBOOK,
	VERIFY_KAKAO,
	VERIFY_LINE,
	VERIFY_NAVER,
	TOTALVERIFY,
} LOGINDEF;

#endif
