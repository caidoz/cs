#pragma once
#include "../Def.h"

#ifndef _ALPHA_DATA_H_
#define _ALPHA_DATA_H_

extern const unsigned char* demoAlpha;
enum { demoAlpha_COUNT = 50 };

//ALPHA_* 인덱스와 1:1로 대응하는 완성 문자열 테이블.
extern const char* const* alphaText;
enum { alphaText_COUNT = TOTAL_ALPHA_TEXT };


extern const unsigned short* alphaX;
enum { alphaX_COUNT = 296 };

extern const signed short* alpha2;
enum { alpha2_COUNT = 222 };

extern const unsigned short* goldAlphaInfo;
enum { goldAlphaInfo_COUNT = 444 };

extern const unsigned short* alphaY;
enum { alphaY_COUNT = 8 };
#endif
