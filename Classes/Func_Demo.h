#pragma once
#include "Core.h"

// Demo ���� �Լ�
void Demo(void);
void Demo_Talk(void);
bool IsTutorialPlaying(void);
bool GetTutorialTalkTarget(int textIdx, int* touchFunc, int* barIdx);
int GetTutorialCrewCardTouchFunc(void);
int GetTutorialTouchFunc(void);
void Demo_Win(void);
void Demo_Alpha(void);
void Demo_Narration(void);
void Demo_SetQuestPlayer(void);
int GatherPlayer(void);
void AfterAttack(OBJECT *);
void AfterDemo(void);
void DemoCore(void);
void DemoCore2(OBJECT *, int);
void DemoCore_Default(OBJECT *, int, int);
void DemoCore_Effect_GetItem(const signed short *);
void DemoCore_Effect_TutorialReward(const signed short *);
void DemoCore_Effect_TutorialInitBar(void);
void SpawnTutorialEnemy(int enemyType, long long hp);
void SetTutorialWave(int waveIdx);
void CloseTutorialWave(void);
void ResumeTutorialPlay(void);
void SkipPlayIntro(void);
void SetDemoEquip(OBJECT *, int, int, int);
void SetDemo(int);
void SetTalk(void);
void SetTalk_Movie(void);
void SetTalk2(int);