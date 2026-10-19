#pragma once

#ifndef _FUNC_ROULETTE_H_
#define _FUNC_ROULETTE_H_

// Utility 함수들
void GetMarkHeadPos(int obj, int* outX, int* outY);
void GetMarkHeadPosAt(int footX, int footY, float zoom, int* outX, int* outY);
void MoveControlMarkTo(int ownerObj, int skillIdx, int hx, int hy);
void MoveControlMarkToObj(int ownerObj, int skillIdx, int destObj);
void MoveControlMarkToSpot(int ownerObj, int skillIdx, int footX, int footY);
int GetPersistentBuffBySkill(int skillIdx);
void MoveControlMarkToBuffStack(int ownerObj, int skillIdx);
void UpdatePersistentBuffControlMarkStack(void);
void UpdateHeroSkillControlMarkStack(void);
int GetUnitScore(OBJECT* pObj);
void DecideRouletteResult();
void InitRouletteJump(void);
void RouletteAttackStart(void);
int GetSameRouletteCnt(int objIdx);
int GetRouletteResultSkillForObj(int obj);
int GetDemoSummonEnemyForSlot(int slot);
int GetDemoSummonEnemyForOwner(int ownerObj);
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

//---- PVP 우주맵 ----
//
//룰렛 PVP 당첨 연출이 쓰던 두 화면이다. 좌상단 PVP 버튼도 같은 화면으로
//들어가야 "어느 쪽으로 들어왔든 같은 우주" 로 읽힌다.
//
//    localFrame  이 화면이 시작한 뒤 지난 프레임
//    buildFrame  다 차오르는 데 걸리는 프레임
void DrawPvpCosmicCastleMap(int localFrame, int buildFrame);
void DrawPvpSelectedCastles(int localFrame, int totalFrame);
bool PvpEntranceIconReviewCheck(int myLevel,int foeLevel);

// Crew 관련
int GetCrewIdxFromType(int);


#endif
