#pragma once
#ifndef _FUNC_MAP_H_
#define _FUNC_MAP_H_
// 방 셋팅 및 그리기 함수
bool IsArenaRunning(void);
void ReadMap(int);
void SetRoom(void);
void SetRoom_BGObj(void);
void SetRoom_Neutral(void);
void SetBossEnemy(void);
void SetStageBoss(void);
void SetHouseCrew(long long, int);
long long CompareCombatPower(ITEM * it1, ITEM * it2);
void SetStageEnemy(int stage, int room);
void SetRoom_Enemy(void);
void SetRoom_Etc(int);
void SetEnemyUser(void);
int GetMaxWaveCnt(void);
int GetSkillCnt(int acquiredSkills[MAXCHARSKILL]);
int selectRandomSkill(int characterID, int acquiredSkills[MAXCHARSKILL]);
void CharSkillSetting(void);
void ObjectSkillSetting(OBJECT * pObj);
void WaveStart(void);
void WaveControler(void);
long long GetTotalWaveHp(int stage);
long long GetTotalEnemyHp(int stage);
long long GetWaveHp(int waveIdx, int curWave);
int SetEnemy(OBJECT *);
void SetNpc(OBJECT *);
void SetRaid(void);
int SetCmf(int);
void SetRoom_Demo(void);
void SetRoom_Quest(void);
void AddPlayer(OBJECT *);
void AddObject(OBJECT *, OBJECT *, int);
void SetCamera(void);
void PopTalk(void);

void DrawBackMapFar(int, int, int, int, float zoom);
void DrawBackMapFront(int, int, int, float zoom);
void DrawBackMap_Back(int, int, int, float zoom);
void DrawBackMapDirect(int xPos, int yPos, int mapIdx, float zoom);
void DrawBackMap(int, int, int, float zoom);
void DrawBg(int, int, float zoom);
void DrawTileDirect(int mapIdx, int x, int yPos, float zoom);
void DrawTile(int mapIdx, int yPos, float zoom);
void DrawForeMap(int, int, int, float zoom);
void DrawScreen(int x, int y, float zoom);
void TheaterDraw();

float EaseInOutSine(float t);
// 부드러운 상하 부유 효과
float GetDioramaFloatY(int frame);
#endif