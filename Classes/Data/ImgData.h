#pragma once

#ifndef _DATA_IMG_H_
#define _DATA_IMG_H_

#include "../Def.h"
#include "../Cmf.h"

extern const unsigned short* imgArray;
enum { imgArray_COUNT = 340 };

extern const unsigned short* neutralOff;
enum { neutralOff_COUNT = 32 };

extern const unsigned short* logoOff;
enum { logoOff_COUNT = 80 };

extern const signed char* neutralOffset;
enum { neutralOffset_COUNT = 8 };

extern const signed char* balloonPos;
enum { balloonPos_COUNT = 6 };

extern const signed char* imgTextPos;
enum { imgTextPos_COUNT = 20 };

extern const signed char* imgTextFrame;
enum { imgTextFrame_COUNT = 22 };


extern const signed short* titleOff;
enum { titleOff_COUNT = 148 };

extern const signed short* effectOff;
enum { effectOff_COUNT = 624 };

extern const signed short* effectMI;
enum { effectMI_COUNT = 4288 };

extern const signed short* hitOff;
enum { hitOff_COUNT = 220 };

extern const signed short* titleMI;
enum { titleMI_COUNT = 216 };

extern const signed short* tenbytenMI;
enum { tenbytenMI_COUNT = 468 };

extern const signed short* hitMI;
enum { hitMI_COUNT = 2096 };

extern const unsigned short* objOff;
enum { objOff_COUNT = 1008 };
#endif