#pragma once
#include "Core.h"

// Demo 관련 함수
void Demo(void);
void Demo_Talk(void);
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
void SetDemoEquip(OBJECT *, int, int, int);
void SetDemo(int);
void SetTalk(void);
void SetTalk_Movie(void);
void SetTalk2(int);