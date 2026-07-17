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

		// 기존 보유 여부에 따라 NEW
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
		DY + 64 * _2X,

		xOffset + DX / 2,
		BOTTOMMENUHEIGHT + 32 * _2X,

		4 * _2X / MOTIONDIV,
		4 * _2X / MOTIONDIV,

		32 * _2X / MOTIONDIV,
		4 * _2X / MOTIONDIV,

		FPS * 3,
		FPS * 3,

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
	int i;
	int row = 2;
	int col = 2;

	float zoom = 1.5f;
	int gap = 8 * _2X;

	//--------------------------------------------------------
	// 준비되지 않았다면 현재 적의 상자로 초기화
	//--------------------------------------------------------
	if (gachaPrepared == false)
		PrepareEnemyGacha();

	//--------------------------------------------------------
	// 보상 개수에 따른 요약 배치
	//--------------------------------------------------------
	switch (boxCardItemCnt[0])
	{
	case 1:
		row = 1;
		col = 1;
		zoom = 2.5f;
		gap = 0;
		break;

	case 2:
		row = 2;
		col = 1;
		zoom = 2.0f;
		gap = 16 * _2X;
		break;

	case 3:
		row = 3;
		col = 1;
		zoom = 1.8f;
		gap = 16 * _2X;
		break;

	case 4:
		row = 2;
		col = 2;
		zoom = 1.8f;
		gap = 16 * _2X;
		break;

	case 5:
	case 6:
		row = 3;
		col = 2;
		zoom = 1.8f;
		gap = 16 * _2X;
		break;

	case 7:
	case 8:
		row = 4;
		col = 2;
		zoom = 1.5f;
		gap = 16 * _2X;
		break;

	default:
		row = 4;
		col = 3;
		zoom = 1.5f;
		gap = 16 * _2X;
		break;
	}

	//--------------------------------------------------------
	// 전투 화면 위 어두운 오버레이
	//--------------------------------------------------------
	ScreenDarken(SCREENDARKEN);

	switch (gachaDepth)
	{
		//--------------------------------------------------------
		// 상자 낙하 및 오픈
		//--------------------------------------------------------
	case GACHA_DEPTH_BOX:
	{
		if (gachaFrame < GACHADELAY_OPENPLACE)
		{
			if (gachaFrame ==
				GACHADELAY_OPENPLACE - 1)
			{
				boxMark[0].frame2 = 1;
			}
		}
		else if (gachaFrame < GACHADELAY_BOXDROP)
		{
			if (boxMark[0].y > STATUSWIN_Y)
				boxMark[0].y -= TSIZE;

			if (boxMark[0].y < STATUSWIN_Y)
				boxMark[0].y = STATUSWIN_Y;
		}
		else if (gachaFrame < GACHADELAY_BOXOPEN)
		{
			if (gachaFrame == GACHADELAY_BOXDROP)
			{
				// boxMark가 현재 적의 상자를 표시
				boxMark[0].jokboIcon = true;

				PlayMusic(M_OPENDOOR);
			}
		}
		else
		{
			//------------------------------------------------
			// 상자가 완전히 열린 뒤 첫 카드 공개 상태로 이동
			//------------------------------------------------
			gachaDepth = GACHA_DEPTH_CARD;
			gachaFrame = 0;
			gachaOpenCardIdx = 0;
			gachaCurrentCardReady = false;
		}

		break;
	}

	//--------------------------------------------------------
	// 상자에서 보상을 한 장씩 공개
	//--------------------------------------------------------
	case GACHA_DEPTH_CARD:
	{
		ITEM* item;

		if (gachaOpenCardIdx >= boxCardItemCnt[0])
		{
			gachaDepth = GACHA_DEPTH_SUMMARY;
			gachaFrame = 0;
			break;
		}

		item = &boxCardItem[0][gachaOpenCardIdx];

		//----------------------------------------------------
		// 아직 현재 카드가 생성되지 않았다면 생성
		//----------------------------------------------------
		if (gachaCurrentCardReady == false)
		{
			float targetZoom = 2.2f;

			startX = xOffset + DX / 2;
			startY = STATUSWIN_Y;

			targetX = xOffset + DX / 2;
			targetY = DY / 2 + 80 * _2X;

			SetBoxCardMark(
				startX,
				startY,

				targetX,
				targetY,

				false,
				false,

				32 * _2X / MOTIONDIV,
				4 * _2X / MOTIONDIV,

				false,
				false,

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

				false,

				0.2f / MOTIONDIV,
				targetZoom,
				0.8f / MOTIONDIV,

				false,
				false,
				false,
				false,

				item->seen == false);

			gachaCurrentCardReady = true;
			gachaFrame = 0;

			//------------------------------------------------
			// 등급별 효과음
			//------------------------------------------------
			if ((item->type == ITEM_CREW ||
				item->type >= ITEM_SWORD) &&
				item->grade >= 4)
			{
				// 고등급 전용 효과음
				// PlayMusic(M_GACHA_BIG);
			}
			else
			{
				PlayMusic(M_ITEM);
			}
		}

		//----------------------------------------------------
		// 카드 뒤 등급별 빛 효과
		//----------------------------------------------------
		DrawGachaItemEffect(
			item,
			xOffset + DX / 2,
			DY / 2 + 80 * _2X,
			gachaFrame);

		//----------------------------------------------------
		// 터치 안내
		//----------------------------------------------------
		if (gachaFrame > FPS / 3)
		{
			SetAlpha(
				32 -
				Abs(frame / MOTIONDIV % 32 - 16));

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

			CenterText(
				TEXT_AUTOEQUIP,
				xOffset + DX / 2,
				BOTTOMMENUHEIGHT + 16 * _2X,
				1.0f,
				gScreenBuffer,
				gScreenLayer,
				false);

			SetRectPoint(
				0,
				DY,
				DX,
				DY,
				TOUCH_FUNC_GETGACHACARD);
		}

		break;
	}

	//--------------------------------------------------------
	// 최종 획득 보상 요약
	//--------------------------------------------------------
	case GACHA_DEPTH_SUMMARY:
	{
		float panelX;
		float panelY;
		int panelW;
		int panelH;

		panelX = xOffset + DX / 2;
		panelY = DY / 2 + 120 * _2X;

		panelW = 304 * _2X;
		panelH = 360 * _2X;

		//--------------------------------------------------------
		// 기존 프레임 리소스로 요약 패널 출력
		//--------------------------------------------------------
		DrawFrame(
			(int)(panelX - panelW / 2),
			(int)(panelY - panelH / 2),
			panelW,
			panelH,
			FRAME_SHOPBALLOON,
			gScreenBuffer,
			gScreenLayer,
			false);

		//--------------------------------------------------------
		// 제목
		//--------------------------------------------------------
		CenterText(
			TEXT_AUTOEQUIP,
			(int)panelX,
			(int)(panelY + panelH / 2 - 32 * _2X),
			1.0f,
			gScreenBuffer,
			gScreenLayer,
			false);

		//--------------------------------------------------------
		// 처음 진입했을 때 요약용 카드 마크 생성
		//--------------------------------------------------------
		if (gachaFrame == 0)
		{
			memset(
				&boxCardMark,
				0,
				sizeof(boxCardMark));

			for (i = 0; i < boxCardItemCnt[0]; i++)
			{
				int itemRow;
				int itemCol;

				float contentWidth;
				float itemX;
				float itemY;

				ITEM* item;

				itemRow = i / row;
				itemCol = i % row;

				contentWidth =
					(float)(
						REWARDCARDSIZE_X * zoom * row +
						gap * (row - 1));

				itemX =
					panelX -
					contentWidth / 2 +
					(float)(
						REWARDCARDSIZE_X * zoom +
						gap) *
					itemCol +
					(float)(
						REWARDCARDSIZE_X * zoom) / 2;

				itemY =
					panelY +
					(float)(
						REWARDCARDSIZE_Y * zoom *
						(col - 1)) / 2 -
					(float)(
						REWARDCARDSIZE_Y * zoom +
						gap) *
					itemRow;

				item = &boxCardItem[0][i];

				SetBoxCardMark(
					panelX,
					panelY,

					itemX,
					itemY,

					false,
					false,

					32 * _2X / MOTIONDIV,
					4 * _2X / MOTIONDIV,

					false,
					false,

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

					false,

					0.2f / MOTIONDIV,
					zoom,
					0.8f / MOTIONDIV,

					false,
					false,
					false,
					false,

					item->seen == false);
			}

			PlayMusic(M_CARDSPLIT);
		}

		//--------------------------------------------------------
		// 터치 안내
		//--------------------------------------------------------
		if (gachaFrame > FPS / 2)
		{
			SetAlpha(
				32 -
				Abs(frame / MOTIONDIV % 32 - 16));

			DrawGoldAlpha(
				(int)panelX,
				(int)(panelY - panelH / 2 + 32 * _2X),
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

			CenterText(
				TEXT_AUTOEQUIP,
				(int)panelX,
				(int)(panelY - panelH / 2 + 16 * _2X),
				1.0f,
				gScreenBuffer,
				gScreenLayer,
				false);

			SetRectPoint(
				0,
				DY,
				DX,
				DY,
				TOUCH_FUNC_GETGACHACARD);
		}

		break;
	}

	//--------------------------------------------------------
	// 실제 보상 지급 및 종료
	//--------------------------------------------------------
	case GACHA_DEPTH_GETITEM:
	{
		if (gachaRewardReceived == false)
		{
			gachaRewardReceived = true;

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

				//------------------------------------------------
				// 장비일 때만 최강 장비 갱신
				//------------------------------------------------
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

		if (gachaFrame > FPS / 3)
		{
			gachaPrepared = false;

			memset(
				&boxMark,
				0,
				sizeof(boxMark));

			memset(
				&boxCardMark,
				0,
				sizeof(boxCardMark));

			OutOfGacha();
			return;
		}

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


