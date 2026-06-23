#pragma once
#include "Core.h"

// Battle 관련 함수
void Play(void);
void AttackSequenceDraw(void);
void EnemySequenceDraw(void);
void RaidSequenceDraw(void);
void PvpEventBarDraw(GAMEEVENT * gEvent, int x, int y, int icon, int count, int max, bool animation, bool questAni, float zoom, cocos2d::RenderTexture * cvtDest, cocos2d::Layer * cvtLayer, bool buffering);
void InfoDraw(void);
void CrewInfoDraw(int stage, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void DiscountMenuDraw(int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void PvpQuestMenuDraw(int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void QuestMenuDraw(int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void QuestDraw(int x, int y, int icon, int count, int max, float animation, bool questAni, int enemyIconShow, int rewardIconShow, int alpha, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void RaidBoxDraw(int x, int y, float zoom, bool touch, bool shadow, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void RaidControlerDraw(void);

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
void SetScreenRatio(void);
void SetHero(void);
void SetBattleCrew(void);