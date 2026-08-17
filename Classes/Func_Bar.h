#pragma once
#include "Core.h"

#ifndef _FUNC_BAR_H_
#define _FUNC_BAR_H_
void DrawBarIcon(int type, int x, int y, float zoom);
void BarDraw(BAR*, float zoom);
void MedalBarDraw(int, int, long long, bool, float zoom);
void PvpEventBarDraw(GAMEEVENT*, int, int, int, int, int, bool, bool, float);
void DevilHeartDraw(int x, int y, float zoom);
void GoldBarDraw(long long count, int icon, int x, int y, int alpha, float zoom);
void BattleCoinBarDraw(long long count, int icon, int x, int y, int alpha, float zoom);
void ExpBarWideDraw(int lv, long long count, int x, int y, float zoom);
void HeartBarDraw(int count, int max, int x, int y, int alpha, float zoom);
void ExpBarDraw(int lv, long long count, int x, int y, int alpha, float zoom);
void ShieldBarDraw(long long count, long long max, int x, int y, float zoom, int hpColor);
void SimpleHpBarDraw(long long count, long long max, int x, int y, float zoom, int hpColor);
void HpBarDraw(int type, long long count, long long max, int x, int y, float zoom);
void DayBarDraw(int day, int x, int y, float zoom);
void WaveBarDraw(int life, int maxLife, int x, int y, float zoom);
void BarAddStop(BAR* barP);

#endif