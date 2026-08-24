#pragma once
#include "../Def.h"

#ifndef _DATA_TEXT_H_
#define _DATA_TEXT_H_

extern const int* areaName;
enum { areaName_COUNT = 15 };

extern const unsigned short* unicode_table;
enum { unicode_table_COUNT = 2350 };


extern const unsigned short* itemNameStart;
enum { itemNameStart_COUNT = 39 };


extern const unsigned short* alphaOff;
enum { alphaOff_COUNT = 499 };

extern const signed short* alertText;
enum { alertText_COUNT = 9 };
#endif