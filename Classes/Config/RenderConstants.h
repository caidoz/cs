#pragma once
// =============================================================
// RENDER CONSTANTS
// 실제 사용되는 렌더링 상수만 유지
// =============================================================

// 기본 줌 상수
#define HEROZOOM                   1.5f           // 히어로 줌
#define CREWZOOM                   1.5f           // 크루 줌
#define MONSTERZOOM                1.5f           // 몬스터 줌
#define BOSSZOOM                   2.5f           // 보스 줌
#define LOBBYZOOM                  1.2f           // 로비 줌
#define BATTLEZOOM                 1.5f          // 배틀 줌
#define SUMMONZOOM                 1.5f           // 소환 줌
#define DROPITEMZOOM               2.0f           // 드롭 아이템 줌
#define HOUSEZOOM                  1.25f          // 하우스 줌
#define HOUSEPLAYERZOOM            1.0f           // 하우스 플레이어 줌
#define BOXZOOM                    2.5f           // 박스 줌
#define BOXCASTLEZOOM              0.25f           // 박스 하우스 줌

// ---
#define REWARDICONZOOM             1.5f           // 보상 아이콘 줌
#define HEROCASTLEZOOM             1.5f           // 영웅 성 줌
#define CREWCASTLEZOOM             1.2f           // 크루 성 줌
#define HITMARKZOOM                0.5f           // 히트마크 줌
#define DIORAMAZOOM                0.77f          // 디오라마 줌
#define DIORAMAZOOM_BATTLE         0.77f//1.0f//          // 디오라마 배틀 줌
#define DIORAMAZOOM_REMAINDER      1.5f           // 디오라마 나머지 줌
#define BATTLEWEAPONZOOM           6.0f           // 배틀 무기 줌
// --- 버튼 감촉
// 누르는 순간 즉시 눌러 들어가고(지연 0), 떼면 살짝 튀었다가 제자리로 온다.
// 지연을 넣어서 쫀득한 것이 아니라, 누른 티가 바로 나고 뗀 결과가 눈에
// 보인 뒤에 화면이 바뀌어서 쫀득한 것이다. 60프레임 기준이다.
#define BUTTON_DOWNSCALE           0.94f          // 누르고 있는 동안의 배율
#define BUTTON_POPSCALE            1.06f          // 뗀 직후 튀어오르는 배율
#define BUTTON_POPFRAME            10             // 튀었다가 돌아오는 프레임
#define BUTTON_HIGHLIGHTALPHA      12             // 눌린 터치영역을 덮는 밝기(32가 불투명)

// --- 보상 재화 마크(하트/골드)가 바로 날아갈 때의 배율
// 값이 클수록 크게 보여준다. 1000부터 자릿수가 하나 늘 때마다 한 단계씩
// 키우고 상한에서 멈춘다. 상한이 없으면 큰 보상에서 아이콘이 화면을 덮는다.
#define CURRENCYMARK_ZOOMBASE      0.87f          // 기본 배율
#define CURRENCYMARK_ZOOMSTEP      0.10f          // 자릿수 한 칸당 가산
#define CURRENCYMARK_ZOOMMAX       1.33f          // 배율 상한

#define SUMMONHEARTZOOM            0.7f           // 소환 연출로 덧그리는 마왕의 심장 배율
#define HITCOUNTZOOM               1.0f           // 히트 카운트 줌
#define RAIDGOLDBARZOOM            2.5f           // 레이드 골드바 줌
#define BATTLEGOLDALPHAZOOM        2.2f           // 배틀 골드 알파 줌
#define BATTLETEXTZOOM             1.5f           // 배틀 텍스트 줌
#define PLAYERHEADZOOM             1              // 플레이어 헤드 줌
#define ALLHEADZOOM                2              // 전체 헤드 줌

// ---
#define CAMERAPER_MULTIPLE         2              // 카메라 배율 분자
#define CAMERAPER_DIVIDE           5              // 카메라 배율 분모

// --- 공격 줌 (공격을 시작하면 공격자를 중심으로 월드만 확대)
// 공격이 진행되는 내내 물고 있다가 공격이 끝나면 놓는다. 유지 프레임이
// 따로 없는 이유다. 들어갈 때와 나올 때의 속도는 다르게 둔다.
// 60프레임 기준이다.
#define HITZOOMMAX                 1.5f           // 공격 중 월드 배율
#define HITZOOMINFRAME             10             // 최대 배율까지 올라가는 프레임
#define HITZOOMOUTFRAME            16             // 원래 배율로 돌아가는 프레임
#define HITZOOMMAXHOLD             240            // 물고 있는 최대 프레임(안전장치)

// --- 연출 줌 (데모의 FOCUS처럼 특정 대상을 잠깐 당겨 보여줄 때)
// 공격 줌과 같은 변환(hitZoom)을 쓴다. 두 개를 따로 두면 서로 덮어써서
// 배율이 튄다. 공격 줌이 걸려 있으면 그쪽이 이긴다.
// 연출이므로 공격 줌보다 약하게, 느리게 들어가고 나온다.
#define FOCUSZOOMMAX               1.35f          // 포커스 대상 확대 배율
#define FOCUSZOOMINFRAME           16             // 최대 배율까지 올라가는 프레임
#define FOCUSZOOMHOLD              (FPS * 4 / 5)  // 당긴 채로 물고 있는 프레임
#define FOCUSZOOMCOOL              (FPS * 3 / 2)  // 다음 연출을 받기까지의 쿨다운
#define FOCUSZOOM_MAXREQ           16             // 한 번에 쌓아둘 수 있는 요청 수
#define FOCUSZOOM_REQTTL           (FPS * 3)      // 요청이 살아 있는 프레임(넘으면 버린다)

// 연출 줌 우선순위. 되돌릴 수 없고 한 번뿐인 것일수록 높다.
// 일반 몬스터 소환처럼 수십 번 반복되는 것은 놓쳐도 되므로 가장 낮다.
#define FOCUSPRI_CREWNEW           50             // 동료 신규 등장
#define FOCUSPRI_EQUIP             40             // 장비 장착/교체
#define FOCUSPRI_CREWCHANGE        35             // 동료 교체
#define FOCUSPRI_BOSSSUMMON        30             // 보스/특수 몬스터 소환
#define FOCUSPRI_BOXDROP           20             // 상자 드랍
#define FOCUSPRI_SUMMON            10             // 일반 몬스터 소환

// ---
#define GOLDBARZOOM                0.5f           // 골드바 줌
#define CROWNBARZOOM               0.5f           // 왕관바 줌
#define BAR_GOLD_ZOOM              1.0f           // 골드 바 줌
#define BAR_CROWN_ZOOM             1.0f           // 왕관 바 줌
#define BAR_HAMMER_ZOOM            1.0f           // 망치 바 줌
#define BAR_SHIELD_ZOOM            1.0f           // 방패 바 줌
#define BAR_BOX_ZOOM               1.1f           // 박스 바 줌
#define BAR_PLAYERHP_ZOOM          1.0f           // 플레이어 HP 바 줌
#define BAR_BOSSHP_ZOOM            0.45f           // 보스 HP 바 줌
#define BAR_COIN_ZOOM              2.0f           // 코인 바 줌
#define BAR_ITEM_ZOOM              2.0f           // 아이템 바 줌
#define BAR_HERO_ZOOM              0.95f           // 영웅 바 줌
#define BAR_CREW_ZOOM              0.95f           // 크루 바 줌
#define BAR_HEART_ZOOM             1.0f           // 하트 바 줌
#define BAR_ROULETTE_ZOOM             0.5f           // 하트 바 줌
#define BAR_HEARTBET_ZOOM             1.6f           // 하트 바 줌
#define BAR_PLAY_ZOOM             1.8f           // 하트 바 줌
#define BAR_CONTROLER_ZOOM			1.5f		//공격버튼
#define BAR_JUMP_ZOOM			1.8f		//공격버튼
#define BAR_BATTLECOIN_ZOOM        1.0f          // 배틀 코인 바 줌
#define BAR_MEDAL_ZOOM             1.0f           // 메달 바 줌
#define BAR_ENEMYUSER_ZOOM         1.0f           // 적 유저 바 줌
#define BAR_ENEMYUSER_BOX_ZOOM     1.0f           // 적 유저 박스 바 줌
#define BAR_MAINSHOP_ZOOM          0.95f           // 메인샵 바 줌
#define BAR_DAILYQUEST_ZOOM        1.0f           // 일일퀘스트 바 줌
#define BAR_CREWUPGRADE_ZOOM       1.0f           // 크루 업그레이드 바 줌
#define BAR_COLLECTIONS_ZOOM       0.95f           // 컬렉션 바 줌
#define BAR_FRIENDS_ZOOM           1.0f           // 친구 바 줌
#define BAR_QUEST_ZOOM             1.0f           // 퀘스트 바 줌
#define BAR_RAIDGOLD_ZOOM          1.2f           // 레이드 골드 바 줌
#define BAR_RAIDCOIN_ZOOM          1.2f           // 레이드 코인 바 줌
#define BAR_COMBATPOWERALL_ZOOM    1.0f           // 전투력 전체 바 줌
#define BAR_COMBATPOWER_ZOOM       1.0f           // 전투력 바 줌
#define BAR_STAR_ZOOM              1.0f           // 별 바 줌
#define BAR_STAGEPROGRESS_ZOOM     1.0f           // 스테이지 진행 바 줌
#define BAR_REMAINEDTURN_ZOOM	3.0f           // 스테이지 진행 바 줌
#define BAR_INVENTORY_ZOOM         0.6f           // 인벤토리 바 줌
#define BAR_SKILL_ZOOM             1.0f           // 스킬 바 줌

// ---
#define EQUIPZOOM                  2.0f           // 장비 줌
#define SKILLICONZOOM              2.0f           // 스킬 아이콘 줌
#define IMGTEXTZOOM                2.0f           // 이미지 텍스트 줌
#define DMGNUMZOOM                 0.5f           // 데미지 숫자 줌
#define XNUMZOOM                   1.4f           // X 숫자 줌
#define ENEMYICONZOOM              0.5f           // 적 아이콘 줌
#define CREWBULLETZOOM				0.6f
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
