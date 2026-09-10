#pragma once

#ifndef _FUNC_UTILITY_H_
#define _FUNC_UTILITY_H_


// Utility 함수들
int TextToString(char* src, int count, char* dst);
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
void EnemyUserProfileDraw_Box(HOUSE* housePtr, int x, int y, float zoom);
void EnemyUserProfileDraw(HOUSE* housePtr, int x, int y, float zoom);
void SocialProfileImageDraw(int profileIdx, int x, int y, float size);
void UserProfileNameDraw(int profileIdx, const char* nickname,
	int imageX, int imageY, float imageSize,
	float nameX, float nameY, float textZoom, int align);
void EffectDrawOnlyBg(int, float zoom);
void EffectDraw(int, float zoom);
void DrawTouchPoint(void);
long long GetCurrentTimeMs();
#endif
