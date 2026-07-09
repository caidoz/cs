#include "Core.h"
#include "Data.h"
#include "Func.h"
#include "Text.h"

void Demo(void)
{
	int i, j, k;
	int gap;
	int totalPlayer = realPlayerCnt;

	if (curMenu == MENU_LIST && xOffset < 0) {
		xOffset -= 32 * _2X;
		if (xOffset <= -GAMEMENUWIN_X)
			xOffset = -GAMEMENUWIN_X;
	}
	else {
		xOffset += 32 * _2X;
		if (xOffset >= 0)
			xOffset = 0;
	}

	if (areaFrame > 0) {
		if (curtainFrame == 0)
			areaFrame--;
	}

	MoveBG();

	switch (movie.type) {
	case MOVIE_MOVE:
		DemoCore();
		break;
	case MOVIE_ALPHA:
		if (demoFrame < 8)
			grayScale = demoFrame * 2;
		else if (demoFrame > frameData[movie.start * DFLEN + 2] - 8)
			grayScale = (frameData[movie.start * DFLEN + 2] - demoFrame) * 2;
		else
			grayScale = 16;
		break;
	}

	i = TOTALOBJECT;

	do {
		i--;

		if (ao[i].active)
			MoveObj(&ao[i]);
	} while (i > 0);

	SetCamera();

#ifdef DEBUG
	if (demoSkip == 0)
#endif
	DrawScreen(DX / 2 + scX, DY / 2 + scY[MENU_PLAY], screenZoom, gScreenBuffer, gScreenLayer, false);

	//여기에 이야기하는 화자가 나온다.

	int talkerZoom = 2;
	int imgW = 765;
	int imgH = 1024;
	int imgX = DX / 2 - imgW / 2;
	int imgY = DY / 2 + imgH / 2;

	switch (movie.index) {
	case DEMO_OPENING_PEACEFUL:
	case DEMO_OPENING_DARKKNIGHT:
	case DEMO_OPENING_PLUNDER:
	case DEMO_OPENING_WARNNING:
	case DEMO_OPENING_END:
		DrawImage(
			imgW, imgH,
			0, 0,
			imgX, imgY,
			false, false, false, false, false,
			1.0f,
			sprite[OP0_IMG + movie.index - DEMO_OPENING_PEACEFUL],
			gScreenBuffer,
			gScreenLayer,
			OP0_IMG + movie.index - DEMO_OPENING_PEACEFUL,
			false
		);
		break;
	case DEMO_OPENING_BEGGAR:
		if (curtainFrame > 0)
			DrawCmfDetailShadow(DEMO_HELPER, PO_C93_W0 + walkFrame[frame / MOTIONDIV % 4], xOffset + HELPER_DEMO_GAP_X - curtainFrame * _2X, STATUSWIN_Y2 + HELPERGAP_Y, LEFT, talkerZoom, gScreenBuffer, gScreenLayer, false);
		else if (curtainFrame < 0)
			DrawCmfDetailShadow(DEMO_HELPER, PO_C93_W0 + walkFrame[frame / MOTIONDIV % 4], xOffset + HELPER_DEMO_GAP_X + curtainFrame * _2X, STATUSWIN_Y2 + HELPERGAP_Y, RIGHT, talkerZoom, gScreenBuffer, gScreenLayer, false);
		else {
			DrawCmfDetailShadow(DEMO_HELPER, frame / MOTIONDIV / MOTIONDIV % 4, xOffset + HELPER_DEMO_GAP_X, STATUSWIN_Y2 + HELPERGAP_Y, RIGHT, talkerZoom, gScreenBuffer, gScreenLayer, false);
			SetRectPoint(xOffset + HELPER_DEMO_GAP_X - 2 * ITEMICONSIZE, STATUSWIN_Y2 + HELPERGAP_Y + 3 * ITEMICONSIZE, ITEMICONSIZE * 4, ITEMICONSIZE * 4, TOUCH_FUNC_SKIPDEMO);

			//SKIP MARK
			MemRectBoth(xOffset + HELPER_DEMO_GAP_X - 24 * _2X, STATUSWIN_Y2 + HELPERGAP_Y - 8 * _2X, 48 * _2X, 11 * _2X, COLOR_BLACK, COLOR_WHITE, gScreenBuffer, gScreenLayer, false);
			CenterAlpha(xOffset + HELPER_DEMO_GAP_X, STATUSWIN_Y2 + HELPERGAP_Y - 10 * _2X, ALPHA_SKIP, FONT_SMALL, false, 1.0f, gScreenBuffer, gScreenLayer, false);
		}

		break;
	case DEMO_TUTORIAL_SEBASTIAN:
		switch (movie.start) {
		case DEMO_TUTORIAL_SEBASTIAN_FRAME0:
			DrawCmfDetailShadow(DEMO_HELPER, PO_C93_W0 + walkFrame[frame / MOTIONDIV % 4], xOffset + HELPER_DEMO_GAP_X - curtainFrame * _2X, STATUSWIN_Y2 + HELPERGAP_Y, LEFT, talkerZoom, gScreenBuffer, gScreenLayer, false);
			break;
		}
		break;
	case DEMO_TUTORIAL_PLAYER:	//내 캐릭터를 보여주고
	case DEMO_TUTORIAL_ENEMY:		//적의 등장 및 적 체력 게이지와 남은 시간에 대한 설명
	case DEMO_TUTORIAL_JOYSTICK:		//조이스틱을 터치해서 공격해보라는것(조이스틱을 슬라이드로 땡기면 자동으로 공격됩니다.)
	case DEMO_TUTORIAL_JOKBO_COIN:	//족보중 코인에 대해
	case DEMO_TUTORIAL_JOKBO_COINBAG:	//족보중 코인백에 대해
	case DEMO_TUTORIAL_JOKBO_HEART:	//족보중 하트에 대해
	case DEMO_TUTORIAL_JOKBO_QUEST:	//족보중 퀘스트 아이템에 대해
	case DEMO_TUTORIAL_BOSS:
	case DEMO_TUTORIAL_JOKBO_BATTLE:	//족보중 히트(주먹)에 대해
	case DEMO_TUTORIAL_JOKBO_RAID:	//족보중 히트(주먹)에 대해
	case DEMO_TUTORIAL_JOKBO_SKILL:
	case DEMO_TUTORIAL_GETWEAPON:		//보상받는 화면을 알려준다.
		DrawCmfDetailShadow(DEMO_HELPER, frame / MOTIONDIV / MOTIONDIV % 4, xOffset + 32 * _2X, STATUSWIN_Y2 + HELPERGAP_Y, RIGHT, talkerZoom, gScreenBuffer, gScreenLayer, false);
		break;
	}

	if (movie.type >= MOVIE_MENU) {

		menuFrame++;
		menuWinFrame++;
	}

	if (movie.start == movie.end) {
		talk.obj = talk.clr = talk.temp = null;
		AfterDemo();

		return;
	}

	if (effect.gray)
		GammaImage(32, 6, 1.0f, gScreenBuffer, gScreenLayer, false);

	//텍스트 뒤 프레임
	switch (movie.type) {
	case MOVIE_MOVE:
		if (frame % MOTIONDIV == 0)
			movie.frame++;
		break;
	case MOVIE_TALK:
	case MOVIE_MENUTALK:
		Demo_Talk();
		break;
	case MOVIE_WIN:
		Demo_Win();
		break;
	case MOVIE_ALPHA:
		Demo_Alpha();
		break;
	case MOVIE_NARRATION:
		Demo_Narration();
		break;
	case MOVIE_SPREAD_MDR:
		SpreadPlayer(MAXX, DIANA, ROBIN);
		break;
	case MOVIE_SPREAD_MRD:
		SpreadPlayer(MAXX, ROBIN, DIANA);
		break;
	case MOVIE_SPREAD_DRM:
		SpreadPlayer(DIANA, ROBIN, MAXX);
		break;
	case MOVIE_SPREAD_DMR:
		SpreadPlayer(DIANA, MAXX, ROBIN);
		break;
	case MOVIE_SPREAD_RMD:
		SpreadPlayer(ROBIN, MAXX, DIANA);
		break;
	case MOVIE_SPREAD_RDM:
		SpreadPlayer(ROBIN, DIANA, MAXX);
		break;
	case MOVIE_GATHER_PLAYER:
		if (GatherPlayer())
			movie.type = MOVIE_MOVE;
		else {
			if (frame % MOTIONDIV == 0)
				demoFrame++;
		}

		focus = PLAYER;
		break;
	case MOVIE_WAITDARKSTONE:
		if (ao[talk.obj].x == 195 * _2X) {
			npcdarkStone = 0;
			ao[talk.obj].status = FALL;
			ao[talk.obj].etc = 2;
			movie.type = MOVIE_MOVE;
			if (frame % MOTIONDIV == 0)
				movie.frame++;
			movie.start++;
		}
		break;
	case MOVIE_SETQUEST_PLAYER:
		Demo_SetQuestPlayer();
		break;
	case MOVIE_OBJSHAKE:
		ao[talk.obj].dx = ao[talk.obj].dy = 0;
		ao[talk.obj].x += demoFrame % 2 == 0 ? -2 * _2X : 2 * _2X;

		if (frame % MOTIONDIV == 0)
			demoFrame++;

		if (demoFrame > 9)
			movie.type = MOVIE_MOVE;
		break;
	case MOVIE_WARPIN:
	case MOVIE_WARPOUT:
		if (demoFrame < 10) {
			ao[focus].active = false;
			SetAlpha(movie.type == MOVIE_WARPIN ? demoFrame * 3 : 32 - demoFrame * 3);
			DrawObj(&ao[focus], gScreenBuffer, gScreenLayer, false);
			SetAlpha(32);
			DrawPlayer(&ao[raidPlayer], 2000 + LEVELUP_FRONT0 + demoFrame, ao[focus].x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ao[focus].y - ry + OBJIMGGAP, ao[focus].dirF, ao[focus].zoom, false, false, false, gScreenBuffer, gScreenLayer, false);
			if (frame % MOTIONDIV == 0)
				demoFrame++;
		}
		else {
			ao[focus].active = movie.type == MOVIE_WARPIN ? true : false;
			movie.type = MOVIE_MOVE;
		}
		break;
	case MOVIE_APPEAROBJ:
	case MOVIE_DISAPPEAROBJ:
		ao[focus].active = false;

		if (focus >= ITEMOBJ)
			ItemMove(&ao[focus]);
		else if (focus >= NEUTRAL) {
			MoveObj(&ao[focus]);
		}
		else if (ao[focus].moveHandler != MACHINEBOSSMOVE)
			DemoMove(&ao[focus]);

		SetAlpha(movie.type == MOVIE_APPEAROBJ ? demoFrame : 32 - demoFrame);
		DrawObj(&ao[focus], gScreenBuffer, gScreenLayer, false);
		SetAlpha(32);
		if (frame % MOTIONDIV == 0)
			demoFrame++;
		//demoFrame += 3;

		if (demoFrame >= FPS) {
			ao[focus].active = movie.type == MOVIE_APPEAROBJ ? true : false;
			movie.type = MOVIE_MOVE;
			break;
		}
		break;
	case MOVIE_FRAMEUNSETBLEND:
		if (ao[focus].mainFrame == 0) {
			movie.type = MOVIE_MOVE;
			break;
		}

		ao[focus].mainFrame--;
		break;
		//두리번 효과
	case MOVIE_GAZEAROUND:
		if ((demoFrame % 6) == 0) {
			if (talk.obj == PLAYERALL) {
				int k;
				for (k = PLAYER; k < PLAYERALL; k++)
					ao[k].dirF = ao[k].dirX = 1 - ao[k].dirF;
			}
			else
				ao[talk.obj].dirF = ao[talk.obj].dirX = 1 - ao[talk.obj].dirF;
		}

		if (demoFrame > 30)
			movie.type = MOVIE_MOVE;

		if (frame % MOTIONDIV == 0)
			demoFrame++;
		break;
	case MOVIE_MENU:
		if (demoFrame > 4)
			goto MOVEOUT;

		if (frame % MOTIONDIV == 0)
			demoFrame++;
		break;
	case MOVIE_MENUMOVE:
		switch (movie.text) {
		default:
			//if (menuDepth == 1 && ao[pObj->type].equip[EQUIP_ARMOR].type != 255)
			//if (menuDepth == 1 && curMenu == 1)
			goto MOVEOUT;
			break;
		}

		if (demoFrame > 100) {
			movie.text--;
			movie.frame -= 2;
			goto MOVEOUT;
		}

		if (frame % MOTIONDIV == 0)
			demoFrame++;
		break;
	MOVEOUT:
		movie.text++;
		movie.talker = ENEMY;
		SetFrameText(movie.text, 512, TEXTLINEPERPAGE, 1.0f);

		movie.type = MOVIE_MENUTALK;
		break;
	}
	/*
	switch (movie.index) {
	case DEMO_OPENING_PEACEFUL:
	case DEMO_OPENING_DARKKNIGHT:
	case DEMO_OPENING_PLUNDER:
	case DEMO_OPENING_WARNNING:
	case DEMO_OPENING_END:
		break;
	default:

		StatusDraw(xOffset, 0, 1.0f, gScreenBuffer, gScreenLayer, false);

		//카드가 나오면
		for (i = 0; i < TOTALCARDMARK; i++) {
			if (cardMark[i].frame2 > 0) {
				GotoPosition(cardMark[i].targetX2, cardMark[i].targetY2, i, cardMark[i].speed2, ICONMARK_CARD);
				cardMark[i].speed2 += cardMark[i].speedIncrement2;
				cardMark[i].zoom2 += cardMark[i].zoomIncrement2;

				//만약 증가량이 0보다 크면
				//end보다 크면 end에서 멈춘다.
				if (cardMark[i].zoomIncrement2 > 0 && cardMark[i].zoom2 > cardMark[i].zoomEnd2)
					cardMark[i].zoom2 = cardMark[i].zoomEnd2;
				if (cardMark[i].zoomIncrement2 < 0 && cardMark[i].zoom2 < cardMark[i].zoomEnd2)
					cardMark[i].zoom2 = cardMark[i].zoomEnd2;

				if (cardMark[i].alpha) {
					SetAlpha(Max(0, TRANSPARENCY_MAX - cardMark[i].alpha));

					if (cardMark[i].alpha < ROULETTE_TRANSPARENCY)
						cardMark[i].alpha++;

				}

				if (Max(0, TRANSPARENCY_MAX - cardMark[i].alpha) > 0) {
					//여기서 카드를 그려주자.
				}

				SetAlpha(32);

				if ((cardMark[i].targetX2 - cardMark[i].x) * (cardMark[i].targetX2 - cardMark[i].x) + (cardMark[i].targetY2 - cardMark[i].y) * (cardMark[i].targetY2 - cardMark[i].y) < 2 * cardMark[i].speed2 * cardMark[i].speed2 && cardMark[i].frame2 >= cardMark[i].waitingFrame2) {
					cardMark[i].x = cardMark[i].targetX2;
					cardMark[i].y = cardMark[i].targetY2;

				}
				else {
					cardMark[i].frame2++;
				}

				if (cardMark[i].alpha == ROULETTE_TRANSPARENCY) {
					memset(&cardMark[i], 0, sizeof(ICONMARK));
					ArrangeControlMark(i);
				}
			}
			else if (cardMark[i].frame > 0) {
				GotoPosition(cardMark[i].targetX, cardMark[i].targetY, i, cardMark[i].speed, ICONMARK_CARD);
				cardMark[i].speed += cardMark[i].speedIncrement;
				cardMark[i].zoom += cardMark[i].zoomIncrement;

				//만약 증가량이 0보다 크면
				//end보다 크면 end에서 멈춘다.
				if (cardMark[i].zoomIncrement > 0 && cardMark[i].zoom > cardMark[i].zoomEnd)
					cardMark[i].zoom = cardMark[i].zoomEnd;
				if (cardMark[i].zoomIncrement < 0 && cardMark[i].zoom < cardMark[i].zoomEnd)
					cardMark[i].zoom = cardMark[i].zoomEnd;

				if (cardMark[i].alpha) {
					SetAlpha(Max(0, TRANSPARENCY_MAX - cardMark[i].alpha));

					if (cardMark[i].alpha < ROULETTE_TRANSPARENCY)
						cardMark[i].alpha++;
				}

				if (Max(0, TRANSPARENCY_MAX - cardMark[i].alpha) > 0) {
					//여기서 카드를 그려주자.
				}

				SetAlpha(32);

				if ((cardMark[i].targetX - cardMark[i].x) * (cardMark[i].targetX - cardMark[i].x) + (cardMark[i].targetY - cardMark[i].y) * (cardMark[i].targetY - cardMark[i].y) < 2 * cardMark[i].speed * cardMark[i].speed && cardMark[i].frame >= cardMark[i].waitingFrame) {

					if (cardMark[i].targetX2 != 0 || cardMark[i].targetY2 != 0) {
						cardMark[i].frame2 = 1;
					}
					else {
						cardMark[i].x = cardMark[i].targetX;
						cardMark[i].y = cardMark[i].targetY;
					}
				}
				else
					cardMark[i].frame++;

				if (cardMark[i].alpha == ROULETTE_TRANSPARENCY) {
					memset(&cardMark[i], 0, sizeof(ICONMARK));
					ArrangeControlMark(i);
				}
			}
		}

		for (i = BAR_GOLD; i < TOTAL_BAR; i++) {
			if (bar[i].active == true && bar[i].front == false) {
				if (bar[i].frame2 > 0) {
					GotoPositionBar(&bar[i], bar[i].targetX2, bar[i].targetY2, bar[i].speed2);
					bar[i].speed2 += bar[i].speedIncrement2;
					bar[i].zoom2 += bar[i].zoomIncrement2;

					//if (bar[i].speed2 < 8 * _2X)
					//	bar[i].speed2 = 8 * _2X;

					//만약 증가량이 0보다 크면
					//end보다 크면 end에서 멈춘다.
					if (bar[i].zoomIncrement2 > 0 && bar[i].zoom2 > bar[i].zoomEnd2)
						bar[i].zoom2 = bar[i].zoomEnd2;
					if (bar[i].zoomIncrement2 < 0 && bar[i].zoom2 < bar[i].zoomEnd2)
						bar[i].zoom2 = bar[i].zoomEnd2;

					if (bar[i].alpha) {
						SetAlpha(Max(0, TRANSPARENCY_MAX - bar[i].alpha));

						if (bar[i].alpha < ROULETTE_TRANSPARENCY)
							bar[i].alpha++;

					}


					SetAlpha(32);

					if ((bar[i].targetX2 - bar[i].x) * (bar[i].targetX2 - bar[i].x) + (bar[i].targetY2 - bar[i].y) * (bar[i].targetY2 - bar[i].y) < 2 * bar[i].speed2 * bar[i].speed2 || bar[i].frame2 >= bar[i].waitingFrame2) {
						bar[i].x = bar[i].targetX2;
						bar[i].y = bar[i].targetY2;
						bar[i].frame2 = bar[i].frame = 0;
					}
					else {
						bar[i].frame2++;
					}

					BarDraw(&bar[i], bar[i].zoom2, gScreenBuffer, gScreenLayer, false);
				}
				else if (bar[i].frame > 0) {
					GotoPositionBar(&bar[i], bar[i].targetX, bar[i].targetY, bar[i].speed);
					bar[i].speed += bar[i].speedIncrement;
					bar[i].zoom += bar[i].zoomIncrement;

					//if (bar[i].speed < 8 * _2X)
					//	bar[i].speed = 8 * _2X;

					//만약 증가량이 0보다 크면
					//end보다 크면 end에서 멈춘다.
					if (bar[i].zoomIncrement > 0 && bar[i].zoom > bar[i].zoomEnd)
						bar[i].zoom = bar[i].zoomEnd;
					if (bar[i].zoomIncrement < 0 && bar[i].zoom < bar[i].zoomEnd)
						bar[i].zoom = bar[i].zoomEnd;

					if (bar[i].alpha) {
						SetAlpha(Max(0, TRANSPARENCY_MAX - bar[i].alpha));

						if (bar[i].alpha < ROULETTE_TRANSPARENCY)
							bar[i].alpha++;
					}


					SetAlpha(32);

					if ((bar[i].targetX - bar[i].x) * (bar[i].targetX - bar[i].x) + (bar[i].targetY - bar[i].y) * (bar[i].targetY - bar[i].y) < 2 * bar[i].speed * bar[i].speed && bar[i].frame >= bar[i].waitingFrame) {

						if (bar[i].targetX2 != 0 || bar[i].targetY2 != 0) {
							bar[i].frame2 = 1;
						}
						else {
							bar[i].x = bar[i].targetX;
							bar[i].y = bar[i].targetY;
						}
					}
					else
						bar[i].frame++;

					BarDraw(&bar[i], bar[i].zoom, gScreenBuffer, gScreenLayer, false);
				}
				else
					BarDraw(&bar[i], bar[i].zoom, gScreenBuffer, gScreenLayer, false);
			}
		}

		if (effect.color2) {
			SetAlpha(24);
			MemRect(xOffset, DY, DX - 2 * xOffset, DY, effect.color, gScreenBuffer, gScreenLayer, false);
			SetAlpha(32);
		}

		if (keyHandle == MK_PLAY) {
			for (i = 0; i < MAXGAMEEVENT; i++) {
				if (robin.gameEvent[i].type && robin.gameEvent[i].front == false) {
					if (robin.gameEvent[i].frame2 > 0) {
						GotoEventMenu(robin.gameEvent[i].targetX2, robin.gameEvent[i].targetY2, i, robin.gameEvent[i].speed2, ICONMARK_REWARD);
						robin.gameEvent[i].speed2 += robin.gameEvent[i].speedIncrement2;
						robin.gameEvent[i].zoom2 += robin.gameEvent[i].zoomIncrement2;


						//만약 증가량이 0보다 크면
						//end보다 크면 end에서 멈춘다.
						if (robin.gameEvent[i].zoomIncrement2 > 0 && robin.gameEvent[i].zoom2 > robin.gameEvent[i].zoomEnd2)
							robin.gameEvent[i].zoom2 = robin.gameEvent[i].zoomEnd2;
						if (robin.gameEvent[i].zoomIncrement2 < 0 && robin.gameEvent[i].zoom2 < robin.gameEvent[i].zoomEnd2)
							robin.gameEvent[i].zoom2 = robin.gameEvent[i].zoomEnd2;

						if ((robin.gameEvent[i].targetX2 - robin.gameEvent[i].x) * (robin.gameEvent[i].targetX2 - robin.gameEvent[i].x) + (robin.gameEvent[i].targetY2 - robin.gameEvent[i].y) * (robin.gameEvent[i].targetY2 - robin.gameEvent[i].y) < 2 * robin.gameEvent[i].speed2 * robin.gameEvent[i].speed2 && robin.gameEvent[i].frame2 >= robin.gameEvent[i].waitingFrame2) {
							robin.gameEvent[i].x = robin.gameEvent[i].targetX2;
							robin.gameEvent[i].y = robin.gameEvent[i].targetY2;


						}
						else {
							robin.gameEvent[i].frame2++;
						}

						EventMenuDraw(&robin.gameEvent[i], gScreenBuffer, gScreenLayer, false);

					}
					else if (robin.gameEvent[i].frame > 0) {
						GotoEventMenu(robin.gameEvent[i].targetX, robin.gameEvent[i].targetY, i, robin.gameEvent[i].speed, ICONMARK_REWARD);

						robin.gameEvent[i].speed += robin.gameEvent[i].speedIncrement;
						robin.gameEvent[i].zoom += robin.gameEvent[i].zoomIncrement;

						//만약 증가량이 0보다 크면
						//end보다 크면 end에서 멈춘다.
						if (robin.gameEvent[i].zoomIncrement > 0 && robin.gameEvent[i].zoom > robin.gameEvent[i].zoomEnd)
							robin.gameEvent[i].zoom = robin.gameEvent[i].zoomEnd;
						if (robin.gameEvent[i].zoomIncrement < 0 && robin.gameEvent[i].zoom < robin.gameEvent[i].zoomEnd)
							robin.gameEvent[i].zoom = robin.gameEvent[i].zoomEnd;

						if ((robin.gameEvent[i].targetX - robin.gameEvent[i].x) * (robin.gameEvent[i].targetX - robin.gameEvent[i].x) + (robin.gameEvent[i].targetY - robin.gameEvent[i].y) * (robin.gameEvent[i].targetY - robin.gameEvent[i].y) < 2 * robin.gameEvent[i].speed * robin.gameEvent[i].speed && robin.gameEvent[i].frame >= robin.gameEvent[i].waitingFrame) {
							//if (rewardMark[i].frame >= rewardMark[i].waitingFrame) {
								//PlayMusic(M_COIN);
								//두번째 세팅이 있으면 
							robin.gameEvent[i].x = robin.gameEvent[i].targetX;
							robin.gameEvent[i].y = robin.gameEvent[i].targetY;

							if (robin.gameEvent[i].targetX2 != 0 || robin.gameEvent[i].targetY2 != 0) {
								robin.gameEvent[i].frame2 = 1;
							}
						}
						else {
							robin.gameEvent[i].frame++;
						}

						EventMenuDraw(&robin.gameEvent[i], gScreenBuffer, gScreenLayer, false);


					}

					//새로 생성이 되었거나 
					//시간이 다 되었으면
					switch (robin.gameEvent[i].status) {
					case EVENT_OPEN:
						if (robin.gameEvent[i].frame == EVENTFRAME_START) {
							robin.gameEvent[i].status = EVENT_DOING;
							robin.gameEvent[i].frame = 0;
						}
						else if (robin.gameEvent[i].frame > 0) {
							robin.gameEvent[i].frame++;
						}
						break;
					case EVENT_DOING:
						if (robin.gameEvent[i].limitTime - (MC_knlCurrentTimeStamp() - robin.gameEvent[i].timeStamp) <= 0) {
							robin.gameEvent[i].status = EVENT_CLOSE;
							robin.gameEvent[i].frame = 1;
						}
						else {
							robin.gameEvent[i].frame++;
						}
						break;
					case EVENT_CLOSE:
						if (robin.gameEvent[i].frame == EVENTFRAME_FINISH) {
							DeleteEventMenu(i);
						}
						else if (robin.gameEvent[i].frame > 0) {
							robin.gameEvent[i].frame++;
						}
						break;
					}
				}
			}
		}

		GNBDraw(xOffset, DY - (GNBHEIGHT - GNB_INIT_HEIGHT), gScreenBuffer, gScreenLayer, false);

		if (curMenu == MENU_PLAY && JoyStickPressPossible() == true)
			EventScheduler();

		for (i = BAR_GOLD; i < TOTAL_BAR; i++) {
			if (bar[i].active == true && bar[i].front == true) {
				if (bar[i].frame2 > 0) {
					GotoPositionBar(&bar[i], bar[i].targetX2, bar[i].targetY2, bar[i].speed2);
					bar[i].speed2 += bar[i].speedIncrement2;
					bar[i].zoom2 += bar[i].zoomIncrement2;

					//if (bar[i].speed2 < 8 * _2X)
					//	bar[i].speed2 = 8 * _2X;

					//만약 증가량이 0보다 크면
					//end보다 크면 end에서 멈춘다.
					if (bar[i].zoomIncrement2 > 0 && bar[i].zoom2 > bar[i].zoomEnd2)
						bar[i].zoom2 = bar[i].zoomEnd2;
					if (bar[i].zoomIncrement2 < 0 && bar[i].zoom2 < bar[i].zoomEnd2)
						bar[i].zoom2 = bar[i].zoomEnd2;

					if (bar[i].alpha) {
						SetAlpha(Max(0, TRANSPARENCY_MAX - bar[i].alpha));

						if (bar[i].alpha < ROULETTE_TRANSPARENCY)
							bar[i].alpha++;

					}


					SetAlpha(32);

					if ((bar[i].targetX2 - bar[i].x) * (bar[i].targetX2 - bar[i].x) + (bar[i].targetY2 - bar[i].y) * (bar[i].targetY2 - bar[i].y) < 2 * bar[i].speed2 * bar[i].speed2 && bar[i].frame2 >= bar[i].waitingFrame2) {
						bar[i].x = bar[i].targetX2;
						bar[i].y = bar[i].targetY2;

					}
					else {
						bar[i].frame2++;
					}

					BarDraw(&bar[i], bar[i].zoom2, gScreenBuffer, gScreenLayer, false);
				}
				else if (bar[i].frame > 0) {
					GotoPositionBar(&bar[i], bar[i].targetX, bar[i].targetY, bar[i].speed);
					bar[i].speed += bar[i].speedIncrement;
					bar[i].zoom += bar[i].zoomIncrement;

					//if (bar[i].speed < 8 * _2X)
					//	bar[i].speed = 8 * _2X;

					//만약 증가량이 0보다 크면
					//end보다 크면 end에서 멈춘다.
					if (bar[i].zoomIncrement > 0 && bar[i].zoom > bar[i].zoomEnd)
						bar[i].zoom = bar[i].zoomEnd;
					if (bar[i].zoomIncrement < 0 && bar[i].zoom < bar[i].zoomEnd)
						bar[i].zoom = bar[i].zoomEnd;

					if (bar[i].alpha) {
						SetAlpha(Max(0, TRANSPARENCY_MAX - bar[i].alpha));

						if (bar[i].alpha < ROULETTE_TRANSPARENCY)
							bar[i].alpha++;
					}


					SetAlpha(32);

					if ((bar[i].targetX - bar[i].x) * (bar[i].targetX - bar[i].x) + (bar[i].targetY - bar[i].y) * (bar[i].targetY - bar[i].y) < 2 * bar[i].speed * bar[i].speed && bar[i].frame >= bar[i].waitingFrame) {

						if (bar[i].targetX2 != 0 || bar[i].targetY2 != 0) {
							bar[i].frame2 = 1;
						}
						else {
							bar[i].x = bar[i].targetX;
							bar[i].y = bar[i].targetY;
						}
					}
					else
						bar[i].frame++;

					BarDraw(&bar[i], bar[i].zoom, gScreenBuffer, gScreenLayer, false);
				}
				else
					BarDraw(&bar[i], bar[i].zoom, gScreenBuffer, gScreenLayer, false);
			}
		}


		for (i = 0; i < TOTALCONTROLMARK; i++) {
			if (controlMark[i].frame2 > 0) {
				GotoPosition(controlMark[i].targetX2, controlMark[i].targetY2, i, controlMark[i].speed2, ICONMARK_CONTROLMARK);
				controlMark[i].speed2 += controlMark[i].speedIncrement2;
				controlMark[i].zoom2 += controlMark[i].zoomIncrement2;

				//if (controlMark[i].speed2 < 8 * _2X)
				//	controlMark[i].speed2 = 8 * _2X;

				//만약 증가량이 0보다 크면
				//end보다 크면 end에서 멈춘다.
				if (controlMark[i].zoomIncrement2 > 0 && controlMark[i].zoom2 > controlMark[i].zoomEnd2)
					controlMark[i].zoom2 = controlMark[i].zoomEnd2;
				if (controlMark[i].zoomIncrement2 < 0 && controlMark[i].zoom2 < controlMark[i].zoomEnd2)
					controlMark[i].zoom2 = controlMark[i].zoomEnd2;

				if (controlMark[i].alpha) {
					SetAlpha(Max(0, TRANSPARENCY_MAX - controlMark[i].alpha));

					if (controlMark[i].alpha < ROULETTE_TRANSPARENCY)
						controlMark[i].alpha++;
				}

				if (Max(0, TRANSPARENCY_MAX - controlMark[i].alpha) > 0) {
					DrawSkillCard(controlMark[i].attackType, controlMark[i].attackStr, xOffset + controlMark[i].x - (float)ROULETTECARDSIZE_X * controlMark[i].zoom2 / 2, controlMark[i].y + floatOffsetY + (float)ROULETTECARDSIZE_Y * controlMark[i].zoom2 / 2, controlMark[i].zoom2, gScreenBuffer, gScreenLayer, false);
				}

				SetAlpha(32);

				if ((controlMark[i].targetX2 - controlMark[i].x) * (controlMark[i].targetX2 - controlMark[i].x) + (controlMark[i].targetY2 - controlMark[i].y) * (controlMark[i].targetY2 - controlMark[i].y) < 2 * controlMark[i].speed2 * controlMark[i].speed2 && controlMark[i].frame2 >= controlMark[i].waitingFrame2) {
					controlMark[i].x = controlMark[i].targetX2;
					controlMark[i].y = controlMark[i].targetY2;
				}
				else {
					controlMark[i].frame2++;
				}

				if (controlMark[i].alpha == ROULETTE_TRANSPARENCY) {
					memset(&controlMark[i], 0, sizeof(ICONMARK));
					ArrangeControlMark(i);
				}
			}
			else if (controlMark[i].frame > 0) {
				GotoPosition(controlMark[i].targetX, controlMark[i].targetY, i, controlMark[i].speed, ICONMARK_CONTROLMARK);
				controlMark[i].speed += controlMark[i].speedIncrement;
				controlMark[i].zoom += controlMark[i].zoomIncrement;

				//만약 증가량이 0보다 크면
				//end보다 크면 end에서 멈춘다.
				if (controlMark[i].zoomIncrement > 0 && controlMark[i].zoom > controlMark[i].zoomEnd)
					controlMark[i].zoom = controlMark[i].zoomEnd;
				if (controlMark[i].zoomIncrement < 0 && controlMark[i].zoom < controlMark[i].zoomEnd)
					controlMark[i].zoom = controlMark[i].zoomEnd;

				if (controlMark[i].alpha) {
					SetAlpha(Max(0, TRANSPARENCY_MAX - controlMark[i].alpha));

					if (controlMark[i].alpha < ROULETTE_TRANSPARENCY)
						controlMark[i].alpha++;
				}

				if (Max(0, TRANSPARENCY_MAX - controlMark[i].alpha) > 0) {
					DrawSkillCard(controlMark[i].attackType, controlMark[i].attackStr, xOffset + controlMark[i].x - (float)ROULETTECARDSIZE_X * controlMark[i].zoom / 2, controlMark[i].y + floatOffsetY + (float)ROULETTECARDSIZE_Y * controlMark[i].zoom / 2, controlMark[i].zoom, gScreenBuffer, gScreenLayer, false);
				}

				SetAlpha(32);

				if ((controlMark[i].targetX - controlMark[i].x) * (controlMark[i].targetX - controlMark[i].x) + (controlMark[i].targetY - controlMark[i].y) * (controlMark[i].targetY - controlMark[i].y) < 2 * controlMark[i].speed * controlMark[i].speed && controlMark[i].frame >= controlMark[i].waitingFrame) {
					if (controlMark[i].targetX2 != 0 || controlMark[i].targetY2 != 0) {
						controlMark[i].frame2 = 1;
					}
					else {
						controlMark[i].x = controlMark[i].targetX;
						controlMark[i].y = controlMark[i].targetY;
					}
				}
				else {
					controlMark[i].frame++;
				}

				if (controlMark[i].alpha == ROULETTE_TRANSPARENCY) {
					memset(&controlMark[i], 0, sizeof(ICONMARK));
					ArrangeControlMark(i);
				}
			}

			if (controlMark[i].lockOpenFrame > 0)
				controlMark[i].lockOpenFrame++;
		}

		if (skillInfoFrame > 0) {
			//SetFontColor(COLOR_WHITE);
			if (curSkill < 100) {//스킬이면
				SetActiveSkillBodyString(curSkill);
			}
			else {
				int focused = raidPlayer;

				memset(skillBodyStr, 0, sizeof(skillBodyStr));
				temp = TEXT_RING_OPTION_EFFECT + ao[focused].equip[EQUIP_RING].detail;

				switch (ao[focused].equip[EQUIP_RING].detail) {
				case ITEM_RING3:
				case ITEM_RING6:
				case ITEM_RING9:
				case ITEM_RING10:
				case ITEM_RING15:
					sprintf(skillBodyStr, TEXTPTR(temp), (float)ao[focused].equip[EQUIP_RING].value / 10);
					break;
				default:
					sprintf(skillBodyStr, TEXTPTR(temp), ao[focused].equip[EQUIP_RING].value);
					break;
				}
			}

			int width = StringWidth(skillStr3, 2) + 8 * _2X + SKILLICONSIZE * 2;

			if (curSkill < 100)//스킬이면
				DrawTextStr(skillStr3, xOffset + DX / 2 - width / 2 + 8 * _2X + SKILLICONSIZE * 2 + 4 * _2X, STATUSWIN_Y + SKILLTEXT_Y, 2, gScreenBuffer, gScreenLayer, false);
			else
				DrawTextStr(ringStr, xOffset + DX / 2 - width / 2 + 8 * _2X + SKILLICONSIZE * 2 + 4 * _2X, STATUSWIN_Y + SKILLTEXT_Y, 2, gScreenBuffer, gScreenLayer, false);


			int collectionIdx = GetCollectionIdx(ao[PLAYER].equip[EQUIP_WEAPON].type, ao[PLAYER].equip[EQUIP_WEAPON].detail, ao[PLAYER].equip[EQUIP_WEAPON].grade);
			int enemyIdx;

			//if (curSkill < 100)//스킬이면
			//	DrawSkillIcon(skillData[SKILLDATASIZE * curSkill + 5], xOffset + DX / 2 - width / 2 + 8 * _2X, STATUSWIN_Y + SKILLTEXT_Y + 8 * _2X, 2, gScreenBuffer, gScreenLayer, false);
			if (skillData[curSkill * SKILLDATASIZE + 0] == SUMMON) {
				enemyIdx = skillData[curSkill * SKILLDATASIZE + 1];

				float zoom = 2.0f;
				SetSectionClip(xOffset + DX / 2 - width / 2 + 8 * _2X, STATUSWIN_Y + SKILLTEXT_Y + 8 * _2X, (float)(SKILLICONSIZE)*zoom, (float)(SKILLICONSIZE)*zoom, false);
				ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, xOffset + DX / 2 - width / 2 + 8 * _2X + (float)(SKILLICONSIZE)*zoom / 2 - (float)40 * _2X / 2 * zoom, STATUSWIN_Y + SKILLTEXT_Y + 8 * _2X + (float)(-SKILLICONSIZE + 8 * _2X) * zoom * 3 / 4, SHADOW_IMG, zoom / 2, gScreenBuffer, gScreenLayer, false);

				DrawCmfDetail(enemyData[enemyIdx * ENEMYDATASIZE + ENEMYDATA_CMF], enemySkillIconPos[3 * enemyIdx + 0], xOffset + DX / 2 - width / 2 + 8 * _2X + (float)(SKILLICONSIZE)*zoom / 2 + (float)(enemySkillIconPos[3 * enemyIdx + 1]) * zoom, STATUSWIN_Y + SKILLTEXT_Y + 8 * _2X + (float)(-SKILLICONSIZE + enemySkillIconPos[3 * enemyIdx + 2]) * zoom, LEFT, zoom / 2, false, false, gScreenBuffer, gScreenLayer, false);

				UnSectionClip(false);
			}
			else
				DrawSkillIcon(skillData[SKILLDATASIZE * curSkill + 5], xOffset + DX / 2 - width / 2 + 8 * _2X, STATUSWIN_Y + SKILLTEXT_Y + 8 * _2X, 2, gScreenBuffer, gScreenLayer, false);
		}


		ActiveHelpDraw(gScreenBuffer, gScreenLayer, false);

		for (i = ROBIN; i < TOTALPLAYER; i++)
			if (ao[i].hitCountFrame > 0) {
				ao[i].hitCountFrame++;

				if (ao[i].hitCountFrame == VANISHFRAME_DMG) {
					ao[i].hitCountFrame = 0;
					ao[i].hitCount = 0;
					ao[i].hitDmg = 0;
				}
			}

		float zoom = 1.0f;

		if (waveStatus == WAVESTATUS_PLAY && attackSequence == ATTACKSEQUENCE_ACTION) {
			if (ao[turn].hitCount > 0) {
				int hitCountPosX = xOffset + ao[turn].x;
				int hitCountPosY = STATUSWIN_Y + (rh - 4) * TSIZE - (ao[turn].y) + floatOffsetY + 48 * _2X;
				DrawGoldNum(ao[turn].hitCount, hitCountPosX, hitCountPosY, RIGHT, false, false, true, 1.2f * zoom, gScreenBuffer, gScreenLayer, false);
				DrawGoldAlpha(hitCountPosX + 4 * _2X, hitCountPosY - 4 * _2X, ALPHA_HIT, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false, gScreenBuffer, gScreenLayer, false);
			}
		}

		//popMenu
		if (drawHandle != MD_NEWCOLLECTION && drawHandle != MD_NEWCARD) {
			if (popUpFrame == 0)
				zoom = 1.0f;
			else if (popUpFrame > 0)
				zoom = popUpFrameData[popUpFrame];

			if (popUpFrame > 0)
				popUpFrame++;

			if (popUpFrame == 8)
				popUpFrame = 0;
		}

		UnSectionClip(false);

		if (curMenu != MENU_PLAY) {
			ResetRectPoint();
		}

		switch (curMenu) {
		case MENU_COLLECTIONS:
			//CollectionsDraw(xOffset, DY - (GNBHEIGHT - GNB_INIT_HEIGHT), zoom, gScreenBuffer, gScreenLayer, false);
			break;
		case MENU_SHOP:
			//ShopDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 * zoom, zoom, gScreenBuffer, gScreenLayer, false);
			break;
		case MENU_STARSHOP:
			StarShopDraw(xOffset + DX / 2 - POPUPWINDOWSIZE_X / 2, POPUPPOSITION_Y + POPUPWINDOWSIZE_Y / 2);
			break;
		case MENU_NEWS:
			NewsDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 * zoom, zoom, gScreenBuffer, gScreenLayer, false);
			break;
		case MENU_GIFTS:
			GiftDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 * zoom, zoom, gScreenBuffer, gScreenLayer, false);
			break;
		case MENU_LEADERBOARD:
			break;
		case MENU_FRIENDS:
			GuildEventDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 * zoom, zoom, gScreenBuffer, gScreenLayer, false);
			break;
		case MENU_INVITEFREINDS:

			break;
		case MENU_CALENDAR://데일리 리워드
			CalendarDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)(POPUPWINDOWSIZE_Y / 2) * zoom, zoom, gScreenBuffer, gScreenLayer, false);
			break;
		case MENU_SETTING:
			OptionDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 * zoom, zoom, gScreenBuffer, gScreenLayer, false);
			break;

		case MENU_LIST:
			GameMenuDraw(xOffset + (DX - GAMEMENUWIN2_X) / 2, DY / 2 + GAMEMENUWIN2_Y / 2, 1.0f, gScreenBuffer, gScreenLayer, false);
			break;
		case MENU_GAMEEVENT:

			switch (robin.gameEvent[curEventIdx].type) {
			case EVENTTYPE_QUEST:
				QuestMenuDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 * zoom, zoom, gScreenBuffer, gScreenLayer, false);
				break;
			case EVENTTYPE_PVP:
				PvpQuestMenuDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 * zoom, zoom, gScreenBuffer, gScreenLayer, false);
				break;
			case EVENTTYPE_SHOP:

				break;
			case EVENTTYPE_DEBTDISCOUNT:
				DiscountMenuDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 * zoom, zoom, gScreenBuffer, gScreenLayer, false);
				break;
			case EVENTTYPE_DOUBLE:
				//EventMenuDraw()
				break;
			case EVENTTYPE_BOSSRAID:
				GoldQuestMenuDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 * zoom, zoom, gScreenBuffer, gScreenLayer, false);
				break;
			case EVENTTYPE_TOUCHGAME:

				break;
			}
			break;
		case MENU_PLAY:
			GameMenuDraw(xOffset, DY, 1.0f, gScreenBuffer, gScreenLayer, false);

			break;
			//메뉴
		case MENU_STAGEINFO:
			//StageInfoDraw(robin.stage, robin.room, false, false, xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2), POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2, zoom, gScreenBuffer, gScreenLayer, false);
			break;
		}
		break;

	}
	*/
	robin.playtime++;

#ifdef DEBUG
	//memset(debugStr, 0, sizeof(debugStr));
	//MC_knlSprintk(debugStr, "|dmap:%d/x:%d/y:%d/dx:%d/dy:%d", movie.index, movie.start, movie.frame, menuDepth, curMenu);
	//CenterTextStr(debugStr, DX / 2, DY - 12);
#endif

	//if (curtainFrame) {
	//	TheaterDraw(gScreenBuffer, gScreenLayer, false);
	//}
}

void Demo_Talk(void)
{
	int i, w = 0;
	signed char talkShakeY = talkShakeFrame;

	if (talkShakeFrame) {
		talkShakeY *= ((talkShakeY % 2) == 0 ? 1 : -1);
		talkShakeY /= 2;
	}

	if (keyHandle == MK_TALK)
		i = talk.obj;
	else
		i = movie.talker;

	//대화자 화살표
	if (!effect.color)
		DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - frame % 8), ao[i].x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ao[i].y - ry + OBJIMGGAP, 0, false, 1.0f, gScreenBuffer, gScreenLayer, false);

	DrawCmfPopUp(ao[i].cmf, movie.text, 0 * _2X, 88 * _2X + HOMEBAR_HEIGHT, DX, 88 * _2X, DX - 120 * _2X, 6, false, 1.0f, gScreenBuffer, gScreenLayer, false);

	if (talkShakeFrame)
		talkShakeFrame--;
}

void Demo_Win(void)
{
	int i, j, k;
	int zoom;
	//int x = 0, y = 0 - (touch == 1 ? 5 : 0);
	int x = xOffset;
	int y = DY - (GNBHEIGHT - GNB_INIT_HEIGHT);

	int xPos = xOffset + DX / 2 - Min(REWARDITEM_XCOUNT, rewardItemCnt) * REWARDCARDSIZE_X / 2;
	int yPos = DY / 2 + ((rewardItemCnt + REWARDITEM_XCOUNT - 1) / REWARDITEM_XCOUNT) * (REWARDCARDSIZE_Y + 4 * _2X) / 2;

	unsigned char* item;
	const unsigned short* demoitem;

	int speed;
	int amount;
	int count;

	int type, detail, grade;
	int tempGachaIcon = gachaIcon[0];
	int tempGachaGrade = gachaGrade[0];
	ITEM* it;

	long long start, end, current;

	int startX, startY, targetX, targetY;
	int width;


	int fontZoom;

	long long getGoldNum = 0;
	long long getHeartNum = 0;
	long long getMedalNum = 0;
	long long getStarNum = 0;
	long long getHammerNum = 0;

	newItemCnt = 0;

	newItemType[newItemCnt] = boxCardItem[0][newItemIdx[curNewItemIdx]].type;
	newItemDetail[newItemCnt] = boxCardItem[0][newItemIdx[curNewItemIdx]].detail;
	newItemGrade[newItemCnt] = boxCardItem[0][newItemIdx[curNewItemIdx]].grade;

	int newItemRewardType = newItemReward[itemStartCnt[newItemType[newItemCnt]] * REWARDITEMDATASIZE + newItemDetail[newItemCnt] * TOTALGRADE * REWARDITEMDATASIZE + newItemGrade[newItemCnt] * REWARDITEMDATASIZE + 0];
	int newItemRewardDetail = newItemReward[itemStartCnt[newItemType[newItemCnt]] * REWARDITEMDATASIZE + newItemDetail[newItemCnt] * TOTALGRADE * REWARDITEMDATASIZE + newItemGrade[newItemCnt] * REWARDITEMDATASIZE + 1];
	int newItemRewardGrade = newItemReward[itemStartCnt[newItemType[newItemCnt]] * REWARDITEMDATASIZE + newItemDetail[newItemCnt] * TOTALGRADE * REWARDITEMDATASIZE + newItemGrade[newItemCnt] * REWARDITEMDATASIZE + 2];
	int newItemRewardCnt = newItemReward[itemStartCnt[newItemType[newItemCnt]] * REWARDITEMDATASIZE + newItemDetail[newItemCnt] * TOTALGRADE * REWARDITEMDATASIZE + newItemGrade[newItemCnt] * REWARDITEMDATASIZE + 3];

	newItemCnt++;

	ResetRectPoint();


	effect.color = COLOR_BLACK;

	for (i = NEUTRAL; i < ITEMOBJ; i++) {
		if (ao[i].type == OBJ_BOX && ao[i].status == false) {
			ao[i].status = true;
		}
	}

	if (winAniFrame == FPS / 2)
		GotoGacha();
	else if (winAniFrame >= FPS) {
		movie.type = MOVIE_MOVE;
		//movie.frame++;
		movie.start++;
	}

	winAniFrame++;
}

void Demo_Alpha(void)
{
	int i;
	if (demoFrame < 8)
		GammaImage(32 - demoFrame, 0, 1.0f, gScreenBuffer, gScreenLayer, false);
	else if (demoFrame > frameData[movie.start * DFLEN + 2] - 8)
		GammaImage(32 - (frameData[movie.start * DFLEN + 2] - demoFrame), 0, 1.0f, gScreenBuffer, gScreenLayer, false);
	else
		GammaImage(24, 0, 1.0f, gScreenBuffer, gScreenLayer, false);

	grayScale = 0;

	if (demoFrame < 16)
		SetAlpha(demoFrame * 2);
	else if (demoFrame > frameData[movie.start * DFLEN + 2] - 16)
		SetAlpha((frameData[movie.start * DFLEN + 2] - demoFrame) * 2);

	for (i = 0; i < 5; i++) {
		int idx = demoAlpha[(frameData[movie.start * DFLEN + 1] - EFFECT_ALPHA_0) * 5 + i];

		if (idx)
			CenterAlpha(DX / 2, DY / 2 + 16 * _2X * (i - 3), idx, FONT_LARGE, false, 1.0f, gScreenBuffer, gScreenLayer, false);
	}

	SetAlpha(32);

	if (frame % MOTIONDIV == 0)
		demoFrame++;

	if (demoFrame >= frameData[movie.start * DFLEN + 2]) {
		movie.type = MOVIE_MOVE;
		movie.frame++;
		movie.start++;
	}
}

void Demo_Narration(void)
{
	int x = xOffset + 16 * _2X;
	int y = 80 * _2X;
	int dx = DX - 32 * _2X;
	int dy = 16 * _2X + FONT_HEIGHT_LINE * 3;

	int textX = 32 * _2X;
	int textY = 80 * _2X;
	int textW = DX - 64 * _2X;
	float textZoom = 1.4f;

	//if (demoFrame < 32)
	//	SetAlpha(demoFrame);

	// 글씨를 적고
	//DrawFrame(x, y, dx, dy, FRAME_SHOPBALLOON, gScreenBuffer, gScreenLayer, false);

	SetFontColor(COLOR_WHITE);

	//if (demoFrame >= 32)
		FrameText(
			TEXTPTR(frameData[movie.start * DFLEN + 2]),
			textX,
			textY,
			textW,
			textLines,
			0,
			textZoom,
			gScreenBuffer,
			gScreenLayer,
			false
		);

		//LineTextSolid(frameData[movie.start * DFLEN + 2], x + 8 * _2X, y - 8 * _2X, dx - 16 * _2X, textZoom, gScreenBuffer, gScreenLayer, false);

	SetFontColor(COLOR_WHITE);

	// 알파값 복귀 프레임증가
	//SetAlpha(32);
	demoFrame++;

	// 종료
	//if (demoFrame >= FPS * 2) {
	//	movie.type = MOVIE_MOVE;
	//	movie.frame++;
	//	movie.start++;
	//}
}

void Demo_SetQuestPlayer(void)
{
	int distance = 0, j;

	//낚시꾼 예외처리

	ao[talk.obj].y += 2 * _2X;
	GetTile(&ao[talk.obj]);

	for (j = 1; j < 4; j++) {
		if (ao[talk.obj].dirX == LEFT) {
			if (mapInfoArray[mapInfoOff + ao[talk.obj].tileY2 * rw + ao[talk.obj].tileX1 - j] < TILE_BLOCK ||
				mapInfoArray[mapInfoOff + ao[talk.obj].tileY1 * rw + ao[talk.obj].tileX1 - j] >= TILE_BLOCK)
				break;
		}
		else {
			if (mapInfoArray[mapInfoOff + ao[talk.obj].tileY2 * rw + ao[talk.obj].tileX2 + j] < TILE_BLOCK ||
				mapInfoArray[mapInfoOff + ao[talk.obj].tileY1 * rw + ao[talk.obj].tileX2 + j] >= TILE_BLOCK)
				break;
		}

		distance += TSIZE * DIR(ao[talk.obj].dirX);
	}

	ao[talk.obj].y -= 2 * _2X;

	ao[raidPlayer].dirF = ao[raidPlayer].dirX = ao[talk.obj].dirX;

	ao[raidPlayer].dx = DIR(ao[raidPlayer].dirX) * 4 * _2X;
	whichPlayer = raidPlayer;
	demoPlayerX[raidPlayer] = ao[raidPlayer].dx;

	if (Abs(ao[raidPlayer].x + ao[raidPlayer].dx - ao[talk.obj].x) > Abs(distance)) {
		ao[raidPlayer].dirF = ao[raidPlayer].dirX = 1 - ao[talk.obj].dirX;

		AddPlayer(&ao[raidPlayer]);
		demoFrame = 0;

		switch (movie.index) {
		default:
			movie.type = MOVIE_SPREAD_RDM;
			break;
		}

		demoPlayerX[raidPlayer] = 0;
	}

	if (frame % MOTIONDIV == 0)
		demoFrame++;
}

int GatherPlayer(void)
{
	int i;

	for (i = DIANA; i < MAXX; i++) {
		if (ao[PLAYER + i].active) {
			ao[PLAYER + i].icon = 0;
			ao[PLAYER + i].dirF = ao[PLAYER + i].dirX = (ao[PLAYER + i].x > ao[PLAYER].x ? LEFT : RIGHT);
			demoPlayerX[PLAYER + i] = DIR(ao[PLAYER + i].dirX) * 4 * _2X;
			whichPlayer = PLAYERALL;
		}

		if (Abs(ao[PLAYER + i].x - ao[PLAYER].x) < 6 * _2X) {
			ao[PLAYER + i].active = false;
			demoPlayerX[PLAYER + i] = 0;
			memset(&ao[PLAYER + i], 0, sizeof(OBJECT));
		}
	}

	if (!ao[PLAYER + 0].active && !ao[PLAYER + 1].active && !ao[PLAYER + 2].active)
		return 1;
	else
		return 0;
}

void AfterAttack(OBJECT* pObj)
{
	int enemyTurn = turn;

	OBJECT* eObj = &ao[enemyTurn];

	option.gameControl = CONTROL_AUTO;
	arenaStatus = STATUS_PLAY;

	pObj->concentrate = 0;
	pObj->attack = false;
	screenDarken = false;
	pObj->currentSkill = -1;
	pObj->attackFrame = 0;
	pObj->continueAttack = false;
#ifdef ONEHEARTONEATTACK
	//autoPlay = false;
	if (autoPlay == true) {
		if ((ONLYATTACKMODE == false && enemyAttackPattern[ao[enemyTurn].type * ATTACKPATTERNTOTALDATASIZE + 2] > 0 && (drawHandle == MD_PLAY && (MC_knlCurrentTimeStamp() - ao[enemyTurn].coolTime >= enemyAttackPattern[ao[enemyTurn].type * ATTACKPATTERNTOTALDATASIZE + 1])))) {
			pObj->turnPosition = COMING;
		}
		else {
#ifdef WARIGARI
			pObj->turnPosition = COMING;
#else
			turn = NEUTRAL;
			if (drawHandle == MD_PLAY && ao[ENEMY].hp != 0 && JoyStickPressPossible()) BoxOpen();
			else {
				pObj->turnPosition = COMING;
			}
#endif
		}
	}
	else {
		pObj->turnPosition = COMING;
		//autoPlay = false;
	}
#endif


	systemRelease = false;
	PlayRelease(pObj);
	pObj->pDx = pObj->dx = 0;

	bar[BAR_ITEM].count = false;
	bar[BAR_ITEM].add = false;
	bar[BAR_ITEM].active = false;

	joyStickDir = LEFT;

	if (GetObjFromPtr(pObj) == raidPlayer && skillUsed > 0) {
		skillInfoFrame = SKILLREMAINEDFRAME;
		skillUsed = SKILLREMAINEDFRAME;
	}
}

void AfterDemo(void)
{
	int i, itemIndex;

	ReleaseCore();


#ifdef DEMOSKIP
	while (movie.start < movie.end) {
		DemoCore();

		i = TOTALOBJECT;

		do {
			i--;

			if (ao[i].active)
				MoveObj(&ao[i]);
		} while (i > 0);

		SetCamera();

		movie.frame++;

		if (movie.type == MOVIE_TALK) {
			movie.type = MOVIE_MOVE;
			movie.start++;
		}
		else if (movie.type == MOVIE_WIN || movie.type == MOVIE_WAITDARKSTONE) {

			DemoCore();
			return;
		}
	}

	for (i = PLAYER + 1; i <= LORA; i++) {
		if (ao[i].active == true && i != 3)
			memset(&ao[i], 0, sizeof(OBJECT));
	}
#endif

	//GotoPlay();

	isDemo = false;
	talk.obj = 0;

	movie.face = -1;

	for (i = ENEMY; i < ITEMOBJ; i++) {
		if (ao[i].active && ao[i].moveHandler == DEMOMOVE) {
			// 예외처리 - 캐릭터 하나 기준
			switch (ao[i].type) {
			case ENEMY_BAHAMUT:
				BahamutReady(&ao[i]);
				continue;
			}

			ao[i].moveHandler = enemyData[ao[i].type * ENEMYDATASIZE + ENEMYDATA_MOVEHANDLER];
			ao[i].etc = 0;
			ao[i].icon = 0;

		}
	}


	// 이벤트 끝나면 무조건 포커스 플레이어로.
	ao[raidPlayer].icon = 0;
	lenzFlag = false;

	SetRoom_Demo();
	SetRoom_Quest();


	robin.demoSeen[movie.index] = true;

	//효과음이니까
	if (curID > M_ENDING)
		TimerMusic();

	nameFrame = nameObj = curEnemyFrame = curEnemy = 0;

	if (touch)
		touchMode = TOUCH_PLAY;

	//데모신 끝나고 특수이벤트 처리
	switch (movie.index) {
	case DEMO_OPENING_PEACEFUL:
	case DEMO_OPENING_DARKKNIGHT:
	case DEMO_OPENING_PLUNDER:
	case DEMO_OPENING_WARNNING:
	case DEMO_OPENING_END:

	case DEMO_OPENING_BEGGAR:

	case DEMO_TUTORIAL_SEBASTIAN:
	case DEMO_TUTORIAL_PLAYER:
	case DEMO_TUTORIAL_ENEMY:
	case DEMO_TUTORIAL_JOYSTICK:
	case DEMO_TUTORIAL_JOKBO_COIN:
	case DEMO_TUTORIAL_JOKBO_COINBAG:
	case DEMO_TUTORIAL_JOKBO_HEART:
	case DEMO_TUTORIAL_JOKBO_QUEST:
	case DEMO_TUTORIAL_BOSS:
	case DEMO_TUTORIAL_JOKBO_BATTLE:
	case DEMO_TUTORIAL_JOKBO_RAID:



		memset(&currencyMarkArr, 0, sizeof(currencyMarkArr));
		memset(&currencyMark, 0, sizeof(currencyMark));
		memset(&itemMark, 0, sizeof(itemMark));
		memset(&cardMark, 0, sizeof(cardMark));
		memset(&rewardMark, 0, sizeof(rewardMark));
		memset(&boxMark, 0, sizeof(boxMark));

		fadeFrame = FPS;
		effect.color = false;
		//아이템을 먹여준다.

		SetDemo(movie.index + 1);
		switch (movie.index) {
		case DEMO_TUTORIAL_GETWEAPON:

			break;
		}
		break;
	default:
		switch (movie.index) {
		case DEMO_OPENING_BEGGAR:
			NewGame();

			break;
		}

		GotoPlay();
		break;
	}
}

void DemoCore(void)
{
	int i, j, k, obj;
	OBJECT* pObj;
	int collectionIdx;

	for (i = movie.start; i < movie.start + 1; i++) {
		const signed short* ssPtr = &frameData[i * DFLEN];

		if (movie.frame < *ssPtr)
			break;
		else if (movie.frame == *ssPtr) {
			movie.type = MOVIE_MOVE;
			obj = raidPlayer;

			if (*(ssPtr + 2) >= 30000) {
				movie.start++;

				if (*(ssPtr + 1) == EFFECT_TALK)
					movie.text++;

				ssPtr += 3;
				movie.frame = *ssPtr;
				continue;
			}
			else if (*(ssPtr + 2) >= 20000) {
				for (j = NEUTRAL; j <= ITEMOBJ - 1; j++) {
					if (ao[j].moveHandler == *(ssPtr + 2) - 20000) {
						obj = j;
						break;
					}
				}
			}

			else if (*(ssPtr + 2) >= 10000) {
				obj = *(ssPtr + 2) - 10000;
			}
			else if (*(ssPtr + 1) != EFFECT_NARRATION && *(ssPtr + 2) >= 5000) {
				movie.start++;

				if (*(ssPtr + 1) == EFFECT_TALK)
					movie.text++;

				ssPtr += 3;
				movie.frame = *ssPtr;
				continue;
			}
			else if (*(ssPtr + 2) >= 0) {
				for (j = PLAYER; j < TOTALOBJECT; j++) {
					if (*(ssPtr + 1) >= EFFECT_TALK
						&& !(*(ssPtr + 1) >= EFFECT_CHANGE_ETC && *(ssPtr + 1) < EFFECT_ERASEICON)
						&& (*(ssPtr + 2) == BULLET || *(ssPtr + 2) == PLAYERALL)) {
						obj = *(ssPtr + 2);
						break;
					}
					else if (ao[j].type == *(ssPtr + 2)) {
						if (*(ssPtr + 1) == EFFECT_REGENMONSTER && ao[j].active == true)
							continue;
						obj = j;
						break;
					}
				}
			}

			pObj = &ao[obj];

			DemoCore2(pObj, *(ssPtr + 1));

			switch (*(ssPtr + 1)) {
			case EFFECT_FADEIN://밝아짐
			case EFFECT_FADEOUT://어두워짐
				fadeFrame = (*(ssPtr + 1) == EFFECT_FADEIN ? -FPS : FPS);
				effect.color = 0;

				if (*(ssPtr + 2) == WHITE)
					fadeColor = 0xFFFFFF;
				else
					fadeColor = 0x000000;
				break;
			case EFFECT_SHAKETALK:
				talkShakeFrame = 7;
			case EFFECT_TALK:
			case EFFECT_MENUTALK:
				//말하게 하기
				movie.text++;
				SetFrameText(movie.text, 512, TEXTLINEPERPAGE, 1.0f);
				movie.talker = obj;
				movie.type = (frameData[i * DFLEN + 1] == EFFECT_TALK ? MOVIE_TALK : MOVIE_MENUTALK);

				if (frameData[i * DFLEN + 2] != BULLET)
					focus = obj;

				talk.obj = obj;

				keyHandle = MK_TALK;
				break;
			case EFFECT_WAVE:
				WaveControler();
				break;
			case EFFECT_FOCUS:
				focus = obj;
				break;
			case EFFECT_FOCUS_FAST:
				focus = obj;

				for (j = 20 - 1; j >= 0; j--)
					SetCamera();
				break;
			case EFFECT_JUMP:
			case EFFECT_SHORTJUMP:
				if (obj == PLAYERALL) {
					int k;
					for (k = PLAYER; k < PLAYERALL; k++) {
						whichPlayer = obj;
						ao[k].status = JUMP;
						if (*(ssPtr + 1) == EFFECT_JUMP)
							ao[k].jumpFrame = 1;
						else
							ao[k].jumpFrame = 3;
					}
				}
				else {
					pObj->status = JUMP;
					if (*(ssPtr + 1) == EFFECT_JUMP) {
						pObj->jumpFrame = 1;
					}
					else {
						pObj->jumpFrame = JUMPFRAME - 2;
						pObj->dx = DIR(pObj->dirX) * 4 * _2X;
					}
				}
				break;
			case EFFECT_CONTRASTDIR:
				if (obj == PLAYERALL) {
					int k;

					for (k = PLAYER; k < PLAYERALL; k++)
						ao[k].dirF = ao[k].dirX = 1 - ao[k].dirX;
				}
				else {
					if (pObj->etc != 6)	//손들고 있는 모션일때는 etc변경안함
						pObj->etc = 0;

					pObj->dirF = pObj->dirX = 1 - pObj->dirX;
				}
				break;
			case EFFECT_LOOKLEFT:
			case EFFECT_LOOKRIGHT:
				if (obj == PLAYERALL) {
					int k;

					for (k = PLAYER; k < PLAYERALL; k++) {
						ao[k].dirF = ao[k].dirX = *(ssPtr + 1) == EFFECT_LOOKLEFT ? LEFT : RIGHT;
					}
				}
				else {
					if (obj < PLAYERALL) {
						if (pObj->etc != 6)	//손들고 있는 모션일때는 etc변경안함
							pObj->etc = 0;
					}

					else {
						switch (pObj->type) {
						default:
							pObj->etc = 0;
						}
					}

					pObj->dirF = pObj->dirX = (*(ssPtr + 1) == EFFECT_LOOKLEFT ? LEFT : RIGHT);
				}
				break;
			case EFFECT_DEACTIVATE:
				if (*(ssPtr + 2) == PLAYERALL) {
					int k;

					for (k = PLAYER; k < PLAYERALL; k++)
						ao[k].active = false;

					break;
				}
				else
					pObj->active = false;
				break;
			case EFFECT_ACTIVATE:
				// 4번째 캐릭은 적용 안됨
				if (*(ssPtr + 2) == PLAYERALL) {
					int k;

					for (k = PLAYER; k < PLAYERALL; k++)
						ao[k].active = true;

					break;
				}
				else
					pObj->active = true;
				break;
			case EFFECT_ESCORT:
				ao[obj].moveHandler = ESCORTMOVE;
				break;
			case EFFECT_SETROOM:
				robinmap = *(ssPtr + 2);
				SetRoom();
				break;
			case EFFECT_GETITEM:
			case EFFECT_GIVEITEM:
			case EFFECT_QUEST:
			case EFFECT_FAILQUEST:
			case EFFECT_CLEARQUEST:
				DemoCore_Effect_GetItem(ssPtr);
				break;
				//case EFFECT_STOPMUSIC:
				//	Stop();
				//	break;
			case EFFECT_PLAYMUSIC:

				switch (*(ssPtr + 2)) {
				case M_SWORDHIT://칼맞음			//32
				case M_GUNHIT://총맞음			//33
				case M_BOOMERANGHIT://부메랑맞음		//34
				case M_LASER://레이저		//36
				case M_BUFF_PINK://핑크색버프	//38
				case M_BUFF_YELLOW://노란색버프	//39
				case M_BUFF_BLUE://파란색버프	//40
				case M_BUFF_RED://빨간색버프	//41
				case M_BANG://터지는소리	//42
				case M_KUNG:	//거대몬스터가 점프했다가 떨어지거나~(쿵)	//44
				case M_OPENDOOR:	//문열때 나는 소리	//45
					Vibration();
					break;
				}


				switch (*(ssPtr + 2)) {
				case M_SWORDHIT://칼맞음			//32
				case M_GUNHIT://총맞음			//33
				case M_BOOMERANGHIT://부메랑맞음		//34
					//PlayMusic(M_SWORDHIT);
					break;
				default:
					PlayMusic(*(ssPtr + 2));
					break;
				}

				break;
			case EFFECT_BOSSROOM:
				robin.bossRoom = (signed char)*(ssPtr + 2);

				if (bossRaidMode == true)
					PlayMusic(M_EVENT_FUNNY);
				else if (robin.bossRoom == true)
					PlayMusic(M_BOSS);
				else {
					switch (movie.index) {
					default:
						GotoGameOver();
						PlayMusic(M_LEVELUP);
					}
				}
				break;
			case EFFECT_REGENMONSTER:
				pObj->maxhp = pObj->hp = questRequestItemCntData[robin.quest + robin.subQuest];
				pObj->str = (robin.stage * TOTALROOM + robin.room + 1) * (10 + enemyData[pObj->type * ENEMYDATASIZE + ENEMYDATA_ADDHP]);
				pObj->mom = GetObjFromPtr(pObj);

				pObj->attr = 100;
				pObj->active = true;
				pObj->moveHandler = REGENMOVE;
				pObj->drawHandler = REGENDRAW;
				break;
			case EFFECT_WARPIN:
			case EFFECT_WARPOUT:
				movie.type = *(ssPtr + 1) == EFFECT_WARPIN ? MOVIE_WARPIN : MOVIE_WARPOUT;
				focus = obj;
				demoFrame = 0;
				PlayMusic(M_BUFF_YELLOW);
				break;
			case EFFECT_OBJSHAKE:
				movie.type = MOVIE_OBJSHAKE;
				talk.obj = obj;
				demoFrame = 0;
				break;
			case EFFECT_APPEAROBJ:
			case EFFECT_DISAPPEAROBJ:
				movie.type = *(ssPtr + 1) == EFFECT_APPEAROBJ ? MOVIE_APPEAROBJ : MOVIE_DISAPPEAROBJ;
				focus = obj;
				demoFrame = 0;
				PlayMusic(M_BUFF_YELLOW);
				break;
			case EFFECT_GAZEAROUND:
				movie.type = MOVIE_GAZEAROUND;
				talk.obj = obj;
				demoFrame = 0;
				break;
			case EFFECT_ATTACK:
				whichPlayer = obj;

				GetMotionPtr(pObj);

				pObj->attack = ATTACK_NORMAL;
				pObj->attackFrame = skillStartFrame[ATTACK_NORMAL];
				HitCountCheck(pObj);
				break;
			case EFFECT_NARRATION:
				movie.type = MOVIE_NARRATION;
				demoFrame = 0;
				SetFrameText(*(ssPtr + 2), 512, TEXTLINEPERPAGE, 1.0f);
				keyHandle = MK_TALK;
				return;
			case EFFECT_ZOOM:
				pObj->zoom = 2.0f;
				break;
			case EFFECT_LENZ:
				lenzFlag = (signed char)*(ssPtr + 2);
				break;
			case EFFECT_EQUIPALL:
				//SetDemoEquip(pObj, ITEM_SWORD, STAR5, GRADE_RARE);
				//SetDemoEquip(pObj, ITEM_HELM, STAR5, GRADE_EPIC);
				//SetDemoEquip(pObj, ITEM_ARMOR, STAR5, GRADE_EPIC);
				//SetDemoEquip(pObj, ITEM_GUNTLET, STAR5, GRADE_EPIC);
				//SetDemoEquip(pObj, ITEM_KILT, STAR5, GRADE_EPIC);
				//SetDemoEquip(pObj, ITEM_GREAVES, STAR5, GRADE_EPIC);
				collectionIdx = TOTAL_COLLECTIONS - 2;
				for (j = 0; j < COLLECTIONSITEMCNT; j++) {
					SetNpcEquipDetail(PLAYER, EQUIP_WEAPON + j, collectionData[collectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + j * COLLECTIONSDATASIZE + 0], collectionData[collectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + j * COLLECTIONSDATASIZE + 1], collectionData[collectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + j * COLLECTIONSDATASIZE + 2]);
				}
				break;
			case EFFECT_UNEQUIPALL:
				for (j = 0; j < EQUIP_NECK; j++) {
					UnEquipItem(pObj, &pObj->equip[i]);
				}
				//robin.inven[0].count = 0;//몽둥이 개수 0
				memset(robin.inven, 0, sizeof(robin.inven));

				for (j = 0; j < TOTALINVENTORY; j++) {
					robin.inven[j].type = EMPTY;
					for (k = 0; k < 12; k++)
						robin.inven[j].option[k][0] = EMPTYINT;
					for (k = 0; k < 6; k++)
						robin.inven[j].socket[k] = EMPTYINT;
				}
				break;
			case EFFECT_EQUIPONLYSWORD:
				SetDemoEquip(pObj, ITEM_SWORD, STAR1, GRADE_NORMAL);
				break;
			case EFFECT_SPREAD_MDR:
			case EFFECT_SPREAD_MRD:
			case EFFECT_SPREAD_DRM:
			case EFFECT_SPREAD_DMR:
			case EFFECT_SPREAD_RMD:
			case EFFECT_SPREAD_RDM:
				movie.type = *(ssPtr + 1) - EFFECT_SPREAD_MDR + MOVIE_SPREAD_MDR;
				demoFrame = 0;
				break;
			case EFFECT_ERASEICON:
				if (*(ssPtr + 2) == PLAYERALL) {
					int k;
					for (k = PLAYER; k < PLAYERALL; k++)
						ao[k].icon = 0;
					break;
				}
				pObj->icon = 0;
				break;
			case EFFECT_STOP:
				whichPlayer = obj;

				if (obj == PLAYERALL) {
					int k;

					for (k = PLAYER; k < PLAYERALL; k++) {
						ao[k].dx = 0;
						demoPlayerX[k] = ao[k].dx;
					}
				}
				else if (obj < PLAYERALL) {
					pObj->dx = 0;
					demoPlayerX[obj] = pObj->dx;
				}

				pObj->etc = 0;
				break;
			default:
				DemoCore_Default(pObj, obj, *(ssPtr + 1));
				break;
			case EFFECT_CHANGETOLEMTILE:
				ChangeTile(24, 15, 2, 3, *(ssPtr + 2));
				break;
			case EFFECT_CHANGEADELTILE:
				ChangeTile(5, 15, 2, 3, *(ssPtr + 2));
				break;
			case EFFECT_ALERT:
				infoFrame = 0;

				SetAlert(*(ssPtr + 2));
				break;
			case EFFECT_FRAMEUNSETBLEND:
				movie.type = MOVIE_FRAMEUNSETBLEND;
				focus = obj;
				demoFrame = 0;
				break;
			case EFFECT_ALPHA_0:
			case EFFECT_ALPHA_1:
			case EFFECT_ALPHA_2:
			case EFFECT_ALPHA_3:
			case EFFECT_ALPHA_4:
			case EFFECT_ALPHA_5:
			case EFFECT_ALPHA_6:
			case EFFECT_ALPHA_7:
			case EFFECT_ALPHA_8:
			case EFFECT_ALPHA_9:
				movie.type = MOVIE_ALPHA;
				demoFrame = 0;
				return;
			case EFFECT_WAITDARKSTONE:
				movie.type = MOVIE_WAITDARKSTONE;
				talk.obj = obj;
				demoFrame = 0;
				return;
			}

			//로라 위치 수정 하고, 퀘스트 ready상태로 만듬

			if (*(ssPtr + 1) != EFFECT_TALK && *(ssPtr + 1) != EFFECT_GETITEM && *(ssPtr + 1) != EFFECT_GIVEITEM && *(ssPtr + 1) != EFFECT_QUEST && *(ssPtr + 1) != EFFECT_CLEARQUEST && *(ssPtr + 1) != EFFECT_FAILQUEST)
				movie.start++;

		}
	}
}

void DemoCore2(OBJECT* pObj, int var)
{
	int i;

	switch (var) {
	case EFFECT_BLACK:
		//까만 화면
		effect.color = 0x000001;
		break;
	case EFFECT_WHITE:
		effect.color = 0xFFFFFF;
		break;
		//테트라쿤이 검은 안개를 뿌림
	case EFFECT_DARKFOG:
		effect.color = 0x9900FF;
		demoFrame = 0;
		break;
	case EFFECT_GRAY:
		effect.color = 0;
		effect.gray = true;
		break;
	case EFFECT_GRAYNULL:
		effect.gray = false;
		break;
	case EFFECT_MENU:
		movie.type = MOVIE_MENU;
		demoFrame = 0;

		if (touch)
			touchMode = TOUCH_GAMEMENU;
		break;
	case EFFECT_MOVELEFT_NPC:
		pObj->dirX = pObj->dirF = LEFT;
		pObj->etc = 1;
		break;
	case EFFECT_MOVERIGHT_NPC:
		pObj->dirX = pObj->dirF = RIGHT;
		pObj->etc = 1;
		break;
	case EFFECT_RUNLEFT_NPC:
		pObj->dirX = pObj->dirF = LEFT;
		pObj->etc = 2;
		break;
	case EFFECT_RUNRIGHT_NPC:
		pObj->dirX = pObj->dirF = RIGHT;
		pObj->dx = Abs(pObj->dx);
		pObj->etc = 2;
		break;
	case EFFECT_EMPTYFOCUS:
		focus = 255;
		break;
	case EFFECT_EMPTYFOCUS_FAST:
		focus = 255;

		for (i = 20 - 1; i >= 0; i--)
			SetCamera();
		break;
	case EFFECT_CHANGEGHOSTDRAW:
		pObj->drawHandler = GHOSTDRAW;
		break;
	case EFFECT_LONGJUMP:
		pObj->status = JUMP;
		pObj->jumpFrame = 0;
		break;
	case EFFECT_LOOKPLAYER:
		pObj->dirF = pObj->dirX = (pObj->x > ao[raidPlayer].x ? LEFT : RIGHT);
		pObj->dx = (1 - 2 * pObj->dirX) * 4 * _2X;//뒷걸음치게 하기
		break;
	case EFFECT_AGAINSTPLAYER:
		pObj->dirF = pObj->dirX = (pObj->x > ao[raidPlayer].x ? RIGHT : LEFT);
		break;
	case EFFECT_STOPMUSIC:
		Stop();
		break;
	case EFFECT_SHAKE:
		effect.shake = 2;

		PlayMusic(M_KUNG);
		break;
	case EFFECT_ERASEOBJECT:
		memset(pObj, 0, sizeof(OBJECT));
		break;
	case EFFECT_ENEMYDRAW:
		pObj->drawHandler = ENEMYDRAW;
		break;
	case EFFECT_HEADZOOMIN:
		pObj->head = 255;
		break;
	case EFFECT_PLAYER_PREPARE:
		AddPlayer(&ao[raidPlayer]);
		break;
	case EFFECT_GATHER_PLAYER:
		movie.type = MOVIE_GATHER_PLAYER;
		demoFrame = 0;
		break;
	case EFFECT_SLINGMOVE:
		pObj->moveHandler = SLINGMOVE;
		break;
	case EFFECT_APPEARBOSSMOVE:
		pObj->moveHandler = APPEARBOSSMOVE;
		break;
	case EFFECT_DEMOMOVE:
		pObj->moveHandler = DEMOMOVE;

		if (pObj->type != ENEMY_BAHAMUT
			|| pObj->type != ENEMY_BAHAMUT_RED
			|| pObj->type != ENEMY_BAHAMUT_BLUE
			|| pObj->type != ENEMY_BAHAMUT_PURPLE
			|| pObj->type != ENEMY_BAHAMUT_GREEN
			|| pObj->type != ENEMY_BAHAMUT_GOLD
			|| pObj->type != ENEMY_BAHAMUT_BLACK)
			pObj->etc = 0;
		break;
	case EFFECT_ENEMYMOVE:
		pObj->moveHandler = ENEMYMOVE;
		break;
	case EFFECT_GUARDMOVE:
		pObj->moveHandler = GUARDMOVE;
		pObj->frame = 0;
		pObj->mainFrame = 0;
		break;
	case EFFECT_GOLIMOVE:
		pObj->moveHandler = GOLIMOVE;
		pObj->frame = 0;
		pObj->mainFrame = 0;
		pObj->hp = pObj->maxhp = 200;
		break;
	case EFFECT_GUARDMOVE2:
		pObj->moveHandler = GUARDMOVE2;
		pObj->frame = 0;
		pObj->mainFrame = 0;
		pObj->maxhp = pObj->hp = 300;
		break;
	case EFFECT_SETQUEST_PLAYER:
		movie.type = MOVIE_SETQUEST_PLAYER;
		demoFrame = 0;
		break;
	case EFFECT_POISON:
		pObj->debuf[POISON] = 20;
		break;
	case EFFECT_CHANGEDEVILTILE:
		ChangeTile(18, 12, 2, 4, 50);
		break;
	case EFFECT_CHANGEDEVILTILE2:
		//ChangeTile(18, 12, 2, 4, 50);
		break;
	case EFFECT_RIDEGOLEM:
		RideGolem(pObj);
		break;
	case EFFECT_TAKEDOWNGOLEM:
		TakeDown();
		break;
	}
}

void DemoCore_Default(OBJECT* pObj, int obj, int var)
{
	int k;

	if (var >= EFFECT_SETTYPE) {
		pObj->type = var - EFFECT_SETTYPE;
		if (pObj->type < NPC_CAPTAIN)
			SetEnemy(pObj);	//타입에 따른 데이터 세팅
		else
			SetNpc(pObj);
	}
	else if (var >= EFFECT_MOTION) {
		if (obj == PLAYERALL) {
			for (k = PLAYER; k < PLAYERALL; k++)
				movie.robinMotion[k] = var - EFFECT_MOTION;
		}
		else if (obj < NEUTRAL)
			movie.robinMotion[obj] = var - EFFECT_MOTION;
		else
			movie.robinMotion[obj] = var - EFFECT_MOTION;

		whichPlayer = obj;
	}

	else if (var >= EFFECT_SETTILEX) {
		if (obj == PLAYERALL) {
			for (k = PLAYER; k < PLAYERALL; k++)
				ao[k].x = (var - EFFECT_SETTILEX);
		}
		else
			pObj->x = (var - EFFECT_SETTILEX);
	}
	else if (var >= EFFECT_SETTILEY) {
		if (obj == PLAYERALL) {
			for (k = PLAYER; k < PLAYERALL; k++) {
				ao[k].y = (var - EFFECT_SETTILEY);

			}
		}
		else
			pObj->y = (var - EFFECT_SETTILEY);
	}
	else if (var > EFFECT_MOVEDOWN)
		pObj->dy = var - EFFECT_MOVEDOWN;
	//위로이동
	else if (var > EFFECT_MOVEUP)
		pObj->dy = -(var - EFFECT_MOVEUP);
	//오른쪽 이동
	else if (var > EFFECT_MOVERIGHT) {
		whichPlayer = obj;

		if (obj == PLAYERALL) {
			for (k = PLAYER; k < PLAYERALL; k++) {
				ao[k].dirF = ao[k].dirX = RIGHT;
				ao[k].dx = (var - EFFECT_MOVERIGHT) * 2 / MOTIONDIV;
				demoPlayerX[k] = ao[k].dx;
			}
		}
		else {
			pObj->dirF = pObj->dirX = RIGHT;
			pObj->dx = (var - EFFECT_MOVERIGHT) * 2 / MOTIONDIV;

			if (obj < PLAYERALL)
				demoPlayerX[obj] = pObj->dx;
		}

		whichPlayer = PLAYERALL;
	}
	//왼쪽 이동
	else if (var > EFFECT_MOVELEFT) {
		whichPlayer = obj;

		if (obj == PLAYERALL) {
			for (k = PLAYER; k < PLAYERALL; k++) {
				ao[k].dirF = ao[k].dirX = LEFT;
				ao[k].dx = -(var - EFFECT_MOVELEFT) * 2 / MOTIONDIV;
				demoPlayerX[k] = ao[k].dx;
			}

		}
		else {
			pObj->dirF = pObj->dirX = LEFT;
			pObj->dx = -(var - EFFECT_MOVELEFT) * 2 / MOTIONDIV;

			if (obj < PLAYERALL)
				demoPlayerX[obj] = pObj->dx;
		}

		whichPlayer = PLAYERALL;
	}
	else if (var >= EFFECT_ICON) {
		if (obj == PLAYERALL) {
			for (k = PLAYER; k < PLAYERALL; k++)
				ao[k].icon = var - EFFECT_ICON;
		}
		else
			pObj->icon = var - EFFECT_ICON;
	}
	else if (var >= EFFECT_CHANGE_ETC) {
		switch (pObj->type) {
		case OBJ_DOOR:
			if (obj > NEUTRAL) {
				pObj->status = var - EFFECT_CHANGE_ETC;
				pObj->frame = 0;
				break;
			}// 아래 break없는것이 맞음.
		default:
			pObj->etc = var - EFFECT_CHANGE_ETC;
			pObj->frame = 0;
		}
	}
}

void DemoCore_Effect_GetItem(const signed short* ssPtr)
{
	movie.type = MOVIE_WIN;
	infoFrame = 0;

	switch (*(ssPtr + 1)) {
	case EFFECT_GETITEM:
	case EFFECT_GIVEITEM:
		infoType = *(ssPtr + 1) == EFFECT_GETITEM ? INFOTYPE_GETITEM : INFOTYPE_GIVEITEM;
		infoData = (unsigned char)*(ssPtr + 2);

		if (*(ssPtr + 1) == EFFECT_GETITEM) {
			switch (infoData) {
			case DEMOITEM_OPENING:
				rewardMark[0].type = ITEM_BOX;
				rewardMark[0].detail = BOX_INGAME;
				rewardMark[0].grade = GRADE_NORMAL;
				break;
			}
		}
		else {
			int itemIndex = TOTALINVENTORY;

			if (itemIndex < robin.count)
				//없애준다
				EraseItem(&robin.inven[itemIndex]);
		}
		break;
	case EFFECT_QUEST:
		infoType = INFOTYPE_QUEST;
		infoData = (unsigned char)*(ssPtr + 2);
		break;
	case EFFECT_CLEARQUEST:
		infoType = INFOTYPE_CLEARQUEST;
		infoData = (unsigned char)*(ssPtr + 2);

		break;
	case EFFECT_FAILQUEST:
		infoType = INFOTYPE_FAILQUEST;
		infoData = (unsigned char)*(ssPtr + 2);
	}

	if (*(ssPtr + 1) == EFFECT_FAILQUEST)
		PlayMusic(M_INN);
	else
		PlayMusic(M_LEVELUP);
}


void SetDemoEquip(OBJECT* pObj, int type, int detail, int grade)
{
	EquipItem(pObj, &robin.inven[itemStartCnt[type] + detail * TOTALGRADE + grade]);
}

void SetDemo(int index)
{
	int i;
	//OBJECT* pObj = &ao[PLAYER];

	ReleaseCore();

	//pObj->dx = 0;
	//pObj->playerRun = false;

	//활강, 다람쥐 풀어주기
	//if (pObj->status == GLIDE)
	//	pObj->status = FALL;

	curEnemy = 0;
	curEnemyFrame = 0;
	movie.type = MOVIE_MOVE;
	movie.index = index;
	movie.start = demoData[index * DDLEN + 5];
	movie.end = demoData[index * DDLEN + 6];
	movie.text = demoData[index * DDLEN + 4] - 1;
	movie.frame = 0;
	drawHandle = MD_DEMO;
	keyHandle = MK_DEMO;
	//pObj->attack = null;
	//pObj->attackFrame = null;
	returnFrame = null;
	//pObj->currentSkill = null;
	//pObj->canMagnet = null;
	// 디아나 화염방사 스킬시전중이었으면 꺼주기
	//pObj->flamer = false;

	for (i = ENEMY; i < NEUTRAL; i++) {
		if (ao[i].active) {
			ao[i].icon = null;

			if ((ao[i].moveHandler == ENEMYMOVE || ao[i].moveHandler == ENEMYMOVETURN) &&
				(ao[i].type != ENEMY_MAMMOTH
					|| ao[i].type != ENEMY_MAMMOTH_RED
					|| ao[i].type != ENEMY_MAMMOTH_BLUE
					|| ao[i].type != ENEMY_MAMMOTH_PURPLE
					|| ao[i].type != ENEMY_MAMMOTH_GREEN
					|| ao[i].type != ENEMY_MAMMOTH_GOLD
					|| ao[i].type != ENEMY_MAMMOTH_BLACK)
				&&
				(ao[i].type != ENEMY_BAHAMUT
					|| ao[i].type != ENEMY_BAHAMUT_RED
					|| ao[i].type != ENEMY_BAHAMUT_BLUE
					|| ao[i].type != ENEMY_BAHAMUT_PURPLE
					|| ao[i].type != ENEMY_BAHAMUT_GREEN
					|| ao[i].type != ENEMY_BAHAMUT_GOLD
					|| ao[i].type != ENEMY_BAHAMUT_BLACK)
				&& ao[i].type != NPC_SOUL) {
				ao[i].moveHandler = DEMOMOVE;
				ao[i].etc = 0;
			}
		}
	}

	//@@ 테스트 필요
	//데모신 들어갈 때 주인공 효과 없애주기
	effect.alpha = 0;

	isDemo = true;

	memset(boomerangAway, 0, sizeof(boomerangAway));

	if (escort.active == false) {
		for (i = PLAYER + 1; i < ENEMY; i++)
			ao[i].active = false;
	}

	//pObj->motion = 0;
	//pObj->attack = 0;
	//pObj->attackFrame = 0;
	//pObj->name = TEXT_MONSTERNAME_START + pObj->type;

	//memset(pObj->debuf, 0, sizeof(pObj->debuf));

	if (robin.demoSeen[index] == false && demoData[index * DDLEN + 1] != TRIGGER_ALWAYS_PLACE)
		robin.demoSeen[index] = true;

	memset(&dmgInfo, 0, sizeof(dmgInfo));
	memset(&imgText, 0, sizeof(imgText));

	switch (index) {
	case DEMO_OPENING_BEGGAR:
		//pObj->x = 260 * _2X;
		//pObj->y = 288 * _2X;
		SetHero();
		SetBattleCrew();
		//InitMenu();
		break;
	}
#ifdef DEBUG
	//demoSkip = false;

	//if (demoSkip == true) {
	//	while (movie.start < DEMO_0_FRAME82) {
	//		DemoCore();

	//		if (ao[PLAYER].active)
	//			PlayerMove(&ao[PLAYER]);

	//		for (i = TOTALOBJECT; i >= 0; i--) {
	//			if (ao[i].active)
	//				MoveObj(&ao[i]);
	//		}

	//		if (movie.type == MOVIE_TALK || movie.type == MOVIE_WIN || movie.type == MOVIE_ALPHA || movie.type == MOVIE_NARRATION || movie.type == MOVIE_PLAYER_PREPARE) {
	//			movie.type = MOVIE_MOVE;
	//			movie.start++;
	//		}

	//		robin.playtime++;
	//		movie.frame++;
	//	}

	//	demoSkip = false;
	//}
#endif
}

void SetTalk(void)
{
	int i, j;
	signed short* ssPtr;

	for (i = 0; i < movie.dCount; i++) {
		// 본래 이것.
		if (ao[talk.obj].type == demoData[movie.movies[i] * DDLEN + 2] &&
			demoData[movie.movies[i] * DDLEN + 1] == TRIGGER_TALK) {
			//디버그용
			//if (ao[talk.obj].type == d.demoData[i * DDLEN + 2] && ((d.demoData[i * DDLEN + 1] == TRIGGER_TALK && !GetBit(robin.demoSeen, i)))) {
			switch (movie.movies[i]) {
			DEFAULT:
			default:
				//해당 데모신을 안봤을때만 데모신 걸리게.
				if (robin.demoSeen[movie.movies[i]])
					continue;

				//시간제 퀘스트 중에는 다른 시간제 퀘스트를 받을 수 없다.
				if (timeFrame > 0) {

				}

				if (robin.count >= robin.maxInven) {

				}

				SetDemo(movie.movies[i]);
				return;
			}
		}
	}

	//SetTalkEnd:
		//@@부하처리
		//아이템을 기준으로 데모신을 걸때 퀘스트 완료 혹은 기타 등


	SetTalk_Movie();
}

void SetTalk_Movie(void)
{
	int i;
	signed short* ssPtr;

}

void SetTalk2(int textIdx)
{
	ao[raidPlayer].motion = PO_C0_N0;
	ReleaseCore();
	ao[raidPlayer].playerRun = false;
	ao[raidPlayer].dx = 0;
	movie.text = textIdx;
	SetFrameText(movie.text, 512, TEXTLINEPERPAGE, 1.0f);
	movie.type = MOVIE_TALK;
	movie.end = -1;
	drawHandle = MD_DEMO;
	keyHandle = MK_TALK;

	if (touch)
		touchMode = TOUCH_TALK;
}