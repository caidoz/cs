#pragma once
#include "Core.h"
#include "Func.h"
#include "Text.h"
#include "Data.h"

enum GACHA_DEPTH
{
	GACHA_DEPTH_BOX = 0,       // 상자 낙하 및 오픈
	GACHA_DEPTH_CARD,          // 보상 한 장씩 공개
	GACHA_DEPTH_SUMMARY,       // 최종 보상 요약
	GACHA_DEPTH_FLYTOBAR,		//요약카드가 각 버튼으로 날라가는 것.
	GACHA_DEPTH_GETITEM        // 인벤토리 반영 후 종료
};

static bool gachaPrepared = false;


// 현재 적에게서 획득한 상자 정보
static int gachaBoxDetail = 0;
static int gachaBoxGrade = 0;

// 카드 한 장씩 공개할 때 사용하는 인덱스
static int gachaOpenCardIdx = 0;

// 현재 카드의 등장 완료 여부
static bool gachaCurrentCardReady = false;

// 보상을 실제 인벤토리에 넣었는지
static bool gachaRewardReceived = false;

static float GachaClamp01(float value)
{
	if (value < 0.0f)
		return 0.0f;

	if (value > 1.0f)
		return 1.0f;

	return value;
}

static float GachaEaseOutCubic(float value)
{
	value = GachaClamp01(value);

	float inverse =
		1.0f - value;

	return 1.0f -
		inverse *
		inverse *
		inverse;
}

static float GachaEaseInOutCubic(float value)
{
	value = GachaClamp01(value);

	if (value < 0.5f)
	{
		return
			4.0f *
			value *
			value *
			value;
	}

	float inverse =
		-2.0f *
		value +
		2.0f;

	return
		1.0f -
		inverse *
		inverse *
		inverse /
		2.0f;
}

static float GachaLerp(
	float start,
	float end,
	float progress)
{
	return
		start +
		(end - start) *
		progress;
}

int MakeGachaRewardItems(
	int boxDetail,
	int boxGrade,
	ITEM* result,
	int maxCount)
{
	if (result == NULL || maxCount <= 0)
		return 0;

	int count = 0;

	//--------------------------------------------------------
	// 실제 프로젝트의 상자 보상 생성 함수가 있다면
	// 이 부분만 교체
	//--------------------------------------------------------

	/*
	예시:

	count = GetBoxReward(
		boxDetail,
		boxGrade,
		result,
		maxCount);
	*/

	//--------------------------------------------------------
	// 임시 샘플
	//--------------------------------------------------------

	// 골드
	if (count < maxCount)
	{
		memset(&result[count], 0, sizeof(ITEM));

		result[count].type = ITEM_GOLD;
		result[count].detail = 0;
		result[count].grade = 0;
		result[count].count = 200000;
		result[count].lv = 0;
		result[count].cooldown = 0;
		result[count].seen = true;

		count++;
	}

	// 동료
	if (count < maxCount)
	{
		memset(&result[count], 0, sizeof(ITEM));

		result[count].type = ITEM_CREW;
		result[count].detail = 3;
		result[count].grade = 4;
		result[count].count = 1;
		result[count].lv = 1;
		result[count].cooldown = 0;

		// ���� ���� ���ο� ���� NEW
		result[count].seen =
			GetInvenIdx(
				result[count].type,
				result[count].detail,
				result[count].grade) != -1;

		count++;
	}

	// 장비
	if (count < maxCount)
	{
		memset(&result[count], 0, sizeof(ITEM));

		result[count].type = ITEM_SWORD;
		result[count].detail = 2;
		result[count].grade = 5;
		result[count].count = 1;
		result[count].lv = 1;
		result[count].cooldown = 0;

		result[count].seen =
			GetInvenIdx(
				result[count].type,
				result[count].detail,
				result[count].grade) != -1;

		count++;
	}

	return count;
}

void PrepareEnemyGacha(void)
{
	int i;
	float boxZoom = 0.3f + 0.01 * boxMark[0].detail;

	gachaBoxDetail = boxMark[0].detail;
	gachaBoxGrade = boxMark[0].grade;
	
	memset(&boxMark, 0, sizeof(boxMark));
	memset(&boxCardMark, 0, sizeof(boxCardMark));
	memset(&boxCardItem, 0, sizeof(boxCardItem));

	gachaIndex = 0;
	boxCnt = 1;

	//--------------------------------------------------------
	// ITEM 구조체 형태로 실제 보상 생성
	//--------------------------------------------------------
	boxCardItemCnt[0] =
		MakeGachaRewardItems(
			gachaBoxDetail,
			gachaBoxGrade,
			boxCardItem[0],
			GACHA_REWARD_MAX);

	//--------------------------------------------------------
	// 상자 마크 생성
	//--------------------------------------------------------
	SetBoxMark(
		xOffset + DX / 2,
		DY + 64 * _2X,

		xOffset + DX / 2,
		BOTTOMMENUHEIGHT + 32 * _2X,

		xOffset + DX / 2,
		BOTTOMMENUHEIGHT + 32 * _2X,

		16 * _2X / MOTIONDIV,
		4 * _2X / MOTIONDIV,

		16 * _2X / MOTIONDIV,
		4 * _2X / MOTIONDIV,

		FPS / 2,
		FPS / 2,

		30,

		gachaBoxDetail,
		gachaBoxGrade,

		boxZoom,
		boxZoom,
		0.01f / MOTIONDIV,

		boxZoom,
		boxZoom,
		0.01f / MOTIONDIV);

	gachaDepth = GACHA_DEPTH_BOX;
	gachaFrame = 0;
	gachaCardIdx = 0;
	gachaOpenCardIdx = 0;

	gachaCurrentCardReady = false;
	gachaRewardReceived = false;
	gachaPrepared = true;

	for (i = 0; i < GACHA_REWARD_MAX; i++)
		memset(&boxCardMark[i], 0, sizeof(boxCardMark[i]));
}

void GotoEnemyGacha(void)
{
	gachaPrepared = false;
	PrepareEnemyGacha();

	// 기존 상태 전환 사용
	// status = STATUS_GACHA;
}

void GachaDraw(void)
{
	static int manualCardMarkIdx = -1;

	//--------------------------------------------------------
	// 카드 정렬 연출 상태
	//--------------------------------------------------------
	static int previousOpenCardIdx = -1;
	static int trayCardCount = 0;
	static bool waitingForTrayComplete = false;

	//--------------------------------------------------------
	// 각 화면 전용 프레임
	//--------------------------------------------------------
	static int previousGachaDepth = -1;
	static int summaryFrame = 0;
	static int flyToBarFrame = 0;
	static int getItemFrame = 0;

	int i;

	//--------------------------------------------------------
	// 최초 준비
	//--------------------------------------------------------
	if (gachaPrepared == false)
	{
		PrepareEnemyGacha();

		manualCardMarkIdx = -1;

		boxMark[0].motionFrame = -1;

		previousGachaDepth = -1;
		previousOpenCardIdx = -1;

		summaryFrame = 0;
		flyToBarFrame = 0;
		getItemFrame = 0;

		trayCardCount = 0;
		waitingForTrayComplete = false;

		gachaCardCanAdvance = false;
		gachaConfirmReady = false;
		
		memset(
			gachaRewardCardAnim,
			0,
			sizeof(gachaRewardCardAnim));
	}

	//--------------------------------------------------------
	// 가챠 단계 변경 확인
	//--------------------------------------------------------
	if (previousGachaDepth != gachaDepth)
	{
		switch (gachaDepth)
		{
		case GACHA_DEPTH_SUMMARY:
			summaryFrame = 0;
			break;
		case GACHA_DEPTH_FLYTOBAR:
			flyToBarFrame = 0;
			break;
		case GACHA_DEPTH_GETITEM:
			getItemFrame = 0;
			break;
		}

		previousGachaDepth = gachaDepth;
	}

	ScreenDarken(SCREENDARKEN);

	switch (gachaDepth)
	{
		//--------------------------------------------------------
		// 상자 등장 및 오픈
		//--------------------------------------------------------
	case GACHA_DEPTH_BOX:
	{
		const int WAIT_END = 8;
		const int SQUASH_END = 13;
		const int RISE_END = 19;
		const int APEX_END = 23;
		const int FALL_END = 29;
		const int LAND_END = 33;
		const int FINISH_END = 43;

		//----------------------------------------------------
		// 상자 최하단 위치
		//----------------------------------------------------
		const float baseY =
			BOTTOMMENUHEIGHT +
			32.0f * _2X;

		const float apexY =
			baseY +
			GACHA_BOX_BOUNCE_HEIGHT * 1.45f;

		float baseZoom =
			boxMark[0].zoomEnd2;

		if (baseZoom <= 0.0f)
			baseZoom = boxMark[0].zoom2;

		float targetY =
			baseY;

		float targetZoom =
			baseZoom;

		//----------------------------------------------------
		// 기존 상자 낙하 완료 확인
		//----------------------------------------------------
		if (boxMark[0].motionFrame < 0)
		{
			const float POSITION_EPSILON =
				0.5f * _2X;

			const float ZOOM_EPSILON =
				0.001f;

			bool positionArrived =
				fabsf(
					boxMark[0].y -
					baseY) <=
				POSITION_EPSILON;

			bool zoomArrived =
				fabsf(
					boxMark[0].zoom2 -
					baseZoom) <=
				ZOOM_EPSILON;

			if (positionArrived &&
				zoomArrived)
			{
				boxMark[0].motionFrame =
					0;

				boxMark[0].y =
					baseY;

				boxMark[0].targetY2 =
					baseY;

				boxMark[0].speed2 =
					0.0f;

				boxMark[0].speedIncrement2 =
					0.0f;

				boxMark[0].zoom2 =
					baseZoom;

				boxMark[0].zoomIncrement2 =
					0.0f;
			}
			else
			{
				break;
			}
		}

		//----------------------------------------------------
		// 상자 바운스 및 오픈
		//----------------------------------------------------
		if (boxMark[0].motionFrame >= 0)
		{
			int animFrame =
				boxMark[0].motionFrame;

			float progress =
				0.0f;

			float curve =
				0.0f;

			targetY =
				baseY;

			targetZoom =
				baseZoom;

			//------------------------------------------------
			// 바닥 대기
			//------------------------------------------------
			if (animFrame < WAIT_END)
			{
				targetY =
					baseY;

				targetZoom =
					baseZoom;
			}

			//------------------------------------------------
			// 점프 전 웅크리기
			//------------------------------------------------
			else if (animFrame < SQUASH_END)
			{
				progress =
					(float)(
						animFrame -
						WAIT_END) /
					(float)(
						SQUASH_END -
						WAIT_END);

				curve =
					progress *
					progress;

				targetY =
					baseY -
					3.0f *
					_2X *
					curve;

				targetZoom =
					baseZoom *
					(1.0f -
						0.05f *
						curve);
			}

			// ------------------------------------------------
			// 빠르게 상승
			//------------------------------------------------
			else if (animFrame < RISE_END)
			{
				progress =
					(float)(
						animFrame -
						SQUASH_END) /
					(float)(
						RISE_END -
						SQUASH_END);

				curve =
					1.0f -
					powf(
						1.0f -
						progress,
						3.0f);

				targetY =
					baseY +
					(apexY -
						baseY) *
					curve;

				targetZoom =
					baseZoom *
					(0.95f +
						0.05f *
						curve);
			}

			//------------------------------------------------
			// 최고점에서 상자 오픈
			//------------------------------------------------
			else if (animFrame < APEX_END)
			{
				targetY =
					apexY;

				targetZoom =
					baseZoom;

				if (animFrame == RISE_END)
				{
					boxMark[0].motion =
						BOXSTATUS_OPENED;

					PlayMusic(M_OPENDOOR);
				}
			}

			//------------------------------------------------
			// 급강하
			//------------------------------------------------
			else if (animFrame < FALL_END)
			{
				progress =
					(float)(
						animFrame -
						APEX_END) /
					(float)(
						FALL_END -
						APEX_END);

				curve =
					progress *
					progress *
					progress;

				targetY =
					apexY -
					(apexY -
						baseY) *
					curve;

				targetZoom =
					baseZoom;
			}

			//------------------------------------------------
			// 착지 충격
			//------------------------------------------------
			else if (animFrame < LAND_END)
			{
				progress =
					(float)(
						animFrame -
						FALL_END) /
					(float)(
						LAND_END -
						FALL_END);

				curve =
					sinf(
						progress *
						3.141592f);

				targetY =
					baseY -
					2.5f *
					_2X *
					curve;

				targetZoom =
					baseZoom *
					(1.0f -
						0.045f *
						curve);

				if (animFrame < LAND_END - 1)
				{
					PlayMusic(M_KUNG);
				}
			}

			//------------------------------------------------
			// 열린 상태로 대기
			//------------------------------------------------
			else
			{
				targetY =
					baseY;

				targetZoom =
					baseZoom;
			}

			boxMark[0].y =
				targetY;

			boxMark[0].targetY2 =
				targetY;

			boxMark[0].zoom2 =
				targetZoom;

			boxMark[0].zoomIncrement2 =
				0.0f;

			//------------------------------------------------
			// 상자 연출 완료
			//------------------------------------------------
			if (animFrame >= FINISH_END)
			{
				boxMark[0].y =
					baseY;

				boxMark[0].targetY2 =
					baseY;

				boxMark[0].zoom2 =
					baseZoom;

				gachaDepth =
					GACHA_DEPTH_CARD;

				gachaOpenCardIdx =
					-1;

				gachaCurrentCardReady =
					true;

				manualCardMarkIdx =
					-1;
			}
			else
			{
				boxMark[0].motionFrame++;
			}
		}

		break;
	}

	//--------------------------------------------------------
	// 카드 한 장씩 공개
	//--------------------------------------------------------
	//--------------------------------------------------------
// 카드 한 장씩 공개
//--------------------------------------------------------
case GACHA_DEPTH_CARD:
{
	//----------------------------------------------------
	// 카드 공개 연출 프레임
	//----------------------------------------------------
	const int CARD_RISE_FRAME =
		8 * MOTIONDIV;

	const int CARD_IMPACT_FRAME =
		2 * MOTIONDIV;

	const int CARD_RECOVER_FRAME =
		3 * MOTIONDIV;

	const int CARD_HOLD_FRAME =
		4 * MOTIONDIV;

	const int CARD_FLIP_INTERVAL =
		2 * MOTIONDIV;

	const int CARD_BACK_FRAME_COUNT =
		7;

	const int CARD_RISE_END =
		CARD_RISE_FRAME;

	const int CARD_IMPACT_END =
		CARD_RISE_END +
		CARD_IMPACT_FRAME;

	const int CARD_RECOVER_END =
		CARD_IMPACT_END +
		CARD_RECOVER_FRAME;

	const int CARD_HOLD_END =
		CARD_RECOVER_END +
		CARD_HOLD_FRAME;

	const int CARD_FLIP_END =
		CARD_HOLD_END +
		CARD_FLIP_INTERVAL *
		CARD_BACK_FRAME_COUNT;

	const int CARD_TOUCH_DELAY =
		FPS / 6;

	//----------------------------------------------------
	// 공개 카드 크기
	//----------------------------------------------------
	const float CARD_START_ZOOM =
		0.38f;

	const float CARD_FINAL_ZOOM =
		0.95f;

	const float CARD_OVERSHOOT_ZOOM =
		1.02f;

	const float CARD_PRESSED_ZOOM =
		0.90f;

	//----------------------------------------------------
	// 하단으로 이동하는 연출
	//----------------------------------------------------
	const int CARD_TO_TRAY_FRAME =
		10 * MOTIONDIV;

	const float TRAY_CARD_ZOOM =
		0.25f;

	const float TRAY_GAP =
		4.0f * _2X;

	//----------------------------------------------------
	// 공개 카드 위치
	//----------------------------------------------------
	const float CARD_START_OFFSET_Y =
		120.0f * _2X;

	const float CARD_END_OFFSET_Y =
		240.0f * _2X;

	const float CARD_CENTER_X =
		boxMark[0].x;

	const float CARD_START_Y =
		boxMark[0].y +
		CARD_START_OFFSET_Y;

	const float CARD_END_Y =
		boxMark[0].y +
		CARD_END_OFFSET_Y;

	int rewardCount =
		boxCardItemCnt[0];

	if (rewardCount >
		GACHA_MAX_REWARD_CARD)
	{
		rewardCount =
			GACHA_MAX_REWARD_CARD;
	}

	//----------------------------------------------------
	// 하단 카드 정렬 위치 계산
	//
	// 최대 12개를 한 줄로 정렬한다.
	//----------------------------------------------------
	float trayCardW =
		240.0f *
		TRAY_CARD_ZOOM;

	float trayCardH =
		332.0f *
		TRAY_CARD_ZOOM;

	float trayTotalW =
		rewardCount *
		trayCardW +
		(rewardCount - 1) *
		TRAY_GAP;

	float trayStartX =
		xOffset +
		DX / 2.0f -
		trayTotalW / 2.0f;

	float trayY =
		BOTTOMMENUHEIGHT +
		12.0f * _2X;

	//----------------------------------------------------
	// 모든 카드의 하단 목표 위치 갱신
	//----------------------------------------------------
	for (i = 0;
		i < rewardCount;
		i++)
	{
		gachaRewardCardAnim[i].trayX =
			trayStartX +
			i *
			(trayCardW + TRAY_GAP);

		gachaRewardCardAnim[i].trayY =
			trayY;

		gachaRewardCardAnim[i].trayZoom =
			TRAY_CARD_ZOOM;
	}

	//----------------------------------------------------
	// 카드 번호가 변경됨
	//
	// 이전 카드가 선택 완료된 것이므로
	// 현재 위치에서 하단 정렬 위치로 날려 보낸다.
	//----------------------------------------------------
	if (previousOpenCardIdx !=
		gachaOpenCardIdx)
	{
		if (previousOpenCardIdx >= 0 &&
			previousOpenCardIdx <
			rewardCount)
		{
			GACHA_REWARD_CARD_ANIM* anim =
				&gachaRewardCardAnim[
					previousOpenCardIdx];

			anim->active =
				true;

			anim->movingToTray =
				true;

			anim->arrivedTray =
				false;

			anim->movingToPopup =
				false;

			anim->arrivedPopup =
				false;

			anim->moveFrame =
				0;

			//------------------------------------------------
			// 현재 공개 카드 위치에서 출발
			//------------------------------------------------
			if (manualCardMarkIdx >= 0)
			{
				ICONMARK* previousCard =
					&boxCardMark[
						manualCardMarkIdx];

				anim->startX =
					previousCard->x;

				anim->startY =
					previousCard->y;

				anim->startZoom =
					previousCard->zoom;

				memset(
					previousCard,
					0,
					sizeof(ICONMARK));

				manualCardMarkIdx =
					-1;
			}
			else
			{
				anim->startX =
					CARD_CENTER_X -
					240.0f *
					CARD_FINAL_ZOOM /
					2.0f;

				anim->startY =
					CARD_END_Y;

				anim->startZoom =
					CARD_FINAL_ZOOM;
			}

			trayCardCount =
				previousOpenCardIdx +
				1;

			PlayMusic(M_ITEM);
		}

		previousOpenCardIdx =
			gachaOpenCardIdx;

		gachaCurrentCardReady =
			false;

		gachaCardCanAdvance =
			false;
	}

	//----------------------------------------------------
	// 하단으로 이동 중인 카드와 도착한 카드 출력
	//----------------------------------------------------
	bool allTrayCardsArrived =
		true;

	for (i = 0;
		i < trayCardCount &&
		i < rewardCount;
		i++)
	{
		GACHA_REWARD_CARD_ANIM* anim =
			&gachaRewardCardAnim[i];

		if (anim->active == false)
			continue;

		float drawX =
			anim->trayX;

		float drawY =
			anim->trayY;

		float drawZoom =
			anim->trayZoom;

		if (anim->movingToTray)
		{
			float progress =
				(float)anim->moveFrame /
				(float)CARD_TO_TRAY_FRAME;

			progress =
				GachaClamp01(progress);

			float moveCurve =
				GachaEaseInOutCubic(
					progress);

			float zoomCurve =
				GachaEaseOutCubic(
					progress);

			drawX =
				GachaLerp(
					anim->startX,
					anim->trayX,
					moveCurve);

			//------------------------------------------------
			// 직선 이동보다 약간 위로 솟는 곡선
			//------------------------------------------------
			float linearY =
				GachaLerp(
					anim->startY,
					anim->trayY,
					moveCurve);

			float arcY =
				sinf(
					progress *
					3.141592f) *
				32.0f *
				_2X;

			drawY =
				linearY +
				arcY;

			drawZoom =
				GachaLerp(
					anim->startZoom,
					anim->trayZoom,
					zoomCurve);

			anim->moveFrame++;

			if (anim->moveFrame >=
				CARD_TO_TRAY_FRAME)
			{
				anim->movingToTray =
					false;

				anim->arrivedTray =
					true;

				anim->moveFrame =
					0;

				drawX =
					anim->trayX;

				drawY =
					anim->trayY;

				drawZoom =
					anim->trayZoom;
			}
		}

		if (anim->arrivedTray == false)
		{
			allTrayCardsArrived =
				false;
		}

		ITEM* trayItem =
			&boxCardItem[0][i];

		DrawItemCard(
			trayItem->type,
			trayItem->detail,
			trayItem->grade,
			trayItem->lv,
			false,
			(int)drawX,
			(int)drawY,
			false,
			drawZoom,
			false,
			0,
			0,
			true,
			0,
			gScreenBuffer,
			gScreenLayer,
			false);
	}

	//----------------------------------------------------
	// 아직 첫 카드를 뽑기 전
	//----------------------------------------------------
	if (gachaOpenCardIdx < 0)
	{
		SetAlpha(
			32 -
			Abs(
				frame /
				MOTIONDIV %
				32 -
				16));

		DrawGoldAlpha(
			xOffset + DX / 2,
			BOTTOMMENUHEIGHT,
			ALPHA_TABTOCOLLECT,
			FONT_GOLD_LARGE,
			1,
			CENTER,
			false,
			false,
			gScreenBuffer,
			gScreenLayer,
			false);

		SetAlpha(32);

		gachaCardCanAdvance =
			true;

		SetRectPoint(
			0,
			DY,
			DX,
			DY,
			TOUCH_FUNC_GETGACHACARD);

		break;
	}

	//----------------------------------------------------
	// 모든 카드 선택 완료
	//----------------------------------------------------
	if (gachaOpenCardIdx >=
		rewardCount)
	{
		waitingForTrayComplete =
			true;

		gachaCurrentCardReady =
			false;

		gachaCardCanAdvance =
			false;

		//------------------------------------------------
		// 마지막 카드까지 하단에 도착하면 요약 화면
		//------------------------------------------------
		if (waitingForTrayComplete &&
			trayCardCount >= rewardCount &&
			allTrayCardsArrived)
		{
			waitingForTrayComplete =
				false;

			gachaDepth =
				GACHA_DEPTH_SUMMARY;

			summaryFrame =
				0;

			previousGachaDepth =
				GACHA_DEPTH_CARD;
		}

		break;
	}

	ITEM* item =
		&boxCardItem[0][
			gachaOpenCardIdx];

	//----------------------------------------------------
	// 현재 공개 카드 생성
	//----------------------------------------------------
	if (gachaCurrentCardReady == false)
	{
		float startCenterX =
			CARD_CENTER_X;

		float startCenterY =
			CARD_START_Y;

		int markIdx =
			SetBoxCardMark(
				startCenterX,
				startCenterY,

				CARD_CENTER_X,
				CARD_END_Y,

				0,
				0,

				0,
				0,

				0,
				0,

				FPS,
				FPS,

				GetItemIcon(
					item->type,
					item->detail,
					item->grade),

				0,

				item->count,
				item->type,
				item->detail,
				item->grade,
				item->cooldown,

				false,
				true,
				true,

				PLAYER,

				1,

				CARD_START_ZOOM,
				CARD_FINAL_ZOOM,
				0.0f,

				CARD_FINAL_ZOOM,
				CARD_FINAL_ZOOM,
				0.0f,

				false,

				item->seen == false);

		if (markIdx >= 0)
		{
			ICONMARK* card =
				&boxCardMark[
					markIdx];

			manualCardMarkIdx =
				markIdx;

			card->manual =
				true;

			card->frame =
				1;

			card->frame2 =
				0;

			card->motionFrame =
				0;

			card->openFrame =
				1;

			card->x =
				startCenterX;

			card->y =
				startCenterY;

			card->targetX =
				CARD_CENTER_X;

			card->targetY =
				CARD_END_Y;

			card->targetX2 =
				0.0f;

			card->targetY2 =
				0.0f;

			card->zoom =
				CARD_START_ZOOM;

			card->zoom2 =
				CARD_START_ZOOM;

			card->zoomEnd =
				CARD_FINAL_ZOOM;

			card->zoomEnd2 =
				CARD_FINAL_ZOOM;

			card->zoomIncrement =
				0.0f;

			card->zoomIncrement2 =
				0.0f;

			card->speed =
				0.0f;

			card->speed2 =
				0.0f;

			card->speedIncrement =
				0.0f;

			card->speedIncrement2 =
				0.0f;

			gachaCurrentCardReady =
				true;

			PlayMusic(M_ITEM);
		}
	}

	//----------------------------------------------------
	// 현재 카드 수동 공개 애니메이션
	//----------------------------------------------------
	if (manualCardMarkIdx >= 0)
	{
		ICONMARK* card =
			&boxCardMark[
				manualCardMarkIdx];

		int cardAnimFrame =
			card->motionFrame;

		float drawCenterX =
			CARD_CENTER_X;

		float drawCenterY =
			CARD_END_Y;

		float drawZoom =
			CARD_FINAL_ZOOM;

		float progress =
			0.0f;

		float curve =
			0.0f;

		if (cardAnimFrame <
			CARD_RISE_END)
		{
			progress =
				(float)cardAnimFrame /
				(float)CARD_RISE_FRAME;

			progress =
				GachaClamp01(
					progress);

			curve =
				GachaEaseOutCubic(
					progress);

			drawCenterY =
				CARD_START_Y +
				(CARD_END_Y -
					CARD_START_Y) *
				curve;

			drawZoom =
				CARD_START_ZOOM +
				(CARD_OVERSHOOT_ZOOM -
					CARD_START_ZOOM) *
				curve;

			card->openFrame =
				1;
		}
		else if (cardAnimFrame <
			CARD_IMPACT_END)
		{
			progress =
				(float)(
					cardAnimFrame -
					CARD_RISE_END) /
				(float)CARD_IMPACT_FRAME;

			progress =
				GachaClamp01(
					progress);

			drawZoom =
				CARD_OVERSHOOT_ZOOM +
				(CARD_PRESSED_ZOOM -
					CARD_OVERSHOOT_ZOOM) *
				progress;

			card->openFrame =
				1;
		}
		else if (cardAnimFrame <
			CARD_RECOVER_END)
		{
			progress =
				(float)(
					cardAnimFrame -
					CARD_IMPACT_END) /
				(float)CARD_RECOVER_FRAME;

			progress =
				GachaClamp01(
					progress);

			curve =
				1.0f -
				(1.0f - progress) *
				(1.0f - progress);

			drawZoom =
				CARD_PRESSED_ZOOM +
				(CARD_FINAL_ZOOM -
					CARD_PRESSED_ZOOM) *
				curve;

			card->openFrame =
				1;
		}
		else if (cardAnimFrame <
			CARD_HOLD_END)
		{
			card->openFrame =
				1;
		}
		else if (cardAnimFrame <
			CARD_FLIP_END)
		{
			int flipElapsed =
				cardAnimFrame -
				CARD_HOLD_END;

			int backFrame =
				flipElapsed /
				CARD_FLIP_INTERVAL +
				1;

			if (backFrame < 1)
			{
				backFrame =
					1;
			}

			if (backFrame ==
				CARD_BACK_FRAME_COUNT - 1 &&
				flipElapsed %
				CARD_FLIP_INTERVAL ==
				0)
			{
				PlayMusic(
					M_CARDSPLIT);
			}

			if (backFrame >
				CARD_BACK_FRAME_COUNT)
			{
				backFrame =
					CARD_BACK_FRAME_COUNT;
			}

			card->openFrame =
				backFrame;
		}
		else
		{
			card->openFrame =
				0;
		}

		card->x =
			drawCenterX;

		card->y =
			drawCenterY;

		card->zoom =
			drawZoom;

		card->zoom2 =
			drawZoom;

		card->manual =
			true;

		card->frame =
			1;

		card->frame2 =
			0;

		card->motionFrame++;
	}

	//----------------------------------------------------
	// 앞면 공개 완료 후 다음 카드 허용
	//----------------------------------------------------
	if (manualCardMarkIdx >= 0)
	{
		ICONMARK* card =
			&boxCardMark[
				manualCardMarkIdx];

		if (card->motionFrame >
			CARD_FLIP_END +
			CARD_TOUCH_DELAY)
		{
			gachaCardCanAdvance =
				true;

			SetAlpha(
				32 -
				Abs(
					frame /
					MOTIONDIV %
					32 -
					16));

			DrawGoldAlpha(
				xOffset + DX / 2,
				BOTTOMMENUHEIGHT,
				ALPHA_TABTOCOLLECT,
				FONT_GOLD_LARGE,
				1,
				CENTER,
				false,
				false,
				gScreenBuffer,
				gScreenLayer,
				false);

			SetAlpha(32);

			SetRectPoint(
				0,
				DY,
				DX,
				DY,
				TOUCH_FUNC_GETGACHACARD);
		}
	}

	break;
}

	//--------------------------------------------------------
// 모든 보상 요약 화면
//--------------------------------------------------------
case GACHA_DEPTH_SUMMARY:
{
	//----------------------------------------------------
	// MENU_IMG 창
	//----------------------------------------------------
	const int PANEL_SRC_X =
		0;

	const int PANEL_SRC_Y =
		606;

	const int PANEL_SRC_W =
		400;

	const int PANEL_SRC_H =
		409;

	//----------------------------------------------------
	// MENU_IMG 확인 버튼
	//----------------------------------------------------
	const int BTN_SRC_X =
		401;

	const int BTN_SRC_Y =
		606;

	const int BTN_SRC_W =
		216;

	const int BTN_SRC_H =
		68;

	//----------------------------------------------------
	// 연출 프레임
	//----------------------------------------------------
	const int SUMMARY_ENTER_FRAME =
		14 * MOTIONDIV;

	const int SUMMARY_CARD_FRAME =
		16 * MOTIONDIV;

	const int SUMMARY_BUTTON_DELAY =
		4 * MOTIONDIV;

	const float PANEL_FINAL_ZOOM =
		1.5f;

	const float PANEL_START_ZOOM =
		0.20f;

	int rewardCount =
		boxCardItemCnt[0];

	if (rewardCount >
		GACHA_MAX_REWARD_CARD)
	{
		rewardCount =
			GACHA_MAX_REWARD_CARD;
	}

	//----------------------------------------------------
	// 요약 화면 최초 진입
	//----------------------------------------------------
	if (summaryFrame == 0)
	{
		manualCardMarkIdx =
			-1;

		gachaCurrentCardReady =
			false;

		gachaCardCanAdvance =
			false;

		gachaConfirmReady =
			false;

		memset(
			boxCardMark,
			0,
			sizeof(boxCardMark));

		for (i = 0;
			i < rewardCount;
			i++)
		{
			gachaRewardCardAnim[i].
				movingToPopup =
				true;

			gachaRewardCardAnim[i].
				arrivedPopup =
				false;

			gachaRewardCardAnim[i].
				moveFrame =
				0;
		}

		PlayMusic(M_CARDSPLIT);
	}

	//----------------------------------------------------
	// 팝업 확대율
	//----------------------------------------------------
	float panelProgress =
		(float)summaryFrame /
		(float)SUMMARY_ENTER_FRAME;

	panelProgress =
		GachaClamp01(
			panelProgress);

	float panelCurve =
		GachaEaseOutCubic(
			panelProgress);

	//----------------------------------------------------
	// 처음 약간 크게 넘어갔다가 복원
	//----------------------------------------------------
	float panelZoom;

	if (panelProgress < 0.75f)
	{
		float firstProgress =
			panelProgress /
			0.75f;

		panelZoom =
			GachaLerp(
				PANEL_START_ZOOM,
				PANEL_FINAL_ZOOM *
				1.05f,
				GachaEaseOutCubic(
					firstProgress));
	}
	else
	{
		float recoverProgress =
			(panelProgress -
				0.75f) /
			0.25f;

		panelZoom =
			GachaLerp(
				PANEL_FINAL_ZOOM *
				1.05f,
				PANEL_FINAL_ZOOM,
				recoverProgress);
	}

	float panelDisplayW =
		PANEL_SRC_W *
		panelZoom;

	float panelDisplayH =
		PANEL_SRC_H *
		panelZoom;

	float panelCX =
		xOffset +
		DX / 2.0f;

	float panelCY =
		DY / 2.0f;

	//----------------------------------------------------
	// 상자가 아래로 빠지는 연출
	//----------------------------------------------------
	float boxExitProgress =
		GachaEaseInOutCubic(
			panelProgress);

	float boxExitY =
		GachaLerp(
			BOTTOMMENUHEIGHT +
			32.0f * _2X,
			-300.0f * _2X,
			boxExitProgress);

	boxMark[0].y =
		boxExitY;

	boxMark[0].targetY2 =
		boxExitY;

	//----------------------------------------------------
	// 팝업 출력
	//----------------------------------------------------
	DrawImage(
		PANEL_SRC_W,
		PANEL_SRC_H,
		PANEL_SRC_X,
		PANEL_SRC_Y,

		panelCX -
		panelDisplayW /
		2.0f,

		panelCY +
		panelDisplayH /
		2.0f,

		false,
		false,
		false,
		false,
		false,

		panelZoom,

		sprite[MENU_IMG],
		gScreenBuffer,
		gScreenLayer,
		MENU_IMG,
		false);

	//----------------------------------------------------
	// 카드 배치
	//
	// 최대 4열 × 3행 = 12장
	//----------------------------------------------------
	int numCols;

	if (rewardCount <= 1)
		numCols = 1;
	else if (rewardCount == 2)
		numCols = 2;
	else if (rewardCount == 3)
		numCols = 3;
	else
		numCols = 4;

	int numRows =
		(rewardCount +
			numCols -
			1) /
		numCols;

	//----------------------------------------------------
	// 팝업 최종 크기를 기준으로 카드 크기 계산
	//----------------------------------------------------
	float finalPanelW =
		PANEL_SRC_W *
		PANEL_FINAL_ZOOM;

	float finalPanelH =
		PANEL_SRC_H *
		PANEL_FINAL_ZOOM;

	float popupGapX =
		4.0f * _2X;

	float popupGapY =
		4.0f * _2X;

	float popupInnerW =
		finalPanelW *
		0.84f;

	float popupInnerH =
		finalPanelH *
		0.66f;

	float popupCardZoomByW =
		(popupInnerW -
			popupGapX *
			(numCols - 1)) /
		(numCols *
			240.0f);

	float popupCardZoomByH =
		(popupInnerH -
			popupGapY *
			(numRows - 1)) /
		(numRows *
			332.0f);

	float popupCardZoom =
		popupCardZoomByW;

	if (popupCardZoom >
		popupCardZoomByH)
	{
		popupCardZoom =
			popupCardZoomByH;
	}

	float popupCardW =
		240.0f *
		popupCardZoom;

	float popupCardH =
		332.0f *
		popupCardZoom;

	float popupGridW =
		numCols *
		popupCardW +
		(numCols - 1) *
		popupGapX;

	float popupGridH =
		numRows *
		popupCardH +
		(numRows - 1) *
		popupGapY;

	float popupGridStartX =
		panelCX -
		popupGridW /
		2.0f;

	//----------------------------------------------------
	// 팝업 중앙보다 약간 위에 카드 배치
	//----------------------------------------------------
	float popupGridTop =
		panelCY +
		finalPanelH *
		0.30f;

	bool allPopupCardsArrived =
		true;

	//----------------------------------------------------
	// 카드 이동 및 출력
	//----------------------------------------------------
	for (i = 0;
		i < rewardCount;
		i++)
	{
		int col =
			i %
			numCols;

		int row =
			i /
			numCols;

		float targetX =
			popupGridStartX +
			col *
			(popupCardW +
				popupGapX);

		float targetY =
			popupGridTop -
			row *
			(popupCardH +
				popupGapY);

		GACHA_REWARD_CARD_ANIM* anim =
			&gachaRewardCardAnim[i];

		anim->popupX =
			targetX;

		anim->popupY =
			targetY;

		anim->popupZoom =
			popupCardZoom;

		float drawX =
			targetX;

		float drawY =
			targetY;

		float drawZoom =
			popupCardZoom;

		if (anim->movingToPopup)
		{
			//------------------------------------------------
			// 팝업 자체가 어느 정도 보인 뒤 카드가 이동
			//------------------------------------------------
			int cardStartDelay =
				i *
				MOTIONDIV /
				2;

			int cardElapsed =
				summaryFrame -
				cardStartDelay;

			if (cardElapsed < 0)
			{
				cardElapsed =
					0;
			}

			float cardProgress =
				(float)cardElapsed /
				(float)SUMMARY_CARD_FRAME;

			cardProgress =
				GachaClamp01(
					cardProgress);

			float cardCurve =
				GachaEaseInOutCubic(
					cardProgress);

			drawX =
				GachaLerp(
					anim->trayX,
					targetX,
					cardCurve);

			float linearY =
				GachaLerp(
					anim->trayY,
					targetY,
					cardCurve);

			float arcY =
				sinf(
					cardProgress *
					3.141592f) *
				38.0f *
				_2X;

			drawY =
				linearY +
				arcY;

			drawZoom =
				GachaLerp(
					anim->trayZoom,
					popupCardZoom,
					GachaEaseOutCubic(
						cardProgress));

			if (cardProgress >=
				1.0f)
			{
				anim->movingToPopup =
					false;

				anim->arrivedPopup =
					true;

				drawX =
					targetX;

				drawY =
					targetY;

				drawZoom =
					popupCardZoom;
			}
		}

		if (anim->arrivedPopup == false)
		{
			allPopupCardsArrived =
				false;
		}

		ITEM* item =
			&boxCardItem[0][i];

		DrawItemCard(
			item->type,
			item->detail,
			item->grade,
			item->lv,
			false,
			(int)drawX,
			(int)drawY,
			false,
			drawZoom,
			false,
			0,
			0,
			true,
			0,
			gScreenBuffer,
			gScreenLayer,
			false);
	}

	//----------------------------------------------------
	// 모든 카드가 박힌 후 확인 버튼 활성화
	//----------------------------------------------------
	if (allPopupCardsArrived &&
		summaryFrame >
		SUMMARY_CARD_FRAME +
		SUMMARY_BUTTON_DELAY)
	{
		gachaConfirmReady =
			true;

		float btnZoom =
			(100.0f * _2X) /
			BTN_SRC_W;

		float btnDisplayW =
			BTN_SRC_W *
			btnZoom;

		float btnDisplayH =
			BTN_SRC_H *
			btnZoom;

		float btnX =
			panelCX -
			btnDisplayW /
			2.0f;

		float btnY =
			panelCY -
			finalPanelH /
			2.0f + btnDisplayH 
			+ 16.0f *
			_2X;

		DrawImage(
			BTN_SRC_W,
			BTN_SRC_H,
			BTN_SRC_X,
			BTN_SRC_Y,
			btnX,
			btnY,
			false,
			false,
			false,
			false,
			false,
			btnZoom,
			sprite[MENU_IMG],
			gScreenBuffer,
			gScreenLayer,
			MENU_IMG,
			false);

		SetAlpha(
			32 -
			Abs(
				frame /
				MOTIONDIV %
				32 -
				16));

		DrawGoldAlpha(
			(int)panelCX,
			BOTTOMMENUHEIGHT,
			ALPHA_TABTOCOLLECT,
			FONT_GOLD_LARGE,
			1,
			CENTER,
			false,
			false,
			gScreenBuffer,
			gScreenLayer,
			false);

		SetAlpha(32);

		//------------------------------------------------
		// 화면 전체가 아니라 확인 버튼만 터치
		//------------------------------------------------
		SetRectPoint(
			(int)btnX,
			(int)(
				btnY +
				btnDisplayH),
			(int)(
				btnX +
				btnDisplayW),
			(int)btnY,
			TOUCH_FUNC_GETGACHACARD);
	}

	summaryFrame++;

	break;
}

//--------------------------------------------------------
// 요약 카드가 하단 메뉴로 날아가는 연출
//--------------------------------------------------------
case GACHA_DEPTH_FLYTOBAR:
{
	//----------------------------------------------------
	// 연출 시간
	//----------------------------------------------------
	const int PANEL_CLOSE_FRAME =
		8 * MOTIONDIV;

	const int CARD_FLY_FRAME =
		14 * MOTIONDIV;

	const int CARD_HOLD_FRAME =
		5 * MOTIONDIV;

	//----------------------------------------------------
	// 카드마다 약간씩 순차 출발
	//----------------------------------------------------
	const int CARD_START_INTERVAL =
		1 * MOTIONDIV;

	//----------------------------------------------------
	// 도착했을 때 크기
	//
	// 팝업에서 보이던 크기의 20%
	//----------------------------------------------------
	const float CARD_TARGET_ZOOM_RATE =
		0.20f;

	//----------------------------------------------------
	// 팝업 정보
	//----------------------------------------------------
	const int PANEL_SRC_X =
		0;

	const int PANEL_SRC_Y =
		606;

	const int PANEL_SRC_W =
		400;

	const int PANEL_SRC_H =
		409;

	const float PANEL_FINAL_ZOOM =
		1.5f;

	float panelCX =
		xOffset +
		DX / 2.0f;

	float panelCY =
		DY / 2.0f;

	int rewardCount =
		boxCardItemCnt[0];

	if (rewardCount >
		GACHA_MAX_REWARD_CARD)
	{
		rewardCount =
			GACHA_MAX_REWARD_CARD;
	}

	//----------------------------------------------------
	// 최초 진입
	//----------------------------------------------------
	if (flyToBarFrame == 0)
	{
		gachaConfirmReady =
			false;

		for (i = 0;
			i < rewardCount;
			i++)
		{
			GACHA_REWARD_CARD_ANIM* anim =
				&gachaRewardCardAnim[i];

			ITEM* item =
				&boxCardItem[0][i];

			anim->movingToBar =
				true;

			anim->arrivedBar =
				false;

			anim->finishedBar =
				false;

			anim->barMoveFrame =
				0;

			anim->barHoldFrame =
				0;

			//------------------------------------------------
			// 팝업 안에 박혀 있던 위치에서 출발
			//------------------------------------------------
			anim->barStartX =
				anim->popupX;

			anim->barStartY =
				anim->popupY;

			anim->barStartZoom =
				anim->popupZoom;

			//------------------------------------------------
			// 카드 종류별 도착 바 위치
			//------------------------------------------------
			float destinationCX =
				panelCX;

			float destinationCY =
				BOTTOMMENUHEIGHT;

			if (item->type ==
				ITEM_CREW)
			{
				destinationCX =
					bar[BAR_CREW].x;

				destinationCY =
					bar[BAR_CREW].y;
			}
			else if (item->type ==
				ITEM_HEART)
			{
				destinationCX =
					bar[BAR_HEART].x;

				destinationCY =
					bar[BAR_HEART].y;
			}
			else if (item->type ==
				ITEM_GOLD)
			{
				destinationCX =
					bar[BAR_GOLD].x;

				destinationCY =
					bar[BAR_GOLD].y;
			}
			else if (item->type <
				ITEM_NETITEM)
			{
				destinationCX =
					bar[BAR_EQUIP].x;

				destinationCY =
					bar[BAR_EQUIP].y;
			}

			//------------------------------------------------
			// 최종 카드 크기
			//------------------------------------------------
			anim->barTargetZoom =
				anim->barStartZoom *
				CARD_TARGET_ZOOM_RATE;

			//------------------------------------------------
			// DrawItemCard 좌표는 카드의 좌측 하단 기준
			//
			// bar 좌표는 중심점으로 보고 보정
			//------------------------------------------------
			anim->barTargetX =
				destinationCX -
				240.0f *
				anim->barTargetZoom /
				2.0f;

			anim->barTargetY =
				destinationCY -
				332.0f *
				anim->barTargetZoom /
				2.0f;
		}

		PlayMusic(M_ITEM);
	}

	//----------------------------------------------------
	// 팝업 닫힘 연출
	//----------------------------------------------------
	float panelCloseProgress =
		(float)flyToBarFrame /
		(float)PANEL_CLOSE_FRAME;

	panelCloseProgress =
		GachaClamp01(
			panelCloseProgress);

	float panelCloseCurve =
		GachaEaseInOutCubic(
			panelCloseProgress);

	float panelZoom =
		GachaLerp(
			PANEL_FINAL_ZOOM,
			0.0f,
			panelCloseCurve);

	//----------------------------------------------------
	// 팝업이 작아지는 동안만 출력
	//----------------------------------------------------
	if (panelZoom > 0.03f)
	{
		float panelDisplayW =
			PANEL_SRC_W *
			panelZoom;

		float panelDisplayH =
			PANEL_SRC_H *
			panelZoom;

		DrawImage(
			PANEL_SRC_W,
			PANEL_SRC_H,
			PANEL_SRC_X,
			PANEL_SRC_Y,

			panelCX -
			panelDisplayW /
			2.0f,

			panelCY +
			panelDisplayH /
			2.0f,

			false,
			false,
			false,
			false,
			false,

			panelZoom,

			sprite[MENU_IMG],
			gScreenBuffer,
			gScreenLayer,
			MENU_IMG,
			false);
	}

	//----------------------------------------------------
	// 모든 카드의 최종 연출 완료 여부
	//----------------------------------------------------
	bool allCardsFinished =
		true;

	for (i = 0;
		i < rewardCount;
		i++)
	{
		GACHA_REWARD_CARD_ANIM* anim =
			&gachaRewardCardAnim[i];

		ITEM* item =
			&boxCardItem[0][i];

		//------------------------------------------------
		// 카드별 출발 지연
		//------------------------------------------------
		int startDelay =
			i *
			CARD_START_INTERVAL;

		int elapsedFrame =
			flyToBarFrame -
			startDelay;

		float drawX =
			anim->barStartX;

		float drawY =
			anim->barStartY;

		float drawZoom =
			anim->barStartZoom;

		//------------------------------------------------
		// 아직 출발 전
		//------------------------------------------------
		if (elapsedFrame < 0)
		{
			allCardsFinished =
				false;
		}

		//------------------------------------------------
		// 하단 바로 날아가는 중
		//------------------------------------------------
		else if (anim->movingToBar)
		{
			float progress =
				(float)elapsedFrame /
				(float)CARD_FLY_FRAME;

			progress =
				GachaClamp01(
					progress);

			float moveCurve =
				GachaEaseInOutCubic(
					progress);

			float zoomCurve =
				GachaEaseOutCubic(
					progress);

			drawX =
				GachaLerp(
					anim->barStartX,
					anim->barTargetX,
					moveCurve);

			//------------------------------------------------
			// 기본 Y 이동
			//------------------------------------------------
			float linearY =
				GachaLerp(
					anim->barStartY,
					anim->barTargetY,
					moveCurve);

			//------------------------------------------------
			// 이동 중 살짝 위로 솟는 포물선
			//------------------------------------------------
			float arcY =
				sinf(
					progress *
					3.141592f) *
				48.0f *
				_2X;

			drawY =
				linearY +
				arcY;

			drawZoom =
				GachaLerp(
					anim->barStartZoom,
					anim->barTargetZoom,
					zoomCurve);

			//------------------------------------------------
			// 목적지 도착
			//------------------------------------------------
			if (progress >= 1.0f)
			{
				anim->movingToBar =
					false;

				anim->arrivedBar =
					true;

				anim->barHoldFrame =
					0;

				drawX =
					anim->barTargetX;

				drawY =
					anim->barTargetY;

				drawZoom =
					anim->barTargetZoom;

				//------------------------------------------------
				// 목적지에 도착했을 때 효과음
				//------------------------------------------------
				PlayMusic(M_ITEM);
			}

			allCardsFinished =
				false;
		}

		//------------------------------------------------
		// 해당 바 위에서 잠시 정지
		//------------------------------------------------
		else if (anim->arrivedBar)
		{
			drawX =
				anim->barTargetX;

			drawY =
				anim->barTargetY;

			drawZoom =
				anim->barTargetZoom;

			anim->barHoldFrame++;

			if (anim->barHoldFrame >=
				CARD_HOLD_FRAME)
			{
				anim->arrivedBar =
					false;

				anim->finishedBar =
					true;
			}
			else
			{
				allCardsFinished =
					false;
			}
		}

		//------------------------------------------------
		// 아직 사라지지 않은 카드만 출력
		//------------------------------------------------
		if (anim->finishedBar == false)
		{
			DrawItemCard(
				item->type,
				item->detail,
				item->grade,
				item->lv,
				false,
				(int)drawX,
				(int)drawY,
				false,
				drawZoom,
				false,
				0,
				0,
				true,
				0,
				gScreenBuffer,
				gScreenLayer,
				false);
		}
	}

	//----------------------------------------------------
	// 모든 카드가 목적지에서 잠시 머문 후 사라짐
	//----------------------------------------------------
	if (allCardsFinished)
	{
		gachaDepth =
			GACHA_DEPTH_GETITEM;

		getItemFrame =
			0;

		previousGachaDepth =
			GACHA_DEPTH_FLYTOBAR;
	}

	flyToBarFrame++;

	break;
}

	//--------------------------------------------------------
	// 보상 실제 지급
	//--------------------------------------------------------
	case GACHA_DEPTH_GETITEM:
	{
		if (gachaRewardReceived == false)
		{
			gachaRewardReceived =
				true;

			for (i = 0;
				i < boxCardItemCnt[0];
				i++)
			{
				ITEM* item =
					&boxCardItem[0][i];

				GetItem(
					item->type,
					item->lv,
					item->detail,
					item->grade,
					item->count,
					false);

				if (item->type != ITEM_CREW &&
					item->type != ITEM_GOLD &&
					item->type != ITEM_HEART &&
					item->type != ITEM_STAR)
				{
					SetStrongestEquip(
						item->type,
						item->detail,
						item->grade);
				}
			}

			PlayMusic(M_ITEM);
		}

		if (getItemFrame > FPS / 3)
		{
			gachaPrepared =
				false;

			manualCardMarkIdx =
				-1;

			previousOpenCardIdx =
				-1;

			trayCardCount =
				0;

			waitingForTrayComplete =
				false;

			flyToBarFrame =
				0;

			gachaCurrentCardReady =
				false;

			gachaCardCanAdvance =
				false;

			gachaConfirmReady =
				false;

			memset(
				gachaRewardCardAnim,
				0,
				sizeof(gachaRewardCardAnim));

			memset(controlMark, 0, sizeof(controlMark));

			OutOfGacha();
			robin.waveIdx++;
			robin.curWaveIdx = 0;
			memset(&robin.waveActive, 0, sizeof(robin.waveActive));
			return;
		}

		getItemFrame++;

		break;
	}
	}

	gachaFrame++;
}


bool IsGachaBigReward(const ITEM* item)
{
	if (item == NULL)
		return false;

	switch (item->type)
	{
	case ITEM_GOLD:
		return item->count >= 1000000;

	case ITEM_CREW:
		return item->grade >= 4;

	default:
		// 장비 아이템 범위는 프로젝트 상수에 맞게 조정
		if (item->type >= ITEM_SWORD &&
			item->grade >= 4)
		{
			return true;
		}

		break;
	}

	return false;
}

void DrawGachaItemEffect(
	const ITEM* item,
	float x,
	float y,
	int effectFrame)
{
	if (item == NULL)
		return;

	int effectImg = GACHA_IMG;
	float effectZoom = 1.0f;

	bool bigReward =
		IsGachaBigReward(item);

	if (bigReward)
	{
		effectImg = GACHA_IMG;

		effectZoom =
			1.1f +
			sin(effectFrame * 5) *
			0.08f;
	}
	else if (item->grade >= 5)
	{
		effectImg = GACHA_IMG;

		effectZoom =
			1.0f +
			sin(effectFrame * 4) *
			0.04f;
	}

	//--------------------------------------------------------
	// 카드 뒤 방사형 빛
	//--------------------------------------------------------
	DrawImage(
		512,
		512,

		0,
		0,

		x - 256.0f * effectZoom,
		y + 256.0f * effectZoom,

		false,
		false,
		false,
		false,
		false,

		effectZoom,

		sprite[effectImg],
		gScreenBuffer,
		gScreenLayer,
		effectImg,
		false);

	//--------------------------------------------------------
	// 고가치 보상 테두리 효과
	//--------------------------------------------------------
	if (bigReward)
	{
		int GACHA_RIM_SIZE_X = 128 * _2X;
		int GACHA_RIM_SIZE_Y = 128 * _2X;

		float rimZoom =
			1.0f +
			sin(effectFrame * 6) *
			0.03f;

		DrawImage(
			GACHA_RIM_SIZE_X,
			GACHA_RIM_SIZE_Y,

			0,
			0,

			x -
			(float)GACHA_RIM_SIZE_X *
			rimZoom / 2,

			y +
			(float)GACHA_RIM_SIZE_Y *
			rimZoom / 2,

			false,
			false,
			false,
			false,
			false,

			rimZoom,

			sprite[GACHA_IMG],
			gScreenBuffer,
			gScreenLayer,
			GACHA_IMG,
			false);
	}

	//--------------------------------------------------------
	// NEW는 SetBoxCardMark 마지막 인자로 이미 전달
	//--------------------------------------------------------
}

void GachaKey(void)
{
	if (gachaPrepared == false)
		return;

	//--------------------------------------------------------
	// 실제 프로젝트에서 터치 함수 체크를 쓴다면 활성화
	//--------------------------------------------------------
	//if (touchFunc != TOUCH_FUNC_GETGACHACARD)
	//	return;

	//--------------------------------------------------------
	// 실제 프로젝트에서 터치 업 조건을 쓴다면 활성화
	//--------------------------------------------------------
	//if (touchUp == false)
	//	return;

	//touchFunc = TOUCH_FUNC_NONE;

	switch (gachaDepth)
	{
		//--------------------------------------------------------
		// 카드 공개
		//--------------------------------------------------------
	case GACHA_DEPTH_CARD:
	{
		if (gachaCardCanAdvance == false)
			break;

		gachaCardCanAdvance =
			false;

		//------------------------------------------------
		// 첫 번째 탭:
		// 첫 번째 카드를 상자에서 꺼냄
		//------------------------------------------------
		if (gachaOpenCardIdx < 0)
		{
			gachaOpenCardIdx =
				0;

			gachaCurrentCardReady =
				false;
		}
		//------------------------------------------------
		// 이후 탭:
		// 현재 카드는 하단 정렬 위치로 이동시키고
		// 다음 카드 번호로 진행
		//------------------------------------------------
		else
		{
			gachaOpenCardIdx++;

			gachaCurrentCardReady =
				false;
		}

		break;
	}

	//--------------------------------------------------------
	// 최종 보상 팝업
	//--------------------------------------------------------
	case GACHA_DEPTH_SUMMARY:
	{
		if (gachaConfirmReady == false)
			break;

		gachaConfirmReady =
			false;

		//------------------------------------------------
		// 바로 아이템 지급 화면으로 넘어가지 않고
		// 카드가 각 메뉴 바로 날아가는 연출 시작
		//------------------------------------------------
		gachaDepth =
			GACHA_DEPTH_FLYTOBAR;

		break;
	}

	//--------------------------------------------------------
	// 카드가 메뉴로 날아가는 동안에는 입력 무시
	//--------------------------------------------------------
	case GACHA_DEPTH_FLYTOBAR:
	{
		break;
	}

	//--------------------------------------------------------
	// 지급 처리 중 입력 무시
	//--------------------------------------------------------
	case GACHA_DEPTH_GETITEM:
	{
		break;
	}
	}
}


