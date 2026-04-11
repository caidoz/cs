#include "Core.h"
#include "Func.h"
#include "Data.h"
#include "Text.h"

// KeyPress

void KeyCore(void)
{
	if (is_release_finished == false && is_key_released == true && twice_released == false && systemKey != systemRelease) {
		systemRelease = null;
		is_release_finished = true;
		is_key_released = false;
	}

#ifdef DEBUG
	if (debug == 0) {
#endif

		if (keyLock)
			return;
		switch (systemKey) {
		case AVK_LEFT:
			systemKey = AVK_4;
			break;
		case AVK_RIGHT:
			systemKey = AVK_6;
			break;
		case AVK_UP:
			systemKey = AVK_2;
			break;
		case AVK_DOWN:
			systemKey = AVK_8;
			break;
		case AVK_SELECT:
			systemKey = AVK_5;
			break;
		}

#ifdef DEBUG
	}
#endif

	//if (netStatus == NETSTATUS_LOCK) {
	//	netStatus = NETSTATUS_OFFLINE;
	//}
	//else {
		switch (keyHandle) {
		case MK_DEMO:
			DemoKey();
			break;
		}
	//}

	if (touchDrawButton == true && touch && (systemKey == AVK_5 || systemKey == AVK_CLR)) {
		touchDrawButton = false;
	}

	if ((touchQuickIcon != false && touch && systemKey == AVK_CLR))
		touchQuickIcon = false;

	systemRelease = null;
	is_key_pressed = false;
	is_press_finished = true;
}

void TitleKey(void)
{
	int i, j;
	int doorY;
	switch (curMenu) {
	case MENU_LOADING://맨 처음에 100 박히는 화면연출
		switch (systemKey) {
		case AVK_5:
			memset(&scY, 0, sizeof(scY));

			PlayMusic(M_SELECT);
			break;
		case AVK_GOTODEMO:
			NewGame();
			SetHero();
			j = 0;
			//현재 어디 데모신까지 봤는지 확인한다.
			for (i = 0; i < TOTALDEMO; i++) {
				robin.demoSeen[i] = false;
				if (robin.demoSeen[i] == true)
					j++;
				else
					break;
			}

			//모든 데모신을 다봤으면
			if (j == TOTALDEMO) {
				robinmap = false;
			}
			else
				robinmap = demoData[j * 7];

			SetRoom();
			areaFrame = 0;
			SetDemo(DEMO_OPENING_PRINCESS);
			break;
		}
		break;
	case MENU_LOGIN://로그인 이력이 없으면 로그인선택
		switch (systemKey) {
		case AVK_LOGIN_FACEBOOK:
			menuResult = 0;
			PlayMusic(M_SELECT);
			break;
		case AVK_LOGIN_GOOGLE:
			menuResult = 0;
			PlayMusic(M_SELECT);
			break;
		case AVK_LOGIN_APPLE:
			menuResult = 0;
			PlayMusic(M_SELECT);
			break;
		case AVK_LOGIN_GUEST:
			menuResult = 0;
			PlayMusic(M_SELECT);
			break;
		}
		break;
	case MENU_POLICY://약관동의
		switch (systemKey) {
		case AVK_5:
			PlayMusic(M_SELECT);
			break;
		}
		break;
	}
}

void BossRaidKey(void)
{
	switch (menuDepth) {
	case 0:
		switch (systemKey) {
		case AVK_5:
			if (robin.count >= robin.maxInven) {
				SetAlert(ALERT_INVENFULL);
			}
			else {
				PlayMusic(M_SELECT);
			}
			break;
		}
		break;
	}
}

void PlayKey(int obj)
{
	int i, j, k, temp = 0;
	OBJECT* pObj = &ao[obj];
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	int collectionIdx = GetCollectionIdx(it->type, it->detail, it->grade);

	int tempIdx;
	int type, detail, grade;
	const signed short* tPtr;
	int ret;
	int skillIdx;
	const long long* reward;
	const long long* boxReward;
	int boxStartIndex;
	int boxEndIndex;
	int speed;
	int cardSpanNum = 2;
	int cardSpan;
	float controlZoom = 1.0f;
	const signed short* scPtr;
	int width;
	int sameRouletteCnt = 1;//동일카드가 몇장 있는지
	int sameRouletteStartIdx;//동일카드가 스타트 되는 지점
	int sameRouletteEndIdx;//동일카드가 엔드가 되는 지점

	int crewIdx;
	int startX;
	int startY;
	int targetX;
	int targetY;
	int itemType;
	int itemDetail;
	int itemGrade;
	int itemCnt;
	int index;
	int distance;

	long long tempPrice;

	int who;

	//달성도 초기화 : 방구석 페인(한 방에서 아무것도 하지 않고 있는 시간)
	rpVar2.roomFrame = 0;

	switch (systemKey) {
	case AVK_1:
	case AVK_2:
	case AVK_3:
	case AVK_4:
	case AVK_5:
	case AVK_6:
	case AVK_7:
	case AVK_8:
	case AVK_9:
		key_released = false;
		break;
	}

	clearFrame = MC_knlCurrentTime();

	if (isTouchKey != TOUCH_DRAG) {
		pObj->pressedKey[2] = pObj->pressedKey[1];
		pObj->pressedKey[1] = pObj->pressedKey[0];
		pObj->pressedKey[0] = systemKey;
	}

	if (systemKey >= AVK_BATTLE_TARGET && systemKey < AVK_BATTLE_TARGET + MAXCREW) {
		//해줘야 될 일들

		//일단 타겟을 설정해 준다.
		battleTarget = systemKey - AVK_BATTLE_TARGET;

		//이후 방패가 있는지를 따져서 방패를 하나 소모시키면서 
		//현재는 서버의 데이터가 없으므로
		//랜덤하게 70%확률로 태클을 걸자

		if (Random(100) < 70)
			battleShield = true;
		else
			battleShield = false;

		battleShield = true;

		//그리고 이겼을 때 획득하는 gold를 결정하자
		battleGold = battleRewardGold[robin.stage];//이거 다 서버에서 받아와야 된다.

		//다음화면으로 넘겨주기 위해서 attackDelay를 제거해 준다.
		attackDelay--;
		if (sequenceDelay > 0)
			sequenceDelay--;
	}
	else if (systemKey >= AVK_RAID_TARGET && systemKey < AVK_RAID_TARGET + TOTALRAIDBOX) {
		//해줘야 될 일들

		//일단 타겟을 설정해 준다.
		raidTarget = systemKey - AVK_RAID_TARGET;

		//그리고 이겼을 때 획득하는 gold를 결정하자
		raidGold = raidBox[raidTarget].gold;//이거 다 서버에서 받아와야 된다.
		//절반값보다 크면
		if (raidBox[raidTarget].gold > enemyHouse.gold * GetBetHeart(ao[PLAYER].equip[EQUIP_WEAPON].detail, ao[PLAYER].equip[EQUIP_WEAPON].grade, bet) / 2)
			raidAttack = ROULETTE_RAID_PERFECT;
		else if (raidBox[raidTarget].gold == 0)
			raidAttack = ROULETTE_RAID_MISS;
		else
			raidAttack = ROULETTE_RAID_GOOD;

		sequenceFrame = 0;
		//다음화면으로 넘겨주기 위해서 attackDelay를 제거해 준다.
		attackDelay--;
		if (sequenceDelay > 0)
			sequenceDelay--;

	}
	else if (systemKey >= AVK_BOSSRAID_REWARDINFO && systemKey < AVK_BOSSRAID_REWARDINFO + BOSSRAIDSIZE) {
		boxReward = &goldQuestReward[(robin.gameEvent[GetEventMenuIdx(EVENTTYPE_BOSSRAID)].barStatus * BOSSRAIDSIZE + systemKey - AVK_BOSSRAID_REWARDINFO) * (BOX1MAXREWARDITEM * 5)];
		SetPopUp(POPUPTYPE_BOXREWARD, xOffset + bar[BAR_ENEMYHP].x + HPBARWIDTH + 48 * _2X - ((ITEMCARDSIZE_X + 4 * _2X) * 3) / 2, bar[BAR_ENEMYHP].y - 28 * _2X - 128 * _2X / 2, (REWARDCARDSIZE_X + 4 * _2X) * 3 + 16 * _2X, 108 * _2X,
			ITEM_BOX, goldQuestBox[robin.gameEvent[GetEventMenuIdx(EVENTTYPE_BOSSRAID)].barStatus * BOSSRAIDSIZE + systemKey - AVK_BOSSRAID_REWARDINFO], GRADE_NORMAL,
			*(boxReward), *(boxReward + 1), *(boxReward + 2), *(boxReward + 3), *(boxReward + 4),
			*(boxReward + 5), *(boxReward + 6), *(boxReward + 7), *(boxReward + 8), *(boxReward + 9),
			*(boxReward + 10), *(boxReward + 11), *(boxReward + 12), *(boxReward + 13), *(boxReward + 14));
	}
	//여기는 별 올려주는 곳
	else if (systemKey >= AVK_CREWSTARUPGRADE && systemKey < AVK_CREWSTARUPGRADE + MAXCREW) {
		int stageCrewIdx = robin.crewStage * MAXCREW + systemKey - AVK_CREWSTARUPGRADE;
		int upgradePrice;
		curStar = robin.crewStar[stageCrewIdx];
		curMaxStar = robin.crewMaxStar[stageCrewIdx];
		maxStar = CREWMAXUPGRADELV;
		//리페어
		if (curStar < curMaxStar)
			upgradePrice = crewStarUpgradeGold[stageCrewIdx * CREWMAXUPGRADELV + robin.crewStar[stageCrewIdx]] / CREWREPAIRPER;
		else
			upgradePrice = crewStarUpgradeGold[stageCrewIdx * CREWMAXUPGRADELV + robin.crewStar[stageCrewIdx]];

		robin.gold -= upgradePrice;
		AddBar(&bar[BAR_GOLD], -upgradePrice, BARFRAME);
		robin.crewStar[stageCrewIdx]++;
		ao[CREW + stageCrewIdx % MAXCREW].curStar++;
		if (robin.crewStar[stageCrewIdx] > robin.crewMaxStar[stageCrewIdx])
			robin.crewMaxStar[stageCrewIdx]++;
		ao[CREW + stageCrewIdx % MAXCREW].levelUpFrame = 1;
		stageUpgradeMotion[systemKey - AVK_CREWSTARUPGRADE] = 1;

		startX = xOffset + ao[CREW + stageCrewIdx % MAXCREW].x;
		startY = STATUSWIN_Y + (rh - 4) * TSIZE - (ao[CREW + stageCrewIdx % MAXCREW].y - OBJIMGGAP) - ry;
		targetX = DX / 2;
		targetY = DY / 2;
		targetX2 = bar[BAR_CROWN].x + ITEMICONSIZE * 1.5f / 2;
		targetY2 = bar[BAR_CROWN].y - ITEMICONSIZE * 1.5f / 2;
		robin.exps++;
		SetCurrencyMark_PopUp(startX, startY, targetX, targetY, targetX2, targetY2, 32 * _2X, 2 * _2X, 32 * _2X, 2 * _2X, FPS / 2, FPS / 2, ICON_CROWN, 30, false, CURRENCY_EXP, 1.0f, 8.0f, 0.8f, 8.0f, 1.5f, -0.6f);
		SaveGame();

	}
	//여기는 레벨 올려주는 곳
	else if (systemKey >= AVK_CREWUPGRADE && systemKey < AVK_CREWUPGRADE + MAXCREW) {
		int stageCrewIdx = robin.crewStage * MAXCREW + systemKey - AVK_CREWUPGRADE;
		robin.gold -= crewStarUpgradeGold[stageCrewIdx * CREWMAXUPGRADELV + robin.crewStar[stageCrewIdx]] / CREWUPGRADEPER;
		AddBar(&bar[BAR_GOLD], -crewStarUpgradeGold[stageCrewIdx * CREWMAXUPGRADELV + robin.crewStar[stageCrewIdx]] / CREWUPGRADEPER, BARFRAME);
		ao[CREW + stageCrewIdx % MAXCREW].lv++;
		ao[CREW + stageCrewIdx % MAXCREW].levelUpFrame = 1;
		stageUpgradeMotion[systemKey - AVK_CREWUPGRADE] = 1;
	}
	else if (systemKey >= AVK_HIT_ATTACK && systemKey < AVK_HIT_ATTACK + MAXCREW) {
		pObj->target = ENEMY + systemKey - AVK_HIT_ATTACK;
		RouletteAttackStart();
	}
	else if (systemKey >= AVK_COLLECTIONS_REWARD && systemKey < AVK_COLLECTIONS_REWARD + TOTAL_COLLECTIONS) {
		collectionIdx = systemKey - AVK_COLLECTIONS_REWARD;
		startX = xOffset + DX / 2 - ITEMICONSIZE / 2;
		startY = DY / 2 - 140 * _2X - 32 * _2X;
		itemType = collectionReward[collectionIdx * 4 + 0];
		itemDetail = collectionReward[collectionIdx * 4 + 1];
		itemGrade = collectionReward[collectionIdx * 4 + 2];
		itemCnt = collectionReward[collectionIdx * 4 + 3];

		switch (itemType) {
		case ITEM_GOLD:

			AddBar(&bar[BAR_GOLD], collectionReward[(systemKey - AVK_COLLECTIONS_REWARD) * 4 + 3], BARFRAME);
			break;
		case ITEM_HEART:
			break;
		case ITEM_MEDAL:
			break;
		case ITEM_STAR:
			break;
		case ITEM_HAMMER:
			break;
		}
		GetItem(itemType, 1, itemDetail, itemGrade, itemCnt, false);

		winAniFrame = 1;
	}
	else if (systemKey >= AVK_EQUIPALL && systemKey < AVK_EQUIPALL + TOTAL_COLLECTIONS) {
		for (i = 0; i < COLLECTIONSITEMCNT; i++) {
			EquipItem(&ao[PLAYER], &robin.inven[GetInvenIdx(collectionData[menuCur * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 0], collectionData[menuCur * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 1], collectionData[menuCur * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 2])]);
		}
		winAniFrame = 1;
		initControlerFrame = 1;
	}
	else if (systemKey >= AVK_ITEMDETAIL && systemKey < AVK_ITEMDETAIL + OPENEDMAXITEMCNT) {
		menuItem = systemKey - AVK_ITEMDETAIL;
		menuDepth = 1;
		ao[NPC].frame = 0;
	}
	else if (systemKey >= AVK_EQUIPDETAIL && systemKey < AVK_EQUIPDETAIL + TOTALEQUIP) {
		menuItem = systemKey - AVK_EQUIPDETAIL;
		SetPopUp(POPUPTYPE_ITEMDETAIL, DX / 2, DY / 2 + ITEMDETAILWINDOWSIZE_Y / 2, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, ao[PLAYER].equip[menuItem].type, ao[PLAYER].equip[menuItem].detail, ao[PLAYER].equip[menuItem].grade,
			false, false, false, false, false,
			false, false, false, false, false,
			false, false, false, false, false);
	}
	else if (systemKey >= AVK_COLLECTIONS_ITEMDETAIL && systemKey < AVK_COLLECTIONS_ITEMDETAIL + COLLECTIONSITEMCNT) {
		menuItem = systemKey - AVK_COLLECTIONS_ITEMDETAIL;
		menuDepth = 2;
		ao[NPC].frame = 0;
	}
	else if (systemKey >= AVK_INVENTORY_SELECTITEM && systemKey < AVK_INVENTORY_SELECTITEM + itemStartCnt[ITEM_GEM]) {
		EquipItem(&ao[PLAYER], &robin.inven[systemKey - AVK_INVENTORY_SELECTITEM]);
		winAniFrame = 1;
	}
	else if (systemKey >= AVK_CREW_DETAIL && systemKey < AVK_CREW_DETAIL + TOTAL_CREW) {
		menuDepth = 1;
		menuCur = systemKey - AVK_CREW_DETAIL;
		memset(&ao[NPC], 0, sizeof(OBJECT));
		ao[NPC].type = crewData[menuCur * CREWDATASIZE + 0];
		SetEnemy(&ao[NPC]);

		ao[NPC].cmf = enemyData[crewData[menuCur * CREWDATASIZE + 0] * ENEMYDATASIZE];
		ao[NPC].moveHandler = CREWMOVE;
		ao[NPC].active = true;
		ao[NPC].x = DX / 2;
		ao[NPC].y = DY / 2;

	}
	else if (systemKey >= AVK_CREW_REWARD && systemKey < AVK_CREW_REWARD + TOTAL_CREW) {
		//여기서 재화를 획득시켜준다.
		crewIdx = GetCrewIdxFromType(ao[ENEMY + systemKey - AVK_CREW_REWARD].type);
		itemType = crewReward[crewIdx * CREWREWARDDATASIZE + 0];
		itemDetail = crewReward[crewIdx * CREWREWARDDATASIZE + 1];
		itemGrade = crewReward[crewIdx * CREWREWARDDATASIZE + 2];
		itemCnt = crewReward[crewIdx * CREWREWARDDATASIZE + 3];
		startX = xOffset + ao[ENEMY + systemKey - AVK_CREW_REWARD].x;
		startY = STATUSWIN_Y + (rh - 4) * TSIZE - ao[ENEMY + systemKey - AVK_CREW_REWARD].y - ry - Min(ao[ENEMY + systemKey - AVK_CREW_REWARD].cpy, -48 * _2X);
		targetX;
		targetY;

		if (itemType == ITEM_BOX) {
			rewardMark[0].type = itemType;
			rewardMark[0].detail = itemDetail;
			rewardMark[0].grade = itemGrade;

			GotoGacha();
		}
		else {
			GetItem(itemType, 1, itemDetail, itemGrade, itemCnt, false);

			switch (itemType) {
			case ITEM_GOLD:
				targetX = bar[BAR_GOLD].x + 6 * _2X + ITEMICONSIZE / 2;
				targetY = bar[BAR_GOLD].y - 6 * _2X - ITEMICONSIZE / 2;
				AddBar(&bar[BAR_GOLD], itemCnt, BARFRAME);
				SetCurrencyMarkArr(startX, startY, targetX, targetY, targetX, targetY, 16 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, CURRENCYWAITINGFRAMEMAX, CURRENCYWAITINGFRAMEMAX, ICON_GOLD, 30, itemCnt, CURRENCY_GOLD, 3.0f, 2.0f, -0.1f, 2.0f, 1.0f, -0.1f, 10, BAR_GOLD);
				break;
			case ITEM_HEART:
				targetX = xOffset + bar[BAR_HEART].x + 16 * _2X + 128 * _2X / 2 - (GetBigNumDx(bar[BAR_HEART].count - GetInitHeart(), true, NUM_FONT_NORMAL, false, true, HEARTBARWIDTH, 1.0f, false) + 20 * _2X + 4 * _2X) / 2 + ITEMICONSIZE / 2;
				targetY = bar[BAR_HEART].y - TSIZE * 1 / 2;
				AddBar(&bar[BAR_BOX], itemCnt, BARFRAME);
				SetCurrencyMarkArr(startX, startY, targetX, targetY, false, false, 16 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, false, false, false, false, ICON_HEART, 30, itemCnt, CURRENCY_HEART, 3.0f, 1.0f, -0.2f / MOTIONDIV, false, false, false, 10, BAR_HEART);
				break;
			case ITEM_MEDAL:
				targetX = xOffset + 4 * _2X + 164 * _2X + ITEMICONSIZE;
				targetY = (GNBHEIGHT == GNB_INIT_HEIGHT ? DY : DY - NORCH_HEIGHT) - 6 * _2X - ITEMICONSIZE / 2;

				AddBar(&bar[BAR_MEDAL], itemCnt, BARFRAME);
				SetCurrencyMarkArr(startX, startY, targetX, targetY, false, false, 16 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, false, false, CURRENCYWAITINGFRAMEMAX, 0, ICON_MEDAL, 30, itemCnt, CURRENCY_MEDAL, 3.0f, 1.0f, -0.2f / MOTIONDIV, false, false, false, 10, BAR_MEDAL);
				break;
			case ITEM_STAR:
				targetX = bar[BAR_CROWN].x + 6 * _2X + ITEMICONSIZE / 2;
				targetY = (GNBHEIGHT == GNB_INIT_HEIGHT ? DY : DY - NORCH_HEIGHT) - 6 * _2X - ITEMICONSIZE / 2;

				AddBar(&bar[BAR_CROWN], itemCnt, BARFRAME);
				SetCurrencyMarkArr(startX, startY, targetX, targetY, false, false, 16 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, false, false, CURRENCYWAITINGFRAMEMAX, 0, ICON_STAR, 30, itemCnt, CURRENCY_STAR, 3.0f, 1.0f, -0.2f / MOTIONDIV, false, false, false, 10, BAR_CROWN);
				break;
			case ITEM_HAMMER:
				targetX = bar[BAR_HAMMER].x + 6 * _2X + ITEMICONSIZE / 2;
				targetY = (GNBHEIGHT == GNB_INIT_HEIGHT ? DY : DY - NORCH_HEIGHT) - 6 * _2X - ITEMICONSIZE / 2;

				AddBar(&bar[BAR_HAMMER], itemCnt, BARFRAME);
				SetCurrencyMarkArr(startX, startY, targetX, targetY, false, false, 2 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, false, false, CURRENCYWAITINGFRAMEMAX, 0, ICON_HAMMER, 30, itemCnt, CURRENCY_HAMMER, 3.0f, 1.0f, -0.2f / MOTIONDIV, false, false, false, 10, BAR_HAMMER);
				break;
			case ITEM_BOX:

				break;
			case ITEM_CREW:

				break;
			case ITEM_SWORD:
			case ITEM_HELM:
			case ITEM_ARMOR:
			case ITEM_GUNTLET:
			case ITEM_KILT:
			case ITEM_GREAVES:
			case ITEM_NECK:
			case ITEM_RING:
				targetX = xOffset + 2 * _2X + 164 * _2X;
				targetY = 1 * ITEMICONSIZE + (GNBHEIGHT == GNB_INIT_HEIGHT ? DY : DY - NORCH_HEIGHT);

				//rewardMark[]
				break;
			}
		}

	}
	else if (systemKey >= AVK_COLLECTIONS_DETAIL && systemKey < AVK_COLLECTIONS_DETAIL + TOTAL_COLLECTIONS) {

		//curMenuBack = curMenu;
		//curMenu = MENU_COLLECTIONS;
		menuDepth = 1;
		menuCur = systemKey - AVK_COLLECTIONS_DETAIL;

	}
	else if (systemKey >= AVK_COLLECTIONS_EQUIP && systemKey < AVK_COLLECTIONS_EQUIP + TOTALEQUIP) {
		menuCur = systemKey - AVK_COLLECTIONS_EQUIP;
	}
	else {
		//기본 움직임
		switch (systemKey) {
		case AVK_4:
		case AVK_6:
			if (pObj->debuf[STUN] || pObj->debuf[KNOCKBACK])
				break;

			if (darkStone) {
				pObj->dirF = (systemKey == AVK_4) ? LEFT : RIGHT;
				break;
			}

			if (CanRunPlayer(obj))
				pObj->playerRun = true;
			break;
		case AVK_8:
			if (pObj->equip[EQUIP_WEAPON].type != EMPTY && pObj->equip[EQUIP_WEAPON].type % 3 == pObj->type && pObj->equip[EQUIP_WEAPON].broken == 0 && pObj->canDown == true && pObj->magnet == false && darkStone == false && !pObj->attack && !pObj->flamer && boomerangAway[obj] == false && pObj->inTile == 0) {
				GetTile(&ao[obj]);

				if (GetObjHeight(&ao[obj]) > 64 * _2X) {
					GetMotionPtr(pObj);

					pObj->currentSkill = -1;
					pObj->mx = false;
					pObj->dx = 0;
					pObj->status = FALL;
					pObj->dirY = DOWN;
					pObj->jumpFrame = 0;
					pObj->attack = ATTACK_DOWN;
					pObj->attackFrame = skillStartFrame[ATTACK_DOWN];
					HitCountCheck(pObj);
				}
			}
			break;
		case AVK_5:
			if (!pObj->attack && waveStatus == WAVESTATUS_PLAY) {
				if (!pObj->flamer) {
					if (pObj->equipImg[EQUIP_WEAPON] == 0 || pObj->equip[EQUIP_WEAPON].broken)
						break;

					GetMotionPtr(pObj);

					pObj->continueAttack = false;

					if (pObj->playerRun == true) {
						pObj->attack = ATTACK_DASH;
						pObj->attackFrame = skillStartFrame[ATTACK_DASH];
						HitCountCheck(pObj);
					}
					else if (boomerangAway[obj] == false) {
						if (pObj->status == WALK) {
							pObj->attack = ATTACK_NORMAL;
							pObj->attackFrame = skillStartFrame[ATTACK_NORMAL];
						}
						else {
							pObj->attack = ATTACK_AIR;
							pObj->attackFrame = skillStartFrame[ATTACK_AIR];
						}
						HitCountCheck(pObj);
					}

					pObj->currentSkill = -1;

					if (pObj->type == DIANA)
						PlayRelease(pObj);
				}
			}
			break;
		case AVK_LEFT:
			switch (menuResult) {
			case 1://공용보물상자
				menuPage2 = (menuPage2 + ((rewardItemCnt + INVEN_TCNT - 1) / INVEN_TCNT - 1)) % ((rewardItemCnt + INVEN_TCNT - 1) / INVEN_TCNT);
				menuItem2 = menuPage2 * INVEN_TCNT;

				PlayMusic(M_BUTTON);
				break;
			case 2://랭킹리스트
				break;
			}
			break;
		case AVK_RIGHT:
			switch (menuResult) {
			case 1://공용보물상자
				menuPage2 = ++menuPage2 % ((rewardItemCnt + INVEN_TCNT - 1) / INVEN_TCNT);
				menuItem2 = menuPage2 * INVEN_TCNT;

				PlayMusic(M_BUTTON);
				break;
			case 2://랭킹리스트
				break;
			}
			break;

			//shop
		case AVK_SOFT1:
			break;
		case AVK_RESURRECTION:
			robin.coin -= (arenaDeadCount + 1) * 10;
			ResurrectionEffect(&ao[raidPlayer]);
			arenaDeadCount++;
			PlayMusic(M_POWERUP);
			break;
		case AVK_AUTOOFF:
			autoPlay = false;
			//autoFrame = -1;

			break;

		case AVK_AUTO:
			int index;
			//현재 조이스틱을 누른 상태인지, 아니면 조이스틱을 누르고 룰렛이 돌아가는 상황에 따라 다르다.
			autoPlay = true;
			if (attackSequence == ATTACKSEQUENCE_SLOT) {

			}
			else {
				BoxOpen();
				joyStickAni++;
				joyStickDir = RIGHT;
			}
			break;
		case AVK_OPTION_VOICE:
			if (option.voice == true) {
				option.voice = false;
			}
			else {
				option.voice = true;
			}
			SaveOption();
			break;
		case AVK_OPTION_BGM:
			option.bgm = (option.bgm + 1) % 2;
			SaveOption();
			if (option.bgm == true)
				TimerMusic();
			else {
				for (i = 0; i < TOTALMUSIC; i++) {
					AudioEngine::stop(audioID[i]);
				}
			}
			break;
		case AVK_OPTION_SE:
			option.se = (option.se + 1) % 2;
			SaveOption();
			if (option.se == true)
				PlayMusic(M_COIN);
			break;
		case AVK_OPTION_EFFECT:
			SaveOption();
			break;
		case AVK_OPTION_PUSHALARM:
			option.pushAlarm = ++option.pushAlarm % 2;
			SaveOption();
			break;
		case AVK_OPTION_ACCOUNT:
			menuDepth = 2;
			menuCur = 1;

			PlayMusic(M_SELECT);
			break;
		case AVK_OPTION_POLICY:
			menuDepth = 2;
			menuCur = 2;

			PlayMusic(M_SELECT);
			break;
		case AVK_CLR:
			switch (drawHandle) {
			case MD_PLAY:
				switch (curMenu) {
				case MENU_PLAY:
					break;
				default:
					if (menuDepth > 0)
						menuDepth--;
					else if (curMenu != MENU_LIST && curMenuBack != MENU_PLAY) {
						switch (curMenuBack) {
						case MENU_GAMEEVENT:
							curMenu = curMenuBack;
							break;
						default:
							curMenu = MENU_LIST;
							xOffset = -GAMEMENUWIN_X;
							break;
						}
					}
					else if (curMenu == MENU_COLLECTIONS && curMenuBack == MENU_PLAY) {
						curMenu = curMenuBack;
					}
					else {
						curMenu = MENU_PLAY;
						memset(&ao[NPC], 0, sizeof(OBJECT));
					}
					break;
				}
				break;
				//밑에는 결과에 대해 AVK_CLR를 사용하면  
			case MD_BATTLE:
				sequenceDelay = ATTACKDELAY_BATTLEREWARD_COIN_GET + 2;
				break;
			case MD_RAID:
				sequenceDelay = ATTACKDELAY_RAIDREWARD_WARP + 2;
				break;
			case MD_BOSSRAID:
				sequenceDelay = ATTACKDELAY_BOSSREWARD_WARP + 2;
				break;
			}
			break;
		case AVK_EQUIPSLOT + EQUIP_WEAPON:
		case AVK_EQUIPSLOT + EQUIP_HELM:
		case AVK_EQUIPSLOT + EQUIP_ARMOR:
		case AVK_EQUIPSLOT + EQUIP_PANTS:
		case AVK_EQUIPSLOT + EQUIP_GLOVE:
		case AVK_EQUIPSLOT + EQUIP_BOOTS:
		case AVK_EQUIPSLOT + EQUIP_NECK:
		case AVK_EQUIPSLOT + EQUIP_RING:
			menuItem = ITEMPTR_EQUIP + menuCur * TOTALEQUIP + (systemKey - AVK_EQUIPSLOT) + 1;
			PlayMusic(M_BUTTON);
			break;
		case AVK_HERO:
			menuItem = null;
			PlayMusic(M_BUTTON);
			break;
		case AVK_GAMEMENU_OUTOFGAME:
			SetAlert(ALERT_EXIT);
			break;
		case AVK_TABMENU1:
			tabMenuFrame[menuCur] = -1;
			menuCur = 0;
			tabMenuFrame[menuCur] = 1;
			scY[MENU_COLLECTIONS] = 0;
			scRecoveryFrameY = 0;
			scAccelY = 0;
			break;
		case AVK_TABMENU2:
			tabMenuFrame[menuCur] = -1;
			menuCur = 1;
			tabMenuFrame[menuCur] = 1;
			scY[MENU_COLLECTIONS] = 0;
			scRecoveryFrameY = 0;
			scAccelY = 0;
			break;
		case AVK_TABMENU3:
			tabMenuFrame[menuCur] = -1;
			menuCur = 2;
			tabMenuFrame[menuCur] = 1;
			scY[MENU_COLLECTIONS] = 0;
			scRecoveryFrameY = 0;
			scAccelY = 0;
			break;
		case AVK_TABMENU4:
			tabMenuFrame[menuCur] = -1;
			menuCur = 3;
			tabMenuFrame[menuCur] = 1;
			scY[MENU_COLLECTIONS] = 0;
			scRecoveryFrameY = 0;
			scAccelY = 0;
			break;
		case AVK_TABMENUX_1:
			menuX = 0;
			break;
		case AVK_TABMENUX_2:
			menuX = 1;
			break;
		case AVK_TABMENUX_3:
			menuX = 2;
			break;
			//보스레이드에서 빠져가는 경우
		case AVK_BOSSRAIDOUT:
			attackSequence = ATTACKSEQUENCE_ATTACKRESULT;
			bossRaidMode = false;
			break;
		case AVK_PLAY:

			curMenu = MENU_PLAY;
			menuX = 0;
			break;
		case AVK_COLLECTIONS:
			curMenuBack = curMenu;
			curMenu = MENU_COLLECTIONS;
			menuDepth = 0;
			menuX = 0;
			menuCur = 0;
			for (i = 0; i < TOTAL_COLLECTIONMENU; i++)
				tabMenuFrame[i] = -1;
			tabMenuFrame[menuCur] = 1;
			SetPopUp(POPUPTYPE_COLLECTIONS, DX / 2, GetScrollDy(curMenu) - DY / 3 - GNBHEIGHT, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_SHOP:
			curMenuBack = curMenu;
			curMenu = MENU_SHOP;
			menuDepth = 0;
			menuX = 0;
			popUpFrame = 1;
			SetPopUp(POPUPTYPE_SHOPINFO, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_STARSHOP:
			curMenuBack = curMenu;
			curMenu = MENU_STARSHOP;
			menuDepth = 0;
			menuX = 0;
			popUpFrame = 1;
			SetPopUp(POPUPTYPE_SHOPINFO, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_NEWS:
			curMenuBack = curMenu;
			curMenu = MENU_NEWS;
			menuDepth = 0;
			menuX = 0;
			popUpFrame = 1;
			SetPopUp(POPUPTYPE_NEWS, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_GIFTS:
			curMenuBack = curMenu;
			curMenu = MENU_GIFTS;
			menuDepth = 0;
			menuX = 0;
			popUpFrame = 1;
			SetPopUp(POPUPTYPE_GIFT, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_LEADERBOARD:
			curMenuBack = curMenu;
			curMenu = MENU_LEADERBOARD;
			menuDepth = 0;
			menuX = 0;
			popUpFrame = 1;
			SetPopUp(POPUPTYPE_READERBOARD, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_FRIENDS:
			curMenuBack = curMenu;
			curMenu = MENU_FRIENDS;
			menuDepth = 0;
			menuX = 0;
			popUpFrame = 1;
			SetPopUp(POPUPTYPE_FRIENDS, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_INVITEFRIENDS:
			curMenuBack = curMenu;
			curMenu = MENU_INVITEFREINDS;
			menuDepth = 0;
			menuX = 0;
			popUpFrame = 1;
			SetPopUp(POPUPTYPE_FRIENDS, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_CALENDAR:
			curMenuBack = curMenu;
			curMenu = MENU_CALENDAR;
			menuDepth = 0;
			menuX = 0;
			popUpFrame = 1;
			SetPopUp(POPUPTYPE_CALENDAR, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_SETTING:
			SetPopUp(POPUPTYPE_OPTION, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_LIST:
			if (autoPlay == true) {
				autoPlay = false;
			}
			else {
				if (menuPressPossible() == true) {
					curMenu = MENU_LIST;
					menuX = 0;
					menuDepth = 0;
				}
			}
			break;
		case AVK_EVENT_QUEST:
			if (autoPlay == true) {
				autoPlay = false;
			}
			else {
				SetPopUp(POPUPTYPE_QUESTINFO, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
					false, false, false, false, false,
					false, false, false, false, false,
					false, false, false, false, false);
			}
			break;
		case AVK_EVENT_PVP:
			if (autoPlay == true) {
				autoPlay = false;
			}
			else {
				SetPopUp(POPUPTYPE_PVPQUESTINFO, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
					false, false, false, false, false,
					false, false, false, false, false,
					false, false, false, false, false);
			}
			break;
		case AVK_EVENT_SHOP:
			if (autoPlay == true) {
				autoPlay = false;
			}
			else {
				SetPopUp(POPUPTYPE_SHOPINFO, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
					false, false, false, false, false,
					false, false, false, false, false,
					false, false, false, false, false);
			}
			break;
		case AVK_EVENT_DEBTDISCOUNT:
			if (autoPlay == true) {
				autoPlay = false;
			}
			else {
				SetPopUp(POPUPTYPE_DEPTDISCOUNT, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
					false, false, false, false, false,
					false, false, false, false, false,
					false, false, false, false, false);

			}
			break;
		case AVK_EVENT_DOUBLE:
			if (autoPlay == true) {
				autoPlay = false;
			}
			else {
				SetPopUp(POPUPTYPE_DOUBLE, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
					false, false, false, false, false,
					false, false, false, false, false,
					false, false, false, false, false);

			}
			break;
		case AVK_EVENT_BOSSRAID:
			if (autoPlay == true) {
				autoPlay = false;
			}
			else {

				SetPopUp(POPUPTYPE_BOSSRAID, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
					false, false, false, false, false,
					false, false, false, false, false,
					false, false, false, false, false);
			}
			break;
		case AVK_ATTACK_REWARD:
			if (sequenceDelay > 0)
				sequenceDelay = 0;
			else if (sequenceDelay == 0) {
				ClearRoom();
			}
			break;
		case AVK_HIT_REWARD:
			if (sequenceDelay > 1)
				sequenceDelay = 1;
			else if (sequenceDelay == 1) {

			}
			break;
		case AVK_RAID_REWARD:
			if (sequenceDelay > 1)
				sequenceDelay = 1;
			else if (sequenceDelay == 1) {

			}
			break;
		case AVK_BOXINFO:
			SetPopUp(POPUPTYPE_BOXINFO, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, ITEM_BOX, bet, GRADE_NORMAL,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_GAMEMENU:
			if (autoPlay == true) {
				autoPlay = false;
			}
			else {
				if (menuPressPossible() == true) {
					curMenu = MENU_LIST;
					xOffset = -8 * _2X;
					PlayMusic(M_SELECT);
				}
			}
			break;
		case AVK_EQUIP_ENCHANT_SELECT:
			menuX = 0;//강화메뉴
			break;
		case AVK_EQUIP_HAMMER_SELECT:
			menuX = 1;//진화메뉴
			break;
			//새로운 아이템 장착
		case AVK_EQUIP_NEWITEM:
			who = robin.newItem.type % 3;
			memset(&popUp[popUpCnt - 1], 0, sizeof(POPUP));
			popUpCnt--;
			rewardMark[0].targetX2 = bar[BAR_INVENTORY + who].x + (float)(48 * _2X + 12 * _2X + equipSlotPos[itemEquipSlot[robin.newItem.type] * 4 + 2] + REWARDCARDSIZE_X / 2) * bar[BAR_INVENTORY].zoom;
			rewardMark[0].targetY2 = bar[BAR_INVENTORY + who].y + (float)(equipSlotPos[itemEquipSlot[robin.newItem.type] * 4 + 3] - 8 * _2X - REWARDCARDSIZE_Y / 2) * bar[BAR_INVENTORY].zoom;
			rewardMark[0].speed2 = 32 * _2X;
			rewardMark[0].speedIncrement2 = 1 * _2X;
			rewardMark[0].frame2 = 0;
			rewardMark[0].waitingFrame2 = FPS;
			rewardMark[0].zoom2 = rewardMark[0].zoom;
			rewardMark[0].zoomEnd2 = 0.7f;
			rewardMark[0].zoomIncrement2 = -0.2f / MOTIONDIV;

			EquipNewItem(&ao[who], &robin.newItem);

			sequenceDelay = ATTACKDELAY_EQUIP_CHANGE + 1;
			break;
		case AVK_DISASSEMBLE_NEWITEM:
			//돈과 경험치를 증가시켜준다.
			sequenceDelay = ATTACKDELAY_EQUIP_SETTING;
			memset(&popUp[popUpCnt - 1], 0, sizeof(POPUP));
			popUpCnt--;
			bar[BAR_QUEST].front = false;
			bar[BAR_COMBATPOWER].front = false;
			break;
		case AVK_ATTACK:
			RouletteAttackStart();

			touchDisable = true;
			break;
		case AVK_HEROCHECK_DIANA:
			if (robin.heroesSetting[DIANA] == true)
				robin.heroesSetting[DIANA] = false;
			else {
				robin.heroesSetting[DIANA] = true;

				if (robin.gold < GetStageAdmissionFee()) {
					robin.heroesSetting[DIANA] = false;

				}
			}
			break;
		case AVK_HEROCHECK_MAXX:
			if (robin.heroesSetting[MAXX] == true)
				robin.heroesSetting[MAXX] = false;
			else {
				robin.heroesSetting[MAXX] = true;

				if (robin.gold < GetStageAdmissionFee()) {
					robin.heroesSetting[MAXX] = false;

				}
			}
			break;
		case AVK_CREWCHECK_1:
			if (robin.crewSetting[0] == true)
				robin.crewSetting[0] = false;
			//골드를 
			else {
				robin.crewSetting[0] = true;

				if (robin.gold < GetStageAdmissionFee()) {
					robin.crewSetting[0] = false;
					//AddLog
				}
			}
			break;
		case AVK_CREWCHECK_2:
			if (robin.crewSetting[1] == true)
				robin.crewSetting[1] = false;
			//골드를 
			else {
				robin.crewSetting[1] = true;

				if (robin.gold < GetStageAdmissionFee()) {
					robin.crewSetting[1] = false;
					//AddLog
				}
			}
			break;
		case AVK_CREWCHECK_3:
			if (robin.crewSetting[2] == true)
				robin.crewSetting[2] = false;
			//골드를 
			else {
				robin.crewSetting[2] = true;

				if (robin.gold < GetStageAdmissionFee()) {
					robin.crewSetting[2] = false;
					//AddLog
				}
			}
			break;

		case AVK_UPGRADE:
		case AVK_HAMMER:
			menuDepth = 4;
			menuFrame = 0;
			PlayMusic(M_SELECT);
			break;
		case AVK_SKILLUPGRADE:
			robin.gold -= skillUpgradeGold[menuCur * MAXSKILLLV + ao[PLAYER].skillLv[curSkill]] * GetBetHeart(collectionData[menuCur * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + 0 * COLLECTIONSDATASIZE + 1], collectionData[menuCur * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + 0 * COLLECTIONSDATASIZE + 2], bet);
			winUpgradeFrame = 1;
			break;
		case AVK_GETREWARDSTART:
			sequenceDelay = ATTACKDELAY_REWARD_TABTOCOLLECT + 1;
			break;
			//가챠에서 써야 될것 같은데? GachaKey에서 PlayKey를 처리해 주니까 여기서 하면 됨.
		case AVK_NEXTREWARD:
			break;
		case AVK_GOTOPLAY:

			break;
		case AVK_GOTOGACHA:
			GotoGacha();
			break;
		case AVK_GOTONEWCARD:
			GotoNewCard();
			if (sequenceDelay > 0)
				sequenceDelay--;

			break;
		case AVK_GOTOHOUSE:
			SetPopUp(POPUPTYPE_ENEMYUSER, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_GOTOSHOP:
			SetPopUp(POPUPTYPE_SHOPINFO, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_DAILYQUEST:
			SetPopUp(POPUPTYPE_DAILYQUEST, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_OUTOFNEWCARD:
			OutOfNewCard();
			break;
		case AVK_OUTOFBATTLERESLUT:
			sequenceDelay = ATTACKDELAY_RAID_REWARD_VALUEUP + 1;
			bar[BAR_GOLD].front = true;
			break;
		case AVK_OUTOFRAIDRESULT:
			sequenceDelay = ATTACKDELAY_RAIDREWARD_WARP + 1;
			break;
		case AVK_GOTOBOSSRAID:
			if ((popUp[popUpCnt - 1].type == POPUPTYPE_QUESTINFO || popUp[popUpCnt - 1].type == POPUPTYPE_PVPQUESTINFO)) {
				if (popUp[popUpCnt - 1].type == POPUPTYPE_QUESTINFO) {
				}
				else if (popUp[popUpCnt - 1].type == POPUPTYPE_PVPQUESTINFO) {
				}
			}
			memset(&popUp[popUpCnt - 1], 0, sizeof(POPUP));
			popUpCnt--;

			//골드이벤트 전투로 이동
			attackSequence = ATTACKSEQUENCE_BOSSRAID;
			sequenceDelay = CURTAINFRAME / CURTAINSPEED + 1;

			bar[BAR_BOX].front = false;
			turn = PLAYER;
			break;
		case AVK_GOTOBATTLE:
			battleStartFrame = BATTLESTARTFRAME;
			touchDisable = true;
			//GotoBattle(); 
			break;
		case AVK_NEWGAME:
			NewGame();

			PlayMusic(M_POWERUP);

			GotoPlay();

			robin.heart = GetInitHeart();

			arenaStatus = STATUS_PLAY;

			AddBar(&bar[BAR_COMBATPOWER], GetCombatPower(&ao[PLAYER]) - (bar[BAR_COMBATPOWER].count + bar[BAR_COMBATPOWER].add), BARFRAME);
			effect.color2 = false;

			waveStatus = WAVESTATUS_READY;
			//TEST
			//SetTestHotKey();
			//TEST
			bar[BAR_INVENTORY + 1].active = false;
			bar[BAR_INVENTORY + 2].active = false;
			bar[BAR_SKILL + 1].active = false;
			bar[BAR_SKILL + 2].active = false;

			robin.gold = 1000000;
			AddBar(&bar[BAR_GOLD], robin.gold, BARFRAME);

			SaveGame();
			for (i = 0; i < robin.eventCnt; i++)
				InitEventPos(&robin.gameEvent[i], GetEventMenuPosX(robin.gameEvent[i].type, EVENT_OPEN), GetEventMenuPosY(robin.gameEvent[i].type, EVENT_OPEN), GetEventMenuPosX(robin.gameEvent[i].type, EVENT_DOING), GetEventMenuPosY(robin.gameEvent[i].type, EVENT_DOING), GetEventMenuPosX(robin.gameEvent[i].type, EVENT_DOING), GetEventMenuPosY(robin.gameEvent[i].type, EVENT_DOING), 16 * _2X, -1 * _2X, 1 * _2X, 1 * _2X, FPS, FPS, false, false, false,
					1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f);

			//TEST
			//여기서 스킬세팅
			/*
			robin.charData[ROBIN].getSkillList[0] = SKILL_ROBIN8;//ROBIN_SKILL_BOOSTSLASH
			robin.charData[ROBIN].getSkillList[1] = SKILL_ROBIN6;//ROBIN_SKILL_AIRCRASH
			robin.charData[ROBIN].getSkillList[2] = SKILL_ROBIN9;//ROBIN_SKILL_HYPERCHARGE
			robin.charData[ROBIN].getSkillList[3] = SKILL_ROBIN10;//ROBIN_SKILL_SOULCRASH
			robin.charData[ROBIN].getSkillList[4] = SKILL_ROBIN7;//ROBIN_SKILL_STAB
			robin.charData[ROBIN].getSkillList[5] = SKILL_ROBIN11;//ROBIN_SKILL_ABSOLUTEPIERCE
			robin.charData[ROBIN].getSkillList[6] = SKILL_ROBIN12;//ROBIN_SKILL_KILLALL
			*/
			SaveGame();
			break;
		case AVK_MAXGAME:

			int stage;
			int questIcon;

			//TEST
			robin.stage = 1;
			//TEST
			stage = robin.stage;
			robin.maxStatusCnt = ++robin.maxStatusCnt % TOTAL_SWORD;
			i = robin.maxStatusCnt;
			NewGame();

			robin.stage = stage;
			robin.maxStatusCnt = i;


			option.gameControl = CONTROL_MANUAL;

			AddBar(&bar[BAR_GOLD], 10000000, BARFRAME);
			GetItem(ITEM_GOLD, false, false, false, 10000000, false);
			AddBar(&bar[BAR_BOX], 9999, BARFRAME);
			GetItem(ITEM_HEART, false, false, false, 9999, false);
			AddBar(&bar[BAR_HAMMER], 9999, BARFRAME);
			GetItem(ITEM_HAMMER, false, false, false, 9999, false);
			//robin.gold = 10000000;//코인
			//robin.medal = 100000;//PVP 아이템
			//robin.coin = 100000;//코인
			//robin.star = 100000;//스타(합성석)
			//robin.hammer = 100000;//합성석
			//robin.heart = 9999;

			detail = DEBUG_STAR;

			for (i = ROBIN; i < 1; i++) {
				for (j = 0; j < TOTALEQUIP; j++) {
					ao[i].equip[j].type = EMPTY;
					for (k = 0; k < 12; k++)
						ao[i].equip[i].option[j][0] = EMPTYINT;
					for (k = 0; k < 6; k++)
						ao[i].equip[i].socket[j] = EMPTYINT;
				}
			}

			MakeItem(&ao[ROBIN].equip[EQUIP_WEAPON], ITEM_SWORD, 1, GRADE_NORMAL, ITEM_SWORD_KING, 0);
			MakeItem(&ao[ROBIN].equip[EQUIP_HELM], ITEM_HELM, 1, GRADE_NORMAL, ITEM_HELM_TITANIUM, 0);
			MakeItem(&ao[ROBIN].equip[EQUIP_ARMOR], ITEM_ARMOR, 1, GRADE_NORMAL, ITEM_ARMOR_DRAGONSKIN, 0);
			MakeItem(&ao[ROBIN].equip[EQUIP_PANTS], ITEM_KILT, 1, GRADE_NORMAL, ITEM_KILT_EARTHQUAKE, 0);
			MakeItem(&ao[ROBIN].equip[EQUIP_GLOVE], ITEM_GUNTLET, 1, GRADE_NORMAL, ITEM_GUNTLET_HOLYHAND, 0);
			MakeItem(&ao[ROBIN].equip[EQUIP_BOOTS], ITEM_GREAVES, 1, GRADE_NORMAL, ITEM_GREAVES_LEGEND, 0);
			//MakeItem(&ao[ROBIN].equip[EQUIP_NECK], ITEM_NECK, 1, GRADE_NORMAL, robin.maxStatusCnt % TOTAL_NECK, 0);
			//MakeItem(&ao[ROBIN].equip[EQUIP_RING], ITEM_RING, 1, GRADE_NORMAL, robin.maxStatusCnt % TOTAL_RING, 0);

			RefreshStat(&ao[ROBIN]);

			MakeItem(&ao[DIANA].equip[EQUIP_WEAPON], ITEM_GUN, 1, GRADE_NORMAL, ITEM_GUN_INFERNO, 0);
			MakeItem(&ao[DIANA].equip[EQUIP_HELM], ITEM_HAT, 1, GRADE_NORMAL, ITEM_HAT_DRAGONSKULL, 0);
			MakeItem(&ao[DIANA].equip[EQUIP_ARMOR], ITEM_VEST, 1, GRADE_NORMAL, ITEM_VEST_QUEEN, 0);
			MakeItem(&ao[DIANA].equip[EQUIP_PANTS], ITEM_SKIRT, 1, GRADE_NORMAL, ITEM_SKIRT_HERO, 0);
			MakeItem(&ao[DIANA].equip[EQUIP_GLOVE], ITEM_ARMLET, 1, GRADE_NORMAL, ITEM_ARMLET_HERO, 0);
			MakeItem(&ao[DIANA].equip[EQUIP_BOOTS], ITEM_SHOES, 1, GRADE_NORMAL, ITEM_SHOES_HEAVENS, 0);
			//MakeItem(&ao[DIANA].equip[EQUIP_NECK], ITEM_NECK, 1, GRADE_NORMAL, robin.maxStatusCnt % TOTAL_NECK, 0);
			//MakeItem(&ao[DIANA].equip[EQUIP_RING], ITEM_RING, 1, GRADE_NORMAL, robin.maxStatusCnt % TOTAL_RING, 0);

			RefreshStat(&ao[DIANA]);

			MakeItem(&ao[MAXX].equip[EQUIP_WEAPON], ITEM_BOOMERANG, 1, GRADE_NORMAL, ITEM_BOOMERANG_MEGATRIAL, 0);
			MakeItem(&ao[MAXX].equip[EQUIP_HELM], ITEM_CAP, 1, GRADE_NORMAL, ITEM_CAP_TROLLHEAD, 0);
			MakeItem(&ao[MAXX].equip[EQUIP_ARMOR], ITEM_COAT, 1, GRADE_NORMAL, ITEM_COAT_HYDRASCALE, 0);
			MakeItem(&ao[MAXX].equip[EQUIP_PANTS], ITEM_PANTS, 1, GRADE_NORMAL, ITEM_PANTS_SATANIC, 0);
			MakeItem(&ao[MAXX].equip[EQUIP_GLOVE], ITEM_GLOVE, 1, GRADE_NORMAL, ITEM_GLOVE_GLORY, 0);
			MakeItem(&ao[MAXX].equip[EQUIP_BOOTS], ITEM_BOOTS, 1, GRADE_NORMAL, ITEM_BOOTS_DESTINY, 0);
			//MakeItem(&ao[MAXX].equip[EQUIP_NECK], ITEM_NECK, 1, GRADE_NORMAL, robin.maxStatusCnt % TOTAL_NECK, 0);
			//MakeItem(&ao[MAXX].equip[EQUIP_RING], ITEM_RING, 1, GRADE_NORMAL, robin.maxStatusCnt % TOTAL_RING, 0);

			RefreshStat(&ao[MAXX]);
			//for (i = 0; i < COLLECTIONSITEMCNT; i++) {
			//	EquipItem(&ao[PLAYER], GetInvenIdx(collectionData[robin.maxStatusCnt * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 0], collectionData[robin.maxStatusCnt * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 1], collectionData[robin.maxStatusCnt * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 2]));
			//}

			//GetItem(ITEM_NECK, 0, robin.maxStatusCnt % TOTAL_NECK, false, 1, false);
			//EquipItem(&ao[PLAYER], robin.count);

			//GetItem(ITEM_RING, 0, robin.maxStatusCnt % TOTAL_RING, false, 1, false);
			//EquipItem(&ao[PLAYER], i);

			//TEST
			//TEST
			//여기서 스킬세팅
			ao[ROBIN].getSkillList[0] = robin.charData[ROBIN].getSkillList[0] = SKILL_ROBIN8;
			ao[ROBIN].getSkillList[1] = robin.charData[ROBIN].getSkillList[1] = SKILL_ROBIN6;
			ao[ROBIN].getSkillList[2] = robin.charData[ROBIN].getSkillList[2] = SKILL_ROBIN9;
			ao[ROBIN].getSkillList[3] = robin.charData[ROBIN].getSkillList[3] = SKILL_ROBIN10;
			ao[ROBIN].getSkillList[4] = robin.charData[ROBIN].getSkillList[4] = SKILL_ROBIN7;
			ao[ROBIN].getSkillList[5] = robin.charData[ROBIN].getSkillList[5] = SKILL_ROBIN11;
			ao[ROBIN].getSkillList[6] = robin.charData[ROBIN].getSkillList[6] = SKILL_ROBIN12;

			ao[DIANA].getSkillList[0] = robin.charData[DIANA].getSkillList[0] = SKILL_DIANA6;
			ao[DIANA].getSkillList[1] = robin.charData[DIANA].getSkillList[1] = SKILL_DIANA7;
			ao[DIANA].getSkillList[2] = robin.charData[DIANA].getSkillList[2] = SKILL_DIANA8;
			ao[DIANA].getSkillList[3] = robin.charData[DIANA].getSkillList[3] = SKILL_DIANA9;
			ao[DIANA].getSkillList[4] = robin.charData[DIANA].getSkillList[4] = SKILL_DIANA10;
			ao[DIANA].getSkillList[5] = robin.charData[DIANA].getSkillList[5] = SKILL_DIANA11;
			ao[DIANA].getSkillList[6] = robin.charData[DIANA].getSkillList[6] = SKILL_DIANA12;

			ao[MAXX].getSkillList[0] = robin.charData[MAXX].getSkillList[0] = SKILL_MAXX7;
			ao[MAXX].getSkillList[1] = robin.charData[MAXX].getSkillList[1] = SKILL_MAXX8;
			ao[MAXX].getSkillList[2] = robin.charData[MAXX].getSkillList[2] = SKILL_MAXX9;
			ao[MAXX].getSkillList[3] = robin.charData[MAXX].getSkillList[3] = SKILL_MAXX10;
			ao[MAXX].getSkillList[4] = robin.charData[MAXX].getSkillList[4] = SKILL_MAXX11;
			ao[MAXX].getSkillList[5] = robin.charData[MAXX].getSkillList[5] = SKILL_MAXX12;
			ao[MAXX].getSkillList[6] = robin.charData[MAXX].getSkillList[6] = SKILL_MAXX13;

			SetHotKey(&ao[PLAYER], HOTKEY_SKILL, SKILL_ROBIN12, 0);
			SetHotKey(&ao[DIANA], HOTKEY_SKILL, SKILL_DIANA12, 1);
			SetHotKey(&ao[MAXX], HOTKEY_SKILL, SKILL_MAXX13, 2);
			//TEST
			robin.count = 0;


			for (i = ROBIN; i < TOTALPLAYER; i++)
				memcpy(&ao[PLAYER + i], &ao[i], sizeof(OBJECT));

			loadedMap = -1;

			PlayMusic(M_POWERUP);

			SaveOption();

			option.gameControl = CONTROL_MANUAL;
			questIcon = GetItemIcon(questRequestItem[robin.quest * 3 + 0], questRequestItem[robin.quest * 3 + 1], questRequestItem[robin.quest * 3 + 2]);
			if (questInfo[robin.quest * QUESTINFODATASIZE + 1] == QUESTTYPE_RAID)
				questIcon = ICON_RAID;
			else if (questInfo[robin.quest * QUESTINFODATASIZE + 1] == QUESTTYPE_BATTLE)
				questIcon = ICON_BATTLE;
			//else
			//	questIcon = ICON_SUMMON + questInfo[robin.quest * QUESTINFODATASIZE + 0];
			//InitEventMenu(&robin.gameEvent[robin.eventCnt], EVENTTYPE_BOSSRAID, false, ICON_EVENT_BOSSRAID, 43200, TOUCH_FUNC_EVENT_BOSSRAID);

			robin.crewStage = 9;
			robin.crewStar[0] = 1;
			robin.crewStar[1] = 1;
			robin.crewStar[2] = 1;
			robin.crewStar[3] = 1;
			robin.crewStar[4] = 1;


			memset(&robin.getCrews, true, sizeof(robin.getCrews));

			robin.lv = 11;
			robin.exps = 1000;
			LevelUp(robin.exps);

			GotoPlay();

			SaveGame();

			//SetBox(&ao[ITEMBOX], bet);
			arenaStatus = STATUS_PLAY;

			AddBar(&bar[BAR_COMBATPOWER], GetCombatPower(&ao[PLAYER]) - (bar[BAR_COMBATPOWER].count + bar[BAR_COMBATPOWER].add), BARFRAME);
			effect.color2 = false;

			waveStatus = WAVESTATUS_READY;

			//SetHero();
			//SetCrew();
			break;
		case AVK_ENEMYATTACK:
			//if (ONLYATTACKMODE == true)
			//	ONLYATTACKMODE = false;
			//else
			//	ONLYATTACKMODE = true;
			ao[ENEMY].id = MC_knlCurrentTimeStamp() + 3600;
			break;

		case AVK_HOME_LEFT:
			if (menuX > 0) {
				menuX--;
				PlayMusic(M_SELECT);
			}
			break;
		case AVK_HOME_RIGHT:
			if (menuX < totalHouse - 1) {
				menuX++;
				PlayMusic(M_SELECT);
			}
			break;
		case AVK_OUTOFHOUSE:
			OutOfHouse();
			break;
		case AVK_STAGE_LEFT:
#ifdef GAMEDEBUG
			if (robin.room > 0)
				robin.room--;
			else if (robin.stage > 0) {
				robin.stage--;
				robin.room = 0;
			}

			stageInfoFrame = 1;
			SetRaidBox(false);
#else
			if (menuX > 0) {
				menuX--;
				stageInfoDepth = 0;
				stageInfoFrame = 0;
				PlayMusic(M_SELECT);
			}
#endif

			break;
		case AVK_STAGE_RIGHT:
#ifdef GAMEDEBUG
			//if (robin.room < TOTALROOM - 1)
			//	robin.room++;
			//else 
			if (robin.stage < TOTAL_STAGE - 1) {
				robin.stage++;
				robin.room = 0;
			}

			stageInfoFrame = 1;
			SetRaidBox(false);

#else
			if (menuX < TOTAL_STAGE - 1) {
				menuX++;
				stageInfoDepth = 0;
				stageInfoFrame = 0;
				PlayMusic(M_SELECT);
			}
#endif
			break;
		case AVK_STAGEINFO:
			//curMenuBack = curMenu;
			//curMenu = MENU_STAGEINFO;
			//stageInfoDepth = 0;
			//popUpFrame = 1;
			SetPopUp(POPUPTYPE_STAGE, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_NEWCOLLECTIONREWARDGET:
			newCollectionDepth = 1;
			newCollectionFrame = 0;
			break;
		case AVK_NEWCARDREWARDGET:
			newCardDepth = 1;
			newCardFrame = 0;
			break;
		case AVK_GETGACHACARD:
			curNewCollection = 0;
			//가챠에서 나온 카드들을 인벤토리에 넣어준다.
			for (i = 0; i < boxCardItemCnt[gachaIndex]; i++) {
				GetItem(boxCardItem[gachaIndex][i].type, boxCardItem[gachaIndex][i].lv, boxCardItem[gachaIndex][i].detail, boxCardItem[gachaIndex][i].grade, 1, false);
				SetStrongestEquip(boxCardItem[gachaIndex][i].type, boxCardItem[gachaIndex][i].detail, boxCardItem[gachaIndex][i].grade);
			}

			//만약 컬렉션이 완성되면 일단 GotoCollection
			if (CollectionCheck() != -1) {
				do {
					newCollectionIdx[curNewCollection] = CollectionCheck();
					curNewCollection++;
				} while (curNewCollection < TOTAL_COLLECTIONS);

				GotoNewCollection();
			}
			else {
				newItemCnt = 0;
				curNewItemIdx = 0;
				for (i = 0; i < gachaCardIdx; i++) {
					if (GetInvenIdx(boxCardItem[gachaIndex][i].type, boxCardItem[gachaIndex][i].detail, boxCardItem[gachaIndex][i].grade) == -1) {
						newItemType[newItemCnt] = boxCardItem[gachaIndex][i].type;
						newItemDetail[newItemCnt] = boxCardItem[gachaIndex][i].detail;
						newItemGrade[newItemCnt] = boxCardItem[gachaIndex][i].grade;
						newItemCnt++;
					}
				}

				//if (newItemCnt > 0)
				//	GotoNewCard();
			}

			curNewCollection = 0;
			gachaDepth = 1;
			gachaFrame = 0;
			break;
		case AVK_GETRAIDGOLD:
			attackDelay = ATTACKDELAY_RAIDREWARD_COIN_BOOTS_RESULT - 2;
			break;
		case AVK_POPUP_HOWTOGETHEROES:
			SetPopUp(POPUPTYPE_HOWTOGETHEROES, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, systemKey - AVK_POPUP_HEROSTAT, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_POPUP_HOWTOGETCREWS:
			SetPopUp(POPUPTYPE_HOWTOGETCREWS, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, systemKey - AVK_POPUP_HEROSTAT, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_POPUP_LVUPREWARD:
			SetPopUp(POPUPTYPE_LEVELUP, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, systemKey - AVK_POPUP_HEROSTAT, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_POPUP_STAGEREWARD:
			int rewardBoxDetail;
			int rewardBoxGrade;

			rewardBoxDetail = stageClearBox[robin.stage];
			rewardBoxGrade = GRADE_NORMAL;

			boxReward = &rewardBoxData[rewardBoxDetail * TOTALGRADE * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + rewardBoxGrade * BOX1MAXREWARDITEM * REWARDITEMDATASIZE];

			itemCnt = 0;
			for (i = 0; i < BOX1MAXREWARDITEM; i++) {
				if (*(boxReward + 5 * i) != -1)
					itemCnt++;
			}

			//여기서 팝업을 띄워준다.
			//SetPopUp(POPUPTYPE_BOXREWARD, xOffset + (float)(DX / 2 - DIORAMASIZE_X * dioramaZoom / 2) * dioramaZoom + (float)stageEnemyPos[stageHouseType[robin.stage] * TOTALROOM * 3 + (systemKey - AVK_POPUP_STAGEREWARD) * 3 + 0] * dioramaZoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 - (float)(72 * _2X) * dioramaZoom + (float)stageEnemyPos[stageHouseType[robin.stage] * TOTALROOM * 3 + (systemKey - AVK_POPUP_STAGEREWARD) * 3 + 1] * dioramaZoom + 108 * _2X, (REWARDCARDSIZE_X + 4 * _2X) * itemCnt + 4 * _2X, REWARDCARDSIZE_Y + 32 * _2X,
			SetPopUp(POPUPTYPE_BOXREWARD, xOffset + (float)DX / 2, POPUPPOSITION_Y, (REWARDCARDSIZE_X + 4 * _2X) * 3 + 4 * _2X, REWARDCARDSIZE_Y + 32 * _2X,
				ITEM_BOX, rewardBoxDetail, rewardBoxGrade,
				*(boxReward), *(boxReward + 1), *(boxReward + 2), *(boxReward + 3), *(boxReward + 4),
				*(boxReward + 5), *(boxReward + 6), *(boxReward + 7), *(boxReward + 8), *(boxReward + 9),
				*(boxReward + 10), *(boxReward + 11), *(boxReward + 12), *(boxReward + 13), *(boxReward + 14));

			//SetPopUp(POPUPTYPE_STAGE, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
			//	false, false, false, false, false,
			//	false, false, false, false, false,
			//	false, false, false, false, false);
			break;
		case AVK_POPUP_HEROSTAT + ROBIN:
		case AVK_POPUP_HEROSTAT + DIANA:
		case AVK_POPUP_HEROSTAT + MAXX:
			SetPopUp(POPUPTYPE_HEROSTAT, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, systemKey - AVK_POPUP_HEROSTAT, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			curMenu = MENU_HERO;
			menuDepth = 0;
			menuX = 0;
			break;
		case AVK_SELECT_HERO + ROBIN:
		case AVK_SELECT_HERO + DIANA:
		case AVK_SELECT_HERO + MAXX:
			curHero = systemKey - AVK_SELECT_HERO;
			//if (curMenu == MENU_COLLECTIONS)
			//	scY[menuCur] = GetScrollDy(curMenu);
			break;
		case AVK_POPUP_CREWUPGRADE:
			SetPopUp(POPUPTYPE_CREWUPGRADE, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, systemKey - AVK_POPUP_HEROSTAT, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_POPUP_CREWLIST:
			curMenuBack = curMenu;
			curMenu = MENU_CREW;
			menuDepth = 0;
			menuX = 0;
			menuCur = 0;

			SetPopUp(POPUPTYPE_CREWLIST, DX / 2, DY - GNBHEIGHT, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_POPUP_CLOSE:
			ClosePopUp();
			break;
		case AVK_JOKBO:
			SetPopUp(POPUPTYPE_JOKBO, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_GETCREW:
			stageInfoFrame = STAGECLEARDELAY_NEWCARD - 1;
			break;
		case AVK_STAGEREWARD:
			stageInfoFrame = STAGECLEARDELAY_TABREWARD - 1;
			break;
		case AVK_STAGEFAILED:
			//stageInfoFrame = STAGECLEARDELAY_TABREWARD - 1;
			ClosePopUp();
			break;
		case AVK_NEWSTAGE:
			stageInfoDepth = STAGEINFO_STAGECLEAR;
			stageInfoFrame = 0;
			break;
		case AVK_SHOP_BUYBOX1:
		case AVK_SHOP_BUYBOX2:
		case AVK_SHOP_BUYBOX3:
			robin.gold -= GetBoxPrice(BOX_EQUIP_SILVER + systemKey - AVK_SHOP_BUYBOX1, GRADE_NORMAL);
			memset(&rewardItem, 0, sizeof(rewardItem));
			memset(&rewardMark, 0, sizeof(rewardMark));
			rewardMark[0].type = rewardItem[0].type = ITEM_BOX;
			rewardMark[0].detail = BOX_EQUIP_SILVER + systemKey - AVK_SHOP_BUYBOX1;
			rewardMark[0].grade = GRADE_NORMAL;
			rewardItemCnt = 1;
			boxCnt = 0;

			GotoGacha();
			break;
		case AVK_HOTKEYPRESS1:
		case AVK_HOTKEYPRESS2:
		case AVK_HOTKEYPRESS3:
			//여기서 바로 HotKeyPress를 터트려서 공격하는게 아니라 몇가지 케이스에서는 이동을 한 뒤 적 앞에 가서 터트린다.
			//
			ao[systemKey - AVK_HOTKEYPRESS1].currentSkill = ao[systemKey - AVK_HOTKEYPRESS1].hotKey[0].idx;

			if (IsMovingSkill(ao[systemKey - AVK_HOTKEYPRESS1].currentSkill) == false)
				HotKeyPress(&ao[systemKey - AVK_HOTKEYPRESS1], 0);

			break;
		}
	}
}

void DemoKey(void)
{
	int newItemType;
	int newItemDetail;
	int newItemGrade;

	int newItemRewardType;
	int newItemRewardDetail;
	int newItemRewardGrade;
	int newItemRewardCnt;

	if (systemKey == AVK_NEWDEMOITEMREWARD || systemKey == AVK_GETDEMOREWARD) {
		newItemType = boxCardItem[0][newItemIdx[curNewItemIdx]].type;
		newItemDetail = boxCardItem[0][newItemIdx[curNewItemIdx]].detail;
		newItemGrade = boxCardItem[0][newItemIdx[curNewItemIdx]].grade;

		newItemRewardType = newItemReward[itemStartCnt[newItemType] * REWARDITEMDATASIZE + newItemDetail * TOTALGRADE * REWARDITEMDATASIZE + newItemGrade * REWARDITEMDATASIZE + 0];
		newItemRewardDetail = newItemReward[itemStartCnt[newItemType] * REWARDITEMDATASIZE + newItemDetail * TOTALGRADE * REWARDITEMDATASIZE + newItemGrade * REWARDITEMDATASIZE + 1];
		newItemRewardGrade = newItemReward[itemStartCnt[newItemType] * REWARDITEMDATASIZE + newItemDetail * TOTALGRADE * REWARDITEMDATASIZE + newItemGrade * REWARDITEMDATASIZE + 2];
		newItemRewardCnt = newItemReward[itemStartCnt[newItemType] * REWARDITEMDATASIZE + newItemDetail * TOTALGRADE * REWARDITEMDATASIZE + newItemGrade * REWARDITEMDATASIZE + 3];
	}

	switch (systemKey) {
	case AVK_NEWDEMOITEMREWARD:
		break;
	case AVK_GETDEMOREWARD:
		winAniFrame = GACHADELAY_TAB;
		GetItem(newItemRewardType, 0, newItemRewardDetail, newItemRewardGrade, newItemRewardCnt, false);

		EquipItem(&ao[PLAYER], &robin.inven[GetInvenIdx(newItemRewardType, newItemRewardDetail, newItemRewardGrade)]);
		break;
	case AVK_DEMOSKIP:
		AfterDemo();
		break;
	}
}

void AlertKey(void)
{
	ITEM* it;
	OBJECT* pObj;

	if (winAniFrame < 8)

		return;

	switch (systemKey) {
	case AVK_4:
		yesNo = 0;
		break;
	case AVK_6:
		yesNo = 1;
		OutOfAlert();
		PlayMusic(M_CLOSEWINDOW);
		break;
	case AVK_5:
		infoText = 0;

		if (yesNo == 0) {
			infoFrame = 0;

			switch (alert) {
			case ALERT_INVENFULL:

				break;
				//퀘스트 완료 아이템을 장착했을 경우
			case ALERT_EQUIP:
				break;
			case ALERT_NOTICE:
				//if (!showNotice)
					GotoPlay();

				return;
				break;
			case ALERT_EXIT:
				break;

			}
		}
	case AVK_CLR:
		OutOfAlert();
		PlayMusic(M_CLOSEWINDOW);
		break;
	}
}


void ClearRoom(void)
{
	int i;
	turn = NEUTRAL;
	turnFrame = 0;
	turnPosition = NEXTROOM;
	arenaStatus = STATUS_RAIDCLEAR;
	option.gameControl = CONTROL_AUTO;
	attackSequence = ATTACKSEQUENCE_READY;
#ifdef ENEMYHPBAR
	for (i = 0; i < MAXENEMY; i++)
		bar[BAR_ENEMYHP + i].active = false;
#endif
	memset(&cardMark, 0, sizeof(cardMark));
	memset(&robin.enemyObj, 0, sizeof(robin.enemyObj));

	for (i = ENEMYUSEROBJ; i < TOTALOBJECT; i++)
		memset(&ao[i], 0, sizeof(OBJECT));

	curMenu = MENU_PLAY;
	xOffset = 0;
	menuDepth = 0;

	attackDelay = 0;
}
//이동해서 공격하는 스킬
bool IsMovingSkill(int idx)
{
	switch (idx) {
		//case SKILL_COMMON_ROBIN1:	//힘단련 : STR 상승
		//case SKILL_COMMON_ROBIN2:	//체력단련 : VIT 상승
		//case SKILL_COMMON_ROBIN3:	//민첩단련 : AGI 상승
		//case SKILL_COMMON_ROBIN4:	//정신단련 : INT 상승
		//case SKILL_COMMON_ROBIN5:	//생명력강화 : HP 최대치 상승
		//case SKILL_COMMON_ROBIN6:	//기력강화 : MP 최대치 상승
		//case SKILL_COMMON_ROBIN7:	//무기숙련 : 공격력 증가
		//case SKILL_COMMON_ROBIN8:	//방어구숙련: 방어력 증가
		//case SKILL_COMMON_ROBIN9:	//약점파악 : 크리티컬 확률 상승
		//case SKILL_COMMON_ROBIN10:	//약점공격 : 크리티컬 데미지 상승
		//case SKILL_COMMON_ROBIN11:	//뚝심 : 데미지 경감
		//case SKILL_COMMON_ROBIN12:	//정조준 : 명중 증가
		//case SKILL_COMMON_ROBIN13:	//신속회피 : 회피 증가

		//case SKILL_ROBIN1:	//검술숙련 : 관통 발생 확률 상승
		//case SKILL_ROBIN2:	//긴급방어 : 방어 발동 확률이 올라감(1레벨이면 방어 발동이 시작: 점점 확률 상승)
		//case SKILL_ROBIN3:	//방어숙련 : 방어 발동시 경감되는 데미지 퍼센트 상승
		//case SKILL_ROBIN4:	//면역력 : 상태이상에 대한 저항력 상승
		//case SKILL_ROBIN5:	//지구전 : INT가 높을수록 VIT 상승
		//case SKILL_ROBIN6:	//에어크래쉬 : 몹 뛰우기
		//case SKILL_ROBIN7:	//마구찌르기 : 난타
		//case SKILL_ROBIN8:	//부스트슬래쉬 : 가로로 크게 배기: 기절공격
		//case SKILL_ROBIN9:	//하이퍼차지 : 돌격공격: 적을 뒤로 날려버림
		//case SKILL_ROBIN10:	//소울크래쉬 : 기절
		//case SKILL_ROBIN11:	//앱솔루트피어스 : 찔러서회전
		//case SKILL_ROBIN12:	//멸살연참 : 연속기
		//case SKILL_ROBIN13:	//방어태세 : 일정시간 VIT 상승
		//case SKILL_ROBIN14:	//정신소모 : MP 소모하여 데미지 경감
		//case SKILL_ROBIN15:	//여유포착 : 적 공격 회피시 HP 상승
		//case SKILL_ROBIN16:	//냉정침착 : 데미지 입으면 MP 회복
		//case SKILL_ROBIN17:	//리플렉션 : 확률로데미지 반사

		//case SKILL_COMMON_DIANA1:	//힘단련 : STR 상승
		//case SKILL_COMMON_DIANA2:	//체력단련 : VIT 상승
		//case SKILL_COMMON_DIANA3:	//민첩단련 : AGI 상승
		//case SKILL_COMMON_DIANA4:	//정신단련 : INT 상승
		//case SKILL_COMMON_DIANA5:	//생명력강화 : HP 최대치 상승
		//case SKILL_COMMON_DIANA6:	//기력강화 : MP 최대치 상승
		//case SKILL_COMMON_DIANA7:	//무기숙련 : 공격력 증가
		//case SKILL_COMMON_DIANA8:	//방어구숙련: 방어력 증가
		//case SKILL_COMMON_DIANA9:	//약점파악 : 크리티컬 확률 상승
		//case SKILL_COMMON_DIANA10:	//약점공격 : 크리티컬 데미지 상승
		//case SKILL_COMMON_DIANA11:	//뚝심 : 데미지 경감
		//case SKILL_COMMON_DIANA12:	//정조준 : 명중 증가
		//case SKILL_COMMON_DIANA13:	//신속회피 : 회피 증가

		//case SKILL_DIANA1:	//매의눈 : 공격 거리 상승
		//case SKILL_DIANA2:	//사격숙련 : 기절공격이 발생할 확률이 상승
		//case SKILL_DIANA3:	//아드레날린 : 기절공격 성공시 MP 회복량 상승
		//case SKILL_DIANA4:	//활성화 : 스킬 재사용 시간 감소
		//case SKILL_DIANA5:	//집중력유지 : STR이 높을수록 INT 상승
		//case SKILL_DIANA6:	//3way : 3방향으로 총 발사
		//case SKILL_DIANA7:	//리플렉션빔 : 레이져가 벽에 튕김
		//case SKILL_DIANA8:	//헬파이어 : 화염 방사기
		//case SKILL_DIANA9:	//로켓런쳐 : 로켓 발사되어 폭발
		//case SKILL_DIANA10:	//호밍미사일 : 유도탄 3개
		//case SKILL_DIANA11:	//킬링존 : 난사
		//case SKILL_DIANA12:	//오비탈레이져 : 인공위성
		//case SKILL_DIANA13:	//리커버리 : 회복탄
		//case SKILL_DIANA14:	//흥분고조 : 방어력 저하 공격력 상승
		//case SKILL_DIANA15:	//흡마의마탄 : 공격시 MP 흡수
		//case SKILL_DIANA16:	//필살집중 : 크리 상승
		//case SKILL_DIANA17:	//파마의직격 : 일정시간 적 방어 무시

		//case SKILL_COMMON_MAXX1:	//힘단련 : STR 상승
		//case SKILL_COMMON_MAXX2:	//체력단련 : VIT 상승
		//case SKILL_COMMON_MAXX3:	//민첩단련 : AGI 상승
		//case SKILL_COMMON_MAXX4:	//정신단련 : INT 상승
		//case SKILL_COMMON_MAXX5:	//생명력강화 : HP 최대치 상승
		//case SKILL_COMMON_MAXX6:	//기력강화 : MP 최대치 상승
		//case SKILL_COMMON_MAXX7:	//무기숙련 : 공격력 증가
		//case SKILL_COMMON_MAXX8:	//방어구숙련: 방어력 증가
		//case SKILL_COMMON_MAXX9:	//약점파악 : 크리티컬 확률 상승
		//case SKILL_COMMON_MAXX10:	//약점공격 : 크리티컬 데미지 상승
		//case SKILL_COMMON_MAXX11:	//뚝심 : 데미지 경감
		//case SKILL_COMMON_MAXX12:	//정조준 : 명중 증가
		//case SKILL_COMMON_MAXX13:	//신속회피 : 회피 증가

		//case SKILL_MAXX1:	//관통력숙련 : 적을 공격했을 때 부메랑의 판정이 남아있을 확률이 상승한다.
		//case SKILL_MAXX2:	//투척숙련 : 부메랑 속도 상승
		//case SKILL_MAXX3:	//연속공격 : 추가 공격 확률 증가
		//case SKILL_MAXX4:	//회전력상승 : 추가 공격 성공시 해당 공격에 대해서 데미지 상승
		//case SKILL_MAXX5:	//탄력성 : VIT 높을수록 AGI 상승
		//case SKILL_MAXX6:	//효율적사고 : INT가 높을수록 AGI가 올라감
	case SKILL_MAXX7:	//돌려차기 : 회전: 기절공격
		//case SKILL_MAXX8:	//숏헌트 : 관통: 사거리 짧음
		//case SKILL_MAXX9:	//에어헌트 : 수직 상승 공격
		//case SKILL_MAXX10:	//캠핑헌트 : 앞으로 날라가서 제자리회전
		//case SKILL_MAXX11:	//호밍헌트 : 가장 가까운 적 때리고 되돌아옴
		//case SKILL_MAXX12:	//써클헌트 : 주인공 주변 보호
		//case SKILL_MAXX13:	//메가헌트 : 관통후 뒤에서 돌아옴
		//case SKILL_MAXX14:	//블러드헌트 : 적 공격시 HP 회복
		//case SKILL_MAXX15:	//현란무도 : 일정시간 회피율 증가
		//case SKILL_MAXX16:	//안도의한숨 : 적 공격 회피시 MP 회복
		//case SKILL_MAXX17:	//혼신분리 : 기절 확률 상승
		return true;
	}

	return false;
}

void HotKeyPress(OBJECT* pObj, int idx)
{
	//스킬 딜레이 감소옵션에 따라서 재사용시간을 줄여준다.
	//대원 동굴 밸런스 - 스딜

	int obj = GetObjFromPtr(pObj);
	int limitStat = pObj->ps[PS_DELAY];
	int delay = 100 - limitStat;
	int i, j;
	int closestEnemy;

	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];

	if (pObj->hotKey[idx].type != HOTKEY_SCREEN)

		//if (obj == raidPlayer)
		//	ReleaseCore();
		//else
		PlayRelease(pObj);

	switch (pObj->hotKey[idx].type) {
		//아무것도 하지 않는다.
	case HOTKEY_NOTHING:
		break;
		//스킬인 경우 해당 스킬을 사용할 수 있는 조건이면 써준다.
		//조건1 MP가 충분한가
		//조건2 현재 시전할수 있는 상태인가
		//조건3 현재 사용하는 스킬이 장비에 맞는 스킬인가
	case HOTKEY_SKILL:
		/*
		if (pObj->dead == true || pObj->hotKey[idx].frame != 0 || pObj->debuf[KNOCKBACK] || pObj->debuf[CURSE] || pObj->debuf[STUN] || pObj->attack >= ATTACK_SKILL) {
			if (obj < TOTALPLAYER) {
				infoFrame = INFOFRAME;
				if (pObj->dead == true)
					infoText = TEXT_CANNOTUSE_DEAD;
				else if (pObj->hotKey[idx].frame != 0)
					infoText = TEXT_CANNOTUSE_COOLTIME;
				else if (pObj->attack >= ATTACK_SKILL)
					infoText = TEXT_CANNOTUSE_SKILL;
				else if (pObj->debuf[CURSE])
					infoText = TEXT_CANNOTUSE_CURSE;
				else if (pObj->debuf[STUN])
					infoText = TEXT_CANNOTUSE_STUN;
				else if (pObj->debuf[KNOCKBACK])
					infoText = TEXT_CANNOTUSE_KNOCKBACK;
				else
					infoText = TEXT_CANNOTUSE;
			}
			return;
		}
		*/

		switch (pObj->hotKey[idx].idx) {
		case SKILL_DIANA14://흥분고조 : 스킬 데미지 업
			j = 0;
			for (i = 0; i < MAXCHARSKILL; i++) {
				if (pObj->getSkillList[i] != -1 && pObj->hotKey[pObj->getSkillList[i]].frame == 0) {
					j++;
				}
			}
			if (j == 0)
				return;
			break;
		case SKILL_MAXX16://안도의한숨 : 상태이상 전부회복
			j = 0;
			for (i = 0; i < TOTALDEBUF; i++) {
				if (!pObj->debuf[i])
					j++;
			}
			if (j == 0)
				return;
			break;
		}

		pObj->attack = skillData[SKILLDATASIZE * pObj->hotKey[idx].idx + SKILLDATASIZE - 3];
		pObj->attackFrame = skillStartFrame[pObj->attack];

		HitCountCheck(pObj);

		closestEnemy = GetClosestObj(pObj);

		if (option.gameControl == CONTROL_AUTO || option.gameControl == CONTROL_AI) {
			if (ao[closestEnemy].x < pObj->x) {
				pObj->dirX = pObj->dirF = LEFT;
			}
			else {
				pObj->dirX = pObj->dirF = RIGHT;
			}
		}

		if (pObj->type == DIANA && pObj->attack == DIANA_SKILL_FLAMER) {
			pObj->attack = false;
			//pObj->flamer = 1 - pObj->flamer;
			pObj->flamer = FPS;// FLAMER_START_FRAME;
			pObj->hotKey[idx].frame = pObj->hotKey[idx].inven;
			pObj->currentSkill = pObj->hotKey[idx].idx;

			PlayMusic(M_FIRE);

			return;
		}


		//스킬 시전
		GetMotionPtr(pObj);

		//pObj->mp -= needMp;
		pObj->continueAttack = false;
		pObj->attackFrame = skillStartFrame[pObj->attack];
		pObj->hotKey[idx].frame = pObj->hotKey[idx].inven;

		PlayRelease(pObj);
		pObj->currentSkill = pObj->hotKey[idx].idx;

		if (tutorialMode == true) {
			if (tutorialStep == TUTORIAL_USE_SKILL) {
				tutorialStep = TOTAL_TUTORIAL;
				popUpFrame = 0;
			}
		}

		break;
	case HOTKEY_RING:
		if (pObj->dead == true || pObj->attack >= ATTACK_SKILL || pObj->hotKey[idx].frame != 0 || pObj->debuf[KNOCKBACK] || (pObj->debuf[STUN] && pObj->equip[EQUIP_RING].detail != ITEM_RING3)) {
			if (obj == raidPlayer && (drawHandle == MD_PLAY || drawHandle == MD_BATTLE || drawHandle == MD_RAID || drawHandle == MD_BOSSRAID)) {
				infoFrame = INFOFRAME;
				if (pObj->dead == true)
					infoText = TEXT_CANNOTUSE_DEAD;
				else if (pObj->hotKey[idx].frame != 0)
					infoText = TEXT_CANNOTUSE_COOLTIME;
				else if (pObj->attack >= ATTACK_SKILL)
					infoText = TEXT_CANNOTUSE_SKILL;
				else if (pObj->debuf[STUN])
					infoText = TEXT_CANNOTUSE_STUN;
				else if (pObj->debuf[KNOCKBACK])
					infoText = TEXT_CANNOTUSE_KNOCKBACK;
				else
					infoText = TEXT_CANNOTUSE;
			}

			return;
		}



		GetMotionPtr(pObj);

		pObj->currentSkill = idx;
		pObj->attack = ATTACK_MAGIC;
		pObj->attackFrame = skillStartFrame[ATTACK_MAGIC];
		pObj->hotKey[obj].frame = pObj->hotKey[obj].inven;

		//attackDelay = FPS * 3;
		//effect.color = COLOR_BLACK;

		if (obj == raidPlayer && (drawHandle == MD_PLAY || drawHandle == MD_BATTLE || drawHandle == MD_RAID || drawHandle == MD_BOSSRAID)) {

			curSkill = pObj->hotKey[idx].idx + 100;
			skillUsed = RINGEFFECTFRAME;
			skillInfoFrame = INFOFRAME;
			ringUser = obj;
			memset(ringStr, 0, sizeof(ringStr));
			sprintf(ringStr, TEXTPTR(TEXT_SKILL_START), TEXTPTR(TEXT_ITEMNAME_START + GetItemName(ITEM_RING, pObj->equip[EQUIP_RING].detail, pObj->equip[EQUIP_RING].grade)));
			SetFrameTextStr(ringStr, DX, 1, 2.0f, itemColorText[pObj->equip[EQUIP_RING].grade]);
			PlayMusic(M_BUFF_PINK);
		}
		break;
	}
}

void GachaKey(void)
{
	PlayKey(PLAYER);
}

void NewSkillKey(void)
{
	PlayKey(PLAYER);
}

void NewCollectionKey(void)
{
	PlayKey(PLAYER);
}

void NewCardKey(void)
{
	PlayKey(PLAYER);
}

void HouseKey(void)
{
	PlayKey(PLAYER);
}


// KeyRelease

void ReleaseCore(void)
{
	key_released = true;

	switch (systemRelease) {
	case AVK_LEFT:
		systemRelease = AVK_4;
		break;
	case AVK_RIGHT:
		systemRelease = AVK_6;
		break;
	case AVK_UP:
		systemRelease = AVK_2;
		break;
	case AVK_DOWN:
		systemRelease = AVK_8;
		break;
	case AVK_SELECT:
		systemRelease = AVK_5;
		break;
	}

	switch (keyHandle) {
#ifdef RELEASEEXEC
	case MK_TITLE:
#ifdef COSTUMETEST
		PlayKey(raidPlayer);
#else
		TitleKey();
#endif
		break;
	case MK_ALERT:
		AlertKey();
		break;
	case MK_PLAY:
		PlayKey(raidPlayer);
		break;
	case MK_BATTLE:
		PlayKey(raidPlayer);
		break;
	case MK_RAID:
		PlayKey(raidPlayer);
		break;
	case MK_BOSSRAID:
		PlayKey(raidPlayer);
		break;
	case MK_DEMO:
		//DemoKey();
		break;
	case MK_GACHA:
		GachaKey();
		break;
	case MK_NEWCOLLECTION:
		PlayKey(raidPlayer);
		break;
	case MK_NEWCARD:
		NewCardKey();
		break;
	case MK_STAGECLEAR:
		PlayKey(raidPlayer);
		break;
#endif
	}

	if (is_key_released == true && touchMode == TOUCH_YESNO && (systemKey == AVK_5 || systemKey == AVK_CLR)) {
		if (yesNo == 0) {
			touchMode = touchModeOld;
			touchModeOld = null;
		}
		else if (yesNo == 1) {
			touchMode = touchModeOld;
		}
	}

	if (touchModeOld && touchMode == TOUCH_YESNO && (systemKey == AVK_5 || systemKey == AVK_CLR)) {
		touchMode = touchModeOld;
		touchModeOld = null;
		touchYESNO = false;
	}

	if (is_key_released == true && touchOK == true && (systemKey == AVK_CLR || systemKey == AVK_5)) {
		touchModeOld = null;
		touchOK = false;
	}

	isTouchKey = TOUCH_NULL;
	systemKey = null;
	systemRelease = null;
	is_release_finished = true;
	is_key_released = false;
	twice_released = false;

	touchYESNO = false;		//TouchArrow 가 그려져 있을때만 YesNoDraw() 양옆에 화살표 터치가 작동하게 하기 위해..
	is_touchkey_pressed = false;

	touchedFrame = 0;
	scDir = SCROLL_NOTHING;
}

void PlayRelease(OBJECT* pObj)
{
	releaseClearFrame = MC_knlCurrentTime();
	releasedKey = systemRelease;

	if (!pObj->attack) {
		switch (systemRelease) {
		case AVK_4:
			if (pObj->pressedKey[1] != AVK_4) {
				pObj->playerRun = false;
				pObj->mx = false;
			}
			break;
		case AVK_6:
			if (pObj->pressedKey[1] != AVK_6) {
				pObj->playerRun = false;
				pObj->mx = false;
			}
			break;
		case AVK_2:
			break;
		case AVK_1:
		case AVK_3:
			if (pObj->playerRun != false && pObj->pressedKey[0] != null)
				break;
		default:
			pObj->playerRun = false;
			pObj->mx = false;
			break;
		}

		if (pObj->status == GLIDE) {
			if (arenaStatus != STATUS_PLAY) {
				pObj->status = FALL;
				pObj->jumpFrame = 0;
			}
		}
	}

	if (pObj->jumpRelease)
		pObj->jumpRelease = false;
}

void ReleasePlayer(OBJECT* pObj)
{
	PlayRelease(pObj);
}


// Touch 관련
void TouchEndedPlayer(OBJECT* pObj)
{
	if (pObj->dead == false && !pObj->debuf[KNOCKBACK] && !pObj->debuf[STUN] && pObj->currentSkill <= 0) {
		if (isTouchKey == TOUCH_PRESS || isTouchKey == TOUCH_DRAG) {
			if (!pObj->attack) {
				if (!(pObj->type == DIANA && pObj->flamer > 0) && !(pObj->type == MAXX && boomerangAway[GetObjFromPtr(pObj)])) {


					//아래로 드래그
					if (touchPressedKey[1][1] - touchPressedKey[0][1] > SWIPE_DISTANCE_Y && isTouchKey == TOUCH_DRAG) {
						pObj->pressedKey[2] = pObj->pressedKey[1];
						pObj->pressedKey[1] = pObj->pressedKey[0];
						pObj->pressedKey[0] = AVK_8;

					}
					else if (touchedFrame < TOUCHCANCELFRAME) {
						pObj->pressedKey[2] = pObj->pressedKey[1];
						pObj->pressedKey[1] = pObj->pressedKey[0];
						pObj->pressedKey[0] = AVK_5;
					}

					GetMotionPtr(&ao[raidPlayer]);

					if (pObj->playerRun == true && pObj->pressedKey[0] == AVK_5) {
						pObj->attack = ATTACK_DASH;
						pObj->attackFrame = skillStartFrame[ATTACK_DASH];
						HitCountCheck(pObj);
					}
					else if (pObj->status == WALK) {
						if (pObj->pressedKey[0] == AVK_5) {

							pObj->attack = ATTACK_NORMAL;
							pObj->attackFrame = skillStartFrame[pObj->attack];
							HitCountCheck(pObj);
						}
					}
					else if ((pObj->status == JUMP || pObj->status == FALL || pObj->status == GLIDE || pObj->status == FLYING) && !pObj->attack) {
						if (pObj->pressedKey[0] == AVK_8) {
							GetMotionPtr(pObj);

							pObj->currentSkill = -1;
							pObj->mx = false;
							pObj->dx = 0;
							pObj->status = FALL;
							pObj->dirY = DOWN;
							pObj->jumpFrame = 0;

							if (GetObjHeight(pObj) > 64 * _2X && pObj->canDown == true) {
								pObj->attack = ATTACK_DOWN;
								pObj->attackFrame = skillStartFrame[ATTACK_DOWN];
								HitCountCheck(pObj);
							}
						}
						else if (pObj->pressedKey[0] == AVK_5) {
							pObj->attack = ATTACK_AIR;
							pObj->attackFrame = skillStartFrame[ATTACK_AIR];
							HitCountCheck(pObj);
						}
					}
				}
			}
			else if (pObj->attack == ATTACK_NORMAL) {
				if (pObj->type == ROBIN ||
					pObj->type == DIANA) {
					pObj->pressedKey[2] = pObj->pressedKey[1];
					pObj->pressedKey[1] = pObj->pressedKey[0];
					pObj->pressedKey[0] = AVK_5;
				}
			}
		}
		else {
			ReleasePlayer(pObj);
		}
	}
	else {
		ReleasePlayer(pObj);
	}
}

int GetTouchFunc(int x, int y)
{
	int i;
	for (i = touchIndex - 1; i >= 0; i--) {
		if (GetRectPoint(x, y, touchRect[i][0], touchRect[i][1], touchRect[i][2], touchRect[i][3])) {
			return touchRect[i][4];
		}
	}

	return false;
}

void ExecTouchFunc(int x, int y)
{
	int i;
	for (i = touchIndex - 1; i >= 0; i--) {
		if (GetRectPoint(x, y, touchRect[i][0], touchRect[i][1], touchRect[i][2], touchRect[i][3])) {

			if (startTouchCheck == true) {
				startTouchRect[0] = touchRect[i][0];//x
				startTouchRect[1] = touchRect[i][1];//y
				startTouchRect[2] = touchRect[i][2];//width
				startTouchRect[3] = touchRect[i][3];//height
			}

			touchFunc(touchRect[i][4]);
			return;
		}
	}
}

int GetRectPoint(int x, int y, int rx, int ry, int width, int height)
{
	if (x > rx && x < rx + width && y > ry - height && y < ry)
		return 1;

	return 0;
}

int GetSwipePoint(int x, int y, int rx, int ry, int width, int height)
{
	if (x > rx && x < rx + width && y > ry - height && y < ry)
		return 1;

	return 0;
}

void ResetRectPoint(void)
{
	int i;
	for (i = 0; i < TOTALTOUCHCNT; i++)
		memset(touchRect, 0, sizeof(touchRect));
	touchIndex = 0;
}

void ResetSwipetPoint(void)
{
	int i;
	for (i = 0; i < TOTALSWIPECNT; i++)
		memset(swipeRect, 0, sizeof(swipeRect));
	swipeIndex = 0;
}

void SetRectPoint(int rx, int ry, int width, int height, int func)
{
	touchRect[touchIndex][0] = rx;
	touchRect[touchIndex][1] = ry;
	touchRect[touchIndex][2] = width;
	touchRect[touchIndex][3] = height;
	touchRect[touchIndex][4] = func;

	touchIndex++;
}

void SetSwipePoint(int rx, int ry, int width, int height, int func)
{
#ifdef CONTROL_MANUAL
	swipeRect[swipeIndex][0] = rx;
	swipeRect[swipeIndex][1] = ry;
	swipeRect[swipeIndex][2] = width;
	swipeRect[swipeIndex][3] = height;
	swipeRect[swipeIndex][4] = func;
	swipeIndex++;
#endif
}

void touchFunc(int func)
{
	int i, j, k, temp = 0;
	int doorY = 256 * _2X;
	int x = DX / 2 - STATUSWIN_X / 2;
	int y = DY / 2 + MINDY / 2;
	ITEM* it;
	int itemType, itemDetail, itemGrade;

	int grade = GRADE_LEGEND;
	int detail;
	OBJECT* pObj;

	//현재 터치하면 안되면
	if (touchDisable)
		return;

	//인벤토리같이 키와 1:1대응이 안되는 것들은 여기서 바로 처리한다.
	if (func >= TOUCH_FUNC_BATTLE_TARGET && func < TOUCH_FUNC_BATTLE_TARGET + MAXCREW)
	{
		systemKey = AVK_BATTLE_TARGET + (func - TOUCH_FUNC_BATTLE_TARGET);
	}
	else if (func >= TOUCH_FUNC_RAID_TARGET && func < TOUCH_FUNC_RAID_TARGET + TOTALRAIDBOX)
	{
		systemKey = AVK_RAID_TARGET + (func - TOUCH_FUNC_RAID_TARGET);
	}
	else if (func >= TOUCH_FUNC_EVENT_BOSSRAID_REWARDINFO && func < TOUCH_FUNC_EVENT_BOSSRAID_REWARDINFO + BOSSRAIDSIZE)
	{
		systemKey = AVK_BOSSRAID_REWARDINFO + (func - TOUCH_FUNC_EVENT_BOSSRAID_REWARDINFO);
	}
	else if (func >= TOUCH_FUNC_CREWSTARUPGRADE && func < TOUCH_FUNC_CREWSTARUPGRADE + MAXCREW) {
		systemKey = AVK_CREWSTARUPGRADE + func - TOUCH_FUNC_CREWSTARUPGRADE;
	}
	else if (func >= TOUCH_FUNC_CREWUPGRADE && func < TOUCH_FUNC_CREWUPGRADE + MAXCREW) {
		systemKey = AVK_CREWUPGRADE + func - TOUCH_FUNC_CREWUPGRADE;
	}
	else if (func >= TOUCH_FUNC_HIT_ATTACK && func < TOUCH_FUNC_HIT_ATTACK + MAXCREW) {
		systemKey = AVK_HIT_ATTACK + func - TOUCH_FUNC_HIT_ATTACK;
	}
	else if (func >= TOUCH_FUNC_COLLECTIONS_REWARD && func < TOUCH_FUNC_COLLECTIONS_REWARD + TOTAL_COLLECTIONS) {
		systemKey = AVK_COLLECTIONS_REWARD + func - TOUCH_FUNC_COLLECTIONS_REWARD;
	}
	else if (func >= TOUCH_FUNC_EQUIPALL && func < TOUCH_FUNC_EQUIPALL + TOTAL_COLLECTIONS) {
		systemKey = AVK_EQUIPALL + func - TOUCH_FUNC_EQUIPALL;
	}
	else if (func >= TOUCH_FUNC_ITEMDETAIL && func < TOUCH_FUNC_ITEMDETAIL + OPENEDMAXITEMCNT) {
		systemKey = AVK_ITEMDETAIL + func - TOUCH_FUNC_ITEMDETAIL;
	}
	else if (func >= TOUCH_FUNC_EQUIPDETAIL && func < TOUCH_FUNC_EQUIPDETAIL + TOTALEQUIP) {
		systemKey = AVK_EQUIPDETAIL + func - TOUCH_FUNC_EQUIPDETAIL;
	}
	else if (func >= TOUCH_FUNC_EQUIP_INVENTORY && func < TOUCH_FUNC_EQUIP_INVENTORY + TOTALINVENTORY) {
		for (i = 0; i < TOTALITEMTYPE; i++)
			if (func - TOUCH_FUNC_EQUIP_INVENTORY < itemStartCnt[i + 1]) {
				itemType = i;
				break;
			}

		itemDetail = ((func - TOUCH_FUNC_EQUIP_INVENTORY) - itemStartCnt[itemType]) / TOTALGRADE;
		itemGrade = ((func - TOUCH_FUNC_EQUIP_INVENTORY) - itemStartCnt[itemType]) % TOTALGRADE;

		systemKey = AVK_INVENTORY_SELECTITEM + GetInvenIdx(itemType, itemDetail, itemGrade);
	}
	else if (func >= TOUCH_FUNC_CREW_DETAIL && func < TOUCH_FUNC_CREW_DETAIL + TOTAL_CREW) {
		systemKey = AVK_CREW_DETAIL + func - TOUCH_FUNC_CREW_DETAIL;
	}
	else if (func >= TOUCH_FUNC_CREW_REWARD && func < TOUCH_FUNC_CREW_REWARD + TOTAL_CREW) {
		systemKey = AVK_CREW_REWARD + func - TOUCH_FUNC_CREW_REWARD;
	}
	else if (func >= TOUCH_FUNC_COLLECTIONS_DETAIL && func < TOUCH_FUNC_COLLECTIONS_DETAIL + TOTAL_COLLECTIONS) {
		systemKey = AVK_COLLECTIONS_DETAIL + func - TOUCH_FUNC_COLLECTIONS_DETAIL;
	}
	else if (func >= TOUCH_FUNC_COLLECTIONS_ITEMDETAIL && func < TOUCH_FUNC_COLLECTIONS_ITEMDETAIL + COLLECTIONSITEMCNT) {
		systemKey = AVK_COLLECTIONS_ITEMDETAIL + func - TOUCH_FUNC_COLLECTIONS_ITEMDETAIL;
	}
	else if (func >= TOUCH_FUNC_COLLECTIONS_EQUIP && func < TOUCH_FUNC_COLLECTIONS_EQUIP + TOTALEQUIP) {
		systemKey = AVK_COLLECTIONS_EQUIP + func - TOUCH_FUNC_COLLECTIONS_EQUIP;
	}
	else {
		switch (func) {
		case TOUCH_FUNC_OPENING:
			systemKey = AVK_5;
			break;
		case TOUCH_FUNC_TITLE:
			systemKey = AVK_5;
			break;

		case TOUCH_FUNC_TITLE_LOGIN_FACEBOOK:
			systemKey = AVK_LOGIN_FACEBOOK;
			break;
		case TOUCH_FUNC_TITLE_LOGIN_GOOGLE:
			systemKey = AVK_LOGIN_GOOGLE;
			break;
		case TOUCH_FUNC_TITLE_LOGIN_APPLE:
			systemKey = AVK_LOGIN_APPLE;
			break;
		case TOUCH_FUNC_TITLE_LOGIN_GUEST:
			systemKey = AVK_LOGIN_GUEST;
			break;

		case TOUCH_FUNC_TITLE_NEWGAME:
			systemKey = AVK_NEWGAME;
			break;

		case TOUCH_FUNC_PLAY://플레이
			systemKey = AVK_PLAY;
			break;
		case TOUCH_FUNC_COLLECTIONS://동료
			systemKey = AVK_COLLECTIONS;
			break;
		case TOUCH_FUNC_STAGE_POPUP:
			systemKey = AVK_STAGE_POPUP;
			break;
		case TOUCH_FUNC_SHOP://상점
			systemKey = AVK_SHOP;
			break;
		case TOUCH_FUNC_STARSHOP://상점
			systemKey = AVK_STARSHOP;
			break;
		case TOUCH_FUNC_NEWS://캐슬 뉴스
			systemKey = AVK_NEWS;
			break;
		case TOUCH_FUNC_GIFTS://선물
			systemKey = AVK_GIFTS;
			break;
		case TOUCH_FUNC_LEADERBOARD://
			systemKey = AVK_LEADERBOARD;
			break;
		case TOUCH_FUNC_FRIENDS://
			systemKey = AVK_FRIENDS;
			break;
		case TOUCH_FUNC_INVITEFRIENDS://
			systemKey = AVK_INVITEFRIENDS;
			break;
		case TOUCH_FUNC_CALENDAR://
			systemKey = AVK_CALENDAR;
			break;
		case TOUCH_FUNC_SETTING://
			systemKey = AVK_SETTING;
			break;
		case TOUCH_FUNC_LIST:
			systemKey = AVK_LIST;
			break;
		case TOUCH_FUNC_EVENT_QUEST:
			systemKey = AVK_EVENT_QUEST;
			break;
		case TOUCH_FUNC_EVENT_PVP:
			systemKey = AVK_EVENT_PVP;
			break;
		case TOUCH_FUNC_EVENT_SHOP:
			systemKey = AVK_EVENT_SHOP;
			break;
		case TOUCH_FUNC_EVENT_DEBTDISCOUNT:
			systemKey = AVK_EVENT_DEBTDISCOUNT;
			break;
		case TOUCH_FUNC_EVENT_DOUBLE:
			systemKey = AVK_EVENT_DOUBLE;
			break;
		case TOUCH_FUNC_EVENT_BOSSRAID:
			systemKey = AVK_EVENT_BOSSRAID;
			break;
		case TOUCH_FUNC_BOXINFO:
			systemKey = AVK_BOXINFO;
			break;
		case TOUCH_FUNC_GAMEMENU:
			systemKey = AVK_GAMEMENU;
			break;
		case TOUCH_FUNC_GAMEMENU_OUT:
			systemKey = AVK_CLR;
			break;
		case TOUCH_FUNC_BOSSRAID_OUT:
			systemKey = AVK_BOSSRAIDOUT;
			break;
		case TOUCH_FUNC_HOME_LEFT:
			systemKey = AVK_HOME_LEFT;
			break;
		case TOUCH_FUNC_HOME_RIGHT:
			systemKey = AVK_HOME_RIGHT;
			break;
		case TOUCH_FUNC_STAGE_LEFT:
			systemKey = AVK_STAGE_LEFT;
			break;
		case TOUCH_FUNC_STAGE_RIGHT:
			systemKey = AVK_STAGE_RIGHT;
			break;
		case TOUCH_FUNC_STAGEINFO:
			systemKey = AVK_STAGEINFO;
			break;
		case TOUCH_FUNC_BUYHOME:
			systemKey = AVK_BUYHOME;
			break;


		case TOUCH_FUNC_EQUIP_INVENTORY:
			systemKey = AVK_ITEMEQUIP;
			break;
		case TOUCH_FUNC_EQUIP_ENCHANT:
			systemKey = AVK_EQUIP_ENCHANT_SELECT;
			break;
		case TOUCH_FUNC_EQUIP_HAMMER:
			systemKey = AVK_EQUIP_HAMMER_SELECT;
			break;
		case TOUCH_FUNC_EQUIP_NEWITEM:
			systemKey = AVK_EQUIP_NEWITEM;

			break;
		case TOUCH_FUNC_DISASSEMBLE_NEWITEM:
			systemKey = AVK_DISASSEMBLE_NEWITEM;
			break;
		case TOUCH_FUNC_OPTION_BGM:
			systemKey = AVK_OPTION_BGM;
			break;
		case TOUCH_FUNC_OPTION_SE:
			systemKey = AVK_OPTION_SE;
			break;
		case TOUCH_FUNC_OPTION_VIBRATION:
			systemKey = AVK_OPTION_VIBRATION;
			break;
		case TOUCH_FUNC_OPTION_LANGUAGE:
			systemKey = AVK_OPTION_LANGUAGE;
			break;
		case TOUCH_FUNC_OPTION_NICKNAME:
			systemKey = AVK_OPTION_NICKNAME;
			break;
		case TOUCH_FUNC_OPTION_FACEBOOK:
			systemKey = AVK_OPTION_FACEBOOK;
			break;
		case TOUCH_FUNC_OPTION_GOOGLE:
			systemKey = AVK_OPTION_GOOGLE;
			break;
		case TOUCH_FUNC_OPTION_GAMECENTER:
			systemKey = AVK_OPTION_GAMECENTER;
			break;
		case TOUCH_FUNC_OPTION_GUEST:
			systemKey = AVK_OPTION_GUEST;
			break;
		case TOUCH_FUNC_OPTION_VOICE:
			systemKey = AVK_OPTION_VOICE;
			break;
		case TOUCH_FUNC_OPTION_SCREENEFFECT:
			systemKey = AVK_OPTION_EFFECT;
			break;
		case TOUCH_FUNC_OPTION_PUSHALARM:
			systemKey = AVK_OPTION_PUSHALARM;
			break;
		case TOUCH_FUNC_OPTION_ACCOUNT:
			systemKey = AVK_OPTION_ACCOUNT;
			break;
		case TOUCH_FUNC_OPTION_POLICY:
			systemKey = AVK_OPTION_POLICY;
			break;
		case TOUCH_FUNC_OPTION_COMMUNITY:
			systemKey = AVK_OPTION_COMMNUNITY;
			break;
		case TOUCH_FUNC_GAMEMENU_NEWS:
			systemKey = AVK_GAMEMENU_NEWS;
			break;
		case TOUCH_FUNC_GAMEMENU_RANKING:
			systemKey = AVK_GAMEMENU_RANKING;
			break;
		case TOUCH_FUNC_GAMEMENU_MAIL:
			systemKey = AVK_GAMEMENU_MAIL;
			break;
		case TOUCH_FUNC_GAMEMENU_SETTING:
			systemKey = AVK_GAMEMENU_SETTING;
			break;

		case TOUCH_FUNC_GAMEMENU_NEWS_CLR:
			systemKey = AVK_GAMEMENU_NEWS_CLR;
			break;
		case TOUCH_FUNC_GAMEMENU_RANKING_CLR:
			systemKey = AVK_GAMEMENU_RANKING_CLR;
			break;
		case TOUCH_FUNC_GAMEMENU_MAIL_CLR:
			systemKey = AVK_GAMEMENU_MAIL_CLR;
			break;
		case TOUCH_FUNC_GAMEMENU_SETTING_CLR:
			systemKey = AVK_GAMEMENU_SETTTING_CLR;
			break;

		case TOUCH_FUNC_GAMEMENU_OUTOFGAME:
			systemKey = AVK_GAMEMENU_OUTOFGAME;
			break;

		case TOUCH_FUNC_TABMENU1:
			systemKey = AVK_TABMENU1;
			break;
		case TOUCH_FUNC_TABMENU2:
			systemKey = AVK_TABMENU2;
			break;
		case TOUCH_FUNC_TABMENU3:
			systemKey = AVK_TABMENU3;
			break;
		case TOUCH_FUNC_TABMENU4:
			systemKey = AVK_TABMENU4;
			break;

		case TOUCH_FUNC_TABMENUX_1:
			systemKey = AVK_TABMENUX_1;
			break;
		case TOUCH_FUNC_TABMENUX_2:
			systemKey = AVK_TABMENUX_2;
			break;
		case TOUCH_FUNC_TABMENUX_3:
			systemKey = AVK_TABMENUX_3;
			break;

		case TOUCH_FUNC_ITEM_UPGRADE:
			systemKey = AVK_UPGRADE;
			break;
		case TOUCH_FUNC_ITEM_HAMMER:
			systemKey = AVK_HAMMER;
			break;
		case TOUCH_FUNC_SKILL_UPGRADE:
			systemKey = AVK_SKILLUPGRADE;
			break;
		case TOUCH_FUNC_INGAME_AUTO:
			systemKey = AVK_AUTO;
			break;
		case TOUCH_FUNC_INGAME_AUTOOFF:
			systemKey = AVK_AUTOOFF;
			break;
			//#endif
		case TOUCH_FUNC_INGAME_VOICEOFF:
			systemKey = AVK_OPTION_VOICE;
			break;
		case TOUCH_FUNC_INGAME_RESULTSKIP_TOP10:
		case TOUCH_FUNC_INGAME_RESULTSKIP_MY:
		case TOUCH_FUNC_INGAME_OUTGAME:
			systemKey = AVK_CLR;
			break;
		case TOUCH_FUNC_INGAME_MOVE:

			break;
		case TOUCH_FUNC_USE_HEART:
			systemKey = AVK_HEART;
			break;
		case TOUCH_FUNC_ROULETTESTART:
			systemKey = AVK_ROULETTESTART;
			break;
		case TOUCH_FUNC_HEARTAMOUNT:
			systemKey = AVK_HEARTAMOUNT;
			break;
		case TOUCH_FUNC_COINAMOUNT:
			systemKey = AVK_COINAMOUNT;
			break;
		case TOUCH_FUNC_TARGETENEMY:
			systemKey = AVK_TARGETENEMY;
			break;
		case TOUCH_FUNC_TARGETENEMY2:
			systemKey = AVK_TARGETENEMY2;
			break;
		case TOUCH_FUNC_TARGETENEMY3:
			systemKey = AVK_TARGETENEMY3;
			break;
		case TOUCH_FUNC_TARGETENEMY4:
			systemKey = AVK_TARGETENEMY4;
			break;
		case TOUCH_FUNC_TARGETENEMY5:
			systemKey = AVK_TARGETENEMY5;
			break;
		case TOUCH_FUNC_ATTACK:
			systemKey = AVK_ATTACK;
			break;
		case TOUCH_FUNC_HEROCHECK_DIANA:
			systemKey = AVK_HEROCHECK_DIANA;
			break;
		case TOUCH_FUNC_HEROCHECK_MAXX:
			systemKey = AVK_HEROCHECK_MAXX;
			break;

		case TOUCH_FUNC_CREWCHECK_1:
			systemKey = AVK_CREWCHECK_1;
			break;
		case TOUCH_FUNC_CREWCHECK_2:
			systemKey = AVK_CREWCHECK_2;
			break;
		case TOUCH_FUNC_CREWCHECK_3:
			systemKey = AVK_CREWCHECK_3;
			break;

		case TOUCH_FUNC_INGAME_CLOSEWINDOW:
			systemKey = AVK_CLR;
			break;
		case TOUCH_FUNC_CHARINFOPAGE:
			j = 0;
			for (i = 0; i < TOTALMENUOPTION; i++) {
				if (Abs(ao[menuCur].ps[optionInfo[i * 2]]) > 0)
					j++;
			}

			if (charInfoPage * CHARINFOPAGELINE < j / CHARINFOPAGELINE)
				charInfoPage++;
			else
				charInfoPage = 0;
			PlayMusic(M_BUTTON);
			break;
		case TOUCH_FUNC_DEBUG_RESETGAME:
			systemKey = AVK_NEWGAME;

			break;
		case TOUCH_FUNC_DEBUG_MAXSTATUS:
			systemKey = AVK_MAXGAME;
			break;
		case TOUCH_FUNC_DEBUG_ENEMYATTACK:
			systemKey = AVK_ENEMYATTACK;
			break;

		case TOUCH_FUNC_DEBUG_CHANGEMODE:
			if (option.gameControl == CONTROL_AUTO)
				option.gameControl = CONTROL_AI;
			else if (option.gameControl == CONTROL_AI)
				option.gameControl = CONTROL_AUTO;

			SaveOption();
			break;
		case TOUCH_FUNC_DEBUG_STARTFROMONEPLAYER:
			option.gameMode = ++option.gameMode % 2;
			SaveOption();
			break;
		case TOUCH_FUNC_DEBUG_CUTOFF:
			option.cutOff = ++option.cutOff % 3;
			SaveOption();
			break;
		case TOUCH_FUNC_DEBUG_HEADZOOM:
			playerHeadZoom = ++playerHeadZoom % 3;
			break;
		case TOUCH_FUNC_DEBUG_EFFECTONLYPLAYER:
			if (effectOnlyPlayer == true)
				effectOnlyPlayer = false;
			else
				effectOnlyPlayer = true;
			break;
		case TOUCH_FUNC_DEBUG_PLAYERDMGNUMBIG:
			if (onlyPlayerDmgNumBig == true)
				onlyPlayerDmgNumBig = false;
			else
				onlyPlayerDmgNumBig = true;
			break;
		case TOUCH_FUNC_DEBUG_GAMESPEED:
			Director::getInstance()->setAnimationInterval(1.0f / option.gameSpeed);
			SaveOption();
			break;
		case TOUCH_FUNC_CLOSEALERT:
			systemKey = AVK_CLR;
			break;

		case TOUCH_FUNC_GOTOGACHA:
			systemKey = AVK_GOTOGACHA;
			break;

		case TOUCH_FUNC_OUTOFMINIGACHA:
			systemKey = AVK_CLR;
			break;
		case TOUCH_FUNC_OUTOFBATTLERESULT:
			systemKey = AVK_OUTOFBATTLERESLUT;
			break;
		case TOUCH_FUNC_OUTOFRAIDRESULT:
			systemKey = AVK_OUTOFRAIDRESULT;
			break;

		case TOUCH_FUNC_RAID_RANKING1:
		case TOUCH_FUNC_RAID_RANKING2:
		case TOUCH_FUNC_RAID_RANKING3:
			raidPlayer = (func - TOUCH_FUNC_RAID_RANKING1);
			PlayMusic(M_BUTTON);
			break;
		case TOUCH_ALERT_INVENTORYFULL_YES:
			systemKey = AVK_SELECT;
			break;
		case TOUCH_ALERT_INVENTORYFULL_NO:
			systemKey = AVK_CLR;
			break;
		case TOUCH_ALERT_ITEMSELL:
			systemKey = AVK_SELLITEM;
			break;
		case TOUCH_ALERT_NO:
			systemKey = AVK_CLR;
			break;
		case TOUCH_ATTACK_REWARD:
			systemKey = AVK_ATTACK_REWARD;
			break;
		case TOUCH_HIT_REWARD:
			systemKey = AVK_HIT_REWARD;
			break;
		case TOUCH_RAID_REWARD:
			systemKey = AVK_RAID_REWARD;
			break;
		case TOUCH_FUNC_SKIPDEMO:
			systemKey = AVK_DEMOSKIP;
			break;

		case TOUCH_FUNC_GOTODEMO:
			systemKey = AVK_GOTODEMO;

			break;
		case TOUCH_FUNC_GOTOPLAY:
			systemKey = AVK_GOTOPLAY;
			break;
		case TOUCH_FUNC_GOTOBOSSRAID:
			systemKey = AVK_GOTOBOSSRAID;
			break;
		case TOUCH_FUNC_GOTOBATTLE:
			systemKey = AVK_GOTOBATTLE;
			break;
		case TOUCH_FUNC_GOTONEWCARD:
			systemKey = AVK_GOTONEWCARD;
			break;
		case TOUCH_FUNC_GOTOHOUSE:
			systemKey = AVK_GOTOHOUSE;
			break;
		case TOUCH_FUNC_GOTOSHOP:
			systemKey = AVK_GOTOSHOP;
			break;
		case TOUCH_FUNC_DAILYQUEST:
			systemKey = AVK_DAILYQUEST;
			break;
		case TOUCH_FUNC_OUTOFHOUSE:
			systemKey = AVK_OUTOFHOUSE;
			break;
		case TOUCH_FUNC_OUTOFNEWCARD:
			systemKey = AVK_OUTOFNEWCARD;
			break;
		case TOUCH_FUNC_OUTOFBOSS:
			systemKey = AVK_OUTOFBOSS;
			break;
		case TOUCH_FUNC_GETREWARDSTART:
			systemKey = AVK_GETREWARDSTART;
			break;
		case TOUCH_FUNC_NEXTREWARD:
			systemKey = AVK_NEXTREWARD;
			break;

		case TOUCH_FUNC_NEWDEMOITEMREWARD:
			systemKey = AVK_NEWDEMOITEMREWARD;
			break;
		case TOUCH_FUNC_GETDEMOREWARD:
			systemKey = AVK_GETDEMOREWARD;
			break;

		case TOUCH_FUNC_NEWCOLLECTIONREWARDGET:
			systemKey = AVK_NEWCOLLECTIONREWARDGET;
			break;
		case TOUCH_FUNC_NEWCARDREWARDGET:
			systemKey = AVK_NEWCARDREWARDGET;
			break;

		case TOUCH_FUNC_GETGACHACARD:
			systemKey = AVK_GETGACHACARD;
			break;
		case TOUCH_FUNC_GETRAIDGOLD:
			systemKey = AVK_GETRAIDGOLD;
			break;
		case TOUCH_FUNC_POPUP_HOWTOGETHEROES:
			systemKey = AVK_POPUP_HOWTOGETHEROES;
			break;
		case TOUCH_FUNC_POPUP_HOWTOGETCREWS:
			systemKey = AVK_POPUP_HOWTOGETCREWS;
			break;
		case TOUCH_FUNC_POPUP_LVUPREWARD:
			systemKey = AVK_POPUP_LVUPREWARD;
			break;
		case TOUCH_FUNC_POPUP_STAGEREWARD:
			systemKey = AVK_POPUP_STAGEREWARD;
			break;
		case TOUCH_FUNC_POPUP_HEROSTAT:
		case TOUCH_FUNC_POPUP_HEROSTAT + 1:
		case TOUCH_FUNC_POPUP_HEROSTAT + 2:
			systemKey = AVK_POPUP_HEROSTAT + func - TOUCH_FUNC_POPUP_HEROSTAT;
			break;
		case TOUCH_FUNC_SELECT_HERO:
		case TOUCH_FUNC_SELECT_HERO + 1:
		case TOUCH_FUNC_SELECT_HERO + 2:
			systemKey = AVK_SELECT_HERO + func - TOUCH_FUNC_SELECT_HERO;
			break;
		case TOUCH_FUNC_POPUP_CREWUPGRADE:
			systemKey = AVK_POPUP_CREWUPGRADE;
			break;
		case TOUCH_FUNC_POPUP_CREWLIST:
			systemKey = AVK_POPUP_CREWLIST;
			break;
		case TOUCH_FUNC_POPUP_CLOSE:
			systemKey = AVK_POPUP_CLOSE;
			break;

		case TOUCH_FUNC_JOKBO:
			systemKey = AVK_JOKBO;
			break;
		case TOUCH_FUNC_GETCREW:
			systemKey = AVK_GETCREW;
			break;
		case TOUCH_FUNC_STAGEREWARD:
			systemKey = AVK_STAGEREWARD;
			break;
		case TOUCH_FUNC_STAGEFAILED:
			systemKey = AVK_STAGEFAILED;
			break;
		case TOUCH_FUNC_NEWSTAGE:
			systemKey = AVK_NEWSTAGE;
			break;
		case TOUCH_FUNC_SHOP_BUYBOX1:
		case TOUCH_FUNC_SHOP_BUYBOX2:
		case TOUCH_FUNC_SHOP_BUYBOX3:
			systemKey = AVK_SHOP_BUYBOX1 + func - TOUCH_FUNC_SHOP_BUYBOX1;
			break;
		case TOUCH_FUNC_HOTKEYPRESS1:
		case TOUCH_FUNC_HOTKEYPRESS2:
		case TOUCH_FUNC_HOTKEYPRESS3:
			systemKey = AVK_HOTKEYPRESS1 + func - TOUCH_FUNC_HOTKEYPRESS1;
			break;
		}
	}
}

void SaveFlag(int which)
{
	saveFlag[which] = true;
}


// JoyStick 관련

bool JoyStickPressGoldQuestPossible(void)
{
	int i;
	int controlMarkActiveCnt = 0;

	for (i = 0; i < TOTALCONTROLMARK; i++) {
		if (controlMark[i].frame > 0)
			return false;
	}

	if (((autoPlay == false && turn == NEUTRAL && !curtainFrame && ao[ENEMY].dead == false && ao[ENEMY].active == true && ao[ENEMY].moveHandler != VANISHMOVE && attackSequence == false) || autoPlay == true) && infoFrame == 0 && areaFrame == 0 && attackSequence == ATTACKSEQUENCE_READY && arenaStatus == STATUS_PLAY)
		return true;
	else
		return false;
}

bool JoyStickPressRaidPossible(void)
{
	if (autoPlay == false && raidChance > 0 && turn == NEUTRAL && !curtainFrame && ao[ENEMY].dead == false && ao[ENEMY].active == true && attackSequence == ATTACKSEQUENCE_READY && arenaStatus == STATUS_PLAY)
		return true;
	else
		return false;
}

bool JoyStickPressPossible(void)
{
	int i;
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];

	switch (drawHandle) {
	case MD_PLAY:
	case MD_BATTLE:
		if (((autoPlay == false && !curtainFrame) || autoPlay == true) && infoFrame == 0 && areaFrame == 0 && attackSequence == ATTACKSEQUENCE_READY && arenaStatus == STATUS_PLAY && ao[PLAYER].dead == false && robin.heart >= GetBetHeart(ao[PLAYER].equip[EQUIP_WEAPON].detail, ao[PLAYER].equip[EQUIP_WEAPON].grade, bet))
			return true;
		else
			return false;
		break;
		//레이드는 조이스틱을 안쓴다.
	case MD_RAID:
		if (!curtainFrame && infoFrame == 0 && areaFrame == 0 && initControlerFrame > 1 && attackSequence == ATTACKSEQUENCE_READY && arenaStatus == STATUS_PLAY && raidChance > 0)
			return true;
		else
			return false;
		break;
	}

	return false;
}

bool menuPressPossible(void)
{
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];

	if (!curtainFrame && !infoFrame && !areaFrame && attackSequence == ATTACKSEQUENCE_READY && !ao[PLAYER].dead && arenaStatus == STATUS_PLAY && autoPlay == false) {
		return true;
	}
	else {
		return false;
	}
}

void JoyStickPressRaid(void)
{
	int i, j;
	int rand;
	int bigger = false;
	OBJECT* pObj = &ao[PLAYER];

	if (attackDelay)
		return;

	//하트는 하지 않고
	if (raidChance > 0 && turn == NEUTRAL) {
		raidChance--;

		//ROULETTE_COIN = 0,//검//일반 데미지 //1, 2, 5배//
		//ROULETTE_BATTLE,//글로브//연타 데미지 //1, 2, 4배 연타//
		//ROULETTE_EQUIP,//헬멧//3개가 다 같으면 크리티컬 데미지//헬멧값만큼 10배에서 시작//
		//ROULETTE_HEART,//갑옷//3개가 다 같으면 하트//
		//ROULETTE_QUEST,//하의//퀘스트 아이템 획득//1, 2, 5배//
		//ROULETTE_RAID,//신발//적과 전투//골드 1, 2, 5배//

		//actionCardArr[0] = ROULETTE_COIN;
		//actionCardArr[1] = ROULETTE_COIN;
		//actionCardArr[2] = ROULETTE_COIN;

		if (ao[pObj->target].gold == 0) {
			attackType = ROULETTE_RAID_MISS;
		}
		else if (ao[pObj->target].gold > ao[ENEMYUSEROBJ].gold * GetBetHeart(ao[PLAYER].equip[EQUIP_WEAPON].detail, ao[PLAYER].equip[EQUIP_WEAPON].grade, bet) / 2) {

			attackType = ROULETTE_RAID_PERFECT;
		}
		else {
			attackType = ROULETTE_RAID_GOOD;
		}

		attackStr = 0;

		sequenceFrame = 0;
		attackSequence = ATTACKSEQUENCE_READY;
		rouletteNum = 0;
		rouletteNumSub = 0;
		rouletteNumBar = 0;
		rouletteNumPvpBar = 0;

		option.gameControl = CONTROL_AUTO;
		turn = PLAYER;
		turnFrame = 0;
		pObj->turnPosition = GOING;
		joyStickAni = 0;

		pObj->superJump = 2;
		pObj->jumpTwice = true;
		pObj->jumpFrame = -4;
		effect.shake = 4;


		PlayMusic(M_SHAKIN);
	}
}
//보스레이드의 경우는 
//1. 보스가 등장하고 
//2. 등장한 보스를 공격하면
//3. 

void BoxOpen(void)
{
	int i, j;
	int itemType, itemDetail, itemGrade, itemLv;
	int rand = Random(ITEMDETAILSEED);
	int eventIdx;

	//
	//TEST
	//여기서 상자에서 꺼낼 아이템을 만들어준다.

	GetItem(ITEM_HEART, false, false, false, -1, false);
	AddBar(&bar[BAR_HEART], -betHeart[bet], BARFRAME);

	bar[BAR_ITEM].frame = 0;
	bar[BAR_ITEM].add = 0;
	bar[BAR_ITEM].count = 0;
	bar[BAR_ITEM].countFrame = 0;

	for (i = 0; i < TOTAL_BOXDROP; i++) {
		if (rand < boxDropProc[bet][i]) {
			boxDropItemType = i;
			break;
		}
	}

	//TEST
	boxDropItemType = BOXDROP_COIN;

	switch (boxDropItemType) {
	case BOXDROP_COIN:
	case BOXDROP_COINBAG:
		attackType = ROULETTE_COIN;
		if (boxDropItemType == BOXDROP_COINBAG)
			attackStr = 1;//5배
		else
			attackStr = 0;//1배

		bar[BAR_GOLD].front = true;
		bar[BAR_INVENTORY].front = false;
		bar[BAR_INVENTORY + 1].front = false;
		bar[BAR_INVENTORY + 2].front = false;
		bar[BAR_COMBATPOWERALL].front = false;

		break;
	case BOXDROP_QUESTITEM:
	case BOXDROP_QUESTITEMBAG:
		attackType = ROULETTE_QUEST;
		if (boxDropItemType == BOXDROP_QUESTITEMBAG)
			attackStr = 2;//5배
		else
			attackStr = 0;//1배

		bar[BAR_INVENTORY].front = false;
		bar[BAR_INVENTORY + 1].front = false;
		bar[BAR_INVENTORY + 2].front = false;

		break;
	case BOXDROP_HEART:
		attackType = ROULETTE_HEART;
		attackStr = HEARTPER;

		bar[BAR_INVENTORY].front = false;
		bar[BAR_INVENTORY + 1].front = false;
		bar[BAR_INVENTORY + 2].front = false;

		break;
	case BOXDROP_EQUIP:
		attackType = ROULETTE_EQUIP;
		itemType = MakeItemType(Random(ITEMTYPESEED));
		//itemType = ITEM_NECK;
		itemDetail = MakeItemDetail(itemType, robin.lv);
		itemGrade = MakeItemGrade(itemType, robin.lv, itemDetail);
		itemLv = MakeItemLevel(itemType, robin.lv);

		MakeItem(&robin.newItem, itemType, itemLv, itemGrade, itemDetail, false);

		bar[BAR_INVENTORY].front = true;
		bar[BAR_INVENTORY + 1].front = true;
		bar[BAR_INVENTORY + 2].front = true;
		break;
	case BOXDROP_BATTLE:
		attackType = ROULETTE_BATTLE;

		bar[BAR_HEART].front = false;
		bar[BAR_QUEST].front = false;
		bar[BAR_COMBATPOWERALL].front = false;
		bar[BAR_INVENTORY].front = false;
		bar[BAR_INVENTORY + 1].front = false;
		bar[BAR_INVENTORY + 2].front = false;

		bar[BAR_ENEMYUSER_BOX].active = true;

		bar[BAR_ENEMYUSER_BOX].x = DX / 2;
		bar[BAR_ENEMYUSER_BOX].y = bar[BAR_HEART].y + 48 * _2X;

		bar[BAR_ENEMYUSER_BOX].front = true;
		bar[BAR_ENEMYUSER_BOX].targetX2 = bar[BAR_ENEMYUSER_BOX].targetX = DX / 2;
		bar[BAR_ENEMYUSER_BOX].targetY = DY / 2;
		bar[BAR_ENEMYUSER_BOX].targetY2 = DY / 2;// DY - GNBHEIGHT - RAIDGOLDBARHEIGHT / 2;// -REWARDCARDSIZE_Y * 3.0f / 2;
		bar[BAR_ENEMYUSER_BOX].speed2 = bar[BAR_ENEMYUSER_BOX].speed = 32 * _2X;
		bar[BAR_ENEMYUSER_BOX].speedIncrement2 = bar[BAR_ENEMYUSER_BOX].speedIncrement = -1 * _2X;

		bar[BAR_ENEMYUSER_BOX].zoom = 0.1f;
		bar[BAR_ENEMYUSER_BOX].zoomIncrement = 0.1f;
		bar[BAR_ENEMYUSER_BOX].zoomEnd = 2.0f;
		bar[BAR_ENEMYUSER_BOX].zoom2 = 2.0f;
		bar[BAR_ENEMYUSER_BOX].zoomIncrement2 = 0.0f;
		bar[BAR_ENEMYUSER_BOX].zoomEnd2 = 2.0f;
		bar[BAR_ENEMYUSER_BOX].frame = 1;
		break;
	case BOXDROP_RAID:
		attackType = ROULETTE_RAID;

		bar[BAR_HEART].front = false;
		bar[BAR_QUEST].front = false;
		bar[BAR_COMBATPOWERALL].front = false;
		bar[BAR_INVENTORY].front = false;
		bar[BAR_INVENTORY + 1].front = false;
		bar[BAR_INVENTORY + 2].front = false;

		bar[BAR_ENEMYUSER_BOX].active = true;

		bar[BAR_ENEMYUSER_BOX].x = DX / 2;
		bar[BAR_ENEMYUSER_BOX].y = bar[BAR_HEART].y + 48 * _2X;

		bar[BAR_ENEMYUSER_BOX].front = true;
		bar[BAR_ENEMYUSER_BOX].targetX2 = bar[BAR_ENEMYUSER_BOX].targetX = DX / 2;
		bar[BAR_ENEMYUSER_BOX].targetY = DY / 2;
		bar[BAR_ENEMYUSER_BOX].targetY2 = DY / 2;// DY - GNBHEIGHT - RAIDGOLDBARHEIGHT / 2;// -REWARDCARDSIZE_Y * 3.0f / 2;
		bar[BAR_ENEMYUSER_BOX].speed2 = bar[BAR_ENEMYUSER_BOX].speed = 32 * _2X;
		bar[BAR_ENEMYUSER_BOX].speedIncrement2 = bar[BAR_ENEMYUSER_BOX].speedIncrement = -1 * _2X;

		bar[BAR_ENEMYUSER_BOX].zoom = 0.1f;
		bar[BAR_ENEMYUSER_BOX].zoomIncrement = 0.1f;
		bar[BAR_ENEMYUSER_BOX].zoomEnd = 2.0f;
		bar[BAR_ENEMYUSER_BOX].zoom2 = 2.0f;
		bar[BAR_ENEMYUSER_BOX].zoomIncrement2 = 0.0f;
		bar[BAR_ENEMYUSER_BOX].zoomEnd2 = 2.0f;
		bar[BAR_ENEMYUSER_BOX].frame = 1;

		raidChance = TOTALRAIDCHANCE;
		break;
	case BOXDROP_SHIELD:
		attackType = ROULETTE_SHIELD;
		attackStr = 0;//1배

		bar[BAR_INVENTORY].front = false;
		bar[BAR_INVENTORY + 1].front = false;
		bar[BAR_INVENTORY + 2].front = false;
		bar[BAR_COMBATPOWERALL].front = false;
		bar[BAR_QUEST].front = false;
		break;
	}

	attackSequence = ATTACKSEQUENCE_ATTACKRESULT;// ATTACKSEQUENCE_ROULETTE;
	sequenceDelay = attackDelayPerType[attackType];
	ao[ITEMBOX].status = BOXSTATUS_OPENING;
	ao[ITEMBOX].frame = 0;
	ao[ITEMBOX].attacked = true;
	ao[ITEMBOX].attackedFrame = BOXATTACKEDFRAME;
#ifdef ATTACKEDINVINCIBLE
	ao[ITEMBOX].invincible = ATTACKEDFRAME;
#endif	

	rouletteNum = 0;
	rouletteNumSub = 0;
	rouletteNumBar = 0;
	rouletteNumPvpBar = 0;

	subAttackType = -1;

	subAttackStr = 0;

	SaveGame();


}

void JoyStickPressAll(void)
{
	int i, j;

	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	int collectionIdx = GetCollectionIdx(it->type, it->detail, it->grade);

	totalRouletteCnt = Min(MAXROULETTE - actionCardCnt, robin.heart / GetBetHeart(it->detail, it->grade, bet));

}

void JoyStickRelease(void)
{
	int i, j, rand;
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	//자동이면
	if (autoPlay == true) {
		if (robin.heart >= GetBetHeart(it->detail, it->grade, bet)) {

			joyStickDir = RIGHT;
			joyStickAni = 0;
			BoxOpen();
		}
		else {
			joyStickDir = LEFT;
			autoPlay = false;
			autoFrame = -1;
		}

	}
	else {
		joyStickDir = LEFT;
		autoPlay = false;
		autoFrame = -1;
	}

	turnFrame = 0;
	turnPosition = HERE;


}

int GetBetHeart(int itemDetail, int itemGrade, int betGrade)
{
	return betHeart[betGrade];
	//return swordHeart[itemDetail * TOTALGRADE + itemGrade] * betHeart[betGrade];
}

int GetBetGold(int itemDetail, int itemGrade)
{
	return swordGold[itemDetail * TOTALGRADE + itemGrade];
	//return betHeart[bet];
}

int printCoords() {
	int radius = 0; // 초기 반경

	int centerX = 0; // 중심점 x 좌표
	int centerY = 0; // 중심점 y 좌표

	double angle = 0; // 회전 각도
	double angleIncrement = (float)0.3f; // 각도 증가량

	for (int i = 0; i < MAX_POINTS; ++i) {
		// 반경이 256 이상인 경우 반경을 고정하고 계속 회전
		if (radius >= MAX_RADIUS) {
			radius = MAX_RADIUS;
		}

		// 좌표 계산
		int x = centerX + static_cast<int>(radius * std::cos(angle));
		int y = centerY + static_cast<int>(radius * std::sin(angle));

		// 좌표를 배열에 저장
		points[i][0] = x;
		points[i][1] = y;

		// 각도 증가
		angle += angleIncrement;

		// 반경 증가
		radius += (float)(3 * _2X) / MOTIONDIV;

		// 각도를 360도로 유지
		if (angle >= 2 * M_PI) {
			angle -= 2 * M_PI;
		}
	}

	return 0;
}

int printBoxCoords() {
	int radius = 0; // 초기 반경

	int centerX = 0; // 중심점 x 좌표
	int centerY = 0; // 중심점 y 좌표

	double angle = 0; // 회전 각도
	double angleIncrement = (float)0.3f; // 각도 증가량

	for (int i = 0; i < MAX_POINTS; ++i) {

		// 좌표 계산
		int x = centerX + static_cast<int>(radius * std::cos(angle));
		int y = centerY + static_cast<int>(radius * std::sin(angle));

		// 좌표를 배열에 저장
		boxPoints[i][0] = x;
		boxPoints[i][1] = y;

		// 각도 증가
		angle += angleIncrement;

		// 반경 증가
		radius += (float)(2 * _2X) / MOTIONDIV;

		// 각도를 360도로 유지
		if (radius >= 48 * _2X) {
			radius = 48 * _2X;
		}
	}

	return 0;
}

//이 함수는 터치된 영역이 이 에어리어와 같은지 확인하는것
//touchX, touchY 전역 변수에 터치된 영역을 넣고
//이 지역이 현재 설정하고자 하는 영역속에 포함되는지 확인하는 함수

bool rectContainsTouchPoint(int x, int y, int w, int h)
{
	return (touchX >= x) &&
		(touchY <= y) &&
		(touchX <= x + w) &&
		(touchY >= y - h);
}