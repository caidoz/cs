#include "Core.h"
#include "Data.h"
#include "Func.h"
#include "Text.h"

void DrawBarIcon(int type, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	switch (type) {
	case BAR_HERO:
		DrawFrame(x, y, (float)(MAINMENU_X)*zoom, (float)(MAINMENU_Y)*zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
		DrawIcon(ICON_EVENT_CROWN, x + (float)(MAINMENU_X / 2) * zoom - (float)(ITEMICONSIZE)*zoom, y - (float)(MAINMENU_Y / 2) * zoom + (float)(ITEMICONSIZE)*zoom, 2.0f * zoom, COLOR_BROWN, false, false, 1, cvtDest, cvtLayer, buffering);
		CenterText(TEXT_HERO, x + (float)(MAINMENU_X / 2) * zoom, y + (float)(10 * _2X) * zoom, 0.8f * zoom, cvtDest, cvtLayer, buffering);
		break;
	case BAR_CREW:
		DrawFrame(x, y, (float)(MAINMENU_X)*zoom, (float)(MAINMENU_Y)*zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
		DrawIcon(ICON_EVENT_GOLDSHEILD, x + (float)(MAINMENU_X / 2) * zoom - (float)(ITEMICONSIZE)*zoom, y - (float)(MAINMENU_Y / 2) * zoom + (float)(ITEMICONSIZE)*zoom, 2.0f * zoom, COLOR_BROWN, false, false, 1, cvtDest, cvtLayer, buffering);
		CenterText(TEXT_BORDERGUARD, x + (float)(MAINMENU_X / 2) * zoom, y + (float)(10 * _2X) * zoom, 0.8f * zoom, cvtDest, cvtLayer, buffering);
		break;
	case BAR_COLLECTIONS:
		DrawFrame(x, y, (float)(MAINMENU_X)*zoom, (float)(MAINMENU_Y)*zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
		DrawImage(108, 108, 266, 150, x + (float)(MAINMENU_X / 2) * zoom - (float)(108 / 2) * 0.8f * zoom, y - (float)(MAINMENU_Y / 2) * zoom + (float)(108 / 2) * 0.8f * zoom, false, false, false, false, 32, 0.8f * zoom, sprite[BOX_IMG], cvtDest, cvtLayer, BOX_IMG, buffering);
		CenterText(TEXT_MENU_COLLECTIONS, x + (float)(MAINMENU_X / 2) * zoom, y + (float)(10 * _2X) * zoom, 0.8f * zoom, cvtDest, cvtLayer, buffering);
		break;
	case BAR_MAINSHOP:
		DrawFrame(x, y, (float)(MAINMENU_X)*zoom, (float)(MAINMENU_Y)*zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
		DrawIcon(ICON_EVENT_BOX, x + (float)(MAINMENU_X / 2) * zoom - (float)(ITEMICONSIZE)*zoom, y - (float)(MAINMENU_Y / 2) * zoom + (float)(ITEMICONSIZE)*zoom, 2.0f * zoom, COLOR_BROWN, false, false, 1, cvtDest, cvtLayer, buffering);
		CenterText(TEXT_MENU_SHOP, x + (float)(MAINMENU_X / 2) * zoom, y + (float)(10 * _2X) * zoom, 0.8f * zoom, cvtDest, cvtLayer, buffering);
		break;
	}
}

void BarDraw(BAR* barP, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	long long count = barP->count;
	int max;//퀘스트에서 맥스값 숫자 적어줄 때 쓰는 변수
	long long val;
	int textPos = 0;
	float textZoom = 1.2f * zoom;
	long long rewardCnt;
	const long long* reward;
	float coinZoom = 1.0f;
	long long remainTime;
	long long totalTime;
	float INFOZOOM = 0.7f;
	int buttonZoom = 3.0f;

	if (barP->add > 0) {
		count += Min(barP->add * barP->aniFrame * 3 / barP->countFrame, barP->add);
		if (count <= barP->count + barP->aniFrame)
			count = barP->count + barP->aniFrame;
		if (count > barP->count + barP->add)
			count = barP->count + barP->add;
	}
	else if (barP->add < 0) {
		count += Max(barP->add * barP->aniFrame * 3 / barP->countFrame, barP->add);
	}


	switch (barP->drawFunc) {
		//0인 경우에는 아무것도 그려주지 않는다.
	case 0:
		break;
	case BAR_GOLD:
		if (count < 0)
			count = 0;

		GoldBarDraw(count, barP->icon + (barP->iconFrame > 0 ? barP->aniFrame % barP->iconFrame : 0), xOffset + barP->x, barP->y, false, zoom, cvtDest, cvtLayer, buffering);

		if (barP->addView)
			DrawNum2AutoSpaceing(barP->add, xOffset + barP->x + (float)(GOLDBARWIDTH - 4 * _2X) * zoom, barP->y - (float)GOLDBARHEIGHT * zoom - (float)(1 * _2X) * zoom, RIGHT, false, barP->add >= 0 ? PLUS : MINUS, GOLDBARWIDTH, true, 0.3f * zoom, false, true, cvtDest, cvtLayer, buffering);
		break;
	case BAR_CROWN:
		ExpBarDraw(robin.lv, count, xOffset + barP->x, barP->y, false, zoom, cvtDest, cvtLayer, buffering);
		SetRectPoint(xOffset + barP->x, barP->y, (float)CROWNBARWIDTH * zoom, (float)CROWNBARHEIGHT * zoom, TOUCH_FUNC_POPUP_LVUPREWARD);

		break;
	case BAR_HAMMER:
	case BAR_SHIELD:

		DrawIcon(barP->icon + (barP->iconFrame > 0 ? barP->aniFrame % barP->iconFrame : 0), xOffset + barP->x + (HAMMERBARWIDTH - ITEMICONSIZE * 1.5f) / 2 * zoom, barP->y - 2 * _2X, 1.5f * zoom, COLOR_WHITE, false, false, 2, cvtDest, cvtLayer, buffering);
		if (barP->drawFunc == BAR_SHIELD) {
			DrawSlashNum(barP->count, GetMaxShield(), xOffset + barP->x + (float)(HAMMERBARWIDTH / 2 + 2 * _2X) * zoom, barP->y - (float)(7 * _2X + ITEMICONSIZE * 1.5f) * zoom, (float)ITEMICONSIZE * 3, zoom * 0.8f, cvtDest, cvtLayer, buffering);
		}
		else {
			DrawBigNumTTF(count, xOffset + barP->x + (float)(ITEMICONSIZE * 1.5f / 2) * zoom + (HAMMERBARWIDTH - ITEMICONSIZE * 1.5f) / 2 * zoom, barP->y - (float)(2 * _2X + ITEMICONSIZE * 1.5f) * zoom, NUM_FONT_NORMAL, CENTER, false, false, (float)HAMMERBARWIDTH * zoom, false, 0.7f * zoom, true, cvtDest, cvtLayer, buffering);
		}
		break;
	case BAR_BOX:

		if (robin.heart >= betHeart[bet]) {
			if (autoPlay == false)
				barP->iconFrame = boxNeutralAnimation[((frame / (MOTIONDIV * 2 * 2)) % 4)];
			else
				barP->iconFrame = ((frame / (MOTIONDIV * 2 * 2)) % 7);
		}
		else
			barP->iconFrame = 0;

		if (ao[ITEMBOX].status == BOXSTATUS_CLOSED) {
			PushButtonDraw(bet, xOffset + barP->x, barP->y, barP->iconFrame, zoom + (GetRectPoint(touchX, touchY, xOffset + barP->x - (float)BOXSIZE_X * zoom / 2, barP->y + (float)BOXSIZE_Y * 2 / 3 * zoom, (float)BOXSIZE_X * zoom, (float)BOXSIZE_Y * 2 / 3 * zoom) == true && touchedFrame > 1 ? Min(0.1f, (float)touchedFrame * 0.01f) : 0), true, cvtDest, cvtLayer, buffering);

			//그리는건 Bar Heart에서 책임진다.
			if (JoyStickPressPossible() && autoPlay == false) {
				if (frame % (FPS * 10) < 3 * FPS)
					DrawHand(xOffset + barP->x - (float)BOXSIZE_X * zoom / 2, barP->y + (float)(BOXSIZE_Y * 3 / 3 - 24 * _2X) * zoom, robin.playtime / MOTIONDIV, 2.0f * zoom, cvtDest, cvtLayer, buffering);
				SetRectPoint(xOffset + barP->x - (float)BOXSIZE_X * zoom / 2, barP->y + (float)BOXSIZE_Y * 2 / 3 * zoom, (float)BOXSIZE_X * zoom, (float)BOXSIZE_Y * zoom, TOUCH_FUNC_USE_HEART);
			}
			else if (autoPlay == true)
				SetRectPoint(xOffset + barP->x - (float)BOXSIZE_X * zoom / 2, barP->y + (float)BOXSIZE_Y * 2 / 3 * zoom, (float)BOXSIZE_X * zoom, (float)BOXSIZE_Y * zoom, TOUCH_FUNC_INGAME_AUTOOFF);
		}

		//조이스틱을 일정시간 누르고 있으면
		if (curtainFrame == 0 && infoFrame == 0 && areaFrame == 0 && autoPlay == false && arenaStatus == STATUS_PLAY && touchedFrame >= AUTOPLAYFRAME && GetRectPoint(touchX, touchY, xOffset + barP->x - (float)BOXSIZE_X * zoom / 2, barP->y + (float)BOXSIZE_Y * 2 / 3 * zoom, (float)BOXSIZE_X * zoom, (float)BOXSIZE_Y * 2 / 3 * zoom)) {
			autoPlay = true;
			autoButtonText = false;
		}

		break;
	default:

		if (barP->drawFunc >= BAR_PLAYERHP && barP->drawFunc < BAR_PLAYERHP + MAXPLAYER) {
			if (barP->owner == curPlayer) {

			}
		}
		else {
			if (barP->owner == curEnemy) {

			}
		}
		break;

	case BAR_BOSSHP:
		BossHpBarDraw(count, barP->max, xOffset + barP->x, barP->y, zoom, cvtDest, cvtLayer, buffering);
		break;
	case BAR_COIN:
		if (count != 0) {
			DrawRouletteNumIcon(count, barP->icon, xOffset + barP->x, barP->y, true, CENTER, zoom, cvtDest, cvtLayer, buffering);
		}
		break;
	case BAR_ITEM:
		DrawRouletteNumIcon(count, barP->icon, xOffset + barP->x, barP->y, true, CENTER, zoom, cvtDest, cvtLayer, buffering);
		break;
	case BAR_HEART:
		HeartBarDraw(count, GetInitHeart(), xOffset + barP->x, barP->y, false, zoom, cvtDest, cvtLayer, buffering);

		switch (drawHandle) {
		case MD_PLAY:
			DrawBattleButton(xOffset + barP->x + (float)(HEARTBARWIDTH / 2) * zoom - (float)(ITEMICONSIZE / 2) * buttonZoom * zoom * battleZoom, barP->y + (float)(ITEMICONSIZE + 4 * _2X) * buttonZoom * zoom * battleZoom, buttonZoom * zoom * battleZoom, (touchDisable == false ? true : false), cvtDest, cvtLayer, buffering);
			if (touchDisable == false)
				SetRectPoint(xOffset + barP->x + (float)(HEARTBARWIDTH / 2) * zoom - (float)(ITEMICONSIZE / 2) * buttonZoom * zoom * battleZoom, barP->y + (float)(ITEMICONSIZE + 4 * _2X) * buttonZoom * zoom, (float)ITEMICONSIZE * buttonZoom * zoom, (float)ITEMICONSIZE * buttonZoom * zoom, TOUCH_FUNC_GOTOBATTLE);

			break;
		case MD_BATTLE:
			DrawHeartButton(betHeart[bet], xOffset + barP->x - (float)(ITEMICONSIZE * 2 + 8 * _2X) * 1.4f * zoom, barP->y - (float)2 * _2X * zoom, 1.4f * zoom, (touchDisable == false ? true : false), true, cvtDest, cvtLayer, buffering);
			if (touchDisable == false)
				SetRectPoint(xOffset + barP->x - (float)(ITEMICONSIZE * 2 + 8 * _2X) * 1.4f * zoom, barP->y - (float)(0 * _2X) * zoom, (float)HEARTBUTTONWIDTH * 1.4f * zoom, (float)HEARTBUTTONHEIGHT * 1.5f * zoom, TOUCH_FUNC_HEARTAMOUNT);

			//누르고 있는 동안은 내려가야 되고
			//떼는 순간 바닥으로 붙고
			//전투가 끝나면 천천히 올라와야 된다.

			DrawAttackButton(count, xOffset + barP->x + (float)(HEARTBARWIDTH + 4 * _2X) * zoom, barP->y - (float)4 * _2X * zoom, 1.5f * zoom, (touchDisable == false ? true : false), false, rectContainsTouchPoint(barP->x + (float)(HEARTBARWIDTH + 8 * _2X) * zoom, barP->y + (float)6 * _2X * zoom, (float)ATTACKBUTTONWIDTH * 2.0f * zoom, (float)ATTACKBUTTONHEIGHT * 2.0f * zoom) * touchFrame, cvtDest, cvtLayer, buffering);
			if (touchDisable == false)
				SetRectPoint(xOffset + barP->x + (float)(HEARTBARWIDTH + 4 * _2X) * zoom, barP->y - (float)0 * _2X * zoom, (float)ATTACKBUTTONWIDTH * 1.5f * zoom, (float)ATTACKBUTTONHEIGHT * 1.8f * zoom, TOUCH_FUNC_ATTACK);
			break;
		}

		if (count >= GetInitHeart()) {

			CenterText(TEXT_HEARTISFULL, xOffset + barP->x + (float)(HEARTBARWIDTH / 2) * zoom, barP->y - (float)(HEARTBARHEIGHT + 2 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

		}
		//만약 모자라면 얼마 뒤에 스핀을 획득하는지 보여준다.
		else {
			DrawIcon(barP->icon, xOffset + barP->x + (float)(-1 * _2X) * zoom, barP->y - (float)(HEARTBARHEIGHT + 1 * _2X) * zoom, zoom, false, false, false, true, cvtDest, cvtLayer, buffering);

			memset(&tempStr, 0, sizeof(tempStr));
			sprintf(tempStr, "+%d", GetHeartAmount());
			DrawTextStr(tempStr, xOffset + barP->x + (float)(19 * _2X) * zoom, barP->y - (float)(HEARTBARHEIGHT + 4 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

			DrawText(TEXT_AFTER, xOffset + barP->x + (float)(43 * _2X) * zoom, barP->y - (HEARTBARHEIGHT + 4 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

			DrawTime(xOffset + barP->x + (float)(79 * _2X) * zoom, barP->y - (HEARTBARHEIGHT + 4 * _2X) * zoom, HEARTTIME - (MC_knlCurrentTimeStamp() - robin.heartTimeStamp), TIME_MINUTE_SECONDS, LEFT, zoom, cvtDest, cvtLayer, buffering);

		}

		break;
	case BAR_BATTLECOIN:
		if (count < 0)
			count = 0;

		BattleCoinBarDraw(count, barP->icon + (barP->iconFrame > 0 ? barP->aniFrame % barP->iconFrame : 0), xOffset + barP->x, barP->y, 16, zoom, cvtDest, cvtLayer, buffering);

		if (barP->addView)
			DrawNum2AutoSpaceing(barP->max, xOffset + barP->x + (float)(GOLDBARWIDTH - 6 * _2X) * zoom, barP->y - (float)GOLDBARHEIGHT * zoom - (float)(1 * _2X) * zoom, RIGHT, false, barP->add >= 0 ? PLUS : MINUS, GOLDBARWIDTH, true, 0.25f * zoom, false, true, cvtDest, cvtLayer, buffering);
		//DrawNum2AutoSpaceing(barP->add, xOffset + barP->x + (float)(GOLDBARWIDTH - 10 * _2X) * zoom, barP->y - (float)GOLDBARHEIGHT * zoom - (float)(4 * _2X) * zoom, RIGHT, false, barP->add >= 0 ? PLUS : MINUS, GOLDBARWIDTH, true, 0.5f * zoom, false, true, cvtDest, cvtLayer, buffering);

		break;
	case BAR_HERO:
		DrawBarIcon(barP->drawFunc, xOffset + barP->x - (float)(MAINMENU_X / 2) * zoom, barP->y + (float)(MAINMENU_Y / 2) * zoom, zoom, cvtDest, cvtLayer, buffering);
		SetRectPoint(xOffset + barP->x - (float)(MAINMENU_X / 2) * zoom, barP->y + (float)(MAINMENU_Y / 2 + 12 * _2X) * zoom, (float)(MAINMENU_X)*zoom, (float)(MAINMENU_Y + 16 * _2X) * zoom, TOUCH_FUNC_POPUP_HEROSTAT);
		break;
	case BAR_CREW:
		DrawBarIcon(barP->drawFunc, xOffset + barP->x - (float)(MAINMENU_X / 2) * zoom, barP->y + (float)(MAINMENU_Y / 2) * zoom, zoom, cvtDest, cvtLayer, buffering);
		SetRectPoint(xOffset + barP->x - (float)(MAINMENU_X / 2) * zoom, barP->y + (float)(MAINMENU_Y / 2 + 12 * _2X) * zoom, (float)(MAINMENU_X)*zoom, (float)(MAINMENU_Y + 16 * _2X) * zoom, TOUCH_FUNC_POPUP_CREWLIST);
		break;
	case BAR_MEDAL:
		DrawRouletteNumIcon(count, barP->icon, xOffset + barP->x, barP->y, true, zoom * 2, CENTER, cvtDest, cvtLayer, buffering);
		break;
	case BAR_ENEMYUSER:
		EnemyUserProfileDraw(&enemyHouse, xOffset + barP->x, barP->y + (float)RAIDGOLDBARHEIGHT / 2 * zoom, zoom, cvtDest, cvtLayer, buffering);
		SetRectPoint(xOffset + barP->x - (float)160 * _2X / 2 * zoom, barP->y + (float)32 * _2X * zoom, (float)160 * _2X * zoom, (float)48 * _2X * zoom, TOUCH_FUNC_GOTOHOUSE);
		break;
	case BAR_ENEMYUSER_BOX:
		EnemyUserProfileDraw_Box(&enemyHouse, xOffset + barP->x - (float)RAIDGOLDBARWIDTH / 2 * zoom, barP->y + (float)RAIDGOLDBARHEIGHT / 2 * zoom, zoom, cvtDest, cvtLayer, buffering);
		break;
	case BAR_DAILYQUEST:
		DrawImage(40 * _2X, 40 * _2X, 40 * _2X * MENUICON_DAILYQUEST, 0 * _2X, xOffset + barP->x - (float)REWARDCARDSIZE_X / 2 * zoom, barP->y + (float)REWARDCARDSIZE_Y / 2 * zoom, false, false, false, false, 32, 1, sprite[MENUICON_IMG], cvtDest, cvtLayer, MENUICON_IMG, buffering);
		MemRectRound(xOffset + barP->x - (float)MAINMENU_X / 2 * zoom, barP->y + (float)(MAINMENU_Y / 2 - MAINMENU_Y + TSIZE) * zoom, (float)MAINMENU_X * zoom, (float)14 * _2X * zoom, COLOR_NAVY, 1 * _2X, cvtDest, cvtLayer, buffering);
		CenterText(TEXT_DAILYQUEST, xOffset + barP->x, barP->y + (float)(MAINMENU_Y / 2 - MAINMENU_Y + TSIZE - 2 * _2X) * zoom, 0.8f * zoom, cvtDest, cvtLayer, buffering);
		SetRectPoint(xOffset + barP->x - (float)MAINMENU_X / 2 * zoom, barP->y + (float)MAINMENU_Y / 2 * zoom, (float)MAINMENU_X * zoom, (float)MAINMENU_Y * zoom, TOUCH_FUNC_DAILYQUEST);
		break;
	case BAR_CREWUPGRADE:
		DrawImage(40 * _2X, 40 * _2X, 40 * _2X * MENUICON_GUILD, 0 * _2X, xOffset + barP->x - (float)REWARDCARDSIZE_X / 2 * zoom, barP->y + (float)REWARDCARDSIZE_Y / 2 * zoom, false, false, false, false, 32, 1, sprite[MENUICON_IMG], cvtDest, cvtLayer, MENUICON_IMG, buffering);
		MemRectRound(xOffset + barP->x - (float)MAINMENU_X / 2 * zoom, barP->y + (float)(MAINMENU_Y / 2 - MAINMENU_Y + TSIZE) * zoom, (float)MAINMENU_X * zoom, (float)14 * _2X * zoom, COLOR_NAVY, 1 * _2X, cvtDest, cvtLayer, buffering);
		CenterText(TEXT_BORDERGUARD, xOffset + barP->x, barP->y + (float)(MAINMENU_Y / 2 - MAINMENU_Y + TSIZE - 2 * _2X) * zoom, 0.8f * zoom, cvtDest, cvtLayer, buffering);
		SetRectPoint(xOffset + barP->x - (float)MAINMENU_X / 2 * zoom, barP->y + (float)MAINMENU_Y / 2 * zoom, (float)MAINMENU_X * zoom, (float)MAINMENU_Y * zoom, TOUCH_FUNC_POPUP_CREWUPGRADE);
		break;
	case BAR_COLLECTIONS:
		DrawBarIcon(barP->drawFunc, xOffset + barP->x - (float)(MAINMENU_X / 2) * zoom, barP->y + (float)(MAINMENU_Y / 2) * zoom, zoom, cvtDest, cvtLayer, buffering);
		SetRectPoint(xOffset + barP->x - (float)(MAINMENU_X / 2) * zoom, barP->y + (float)(MAINMENU_Y / 2 + 12 * _2X) * zoom, (float)(MAINMENU_X)*zoom, (float)(MAINMENU_Y + 16 * _2X) * zoom, TOUCH_FUNC_COLLECTIONS);
		break;
	case BAR_MAINSHOP:
		DrawBarIcon(barP->drawFunc, xOffset + barP->x - (float)(MAINMENU_X / 2) * zoom, barP->y + (float)(MAINMENU_Y / 2) * zoom, zoom, cvtDest, cvtLayer, buffering);
		SetRectPoint(xOffset + barP->x - (float)(MAINMENU_X / 2) * zoom, barP->y + (float)(MAINMENU_Y / 2 + 12 * _2X) * zoom, (float)(MAINMENU_X)*zoom, (float)(MAINMENU_Y + 16 * _2X) * zoom, TOUCH_FUNC_SHOP);
		break;
	case BAR_FRIENDS:
		DrawImage(40 * _2X, 40 * _2X, 40 * _2X * MENUICON_HERO, 0 * _2X, xOffset + barP->x - (float)REWARDCARDSIZE_X / 2 * zoom, barP->y + (float)REWARDCARDSIZE_Y / 2 * zoom, false, false, false, false, 32, 1, sprite[MENUICON_IMG], cvtDest, cvtLayer, MENUICON_IMG, buffering);
		MemRectRound(xOffset + barP->x - (float)MAINMENU_X / 2 * zoom, barP->y + (float)(MAINMENU_Y / 2 - MAINMENU_Y + TSIZE) * zoom, (float)MAINMENU_X * zoom, (float)14 * _2X * zoom, COLOR_NAVY, 1 * _2X, cvtDest, cvtLayer, buffering);
		CenterText(TEXT_MENU_FRIENDS, xOffset + barP->x, barP->y + (float)(MAINMENU_Y / 2 - MAINMENU_Y + TSIZE - 2 * _2X) * zoom, 0.8f * zoom, cvtDest, cvtLayer, buffering);
		SetRectPoint(xOffset + barP->x - (float)MAINMENU_X / 2 * zoom, barP->y + (float)MAINMENU_Y / 2 * zoom, (float)MAINMENU_X * zoom, (float)MAINMENU_Y * zoom, TOUCH_FUNC_FRIENDS);
		break;
	case BAR_NPC:
		DrawImage(207, 33, 0, 953, xOffset + barP->x + shakePosX[effect.hpShake], barP->y - 12 * _2X + shakePosY[effect.hpShake], false, false, false, false, false, 2.0f, sprite[THEATER_IMG], cvtDest, cvtLayer, THEATER_IMG, buffering);
		EnemyProfileDraw(xOffset + barP->x + (float)(4 * _2X) * zoom, barP->y - (float)(14 * _2X) * zoom, ao[ENEMY].type, zoom, false, false, cvtDest, cvtLayer, buffering);

		MemRect(xOffset + barP->x + (float)(40 * _2X + shakePosX[effect.hpShake]) * zoom, barP->y + (float)(-20 * _2X + shakePosY[effect.hpShake]) * zoom, val, (float)(HPBARHEIGHT)*zoom, ENEMYHPBARCOLOR, cvtDest, cvtLayer, buffering);

		DrawNum(count, xOffset + barP->x + (float)(30 * _2X + HPBARWIDTH + shakePosX[effect.hpShake]) * zoom, barP->y + (float)(-20 * _2X + shakePosY[effect.hpShake] - 2 * _2X) * zoom, NUM_FONT_NORMAL, RIGHT, 0, count >= 0 ? false : MINUS, true, zoom, true, cvtDest, cvtLayer, buffering);

		DrawIcon(barP->icon + frame % GOLDICONFRAME, xOffset + barP->x + (float)(30 * _2X + HPBARWIDTH - GetNumDx(count, 0, NUM_FONT_NORMAL, 0, true, zoom, true) - 20 * _2X + shakePosX[effect.hpShake]) * zoom, barP->y + (float)(-20 * _2X + shakePosY[effect.hpShake]) * zoom, zoom, false, false, false, true, cvtDest, cvtLayer, buffering);

		if (attackSequence != ATTACKSEQUENCE_REWARD) {

			DrawRewardCard(ITEM_BOX, goldQuestBox[robin.gameEvent[GetEventMenuIdx(EVENTTYPE_BOSSRAID)].barStatus * BOSSRAIDSIZE + robin.gameEvent[GetEventMenuIdx(EVENTTYPE_BOSSRAID)].barFrame], false, 1, 1, xOffset + barP->x + (float)(HPBARWIDTH + 32 * _2X) * zoom, barP->y - (float)(8 * _2X) * zoom, false, zoom, false, false, true, false, false, true, cvtDest, cvtLayer, buffering);
			//type이 상자면 상세값을 확인할 수 있는 세부창을 띄워줄 수 있도록 한다.
			if (JoyStickPressPossible() == true)
				SetRectPoint(xOffset + barP->x + (float)(HPBARWIDTH + 32 * _2X) * zoom, barP->y - 8 * _2X, REWARDCARDSIZE_X * zoom, REWARDCARDSIZE_Y * zoom, TOUCH_FUNC_POPUP_STAGEREWARD);
		}

		if (effect.hpShake) {
			effect.hpShake++;

			if (effect.hpShake == 5) {
				effect.hpShake = 0;
			}
		}
		break;
	case BAR_QUEST:
		QuestDraw(xOffset + barP->x, barP->y, barP->icon, robin.questCnt - (robin.subQuest == 0 ? 0 : questRequestItemCnt[robin.quest * TOTALSUBQUEST + robin.subQuest - 1]), questRequestItemCnt[robin.quest * TOTALSUBQUEST + robin.subQuest] - (robin.subQuest == 0 ? 0 : questRequestItemCnt[robin.quest * TOTALSUBQUEST + robin.subQuest - 1]), false, false, barP->enemyIcon, barP->rewardIcon, false, zoom, cvtDest, cvtLayer, buffering);
		break;
	case BAR_RAIDGOLD:
		DrawRouletteNumIcon(count, barP->icon, xOffset + barP->x, barP->y, true, CENTER, zoom * 1.5f, cvtDest, cvtLayer, buffering);
		break;
	case BAR_RAIDCOIN:
		DrawRouletteNumIcon(count, barP->icon, xOffset + barP->x, barP->y, true, CENTER, zoom * 1.5f, cvtDest, cvtLayer, buffering);
		break;
	case BAR_COMBATPOWER:
	case BAR_COMBATPOWERALL:
		DrawCombatPower(count, barP->icon, xOffset + barP->x, barP->y, false, zoom, cvtDest, cvtLayer, buffering);
		break;
	case BAR_STAGEPROGRESS:
		StageProgressDraw(xOffset + barP->x, barP->y, count, barP->countFrame, zoom, cvtDest, cvtLayer, buffering);
		break;
	case BAR_REMAINEDTURN:
		RemainedTurnDraw(xOffset + barP->x, barP->y, count, barP->countFrame, zoom, cvtDest, cvtLayer, buffering);
		break;
	case BAR_INVENTORY:
	case BAR_INVENTORY + 1:
	case BAR_INVENTORY + 2:
		InventoryDraw(&ao[barP->owner], xOffset + barP->x, barP->y, zoom, cvtDest, cvtLayer, buffering);
		break;
	case BAR_SKILL:
	case BAR_SKILL + 1:
	case BAR_SKILL + 2:
		DrawQuick(&ao[barP->owner], xOffset + barP->x, barP->y, true, zoom, cvtDest, cvtLayer, buffering);
		break;
	}


	if (barP->aniFrame > 0) {
		if (barP->aniFrame == barP->countFrame) {
			barP->aniFrame = barP->countFrame = 0;
			barP->count += barP->add;
			barP->add = 0;
			barP->addView = false;

			if (drawHandle == MD_PLAY || drawHandle == MD_BATTLE) {
				switch (barP->type) {
				case BAR_COIN:
					//case BAR_BOSSHP:
					barP->count = 0;
					barP->front = false;
					break;
				case BAR_MEDAL:
				case BAR_ITEM:
					barP->active = false;
					barP->count = 0;
					barP->front = false;
					break;
				case BAR_BOX:
				case BAR_GOLD:
				case BAR_BOSSHP:
					barP->front = false;
					break;

				}
			}
		}
		else
			barP->aniFrame++;
	}
}

void HammerBarDraw(int x, int y, long long amount, bool ani, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	if (ani) {
		MemRect(x - (float)(2 * _2X) * zoom, y + 2 * _2X, CROWNBARWIDTH + 4 * _2X, CROWNBARHEIGHT + 4 * _2X, itemColor[frame % 6], cvtDest, cvtLayer, buffering);
	}

	DrawWindow2(x, y, (TSIZE * 6), (TSIZE * 2), COLOR_NAVY, zoom, cvtDest, cvtLayer, buffering);

	if (ironFrame > 0 && ironFrame % 2 == 0 && ani == true)
		DrawIcon(ICON_HAMMER, x, y + (float)(1 * _2X) * zoom, 2 * zoom, false, false, false, true, cvtDest, cvtLayer, buffering);
	else
		DrawIcon(ICON_HAMMER, x + (float)(8 * _2X) * zoom, y - (float)(9 * _2X) * zoom, zoom, false, false, false, true, cvtDest, cvtLayer, buffering);

	DrawNum(amount, x + (float)(TSIZE * 5 + 8 * _2X) * zoom, y - (float)(5 * _2X * 2) * zoom, NUM_FONT_NORMAL, RIGHT, false, false, true, zoom, true, cvtDest, cvtLayer, buffering);
	if (ironFrame > 0 && ani == true)
		ironFrame--;
}


void BossHpBarDraw(long long count, long long max, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	float textPos = 0.0f;
	float width = StringWidth(textId[TEXT_STAGE], zoom) + (float)(4 * _2X) * zoom + GetNumDx(robin.stage + 1, false, NUM_FONT_NORMAL, false, false, zoom, false) + GetNumDx(robin.room + 1, MINUS, NUM_FONT_NORMAL, false, false, zoom, false);
	float goldZoom = zoom * 0.8f;
	float textZoom = zoom * 1.0f;
	int i;
	long long betCnt = bossGold[robin.stage] * GetBetHeart(ao[PLAYER].equip[EQUIP_WEAPON].detail, ao[PLAYER].equip[EQUIP_WEAPON].grade, bet);
	int obj = ENEMY + GetEnemyBarIdx(ENEMY);

	MemRectBothThick(x - (float)BOSSHPBARWIDTH / 2 * zoom, y + (float)BOSSHPBARHEIGHT / 2 * zoom, (float)BOSSHPBARWIDTH * zoom, (float)BOSSHPBARHEIGHT * zoom, COLOR_NAVY, COLOR_BLACK, cvtDest, cvtLayer, buffering);
	MemRect(x - (float)(BOSSHPBARWIDTH / 2 - 4 * _2X) * zoom, y + (float)(BOSSHPBARHEIGHT / 2 - 4 * _2X) * zoom, (float)(BOSSHPBARWIDTH - 8 * _2X) * count / max * zoom, (float)(BOSSHPBARHEIGHT - 8 * _2X) * zoom, COLOR_REALRED, cvtDest, cvtLayer, buffering);
	//DrawSlashNum(count, max, x, y + (float)(BOSSHPBARHEIGHT / 2 - 8 * _2X) * zoom, (float)(BOSSHPBARWIDTH / 2 - 4 * _2X) * zoom, 1.5f * zoom, cvtDest, cvtLayer, buffering);
	if (count > 0)
		DrawNum2AutoSpaceing(count, x + (float)(BOSSHPBARWIDTH / 2 - 8 * _2X) * zoom, y + (float)(BOSSHPBARHEIGHT / 2 - 7 * _2X) * zoom, RIGHT, false, false, (float)(BOSSHPBARWIDTH - 16 * _2X) * zoom, true, 0.4f * zoom, false, 2 * _2X, cvtDest, cvtLayer, buffering);
	//DrawStageLabel(x, y + (float)(BOSSHPBARHEIGHT + 8 * _2X) * zoom, TEXT_ALPHA_WAVE, robin.stage, robin.room, true, 1.0f * zoom, cvtDest, cvtLayer, buffering);

	DevilHeartDraw(x - (float)(BOSSHPBARWIDTH / 2) * zoom, y - (float)16 * _2X * zoom, 1.5f * zoom, cvtDest, cvtLayer, buffering);

	//DrawCmfDetail(CMF_NPC_HEART, PO_C122_HEART, x - (float)(BOSSHPBARWIDTH / 2) * zoom, y - (float)16 * _2X * zoom, RIGHT, 1.5f * zoom, false, false, cvtDest, cvtLayer, buffering);

	//DrawStageLabel(x - (float)(BOSSHPBARWIDTH / 2 + 60 * _2X) * zoom, y + (float)(BOSSHPBARHEIGHT - 4 * _2X) * zoom, TEXT_ALPHA_WAVE, robin.stage, robin.room, true, 0.85f * zoom, cvtDest, cvtLayer, buffering);

}

void MedalBarDraw(int x, int y, long long amount, bool ani, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	if (ani) {
		MemRect(x - (float)(2 * _2X) * zoom, y + (float)(2 * _2X) * zoom, (float)(MEDALBARWIDTH + 4 * _2X) * zoom, (float)(MEDALBARHEIGHT + 4 * _2X) * zoom, itemColor[frame % 6], cvtDest, cvtLayer, buffering);
	}

	DrawWindow2(x, y, MEDALBARWIDTH, MEDALBARHEIGHT, COLOR_NAVY, zoom, cvtDest, cvtLayer, buffering);

	if (medalFrame > 0 && medalFrame % 2 == 0 && ani == true)
		DrawIcon(ICON_MEDAL, x, y + (float)(1 * _2X) * zoom, (float)2 * zoom, false, false, false, true, cvtDest, cvtLayer, buffering);
	else
		DrawIcon(ICON_MEDAL, x + (float)(8 * _2X) * zoom, y - (float)(9 * _2X) * zoom, zoom, false, false, false, true, cvtDest, cvtLayer, buffering);

	DrawNum(amount, x + (float)(TSIZE * 5 + 8 * _2X) * zoom, y - (float)(5 * _2X * 2) * zoom, NUM_FONT_NORMAL, RIGHT, false, false, true, zoom, true, cvtDest, cvtLayer, buffering);
	if (medalFrame > 0 && ani == true)
		medalFrame--;
}

void PvpEventBarDraw(GAMEEVENT* gEvent, int x, int y, int icon, int count, int max, bool animation, bool questAni, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int i, j;

	float w = (float)PVPQUESTBARWIDTH * zoom;
	float h = (float)PVPQUESTBARHEIGHT * zoom;
	float iconZoom = EQUIPZOOM;

	float xPos;
	int moveSpeed = 4 * _2X * 2 / MOTIONDIV;
	long long start, end, current;

	if (robin.pvpSubQuest == 0) {
		start = count;
		end = max;
	}
	else {
		start = count - pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + (robin.pvpSubQuest - 1) * TOTALPVPDETAILREQUEST + 2];

		//end = Max(pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + (robin.pvpSubQuest - 1) * TOTALPVPDETAILREQUEST + 2], max - pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + (robin.pvpSubQuest - 1) * TOTALPVPDETAILREQUEST + 2]);
		end = max - pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + (robin.pvpSubQuest - 1) * TOTALPVPDETAILREQUEST + 2];

	}

	if (robin.pvpSubQuest >= TOTALPVPSUBQUEST)
		return;

	switch (gEvent->barStatus) {
	case EVENT_BAR_NEW:
		w = 0;

		if (gEvent->barFrame > 0) {
			w = Min((float)PVPQUESTBARWIDTH * zoom, (float)gEvent->barFrame * moveSpeed * zoom);
			gEvent->barFrame++;
		}
		break;
	case EVENT_BAR_ITEMGET:
		w = (float)PVPQUESTBARWIDTH * zoom;
		break;
	case EVENT_BAR_GUAGE_FILL:
		w = (float)PVPQUESTBARWIDTH * zoom;
		gEvent->barFrame++;

		if (gEvent->barFrame > end)
			gEvent->barFrame = end;
		break;
	case EVENT_BAR_REWARDGET:
		w = (float)PVPQUESTBARWIDTH * zoom;
		break;
	case EVENT_BAR_NEXT:
		w = (float)PVPQUESTBARWIDTH * zoom;
		break;
	case EVENT_BAR_CLOSE:
		if (gEvent->barFrame > 0) {
			w = Max(0, (float)PVPQUESTBARWIDTH * zoom - (float)gEvent->barFrame * moveSpeed * zoom);
			gEvent->barFrame++;
		}
		break;
	}

	//일단 x를 이동시키고, 클립으로 오른쪽을 잘라준다.
	x = x + (float)PVPQUESTBARWIDTH * zoom - w;

	if (w <= 0)
		return;

	SetSectionClip(x - (float)(ITEMICONSIZE + 4 * _2X) * zoom * iconZoom, y + (float)(ITEMICONSIZE + 4 * _2X) * zoom, w + (float)ITEMICONSIZE * zoom * 4, h + (float)(ITEMICONSIZE * 2 + 8 * _2X) * zoom, false);

	if (animation)
		MemRect(x - (float)(2 * _2X) * zoom, y + (float)(2 * _2X) * zoom, w + (float)(4 * _2X) * zoom, h + (float)(4 * _2X) * zoom, itemColor[frame % 6], cvtDest, cvtLayer, buffering);

	DrawWindow2(x, y, PVPQUESTBARWIDTH, PVPQUESTBARHEIGHT, COLOR_NAVY, zoom, cvtDest, cvtLayer, buffering);

	//TEST
	//count = 70;
	//max = 100;
	//여기야
	if ((float)(PVPQUESTBARWIDTH - 12 * _2X) * start / end + gEvent->barFrame < (float)(PVPQUESTBARWIDTH - 12 * _2X) * (start + 1) / end)
		MemRect(x + (float)(6 * _2X) * zoom, y - (float)(7 * _2X) * zoom, (float)((PVPQUESTBARWIDTH - 12 * _2X) * start / end + gEvent->barFrame) * zoom, (float)(PVPQUESTBARHEIGHT - 14 * _2X) * zoom, COLOR_REALYELLOW, cvtDest, cvtLayer, buffering);
	else
		MemRect(x + (float)(6 * _2X) * zoom, y - (float)(7 * _2X) * zoom, (float)(PVPQUESTBARWIDTH - 12 * _2X) * zoom * start / end, (float)(PVPQUESTBARHEIGHT - 14 * _2X) * zoom, COLOR_REALYELLOW, cvtDest, cvtLayer, buffering);

	DrawIcon(icon, x + (float)(-ITEMICONSIZE) * zoom * iconZoom, y + (float)(2 * _2X) * zoom * iconZoom, zoom * iconZoom, COLOR_BROWN, animation, true, true, cvtDest, cvtLayer, buffering);

	j = 0;
	for (i = 0; i < TOTALPVPDETAILREQUEST; i++) {
		if (count >= pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i]) {
			j++;
			break;
		}
	}
#ifdef GUIDELINE
	for (i = 0; i < TOTALPVPDETAILREQUEST; i++) {
		MemRect(x + (float)(6 * _2X) * zoom + (float)(PVPQUESTBARWIDTH - 12 * _2X) * pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i] / max, y - (float)(7 * _2X) * zoom, (float)(1 * _2X) * zoom, (float)(PVPQUESTBARHEIGHT - 14 * _2X) * zoom, COLOR_REALRED, cvtDest, cvtLayer, buffering);
		DrawNum(pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i], x + (float)(6 * _2X) * zoom + (float)(PVPQUESTBARWIDTH - 12 * _2X) * pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i] / max, y - (float)(7 * _2X + PVPQUESTBARHEIGHT) * zoom, NUM_FONT_NORMAL, CENTER, false, false, true, zoom, true, cvtDest, cvtLayer, buffering);
	}
#endif
	xPos = 0;

	if (curMenu == MENU_PLAY) {
		for (i = 0; i < TOTALPVPDETAILREQUEST; i++) {
			if (robin.pvpSubQuest == 0)
				xPos = (float)(6 * _2X + (PVPQUESTBARWIDTH - 12 * _2X) * (pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i]) / (pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + 2])) * zoom;
			else
				xPos = (float)(6 * _2X + (PVPQUESTBARWIDTH - 12 * _2X) * (pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i] - pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + (robin.pvpSubQuest - 1) * TOTALPVPDETAILREQUEST + 2]) / (pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + 2] - pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + (robin.pvpSubQuest - 1) * TOTALPVPDETAILREQUEST + 2])) * zoom;

			if (i >= robin.pvpDetailQuest) {
				DrawRewardCard(pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 0], pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 1], pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 2], 0, pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 3], x + xPos - (float)REWARDCARDSIZE_X / 2 * zoom * iconZoom * 0.6f, y + (float)8 * _2X * zoom, false, 0.6f * zoom * iconZoom, false, false, true, false, false, true, cvtDest, cvtLayer, buffering);
				pvpRewardPosition[i][0] = x + xPos + (float)(ITEMICONSIZE / 2) * 0.6f * zoom * iconZoom;
				pvpRewardPosition[i][1] = y - (float)(2 * _2X) * zoom * iconZoom - (float)(ITEMICONSIZE / 2) * zoom * iconZoom;

				//TEST
				//DrawNum(pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i], x + xPos + (float)ITEMICONSIZE / 2 * zoom, y + (-(float)ITEMICONSIZE - 4 * _2X) * zoom, NUM_FONT_LARGE, CENTER, false, false, true, zoom / 2, cvtDest, cvtLayer, buffering);
			}

		}
	}
	else {
		for (i = 0; i < TOTALPVPDETAILREQUEST; i++) {
			if (robin.pvpSubQuest == 0)
				xPos = (float)(6 * _2X + (PVPQUESTBARWIDTH - 12 * _2X) * (pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i]) / (pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + 2])) * zoom;
			else
				xPos = (float)(6 * _2X + (PVPQUESTBARWIDTH - 12 * _2X) * (pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i] - pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + (robin.pvpSubQuest - 1) * TOTALPVPDETAILREQUEST + 2]) / (pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + 2] - pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + (robin.pvpSubQuest - 1) * TOTALPVPDETAILREQUEST + 2])) * zoom;

			if (i >= robin.pvpDetailQuest) {
				//DrawIcon(GetItemIcon(pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 0], pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 1], pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 2]), x + xPos, y - (float)(2 * _2X) * zoom, zoom, COLOR_BROWN, false, false, cvtDest, cvtLayer, buffering);
				DrawRewardCard(pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 0], pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 1], pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 2], 0, pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 3], x + xPos - (float)REWARDCARDSIZE_X / 2 * zoom * iconZoom * 0.6f, y + (float)8 * _2X * zoom, false, 0.6f * zoom * iconZoom, false, false, true, false, false, true, cvtDest, cvtLayer, buffering);

				pvpRewardPosition[i][0] = x + xPos + (float)(ITEMICONSIZE / 2) * 0.6f * zoom * iconZoom;
				pvpRewardPosition[i][1] = y - (float)(2 * _2X) * zoom * iconZoom - (float)(ITEMICONSIZE / 2) * zoom * iconZoom;

				//DrawNum(pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i], x + xPos + (float)ITEMICONSIZE / 2 * zoom, y + (-(float)ITEMICONSIZE - 4 * _2X) * zoom, NUM_FONT_LARGE, CENTER, false, false, true, zoom / 2, cvtDest, cvtLayer, buffering);
			}
		}
	}

	UnSectionClip(false);

	if (gEvent->barStatus == EVENT_BAR_REWARDGET && gEvent->frame == FPS) {
		//gEvent->
	}
}

void DevilHeartDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	int tempGrayScale = grayScale;
	OBJECT* pObj = &ao[PLAYER];
	OBJECT* eObj = &ao[ENEMY];
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	int crewIdx = 0;

	float defaultAngle;
	float radius = (float)ROULETTERADIUS * zoom;//반경

	if (curtainFrame == 0 && areaFrame == 0 && GetCardMarkCnt() == maxRouletteCnt && arenaStatus == STATUS_READY)
		arenaStatus = STATUS_PLAY;

	//defaultAngle = 360 / maxRouletteCnt;
	defaultAngle = 360 / 6;

	switch (attackSequence) {
	default:
		DrawCmfDetail(CMF_NPC_HEART, PO_C122_HEART, x, y, RIGHT, zoom, false, false, cvtDest, cvtLayer, buffering);
		break;
	}


}

void GoldBarDraw(long long count, int icon, int x, int y, int alpha, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	DrawRoundBar(x + (float)0 * zoom, y, 1.0f, ROUNDBAR_BIG, BARCOLOR_YELLOW, alpha, 0.5f * zoom, cvtDest, cvtLayer, buffering);
	DrawIcon(icon, x + (float)(6 * _2X) * zoom, y - (float)(6 * _2X) * zoom, 1.2f * zoom, COLOR_BROWN, false, false, 1, cvtDest, cvtLayer, buffering);
#ifdef NUMTTF
	DrawBigNumTTF(count, x + (float)(GOLDBARWIDTH - 10 * _2X) * zoom, y - (float)(5 * _2X * 2) * zoom, NUM_FONT_NORMAL, RIGHT, false, false, (float)(GOLDBARWIDTH - ITEMICONSIZE - 0 * _2X) * zoom, true, zoom, true, cvtDest, cvtLayer, buffering);
#else
	DrawNum2AutoSpaceing(count, x + (float)(GOLDBARWIDTH - 7 * _2X) * zoom, y - (float)(10 * _2X) * zoom, RIGHT, false, false, (float)(GOLDBARWIDTH - ITEMICONSIZE * 1.2f - 13 * _2X) * zoom, true, NUM2ZOOM * 1.2f * zoom, true, true, cvtDest, cvtLayer, buffering);
	//DrawBigNum2Bold(count, x + (float)(0.5f * GOLDBARWIDTH - 8 * _2X) * zoom, y - (float)(11 * _2X) * zoom, RIGHT, false, false, (float)(GOLDBARWIDTH * 0.55f - ITEMICONSIZE * 1.2f - 12 * _2X) * zoom, true, NUM2ZOOM * 1.2f * zoom, true, cvtDest, cvtLayer, buffering);
#endif
}

void BattleCoinBarDraw(long long count, int icon, int x, int y, int alpha, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	DrawRoundBar(x + (float)0 * zoom, y, 1.0f, ROUNDBAR_BIG, BARCOLOR_PURPLE, alpha, 0.5f * zoom, cvtDest, cvtLayer, buffering);
	DrawIcon(icon, x + (float)(6 * _2X) * zoom, y - (float)(6 * _2X) * zoom, 1.2f * zoom, COLOR_BROWN, false, false, 1, cvtDest, cvtLayer, buffering);
#ifdef NUMTTF
	DrawBigNumTTF(count, x + (float)(GOLDBARWIDTH - 10 * _2X) * zoom, y - (float)(5 * _2X * 2) * zoom, NUM_FONT_NORMAL, RIGHT, false, false, (float)(GOLDBARWIDTH - ITEMICONSIZE - 0 * _2X) * zoom, true, zoom, true, cvtDest, cvtLayer, buffering);
#else
	DrawNum2AutoSpaceing(count, x + (float)(GOLDBARWIDTH - 7 * _2X) * zoom, y - (float)(10 * _2X) * zoom, RIGHT, false, false, (float)(GOLDBARWIDTH - ITEMICONSIZE * 1.2f - 13 * _2X) * zoom, true, NUM2ZOOM * 1.2f * zoom, true, true, cvtDest, cvtLayer, buffering);
	//DrawBigNum2Bold(count, x + (float)(0.5f * GOLDBARWIDTH - 8 * _2X) * zoom, y - (float)(11 * _2X) * zoom, RIGHT, false, false, (float)(GOLDBARWIDTH * 0.55f - ITEMICONSIZE * 1.2f - 12 * _2X) * zoom, true, NUM2ZOOM * 1.2f * zoom, true, cvtDest, cvtLayer, buffering);
#endif
}

void ExpBarWideDraw(int lv, long long count, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	//count = 10;
	//MemRect(x + (float)(ITEMICONSIZE * 1.5f / 2) * zoom, y - (float)(2 * _2X) * zoom, (float)(CROWNBARWIDTH - 1.5f * ITEMICONSIZE + 4 * _2X) * zoom, (float)(CROWNBARHEIGHT + 4 * _2X) * zoom, COLOR_BROWN, cvtDest, cvtLayer, buffering);
	//MemRect(x + (float)(ITEMICONSIZE * 1.5f / 2 + 2 * _2X) * zoom, y - (float)(4 * _2X) * zoom, (float)(CROWNBARWIDTH - 1.5f * ITEMICONSIZE) * zoom, (float)(CROWNBARHEIGHT)* zoom, COLOR_NAVY, cvtDest, cvtLayer, buffering);
	//count = 33960000;

	DrawWindow2(x + (float)(ITEMICONSIZE * 1.5f + 2 * _2X) * zoom, y, (float)(CROWNBARWIDTH_WIDE - 1.5f * ITEMICONSIZE - 28 * _2X), (float)(CROWNBARHEIGHT), COLOR_NAVY, zoom, cvtDest, cvtLayer, buffering);

	MemRect(x + (float)(ITEMICONSIZE * 1.5f + 2 * _2X + 6 * _2X) * zoom, y - (float)(7 * _2X) * zoom, Min((float)(CROWNBARWIDTH - 1.5f * ITEMICONSIZE - 28 * _2X) * zoom, (float)(CROWNBARWIDTH_WIDE - 1.5f * ITEMICONSIZE - 28 * _2X) * ((float)(count - NextExp(lv - 1)) / (float)(NextExp(lv) - NextExp(lv - 1))) * zoom), (float)(CROWNBARHEIGHT - 14 * _2X) * zoom, COLOR_REALYELLOW, cvtDest, cvtLayer, buffering);
	//MemRect(x + (float)(ITEMICONSIZE * 1.5f / 2 + 8 * _2X) * zoom, y - (float)(8 * _2X) * zoom, (float)100, (float)(CROWNBARHEIGHT - 16 * _2X)* zoom, COLOR_REALYELLOW, cvtDest, cvtLayer, buffering);

	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%ld / %ld", (long)(count - NextExp(lv - 1)), (long)(NextExp(lv) - NextExp(lv - 1)));
	//sprintf(tempStr, "%ld / %ld", 80, 100);
	CenterTextStr(tempStr, x + (float)(CROWNBARWIDTH_WIDE / 2 + 1.5f * ITEMICONSIZE - 24 * _2X) * zoom, y - (float)(4 * _2X + 6 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

	DrawStarNum(ICON_CROWN, lv + 1, x + (float)2 * _2X * zoom, y - (float)4 * _2X * zoom, 1.5f * zoom, cvtDest, cvtLayer, buffering);
	//DrawIcon(ICON_STAR, x + (float)2 * _2X * zoom, y - (float)4 * _2X * zoom, 1.5f * zoom, COLOR_BROWN, false, false, cvtDest, cvtLayer, buffering);
	//DrawNum(lv, x + (float)(2 * _2X + ITEMICONSIZE * 1.5f / 2) * zoom, y - (float)10 * _2X * zoom, NUM_FONT_NORMAL, CENTER, false, false, false, zoom, false, cvtDest, cvtLayer, buffering);
	DrawLevelUpCard(levelUpReward[lv], lv, false, x + (float)(CROWNBARWIDTH_WIDE + 1.5f * ITEMICONSIZE - 4 * _2X - 48 * _2X) * zoom, y - (float)(0 * _2X) * zoom, 0.4f * zoom, cvtDest, cvtLayer, buffering);
}

void HeartBarDraw(int count, int max, int x, int y, int alpha, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	DrawRoundBar(x, y, (float)Min(count, max) / max, ROUNDBAR_BIG, BARCOLOR_RED, alpha, 0.5f * zoom, cvtDest, cvtLayer, buffering);

	DrawIcon(ICON_HEART, x + (float)0 * _2X * zoom, y - (float)0 * _2X * zoom, 1.0f * zoom, COLOR_WHITE, false, false, 3.0f, cvtDest, cvtLayer, buffering);
#ifdef NUMTTF
	DrawBigNumTTF(count, x + (float)(GOLDBARWIDTH - 10 * _2X) * zoom, y - (float)(5 * _2X * 2) * zoom, NUM_FONT_NORMAL, RIGHT, false, false, (float)(GOLDBARWIDTH - ITEMICONSIZE - 0 * _2X) * zoom, true, zoom, true, cvtDest, cvtLayer, buffering);
#else
	DrawSlashNum(count, max, x + (float)(HEARTBARWIDTH / 2 + 2 * _2X) * zoom, y - (float)(10 * _2X) * zoom, HEARTBARWIDTH, 1.2f * zoom, cvtDest, cvtLayer, buffering);

	//DrawNum2AutoSpaceing(count, x + (float)(CROWNBARWIDTH - 7 * _2X) * zoom, y - (float)(10 * _2X) * zoom, RIGHT, false, false, (float)(CROWNBARWIDTH - ITEMICONSIZE * 1.2f - 13 * _2X) * zoom, true, NUM2ZOOM * 1.2f * zoom, true, true, cvtDest, cvtLayer, buffering);
	//DrawBigNum2Bold(count, x + (float)(CROWNBARWIDTH - 7 * _2X) * zoom, y - (float)(10 * _2X) * zoom, RIGHT, false, false, (float)(CROWNBARWIDTH - ITEMICONSIZE * 1.2f - 13 * _2X) * zoom, true, NUM2ZOOM * 1.2f * zoom, true, cvtDest, cvtLayer, buffering);
#endif
}

void ExpBarDraw(int lv, long long count, int x, int y, int alpha, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	DrawRoundBar(x + (float)0 * zoom, y, ((float)(count - NextExp(lv - 1)) / (float)(NextExp(lv) - NextExp(lv - 1))), ROUNDBAR_SMALL, BARCOLOR_PURPLE, alpha, 0.5f * zoom, cvtDest, cvtLayer, buffering);
#ifdef NUMTTF
	DrawBigNumTTF(count, x + (float)(GOLDBARWIDTH - 10 * _2X) * zoom, y - (float)(5 * _2X * 2) * zoom, NUM_FONT_NORMAL, RIGHT, false, false, (float)(GOLDBARWIDTH - ITEMICONSIZE - 0 * _2X) * zoom, true, zoom, true, cvtDest, cvtLayer, buffering);
#else
	DrawNum2AutoSpaceing(count, x + (float)(CROWNBARWIDTH - 7 * _2X) * zoom, y - (float)(10 * _2X) * zoom, RIGHT, false, false, (float)(CROWNBARWIDTH - ITEMICONSIZE * 1.2f - 13 * _2X) * zoom, true, NUM2ZOOM * 1.2f * zoom, true, true, cvtDest, cvtLayer, buffering);
#endif

	DrawStarNum(ICON_CROWN, lv + 1, x + (float)6 * _2X * zoom, y - (float)6 * _2X * zoom, 1.2f * zoom, cvtDest, cvtLayer, buffering);

}

void ShieldBarDraw(long long count, long long max, int x, int y, float zoom, int hpColor, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	long long val;
	float coinZoom = 1.0f;
	val = (float)(SIMPLEHPBARWIDTH)*zoom * count / max;

	MemRect(xOffset + x + (float)shakePosX[effect.hpShake] * zoom, y + (float)shakePosY[effect.hpShake] * zoom, (float)(SIMPLEHPBARWIDTH + 2 * _2X) * zoom, (float)(SIMPLEHPBARHEIGHT + 2 * _2X) * zoom, COLOR_NAVY, cvtDest, cvtLayer, buffering);
	MemRect(xOffset + x + (float)(1 * _2X + shakePosX[effect.hpShake]) * zoom, y + (float)(-1 * _2X + shakePosY[effect.hpShake]) * zoom, val, (float)(SIMPLEHPBARHEIGHT)*zoom, hpColor, cvtDest, cvtLayer, buffering);
	CenterText(TEXT_SHIELD, xOffset + x + (float)(SIMPLEHPBARWIDTH / 2 + shakePosX[effect.hpShake]) * zoom, y + (float)(shakePosY[effect.hpShake] + 12 * _2X) * zoom, zoom, cvtDest, cvtLayer, buffering);

	//상태이상이 걸려
	if (effect.hpShake) {
		effect.hpShake++;

		if (effect.hpShake == 5) {
			effect.hpShake = 0;
		}
	}
}

void SimpleHpBarDraw(long long count, long long max, int x, int y, float zoom, int hpColor, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	long long val;
	float coinZoom = 1.0f;
	val = (float)(SIMPLEHPBARWIDTH)*zoom * count / max;

	MemRect(x + (float)shakePosX[effect.hpShake] * zoom, y + (float)shakePosY[effect.hpShake] * zoom, (float)(SIMPLEHPBARWIDTH + 2 * _2X) * zoom, (float)(SIMPLEHPBARHEIGHT + 2 * _2X) * zoom, COLOR_NAVY, cvtDest, cvtLayer, buffering);
	MemRect(x + (float)(1 * _2X + shakePosX[effect.hpShake]) * zoom, y + (float)(-1 * _2X + shakePosY[effect.hpShake]) * zoom, val, (float)(SIMPLEHPBARHEIGHT)*zoom, hpColor, cvtDest, cvtLayer, buffering);
	DrawNum2AutoSpaceing(count, x + (float)SIMPLEHPBARWIDTH * zoom / 2, y + (float)shakePosY[effect.hpShake] * zoom + (float)-12 * _2X * zoom, CENTER, 0, false, (float)HPBARWIDTH * zoom, true, NUM2ZOOM * 1.1f * zoom, false, true, cvtDest, cvtLayer, buffering);
	
	//상태이상이 걸려
	if (effect.hpShake) {
		effect.hpShake++;

		if (effect.hpShake == 5) {
			effect.hpShake = 0;
		}
	}
}

void HpBarDraw(int type, long long count, long long max, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering)
{
	long long val;
	float coinZoom = 1.0f;
	int textPos = 0;
	float textZoom = 0.8f * zoom;
	int obj = ENEMY + GetEnemyBarIdx(ENEMY);
	int HPBARCOLOR = type <= MAXX ? COLOR_GREEN : COLOR_REALRED;

	val = (float)(HPBARWIDTH - 4 * _2X) * zoom * count / max;

	if (type <= MAXX) {
		DrawFrame(xOffset + x + (float)26 * _2X * zoom + (float)shakePosX[effect.hpShake] * zoom, y - (float)(1 * _2X + shakePosY[effect.hpShake]) * zoom, (float)HPBARWIDTH * zoom, (float)(HPBARHEIGHT)*zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
		MemRect(xOffset + x + (float)26 * _2X * zoom + (float)(1 * _2X + shakePosX[effect.hpShake]) * zoom, y + (float)(-3 * _2X + shakePosY[effect.hpShake]) * zoom, val, (float)(HPBARHEIGHT - 4 * _2X) * zoom, 0x33FF00, cvtDest, cvtLayer, buffering);

		DrawBigNum(count, xOffset + x + (float)26 * _2X * zoom + (float)(HPBARWIDTH + shakePosX[effect.hpShake] - 4 * _2X) * zoom, y + (float)(-3 * _2X + shakePosY[effect.hpShake]) * zoom, NUM_FONT_NORMAL, RIGHT, 0, count >= 0 ? false : MINUS, (float)(HPBARWIDTH - ITEMICONSIZE) * zoom, true, zoom, false, cvtDest, cvtLayer, buffering);

		EnemyProfileDraw(xOffset + x, y + (float)0 * _2X * zoom, type, false, false, 0.8f * zoom, cvtDest, cvtLayer, buffering);
	}
	else {
		DrawFrame(xOffset + x + (float)shakePosX[effect.hpShake] * zoom, y - (float)(1 * _2X + shakePosY[effect.hpShake]) * zoom, (float)HPBARWIDTH * zoom, (float)(HPBARHEIGHT)*zoom, FRAME_SHOPBALLOON, cvtDest, cvtLayer, buffering);
		MemRect(xOffset + x + (float)(2 * _2X + shakePosX[effect.hpShake]) * zoom, y + (float)(-3 * _2X + shakePosY[effect.hpShake]) * zoom, val, (float)(HPBARHEIGHT - 4 * _2X) * zoom, COLOR_VERYRED, cvtDest, cvtLayer, buffering);

		DrawBigNum(count, xOffset + x + (float)4 * _2X * zoom + (float)(shakePosX[effect.hpShake]) * zoom, y + (float)(-3 * _2X + shakePosY[effect.hpShake]) * zoom, NUM_FONT_NORMAL, LEFT, 0, count >= 0 ? false : MINUS, (float)(HPBARWIDTH - ITEMICONSIZE) * zoom, true, zoom, false, cvtDest, cvtLayer, buffering);

		EnemyProfileDraw(xOffset + x + (float)(HPBARWIDTH - 4 * _2X) * zoom, y + (float)0 * _2X * zoom, type, false, false, 0.8f * zoom, cvtDest, cvtLayer, buffering);
	}

	if (effect.hpShake) {
		effect.hpShake++;

		if (effect.hpShake == 5) {
			effect.hpShake = 0;
		}
	}
}