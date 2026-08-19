#pragma once
#include "../Def.h"

#ifndef _DATA_QUEST_H_
#define _DATA_QUEST_H_

extern const int* goldQuestBox;
enum { goldQuestBox_COUNT = 10 };

extern const int* goldQuestNpc;
enum { goldQuestNpc_COUNT = 10 };

extern const int* goldQuestZokboIcon;
enum { goldQuestZokboIcon_COUNT = 21 };

extern const float* goldQuestZokboValue;
enum { goldQuestZokboValue_COUNT = 10 };

extern const int* goldQuestResultItem;
enum { goldQuestResultItem_COUNT = 30 };


//보스
extern const long long* goldQuestReward;
enum { goldQuestReward_COUNT = 150 };

//첫번째는 아이콘, 두번째는 지속시간
extern const unsigned int* pvpQuestInfo;
enum { pvpQuestInfo_COUNT = 510 };

extern const unsigned int* pvpQuestRequest;
enum { pvpQuestRequest_COUNT = 5040 };


extern const unsigned long long* pvpQuestReward;
enum { pvpQuestReward_COUNT = 20280 };

extern const unsigned int* questRequestItem;
enum { questRequestItem_COUNT = 496 };

//퀘스트 요구 아이템
extern const unsigned long long* questRequestItemCntData;
enum { questRequestItemCntData_COUNT = 900 };


//코인레이드의 골드를 250으로 나누면 스케일이 맞다.
//비율을 좀 알아보자
//
extern const unsigned long long* questReward;
enum { questReward_COUNT = 3600 };

//0:발생자 CMF 1:퀘스트타입 2:요구아이템 3:보상 아이템 4 : 플레이타임(seconds)

// QUESTINFO 정보입력 -> 8번의 퀘스트 타입에 따라 정보 수정필요.
// QUESTTYPE_ITEM_QUEST or QUESTTYPE_ITEM_ONE : (아이템가져오는퀘스트일때)REQUEST_QUEST명(ex:REQUEST_QUEST1) <-추가후 questRequest에 필요아이템 등록. TOTALITEMQUEST 값 변경. itemQuest에 퀘스트 등록
// QUESTTYPE_MON : (몹잡는퀘일때)TOTALENEMYQUEST에 값 변경. enemyQuest에 QUEST등록.
// QUESTTYPE_TRAVEL : (지도펴는퀘일때)TOTALTRAVELQUEST에 값 변경. travelQuest에 QUEST등록.
// QUESTTYPE_DEMO : (데모신보는퀘일때)TOTALDEMOQUEST에 값 변경. demoQuest에 QUEST등록.
extern const signed int* questInfo;
enum { questInfo_COUNT = 108 };


extern const int* goldQuestDotPosition;
enum { goldQuestDotPosition_COUNT = 60 };


extern const float* goldQuestZoomData;
enum { goldQuestZoomData_COUNT = 20 };
#endif