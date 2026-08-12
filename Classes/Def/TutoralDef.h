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

#endif
