#pragma once

#ifndef _FUNC_SYSTEM_H_
#define _FUNC_SYSTEM_H_

// Initialize and Setting
void InitMotion(OBJECT *);
void InitGraphics(void);
void InitMenu(void);
void InitGame(void);
int AddLog(unsigned char type, unsigned short cmf, unsigned short cmf2, unsigned short icon, long long count,
	int x, int y, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2,
	float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2, char * text);

//아이콘 한 개 + 한 줄 텍스트짜리 로그. iconType은 LOGICON_*, a/b/c의 의미는 종류마다 다르다.
void AddSimpleLog(int iconType, int a, int b, int c, int textIdx);

void AddBar(BAR *, signed long long, int countFrame);
void InitTarget(void);
void ArrangeEnemyTarget(void);
void ArrangeEnemyHpBar(void);
void LoadEnemyHpBar(void);
void InitBar(int);
void InitStatue(OBJECT *);
void InitReward(void);
void InitCalendar(void);
void InitCalendarWeek(void);
void SetPvpQuestReward(int);
int GetSlotCrewCnt(void);
void NewGame(void);
void GotoTitle(void);
void GotoPlay(bool forceReload = true);
void OutOfGacha(void);
void OutOfNewCard(void);
void GotoHouse(int house, int userIdx);
void GotoBoss(void);
void OutOfHouse(void);
static int CrewIdToCrewDataKey(int crewId);
static int CrewDataKeyToCmf(int crewDataKey);
static int RemoveIdFromArray(int* arr, int n, int removeId);
static void ShuffleIntArray(int* arr, int n);
static int GetBgFrameForCrewKey(int crewDataKey);
static int GetCrewStar(int crewId);
static int GetCrewRegion(int crewId);
static int GetRegionCount(void);
static int ModI(int a, int m);
static void DrawCrewGridBackground(void);
static void DrawFilmOverlay(void);
static double Rand01();
static int RollStar1to9();
static int RollRegion(int regionCount);
static int PopFromBucket(std::vector<int>& bucket);
static int PickOneCrewIdByRegionStar(
	std::vector<std::vector<std::vector<int>>>& buckets,
	int regionCount,
	int r, int s);
static inline float BL_Next01();
static inline int RegionFromCastlePos(int castlePos);
void BattleLoadingDraw(void);
static uint32_t BL_NextU32();
void BattleLoadingUpdate(void);
void GotoBattle(void);
void SetRaidBox(bool activeVal);
void WhoIsNextTurn(void);
void GotoNextStage(void);
void GotoGacha(void);
void GotoNewCollection(void);
void GotoNewCard(void);
void GotoGameOver(void);
void DemoTrigger(void);
void AddPlayer(OBJECT *);
void SpreadPlayer(int, int, int);
void ChangeTile(int, int, int, int, int);

// Save & Load
void SaveGame(void);
void LoadRoulette(void);
void LoadGame(void);
//서버가 robin을 채운 뒤의 마무리(LoadGame에서 파일 읽기만 뺀 것)
void LoadGameAfterNet(void);
void SaveOption(void);
void LoadHeroObj(int type);
void LoadOption(void);
void SaveAiHouse(void);
void LoadAiHouse(void);
void MakeAiHouse(void);

#endif