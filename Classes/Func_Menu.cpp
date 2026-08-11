#pragma once
#include "Core.h"
#include "Func.h"
#include "Text.h"
#include "Data.h"

// Menu & UI ∞¸∑√ «‘ºˆ
//¥∫Ω∫ µÂ∑ŒøÏ
void NewsDraw(int x, int y, float zoom)
{
	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

}
//º±π∞«‘ µÂ∑ŒøÏ
void GiftDraw(int x, int y, float zoom)
{
	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

}

//ƒ£±∏øÕ¿« ¿¸≈ı µÂ∑ŒøÏ
void GuildEventDraw(int x, int y, float zoom)
{
	int i, j, tempIdx, mul = 1;
	int week = 0;
	int dayOfWeek = 1;
	int dayOfMonth = robin.calendarMonthDay;

	DrawImage((float)POPUPWINDOWSIZE_X * zoom, (float)(POPUPWINDOWSIZE_Y)*zoom, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

	switch (menuDepth) {

	case 0:
		//ø©±‚º≠¥¬ ±◊≥… ∏ÆΩ∫∆Æ∏¶ ±◊∑¡¡ÿ¥Ÿ.
		//«œ∑Áø° ºº∞°¡ˆ
		for (i = 0; i < 3; i++) {
			MemRectRound(x + (float)(32 * _2X) * zoom, y - (float)(48 * _2X + 80 * _2X * i) * zoom, (float)(256 * _2X) * zoom, (float)(72 * _2X) * zoom, COLOR_BROWN, 2);

			//DrawFrame(x + (float)32 * _2X * zoom, y - (float)(48 * _2X + 80 * _2X * i) * zoom, (float)256 * _2X * zoom, (float)72 * _2X * zoom, COLOR_LIGHTBROWN, )
		}
	case 1:
		//ø©±‚º≠ ∞¢¡æ »πµÊ ¿Ã∆Â∆Æ∏¶ ±◊∑¡¡ÿ¥Ÿ.

		break;
	}


	//«ˆ¿Á µ•¿œ∏Æ ¿Ã∫•∆Æ±Ó¡ˆ ≥≤¥¬ Ω√∞£
	DrawTime(x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y + (float)(-440 * _2X) * zoom, Max(0, 86400 - (MC_knlCurrentTimeStamp() - robin.calendarTimeStamp)), TIME_HOUR_MINUTE, CENTER, zoom);


}

void DailyQuestDraw(int x, int y, float zoom)
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


	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

	switch (menuDepth) {

	case 0:
		//ø©±‚º≠¥¬ ±◊≥… ∏ÆΩ∫∆Æ∏¶ ±◊∑¡¡ÿ¥Ÿ.
		//«œ∑Áø° ºº∞°¡ˆ
		for (i = 0; i < 3; i++) {
			//for (i = 0; i < TOTAL_DAILYQUEST_TYPE; i++) {
			MemRectRound(x + (float)(20 * _2X) * zoom, y - (float)(64 * _2X + 72 * _2X * i) * zoom, (float)(280 * _2X) * zoom, (float)(64 * _2X) * zoom, COLOR_BEIGE, 2 * _2X);

			dailyQuestType = i;

			switch (i) {
				//ªÛ¿⁄∏¶ ø≠æÓº≠ ¿Â∫Ò∏¶ æÚæÓ∂Û
			case DAILYQUEST_OPEN_BOX_GETEQUIP:
				//ªÛ¿⁄∏¶ ø©ººø‰
				DrawNeutral(OBJ_BOX0 + boxOpenAnimation[((frame / (MOTIONDIV * 2)) % 20)], x + (float)(20 * _2X + 32 * _2X) * zoom, y - (float)(64 * _2X + 60 * _2X + 72 * _2X * i) * zoom, LEFT, 2.0f * zoom);
				if (frame / (MOTIONDIV) % 40 > 16/* && ((frame / (MOTIONDIV * 2)) % 20) < 16*/) {
					boxOpenFrame = ((frame / (MOTIONDIV)) % 40) - 16;

					for (j = 0; j < 3; j++)
						DrawIcon(GetItemIcon(boxOpenItemFrameInfo[boxOpenFrame * 3 * BOXOPENITEMFRAMEINFOSIZE + BOXOPENITEMFRAMEINFOSIZE * j + 0], boxOpenItemFrameInfo[boxOpenFrame * 3 * BOXOPENITEMFRAMEINFOSIZE + BOXOPENITEMFRAMEINFOSIZE * j + 1], boxOpenItemFrameInfo[boxOpenFrame * 3 * BOXOPENITEMFRAMEINFOSIZE + BOXOPENITEMFRAMEINFOSIZE * j + 2]), x + (float)(20 * _2X + 32 * _2X) * zoom + (float)boxOpenItemFrameInfo[boxOpenFrame * 3 * BOXOPENITEMFRAMEINFOSIZE + BOXOPENITEMFRAMEINFOSIZE * j + 3] * zoom, y - (float)(64 * _2X + 60 * _2X + 72 * _2X * i) * zoom + (float)boxOpenItemFrameInfo[boxOpenFrame * 3 * BOXOPENITEMFRAMEINFOSIZE + BOXOPENITEMFRAMEINFOSIZE * j + 4] * zoom, (float)boxOpenItemFrameInfo[boxOpenFrame * 3 * BOXOPENITEMFRAMEINFOSIZE + BOXOPENITEMFRAMEINFOSIZE * j + 5] * zoom, COLOR_WHITE, true, true, 1);
				}

				break;
				//±π∞Êºˆ∫Ò¥Î∏¶ æ˜±◊∑π¿ÃµÂ∏¶ «ÿ∂Û
			case DAILYQUEST_UPGRADE_CREW:
				ao[NPC].x = x + (float)(28 * _2X + 24 * _2X) * zoom;
				ao[NPC].y = y - (float)(52 * _2X * NPCZOOM + 72 * _2X * i) * zoom - (float)(8 * _2X + 24 * _2X) * NPCZOOM * zoom;

				DrawImage(32 * _2X, 12 * _2X, 107 * _2X, 48 * _2X, ao[NPC].x - (float)16 * _2X * NPCZOOM * zoom, ao[NPC].y + (float)(2 * _2X) * NPCZOOM * zoom, false, false, false, false, false, NPCZOOM * zoom, sprite[MAP_OBJ_IMG + 6], MAP_OBJ_IMG + 6);

				DrawCmfDetailShadow(enemyData[crewData[(robin.stage * MAXCREW + MAXCREW - 1) * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_CMF], crewPos[enemyData[crewData[(robin.stage * MAXCREW + MAXCREW - 1) * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_CMF]], ao[NPC].x, ao[NPC].y, RIGHT, enemyIconZoom[crewData[(robin.stage * MAXCREW + MAXCREW - 1) * CREWDATASIZE]] * NPCZOOM * zoom);
				break;
				//¥Ÿ∏• ¿Ø¿˙∏¶ ∞¯∞›«ÿ∂Û
			case DAILYQUEST_ATTACK_OTHERUSER:
				EnemyUserProfileDraw(&enemyHouse, x + (float)(20 * _2X + 28 * _2X - 20 * _2X) * zoom, y - (float)(58 * _2X + 72 * _2X * i) * zoom, zoom);
				break;
			case DAILYQUEST_COLLECT_GOLD:
				DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, x + (float)(20 * _2X + 12 * _2X) * zoom, y - (float)(80 * _2X + 72 * _2X * i) * zoom, 2.5f * zoom, false, false, false, 1);
				break;
			case DAILYQUEST_STAGE_TRY:
				DrawBox(stageClearBox[robin.stage], x + (float)(20 * _2X + 32 * _2X + 24 * _2X) * zoom, y - (float)(64 * _2X + 60 * _2X + 72 * _2X * i) * zoom, LEFT, boxNeutralAnimation[((frame / (MOTIONDIV * 2 * 2)) % 4)], COLOR_WHITE, true, false, true, 1.2f * zoom / 1.2f);

				DrawCmfDetailShadow(enemyData[stageBossType * ENEMYDATASIZE + ENEMYDATA_CMF], crewPos[stageBossType * 5 + 0] + (frame / 2 % crewPos[stageBossType * 5 + 1]), x + (float)(20 * _2X + 28 * _2X) * zoom, y - (float)(64 * _2X + 60 * _2X + 72 * _2X * i) * zoom, LEFT, /*enemyIconZoom[stageBossType] **/ zoom / 1.2f);

				DrawStageLabel(x + (float)(20 * _2X + 28 * _2X) * zoom, y - (float)(64 * _2X + 60 * _2X - 60 * _2X + 72 * _2X * i) * zoom, TEXT_STAGE, robin.stage, robin.room, true, zoom / 1.2f);

				break;

			}
			//DrawFrame(x + (float)(32 * _2X + 28 * _2X + 48 * _2X) * zoom, y - (float)(64 * _2X + 32 * _2X + 72 * _2X * i) * zoom, float(DAILYQUESTBARWIDTH) * zoom, float(DAILYQUESTBARHEIGHT) * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
			DrawText(TEXT_DAILYQUEST_OPEN_BOX_GETEQUIP + i, x + (float)(20 * _2X + 32 * _2X + 40 * _2X) * zoom, y - (float)(64 * _2X + 12 * _2X + 72 * _2X * i) * zoom, zoom);
			DrawGuage(x + (float)(20 * _2X + 28 * _2X + 40 * _2X) * zoom, y - (float)(64 * _2X + 32 * _2X + 72 * _2X * i) * zoom, float(DAILYQUESTBARWIDTH) * zoom, float(DAILYQUESTBARHEIGHT) * zoom, 10, 30, COLOR_NAVY, COLOR_HEARTBAR, zoom);
			DrawRewardCard(i, i, i, false, 1, x + (float)(20 * _2X + 28 * _2X + 204 * _2X) * zoom, y - (float)(64 * _2X + 4 * _2X + 72 * _2X * i) * zoom, false, zoom, true, false, true, GetItemStar(i, i, i), GetItemStar(i, i, i), true, 0);
		}
	case 1:
		//ø©±‚º≠ ∞¢¡æ »πµÊ ¿Ã∆Â∆Æ∏¶ ±◊∑¡¡ÿ¥Ÿ.

		break;
	}


	//«ˆ¿Á µ•¿œ∏Æ ¿Ã∫•∆Æ±Ó¡ˆ ≥≤¥¬ Ω√∞£
	DrawTime(x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y + (float)(-440 * _2X) * zoom, Max(0, 86400 - (MC_knlCurrentTimeStamp() - robin.calendarTimeStamp)), TIME_HOUR_MINUTE, CENTER, zoom);

}


void ShopDraw_Back(int x, int y)
{
	int i;
	ITEM* it;

	switch (menuDepth) {
	case 0:
		switch (menuIdx) {
		default:

			MemRectRound(x, y, DX, DY, 0x1D2B47, 1 * _2X);
			DrawBackMap_Back(x, DY / 2 - 320 * _2X / 2, TOLEMHOUSE2, 1.0f);

			break;
		}
		break;
	case 1:
		break;
	case 2:
		break;
	}
}

//∫∞ µÂ∑ŒøÏ
void StarShopDraw(int x, int y)
{
	DrawCmfPopUp(CMF_NPC_USERQUEST, TEXT_MENU_STARSHOP, x, y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, DX - 120 * _2X, 6, 1, 1.0f);


}


void HeroDraw(int type, int x, int y, int dirX, float zoom)
{
	OBJECT* pObj = &ao[PLAYER];

	if (IsGetHero(type) == false)
		grayScale = 32;
	EnemyProfileDraw(x, y, type, false, (drawHandle == MD_PLAY ? ao[type].lv : false), 1.0f * zoom);

	//DrawPlayer(&ao[type], IsGetHero(type) == false ? 0 : frame / 2 % 4, x, y, dirX, HOUSEZOOM * zoom, false, false, true, cvtDest, cvtLayer, buffering);
	grayScale = 0;
	if (IsGetHero(type) == false) {
		DrawLock(getHeroLv[type], x + (float)(+(2 * _2X)) * zoom, y - (float)2 * _2X * zoom, 2.0f * zoom);
	}

}

void HeroListDraw(int x, int y, float zoom, bool checkBox, int gap)
{
	int i;
	OBJECT* pObj = &ao[PLAYER];

	//DrawFrame(x, y - (float)8 * _2X * zoom, (float)140 * _2X * zoom, (float)64 * _2X * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);

	for (i = 1; i < MAXPLAYER; i++) {
		//DrawFrame(x + (float)8 * _2X * zoom + (gap * (i - 1)) * zoom, y - (float)24 * _2X * zoom, (float)32 * _2X * zoom, (float)32 * _2X * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);

		//SetSectionClip(x + (float)8 * _2X + (gap * (i - 1)) * zoom, y - (float)24 * _2X * zoom, (float)32 * _2X * zoom, (float)32 * _2X * zoom, false);
		HeroDraw(i, x + (float)0 * _2X + (gap * (i - 1)) * zoom, y - (float)24 * _2X * zoom, LEFT, zoom);
		//UnSectionClip(false);
	}

	if (drawHandle == MD_PLAY || drawHandle == MD_BATTLE)
		DrawLabel(x + (float)(14 * _2X) * zoom, y - (float)(68 * _2X) * zoom, TEXT_ALPHA_HEROES, 0.72f * zoom);

}


void HeroSelectButtonList(int x, int y, float zoom, int selected, bool touchActive, bool horizontal)
{
	int i;

	if (horizontal == true) {
		for (i = 0; i < TOTALCHAR; i++) {
			DrawFrame(x + i * (float)(HEROBUTTON_X + 4 * _2X) * zoom, y + (selected == i ? (float)4 * _2X * zoom : 0), (float)HEROBUTTON_X * zoom, (float)HEROBUTTON_Y * zoom, FRAME_SHOPBALLOON);
			DrawPlayer(&ao[i], (i == selected ? frame / 4 % 4 : 0), x + i * (float)(HEROBUTTON_X + 4 * _2X) * zoom + (float)(HEROBUTTON_X / 2) * zoom, y + (selected == i ? (float)4 * _2X * zoom : 0) - (float)(HEROBUTTON_Y - 8 * _2X) * zoom, RIGHT, zoom, false, false, true);
			if (i != selected && touchActive == true)
				SetRectPoint(x + i * (float)(HEROBUTTON_X + 4 * _2X) * zoom, y + (selected == i ? (float)4 * _2X * zoom : 0), (float)HEROBUTTON_X * zoom, (float)HEROBUTTON_Y * zoom, TOUCH_FUNC_SELECT_HERO + i);
		}
	}
	else {
		for (i = 0; i < TOTALCHAR; i++) {
			DrawFrame(x - (selected == i ? (float)4 * _2X * zoom : 0), y - i * (float)(HEROBUTTON_Y + 8 * _2X) * zoom, (float)HEROBUTTON_X * zoom, (float)HEROBUTTON_Y * zoom, FRAME_SHOPBALLOON);
			DrawPlayer(&ao[i], (i == selected ? frame / 4 % 4 : 0), x - (selected == i ? (float)4 * _2X * zoom : 0) + (float)(HEROBUTTON_X / 2) * zoom, y - i * (float)(HEROBUTTON_Y + 8 * _2X) * zoom - (float)(HEROBUTTON_Y - 8 * _2X) * zoom, LEFT, zoom, false, false, true);
			if (i != selected && touchActive == true)
				SetRectPoint(x - (selected == i ? (float)4 * _2X * zoom : 0), y - i * (float)(HEROBUTTON_Y + 8 * _2X) * zoom, (float)HEROBUTTON_X * zoom, (float)HEROBUTTON_Y * zoom, TOUCH_FUNC_SELECT_HERO + i);
		}
	}
}

void HeroStatDraw(OBJECT* pObj, int x, int y, float zoom)
{
	int i;
	float plusX = (float)(12 * _2X) * zoom;
	float plusY = (float)(-52 * _2X) * zoom;
	const signed short* usPtr;
	//»˜æÓ∑Œ Ω∫≈»¿ª ±◊∑¡¡ÿ¥Ÿ.
	//DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], cvtDest, cvtLayer, UI_PAPER_POPUP_IMG, false);

	//DrawPlayer(pObj, PO_C0_N0 + (frame / 2 / MOTIONDIV % 4), x + (float)32 * _2X * zoom, y - (float)54 * _2X * zoom, RIGHT, zoom * 2.0f, false, false, true, cvtDest, cvtLayer, buffering);

	//BarDraw(&bar[BAR_GOLD], zoom, cvtDest, cvtLayer, buffering);

	HeroSelectButtonList(x + (float)(4 * _2X) * zoom, DY - (float)8 * _2X * zoom, zoom, curHero, menuDepth == 0 ? true : false, true);

	BarDraw(&bar[BAR_COMBATPOWERALL], zoom);

	for (i = TOTALEQUIP - 1; i >= 0; i--) {
		usPtr = &equipSlotPos2[i * 4];

		if (pObj->equip[*usPtr].type < EMPTY) {
			if (pObj->equipImg[*usPtr] == 0)
				grayScale = 20;

			DrawItemIcon(&pObj->equip[*usPtr], pObj, x + plusX + (float)*(usPtr + 2) * zoom, y + plusY + (float)*(usPtr + 3) * zoom, zoom * 2);

			MemRectFrameThick(x + plusX + (float)*(usPtr + 2) * zoom - (float)2 * _2X * zoom, y + plusY + (float)*(usPtr + 3) * zoom + (float)2 * _2X * zoom, (float)(ITEMICONSIZE * 2 + 4 * _2X) * zoom, (float)(ITEMICONSIZE * 2 + 4 * _2X) * zoom, itemColor[pObj->equip[*usPtr].grade], (float)1 * _2X * zoom);

			if (*usPtr == EQUIP_RING && pObj->equip[EQUIP_RING].cooldown)
				DrawCycle(x + plusX + (float)*(usPtr + 2) * zoom, y + plusY + (float)*(usPtr + 3) * zoom, (float)16 * _2X * 2 * zoom, (float)16 * _2X * 2 * zoom, pObj->equip[EQUIP_RING].cooldown, ringOption[pObj->equip[EQUIP_RING].detail * 7 + 3 + Min(3, pObj->equip[EQUIP_RING].grade)] * 120, zoom);

			if (pObj->equipImg[*usPtr] == 0) {
				grayScale = 0;
				SetAlpha(8);
				MemRect(x + plusX + (float)*(usPtr + 2) * zoom, y + plusY + (float)*(usPtr + 3) * zoom, (float)16 * _2X * 2 * zoom, (float)16 * _2X * 2 * zoom, 0xFF0000);
				SetAlpha(32);
			}
		}

		if (hotKeyFrame && hotKeyFrame / 10 == *usPtr + 10) {
			DrawEffect(EFFECT_SLOT0 + 7 - (hotKeyFrame % 10), x + plusX + (float)*(usPtr + 2) * zoom + (float)8 * _2X * 2 * zoom, y + plusY + (float)*(usPtr + 3) * zoom - (float)8 * _2X * 2 * zoom, LEFT, false, zoom);
			hotKeyFrame--;

			if (hotKeyFrame % 10 == 0)
				hotKeyFrame = 0;
		}
	}

	DrawFrame(x + (float)32 * _2X * zoom, y + plusY - (float)35 * _2X * zoom, (float)(POPUPWINDOWSIZE_X - 64 * _2X) * zoom, (float)120 * _2X * zoom, FRAME_NOFRAME);

	//DrawText()
	//HP, MP, EXP ∫Œ∫–
	//hp
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s  %lld  /  %lld", textId[TEXT_ALPHA_HP], pObj->hp, pObj->ps[PS_HP]);
	DrawTextStr(tempStr, x + (float)40 * _2X * zoom, y + plusY - (float)40 * _2X * zoom, zoom);

	//√— ∞¯∞›ºˆƒ°
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s  %lld  -  %lld", textId[TEXT_ALPHA_DAMAGE], RoundDiv(pObj->ps[PS_DMG] * (100 - weaponRange[pObj->equip[EQUIP_WEAPON].type]), 100), RoundDiv(pObj->ps[PS_DMG] * (100 + weaponRange[pObj->equip[EQUIP_WEAPON].type]), 100));
	DrawTextStr(tempStr, x + (float)40 * _2X * zoom, y + plusY - (float)55 * _2X * zoom, zoom);

	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s  %lld", textId[TEXT_ALPHA_DEFENSE], pObj->ps[PS_ARMOR]);
	DrawTextStr(tempStr, x + (float)40 * _2X * zoom, y + plusY - (float)70 * _2X * zoom, zoom);


	//STR
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s  %lld", textId[TEXT_ALPHA_STR], pObj->ps[PS_STR]);
	DrawTextStr(tempStr, x + (float)40 * _2X * zoom, y + plusY - (float)85 * _2X * zoom, zoom);

	//VIT
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s  %lld", textId[TEXT_ALPHA_VIT], pObj->ps[PS_VIT]);
	DrawTextStr(tempStr, x + (float)(40 + 108) * _2X * zoom, y + plusY - (float)85 * _2X * zoom, zoom);

	//AGI
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s  %lld", textId[TEXT_ALPHA_AGI], pObj->ps[PS_AGI]);
	DrawTextStr(tempStr, x + (float)40 * _2X * zoom, y + plusY - (float)100 * _2X * zoom, zoom);

	//INT
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s  %lld", textId[TEXT_ALPHA_INT], pObj->ps[PS_INT]);
	DrawTextStr(tempStr, x + (float)(40 + 108) * _2X * zoom, y + plusY - (float)100 * _2X * zoom, zoom);

	DrawTextStr(textId[TEXT_ATTRREGIST], x + (float)40 * _2X * zoom, y + plusY - (float)115 * _2X * zoom, 1.2f * zoom);

	//¿˙«◊µµ
	for (i = 5 - 1; i >= 0; i--) {
		DrawArray(IMG_FLAME + i, x + (float)(40 * _2X + 48 * _2X * i) * zoom, y + plusY - (float)134 * _2X * zoom, 2.0f * zoom);
		DrawNum(pObj->ps[PS_FIRE + i], x + (float)(40 * _2X + 24 * _2X + 48 * _2X * i) * zoom, y + plusY - (float)136 * _2X * zoom, NUM_FONT_NORMAL, LEFT, false, false, true, zoom, false);
	}

	memset(optionStr, 0, sizeof(optionStr));

	for (i = 0; i < TOTALMENUOPTION; i++) {
		sprintf(optionStr[i], TEXTPTR(TEXT_PREFIX_DESC + optionInfo[i * 2 + 1]), Abs(pObj->ps[optionInfo[i * 2]]));

	}

	for (i = 0; i < TOTALMENUOPTION; i++)
		DrawTextStr(optionStr[i], x + (float)(24 * _2X + 160 * _2X * (i % 2)) * zoom, y + plusY - (float)(162 * _2X + 15 * _2X * (i / 2)) * zoom, zoom);
}

void ItemDetailDraw(ITEM* it, int x, int y, float zoom, bool equipped, bool onlyInfo)
{
	int i, j;
	float width;
	//∞∏¿Ã ∏∂¿Ã≥ Ω∫∏È «ˆ¿Á ¿Â¬¯¡ﬂ¿Œ∞‘ ¡¡¿∫∞≈¥Ÿ
	long long combatPowerGap = CompareCombatPower(&robin.newItem, &ao[robin.newItem.type % 3].equip[itemEquipSlot[robin.newItem.type]]);

	int arrowDirY = DOWN;
	
	if (combatPowerGap >= 0)
		arrowDirY = UP;

	//DrawFrame(x, y, (float)ITEMDETAILWINDOWSIZE_X * zoom, (float)(ITEMDETAILWINDOWSIZE_Y) * zoom, FRAME_NORMAL, cvtDest, cvtLayer, buffering);
	
	//equipped∞° true∏È ¿Â¬¯¡ﬂ, false∏È 
	switch (it->type) {
		//¿Â∫Ò
	default:
		DrawItemCard(
			it->type,
			it->detail,
			it->grade,
			it->lv,
			it->count,
			false,
			x,
			y,
			false,
			1.5f * zoom,
			false,
			false,
			false,
			false,
			0);

		DrawTouchLargeButton(x + (float)(432) * zoom, y - (float)(20) * zoom, BUYBUTTON_X, BUYBUTTON_Y, textId[TEXT_EQUIP], TOUCH_FUNC_EQUIP_INVENTORY + GetInvenIdx(it->type, it->detail, it->grade), FRAME_GREEN, zoom / CARDDEFAULTZOOM);

		break;
		//µø∑·
	case ITEM_CREW:
		int crewType = crewData[it->detail * CREWDATASIZE + CREWDATA_TYPE];
		int crewDetail = it->detail;
		int crewGrade = it->grade;
		int crewCmf = enemyData[crewType * ENEMYDATASIZE + ENEMYDATA_CMF];
		int crewMotion = crewPos[crewType * 5 + 0] + (frame / 2 / MOTIONDIV) % crewPos[crewType * 5 + 1];
		int crewName = TEXT_MONSTERNAME_START + crewType;
		int crewStar = GetItemStar(crewType, crewDetail, crewGrade);

		DrawItemCard(
			it->type,
			crewDetail,
			crewGrade,
			it->lv,
			it->count,
			false,
			x,
			y,
			false,
			1.2f * zoom,
			false,
			false,
			false,
			false,
			0);

		float slotZoom = 0.5f;
		for (i = 0; i < 3; i++) {
			float startX = x + (float)16 * zoom;
			float startY = y - (float)(400 + SLOTSIZE_Y * slotZoom * i) * zoom;
			
			DrawImage(SLOTSIZE_X, SLOTSIZE_Y, 0, 0,
				startX, startY,
				false, false, false, false, false,
				slotZoom * zoom, sprite[SLOT_IMG], SLOT_IMG);

			for (int j = 0; j < i + 1; j++)
			{
				float centerX = startX + (float)4 * slotZoom * zoom + (float)reelPostion[j * 2 + 0] * slotZoom * zoom;
				float centerY = startY + (float)reelPostion[j * 2 + 1] * slotZoom * zoom;

				float baseScale = 2.5f * slotZoom * zoom * enemyIconZoom[crewType];
				/*
				ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X,
					centerX - (float)12 * _2X * 2.5f * slotZoom * zoom,
					centerY + (float)8 * _2X * 2.5f * slotZoom * zoom,
					SHADOW_IMG, 2.5f * slotZoom * zoom, cvtDest, cvtLayer, buffering);
				*/

				DrawCmfDetailShadow(enemyData[crewType * ENEMYDATASIZE + ENEMYDATA_CMF],
					crewPos[crewType * 5 + 0],
					centerX, centerY,
					RIGHT, baseScale);
			}
		}

		return;
		/*
		DrawImageScale(128, 128, 716, 609, x, y, false, false, false, false, false, 4.75f * zoom, 1.65f * zoom, sprite[UI_NEW_IMG], cvtDest, cvtLayer, UI_NEW_IMG, buffering);

		//ƒ≥∏Ø≈Õ
		DrawImageScale(128, 128, 587, 737, x + (float)8 * zoom, y - (float)8 * zoom, false, false, false, false, false, 1.5f * zoom, 1.5f * zoom, sprite[UI_NEW_IMG], cvtDest, cvtLayer, UI_NEW_IMG, buffering);
		
		int crewType = crewData[it->detail * CREWDATASIZE + CREWDATA_TYPE];
		int crewDetail = it->detail;
		int crewGrade = it->grade;
		int crewCmf = enemyData[crewType * ENEMYDATASIZE + ENEMYDATA_CMF];
		int crewMotion = crewPos[crewType * 5 + 0] + (frame / 2 / MOTIONDIV) % crewPos[crewType * 5 + 1];
		int crewName = TEXT_MONSTERNAME_START + crewType;
		int crewStar = GetItemStar(crewType, crewDetail, crewGrade);

		DrawCmfDetailShadow(crewCmf, crewMotion, x + (float)104 * zoom, y - (float)160 * zoom, RIGHT, 2.0f * zoom, cvtDest, cvtLayer, buffering);
		SetFontColor(0x28145B);
		DrawTextSolid(crewName, x + (float)228 * zoom, y - (float)20 * zoom, 1.5f * zoom, cvtDest, cvtLayer, buffering);
		SetFontColor(COLOR_WHITE);
		DrawStar(ICON_STAR, x + (float)232 * zoom, y - (float)74 * zoom, crewStar, crewStar, crewStar, LEFT, false, 1.0f * zoom, cvtDest, cvtLayer, buffering);
		DrawButton(x + (float)228 * zoom, y - (float)110 * zoom, BUTTON_COLOR_PURPLE, (float)68 * zoom, false, false, false, 0.5f * zoom, 1.0f * zoom, cvtDest, cvtLayer, buffering);
		DrawLv(it->lv, x + (float)276 * zoom, y - (float)120 * zoom, 1.0f * zoom, CENTER, cvtDest, cvtLayer, buffering);
		DrawTouchLargeButton(x + (float)(432) * zoom, y - (float)(20) * zoom, BUYBUTTON_X, BUYBUTTON_Y, textId[TEXT_EQUIP], TOUCH_FUNC_EQUIP_INVENTORY + GetInvenIdx(ITEM_CREW, crewDetail, crewGrade), FRAME_GREEN, zoom, cvtDest, cvtLayer, buffering);
		*/

		//∑Í∑ø∆«
		DrawImageScale(128, 128, 587, 737, x + (float)8 * zoom, y - (float)240 * zoom, false, false, false, false, false, 1.5f * zoom, 1.5f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);

		for (i = 0; i < 3; i++) {
			DrawImage(SLOTSIZE_X, SLOTSIZE_Y, 0, 0,
				x + (float)16 * zoom, y - (float)(240 + i * 72) * zoom,
				false, false, false, false, false,
				0.35f * zoom, sprite[SLOT_IMG], SLOT_IMG);
			for (j = 0; j < i + 1; j++)
				DrawCmfDetailShadow(crewCmf, crewPos[crewType * 5 + 0], x + (float)(44 + 56 * j) * zoom, y - (float)(240 + i * 72 + 56) * zoom, RIGHT, 1.0f * zoom);

			int skillIcon = skillData[SKILLDATASIZE * crewData[crewType * CREWDATASIZE + CREWDATA_SKILL1 + i] + SKILLDATA_ICON];
			DrawSkillIcon(skillIcon, x + (float)300 * zoom, y - (float)(240 + i * 60) * zoom, 2.0f * zoom);

		}
		//∑π∫ßæ˜
		DrawImageScale(128, 128, 587, 737, x + (float)8 * zoom, y - (float)240 * 2 * zoom, false, false, false, false, false, 1.5f * zoom, 1.5f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);


		DrawButton(x + (float)32 * zoom, y - (float)(240 * 2 + 32) * zoom, BUTTON_COLOR_PURPLE, 64, false, TEXT_ALPHA_BEFORE, false, 0.5f, 1.0f);
		DrawImageScale(128, 128, 587, 608, x + (float)8 * zoom, y - (float)(240 * 2 + 24) * zoom, false, false, false, false, false, 1.5f * zoom, 1.5f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
		
		
		DrawButton(x + (float)228 * zoom, y - (float)(240 * 2 + 32) * zoom, BUTTON_COLOR_PURPLE, 64, false, TEXT_ALPHA_AFTER, false, 0.5f, 1.0f);
		DrawImageScale(128, 128, 587, 608, x + (float)228 * zoom, y - (float)(240 * 2 + 24) * zoom, false, false, false, false, false, 1.5f * zoom, 1.5f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);

		//TEXT_EQUIP
		//TEXT_SOCKETING
		break;
	}

	return;

	if (onlyInfo == true)
		DrawLabel(x + (float)(ITEMDETAILWINDOWSIZE_X / 2 - 40 * _2X) * zoom, y + (float)24 * _2X * zoom, TEXT_DETAILINFO, zoom);
	else
		DrawLabel(x + (float)(ITEMDETAILWINDOWSIZE_X / 2 - 40 * _2X) * zoom, y + (float)24 * _2X * zoom, equipped == true ? TEXT_EQUIPPEDITEM : TEXT_NEWITEM, zoom);

	if (equipped == false && onlyInfo == false && combatPowerGap != 0) {
		DrawText(TEXT_COMBATPOWER, x + (float)252 * _2X * zoom, y + (float)(-4 * _2X) * zoom, zoom);
		if (combatPowerGap > 0)
			SetColor(COLOR_REALYELLOW);
		else
			SetColor(COLOR_REALRED);
		DrawNum(combatPowerGap, x + (float)280 * _2X * zoom, y + (float)-18 * _2X * zoom, NUM_FONT_NORMAL, RIGHT, false, combatPowerGap > 0 ? PLUS : MINUS, true, zoom, false);
		SetColor(false);
	}
	//DrawRewardCard(it->type, it->detail, it->grade, it->cooldown, it->count, x + (float)0 * _2X * zoom, y - (float)0 * _2X * zoom, false, zoom * DEFAULTZOOM, false, false, true, GetItemStar(it->type, it->detail, it->grade), GetItemStar(it->type, it->detail, it->grade), true, 0, cvtDest, cvtLayer, buffering);

	//DrawIcon(GetItemIcon(it->type, it->detail, it->grade), x + (float)(8 * _2X) * zoom, y - (float)8 * _2X * zoom, zoom * DEFAULTZOOM, false, false, true, cvtDest, cvtLayer, buffering);

	DrawItemIcon(it, &ao[PLAYER], x + (float)(8 * _2X) * zoom, y - (float)8 * _2X * zoom, zoom * LOBBYZOOM);

	//º“ƒœ¿Ã ¿÷¥¬ æ∆¿Ã≈€¿Ã∂Û∏È
	//if (it->type <= ITEM_RING && it->count > 0) {
	//	DrawAlpha(x + (float)48 * _2X * zoom, y - (float)5 * _2X * zoom, ALPHA_SOCKET, FONT_SMALL, zoom, false, cvtDest, cvtLayer, buffering);
	//	for (i = 0; i < it->count; i++)
	//		DrawSocket(it->socket[i], x + (float)(88 * _2X + 9 * _2X * i) * zoom, y - (float)5 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);
	//}
	memset(&itemName, 0, sizeof(itemName));
	sprintf(itemName, "||[%s]  %s  |b%s %d", textId[TEXT_NORMAL + it->grade], it->name, textId[TEXT_ALPHA_LV], (int)(it->cooldown + 1));
	itemName[1] = itemColorText[it->grade];
	DrawTextStr(itemName, x + (float)44 * _2X * zoom, y - (float)16 * _2X * zoom, zoom);

	SetFontColor(COLOR_WHITE);

	MemRect(x + (float)4 * _2X * zoom, y - (float)42 * _2X * zoom, (float)(ITEMDETAILWINDOWSIZE_X - 8 * _2X) * zoom, (float)2 * _2X * zoom, COLOR_SKY);


	SetItemString(it, false, false);
	//SetFontColor(COLOR_)
	DrawTextStrSystem(tempStr, x + (float)44 * _2X * zoom, y - (float)28 * _2X * zoom, 0.8f * zoom, LEFT, false);

	//¿Â∫Ò¿Œ ∞ÊøÏ
	if (it->type <= ITEM_RING || it->type == ITEM_RECIPE) {
		int itemType = it->type;

		if (itemType == ITEM_RECIPE) {
			itemType = it->detail >> 3;
		}

		//¡æ∑˘
		width = GetAlphaWidth(ALPHA_SWORD + itemType, FONT_SMALL, zoom);
		//SetBlend(12, 0x0000FF);
		DrawAlpha(x + (float)(44 * _2X) * zoom, y - (float)6 * _2X * zoom, ALPHA_SWORD + itemType, FONT_SMALL, zoom, false);
		//UnSetBlend();

		DrawTextStr(textId[TEXT_DEFAULTSTAT], x + (float)12 * _2X * zoom, y - (float)52 * _2X * zoom, zoom);

		//∞¯∞›/πÊæÓ∑¬/»ø∞˙ ≈ÿΩ∫∆Æ
		//MemRectFrame(x + (float)4 * _2X * zoom, y - (float)75 * _2X * zoom, (float)168 * _2X * zoom, (float)15 * _2X * zoom, 0x9BA9BD, cvtDest, cvtLayer, buffering);

		//if (itemType != ITEM_RING)
		//	DrawAlpha(x + (float)7 * _2X * zoom, y - (float)79 * _2X * zoom, itemValueType[itemType], FONT_SMALL, zoom, false, cvtDest, cvtLayer, buffering);

		switch (it->type) {
		default:
			memset(&defaultStatStr, 0, sizeof(defaultStatStr));

			sprintf(defaultStatStr, "%s  %s", textId[itemValueTypeText[it->type]], dmgStr);

			DrawTextStr(defaultStatStr, x + (float)64 * _2X * zoom, y - (float)52 * _2X * zoom, zoom);

			if (equipped == false) {
				if (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) != 0) {
					//if (combatPowerNext - combatPowerCur != 0) {
						//arrowDirY = frame / FPS % 2;
						//DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - (robin.playtime / 2) % 8), x + (float)(arrowDirY == UP ? 180 * _2X : 180 * _2X) * zoom, y - (arrowDirY == UP ? (float)40 * _2X * zoom : (float)64 * _2X * zoom), LEFT, (arrowDirY == UP) ? false : 180, (float)(1.2f) * zoom, cvtDest, cvtLayer, buffering);
					DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - (robin.playtime / 2) % 8), x + (float)(GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? 200 * _2X : 210 * _2X) * zoom, y - (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? (float)40 * _2X : (float)54 * _2X) * zoom, LEFT, GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? false : 180, (float)(1.1f) * zoom);
					DrawNum(GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]), x + (float)280 * _2X * zoom, y - (float)50 * _2X * zoom, NUM_FONT_NORMAL, RIGHT, false, GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? PLUS : MINUS, true, 1.1f * zoom, false);
				}
			}

			//DrawTextStr(textId[itemValueTypeText[it->type]], x + (float)64 * _2X * zoom, y - (float)52 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);
			//DrawTextStr(dmgStr, x + (float)100 * _2X * zoom, y - (float)52 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);
			/*
			//∞≠»≠∑π∫ß
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
			DrawTextStr(dmgStr, x + (float)64 * _2X * zoom, y - (float)52 * _2X * zoom, zoom);

			if (equipped == false) {
				if (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) != 0) {
					//if (combatPowerNext - combatPowerCur != 0) {
						//arrowDirY = frame / FPS % 2;
						//DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - (robin.playtime / 2) % 8), x + (float)(arrowDirY == UP ? 180 * _2X : 180 * _2X) * zoom, y - (arrowDirY == UP ? (float)40 * _2X * zoom : (float)64 * _2X * zoom), LEFT, (arrowDirY == UP) ? false : 180, (float)(1.2f) * zoom, cvtDest, cvtLayer, buffering);
					DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - (robin.playtime / 2) % 8), x + (float)(GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? 200 * _2X : 210 * _2X) * zoom, y - (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? (float)40 * _2X : (float)54 * _2X) * zoom, LEFT, (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0) ? false : 180, (float)(1.2f) * zoom);
					DrawNum(GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]), x + (float)280 * _2X * zoom, y - (float)50 * _2X * zoom, NUM_FONT_NORMAL, RIGHT, false, (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0) ? PLUS : MINUS, true, 1.1f * zoom, false);
				}
			}
			break;
		case ITEM_RING:
			DrawTextStr(dmgStr, x + (float)64 * _2X * zoom, y - (float)52 * _2X * zoom, zoom);

			if (equipped == false) {
				if (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) != 0) {
					//if (combatPowerNext - combatPowerCur != 0) {
						//arrowDirY = frame / FPS % 2;
						//DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - (robin.playtime / 2) % 8), x + (float)(arrowDirY == UP ? 180 * _2X : 180 * _2X) * zoom, y - (arrowDirY == UP ? (float)40 * _2X * zoom : (float)64 * _2X * zoom), LEFT, (arrowDirY == UP) ? false : 180, (float)(1.2f) * zoom, cvtDest, cvtLayer, buffering);
					DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - (robin.playtime / 2) % 8), x + (float)(GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? 200 * _2X : 210 * _2X) * zoom, y - (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? (float)40 * _2X : (float)54 * _2X) * zoom, LEFT, (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0) ? false : 180, (float)(1.2f) * zoom);
					DrawNum(GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]), x + (float)280 * _2X * zoom, y - (float)50 * _2X * zoom, NUM_FONT_NORMAL, RIGHT, false, (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0) ? PLUS : MINUS, true, 1.1f * zoom, false);
				}
			}
			break;
		case ITEM_RECIPE:
			DrawTextStr(dmgStr, x + (float)64 * _2X * zoom, y - (float)52 * _2X * zoom, zoom);

			break;
		}
	}
	else if (it->type == ITEM_GEM) {
		MemRectFrame(x + (float)4 * _2X * zoom, y - (float)60 * _2X * zoom, (float)168 * _2X * zoom, (float)13 * _2X * zoom, 0x9BA9BD);

		//¡æ∑˘
		width = GetAlphaWidth(ALPHA_GEM, FONT_SMALL, zoom);

		SetBlend(12, 0x0000FF);
		DrawAlpha(x + (float)169 * _2X * zoom - width, y - (float)63 * _2X * zoom, ALPHA_GEM, FONT_SMALL, zoom, false);
		UnSetBlend();

		//∞¯∞›/πÊæÓ∑¬/»ø∞˙ ≈ÿΩ∫∆Æ
		MemRectFrame(x + (float)4 * _2X * zoom, y - (float)75 * _2X * zoom, (float)168 * _2X * zoom, (float)15 * _2X * zoom, 0x9BA9BD);
		DrawAlpha(x + (float)7 * _2X * zoom, y - (float)79 * _2X * zoom, ALPHA_OPTION, FONT_SMALL, zoom, false);
		DrawTextStr(optionStr[0], x + (float)43 * _2X * zoom, y - (float)76 * _2X * zoom, zoom);
	}
	else {
		if (it->type == ITEM_QUEST && it->detail >= ITEM_QUEST_MAP)
			MemRect(x + (float)4 * _2X * zoom, y - (float)73 * _2X * zoom, (float)168 * _2X * zoom, (float)2 * _2X * zoom, COLOR_SKY);
		else
			MemRect(x + (float)4 * _2X * zoom, y - (float)60 * _2X * zoom, (float)168 * _2X * zoom, (float)2 * _2X * zoom, COLOR_SKY);
	}
	if (it->option[0][0] != EMPTYINT && optionStr[0][0] != 0)
		DrawTextStr(textId[TEXT_OPTIONSTAT], x + (float)12 * _2X * zoom, y - (float)72 * _2X * zoom, zoom);
	ItemOptionDraw(it, x + (float)(64 * _2X) * zoom, y - (float)(72 * _2X * zoom), zoom, equipped);
	if (equipped == false && onlyInfo == false)
		ItemOptionCompareDraw(it, &ao[PLAYER].equip[itemEquipSlot[it->type]], x + (float)(200 * _2X) * zoom, y - (float)(72 * _2X * zoom), zoom);
	//¿Â¬¯, ±≥√º πˆ∆∞
	if (equipped == false && onlyInfo == false) {
		DrawTouchLargeButton(x + (float)(8 * _2X) * zoom, y - (float)(ITEMDETAILWINDOWSIZE_Y - 36 * _2X) * zoom, BUYBUTTON_X, BUYBUTTON_Y, textId[TEXT_DISASSEMBLE], TOUCH_FUNC_DISASSEMBLE_NEWITEM, FRAME_RED, zoom);
		DrawTouchLargeButton(x + (float)(196 * _2X) * zoom, y - (float)(ITEMDETAILWINDOWSIZE_Y - 36 * _2X) * zoom, BUYBUTTON_X, BUYBUTTON_Y, textId[TEXT_EQUIP], TOUCH_FUNC_EQUIP_NEWITEM, FRAME_GREEN, zoom);

		//if (CompareCombatPower(it, &ao[PLAYER].equip[itemEquipSlot[it->type]]) < 0) {
		//	ResetRectPoint();
		//	ScreenDarken(SCREENDARKEN);
		//	//∞Ê∞Ì
		//	DrawFrame(DX / 2, DY / 2, (float)160 * _2X * zoom, (float)160 * _2X * zoom, FRAME_ANIINFO, cvtDest, cvtLayer, buffering);

		//	DrawTouchLargeButton(x + (float)(32 * _2X) * zoom, DY / 2 - (float)(160 * _2X - 36 * _2X) * zoom, BUYBUTTON_X, BUYBUTTON_Y, textId[TEXT_CANCEL], TOUCH_FUNC_DISASSEMBLE_NEWITEM, FRAME_RED, zoom, cvtDest, cvtLayer, buffering);
		//	DrawTouchLargeButton(x + (float)(128 * _2X) * zoom, DY / 2 - (float)(160 * _2X - 36 * _2X) * zoom, BUYBUTTON_X, BUYBUTTON_Y, textId[TEXT_EQUIP], TOUCH_FUNC_EQUIP_NEWITEM, FRAME_GREEN, zoom, cvtDest, cvtLayer, buffering);

		//}

	}
	UnSectionClip(false);
}

void ItemOptionCompareDraw(ITEM* it1, ITEM* it2, int x, int y, float zoom)
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
					DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - (robin.playtime / 2) % 8), x + (float)(it1->option[i][1] - it2->option[i][1] > 0 ? 0 * _2X : 9 * _2X) * zoom, y - (it1->option[i][1] - it2->option[i][1] > 0 ? (float)-10 * _2X : (float)4 * _2X) * zoom, LEFT, (it1->option[i][1] - it2->option[i][1] > 0) ? false : 180, (float)(1.0f) * zoom);
					memset(&itemOptionStr, 0, sizeof(itemOptionStr));
					valueInt = it1->option[i][1] - it2->option[i][1];
					sprintf(itemOptionStr, TEXTPTR(TEXT_PREFIX_DESC_COMPARE + it1->option[i][0]), valueInt);
					DrawTextStr(itemOptionStr, x + (float)16 * _2X * zoom, y, zoom);
				}
			y -= (float)13 * _2X * zoom;
		}
	}
}

void ItemOptionDraw(ITEM* it, int x, int y, float zoom, bool equipped)
{
	int i, rt = 1, count, require;

	if (it->type <= ITEM_RING) {
		//ø…º«
		count = y;

		for (i = 0; i < 12; i++) {
			if (it->option[i][0] != EMPTYINT && optionStr[i][0] != 0) {
#ifdef DEBUG
				if (drawHandle == MD_SIMUL && i == e[0])
					DrawHand(x, y, 0);
#endif

				DrawTextStr(optionStr[i], x + (float)0 * _2X * zoom, y, zoom);
				y -= (float)13 * _2X * zoom;
			}
		}

		for (i = 0; i < 6; i++) {
			if (gemStr[i][0] != 0) {
				DrawTextStr(gemStr[i], x + (float)0 * _2X, y, zoom);
				y -= (float)13 * _2X * zoom;
			}
		}

		if (count != y) {
			y -= (float)5 * _2X;
			count = y;
		}

		if (it->type < ITEM_GEM) {
			//ºº∆Ææ∆¿Ã≈€¿Œ ∞ÊøÏ ºº∆Æ»ø∞˙∏¶ ∫∏ø©¡ÿ¥Ÿ.
			if (it->grade == GRADE_SET) {
				const int* ucPtr = &setOption[(it->set % 100) * SETOPTIONDATASIZE];

				DrawTextStr(setStr[0], x + (float)0 * _2X, y, zoom);

				y += 15;

				for (i = 1; i < 7 && setStr[i][0] != 0; i++, ucPtr += 3) {
					//if (it >= ITEMPTR_EQUIP && idx != ITEMPTR_TEMPITEM && setCount[idx - ITEMPTR_EQUIP] >= *ucPtr)
					//	SetBlend(8, 0x0000FF);
					//else
					SetBlend(16, 0x000000);

					//grayScale = 24;

					DrawTextStr(setStr[i], x + (float)0 * _2X * zoom, y, zoom);
					y -= (float)13 * _2X;

					UnSetBlend();
					grayScale = 0;
				}
			}
			/*
			if (it->type < ITEM_NECK && it->cooldown < MAXENCHANT) {
				if (count != y)
					y += 5;

				//∞≠»≠¿Á∑· ªÛºº≥ªøÎ
				for (i = 0; i < 2; i++) {
					unsigned char *eData = &d.enchantData[(it->type * 40 + d.itemDataOrder[(it->detail * 6 + it->grade)]) * ENCHANTDATASIZE + i * 2];

					//æ∆¿Ãƒ‹ π◊ ø‰±∏∞πºˆ
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

					//¿Ø¿˙∞° º“¡ˆ«— ∞≥ºˆ∞° ¡¶¿€«œ±‚ √Ê∫–«—¡ˆ √º≈©«œ∞Ì ªÁøÎ¿⁄∞° ∞°¡ˆ∞Ì ¿÷¥¬ ∞πºˆ∏∏≈≠¿ª ∫Œ√§≤√∑Œ ∫∏ø©¡ÿ¥Ÿ.
					if (count < require) {
						DrawCycle(x + 40, y + 15 + i * 18, 16, 16, 4 + require - count, 4 + require);
						rt = 0;
					}

					//æ∆¿Ã≈€ ¿Ã∏ß
					DrawText(TEXT_ITEMNAME_START + GetItemName(ITEM_IRON + *eData / 50, *eData % 50, 0), x + 60, y + 17 + i * 18);
				}

				//∞≠»≠¿Á∑·
				SetFontColor(rt == 0 ? 0xFF0000 : 0x00FF00);
				CenterText(TEXT_ENCHANT_STUFF, x + 82, y);
			}
			*/
		}
	}
	else if (it->type == ITEM_RECIPE) {
		//±‚∫ª¿Á∑· ªÛºº≥ªøÎ
		if (GetItemCount(it->type, it->detail, it->grade) == 0) {
			grayScale = 20;
			SetBlend(6, 0xFF0000);
			rt = 0;
		}

		DrawIcon(GetItemIcon(it->type, it->detail, it->grade), x + (float)40 * zoom, y - (float)15 * _2X, zoom, false, false, false, 1);

		if (rt == 0) {
			SetAlpha(10);
			MemRect(x + (float)40 * _2X * zoom, y - (float)15 * _2X, (float)16 * _2X * zoom, (float)16 * _2X * zoom, 0x990000);
			SetAlpha(32);
			grayScale = 0;
			UnSetBlend();
		}

		DrawText(TEXT_ITEMNAME_START + GetItemName(it->type, it->detail, it->grade), x + (float)60 * _2X * zoom, y - (float)17 * _2X * zoom, zoom);
	}
}

void EquipInfoDraw(ITEM* it, int x, int y, int itemType, int itemDetail, int itemGrade, int depth, int menuX, float zoom)
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

	//¿Œ∫•≈‰∏Æø°º≠ ΩΩ∑‘¿ª √£¥¬¥Ÿ.
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
		//¿Ã¿¸¥‹∞Ë
		//TouchArrow2(2, x + 0 * _2X, y + 0, DY / 2, cvtDest, cvtLayer, buffering);

		if (winAniFrame > 0) {
			winAniFrame++;

			DrawNeutral(OBJ_STAMPEFFECT0 + (frame / 3 % 8), x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + 160 * _2X) * zoom, 0, 1.0f);

			if (winAniFrame == FPS)
				winAniFrame = 0;
		}


		//«ˆ¿Á¥‹∞Ë
		DrawPlayerCostume(
			pObj->type,
			pObj->equip[EQUIP_WEAPON].type != EMPTY ? pObj->equip[EQUIP_WEAPON].detail : -1, pObj->equip[EQUIP_WEAPON].type != EMPTY ? pObj->equip[EQUIP_WEAPON].grade : 0,
			pObj->equip[EQUIP_GLOVE].type != EMPTY ? pObj->equip[EQUIP_GLOVE].detail : -1, pObj->equip[EQUIP_GLOVE].type != EMPTY ? pObj->equip[EQUIP_GLOVE].grade : 0,
			pObj->equip[EQUIP_HELM].type != EMPTY ? pObj->equip[EQUIP_HELM].detail : -1, pObj->equip[EQUIP_HELM].type != EMPTY ? pObj->equip[EQUIP_HELM].grade : 0,
			pObj->equip[EQUIP_ARMOR].type != EMPTY ? pObj->equip[EQUIP_ARMOR].detail : -1, pObj->equip[EQUIP_ARMOR].type != EMPTY ? pObj->equip[EQUIP_ARMOR].grade : 0,
			pObj->equip[EQUIP_PANTS].type != EMPTY ? pObj->equip[EQUIP_PANTS].detail : -1, pObj->equip[EQUIP_PANTS].type != EMPTY ? pObj->equip[EQUIP_PANTS].grade : 0,
			pObj->equip[EQUIP_BOOTS].type != EMPTY ? pObj->equip[EQUIP_BOOTS].detail : -1, pObj->equip[EQUIP_BOOTS].type != EMPTY ? pObj->equip[EQUIP_BOOTS].grade : 0,

			x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + 160 * _2X) * zoom, RIGHT, true, zoom * HEROZOOM);

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

		DrawRewardCard(itemType, itemDetail, itemGrade, itemLv, itemCnt, x + (float)(DX / 2 - REWARDCARDSIZE_X) * zoom, y + (float)(DY / 2 + 148 * _2X) * zoom, true, (float)2 * zoom, true, false, true, itemLv, ITEMMAXLEVEL, true, 0);
		//∞≥∫∞ ¿Â¬¯¿Ã µ«¡ˆ æ ¥¬¥Ÿ∏È
		//∏∏æ‡ ¿Â¬¯¿Ã µ«æÓ ¿÷¡ˆ æ ¿∏∏È
		if (GetEquipSlot(itemType, itemDetail, itemGrade) == -1) {
			DrawTextButton(x + (float)(DX / 2 - 40 * _2X) * zoom, y + (float)(DY / 2 + 148 * _2X - REWARDCARDSIZE_Y * 2 - 8 * _2X) * zoom, (float)(80 * _2X) * zoom, (float)(28 * _2X) * zoom, 0, false, zoom, false, TEXT_EQUIP);
			SetRectPoint(x + (float)(DX / 2 - 40 * _2X) * zoom, y + (float)(DY / 2 + 148 * _2X - REWARDCARDSIZE_Y * 2 - 8 * _2X) * zoom, (float)(80 * _2X) * zoom, (float)(28 * _2X) * zoom, TOUCH_FUNC_EQUIP_INVENTORY + itemStartCnt[itemType] + itemDetail * TOTALGRADE + itemGrade);
		}
		else
			DrawTextButton(x + (float)(DX / 2 - 40 * _2X) * zoom, y + (float)(DY / 2 + 148 * _2X - REWARDCARDSIZE_Y * 2 - 8 * _2X) * zoom, (float)(80 * _2X) * zoom, (float)(28 * _2X) * zoom, 0, 32, zoom, false, TEXT_SOCKETING);


		//∞ÒµÂ / ∞ÒµÂπÈ / «œ∆Æ / ƒ˘Ω∫∆Æ æ∆¿Ã≈€
		switch (itemType) {
		default:
			DrawItemValue(it->type, it->detail, it->grade, it->cooldown, x + (float)(DX / 2) * zoom, y + (float)(DY / 2 - 10 * _2X - ITEMICONSIZE) * zoom, CENTER, false, zoom, 128 * _2X * zoom);
			break;
		}

		switch (itemType) {
		case ITEM_SWORD:
			LineText(TEXT_TIP_MENU_SWORD, x + (float)(DX / 2 - 136 * _2X + 12 * _2X) * zoom, y + (float)(DY / 2 - 64 * _2X) * zoom, (float)(272 * _2X - 8 * _2X) * zoom, zoom);
			break;
		case ITEM_GUNTLET:
			LineText(TEXT_TIP_MENU_GLOVE, x + (float)(DX / 2 - 136 * _2X + 12 * _2X) * zoom, y + (float)(DY / 2 - 64 * _2X) * zoom, (float)(272 * _2X - 8 * _2X) * zoom, zoom);
			break;
		case ITEM_HELM:
			LineText(TEXT_TIP_MENU_HELM, x + (float)(DX / 2 - 136 * _2X + 12 * _2X) * zoom, y + (float)(DY / 2 - 64 * _2X) * zoom, (float)(272 * _2X - 8 * _2X) * zoom, zoom);
			break;
		case ITEM_ARMOR:
			LineText(TEXT_TIP_MENU_ARMOR, x + (float)(DX / 2 - 136 * _2X + 12 * _2X) * zoom, y + (float)(DY / 2 - 64 * _2X) * zoom, (float)(272 * _2X - 8 * _2X) * zoom, zoom);
			break;
		case ITEM_KILT:
			LineText(TEXT_TIP_MENU_PANTS, x + (float)(DX / 2 - 136 * _2X + 12 * _2X) * zoom, y + (float)(DY / 2 - 64 * _2X) * zoom, (float)(272 * _2X - 8 * _2X) * zoom, zoom);
			break;
		case ITEM_GREAVES:
			LineText(TEXT_TIP_MENU_BOOTS, x + (float)(DX / 2 - 136 * _2X + 12 * _2X) * zoom, y + (float)(DY / 2 - 64 * _2X) * zoom, (float)(272 * _2X - 8 * _2X) * zoom, zoom);
			break;
		}
		//¿Â¬¯«— ∏Ω¿¿ª ∫∏ø©¡÷∞Ì,

		//æ˜±◊∑π¿ÃµÂ
		//øﬁ¬ ¿Ã ∞≠»≠«œ±‚
		//ø¿∏•¬ ¿Ã ¿Â¬¯«œ±‚
		//

		for (i = 0; i < 1; i++) {
			if (menuX == i) {
				DrawFrame(x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i - 2 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 4 * _2X + 2 * _2X + YGAP) * zoom, (float)(128 * _2X) * zoom, (float)(32 * _2X) * zoom, FRAME_CHOICEBUTTON_BEIGE);
			}
			else {
				DrawFrame(x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 4 * _2X + YGAP) * zoom, (float)(128 * _2X) * zoom, (float)(32 * _2X) * zoom, FRAME_CHOICEBUTTON);
			}
			switch (i) {
				//∞≠»≠«œ±‚
			case 0:
				ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i - 20 * _2X + 24 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 4 * _2X + YGAP + 8 * _2X - 20 * _2X) * zoom, SHADOW_IMG, zoom);
				DrawNeutral(EFFECT_CRAFT0 + (menuX == 0 ? (frame / 2) % 3 : 0), x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i + 24 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 4 * _2X + YGAP - 20 * _2X) * zoom, 0, zoom);
				DrawText(TEXT_UPGRADE, x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i + 60 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 14 * _2X + YGAP) * zoom, zoom);

				//memset(tempStr, 0, sizeof(tempStr));
				//sprintf(tempStr, TEXTPTR(TEXT_MAXLEVEL), collectionLvLimit[collectionIdx]);

				//DrawTextStr(tempStr, x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i + 60 * _2X + 128 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 14 * _2X + YGAP) * zoom, zoom, cvtDest, cvtLayer, buffering);
				break;
				//¡¯»≠«œ±‚TEXT_HAMMER
			case 1:
				ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i - 20 * _2X + 24 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 4 * _2X + YGAP + 8 * _2X - 20 * _2X) * zoom, SHADOW_IMG, zoom);
				DrawCmfDetail(CMF_NPC_HEART, PO_C122_HEART, x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i + 24 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 4 * _2X + YGAP - 20 * _2X) * zoom, LEFT, zoom, false, false);
				DrawText(TEXT_HAMMER, x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i + 60 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 14 * _2X + YGAP) * zoom, zoom);
				break;
			}

			SetRectPoint(x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 4 * _2X + YGAP) * zoom, (float)(128 * _2X) * zoom, (float)(32 * _2X) * zoom, TOUCH_FUNC_EQUIP_ENCHANT + i);
		}

		switch (menuX) {
		case 0:
			Divide = 2;
			CARDZOOM = 0.45f;

			if (itemLv < collectionLvLimit[collectionIdx]) {
				//«ˆ¿Á ∑π∫ß∞˙ µ•πÃ¡ˆ

				DrawStar(ICON_STAR, +(float)(DX / 2 - 132 * _2X + 42 * _2X + 11 * _2X * 2) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 32 * _2X - 10 * _2X + YGAP - 2 * _2X * 2) * zoom, itemLv, ITEMMAXLEVEL, ITEMMAXLEVEL, CENTER, true, zoom);

				DrawStar(ICON_STAR, x + (float)(DX / 2 - 132 * _2X + 42 * _2X + 11 * _2X * 2 + 140 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 32 * _2X - 10 * _2X + YGAP - 2 * _2X * 2) * zoom, itemLv + 1, ITEMMAXLEVEL, ITEMMAXLEVEL, CENTER, true, zoom);

				//æ˜±◊∑π¿ÃµÂ »≠ªÏ«•
				SetAlpha(32 - Abs(frame % 32 - 16));
				DrawImage(18 * _2X, 14 * _2X, 58 * _2X, 174 * _2X, x + (float)(DX / 2 - 12 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 32 * _2X - 8 * _2X + YGAP) * zoom, true, false, false, false, false, (float)1.5f * zoom, sprite[COMMON_IMG], COMMON_IMG);
				SetAlpha(32);

				//æ˜±◊∑π¿ÃµÂ ∫∏ªÛ

				//æ˜±◊∑π¿ÃµÂ »ƒ µ•πÃ¡ˆ
				DrawBuyButton(x + (float)(DX / 2) * zoom - ((float)BUYBUTTON_X * zoom) / 2, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 32 * _2X - (MINDY_MIN - 240 * _2X - 4 * _2X - 32 * _2X) + 28 * _2X + 8 * _2X - 32 * _2X - 8 * _2X) * zoom, (float)BUYBUTTON_X * zoom, (float)(BUYBUTTON_Y)*zoom, frame, robin.hammer >= GetUpgradeHammer(itemType, itemDetail, itemGrade, itemLv) ? 0 : 32, GetUpgradeHammer(itemType, itemDetail, itemGrade, itemLv), CURRENCY_HAMMER, zoom, false, false, false);
				if (robin.hammer >= GetUpgradeHammer(itemType, itemDetail, itemGrade, itemLv)) {
					SetRectPoint(x + (float)(DX / 2) * zoom - ((float)BUYBUTTON_X * zoom) / 2, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 32 * _2X - (MINDY_MIN - 240 * _2X - 4 * _2X - 32 * _2X) + 28 * _2X + 8 * _2X - 32 * _2X - 8 * _2X) * zoom, (float)BUYBUTTON_X * zoom, (float)(BUYBUTTON_Y)*zoom, TOUCH_FUNC_ITEM_UPGRADE);
				}
			}
			else {

				DrawStar(ICON_STAR, +(float)(DX / 2) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 32 * _2X - 10 * _2X + YGAP - 2 * _2X * 2) * zoom, itemLv, ITEMMAXLEVEL, ITEMMAXLEVEL, CENTER, true, zoom);

				CenterText(TEXT_MAXUPGRADED, x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 380 * _2X - 2 * ITEMICONSIZE - 8 * _2X - 20 * _2X) * zoom, zoom);
			}

			break;
		case 1:
			for (i = 0; i < ITEMHAMMERCNT; i++) {
				DrawFrame(x + (float)(DX / 2 - 136 * _2X + 10 * _2X + (ITEMCARD_WIDTH / 3 + 4 * _2X) * i) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 12 * _2X + YGAP) * zoom, (float)(ITEMCARD_WIDTH / 3) * zoom, (float)(ITEMCARD_HEIGHT / 3) * zoom, FRAME_SHOPBALLOON);
				if (itemCnt <= i) {
					DrawAlpha(x + (float)(DX / 2 - 136 * _2X + 10 * _2X + (ITEMCARD_WIDTH / 3 + 4 * _2X) * i + ITEMCARD_WIDTH / 3 / 2 - 4 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 12 * _2X - ITEMCARD_HEIGHT / 3 / 2 + 4 * _2X + YGAP) * zoom, ALPHA_PLUS, FONT_SMALL, zoom, false);
				}
				else {
					ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(DX / 2 - 136 * _2X + 10 * _2X + (ITEMCARD_WIDTH / 3 + 4 * _2X) * i + ITEMCARD_WIDTH / 3 / 2 - 20 * _2X * 1) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 12 * _2X - ITEMCARD_HEIGHT / 3 / 2 + ITEMICONSIZE * 1 + ITEMICONSIZE * 1 / 4 - 4 * _2X - (ITEMICONSIZE + 4 * _2X) + YGAP) * zoom, SHADOW_IMG, zoom);
					DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), x + (float)(DX / 2 - 136 * _2X + 10 * _2X + (ITEMCARD_WIDTH / 3 + 4 * _2X) * i + ITEMCARD_WIDTH / 3 / 2 - ITEMICONSIZE * 1) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 12 * _2X - ITEMCARD_HEIGHT / 3 / 2 + ITEMICONSIZE * 1 + ITEMICONSIZE * 1 / 4 - 4 * _2X + YGAP) * zoom, (float)2 * zoom, false, false, false, 1);
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

			DrawFrame(x + (float)(DX / 2 - 136 * _2X + 14 * _2X + (ITEMCARD_WIDTH / 3 + 4 * _2X) * ITEMHAMMERCNT + 12 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 12 * _2X + YGAP) * zoom, (float)(ITEMCARD_WIDTH / 3) * zoom, (float)(ITEMCARD_HEIGHT / 3) * zoom, FRAME_SHOPBALLOON);
			ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(DX / 2 - 136 * _2X + 14 * _2X + (ITEMCARD_WIDTH / 3 + 4 * _2X) * ITEMHAMMERCNT + 12 * _2X + ITEMCARD_WIDTH / 3 / 2 - 20 * _2X * 1) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 12 * _2X - ITEMCARD_HEIGHT / 3 / 2 + ITEMICONSIZE * 1 + ITEMICONSIZE * 1 / 4 - 4 * _2X - (ITEMICONSIZE + 4 * _2X) + YGAP) * zoom, SHADOW_IMG, zoom);
			DrawIcon(GetItemIcon(itemTypeNext, itemDetailNext, itemGradeNext), x + (float)(DX / 2 - 136 * _2X + 14 * _2X + (ITEMCARD_WIDTH / 3 + 4 * _2X) * ITEMHAMMERCNT + 12 * _2X + ITEMCARD_WIDTH / 3 / 2 - ITEMICONSIZE * 1) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 12 * _2X - ITEMCARD_HEIGHT / 3 / 2 + ITEMICONSIZE * 1 + ITEMICONSIZE * 1 / 4 - 4 * _2X + YGAP) * zoom, (float)2 * zoom, false, false, false, 1);

			if (itemCnt >= ITEMHAMMERCNT) {
				SetAlpha(32 - Abs(frame % 32 - 16));
				DrawImage(18 * _2X, 14 * _2X, 58 * _2X, 174 * _2X, x + (float)(DX / 2 - 136 * _2X + (ITEMCARD_WIDTH / 3 + 4 * _2X) * ITEMHAMMERCNT) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 20 * _2X + YGAP) * zoom, true, false, false, false, false, (float)2 * zoom, sprite[COMMON_IMG], COMMON_IMG);
				SetAlpha(32);
			}
			else {
				SetAlpha(16);
				DrawImage(18 * _2X, 14 * _2X, 58 * _2X, 174 * _2X, x + (float)(DX / 2 - 136 * _2X + (ITEMCARD_WIDTH / 3 + 4 * _2X) * ITEMHAMMERCNT) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 20 * _2X + YGAP) * zoom, true, false, false, false, false, (float)2 * zoom, sprite[COMMON_IMG], COMMON_IMG);
				SetAlpha(32);

				CenterText(TEXT_5CARDNEED, x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 280 * _2X - 32 * _2X - 60 * _2X + YGAP) * zoom, zoom);

			}

			DrawBuyButton(x + (float)(DX / 2) * zoom - (float)(BUYBUTTON_X)*zoom / 2, y + (float)(DY / 2 + MINDY_MIN / 2 - 16 * _2X - 280 * _2X - 32 * _2X - (MINDY_MIN - 280 * _2X - 4 * _2X - 32 * _2X) + 28 * _2X + 8 * _2X - 32 * _2X) * zoom, (float)(BUYBUTTON_X)*zoom, (float)(BUYBUTTON_Y)*zoom, frame, robin.star >= itemEvolutionItem[itemDetail * TOTALGRADE * (ITEMMAXLEVEL + 1) + itemGrade * (ITEMMAXLEVEL + 1) + itemLv] ? 0 : 32, itemEvolutionItem[itemDetail * TOTALGRADE * (ITEMMAXLEVEL + 1) + itemGrade * (ITEMMAXLEVEL + 1) + itemLv], CURRENCY_STAR, zoom, false, false, discount);

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
				MemRect(x, DY, DX, DY, COLOR_BLACK);
				SetAlpha(32);


				ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(DX / 2 - 20 * _2X) * zoom, (float)(DY / 2 - 216 * _2X / 2 + 8 * _2X) * zoom, SHADOW_IMG, zoom);
				DrawNeutral(EFFECT_CRAFT0 + (menuFrame < FPS ? menuFrame / MOTIONDIV % 3 : 0), x + (float)(DX / 2) * zoom, (float)(DY / 2 - 216 * _2X / 2) * zoom, 0, 3 * zoom);

				if (menuFrame < FPS) {
					if (itemType == ITEM_CREW) {
						curStar = maxStar = crewData[itemDetail * CREWDATASIZE + CREWDATASIZE - 1] + 1;
					}
					else {
						curStar = maxStar = GetItemStar(itemType, itemDetail, itemGrade);
					}

					DrawRewardCard(itemType, itemDetail, itemGrade, itemLv, itemCnt, x + (float)(DX / 2 - REWARDCARDSIZE_X) * zoom, y + (float)(DY / 2 + 148 * _2X) * zoom, false, (float)2 * zoom, true, false, true, curStar, maxStar, true, 0);

					if (menuFrame > FPS * 2 / 3) {
						DrawRewardCard(itemType, itemDetail, itemGrade, itemLv + 1, itemCnt, x + (float)(DX / 2 - REWARDCARDSIZE_X - (FPS - menuFrame) * REWARDCARDSIZE_X / 2) * zoom, y + (float)(DY / 2 + 148 * _2X + (FPS - menuFrame) * REWARDCARDSIZE_Y / 2) * zoom, false, (float)(2 + FPS - menuFrame) * zoom, true, false, true, curStar, maxStar, true, 0);
					}
					else if (menuFrame >= FPS * 1 / 3) {
						DrawEffect(EFFECT_HOLY0 + (menuFrame % 10), x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + 148 * _2X - REWARDCARDSIZE_Y) * zoom, LEFT, false, 2.0f * zoom);
					}
					else {
						DrawEffect(BUFF_ARMOR0 + (menuFrame % 12), x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + 148 * _2X - REWARDCARDSIZE_Y) * zoom, LEFT, false, 2.0f * zoom);
					}

					DrawEffect(1000 - 1 + HIT_DIANA_MEDIUM1 + menuFrame % 7, x + (float)(DX / 2) * zoom, y + (float)(DY / 2 - 216 * _2X / 2 + 8 * _2X) * zoom, LEFT, false, zoom);

					if (menuFrame / MOTIONDIV % 3 == 2)
						PlayMusic(M_IRON);

					//if (menuFrame / 2 % 7)
					//DrawSubText(textId[TEXT_ENCHANTING], 0, menuFrame % 7, x + (float)(DX / 2) * zoom - StringWidth(textId[TEXT_ENCHANTING], zoom) / 2, y + (float)(-EQUIP_WIN_HEIGHT + 272 * _2X - 216 * _2X - 4 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

					SetAlpha(32 - Abs(frame % 32 - 16));
					CenterText(TEXT_ENCHANTING, x + (float)(DX / 2) * zoom, y + (float)(128 * _2X) * zoom, zoom);
					SetAlpha(32);

					if (menuFrame == FPS - 1) {
						//∞ÒµÂ ¬˜∞®
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
				//ƒ·±◊∑π≈¯∑π¿Ãº«Ω∫!
				else {
					if (itemType == ITEM_CREW) {
						curStar = maxStar = crewData[itemDetail * CREWDATASIZE + CREWDATASIZE - 1] + 1;
					}
					else {
						//curStar = maxStar = GetItemStar(itemType, itemDetail, itemGrade);
						curStar = itemLv + 1;
						maxStar = ITEMMAXLEVEL;

					}

					DrawRewardCard(itemType, itemDetail, itemGrade, itemLv, itemCnt, x + (float)(DX / 2 - REWARDCARDSIZE_X) * zoom, y + (DY / 2 + 148 * _2X) * zoom, false, (float)2 * zoom, true, true, true, curStar, maxStar, true, 0);

					DrawEffect(EFFECT_LEVELUP_TEXT0 + (frame / 2) % 14, x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + 128 * _2X + 32 * _2X) * zoom, 0, false, (float)3 * zoom);

					DrawGoldAlpha(x + (float)(DX / 2) * zoom, y + (float)(DY / 2 - 160 * _2X) * zoom, ALPHA_CONGRATULATIONS, FONT_GOLD_LARGE, zoom, CENTER, true, false);

					SetRectPoint(xOffset, DY, DX, DY, TOUCH_FUNC_GAMEMENU_OUT);

					SetAlpha(32 - Abs(frame / MOTIONDIV % 32 - 16));
					DrawGoldAlpha(xOffset + DX / 2, DY / 2 + TABBUTTONGAP, ALPHA_TABTOCOLLECT, FONT_GOLD_LARGE, 1, CENTER, false, false);
					SetAlpha(32);
				}
				break;
			case 1:
				effect.color = COLOR_BLACK;

				//¡¯»≠ æ÷¥œ∏ﬁ¿Ãº«
				if (menuFrame < 10 * 3 + 10 * 2 + 10 * 1 + 5 * 2 + 8 * 2 + 8 * 2 * 2) {

					width = ITEMHAMMERCNT * (ROULETTECARDSIZE_X + 8 * _2X);

					for (i = 0; i < ITEMHAMMERCNT; i++) {

						if (menuFrame >= 10 * 3 + 10 * 2 + 10 * 1 + 5 * 2 + 8 * 2 && menuFrame < 10 * 3 + 10 * 2 + 10 * 1 + 5 * 2 + 8 * 2 + 8 * 2 * 2) {
							SetAlpha(Min(32, menuFrame - (10 * 3 + 10 * 2 + 10 * 1 + 5 * 2 + 8 * 2)));
							SetColor(COLOR_WHITE);
							DrawFrame(x + (float)(DX / 2 - width / 2 + (ROULETTECARDSIZE_X + 8 * _2X) * i) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 300 * _2X) * zoom, (float)(ROULETTECARDSIZE_X)*zoom, (float)(ROULETTECARDSIZE_Y)*zoom, FRAME_SHOPBALLOON);
							SetColor(false);
							SetAlpha(32);
						}
					}
				}

				//0: ƒ´µÂ∞° 
				//¥Ÿº∏∞≥¿« ƒ´µÂ∞° «œ≥™∑Œ «’√ƒ¡ˆ∞Ì		
				if (menuFrame < 10 * 3 + 10 * 2 + 10 * 1 + 5 * 2 + 8 * 2 + 8 * 2 * 2 + FPS / 2) {

					//55 - 41 + 2
					if (menuFrame < 10 * 3) {
						DrawCmfDetail(CMF_NPC_HEART, PO_C122_6_C0 + (menuFrame / 3), x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + 64 * _2X) * zoom, LEFT, (float)3 * zoom, false, false);
					}
					else if (menuFrame < 10 * 3 + 10 * 2) {
						DrawCmfDetail(CMF_NPC_HEART, PO_C122_6_C0 + ((menuFrame - (10 * 3)) / 2), x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + 64 * _2X) * zoom, LEFT, (float)3 * zoom, false, false);
					}
					else if (menuFrame < 10 * 3 + 10 * 2 + 10 * 1) {
						DrawCmfDetail(CMF_NPC_HEART, PO_C122_6_C0 + ((menuFrame - (10 * 3 + 10 * 2)) / 1), x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + 64 * _2X) * zoom, LEFT, (float)3 * zoom, false, false);
					}
					else if (menuFrame < 10 * 3 + 10 * 2 + 10 * 1 + 5 * 2) {
						DrawCmfDetail(CMF_NPC_HEART, PO_C122_6_SUM0 + ((menuFrame - (10 * 3 + 10 * 2 + 10 * 1)) / 2), x + DX / 2, y + DY / 2 + 64 * _2X, LEFT, (float)3 * zoom, false, false);
					}
					else if (menuFrame < 10 * 3 + 10 * 2 + 10 * 1 + 5 * 2 + 8 * 2) {
						DrawCmfDetail(CMF_NPC_HEART, PO_C122_6_0 + (menuFrame - (10 * 3 + 10 * 2 + 10 * 1 + 5 * 2)) / 2, x + DX / 2, y + DY / 2 + 64 * _2X, LEFT, (float)3 * zoom, false, false);
					}
					else if (menuFrame < 10 * 3 + 10 * 2 + 10 * 1 + 5 * 2 + 8 * 2 + 8 * 2 * 2) {
						DrawCmfDetail(CMF_NPC_HEART, PO_C122_SPARK0 + ((menuFrame - (10 * 3 + 10 * 2 + 10 * 1 + 5 * 2 + 8 * 2)) / 2 % 8), x + DX / 2, y + DY / 2 + 64 * _2X, LEFT, (float)3 * zoom, false, false);
					}
					else {
						if (itemTypeNext == ITEM_CREW) {
							curStar = maxStar = crewData[itemDetailNext * CREWDATASIZE + CREWDATASIZE - 1] + 1;
						}
						else {
							curStar = maxStar = GetItemStar(itemTypeNext, itemDetailNext, itemGradeNext);
						}

						DrawRewardCard(itemTypeNext, itemDetailNext, itemGradeNext, itemLv, itemCnt, x + DX / 2 - ITEMCARDSIZE_X / 2, y + DY / 2 + (menuFrame - (10 * 3 + 10 * 2 + 10 * 1 + 5 * 2 + 8 * 2 + 8 * 2 * 2)) * 8 * _2X, false, 2, true, false, true, curStar, maxStar, true, 0);
					}

					if (menuFrame / 2 % 3 == 2)
						PlayMusic(M_IRON);

					if (menuFrame / 2 % 7)
						DrawSubText(textId[TEXT_ENCHANTING], 0, menuFrame % 7, x + DX / 2 - StringWidth(textId[TEXT_ENCHANTING], 1.0f) / 2, y - EQUIP_WIN_HEIGHT + 272 * _2X - 216 * _2X - 4 * _2X, 1.0f);

					if (menuFrame == 21 * 2 - 1) {
						//¡∂«’ºÆ ¬˜∞®
						robin.star -= itemEvolutionItem[itemDetail * TOTALGRADE * (ITEMMAXLEVEL + 1) + itemGrade * (ITEMMAXLEVEL + 1) + itemLv];
						it = GetItemPtr(ITEMPTR_INVEN + itemStartCnt[itemType / TOTALPLAYER] + itemDetail * TOTALGRADE + itemGrade);

						it->count -= ITEMHAMMERCNT;

						//∏∂¡ˆ∏∑ µÓ±ﬁ¿Ã∏È µ≈◊¿œ¿ª «œ≥™ ø√∑¡¡ÿ¥Ÿ.
						if (itemGrade == GRADE_LEGEND) {
							robin.inven[ITEMPTR_INVEN + itemStartCnt[itemType / TOTALPLAYER] + (itemDetail + 1) * TOTALGRADE + 0].count++;
						}
						//±◊∑∏¡ˆ æ ¿∏∏È ±◊∑π¿ÃµÂ∏¶ «œ≥™ ø√∑¡¡ÿ¥Ÿ. 
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
					DrawCmfDetail(CMF_NPC_HEART, PO_C122_BURST0 + Min(4, ((menuFrame / 4) % 7)), x + DX / 2, y + DY / 2 - 128 * _2X, LEFT, 3.0f, false, false);

					if (itemTypeNext == ITEM_CREW) {
						curStar = maxStar = crewData[itemDetailNext * CREWDATASIZE + CREWDATASIZE - 1] + 1;
					}
					else {
						curStar = maxStar = GetItemStar(itemTypeNext, itemDetailNext, itemGradeNext);
					}

					DrawRewardCard(itemTypeNext, itemDetailNext, itemGradeNext, itemLv, itemCnt, x + DX / 2 - ITEMCARDSIZE_X / 2, y + DY / 2 + 108 * _2X, false, 2.0f, true, false, true, curStar, maxStar, true, 0);

					//∞≠»≠º∫∞¯Ω√
					DrawEffect(EFFECT_LEVELUP_TEXT0 + (frame / 2) % 14, x + DX / 2, y + DY / 2 + 108 * _2X + 32 * _2X, 0, false, 3.0f);

					DrawGoldAlpha(x + DX / 2, y + DY / 2 - 160 * _2X, ALPHA_CONGRATULATIONS, FONT_GOLD_LARGE, 1.0f, CENTER, true, false);

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

void DrawCombatPower(long long pow, int icon, int x, int y, int alpha, float zoom)
{
	DrawRoundBar(x + (float)0 * zoom, y, 1.0f, ROUNDBAR_SMALL, BARCOLOR_RED, alpha, 0.5f * zoom);

	DrawIcon(icon, x + (float)(5 * _2X) * zoom, y - (float)5 * _2X * zoom, 1.4f * zoom, COLOR_BROWN, false, false, 1);
#ifdef NUMTTF
	DrawBigNumTTF(pow, x + (float)(COMBATPOWBARWIDTH - 10 * _2X) * zoom, y + (float)(-5 * _2X * 2) * zoom, NUM_FONT_NORMAL, RIGHT, false, false, (float)(COMBATPOWBARWIDTH - ITEMICONSIZE - 8 * _2X * 2) * zoom, true, zoom, true);
#else
	DrawBigNum2Bold(pow, x + (float)(COMBATPOWBARWIDTH - 7 * _2X) * zoom, y - (float)(10 * _2X) * zoom, RIGHT, false, false, (float)(COMBATPOWBARWIDTH - ITEMICONSIZE * 1.2f - 13 * _2X) * zoom, true, NUM2ZOOM * 1.2f * zoom, true);

#endif

}

void StarBarDraw(long long pow, int icon, int x, int y, int alpha, float zoom)
{
	DrawRoundBar(x + (float)0 * zoom, y, 1.0f, ROUNDBAR_SMALL, BARCOLOR_PURPLE, alpha, 0.5f * zoom);

	DrawIcon(icon, x + (float)(5 * _2X) * zoom, y - (float)5 * _2X * zoom, 1.4f * zoom, COLOR_BROWN, false, false, 1);
#ifdef NUMTTF
	DrawBigNumTTF(pow, x + (float)(COMBATPOWBARWIDTH - 10 * _2X) * zoom, y + (float)(-5 * _2X * 2) * zoom, NUM_FONT_NORMAL, RIGHT, false, false, (float)(COMBATPOWBARWIDTH - ITEMICONSIZE - 8 * _2X * 2) * zoom, true, zoom, true);
#else
	DrawBigNum2Bold(pow, x + (float)(COMBATPOWBARWIDTH - 7 * _2X) * zoom, y - (float)(10 * _2X) * zoom, RIGHT, false, false, (float)(COMBATPOWBARWIDTH - ITEMICONSIZE * 1.2f - 13 * _2X) * zoom, true, NUM2ZOOM * 1.2f * zoom, true);

#endif

}

void StageProgressDraw(int x, int y, int current, int progress, float zoom)
{
	int i;

	DrawFrame(x, y, (float)STAGEPROGRESSBARWIDTH * zoom, (float)STAGEPROGRESSBARHEIGHT * zoom, FRAME_SHOPBALLOON);
	//for (i = 0; i < )
}

void RemainedTurnDraw(int x, int y, int current, int progress, float zoom)
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

		// ===== ¿Ã¿¸ º˝¿⁄(3) æ÷¥œ∏ﬁ¿Ãº« =====
		// Phase 1: ¬…±◊∂ÛµÈ±‚ (0.0 ~ 0.2)
		if (t >= 0.0f && t < 0.2f)
		{
			float phase = t / 0.2f; // 0.0 ~ 1.0
			float squashCurve = pow(phase, 2.0f);

			oldYOffset = -10.0f * _2X * zoom * squashCurve;
			oldNumZoom = zoom * (1.0f + 0.2f * squashCurve);
			oldAlpha = 32;
		}
		// Phase 2: ¿€¿∫ ∆˜π∞º±¿∏∑Œ øÏ√¯ ¿Ãµø (0.2 ~ 0.5)
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
		// Phase 3: øÏ√¯ ≥°ø°º≠ æ∆∑°∑Œ ∂≥æÓ¡ˆ∏Èº≠ ∆‰¿ÃµÂæ∆øÙ (0.5 ~ 0.8)
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
			// Phase 3 ¿Ã»ƒø°¥¬ ¿Ã¿¸ º˝¿⁄ æ» ±◊∏≤
			oldAlpha = 0;
		}

		// ===== ªı º˝¿⁄(2) æ÷¥œ∏ﬁ¿Ãº« =====
		// Phase 4: ¿€∞‘ ≥™≈∏≥™º≠ ƒø¡ˆ∏Èº≠ ¡§¡ˆ (0.85 ~ 0.95)
		if (t >= 0.85f && t < 0.95f)
		{
			float phase = (t - 0.85f) / 0.1f; // 0.0 ~ 1.0

			float riseCurve = 1.0f - pow(1.0f - phase, 3.0f);
			newYOffset = -25.0f * _2X * zoom * (1.0f - riseCurve);

			newNumZoom = zoom * (0.5f + 0.5f * riseCurve);

			newAlpha = (int)(32 * Min(phase * 2.0f, 1.0f));
		}
		// Phase 5: ¡§¡ˆ »ƒ ªÏ¬¶ ≥ª∑¡ø¿∏Á æ»¬¯ (0.95 ~ 1.0)
		else if (t >= 0.95f)
		{
			float phase = (t - 0.95f) / 0.05f; // 0.0 ~ 1.0

			float settleCurve = pow(phase, 2.0f);
			newYOffset = -3.0f * _2X * zoom * (1.0f - settleCurve);

			newNumZoom = zoom;
			newAlpha = 32;
		}

		// ¿Ã¿¸ º˝¿⁄(3) ±◊∏Æ±‚
		if (oldAlpha > 0)
		{
			SetAlpha(oldAlpha);
			DrawGoldNum(remainedTurn + 1, x + oldXOffset, y + oldYOffset, CENTER, 1, false, false, oldNumZoom);
			SetAlpha(32);
		}

		// ªı º˝¿⁄(2) ±◊∏Æ±‚
		if (newAlpha > 0)
		{
			SetAlpha(newAlpha);
			DrawGoldNum(remainedTurn, x + newXOffset, y + newYOffset, CENTER, 1, false, false, newNumZoom);
			SetAlpha(32);
		}
	}
	else
	{
		DrawGoldNum(remainedTurn, x, y, CENTER, 1, false, false, zoom);
	}

	CenterTextStr("Remained", x, y - (float)20 * _2X * zoom, 0.3f * zoom);
	CenterTextStr("Turn", x, y - (float)24 * _2X * zoom, 0.3f * zoom);

	if (remainedTurnFrame > 0)
		remainedTurnFrame++;
	if (remainedTurnFrame == FPS)
		remainedTurnFrame = 0;
}

void HowToGetHeroesDraw(int x, int y, float zoom)
{
	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

	//¿œ¥‹ »˜æÓ∑Œ∏¶ »πµÊ«œ¥¬ ¡∂∞«¿ª ¡§∏Æ«œ¿⁄.
	//1π¯ ∑π∫ß, 2π¯ Ω∫≈◊¿Ã¡ˆ
	//∑π∫ß∑Œ «œ∏È ªÛ¿⁄∏¶ ∏π¿Ã ø≠æÓæﬂ «œ¥œ±Ó «œ∆Æ∞° ∏π¿Ã « ø‰«œ∞Ì
	//Ω∫≈◊¿Ã¡ˆ∑Œ «œ∏È 

	//DrawLabel(x + (float)(POPUPWINDOWSIZE_X - 88 * _2X) / 2 * zoom, y - (float)0 * _2X * zoom, TEXT_BORDERGUARD, zoom, cvtDest, cvtLayer, buffering);

	DrawEffect(EFFECT_LEVELUP_TEXT10, x + (float)POPUPWINDOWSIZE_X / 2, y, LEFT, false, zoom);
	DrawStarNum(ICON_STAR, 1, x + (float)POPUPWINDOWSIZE_X / 2, y, 2.0f * zoom);
}

void HowToGetCrewsDraw(int x, int y, float zoom)
{
	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

	//¿œ¥‹ ≈©∑˘¿⁄∏Æ∏¶ ø¿«¬«œ¥¬ ¡∂∞«¿ª ¡§∏Æ«œ¿⁄.
	//1π¯ ∑π∫ß, 2π¯ Ω∫≈◊¿Ã¡ˆ
	//∑π∫ß∑Œ «œ∏È ªÛ¿⁄∏¶ ∏π¿Ã ø≠æÓæﬂ «œ¥œ±Ó «œ∆Æ∞° ∏π¿Ã « ø‰«œ∞Ì
	//Ω∫≈◊¿Ã¡ˆ∑Œ «œ∏È 

	//DrawLabel(x + (float)(POPUPWINDOWSIZE_X - 88 * _2X) / 2 * zoom, y - (float)0 * _2X * zoom, TEXT_BORDERGUARD, zoom, cvtDest, cvtLayer, buffering);

}

//«ˆ¿Á æ˜±◊∑π¿ÃµÂ∞° ∞°¥…«— 
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

void CalendarDraw(int x, int y, float zoom)
{
	int i, j, tempIdx, mul = 1;
	int week = 0;
	int dayOfWeek = 1;
	int dayOfMonth = robin.calendarMonthDay;

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

	//πÿø° ¿œ¡÷¿œ¬•∏Æ Ω∫ƒ…¡Ï «•
	for (i = 0; i < WEEK + 1; i++) {
		switch (i) {
			//1¥ﬁƒ° ∫∏ªÛ¿Ã ±◊∑¡¡ˆ∞Ì
		case 0:
			DrawFrame(x + (float)(calendarPos[4 * i + 0]) * zoom, y + (float)(calendarPos[4 * i + 1] - 16 * _2X) * zoom, (float)(calendarPos[4 * i + 2]) * zoom, (float)(calendarPos[4 * i + 3]) * zoom, FRAME_SHOPBALLOON);

			SetSectionClip(x + (float)(calendarPos[4 * i + 0] + 4 * _2X) * zoom, y + (float)(calendarPos[4 * i + 1] - 16 * _2X - 4 * _2X) * zoom, (float)(calendarPos[4 * i + 2] - 8 * _2X) * zoom, (float)(calendarPos[4 * i + 3] - 8 * _2X) * zoom, false);

			DrawTileDirect(CASTLE1, x - (float)(12 * _2X) * zoom, y - (float)(280 * _2X) * zoom, zoom);

			SetSectionClip(x + (float)(calendarPos[4 * i + 0] + 4 * _2X) * zoom, y + (float)(calendarPos[4 * i + 1] - 16 * _2X - 4 * _2X) * zoom, (float)(calendarPos[4 * i + 2] - 8 * _2X) * zoom, (float)(calendarPos[4 * i + 3] - 8 * _2X) * zoom, false);

			DrawCmfDetail(CMF_NPC_LORA, 0, x + (float)(40 * _2X) * zoom, y - (float)(128 * _2X + 8 * _2X) * zoom, RIGHT, 4.0f * zoom, false, false);
			DrawCmfDetail(CMF_NPC_KING, 0, x + (float)(240 * _2X) * zoom, y - (float)(128 * _2X + 8 * _2X) * zoom, LEFT, 4.0f * zoom, false, false);

			ScreenDarken(16);

			UnSectionClip(false);

			DrawIcon(ICON_EVENT_CROWN, x + (float)(24 * _2X) * zoom, y - (float)(84 * _2X) * zoom, 1.5f * zoom, COLOR_BROWN, true, false, 1);

			MemRectRound(x + (float)(calendarPos[4 * i + 0] + 32 * _2X) * zoom, y + (float)(calendarPos[4 * i + 1] - 64 * _2X) * zoom, (float)(CALENDARBAR_WIDTH)*zoom, (float)(CALENDARBAR_HEIGHT)*zoom, COLOR_NAVY, Max(1 * _2X, (float)2 * _2X * zoom));
			MemRectRound(x + (float)(calendarPos[4 * i + 0] + 32 * _2X + 4 * _2X) * zoom, y + (float)(calendarPos[4 * i + 1] - 64 * _2X - 4 * _2X) * zoom, (float)(CALENDARBAR_WIDTH * dayOfMonth / MONTH) * zoom, (float)(CALENDARBAR_HEIGHT - 8 * _2X) * zoom, COLOR_ORANGE, Max(1 * _2X, (float)2 * _2X * zoom));

			for (j = 0; j < 4; j++) {
				DrawBox(calendarInfo1Month[(robin.stage / 10) * 3 * 4 + 3 * j + 1], x + (float)(calendarPos[4 * i + 0] + 36 * _2X + CALENDARBAR_WIDTH * calendarMonthlyRewardDay[j] / MONTH - (float)(0 / 2)) * zoom, y + (float)(calendarPos[4 * i + 1] - BOXSIZE_Y) * zoom, LEFT, boxNeutralAnimation[((frame / (MOTIONDIV * 2 * 2)) % 4)], false, true, false, true, (float)(1.2f) * zoom);
				DrawIcon(ICON_GOLD, x + (float)(calendarPos[4 * i + 0] + 32 * _2X + CALENDARBAR_WIDTH * calendarMonthlyRewardDay[j] / MONTH) * zoom, y + (float)(calendarPos[4 * i + 1] - 66 * _2X) * zoom, 1.2f * zoom, false, false, false, 1);
				SetFontColor(COLOR_BROWN);
				memset(tempStr, 0, sizeof(tempStr));
				sprintf(tempStr, "%d", calendarMonthlyRewardDay[j]);

				CenterTextStrSolid(tempStr, x + (float)(calendarPos[4 * i + 0] + 34 * _2X + CALENDARBAR_WIDTH * calendarMonthlyRewardDay[j] / MONTH + ITEMICONSIZE / 2) * zoom, y + (float)(calendarPos[4 * i + 1] - 64 * _2X - 4 * _2X) * zoom, 1.2f * zoom);
				SetFontColor(COLOR_WHITE);
				//DrawNum(calendarMonthlyRewardDay[j], x + (float)(calendarPos[4 * i + 0] + 36 * _2X + CALENDARBAR_WIDTH * calendarMonthlyRewardDay[j] / MONTH - ITEMICONSIZE + ITEMICONSIZE / 2 - 1 * _2X) * zoom, y + (float)(calendarPos[4 * i + 1] - 66 * _2X - 4 * _2X - 1 * _2X) * zoom, NUM_FONT_SMALL, CENTER, false, false, false, zoom, cvtDest, cvtLayer, buffering);
			}

			DrawLabel(x + (float)(calendarPos[4 * i + 0] + calendarPos[4 * i + 2] / 2 - ITEMCARDSIZE_X / 2 - 2 * _2X) * zoom, y + (float)(calendarPos[4 * i + 1] + 25 * _2X) * zoom, TEXT_CALENDAR_DAILYREWARD, zoom);

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

			DrawRewardCard(calendarInfo1Week[week * 4 * 10 + i * 4 + 0], calendarInfo1Week[week * 4 * 10 + i * 4 + 1], calendarInfo1Week[week * 4 * 10 + i * 4 + 2], 1, calendarInfo1Week[week * 4 * 10 + i * 4 + 3], x + (float)(calendarPos[4 * i + 0]) * zoom, y + (float)(calendarPos[4 * i + 1]) * zoom, false, 1.5f * zoom, false, false, true, curStar, maxStar, true, 0);

			//DrawLabel(x + (float)(calendarPos[4 * i + 0] - 2 * _2X) * zoom, y + (float)(calendarPos[4 * i + 1] + 25 * _2X) * zoom, TEXT_CALENDAR_DAY1 + i - 1, zoom, cvtDest, cvtLayer, buffering);
			//DrawTextButton(x + (float)(calendarPos[4 * i + 0] + 0 * _2X) * zoom, y + (float)(calendarPos[4 * i + 1] + 25 * _2X) * zoom, (float)(64 * _2X) * zoom, (float)(28 * _2X) * zoom, false, robin.calendarDayStatus[i - 1] == CALENDAR_REWARDSTATUS_REWARDGET ? 32 : 0, zoom, false, TEXT_CALENDAR_DAY1 + i - 1, cvtDest, cvtLayer, buffering);


			grayScale = 0;

			SetFontColor(COLOR_BROWN);
			CenterTextSolid(TEXT_CALENDAR_DAY1 + i - 1, x + (float)(calendarPos[4 * i + 0] + (float)REWARDCARDSIZE_X * 1.5f / 2) * zoom, y + (float)(calendarPos[4 * i + 1] + 16 * _2X) * zoom, 1.2f * zoom);
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

				DrawRewardCard(calendarInfo1Week[week * 4 * 10 + (i + j) * 4 + 0], calendarInfo1Week[week * 4 * 10 + (i + j) * 4 + 1], calendarInfo1Week[week * 4 * 10 + (i + j) * 4 + 2], 1, calendarInfo1Week[week * 4 * 10 + i * 4 + 3], x + (float)(calendarPos[4 * i + 0] + 24 * _2X + j * (76 * _2X)) * zoom, y + (float)(calendarPos[4 * i + 1]) * zoom, false, 1.5f * zoom, false, false, true, curStar, maxStar, true, 0);
			}

			//DrawLabel(x + (float)(calendarPos[4 * i + 0] + calendarPos[4 * i + 2] / 2 - ITEMCARDSIZE_X / 2 - 2 * _2X) * zoom, y + (float)(calendarPos[4 * i + 1] + 25 * _2X) * zoom, TEXT_CALENDAR_DAY1 + i - 1, zoom, cvtDest, cvtLayer, buffering);
			//DrawTextButton(x + (float)(POPUPWINDOWSIZE_X - 64 * _2X) / 2 * zoom, y + (float)(calendarPos[4 * i + 1] + 25 * _2X) * zoom, (float)(64 * _2X) * zoom, (float)(28 * _2X) * zoom, false, robin.calendarDayStatus[i - 1] == CALENDAR_REWARDSTATUS_REWARDGET ? 32 : 0, zoom, false, TEXT_CALENDAR_DAY1 + i - 1, cvtDest, cvtLayer, buffering);

			grayScale = 0;

			SetFontColor(COLOR_BROWN);
			CenterTextSolid(TEXT_CALENDAR_DAY1 + i - 1, x + (float)(POPUPWINDOWSIZE_X / 2) * zoom, y + (float)(calendarPos[4 * i + 1] + 16 * _2X) * zoom, 1.2f * zoom);
			SetFontColor(COLOR_WHITE);
			break;
		}

	}

	//«ˆ¿Á ∫∏ªÛ±Ó¡ˆ ≥≤¿∫ Ω√∞£
	//DrawTime(x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y + (float)( - 440 * _2X) * zoom, Max(0, 86400 - (MC_knlCurrentTimeStamp() - robin.calendarTimeStamp)), TIME_HOUR_MINUTE, CENTER, zoom, cvtDest, cvtLayer, buffering);



	//ªÛ¥‹ø° «—¥ﬁ¬•∏Æ Ω∫ƒ…¡Ï «•

	//¿ßø° ≈∏¿Ã∆≤ ≈¬±◊∏¶ ∫Ÿø©¡÷∞Ì,
	//
}

void OptionDraw(int x, int y, float zoom)
{
	//int GAP = -4 * _2X;
	int GAP = 14 * _2X;

	//DrawFrame(x, y, (float)(POPUPWINDOWSIZE_X)* zoom, (float)(GAMEMENUWIN2_Y)* zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

	//∏ﬁ¿Œ»≠∏È
//¿Ωæ«
	CenterText(TEXT_BGM, x + (float)(50 * _2X + 32 * _2X + GAP) * zoom, y - (float)(32 * _2X) * zoom, zoom);
	DrawTouchLargeButton(x + (float)(50 * _2X + 32 * _2X + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 16 * _2X) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[option.bgm ? TEXT_ON : TEXT_OFF], TOUCH_FUNC_OPTION_BGM, option.bgm ? FRAME_GREEN : FRAME_RED, zoom);

	//»ø∞˙¿Ω
	CenterText(TEXT_SE, x + (float)(DX / 2 + 104 * _2X / 2 + GAP) * zoom, y - (float)(32 * _2X) * zoom, zoom);
	DrawTouchLargeButton(x + (float)(DX / 2 + 104 * _2X / 2 + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 16 * _2X) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[option.se ? TEXT_ON : TEXT_OFF], TOUCH_FUNC_OPTION_SE, option.se ? FRAME_GREEN : FRAME_RED, zoom);

	//¡¯µø
	CenterText(TEXT_VIBRATION, x + (float)(50 * _2X + 32 * _2X + GAP) * zoom, y + (float)(-32 * _2X - 64 * _2X) * zoom, zoom);
	DrawTouchLargeButton(x + (float)(50 * _2X + 32 * _2X + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 16 * _2X - 64 * _2X) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[option.vibration ? TEXT_ON : TEXT_OFF], TOUCH_FUNC_OPTION_VIBRATION, option.vibration ? FRAME_GREEN : FRAME_RED, zoom);

	//ææÓ
	CenterText(TEXT_LANGUAGE, x + (float)(DX / 2 + 104 * _2X / 2 + GAP) * zoom, y + (float)(-32 * _2X - 64 * _2X) * zoom, zoom);
	DrawTouchLargeButton(x + (float)(DX / 2 + 104 * _2X / 2 + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 16 * _2X - 64 * _2X) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[TEXT_KOREAN + option.language], TOUCH_FUNC_OPTION_LANGUAGE, FRAME_BLUE, zoom);

	//∆‰¿ÃΩ∫∫œ
	CenterText(TEXT_FACEBOOK, x + (float)(50 * _2X + 32 * _2X + GAP) * zoom, y + (float)(-32 * _2X - 64 * _2X * 2) * zoom, zoom);
	DrawTouchLargeButton(x + (float)(50 * _2X + 32 * _2X + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 16 * _2X - 64 * _2X * 2) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[option.facebook ? TEXT_CONNECTED : TEXT_DISCONNECTED], TOUCH_FUNC_OPTION_FACEBOOK, option.facebook ? FRAME_GREEN : FRAME_RED, zoom);

	//±∏±€«√∑π¿Ã
	CenterText(TEXT_GOOGLEPLAY, x + (float)(DX / 2 + 104 * _2X / 2 + GAP) * zoom, y + (float)(-32 * _2X - 64 * _2X * 2) * zoom, zoom);
	DrawTouchLargeButton(x + (float)(DX / 2 + 104 * _2X / 2 + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 16 * _2X - 64 * _2X * 2) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[option.google ? TEXT_CONNECTED : TEXT_DISCONNECTED], TOUCH_FUNC_OPTION_GOOGLE, option.google ? FRAME_GREEN : FRAME_RED, zoom);

	//∞‘¿”ºæ≈Õ
	CenterText(TEXT_GAMECENTER, x + (float)(50 * _2X + 32 * _2X + GAP) * zoom, y + (float)(-32 * _2X - 64 * _2X * 3) * zoom, zoom);
	DrawTouchLargeButton(x + (float)(50 * _2X + 32 * _2X + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 16 * _2X - 64 * _2X * 3) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[option.gameCenter ? TEXT_CONNECTED : TEXT_DISCONNECTED], TOUCH_FUNC_OPTION_GAMECENTER, option.gameCenter ? FRAME_GREEN : FRAME_RED, zoom);

	//∞‘Ω∫∆Æ
	CenterText(TEXT_GUEST, x + (float)(DX / 2 + 104 * _2X / 2 + GAP) * zoom, y + (float)(-32 * _2X - 64 * _2X * 3) * zoom, zoom);
	DrawTouchLargeButton(x + (float)(DX / 2 + 104 * _2X / 2 + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 16 * _2X - 64 * _2X * 3) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[TEXT_CONNECTED], TOUCH_FUNC_OPTION_GUEST, FRAME_GREY, zoom);

	//µµøÚ∏ª ¡ˆø¯
	DrawTouchLargeButton(x + (float)(50 * _2X + 32 * _2X + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 64 * _2X * 4 - 12 * _2X) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[TEXT_HELP], TOUCH_FUNC_OPTION_HELP, FRAME_BLUE, zoom);

	//∞≥¿Œ¡§∫∏ ∫∏»£¡§√•
	DrawTouchLargeButton(x + (float)(DX / 2 + 104 * _2X / 2 + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 64 * _2X * 4 - 12 * _2X) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[TEXT_PRIVACY], TOUCH_FUNC_OPTION_POLICY, FRAME_BLUE, zoom);

	//¿ÃøÎæ‡∞¸
	DrawTouchLargeButton(x + (float)(50 * _2X + 32 * _2X + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 64 * _2X * 4 - 12 * _2X - 40 * _2X) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[TEXT_TERMOFSERVICE], TOUCH_FUNC_OPTION_POLICY, FRAME_GREY, zoom);

	//¡¶¿€¡¯
	DrawTouchLargeButton(x + (float)(DX / 2 + 104 * _2X / 2 + GAP - OPTIONBUTTONSIZE_X / 2) * zoom, y + (float)(-32 * _2X - 64 * _2X * 4 - 12 * _2X - 40 * _2X) * zoom, (float)OPTIONBUTTONSIZE_X * zoom, (float)OPTIONBUTTONSIZE_Y * zoom, textId[TEXT_STAFF], TOUCH_FUNC_OPTION_COMMUNITY, FRAME_GREY, zoom);
}


void SlotDraw(int x, int y, int crew1Cmf, int crew2Cmf, int crew3Cmf, float zoom)
{
	DrawImage(SLOTSIZE_X, SLOTSIZE_Y, 0, 0,
		x, y,
		false, false, false, false, false,
		0.35f * zoom, sprite[SLOT_IMG], SLOT_IMG);

	//DrawCmfDetailShadow(crew1Cmf, crewPos[crewType * 5 + 0], x + (float)(44 + 56 * j) * zoom, y - (float)(240 + i * 72 + 56) * zoom, RIGHT, 1.0f * zoom, cvtDest, cvtLayer, buffering);

}

void JokboDraw(int x, int y, float zoom)
{

}


void LevelUpMenuDraw(int lv, int status, int x, int y, float zoom)
{
	int i;

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);


	ExpBarWideDraw(robin.lv, robin.exps, x + (float)(POPUPWINDOWSIZE_X - CROWNBARWIDTH_WIDE) / 2 * zoom, y - (float)0 * _2X * zoom, zoom);

	for (i = 0; i < TOTAL_LVUPREWARD; i++) {
		DrawLevelUpCard(i, GetLevelUpRewardLv(i, robin.lv), GetLevelUpRewardLv(i, robin.lv) == false ? true : false, x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X) * zoom, y - (float)((i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y - 12 * _2X) + TSIZE * 2 + 8 * _2X) * zoom, zoom);

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


		//∏Ó∫–¿« ∏Ó¿ª ∏æ“¥¬¡ˆ∏¶ ∫∏ø©¡÷¥¬
		if (setItemCnt > 0) {
			DrawNum(setItemCnt, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 22 * _2X - 14 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X - 32 * _2X + 18 * _2X, NUM_FONT_NORMAL, LEFT, false, false, false, 1.0f, gScreenBuffer, gScreenLayer, false);
			DrawText(TEXT_SLASH, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 22 * _2X - 2 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X - 32 * _2X - 2 * _2X + 18 * _2X, 1.0f, gScreenBuffer, gScreenLayer, false);
			DrawNum(COLLECTIONSITEMCNT, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 22 * _2X + 6 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X - 32 * _2X + 18 * _2X, NUM_FONT_NORMAL, LEFT, false, false, false, 1.0f, gScreenBuffer, gScreenLayer, false);
		}
		//6∞≥∞° ¥Ÿ ¿Â¬¯µ«æÓ ¿÷æÓº≠ Ω∫≈≥¿Ã »∞º∫»≠ µ«æÓ ¿÷¿∏∏È
		if (GetFullEquipedCollectionIdx() == i)
			DrawNeutral(OBJ_STAMPEFFECT0 + (frame / 3 % 8), x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 4 * _2X + 16 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X, 0, 1.0f, gScreenBuffer, gScreenLayer, false);
		//∏∏æ‡ 6∞≥∞° ¥Ÿ ∏ø©∏∏ ¿÷¿∏∏È
		else if (setItemCnt == COLLECTIONSITEMCNT) {
			//æ∆π´∞Õµµ «œ¡ˆ æ ¥¬¥Ÿ.
		}
		else if (setItemCnt > 0) {
			//æ∆π´∞Õµµ «œ¡ˆ æ ¥¬¥Ÿ.
		}
		//æ∆π´∞Õµµ æ¯¿∏∏È
		else
			DrawIcon(ICON_EVENT_LOCK, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 4 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X + 32 * _2X - 12 * _2X - 52 * _2X, 2.0f, false, false, false, gScreenBuffer, gScreenLayer, false);
		*/
		//DrawLabel(x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + 8 * _2X) * zoom, y - (float)((i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) + 88 * _2X + TSIZE) * zoom, TEXT_LVUPREWARD_AUTOROLL + i, zoom, cvtDest, cvtLayer, buffering);

		SetRectPoint(x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X) * zoom, y - (float)((i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y - 12 * _2X) + TSIZE * 2 + 8 * _2X) * zoom, (float)(COLLECTIONCARDSIZE_X - 36 * _2X) * zoom, (float)(COLLECTIONCARDSIZE_Y - 16 * _2X) * zoom, TOUCH_FUNC_COLLECTIONS_DETAIL + i);

	}
	//
	//¿œ¥‹ ∏ﬁ¥∫ ¡§∏Æ∫Œ≈Õ «œ¿⁄.
	//1. ªÛ¡°->
	//2. ƒ˘Ω∫∆Æ∞° ¿÷∞Ì
	//3. 

	//∑π∫ßæ˜ ¿Ã∆Â∆Æ∏¶ ¡§¿««œ¿⁄.
	//ƒ…¿ÃΩ∫ ¡§¿«
	//1. √÷¥Î «œ∆ÆøÕ Ω√∞£¥Á »∏∫π∑Æ ¡ı∞°
	//2. ∏ﬁ¥∫ ø¿«¬
	//   - 
	//   - 
	//3. 
}

void DeptDiscountDraw(int x, int y, float zoom)
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

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

}


void DoubleGoldDraw(int x, int y, float zoom)
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

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

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
	case BOX_CASTLE0:
	case BOX_CASTLE1:
	case BOX_CASTLE2:
	case BOX_CASTLE3:
	case BOX_CASTLE4:
	case BOX_CASTLE5:
		return CURRENCY_GOLD;
	case BOX_CASTLE6:
	case BOX_CASTLE7:
	case BOX_CASTLE8:
	case BOX_CASTLE9:
		return CURRENCY_STAR;
	case BOX_CASTLE10:
	case BOX_CASTLE11:
	case BOX_CASTLE12:
	case BOX_CASTLE13:
	case BOX_CASTLE14:
	case BOX_CASTLE15:
		return CURRENCY_GOLD;
	}
}

int GetBoxGold(int boxType)
{
	//π⁄Ω∫¿« ƒ⁄¿Œ¿ª ±∏«œ¥¬ πÊπ˝
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
	case BOX_REWARD0:
		return 10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000;
	case BOX_REWARD1:	//ƒ´µÂ «—¿Â	//BOX_CHEST1
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000);
	case BOX_REWARD2:	//ƒ´µÂ µŒ¿Â	//BOX_CHEST2
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 10;
	case BOX_REWARD3:	//ƒ´µÂ ºº¿Â	//BOX_CHEST3
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 100;
	case BOX_REWARD4:
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 1000;
	case BOX_REWARD5:
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 10000;
	case BOX_REWARD6:
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 100;
	case BOX_REWARD7:
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 100;
	}
}

int GetItemCategoryCnt(int category) {
	int i;
	int j = 0;
	for (i = 0; i < TOTALINVENTORY; i++) {
		if (robin.inven[i].type == category) {
			j++;
		}
	}

	return j;
}

int GetScrollDy(int menuIdx)
{
	int i, j;
	int scrollDy = 0;
	int gapY = 0;
	int itemCategoryCnt;

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
		itemCategoryCnt = GetItemCategoryCnt(ITEM_CREW);

		scrollDy = (float)(CREW_GAP_Y) * (itemCategoryCnt / INVEN_HCNT + 1 - (itemCategoryCnt % INVEN_HCNT == 0 ? 1 : 0)) - 16;
		break;
	case MENU_COLLECTIONS:
		//«ˆ¿Á Ω∫≈©∑— ±‚¡ÿ¿∏∑Œ æ∆¿Ã≈€¿Ã ∏Ó∞≥¿Œ¡ˆ »Æ¿Œ
		itemCategoryCnt = GetItemCategoryCnt(menuX * TOTALCHAR + curHero);

		scrollDy = (float)(INVENTORY_GAP_Y) * (itemCategoryCnt / INVEN_HCNT + 1 - (itemCategoryCnt % INVEN_HCNT == 0 ? 1 : 0));
		break;
	case MENU_CASTLE:

		scrollDy = (float)(CASTLE_GAP_Y) * (TOTALCASTLE - 1);

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
	case MD_OPENING:
		OpeningDraw();
		break;
	case MD_PLAY:
	case MD_BATTLE:
	case MD_RAID:
	case MD_BOSSRAID:
		Play();
		break;
	case MD_GACHA:
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
	MemRect(0, DY, DX, DY, COLOR_NAVY);
	SetAlpha(32);

	ResetRectPoint();
	//4∞˜¿ª πŸ±˘¿∏∑Œ ≥™∞°¥¬∞Õ¿∏∑Œ «œ¿⁄
	SetRectPoint(0, DY, DX, (DY - *(ucPtr + 1)) / 2, TOUCH_ALERT_NO);//¿ß¬ 
	SetRectPoint(0, DY / 2 + *(ucPtr + 1) / 2, (DX - *ucPtr) / 2, *(ucPtr + 1), TOUCH_ALERT_NO);//øﬁ¬ 
	SetRectPoint(DX / 2 + *ucPtr / 2, DY / 2 + *(ucPtr + 1) / 2, (DX - *ucPtr) / 2, *(ucPtr + 1), TOUCH_ALERT_NO);//ø¿∏•¬ 
	SetRectPoint(0, DY / 2 - *(ucPtr + 1) / 2, DX, (DY - *(ucPtr + 1)) / 2, TOUCH_ALERT_NO);//æ∆∑°¬ 

	if (winAniFrame < 7)
		DrawFrame(DX / 2, DY / 2, *ucPtr, *(ucPtr + 1), FRAME_ANIINFO);
	else {
		DrawCmfPopUp(*(ucPtr + 4), pText, DX / 2 - *ucPtr / 2, DY / 2 + *(ucPtr + 1) / 2, *ucPtr, *(ucPtr + 1), DX - 120 * _2X, 5, 6, 1.0f);
		switch (alert) {
		default:
			if (winAniFrame > 7) {
				switch (pText) {
				case -5:
					break;
				case -4:
					pStr = "¬¯øÎ¡ﬂ¿Œ æ∆¿Ã≈€¿∏∑Œ ƒ˘Ω∫∆Æ∏¶ øœ∑·«“ ºˆ æ¯Ω¿¥œ¥Ÿ.";
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
						DrawTouchButton(DX / 2 - (StringWidth(textId[TEXT_CONFIRM], 1.0f) + 4) / 2, (DY - *(ucPtr + 1)) / 2 + 28 * _2X, textId[TEXT_CONFIRM], TOUCH_FUNC_CLOSEALERT);
					else
						YesNoDraw(DX / 2, (DY - *(ucPtr + 1)) / 2 + 40 * _2X);

					if (touch)
						touchModeOld = null;
				}

			}
			break;
		}
	}

	winAniFrame++;
}

void NewCollectionDraw(int x, int y, float zoom)
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

	MemRect(0, DY, DX, DY, COLOR_BLACK);

	for (i = 0; i < DX / 128 * _2X + 1; i++)
		DrawImage(128 * _2X, 208 * _2X, 0 * _2X, 0 * _2X, x + (float)(i * 128 * _2X) * zoom, y + (float)(-288 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_BG_IMG + MAPTYPE_SPACE], MAP_BG_IMG + MAPTYPE_SPACE);

	DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, x + (float)(DX / 2 - DIORAMASIZE_X / 2) * zoom, y + (float)(-288 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_DIORAMA_IMG + HOUSE_DEVILCASTLE], MAP_DIORAMA_IMG + HOUSE_DEVILCASTLE);

	effect.color2 = COLOR_BLACK;

	CollectionDetailListDraw(x, y, newCollectionIdx[curNewCollection], zoom);

	itemType = collectionData[newCollectionIdx[curNewCollection] * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + 0 * COLLECTIONSDATASIZE + 0];
	itemDetail = collectionData[newCollectionIdx[curNewCollection] * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + 0 * COLLECTIONSDATASIZE + 1];
	itemGrade = collectionData[newCollectionIdx[curNewCollection] * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + 0 * COLLECTIONSDATASIZE + 2];
	itemLv = GetItemLv(itemType, itemDetail, itemGrade);

	collectionIdx = GetCollectionIdx(itemType, itemDetail, itemGrade);

	skillLv = ao[PLAYER].skillLv[newSkillIdx];

	DrawNum(skillLv + 1, x + (float)(8 * _2X + SKILLICONSIZE * iconZoom * 0.75f + 2 * _2X * iconZoom) * zoom + StringWidth(textId[TEXT_SKILLNAME_COMMON_ROBIN1 + newSkillIdx], iconZoom * 0.75f * zoom) + (float)(2 * _2X * iconZoom) * zoom + StringWidth(textId[TEXT_ALPHA_LV], iconZoom * 0.5f * zoom) + (float)(8 * _2X * iconZoom) * zoom, y + (float)(-346 * _2X) * zoom, NUM_FONT_NORMAL, CENTER, 2, false, false, (float)(0.5f * iconZoom) * zoom, true);

	for (i = 0; i < TOTALHITMARK; i++) {
		if (hitMark[i].frame > 0) {
			if (hitMark[i].x != 0 || hitMark[i].y != 0) {
				DrawEffect(1000 - 1 + hitMarkData[hitMark[i].type * 3 + (hitMark[i].etc == 0 ? 0 : 1)] + hitMark[i].frame, (float)(hitMark[i].x) * zoom, (float)(hitMark[i].y) * zoom, hitMark[i].dir, false, zoom);
			}
		}
	}

	if (newCollectionFrame > FPS / 2) {
		effect.color2 = COLOR_BLACK;

		DrawGoldAlpha(x + (float)(DX / 2) * zoom, y + (float)(-400 * _2X) * zoom, ALPHA_CONGRATULATIONS, FONT_GOLD_LARGE, zoom, CENTER, true, false);

		CenterText(TEXT_COLLECTIONCOMPLETED, x + DX / 2, y + (float)(-400 * _2X - 32 * _2X) * zoom, (float)(1.2f) * zoom);

		if (newCollectionDepth == 0) {
			DrawText(TEXT_COLLECTIONREWARD, x + (float)(8 * _2X) * zoom, y + (float)(-400 * _2X - 72 * _2X) * zoom, (float)(1.5f) * zoom);

			DrawEffect(EFFECT_INSIDE_ARROW0 + Abs(4 - (newCollectionFrame / MOTIONDIV) % 8), x + (float)(180 * _2X) * zoom, y + (float)(-400 * _2X - 80 * _2X) * zoom, RIGHT, false, (float)(2.0f) * zoom);

			DrawBuyButton(x + (float)(DX - 128 * _2X) * zoom, y + (float)(-464 * _2X) * zoom, (float)128 * _2X * zoom, (float)BUYBUTTON_Y * zoom, newCollectionFrame, false, collectionReward[newCollectionIdx[curNewCollection] * 4 + 3], CURRENCY_HEART, zoom, false, false, false);

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

		DrawBuyButton(x + (float)(DX - 128 * _2X) * zoom, y + (float)(-464 * _2X) * zoom, (float)128 * _2X * zoom, (float)BUYBUTTON_Y * zoom, newCollectionFrame, false, collectionReward[newCollectionIdx[curNewCollection] * 4 + 3], CURRENCY_HEART, zoom, false, false, false);

		BarDraw(&bar[BAR_BOX], bar[BAR_BOX].zoom);

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
	int row = 1;//∞°∑Œ∑Œ ∏Ó∞≥¿Œ¡ˆ
	int col = 1;//ºº∑Œ∑Œ ∏Ó¡Ÿ¿Œ¡ˆ
	bool crewMenuDraw = false;
	bool equipMenuDraw = false;
	float menuZoom = 1.0f;
	float width;
	int remainNewItemCnt;
	//º∫ µÓ¿Â«œ¥¬ ∞≈ æ¯æ÷¡÷±‚
	ResetRectPoint();

	MemRect(0, DY, DX, DY, mapColor[MAPTYPE_SPACE]);

	if (newCardFrame < GACHADELAY_BOXDROP && newCardDepth == 0)
		newCardFrame = GACHADELAY_BOXDROP;

	for (i = 0; i < DX / 128 * _2X + 1; i++)
		DrawImage(128 * _2X, 208 * _2X, 0 * _2X, 0 * _2X, xOffset + i * 128 * _2X, STATUSWIN_Y + 208 * _2X / 2, false, false, false, false, false, 1.0f, sprite[MAP_BG_IMG + MAPTYPE_SPACE], MAP_BG_IMG + MAPTYPE_SPACE);

	DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, xOffset + DX / 2 - DIORAMASIZE_X / 2, STATUSWIN_Y + DIORAMASIZE_Y / 2, false, false, false, false, false, 1.0f, sprite[MAP_DIORAMA_IMG + HOUSE_DEVILCASTLE], MAP_DIORAMA_IMG + HOUSE_DEVILCASTLE);

	if (newItemType[curNewItemIdx] == ITEM_CREW) {
		curStar = maxStar = crewData[newItemDetail[curNewItemIdx] * CREWDATASIZE + CREWDATASIZE - 1] + 1;
	}
	else {
		curStar = maxStar = GetItemStar(newItemType[curNewItemIdx], newItemDetail[curNewItemIdx], newItemGrade[curNewItemIdx]);
	}

	if (newCardFrame >= GACHADELAY_BOXDROP) {
		zoom = Min(2.5f, 0.3f * (newCardFrame - GACHADELAY_BOXDROP));
		DrawRewardCard(newItemType[curNewItemIdx], newItemDetail[curNewItemIdx], newItemGrade[curNewItemIdx], 0, false, DX / 2 - (float)REWARDCARDSIZE_X / 2 * zoom, STATUSWIN_Y + Min(200 * _2X, 20 * _2X * (newCardFrame - GACHADELAY_BOXDROP)) + (float)REWARDCARDSIZE_Y / 2 * zoom, true, zoom, true, true, true, curStar, maxStar, true, 0);
	}

	if (newCardFrame >= GACHADELAY_BOXOPEN) {
		zoom = Max(1.5f, 8.0f + 0.5f * (GACHADELAY_BOXOPEN - newCardFrame));
		DrawGoldAlpha(DX / 2, DY / 2 + 200 * _2X + (float)23 * _2X / 2 * zoom, ALPHA_NEWCARD, FONT_GOLD_LARGE, zoom, CENTER, true, false);
	}

	switch (newCardDepth) {
	case 0:


		if (newCardFrame >= GACHADELAY_ITEMDROP) {
			//zoom = Min(1.0f, 0.3f * (newCardFrame - GACHADELAY_ITEMDROP));
			zoom = 1.0f;

			DrawText(TEXT_NEWCARDGETREWARD, (float)(8 * _2X) * zoom, DY / 2 + (float)(236 * _2X) + (float)(-400 * _2X - 76 * _2X) * zoom, (float)(1.5f) * zoom);

			DrawEffect(EFFECT_INSIDE_ARROW0 + Abs(4 - (newCardFrame / MOTIONDIV) % 8), (float)(180 * _2X) * zoom, DY / 2 + (float)(236 * _2X) + (float)(-400 * _2X - 84 * _2X) * zoom, RIGHT, false, (float)(2.0f) * zoom);

			DrawBuyButton((float)(DX / 2 + 32 * _2X) * zoom, DY / 2 + (float)(236 * _2X) + (float)(-464 * _2X) * zoom, (float)(108 * _2X) * zoom, (float)(32 * _2X) * zoom, frame, false, equipGetRewardHeart[newItemType[curNewItemIdx] * TOTAL_COLLECTIONS + newItemDetail[curNewItemIdx] * TOTALGRADE + newItemGrade[curNewItemIdx]], CURRENCY_HEART, zoom, false, false, false);

			SetRectPoint((float)(DX / 2 + 32 * _2X) * zoom, DY / 2 + (float)(236 * _2X) + (float)(-464 * _2X) * zoom, (float)(108 * _2X) * zoom, (float)(32 * _2X) * zoom, TOUCH_FUNC_NEWCARDREWARDGET);


			//if (frame % 3 == 0)
			//	SetHitMark(Random(DX), Random(DY), Random(2), DIANA, 1, PLAYER, zoom);
		}
		break;
	case 1:
		zoom = 1.0f;

		effect.color2 = COLOR_BLACK;

		DrawBuyButton((float)(DX / 2 + 32 * _2X) * zoom, DY / 2 + (float)(236 * _2X) + (float)(-464 * _2X) * zoom, (float)(108 * _2X) * zoom, (float)(32 * _2X) * zoom, frame, false, equipGetRewardHeart[newItemType[curNewItemIdx] * TOTAL_COLLECTIONS + newItemDetail[curNewItemIdx] * TOTALGRADE + newItemGrade[curNewItemIdx]], CURRENCY_HEART, zoom, false, false, false);

		BarDraw(&bar[BAR_BOX], bar[BAR_BOX].zoom);

		if (newCardFrame == 1) {
			//width = GetBigNumDx(equipGetRewardHeart[newItemType[curNewItemIdx] * TOTAL_COLLECTIONS + newItemDetail[curNewItemIdx] * TOTALGRADE + newItemGrade[curNewItemIdx]], false, NUM_FONT_NORMAL, false, true, 108 * _2X - (float)(ITEMICONSIZE + 4 * _2X) * 1.0f, 1.0f, true) + (float)(ITEMICONSIZE + 4 * _2X) * 1.0f;
			//SetCurrencyMarkArr((float)(DX / 2 + 32 * _2X + 108 * _2X / 2 + ITEMICONSIZE / 2) * zoom - width / 2, DY / 2 + (float)(236 * _2X) + (float)(-464 * _2X) * zoom - (float)(32 * _2X) * zoom / 2, (float)(bar[BAR_BOX].x + 16 * _2X + 128 * _2X / 2) * zoom - (GetBigNumDx(bar[BAR_BOX].count - GetInitHeart(), true, NUM_FONT_NORMAL, false, true, (float)(HEARTBARADDNUMWIDTH)* zoom, zoom, true) + (float)(20 * _2X + 4 * _2X) * zoom) / 2 + (float)(ITEMICONSIZE / 2) * zoom, bar[BAR_BOX].y - 8 * _2X - ITEMICONSIZE, false, false, 16 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, false, false, FPS, false, ICON_HEART, 30, collectionReward[newCollectionIdx[curNewCollection] * 4 + 3], CURRENCY_HEART, 2.0f, 1.5f, -0.2f / MOTIONDIV, false, false, false, 10);

			AddBar(&bar[BAR_BOX], equipGetRewardHeart[newItemType[curNewItemIdx] * TOTAL_COLLECTIONS + newItemDetail[curNewItemIdx] * TOTALGRADE + newItemGrade[curNewItemIdx]], BARFRAME);
			GetItem(ITEM_HEART, false, false, false, equipGetRewardHeart[newItemType[curNewItemIdx] * TOTAL_COLLECTIONS + newItemDetail[curNewItemIdx] * TOTALGRADE + newItemGrade[curNewItemIdx]], false);

		}
		else if (newCardFrame == FPS * 1) {
			//«ˆ¿Á æ∆¿Ã≈€ ¿Œµ¶Ω∫∏¶ ¥ı«ÿ¡÷∞Ì
			curNewItemIdx++;

			newCardDepth = 0;
			newCardFrame = 0;

			//∏∏æ‡ ªı∑ŒøÓ æ∆¿Ã≈€¿Ã∏È
			if (newItemCnt == curNewItemIdx) {
				drawHandle = before_DrawHandle_NewCard;
				keyHandle = before_KeyHandle_NewCard;

			}
		}
		break;
	}

	if (newItemCnt > 1) {

		DrawFrame(xOffset + DX / 2 - 152 * _2X, STATUSWIN_Y, 304 * _2X, 48 * _2X, FRAME_SHOPBALLOON);
		remainNewItemCnt = (newItemCnt - curNewItemIdx);
		width = (float)(BOXSIZE_X * 0.7f + 4 * _2X) * Min(6, remainNewItemCnt) - 4 * _2X;

		for (i = curNewItemIdx; i < curNewItemIdx + Min(6, remainNewItemCnt); i++) {
			if (newItemType[i] == ITEM_CREW) {
				curStar = maxStar = crewData[newItemDetail[i] * CREWDATASIZE + CREWDATASIZE - 1] + 1;
			}
			else {
				curStar = maxStar = GetItemStar(newItemType[i], newItemDetail[i], newItemGrade[i]);
			}

			DrawRewardCard(newItemType[i], newItemDetail[i], newItemGrade[i], 0, false, xOffset + DX / 2 - width / 2 + (float)(BOXSIZE_X * 0.7f + 4 * _2X) * (i - curNewItemIdx), STATUSWIN_Y - 4 * _2X, true, 0.7f, true, true, true, curStar, maxStar, true, 0);
		}

		DrawNum(remainNewItemCnt, DX / 2 - 8 * _2X, STATUSWIN_Y - 52 * _2X, NUM_FONT_NORMAL, RIGHT, false, false, false, 1.0f, true);
		CenterText(TEXT_SLASH, DX / 2, STATUSWIN_Y - 54 * _2X, 1.0f);
		DrawNum(newItemCnt, DX / 2 + 8 * _2X, STATUSWIN_Y - 52 * _2X, NUM_FONT_NORMAL, LEFT, false, false, false, 1.0f, true);

	}

	newCardFrame++;

	for (i = 0; i < TOTALHITMARK; i++) {
		if (hitMark[i].frame > 0) {
			if (hitMark[i].x != 0 || hitMark[i].y != 0) {
				DrawEffect(1000 - 1 + hitMarkData[hitMark[i].type * 3 + (hitMark[i].etc == 0 ? 0 : 1)] + hitMark[i].frame, xOffset + hitMark[i].x - rx, hitMark[i].y - ry - OBJIMGGAP, hitMark[i].dir, false, 1.0f);
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

void StageInfoDraw(int stage, int room, long long combatPower, bool cur, int x, int y, float zoom)
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
	//∫∏Ω∫

	//robin.stage = 9;


	switch (stageInfoDepth) {
	case STAGEINFO_CREWDROP:
		DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

		//DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom - (float)(DIORAMASIZE_X) / 2 * zoom, y + (float)16 * _2X * zoom + yGap, false, false, false, false, false, zoom, sprite[MAP_DIORAMA_IMG + stageHouseType[stage]], cvtDest, cvtLayer, MAP_DIORAMA_IMG + stageHouseType[stage], buffering);
		//∫∏Ω∫ ¡§∫∏
		DrawStageLabel(x + (float)(DX / 2) * zoom, y + (float)(8 * _2X) * zoom, TEXT_STAGE, robin.stage, robin.room, true, zoom);

		//ø˛¿Ã∫Í ∫∏Ω∫
		//if (stageInfoCurFrame > 20)
		DrawCmfDetailShadow(enemyData[stageBossType * ENEMYDATASIZE + ENEMYDATA_CMF], frame / 2 % crewPos[stageBossType * CREWDATASIZE], x + (float)(DX / 2) * zoom, y - (float)108 * _2X * zoom + Max(0 * _2X, (FPS / 2 - stageInfoCurFrame) * 16 * _2X) * zoom + yGap, RIGHT, zoom);

		//BossHpBarDraw(GetStageBossObjectIdx() == false ? stageBossMaxHp : ao[GetStageBossObjectIdx()].hp, stageBossMaxHp, x + (float)(DX / 2) * zoom, y - (float)116 * _2X * zoom, zoom, cvtDest, cvtLayer, buffering);
		if (stageInfoCurFrame > 23)
			DrawGoldAlpha(x + (float)92 * _2X * zoom, y - (float)(DIORAMASIZE_Y - 44 * _2X) * zoom + yGap, ALPHA_BOSS, FONT_GOLD_LARGE, 0.7f * zoom, LEFT, true, false);

		if (stageInfoCurFrame > 26) {
			HpBarDraw(stageBossType, GetStageBossObjectIdx() == false ? stageBossMaxHp : ao[GetStageBossObjectIdx()].hp, stageBossMaxHp, x + (float)(DX / 2) * zoom, y - (float)152 * _2X * zoom + yGap, zoom);
		}

		if (stageInfoCurFrame > 30) {
			SetAlpha(28);
			GradiationFrame(x + (float)(POPUPWINDOWSIZE_X - 280 * _2X) / 2 * zoom, y - (float)(192 * _2X) * zoom + yGap, (float)280 * _2X * zoom, (float)24 * _2X * zoom, 0);
			SetAlpha(32);
		}

		if (stageInfoCurFrame > 33)
			CenterText(TEXT_CLEARREWARDS, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)(192 * _2X + 7 * _2X) * zoom + yGap, zoom);

		if (stageInfoCurFrame > 36)
			DrawBox(stageClearBox[robin.stage], x + (float)48 * _2X * zoom, y - (float)(200 * _2X + 88 * _2X) * zoom + yGap, LEFT, false, COLOR_WHITE, false, false, true, (float)BOXCASTLEZOOM * zoom);

		if (stageInfoCurFrame > 39) {
			DrawFrame(x + (float)(88 * _2X) * zoom, y - (float)(200 * _2X + 26 * _2X) * zoom + yGap, (float)208 * _2X * zoom, (float)RAIDGOLDBARHEIGHT * zoom, FRAME_SHOPBALLOON);
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
			//ø˛¿Ã∫Í ∫∏ªÛ
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

				DrawRewardCard(rewardType, rewardDetail, rewardGrade, 1, rewardCnt, x + (float)(DX / 2 - (rewardItemCnt) * (REWARDCARDSIZE_X + 4 * _2X) * 1.5f / 2 + i * (REWARDCARDSIZE_X + 2 * _2X) * 1.5f + 38 * _2X) * zoom, y - (float)(224 * _2X) * zoom + yGap, false, 1.5f * zoom, false, false, true, curStar, maxStar, true, 0);

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
		DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);
		SetAlpha(32);

		//DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom - (float)(DIORAMASIZE_X) / 2 * zoom, y + (float)16 * _2X * zoom - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_DIORAMA_IMG + stageHouseType[stage]], cvtDest, cvtLayer, MAP_DIORAMA_IMG + stageHouseType[stage], buffering);

		//ºº¿‘¿⁄
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
							DrawCmfDetail(CMF_NPC_HEART, PO_C122_SPARK0 + stageInfoCurFrame / MOTIONDIV % 8, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - DIORAMASIZE_Y / 2 + (float)8 * _2X + enemyCrewY - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom + (float)100 * _2X * zoom, LEFT, LOBBYZOOM, false, false);
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
								CenterText(TEXT_MONSTERNAME_START + enemyHouse.crew[i], DX / 2, DY / 2 + TABBUTTONGAP + 80 * _2X, 2.0f);
								SetFontColor(COLOR_WHITE);
								CenterText(TEXT_STAGECLEARCREWGET, DX / 2, DY / 2 + TABBUTTONGAP + 48 * _2X, 1.5f);
								SetAlpha(32 - Abs(frame / MOTIONDIV % 32 - 16));
								DrawGoldAlpha(xOffset + DX / 2, DY / 2 + TABBUTTONGAP, ALPHA_TABTOCOLLECT, FONT_GOLD_LARGE, 1, CENTER, false, false);
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

							DrawImage(40 * _2X, 40 * _2X, 80 * _2X, 0 * _2X, startX, startY, false, false, false, false, 32, menuZoom, sprite[MENUICON_IMG], MENUICON_IMG);

						}
					}
					break;

				}
			}

		}

		//1.º∫∞˙ µø∑·µÈ¿ª æ’¿∏∑Œ ≥ª ººøÓ ªÛ≈¬ø°º≠
		if (stageInfoCurFrame < STAGECLEARDELAY_APPEAR) {
			UnSectionClip(true);
			//DrawCmfDetail(enemyData[boss[stage] * ENEMYDATASIZE + ENEMYDATA_CMF], crewPos[boss[stage] * 5 + 0] + (FPS / 2 + 10 < stageInfoCurFrame ? frame / 2 / MOTIONDIV : 0) % crewPos[boss[stage] * 5 + 1], x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)DIORAMASIZE_Y * zoom + (float)32 * _2X * zoom - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom, RIGHT, enemyZoom[boss[stage]] * enemyBossZoom[boss[stage]] * zoom * 0.6f + (float)stageInfoCurFrame * zoom * 0.01f + (float)stageInfoCurFrame * stageInfoCurFrame / 5 * zoom * 0.001f, false, false, cvtDest, cvtLayer, buffering);
			UnSectionClip(false);
		}
		//2.∫∏Ω∫∞° ≥Ø∂Û∞°∞Ì
		else if (stageInfoCurFrame < STAGECLEARDELAY_BOSSAWAY) {
			UnSectionClip(true);
			//DrawCmfDetail(enemyData[boss[stage] * ENEMYDATASIZE + ENEMYDATA_CMF], crewPos[boss[stage] * 5 + 0] + (FPS / 2 + 10 < stageInfoCurFrame ? frame / 2 / MOTIONDIV : 0) % crewPos[boss[stage] * 5 + 1], x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)DIORAMASIZE_Y * zoom + (float)32 * _2X * zoom - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom, RIGHT, enemyZoom[boss[stage]] * enemyBossZoom[boss[stage]] * zoom * 0.6f + (float)stageInfoCurFrame * zoom * 0.01f + (float)stageInfoCurFrame * stageInfoCurFrame / 5 * zoom * 0.001f, (stageInfoCurFrame + (stageInfoCurFrame * stageInfoCurFrame) / (5 * MOTIONDIV)) % 360, false, cvtDest, cvtLayer, buffering);
			UnSectionClip(false);
		}
		//3.ºº¿‘¿⁄µÈ¿Ã øÙ¥¬ ∏Ω¿¿Ã ≥™ø¿∞Ì, ø©±‚º≠ πÿø° ≈ÿΩ∫∆Æ∏¶ ∂Áøˆ¡÷∏Èº≠ ∑Í∑ø Ω∫≈∏∆Æ∏¶ ªÁøÎ¿⁄∞° º±≈√«œ∞‘ Ω√≈≤¥Ÿ.
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
		//Ω∫≈◊¿Ã¡ˆ ≈¨∏ÆæÓ ∫∏ªÛ
	case STAGEINFO_STAGECLEAR:
		SetAlpha(20);
		MemRect(0, DY, DX, DY, COLOR_BLACK);
		SetAlpha(32);

		DrawGoldAlpha(DX / 2, DY - GNBHEIGHT - 16 * _2X, ALPHA_STAGECLEAR, FONT_GOLD_LARGE, fontZoom, CENTER, true, false);

		//Ω∫≈◊¿Ã¡ˆ ≈¨∏ÆæÓ æÀ∆ƒ∫™¿Ã ∂ﬂ∞Ì
		if (stageInfoCurFrame < STAGECLEARDELAY_ALPHA) {

		}
		//ªÛ¿⁄∞° ∂ﬂ∞Ì
		else if (stageInfoCurFrame < STAGECLEARDELAY_BOXDROP) {
			if (stageInfoCurFrame == STAGECLEARDELAY_ALPHA) {
				SetBoxMark(xOffset + DX / 2, DY + REWARDCARDSIZE_Y, xOffset + DX / 2, STATUSWIN_Y + 16 * _2X, xOffset + DX / 2, STATUSWIN_Y + 16 * _2X, 16 * _2X * 2 / MOTIONDIV, 2 * _2X * 2 / MOTIONDIV, 2 * _2X * 2 / MOTIONDIV, 2 * _2X * 2 / MOTIONDIV, FPS * 3, FPS * 3, 30, stageClearBox[robin.stage], GRADE_NORMAL, BOXZOOM, BOXZOOM, 0.2f / MOTIONDIV, BOXZOOM, BOXZOOM, 0.2f / MOTIONDIV);
			}
		}
		//ªÛ¿⁄∞° ø≠∏Æ∏Èº≠ ≥ª∫Œ ∫∏ªÛ¿Ã ≥™ø¿∞Ì, ªÛ¿⁄¥¬ ªÁ∂Û¡ˆ∞Ì
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
				boxMark[0].openFrame = true;
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
		//∫∏ªÛ¿ª ≈««œ∂Û¥¬ ∏ﬁ¥∫∞° ≥™ø¿∞Ì
		else if (stageInfoCurFrame < STAGECLEARDELAY_TABREWARD) {
			SetAlpha(32 - Abs(frame / MOTIONDIV % 32 - 16));
			DrawGoldAlpha(xOffset + DX / 2, DY / 2 + TABBUTTONGAP, ALPHA_TABTOCOLLECT, FONT_GOLD_LARGE, 1, CENTER, false, false);
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

					BarDraw(&bar[BAR_GOLD], bar[BAR_GOLD].zoom);
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

					BarDraw(&bar[BAR_HEART], bar[BAR_HEART].zoom);
					break;
				case ITEM_MEDAL:
					getMedalNum += rewardItem[i].count;

					targetX = xOffset + 4 * _2X + 164 * _2X + ITEMICONSIZE / 2;
					targetY = DY - (GNBHEIGHT - GNB_INIT_HEIGHT) - ITEMICONSIZE / 2;
					if (stageInfoCurFrame == STAGECLEARDELAY_TABREWARD) {
						SetCurrencyMarkArr_PopUp(startX, startY, targetX, targetY, false, false, 16 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, false, false, CURRENCYWAITINGFRAMEMAX, 0, ICON_MEDAL, 30, rewardItem[i].count, CURRENCY_MEDAL, 2.0f, 2.0f, -0.2f / MOTIONDIV, 2.0f, 1.0f, -0.2f, 10);
						j++;
					}

					BarDraw(&bar[BAR_MEDAL], bar[BAR_MEDAL].zoom);
					break;
				case ITEM_STAR:
					getStarNum += rewardItem[i].count;

					targetX = xOffset + 4 * _2X + 164 * _2X + ITEMICONSIZE / 2;
					targetY = DY - (GNBHEIGHT - GNB_INIT_HEIGHT) - ITEMICONSIZE / 2;
					if (stageInfoCurFrame == STAGECLEARDELAY_TABREWARD) {
						SetCurrencyMarkArr_PopUp(startX, startY, targetX, targetY, false, false, 16 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, false, false, CURRENCYWAITINGFRAMEMAX, 0, ICON_STAR, 30, rewardItem[i].count, CURRENCY_STAR, 2.0f, 1.0f, -0.2f / MOTIONDIV, false, false, false, 10);
						j++;
					}
					break;
				case ITEM_HAMMER:
					getHammerNum += rewardItem[i].count;

					targetX = xOffset + 4 * _2X + 164 * _2X + ITEMICONSIZE / 2;
					targetY = DY - (GNBHEIGHT - GNB_INIT_HEIGHT) - ITEMICONSIZE / 2;
					if (stageInfoCurFrame == STAGECLEARDELAY_TABREWARD) {
						SetCurrencyMarkArr_PopUp(startX, startY, targetX, targetY, false, false, 4 * _2X / MOTIONDIV, 4 * _2X / MOTIONDIV, false, false, CURRENCYWAITINGFRAMEMAX, 0, ICON_HAMMER, 30, rewardItem[i].count, CURRENCY_HAMMER, 2.0f, 1.0f, -0.2f / MOTIONDIV, false, false, false, 10);
						j++;
					}
					BarDraw(&bar[BAR_HAMMER], bar[BAR_HAMMER].zoom);
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

						DrawImage(40 * _2X, 40 * _2X, 80 * _2X, 0 * _2X, startX, startY, false, false, false, false, 32, menuZoom, sprite[MENUICON_IMG], MENUICON_IMG);

					}
					else if (equipMenuDraw == false) {
						equipMenuDraw = true;

						startX = xOffset + DX / 2 - 150 * _2X + 40 * _2X / 2 - (float)(40 * _2X) * menuZoom / 2;
						startY = STATUSWIN_Y + JOYSTICKGAP + 83 * _2X + (float)(40 * _2X) * menuZoom / 2;

						DrawImage(40 * _2X, 40 * _2X, 0 * _2X, 0 * _2X, startX, startY, false, false, false, false, false, menuZoom, sprite[MENUICON_IMG], MENUICON_IMG);
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
					//	//ø©±‚º≠ Ω∫≈≥¿∫ µ˚∑Œ Ω≈±‘ »πµÊ »§¿∫ ∑π∫ßæ˜¿ª «ÿ¡ÿ¥Ÿ..
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

			//»πµÊµ»∞Õ¿∫ ¡¶ø‹«œ∞Ì ¥Á∞‹¡ÿ¥Ÿ.
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

				//rewardItemCnt ∞° 0∫∏¥Ÿ ≈©¥Ÿ¥¬ ∞Õ¿∫ ªÛ¿⁄∞° ¿÷¥Ÿ¥¬ ∞Õ¿Ãπ«∑Œ GotoGacha∑Œ ∫∏≥Ω¥Ÿ.
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
		//∞°¬˜∞° ¿÷¿∏∏È «ÿ¥Á »≠∏È¿∏∑Œ ∫∏≥ª¡÷∞Ì

		//¥Ÿ ≥°≥™∏È ¡æ∑·Ω√ƒ—¡÷∏Èº≠ ¥Ÿ¿Ω Ω∫≈◊¿Ã¡ˆ∑Œ ¿Ãµø«œ∞Ì
		break;

	case STAGEINFO_NEWSTAGE:

		DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

		//DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom - (float)(DIORAMASIZE_X) / 2 * zoom, y + (float)16 * _2X * zoom, false, false, false, false, false, zoom, sprite[MAP_DIORAMA_IMG + stageHouseType[stage]], cvtDest, cvtLayer, MAP_DIORAMA_IMG + stageHouseType[stage], buffering);

		//ºº¿‘¿⁄
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
			DrawPlayer(&ao[SOLDIER], frame / MOTIONDIV % 4, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)DIORAMASIZE_Y * zoom + (float)32 * _2X * zoom, LEFT, 2.0f * zoom * Max(1, FPS / 2 + 10 - stageInfoCurFrame) * 0.6f, false, false, true);

#else
			DrawCmfDetailShadow(enemyData[boss[stage] * ENEMYDATASIZE + ENEMYDATA_CMF], crewPos[boss[stage] * 5 + 0] + (FPS / 2 + 10 < stageInfoCurFrame ? frame / 2 / MOTIONDIV : 0) % crewPos[boss[stage] * 5 + 1], x + (float)(POPUPWINDOWSIZE_X - 160 * _2X) / 2 * zoom, y - (float)DIORAMASIZE_Y * zoom + (float)32 * _2X * zoom, LEFT, enemyZoom[boss[stage]] * enemyBossZoom[boss[stage]] * zoom * Max(1, FPS / 2 + 10 - stageInfoCurFrame) * 0.6f);
#endif
		}

		if (stageInfoCurFrame > 23) {
#ifdef PVPWITHUSER
			DrawLabel(x + (float)(POPUPWINDOWSIZE_X - 88 * _2X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X) * zoom, false, zoom);
			CenterText(TEXT_NICKNAME + 4, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X + 10 * _2X) * zoom, zoom);
#else
			//DrawImage(207, 33, 0, 953, x + (float)(POPUPWINDOWSIZE_X - 64 * _2X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X + 6 * _2X) * zoom, false, false, false, false, false, 1.5f * zoom, sprite[THEATER_IMG], cvtDest, cvtLayer, THEATER_IMG, buffering);
			//MemRect(x + (float)(POPUPWINDOWSIZE_X - 15 * _2X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X + 12 * _2X) * zoom, (float)(HPBARWIDTH * 1.5f / 2 * robin.bossObj.hp / robin.bossObj.maxhp)* zoom, (float)(HPBARHEIGHT * 1.5f / 2)* zoom, ENEMYHPBARCOLOR, cvtDest, cvtLayer, buffering);
			//DrawNum(robin.bossObj.hp, x + (float)(POPUPWINDOWSIZE_X - 15 * _2X + (float)HPBARWIDTH * 1.5f - 8 * _2X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X + 12 * _2X) * zoom, NUM_FONT_NORMAL, RIGHT, 0, count >= 0 ? false : MINUS, true, zoom, cvtDest, cvtLayer, buffering);
			//DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, x + (float)(POPUPWINDOWSIZE_X - 15 * _2X + (float)HPBARWIDTH * 1.5f - 8 * _2X) / 2 * zoom - GetNumDx(robin.bossObj.hp, 0, NUM_FONT_NORMAL, 0, true, zoom) - (float)(ITEMICONSIZE * 0.8f + 4 * _2X) * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X + 11 * _2X) * zoom, 0.8f * zoom, false, false, false, cvtDest, cvtLayer, buffering);
			HpBarDraw(boss[robin.stage], robin.totalBossHp, robin.totalBossMaxHp, x + (float)(POPUPWINDOWSIZE_X - 16 * _2X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X + 10 * _2X) * zoom, 0.8f * zoom);

			DrawLabel(x + (float)(POPUPWINDOWSIZE_X - 88 * _2X - 160 * _2X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X) * zoom, TEXT_STAGENAME + stage/*TEXT_MONSTERNAME_START + boss[stage]*/, zoom);
#endif
		}

		if (stageInfoCurFrame > 26) {
#ifdef PVPWITHUSER
			CenterAlpha(x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X) * zoom, ALPHA_USERINFO, FONT_SMALL, false, zoom);
#else
			CenterAlpha(x + (float)(POPUPWINDOWSIZE_X - 160 * _2X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X) * zoom, ALPHA_BOSS, FONT_SMALL, false, zoom);

#endif
		}

		if (stageInfoCurFrame > 30) {
			SetAlpha(28);
			GradiationFrame(x + (float)(POPUPWINDOWSIZE_X - 280 * _2X) / 2 * zoom, y - (float)(200 * _2X) * zoom, (float)280 * _2X * zoom, (float)24 * _2X * zoom, 0);
			SetAlpha(32);
		}

		if (stageInfoCurFrame > 33)
			CenterText(TEXT_RAIDGOLD, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)(200 * _2X + 7 * _2X) * zoom, zoom);

		if (stageInfoCurFrame > 36)
			DrawFrame(x + (float)(POPUPWINDOWSIZE_X - 256 * _2X) / 2 * zoom, y - (float)(200 * _2X + 26 * _2X) * zoom, (float)256 * _2X * zoom, (float)RAIDGOLDBARHEIGHT * zoom, FRAME_SHOPBALLOON);

		if (stageInfoCurFrame > 39) {

			width = (float)(ITEMICONSIZE * 1.5f + 4 * _2X) * goldZoom + GetBigNumGoldDx(betCnt, false, FONT_GOLD_LARGE, false, true, (float)(256 * _2X - 32 * _2X) * zoom, goldZoom);

			DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom - width / 2, y - (float)(200 * _2X + 24 * _2X) * zoom - (float)8 * _2X * zoom, 1.5f * goldZoom, false, false, false, true);

			DrawBigNumGold(betCnt, x + (float)POPUPWINDOWSIZE_X / 2 * zoom - width / 2 + (float)(ITEMICONSIZE * 1.5f + 4 * _2X) * zoom, y - (float)(200 * _2X + 24 * _2X) * zoom - (float)8 * _2X * zoom, FONT_GOLD_LARGE, LEFT, false, false, (float)(240 * _2X - 32 * _2X) * goldZoom, true, goldZoom);
		}

		if (stageInfoCurFrame > 45) {
			SetAlpha(28);
			GradiationFrame(x + (float)(POPUPWINDOWSIZE_X - 280 * _2X) / 2 * zoom, y - (float)(260 * _2X) * zoom, (float)(280 * _2X) * zoom, (float)(24 * _2X) * zoom, 0);
			SetAlpha(32);
		}

		if (stageInfoCurFrame > 48)
			CenterText(TEXT_RENT, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)(260 * _2X + 7 * _2X) * zoom, zoom);

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

					//DrawRewardCard(ITEM_CREW, detail, GRADE_NORMAL, 1, 1, x + (float)(14 * _2X) * zoom, y - (float)(298 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 8 * _2X) * i * 1.2f * zoom, false, 1.2f * zoom, false, false, false, curStar, maxStar, 0, cvtDest, cvtLayer, buffering);

					//DrawBuyButton(x + (float)(14 * _2X) * zoom + (float)50 * _2X * zoom, y - (float)(298 * _2X + 16 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 8 * _2X) * i * 1.2f * zoom, (float)(160 * _2X) * zoom, (float)(32 * _2X) * zoom, frame, false, 100000000, CURRENCY_GOLD, zoom, false, false, false, cvtDest, cvtLayer, buffering);

					//DrawRewardCard(ITEM_CREW, detail, GRADE_NORMAL, 1, 1, x + (float)(10 * _2X) * zoom + (float)(POPUPWINDOWSIZE_X - 30 * _2X) / 2 * (i % 2) * zoom, y - (float)(298 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 8 * _2X) * (i / 2) * 1.2f * zoom, false, 1.2f * zoom, false, false, false, curStar, maxStar, 0, cvtDest, cvtLayer, buffering);

					if (stageUpgradeMotion[i] > 0 && stageUpgradeMotion[i] < 11) {
						ao[NPC].cmf = ao[NPC].type = ROBIN;
						ao[NPC].x = x + (float)(36 * _2X) * zoom + (float)(POPUPWINDOWSIZE_X - 30 * _2X) / 2 * (i % 2) * zoom;
						ao[NPC].y = y - (float)(336 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 6 * _2X) * (i / 2) * 1.2f * zoom;
						DrawPlayer(&ao[NPC], 2000 - 1 + LEVELUP_BACK0 + stageUpgradeMotion[i], ao[NPC].x, ao[NPC].y, false, zoom, false, false, false);

					}
					DrawCmfDetailShadow(enemyData[enemyHouse.crew[i] * ENEMYDATASIZE + ENEMYDATA_CMF], crewData[enemyHouse.crew[i] * 3 + 0], x + (float)(36 * _2X) * zoom + (float)(POPUPWINDOWSIZE_X - 30 * _2X) / 2 * (i % 2) * zoom, y - (float)(336 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 6 * _2X) * (i / 2) * 1.2f * zoom, RIGHT, enemyZoom[enemyHouse.crew[i]] * zoom);


					DrawStar(ICON_STAR, x + (float)(12 * _2X) * zoom + (float)(POPUPWINDOWSIZE_X - 30 * _2X) / 2 * (i % 2) * zoom + (float)90 * _2X * zoom, y - (float)(296 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 6 * _2X) * (i / 2) * 1.2f * zoom, curStar, curMaxStar, maxStar, CENTER, true, zoom);
					//√÷¥Î∞™ø° µµ¥ﬁ«œ∏È
					if (curStar == maxStar) {
						DrawMaxButton(x + (float)(12 * _2X) * zoom + (float)(POPUPWINDOWSIZE_X - 30 * _2X) / 2 * (i % 2) * zoom + (float)48 * _2X * zoom, y - (float)(292 * _2X + 20 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 6 * _2X) * (i / 2) * 1.2f * zoom, (float)(96 * _2X) * zoom, (float)(32 * _2X) * zoom, ALPHA_MAX, zoom);
					}
					else {
						DrawBuyButton(x + (float)(12 * _2X) * zoom + (float)(POPUPWINDOWSIZE_X - 30 * _2X) / 2 * (i % 2) * zoom + (float)48 * _2X * zoom, y - (float)(292 * _2X + 20 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 6 * _2X) * (i / 2) * 1.2f * zoom, (float)(96 * _2X) * zoom, (float)(32 * _2X) * zoom, frame, robin.gold < upgradePrice ? true : false, upgradePrice, CURRENCY_GOLD, zoom, false, false, false);
						//if (robin.gold >= upgradePrice)
						//	SetRectPoint(x + (float)(12 * _2X) * zoom + (float)(POPUPWINDOWSIZE_X - 30 * _2X) / 2 * (i % 2) * zoom + (float)48 * _2X * zoom, y - (float)(292 * _2X + 20 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 6 * _2X) * (i / 2) * 1.2f * zoom, (float)(96 * _2X) * zoom, (float)(32 * _2X) * zoom, TOUCH_FUNC_CREWUPGRADE + i);
					}

					if (stageUpgradeMotion[i] > 0 && stageUpgradeMotion[i] < 11) {
						DrawPlayer(&ao[NPC], 2000 - 1 + LEVELUP_FRONT0 + stageUpgradeMotion[i], ao[NPC].x, ao[NPC].y, false, zoom, false, false, false);

						DrawEffect(EFFECT_LEVELUP_TEXT0 - 1 + (stageUpgradeMotion[i] < 11 ? stageUpgradeMotion[i] : Max(11, stageUpgradeMotion[i] - 5)), ao[NPC].x, ao[NPC].y - (float)(16 * _2X) * zoom, 0, false, 1.0f);

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
			//º∫¡÷øÕ ¿œ±‚≈‰
			DrawTextButton(x + (float)(DX / 2 - 0 * _2X) * zoom, y - (float)(416 * _2X) * zoom, (float)(120 * _2X) * zoom, (float)(48 * _2X) * zoom, frame, totalStar < 10 || robin.bossRoom == true ? true : false, 1.0f, false, TEXT_LORD_DUEL);
			//if (totalStar < MAXSTARPERHOUSE || robin.bossRoom == true)
			//	grayScale = 32;
			DrawGoldAlpha(x + (float)(DX / 2 - 0 * _2X + 120 * _2X / 2) * zoom, y - (float)(416 * _2X + 22 * _2X) * zoom, ALPHA_BOSSDUEL, FONT_GOLD_LARGE, (float)zoom * 0.7f, CENTER, false, false);
			grayScale = 0;
			//if (totalStar == MAXSTARPERHOUSE && robin.bossRoom == false)
			//	SetRectPoint(x + (float)(DX / 2 - 0 * _2X) * zoom, y - (float)(416 * _2X) * zoom, (float)(120 * _2X) * zoom, (float)(48 * _2X) * zoom, TOUCH_FUNC_GOTOSTAGEBOSS);
		}

		BarDraw(&bar[BAR_GOLD], bar[BAR_GOLD].zoom);

		//¥∫Ω∫≈◊¿Ã¡ˆø° ¥Î«— ≥ªøÎ¿Ã ∂ﬂ∞Ì
		fontZoom = Max(1.2f, (float)(54 + MAXCREW * 3 + FPS / 2 - stageInfoCurFrame) * 0.2f / MOTIONDIV);

		if (stageInfoCurFrame > 54 + MAXCREW * 3)
			DrawGoldAlpha(DX / 2, DY / 2 + 248 * _2X, ALPHA_NEWSTAGE, FONT_GOLD_LARGE, fontZoom, CENTER, true, false);

		//∞‘¿”¿∏∑Œ µπæ∆∞£¥Ÿ.

		if (stageInfoCurFrame == 54 + MAXCREW * 3 + FPS * 3) {
			robin.bossRoom = false;
			memset(&robin.enemyObj, 0, sizeof(robin.enemyObj));
			robinmap = MAP_DIORAMA_TOLEM + castleOrder[robin.castle];
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


	//«ˆ¿Á ≈∏∞Ÿ∆√µ«¥¬ «œøÏΩ∫


	if (cur == true)
		stageInfoFrame++;
}

int GetCrewInventoryIdx(int type)
{
	int i = 0;

	for (i = 0; i < TOTALINVENTORY; i++) {
		if (robin.inven[i].type == ITEM_CREW && robin.inven[i].detail == GetCrewIdxFromType(type)) {
			return i;
		}
	}

	return false;
}
// √÷¡æ ±◊∏Æ±‚ «‘ºˆ
void CrewMenuDraw(int x, int y, float zoom)
{
	int i, j;
	float OUTTHICK = (float)5 * zoom;
	float INTTHICK = (float)5 * zoom;
	float WINX = (float)DX * zoom;
	float WINY = (float)(DY - (GNBHEIGHT) - (BOTTOMMENUHEIGHT - BOTTOMMENU_INIT_HEIGHT)) * zoom;
	int itemType, itemDetail, itemGrade, itemLv, itemStar;
	long itemCnt;
	
	//SetAlpha(24);
	MemRect(x, y, WINX, WINY, 0xD8D6FB);
	//SetAlpha(32);

	
	// 1. πË∞Ê π◊ ≈´ UI
	for (i = 0; i < 2; i++)
		DrawImage(crewMenuUiData[i * MENUUIDATACNT + 0], crewMenuUiData[i * MENUUIDATACNT + 1], crewMenuUiData[i * MENUUIDATACNT + 2], crewMenuUiData[i * MENUUIDATACNT + 3], x + (float)crewMenuUiData[i * MENUUIDATACNT + 4] * zoom, y - (float)(crewMenuUiData[i * MENUUIDATACNT + 5]) * zoom, false, false, false, false, false, zoom, sprite[crewMenuUiData[i * MENUUIDATACNT + 6]], crewMenuUiData[i * MENUUIDATACNT + 6]);

	CenterText(TEXT_BORDERGUARD, x + (float)160 * _2X * zoom, y - (float)40 * zoom, 2.0f * zoom);
	CenterText(TEXT_CREW_LISTEDIT, x + (float)160 * _2X * zoom, y - (float)90 * zoom, 1.1f * zoom);
	CenterText(TEXT_CREW_CURRENTLIST, x + (float)160 * _2X * zoom, y - (float)138 * zoom, 1.0f * zoom);
	
	//º∫∞˙ ∏∆Ω∫ ∫∞
	SetColor(COLOR_BROWN);
	for (i = 0; i < 4; i++) {
		DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, x + (float)(500) * zoom + (float)solidPosition[2 * i + 0] * 1 * _2X * zoom, y - (float)(12) * zoom + (float)solidPosition[2 * i + 1] * 1 * _2X * zoom, false, false, false, false, false, 0.1f * zoom, sprite[MAP_DIORAMA_IMG + CASTLE_ADELINE], MAP_DIORAMA_IMG + CASTLE_ADELINE);
	}
	SetColor(false);
	DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, x + (float)(500) * zoom, y - (float)(12) * zoom, false, false, false, false, false, 0.1f * zoom, sprite[MAP_DIORAMA_IMG + CASTLE_ADELINE], MAP_DIORAMA_IMG + CASTLE_ADELINE);
	//StarBarDraw(castleStarLimit[robin.castle], ICON_STAR, x + (float)(510) * zoom, y - (float)(92) * zoom, false, 0.6f * zoom, cvtDest, cvtLayer, buffering);

	//DrawImageScale(128, 128, 716, 609, x + (float)20 * zoom, y - (float)132 * zoom, false, false, false, false, false, 4.67f * zoom, 2.54f * zoom, sprite[UI_NEW_IMG], cvtDest, cvtLayer, UI_NEW_IMG, buffering);
	
	DrawImageScale(176, 40, 1, 679, x + (float)(232) * zoom, y - (float)120 * zoom, false, false, false, false, false, 1.0f * zoom, 1.0f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
	CenterText(TEXT_CREW_CURRENTLIST, x + (float)320 * zoom, y - (float)130 * zoom, zoom);

	int curTeamStar = 0;
	int crewInventoryIdx;
	for (i = 0; i < MAXCREW; i++) {
		if (robin.slotCrew[i] > -1) {
			crewInventoryIdx = GetCrewInventoryIdx(robin.slotCrew[i]);
			itemType = ITEM_CREW;
			itemDetail = robin.inven[crewInventoryIdx].detail;
			itemGrade = robin.inven[crewInventoryIdx].grade;
			curTeamStar += GetItemStar(itemType, itemDetail, itemGrade);
		}
	}

	DrawImageScale(176, 40, 1, 679, x + (float)(480) * zoom, y - (float)120 * zoom, false, false, false, false, false, 0.8f * zoom, 0.95f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
	DrawIcon(ICON_STAR, x + (float)(472) * zoom, y - (float)120 * zoom, 1.0f * zoom, COLOR_WHITE, false, false, 1 * _2X);
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%d/%d", curTeamStar, castleStarLimit[robin.castle]);
	CenterTextStr(tempStr, x + (float)568 * zoom, y - (float)128 * zoom, 1.0f * zoom);

	//ΩΩ∑‘ 6∞≥¬•∏Æ ¿ÃπÃ¡ˆ∏¶ ±◊∑¡¡ÿ¥Ÿ.
	
	DrawImage(1024, 220, 0, 217,
		x + WINX / 2 - (float)1024 / 2 * 0.61f * zoom, y - (float)168 * zoom,
		false, false, false, false, false,
		0.61f * zoom, sprite[SLOT_IMG], SLOT_IMG);

	//«ˆ¿Á º±≈√µ«æÓ ¿÷¥¬ ƒ≥∏Ø≈Õ 6∞≥
	for (i = 0; i < MAXCREW; i++) {
		int slotX = x + (float)(16 + 102 * (i % MAXCREW)) * zoom;
		int slotY = y - (float)(168 + 180 * (i / MAXCREW)) * zoom;

		//DrawButton(slotX + (float)(40) * zoom, slotY + (float)(24) * zoom, BUTTON_COLOR_BROWN, 64, false, TEXT_CATEGORY_ITEM_SWORD + i * 3, false, 0.4f * zoom, 0.8f * zoom, cvtDest, cvtLayer, buffering);
		memset(&tempStr, 0, sizeof(tempStr));

		if (robin.slotCrew[i] == -1) {
			
			float emphasisScale = (0.8f + sinf(frame * 0.05f) * 0.05f) * zoom;

			DrawPlusMark(
				slotX + (float)52 * zoom - (float)32 * emphasisScale,
				slotY - (float)72 * zoom + (float)32 * emphasisScale,
				emphasisScale);
		}
		else {
			itemType = ITEM_CREW;
			itemDetail = GetCrewIdxFromType(robin.slotCrew[i]);
			itemGrade = GRADE_NORMAL;
			itemLv = robin.inven[GetInvenIdx(itemType, itemDetail, itemGrade)].lv;
			itemStar = GetItemStar(itemType, itemDetail, itemGrade);

			int crewCmf = enemyData[crewData[itemDetail * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_CMF];
			int crewType = crewData[itemDetail * CREWDATASIZE + CREWDATA_TYPE];
			DrawCmfDetailShadow(crewCmf, crewPos[crewType * 5 + 0] + (menuX == i ? (frame / 2 / MOTIONDIV) % crewPos[crewType * 5 + 1] : 0),
				slotX + (float)52 * zoom,
				slotY - (float)88 * zoom,
				RIGHT, enemyZoom[crewType] * 1.3f * zoom);
			DrawStar(ICON_STAR, slotX + (float)52 * zoom, slotY - (float)102 * zoom, itemStar, itemStar, itemStar, CENTER, false, 0.6f * zoom);
			/*
			DrawItemCard(
				itemType,
				itemDetail,
				itemGrade,
				itemLv,
				false,
				slotX,
				slotY,
				TEXT_SOCKETING,
				0.70f * zoom,
				true,
				false,
				TOUCH_FUNC_MENUCUR_CREW1 + i,
				menuCur == i ? itemColor[frame % 6] : false,
				0,
				cvtDest,
				cvtLayer,
				buffering
			);
			*/
		}

		if (menuX == i) {
			MemRectFrameThick(
				slotX,
				slotY,
				(float)CARDSIZE_X * 0.45f * zoom,
				(float)CARDSIZE_Y * 0.4f * zoom,
				itemColor[frame / 2 % 6],
				1 * _2X);
		}
		else {
			SetRectPoint(
				slotX,
				slotY,
				(float)CARDSIZE_X * 0.45f * zoom,
				(float)CARDSIZE_Y * 0.4f * zoom,
				TOUCH_FUNC_MENUX_1 + i
			);
		}
	}
	


	//SetAlpha(32 - Abs(frame / MOTIONDIV % 32 - 16));
	//DrawImage(174, 138, 293, 870, x + (float)(50 + (182 * (menuCur % 3))) * zoom, y - (float)(160 + 136 * (menuCur / 3)) * zoom, false, false, false, false, false, 1.0f * zoom, sprite[MENU_CREW_IMG], cvtDest, cvtLayer, MENU_CREW_IMG, buffering);
	//SetAlpha(32);

	// 2. ≈©∑Á ∏ÆΩ∫∆Æ
	SetSectionClip(0, y - (float)320 * zoom, DX, WINY - (float)340 * zoom, false);

	curHero = ROBIN;

	int itemInvenIdxList[TOTALINVENTORY];

	j = 0;
	for (i = 0; i < TOTALINVENTORY; i++) {
		if (robin.inven[i].type == ITEM_CREW) {
			itemInvenIdxList[j] = i;
			j++;
		}
	}

	int INVENTORY_COL_CNT = 4;

	for (i = 0; i < j; i++) {
		int col = i % INVENTORY_COL_CNT;
		int row = i / INVENTORY_COL_CNT;

		int cardX = x + (float)(INVENTORY_X + INVENTORY_GAP_X * col) * zoom;
		int cardY = y - (float)(320 + (CREW_GAP_Y) * row - scY[MENU_CREW]) * zoom;

		itemType = robin.inven[itemInvenIdxList[i]].type;
		itemDetail = robin.inven[itemInvenIdxList[i]].detail;
		itemGrade = robin.inven[itemInvenIdxList[i]].grade;
		itemLv = robin.inven[itemInvenIdxList[i]].lv;
		itemCnt = robin.inven[itemInvenIdxList[i]].count;
		
		DrawItemCard(
			itemType,
			itemDetail,
			itemGrade,
			itemLv,
			itemCnt,
			false,
			cardX,
			cardY,
			itemLv == 0 ? TEXT_NOTACQUIRED : TEXT_EQUIP,
			CARDDEFAULTZOOM* zoom,
			false,
			false,
			menuDepth == 0 ? TOUCH_FUNC_ITEMDETAIL + itemInvenIdxList[i] : false,
			//itemLv > 0 ? TOUCH_FUNC_EQUIP_INVENTORY + itemInvenIdxList[i] : false,
			//menuDepth == 0 ? TOUCH_FUNC_ITEMDETAIL + itemInvenIdxList[i] + i : false,
			false,
			0);

		//ÌäúÌÜ†Î¶¨Ïñº: ÏÉàÎ°ú ÏñªÏùÄ ÎèôÎ£å Ïπ¥ÎìúÎßå Î∞ùÍ≤å ÎÇ®Í∏∞Í≥† ÎÇòÎ®∏ÏßÄÎ•º Ïñ¥Îë°Í≤å ÎçÆÎäîÎã§.
		//ÏÇ¨Í∞ÅÌòïÏùÄ DrawItemCard()Í∞Ä Ïπ¥Îìú ÌÑ∞ÏπòÏòÅÏó≠ÏúºÎ°ú Îì±Î°ùÌïòÎäî Í≤ÉÍ≥º Í∞ôÏùÄ Í∞íÏù¥Îã§.
		if (GetTutorialCrewCardTouchFunc() == TOUCH_FUNC_ITEMDETAIL + itemInvenIdxList[i]) {
			int itemStar = GetItemStar(itemType, itemDetail, itemGrade);
			float cardZoom = CARDDEFAULTZOOM * zoom;
			float rx = cardX + (float)equipBgData[(itemStar - 1) * 6 + 4] * cardZoom;
			float ry = cardY - (float)equipBgData[(itemStar - 1) * 6 + 5] * cardZoom;
			float rw = (float)equipBgData[(itemStar - 1) * 6 + 0] * cardZoom;
			float rh = (float)equipBgData[(itemStar - 1) * 6 + 1] * cardZoom;
			float pulse = 1.0f + sinf((float)frame * 0.1f) * 0.06f;

			//ÏÜêÏùÄ Ïπ¥Îìú ÌïúÍ∞ÄÏö¥Îç∞Ïóê, ÌÅ¨Í≤å.
			//DrawHand()ø° ≥—±‚¥¬ ¡¬«•∞° º’ ±◊∏≤¿« ¡¬ªÛ¥‹¿Ã∂Û, ¡ﬂæ”¿ª ±◊≥… ¡÷∏È º’¿Ã
			//¡ﬂæ”ø°º≠ ø¿∏•¬  æ∆∑°∑Œ ª∏¥¬¥Ÿ. ¿⁄±‚ ≈©±‚∏∏≈≠ øﬁ¬ /¿ß∑Œ π∞∑¡ º’≥°¿Ã ¡ﬂæ”ø° ø¿∞‘ «—¥Ÿ.
			float handZoom = 2.4f;
			float handW = (float)imgArray[IMG_HAND1 * 4 + 2] * handZoom;
			float handH = (float)imgArray[IMG_HAND1 * 4 + 3] * handZoom;

			DrawHand(rx + rw / 2 - handW, ry - rh / 2 + handH, robin.playtime / MOTIONDIV, handZoom);

			//Ïπ¥ÎìúÎäî Ìè≠ rw, Í∞ÄÎ°ú Í∞ÑÍ≤©ÏùÄ INVENTORY_GAP_X * zoomÏù¥Îùº Ïπ¥Îìú ÏÇ¨Ïù¥ Ïó¨Î∞±Ïù¥ Í±∞Ïùò ÏóÜÎã§.
			//Î∞òÍ≤ΩÏùÑ Ïπ¥Îìú ÎÜíÏù¥ Í∏∞Ï§ÄÏúºÎ°ú Ïû°ÏúºÎ©¥ ÏòÜ Ïπ¥ÎìúÍπåÏßÄ ÌÜµÏß∏Î°ú Î∞ùÏïÑÏßÄÎØÄÎ°ú Ìè≠ Í∏∞Ï§ÄÏúºÎ°ú Ïû°ÎäîÎã§.
			//ÏòÜ Ïπ¥ÎìúÏùò ÏïàÏ™Ω Î™®ÏÑúÎ¶¨ÍπåÏßÄÍ∞Ä Ï§ëÏã¨ÏóêÏÑú (INVENTORY_GAP_X - 240 * CARDDEFAULTZOOM / 2) * zoom
			//Ïù¥ÎØÄÎ°ú Í∑∏ ÏïàÏ™ΩÏóêÏÑú Í∞êÏá†Í∞Ä ÎÅùÎÇòÎèÑÎ°ù ÎëîÎã§.
			SetSpotlight(rx + rw / 2, ry - rh / 2,
				rw * 0.34f * pulse, rw * 0.60f * pulse, 0.25f);
		}
	}

	int scrollH = WINY - (float)340 * zoom;

	DrawScroll(
		x + (float)612 * zoom,
		y - (float)320 * zoom,
		scrollH,
		MENU_CREW);

	UnSectionClip(false);

	//√÷ø‹∞¢ ≈◊µŒ∏Æ
	MemRectFrameThick(x, y, WINX, WINY, 0x2C2578, (float)OUTTHICK * zoom);
	//±◊æ»ø° ≈◊µŒ∏Æ
	MemRectFrameThick(x + OUTTHICK, y - OUTTHICK, WINX - 2 * OUTTHICK, WINY - 2 * OUTTHICK, 0x7653D3, INTTHICK);

	switch (menuDepth) {
	case 1:
		ResetRectPoint();
		//ScreenDarken(SCREENDARKEN);
		MemRect(x, y, WINX, WINY, 0xD8D6FB);
		// 1. πË∞Ê π◊ ≈´ UI
		for (i = 0; i < 2; i++)
			DrawImage(crewMenuUiData[i * MENUUIDATACNT + 0], crewMenuUiData[i * MENUUIDATACNT + 1], crewMenuUiData[i * MENUUIDATACNT + 2], crewMenuUiData[i * MENUUIDATACNT + 3], x + (float)crewMenuUiData[i * MENUUIDATACNT + 4] * zoom, y - (float)(crewMenuUiData[i * MENUUIDATACNT + 5]) * zoom, false, false, false, false, false, zoom, sprite[crewMenuUiData[i * MENUUIDATACNT + 6]], crewMenuUiData[i * MENUUIDATACNT + 6]);

		CenterText(TEXT_BORDERGUARD, x + (float)160 * _2X * zoom, y - (float)40 * zoom, 2.0f * zoom);
		CenterText(TEXT_ACTIONCARDINFO, x + (float)160 * _2X * zoom, y - (float)90 * zoom, 1.1f * zoom);

		//CenterText(TEXT_CREW_LISTEDIT, x + (float)160 * _2X * zoom, y - (float)90 * zoom, 1.1f * zoom, cvtDest, cvtLayer, buffering);
		//CenterText(TEXT_CREW_CURRENTLIST, x + (float)160 * _2X * zoom, y - (float)138 * zoom, 1.0f * zoom, cvtDest, cvtLayer, buffering);

		ItemDetailDraw(&robin.inven[menuItem], x + (float)16 * zoom, y - (float)152 * zoom, CARDDEFAULTZOOM * 1.2f * zoom, false, false);
		
		DrawTouchLargeButton(x + (float)(80) * zoom, y - (float)(694) * zoom, BUYBUTTON_X, BUYBUTTON_Y, textId[TEXT_EQUIP], TOUCH_FUNC_EQUIP_INVENTORY + GetInvenIdx(robin.inven[menuItem].type, robin.inven[menuItem].detail, robin.inven[menuItem].grade), FRAME_GREEN, 1.0f * zoom);
		DrawTouchLargeButton(x + (float)(380) * zoom, y - (float)(694) * zoom, BUYBUTTON_X, BUYBUTTON_Y, textId[TEXT_UPGRADE], TOUCH_FUNC_EQUIP_INVENTORY + GetInvenIdx(robin.inven[menuItem].type, robin.inven[menuItem].detail, robin.inven[menuItem].grade), FRAME_RED, 1.0f * zoom);

		//Tutorial: pulse a highlight around the EQUIP button while the EQUIP step is guiding the player to tap it.
		if (robin.demoSeen[DEMO_TUTORIAL_EQUIP] && !robin.demoSeen[DEMO_TUTORIAL_HEARTBET]) {
			float pulse = 0.9f + sinf((float)frame * 0.1f) * 0.1f;
			float hlW = (float)BUYBUTTON_X * zoom * pulse;
			float hlH = (float)BUYBUTTON_Y * zoom * pulse;
			MemRectFrameThick(x + (float)(80) * zoom - (hlW - (float)BUYBUTTON_X * zoom) / 2, y - (float)(694) * zoom - (hlH - (float)BUYBUTTON_Y * zoom) / 2, hlW, hlH, COLOR_YELLOW, (int)(3 * _2X));
		}

		//√÷ø‹∞¢ ≈◊µŒ∏Æ
		MemRectFrameThick(x, y, WINX, WINY, 0x2C2578, (float)OUTTHICK* zoom);
		//±◊æ»ø° ≈◊µŒ∏Æ
		MemRectFrameThick(x + OUTTHICK, y - OUTTHICK, WINX - 2 * OUTTHICK, WINY - 2 * OUTTHICK, 0x7653D3, INTTHICK);

		break;
	}
	BarDraw(&bar[BAR_GOLD], bar[BAR_GOLD].zoom);
	//BarDraw(&bar[BAR_STAR], bar[BAR_STAR].zoom, cvtDest, cvtLayer, buffering);

}

void CrewPannelDraw(int crewIdx, int x, int y, float zoom)
{
	SetRectPoint(x + (float)120 * zoom, y - (float)60 * zoom, (float)179 * zoom, (float)48 * zoom, TOUCH_FUNC_MENUCUR_CREWSET + crewIdx);

}

bool IsCrewSet(int crewIdx)
{
	int i;
	for (i = 0; i < MAXCREW; i++) {
		if (robin.slotCrew[i] == crewData[crewIdx * CREWDATASIZE + CREWDATA_TYPE])
			return true;
	}
	return false;
}

void DrawButton(int x, int y, int color, int size, int icon, int text, bool ani, float zoomX, float zoomY)
{
	float zoom = zoomY;
	//∆–≥Œ ±◊∏Æ±‚
	//DrawImage(buttonImgData[color * BUTTON_TOTALSIZE * 5 + size * 5 + 0], buttonImgData[color * BUTTON_TOTALSIZE * 5 + size * 5 + 1], buttonImgData[color * BUTTON_TOTALSIZE * 5 + size * 5 + 2], buttonImgData[color * BUTTON_TOTALSIZE * 5 + size * 5 + 3], x, y, false, false, false, false, false, zoom, sprite[buttonImgData[color * BUTTON_TOTALSIZE * 5 + size * 5 + 4]], cvtDest, cvtLayer, buttonImgData[color * BUTTON_TOTALSIZE * 5 + size * 5 + 4], buffering);
	DrawImageScale(buttonImgData[color * 5 + 0], buttonImgData[color * 5 + 1], buttonImgData[color * 5 + 2], buttonImgData[color * 5 + 3], x, y, false, false, false, false, false, zoomX, zoomY, sprite[buttonImgData[color * 5 + 4]], buttonImgData[color * 5 + 4]);

	//æ∆¿Ãƒ‹ ±◊∏Æ±‚(¿œ¥‹ ª˝∑´)

	//≈ÿΩ∫∆Æ ±◊∏Æ±‚
	if (text > 0) {
		SetFontColor(COLOR_WHITE);
		CenterText(text, x + (float)buttonImgData[color * 5 + 0] / 2 * zoomX, y - (float)3 * _2X * zoom, 1.2f * zoom);
	}
}

void DrawEquipItemCard(int itemType, int itemDetail, int itemGrade, int itemLv, int itemCnt, int x, int y, float zoom)
{
	int i;
	int star = GetItemStar(itemType, itemDetail, itemGrade);
	int width;
	int repItem = 0;
	int setItemCnt = 0;
	int rewardIcon;
	ITEM* it;
	OBJECT* pObj = &ao[curHero];
	long long realValue;
	float numWidth = (float)(32 * _2X) * zoom;
	DrawRewardCard(itemType, itemDetail, itemGrade, itemLv, itemCnt, x, y, false, zoom, true, false, true, star, star, star, 0);
}

void DrawItemCardBack(
	int itemStar,
	int x,
	int y,
	float zoom,
	int backFrame)
{
	const int CARD_BACK_W = 240;
	const int CARD_BACK_H = 332;
	const int CARD_BACK_COL = 4;

	int frameIdx =
		backFrame - 1;

	int xs =
		(frameIdx % CARD_BACK_COL) *
		CARD_BACK_W;

	int ys =
		(frameIdx / CARD_BACK_COL) *
		CARD_BACK_H;

	float frontX =
		x +
		(float)equipBgData[
			(itemStar - 1) * 6 + 4
		] * zoom;

	float frontY =
		y -
		(float)equipBgData[
			(itemStar - 1) * 6 + 5
		] * zoom;

	float frontW =
		(float)equipBgData[
			(itemStar - 1) * 6 + 0
		] * zoom;

	float frontH =
		(float)equipBgData[
			(itemStar - 1) * 6 + 1
		] * zoom;

	float scaleX =
		frontW /
		(float)CARD_BACK_W;

	float scaleY =
		frontH /
		(float)CARD_BACK_H;

	DrawImageScale(
		CARD_BACK_W,
		CARD_BACK_H,
		xs,
		ys,

		frontX,
		frontY,

		false,
		false,
		false,
		false,
		false,

		scaleX,
		scaleY,

		sprite[CARDBACK_IMG],

		CARDBACK_IMG);
}

void DrawItemCard(
	int itemType,
	int itemDetail,
	int itemGrade,
	int itemLv,
	long itemCnt,
	bool empty,
	int x,
	int y,
	int text,
	float zoom,
	bool ani,
	int buttonTouchFunc,
	int cardTouchFunc,
	int selectedFrame,
	int backFrame)
{
	int i;
	int itemStar = 1;
	int invenIdx = 0;
	int bgIndex = crewData[itemDetail * CREWDATASIZE + CREWDATA_CARDBG];


	//--------------------------------------------------------
	// ƒ´µÂ µﬁ∏È ∞¯∞≥ æ÷¥œ∏ﬁ¿Ãº«
	//
	// backFrame
	// 0   : ±‚¡∏ ƒ´µÂ æ’∏È
	// 1~7 : CARD_IMG¿« 0~6π¯ µﬁ∏È ¿ÃπÃ¡ˆ
	//--------------------------------------------------------
	if (backFrame >= 1 && backFrame <= 7)
	{
		DrawItemCardBack(
			itemStar,
			x,
			y,
			zoom,
			backFrame);

		return;
	}

	if (empty == false)
		itemStar = GetItemStar(itemType, itemDetail, itemGrade);

	invenIdx = GetInvenIdx(itemType, itemDetail, itemGrade);

	DrawImageScale(
		198,
		288,
		198 * (bgIndex % 5),
		288 * (bgIndex / 5),
		x + (float)18 * zoom,
		y - (float)22 * zoom,
		false, false, false, false, false,
		1.02f * zoom,
		zoom,
		sprite[CARDBG_IMG],
		CARDBG_IMG);

	DrawImageScale(
		equipBgData[(itemStar - 1) * 6 + 0],
		equipBgData[(itemStar - 1) * 6 + 1],
		equipBgData[(itemStar - 1) * 6 + 2],
		equipBgData[(itemStar - 1) * 6 + 3],
		x + (float)equipBgData[(itemStar - 1) * 6 + 4] * zoom,
		y - (float)equipBgData[(itemStar - 1) * 6 + 5] * zoom,
		false, false, false, false, false,
		zoom,
		zoom,
		sprite[CARD_IMG],
		CARD_IMG);

	SetColor(false);

	if (selectedFrame) {
		MemRectFrameThick(
			x + (float)equipBgData[(itemStar - 1) * 6 + 4] * zoom,
			y - (float)(equipBgData[(itemStar - 1) * 6 + 5] + 8) * zoom,
			equipBgData[(itemStar - 1) * 6 + 0] * zoom,
			(equipBgData[(itemStar - 1) * 6 + 1] - 8) * zoom,
			selectedFrame,
			1 * _2X);
	}

	if (empty) {
		DrawPlusMark(
			x + (float)88 * zoom,
			y - (float)72 * zoom,
			1.45f * zoom);
	}
	else {
		//«ˆ¿Á «√∑π¿Ã∏ﬁ¥∫∏È ±Ó∏ƒ∞‘, æ∆¥œ∏È »πµÊ√¢¿Ã¥œ±Ó ∫∏ø©¡ÿ¥Ÿ.
		if (itemLv == 0 && drawHandle == MD_PLAY)
			SetColor(COLOR_BLACK);
			//grayScale = 32;

		if (itemType == ITEM_CREW) {
			int crewCmf = enemyData[crewData[itemDetail * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_CMF];
			int crewType = crewData[itemDetail * CREWDATASIZE + CREWDATA_TYPE];
			DrawCmfDetailShadow(crewCmf, crewPos[crewType * 5 + 0] + (ani == true ? (frame / 2 / MOTIONDIV) % crewPos[crewType * 5 + 1] : 0),
				x + (float)120 * zoom,
				y - (float)240 * zoom, 
				RIGHT, enemyZoom[crewType] * 2.2f * zoom);
		}
		else {
			DrawIcon(
				GetItemIcon(itemType, itemDetail, itemGrade),
				x + (float)72 * zoom,
				y - (float)122 * zoom,
				3.3f * zoom,
				COLOR_BROWN,
				false,
				true,
				(float)1 * zoom);
		}

		SetColor(false);
		grayScale = 0;

		if (itemLv == 0) {
			if (drawHandle == MD_PLAY)
				CenterTextStr("?", x + (float)(120) * zoom, y - (float)(146) * zoom, 2.7f * zoom);
		
			//SetAlpha(24);
			//MemRect(x + (float)4 * zoom, y - (float)128 * zoom, (float)120 * zoom, (float)24 * zoom, 0x333333, cvtDest, cvtLayer, buffering);
			//SetAlpha(32);
			memset(&tempStr, 0, sizeof(tempStr));
			if (itemType == ITEM_CREW)
				sprintf(tempStr, "%s", textId[TEXT_MONSTERNAME_START + crewData[itemDetail * CREWDATASIZE + CREWDATA_TYPE]]);
			else
				sprintf(tempStr, "%s", textId[TEXT_ITEMNAME_START + GetItemName(itemType, itemDetail, itemGrade)]);
			CenterTextStr(tempStr, x + (float)(120) * zoom, y - (float)(268) * zoom, 1.3f * zoom);

		}
		else {
			//SetAlpha(24);
			//MemRect(x + (float)16 * zoom, y - (float)234 * zoom, (float)108 * zoom, (float)32 * zoom, 0x333333, cvtDest, cvtLayer, buffering);
			//SetAlpha(32);
			//memset(&tempStr, 0, sizeof(tempStr));
			//sprintf(tempStr, "LV %d", itemLv);
			//CenterTextStr(tempStr, x + (float)(120) * zoom, y - (float)(240) * zoom, 1.0f * zoom, cvtDest, cvtLayer, buffering);

			////CenterText(text, x + (float)72 * zoom, y - (float)132 * zoom, zoom, cvtDest, cvtLayer, buffering);
			////DrawRoundBar(x + (float)8 * zoom, y - (float)132 * zoom, 0.25f, ROUNDBAR_BIG, BARCOLOR_YELLOW, false, 0.25f * zoom, cvtDest, cvtLayer, buffering);
			////DrawImageScale(176, 40, 1, 679, x + (float)200 * zoom, y - (float)(132 + 12) * zoom, false, false, false, false, false, 1.2f * zoom, 1.2f * zoom, sprite[UI_NEW_IMG], cvtDest, cvtLayer, UI_NEW_IMG, buffering);
			DrawImageScale(222, 46, 0, 664 + 46 * (itemStar - 1), x + (float)24 * zoom, y - (float)(268) * zoom, false, false, false, false, false, 0.9f * zoom, 0.9f * zoom, sprite[CARD_IMG], CARD_IMG);
			memset(&tempStr, 0, sizeof(tempStr));
			sprintf(tempStr, "%d/%d", robin.inven[invenIdx].count, upgradeCostCrew[itemStar - 1][itemLv * 2 + 0]);

			SetFontColor(COLOR_WHITE);
			CenterTextStr(tempStr, x + (float)120 * zoom, y - (float)(268 + 4) * zoom, 1.3f * zoom);

			float yScale = 1.05f + 0.35f * sinf(frame * 0.18f - 1.57f);

			if (robin.inven[invenIdx].count < upgradeCostCrew[itemStar - 1][itemLv * 2 + 0])
				yScale = 1.0f;

			SetColor(COLOR_BLACK);
			for (i = 0; i < 4; i++) {
				DrawImageScale(56, 70, 223 + (itemStar - 1) * 56, 731, x + (float)4 * _2X * zoom + (float)solidPosition[2 * i + 0] * 1 * _2X * zoom, y - (float)(174 - 55 * 0.5f * yScale) / 0.55f * zoom + (float)solidPosition[2 * i + 1] * 1 * _2X * zoom, false, false, false, false, false, 0.7f * zoom, 0.6f * yScale * zoom, sprite[CARD_IMG], CARD_IMG);
			}
			SetColor(false);
			DrawImageScale(56, 70, 223 + (itemStar - 1) * 56, 731, x + (float)4 * _2X * zoom, y - (float)(174 - 55 * 0.5f * yScale) / 0.55f * zoom, false, false, false, false, false, 0.7f * zoom, 0.6f * yScale * zoom, sprite[CARD_IMG], CARD_IMG);

		}

		switch (itemType) {
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
				DrawStar(
					ICON_STAR,
					x + (float)120 * zoom,
					y - (float)50 * zoom,
					GetItemStar(itemType, itemDetail, itemGrade),
					GetItemStar(itemType, itemDetail, itemGrade),
					GetItemStar(itemType, itemDetail, itemGrade),
					CENTER,
					false,
					1.0f * zoom);
				break;
			default:
				//------------------------------------------------
		// «œ∆Æ ºˆ∑Æ
		//------------------------------------------------
				DrawGoldNum(
					itemCnt,  // æ∆∑° º≥∏Ì ¬¸∞Ì

					x + (float)120 * zoom,
					y - (float)50 * zoom,

					CENTER,
					false,
					false,
					true,
					1.0f * zoom);
				break;
		}
		
	}

	
	if (cardTouchFunc) {
		SetRectPoint(x + (float)equipBgData[(itemStar - 1) * 6 + 4] * zoom,
			y - (float)equipBgData[(itemStar - 1) * 6 + 5] * zoom,
			(float)equipBgData[(itemStar - 1) * 6 + 0] * zoom,
			(float)equipBgData[(itemStar - 1) * 6 + 1] * zoom,
			cardTouchFunc);
	}
	if (buttonTouchFunc) {
		SetRectPoint(x + (float)equipBgData[(itemStar - 1) * 6 + 4] * zoom,
			y - (float)equipBgData[(itemStar - 1) * 6 + 5] * zoom - (float)equipBgData[(itemStar - 1) * 6 + 1] * zoom * 3 / 4,
			(float)equipBgData[(itemStar - 1) * 6 + 0] * zoom,
			(float)equipBgData[(itemStar - 1) * 6 + 1] * zoom / 4,
			buttonTouchFunc);
	}
}

void CollectionsDraw(int x, int y, float zoom)
{
	int i, j;
	float OUTTHICK = (float)5 * zoom;
	float INTTHICK = (float)5 * zoom;
	float WINX = (float)DX * zoom;
	float WINY = (float)(DY - (GNBHEIGHT)-(BOTTOMMENUHEIGHT - BOTTOMMENU_INIT_HEIGHT)) * zoom;
	
	int w = COLLECTIONCARDSIZE_X;
	int h = COLLECTIONCARDSIZE_Y;
	int star = 1;
	int width;
	int repItem = 0;
	int setItemCnt = 0;
	int rewardIcon;
	int itemType, itemDetail, itemGrade, itemLv, itemCnt, itemSlot, itemIdx, itemIcon, itemStar;
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

	MemRect(x, y, WINX, WINY, 0x3B2513);

	for (i = 0; i < 2; i++)
		DrawImage(equipMenuUiData[i * MENUUIDATACNT + 0], equipMenuUiData[i * MENUUIDATACNT + 1], equipMenuUiData[i * MENUUIDATACNT + 2], equipMenuUiData[i * MENUUIDATACNT + 3], x + (float)equipMenuUiData[i * MENUUIDATACNT + 4] * zoom, y - (float)(equipMenuUiData[i * MENUUIDATACNT + 5]) * zoom, false, false, false, false, false, zoom, sprite[equipMenuUiData[i * MENUUIDATACNT + 6]], equipMenuUiData[i * MENUUIDATACNT + 6]);

	CenterText(TEXT_EQUIPMENT, x + (float)160 * _2X * zoom, y - (float)48 * zoom, 2.0f * zoom);
	CenterText(TEXT_EQUIP_LISTEDIT, x + (float)160 * _2X * zoom, y - (float)100 * zoom, 1.1f * zoom);
	//CenterText(TEXT_CREW_CURRENTLIST, x + (float)160 * _2X * zoom, y - (float)138 * zoom, 1.0f * zoom, cvtDest, cvtLayer, buffering);

	DrawImageScale(128, 128, 716, 874, x + (float)8 * zoom, y - (float)124 * zoom, false, false, false, false, false, (float)(WINX - 16) / 128 * zoom, (float)(WINY - 132) / 128 * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);

	DrawImageScale(128, 128, 587, 608, x + (float)32 * zoom, y - (float)142 * zoom, false, false, false, false, false, (float)3.4f * zoom, (float)2.8f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);

	for (i = 0; i < EQUIP_NECK; i++) {
		int slotX = x + (float)(52 + 144 * (i % 3)) * zoom;
		int slotY = y - (float)(160 + 180 * (i / 3)) * zoom;

		memset(&tempStr, 0, sizeof(tempStr));

		DrawButton(slotX + (float)(20) * zoom, slotY + (float)(24) * zoom, BUTTON_COLOR_BROWN, 64, false, TEXT_CATEGORY_ITEM_SWORD + i * 3, false, 0.4f * zoom, 0.8f * zoom);

		if (ao[ROBIN].equip[i].type == EMPTY) {
			DrawItemCard(
				EMPTY,
				0,
				0,
				0,
				0,
				true,
				slotX,
				slotY,
				TEXT_NOTACQUIRED,
				CARDDEFAULTZOOM * 0.8f * zoom,
				false,
				false,
				menuX != i ? TOUCH_FUNC_MENUX_1 + i : 0,
				menuX == i ? itemColor[frame % 6] : false,
				0);
		}
		else {
			itemType = i * 3;
			itemDetail = ao[ROBIN].equip[i].detail;
			itemGrade = ao[ROBIN].equip[i].grade;
			itemLv = ao[ROBIN].equip[i].lv;
			itemCnt = 1;

			DrawItemCard(
				itemType,
				itemDetail,
				itemGrade,
				itemLv,
				itemCnt,
				false,
				slotX,
				slotY,
				TEXT_SOCKETING,
				CARDDEFAULTZOOM * 0.8f * zoom,
				false,
				false,
				TOUCH_FUNC_ITEMDETAIL + GetInvenIdx(itemType, itemDetail, itemGrade),
				menuX == i ? itemColor[frame % 6] : false,
				0);
		}

		
	}

	DrawImageScale(128, 128, 587, 608, x + (float)476 * zoom, y - (float)142 * zoom, false, false, false, false, false, 1.0f * zoom, 1.0f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
	DrawPlayer(&ao[ROBIN], 0, x + (float)(476 + 128 / 2) * zoom, y - (float)242 * zoom, LEFT, 1.5f * zoom, false, false, true);

	DrawImageScale(128, 128, 587, 608, x + (float)476 * zoom, y - (float)280 * zoom, false, false, false, false, false, 1.0f * zoom, 1.7f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);

	//∞¯∞›∑¬
	itemType = ITEM_SWORD;
	itemDetail = ao[ROBIN].equip[EQUIP_WEAPON].detail;
	itemGrade = ao[ROBIN].equip[EQUIP_WEAPON].grade;
	DrawImageScale(64, 64, 455, 709, x + (float)(476 + 8) * zoom, y - (float)(220 + 16 + 70) * zoom, false, false, false, false, false, 0.6f * zoom, 0.6f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
	//DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), x + (float)(476 + 8) * zoom, y - (float)(220 + 12 + 70) * zoom, 1.2f * zoom, false, false, true, (float)1.0f * zoom, cvtDest, cvtLayer, buffering);
	
	SetFontColor(COLOR_GREY);
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s@+%d", textId[TEXT_ATK], ao[ROBIN].ps[PS_DMG]);
	LineTextStrSolid(tempStr, x + (float)(476 + 8 + 46) * zoom, y - (float)(220 + 10 + 70) * zoom, (float)108 * zoom, -1, -1, zoom);
	SetFontColor(COLOR_WHITE);
	//πÊæÓ∑¬
	itemType = ITEM_ARMOR;
	itemDetail = ao[ROBIN].equip[EQUIP_ARMOR].detail;
	itemGrade = ao[ROBIN].equip[EQUIP_ARMOR].grade;
	DrawImageScale(64, 64, 520, 709, x + (float)(476 + 8) * zoom, y - (float)(220 + 16 + 70 * 2) * zoom, false, false, false, false, false, 0.6f * zoom, 0.6f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
	//DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), x + (float)(476 + 8) * zoom, y - (float)(220 + 12 + 70 * 2) * zoom, 1.2f * zoom, false, false, true, (float)1.0f * zoom, cvtDest, cvtLayer, buffering);

	SetFontColor(COLOR_GREY);
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s@+%d", textId[TEXT_DEF], ao[ROBIN].ps[PS_ARMOR]);
	LineTextStrSolid(tempStr, x + (float)(476 + 8 + 46) * zoom, y - (float)(220 + 10 + 70 * 2) * zoom, (float)108 * zoom, -1, -1, zoom);
	SetFontColor(COLOR_WHITE);
	//√º∑¬
	DrawImageScale(64, 64, 390, 709, x + (float)(476 + 8) * zoom, y - (float)(220 + 16 + 70 * 3) * zoom, false, false, false, false, false, 0.6f * zoom, 0.6f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
	//DrawIcon(ICON_HEART, x + (float)(476 + 8) * zoom, y - (float)(220 + 12 + 70 * 3) * zoom, 1.2f * zoom, false, false, true, (float)1.0f * zoom, cvtDest, cvtLayer, buffering);
	
	SetFontColor(COLOR_GREY);
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s@+%d", textId[TEXT_HERO_PARAM_HP], ao[ROBIN].ps[PS_HP]);
	LineTextStrSolid(tempStr, x + (float)(476 + 8 + 46) * zoom, y - (float)(220 + 10 + 70 * 3) * zoom, (float)108 * zoom, -1, -1, zoom);
	SetFontColor(COLOR_WHITE);

	// 2. æ∆¿Ã≈€ ƒ´≈◊∞Ì∏Æ ∏ÆΩ∫∆Æ
	
	for (i = 0; i < EQUIP_NECK; i++) {
		itemType = ITEM_SWORD + i * 3;
		itemDetail = ao[ROBIN].equip[i].detail;
		itemGrade = ao[ROBIN].equip[i].grade;

		DrawButton(x + (float)(34 + i * 96) * zoom, y - (float)(508) * zoom, menuX == i ? BUTTON_COLOR_PURPLE : BUTTON_COLOR_BROWN, 64, GetItemIcon(itemType, itemGrade, itemDetail), TEXT_CATEGORY_ITEM_SWORD + itemType, false, 0.5f * zoom, 1.0f * zoom);
		if (menuX != i)
			SetRectPoint(x + (float)(34 + i * 96) * zoom, y - (float)(508) * zoom, (float)80 * zoom, (float)48 * zoom, TOUCH_FUNC_MENUX_1 + i);
	}

	// 3. ¿Â∫Ò ∏ÆΩ∫∆Æ
	SetSectionClip(0, y - (float)560 * zoom, DX, WINY - (float)600 * zoom, false);

	curHero = ROBIN;

	int itemInvenIdxList[TOTALINVENTORY];


	j = 0;
	for (i = 0; i < TOTALINVENTORY; i++) {
		if (robin.inven[i].type == menuX * TOTALCHAR) {
			itemInvenIdxList[j] = i;
			j++;
		}
	}

	int INVENTORY_COL_CNT = 4;

	for (i = 0; i < j; i++) {
		int col = i % INVENTORY_COL_CNT;
		int row = i / INVENTORY_COL_CNT;

		int cardX = x + (float)(INVENTORY_X + INVENTORY_GAP_X * col) * zoom;
		int cardY = y - (float)(560 + INVENTORY_GAP_Y * row - scY[MENU_COLLECTIONS]) * zoom;

		itemType = robin.inven[itemInvenIdxList[i]].type;
		itemDetail = robin.inven[itemInvenIdxList[i]].detail;
		itemGrade = robin.inven[itemInvenIdxList[i]].grade;
		itemLv = robin.inven[itemInvenIdxList[i]].lv;

		DrawItemCard(
			itemType,
			itemDetail,
			itemGrade,
			itemLv,
			itemCnt,
			false,
			cardX,
			cardY,
			itemLv == 0 ? TEXT_NOTACQUIRED : TEXT_EQUIP,
			CARDDEFAULTZOOM * 0.9f * zoom,
			false,
			itemLv > 0 ? TOUCH_FUNC_EQUIP_INVENTORY + itemInvenIdxList[i] : false,
			menuDepth == 0 ? TOUCH_FUNC_ITEMDETAIL + itemInvenIdxList[i] : false,
			false,
			0);
	}

	int scrollH = WINY - (float)580 * zoom;

	DrawScroll(
		x + (float)612 * zoom,
		y - (float)560 * zoom,
		scrollH,
		MENU_COLLECTIONS);

	UnSectionClip(false);

	//√÷ø‹∞¢ ≈◊µŒ∏Æ
	MemRectFrameThick(x, y, WINX, WINY, 0x271910, (float)OUTTHICK * zoom);
	//±◊æ»ø° ≈◊µŒ∏Æ
	MemRectFrameThick(x + OUTTHICK, y - OUTTHICK, WINX - 2 * OUTTHICK, WINY - 2 * OUTTHICK, 0x5F4022, INTTHICK);

	switch (menuDepth) {
		case 1:
			ResetRectPoint();
			MemRect(x, y, WINX, WINY, 0x3B2513);

			for (i = 0; i < 2; i++)
				DrawImage(equipMenuUiData[i * MENUUIDATACNT + 0], equipMenuUiData[i * MENUUIDATACNT + 1], equipMenuUiData[i * MENUUIDATACNT + 2], equipMenuUiData[i * MENUUIDATACNT + 3], x + (float)equipMenuUiData[i * MENUUIDATACNT + 4] * zoom, y - (float)(equipMenuUiData[i * MENUUIDATACNT + 5]) * zoom, false, false, false, false, false, zoom, sprite[equipMenuUiData[i * MENUUIDATACNT + 6]], equipMenuUiData[i * MENUUIDATACNT + 6]);

			CenterText(TEXT_EQUIPMENT, x + (float)160 * _2X * zoom, y - (float)48 * zoom, 2.0f * zoom);
			CenterText(TEXT_EQUIP_LISTEDIT, x + (float)160 * _2X * zoom, y - (float)100 * zoom, 1.1f * zoom);

			ItemDetailDraw(&robin.inven[menuItem], x + (float)16 * zoom, y - (float)152 * zoom, 1.0f * zoom, false, false);
			
			//EquipInfoDraw(&ao[curHero].equip[menuX], x, y - 500, robin.inven[menuItem].type, robin.inven[menuItem].detail, robin.inven[menuItem].grade, /*menuDepth - 2*/0, menuX, 1.0f, cvtDest, cvtLayer, buffering);

			//√÷ø‹∞¢ ≈◊µŒ∏Æ
			MemRectFrameThick(x, y, WINX, WINY, 0x271910, (float)OUTTHICK * zoom);
			//±◊æ»ø° ≈◊µŒ∏Æ
			MemRectFrameThick(x + OUTTHICK, y - OUTTHICK, WINX - 2 * OUTTHICK, WINY - 2 * OUTTHICK, 0x5F4022, INTTHICK);

			break;
	}
	return;
	
	//Top menu
	//if (menuCur < EQUIP_NECK)

	//BarDraw(&bar[BAR_GOLD], zoom, cvtDest, cvtLayer, buffering);
	//BarDraw(&bar[BAR_COMBATPOWERALL], zoom, cvtDest, cvtLayer, buffering);

	//HeroSelectButtonList(x + (float)(DX - HEROBUTTON_X - 1 * _2X) * zoom, DY - (float)48 * _2X * zoom, zoom, curHero, false, false, cvtDest, cvtLayer, buffering);
	HeroSelectButtonList(x + 1 * _2X * zoom, DY - (float)8 * _2X * zoom, zoom, curHero, menuDepth == 0 ? true : false, true);


	//Bottom Menu
	for (i = 0; i < TOTALEQUIP; i++) {
		DrawFrame((float)(2 * _2X + i * (COLLECTIONMENU_X + 4 * _2X)) * zoom, (float)(COLLECTIONMENU_Y + 2 * _2X + BOTTOMMENUHEIGHT + (menuCur == i ? 8 * _2X : 0 * _2X)) * zoom, (float)COLLECTIONMENU_X * zoom, (float)COLLECTIONMENU_Y * zoom, FRAME_SHOPBALLOON);
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
			DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), (float)(6 * _2X + i * (COLLECTIONMENU_X + 4 * _2X)) * zoom, (float)(COLLECTIONMENU_Y + 2 * _2X - 4 * _2X + BOTTOMMENUHEIGHT + (menuCur == i ? 8 * _2X : 0 * _2X)) * zoom, 1.7f * zoom, COLOR_BROWN, false, false, 1.0f * zoom);
			break;
		}

		if (menuCur != i && menuDepth == 0) {
			SetRectPoint((float)(2 * _2X + i * (COLLECTIONMENU_X + 4 * _2X)) * zoom, (float)(COLLECTIONMENU_Y + 2 * _2X + BOTTOMMENUHEIGHT + (menuCur == i ? 8 * _2X : 0 * _2X)) * zoom, (float)COLLECTIONMENU_X * zoom, (float)COLLECTIONMENU_Y * zoom, TOUCH_FUNC_COLLECTIONS_EQUIP + i);
		}
	}


	switch (menuDepth) {
		//ªÛºº∫∏±‚
		//menuItem ¿∏∑Œ «œ¿⁄.
		//
	case 1:
		ScreenDarken(SCREENDARKEN);

		menuItem = 1;

		itemType = menuCur;
		itemDetail = menuItem;
		itemGrade = GRADE_NORMAL;
		itemLv = GetItemLv(itemType, itemDetail, itemGrade);

		EquipInfoDraw(&ao[menuCur].equip[EQUIP_WEAPON], x, y, itemType, itemDetail, itemGrade, /*menuDepth - 2*/0, menuX, 1.0f);

		break;
	}
	return;

	SetSectionClip(0, y - (float)32 * _2X * zoom, (float)POPUPWINDOWSIZE_X * zoom, (float)(POPUPWINDOWSIZE_Y - 16 * _2X) * zoom, false);

	for (i = 0; i < TOTALCHAR; i++) {
		EnemyProfileDraw(x + (float)(28 * _2X + 92 * _2X * i) * zoom, y - (float)(48 * _2X) * zoom, i, false, false, zoom);
		SetRectPoint(x + (float)(28 * _2X + 92 * _2X * i) * zoom, y - (float)(48 * _2X) * zoom, (float)80 * _2X * zoom, (float)32 * _2X * zoom, TOUCH_FUNC_TABMENUX_1 + i);
		CenterText(TEXT_MONSTERNAME_START + i, x + (float)(28 * _2X + 92 * _2X * i + 52 * _2X) * zoom, y - (float)(48 * _2X + 12 * _2X) * zoom, zoom);

		//DrawFrame(x + (float)(28 * _2X + 92 * _2X * i) * zoom, y - (float)(48 * _2X) * zoom, (float)80 * _2X * zoom, (float)32 * _2X * zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
		//DrawPlayer(&ao[i], (menuX == i ? frame / 2 % 4 : 0), x + (float)(44 * _2X + 92 * _2X * i) * zoom, y - (float)(48 * _2X + 20 * _2X) * zoom, RIGHT, zoom, false, false, true, cvtDest, cvtLayer, buffering);
		//CenterText(TEXT_MONSTERNAME_START + i, x + (float)(28 * _2X + 92 * _2X * i + 52 * _2X) * zoom, y - (float)(48 * _2X + 12 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);
		//SetRectPoint(x + (float)(28 * _2X + 92 * _2X * i) * zoom, y - (float)(48 * _2X) * zoom, (float)80 * _2X * zoom, (float)32 * _2X * zoom, TOUCH_FUNC_TABMENUX_1 + i);

	}

	switch (menuCur) {
		//»˜æÓ∑Œ
	case COLLECTIONMENU_EQUIP:

		HeroStatDraw(&ao[curHero], x + (float)0 * _2X * zoom, y + scY[MENU_COLLECTIONS] - (float)52 * _2X * zoom, zoom);

		break;
		//Ω∫≈≥
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

			DrawImage(32 * _2X, 48 * _2X, 32 * _2X, 0 * _2X, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2, false, false, false, false, false, 2.0f, sprite[MAP_OBJ_IMG + 17], MAP_OBJ_IMG + 17);
			ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 16 * _2X, SHADOW_IMG, 2.0f);

			if (setItemCnt == 0)
				SetColor(COLOR_BLACK);

			DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 4 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X + 32 * _2X + (setItemCnt == COLLECTIONSITEMCNT ? -Abs((frame + i) / 2 % 32 - 16) : 0), 2.0f, false, false, false, true);

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
						DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + (j % 3) * (ITEMICONSIZE + 4 * _2X) + 22 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 4 * _2X - 48 * _2X - (j / 3) * (ITEMICONSIZE + 4 * _2X), 1.0f, false, false, false, true);
					}
					else {
						if (itemSlot == -1)
							grayScale = 32;
						DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + (j % 3) * (ITEMICONSIZE + 4 * _2X) + 22 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 4 * _2X - 48 * _2X - (j / 3) * (ITEMICONSIZE + 4 * _2X), 1.0f, COLOR_BROWN, false, false, true);

					}

					grayScale = 0;
					SetColor(false);
				}


			//∏Ó∫–¿« ∏Ó¿ª ∏æ“¥¬¡ˆ∏¶ ∫∏ø©¡÷¥¬ 
			if (setItemCnt > 0) {
				DrawNum(setItemCnt, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 22 * _2X - 14 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X - 32 * _2X + 18 * _2X, NUM_FONT_NORMAL, LEFT, false, false, false, 1.0f, true);
				DrawText(TEXT_SLASH, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 22 * _2X - 2 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X - 32 * _2X - 2 * _2X + 18 * _2X, 1.0f);
				DrawNum(COLLECTIONSITEMCNT, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 22 * _2X + 6 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X - 32 * _2X + 18 * _2X, NUM_FONT_NORMAL, LEFT, false, false, false, 1.0f, true);
			}
			//6∞≥∞° ¥Ÿ ¿Â¬¯µ«æÓ ¿÷æÓº≠ Ω∫≈≥¿Ã »∞º∫»≠ µ«æÓ ¿÷¿∏∏È
			if (GetFullEquipedCollectionIdx() == i)
				DrawNeutral(OBJ_STAMPEFFECT0 + (frame / 3 % 8), x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 4 * _2X + 16 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X, 0, 1.0f);
			//∏∏æ‡ 6∞≥∞° ¥Ÿ ∏ø©∏∏ ¿÷¿∏∏È
			else if (setItemCnt == COLLECTIONSITEMCNT) {
				//æ∆π´∞Õµµ «œ¡ˆ æ ¥¬¥Ÿ.
			}
			else if (setItemCnt > 0) {
				//æ∆π´∞Õµµ «œ¡ˆ æ ¥¬¥Ÿ.
			}
			//æ∆π´∞Õµµ æ¯¿∏∏È
			else
				DrawIcon(ICON_EVENT_LOCK, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 4 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X + 32 * _2X - 12 * _2X - 52 * _2X, 2.0f, false, false, false, true);

			DrawLabel(x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + 8 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - 88 * _2X - TSIZE * 2, TEXT_COLLECTIONS + i, 1.0f);

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

		CollectionDetailListDraw(xOffset, y, menuCur, 1.0f);

		SetAlpha(28);
		GradiationFrame(x + DX / 2 - 160 * _2X, y - 316 * _2X, 320 * _2X, 24 * _2X, 0);
		SetAlpha(32);
		CenterText(TEXT_ACTIONCARDINFO, x + DX / 2, y - 316 * _2X - 8 * _2X, 1.0f);

		SetAlpha(28);
		GradiationFrame(x + DX / 2 - 160 * _2X, y - 400 * _2X, 320 * _2X, 24 * _2X, 0);
		SetAlpha(32);
		CenterText(TEXT_COLLECTIONREWARD, x + DX / 2, y - 400 * _2X - 8 * _2X, 1.0f);

		//if (robin.collectionRewardGet[menuCur] == true)
		//	grayScale = 32;
		DrawIcon(GetItemIcon(collectionReward[menuCur * 4 + 0], collectionReward[menuCur * 4 + 1], collectionReward[menuCur * 4 + 2]), x + DX / 2 - (GetNumDx(collectionReward[menuCur * 4 + 3], false, NUM_FONT_LARGE, false, true, 1.5f * zoom / 2, true) + (float)ITEMICONSIZE * zoom + (float)(2 * _2X) * zoom) / 2, (y - 400 * _2X - 26 * _2X) * zoom / 2, zoom, false, false, false, true);
		DrawNum(collectionReward[menuCur * 4 + 3], x + DX / 2 - (GetNumDx(collectionReward[menuCur * 4 + 3], false, NUM_FONT_LARGE, false, true, 1.5f * zoom / 2, true) + (float)ITEMICONSIZE * zoom + (float)(2 * _2X) * zoom) / 2 + (float)ITEMICONSIZE * zoom + (float)(2 * _2X) * zoom, (y - 400 * _2X - 26 * _2X) * zoom / 2, NUM_FONT_LARGE, LEFT, 0, false, true, 1.5f * zoom / 2, true);
		grayScale = 0;

		//∏µŒ ¿Â¬¯
		//æ∆¡˜ ¿Â¬¯µ«¡ˆ æ ∞Ì 
		if (GetFullEquipedCollectionIdx() != menuCur && IsCollectionFull(menuCur) == true) {
			DrawTextButton(x + DX / 2 - 40 * _2X, y - 410 * _2X - 46 * _2X - 12 * _2X, 80 * _2X, 28 * _2X, 0, false, 1, false, TEXT_EQUIPALL);
			SetRectPoint(x + DX / 2 - 40 * _2X, y - 410 * _2X - 46 * _2X - 12 * _2X, 80 * _2X, 28 * _2X, TOUCH_FUNC_EQUIPALL + menuCur);
		}
		else
			DrawTextButton(x + DX / 2 - 40 * _2X, y - 410 * _2X - 46 * _2X - 12 * _2X, 80 * _2X, 28 * _2X, 0, 32, 1, false, TEXT_EQUIPALL);

		if (winAniFrame > 0) {
			winAniFrame++;

			DrawNeutral(OBJ_STAMPEFFECT0 + (frame / 3 % 8), x + 64 * _2X, y - 410 * _2X - 46 * _2X - 32 * _2X, 0, 1.0f);

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

			x + 64 * _2X, DY / 2 - 252 * _2X, RIGHT, false, HOUSEPLAYERZOOM);


		break;

	case 2:
	case 3:
	case 4:

		itemType = collectionData[menuCur * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + menuItem * COLLECTIONSDATASIZE + 0];
		itemDetail = collectionData[menuCur * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + menuItem * COLLECTIONSDATASIZE + 1];
		itemGrade = collectionData[menuCur * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + menuItem * COLLECTIONSDATASIZE + 2];
		itemLv = GetItemLv(itemType, itemDetail, itemGrade);

		EquipInfoDraw(&ao[PLAYER].equip[EQUIP_WEAPON], x, y, itemType, itemDetail, itemGrade, menuDepth - 2, menuX, 1.0f);
		break;
	}

}

void CollectionDetailListDraw(int x, int y, int collectionIdx, float zoom)
{
	int i;
	int itemType, itemDetail, itemGrade, itemLv, itemCnt, itemSlot, itemIdx, itemIcon;
	float iconZoom = EQUIPZOOM;
	float width;
	ITEM* it;
	int setItemCnt = 0;

	DrawLabel(x + (float)(DX / 2 - 40 * _2X) * zoom, y, TEXT_COLLECTIONS + collectionIdx, zoom);

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

		DrawImage(32 * _2X, 48 * _2X, 32 * _2X, 0 * _2X, x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - TSIZE * 3 - 4 * _2X) * zoom, false, false, false, false, false, iconZoom * zoom, sprite[MAP_OBJ_IMG + 17], MAP_OBJ_IMG + 17);
		ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - TSIZE * 3 - 4 * _2X - 24 * _2X) * zoom, SHADOW_IMG, iconZoom / 2 * zoom);

		if (itemIdx == -1)
			SetColor(COLOR_BLACK);

		DrawIcon(GetItemIcon(itemType, itemDetail, itemGrade), x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 4 * _2X) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - TSIZE * 3 - 4 * _2X - 24 * _2X + 32 * _2X - Abs((frame + i) / 2 % 32 - 16)) * zoom, 2.0f * zoom, false, false, false, true);

		SetColor(false);

		DrawStar(ICON_STAR, x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + COLLECTIONCARDSIZE_X / 2) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - TSIZE * 2) * zoom, itemLv, ITEMMAXLEVEL, ITEMMAXLEVEL, CENTER, true, 0.8f * zoom);

		if (itemIdx == -1)
			DrawIcon(ICON_EVENT_LOCK, x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 4 * _2X) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - TSIZE * 3 - 8 * _2X) * zoom, iconZoom * zoom, false, false, false, true);

		DrawItemValue(itemType, itemDetail, itemGrade, itemLv, x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 32 * _2X) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - COLLECTIONCARDSIZE_Y) * zoom, CENTER, false, iconZoom / 2 * zoom, 32 * _2X * iconZoom * zoom);

		if (itemIdx == -1) {
			sprintf(tempStr, "%s", TEXTPTR(TEXT_NOTACQUIRED));
		}
		else {
			//∑π∫ß«•Ω√
			sprintf(tempStr, TEXTPTR(TEXT_ALPHA_LV), itemLv + 1);
		}
		//DrawText(TEXT_LV, x + w / 2 - 24 * _2X, y - REWARDCARDSIZE_Y + 32 * _2X, cvtDest, cvtLayer, buffering);
		CenterTextStr(tempStr, x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 32 * _2X + 2 * _2X) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - COLLECTIONCARDSIZE_Y - TSIZE * 1 - 8 * _2X) * zoom, iconZoom / 2 * zoom);

		DrawLabel(x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + 8 * _2X) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - 88 * _2X - TSIZE * 3 - 4 * _2X) * zoom, itemIdx == -1 ? TEXT_QUESTION : TEXT_ITEMNAME_START + GetItemName(itemType, itemDetail, itemGrade), zoom);
	}

	//ƒ√∑∫º« ±‚¥… ±◊∏Æ±‚
	//ºº∆ÆΩ∫≈≥¿∫ ∫∞µµ∑Œ «•Ω√«ÿµŒ¡ˆ æ ¥¬¥Ÿ.


}


void ShopDraw(int x, int y, float zoom)
{
	int i, j;
	float OUTTHICK = (float)5 * zoom;
	float INTTHICK = (float)5 * zoom;
	float WINX = (float)DX * zoom;
	float WINY = (float)(DY - (GNBHEIGHT)-(BOTTOMMENUHEIGHT - BOTTOMMENU_INIT_HEIGHT)) * zoom;

	int tempIdx, mul = 1;

	MemRect(x, y, WINX, WINY, 0x3B2513);

	for (i = 0; i < 2; i++)
		DrawImage(shopMenuUiData[i * MENUUIDATACNT + 0], shopMenuUiData[i * MENUUIDATACNT + 1], shopMenuUiData[i * MENUUIDATACNT + 2], shopMenuUiData[i * MENUUIDATACNT + 3], x + (float)shopMenuUiData[i * MENUUIDATACNT + 4] * zoom, y - (float)(shopMenuUiData[i * MENUUIDATACNT + 5]) * zoom, false, false, false, false, false, zoom, sprite[shopMenuUiData[i * MENUUIDATACNT + 6]], shopMenuUiData[i * MENUUIDATACNT + 6]);

	CenterText(TEXT_MENU_SHOP, x + (float)160 * _2X * zoom, y - (float)48 * zoom, 2.0f * zoom);
	CenterText(TEXT_SHOP_BUY, x + (float)160 * _2X * zoom, y - (float)100 * zoom, 1.1f * zoom);
	//CenterText(TEXT_CREW_CURRENTLIST, x + (float)160 * _2X * zoom, y - (float)138 * zoom, 1.0f * zoom, cvtDest, cvtLayer, buffering);

	//√÷ø‹∞¢ ≈◊µŒ∏Æ
	MemRectFrameThick(x, y, WINX, WINY, 0x271910, (float)OUTTHICK * zoom);
	//±◊æ»ø° ≈◊µŒ∏Æ
	MemRectFrameThick(x + OUTTHICK, y - OUTTHICK, WINX - 2 * OUTTHICK, WINY - 2 * OUTTHICK, 0x5F4022, INTTHICK);

	return;

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y - (float)(POPUPSTORE_Y + 16 * _2X) * zoom, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

	switch (menuDepth) {
	case 0:
		switch (menuIdx) {
		default:
			//ªÛ¥‹¿« ∆Àæ˜Ω∫≈‰æÓ
			for (i = 0; i < TOTALPOPUPSTORE; i++) {
				DrawFrame(x + (float)32 * _2X * zoom + scX + (float)DX * zoom * (i - menuX), y, (float)(DX - 64 * _2X) * zoom, (float)POPUPSTORE_Y * zoom, FRAME_SHOPBALLOON);
				DrawNumTTF(i + 1, x + (float)34 * _2X * zoom + scX + (float)DX * zoom * (i - menuX), y - (float)2 * _2X * zoom, NUM_FONT_LARGE, LEFT, false, false, false, 1.0f, false);
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

				DrawImage(9 * _2X, 9 * _2X, (menuX == i ? 145 * _2X : 154 * _2X), 0 * _2X, x + (float)((DX / 2 - (16 * 4 + 9) * _2X / 2) + i * 16 * _2X) * zoom, y - (float)POPUPSTORE_Y * zoom - (float)4 * _2X * zoom, false, false, false, false, false, zoom, sprite[COMMON_IMG], COMMON_IMG);
				SetColor(false);
				SetAlpha(32);
			}

			return;
			//«œ∆ÆªÛ«∞ 6∞≥
			//y -= GNBHEIGHT;

			DrawLabel(x + (float)(POPUPWINDOWSIZE_X / 2 - 40 * _2X) * zoom, y + (float)16 * _2X * zoom, TEXT_SHOP_HEART_TITLE, zoom);

			for (i = 0; i < 6; i++) {

				//if (zoom == 1)
				//	SetRectPoint(x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3)) * zoom, y + (float)(-40 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3)) * zoom, (float)SHOPMENUCARD_WIDTH * zoom, (float)SHOPMENUCARD_HEIGHT * zoom, TOUCH_FUNC_EQUIP_INVENTORY + i);

				DrawImage(72 * _2X, 64 * _2X, 0 * _2X, 0 * _2X, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + (SHOPMENUCARD_WIDTH - 72 * _2X) / 2) * zoom, y + (float)(-16 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - (SHOPMENUCARD_HEIGHT - 88 * _2X) / 2) * zoom, false, false, false, false, false, zoom, sprite[HEART_0_IMG + i], HEART_0_IMG + i);

				//«œ∆Æºˆ∑Æ
				DrawNum(currencyShop[0 * 7 + i * 7 + 4], x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + SHOPMENUCARD_WIDTH / 2) * zoom, y + (float)(-16 * _2X - (SHOPMENUCARD_HEIGHT) * (i / 3)) * zoom, NUM_FONT_NORMAL, CENTER, 0, false, true, zoom, true);

				if (currencyShop[0 * 7 + i * 7 + 2]) {
					memset(tempStr, 0, sizeof(tempStr));
					sprintf(tempStr, "+%d%%", currencyShop[0 * 7 + i * 7 + 2]);
					//∫∏≥ Ω∫ º˝¿⁄
					CenterTextStr(tempStr, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + SHOPMENUCARD_WIDTH / 2) * zoom, y + (float)(-16 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 36 * _2X) * zoom, zoom);
				}
				//æ∆¿Ãƒ‹

				//DrawNeutral(OBJ_ITEM0 + (frame + i) % 4, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + (SHOPMENUCARD_WIDTH - 16 * _2X * 2) / 2 + ITEMICONSIZE) * zoom, y + (float)(- 16 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 52 * _2X) * zoom, LEFT, (float)2 * zoom, gScreenBuffer, gScreenLayer, false);

				DrawBuyButton(x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + 6 * _2X) * zoom, y + (float)(-16 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - SHOPMENUCARD_HEIGHT + 34 * _2X) * zoom, (float)(SHOPMENUCARD_WIDTH - 12 * _2X) * zoom, (float)(RAIDGOLDBARHEIGHT)*zoom, frame, 0, currencyShop[0 * 7 + i * 7 + 6], currencyShop[0 * 7 + i * 7 + 5], zoom, false, false, false);
			}

			y -= (float)(208 * _2X) * zoom;

			//¿Â∫ÒªÃ±‚ 3¡æ
			DrawLabel(x + (float)(POPUPWINDOWSIZE_X / 2 - 40 * _2X) * zoom, y, TEXT_SHOP_GACHA_TITLE, zoom);

			for (i = 0; i < 3; i++) {
				ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + (SHOPMENUCARD_WIDTH - 16 * _2X * 2) / 2 - 4 * _2X) * zoom, y + (float)(-40 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 46 * _2X - 20 * _2X) * zoom, SHADOW_IMG, zoom);
				DrawCastleBoxXY(BOX_REWARD2 + i, false, LEFT, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + (SHOPMENUCARD_WIDTH - 16 * _2X * 2) / 2 - 4 * _2X + 20 * _2X - (BOXSIZE_X / 2)) * zoom, y + (float)(-40 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 50 * _2X + BOXSIZE_Y) * zoom, itemColor[frame % 6], zoom);
				CenterText(TEXT_ITEMNAME_BOX + BOX_REWARD2 + i, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + SHOPMENUCARD_WIDTH / 2) * zoom, y + (float)(-32 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3)) * zoom, zoom);

				//DrawNeutral(OBJ_ITEM0 + (frame + i) % 4, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + (SHOPMENUCARD_WIDTH - 16 * _2X * 2) / 2 + ITEMICONSIZE) * zoom, y +(float)(-40 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 26 * _2X - 16 * _2X - ITEMICONSIZE * 2) * zoom, LEFT, (float)2 * zoom, gScreenBuffer, gScreenLayer, false);

				DrawBuyButton(x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + 6 * _2X) * zoom, y + (float)(-32 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - SHOPMENUCARD_HEIGHT + 28 * _2X) * zoom, (float)(SHOPMENUCARD_WIDTH - 12 * _2X) * zoom, (float)(RAIDGOLDBARHEIGHT)*zoom, frame, 0, GetBoxPrice(BOX_REWARD2 + i, GRADE_NORMAL), GetBoxCurrency(BOX_REWARD2 + i, GRADE_NORMAL), zoom, false, false, false);
				if (robin.gold >= GetBoxPrice(BOX_REWARD2 + i, GRADE_NORMAL))
					SetRectPoint(x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + 6 * _2X) * zoom, y + (float)(-32 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - SHOPMENUCARD_HEIGHT + 28 * _2X) * zoom, (float)(SHOPMENUCARD_WIDTH - 12 * _2X) * zoom, (float)(RAIDGOLDBARHEIGHT)*zoom, TOUCH_FUNC_SHOP_BUYBOX1 + i);
			}

			y -= (float)(128 * _2X) * zoom;

			DrawLabel(x + (float)(POPUPWINDOWSIZE_X / 2 - 40 * _2X) * zoom, y, TEXT_SHOP_COIN_TITLE, zoom);

			for (i = 0; i < 3; i++) {
				DrawImage(64 * _2X, 52 * _2X, 0 * _2X, 0 * _2X, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + (SHOPMENUCARD_WIDTH - 64 * _2X) / 2) * zoom, y + (float)(-24 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - (SHOPMENUCARD_HEIGHT - 52 * _2X) / 2) * zoom, false, false, false, false, false, zoom, sprite[COIN_0_IMG + 3 + i], COIN_0_IMG + 3 + i);

				//ƒ⁄¿Œºˆ∑Æ
				DrawNum(currencyShop[9 * 7 + i * 7 + 4], x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + SHOPMENUCARD_WIDTH / 2) * zoom, y + (float)(-24 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 8 * _2X) * zoom, NUM_FONT_NORMAL, CENTER, 0, false, true, zoom, true);

				if (currencyShop[9 * 7 + i * 7 + 2]) {
					memset(tempStr, 0, sizeof(tempStr));
					sprintf(tempStr, "+%d%%", currencyShop[9 * 7 + i * 7 + 2]);
					//∫∏≥ Ω∫ º˝¿⁄
					CenterTextStr(tempStr, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + SHOPMENUCARD_WIDTH / 2) * zoom, y + (float)(-24 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 52 * _2X) * zoom, zoom);
				}

				//DrawNeutral(OBJ_ITEM0 + (frame + i) % 4, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + (SHOPMENUCARD_WIDTH - 16 * _2X * 2) / 2 + ITEMICONSIZE) * zoom, y + (float)(- 16 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 26 * _2X - 16 * _2X - ITEMICONSIZE * 2) * zoom, LEFT, (float)2 * zoom, gScreenBuffer, gScreenLayer, false);

				DrawBuyButton(x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + 6 * _2X) * zoom, y + (float)(-32 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - SHOPMENUCARD_HEIGHT + 28 * _2X) * zoom, (float)(SHOPMENUCARD_WIDTH - 12 * _2X) * zoom, (float)(RAIDGOLDBARHEIGHT)*zoom, frame, 0, currencyShop[9 * 7 + i * 7 + 6], currencyShop[9 * 7 + i * 7 + 5], zoom, false, false, false);
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

void CastleMenuDraw(int x, int y, float zoom)
{
	int i, j;
	float OUTTHICK = (float)5 * zoom;
	float INTTHICK = (float)5 * zoom;
	float WINX = (float)DX * zoom;
	float WINY = (float)(DY - (GNBHEIGHT)-(BOTTOMMENUHEIGHT - BOTTOMMENU_INIT_HEIGHT)) * zoom;

	int tempIdx, mul = 1;

	MemRect(x, y, WINX, WINY, 0xB4D4F2);

	for (i = 0; i < 2; i++)
		DrawImage(castleMenuUiData[i * MENUUIDATACNT + 0], castleMenuUiData[i * MENUUIDATACNT + 1], castleMenuUiData[i * MENUUIDATACNT + 2], castleMenuUiData[i * MENUUIDATACNT + 3], x + (float)castleMenuUiData[i * MENUUIDATACNT + 4] * zoom, y - (float)(castleMenuUiData[i * MENUUIDATACNT + 5]) * zoom, false, false, false, false, false, zoom, sprite[castleMenuUiData[i * MENUUIDATACNT + 6]], castleMenuUiData[i * MENUUIDATACNT + 6]);

	CenterText(TEXT_CASTLE, x + (float)160 * _2X * zoom, y - (float)48 * zoom, 2.0f * zoom);
	CenterText(TEXT_CASTLE_LISTSELECT, x + (float)160 * _2X * zoom, y - (float)100 * zoom, 1.1f * zoom);
	//CenterText(TEXT_CREW_CURRENTLIST, x + (float)160 * _2X * zoom, y - (float)138 * zoom, 1.0f * zoom, cvtDest, cvtLayer, buffering);
	//«ˆ¿Á º∫
	DrawImageScale(128, 128, 716, 874, x + (float)8 * zoom, y - (float)(132) * zoom, false, false, false, false, false, 4.9f * zoom, 2.0f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
	DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, x + (float)16 * zoom, y - (float)124 * zoom, false, false, false, false, false, 0.25f * zoom, sprite[MAP_DIORAMA_IMG + castleOrder[robin.castle]], MAP_DIORAMA_IMG + castleOrder[robin.castle]);
	DrawImageScale(176, 40, 1, 679, x + (float)280 * zoom, y - (float)(132 + 12) * zoom, false, false, false, false, false, 1.2f * zoom, 1.2f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
	CenterText(TEXT_CASTLE_TOLEM + castleOrder[robin.castle], x + (float)280 * zoom + (float)106 * zoom, y - (float)(132 + 20) * zoom, 1.2f * zoom);


	//∏ÆΩ∫∆Æ¿« º∫
	int slotX;
	int slotY = y - (float)(400 + CASTLE_GAP_Y * 0) * zoom;

	SetSectionClip(0, slotY, DX, slotY - (HOMEBAR_HEIGHT + 8 * _2X) * zoom, false);

	for (i = 0; i < TOTALCASTLE; i++) {
		slotX = x + (float)12 * zoom;
		slotY = y - (float)(400 + CASTLE_GAP_Y * i - scY[MENU_CASTLE]) * zoom;

		DrawImageScale(128, 128, 716, 609, slotX, slotY, false, false, false, false, false, 4.7f * zoom, 1.15f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
		DrawImageScale(128, 128, 587, 737, slotX + (float)8 * zoom, slotY - (float)8 * zoom, false, false, false, false, false, 1.0f * zoom, 1.0f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);

		DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, slotX + (float)10 * zoom, slotY + (float)4 * zoom, false, false, false, false, false, 0.12f * zoom, sprite[MAP_DIORAMA_IMG + castleOrder[i]], MAP_DIORAMA_IMG + castleOrder[i]);
		StarBarDraw(castleStarLimit[castleOrder[i]], ICON_STAR, slotX + (float)24 * zoom, slotY - (float)102 * zoom, false, 0.7f);

		//SetFontColor(COLOR_DARKGREY);
		DrawImageScale(176, 40, 1, 679, slotX + (float)152 * zoom, slotY - (float)4 * zoom, false, false, false, false, false, 1.0f * zoom, 1.0f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
		CenterText(TEXT_CASTLE_TOLEM + castleOrder[i], slotX + (float)240 * zoom, slotY - (float)12 * zoom, 1.2f * zoom);
		//SetFontColor(COLOR_WHITE);

		//√÷¥Î µø∑· ∫∞
		//DrawIcon(ICON_STAR, slotX + (float)152 * zoom, slotY - (float)60 * zoom, 1.0f * zoom, COLOR_BROWN, false, false, 1 * _2X, cvtDest, cvtLayer, buffering);
		//DrawNum2AutoSpaceing(castleStarLimit[i], slotX + (float)200 * zoom, slotY - (float)64 * zoom, LEFT, false, false, (float)(GOLDBARWIDTH - ITEMICONSIZE * 1.2f - 13 * _2X) * zoom, true, NUM2ZOOM * 1.5f * zoom, true, true, cvtDest, cvtLayer, buffering);

		//ªÛ¿⁄
		DrawImageScale(128, 128, 587, 737, slotX + (float)350 * zoom, slotY - (float)8 * zoom, false, false, false, false, false, 0.8f * zoom, 0.8f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
		DrawBox(BOX_CASTLE0 + castleOrder[i], slotX + (float)400 * zoom, slotY - (float)108 * zoom, LEFT, 0, false, false, false, false, BOXCASTLEZOOM * 0.9f);

		GoldBarDraw(castleBoxGold[castleOrder[i]], ICON_GOLD, slotX + (float)332 * zoom, slotY - (float)108 * zoom, false, 0.6f * zoom);
		//»πµÊΩ√ ƒ≥∏Ø≈Õ
		//DrawImageScale(128, 128, 587, 737, slotX + (float)480 * zoom, slotY - (float)8 * zoom, false, false, false, false, false, 0.8f * zoom, 0.8f * zoom, sprite[UI_NEW_IMG], cvtDest, cvtLayer, UI_NEW_IMG, buffering);
		DrawItemCard(ITEM_CREW, i * 2, GRADE_NORMAL, 1, 1, false, slotX + (float)480 * zoom, slotY + (float)8 * zoom, TEXT_ALPHA_REWARD, CARDDEFAULTZOOM * 0.8f * zoom, false, false, false, false, 0);
	}

	int scrollH = WINY - (float)(420 + 184 * 0) * zoom;

	DrawScroll(
		x + (float)616 * zoom,
		y - (float)(400 + 184 * 0) * zoom,
		scrollH,
		MENU_CASTLE);

	UnSectionClip(false);

	//√÷ø‹∞¢ ≈◊µŒ∏Æ
	MemRectFrameThick(x, y, WINX, WINY, 0x052F6C, (float)OUTTHICK * zoom);
	//±◊æ»ø° ≈◊µŒ∏Æ
	MemRectFrameThick(x + OUTTHICK, y - OUTTHICK, WINX - 2 * OUTTHICK, WINY - 2 * OUTTHICK, 0x0C459B, INTTHICK);

	return;
}
