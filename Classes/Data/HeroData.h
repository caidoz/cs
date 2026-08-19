#pragma once


#ifndef _DATA_HERO_H_
#define _DATA_HERO_H_

#include "../Def.h"
#include "../Cmf.h"

//const unsigned long long crewStarUpgradeGold[TOTAL_CREW * (STAR5 + 1)] = {
extern const signed long long* crewStarUpgradeGold;
enum { crewStarUpgradeGold_COUNT = 2500 };

extern const unsigned long long* crewLvUpgradeGold;
enum { crewLvUpgradeGold_COUNT = 1600 };


extern const signed short* monXYGap;
enum { monXYGap_COUNT = 856 };

//현재 레벨을 기준으로 레벨업에 필요한 경험치
//레벨 1이면 2가 되기 위해서 4//2가 필요하다.
extern const long long* lvUpExp;
enum { lvUpExp_COUNT = 99 };

extern const int* defaultStat;
enum { defaultStat_COUNT = 3 };

extern const int* attackDelayFrame;
enum { attackDelayFrame_COUNT = 3 };

extern const int* attackDefaultFrame;
enum { attackDefaultFrame_COUNT = 3 };

extern const int* attackCountPerOnce;
enum { attackCountPerOnce_COUNT = 3 };

extern const float* skillEfficiency;
enum { skillEfficiency_COUNT = 3 };

extern const int* dx_walk;
enum { dx_walk_COUNT = 3 };

extern const unsigned char* walkFrame;
enum { walkFrame_COUNT = 4 };


//LV이 0일 때는
extern const int* crewBulletLvUpDmgPercent;
enum { crewBulletLvUpDmgPercent_COUNT = 10 };


//const int crewData[TOTAL_CREW * CREWDATASIZE] = {
//0 종류
//1 몇성인지
//2 DMG
//3 DATA_SLING
extern const int* crewData;
enum { crewData_COUNT = 384 };



//const signed char jump[6] = {24, 16, 11, 8, 5, 2};
//const signed char jump2[6] = {24, 18, 13, 9, 5, 2};

extern const signed short* jumpUpMotion;
enum { jumpUpMotion_COUNT = 56 };

extern const signed short* jumpDownMotion;
enum { jumpDownMotion_COUNT = 107 };

extern const signed short* backHomeMotion;
enum { backHomeMotion_COUNT = 105 };

//60프레임 대응. 원본 {14,13,12,11,10,8,6,4,2,1}의 각 값을 두 프레임에 나눠 담았다.
//총 상승량 81은 그대로고 체공 시간만 2배가 되어 30프레임 시절 체감으로 돌아온다.
extern const signed char* jump;
enum { jump_COUNT = 20 };
extern const signed short* jumpFullFrame;
enum { jumpFullFrame_COUNT = 11 };

extern const signed short* alphaJumpFrame;
enum { alphaJumpFrame_COUNT = 11 };


extern const signed short* jumpFullFrame2;
enum { jumpFullFrame2_COUNT = 7 };

extern const unsigned char* charEtcData;
enum { charEtcData_COUNT = 6 };

extern const unsigned short* robinSkillStartFrame;
enum { robinSkillStartFrame_COUNT = 23 };

extern const unsigned short* robinSkillClosingFrame;
enum { robinSkillClosingFrame_COUNT = 23 };

extern const unsigned short* dianaSkillStartFrame;
enum { dianaSkillStartFrame_COUNT = 23 };

extern const unsigned short* dianaSkillClosingFrame;
enum { dianaSkillClosingFrame_COUNT = 23 };

extern const unsigned short* maxxSkillStartFrame;
enum { maxxSkillStartFrame_COUNT = 22 };

extern const unsigned short* maxxSkillClosingFrame;
enum { maxxSkillClosingFrame_COUNT = 22 };

//c0~c2 모션을 60프레임용으로 늘리면 인덱스가 char 범위를 넘는다.
//MSVC는 이 경우 에러가 아니라 C4309 경고만 내고 값을 잘라버리므로 폭을 넓혀 둔다.
extern const unsigned short* robinSkillMotion;
enum { robinSkillMotion_COUNT = 8612 };

extern const unsigned short* dianaSkillMotion;
enum { dianaSkillMotion_COUNT = 7964 };

extern const unsigned short* maxxSkillMotion;
enum { maxxSkillMotion_COUNT = 3652 };


extern const signed char* dianaHelmPos;
enum { dianaHelmPos_COUNT = 50 };

extern const signed char* maxxHelmPos;
enum { maxxHelmPos_COUNT = 50 };

extern const unsigned short* concentrateMotion;
enum { concentrateMotion_COUNT = 25 };

extern const unsigned short* bombShotMotion;
enum { bombShotMotion_COUNT = 88 };

//const signed char guidedShotDx[16] = {
//	//PO_C1_MISSILE_SHOT0
//	-2, 0,
//	//PO_C1_MISSILE_SHOT1
//	-1, 1,
//	//PO_C1_MISSILE_SHOT2
//	0, 2,
//	//PO_C1_MISSILE_SHOT3
//	1, 1,
//	//PO_C1_MISSILE_SHOT4
//	2, 0,
//	//PO_C1_MISSILE_SHOT5
//	1, -1,
//	//PO_C1_MISSILE_SHOT6
//	0, -2,
//	//PO_C1_MISSILE_SHOT7
//	-1, -1,
//};
//24 + 36 * 3 + 36 * 3 = 
extern const unsigned short* satelliteShotMotion;
enum { satelliteShotMotion_COUNT = 240 };

//주의 : core.h는 signed이어야 함
extern const signed short* satelliteShotData;
enum { satelliteShotData_COUNT = 15 };

extern const unsigned char* hitMarkData;
enum { hitMarkData_COUNT = 15 };

extern const unsigned short* buffData;
enum { buffData_COUNT = 52 };

extern const unsigned short* dianaBulletData;
enum { dianaBulletData_COUNT = 35 };

//주의 : core.h는 signed이어야 함
extern const signed short* maxxBoomerangData;
enum { maxxBoomerangData_COUNT = 119 };

extern const short* normalboomerangData;
enum { normalboomerangData_COUNT = 64 };

//주의 : core.h는 signed이어야 함
extern const signed short* sateliteMotion;
enum { sateliteMotion_COUNT = 816 };


extern const unsigned char* levelUpMIC;
enum { levelUpMIC_COUNT = 40 };

extern const signed int* debufStartFrame;
enum { debufStartFrame_COUNT = 6 };

extern const unsigned char* debufEffect;
enum { debufEffect_COUNT = 72 };

extern const unsigned char* emoticonRate;
enum { emoticonRate_COUNT = 26 };

extern const signed char* scowlEffect;
enum { scowlEffect_COUNT = 8 };

extern const signed char* sweatEffect;
enum { sweatEffect_COUNT = 7 };

extern const signed char* questionEffect;
enum { questionEffect_COUNT = 10 };

extern const signed char* surpriseEffect;
enum { surpriseEffect_COUNT = 5 };

extern const unsigned short* stunMotion;
enum { stunMotion_COUNT = 10 };


extern const signed short* equipSlotPos;
enum { equipSlotPos_COUNT = 24 };

extern const signed short* equipSlotPos2;
enum { equipSlotPos2_COUNT = 32 };

extern const unsigned char* statueInfo;
enum { statueInfo_COUNT = 16 };


extern const unsigned short* deadMotion;
enum { deadMotion_COUNT = 24 };


extern const unsigned short* motionData;
enum { motionData_COUNT = 96 };
#endif

