#pragma once
#include "../Def.h"

#ifndef _DATA_GAME_H_
#define _DATA_GAME_H_

extern const unsigned short* attackSequenceFrameData;
enum { attackSequenceFrameData_COUNT = 7 };


extern const unsigned char* betCoin;
enum { betCoin_COUNT = 5 };

extern const unsigned char* betHeart;
enum { betHeart_COUNT = 7 };

//0:패시브/액티브인가, 1:소비MP, 2:쿨타임, 3:습득조건스킬명, 4:습득조건스킬레벨, 5:아이콘
//0:패시브/액티브인가, 1:소환몬스터, 2:소환위치, 3:습득조건스킬명, 4:습득조건스킬레벨, 5:아이콘
extern const long long* skillUpgradeGold;
enum { skillUpgradeGold_COUNT = 900 };


extern const signed char* attrToDebuf;
enum { attrToDebuf_COUNT = 6 };

extern const unsigned char* attrEffect;
enum { attrEffect_COUNT = 120 };


extern const unsigned char* playerMainStat;
enum { playerMainStat_COUNT = 3 };

extern const unsigned char* zoomData;
enum { zoomData_COUNT = 5 };

const char* const saveFileName[3] = {
	SAVEFILE,
	GAMEFILE,
	OPTIONFILE,
};

extern const unsigned char* debufToAttr;
enum { debufToAttr_COUNT = 6 };

extern const signed char* signCurve;
enum { signCurve_COUNT = 16 };


extern const unsigned char* optionInfo;
enum { optionInfo_COUNT = 54 };


extern const unsigned short* sin1024;
enum { sin1024_COUNT = 91 };

extern const unsigned short* tan1024;
enum { tan1024_COUNT = 91 };
#endif

