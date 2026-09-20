#pragma once
#ifndef _FUNC_MAP_H_
#define _FUNC_MAP_H_
// 방 셋팅 및 그리기 함수
bool IsArenaRunning(void);
void ReadMap(int);
void SetRoom(void);
void SetRoom_BGObj(void);
void SetRoom_Neutral(void);
void SetStageBoss(void);
long long CompareCombatPower(ITEM * it1, ITEM * it2);
void SetStageEnemy(int stage, int room);
void SetRoom_Etc(int);
void SetEnemyUser(void);
int GetWaveRow(int waveIdx);
int GetWaveKind(int waveIdx);
int GetWaveHpMul(int waveIdx);
int GetMaxWaveCnt(void);

//---- 3일 주기 ----
//
// 자세한 것은 Func_Map.cpp 의 GetStageCycleIdx() 위에 적어 두었다.
enum {
	STAGE_PER_DAY = 2,		//낮 한 판, 밤 한 판
	STAGE_PER_CYCLE = 5,	//2 + 2 + 마지막 날
	CYCLE_DAYS = 3,

	//한 판에 나오는 몬스터 수. 이 수를 채우면 판이 끝난다.
	//
	//웨이브 한 줄에 최대 MAXWAVEENEMY(3) 마리가 서므로 다섯 줄쯤이 한
	//판이다. 줄 수가 아니라 마리 수로 세는 것은, 줄마다 마리 수가 달라도
	//판의 길이가 같아야 하기 때문이다.
	STAGE_MONSTER_CNT = 15,
};

int GetStageCycleIdx(void);
int GetStageDay(void);
bool IsStageNight(void);
bool IsFinalDayStage(void);
int GetStagesUntilFinalDay(void);
int GetSkillCnt(int acquiredSkills[MAXCHARSKILL]);
int selectRandomSkill(int characterID, int acquiredSkills[MAXCHARSKILL]);
void ObjectSkillSetting(OBJECT * pObj);
void WaveControler(void);
void DrawWaveAnnouncement(void);
void StartTurnPhaseAnnouncement(bool enemyPhase);
void DrawTurnPhaseAnnouncement(void);
bool IsTurnPhaseAnnouncementActive(void);
long long GetTotalWaveHp(int stage);
long long GetTotalEnemyHp(int stage);
long long GetWaveHpTier(int tier);
long long GetWaveHp(int waveIdx, int curWave);
int SetEnemy(OBJECT *);
void SetNpc(OBJECT *);
void SetRoom_Demo(void);
void SetRoom_Quest(void);
void AddPlayer(OBJECT *);
void AddObject(OBJECT *, OBJECT *, int);
void SetCamera(void);
void PopTalk(void);

void DrawBackMapFar(int, int, int, int, float zoom);
void DrawBackMapFront(int, int, int, float zoom);
void DrawBackMap_Back(int, int, int, float zoom);
void DrawBackMap(int, int, int, float zoom);
void DrawBg(int, int, float zoom);
void DrawTileDirect(int mapIdx, int x, int yPos, float zoom);
void DrawTile(int mapIdx, int yPos, float zoom);
void DrawScreen(int x, int y, float zoom);
void TheaterDraw();

float EaseInOutSine(float t);
// 부드러운 상하 부유 효과
float GetDioramaFloatY(int frame);
#endif
