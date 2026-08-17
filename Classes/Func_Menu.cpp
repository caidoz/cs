#pragma once
#include "Core.h"
#include "Func.h"
#include "Text.h"
#include "Data.h"

// Menu & UI 관련 함수
//뉴스 드로우
void NewsDraw(int x, int y, float zoom)
{
	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

}
//선물함 드로우
void GiftDraw(int x, int y, float zoom)
{
	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

}

//친구와의 전투 드로우
void GuildEventDraw(int x, int y, float zoom)
{
	int i;

	DrawImage((float)POPUPWINDOWSIZE_X * zoom, (float)(POPUPWINDOWSIZE_Y)*zoom, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

	switch (menuDepth) {

	case 0:
		//여기서는 그냥 리스트를 그려준다.
		//하루에 세가지
		for (i = 0; i < 3; i++) {
			MemRectRound(x + (float)(32 * _2X) * zoom, y - (float)(48 * _2X + 80 * _2X * i) * zoom, (float)(256 * _2X) * zoom, (float)(72 * _2X) * zoom, COLOR_BROWN, 2);

			//DrawFrame(x + (float)32 * _2X * zoom, y - (float)(48 * _2X + 80 * _2X * i) * zoom, (float)256 * _2X * zoom, (float)72 * _2X * zoom, COLOR_LIGHTBROWN, )
		}
	case 1:
		//여기서 각종 획득 이펙트를 그려준다.

		break;
	}


	//현재 데일리 이벤트까지 남는 시간
	DrawTime(x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y + (float)(-440 * _2X) * zoom, Max(0, 86400 - (MC_knlCurrentTimeStamp() - robin.calendarTimeStamp)), TIME_HOUR_MINUTE, CENTER, zoom);


}

void DailyQuestDraw(int x, int y, float zoom)
{
	int i, j;
	int boxOpenFrame;
	int dailyQuestType;

	float NPCZOOM = 1.3f;

	int stageBossIdx = GetStageBossIdx();
	int stageBossType = GetStageBossType();


	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

	switch (menuDepth) {

	case 0:
		//여기서는 그냥 리스트를 그려준다.
		//하루에 세가지
		for (i = 0; i < 3; i++) {
			//for (i = 0; i < TOTAL_DAILYQUEST_TYPE; i++) {
			MemRectRound(x + (float)(20 * _2X) * zoom, y - (float)(64 * _2X + 72 * _2X * i) * zoom, (float)(280 * _2X) * zoom, (float)(64 * _2X) * zoom, COLOR_BEIGE, 2 * _2X);

			dailyQuestType = i;

			switch (i) {
				//상자를 열어서 장비를 얻어라
			case DAILYQUEST_OPEN_BOX_GETEQUIP:
				//상자를 여세요
				DrawNeutral(OBJ_BOX0 + boxOpenAnimation[((frame / (MOTIONDIV * 2)) % 20)], x + (float)(20 * _2X + 32 * _2X) * zoom, y - (float)(64 * _2X + 60 * _2X + 72 * _2X * i) * zoom, LEFT, 2.0f * zoom);
				if (frame / (MOTIONDIV) % 40 > 16/* && ((frame / (MOTIONDIV * 2)) % 20) < 16*/) {
					boxOpenFrame = ((frame / (MOTIONDIV)) % 40) - 16;

					for (j = 0; j < 3; j++)
						DrawIcon(GetItemIcon(boxOpenItemFrameInfo[boxOpenFrame * 3 * BOXOPENITEMFRAMEINFOSIZE + BOXOPENITEMFRAMEINFOSIZE * j + 0], boxOpenItemFrameInfo[boxOpenFrame * 3 * BOXOPENITEMFRAMEINFOSIZE + BOXOPENITEMFRAMEINFOSIZE * j + 1], boxOpenItemFrameInfo[boxOpenFrame * 3 * BOXOPENITEMFRAMEINFOSIZE + BOXOPENITEMFRAMEINFOSIZE * j + 2]), x + (float)(20 * _2X + 32 * _2X) * zoom + (float)boxOpenItemFrameInfo[boxOpenFrame * 3 * BOXOPENITEMFRAMEINFOSIZE + BOXOPENITEMFRAMEINFOSIZE * j + 3] * zoom, y - (float)(64 * _2X + 60 * _2X + 72 * _2X * i) * zoom + (float)boxOpenItemFrameInfo[boxOpenFrame * 3 * BOXOPENITEMFRAMEINFOSIZE + BOXOPENITEMFRAMEINFOSIZE * j + 4] * zoom, (float)boxOpenItemFrameInfo[boxOpenFrame * 3 * BOXOPENITEMFRAMEINFOSIZE + BOXOPENITEMFRAMEINFOSIZE * j + 5] * zoom, COLOR_WHITE, true, true, 1);
				}

				break;
				//국경수비대를 업그레이드를 해라
			case DAILYQUEST_UPGRADE_CREW:
				ao[NPC].x = x + (float)(28 * _2X + 24 * _2X) * zoom;
				ao[NPC].y = y - (float)(52 * _2X * NPCZOOM + 72 * _2X * i) * zoom - (float)(8 * _2X + 24 * _2X) * NPCZOOM * zoom;

				DrawImage(32 * _2X, 12 * _2X, 107 * _2X, 48 * _2X, ao[NPC].x - (float)16 * _2X * NPCZOOM * zoom, ao[NPC].y + (float)(2 * _2X) * NPCZOOM * zoom, false, false, false, false, false, NPCZOOM * zoom, sprite[MAP_OBJ_IMG + 6], MAP_OBJ_IMG + 6);

				DrawCmfDetailShadow(enemyData[crewData[(robin.stage * MAXCREW + MAXCREW - 1) * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_CMF], crewPos[enemyData[crewData[(robin.stage * MAXCREW + MAXCREW - 1) * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_CMF]], ao[NPC].x, ao[NPC].y, RIGHT, enemyIconZoom[crewData[(robin.stage * MAXCREW + MAXCREW - 1) * CREWDATASIZE]] * NPCZOOM * zoom);
				break;
				//다른 유저를 공격해라
			case DAILYQUEST_ATTACK_OTHERUSER:
				EnemyUserProfileDraw(&enemyHouse, x + (float)(20 * _2X + 28 * _2X - 20 * _2X) * zoom, y - (float)(58 * _2X + 72 * _2X * i) * zoom, zoom);
				break;
			case DAILYQUEST_COLLECT_GOLD:
				DrawIcon(ICON_GOLD + frame % GOLDICONFRAME, x + (float)(20 * _2X + 12 * _2X) * zoom, y - (float)(80 * _2X + 72 * _2X * i) * zoom, 2.5f * zoom, false, false, false, 1);
				break;
			case DAILYQUEST_STAGE_TRY:
				DrawBox(stageClearBox[robin.stage], x + (float)(20 * _2X + 32 * _2X + 24 * _2X) * zoom, y - (float)(64 * _2X + 60 * _2X + 72 * _2X * i) * zoom, LEFT, boxNeutralAnimation[((frame / (MOTIONDIV * 2 * 2)) % 4)], COLOR_WHITE, true, false, true, 1.2f * zoom / 1.2f);

				DrawCmfDetailShadow(enemyData[stageBossType * ENEMYDATASIZE + ENEMYDATA_CMF], crewPos[stageBossType * 5 + 0] + (frame / 4 % crewPos[stageBossType * 5 + 1]), x + (float)(20 * _2X + 28 * _2X) * zoom, y - (float)(64 * _2X + 60 * _2X + 72 * _2X * i) * zoom, LEFT, /*enemyIconZoom[stageBossType] **/ zoom / 1.2f);

				DrawStageLabel(x + (float)(20 * _2X + 28 * _2X) * zoom, y - (float)(64 * _2X + 60 * _2X - 60 * _2X + 72 * _2X * i) * zoom, TEXT_STAGE, robin.stage, robin.room, true, zoom / 1.2f);

				break;

			}
			DrawText(TEXT_DAILYQUEST_OPEN_BOX_GETEQUIP + i, x + (float)(20 * _2X + 32 * _2X + 40 * _2X) * zoom, y - (float)(64 * _2X + 12 * _2X + 72 * _2X * i) * zoom, zoom);
			DrawGuage(x + (float)(20 * _2X + 28 * _2X + 40 * _2X) * zoom, y - (float)(64 * _2X + 32 * _2X + 72 * _2X * i) * zoom, float(DAILYQUESTBARWIDTH) * zoom, float(DAILYQUESTBARHEIGHT) * zoom, 10, 30, COLOR_NAVY, COLOR_HEARTBAR, zoom);
			DrawRewardCard(i, i, i, false, 1, x + (float)(20 * _2X + 28 * _2X + 204 * _2X) * zoom, y - (float)(64 * _2X + 4 * _2X + 72 * _2X * i) * zoom, false, zoom, true, false, true, GetItemStar(i, i, i), GetItemStar(i, i, i), true, 0);
		}
	case 1:
		//여기서 각종 획득 이펙트를 그려준다.

		break;
	}


	//현재 데일리 이벤트까지 남는 시간
	DrawTime(x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y + (float)(-440 * _2X) * zoom, Max(0, 86400 - (MC_knlCurrentTimeStamp() - robin.calendarTimeStamp)), TIME_HOUR_MINUTE, CENTER, zoom);

}


void ShopDraw_Back(int x, int y)
{

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

//별 드로우
void StarShopDraw(int x, int y)
{
	DrawCmfPopUp(CMF_NPC_USERQUEST, TEXT_MENU_STARSHOP, x, y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, DX - 120 * _2X, 6, 1, 1.0f);


}


void HeroDraw(int type, int x, int y, int dirX, float zoom)
{

	if (IsGetHero(type) == false)
		grayScale = 32;
	EnemyProfileDraw(x, y, type, false, (drawHandle == MD_PLAY ? ao[type].lv : false), 1.0f * zoom);

	grayScale = 0;
	if (IsGetHero(type) == false) {
		DrawLock(getHeroLv[type], x + (float)(+(2 * _2X)) * zoom, y - (float)2 * _2X * zoom, 2.0f * zoom);
	}

}

void HeroListDraw(int x, int y, float zoom, bool checkBox, int gap)
{
	int i;


	for (i = 1; i < MAXPLAYER; i++) {

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
	//히어로 스탯을 그려준다.



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
	//HP, MP, EXP 부분
	//hp
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s  %lld  /  %lld", textId[TEXT_ALPHA_HP], pObj->hp, pObj->ps[PS_HP]);
	DrawTextStr(tempStr, x + (float)40 * _2X * zoom, y + plusY - (float)40 * _2X * zoom, zoom);

	//총 공격수치
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

	//저항도
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
	//갭이 마이너스면 현재 장착중인게 좋은거다
	long long combatPowerGap = CompareCombatPower(&robin.newItem, &ao[robin.newItem.type % 3].equip[itemEquipSlot[robin.newItem.type]]);

	int arrowDirY = DOWN;
	
	if (combatPowerGap >= 0)
		arrowDirY = UP;

	
	//equipped가 true면 장착중, false면 
	switch (it->type) {
		//장비
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

		//튜토리얼 3단: 장착 버튼을 누르게 한다.
		//사각형은 바로 위 DrawTouchLargeButton()에 넘긴 것과 같은 값이라 스팟과 터치영역이 겹친다.
		if (GetTutorialEquipButtonTouchFunc() == TOUCH_FUNC_EQUIP_INVENTORY + GetInvenIdx(it->type, it->detail, it->grade)) {
			float btnZoom = zoom / CARDDEFAULTZOOM;
			float bx = x + (float)(432) * zoom;
			float by = y - (float)(20) * zoom;
			float bw = (float)BUYBUTTON_X * btnZoom;
			float bh = (float)BUYBUTTON_Y * btnZoom;
			float pulse = 1.0f + sinf((float)frame * 0.1f) * 0.06f;

			//손 크기는 앞 단계들과 같게 맞춘다.
			float handZoom = 2.0f;
			float handW = (float)imgArray[IMG_HAND1 * 4 + 2] * handZoom;
			float handH = (float)imgArray[IMG_HAND1 * 4 + 3] * handZoom;

			DrawHand(bx + bw / 2 - handW, by - bh / 2 + handH, robin.playtime / MOTIONDIV, handZoom);

			//버튼이 가로로 길어서 폭 기준으로 잡으면 옆의 카드까지 밝아진다. 높이 기준으로 좁힌다.
			SetSpotlight(bx + bw / 2, by - bh / 2,
				bh * 0.9f * pulse, bh * 1.6f * pulse, 0.25f);
		}

		break;
		//동료
	case ITEM_CREW:
		int crewType = crewData[it->detail * CREWDATASIZE + CREWDATA_TYPE];
		int crewDetail = it->detail;
		int crewGrade = it->grade;
		int crewCmf = enemyData[crewType * ENEMYDATASIZE + ENEMYDATA_CMF];
		int crewMotion = crewPos[crewType * 5 + 0] + (frame / 4 / MOTIONDIV) % crewPos[crewType * 5 + 1];
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

				DrawCmfDetailShadow(enemyData[crewType * ENEMYDATASIZE + ENEMYDATA_CMF],
					crewPos[crewType * 5 + 0],
					centerX, centerY,
					RIGHT, baseScale);
			}
		}

		return;

		//룰렛판
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
		//레벨업
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


	DrawItemIcon(it, &ao[PLAYER], x + (float)(8 * _2X) * zoom, y - (float)8 * _2X * zoom, zoom * LOBBYZOOM);

	//소켓이 있는 아이템이라면
	//if (it->type <= ITEM_RING && it->count > 0) {
	//	for (i = 0; i < it->count; i++)
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

	//장비인 경우
	if (it->type <= ITEM_RING || it->type == ITEM_RECIPE) {
		int itemType = it->type;

		if (itemType == ITEM_RECIPE) {
			itemType = it->detail >> 3;
		}

		//종류
		width = GetAlphaWidth(ALPHA_SWORD + itemType, FONT_SMALL, zoom);
		//SetBlend(12, 0x0000FF);
		DrawAlpha(x + (float)(44 * _2X) * zoom, y - (float)6 * _2X * zoom, ALPHA_SWORD + itemType, FONT_SMALL, zoom, false);
		//UnSetBlend();

		DrawTextStr(textId[TEXT_DEFAULTSTAT], x + (float)12 * _2X * zoom, y - (float)52 * _2X * zoom, zoom);

		//공격/방어력/효과 텍스트

		//if (itemType != ITEM_RING)

		switch (it->type) {
		default:
			memset(&defaultStatStr, 0, sizeof(defaultStatStr));

			sprintf(defaultStatStr, "%s  %s", textId[itemValueTypeText[it->type]], dmgStr);

			DrawTextStr(defaultStatStr, x + (float)64 * _2X * zoom, y - (float)52 * _2X * zoom, zoom);

			if (equipped == false) {
				if (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) != 0) {
					//if (combatPowerNext - combatPowerCur != 0) {
						//arrowDirY = frame / FPS % 2;
					DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - (robin.playtime / 2) % 8), x + (float)(GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? 200 * _2X : 210 * _2X) * zoom, y - (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? (float)40 * _2X : (float)54 * _2X) * zoom, LEFT, GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? false : 180, (float)(1.1f) * zoom);
					DrawNum(GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]), x + (float)280 * _2X * zoom, y - (float)50 * _2X * zoom, NUM_FONT_NORMAL, RIGHT, false, GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) > 0 ? PLUS : MINUS, true, 1.1f * zoom, false);
				}
			}

			break;
		case ITEM_NECK:
			DrawTextStr(dmgStr, x + (float)64 * _2X * zoom, y - (float)52 * _2X * zoom, zoom);

			if (equipped == false) {
				if (GetItemValue(it) - GetItemValue(&ao[PLAYER].equip[itemEquipSlot[it->type]]) != 0) {
					//if (combatPowerNext - combatPowerCur != 0) {
						//arrowDirY = frame / FPS % 2;
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

		//종류
		width = GetAlphaWidth(ALPHA_GEM, FONT_SMALL, zoom);

		SetBlend(12, 0x0000FF);
		DrawAlpha(x + (float)169 * _2X * zoom - width, y - (float)63 * _2X * zoom, ALPHA_GEM, FONT_SMALL, zoom, false);
		UnSetBlend();

		//공격/방어력/효과 텍스트
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
	//장착, 교체 버튼
	if (equipped == false && onlyInfo == false) {
		DrawTouchLargeButton(x + (float)(8 * _2X) * zoom, y - (float)(ITEMDETAILWINDOWSIZE_Y - 36 * _2X) * zoom, BUYBUTTON_X, BUYBUTTON_Y, textId[TEXT_DISASSEMBLE], TOUCH_FUNC_DISASSEMBLE_NEWITEM, FRAME_RED, zoom);
		DrawTouchLargeButton(x + (float)(196 * _2X) * zoom, y - (float)(ITEMDETAILWINDOWSIZE_Y - 36 * _2X) * zoom, BUYBUTTON_X, BUYBUTTON_Y, textId[TEXT_EQUIP], TOUCH_FUNC_EQUIP_NEWITEM, FRAME_GREEN, zoom);

		//if (CompareCombatPower(it, &ao[PLAYER].equip[itemEquipSlot[it->type]]) < 0) {
		//	ResetRectPoint();
		//	ScreenDarken(SCREENDARKEN);
		//	//경고


		//}

	}
	UnSectionClip(false);
}

void ItemOptionCompareDraw(ITEM* it1, ITEM* it2, int x, int y, float zoom)
{
	int i;
	unsigned char mark[12];
	int valueInt;

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
		//옵션
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
			//세트아이템인 경우 세트효과를 보여준다.
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
	int itemLv, itemCnt, itemIdx, itemIcon;
	int itemTypeNext, itemDetailNext, itemGradeNext;
	int icon, skillIcon, questIcon, pvpQuestIcon;
	OBJECT* pObj = &ao[PLAYER];
	int collectionIdx;

	float width;
	float YGAP = -64 * _2X;
	int eventIdx = GetEventMenuIdx(EVENTTYPE_DEBTDISCOUNT);
	float discount = 0;
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

		if (winAniFrame > 0) {
			winAniFrame++;

			DrawNeutral(OBJ_STAMPEFFECT0 + (frame / 3 % 8), x + (float)(DX / 2) * zoom, y + (float)(DY / 2 + 160 * _2X) * zoom, 0, 1.0f);

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
		//개별 장착이 되지 않는다면
		//만약 장착이 되어 있지 않으면
		if (GetEquipSlot(itemType, itemDetail, itemGrade) == -1) {
			DrawTextButton(x + (float)(DX / 2 - 40 * _2X) * zoom, y + (float)(DY / 2 + 148 * _2X - REWARDCARDSIZE_Y * 2 - 8 * _2X) * zoom, (float)(80 * _2X) * zoom, (float)(28 * _2X) * zoom, 0, false, zoom, false, TEXT_EQUIP);
			SetRectPoint(x + (float)(DX / 2 - 40 * _2X) * zoom, y + (float)(DY / 2 + 148 * _2X - REWARDCARDSIZE_Y * 2 - 8 * _2X) * zoom, (float)(80 * _2X) * zoom, (float)(28 * _2X) * zoom, TOUCH_FUNC_EQUIP_INVENTORY + itemStartCnt[itemType] + itemDetail * TOTALGRADE + itemGrade);
		}
		else
			DrawTextButton(x + (float)(DX / 2 - 40 * _2X) * zoom, y + (float)(DY / 2 + 148 * _2X - REWARDCARDSIZE_Y * 2 - 8 * _2X) * zoom, (float)(80 * _2X) * zoom, (float)(28 * _2X) * zoom, 0, 32, zoom, false, TEXT_SOCKETING);


		//골드 / 골드백 / 하트 / 퀘스트 아이템
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
		//장착한 모습을 보여주고,

		//업그레이드
		//왼쪽이 강화하기
		//오른쪽이 장착하기
		//

		for (i = 0; i < 1; i++) {
			if (menuX == i) {
				DrawFrame(x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i - 2 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 4 * _2X + 2 * _2X + YGAP) * zoom, (float)(128 * _2X) * zoom, (float)(32 * _2X) * zoom, FRAME_CHOICEBUTTON_BEIGE);
			}
			else {
				DrawFrame(x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 4 * _2X + YGAP) * zoom, (float)(128 * _2X) * zoom, (float)(32 * _2X) * zoom, FRAME_CHOICEBUTTON);
			}
			switch (i) {
				//강화하기
			case 0:
				ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i - 20 * _2X + 24 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 4 * _2X + YGAP + 8 * _2X - 20 * _2X) * zoom, SHADOW_IMG, zoom);
				DrawNeutral(EFFECT_CRAFT0 + (menuX == 0 ? (frame / 2) % 3 : 0), x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i + 24 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 4 * _2X + YGAP - 20 * _2X) * zoom, 0, zoom);
				DrawText(TEXT_UPGRADE, x + (float)(DX / 2 - 132 * _2X + 134 * _2X * i + 60 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 14 * _2X + YGAP) * zoom, zoom);

				//memset(tempStr, 0, sizeof(tempStr));
				//sprintf(tempStr, TEXTPTR(TEXT_MAXLEVEL), collectionLvLimit[collectionIdx]);

				break;
				//진화하기TEXT_HAMMER
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
				//현재 레벨과 데미지

				DrawStar(ICON_STAR, +(float)(DX / 2 - 132 * _2X + 42 * _2X + 11 * _2X * 2) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 32 * _2X - 10 * _2X + YGAP - 2 * _2X * 2) * zoom, itemLv, ITEMMAXLEVEL, ITEMMAXLEVEL, CENTER, true, zoom);

				DrawStar(ICON_STAR, x + (float)(DX / 2 - 132 * _2X + 42 * _2X + 11 * _2X * 2 + 140 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 32 * _2X - 10 * _2X + YGAP - 2 * _2X * 2) * zoom, itemLv + 1, ITEMMAXLEVEL, ITEMMAXLEVEL, CENTER, true, zoom);

				//업그레이드 화살표
				SetAlpha(32 - Abs(frame % 32 - 16));
				DrawImage(18 * _2X, 14 * _2X, 58 * _2X, 174 * _2X, x + (float)(DX / 2 - 12 * _2X) * zoom, y + (float)(DY / 2 + MINDY_MIN / 2 - 240 * _2X - 32 * _2X - 8 * _2X + YGAP) * zoom, true, false, false, false, false, (float)1.5f * zoom, sprite[COMMON_IMG], COMMON_IMG);
				SetAlpha(32);

				//업그레이드 보상

				//업그레이드 후 데미지
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

					SetAlpha(32 - Abs(frame % 32 - 16));
					CenterText(TEXT_ENCHANTING, x + (float)(DX / 2) * zoom, y + (float)(128 * _2X) * zoom, zoom);
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

				//진화 애니메이션
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

				//0: 카드가 
				//다섯개의 카드가 하나로 합쳐지고		
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
					DrawCmfDetail(CMF_NPC_HEART, PO_C122_BURST0 + Min(4, ((menuFrame / 4) % 7)), x + DX / 2, y + DY / 2 - 128 * _2X, LEFT, 3.0f, false, false);

					if (itemTypeNext == ITEM_CREW) {
						curStar = maxStar = crewData[itemDetailNext * CREWDATASIZE + CREWDATASIZE - 1] + 1;
					}
					else {
						curStar = maxStar = GetItemStar(itemTypeNext, itemDetailNext, itemGradeNext);
					}

					DrawRewardCard(itemTypeNext, itemDetailNext, itemGradeNext, itemLv, itemCnt, x + DX / 2 - ITEMCARDSIZE_X / 2, y + DY / 2 + 108 * _2X, false, 2.0f, true, false, true, curStar, maxStar, true, 0);

					//강화성공시
					DrawEffect(EFFECT_LEVELUP_TEXT0 + (frame / 2) % 14, x + DX / 2, y + DY / 2 + 108 * _2X + 32 * _2X, 0, false, 3.0f);

					DrawGoldAlpha(x + DX / 2, y + DY / 2 - 160 * _2X, ALPHA_CONGRATULATIONS, FONT_GOLD_LARGE, 1.0f, CENTER, true, false);


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
			DrawGoldNum(remainedTurn + 1, x + oldXOffset, y + oldYOffset, CENTER, 1, false, false, oldNumZoom);
			SetAlpha(32);
		}

		// 새 숫자(2) 그리기
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

	//일단 히어로를 획득하는 조건을 정리하자.
	//1번 레벨, 2번 스테이지
	//레벨로 하면 상자를 많이 열어야 하니까 하트가 많이 필요하고
	//스테이지로 하면 


	DrawEffect(EFFECT_LEVELUP_TEXT10, x + (float)POPUPWINDOWSIZE_X / 2, y, LEFT, false, zoom);
	DrawStarNum(ICON_STAR, 1, x + (float)POPUPWINDOWSIZE_X / 2, y, 2.0f * zoom);
}

void HowToGetCrewsDraw(int x, int y, float zoom)
{
	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

	//일단 크류자리를 오픈하는 조건을 정리하자.
	//1번 레벨, 2번 스테이지
	//레벨로 하면 상자를 많이 열어야 하니까 하트가 많이 필요하고
	//스테이지로 하면 


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

void CalendarDraw(int x, int y, float zoom)
{
	int i, j;
	int week = 0;
	int dayOfMonth = robin.calendarMonthDay;

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

	//밑에 일주일짜리 스케쥴 표
	for (i = 0; i < WEEK + 1; i++) {
		switch (i) {
			//1달치 보상이 그려지고
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


			grayScale = 0;

			SetFontColor(COLOR_BROWN);
			CenterTextSolid(TEXT_CALENDAR_DAY1 + i - 1, x + (float)(POPUPWINDOWSIZE_X / 2) * zoom, y + (float)(calendarPos[4 * i + 1] + 16 * _2X) * zoom, 1.2f * zoom);
			SetFontColor(COLOR_WHITE);
			break;
		}

	}

	//현재 보상까지 남은 시간



	//상단에 한달짜리 스케쥴 표

	//위에 타이틀 태그를 붙여주고,
	//
}

//환경설정 화면 글자 크기
static const float OPTIONTITLEZOOM = 1.8f;
static const float OPTIONTEXTZOOM = 1.2f;
static const float OPTIONROWTEXTZOOM = 1.32f;	//항목 이름은 리본/버튼 글자보다 10% 크게

//환경설정 화면(option.png)에서 잘라 쓰는 파츠 좌표.
//optionSample.png의 배치를 그대로 따라간다.
enum {
	//창 본체. 세로로 늘릴 때는 y축을 늘리지 않고 MID 띠를 반복해서 쌓는다.
	OPT_WIN_X = 2, OPT_WIN_W = 398,
	OPT_WIN_TOP_Y = 1, OPT_WIN_TOP_H = 95,		//타이틀바 + 위쪽 금색 모서리
	OPT_WIN_MID_Y = 200, OPT_WIN_MID_H = 20,		//반복해서 쌓는 중간 띠
	OPT_WIN_BOT_Y = 300, OPT_WIN_BOT_H = 69,		//아래쪽 금색 모서리 + 하단 테두리

	//타이틀바의 X버튼(창 이미지에 이미 그려져 있다. 터치영역만 잡아준다)
	OPT_CLOSE_X = 345, OPT_CLOSE_Y = 26, OPT_CLOSE_W = 50, OPT_CLOSE_H = 40,

	//하단 회색 띠(고객센터/이용약관/개인정보처리방침이 올라간다)
	OPT_FOOT_X = 2, OPT_FOOT_Y = 375, OPT_FOOT_W = 396, OPT_FOOT_H = 59, OPT_FOOT_EDGE = 24,

	//본문 패널(밝은 회색 라운드)
	OPT_PANEL_X = 413, OPT_PANEL_Y = 48, OPT_PANEL_W = 304, OPT_PANEL_H = 309, OPT_PANEL_EDGE = 40,

	//섹션 리본(파랑)
	OPT_RIBBON_X = 733, OPT_RIBBON_Y = 31, OPT_RIBBON_W = 248, OPT_RIBBON_H = 55, OPT_RIBBON_EDGE = 26,

	//행 묶음 배경(크림색)
	OPT_GROUP_X = 734, OPT_GROUP_Y = 160, OPT_GROUP_W = 286, OPT_GROUP_H = 56, OPT_GROUP_EDGE = 24,

	//가로로 긴 파란 버튼
	OPT_BTNBLUE_X = 283, OPT_BTNBLUE_Y = 509, OPT_BTNBLUE_W = 163, OPT_BTNBLUE_H = 69, OPT_BTN_EDGE = 28,

	//토글 스위치
	OPT_TOGGLEON_X = 414, OPT_TOGGLEON_Y = 382, OPT_TOGGLE_W = 86, OPT_TOGGLE_H = 45,
	OPT_TOGGLEOFF_X = 413, OPT_TOGGLEOFF_Y = 437,

	//파란 화살표 버튼
	OPT_ARROW_X = 866, OPT_ARROW_Y = 424, OPT_ARROW_W = 65, OPT_ARROW_H = 62,

	//아이콘 3x3. 좌->우 열, 위->아래 행.
	OPT_ICON_W = 66, OPT_ICON_H = 66,
	OPT_ICONCOL0 = 9, OPT_ICONCOL1 = 88, OPT_ICONCOL2 = 166,
	OPT_ICONROW0 = 441, OPT_ICONROW1 = 511, OPT_ICONROW2 = 581,
};

//option.png 한 조각을 그대로 그린다.
static void DrawOptionPart(int sx, int sy, int sw, int sh, float x, float y, float sc)
{
	DrawImage(sw, sh, sx, sy, x, y, false, false, false, false, false, sc, sprite[OPTION_IMG], OPTION_IMG);
}

//가운데를 늘려서 원하는 크기로 만드는 9분할. 모서리는 원본 비율을 지킨다.
static void DrawOptionPart9(int sx, int sy, int sw, int sh, int edge, float x, float y, float w, float h, float sc)
{
	float e = (float)edge * sc;
	int   me = sw - edge * 2;	//가운데 소스 폭
	int   mv = sh - edge * 2;	//가운데 소스 높이
	float mw = w - e * 2;
	float mh = h - e * 2;

	if (w <= 0 || h <= 0)
		return;

	if (mw < 0) mw = 0;
	if (mh < 0) mh = 0;

	//늘린 조각과 모서리가 맞닿는 곳은 반올림 때문에 1픽셀 틈이 생긴다.
	//변과 가운데를 양쪽으로 OV만큼 키워 겹쳐 그린 뒤, 모서리를 그 위에 덮는다.
	{
		const float OV = 1.0f;
		float ow = mw + OV * 2;
		float oh = mh + OV * 2;

		//위/아래 변
		if (mw > 0 && me > 0) {
			DrawImageScale(me, edge, sx + edge, sy, x + e - OV, y, false, false, false, false, false, ow / (float)me, sc, sprite[OPTION_IMG], OPTION_IMG);
			DrawImageScale(me, edge, sx + edge, sy + sh - edge, x + e - OV, y - h + e, false, false, false, false, false, ow / (float)me, sc, sprite[OPTION_IMG], OPTION_IMG);
		}

		//좌/우 변
		if (mh > 0 && mv > 0) {
			DrawImageScale(edge, mv, sx, sy + edge, x, y - e + OV, false, false, false, false, false, sc, oh / (float)mv, sprite[OPTION_IMG], OPTION_IMG);
			DrawImageScale(edge, mv, sx + sw - edge, sy + edge, x + w - e, y - e + OV, false, false, false, false, false, sc, oh / (float)mv, sprite[OPTION_IMG], OPTION_IMG);
		}

		//가운데
		if (mw > 0 && mh > 0 && me > 0 && mv > 0)
			DrawImageScale(me, mv, sx + edge, sy + edge, x + e - OV, y - e + OV, false, false, false, false, false, ow / (float)me, oh / (float)mv, sprite[OPTION_IMG], OPTION_IMG);
	}

	//네 모서리
	DrawOptionPart(sx, sy, edge, edge, x, y, sc);
	DrawOptionPart(sx + sw - edge, sy, edge, edge, x + w - e, y, sc);
	DrawOptionPart(sx, sy + sh - edge, edge, edge, x, y - h + e, sc);
	DrawOptionPart(sx + sw - edge, sy + sh - edge, edge, edge, x + w - e, y - h + e, sc);
}

//창을 세로로 늘린다. y축 스케일을 키우면 테두리가 뭉개지므로
//중간 띠(OPT_WIN_MID)를 필요한 만큼 반복해서 쌓아 올린다.
static void DrawOptionWindow(float x, float y, float w, float h)
{
	float s = w / (float)OPT_WIN_W;
	float topH = (float)OPT_WIN_TOP_H * s;
	float botH = (float)OPT_WIN_BOT_H * s;
	//띠 하나를 그린 뒤 원본 1픽셀만큼 덜 내려간다.
	//딱 맞게 내려가면 반올림 때문에 이음매에 1픽셀 틈이 생긴다.
	float step = (float)(OPT_WIN_MID_H - 1) * s;
	float rest = h - topH - botH;
	float cy = y - topH;

	DrawOptionPart(OPT_WIN_X, OPT_WIN_TOP_Y, OPT_WIN_W, OPT_WIN_TOP_H, x, y, s);

	while (rest > 0.5f) {
		if (rest >= step) {
			DrawOptionPart(OPT_WIN_X, OPT_WIN_MID_Y, OPT_WIN_W, OPT_WIN_MID_H, x, cy, s);
			cy -= step;
			rest -= step;
		}
		else {
			//마지막 자투리는 띠를 잘라서 채운다. 모자라지 않게 한 픽셀 넉넉히 자른다.
			int cut = (int)(rest / s) + 1;

			DrawOptionPart(OPT_WIN_X, OPT_WIN_MID_Y, OPT_WIN_W, cut, x, cy, s);
			cy -= rest;
			rest = 0;
		}
	}

	DrawOptionPart(OPT_WIN_X, OPT_WIN_BOT_Y, OPT_WIN_W, OPT_WIN_BOT_H, x, cy, s);
}

//섹션 제목 리본
static void DrawOptionRibbon(const char* title, float x, float y, float w, float h, float sc)
{
	DrawOptionPart9(OPT_RIBBON_X, OPT_RIBBON_Y, OPT_RIBBON_W, OPT_RIBBON_H, OPT_RIBBON_EDGE, x, y, w, h, sc);

	//리본은 왼쪽 끝의 금색 장식이 글자를 밀어내므로 그만큼 오른쪽으로 옮겨서 가운데 정렬한다.
	SetFontColor(COLOR_WHITE);
	CenterTextStr(title, x + w * 0.5f + h * 0.24f, y - h * 0.5f + (float)FONT_HEIGHT * OPTIONTEXTZOOM / 2, OPTIONTEXTZOOM);
	SetFontColor(COLOR_WHITE);
}

//아이콘 + 이름으로 시작하는 한 줄. 오른쪽에 무엇을 붙일지는 호출한 쪽이 정한다.
static void DrawOptionRowLabel(int iconSx, int iconSy, const char* label, float x, float y, float rowH)
{
	float iconSize = rowH * 0.7f;
	float iconSc = iconSize / (float)OPT_ICON_W;

	DrawOptionPart(iconSx, iconSy, OPT_ICON_W, OPT_ICON_H, x + rowH * 0.14f, y - (rowH - iconSize) / 2, iconSc);

	SetFontColor(COLOR_WHITE);
	DrawTextStr(label, x + rowH * 0.14f + iconSize + rowH * 0.2f, y - rowH / 2 + (float)FONT_HEIGHT * OPTIONROWTEXTZOOM / 2, OPTIONROWTEXTZOOM);
}

//ON/OFF 토글. 오른쪽 끝에 붙는다.
static void DrawOptionToggle(bool on, float rightX, float centerY, float toggleH, int touchFunc)
{
	float sc = toggleH / (float)OPT_TOGGLE_H;
	float toggleW = (float)OPT_TOGGLE_W * sc;
	float tx = rightX - toggleW;
	float ty = centerY + toggleH / 2;

	if (on)
		DrawOptionPart(OPT_TOGGLEON_X, OPT_TOGGLEON_Y, OPT_TOGGLE_W, OPT_TOGGLE_H, tx, ty, sc);
	else
		DrawOptionPart(OPT_TOGGLEOFF_X, OPT_TOGGLEOFF_Y, OPT_TOGGLE_W, OPT_TOGGLE_H, tx, ty, sc);

	SetRectPoint(tx, ty, toggleW, toggleH, touchFunc);
}

void OptionDraw(int x, int y, float zoom)
{
	const float w = (float)POPUPWINDOWSIZE_X * zoom;
	const float h = (float)POPUPWINDOWSIZE_Y * zoom;
	const float s = w / (float)OPT_WIN_W;		//창을 팝업 폭에 맞춘 배율

	const float RIBBONH = 40 * zoom;
	const float ROWH = 57 * zoom;
	const float SECTIONGAP = 5 * zoom;
	const float RIBBONW = 160 * zoom;
	const float TOGGLEH = ROWH * 0.78f;

	float innerL = x + 22.0f * s;
	float innerR = x + w - 22.0f * s;
	float innerW = innerR - innerL;

	float footH = (float)OPT_FOOT_H * s;
	float footY = y - h + 20.0f * s + footH;	//하단 띠의 위쪽 좌표
	float panelTop = y - 82.0f * s;
	float panelBottom = footY + 4.0f * s;
	float panelH = panelTop - panelBottom;

	float cy;			//지금 그릴 줄의 위쪽 좌표
	float groupTop;
	float rowRight;
	float bx, bw;
	int i;

	//창 + 본문 패널
	DrawOptionWindow(x, y, w, h);
	DrawOptionPart9(OPT_PANEL_X, OPT_PANEL_Y, OPT_PANEL_W, OPT_PANEL_H, OPT_PANEL_EDGE, innerL, panelTop, innerW, panelH, s * 0.5f);

	//타이틀. 가운데의 기어 방패를 피해 왼쪽으로 빼고 조금 내려 그린다.
	SetFontColor(COLOR_WHITE);
	CenterTextStr("환경설정", x + w / 2 - 180.0f * zoom, y - 30.0f * s - 32.0f * zoom + (float)FONT_HEIGHT * OPTIONTITLEZOOM / 2, OPTIONTITLEZOOM);

	//타이틀바의 X버튼은 창 이미지에 이미 그려져 있다. 터치영역만 얹는다.
	SetRectPoint(x + (float)OPT_CLOSE_X * s, y - (float)OPT_CLOSE_Y * s, (float)OPT_CLOSE_W * s, (float)OPT_CLOSE_H * s, TOUCH_FUNC_POPUP_CLOSE);

	//글자와 버튼을 키워야 해서 좌우 여백을 최대한 줄여 쓴다.
	innerL += 7.0f * zoom;
	innerR -= 7.0f * zoom;
	innerW = innerR - innerL;
	rowRight = innerR - 6.0f * zoom;

	cy = panelTop - 9.0f * zoom;

	//----- 사운드 -----
	DrawOptionRibbon("사운드", innerL, cy, RIBBONW, RIBBONH, s * 0.6f);
	cy -= RIBBONH + 4 * zoom;

	groupTop = cy;
	DrawOptionPart9(OPT_GROUP_X, OPT_GROUP_Y, OPT_GROUP_W, OPT_GROUP_H, OPT_GROUP_EDGE, innerL, groupTop, innerW, ROWH * 2, s * 0.5f);

	DrawOptionRowLabel(OPT_ICONCOL1, OPT_ICONROW0, textId[TEXT_BGM], innerL, cy, ROWH);
	DrawOptionToggle(option.bgm != 0, rowRight, cy - ROWH / 2, TOGGLEH, TOUCH_FUNC_OPTION_BGM);
	cy -= ROWH;

	DrawOptionRowLabel(OPT_ICONCOL0, OPT_ICONROW0, textId[TEXT_SE], innerL, cy, ROWH);
	DrawOptionToggle(option.se != 0, rowRight, cy - ROWH / 2, TOGGLEH, TOUCH_FUNC_OPTION_SE);
	cy -= ROWH + SECTIONGAP;

	//----- 알림 -----
	DrawOptionRibbon("알림", innerL, cy, RIBBONW, RIBBONH, s * 0.6f);
	cy -= RIBBONH + 4 * zoom;

	//알림 설정 버튼이 아래 테두리에 닿지 않게 바탕패널만 조금 더 늘려준다.
	groupTop = cy;
	DrawOptionPart9(OPT_GROUP_X, OPT_GROUP_Y, OPT_GROUP_W, OPT_GROUP_H, OPT_GROUP_EDGE, innerL, groupTop, innerW, ROWH * 2 + 16.0f * zoom, s * 0.5f);

	DrawOptionRowLabel(OPT_ICONCOL2, OPT_ICONROW0, "푸시 알림", innerL, cy, ROWH);
	DrawOptionToggle(option.pushAlarm != 0, rowRight, cy - ROWH / 2, TOGGLEH, TOUCH_FUNC_OPTION_PUSHALARM);
	cy -= ROWH;

	//알림 설정(가로로 긴 파란 버튼 한 줄)
	{
		float bh = ROWH * 0.88f + 4.0f * zoom;
		float by = cy - (ROWH - bh) / 2;
		float iconSize = bh * 0.7f;

		bx = innerL + 16.0f * zoom;
		bw = rowRight - bx;

		DrawOptionPart9(OPT_BTNBLUE_X, OPT_BTNBLUE_Y, OPT_BTNBLUE_W, OPT_BTNBLUE_H, OPT_BTN_EDGE, bx, by, bw, bh, s * 0.5f);
		DrawOptionPart(OPT_ICONCOL2, OPT_ICONROW2, OPT_ICON_W, OPT_ICON_H, bx + bh * 0.2f, by - (bh - iconSize) / 2, iconSize / (float)OPT_ICON_W);

		SetFontColor(COLOR_WHITE);
		DrawTextStr("알림 설정", bx + bh * 0.2f + iconSize + bh * 0.24f, by - bh / 2 + (float)FONT_HEIGHT * OPTIONTEXTZOOM / 2, OPTIONTEXTZOOM);

		DrawOptionPart(OPT_ARROW_X, OPT_ARROW_Y, OPT_ARROW_W, OPT_ARROW_H, bx + bw - bh * 0.9f, by - (bh - bh * 0.7f) / 2, bh * 0.7f / (float)OPT_ARROW_H);

		SetRectPoint(bx, by, bw, bh, TOUCH_FUNC_OPTION_PUSHALARM);
	}
	//늘어난 알림 패널만큼 기타 섹션 전체를 아래로 내린다.
	cy -= ROWH + SECTIONGAP + 16.0f * zoom;

	//----- 기타 -----
	DrawOptionRibbon("기타", innerL, cy, RIBBONW, RIBBONH, s * 0.6f);
	cy -= RIBBONH + 4 * zoom;

	groupTop = cy;
	DrawOptionPart9(OPT_GROUP_X, OPT_GROUP_Y, OPT_GROUP_W, OPT_GROUP_H, OPT_GROUP_EDGE, innerL, groupTop, innerW, ROWH * 3, s * 0.5f);

	DrawOptionRowLabel(OPT_ICONCOL0, OPT_ICONROW1, textId[TEXT_VIBRATION], innerL, cy, ROWH);
	DrawOptionToggle(option.vibration != 0, rowRight, cy - ROWH / 2, TOGGLEH, TOUCH_FUNC_OPTION_VIBRATION);
	cy -= ROWH;

	//언어(값이 적힌 파란 버튼)
	DrawOptionRowLabel(OPT_ICONCOL1, OPT_ICONROW1, textId[TEXT_LANGUAGE], innerL, cy, ROWH);
	{
		float bh = ROWH * 0.82f;
		float by = cy - (ROWH - bh) / 2;

		bw = 176.0f * zoom;
		bx = rowRight - bw;

		DrawOptionPart9(OPT_BTNBLUE_X, OPT_BTNBLUE_Y, OPT_BTNBLUE_W, OPT_BTNBLUE_H, OPT_BTN_EDGE, bx, by, bw, bh, s * 0.5f);

		SetFontColor(COLOR_WHITE);
		CenterTextStr(textId[TEXT_KOREAN + option.language], bx + bw / 2 - bh * 0.3f, by - bh / 2 + (float)FONT_HEIGHT * OPTIONTEXTZOOM / 2, OPTIONTEXTZOOM);

		DrawOptionPart(OPT_ARROW_X, OPT_ARROW_Y, OPT_ARROW_W, OPT_ARROW_H, bx + bw - bh * 0.9f, by - (bh - bh * 0.7f) / 2, bh * 0.7f / (float)OPT_ARROW_H);

		SetRectPoint(bx, by, bw, bh, TOUCH_FUNC_OPTION_LANGUAGE);
	}
	cy -= ROWH;

	//버전 정보
	DrawOptionRowLabel(OPT_ICONCOL1, OPT_ICONROW2, "버전 정보", innerL, cy, ROWH);
	SetFontColor(COLOR_WHITE);
	DrawTextStrSystem("Ver 1.0.0", rowRight, cy - ROWH / 2 + (float)FONT_HEIGHT * OPTIONROWTEXTZOOM / 2, OPTIONROWTEXTZOOM, RIGHT, true);

	//----- 하단 띠 + 버튼 3개 -----
	DrawOptionPart9(OPT_FOOT_X, OPT_FOOT_Y, OPT_FOOT_W, OPT_FOOT_H, OPT_FOOT_EDGE, x + 12.0f * s, footY, w - 24.0f * s, footH, s);

	{
		const char* footText[3] = { "고객센터", "이용약관", "개인정보처리방침" };
		const int footTouch[3] = { TOUCH_FUNC_OPTION_HELP, TOUCH_FUNC_OPTION_POLICY, TOUCH_FUNC_OPTION_POLICY };
		float gap = 8.0f * zoom;
		float bh2 = footH * 0.68f;
		float by2 = footY - (footH - bh2) / 2;

		bw = (innerW - gap * 2) / 3;

		for (i = 0; i < 3; i++) {
			//글자는 섹션 제목 크기까지 키우되, 버튼을 넘칠 때만 그만큼 줄인다.
			float tz = OPTIONTEXTZOOM;
			float maxW = bw - 14.0f * zoom;
			float tw;

			bx = innerL + (bw + gap) * i;

			DrawOptionPart9(OPT_BTNBLUE_X, OPT_BTNBLUE_Y, OPT_BTNBLUE_W, OPT_BTNBLUE_H, OPT_BTN_EDGE, bx, by2, bw, bh2, s * 0.5f);

			tw = StringWidth(footText[i], tz);
			if (tw > maxW && tw > 0)
				tz *= (maxW / tw) * 0.95f;	//넘치는 글자는 5% 더 줄여 좌우에 여유를 준다

			SetFontColor(COLOR_WHITE);
			CenterTextStr(footText[i], bx + bw / 2, by2 - bh2 / 2 + (float)FONT_HEIGHT * tz / 2, tz);

			SetRectPoint(bx, by2, bw, bh2, footTouch[i]);
		}
	}

	SetFontColor(COLOR_WHITE);
}


void SlotDraw(int x, int y, int crew1Cmf, int crew2Cmf, int crew3Cmf, float zoom)
{
	DrawImage(SLOTSIZE_X, SLOTSIZE_Y, 0, 0,
		x, y,
		false, false, false, false, false,
		0.35f * zoom, sprite[SLOT_IMG], SLOT_IMG);


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

void DeptDiscountDraw(int x, int y, float zoom)
{
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	int itemType = it->type;
	int itemDetail = it->detail;
	int itemGrade = it->grade;
	int collectionIdx = GetCollectionIdx(itemType, itemDetail, itemGrade);
	float itemValueZoom = 1.0f;
	float w = (float)ROULETTECARDSIZE_X * zoom;
	float h = (float)ROULETTECARDSIZE_Y * zoom;
	float bigNumWidth = (float)ITEMICONSIZE * itemValueZoom * zoom * 1.7f;
	int type;

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

}


void DoubleGoldDraw(int x, int y, float zoom)
{
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	int itemType = it->type;
	int itemDetail = it->detail;
	int itemGrade = it->grade;
	int collectionIdx = GetCollectionIdx(itemType, itemDetail, itemGrade);
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
	case BOX_REWARD0:
		return 10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000;
	case BOX_REWARD1:	//카드 한장	//BOX_CHEST1
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000);
	case BOX_REWARD2:	//카드 두장	//BOX_CHEST2
		return (10000 + robin.stage * 1000 + robin.stage * robin.stage * 1000) * 10;
	case BOX_REWARD3:	//카드 세장	//BOX_CHEST3
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
	int scrollDy = 0;
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
		//현재 스크롤 기준으로 아이템이 몇개인지 확인
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
	//4곳을 바깥으로 나가는것으로 하자
	SetRectPoint(0, DY, DX, (DY - *(ucPtr + 1)) / 2, TOUCH_ALERT_NO);//위쪽
	SetRectPoint(0, DY / 2 + *(ucPtr + 1) / 2, (DX - *ucPtr) / 2, *(ucPtr + 1), TOUCH_ALERT_NO);//왼쪽
	SetRectPoint(DX / 2 + *ucPtr / 2, DY / 2 + *(ucPtr + 1) / 2, (DX - *ucPtr) / 2, *(ucPtr + 1), TOUCH_ALERT_NO);//오른쪽
	SetRectPoint(0, DY / 2 - *(ucPtr + 1) / 2, DX, (DY - *(ucPtr + 1)) / 2, TOUCH_ALERT_NO);//아래쪽

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
	int itemType, itemDetail, itemGrade, itemLv, skillLv;
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
	int row = 1;//가로로 몇개인지
	int col = 1;//세로로 몇줄인지
	float width;
	int remainNewItemCnt;
	//성 등장하는 거 없애주기
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
	int count = 1;
	float goldZoom = 0.8f * zoom;
	float width;
	int enemyCrewY = 400 * _2X;
	int beforeEnemyCrewY;
	int stageBossIdx = GetStageBossIdx();
	int stageBossType = GetStageBossType();
	int stageBossMaxHp = (robin.stage * TOTALROOM + robin.room + 1) * (100 + enemyData[stageBossType * ENEMYDATASIZE + 3]);
	int itemType, itemDetail, itemGrade, itemCnt;
	int rewardType, rewardDetail, rewardGrade, rewardCnt;
	int curStar, maxStar;
	float yGap = (float)-32 * _2X * zoom;


	int stageInfoCurFrame = stageInfoFrame;
	int bFrame = 2;

	float menuZoom;
	float fontZoom = Max(1.2f, (float)(STAGECLEARDELAY_ALPHA - stageInfoCurFrame) * 0.2f / MOTIONDIV);

	long long getGoldNum = 0;
	long long getHeartNum = 0;
	long long getMedalNum = 0;
	long long getStarNum = 0;
	long long getHammerNum = 0;

	bool crewMenuDraw = false;
	bool equipMenuDraw = false;

	int totalStar = 0;
	long long betCnt = bossGold[stage] * GetBetHeart(ao[PLAYER].equip[EQUIP_WEAPON].detail, ao[PLAYER].equip[EQUIP_WEAPON].grade, bet);


	long long betGold = GetStageAdmissionFee();


	if (cur == false)
		stageInfoCurFrame = FPS * 10;

	//ao[ENEMY].type = stageEnemy[robin.stage * TOTALROOM + robin.room];
	SetEnemy(&ao[ENEMY]);
	ao[ENEMY].active = false;
	//보스

	//robin.stage = 9;


	switch (stageInfoDepth) {
	case STAGEINFO_CREWDROP:
		DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

		//보스 정보
		DrawStageLabel(x + (float)(DX / 2) * zoom, y + (float)(8 * _2X) * zoom, TEXT_STAGE, robin.stage, robin.room, true, zoom);

		//웨이브 보스
		//if (stageInfoCurFrame > 20)
		DrawCmfDetailShadow(enemyData[stageBossType * ENEMYDATASIZE + ENEMYDATA_CMF], frame / 4 % crewPos[stageBossType * CREWDATASIZE], x + (float)(DX / 2) * zoom, y - (float)108 * _2X * zoom + Max(0 * _2X, (FPS / 2 - stageInfoCurFrame) * 16 * _2X) * zoom + yGap, RIGHT, zoom);

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

				DrawRewardCard(rewardType, rewardDetail, rewardGrade, 1, rewardCnt, x + (float)(DX / 2 - (rewardItemCnt) * (REWARDCARDSIZE_X + 4 * _2X) * 1.5f / 2 + i * (REWARDCARDSIZE_X + 2 * _2X) * 1.5f + 38 * _2X) * zoom, y - (float)(224 * _2X) * zoom + yGap, false, 1.5f * zoom, false, false, true, curStar, maxStar, true, 0);

			}
			//width = (float)(ITEMICONSIZE * 1.5f + 4 * _2X) * goldZoom + GetBigNumGoldDx(betCnt, false, FONT_GOLD_LARGE, false, true, (float)(256 * _2X - 32 * _2X) * zoom, goldZoom);


		}


		break;
	case STAGEINFO_CREWGACHA:


		//SetAlpha(28);
		//SetAlpha(32);



		//width = (float)(ITEMICONSIZE * 1.5f + 4 * _2X) * goldZoom + GetBigNumGoldDx(bossHp, false, FONT_GOLD_LARGE, false, true, (float)(240 * _2X - 32 * _2X) * zoom, goldZoom);


		SetAlpha(Max(0, 32 - stageInfoFrame));
		DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);
		SetAlpha(32);


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

					}
					else if (stageInfoCurFrame < STAGECLEARDELAY_LEVITATION) {
						beforeEnemyCrewY = enemyCrewY;

						enemyCrewY = (stageInfoCurFrame - STAGECLEARDELAY_HAPPYTIME) * 1 * _2X * 2 / MOTIONDIV;

					}
					else if (stageInfoCurFrame < STAGECLEARDELAY_ROTATION) {
						enemyCrewY = FPS * _2X;



					}
					else if (stageInfoCurFrame < STAGECLEARDELAY_TOGETHER) {
						enemyCrewY = STAGECLEARDELAY_TOGETHER - stageInfoCurFrame;
						//if (32 - (stageInfoCurFrame - STAGECLEARDELAY_ROTATION) / MOTIONDIV / 8 > 0) {
						SetAlpha(32 - (stageInfoCurFrame - STAGECLEARDELAY_ROTATION) / MOTIONDIV / 8);
						SetAlpha(32);
						//}
					}
					else if (stageInfoCurFrame < STAGECLEARDELAY_SELECTEDCREW) {
						enemyCrewY = 0;
						if (i == selectedCrew) {
							SetAlpha(Min(32, stageInfoCurFrame - STAGECLEARDELAY_TOGETHER));
							SetAlpha(32);
							DrawCmfDetail(CMF_NPC_HEART, PO_C122_SPARK0 + stageInfoCurFrame / MOTIONDIV % 8, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - DIORAMASIZE_Y / 2 + (float)8 * _2X + enemyCrewY - (float)Min(160 * _2X, stageInfoFrame * 4 * _2X) * zoom + (float)100 * _2X * zoom, LEFT, LOBBYZOOM, false, false);
						}
					}
					else if (stageInfoCurFrame < STAGECLEARDELAY_CREWAPPEAR) {
						enemyCrewY = 0;
						if (i == selectedCrew) {
						}
					}
					else if (stageInfoCurFrame < STAGECLEARDELAY_NEWCARD) {
						enemyCrewY = 0;
						if (i == selectedCrew) {

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

		//1.성과 동료들을 앞으로 내 세운 상태에서
		if (stageInfoCurFrame < STAGECLEARDELAY_APPEAR) {
			UnSectionClip(true);
			UnSectionClip(false);
		}
		//2.보스가 날라가고
		else if (stageInfoCurFrame < STAGECLEARDELAY_BOSSAWAY) {
			UnSectionClip(true);
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
		MemRect(0, DY, DX, DY, COLOR_BLACK);
		SetAlpha(32);

		DrawGoldAlpha(DX / 2, DY - GNBHEIGHT - 16 * _2X, ALPHA_STAGECLEAR, FONT_GOLD_LARGE, fontZoom, CENTER, true, false);

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
		//보상을 탭하라는 메뉴가 나오고
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

		DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);


		//세입자
		for (i = MAXCREW - 1; i >= 0; i--) {
			if (enemyHouse.crew[i] != null) {
				switch (stageInfoDepth) {
				case STAGEINFO_NEWSTAGE:
					beforeEnemyCrewY = enemyCrewY;

					enemyCrewY -= stageInfoCurFrame * 16 * _2X;

					if (enemyCrewY < 0)
						enemyCrewY = 0;

					break;
				}
			}

		}

		if (stageInfoCurFrame > 20) {
#ifdef PVPWITHUSER
			DrawPlayer(&ao[SOLDIER], frame / MOTIONDIV % 4, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)DIORAMASIZE_Y * zoom + (float)32 * _2X * zoom, LEFT, 2.0f * zoom * Max(1, FPS / 2 + 10 - stageInfoCurFrame) * 0.6f, false, false, true);

#else
			DrawCmfDetailShadow(enemyData[boss[stage] * ENEMYDATASIZE + ENEMYDATA_CMF], crewPos[boss[stage] * 5 + 0] + (FPS / 2 + 10 < stageInfoCurFrame ? frame / 4 / MOTIONDIV : 0) % crewPos[boss[stage] * 5 + 1], x + (float)(POPUPWINDOWSIZE_X - 160 * _2X) / 2 * zoom, y - (float)DIORAMASIZE_Y * zoom + (float)32 * _2X * zoom, LEFT, enemyZoom[boss[stage]] * enemyBossZoom[boss[stage]] * zoom * Max(1, FPS / 2 + 10 - stageInfoCurFrame) * 0.6f);
#endif
		}

		if (stageInfoCurFrame > 23) {
#ifdef PVPWITHUSER
			DrawLabel(x + (float)(POPUPWINDOWSIZE_X - 88 * _2X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X) * zoom, false, zoom);
			CenterText(TEXT_NICKNAME + 4, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)(DIORAMASIZE_Y - 32 * _2X + 10 * _2X) * zoom, zoom);
#else
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


		for (i = 0; i < MAXCREW; i++) {
			if (enemyHouse.crew[i] != null) {
				if (stageInfoCurFrame > 54 + i * 3) {

					detail = enemyHouse.crew[i];

					curStar = enemyHouse.crewCurStar[i];
					curMaxStar = enemyHouse.crewMaxStar[i];
					maxStar = crewData[detail * CREWDATASIZE + CREWDATASIZE - 1] + 1;
					signed long long upgradePrice = crewStarUpgradeGold[stage * MAXCREW * CREWMAXUPGRADELV + i * (CREWMAXUPGRADELV)+curStar] / CREWUPGRADEPER;




					if (stageUpgradeMotion[i] > 0 && stageUpgradeMotion[i] < 11) {
						ao[NPC].cmf = ao[NPC].type = ROBIN;
						ao[NPC].x = x + (float)(36 * _2X) * zoom + (float)(POPUPWINDOWSIZE_X - 30 * _2X) / 2 * (i % 2) * zoom;
						ao[NPC].y = y - (float)(336 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 6 * _2X) * (i / 2) * 1.2f * zoom;
						DrawPlayer(&ao[NPC], 2000 - 1 + LEVELUP_BACK0 + stageUpgradeMotion[i], ao[NPC].x, ao[NPC].y, false, zoom, false, false, false);

					}
					DrawCmfDetailShadow(enemyData[enemyHouse.crew[i] * ENEMYDATASIZE + ENEMYDATA_CMF], crewData[enemyHouse.crew[i] * 3 + 0], x + (float)(36 * _2X) * zoom + (float)(POPUPWINDOWSIZE_X - 30 * _2X) / 2 * (i % 2) * zoom, y - (float)(336 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 6 * _2X) * (i / 2) * 1.2f * zoom, RIGHT, enemyZoom[enemyHouse.crew[i]] * zoom);


					DrawStar(ICON_STAR, x + (float)(12 * _2X) * zoom + (float)(POPUPWINDOWSIZE_X - 30 * _2X) / 2 * (i % 2) * zoom + (float)90 * _2X * zoom, y - (float)(296 * _2X) * zoom - (float)(REWARDCARDSIZE_Y - 6 * _2X) * (i / 2) * 1.2f * zoom, curStar, curMaxStar, maxStar, CENTER, true, zoom);
					//최대값에 도달하면
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
			//성주와 일기토
			DrawTextButton(x + (float)(DX / 2 - 0 * _2X) * zoom, y - (float)(416 * _2X) * zoom, (float)(120 * _2X) * zoom, (float)(48 * _2X) * zoom, frame, totalStar < 10 || robin.bossRoom == true ? true : false, 1.0f, false, TEXT_LORD_DUEL);
			//if (totalStar < MAXSTARPERHOUSE || robin.bossRoom == true)
			//	grayScale = 32;
			DrawGoldAlpha(x + (float)(DX / 2 - 0 * _2X + 120 * _2X / 2) * zoom, y - (float)(416 * _2X + 22 * _2X) * zoom, ALPHA_BOSSDUEL, FONT_GOLD_LARGE, (float)zoom * 0.7f, CENTER, false, false);
			grayScale = 0;
			//if (totalStar == MAXSTARPERHOUSE && robin.bossRoom == false)
			//	SetRectPoint(x + (float)(DX / 2 - 0 * _2X) * zoom, y - (float)(416 * _2X) * zoom, (float)(120 * _2X) * zoom, (float)(48 * _2X) * zoom, TOUCH_FUNC_GOTOSTAGEBOSS);
		}

		BarDraw(&bar[BAR_GOLD], bar[BAR_GOLD].zoom);

		//뉴스테이지에 대한 내용이 뜨고
		fontZoom = Max(1.2f, (float)(54 + MAXCREW * 3 + FPS / 2 - stageInfoCurFrame) * 0.2f / MOTIONDIV);

		if (stageInfoCurFrame > 54 + MAXCREW * 3)
			DrawGoldAlpha(DX / 2, DY / 2 + 248 * _2X, ALPHA_NEWSTAGE, FONT_GOLD_LARGE, fontZoom, CENTER, true, false);

		//게임으로 돌아간다.

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


	//현재 타겟팅되는 하우스


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
// 최종 그리기 함수
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

	
	// 1. 배경 및 큰 UI
	for (i = 0; i < 2; i++)
		DrawImage(crewMenuUiData[i * MENUUIDATACNT + 0], crewMenuUiData[i * MENUUIDATACNT + 1], crewMenuUiData[i * MENUUIDATACNT + 2], crewMenuUiData[i * MENUUIDATACNT + 3], x + (float)crewMenuUiData[i * MENUUIDATACNT + 4] * zoom, y - (float)(crewMenuUiData[i * MENUUIDATACNT + 5]) * zoom, false, false, false, false, false, zoom, sprite[crewMenuUiData[i * MENUUIDATACNT + 6]], crewMenuUiData[i * MENUUIDATACNT + 6]);

	CenterText(TEXT_BORDERGUARD, x + (float)160 * _2X * zoom, y - (float)40 * zoom, 2.0f * zoom);
	CenterText(TEXT_CREW_LISTEDIT, x + (float)160 * _2X * zoom, y - (float)90 * zoom, 1.1f * zoom);
	CenterText(TEXT_CREW_CURRENTLIST, x + (float)160 * _2X * zoom, y - (float)138 * zoom, 1.0f * zoom);
	
	//성과 맥스 별
	SetColor(COLOR_BROWN);
	for (i = 0; i < 4; i++) {
		DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, x + (float)(500) * zoom + (float)solidPosition[2 * i + 0] * 1 * _2X * zoom, y - (float)(12) * zoom + (float)solidPosition[2 * i + 1] * 1 * _2X * zoom, false, false, false, false, false, 0.1f * zoom, sprite[MAP_DIORAMA_IMG + CASTLE_ADELINE], MAP_DIORAMA_IMG + CASTLE_ADELINE);
	}
	SetColor(false);
	DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, x + (float)(500) * zoom, y - (float)(12) * zoom, false, false, false, false, false, 0.1f * zoom, sprite[MAP_DIORAMA_IMG + CASTLE_ADELINE], MAP_DIORAMA_IMG + CASTLE_ADELINE);

	
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

	//슬롯 6개짜리 이미지를 그려준다.
	
	DrawImage(1024, 220, 0, 217,
		x + WINX / 2 - (float)1024 / 2 * 0.61f * zoom, y - (float)168 * zoom,
		false, false, false, false, false,
		0.61f * zoom, sprite[SLOT_IMG], SLOT_IMG);

	//현재 선택되어 있는 캐릭터 6개
	for (i = 0; i < MAXCREW; i++) {
		int slotX = x + (float)(16 + 102 * (i % MAXCREW)) * zoom;
		int slotY = y - (float)(168 + 180 * (i / MAXCREW)) * zoom;

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

			//튜토리얼: 방금 편성한 동료는 위에서 뛰어 내려앉는다. 성 위 등장 연출과 결을 맞춘 것이다.
			float dropY = 0.0f;

			if (tutorialCrewStep == TUTORIAL_CREWSTEP_SLOTSHOW && i == TUTORIAL_CREW_SLOT)
				dropY = GetTutorialCrewDropOffset(tutorialCrewStepFrame, zoom);

			int crewCmf = enemyData[crewData[itemDetail * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_CMF];
			int crewType = crewData[itemDetail * CREWDATASIZE + CREWDATA_TYPE];
			DrawCmfDetailShadow(crewCmf, crewPos[crewType * 5 + 0] + (menuX == i ? (frame / 4 / MOTIONDIV) % crewPos[crewType * 5 + 1] : 0),
				slotX + (float)52 * zoom,
				slotY - (float)88 * zoom + dropY,
				RIGHT, enemyZoom[crewType] * 1.3f * zoom);
			DrawStar(ICON_STAR, slotX + (float)52 * zoom, slotY - (float)102 * zoom, itemStar, itemStar, itemStar, CENTER, false, 0.6f * zoom);
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

		//튜토리얼 1단: 동료를 넣을 자리를 먼저 고르게 한다.
		//사각형은 바로 위 SetRectPoint()에 넘긴 것과 같은 값이라 스팟과 터치영역이 겹친다.
		if (GetTutorialCrewSlotTouchFunc() == TOUCH_FUNC_MENUX_1 + i) {
			float rw = (float)CARDSIZE_X * 0.45f * zoom;
			float rh = (float)CARDSIZE_Y * 0.4f * zoom;
			float pulse = 1.0f + sinf((float)frame * 0.1f) * 0.06f;

			//DrawHand()에 넘기는 좌표가 손 그림의 좌상단이라 자기 크기만큼 물려야 손끝이 중앙에 온다.
			float handZoom = 2.0f;
			float handW = (float)imgArray[IMG_HAND1 * 4 + 2] * handZoom;
			float handH = (float)imgArray[IMG_HAND1 * 4 + 3] * handZoom;

			DrawHand(slotX + rw / 2 - handW, slotY - rh / 2 + handH, robin.playtime / MOTIONDIV, handZoom);

			//슬롯은 가로로 붙어 있어 옆 슬롯까지 밝아지지 않도록 폭 기준으로 반경을 잡는다.
			SetSpotlight(slotX + rw / 2, slotY - rh / 2,
				rw * 0.55f * pulse, rw * 1.00f * pulse, 0.25f);
		}

		//튜토리얼 4단: 편성된 자리를 밝혀서 어디에 들어갔는지 보여준다. 손은 띄우지 않는다.
		//누를 것이 없고 잠깐 보여주기만 하는 구간이라 손이 있으면 오히려 눌러야 하는 줄 안다.
		if (tutorialCrewStep == TUTORIAL_CREWSTEP_SLOTSHOW && i == TUTORIAL_CREW_SLOT) {
			float rw = (float)CARDSIZE_X * 0.45f * zoom;
			float rh = (float)CARDSIZE_Y * 0.4f * zoom;
			float pulse = 1.0f + sinf((float)frame * 0.1f) * 0.06f;

			SetSpotlight(slotX + rw / 2, slotY - rh / 2,
				rw * 0.55f * pulse, rw * 1.00f * pulse, 0.25f);
		}
	}
	


	//SetAlpha(32 - Abs(frame / MOTIONDIV % 32 - 16));
	//SetAlpha(32);

	// 2. 크루 리스트
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

		//튜토리얼: 새로 얻은 동료 카드만 밝게 남기고 나머지를 어둡게 덮는다.
		//사각형은 DrawItemCard()가 카드 터치영역으로 등록하는 것과 같은 값이다.
		if (GetTutorialCrewCardTouchFunc() == TOUCH_FUNC_ITEMDETAIL + itemInvenIdxList[i]) {
			int itemStar = GetItemStar(itemType, itemDetail, itemGrade);
			float cardZoom = CARDDEFAULTZOOM * zoom;
			float rx = cardX + (float)equipBgData[(itemStar - 1) * 6 + 4] * cardZoom;
			float ry = cardY - (float)equipBgData[(itemStar - 1) * 6 + 5] * cardZoom;
			float rw = (float)equipBgData[(itemStar - 1) * 6 + 0] * cardZoom;
			float rh = (float)equipBgData[(itemStar - 1) * 6 + 1] * cardZoom;
			float pulse = 1.0f + sinf((float)frame * 0.1f) * 0.06f;

			//손은 카드 한가운데에, 크게.
			//DrawHand()에 넘기는 좌표가 손 그림의 좌상단이라, 중앙을 그냥 주면 손이
			//중앙에서 오른쪽 아래로 뻗는다. 자기 크기만큼 왼쪽/위로 물려 손끝이 중앙에 오게 한다.
			float handZoom = 2.4f;
			float handW = (float)imgArray[IMG_HAND1 * 4 + 2] * handZoom;
			float handH = (float)imgArray[IMG_HAND1 * 4 + 3] * handZoom;

			DrawHand(rx + rw / 2 - handW, ry - rh / 2 + handH, robin.playtime / MOTIONDIV, handZoom);

			//카드는 폭 rw, 가로 간격은 INVENTORY_GAP_X * zoom이라 카드 사이 여백이 거의 없다.
			//반경을 카드 높이 기준으로 잡으면 옆 카드까지 통째로 밝아지므로 폭 기준으로 잡는다.
			//옆 카드의 안쪽 모서리까지가 중심에서 (INVENTORY_GAP_X - 240 * CARDDEFAULTZOOM / 2) * zoom
			//이므로 그 안쪽에서 감쇠가 끝나도록 둔다.
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

	//최외각 테두리
	MemRectFrameThick(x, y, WINX, WINY, 0x2C2578, (float)OUTTHICK * zoom);
	//그안에 테두리
	MemRectFrameThick(x + OUTTHICK, y - OUTTHICK, WINX - 2 * OUTTHICK, WINY - 2 * OUTTHICK, 0x7653D3, INTTHICK);

	switch (menuDepth) {
	case 1:
		ResetRectPoint();
		//ScreenDarken(SCREENDARKEN);
		MemRect(x, y, WINX, WINY, 0xD8D6FB);
		// 1. 배경 및 큰 UI
		for (i = 0; i < 2; i++)
			DrawImage(crewMenuUiData[i * MENUUIDATACNT + 0], crewMenuUiData[i * MENUUIDATACNT + 1], crewMenuUiData[i * MENUUIDATACNT + 2], crewMenuUiData[i * MENUUIDATACNT + 3], x + (float)crewMenuUiData[i * MENUUIDATACNT + 4] * zoom, y - (float)(crewMenuUiData[i * MENUUIDATACNT + 5]) * zoom, false, false, false, false, false, zoom, sprite[crewMenuUiData[i * MENUUIDATACNT + 6]], crewMenuUiData[i * MENUUIDATACNT + 6]);

		CenterText(TEXT_BORDERGUARD, x + (float)160 * _2X * zoom, y - (float)40 * zoom, 2.0f * zoom);
		CenterText(TEXT_ACTIONCARDINFO, x + (float)160 * _2X * zoom, y - (float)90 * zoom, 1.1f * zoom);


		ItemDetailDraw(&robin.inven[menuItem], x + (float)16 * zoom, y - (float)152 * zoom, CARDDEFAULTZOOM * 1.2f * zoom, false, false);
		
		DrawTouchLargeButton(x + (float)(80) * zoom, y - (float)(694) * zoom, BUYBUTTON_X, BUYBUTTON_Y, textId[TEXT_EQUIP], TOUCH_FUNC_EQUIP_INVENTORY + GetInvenIdx(robin.inven[menuItem].type, robin.inven[menuItem].detail, robin.inven[menuItem].grade), FRAME_GREEN, 1.0f * zoom);
		DrawTouchLargeButton(x + (float)(380) * zoom, y - (float)(694) * zoom, BUYBUTTON_X, BUYBUTTON_Y, textId[TEXT_UPGRADE], TOUCH_FUNC_EQUIP_INVENTORY + GetInvenIdx(robin.inven[menuItem].type, robin.inven[menuItem].detail, robin.inven[menuItem].grade), FRAME_RED, 1.0f * zoom);

		//튜토리얼 3단: 장착 버튼을 누르게 한다.
		//사각형은 바로 위 DrawTouchLargeButton()에 넘긴 것과 같은 값이라 스팟과 터치영역이 겹친다.
		if (GetTutorialCrewEquipTouchFunc()) {
			float bx = x + (float)(80) * zoom;
			float by = y - (float)(694) * zoom;
			float bw = (float)BUYBUTTON_X * zoom;
			float bh = (float)BUYBUTTON_Y * zoom;
			float pulse = 1.0f + sinf((float)frame * 0.1f) * 0.06f;

			//손 크기는 앞 단계(슬롯/카드 안내)와 같게 맞춘다.
			//DrawHand()에 넘기는 좌표가 손 그림의 좌상단이라 자기 크기만큼 물려야 손끝이 중앙에 온다.
			float handZoom = 2.0f;
			float handW = (float)imgArray[IMG_HAND1 * 4 + 2] * handZoom;
			float handH = (float)imgArray[IMG_HAND1 * 4 + 3] * handZoom;

			DrawHand(bx + bw / 2 - handW, by - bh / 2 + handH, robin.playtime / MOTIONDIV, handZoom);

			//버튼은 가로로 긴 편이라 폭 기준으로 잡으면 옆의 강화하기 버튼까지 밝아진다.
			//높이 기준으로 좁게 잡는다.
			SetSpotlight(bx + bw / 2, by - bh / 2,
				bh * 0.9f * pulse, bh * 1.6f * pulse, 0.25f);
		}

		//Tutorial: pulse a highlight around the EQUIP button while the EQUIP step is guiding the player to tap it.
		if (robin.demoSeen[DEMO_TUTORIAL_EQUIP] && !robin.demoSeen[DEMO_TUTORIAL_HEARTBET]) {
			float pulse = 0.9f + sinf((float)frame * 0.1f) * 0.1f;
			float hlW = (float)BUYBUTTON_X * zoom * pulse;
			float hlH = (float)BUYBUTTON_Y * zoom * pulse;
			MemRectFrameThick(x + (float)(80) * zoom - (hlW - (float)BUYBUTTON_X * zoom) / 2, y - (float)(694) * zoom - (hlH - (float)BUYBUTTON_Y * zoom) / 2, hlW, hlH, COLOR_YELLOW, (int)(3 * _2X));
		}

		//최외각 테두리
		MemRectFrameThick(x, y, WINX, WINY, 0x2C2578, (float)OUTTHICK* zoom);
		//그안에 테두리
		MemRectFrameThick(x + OUTTHICK, y - OUTTHICK, WINX - 2 * OUTTHICK, WINY - 2 * OUTTHICK, 0x7653D3, INTTHICK);

		break;
	}
	BarDraw(&bar[BAR_GOLD], bar[BAR_GOLD].zoom);

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
	//패널 그리기
	DrawImageScale(buttonImgData[color * 5 + 0], buttonImgData[color * 5 + 1], buttonImgData[color * 5 + 2], buttonImgData[color * 5 + 3], x, y, false, false, false, false, false, zoomX, zoomY, sprite[buttonImgData[color * 5 + 4]], buttonImgData[color * 5 + 4]);

	//아이콘 그리기(일단 생략)

	//텍스트 그리기
	if (text > 0) {
		SetFontColor(COLOR_WHITE);
		CenterText(text, x + (float)buttonImgData[color * 5 + 0] / 2 * zoomX, y - (float)3 * _2X * zoom, 1.2f * zoom);
	}
}

void DrawEquipItemCard(int itemType, int itemDetail, int itemGrade, int itemLv, int itemCnt, int x, int y, float zoom)
{
	int star = GetItemStar(itemType, itemDetail, itemGrade);
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
	// 카드 뒷면 공개 애니메이션
	//
	// backFrame
	// 0   : 기존 카드 앞면
	// 1~7 : CARD_IMG의 0~6번 뒷면 이미지
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
		//카드 한가운데에 오도록 왼쪽 4픽셀, 아래 8픽셀 밀어준다(y는 위로 갈수록 커진다).
		DrawPlusMark(
			x + (float)88 * zoom - 4,
			y - (float)72 * zoom - 8,
			1.45f * zoom);
	}
	else {
		//현재 플레이메뉴면 까맣게, 아니면 획득창이니까 보여준다.
		if (itemLv == 0 && drawHandle == MD_PLAY)
			SetColor(COLOR_BLACK);
			//grayScale = 32;

		if (itemType == ITEM_CREW) {
			int crewCmf = enemyData[crewData[itemDetail * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_CMF];
			int crewType = crewData[itemDetail * CREWDATASIZE + CREWDATA_TYPE];
			DrawCmfDetailShadow(crewCmf, crewPos[crewType * 5 + 0] + (ani == true ? (frame / 4 / MOTIONDIV) % crewPos[crewType * 5 + 1] : 0),
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
			//SetAlpha(32);
			//memset(&tempStr, 0, sizeof(tempStr));
			//sprintf(tempStr, "LV %d", itemLv);

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
		// 하트 수량
		//------------------------------------------------
				DrawGoldNum(
					itemCnt,  // 아래 설명 참고

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
	
	int repItem = 0;
	int setItemCnt = 0;
	int itemType, itemDetail, itemGrade, itemLv, itemCnt, itemSlot;
	OBJECT* pObj = &ao[curHero];
	float numWidth = (float)(32 * _2X) * zoom;
	int collectionIdx;
	int menuText[] = { TEXT_EQUIPMENT, TEXT_SKILL };

	MemRect(x, y, WINX, WINY, 0x3B2513);

	for (i = 0; i < 2; i++)
		DrawImage(equipMenuUiData[i * MENUUIDATACNT + 0], equipMenuUiData[i * MENUUIDATACNT + 1], equipMenuUiData[i * MENUUIDATACNT + 2], equipMenuUiData[i * MENUUIDATACNT + 3], x + (float)equipMenuUiData[i * MENUUIDATACNT + 4] * zoom, y - (float)(equipMenuUiData[i * MENUUIDATACNT + 5]) * zoom, false, false, false, false, false, zoom, sprite[equipMenuUiData[i * MENUUIDATACNT + 6]], equipMenuUiData[i * MENUUIDATACNT + 6]);

	CenterText(TEXT_EQUIPMENT, x + (float)160 * _2X * zoom, y - (float)48 * zoom, 2.0f * zoom);
	CenterText(TEXT_EQUIP_LISTEDIT, x + (float)160 * _2X * zoom, y - (float)100 * zoom, 1.1f * zoom);

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

		//튜토리얼 1단: 장비를 넣을 자리(갑옷)를 먼저 고르게 한다.
		//4단: 장착된 뒤 그 자리를 다시 밝혀서 어디에 들어갔는지 보여준다(손은 띄우지 않는다).
		bool equipSlotGuide = (GetTutorialEquipSlotTouchFunc() == TOUCH_FUNC_MENUX_1 + i);
		bool equipSlotShow = (tutorialEquipStep == TUTORIAL_EQUIPSTEP_SLOTSHOW && i == TUTORIAL_EQUIP_SLOT);

		if (equipSlotGuide || equipSlotShow) {
			//DrawItemCard()가 카드 터치영역으로 쓰는 사각형과 같은 기준으로 잡는다.
			float cardZoom = CARDDEFAULTZOOM * 0.8f * zoom;
			float rw = (float)240 * cardZoom;
			float rh = (float)332 * cardZoom;
			float pulse = 1.0f + sinf((float)frame * 0.1f) * 0.06f;

			if (equipSlotGuide) {
				//손 크기는 동료 안내와 같게 맞춘다.
				float handZoom = 2.0f;
				float handW = (float)imgArray[IMG_HAND1 * 4 + 2] * handZoom;
				float handH = (float)imgArray[IMG_HAND1 * 4 + 3] * handZoom;

				DrawHand(slotX + rw / 2 - handW, slotY - rh / 2 + handH, robin.playtime / MOTIONDIV, handZoom);
			}

			//슬롯은 가로로 붙어 있어 옆 슬롯까지 밝아지지 않도록 폭 기준으로 반경을 잡는다.
			SetSpotlight(slotX + rw / 2, slotY - rh / 2,
				rw * 0.55f * pulse, rw * 1.00f * pulse, 0.25f);
		}
	}

	DrawImageScale(128, 128, 587, 608, x + (float)476 * zoom, y - (float)142 * zoom, false, false, false, false, false, 1.0f * zoom, 1.0f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
	DrawPlayer(&ao[ROBIN], 0, x + (float)(476 + 128 / 2) * zoom, y - (float)242 * zoom, LEFT, 1.5f * zoom, false, false, true);

	DrawImageScale(128, 128, 587, 608, x + (float)476 * zoom, y - (float)280 * zoom, false, false, false, false, false, 1.0f * zoom, 1.7f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);

	//공격력
	itemType = ITEM_SWORD;
	itemDetail = ao[ROBIN].equip[EQUIP_WEAPON].detail;
	itemGrade = ao[ROBIN].equip[EQUIP_WEAPON].grade;
	DrawImageScale(64, 64, 455, 709, x + (float)(476 + 8) * zoom, y - (float)(220 + 16 + 70) * zoom, false, false, false, false, false, 0.6f * zoom, 0.6f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
	
	SetFontColor(COLOR_GREY);
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s@+%d", textId[TEXT_ATK], ao[ROBIN].ps[PS_DMG]);
	LineTextStrSolid(tempStr, x + (float)(476 + 8 + 46) * zoom, y - (float)(220 + 10 + 70) * zoom, (float)108 * zoom, -1, -1, zoom);
	SetFontColor(COLOR_WHITE);
	//방어력
	itemType = ITEM_ARMOR;
	itemDetail = ao[ROBIN].equip[EQUIP_ARMOR].detail;
	itemGrade = ao[ROBIN].equip[EQUIP_ARMOR].grade;
	DrawImageScale(64, 64, 520, 709, x + (float)(476 + 8) * zoom, y - (float)(220 + 16 + 70 * 2) * zoom, false, false, false, false, false, 0.6f * zoom, 0.6f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);

	SetFontColor(COLOR_GREY);
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s@+%d", textId[TEXT_DEF], ao[ROBIN].ps[PS_ARMOR]);
	LineTextStrSolid(tempStr, x + (float)(476 + 8 + 46) * zoom, y - (float)(220 + 10 + 70 * 2) * zoom, (float)108 * zoom, -1, -1, zoom);
	SetFontColor(COLOR_WHITE);
	//체력
	DrawImageScale(64, 64, 390, 709, x + (float)(476 + 8) * zoom, y - (float)(220 + 16 + 70 * 3) * zoom, false, false, false, false, false, 0.6f * zoom, 0.6f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
	
	SetFontColor(COLOR_GREY);
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%s@+%d", textId[TEXT_HERO_PARAM_HP], ao[ROBIN].ps[PS_HP]);
	LineTextStrSolid(tempStr, x + (float)(476 + 8 + 46) * zoom, y - (float)(220 + 10 + 70 * 3) * zoom, (float)108 * zoom, -1, -1, zoom);
	SetFontColor(COLOR_WHITE);

	// 2. 아이템 카테고리 리스트
	
	for (i = 0; i < EQUIP_NECK; i++) {
		itemType = ITEM_SWORD + i * 3;
		itemDetail = ao[ROBIN].equip[i].detail;
		itemGrade = ao[ROBIN].equip[i].grade;

		DrawButton(x + (float)(34 + i * 96) * zoom, y - (float)(508) * zoom, menuX == i ? BUTTON_COLOR_PURPLE : BUTTON_COLOR_BROWN, 64, GetItemIcon(itemType, itemGrade, itemDetail), TEXT_CATEGORY_ITEM_SWORD + itemType, false, 0.5f * zoom, 1.0f * zoom);
		if (menuX != i)
			SetRectPoint(x + (float)(34 + i * 96) * zoom, y - (float)(508) * zoom, (float)80 * zoom, (float)48 * zoom, TOUCH_FUNC_MENUX_1 + i);
	}

	// 3. 장비 리스트
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

		//튜토리얼 2단: 새로 얻은 장비 카드만 밝게 남기고 나머지를 어둡게 덮는다.
		//사각형은 DrawItemCard()가 카드 터치영역으로 등록하는 것과 같은 값이다.
		if (GetTutorialEquipCardTouchFunc() == TOUCH_FUNC_ITEMDETAIL + itemInvenIdxList[i]) {
			int cardStar = GetItemStar(itemType, itemDetail, itemGrade);
			float cardZoom = CARDDEFAULTZOOM * 0.9f * zoom;
			float rx = cardX + (float)equipBgData[(cardStar - 1) * 6 + 4] * cardZoom;
			float ry = cardY - (float)equipBgData[(cardStar - 1) * 6 + 5] * cardZoom;
			float rw = (float)equipBgData[(cardStar - 1) * 6 + 0] * cardZoom;
			float rh = (float)equipBgData[(cardStar - 1) * 6 + 1] * cardZoom;
			float pulse = 1.0f + sinf((float)frame * 0.1f) * 0.06f;

			//DrawHand()에 넘기는 좌표가 손 그림의 좌상단이라 자기 크기만큼 물려야 손끝이 중앙에 온다.
			float handZoom = 2.4f;
			float handW = (float)imgArray[IMG_HAND1 * 4 + 2] * handZoom;
			float handH = (float)imgArray[IMG_HAND1 * 4 + 3] * handZoom;

			DrawHand(rx + rw / 2 - handW, ry - rh / 2 + handH, robin.playtime / MOTIONDIV, handZoom);

			//카드 사이 여백이 거의 없어서 높이 기준으로 잡으면 옆 카드까지 밝아진다. 폭 기준으로 좁힌다.
			SetSpotlight(rx + rw / 2, ry - rh / 2,
				rw * 0.34f * pulse, rw * 0.60f * pulse, 0.25f);
		}
	}

	int scrollH = WINY - (float)580 * zoom;

	DrawScroll(
		x + (float)612 * zoom,
		y - (float)560 * zoom,
		scrollH,
		MENU_COLLECTIONS);

	UnSectionClip(false);

	//최외각 테두리
	MemRectFrameThick(x, y, WINX, WINY, 0x271910, (float)OUTTHICK * zoom);
	//그안에 테두리
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
			

			//최외각 테두리
			MemRectFrameThick(x, y, WINX, WINY, 0x271910, (float)OUTTHICK * zoom);
			//그안에 테두리
			MemRectFrameThick(x + OUTTHICK, y - OUTTHICK, WINX - 2 * OUTTHICK, WINY - 2 * OUTTHICK, 0x5F4022, INTTHICK);

			break;
	}
	return;
	
	//Top menu
	//if (menuCur < EQUIP_NECK)


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

		EquipInfoDraw(&ao[menuCur].equip[EQUIP_WEAPON], x, y, itemType, itemDetail, itemGrade, /*menuDepth - 2*/0, menuX, 1.0f);

		break;
	}
	return;

	SetSectionClip(0, y - (float)32 * _2X * zoom, (float)POPUPWINDOWSIZE_X * zoom, (float)(POPUPWINDOWSIZE_Y - 16 * _2X) * zoom, false);

	for (i = 0; i < TOTALCHAR; i++) {
		EnemyProfileDraw(x + (float)(28 * _2X + 92 * _2X * i) * zoom, y - (float)(48 * _2X) * zoom, i, false, false, zoom);
		SetRectPoint(x + (float)(28 * _2X + 92 * _2X * i) * zoom, y - (float)(48 * _2X) * zoom, (float)80 * _2X * zoom, (float)32 * _2X * zoom, TOUCH_FUNC_TABMENUX_1 + i);
		CenterText(TEXT_MONSTERNAME_START + i, x + (float)(28 * _2X + 92 * _2X * i + 52 * _2X) * zoom, y - (float)(48 * _2X + 12 * _2X) * zoom, zoom);

		//SetRectPoint(x + (float)(28 * _2X + 92 * _2X * i) * zoom, y - (float)(48 * _2X) * zoom, (float)80 * _2X * zoom, (float)32 * _2X * zoom, TOUCH_FUNC_TABMENUX_1 + i);

	}

	switch (menuCur) {
		//히어로
	case COLLECTIONMENU_EQUIP:

		HeroStatDraw(&ao[curHero], x + (float)0 * _2X * zoom, y + scY[MENU_COLLECTIONS] - (float)52 * _2X * zoom, zoom);

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


			//몇분의 몇을 모았는지를 보여주는 
			if (setItemCnt > 0) {
				DrawNum(setItemCnt, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 22 * _2X - 14 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X - 32 * _2X + 18 * _2X, NUM_FONT_NORMAL, LEFT, false, false, false, 1.0f, true);
				DrawText(TEXT_SLASH, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 22 * _2X - 2 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X - 32 * _2X - 2 * _2X + 18 * _2X, 1.0f);
				DrawNum(COLLECTIONSITEMCNT, x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 22 * _2X + 6 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X - 32 * _2X + 18 * _2X, NUM_FONT_NORMAL, LEFT, false, false, false, 1.0f, true);
			}
			//6개가 다 장착되어 있어서 스킬이 활성화 되어 있으면
			if (GetFullEquipedCollectionIdx() == i)
				DrawNeutral(OBJ_STAMPEFFECT0 + (frame / 3 % 8), x + 2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 12 * _2X + 4 * _2X + 16 * _2X, y - (i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 4 * _2X + 32 * _2X) - TSIZE * 2 - 24 * _2X, 0, 1.0f);
			//만약 6개가 다 모여만 있으면
			else if (setItemCnt == COLLECTIONSITEMCNT) {
				//아무것도 하지 않는다.
			}
			else if (setItemCnt > 0) {
				//아무것도 하지 않는다.
			}
			//아무것도 없으면
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

		//모두 장착
		//아직 장착되지 않고 
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
	int itemType, itemDetail, itemGrade, itemLv, itemCnt, itemIdx;
	float iconZoom = EQUIPZOOM;
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
			//레벨표시
			sprintf(tempStr, TEXTPTR(TEXT_ALPHA_LV), itemLv + 1);
		}
		CenterTextStr(tempStr, x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X + 32 * _2X + 2 * _2X) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - COLLECTIONCARDSIZE_Y - TSIZE * 1 - 8 * _2X) * zoom, iconZoom / 2 * zoom);

		DrawLabel(x + (float)(2 * _2X + (i % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + 8 * _2X) * zoom, y + (float)(-(i / COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_Y + 40 * _2X) - 88 * _2X - TSIZE * 3 - 4 * _2X) * zoom, itemIdx == -1 ? TEXT_QUESTION : TEXT_ITEMNAME_START + GetItemName(itemType, itemDetail, itemGrade), zoom);
	}

	//컬렉션 기능 그리기
	//세트스킬은 별도로 표시해두지 않는다.


}


void ShopDraw(int x, int y, float zoom)
{
	int i;
	float OUTTHICK = (float)5 * zoom;
	float INTTHICK = (float)5 * zoom;
	float WINX = (float)DX * zoom;
	float WINY = (float)(DY - (GNBHEIGHT)-(BOTTOMMENUHEIGHT - BOTTOMMENU_INIT_HEIGHT)) * zoom;


	MemRect(x, y, WINX, WINY, 0x3B2513);

	for (i = 0; i < 2; i++)
		DrawImage(shopMenuUiData[i * MENUUIDATACNT + 0], shopMenuUiData[i * MENUUIDATACNT + 1], shopMenuUiData[i * MENUUIDATACNT + 2], shopMenuUiData[i * MENUUIDATACNT + 3], x + (float)shopMenuUiData[i * MENUUIDATACNT + 4] * zoom, y - (float)(shopMenuUiData[i * MENUUIDATACNT + 5]) * zoom, false, false, false, false, false, zoom, sprite[shopMenuUiData[i * MENUUIDATACNT + 6]], shopMenuUiData[i * MENUUIDATACNT + 6]);

	CenterText(TEXT_MENU_SHOP, x + (float)160 * _2X * zoom, y - (float)48 * zoom, 2.0f * zoom);
	CenterText(TEXT_SHOP_BUY, x + (float)160 * _2X * zoom, y - (float)100 * zoom, 1.1f * zoom);

	//최외각 테두리
	MemRectFrameThick(x, y, WINX, WINY, 0x271910, (float)OUTTHICK * zoom);
	//그안에 테두리
	MemRectFrameThick(x + OUTTHICK, y - OUTTHICK, WINX - 2 * OUTTHICK, WINY - 2 * OUTTHICK, 0x5F4022, INTTHICK);

	return;

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y - (float)(POPUPSTORE_Y + 16 * _2X) * zoom, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

	switch (menuDepth) {
	case 0:
		switch (menuIdx) {
		default:
			//상단의 팝업스토어
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
			//하트상품 6개
			//y -= GNBHEIGHT;

			DrawLabel(x + (float)(POPUPWINDOWSIZE_X / 2 - 40 * _2X) * zoom, y + (float)16 * _2X * zoom, TEXT_SHOP_HEART_TITLE, zoom);

			for (i = 0; i < 6; i++) {

				//if (zoom == 1)
				//	SetRectPoint(x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3)) * zoom, y + (float)(-40 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3)) * zoom, (float)SHOPMENUCARD_WIDTH * zoom, (float)SHOPMENUCARD_HEIGHT * zoom, TOUCH_FUNC_EQUIP_INVENTORY + i);

				DrawImage(72 * _2X, 64 * _2X, 0 * _2X, 0 * _2X, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + (SHOPMENUCARD_WIDTH - 72 * _2X) / 2) * zoom, y + (float)(-16 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - (SHOPMENUCARD_HEIGHT - 88 * _2X) / 2) * zoom, false, false, false, false, false, zoom, sprite[HEART_0_IMG + i], HEART_0_IMG + i);

				//하트수량
				DrawNum(currencyShop[0 * 7 + i * 7 + 4], x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + SHOPMENUCARD_WIDTH / 2) * zoom, y + (float)(-16 * _2X - (SHOPMENUCARD_HEIGHT) * (i / 3)) * zoom, NUM_FONT_NORMAL, CENTER, 0, false, true, zoom, true);

				if (currencyShop[0 * 7 + i * 7 + 2]) {
					memset(tempStr, 0, sizeof(tempStr));
					sprintf(tempStr, "+%d%%", currencyShop[0 * 7 + i * 7 + 2]);
					//보너스 숫자
					CenterTextStr(tempStr, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + SHOPMENUCARD_WIDTH / 2) * zoom, y + (float)(-16 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 36 * _2X) * zoom, zoom);
				}
				//아이콘

				//DrawNeutral(OBJ_ITEM0 + (frame + i) % 4, x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + (SHOPMENUCARD_WIDTH - 16 * _2X * 2) / 2 + ITEMICONSIZE) * zoom, y + (float)(- 16 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 52 * _2X) * zoom, LEFT, (float)2 * zoom, gScreenBuffer, gScreenLayer, false);

				DrawBuyButton(x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + 6 * _2X) * zoom, y + (float)(-16 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - SHOPMENUCARD_HEIGHT + 34 * _2X) * zoom, (float)(SHOPMENUCARD_WIDTH - 12 * _2X) * zoom, (float)(RAIDGOLDBARHEIGHT)*zoom, frame, 0, currencyShop[0 * 7 + i * 7 + 6], currencyShop[0 * 7 + i * 7 + 5], zoom, false, false, false);
			}

			y -= (float)(208 * _2X) * zoom;

			//장비뽑기 3종
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

				//코인수량
				DrawNum(currencyShop[9 * 7 + i * 7 + 4], x + (float)(2 * _2X + (SHOPMENUCARD_WIDTH + 2 * _2X) * (i % 3) + SHOPMENUCARD_WIDTH / 2) * zoom, y + (float)(-24 * _2X - (SHOPMENUCARD_HEIGHT + 8 * _2X) * (i / 3) - 8 * _2X) * zoom, NUM_FONT_NORMAL, CENTER, 0, false, true, zoom, true);

				if (currencyShop[9 * 7 + i * 7 + 2]) {
					memset(tempStr, 0, sizeof(tempStr));
					sprintf(tempStr, "+%d%%", currencyShop[9 * 7 + i * 7 + 2]);
					//보너스 숫자
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
	int i;
	float OUTTHICK = (float)5 * zoom;
	float INTTHICK = (float)5 * zoom;
	float WINX = (float)DX * zoom;
	float WINY = (float)(DY - (GNBHEIGHT)-(BOTTOMMENUHEIGHT - BOTTOMMENU_INIT_HEIGHT)) * zoom;


	MemRect(x, y, WINX, WINY, 0xB4D4F2);

	for (i = 0; i < 2; i++)
		DrawImage(castleMenuUiData[i * MENUUIDATACNT + 0], castleMenuUiData[i * MENUUIDATACNT + 1], castleMenuUiData[i * MENUUIDATACNT + 2], castleMenuUiData[i * MENUUIDATACNT + 3], x + (float)castleMenuUiData[i * MENUUIDATACNT + 4] * zoom, y - (float)(castleMenuUiData[i * MENUUIDATACNT + 5]) * zoom, false, false, false, false, false, zoom, sprite[castleMenuUiData[i * MENUUIDATACNT + 6]], castleMenuUiData[i * MENUUIDATACNT + 6]);

	CenterText(TEXT_CASTLE, x + (float)160 * _2X * zoom, y - (float)48 * zoom, 2.0f * zoom);
	CenterText(TEXT_CASTLE_LISTSELECT, x + (float)160 * _2X * zoom, y - (float)100 * zoom, 1.1f * zoom);
	//현재 성
	DrawImageScale(128, 128, 716, 874, x + (float)8 * zoom, y - (float)(132) * zoom, false, false, false, false, false, 4.9f * zoom, 2.0f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
	DrawImage(DIORAMASIZE_X, DIORAMASIZE_Y, 0, 0, x + (float)16 * zoom, y - (float)124 * zoom, false, false, false, false, false, 0.25f * zoom, sprite[MAP_DIORAMA_IMG + castleOrder[robin.castle]], MAP_DIORAMA_IMG + castleOrder[robin.castle]);
	DrawImageScale(176, 40, 1, 679, x + (float)280 * zoom, y - (float)(132 + 12) * zoom, false, false, false, false, false, 1.2f * zoom, 1.2f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
	CenterText(TEXT_CASTLE_TOLEM + castleOrder[robin.castle], x + (float)280 * zoom + (float)106 * zoom, y - (float)(132 + 20) * zoom, 1.2f * zoom);


	//리스트의 성
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

		//최대 동료 별

		//상자
		DrawImageScale(128, 128, 587, 737, slotX + (float)350 * zoom, slotY - (float)8 * zoom, false, false, false, false, false, 0.8f * zoom, 0.8f * zoom, sprite[UI_NEW_IMG], UI_NEW_IMG);
		DrawBox(BOX_CASTLE0 + castleOrder[i], slotX + (float)400 * zoom, slotY - (float)108 * zoom, LEFT, 0, false, false, false, false, BOXCASTLEZOOM * 0.9f);

		GoldBarDraw(castleBoxGold[castleOrder[i]], ICON_GOLD, slotX + (float)332 * zoom, slotY - (float)108 * zoom, false, 0.6f * zoom);
		//획득시 캐릭터
		DrawItemCard(ITEM_CREW, i * 2, GRADE_NORMAL, 1, 1, false, slotX + (float)480 * zoom, slotY + (float)8 * zoom, TEXT_ALPHA_REWARD, CARDDEFAULTZOOM * 0.8f * zoom, false, false, false, false, 0);
	}

	int scrollH = WINY - (float)(420 + 184 * 0) * zoom;

	DrawScroll(
		x + (float)616 * zoom,
		y - (float)(400 + 184 * 0) * zoom,
		scrollH,
		MENU_CASTLE);

	UnSectionClip(false);

	//최외각 테두리
	MemRectFrameThick(x, y, WINX, WINY, 0x052F6C, (float)OUTTHICK * zoom);
	//그안에 테두리
	MemRectFrameThick(x + OUTTHICK, y - OUTTHICK, WINX - 2 * OUTTHICK, WINY - 2 * OUTTHICK, 0x0C459B, INTTHICK);

	return;
}
