#pragma once
#include "../Def.h"

#ifndef _CASTLE_DATA_H_
#define _CASTLE_DATA_H_

extern const int* castleOrder;
enum { castleOrder_COUNT = 19 };

extern const int* castleBoxColor;
enum { castleBoxColor_COUNT = 19 };

extern const long long* castleBoxGold;
enum { castleBoxGold_COUNT = 19 };

extern const int* castleStarLimit;
enum { castleStarLimit_COUNT = 19 };

extern const int* setHeroPos;
enum { setHeroPos_COUNT = 114 };

extern const int* setEnemyPos;
enum { setEnemyPos_COUNT = 114 };

//앞에 세개는 히어로
//나머지는 
extern const int* castleCrewPosition;
enum { castleCrewPosition_COUNT = 228 };

// 로비 동료의 시작점(x, y)과 자유 이동 범위(width, height).
// 성마다 한 줄씩 있으므로 로비 배치를 손볼 때 이 표만 조절하면 된다.
extern const int* lobbyCrewArea;
enum { lobbyCrewArea_COUNT = TOTALCASTLE * 4 };

// 성의 가방 칸. castleGridCellStart[성] 부터 castleGridCellCnt[성] 개의
// {열, 행} 쌍이다(CastleData.cpp 의 표 설명 참고).
extern const int castleGridCellCnt[TOTALCASTLE];
extern const int castleGridCellStart[TOTALCASTLE];
extern const signed char* castleGridCell;
enum { castleGridCell_COUNT = 726 };	//배열 길이. 칸 수(363)의 두 배다
#endif
