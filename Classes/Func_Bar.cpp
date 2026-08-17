#include "Core.h"
#include "Data.h"
#include "Func.h"
#include "Text.h"

void DrawBarIcon(int type, int x, int y, float zoom)
{
	int fontColor = 0x555555;

	switch (type) {
	case BAR_CASTLE:
		DrawImage(128, 128, 128 * 3, 0, x + (float)(MAINMENU_X / 2) * zoom - (float)(128) * 0.4f * zoom, y - (float)(MAINMENU_Y / 2) * zoom + (float)(128) * 0.4f * zoom + (float)(0 * _2X) * zoom, false, false, false, false, 32, 0.8f * zoom, sprite[THEATER_IMG], THEATER_IMG);
		//SetFontColor(fontColor);
		//SetFontColor(COLOR_WHITE);
		break;
	case BAR_CREW:
		DrawImage(128, 128, 128 * 1, 0, x + (float)(MAINMENU_X / 2) * zoom - (float)(128) * 0.4f * zoom, y - (float)(MAINMENU_Y / 2) * zoom + (float)(128) * 0.4f * zoom + (float)(0 * _2X) * zoom, false, false, false, false, 32, 0.8f * zoom, sprite[THEATER_IMG], THEATER_IMG);
		//SetFontColor(fontColor);
		//SetFontColor(COLOR_WHITE);
		break;
	case BAR_EQUIP:
		DrawImage(128, 128, 128 * 0, 0, x + (float)(MAINMENU_X / 2) * zoom - (float)(128) * 0.4f * zoom, y - (float)(MAINMENU_Y / 2) * zoom + (float)(128) * 0.4f * zoom + (float)(0 * _2X) * zoom, false, false, false, false, 32, 0.8f * zoom, sprite[THEATER_IMG], THEATER_IMG);
		break;
	case BAR_MAINSHOP:
		DrawImage(128, 128, 128 * 2, 0, x + (float)(MAINMENU_X / 2) * zoom - (float)(128) * 0.4f * zoom, y - (float)(MAINMENU_Y / 2) * zoom + (float)(128) * 0.4f * zoom + (float)(0 * _2X) * zoom, false, false, false, false, 32, 0.8f * zoom, sprite[THEATER_IMG], THEATER_IMG);

		//SetFontColor(fontColor);
		//SetFontColor(COLOR_WHITE);
		break;
	}
}

void BarDraw(BAR* barP, float zoom)
{
	//메뉴형 바(동료/장비/성/상점/일일퀘스트 등)는 모두 같은 크기의 터치영역을
	//쓰고, 그 영역의 한가운데가 barP->x/y다. 여기서 zoom 하나만 눌림 배율로
	//곱해두면 아래 그리기가 전부 제자리에서 줄었다 튀어오른다.
	//
	//누른 지점이 이 사각형 안일 때만 1이 아닌 값이 오므로, 크기가 다른
	//골드바나 하트바는 저절로 걸러진다. 눌린 뒤에 터치영역이 같이 줄어드는
	//것은 상관없다 - 취소 판정은 누를 때 잡아둔 사각형으로 하기 때문이다.
	zoom *= GetButtonPressScale(
		xOffset + barP->x - (float)MAINMENU_X / 2 * zoom,
		barP->y + (float)MAINMENU_Y / 2 * zoom,
		(float)MAINMENU_X * zoom,
		(float)MAINMENU_Y * zoom);

	long long count = barP->count;
	int max;//퀘스트에서 맥스값 숫자 적어줄 때 쓰는 변수
	long long val;

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

		GoldBarDraw(count, barP->icon + (barP->iconFrame > 0 ? barP->aniFrame % barP->iconFrame : 0), xOffset + barP->x, barP->y, false, zoom);

		if (barP->addView)
			DrawNum2AutoSpaceing(barP->addViewSum, xOffset + barP->x + (float)(GOLDBARWIDTH - 4 * _2X) * zoom, barP->y - (float)GOLDBARHEIGHT * zoom - (float)(1 * _2X) * zoom, RIGHT, false, barP->addViewSum >= 0 ? PLUS : MINUS, GOLDBARWIDTH, true, 0.3f * zoom, false, true);
		break;
	case BAR_CROWN:
		ExpBarDraw(robin.lv, count, xOffset + barP->x, barP->y, false, zoom);
		SetRectPoint(xOffset + barP->x, barP->y, (float)CROWNBARWIDTH * zoom, (float)CROWNBARHEIGHT * zoom, TOUCH_FUNC_POPUP_LVUPREWARD);

		if (barP->addView)
			DrawNum2AutoSpaceing(barP->addViewSum, xOffset + barP->x + (float)(CROWNBARWIDTH - 4 * _2X) * zoom, barP->y - (float)CROWNBARHEIGHT * zoom - (float)(1 * _2X) * zoom, RIGHT, false, barP->addViewSum >= 0 ? PLUS : MINUS, GOLDBARWIDTH, true, 0.3f * zoom, false, true);

		break;
	case BAR_HAMMER:
	case BAR_SHIELD:

		DrawIcon(barP->icon + (barP->iconFrame > 0 ? barP->aniFrame % barP->iconFrame : 0), xOffset + barP->x + (HAMMERBARWIDTH - ITEMICONSIZE * 1.5f) / 2 * zoom, barP->y - 2 * _2X, 1.5f * zoom, COLOR_WHITE, false, false, 2);
		if (barP->drawFunc == BAR_SHIELD) {
			DrawSlashNum(barP->count, GetMaxShield(), xOffset + barP->x + (float)(HAMMERBARWIDTH / 2 + 2 * _2X) * zoom, barP->y - (float)(7 * _2X + ITEMICONSIZE * 1.5f) * zoom, (float)ITEMICONSIZE * 3, zoom * 0.8f);
		}
		else {
			DrawBigNumTTF(count, xOffset + barP->x + (float)(ITEMICONSIZE * 1.5f / 2) * zoom + (HAMMERBARWIDTH - ITEMICONSIZE * 1.5f) / 2 * zoom, barP->y - (float)(2 * _2X + ITEMICONSIZE * 1.5f) * zoom, NUM_FONT_NORMAL, CENTER, false, false, (float)HAMMERBARWIDTH * zoom, false, 0.7f * zoom, true);
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
			PushButtonDraw(bet, xOffset + barP->x, barP->y, barP->iconFrame, zoom + (GetRectPoint(touchX, touchY, xOffset + barP->x - (float)BOXSIZE_X * zoom / 2, barP->y + (float)BOXSIZE_Y * 2 / 3 * zoom, (float)BOXSIZE_X * zoom, (float)BOXSIZE_Y * 2 / 3 * zoom) == true && touchedFrame > 1 ? Min(0.1f, (float)touchedFrame * 0.01f) : 0), true);

			//그리는건 Bar Heart에서 책임진다.
			if (JoyStickPressPossible() && autoPlay == false) {
				if (frame % (FPS * 10) < 3 * FPS)
					DrawHand(xOffset + barP->x - (float)BOXSIZE_X * zoom / 2, barP->y + (float)(BOXSIZE_Y * 3 / 3 - 24 * _2X) * zoom, robin.playtime / MOTIONDIV, 2.0f * zoom);
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
		BossHpBarDraw(count, barP->max, xOffset + barP->x, barP->y, zoom);
		
		if (barP->addView)
			DrawNum2AutoSpaceing(barP->addViewSum, xOffset + barP->x + (float)(BOSSHPBARWIDTH + 32 * _2X) * 0.5f * zoom, barP->y + (float)BOSSHPBARHEIGHT * zoom / 2 + (float)(20 * _2X) * 0.5f * zoom, LEFT, false, barP->addViewSum >= 0 ? PLUS : MINUS, GOLDBARWIDTH, true, 0.5f * zoom, false, true);

		break;
	case BAR_COIN:
		if (count != 0) {
			DrawRouletteNumIcon(count, barP->icon, xOffset + barP->x, barP->y, true, CENTER, zoom);
		}
		break;
	case BAR_ITEM:
		DrawRouletteNumIcon(count, barP->icon, xOffset + barP->x, barP->y, true, CENTER, barP->zoom);
		break;
	case BAR_HEART:
		HeartBarDraw(count, GetInitHeart(), xOffset + barP->x - (float)HEARTBARWIDTH / 2 * barP->zoom, barP->y, false, barP->zoom);

		SetFontColor(COLOR_WHITE);

		if (barP->addView)
			DrawNum2AutoSpaceing(barP->addViewSum, xOffset + barP->x + (float)(HEARTBARWIDTH / 2 - 16 * _2X) * zoom, barP->y - (float)HEARTBARHEIGHT * zoom - (float)(1 * _2X) * zoom, RIGHT, false, barP->addViewSum >= 0 ? PLUS : MINUS, HEARTBARWIDTH, true, 0.3f * zoom, false, true);
		else {
			
			if (count >= GetInitHeart()) {
				CenterText(TEXT_HEARTISFULL, xOffset + barP->x, barP->y - (float)(HEARTBARHEIGHT + 2 * _2X) * barP->zoom, barP->zoom);
				//SetFontColor(false);
			}
			//만약 모자라면 얼마 뒤에 스핀을 획득하는지 보여준다.
			else {
				DrawIcon(barP->icon, xOffset + barP->x - (float)(HEARTBARWIDTH / 2 - 0 * _2X) * barP->zoom, barP->y - (float)(HEARTBARHEIGHT + 0 * _2X) * barP->zoom, barP->zoom, false, false, false, true);

				memset(&tempStr, 0, sizeof(tempStr));
				sprintf(tempStr, "+%d", GetHeartAmount());
				DrawTextStr(tempStr, xOffset + barP->x - (float)(HEARTBARWIDTH / 2 - 18 * _2X) * barP->zoom, barP->y - (float)(HEARTBARHEIGHT + 1 * _2X) * barP->zoom, barP->zoom);

				DrawText(TEXT_AFTER, xOffset + barP->x - (float)(HEARTBARWIDTH / 2 - 42 * _2X) * barP->zoom, barP->y - (float)(HEARTBARHEIGHT + 1 * _2X) * barP->zoom, barP->zoom);

				DrawTime(xOffset + barP->x - (float)(HEARTBARWIDTH / 2 - 78 * _2X) * zoom, barP->y - (float)(HEARTBARHEIGHT + 1 * _2X) * zoom, HEARTTIME - (MC_knlCurrentTimeStamp() - robin.heartTimeStamp), TIME_MINUTE_SECONDS, LEFT, zoom);

			}
		}
		break;
	case BAR_ROULETTE://룰렛
		RouletteDraw(xOffset + barP->x, barP->y, barP->zoom);

		//룰렛이 막 열렸다는 것을 알리는 반짝임. 슬롯판 위에 흰빛을 깜빡여 덮는다.
		//SetDemo(DEMO_TUTORIAL_ROULETTE)가 프레임 수를 걸어두고 여기서 소진한다.
		if (rouletteGlowFrame > 0) {
			//0 -> 최대 -> 0으로 두어 번 오갔다 사라진다.
			int glowAlpha = (int)(12 * (0.5f + 0.5f * sinf((float)rouletteGlowFrame * 0.25f))
				* (float)rouletteGlowFrame / (float)ROULETTE_GLOW_FRAME);

			if (glowAlpha > 0) {
				SetAlpha(glowAlpha);
				MemRect(xOffset + barP->x - (float)SLOTSIZE_X / 2 * barP->zoom, barP->y,
					(float)SLOTSIZE_X * barP->zoom, (float)SLOTSIZE_Y * barP->zoom, COLOR_WHITE);
				SetAlpha(32);
			}

			rouletteGlowFrame--;
		}


		//튜토리얼: 성 위에서 갈아입은 주인공을 비춘다.
		//플레이 화면에서 매 프레임 도는 자리라 여기에 붙였다(스팟라이트는 즉시모드).
		SetTutorialHeroSpotlight();
		if (touchDisable == false)
			SetRectPoint(xOffset + barP->x - (float)SLOTSIZE_X / 2 * barP->zoom, barP->y, (float)SLOTSIZE_X * barP->zoom, (float)SLOTSIZE_Y * barP->zoom, TOUCH_FUNC_POPUP_CREWLIST);
		break;
	case BAR_HEARTBET://하트베팅 버튼
	{
		//인터랙티브 전투 튜토리얼: 하트베팅을 아직 안 배운 시점(DEMO_TUTORIAL_HEARTBET 전)에는 공격
		//버튼만 눌러야 하므로 하트베팅 버튼의 터치와 DrawHand 안내를 막는다.
		//다만 그레이스케일은 걸지 않는다 - 룰렛 잠금 표시와 마찬가지로 버튼은 원색 그대로 보여준다.
		//
		//잠금은 튜토리얼이 도는 동안에만 건다. demoSeen만으로 판정하면 튜토리얼을 건너뛰었거나
		//그 데모 블록을 거치지 않은 세이브에서 일반 플레이 내내 버튼이 죽어 있게 된다.
		bool heartBetTutorialLocked = IsTutorialPlaying() && !robin.demoSeen[DEMO_TUTORIAL_HEARTBET];

		//하트베팅 버튼
		//터치영역과 같은 사각형으로 눌림을 물어보고, 한가운데를 붙잡아 배율만 준다.
		float btnPress = GetButtonPressScale(xOffset + barP->x, barP->y,
			(float)HEARTBUTTONWIDTH * barP->zoom, (float)HEARTBUTTONHEIGHT * barP->zoom);
		float btnGapX = (float)HEARTBUTTONWIDTH * barP->zoom * (btnPress - 1.0f) / 2;
		float btnGapY = (float)HEARTBUTTONHEIGHT * barP->zoom * (btnPress - 1.0f) / 2;

		DrawHeartButton(betHeart[bet], xOffset + barP->x - btnGapX, barP->y + btnGapY, barP->zoom * btnPress, (IsTouchFuncEnabled(TOUCH_FUNC_HEARTAMOUNT) && !heartBetTutorialLocked ? true : false), true);

		if (IsTouchFuncEnabled(TOUCH_FUNC_HEARTAMOUNT) && !heartBetTutorialLocked)
			SetRectPoint(xOffset + barP->x, barP->y, (float)HEARTBUTTONWIDTH * barP->zoom, (float)HEARTBUTTONHEIGHT * barP->zoom, TOUCH_FUNC_HEARTAMOUNT);
	}

		//예전에는 여기서 노란 테두리를 펄스로 그려 베팅 버튼을 강조했다. 지금은 안내 대사가
		//스팟라이트 + 손으로 같은 일을 하므로(Demo_Talk의 GetTutorialTalkTarget 경로) 뺐다.
		//테두리만 남으면 "웬 사각형이 혼자 움직이는" 것으로 보인다.
		break;
	case BAR_PLAY://플레이 버튼
	{
			//공격 버튼
			//터치영역과 같은 사각형으로 눌림을 물어보고, 한가운데를 붙잡아 배율만 준다.
			float btnPress = GetButtonPressScale(xOffset + barP->x, barP->y,
				(float)ATTACKBUTTONWIDTH * barP->zoom, (float)ATTACKBUTTONHEIGHT * barP->zoom);
			float btnGapX = (float)ATTACKBUTTONWIDTH * barP->zoom * (btnPress - 1.0f) / 2;
			float btnGapY = (float)ATTACKBUTTONHEIGHT * barP->zoom * (btnPress - 1.0f) / 2;

			DrawAttackButton(count, xOffset + barP->x - btnGapX, barP->y + btnGapY, barP->zoom * btnPress, IsTouchFuncEnabled(TOUCH_FUNC_ATTACK), false, rectContainsTouchPoint(barP->x + (float)(HEARTBARWIDTH + 8 * _2X) * barP->zoom, barP->y + (float)6 * _2X * barP->zoom, (float)ATTACKBUTTONWIDTH * 2.0f * zoom, (float)ATTACKBUTTONHEIGHT * 2.0f * barP->zoom) * touchFrame);
		if (touchDisable == false)
			SetRectPoint(xOffset + barP->x, barP->y, (float)ATTACKBUTTONWIDTH * barP->zoom, (float)ATTACKBUTTONHEIGHT * barP->zoom, TOUCH_FUNC_ATTACK);

		break;
	}
	case BAR_JOYSTICK:
		if (joyReturning) {
			joyDx += (0.0f - joyDx) * joyReturnSpeed;
			joyDy += (0.0f - joyDy) * joyReturnSpeed;

			if (Abs(joyDx) < 0.5f && Abs(joyDy) < 0.5f) {
				joyDx = 0;
				joyDy = 0;
				joyReturning = false;
			}
		}

		JoyStickDraw(count, xOffset + barP->x, barP->y, joyDx, joyDy, joyPower, barP->zoom, IsTouchFuncEnabled(TOUCH_FUNC_MOVE), false, rectContainsTouchPoint(barP->x + (float)(HEARTBARWIDTH + 8 * _2X) * barP->zoom, barP->y + (float)6 * _2X * barP->zoom, (float)ATTACKBUTTONWIDTH * 2.0f * zoom, (float)ATTACKBUTTONHEIGHT * 2.0f * barP->zoom) * touchFrame);
		if (touchDisable == false)
			SetRectPoint(xOffset + barP->x - (float)(108 / 2) * barP->zoom, barP->y + (float)(93 / 2) * barP->zoom, (float)108 * barP->zoom, (float)93 * barP->zoom, TOUCH_FUNC_MOVE);
		break;
	case BAR_JUMP:
	{
			//점프 버튼
			//터치영역과 같은 사각형으로 눌림을 물어보고, 한가운데를 붙잡아 배율만 준다.
			float btnPress = GetButtonPressScale(xOffset + barP->x, barP->y,
				(float)ATTACKBUTTONWIDTH * barP->zoom, (float)ATTACKBUTTONHEIGHT * barP->zoom);
			float btnGapX = (float)ATTACKBUTTONWIDTH * barP->zoom * (btnPress - 1.0f) / 2;
			float btnGapY = (float)ATTACKBUTTONHEIGHT * barP->zoom * (btnPress - 1.0f) / 2;

			DrawJumpButton(count, xOffset + barP->x - btnGapX, barP->y + btnGapY, barP->zoom * btnPress, IsTouchFuncEnabled(TOUCH_FUNC_JUMP), false, rectContainsTouchPoint(barP->x + (float)(HEARTBARWIDTH + 8 * _2X) * barP->zoom, barP->y + (float)6 * _2X * barP->zoom, (float)ATTACKBUTTONWIDTH * 2.0f * zoom, (float)ATTACKBUTTONHEIGHT * 2.0f * barP->zoom) * touchFrame);
		if (touchDisable == false)
			SetRectPoint(xOffset + barP->x, barP->y, (float)ATTACKBUTTONWIDTH * barP->zoom, (float)ATTACKBUTTONHEIGHT * barP->zoom, TOUCH_FUNC_JUMP);
		break;
	}
	case BAR_BATTLECOIN:
		if (count < 0)
			count = 0;
		if (count > 0) {
			BattleCoinBarDraw(count, barP->icon + (barP->iconFrame > 0 ? barP->aniFrame % barP->iconFrame : 0), xOffset + barP->x, barP->y, false, zoom);
		}
//		if (barP->addView)

		break;
	case BAR_CASTLE:
		DrawBarIcon(barP->drawFunc, xOffset + barP->x - (float)(MAINMENU_X / 2) * zoom, barP->y + (float)(MAINMENU_Y / 2) * zoom, zoom);
		SetRectPoint(xOffset + barP->x - (float)(MAINMENU_X / 2) * zoom, barP->y + (float)(MAINMENU_Y / 2 + 12 * _2X) * zoom, (float)(MAINMENU_X)*zoom, (float)(MAINMENU_Y + 16 * _2X) * zoom, TOUCH_FUNC_POPUP_CASTLEMENU);
		break;
	case BAR_CREW:
		DrawBarIcon(barP->drawFunc, xOffset + barP->x - (float)(MAINMENU_X / 2) * zoom, barP->y + (float)(MAINMENU_Y / 2) * zoom, zoom);
		SetRectPoint(xOffset + barP->x - (float)(MAINMENU_X / 2) * zoom, barP->y + (float)(MAINMENU_Y / 2 + 12 * _2X) * zoom, (float)(MAINMENU_X)*zoom, (float)(MAINMENU_Y + 16 * _2X) * zoom, TOUCH_FUNC_POPUP_CREWLIST);
		break;
	case BAR_MEDAL:
		DrawRouletteNumIcon(count, barP->icon, xOffset + barP->x, barP->y, true, zoom * 2, CENTER);
		break;
	case BAR_ENEMYUSER:
		EnemyUserProfileDraw(&enemyHouse, xOffset + barP->x, barP->y + (float)RAIDGOLDBARHEIGHT / 2 * zoom, zoom);
		SetRectPoint(xOffset + barP->x - (float)160 * _2X / 2 * zoom, barP->y + (float)32 * _2X * zoom, (float)160 * _2X * zoom, (float)48 * _2X * zoom, TOUCH_FUNC_GOTOHOUSE);
		break;
	case BAR_ENEMYUSER_BOX:
		EnemyUserProfileDraw_Box(&enemyHouse, xOffset + barP->x - (float)RAIDGOLDBARWIDTH / 2 * zoom, barP->y + (float)RAIDGOLDBARHEIGHT / 2 * zoom, zoom);
		break;
	case BAR_DAILYQUEST:
		DrawImage(40 * _2X, 40 * _2X, 40 * _2X * MENUICON_DAILYQUEST, 0 * _2X, xOffset + barP->x - (float)REWARDCARDSIZE_X / 2 * zoom, barP->y + (float)REWARDCARDSIZE_Y / 2 * zoom, false, false, false, false, 32, 1, sprite[MENUICON_IMG], MENUICON_IMG);
		MemRectRound(xOffset + barP->x - (float)MAINMENU_X / 2 * zoom, barP->y + (float)(MAINMENU_Y / 2 - MAINMENU_Y + TSIZE) * zoom, (float)MAINMENU_X * zoom, (float)14 * _2X * zoom, COLOR_NAVY, 1 * _2X);
		CenterText(TEXT_DAILYQUEST, xOffset + barP->x, barP->y + (float)(MAINMENU_Y / 2 - MAINMENU_Y + TSIZE - 2 * _2X) * zoom, 0.8f * zoom);
		SetRectPoint(xOffset + barP->x - (float)MAINMENU_X / 2 * zoom, barP->y + (float)MAINMENU_Y / 2 * zoom, (float)MAINMENU_X * zoom, (float)MAINMENU_Y * zoom, TOUCH_FUNC_DAILYQUEST);
		break;
	case BAR_CREWUPGRADE:
		DrawImage(40 * _2X, 40 * _2X, 40 * _2X * MENUICON_GUILD, 0 * _2X, xOffset + barP->x - (float)REWARDCARDSIZE_X / 2 * zoom, barP->y + (float)REWARDCARDSIZE_Y / 2 * zoom, false, false, false, false, 32, 1, sprite[MENUICON_IMG], MENUICON_IMG);
		MemRectRound(xOffset + barP->x - (float)MAINMENU_X / 2 * zoom, barP->y + (float)(MAINMENU_Y / 2 - MAINMENU_Y + TSIZE) * zoom, (float)MAINMENU_X * zoom, (float)14 * _2X * zoom, COLOR_NAVY, 1 * _2X);
		CenterText(TEXT_BORDERGUARD, xOffset + barP->x, barP->y + (float)(MAINMENU_Y / 2 - MAINMENU_Y + TSIZE - 2 * _2X) * zoom, 0.8f * zoom);
		SetRectPoint(xOffset + barP->x - (float)MAINMENU_X / 2 * zoom, barP->y + (float)MAINMENU_Y / 2 * zoom, (float)MAINMENU_X * zoom, (float)MAINMENU_Y * zoom, TOUCH_FUNC_POPUP_CREWUPGRADE);
		break;
	case BAR_EQUIP:
		DrawBarIcon(barP->drawFunc, xOffset + barP->x - (float)(MAINMENU_X / 2) * zoom, barP->y + (float)(MAINMENU_Y / 2) * zoom, zoom);
		SetRectPoint(xOffset + barP->x - (float)(MAINMENU_X / 2) * zoom, barP->y + (float)(MAINMENU_Y / 2 + 12 * _2X) * zoom, (float)(MAINMENU_X)*zoom, (float)(MAINMENU_Y + 16 * _2X) * zoom, TOUCH_FUNC_COLLECTIONS);
		break;
	case BAR_MAINSHOP:
		DrawBarIcon(barP->drawFunc, xOffset + barP->x - (float)(MAINMENU_X / 2) * zoom, barP->y + (float)(MAINMENU_Y / 2) * zoom, zoom);
		SetRectPoint(xOffset + barP->x - (float)(MAINMENU_X / 2) * zoom, barP->y + (float)(MAINMENU_Y / 2 + 12 * _2X) * zoom, (float)(MAINMENU_X)*zoom, (float)(MAINMENU_Y + 16 * _2X) * zoom, TOUCH_FUNC_SHOP);
		break;
	case BAR_FRIENDS:
		DrawImage(40 * _2X, 40 * _2X, 40 * _2X * MENUICON_HERO, 0 * _2X, xOffset + barP->x - (float)REWARDCARDSIZE_X / 2 * zoom, barP->y + (float)REWARDCARDSIZE_Y / 2 * zoom, false, false, false, false, 32, 1, sprite[MENUICON_IMG], MENUICON_IMG);
		MemRectRound(xOffset + barP->x - (float)MAINMENU_X / 2 * zoom, barP->y + (float)(MAINMENU_Y / 2 - MAINMENU_Y + TSIZE) * zoom, (float)MAINMENU_X * zoom, (float)14 * _2X * zoom, COLOR_NAVY, 1 * _2X);
		CenterText(TEXT_MENU_FRIENDS, xOffset + barP->x, barP->y + (float)(MAINMENU_Y / 2 - MAINMENU_Y + TSIZE - 2 * _2X) * zoom, 0.8f * zoom);
		SetRectPoint(xOffset + barP->x - (float)MAINMENU_X / 2 * zoom, barP->y + (float)MAINMENU_Y / 2 * zoom, (float)MAINMENU_X * zoom, (float)MAINMENU_Y * zoom, TOUCH_FUNC_FRIENDS);
		break;
	case BAR_NPC:
		DrawImage(207, 33, 0, 953, xOffset + barP->x + shakePosX[effect.hpShake], barP->y - 12 * _2X + shakePosY[effect.hpShake], false, false, false, false, false, 2.0f, sprite[THEATER_IMG], THEATER_IMG);
		EnemyProfileDraw(xOffset + barP->x + (float)(4 * _2X) * zoom, barP->y - (float)(14 * _2X) * zoom, ao[ENEMY].type, zoom, false, false);

		//채워지는 폭. HpBarDraw()와 같은 식이다. 예전에는 val을 대입하는 줄이 아예
		//없어서 초기화도 안 된 값이 그대로 폭으로 들어갔다.
		val = barP->max > 0
			? (long long)((float)(HPBARWIDTH)*zoom * count / barP->max)
			: 0;

		MemRect(xOffset + barP->x + (float)(40 * _2X + shakePosX[effect.hpShake]) * zoom, barP->y + (float)(-20 * _2X + shakePosY[effect.hpShake]) * zoom, val, (float)(HPBARHEIGHT)*zoom, ENEMYHPBARCOLOR);

		DrawNum(count, xOffset + barP->x + (float)(30 * _2X + HPBARWIDTH + shakePosX[effect.hpShake]) * zoom, barP->y + (float)(-20 * _2X + shakePosY[effect.hpShake] - 2 * _2X) * zoom, NUM_FONT_NORMAL, RIGHT, 0, count >= 0 ? false : MINUS, true, zoom, true);

		DrawIcon(barP->icon + frame % GOLDICONFRAME, xOffset + barP->x + (float)(30 * _2X + HPBARWIDTH - GetNumDx(count, 0, NUM_FONT_NORMAL, 0, true, zoom, true) - 20 * _2X + shakePosX[effect.hpShake]) * zoom, barP->y + (float)(-20 * _2X + shakePosY[effect.hpShake]) * zoom, zoom, false, false, false, true);

		if (attackSequence != ATTACKSEQUENCE_REWARD) {

			DrawRewardCard(ITEM_BOX, goldQuestBox[robin.gameEvent[GetEventMenuIdx(EVENTTYPE_BOSSRAID)].barStatus * BOSSRAIDSIZE + robin.gameEvent[GetEventMenuIdx(EVENTTYPE_BOSSRAID)].barFrame], false, 1, 1, xOffset + barP->x + (float)(HPBARWIDTH + 32 * _2X) * zoom, barP->y - (float)(8 * _2X) * zoom, false, zoom, false, false, true, false, false, true, 0);
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
		QuestDraw(xOffset + barP->x, barP->y, barP->icon, robin.questCnt - (robin.subQuest == 0 ? 0 : questRequestItemCnt[robin.quest * TOTALSUBQUEST + robin.subQuest - 1]), questRequestItemCnt[robin.quest * TOTALSUBQUEST + robin.subQuest] - (robin.subQuest == 0 ? 0 : questRequestItemCnt[robin.quest * TOTALSUBQUEST + robin.subQuest - 1]), false, false, barP->enemyIcon, barP->rewardIcon, false, zoom);
		break;
	case BAR_RAIDGOLD:
		DrawRouletteNumIcon(count, barP->icon, xOffset + barP->x, barP->y, true, CENTER, zoom * 1.5f);
		break;
	case BAR_RAIDCOIN:
		DrawRouletteNumIcon(count, barP->icon, xOffset + barP->x, barP->y, true, CENTER, zoom * 1.5f);
		break;
	case BAR_COMBATPOWER:
	case BAR_COMBATPOWERALL:
		DrawCombatPower(count, barP->icon, xOffset + barP->x, barP->y, false, zoom);
		break;
	case BAR_STAR:
		if (count < 0)
			count = 0;

		StarBarDraw(count, barP->icon + (barP->iconFrame > 0 ? barP->aniFrame % barP->iconFrame : 0), xOffset + barP->x, barP->y, false, zoom);

		if (barP->addView)
			DrawNum2AutoSpaceing(barP->addViewSum, xOffset + barP->x + (float)(GOLDBARWIDTH - 4 * _2X) * zoom, barP->y - (float)GOLDBARHEIGHT * zoom - (float)(1 * _2X) * zoom, RIGHT, false, barP->addViewSum >= 0 ? PLUS : MINUS, GOLDBARWIDTH, true, 0.3f * zoom, false, true);
		break;
	case BAR_STAGEPROGRESS:
		StageProgressDraw(xOffset + barP->x, barP->y, count, barP->countFrame, zoom);
		break;
	case BAR_REMAINEDTURN:
		RemainedTurnDraw(xOffset + barP->x, barP->y, count, barP->countFrame, zoom);
		break;
		
	// 새로운 룰렛 시스템 UI
	case BAR_DAY:
		DayBarDraw(DAYS3 - (GetCurrentTimeMs() - robin.startTime), xOffset + barP->x, barP->y, zoom);
		SetRectPoint(xOffset + barP->x - 32 * _2X, STATUSWIN_Y + (rh - 4) * TSIZE - ao[ROBIN].ny - ry + 40 * _2X, 64 * _2X, 64 * _2X, TOUCH_FUNC_GOTOBATTLE);
		break;
	case BAR_WAVE:
		WaveBarDraw(count, barP->max, xOffset + barP->x, barP->y, zoom);
		break;
		
	case BAR_INVENTORY:
	case BAR_INVENTORY + 1:
	case BAR_INVENTORY + 2:
		InventoryDraw(&ao[barP->owner], xOffset + barP->x, barP->y, zoom);
		break;
	case BAR_SKILL:
	case BAR_SKILL + 1:
	case BAR_SKILL + 2:
		DrawQuick(&ao[barP->owner], xOffset + barP->x, barP->y, true, zoom);
		break;
	}


	if (barP->aniFrame > 0) {
		if (barP->aniFrame == barP->countFrame) {
			BarAddStop(barP);
		}
		else
			barP->aniFrame++;
	}
}

void BarAddStop(BAR * barP)
{
	barP->aniFrame = barP->countFrame = 0;
	barP->count += barP->add;
	barP->add = 0;
	barP->addView = false;
	barP->addViewSum = 0;

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

	ao[NEUTRAL].status = BOXSTATUS_CLOSED;
}


void BossHpBarDraw(long long count, long long max, int x, int y, float zoom)
{
	float width = StringWidth(textId[TEXT_STAGE], zoom) + (float)(4 * _2X) * zoom + GetNumDx(robin.stage + 1, false, NUM_FONT_NORMAL, false, false, zoom, false) + GetNumDx(robin.room + 1, MINUS, NUM_FONT_NORMAL, false, false, zoom, false);
	long long betCnt = bossGold[robin.stage] * GetBetHeart(ao[PLAYER].equip[EQUIP_WEAPON].detail, ao[PLAYER].equip[EQUIP_WEAPON].grade, bet);
	int obj = ENEMY + GetEnemyBarIdx(ENEMY);

	//count = 100;
	//max = 200;
	DrawRoundBar(x - (float)BOSSHPBARWIDTH / 2 * zoom, y + (float)BOSSHPBARHEIGHT * zoom, (float)(count) / (float)max, ROUNDBAR_BIG, BARCOLOR_RED, false, zoom);
	
	if (count > 0)
		DrawNum2AutoSpaceing(count, x + (float)(BOSSHPBARWIDTH / 2 - 12 * _2X) * zoom, y + (float)(BOSSHPBARHEIGHT / 2 + 12 * _2X) * zoom, RIGHT, false, false, (float)(BOSSHPBARWIDTH - 16 * _2X) * zoom, true, 0.6f * zoom, false, 2 * _2X);

	DevilHeartDraw(x - (float)(BOSSHPBARWIDTH / 2) * zoom, y + (float)0 * _2X * zoom, 2.5f * zoom);



}

void MedalBarDraw(int x, int y, long long amount, bool ani, float zoom)
{
	if (ani) {
		MemRect(x - (float)(2 * _2X) * zoom, y + (float)(2 * _2X) * zoom, (float)(MEDALBARWIDTH + 4 * _2X) * zoom, (float)(MEDALBARHEIGHT + 4 * _2X) * zoom, itemColor[frame % 6]);
	}

	if (medalFrame > 0 && medalFrame % 2 == 0 && ani == true)
		DrawIcon(ICON_MEDAL, x, y + (float)(1 * _2X) * zoom, (float)2 * zoom, false, false, false, true);
	else
		DrawIcon(ICON_MEDAL, x + (float)(8 * _2X) * zoom, y - (float)(9 * _2X) * zoom, zoom, false, false, false, true);

	DrawNum(amount, x + (float)(TSIZE * 5 + 8 * _2X) * zoom, y - (float)(5 * _2X * 2) * zoom, NUM_FONT_NORMAL, RIGHT, false, false, true, zoom, true);
	if (medalFrame > 0 && ani == true)
		medalFrame--;
}

void PvpEventBarDraw(GAMEEVENT* gEvent, int x, int y, int icon, int count, int max, bool animation, bool questAni, float zoom)
{
	int i, j;

	float w = (float)PVPQUESTBARWIDTH * zoom;
	float h = (float)PVPQUESTBARHEIGHT * zoom;
	float iconZoom = EQUIPZOOM;

	float xPos;
	int moveSpeed = 4 * _2X * 2 / MOTIONDIV;
	long long start, end;

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
		MemRect(x - (float)(2 * _2X) * zoom, y + (float)(2 * _2X) * zoom, w + (float)(4 * _2X) * zoom, h + (float)(4 * _2X) * zoom, itemColor[frame % 6]);

	//TEST
	//count = 70;
	//max = 100;
	//여기야
	if ((float)(PVPQUESTBARWIDTH - 12 * _2X) * start / end + gEvent->barFrame < (float)(PVPQUESTBARWIDTH - 12 * _2X) * (start + 1) / end)
		MemRect(x + (float)(6 * _2X) * zoom, y - (float)(7 * _2X) * zoom, (float)((PVPQUESTBARWIDTH - 12 * _2X) * start / end + gEvent->barFrame) * zoom, (float)(PVPQUESTBARHEIGHT - 14 * _2X) * zoom, COLOR_REALYELLOW);
	else
		MemRect(x + (float)(6 * _2X) * zoom, y - (float)(7 * _2X) * zoom, (float)(PVPQUESTBARWIDTH - 12 * _2X) * zoom * start / end, (float)(PVPQUESTBARHEIGHT - 14 * _2X) * zoom, COLOR_REALYELLOW);

	DrawIcon(icon, x + (float)(-ITEMICONSIZE) * zoom * iconZoom, y + (float)(2 * _2X) * zoom * iconZoom, zoom * iconZoom, COLOR_BROWN, animation, true, true);

	j = 0;
	for (i = 0; i < TOTALPVPDETAILREQUEST; i++) {
		if (count >= pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i]) {
			j++;
			break;
		}
	}
#ifdef GUIDELINE
	for (i = 0; i < TOTALPVPDETAILREQUEST; i++) {
		MemRect(x + (float)(6 * _2X) * zoom + (float)(PVPQUESTBARWIDTH - 12 * _2X) * pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i] / max, y - (float)(7 * _2X) * zoom, (float)(1 * _2X) * zoom, (float)(PVPQUESTBARHEIGHT - 14 * _2X) * zoom, COLOR_REALRED);
		DrawNum(pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i], x + (float)(6 * _2X) * zoom + (float)(PVPQUESTBARWIDTH - 12 * _2X) * pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i] / max, y - (float)(7 * _2X + PVPQUESTBARHEIGHT) * zoom, NUM_FONT_NORMAL, CENTER, false, false, true, zoom, true);
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
				DrawRewardCard(pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 0], pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 1], pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 2], 0, pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 3], x + xPos - (float)REWARDCARDSIZE_X / 2 * zoom * iconZoom * 0.6f, y + (float)8 * _2X * zoom, false, 0.6f * zoom * iconZoom, false, false, true, false, false, true, 0);
				pvpRewardPosition[i][0] = x + xPos + (float)(ITEMICONSIZE / 2) * 0.6f * zoom * iconZoom;
				pvpRewardPosition[i][1] = y - (float)(2 * _2X) * zoom * iconZoom - (float)(ITEMICONSIZE / 2) * zoom * iconZoom;

				//TEST
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
				DrawRewardCard(pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 0], pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 1], pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 2], 0, pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + i) * PVPQUESTDATASIZE + 3], x + xPos - (float)REWARDCARDSIZE_X / 2 * zoom * iconZoom * 0.6f, y + (float)8 * _2X * zoom, false, 0.6f * zoom * iconZoom, false, false, true, false, false, true, 0);

				pvpRewardPosition[i][0] = x + xPos + (float)(ITEMICONSIZE / 2) * 0.6f * zoom * iconZoom;
				pvpRewardPosition[i][1] = y - (float)(2 * _2X) * zoom * iconZoom - (float)(ITEMICONSIZE / 2) * zoom * iconZoom;

			}
		}
	}

	UnSectionClip(false);

	if (gEvent->barStatus == EVENT_BAR_REWARDGET && gEvent->frame == FPS) {
		//gEvent->
	}
}

void DevilHeartDraw(int x, int y, float zoom)
{

	float defaultAngle;
	float radius = (float)ROULETTERADIUS * zoom;//반경

	if (curtainFrame == 0 && areaFrame == 0 && GetCardMarkCnt() == maxRouletteCnt && arenaStatus == STATUS_READY)
		arenaStatus = STATUS_PLAY;

	//defaultAngle = 360 / maxRouletteCnt;
	defaultAngle = 360 / 6;

	switch (attackSequence) {
	default:
		DrawCmfDetail(CMF_NPC_HEART, PO_C122_HEART, x, y, RIGHT, zoom, false, false);
		break;
	}


}

void GoldBarDraw(long long count, int icon, int x, int y, int alpha, float zoom)
{
	DrawRoundBar(x + (float)0 * zoom, y, 1.0f, ROUNDBAR_BIG, BARCOLOR_YELLOW, alpha, 0.5f * zoom);
	DrawIcon(icon, x + (float)(6 * _2X) * zoom, y - (float)(6 * _2X) * zoom, 1.2f * zoom, COLOR_BROWN, false, false, 1);
#ifdef NUMTTF
	DrawBigNumTTF(count, x + (float)(GOLDBARWIDTH - 10 * _2X) * zoom, y - (float)(5 * _2X * 2) * zoom, NUM_FONT_NORMAL, RIGHT, false, false, (float)(GOLDBARWIDTH - ITEMICONSIZE - 0 * _2X) * zoom, true, zoom, true);
#else
	DrawNum2AutoSpaceing(count, x + (float)(GOLDBARWIDTH - 7 * _2X) * zoom, y - (float)(10 * _2X) * zoom, RIGHT, false, false, (float)(GOLDBARWIDTH - ITEMICONSIZE * 1.2f - 13 * _2X) * zoom, true, NUM2ZOOM * 1.2f * zoom, true, true);
#endif
}

void BattleCoinBarDraw(long long count, int icon, int x, int y, int alpha, float zoom)
{
#ifdef NUMTTF
	DrawBigNumTTF(count, x + (float)(GOLDBARWIDTH - 10 * _2X) * zoom, y - (float)(5 * _2X * 2) * zoom, NUM_FONT_NORMAL, RIGHT, false, false, (float)(GOLDBARWIDTH - ITEMICONSIZE - 0 * _2X) * zoom, true, zoom, true);
#else
	DrawGoldNum(count, x, y, CENTER, false, PLUS, true, zoom);
#endif
}

void ExpBarWideDraw(int lv, long long count, int x, int y, float zoom)
{
	//count = 10;
	//count = 33960000;

	MemRect(x + (float)(ITEMICONSIZE * 1.5f + 2 * _2X + 6 * _2X) * zoom, y - (float)(7 * _2X) * zoom, Min((float)(CROWNBARWIDTH - 1.5f * ITEMICONSIZE - 28 * _2X) * zoom, (float)(CROWNBARWIDTH_WIDE - 1.5f * ITEMICONSIZE - 28 * _2X) * ((float)(count - NextExp(lv - 1)) / (float)(NextExp(lv) - NextExp(lv - 1))) * zoom), (float)(CROWNBARHEIGHT - 14 * _2X) * zoom, COLOR_REALYELLOW);

	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%ld / %ld", (long)(count - NextExp(lv - 1)), (long)(NextExp(lv) - NextExp(lv - 1)));
	//sprintf(tempStr, "%ld / %ld", 80, 100);
	CenterTextStr(tempStr, x + (float)(CROWNBARWIDTH_WIDE / 2 + 1.5f * ITEMICONSIZE - 24 * _2X) * zoom, y - (float)(4 * _2X + 6 * _2X) * zoom, zoom);

	DrawStarNum(ICON_CROWN, lv + 1, x + (float)2 * _2X * zoom, y - (float)4 * _2X * zoom, 1.5f * zoom);
	DrawLevelUpCard(levelUpReward[lv], lv, false, x + (float)(CROWNBARWIDTH_WIDE + 1.5f * ITEMICONSIZE - 4 * _2X - 48 * _2X) * zoom, y - (float)(0 * _2X) * zoom, 0.4f * zoom);
}

void HeartBarDraw(int count, int max, int x, int y, int alpha, float zoom)
{
	DrawRoundBar(x, y, (float)Min(count, max) / max, ROUNDBAR_BIG, BARCOLOR_RED, alpha, 0.5f * zoom);

	DrawIcon(ICON_HEART, x + (float)0 * _2X * zoom, y - (float)0 * _2X * zoom, 1.0f * zoom, COLOR_WHITE, false, false, 3.0f);
#ifdef NUMTTF
	DrawBigNumTTF(count, x + (float)(GOLDBARWIDTH - 10 * _2X) * zoom, y - (float)(5 * _2X * 2) * zoom, NUM_FONT_NORMAL, RIGHT, false, false, (float)(GOLDBARWIDTH - ITEMICONSIZE - 0 * _2X) * zoom, true, zoom, true);
#else
	SetFontColor(COLOR_WHITE);
	DrawSlashNum(count, max, x + (float)(HEARTBARWIDTH / 2 + 2 * _2X) * zoom, y - (float)(10 * _2X) * zoom, HEARTBARWIDTH, 1.2f * zoom);
	SetFontColor(false);
#endif
}

void ExpBarDraw(int lv, long long count, int x, int y, int alpha, float zoom)
{
	DrawRoundBar(x + (float)0 * zoom, y, ((float)(count - NextExp(lv - 1)) / (float)(NextExp(lv) - NextExp(lv - 1))), ROUNDBAR_SMALL, BARCOLOR_PURPLE, alpha, 0.5f * zoom);
#ifdef NUMTTF
	DrawBigNumTTF(count, x + (float)(GOLDBARWIDTH - 10 * _2X) * zoom, y - (float)(5 * _2X * 2) * zoom, NUM_FONT_NORMAL, RIGHT, false, false, (float)(GOLDBARWIDTH - ITEMICONSIZE - 0 * _2X) * zoom, true, zoom, true);
#else
	DrawNum2AutoSpaceing(count, x + (float)(CROWNBARWIDTH - 7 * _2X) * zoom, y - (float)(10 * _2X) * zoom, RIGHT, false, false, (float)(CROWNBARWIDTH - ITEMICONSIZE * 1.2f - 13 * _2X) * zoom, true, NUM2ZOOM * 1.2f * zoom, true, true);
#endif

	DrawStarNum(ICON_CROWN, lv + 1, x + (float)6 * _2X * zoom, y - (float)6 * _2X * zoom, 1.2f * zoom);

}

void ShieldBarDraw(long long count, long long max, int x, int y, float zoom, int hpColor)
{
	long long val;
	val = (float)(SIMPLEHPBARWIDTH)*zoom * count / max;

	MemRect(xOffset + x + (float)shakePosX[effect.hpShake] * zoom, y + (float)shakePosY[effect.hpShake] * zoom, (float)(SIMPLEHPBARWIDTH + 2 * _2X) * zoom, (float)(SIMPLEHPBARHEIGHT + 2 * _2X) * zoom, COLOR_NAVY);
	MemRect(xOffset + x + (float)(1 * _2X + shakePosX[effect.hpShake]) * zoom, y + (float)(-1 * _2X + shakePosY[effect.hpShake]) * zoom, val, (float)(SIMPLEHPBARHEIGHT)*zoom, hpColor);
	CenterText(TEXT_SHIELD, xOffset + x + (float)(SIMPLEHPBARWIDTH / 2 + shakePosX[effect.hpShake]) * zoom, y + (float)(shakePosY[effect.hpShake] + 12 * _2X) * zoom, zoom);

	//상태이상이 걸려
	if (effect.hpShake) {
		effect.hpShake++;

		if (effect.hpShake == 5) {
			effect.hpShake = 0;
		}
	}
}

void SimpleHpBarDraw(long long count, long long max, int x, int y, float zoom, int hpColor)
{
	long long val;
	val = (float)(SIMPLEHPBARWIDTH)*zoom * count / max;

	MemRect(x + (float)shakePosX[effect.hpShake] * zoom, y + (float)shakePosY[effect.hpShake] * zoom, (float)(SIMPLEHPBARWIDTH + 2 * _2X) * zoom, (float)(SIMPLEHPBARHEIGHT + 2 * _2X) * zoom, COLOR_NAVY);
	MemRect(x + (float)(1 * _2X + shakePosX[effect.hpShake]) * zoom, y + (float)(-1 * _2X + shakePosY[effect.hpShake]) * zoom, val, (float)(SIMPLEHPBARHEIGHT)*zoom, hpColor);
	DrawNum2AutoSpaceing(count, x + (float)SIMPLEHPBARWIDTH * zoom / 2, y + (float)shakePosY[effect.hpShake] * zoom + (float)-(SIMPLEHPBARHEIGHT + 3 * _2X) * zoom, CENTER, 0, false, (float)HPBARWIDTH * zoom, true, NUM2ZOOM * 0.9f * zoom, false, true);

	//상태이상이 걸려
	if (effect.hpShake) {
		effect.hpShake++;

		if (effect.hpShake == 5) {
			effect.hpShake = 0;
		}
	}
}

void HpBarDraw(int type, long long count, long long max, int x, int y, float zoom)
{
	long long val;
	int obj = ENEMY + GetEnemyBarIdx(ENEMY);

	val = (float)(HPBARWIDTH - 4 * _2X) * zoom * count / max;

	if (type <= MAXX) {
		DrawFrame(xOffset + x + (float)26 * _2X * zoom + (float)shakePosX[effect.hpShake] * zoom, y - (float)(1 * _2X + shakePosY[effect.hpShake]) * zoom, (float)HPBARWIDTH * zoom, (float)(HPBARHEIGHT)*zoom, FRAME_SHOPBALLOON);
		MemRect(xOffset + x + (float)26 * _2X * zoom + (float)(1 * _2X + shakePosX[effect.hpShake]) * zoom, y + (float)(-3 * _2X + shakePosY[effect.hpShake]) * zoom, val, (float)(HPBARHEIGHT - 4 * _2X) * zoom, 0x33FF00);

		DrawBigNum(count, xOffset + x + (float)26 * _2X * zoom + (float)(HPBARWIDTH + shakePosX[effect.hpShake] - 4 * _2X) * zoom, y + (float)(-3 * _2X + shakePosY[effect.hpShake]) * zoom, NUM_FONT_NORMAL, RIGHT, 0, count >= 0 ? false : MINUS, (float)(HPBARWIDTH - ITEMICONSIZE) * zoom, true, zoom, false);

		EnemyProfileDraw(xOffset + x, y + (float)0 * _2X * zoom, type, false, false, 0.8f * zoom);
	}
	else {
		DrawFrame(xOffset + x + (float)shakePosX[effect.hpShake] * zoom, y - (float)(1 * _2X + shakePosY[effect.hpShake]) * zoom, (float)HPBARWIDTH * zoom, (float)(HPBARHEIGHT)*zoom, FRAME_SHOPBALLOON);
		MemRect(xOffset + x + (float)(2 * _2X + shakePosX[effect.hpShake]) * zoom, y + (float)(-3 * _2X + shakePosY[effect.hpShake]) * zoom, val, (float)(HPBARHEIGHT - 4 * _2X) * zoom, COLOR_VERYRED);

		DrawBigNum(count, xOffset + x + (float)4 * _2X * zoom + (float)(shakePosX[effect.hpShake]) * zoom, y + (float)(-3 * _2X + shakePosY[effect.hpShake]) * zoom, NUM_FONT_NORMAL, LEFT, 0, count >= 0 ? false : MINUS, (float)(HPBARWIDTH - ITEMICONSIZE) * zoom, true, zoom, false);

		EnemyProfileDraw(xOffset + x + (float)(HPBARWIDTH - 4 * _2X) * zoom, y + (float)0 * _2X * zoom, type, false, false, 0.8f * zoom);
	}

	if (effect.hpShake) {
		effect.hpShake++;

		if (effect.hpShake == 5) {
			effect.hpShake = 0;
		}
	}
}

// ============================================================================
// Day 표시 함수 - 강조된 Day 카운터
// ============================================================================
void DayBarDraw(int day, int x, int y, float zoom)
{
	float emphasisScale = (1.0f + sinf(frame * 0.05f) * 0.05f) * zoom;
	//emphasisScale = 1.3f * zoom;

	y = STATUSWIN_Y + (rh - 4) * TSIZE - ao[ROBIN].ny - ry;

	DrawNeutral(OBJ_BLACKHOLE0 + Abs(15 - frame) % 15, x, y + (float)20 * zoom, 0, emphasisScale * 2.0f);

	DrawCmfDetailShadow(enemyData[boss[robin.stage] * ENEMYDATASIZE + ENEMYDATA_CMF], crewPos[boss[robin.stage] * 5 + 0] + (frame / 4 % crewPos[boss[robin.stage] * 5 + 1]), x, y, LEFT, emphasisScale);
	DrawRemainTime(x, y - (float)8 * _2X * zoom, day, CENTER, emphasisScale * 2.0f);
	
	DrawGoldAlpha(x, y + (float)132 * zoom, ALPHA_BOSS, FONT_GOLD_LARGE, zoom, CENTER, false, false);

}

// ============================================================================
// Life(수명) 표시 함수 - 하트 아이콘
// ============================================================================
void WaveBarDraw(int life, int maxLife, int x, int y, float zoom)
{
	float emphasisScale = (1.0f + sinf(frame * 0.05f) * 0.05f) * zoom;
	//emphasisScale = 1.3f * zoom;

	//y = STATUSWIN_Y + (rh - 4) * TSIZE - ao[ROBIN].ny - ry;

	DrawNeutral(OBJ_WORMHOLE0 + Abs(3 - frame) % 3, x, y + (float)20 * zoom, 0, emphasisScale * 2.0f);

	DrawCmfDetailShadow(enemyData[wave[robin.waveIdx * WAVEDATASIZE * MAXWAVEENEMY + robin.curWaveIdx * WAVEDATASIZE + 0] * ENEMYDATASIZE + ENEMYDATA_CMF], crewPos[wave[robin.waveIdx * WAVEDATASIZE * MAXWAVEENEMY + robin.curWaveIdx * WAVEDATASIZE + 0] * 5 + 0] + (frame / 4 % crewPos[wave[robin.waveIdx * WAVEDATASIZE * MAXWAVEENEMY + robin.curWaveIdx * WAVEDATASIZE + 0] * 5 + 1]), x, y, LEFT, emphasisScale);
	
	DrawGoldAlpha(x, y + (float)132 * zoom, ALPHA_STAGE, FONT_GOLD_LARGE, zoom, CENTER, false, false);
	DrawGoldNum(robin.curWaveIdx + 1, x, y + (float)108 * zoom, CENTER, false, false, false, 0.5f * zoom);

}