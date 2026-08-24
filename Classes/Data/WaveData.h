#pragma once
#include "../Def.h"

#ifndef _DATA_WAVE_H_
#define _DATA_WAVE_H_

//robin.
extern const int* boss;
enum { boss_COUNT = 18 };
//0: 어떤 몬스터가 등장하는지
//1: 등장 타이밍
//2: 체력
extern const int* wave;
enum { wave_COUNT = 90000 };

extern const long long* stageGold;
enum { stageGold_COUNT = 1000 };

#endif