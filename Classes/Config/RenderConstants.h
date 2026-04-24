#pragma once
// =============================================================
// RENDER CONSTANTS
// 실제 사용되는 렌더링 상수만 유지
// =============================================================

// 기본 줌 상수
#define HEROZOOM                   2.0f           // 히어로 줌
#define CREWZOOM                   1.8f           // 크루 줌
#define MONSTERZOOM                2.5f           // 몬스터 줌
#define BOSSZOOM                   2.0f           // 보스 줌
#define LOBBYZOOM                  1.5f           // 로비 줌
#define BATTLEZOOM                 1.5f          // 배틀 줌
#define SUMMONZOOM                 2.0f           // 소환 줌
#define DROPITEMZOOM               2.0f           // 드롭 아이템 줌
#define HOUSEZOOM                  1.25f          // 하우스 줌
#define HOUSEPLAYERZOOM            1.0f           // 하우스 플레이어 줌
#define BOXZOOM                    2.5f           // 박스 줌
#define BOXHOUSEZOOM               1.5f           // 박스 하우스 줌

// ---
#define REWARDICONZOOM             1.5f           // 보상 아이콘 줌
#define HEROCASTLEZOOM             2.0f           // 영웅 성 줌
#define CREWCASTLEZOOM             1.8f           // 크루 성 줌
#define HITMARKZOOM                1.0f           // 히트마크 줌
#define DIORAMAZOOM                0.63f          // 디오라마 줌
#define DIORAMAZOOM_BATTLE         0.63f//1.0f//          // 디오라마 배틀 줌
#define DIORAMAZOOM_REMAINDER      1.5f           // 디오라마 나머지 줌
#define BATTLEWEAPONZOOM           6.0f           // 배틀 무기 줌
#define HITCOUNTZOOM               1.0f           // 히트 카운트 줌
#define RAIDGOLDBARZOOM            2.5f           // 레이드 골드바 줌
#define BATTLEGOLDALPHAZOOM        2.2f           // 배틀 골드 알파 줌
#define BATTLETEXTZOOM             1.5f           // 배틀 텍스트 줌
#define PLAYERHEADZOOM             1              // 플레이어 헤드 줌
#define ALLHEADZOOM                2              // 전체 헤드 줌

// ---
#define CAMERAPER_MULTIPLE         2              // 카메라 배율 분자
#define CAMERAPER_DIVIDE           5              // 카메라 배율 분모

// ---
#define GOLDBARZOOM                0.5f           // 골드바 줌
#define CROWNBARZOOM               0.5f           // 왕관바 줌
#define BAR_GOLD_ZOOM              1.0f           // 골드 바 줌
#define BAR_CROWN_ZOOM             1.0f           // 왕관 바 줌
#define BAR_HAMMER_ZOOM            1.0f           // 망치 바 줌
#define BAR_SHIELD_ZOOM            1.0f           // 방패 바 줌
#define BAR_BOX_ZOOM               1.1f           // 박스 바 줌
#define BAR_PLAYERHP_ZOOM          1.0f           // 플레이어 HP 바 줌
#define BAR_BOSSHP_ZOOM            0.8f           // 보스 HP 바 줌
#define BAR_COIN_ZOOM              2.0f           // 코인 바 줌
#define BAR_ITEM_ZOOM              2.0f           // 아이템 바 줌
#define BAR_HERO_ZOOM              1.0f           // 영웅 바 줌
#define BAR_CREW_ZOOM              1.0f           // 크루 바 줌
#define BAR_HEART_ZOOM             1.0f           // 하트 바 줌
#define BAR_BATTLECOIN_ZOOM        1.25f          // 배틀 코인 바 줌
#define BAR_MEDAL_ZOOM             1.0f           // 메달 바 줌
#define BAR_ENEMYUSER_ZOOM         1.0f           // 적 유저 바 줌
#define BAR_ENEMYUSER_BOX_ZOOM     1.0f           // 적 유저 박스 바 줌
#define BAR_MAINSHOP_ZOOM          1.0f           // 메인샵 바 줌
#define BAR_DAILYQUEST_ZOOM        1.0f           // 일일퀘스트 바 줌
#define BAR_CREWUPGRADE_ZOOM       1.0f           // 크루 업그레이드 바 줌
#define BAR_COLLECTIONS_ZOOM       1.0f           // 컬렉션 바 줌
#define BAR_FRIENDS_ZOOM           1.0f           // 친구 바 줌
#define BAR_QUEST_ZOOM             1.0f           // 퀘스트 바 줌
#define BAR_RAIDGOLD_ZOOM          1.2f           // 레이드 골드 바 줌
#define BAR_RAIDCOIN_ZOOM          1.2f           // 레이드 코인 바 줌
#define BAR_COMBATPOWERALL_ZOOM    1.0f           // 전투력 전체 바 줌
#define BAR_COMBATPOWER_ZOOM       1.0f           // 전투력 바 줌
#define BAR_STAGEPROGRESS_ZOOM     1.0f           // 스테이지 진행 바 줌
#define BAR_REMAINEDTURN_ZOOM		3.0f           // 스테이지 진행 바 줌
#define BAR_INVENTORY_ZOOM         0.6f           // 인벤토리 바 줌
#define BAR_SKILL_ZOOM             1.0f           // 스킬 바 줌

// ---
#define EQUIPZOOM                  2.0f           // 장비 줌
#define SKILLICONZOOM              2.0f           // 스킬 아이콘 줌
#define IMGTEXTZOOM                2.0f           // 이미지 텍스트 줌
#define DMGNUMZOOM                 2.5f           // 데미지 숫자 줌
#define XNUMZOOM                   1.4f           // X 숫자 줌
#define ENEMYICONZOOM              0.6f           // 적 아이콘 줌
#define EQUIPICON_X                0              // 장비 아이콘 X
#define EQUIPICON_Y                -40 * _2X                // 장비 아이콘 Y

// ---
#define BATTLECHARZOOM             3.0f           // 배틀 캐릭터 줌
#define BATTLECHARSTARZOOM         2.0f           // 배틀 캐릭터 별 줌
#define BATTLECHARSTARZOOM_FAIL    1.2f           // 배틀 캐릭터 별 실패 줌
#define BATTLEPOSGAP_Y             -ITEMICONSIZE * 8.0f     // 배틀 위치 Y 간격
#define STAGESTARBUTTONZOOM        0.8f           // 스테이지 별 버튼 줌
#define NUM2ZOOM                   0.22f          // 숫자2 줌
#define UPGRADEBUTTONPER           0.72f          // 업그레이드 버튼 비율

// ---
#define HITCOUNTPOSX               160 * _2X                // 히트 카운트 X 위치
#define HITCOUNTPOSY               0 * _2X                  // 히트 카운트 Y 위치
#define PROFILEIMG_X               32 * _2X                 // 프로필 이미지 X
#define PROFILEIMG_Y               32 * _2X                 // 프로필 이미지 Y
#define STAGEINFO_Y                200 * _2X                // 스테이지 정보 Y
#define CONTROLMARKGAP_X           4 * _2X                  // 컨트롤 마크 X 간격

// ---
#define BG_COLS                    10             // 배경 열 수
#define BG_ZOOM                    (0.5f)                   // 배경 줌
#define BG_SCROLL_SPD_X            (1)                      // 배경 스크롤 X 속도
#define BG_SCROLL_SPD_Y            (1)                      // 배경 스크롤 Y 속도
#define BG_SIL_W                   6              // 배경 실루엣 너비
#define BG_SIL_H                   6              // 배경 실루엣 높이
#define BG_SIL_N                   (BG_SIL_W * BG_SIL_H)    // 배경 실루엣 총 수

// ---
#define FX_ELECTRIC_WEAK_IMG       0              // 전기 약 이미지
#define FX_ELECTRIC_MID_IMG        1              // 전기 중 이미지
#define FX_ELECTRIC_STRONG_IMG     2              // 전기 강 이미지
#define FX_FLASH_WEAK_IMG          3              // 플래시 약 이미지
#define FX_FLASH_STRONG_IMG        4              // 플래시 강 이미지
#define FX_ELECTRIC_FRAMES         8              // 전기 프레임 수
#define FX_ELECTRIC_H              64             // 전기 높이
