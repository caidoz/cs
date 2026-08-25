#pragma once

#ifndef _CONFIG_CONTENT_H_
#define _CONFIG_CONTENT_H_

//=============================================================================
// 콘텐츠 배포 설정
//
// BuildConfig.h 에 두지 않는다. 그쪽은 Definitions.xlsx 에서 자동 생성되는
// 파일이라 여기 적은 것이 다음 생성 때 날아간다.
//=============================================================================

//---- 갱신을 받아올 곳 ----
//
// 끝에 / 를 붙인다. 여기에 매니페스트와 파일들이 있어야 한다.
//
//     <베이스>/manifest.tsv
//     <베이스>/data/content.pack
//     <베이스>/res/aa.png
//
// 비워 두면 네트워크를 안 탄다. 대신 쓰기 가능 경로의 cdn/ 폴더를 본다.
// 서버 없이 갱신이 도는지 시험할 때 그렇게 쓴다.
//
// 올릴 곳이 정해지면 여기만 채우면 된다. 코드는 안 고쳐도 된다.
//
//     #define CONTENT_CDN_URL "https://cdn.example.com/cs/"
//
// https 를 쓸 것. http 로 두면 안드로이드와 iOS가 기본 설정에서 막는다.
#define CONTENT_CDN_URL "https://cdn.bigpixel.kr/"

#endif
