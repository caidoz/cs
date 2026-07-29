#pragma once
#ifndef _FUNC_GACHA_H_
#define _FUNC_GACHA_H_

#define GACHA_BOX_BOUNCE_FALL		(FPS * 8 / 30)	// 낙하
#define GACHA_BOX_BOUNCE_UP		(FPS * 5 / 30)	// 튀어 오름
#define GACHA_BOX_BOUNCE_DOWN		(FPS * 5 / 30)	// 다시 내려옴
#define GACHA_BOX_BOUNCE_HEIGHT		(32 * _2X)		// 바운스 높이

#define GACHA_REWARD_MAX 16
#define GACHA_MAX_REWARD_CARD 12

//------------------------------------------------------------
// 공개가 끝난 카드의 이동 연출 정보
//------------------------------------------------------------
typedef struct GACHA_REWARD_CARD_ANIM
{
	bool active;

	bool movingToTray;
	bool arrivedTray;

	bool movingToPopup;
	bool arrivedPopup;

	int moveFrame;

	float startX;
	float startY;
	float startZoom;

	float trayX;
	float trayY;
	float trayZoom;

	float popupX;
	float popupY;
	float popupZoom;

	//--------------------------------------------------------
	// 하단 메뉴로 날아가는 최종 연출
	//--------------------------------------------------------
	bool movingToBar;
	bool arrivedBar;
	bool finishedBar;

	int barMoveFrame;
	int barHoldFrame;

	float barStartX;
	float barStartY;
	float barStartZoom;

	float barTargetX;
	float barTargetY;
	float barTargetZoom;

} GACHA_REWARD_CARD_ANIM;

static GACHA_REWARD_CARD_ANIM
gachaRewardCardAnim[GACHA_MAX_REWARD_CARD];

static bool gachaCardCanAdvance = false;
static bool gachaConfirmReady = false;

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