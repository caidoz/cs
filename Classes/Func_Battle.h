#pragma once
#include "Core.h"

// Battle 관련 함수
void Play(void);
void AttackSequenceDraw(void);
void EnemySequenceDraw(void);
void RaidSequenceDraw(void);
void PvpEventBarDraw(GAMEEVENT * gEvent, int x, int y, int icon, int count, int max, bool animation, bool questAni, float zoom);
void InfoDraw(void);
void DiscountMenuDraw(int, int, float zoom);
void PvpQuestMenuDraw(int, int, float zoom);
void QuestMenuDraw(int, int, float zoom);
void QuestDraw(int x, int y, int icon, int count, int max, float animation, bool questAni, int enemyIconShow, int rewardIconShow, int alpha, float zoom);
void RaidControlerDraw(void);
void SetScreenRatio(void);
void SetHero(void);
void SetBattleCrew(void);