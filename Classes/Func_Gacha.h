#pragma once
#ifndef _FUNC_GACHA_H_
#define _FUNC_GACHA_H_

#define GACHA_BOX_BOUNCE_FALL		(FPS * 8 / 30)	// 낙하
#define GACHA_BOX_BOUNCE_UP		(FPS * 5 / 30)	// 튀어 오름
#define GACHA_BOX_BOUNCE_DOWN		(FPS * 5 / 30)	// 다시 내려옴
#define GACHA_BOX_BOUNCE_HEIGHT		(32 * _2X)		// 바운스 높이

int MakeGachaRewardItems(
	int boxDetail,
	int boxGrade,
	ITEM* result,
	int maxCount);

void PrepareEnemyGacha(void);
void GotoEnemyGacha(void);
void GachaDraw(void);

bool IsGachaBigReward(const ITEM* item);

void DrawGachaItemEffect(
	const ITEM* item,
	float x,
	float y,
	int effectFrame);

void GachaKey(void);

#endif