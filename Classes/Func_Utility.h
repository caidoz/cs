#pragma once

#ifndef _FUNC_UTILITY_H_
#define _FUNC_UTILITY_H_


// Utility ÇÔ¼öµé
unsigned short Convert_Char_KSC5601_To_UCS2(unsigned char byte1, unsigned char byte2);
int TextToString(char* src, int count, char* dst);
int UCS2toUTF8(unsigned short* ucs2, int count, char* dst);
void TouchArrow2(int, int, int, int, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void DrawPlayerCostume(
	int type,
	int weaponDetail, int weaponGrade,
	int gloveDetail, int gloveGrade,
	int helmDetail, int helmGrade,
	int armorDetail, int armorGrade,
	int pantsDetail, int pantsGrade,
	int bootsDetail, int bootsGrade,
	int x, int y, int dirX, int attackMotion, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void StatusDraw(int x, int y, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void ShopMenuDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void EnemyUserProfileDraw_Box(HOUSE* housePtr, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void EnemyUserProfileDraw(HOUSE* housePtr, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void EffectDrawOnlyBg(int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void EffectDraw(int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void DrawTouchPoint(void);
void InitBanner(void);
long long GetCurrentTimeMs();
#endif