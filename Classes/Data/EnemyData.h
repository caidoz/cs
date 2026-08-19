#pragma once

#ifndef _DATA_ENEMY_H_
#define _DATA_ENEMY_H_

#include "../Def.h"
#include "../Cmf.h"

extern const long long* monStr;
enum { monStr_COUNT = 500 };


extern const long long* bossHp;
enum { bossHp_COUNT = 100 };

extern const long long* bossStr;
enum { bossStr_COUNT = 100 };

extern const short* summonMotion;
enum { summonMotion_COUNT = 30 };

extern const unsigned char* slimeMotion;
enum { slimeMotion_COUNT = 8 };

//모든 스킬의 개수
//시작
//쿨타임
//이동1 //공격1 //복귀 //뉴트럴 //데미지 배수 //사거리
//이동2 //공격2 //복귀 //뉴트럴 //데미지 배수 //사거리
//버프모션1 //버프2 //복귀 //뉴트럴 //데미지 배수 //사거리
//죽는모션
extern const signed short* enemyAttackPattern;
enum { enemyAttackPattern_COUNT = 8620 };

extern const float* enemyIconZoom;
enum { enemyIconZoom_COUNT = 431 };
//
extern const float* enemyZoom;
enum { enemyZoom_COUNT = 431 };

extern const float* enemyBossZoom;
enum { enemyBossZoom_COUNT = 431 };

extern const signed short* enemyData;
enum { enemyData_COUNT = 3448 };

extern const long long int* enemyStatInfo;
enum { enemyStatInfo_COUNT = 1293 };


extern const signed short* enemyAttr;
enum { enemyAttr_COUNT = 5136 };
#endif
