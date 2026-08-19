#pragma once
#include "../Def.h"

#ifndef _DATA_OBJECT_H_
#define _DATA_OBJECT_H_

extern const signed short* objMI;
enum { objMI_COUNT = 5408 };

extern const signed short* levelUpMI;
enum { levelUpMI_COUNT = 244 };

//core.h는 반드시 signed char로 들어가야 함
extern const signed short* objectData;
enum { objectData_COUNT = 423 };

extern const signed char* boxNeutralAnimation;
enum { boxNeutralAnimation_COUNT = 4 };


extern const signed char* boxOpenAnimation;
enum { boxOpenAnimation_COUNT = 20 };

extern const float* boxOpenItemFrameInfo;
enum { boxOpenItemFrameInfo_COUNT = 378 };
#endif