#pragma once
#include "../Def.h"

#ifndef _CASTLE_DATA_H_
#define _CASTLE_DATA_H_

extern const int* castleOrder;
enum { castleOrder_COUNT = 19 };

extern const float* castleBoxZoom;
enum { castleBoxZoom_COUNT = 19 };

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
#endif