#pragma once

#ifndef _DATA_BATTLE_H_
#define _DATA_BATTLE_H_

#include "../Def.h"
#include "../Cmf.h"

extern const int* battleMotion;
enum { battleMotion_COUNT = 90 };

extern const int* houseGoldStage;
enum { houseGoldStage_COUNT = 12 };

extern const long long* houseGold;
enum { houseGold_COUNT = 12 };

extern const int* wheelCrewPos;
enum { wheelCrewPos_COUNT = 10 };

extern const unsigned short gameEventOpenStage[24];

extern const int* rouletteProb;
enum { rouletteProb_COUNT = 7 };

extern const int activeSkillProb[TOTALCHAR][2 * MAXCHARSKILL];

extern const float* popUpFrameData;
enum { popUpFrameData_COUNT = 8 };

extern const short* hitAlpha;
enum { hitAlpha_COUNT = 3 };

extern const short* raidAlpha;
enum { raidAlpha_COUNT = 3 };

// ===== 도장깨기/돈털기 데이터 =====
extern const int* battleData;
enum { battleData_COUNT = 3 };

extern const int* skillInitData;
enum { skillInitData_COUNT = 18 };

const unsigned short attackRange[] =
{
    TSIZE / 2,//1 * TSIZE,// + TSIZE / 2,
    1 * TSIZE,//1 * TSIZE + TSIZE / 2,// + TSIZE / 2,
    1 * TSIZE + TSIZE / 2,//2 * TSIZE,// + TSIZE / 2,
};


extern const unsigned short* arenaOff;
enum { arenaOff_COUNT = 72 };

extern const signed short* arenaMI;
enum { arenaMI_COUNT = 360 };

extern const unsigned char* arenaMIC;
enum { arenaMIC_COUNT = 46 };
#endif
