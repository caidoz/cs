#pragma once
#include "Core.h"

#ifndef _FUNC_BAR_H_
#define _FUNC_BAR_H_
void DrawBarIcon(int type, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void BarDraw(BAR*, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void HammerBarDraw(int, int, long long, bool, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void MedalBarDraw(int, int, long long, bool, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void PvpEventBarDraw(GAMEEVENT*, int, int, int, int, int, bool, bool, float, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void DevilHeartDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void GoldBarDraw(long long count, int icon, int x, int y, int alpha, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void BattleCoinBarDraw(long long count, int icon, int x, int y, int alpha, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void ExpBarWideDraw(int lv, long long count, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void HeartBarDraw(int count, int max, int x, int y, int alpha, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void ExpBarDraw(int lv, long long count, int x, int y, int alpha, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void ShieldBarDraw(long long count, long long max, int x, int y, float zoom, int hpColor, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void SimpleHpBarDraw(long long count, long long max, int x, int y, float zoom, int hpColor, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void HpBarDraw(int type, long long count, long long max, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void DayBarDraw(int day, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void WaveBarDraw(int life, int maxLife, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void BarAddStop(BAR* barP);

#endif