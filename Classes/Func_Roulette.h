#pragma once

#ifndef _FUNC_ROULETTE_H_
#define _FUNC_ROULETTE_H_

// Utility 함수들
void GetMarkHeadPos(int obj, int* outX, int* outY);
void GetMarkHeadPosAt(int footX, int footY, float zoom, int* outX, int* outY);
void MoveControlMarkTo(int ownerObj, int skillIdx, int hx, int hy);
void MoveControlMarkToObj(int ownerObj, int skillIdx, int destObj);
void MoveControlMarkToSpot(int ownerObj, int skillIdx, int footX, int footY);
int GetUnitScore(OBJECT* pObj);
void DecideRouletteResult();
void InitRouletteJump(void);
void RouletteAttackStart(void);
int GetSameRouletteCnt(int objIdx);
int UpgradeSkillIdx(int reelIdx, int count);
//------------------------------------------------------------
// 룰렛 미리보기(애니메이션 없음)
// slotCrewIdx : 슬롯에 들어갈 동료 offset
// totalCrewCount : 현재 보유 동료 수
//------------------------------------------------------------
void RouletteDrawSimple3Slots(
	int x,
	int y,
	float zoom,
	const int slotCrewIdx[3],
	int totalCrewCount);

void RouletteDraw(int x, int y, float zoom);

// Crew 관련
int GetCrewIdxFromType(int);


#endif