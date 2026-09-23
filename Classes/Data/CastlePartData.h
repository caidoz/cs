#pragma once

//======================================================================
// 성 파츠
//
// 성 단계와 단계 사이를 메우는 자리다. 스테이지만 밀면 성이 저절로
// 오르면 판에서 번 골드가 갈 데가 없다. 파츠에 골드를 넣어 올리고,
// 목표치만큼 올리면 증축(다음 성)으로 넘어간다.
//
// ---- 왜 "전부 만렙" 이 아니라 "합계" 인가 ----
//
// 전부 올려야 넘어가면 순서만 고르게 되고 모두 같은 성을 갖는다. 합계로
// 두면 "성벽에 몰아주고 빨리 넘어갈까, 고루 올릴까" 가 생긴다. 못 올린
// 것은 그 성을 떠나면 다시 못 올리므로, 무엇을 포기했는가가 그 회차의
// 성격이 된다.
//
// 목표치는 전체의 3/4 이다(CastleGoalStep).
//
// ---- 파츠는 올릴 때마다 바로 값을 한다 ----
//
// 증축까지 기다리게 하면 넣은 보람이 없어 아무도 안 넣는다. 효과는
// effectType 으로 갈라 두었고, 실제로 쓰는 쪽에서 그 종류를 찾아 더한다.
//======================================================================

#ifndef _CASTLE_PART_DATA_H_
#define _CASTLE_PART_DATA_H_

enum {
	CASTLE_PART_MAX = 4,	//한 성에 들어가는 요소의 상한
	CASTLE_STAGE_CNT = 10,	//성 단계(그림 castle0 ~ castle9 와 짝)
};

//파츠가 무엇을 올리는가. 쓰는 쪽이 이 종류로 찾아 쓴다.
enum {
	CPE_NONE = 0,
	CPE_HP_PCT,			//히어로 최대 체력 +%
	CPE_DEF,			//방어 +
	CPE_DMG_TAKEN_PCT,	//받는 피해 -%
	CPE_BAG,			//가방 칸 +
	CPE_CREWSLOT,		//동료 편성 칸 +
	CPE_STARTGOLD,		//판 시작 골드 +
	CPE_GOLD_PCT,		//골드 획득 +%
	CPE_CREW_DMG_PCT,	//동료 공격 +%
	CPE_CREW_HP_PCT,	//동료 체력 +%
	CPE_SHOP_PRICE_PCT,	//룰렛 값 -%
	CPE_REROLL_FREE,	//무료 다시 뽑기 +
	CPE_GEAR_GRADE,		//나오는 장비 등급 가중치 +
	CPE_INCOME_PCT,		//수금량 +%
	CPE_INCOME_CAP_PCT,	//금고 상한 +%
	CPE_ALLSTAT_PCT,	//모든 능력치 +%
	CPE_MERGE_BONUS,	//합성 보너스
	CPE_FOE_PREVIEW,	//적 장비 미리보기
};

struct CastlePartInfo {
	const char* name;
	const char* effect;	//한 줄 설명. %d 자리에 지금 효과량이 들어간다
	int effectType;
	int maxLv;
	int costBase;		//1레벨 값
	int costAdd;		//레벨 하나마다 더 드는 값
	int bonusPerLv;		//레벨 하나가 주는 양
};

struct CastleStageInfo {
	const char* title;	//그 성의 이름
	int cell;			//가방 칸(컨셉 그림의 숫자)
	int partCnt;
	CastlePartInfo part[CASTLE_PART_MAX];
};

//----------------------------------------------------------------------
// 성 열 단계
//
// 초반은 체력과 칸처럼 바로 체감되는 것, 후반은 확률과 배수처럼 빌드를
// 바꾸는 것이다. 한 성 안의 요소끼리는 서로 다른 축을 건드린다 - 같은
// 것을 세 번 올리게 하면 고를 이유가 없다.
//----------------------------------------------------------------------
static const CastleStageInfo castleStage[CASTLE_STAGE_CNT] = {
	{ "기초 요새", 6, 3, {
		{ "성문",     "최대 체력 +%d%%",   CPE_HP_PCT,     2,  200, 150,  5 },
		{ "울타리",   "방어 +%d",          CPE_DEF,        2,  180, 140,  3 },
		{ "횃불",     "판 시작 골드 +%d",  CPE_STARTGOLD,  2,  220, 160, 30 },
	}},
	{ "작은 성채", 10, 3, {
		{ "막사",     "편성 칸 +%d",       CPE_CREWSLOT,   2,  400, 300,  1 },
		{ "우물",     "최대 체력 +%d%%",   CPE_HP_PCT,     2,  260, 200,  5 },
		{ "창고 터",  "가방 칸 +%d",       CPE_BAG,        2,  300, 220,  4 },
	}},
	{ "병영의 시작", 14, 3, {
		{ "병영",     "편성 칸 +%d",       CPE_CREWSLOT,   3,  500, 380,  1 },
		{ "훈련장",   "동료 공격 +%d%%",   CPE_CREW_DMG_PCT, 3, 420, 320,  5 },
		{ "무기고",   "장비 등급 +%d",     CPE_GEAR_GRADE, 3,  460, 340,  1 },
	}},
	{ "수비 강화", 18, 3, {
		{ "방어 타워", "방어 +%d",         CPE_DEF,        3,  520, 380,  5 },
		{ "성벽 보강", "최대 체력 +%d%%",  CPE_HP_PCT,     3,  560, 400, 10 },
		{ "성문 강화", "받는 피해 -%d%%",  CPE_DMG_TAKEN_PCT, 3, 600, 430, 3 },
	}},
	{ "왕국의 기틀", 24, 3, {
		{ "집무실",   "수금량 +%d%%",      CPE_INCOME_PCT, 4,  700, 500, 20 },
		{ "식당",     "동료 체력 +%d%%",   CPE_CREW_HP_PCT, 4, 650, 480, 10 },
		{ "깃발",     "골드 획득 +%d%%",   CPE_GOLD_PCT,   4,  720, 520, 10 },
	}},
	{ "상업의 발전", 32, 3, {
		{ "상점",     "룰렛 값 -%d%%",     CPE_SHOP_PRICE_PCT, 4, 800, 560, 10 },
		{ "창고",     "가방 칸 +%d",       CPE_BAG,        4,  760, 540,  8 },
		{ "생산 시설", "금고 상한 +%d%%",  CPE_INCOME_CAP_PCT, 4, 840, 580, 50 },
	}},
	{ "마법의 탑", 40, 4, {
		{ "연구실",   "장비 등급 +%d",     CPE_GEAR_GRADE, 4, 1000, 700,  1 },
		{ "마법 탑",  "무료 다시 뽑기 +%d", CPE_REROLL_FREE, 4, 1100, 760, 1 },
		{ "소환진",   "편성 칸 +%d",       CPE_CREWSLOT,   4, 1200, 820,  1 },
		{ "마력로",   "모든 능력치 +%d%%", CPE_ALLSTAT_PCT, 4, 1300, 880,  3 },
	}},
	{ "왕국의 심장", 48, 4, {
		{ "왕좌",     "모든 능력치 +%d%%", CPE_ALLSTAT_PCT, 4, 1500, 980,  5 },
		{ "의회실",   "수금량 +%d%%",      CPE_INCOME_PCT, 4, 1400, 940, 30 },
		{ "상징",     "합성 보너스 +%d%%", CPE_MERGE_BONUS, 4, 1600, 1020, 5 },
		{ "보물창고", "가방 칸 +%d",       CPE_BAG,        4, 1450, 960,  8 },
	}},
	{ "천공의 요새", 56, 4, {
		{ "공중 정원", "최대 체력 +%d%%",  CPE_HP_PCT,     5, 1800, 1100, 15 },
		{ "전망대",   "적 장비 미리보기 %d", CPE_FOE_PREVIEW, 5, 1700, 1050, 1 },
		{ "특수 시설", "가방 칸 +%d",      CPE_BAG,        5, 1900, 1150, 10 },
		{ "성령비",   "골드 획득 +%d%%",   CPE_GOLD_PCT,   5, 1750, 1080, 15 },
	}},
	{ "전설의 왕국", 60, 4, {
		{ "대전당",   "모든 능력치 +%d%%", CPE_ALLSTAT_PCT, 5, 2400, 1400, 10 },
		{ "보물고",   "가방 칸 +%d",       CPE_BAG,        5, 2200, 1300, 12 },
		{ "왕국의 문장", "편성 칸 +%d",    CPE_CREWSLOT,   5, 2600, 1500,  2 },
		{ "성좌",     "장비 등급 +%d",     CPE_GEAR_GRADE, 5, 2500, 1450,  2 },
	}},
};

//성 번호를 컨셉 단계로. 성 표가 열 개보다 많아도 마지막 단계를 쓴다.
inline int CastleStageIdx(int castle)
{
	if (castle < 0)
		return 0;

	return castle < CASTLE_STAGE_CNT ? castle : CASTLE_STAGE_CNT - 1;
}

inline const CastleStageInfo* CastleStageAt(int castle)
{
	return &castleStage[CastleStageIdx(castle)];
}

inline int CastlePartCnt(int castle)
{
	return CastleStageAt(castle)->partCnt;
}

inline const CastlePartInfo* CastlePartAt(int castle, int part)
{
	const CastleStageInfo* s = CastleStageAt(castle);

	if (part < 0 || part >= s->partCnt)
		return 0;

	return &s->part[part];
}

//이 성에서 올릴 수 있는 단의 총합.
inline int CastlePartTotal(int castle)
{
	const CastleStageInfo* s = CastleStageAt(castle);
	int sum = 0;

	for (int i = 0; i < s->partCnt; i++)
		sum += s->part[i].maxLv;

	return sum;
}

//증축에 필요한 단. 전체의 3/4 이다(올림).
inline int CastleGoalStep(int castle)
{
	return (CastlePartTotal(castle) * 3 + 3) / 4;
}

//레벨 하나를 더 올리는 데 드는 골드. 성마다 표에 적힌 값이라
//따로 배수를 곱하지 않는다 - 뒤 성일수록 표의 값 자체가 크다.
inline int CastlePartCost(int castle, int part, int lv)
{
	const CastlePartInfo* p = CastlePartAt(castle, part);

	if (!p)
		return 0;

	return p->costBase + p->costAdd * lv;
}

//지금 레벨이 주는 양.
inline int CastlePartBonus(int castle, int part, int lv)
{
	const CastlePartInfo* p = CastlePartAt(castle, part);

	return p ? p->bonusPerLv * lv : 0;
}

//---- 증축 조건 ----
//
//파츠 합계만으로는 부족하다. 골드만 부으면 넘어가는 성장이 되기 때문이다.
//판을 깨고 동료를 모으는 것도 같이 본다.
inline int CastleNeedStage(int castle)	{ return (castle + 1) * 3; }
inline int CastleNeedCrew(int castle)	{ return 2 + castle; }

//즉시 완성 값. 남은 골드를 이 비율로 캐시로 바꾼다(올림).
#define CASTLE_CASH_PER_GOLD	1000

#endif
