#pragma once
#include "../Def.h"

#ifndef _DATA_REWARD_H_
#define _DATA_REWARD_H_

// 전투 및 레이드 보상 데이터
extern const int* battleRewardMedal;
enum { battleRewardMedal_COUNT = 7 };

// 스테이지별 전투 보상 골드
extern const long long* battleRewardGold;
enum { battleRewardGold_COUNT = 80 };

// 스테이지별 보스 레이드 골드
extern const long long* bossGold;
enum { bossGold_COUNT = 100 };

extern const int* raidRewardMedal;
enum { raidRewardMedal_COUNT = 7 };


extern const long long* stageClearBox;
enum { stageClearBox_COUNT = 51 };

extern const int* levelUpCategory;
enum { levelUpCategory_COUNT = 9 };

//없으면 -1로 해준다.
extern const signed long long* levelUpReward;
enum { levelUpReward_COUNT = 200 };


//없으면 -1로 해준다.
extern const signed long long* stageClearReward;
enum { stageClearReward_COUNT = 1200 };

extern const long long* equipGetRewardHeart;
enum { equipGetRewardHeart_COUNT = 432 };


//0, 1, 2 : 아이템 데이터 type, detail, grade
//4, 5 : 생산량, 생산텀(second)
extern const unsigned long long* crewReward;
enum { crewReward_COUNT = 140 };

extern const unsigned int* crewGetReward;
enum { crewGetReward_COUNT = 132 };

extern const long long* bossReward;
enum { bossReward_COUNT = 400 };


extern const int* calendarPos;
enum { calendarPos_COUNT = 32 };

extern const int* calendarMonthlyRewardDay;
enum { calendarMonthlyRewardDay_COUNT = 4 };

//박스 아이콘, 카운트, 1번째 박스 보상, 2번째 박스 보상, 3번째 박스 보상, 4번째 박스 보상
//각 박스는 최대 3개의 아이템 보상을 주고
//아이템 정보는 type, detail, (grade or count) 이렇게 3개 데이터를 사용한다.
extern const long long* calendarInfo1Month;
enum { calendarInfo1Month_COUNT = 120 };

//여기는 실제 들어갈 보상
//여기도 최대 3가지 들어갈 수 있고, 여기에는 대표 아이콘이 없고 레어하게 그냥 나열한다.
extern const long long* calendarInfo1Week;
enum { calendarInfo1Week_COUNT = 40 };

//종류, 수량
extern const int* collectionReward;
enum { collectionReward_COUNT = 96 };
#endif