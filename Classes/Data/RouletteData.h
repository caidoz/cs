#pragma once
#include "../Def.h"

#ifndef _DATA_ROULETTE_H_
#define _DATA_ROULETTE_H_

extern const unsigned char* rouletteAttackStr;
enum { rouletteAttackStr_COUNT = 324 };

extern const unsigned char* rouletteRaidStr;
enum { rouletteRaidStr_COUNT = 28 };

extern const int* attackDelayPerType;
enum { attackDelayPerType_COUNT = 9 };
#endif