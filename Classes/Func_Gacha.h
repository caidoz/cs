#pragma once
#ifndef _FUNC_GACHA_H_
#define _FUNC_GACHA_H_
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