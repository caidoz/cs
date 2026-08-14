#pragma once

#ifndef _DEF_TUTORIAL_H_
#define _DEF_TUTORIAL_H_
typedef enum _tutorial {
	TUTORIAL_MOVE_ATTACK = 0,//이동 및 공격
	TUTORIAL_SELECT_SKILL,//레벨 업 및 스킬선택
	TUTORIAL_USE_SKILL,//스킬사용
	TUTORIAL_HERO,//영웅
	TUTORIAL_SOLDIER,//용병
	TUTORIAL_AWARDS,//시상식

	TUTORIAL_INVENTORY,//인벤토리에서 아이템 선택하기
	TUTORIAL_SELLITEM,//아이템 판매하기
	TUTORIAL_EQUIP,//장비되어 있는 무기 선택하기
	TUTORIAL_UPGRADEBUTTON,//강화하기 버튼 누르기
	TUTORIAL_UPGRADE,//업그레이드하기
	TUTORIAL_MAKEITEM,//아이템 제작하기

	TUTORIAL_PASS,//패스메뉴 들어가기
	TUTORIAL_PASSREWARD,//패스메뉴 보상받기

	TUTORIAL_SOLDIERMENU,//솔저메뉴에 진입시
	TUTORIAL_SOLDIERSELECT,//용병 선택하기
	TUTORIAL_SOLDIERSTART,//전투 들어가기

	TUTORIAL_STUN_HOLY,//스턴 설명 및 성 속성
	TUTORIAL_POISON_THUNDER,//중독과 번개 속성
	TUTORIAL_BLIND_FLAME,//블라인드 설명 및 화염 속성
	TUTORIAL_SLOW_ICE,//슬로우 설명 및 냉기 속성
	TUTORIAL_CURSE_DARK,//저주와 암흑 속성

	TOTAL_TUTORIAL,
} TUTORIAL;

//튜토리얼에서 동료를 넣도록 안내하는 슬롯 번호.
//0번은 세바스찬이 이미 차지하고 있어 두 번째 자리를 안내한다.
#define TUTORIAL_CREW_SLOT		1

//동료 상세보기에서 장착을 누른 뒤부터 성 위에 등장하는 것까지의 안내 단계.
//슬롯 고르기/카드 고르기(GetTutorialCrewSlotTouchFunc, GetTutorialCrewCardTouchFunc)는
//tutorialCrewGuide로 돌고, 그 다음부터를 이 단계값이 이어받는다.
typedef enum _tutorialCrewStep {
	TUTORIAL_CREWSTEP_NONE = 0,	//안내 없음
	TUTORIAL_CREWSTEP_EQUIP,	//상세보기의 장착 버튼을 눌러야 한다
	TUTORIAL_CREWSTEP_SLOTSHOW,	//편성칸에 내려앉는 것을 보여주는 동안
	TUTORIAL_CREWSTEP_CLOSE,	//왼쪽 위 뒤로가기를 눌러야 한다
	TUTORIAL_CREWSTEP_CASTLE,	//성 위 등장 + 룰렛 슬롯 등장을 보여주는 동안
} TUTORIALCREWSTEP;

//각 단계에서 자동으로 다음으로 넘어가기까지의 프레임.
#define TUTORIAL_CREWSTEP_SLOTSHOW_FRAME	(FPS * 2)
#define TUTORIAL_CREWSTEP_CASTLE_FRAME		(FPS * 3)

//튜토리얼에서 장착을 안내하는 장비 슬롯. 두번째 상자에서 나오는 기본 갑옷 자리다.
#define TUTORIAL_EQUIP_SLOT		EQUIP_ARMOR

//장비 장착 안내 단계. 동료 편성 안내와 같은 흐름이지만, 편성표가 아니라 주인공이 직접
//입는 것이라 마지막에 성 위의 주인공을 비춘다.
typedef enum _tutorialEquipStep {
	TUTORIAL_EQUIPSTEP_NONE = 0,	//안내 없음
	TUTORIAL_EQUIPSTEP_SLOT,		//갑옷 슬롯을 골라야 한다
	TUTORIAL_EQUIPSTEP_CARD,		//새 갑옷 카드를 눌러 상세보기로 들어가야 한다
	TUTORIAL_EQUIPSTEP_EQUIP,		//상세보기의 장착 버튼을 눌러야 한다
	TUTORIAL_EQUIPSTEP_SLOTSHOW,	//슬롯에 들어간 것을 보여주는 동안
	TUTORIAL_EQUIPSTEP_CLOSE,		//왼쪽 위 뒤로가기를 눌러야 한다
	TUTORIAL_EQUIPSTEP_HERO,		//성 위 주인공이 갈아입은 것을 보여주는 동안
} TUTORIALEQUIPSTEP;

#define TUTORIAL_EQUIPSTEP_SLOTSHOW_FRAME	(FPS * 2)
#define TUTORIAL_EQUIPSTEP_HERO_FRAME		(FPS * 3)

//튜토리얼 4연전이 쓰는 wave[] 행. 표 앞쪽 0~3번을 순서대로 그대로 쓴다.
//튜토리얼 전용 행을 따로 만들지 않는다 - 표 순서와 실제 진행이 어긋나면 나중에 읽기 어렵다.
//튜토리얼이 끝나면 4번 행부터 일반 진행이 이어진다.
#define TUTORIAL_WAVEIDX_1ST				0	//SNAIL		첫 몬스터
#define TUTORIAL_WAVEIDX_2ND				1	//SNAIL		동료 편성을 배운 뒤
#define TUTORIAL_WAVEIDX_3RD				2	//TREE		하트 3배 베팅 대상
#define TUTORIAL_WAVEIDX_BOSS				3	//SNAIL_GREEN	마무리 보스(2배 크기)

//튜토리얼 마무리 보스(2배 크기 초록 달팽이)의 체력.
//동료 3명이 겹친 강한 공격 한 방에 죽어야 하므로 넉넉하지 않게 잡는다.
#define TUTORIAL_BOSS_HP					300

//마무리 보스를 몇 배로 키울지.
#define TUTORIAL_BOSS_ZOOM					2.0f

//룰렛 개방 반짝임이 도는 시간.
#define ROULETTE_GLOW_FRAME					(FPS * 2)

#endif
