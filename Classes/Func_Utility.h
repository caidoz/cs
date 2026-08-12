#pragma once

#ifndef _FUNC_UTILITY_H_
#define _FUNC_UTILITY_H_


// Utility 함수들
unsigned short Convert_Char_KSC5601_To_UCS2(unsigned char byte1, unsigned char byte2);
int TextToString(char* src, int count, char* dst);
int UCS2toUTF8(unsigned short* ucs2, int count, char* dst);
void TouchArrow2(int, int, int, int);
void DrawPlayerCostume(
	int type,
	int weaponDetail, int weaponGrade,
	int gloveDetail, int gloveGrade,
	int helmDetail, int helmGrade,
	int armorDetail, int armorGrade,
	int pantsDetail, int pantsGrade,
	int bootsDetail, int bootsGrade,
	int x, int y, int dirX, int attackMotion, float zoom);
void StatusDraw(int x, int y, float zoom);
void ShopMenuDraw(int x, int y, float zoom);
void EnemyUserProfileDraw_Box(HOUSE* housePtr, int x, int y, float zoom);
void EnemyUserProfileDraw(HOUSE* housePtr, int x, int y, float zoom);
void EffectDrawOnlyBg(int, float zoom);
void EffectDraw(int, float zoom);
void DrawTouchPoint(void);
void InitBanner(void);
long long GetCurrentTimeMs();
#endif