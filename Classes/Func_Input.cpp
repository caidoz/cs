#include "Core.h"
#include "Func.h"
#include "Data.h"
#include "Text.h"

// KeyPress

//인벤토리에서 찾아 장비시킨다.
//GetInvenIdx()는 못 찾으면 -1을 돌려주는데, 그대로 &robin.inven[-1]을 넘기면
//배열 밖을 읽고 EquipItem()이 그 쓰레기값으로 슬롯을 골라 엉뚱한 곳에 써버린다.
//인벤에 없는 아이템을 장비시키려 할 때 실제로 그렇게 된다.
static void EquipInvenItem(OBJECT* pObj, int type, int detail, int grade)
{
	int idx = GetInvenIdx(type, detail, grade);

	if (idx < 0)
		return;

	EquipItem(pObj, &robin.inven[idx]);
}

//하트 베팅을 한 칸 올린다. 하트가 모자라면 처음으로 돌아간다.
//일반 플레이(AVK_HEARTAMOUNT)와 튜토리얼 대사 중 누르는 경로가 같은 동작을 해야 해서 따로 뺐다.
void RaiseHeartBet(void)
{
	if (robin.heart > betHeart[bet + 1])
		bet = (bet + 1) % MAXBET;
	else
		bet = 0;

	//튜토리얼: 베팅을 배우는 구간(HEARTBET 봄 ~ ROULETTE 보기 전)에만 무슨 일이 일어났는지 알려준다.
	if (IsTutorialPlaying() && robin.demoSeen[DEMO_TUTORIAL_HEARTBET] && !robin.demoSeen[DEMO_TUTORIAL_ROULETTE])
		AddSimpleLog(LOGICON_ICON, ICON_HEART, 0, 0, TEXT_TUTORIAL_BETUP);
}

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
	int i, j, k;
	switch (curMenu) {
	case MENU_LOADING://�� ó���� 100 ������ ȭ�鿬��
		switch (systemKey) {
		case AVK_5:
			memset(&scY, 0, sizeof(scY));

			PlayMusic(M_SELECT);
			break;
		case AVK_MAXGAME:

			int stage;
			int questIcon;

			//TEST
			stage = robin.stage;
			robin.maxStatusCnt = ++robin.maxStatusCnt % TOTAL_SWORD;
			i = robin.maxStatusCnt;
			NewGame();

			robin.castle = 18;

			//SetRoom_Neutral();

			robin.stage = stage;
			robin.maxStatusCnt = i;

			option.gameControl = CONTROL_MANUAL;

			AddBar(&bar[BAR_GOLD], 10000000, BARFRAME);
			GetItem(ITEM_GOLD, false, false, false, 10000000, false);
			AddBar(&bar[BAR_HEART], 9999, BARFRAME);
			GetItem(ITEM_HEART, false, false, false, 9999, false);
			AddBar(&bar[BAR_HAMMER], 9999, BARFRAME);
			GetItem(ITEM_HAMMER, false, false, false, 9999, false);
			//robin.gold = 10000000;//코인
			//robin.medal = 100000;//PVP 아이템
			//robin.coin = 100000;//코인
			//robin.star = 100000;//��Ÿ(�ռ���)
			//robin.hammer = 100000;//합성석
			//robin.heart = 9999;

			for (i = ROBIN; i < 1; i++) {
				for (j = 0; j < TOTALEQUIP; j++) {
					ao[i].equip[j].type = EMPTY;
					for (k = 0; k < 12; k++)
						ao[i].equip[i].option[j][0] = EMPTYINT;
					for (k = 0; k < 6; k++)
						ao[i].equip[i].socket[j] = EMPTYINT;
				}
			}

			EquipInvenItem(&ao[ROBIN], ITEM_SWORD, ITEM_SWORD_CALADBOLG, GRADE_NORMAL);
			EquipInvenItem(&ao[ROBIN], ITEM_HELM, ITEM_HELM_TITANIUM, GRADE_NORMAL);
			EquipInvenItem(&ao[ROBIN], ITEM_ARMOR, ITEM_ARMOR_DRAGONSKIN, GRADE_NORMAL);
			EquipInvenItem(&ao[ROBIN], ITEM_GUNTLET, ITEM_GUNTLET_HOLYHAND, GRADE_NORMAL);
			EquipInvenItem(&ao[ROBIN], ITEM_KILT, ITEM_KILT_EARTHQUAKE, GRADE_NORMAL);
			EquipInvenItem(&ao[ROBIN], ITEM_GREAVES, ITEM_GREAVES_LEGEND, GRADE_NORMAL);

			//EquipItem(&ao[ROBIN].equip[EQUIP_WEAPON], ITEM_SWORD, 1, GRADE_NORMAL, ITEM_SWORD_KING, 0);
			//MakeItem(&ao[ROBIN].equip[EQUIP_HELM], ITEM_HELM, 1, GRADE_NORMAL, ITEM_HELM_TITANIUM, 0);
			//MakeItem(&ao[ROBIN].equip[EQUIP_ARMOR], ITEM_ARMOR, 1, GRADE_NORMAL, ITEM_ARMOR_DRAGONSKIN, 0);
			//MakeItem(&ao[ROBIN].equip[EQUIP_PANTS], ITEM_KILT, 1, GRADE_NORMAL, ITEM_KILT_EARTHQUAKE, 0);
			//MakeItem(&ao[ROBIN].equip[EQUIP_GLOVE], ITEM_GUNTLET, 1, GRADE_NORMAL, ITEM_GUNTLET_HOLYHAND, 0);
			//MakeItem(&ao[ROBIN].equip[EQUIP_BOOTS], ITEM_GREAVES, 1, GRADE_NORMAL, ITEM_GREAVES_LEGEND, 0);
			//MakeItem(&ao[ROBIN].equip[EQUIP_NECK], ITEM_NECK, 1, GRADE_NORMAL, robin.maxStatusCnt % TOTAL_NECK, 0);
			//MakeItem(&ao[ROBIN].equip[EQUIP_RING], ITEM_RING, 1, GRADE_NORMAL, robin.maxStatusCnt % TOTAL_RING, 0);

			RefreshStat(&ao[ROBIN]);

			//MakeItem(&ao[DIANA].equip[EQUIP_WEAPON], ITEM_GUN, 1, GRADE_NORMAL, ITEM_GUN_INFERNO, 0);
			//MakeItem(&ao[DIANA].equip[EQUIP_HELM], ITEM_HAT, 1, GRADE_NORMAL, ITEM_HAT_DRAGONSKULL, 0);
			//MakeItem(&ao[DIANA].equip[EQUIP_ARMOR], ITEM_VEST, 1, GRADE_NORMAL, ITEM_VEST_QUEEN, 0);
			//MakeItem(&ao[DIANA].equip[EQUIP_PANTS], ITEM_SKIRT, 1, GRADE_NORMAL, ITEM_SKIRT_HERO, 0);
			//MakeItem(&ao[DIANA].equip[EQUIP_GLOVE], ITEM_ARMLET, 1, GRADE_NORMAL, ITEM_ARMLET_HERO, 0);
			//MakeItem(&ao[DIANA].equip[EQUIP_BOOTS], ITEM_SHOES, 1, GRADE_NORMAL, ITEM_SHOES_HEAVENS, 0);
			//MakeItem(&ao[DIANA].equip[EQUIP_NECK], ITEM_NECK, 1, GRADE_NORMAL, robin.maxStatusCnt % TOTAL_NECK, 0);
			//MakeItem(&ao[DIANA].equip[EQUIP_RING], ITEM_RING, 1, GRADE_NORMAL, robin.maxStatusCnt % TOTAL_RING, 0);

			//RefreshStat(&ao[DIANA]);

			//MakeItem(&ao[MAXX].equip[EQUIP_WEAPON], ITEM_BOOMERANG, 1, GRADE_NORMAL, ITEM_BOOMERANG_MEGATRIAL, 0);
			//MakeItem(&ao[MAXX].equip[EQUIP_HELM], ITEM_CAP, 1, GRADE_NORMAL, ITEM_CAP_TROLLHEAD, 0);
			//MakeItem(&ao[MAXX].equip[EQUIP_ARMOR], ITEM_COAT, 1, GRADE_NORMAL, ITEM_COAT_HYDRASCALE, 0);
			//MakeItem(&ao[MAXX].equip[EQUIP_PANTS], ITEM_PANTS, 1, GRADE_NORMAL, ITEM_PANTS_SATANIC, 0);
			//MakeItem(&ao[MAXX].equip[EQUIP_GLOVE], ITEM_GLOVE, 1, GRADE_NORMAL, ITEM_GLOVE_GLORY, 0);
			//MakeItem(&ao[MAXX].equip[EQUIP_BOOTS], ITEM_BOOTS, 1, GRADE_NORMAL, ITEM_BOOTS_DESTINY, 0);
			//MakeItem(&ao[MAXX].equip[EQUIP_NECK], ITEM_NECK, 1, GRADE_NORMAL, robin.maxStatusCnt % TOTAL_NECK, 0);
			//MakeItem(&ao[MAXX].equip[EQUIP_RING], ITEM_RING, 1, GRADE_NORMAL, robin.maxStatusCnt % TOTAL_RING, 0);

			//RefreshStat(&ao[MAXX]);
			//for (i = 0; i < COLLECTIONSITEMCNT; i++) {
			//	EquipItem(&ao[PLAYER], GetInvenIdx(collectionData[robin.maxStatusCnt * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 0], collectionData[robin.maxStatusCnt * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 1], collectionData[robin.maxStatusCnt * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 2]));
			//}

			//GetItem(ITEM_NECK, 0, robin.maxStatusCnt % TOTAL_NECK, false, 1, false);
			//EquipItem(&ao[PLAYER], robin.count);

			//GetItem(ITEM_RING, 0, robin.maxStatusCnt % TOTAL_RING, false, 1, false);
			//EquipItem(&ao[PLAYER], i);

			//TEST
			//TEST
			//���⼭ ��ų����
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

			robin.lv = 11;
			robin.exps = 1000;
			LevelUp(robin.exps);

			//======================================================================
			//TEST : ?�료 ?�별 룰렛/??진행 ?�인???�팅
			//
			//NewGame()??robin.slotCrew[0] = NPC_SEBASTIAN???�어?�기 ?�문?? 먼�? ?��?
			//비워??"?�어�??�자" ?�태�?만들 ???�다.
			//?�래 블록 �??�인?�고 ?��? �??�나�?주석???��??�머지??주석 처리?�다.
			//crewCnt????�� GetSlotCrewCnt()�?slotCrew[]?�서 ?�시 ?��?�?직접 ?�?�하지 ?�는??
			//
			//  0�?: 룰렛 ?�이 ATTACKSEQUENCE_ACTION 직행(?�어로만 공격)
			//  1~5�?: 룰렛?� ?�되 ?�는 릴�? ?�물??-1), 중복 ?�이 뽑히므�???�� 1?�벨 ?�킬
			//  6�?: ?�식 룰렛(중복 발생 -> 2/3매치 ?�킬 강화 ?�출)
			//======================================================================
			for (i = 0; i < MAXCREW; i++)
				robin.slotCrew[i] = -1;

			//--- 0�?: ?�어�??�자 -------------------------------------------------
			//(slotCrew�??��? -1�?비워?????�태가 그�?�?0명이??

			//--- 1�?---------------------------------------------------------------
			//robin.slotCrew[0] = NPC_SEBASTIAN;

			//--- 2�?---------------------------------------------------------------
			//robin.slotCrew[0] = NPC_SEBASTIAN;
			//robin.slotCrew[1] = NPC_GIRL;

			//--- 3�?---------------------------------------------------------------
			//robin.slotCrew[0] = NPC_SEBASTIAN;
			//robin.slotCrew[1] = NPC_GIRL;
			//robin.slotCrew[2] = NPC_UNCLE;

			//--- 4�?---------------------------------------------------------------
			//robin.slotCrew[0] = NPC_SEBASTIAN;
			//robin.slotCrew[1] = NPC_GIRL;
			//robin.slotCrew[2] = NPC_UNCLE;
			//robin.slotCrew[3] = NPC_AUNT;

			//--- 5�?---------------------------------------------------------------
			//robin.slotCrew[0] = NPC_SEBASTIAN;
			//robin.slotCrew[1] = NPC_GIRL;
			//robin.slotCrew[2] = NPC_UNCLE;
			//robin.slotCrew[3] = NPC_AUNT;
			//robin.slotCrew[4] = NPC_ADELKNIGHT;

			//--- 6�?: ?�식 룰렛 ---------------------------------------------------
			robin.slotCrew[0] = NPC_SEBASTIAN;
			robin.slotCrew[1] = NPC_GIRL;
			robin.slotCrew[2] = NPC_UNCLE;
			robin.slotCrew[3] = NPC_AUNT;
			robin.slotCrew[4] = NPC_ADELKNIGHT;
			robin.slotCrew[5] = NPC_NOBLEMAN;

			crewCnt = GetSlotCrewCnt();

			
			//동료를 전부 획득 상태로 만든다(lv 0이 미획득이라 "?"로 보인다).
			//인벤 앞쪽 TOTAL_CREW칸이 동료라는 보장은 NewGame() 직후에만 성립하고,
			//그 뒤 장비/아이템이 들어가면 배치가 달라진다. 그래서 인덱스가 아니라
			//type으로 찾는다.
			for (i = 0; i < TOTALINVENTORY; i++) {
				if (robin.inven[i].type != ITEM_CREW)
					continue;

				robin.inven[i].count = 1;
				robin.inven[i].lv = 1;
			}

			//SetRoom();
			GotoPlay();

			SaveGame();

			//ao[NEUTRAL].etc = robin.castle;
			ao[NEUTRAL].zoom = BOXCASTLEZOOM * (1.0f + (float)0.05f * robin.castle);
			//SetBox(&ao[ITEMBOX], bet);
			arenaStatus = STATUS_PLAY;

			waveStatus = WAVESTATUS_READY;
			break;
		case AVK_GOTOPLAY:
			GotoPlay();
			break;
		case AVK_NEWGAME:
			NewGame();
			GotoPlay();
			for (i = 0; i < TOTAL_BAR; i++)
				bar[i].active = false;
			SetDemo(0);
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

			//���?�������?�ٺ�����
			if (j == TOTALDEMO) {
				robinmap = false;
			}
			else
				robinmap = demoData[j * 7];

			SetRoom();
			areaFrame = 0;
			SetDemo(DEMO_OPENING_PEACEFUL);
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
	case MENU_POLICY://�������?
		switch (systemKey) {
		case AVK_5:
			PlayMusic(M_SELECT);
			break;
		}
		break;
	}
}

void TalkKey(void)
{
	int i, j;

	switch (drawHandle) {
	case MD_OPENING:
		if (textFrame < textStringLength[textPage - 1])	//만약 프레임이 다 안넘어갔으면
			textFrame = textStringLength[textPage - 1] + 1;
		else if (openingTextPage < OPENING_TOTAL_TEXT - 1) {//만약 프레임은 다 넘어갔는데 페이지가 다 안넘어갔으면
			openingTextPage++;
			SetFrameText(TEXT_OPENING_0_0 + openingTextPage, 512, TEXTLINEPERPAGE, 1.4f);
			//textFrame = 0;
		}
		else {
			textFrame = 0;
			textCurPage = 0;
			openingTextPage = 0;

			robin.castle = 18;
			robinmap = MAP_DIORAMA_TOLEM + castleOrder[robin.castle];

			GotoPlay();

			arenaStatus = STATUS_PLAY;

			AddBar(&bar[BAR_COMBATPOWERALL], GetCombatPowerAll(PLAYER), BARFRAME);
			SetEnemyUser();

			for (i = 0; i < robin.eventCnt; i++) {
				InitEventPos(
					&robin.gameEvent[i],
					GetEventMenuPosX(robin.gameEvent[i].type, EVENT_OPEN),
					GetEventMenuPosY(robin.gameEvent[i].type, EVENT_OPEN),
					GetEventMenuPosX(robin.gameEvent[i].type, EVENT_DOING),
					GetEventMenuPosY(robin.gameEvent[i].type, EVENT_DOING),
					GetEventMenuPosX(robin.gameEvent[i].type, EVENT_DOING),
					GetEventMenuPosY(robin.gameEvent[i].type, EVENT_DOING),
					16 * _2X, -1 * _2X, 1 * _2X, 1 * _2X,
					FPS, FPS,
					false, false, false,
					1.0f, 1.0f, 0.0f,
					1.0f, 1.0f, 0.0f
				);
			}

			bet = 0;
			robin.heart = GetInitHeart();

			maxRouletteCnt = swordSkillCnt[0];
			touchDisable = false;

			for (i = 0; i < EQUIP_NECK; i++) {
				for (j = 0; j < itemTypeCnt[i * TOTALCHAR]; j++) {
					GetItem(i, 1, j, GRADE_NORMAL, 1, false);
				}
			}
		}
		break;
	case MD_DEMO:
		//대사가 떠 있을 때만 넘길 수 있다. 아래에서 movie.type을 MOVIE_MOVE로
		//되돌리는데, 그 뒤에 들어온 탭이 여기로 또 들어오면 movie.start를 한 번 더
		//올려서 데모 장면 하나를 통째로 건너뛴다. 연타하면 "때마침 몬스터가
		//나타났네요!" 다음 장면이 날아가 실전투 핸드오프가 걸리지 않고 멈춘다.
		//keyHandle은 EFFECT_TALK에서 MK_TALK으로 바뀐 뒤 다음 연출까지 그대로라
		//keyHandle만으로는 이 상태를 가릴 수 없다.
		if (movie.type != MOVIE_TALK && movie.type != MOVIE_MENUTALK
			&& movie.type != MOVIE_NARRATION)
			break;

		if (textFrame < textStringLength[textPage - 1])	//만약 프레임이 다 안넘어갔으면
			textFrame = textStringLength[textPage - 1] + 1;
		else {
			//?�터?�티�??�투 ?�토리얼: SEBASTIAN??"공격버튼???�러주세?? ?�?��? ?�는 ?�력?�
			//�?�?공격???�도�??�약?�둔???�행?� WaveControler()???��??�에??.
			//?�전?�는 bar[BAR_PLAY].active�?조건?�로 걸었?�데, ??바는 룰렛 ?�트�??�출??
			//?�나???�점(Func_Roulette.cpp??InitBar(BAR_PLAY))?�야 켜진?? �??�에 ??���?
			//?�약????걸린 �??�?�만 ?�어가??"?�투�??�어?�는???�무??공격?��? ?�는" ?�태가 ?�고,
			//?�버거로 지?�시?�면 �??�이 ?�트로�? ?�나 ?�연???�작?�는 ?�?�밍 ?�이?��???
			//?�력 종류/�??�태?� 무�??�게 ??�� ?�약?�다.
			//안내 대사를 넘긴 것이 그 대사가 지정한 버튼이면, 그 버튼의 동작을 예약한다.
			//지금은 keyHandle이 MK_TALK이라 ReleaseCore()가 여기(TalkKey)로만 보내고,
			//동작을 실제로 수행하는 PlayKey()까지 가지 않는다. 게다가 곧 AfterDemo()가
			//플레이로 전환하면서 입력 상태를 지운다 - 동료 바를 눌러도 메뉴가 안 열리고
			//대사만 끝나던 것이 이 때문이다. 예약해 두면 Play()가 돌아온 뒤 처리한다.
			int talkTouchFunc;

			if (GetTutorialTalkTarget(movie.text, &talkTouchFunc, nullptr)) {
				if (talkTouchFunc == TOUCH_FUNC_ATTACK)
				tutorialAttackPending = true;
				//하트 베팅만은 예약하지 않고 그 자리에서 올린다.
				//예약(tutorialPendingTouchFunc)은 컷씬이 다 끝나 플레이로 돌아왔을 때 처리되는데,
				//베팅은 다음 대사에서 "하트값이 2가 되었네요"라고 짚어줘야 해서 지금 바뀌어야 한다.
				else if (talkTouchFunc == TOUCH_FUNC_HEARTAMOUNT)
					RaiseHeartBet();
				else
					tutorialPendingTouchFunc = talkTouchFunc;
			}

			movie.type = MOVIE_MOVE;
			movie.frame++;
			movie.start++;
		}
		break;
	}
}

void PlayKey(int obj)
{
	int i;
	OBJECT* pObj = &ao[obj];
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	int collectionIdx = GetCollectionIdx(it->type, it->detail, it->grade);

	int type, detail, grade;
	const long long* boxReward;
	int sameRouletteCnt = 1;//����ī�尡 ���� �ִ���
	int sameRouletteStartIdx;//����ī�尡 ��ŸƮ �Ǵ� ����
	int sameRouletteEndIdx;//����ī�尡 ���尡 �Ǵ� ����

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


	int who;

	//�޼��� �ʱ�ȭ : �汸�� ����(�� �濡�� �ƹ��͵� ���� �ʰ� �ִ� �ð�)
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
		battleGold = battleRewardGold[robin.stage];//�̰� �� �������� �޾ƿ;� �ȴ�.

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
		raidGold = raidBox[raidTarget].gold;//�̰� �� �������� �޾ƿ;� �ȴ�.
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
	else if (systemKey >= AVK_ITEMDETAIL && systemKey < AVK_ITEMDETAIL + TOTALINVENTORY) {
		//튜토리얼에서 안내하던 동료 카드를 눌러 상세보기로 들어왔으면 그 단계를 마친 것으로 둔다.
		//스팟라이트/터치제한이 이 플래그를 보고 풀린다.
		if (GetTutorialCrewCardTouchFunc() == TOUCH_FUNC_ITEMDETAIL + (systemKey - AVK_ITEMDETAIL)) {
			robin.demoSeen[DEMO_TUTORIAL_CREWMENU] = true;

			//여기서부터는 상세보기의 장착 버튼을 누르게 하는 2부 안내가 이어받는다.
			SetTutorialCrewStep(TUTORIAL_CREWSTEP_EQUIP);
		}

		tutorialCrewGuide = false;

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
	else if (systemKey >= AVK_CREW_DETAIL && systemKey < AVK_CREW_DETAIL + CAP_CREW) {
		menuDepth = 1;
		menuCur = systemKey - AVK_CREW_DETAIL;
		memset(&ao[NPC], 0, sizeof(OBJECT));
		ao[NPC].type = crewData[menuCur * CREWDATASIZE + CREWDATA_TYPE];
		SetEnemy(&ao[NPC]);

		ao[NPC].cmf = enemyData[crewData[menuCur * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_CMF];
		ao[NPC].moveHandler = CREWMOVE;
		ao[NPC].active = true;
		ao[NPC].x = DX / 2;
		ao[NPC].y = DY / 2;

	}
	else if (systemKey >= AVK_CREW_REWARD && systemKey < AVK_CREW_REWARD + CAP_CREW) {
		//���⼭ ��ȭ�� ȹ������ش�?
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
				targetY = DY - (GNBHEIGHT - GNB_INIT_HEIGHT) - 6 * _2X - ITEMICONSIZE / 2;

				AddBar(&bar[BAR_MEDAL], itemCnt, BARFRAME);
				SetCurrencyMarkArr(startX, startY, targetX, targetY, false, false, 16 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, false, false, CURRENCYWAITINGFRAMEMAX, 0, ICON_MEDAL, 30, itemCnt, CURRENCY_MEDAL, 3.0f, 1.0f, -0.2f / MOTIONDIV, false, false, false, 10, BAR_MEDAL);
				break;
			case ITEM_STAR:
				targetX = bar[BAR_CROWN].x + 6 * _2X + ITEMICONSIZE / 2;
				targetY = DY - (GNBHEIGHT - GNB_INIT_HEIGHT) - 6 * _2X - ITEMICONSIZE / 2;

				AddBar(&bar[BAR_CROWN], itemCnt, BARFRAME);
				SetCurrencyMarkArr(startX, startY, targetX, targetY, false, false, 16 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, false, false, CURRENCYWAITINGFRAMEMAX, 0, ICON_STAR, 30, itemCnt, CURRENCY_STAR, 3.0f, 1.0f, -0.2f / MOTIONDIV, false, false, false, 10, BAR_CROWN);
				break;
			case ITEM_HAMMER:
				targetX = bar[BAR_HAMMER].x + 6 * _2X + ITEMICONSIZE / 2;
				targetY = DY - (GNBHEIGHT - GNB_INIT_HEIGHT) - 6 * _2X - ITEMICONSIZE / 2;

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
				targetY = 1 * ITEMICONSIZE + DY - (GNBHEIGHT - GNB_INIT_HEIGHT);

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
	else if (systemKey >= AVK_MENUCUR_CREWSET && systemKey < AVK_MENUCUR_CREWSET + CAP_CREW) {
		robin.slotCrew[menuCur] = crewData[(systemKey  - AVK_MENUCUR_CREWSET) *CREWDATASIZE + CREWDATA_TYPE];
		SetBattleCrew();//다시 재설정.
	}
	else if (systemKey >= AVK_EQUIP_INVENTORY && systemKey < AVK_EQUIP_INVENTORY + TOTALINVENTORY) {
		switch (robin.inven[systemKey - AVK_EQUIP_INVENTORY].type) {
		case ITEM_CREW:
			robin.slotCrew[menuX] = crewData[robin.inven[systemKey - AVK_EQUIP_INVENTORY].detail * CREWDATASIZE + CREWDATA_TYPE];
			menuDepth--;

			//튜토리얼: 편성칸으로 돌아가 새 동료가 내려앉는 것을 보여준다.
			//SetBattleCrew()는 여기서 부르지 않는다. 지금 부르면 메뉴 뒤에서 성 위 등장 연출이
			//먼저 끝나버려서, 메뉴를 닫았을 때 보여줄 것이 남지 않는다.
			if (tutorialCrewStep == TUTORIAL_CREWSTEP_EQUIP) {
				SetTutorialCrewStep(TUTORIAL_CREWSTEP_SLOTSHOW);
				AddTutorialCrewLog(TEXT_TUTORIAL_CREWSET);
			}
			break;
		default:
			EquipItem(&ao[ROBIN], &robin.inven[systemKey - AVK_EQUIP_INVENTORY]);

			//튜토리얼: 장착했으면 리스트로 돌아가 갑옷 자리에 들어간 것을 보여준다.
			//상세보기에 머물러 있으면 슬롯이 화면에 없어서 보여줄 것이 없다.
			if (tutorialEquipStep == TUTORIAL_EQUIPSTEP_EQUIP) {
				menuDepth--;
				SetTutorialEquipStep(TUTORIAL_EQUIPSTEP_SLOTSHOW);
				AddTutorialEquipLog(TEXT_TUTORIAL_EQUIPSET);
				break;
			}

			//Tutorial: after the player manually equips gear following the EQUIP step's guidance,
			//advance to the next tutorial demo (heart betting explanation).
			//안내가 도는 중이면 여기서 넘기지 않는다. 메뉴를 닫고 성 위 연출까지 끝난 뒤
			//TutorialEquipStepUpdate()가 넘긴다.
			if (tutorialEquipStep == TUTORIAL_EQUIPSTEP_NONE
				&& robinmap == MAP_DIORAMA_TOLEM && !robin.demoSeen[DEMO_TUTORIAL_HEARTBET] && robin.demoSeen[DEMO_TUTORIAL_EQUIP])
				SetDemo(DEMO_TUTORIAL_HEARTBET);
			break;
		}
	}
	else {
		//�⺻ ������
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
			case 1://���뺸������
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
			case 1://���뺸������
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
			//���� ���̽�ƽ�� ���� ��������, �ƴϸ� ���̽�ƽ�� ������ �귿�� ���ư��� ��Ȳ�� ���� �ٸ���.
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
			//환경설정의 "알림 설정" 줄을 누르면 종류별 창을 연다.
			//전체 스위치는 그 창 안에서 끄고 켠다.
			SetPopUp(POPUPTYPE_OPTION_PUSHALARM, xOffset + DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			PlayMusic(M_SELECT);
			break;
		case AVK_OPTION_LANGUAGE:
			SetPopUp(POPUPTYPE_OPTION_LANGUAGE, xOffset + DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			PlayMusic(M_SELECT);
			break;
		case AVK_OPTION_HELP:
			SetPopUp(POPUPTYPE_OPTION_HELP, xOffset + DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			PlayMusic(M_SELECT);
			break;
		case AVK_OPTION_HELP_MAIL:
			//메일 앱을 여는 것은 플랫폼마다 방식이 달라서 여기서는 소리만 낸다.
			//TODO: 안드로이드/iOS 네이티브 호출을 붙여야 한다.
			PlayMusic(M_SELECT);
			break;
		case AVK_OPTION_PUSHALARM_TYPE + 0:
			//전체 스위치. 이것만 끄면 종류와 무관하게 아무것도 안 나간다.
			option.pushAlarm = option.pushAlarm ? 0 : 1;
			SaveOption();
			PlayMusic(M_BUTTON);
			break;
		case AVK_OPTION_PUSHALARM_TYPE + 1:
		case AVK_OPTION_PUSHALARM_TYPE + 2:
		case AVK_OPTION_PUSHALARM_TYPE + 3:
		case AVK_OPTION_PUSHALARM_TYPE + 4:
			{
				//꺼진 것을 비트로 들고 있으므로 뒤집기만 하면 된다.
				int bit = 1 << (systemKey - AVK_OPTION_PUSHALARM_TYPE);

				option.pushAlarmOff ^= bit;
				SaveOption();
				PlayMusic(M_BUTTON);
			}
			break;
		case AVK_OPTION_ACCOUNT:
			menuDepth = 2;
			menuCur = 1;

			PlayMusic(M_SELECT);
			break;
		case AVK_OPTION_LANGUAGE_SELECT + 0:
		case AVK_OPTION_LANGUAGE_SELECT + 1:
		case AVK_OPTION_LANGUAGE_SELECT + 2:
		case AVK_OPTION_LANGUAGE_SELECT + 3:
		case AVK_OPTION_LANGUAGE_SELECT + 4:
		case AVK_OPTION_LANGUAGE_SELECT + 5:
		case AVK_OPTION_LANGUAGE_SELECT + 6:
		case AVK_OPTION_LANGUAGE_SELECT + 7:
		case AVK_OPTION_LANGUAGE_SELECT + 8:
		case AVK_OPTION_LANGUAGE_SELECT + 9:
		case AVK_OPTION_LANGUAGE_SELECT + 10:
		case AVK_OPTION_LANGUAGE_SELECT + 11:
			option.language = (unsigned char)(systemKey - AVK_OPTION_LANGUAGE_SELECT);
			SaveOption();
			PlayMusic(M_BUTTON);
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
					sequenceDelay = ATTACKDELAY_BATTLEREWARD_COIN_GET + 2;
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
				//�ؿ��� �����?���� AVK_CLR�� ����ϸ�? 
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
			//�������̵忡�� �������� ���?
		case AVK_BOSSRAIDOUT:
			attackSequence = ATTACKSEQUENCE_ATTACKRESULT;
			bossRaidMode = false;
			break;
		case AVK_PLAY:

			curMenu = MENU_PLAY;
			menuX = 0;
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
			//���� ����ġ�� ���������ش�.
			sequenceDelay = ATTACKDELAY_EQUIP_SETTING;
			memset(&popUp[popUpCnt - 1], 0, sizeof(POPUP));
			popUpCnt--;
			bar[BAR_QUEST].front = false;
			bar[BAR_COMBATPOWER].front = false;
			break;
		case AVK_ATTACK:
			if (drawHandle == MD_PLAY || drawHandle == MD_DEMO) {
				RouletteAttackStart();
				bar[BAR_PLAY].aniFrame = 1;
				touchDisable = true;
			}
			break;
		case AVK_MOVE:
			break;
		case AVK_JUMP:
			systemKey = AVK_2;
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
		case AVK_UPGRADE:
		case AVK_HAMMER:
			menuDepth = 4;
			menuFrame = 0;
			PlayMusic(M_SELECT);
			break;
			//동료 상세보기의 업그레이드.
			//비용표는 upgradeCostCrew[별-1][현재레벨*2 + (0:조각, 1:골드)]이고,
			//레벨 0은 "아직 안 뽑은 동료"라서 올릴 대상이 아니다.
		case AVK_CREW_LEVELUP:
		{
			ITEM* crewIt = &robin.inven[menuItem];

			if (crewIt->type == ITEM_CREW && CanCrewLevelUp(crewIt)) {
				int crewStar = GetItemStar(ITEM_CREW, crewIt->detail, crewIt->grade);

				crewIt->count -= upgradeCostCrew[crewStar - 1][crewIt->lv * 2 + 0];
				robin.gold -= upgradeCostCrew[crewStar - 1][crewIt->lv * 2 + 1];
				crewIt->lv++;

				//성 위에 서 있는 동료도 바로 새 레벨로 다시 세운다.
				SetBattleCrew();

				winUpgradeFrame = 1;
				PlayMusic(M_LEVELUP);
				SaveGame();
			}
			else
				PlayMusic(M_ERROR);
		}
		break;
		case AVK_SKILLUPGRADE:
			robin.gold -= skillUpgradeGold[menuCur * MAXSKILLLV + ao[PLAYER].skillLv[curSkill]] * GetBetHeart(collectionData[menuCur * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + 0 * COLLECTIONSDATASIZE + 1], collectionData[menuCur * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + 0 * COLLECTIONSDATASIZE + 2], bet);
			winUpgradeFrame = 1;
			break;
		case AVK_GETREWARDSTART:
			sequenceDelay = ATTACKDELAY_REWARD_TABTOCOLLECT + 1;
			break;
			//��í���� ���?�ɰ� ������? GachaKey���� PlayKey�� ó���� �ִϱ� ���⼭ �ϸ� ��.
		case AVK_NEXTREWARD:
			break;
		case AVK_GOTOPLAY:
			GotoPlay();
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

			//����̺��?������ �̵�
			attackSequence = ATTACKSEQUENCE_BOSSRAID;
			sequenceDelay = CURTAINFRAME / CURTAINSPEED + 1;

			bar[BAR_BOX].front = false;
			turn = PLAYER;
			break;
		case AVK_GOTOBATTLE:
			battleStartFrame = BATTLESTARTFRAME;
			touchDisable = true;
			AddBar(&bar[BAR_HEART], -GetStageAdmissionHeart(robin.stage), BARFRAME);
			GotoBattle(); 
			break;
		case AVK_NEWGAME:
			NewGame();

			PlayMusic(M_POWERUP);

			GotoPlay();
			SetDemo(0);
			break;
		case AVK_HEARTAMOUNT:
			RaiseHeartBet();
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
			//��í���� ���� ī�����?�κ��丮�� �־��ش�.
			for (i = 0; i < boxCardItemCnt[gachaIndex]; i++) {
				GetItem(boxCardItem[gachaIndex][i].type, boxCardItem[gachaIndex][i].lv, boxCardItem[gachaIndex][i].detail, boxCardItem[gachaIndex][i].grade, 1, false);

				//튜토리얼에서 장착을 가르치기 전까지는 자동장착하지 않는다(Func_Gacha.cpp 주석 참고).
				if (!(IsTutorialPlaying() && !robin.demoSeen[DEMO_TUTORIAL_EQUIP]))
				SetStrongestEquip(boxCardItem[gachaIndex][i].type, boxCardItem[gachaIndex][i].detail, boxCardItem[gachaIndex][i].grade);
			}

			//���� �÷����� �ϼ��Ǹ� �ϴ� GotoCollection
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

			//TODO: 보상 목록을 되살려야 한다.
			//보상표가 들어 있던 rewardBoxData가 구조체 배열(REWARD_BOX_DATA)로
			//바뀌면서 위 대입이 주석 처리됐는데, 아래에서는 boxReward를 그대로
			//역참조하고 있었다. 초기화도 안 된 포인터라 아무 메모리나 읽는다.
			//지금은 대체할 평면 테이블이 없으므로 빈 목록으로 띄운다.
			//-1은 아래 개수 세기가 쓰던 "빈 칸" 표시값이다.
			itemCnt = 0;

			//���⼭ �˾��� ����ش�?
			//SetPopUp(POPUPTYPE_BOXREWARD, xOffset + (float)(DX / 2 - DIORAMASIZE_X * dioramaZoom / 2) * dioramaZoom + (float)stageEnemyPos[stageHouseType[robin.stage] * TOTALROOM * 3 + (systemKey - AVK_POPUP_STAGEREWARD) * 3 + 0] * dioramaZoom, POPUPPOSITION_Y + (float)POPUPWINDOWSIZE_Y / 2 - (float)(72 * _2X) * dioramaZoom + (float)stageEnemyPos[stageHouseType[robin.stage] * TOTALROOM * 3 + (systemKey - AVK_POPUP_STAGEREWARD) * 3 + 1] * dioramaZoom + 108 * _2X, (REWARDCARDSIZE_X + 4 * _2X) * itemCnt + 4 * _2X, REWARDCARDSIZE_Y + 32 * _2X,
			SetPopUp(POPUPTYPE_BOXREWARD, xOffset + (float)DX / 2, POPUPPOSITION_Y, (REWARDCARDSIZE_X + 4 * _2X) * 3 + 4 * _2X, REWARDCARDSIZE_Y + 32 * _2X,
				ITEM_BOX, rewardBoxDetail, rewardBoxGrade,
				-1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1,
				-1, -1, -1, -1, -1);

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

			SetPopUp(POPUPTYPE_CREWLIST, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
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
			SetPopUp(POPUPTYPE_COLLECTIONS, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_POPUP_CASTLEMENU:
			curMenuBack = curMenu;
			curMenu = MENU_CASTLE;
			menuDepth = 0;
			menuX = 0;
			menuCur = 0;

			SetPopUp(POPUPTYPE_CASTLEMENU, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false,
				false, false, false, false, false);
			break;
		case AVK_POPUP_CLOSE:
			//튜토리얼: 여기서야 성 위에 동료를 실제로 세운다.
			//SetBattleCrew()가 새로 배치되는 슬롯만 REGENMOVE(등장 낙하)로 태우므로,
			//메뉴를 닫는 순간 성 위에 떨어지는 연출이 시작된다.
			if (tutorialCrewStep == TUTORIAL_CREWSTEP_CLOSE) {
				crewCnt = GetSlotCrewCnt();
				SetBattleCrew();
				SetTutorialCrewStep(TUTORIAL_CREWSTEP_CASTLE);
				AddTutorialCrewLog(TEXT_TUTORIAL_CREWJOIN);
			}

			//튜토리얼: 장비는 이미 주인공이 입고 있다. 성으로 돌아가 갈아입은 모습을 보여준다.
			if (tutorialEquipStep == TUTORIAL_EQUIPSTEP_CLOSE) {
				SetTutorialEquipStep(TUTORIAL_EQUIPSTEP_HERO);
				AddTutorialEquipLog(TEXT_TUTORIAL_EQUIPWEAR);
			}

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
			robin.gold -= GetBoxPrice(BOX_REWARD2 + systemKey - AVK_SHOP_BUYBOX1, GRADE_NORMAL);
			memset(&rewardItem, 0, sizeof(rewardItem));
			memset(&rewardMark, 0, sizeof(rewardMark));
			rewardMark[0].type = rewardItem[0].type = ITEM_BOX;
			rewardMark[0].detail = BOX_REWARD2 + systemKey - AVK_SHOP_BUYBOX1;
			rewardMark[0].grade = GRADE_NORMAL;
			rewardItemCnt = 1;
			boxCnt = 0;

			GotoGacha();
			break;
		case AVK_HOTKEYPRESS1:
		case AVK_HOTKEYPRESS2:
		case AVK_HOTKEYPRESS3:
			//���⼭ �ٷ� HotKeyPress�� ��Ʈ���� �����ϴ°� �ƴ϶� ��� ���̽������� �̵��� �� �� �� �տ� ���� ��Ʈ����.
			//
			ao[systemKey - AVK_HOTKEYPRESS1].currentSkill = ao[systemKey - AVK_HOTKEYPRESS1].hotKey[0].idx;

			if (IsMovingSkill(ao[systemKey - AVK_HOTKEYPRESS1].currentSkill) == false)
				HotKeyPress(&ao[systemKey - AVK_HOTKEYPRESS1], 0);

			break;
		case AVK_MENUCUR_CREW1:
		case AVK_MENUCUR_CREW2:
		case AVK_MENUCUR_CREW3:
		case AVK_MENUCUR_CREW4:
		case AVK_MENUCUR_CREW5:
		case AVK_MENUCUR_CREW6:
			menuCur = systemKey - AVK_MENUCUR_CREW1;
			break;
		case AVK_MENUX_1:
		case AVK_MENUX_2:
		case AVK_MENUX_3:
		case AVK_MENUX_4:
		case AVK_MENUX_5:
		case AVK_MENUX_6:
			scY[MENU_COLLECTIONS] = 0;
			menuX = systemKey - AVK_MENUX_1;
			break;
		}
	}
}

void DemoKey(void)
{
	int newItemType;
	int newItemDetail;
	int newItemGrade;

	//아래 if 안에서만 채워진다. 쓰는 곳(AVK_GETDEMOREWARD)이 같은 조건이라
	//실제로 도달하지는 않지만, 컴파일러가 짝을 못 지으니 여기서 잡아둔다.
	int newItemRewardType = 0;
	int newItemRewardDetail = 0;
	int newItemRewardGrade = 0;
	int newItemRewardCnt = 0;

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
				//����Ʈ �Ϸ� �������� �������� ���?
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
//�̵��ؼ� �����ϴ� ��ų
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
		//case SKILL_COMMON_ROBIN9:	//�����ľ� : ũ��Ƽ�� Ȯ�� ���?
		//case SKILL_COMMON_ROBIN10:	//�������� : ũ��Ƽ�� ������ ���?
		//case SKILL_COMMON_ROBIN11:	//뚝심 : 데미지 경감
		//case SKILL_COMMON_ROBIN12:	//정조준 : 명중 증가
		//case SKILL_COMMON_ROBIN13:	//�ż�ȸ�� : ȸ�� ����

		//case SKILL_ROBIN1:	//�˼����� : ���� �߻� Ȯ�� ���?
		//case SKILL_ROBIN2:	//��޹�� : ���?�ߵ� Ȯ���� �ö�(1�����̸� ���?�ߵ��� ����: ���� Ȯ�� ���?
		//case SKILL_ROBIN3:	//������ : ���?�ߵ��� �氨�Ǵ� ������ �ۼ�Ʈ ���?
		//case SKILL_ROBIN4:	//�鿪�� : �����̻� ���� ���׷� ���?
		//case SKILL_ROBIN5:	//지구전 : INT가 높을수록 VIT 상승
		//case SKILL_ROBIN6:	//����ũ���� : �� �ٿ��?
		//case SKILL_ROBIN7:	//마구찌르기 : 난타
		//case SKILL_ROBIN8:	//�ν�Ʈ������ : ���η� ũ�� ���? ��������
		//case SKILL_ROBIN9:	//하이퍼차지 : 돌격공격: 적을 뒤로 날려버림
		//case SKILL_ROBIN10:	//�ҿ�ũ���� : ����
		//case SKILL_ROBIN11:	//앱솔루트피어스 : 찔러서회전
		//case SKILL_ROBIN12:	//��쿬��?: ���ӱ�
		//case SKILL_ROBIN13:	//방어태세 : 일정시간 VIT 상승
		//case SKILL_ROBIN14:	//정신소모 : MP 소모하여 데미지 경감
		//case SKILL_ROBIN15:	//�������� : �� ���� ȸ�ǽ� HP ���?
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
		//case SKILL_COMMON_DIANA9:	//�����ľ� : ũ��Ƽ�� Ȯ�� ���?
		//case SKILL_COMMON_DIANA10:	//�������� : ũ��Ƽ�� ������ ���?
		//case SKILL_COMMON_DIANA11:	//뚝심 : 데미지 경감
		//case SKILL_COMMON_DIANA12:	//정조준 : 명중 증가
		//case SKILL_COMMON_DIANA13:	//�ż�ȸ�� : ȸ�� ����

		//case SKILL_DIANA1:	//���Ǵ� : ���� �Ÿ� ���?
		//case SKILL_DIANA2:	//��ݼ���?: ���������� �߻��� Ȯ���� ���?
		//case SKILL_DIANA3:	//�Ƶ巹���� : �������� ������ MP ȸ���� ���?
		//case SKILL_DIANA4:	//Ȱ��ȭ : ��ų ���� �ð� ����
		//case SKILL_DIANA5:	//집중력유지 : STR이 높을수록 INT 상승
		//case SKILL_DIANA6:	//3way : 3방향으로 총 발사
		//case SKILL_DIANA7:	//���÷��Ǻ� : �������� ���� ƨ��
		//case SKILL_DIANA8:	//�����̾� : ȭ�� ����
		//case SKILL_DIANA9:	//로켓런쳐 : 로켓 발사되어 폭발
		//case SKILL_DIANA10:	//호밍미사일 : 유도탄 3개
		//case SKILL_DIANA11:	//킬링존 : 난사
		//case SKILL_DIANA12:	//����Ż������ : �ΰ�����
		//case SKILL_DIANA13:	//리커버리 : 회복탄
		//case SKILL_DIANA14:	//��а���?: ���� ���� ���ݷ� ���?
		//case SKILL_DIANA15:	//흡마의마탄 : 공격시 MP 흡수
		//case SKILL_DIANA16:	//�ʻ����� : ũ�� ���?
		//case SKILL_DIANA17:	//�ĸ������� : �����ð� �� ���?����

		//case SKILL_COMMON_MAXX1:	//힘단련 : STR 상승
		//case SKILL_COMMON_MAXX2:	//체력단련 : VIT 상승
		//case SKILL_COMMON_MAXX3:	//민첩단련 : AGI 상승
		//case SKILL_COMMON_MAXX4:	//정신단련 : INT 상승
		//case SKILL_COMMON_MAXX5:	//생명력강화 : HP 최대치 상승
		//case SKILL_COMMON_MAXX6:	//기력강화 : MP 최대치 상승
		//case SKILL_COMMON_MAXX7:	//무기숙련 : 공격력 증가
		//case SKILL_COMMON_MAXX8:	//방어구숙련: 방어력 증가
		//case SKILL_COMMON_MAXX9:	//�����ľ� : ũ��Ƽ�� Ȯ�� ���?
		//case SKILL_COMMON_MAXX10:	//�������� : ũ��Ƽ�� ������ ���?
		//case SKILL_COMMON_MAXX11:	//뚝심 : 데미지 경감
		//case SKILL_COMMON_MAXX12:	//정조준 : 명중 증가
		//case SKILL_COMMON_MAXX13:	//�ż�ȸ�� : ȸ�� ����

		//case SKILL_MAXX1:	//����¼���?: ���� �������� �� �θ޶��� ������ �������� Ȯ���� ����Ѵ�?
		//case SKILL_MAXX2:	//��ô���� : �θ޶� �ӵ� ���?
		//case SKILL_MAXX3:	//���Ӱ��� : �߰� ���� Ȯ�� ����
		//case SKILL_MAXX4:	//ȸ���»��?: �߰� ���� ������ �ش� ���ݿ� ���ؼ� ������ ���?
		//case SKILL_MAXX5:	//탄력성 : VIT 높을수록 AGI 상승
		//case SKILL_MAXX6:	//ȿ�������?: INT�� �������� AGI�� �ö�
	case SKILL_MAXX7:	//돌려차기 : 회전: 기절공격
		//case SKILL_MAXX8:	//����Ʈ : ����: ��Ÿ�?ª��
		//case SKILL_MAXX9:	//������Ʈ : ���� ���?����
		//case SKILL_MAXX10:	//캠핑헌트 : 앞으로 날라가서 제자리회전
		//case SKILL_MAXX11:	//ȣ����Ʈ : ���� �����?�� ������ �ǵ��ƿ�
		//case SKILL_MAXX12:	//��Ŭ��Ʈ : ���ΰ� �ֺ� ��ȣ
		//case SKILL_MAXX13:	//메가헌트 : 관통후 뒤에서 돌아옴
		//case SKILL_MAXX14:	//블러드헌트 : 적 공격시 HP 회복
		//case SKILL_MAXX15:	//현란무도 : 일정시간 회피율 증가
		//case SKILL_MAXX16:	//안도의한숨 : 적 공격 회피시 MP 회복
		//case SKILL_MAXX17:	//ȥ�źи� : ���� Ȯ�� ���?
		return true;
	}

	return false;
}

void HotKeyPress(OBJECT* pObj, int idx)
{
	//��ų ������ ���ҿɼǿ� ���� ����ð���?�ٿ��ش�.
	//���?���� �뷱�� - ����

	int obj = GetObjFromPtr(pObj);
	int limitStat = pObj->ps[PS_DELAY];
	int i, j;
	int closestEnemy;


	if (pObj->hotKey[idx].type != HOTKEY_SCREEN)

		//if (obj == raidPlayer)
		//	ReleaseCore();
		//else
		PlayRelease(pObj);

	switch (pObj->hotKey[idx].type) {
		//아무것도 하지 않는다.
	case HOTKEY_NOTHING:
		break;
		//��ų�� ���?�ش� ��ų�� �����?�� �ִ� �����̸� ���ش�.
		//조건1 MP가 충분한가
		//����2 ���� �����Ҽ� �ִ� �����ΰ�
		//����3 ���� ����ϴ�?��ų�� ���?�´� ��ų�ΰ�
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
		case SKILL_DIANA14://��а���?: ��ų ������ ��
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
			pObj->flamer = FLAMER_START_FRAME;
			pObj->hotKey[idx].frame = pObj->hotKey[idx].inven;
			pObj->currentSkill = pObj->hotKey[idx].idx;
			//pObj->attack = DIANA_SKILL_FLAMER;

			PlayMusic(M_FIRE);

			return;
		}


		//��ų ����
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


void NewCardKey(void)
{
	PlayKey(PLAYER);
}


// KeyRelease

void ReleaseCore(bool dispatchKey)
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

	//SetDemo()/AfterDemo()/SetTalk2() ?��? ??모드�??�어가�????�력 ?�태�??�리??목적?�로�?
	//ReleaseCore()�?부르는?? ?�래 switch(keyHandle)??"?�제 ?�렸????�?그�?�??�실??TalkKey,
	//PlayKey ???�버린다. �?결과 ????번으�??�음 ?�모 블록???�어가?�마??�?stale???��? ??
	//처리?�어 - ?�?��? ?�러 �?건너?�거?? ?�투 ?�중 ?�모�??�환?�는 ?�간 공격??중복 처리?�는 ?�의
	//?�인???�다. dispatchKey=false�?부르면 ?�리(???�래 코드)�??�고 ?�실?��? 건너?�다.
	//튜토리얼에서 특정 버튼을 누르라고 안내 중일 때, 지정된 터치영역이 아닌 곳을 눌렀으면
	//아무것도 처리하지 않는다. TalkKey()는 touchRect를 거치지 않고 탭만으로 movie.start++를
	//해버려서, SetRectPoint()를 막는 것만으로는 대화가 그냥 넘어가 버린다.
	//TUTORIAL_TOUCH_NONE(컷씬 진행 중)일 때는 막지 않는다. 대사를 탭으로 넘기는 건 정상 동작이다.
	if (gTutorialTouchFunc >= 0 && gTouchHitFunc != gTutorialTouchFunc)
		dispatchKey = false;

	if (dispatchKey)
	switch (keyHandle) {
#ifdef RELEASEEXEC
	case MK_TITLE:
#ifdef COSTUMETEST
		PlayKey(raidPlayer);
#else
		TitleKey();
#endif
		break;
	case MK_TALK:
		TalkKey();
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
	//누른 그 버튼에서 뗐을 때만 튀어오른다. 밖으로 빼서 취소한 경우는
	//UpdateButtonPress()가 이미 눌림을 풀어놨으므로 여기서 아무 일도 안 한다.
	ClearButtonPress(buttonPressFunc >= 0 && buttonPressFunc == gTouchHitFunc);

	is_release_finished = true;
	is_key_released = false;
	twice_released = false;

	touchYESNO = false;		//TouchArrow �� �׷��� �������� YesNoDraw() �翷�� ȭ��ǥ ��ġ�� �۵��ϰ� �ϱ� ����..
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

	//이번 터치가 뭘 눌렀는지 기록해 둔다. ReleaseCore()가 이걸 보고 튜토리얼 중
	//엉뚱한 곳을 눌렀을 때 키 처리를 통째로 건너뛴다.
	gTouchHitFunc = TUTORIAL_TOUCH_NONE;

	for (i = touchIndex - 1; i >= 0; i--) {
		if (GetRectPoint(x, y, touchRect[i][0], touchRect[i][1], touchRect[i][2], touchRect[i][3])) {

			gTouchHitFunc = touchRect[i][4];

			if (startTouchCheck == true) {
				startTouchRect[0] = touchRect[i][0];//x
				startTouchRect[1] = touchRect[i][1];//y
				startTouchRect[2] = touchRect[i][2];//width
				startTouchRect[3] = touchRect[i][3];//height

				//누른 티를 즉시 낸다. 여기서 늦추면 "먹통인가?" 싶어진다.
				SetButtonPress(touchRect[i][4]);
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

void ResetRectPoint(void)
{
	int i;
	for (i = 0; i < TOTALTOUCHCNT; i++)
		memset(touchRect, 0, sizeof(touchRect));
	touchIndex = 0;
}

//지금 이 터치기능이 살아 있는지. 터치영역 등록과 DrawHand 표시가 같은 판정을 쓰도록
//한 곳에 모아 둔다. 튜토리얼 안내 중에는 눌러야 하는 것 하나만 살아 있다.
bool IsTouchFuncEnabled(int func)
{
	if (touchDisable)
		return false;

	if (gTutorialTouchFunc != TUTORIAL_TOUCH_FREE && func != gTutorialTouchFunc)
		return false;

	return true;
}

void SetRectPoint(int rx, int ry, int width, int height, int func)
{
	//튜토리얼 안내 중에는 지금 눌러야 하는 것 말고는 터치영역 자체를 만들지 않는다.
	//모든 터치영역이 이 함수를 거치므로 메뉴마다 따로 막을 필요가 없다.
	if (gTutorialTouchFunc != TUTORIAL_TOUCH_FREE && func != gTutorialTouchFunc)
		return;

	// 터치 사각형 좌표
	int rectX1 = rx;
	int rectY1 = ry;
	int rectX2 = rx + width;
	int rectY2 = ry - height;

	// Ŭ���� ������ ���� ���� ���?
	int clippedX1 = Max(rectX1, clipX);
	int clippedY1 = Min(rectY1, clipY);
	int clippedX2 = Min(rectX2, clipX2);
	int clippedY2 = Max(rectY2, clipY2);

	// ��ġ�� ������ ������ ��ġ ���?�� ��
	if (clippedX1 >= clippedX2) return;
	if (clippedY1 <= clippedY2) return;

	touchRect[touchIndex][0] = clippedX1;
	touchRect[touchIndex][1] = clippedY1;
	touchRect[touchIndex][2] = clippedX2 - clippedX1;
	touchRect[touchIndex][3] = clippedY1 - clippedY2;
	touchRect[touchIndex][4] = func;

	touchIndex++;
}

void touchFunc(int func)
{
	int i, j;
	int x = DX / 2 - STATUSWIN_X / 2;
	int y = DY / 2 + MINDY / 2;
	int itemType, itemDetail, itemGrade;


	//현재 터치하면 안되면
	if (touchDisable)
		return;

	//�κ��丮���� Ű�� 1:1������ �ȵǴ� �͵��� ���⼭ �ٷ� ó���Ѵ�.
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
	else if (func >= TOUCH_FUNC_HIT_ATTACK && func < TOUCH_FUNC_HIT_ATTACK + MAXCREW) {
		systemKey = AVK_HIT_ATTACK + func - TOUCH_FUNC_HIT_ATTACK;
	}
	else if (func >= TOUCH_FUNC_OPTION_LANGUAGE_SELECT && func < TOUCH_FUNC_OPTION_LANGUAGE_SELECT + TOTALLANGUAGE) {
		systemKey = AVK_OPTION_LANGUAGE_SELECT + func - TOUCH_FUNC_OPTION_LANGUAGE_SELECT;
	}
	else if (func >= TOUCH_FUNC_OPTION_PUSHALARM_TYPE && func < TOUCH_FUNC_OPTION_PUSHALARM_TYPE + TOTAL_PUSHALARM) {
		systemKey = AVK_OPTION_PUSHALARM_TYPE + func - TOUCH_FUNC_OPTION_PUSHALARM_TYPE;
	}
	else if (func >= TOUCH_FUNC_COLLECTIONS_REWARD && func < TOUCH_FUNC_COLLECTIONS_REWARD + TOTAL_COLLECTIONS) {
		systemKey = AVK_COLLECTIONS_REWARD + func - TOUCH_FUNC_COLLECTIONS_REWARD;
	}
	else if (func >= TOUCH_FUNC_ITEMDETAIL && func < TOUCH_FUNC_ITEMDETAIL + TOTALINVENTORY) {
		systemKey = AVK_ITEMDETAIL + func - TOUCH_FUNC_ITEMDETAIL;
	}
	else if (func >= TOUCH_FUNC_EQUIPDETAIL && func < TOUCH_FUNC_EQUIPDETAIL + TOTALEQUIP) {
		systemKey = AVK_EQUIPDETAIL + func - TOUCH_FUNC_EQUIPDETAIL;
	}
	else if (func >= TOUCH_FUNC_EQUIP_INVENTORY && func < TOUCH_FUNC_EQUIP_INVENTORY + TOTALINVENTORY) {
		//for (i = 0; i < TOTALITEMTYPE; i++)
		//	if (func - TOUCH_FUNC_EQUIP_INVENTORY < itemStartCnt[i + 1]) {
		//		itemType = i;
		//		break;
		//	}

		//itemType = robin.inven[(func - TOUCH_FUNC_EQUIP_INVENTORY)].type;
		//itemDetail = ((func - TOUCH_FUNC_EQUIP_INVENTORY) - itemStartCnt[itemType]);
		//itemGrade = GRADE_NORMAL;

		//itemDetail = ((func - TOUCH_FUNC_EQUIP_INVENTORY) - itemStartCnt[itemType]) / TOTALGRADE;
		//itemGrade = ((func - TOUCH_FUNC_EQUIP_INVENTORY) - itemStartCnt[itemType]) % TOTALGRADE;

		systemKey = AVK_EQUIP_INVENTORY + func - TOUCH_FUNC_EQUIP_INVENTORY;
	}
	else if (func >= TOUCH_FUNC_CREW_DETAIL && func < TOUCH_FUNC_CREW_DETAIL + CAP_CREW) {
		systemKey = AVK_CREW_DETAIL + func - TOUCH_FUNC_CREW_DETAIL;
	}
	else if (func >= TOUCH_FUNC_CREW_REWARD && func < TOUCH_FUNC_CREW_REWARD + CAP_CREW) {
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
	else if (func >= TOUCH_FUNC_MENUCUR_CREWSET && func < TOUCH_FUNC_MENUCUR_CREWSET + CAP_CREW) {
		systemKey = AVK_MENUCUR_CREWSET + func - TOUCH_FUNC_MENUCUR_CREWSET;
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
		case TOUCH_FUNC_COLLECTIONS://����
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
		case TOUCH_FUNC_NEWS://ĳ�� ����
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
		case TOUCH_FUNC_OPTION_HELP:
			systemKey = AVK_OPTION_HELP;
			break;
		case TOUCH_FUNC_OPTION_HELP_MAIL:
			systemKey = AVK_OPTION_HELP_MAIL;
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
		case TOUCH_FUNC_CREW_LEVELUP:
			systemKey = AVK_CREW_LEVELUP;
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
			if (option.gameMode == TURNRPG) {
				systemKey = AVK_ATTACK;
				drawHandle = MD_PLAY;
				keyHandle = MK_PLAY;
				isDemo = false;
			}
			else
				systemKey = AVK_5;
			break;
		case TOUCH_FUNC_MOVE:
			joyPressed = true;
			joyReturning = false;

			joyStartX = bar[BAR_JOYSTICK].x;
			joyStartY = bar[BAR_JOYSTICK].y;
			joyDx = 0;
			joyDy = 0;
			joyPower = 0;
			joyDir = -1;
			break;
		case TOUCH_FUNC_JUMP:
			systemKey = AVK_2;
			break;
		case TOUCH_FUNC_HEROCHECK_DIANA:
			systemKey = AVK_HEROCHECK_DIANA;
			break;
		case TOUCH_FUNC_HEROCHECK_MAXX:
			systemKey = AVK_HEROCHECK_MAXX;
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
			//Director::getInstance()->setAnimationInterval(1.0f / option.gameSpeed);
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
		case TOUCH_FUNC_POPUP_CASTLEMENU:
			systemKey = AVK_POPUP_CASTLEMENU;
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
		case TOUCH_FUNC_MENUCUR_CREW1:
		case TOUCH_FUNC_MENUCUR_CREW2:
		case TOUCH_FUNC_MENUCUR_CREW3:
		case TOUCH_FUNC_MENUCUR_CREW4:
		case TOUCH_FUNC_MENUCUR_CREW5:
		case TOUCH_FUNC_MENUCUR_CREW6:
			systemKey = AVK_MENUCUR_CREW1 + func - TOUCH_FUNC_MENUCUR_CREW1;
			break;
		case TOUCH_FUNC_MENUX_1:
		case TOUCH_FUNC_MENUX_2:
		case TOUCH_FUNC_MENUX_3:
		case TOUCH_FUNC_MENUX_4:
		case TOUCH_FUNC_MENUX_5:
		case TOUCH_FUNC_MENUX_6:
			systemKey = AVK_MENUX_1 + func - TOUCH_FUNC_MENUX_1;
			break;
		}
	}
}

void SaveFlag(int which)
{
	saveFlag[which] = true;
}


// JoyStick 관련

bool JoyStickPressPossible(void)
{

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

	if (!curtainFrame && !infoFrame && !areaFrame && attackSequence == ATTACKSEQUENCE_READY && !ao[PLAYER].dead && arenaStatus == STATUS_PLAY && autoPlay == false) {
		return true;
	}
	else {
		return false;
	}
}

//�������̵��� ���� 
//1. 보스가 등장하고 
//2. ������ ������ �����ϸ�
//3. 

void BoxOpen(void)
{
	int i;
	int itemType, itemDetail, itemGrade, itemLv;
	int rand = Random(ITEMDETAILSEED);

	//
	//TEST
	//���⼭ ���ڿ��� ���� �������� ������ش�?

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

	//MD_PLAY의 상자는 몬스터 드롭이라 골드만 나온다.
	//boxDropProc 표에는 장비/배틀/레이드까지 들어 있지만 그건 플레이 화면 밖에서 쓰는
	//분포다. 여기서 표를 그대로 따르면 몬스터를 때릴 때마다 배틀/레이드로 넘어간다.
	if (drawHandle == MD_PLAY)
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
		//드롭 품질은 플레이어 레벨이 아니라 성 진행도를 따른다.
		//robin.lv를 쓰면 성을 진행하지 않고 레벨만 올려도 최상위 티어가 나온다.
		itemDetail = MakeItemDetail(itemType, GetDropLv());
		itemGrade = MakeItemGrade(itemType, GetDropLv(), itemDetail);
		itemLv = MakeItemLevel(itemType, GetDropLv());

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
	ao[ITEMBOX].motion = BOXSTATUS_OPENING;
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

void JoyStickRelease(void)
{
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	//�ڵ��̸�
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

int printCoords() {
	int radius = 0; // 초기 반경

	int centerX = 0; // 중심점 x 좌표
	int centerY = 0; // 중심점 y 좌표

	double angle = 0; // 회전 각도
	double angleIncrement = (float)0.3f; // 각도 증가량

	for (int i = 0; i < MAX_POINTS; ++i) {
		// �ݰ��� 256 �̻��� ���?�ݰ��� �����ϰ� ���?ȸ��
		if (radius >= MAX_RADIUS) {
			radius = MAX_RADIUS;
		}

		// 좌표 계산
		int x = centerX + static_cast<int>(radius * std::cos(angle));
		int y = centerY + static_cast<int>(radius * std::sin(angle));

		// ��ǥ�� �迭�� ����
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

		// ��ǥ�� �迭�� ����
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

//�� �Լ��� ��ġ�� ������ �� ������?������ Ȯ���ϴ°�
//touchX, touchY ���� ������ ��ġ�� ������ �ְ�
//�� ������ ���� �����ϰ��� �ϴ� �����ӿ� ���ԵǴ��� Ȯ���ϴ� �Լ�

//----------------------------------------------------------------------
// 버튼 감촉
//
// 버튼 객체를 따로 만들지 않는다. 이 코드베이스의 터치는 매 프레임 다시
// 등록되는 사각형 + 기능 번호(SetRectPoint)라서, 그리기와 터치영역이 서로
// 다른 함수에서 계산된다. 객체로 묶으려면 수백 곳을 한꺼번에 고쳐야 하고
// SetRectPoint 한 곳에서 하던 튜토리얼 게이팅도 다시 설계해야 한다.
//
// 그래서 기능 번호를 그대로 키로 쓴다. 그리는 쪽은 자기 func으로
// GetButtonScale()만 물어보면 되고, 안 물어보는 버튼은 예전 그대로 동작한다.
//----------------------------------------------------------------------

//누르는 순간 호출한다. 눌린 사각형을 같이 적어둬야 손가락이 버튼 밖으로
//나갔을 때 취소할 수 있다.
void SetButtonPress(int func)
{
	buttonPressFunc = func;
	buttonPressFrame = 0;

	buttonPressRect[0] = startTouchRect[0];
	buttonPressRect[1] = startTouchRect[1];
	buttonPressRect[2] = startTouchRect[2];
	buttonPressRect[3] = startTouchRect[3];

	buttonPressX = touchX;
	buttonPressY = touchY;
}

//떼거나 취소할 때 호출한다. pop이 true면 튀어오르는 연출을 시작한다.
void ClearButtonPress(bool pop)
{
	if (pop && buttonPressFunc >= 0) {
		buttonPopFunc = buttonPressFunc;
		buttonPopFrame = BUTTON_POPFRAME;
		buttonPopX = buttonPressX;
		buttonPopY = buttonPressY;

		//떼고 나서도 잠깐 남아 있어야 톡 누른 것이 눈에 든다.
		buttonHighlightFrame = BUTTON_HIGHLIGHTHOLD + BUTTON_HIGHLIGHTFADE;
	}

	buttonPressFunc = -1;
	buttonPressFrame = 0;
}

//한 프레임 진행. 손가락이 처음 눌렀던 사각형을 벗어나면 눌림을 푼다.
//누른 채로 밖으로 빼면 취소되는 것이 버튼의 기본 동작이고, 그래야
//"되돌릴 수 있다"는 안정감이 생긴다.
void UpdateButtonPress(void)
{
	//이번 프레임에 누가 스스로 표현하는지는 지금부터 다시 센다.
	buttonPressHandled = false;

	if (buttonHighlightFrame > 0)
		buttonHighlightFrame--;

	if (buttonPopFrame > 0)
		buttonPopFrame--;
	else
		buttonPopFunc = -1;

	if (buttonPressFunc < 0)
		return;

	buttonPressFrame++;

	if (!rectContainsTouchPoint(buttonPressRect[0], buttonPressRect[1],
			buttonPressRect[2], buttonPressRect[3]))
		ClearButtonPress(false);
}

//그리는 쪽이 쓰는 배율. 누르고 있으면 들어가 있고, 뗀 직후에는 튀었다가
//제자리로 돌아온다.
//기능 번호만으로는 부족하다. 한 화면에 같은 번호를 쓰는 버튼이 둘 이상
//있을 수 있어서(장비창의 장착/강화가 그렇다) 그것들이 같이 움직인다.
//누른 지점이 내 사각형 안에 있는지까지 봐야 누른 그 버튼만 반응한다.
static bool ButtonHit(int px, int py, int x, int y, int w, int h)
{
	return (px >= x) && (px <= x + w) && (py <= y) && (py >= y - h);
}

//기능 번호를 모르는 버튼용. 누른 지점이 내 사각형 안이면 나다.
//버튼끼리는 겹치지 않으므로 이것만으로 충분하다.
float GetButtonPressScale(int x, int y, int w, int h)
{
	if (buttonPressFunc >= 0
		&& ButtonHit(buttonPressX, buttonPressY, x, y, w, h)) {
		buttonPressHandled = true;

		return BUTTON_DOWNSCALE;
	}

	if (buttonPopFrame > 0
		&& ButtonHit(buttonPopX, buttonPopY, x, y, w, h)) {
		float t = (float)buttonPopFrame / (float)BUTTON_POPFRAME;

		buttonPressHandled = true;

		return 1.0f + (BUTTON_POPSCALE - 1.0f) * t;
	}

	return 1.0f;
}

float GetButtonScale(int func, int x, int y, int w, int h)
{
	if (func < 0)
		return 1.0f;

	if (func == buttonPressFunc
		&& ButtonHit(buttonPressX, buttonPressY, x, y, w, h)) {
		//이 버튼이 스스로 눌린 티를 내므로 공용 하이라이트는 필요 없다.
		buttonPressHandled = true;

		return BUTTON_DOWNSCALE;
	}

	if (func == buttonPopFunc && buttonPopFrame > 0
		&& ButtonHit(buttonPopX, buttonPopY, x, y, w, h)) {
		float t = (float)buttonPopFrame / (float)BUTTON_POPFRAME;

		//튀는 동안에도 이 버튼이 스스로 표현하는 중이다.
		buttonPressHandled = true;

		return 1.0f + (BUTTON_POPSCALE - 1.0f) * t;
	}

	return 1.0f;
}

bool rectContainsTouchPoint(int x, int y, int w, int h)
{
	return (touchX >= x) &&
		(touchY <= y) &&
		(touchX <= x + w) &&
		(touchY >= y - h);
}