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
		else if (ao[i].dead == true && ao[i].moveHandler == REGENMOVE)
			RegenMove(&ao[i]);
	} while (i > 0);

	SetCamera();

#ifdef DEBUG
	if (demoSkip == 0)
#endif
	DrawScreen(DX / 2 + scX, DY / 2 + scY[MENU_PLAY], screenZoom);

	//HUD(StatusDraw/InfoDraw/카드마크 등)를 대화신/캐릭터 초상화보다 먼저 그려서, 나레이션/TALK 창이
	//항상 HUD 위(가장 바깥 레이어)에 보이도록 한다.

	switch (movie.index) {
	case DEMO_OPENING_PEACEFUL:
	case DEMO_OPENING_DARKKNIGHT:
	case DEMO_OPENING_PLUNDER:
	case DEMO_OPENING_WARNNING:
	case DEMO_OPENING_END:
		break;
	default:

		StatusDraw(xOffset, 0, 1.0f);

		InfoDraw();

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

					BarDraw(&bar[i], bar[i].zoom2);
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

					BarDraw(&bar[i], bar[i].zoom);
				}
				else
					BarDraw(&bar[i], bar[i].zoom);
			}
		}

		if (effect.color2) {
			SetAlpha(24);
			MemRect(xOffset, DY, DX - 2 * xOffset, DY, effect.color);
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

						EventMenuDraw(&robin.gameEvent[i]);

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
								PlayMusic(M_COIN);
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

						EventMenuDraw(&robin.gameEvent[i]);


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

		GNBDraw(xOffset, DY - (GNBHEIGHT - GNB_INIT_HEIGHT));

		if (curMenu == MENU_PLAY && JoyStickPressPossible() == true)
			EventScheduler();

		if (turn >= ENEMY && turn < NEUTRAL)
			EnemySequenceDraw();
		else
			AttackSequenceDraw();

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

					BarDraw(&bar[i], bar[i].zoom2);
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

					BarDraw(&bar[i], bar[i].zoom);
				}
				else
					BarDraw(&bar[i], bar[i].zoom);
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
					DrawSkillCard(controlMark[i].attackType, controlMark[i].attackStr, xOffset + controlMark[i].x - (float)ROULETTECARDSIZE_X * controlMark[i].zoom2 / 2, controlMark[i].y + floatOffsetY + (float)ROULETTECARDSIZE_Y * controlMark[i].zoom2 / 2, controlMark[i].zoom2);
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
					DrawSkillCard(controlMark[i].attackType, controlMark[i].attackStr, xOffset + controlMark[i].x - (float)ROULETTECARDSIZE_X * controlMark[i].zoom / 2, controlMark[i].y + floatOffsetY + (float)ROULETTECARDSIZE_Y * controlMark[i].zoom / 2, controlMark[i].zoom);
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
				DrawTextStr(skillStr3, xOffset + DX / 2 - width / 2 + 8 * _2X + SKILLICONSIZE * 2 + 4 * _2X, STATUSWIN_Y + SKILLTEXT_Y, 2);
			else
				DrawTextStr(ringStr, xOffset + DX / 2 - width / 2 + 8 * _2X + SKILLICONSIZE * 2 + 4 * _2X, STATUSWIN_Y + SKILLTEXT_Y, 2);


			int collectionIdx = GetCollectionIdx(ao[PLAYER].equip[EQUIP_WEAPON].type, ao[PLAYER].equip[EQUIP_WEAPON].detail, ao[PLAYER].equip[EQUIP_WEAPON].grade);
			int enemyIdx;

			//if (curSkill < 100)//스킬이면
			//	DrawSkillIcon(skillData[SKILLDATASIZE * curSkill + 5], xOffset + DX / 2 - width / 2 + 8 * _2X, STATUSWIN_Y + SKILLTEXT_Y + 8 * _2X, 2, gScreenBuffer, gScreenLayer, false);
			if (skillData[curSkill * SKILLDATASIZE + 0] == SUMMON) {
				enemyIdx = skillData[curSkill * SKILLDATASIZE + 1];

				float zoom = 2.0f;
				SetSectionClip(xOffset + DX / 2 - width / 2 + 8 * _2X, STATUSWIN_Y + SKILLTEXT_Y + 8 * _2X, (float)(SKILLICONSIZE)*zoom, (float)(SKILLICONSIZE)*zoom, false);
				ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, xOffset + DX / 2 - width / 2 + 8 * _2X + (float)(SKILLICONSIZE)*zoom / 2 - (float)40 * _2X / 2 * zoom, STATUSWIN_Y + SKILLTEXT_Y + 8 * _2X + (float)(-SKILLICONSIZE + 8 * _2X) * zoom * 3 / 4, SHADOW_IMG, zoom / 2);

				DrawCmfDetail(enemyData[enemyIdx * ENEMYDATASIZE + ENEMYDATA_CMF], enemySkillIconPos[3 * enemyIdx + 0], xOffset + DX / 2 - width / 2 + 8 * _2X + (float)(SKILLICONSIZE)*zoom / 2 + (float)(enemySkillIconPos[3 * enemyIdx + 1]) * zoom, STATUSWIN_Y + SKILLTEXT_Y + 8 * _2X + (float)(-SKILLICONSIZE + enemySkillIconPos[3 * enemyIdx + 2]) * zoom, LEFT, zoom / 2, false, false);

				UnSectionClip(false);
			}
			else
				DrawSkillIcon(skillData[SKILLDATASIZE * curSkill + 5], xOffset + DX / 2 - width / 2 + 8 * _2X, STATUSWIN_Y + SKILLTEXT_Y + 8 * _2X, 2);
		}


		ActiveHelpDraw();

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
				DrawGoldNum(ao[turn].hitCount, hitCountPosX, hitCountPosY, RIGHT, false, false, true, 1.2f * zoom);
				DrawGoldAlpha(hitCountPosX + 4 * _2X, hitCountPosY - 4 * _2X, ALPHA_HIT, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false);
			}
		}

		if (attackDelay == 0 && menuResult == 0 && ((drawHandle == MD_PLAY && curMenu == MENU_PLAY) || drawHandle == MD_BATTLE || drawHandle == MD_RAID || drawHandle == MD_BOSSRAID || drawHandle == MD_BOSSRAID || drawHandle == MD_DEMO) && popUp[0].active == false) {
			robin.playtime++;
			arenaItemFrame++;
			turnFrame++;
		}
		else {
			robin.playtime++;
		}

		//popMenu
		//popUpCnt(실제 열린 메뉴 팝업 수)가 0일 땐 이 블록이 할 일이 없는데도 매 프레임 돌면서
		//popUpFrame을 건드려서, Demo_Talk()가 같은 popUpFrame으로 관리하는 대화창 점프/텍스트리빌
		//연출과 충돌해 계속 리셋되는 원인이 됐다. 실제 팝업이 열려있을 때만 돌게 막는다.
		if (drawHandle != MD_NEWCOLLECTION && drawHandle != MD_NEWCARD && popUpCnt > 0) {
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
			NewsDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 * zoom, zoom);
			break;
		case MENU_GIFTS:
			GiftDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 * zoom, zoom);
			break;
		case MENU_LEADERBOARD:
			break;
		case MENU_FRIENDS:
			GuildEventDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 * zoom, zoom);
			break;
		case MENU_INVITEFREINDS:

			break;
		case MENU_CALENDAR://데일리 리워드
			CalendarDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)(POPUPWINDOWSIZE_Y / 2) * zoom, zoom);
			break;
		case MENU_SETTING:
			OptionDraw(DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 * zoom, zoom);
			break;

		case MENU_LIST:
			GameMenuDraw(xOffset + (DX - GAMEMENUWIN2_X) / 2, DY / 2 + GAMEMENUWIN2_Y / 2, 1.0f);
			break;
		case MENU_GAMEEVENT:

			switch (robin.gameEvent[curEventIdx].type) {
			case EVENTTYPE_QUEST:
				QuestMenuDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 * zoom, zoom);
				break;
			case EVENTTYPE_PVP:
				PvpQuestMenuDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 * zoom, zoom);
				break;
			case EVENTTYPE_SHOP:

				break;
			case EVENTTYPE_DEBTDISCOUNT:
				DiscountMenuDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 * zoom, zoom);
				break;
			case EVENTTYPE_DOUBLE:
				//EventMenuDraw()
				break;
			case EVENTTYPE_BOSSRAID:
				GoldQuestMenuDraw(xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2) * zoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 * zoom, zoom);
				break;
			case EVENTTYPE_TOUCHGAME:

				break;
			}
			break;
		case MENU_PLAY:
			GameMenuDraw(xOffset, DY, 1.0f);

			break;
			//메뉴
		case MENU_STAGEINFO:
			//StageInfoDraw(robin.stage, robin.room, false, false, xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2), POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2, zoom, gScreenBuffer, gScreenLayer, false);
			break;
		}
		break;

	}

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
		MemRect(0, DY, DX, DY, COLOR_BLACK);
		DrawImage(
			imgW, imgH,
			0, 0,
			imgX, imgY,
			false, false, false, false, false,
			1.0f,
			sprite[OP0_IMG + movie.index - DEMO_OPENING_PEACEFUL],
			OP0_IMG + movie.index - DEMO_OPENING_PEACEFUL);
		break;
	case DEMO_TUTORIAL_INIT:
		if (curtainFrame > 0)
			DrawCmfDetailShadow(DEMO_HELPER, PO_C93_W0 + walkFrame[frame / MOTIONDIV % 4], xOffset + HELPER_DEMO_GAP_X - curtainFrame * _2X, STATUSWIN_Y2 + HELPERGAP_Y, LEFT, talkerZoom);
		else if (curtainFrame < 0)
			DrawCmfDetailShadow(DEMO_HELPER, PO_C93_W0 + walkFrame[frame / MOTIONDIV % 4], xOffset + HELPER_DEMO_GAP_X + curtainFrame * _2X, STATUSWIN_Y2 + HELPERGAP_Y, RIGHT, talkerZoom);
		else {
			DrawCmfDetailShadow(DEMO_HELPER, frame / MOTIONDIV / MOTIONDIV % 4, xOffset + HELPER_DEMO_GAP_X, STATUSWIN_Y2 + HELPERGAP_Y, RIGHT, talkerZoom);
			SetRectPoint(xOffset + HELPER_DEMO_GAP_X - 2 * ITEMICONSIZE, STATUSWIN_Y2 + HELPERGAP_Y + 3 * ITEMICONSIZE, ITEMICONSIZE * 4, ITEMICONSIZE * 4, TOUCH_FUNC_SKIPDEMO);

			//SKIP MARK
			MemRectBoth(xOffset + HELPER_DEMO_GAP_X - 24 * _2X, STATUSWIN_Y2 + HELPERGAP_Y - 8 * _2X, 48 * _2X, 11 * _2X, COLOR_BLACK, COLOR_WHITE);
			CenterAlpha(xOffset + HELPER_DEMO_GAP_X, STATUSWIN_Y2 + HELPERGAP_Y - 10 * _2X, ALPHA_SKIP, FONT_SMALL, false, 1.0f);
		}

		break;
	case DEMO_TUTORIAL_SEBASTIAN:
		switch (movie.start) {
		case DEMO_TUTORIAL_SEBASTIAN_FRAME0:
			DrawCmfDetailShadow(DEMO_HELPER, PO_C93_W0 + walkFrame[frame / MOTIONDIV % 4], xOffset + HELPER_DEMO_GAP_X - curtainFrame * _2X, STATUSWIN_Y2 + HELPERGAP_Y, LEFT, talkerZoom);
			break;
		}
		break;
	case DEMO_TUTORIAL_FIRSTKILL:	//2:첫 처치 보상(상자/하트/동료) 설명
	case DEMO_TUTORIAL_CREWMENU:	//3:동료 메뉴 장착 안내
	case DEMO_TUTORIAL_SECONDKILL:	//4:재공격 보상(하트/동료/장비) 설명
	case DEMO_TUTORIAL_EQUIP:		//5:동료 자동장착+장비 수동장착 안내
	case DEMO_TUTORIAL_HEARTBET:	//6:하트 베팅/3배공격 설명
	case DEMO_TUTORIAL_ROULETTE:	//7:룰렛 개방 연출/설명
	case DEMO_TUTORIAL_ROULETTE_LIVE:	//8:룰렛 실전 관전 안내
	case DEMO_TUTORIAL_BOSS:		//9:보스전 안내
		DrawCmfDetailShadow(DEMO_HELPER, frame / MOTIONDIV / MOTIONDIV % 4, xOffset + 32 * _2X, STATUSWIN_Y2 + HELPERGAP_Y, RIGHT, talkerZoom);
		break;
	}

	if (movie.type >= MOVIE_MENU) {

		menuFrame++;
		menuWinFrame++;
	}

	//대사 중 연타하면 TalkKey()가 탭마다 movie.start++를 하기 때문에 movie.end를 그냥 지나칠 수 있다.
	//예전처럼 ==로 보면 movie.start는 단조증가라 이 조건이 두 번 다시 참이 되지 않아서,
	//AfterDemo()가 영영 호출되지 않고 DemoCore()가 다음 블록들의 행(EFFECT_WAVE 몬스터 스폰,
	//EFFECT_TALK 등)을 잘못된 movie.index 상태로 계속 실행하다가 frameData[] 밖까지 넘어갔다.
	//>=로 두면 넘겨도 그 시점에 블록이 정상 종료된다.
	//단 movie.end < 0은 SetTalk2()가 쓰는 "데모 블록이 아닌 단독 대사" 경로다(movie.end = -1).
	//예전 ==에서는 절대 성립하지 않던 조건이라 그대로 두지 않으면 대사가 뜨자마자 AfterDemo()가 불린다.
	if (movie.end >= 0 && movie.start >= movie.end) {
		talk.obj = talk.clr = talk.temp = null;
		AfterDemo();

		return;
	}

	if (effect.gray)
		GammaImage(32, 6, 1.0f);

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
			DrawObj(&ao[focus]);
			SetAlpha(32);
			DrawPlayer(&ao[raidPlayer], 2000 + LEVELUP_FRONT0 + demoFrame, ao[focus].x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ao[focus].y - ry + OBJIMGGAP, ao[focus].dirF, ao[focus].zoom, false, false, false);
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
		DrawObj(&ao[focus]);
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

	bool back = false;
	battleZoom = 1.0f;

	if (battleStartFrame > 0) {
		//battleZoom = 1.0f * (bar[BAR_HEART].zoom + battleFrameZoom[(BATTLESTARTFRAME - battleStartFrame)]);

		//ResetRectPoint();
		//SetAlpha((int)(BATTLESTARTFRAME - battleStartFrame));
		//MemRect(0, DY, DX, DY, COLOR_BLACK, gScreenBuffer, gScreenLayer, false);
		//SetAlpha(32);
		battleStartFrame--;
		//dioramaZoom += battleZoom / 30;

		//if (battleStartFrame == 0)
		//	GotoBattleLoading();
	}

	//robin.playtime++;

#ifdef DEBUG
	//memset(debugStr, 0, sizeof(debugStr));
	//MC_knlSprintk(debugStr, "|dmap:%d/x:%d/y:%d/dx:%d/dy:%d", movie.index, movie.start, movie.frame, menuDepth, curMenu);
	//CenterTextStr(debugStr, DX / 2, DY - 12);
#endif

	//if (curtainFrame) {
	//	TheaterDraw(gScreenBuffer, gScreenLayer, false);
	//}
}

//인터랙티브 전투 튜토리얼이 진행 중인지(튜토리얼 방에서 아직 끝나지 않았는지).
bool IsTutorialPlaying(void)
{
	return robinmap == MAP_DIORAMA_TOLEM && !robin.demoSeen[DEMO_TUTORIAL_END];
}

//대사를 띄워둔 채 플레이어가 특정 버튼을 직접 눌러야 다음으로 넘어가는 튜토리얼 안내 대사인지.
//맞으면 눌러야 하는 터치기능과 강조할 바를 돌려준다.
//터치 제한, 스팟라이트, DrawHand, 대사 대기 처리가 모두 같은 기준을 봐야 해서 여기에 모아 둔다.
//
//데모 블록 번호(movie.index)가 아니라 지금 떠 있는 대사(movie.text)로 판정한다.
//movie.text는 SetDemo()가 헤더값으로 리셋하고 EFFECT_TALK마다 ++하는 별도 커서라 블록 진행과
//항상 1:1로 붙어 있지 않고, 플레이어가 반응하는 것도 블록 번호가 아니라 읽고 있는 문장이다.
bool GetTutorialTalkTarget(int textIdx, int* touchFunc, int* barIdx)
{
	int func;
	int idx;

	switch (textIdx) {
	case TEXT_OPENING_5_1:			//"때마침 몬스터가 나타났네요! 공격버튼을 눌러주세요!!"
	case TEXT_TUTORIAL_SECONDKILL:	//"다시 공격해보자! 이번엔 하트와 동료, 장비를 얻을 수 있다."
		func = TOUCH_FUNC_ATTACK;
		idx = BAR_PLAY;
		break;
	case TEXT_TUTORIAL_FIRSTKILL:	//"상자에서 동료를 획득하셨네요? 그럼 동료를 전투에 참가시켜볼까요??"
		func = TOUCH_FUNC_POPUP_CREWLIST;
		idx = BAR_CREW;
		break;
	default:
		return false;
	}

	if (touchFunc)
		*touchFunc = func;

	if (barIdx)
		*barIdx = idx;

	return true;
}

//안내 대사에서 강조할 바의 버튼 사각형(왼쪽, 윗변, 폭, 높이).
//BarDraw()가 SetRectPoint()에 넘기는 값과 같아야 스팟라이트/손 위치가 실제 터치영역과 맞는다.
static void GetTutorialTalkRect(int barIdx, float* x, float* y, float* w, float* h)
{
	BAR* barP = &bar[barIdx];
	float zoom = barP->zoom;

	switch (barIdx) {
	case BAR_CREW:
		*x = xOffset + barP->x - (float)(MAINMENU_X / 2) * zoom;
		*y = barP->y + (float)(MAINMENU_Y / 2 + 12 * _2X) * zoom;
		*w = (float)(MAINMENU_X)*zoom;
		*h = (float)(MAINMENU_Y + 16 * _2X) * zoom;
		break;
	default:	//BAR_PLAY
		*x = xOffset + barP->x;
		*y = barP->y;
		*w = (float)ATTACKBUTTONWIDTH * zoom;
		*h = (float)ATTACKBUTTONHEIGHT * zoom;
		break;
	}
}

//튜토리얼: 동료 메뉴에서 새로 얻은 동료 카드를 눌러 상세보기로 들어가야 하는 단계인지.
//맞으면 그 카드의 터치기능을, 아니면 0을 돌려준다.
//대사가 떠 있는 단계가 아니라 "메뉴가 열려 있는 동안"의 안내라 GetTutorialTalkTarget()과 별개다.
//단계 완료 표시는 robin.demoSeen[DEMO_TUTORIAL_CREWMENU]를 쓴다. 그 데모 블록은 이제
//아무도 부르지 않아(FIRSTKILL 체인을 끊었다) 이 플래그가 비어 있고, 의미도 "동료 메뉴 단계를
//마쳤다"로 그대로 들어맞는다.
int GetTutorialCrewCardTouchFunc(void)
{
	int i;

	if (IsTutorialPlaying() == false)
		return 0;

	if (robin.demoSeen[DEMO_TUTORIAL_CREWMENU])
		return 0;

	//동료 리스트가 열려 있고 아직 상세보기로 들어가지 않은 상태에서만
	if (curMenu != MENU_CREW || menuDepth != 0)
		return 0;

	//세바스찬이 아닌 첫 동료 = 상자에서 새로 얻은 동료
	for (i = 0; i < TOTALINVENTORY; i++) {
		if (robin.inven[i].type == ITEM_CREW && robin.inven[i].detail != CREW_SEBASTIAN && robin.inven[i].lv > 0)
			return TOUCH_FUNC_ITEMDETAIL + i;
	}

	return 0;
}

//튜토리얼에서 지금 눌러야 하는 터치기능을 돌려준다. -1이면 제한하지 않는다.
//프레임 시작(Core.cpp의 touchIndex 초기화 지점)에서 한 번 정해야 한다. Demo_Talk()에서
//정하면 BarDraw()처럼 그보다 먼저 도는 곳이 이미 등록해 둔 터치영역이 새어나간다.
int GetTutorialTouchFunc(void)
{
	//동료 메뉴 안내는 컷씬이 아니라 메뉴가 열린 상태(MD_PLAY + 팝업)에서 돈다.
	int crewCardFunc = GetTutorialCrewCardTouchFunc();

	if (crewCardFunc)
		return crewCardFunc;

	if (drawHandle != MD_DEMO)
		return TUTORIAL_TOUCH_FREE;

	//튜토리얼 컷씬이 아니면(오프닝 등 일반 데모) 손대지 않는다.
	if (movie.index < DEMO_TUTORIAL_INIT || movie.index > DEMO_TUTORIAL_END)
		return TUTORIAL_TOUCH_FREE;

	//여기부터는 튜토리얼 컷씬 진행 중이다. 기본은 "아무것도 안 눌림"이다.
	//EFFECT_TUTORIAL_INITBAR가 바를 만드는 몇 프레임 동안 버튼의 터치영역이 잠깐
	//살아나서 컷씬 도중에 눌리던 것도 이걸로 막힌다.
	if (movie.type != MOVIE_TALK && movie.type != MOVIE_MENUTALK)
		return TUTORIAL_TOUCH_NONE;

	if (textPage <= 0 || textFrame < textStringLength[textPage - 1])
		return TUTORIAL_TOUCH_NONE;

	//버튼 안내 대사. 눌러야 하는 그 버튼 외에는 전부 막는다.
	int touchFunc;

	if (GetTutorialTalkTarget(movie.text, &touchFunc, nullptr))
		return touchFunc;

	return TUTORIAL_TOUCH_NONE;
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
		DrawEffect(EFFECT_DEMOTALK_ARROW0 + Abs(4 - frame % 8), ao[i].x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - ao[i].y - ry + OBJIMGGAP, 0, false, 1.0f);

	DrawCmfPopUp(ao[i].cmf, movie.text, 0 * _2X, DY - GNBHEIGHT, DX, 88 * _2X, DX - 120 * _2X, 6, false, 1.0f, RIGHT);

	//인터랙티브 전투 튜토리얼: 공격을 안내하는 대사는 시간이 지났다고 저절로 넘어가면 안 된다
	//(예전엔 텍스트가 끝나고 2초 뒤 자동으로 컷씬을 종료시켜서, 플레이어가 누르기도 전에 실전투로
	//넘어가 공격 연출이 바로 시작되는 것처럼 보였다). 대사는 그대로 띄워둔 채 대기하고,
	//플레이어가 실제 공격버튼을 눌렀을 때만 TalkKey()가 다음 단계로 넘겨준다.
	//공격버튼(BAR_PLAY)의 터치영역은 BarDraw()에서 touchDisable == false일 때만 등록되므로,
	//이 대사가 떠 있는 동안에는 터치를 열어둬야 버튼을 누를 수 있다.
	int talkTouchFunc;
	int talkBarIdx;

	if (GetTutorialTalkTarget(movie.text, &talkTouchFunc, &talkBarIdx) && textFrame >= textStringLength[textPage - 1]) {
		touchDisable = false;

		//눌러야 할 버튼만 밝게 남기고 나머지를 어둡게 덮는다. 사각형은 BarDraw()가
		//SetRectPoint()에 넘기는 것과 같은 값이라 스팟과 실제 터치영역이 정확히 겹친다.
		float bx, by, bw, bh;
		float pulse = 1.0f + sinf((float)frame * 0.1f) * 0.06f;	//숨쉬듯 반경이 오르내린다

		GetTutorialTalkRect(talkBarIdx, &bx, &by, &bw, &bh);

		float spotX = bx + bw / 2;
		float spotY = by - bh / 2;
		float spotSize = Max(bw, bh);

		//공격버튼은 DrawAttackButton()이 ani일 때 손을 직접 그리지만, 나머지 바는 안 그린다.
		//여기서 그려줘야 안내하는 버튼마다 포인터가 붙는다.
		if (talkBarIdx != BAR_PLAY)
			DrawHand(bx - (float)4 * _2X, by + (float)4 * _2X, robin.playtime / MOTIONDIV, 1.2f);

		SetSpotlight(spotX, spotY,
			spotSize * 0.6f * pulse, spotSize * 1.4f * pulse, 0.25f);

		//대화신은 같이 노출되어야 하므로 대화창 영역은 암전에서 뺀다.
		//바로 위 DrawCmfPopUp()에 넘긴 사각형과 같은 값이다.
		SetSpotlightKeepRect(0 * _2X, DY - GNBHEIGHT, DX, 88 * _2X, 12 * _2X);
	}

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
		GammaImage(32 - demoFrame, 0, 1.0f);
	else if (demoFrame > frameData[movie.start * DFLEN + 2] - 8)
		GammaImage(32 - (frameData[movie.start * DFLEN + 2] - demoFrame), 0, 1.0f);
	else
		GammaImage(24, 0, 1.0f);

	grayScale = 0;

	if (demoFrame < 16)
		SetAlpha(demoFrame * 2);
	else if (demoFrame > frameData[movie.start * DFLEN + 2] - 16)
		SetAlpha((frameData[movie.start * DFLEN + 2] - demoFrame) * 2);

	for (i = 0; i < 5; i++) {
		int idx = demoAlpha[(frameData[movie.start * DFLEN + 1] - EFFECT_ALPHA_0) * 5 + i];

		if (idx)
			CenterAlpha(DX / 2, DY / 2 + 16 * _2X * (i - 3), idx, FONT_LARGE, false, 1.0f);
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
			textZoom);

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

	ReleaseCore(false);


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

	case DEMO_TUTORIAL_INIT:

	//DEMO_TUTORIAL_FIRSTKILL/SECONDKILL/ROULETTE는 보상 설명 뒤 바로 다음 안내 컷씬으로 이어진다.
	//DEMO_TUTORIAL_SEBASTIAN과 나머지(CREWMENU/EQUIP/HEARTBET/ROULETTE_LIVE/BOSS)는 실전투/실메뉴 조작으로
	//넘겨야 하므로 default(GotoPlay/ResumeTutorialPlay) 경로를 타도록 이 목록에서 제외한다 - 실전투 중
	//다음 컷씬 복귀는 robin.demoSeen[]을 확인하는 별도 트리거(Func_Combat.cpp 사망 훅, Func_Input.cpp 장착 훅)가 담당한다.
	//DEMO_TUTORIAL_FIRSTKILL은 여기서 제외한다. 이 대사("상자에서 동료를 획득하셨네요?")는
	//플레이어가 동료 바(BAR_CREW)를 눌러야 넘어가고, 그 터치가 동료 메뉴를 직접 연다.
	//체인으로 다음 컷씬을 띄우면 버튼을 누를 새도 없이 넘어가 버린다.
	case DEMO_TUTORIAL_SECONDKILL:
	case DEMO_TUTORIAL_ROULETTE:



		memset(&currencyMarkArr, 0, sizeof(currencyMarkArr));
		memset(&currencyMark, 0, sizeof(currencyMark));
		memset(&itemMark, 0, sizeof(itemMark));
		memset(&cardMark, 0, sizeof(cardMark));
		memset(&rewardMark, 0, sizeof(rewardMark));
		memset(&boxMark, 0, sizeof(boxMark));

		//DEMO_TUTORIAL_INIT -> DEMO_TUTORIAL_SEBASTIAN은 같은 방/캐릭터로 이어지는 연속 장면이라
		//여기서 fadeFrame을 세팅하면 화면이 순간적으로 어두워졌다 1초간 서서히 밝아지는 페이드가
		//끼어들어 "화면이 깜빡이며 리셋되는 것처럼" 보인다. 오프닝 장면 전환(실제로 배경이 바뀜)에는
		//필요하므로 DEMO_TUTORIAL_INIT만 제외한다.
		if (movie.index != DEMO_TUTORIAL_INIT)
			fadeFrame = FPS;
		effect.color = false;
		//아이템을 먹여준다.

		SetDemo(movie.index + 1);
		break;
	default:

		//인터랙티브 전투 튜토리얼: DEMO_TUTORIAL_INIT의 EFFECT_SETROOM에서 이미 MAP_DIORAMA_TOLEM으로
		//방을 로드해뒀기 때문에(loadedMap==robinmap), 여기서는 GotoPlay(false)로 강제 리로드를 꺼서
		//SetRoom()의 ao[] 전체 memset이 아예 실행되지 않게 한다 - 컷씬 중 스폰한 몬스터가 그대로 남는다.
		//최초 1회(DEMO_TUTORIAL_SEBASTIAN)만 정식 GotoPlay()로 방에 진입하고, 그 이후의 튜토리얼
		//복귀는 ResumeTutorialPlay()로 가볍게 처리한다.
		if (movie.index == DEMO_TUTORIAL_SEBASTIAN)
			GotoPlay(false);
		else
			ResumeTutorialPlay();

		//Play()의 지역명/START 인트로를 건너뛴다. 이 구간이 systemKey를 강제로 지워서
		//공격버튼 입력이 먹지 않았다(자세한 내용은 SkipPlayIntro() 주석 참고).
		SkipPlayIntro();

		//인터랙티브 전투 튜토리얼: 몬스터는 정식 wave[] 데이터/WaveControler()로 스폰한다(타입/좌표/
		//점프연출/SaveGame()까지 실제 게임과 동일한 경로를 타고, 체력만 SetEnemy()에서 robin.waveIdx
		//기준으로 낮춘다 - Func_Map.cpp 참고). 원하는 몬스터 타입이 있는 wave[] 행(waveIdx)을 직접
		//골라서 슬롯0만 열어 재사용한다(웨이브 순번 의미는 무시: 0=SNAIL, 5=ONEEYE, 6=SKELETON).
		//슬롯 세팅은 반드시 SetTutorialWave()를 쓴다 - 나머지 슬롯을 막지 않으면 매 프레임 연속으로
		//스폰되면서 InitBar/SaveGame이 반복된다(자세한 내용은 SetTutorialWave() 주석 참고).
		//SetHero()의 착지 트리거를 안 타서 waveStatus가 저절로 WAVESTATUS_PLAY가 안 되므로 여기서
		//직접 켜야 WaveControler()가 매프레임 돈다 - touchDisable 자동 해제도 이걸 통해 이루어진다.
		switch (movie.index) {
		case DEMO_TUTORIAL_SEBASTIAN:
			//바 초기화는 DEMO_TUTORIAL_INIT의 EFFECT_TUTORIAL_INITBAR에서 처리하므로 여기서 하지 않는다.
			//몬스터는 컷씬 중간(FRAME3의 EFFECT_WAVE, SetDemo()가 준비해둔 waveIdx=0)에서 이미
			//스폰됐고, 바로 위 GotoPlay(false)가 SetRoom()의 강제 리로드를 꺼뒀으므로 ao[]가
			//memset되지 않아 그 몬스터가 그대로 살아있다 - 재스폰 불필요, 웨이브를 닫고 waveStatus만 켠다.
			CloseTutorialWave();
			waveStatus = WAVESTATUS_PLAY;
			touchDisable = true;
			tutorialWaitingEnemyLand = true;
			break;
		case DEMO_TUTORIAL_CREWMENU:
			SetTutorialWave(0);		//SNAIL
			waveStatus = WAVESTATUS_PLAY;
			touchDisable = true;
			tutorialWaitingEnemyLand = true;
			break;
		case DEMO_TUTORIAL_HEARTBET:
			SetTutorialWave(5);		//ONEEYE
			waveStatus = WAVESTATUS_PLAY;
			touchDisable = true;
			tutorialWaitingEnemyLand = true;
			break;
		case DEMO_TUTORIAL_ROULETTE_LIVE:
			SetTutorialWave(6);		//SKELETON
			waveStatus = WAVESTATUS_PLAY;
			touchDisable = true;
			tutorialWaitingEnemyLand = true;
			break;
		case DEMO_TUTORIAL_BOSS:
			//보스는 일반 wave[] 순환과 성격이 달라(robin.bossRoom류 별도 체계) 지금은 기존 커스텀
			//스폰을 그대로 둔다. 대신 WaveControler()가 일반 몬스터를 끼워 넣지 못하게 웨이브는 닫는다.
			CloseTutorialWave();
			touchDisable = true;
			tutorialWaitingEnemyLand = true;
			SpawnTutorialEnemy(ENEMY_CASTLE_BOSS4, 5000);	//TODO: 강제 룰렛 결과(가장 센 동료 스킬)로 한방킷 되도록 밸런스 확인
			break;
		default:
			//몬스터를 스폰하지 않는 단계(EQUIP)는 기다릴 이유가 없으니 바로 터치를 풀어준다.
			touchDisable = false;
			tutorialWaitingEnemyLand = false;
			break;
		}
		break;
	}
}

void SetTutorialWave(int waveIdx)
{
	int i;

	//인터랙티브 전투 튜토리얼: 정식 wave[] 데이터로 "딱 한 마리만" 스폰시키기 위한 슬롯 세팅.
	//WaveControler()는 robin.waveActive[robin.curWaveIdx] == false인 슬롯을 스폰하고 curWaveIdx만
	//올릴 뿐, robin.waveTimeStamp를 갱신하지 않는다. 그래서 waveTimeStamp를 0으로 두면
	//(현재시각 - 0 >= 지연시간)이 모든 슬롯에서 항상 참이 되어, 남은 슬롯까지 매 프레임 하나씩
	//연달아 튀어나온다. 스폰 1회마다 InitBar(BAR_ENEMYHP)/BackUpEnemyObj()/SaveGame()가 돌기 때문에
	//"가만히 놔둬도 초기화가 반복되는" 것처럼 보였다.
	//슬롯0만 열어두고 나머지는 이미 스폰한 것으로 막아두면, waveTimeStamp가 0이어도 한 마리만 나온다.
	robin.waveIdx = waveIdx;
	robin.curWaveIdx = 0;

	for (i = 0; i < MAXWAVEENEMY; i++)
		robin.waveActive[i] = true;

	robin.waveActive[0] = false;

	//슬롯0은 지연 없이 바로 나와야 하므로 0으로 둔다(나머지 슬롯은 위에서 이미 막았다).
	robin.waveTimeStamp = 0;
}

void CloseTutorialWave(void)
{
	int i;

	//이번 튜토리얼 단계의 몬스터를 이미 스폰해둔 경우(컷씬 중 EFFECT_WAVE 등) WaveControler()가
	//추가로 스폰하지 못하게 웨이브를 완전히 닫는다.
	robin.curWaveIdx = GetMaxWaveCnt();

	for (i = 0; i < MAXWAVEENEMY; i++)
		robin.waveActive[i] = true;
}

//인터랙티브 전투 튜토리얼: 컷씬에서 실전투로 넘어올 때 Play()의 "지역명 / START" 인트로 연출을
//통째로 건너뛴다.
//
//GotoPlay()는 areaFrame = INFOFRAME을 걸어두는데, Play()는 그 값이 0이 되는 프레임과
//이어서 세팅되는 arenaFrame(= INFOFRAME * 2)이 0이 되는 프레임에서 각각
//  systemKey = null; key_released = true;              (areaFrame == 0)
//  systemRelease = systemKey = null; ReleasePlayer();  (arenaFrame == 0)
//를 실행한다(Func_Battle.cpp의 areaFrame/arenaFrame 블록 참고).
//즉 실전투 진입 직후 수십 프레임 동안은 입력이 강제로 지워져서 공격버튼을 눌러도 먹지 않고,
//그 사이 캐릭터/모션 재설정이 겹쳐 전투가 시작되지 않은 것처럼 보인다.
//튜토리얼은 컷씬에서 이미 상황 설명을 끝냈으므로 이 인트로가 필요 없다.
//인트로가 끝나는 시점에 하던 마무리 처리는 여기서 직접 해준다.
void SkipPlayIntro(void)
{
	int i;

	//인트로 첫 프레임(areaFrame == INFOFRAME)에 하던 일: 살아있는 적의 모션을 다시 잡아준다.
	//InitMotion()은 cmd_m_crash[cmf][motion * 8]에서 피격박스(cx/cy/cpx/cpy)와 공격박스
	//(ax/ay/apx/apy)를 zoom을 곱해 채우는 함수라, 이걸 건너뛰면 스폰 시점 모션 기준의 낡은
	//박스가 그대로 남아 AttackCrash()의 겹침 판정이 어긋난다(공격은 나가는데 안 맞음).
	for (i = ENEMY; i < NEUTRAL; i++) {
		if (ao[i].active == true)
			InitMotion(&ao[i]);
	}

	infoFrame = 0;
	infoText = 0;
	areaFrame = 0;
	arenaFrame = 0;

	if (loadRoulette == true) {
		turn = PLAYER;
		attackSequence = ATTACKSEQUENCE_READY;
		loadRoulette = false;
		initControlerFrame = ROULETTESPREADTIME;
	}
	else
		initControlerFrame = 1;

	touchIdleFrame = 0;
	idleHelpCnt = 0;

	keyHandle = MK_PLAY;
}

void ResumeTutorialPlay(void)
{
	//정식 GotoPlay()는 room을 리로드하며 ao[]를 통째로 초기화하기 때문에, 같은 플레이 세션 안에서
	//반복되는 튜토리얼 컷씬->실전투 복귀에는 쓸 수 없다(직전에 스폰한 몬스터가 사라짐). 여기서는
	//실전투로 되돌아가는 데 필요한 최소한(모드 전환)만 처리한다.
	drawHandle = MD_PLAY;
	keyHandle = MK_PLAY;
	arenaStatus = STATUS_PLAY;

	//AttackObj()는 맨 첫 줄이 "if (isDemo) return 0;"이라, 여기가 true로 남으면 데미지 계산 전에
	//조용히 0을 반환해서 모든 공격이 무효가 된다.
	isDemo = false;
}

void SpawnTutorialEnemy(int enemyType, long long hp)
{
	//WaveControler()(Func_Map.cpp)를 참고해서 만들었다. 실제 웨이브 몬스터와 똑같이
	//RegenEnemy()로 스폰해서 RegenMove()의 점프-등장 연출(붕 뜨면서 커졌다가 착지)을 그대로 타게 하고,
	//착지 시점(frame==FPS/2)에 RegenMove가 자동으로 moveHandler를 ENEMYMOVETURN(MD_PLAY 기준)으로
	//바꿔주므로 별도로 강제할 필요가 없다. 직접 SetEnemy+active=true로 즉석 배치하던 이전 방식은
	//점프 연출이 전혀 없어서 몬스터가 "그냥 나타나는" 것처럼 보였다.
	int i;
	OBJECT* pObj = nullptr;

	for (i = ENEMY; i < NEUTRAL; i++) {
		if (!ao[i].type && ao[i].active == false) {
			pObj = &ao[i];
			break;
		}
	}

	if (pObj == nullptr)
		return;

	int x = setEnemyPos[robin.castle * 2 * MAXWAVEENEMY + 0];
	int y = setEnemyPos[robin.castle * 2 * MAXWAVEENEMY + 1];

	RegenEnemy(pObj, enemyType, x, y, LEFT);

	pObj->defaultZoom = pObj->zoom = MONSTERZOOM;
	pObj->mom = GetObjFromPtr(pObj);

	//RegenMove()가 착지 시점에 pObj->hp = pObj->maxhp로 재설정하므로 maxhp만 정확히 맞춰두면 된다.
	pObj->maxhp = pObj->hp = hp;

	//InitBar(BAR_BOSSHP)는 max를 GetTotalWaveHp(robin.waveIdx)로 채우는데, 튜토리얼 몬스터는 실제
	//wave[] 데이터와 무관해서 이 값이 안 맞는다(0이면 빨간 바가 아예 안 그려짐) - 여기서 실제 스폰
	//HP를 더해준다. 여러 마리가 나올 수 있으므로 덮어쓰지 않고 누적한다.
	bar[BAR_BOSSHP].max += hp;

	//WaveControler()가 스폰 마지막에 하는 것과 동일하게 dead=true/active=false로 둬야 한다.
	//매 프레임 오브젝트 갱신 루프(Func_Battle.cpp의 "else if (dead==true && moveHandler==REGENMOVE) RegenMove(...)")
	//가 이 조건을 보고서야 RegenMove()를 틱해준다 - 이게 없으면 점프 연출이 아예 시작되지 않고
	//오브젝트가 가만히 멈춰있기만 한다("생성될 때까지 타이밍을 기다리는" 부분이 여기서 처리된다).
	pObj->dead = true;
	pObj->active = false;
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

					//히어로는 0번(주인공)만 활성화
					ao[PLAYER].active = true;

					//크루는 실제 보유한 인원(crewCnt)까지만 활성화 - 나머지 빈 슬롯까지 켜면
					//DrawDiorama의 그림자 루프가 위치/타입이 없는 빈 슬롯까지 그려버린다.
					for (k = CREW; k < CREW + crewCnt; k++)
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
			case EFFECT_TUTORIAL_REWARD:
				DemoCore_Effect_TutorialReward(ssPtr);
				break;
			case EFFECT_TUTORIAL_INITBAR:
				DemoCore_Effect_TutorialInitBar();
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


void DemoCore_Effect_TutorialReward(const signed short* ssPtr)
{
	//demoItem[]의 한 행(NPC, type, detail, grade, count)을 그대로 GetItem()에 넘겨 확정 보상을 지급한다.
	//랜덤 상자 오픈 연출(Demo_Win, boxCardItem 계열)을 타지 않으므로 튜토리얼처럼 결과가 항상 같아야 하는
	//구간에서 사용한다.
	int idx = *(ssPtr + 2);
	int type = demoItem[idx * 5 + 1];
	int detail = demoItem[idx * 5 + 2];
	int grade = demoItem[idx * 5 + 3];
	int count = demoItem[idx * 5 + 4];

	GetItem(type, 1, detail, grade, count, false);
}

void DemoCore_Effect_TutorialInitBar(void)
{
	InitBar(BAR_GOLD);
	InitBar(BAR_CROWN);
	InitBar(BAR_MEDAL);
	InitBar(BAR_SHIELD);
	InitBar(BAR_CREW);
	InitBar(BAR_EQUIP);
	InitBar(BAR_CASTLE);
	InitBar(BAR_MAINSHOP);
	InitBar(BAR_HEART);
	InitBar(BAR_STAR);
	//BAR_HEARTBET/BAR_PLAY는 여기서 InitBar하지 않는다. BAR_ROULETTE가 활성화되면 RouletteDraw()가
	//곧바로 호출되고, 그 인트로 팝 애니메이션이 끝나는 시점(Func_Roulette.cpp)에 이미 InitBar(BAR_HEARTBET)/
	//InitBar(BAR_PLAY)를 호출한다. 여기서도 부르면 바가 두 번 초기화된다.
	InitBar(BAR_ROULETTE);

	InitBar(BAR_BOSSHP);
	//InitBar(BAR_BOSSHP)는 max를 GetTotalWaveHp(robin.waveIdx)(실제 웨이브 기준값, 수천 단위)로 채우는데
	//튜토리얼은 실제 웨이브와 무관하다. 0으로 강제 리셋해서 이후 SpawnTutorialEnemy()의 max += hp가
	//튜토리얼 몬스터 체력만으로 정확히 채워지게 한다.
	bar[BAR_BOSSHP].max = 0;
}

void SetDemoEquip(OBJECT* pObj, int type, int detail, int grade)
{
	EquipItem(pObj, &robin.inven[itemStartCnt[type] + detail * TOTALGRADE + grade]);
}

void SetDemo(int index)
{
	int i;
	//OBJECT* pObj = &ao[PLAYER];

	ReleaseCore(false);

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
		for (i = PLAYER + 1; i < ENEMY; i++) {
			//크루(ao[CREW..CREW+MAXCREW))는 끄지 않는다.
			//오브젝트 갱신 루프는 "active면 MoveObj / dead && REGENMOVE면 RegenMove" 두 갈래뿐이라
			//(Func_Battle.cpp, Func_Demo.cpp), 이미 자리에 서 있던 크루
			//(active=true / dead=false / CREWMOVE)를 여기서 꺼버리면 두 갈래 어디에도 걸리지 않아
			//되살릴 주체가 없어진다 - 컷씬을 한 번 거치면 성 위의 세바스찬이 영영 사라졌다.
			//(예전에는 SetBattleCrew()가 매번 전원을 REGENMOVE로 다시 만들어서 우연히 되살아났고,
			//그게 "동료를 얻을 때마다 전원이 다시 등장하는" 증상의 원인이었다)
			if (i >= CREW && i < CREW + MAXCREW)
				continue;

			ao[i].active = false;
		}
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
	case DEMO_TUTORIAL_INIT:
		//pObj->x = 260 * _2X;
		//pObj->y = 288 * _2X;
		SetHero();
		SetBattleCrew();
		//InitMenu();
		break;
	case DEMO_TUTORIAL_SEBASTIAN:
		//인터랙티브 전투 튜토리얼: 이 블록 FRAME3의 EFFECT_WAVE가 아직 drawHandle==MD_DEMO인 컷씬
		//도중에 WaveControler()를 호출해서 몬스터를 스폰한다(정식 wave[] 데이터 사용, 체력은
		//SetEnemy()에서 robin.waveIdx 기준으로 낮춤 - Func_Map.cpp 참고). 그 EFFECT_WAVE보다 먼저
		//여기서 슬롯을 준비해둔다. waveIdx=0은 SNAIL이 있는 행.
		//SetTutorialWave()가 슬롯0 외의 슬롯을 막아주므로, 컷씬이 끝나고 waveStatus가
		//WAVESTATUS_PLAY로 켜져도 나머지 웨이브가 줄줄이 스폰되지 않는다.
		SetTutorialWave(0);
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
	ReleaseCore(false);
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