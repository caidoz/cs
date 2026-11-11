#pragma once

#ifndef _DEF_BOARD_H_
#define _DEF_BOARD_H_

//==========================================================================
// 룰렛 × 합성 턴제 전투 — 판의 상수
//
// docs/기획_룰렛_합성.md §16 "확정 규칙 한 장" 이 기준이다. 숫자를 고치려면
// 그 표를 먼저 고치고 여기로 옮긴다. 판 크기는 "룰렛 횟수 × 3 + 여유 6" 으로
// 룰렛 횟수에 묶여 있다(§1-1). 한쪽만 바꾸면 10턴을 다 못 모은다.
//==========================================================================
enum {
	BOARD_W = 6,
	BOARD_H = 6,
	BOARD_CELLS = BOARD_W * BOARD_H,

	BOARD_LINEAGES = 3,		//런 시작 슬롯이 정하는 계열 수
	BOARD_REELS = 3,		//룰렛 릴 수 = 한 번에 나오는 블록 수
	BOARD_SPINS = 10,		//적 하나당 룰렛 횟수
	BOARD_TRAY = BOARD_REELS,

	//---- 릴에서 장비가 나오는 비율(%) ----
	//
	//전에는 비율이 뽑기 운에 끌려다녔다. 릴 세 줄의 계열을 먼저 뽑고
	//(choose) 그 셋에서 고르게 돌리는 식이라, 계열 뽑기가 어떻게 나왔는지에
	//따라 장비가 1/3 이 되기도 2/3 이 되기도 했다.
	//
	//세 줄에 장비가 하나도 안 걸리는 판에서는 아무리 돌려도 장비가 안
	//나온다 - 합성 트리가 통째로 멈춘다.
	//
	//한 칸이 나올 때마다 이 확률로 "장비냐 동료냐" 를 먼저 정하고, 그다음
	//그 쪽 계열 중에서 고른다. 한쪽이 릴에 없으면 반대쪽으로 간다.
	BOARD_GEAR_PCT = 70,

	//---- 서는 맛 ----
	//
	//릴이 그냥 멈추면 "바뀌었다" 로만 보이고 슬롯머신으로 안 읽힌다.
	//마지막에 조금 넘어갔다 되돌아오고, 선 줄이 한 번 번쩍인다.
	REEL_OVERSHOOT = 14,		//넘어갔다 오는 픽셀(_2X 아닌 scale 배)
	REEL_STOP_FLASH = 8,		//선 뒤 테두리가 남는 프레임

	BLOCK_LV_MAX = 6,		//6단 = 성급(★1~★6). 크기 1×1·1×2·2×2·2×3·3×3·3×4 (2026-11-09)
	BOARD_MAX_BLOCKS = BOARD_CELLS,

	RUN_LIVES_BASE = 3,		//갑옷 없을 때의 목숨
	ENEMY_LIFE_COST_NORMAL = 1,
	ENEMY_LIFE_COST_BOSS = 2,
};

//계열의 종류. 동료 계열의 id 는 역할군(CrewRole), 장비면 id 는 쓰지 않는다.
//블록이 어떤 동료인지는 블록이 따로 든다 — 합성 결과가 그 역할·★ 안에서 무작위이기 때문.
enum LineageKind {
	LINEAGE_CREW = 0,
	LINEAGE_SWORD,		//히어로 평타 / 궁극기
	LINEAGE_ARMOR,		//보호 / 적 턴 삭제
	LINEAGE_NECK,		//하트 / 룰렛 횟수
	LINEAGE_KIND_COUNT,
};

//역할군 4. 64명이 역할 × ★ 로 고르게 깔려 있어(지휘 17·포격 15·지원 17·공격 15) 이것이 곧 합성 트리다.
enum BoardCrewRole {	//Func_Draw.h 의 CrewRole(CREW_ROLE_*) 과 같은 순서. 값이 같아야 한다
	ROLE_COMMANDER = 0,	//지휘
	ROLE_ARTILLERY,		//포격 (★5 가 끝 — ★6 이 없다)
	ROLE_SUPPORT,		//지원
	ROLE_STRIKER,		//공격
	ROLE_COUNT,
};

//동료 특성 6종(§14-2). 동료 하나에 하나. 장비 계열은 TRAIT_NONE.
enum BlockTrait {
	TRAIT_NONE = 0,
	TRAIT_EXPOSE,		//표식: 이후 모든 타격 증폭
	TRAIT_INSPIRE,		//고무: 바로 다음 블록 배수
	TRAIT_STRIKE,		//강타: 자기 피해 증폭
	TRAIT_VOLLEY,		//연타: 탄 수. 적이 여럿일 때 전부 맞음
	TRAIT_CHILL,		//빙결: Lv3+ 적 턴 삭제, Lv1·2 적 공격 절반
	TRAIT_BURN,			//지속: 다음 교환 시작에 또 피해
	TRAIT_COUNT,
};

#endif
