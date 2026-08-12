#include "Core.h"
#include "Data.h"
#include "Func.h"
#include "Text.h"

// Battle 관련 함수
void Play(void)
{
	int i, j, k;
	int gap;
	int totalPlayer = realPlayerCnt;
	int itemType;
	int itemDetail, itemGrade;
	ITEM* it;
	OBJECT* eObj = &ao[ao[PLAYER].target];
	int x, y;

	int startX;
	int startY;
	float zoom;

	//인터랙티브 전투 튜토리얼: Func_Combat.cpp의 몬스터 사망 훅이 예약해둔 다음 컷씬을 여기서 시작한다.
	//사망 연출(VANISHMOVE) -> 상자 드롭 -> 상자 열기(GotoGacha) -> 보상 획득이 전부 끝나고 플레이
	//화면이 조용해졌을 때만 넘어가야, 사망 시점에 바로 SetDemo()를 불러 그 연출들이 잘려나가던
	//문제가 생기지 않는다. 가챠 중에는 drawHandle이 MD_GACHA라 이 조건 자체가 성립하지 않는다.
	if (tutorialPendingDemo != -1 && drawHandle == MD_PLAY && curMenu == MENU_PLAY
		&& attackSequence == ATTACKSEQUENCE_READY
		&& attackDelay == 0 && sequenceDelay == 0
		&& popUpCnt == 0 && curtainFrame == 0 && fadeFrame == 0) {
		bool sceneBusy = false;

		//바닥에 떨어진 상자/아이템 오브젝트가 아직 남아있으면 기다린다.
		for (i = ITEMOBJ; i < TOTALOBJECT; i++) {
			if (ao[i].active) {
				sceneBusy = true;
				break;
			}
		}

		//죽는 연출(VANISHMOVE) 중인 몬스터가 남아있어도 기다린다.
		for (i = ENEMY; !sceneBusy && i < NEUTRAL; i++) {
			if (ao[i].type != 0 && ao[i].active)
				sceneBusy = true;
		}

		if (!sceneBusy) {
			int nextDemo = tutorialPendingDemo;

			tutorialPendingDemo = -1;
			SetDemo(nextDemo);

			return;
		}
	}

	//튜토리얼 안내 대사에서 누른 버튼(동료 바 등)의 동작을 여기서 처리한다.
	//TalkKey()가 예약해 둔 터치기능을 실제 눌린 것과 똑같이 흘려보낸다 - touchFunc()가
	//systemKey를 세우고 PlayKey()가 그 키로 팝업을 연다.
	if (tutorialPendingTouchFunc && drawHandle == MD_PLAY && popUpCnt == 0) {
		int pendingFunc = tutorialPendingTouchFunc;

		tutorialPendingTouchFunc = 0;

		//동료 메뉴를 여는 안내였다면, 새 동료 카드를 누를 때까지 안내를 이어간다.
		if (pendingFunc == TOUCH_FUNC_POPUP_CREWLIST)
			tutorialCrewGuide = true;

		touchFunc(pendingFunc);
		PlayKey(raidPlayer);
		systemKey = null;
	}

	//DEBUG: 튜토리얼 진행 상태 추적용 임시 오버레이. 원인 확인되면 제거.
	if (robinmap == MAP_DIORAMA_TOLEM) {
		char dbgStr[256];

		sprintf(dbgStr, "reload=%d seq=%d arena=%d wave=%d aDly=%d tDis=%d | info=%d area=%d arenaF=%d",
			gDebugSetRoomReloadCount, attackSequence, arenaStatus, waveStatus, attackDelay, touchDisable,
			infoFrame, areaFrame, arenaFrame);
		DrawTextStr(dbgStr, 10 * _2X, DY - 60 * _2X, 0.7f);


		//crewCnt / 예약공격 / 턴 / 각 캐릭터의 준비 상태.
		//pend=1인데 공격이 안 나가면 crew나 enemy 중 준비가 안 된 쪽이 원인이다.
		sprintf(dbgStr, "crewCnt=%d pend=%d turn=%d totT=%d | P(act=%d mv=%d) C0(act=%d mv=%d) E(act=%d mv=%d)",
			crewCnt, tutorialAttackPending, turn, totalTurn,
			ao[PLAYER].active, ao[PLAYER].moveHandler,
			ao[CREW].active, ao[CREW].moveHandler,
			ao[ENEMY].active, ao[ENEMY].moveHandler);
		DrawTextStr(dbgStr, 10 * _2X, DY - 74 * _2X, 0.7f);

		//AttackCrash() 판정 입력값.
		//AttackCrash(공격자, 대상)은 맨 앞에서 "공격자.ax == 0 || 대상.cx == 0"이면 즉시 false다.
		//그 다음 공격박스(x+apx, y+apy, ax, ay)와 피격박스(PxlLeft/Up/Right/Down = x+cpx, y+cpy, cx, cy)의
		//겹침을 본다. 두 박스 모두 InitMotion()이 cmd_m_crash[cmf][motion*8]에 zoom을 곱해 채운다.
		//따라서 ax=0(공격 모션 프레임이 아님) / cx=0(피격 박스 없음) / zoom=0 중 하나면 절대 안 맞는다.
		//총알을 찾아서 같이 찍는다.
		int dbgBullet = 0;
		for (i = BULLET; i < ENEMYUSEROBJ; i++) {
			if (ao[i].active) {
				dbgBullet = i;
				break;
			}
		}

		sprintf(dbgStr, "P(ax=%d ay=%d mo=%d atk=%d x=%d y=%d) B%d(ax=%d mo=%d x=%d y=%d) E(cx=%d cy=%d mo=%d zm=%d x=%d y=%d hp=%d/%d)",
			(int)ao[PLAYER].ax, (int)ao[PLAYER].ay, ao[PLAYER].motion, ao[PLAYER].attack, (int)ao[PLAYER].x, (int)ao[PLAYER].y,
			dbgBullet, (int)ao[dbgBullet].ax, ao[dbgBullet].motion, (int)ao[dbgBullet].x, (int)ao[dbgBullet].y,
			(int)ao[ENEMY].cx, (int)ao[ENEMY].cy, ao[ENEMY].motion, (int)(ao[ENEMY].zoom * 100), (int)ao[ENEMY].x, (int)ao[ENEMY].y,
			(int)ao[ENEMY].hp, (int)ao[ENEMY].maxhp);
		DrawTextStr(dbgStr, 10 * _2X, DY - 88 * _2X, 0.6f);
	}

	//if (drawHandle == MD_PLAY)
	JOKBOGAP = JOKBOGAP_INIT;
	//else if (drawHandle == MD_BATTLE)
	//	JOKBOGAP = -52 * _2X;


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

	if (/*curEnemyFrame > 0 && */curEnemy > 0) {
		//curEnemyFrame--;

		if (/*curEnemyFrame == 0 || */ao[curEnemy].active == false || ao[curEnemy].drawHandler == null) {
			curEnemyFrame = null;
			curEnemy = null;
		}
	}

	if (explainFrame > 0) {
		explainFrame--;

		if (explainFrame == 0)
			explainText = 0;
	}

	//지역명표시
	if (infoFrame > 0) {
		infoFrame--;

		if (infoFrame == 0) {
			infoText = 0;
		}
	}
	else if (areaFrame > 0) {
		if (areaFrame == INFOFRAME)
		{
			for (i = ENEMY; i < NEUTRAL; i++) {
				if (ao[i].active == true) {
					if (ao[i].type == ENEMY_CASTLE2
						|| ao[i].type == ENEMY_CASTLE2_RED
						|| ao[i].type == ENEMY_CASTLE2_BLUE
						|| ao[i].type == ENEMY_CASTLE2_PURPLE
						|| ao[i].type == ENEMY_CASTLE2_GREEN
						|| ao[i].type == ENEMY_CASTLE2_GOLD
						|| ao[i].type == ENEMY_CASTLE2_BLACK)
						ao[i].motion = 0;

					InitMotion(&ao[i]);
				}
			}

			if (loadRoulette == true) {
				LoadRoulette();

			}
		}

		if (curtainFrame == 0) {
			areaFrame--;
			//전투신 돌입시 줌이 작아질때
			if (drawHandle == MD_BATTLE) {
				dioramaZoom -= 0.5f;
				if (dioramaZoom < DIORAMAZOOM_BATTLE + dioramaZoomGap)
					dioramaZoom = DIORAMAZOOM_BATTLE + dioramaZoomGap;
			}
		}

		switch (areaFrame) {
		case 6:
		case 5:
		case 4:
		case 3:
		case 2:
		case 1:

			break;
		case 0:

			ao[PLAYER].pressedKey[0] = NULL;
			systemKey = null;
			key_released = true;
			//arenaStatus = STATUS_PLAY;

			switch (drawHandle) {
			case MD_PLAY:
				ao[PLAYER].nx = BATTLEPOSITION_PLAYER_X;// ao[PLAYER].x + TSIZE;
				ao[PLAYER].ny = ao[PLAYER].y;
				break;
			}

			arenaFrame = INFOFRAME * 2;
			//1. 초반에 스타트 프레임이라는 것을 설정하자.
			//스타트 프레임이 설정되면
			//일단 띄워줘야 되는 창을 다음 순서대로 띄워준다.


			//플레이 프레임이 있으면
			//여기서 일단 현재 스테이지의 목적을 명확히 해준다.
			//명확히 보여줘야 되는 첫번째 정보는 이번 스테이지를 클리어하기 위한 정보들, 빚을 얼마나 갚아줘야 되는지 얼마나 시간이 남았는지, 주어지는 보상은 어떤것인지를 보여준다.
			//명확히 보여줘야 되는 두번째 정보는 
			//arenaFrame = 0;

			break;
		}
	}
#ifdef PHASEFRAME
	else if (phaseFrame > 0) {
		if (curtainFrame == 0)
			phaseFrame--;
		if (phaseFrame == 0)
			arenaFrame = INFOFRAME * 2;
	}
#endif
	//////////////////////////////////////////////
	else if (arenaFrame > 0) {
		arenaFrame--;

		if (arenaFrame == 0 && ao[raidPlayer].hp > 0) {
			if (drawHandle == MD_BATTLE) {
				keyHandle = MK_BATTLE;
			}
			else if (drawHandle == MD_RAID)
				keyHandle = MK_RAID;
			else if (drawHandle == MD_PLAY) {
				keyHandle = MK_PLAY;

			}
			else if (drawHandle == MD_BOSSRAID)
				keyHandle = MK_BOSSRAID;

			touchIdleFrame = 0;
			idleHelpCnt = 0;
			ReleasePlayer(&ao[raidPlayer]);
			isTouchKey = TOUCH_RELEASE;
			is_key_released = false;
			is_release_finished = true;
			systemRelease = null;
			systemKey = null;
			initControlerFrame = 1;


			switch (drawHandle) {
			case MD_PLAY:
				if (loadRoulette == true) {
					turn = PLAYER;
					attackSequence = ATTACKSEQUENCE_READY;
					loadRoulette = false;
					initControlerFrame = ROULETTESPREADTIME;
					touchDisable = false;
				}
				break;
			case MD_BATTLE:
				
				
				break;
			}
		}
	}

	for (i = PLAYER; i < TOTALCHAR; i++)
		if (ao[i].superJump < 0)
			ao[i].superJump++;

	//퀘스트프레임
	if (questFrame > 0)
		questFrame--;

	if (npcGetFrame > 0)
		npcGetFrame--;
	else if (stageClearFrame > 0) {
		stageClearFrame--;
	}

	if (skillInfoFrame > 0)
		skillInfoFrame--;

	if (skillGetFrame > 0 && attackDelay == 0)
		skillGetFrame--;

	if (ringFrame)
		ringFrame--;

	if (onceDmgUpdateFrame)
		onceDmgUpdateFrame--;

	if (bar[BAR_QUEST].enemyIcon > 1)
		bar[BAR_QUEST].enemyIcon--;

	if (bar[BAR_QUEST].rewardIcon > 1)
		bar[BAR_QUEST].rewardIcon--;

	if ((drawHandle == MD_PLAY && curMenu == MENU_PLAY) || drawHandle == MD_BATTLE || drawHandle == MD_RAID || drawHandle == MD_BOSSRAID) {
		//if (!attackDelay || (attackSequence == ATTACKSEQUENCE_ATTACKRESULT && (attackDelay > FPS * 12 / 4 && attackType == ROULETTE_BATTLE))) {
		if (!attackDelay) {
			if (waveStatus == WAVESTATUS_PLAY) {
				for (i = PLAYER; i < TOTALCHAR; i++) {
					//단축스킬 쿨타임
					for (j = MAXHOTKEY; j >= 0; j--) {
						if ((ao[i].hotKey[j].type == HOTKEY_SKILL || ao[i].hotKey[j].type == HOTKEY_RING) && ao[i].hotKey[j].frame)
							ao[i].hotKey[j].frame--;

						if (ao[i].hotKey[j].type == HOTKEY_SKILL && ao[i].hotKey[j].frame == 0 && autoSkill == true)
							HotKeyPress(&ao[i], j);
					}

					//MAXHOTKEY 는 

					//반지 쿨타임
					if (ao[i].equip[EQUIP_RING].type == ITEM_RING && ao[i].equip[EQUIP_RING].cooldown)
						ao[i].equip[EQUIP_RING].cooldown--;

					//산소
					if (ao[i].canBreath)
						ao[i].O2 = Min(OXYGEN, ao[i].O2 + 8);
					else {
						ao[i].O2 = Max(0, ao[i].O2 - 1);

						//if (ao[i].O2 == 0 && robin.playtime % 6 == 3) {
						//    if (mapData[7] == MAPTYPE_SPACE)
						//        AttackRobin(ATTACKTYPE_SPACE, i);
						//    else
						//        AttackRobin(ATTACKTYPE_WATER, i);
						//}
					}

					//체력회복
				}

				//아이템 쿨타임
				for (i = 0; i < robin.count; i++) {
					if ((robin.inven[i].type == ITEM_WASTE || robin.inven[i].type == ITEM_RING) && robin.inven[i].cooldown)
						robin.inven[i].cooldown--;
				}
			}

			//SetRoom();

			MoveBG();

			for (i = ITEMOBJ - 1; i >= 0; i--) {
				if (ao[i].active)
					MoveObj(&ao[i]);
				else if (ao[i].dead == true && ao[i].moveHandler == REGENMOVE)
					RegenMove(&ao[i]);
			}

			SetCamera();

			//보스방에서 대화안되게//아이템과 npc가 같은자리에 있을때 아이템 우선 처리
			if (robin.bossRoom == false && itemFrame <= 20 && !escort.active)
				PopTalk();
		}
		else {
			MoveBG();


			if (attackDelay == 0) {
				for (i = PLAYER; i < TOTALCHAR; i++) {
					memset(&ao[i].ringValue, 0, sizeof(TOTAL_RING));
				}
			}
		}

		if (attackDelay > 0)
			attackDelay--;
		if (sequenceDelay > 0)
			sequenceDelay--;

	}


	//아이템은 attackDelay와 상관없이 여기서 처리해준다.
	for (i = TOTALOBJECT - 1; i >= ITEMOBJ; i--) {
		if (ao[i].active)
			MoveObj(&ao[i]);
		else if (ao[i].dead == true && ao[i].moveHandler == REGENMOVE)
			RegenMove(&ao[i]);
	}

	//AttackSequenceDraw에서는 그려주기만 하고
	//여기에서 전투관련 조작을 해준다.
	switch (drawHandle) {
	//case MD_BATTLE:
	case MD_PLAY:
		if (waveStatus == WAVESTATUS_PLAY)
			WaveControler();
		break;
	case MD_BATTLE:
		


		break;
	}

	DrawScreen(DX / 2 + scX, DY / 2 + scY[MENU_PLAY], screenZoom);

	grayScale = 0;

	offX = 0;

	if (drawHandle == MD_TITLE) {

	}

	else {

		gap = STATUSWIN_Y + 24 * _2X;
		//도움말 버튼




		//}
		grayScale = 0;

		//게임버튼

		StatusDraw(xOffset, 0, 1.0f);

		switch (drawHandle) {
		case MD_PLAY:

			break;
		case MD_BATTLE:
			break;
		}

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

		switch (drawHandle) {
		case MD_PLAY://여기서는 몬스터와의 전투
			GNBDraw(xOffset, DY - (GNBHEIGHT - GNB_INIT_HEIGHT));

			if (curMenu == MENU_PLAY && JoyStickPressPossible() == true)
				EventScheduler();
			//
			//여기서 상태를 정리한다.
			//ATTACKSEQUENCE_READY : 일반상태
			//ATTACKSEQUENCE_ACTION : 검으로 상태 찌르기
			//ATTACKSEQUENCE_ATTACKRESULT : 상자에서 보상 나오기
			//1. 보상을 내 보내주고
			//지급순서는 하트, 퀘스트 아이템, 골드, 장비(장비가 제일 마지막)
			//2. 하트는 하트바로 지급
			//3. 퀘스트 아이템은 퀘스트 바로 지급
			//3-1. 퀘스트 처리는 기존과 같이 바가 올라가고 보상 획득
			//4. 골드는 그냥 획득
			//5. 장비가 있으면
			//5-1. 기존슬롯이 비어있으면 자동장착
			//5-2. 기존슬롯이 차 있으면 교체여부 확인
			//6. 기존슬롯에 아이템이 있어서 분해되는 장비가 있으면
			//6-1 장비의 별개수만큼 BAR_CROWN로 보내주고 
			//6-2 여기서 레벨업이 발생하면 레벨업화면을 띄워주고
			//6-3 골드도 같이 보내준다.

			//if (turn >= ENEMY && turn < NEUTRAL)
			//	EnemySequenceDraw();
			//else
			//	AttackSequenceDraw();
			if (turn >= ENEMY && turn < NEUTRAL)
				EnemySequenceDraw();
			else
				AttackSequenceDraw();
			break;
		case MD_BATTLE:
			GNBDraw(xOffset, DY - (GNBHEIGHT - GNB_INIT_HEIGHT));
			//if (arenaFrame == 0)
			
			//if (turn >= ENEMY && turn < NEUTRAL)
			//	EnemySequenceDraw();
			//else
			//	AttackSequenceDraw();

			break;
		case MD_RAID:
			RaidSequenceDraw();
			break;
		case MD_BOSSRAID:
			GNBDraw(xOffset, DY - (GNBHEIGHT - GNB_INIT_HEIGHT));
			AttackSequenceDraw();
			break;
		}
	}

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

	if (keyHandle == MK_PLAY) {
		for (i = 0; i < MAXGAMEEVENT; i++) {
			if (robin.gameEvent[i].type && robin.gameEvent[i].front == true) {
				if (robin.gameEvent[i].frame2 > 0) {
					GotoPosition(robin.gameEvent[i].targetX2, robin.gameEvent[i].targetY2, i, robin.gameEvent[i].speed2, ICONMARK_REWARD);
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
					GotoPosition(robin.gameEvent[i].targetX, robin.gameEvent[i].targetY, i, robin.gameEvent[i].speed, ICONMARK_REWARD);

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

	zoom = 1.0f;

	if (waveStatus == WAVESTATUS_PLAY && attackSequence == ATTACKSEQUENCE_ACTION) {
		if (ao[turn].hitCount > 0) {
			int hitCountPosX = xOffset + ao[turn].x;
			int hitCountPosY = STATUSWIN_Y + (rh - 4) * TSIZE - (ao[turn].y) + floatOffsetY + 48 * _2X;
			DrawGoldNum(ao[turn].hitCount, hitCountPosX, hitCountPosY, RIGHT, false, false, true, 1.2f * zoom);
			DrawGoldAlpha(hitCountPosX + 4 * _2X, hitCountPosY - 4 * _2X, ALPHA_HIT, FONT_GOLD_LARGE, 0.8f * zoom, LEFT, false, false);
		}
	}


	if (attackDelay == 0 && menuResult == 0 && ((drawHandle == MD_PLAY && curMenu == MENU_PLAY) || drawHandle == MD_BATTLE || drawHandle == MD_RAID || drawHandle == MD_BOSSRAID || drawHandle == MD_BOSSRAID) && popUp[0].active == false) {
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

	switch (drawHandle) {
	case MD_PLAY:

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

		//이전 메뉴 버튼의 역할만 한다.
		//if (curMenu != MENU_PLAY || xOffset)
		//	GNBDraw(xOffset, DY - (GNBHEIGHT - GNB_INIT_HEIGHT), gScreenBuffer, gScreenLayer, false);

		break;
	case MD_BATTLE:
		break;
	case MD_RAID:
		break;
	case MD_BOSSRAID:
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
}

void AttackSequenceDraw(void)
{
	int i, j, k;

	long long gloveValue = 0;
	float width;
	float iconZoom;
	int totalObjCnt = 0;
	int x = xOffset + DX / 2 - 92 * _2X;
	int y = STATUSWIN_Y + ENEMYHPBARYGAP;

	long long start = dmgInfo[dmgIndex].dmg;
	long long end = dmgInfo[dmgIndex].dmg * rouletteAttackStr[actionCardIdx * TOTALROULETTECHANCE + attackStr];
	long long current;
	long long gap = (end - start) / (FPS / 2);

	long long start2;
	long long end2;
	long long gap2;

	int icon;
	int rewardIcon;
	int currencyIcon;
	int currency;

	int amount;

	int tempBet = bet;
	OBJECT* pObj = &ao[turn];
	OBJECT* eObj = &ao[pObj->target];
	int size = 2;

	int damage;
	int TERM = 1;
	int PHASE = 1;

	float battleZoom = dioramaZoom;

	int pvpMenuIndex;

	ITEM* it;
	int skillRewardType;

	long long getGoldNum = 0;
	long long getHeartNum = 0;
	long long getMedalNum = 0;
	long long getStarNum = 0;
	long long getHammerNum = 0;

	float rewardZoom = 2.0f;
	int row = 2;//가로로 몇개인지
	int col = 2;//세로로 몇줄인지
	int rewardGap = 8 * _2X;

	int enemyCrewY = 512 * _2X;
	int beforeEnemyCrewY;

	bool crewMenuDraw = false;
	bool equipMenuDraw = false;

	float menuZoom = 1.0f;
	int doorY;

	int collectionIdx;

	int curQuest = robin.quest;
	int questCmf = questInfo[robin.quest * QUESTINFODATASIZE];
	int questRequest = questInfo[robin.quest * QUESTINFODATASIZE + 2];
	int itemType = questRequestItem[questRequest * 3];
	int itemDetail = questRequestItem[questRequest * 3 + 1];
	int itemGrade = questRequestItem[questRequest * 3 + 2];
	int itemCnt;
	int itemLv;

	const signed short* tPtr;

	float barZoom;

	int beforeCoinBarY;
	float beforeCoinBarZoom;

	float startX, startY, targetX, targetY, targetX2, targetY2, speed, speedIncrement, speed2, speedIncrement2, waitingFrame, waitingFrame2, zoom, zoomEnd, zoomIncrement, zoom2, zoomEnd2, zoomIncrement2;
	int backUpX, backUpY;


	int boxY;
	int rewardCnt;

	int who;

	int jokboAniFrame = FPS / 3;
	float zoomBefore;

	//bond

	//if (drawHandle == MD_PLAY) {
	XNUMGAP = 0;
	YNUMGAP = -24 * _2X;
	//}
	//else if (drawHandle == MD_BATTLE) {
	//	XNUMGAP = 116 * _2X;
	//	YNUMGAP = 16 * _2X;
	//}

	it = &ao[turn].equip[EQUIP_WEAPON];
	collectionIdx = GetCollectionIdx(it->type, it->detail, it->grade);

	for (i = 0; i < TOTALPLAYER; i++)
		ao[i].hitCountPlus = false;

	if (GetEventMenuIdx(EVENTTYPE_QUEST) != -1)
		gEvent = &robin.gameEvent[GetEventMenuIdx(EVENTTYPE_QUEST)];

	//switch (rewardItemCnt) {
	//case 1:
	//	row = 1;
	//	col = 1;
	//	rewardZoom = 2.5f;
	//	rewardGap = 0;
	//	break;
	//case 2:
	//	row = 2;
	//	col = 1;
	//	rewardZoom = 2.0f;
	//	rewardGap = 16 * _2X;
	//	break;
	//case 3:
	//	row = 3;
	//	col = 1;
	//	rewardZoom = 1.8f;
	//	rewardGap = 16 * _2X;
	//	break;
	//case 4:
	//	row = 2;
	//	col = 2;
	//	rewardZoom = 1.8f;
	//	rewardGap = 16 * _2X;
	//	break;
	//case 5:
	//case 6:
	//	row = 3;
	//	col = 2;
	//	rewardZoom = 1.8f;
	//	rewardGap = 16 * _2X;
	//	break;
	//case 7:
	//case 8:
	//	row = 4;
	//	col = 2;
	//	rewardZoom = 1.5f;
	//	rewardGap = 16 * _2X;
	//	break;
	//case 9:
	//	row = 3;
	//	col = 3;
	//	rewardZoom = 1.5f;
	//	rewardGap = 16 * _2X;
	//	break;
	//case 10:
	//case 11:
	//case 12:
	//	row = 4;
	//	col = 3;
	//	rewardZoom = 1.5f;
	//	rewardGap = 16 * _2X;
	//	break;
	//case 13:
	//case 14:
	//case 15:
	//case 16:
	//	row = 4;
	//	col = 3;
	//	rewardZoom = 1.5f;
	//	rewardGap = 16 * _2X;
	//	break;
	//}

	row = 4;
	col = 3;
	rewardZoom = 1.5f;
	rewardGap = 16 * _2X;

	if (pObj->equip[EQUIP_GLOVE].type != EMPTY)
		gloveValue = itemUpgradeValue[pObj->equip[EQUIP_GLOVE].type * TOTAL_COLLECTIONS * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_GLOVE].detail * TOTALGRADE * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_GLOVE].grade * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_GLOVE].cooldown];

	switch (attackSequence) {
	case ATTACKSEQUENCE_READY:
		break;
		//여기서는 슬롯만 돈다. 이미 NPC종류는 이미 결정된 상태여서 할일은 없다.
		//결정이 되면
	case ATTACKSEQUENCE_SLOT:
		break;

	case ATTACKSEQUENCE_ACTION:
		//여기서는 선택된 크류가 다음과 같은 액션을 보여주는 것을 보여준다.
		//1. 크류는 먼저 발동되고, 버프를 하던 뭘하던 최종에는 히어로들이 공격한다.
		//2. 크류가 할 수 있는 액션을 정하자.
		// 1) 크루
		//  - 세개의 슬롯 중 한번 선택되면 -> 일반공격(구체를 발사한다.)
		//  - 세개의 슬롯 중 두번 선택되면 -> 강한 공격을 하던가 버프 스킬을 걸어주고
		//  - 세개의 슬롯 중 세번 선택되면 -> 히어로의 스킬을 사용하거나 몬스터를 소환한다.
		// 2) 몬스터
		// - 세개의 슬롯 중 한번 선택되면 -> 전투위치로 소환되어 일반공격
		// - 세개의 슬롯 중 두번 선택되면 -> 강공격을 한다.
		// - 세개의 슬롯 중 세번 선택되면 -> 일반 몬스터는 주인공한테 버프를 하거나, 보스급이면 특수공격을 적에게 한다.
		//
		//일단 캐릭터가 공격이냐, 버프냐, 
		//if (sequenceFrame < FPS) {
			//ScreenDarken(SCREENDARKEN);
			//여기서 어떤 캐릭터가 현재 스킬을 발동중인지 적어준다.
		ao[turn].zoom *= dioramaZoom;
		DrawObj(&ao[turn]);
		ao[turn].zoom /= dioramaZoom;
		//이렇게 되면 버프고
		if (ao[turn].target < TOTALCHAR) {

		}
		//공격
		else if (ao[turn].target >= ENEMY) {

		}
		break;
		//코인 결과를 정리하는 타이밍
	case ATTACKSEQUENCE_COIN:
		if (turnFrame == 2 * FPS) {
			//BAR_BATTLECOIN에서 BAR_GOLD로 이동하게 수정
			ao[NEUTRAL].motion = BOXSTATUS_OPENED;
			SetCurrencyMarkArr(
				ao[NEUTRAL].x, 
				STATUSWIN_Y + (rh - 4) * TSIZE - ao[NEUTRAL].y + (float)(256) * ao[NEUTRAL].zoom, 
				bar[BAR_GOLD].x + 6 * _2X + ITEMICONSIZE / 2, 
				bar[BAR_GOLD].y - 6 * _2X - ITEMICONSIZE / 2, 
				bar[BAR_GOLD].x + 6 * _2X + ITEMICONSIZE / 2,
				bar[BAR_GOLD].y - 6 * _2X - ITEMICONSIZE / 2,
				16 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, CURRENCYWAITINGFRAMEMAX, CURRENCYWAITINGFRAMEMAX, ICON_GOLD, 30, (bar[BAR_BATTLECOIN].count + bar[BAR_BATTLECOIN].add), CURRENCY_GOLD, 3.0f, 2.0f, -0.2f / MOTIONDIV, 2.0f, 1.0f, -0.2f / MOTIONDIV, 10, BAR_GOLD);

			/*
			SetCurrencyMark(
				//bar[BAR_BATTLECOIN].x + (float)(6 * _2X + ITEMICONSIZE * 1.5f / 2) * BAR_BATTLECOIN_ZOOM, bar[BAR_BATTLECOIN].y - (float)(6 * _2X + ITEMICONSIZE * 1.5f / 2) * BAR_BATTLECOIN_ZOOM,
				ao[NEUTRAL].x, ao[NEUTRAL].y + (float)(256) * ao[NEUTRAL].zoom,
				bar[BAR_GOLD].x + 6 * _2X + ITEMICONSIZE / 2, bar[BAR_GOLD].y - 6 * _2X - ITEMICONSIZE / 2,
				bar[BAR_GOLD].x + 6 * _2X + ITEMICONSIZE / 2, bar[BAR_GOLD].y - 6 * _2X - ITEMICONSIZE / 2,
				8 * _2X, 1 * _2X,
				8 * _2X, 1 * _2X,
				FPS / 2, FPS / 2,
				ICON_GOLD,
				30,
				bar[BAR_BATTLECOIN].count + bar[BAR_BATTLECOIN].add,
				CURRENCY_GOLD,
				CURRENCYICON_STARTSIZE, CURRENCYICON_ENDSIZE2, 0.3f,
				CURRENCYICON_ENDSIZE2, CURRENCYICON_STARTSIZE, -0.2f,
				BAR_GOLD
			);
			*/
		}
		else if (turnFrame == 3 * FPS) {
			bar[BAR_BATTLECOIN].targetX = bar[BAR_BATTLECOIN].targetX2 = bar[BAR_BATTLECOIN].x;
			bar[BAR_BATTLECOIN].targetY = bar[BAR_BATTLECOIN].y - 32 * _2X;
			bar[BAR_BATTLECOIN].targetY2 = DY + 80 * _2X;
			bar[BAR_BATTLECOIN].speed = 4 * _2X;
			bar[BAR_BATTLECOIN].speedIncrement = 1 * _2X;
			bar[BAR_BATTLECOIN].speed2 = 8 * _2X;
			bar[BAR_BATTLECOIN].speedIncrement2 = 1 * _2X;
			bar[BAR_BATTLECOIN].frame = 1;
			bar[BAR_BATTLECOIN].frame2 = 0;
			bar[BAR_BATTLECOIN].zoom2 = bar[BAR_BATTLECOIN].zoom;
			bar[BAR_BATTLECOIN].zoomIncrement2 = bar[BAR_BATTLECOIN].zoomIncrement;

			ao[NEUTRAL].motion = BOXSTATUS_CLOSED;
		}
		else if (turnFrame == 4 * FPS) {
			attackSequence = ATTACKSEQUENCE_READY;
			turnFrame = 0;
			touchDisable = false;
			memset(&turnList, 0, sizeof(turnList));
			memset(&ao[SOLDIER], 0, sizeof(OBJECT) * MAXENEMYOBJ);
			for (i = 0; i < PLAYERALL; i++)
				ao[i].turnPosition = HERE;
		}
		break;
	case ATTACKSEQUENCE_ATTACKRESULT:

		break;
	case ATTACKSEQUENCE_REWARD_BATTLE:
	case ATTACKSEQUENCE_REWARD_RAID:
		ResetRectPoint();

		for (i = 0; i < MAXGAMEEVENT; i++) {
			if (robin.gameEvent[i].type == EVENTTYPE_PVP)
				pvpMenuIndex = i;
		}

		if (curtainFrame || areaFrame) {
			sequenceDelay++;
		}

		effect.color2 = COLOR_BLACK;

		rewardIcon = pvpQuestInfo[robin.pvpQuest * PVPQUESTINFODATASIZE + 0];
		//일단 바가 튀어나오면
		if (sequenceDelay == ATTACKDELAY_REWARD_BATTLE_START + FPS - 0) {

		}
		//레이드 보상
		else if (sequenceDelay == ATTACKDELAY_REWARD_BATTLE_START + FPS - 1) {
			if (attackSequence == ATTACKSEQUENCE_REWARD_BATTLE) {
				AddBar(&bar[BAR_MEDAL], battleRewardMedal[1 - battleShield] * GetBetHeart(it->detail, it->grade, bet), BARFRAME);
			}
			else if (attackSequence == ATTACKSEQUENCE_REWARD_RAID) {
				AddBar(&bar[BAR_MEDAL], raidRewardMedal[attackStr] * GetBetHeart(it->detail, it->grade, bet), BARFRAME);
			}

			robin.gameEvent[GetEventMenuIdx(EVENTTYPE_PVP)].front = true;
			bar[BAR_MEDAL].icon = pvpQuestInfo[robin.pvpQuest * PVPQUESTINFODATASIZE + 0];
		}
		//게이지바가 튀어나오는 동안 레이드
		else if (sequenceDelay > ATTACKDELAY_REWARD_BATTLE_START) {

			if (sequenceDelay == ATTACKDELAY_REWARD_BATTLE_START + FPS - 5) {
				robin.gameEvent[pvpMenuIndex].barStatus = EVENT_BAR_NEW;
				robin.gameEvent[pvpMenuIndex].barFrame = 1;

				SetPvpQuestReward(bar[BAR_MEDAL].count + bar[BAR_MEDAL].add);
			}


		}
		//게이지바에 배틀 아이템 날라가는 것 
		else if (sequenceDelay > ATTACKDELAY_REWARD_BATTLE_CURRENCY) {

			if (sequenceDelay == ATTACKDELAY_REWARD_BATTLE_START) {
				robin.gameEvent[pvpMenuIndex].barStatus = EVENT_BAR_ITEMGET;
				robin.gameEvent[pvpMenuIndex].frame = 1;
			}

			if (sequenceDelay > ATTACKDELAY_REWARD_BATTLE_CURRENCY + FPS * 3 / ROULETTEDIV)
				SetCurrencyMark(bar[BAR_MEDAL].x - (float)(ITEMICONSIZE * 2.0f) / 2 - 8 * _2X, bar[BAR_MEDAL].y - (float)(ITEMICONSIZE * 2.0f) / 2 - 8 * _2X, robin.gameEvent[GetEventMenuIdx(EVENTTYPE_PVP)].x + (float)(-PVPQUESTBARWIDTH - 32 * _2X * 1) * robin.gameEvent[GetEventMenuIdx(EVENTTYPE_PVP)].zoom - (float)ITEMICONSIZE * robin.gameEvent[GetEventMenuIdx(EVENTTYPE_PVP)].zoom * 2 + (float)ITEMICONSIZE / 2 * robin.gameEvent[GetEventMenuIdx(EVENTTYPE_PVP)].zoom * 2, robin.gameEvent[GetEventMenuIdx(EVENTTYPE_PVP)].y + 4 * _2X, false, false, 16 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, false, false, FPS, false, rewardIcon, 30, 10, CURRENCY_MEDAL, 2.0f, 2.0f, 0.0f, false, false, false, BAR_ITEM);

			if (sequenceDelay == ATTACKDELAY_REWARD_BATTLE_CURRENCY + 1)
				rouletteNum = robin.pvpQuestCnt;
		}
		//바가 차는것
		else if (sequenceDelay > ATTACKDELAY_REWARD_BATTLE_FILL) {

			if (sequenceDelay == ATTACKDELAY_REWARD_BATTLE_CURRENCY) {
				robin.gameEvent[pvpMenuIndex].barStatus = EVENT_BAR_GUAGE_FILL;
				robin.gameEvent[pvpMenuIndex].frame = 1;
				robin.gameEvent[pvpMenuIndex].barFrame = 1;

				//만약 획득할 퀘스트 아이템 개수가 현재 클리어필요량보다 많다면
				if (!robin.remainPvpQuestItem && robin.pvpQuestCnt != pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + robin.pvpDetailQuest]) {
					sequenceDelay = ATTACKDELAY_REWARD_BATTLE_CHANGEPVPQUEST + 1;
				}
			}

			start = robin.pvpQuestCnt;
			end = start + robin.thisTimePvpQuestItem;

			current = start + (float)(end - start) * (ATTACKDELAY_REWARD_BATTLE_CURRENCY - sequenceDelay) / (ATTACKDELAY_REWARD_BATTLE_CURRENCY - ATTACKDELAY_REWARD_BATTLE_FILL);
			if (rouletteNum == end) {
				sequenceDelay == ATTACKDELAY_REWARD_BATTLE_FILL + 1;
			}
			else if (rouletteNum < current)
				rouletteNum = current;
			else if (rouletteNum >= current && rouletteNum < end)
				rouletteNum++;
			else {
				rouletteNum = end;
				//sequenceDelay = ATTACKDELAY_REWARD_BATTLE_FILL + 1;
			}

			//robin.pvpQuestCnt = current;

			//EventMenuDraw(&robin.gameEvent[pvpMenuIndex], gScreenBuffer, gScreenLayer, false);

			//robin.pvpQuestCnt = pvpQuestCntBack;

			if (sequenceDelay == ATTACKDELAY_REWARD_BATTLE_FILL + 1) {
				robin.pvpQuestCnt += robin.thisTimePvpQuestItem;
				robin.remainPvpQuestItem -= robin.thisTimePvpQuestItem;
				//만약 획득할 퀘스트 아이템 개수가 현재 클리어필요량보다 많다면
				if (robin.pvpQuestCnt == pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + robin.pvpDetailQuest]) {
					robin.gameEvent[pvpMenuIndex].barStatus = EVENT_BAR_REWARDGET;
					robin.gameEvent[pvpMenuIndex].frame = 1;
					robin.gameEvent[pvpMenuIndex].barFrame = 1;

					startX = pvpRewardPosition[robin.pvpDetailQuest][0];
					startY = pvpRewardPosition[robin.pvpDetailQuest][1];

					//startX = startX * robin.gameEvent[pvpMenuIndex].zoom;

					targetX = xOffset + DX / 2 - (float)(REWARDCARDSIZE_X * rewardZoom * row + rewardGap * (row - 1)) / 2 + (float)(REWARDCARDSIZE_X * rewardZoom + rewardGap) * (pvpRewardIndex % row) + (float)(REWARDCARDSIZE_X * rewardZoom) / 2;
					targetY = DY / 2 + (float)REWARDCARDSIZE_Y * rewardZoom * col - (float)(REWARDCARDSIZE_Y * rewardZoom + rewardGap) * (pvpRewardIndex / row) - (float)(REWARDCARDSIZE_Y * rewardZoom) / 2 - 108 * _2X;

					SetRewardMark(startX, startY, targetX, targetY, false, false, 16 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, false, false, FPS / 2, false, GetItemIcon(pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + robin.pvpDetailQuest) * PVPQUESTDATASIZE + 0], pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + robin.pvpDetailQuest) * PVPQUESTDATASIZE + 1], pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + robin.pvpDetailQuest) * PVPQUESTDATASIZE + 2]), 30, pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + robin.pvpDetailQuest) * PVPQUESTDATASIZE + 3], pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + robin.pvpDetailQuest) * PVPQUESTDATASIZE + 0], pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + robin.pvpDetailQuest) * PVPQUESTDATASIZE + 1], pvpQuestReward[(robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + robin.pvpDetailQuest) * PVPQUESTDATASIZE + 2], false, false, true, false, PLAYER, true, false, true, 0.8f, rewardZoom, 0.2f / MOTIONDIV, false, false, false);
					pvpRewardIndex++;
				}


				//만약 보상까지 도달하지 못하면
				if (!robin.remainPvpQuestItem && robin.pvpQuestCnt != pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + robin.pvpDetailQuest]) {
					//sequenceDelay = ATTACKDELAY_REWARD_BATTLE_CHANGEPVPQUEST + 1;
					sequenceDelay = ATTACKDELAY_REWARD_BATTLE_REWARDGET;
				}

				bar[BAR_MEDAL].active = false;
			}
		}
		//박스를 화면으로 날려주는 것
		else if (sequenceDelay > ATTACKDELAY_REWARD_BATTLE_BOXOPEN) {
			//EventMenuDraw(&robin.gameEvent[pvpMenuIndex], gScreenBuffer, gScreenLayer, false);

			//상자를 오픈했으니 현재 획득 카운트를 늘려주고 바가 차는 곳으로 돌려보낸다.
			if (sequenceDelay == ATTACKDELAY_REWARD_BATTLE_BOXOPEN + 1) {

				//만약 모든 서브 퀘스트를 클리어했으면 리워드로 보내고
				if (robin.pvpDetailQuest + 1 == TOTALPVPDETAILREQUEST && robin.pvpSubQuest + 1 == TOTALPVPSUBQUEST) {
					//sequenceDelay = ATTACKDELAY_REWARD_BATTLE_BOXOPEN + 1;//보상신으로 넘어간다.
					attackSequence = ATTACKSEQUENCE_REWARD;
					sequenceDelay = ATTACKDELAY_REWARD_START;
				}
				//그렇지 않으면 바를 닫았다가, 다음 퀘스트를 보여주는 신으로 보낸다.
				else if (robin.pvpDetailQuest + 1 == TOTALPVPDETAILREQUEST) {
					//sequenceDelay = ATTACKDELAY_REWARD_BATTLE_BOXOPEN + 1;
				}
				//만약 그냥 현재 서브퀘이면 그냥 다시 바차는데로 보낸다. 
				else {
					robin.pvpDetailQuest++;
					sequenceDelay = ATTACKDELAY_REWARD_BATTLE_CURRENCY + 1;
					robin.thisTimePvpQuestItem = Min(robin.remainPvpQuestItem, (pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + robin.pvpDetailQuest] - robin.pvpQuestCnt));

				}

			}
		}
		//피브이피 퀘스트를 체인지
		else if (sequenceDelay > ATTACKDELAY_REWARD_BATTLE_CHANGEPVPQUEST) {

			//여기서 바를 닫아주고
			if (sequenceDelay == ATTACKDELAY_REWARD_BATTLE_BOXOPEN - 1) {
				robin.gameEvent[pvpMenuIndex].barStatus = EVENT_BAR_CLOSE;
				robin.gameEvent[pvpMenuIndex].frame = 1;
				robin.gameEvent[pvpMenuIndex].barFrame = 1;
			}
			else if (sequenceDelay == ATTACKDELAY_REWARD_BATTLE_CHANGEPVPQUEST + (ATTACKDELAY_REWARD_BATTLE_BOXOPEN - ATTACKDELAY_REWARD_BATTLE_CHANGEPVPQUEST) / 2) {
				robin.pvpDetailQuest++;
				//만약 디테일퀘스트가 끝까지 갔으면
				//퀘스트를 증가시켜주고 
				if (robin.pvpDetailQuest == TOTALPVPDETAILREQUEST) {
					robin.pvpSubQuest++;
					robin.pvpDetailQuest = 0;
					//rouletteNum = 0;
				}

				robin.thisTimePvpQuestItem = Min(robin.remainPvpQuestItem, (pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + robin.pvpDetailQuest] - robin.pvpQuestCnt));

				robin.gameEvent[pvpMenuIndex].barStatus = EVENT_BAR_NEW;
				robin.gameEvent[pvpMenuIndex].frame = 1;
				robin.gameEvent[pvpMenuIndex].barFrame = 1;

			}
			else if (sequenceDelay == ATTACKDELAY_REWARD_BATTLE_CHANGEPVPQUEST + 1) {
				sequenceDelay = ATTACKDELAY_REWARD_BATTLE_CURRENCY + 1;
			}

			//EventMenuDraw(&robin.gameEvent[pvpMenuIndex], gScreenBuffer, gScreenLayer, false);

		}
		//보상을 보여주는 신
		else if (sequenceDelay > ATTACKDELAY_REWARD_BATTLE_REWARDGET) {

			if (sequenceDelay == ATTACKDELAY_REWARD_BATTLE_BOXOPEN) {
				robin.gameEvent[pvpMenuIndex].barStatus = EVENT_BAR_REWARDGET;
				robin.gameEvent[pvpMenuIndex].frame = 1;
				robin.gameEvent[pvpMenuIndex].barFrame = 1;
			}

			//EventMenuDraw(&robin.gameEvent[pvpMenuIndex], gScreenBuffer, gScreenLayer, false);

		}
		else if (sequenceDelay > ATTACKDELAY_REWARD_BATTLE_CLOSE) {
			if (sequenceDelay == ATTACKDELAY_REWARD_BATTLE_REWARDGET - 5) {
				robin.gameEvent[pvpMenuIndex].barStatus = EVENT_BAR_CLOSE;
				robin.gameEvent[pvpMenuIndex].frame = 1;
				robin.gameEvent[pvpMenuIndex].barFrame = 1;
			}

			//robin.gameEvent[pvpMenuIndex].zoom -= 0.2f / MOTIONDIV;

			//if (robin.gameEvent[pvpMenuIndex].zoom <= 1.0f)
			//	robin.gameEvent[pvpMenuIndex].zoom = 1.0f;

			//EventMenuDraw(&robin.gameEvent[pvpMenuIndex], gScreenBuffer, gScreenLayer, false);

		}
		else {
			if (sequenceDelay == 2 && rewardItemCnt > 0 && eObj->moveHandler == VANISHMOVE) {
				attackSequence = ATTACKSEQUENCE_REWARD;
				sequenceDelay = ATTACKDELAY_REWARD_START;
			}
		}

		if (sequenceDelay == 1) {

			//획득할 보상이 있으면 
			if (rewardItemCnt > 0) {
				effect.color2 = COLOR_BLACK;

				attackSequence = ATTACKSEQUENCE_REWARD;
				sequenceDelay = ATTACKDELAY_REWARD_START;
			}
			//만약 보상이 없으면
			else {
				memset(dmgInfo, 0, sizeof(dmgInfo));

				attackSequence = ATTACKSEQUENCE_READY;

				turnPosition = COMING;
				arenaStatus = STATUS_PLAY;
				option.gameControl = CONTROL_AUTO;
				screenDarken = false;
#ifdef ENEMYHPBAR
				bar[BAR_ENEMYHP].active = true;
#endif
				bar[BAR_GOLD].active = true;
				bar[BAR_CROWN].active = true;
				bar[BAR_QUEST].active = true;

				effect.color2 = false;

				//SetBox(&ao[ITEMBOX], bet);

			}

			gEvent->front = false;
		}

		touchDisable = true;

		break;
	case ATTACKSEQUENCE_REWARD:
		effect.color2 = COLOR_BLACK;
		if (sequenceDelay > ATTACKDELAY_REWARD_TABTOCOLLECT) {
			if (sequenceDelay == ATTACKDELAY_REWARD_TABTOCOLLECT + 2) {
				if (robin.bossRoom == true)
					bar[BAR_ENEMYUSER].front = false;
				else {
#ifdef ENEMYHPBAR
					for (i = 0; i < MAXENEMY; i++)
						bar[BAR_ENEMYHP + i].front = false;
#endif
				}

				sequenceDelay = ATTACKDELAY_REWARD_TABTOCOLLECT + 3;
				SetAlpha(32 - Abs(frame / MOTIONDIV % 32 - 16));
				DrawGoldAlpha(xOffset + DX / 2, DY / 2 + TABBUTTONGAP, ALPHA_TABTOCOLLECT, FONT_GOLD_LARGE, 1, CENTER, false, false);
				SetAlpha(32);
				//박스가 있으면
				if (rewardMark[curRewardItem].type == ITEM_BOX)
					SetRectPoint(0, DY, DX, DY, TOUCH_FUNC_GOTOGACHA);
				/*
				else if ((rewardMark[curRewardItem].type == ITEM_SWORD ||
					rewardMark[curRewardItem].type == ITEM_GUN ||
					rewardMark[curRewardItem].type == ITEM_BOOMERANG ||
					rewardMark[curRewardItem].type == ITEM_HELM ||
					rewardMark[curRewardItem].type == ITEM_HAT ||
					rewardMark[curRewardItem].type == ITEM_CAP ||
					rewardMark[curRewardItem].type == ITEM_ARMOR ||
					rewardMark[curRewardItem].type == ITEM_VEST ||
					rewardMark[curRewardItem].type == ITEM_COAT ||
					rewardMark[curRewardItem].type == ITEM_GUNTLET ||
					rewardMark[curRewardItem].type == ITEM_ARMLET ||
					rewardMark[curRewardItem].type == ITEM_GLOVE ||
					rewardMark[curRewardItem].type == ITEM_KILT ||
					rewardMark[curRewardItem].type == ITEM_SKIRT ||
					rewardMark[curRewardItem].type == ITEM_PANTS ||
					rewardMark[curRewardItem].type == ITEM_GREAVES ||
					rewardMark[curRewardItem].type == ITEM_SHOES ||
					rewardMark[curRewardItem].type == ITEM_BOOTS ||
					rewardMark[curRewardItem].type == ITEM_CREW) && GetInvenIdx(rewardMark[curRewardItem].type, rewardMark[curRewardItem].detail, rewardMark[curRewardItem].grade) == -1)
					SetRectPoint(0, DY, DX, DY, TOUCH_FUNC_GOTONEWCARD);
				*/
				else
					SetRectPoint(0, DY, DX, DY, TOUCH_FUNC_GETREWARDSTART);
			}
		}
		else if (sequenceDelay > ATTACKDELAY_REWARD_COLLECTING) {
			j = 0;
			for (i = 0; i < rewardItemCnt; i++) {
				startX = rewardMark[i].x + 2 * _2X;
				startY = rewardMark[i].y + ITEMICONSIZE * 2.0f - 2 * _2X;

				switch (rewardItem[i].type) {
				case ITEM_GOLD:
					getGoldNum += rewardItem[i].count;

					targetX = bar[BAR_GOLD].x + 8 * _2X + ITEMICONSIZE / 2;
					targetY = bar[BAR_GOLD].y - 8 * _2X - ITEMICONSIZE / 2;

					if (sequenceDelay == ATTACKDELAY_REWARD_TABTOCOLLECT)
						SetCurrencyMarkArr(startX, startY, targetX, targetY, targetX, targetY, 16 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, CURRENCYWAITINGFRAMEMAX, CURRENCYWAITINGFRAMEMAX, ICON_GOLD, 30, rewardItem[i].count, CURRENCY_GOLD, 3.0f, 2.0f, -0.2f / MOTIONDIV, 2.0f, 1.0f, -0.2f / MOTIONDIV, 10, BAR_GOLD);

					if (rewardFrame == 1)
						j++;
					break;
				case ITEM_HEART:
					getHeartNum += rewardItem[i].count;

					targetX = xOffset + bar[BAR_HEART].x + 16 * _2X + 128 * _2X / 2 - (GetBigNumDx(bar[BAR_HEART].count - GetInitHeart(), true, NUM_FONT_NORMAL, false, true, HEARTBARWIDTH, 1.0f, true) + 20 * _2X + 4 * _2X) / 2 + ITEMICONSIZE / 2;
					targetY = bar[BAR_HEART].y - TSIZE * 1 / 2;

					if (sequenceDelay == ATTACKDELAY_REWARD_TABTOCOLLECT)
						SetCurrencyMarkArr(startX, startY, startX, startY, targetX, targetY, 2 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, 16 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, FPS / 2, FPS / 2, ICON_HEART, 30, rewardItem[i].count, CURRENCY_HEART, 2.0f, 3.0f, 0.2f / MOTIONDIV, 3.0f, 1.5f, -0.2f / MOTIONDIV, 10, BAR_HEART);

					if (rewardFrame == 1)
						j++;
					break;
				case ITEM_MEDAL:
					getMedalNum += rewardItem[i].count;

					targetX = xOffset + 4 * _2X + 164 * _2X + ITEMICONSIZE / 2;
					targetY = DY - (GNBHEIGHT - GNB_INIT_HEIGHT) - ITEMICONSIZE / 2;
					if (sequenceDelay == ATTACKDELAY_REWARD_TABTOCOLLECT)
						SetCurrencyMarkArr(startX, startY, targetX, targetY, false, false, 16 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, false, false, CURRENCYWAITINGFRAMEMAX, 0, ICON_MEDAL, 30, rewardItem[i].count, CURRENCY_MEDAL, 2.0f, 1.0f, -0.2f / MOTIONDIV, false, false, false, 10, BAR_MEDAL);

					if (rewardFrame == 1)
						j++;
					break;
				case ITEM_STAR:
					getStarNum += rewardItem[i].count;

					targetX = bar[BAR_CROWN].x + 8 * _2X + ITEMICONSIZE / 2;
					targetY = bar[BAR_CROWN].y - 8 * _2X - ITEMICONSIZE / 2;

					if (sequenceDelay == ATTACKDELAY_REWARD_TABTOCOLLECT)
						SetCurrencyMarkArr(startX, startY, targetX, targetY, targetX, targetY, 16 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, CURRENCYWAITINGFRAMEMAX, CURRENCYWAITINGFRAMEMAX, ICON_STAR, 30, rewardItem[i].count, CURRENCY_STAR, 3.0f, 2.0f, -0.2f / MOTIONDIV, 2.0f, 1.0f, -0.2f / MOTIONDIV, 10, BAR_CROWN);

					if (rewardFrame == 1)
						j++;
					break;
				case ITEM_HAMMER:
					getHammerNum += rewardItem[i].count;

					targetX = bar[BAR_HAMMER].x + 8 * _2X + ITEMICONSIZE / 2;
					targetY = bar[BAR_HAMMER].y - 8 * _2X - ITEMICONSIZE / 2;

					if (sequenceDelay == ATTACKDELAY_REWARD_TABTOCOLLECT)
						SetCurrencyMarkArr(startX, startY, targetX, targetY, targetX, targetY, 16 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, CURRENCYWAITINGFRAMEMAX, CURRENCYWAITINGFRAMEMAX, ICON_HAMMER, 30, rewardItem[i].count, CURRENCY_HAMMER, 3.0f, 2.0f, -0.2f / MOTIONDIV, 2.0f, 1.0f, -0.2f / MOTIONDIV, 10, BAR_HAMMER);

					if (rewardFrame == 1)
						j++;
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
					if (ATTACKDELAY_REWARD_TABTOCOLLECT - sequenceDelay < 15)
						menuZoom = Min(1.5f, (float)(ATTACKDELAY_REWARD_TABTOCOLLECT - sequenceDelay) / 10);
					else if (ATTACKDELAY_REWARD_TABTOCOLLECT - sequenceDelay < 15 + 15)
						menuZoom = 1.5f;
					else if (ATTACKDELAY_REWARD_TABTOCOLLECT - sequenceDelay < 15 + 15 + 5)
						menuZoom = Max(1.0f, 1.5f - (float)(ATTACKDELAY_REWARD_TABTOCOLLECT - sequenceDelay - 15 - 15) / 10);
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

					if (sequenceDelay == ATTACKDELAY_REWARD_TABTOCOLLECT) {
						if (rewardItem[i].type == ITEM_CREW)
							rewardMark[i].targetX2 = xOffset + DX / 2 + 108 * _2X + 20 * _2X;
						else
							rewardMark[i].targetX2 = xOffset + DX / 2 - 150 * _2X + 20 * _2X;

						rewardMark[i].targetY2 = STATUSWIN_Y + JOYSTICKGAP + 83 * _2X;

						rewardMark[i].zoom2 = rewardMark[i].zoom;
						rewardMark[i].zoomEnd2 = 1.0f;
						rewardMark[i].zoomIncrement2 = -0.2f / MOTIONDIV;
						rewardMark[i].speed2 = 2 * _2X / MOTIONDIV;
						rewardMark[i].speedIncrement2 = 2 * _2X / MOTIONDIV;
						rewardMark[i].frame2 = 1;

						GetItem(rewardItem[i].type, rewardItem[i].cooldown, rewardItem[i].detail, rewardItem[i].grade, 1, false);
						PlayMusic(M_CARDSPLIT);

					}
					break;
				case ITEM_BOX:

					break;
				}

			}

			if (getGoldNum > 0 && sequenceDelay == ATTACKDELAY_REWARD_COLLECTING + FPS / 2) {
				AddBar(&bar[BAR_GOLD], getGoldNum, BARFRAME);
				GetItem(ITEM_GOLD, false, false, false, getGoldNum, false);
			}


			if (getHeartNum > 0 && sequenceDelay == ATTACKDELAY_REWARD_COLLECTING + FPS / 2) {
				AddBar(&bar[BAR_BOX], getHeartNum, BARFRAME);
				GetItem(ITEM_HEART, false, false, false, getHeartNum, false);
			}

			if (getMedalNum > 0 && sequenceDelay == ATTACKDELAY_REWARD_COLLECTING + FPS / 2) {
				AddBar(&bar[BAR_MEDAL], getMedalNum, BARFRAME);
				GetItem(ITEM_MEDAL, false, false, false, getMedalNum, false);
			}

			if (getStarNum > 0 && sequenceDelay == ATTACKDELAY_REWARD_COLLECTING + FPS / 2) {
				AddBar(&bar[BAR_CROWN], getStarNum, BARFRAME);
				GetItem(ITEM_STAR, false, false, false, getStarNum, false);
			}

			if (getHammerNum > 0 && sequenceDelay == ATTACKDELAY_REWARD_COLLECTING + FPS / 2) {
				AddBar(&bar[BAR_HAMMER], getHammerNum, BARFRAME);
				GetItem(ITEM_HAMMER, false, false, false, getHammerNum, false);
			}

			//획득된것은 제외하고 당겨준다.
			if (sequenceDelay == ATTACKDELAY_REWARD_COLLECTING + 1) {

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
						memset(&rewardMark[i], 0, sizeof(ICONMARK));
						for (k = i; k < rewardItemCnt - 1; k++) {
							memcpy(&rewardItem[k], &rewardItem[k + 1], sizeof(ITEM));
							memcpy(&rewardMark[k], &rewardMark[k + 1], sizeof(ICONMARK));
						}
						memset(&rewardItem[rewardItemCnt - 1], 0, sizeof(ITEM));
						memset(&rewardMark[rewardItemCnt - 1], 0, sizeof(ICONMARK));
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
			if (sequenceDelay == 1) {
				if (attackSequenceBefore) {
					attackSequence = attackSequenceBefore;
					attackType = attackTypeBefore;
					attackStr = attackStrBefore;
					sequenceDelay = attackDelayBefore;
					attackSequenceBefore = attackTypeBefore = attackStrBefore = attackDelayBefore = false;
				}
				//만약 적의 hp가 0이면 스테이지 클리어로 보내고
				else if (AliveEnemyCnt() == true && robin.bossRoom == true) {
					attackSequence = ATTACKSEQUENCE_STAGECLEAR;
					sequenceDelay = ATTACKDELAY_STAGECLEAR_START + 2 * FPS / ROULETTEDIV;
					bar[BAR_BOX].front = false;
					stageInfoDepth = STAGEINFO_CREWGACHA;
					stageInfoFrame = 0;
				}
				//그렇지 않으면 
				else {
					AfterAttack(&ao[turn]);
				}
			}

		}
		break;
	case ATTACKSEQUENCE_BOSS:
		effect.color2 = COLOR_BLACK;
		speed = 14 * _2X;
		//일단 보스가 나오고
		if (sequenceDelay > ATTACKDELAY_BOSS_START) {
			//그리고 룰렛카드를 없애주고
			if (sequenceDelay == ATTACKDELAY_BOSS_START + 1) {
				PlayMusic(M_SHAKIN);
			}

		}
		//우리편이 나오고
		else if (sequenceDelay > ATTACKDELAY_BOSS_BOSS) {

			battleZoom = Max(2.0f, 2.0f + 0.5f * (float)(sequenceDelay - ROULETTEDIV - ATTACKDELAY_BOSS_BOSS));
			DrawPlayer(pObj, motionData[0], DX / 2 - 80 * _2X, STATUSWIN_Y - 64 * _2X, RIGHT, battleZoom, false, false, true);

			if (sequenceDelay == ATTACKDELAY_BOSS_BOSS + 1)
				PlayMusic(M_SHAKIN);
		}
		//보스듀얼이 뜨고
		else if (sequenceDelay > ATTACKDELAY_BOSS_DUEL) {

			battleZoom = 2.0f;
			DrawPlayer(pObj, motionData[32 + (ATTACKDELAY_BOSS_PLAYER - sequenceDelay) / MOTIONDIV % 32], DX / 2 - 80 * _2X, STATUSWIN_Y - 64 * _2X, RIGHT, battleZoom, false, false, true);

			battleZoom = Max(1.5f, 1.5f + 0.5f * (float)(sequenceDelay - ROULETTEDIV - ATTACKDELAY_BOSS_DUEL));
			DrawGoldAlpha(DX / 2, DY / 2, ALPHA_BOSSDUEL, FONT_GOLD_LARGE, battleZoom, CENTER, false, false);

			if (sequenceDelay == ATTACKDELAY_BOSS_DUEL + 1)
				PlayMusic(M_SHAKIN);
		}
		//커튼이 닫힌다.
		else if (sequenceDelay > ATTACKDELAY_BOSS_PLAYER) {

			battleZoom = 2.0f;
			DrawPlayer(pObj, PO_C0_STING6, DX / 2 - 80 * _2X, STATUSWIN_Y - 64 * _2X, RIGHT, battleZoom, false, false, true);

			battleZoom = 1.5f;
			DrawGoldAlpha(DX / 2, DY / 2, ALPHA_BOSSDUEL, FONT_GOLD_LARGE, battleZoom, CENTER, false, false);

			battleZoom = Max(2.0f, 2.0f + 0.5f * (float)(sequenceDelay - ROULETTEDIV - ATTACKDELAY_BOSS_PLAYER));
			CenterText(TEXT_BOSSMODE_TITLE, xOffset + DX / 2, STATUSWIN_Y + 64 * _2X + battleZoom * (float)FONT_HEIGHT / 2, battleZoom);

			if (sequenceDelay == ATTACKDELAY_BOSS_PLAYER + 1)
				PlayMusic(M_BOSS);
		}
		//2. 워프존을 만들어주고 FPS
		else if (sequenceDelay > ATTACKDELAY_BOSS_WARP) {

			battleZoom = 2.0f;
			DrawPlayer(pObj, PO_C0_STING6, DX / 2 - 80 * _2X, STATUSWIN_Y - 64 * _2X, RIGHT, battleZoom, false, false, true);

			battleZoom = 1.5f;
			DrawGoldAlpha(DX / 2, DY / 2, ALPHA_BOSSDUEL, FONT_GOLD_LARGE, battleZoom, CENTER, false, false);

			battleZoom = 2.0f;
			CenterText(TEXT_BOSSMODE_TITLE, xOffset + DX / 2, STATUSWIN_Y + 64 * _2X + battleZoom * (float)FONT_HEIGHT / 2, battleZoom);

		}
		//3. 워프로 달려가면 된다. FPS
		else {

			battleZoom = 2.0f;
			DrawPlayer(pObj, PO_C0_STING6, DX / 2 - 80 * _2X, STATUSWIN_Y - 64 * _2X, RIGHT, battleZoom, false, false, true);

			battleZoom = 1.5f;
			DrawGoldAlpha(DX / 2, DY / 2, ALPHA_BOSSDUEL, FONT_GOLD_LARGE, battleZoom, CENTER, false, false);

			battleZoom = 2.0f;
			CenterText(TEXT_BOSSMODE_TITLE, xOffset + DX / 2, STATUSWIN_Y + 64 * _2X + battleZoom * (float)FONT_HEIGHT / 2, battleZoom);


			y = STATUSWIN_Y + DRAWROULETTENUMGAP_SUB;

		}

		if (sequenceDelay == 1) {

			GotoBoss();
			return;
		}
		break;
	case ATTACKSEQUENCE_BOSSRAID:
		//effect.color2 = COLOR_BLACK;
		//speed = 14 * _2X;
		if (sequenceDelay == 1) {
			return;
		}
		break;
	case ATTACKSEQUENCE_STAGECLEAR:
		effect.color2 = COLOR_BLACK;
		speed = 14 * _2X;
		//StageInfoDraw(robin.stage, robin.room, false, false, xOffset + DX / 2 - (float)(POPUPWINDOWSIZE_X / 2), POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2, zoom, gScreenBuffer, gScreenLayer, false);

		//일단 보스가 나오고
		if (sequenceDelay > ATTACKDELAY_BOSS_START) {


		}
		//우리편이 나오고
		else if (sequenceDelay > ATTACKDELAY_BOSS_BOSS) {


		}
		//보스듀얼이 뜨고
		else if (sequenceDelay > ATTACKDELAY_BOSS_DUEL) {

		}
		//커튼이 닫힌다.
		else if (sequenceDelay > ATTACKDELAY_BOSS_PLAYER) {

			if (sequenceDelay == ATTACKDELAY_BOSS_PLAYER + 1)
				PlayMusic(M_BOSS);
		}
		//2. 워프존을 만들어주고 FPS
		else if (sequenceDelay > ATTACKDELAY_BOSS_WARP) {

			if (sequenceDelay == ATTACKDELAY_RAID_WARP + 1) {

			}
		}
		//3. 워프로 달려가면 된다. FPS
		else {
			y = STATUSWIN_Y + DRAWROULETTENUMGAP_SUB;

		}

		if (sequenceDelay == 1) {

			robin.stage++;
			robin.room = 0;
			if (robin.stage > robin.maxStage[robin.stage]) {
				robin.maxStage[robin.stage] = robin.stage;
				robin.maxRoom[robin.stage] = 0;
			}
			robin.bossRoom = false;
			robinmap = MAP_DIORAMA_TOLEM + castleOrder[robin.castle];
			//SetBossObj();
			SetRoom();
			if (doubleBuffer) {
				//if (oldMap != robinmap)
				DoubleBuffering(drawHandle);
			}

			fadeFrame = FPS;
			arenaStatus = STATUS_READY;

			focus = PLAYER;
			raidPlayer = PLAYER;
			turn = PLAYER;
			turnFrame = 0;
			for (i = 0; i < TOTALOBJECT; i++) {
				ao[i].turn = 0;
				ao[i].turnPosition = HERE;
			}

			memset(&robin.enemyObj, 0, sizeof(robin.enemyObj));
			memset(&ao[ENEMY], 0, sizeof(robin.enemyObj));

			if (touch) {
				touchMode = TOUCH_PLAY;
				touchModeOld = null;
				touchIndex = 0;
				swipeIndex = 0;
			}

			attackSequence = ATTACKSEQUENCE_READY;

			return;
		}
		break;
	}

	sequenceFrame++;
}

void EnemySequenceDraw(void)
{
	int i, j, k;
	int x = xOffset + DX / 2 - 92 * _2X;
	int y = STATUSWIN_Y + ENEMYHPBARYGAP;

	int icon;
	int rewardIcon;
	int iconArr[3];
	int currencyIcon;
	int currency;
	int enemyTurn = turn;

	int speed;
	int amount;

	int tempBet = bet;
	OBJECT* eObj = &ao[enemyTurn];
	eObj->target = GetClosestPlayer(eObj);

	OBJECT* pObj = &ao[eObj->target];
	int enemyBarIdx = GetEnemyBarIdx(enemyTurn);
	int size = 2;

	int damage;
	int TERM = 1;
	int PHASE = 1;

	int battleZoom;

	long long armorValue = 0;
	float iconZoom;
	float width;

	const signed short* tPtr;
	int ret;

	tPtr = cmf_status_data[eObj->cmf][eObj->etc];
	ret = *tPtr;

	if (pObj->equip[EQUIP_ARMOR].type != EMPTY)
		armorValue = itemUpgradeValue[pObj->equip[EQUIP_ARMOR].type * TOTAL_COLLECTIONS * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_ARMOR].detail * TOTALGRADE * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_ARMOR].grade * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_ARMOR].cooldown];

	//항상 터치가 안되도록 한다.
	touchDisable = true;

	currencyIcon = ICON_GOLD;
	currency = CURRENCY_GOLD;

	if (eObj->debuf[STUN]) {
		turn = PLAYER;
		return;
	}

	switch (attackSequence) {
	case ATTACKSEQUENCE_ACTION:
		//effect.color = COLOR_BLACK;
		//여기서는 스킬 발동을 보여주고, 발동된 스킬에 따라 이동하는걸 보여준다.
		if (GetDistance(eObj, pObj) > GetAttackRange(GetObjFromPtr(eObj))) {
			//일단 달려가라

		}
		//모션이 다 끝났으면
		//모션이 너무 길어서 바가 초기화될정도면 일단 모션의 최고치를 짜른다.
		//effect.color = COLOR_BLACK;

		else if (eObj->frame % ret == 0) {
			eObj->etc = enemyAttackPattern[eObj->type * ATTACKPATTERNTOTALDATASIZE + 2 + eObj->currentSkill * ATTACKPATTERNDATASIZE + eObj->turnPosition];
			eObj->frame = 0;
			eObj->mainFrame = 0;
			eObj->turnPosition = COMING;
			//attackSequence = ATTACKSEQUENCE_ROULETTE;
			//attackDelay = ENEMYDELAY_COIN_START;
			sequenceFrame = 0;
		}
		break;
	case ATTACKSEQUENCE_ATTACKRESULT:
		switch (attackType) {
		case ROULETTE_COIN://코인을 뺏어오는것
			//여기서 갑옷이 있으면 절대값을 빼준다.
			if (attackDelay > ENEMYDELAY_COIN_DEFAULTVALUE) {
				if (attackDelay == ENEMYDELAY_COIN_DEFAULTVALUE + 1) {
					//갑옷이 없으면
					if (ao[PLAYER].equip[EQUIP_ARMOR].type == EMPTY) {
						attackDelay = ENEMYDELAY_COIN_ARMOR_RESULT;
					}
				}
			}
			else if (attackDelay > ENEMYDELAY_COIN_ARMOR_DOWN) {
				//1. 일단 갑옷 아이콘이 나오고
				effect.color2 = COLOR_BLACK;

				iconZoom = attackDelay + 7 * MOTIONDIV - ENEMYDELAY_COIN_DEFAULTVALUE;

				if (iconZoom < EQUIPZOOM)
					iconZoom = EQUIPZOOM;

				width = (float)ITEMICONSIZE * iconZoom + (float)(4 * _2X) * iconZoom + GetNumDx(armorValue, PLUS, NUM_FONT_LARGE, false, true, iconZoom * 3 / 4, false) + (float)(2 * _2X) * iconZoom + (float)(8 * _2X) * iconZoom;

				if (ao[PLAYER].equip[EQUIP_ARMOR].type != EMPTY) {
					DrawIcon(GetItemIcon(ao[PLAYER].equip[EQUIP_ARMOR].type, ao[PLAYER].equip[EQUIP_ARMOR].detail, ao[PLAYER].equip[EQUIP_ARMOR].grade), xOffset + bar[BAR_COIN].x + EQUIPICON_X - width / 2, bar[BAR_COIN].y + EQUIPICON_Y + iconZoom * ITEMICONSIZE / 2, iconZoom, false, false, false, true);
					DrawNum(armorValue, xOffset + bar[BAR_COIN].x + EQUIPICON_X - width / 2 + (float)ITEMICONSIZE * iconZoom + (float)(4 * _2X) * iconZoom, bar[BAR_COIN].y + EQUIPICON_Y + iconZoom * (ITEMICONSIZE - 2 * _2X) / 2, NUM_FONT_LARGE, LEFT, false, MINUS, true, iconZoom * 3 / 4, false);
					DrawImage(8 * _2X, 11 * _2X, 216 * _2X, 141 * _2X, xOffset + bar[BAR_COIN].x + EQUIPICON_X - width / 2 + (float)ITEMICONSIZE * iconZoom + (float)(4 * _2X) * iconZoom + GetNumDx(armorValue, PLUS, NUM_FONT_LARGE, false, true, iconZoom * 3 / 4, false) + (float)(2 * _2X) * iconZoom, bar[BAR_COIN].y + EQUIPICON_Y + (float)iconZoom * (ITEMICONSIZE - 5 * _2X) / 2, false, false, false, false, false, iconZoom, sprite[EFFECT_IMG], EFFECT_IMG);
				}

				if (attackDelay == ENEMYDELAY_COIN_ARMOR_DOWN + 1) {
					AddBar(&bar[BAR_COIN], -(float)(bar[BAR_COIN].count + bar[BAR_COIN].add) * armorValue / 100, BARFRAME);
				}
			}
			else if (attackDelay > ENEMYDELAY_COIN_ARMOR_RESULT) {
				effect.color2 = COLOR_BLACK;

				iconZoom = EQUIPZOOM;

				width = (float)ITEMICONSIZE * iconZoom + (float)(4 * _2X) * iconZoom + GetNumDx(armorValue, PLUS, NUM_FONT_LARGE, false, true, iconZoom * 3 / 4, false) + (float)(2 * _2X) * iconZoom + (float)(8 * _2X) * iconZoom;

				if (ao[PLAYER].equip[EQUIP_ARMOR].type != EMPTY) {
					DrawIcon(GetItemIcon(ao[PLAYER].equip[EQUIP_ARMOR].type, ao[PLAYER].equip[EQUIP_ARMOR].detail, ao[PLAYER].equip[EQUIP_ARMOR].grade), xOffset + bar[BAR_COIN].x + EQUIPICON_X - width / 2, bar[BAR_COIN].y + EQUIPICON_Y + iconZoom * ITEMICONSIZE / 2, iconZoom, false, false, false, true);
					DrawNum(armorValue, xOffset + bar[BAR_COIN].x + EQUIPICON_X - width / 2 + (float)ITEMICONSIZE * iconZoom + (float)(4 * _2X) * iconZoom, bar[BAR_COIN].y + EQUIPICON_Y + iconZoom * (ITEMICONSIZE - 2 * _2X) / 2, NUM_FONT_LARGE, LEFT, false, MINUS, true, iconZoom * 3 / 4, false);
					DrawImage(8 * _2X, 11 * _2X, 216 * _2X, 141 * _2X, xOffset + bar[BAR_COIN].x + EQUIPICON_X - width / 2 + (float)ITEMICONSIZE * iconZoom + (float)(4 * _2X) * iconZoom + GetNumDx(armorValue, MINUS, NUM_FONT_LARGE, false, true, iconZoom * 3 / 4, false) + (float)(2 * _2X) * iconZoom, bar[BAR_COIN].y + EQUIPICON_Y + (float)iconZoom * (ITEMICONSIZE - 5 * _2X) / 2, false, false, false, false, false, iconZoom, sprite[EFFECT_IMG], EFFECT_IMG);
				}
			}

			else if (attackDelay > ENEMYDELAY_COIN_PLAYER_ATTACK) {

				if (attackDelay == ENEMYDELAY_COIN_ARMOR_RESULT - 1) {
					if (bar[BAR_GOLD].count < -(bar[BAR_COIN].count + bar[BAR_COIN].add)) {
						AddBar(&bar[BAR_GOLD], -(-(bar[BAR_COIN].count + bar[BAR_COIN].add) - bar[BAR_GOLD].count), BARFRAME);
						//골드를 빼주고
						GetItem(ITEM_GOLD, false, false, false, -(-(bar[BAR_COIN].count + bar[BAR_COIN].add) - bar[BAR_GOLD].count), false);

					}
					else {
						AddBar(&bar[BAR_GOLD], (bar[BAR_COIN].count + bar[BAR_COIN].add), BARFRAME);
						GetItem(ITEM_GOLD, false, false, false, (bar[BAR_COIN].count + bar[BAR_COIN].add), false);

					}
				}

				if (attackDelay == ENEMYDELAY_COIN_PLAYER_ATTACK + 1) {
					BackUpEnemyObj();
					for (i = ENEMY; i < NEUTRAL; i++)
						robin.enemyObj[i - ENEMY].x = ao[i].nx;

					SaveGame();
				}
			}
			else {
				//effect.color2 = false;
				//몬스터가 제자리로 도착하면 여기서 상태를 정리해준다.

			}
			break;
		case ROULETTE_EQUIP://스스로 코인을 채워오는것
			break;
		}

		if (attackDelay == 1) {
			//attackSequence = attackSequenceBack;
			//attackSequence = ATTACKSEQUENCE_READY;
			//turn = PLAYER;


		}
		break;

	}

	sequenceFrame++;
}

void RaidSequenceDraw(void)
{
	int i, j;
	float width = 44 * _2X;
	int totalObjCnt = 0;
	int x = xOffset + DX / 2 - 92 * _2X;
	int y = STATUSWIN_Y + ENEMYHPBARYGAP;
	long long start = dmgInfo[dmgIndex].dmg;
	long long end = dmgInfo[dmgIndex].dmg * GetBetHeart(ao[PLAYER].equip[EQUIP_WEAPON].detail, ao[PLAYER].equip[EQUIP_WEAPON].grade, bet);


	int icon;
	int rewardIcon;
	int iconArr[3];
	int currencyIcon;
	int currency;

	int amount;

	int tempBet = bet;
	OBJECT* pObj = &ao[PLAYER];
	OBJECT* eObj = &ao[ENEMY];
	OBJECT* pDest = &ao[pObj->target];
	int size = 2;

	int damage;
	int TERM = 1;
	int PHASE = 1;

	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];

	float fontZoom = 2;

	int equipCount = 0;
	int goldAlpha = MISS;

	float startX, startY, targetX, targetY, targetX2, targetY2, speed, speedIncrement, speed2, speedIncrement2, waitingFrame, waitingFrame2, zoom, zoomEnd, zoomIncrement, zoom2, zoomEnd2, zoomIncrement2;
	int backUpX, backUpY;

	long long bootsValue = 0;
	float iconZoom;

	if (ao[PLAYER].equip[EQUIP_BOOTS].type != EMPTY)
		bootsValue = itemUpgradeValue[pObj->equip[EQUIP_BOOTS].type * TOTAL_COLLECTIONS * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_BOOTS].detail * TOTALGRADE * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_BOOTS].grade * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_BOOTS].cooldown];

	switch (attackSequence) {
	case ATTACKSEQUENCE_READY:
		effect.color2 = false;
		break;
	default:
		effect.color2 = COLOR_BLACK;
		break;
	}
	//모션

	RaidControlerDraw();

	ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, pObj->x - (float)12 * _2X * pObj->zoom, STATUSWIN_Y2 + 102 * _2X + (float)8 * _2X * pObj->zoom, SHADOW_IMG, pObj->zoom);
	DrawObj(pObj);

	switch (attackSequence) {
	case ATTACKSEQUENCE_READY:
		pObj->motion = PO_C0_N0 + frame / MOTIONDIV % 4;
		break;
		//현재는 룰렛을 그리는 타이밍이다.
	case ATTACKSEQUENCE_SLOT:
		pObj->motion = jumpUpMotion[sequenceFrame / 2];

		if (pObj->motion == PO_C0_JU0)
			GotoObjZoom(&ao[pObj->target], pObj, 24 * _2X / MOTIONDIV, 0, -120 * _2X, 0.2f / MOTIONDIV, 2.0f);

		if (sequenceFrame == FPS * 3 / 2 / MOTIONDIV) {
			attackSequence = ATTACKSEQUENCE_ACTION;
			sequenceFrame = 0;

			switch (attackType) {
			default:
				//일단 공격을 하자.
				pObj->attack = ATTACK_DOWN;
				pObj->attackFrame = skillStartFrame[ATTACK_DOWN];
				HitCountCheck(pObj);
				raidFrame = FPS * 5 * MOTIONDIV;
				break;
			}
		}
		break;
	case ATTACKSEQUENCE_ACTION:

		pObj->motion = jumpDownMotion[sequenceFrame / MOTIONDIV];

		if (pObj->motion >= PO_C0_DOA2) {
			GotoObjZoom(&ao[pObj->target], pObj, FREEFALL, 0, 0, 0.2f / MOTIONDIV, 3.0f);
		}

		if (ObjCrash(pObj, &ao[pObj->target]) && pObj->motion == PO_C0_DOA3 && dmgInfo[dmgIndex].dmg == 0) {
			dmgInfo[dmgIndex].dmg = Min(ao[pObj->target].gold, 1);
			dmgInfo[dmgIndex].x = DX / 2;

			raidFrame = GetRaidAttackFrameCnt(attackType);
			sequenceFrame = 0;
			ao[pObj->target].motion = BOXSTATUS_OPENING;
			ao[pObj->target].frame = 0;
		}

		if (dmgInfo[dmgIndex].dmg > 0) {
			currencyIcon = ICON_GOLD;
			currency = CURRENCY_GOLD;

			startX = xOffset + ao[pObj->target].x - rx - ITEMICONSIZE;
			startY = STATUSWIN_Y + (rh - 4) * TSIZE - (ao[pObj->target].y - OBJIMGGAP) - ry;
			targetX = startX + coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 0];
			targetY = startY + coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 1];
			//targetX2 = bar[BAR_COIN].x - (GetNumDx(ao[pObj->target].gold, false, NUM_FONT_LARGE, false, true, 1.0f) + 1 * ITEMICONSIZE + 6 * _2X) / 2 + ITEMICONSIZE / 2;
			//targetY2 = bar[BAR_COIN].y - ITEMICONSIZE / 2;
			targetX2 = bar[BAR_RAIDCOIN].x + (float)(-(GetNumDx(ao[pObj->target].gold, false, NUM_FONT_LARGE, false, true, 1.0f, true) + 1 * ITEMICONSIZE + 6 * _2X) / 2 + ITEMICONSIZE / 2) * 1.5f;
			targetY2 = bar[BAR_RAIDCOIN].y - (float)(ITEMICONSIZE / 2) * 1.5f;
			speed = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 2] / MOTIONDIV;
			speedIncrement = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 3] / MOTIONDIV;
			speed2 = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 4] / MOTIONDIV;
			speedIncrement2 = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 5] / MOTIONDIV;
			waitingFrame = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 6];
			waitingFrame2 = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 7];
			zoom = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 8];
			zoomEnd = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 9];
			zoomIncrement = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 10];
			zoom2 = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 11];
			zoomEnd2 = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 12];
			zoomIncrement2 = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 13];

			SetCurrencyMark(startX, startY, targetX, targetY, targetX2, targetY2, speed, speedIncrement, speed2, speedIncrement2, waitingFrame, waitingFrame2, ICON_GOLD, 30, dmgInfo[dmgIndex].dmg, CURRENCY_GOLD, zoom, zoomEnd, zoomIncrement, zoom2, zoomEnd2, zoomIncrement2, BAR_RAIDCOIN);
			DrawEffect(attackType == ROULETTE_COIN ? 1000 + HIT_DIANA_SMALL1 + (frame / MOTIONDIV % 7) : 1000 + HIT_DIANA_MEDIUM1 + (frame / MOTIONDIV % 7), xOffset + pDest->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - pDest->y - ry, ao[PLAYER].dirF, false, 1.0f);

			width = GetGoldNumDx(ao[NPC].hitCount, false, 2, true, 2 * 1) + (float)(102 * _2X) * 1;
			x = xOffset + DX / 2 - width / 2;
			y = STATUSWIN_Y - 32 * _2X;

			DrawHitCount(&ao[NPC], x, y, HITCOUNTZOOM);
			ao[NPC].hitCount++;

		}

		if (ao[NPC].hitCount >= raidFrame) {
			attackSequence = ATTACKSEQUENCE_ATTACKRESULT;
			attackDelay = ATTACKDELAY_RAIDMODE_START + 2 * FPS / ROULETTEDIV;
			sequenceFrame = 0;
			pObj->frame = 0;
		}
		break;
	case ATTACKSEQUENCE_ATTACKRESULT:

		fontZoom = 1.5f;

		currencyIcon = ICON_GOLD;

		width = GetGoldNumDx(ao[NPC].hitCount, false, 2, true, 2 * 1) + (float)(52 * _2X) * 1;

		x = xOffset + DX / 2 - width / 2;
		y = STATUSWIN_Y - 32 * _2X;

		DrawHitCount(&ao[NPC], x, y, HITCOUNTZOOM);

		//임시로 오브젝트를 만들어서 다시 돌려준다.
		pObj->motion = backHomeMotion[pObj->frame / MOTIONDIV];

		switch (pObj->motion) {
		case PO_C0_DOA4:
			break;
		case PO_C0_JU0:
			backUpX = ao[pObj->target].x;
			backUpY = ao[pObj->target].y;

			ao[pObj->target].x = DX / 2;
			ao[pObj->target].y -= 64 * _2X;

			GotoObjZoom(&ao[pObj->target], pObj, 16 * _2X / MOTIONDIV, 0, 0, 0.2f / MOTIONDIV, 3.0f);

			ao[pObj->target].x = backUpX;
			ao[pObj->target].y = backUpY;
			break;
		case PO_C0_JD0:
			backUpX = ao[pObj->target].x;
			backUpY = ao[pObj->target].y;

			ao[pObj->target].x = DX / 2;
			ao[pObj->target].y = DY / 2;//houseInfo[enemyHouse.houseType * HOUSEINFODATASIZE + 3] + 25 * TSIZE + TSIZE / 2;

			GotoObjZoom(&ao[pObj->target], pObj, 16 * _2X / MOTIONDIV, 0, 0, -0.2f / MOTIONDIV, 1.5f);

			ao[pObj->target].x = backUpX;
			ao[pObj->target].y = backUpY;
			break;
		case PO_C0_LANDING0:
			break;
		case PO_C0_LANDING1:
			break;
		}

		pObj->frame++;

		switch (attackType) {
		case ROULETTE_RAID_GOOD://일반
		case ROULETTE_RAID_PERFECT://대박

			if (attackDelay > ATTACKDELAY_RAIDMODE_START) {

			}
			//현재 숫자를 보여주고 // 2 / 4
			else if (attackDelay > ATTACKDELAY_RAIDMODE_UP) {
				pObj->motion = pObj->frame / MOTIONDIV % 4;

				if (attackDelay == ATTACKDELAY_RAIDMODE_START)
					AddBar(&bar[BAR_RAIDGOLD], ao[pObj->target].gold, BARFRAME);

				DrawGoldAlpha(xOffset + DX / 2, bar[BAR_RAIDGOLD].y - 64 * _2X + (float)46 * fontZoom / 2, hitAlpha[attackType], FONT_GOLD_LARGE, fontZoom, CENTER, false, false);

				if (attackDelay == ATTACKDELAY_RAIDMODE_START)
					PlayMusic(M_COIN);
			}
			else if (attackDelay > ATTACKDELAY_RAIDMODE_DEFAULT) {

				DrawGoldAlpha(xOffset + DX / 2, bar[BAR_RAIDGOLD].y - 64 * _2X + (float)46 * fontZoom / 2, hitAlpha[attackType], FONT_GOLD_LARGE, fontZoom, CENTER, false, false);
				if (attackDelay == ATTACKDELAY_RAIDMODE_DEFAULT + 1) {
					sequenceFrame = 0;
				}
			}
			//숫자를 합산해 주고
			else if (attackDelay > ATTACKDELAY_RAIDMODE_SUM) {
				pObj->motion = pObj->frame / MOTIONDIV % 4;
				if (attackDelay == ATTACKDELAY_RAIDMODE_DEFAULT)
					PlayMusic(M_SHAKIN);

				//SetAlpha(Max(0, 32 - (sequenceFrame / MOTIONDIV)));

				//bar[BAR_COIN].y -= 24 * _2X / MOTIONDIV;

				//if (bar[BAR_COIN].y < bar[BAR_RAIDCOIN].y)
				//	bar[BAR_COIN].y = bar[BAR_RAIDCOIN].y;


				//SetAlpha(32);


				if (attackDelay == ATTACKDELAY_RAIDMODE_SUM + 1) {
					//AddBar(&bar[BAR_RAIDCOIN], (bar[BAR_COIN].count + bar[BAR_COIN].add), BARFRAME);
					AddBar(&bar[BAR_RAIDGOLD], (bar[BAR_RAIDGOLD].count + bar[BAR_RAIDGOLD].add), BARFRAME);

					PlayMusic(M_CASHIER);
				}
			}
			//적 캐릭터 사라짐
			else {
				pObj->motion = pObj->frame / MOTIONDIV % 4;
			}
			break;
			//미스
		case ROULETTE_RAID_MISS:

			if (attackDelay <= ATTACKDELAY_RAIDMODE_START) {
				DrawGoldAlpha(xOffset + DX / 2, bar[BAR_RAIDGOLD].y - 64 * _2X + (float)46 * fontZoom / 2, hitAlpha[attackType], FONT_GOLD_LARGE, fontZoom, CENTER, false, false);
			}

			if (attackDelay == ATTACKDELAY_RAIDMODE_UP)
				attackDelay = 1;
			break;
		}

		//attackType = ROULETTE_QUEST;

		if (attackDelay == 1) {

			if (raidChance > 0)
				attackSequence = ATTACKSEQUENCE_READY;
			else {

				//결과항목
				attackStr = 0;
				for (i = 0; i < 4; i++) {
					if (ao[ITEMOBJ + i].gold > 0 && ao[ITEMOBJ + i].status == BOXSTATUS_OPENED)
						attackStr++;
				}

				switch (attackStr) {
				default:
					attackStr = 0;
					break;
				case 2:
					if (bar[BAR_COIN].count + bar[BAR_COIN].add > (bar[BAR_ENEMYUSER].count + bar[BAR_ENEMYUSER].add / 2))
						attackStr = 1;
					else
						attackStr = 0;
					break;
				case 3:
					attackStr = 2;
					break;
				}

				attackSequence = ATTACKSEQUENCE_REWARD;
				attackDelay = ATTACKDELAY_RAIDREWARD_START + FPS;
				if (bar[BAR_COIN].count + bar[BAR_COIN].add == (ao[ENEMYUSEROBJ].gold) * GetBetHeart(ao[PLAYER].equip[EQUIP_WEAPON].detail, ao[PLAYER].equip[EQUIP_WEAPON].grade, bet)) {
					attackType = ROULETTE_RAID_PERFECT;
				}
				else if (bar[BAR_COIN].count + bar[BAR_COIN].add < (ao[ENEMYUSEROBJ].gold) * GetBetHeart(ao[PLAYER].equip[EQUIP_WEAPON].detail, ao[PLAYER].equip[EQUIP_WEAPON].grade, bet) / 2) {
					attackType = ROULETTE_RAID_MISS;
				}
				else {
					attackType = ROULETTE_RAID_GOOD;
				}

				PlayMusic(M_CHEER);
			}

			pObj->concentrate = 0;
			pObj->attack = false;
			turn = NEUTRAL;

			memset(&cardMark, 0, sizeof(cardMark));

			systemRelease = false;
			PlayRelease(pObj);
			pObj->pDx = pObj->dx = 0;
			memset(&dmgInfo[dmgIndex], 0, sizeof(DMGINFO));

			//값 초기화
			bar[BAR_RAIDGOLD].count = 0;
			bar[BAR_RAIDGOLD].add = 0;
			bar[BAR_RAIDGOLD].active = false;

			if (GetObjFromPtr(pObj) == raidPlayer && skillUsed > 0) {
				skillInfoFrame = SKILLREMAINEDFRAME;
				skillUsed = SKILLREMAINEDFRAME;
			}

		}

		break;
	case ATTACKSEQUENCE_REWARD:


		targetX = xOffset + DX / 2 - ITEMCARDSIZE_X / 2;
		targetY = DY / 2 + HITPOSITIONGAP;

		fontZoom = Max((attackDelay + 8 - (ATTACKDELAY_RAIDREWARD_START + FPS)), 2);

		fontZoom = Min(8, fontZoom);


		rewardIcon = pvpQuestInfo[robin.pvpQuest * PVPQUESTINFODATASIZE + 0];

		DrawGoldAlpha(xOffset + DX / 2, bar[BAR_RAIDGOLD].y - 64 * _2X + 64 * _2X + (float)46 * fontZoom / 2, raidAlpha[attackStr], FONT_GOLD_LARGE, fontZoom, CENTER, false, false);

		//1. 현재 코인을 보여주고
		if (attackDelay > ATTACKDELAY_RAIDREWARD_START) {
			if (attackDelay == ATTACKDELAY_RAIDREWARD_START + 1) {
				sequenceFrame = 0;
				//장비가 없다면
				if (ao[PLAYER].equip[EQUIP_BOOTS].type == EMPTY)
					attackDelay = ATTACKDELAY_RAIDREWARD_COIN_BOOTS_RESULT;
			}
		}
		//2. 부츠가 있다면 숫자가 올라가고 
		else if (attackDelay > ATTACKDELAY_RAIDREWARD_COIN_BOOTS_UP) {
			iconZoom = attackDelay + 7 * MOTIONDIV - ATTACKDELAY_RAIDREWARD_START;

			if (iconZoom < EQUIPZOOM)
				iconZoom = EQUIPZOOM;

			width = (float)ITEMICONSIZE * iconZoom + (float)(4 * _2X) * iconZoom + GetNumDx(bootsValue, PLUS, NUM_FONT_LARGE, false, true, iconZoom * 3 / 4, true) + (float)(2 * _2X) * iconZoom + (float)(8 * _2X) * iconZoom;

			if (ao[PLAYER].equip[EQUIP_BOOTS].type != EMPTY) {
				DrawIcon(GetItemIcon(ao[PLAYER].equip[EQUIP_BOOTS].type, ao[PLAYER].equip[EQUIP_BOOTS].detail, ao[PLAYER].equip[EQUIP_BOOTS].grade), xOffset + bar[BAR_COIN].x + EQUIPICON_X - width / 2, bar[BAR_COIN].y + EQUIPICON_Y + iconZoom * ITEMICONSIZE / 2, iconZoom, false, false, false, true);
				DrawNum(bootsValue, xOffset + bar[BAR_COIN].x + EQUIPICON_X - width / 2 + (float)ITEMICONSIZE * iconZoom + (float)(4 * _2X) * iconZoom, bar[BAR_COIN].y + EQUIPICON_Y + iconZoom * (ITEMICONSIZE - 2 * _2X) / 2, NUM_FONT_LARGE, LEFT, false, PLUS, true, iconZoom * 3 / 4, true);
				DrawImage(8 * _2X, 11 * _2X, 216 * _2X, 141 * _2X, xOffset + bar[BAR_COIN].x + EQUIPICON_X - width / 2 + (float)ITEMICONSIZE * iconZoom + (float)(4 * _2X) * iconZoom + GetNumDx(bootsValue, PLUS, NUM_FONT_LARGE, false, true, iconZoom * 3 / 4, true) + (float)(2 * _2X) * iconZoom, bar[BAR_COIN].y + EQUIPICON_Y + (float)iconZoom * (ITEMICONSIZE - 5 * _2X) / 2, false, false, false, false, false, iconZoom, sprite[EFFECT_IMG], EFFECT_IMG);
			}

			if (attackDelay == ATTACKDELAY_RAIDREWARD_COIN_BOOTS_UP + 1) {
				AddBar(&bar[BAR_COIN], (float)(bar[BAR_COIN].count + bar[BAR_COIN].add) * bootsValue / 100, BARFRAME);
			}

		}
		//3. 부츠에 의해 올라간 숫자를 보여주고
		else if (attackDelay > ATTACKDELAY_RAIDREWARD_COIN_BOOTS_RESULT) {
			iconZoom = EQUIPZOOM;

			width = (float)ITEMICONSIZE * iconZoom + (float)(4 * _2X) * iconZoom + GetNumDx(bootsValue, PLUS, NUM_FONT_LARGE, false, true, iconZoom * 3 / 4, true) + (float)(2 * _2X) * iconZoom + (float)(8 * _2X) * iconZoom;

			if (ao[PLAYER].equip[EQUIP_BOOTS].type != EMPTY) {
				DrawIcon(GetItemIcon(ao[PLAYER].equip[EQUIP_BOOTS].type, ao[PLAYER].equip[EQUIP_BOOTS].detail, ao[PLAYER].equip[EQUIP_BOOTS].grade), xOffset + bar[BAR_COIN].x + EQUIPICON_X - width / 2, bar[BAR_COIN].y + EQUIPICON_Y + iconZoom * ITEMICONSIZE / 2, iconZoom, false, false, false, true);
				DrawNum(bootsValue, xOffset + bar[BAR_COIN].x + EQUIPICON_X - width / 2 + (float)ITEMICONSIZE * iconZoom + (float)(4 * _2X) * iconZoom, bar[BAR_COIN].y + EQUIPICON_Y + iconZoom * (ITEMICONSIZE - 2 * _2X) / 2, NUM_FONT_LARGE, LEFT, false, PLUS, true, iconZoom * 3 / 4, true);
				DrawImage(8 * _2X, 11 * _2X, 216 * _2X, 141 * _2X, xOffset + bar[BAR_COIN].x + EQUIPICON_X - width / 2 + (float)ITEMICONSIZE * iconZoom + (float)(4 * _2X) * iconZoom + GetNumDx(bootsValue, PLUS, NUM_FONT_LARGE, false, true, iconZoom * 3 / 4, true) + (float)(2 * _2X) * iconZoom, bar[BAR_COIN].y + EQUIPICON_Y + (float)iconZoom * (ITEMICONSIZE - 5 * _2X) / 2, false, false, false, false, false, iconZoom, sprite[EFFECT_IMG], EFFECT_IMG);
			}
		}
		//4. 골드를 획득하고
		else if (attackDelay > ATTACKDELAY_RAIDREWARD_GOLDGET) {

			if (attackDelay == ATTACKDELAY_RAIDREWARD_COIN_BOOTS_RESULT - 1) {
				attackDelay = ATTACKDELAY_RAIDREWARD_COIN_BOOTS_RESULT;

				SetAlpha(32 - Abs(frame / MOTIONDIV % 32 - 16));
				DrawGoldAlpha(xOffset + DX / 2, DY / 2 + TABBUTTONGAP, ALPHA_TABTOCOLLECT, FONT_GOLD_LARGE, 1, CENTER, false, false);
				SetAlpha(32);
				SetRectPoint(0, DY, DX, DY, TOUCH_FUNC_GETRAIDGOLD);
			}
			//여기서 돈이 빨려들어간다.
			else if (attackDelay == ATTACKDELAY_RAIDREWARD_COIN_BOOTS_RESULT - 3) {

			}
		}
		else if (attackDelay > ATTACKDELAY_RAIDREWARD_GOLDTIME) {
			startX = xOffset + DX / 2 - (GetNumDx(bar[BAR_COIN].count + bar[BAR_COIN].add, false, NUM_FONT_NORMAL, false, true, 1.0f, true) + 1 * ITEMICONSIZE + 6 * _2X) / 2 + ITEMICONSIZE / 2;
			startY = bar[BAR_COIN].y - (DRAWROULETTENUM_SUB_HEIGHT / 2);
			targetX = startX + coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 0];
			targetY = startY + coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 1];
			targetX2 = bar[BAR_GOLD].x + 8 * _2X + ITEMICONSIZE / 2;
			targetY2 = bar[BAR_GOLD].y - 8 * _2X - ITEMICONSIZE / 2;
			speed = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 2] / MOTIONDIV;
			speedIncrement = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 3] / MOTIONDIV;
			speed2 = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 4] / MOTIONDIV;
			speedIncrement2 = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 5] / MOTIONDIV;
			waitingFrame = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 6];
			waitingFrame2 = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 7];
			zoom = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 8];
			zoomEnd = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 9];
			zoomIncrement = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 10];
			zoom2 = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 11];
			zoomEnd2 = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 12];
			zoomIncrement2 = coinScatterInfoRaid[(sequenceFrame % 20) * COINSCATTERRAIDINFOSIZE + 13];

			SetCurrencyMark(startX, startY, targetX, targetY, targetX2, targetY2, speed, speedIncrement, speed2, speedIncrement2, waitingFrame, waitingFrame2, ICON_GOLD, 30, dmgInfo[dmgIndex].dmg, CURRENCY_GOLD, zoom, zoomEnd, zoomIncrement, zoom2, zoomEnd2, zoomIncrement2, BAR_GOLD);

		}
		//10. 철수 준비를 한 다음에
		else if (attackDelay > ATTACKDELAY_RAIDREWARD_WARP) {
			if (attackDelay == ATTACKDELAY_RAIDREWARD_GOLDTIME - 1) {
				AddBar(&bar[BAR_GOLD], (bar[BAR_COIN].count + bar[BAR_COIN].add), BARFRAME);
				GetItem(ITEM_GOLD, false, false, false, (bar[BAR_COIN].count + bar[BAR_COIN].add), false);
			}
		}
		//16. 워프로 달려가면 된다. FPS
		else {

		}
		if (attackDelay == 1) {
			amount = dmgInfo[dmgIndex].dmg;

			oldMap = robinmap;

			robinmap = MAP_DIORAMA_TOLEM + castleOrder[robin.castle];

			SetRoom();

			if (doubleBuffer) {
				//if (oldMap != robinmap)
				DoubleBuffering(drawHandle);
			}


			GotoPlay();
#ifdef ENEMYHPBAR
			for (i = 0; i < MAXENEMY; i++) {
				bar[BAR_ENEMYHP + i].active = true;
			}
#endif
			memcpy(&ao[PLAYER], &ao[SOLDIER], sizeof(OBJECT));
			ao[PLAYER].active = true;
			memset(&ao[SOLDIER], 0, sizeof(OBJECT));

			memset(&cardMark, 0, sizeof(cardMark));
			memset(&rewardMark, 0, sizeof(rewardMark));
			memset(&boxMark, 0, sizeof(boxMark));
			memset(&goldAlphaMark, 0, sizeof(goldAlphaMark));

			attackSequence = ATTACKSEQUENCE_REWARD_RAID;
			attackDelay = ATTACKDELAY_REWARD_BATTLE_START + FPS;

			rouletteNum = 0;
			rouletteNumSub = 0;
			rouletteNumBar = 0;
			rouletteNumPvpBar = 0;

			dmgInfo[dmgIndex].dmg = amount;
			dmgInfo[dmgIndex].x = DX / 2;

			areaFrame = 0;
			infoFrame = 0;

			//SetEnemyUser();

			bar[BAR_BOX].active = true;
			bar[BAR_GOLD].active = true;
			bar[BAR_CROWN].active = true;
			bar[BAR_HAMMER].active = true;
			bar[BAR_SHIELD].active = true;
			bar[BAR_QUEST].active = true;

			bar[BAR_COIN].y = STATUSWIN_Y + DRAWROULETTENUMGAP_SUB;
			bar[BAR_RAIDCOIN].active = false;

			bar[BAR_RAIDCOIN].y = STATUSWIN_Y + 128 * _2X;

			if (drawHandle == MD_BATTLE)
				ao[PLAYER].zoom = BATTLEZOOM;
			else
				ao[PLAYER].zoom = LOBBYZOOM;
			bar[BAR_COIN].front = false;

			bar[BAR_COIN].y -= 20 * _2X;
			bar[BAR_ENEMYUSER].y -= 20 * _2X;

			if (robin.bossRoom == true)
				bar[BAR_BOSSHP].active = true;

			//if (actionCardCnt > 0) {
			//	loadRoulette = true;
			//	//LoadRoulette();
			//}
			//else {
			initControlerFrame = 1;
			for (i = 0; i < TOTALCONTROLMARK; i++)
				controlerSpread[i] = true;
			//}

			memset(&controlMark, 0, sizeof(controlMark));

			//infoFrame = INFOFRAME;
		}
		break;
	}

	sequenceFrame++;
}


void InfoDraw(void)
{
	int i, j, k;
	int x, y;
	int gap = -48 * _2X;
	int type;
	int icon;

	//if (drawHandle != MD_PLAY)
	//	return;

	if (explainFrame > 0 && explainText > 0) {
		SetAlpha(16);
		MemRect(0, STATUSWIN_Y + STAGEINFO_Y, DX, 16 * _2X, 0x333333);
		SetAlpha(32);
		SetFontColor(0xFF0000);
		CenterTextSolid(explainText, DX / 2, STATUSWIN_Y + STAGEINFO_Y - 2 * _2X, 1.0f);
	}


	//수신동의 여부
	if (infoFrame > 0) {
		SetAlpha(24);
		MemRect(0, STATUSWIN_Y + STAGEINFO_Y, DX, 16 * _2X, 0x333333);
		SetAlpha(32);
		SetFontColor(0xFF0000);
		CenterTextSolid(infoText, DX / 2, STATUSWIN_Y + STAGEINFO_Y - 2 * _2X, 1.0f);
		SetFontColor(COLOR_WHITE);
	}
	else if (areaFrame > 0) {
		int y;
		switch (drawHandle) {
			//case MD_PLAY:
			//case MD_BATTLE:
			//case MD_RAID:
			//case MD_BOSSRAID:
				//option.gameControl = CONTROL_AUTO;
				//ao[PLAYER].pressedKey[2] = ao[PLAYER].pressedKey[1];
				//ao[PLAYER].pressedKey[1] = ao[PLAYER].pressedKey[0];
				//ao[PLAYER].pressedKey[0] = AVK_6;
			//	break;
		default:
			gap += -8 * _2X;

			switch (areaFrame) {
			case 0:
			case AREAFRAME:
				y = 80 * _2X;
				SetAlpha(8);
				break;
			case 1:
			case AREAFRAME - 1:
				y = 40 * _2X;
				SetAlpha(12);
				break;
			case 2:
			case AREAFRAME - 2:
				y = 20 * _2X;
				SetAlpha(16);
				break;
			case 3:
			case INFOFRAME - 3:
				y = 10 * _2X;
				SetAlpha(20);
				break;
			case 4:
			case AREAFRAME - 4:
				y = 5 * _2X;
				SetAlpha(24);
				break;
			case 5:
			case AREAFRAME - 5:
				y = 3 * _2X;
				SetAlpha(28);
				break;
			default:
				y = 14 * _2X;
				SetAlpha(32);
				break;
			}

			for (i = 0; i < DX; i += 32) {
				//c.bmp
				DrawImage(32 * _2X, 6 * _2X, 158 * _2X, 84 * _2X, i * _2X, STATUSWIN_Y + STAGEINFO_Y + y + gap, false, false, false, 1, false, 1.0f, sprite[COMMON_IMG], COMMON_IMG);
				DrawImage(32 * _2X, 6 * _2X, 158 * _2X, 84 * _2X, i * _2X, STATUSWIN_Y + STAGEINFO_Y - y + gap, false, 180.0f, false, 1, false, 1.0f, sprite[COMMON_IMG], COMMON_IMG);
			}

			SetAlpha(m_lgrpAlpha / 2);
			//MemRect(0, STATUSWIN_Y + STAGEINFO_Y + y + gap, DX, y * 2 - 6 * _2X, 0x121625, gScreenBuffer, gScreenLayer, false);
			SetAlpha(m_lgrpAlpha * 2);

			SetAlpha(32);

			switch (drawHandle) {
			case MD_PLAY:
				break;
			case MD_BATTLE:
				break;
			case MD_RAID:
				break;
			case MD_BOSSRAID:
				break;
			}
			break;
		}

	}

	//투기장인 경우는 Start를 해준다.
	else if (arenaFrame > 0) {
		int temp;
		gap -= 16 * _2X;

		//if (drawHandle == MD_BATTLE)
		//	gap += 100 * _2X;

		if (arenaFrame / 2 < 23 || arenaFrame / 2 > 1)
			temp = 24 * _2X;
		else
			temp = (arenaFrame / 2 > INFOFRAME / 2 ? INFOFRAME - arenaFrame / 2 : arenaFrame / 2) * 12 * _2X;
		//arenaFrame에 따라서 START문구 표시해주고
		SetAlpha(m_lgrpAlpha / 2);
		MemRect(0, STATUSWIN_Y + STAGEINFO_Y + temp / 2 + 5 * _2X + gap, DX, temp + 5 * _2X, 0x121625);
		SetAlpha(m_lgrpAlpha * 2);

		if (arenaFrame / 2 > INFOFRAME - 3 || arenaFrame / 2 < 3)
			DrawBgEffect(3000 + ARENA_FRAME0 + (arenaFrame / 2 > INFOFRAME / 2 ? INFOFRAME - arenaFrame / 2 : arenaFrame / 2), DX / 2, STATUSWIN_Y + STAGEINFO_Y + 3 * _2X + gap, 0, 1.0f);
		else {
			for (i = 0; i < DX + 31 * _2X; i += 32 * _2X)
				DrawBgEffect(3000 + ARENA_FRAME3, i, STATUSWIN_Y + STAGEINFO_Y + 3 * _2X + gap, 0, 1.0f);

			//Start 글씨 띄우기
			SetAlpha(32);

			DrawBgEffect(3000 + ARENA_START, DX / 2, STATUSWIN_Y + STAGEINFO_Y + 3 * _2X + gap, 0, 1.0f);
		}

		SetAlpha(32);
		//현재 보스면
		if (bossOn == true && (drawHandle == MD_PLAY || drawHandle == MD_BATTLE)) {
			if (arenaFrame == INFOFRAME * 2 - 1)
				SetFrameTextStr(textId[TEXT_BOSSAPPEAR], DX, 1, 2.0f, fontGradiation[areaFrame % 21]);
			if (arenaFrame < INFOFRAME * 2 - 1)
				FrameText(textId[TEXT_BOSSAPPEAR], DX / 2 - StringWidth(textId[TEXT_BOSSAPPEAR], _2X) / 2 + 8 * _2X, STATUSWIN_Y + STAGEINFO_Y - 88 * _2X, DX, 1, 0, 2);

			//SetFontColor(COLOR_WHITE);
			CenterText(TEXT_MONSTERNAME_START + GetStageBossType(), DX / 2, STATUSWIN_Y + STAGEINFO_Y - 52 * _2X + gap, _3X);
		}
	}
	else {

	}

	switch (drawHandle) {
	case MD_PLAY:
	case MD_BATTLE:
		//지역명
		x = xOffset + DX / 2 - STAGELABELWIDTH / 2;
		y = STATUSWIN_Y + STAGELABELGAP;

		bar[BAR_COIN].x = DX / 2;
		bar[BAR_COIN].y = STATUSWIN_Y + DRAWROULETTENUMGAP_SUB;

		break;
	case MD_RAID:
		x = xOffset + DX / 2 - 80 * _2X;
		y = DY / 2 + MINDY_MIN2 / 2 - 80 * _2X;

		break;
	case MD_BOSSRAID:

		break;
	}

	if (questFrame > 0) {
		SetAlpha(16);

		for (i = 0; i < DX; i += 32 * _2X) {
			//c.bmp
			DrawImage(32 * _2X, 6 * _2X, 158 * _2X, 84 * _2X, i, STATUSWIN_Y + REALDY - (REALDY / 8 + 14 * _2X), false, false, false, 1, false, 1.0f, sprite[COMMON_IMG], COMMON_IMG);
			DrawImage(32 * _2X, 6 * _2X, 158 * _2X, 84 * _2X, i, STATUSWIN_Y + REALDY - (REALDY / 8 + 36 * _2X), false, 180.0f, false, 1, false, 1.0f, sprite[COMMON_IMG], COMMON_IMG);
		}

		MemRect(0, STATUSWIN_Y + REALDY - (REALDY / 8 + 20 * _2X), DX, 16 * _2X, 0x000000);
		SetAlpha(32);
		CenterTextStrSolid(infoStr, DX / 2, DY / 8 + 2 * _2X + 20 * _2X, 1.0f);
	}
	else if (itemFrame > 0 && ao[cItem].type == OBJ_ITEM && ao[cItem].type != ITEM_STATUE) {

		SetAlpha(16);

		for (i = 0; i < DX; i += 32 * _2X) {
			//c.bmp
			DrawImage(32 * _2X, 6 * _2X, 158 * _2X, 84 * _2X, i, STATUSWIN_Y + REALDY - (REALDY / 8 + 14 * _2X), false, false, false, 1, false, 1.0f, sprite[COMMON_IMG], COMMON_IMG);
			DrawImage(32 * _2X, 6 * _2X, 158 * _2X, 84 * _2X, i, STATUSWIN_Y + REALDY - (REALDY / 8 + 36 * _2X), false, 180.0f, false, 1, false, 1.0f, sprite[COMMON_IMG], COMMON_IMG);
		}

		MemRect(0, STATUSWIN_Y + REALDY - (REALDY / 8 + 20 * _2X), DX, 16 * _2X, 0x000000);
		SetAlpha(32);
		SetFontColor(itemColor[ao[cItem].apy % 10]);

		if (ao[cItem].def == ITEM_GOLD || ao[cItem].ax > 1)
			CenterTextStrSolid(infoStr, DX / 2, STATUSWIN_Y + REALDY - (REALDY / 8 + 2 * _2X + 20 * _2X), 1.0f);
		else
			CenterTextSolid(ao[cItem].name, DX / 2, STATUSWIN_Y + REALDY - (REALDY / 8 + 2 * _2X + 20 * _2X), 1.0f);

		if (nameFrame > 0) {
			ao[talk.obj].icon = ao[talk.obj].iconFrame = null;
			talk.obj = talk.clr = talk.temp = null;
			talk.cur = 0;
			talk.frame = 0;
			talk.temp = 0;
			talk.width = 0;
			nameFrame = 0;
			nameObj = 0;
		}
	}
	else if (nameFrame > 0 && nameObj != 0) {
		GradiationFrame(DX + enemyWinPos[4 + (nameFrame < INFOFRAME - 2 ? 3 : INFOFRAME - nameFrame)], DY - 32 * _2X, -enemyWinPos[4 + (nameFrame < INFOFRAME - 2 ? 3 : INFOFRAME - nameFrame)] * 2, 14 * _2X, 0);
		SetFontColor(0xEFDFB6);
		DrawTextSolid(ao[nameObj].name, DX + enemyWinPos[4 + (nameFrame < INFOFRAME - 2 ? 3 : INFOFRAME - nameFrame)] + 8 * _2X, DY - 33 * _2X, 1.0f);
		if (attackDelay == 0 && menuResult == 0 && keyHandle != MK_ALERT)
			nameFrame--;
		if (nameFrame == 0)
			nameObj = 0;
	}

	if (buffItemUsed > 0) {
		CenterTextStr(buffItemStr, DX / 2, STATUSWIN_Y + REALDY - 192 * _2X - 24 * _2X + 16 * _2X, 2);

		DrawIcon(GetItemIcon(ITEM_WASTE, buffItemUsed, false), DX / 2 - 16 * _2X, STATUSWIN_Y + REALDY - 192 * _2X - 24 * _2X + 40 * _2X, _2X + 16 * _2X, false, false, false, true);
		DrawNeutral(OBJ_BALL0 + (frame % 4), DX / 2, STATUSWIN_Y + REALDY - 192 * _2X - 24 * _2X + 40 * _2X - 8 * 2 * _2X + 16 * _2X, LEFT, 2);
	}

}

//왼쪽 상단에 구출할 캐릭터
//오른쪽 하단에 보스 몬스터
//센터에 시나리오 왜 잡혀갔는지
//하단에 마이킹을 털어줄건지.
//마이킹을 터는 방법

void CrewInfoDraw(int crewIdx, int x, int y, float zoom)
{
	int i;
	int itemType = ITEM_CREW;
	int itemDetail = crewIdx;
	int itemGrade = 0;
	int itemLv = 1;
	int crewType = crewData[crewIdx * CREWDATASIZE + CREWDATA_TYPE];
	int crewCmf = enemyData[crewType * ENEMYDATASIZE + ENEMYDATA_CMF];
	int count = 1;
	float cardZoom = 2.0f * zoom;
	int itemCnt, itemSlot, itemIdx, itemIcon;
	int itemTypeNext, itemDetailNext, itemGradeNext;
	int icon, skillIcon, questIcon, pvpQuestIcon;
	OBJECT* pObj = &ao[PLAYER];
	int collectionIdx;

	ITEM* it;
	float width;
	float YGAP = -48 * _2X;
	int eventIdx = GetEventMenuIdx(EVENTTYPE_DEBTDISCOUNT);
	float discount = 0;

	int crewRewardType = crewReward[crewIdx * CREWREWARDDATASIZE + 0];
	int crewRewardDetail = crewReward[crewIdx * CREWREWARDDATASIZE + 1];
	int crewRewardGrade = crewReward[crewIdx * CREWREWARDDATASIZE + 2];
	long long crewRewardCnt = crewReward[crewIdx * CREWREWARDDATASIZE + 3];
	int crewRewardTime = crewReward[crewIdx * CREWREWARDDATASIZE + 4];

	if (eventIdx != -1)
		discount = robin.gameEvent[eventIdx].value;

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

	if (itemType == ITEM_CREW) {
		curStar = maxStar = enemyData[crewData[itemDetail * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_STAR] + 1;
	}
	else {
		curStar = maxStar = GetItemStar(itemType, itemDetail, itemGrade);
	}

	//카드를 보여주고
	DrawCmfDetailShadow(crewCmf, crewPos[crewType * 5 + 0] + (frame / MOTIONDIV) % crewPos[crewType * 5 + 1], x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)(16 * _2X - crewData[crewIdx * CREWDATASIZE + 6]) * zoom, LEFT, zoom * MONSTERZOOM * enemyZoom[crewType]);
	DrawStar(ICON_STAR, x + (float)(POPUPWINDOWSIZE_X) / 2 * zoom, y - (float)(34 * _2X - crewData[crewIdx * CREWDATASIZE + 6]) * zoom, curStar, maxStar, CREWMAXUPGRADELV, CENTER, true, zoom * 1.2f);

	//이름 써주기
	DrawLabel(x + (float)(POPUPWINDOWSIZE_X / 2 - 40 * _2X) * zoom, y + (float)16 * _2X * zoom, TEXT_MONSTERNAME_START + crewType, zoom);
	//생산량
	memset(&tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%d %s", crewRewardTime / (60 * 60), textId[TEXT_MADA]);

	DrawTextStr(tempStr, x + (float)(32 * _2X) * zoom, y - (float)(226 * _2X) * zoom, zoom);

	if (crewRewardType == ITEM_BOX) {
		DrawBox(crewRewardDetail, x + (float)(POPUPWINDOWSIZE_X / 2 - (float)BOXSIZE_X * 0.5f / 2) * zoom, y - (float)(228 * _2X + ITEMICONSIZE) * zoom, LEFT, false, false, true, false, true, zoom * 0.5f);
	}
	else {
		width = (float)ITEMICONSIZE * zoom + (float)4 * _2X * zoom + GetBigNumDx(crewRewardCnt, false, NUM_FONT_LARGE, false, true, 256 * _2X - 16 * _2X - ITEMICONSIZE - 4 * _2X, zoom, true);
		DrawIcon(GetItemIcon(crewRewardType, crewRewardDetail, crewRewardGrade), x + (float)(POPUPWINDOWSIZE_X / 2) * zoom - width / 2, y - (float)(240 * _2X + ITEMICONSIZE) * zoom, zoom, false, false, false, 1);
		DrawBigNum(crewRewardCnt, x + (float)(POPUPWINDOWSIZE_X / 2) * zoom - width / 2 + (float)(ITEMICONSIZE + 4 * _2X) * zoom, y - (float)(240 * _2X + ITEMICONSIZE - 1 * _2X) * zoom, NUM_FONT_LARGE, LEFT, false, false, (float)(256 * _2X - 16 * _2X - ITEMICONSIZE - 4 * _2X) * zoom, true, zoom, true);
	}

}

void DiscountMenuDraw(int x, int y, float zoom)
{
	int i, j;
	int width;
	int icon = pvpQuestInfo[robin.pvpQuest * PVPQUESTINFODATASIZE + 0];
	OBJECT* pObj = &ao[PLAYER];
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	gEvent = &robin.gameEvent[GetEventMenuIdx(EVENTTYPE_DEBTDISCOUNT)];
	int collectionIdx = GetCollectionIdx(it->type, it->detail, it->grade);

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

	DrawWindow5(x + (float)(16 * _2X) * zoom, y - (float)(124 * _2X) * zoom, (float)(POPUPWINDOWSIZE_X - 32 * _2X) * zoom, (float)(POPUPWINDOWSIZE_Y - 152 * _2X) * zoom, TOLEMHOUSE2, zoom, 0);

	ShadowImage(40 * _2X, 16 * _2X, 26 * _2X, 1 * _2X, x + (float)(POPUPWINDOWSIZE_X / 2 - 40 * _2X * 2 / 2) * zoom, y + (float)(-160 * _2X + 8 * _2X * 3) * zoom, SHADOW_IMG, 2 * zoom);
	DrawNeutral(EFFECT_CRAFT0 + (frame / 2) % 3, x + (float)(POPUPWINDOWSIZE_X / 2) * zoom, y - (float)(160 * _2X) * zoom, 0, 4 * zoom);

	CenterText(TEXT_EVENT_DISCOUNT, x + (float)(POPUPWINDOWSIZE_X / 2) * zoom, y - (float)(4 * _2X) * zoom, zoom);


	//남은 시간
	DrawText(TEXT_REMAINTIME, x + (float)64 * _2X * zoom, y - (float)452 * _2X * zoom, zoom);

	DrawTime(x + (float)128 * _2X * zoom, y - (float)450 * _2X * zoom, Max(gEvent->limitTime - (MC_knlCurrentTimeStamp() - gEvent->timeStamp), 0), TIME_MINUTE_SECONDS, LEFT, zoom);

	//
	DrawTextButton(x + (POPUPWINDOWSIZE_X / 2 - 80 * _2X / 2) * zoom, y - (POPUPWINDOWSIZE_Y - 4 * ITEMICONSIZE) * zoom, (float)(80 * _2X) * zoom, (float)(28 * _2X) * zoom, FRAME_GREEN, false, zoom, false, TEXT_GOTOUPGRADE);
	SetRectPoint(x + (POPUPWINDOWSIZE_X / 2 - 80 * _2X / 2) * zoom, y - (POPUPWINDOWSIZE_Y - 4 * ITEMICONSIZE) * zoom, (float)(80 * _2X) * zoom, (float)(28 * _2X) * zoom, TOUCH_FUNC_COLLECTIONS_DETAIL + collectionIdx);
}


void PvpQuestMenuDraw(int x, int y, float zoom)
{
	int i, j;
	int width;
	int icon = pvpQuestInfo[robin.pvpQuest * PVPQUESTINFODATASIZE + 0];
	OBJECT* pObj = &ao[PLAYER];
	gEvent = &robin.gameEvent[GetEventMenuIdx(EVENTTYPE_PVP)];
	float pvpBarZoom = 1.0f;
	int tempBarStatus = gEvent->barStatus;
	float PVPREWARDZOOM = 0.65f;

	gEvent->barStatus = EVENT_BAR_REWARDGET;

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

	CenterText(TEXT_PVPQUESTNAME0 + robin.pvpQuest, x + (float)(POPUPWINDOWSIZE_X / 2) * zoom, y - (float)(4 * _2X + 8 * _2X) * zoom, zoom);

	PvpEventBarDraw(gEvent, x + (float)(POPUPWINDOWSIZE_X / 2 - PVPQUESTBARWIDTH / 2 * pvpBarZoom + 8 * _2X * pvpBarZoom) * zoom, y - (float)(36 * _2X) * zoom, pvpQuestInfo[robin.pvpQuest * PVPQUESTINFODATASIZE + 0], robin.pvpQuestCnt, pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + TOTALPVPDETAILREQUEST - 1], false, true, zoom * pvpBarZoom);
	gEvent->barStatus = tempBarStatus;

	MedalBarDraw(x + (float)(POPUPWINDOWSIZE_X / 2 - MEDALBARWIDTH / 2) * zoom, y - (float)(88 * _2X) * zoom, robin.pvpQuestCnt, false, zoom);

	DrawWindow4(x + (float)(16 * _2X) * zoom, y - (float)(124 * _2X) * zoom, (float)(POPUPWINDOWSIZE_X - 32 * _2X) * zoom, (float)(POPUPWINDOWSIZE_Y - 152 * _2X) * zoom, MAPTYPE_FLAME, 1.0f);

	//레이드 보상
	DrawIcon(ICON_RAID, x + (float)(POPUPWINDOWSIZE_X / 2 - MEDALREWARDSIZESMALL_X / 2 - 16 * _2X) * zoom, y + (float)(-132 * _2X) * zoom, zoom * 1.5f, COLOR_BROWN, false, false, true);
	DrawText(TEXT_RAID_JOKBO_DESC, x + (float)(POPUPWINDOWSIZE_X / 2 - MEDALREWARDSIZESMALL_X / 2 - 16 * _2X + (float)(ITEMICONSIZE + 8 * _2X) * 1.5f) * zoom, y + (float)(-132 * _2X - 8 * _2X) * zoom, zoom);

	for (i = 0; i < 3; i++) {
		DrawMedalReward(ROULETTE_RAID, x + (float)(POPUPWINDOWSIZE_X / 2 - MEDALREWARDSIZESMALL_X / 2 + 16 * _2X) * zoom, y + (float)(-124 * _2X - 8 * _2X - 32 * _2X - (float)(MEDALREWARDSIZESMALL_Y + 16 * _2X) * PVPREWARDZOOM * i) * zoom, DX - 16 * _2X, BATTLEREWARDBOX_Y, HITCARD_RESULT, i, false, zoom * PVPREWARDZOOM);
	}

	//배틀 보상
	DrawIcon(ICON_BATTLE, x + (float)(POPUPWINDOWSIZE_X / 2 - MEDALREWARDSIZESMALL_X / 2 - 16 * _2X) * zoom, y + (float)(-272 * _2X) * zoom, zoom * 1.5f, COLOR_BROWN, false, false, true);
	DrawText(TEXT_BATTLE_JOKBO_DESC, x + (float)(POPUPWINDOWSIZE_X / 2 - MEDALREWARDSIZESMALL_X / 2 - 16 * _2X + (float)(ITEMICONSIZE + 8 * _2X) * 1.5f) * zoom, y + (float)(-272 * _2X - 8 * _2X) * zoom, zoom);

	for (i = 0; i < 2; i++) {
		DrawMedalReward(ROULETTE_BATTLE, x + (float)(POPUPWINDOWSIZE_X / 2 - MEDALREWARDSIZESMALL_X / 2 + 16 * _2X) * zoom, y + (float)(-272 * _2X - 32 * _2X - (MEDALREWARDSIZESMALL_Y + 16 * _2X) * PVPREWARDZOOM * i) * zoom, DX - 16 * _2X, BATTLEREWARDBOX_Y, HITCARD_RESULT, i, false, zoom * PVPREWARDZOOM);
	}


	//남은 시간
	DrawText(TEXT_REMAINTIME, x + (float)(108 * _2X) * zoom, y - (float)(448 * _2X - 72 * _2X) * zoom, zoom);

	DrawTime(x + (float)(160 * _2X) * zoom, y - (float)(448 * _2X - 72 * _2X) * zoom, Max(gEvent->limitTime - (MC_knlCurrentTimeStamp() - gEvent->timeStamp), 0), TIME_HOUR_MINUTE, LEFT, zoom);
}

void QuestMenuDraw(int x, int y, float zoom)
{
	int i, j;
	int width;
	int icon;
	OBJECT* pObj = &ao[PLAYER];
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	gEvent = &robin.gameEvent[GetEventMenuIdx(EVENTTYPE_QUEST)];

	icon = gEvent->icon;

	DrawImage(POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, 0, 0, x, y, false, false, false, false, false, zoom, sprite[UI_PAPER_POPUP_IMG], UI_PAPER_POPUP_IMG);

	CenterText(TEXT_QUESTNAME0 + robin.quest, x + (float)(POPUPWINDOWSIZE_X / 2) * zoom, y - (float)(28 * _2X - 16 * _2X) * zoom, zoom);

	DrawWindow4(x + (float)(16 * _2X) * zoom, y - (float)(80 * _2X - 24 * _2X) * zoom, (float)(POPUPWINDOWSIZE_X - 32 * _2X) * zoom, (float)(POPUPWINDOWSIZE_Y - 80 * _2X) * zoom, MAPTYPE_SWAMP, 1.0f * zoom);

	DrawLabel(x + (float)(POPUPWINDOWSIZE_X / 2) * zoom - (float)(40 * _2X) * zoom, y - (float)(64 * _2X - 32 * _2X) * zoom, TEXT_GRANDPRIZE, zoom);

	//DrawCmfDetailShadow(enemyData[questInfo[robin.quest * QUESTINFODATASIZE] * ENEMYDATASIZE + 0], frame / 2 % 4, x + (float)(48 * _2X) * zoom, y - (float)(88 * _2X) * zoom, RIGHT, zoom, cvtDest, cvtLayer, buffering);

	//DrawIcon(icon, x + (float)(248 * _2X) * zoom, y - (float)(56 * _2X) * zoom, 2.0f * zoom, COLOR_BROWN, false, true, cvtDest, cvtLayer, buffering);

	//바를 그려주기
	MemRectRound(x + (float)(36 * _2X) * zoom, y - (float)(160 * _2X - 44 * _2X) * zoom, (float)(16 * _2X) * zoom, (float)(240 * _2X) * zoom, COLOR_NAVY, 2);
	MemRectRound(x + (float)(36 * _2X + 2 * _2X) * zoom, y - (float)(160 * _2X - 44 * _2X) * zoom, (float)(12 * _2X) * zoom, (float)(238 * _2X) * zoom, COLOR_ORANGE, 2);

	SetAlpha(30);
	DrawFrame(x + (float)(32 * _2X) * zoom, y - (float)(104 * _2X - 40 * _2X) * zoom, (float)(POPUPWINDOWSIZE_X - 32 * _2X * 2) * zoom, (float)(REWARDCARDSIZE_Y)*zoom, FRAME_GREEN);
	SetAlpha(32);

	if (questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (subQuestCnt[robin.quest] - 1) * QUESTREWARDDATASIZE + 0] == ITEM_CREW) {
		curStar = maxStar = crewData[questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (subQuestCnt[robin.quest] - 1) * QUESTREWARDDATASIZE + 1] * CREWDATASIZE + CREWDATASIZE - 1] + 1;
	}
	else {
		curStar = maxStar = GetItemStar(questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (subQuestCnt[robin.quest] - 1) * QUESTREWARDDATASIZE + 0], questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (subQuestCnt[robin.quest] - 1) * QUESTREWARDDATASIZE + 1], questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (subQuestCnt[robin.quest] - 1) * QUESTREWARDDATASIZE + 2]);
	}

	DrawRewardCard(questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (subQuestCnt[robin.quest] - 1) * QUESTREWARDDATASIZE + 0], questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (subQuestCnt[robin.quest] - 1) * QUESTREWARDDATASIZE + 1], questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (subQuestCnt[robin.quest] - 1) * QUESTREWARDDATASIZE + 2], 1, questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (subQuestCnt[robin.quest] - 1) * QUESTREWARDDATASIZE + 3], x + (float)(POPUPWINDOWSIZE_X / 2 - REWARDCARDSIZE_X * 1.5f / 2) * zoom, y - (float)(96 * _2X - 40 * _2X) * zoom, false, zoom * 1.5f, false, false, true, curStar, maxStar, true, 0);

	DrawNeutral(OBJ_ITEM0 + frame % 4, x + (float)(POPUPWINDOWSIZE_X / 2) * zoom, y + (-108 * _2X + 40 * _2X - ITEMICONSIZE * 2) * zoom, 0, 2 * zoom);


	//5개 정도 보여주자
	for (i = 0; i < 5; i++) {
		SetAlpha(30);
		DrawFrame(x + (float)(64 * _2X) * zoom, y + (float)(-368 * _2X + 44 * _2X + (REWARDCARDSIZE_Y * 0.9f) * i) * zoom, (float)(POPUPWINDOWSIZE_X - 128 * _2X) * zoom, (float)(REWARDCARDSIZE_Y) * 0.9f * zoom, (i == 0 ? FRAME_BLUE : FRAME_GREY));
		SetAlpha(32);
		DrawIcon((i == 0 ? ICON_EVENT_CROWN : ICON_EVENT_LOCK), x + (float)(36 * _2X) * zoom, y + (float)(-360 * _2X + 44 * _2X + (REWARDCARDSIZE_Y * 0.9f) * i - REWARDCARDSIZE_Y / 2 + 7 * _2X) * zoom, zoom, COLOR_BROWN, i == 0 ? true : false, false, true);

		if (questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (robin.subQuest + i) * QUESTREWARDDATASIZE + 0] == ITEM_CREW) {
			curStar = maxStar = crewData[questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (robin.subQuest + i) * QUESTREWARDDATASIZE + 1] * CREWDATASIZE + CREWDATASIZE - 1] + 1;
		}
		else {
			curStar = maxStar = GetItemStar(questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (robin.subQuest + i) * QUESTREWARDDATASIZE + 0], questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (robin.subQuest + i) * QUESTREWARDDATASIZE + 1], questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (robin.subQuest + i) * QUESTREWARDDATASIZE + 2]);
		}

		DrawRewardCard(questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (robin.subQuest + i) * QUESTREWARDDATASIZE + 0], questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (robin.subQuest + i) * QUESTREWARDDATASIZE + 1], questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (robin.subQuest + i) * QUESTREWARDDATASIZE + 2], 1, questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (robin.subQuest + i) * QUESTREWARDDATASIZE + 3], x + (float)(POPUPWINDOWSIZE_X / 2 - REWARDCARDSIZE_X * 1.2f / 2) * zoom, y + (float)(-368 * _2X + 44 * _2X + (REWARDCARDSIZE_Y * 0.9f) * i + 4 * _2X) * zoom, false, zoom * 1.2f, false, false, true, curStar, maxStar, true, 0);
	}

	//남은 시간
	DrawText(TEXT_REMAINTIME, x + (float)(120 * _2X) * zoom, y - (float)(448 * _2X - 72 * _2X) * zoom, zoom);

	DrawTime(x + (float)(168 * _2X) * zoom, y - (float)(448 * _2X - 72 * _2X) * zoom, Max(gEvent->limitTime - (MC_knlCurrentTimeStamp() - gEvent->timeStamp), 0), TIME_HOUR_MINUTE, LEFT, zoom);
}


//addPixel의 
void QuestDraw(int x, int y, int icon, int count, int max, float animation, bool questAni, int enemyIconShow, int rewardIconShow, int alpha, float zoom)
{
	float w = (float)QUESTBARWIDTH * zoom;
	float h = (float)QUESTBARHEIGHT * zoom;
	int rewardType = questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + robin.subQuest * QUESTREWARDDATASIZE + 0];
	int rewardDetail = questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + robin.subQuest * QUESTREWARDDATASIZE + 1];
	int rewardGrade = questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + robin.subQuest * QUESTREWARDDATASIZE + 2];
	int rewardIcon = GetItemIcon(rewardType, rewardDetail, rewardGrade);
	long long rewardCnt = questReward[robin.quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + robin.subQuest * QUESTREWARDDATASIZE + 3];
	gEvent = &robin.gameEvent[GetEventMenuIdx(EVENTTYPE_QUEST)];
	float zoomOrigin = zoom;
	float ENEMYICONZOOM_X = 0.7f;
	float ENEMYICONZOOM_Y = 0.6f;
	//체력바형태로 변경

	if (robin.subQuest >= TOTALSUBQUEST)
		return;

	DrawRoundBar(x + (float)0 * zoom, y, (float)count / max, ROUNDBAR_BIG, BARCOLOR_GREEN, alpha, 0.5f * zoom);

	//TEST
	//count = 100;
	//max = 100;

	DrawIcon(icon, x - (float)ITEMICONSIZE * 1.6f * zoom - (float)4 * _2X * zoom, y - (float)4 * _2X * zoom, zoom * 1.6f, COLOR_WHITE, animation, false, 1.6f);

	DrawSlashNum(count, max, x + w / 2, y - (float)(10 * _2X) * zoom, w, 1.2f * zoom);

	if (rewardIconShow > 0) {
		if (rewardType == ITEM_CREW) {
			curStar = maxStar = crewData[rewardDetail * CREWDATASIZE + CREWDATASIZE - 1] + 1;
		}
		else {
			curStar = maxStar = GetItemStar(rewardType, rewardDetail, rewardGrade);
		}

		DrawRewardCard(rewardType, rewardDetail, rewardGrade, 1, rewardCnt, x + w - (float)(rewardType == ITEM_BOX ? 8 * _2X : 8 * _2X) * zoom, y + (float)8 * _2X * zoom, false, 1.2f * zoom, false, false, true, curStar, maxStar, true, 0);
	}

	if (menuPressPossible())
		SetRectPoint(x, y, w, h, TOUCH_FUNC_EVENT_QUEST);

}

void RaidBoxDraw(int x, int y, float zoom, bool touch, bool shadow)
{
	int i;
	int j = 0;

	for (i = 0; i < TOTALRAIDBOX; i++) {
		switch (raidBox[i].motion) {
		case BOXSTATUS_APPEAR:
			if (curtainFrame == 0) {
				raidBox[i].motion = OBJ_BOX0;
				raidBox[i].frame++;
				raidBox[i].zoom += 0.2f / MOTIONDIV;
				if (raidBox[i].zoom > BOXCASTLEZOOM)
					raidBox[i].zoom = BOXCASTLEZOOM;
				//SetAlpha(ao[i].frame);
			}

			if (raidBox[i].frame == FPS) {
				raidBox[i].status = BOXSTATUS_CLOSED;
				raidBox[i].frame = 0;
			}

			break;
		case BOXSTATUS_CLOSED:
			raidBox[i].motion = OBJ_BOX0 + boxNeutralAnimation[((raidBox[i].frame / (MOTIONDIV * 2)) % 4)];
			raidBox[i].frame++;
			break;
		case BOXSTATUS_OPENING:
			raidBox[i].motion = Min(OBJ_BOX5, OBJ_BOX0 + raidBox[i].frame / (MOTIONDIV * 2));
			raidBox[i].frame++;
			if (raidBox[i].motion == OBJ_BOX5) {
				if (raidBox[i].gold == false)
					raidBox[i].status = BOXSTATUS_EMPTY;
				else
					raidBox[i].status = BOXSTATUS_OPENED;
				raidBox[i].frame = 0;
			}
			break;
		case BOXSTATUS_OPENED:
			//raidBox[i].motion = OBJ_BOX3 + raidBox[i].frame / (MOTIONDIV * 2) % 4;
			raidBox[i].motion = OBJ_BOX6;
			raidBox[i].frame++;
			break;
		case BOXSTATUS_CLOSING:
			raidBox[i].motion = OBJ_BOX5 - raidBox[i].frame / (MOTIONDIV * 2);
			raidBox[i].frame++;
			if (raidBox[i].motion == OBJ_BOX0) {
				raidBox[i].status = BOXSTATUS_CLOSED;
				raidBox[i].motion = OBJ_BOX0;
				raidBox[i].frame = 0;
			}
			break;
		case BOXSTATUS_EMPTY:
			raidBox[i].motion = OBJ_BOX6;
			break;
		}

		if (shadow == true)
			ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X, x + raidBox[i].x - (float)(12 * _2X) * zoom, y + raidBox[i].y + (float)(8 * _2X) * BOXCASTLEZOOM * zoom, SHADOW_IMG, zoom);

		DrawNeutral(raidBox[i].motion, x + raidBox[i].x, y + raidBox[i].y, LEFT, zoom);
		if (touch == true && raidBox[i].status != BOXSTATUS_OPENED && raidBox[i].status != BOXSTATUS_EMPTY) {
			SetRectPoint(x + raidBox[i].x - (float)24 * _2X * zoom, y + raidBox[i].y + (float)(ITEMICONSIZE * 1.0f + 2 * _2X) * zoom * 2, (float)(ITEMICONSIZE * 1.5f) * zoom * 2, (float)(ITEMICONSIZE * 1.5f) * zoom * 2, TOUCH_FUNC_RAID_TARGET + i);
			DrawHand(x + raidBox[i].x - (float)16 * _2X * zoom, y + raidBox[i].y + (float)(ITEMICONSIZE * 1.0f + 2 * _2X) * zoom * 2, robin.playtime / MOTIONDIV, 1.5f * zoom);
		}
#ifdef GUIDELINE
		DrawNum(raidBox[i].gold, x + raidBox[i].x, y + raidBox[i].y - 8 * _2X, NUM_FONT_NORMAL, CENTER, false, false, true, zoom / 2, true);
#endif
	}
}

void RaidControlerDraw(void)
{
	int i, j;

	//하트
	startX = xOffset + 52 * _2X;
	startY = STATUSWIN_Y - 60 * _2X;

	//startY = STATUSWIN_Y2 + HEARTBARGAP - 90 * _2X;

	for (i = 0; i < TOTALRAIDCHANCE; i++) {
		if (i < raidChance) {
			DrawNeutral(OBJ_BOX0 + boxNeutralAnimation[((frame / (MOTIONDIV * 2 * 2)) % 4)], startX + 28 * _2X * i, startY, LEFT, 1.0f);

		}
		else {
			grayScale = 32;
			DrawNeutral(OBJ_BOX6, startX + 28 * _2X * i, startY, LEFT, 1.0f);
			grayScale = 0;
			//DrawAlpha(startX + 28 * _2X * i - 1 * ITEMICONSIZE + 4 * _2X, startY + 1 * ITEMICONSIZE + 4 * _2X, ALPHA_X, FONT_SMALL, 3.0f, false, gScreenBuffer, gScreenLayer, false);
		}
	}

}

void SetScreenRatio(void)
{
	GNBHEIGHT = GNB_INIT_HEIGHT;
	BOTTOMMENUHEIGHT = BOTTOMMENU_INIT_HEIGHT;

	if (SCREENRATIO <= 167) {//3:5
	}

	if (SCREENRATIO >= 200) {//9:18.5(!)
		GNBHEIGHT += NORCH_HEIGHT;
		BOTTOMMENUHEIGHT += HOMEBAR_HEIGHT;
	}
	else
		HOMEBAR_HEIGHT = 0;
#ifndef CENTERDISPLAY
	if (SCREENRATIO <= 150)
		MINDY -= GNBHEIGHT + BOTTOMMENUHEIGHT;
#endif

#ifdef CENTERDISPLAY
	switch (drawHandle) {
		//case MD_BATTLE:
		//case MD_RAID:
		//case MD_HOUSE:
		//	PLAYAREA_Y = 22 * TSIZE;
		//	REALDY = PLAYAREA_Y;
		//	STATUSWIN_Y = DY / 2 - 142 * _2X;
		//	break;
	default:
		PLAYAREA_Y = 22 * TSIZE;
		REALDY = PLAYAREA_Y;
		//STATUSWIN_Y = DY / 2 + (float)(-360 * _2X + DIORAMA_GAPY) * dioramaZoom + 16 * _2X;
		STATUSWIN_Y = STATUSWIN_Y_INIT = DY - GNBHEIGHT + (float)(-DIORAMASIZE_Y) * DIORAMAZOOM_BATTLE + 108 * _2X - (SCREENRATIO - 134) * 3;
		STATUSWIN_Y2 = STATUSWIN_Y - 64 * _2X;
		//PLAYAREA_Y = 22 * TSIZE;
		//REALDY = PLAYAREA_Y;
		//STATUSWIN_Y = 302 * _2X + BOTTOMMENUHEIGHT;
		break;
	}

#else
	PLAYAREA_Y = 180 * _2X + Min(140 * _2X, Max(0, (SCREENRATIO - 133) * 3 * _2X));
	REALDY = PLAYAREA_Y;
	STATUSWIN_Y = DY - REALDY;
#endif

	

	INVEN_VCNT = 3;
	if ((DY - MINDY - GNBHEIGHT - BOTTOMMENUHEIGHT) / (INVEN_ICON_VGAP + INVEN_ICON_SIZE) > 0)
		INVEN_VCNT += (DY - MINDY - GNBHEIGHT - BOTTOMMENUHEIGHT) / (INVEN_ICON_VGAP + INVEN_ICON_SIZE);
	INVEN_TCNT = INVEN_HCNT * INVEN_VCNT;

	EQUIP_WIN_HEIGHT = EQUIPWIN_DEFAULT + INVEN_VCNT * (INVEN_ICON_SIZE + INVEN_ICON_VGAP);
	//EQUIP_WIN_HEIGHT = MINDY;

	POPUPPOSITION_Y = DY / 2;// Min(DY / 2, DY - GNBHEIGHT - POPUPWINDOWSIZE_Y / 2 + 16 * _2X);

	//bar[BAR_BOSSHP].y = bar[BAR_HEART].y + BOSSHPBARHEIGHT - 16 * _2X;
	//dioramaZoomGap = (float)(220 - SCREENRATIO) / 100 / 2;

}

void SetHero(void)
{
	int i;
	int doorY = 256 * _2X;
	int playerCnt = MAXPLAYER;

	//3명을 모두 세팅한다.
	for (i = 0; i < playerCnt; i++) {

		//for (i = NEUTRAL; i < ITEMOBJ; i++) {
		//	if (ao[i].type == OBJ_DOOR) {
		//		//doorY = ao[i].y + 32 * _2X;
		//		ao[i].status = OPENED;
		//		MoveObj(&ao[i]);
		//		break;
		//	}
		//}
		//if (IsGetHero(i)) {
		if (IsGetHero(i)) {
			LoadHeroObj(i);

			switch (drawHandle) {
			//case MD_PLAY:
			default:
				ao[PLAYER + i].nx = ao[PLAYER + i].x = setHeroPos[castleOrder[robin.castle] * 2 * TOTALCHAR + i * 2 + 0];
				ao[PLAYER + i].ny = ao[PLAYER + i].y = setHeroPos[castleOrder[robin.castle] * 2 * TOTALCHAR + i * 2 + 1];// doorY + TSIZE;
				ao[PLAYER + i].defaultZoom = ao[PLAYER + i].zoom = heroZoom[i] * HEROZOOM;
				ao[PLAYER + i].dirF = ao[PLAYER + i].dirX = RIGHT;
				ao[PLAYER + i].moveHandler = REGENMOVE;
				ao[PLAYER + i].drawHandler = REGENDRAW;
				ao[PLAYER + i].dead = true;
				ao[PLAYER + i].frame = -(crewCnt + heroCnt - i) * FPS / 3;
				ao[PLAYER + i].active = false;

				break;
			}
			ao[PLAYER + i].playerRun = false;
			ao[PLAYER + i].dx = 0;
			ao[PLAYER + i].flamer = null;
			GetTile(&ao[PLAYER + i]);

			InitStatue(&ao[PLAYER + i]);

			ao[PLAYER + i].name = TEXT_MONSTERNAME_START + i;// +TEXT_NICKNAME + Random(100);
			profileImg[0] = PROFILE_IMG;
			//ao[PLAYER + i].active = true;
			//SetEnemy(&ao[MAXPLAYER + i]);

			//if (IsGetHero(i) == false)
			//ao[PLAYER + i].active = IsGetHero(i);

		}
	}

	switch (drawHandle) {
	case MD_PLAY:
		/*
		ao[NEUTRAL].x = 16 * _2X;
		ao[NEUTRAL].y = (rh - 7) * TSIZE;
		ao[NEUTRAL].type = OBJ_BOX;
		ao[NEUTRAL].active = true;
		ao[NEUTRAL].
		*/
		break;
	case MD_BATTLE:
		break;
	}
}

//몬스터나 NPC 동료를 추가
void SetBattleCrew()
{
	int i, j = 0;
	int crewIdx;
	int newCnt = 0;

	//예전에는 맨 앞에서 ao[CREW..CREW+MAXCREW)를 전부 memset하고 다시 만들면서 모든 동료에게
	//REGENMOVE(등장 낙하 연출)를 걸었다. 그런데 이 함수는 동료를 새로 하나 얻을 때마다 불린다
	//(Func_Item.cpp의 GetItem() ITEM_CREW 자동장착 경로). 그래서 동료 한 명을 획득할 때마다
	//이미 자리에 서 있던 기존 동료들까지 전부 등장 연출을 처음부터 다시 하는 문제가 있었다.
	//지금은 슬롯 단위로 보고, "새로 배치되는 슬롯"만 등장 연출을 태운다.
	for (i = 0; i < MAXCREW; i++) {
		bool keep;

		//빈 슬롯은 비워둔다.
		if (i >= crewCnt || robin.slotCrew[i] == -1) {
			memset(&ao[CREW + i], false, sizeof(OBJECT));
			continue;
		}

		//같은 동료가 이미 이 슬롯에 자리잡고 있으면(서 있거나 등장 연출 진행 중) 오브젝트를
		//다시 만들지 않는다.
		keep = (ao[CREW + i].type == robin.slotCrew[i]
			&& (ao[CREW + i].active == true || ao[CREW + i].moveHandler == REGENMOVE));

		if (keep == false) {
			memset(&ao[CREW + i], false, sizeof(OBJECT));

			ao[CREW + i].type = robin.slotCrew[i];
			ao[CREW + i].cmf = enemyData[ao[CREW + i].type * ENEMYDATASIZE + ENEMYDATA_CMF];

			//SetNpc()는 active/motion/moveHandler/drawHandler/hp까지 덮어쓰므로
			//새로 배치하는 슬롯에서만 부른다. 유지되는 슬롯에 부르면 CREWMOVE가 NPCMOVE로 바뀐다.
			SetNpc(&ao[CREW + i]);

			ao[CREW + i].defaultZoom = ao[CREW + i].zoom = (float)enemyIconZoom[ao[CREW + i].type] * CREWZOOM;

			ao[CREW + i].active = false;
			ao[CREW + i].dead = true;

			//등장 시차는 "이번에 새로 배치되는 순번" 기준이다. 슬롯번호(i)로 잡으면 뒤쪽 슬롯에
			//한 명만 추가됐을 때 그 슬롯 수만큼 늦게 등장한다.
			ao[CREW + i].frame = -newCnt * FPS / 3;

			ao[CREW + i].moveHandler = REGENMOVE;
			ao[CREW + i].drawHandler = REGENDRAW;
			ao[CREW + i].status = CREW_STATUS_NEUTRAL;
			ao[CREW + i].dirF = ao[CREW + i].dirX = RIGHT;

			newCnt++;
		}

		//위치와 스탯/스킬은 유지되는 슬롯도 최신값으로 맞춰준다(성이 바뀌면 자리 좌표가 달라진다).
		ao[CREW + i].nx = (float)castleCrewPosition[castleOrder[robin.castle] * MAXCREW * 2 + i * 2 + 0];
		ao[CREW + i].ny = (float)castleCrewPosition[castleOrder[robin.castle] * MAXCREW * 2 + i * 2 + 1];

		//등장 연출 중에는 현재 좌표를 건드리지 않는다(공중에서 순간이동해 보인다).
		if (ao[CREW + i].moveHandler != REGENMOVE) {
			ao[CREW + i].x = ao[CREW + i].nx;
			ao[CREW + i].y = ao[CREW + i].ny;
		}
		else if (keep == false) {
			ao[CREW + i].x = ao[CREW + i].nx;
			ao[CREW + i].y = ao[CREW + i].ny;
		}

		//GetCrewIdxFromType()은 크루 데이터에 없는 타입이면 -1을 준다.
		//가드 없이 쓰면 crewData[-CREWDATASIZE + ...]로 배열 밖을 읽는다.
		crewIdx = GetCrewIdxFromType(ao[CREW + i].type);

		if (crewIdx >= 0) {
			ao[CREW + i].ps[PS_DMG] = ao[CREW + i].str = crewData[crewIdx * CREWDATASIZE + CREWDATA_STR];

			for (j = 0; j < TOTALREEL; j++)
				ao[CREW + i].getSkillList[j] = crewData[crewIdx * CREWDATASIZE + CREWDATA_SKILL1 + j];
		}
	}
}