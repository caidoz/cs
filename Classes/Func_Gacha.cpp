#pragma once
#include "Core.h"
#include "Func.h"
#include "Text.h"
#include "Data.h"

#define GACHA_REWARD_MAX 16

enum GACHA_DEPTH
{
	GACHA_DEPTH_BOX = 0,       // 상자 낙하 및 오픈
	GACHA_DEPTH_CARD,          // 보상 한 장씩 공개
	GACHA_DEPTH_SUMMARY,       // 최종 보상 요약
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
	// 각 화면 전용 프레임
	//--------------------------------------------------------
	static int previousGachaDepth = -1;
	static int summaryFrame = 0;
	static int getItemFrame = 0;

	int i;

	//--------------------------------------------------------
	// 최초 준비
	//--------------------------------------------------------
	if (gachaPrepared == false)
	{
		PrepareEnemyGacha();

		manualCardMarkIdx = -1;

		//----------------------------------------------------
		// 기존 상자 낙하가 아직 끝나지 않은 상태
		//----------------------------------------------------
		boxMark[0].motionFrame = -1;

		previousGachaDepth = -1;
		summaryFrame = 0;
		getItemFrame = 0;
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
	case GACHA_DEPTH_CARD:
	{
		//----------------------------------------------------
		// 카드 연출 프레임
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
		// 카드 확대율
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
		// 상자 기준 카드 위치
		//
		// 시작 위치:
		// 상자 중심에서 120만큼 위
		//
		// 최종 위치:
		// 상자 중심에서 360만큼 위
		//
		// 실제 상승 거리:
		// 360 - 120 = 240
		//----------------------------------------------------
		const float CARD_START_OFFSET_Y =
			120.0f * _2X;

		const float CARD_END_OFFSET_Y =
			240.0f * _2X;

		//----------------------------------------------------
		// X와 Y 모두 상자 좌표 기준
		//----------------------------------------------------
		const float CARD_CENTER_X =
			boxMark[0].x;

		const float CARD_START_Y =
			boxMark[0].y +
			CARD_START_OFFSET_Y;

		const float CARD_END_Y =
			boxMark[0].y +
			CARD_END_OFFSET_Y;

		//----------------------------------------------------
		// ���� ù �� ��
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

			SetRectPoint(
				0,
				DY,
				DX,
				DY,
				TOUCH_FUNC_GETGACHACARD);

			break;
		}

		//----------------------------------------------------
		// 모든 보상 공개 완료
		//----------------------------------------------------
		if (gachaOpenCardIdx >=
			boxCardItemCnt[0])
		{
			if (manualCardMarkIdx >= 0)
			{
				memset(
					&boxCardMark[
						manualCardMarkIdx],
						0,
						sizeof(ICONMARK));

				manualCardMarkIdx =
					-1;
			}

			gachaCurrentCardReady =
				false;

			gachaDepth =
				GACHA_DEPTH_SUMMARY;

			break;
		}

		ITEM* item =
			&boxCardItem[0][
				gachaOpenCardIdx];

		//----------------------------------------------------
		// 현재 카드 생성
		//----------------------------------------------------
		if (gachaCurrentCardReady == false)
		{
			//------------------------------------------------
			// 이전 카드 제거
			//------------------------------------------------
			if (manualCardMarkIdx >= 0)
			{
				memset(
					&boxCardMark[
						manualCardMarkIdx],
						0,
						sizeof(ICONMARK));

				manualCardMarkIdx =
					-1;
			}

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

					//------------------------------------------------
					// 카드 뒷면 1번
					//------------------------------------------------
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
					&boxCardMark[markIdx];

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
		// 현재 카드 수동 애니메이션
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

			//------------------------------------------------
			// 1. 상자에서 위로 상승
			//------------------------------------------------
			if (cardAnimFrame <
				CARD_RISE_END)
			{
				progress =
					(float)cardAnimFrame /
					(float)CARD_RISE_FRAME;

				if (progress < 0.0f)
					progress = 0.0f;

				if (progress > 1.0f)
					progress = 1.0f;

				curve =
					1.0f -
					powf(
						1.0f -
						progress,
						3.0f);

				drawCenterX =
					CARD_CENTER_X;

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

			//------------------------------------------------
			// 2. 도착 충격으로 살짝 축소
			//------------------------------------------------
			else if (cardAnimFrame <
				CARD_IMPACT_END)
			{
				progress =
					(float)(
						cardAnimFrame -
						CARD_RISE_END) /
					(float)CARD_IMPACT_FRAME;

				if (progress < 0.0f)
					progress = 0.0f;

				if (progress > 1.0f)
					progress = 1.0f;

				drawCenterX =
					CARD_CENTER_X;

				drawCenterY =
					CARD_END_Y;

				drawZoom =
					CARD_OVERSHOOT_ZOOM +
					(CARD_PRESSED_ZOOM -
						CARD_OVERSHOOT_ZOOM) *
					progress;

				card->openFrame =
					1;
			}

			//------------------------------------------------
			// 3. 최종 크기로 복원
			//------------------------------------------------
			else if (cardAnimFrame <
				CARD_RECOVER_END)
			{
				progress =
					(float)(
						cardAnimFrame -
						CARD_IMPACT_END) /
					(float)CARD_RECOVER_FRAME;

				if (progress < 0.0f)
					progress = 0.0f;

				if (progress > 1.0f)
					progress = 1.0f;

				curve =
					1.0f -
					(1.0f - progress) *
					(1.0f - progress);

				drawCenterX =
					CARD_CENTER_X;

				drawCenterY =
					CARD_END_Y;

				drawZoom =
					CARD_PRESSED_ZOOM +
					(CARD_FINAL_ZOOM -
						CARD_PRESSED_ZOOM) *
					curve;

				card->openFrame =
					1;
			}

			//------------------------------------------------
			// 4. 카드 뒷면으로 잠시 정지
			//------------------------------------------------
			else if (cardAnimFrame <
				CARD_HOLD_END)
			{
				drawCenterX =
					CARD_CENTER_X;

				drawCenterY =
					CARD_END_Y;

				drawZoom =
					CARD_FINAL_ZOOM;

				card->openFrame =
					1;
			}

			//------------------------------------------------
			// 5. 뒷면 애니메이션 1~7
			//------------------------------------------------
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

				if (backFrame < 1) {
					backFrame = 1;
				}
				
				if (backFrame == CARD_BACK_FRAME_COUNT - 1)
				{
					PlayMusic(M_CARDSPLIT);
				}

				if (backFrame >
					CARD_BACK_FRAME_COUNT)
				{
					backFrame =
						CARD_BACK_FRAME_COUNT;
				}

				drawCenterX =
					CARD_CENTER_X;

				drawCenterY =
					CARD_END_Y;

				drawZoom =
					CARD_FINAL_ZOOM;

				card->openFrame =
					backFrame;
			}

			//------------------------------------------------
			// 6. 앞면 공개
			//------------------------------------------------
			else
			{
				drawCenterX =
					CARD_CENTER_X;

				drawCenterY =
					CARD_END_Y;

				drawZoom =
					CARD_FINAL_ZOOM;

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
		// 앞면 공개 이후 다음 탭 허용
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
		// MENU_IMG ���� ��ġ
		const int PANEL_SRC_X = 0;
		const int PANEL_SRC_Y = 606;
		const int PANEL_SRC_W = 400;
		const int PANEL_SRC_H = 409;

		// MENU_IMG ���콺 ��ġ
		const int BTN_SRC_X = 401;
		const int BTN_SRC_Y = 606;
		const int BTN_SRC_W = 216;
		const int BTN_SRC_H = 68;

		// ��� ȭ�� ǥ�� ũ��
		float panelDisplayW = 400;
		float panelZoom = 1.0f;
		float panelDisplayH = PANEL_SRC_H * panelZoom;

		// ��� ȭ�� �߽� ��ġ
		float panelCX = xOffset + DX / 2.0f;
		float panelCY = DY / 2.0f + panelDisplayH * 0.05f;

		//----------------------------------------------------
		// ��ø ������ (summaryFrame == 0)
		//----------------------------------------------------
		if (summaryFrame == 0)
		{
			manualCardMarkIdx = -1;
			gachaCurrentCardReady = false;
			memset(boxCardMark, 0, sizeof(boxCardMark));
			PlayMusic(M_CARDSPLIT);
		}

		//----------------------------------------------------
		// ��� ȭ�鿡 ī�� ī�带 DrawImage�� �׸���
		//----------------------------------------------------
		DrawImage(
			PANEL_SRC_W, PANEL_SRC_H,
			PANEL_SRC_X, PANEL_SRC_Y,
			panelCX - panelDisplayW / 2.0f,
			panelCY - panelDisplayH / 2.0f,
			false, false, false, false, false,
			panelZoom,
			sprite[MENU_IMG],
			gScreenBuffer, gScreenLayer, MENU_IMG, false);

		//----------------------------------------------------
		// ī�� ���̾ƿ� ���
		//----------------------------------------------------
		int count = boxCardItemCnt[0];
		int numCols, numRows;

		if (count <= 1)       numCols = 1;
		else if (count <= 4)  numCols = 2;
		else                  numCols = 3;

		numRows = (count + numCols - 1) / numCols;

		float cardGap = 4.0f * _2X;
		float innerW = panelDisplayW * 0.84f;
		float cardZoom =
			(innerW - cardGap * (numCols - 1)) /
			(numCols * 240.0f);

		float cardW = 240.0f * cardZoom;
		float cardH = 332.0f * cardZoom;
		float gridW = numCols * cardW + (numCols - 1) * cardGap;
		float gridH = numRows * cardH + (numRows - 1) * cardGap;

		// ������ ���̺��(72px ������) ���̿� ư ���(40*_2X) Ȯ�б� ����
		float ribbonH = 72.0f * panelZoom;
		float btnAreaH = 40.0f * _2X;
		float contentTop =
			panelCY + panelDisplayH / 2.0f - ribbonH;
		float contentBottom =
			panelCY - panelDisplayH / 2.0f + btnAreaH;
		float gridCY = (contentTop + contentBottom) / 2.0f;

		// ù ��° ī�� ���(��) Y ��ġ
		float row0Bottom =
			gridCY + gridH / 2.0f - cardH;

		float gridStartX =
			panelCX - gridW / 2.0f;

		//----------------------------------------------------
		// DrawItemCard�� ī�带 ������
		//----------------------------------------------------
		for (i = 0; i < count; i++)
		{
			int itemCol = i % numCols;
			int itemRow = i / numCols;

			ITEM* item = &boxCardItem[0][i];

			float cx =
				gridStartX +
				itemCol * (cardW + cardGap);

			float cy =
				row0Bottom -
				itemRow * (cardH + cardGap);

			DrawItemCard(
				item->type,
				item->detail,
				item->grade,
				item->lv,
				false,
				(int)cx,
				(int)cy,
				false,
				cardZoom,
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
		// 요약 화면 탭
		//----------------------------------------------------
		if (summaryFrame > FPS / 2)
		{
			// ���콺 ư
			float btnZoom =
				(100.0f * _2X) / BTN_SRC_W;
			float btnDisplayW = BTN_SRC_W * btnZoom;
			float btnDisplayH = BTN_SRC_H * btnZoom;

			float btnX =
				panelCX - btnDisplayW / 2.0f;
			float btnY =
				panelCY -
				panelDisplayH / 2.0f +
				8.0f * _2X;

			DrawImage(
				BTN_SRC_W, BTN_SRC_H,
				BTN_SRC_X, BTN_SRC_Y,
				btnX, btnY,
				false, false, false, false, false,
				btnZoom,
				sprite[MENU_IMG],
				gScreenBuffer, gScreenLayer, MENU_IMG, false);

			//----------------------------------------------------
			// 요약 화면 탭
			//----------------------------------------------------
			SetAlpha(
				32 -
				Abs(frame / MOTIONDIV % 32 - 16));

			DrawGoldAlpha(
				(int)panelCX,
				(int)(btnY + btnDisplayH / 2.0f),
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

		summaryFrame++;

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

			gachaCurrentCardReady =
				false;

			memset(
				boxMark,
				0,
				sizeof(boxMark));

			memset(
				boxCardMark,
				0,
				sizeof(boxCardMark));

			OutOfGacha();
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

	//if (touchFunc != TOUCH_FUNC_GETGACHACARD)
	//	return;

	// 실제 프로젝트의 터치 업 조건 사용
	//if (touchUp == false)
	//	return;	

	//touchFunc = TOUCH_FUNC_NONE;

	switch (gachaDepth)
	{
	case GACHA_DEPTH_CARD:
		//----------------------------------------------------
		// 현재 카드 제거
		//----------------------------------------------------
		if (gachaOpenCardIdx <
			boxCardItemCnt[0])
		{
			memset(
				&boxCardMark[gachaOpenCardIdx],
				0,
				sizeof(
					boxCardMark[
						gachaOpenCardIdx]));
		}

		gachaOpenCardIdx++;
		gachaCurrentCardReady = false;
		gachaFrame = 0;

		if (gachaOpenCardIdx >=
			boxCardItemCnt[0])
		{
			gachaDepth =
				GACHA_DEPTH_SUMMARY;

			gachaFrame = 0;

			memset(
				&boxCardMark,
				0,
				sizeof(boxCardMark));
		}

		break;

	case GACHA_DEPTH_SUMMARY:
		gachaDepth = GACHA_DEPTH_GETITEM;
		gachaFrame = 0;
		break;
	}
}


