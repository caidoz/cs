#pragma once
// =============================================================
// AUTO GENERATED - DO NOT EDIT
// Source : Definitions.xlsx
// Sheet  : BuildConfig
// Date   : 2026-02-26 17:21
// =============================================================


// ---
#define DEVELOPMENT                    // 개발 빌드 모드
// #define RELEASE                     // 릴리즈 빌드 모드

// ---
#define GAMEDEBUG                      // 게임 전체 디버그
#define DEBUGMENU                      // 디버그 메뉴 표시
#define TURNRPG			0                   // 턴제 RPG 모드
#define ACTIONRPG		1					// 액션 RPG
#define INFINITEMODE                   // 무한 모드
#define NOIAP                          // 인앱결제 비활성화

// ---
#define ROULETTE                       // 룰렛 시스템
#define ROULETTEICON                   // 룰렛 아이콘 표시
#define SELECTROULETTE                 // 룰렛 선택 모드
#define SHOWJOKBOMULTIPLE              // 족보 배율 표시

// ---
#define ONEHEARTONEATTACK              // 하트 1개당 공격 1회
#define ENEMYUSER                      // 적 유저 모드
#define PVPWITHUSER                    // 유저간 PVP
#define NOCRITICAL                     // 크리티컬 없음
#define STUNEXCEPTBOSS                 // 보스 스턴 제외
#define DAMAGE_REDUCE_BY_HP            // HP에 따른 데미지 감소
#define ATTACK_INIT_DELAY              // 공격 초기 딜레이
#define MANUALDELAY                    // 수동 딜레이

// ---
#define BGEFFECTDRAW                   // 배경 이펙트 렌더
#define CLIPPING                       // 클리핑
#define DOUBLEBUFFERING                // 더블 버퍼링
#define EQUIPCARDIMG                   // 장비 카드 이미지
#define CENTERDISPLAY                  // 중앙 디스플레이
#define TTFFONT                        // TTF 폰트 사용

// ---
#define DROPONLYROBINS                 // 로빈 아이템만 드롭
#define WITHOUTNECKRING                // 목걸이/반지 제외
#define SETITEM                        // 세트 아이템
#define ALLEQUIPLEGENDGRADE            // 모든 장비 레전드 등급
#define GLOVEATTACKFRAME               // 장갑 공격 프레임

// ---
#define SKILLCARD                      // 스킬 카드
#define SKILLTEST                      // 스킬 테스트 모드
#define ENEMYSKILLTEST                 // 적 스킬 테스트
#define NOSKILLMOVE                    // 스킬 이동 없음
#define EVERYLVGETSKILL                // 매 레벨 스킬 획득

// ---
#define LVUPBYGOLD                     // 골드로 레벨업
#define TIERPLAYERCNT                  // 티어 플레이어 수
#define TIERFLOOR                      // 티어 층수
#define TIERCUTOFF                     // 티어 컷오프

// ---
#define MOVETEST                       // 이동 테스트
#define GETITEMAUTO                    // 아이템 자동 획득
#define SCROLLTEST                     // 스크롤 테스트
#define BLOCKOBJ                       // 오브젝트 블록
#define ARENAMONDATA                   // 아레나 몬스터 데이터
#define WARIGARI                       // 와리가리
#define CAGE                           // 케이지
#define INTEREST                       // 이자 시스템
#define NOINERTIA                      // 관성 없음

// ---
#define HITMARKSHOW                    // 히트마크 표시
#define HITMARKWHITE                   // 히트마크 흰색

// ---
#define ATTACKFIRSTROULETTELAST        // 공격 먼저 룰렛 나중
#define ROBINDEFAULTATTACKSTING        // 로빈 기본 공격 스팅
#define LONGSWORDLONGDMG               // 롱소드 긴 데미지

// ---
#define TITLETYPEMUSKETTERS            // 머스킷티어스 타이틀

// ---
#define MAXPLAYER_FIVE             5        // 최대 플레이어 수
#define MAXACTIVESKILL             7        // 최대 액티브 스킬
#define BIGSWORD                   5        // 큰 검 크기
#define REWARDZOOM                 2        // 보상 줌
#define EQUIPREWARDZOOM            2        // 장비 보상 줌
#define ROULETTEZOOM               0.5f     // 룰렛 줌
#define SLOTINITZOOM               0.5f    // 슬롯 초기 줌
#define SLOTZOOM                   0.6f    // 슬롯 줌
#define JOYSTICKZOOM               2.0f     // 조이스틱 줌

//---- 캐릭터 그림 뽑기 ----
//
//1 로 두고 한 번 실행하면 동료와 몬스터를 한 마리씩 PNG 로 떨구고
//그만둔다. 밸런스 엑셀에 그림을 넣으려고 만든 것이다.
//
//왜 게임이 그리나. 캐릭터 한 장은 조각을 겹쳐 그린 것이라
//(DrawCmfDetail 이 부위마다 확대/반전/반투명/라이튼을 걸며 조립한다)
//바깥에서 흉내내면 언젠가 어긋난다. 이미 그릴 줄 아는 쪽이 그린다.
//
//떨군 자리는 로그에 찍힌다. 윈도우면 대개
//    C:/Users/<이름>/AppData/Local/cs/dump/
//뽑고 나면 다시 0 으로 되돌린다. 켜 두면 게임이 안 돈다.
#define DUMP_CMF_PNG               0

//한 장의 크기와 배율. 엑셀에 넣을 것이라 크게 뽑을 필요가 없다.
#define DUMP_CMF_SIZE              128
#define DUMP_CMF_ZOOM              1.0f
