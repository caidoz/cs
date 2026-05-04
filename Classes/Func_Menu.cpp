#pragma once
#include "Core.h"
#include "Func.h"
#include "Text.h"
#include "Data.h"

// Menu & UI 관련 함수
//뉴스 드로우
void NewsDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], cvtDest, cvtLayer, UI_PAPER_POPUP_IMG, buffering);

}
//선물함 드로우
void GiftDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], cvtDest, cvtLayer, UI_PAPER_POPUP_IMG, buffering);

}

//친구와의 전투 드로우
void GuildEventDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i, j, tempIdx, mul = 1;
	int week = 0;
	int dayOfWeek = 1;
	int dayOfMonth = robin.calendarMonthDay;

	DrawImage((float)POPUPWINDOWSIZE_X * zoom, (float)(POPUPWINDOWSIZE_Y)*zoom, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], cvtDest, cvtLayer, UI_PAPER_POPUP_IMG, buffering);

	switch (menuDepth) {

	case 0:
		//여기서는 그냥 리스트를 그려준다.
		//하루에 세가지
		for (i = 0; i < 3; i++) {
			MemRectRound(x + (float)(32 * _2X) * zoom, y - (float)(48 * _2X + 80 * _2X * i) * zoom, (float)(256 * _2X) * zoom, (float)(72 * _2X) * zoom, COLOR_BROWN, 2, cvtDest, cvtLayer, buffering);

			//DrawFrame(x + (float)32 * _2X * zoom, y - (float)(48 * _2X + 80 * _2X * i) * zoom, (float)256 * _2X * zoom, (float)72 * _2X * zoom, COLOR_LIGHTBROWN, )
		}
	case 1:
		//여기서 각종 획득 이펙트를 그려준다.

		break;
	}


	//현재 데일리 이벤트까지 남는 시간
	DrawTime(x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y + (float)(-440 * _2X) * zoom, Max(0, 86400 - (MC_knlCurrentTimeStamp() - robin.calendarTimeStamp)), TIME_HOUR_MINUTE, CENTER, zoom, cvtDest, cvtLayer, buffering);


}

void DailyQuestDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i, j, tempIdx, mul = 1;
	int week = 0;
	int dayOfWeek = 1;
	int dayOfMonth = robin.calendarMonthDay;
	int boxOpenFrame;
	int dailyQuestType;

	float NPCZOOM = 1.3f;

	int stageBossIdx = GetStageBossIdx();
	int stageBossType = GetStageBossType();


	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], cvtDest, cvtLayer, UI_PAPER_POPUP_IMG, buffering);

	switch (menuDepth) {

	case 0:
		//여기서는 그냥 리스트를 그려준다.
		//하루에 세가지
		for (i = 0; i < 3; i++) {
			//for (i = 0; i < TOTAL_DAILYQUEST_TYPE; i++) {
			MemRectRound(x + (float)(20 * _2X) * zoom, y - (float)(64 * _2X + 72 * _2X * i) * zoom, (float)(280 * _2X) * zoom, (float)(64 * _2X) * zoom, COLOR_BEIGE, 2 * _2X, cvtDest, cvtLayer, buffering);

			dailyQuestType = i;

			switch (i) {
				//상자를 열어서 장비를 얻어라
			case DAILYQUEST_OPEN_BOX_GETEQUIP:
				//상자를 여세요
				DrawNeutral(OBJ_BOX0 + boxOpenAnimation[((frame / (MOTIONDIV * 2)) % 20)], x + (float)(20 * _2X + 32 * _2X) * zoom, y - (float)(64 * _2X + 60 * _2X + 72 * _2X * i) * zoom, LEFT, 2.0f * zoom, cvtDest, cvtLayer, buffering);
				if (frame / (MOTIONDIV) % 40 > 16/* && ((frame / (MOTIONDIV * 2)) % 20) < 16*/) {
					boxOpenFrame = ((frame / (MOTIONDIV)) % 40) - 16;

					for (j = 0; j < 3; j++)
						DrawIcon(GetItemIcon(boxOpenItemFrameInfo[boxOpenFrame * 3 * BOXOPENITEMFRAMEINFOSIZE + BOXOPENITEMFRAMEINFOSIZE * j + 0], boxOpenItemFrameInfo[boxOpenFrame * 3 * BOXOPENITEMFRAMEINFOSIZE + BOXOPENITEMFRAMEINFOSIZE * j + 1], boxOpenItemFrameInfo[boxOpenFrame * 3 * BOXOPENITEMFRAMEINFOSIZE + BOXOPENITEMFRAMEINFOSIZE * j + 2]), x + (float)(20 * _2X + 32 * _2X) * zoom + (float)boxOpenItemFrameInfo[boxOpenFrame * 3 * BOXOPENITEMFRAMEINFOSIZE + BOXOPENITEMFRAMEINFOSIZE * j + 3] * zoom, y - (float)(64 * _2X + 60 * _2X + 72 * _2X * i) * zoom + (float)boxOpenItemFrameInfo[boxOpenFrame * 3 * BOXOPENITEMFRAMEINFOSIZE + BOXOPENITEMFRAMEINFOSIZE * j + 4] * zoom, (float)boxOpenItemFrameInfo[boxOpenFrame * 3 * BOXOPENITEMFRAMEINFOSIZE + BOXOPENITEMFRAMEINFOSIZE * j + 5] * zoom, COLOR_WHITE, true, true, 1, cvtDest, cvtLayer, buffering);
				}

				break;
				//국경수비대를 업그레이드를 해라
			case DAILYQUEST_UPGRADE_CREW:
				ao[NPC].x = x + (float)(28 * _2X + 24 * _2X) * zoom;
				ao[NPC].y = y - (float)(52 * _2X * NPCZOOM + 72 * _2X * i) * zoom - (float)(8 * _2X + 24 * _2X) * NPCZOOM * zoom;

				DrawImage(32 * _2X, 12 * _2X, 107 * _2X, 48 * _2X, ao[NPC].x - (float)16 * _2X * NPCZOOM * zoom, ao[NPC].y + (float)(2 * _2X) * NPCZOOM * zoom, false, false, false, false, false, NPCZOOM * zoom, sprite[MAP_OBJ_IMG + 6], cvtDest, cvtLayer, MAP_OBJ_IMG + 6, buffering);

				DrawCmfDetailShadow(enemyData[crewData[(robin.stage * MAXCREW + MAXCREW - 1) * CREWDATASIZE] * ENEMYDATASIZE + 0], enemyIconPos[crewData[(robin.stage * MAXCREW + MAXCREW - 1) * CREWDATASIZE] * 3 + 0], ao[NPC].x, ao[NPC].y, RIGHT, enemyIconZoom[crewData[(robin.stage * MAXCREW + MAXCREW - 1) * CREWDATASIZE]] * NPCZOOM * zoom, cvtDest, cvtLayer, buffering);
				break;
				//다른 유저를 공격해라
			case DAILYQUEST_ATTACK_OTHERUSER:
				EnemyUserProfileDraw(&enemyHouse, x + (float)(20 * _2X + 28 * _2X - 20 * _2X) * zoom, y - (float)(58 * _2X + 72 * _2X * i) * zoom, zoom, cvtDest, cvtLayer, buffering);
				break;
			case DAILYQUEST_COLLECT_GOLD:
				DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, x + (float)(20 * _2X + 12 * _2X) * zoom, y - (float)(80 * _2X + 72 * _2X * i) * zoom, 2.5f * zoom, false, false, false, 1, cvtDest, cvtLayer, buffering);
				break;
			case DAILYQUEST_STAGE_TRY:
				DrawBox(stageClearBox[robin.stage], x + (float)(20 * _2X + 32 * _2X + 24 * _2X) * zoom, y - (float)(64 * _2X + 60 * _2X + 72 * _2X * i) * zoom, LEFT, boxNeutralAnimation[((frame / (MOTIONDIV * 2 * 2)) % 4)], COLOR_WHITE, true, false, true, 1.2f * zoom / 1.2f, cvtDest, cvtLayer, buffering);

				DrawCmfDetailShadow(enemyData[stageBossType * ENEMYDATASIZE + ENEMYDATA_CMF], crewPos[stageBossType * 5 + 0] + (frame / 2 % crewPos[stageBossType * 5 + 1]), x + (float)(20 * _2X + 28 * _2X) * zoom, y - (float)(64 * _2X + 60 * _2X + 72 * _2X * i) * zoom, LEFT, /*enemyIconZoom[stageBossType] **/ zoom / 1.2f, cvtDest, cvtLayer, buffering);

				DrawStageLabel(x + (float)(20 * _2X + 28 * _2X) * zoom, y - (float)(64 * _2X + 60 * _2X - 60 * _2X + 72 * _2X * i) * zoom, TEXT_STAGE, robin.stage, robin.room, true, zoom / 1.2f, cvtDest, cvtLayer, buffering);

				break;

			}
			//DrawFrame(x + (float)(32 * _2X + 28 * _2X + 48 * _2X) * zoom, y - (float)(64 * _2X + 32 * _2X + 72 * _2X * i) * zoom, float(DAILYQUESTBARWIDTH) * zoom, float(DAILYQUESTBARHEIGHT) * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
			//DrawWindow2(x + (float)(32 * _2X + 20 * _2X + 48 * _2X) * zoom, y - (float)(64 * _2X + 16 * _2X + 72 * _2X * i) * zoom, float(DAILYQUESTBARWIDTH), float(DAILYQUESTBARHEIGHT), COLOR_NAVY, zoom, cvtDest, cvtLayer, buffering);
			DrawText(TEXT_DAILYQUEST_OPEN_BOX_GETEQUIP + i, x + (float)(20 * _2X + 32 * _2X + 40 * _2X) * zoom, y - (float)(64 * _2X + 12 * _2X + 72 * _2X * i) * zoom, zoom, cvtDest, cvtLayer, buffering);
			DrawGuage(x + (float)(20 * _2X + 28 * _2X + 40 * _2X) * zoom, y - (float)(64 * _2X + 32 * _2X + 72 * _2X * i) * zoom, float(DAILYQUESTBARWIDTH) * zoom, float(DAILYQUESTBARHEIGHT) * zoom, 10, 30, COLOR_NAVY, COLOR_HEARTBAR, zoom, cvtDest, cvtLayer, buffering);
			DrawRewardCard(i, i, i, false, 1, x + (float)(20 * _2X + 28 * _2X + 204 * _2X) * zoom, y - (float)(64 * _2X + 4 * _2X + 72 * _2X * i) * zoom, false, zoom, true, false, true, GetItemStar(i, i, i), GetItemStar(i, i, i), true, cvtDest, cvtLayer, buffering);
		}
	case 1:
		//여기서 각종 획득 이펙트를 그려준다.

		break;
	}


	//현재 데일리 이벤트까지 남는 시간
	DrawTime(x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y + (float)(-440 * _2X) * zoom, Max(0, 86400 - (MC_knlCurrentTimeStamp() - robin.calendarTimeStamp)), TIME_HOUR_MINUTE, CENTER, zoom, cvtDest, cvtLayer, buffering);

}


void ShopDraw_Back(int x, int y, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i;
	ITEM* it;

	switch (menuDepth) {
	case 0:
		switch (menuIdx) {
		default:

			MemRectRound(x, y, DX, DY, 0x1D2B47, 1 * _2X, cvtDest, cvtLayer, buffering);
			DrawBackMap_Back(x, DY / 2 - 320 * _2X / 2, TOLEMHOUSE2, 1.0f, cvtDest, cvtLayer, buffering);

			break;
		}
		break;
	case 1:
		break;
	case 2:
		break;
	}
}

void ShopDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i, tempIdx, mul = 1;

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y - (float)(POPUPSTORE_Y + 16 * _2X) * zoom, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], gScreenBuffer, gScreenLayer, UI_PAPER_POPUP_IMG, false);

	switch (menuDepth) {
	case 0:
		switch (menuIdx) {
		default:
			//상단의 팝업스토어
			for (i = 0; i < TOTALPOPUPSTORE; i++) {
				DrawFrame(x + (float)32 * _2X * zoom + scX + (float)DX * zoom * (i - menuX), y, (float)(DX - 64 * _2X) * zoom, (float)POPUPSTORE_Y * zoom, FRAME_SHOPBALLOON, gScreenBuffer, gScreenLayer, false);
				DrawNumTTF(i + 1, x + (float)34 * _2X * zoom + scX + (float)DX * zoom * (i - menuX), y - (float)2 * _2X * zoom, NUM_FONT_LARGE, LEFT, false, false, false, 1.0f, false, gScreenBuffer, gScreenLayer, false);
			}

			for (i = 0; i < TOTALPOPUPSTORE; i++) {
				if (i == TOTALPOPUPSTORE - 1) {
					if ((long)(currentTimeStamp - robin.freeRewardTimeStamp) >= FREEITEMTIME) {
						SetAlpha(32 - Abs(frame / MOTIONDIV % 32 - 16));
						SetColor(COLOR_REALRED);
					}
					else
						SetColor(COLOR_RED);
				}

				DrawImage(9 * _2X, 9 * _2X, (menuX == i ? 145 * _2X : 154 * _2X), 0 * _2X, x + (float)((DX / 2 - (16 * 4 + 9) * _2X / 2) + i * 16 * _2X) * zoom, y - (float)POPUPSTORE_Y * zoom - (float)4 * _2X * zoom, false, false, false, false, false, zoom, sprite[COMMON_IMG], gScreenBuffer, gScreenLayer, COMMON_IMG, false);
				SetColor(false);
				SetAlpha(32);
			}

			return;
			//하트상품 6개
			//y -= GNBHEIGHT;

			DrawLabel(x + (float)(POPUPWINDOWSIZE_X / 2 - 40 * _2X) * zoom, y + (float)16 * _2X * zoom, TEXT_SHOP_HEART_TITLE, zoom, gScreenBuffer, gScreenLayer, false);

			for (i = 0; i < 6; i++) {

				//if (zoom == 1)
				//	SetRectPoint(x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3)) * zoom, y + (float)(-40 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3)) * zoom, (float)SHOPMENUCARD_WIDTH * zoom, (float)SHOPMENUCARD_HEIGHT * zoom, TOUCH_FUNC_EQUIP_INVENTORY + i);

				DrawImage(72 * _2X, 64 * _2X, 0 * _2X, 0 * _2X, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + (SHOPMENUCARD_WIDTH - 72 * _2X) / 2) * zoom, y + (float)(-16 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - (SHOPMENUCARD_HEIGHT - 88 * _2X) / 2) * zoom, false, false, false, false, false, zoom, sprite[HEART_0_IMG + i], gScreenBuffer, gScreenLayer, HEART_0_IMG + i, false);

				//하트수량
				DrawNum(currencyShop[0 * 7 + i * 7 + 4], x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + SHOPMENUCARD_WIDTH / 2) * zoom, y + (float)(-16 * _2X - (SHOPMENUCARD_HEIGHT) * (i / 3)) * zoom, NUM_FONT_NORMAL, CENTER, 0, false, true, zoom, true, gScreenBuffer, gScreenLayer, false);

				if (currencyShop[0 * 7 + i * 7 + 2]) {
					memset(tempStr, 0, sizeof(tempStr));
					sprintf(tempStr, "+%d%%", currencyShop[0 * 7 + i * 7 + 2]);
					//보너스 숫자
					CenterTextStr(tempStr, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + SHOPMENUCARD_WIDTH / 2) * zoom, y + (float)(-16 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 36 * _2X) * zoom, zoom, gScreenBuffer, gScreenLayer, false);
				}
				//아이콘

				//DrawNeutral(OBJ_ITEM0 + (frame + i) % 4, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + (SHOPMENUCARD_WIDTH - 16 * _2X * 2) / 2 + ITEMICONSIZE) * zoom, y + (float)(- 16 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 52 * _2X) * zoom, LEFT, (float)2 * zoom, gScreenBuffer, gScreenLayer, false);

				DrawBuyButton(x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + 6 * _2X) * zoom, y + (float)(-16 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - SHOPMENUCARD_HEIGHT + 34 * _2X) * zoom, (float)(SHOPMENUCARD_WIDTH - 12 * _2X) * zoom, (float)(RAIDGOLDBARHEIGHT)*zoom, frame, 0, currencyShop[0 * 7 + i * 7 + 6], currencyShop[0 * 7 + i * 7 + 5], zoom, false, false, false, gScreenBuffer, gScreenLayer, false);
			}

			y -= (float)(208 * _2X) * zoom;

			//장비뽑기 3종
			DrawLabel(x + (float)(POPUPWINDOWSIZE_X / 2 - 40 * _2X) * zoom, y, TEXT_SHOP_GACHA_TITLE, zoom, gScreenBuffer, gScreenLayer, false);

			for (i = 0; i < 3; i++) {
				ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + (SHOPMENUCARD_WIDTH - 16 * _2X * 2) / 2 - 4 * _2X) * zoom, y + (float)(-40 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 46 * _2X - 20 * _2X) * zoom, SHADOW_IMG, zoom, gScreenBuffer, gScreenLayer, false);
				DrawBoxSpecial(x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + (SHOPMENUCARD_WIDTH - 16 * _2X * 2) / 2 - 4 * _2X + 20 * _2X - (BOXSIZE_X / 2)) * zoom, y + (float)(-40 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 50 * _2X + BOXSIZE_Y) * zoom, LEFT, BOX_EQUIP_SILVER + i, (float)1.0f * zoom, false, false, false, gScreenBuffer, gScreenLayer, false);
				CenterText(TEXT_ITEMNAME_BOX + BOX_EQUIP_SILVER + i, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + SHOPMENUCARD_WIDTH / 2) * zoom, y + (float)(-32 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3)) * zoom, zoom, gScreenBuffer, gScreenLayer, false);

				//DrawNeutral(OBJ_ITEM0 + (frame + i) % 4, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + (SHOPMENUCARD_WIDTH - 16 * _2X * 2) / 2 + ITEMICONSIZE) * zoom, y +(float)(-40 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 26 * _2X - 16 * _2X - ITEMICONSIZE * 2) * zoom, LEFT, (float)2 * zoom, gScreenBuffer, gScreenLayer, false);

				DrawBuyButton(x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + 6 * _2X) * zoom, y + (float)(-32 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - SHOPMENUCARD_HEIGHT + 28 * _2X) * zoom, (float)(SHOPMENUCARD_WIDTH - 12 * _2X) * zoom, (float)(RAIDGOLDBARHEIGHT)*zoom, frame, 0, GetBoxPrice(BOX_EQUIP_SILVER + i, GRADE_NORMAL), GetBoxCurrency(BOX_EQUIP_SILVER + i, GRADE_NORMAL), zoom, false, false, false, gScreenBuffer, gScreenLayer, false);
				if (robin.gold >= GetBoxPrice(BOX_EQUIP_SILVER + i, GRADE_NORMAL))
					SetRectPoint(x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + 6 * _2X) * zoom, y + (float)(-32 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - SHOPMENUCARD_HEIGHT + 28 * _2X) * zoom, (float)(SHOPMENUCARD_WIDTH - 12 * _2X) * zoom, (float)(RAIDGOLDBARHEIGHT)*zoom, TOUCH_FUNC_SHOP_BUYBOX1 + i);
			}

			y -= (float)(128 * _2X) * zoom;

			DrawLabel(x + (float)(POPUPWINDOWSIZE_X / 2 - 40 * _2X) * zoom, y, TEXT_SHOP_COIN_TITLE, zoom, gScreenBuffer, gScreenLayer, false);

			for (i = 0; i < 3; i++) {
				DrawImage(64 * _2X, 52 * _2X, 0 * _2X, 0 * _2X, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + (SHOPMENUCARD_WIDTH - 64 * _2X) / 2) * zoom, y + (float)(-24 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - (SHOPMENUCARD_HEIGHT - 52 * _2X) / 2) * zoom, false, false, false, false, false, zoom, sprite[COIN_0_IMG + 3 + i], gScreenBuffer, gScreenLayer, COIN_0_IMG + 3 + i, false);

				//코인수량
				DrawNum(currencyShop[9 * 7 + i * 7 + 4], x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + SHOPMENUCARD_WIDTH / 2) * zoom, y + (float)(-24 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 8 * _2X) * zoom, NUM_FONT_NORMAL, CENTER, 0, false, true, zoom, true, gScreenBuffer, gScreenLayer, false);

				if (currencyShop[9 * 7 + i * 7 + 2]) {
					memset(tempStr, 0, sizeof(tempStr));
					sprintf(tempStr, "+%d%%", currencyShop[9 * 7 + i * 7 + 2]);
					//보너스 숫자
					CenterTextStr(tempStr, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + SHOPMENUCARD_WIDTH / 2) * zoom, y + (float)(-24 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 52 * _2X) * zoom, zoom, gScreenBuffer, gScreenLayer, false);
				}

				//DrawNeutral(OBJ_ITEM0 + (frame + i) % 4, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + (SHOPMENUCARD_WIDTH - 16 * _2X * 2) / 2 + ITEMICONSIZE) * zoom, y + (float)(- 16 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 26 * _2X - 16 * _2X - ITEMICONSIZE * 2) * zoom, LEFT, (float)2 * zoom, gScreenBuffer, gScreenLayer, false);

				DrawBuyButton(x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + 6 * _2X) * zoom, y + (float)(-32 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - SHOPMENUCARD_HEIGHT + 28 * _2X) * zoom, (float)(SHOPMENUCARD_WIDTH - 12 * _2X) * zoom, (float)(RAIDGOLDBARHEIGHT)*zoom, frame, 0, currencyShop[9 * 7 + i * 7 + 6], currencyShop[9 * 7 + i * 7 + 5], zoom, false, false, false, gScreenBuffer, gScreenLayer, false);
			}

			break;
		}
		break;
	case 1:
		break;
	case 2:
		break;
	}
}
//별 드로우
void StarShopDraw(int x, int y)
{
	DrawCmfPopUp(CMF_NPC_USERQUEST, TEXT_MENU_STARSHOP, x, y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, DX - 120 * _2X, 6, 1, 1.0f, gScreenBuffer, gScreenLayer, false);


}


void HeroDraw(int type, int x, int y, int dirX, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	OBJECT* pObj = &ao[PLAYER];

	if (IsGetHero(type) == false)
		grayScale = 32;
	EnemyProfileDraw(x, y, type, false, (drawHandle == MD_PLAY ? ao[type].lv : false), 1.0f * zoom, cvtDest, cvtLayer, buffering);

	//DrawPlayer(&ao[type], IsGetHero(type) == false ? 0 : frame / 2 % 4, x, y, dirX, HOUSEZOOM * zoom, false, false, true, cvtDest, cvtLayer, buffering);
	grayScale = 0;
	if (IsGetHero(type) == false) {
		DrawLock(getHeroLv[type], x + (float)(+(2 * _2X)) * zoom, y - (float)2 * _2X * zoom, 2.0f * zoom, cvtDest, cvtLayer, buffering);
	}

}

void HeroListDraw(int x, int y, float zoom, bool checkBox, int gap, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i;
	OBJECT* pObj = &ao[PLAYER];

	//DrawFrame(x, y - (float)8 * _2X * zoom, (float)140 * _2X * zoom, (float)64 * _2X * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);

	for (i = 1; i < MAXPLAYER; i++) {
		//DrawFrame(x + (float)8 * _2X * zoom + (gap * (i - 1)) * zoom, y - (float)24 * _2X * zoom, (float)32 * _2X * zoom, (float)32 * _2X * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);

		//SetSectionClip(x + (float)8 * _2X + (gap * (i - 1)) * zoom, y - (float)24 * _2X * zoom, (float)32 * _2X * zoom, (float)32 * _2X * zoom, false);
		HeroDraw(i, x + (float)0 * _2X + (gap * (i - 1)) * zoom, y - (float)24 * _2X * zoom, LEFT, zoom, cvtDest, cvtLayer, buffering);
		//UnSectionClip(false);
	}

	if (drawHandle == MD_PLAY || drawHandle == MD_BATTLE)
		DrawLabel(x + (float)(14 * _2X) * zoom, y - (float)(68 * _2X) * zoom, TEXT_ALPHA_HEROES, 0.72f * zoom, cvtDest, cvtLayer, buffering);

}


void HeroSelectButtonList(int x, int y, float zoom, int selected, bool touchActive, bool horizontal, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i;

	if (horizontal == true) {
		for (i = 0; i < TOTALCHAR; i++) {
			DrawFrame(x + i * (float)(HEROBUTTON_X + 4 * _2X) * zoom, y + (selected == i ? (float)4 * _2X * zoom : 0), (float)HEROBUTTON_X * zoom, (float)HEROBUTTON_Y * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
			DrawPlayer(&ao[i], (i == selected ? frame / 4 % 4 : 0), x + i * (float)(HEROBUTTON_X + 4 * _2X) * zoom + (float)(HEROBUTTON_X / 2) * zoom, y + (selected == i ? (float)4 * _2X * zoom : 0) - (float)(HEROBUTTON_Y - 8 * _2X) * zoom, RIGHT, zoom, false, false, true, cvtDest, cvtLayer, buffering);
			if (i != selected && touchActive == true)
				SetRectPoint(x + i * (float)(HEROBUTTON_X + 4 * _2X) * zoom, y + (selected == i ? (float)4 * _2X * zoom : 0), (float)HEROBUTTON_X * zoom, (float)HEROBUTTON_Y * zoom, TOUCH_FUNC_SELECT_HERO + i);
		}
	}
	else {
		for (i = 0; i < TOTALCHAR; i++) {
			DrawFrame(x - (selected == i ? (float)4 * _2X * zoom : 0), y - i * (float)(HEROBUTTON_Y + 8 * _2X) * zoom, (float)HEROBUTTON_X * zoom, (float)HEROBUTTON_Y * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
			DrawPlayer(&ao[i], (i == selected ? frame / 4 % 4 : 0), x - (selected == i ? (float)4 * _2X * zoom : 0) + (float)(HEROBUTTON_X / 2) * zoom, y - i * (float)(HEROBUTTON_Y + 8 * _2X) * zoom - (float)(HEROBUTTON_Y - 8 * _2X) * zoom, LEFT, zoom, false, false, true, cvtDest, cvtLayer, buffering);
			if (i != selected && touchActive == true)
				SetRectPoint(x - (selected == i ? (float)4 * _2X * zoom : 0), y - i * (float)(HEROBUTTON_Y + 8 * _2X) * zoom, (float)HEROBUTTON_X * zoom, (float)HEROBUTTON_Y * zoom, TOUCH_FUNC_SELECT_HERO + i);
		}
	}
}

void HeroStatDraw(OBJECT* pObj, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i;
	float plusX = (float)(12 * _2X) * zoom;
	float plusY = (float)(-52 * _2X) * zoom;
	const signed short* usPtr;
	//히어로 스탯을 그려준다.
	//DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], cvtDest, cvtLayer, UI_PAPER_POPUP_IMG, false);

	//DrawPlayer(pObj, PO_C0_N0 + (frame / 2 / MOTIONDIV % 4), x + (float)32 * _2X * zoom, y - (float)54 * _2X * zoom, RIGHT, zoom * 2.0f, false, false, true, cvtDest, cvtLayer, buffering);

	//BarDraw(&bar[BAR_GOLD], zoom, cvtDest, cvtLayer, buffering);

	HeroSelectButtonList(x + (float)(4 * _2X) * zoom, DY - (float)8 * _2X * zoom, zoom, curHero, menuDepth == 0 ? true : false, true, cvtDest, cvtLayer, buffering);

	BarDraw(&bar[BAR_COMBATPOWERALL], zoom, cvtDest, cvtLayer, buffering);

	//ExpBarDraw(pObj->lv, pObj->exps, x + (float)52 * _2X * zoom + (float)8 * _2X * zoom, y - (float)32 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

	//DrawCombatPower(GetCombatPower(pObj), ICON_EVENT_2SWORD, x + (float)220 * _2X * zoom, y - (float)32 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

	//InventoryDraw(x + (float)12 * _2X * zoom, y - (float)72 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);
	DrawEquipSlot(x + plusX, y + plusY, zoom, cvtDest, cvtLayer, buffering);

	for (i = TOTALEQUIP - 1; i >= 0; i--) {
		usPtr = &equipSlotPos2[i * 4];

		if (pObj->equip[*usPtr].type < EMPTY) {
			if (pObj->equipImg[*usPtr] == 0)
				grayScale = 20;

			DrawItemIcon(&pObj->equip[*usPtr], pObj, x + plusX + (float)*(usPtr + 2) * zoom, y + plusY + (float)*(usPtr + 3) * zoom, zoom * 2, cvtDest, cvtLayer, buffering);

			MemRectFrameThick(x + plusX + (float)*(usPtr + 2) * zoom - (float)2 * _2X * zoom, y + plusY + (float)*(usPtr + 3) * zoom + (float)2 * _2X * zoom, (float)(ITEMICONSIZE * 2 + 4 * _2X) * zoom, (float)(ITEMICONSIZE * 2 + 4 * _2X) * zoom, itemColor[pObj->equip[*usPtr].grade], (float)1 * _2X * zoom, cvtDest, cvtLayer, buffering);

			if (*usPtr == EQUIP_RING && pObj->equip[EQUIP_RING].cooldown)
				DrawCycle(x + plusX + (float)*(usPtr + 2) * zoom, y + plusY + (float)*(usPtr + 3) * zoom, (float)16 * _2X * 2 * zoom, (float)16 * _2X * 2 * zoom, pObj->equip[EQUIP_RING].cooldown, ringOption[pObj->equip[EQUIP_RING].detail * 7 + 3 + Min(3, pObj->equip[EQUIP_RING].grade)] * 120, zoom, cvtDest, cvtLayer, buffering);

			if (pObj->equipImg[*usPtr] == 0) {
				grayScale = 0;
				SetAlpha(8);
				MemRect(x + plusX + (float)*(usPtr + 2) * zoom, y + plusY + (float)*(usPtr + 3) * zoom, (float)16 * _2X * 2 * zoom, (float)16 * _2X * 2 * zoom, 0xFF0000, cvtDest, cvtLayer, buffering);
				SetAlpha(32);
			}
		}

		if (hotKeyFrame && hotKeyFrame / 10 == *usPtr + 10) {
			DrawEffect(EFFECT_SLOT0 + 7 - (hotKeyFrame % 10), x + plusX + (float)*(usPtr + 2) * zoom + (float)8 * _2X * 2 * zoom, y + plusY + (float)*(usPtr + 3) * zoom - (float)8 * _2X * 2 * zoom, LEFT, false, zoom, cvtDest, cvtLayer, buffering);
			hotKeyFrame--;

			if (hotKeyFrame % 10 == 0)
				hotKeyFrame = 0;
		}
	}

	DrawFrame(x + (float)32 * _2X * zoom, y + plusY - (float)35 * _2X * zoom, (float)(POPUPWINDOWSIZE_X - 64 * _2X) * zoom, (float)120 * _2X * zoom, FRAME_NOFRAME, cvtDest, cvtLayer, buffering);

	//DrawText()
	//HP, MP, EXP 부분
	//hp
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s  %lld  /  %lld", textId[TEXT_ALPHA_HP], pObj->hp, pObj->ps[PS_HP]);
	DrawTextStr(tempStr, x + (float)40 * _2X * zoom, y + plusY - (float)40 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

	//총 공격수치
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s  %lld  -  %lld", textId[TEXT_ALPHA_DAMAGE], RoundDiv(pObj->ps[PS_DMG] * (100 - weaponRange[pObj->equip[EQUIP_WEAPON].type]), 100), RoundDiv(pObj->ps[PS_DMG] * (100 + weaponRange[pObj->equip[EQUIP_WEAPON].type]), 100));
	DrawTextStr(tempStr, x + (float)40 * _2X * zoom, y + plusY - (float)55 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s  %lld", textId[TEXT_ALPHA_DEFENSE], pObj->ps[PS_ARMOR]);
	DrawTextStr(tempStr, x + (float)40 * _2X * zoom, y + plusY - (float)70 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);


	//STR
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s  %lld", textId[TEXT_ALPHA_STR], pObj->ps[PS_STR]);
	DrawTextStr(tempStr, x + (float)40 * _2X * zoom, y + plusY - (float)85 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

	//VIT
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s  %lld", textId[TEXT_ALPHA_VIT], pObj->ps[PS_VIT]);
	DrawTextStr(tempStr, x + (float)(40 + 108) * _2X * zoom, y + plusY - (float)85 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

	//AGI
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s  %lld", textId[TEXT_ALPHA_AGI], pObj->ps[PS_AGI]);
	DrawTextStr(tempStr, x + (float)40 * _2X * zoom, y + plusY - (float)100 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

	//INT
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s  %lld", textId[TEXT_ALPHA_INT], pObj->ps[PS_INT]);
	DrawTextStr(tempStr, x + (float)(40 + 108) * _2X * zoom, y + plusY - (float)100 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

	DrawTextStr(textId[TEXT_ATTRREGIST], x + (float)40 * _2X * zoom, y + plusY - (float)115 * _2X * zoom, 1.2f * zoom, cvtDest, cvtLayer, buffering);

	//저항도
	for (i = 5 - 1; i >= 0; i--) {
		DrawArray(IMG_FLAME + i, x + (float)(40 * _2X + 48 * _2X * i) * zoom, y + plusY - (float)134 * _2X * zoom, 2.0f * zoom, cvtDest, cvtLayer, buffering);
		DrawNum(pObj->ps[PS_FIRE + i], x + (float)(40 * _2X + 24 * _2X + 48 * _2X * i) * zoom, y + plusY - (float)136 * _2X * zoom, NUM_FONT_NORMAL, LEFT, false, false, true, zoom, false, cvtDest, cvtLayer, buffering);
	}

	memset(optionStr, 0, sizeof(optionStr));

	for (i = 0; i < TOTALMENUOPTION; i++) {
		sprintf(optionStr[i], TEXTPTR(TEXT_PREFIX_DESC + optionInfo[i * 2 + 1]), Abs(pObj->ps[optionInfo[i * 2]]));

	}

	for (i = 0; i < TOTALMENUOPTION; i++)
		DrawTextStr(optionStr[i], x + (float)(24 * _2X + 160 * _2X * (i % 2)) * zoom, y + plusY - (float)(162 * _2X + 15 * _2X * (i / 2)) * zoom, zoom, cvtDest, cvtLayer, buffering);
}

void ItemDetailDraw(ITEM* it, int x, int y, float zoom, bool equipped, bool onlyInfo, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i;
	float width;
	//갭이 마이너스면 현재 장착중인게 좋은거다
	long long combatPowerGap = CompareCombatPower(&robin.newItem, &ao[robin.newItem.type % 3].equip[itemEquipSlot[robin.newItem.type]]);

	int arrowDirY = DOWN;

	if (combatPowerGap >= 0)
		arrowDirY = UP;



	//equipped가 true면 장착중, false면 

	DrawFrame(x, y + (float)8 * _2X * zoom, (float)ITEMDETAILWINDOWSIZE_X * zoom, (float)(ITEMDETAILWINDOWSIZE_Y + 8 * _2X) * zoom, FRAME_NORMAL, cvtDest, cvtLayer, buffering);
	if (onlyInfo == true)
		DrawLabel(x + (float)(ITEMDETAILWINDOWSIZE_X / 2 - 40 * _2X) * zoom, y + (float)24 * _2X * zoom, TEXT_DETAILINFO, zoom, cvtDest, cvtLayer, buffering);
	else
		DrawLabel(x + (float)(ITEMDETAILWINDOWSIZE_X / 2 - 40 * _2X) * zoom, y + (float)24 * _2X * zoom, equipped == true ? TEXT_EQUIPPEDITEM : TEXT_NEWITEM, zoom, cvtDest, cvtLayer, buffering);

	if (equipped == false && onlyInfo == false && combatPowerGap != 0) {
		DrawText(TEXT_COMBATPOWER, x + (float)252 * _2X * zoom, y + (float)(-4 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
		if (combatPowerGap > 0)
			SetColor(COLOR_REALYELLOW);
		else
			SetColor(COLOR_REALRED);
		DrawNum(combatPowerGap, x + (float)280 * _2X * zoom, y + (float)-18 * _2X * zoom, NUM_FONT_NORMAL, RIGHT, false, combatPowerGap > 0 ? PLUS : MINUS, true, zoom, false, cvtDest, cvtLayer, buffering);
		SetColor(false);
	}
	//DrawRewardCard(it->type, it->detail, it->grade, it->cooldown, it->count, x + (float)0 * _2X * zoom, y - (float)0 * _2X * zoom, false, zoom * DEFAULTZOOM, false, false, true, GetItemStar(it->type, it->detail, it->grade), GetItemStar(it->type, it->detail, it->grade), true, cvtDest, cvtLayer, buffering);

	//DrawIcon(GetItemIcon(it->type, it->detail, it->grade), x + (float)(8 * _2X) * zoom, y - (float)8 * _2X * zoom, zoom * DEFAULTZOOM, false, false, true, cvtDest, cvtLayer, buffering);

	DrawItemIcon(it, &ao[PLAYER], x + (float)(8 * _2X) * zoom, y - (float)8 * _2X * zoom, zoom * LOBBYZOOM, cvtDest, cvtLayer, buffering);

	//소켓이 있는 아이템이라면
	//if (it->type <= ITEM_RING && it->count > 0) {
	//	DrawAlpha(x + (float)48 * _2X * zoom, y - (float)5 * _2X * zoom, ALPHA_SOCKET, FONT_SMALL, zoom, false, cvtDest, cvtLayer, buffering);
	//	for (i = 0; i < it->count; i++)
	//		DrawSocket(it->socket[i], x + (float)(88 * _2X + 9 * _2X * i) * zoom, y - (float)5 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);
	//}
	memset(&itemName, 0, sizeof(itemName));
	sprintf(itemName, "||[%s]  %s  |b%s %d", textId[TEXT_NORMAL + it->grade], it->name, textId[TEXT_ALPHA_LV], (int)(it->cooldown + 1));
	itemName[1] = itemColorText[it->grade];
	DrawTextStr(itemName, x + (float)44 * _2X * zoom, y - (float)16 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

	SetFontColor(COLOR_WHITE);

	MemRect(x + (float)4 * _2X * zoom, y - (float)42 * _2X * zoom, (float)(ITEMDETAILWINDOWSIZE_X - 8 * _2X) * zoom, (float)2 * _2X * zoom, COLOR_SKY, cvtDest, cvtLayer, buffering);


	SetItemString(it, false, false);
	//SetFontColor(COLOR_)
	DrawTextStrSystem(tempStr, x + (float)44 * _2X * zoom, y - (float)28 * _2X * zoom, 0.8f * zoom, LEFT, false, cvtDest, cvtLayer, buffering);

	//장비인 경우
	if (it->type <= ITEM_RING || it->type == ITEM_RECIPE) {
		int itemType = it->type;

		if (itemType == ITEM_RECIPE) {
			itemType = it->detail >> 3;
		}

		//종류
		width = GetAlphaWidth(ALPHA_SWORD + itemType, FONT_SMALL, zoom);
		//SetBlend(12, 0x0000FF);
		DrawAlpha(x + (float)(44 * _2X) * zoom, y - (float)6 * _2X * zoom, ALPHA_SWORD + itemType, FONT_SMALL, zoom, false, cvtDest, cvtLayer, buffering);
		//UnSetBlend();

		DrawTextStr(textId[TEXT_DEFAULTSTAT], x + (float)12 * _2X * zoom, y - (float)52 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

		//공격/방어력/효과 텍스트
		//MemRectFrame(x + (float)4 * _2X * zoom, y - (float)75 * _2X * zoom, (float)168 * _2X * zoom, (float)15 * _2X * zoom, 0x9BA9BD, cvtDest, cvtLayer, buffering);

		//if (itemType != ITEM_RING)
		//	DrawAlpha(x + (float)7 * _2X * zoom, y - (float)79 * _2X * zoom, itemValueType[itemType], FONT_SMALL, zoom, false, cvtDest, cvtLayer, buffering);

		switch (it->type) {
		default:
			memset(&defaultStatStr, 0, sizeof(defaultStatStr));

			sprintf(defaultStatStr, "%s  %s", textId[itemValueTypeText[it->type]], dmgStr);

			DrawTextStr(defaultStatStr, x + (float)64 * _2X * zoom, y - (float)52 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

			if (equipped == false) {
				if (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) != 0) {
					//if (combatPowerNext - combatPowerCur != 0) {
						//arrowDirY = frame / FPS % 2;
						//DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - (robin.playtime / 2) % 8), x + (float)(arrowDirY == UP ? 180 * _2X : 180 * _2X) * zoom, y - (arrowDirY == UP ? (float)40 * _2X * zoom : (float)64 * _2X * zoom), LEFT, (arrowDirY == UP) ? false : 180, (float)(1.2f) * zoom, cvtDest, cvtLayer, buffering);
					DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - (robin.playtime / 2) % 8), x + (float)(GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? 200 * _2X : 210 * _2X) * zoom, y - (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? (float)40 * _2X : (float)54 * _2X) * zoom, LEFT, GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? false : 180, (float)(1.1f) * zoom, cvtDest, cvtLayer, buffering);
					DrawNum(GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]), x + (float)280 * _2X * zoom, y - (float)50 * _2X * zoom, NUM_FONT_NORMAL, RIGHT, false, GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? PLUS : MINUS, true, 1.1f * zoom, false, cvtDest, cvtLayer, buffering);
				}
			}

			//DrawTextStr(textId[itemValueTypeText[it->type]], x + (float)64 * _2X * zoom, y - (float)52 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);
			//DrawTextStr(dmgStr, x + (float)100 * _2X * zoom, y - (float)52 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);
			/*
			//강화레벨
			SetBlend(8, 0xEFA536);
			DrawAlpha(x + (float)115 * _2X * zoom, y - (float)79 * _2X * zoom, ALPHA_ENCHANT, FONT_SMALL, zoom, false, cvtDest, cvtLayer, buffering);
			UnSetBlend();
			DrawArray(IMG_SMALLPLUS, x + (float)153 * _2X * zoom, y - (float)79 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

			if (it->cooldown)
				SetBlend(12, 0x00FF00);

			DrawNum(it->cooldown, x + (float)170 * _2X * zoom, y - (float)79 * _2X * zoom, NUM_FONT_SMALL, RIGHT, 0, false, true, zoom, false, cvtDest, cvtLayer, buffering);
			UnSetBlend();
			*/
			break;
		case ITEM_NECK:
			DrawTextStr(dmgStr, x + (float)64 * _2X * zoom, y - (float)52 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

			if (equipped == false) {
				if (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) != 0) {
					//if (combatPowerNext - combatPowerCur != 0) {
						//arrowDirY = frame / FPS % 2;
						//DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - (robin.playtime / 2) % 8), x + (float)(arrowDirY == UP ? 180 * _2X : 180 * _2X) * zoom, y - (arrowDirY == UP ? (float)40 * _2X * zoom : (float)64 * _2X * zoom), LEFT, (arrowDirY == UP) ? false : 180, (float)(1.2f) * zoom, cvtDest, cvtLayer, buffering);
					DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - (robin.playtime / 2) % 8), x + (float)(GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? 200 * _2X : 210 * _2X) * zoom, y - (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? (float)40 * _2X : (float)54 * _2X) * zoom, LEFT, (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0) ? false : 180, (float)(1.2f) * zoom, cvtDest, cvtLayer, buffering);
					DrawNum(GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]), x + (float)280 * _2X * zoom, y - (float)50 * _2X * zoom, NUM_FONT_NORMAL, RIGHT, false, (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0) ? PLUS : MINUS, true, 1.1f * zoom, false, cvtDest, cvtLayer, buffering);
				}
			}
			break;
		case ITEM_RING:
			DrawTextStr(dmgStr, x + (float)64 * _2X * zoom, y - (float)52 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

			if (equipped == false) {
				if (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) != 0) {
					//if (combatPowerNext - combatPowerCur != 0) {
						//arrowDirY = frame / FPS % 2;
						//DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - (robin.playtime / 2) % 8), x + (float)(arrowDirY == UP ? 180 * _2X : 180 * _2X) * zoom, y - (arrowDirY == UP ? (float)40 * _2X * zoom : (float)64 * _2X * zoom), LEFT, (arrowDirY == UP) ? false : 180, (float)(1.2f) * zoom, cvtDest, cvtLayer, buffering);
					DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - (robin.playtime / 2) % 8), x + (float)(GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? 200 * _2X : 210 * _2X) * zoom, y - (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? (float)40 * _2X : (float)54 * _2X) * zoom, LEFT, (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0) ? false : 180, (float)(1.2f) * zoom, cvtDest, cvtLayer, buffering);
					DrawNum(GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]), x + (float)280 * _2X * zoom, y - (float)50 * _2X * zoom, NUM_FONT_NORMAL, RIGHT, false, (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0) ? PLUS : MINUS, true, 1.1f * zoom, false, cvtDest, cvtLayer, buffering);
				}
			}
			break;
		case ITEM_RECIPE:
			DrawTextStr(dmgStr, x + (float)64 * _2X * zoom, y - (float)52 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

			break;
		}
	}
	else if (it->type == ITEM_GEM) {
		MemRectFrame(x + (float)4 * _2X * zoom, y - (float)60 * _2X * zoom, (float)168 * _2X * zoom, (float)13 * _2X * zoom, 0x9BA9BD, cvtDest, cvtLayer, buffering);

		//종류
		width = GetAlphaWidth(ALPHA_GEM, FONT_SMALL, zoom);

		SetBlend(12, 0x0000FF);
		DrawAlpha(x + (float)169 * _2X * zoom - width, y - (float)63 * _2X * zoom, ALPHA_GEM, FONT_SMALL, zoom, false, cvtDest, cvtLayer, buffering);
		UnSetBlend();

		//공격/방어력/효과 텍스트
		MemRectFrame(x + (float)4 * _2X * zoom, y - (float)75 * _2X * zoom, (float)168 * _2X * zoom, (float)15 * _2X * zoom, 0x9BA9BD, cvtDest, cvtLayer, buffering);
		DrawAlpha(x + (float)7 * _2X * zoom, y - (float)79 * _2X * zoom, ALPHA_OPTION, FONT_SMALL, zoom, false, cvtDest, cvtLayer, buffering);
		DrawTextStr(optionStr[0], x + (float)43 * _2X * zoom, y - (float)76 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);
	}
	else {
		if (it->type == ITEM_QUEST && it->detail >= ITEM_QUEST_MAP)
			MemRect(x + (float)4 * _2X * zoom, y - (float)73 * _2X * zoom, (float)168 * _2X * zoom, (float)2 * _2X * zoom, COLOR_SKY, cvtDest, cvtLayer, buffering);
		else
			MemRect(x + (float)4 * _2X * zoom, y - (float)60 * _2X * zoom, (float)168 * _2X * zoom, (float)2 * _2X * zoom, COLOR_SKY, cvtDest, cvtLayer, buffering);
	}
	if (it->option[0][0] != EMPTYINT && optionStr[0][0] != 0)
		DrawTextStr(textId[TEXT_OPTIONSTAT], x + (float)12 * _2X * zoom, y - (float)72 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);
	ItemOptionDraw(it, x + (float)(64 * _2X) * zoom, y - (float)(72 * _2X * zoom), zoom, equipped, cvtDest, cvtLayer, buffering);
	if (equipped == false && onlyInfo == false)
		ItemOptionCompareDraw(it, &ao[PLAYER].equip[itemEquipSlot[it->type]], x + (float)(200 * _2X) * zoom, y - (float)(72 * _2X * zoom), zoom, cvtDest, cvtLayer, buffering);
	//장착, 교체 버튼
	if (equipped == false && onlyInfo == false) {
		DrawTouchLargeButton(x + (float)(8 * _2X) * zoom, y - (float)(ITEMDETAILWINDOWSIZE_Y - 36 * _2X) * zoom, BUYBUTTON_X, BUYBUTTON_Y, textId[TEXT_DISASSEMBLE], TOUCH_FUNC_DISASSEMBLE_NEWITEM, FRAME_RED, zoom, cvtDest, cvtLayer, buffering);
		DrawTouchLargeButton(x + (float)(196 * _2X) * zoom, y - (float)(ITEMDETAILWINDOWSIZE_Y - 36 * _2X) * zoom, BUYBUTTON_X, BUYBUTTON_Y, textId[TEXT_EQUIP], TOUCH_FUNC_EQUIP_NEWITEM, FRAME_GREEN, zoom, cvtDest, cvtLayer, buffering);

		//if (CompareCombatPower(it, &ao[PLAYER].equip[itemEquipSlot[it->type]]) < 0) {
		//	ResetRectPoint();
		//	ScreenDarken(SCREENDARKEN);
		//	//경고
		//	DrawFrame(DX / 2, DY / 2, (float)160 * _2X * zoom, (float)160 * _2X * zoom, FRAME_ANIINFO, cvtDest, cvtLayer, buffering);

		//	DrawTouchLargeButton(x + (float)(32 * _2X) * zoom, DY / 2 - (float)(160 * _2X - 36 * _2X) * zoom, BUYBUTTON_X, BUYBUTTON_Y, textId[TEXT_CANCEL], TOUCH_FUNC_DISASSEMBLE_NEWITEM, FRAME_RED, zoom, cvtDest, cvtLayer, buffering);
		//	DrawTouchLargeButton(x + (float)(128 * _2X) * zoom, DY / 2 - (float)(160 * _2X - 36 * _2X) * zoom, BUYBUTTON_X, BUYBUTTON_Y, textId[TEXT_EQUIP], TOUCH_FUNC_EQUIP_NEWITEM, FRAME_GREEN, zoom, cvtDest, cvtLayer, buffering);

		//}

	}
	UnSectionClip(false);
}

void ItemOptionCompareDraw(ITEM* it1, ITEM* it2, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i;
	unsigned char mark[12];
	int valueInt;
	float valueFloat;

	for (i = 0; i < 12; i++) {
		if (it1->option[i][0] != EMPTYINT && optionStr[i][0] != 0) {
#ifdef DEBUG
			if (drawHandle == MD_SIMUL && i == e[0])
				DrawHand(x, y, 0);
#endif
			if (it1->option[i][0] == it2->option[i][0])
				if (it1->option[i][1] - it2->option[i][1] != 0) {
					DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - (robin.playtime / 2) % 8), x + (float)(it1->option[i][1] - it2->option[i][1] > 0 ? 0 * _2X : 9 * _2X) * zoom, y - (it1->option[i][1] - it2->option[i][1] > 0 ? (float)-10 * _2X : (float)4 * _2X) * zoom, LEFT, (it1->option[i][1] - it2->option[i][1] > 0) ? false : 180, (float)(1.0f) * zoom, cvtDest, cvtLayer, buffering);
					memset(&itemOptionStr, 0, sizeof(itemOptionStr));
					valueInt = it1->option[i][1] - it2->option[i][1];
					sprintf(itemOptionStr, TEXTPTR(TEXT_PREFIX_DESC_COMPARE + it1->option[i][0]), valueInt);
					DrawTextStr(itemOptionStr, x + (float)16 * _2X * zoom, y, zoom, cvtDest, cvtLayer, buffering);
				}
			y -= (float)13 * _2X * zoom;
		}
	}
}

void ItemOptionDraw(ITEM* it, int x, int y, float zoom, bool equipped, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i, rt = 1, count, require;

	if (it->type <= ITEM_RING) {
		//옵션
		count = y;

		for (i = 0; i < 12; i++) {
			if (it->option[i][0] != EMPTYINT && optionStr[i][0] != 0) {
#ifdef DEBUG
				if (drawHandle == MD_SIMUL && i == e[0])
					DrawHand(x, y, 0);
#endif

				DrawTextStr(optionStr[i], x + (float)0 * _2X * zoom, y, zoom, cvtDest, cvtLayer, buffering);
				y -= (float)13 * _2X * zoom;
			}
		}

		for (i = 0; i < 6; i++) {
			if (gemStr[i][0] != 0) {
				DrawTextStr(gemStr[i], x + (float)0 * _2X, y, zoom, cvtDest, cvtLayer, buffering);
				y -= (float)13 * _2X * zoom;
			}
		}

		if (count != y) {
			y -= (float)5 * _2X;
			count = y;
		}

		if (it->type < ITEM_GEM) {
			//세트아이템인 경우 세트효과를 보여준다.
			if (it->grade == GRADE_SET) {
				const int* ucPtr = &setOption[(it->set % 100) * SETOPTIONDATASIZE];

				DrawTextStr(setStr[0], x + (float)0 * _2X, y, zoom, cvtDest, cvtLayer, buffering);

				y += 15;

				for (i = 1; i < 7 && setStr[i][0] != 0; i++, ucPtr += 3) {
					//if (it >= ITEMPTR_EQUIP && idx != ITEMPTR_TEMPITEM && setCount[idx - ITEMPTR_EQUIP] >= *ucPtr)
					//	SetBlend(8, 0x0000FF);
					//else
					SetBlend(16, 0x000000);

					//grayScale = 24;

					DrawTextStr(setStr[i], x + (float)0 * _2X * zoom, y, zoom, cvtDest, cvtLayer, buffering);
					y -= (float)13 * _2X;

					UnSetBlend();
					grayScale = 0;
				}
			}
			/*
			if (it->type < ITEM_NECK && it->cooldown < MAXENCHANT) {
				if (count != y)
					y += 5;

				//강화재료 상세내용
				for (i = 0; i < 2; i++) {
					unsigned char *eData = &d.enchantData[(it->type * 40 + d.itemDataOrder[(it->detail * 6 + it->grade)]) * ENCHANTDATASIZE + i * 2];

					//아이콘 및 요구갯수
					require = UpDiv((it->cooldown + 1) * *(eData + 1), ENCHANTITEMRATE);
					count = GetItemCount(ITEM_IRON + *eData / 50, *eData % 50, 0);

					if (count < require) {
						grayScale = 20;
						SetBlend(6, 0xFF0000);
					}

					DrawIcon(GetItemIcon(ITEM_IRON + *eData / 50, *eData % 50), x + 40, y + 15 + i * 18);
					DrawNum(require, x + 55, y + 24 + i * 18, FONT_SMALL, RIGHT, 0, false);

					grayScale = 0;
					UnSetBlend();

					//유저가 소지한 개수가 제작하기 충분한지 체크하고 사용자가 가지고 있는 갯수만큼을 부채꼴로 보여준다.
					if (count < require) {
						DrawCycle(x + 40, y + 15 + i * 18, 16, 16, 4 + require - count, 4 + require);
						rt = 0;
					}

					//아이템 이름
					DrawText(TEXT_ITEMNAME_START + GetItemName(ITEM_IRON + *eData / 50, *eData % 50, 0), x + 60, y + 17 + i * 18);
				}

				//강화재료
				SetFontColor(rt == 0 ? 0xFF0000 : 0x00FF00);
				CenterText(TEXT_ENCHANT_STUFF, x + 82, y);
			}
			*/
		}
	}
	else if (it->type == ITEM_RECIPE) {
		//기본재료 상세내용
		if (GetItemCount(it->type, it->detail, it->grade) == 0) {
			grayScale = 20;
			SetBlend(6, 0xFF0000);
			rt = 0;
		}

		DrawIcon(GetItemIcon(it->type, it->detail, it->grade), x + (float)40 * zoom, y - (float)15 * _2X, zoom, false, false, false, 1, cvtDest, cvtLayer, buffering);

		if (rt == 0) {
			SetAlpha(10);
			MemRect(x + (float)40 * _2X * zoom, y - (float)15 * _2X, (float)16 * _2X * zoom, (float)16 * _2X * zoom, 0x990000, cvtDest, cvtLayer, buffering);
			SetAlpha(32);
			grayScale = 0;
			UnSetBlend();
		}

		DrawText(TEXT_ITEMNAME_START + GetItemName(it->type, it->detail, it->grade), x + (float)60 * _2X * zoom, y - (float)17 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);
	}
}

void EquipInfoDraw(ITEM* it, int x, int y, int itemType, int itemDetail, int itemGrade, int depth, int menuX, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i;
	int itemLv, itemCnt, itemSlot, itemIdx, itemIcon;
	int itemTypeNext, itemDetailNext, itemGradeNext;
	int icon, skillIcon, questIcon, pvpQuestIcon;
	OBJECT* pObj = &ao[PLAYER];
	int collectionIdx;

	float width;
	float YGAP = -64 * _2X;
	int eventIdx = GetEventMenuIdx(EVENTTYPE_DEBTDISCOUNT);
	float discount = 0;
	int swordSkillIdx;
	int curSkillPerSword = 4;
	float CARDZOOM = 0.7f;
	int Divide = 1;

	if (eventIdx != -1)
		discount = robin.gameEvent[eventIdx].value;

	//인벤토리에서 슬롯을 찾는다.
	itemIdx = GetInvenIdx(itemType, itemDetail, itemGrade);
	itemIcon = GetItemIcon(itemType, itemDetail, itemGrade);
	itemLv = GetItemLv(itemType, itemDetail, itemGrade);
	itemCnt = GetItemCount(itemType, itemDetail, itemGrade);
	it = GetItemPtr(ITEMPTR_INVEN + itemIdx);

	SetItemString(it, 0, 0);

	switch (depth) {
	case 0:
	case 1:
	case 2:
		//이전단계
		//TouchArrow2(2, x + 0 * _2X, y + 0, DY / 2, cvtDest, cvtLayer, buffering);

		if (winAniFrame > 0) {
			winAniFrame++;

			DrawNeutral(OBJ_STAMPEFFECT0 + (frame / 3 % 8), x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + 160 * _2X) * zoom, 0, 1.0f, gScreenBuffer, gScreenLayer, false);

			if (winAniFrame == FPS)
				winAniFrame = 0;
		}


		//현재단계
		DrawPlayerCostume(
			pObj->type,
			pObj->equip[EQUIP_WEAPON].type != EMPTY ? pObj->equip[EQUIP_WEAPON].detail : -1, pObj->equip[EQUIP_WEAPON].type != EMPTY ? pObj->equip[EQUIP_WEAPON].grade : 0,
			pObj->equip[EQUIP_GLOVE].type != EMPTY ? pObj->equip[EQUIP_GLOVE].detail : -1, pObj->equip[EQUIP_GLOVE].type != EMPTY ? pObj->equip[EQUIP_GLOVE].grade : 0,
			pObj->equip[EQUIP_HELM].type != EMPTY ? pObj->equip[EQUIP_HELM].detail : -1, pObj->equip[EQUIP_HELM].type != EMPTY ? pObj->equip[EQUIP_HELM].grade : 0,
			pObj->equip[EQUIP_ARMOR].type != EMPTY ? pObj->equip[EQUIP_ARMOR].detail : -1, pObj->equip[EQUIP_ARMOR].type != EMPTY ? pObj->equip[EQUIP_ARMOR].grade : 0,
			pObj->equip[EQUIP_PANTS].type != EMPTY ? pObj->equip[EQUIP_PANTS].detail : -1, pObj->equip[EQUIP_PANTS].type != EMPTY ? pObj->equip[EQUIP_PANTS].grade : 0,
			pObj->equip[EQUIP_BOOTS].type != EMPTY ? pObj->equip[EQUIP_BOOTS].detail : -1, pObj->equip[EQUIP_BOOTS].type != EMPTY ? pObj->equip[EQUIP_BOOTS].grade : 0,

			x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + 160 * _2X) * zoom, RIGHT, true, zoom * HEROZOOM, cvtDest, cvtLayer, buffering
		);

		icon = statIcon[itemEquipSlot[itemType]];

		collectionIdx = GetCollectionIdx(itemType, itemDetail, itemGrade);

		skillIcon = ICON_GOLD;

		itemIdx = GetInvenIdx(itemType, itemDetail, itemGrade);
		itemIcon = GetItemIcon(itemType, itemDetail, itemGrade);
		itemLv = GetItemLv(itemType, itemDetail, itemGrade);
		itemCnt = GetItemCount(itemType, itemDetail, itemGrade);
		it = GetItemPtr(ITEMPTR_INVEN + itemIdx);

		if (questInfo[robin.quest * QUESTINFODATASIZE + 1] == QUESTTYPE_RAID)
			questIcon = ICON_RAID;
		else if (questInfo[robin.quest * QUESTINFODATASIZE + 1] == QUESTTYPE_BATTLE)
			questIcon = ICON_BATTLE;
		else
			questIcon = GetItemIcon(questRequestItem[robin.quest * 3 + 0], questRequestItem[robin.quest * 3 + 1], questRequestItem[robin.quest * 3 + 2]);

		pvpQuestIcon = pvpQuestInfo[robin.pvpQuest * PVPQUESTINFODATASIZE + 0];
		//TEST
		//itemLv = 5;

		if (itemType == ITEM_CREW) {
			curStar = maxStar = crewData[itemDetail * CREWDATASIZE + CREWDATASIZE - 1] + 1;
		}
		else {
			curStar = maxStar = GetItemStar(itemType, itemDetail, itemGrade);
		}

		DrawRewardCard(itemType, itemDetail, itemGrade, itemLv, itemCnt, x + (float)(DX / 2 - REWARDCARDSIZE_X) * zoom, y + (float)(DY / 2 + 148 * _2X) * zoom, true, (float)2 * zoom, true, false, true, itemLv, ITEMMAXLEVEL, true, cvtDest, cvtLayer, buffering);
		//개별 장착이 되지 않는다면
		//만약 장착이 되어 있지 않으면
		if (GetEquipSlot(itemType, itemDetail, itemGrade) == -1) {
			DrawTextButton(x + (float)(DX / 2 - 40 * _2X) * zoom, y + (float)(DY / 2 + 148 * _2X - REWARDCARDSIZE_Y * 2 - 8 * _2X) * zoom, (float)(80 * _2X) * zoom, (float)(28 * _2X) * zoom, 0, false, zoom, false, TEXT_EQUIP, cvtDest, cvtLayer, buffering);
			SetRectPoint(x + (float)(DX / 2 - 40 * _2X) * zoom, y + (float)(DY / 2 + 148 * _2X - REWARDCARDSIZE_Y * 2 - 8 * _2X) * zoom, (float)(80 * _2X) * zoom, (float)(28 * _2X) * zoom, TOUCH_FUNC_EQUIP_INVENTORY + itemStartCnt[itemType] + itemDetail * TOTALGRADE + itemGrade);
		}
		else
			DrawTextButton(x + (float)(DX / 2 - 40 * _2X) * zoom, y + (float)(DY / 2 + 148 * _2X - REWARDCARDSIZE_Y * 2 - 8 * _2X) * zoom, (float)(80 * _2X) * zoom, (float)(28 * _2X) * zoom, 0, 32, zoom, false, TEXT_SOCKETING, cvtDest, cvtLayer, buffering);


		DrawWindow2(x + (float)(DX / 2 - 158 * _2X) * zoom, y + (float)(DY / 2 - 10 * _2X) * zoom, 316 * _2X, 60 * _2X, COLOR_NAVY, zoom, cvtDest, cvtLayer, buffering);
		//골드 / 골드백 / 하트 / 퀘스트 아이템
		switch (itemType) {
		default:
			DrawItemValue(it->type, it->detail, it->grade, it->cooldown, x + (float)(DX / 2) * zoom, y + (float)(DY / 2 - 10 * _2X - ITEMICONSIZE) * zoom, CENTER, false, zoom, 128 * _2X * zoom, cvtDest, cvtLayer, buffering);
			break;
		}

		switch (itemType) {
		case ITEM_SWORD:
			LineText(TEXT_TIP_MENU_SWORD, x + (float)(DX / 2 - 136 * _2X + 12 * _2X) * zoom, y + (float)(DY / 2 - 64 * _2X) * zoom, (float)(272 * _2X - 8 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
			break;
		case ITEM_GUNTLET:
			LineText(TEXT_TIP_MENU_GLOVE, x + (float)(DX / 2 - 136 * _2X + 12 * _2X) * zoom, y + (float)(DY / 2 - 64 * _2X) * zoom, (float)(272 * _2X - 8 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
			break;
		case ITEM_HELM:
			LineText(TEXT_TIP_MENU_HELM, x + (float)(DX / 2 - 136 * _2X + 12 * _2X) * zoom, y + (float)(DY / 2 - 64 * _2X) * zoom, (float)(272 * _2X - 8 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
			break;
		case ITEM_ARMOR:
			LineText(TEXT_TIP_MENU_ARMOR, x + (float)(DX / 2 - 136 * _2X + 12 * _2X) * zoom, y + (float)(DY / 2 - 64 * _2X) * zoom, (float)(272 * _2X - 8 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
			break;
		case ITEM_KILT:
			LineText(TEXT_TIP_MENU_PANTS, x + (float)(DX / 2 - 136 * _2X + 12 * _2X) * zoom, y + (float)(DY / 2 - 64 * _2X) * zoom, (float)(272 * _2X - 8 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
			break;
		case ITEM_GREAVES:
			LineText(TEXT_TIP_MENU_BOOTS, x + (float)(DX / 2 - 136 * _2X + 12 * _2X) * zoom, y + (float)(DY / 2 - 64 * _2X) * zoom, (float)(272 * _2X - 8 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
			break;
		}
		//장착한 모습을 보여주고,

		//업그레이드
		//왼쪽이 강화하기
		//오른쪽이 장착하기
		//

		for (i = 0; i < 1; i++) {
			if (menuX == i) {
				DrawFrame(x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i - 2 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 4 * _2X + 2 * _2X + YGAP) * zoom, (float)(128 * _2X) * zoom, (float)(32 * _2X) * zoom, FRAME_CHOICEBUTTON_BEIGE, cvtDest, cvtLayer, buffering);
			}
			else {
				DrawFrame(x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 4 * _2X + YGAP) * zoom, (float)(128 * _2X) * zoom, (float)(32 * _2X) * zoom, FRAME_CHOICEBUTTON, cvtDest, cvtLayer, buffering);
			}
			switch (i) {
				//강화하기
			case 0:
				ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i - 20 * _2X + 24 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 4 * _2X + YGAP + 8 * _2X - 20 * _2X) * zoom, SHADOW_IMG, zoom, cvtDest, cvtLayer, buffering);
				DrawNeutral(EFFECT_CRAFT0 + (menuX == 0 ? (frame / 2) % 3 : 0), x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i + 24 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 4 * _2X + YGAP - 20 * _2X) * zoom, 0, zoom, cvtDest, cvtLayer, buffering);
				DrawText(TEXT_UPGRADE, x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i + 60 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 14 * _2X + YGAP) * zoom, zoom, cvtDest, cvtLayer, buffering);

				//memset(tempStr, 0, sizeof(tempStr));
				//sprintf(tempStr, TEXTPTR(TEXT_MAXLEVEL), collectionLvLimit[collectionIdx]);

				//DrawTextStr(tempStr, x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i + 60 * _2X + 128 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 14 * _2X + YGAP) * zoom, zoom, cvtDest, cvtLayer, buffering);
				break;
				//진화하기TEXT_HAMMER
			case 1:
				ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i - 20 * _2X + 24 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 4 * _2X + YGAP + 8 * _2X - 20 * _2X) * zoom, SHADOW_IMG, zoom, cvtDest, cvtLayer, buffering);
				DrawCmfDetail(CMF_NPC_HEART, PO_C122_HEART, x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i + 24 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 4 * _2X + YGAP - 20 * _2X) * zoom, LEFT, zoom, false, false, cvtDest, cvtLayer, buffering);
				DrawText(TEXT_HAMMER, x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i + 60 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 14 * _2X + YGAP) * zoom, zoom, cvtDest, cvtLayer, buffering);
				break;
			}

			SetRectPoint(x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 4 * _2X + YGAP) * zoom, (float)(128 * _2X) * zoom, (float)(32 * _2X) * zoom, TOUCH_FUNC_EQUIP_ENCHANT + i);
		}

		DrawWindow2(x + (float)(DX / 2 - 136 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 32 * _2X + YGAP) * zoom, 272 * _2X, MINDY_MIN + 16 * _2X - 240 * _2X - 4 * _2X + YGAP, COLOR_NAVY, zoom, cvtDest, cvtLayer, buffering);

		switch (menuX) {
		case 0:
			Divide = 2;
			CARDZOOM = 0.45f;

			if (itemLv < collectionLvLimit[collectionIdx]) {
				//현재 레벨과 데미지

				DrawStar(ICON_STAR, +(float)(DX / 2 - 132 * _2X + 42 * _2X + 11 * _2X * 2) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 32 * _2X - 10 * _2X + YGAP - 2 * _2X * 2) * zoom, itemLv, ITEMMAXLEVEL, ITEMMAXLEVEL, CENTER, true, zoom, cvtDest, cvtLayer, buffering);

				DrawStar(ICON_STAR, x + (float)(DX / 2 - 132 * _2X + 42 * _2X + 11 * _2X * 2 + 140 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 32 * _2X - 10 * _2X + YGAP - 2 * _2X * 2) * zoom, itemLv + 1, ITEMMAXLEVEL, ITEMMAXLEVEL, CENTER, true, zoom, cvtDest, cvtLayer, buffering);

				//업그레이드 화살표
				SetAlpha(32 - Abs(frame % 32 - 16));
				DrawImage(18 * _2X, 14 * _2X, 58 * _2X, 174 * _2X, x + (float)(DX / 2 - 12 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 32 * _2X - 8 * _2X + YGAP) * zoom, true, false, false, false, false, (float)1.5f * zoom, sprite[COMMON_IMG], gScreenBuffer, gScreenLayer, COMMON_IMG, false);
				SetAlpha(32);

				//업그레이드 보상

				//업그레이드 후 데미지
				DrawBuyButton(x + (float)(DX / 2) * zoom - ((float)BUYBUTTON_X * zoom) / 2, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 32 * _2X - (MINDY_MIN - 240 * _2X - 4 * _2X - 32 * _2X) + 28 * _2X + 8 * _2X - 32 * _2X - 8 * _2X) * zoom, (float)BUYBUTTON_X * zoom, (float)(BUYBUTTON_Y)*zoom, frame, robin.hammer >= GetUpgradeHammer(itemType, itemDetail, itemGrade, itemLv) ? 0 : 32, GetUpgradeHammer(itemType, itemDetail, itemGrade, itemLv), CURRENCY_HAMMER, zoom, false, false, false, cvtDest, cvtLayer, buffering);
				if (robin.hammer >= GetUpgradeHammer(itemType, itemDetail, itemGrade, itemLv)) {
					SetRectPoint(x + (float)(DX / 2) * zoom - ((float)BUYBUTTON_X * zoom) / 2, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 32 * _2X - (MINDY_MIN - 240 * _2X - 4 * _2X - 32 * _2X) + 28 * _2X + 8 * _2X - 32 * _2X - 8 * _2X) * zoom, (float)BUYBUTTON_X * zoom, (float)(BUYBUTTON_Y)*zoom, TOUCH_FUNC_ITEM_UPGRADE);
				}
			}
			else {

				DrawStar(ICON_STAR, +(float)(DX / 2) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 32 * _2X - 10 * _2X + YGAP - 2 * _2X * 2) * zoom, itemLv, ITEMMAXLEVEL, ITEMMAXLEVEL, CENTER, true, zoom, cvtDest, cvtLayer, buffering);

				CenterText(TEXT_MAXUPGRADED, x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 380 * _2X - 2 * ITEMICONSIZE - 8 * _2X - 20 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
			}

			break;
		case 1:
			for (i = 0; i < ITEMHAMMERCNT; i++) {
				DrawFrame(x + (float)(DX / 2 - 136 * _2X + 10 * _2X + (ITEMCARD_WIDTH / 3 + 4 * _2X) * i) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 12 * _2X + YGAP) * zoom, (float)(ITEMCARD_WIDTH / 3) * zoom, (float)(ITEMCARD_HEIGHT / 3) * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
				if (itemCnt <= i) {
					DrawAlpha(x + (float)(DX / 2 - 136 * _2X + 10 * _2X + (ITEMCARD_WIDTH / 3 + 4 * _2X) * i + ITEMCARD_WIDTH / 3 / 2 - 4 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 12 * _2X - ITEMCARD_HEIGHT / 3 / 2 + 4 * _2X + YGAP) * zoom, ALPHA_PLUS, FONT_SMALL, zoom, false, cvtDest, cvtLayer, buffering);
				}
				else {
					ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(DX / 2 - 136 * _2X + 10 * _2X + (ITEMCARD_WIDTH / 3 + 4 * _2X) * i + ITEMCARD_WIDTH / 3 / 2 - 20 * _2X * 1) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 12 * _2X - ITEMCARD_HEIGHT / 3 / 2 + ITEMICONSIZE * 1 + ITEMICONSIZE * 1 / 4 - 4 * _2X - (ITEMICONSIZE + 4 * _2X) + YGAP) * zoom, SHADOW_IMG, zoom, cvtDest, cvtLayer, buffering);
					DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), x + (float)(DX / 2 - 136 * _2X + 10 * _2X + (ITEMCARD_WIDTH / 3 + 4 * _2X) * i + ITEMCARD_WIDTH / 3 / 2 - ITEMICONSIZE * 1) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 12 * _2X - ITEMCARD_HEIGHT / 3 / 2 + ITEMICONSIZE * 1 + ITEMICONSIZE * 1 / 4 - 4 * _2X + YGAP) * zoom, (float)2 * zoom, false, false, false, 1, cvtDest, cvtLayer, buffering);
				}
			}

			itemTypeNext = itemType;

			if (itemGrade < GRADE_LEGEND) {
				itemDetailNext = itemDetail;
				itemGradeNext = itemGrade + 1;
			}
			else if (itemGrade == GRADE_LEGEND) {
				itemDetailNext = itemDetail + 1;
				itemGradeNext = 0;
			}

			DrawFrame(x + (float)(DX / 2 - 136 * _2X + 14 * _2X + (ITEMCARD_WIDTH / 3 + 4 * _2X) * ITEMHAMMERCNT + 12 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 12 * _2X + YGAP) * zoom, (float)(ITEMCARD_WIDTH / 3) * zoom, (float)(ITEMCARD_HEIGHT / 3) * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
			ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(DX / 2 - 136 * _2X + 14 * _2X + (ITEMCARD_WIDTH / 3 + 4 * _2X) * ITEMHAMMERCNT + 12 * _2X + ITEMCARD_WIDTH / 3 / 2 - 20 * _2X * 1) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 12 * _2X - ITEMCARD_HEIGHT / 3 / 2 + ITEMICONSIZE * 1 + ITEMICONSIZE * 1 / 4 - 4 * _2X - (ITEMICONSIZE + 4 * _2X) + YGAP) * zoom, SHADOW_IMG, zoom, cvtDest, cvtLayer, buffering);
			DrawIcon(GetItemIcon(itemTypeNext, itemDetailNext, itemGradeNext), x + (float)(DX / 2 - 136 * _2X + 14 * _2X + (ITEMCARD_WIDTH / 3 + 4 * _2X) * ITEMHAMMERCNT + 12 * _2X + ITEMCARD_WIDTH / 3 / 2 - ITEMICONSIZE * 1) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 12 * _2X - ITEMCARD_HEIGHT / 3 / 2 + ITEMICONSIZE * 1 + ITEMICONSIZE * 1 / 4 - 4 * _2X + YGAP) * zoom, (float)2 * zoom, false, false, false, 1, cvtDest, cvtLayer, buffering);

			if (itemCnt >= ITEMHAMMERCNT) {
				SetAlpha(32 - Abs(frame % 32 - 16));
				DrawImage(18 * _2X, 14 * _2X, 58 * _2X, 174 * _2X, x + (float)(DX / 2 - 136 * _2X + (ITEMCARD_WIDTH / 3 + 4 * _2X) * ITEMHAMMERCNT) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 20 * _2X + YGAP) * zoom, true, false, false, false, false, (float)2 * zoom, sprite[COMMON_IMG], cvtDest, cvtLayer, COMMON_IMG, buffering);
				SetAlpha(32);
			}
			else {
				SetAlpha(16);
				DrawImage(18 * _2X, 14 * _2X, 58 * _2X, 174 * _2X, x + (float)(DX / 2 - 136 * _2X + (ITEMCARD_WIDTH / 3 + 4 * _2X) * ITEMHAMMERCNT) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 20 * _2X + YGAP) * zoom, true, false, false, false, false, (float)2 * zoom, sprite[COMMON_IMG], cvtDest, cvtLayer, COMMON_IMG, buffering);
				SetAlpha(32);

				CenterText(TEXT_5CARDNEED, x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 60 * _2X + YGAP) * zoom, zoom, cvtDest, cvtLayer, buffering);

			}

			DrawBuyButton(x + (float)(DX / 2) * zoom - (float)(BUYBUTTON_X)*zoom / 2, y + (float)(DY / 2 + MINDY_MIN / 2 - 16 * _2X - 280 * _2X - 32 * _2X - (MINDY_MIN - 280 * _2X - 4 * _2X - 32 * _2X) + 28 * _2X + 8 * _2X - 32 * _2X) * zoom, (float)(BUYBUTTON_X)*zoom, (float)(BUYBUTTON_Y)*zoom, frame, robin.star >= itemEvolutionItem[itemDetail * TOTALGRADE * (ITEMMAXLEVEL + 1) + itemGrade * (ITEMMAXLEVEL + 1) + itemLv] ? 0 : 32, itemEvolutionItem[itemDetail * TOTALGRADE * (ITEMMAXLEVEL + 1) + itemGrade * (ITEMMAXLEVEL + 1) + itemLv], CURRENCY_STAR, zoom, false, false, discount, cvtDest, cvtLayer, buffering);

			if (robin.star >= itemEvolutionItem[itemDetail * TOTALGRADE * (ITEMMAXLEVEL + 1) + itemGrade * (ITEMMAXLEVEL + 1) + itemLv]) {
				SetRectPoint(x + (float)(DX / 2) * zoom - (GetNumDx(itemEvolutionItem[itemDetail * TOTALGRADE * (ITEMMAXLEVEL + 1) + itemGrade * (ITEMMAXLEVEL + 1) + itemLv], false, NUM_FONT_NORMAL, false, true, zoom, true) + (float)(40 * _2X) * zoom) / 2, y + (float)(DY / 2 + MINDY_MIN / 2 - 16 * _2X - 280 * _2X - 32 * _2X - (MINDY_MIN - 280 * _2X - 4 * _2X - 32 * _2X) + 28 * _2X + 8 * _2X - 32 * _2X) * zoom, GetNumDx(itemEvolutionItem[itemDetail * TOTALGRADE * (ITEMMAXLEVEL + 1) + itemGrade * (ITEMMAXLEVEL + 1) + itemLv], false, NUM_FONT_NORMAL, false, true, zoom, true) + (float)(40 * _2X) * zoom, (float)(RAIDGOLDBARHEIGHT)*zoom, TOUCH_FUNC_ITEM_HAMMER);
			}
			break;
		}

		if (depth == 2) {
			UnSectionClip(false);

			switch (menuX) {
			case 0:
				SetAlpha(24);
				MemRect(x, DY, DX, DY, COLOR_BLACK, cvtDest, cvtLayer, buffering);
				SetAlpha(32);


				ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(DX / 2 - 20 * _2X) * zoom, (float)(DY / 2 - 216 * _2X / 2 + 8 * _2X) * zoom, SHADOW_IMG, zoom, cvtDest, cvtLayer, buffering);
				DrawNeutral(EFFECT_CRAFT0 + (menuFrame < FPS ? menuFrame / MOTIONDIV % 3 : 0), x + (float)(DX / 2) * zoom, (float)(DY / 2 - 216 * _2X / 2) * zoom, 0, 3 * zoom, cvtDest, cvtLayer, buffering);

				if (menuFrame < FPS) {
					if (itemType == ITEM_CREW) {
						curStar = maxStar = crewData[itemDetail * CREWDATASIZE + CREWDATASIZE - 1] + 1;
					}
					else {
						curStar = maxStar = GetItemStar(itemType, itemDetail, itemGrade);
					}

					DrawRewardCard(itemType, itemDetail, itemGrade, itemLv, itemCnt, x + (float)(DX / 2 - REWARDCARDSIZE_X) * zoom, y + (float)(DY / 2 + 148 * _2X) * zoom, false, (float)2 * zoom, true, false, true, curStar, maxStar, true, cvtDest, cvtLayer, buffering);

					if (menuFrame > FPS * 2 / 3) {
						DrawRewardCard(itemType, itemDetail, itemGrade, itemLv + 1, itemCnt, x + (float)(DX / 2 - REWARDCARDSIZE_X - (FPS - menuFrame) * REWARDCARDSIZE_X / 2) * zoom, y + (float)(DY / 2 + 148 * _2X + (FPS - menuFrame) * REWARDCARDSIZE_Y / 2) * zoom, false, (float)(2 + FPS - menuFrame) * zoom, true, false, true, curStar, maxStar, true, cvtDest, cvtLayer, buffering);
					}
					else if (menuFrame >= FPS * 1 / 3) {
						DrawEffect(EFFECT_HOLY0 + (menuFrame % 10), x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + 148 * _2X - REWARDCARDSIZE_Y) * zoom, LEFT, false, 2.0f * zoom, cvtDest, cvtLayer, buffering);
					}
					else {
						DrawEffect(BUFF_ARMOR0 + (menuFrame % 12), x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + 148 * _2X - REWARDCARDSIZE_Y) * zoom, LEFT, false, 2.0f * zoom, cvtDest, cvtLayer, buffering);
					}

					DrawEffect(1000 - 1 + HIT_DIANA_MEDIUM1 + menuFrame % 7, x + (float)(DX / 2) * zoom, y + (float)(DY / 2 - 216 * _2X / 2 + 8 * _2X) * zoom, LEFT, false, zoom, cvtDest, cvtLayer, buffering);

					if (menuFrame / MOTIONDIV % 3 == 2)
						PlayMusic(M_IRON);

					//if (menuFrame / 2 % 7)
					//DrawSubText(textId[TEXT_ENCHANTING], 0, menuFrame % 7, x + (float)(DX / 2) * zoom - StringWidth(textId[TEXT_ENCHANTING], zoom) / 2, y + (float)(-EQUIP_WIN_HEIGHT + 272 * _2X - 216 * _2X - 4 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

					SetAlpha(32 - Abs(frame % 32 - 16));
					CenterText(TEXT_ENCHANTING, x + (float)(DX / 2) * zoom, y + (float)(128 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
					SetAlpha(32);

					if (menuFrame == FPS - 1) {
						//골드 차감
						robin.hammer -= GetUpgradeHammer(itemType, itemDetail, itemGrade, itemLv);
						AddBar(&bar[BAR_HAMMER], -GetUpgradeHammer(itemType, itemDetail, itemGrade, itemLv), BARFRAME);

						it->cooldown++;

						for (i = 0; i < TOTALEQUIP; i++) {
							if (ao[PLAYER].equip[i].type == it->type && ao[PLAYER].equip[i].detail == it->detail && ao[PLAYER].equip[i].grade == it->grade)
								ao[PLAYER].equip[i].cooldown = it->cooldown;
						}

						//if (ao[PLAYER].equip[EQUIP])

						PlayMusic(M_CHEER);

						RefreshStat(&ao[PLAYER]);
						//SaveFlag(0);
						SaveGame();
					}

				}
				//콩그레툴레이션스!
				else {
					if (itemType == ITEM_CREW) {
						curStar = maxStar = crewData[itemDetail * CREWDATASIZE + CREWDATASIZE - 1] + 1;
					}
					else {
						//curStar = maxStar = GetItemStar(itemType, itemDetail, itemGrade);
						curStar = itemLv + 1;
						maxStar = ITEMMAXLEVEL;

					}

					DrawRewardCard(itemType, itemDetail, itemGrade, itemLv, itemCnt, x + (float)(DX / 2 - REWARDCARDSIZE_X) * zoom, y + (DY / 2 + 148 * _2X) * zoom, false, (float)2 * zoom, true, true, true, curStar, maxStar, true, cvtDest, cvtLayer, buffering);

					DrawEffect(EFFECT_LEVELUP_TEXT0 + (frame / 2) % 14, x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + 128 * _2X + 32 * _2X) * zoom, 0, false, (float)3 * zoom, cvtDest, cvtLayer, buffering);

					DrawGoldAlpha(x + (float)(DX / 2) * zoom, y + (float)(DY / 2 - 160 * _2X) * zoom, ALPHA_CONGRATULATIONS, FONT_GOLD_LARGE, zoom, CENTER, true, false, cvtDest, cvtLayer, buffering);

					SetRectPoint(xOffset, DY, DX, DY, TOUCH_FUNC_GAMEMENU_OUT);

					SetAlpha(32 - Abs(frame / MOTIONDIV % 32 - 16));
					DrawGoldAlpha(xOffset + DX / 2, DY / 2 + TABBUTTONGAP, ALPHA_TABTOCOLLECT, FONT_GOLD_LARGE, 1, CENTER, false, false, gScreenBuffer, gScreenLayer, false);
					SetAlpha(32);
				}
				break;
			case 1:
				effect.color = COLOR_BLACK;

				//진화 애니메이션
				if (menuFrame < 10 * 3 + 10 * 2 + 10 * 1 + 5 * 2 + 8 * 2 + 8 * 2 * 2) {

					width = ITEMHAMMERCNT * (ROULETTECARDSIZE_X + 8 * _2X);

					for (i = 0; i < ITEMHAMMERCNT; i++) {

						if (menuFrame >= 10 * 3 + 10 * 2 + 10 * 1 + 5 * 2 + 8 * 2 && menuFrame < 10 * 3 + 10 * 2 + 10 * 1 + 5 * 2 + 8 * 2 + 8 * 2 * 2) {
							SetAlpha(Min(32, menuFrame - (10 * 3 + 10 * 2 + 10 * 1 + 5 * 2 + 8 * 2)));
							SetColor(COLOR_WHITE);
							DrawFrame(x + (float)(DX / 2 - width / 2 + (ROULETTECARDSIZE_X + 8 * _2X) * i) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 300 * _2X) * zoom, (float)(ROULETTECARDSIZE_X)*zoom, (float)(ROULETTECARDSIZE_Y)*zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
							SetColor(false);
							SetAlpha(32);
						}
					}
				}

				//0: 카드가 
				//다섯개의 카드가 하나로 합쳐지고		
				if (menuFrame < 10 * 3 + 10 * 2 + 10 * 1 + 5 * 2 + 8 * 2 + 8 * 2 * 2 + FPS / 2) {

					//55 - 41 + 2
					if (menuFrame < 10 * 3) {
						DrawCmfDetail(CMF_NPC_HEART, PO_C122_6_C0 + (menuFrame / 3), x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + 64 * _2X) * zoom, LEFT, (float)3 * zoom, false, false, cvtDest, cvtLayer, buffering);
					}
					else if (menuFrame < 10 * 3 + 10 * 2) {
						DrawCmfDetail(CMF_NPC_HEART, PO_C122_6_C0 + ((menuFrame - (10 * 3)) / 2), x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + 64 * _2X) * zoom, LEFT, (float)3 * zoom, false, false, cvtDest, cvtLayer, buffering);
					}
					else if (menuFrame < 10 * 3 + 10 * 2 + 10 * 1) {
						DrawCmfDetail(CMF_NPC_HEART, PO_C122_6_C0 + ((menuFrame - (10 * 3 + 10 * 2)) / 1), x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + 64 * _2X) * zoom, LEFT, (float)3 * zoom, false, false, cvtDest, cvtLayer, buffering);
					}
					else if (menuFrame < 10 * 3 + 10 * 2 + 10 * 1 + 5 * 2) {
						DrawCmfDetail(CMF_NPC_HEART, PO_C122_6_SUM0 + ((menuFrame - (10 * 3 + 10 * 2 + 10 * 1)) / 2), x + DX / 2, y + DY / 2 + 64 * _2X, LEFT, (float)3 * zoom, false, false, cvtDest, cvtLayer, buffering);
					}
					else if (menuFrame < 10 * 3 + 10 * 2 + 10 * 1 + 5 * 2 + 8 * 2) {
						DrawCmfDetail(CMF_NPC_HEART, PO_C122_6_0 + (menuFrame - (10 * 3 + 10 * 2 + 10 * 1 + 5 * 2)) / 2, x + DX / 2, y + DY / 2 + 64 * _2X, LEFT, (float)3 * zoom, false, false, cvtDest, cvtLayer, buffering);
					}
					else if (menuFrame < 10 * 3 + 10 * 2 + 10 * 1 + 5 * 2 + 8 * 2 + 8 * 2 * 2) {
						DrawCmfDetail(CMF_NPC_HEART, PO_C122_SPARK0 + ((menuFrame - (10 * 3 + 10 * 2 + 10 * 1 + 5 * 2 + 8 * 2)) / 2 % 8), x + DX / 2, y + DY / 2 + 64 * _2X, LEFT, (float)3 * zoom, false, false, cvtDest, cvtLayer, buffering);
					}
					else {
						if (itemTypeNext == ITEM_CREW) {
							curStar = maxStar = crewData[itemDetailNext * CREWDATASIZE + CREWDATASIZE - 1] + 1;
						}
						else {
							curStar = maxStar = GetItemStar(itemTypeNext, itemDetailNext, itemGradeNext);
						}

						DrawRewardCard(itemTypeNext, itemDetailNext, itemGradeNext, itemLv, itemCnt, x + DX / 2 - ITEMCARDSIZE_X / 2, y + DY / 2 + (menuFrame - (10 * 3 + 10 * 2 + 10 * 1 + 5 * 2 + 8 * 2 + 8 * 2 * 2)) * 8 * _2X, false, 2, true, false, true, curStar, maxStar, true, cvtDest, cvtLayer, buffering);
					}

					if (menuFrame / 2 % 3 == 2)
						PlayMusic(M_IRON);

					if (menuFrame / 2 % 7)
						DrawSubText(textId[TEXT_ENCHANTING], 0, menuFrame % 7, x + DX / 2 - StringWidth(textId[TEXT_ENCHANTING], 1.0f) / 2, y - EQUIP_WIN_HEIGHT + 272 * _2X - 216 * _2X - 4 * _2X, 1.0f, cvtDest, cvtLayer, buffering);

					if (menuFrame == 21 * 2 - 1) {
						//조합석 차감
						robin.star -= itemEvolutionItem[itemDetail * TOTALGRADE * (ITEMMAXLEVEL + 1) + itemGrade * (ITEMMAXLEVEL + 1) + itemLv];
						it = GetItemPtr(ITEMPTR_INVEN + itemStartCnt[itemType / TOTALPLAYER] + itemDetail * TOTALGRADE + itemGrade);

						it->count -= ITEMHAMMERCNT;

						//마지막 등급이면 디테일을 하나 올려준다.
						if (itemGrade == GRADE_LEGEND) {
							robin.inven[ITEMPTR_INVEN + itemStartCnt[itemType / TOTALPLAYER] + (itemDetail + 1) * TOTALGRADE + 0].count++;
						}
						//그렇지 않으면 그레이드를 하나 올려준다. 
						else {
							robin.inven[ITEMPTR_INVEN + itemStartCnt[itemType / TOTALPLAYER] + itemDetail * TOTALGRADE + itemGrade++].count++;
						}


						PlayMusic(M_LEVELUP);

						RefreshStat(&ao[PLAYER]);
						//SaveFlag(0);
						SaveGame();

						depth = 3;
					}
				}
				else {
					DrawCmfDetail(CMF_NPC_HEART, PO_C122_BURST0 + Min(4, ((menuFrame / 4) % 7)), x + DX / 2, y + DY / 2 - 128 * _2X, LEFT, 3.0f, false, false, cvtDest, cvtLayer, buffering);

					if (itemTypeNext == ITEM_CREW) {
						curStar = maxStar = crewData[itemDetailNext * CREWDATASIZE + CREWDATASIZE - 1] + 1;
					}
					else {
						curStar = maxStar = GetItemStar(itemTypeNext, itemDetailNext, itemGradeNext);
					}

					DrawRewardCard(itemTypeNext, itemDetailNext, itemGradeNext, itemLv, itemCnt, x + DX / 2 - ITEMCARDSIZE_X / 2, y + DY / 2 + 108 * _2X, false, 2.0f, true, false, true, curStar, maxStar, true, cvtDest, cvtLayer, buffering);

					//강화성공시
					DrawEffect(EFFECT_LEVELUP_TEXT0 + (frame / 2) % 14, x + DX / 2, y + DY / 2 + 108 * _2X + 32 * _2X, 0, false, 3.0f, cvtDest, cvtLayer, buffering);

					DrawGoldAlpha(x + DX / 2, y + DY / 2 - 160 * _2X, ALPHA_CONGRATULATIONS, FONT_GOLD_LARGE, 1.0f, CENTER, true, false, cvtDest, cvtLayer, buffering);

					//DrawSubText(textId[TEXT_ENCHANTSUCCEED], 0, Min(5, menuFrame / 2 - 21), x + DX / 2 - StringWidth(textId[TEXT_ENCHANTSUCCEED]) / 2, y - EQUIP_WIN_HEIGHT + 272 * _2X - 216 * _2X - 4 * _2X, cvtDest, cvtLayer, buffering);

					SetRectPoint(xOffset, DY, DX, DY, TOUCH_FUNC_GAMEMENU_OUT);
				}
				break;
			}

			menuFrame++;

		}
		break;
	}
}

void DrawCombatPower(long long pow, int icon, int x, int y, int alpha, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	DrawRoundBar(x + (float)0 * zoom, y, 1.0f, ROUNDBAR_SMALL, BARCOLOR_RED, alpha, 0.5f * zoom, cvtDest, cvtLayer, buffering);

	DrawIcon(icon, x + (float)(5 * _2X) * zoom, y - (float)5 * _2X * zoom, 1.4f * zoom, COLOR_BROWN, false, false, 1, cvtDest, cvtLayer, buffering);
#ifdef NUMTTF
	DrawBigNumTTF(pow, x + (float)(COMBATPOWBARWIDTH - 10 * _2X) * zoom, y + (float)(-5 * _2X * 2) * zoom, NUM_FONT_NORMAL, RIGHT, false, false, (float)(COMBATPOWBARWIDTH - ITEMICONSIZE - 8 * _2X * 2) * zoom, true, zoom, true, cvtDest, cvtLayer, buffering);
#else
	DrawBigNum2Bold(pow, x + (float)(COMBATPOWBARWIDTH - 7 * _2X) * zoom, y - (float)(10 * _2X) * zoom, RIGHT, false, false, (float)(COMBATPOWBARWIDTH - ITEMICONSIZE * 1.2f - 13 * _2X) * zoom, true, NUM2ZOOM * 1.2f * zoom, true, cvtDest, cvtLayer, buffering);

#endif

}

void StageProgressDraw(int x, int y, int current, int progress, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i;

	DrawFrame(x, y, (float)STAGEPROGRESSBARWIDTH * zoom, (float)STAGEPROGRESSBARHEIGHT * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
	//for (i = 0; i < )
}

void RemainedTurnDraw(int x, int y, int current, int progress, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	float oldNumZoom = zoom;
	float newNumZoom = zoom;
	int oldAlpha = 32;
	int newAlpha = 0;
	float oldXOffset = 0.0f;
	float oldYOffset = 0.0f;
	float newXOffset = 0.0f;
	float newYOffset = 0.0f;

	if (remainedTurnFrame > 0)
	{
		float t = (float)remainedTurnFrame / FPS; // 0.0 ~ 1.0

		// ===== 이전 숫자(3) 애니메이션 =====
		// Phase 1: 쪼그라들기 (0.0 ~ 0.2)
		if (t >= 0.0f && t < 0.2f)
		{
			float phase = t / 0.2f; // 0.0 ~ 1.0
			float squashCurve = pow(phase, 2.0f);

			oldYOffset = -10.0f * _2X * zoom * squashCurve;
			oldNumZoom = zoom * (1.0f + 0.2f * squashCurve);
			oldAlpha = 32;
		}
		// Phase 2: 작은 포물선으로 우측 이동 (0.2 ~ 0.5)
		else if (t >= 0.2f && t < 0.5f)
		{
			float phase = (t - 0.2f) / 0.3f; // 0.0 ~ 1.0

			oldXOffset = 30.0f * _2X * zoom * phase;

			float verticalCurve = -4.0f * phase * (phase - 1.0f);
			oldYOffset = -10.0f * _2X * zoom + 15.0f * _2X * zoom * verticalCurve;

			if (phase < 0.3f)
			{
				oldNumZoom = zoom * (1.2f - 0.2f * (phase / 0.3f));
			}
			else
			{
				oldNumZoom = zoom;
			}
			oldAlpha = 32;
		}
		// Phase 3: 우측 끝에서 아래로 떨어지면서 페이드아웃 (0.5 ~ 0.8)
		else if (t >= 0.5f && t < 0.8f)
		{
			float phase = (t - 0.5f) / 0.3f; // 0.0 ~ 1.0

			oldXOffset = 30.0f * _2X * zoom + 10.0f * _2X * zoom * phase;

			float fallCurve = pow(phase, 2.0f);
			oldYOffset = 5.0f * _2X * zoom - 40.0f * _2X * zoom * fallCurve;

			oldNumZoom = zoom * (1.0f - 0.5f * phase);
			oldAlpha = 32 - (int)(32 * phase);
		}
		else
		{
			// Phase 3 이후에는 이전 숫자 안 그림
			oldAlpha = 0;
		}

		// ===== 새 숫자(2) 애니메이션 =====
		// Phase 4: 작게 나타나서 커지면서 정지 (0.85 ~ 0.95)
		if (t >= 0.85f && t < 0.95f)
		{
			float phase = (t - 0.85f) / 0.1f; // 0.0 ~ 1.0

			float riseCurve = 1.0f - pow(1.0f - phase, 3.0f);
			newYOffset = -25.0f * _2X * zoom * (1.0f - riseCurve);

			newNumZoom = zoom * (0.5f + 0.5f * riseCurve);

			newAlpha = (int)(32 * Min(phase * 2.0f, 1.0f));
		}
		// Phase 5: 정지 후 살짝 내려오며 안착 (0.95 ~ 1.0)
		else if (t >= 0.95f)
		{
			float phase = (t - 0.95f) / 0.05f; // 0.0 ~ 1.0

			float settleCurve = pow(phase, 2.0f);
			newYOffset = -3.0f * _2X * zoom * (1.0f - settleCurve);

			newNumZoom = zoom;
			newAlpha = 32;
		}

		// 이전 숫자(3) 그리기
		if (oldAlpha > 0)
		{
			SetAlpha(oldAlpha);
			DrawGoldNum(remainedTurn + 1, x + oldXOffset, y + oldYOffset, CENTER, 1, false, false, oldNumZoom, cvtDest, cvtLayer, buffering);
			SetAlpha(32);
		}

		// 새 숫자(2) 그리기
		if (newAlpha > 0)
		{
			SetAlpha(newAlpha);
			DrawGoldNum(remainedTurn, x + newXOffset, y + newYOffset, CENTER, 1, false, false, newNumZoom, cvtDest, cvtLayer, buffering);
			SetAlpha(32);
		}
	}
	else
	{
		DrawGoldNum(remainedTurn, x, y, CENTER, 1, false, false, zoom, cvtDest, cvtLayer, buffering);
	}

	CenterTextStr("Remained", x, y - (float)20 * _2X * zoom, 0.3f * zoom, cvtDest, cvtLayer, buffering);
	CenterTextStr("Turn", x, y - (float)24 * _2X * zoom, 0.3f * zoom, cvtDest, cvtLayer, buffering);

	if (remainedTurnFrame > 0)
		remainedTurnFrame++;
	if (remainedTurnFrame == FPS)
		remainedTurnFrame = 0;
}

void CrewSetDraw(int stage, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i;
	int stageCrewIdx;
	int stageCrewType;
	long long upgradePrice;
	bool opened;


	DrawImage(512, 19, 2, 612, x + (float)(DX / 2) * zoom + (float)(-512 / 2) * zoom, y, false, false, false, false, false, zoom, sprite[UI_NEW_IMG], cvtDest, cvtLayer, UI_NEW_IMG, false);
	CenterText(TEXT_MAPNAME + MAP_DIORAMA_CASTLE + stage, x + (float)(DX / 2) * zoom, y - (float)12 * _2X * zoom, 1.2f * zoom, cvtDest, cvtLayer, buffering);
	
	DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, x + (float)4 * _2X * zoom, y - (float)8 * _2X * zoom, false, false, false, false, false, 0.08f * zoom, sprite[MAP_DIORAMA_IMG + dioramaMapImg[stage]], cvtDest, cvtLayer, MAP_DIORAMA_IMG + dioramaMapImg[stage], false);
	//현재 최고 기록
	DrawGoldAlpha(x + (float)52 * _2X * zoom, y - (float)(18 * _2X) * zoom, ALPHA_MAX, FONT_GOLD_LARGE, 0.6f * zoom, LEFT, false, false, cvtDest, cvtLayer, buffering);
	DrawGoldAlpha(x + (float)52 * _2X * zoom, y - (float)(34 * _2X) * zoom, ALPHA_STAGE, FONT_GOLD_LARGE, 0.6f * zoom, LEFT, false, false, cvtDest, cvtLayer, buffering);

	DrawGoldNum(299 - stage * 10, x + (float)(DX / 2) * zoom, y - (float)(32 * _2X) * zoom, CENTER, false, false, false, 0.8f * zoom, cvtDest, cvtLayer, buffering);

	grayScale = false;

	for (i = 0; i < MAXCREW; i++) {
		stageCrewIdx = stage * MAXCREW + i + TOTALCHAR;//현재 인덱스
		stageCrewType = crewData[stageCrewIdx * CREWDATASIZE];

		curStar = robin.crewStar[stageCrewIdx];
		curMaxStar = robin.crewMaxStar[stageCrewIdx];
		maxStar = CREWMAXUPGRADELV;
		if (curStar < curMaxStar)
			upgradePrice = crewStarUpgradeGold[stageCrewIdx * CREWMAXUPGRADELV + curStar] / CREWUPGRADEPER;
		else
			upgradePrice = crewStarUpgradeGold[stageCrewIdx * CREWMAXUPGRADELV + curStar];


		ao[NPC].cmf = ao[NPC].type = ROBIN;
		ao[NPC].x = x + (float)(8 * _2X + CREWSET_XGAP * ((stage * MAXCREW + i) % MAXCREW) + ITEMICONSIZE) * zoom;
		ao[NPC].y = y - (float)(8 * _2X + 80 * _2X) * zoom;

		DrawImage(32 * _2X, 12 * _2X, 107 * _2X, 48 * _2X, ao[NPC].x - (float)16 * _2X * zoom, ao[NPC].y + (float)(2 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + 6], cvtDest, cvtLayer, MAP_OBJ_IMG + 6, buffering);

		if (stage == robin.crewStage && stageUpgradeMotion[i] > 0 && stageUpgradeMotion[i] < 11) {
			DrawPlayer(&ao[NPC], 2000 - 1 + LEVELUP_BACK0 + stageUpgradeMotion[i], ao[NPC].x, ao[NPC].y, false, zoom, false, false, false, cvtDest, cvtLayer, buffering);
		}

		//if (i / MAXCREW > robin.crewStage)
		//	SetColor(COLOR_BLACK);//grayScale = 32;
		//else if (!robin.crewMaxStar[stage * MAXCREW + i])
		//	grayScale = 32;
		
		DrawCmfDetailShadow(enemyData[crewData[stageCrewIdx * CREWDATASIZE] * ENEMYDATASIZE + 0], enemyIconPos[crewData[stageCrewIdx * CREWDATASIZE] * 3 + 0], ao[NPC].x, ao[NPC].y, RIGHT, enemyIconZoom[crewData[stageCrewIdx * CREWDATASIZE]] * zoom, cvtDest, cvtLayer, buffering);
		SetColor(false);
		grayScale = 0;
		//DrawIcon(GetItemIcon(ITEM_STATUE, i, false), x + (float)(36 * _2X + 72 * _2X * (i % 4)) * zoom, y - (float)(64 * _2X + 80 * _2X * (i / 4)), 2.0f * zoom, COLOR_BROWN, false, true, cvtDest, cvtLayer, buffering);
		//if (!robin.crewMaxStar[(stage * MAXCREW + i)])
		//	DrawIcon(ICON_EVENT_LOCK, ao[NPC].x - (float)ITEMICONSIZE / 2 * zoom, ao[NPC].y - (float)2 * _2X * zoom, zoom, COLOR_BROWN, false, false, true, cvtDest, cvtLayer, buffering);
		//else
			DrawStar(ICON_CROWN, ao[NPC].x, ao[NPC].y - (float)12 * _2X * zoom, robin.crewStar[(stage * MAXCREW + i)], robin.crewMaxStar[(stage * MAXCREW + i)], CREWMAXUPGRADELV, CENTER, true, 0.7f * zoom, cvtDest, cvtLayer, buffering);

		if (robin.crewStar[(stage * MAXCREW + i)] < robin.crewMaxStar[(stage * MAXCREW + i)])
			DrawEffect(DEBUF_STUN0 + frame % 6, ao[NPC].x, ao[NPC].y + (float)6 * _2X * zoom, RIGHT, false, zoom, cvtDest, cvtLayer, buffering);

		if (stage == robin.crewStage && stageUpgradeMotion[i] > 0 && stageUpgradeMotion[i] < 11) {
			DrawPlayer(&ao[NPC], 2000 - 1 + LEVELUP_FRONT0 + stageUpgradeMotion[i], ao[NPC].x, ao[NPC].y, false, zoom, false, false, false, cvtDest, cvtLayer, buffering);

			DrawEffect(EFFECT_LEVELUP_TEXT0 - 1 + (stageUpgradeMotion[i] < 11 ? stageUpgradeMotion[i] : Max(11, stageUpgradeMotion[i] - 5)), ao[NPC].x, ao[NPC].y - (float)(16 * _2X) * zoom, 0, false, zoom, cvtDest, cvtLayer, buffering);

		}

		if (stageUpgradeMotion[i] == 3)
			PlayMusic(M_LEVELUP);

		if (stageUpgradeMotion[i] > 0)
			stageUpgradeMotion[i]++;

		if (stageUpgradeMotion[i] == 11)
			stageUpgradeMotion[i] = 0;


		//이후 데미지
		
		if (curStar < curMaxStar) {
			DrawBuyButton(ao[NPC].x - (float)CREWSET_UPGRADEBUTTON_X / 2 * zoom, ao[NPC].y - (float)24 * _2X * zoom, (float)CREWSET_UPGRADEBUTTON_X * zoom, (float)(32 * _2X) * zoom, frame, robin.gold < upgradePrice ? FRAME_GREY : FRAME_RED, upgradePrice, CURRENCY_GOLD, 0.8f * zoom, false, false, false, cvtDest, cvtLayer, buffering);
			if (robin.gold >= upgradePrice) {
				SetRectPoint(ao[NPC].x - (float)CREWSET_UPGRADEBUTTON_X / 2 * zoom, ao[NPC].y - (float)24 * _2X * zoom, (float)CREWSET_UPGRADEBUTTON_X * zoom, (float)(32 * _2X) * zoom, TOUCH_FUNC_CREWSTARUPGRADE + i);
			}
		}
		//아직 최대값에 도달하지 못하면
		else if (curStar < maxStar) {
			DrawBuyButton(ao[NPC].x - (float)CREWSET_UPGRADEBUTTON_X / 2 * zoom, ao[NPC].y - (float)24 * _2X * zoom, (float)CREWSET_UPGRADEBUTTON_X * zoom, (float)(32 * _2X) * zoom, frame, robin.gold < upgradePrice ? FRAME_GREY : FRAME_GREEN, upgradePrice, CURRENCY_GOLD, 0.8f * zoom, false, false, false, cvtDest, cvtLayer, buffering);
			if (robin.gold >= upgradePrice) {
				SetRectPoint(ao[NPC].x - (float)CREWSET_UPGRADEBUTTON_X / 2 * zoom, ao[NPC].y - (float)24 * _2X * zoom, (float)CREWSET_UPGRADEBUTTON_X * zoom, (float)(32 * _2X) * zoom, TOUCH_FUNC_CREWSTARUPGRADE + i);
			}
		}
		//최대값에 도달하면

		else {

			DrawMaxButton(ao[NPC].x - (float)CREWSET_UPGRADEBUTTON_X / 2 * zoom, ao[NPC].y - (float)24 * _2X * zoom, (float)CREWSET_UPGRADEBUTTON_X * zoom, (float)(32 * _2X) * zoom, ALPHA_MAX, 0.8f * zoom, cvtDest, cvtLayer, buffering);
		}

	}
}

void CrewUpgradeMenuDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i;
	int stageCrewIdx;
	int stageCrewType;
	int stageInfoCurFrame = stageInfoFrame;
	int detail;
	float yGap = REWARDCARDSIZE_Y + 8 * _2X;
	float buttonGap = 120 * _2X * zoom;
	long long upgradePrice;

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], cvtDest, cvtLayer, UI_PAPER_POPUP_IMG, false);

	DrawLabel(x + (float)(POPUPWINDOWSIZE_X - 88 * _2X) / 2 * zoom, y - (float)0 * _2X * zoom, TEXT_BORDERGUARD, zoom, cvtDest, cvtLayer, buffering);

	CrewSetDraw(robin.crewStage, x + (float)(16 * _2X) * zoom, y - (float)(60 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

	for (i = 0; i < MAXCREW; i++) {
		stageCrewIdx = robin.crewStage * MAXCREW + i;//현재 인덱스
		stageCrewType = crewData[stageCrewIdx * CREWDATASIZE];

		curStar = robin.crewStar[stageCrewIdx];
		curMaxStar = robin.crewMaxStar[stageCrewIdx];
		maxStar = CREWMAXUPGRADELV;
		if (curStar < curMaxStar)
			upgradePrice = crewStarUpgradeGold[stageCrewIdx * CREWMAXUPGRADELV + curStar] / CREWUPGRADEPER;
		else
			upgradePrice = crewStarUpgradeGold[stageCrewIdx * CREWMAXUPGRADELV + curStar];

		ao[NPC].cmf = ao[NPC].type = ROBIN;
		ao[NPC].x = x + (float)(16 * _2X) * zoom + (float)(16 * _2X + CREWSET_XGAP * (i % MAXCREW) + ITEMICONSIZE) * zoom;
		ao[NPC].y = y - (float)(52 * _2X) * zoom - (float)(64 * _2X) * zoom;


		CenterText(TEXT_HERO_PARAM_DMG, ao[NPC].x, ao[NPC].y - (float)24 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);
		//현재 데미지
		DrawNumTTF(GetCrewDmg(stageCrewIdx, robin.crewStar[stageCrewIdx]), ao[NPC].x, ao[NPC].y - (float)40 * _2X * zoom, NUM_FONT_NORMAL, CENTER, false, false, true, zoom, false, cvtDest, cvtLayer, buffering);

		//이후 데미지
		if (curStar < maxStar) {
			DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - frame % 8), ao[NPC].x + (float)16 * _2X, ao[NPC].y - (float)64 * _2X * zoom, 0, 180, 1.5f * zoom, cvtDest, cvtLayer, buffering);

			DrawNumTTF(GetCrewDmg(stageCrewIdx, robin.crewStar[stageCrewIdx] + 1), ao[NPC].x, ao[NPC].y - (float)88 * _2X * zoom, NUM_FONT_NORMAL, CENTER, false, false, true, zoom, false, cvtDest, cvtLayer, buffering);
		}

		if (curStar < curMaxStar) {
			DrawBuyButton(ao[NPC].x - (float)CREWSET_UPGRADEBUTTON_X / 2 * zoom, ao[NPC].y - (float)102 * _2X * zoom, (float)CREWSET_UPGRADEBUTTON_X * zoom, (float)(32 * _2X) * zoom, frame, robin.gold < upgradePrice ? FRAME_GREY : FRAME_RED, upgradePrice, CURRENCY_GOLD, 0.8f * zoom, false, false, false, cvtDest, cvtLayer, buffering);
			if (robin.gold >= upgradePrice) {
				SetRectPoint(ao[NPC].x - (float)CREWSET_UPGRADEBUTTON_X / 2 * zoom, ao[NPC].y - (float)102 * _2X * zoom, (float)CREWSET_UPGRADEBUTTON_X * zoom, (float)(32 * _2X) * zoom, TOUCH_FUNC_CREWSTARUPGRADE + i);
			}
		}
		//아직 최대값에 도달하지 못하면
		else if (curStar < maxStar) {
			DrawBuyButton(ao[NPC].x - (float)CREWSET_UPGRADEBUTTON_X / 2 * zoom, ao[NPC].y - (float)102 * _2X * zoom, (float)CREWSET_UPGRADEBUTTON_X * zoom, (float)(32 * _2X) * zoom, frame, robin.gold < upgradePrice ? FRAME_GREY : FRAME_GREEN, upgradePrice, CURRENCY_GOLD, 0.8f * zoom, false, false, false, cvtDest, cvtLayer, buffering);
			if (robin.gold >= upgradePrice) {
				SetRectPoint(ao[NPC].x - (float)CREWSET_UPGRADEBUTTON_X / 2 * zoom, ao[NPC].y - (float)102 * _2X * zoom, (float)CREWSET_UPGRADEBUTTON_X * zoom, (float)(32 * _2X) * zoom, TOUCH_FUNC_CREWSTARUPGRADE + i);
			}
		}
		//최대값에 도달하면

		else {

			DrawMaxButton(ao[NPC].x - (float)CREWSET_UPGRADEBUTTON_X / 2 * zoom, ao[NPC].y - (float)102 * _2X * zoom, (float)CREWSET_UPGRADEBUTTON_X * zoom, (float)(32 * _2X) * zoom, ALPHA_MAX, 0.8f * zoom, cvtDest, cvtLayer, buffering);
		}

	}

	//for (i = 0; i < (TOTAL_CREW + MAXCREW - 1) / MAXCREW; i++) {
	//	CrewSetDraw(i, x + (float)(32 * _2X) * zoom, y + scY[MENU_COLLECTIONS] - (float)(32 * _2X + 24 * _2X + COLLECTION_YGAP * i) * zoom, zoom, cvtDest, cvtLayer, buffering);
	//}

	LineText(TEXT_BORDERGUARD_DESC, x + (float)32 * _2X * zoom, y - (float)260 * _2X * zoom, (float)(POPUPWINDOWSIZE_X - 64 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

	CrewSetDraw(robin.crewStage + 1, x + (float)(16 * _2X) * zoom, y - (float)(312 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

}

void HowToGetHeroesDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], cvtDest, cvtLayer, UI_PAPER_POPUP_IMG, false);

	//일단 히어로를 획득하는 조건을 정리하자.
	//1번 레벨, 2번 스테이지
	//레벨로 하면 상자를 많이 열어야 하니까 하트가 많이 필요하고
	//스테이지로 하면 

	//DrawLabel(x + (float)(POPUPWINDOWSIZE_X - 88 * _2X) / 2 * zoom, y - (float)0 * _2X * zoom, TEXT_BORDERGUARD, zoom, cvtDest, cvtLayer, buffering);

	DrawEffect(EFFECT_LEVELUP_TEXT10, x + (float)POPUPWINDOWSIZE_X / 2, y, LEFT, false, zoom, cvtDest, cvtLayer, buffering);
	DrawStarNum(ICON_STAR, 1, x + (float)POPUPWINDOWSIZE_X / 2, y, 2.0f * zoom, cvtDest, cvtLayer, buffering);
}

void HowToGetCrewsDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], cvtDest, cvtLayer, UI_PAPER_POPUP_IMG, false);

	//일단 크류자리를 오픈하는 조건을 정리하자.
	//1번 레벨, 2번 스테이지
	//레벨로 하면 상자를 많이 열어야 하니까 하트가 많이 필요하고
	//스테이지로 하면 

	//DrawLabel(x + (float)(POPUPWINDOWSIZE_X - 88 * _2X) / 2 * zoom, y - (float)0 * _2X * zoom, TEXT_BORDERGUARD, zoom, cvtDest, cvtLayer, buffering);

}

//현재 업그레이드가 가능한 
int GetItemCntUpgradePossible(void)
{
	int i, j;
	int itemCnt = 0;
	int itemType;
	int itemDetail;
	int itemGrade;
	int itemLv = 0;
	int invenIdx;

	for (i = 0; i < TOTAL_COLLECTIONS; i++) {
		for (j = 0; j < COLLECTIONSITEMCNT; j++) {
			itemType = collectionData[i * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + j * COLLECTIONSDATASIZE + 0];
			itemDetail = collectionData[i * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + j * COLLECTIONSDATASIZE + 1];
			itemGrade = collectionData[i * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + j * COLLECTIONSDATASIZE + 2];
			invenIdx = GetInvenIdx(itemType, itemDetail, itemGrade);
			if (invenIdx != -1) {
				itemLv = robin.inven[invenIdx].cooldown;
				if (robin.hammer >= GetUpgradeHammer(itemType, itemDetail, itemGrade, itemLv))
					itemCnt++;
			}
		}
	}

	return itemCnt;
}

void CollectionsDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i, j;
	int w = COLLECTIONCARDSIZE_X;
	int h = COLLECTIONCARDSIZE_Y;
	int star = 1;
	int width;
	int repItem = 0;
	int setItemCnt = 0;
	int rewardIcon;
	int itemType, itemDetail, itemGrade, itemLv, itemCnt, itemSlot, itemIdx, itemIcon;
	ITEM* it;
	OBJECT* pObj = &ao[curHero];
	int starCnt;
	long long realValue;
	float numWidth = (float)(32 * _2X) * zoom;
	int actionCardIdx;
	int skillIdx;
	int swordSkillIdx;
	int collectionIdx;
	int menuText[] = { TEXT_EQUIPMENT, TEXT_SKILL };
	int charType = ROBIN;
	long long upgradePrice;

	for (i = 0; i < (menuCur < EQUIP_NECK ? itemTypeCnt[menuCur * TOTALCHAR + curHero] : itemTypeCnt[menuCur - EQUIP_NECK + ITEM_NECK]); i++) {
		ao[NPC].cmf = ao[NPC].type = curHero;
		ao[NPC].x = x + (float)(16 * _2X + CREWSET_XGAP * ((i * MAXCREW + i) % MAXCREW) + ITEMICONSIZE) * zoom;
		ao[NPC].y = y - (float)(88 * _2X) * (i / MAXCREW) * zoom;

		DrawImage(32 * _2X, 12 * _2X, 107 * _2X, 48 * _2X, ao[NPC].x - (float)16 * _2X * zoom, ao[NPC].y + (float)(2 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + 6], cvtDest, cvtLayer, MAP_OBJ_IMG + 6, buffering);

		//if (robin.getCrews[i] == false)
		//	grayScale = 32;
		//DrawCmfDetailShadow(enemyData[crewData[i * CREWDATASIZE] * ENEMYDATASIZE + 0], enemyIconPos[crewData[i * CREWDATASIZE] * 3 + 0], ao[NPC].x, ao[NPC].y, RIGHT, enemyIconZoom[crewData[i * CREWDATASIZE]] * zoom, cvtDest, cvtLayer, buffering);
		switch (menuCur) {
		case EQUIP_NECK:
			itemType = ITEM_NECK;
			break;
		case EQUIP_RING:
			itemType = ITEM_RING;
			break;
		default:
			itemType = TOTALCHAR * menuCur + curHero;
			break;
		}
		itemDetail = i;
		itemGrade = GRADE_NORMAL;
		//if (robin.inven[i].count == 0)
		//	grayScale = 32;
		DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), ao[NPC].x - (float)ITEMICONSIZE * zoom, ao[NPC].y + (float)(2 * ITEMICONSIZE - 4 * _2X) * zoom, 1.8f * zoom, COLOR_BROWN, false, true, (float)1 * _2X * zoom, cvtDest, cvtLayer, buffering);
		SetColor(false);
		grayScale = 0;

		//if (robin.inven[i].count == 0)
		//	DrawIcon(ICON_EVENT_LOCK, ao[NPC].x - (float)ITEMICONSIZE / 2 * zoom, ao[NPC].y - (float)2 * _2X * zoom, zoom, COLOR_BROWN, false, false, true, cvtDest, cvtLayer, buffering);
		//else
			DrawStar(ICON_CROWN, ao[NPC].x, ao[NPC].y - (float)12 * _2X * zoom, robin.crewStar[i], robin.crewMaxStar[i], CREWMAXUPGRADELV, CENTER, true, 0.7f * zoom, cvtDest, cvtLayer, buffering);

		upgradePrice = itemPrice[itemStartCnt[itemType] + itemDetail];

		//DrawBuyButton(ao[NPC].x - (float)CREWSET_UPGRADEBUTTON_X / 2 * zoom, ao[NPC].y - (float)22 * _2X * zoom, (float)CREWSET_UPGRADEBUTTON_X * zoom, (float)(32 * _2X) * zoom, frame, robin.gold < upgradePrice ? FRAME_GREY : FRAME_RED, upgradePrice, CURRENCY_GOLD, 0.8f * zoom, false, false, false, cvtDest, cvtLayer, buffering);
		DrawBuyButton(ao[NPC].x - (float)CREWSET_UPGRADEBUTTON_X / 2 * zoom, ao[NPC].y - (float)22 * _2X * zoom, (float)CREWSET_UPGRADEBUTTON_X * zoom, (float)(32 * _2X) * zoom, frame, FRAME_GREEN, upgradePrice, CURRENCY_GOLD, 0.8f * zoom, false, false, false, cvtDest, cvtLayer, buffering);

		if (menuDepth == 0) {
			SetRectPoint(ao[NPC].x - (float)CREWSET_UPGRADEBUTTON_X / 2 * zoom, ao[NPC].y + (float)32 * _2X * zoom, (float)CREWSET_UPGRADEBUTTON_X * zoom, (float)(80 * _2X) * zoom, TOUCH_FUNC_ITEMDETAIL + i);
		}
	}
	//Top menu
	//if (menuCur < EQUIP_NECK)
	
	//BarDraw(&bar[BAR_GOLD], zoom, cvtDest, cvtLayer, buffering);
	//BarDraw(&bar[BAR_COMBATPOWERALL], zoom, cvtDest, cvtLayer, buffering);

	//HeroSelectButtonList(x + (float)(DX - HEROBUTTON_X - 1 * _2X) * zoom, DY - (float)48 * _2X * zoom, zoom, curHero, false, false, cvtDest, cvtLayer, buffering);
	HeroSelectButtonList(x + 1 * _2X * zoom, DY - (float)8 * _2X * zoom, zoom, curHero, menuDepth == 0 ? true : false, true, cvtDest, cvtLayer, buffering);


	//Bottom Menu
	for (i = 0; i < TOTALEQUIP; i++) {
		DrawFrame((float)(2 * _2X + i * (COLLECTIONMENU_X + 4 * _2X)) * zoom, (float)(COLLECTIONMENU_Y + 2 * _2X + BOTTOMMENUHEIGHT + (menuCur == i ? 8 * _2X : 0 * _2X)) * zoom, (float)COLLECTIONMENU_X * zoom, (float)COLLECTIONMENU_Y * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
		itemType = itemSlotEquip[i] + (i < EQUIP_NECK ? curHero : 0);
		itemDetail = STAR1;
		itemGrade = GRADE_NORMAL;

		switch (i) {
		default:
			//case EQUIP_WEAPON:
			//case EQUIP_HELM:
			//case EQUIP_ARMOR:
			//case EQUIP_PANTS:
			//case EQUIP_GLOVE:
			//case EQUIP_BOOTS:
			//case EQUIP_NECK:
			//case EQUIP_RING:
			DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), (float)(6 * _2X + i * (COLLECTIONMENU_X + 4 * _2X)) * zoom, (float)(COLLECTIONMENU_Y + 2 * _2X - 4 * _2X + BOTTOMMENUHEIGHT + (menuCur == i ? 8 * _2X : 0 * _2X)) * zoom, 1.7f * zoom, COLOR_BROWN, false, false, 1.0f * zoom, cvtDest, cvtLayer, buffering);
			break;
		}

		if (menuCur != i && menuDepth == 0) {
			SetRectPoint((float)(2 * _2X + i * (COLLECTIONMENU_X + 4 * _2X)) * zoom, (float)(COLLECTIONMENU_Y + 2 * _2X + BOTTOMMENUHEIGHT + (menuCur == i ? 8 * _2X : 0 * _2X)) * zoom, (float)COLLECTIONMENU_X * zoom, (float)COLLECTIONMENU_Y * zoom, TOUCH_FUNC_COLLECTIONS_EQUIP + i);
		}
	}


	switch (menuDepth) {
		//상세보기
		//menuItem 으로 하자.
		//
	case 1:
		ScreenDarken(SCREENDARKEN);

		menuItem = 1;

		itemType = menuCur;
		itemDetail = menuItem;
		itemGrade = GRADE_NORMAL;
		itemLv = GetItemLv(itemType, itemDetail, itemGrade);

		EquipInfoDraw(&ao[menuCur].equip[EQUIP_WEAPON], x, y, itemType, itemDetail, itemGrade, /*menuDepth - 2*/0, menuX, 1.0f, cvtDest, cvtLayer, buffering);
		
		break;
	}
	return;

	SetSectionClip(0, y - (float)32 * _2X * zoom, (float)POPUPWINDOWSIZE_X * zoom, (float)(POPUPWINDOWSIZE_Y - 16 * _2X) * zoom, false);

	for (i = 0; i < TOTALCHAR; i++) {
		EnemyProfileDraw(x + (float)(28 * _2X + 92 * _2X * i) * zoom, y - (float)(48 * _2X) * zoom, i, false, false, zoom, cvtDest, cvtLayer, buffering);
		SetRectPoint(x + (float)(28 * _2X + 92 * _2X * i) * zoom, y - (float)(48 * _2X) * zoom, (float)80 * _2X * zoom, (float)32 * _2X * zoom, TOUCH_FUNC_TABMENUX_1 + i);
		CenterText(TEXT_MONSTERNAME_START + i, x + (float)(28 * _2X + 92 * _2X * i + 52 * _2X) * zoom, y - (float)(48 * _2X + 12 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

		//DrawFrame(x + (float)(28 * _2X + 92 * _2X * i) * zoom, y - (float)(48 * _2X) * zoom, (float)80 * _2X * zoom, (float)32 * _2X * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
		//DrawPlayer(&ao[i], (menuX == i ? frame / 2 % 4 : 0), x + (float)(44 * _2X + 92 * _2X * i) * zoom, y - (float)(48 * _2X + 20 * _2X) * zoom, RIGHT, zoom, false, false, true, cvtDest, cvtLayer, buffering);
		//CenterText(TEXT_MONSTERNAME_START + i, x + (float)(28 * _2X + 92 * _2X * i + 52 * _2X) * zoom, y - (float)(48 * _2X + 12 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
		//SetRectPoint(x + (float)(28 * _2X + 92 * _2X * i) * zoom, y - (float)(48 * _2X) * zoom, (float)80 * _2X * zoom, (float)32 * _2X * zoom, TOUCH_FUNC_TABMENUX_1 + i);

	}

	switch (menuCur) {
		//히어로
	case COLLECTIONMENU_EQUIP:

		HeroStatDraw(&ao[curHero], x + (float)0 * _2X * zoom, y + scY[MENU_COLLECTIONS] - (float)52 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

		break;
		//스킬
	}


	UnSectionClip(false);

	return;
	switch (menuDepth) {
	case 0:
		for (i = 0; i < TOTAL_COLLECTIONS; i++) {
			repItem = GetHighestCollections(i);

			itemType = collectionData[COLLECTIONSITEMCNT * COLLECTIONSDATASIZE * i + repItem * COLLECTIONSDATASIZE + 0];
			itemDetail = collectionData[COLLECTIONSITEMCNT * COLLECTIONSDATASIZE * i + repItem * COLLECTIONSDATASIZE + 1];
			itemGrade = collectionData[COLLECTIONSITEMCNT * COLLECTIONSDATASIZE * i + repItem * COLLECTIONSDATASIZE + 2];
			itemLv = GetItemLv(itemType, itemDetail, itemGrade);

			itemSlot = GetEquipSlot(itemType, itemDetail, itemGrade);

			setItemCnt = 0;

			for (j = 0; j < COLLECTIONSITEMCNT; j++) {
				if (GetInvenIdx(collectionData[COLLECTIONSITEMCNT * COLLECTIONSDATASIZE * i + j * COLLECTIONSDATASIZE + 0], collectionData[COLLECTIONSITEMCNT * COLLECTIONSDATASIZE * i + j * COLLECTIONSDATASIZE + 1], collectionData[COLLECTIONSITEMCNT * COLLECTIONSDATASIZE * i + j * COLLECTIONSDATASIZE + 2]) != -1) {
					setItemCnt++;
				}
			}

			DrawImage(32 * _2X, 48 * _2X, 32 * _2X, 0 * _2X, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2, false, false, false, false, false, 2.0f, sprite[MAP_OBJ_IMG + 17], gScreenBuffer, gScreenLayer, MAP_OBJ_IMG + 17, false);
			ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 16 * _2X, SHADOW_IMG, 2.0f, gScreenBuffer, gScreenLayer, false);

			if (setItemCnt == 0)
				SetColor(COLOR_BLACK);

			DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 4 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X + 32 * _2X + (setItemCnt == COLLECTIONSITEMCNT ? -Abs((frame + i) / 2 % 32 - 16) : 0), 2.0f, false, false, false, true, gScreenBuffer, gScreenLayer, false);

			SetColor(false);

			if (setItemCnt > 0)
				for (j = 0; j < COLLECTIONSITEMCNT; j++) {
					itemType = collectionData[COLLECTIONSITEMCNT * COLLECTIONSDATASIZE * i + j * COLLECTIONSDATASIZE + 0];
					itemDetail = collectionData[COLLECTIONSITEMCNT * COLLECTIONSDATASIZE * i + j * COLLECTIONSDATASIZE + 1];
					itemGrade = collectionData[COLLECTIONSITEMCNT * COLLECTIONSDATASIZE * i + j * COLLECTIONSDATASIZE + 2];
					itemLv = GetItemLv(itemType, itemDetail, itemGrade);

					itemSlot = GetEquipSlot(itemType, itemDetail, itemGrade);

					if (GetInvenIdx(itemType, itemDetail, itemGrade) == -1/* || robin.inven[GetInvenIdx(itemType, itemDetail, itemGrade)].count == 0*/) {
						SetColor(COLOR_BLACK);
						DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + (j % 3) * (ITEMICONSIZE + 4 * _2X) + 22 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 4 * _2X - 48 * _2X - (j / 3) * (ITEMICONSIZE + 4 * _2X), 1.0f, false, false, false, true, gScreenBuffer, gScreenLayer, false);
					}
					else {
						if (itemSlot == -1)
							grayScale = 32;
						DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + (j % 3) * (ITEMICONSIZE + 4 * _2X) + 22 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 4 * _2X - 48 * _2X - (j / 3) * (ITEMICONSIZE + 4 * _2X), 1.0f, COLOR_BROWN, false, false, true, gScreenBuffer, gScreenLayer, false);

					}

					grayScale = 0;
					SetColor(false);
				}


			//몇분의 몇을 모았는지를 보여주는 
			if (setItemCnt > 0) {
				DrawNum(setItemCnt, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 22 * _2X - 14 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X - 32 * _2X + 18 * _2X, NUM_FONT_NORMAL, LEFT, false, false, false, 1.0f, true, gScreenBuffer, gScreenLayer, false);
				DrawText(TEXT_SLASH, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 22 * _2X - 2 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X - 32 * _2X - 2 * _2X + 18 * _2X, 1.0f, gScreenBuffer, gScreenLayer, false);
				DrawNum(COLLECTIONSITEMCNT, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 22 * _2X + 6 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X - 32 * _2X + 18 * _2X, NUM_FONT_NORMAL, LEFT, false, false, false, 1.0f, true, gScreenBuffer, gScreenLayer, false);
			}
			//6개가 다 장착되어 있어서 스킬이 활성화 되어 있으면
			if (GetFullEquipedCollectionIdx() == i)
				DrawNeutral(OBJ_STAMPEFFECT0 + (frame / 3 % 8), x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 4 * _2X + 16 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X, 0, 1.0f, gScreenBuffer, gScreenLayer, false);
			//만약 6개가 다 모여만 있으면
			else if (setItemCnt == COLLECTIONSITEMCNT) {
				//아무것도 하지 않는다.
			}
			else if (setItemCnt > 0) {
				//아무것도 하지 않는다.
			}
			//아무것도 없으면
			else
				DrawIcon(ICON_EVENT_LOCK, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 4 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X + 32 * _2X - 12 * _2X - 52 * _2X, 2.0f, false, false, false, true, gScreenBuffer, gScreenLayer, false);

			DrawLabel(x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + 8 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - 88 * _2X - TSIZE * 2, TEXT_COLLECTIONS + i, 1.0f, gScreenBuffer, gScreenLayer, false);

			if (JoyStickPressPossible() == true && setItemCnt > 0)
				SetRectPoint(x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + 16 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - 32 * _2X, COLLECTIONCARDSIZE_X - 36 * _2X, COLLECTIONCARDSIZE_Y - 16 * _2X, TOUCH_FUNC_COLLECTIONS_DETAIL + i);

		}
		break;
	case 1:
		y = DY / 2 + 236 * _2X;

		collectionIdx = menuCur;

		for (j = 0; j < COLLECTIONSITEMCNT; j++) {
			itemType = collectionData[menuCur * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + j * COLLECTIONSDATASIZE + 0];
			itemDetail = collectionData[menuCur * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + j * COLLECTIONSDATASIZE + 1];
			itemGrade = collectionData[menuCur * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + j * COLLECTIONSDATASIZE + 2];
		}

		CollectionDetailListDraw(xOffset, y, menuCur, 1.0f, gScreenBuffer, gScreenLayer, false);

		SetAlpha(28);
		GradiationFrame(x + DX / 2 - 160 * _2X, y - 316 * _2X, 320 * _2X, 24 * _2X, 0, gScreenBuffer, gScreenLayer, false);
		SetAlpha(32);
		CenterText(TEXT_ACTIONCARDINFO, x + DX / 2, y - 316 * _2X - 8 * _2X, 1.0f, gScreenBuffer, gScreenLayer, false);

		SetAlpha(28);
		GradiationFrame(x + DX / 2 - 160 * _2X, y - 400 * _2X, 320 * _2X, 24 * _2X, 0, gScreenBuffer, gScreenLayer, false);
		SetAlpha(32);
		CenterText(TEXT_COLLECTIONREWARD, x + DX / 2, y - 400 * _2X - 8 * _2X, 1.0f, gScreenBuffer, gScreenLayer, false);

		//if (robin.collectionRewardGet[menuCur] == true)
		//	grayScale = 32;
		DrawIcon(GetItemIcon(collectionReward[menuCur * 4 + 0], collectionReward[menuCur * 4 + 1], collectionReward[menuCur * 4 + 2]), x + DX / 2 - (GetNumDx(collectionReward[menuCur * 4 + 3], false, NUM_FONT_LARGE, false, true, 1.5f * zoom / 2, true) + (float)ITEMICONSIZE * zoom + (float)(2 * _2X) * zoom) / 2, (y - 400 * _2X - 26 * _2X) * zoom / 2, zoom, false, false, false, true, gScreenBuffer, gScreenLayer, false);
		DrawNum(collectionReward[menuCur * 4 + 3], x + DX / 2 - (GetNumDx(collectionReward[menuCur * 4 + 3], false, NUM_FONT_LARGE, false, true, 1.5f * zoom / 2, true) + (float)ITEMICONSIZE * zoom + (float)(2 * _2X) * zoom) / 2 + (float)ITEMICONSIZE * zoom + (float)(2 * _2X) * zoom, (y - 400 * _2X - 26 * _2X) * zoom / 2, NUM_FONT_LARGE, LEFT, 0, false, true, 1.5f * zoom / 2, true, gScreenBuffer, gScreenLayer, false);
		grayScale = 0;

		//모두 장착
		//아직 장착되지 않고 
		if (GetFullEquipedCollectionIdx() != menuCur && IsCollectionFull(menuCur) == true) {
			DrawTextButton(x + DX / 2 - 40 * _2X, y - 410 * _2X - 46 * _2X - 12 * _2X, 80 * _2X, 28 * _2X, 0, false, 1, false, TEXT_EQUIPALL, gScreenBuffer, gScreenLayer, false);
			SetRectPoint(x + DX / 2 - 40 * _2X, y - 410 * _2X - 46 * _2X - 12 * _2X, 80 * _2X, 28 * _2X, TOUCH_FUNC_EQUIPALL + menuCur);
		}
		else
			DrawTextButton(x + DX / 2 - 40 * _2X, y - 410 * _2X - 46 * _2X - 12 * _2X, 80 * _2X, 28 * _2X, 0, 32, 1, false, TEXT_EQUIPALL, gScreenBuffer, gScreenLayer, false);

		if (winAniFrame > 0) {
			winAniFrame++;

			DrawNeutral(OBJ_STAMPEFFECT0 + (frame / 3 % 8), x + 64 * _2X, y - 410 * _2X - 46 * _2X - 32 * _2X, 0, 1.0f, gScreenBuffer, gScreenLayer, false);

			if (winAniFrame == FPS)
				winAniFrame = 0;
		}

		//if (x < 10000)
		//	return;

		DrawPlayerCostume(
			ROBIN,
			pObj->equip[EQUIP_WEAPON].type != EMPTY ? pObj->equip[EQUIP_WEAPON].detail : -1, pObj->equip[EQUIP_WEAPON].type != EMPTY ? pObj->equip[EQUIP_WEAPON].grade : 0,
			pObj->equip[EQUIP_GLOVE].type != EMPTY ? pObj->equip[EQUIP_GLOVE].detail : -1, pObj->equip[EQUIP_GLOVE].type != EMPTY ? pObj->equip[EQUIP_GLOVE].grade : 0,
			pObj->equip[EQUIP_HELM].type != EMPTY ? pObj->equip[EQUIP_HELM].detail : -1, pObj->equip[EQUIP_HELM].type != EMPTY ? pObj->equip[EQUIP_HELM].grade : 0,
			pObj->equip[EQUIP_ARMOR].type != EMPTY ? pObj->equip[EQUIP_ARMOR].detail : -1, pObj->equip[EQUIP_ARMOR].type != EMPTY ? pObj->equip[EQUIP_ARMOR].grade : 0,
			pObj->equip[EQUIP_PANTS].type != EMPTY ? pObj->equip[EQUIP_PANTS].detail : -1, pObj->equip[EQUIP_PANTS].type != EMPTY ? pObj->equip[EQUIP_PANTS].grade : 0,
			pObj->equip[EQUIP_BOOTS].type != EMPTY ? pObj->equip[EQUIP_BOOTS].detail : -1, pObj->equip[EQUIP_BOOTS].type != EMPTY ? pObj->equip[EQUIP_BOOTS].grade : 0,

			x + 64 * _2X, DY / 2 - 252 * _2X, RIGHT, false, HOUSEPLAYERZOOM, gScreenBuffer, gScreenLayer, false
		);


		break;

	case 2:
	case 3:
	case 4:

		itemType = collectionData[menuCur * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + menuItem * COLLECTIONSDATASIZE + 0];
		itemDetail = collectionData[menuCur * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + menuItem * COLLECTIONSDATASIZE + 1];
		itemGrade = collectionData[menuCur * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + menuItem * COLLECTIONSDATASIZE + 2];
		itemLv = GetItemLv(itemType, itemDetail, itemGrade);

		EquipInfoDraw(&ao[PLAYER].equip[EQUIP_WEAPON], x, y, itemType, itemDetail, itemGrade, menuDepth - 2, menuX, 1.0f, gScreenBuffer, gScreenLayer, false);
		break;
	}

}

void CollectionDetailListDraw(int x, int y, int collectionIdx, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i;
	int itemType, itemDetail, itemGrade, itemLv, itemCnt, itemSlot, itemIdx, itemIcon;
	float iconZoom = EQUIPZOOM;
	float width;
	ITEM* it;
	int setItemCnt = 0;

	DrawLabel(x + (float)(DX / 2 - 40 * _2X) * zoom, y, TEXT_COLLECTIONS + collectionIdx, zoom, cvtDest, cvtLayer, buffering);

	for (i = 0; i < COLLECTIONSITEMCNT; i++) {
		itemIdx = GetInvenIdx(collectionData[COLLECTIONSITEMCNT * COLLECTIONSDATASIZE * collectionIdx + i * COLLECTIONSDATASIZE + 0], collectionData[COLLECTIONSITEMCNT * COLLECTIONSDATASIZE * collectionIdx + i * COLLECTIONSDATASIZE + 1], collectionData[COLLECTIONSITEMCNT * COLLECTIONSDATASIZE * collectionIdx + i * COLLECTIONSDATASIZE + 2]);

		itemType = collectionData[collectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 0];
		itemDetail = collectionData[collectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 1];
		itemGrade = collectionData[collectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 2];
		itemLv = GetItemLv(itemType, itemDetail, itemGrade);

		if (itemIdx == -1)
			itemCnt = 0;
		else
			itemCnt = GetItemCount(itemType, itemDetail, itemGrade);


		if (itemIdx != -1) {
			it = GetItemPtr(ITEMPTR_INVEN + itemIdx);
			setItemCnt++;
			//SetRectPoint(x + (float)(12 * _2X + (i % COLLECTION_XCOUNT) * (REWARDCARDSIZE_X * 2 + 16 * _2X)) * iconZoom / 2, y + (float)(-(i / COLLECTION_XCOUNT) * (REWARDCARDSIZE_Y * 2 + 16 * _2X) - TSIZE * 3 - 4 * _2X) * iconZoom / 2, REWARDCARDSIZE_X * 2, REWARDCARDSIZE_Y * 2, TOUCH_FUNC_COLLECTIONS_ITEMDETAIL + i);

			if (drawHandle == MD_PLAY || drawHandle == MD_BATTLE)
				SetRectPoint(x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - TSIZE * 3 - 4 * _2X) * zoom, (float)(32 * _2X * 2) * zoom, (float)(48 * _2X * 2) * zoom, TOUCH_FUNC_COLLECTIONS_ITEMDETAIL + i);
		}

		DrawImage(32 * _2X, 48 * _2X, 32 * _2X, 0 * _2X, x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - TSIZE * 3 - 4 * _2X) * zoom, false, false, false, false, false, iconZoom * zoom, sprite[MAP_OBJ_IMG + 17], cvtDest, cvtLayer, MAP_OBJ_IMG + 17, buffering);
		ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - TSIZE * 3 - 4 * _2X - 24 * _2X) * zoom, SHADOW_IMG, iconZoom / 2 * zoom, cvtDest, cvtLayer, buffering);

		if (itemIdx == -1)
			SetColor(COLOR_BLACK);

		DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 4 * _2X) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - TSIZE * 3 - 4 * _2X - 24 * _2X + 32 * _2X - Abs((frame + i) / 2 % 32 - 16)) * zoom, 2.0f * zoom, false, false, false, true, cvtDest, cvtLayer, buffering);

		SetColor(false);

		DrawStar(ICON_STAR, x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + COLLECTIONCARDSIZE_X / 2) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - TSIZE * 2) * zoom, itemLv, ITEMMAXLEVEL, ITEMMAXLEVEL, CENTER, true, 0.8f * zoom, cvtDest, cvtLayer, buffering);

		if (itemIdx == -1)
			DrawIcon(ICON_EVENT_LOCK, x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 4 * _2X) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - TSIZE * 3 - 8 * _2X) * zoom, iconZoom * zoom, false, false, false, true, cvtDest, cvtLayer, buffering);

		DrawItemValue(itemType, itemDetail, itemGrade, itemLv, x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 32 * _2X) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - COLLECTIONCARDSIZE_Y) * zoom, CENTER, false, iconZoom / 2 * zoom, 32 * _2X * iconZoom * zoom, cvtDest, cvtLayer, buffering);

		if (itemIdx == -1) {
			sprintf(tempStr, "%s", TEXTPTR(TEXT_NOTACQUIRED));
		}
		else {
			//레벨표시
			sprintf(tempStr, TEXTPTR(TEXT_ALPHA_LV), itemLv + 1);
		}
		//DrawText(TEXT_LV, x + w / 2 - 24 * _2X, y - REWARDCARDSIZE_Y + 32 * _2X, cvtDest, cvtLayer, buffering);
		CenterTextStr(tempStr, x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 32 * _2X + 2 * _2X) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - COLLECTIONCARDSIZE_Y - TSIZE * 1 - 8 * _2X) * zoom, iconZoom / 2 * zoom, cvtDest, cvtLayer, buffering);

		DrawLabel(x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + 8 * _2X) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - 88 * _2X - TSIZE * 3 - 4 * _2X) * zoom, itemIdx == -1 ? TEXT_QUESTION : TEXT_ITEMNAME_START + GetItemName(itemType, itemDetail, itemGrade), zoom, cvtDest, cvtLayer, buffering);
	}

	//컬렉션 기능 그리기
	//세트스킬은 별도로 표시해두지 않는다.


}

void CalendarDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i, j, tempIdx, mul = 1;
	int week = 0;
	int dayOfWeek = 1;
	int dayOfMonth = robin.calendarMonthDay;

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], cvtDest, cvtLayer, UI_PAPER_POPUP_IMG, buffering);

	//밑에 일주일짜리 스케쥴 표
	for (i = 0; i < WEEK + 1; i++) {
		switch (i) {
			//1달치 보상이 그려지고
		case 0:
			DrawFrame(x + (float)(calendarPos[4 * i + 0]) * zoom, y + (float)(calendarPos[4 * i + 1] - 16 * _2X) * zoom, (float)(calendarPos[4 * i + 2]) * zoom, (float)(calendarPos[4 * i + 3]) * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);

			SetSectionClip(x + (float)(calendarPos[4 * i + 0] + 4 * _2X) * zoom, y + (float)(calendarPos[4 * i + 1] - 16 * _2X - 4 * _2X) * zoom, (float)(calendarPos[4 * i + 2] - 8 * _2X) * zoom, (float)(calendarPos[4 * i + 3] - 8 * _2X) * zoom, false);

			DrawTileDirect(CASTLE1, x - (float)(12 * _2X) * zoom, y - (float)(280 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

			SetSectionClip(x + (float)(calendarPos[4 * i + 0] + 4 * _2X) * zoom, y + (float)(calendarPos[4 * i + 1] - 16 * _2X - 4 * _2X) * zoom, (float)(calendarPos[4 * i + 2] - 8 * _2X) * zoom, (float)(calendarPos[4 * i + 3] - 8 * _2X) * zoom, false);

			DrawCmfDetail(CMF_NPC_LORA, 0, x + (float)(40 * _2X) * zoom, y - (float)(128 * _2X + 8 * _2X) * zoom, RIGHT, 4.0f * zoom, false, false, cvtDest, cvtLayer, buffering);
			DrawCmfDetail(CMF_NPC_KING, 0, x + (float)(240 * _2X) * zoom, y - (float)(128 * _2X + 8 * _2X) * zoom, LEFT, 4.0f * zoom, false, false, cvtDest, cvtLayer, buffering);

			ScreenDarken(16);

			UnSectionClip(false);

			DrawIcon(ICON_EVENT_CROWN, x + (float)(24 * _2X) * zoom, y - (float)(84 * _2X) * zoom, 1.5f * zoom, COLOR_BROWN, true, false, 1, cvtDest, cvtLayer, buffering);

			MemRectRound(x + (float)(calendarPos[4 * i + 0] + 32 * _2X) * zoom, y + (float)(calendarPos[4 * i + 1] - 64 * _2X) * zoom, (float)(CALENDARBAR_WIDTH)*zoom, (float)(CALENDARBAR_HEIGHT)*zoom, COLOR_NAVY, Max(1 * _2X, (float)2 * _2X * zoom), cvtDest, cvtLayer, buffering);
			MemRectRound(x + (float)(calendarPos[4 * i + 0] + 32 * _2X + 4 * _2X) * zoom, y + (float)(calendarPos[4 * i + 1] - 64 * _2X - 4 * _2X) * zoom, (float)(CALENDARBAR_WIDTH * dayOfMonth / MONTH) * zoom, (float)(CALENDARBAR_HEIGHT - 8 * _2X) * zoom, COLOR_ORANGE, Max(1 * _2X, (float)2 * _2X * zoom), cvtDest, cvtLayer, buffering);

			for (j = 0; j < 4; j++) {
				DrawBox(calendarInfo1Month[(robin.stage / 10) * 3 * 4 + 3 * j + 1], x + (float)(calendarPos[4 * i + 0] + 36 * _2X + CALENDARBAR_WIDTH * calendarMonthlyRewardDay[j] / MONTH - (float)(0 / 2)) * zoom, y + (float)(calendarPos[4 * i + 1] - BOXSIZE_Y) * zoom, LEFT, boxNeutralAnimation[((frame / (MOTIONDIV * 2 * 2)) % 4)], false, true, false, true, (float)(1.2f) * zoom, cvtDest, cvtLayer, buffering);
				DrawIcon(ICON_GOLD, x + (float)(calendarPos[4 * i + 0] + 32 * _2X + CALENDARBAR_WIDTH * calendarMonthlyRewardDay[j] / MONTH) * zoom, y + (float)(calendarPos[4 * i + 1] - 66 * _2X) * zoom, 1.2f * zoom, false, false, false, 1, cvtDest, cvtLayer, buffering);
				SetFontColor(COLOR_BROWN);
				memset(tempStr, 0, sizeof(tempStr));
				sprintf(tempStr, "%d", calendarMonthlyRewardDay[j]);

				CenterTextStrSolid(tempStr, x + (float)(calendarPos[4 * i + 0] + 34 * _2X + CALENDARBAR_WIDTH * calendarMonthlyRewardDay[j] / MONTH + ITEMICONSIZE / 2) * zoom, y + (float)(calendarPos[4 * i + 1] - 64 * _2X - 4 * _2X) * zoom, 1.2f * zoom, cvtDest, cvtLayer, buffering);
				SetFontColor(COLOR_WHITE);
				//DrawNum(calendarMonthlyRewardDay[j], x + (float)(calendarPos[4 * i + 0] + 36 * _2X + CALENDARBAR_WIDTH * calendarMonthlyRewardDay[j] / MONTH - ITEMICONSIZE + ITEMICONSIZE / 2 - 1 * _2X) * zoom, y + (float)(calendarPos[4 * i + 1] - 66 * _2X - 4 * _2X - 1 * _2X) * zoom, NUM_FONT_SMALL, CENTER, false, false, false, zoom, cvtDest, cvtLayer, buffering);
			}

			DrawLabel(x + (float)(calendarPos[4 * i + 0] + calendarPos[4 * i + 2] / 2 - ITEMCARDSIZE_X / 2 - 2 * _2X) * zoom, y + (float)(calendarPos[4 * i + 1] + 25 * _2X) * zoom, TEXT_CALENDAR_DAILYREWARD, zoom, cvtDest, cvtLayer, buffering);

			break;
		default:
			if (robin.calendarDayStatus[i - 1] == CALENDAR_REWARDSTATUS_REWARDGET)
				grayScale = 32;

			if (calendarInfo1Week[week * 4 * 10 + i * 4 + 0] == ITEM_CREW) {
				curStar = maxStar = crewData[calendarInfo1Week[week * 4 * 10 + i * 4 + 1] * CREWDATASIZE + CREWDATASIZE - 1] + 1;
			}
			else {
				curStar = maxStar = GetItemStar(calendarInfo1Week[week * 4 * 10 + i * 4 + 0], calendarInfo1Week[week * 4 * 10 + i * 4 + 1], calendarInfo1Week[week * 4 * 10 + i * 4 + 2]);
			}

			DrawRewardCard(calendarInfo1Week[week * 4 * 10 + i * 4 + 0], calendarInfo1Week[week * 4 * 10 + i * 4 + 1], calendarInfo1Week[week * 4 * 10 + i * 4 + 2], 1, calendarInfo1Week[week * 4 * 10 + i * 4 + 3], x + (float)(calendarPos[4 * i + 0]) * zoom, y + (float)(calendarPos[4 * i + 1]) * zoom, false, 1.5f * zoom, false, false, true, curStar, maxStar, true, cvtDest, cvtLayer, buffering);

			//DrawLabel(x + (float)(calendarPos[4 * i + 0] - 2 * _2X) * zoom, y + (float)(calendarPos[4 * i + 1] + 25 * _2X) * zoom, TEXT_CALENDAR_DAY1 + i - 1, zoom, cvtDest, cvtLayer, buffering);
			//DrawTextButton(x + (float)(calendarPos[4 * i + 0] + 0 * _2X) * zoom, y + (float)(calendarPos[4 * i + 1] + 25 * _2X) * zoom, (float)(64 * _2X) * zoom, (float)(28 * _2X) * zoom, false, robin.calendarDayStatus[i - 1] == CALENDAR_REWARDSTATUS_REWARDGET ? 32 : 0, zoom, false, TEXT_CALENDAR_DAY1 + i - 1, cvtDest, cvtLayer, buffering);


			grayScale = 0;

			SetFontColor(COLOR_BROWN);
			CenterTextSolid(TEXT_CALENDAR_DAY1 + i - 1, x + (float)(calendarPos[4 * i + 0] + (float)REWARDCARDSIZE_X * 1.5f / 2) * zoom, y + (float)(calendarPos[4 * i + 1] + 16 * _2X) * zoom, 1.2f * zoom, cvtDest, cvtLayer, buffering);
			SetFontColor(COLOR_WHITE);
			break;
		case WEEK:
			if (robin.calendarDayStatus[i - 1] == CALENDAR_REWARDSTATUS_REWARDGET)
				grayScale = 32;

			for (j = 0; j < 3; j++) {
				if (calendarInfo1Week[week * 4 * 10 + (i + j) * 4 + 0] == ITEM_CREW) {
					curStar = maxStar = crewData[calendarInfo1Week[week * 4 * 10 + (i + j) * 4 + 1] * CREWDATASIZE + CREWDATASIZE - 1] + 1;
				}
				else {
					curStar = maxStar = GetItemStar(calendarInfo1Week[week * 4 * 10 + (i + j) * 4 + 0], calendarInfo1Week[week * 4 * 10 + (i + j) * 4 + 1], calendarInfo1Week[week * 4 * 10 + (i + j) * 4 + 2]);
				}

				DrawRewardCard(calendarInfo1Week[week * 4 * 10 + (i + j) * 4 + 0], calendarInfo1Week[week * 4 * 10 + (i + j) * 4 + 1], calendarInfo1Week[week * 4 * 10 + (i + j) * 4 + 2], 1, calendarInfo1Week[week * 4 * 10 + i * 4 + 3], x + (float)(calendarPos[4 * i + 0] + 24 * _2X + j * (76 * _2X)) * zoom, y + (float)(calendarPos[4 * i + 1]) * zoom, false, 1.5f * zoom, false, false, true, curStar, maxStar, true, cvtDest, cvtLayer, buffering);
			}

			//DrawLabel(x + (float)(calendarPos[4 * i + 0] + calendarPos[4 * i + 2] / 2 - ITEMCARDSIZE_X / 2 - 2 * _2X) * zoom, y + (float)(calendarPos[4 * i + 1] + 25 * _2X) * zoom, TEXT_CALENDAR_DAY1 + i - 1, zoom, cvtDest, cvtLayer, buffering);
			//DrawTextButton(x + (float)(POPUPWINDOWSIZE_X - 64 * _2X) / 2 * zoom, y + (float)(calendarPos[4 * i + 1] + 25 * _2X) * zoom, (float)(64 * _2X) * zoom, (float)(28 * _2X) * zoom, false, robin.calendarDayStatus[i - 1] == CALENDAR_REWARDSTATUS_REWARDGET ? 32 : 0, zoom, false, TEXT_CALENDAR_DAY1 + i - 1, cvtDest, cvtLayer, buffering);

			grayScale = 0;

			SetFontColor(COLOR_BROWN);
			CenterTextSolid(TEXT_CALENDAR_DAY1 + i - 1, x + (float)(POPUPWINDOWSIZE_X / 2) * zoom, y + (float)(calendarPos[4 * i + 1] + 16 * _2X) * zoom, 1.2f * zoom, cvtDest, cvtLayer, buffering);
			SetFontColor(COLOR_WHITE);
			break;
		}

	}

	//현재 보상까지 남은 시간
	//DrawTime(x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y + (float)( - 440 * _2X) * zoom, Max(0, 86400 - (MC_knlCurrentTimeStamp() - robin.calendarTimeStamp)), TIME_HOUR_MINUTE, CENTER, zoom, cvtDest, cvtLayer, buffering);



	//상단에 한달짜리 스케쥴 표

	//위에 타이틀 태그를 붙여주고,
	//
}

void OptionDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	//int GAP = -4 * _2X;
	int GAP = 14 * _2X;

	//DrawFrame(x, y, (float)(POPUPWINDOWSIZE_X)* zoom, (float)(GAMEMENUWIN2_Y)* zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], cvtDest, cvtLayer, UI_PAPER_POPUP_IMG, false);

	//메인화면
//음악
	CenterText(TEXT_BGM, x + (float)(50 * _2X + 32 * _2X + GAP) * zoom, y - (float)(32 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
	DrawTouchLargeButton(x + (float)(50 * _2X + 32 * _2X + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 16 * _2X) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[option.bgm ? TEXT_ON : TEXT_OFF], TOUCH_FUNC_OPTION_BGM, option.bgm ? FRAME_GREEN : FRAME_RED, zoom, cvtDest, cvtLayer, buffering);

	//효과음
	CenterText(TEXT_SE, x + (float)(DX / 2 + 104 * _2X / 2 + GAP) * zoom, y - (float)(32 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
	DrawTouchLargeButton(x + (float)(DX / 2 + 104 * _2X / 2 + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 16 * _2X) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[option.se ? TEXT_ON : TEXT_OFF], TOUCH_FUNC_OPTION_SE, option.se ? FRAME_GREEN : FRAME_RED, zoom, cvtDest, cvtLayer, buffering);

	//진동
	CenterText(TEXT_VIBRATION, x + (float)(50 * _2X + 32 * _2X + GAP) * zoom, y + (float)(-32 * _2X - 64 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
	DrawTouchLargeButton(x + (float)(50 * _2X + 32 * _2X + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 16 * _2X - 64 * _2X) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[option.vibration ? TEXT_ON : TEXT_OFF], TOUCH_FUNC_OPTION_VIBRATION, option.vibration ? FRAME_GREEN : FRAME_RED, zoom, cvtDest, cvtLayer, buffering);

	//언어
	CenterText(TEXT_LANGUAGE, x + (float)(DX / 2 + 104 * _2X / 2 + GAP) * zoom, y + (float)(-32 * _2X - 64 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
	DrawTouchLargeButton(x + (float)(DX / 2 + 104 * _2X / 2 + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 16 * _2X - 64 * _2X) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[TEXT_KOREAN + option.language], TOUCH_FUNC_OPTION_LANGUAGE, FRAME_BLUE, zoom, cvtDest, cvtLayer, buffering);

	//페이스북
	CenterText(TEXT_FACEBOOK, x + (float)(50 * _2X + 32 * _2X + GAP) * zoom, y + (float)(-32 * _2X - 64 * _2X * 2) * zoom, zoom, cvtDest, cvtLayer, buffering);
	DrawTouchLargeButton(x + (float)(50 * _2X + 32 * _2X + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 16 * _2X - 64 * _2X * 2) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[option.facebook ? TEXT_CONNECTED : TEXT_DISCONNECTED], TOUCH_FUNC_OPTION_FACEBOOK, option.facebook ? FRAME_GREEN : FRAME_RED, zoom, cvtDest, cvtLayer, buffering);

	//구글플레이
	CenterText(TEXT_GOOGLEPLAY, x + (float)(DX / 2 + 104 * _2X / 2 + GAP) * zoom, y + (float)(-32 * _2X - 64 * _2X * 2) * zoom, zoom, cvtDest, cvtLayer, buffering);
	DrawTouchLargeButton(x + (float)(DX / 2 + 104 * _2X / 2 + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 16 * _2X - 64 * _2X * 2) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[option.google ? TEXT_CONNECTED : TEXT_DISCONNECTED], TOUCH_FUNC_OPTION_GOOGLE, option.google ? FRAME_GREEN : FRAME_RED, zoom, cvtDest, cvtLayer, buffering);

	//게임센터
	CenterText(TEXT_GAMECENTER, x + (float)(50 * _2X + 32 * _2X + GAP) * zoom, y + (float)(-32 * _2X - 64 * _2X * 3) * zoom, zoom, cvtDest, cvtLayer, buffering);
	DrawTouchLargeButton(x + (float)(50 * _2X + 32 * _2X + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 16 * _2X - 64 * _2X * 3) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[option.gameCenter ? TEXT_CONNECTED : TEXT_DISCONNECTED], TOUCH_FUNC_OPTION_GAMECENTER, option.gameCenter ? FRAME_GREEN : FRAME_RED, zoom, cvtDest, cvtLayer, buffering);

	//게스트
	CenterText(TEXT_GUEST, x + (float)(DX / 2 + 104 * _2X / 2 + GAP) * zoom, y + (float)(-32 * _2X - 64 * _2X * 3) * zoom, zoom, cvtDest, cvtLayer, buffering);
	DrawTouchLargeButton(x + (float)(DX / 2 + 104 * _2X / 2 + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 16 * _2X - 64 * _2X * 3) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[TEXT_CONNECTED], TOUCH_FUNC_OPTION_GUEST, FRAME_GREY, zoom, cvtDest, cvtLayer, buffering);

	//도움말 지원
	DrawTouchLargeButton(x + (float)(50 * _2X + 32 * _2X + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 64 * _2X * 4 - 12 * _2X) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[TEXT_HELP], TOUCH_FUNC_OPTION_HELP, FRAME_BLUE, zoom, cvtDest, cvtLayer, buffering);

	//개인정보 보호정책
	DrawTouchLargeButton(x + (float)(DX / 2 + 104 * _2X / 2 + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 64 * _2X * 4 - 12 * _2X) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[TEXT_PRIVACY], TOUCH_FUNC_OPTION_POLICY, FRAME_BLUE, zoom, cvtDest, cvtLayer, buffering);

	//이용약관
	DrawTouchLargeButton(x + (float)(50 * _2X + 32 * _2X + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 64 * _2X * 4 - 12 * _2X - 40 * _2X) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[TEXT_TERMOFSERVICE], TOUCH_FUNC_OPTION_POLICY, FRAME_GREY, zoom, cvtDest, cvtLayer, buffering);

	//제작진
	DrawTouchLargeButton(x + (float)(DX / 2 + 104 * _2X / 2 + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 64 * _2X * 4 - 12 * _2X - 40 * _2X) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[TEXT_STAFF], TOUCH_FUNC_OPTION_COMMUNITY, FRAME_GREY, zoom, cvtDest, cvtLayer, buffering);
}


void JokboDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{

}


void LevelUpMenuDraw(int lv, int status, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i;

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], cvtDest, cvtLayer, UI_PAPER_POPUP_IMG, false);


	ExpBarWideDraw(robin.lv, robin.exps, x + (float)(POPUPWINDOWSIZE_X - CROWNBARWIDTH_WIDE) / 2 * zoom, y - (float)0 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);

	for (i = 0; i < TOTAL_LVUPREWARD; i++) {
		DrawLevelUpCard(i, GetLevelUpRewardLv(i, robin.lv), GetLevelUpRewardLv(i, robin.lv) == false ? true : false, x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X) * zoom, y - (float)((i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y - 12 * _2X) + TSIZE * 2 + 8 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

		//DrawImage(32 * _2X, 48 * _2X, 32 * _2X, 0 * _2X, x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X) * zoom, y - (float)((i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) + TSIZE * 2) * zoom, false, false, false, false, false, 2.0f * zoom, sprite[MAP_OBJ_IMG + 17], cvtDest, cvtLayer, MAP_OBJ_IMG + 17, buffering);
		//ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X) * zoom, y - (float)((i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) + TSIZE * 2 + 16 * _2X) * zoom, SHADOW_IMG, 2.0f * zoom, cvtDest, cvtLayer, buffering);
		//DrawFrame(x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + 16 * _2X) * zoom, y - (float)((i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) + 32 * _2X) * zoom, (float)32 * _2X * 2 * zoom, (float)48 * _2X * 2 * zoom, FRAME_MENUWIN, cvtDest, cvtLayer, buffering);
		/*
		if (setItemCnt == 0)
			SetColor(COLOR_BLACK);

		DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 4 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X + 32 * _2X + (setItemCnt == COLLECTIONSITEMCNT ? -Abs((frame + i) / 2 % 32 - 16) : 0), 2.0f, false, false, false, gScreenBuffer, gScreenLayer, false);

		SetColor(false);

		if (setItemCnt > 0)
			for (j = 0; j < COLLECTIONSITEMCNT; j++) {
				itemType = collectionData[COLLECTIONSITEMCNT * COLLECTIONSDATASIZE * i + j * COLLECTIONSDATASIZE + 0];
				itemDetail = collectionData[COLLECTIONSITEMCNT * COLLECTIONSDATASIZE * i + j * COLLECTIONSDATASIZE + 1];
				itemGrade = collectionData[COLLECTIONSITEMCNT * COLLECTIONSDATASIZE * i + j * COLLECTIONSDATASIZE + 2];
				itemLv = GetItemLv(itemType, itemDetail, itemGrade);

				itemSlot = GetEquipSlot(itemType, itemDetail, itemGrade);

				if (GetInvenIdx(itemType, itemDetail, itemGrade) == -1) {
					SetColor(COLOR_BLACK);
					DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + (j % 3) * (ITEMICONSIZE + 4 * _2X) + 22 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 4 * _2X - 48 * _2X - (j / 3) * (ITEMICONSIZE + 4 * _2X), 1.0f, false, false, false, gScreenBuffer, gScreenLayer, false);
				}
				else {
					if (itemSlot == -1)
						grayScale = 32;
					DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + (j % 3) * (ITEMICONSIZE + 4 * _2X) + 22 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 4 * _2X - 48 * _2X - (j / 3) * (ITEMICONSIZE + 4 * _2X), 1.0f, true, false, false, gScreenBuffer, gScreenLayer, false);

				}

				grayScale = 0;
				SetColor(false);
			}


		//몇분의 몇을 모았는지를 보여주는
		if (setItemCnt > 0) {
			DrawNum(setItemCnt, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 22 * _2X - 14 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X - 32 * _2X + 18 * _2X, NUM_FONT_NORMAL, LEFT, false, false, false, 1.0f, gScreenBuffer, gScreenLayer, false);
			DrawText(TEXT_SLASH, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 22 * _2X - 2 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X - 32 * _2X - 2 * _2X + 18 * _2X, 1.0f, gScreenBuffer, gScreenLayer, false);
			DrawNum(COLLECTIONSITEMCNT, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 22 * _2X + 6 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X - 32 * _2X + 18 * _2X, NUM_FONT_NORMAL, LEFT, false, false, false, 1.0f, gScreenBuffer, gScreenLayer, false);
		}
		//6개가 다 장착되어 있어서 스킬이 활성화 되어 있으면
		if (GetFullEquipedCollectionIdx() == i)
			DrawNeutral(OBJ_STAMPEFFECT0 + (frame / 3 % 8), x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 4 * _2X + 16 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X, 0, 1.0f, gScreenBuffer, gScreenLayer, false);
		//만약 6개가 다 모여만 있으면
		else if (setItemCnt == COLLECTIONSITEMCNT) {
			//아무것도 하지 않는다.
		}
		else if (setItemCnt > 0) {
			//아무것도 하지 않는다.
		}
		//아무것도 없으면
		else
			DrawIcon(ICON_EVENT_LOCK, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 4 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X + 32 * _2X - 12 * _2X - 52 * _2X, 2.0f, false, false, false, gScreenBuffer, gScreenLayer, false);
		*/
		//DrawLabel(x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + 8 * _2X) * zoom, y - (float)((i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) + 88 * _2X + TSIZE) * zoom, TEXT_LVUPREWARD_AUTOROLL + i, zoom, cvtDest, cvtLayer, buffering);

		SetRectPoint(x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X) * zoom, y - (float)((i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y - 12 * _2X) + TSIZE * 2 + 8 * _2X) * zoom, (float)(COLLECTIONCARDSIZE_X - 36 * _2X) * zoom, (float)(COLLECTIONCARDSIZE_Y - 16 * _2X) * zoom, TOUCH_FUNC_COLLECTIONS_DETAIL + i);

	}
	//
	//일단 메뉴 정리부터 하자.
	//1. 상점->
	//2. 퀘스트가 있고
	//3. 

	//레벨업 이펙트를 정의하자.
	//케이스 정의
	//1. 최대 하트와 시간당 회복량 증가
	//2. 메뉴 오픈
	//   - 
	//   - 
	//3. 
}

void DeptDiscountDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i, j;
	float rouletteZoom = 0.7f;
	int gapX = 12 * _2X;
	int gapX2 = 4 * _2X;
	int gapY = 24 * _2X;
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	int itemType = it->type;
	int itemDetail = it->detail;
	int itemGrade = it->grade;
	int itemLv = it->cooldown;
	int rewardIcon;
	int collectionIdx = GetCollectionIdx(itemType, itemDetail, itemGrade);
	long long str;
	float width;
	float itemValueZoom = 1.0f;
	float w = (float)ROULETTECARDSIZE_X * zoom;
	float h = (float)ROULETTECARDSIZE_Y * zoom;
	float bigNumWidth = (float)ITEMICONSIZE * itemValueZoom * zoom * 1.7f;
	int type;

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], cvtDest, cvtLayer, UI_PAPER_POPUP_IMG, false);

}


void DoubleGoldDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i, j;
	float rouletteZoom = 0.7f;
	int gapX = 12 * _2X;
	int gapX2 = 4 * _2X;
	int gapY = 24 * _2X;
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	int itemType = it->type;
	int itemDetail = it->detail;
	int itemGrade = it->grade;
	int itemLv = it->cooldown;
	int rewardIcon;
	int collectionIdx = GetCollectionIdx(itemType, itemDetail, itemGrade);
	long long str;
	float width;
	float itemValueZoom = 1.0f;
	float w = (float)ROULETTECARDSIZE_X * zoom;
	float h = (float)ROULETTECARDSIZE_Y * zoom;
	float bigNumWidth = (float)ITEMICONSIZE * itemValueZoom * zoom * 1.7f;
	int type;

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], cvtDest, cvtLayer, UI_PAPER_POPUP_IMG, false);

}




void LimitScrollY(void)
{
	if (scY[curMenu] < 0) {
		scY[curMenu] = 0;
	}
	else if (scY[curMenu] > scT[curMenu]) {
		scY[curMenu] = scT[curMenu];
	}
}

int GetBoxCurrency(int detail, int grade)
{
	switch (detail) {
	case BOX_EQUIP_WOOD:
	case BOX_EQUIP_SILVER:
	case BOX_EQUIP_GOLD:
	case BOX_EQUIP_MAGIC:
	case BOX_CREW_SEBASTIAN:
	case BOX_CREW_PRINCESS:
		return CURRENCY_GOLD;
	case BOX_EQUIP_HERO:
	case BOX_EQUIP_LEGEND:
	case BOX_CREW_KING:
	case BOX_CREW_DEVIL:
		return CURRENCY_STAR;
	case BOX_ATTR_FIRE:
	case BOX_ATTR_FROST:
	case BOX_ATTR_EARTH:
	case BOX_ATTR_THUNDER:
	case BOX_ATTR_LIGHT:
	case BOX_ATTR_DARK:
		return CURRENCY_GOLD;
	}
}

int GetBoxGold(int boxType)
{
	//박스의 코인을 구하는 방법
	return stageGold[robin.stage * TOTALROOM + robin.room] * betHeart[boxType];
}

int GetBoxQuestItem(int boxType)
{
	return betHeart[boxType];
}

int GetBoxHeartItem(int boxType)
{
	return betHeart[boxType] * HEARTPER;
}

int GetBoxPrice(int detail, int grade)
{
	switch (detail) {
	case BOX_EQUIP_WOOD:
		return 10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000;
	case BOX_EQUIP_SILVER:	//카드 한장	//BOX_CHEST1
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000);
	case BOX_EQUIP_GOLD:	//카드 두장	//BOX_CHEST2
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 10;
	case BOX_EQUIP_MAGIC:	//카드 세장	//BOX_CHEST3
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 100;
	case BOX_EQUIP_HERO:
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 1000;
	case BOX_EQUIP_LEGEND:
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 10000;
	case BOX_CREW_SEBASTIAN:
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 100;
	case BOX_CREW_PRINCESS:
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 100;
	case BOX_CREW_KING:
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 100;
	case BOX_CREW_DEVIL:
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 100;
	case BOX_ATTR_FIRE:
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 100;
	case BOX_ATTR_FROST:
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 100;
	case BOX_ATTR_EARTH:
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 100;
	case BOX_ATTR_THUNDER:
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 100;
	case BOX_ATTR_LIGHT:
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 100;
	case BOX_ATTR_DARK:
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 100;
	}
}

int GetScrollDy(int menuIdx)
{
	int i, j;
	int scrollDy = 0;
	int gapY = 0;

	switch (menuIdx) {
	case MENU_PLAY:
		scrollDy = (float)(DIORAMASIZE_Y * dioramaZoom + 32 * _2X) * (TOTALCASTLE + 1);
		break;
		//case MENU_MAP:
		//	scrollDy = TOTAL_STAGE * STAGELIST_Y + GNBHEIGHT + BOTTOMMENUHEIGHT;
		//	break;
	case MENU_SHOP:
	case MENU_STARSHOP:
		scrollDy = 680 * _2X + 12 * _2X;
		break;
	case MENU_GIFTS:
		scrollDy = 1050 * _2X + GNBHEIGHT + BOTTOMMENUHEIGHT;
		break;
	case MENU_CREW:
		scrollDy = CREWSET_YGAP * (TOTAL_CREW / MAXCREW);
		break;
	case MENU_COLLECTIONS:
		scrollDy = (float)88 * _2X * ((itemTypeCnt[menuCur < EQUIP_NECK ? itemSlotEquip[menuCur] + curHero : itemSlotEquip[menuCur]] + 1) / MAXCREW) + GNBHEIGHT + BOTTOMMENUHEIGHT;
		/*
		switch (menuCur) {
			case COLLECTIONMENU_EQUIP:
				scrollDy = POPUPWINDOWSIZE_Y;
				break;
			case COLLECTIONMENU_SKILL:
				scrollDy = (120 * _2X) + COLLECTION_YGAP * ((TOTAL_CREW + 3) / 4);
				break;
		}
		*/
		break;
	case MENU_LEADERBOARD:
	case MENU_FRIENDS:
	case MENU_INVITEFREINDS:
	case MENU_CALENDAR:
	case MENU_SETTING:
		scrollDy = DY;
		break;
	default:
		scrollDy = DY;
		break;
	}

	return scrollDy;
}


void SetAlert(int type)
{
	before_DrawHandle = drawHandle;
	before_KeyHandle = keyHandle;
	drawHandle = MD_ALERT;
	keyHandle = MK_ALERT;
	alert = type;
	infoFrame = 0;
	winAniFrame = 0;
	yesNo = 0;
	popUpFrame = 7;
}

void OutOfAlert(void)
{
	drawHandle = before_DrawHandle;
	keyHandle = before_KeyHandle;
}

void DrawHandleExec(int drawIdx)
{
	int x = 0;
	int y = DY;
	int dx = DX;
	int dy = DY;

	drawHandle = before_DrawHandle;
	before_DrawHandle = drawIdx;

	switch (drawHandle) {
	case MD_LOGO:
		LogoDraw();
		break;
	case MD_TITLE:
		TitleDraw();
		break;
	case MD_PLAY:
	case MD_BATTLE:
	case MD_RAID:
	case MD_BOSSRAID:
		Play();
		break;
	}

	before_DrawHandle = drawHandle;
	drawHandle = drawIdx;
}

void AlertDraw(void)
{
	const unsigned short* ucPtr = &alertData[alert * ALERTDATASIZE];
	std::string pStr;
	int pText = alertText[alert];

	DrawHandleExec(MD_ALERT);

	SetAlpha(16);
	MemRect(0, DY, DX, DY, COLOR_NAVY, gScreenBuffer, gScreenLayer, false);
	SetAlpha(32);

	ResetRectPoint();
	//4곳을 바깥으로 나가는것으로 하자
	SetRectPoint(0, DY, DX, (DY - *(ucPtr + 1)) / 2, TOUCH_ALERT_NO);//위쪽
	SetRectPoint(0, DY / 2 + *(ucPtr + 1) / 2, (DX - *ucPtr) / 2, *(ucPtr + 1), TOUCH_ALERT_NO);//왼쪽
	SetRectPoint(DX / 2 + *ucPtr / 2, DY / 2 + *(ucPtr + 1) / 2, (DX - *ucPtr) / 2, *(ucPtr + 1), TOUCH_ALERT_NO);//오른쪽
	SetRectPoint(0, DY / 2 - *(ucPtr + 1) / 2, DX, (DY - *(ucPtr + 1)) / 2, TOUCH_ALERT_NO);//아래쪽

	if (winAniFrame < 7)
		DrawFrame(DX / 2, DY / 2, *ucPtr, *(ucPtr + 1), FRAME_ANIINFO, gScreenBuffer, gScreenLayer, false);
	else {
		DrawCmfPopUp(*(ucPtr + 4), pText, DX / 2 - *ucPtr / 2, DY / 2 + *(ucPtr + 1) / 2, *ucPtr, *(ucPtr + 1), DX - 120 * _2X, 5, 6, 1.0f, gScreenBuffer, gScreenLayer, false);
		switch (alert) {
		default:
			if (winAniFrame > 7) {
				switch (pText) {
				case -5:
					break;
				case -4:
					pStr = "착용중인 아이템으로 퀘스트를 완료할 수 없습니다.";
					break;
				case -3:
					pStr = skillStr;
					break;
				case -2:
					pStr = infoStr;
					break;
				case -1:
					pStr = tempStr;
					break;
				default:
					break;
				case 0:
					switch (alert) {
					case ALERT_NOTICE:
						break;
					}
				}


				if (pText) {

					if (*(ucPtr + 3) == 0)
						DrawTouchButton(DX / 2 - (StringWidth(textId[TEXT_CONFIRM], 1.0f) + 4) / 2, (DY - *(ucPtr + 1)) / 2 + 28 * _2X, textId[TEXT_CONFIRM], TOUCH_FUNC_CLOSEALERT, gScreenBuffer, gScreenLayer, false);
					else
						YesNoDraw(DX / 2, (DY - *(ucPtr + 1)) / 2 + 40 * _2X, gScreenBuffer, gScreenLayer, false);

					if (touch)
						touchModeOld = null;
				}

			}
			break;
		}
	}

	winAniFrame++;
}

void GachaDraw(void)
{
	int i, j, speed, count = -1;
	int row = 2;//가로로 몇개인지
	int col = 2;//세로로 몇줄인지
	float zoom = 1.5f;
	int gap = 8 * _2X;
	bool crewMenuDraw = false;
	bool equipMenuDraw = false;
	float menuZoom = 1.0f;
	float width;
	int remainBoxCnt;

	switch (boxCardItemCnt[gachaIndex]) {
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
	case 9:
		row = 3;
		col = 3;
		zoom = 1.5f;
		gap = 16 * _2X;
		break;
	case 10:
	case 11:
	case 12:
		row = 4;
		col = 3;
		zoom = 1.5f;
		gap = 16 * _2X;
		break;
	case 13:
	case 14:
	case 15:
	case 16:
		row = 4;
		col = 3;
		zoom = 1.5f;
		gap = 16 * _2X;
		break;
	}

	MemRect(0, DY, DX, DY, mapColor[MAPTYPE_SPACE], gScreenBuffer, gScreenLayer, false);

	if (gachaFrame < GACHADELAY_OPENPLACE && gachaDepth == 0) {
		zoom = (float)(GACHADELAY_OPENPLACE - gachaFrame) * 0.2f * 2 / MOTIONDIV + 0.8f;
		for (i = 0; i < DX / 128 * _2X + 1; i++) {
			DrawImage(128 * _2X, 208 * _2X, 0 * _2X, 0 * _2X, xOffset + i * (float)128 * _2X * zoom, STATUSWIN_Y2 + (float)(208 * _2X) * zoom / 2, false, false, false, false, false, zoom, sprite[MAP_BG_IMG + MAPTYPE_SPACE], gScreenBuffer, gScreenLayer, MAP_BG_IMG + MAPTYPE_SPACE, false);
		}

		DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, xOffset + DX / 2 - (float)(DIORAMASIZE_X / 2) * zoom, STATUSWIN_Y2 + (float)(DIORAMASIZE_Y / 2) * zoom, false, false, false, false, false, zoom, sprite[MAP_DIORAMA_IMG + HOUSE_DEVILCASTLE], gScreenBuffer, gScreenLayer, MAP_DIORAMA_IMG + HOUSE_DEVILCASTLE, false);

	}
	else {
		for (i = 0; i < DX / 128 * _2X + 1; i++)
			DrawImage(128 * _2X, 208 * _2X, 0 * _2X, 0 * _2X, xOffset + i * 128 * _2X, STATUSWIN_Y2 + 208 * _2X / 2, false, false, false, false, false, 1.0f, sprite[MAP_BG_IMG + MAPTYPE_SPACE], gScreenBuffer, gScreenLayer, MAP_BG_IMG + MAPTYPE_SPACE, false);

		DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, xOffset + DX / 2 - DIORAMASIZE_X / 2, STATUSWIN_Y2 + DIORAMASIZE_Y / 2, false, false, false, false, false, 1.0f, sprite[MAP_DIORAMA_IMG + HOUSE_DEVILCASTLE], gScreenBuffer, gScreenLayer, MAP_DIORAMA_IMG + HOUSE_DEVILCASTLE, false);
	}
	//가차화면
	switch (gachaDepth) {
		//상자에서 아이템이 나오는 부분
	case 0:

		//박스가 떨어지는 화면
		if (gachaFrame < GACHADELAY_OPENPLACE) {
			if (gachaFrame == GACHADELAY_OPENPLACE - 1)
				boxMark[0].frame2 = 1;
		}
		else if (gachaFrame < GACHADELAY_BOXDROP) {
			//if (boxMark[gachaIndex].y > STATUSWIN_Y)
			//	boxMark[gachaIndex].y -= TSIZE;

			//if (boxMark[gachaIndex].y < STATUSWIN_Y)
			//	boxMark[gachaIndex].y = STATUSWIN_Y;
		}
		//박스가 열리는 화면
		else if (gachaFrame < GACHADELAY_BOXOPEN) {
			if (gachaFrame == GACHADELAY_BOXDROP) {
				boxMark[0].jokboIcon = true;
				PlayMusic(M_OPENDOOR);
			}
		}
		else if (gachaFrame < GACHADELAY_ITEMDROP) {
			//스테이터스 창의 카드들
			startX = xOffset + DX / 2;
			startY = STATUSWIN_Y2;

			if (gachaFrame % ROULETTEDIV == 0 && gachaCardIdx < boxCardItemCnt[gachaIndex]) {
				//센터에 왔을 때 카드들
				targetX = xOffset + DX / 2 - (float)(REWARDCARDSIZE_X * zoom * row + gap * (row - 1)) / 2 + (float)(REWARDCARDSIZE_X * zoom + gap) * (gachaCardIdx % row) + (float)(REWARDCARDSIZE_X * zoom) / 2;
				targetY = DY / 2 + (float)REWARDCARDSIZE_Y * zoom * col - (float)(REWARDCARDSIZE_Y * zoom + gap) * (gachaCardIdx / row) - (float)(REWARDCARDSIZE_Y * zoom) / 2;

				switch (boxCardItem[gachaIndex][gachaCardIdx].type) {
				default:
					SetBoxCardMark(startX, startY, targetX, targetY, false, false, 32 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, false, false, FPS, FPS, GetItemIcon(boxCardItem[gachaIndex][gachaCardIdx].type, boxCardItem[gachaIndex][gachaCardIdx].detail, boxCardItem[gachaIndex][gachaCardIdx].grade), 0,
						boxCardItem[gachaIndex][gachaCardIdx].count, boxCardItem[gachaIndex][gachaCardIdx].type, boxCardItem[gachaIndex][gachaCardIdx].detail, boxCardItem[gachaIndex][gachaCardIdx].grade, boxCardItem[gachaIndex][gachaCardIdx].cooldown, false, true, true, PLAYER, false, 0.2f / MOTIONDIV, zoom, 0.8f / MOTIONDIV, false, false, false, false, boxCardItem[gachaIndex][gachaCardIdx].seen == false ? true : false);
					break;
				}

				gachaCardIdx++;
			}
			//여기서 뉴카드가 있는지 확인하고 GotoNewCard로 넘겨준다.
			//if (gachaFrame == GACHADELAY_ITEMDROP - 1) {
			//	newItemCnt = 0;
			//	curNewItemIdx = 0;
			//	for (i = 0; i < gachaCardIdx; i++) {
			//		if (GetInvenIdx(boxCardItem[gachaIndex][i].type, boxCardItem[gachaIndex][i].detail, boxCardItem[gachaIndex][i].grade) == -1) {
			//			newItemType[newItemCnt] = boxCardItem[gachaIndex][i].type;
			//			newItemDetail[newItemCnt] = boxCardItem[gachaIndex][i].detail;
			//			newItemGrade[newItemCnt] = boxCardItem[gachaIndex][i].grade;
			//			newItemCnt++;
			//		}
			//	}

			//	if (newItemCnt > 0)
			//		GotoNewCard();
			//}
		}
		else {

			SetAlpha(32 - Abs(frame / MOTIONDIV % 32 - 16));
			DrawGoldAlpha(xOffset + DX / 2, DY / 2 + TABBUTTONGAP, ALPHA_TABTOCOLLECT, FONT_GOLD_LARGE, 1, CENTER, false, false, gScreenBuffer, gScreenLayer, false);
			SetAlpha(32);
			CenterText(TEXT_AUTOEQUIP, xOffset + DX / 2, DY / 2 + TABBUTTONGAP + 16 * _2X, 1.0f, gScreenBuffer, gScreenLayer, false);

			SetRectPoint(0, DY, DX, DY, TOUCH_FUNC_GETGACHACARD);
		}
		break;
	case 1:
		//
		if (gachaFrame < GACHADELAY_GETITEM) {
			if (gachaFrame == FPS / 2) {
				//여기서 장비인지 크류인지 확인하고 해당쪽으로 보내준다.
				for (i = 0; i < boxCardItemCnt[gachaIndex]; i++) {
					if (boxCardItem[gachaIndex][i].type == ITEM_CREW) {
						boxCardMark[i].targetX2 = xOffset + DX / 2 + 108 * _2X + 20 * _2X;
					}
					else {
						boxCardMark[i].targetX2 = xOffset + DX / 2 - 150 * _2X + 20 * _2X;
					}
					boxCardMark[i].targetY2 = STATUSWIN_Y2 + JOYSTICKGAP + 83 * _2X;
					boxCardMark[i].zoom2 = boxCardMark[i].zoom;
					boxCardMark[i].zoomEnd2 = 1.0f;
					boxCardMark[i].zoomIncrement2 = -0.2f / MOTIONDIV;
					boxCardMark[i].speed2 = 32 * _2X / MOTIONDIV;
					boxCardMark[i].speedIncrement2 = 4 * _2X / MOTIONDIV;
					boxCardMark[i].frame2 = 1;

					PlayMusic(M_CARDSPLIT);
				}

				//하단의 내용을 터치시로 변경해 준다.
				////가챠에서 나온 카드들을 인벤토리에 넣어준다.
				//for (i = 0; i < boxCardItemCnt[gachaIndex]; i++) {
				//	GetItem(boxCardItem[gachaIndex][i].type, boxCardItem[gachaIndex][i].lv, boxCardItem[gachaIndex][i].detail, boxCardItem[gachaIndex][i].grade, 1, false);
				//	SetStrongestEquip(boxCardItem[gachaIndex][i].type, boxCardItem[gachaIndex][i].detail, boxCardItem[gachaIndex][i].grade);
				//}
			}

			//여기서 장비인지 크류인지 확인하고 해당쪽으로 보내준다.
			for (i = 0; i < boxCardItemCnt[gachaIndex]; i++) {
				if (gachaFrame < 6 * MOTIONDIV)
					menuZoom = Min(1.5f, (float)(gachaFrame) * 2 / MOTIONDIV / 10);
				else if (gachaFrame < 6 * MOTIONDIV + 6 * MOTIONDIV)
					menuZoom = 1.5f;
				else if (gachaFrame < 6 * MOTIONDIV + 6 * MOTIONDIV + 2 * MOTIONDIV)
					menuZoom = Max(1.0f, 1.5f - (float)(gachaFrame - 6 * MOTIONDIV - 6 * MOTIONDIV) / 10);
				else
					menuZoom = 1.0f;

				if (boxCardItem[gachaIndex][i].type == ITEM_CREW && crewMenuDraw == false) {
					crewMenuDraw = true;

					startX = xOffset + DX / 2 + 108 * _2X + 40 * _2X / 2 - (float)(40 * _2X) * menuZoom / 2;
					startY = STATUSWIN_Y2 + JOYSTICKGAP + 83 * _2X + (float)(40 * _2X) * menuZoom / 2;

					DrawImage(40 * _2X, 40 * _2X, 80 * _2X, 0 * _2X, startX, startY, false, false, false, false, 32, menuZoom, sprite[MENUICON_IMG], gScreenBuffer, gScreenLayer, MENUICON_IMG, false);

				}
				else if (equipMenuDraw == false) {
					equipMenuDraw = true;

					startX = xOffset + DX / 2 - 150 * _2X + 40 * _2X / 2 - (float)(40 * _2X) * menuZoom / 2;
					startY = STATUSWIN_Y2 + JOYSTICKGAP + 83 * _2X + (float)(40 * _2X) * menuZoom / 2;

					DrawImage(40 * _2X, 40 * _2X, 0 * _2X, 0 * _2X, startX, startY, false, false, false, false, false, menuZoom, sprite[MENUICON_IMG], gScreenBuffer, gScreenLayer, MENUICON_IMG, false);
				}

				if (gachaFrame == 1 * FPS) {
					boxCardMark[i].zoomEnd2 = 0.2f / MOTIONDIV;
					boxCardMark[i].zoomIncrement2 = -0.2f / MOTIONDIV;
				}

				if (gachaFrame == 1 * FPS + 5 * MOTIONDIV) {
					memset(&boxCardMark[i], 0, sizeof(boxCardMark[i]));
					PlayMusic(M_ITEM);
				}
			}
		}
		else {
			SetAlpha(32 - Abs(frame / MOTIONDIV % 32 - 16));
			DrawGoldAlpha(xOffset + DX / 2, DY / 2 + TABBUTTONGAP, ALPHA_TABTOCOLLECT, FONT_GOLD_LARGE, 1, CENTER, false, false, gScreenBuffer, gScreenLayer, false);
			SetAlpha(32);
			CenterText(TEXT_AUTOEQUIP, xOffset + DX / 2, DY / 2 + TABBUTTONGAP - 32 * _2X, 1.0f, gScreenBuffer, gScreenLayer, false);

			//박스가 아직 남아있으면 다시 가챠드로우로 보내준다.
			if (boxCnt - (gachaIndex + 1) > 0) {
				gachaIndex++;
				memset(&boxMark, 0, sizeof(boxMark));
				memset(&boxCardMark, 0, sizeof(boxCardMark));
				SetBoxMark(xOffset + DX / 2, DY + REWARDCARDSIZE_Y, xOffset + DX / 2, DY + REWARDCARDSIZE_Y, xOffset + DX / 2, STATUSWIN_Y, 4 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, 32 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, FPS * 3, FPS * 3, 30, rewardMark[gachaIndex].detail, rewardMark[gachaIndex].grade, 2.0f * 2 / 3, 2.0f * 2 / 3, 0.2f / MOTIONDIV, 2.0f * 2 / 3, 2.0f * 2 / 3, 0.2f / MOTIONDIV);
				gachaDepth = 0;
				gachaFrame = 0;
				gachaCardIdx = 0;
			}
			else {
				OutOfGacha();
				//GotoPlay();
				//attackSequence = ATTACKSEQUENCE_REWARD;
				//sequenceDelay = ATTACKDELAY_REWARD_COLLECTING;

			}
		}

		break;
	}

	if (boxCnt > 1) {

		DrawFrame(xOffset + DX / 2 - 152 * _2X, STATUSWIN_Y2 - 80 * _2X, 304 * _2X, 48 * _2X, FRAME_SHOPBALLOON, gScreenBuffer, gScreenLayer, false);
		remainBoxCnt = (boxCnt - gachaIndex);
		width = (float)(BOXSIZE_X * 0.7f + 4 * _2X) * Min(6, remainBoxCnt) - 4 * _2X;

		for (i = gachaIndex; i < gachaIndex + Min(6, remainBoxCnt); i++) {
			DrawBox(rewardMark[i].detail, xOffset + DX / 2 - width / 2 + (float)(BOXSIZE_X * 0.7f + 4 * _2X) * (i - gachaIndex), STATUSWIN_Y2 - 78 * _2X, LEFT, boxNeutralAnimation[((frame / (MOTIONDIV * 2 * 2)) % 4)], false, true, false, true, 0.7f, gScreenBuffer, gScreenLayer, false);
		}

		DrawNum(remainBoxCnt, DX / 2 - 8 * _2X, STATUSWIN_Y2 - 78 * _2X - 52 * _2X, NUM_FONT_NORMAL, RIGHT, false, false, false, 1.0f, true, gScreenBuffer, gScreenLayer, false);
		CenterText(TEXT_SLASH, DX / 2, STATUSWIN_Y2 - 78 * _2X - 54 * _2X, 1.0f, gScreenBuffer, gScreenLayer, false);
		DrawNum(boxCnt, DX / 2 + 8 * _2X, STATUSWIN_Y2 - 78 * _2X - 52 * _2X, NUM_FONT_NORMAL, LEFT, false, false, false, 1.0f, true, gScreenBuffer, gScreenLayer, false);

	}

	gachaFrame++;
}

void NewCollectionDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i;
	float iconZoom = EQUIPZOOM;
	float width;
	ITEM* it;
	int itemType, itemDetail, itemGrade, itemLv, skillIdx, skillLv;
	int setItemCnt = 0;
	int collectionIdx;
	int newSkillIdx;

	if (newCollectionFrame % 3 == 0 && zoom == 1)
		SetHitMark(Random(DX), Random(DY), Random(2), DIANA, 1, PLAYER, HITMARKZOOM/*zoom*/);

	if (ao[ITEMBOX].levelUpFrame == 0)
		ao[ITEMBOX].levelUpFrame = 1;
	else if (ao[ITEMBOX].levelUpFrame == 11)
		ao[ITEMBOX].levelUpFrame = 0;
	else
		ao[ITEMBOX].levelUpFrame++;

	ResetRectPoint();

	MemRect(0, DY, DX, DY, COLOR_BLACK, cvtDest, cvtLayer, buffering);

	for (i = 0; i < DX / 128 * _2X + 1; i++)
		DrawImage(128 * _2X, 208 * _2X, 0 * _2X, 0 * _2X, x + (float)(i * 128 * _2X) * zoom, y + (float)(-288 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_BG_IMG + MAPTYPE_SPACE], cvtDest, cvtLayer, MAP_BG_IMG + MAPTYPE_SPACE, buffering);

	DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, x + (float)(DX / 2 - DIORAMASIZE_X / 2) * zoom, y + (float)(-288 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_DIORAMA_IMG + HOUSE_DEVILCASTLE], cvtDest, cvtLayer, MAP_DIORAMA_IMG + HOUSE_DEVILCASTLE, buffering);

	effect.color2 = COLOR_BLACK;

	CollectionDetailListDraw(x, y, newCollectionIdx[curNewCollection], zoom, cvtDest, cvtLayer, buffering);

	itemType = collectionData[newCollectionIdx[curNewCollection] * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + 0 * COLLECTIONSDATASIZE + 0];
	itemDetail = collectionData[newCollectionIdx[curNewCollection] * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + 0 * COLLECTIONSDATASIZE + 1];
	itemGrade = collectionData[newCollectionIdx[curNewCollection] * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + 0 * COLLECTIONSDATASIZE + 2];
	itemLv = GetItemLv(itemType, itemDetail, itemGrade);

	collectionIdx = GetCollectionIdx(itemType, itemDetail, itemGrade);

	skillLv = ao[PLAYER].skillLv[newSkillIdx];

	DrawNum(skillLv + 1, x + (float)(8 * _2X + SKILLICONSIZE * iconZoom * 0.75f + 2 * _2X * iconZoom) * zoom + StringWidth(textId[TEXT_SKILLNAME_COMMON_ROBIN1 + newSkillIdx], iconZoom * 0.75f * zoom) + (float)(2 * _2X * iconZoom) * zoom + StringWidth(textId[TEXT_ALPHA_LV], iconZoom * 0.5f * zoom) + (float)(8 * _2X * iconZoom) * zoom, y + (float)(-346 * _2X) * zoom, NUM_FONT_NORMAL, CENTER, 2, false, false, (float)(0.5f * iconZoom) * zoom, true, cvtDest, cvtLayer, buffering);

	for (i = 0; i < TOTALHITMARK; i++) {
		if (hitMark[i].frame > 0) {
			if (hitMark[i].x != 0 || hitMark[i].y != 0) {
				DrawEffect(1000 - 1 + hitMarkData[hitMark[i].type * 3 + (hitMark[i].etc == 0 ? 0 : 1)] + hitMark[i].frame, (float)(hitMark[i].x) * zoom, (float)(hitMark[i].y) * zoom, hitMark[i].dir, false, zoom, cvtDest, cvtLayer, buffering);
			}
		}
	}

	if (newCollectionFrame > FPS / 2) {
		effect.color2 = COLOR_BLACK;

		DrawGoldAlpha(x + (float)(DX / 2) * zoom, y + (float)(-400 * _2X) * zoom, ALPHA_CONGRATULATIONS, FONT_GOLD_LARGE, zoom, CENTER, true, false, cvtDest, cvtLayer, buffering);

		CenterText(TEXT_COLLECTIONCOMPLETED, x + DX / 2, y + (float)(-400 * _2X - 32 * _2X) * zoom, (float)(1.2f) * zoom, cvtDest, cvtLayer, buffering);

		if (newCollectionDepth == 0) {
			DrawText(TEXT_COLLECTIONREWARD, x + (float)(8 * _2X) * zoom, y + (float)(-400 * _2X - 72 * _2X) * zoom, (float)(1.5f) * zoom, cvtDest, cvtLayer, buffering);

			DrawEffect(EFFECT_INSIDE_ARROW0 + Abs(4 - (newCollectionFrame / MOTIONDIV) % 8), x + (float)(180 * _2X) * zoom, y + (float)(-400 * _2X - 80 * _2X) * zoom, RIGHT, false, (float)(2.0f) * zoom, cvtDest, cvtLayer, buffering);

			DrawBuyButton(x + (float)(DX - 128 * _2X) * zoom, y + (float)(-464 * _2X) * zoom, (float)128 * _2X * zoom, (float)BUYBUTTON_Y * zoom, newCollectionFrame, false, collectionReward[newCollectionIdx[curNewCollection] * 4 + 3], CURRENCY_HEART, zoom, false, false, false, cvtDest, cvtLayer, buffering);

			SetRectPoint(x + (float)(DX - 128 * _2X) * zoom, y + (float)(-464 * _2X) * zoom, (float)128 * _2X * zoom, (float)BUYBUTTON_Y * zoom, TOUCH_FUNC_NEWCOLLECTIONREWARDGET);
		}
	}

	for (i = 0; i < TOTALHITMARK; i++) {
		if (hitMark[i].frame > 0) {
			hitMark[i].frame++;

			if (hitMark[i].frame == hitMarkData[hitMark[i].type * 3 + 2]) {
				memset(&hitMark[i], 0, sizeof(HITMARK));
			}
		}
	}

	if (newCollectionDepth == 1) {
		effect.color2 = COLOR_BLACK;

		DrawBuyButton(x + (float)(DX - 128 * _2X) * zoom, y + (float)(-464 * _2X) * zoom, (float)128 * _2X * zoom, (float)BUYBUTTON_Y * zoom, newCollectionFrame, false, collectionReward[newCollectionIdx[curNewCollection] * 4 + 3], CURRENCY_HEART, zoom, false, false, false, cvtDest, cvtLayer, buffering);

		BarDraw(&bar[BAR_BOX], bar[BAR_BOX].zoom, cvtDest, cvtLayer, buffering);

		if (newCollectionFrame == 1) {
			AddBar(&bar[BAR_BOX], collectionReward[newCollectionIdx[curNewCollection] * 4 + 3], BARFRAME);
			GetItem(ITEM_HEART, false, false, false, collectionReward[newCollectionIdx[curNewCollection] * 4 + 3], false);

		}
		else if (newCollectionFrame == FPS * 2) {
			drawHandle = before_DrawHandle_Collections;
			keyHandle = before_KeyHandle_Collections;
			gachaFrame = 0;
		}
	}

	newCollectionFrame++;
}

void NewCardDraw(void)
{
	int i;
	float zoom = 2.0f;
	int row = 1;//가로로 몇개인지
	int col = 1;//세로로 몇줄인지
	bool crewMenuDraw = false;
	bool equipMenuDraw = false;
	float menuZoom = 1.0f;
	float width;
	int remainNewItemCnt;
	//성 등장하는 거 없애주기
	ResetRectPoint();

	MemRect(0, DY, DX, DY, mapColor[MAPTYPE_SPACE], gScreenBuffer, gScreenLayer, false);

	if (newCardFrame < GACHADELAY_BOXDROP && newCardDepth == 0)
		newCardFrame = GACHADELAY_BOXDROP;

	for (i = 0; i < DX / 128 * _2X + 1; i++)
		DrawImage(128 * _2X, 208 * _2X, 0 * _2X, 0 * _2X, xOffset + i * 128 * _2X, STATUSWIN_Y + 208 * _2X / 2, false, false, false, false, false, 1.0f, sprite[MAP_BG_IMG + MAPTYPE_SPACE], gScreenBuffer, gScreenLayer, MAP_BG_IMG + MAPTYPE_SPACE, false);

	DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, xOffset + DX / 2 - DIORAMASIZE_X / 2, STATUSWIN_Y + DIORAMASIZE_Y / 2, false, false, false, false, false, 1.0f, sprite[MAP_DIORAMA_IMG + HOUSE_DEVILCASTLE], gScreenBuffer, gScreenLayer, MAP_DIORAMA_IMG + HOUSE_DEVILCASTLE, false);

	if (newItemType[curNewItemIdx] == ITEM_CREW) {
		curStar = maxStar = crewData[newItemDetail[curNewItemIdx] * CREWDATASIZE + CREWDATASIZE - 1] + 1;
	}
	else {
		curStar = maxStar = GetItemStar(newItemType[curNewItemIdx], newItemDetail[curNewItemIdx], newItemGrade[curNewItemIdx]);
	}

	if (newCardFrame >= GACHADELAY_BOXDROP) {
		zoom = Min(2.5f, 0.3f * (newCardFrame - GACHADELAY_BOXDROP));
		DrawRewardCard(newItemType[curNewItemIdx], newItemDetail[curNewItemIdx], newItemGrade[curNewItemIdx], 0, false, DX / 2 - (float)REWARDCARDSIZE_X / 2 * zoom, STATUSWIN_Y + Min(200 * _2X, 20 * _2X * (newCardFrame - GACHADELAY_BOXDROP)) + (float)REWARDCARDSIZE_Y / 2 * zoom, true, zoom, true, true, true, curStar, maxStar, true, gScreenBuffer, gScreenLayer, false);
	}

	if (newCardFrame >= GACHADELAY_BOXOPEN) {
		zoom = Max(1.5f, 8.0f + 0.5f * (GACHADELAY_BOXOPEN - newCardFrame));
		DrawGoldAlpha(DX / 2, DY / 2 + 200 * _2X + (float)23 * _2X / 2 * zoom, ALPHA_NEWCARD, FONT_GOLD_LARGE, zoom, CENTER, true, false, gScreenBuffer, gScreenLayer, false);
	}

	switch (newCardDepth) {
	case 0:


		if (newCardFrame >= GACHADELAY_ITEMDROP) {
			//zoom = Min(1.0f, 0.3f * (newCardFrame - GACHADELAY_ITEMDROP));
			zoom = 1.0f;

			DrawText(TEXT_NEWCARDGETREWARD, (float)(8 * _2X) * zoom, DY / 2 + (float)(236 * _2X) + (float)(-400 * _2X - 76 * _2X) * zoom, (float)(1.5f) * zoom, gScreenBuffer, gScreenLayer, false);

			DrawEffect(EFFECT_INSIDE_ARROW0 + Abs(4 - (newCardFrame / MOTIONDIV) % 8), (float)(180 * _2X) * zoom, DY / 2 + (float)(236 * _2X) + (float)(-400 * _2X - 84 * _2X) * zoom, RIGHT, false, (float)(2.0f) * zoom, gScreenBuffer, gScreenLayer, false);

			DrawBuyButton((float)(DX / 2 + 32 * _2X) * zoom, DY / 2 + (float)(236 * _2X) + (float)(-464 * _2X) * zoom, (float)(108 * _2X) * zoom, (float)(32 * _2X) * zoom, frame, false, equipGetRewardHeart[newItemType[curNewItemIdx] * TOTAL_COLLECTIONS + newItemDetail[curNewItemIdx] * TOTALGRADE + newItemGrade[curNewItemIdx]], CURRENCY_HEART, zoom, false, false, false, gScreenBuffer, gScreenLayer, false);

			SetRectPoint((float)(DX / 2 + 32 * _2X) * zoom, DY / 2 + (float)(236 * _2X) + (float)(-464 * _2X) * zoom, (float)(108 * _2X) * zoom, (float)(32 * _2X) * zoom, TOUCH_FUNC_NEWCARDREWARDGET);


			//if (frame % 3 == 0)
			//	SetHitMark(Random(DX), Random(DY), Random(2), DIANA, 1, PLAYER, zoom);
		}
		break;
	case 1:
		zoom = 1.0f;

		effect.color2 = COLOR_BLACK;

		DrawBuyButton((float)(DX / 2 + 32 * _2X) * zoom, DY / 2 + (float)(236 * _2X) + (float)(-464 * _2X) * zoom, (float)(108 * _2X) * zoom, (float)(32 * _2X) * zoom, frame, false, equipGetRewardHeart[newItemType[curNewItemIdx] * TOTAL_COLLECTIONS + newItemDetail[curNewItemIdx] * TOTALGRADE + newItemGrade[curNewItemIdx]], CURRENCY_HEART, zoom, false, false, false, gScreenBuffer, gScreenLayer, false);

		BarDraw(&bar[BAR_BOX], bar[BAR_BOX].zoom, gScreenBuffer, gScreenLayer, false);

		if (newCardFrame == 1) {
			//width = GetBigNumDx(equipGetRewardHeart[newItemType[curNewItemIdx] * TOTAL_COLLECTIONS + newItemDetail[curNewItemIdx] * TOTALGRADE + newItemGrade[curNewItemIdx]], false, NUM_FONT_NORMAL, false, true, 108 * _2X - (float)(ITEMICONSIZE + 4 * _2X) * 1.0f, 1.0f, true) + (float)(ITEMICONSIZE + 4 * _2X) * 1.0f;
			//SetCurrencyMarkArr((float)(DX / 2 + 32 * _2X + 108 * _2X / 2 + ITEMICONSIZE / 2) * zoom - width / 2, DY / 2 + (float)(236 * _2X) + (float)(-464 * _2X) * zoom - (float)(32 * _2X) * zoom / 2, (float)(bar[BAR_BOX].x + 16 * _2X + 128 * _2X / 2) * zoom - (GetBigNumDx(bar[BAR_BOX].count - GetInitHeart(), true, NUM_FONT_NORMAL, false, true, (float)(HEARTBARADDNUMWIDTH)* zoom, zoom, true) + (float)(20 * _2X + 4 * _2X) * zoom) / 2 + (float)(ITEMICONSIZE / 2) * zoom, bar[BAR_BOX].y - 8 * _2X - ITEMICONSIZE, false, false, 16 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, false, false, FPS, false, ICON_HEART, 30, collectionReward[newCollectionIdx[curNewCollection] * 4 + 3], CURRENCY_HEART, 2.0f, 1.5f, -0.2f / MOTIONDIV, false, false, false, 10);

			AddBar(&bar[BAR_BOX], equipGetRewardHeart[newItemType[curNewItemIdx] * TOTAL_COLLECTIONS + newItemDetail[curNewItemIdx] * TOTALGRADE + newItemGrade[curNewItemIdx]], BARFRAME);
			GetItem(ITEM_HEART, false, false, false, equipGetRewardHeart[newItemType[curNewItemIdx] * TOTAL_COLLECTIONS + newItemDetail[curNewItemIdx] * TOTALGRADE + newItemGrade[curNewItemIdx]], false);

		}
		else if (newCardFrame == FPS * 1) {
			//현재 아이템 인덱스를 더해주고
			curNewItemIdx++;

			newCardDepth = 0;
			newCardFrame = 0;

			//만약 새로운 아이템이면
			if (newItemCnt == curNewItemIdx) {
				drawHandle = before_DrawHandle_NewCard;
				keyHandle = before_KeyHandle_NewCard;

			}
		}
		break;
	}

	if (newItemCnt > 1) {

		DrawFrame(xOffset + DX / 2 - 152 * _2X, STATUSWIN_Y, 304 * _2X, 48 * _2X, FRAME_SHOPBALLOON, gScreenBuffer, gScreenLayer, false);
		remainNewItemCnt = (newItemCnt - curNewItemIdx);
		width = (float)(BOXSIZE_X * 0.7f + 4 * _2X) * Min(6, remainNewItemCnt) - 4 * _2X;

		for (i = curNewItemIdx; i < curNewItemIdx + Min(6, remainNewItemCnt); i++) {
			//DrawBoxSpecial(xOffset + DX / 2 - width / 2 + (float)(BOXSIZE_X * 0.7f + 4 * _2X) * (i - curNewItemIdx), STATUSWIN_Y - 78 * _2X, rewardMark[i].detail, 0.7f, false, false, false, gScreenBuffer, gScreenLayer, false);
			if (newItemType[i] == ITEM_CREW) {
				curStar = maxStar = crewData[newItemDetail[i] * CREWDATASIZE + CREWDATASIZE - 1] + 1;
			}
			else {
				curStar = maxStar = GetItemStar(newItemType[i], newItemDetail[i], newItemGrade[i]);
			}

			DrawRewardCard(newItemType[i], newItemDetail[i], newItemGrade[i], 0, false, xOffset + DX / 2 - width / 2 + (float)(BOXSIZE_X * 0.7f + 4 * _2X) * (i - curNewItemIdx), STATUSWIN_Y - 4 * _2X, true, 0.7f, true, true, true, curStar, maxStar, true, gScreenBuffer, gScreenLayer, false);
		}

		DrawNum(remainNewItemCnt, DX / 2 - 8 * _2X, STATUSWIN_Y - 52 * _2X, NUM_FONT_NORMAL, RIGHT, false, false, false, 1.0f, true, gScreenBuffer, gScreenLayer, false);
		CenterText(TEXT_SLASH, DX / 2, STATUSWIN_Y - 54 * _2X, 1.0f, gScreenBuffer, gScreenLayer, false);
		DrawNum(newItemCnt, DX / 2 + 8 * _2X, STATUSWIN_Y - 52 * _2X, NUM_FONT_NORMAL, LEFT, false, false, false, 1.0f, true, gScreenBuffer, gScreenLayer, false);

	}

	newCardFrame++;

	for (i = 0; i < TOTALHITMARK; i++) {
		if (hitMark[i].frame > 0) {
			if (hitMark[i].x != 0 || hitMark[i].y != 0) {
				DrawEffect(1000 - 1 + hitMarkData[hitMark[i].type * 3 + (hitMark[i].etc == 0 ? 0 : 1)] + hitMark[i].frame, xOffset + hitMark[i].x - rx, hitMark[i].y - ry - OBJIMGGAP, hitMark[i].dir, false, 1.0f, gScreenBuffer, gScreenLayer, false);
			}
		}
	}

	for (i = 0; i < TOTALHITMARK; i++) {
		if (hitMark[i].frame > 0) {
			hitMark[i].frame++;

			if (hitMark[i].frame == hitMarkData[hitMark[i].type * 3 + 2]) {
				memset(&hitMark[i], 0, sizeof(HITMARK));
			}
		}
	}
}

void StageInfoDraw(int stage, int room, long long combatPower, bool cur, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	/**/
	int i, j, k;
	int type = ITEM_CREW;
	int detail = stage;
	int grade = 0;
	int lv = 0;
	int count = 1;
	float cardZoom = 1.5f * zoom;
	float goldZoom = 0.8f * zoom;
	float width;
	int enemyCrewY = 400 * _2X;
	int beforeEnemyCrewY;
	int stageCrewIdx;
	int stageBossIdx = GetStageBossIdx();
	int stageBossType = GetStageBossType();
	int stageBossMaxHp = (robin.stage * TOTALROOM + robin.room + 1) * (100 + enemyData[stageBossType * ENEMYDATASIZE + 3]);
	int itemType, itemDetail, itemGrade, itemCnt;
	int rewardType, rewardDetail, rewardGrade, rewardCnt;
	int curStar, maxStar;
	float yGap = (float)-32 * _2X * zoom;

	long long realValue;
	float numWidth = ITEMICONSIZE;

	int stageInfoCurFrame = stageInfoFrame;
	int bFrame = 2;

	float menuZoom;
	float fontZoom = Max(1.2f, (float)(STAGECLEARDELAY_ALPHA - stageInfoCurFrame) * 0.2f / MOTIONDIV);
	float roomZoom = 0.5f * zoom;

	long long getGoldNum = 0;
	long long getHeartNum = 0;
	long long getMedalNum = 0;
	long long getStarNum = 0;
	long long getHammerNum = 0;

	bool crewMenuDraw = false;
	bool equipMenuDraw = false;

	int doorY = 10 * TSIZE;
	int totalStar = 0;
	long long betCnt = bossGold[stage] * GetBetHeart(ao[PLAYER].equip[EQUIP_WEAPON].detail, ao[PLAYER].equip[EQUIP_WEAPON].grade, bet);

	int mapIdx;
	int price;

	long long betGold = GetStageAdmissionFee();

	int textPos = 0;
	float textZoom = 1.0f;

	if (cur == false)
		stageInfoCurFrame = FPS * 10;

	//ao[ENEMY].type = stageEnemy[robin.stage * TOTALROOM + robin.room];
	SetEnemy(&ao[ENEMY]);
	ao[ENEMY].active = false;
	//보스

	//robin.stage = 9;


	switch (stageInfoDepth) {
	case STAGEINFO_CREWDROP:
		DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], cvtDest, cvtLayer, UI_PAPER_POPUP_IMG, buffering);

		//DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom - (float)(DIORAMASIZE_X) / 2 * zoom, y + (float)16 * _2X * zoom + yGap, false, false, false, false, false, zoom, sprite[MAP_DIORAMA_IMG + stageHouseType[stage]], cvtDest, cvtLayer, MAP_DIORAMA_IMG + stageHouseType[stage], buffering);
		//보스 정보
		DrawStageLabel(x + (float)(DX / 2) * zoom, y + (float)(8 * _2X) * zoom, TEXT_STAGE, robin.stage, robin.room, true, zoom, cvtDest, cvtLayer, buffering);

		//웨이브 보스
		//if (stageInfoCurFrame > 20)
		DrawCmfDetailShadow(enemyData[stageBossType * ENEMYDATASIZE + ENEMYDATA_CMF], frame / 2 % crewPos[stageBossType * CREWDATASIZE], x + (float)(DX / 2) * zoom, y - (float)108 * _2X * zoom + Max(0 * _2X, (FPS / 2 - stageInfoCurFrame) * 16 * _2X) * zoom + yGap, RIGHT, zoom, cvtDest, cvtLayer, buffering);

		//BossHpBarDraw(GetStageBossObjectIdx() == false ? stageBossMaxHp : ao[GetStageBossObjectIdx()].hp, stageBossMaxHp, x + (float)(DX / 2) * zoom, y - (float)116 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);
		if (stageInfoCurFrame > 23)
			DrawGoldAlpha(x + (float)92 * _2X * zoom, y - (float)(DIORAMASIZE_Y - 44 * _2X) * zoom + yGap, ALPHA_BOSS, FONT_GOLD_LARGE, 0.7f * zoom, LEFT, true, false, cvtDest, cvtLayer, buffering);

		if (stageInfoCurFrame > 26) {
			HpBarDraw(stageBossType, GetStageBossObjectIdx() == false ? stageBossMaxHp : ao[GetStageBossObjectIdx()].hp, stageBossMaxHp, x + (float)(DX / 2) * zoom, y - (float)152 * _2X * zoom + yGap, zoom, cvtDest, cvtLayer, buffering);
		}

		if (stageInfoCurFrame > 30) {
			SetAlpha(28);
			GradiationFrame(x + (float)(POPUPWINDOWSIZE_X - 280 * _2X) / 2 * zoom, y - (float)(192 * _2X) * zoom + yGap, (float)280 * _2X * zoom, (float)24 * _2X * zoom, 0, cvtDest, cvtLayer, buffering);
			SetAlpha(32);
		}

		if (stageInfoCurFrame > 33)
			CenterText(TEXT_CLEARREWARDS, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)(192 * _2X + 7 * _2X) * zoom + yGap, zoom, cvtDest, cvtLayer, buffering);

		if (stageInfoCurFrame > 36)
			DrawBox(stageClearBox[robin.stage], x + (float)48 * _2X * zoom, y - (float)(200 * _2X + 88 * _2X) * zoom + yGap, LEFT, false, COLOR_WHITE, false, false, true, (float)BOXHOUSEZOOM * zoom, cvtDest, cvtLayer, buffering);

		if (stageInfoCurFrame > 39) {
			DrawFrame(x + (float)(88 * _2X) * zoom, y - (float)(200 * _2X + 26 * _2X) * zoom + yGap, (float)208 * _2X * zoom, (float)RAIDGOLDBARHEIGHT * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
		}

		if (stageInfoCurFrame > 42) {
			InitReward();

			for (i = 0; i < BOX1MAXREWARDITEM; i++) {
				itemType = stageClearReward[robin.stage * BOX1MAXREWARDITEM * REWARDDATASIZE + i * REWARDDATASIZE];
				itemDetail = stageClearReward[robin.stage * BOX1MAXREWARDITEM * REWARDDATASIZE + i * REWARDDATASIZE + 1];
				itemGrade = stageClearReward[robin.stage * BOX1MAXREWARDITEM * REWARDDATASIZE + i * REWARDDATASIZE + 2];
				itemCnt = stageClearReward[robin.stage * BOX1MAXREWARDITEM * REWARDDATASIZE + i * REWARDDATASIZE + 3];

				if (itemType != -1) {
					rewardItem[rewardItemCnt].type = itemType;
					rewardItem[rewardItemCnt].detail = itemDetail;
					rewardItem[rewardItemCnt].grade = itemGrade;
					rewardItem[rewardItemCnt].count = itemCnt;

					rewardItemCnt++;
				}
			}
			//웨이브 보상
			for (i = 0; i < rewardItemCnt; i++) {
				rewardType = stageClearReward[robin.stage * BOX1MAXREWARDITEM * REWARDDATASIZE + i * REWARDDATASIZE + 0];
				rewardDetail = stageClearReward[robin.stage * BOX1MAXREWARDITEM * REWARDDATASIZE + i * REWARDDATASIZE + 1];
				rewardGrade = stageClearReward[robin.stage * BOX1MAXREWARDITEM * REWARDDATASIZE + i * REWARDDATASIZE + 2];
				rewardCnt = stageClearReward[robin.stage * BOX1MAXREWARDITEM * REWARDDATASIZE + i * REWARDDATASIZE + 3];

				if (rewardType == ITEM_CREW) {
					curStar = maxStar = crewData[rewardDetail * CREWDATASIZE + CREWDATASIZE - 1] + 1;
				}
				else {
					curStar = maxStar = GetItemStar(rewardType, rewardDetail, rewardGrade);
				}

				DrawRewardCard(rewardType, rewardDetail, rewardGrade, 1, rewardCnt, x + (float)(DX / 2 - (rewardItemCnt) * (REWARDCARDSIZE_X + 4 * _2X) * 1.5f / 2 + i * (REWARDCARDSIZE_X + 2 * _2X) * 1.5f + 38 * _2X) * zoom, y - (float)(224 * _2X) * zoom + yGap, false, 1.5f * zoom, false, false, true, curStar, maxStar, true, cvtDest, cvtLayer, buffering);

			}
			//width = (float)(ITEMICONSIZE * 1.5f + 4 * _2X) * goldZoom + GetBigNumGoldDx(betCnt, false, FONT_GOLD_LARGE, false, true, (float)(256 * _2X - 32 * _2X) * zoom, goldZoom);

			//DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom - width / 2, y - (float)(200 * _2X + 24 * _2X) * zoom - (float)8 * _2X * zoom, 1.5f * goldZoom, false, false, false, cvtDest, cvtLayer, buffering);

			//DrawBigNumGold(betCnt, x + (float)POPUPWINDOWSIZE_X / 2 * zoom - width / 2 + (float)(ITEMICONSIZE * 1.5f + 4 * _2X) * zoom, y - (float)(200 * _2X + 24 * _2X) * zoom - (float)8 * _2X * zoom, FONT_GOLD_LARGE, LEFT, false, false, (float)(240 * _2X - 32 * _2X) * goldZoom, true, goldZoom, cvtDest, cvtLayer, buffering);
		}


		break;
	case STAGEINFO_CREWGACHA:


		//SetAlpha(28);
		//GradiationFrame(x + (float)(POPUPWINDOWSIZE_X - 280 * _2X) / 2 * zoom, y - (float)(200 * _2X) * zoom, (float)280 * _2X * zoom, (float)24 * _2X * zoom, 0, cvtDest, cvtLayer, buffering);
		//SetAlpha(32);

		//CenterText(TEXT_GOLDPOSSETION, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)(200 * _2X + 7 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

		//DrawFrame(x + (float)(POPUPWINDOWSIZE_X - 240 * _2X) / 2 * zoom, y - (float)(200 * _2X + 26 * _2X) * zoom, (float)240 * _2X * zoom, (float)RAIDGOLDBARHEIGHT * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);

		//width = (float)(ITEMICONSIZE * 1.5f + 4 * _2X) * goldZoom + GetBigNumGoldDx(bossHp, false, FONT_GOLD_LARGE, false, true, (float)(240 * _2X - 32 * _2X) * zoom, goldZoom);

		//DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom - width / 2, y - (float)(200 * _2X + 24 * _2X) * zoom - (float)8 * _2X * zoom, 1.5f * goldZoom, false, false, false, cvtDest, cvtLayer, buffering);

		//DrawBigNumGold(bossHp, x + (float)POPUPWINDOWSIZE_X / 2 * zoom - width / 2 + (float)(ITEMICONSIZE * 1.5f + 4 * _2X) * zoom, y - (float)(200 * _2X + 24 * _2X) * zoom - (float)8 * _2X * zoom, FONT_GOLD_LARGE, LEFT, false, false, (float)(240 * _2X - 32 * _2X) * goldZoom, true, goldZoom, cvtDest, cvtLayer, buffering);
		SetAlpha(Max(0, 32 - stageInfoFrame));
		DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], cvtDest, cvtLayer, UI_PAPER_POPUP_IMG, buffering);
		SetAlpha(32);

		//DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom - (float)(DIORAMASIZE_X) / 2 * zoom, y + (float)16 * _2X * zoom - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_DIORAMA_IMG + stageHouseType[stage]], cvtDest, cvtLayer, MAP_DIORAMA_IMG + stageHouseType[stage], buffering);

		//세입자
		for (i = MAXCREW - 1; i >= 0; i--) {
			if (enemyHouse.crew[i] != null) {
				switch (stageInfoDepth) {
				case STAGEINFO_CREWDROP:
				case STAGEINFO_CREWGACHA:


					if (stageInfoCurFrame < STAGECLEARDELAY_HAPPYTIME) {
						beforeEnemyCrewY = enemyCrewY;

						enemyCrewY -= stageInfoCurFrame * 16 * _2X * 2 / MOTIONDIV;

						if (enemyCrewY < 0)
							enemyCrewY = 0;

						//DrawCmfDetailShadow(enemyData[enemyHouse.crew[i] * ENEMYDATASIZE + ENEMYDATA_CMF], enemyBigIconPos[enemyHouse.crew[i] * 3 + 0], x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom - (float)(DIORAMASIZE_X) / 2 * zoom + (float)stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3] * zoom, y + (float)stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3 + 1] * zoom + (float)8 * _2X + enemyCrewY - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom, stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3 + 2], enemyZoom[enemyHouse.crew[i]] * dioramaZoom * zoom, cvtDest, cvtLayer, buffering);
					}
					else if (stageInfoCurFrame < STAGECLEARDELAY_LEVITATION) {
						beforeEnemyCrewY = enemyCrewY;

						enemyCrewY = (stageInfoCurFrame - STAGECLEARDELAY_HAPPYTIME) * 1 * _2X * 2 / MOTIONDIV;

						//DrawCmfDetailShadow(enemyData[enemyHouse.crew[i] * ENEMYDATASIZE + ENEMYDATA_CMF], enemyBigIconPos[enemyHouse.crew[i] * 3 + 0], x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom - (float)(DIORAMASIZE_X) / 2 * zoom + (float)stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3] * zoom, y + (float)stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3 + 1] * zoom + (float)8 * _2X + enemyCrewY - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom, stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3 + 2], enemyZoom[enemyHouse.crew[i]] * dioramaZoom * zoom, cvtDest, cvtLayer, buffering);
					}
					else if (stageInfoCurFrame < STAGECLEARDELAY_ROTATION) {
						enemyCrewY = FPS * _2X;

						//DrawCmfDetailShadow(enemyData[enemyHouse.crew[i] * ENEMYDATASIZE + ENEMYDATA_CMF], enemyBigIconPos[enemyHouse.crew[i] * 3 + 0], x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom + points[(stageInfoCurFrame - STAGECLEARDELAY_LEVITATION + i * 10) % MAX_POINTS][0], y + (float)stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3 + 1] * zoom + (float)8 * _2X + enemyCrewY - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom + points[(stageInfoCurFrame - STAGECLEARDELAY_LEVITATION + i * 10) % MAX_POINTS][1], stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3 + 2], enemyZoom[enemyHouse.crew[i]] * dioramaZoom * zoom, cvtDest, cvtLayer, buffering);


					}
					else if (stageInfoCurFrame < STAGECLEARDELAY_TOGETHER) {
						enemyCrewY = STAGECLEARDELAY_TOGETHER - stageInfoCurFrame;
						//if (32 - (stageInfoCurFrame - STAGECLEARDELAY_ROTATION) / MOTIONDIV / 8 > 0) {
						SetAlpha(32 - (stageInfoCurFrame - STAGECLEARDELAY_ROTATION) / MOTIONDIV / 8);
						//DrawCmfDetailShadow(enemyData[enemyHouse.crew[i] * ENEMYDATASIZE + ENEMYDATA_CMF], enemyBigIconPos[enemyHouse.crew[i] * 3 + 0], x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom + points[(STAGECLEARDELAY_TOGETHER - stageInfoCurFrame - FPS + i * 10) % MAX_POINTS][0], y + (float)stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3 + 1] * zoom + (float)8 * _2X + enemyCrewY - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom + points[(STAGECLEARDELAY_TOGETHER - FPS - stageInfoCurFrame + i * 10) % MAX_POINTS][1], stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3 + 2], enemyZoom[enemyHouse.crew[i]] * dioramaZoom * zoom, cvtDest, cvtLayer, buffering);
						SetAlpha(32);
						//}
					}
					else if (stageInfoCurFrame < STAGECLEARDELAY_SELECTEDCREW) {
						enemyCrewY = 0;
						if (i == selectedCrew) {
							SetAlpha(Min(32, stageInfoCurFrame - STAGECLEARDELAY_TOGETHER));
							//DrawCmfDetailShadow(enemyData[enemyHouse.crew[i] * ENEMYDATASIZE + ENEMYDATA_CMF], enemyBigIconPos[enemyHouse.crew[i] * 3 + 0], x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - DIORAMASIZE_Y / 2 + (float)8 * _2X + enemyCrewY - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom, stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3 + 2], enemyZoom[enemyHouse.crew[i]] * 1.5f * zoom, cvtDest, cvtLayer, buffering);
							SetAlpha(32);
							DrawCmfDetail(CMF_NPC_HEART, PO_C122_SPARK0 + stageInfoCurFrame / MOTIONDIV % 8, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - DIORAMASIZE_Y / 2 + (float)8 * _2X + enemyCrewY - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom + (float)100 * _2X * zoom, LEFT, LOBBYZOOM, false, false, gScreenBuffer, gScreenLayer, false);
						}
					}
					else if (stageInfoCurFrame < STAGECLEARDELAY_CREWAPPEAR) {
						enemyCrewY = 0;
						if (i == selectedCrew) {
							//DrawCmfDetailShadow(enemyData[enemyHouse.crew[i] * ENEMYDATASIZE + ENEMYDATA_CMF], enemyBigIconPos[enemyHouse.crew[i] * 3 + 0], x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - DIORAMASIZE_Y / 2 + (float)8 * _2X + enemyCrewY - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom, stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3 + 2], enemyZoom[enemyHouse.crew[i]] * 1.5f * zoom, cvtDest, cvtLayer, buffering);
						}
					}
					else if (stageInfoCurFrame < STAGECLEARDELAY_NEWCARD) {
						enemyCrewY = 0;
						if (i == selectedCrew) {
							//DrawCmfDetailShadow(enemyData[enemyHouse.crew[i] * ENEMYDATASIZE + ENEMYDATA_CMF], enemyBigIconPos[enemyHouse.crew[i] * 3 + 0], x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - DIORAMASIZE_Y / 2 + (float)8 * _2X + enemyCrewY - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom, stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3 + 2], enemyZoom[enemyHouse.crew[i]] * 1.5f * zoom, cvtDest, cvtLayer, buffering);

							if (stageInfoCurFrame == STAGECLEARDELAY_CREWAPPEAR)
								SetRewardMark(x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - DIORAMASIZE_Y / 2 + (float)8 * _2X + enemyCrewY - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom, DX / 2, DY / 2 + 148 * _2X, DX / 2, DY / 2 + 148 * _2X, 32 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, 16 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, FPS, FPS, false, 30, 1,
									ITEM_CREW, GetCrewIdxFromType(enemyHouse.crew[i]), GRADE_NORMAL, false, true, true, false, PLAYER, true, true, GetInvenIdx(ITEM_CREW, GetCrewIdxFromType(enemyHouse.crew[i]), GRADE_NORMAL) == -1 ? false : true, 0.2f / MOTIONDIV, 3.0f, 0.4f / MOTIONDIV, 3.0f, 2.5f, -0.2f / MOTIONDIV);

							if (stageInfoCurFrame == STAGECLEARDELAY_NEWCARD - 2) {
								stageInfoFrame = stageInfoCurFrame = STAGECLEARDELAY_NEWCARD - 3;
								SetFontColor(itemColor[crewData[GetCrewIdxFromType(enemyHouse.crew[i]) * CREWDATASIZE + CREWDATASIZE - 1]]);
								CenterText(TEXT_MONSTERNAME_START + enemyHouse.crew[i], DX / 2, DY / 2 + TABBUTTONGAP + 80 * _2X, 2.0f, gScreenBuffer, gScreenLayer, false);
								SetFontColor(COLOR_WHITE);
								CenterText(TEXT_STAGECLEARCREWGET, DX / 2, DY / 2 + TABBUTTONGAP + 48 * _2X, 1.5f, gScreenBuffer, gScreenLayer, false);
								SetAlpha(32 - Abs(frame / MOTIONDIV % 32 - 16));
								DrawGoldAlpha(xOffset + DX / 2, DY / 2 + TABBUTTONGAP, ALPHA_TABTOCOLLECT, FONT_GOLD_LARGE, 1, CENTER, false, false, gScreenBuffer, gScreenLayer, false);
								SetAlpha(32);

								SetRectPoint(0, DY, DX, DY, TOUCH_FUNC_GETCREW);
							}
						}
					}
					else if (stageInfoCurFrame < STAGECLEARDELAY_GETCARD) {
						enemyCrewY = 0;
						if (i == selectedCrew) {
							//DrawCmfDetailShadow(enemyData[enemyHouse.crew[i] * ENEMYDATASIZE + ENEMYDATA_CMF], enemyBigIconPos[enemyHouse.crew[i] * 3 + 0], x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - DIORAMASIZE_Y / 2 + (float)8 * _2X + enemyCrewY - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom, stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3 + 2], enemyZoom[enemyHouse.crew[i]] * dioramaZoom * zoom, cvtDest, cvtLayer, buffering);

							if (stageInfoCurFrame == STAGECLEARDELAY_NEWCARD) {
								rewardMark[0].targetX2 = xOffset + DX / 2 + 108 * _2X + 20 * _2X;
								rewardMark[0].targetY2 = STATUSWIN_Y + JOYSTICKGAP + 83 * _2X;
								rewardMark[0].zoom2 = rewardMark[0].zoom;
								rewardMark[0].zoomEnd2 = 1.0f;
								rewardMark[0].zoomIncrement2 = -0.2f / MOTIONDIV;
								rewardMark[0].speed2 = 2 * _2X / MOTIONDIV;
								rewardMark[0].speedIncrement2 = 2 * _2X / MOTIONDIV;
								rewardMark[0].frame2 = 1;

								PlayMusic(M_CARDSPLIT);
							}

							if (stageInfoCurFrame - STAGECLEARDELAY_NEWCARD < 15)
								menuZoom = Min(1.5f, (float)(stageInfoCurFrame - STAGECLEARDELAY_NEWCARD) / 10);
							else if (stageInfoCurFrame - STAGECLEARDELAY_NEWCARD < 15 + 15)
								menuZoom = 1.5f;
							else if (stageInfoCurFrame - STAGECLEARDELAY_NEWCARD < 15 + 15 + 5)
								menuZoom = Max(1.0f, 1.5f - (float)(stageInfoCurFrame - STAGECLEARDELAY_NEWCARD - 15 - 15) / 10);
							else
								menuZoom = 1.0f;

							startX = xOffset + DX / 2 + 108 * _2X + 40 * _2X / 2 - (float)(40 * _2X) * menuZoom / 2;
							startY = STATUSWIN_Y + JOYSTICKGAP + 83 * _2X + (float)(40 * _2X) * menuZoom / 2;

							DrawImage(40 * _2X, 40 * _2X, 80 * _2X, 0 * _2X, startX, startY, false, false, false, false, 32, menuZoom, sprite[MENUICON_IMG], gScreenBuffer, gScreenLayer, MENUICON_IMG, false);

						}
					}
					break;

				}
			}

		}

		//1.성과 동료들을 앞으로 내 세운 상태에서
		if (stageInfoCurFrame < STAGECLEARDELAY_APPEAR) {
			UnSectionClip(true);
			//DrawCmfDetail(enemyData[boss[stage] * ENEMYDATASIZE + ENEMYDATA_CMF], crewPos[boss[stage] * 5 + 0] + (FPS / 2 + 10 < stageInfoCurFrame ? frame / 2 / MOTIONDIV : 0) % crewPos[boss[stage] * 5 + 1], x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)DIORAMASIZE_Y * zoom + (float)32 * _2X * zoom - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom, RIGHT, enemyZoom[boss[stage]] * enemyBossZoom[boss[stage]] * zoom * 0.6f + (float)stageInfoCurFrame * zoom * 0.01f + (float)stageInfoCurFrame * stageInfoCurFrame / 5 * zoom * 0.001f, false, false, cvtDest, cvtLayer, buffering);
			UnSectionClip(false);
		}
		//2.보스가 날라가고
		else if (stageInfoCurFrame < STAGECLEARDELAY_BOSSAWAY) {
			UnSectionClip(true);
			//DrawCmfDetail(enemyData[boss[stage] * ENEMYDATASIZE + ENEMYDATA_CMF], crewPos[boss[stage] * 5 + 0] + (FPS / 2 + 10 < stageInfoCurFrame ? frame / 2 / MOTIONDIV : 0) % crewPos[boss[stage] * 5 + 1], x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)DIORAMASIZE_Y * zoom + (float)32 * _2X * zoom - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom, RIGHT, enemyZoom[boss[stage]] * enemyBossZoom[boss[stage]] * zoom * 0.6f + (float)stageInfoCurFrame * zoom * 0.01f + (float)stageInfoCurFrame * stageInfoCurFrame / 5 * zoom * 0.001f, (stageInfoCurFrame + (stageInfoCurFrame * stageInfoCurFrame) / (5 * MOTIONDIV)) % 360, false, cvtDest, cvtLayer, buffering);
			UnSectionClip(false);
		}
		//3.세입자들이 웃는 모습이 나오고, 여기서 밑에 텍스트를 띄워주면서 룰렛 스타트를 사용자가 선택하게 시킨다.
		else if (stageInfoCurFrame < STAGECLEARDELAY_HAPPYTIME) {

			for (i = MAXCREW - 1; i >= 0; i--) {

				//DrawArray(IMG_BALLOON0 + bFrame, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom - (float)(DIORAMASIZE_X) / 2 * zoom + (float)stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3] * zoom + (float)(balloonPos[bFrame * 2] + stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3 + 2] * 4 * _2X) * zoom, y + (float)stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3 + 1] * zoom + (float)8 * _2X + enemyCrewY - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom - (float)balloonPos[bFrame * 2 + 1] * zoom, 1.0f, gScreenBuffer, gScreenLayer, false);

				//DrawEmoticon(EMOTICON_HAPPY, false, stageInfoCurFrame, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom - (float)(DIORAMASIZE_X) / 2 * zoom + (float)stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3] * zoom + (float)2 * _2X * stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3 + 2] * zoom, y + (float)stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3 + 1] * zoom + (float)8 * _2X * zoom + (float)enemyCrewY * zoom - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom + (float)43 * _2X * zoom, 0.9f, gScreenBuffer, gScreenLayer, false);
			}
		}

		if (stageInfoCurFrame == STAGECLEARDELAY_GETCARD) {
			GetItem(rewardMark[0].type, 1, rewardMark[0].detail, rewardMark[0].grade, 1, false);
			//robin.crew[GetCrewIdxFromType(stageCrew[selectedCrew])] = true;
			memset(&rewardMark[0], 0, sizeof(rewardMark[0]));
			stageInfoDepth = STAGEINFO_STAGECLEAR;
			stageInfoFrame = 0;
		}
		break;
		//스테이지 클리어 보상
	case STAGEINFO_STAGECLEAR:
		SetAlpha(20);
		MemRect(0, DY, DX, DY, COLOR_BLACK, cvtDest, cvtLayer, buffering);
		SetAlpha(32);

		DrawGoldAlpha(DX / 2, DY - GNBHEIGHT - 16 * _2X, ALPHA_STAGECLEAR, FONT_GOLD_LARGE, fontZoom, CENTER, true, false, gScreenBuffer, gScreenLayer, false);

		//스테이지 클리어 알파벳이 뜨고
		if (stageInfoCurFrame < STAGECLEARDELAY_ALPHA) {

		}
		//상자가 뜨고
		else if (stageInfoCurFrame < STAGECLEARDELAY_BOXDROP) {
			if (stageInfoCurFrame == STAGECLEARDELAY_ALPHA) {
				SetBoxMark(xOffset + DX / 2, DY + REWARDCARDSIZE_Y, xOffset + DX / 2, STATUSWIN_Y + 16 * _2X, xOffset + DX / 2, STATUSWIN_Y + 16 * _2X, 16 * _2X * 2 / MOTIONDIV, 2 * _2X * 2 / MOTIONDIV, 2 * _2X * 2 / MOTIONDIV, 2 * _2X * 2 / MOTIONDIV, FPS * 3, FPS * 3, 30, stageClearBox[robin.stage], GRADE_NORMAL, BOXZOOM, BOXZOOM, 0.2f / MOTIONDIV, BOXZOOM, BOXZOOM, 0.2f / MOTIONDIV);
			}
		}
		//상자가 열리면서 내부 보상이 나오고, 상자는 사라지고
		else if (stageInfoCurFrame < STAGECLEARDELAY_CLEARREWARD) {

			int row = 1;
			int col = 1;
			float zoom = 1.0f;
			int gap;
			int itemType;
			int itemDetail;
			int itemGrade;
			int itemCnt;

			if (stageInfoCurFrame == STAGECLEARDELAY_BOXDROP) {
				boxMark[0].jokboIcon = true;
				InitReward();

				for (i = 0; i < BOX1MAXREWARDITEM; i++) {
					itemType = stageClearReward[robin.stage * BOX1MAXREWARDITEM * REWARDDATASIZE + i * REWARDDATASIZE];
					itemDetail = stageClearReward[robin.stage * BOX1MAXREWARDITEM * REWARDDATASIZE + i * REWARDDATASIZE + 1];
					itemGrade = stageClearReward[robin.stage * BOX1MAXREWARDITEM * REWARDDATASIZE + i * REWARDDATASIZE + 2];
					itemCnt = stageClearReward[robin.stage * BOX1MAXREWARDITEM * REWARDDATASIZE + i * REWARDDATASIZE + 3];

					if (itemType != -1) {
						rewardItem[rewardItemCnt].type = itemType;
						rewardItem[rewardItemCnt].detail = itemDetail;
						rewardItem[rewardItemCnt].grade = itemGrade;
						rewardItem[rewardItemCnt].count = itemCnt;

						rewardItemCnt++;
					}
				}
			}

			switch (rewardItemCnt) {
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
			case 9:
				row = 3;
				col = 3;
				zoom = 1.5f;
				gap = 16 * _2X;
				break;
			case 10:
			case 11:
			case 12:
				row = 4;
				col = 3;
				zoom = 1.5f;
				gap = 16 * _2X;
				break;
			case 13:
			case 14:
			case 15:
			case 16:
				row = 4;
				col = 3;
				zoom = 1.5f;
				gap = 16 * _2X;
				break;
			}

			zoom = 1.5f;

			if (stageInfoCurFrame % ROULETTEDIV == 0 && stageRewardIdx < rewardItemCnt) {
				itemType = stageClearReward[robin.stage * BOX1MAXREWARDITEM * REWARDDATASIZE + stageRewardIdx * REWARDDATASIZE];
				itemDetail = stageClearReward[robin.stage * BOX1MAXREWARDITEM * REWARDDATASIZE + stageRewardIdx * REWARDDATASIZE + 1];
				itemGrade = stageClearReward[robin.stage * BOX1MAXREWARDITEM * REWARDDATASIZE + stageRewardIdx * REWARDDATASIZE + 2];
				itemCnt = stageClearReward[robin.stage * BOX1MAXREWARDITEM * REWARDDATASIZE + stageRewardIdx * REWARDDATASIZE + 3];

				startX = xOffset + DX / 2;
				startY = STATUSWIN_Y - BOXSIZE_Y;

				targetX = xOffset + DX / 2 - (float)(REWARDCARDSIZE_X * zoom * row + gap * (row - 1)) / 2 + (float)(REWARDCARDSIZE_X * zoom + gap) * (stageRewardIdx % row) + (float)(REWARDCARDSIZE_X * zoom) / 2;
				targetY = DY / 2 + (float)REWARDCARDSIZE_Y * zoom * col - (float)(REWARDCARDSIZE_Y * zoom + gap) * (stageRewardIdx / row) - (float)(REWARDCARDSIZE_Y * zoom) / 2;

				SetBoxCardMark(startX, startY, targetX, targetY, false, false, 16 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, false, false, FPS, FPS, GetItemIcon(itemType, itemDetail, itemGrade), 30, itemCnt,
					itemType, itemDetail, itemGrade, 1, false, true, false, PLAYER, true, itemType < ITEM_GEM || itemType == ITEM_CREW ? true : false, ((itemType < ITEM_GEM && GetInvenIdx(itemType, itemDetail, itemGrade) == -1) || (itemType == ITEM_CREW)) ? true : false, 0.2f / MOTIONDIV, zoom, 0.2f / MOTIONDIV, false, false, false);

				stageRewardIdx++;
			}
		}
		//보상을 탭하라는 메뉴가 나오고
		else if (stageInfoCurFrame < STAGECLEARDELAY_TABREWARD) {
			SetAlpha(32 - Abs(frame / MOTIONDIV % 32 - 16));
			DrawGoldAlpha(xOffset + DX / 2, DY / 2 + TABBUTTONGAP, ALPHA_TABTOCOLLECT, FONT_GOLD_LARGE, 1, CENTER, false, false, gScreenBuffer, gScreenLayer, false);
			SetAlpha(32);

			SetRectPoint(0, DY, DX, DY, TOUCH_FUNC_STAGEREWARD);

			if (stageInfoCurFrame == STAGECLEARDELAY_TABREWARD - 2)
				stageInfoFrame = stageInfoCurFrame = STAGECLEARDELAY_TABREWARD - 3;

		}
		else if (stageInfoCurFrame < STAGECLEARDELAY_GETREWARD) {
			j = 0;
			for (i = 0; i < rewardItemCnt; i++) {
				startX = boxCardMark[i].x;
				startY = boxCardMark[i].y;

				switch (rewardItem[i].type) {
				case ITEM_GOLD:
					startX = boxCardMark[i].x + ITEMICONSIZE + 8 * _2X;

					getGoldNum += rewardItem[i].count;

					targetX = bar[BAR_GOLD].x + 8 * _2X + ITEMICONSIZE / 2;
					targetY = bar[BAR_GOLD].y - 8 * _2X - ITEMICONSIZE / 2;

					if (stageInfoCurFrame == STAGECLEARDELAY_TABREWARD) {
						SetCurrencyMarkArr_PopUp(startX, startY, targetX, targetY, targetX, targetY, 16 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, CURRENCYWAITINGFRAMEMAX, CURRENCYWAITINGFRAMEMAX, ICON_GOLD, 30, rewardItem[i].count, CURRENCY_GOLD, 2.0f, 2.0f, -0.2f / MOTIONDIV, 2.0f, 1.0f, -0.2f / MOTIONDIV, 10);
						j++;
					}

					BarDraw(&bar[BAR_GOLD], bar[BAR_GOLD].zoom, cvtDest, cvtLayer, buffering);
					break;
				case ITEM_HEART:
					startY = boxCardMark[i].y + ITEMICONSIZE;

					getHeartNum += rewardItem[i].count;

					targetX = xOffset + bar[BAR_HEART].x;
					targetY = bar[BAR_HEART].y - TSIZE * 1 / 2;

					if (stageInfoCurFrame == STAGECLEARDELAY_TABREWARD) {
						SetCurrencyMarkArr_PopUp(startX, startY, targetX, targetY, targetX, targetY, 4 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, 16 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, FPS / 2, FPS / 2, ICON_HEART, 30, rewardItem[i].count, CURRENCY_HEART, 2.0f, 2.0f, 0.2f / MOTIONDIV, 2.0f, 1.0f, -0.2f / MOTIONDIV, 10);
						j++;
					}

					BarDraw(&bar[BAR_HEART], bar[BAR_HEART].zoom, cvtDest, cvtLayer, buffering);
					break;
				case ITEM_MEDAL:
					getMedalNum += rewardItem[i].count;

					targetX = xOffset + 4 * _2X + 164 * _2X + ITEMICONSIZE / 2;
					targetY = (GNBHEIGHT == GNB_INIT_HEIGHT ? DY : DY - NORCH_HEIGHT) - ITEMICONSIZE / 2;
					if (stageInfoCurFrame == STAGECLEARDELAY_TABREWARD) {
						SetCurrencyMarkArr_PopUp(startX, startY, targetX, targetY, false, false, 16 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, false, false, CURRENCYWAITINGFRAMEMAX, 0, ICON_MEDAL, 30, rewardItem[i].count, CURRENCY_MEDAL, 2.0f, 2.0f, -0.2f / MOTIONDIV, 2.0f, 1.0f, -0.2f, 10);
						j++;
					}

					BarDraw(&bar[BAR_MEDAL], bar[BAR_MEDAL].zoom, cvtDest, cvtLayer, buffering);
					break;
				case ITEM_STAR:
					getStarNum += rewardItem[i].count;

					targetX = xOffset + 4 * _2X + 164 * _2X + ITEMICONSIZE / 2;
					targetY = (GNBHEIGHT == GNB_INIT_HEIGHT ? DY : DY - NORCH_HEIGHT) - ITEMICONSIZE / 2;
					if (stageInfoCurFrame == STAGECLEARDELAY_TABREWARD) {
						SetCurrencyMarkArr_PopUp(startX, startY, targetX, targetY, false, false, 16 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, false, false, CURRENCYWAITINGFRAMEMAX, 0, ICON_STAR, 30, rewardItem[i].count, CURRENCY_STAR, 2.0f, 1.0f, -0.2f / MOTIONDIV, false, false, false, 10);
						j++;
					}
					break;
				case ITEM_HAMMER:
					getHammerNum += rewardItem[i].count;

					targetX = xOffset + 4 * _2X + 164 * _2X + ITEMICONSIZE / 2;
					targetY = (GNBHEIGHT == GNB_INIT_HEIGHT ? DY : DY - NORCH_HEIGHT) - ITEMICONSIZE / 2;
					if (stageInfoCurFrame == STAGECLEARDELAY_TABREWARD) {
						SetCurrencyMarkArr_PopUp(startX, startY, targetX, targetY, false, false, 4 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, false, false, CURRENCYWAITINGFRAMEMAX, 0, ICON_HAMMER, 30, rewardItem[i].count, CURRENCY_HAMMER, 2.0f, 1.0f, -0.2f / MOTIONDIV, false, false, false, 10);
						j++;
					}
					BarDraw(&bar[BAR_HAMMER], bar[BAR_HAMMER].zoom, cvtDest, cvtLayer, buffering);
					break;
				case ITEM_SWORD:
				case ITEM_GUN:
				case ITEM_BOOMERANG:
				case ITEM_HELM:
				case ITEM_HAT:
				case ITEM_CAP:
				case ITEM_ARMOR:
				case ITEM_VEST:
				case ITEM_COAT:
				case ITEM_GUNTLET:
				case ITEM_ARMLET:
				case ITEM_GLOVE:
				case ITEM_KILT:
				case ITEM_SKIRT:
				case ITEM_PANTS:
				case ITEM_GREAVES:
				case ITEM_SHOES:
				case ITEM_BOOTS:
				case ITEM_CREW:
					if (stageInfoCurFrame - STAGECLEARDELAY_TABREWARD < 15)
						menuZoom = Min(1.5f, (float)(stageInfoCurFrame - STAGECLEARDELAY_TABREWARD) / 10);
					else if (stageInfoCurFrame - STAGECLEARDELAY_TABREWARD < 15 + 15)
						menuZoom = 1.5f;
					else if (stageInfoCurFrame - STAGECLEARDELAY_TABREWARD < 15 + 15 + 5)
						menuZoom = Max(1.0f, 1.5f - (float)(stageInfoCurFrame - STAGECLEARDELAY_TABREWARD - 15 - 15) / 10);
					else
						menuZoom = 1.0f;

					if (rewardItem[i].type == ITEM_CREW && crewMenuDraw == false) {
						crewMenuDraw = true;

						startX = xOffset + DX / 2 + 108 * _2X + 40 * _2X / 2 - (float)(40 * _2X) * menuZoom / 2;
						startY = STATUSWIN_Y + JOYSTICKGAP + 83 * _2X + (float)(40 * _2X) * menuZoom / 2;

						DrawImage(40 * _2X, 40 * _2X, 80 * _2X, 0 * _2X, startX, startY, false, false, false, false, 32, menuZoom, sprite[MENUICON_IMG], gScreenBuffer, gScreenLayer, MENUICON_IMG, false);

					}
					else if (equipMenuDraw == false) {
						equipMenuDraw = true;

						startX = xOffset + DX / 2 - 150 * _2X + 40 * _2X / 2 - (float)(40 * _2X) * menuZoom / 2;
						startY = STATUSWIN_Y + JOYSTICKGAP + 83 * _2X + (float)(40 * _2X) * menuZoom / 2;

						DrawImage(40 * _2X, 40 * _2X, 0 * _2X, 0 * _2X, startX, startY, false, false, false, false, false, menuZoom, sprite[MENUICON_IMG], gScreenBuffer, gScreenLayer, MENUICON_IMG, false);
					}

					if (stageInfoCurFrame == STAGECLEARDELAY_GETREWARD - 1) {
						if (rewardItem[i].type == ITEM_CREW)
							boxCardMark[i].targetX2 = xOffset + DX / 2 + 108 * _2X + 20 * _2X;
						else
							boxCardMark[i].targetX2 = xOffset + DX / 2 - 150 * _2X + 20 * _2X;

						boxCardMark[i].targetY2 = STATUSWIN_Y + JOYSTICKGAP + 83 * _2X;

						boxCardMark[i].zoom2 = boxCardMark[i].zoom;
						boxCardMark[i].zoomEnd2 = 1.0f;
						boxCardMark[i].zoomIncrement2 = -0.2f / MOTIONDIV;
						boxCardMark[i].speed2 = 2 * _2X / MOTIONDIV;
						boxCardMark[i].speedIncrement2 = 2 * _2X / MOTIONDIV;
						boxCardMark[i].frame2 = 1;

						GetItem(rewardItem[i].type, rewardItem[i].cooldown, rewardItem[i].detail, rewardItem[i].grade, 1, false);
						PlayMusic(M_CARDSPLIT);

					}
					break;
				case ITEM_BOX:

					break;
					//	//여기서 스킬은 따로 신규 획득 혹은 레벨업을 해준다..
				case ITEM_SKILL:

					break;
				}

			}

			if (getGoldNum > 0 && stageInfoCurFrame == STAGECLEARDELAY_TABREWARD + FPS / 2) {
				AddBar(&bar[BAR_GOLD], getGoldNum, BARFRAME);
				GetItem(ITEM_GOLD, false, false, false, getGoldNum, false);
			}


			if (getHeartNum > 0 && stageInfoCurFrame == STAGECLEARDELAY_TABREWARD + FPS / 2) {
				AddBar(&bar[BAR_BOX], getHeartNum, BARFRAME);
				GetItem(ITEM_HEART, false, false, false, getHeartNum, false);
			}

			if (getMedalNum > 0 && stageInfoCurFrame == STAGECLEARDELAY_TABREWARD + FPS / 2) {
				AddBar(&bar[BAR_MEDAL], getMedalNum, BARFRAME);
				GetItem(ITEM_MEDAL, false, false, false, getMedalNum, false);
			}

			if (getStarNum > 0 && stageInfoCurFrame == STAGECLEARDELAY_TABREWARD + FPS / 2) {
				AddBar(&bar[BAR_CROWN], getStarNum, BARFRAME);
				GetItem(ITEM_STAR, false, false, false, getStarNum, false);
			}

			if (getHammerNum > 0 && stageInfoCurFrame == STAGECLEARDELAY_TABREWARD + FPS / 2) {
				AddBar(&bar[BAR_HAMMER], getHammerNum, BARFRAME);
				GetItem(ITEM_HAMMER, false, false, false, getHammerNum, false);
			}

			//획득된것은 제외하고 당겨준다.
			if (stageInfoCurFrame == STAGECLEARDELAY_GETREWARD - 1) {

				for (i = 0; i < rewardItemCnt; i++) {
					switch (rewardItem[i].type) {
					case ITEM_GOLD:
					case ITEM_HEART:
					case ITEM_MEDAL:
					case ITEM_STAR:
					case ITEM_HAMMER:

					case ITEM_SWORD:
					case ITEM_GUN:
					case ITEM_BOOMERANG:
					case ITEM_HELM:
					case ITEM_HAT:
					case ITEM_CAP:
					case ITEM_ARMOR:
					case ITEM_VEST:
					case ITEM_COAT:
					case ITEM_GUNTLET:
					case ITEM_ARMLET:
					case ITEM_GLOVE:
					case ITEM_KILT:
					case ITEM_SKIRT:
					case ITEM_PANTS:
					case ITEM_GREAVES:
					case ITEM_SHOES:
					case ITEM_BOOTS:
					case ITEM_CREW:
						memset(&rewardItem[i], 0, sizeof(ITEM));
						memset(&boxCardMark[i], 0, sizeof(ICONMARK));
						for (k = i; k < rewardItemCnt - 1; k++) {
							memcpy(&rewardItem[k], &rewardItem[k + 1], sizeof(ITEM));
							memcpy(&boxCardMark[k], &boxCardMark[k + 1], sizeof(ICONMARK));
						}
						memset(&rewardItem[rewardItemCnt - 1], 0, sizeof(ITEM));
						memset(&boxCardMark[rewardItemCnt - 1], 0, sizeof(ICONMARK));
						rewardItemCnt--;
						i--;
						break;
					}
				}

				//rewardItemCnt 가 0보다 크다는 것은 상자가 있다는 것이므로 GotoGacha로 보낸다.
				if (rewardItemCnt > 0)
					GotoGacha();

			}
		}
		else {
			//stageInfoDepth = STAGEINFO_NEWSTAGE;
			stageInfoFrame = 0;
			robin.stage++;
			robin.room = 0;
			if (robin.stage > robin.maxStage[robin.stage]) {
				robin.maxStage[robin.stage] = robin.stage;
				robin.maxRoom[robin.stage] = 0;
			}

			//SetBossObj();

			ClosePopUp();

			memset(&currencyMarkArr_PopUp, 0, sizeof(currencyMarkArr_PopUp));
			memset(&currencyMark_PopUp, 0, sizeof(currencyMark_PopUp));
			memset(&rewardMark_PopUp, 0, sizeof(rewardMark_PopUp));
			memset(&boxMark, 0, sizeof(boxMark));
			memset(&boxCardMark, 0, sizeof(boxCardMark));

			waveStatus = WAVESTATUS_READY;

			SaveGame();
		}
		//가차가 있으면 해당 화면으로 보내주고

		//다 끝나면 종료시켜주면서 다음 스테이지로 이동하고
		break;

	case STAGEINFO_NEWSTAGE:

		DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], cvtDest, cvtLayer, UI_PAPER_POPUP_IMG, buffering);

		//DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom - (float)(DIORAMASIZE_X) / 2 * zoom, y + (float)16 * _2X * zoom, false, false, false, false, false, zoom, sprite[MAP_DIORAMA_IMG + stageHouseType[stage]], cvtDest, cvtLayer, MAP_DIORAMA_IMG + stageHouseType[stage], buffering);

		//세입자
		for (i = MAXCREW - 1; i >= 0; i--) {
			if (enemyHouse.crew[i] != null) {
				switch (stageInfoDepth) {
				case STAGEINFO_NEWSTAGE:
					beforeEnemyCrewY = enemyCrewY;

					enemyCrewY -= stageInfoCurFrame * 16 * _2X;

					if (enemyCrewY < 0)
						enemyCrewY = 0;

					//DrawCmfDetailShadow(enemyData[enemyHouse.crew[i] * ENEMYDATASIZE + ENEMYDATA_CMF], enemyBigIconPos[enemyHouse.crew[i] * 3 + 0], x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom - (float)(DIORAMASIZE_X) / 2 * zoom + (float)stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3] * zoom, y + (float)stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3 + 1] * zoom + (float)8 * _2X + enemyCrewY, stageEnemyPos[stageHouse.houseType * MAXCREW * 3 + i * 3 + 2], enemyZoom[enemyHouse.crew[i]] * dioramaZoom * zoom, cvtDest, cvtLayer, buffering);
					break;
				}
			}

		}

		if (stageInfoCurFrame > 20) {
#ifdef PVPWITHUSER
			DrawPlayer(&ao[SOLDIER], frame / MOTIONDIV % 4, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)DIORAMASIZE_Y * zoom + (float)32 * _2X * zoom, LEFT, 2.0f * zoom * Max(1, FPS / 2 + 10 - stageInfoCurFrame) * 0.6f, false, false, true, cvtDest, cvtLayer, buffering);

#else
			DrawCmfDetailShadow(enemyData[boss[stage] * ENEMYDATASIZE + ENEMYDATA_CMF], crewPos[boss[stage] * 5 + 0] + (FPS / 2 + 10 < stageInfoCurFrame ? frame / 2 / MOTIONDIV : 0) % crewPos[boss[stage] * 5 + 1], x + (float)(POPUPWINDOWSIZE_X - 160 * _2X) / 2 * zoom, y - (float)DIORAMASIZE_Y * zoom + (float)32 * _2X * zoom, LEFT, enemyZoom[boss[stage]] * enemyBossZoom[boss[stage]] * zoom * Max(1, FPS / 2 + 10 - stageInfoCurFrame) * 0.6f, cvtDest, cvtLayer, buffering);
#endif
		}

		if (stageInfoCurFrame > 23) {
#ifdef PVPWITHUSER
			DrawLabel(x + (float)(POPUPWINDOWSIZE_X - 88 * _2X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X) * zoom, false, zoom, cvtDest, cvtLayer, buffering);
			CenterText(TEXT_NICKNAME + 4, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X + 10 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
#else
			//DrawImage(207, 33, 0, 953, x + (float)(POPUPWINDOWSIZE_X - 64 * _2X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X + 6 * _2X) * zoom, false, false, false, false, false, 1.5f * zoom, sprite[THEATER_IMG], cvtDest, cvtLayer, THEATER_IMG, buffering);
			//MemRect(x + (float)(POPUPWINDOWSIZE_X - 15 * _2X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X + 12 * _2X) * zoom, (float)(HPBARWIDTH * 1.5f / 2 * robin.bossObj.hp / robin.bossObj.maxhp)* zoom, (float)(HPBARHEIGHT * 1.5f / 2)* zoom, ENEMYHPBARCOLOR, cvtDest, cvtLayer, buffering);
			//DrawNum(robin.bossObj.hp, x + (float)(POPUPWINDOWSIZE_X - 15 * _2X + (float)HPBARWIDTH * 1.5f - 8 * _2X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X + 12 * _2X) * zoom, NUM_FONT_NORMAL, RIGHT, 0, count >= 0 ? false : MINUS, true, zoom, cvtDest, cvtLayer, buffering);
			//DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, x + (float)(POPUPWINDOWSIZE_X - 15 * _2X + (float)HPBARWIDTH * 1.5f - 8 * _2X) / 2 * zoom - GetNumDx(robin.bossObj.hp, 0, NUM_FONT_NORMAL, 0, true, zoom) - (float)(ITEMICONSIZE * 0.8f + 4 * _2X) * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X + 11 * _2X) * zoom, 0.8f * zoom, false, false, false, cvtDest, cvtLayer, buffering);
			HpBarDraw(boss[robin.stage], robin.totalBossHp, robin.totalBossMaxHp, x + (float)(POPUPWINDOWSIZE_X - 16 * _2X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X + 10 * _2X) * zoom, 0.8f * zoom, cvtDest, cvtLayer, buffering);

			DrawLabel(x + (float)(POPUPWINDOWSIZE_X - 88 * _2X - 160 * _2X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X) * zoom, TEXT_STAGENAME + stage/*TEXT_MONSTERNAME_START + boss[stage]*/, zoom, cvtDest, cvtLayer, buffering);
#endif
		}

		if (stageInfoCurFrame > 26) {
#ifdef PVPWITHUSER
			CenterAlpha(x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X) * zoom, ALPHA_USERINFO, FONT_SMALL, false, zoom, cvtDest, cvtLayer, buffering);
#else
			CenterAlpha(x + (float)(POPUPWINDOWSIZE_X - 160 * _2X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X) * zoom, ALPHA_BOSS, FONT_SMALL, false, zoom, cvtDest, cvtLayer, buffering);

#endif
		}

		if (stageInfoCurFrame > 30) {
			SetAlpha(28);
			GradiationFrame(x + (float)(POPUPWINDOWSIZE_X - 280 * _2X) / 2 * zoom, y - (float)(200 * _2X) * zoom, (float)280 * _2X * zoom, (float)24 * _2X * zoom, 0, cvtDest, cvtLayer, buffering);
			SetAlpha(32);
		}

		if (stageInfoCurFrame > 33)
			CenterText(TEXT_RAIDGOLD, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)(200 * _2X + 7 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

		if (stageInfoCurFrame > 36)
			DrawFrame(x + (float)(POPUPWINDOWSIZE_X - 256 * _2X) / 2 * zoom, y - (float)(200 * _2X + 26 * _2X) * zoom, (float)256 * _2X * zoom, (float)RAIDGOLDBARHEIGHT * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);

		if (stageInfoCurFrame > 39) {

			width = (float)(ITEMICONSIZE * 1.5f + 4 * _2X) * goldZoom + GetBigNumGoldDx(betCnt, false, FONT_GOLD_LARGE, false, true, (float)(256 * _2X - 32 * _2X) * zoom, goldZoom);

			DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom - width / 2, y - (float)(200 * _2X + 24 * _2X) * zoom - (float)8 * _2X * zoom, 1.5f * goldZoom, false, false, false, true, cvtDest, cvtLayer, buffering);

			DrawBigNumGold(betCnt, x + (float)POPUPWINDOWSIZE_X / 2 * zoom - width / 2 + (float)(ITEMICONSIZE * 1.5f + 4 * _2X) * zoom, y - (float)(200 * _2X + 24 * _2X) * zoom - (float)8 * _2X * zoom, FONT_GOLD_LARGE, LEFT, false, false, (float)(240 * _2X - 32 * _2X) * goldZoom, true, goldZoom, cvtDest, cvtLayer, buffering);
		}

		if (stageInfoCurFrame > 45) {
			SetAlpha(28);
			GradiationFrame(x + (float)(POPUPWINDOWSIZE_X - 280 * _2X) / 2 * zoom, y - (float)(260 * _2X) * zoom, (float)(280 * _2X) * zoom, (float)(24 * _2X) * zoom, 0, cvtDest, cvtLayer, buffering);
			SetAlpha(32);
		}

		if (stageInfoCurFrame > 48)
			CenterText(TEXT_RENT, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)(260 * _2X + 7 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

		//if (stageInfoCurFrame > 51)
		//	DrawWindow2(x + (float)(8 * _2X) * zoom, y - (float)(284 * _2X) * zoom, (float)(POPUPWINDOWSIZE_X - 16 * _2X), (float)(188 * _2X), COLOR_WHITE, zoom, cvtDest, cvtLayer, buffering);


		for (i = 0; i < MAXCREW; i++) {
			if (enemyHouse.crew[i] != null) {
				if (stageInfoCurFrame > 54 + i * 3) {

					detail = enemyHouse.crew[i];

					curStar = enemyHouse.crewCurStar[i];
					curMaxStar = enemyHouse.crewMaxStar[i];
					maxStar = crewData[detail * CREWDATASIZE + CREWDATASIZE - 1] + 1;
					signed long long upgradePrice = crewStarUpgradeGold[stage * MAXCREW * CREWMAXUPGRADELV + i * (CREWMAXUPGRADELV)+curStar] / CREWUPGRADEPER;

					//DrawRewardCard(ITEM_CREW, detail, GRADE_NORMAL, 1, 1, x + (float)(14 * _2X) * zoom, y - (float)(298 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 8 * _2X) * i * 1.2f * zoom, false, 1.2f * zoom, false, false, false, curStar, maxStar, cvtDest, cvtLayer, buffering);

					//DrawBuyButton(x + (float)(14 * _2X) * zoom + (float)50 * _2X * zoom, y - (float)(298 * _2X + 16 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 8 * _2X) * i * 1.2f * zoom, (float)(160 * _2X) * zoom, (float)(32 * _2X) * zoom, frame, false, 100000000, CURRENCY_GOLD, zoom, false, false, false, cvtDest, cvtLayer, buffering);

					//DrawRewardCard(ITEM_CREW, detail, GRADE_NORMAL, 1, 1, x + (float)(10 * _2X) * zoom + (float)(POPUPWINDOWSIZE_X - 30 * _2X) / 2 * (i % 2) * zoom, y - (float)(298 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 8 * _2X) * (i / 2) * 1.2f * zoom, false, 1.2f * zoom, false, false, false, curStar, maxStar, cvtDest, cvtLayer, buffering);

					if (stageUpgradeMotion[i] > 0 && stageUpgradeMotion[i] < 11) {
						ao[NPC].cmf = ao[NPC].type = ROBIN;
						ao[NPC].x = x + (float)(36 * _2X) * zoom + (float)(POPUPWINDOWSIZE_X - 30 * _2X) / 2 * (i % 2) * zoom;
						ao[NPC].y = y - (float)(336 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 6 * _2X) * (i / 2) * 1.2f * zoom;
						DrawPlayer(&ao[NPC], 2000 - 1 + LEVELUP_BACK0 + stageUpgradeMotion[i], ao[NPC].x, ao[NPC].y, false, zoom, false, false, false, cvtDest, cvtLayer, buffering);

					}
					DrawCmfDetailShadow(enemyData[enemyHouse.crew[i] * ENEMYDATASIZE + ENEMYDATA_CMF], enemyBigIconPos[enemyHouse.crew[i] * 3 + 0], x + (float)(36 * _2X) * zoom + (float)(POPUPWINDOWSIZE_X - 30 * _2X) / 2 * (i % 2) * zoom, y - (float)(336 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 6 * _2X) * (i / 2) * 1.2f * zoom, RIGHT, enemyZoom[enemyHouse.crew[i]] * zoom, cvtDest, cvtLayer, buffering);


					DrawStar(ICON_CROWN, x + (float)(12 * _2X) * zoom + (float)(POPUPWINDOWSIZE_X - 30 * _2X) / 2 * (i % 2) * zoom + (float)90 * _2X * zoom, y - (float)(296 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 6 * _2X) * (i / 2) * 1.2f * zoom, curStar, curMaxStar, maxStar, CENTER, true, zoom, cvtDest, cvtLayer, buffering);
					//최대값에 도달하면
					if (curStar == maxStar) {
						DrawMaxButton(x + (float)(12 * _2X) * zoom + (float)(POPUPWINDOWSIZE_X - 30 * _2X) / 2 * (i % 2) * zoom + (float)48 * _2X * zoom, y - (float)(292 * _2X + 20 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 6 * _2X) * (i / 2) * 1.2f * zoom, (float)(96 * _2X) * zoom, (float)(32 * _2X) * zoom, ALPHA_MAX, zoom, cvtDest, cvtLayer, buffering);
					}
					else {
						DrawBuyButton(x + (float)(12 * _2X) * zoom + (float)(POPUPWINDOWSIZE_X - 30 * _2X) / 2 * (i % 2) * zoom + (float)48 * _2X * zoom, y - (float)(292 * _2X + 20 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 6 * _2X) * (i / 2) * 1.2f * zoom, (float)(96 * _2X) * zoom, (float)(32 * _2X) * zoom, frame, robin.gold < upgradePrice ? true : false, upgradePrice, CURRENCY_GOLD, zoom, false, false, false, cvtDest, cvtLayer, buffering);
						if (robin.gold >= upgradePrice)
							SetRectPoint(x + (float)(12 * _2X) * zoom + (float)(POPUPWINDOWSIZE_X - 30 * _2X) / 2 * (i % 2) * zoom + (float)48 * _2X * zoom, y - (float)(292 * _2X + 20 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 6 * _2X) * (i / 2) * 1.2f * zoom, (float)(96 * _2X) * zoom, (float)(32 * _2X) * zoom, TOUCH_FUNC_CREWUPGRADE + i);
					}

					if (stageUpgradeMotion[i] > 0 && stageUpgradeMotion[i] < 11) {
						DrawPlayer(&ao[NPC], 2000 - 1 + LEVELUP_FRONT0 + stageUpgradeMotion[i], ao[NPC].x, ao[NPC].y, false, zoom, false, false, false, cvtDest, cvtLayer, buffering);

						DrawEffect(EFFECT_LEVELUP_TEXT0 - 1 + (stageUpgradeMotion[i] < 11 ? stageUpgradeMotion[i] : Max(11, stageUpgradeMotion[i] - 5)), ao[NPC].x, ao[NPC].y - (float)(16 * _2X) * zoom, 0, false, 1.0f, cvtDest, cvtLayer, buffering);

					}

					if (stageUpgradeMotion[i] == 3)
						PlayMusic(M_LEVELUP);

					if (stageUpgradeMotion[i] > 0)
						stageUpgradeMotion[i]++;

					if (stageUpgradeMotion[i] == 11)
						stageUpgradeMotion[i] = 0;

				}

			}
		}

		for (i = 0; i < MAXCREW; i++) {
			if (enemyHouse.crew[i] != null) {
				curStar = enemyHouse.crewCurStar[i];

				totalStar += curStar;
			}
		}
		if (stageInfoCurFrame > 54 + MAXCREW * 3) {
			//성주와 일기토
			DrawTextButton(x + (float)(DX / 2 - 0 * _2X) * zoom, y - (float)(416 * _2X) * zoom, (float)(120 * _2X) * zoom, (float)(48 * _2X) * zoom, frame, totalStar < 10 || robin.bossRoom == true ? true : false, 1.0f, false, TEXT_LORD_DUEL, cvtDest, cvtLayer, buffering);
			//if (totalStar < MAXSTARPERHOUSE || robin.bossRoom == true)
			//	grayScale = 32;
			DrawGoldAlpha(x + (float)(DX / 2 - 0 * _2X + 120 * _2X / 2) * zoom, y - (float)(416 * _2X + 22 * _2X) * zoom, ALPHA_BOSSDUEL, FONT_GOLD_LARGE, (float)zoom * 0.7f, CENTER, false, false, cvtDest, cvtLayer, buffering);
			grayScale = 0;
			//if (totalStar == MAXSTARPERHOUSE && robin.bossRoom == false)
			//	SetRectPoint(x + (float)(DX / 2 - 0 * _2X) * zoom, y - (float)(416 * _2X) * zoom, (float)(120 * _2X) * zoom, (float)(48 * _2X) * zoom, TOUCH_FUNC_GOTOSTAGEBOSS);
		}

		BarDraw(&bar[BAR_GOLD], bar[BAR_GOLD].zoom, cvtDest, cvtLayer, buffering);

		//뉴스테이지에 대한 내용이 뜨고
		fontZoom = Max(1.2f, (float)(54 + MAXCREW * 3 + FPS / 2 - stageInfoCurFrame) * 0.2f / MOTIONDIV);

		if (stageInfoCurFrame > 54 + MAXCREW * 3)
			DrawGoldAlpha(DX / 2, DY / 2 + 248 * _2X, ALPHA_NEWSTAGE, FONT_GOLD_LARGE, fontZoom, CENTER, true, false, gScreenBuffer, gScreenLayer, false);

		//게임으로 돌아간다.

		if (stageInfoCurFrame == 54 + MAXCREW * 3 + FPS * 3) {
			robin.bossRoom = false;
			memset(&robin.enemyObj, 0, sizeof(robin.enemyObj));
			robinmap = dioramaMap[robin.stage];
			GotoPlay();
			initControlerFrame = 1;
			for (i = 0; i < TOTALCONTROLMARK; i++)
				controlerSpread[i] = true;
		}
		break;
	}

	switch (stageInfoDepth) {
	case STAGEINFO_CREWDROP:
		break;
	case STAGEINFO_CREWGACHA:

		break;
	}


	//현재 타겟팅되는 하우스


	if (cur == true)
		stageInfoFrame++;
}

void CrewListDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i;

	for (i = 0; i < TOTALCASTLE; i++)
		CrewSetDraw(i, x, y + POPUPPOSITION_Y - GNBHEIGHT - CREWSET_YGAP * (i), zoom, cvtDest, cvtLayer, buffering);

	DrawScroll((float)(DX - 8 * _2X * zoom), GNBHEIGHT, (float)8 * _2X * zoom, MENU_CREW, cvtDest, cvtLayer, buffering);
}
