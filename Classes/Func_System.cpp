#include "Core.h"
#include "Data.h"
#include "Func.h"
#include "Text.h"

#ifndef _WIN32
#include <sys/time.h>

static unsigned long GetTickCount()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (unsigned long)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
#endif

// Initialize and Setting
void InitMotion(OBJECT* pObj)
{
	int motion = pObj->motion;
	const signed short* scPtr;
	int detail;
	int skillLv;
	float cZoom = pObj->zoom;

	if (pObj->cmf < 0) {
		switch (pObj->type) {
		case OBJ_BOX:
			scPtr = &neutralData[pObj->type * NEUTRALDATASIZE];
			pObj->cpx = (float)*(scPtr + 4) * cZoom;
			pObj->cpy = (float)*(scPtr + 5) * cZoom;
			pObj->cx = (float)*(scPtr + 6) * cZoom;
			pObj->cy = (float)*(scPtr + 7) * cZoom;

			break;
		}
		return;
	}

	//충돌 사이즈
	scPtr = &cmd_m_crash[pObj->cmf][motion * 8];

	pObj->cx = (*(scPtr + 2)) * cZoom;
	pObj->cy = (*(scPtr + 3)) * cZoom;
	pObj->cpx = -DIR(pObj->dirF) * *scPtr * cZoom - pObj->dirF * pObj->cx;
	pObj->cpy = Min(0, *(scPtr + 1) * cZoom);


	//공격 사이즈
	pObj->ax = (*(scPtr + 6)) * pObj->zoom;
	pObj->ay = (*(scPtr + 7)) * pObj->zoom;
	pObj->apx = -DIR(pObj->dirF) * *(scPtr + 4) * pObj->zoom - pObj->dirF * pObj->ax;
	pObj->apy = *(scPtr + 5) * pObj->zoom;

	//플레이어 공격사이즈 변경
	motion = GetObjFromPtr(pObj);

	if (pObj->equipImg[EQUIP_WEAPON] == 0 && motion < TOTALCHAR)
		return;

	detail = pObj->equip[EQUIP_WEAPON].detail * 2 * _2X;

	if (motion >= BULLET) {
		if (pObj->moveHandler == BULLETBOOMERANGMOVE) {
			detail = ao[pObj->target].equip[EQUIP_WEAPON].detail * 2 * _2X;
			pObj->apx -= detail;
			pObj->apy -= detail;
			pObj->ax += detail * 2;
			pObj->ay += detail * 2;
		}
		return;
	}

	if (pObj->moveHandler == PLAYERMOVE || pObj->moveHandler == ENEMYPLAYERMOVE) {
		if ((ao[motion].type) == ROBIN) {
			if (pObj->dirF == LEFT)
				pObj->apx -= 2 * detail;

			pObj->ax += 2 * detail;
		}
		else if ((ao[motion].type) == DIANA) {
			//if (motion == 0)
			skillLv = GetSkillLv(motion, SKILL_DIANA1);

			if (skillLv) {
				if (pObj->dirF == LEFT)
					pObj->apx -= 3 * skillLv;

				pObj->ax += 3 * skillLv;
			}

			if (pObj->dirF == LEFT)
				pObj->apx -= 2 * detail;

			pObj->ax += 2 * detail;
		}
	}
}

void InitGraphics(void)
{
	int i, j;
	//int x, y, z, aa, b;
	unsigned int dist;

	memset(a.waves, 0, sizeof(a.waves));

	for (i = -WAVE_RADIUS; i <= WAVE_RADIUS; i++) {
		for (j = -WAVE_RADIUS; j <= WAVE_RADIUS; j++) {
			dist = SqrtX256(i * i + j * j);

			if (dist < WAVE_RADIUS << 8)
				a.waves[(i + WAVE_RADIUS) * WAVE_DIAMETER + j + WAVE_RADIUS] = (signed short)(BC_mathCos1024((dist * 3217 / WAVE_RADIUS) >> 18) >> 5);
		}
	}
}

void InitMenu(void)
{
	int i;

	menuIdx = 0;
	menuDepth = 0;
	menuCur = 0;
	menuPage = 0;
	menuPage2 = 0;
	menuFocus = 0;
	menuFocus2 = 0;
	menuX = 0;
	menuY = 0;
	menuResult = 0;
	menuIcon = 0;
	menuFrame = 0;
	menuAni = 0;
	menuItem = -1;
	hotKeyFrame = 0;
	npcGetFrame = 0;
	stageClearFrame = 0;
	skillGetFrame = 0;
	buffItemFrame = 0;
	bet = 0;
	memset(dmgInfo, 0, sizeof(dmgInfo));
	curHero = 0;

	memset(scS, 0, sizeof(scS));
	memset(scE, 0, sizeof(scE));
	memset(scT, 0, sizeof(scT));
	memset(scC, 0, sizeof(scC));
	memset(scP, 0, sizeof(scP));

	for (i = 0; i < TOTAL_MENU; i++)
		scT[i] = GetScrollDy(i);

	SetScreenRatio();

	InitBar(BAR_GOLD);
	InitBar(BAR_CROWN);
	InitBar(BAR_BOX);
	InitBar(BAR_HEART);
	InitBar(BAR_MEDAL);
	//TEST
	//InitBar(BAR_QUEST);
	InitBar(BAR_SHIELD);
	//InitBar(BAR_COMBATPOWERALL);
	InitBar(BAR_STAR);
	InitBar(BAR_DAY);
	//InitBar(BAR_WAVE);


	InitBar(BAR_COIN);
	InitBar(BAR_ITEM);
	InitBar(BAR_CASTLE);
	InitBar(BAR_CREW);
	InitBar(BAR_EQUIP);
	InitBar(BAR_MAINSHOP);

	InitBar(BAR_ROULETTE);
	
	//InitBar(BAR_ENEMYUSER);
	//InitBar(BAR_ENEMYUSER_BOX);
	//InitBar(BAR_DAILYQUEST);
	//InitBar(BAR_CREWUPGRADE);
	//InitBar(BAR_FRIENDS);

	////InitBar(BAR_RAIDCOIN);

	////InitBar(BAR_HAMMER);
	////InitBar(BAR_BOSSHP);
	////InitBar(BAR_COMBATPOWER);
	////InitBar(BAR_STAGEPROGRESS);
	////InitBar(BAR_INVENTORY);
	//InitBar(BAR_BATTLECOIN);

	if (GetEventMenuIdx(EVENTTYPE_QUEST) != -1)
		bar[BAR_QUEST].active = true;

	TOTAL_OPENEDMENU = 0;
	for (i = 0; i < TOTAL_MENU; i++) {
		if (menuOpened[i])
			TOTAL_OPENEDMENU++;
	}


	//scS[MENU_CREW] = CREWHEIGHT * TOTAL_CREW;
	joyStickDir = LEFT;
	joyStickAni = 0;

	memset(&currencyMarkArr, 0, sizeof(currencyMarkArr));
	memset(&currencyMarkArr_PopUp, 0, sizeof(currencyMarkArr_PopUp));
	memset(&currencyMark, 0, sizeof(currencyMark));
	memset(&currencyMark_PopUp, 0, sizeof(currencyMark_PopUp));
	memset(&itemMark, 0, sizeof(itemMark));
	memset(&controlMark, 0, sizeof(controlMark));
	memset(&controlMarkBack, 0, sizeof(controlMarkBack));
	memset(&controlerSpread, 0, sizeof(controlerSpread));
	memset(&cardMark, 0, sizeof(cardMark));
	memset(&cardMarkBack, 0, sizeof(cardMarkBack));
	memset(&rewardMark, 0, sizeof(rewardMark));
	memset(&boxMark, 0, sizeof(boxMark));
	memset(&boxCardMark, 0, sizeof(boxCardMark));
	memset(&soulMark, 0, sizeof(soulMark));
	memset(&goldAlphaMark, 0, sizeof(goldAlphaMark));
}

void InitGame(void)
{
	int i, j, k;

	for (i = 0; i < TOTALOBJECT; i++) {
		memset(&ao[i], 0, sizeof(OBJECT));
		ao[i].O2 = OXYGEN;
	}

	memset(&dmgInfo, 0, sizeof(dmgInfo));
	memset(&imgText, 0, sizeof(imgText));
	memset(&hitMark, 0, sizeof(hitMark));
	memset(&rpVar2, 0, sizeof(rpVar2));

	timeFrame = 0;
	menuItem = -1;
	loadedMap = -1;
	cNeutral = -1;
	focus = 0;
	raidPlayer = PLAYER;
	infoFrame = 0;
	areaFrame = 0;
	questFrame = 0;
	itemFrame = 0;
	battleStartFrame = 0;
	nameFrame = 0;
	warpFrame = 0;
	npcGetFrame = 0;
	stageClearFrame = 0;
	skillGetFrame = 0;
	buffItemFrame = 0;
	returnFrame = 0;
	arenaFrame = 0;
	arenaTotalTime = 0;
	arenaScore = 0;
	currentTimeQuest = 0;
	escort.active = 0;
	TimeFailDemo = 0;
	infoText = 0;
	caveMap = 0;
	caveKill = 0;
	memset(&movie.robinMotion, 0, sizeof(movie.robinMotion));

	isDemo = false;
	talkShakeFrame = 0;

	robin.maxInven = option.maxInven;

	for (i = ENEMY; i < NEUTRAL; i++)
		ao[i].hp = ao[i].maxhp = 0;

	totalProb = 0;

	tutorialMode = true;


	MakeBoxDropPercent();//소수점 초기화

	for (i = 0; i < TOTALQUESTREQUEST; i++)
	{
		for (j = 0; j < TOTALSUBQUEST; j++) {
			if (j == 0)
				questRequestItemCnt[i * TOTALSUBQUEST + j] = questRequestItemCntData[i * TOTALSUBQUEST + j];
			else
				questRequestItemCnt[i * TOTALSUBQUEST + j] = questRequestItemCnt[i * TOTALSUBQUEST + j - 1] + questRequestItemCntData[i * TOTALSUBQUEST + j];
		}
	}


	int questDataCnt = sizeof(questRequestItemCntData);
	int subQuestDataCnt;

	for (i = 0; i < questDataCnt / TOTALSUBQUEST; i++) {
		subQuestDataCnt = 0;
		for (j = 0; j < TOTALSUBQUEST; j++) {
			if (questRequestItemCntData[i * TOTALSUBQUEST + j] > 0)
				subQuestDataCnt++;
		}
		subQuestCnt[i] = subQuestDataCnt;
	}
	//스테이스바 
	//ReleaseCore();
	rouletteNum = 0;

	wheelMaxSpeed = WHEELMAXSPEED;

	maxUserLv = 50;

	refreshRate = FPS;
}

void EraseControlMark(int selected)
{
	int i;
	//일단 알파값을 올려주고 알파값이 다 올라가면 지워지도록 한다.
	controlMark[selected].alpha = 1;

	for (i = selected + 1; i < actionCardCnt; i++) {
		controlMark[i].targetX2 = controlMark[i].targetX = xOffset + (i - 1) * (ROULETTECARDSIZE_X + 1 * _2X) + ROULETTECARDSIZE_X / 2;
		controlMark[i].targetY2 = controlMark[i].targetY;
		controlMark[i].zoom2 = controlMark[i].zoom;
		controlMark[i].speed = controlMark[i].speed2 = 1 * _2X;
		controlMark[i].speedIncrement = controlMark[i].speedIncrement2 = 1 * _2X;
		controlMark[i].frame = 1;
		controlerSpread[i] = false;
	}

	SaveGame();
}
//로그의 정의
//
void AddLog(unsigned char type, unsigned short cmf, unsigned short cmf2, unsigned short icon, long long count,
	int x, int y, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2,
	float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2, char* text)
{
	int i;
	int curIdx;//현재 인덱스
	int activeIdx = -1;

	for (i = 0; i < MAXLOG; i++) {
		if (gameLog[i].active == false || (gameLog[i].active == true && gameLog[i].type == type)) {
			gameLog[i].active = true;
			gameLog[i].type = type;

			gameLog[i].cmf = cmf;
			gameLog[i].cmf2 = cmf2;
			gameLog[i].icon = icon;
			gameLog[i].count = count;

			gameLog[i].x = x;
			gameLog[i].y = y;

			gameLog[i].targetX = targetX;
			gameLog[i].targetY = targetY;
			gameLog[i].targetX2 = targetX2;
			gameLog[i].targetY2 = targetY2;
			gameLog[i].speed = speed;
			gameLog[i].speedIncrement = speedIncrement;
			gameLog[i].speed2 = speed2;
			gameLog[i].speedIncrement2 = speedIncrement2;
			gameLog[i].waitingFrame = waitingFrame;
			gameLog[i].waitingFrame2 = waitingFrame2;
			gameLog[i].frame = gameLog[i].frame2 = 0;

			gameLog[i].zoom = zoom;
			gameLog[i].zoomEnd = zoomEnd;
			gameLog[i].zoomIncrement = zoomIncrement;
			gameLog[i].zoom2 = zoom2;
			gameLog[i].zoomEnd2 = zoomEnd2;
			gameLog[i].zoomIncrement2 = zoomIncrement2;

			memset(&gameLog[i].text, 0, sizeof(gameLog[i].text));
			memcpy(&gameLog[i].text, text, sizeof(gameLog[i].text));
			curIdx = i;
			break;
		}

	}

	for (i = 0; i < curIdx; i++) {
		if (gameLog[i].frame > 0 || gameLog[i].frame2 > 0) {
			activeIdx = i;
		}
	}
	//아직 활성화되어 있는 인덱스가 없으면 이번에 add된 로그를 활성화시켜주자.
	if (activeIdx == -1)
		gameLog[curIdx].frame = 1;

}

void AddBar(BAR* barP, signed long long add, int countFrame)
{
	if (barP->type == BAR_ITEM) {
		barP->type = barP->type;
	}

	barP->active = true;
	//이미 더하고 있는게 있으면
	if (barP->add) {
		barP->count += barP->add;
	}
	barP->add = add;
	
	if (barP->addView == false)
	{
		barP->addViewSum = add;
	}
	else
	{
		barP->addViewSum += add;
	}

	barP->addView = true;

	barP->aniFrame = 1;
	barP->countFrame = countFrame;

	//barP->front = true;

	//어떤 바도 마이너스가 되지는 않는다.
	//if (bar->count < 0)
	//	bar->count = 0;
}

void InitTarget(void)
{
	int i;

	for (i = ENEMY; i < NEUTRAL; i++) {
		if (ao[i].active == true && ao[i].mom == i) {
			ao[PLAYER].target = i;
		}
	}

	for (i = NEUTRAL; i < ITEMOBJ; i++) {
		if (ao[i].active == true && ao[i].type == OBJ_BOX) {
			ao[PLAYER].target = i;
			break;
		}
	}

}

void ArrangeTarget(void)
{
	int i, j;
	int distance[MAXENEMY] = { 0, };
	int enemyIdx[MAXENEMY] = { 0, };

	return;

	//만약 타겟팅 된 몬스터가 죽었으면
	for (i = 0, j = 0; i < MAXENEMY; i++) {
		if (ao[GetObjectNumFromEnemyIdx(i)].active == true && ao[GetObjectNumFromEnemyIdx(i)].dead == false) {
			enemyIdx[j] = GetObjectNumFromEnemyIdx(i);
			distance[j] = GetDistance(&ao[PLAYER], &ao[enemyIdx[j]]);
			j++;
		}
	}

	sortArray(distance, enemyIdx, j);

	ao[PLAYER].target = enemyIdx[0];
}

void ArrangeEnemyTarget(void)
{
	int i;
	//만약 타겟팅 된 몬스터가 죽었으면
	if (ao[ao[PLAYER].target].dead == true || ao[ao[PLAYER].target].active == false) {
		InitTarget();
	}
}

//몬스터가 죽으면 해당 내용에 대해 HP바를 어레인지 해주는것
void ArrangeEnemyHpBar(void)
{
	int i;
	for (i = 0; i < MAXENEMY; i++) {
		if (ao[bar[BAR_ENEMYHP + i].owner].dead == true || ao[bar[BAR_ENEMYHP + i].owner].active == false) {
			bar[BAR_ENEMYHP + i].active = false;
		}
	}
}

void LoadEnemyHpBar(void)
{
	int i, j = 0;
	for (i = ENEMY; i < NEUTRAL; i++) {
		if (ao[i].mom == ENEMY + GetEnemyBarIdx(i) && ao[i].active == true && ao[i].dead == false) {
			InitBar(BAR_ENEMYHP + GetEnemyBarIdx(i));
		}
	}
}

void InitBar(int type)
{
	int heroCnt = 1;
	switch (type) {
	case BAR_GOLD:
		bar[BAR_GOLD].active = true;
		bar[BAR_GOLD].type = BAR_GOLD;

		bar[BAR_GOLD].count = robin.gold;
		bar[BAR_GOLD].add = 0;
		bar[BAR_GOLD].countFrame = 0;

		bar[BAR_GOLD].icon = ICON_GOLD;
		bar[BAR_GOLD].iconFrame = 0;

		bar[BAR_GOLD].frame = 0;
		bar[BAR_GOLD].frame2 = 0;
		bar[BAR_GOLD].aniFrame = 0;

		bar[BAR_GOLD].x = CROWNBARWIDTH + 2 * _2X;
		bar[BAR_GOLD].y = DY - (GNBHEIGHT - GNB_INIT_HEIGHT);

		bar[BAR_GOLD].targetX = 0;
		bar[BAR_GOLD].targetY = 0;

		bar[BAR_GOLD].front = false;

		bar[BAR_GOLD].drawFunc = BAR_GOLD;

		bar[BAR_GOLD].zoom = BAR_GOLD_ZOOM;
		break;
	case BAR_CROWN:
		bar[BAR_CROWN].active = true;
		bar[BAR_CROWN].type = BAR_CROWN;

		bar[BAR_CROWN].count = ao[PLAYER].exps;
		bar[BAR_CROWN].add = 0;
		bar[BAR_CROWN].countFrame = 0;

		bar[BAR_CROWN].icon = ICON_STAR;
		bar[BAR_CROWN].iconFrame = 0;

		bar[BAR_CROWN].frame = 0;
		bar[BAR_CROWN].frame2 = 0;
		bar[BAR_CROWN].aniFrame = 0;

		bar[BAR_CROWN].x = 0;
		bar[BAR_CROWN].y = DY - (GNBHEIGHT - GNB_INIT_HEIGHT);

		bar[BAR_CROWN].targetX = 0;
		bar[BAR_CROWN].targetY = 0;

		bar[BAR_CROWN].front = false;

		bar[BAR_CROWN].drawFunc = BAR_CROWN;

		bar[BAR_CROWN].zoom = BAR_CROWN_ZOOM;
		break;
	case BAR_HAMMER:
		bar[BAR_HAMMER].active = true;
		bar[BAR_HAMMER].type = BAR_HAMMER;

		bar[BAR_HAMMER].count = robin.hammer;
		bar[BAR_HAMMER].add = 0;
		bar[BAR_HAMMER].countFrame = 0;

		bar[BAR_HAMMER].icon = ICON_HAMMER;
		bar[BAR_HAMMER].iconFrame = 0;

		bar[BAR_HAMMER].frame = 0;
		bar[BAR_HAMMER].frame2 = 0;
		bar[BAR_HAMMER].aniFrame = 0;

		bar[BAR_HAMMER].x = GOLDBARWIDTH + CROWNBARWIDTH;
		bar[BAR_HAMMER].y = DY - (GNBHEIGHT - GNB_INIT_HEIGHT) - 2 * _2X;

		bar[BAR_HAMMER].targetX = 0;
		bar[BAR_HAMMER].targetY = 0;

		bar[BAR_HAMMER].front = false;

		bar[BAR_HAMMER].drawFunc = BAR_HAMMER;

		bar[BAR_HAMMER].zoom = BAR_HAMMER_ZOOM;
		break;
	case BAR_SHIELD:
		bar[BAR_SHIELD].active = true;
		bar[BAR_SHIELD].type = BAR_SHIELD;

		bar[BAR_SHIELD].count = robin.shield;
		bar[BAR_SHIELD].add = 0;
		bar[BAR_SHIELD].countFrame = 0;

		bar[BAR_SHIELD].icon = ICON_SHIELD;
		bar[BAR_SHIELD].iconFrame = 0;

		bar[BAR_SHIELD].frame = 0;
		bar[BAR_SHIELD].frame2 = 0;
		bar[BAR_SHIELD].aniFrame = 0;

		bar[BAR_SHIELD].x = CROWNBARWIDTH + 2 * _2X + GOLDBARWIDTH + 2 * _2X + COMBATPOWBARWIDTH + 1 * _2X;// +10 * _2X;
		bar[BAR_SHIELD].y = DY - (GNBHEIGHT - GNB_INIT_HEIGHT) - 2 * _2X;

		bar[BAR_SHIELD].targetX = 0;
		bar[BAR_SHIELD].targetY = 0;

		bar[BAR_SHIELD].front = false;

		bar[BAR_SHIELD].drawFunc = BAR_SHIELD;

		bar[BAR_SHIELD].zoom = BAR_SHIELD_ZOOM;
		break;
	case BAR_BOX:
		bar[BAR_BOX].active = true;
		bar[BAR_BOX].type = BAR_BOX;

		bar[BAR_BOX].count = betHeart[bet];
		bar[BAR_BOX].add = 0;
		bar[BAR_BOX].countFrame = 0;

		bar[BAR_BOX].icon = ICON_HEART;
		bar[BAR_BOX].iconFrame = 0;

		bar[BAR_BOX].frame = 0;
		bar[BAR_BOX].frame2 = 0;
		bar[BAR_BOX].aniFrame = 0;
		bar[BAR_BOX].zoom = BAR_BOX_ZOOM;

		bar[BAR_BOX].x = DX / 2;// -79 * _2X;
		//bar[BAR_BOX].y = STATUSWIN_Y + 16 * _2X + BAR_BOTTOMMENUGAP;
		bar[BAR_BOX].y = 80 * _2X + BOTTOMMENUHEIGHT;// +BAR_BOTTOMMENUGAP;

		//bar[BAR_BOX].x = DX / 2 - (float)79 * _2X * bar[BAR_BOX].zoom;
		//bar[BAR_BOX].y = (float)32 * _2X * bar[BAR_BOX].zoom;

		bar[BAR_BOX].targetX = 0;
		bar[BAR_BOX].targetY = 0;

		bar[BAR_BOX].front = false;

		bar[BAR_BOX].drawFunc = BAR_BOX;


		break;
		//case BAR_PLAYERHP:
	default:
		bar[type].active = true;
		bar[type].type = type;

		if (type >= BAR_PLAYERHP && type < BAR_PLAYERHP + MAXPLAYER) {
			bar[type].count = ao[type - BAR_PLAYERHP].hp;
			bar[type].max = ao[type - BAR_PLAYERHP].ps[PS_HP];
			//bar[type].x = 32 * _2X;
			//bar[type].y = Min(STATUSWIN_Y + DIORAMASIZE_Y + HPBARGAP, DY);
			//bar[type].y = STATUSWIN_Y - 30 * _2X;

			bar[type].x = ao[PLAYER + type - BAR_PLAYERHP].x - rx;
			bar[type].owner = PLAYER + type - BAR_PLAYERHP;

		}
		else {
			bar[type].count = robin.enemyObj[GetEnemyBarIdx(ENEMY + type - BAR_ENEMYHP)].hp;
			bar[type].max = robin.enemyObj[GetEnemyBarIdx(ENEMY + type - BAR_ENEMYHP)].maxhp;
			//bar[type].x = DX / 2 + 4 * _2X;
			//bar[type].y = Min(STATUSWIN_Y + DIORAMASIZE_Y + HPBARGAP, DY);
			//bar[type].y = STATUSWIN_Y + 14 * _2X;
			bar[type].x = ao[ENEMY + GetEnemyBarIdx(ENEMY + type - BAR_ENEMYHP)].x - rx;


			bar[type].owner = ENEMY + type - BAR_ENEMYHP;
		}

		//if (BAR_BOTTOMMENUGAP < -32 * _2X)
		//	bar[type].y = STATUSWIN_Y - 32 * _2X + BAR_BOTTOMMENUGAP;
		//else
		bar[type].y = STATUSWIN_Y - 32 * _2X;

		bar[type].add = 0;
		bar[type].countFrame = 0;

		bar[type].icon = ICON_GOLD;
		bar[type].iconFrame = 0;

		bar[type].frame = 0;
		bar[type].frame2 = 0;
		bar[type].aniFrame = 0;

		bar[type].zoom = BAR_PLAYERHP_ZOOM;

		bar[type].targetX = 0;
		bar[type].targetY = 0;

		bar[type].front = false;

		bar[type].drawFunc = type;

		break;
	case BAR_BOSSHP:
		bar[BAR_BOSSHP].active = true;
		bar[BAR_BOSSHP].type = BAR_BOSSHP;

		bar[BAR_BOSSHP].max = GetTotalWaveHp(robin.stage);
		bar[BAR_BOSSHP].add = 0;
		bar[BAR_BOSSHP].countFrame = 0;

		bar[BAR_BOSSHP].icon = ICON_GOLD;
		bar[BAR_BOSSHP].iconFrame = 0;

		bar[BAR_BOSSHP].frame = 0;
		bar[BAR_BOSSHP].frame2 = 0;
		bar[BAR_BOSSHP].aniFrame = 0;

		bar[BAR_BOSSHP].zoom = BAR_BOSSHP_ZOOM;
		bar[BAR_BOSSHP].zoom2 = BAR_BOSSHP_ZOOM;

		bar[BAR_BOSSHP].x = DX + 32 * _2X;
		bar[BAR_BOSSHP].y = BOTTOMMENUHEIGHT + (float)SLOTSIZE_Y * SLOTINITZOOM;//STATUSWIN_Y - 28 * _2X;// +BOSSHPBARHEIGHT;

		bar[BAR_BOSSHP].targetX = DX / 2 - 32 * _2X;
		bar[BAR_BOSSHP].targetY = BOTTOMMENUHEIGHT + (float)SLOTSIZE_Y * SLOTINITZOOM;

		bar[BAR_BOSSHP].zoomEnd = bar[BAR_BOSSHP].zoom;
		bar[BAR_BOSSHP].speed = 8 * _2X;
		bar[BAR_BOSSHP].speedIncrement = 1 * _2X;

		bar[BAR_BOSSHP].targetX2 = DX / 2;
		bar[BAR_BOSSHP].targetY2 = BOTTOMMENUHEIGHT + (float)SLOTSIZE_Y * SLOTINITZOOM;

		bar[BAR_BOSSHP].zoomEnd2 = bar[BAR_BOSSHP].zoom2;
		bar[BAR_BOSSHP].speed2 = 8 * _2X;
		bar[BAR_BOSSHP].speedIncrement2 = 1 * _2X;

		bar[BAR_BOSSHP].frame = 1;

		bar[BAR_BOSSHP].front = false;

		bar[BAR_BOSSHP].drawFunc = BAR_BOSSHP;
		break;
	case BAR_COIN:
		bar[BAR_COIN].active = false;
		bar[BAR_COIN].type = BAR_COIN;

		bar[BAR_COIN].count = 0;
		bar[BAR_COIN].add = 0;
		bar[BAR_COIN].countFrame = 0;

		bar[BAR_COIN].icon = ICON_GOLD;
		bar[BAR_COIN].iconFrame = 0;

		bar[BAR_COIN].frame = 0;
		bar[BAR_COIN].frame2 = 0;
		bar[BAR_COIN].aniFrame = 0;

		bar[BAR_COIN].x = DX / 2;

		bar[BAR_COIN].y = STATUSWIN_Y + DRAWROULETTENUMGAP_SUB;

		bar[BAR_COIN].targetX = 0;
		bar[BAR_COIN].targetY = 0;

		bar[BAR_COIN].front = false;

		bar[BAR_COIN].drawFunc = BAR_COIN;

		bar[BAR_COIN].zoom = BAR_COIN_ZOOM;
		break;
	case BAR_ITEM:
		bar[BAR_ITEM].active = false;
		bar[BAR_ITEM].type = BAR_ITEM;

		bar[BAR_ITEM].count = 0;
		bar[BAR_ITEM].add = 0;
		bar[BAR_ITEM].countFrame = 0;

		bar[BAR_ITEM].icon = 0;
		bar[BAR_ITEM].iconFrame = 0;

		bar[BAR_ITEM].frame = 0;
		bar[BAR_ITEM].frame2 = 0;
		bar[BAR_ITEM].aniFrame = 0;

		bar[BAR_ITEM].x = DX / 2;
		bar[BAR_ITEM].y = STATUSWIN_Y + DRAWROULETTENUMGAP_SUB;

		bar[BAR_ITEM].targetX = 0;
		bar[BAR_ITEM].targetY = 0;

		bar[BAR_ITEM].front = false;

		bar[BAR_ITEM].drawFunc = BAR_ITEM;

		bar[BAR_ITEM].zoom = BAR_ITEM_ZOOM;
		break;
	
	case BAR_CREW:
		bar[BAR_CREW].active = true;
		bar[BAR_CREW].type = BAR_CREW;

		bar[BAR_CREW].count = 0;
		bar[BAR_CREW].add = 0;
		bar[BAR_CREW].countFrame = 0;

		bar[BAR_CREW].icon = 0;
		bar[BAR_CREW].iconFrame = 0;

		bar[BAR_CREW].frame = 0;
		bar[BAR_CREW].frame2 = 0;
		bar[BAR_CREW].aniFrame = 0;

		bar[BAR_CREW].x = MAINMENU_X / 2;
		bar[BAR_CREW].y = BOTTOMMENUHEIGHT - MAINMENU_Y / 2;

		bar[BAR_CREW].targetX = 0;
		bar[BAR_CREW].targetY = 0;

		bar[BAR_CREW].front = false;

		bar[BAR_CREW].drawFunc = BAR_CREW;

		bar[BAR_CREW].zoom = BAR_CREW_ZOOM;
		break;
	case BAR_EQUIP:
		bar[BAR_EQUIP].active = true;
		bar[BAR_EQUIP].type = BAR_EQUIP;

		bar[BAR_EQUIP].count = enemyHouse.gold;
		bar[BAR_EQUIP].add = 0;
		bar[BAR_EQUIP].countFrame = 0;

		bar[BAR_EQUIP].icon = ICON_GOLD;
		bar[BAR_EQUIP].iconFrame = 0;

		bar[BAR_EQUIP].frame = 0;
		bar[BAR_EQUIP].frame2 = 0;
		bar[BAR_EQUIP].aniFrame = 0;

		bar[BAR_EQUIP].zoom = BAR_COLLECTIONS_ZOOM;

		bar[BAR_EQUIP].x = MAINMENU_X + (MAINMENU_X / 2);
		bar[BAR_EQUIP].y = BOTTOMMENUHEIGHT - MAINMENU_Y / 2;

		bar[BAR_EQUIP].targetX = 0;
		bar[BAR_EQUIP].targetY = 0;

		bar[BAR_EQUIP].front = false;

		bar[BAR_EQUIP].drawFunc = BAR_EQUIP;

		break;
	case BAR_HEART:
		bar[BAR_HEART].active = true;
		bar[BAR_HEART].type = BAR_HEART;

		bar[BAR_HEART].count = robin.heart;
		bar[BAR_HEART].add = 0;
		bar[BAR_HEART].countFrame = 0;

		bar[BAR_HEART].icon = ICON_HEART;
		bar[BAR_HEART].iconFrame = 0;

		bar[BAR_HEART].frame = 1;
		bar[BAR_HEART].frame2 = 0;
		bar[BAR_HEART].aniFrame = 0;

		bar[BAR_HEART].x = DX / 2;
		bar[BAR_HEART].y = -64 * _2X; //HEARTBARHEIGHT + STATUSWIN_Y - 28 * _2X;
		
		bar[BAR_HEART].targetX = bar[BAR_HEART].targetX2 = DX / 2;
		bar[BAR_HEART].targetY = bar[BAR_HEART].targetY2 = BOTTOMMENUHEIGHT - 2 * _2X;

		bar[BAR_HEART].speed2 = bar[BAR_HEART].speed = 8 * _2X;
		bar[BAR_HEART].waitingFrame = bar[BAR_HEART].waitingFrame2 = FPS;
		bar[BAR_HEART].zoomIncrement = bar[BAR_HEART].zoomIncrement2 = 0;
		bar[BAR_HEART].zoomEnd = bar[BAR_HEART].zoomEnd2 = BAR_HEART_ZOOM;

		bar[BAR_HEART].front = false;

		bar[BAR_HEART].drawFunc = BAR_HEART;

		bar[BAR_HEART].zoom = BAR_HEART_ZOOM;
		break;
	case BAR_ROULETTE:
		bar[BAR_ROULETTE].active = true;
		bar[BAR_ROULETTE].type = BAR_ROULETTE;

		bar[BAR_ROULETTE].frame = 0;
		bar[BAR_ROULETTE].frame2 = 0;
		bar[BAR_ROULETTE].aniFrame = 0;

		bar[BAR_ROULETTE].x = DX / 2;
		bar[BAR_ROULETTE].y = (float)SLOTSIZE_Y * SLOTINITZOOM + BOTTOMMENUHEIGHT - 2 * _2X; //HEARTBARHEIGHT + STATUSWIN_Y - 28 * _2X;

		bar[BAR_ROULETTE].targetX = 0;
		bar[BAR_ROULETTE].targetY = 0;

		bar[BAR_ROULETTE].front = false;

		bar[BAR_ROULETTE].drawFunc = BAR_ROULETTE;

		bar[BAR_ROULETTE].zoom = BAR_ROULETTE_ZOOM;
		break;
	case BAR_HEARTBET:
		bar[BAR_HEARTBET].active = true;
		bar[BAR_HEARTBET].type = BAR_HEARTBET;

		bar[BAR_HEARTBET].frame = 1;
		bar[BAR_HEARTBET].frame2 = 0;
		bar[BAR_HEARTBET].aniFrame = 0;

		bar[BAR_HEARTBET].x = -128 * _2X;
		bar[BAR_HEARTBET].y = (float)SLOTSIZE_Y * SLOTINITZOOM + BOTTOMMENUHEIGHT + 8 * _2X; //HEARTBARHEIGHT + STATUSWIN_Y - 28 * _2X;

		bar[BAR_HEARTBET].targetX = bar[BAR_HEARTBET].targetX2 = 4 * _2X;
		bar[BAR_HEARTBET].targetY = bar[BAR_HEARTBET].targetY2 = (float)SLOTSIZE_Y * SLOTINITZOOM + BOTTOMMENUHEIGHT + 8 * _2X;

		bar[BAR_HEARTBET].speed2 = bar[BAR_HEARTBET].speed = 8 * _2X;
		bar[BAR_HEARTBET].waitingFrame = bar[BAR_HEARTBET].waitingFrame2 = FPS;
		bar[BAR_HEARTBET].zoomIncrement = bar[BAR_HEARTBET].zoomIncrement2 = 0;
		bar[BAR_HEARTBET].zoomEnd = bar[BAR_HEARTBET].zoomEnd2 = BAR_HEARTBET_ZOOM;

		bar[BAR_HEARTBET].front = false;

		bar[BAR_HEARTBET].drawFunc = BAR_HEARTBET;

		bar[BAR_HEARTBET].zoom = BAR_HEARTBET_ZOOM;
		break;
	case BAR_PLAY:
		bar[BAR_PLAY].active = true;
		bar[BAR_PLAY].type = BAR_PLAY;

		bar[BAR_PLAY].frame = 1;
		bar[BAR_PLAY].frame2 = 0;
		bar[BAR_PLAY].aniFrame = 0;

		bar[BAR_PLAY].x = DX + 128 * _2X;
		bar[BAR_PLAY].y = (float)SLOTSIZE_Y * SLOTINITZOOM + BOTTOMMENUHEIGHT + 12 * _2X; //HEARTBARHEIGHT + STATUSWIN_Y - 28 * _2X;

		bar[BAR_PLAY].targetX = bar[BAR_PLAY].targetX2 = DX - 72 * _2X;
		bar[BAR_PLAY].targetY = bar[BAR_PLAY].targetY2 = (float)SLOTSIZE_Y * SLOTINITZOOM + BOTTOMMENUHEIGHT + 12 * _2X;

		bar[BAR_PLAY].speed2 = bar[BAR_PLAY].speed = 8 * _2X;
		bar[BAR_PLAY].waitingFrame = bar[BAR_PLAY].waitingFrame2 = FPS;
		bar[BAR_PLAY].zoomIncrement = bar[BAR_PLAY].zoomIncrement2 = 0;
		bar[BAR_PLAY].zoomEnd = bar[BAR_PLAY].zoomEnd2 = BAR_PLAY_ZOOM;

		bar[BAR_PLAY].front = false;

		bar[BAR_PLAY].drawFunc = BAR_PLAY;

		bar[BAR_PLAY].zoom = BAR_PLAY_ZOOM;
		break;
	case BAR_JOYSTICK:
		bar[BAR_JOYSTICK].active = true;
		bar[BAR_JOYSTICK].type = BAR_JOYSTICK;

		bar[BAR_JOYSTICK].frame = 1;
		bar[BAR_JOYSTICK].frame2 = 0;
		bar[BAR_JOYSTICK].aniFrame = 0;

		bar[BAR_JOYSTICK].x = -68 * _2X;
		bar[BAR_JOYSTICK].y = (float)SLOTSIZE_Y * SLOTINITZOOM + BOTTOMMENUHEIGHT - 2 * _2X - 128; //HEARTBARHEIGHT + STATUSWIN_Y - 28 * _2X;

		bar[BAR_JOYSTICK].targetX = bar[BAR_JOYSTICK].targetX2 = 48 * _2X;
		bar[BAR_JOYSTICK].targetY = bar[BAR_JOYSTICK].targetY2 = (float)SLOTSIZE_Y * SLOTINITZOOM + BOTTOMMENUHEIGHT - 2 * _2X - 128;

		bar[BAR_JOYSTICK].speed2 = bar[BAR_JOYSTICK].speed = 8 * _2X;
		bar[BAR_JOYSTICK].waitingFrame = bar[BAR_JOYSTICK].waitingFrame2 = FPS;
		bar[BAR_JOYSTICK].zoomIncrement = bar[BAR_JOYSTICK].zoomIncrement2 = 0;
		bar[BAR_JOYSTICK].zoomEnd = bar[BAR_JOYSTICK].zoomEnd2 = BAR_CONTROLER_ZOOM;

		bar[BAR_JOYSTICK].front = false;

		bar[BAR_JOYSTICK].drawFunc = BAR_JOYSTICK;

		bar[BAR_JOYSTICK].zoom = BAR_CONTROLER_ZOOM;
		break;
	case BAR_JUMP:
		bar[BAR_JUMP].active = true;
		bar[BAR_JUMP].type = BAR_JUMP;

		bar[BAR_JUMP].frame = 1;
		bar[BAR_JUMP].frame2 = 0;
		bar[BAR_JUMP].aniFrame = 0;

		bar[BAR_JUMP].x = DX - 100 * _2X;
		bar[BAR_JUMP].y =  - 80 * _2X; //HEARTBARHEIGHT + STATUSWIN_Y - 28 * _2X;

		bar[BAR_JUMP].targetX = bar[BAR_JUMP].targetX2 = DX - 100 * _2X;
		bar[BAR_JUMP].targetY = bar[BAR_JUMP].targetY2 = (float)SLOTSIZE_Y * SLOTINITZOOM + BOTTOMMENUHEIGHT + 12 * _2X - 60 * _2X;
		
		bar[BAR_JUMP].speed2 = bar[BAR_JUMP].speed = 8 * _2X;
		bar[BAR_JUMP].waitingFrame = bar[BAR_JUMP].waitingFrame2 = FPS;
		bar[BAR_JUMP].zoomIncrement = bar[BAR_JUMP].zoomIncrement2 = 0;
		bar[BAR_JUMP].zoomEnd = bar[BAR_JUMP].zoomEnd2 = BAR_JUMP_ZOOM;

		bar[BAR_JUMP].front = false;

		bar[BAR_JUMP].drawFunc = BAR_JUMP;

		bar[BAR_JUMP].zoom = BAR_JUMP_ZOOM;
		break;
	case BAR_BATTLECOIN:
		bar[BAR_BATTLECOIN].active = true;
		bar[BAR_BATTLECOIN].type = BAR_BATTLECOIN;

		bar[BAR_BATTLECOIN].count = 0;
		bar[BAR_BATTLECOIN].add = 0;
		bar[BAR_BATTLECOIN].countFrame = 0;

		bar[BAR_BATTLECOIN].icon = ICON_GOLD;
		bar[BAR_BATTLECOIN].iconFrame = 0;

		bar[BAR_BATTLECOIN].aniFrame = 0;

		bar[BAR_BATTLECOIN].x = ao[NEUTRAL].x;
		bar[BAR_BATTLECOIN].y = STATUSWIN_Y + (rh - 4) * TSIZE - ao[NEUTRAL].y - TSIZE / 4;

		//bar[BAR_BATTLECOIN].targetX = bar[BAR_BATTLECOIN].targetX2 = bar[BAR_BATTLECOIN].x;
		//bar[BAR_BATTLECOIN].targetY = DY - GNBHEIGHT;
		/*
		if (SCREENRATIO <= 150) {
			switch (robin.stage) {
			//case CASTLE_ADELINE:
			//	bar[BAR_BATTLECOIN].targetY = bar[BAR_BATTLECOIN].targetY2 = DY / 2 + 108 * _2X;
			//	break;
			default:
				bar[BAR_BATTLECOIN].targetY = bar[BAR_BATTLECOIN].targetY2 = STATUSWIN_Y + (rh - 4) * TSIZE - ao[ROBIN].y + TSIZE * 4;
				break;
			}
		}
		else
			bar[BAR_BATTLECOIN].targetY = bar[BAR_BATTLECOIN].targetY2 = STATUSWIN_Y + (rh - 4) * TSIZE - ao[ROBIN].y + TSIZE * 4;
		*/
		//bar[BAR_BATTLECOIN].speed = 8 * _2X;
		//bar[BAR_BATTLECOIN].speedIncrement = 1 * _2X;

		bar[BAR_BATTLECOIN].frame = 0;
		bar[BAR_BATTLECOIN].frame2 = 0;

		bar[BAR_BATTLECOIN].front = false;

		bar[BAR_BATTLECOIN].drawFunc = BAR_BATTLECOIN;

		bar[BAR_BATTLECOIN].zoom = bar[BAR_BATTLECOIN].zoom2 = BAR_BATTLECOIN_ZOOM;
		break;
	case BAR_MEDAL:
		bar[BAR_MEDAL].active = false;
		bar[BAR_MEDAL].type = BAR_MEDAL;

		bar[BAR_MEDAL].count = 0;
		bar[BAR_MEDAL].add = 0;
		bar[BAR_MEDAL].countFrame = 0;

		bar[BAR_MEDAL].icon = pvpQuestInfo[robin.pvpQuest * PVPQUESTINFODATASIZE + 0];
		bar[BAR_MEDAL].iconFrame = 0;

		bar[BAR_MEDAL].frame = 0;
		bar[BAR_MEDAL].frame2 = 0;
		bar[BAR_MEDAL].aniFrame = 0;

		bar[BAR_MEDAL].x = DX / 2;
		bar[BAR_MEDAL].y = DY / 2 + 32 * _2X;// STATUSWIN_Y + DRAWROULETTENUMGAP_BATTLE;

		bar[BAR_MEDAL].targetX = 0;
		bar[BAR_MEDAL].targetY = 0;

		bar[BAR_MEDAL].front = false;

		bar[BAR_MEDAL].drawFunc = BAR_MEDAL;

		bar[BAR_MEDAL].zoom = BAR_MEDAL_ZOOM;
		break;
	case BAR_ENEMYUSER:
		bar[BAR_ENEMYUSER].active = true;
		bar[BAR_ENEMYUSER].type = BAR_ENEMYUSER;

		bar[BAR_ENEMYUSER].count = enemyHouse.gold;
		bar[BAR_ENEMYUSER].add = 0;
		bar[BAR_ENEMYUSER].countFrame = 0;

		bar[BAR_ENEMYUSER].icon = ICON_GOLD;
		bar[BAR_ENEMYUSER].iconFrame = 0;

		bar[BAR_ENEMYUSER].frame = 0;
		bar[BAR_ENEMYUSER].frame2 = 0;
		bar[BAR_ENEMYUSER].aniFrame = 0;

		bar[BAR_ENEMYUSER].zoom = BAR_ENEMYUSER_ZOOM;

		bar[BAR_ENEMYUSER].x = xOffset + DX / 2;// -(float)(RAIDGOLDBARWIDTH)*bar[BAR_ENEMYUSER].zoom / 2;//DX - 48 * _2X;// DX / 2 - (float)(RAIDGOLDBARWIDTH)* bar[BAR_ENEMYUSER].zoom / 2;
		bar[BAR_ENEMYUSER].y = STATUSWIN_Y + DIORAMASIZE_Y + 30 * _2X;//(float)(RAIDGOLDBARHEIGHT)*bar[BAR_ENEMYUSER].zoom / 2;

		bar[BAR_ENEMYUSER].targetX = 0;
		bar[BAR_ENEMYUSER].targetY = 0;

		bar[BAR_ENEMYUSER].front = false;

		bar[BAR_ENEMYUSER].drawFunc = BAR_ENEMYUSER;

		break;
	case BAR_ENEMYUSER_BOX:
		bar[BAR_ENEMYUSER_BOX].active = false;
		bar[BAR_ENEMYUSER_BOX].type = BAR_ENEMYUSER_BOX;

		bar[BAR_ENEMYUSER_BOX].count = enemyHouse.gold;
		bar[BAR_ENEMYUSER_BOX].add = 0;
		bar[BAR_ENEMYUSER_BOX].countFrame = 0;

		bar[BAR_ENEMYUSER_BOX].icon = ICON_GOLD;
		bar[BAR_ENEMYUSER_BOX].iconFrame = 0;

		bar[BAR_ENEMYUSER_BOX].frame = 0;
		bar[BAR_ENEMYUSER_BOX].frame2 = 0;
		bar[BAR_ENEMYUSER_BOX].aniFrame = 0;

		bar[BAR_ENEMYUSER_BOX].zoom = BAR_ENEMYUSER_BOX_ZOOM;

		bar[BAR_ENEMYUSER_BOX].x = DX / 2;//DX - 48 * _2X;// DX / 2 - (float)(RAIDGOLDBARWIDTH)* bar[BAR_ENEMYUSER_BOX].zoom / 2;
		bar[BAR_ENEMYUSER_BOX].y = bar[BAR_HEART].y + 48 * _2X;

		bar[BAR_ENEMYUSER_BOX].targetX = 0;
		bar[BAR_ENEMYUSER_BOX].targetY = 0;

		bar[BAR_ENEMYUSER_BOX].front = false;

		bar[BAR_ENEMYUSER_BOX].drawFunc = BAR_ENEMYUSER_BOX;

		break;
	case BAR_CASTLE:
		bar[BAR_CASTLE].active = true;
		bar[BAR_CASTLE].type = BAR_CASTLE;

		bar[BAR_CASTLE].count = 0;
		bar[BAR_CASTLE].add = 0;
		bar[BAR_CASTLE].countFrame = 0;

		bar[BAR_CASTLE].icon = 0;
		bar[BAR_CASTLE].iconFrame = 0;

		bar[BAR_CASTLE].frame = 0;
		bar[BAR_CASTLE].frame2 = 0;
		bar[BAR_CASTLE].aniFrame = 0;

		bar[BAR_CASTLE].x = DX - MAINMENU_X - (MAINMENU_X / 2);//DX - 48 * _2X;// DX / 2 - (float)(RAIDGOLDBARWIDTH)* bar[BAR_MAINSHOP].zoom / 2;
		bar[BAR_CASTLE].y = BOTTOMMENUHEIGHT - MAINMENU_Y / 2;

		bar[BAR_CASTLE].targetX = 0;
		bar[BAR_CASTLE].targetY = 0;

		bar[BAR_CASTLE].front = false;

		bar[BAR_CASTLE].drawFunc = BAR_CASTLE;

		bar[BAR_CASTLE].zoom = BAR_HERO_ZOOM;
		break;
	case BAR_MAINSHOP:
		bar[BAR_MAINSHOP].active = true;
		bar[BAR_MAINSHOP].type = BAR_MAINSHOP;

		bar[BAR_MAINSHOP].count = 0;
		bar[BAR_MAINSHOP].add = 0;
		bar[BAR_MAINSHOP].countFrame = 0;

		bar[BAR_MAINSHOP].icon = MENU_SHOP;
		bar[BAR_MAINSHOP].iconFrame = 0;

		bar[BAR_MAINSHOP].frame = 0;
		bar[BAR_MAINSHOP].frame2 = 0;
		bar[BAR_MAINSHOP].aniFrame = 0;

		bar[BAR_MAINSHOP].zoom = BAR_MAINSHOP_ZOOM;

		bar[BAR_MAINSHOP].x = DX - MAINMENU_X / 2;
		bar[BAR_MAINSHOP].y = BOTTOMMENUHEIGHT - MAINMENU_Y / 2;

		bar[BAR_MAINSHOP].targetX = 0;
		bar[BAR_MAINSHOP].targetY = 0;

		bar[BAR_MAINSHOP].front = false;

		bar[BAR_MAINSHOP].drawFunc = BAR_MAINSHOP;

		break;

	case BAR_DAILYQUEST:
		bar[BAR_DAILYQUEST].active = true;
		bar[BAR_DAILYQUEST].type = BAR_DAILYQUEST;

		bar[BAR_DAILYQUEST].count = enemyHouse.gold;
		bar[BAR_DAILYQUEST].add = 0;
		bar[BAR_DAILYQUEST].countFrame = 0;

		bar[BAR_DAILYQUEST].icon = ICON_GOLD;
		bar[BAR_DAILYQUEST].iconFrame = 0;

		bar[BAR_DAILYQUEST].frame = 0;
		bar[BAR_DAILYQUEST].frame2 = 0;
		bar[BAR_DAILYQUEST].aniFrame = 0;

		bar[BAR_DAILYQUEST].zoom = BAR_DAILYQUEST_ZOOM;

		bar[BAR_DAILYQUEST].x = xOffset + (float)(MAINMENU_X + 4 * _2X) * bar[BAR_DAILYQUEST].zoom / 2;//DX - 48 * _2X;// DX / 2 - (float)(RAIDGOLDBARWIDTH)* bar[BAR_DAILYQUEST].zoom / 2;
		bar[BAR_DAILYQUEST].y = STATUSWIN_Y - 100 * _2X + BAR_BOTTOMMENUGAP;

		bar[BAR_DAILYQUEST].targetX = 0;
		bar[BAR_DAILYQUEST].targetY = 0;

		bar[BAR_DAILYQUEST].front = false;

		bar[BAR_DAILYQUEST].drawFunc = BAR_DAILYQUEST;

		break;
	case BAR_CREWUPGRADE:
		bar[BAR_CREWUPGRADE].active = true;
		bar[BAR_CREWUPGRADE].type = BAR_CREWUPGRADE;

		bar[BAR_CREWUPGRADE].count = enemyHouse.gold;
		bar[BAR_CREWUPGRADE].add = 0;
		bar[BAR_CREWUPGRADE].countFrame = 0;

		bar[BAR_CREWUPGRADE].icon = ICON_GOLD;
		bar[BAR_CREWUPGRADE].iconFrame = 0;

		bar[BAR_CREWUPGRADE].frame = 0;
		bar[BAR_CREWUPGRADE].frame2 = 0;
		bar[BAR_CREWUPGRADE].aniFrame = 0;

		bar[BAR_CREWUPGRADE].zoom = BAR_CREWUPGRADE_ZOOM;

		//bar[BAR_CREWUPGRADE].x = xOffset + (MAINMENU_X + 4 * _2X) + (float)(MAINMENU_X + 4 * _2X) * bar[BAR_CREWUPGRADE].zoom / 2;//DX - 48 * _2X;// DX / 2 - (float)(RAIDGOLDBARWIDTH)* bar[BAR_CREWUPGRADE].zoom / 2;
		bar[BAR_CREWUPGRADE].x = xOffset + DX - (MAINMENU_X + 4 * _2X) - (float)(MAINMENU_X)*bar[BAR_CREWUPGRADE].zoom / 2;//DX - 48 * _2X;// DX / 2 - (float)(RAIDGOLDBARWIDTH)* bar[BAR_EQUIP].zoom / 2;
		bar[BAR_CREWUPGRADE].y = STATUSWIN_Y - 100 * _2X + BAR_BOTTOMMENUGAP;

		bar[BAR_CREWUPGRADE].targetX = 0;
		bar[BAR_CREWUPGRADE].targetY = 0;

		bar[BAR_CREWUPGRADE].front = false;

		bar[BAR_CREWUPGRADE].drawFunc = BAR_CREWUPGRADE;

		break;
	case BAR_FRIENDS:
		bar[BAR_FRIENDS].active = true;
		bar[BAR_FRIENDS].type = BAR_FRIENDS;

		bar[BAR_FRIENDS].count = enemyHouse.gold;
		bar[BAR_FRIENDS].add = 0;
		bar[BAR_FRIENDS].countFrame = 0;

		bar[BAR_FRIENDS].icon = ICON_GOLD;
		bar[BAR_FRIENDS].iconFrame = 0;

		bar[BAR_FRIENDS].frame = 0;
		bar[BAR_FRIENDS].frame2 = 0;
		bar[BAR_FRIENDS].aniFrame = 0;

		bar[BAR_FRIENDS].zoom = BAR_FRIENDS_ZOOM;

		bar[BAR_FRIENDS].x = xOffset + DX - (float)(MAINMENU_X)*bar[BAR_FRIENDS].zoom / 2;//DX - 48 * _2X;// DX / 2 - (float)(RAIDGOLDBARWIDTH)* bar[BAR_FRIENDS].zoom / 2;
		bar[BAR_FRIENDS].y = STATUSWIN_Y - 100 * _2X + BAR_BOTTOMMENUGAP;

		bar[BAR_FRIENDS].targetX = 0;
		bar[BAR_FRIENDS].targetY = 0;

		bar[BAR_FRIENDS].front = false;

		bar[BAR_FRIENDS].drawFunc = BAR_FRIENDS;

		break;
	case BAR_QUEST:
		if (GetEventMenuIdx(EVENTTYPE_QUEST) != -1)
			gEvent = &robin.gameEvent[GetEventMenuIdx(EVENTTYPE_QUEST)];

		//BAR_QUEST,
		bar[BAR_QUEST].active = true;
		bar[BAR_QUEST].type = BAR_QUEST;

		bar[BAR_QUEST].count = robin.questCnt;
		bar[BAR_QUEST].add = 0;
		bar[BAR_QUEST].countFrame = 0;

		if (GetEventMenuIdx(EVENTTYPE_QUEST) != -1) {
			if (gEvent->subType == QUESTTYPE_BATTLE)
				bar[BAR_QUEST].icon = ICON_BATTLE;
			else if (gEvent->subType == QUESTTYPE_RAID)
				bar[BAR_QUEST].icon = ICON_RAID;
			else
				bar[BAR_QUEST].icon = GetItemIcon(questRequestItem[robin.quest * 3 + 0], questRequestItem[robin.quest * 3 + 1], questRequestItem[robin.quest * 3 + 2]); //ICON_SUMMON + questInfo[robin.quest * QUESTINFODATASIZE + robin.subQuest];
		}
		else
			bar[BAR_QUEST].icon = GetItemIcon(questRequestItem[robin.quest * 3 + 0], questRequestItem[robin.quest * 3 + 1], questRequestItem[robin.quest * 3 + 2]); //ICON_SUMMON + questInfo[robin.quest * QUESTINFODATASIZE + robin.subQuest];

		bar[BAR_QUEST].iconFrame = 0;

		bar[BAR_QUEST].frame = 0;
		bar[BAR_QUEST].frame2 = 0;
		bar[BAR_QUEST].aniFrame = 0;

		bar[BAR_QUEST].zoom = BAR_QUEST_ZOOM;

		bar[BAR_QUEST].x = xOffset + DX / 2 - (float)(QUESTBARWIDTH)*bar[BAR_QUEST].zoom / 2;
		bar[BAR_QUEST].y = bar[BAR_BOX].y + 80 * _2X;// +DIORAMASIZE_Y + 64 * _2X;
		//bar[BAR_QUEST].y = STATUSWIN_Y + 28 * _2X + BAR_UPPERMENUGAP / 2;// +DIORAMASIZE_Y + 64 * _2X;
		//bar[BAR_QUEST].y = STATUSWIN_Y + DIORAMASIZE_Y + 64 * _2X + BAR_UPPERMENUGAP / 2;// +DIORAMASIZE_Y + 64 * _2X;

		bar[BAR_QUEST].targetX = 0;
		bar[BAR_QUEST].targetY = 0;

		bar[BAR_QUEST].front = true;

		bar[BAR_QUEST].enemyIcon = true;
		bar[BAR_QUEST].rewardIcon = true;

		bar[BAR_QUEST].drawFunc = BAR_QUEST;
		break;
	case BAR_RAIDGOLD:
		bar[BAR_RAIDGOLD].active = true;
		bar[BAR_RAIDGOLD].type = BAR_RAIDGOLD;

		bar[BAR_RAIDGOLD].count = 0;// enemyHouse.gold;
		bar[BAR_RAIDGOLD].add = 0;
		bar[BAR_RAIDGOLD].countFrame = 0;

		bar[BAR_RAIDGOLD].icon = ICON_GOLD;
		bar[BAR_RAIDGOLD].iconFrame = 0;

		bar[BAR_RAIDGOLD].frame = 0;
		bar[BAR_RAIDGOLD].frame2 = 0;
		bar[BAR_RAIDGOLD].aniFrame = 0;

		bar[BAR_RAIDGOLD].zoom = BAR_RAIDGOLD_ZOOM;

		bar[BAR_RAIDGOLD].x = xOffset + DX / 2;//DX - 48 * _2X;// DX / 2 - (float)(RAIDGOLDBARWIDTH)* bar[BAR_RAIDGOLD].zoom / 2;
		bar[BAR_RAIDGOLD].y = STATUSWIN_Y + DIORAMA_BATTLE_GAPY + 48 * _2X;

		bar[BAR_RAIDGOLD].targetX = 0;
		bar[BAR_RAIDGOLD].targetY = 0;

		bar[BAR_RAIDGOLD].front = false;

		bar[BAR_RAIDGOLD].drawFunc = BAR_RAIDGOLD;

		break;
	case BAR_RAIDCOIN:
		bar[BAR_RAIDCOIN].active = false;
		bar[BAR_RAIDCOIN].type = BAR_RAIDCOIN;

		bar[BAR_RAIDCOIN].count = 0;
		bar[BAR_RAIDCOIN].add = 0;
		bar[BAR_RAIDCOIN].countFrame = 0;

		bar[BAR_RAIDCOIN].icon = ICON_GOLD;
		bar[BAR_RAIDCOIN].iconFrame = 0;

		bar[BAR_RAIDCOIN].frame = 0;
		bar[BAR_RAIDCOIN].frame2 = 0;
		bar[BAR_RAIDCOIN].aniFrame = 0;

		bar[BAR_RAIDCOIN].x = DX / 2;

		bar[BAR_RAIDCOIN].y = STATUSWIN_Y2 + 28 * _2X;

		bar[BAR_RAIDCOIN].targetX = 0;
		bar[BAR_RAIDCOIN].targetY = 0;

		bar[BAR_RAIDCOIN].front = false;

		bar[BAR_RAIDCOIN].drawFunc = BAR_RAIDCOIN;

		bar[BAR_RAIDCOIN].zoom = 1.2f;
		break;
	case BAR_STAR:
		bar[BAR_STAR].active = true;
		bar[BAR_STAR].type = BAR_STAR;

		bar[BAR_STAR].count = 0;
		bar[BAR_STAR].add = 0;
		bar[BAR_STAR].countFrame = 0;

		bar[BAR_STAR].icon = ICON_STAR;
		bar[BAR_STAR].iconFrame = 0;

		bar[BAR_STAR].frame = 0;
		bar[BAR_STAR].frame2 = 0;
		bar[BAR_STAR].aniFrame = 0;

		bar[BAR_STAR].x = CROWNBARWIDTH + 2 * _2X + GOLDBARWIDTH + 2 * _2X;
		bar[BAR_STAR].y = DY - (GNBHEIGHT - GNB_INIT_HEIGHT);

		//bar[BAR_STAR].x = DX / 2;
		//bar[BAR_STAR].y = DY / 2 + DIORAMASIZE_Y / 2 * DEFAULTZOOM - DIORAMASIZE_Y * DEFAULTZOOM + 87 * _2X;

		bar[BAR_STAR].targetX = 0;
		bar[BAR_STAR].targetY = 0;

		bar[BAR_STAR].front = false;

		bar[BAR_STAR].drawFunc = BAR_STAR;

		bar[BAR_STAR].zoom = BAR_STAR_ZOOM;
		break;
	case BAR_COMBATPOWERALL:
		bar[BAR_COMBATPOWERALL].active = true;
		bar[BAR_COMBATPOWERALL].type = BAR_COMBATPOWERALL;

		bar[BAR_COMBATPOWERALL].count = 0;
		bar[BAR_COMBATPOWERALL].add = 0;
		bar[BAR_COMBATPOWERALL].countFrame = 0;

		bar[BAR_COMBATPOWERALL].icon = ICON_EVENT_2SWORD;
		bar[BAR_COMBATPOWERALL].iconFrame = 0;

		bar[BAR_COMBATPOWERALL].frame = 0;
		bar[BAR_COMBATPOWERALL].frame2 = 0;
		bar[BAR_COMBATPOWERALL].aniFrame = 0;

		bar[BAR_COMBATPOWERALL].x = CROWNBARWIDTH + 2 * _2X + GOLDBARWIDTH + 2 * _2X;
		bar[BAR_COMBATPOWERALL].y = DY - (GNBHEIGHT - GNB_INIT_HEIGHT);

		//bar[BAR_COMBATPOWERALL].x = DX / 2;
		//bar[BAR_COMBATPOWERALL].y = DY / 2 + DIORAMASIZE_Y / 2 * DEFAULTZOOM - DIORAMASIZE_Y * DEFAULTZOOM + 87 * _2X;

		bar[BAR_COMBATPOWERALL].targetX = 0;
		bar[BAR_COMBATPOWERALL].targetY = 0;

		bar[BAR_COMBATPOWERALL].front = false;

		bar[BAR_COMBATPOWERALL].drawFunc = BAR_COMBATPOWERALL;

		bar[BAR_COMBATPOWERALL].zoom = BAR_COMBATPOWERALL_ZOOM;
		break;
	case BAR_COMBATPOWER:
		bar[BAR_COMBATPOWER].active = true;
		bar[BAR_COMBATPOWER].type = BAR_COMBATPOWER;

		bar[BAR_COMBATPOWER].count = 0;
		bar[BAR_COMBATPOWER].add = 0;
		bar[BAR_COMBATPOWER].countFrame = 0;

		bar[BAR_COMBATPOWER].icon = ICON_EVENT_2SWORD;
		bar[BAR_COMBATPOWER].iconFrame = 0;

		bar[BAR_COMBATPOWER].frame = 0;
		bar[BAR_COMBATPOWER].frame2 = 0;
		bar[BAR_COMBATPOWER].aniFrame = 0;

		bar[BAR_COMBATPOWER].x = CROWNBARWIDTH + GOLDBARWIDTH + 4 * _2X;
		bar[BAR_COMBATPOWER].y = GNBHEIGHT - GNB_INIT_HEIGHT;

		//bar[BAR_COMBATPOWER].x = DX / 2;
		//bar[BAR_COMBATPOWER].y = DY / 2 + DIORAMASIZE_Y / 2 * DEFAULTZOOM - DIORAMASIZE_Y * DEFAULTZOOM + 87 * _2X;

		bar[BAR_COMBATPOWER].targetX = 0;
		bar[BAR_COMBATPOWER].targetY = 0;

		bar[BAR_COMBATPOWER].front = false;

		bar[BAR_COMBATPOWER].drawFunc = BAR_COMBATPOWER;

		bar[BAR_COMBATPOWER].zoom = BAR_COMBATPOWER_ZOOM;
		break;
	case BAR_STAGEPROGRESS:
		bar[BAR_STAGEPROGRESS].active = true;
		bar[BAR_STAGEPROGRESS].type = BAR_STAGEPROGRESS;

		bar[BAR_STAGEPROGRESS].count = 0;
		bar[BAR_STAGEPROGRESS].add = 0;
		bar[BAR_STAGEPROGRESS].countFrame = 0;

		bar[BAR_STAGEPROGRESS].icon = ICON_EVENT_2SWORD;
		bar[BAR_STAGEPROGRESS].iconFrame = 0;

		bar[BAR_STAGEPROGRESS].frame = 0;
		bar[BAR_STAGEPROGRESS].frame2 = 0;
		bar[BAR_STAGEPROGRESS].aniFrame = 0;

		bar[BAR_STAGEPROGRESS].x = DX / 2 - STAGEPROGRESSBARWIDTH / 2;
		bar[BAR_STAGEPROGRESS].y = STATUSWIN_Y;

		bar[BAR_STAGEPROGRESS].targetX = 0;
		bar[BAR_STAGEPROGRESS].targetY = 0;

		bar[BAR_STAGEPROGRESS].front = true;

		bar[BAR_STAGEPROGRESS].drawFunc = BAR_STAGEPROGRESS;

		bar[BAR_STAGEPROGRESS].zoom = BAR_STAGEPROGRESS_ZOOM;
		break;
	case BAR_REMAINEDTURN:
		bar[BAR_REMAINEDTURN].active = true;
		bar[BAR_REMAINEDTURN].type = BAR_REMAINEDTURN;

		bar[BAR_REMAINEDTURN].count = 0;
		bar[BAR_REMAINEDTURN].add = 0;
		bar[BAR_REMAINEDTURN].countFrame = 0;

		bar[BAR_REMAINEDTURN].icon = false;
		bar[BAR_REMAINEDTURN].iconFrame = 0;

		bar[BAR_REMAINEDTURN].frame = 0;
		bar[BAR_REMAINEDTURN].frame2 = 0;
		bar[BAR_REMAINEDTURN].aniFrame = 0;

		bar[BAR_REMAINEDTURN].x = DX / 2 + HEARTBARWIDTH / 2 + 64 * _2X;
		bar[BAR_REMAINEDTURN].y = bar[BAR_HEART].y + BOSSHPBARHEIGHT + 48 * _2X;

		bar[BAR_REMAINEDTURN].targetX = 0;
		bar[BAR_REMAINEDTURN].targetY = 0;

		bar[BAR_REMAINEDTURN].front = true;

		bar[BAR_REMAINEDTURN].drawFunc = BAR_REMAINEDTURN;

		bar[BAR_REMAINEDTURN].zoom = BAR_REMAINEDTURN_ZOOM;
		break;
	case BAR_INVENTORY:
	case BAR_INVENTORY + 1:
	case BAR_INVENTORY + 2:
		bar[type].active = true;
		bar[type].type = type;

		bar[type].count = 0;
		bar[type].add = 0;
		bar[type].countFrame = 0;

		bar[type].icon = ICON_EVENT_2SWORD;
		bar[type].iconFrame = 0;

		bar[type].frame = 0;
		bar[type].frame2 = 0;
		bar[type].aniFrame = 0;

		bar[type].zoom = BAR_INVENTORY_ZOOM;
		showHeroCnt = heroCnt = GetHeroCnt();
		switch (heroCnt) {
		case 1:
			bar[type].x = DX - 107 * _2X - (float)(INVENTORYBAR_WIDTH + 8 * _2X) * (GetHeroIdx(type - BAR_INVENTORY) + 1) * bar[type].zoom;
			break;
		case 2:
			bar[type].x = DX - 52 * _2X - (float)(INVENTORYBAR_WIDTH + 8 * _2X) * (GetHeroIdx(type - BAR_INVENTORY) + 1) * bar[type].zoom;
			break;
		case 3:
			bar[type].x = DX - (float)(INVENTORYBAR_WIDTH + 8 * _2X) * (GetHeroIdx(type - BAR_INVENTORY) + 1) * bar[type].zoom;
			break;
		}

		bar[type].y = STATUSWIN_Y + (float)(INVENTORYBAR_HEIGHT - 84 * _2X) * bar[type].zoom;// +BAR_BOTTOMMENUGAP;

		bar[type].targetX = 0;
		bar[type].targetY = 0;

		bar[type].front = true;
		bar[type].drawFunc = type;

		bar[type].owner = type - BAR_INVENTORY;
		break;
	case BAR_SKILL:
	case BAR_SKILL + 1:
	case BAR_SKILL + 2:
		bar[type].active = true;
		bar[type].type = type;

		bar[type].count = 0;
		bar[type].add = 0;
		bar[type].countFrame = 0;

		bar[type].icon = ICON_EVENT_2SWORD;
		bar[type].iconFrame = 0;

		bar[type].frame = 0;
		bar[type].frame2 = 0;
		bar[type].aniFrame = 0;

		bar[type].zoom = BAR_SKILL_ZOOM;
		showHeroCnt = heroCnt = GetHeroCnt();

		switch (heroCnt) {
		case 1:
			bar[type].x = DX + DX - (float)112 * _2X * bar[type].zoom - (float)(QUICKSLOTGAP + 8 * _2X) * (GetHeroIdx(type - BAR_SKILL) + 1) * bar[type].zoom;
			break;
		case 2:
			bar[type].x = DX + DX - (float)66 * _2X * bar[type].zoom - (float)(QUICKSLOTGAP + 8 * _2X) * (GetHeroIdx(type - BAR_SKILL) + 1) * bar[type].zoom;
			break;
		case 3:
			bar[type].x = DX + DX - (float)20 * _2X * bar[type].zoom - (float)(QUICKSLOTGAP + 8 * _2X) * (GetHeroIdx(type - BAR_SKILL) + 1) * bar[type].zoom;
			break;
		}

		bar[type].y = STATUSWIN_Y + (float)(INVENTORYBAR_HEIGHT - 10 * _2X) * bar[BAR_INVENTORY + type - BAR_SKILL].zoom;// +BAR_BOTTOMMENUGAP;

		bar[type].targetX = 0;
		bar[type].targetY = 0;

		bar[type].front = true;

		bar[type].drawFunc = type;
		bar[type].owner = type - BAR_SKILL;
		break;
	case BAR_DAY:
		bar[type].active = true;
		bar[type].x = DX + 32 * _2X;  // 왕관 옆
		bar[type].y = STATUSWIN_Y;
		bar[type].count = robin.currentDay;
		bar[type].drawFunc = BAR_DAY;
		bar[type].front = true;
		bar[type].zoom = 0.5f;
		bar[type].zoom2 = 0.5f;

		//bar[type].zoom = 2.0f;
		//bar[type].zoom2 = 1.0f;

		bar[type].targetX2 = bar[type].targetX = DX - 32 * _2X;
		bar[type].targetY2 = bar[type].targetY = bar[type].y;

		//bar[type].zoomEnd = 1.0f;
		//bar[type].zoomEnd2 = 0.6f;
		bar[type].zoomEnd = 0.5f;
		bar[type].zoomEnd2 = 0.5f;

		bar[type].speed = 8 * _2X;
		bar[type].speed2 = 16 * _2X;

		bar[type].speedIncrement = 0.1f;
		bar[type].speedIncrement2 = 0.1f;

		bar[type].zoomIncrement = -0.1f;
		bar[type].zoomIncrement2 = -0.01f;

		bar[type].waitingFrame = FPS;
		bar[type].waitingFrame2 = FPS;

		bar[type].frame = 1;

		bar[type].front = false;

		break;
	case BAR_WAVE:
		bar[type].active = true;
		bar[type].x = DX + 32 * _2X;  // 왕관 옆
		bar[type].y = DY - GNBHEIGHT - 32 * _2X;
		bar[type].count = robin.curWaveIdx;
		bar[type].drawFunc = BAR_WAVE;
		bar[type].front = true;
		bar[type].zoom = 0.5f;
		bar[type].zoom2 = 0.5f;

		//bar[type].zoom = 2.0f;
		//bar[type].zoom2 = 1.0f;

		bar[type].targetX2 = bar[type].targetX = DX - 32 * _2X;
		bar[type].targetY2 = bar[type].targetY = bar[type].y;

		//bar[type].zoomEnd = 1.0f;
		//bar[type].zoomEnd2 = 0.6f;
		bar[type].zoomEnd = 0.5f;
		bar[type].zoomEnd2 = 0.5f;

		bar[type].speed = 8 * _2X;
		bar[type].speed2 = 16 * _2X;

		bar[type].speedIncrement = 0.1f;
		bar[type].speedIncrement2 = 0.1f;

		bar[type].zoomIncrement = -0.1f;
		bar[type].zoomIncrement2 = -0.01f;

		bar[type].waitingFrame = FPS;
		bar[type].waitingFrame2 = FPS;

		bar[type].frame = 1;

		bar[type].front = false;
		break;

	}


}

void InitStatue(OBJECT* pObj)
{
	pObj->canRun = false;
	pObj->canDown = false;
	pObj->canPush = false;
	pObj->canSwim = 1;
	pObj->canMagma = false;
	pObj->canSled = false;
	pObj->canOnWater = false;
	pObj->canMagnet = false;
	pObj->canBreak = false;
	pObj->canJumpTwice = false;
	pObj->canOnThorn = false;
	pObj->canGlide = false;
	pObj->canSuperJump = false;
	pObj->canSpace = false;

	switch (pObj->inTile) {
	default:
		pObj->canBreath = true;
		break;
	case WATER:
	case SWAMP:
		pObj->canBreath = robin.statue[ITEM_STATUE_MERMAID];
		break;
	case SPACE:
		pObj->canBreath = robin.statue[ITEM_STATUE_SPIRIT];
		break;
	}

	//질풍의 상
//	if (robin.statue[ITEM_STATUE_WIND])
//#ifdef CONTROL_MANUAL
//		if (!(GetObjFromPtr(pObj) == PLAYER && (keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID)))

//#endif
//		pObj->canRun = true;

	//파괴의 상
	if (robin.statue[ITEM_STATUE_DESTRUCT])
		pObj->canDown = true;

	//완력의 상
	if (robin.statue[ITEM_STATUE_POWER])
		pObj->canPush = true;

	//인어의 상
	if (robin.statue[ITEM_STATUE_MERMAID])
		pObj->canSwim = true;

	//불꽃의 상
	if (robin.statue[ITEM_STATUE_FLAME])
		pObj->canMagma = true;

	//펭귄의 상
	if (robin.statue[ITEM_STATUE_PENGUIN])
		pObj->canSled = true;

	//얼음의 상
	if (robin.statue[ITEM_STATUE_ICE])
		pObj->canOnWater = true;

	//번개의 상

	//태양의 상
	if (robin.statue[ITEM_STATUE_SUN])
		pObj->canBreak = true;

	//토끼의 상
	if (robin.statue[ITEM_STATUE_RABBIT])
		pObj->canJumpTwice = true;

	//골렘의 상
	if (robin.statue[ITEM_STATUE_GOLEM])
		pObj->canOnThorn = true;

	//차원의 상

	//독수리의 상
	if (robin.statue[ITEM_STATUE_EAGLE])
		pObj->canGlide = true;

	//다람쥐의 상

	//드래곤의 상
	if (robin.statue[ITEM_STATUE_DRAGON])
		pObj->canSuperJump = true;

	//영혼의 상
	if (robin.statue[ITEM_STATUE_SPIRIT])
		pObj->canSpace = true;
}

void InitReward(void)
{
	int i;

	memset(&rewardItem, 0, sizeof(ITEM) * MAXREWARDITEM * 2);//메인 리워드 아이템
	rewardItemCnt = 0;//현재 획득된 아이템
	curRewardItem = 0;//현재 획득진행중에 있는 아이템
	focusedItem = 0;
	rewardIndex = 0;
}

void InitCalendar(void)
{

	InitCalendarWeek();
	robin.calendarMonthDay = 0;
}

void InitCalendarWeek(void)
{
	int i;
	robin.calendarTimeStamp = MC_knlCurrentTimeStamp();

	for (i = 0; i < WEEK; i++) {
		robin.calendarDayStatus[i] = CALENDAR_REWARDSTATUS_NONE;
	}

	robin.calendarDayStatus[MONDAY] = CALENDAR_REWARDSTATUS_NOTYET;
}

//획득한 아이템의 개수를 인자로 받는다. 
void SetPvpQuestReward(int getPvpQuestItemCnt)
{
	int start = robin.pvpQuestCnt;
	int end = start + getPvpQuestItemCnt;
	int i = 0;
	int pvpQuest = robin.pvpQuest;
	int pvpSubQuest = robin.pvpSubQuest;
	int pvpDetailQuest = robin.pvpDetailQuest;

	//보상을 초기화 시키고
	InitReward();
	//
	if (pvpQuestRequest[pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + pvpSubQuest * TOTALPVPDETAILREQUEST + pvpDetailQuest + i] <= end) {
		start = pvpQuestRequest[pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + pvpSubQuest * TOTALPVPDETAILREQUEST + pvpDetailQuest + i];

		do {
			if (start <= end) {
				rewardItem[rewardItemCnt].type = pvpQuestReward[(pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + pvpSubQuest * TOTALPVPDETAILREQUEST + pvpDetailQuest + i) * PVPQUESTDATASIZE + 0];
				rewardItem[rewardItemCnt].detail = pvpQuestReward[(pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + pvpSubQuest * TOTALPVPDETAILREQUEST + pvpDetailQuest + i) * PVPQUESTDATASIZE + 1];
				rewardItem[rewardItemCnt].grade = pvpQuestReward[(pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + pvpSubQuest * TOTALPVPDETAILREQUEST + pvpDetailQuest + i) * PVPQUESTDATASIZE + 2];
				rewardItem[rewardItemCnt].count = pvpQuestReward[(pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + pvpSubQuest * TOTALPVPDETAILREQUEST + pvpDetailQuest + i) * PVPQUESTDATASIZE + 3];
				rewardItemCnt++;
				i++;

				if (pvpDetailQuest + i >= TOTALPVPDETAILREQUEST) {
					pvpSubQuest++;
					pvpDetailQuest = 0;
					i = 0;

					//모든 퀘스트를 클리어
					if (pvpSubQuest == TOTALPVPSUBQUEST) {
						break;
					}
				}

				start = pvpQuestRequest[pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + pvpSubQuest * TOTALPVPDETAILREQUEST + pvpDetailQuest + i];
			}
		} while (start <= end);
	}

	robin.remainPvpQuestItem = getPvpQuestItemCnt;
	robin.thisTimePvpQuestItem = Min(robin.remainPvpQuestItem, (pvpQuestRequest[robin.pvpQuest * TOTALPVPSUBQUEST * TOTALPVPDETAILREQUEST + robin.pvpSubQuest * TOTALPVPDETAILREQUEST + robin.pvpDetailQuest] - robin.pvpQuestCnt));

}
//획득한 아이템의 개수를 인자로 받는다.
void SetQuestReward(int getQuestItemCnt)
{
	int start = robin.questCnt;
	int end = start + getQuestItemCnt;
	int i = 0;
	int quest = robin.quest;
	int subQuest = robin.subQuest;

	InitReward();
	//한번에 획득할 모든 퀘스트 이미지를 처리한다.

	if (questRequestItemCnt[quest * TOTALSUBQUEST + subQuest + i] <= end) {
		start = questRequestItemCnt[quest * TOTALSUBQUEST + subQuest + i];

		do {
			if (start <= end) {
				rewardItem[rewardItemCnt].type = questReward[quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (subQuest + i) * QUESTREWARDDATASIZE + 0];
				rewardItem[rewardItemCnt].detail = questReward[quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (subQuest + i) * QUESTREWARDDATASIZE + 1];
				rewardItem[rewardItemCnt].grade = questReward[quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (subQuest + i) * QUESTREWARDDATASIZE + 2];
				rewardItem[rewardItemCnt].count = questReward[quest * TOTALSUBQUEST * QUESTREWARDDATASIZE + (subQuest + i) * QUESTREWARDDATASIZE + 3];
				rewardItemCnt++;
				i++;

				if (subQuest + i >= TOTALSUBQUEST) {
					break;
				}

				start = questRequestItemCnt[quest * TOTALSUBQUEST + subQuest + i];
			}
		} while (start <= end);
	}

	robin.remainQuestItem = getQuestItemCnt;
	robin.thisTimeQuestItem = Min(robin.remainQuestItem, (questRequestItemCnt[quest * TOTALSUBQUEST + subQuest] - robin.questCnt));

}


//현재 이 아이템을 인벤토리에 넣을 수 있는지 없는지 확인하는 함수
//return 값이 -1이면 소지개수 초과, 0이면 인벤토리가 가득차고, 1이면 넣을수 있음
int InsertItemTest(int type, int detail, int cnt)
{
	int i, j = -1;

	switch (type) {
		//무조건 받을 수 있는것
	case ITEM_GOLD:
	case ITEM_KEY:
	case ITEM_STATUE:
		return true;

		//갯수가 중첩되는것
	case ITEM_WASTE:
	case ITEM_IRON:
	case ITEM_LEATHER:
	case ITEM_CLOTH:
	case ITEM_WOOD:
	case ITEM_ESSENCE:
	case ITEM_QUEST:
		//해당아이템이 있는지 검사
		for (i = 0; i < robin.maxInven; i++) {
			if (robin.inven[i].type == type && robin.inven[i].detail == detail) {
				j = i;
				break;
			}
		}
		//만약 이미 그 아이템을 가지고 있다면
		if (j != -1) {
			//만약 아이템의 갯수가 9999 개 까지는
			if (robin.inven[i].count + cnt < 10000)
				return true;
			else
				return -1;
		}
		else {
			for (i = 0; i < robin.maxInven; i++) {
				if (robin.inven[i].type == EMPTY) {
					break;
				}
			}
			//만약 빈인벤토리가 있으면
			if (i < robin.maxInven)
				return true;
			else
				return false;
		}
		break;
		//갯수가 중첩되지 않는것
	default:
		for (i = 0; i < robin.maxInven; i++) {
			if (robin.inven[i].type == EMPTY) {
				break;
			}
		}
		//만약 빈인벤토리가 있으면
		if (i < robin.maxInven)
			return true;
		else
			return false;
		break;
	}
}

void NewGame(void)
{
	int i, j, k;
	ITEM* it;

	InitGame();

	memset(&robin, 0, sizeof(ROBINDATA));

	robin.startTime = GetCurrentTimeMs();

	robin.stage = 0;
	robin.room = 0;

	SaveFlag(2);

	isDemo = false;

	robin.count = 0;
	memset(robin.inven, 0, sizeof(robin.inven));

	for (i = 0; i < TOTALINVENTORY; i++) {
		robin.inven[i].type = EMPTY;
		for (j = 0; j < 12; j++)
			robin.inven[i].option[j][0] = EMPTYINT;
		for (j = 0; j < 6; j++)
			robin.inven[i].socket[j] = EMPTYINT;
	}

	k = 0;
	for (i = 0; i < EQUIP_NECK; i++) {
		for (j = 0; j < (itemStartCnt[i * TOTALCHAR + 1] - itemStartCnt[i * TOTALCHAR]); j++) {
			MakeItem(&robin.inven[robin.count], i * TOTALCHAR, 0, 0, j, false);
			robin.inven[robin.count].count = 1;
			robin.inven[robin.count].lv = 1;
			robin.count++;
		}
	}

	for (i = 0; i < TOTAL_CREW; i++) {
		MakeItem(&robin.inven[robin.count], ITEM_CREW, 0, 0, i, false);
		robin.inven[robin.count].count = 1;
		robin.inven[robin.count].lv = 1;
		robin.count++;
	}

	//무기하나 주기
	//MakeItem(&robin.inven[0], ITEM_SWORD, 0, 0, 0, false);
	//robin.inven[0].count = 1;
	//robin.count++;

	robin.lv = 0;
	robin.exps = 0;

	//초기 장비 주기
	for (i = ROBIN; i < TOTALPLAYER; i++) {
		ao[i].type = ao[i].cmf = i;
		ao[i].name = TEXT_NICKNAME + Random(100);

		InitStat(&ao[i]);

		for (j = 0; j < TOTALEQUIP; j++) {
			ao[i].equip[j].type = EMPTY;
			for (k = 0; k < 12; k++)
				ao[i].equip[i].option[j][0] = EMPTYINT;
			for (k = 0; k < 6; k++)
				ao[i].equip[i].socket[j] = EMPTYINT;
		}

		switch (i) {
		case ROBIN:
			robin.inven[GetInvenIdx(ITEM_SWORD, ITEM_SWORD_STICK, GRADE_NORMAL)].lv = 1;
			EquipItem(&ao[i], &robin.inven[GetInvenIdx(ITEM_SWORD, ITEM_SWORD_STICK, GRADE_NORMAL)]);
			//MakeItem(&ao[i].equip[EQUIP_WEAPON], ITEM_SWORD, 1, GRADE_NORMAL, ITEM_SWORD_STICK, 0);
			break;
		case DIANA:
			robin.inven[GetInvenIdx(ITEM_GUN, ITEM_GUN_PISTOL, GRADE_NORMAL)].lv = 1;
			EquipItem(&ao[i], &robin.inven[GetInvenIdx(ITEM_GUN, ITEM_GUN_PISTOL, GRADE_NORMAL)]);
			//MakeItem(&ao[i].equip[EQUIP_WEAPON], ITEM_GUN, 1, GRADE_NORMAL, ITEM_GUN_PISTOL, 0);
			break;
		case MAXX:
			robin.inven[GetInvenIdx(ITEM_BOOMERANG, ITEM_BOOMERANG_BOOMERANG, GRADE_NORMAL)].lv = 1;
			EquipItem(&ao[i], &robin.inven[GetInvenIdx(ITEM_BOOMERANG, ITEM_BOOMERANG_BOOMERANG, GRADE_NORMAL)]);
			//MakeItem(&ao[i].equip[EQUIP_WEAPON], ITEM_BOOMERANG, 1, GRADE_NORMAL, ITEM_BOOMERANG_BOOMERANG, 0);
			break;
		}

		RefreshStat(&ao[i]);
		ao[i].exps = 0;

		if (i == ROBIN)
			ao[i].lv = 1;
		else
			ao[i].lv = 0;

		ao[i].hp = ao[i].ps[PS_HP];
		ao[i].mp = ao[i].ps[PS_MP];

		ao[i].x = LOBBYPOSITION_X - i * TSIZE;
		ao[i].y = (rh - 7) * TSIZE;

		ao[i].dirF = RIGHT;

		ao[i].inTile = GROUND;
		ao[i].dirY = DOWN;
		ao[i].drawHandler = PLAYERDRAW;
		ao[i].moveHandler = PLAYERMOVE;
		//[i].moveHandler = NPCMOVE;
		//ao[i].moveHandler = NULL;
		//ao[i].active = false;
		ao[i].zoom = LOBBYZOOM;
		ao[i].O2 = OXYGEN;

		InitMotion(&ao[i]);

		InitStatue(&ao[i]);

		//for (j = 0; j < 6; j++) {
		//	ao[i].getSkillList[j] = skillInitData[3 * j + 0];
		//}

		memcpy((char*)&robin.charData[i].equip, &ao[i].equip, sizeof(ITEM) * TOTALEQUIP);
	}

	robin.heroesSetting[ROBIN] = true;
	robin.heroesSetting[DIANA] = false;
	robin.heroesSetting[MAXX] = false;

	robin.heart = GetInitHeart();
	robin.heartTimeStamp = MC_knlCurrentTimeStamp();

	robin.maxInven = option.maxInven;//현재 인벤토리의 최대 아이템 크기

	//포션3개주기
	//GetItem(ITEM_WASTE, 0, ITEM_WASTE_STAR, 0, 3, 0);

	npcGetFrame = 0;
	stageClearFrame = 0;
	skillGetFrame = 0;
	buffItemFrame = 0;

	//robin.buyHouse[0] = true;

	robin.statue[ITEM_STATUE_DESTRUCT] = false;
	robin.statue[ITEM_STATUE_RABBIT] = false;
	robin.statue[ITEM_STATUE_EAGLE] = false;
	robin.statue[ITEM_STATUE_DRAGON] = false;
	InitStatue(&ao[PLAYER]);

	//memset(robin.soulCheck, true, sizeof(robin.soulCheck));

	//robin.gold = 1000;
	//robin.medal = 0;
	//robin.coin = 1000;
	//robin.hammer = 1000;

	//mapSeenCount = 50;
	//for (i = 0; i < 4; i++) {
	//	robin.crew[i] = true;
	//	robin.crewTime[i] = 0;
	//	robin.crewTimeStamp[i] = MC_knlCurrentTimeStamp();
	//}

	//robin.nickname = to_string(MC_knlCurrentTimeStamp());

	bet = 2;

	robin.quest = 0;
	robin.subQuest = 0;
	robin.questTimeStamp = MC_knlCurrentTimeStamp();

	//robin.shield = GetMaxShield();
	robin.shield = 0;

	//이벤트 세팅
	robin.eventCnt = 0;

	for (i = 0; i < TOTAL_MENU; i++)
		robin.openedMenu[i] = menuOpened[i];

	robin.calendarTimeStamp = MC_knlCurrentTimeStamp();
	robin.freeRewardTimeStamp = MC_knlCurrentTimeStamp();

	option.bgm = true;
	option.se = true;
	option.effect = true;
	option.voice = false;
	option.maxInven = STARTINVENTORY;

	option.gameControl = CONTROL_AUTO;
	option.gameSpeed = FPS;
	option.macro = false;
	option.vibration = false;

	SaveOption();

	memcpy(&ao[SOLDIER], &ao[PLAYER], sizeof(OBJECT));
	ao[SOLDIER].active = false;

	crewInitializeFrame = 1;
	for (i = 0; i < TOTALCONTROLMARK; i++)
		controlerSpread[i] = true;

	//SetBossObj();
	SetEnemyUser();
	//SetStageHouse();

	InitMenu();
	InitCalendar();

	actionCardCnt = 0;

	robin.curWaveIdx = 0;
	memset(&robin.waveActive, 0, sizeof(robin.waveActive));
	robin.waveTimeStamp = MC_knlCurrentTimeStamp();//여기서 웨이브 시작 시간을 정해주고


	option.gameControl = CONTROL_MANUAL;
	robin.castle = 0;
	robinmap = MAP_DIORAMA_TOLEM + castleOrder[robin.castle];
#ifdef GAMEDEBUG
	//robin.gold = 1000000;
	robin.gold = 0;

#endif
	// NewGame() 또는 InitRobin() 함수 내부에 추가
	robin.currentDay = 1;           // Day 1부터 시작
	robin.lifeRemaining = 3;        // 3일의 수명

	//crewCnt = MAXCREW;

	for (i = 0; i < crewCnt; i++)
		robin.slotCrew[i] = -1;
	
	robin.slotCrew[0] = NPC_SEBASTIAN;

	//robin.slotCrew[1] = NPC_UNCLE;
	//robin.slotCrew[2] = NPC_AUNT;
	//robin.slotCrew[3] = NPC_ADELKNIGHT;
	//robin.slotCrew[4] = NPC_NOBLEMAN;
	//robin.slotCrew[5] = NPC_SEBASTIAN;

#ifdef TESTINVINCIBLE
	robin.exps = 31000000;
	robin.gold = 1000000;
	robin.maxInven = 100;
#endif

	//for (i = 0; i < 8; i++) {
	//	GetItem(ITEM_IRON, 0, i, GRADE_NORMAL, 300, 0);
	//	GetItem(ITEM_LEATHER, 0, i, GRADE_NORMAL, 300, 0);
	//	GetItem(ITEM_WOOD, 0, i, GRADE_NORMAL, 300, 0);
	//	GetItem(ITEM_CLOTH, 0, i, GRADE_NORMAL, 300, 0);
	//}

	//for (i = 0; i < TOTAL_ESSENCE; i++)
	//	GetItem(ITEM_ESSENCE, 0, i, GRADE_NORMAL, 100, 0);

	//GetItem(ITEM_NETITEM, 0, ITEM_NET_RESURRECTION, GRADE_NORMAL, 5000);

	//for (i = 0; i < TOTAL_STATUE; i++)
	//	robin.statue[i] = true;

	//for (i = 0; i < TOTALQUEST; i++)
	//	if (questInfo[i * QUESTINFODATASIZE + 9] == QUESTTYPE_CARRY)
	//		robin.questStatus[i] = QUESTSTART;

	//for (i = 0; i < TOTAL_SKILL; i++)
	//	robin.skillLv[i] = 10;

	//robinmap = TOLEM1;
	//robin.x = 3 * TSIZE;
	//ao[PLAYER].y = robin.y = 15 * TSIZE;

	//GetItem(ITEM_WASTE, 1, ITEM_WASTE_RETURN, 0, 10);
	//robin.statue[ITEM_STATUE_DIMENSION] = true;
	//robin.demoSeen[DEMO_QUEST0] = true;
	//robin.demoSeen[DEMO_QUEST37_END] = true;

	//robin.lv = 99;
	//robin.sp = 100;
	//robin.mp = robin.ps[PS_MP] = 10000;
	//robin.exps = 3100000;
	//robin.gold = 100000;

	//robin.lv = 99;
	//robin.stat[STAT_STR] = 999;
	//robin.stat[STAT_AGI] = 999;
	//robin.stat[STAT_VIT] = 999;
	//robin.stat[STAT_INT] = 999;

	//RefreshStat();

	//switch (option.curSlot) {
	//	case 1:
	//		for (i = 0; i < DEMO_QUEST168_BOSSBAD; i++)
	//			robin.demoSeen[i] = true;

	//		robin.demoSeen[DEMO_TOLEMGUILD] = true;
	//		robin.demoSeen[DEMO_ATLEGUILD] = true;
	//		robin.demoSeen[DEMO_ADELGUILD] = true;
	//		robin.demoSeen[DEMO_ELFGUILD] = true;

	//		for (i = 0; i < TOTAL_STATUE; i++)
	//			robin.statue[i] = true;
	//		for (i = 0; i < TOTAL_KEYITEM; i++)
	//			SetBit(robin.keyItem, i);
	//		for (i = 0; i < TOTALMAP; i++)
	//			SetBit(robin.mapSeen, i);
	//		for (i = 0; i < TOTALQUEST; i++)
	//			robin.questStatus[i] = QUESTEND;

	//		InitStatue();

	//		robin.lv = 99;
	//		robin.stat[STAT_STR] = 700;
	//		robin.stat[STAT_AGI] = 700;
	//		robin.stat[STAT_INT] = 700;
	//		robin.ps[PS_DMG] = 5000;
	//		robin.hp = robin.ps[PS_HP] = 8570;
	//		robin.mp = robin.ps[PS_MP] = 999;
	//		robin.sp = 250;
	//		robin.ap = 9999;

	//		RefreshStat();
	//		robin.gold = 10000000;

	//		GetItem(ITEM_SWORD, 90, ITEM_SWORD_DRAGONTOOTH, GRADE_LEGEND, 1, 0);
	//		GetItem(ITEM_HELM, 90, ITEM_HELM_SPIKEHEAD, GRADE_LEGEND, 1, 0);
	//		GetItem(ITEM_ARMOR, 90, ITEM_ARMOR_SKULL, GRADE_LEGEND, 1, 0);
	//		GetItem(ITEM_GUNTLET, 90, ITEM_GUNTLET_KNIGHT, GRADE_LEGEND, 1, 0);
	//		GetItem(ITEM_KILT, 90, ITEM_KILT_NIGHTMARE, GRADE_LEGEND, 1, 0);
	//		GetItem(ITEM_GREAVES, 90, ITEM_GREAVES_FROZEN, GRADE_LEGEND, 1, 0);
	//		GetItem(ITEM_NECK, 90, ITEM_NECK10, GRADE_LEGEND, 1, 0);
	//		GetItem(ITEM_RING, 90, ITEM_RING2, GRADE_LEGEND, 1, 0);

	//		for (i = 0; i < TOTAL_ESSENCE; i++)
	//			GetItem(ITEM_ESSENCE, 0, i, GRADE_NORMAL, 300, 0);
	//		for (i = 0; i < TOTAL_GEM; i++)
	//			GetItem(ITEM_GEM, 0, i, GRADE_RARE, 300, 0);
	//		for (i = 0; i < TOTAL_IRON; i++)
	//			GetItem(ITEM_IRON, 0, i, GRADE_NORMAL, 300, 0);
	//		for (i = 0; i < TOTAL_LEATHER; i++)
	//			GetItem(ITEM_LEATHER, 0, i, GRADE_NORMAL, 300, 0);
	//		for (i = 0; i < TOTAL_WOOD; i++)
	//			GetItem(ITEM_WOOD, 0, i, GRADE_NORMAL, 300, 0);
	//		for (i = 0; i < TOTAL_CLOTH; i++)
	//			GetItem(ITEM_CLOTH, 0, i, GRADE_NORMAL, 300, 0);
	//		break;
	//	case 2:
	//		for (i = 0; i < DEMO_QUEST168_BOSSBAD; i++)
	//			robin.demoSeen[i] = true;

	//		robin.demoSeen[DEMO_TOLEMGUILD] = true;
	//		robin.demoSeen[DEMO_ATLEGUILD] = true;
	//		robin.demoSeen[DEMO_ADELGUILD] = true;
	//		robin.demoSeen[DEMO_ELFGUILD] = true;

	//		robin.demoSeen[DEMO_QUEST168_FIREBOSSCLEAR] = true;
	//		robin.demoSeen[DEMO_QUEST168_THUNDERBOSSCLEAR] = true;
	//		robin.demoSeen[DEMO_QUEST168_ICEBOSSCLEAR] = true;
	//		robin.demoSeen[DEMO_QUEST168_HOLYBOSSCLEAR] = true;
	//		robin.demoSeen[DEMO_QUEST168_DARKBOSSCLEAR] = true;

	//		for (i = 0; i < TOTAL_STATUE; i++)
	//			robin.statue[i] = true;
	//		for (i = 0; i < TOTAL_KEYITEM; i++)
	//			SetBit(robin.keyItem, i);
	//		for (i = 0; i < TOTALMAP; i++)
	//			SetBit(robin.mapSeen, i);
	//		for (i = 0; i < TOTALQUEST; i++)
	//			robin.questStatus[i] = QUESTEND;

	//		InitStatue();

	//		robin.lv = 99;
	//		robin.stat[STAT_STR] = 700;
	//		robin.stat[STAT_AGI] = 700;
	//		robin.stat[STAT_INT] = 700;
	//		robin.ps[PS_DMG] = 5000;
	//		robin.hp = robin.ps[PS_HP] = 8570;
	//		robin.mp = robin.ps[PS_MP] = 999;
	//		robin.sp = 250;
	//		robin.ap = 9999;

	//		game.playMode[2] = HELL_READY;
	//		SaveFlag(2);

	//		RefreshStat();
	//		robin.gold = 10000000;

	//		GetItem(ITEM_GUN, 90, ITEM_GUN_INFERNO, GRADE_LEGEND, 1, 0);
	//		GetItem(ITEM_HAT, 90, ITEM_HAT_ELVENCAP, GRADE_LEGEND, 1, 0);
	//		GetItem(ITEM_VEST, 90, ITEM_VEST_SPATIOTEMPORAL, GRADE_LEGEND, 1, 0);
	//		GetItem(ITEM_ARMLET, 90, ITEM_ARMLET_DIGNITY, GRADE_LEGEND, 1, 0);
	//		GetItem(ITEM_SKIRT, 90, ITEM_SKIRT_CHAOS, GRADE_LEGEND, 1, 0);
	//		GetItem(ITEM_SHOES, 90, ITEM_SHOES_INCARNATION, GRADE_LEGEND, 1, 0);
	//		GetItem(ITEM_NECK, 90, ITEM_NECK15, GRADE_LEGEND, 1, 0);
	//		GetItem(ITEM_RING, 90, ITEM_RING6, GRADE_LEGEND, 1, 0);

	//		for (i = 0; i < TOTAL_ESSENCE; i++)
	//			GetItem(ITEM_ESSENCE, 0, i, GRADE_NORMAL, 300, 0);
	//		for (i = 0; i < TOTAL_GEM; i++)
	//			GetItem(ITEM_GEM, 0, i, GRADE_RARE, 300, 0);
	//		for (i = 0; i < TOTAL_IRON; i++)
	//			GetItem(ITEM_IRON, 0, i, GRADE_NORMAL, 300, 0);
	//		for (i = 0; i < TOTAL_LEATHER; i++)
	//			GetItem(ITEM_LEATHER, 0, i, GRADE_NORMAL, 300, 0);
	//		for (i = 0; i < TOTAL_WOOD; i++)
	//			GetItem(ITEM_WOOD, 0, i, GRADE_NORMAL, 300, 0);
	//		for (i = 0; i < TOTAL_CLOTH; i++)
	//			GetItem(ITEM_CLOTH, 0, i, GRADE_NORMAL, 300, 0);
	//		break;
	//}
	SaveGame();

#ifdef DEBUG
	//DebugInit();
#endif
}

void GotoTitle(void)
{
	drawHandle = MD_TITLE;
	keyHandle = MK_TITLE;

	curMenu = MENU_LOADING;

	frame = 0;


	//TEXT_LOGIN_100

	PlayMusic(M_HEART);

	printCoords();
	printBoxCoords();

#ifdef COSTUMETEST
	int i;

	stageInfoDepth = STAGEINFO_NEWSTAGE;
	stageInfoFrame = 0;

	robin.stage++;
	robin.room = 0;
	memset(&robin.bossObj, 0, sizeof(robin.bossObj));
	SetBossObj();

	selectedCrew = Proc(proc4, 4);
	//void	SetBossCrew(robin.stage);
#endif
}

void GotoPlay(void)
{
	int i, j, k = 0;
	int doorY = 10 * TSIZE;
	int prevDrawHandle = drawHandle;
	int prevKeyHandle = keyHandle;
	OBJECT* pObj;

	//InitMenu(); 
	robin.stage = 0;

	//memset(&ao[NPC], 0, sizeof(OBJECT));
	ao[NPC].active = false;

	drawHandle = MD_PLAY;
	keyHandle = MK_PLAY;
	frame = 0;

	loadedMap = -1;

	oldMap = robinmap;
	robinmap = MAP_DIORAMA_TOLEM + castleOrder[robin.castle];

	//robinmap = TOLEMHOUSE2;

	SetRoom();

	if (doubleBuffer) {
		if (oldMap != robinmap)
			DoubleBuffering(drawHandle);
	}

	//for (i = NEUTRAL; i < ITEMOBJ; i++)
	//	if (ao[i].type == OBJ_BOX) {
	//		ao[i].active = false;
	//	}

	fadeFrame = FPS;
	arenaStatus = STATUS_READY;

	raidPlayer = focus = PLAYER;

	turn = PLAYER;
	turnFrame = 0;
	turnPosition = HERE;
	for (i = 0; i < TOTALOBJECT; i++) {
		ao[i].turn = 0;
		ao[i].turnPosition = HERE;
	}

#ifdef ENEMYHPBAR
	LoadEnemyHpBar();
#endif
	InitTarget();

	if (touch) {
		touchMode = TOUCH_PLAY;
		touchModeOld = null;
		touchIndex = 0;
		swipeIndex = 0;
	}

	curMenu = MENU_PLAY;

	effect.color = effect.color2 = false;

	memset(&ao[SOLDIER], 0, sizeof(OBJECT));
	oldMap = robinmap;
	robinmap = MAP_DIORAMA_TOLEM + castleOrder[robin.castle];
	SetRoom();

	areaFrame = INFOFRAME;

	SetHero();
	SetBattleCrew();
	DecideRouletteResult();

	sequenceFrame = false;
	screenDarken = false;

	memset(&cardMark, 0, sizeof(cardMark));
	memset(&rewardMark, 0, sizeof(rewardMark));
	memset(&boxMark, 0, sizeof(boxMark));

	//상자 박스를 만들어준다.
	//SetBox(&ao[ITEMBOX], 0);

	pvpRewardIndex = 0;

	if (bossRaidMode == true)
		PlayMusic(M_EVENT_FUNNY);
	else if (robin.bossRoom == true)
		PlayMusic(M_BOSS);
	else
		PlayMusic(M_TITLE);

	attackSequence = ATTACKSEQUENCE_READY;
	arenaStatus = STATUS_READY;
	currencyMarkCnt = 0;

	turn = PLAYER;
	turnFrame = 0;
	turnPosition = HERE;

	for (i = 0; i < TOTALOBJECT; i++) {
		ao[i].turn = 0;
		ao[i].turnPosition = HERE;
	}

	arenaStatus = STATUS_PLAY;
	touchDisable = true;
	battleStartFrame = BATTLESTARTFRAME;

}

void BackToReward(void)
{
	int i;

	rewardFrame = 0;
	menuDepth = 0;

	//memset(&rewardItem[focusedItem], 0, sizeof(ITEM));
	//for (i = focusedItem; i < rewardItemCnt - 1; i++) {
	//	memcpy(&rewardItem[i], &rewardItem[i + 1], sizeof(ITEM));
	//}
	//memset(&rewardItem[rewardItemCnt - 1], 0, sizeof(ITEM));
	//rewardItemCnt--;
	focusedItem++;

	memset(&rewardMark, 0, sizeof(rewardMark));
	memset(&boxMark, 0, sizeof(boxMark));

	GotoGacha();
}

void OutOfGacha(void)
{
	int i;

	drawHandle = before_DrawHandle_Gacha;
	keyHandle = before_KeyHandle_Gacha;
	curMenu = before_CurMenu_Gacha;

	robinmap = playmap;
	ReadMap(robinmap);
	DoubleBuffering(drawHandle);

	PlayMusic(M_SELECT);

	switch (drawHandle) {
	case MD_PLAY:
	case MD_BATTLE:
		//물리치면 다음 스테이지로
		if (curMenu == MENU_PLAY) {

			if (attackSequenceBefore) {
				attackSequence = attackSequenceBefore;
				attackType = attackTypeBefore;
				attackStr = attackStrBefore;
				attackDelay = attackDelayBefore;
				rewardItemCnt = rewardItemCntBefore;
				memcpy(&rewardMark, &rewardMarkBack, sizeof(rewardMark));
				memcpy(&rewardItem, &rewardItemBack, sizeof(rewardItem));

				attackSequenceBefore = attackTypeBefore = attackStrBefore = attackDelayBefore = false;
			}
			else {
				attackSequence = ATTACKSEQUENCE_READY;
				turnPosition = COMING;
				arenaStatus = STATUS_PLAY;
				option.gameControl = CONTROL_AUTO;
				screenDarken = false;

				bar[BAR_BOX].active = true;
				bar[BAR_GOLD].active = true;
				bar[BAR_CROWN].active = true;
				bar[BAR_QUEST].active = true;

				effect.color2 = false;
				effect.color = false;
			}

			ao[PLAYER].attack = false;
		}
		break;
	case MD_RAID:

		break;
	}

	memset(&boxMark, 0, sizeof(boxMark));
	memset(&boxCardMark, 0, sizeof(boxCardMark));
}

void OutOfNewCard(void)
{
	int i;

	drawHandle = before_DrawHandle;
	keyHandle = before_KeyHandle;

	if (drawHandle == MD_PLAY || drawHandle == MD_BATTLE) {
		if (attackSequence == ATTACKSEQUENCE_REWARD)
			attackDelay = ATTACKDELAY_REWARD_TABTOCOLLECT + 1;
	}
}

void GotoBoss(void)
{
	int i;
	int doorY = 256 * _2X;
	OBJECT* pObj = &ao[PLAYER];
	OBJECT* eObj = &ao[ENEMY];

	ao[NPC].active = false;

	memset(&ao[SOLDIER], 0, sizeof(OBJECT));
	memcpy(&ao[SOLDIER], pObj, sizeof(OBJECT));
	ao[SOLDIER].active = false;

	robin.bossRoom = true;

	raidPlayer = PLAYER;

	menuDepth = 0;
	frame = 0;

	loadedMap = -1;

	oldMap = playmap = robinmap;
	robinmap = BOSSROOM;

	SetRoom();

	SetStageBoss();

	fadeFrame = FPS;
	arenaStatus = STATUS_READY;

	raidPlayer = focus = PLAYER;
	turn = PLAYER;
	turnFrame = 0;
	turnPosition = HERE;
	for (i = 0; i < TOTALOBJECT; i++) {
		ao[i].turn = 0;
		ao[i].turnPosition = HERE;
	}


	if (touch) {
		touchMode = TOUCH_PLAY;
		touchModeOld = null;
		touchIndex = 0;
		swipeIndex = 0;
	}

	//curMenu = MENU_PLAY;
	//컨트롤마크를 다 없애고
	//memset(&controlMark, 0, sizeof(controlMark));
	initControlerFrame = 1;
	crewInitializeFrame = 1;
	for (i = 0; i < TOTALCONTROLMARK; i++)
		controlerSpread[i] = true;

	attackSequence = ATTACKSEQUENCE_READY;

	drawHandle = MD_PLAY;
	keyHandle = MK_PLAY;

	PlayMusic(M_BOSS);
	bar[BAR_BOSSHP].count = 0;
	bar[BAR_BOSSHP].add = 0;
	AddBar(&bar[BAR_BOSSHP], ao[GetEnemyBarIdx(ENEMY)].hp, BARFRAME);
#ifdef ENEMYHPBAR
	bar[BAR_ENEMYHP].active = false;
#endif
}

void OutOfBattle(void)
{
	memset(&cardMark, 0, sizeof(cardMark));
	memset(&rewardMark, 0, sizeof(rewardMark));
	memset(&boxMark, 0, sizeof(boxMark));
	memset(&goldAlphaMark, 0, sizeof(goldAlphaMark));

	attackSequence = ATTACKSEQUENCE_REWARD_BATTLE;
	sequenceDelay = ATTACKDELAY_REWARD_BATTLE_START + FPS;
	sequenceFrame = 0;

	rouletteNum = 0;
	rouletteNumSub = 0;
	rouletteNumBar = 0;
	rouletteNumPvpBar = 0;

	bar[BAR_ENEMYUSER].front = false;
	bar[BAR_CROWN].front = false;
	bar[BAR_GOLD].front = false;

	bar[BAR_RAIDGOLD].active = false;
	bar[BAR_RAIDGOLD].front = false;
	bar[BAR_ENEMYUSER_BOX].active = false;
	bar[BAR_ENEMYUSER_BOX].front = false;

	attackDelay = 0;
}

void OutOfRaid(void)
{
	memset(&cardMark, 0, sizeof(cardMark));
	memset(&rewardMark, 0, sizeof(rewardMark));
	memset(&boxMark, 0, sizeof(boxMark));
	memset(&goldAlphaMark, 0, sizeof(goldAlphaMark));

	attackSequence = ATTACKSEQUENCE_REWARD_RAID;
	sequenceDelay = ATTACKSEQUENCE_REWARD_RAID + FPS;
	sequenceFrame = 0;

	rouletteNum = 0;
	rouletteNumSub = 0;
	rouletteNumBar = 0;
	rouletteNumPvpBar = 0;

	attackDelay = 0;
}

void OutOfHouse(void)
{
	int i;

	drawHandle = before_DrawHandle;
	keyHandle = before_KeyHandle;

	SetScreenRatio();

	robinmap = playmap;
	ReadMap(robinmap);
	DoubleBuffering(drawHandle);

	SetRoom_Neutral();

	PlayMusic(M_SELECT);

	memcpy(&ao[PLAYER], &ao[SOLDIER], sizeof(OBJECT));
	CopyEnemyObj();
	ao[PLAYER].active = true;

	for (i = ENEMY; i < NEUTRAL; i++) {
		if (ao[i].type) {
			ao[i].active = true;
		}
	}

	//for (i = 0; i < actionCardCnt; i++) {
	//	controlMark[i].frame = 1;
	//}
	memcpy(&controlMark, &controlMarkBack, sizeof(controlMark));
	memcpy(&cardMark, &cardMarkBack, sizeof(cardMark));

	//bar[BAR_COIN].active = true;
}

static int CrewIdToCrewDataKey(int crewId)
{
	int dataId = crewId;
	return crewData[dataId * CREWDATASIZE];
}

static int CrewDataKeyToCmf(int crewDataKey)
{
	return enemyData[crewDataKey * ENEMYDATASIZE + ENEMYDATA_CMF];
}

static int RemoveIdFromArray(int* arr, int n, int removeId)
{
	for (int i = 0; i < n; i++) {
		if (arr[i] == removeId) {
			arr[i] = arr[n - 1];
			return n - 1;
		}
	}
	return n;
}

static void ShuffleIntArray(int* arr, int n)
{
	for (int i = n - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		int t = arr[i];
		arr[i] = arr[j];
		arr[j] = t;
	}
}

// 배경 캐릭터의 “스탠딩 프레임”이 있다면 그걸 쓰는 게 좋고,
// 없으면 0으로 고정
static int GetBgFrameForCrewKey(int crewDataKey)
{
	// 일단 0 고정. (원하면 crewPos 기반으로 idle frame 잡아줄 수도 있음)
	return 0;
}

static inline int GetCrewKeyFromCrewId(int crewId)
{
	return CrewIdToCrewDataKey(crewId); // crewData의 인덱스(=key)
}

// crewId 기준 별
static int GetCrewStar(int crewId)
{
	int key = GetCrewKeyFromCrewId(crewId);
	return enemyData[crewData[key * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_STAR];
}

static int GetRegionCount(void)
{
	return TOTALCASTLE;
}

static int ModI(int a, int m)
{
	int r = a % m;
	return (r < 0) ? r + m : r;
}

static void DrawCrewGridBackground(void)
{
	int bestDist = 0x7fffffff;
	int bestX = 0;
	int bestY = 0;
	bool found = false;

	// ------------------------------------------------------------
	// crewData는 [ROBIN, DIANA, MAXX, ...] 처럼 히어로(0~2)까지 포함된
	// "전체 목록"을 들고 있다고 가정한다.
	//
	// robin.getCrews[] 는 "히어로가 빠진 크루만" 배열이므로
	// owned 체크에서만 (idx - TOTALCHAR) 보정을 한다.
	// ------------------------------------------------------------
	const int total = TOTAL_CREW;            // ✅ crewData 전체 길이(히어로 포함)
	const int rows = (total / BG_COLS) + 1;

	int cellW = 32 * _2X;
	int cellH = 32 * _2X;

	int sx = bgScrollX % cellW; if (sx < 0) sx += cellW;
	int sy = bgScrollY % cellH; if (sy < 0) sy += cellH;

	int startX = -sx - cellW;
	int startY = -sy - cellH;

	int needCols = (DX / cellW) + 3;
	int needRows = (DY / cellH) + 3;

	int offC = bgScrollX / cellW;
	int offR = bgScrollY / cellH;

	for (int r = 0; r < needRows; r++) {
		for (int c = 0; c < needCols; c++) {

			// ✅ 셀 실제 좌표
			int x = startX + c * cellW;
			int y = startY + r * cellH;

			int gridC = ModI((c - 1) + offC, BG_COLS);
			int gridR = ModI((r - 1) + offR, rows);

			int slot = gridR * BG_COLS + gridC;

			// ✅ 전체 리스트 인덱스(0..total-1)로 정규화
			int idx = ModI(slot, total);

			// ✅ crewData는 idx 그대로 접근 (절대 +TOTALCHAR 하지 않음)
			int crewDataIdx = idx;

			int type = crewData[crewDataIdx * CREWDATASIZE]; // 0,1,2면 히어로
			int cmf = -1;
			bool owned = false;

			if (type < TOTALCHAR) {
				// -----------------------------
				// HERO (0~2)
				// -----------------------------
				cmf = ao[type].cmf;
				owned = IsGetHero(type);
			}
			else {
				// -----------------------------
				// CREW (hero 제외 인덱스 보정)
				// -----------------------------
				int crewIdNoHero = crewDataIdx - TOTALCHAR; // robin.getCrews는 hero 제외
				if (crewIdNoHero < 0) crewIdNoHero = 0;    // 방어(정상적이면 음수 안 나옴)

				cmf = enemyData[type * ENEMYDATASIZE + ENEMYDATA_CMF];
				//owned = robin.getCrews[crewIdNoHero];
			}

			// ------------------------------------------------------------
			// 소환 시작 위치 확정 (type 비교)
			// type==summonType 이면, 그 셀이 실제로 그 캐릭(type)을 가리키는 상태여야 함
			// (hero도 crewData에 들어있으므로 type 0~2 매칭 가능)
			// ------------------------------------------------------------
			if (needPickSummonFromBg && type == summonType) {
				if (!(x < -cellW || x > DX + cellW || y < -cellH || y > DY + cellH)) {
					int cx = DX / 2;
					int cy = DY / 2;
					int dx0 = x - cx;
					int dy0 = y - cy;
					int dist = dx0 * dx0 + dy0 * dy0;

					if (dist < bestDist) {
						bestDist = dist;
						bestX = x;
						bestY = y;
						found = true;
					}
				}
			}

			// ------------------------------------------------------------
			// 그리기 (히어로는 DrawPlayer, 크루는 DrawCmfDetailShadow)
			// ------------------------------------------------------------
			if (type < TOTALCHAR) {
				// HERO
				DrawPlayer(&ao[type], (blFrame / 2) % 4,
					x, y, RIGHT, enemyZoom[type],
					false, false, true,
					gScreenBuffer, gScreenLayer, false);
			}
			else {
				// CREW
				DrawCmfDetailShadow(
					cmf, crewPos[type * 5],
					x, y, RIGHT,
					BG_ZOOM * enemyZoom[type],
					gScreenBuffer, gScreenLayer, false);
			}

			// 미보유 표시
			if (!owned) {
				for (int py = -8 * _2X; py <= 8 * _2X; py += 4 * _2X)
					MemRect(x - 10 * _2X, y + py, 20 * _2X, 1 * _2X,
						COLOR_BLACK, gScreenBuffer, gScreenLayer, false);
			}
		}
	}

	// ------------------------------------------------------------
	// pick 완료 처리
	// ------------------------------------------------------------
	if (needPickSummonFromBg && found) {
		summonFromX = bestX;
		summonFromY = bestY;

		// 바로 그 프레임에 그 위치에서 시작
		summonX = summonFromX;
		summonY = summonFromY;

		pickedSummonFromBg = true;
		needPickSummonFromBg = false;
	}
}

static void DrawFilmOverlay(void)
{
	for (int y = 0; y < DY; y += 2 * _2X)
		MemRect(0, y, DX, 1 * _2X,
			COLOR_BLACK, gScreenBuffer, gScreenLayer, false);
}

static double Rand01()
{
	return (double)rand() / (double)RAND_MAX;
}

static int RollStar1to9()
{
	// 누적확률 테이블
	// 1:31, 2:20, 3:15, 4:10, 5:8, 6:7, 7:5, 8:3, 9:1  (합 100)
	int r = rand() % 100; // 0..99
	int acc = 31; if (r < acc) return 1;
	acc += 20;   if (r < acc) return 2;
	acc += 15;   if (r < acc) return 3;
	acc += 10;   if (r < acc) return 4;
	acc += 8;    if (r < acc) return 5;
	acc += 7;    if (r < acc) return 6;
	acc += 5;    if (r < acc) return 7;
	acc += 3;    if (r < acc) return 8;
	return 9;
}

static int RollRegion(int regionCount)
{
	return rand() % regionCount; // 0..regionCount-1
}

// buckets[r][s] : 해당 지역 r, 별 s(1..9)에 속한 "보유 crewId" 목록 (비복원 위해 pop_back 사용)
static int PopFromBucket(std::vector<int>& bucket)
{
	if (bucket.empty()) return -1;
	int id = bucket.back();
	bucket.pop_back();
	return id;
}


// --- fallback 규칙 ---
// 1) (r,s) 있으면 거기서
// 2) 같은 r에서 다른 s 아무거나
// 3) 같은 s에서 다른 r 아무거나
// 4) 전체에서 아무거나
static int PickOneCrewIdByRegionStar(
	std::vector<std::vector<std::vector<int>>>& buckets,
	int regionCount,
	int r,
	int s
) {
	// 1) exact
	auto& b = buckets[r][s];
	if (!b.empty()) { int id = b.back(); b.pop_back(); return id; }

	// 2) fallback: 모든 non-empty 셀에서 랜덤
	struct Cell { int r, s; };
	std::vector<Cell> cells;
	cells.reserve(regionCount * 9);

	for (int rr = 0; rr < regionCount; rr++)
		for (int ss = 1; ss <= 9; ss++)
			if (!buckets[rr][ss].empty())
				cells.push_back({ rr, ss });

	if (cells.empty()) return -1;

	int k = rand() % (int)cells.size();
	auto& bb = buckets[cells[k].r][cells[k].s];
	int id = bb.back(); bb.pop_back();
	return id;
}

static uint32_t gBL_Rng = 0x12345678u;

static inline uint32_t BL_NextU32()
{
	// xorshift32
	uint32_t x = gBL_Rng;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	gBL_Rng = x;
	return x;
}

static inline float BL_Next01()
{
	return (BL_NextU32() >> 8) * (1.0f / 16777216.0f); // 24-bit mantissa
}

// hero 3개(0,1,2) 이후부터가 지역/슬롯 포지션이라고 가정
static inline int RegionFromCastlePos(int castlePos)
{
	// 지역 포지션 시작점
	const int FIRST = (int)CASTLE_ADELINE_CREWPOS1;

	if (castlePos < FIRST) return -1;

	int region = (castlePos - FIRST) / 9; // 지역당 9개 고정
	if (region < 0 || region >= TOTALCASTLE) return -1;

	return region; // 0..TOTALCASTLE-1
}

void BattleLoadingDraw(void)
{
	int dx = 24 * _2X;
	int runY = 16 * _2X;
	int leftX = 24 * _2X;

	MemRect(0, DY, DX, DY, COLOR_BLACK,
		gScreenBuffer, gScreenLayer, false);

	// 1) 배경 격자
	DrawCrewGridBackground();

	// 2) 필름
	DrawFilmOverlay();

	// ------------------------------------------------------------
	// 히어로 보유 수(0부터 연속)
	// ------------------------------------------------------------
	int ownedHeroCnt = 0;
	for (int i = 0; i < TOTALCHAR; i++) {
		if (IsGetHero(i)) ownedHeroCnt++;
		else break;
	}
	if (ownedHeroCnt < 1) ownedHeroCnt = 1;

	// ------------------------------------------------------------
	// 3) 소환 중 캐릭터(센터/합류 중)
	// ------------------------------------------------------------
	if ((blState == BL_REVEAL || blState == BL_JOIN) && summonCmf >= 0) {
		float typeZoom = 1.0f;
		int index = GetCrewIdxFromType(summonType);
		int crewSummonIdx = showCrewCnt - ownedHeroCnt;
		if (summonType >= 0) typeZoom = enemyIconZoom[summonType];

		DrawCmfDetailShadow(
			summonCmf, crewPos[summonType * 5],
			summonX, summonY,
			RIGHT, summonScale * typeZoom,
			gScreenBuffer, gScreenLayer, false
		);

		if (blState == BL_REVEAL) {
			switch (summonCmf) {
			case ROBIN:
			case DIANA:
			case MAXX:
				//이름과 레벨
				DrawLv(ao[summonCmf].lv, summonX, summonY - (float)8 * _2X * summonScale * typeZoom, summonScale * typeZoom * 0.5f, CENTER, gScreenBuffer, gScreenLayer, false);
				CenterText(ao[summonCmf].name, summonX, summonY - (float)16 * _2X * summonScale * typeZoom, summonScale * typeZoom * 0.5f, gScreenBuffer, gScreenLayer, false);
				break;
			default:
				//이름과 별
				DrawStar(ICON_STAR, summonX, summonY - (float)12 * _2X * summonScale * typeZoom * 0.5f, enemyData[crewData[index * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_STAR] + 1, enemyData[crewData[index * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_STAR] + 1, enemyData[crewData[index * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_STAR] + 1, CENTER, true, summonScale * typeZoom * 0.5f, gScreenBuffer, gScreenLayer, false);
				CenterText(ao[CREW + crewSummonIdx].name, summonX, summonY - (float)16 * _2X * summonScale * typeZoom, summonScale * typeZoom * 0.5f, gScreenBuffer, gScreenLayer, false);
				break;
			}
		}
	}

	// ------------------------------------------------------------
	// 4) 러닝 라인
	//    showCrewCnt = "등장 완료된 전체 수(히어로+크루)"
	//    배치 규칙:
	//      첫번째(가장 먼저 나온) 캐릭이 맨 오른쪽(앞),
	//      새로 나올수록 맨 왼쪽(뒤)로 들어오며
	//      뽑힐 때마다 기존 애들이 한 칸씩 오른쪽으로 밀림
	// ------------------------------------------------------------
	int moveX = (blState == BL_FINISH) ? finishOffsetX : 0;

	// JOIN 중에는 "기존 애들이 dx 만큼 밀리는" 걸 부드럽게 보이도록 shift 보간
	int joinShift = 0;
	if (blState == BL_JOIN) {
		const int JOIN_FRAMES = 6;
		float u = (float)blStateFrame / (float)JOIN_FRAMES;
		if (u > 1) u = 1;

		float e;
		if (u < 0.5f) e = 2.0f * u * u;
		else         e = 1.0f - (float)pow(-2.0f * u + 2.0f, 2.0f) / 2.0f;

		joinShift = (int)(dx * e); // 0 -> dx
	}

	// ✅ 기존(등장 완료) 캐릭터들
	for (int i = 0; i < showCrewCnt; i++) {

		// i=0(첫번째로 나온 애)가 "앞"이라서, showCrewCnt 증가 시 자동으로 오른쪽으로 밀리게 배치
		int x = leftX + (showCrewCnt - 1 - i) * dx + moveX;

		// JOIN 중에는 기존 애들이 앞으로(dx) 밀리는 중이므로 shift 추가
		// (새로 들어오는 애는 별도로 summon으로 그리고 있음)
		if (blState == BL_JOIN) x += joinShift;

		if (i < ownedHeroCnt) {
			// 히어로
			DrawPlayer(&ao[i], (blFrame / 2) % 4,
				x,
				runY, RIGHT, enemyZoom[i],
				false, false, true,
				gScreenBuffer, gScreenLayer, false);
		}
		else {
			// 크루
			int crewIdx = i - ownedHeroCnt;
			int key = robin.slotCrew[crewIdx];
			int cmf = enemyData[key * ENEMYDATASIZE + ENEMYDATA_CMF];

			DrawCmfDetailShadow(
				cmf,
				crewPos[key * 5] + (blFrame / 2) % crewPos[key * 5 + 1],
				x, runY,
				RIGHT, enemyIconZoom[key],
				gScreenBuffer, gScreenLayer, false
			);
		}
	}

	// 5) 로딩바
	int barW = Min(DX, blFrame * 2);
	MemRect(0, 8 * _2X, barW, 8 * _2X,
		COLOR_ORANGE, gScreenBuffer, gScreenLayer, false);

	BarDraw(&bar[BAR_COMBATPOWERALL], bar[BAR_COMBATPOWERALL].zoom, gScreenBuffer, gScreenLayer, false);
}

// 로딩용: crewId -> type (crewDataKey 기준)
static inline int GetTypeFromCrewId(int crewId)
{
	int key = CrewIdToCrewDataKey(crewId);
	return crewData[key * CREWDATASIZE + CREWDATA_TYPE];
}

// 로딩용: crewId -> GetUnitScore와 "완전히 동일한 기준" 점수
static inline int GetScoreFromCrewId_UnitRule(int crewId)
{
	OBJECT tmp;
	memset(&tmp, 0, sizeof(tmp));
	tmp.type = GetTypeFromCrewId(crewId);
	return GetUnitScore(&tmp); // (별*100 + 지역) 네가 바꾼 GetUnitScore 사용
}


static inline void BL_SeedRng(uint32_t seed)
{
	gBL_Rng = (seed ? seed : 0x12345678u);
}



static inline int GetCrewRegionSafeByCrewId(int crewId)
{
	int key = CrewIdToCrewDataKey(crewId);      // crewData 인덱스
	int castlePos = crewData[key * CREWDATASIZE + CREWDATA_CASTLEIDX];
	return RegionFromCastlePos(castlePos);
}

static inline int ScoreFromCrewId(int crewId)
{
	// 네가 정의한 기준(별*100 + 지역)과 동일하게 맞추려면:
	int key = CrewIdToCrewDataKey(crewId);
	int star = enemyData[crewData[key * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_STAR];
	int region = GetCrewRegionSafeByCrewId(crewId); // 0..TOTALCASTLE-1
	if (region < 0) region = 0;
	return star * 100 + region;
}

void PickBattleCrew(
	int* outCrewIdList,
	int* outCrewKeyList,
	int& outCrewCnt,
	int maxCrew,
	bool hasLeader,
	int leaderCrewId
)
{
	const int regionCount = GetRegionCount(); // = TOTALCASTLE
	outCrewCnt = 0;

	// ==============================
	// 리더 0번 고정
	// ==============================
	std::vector<char> picked(TOTAL_CREW, 0);

	if (hasLeader) {
		outCrewIdList[0] = leaderCrewId;
		outCrewKeyList[0] = CrewIdToCrewDataKey(leaderCrewId);
		picked[leaderCrewId] = 1;
		outCrewCnt = 1;
	}

	const int want = hasLeader ? (maxCrew - 1) : maxCrew;

	// ==============================
	// STAR 풀 구성 (hero 3개 제외: key<3 제외)
	// ==============================
	std::vector<int> starPool[10];
	for (int crewId = 0; crewId < TOTAL_CREW; crewId++) {
		//if (!robin.getCrews[crewId]) continue;
		if (picked[crewId]) continue;

		int key = CrewIdToCrewDataKey(crewId);
		if (key < 3) continue; // HERO 3개 제외

		int star = GetCrewStar(crewId);
		if (star < 1 || star > 9) continue;

		int region = GetCrewRegionSafeByCrewId(crewId);
		if (region < 0 || region >= regionCount) continue; // ✅ 안전

		starPool[star].push_back(crewId);
	}

	// ==============================
	// 확률(기본) + pity/감쇠
	// ==============================
	static float STAR_BASE[10] = {
		0.0f,
		0.35f, 0.25f, 0.15f, 0.10f, 0.07f, 0.04f, 0.025f, 0.015f, 0.005f
	};

	const int   PITY_TRIGGER = 10;    // 고등급(>=7) N번 안 나오면
	const float PITY_BONUS = 0.20f; // 그 때 고등급 확률 보정
	const float REGION_PENALTY = 0.70f; // 같은 지역 연속 페널티
	const float STAR_PENALTY = 0.75f; // 같은 별 연속 페널티

	std::vector<int> recentRegion(regionCount, 0);
	int recentStar[10] = { 0 };
	int noHighStarCount = 0;

	auto RollStar = [&]() -> int
		{
			float w[10] = { 0 };
			float sum = 0.0f;

			for (int s = 1; s <= 9; s++) {
				float p = STAR_BASE[s];

				// pity: 고등급(7~9) 안 나오면 고등급만 살짝 부스트
				if (noHighStarCount >= PITY_TRIGGER && s >= 7)
					p *= (1.0f + PITY_BONUS);

				// 연속 억제(소프트)
				if (recentStar[s] > 0) {
					// 1회면 0.75, 2회면 0.75^2 ...
					float mul = 1.0f;
					for (int k = 0; k < recentStar[s]; k++) mul *= STAR_PENALTY;
					p *= mul;
				}

				w[s] = p;
				sum += p;
			}

			float r = BL_Next01() * sum;
			for (int s = 1; s <= 9; s++) {
				r -= w[s];
				if (r <= 0.0f) return s;
			}
			return 1;
		};

	auto PickFromStar = [&](int star) -> int
		{
			// 가중치: 같은 지역이 많이 뽑혔으면 감쇠
			struct Cand { int cid; float w; };
			std::vector<Cand> cand;
			cand.reserve(starPool[star].size());

			for (int cid : starPool[star]) {
				if (picked[cid]) continue;

				int region = GetCrewRegionSafeByCrewId(cid);
				if (region < 0 || region >= regionCount) continue;

				float w = 1.0f;
				if (recentRegion[region] > 0) {
					float mul = 1.0f;
					for (int k = 0; k < recentRegion[region]; k++) mul *= REGION_PENALTY;
					w *= mul;
				}

				cand.push_back({ cid, w });
			}

			if (cand.empty()) return -1;

			float sum = 0.0f;
			for (auto& c : cand) sum += c.w;

			float r = BL_Next01() * sum;
			for (auto& c : cand) {
				r -= c.w;
				if (r <= 0.0f) return c.cid;
			}
			return cand.back().cid;
		};

	// ==============================
	// 픽 루프
	// ==============================
	while (outCrewCnt < maxCrew && (outCrewCnt - (hasLeader ? 1 : 0)) < want)
	{
		int star = RollStar();
		int cid = PickFromStar(star);

		// fallback: 아래 등급으로 내려가며 채우기
		if (cid < 0) {
			for (int s = star - 1; s >= 1 && cid < 0; s--) {
				cid = PickFromStar(s);
				if (cid >= 0) star = s;
			}
		}
		if (cid < 0) break;

		picked[cid] = 1;
		outCrewIdList[outCrewCnt] = cid;
		outCrewKeyList[outCrewCnt] = CrewIdToCrewDataKey(cid);
		outCrewCnt++;

		// 상태 갱신
		if (star >= 7) noHighStarCount = 0;
		else           noHighStarCount++;

		recentStar[star]++;

		int region = GetCrewRegionSafeByCrewId(cid);
		if (region >= 0 && region < regionCount) recentRegion[region]++;
	}

	// ==============================
	// 최종 정렬
	// 리더(0) 고정, 뒤로 갈수록 강해지게
	// ==============================
	int start = hasLeader ? 1 : 0;

	std::sort(outCrewIdList + start, outCrewIdList + outCrewCnt,
		[](int a, int b) {
			return ScoreFromCrewId(a) < ScoreFromCrewId(b);
		});

	for (int i = start; i < outCrewCnt; i++)
		outCrewKeyList[i] = CrewIdToCrewDataKey(outCrewIdList[i]);
}

void GotoBattleLoading(void)
{
	int i;

	//drawHandle = MD_BATTLELOADING;
	frame = 0;
	sequenceFrame = false;
	screenDarken = false;

	heroCnt = 0;
	crewCnt = MAXCREW;
	showCrewCnt = 0;
	cardCmf = -1;
	cardAlpha = 0;

	// HERO 카운트
	for (i = 0; i < TOTALCHAR; i++) {
		if (IsGetHero(i) == true) heroCnt++;
	}

	showHeroCnt = heroCnt;

	// ------------------------------
	// 리더: 0번 고정
	// ------------------------------
	int leaderCrewId = robin.slotCrew[0];
	bool hasLeader = false;
	if (leaderCrewId >= 0 && leaderCrewId < TOTAL_CREW/* && robin.getCrews[leaderCrewId] == true*/) {
		hasLeader = true;
		crewIdList[0] = leaderCrewId;
		robin.slotCrew[0] = CrewIdToCrewDataKey(leaderCrewId);
		crewCnt = 1;
	}

	int regionCount = GetRegionCount();

	uint32_t seed = 0;
	seed ^= (uint32_t)time(NULL);          // 가능하면
	seed ^= (uint32_t)GetTickCount();      // Windows면 이게 더 좋음
	seed ^= (uint32_t)(uintptr_t)&seed;    // fallback

	BL_SeedRng(seed);

	// ------------------------------
	// [CANDIDATES] 전 지역 후보를 통째로 모아서 셔플 (편향 제거)
	// ------------------------------
	PickBattleCrew(
		crewIdList,
		robin.slotCrew,
		crewCnt,
		MAXCREW,
		hasLeader,
		leaderCrewId
	);

	//TEST
	//crewCnt = MAXCREW;

	//robin.slotCrew[0] = NPC_GIRL;
	//robin.slotCrew[1] = NPC_UNCLE;
	//robin.slotCrew[2] = NPC_AUNT;
	//robin.slotCrew[3] = NPC_ADELKNIGHT;
	//robin.slotCrew[4] = NPC_NOBLEMAN;
	//robin.slotCrew[5] = NPC_SEBASTIAN;

	// ---- 로딩 연출 초기화 ----
	blState = BL_REVEAL;
	blStateFrame = 0;
	blFrame = 0;
	finishOffsetX = 0;

	summonCmf = -1;

	showCrewCnt = 0;

	bgScrollX = 0;
	bgScrollY = 0;

	robin.stage = nearestIndex;

	SetHero();
	SetBattleCrew();

	//bar[BAR_COMBATPOWERALL].front = true;
	//bar[BAR_COMBATPOWERALL].count = 0;
	//bar[BAR_COMBATPOWERALL].countFrame = 0;
	//bar[BAR_COMBATPOWERALL].add = 0;
	//bar[BAR_COMBATPOWERALL].max = 0;
	//for (i = 0; i < TOTALCHAR; i++) {
	//	if (IsGetHero(i))
	//		AddBar(&bar[BAR_COMBATPOWERALL], GetCombatPower(&ao[i]), BARFRAME);
	//}
}

void BattleLoadingUpdate(void)
{
	blFrame++;
	blStateFrame++;

	// 배경 스크롤
	bgScrollX += 2 * _2X;
	bgScrollY += 2 * _2X;

	// ------------------------------------------------------------
	// 히어로 보유 수(0부터 연속) 계산: 1~TOTALCHAR
	// 첫번째 히어로는 무조건 있음
	// ------------------------------------------------------------
	int ownedHeroCnt = 0;
	for (int i = 0; i < TOTALCHAR; i++) {
		if (IsGetHero(i)) ownedHeroCnt++;
		else break; // 순차 획득이므로 끊기면 종료
	}
	if (ownedHeroCnt < 1) ownedHeroCnt = 1;

	const int totalReveal = ownedHeroCnt + crewCnt;

	// 로딩바 진행률: "등장 완료 수" 기준
	loadPct = (totalReveal > 0) ? (showCrewCnt * 100 / totalReveal) : 100;

	// ------------------------------------------------------------
	// 1) REVEAL: 배경 위치 -> 센터
	// ------------------------------------------------------------
	if (blState == BL_REVEAL)
	{
		const int REVEAL_FRAMES = 8;
		const int HOLD_FRAMES = 10;

		// 다음에 뽑을 인덱스(0-based): showCrewCnt가 "등장 완료 수"이므로 그 다음을 뽑는다
		int nextIdx = showCrewCnt;

		// 다 뽑았으면 RUN_ALL로
		if (nextIdx >= totalReveal) {
			blState = BL_RUN_ALL;
			blStateFrame = 0;
			return;
		}

		// 진입 1프레임: 이번에 소환할 대상 세팅 + 배경에서 좌표 pick 요청
		if (blStateFrame == 1) {

			// 히어로 먼저, 그 다음 크루
			if (nextIdx < ownedHeroCnt) {
				summonType = nextIdx;                 // 히어로 id(0~)
				summonCmf = ao[summonType].cmf;
				AddBar(&bar[BAR_COMBATPOWERALL], GetCombatPower(&ao[nextIdx]), FPS / 2);
			}
			else {
				int crewIdx = nextIdx - ownedHeroCnt; // 0~crewCnt-1
				summonType = robin.slotCrew[crewIdx];       // 크루 type(key)
				summonCmf = enemyData[summonType * ENEMYDATASIZE + ENEMYDATA_CMF];

				// 기존 로직 유지(전투력바 등): crewIdx 기준
				AddBar(&bar[BAR_COMBATPOWERALL], GetCombatPower(&ao[CREW + crewIdx]), FPS / 2);
			}

			needPickSummonFromBg = true;
			pickedSummonFromBg = false;

			summonScale = 1.0f;
		}

		// 배경 Draw에서 아직 출발점을 못 잡았으면 대기
		if (!pickedSummonFromBg) {
			const int MAX_WAIT = FPS / 2;
			if (blStateFrame <= MAX_WAIT) return;

			// fallback: 센터에서 튀어나오게
			pickedSummonFromBg = true;
			needPickSummonFromBg = false;
			summonFromX = DX / 2;
			summonFromY = DY / 2;
			blStateFrame = 0;
		}

		const int centerX = DX / 2;
		const int centerY = DY / 2;

		// 1) 배경->센터
		if (blStateFrame <= REVEAL_FRAMES) {
			float u = (float)blStateFrame / (float)REVEAL_FRAMES;
			if (u > 1) u = 1;

			// ease-out
			float e = 1.0f - (1.0f - u) * (1.0f - u);

			summonX = summonFromX + (int)((centerX - summonFromX) * e);
			summonY = summonFromY + (int)((centerY - summonFromY) * e);

			summonScale = 1.0f + 1.2f * u;
			return;
		}

		// 2) 센터 HOLD
		if (blStateFrame <= REVEAL_FRAMES + HOLD_FRAMES) {
			summonX = centerX;
			summonY = centerY;
			summonScale = 2.2f;
			return;
		}

		// 3) JOIN으로
		needPickSummonFromBg = false;
		blState = BL_JOIN;
		blStateFrame = 0;
		return;
	}

	// ------------------------------------------------------------
	// 2) JOIN: 센터 -> 러닝라인(왼쪽 합류) + 기존 캐릭 한 칸 밀림(그림에서 보간)
	// ------------------------------------------------------------
	if (blState == BL_JOIN)
	{
		const int JOIN_FRAMES = 6; // 너무 짧으면 순간이동 느낌

		if (blStateFrame == 1) {
			joinFromX = summonX;
			joinFromY = summonY;
		}

		float u = (float)blStateFrame / (float)JOIN_FRAMES;
		if (u > 1) u = 1;

		// easeInOutQuad
		float e;
		if (u < 0.5f) e = 2.0f * u * u;
		else         e = 1.0f - (float)pow(-2.0f * u + 2.0f, 2.0f) / 2.0f;

		int dx = 24 * _2X;
		int runY = 16 * _2X;
		int leftX = 24 * _2X;      // ✅ 러닝라인의 "맨 왼쪽(뒤)" 위치

		// ✅ 새로 뽑힌 애는 항상 맨 왼쪽으로 합류(뒤에 붙음)
		int toX = leftX;
		int toY = runY;

		summonX = joinFromX + (int)((toX - joinFromX) * e);
		summonY = joinFromY + (int)((toY - joinFromY) * e);

		// 스케일 줄이기
		summonScale = 2.2f + (1.0f - 2.2f) * u;

		if (blStateFrame >= JOIN_FRAMES) {
			// ✅ 합류 완료: "등장 완료 수" 증가
			showCrewCnt++;

			// 다음 대상이 남아있으면 다시 REVEAL
			int ownedHeroCnt2 = 0;
			for (int i = 0; i < TOTALCHAR; i++) {
				if (IsGetHero(i)) ownedHeroCnt2++;
				else break;
			}
			if (ownedHeroCnt2 < 1) ownedHeroCnt2 = 1;

			int totalReveal2 = ownedHeroCnt2 + crewCnt;

			if (showCrewCnt < totalReveal2) {
				blState = BL_REVEAL;
				blStateFrame = 0;
			}
			else {
				blState = BL_RUN_ALL;
				blStateFrame = 0;
			}
		}
		return;
	}

	// ------------------------------------------------------------
	// 3) RUN_ALL: 전부 뽑혔으면 잠깐 러닝만
	// ------------------------------------------------------------
	if (blState == BL_RUN_ALL)
	{
		if (blStateFrame > 12) {
			blState = BL_FINISH;
			blStateFrame = 0;
		}
		return;
	}

	// ------------------------------------------------------------
	// 4) FINISH: 전원 오른쪽으로 달려서 화면 밖으로
	// ------------------------------------------------------------
	if (blState == BL_FINISH)
	{
		finishOffsetX += (3 + blStateFrame / 6) * _2X;

		if (finishOffsetX >= DX) {
			finishOffsetX = 0;
			GotoBattle();
		}
		return;
	}
}

void GotoBattle(void)
{
	int i;
	int count;


	if (touch) {
		touchMode = TOUCH_PLAY;
		touchModeOld = null;
		touchIndex = 0;
		swipeIndex = 0;
	}

	effect.color = effect.color2 = false;

	memset(&ao[SOLDIER], 0, sizeof(OBJECT));
	oldMap = robinmap;
	robinmap = MAP_DIORAMA_TOLEM + castleOrder[robin.castle];
	SetRoom();

	//bar[BAR_BOX].active = false;
	//bar[BAR_GOLD].active = false;
	//bar[BAR_CROWN].active = false;
	//bar[BAR_QUEST].active = false;
	//bar[BAR_HAMMER].active = false;
	//bar[BAR_SHIELD].active = false;
	//bar[BAR_COMBATPOWER].active = false;
	//bar[BAR_HEART].active = false;
	//bar[BAR_]
	//InitBar(BAR_STAGEPROGRESS);

	//bar[BAR_CASTLE].active = false;
	bar[BAR_CASTLE].targetX = bar[BAR_CASTLE].targetX2 = bar[BAR_CASTLE].x;
	bar[BAR_CASTLE].targetY = bar[BAR_CASTLE].targetY2 = bar[BAR_CASTLE].y - 120 * _2X;
	bar[BAR_CASTLE].speed2 = bar[BAR_CASTLE].speed = 8 * _2X;
	bar[BAR_CASTLE].speedIncrement2 = bar[BAR_CASTLE].speedIncrement = 1 * _2X;
	bar[BAR_CASTLE].frame = 1;

	//bar[BAR_CREW].active = false;
	bar[BAR_CREW].targetX = bar[BAR_CREW].targetX2 = bar[BAR_CREW].x;
	bar[BAR_CREW].targetY = bar[BAR_CREW].targetY2 = bar[BAR_CREW].y - 120 * _2X;
	bar[BAR_CREW].speed2 = bar[BAR_CREW].speed = 8 * _2X;
	bar[BAR_CREW].speedIncrement2 = bar[BAR_CREW].speedIncrement = 1 * _2X;
	bar[BAR_CREW].frame = 1;

	//bar[BAR_MAINSHOP].active = false;
	bar[BAR_MAINSHOP].targetX = bar[BAR_MAINSHOP].targetX2 = bar[BAR_MAINSHOP].x;
	bar[BAR_MAINSHOP].targetY = bar[BAR_MAINSHOP].targetY2 = bar[BAR_MAINSHOP].y - 120 * _2X;
	bar[BAR_MAINSHOP].speed2 = bar[BAR_MAINSHOP].speed = 8 * _2X;
	bar[BAR_MAINSHOP].speedIncrement2 = bar[BAR_MAINSHOP].speedIncrement = 1 * _2X;
	bar[BAR_MAINSHOP].frame = 1;

	//bar[BAR_EQUIP].active = false;
	bar[BAR_EQUIP].targetX = bar[BAR_EQUIP].targetX2 = bar[BAR_EQUIP].x;
	bar[BAR_EQUIP].targetY = bar[BAR_EQUIP].targetY2 = bar[BAR_EQUIP].y - 120 * _2X;
	bar[BAR_EQUIP].speed2 = bar[BAR_EQUIP].speed = 8 * _2X;
	bar[BAR_EQUIP].speedIncrement2 = bar[BAR_EQUIP].speedIncrement = 1 * _2X;
	bar[BAR_EQUIP].frame = 1;

	//bar[BAR_ROULETTE].active = false;
	bar[BAR_ROULETTE].targetX = bar[BAR_ROULETTE].targetX2 = bar[BAR_ROULETTE].x;
	bar[BAR_ROULETTE].targetY = bar[BAR_ROULETTE].targetY2 = bar[BAR_ROULETTE].y - 120 * _2X;
	bar[BAR_ROULETTE].speed2 = bar[BAR_ROULETTE].speed = 8 * _2X;
	bar[BAR_ROULETTE].speedIncrement2 = bar[BAR_ROULETTE].speedIncrement = 1 * _2X;
	bar[BAR_ROULETTE].frame = 1;

	//bar[BAR_HEARTBET].active = false;
	bar[BAR_HEARTBET].targetX = bar[BAR_HEARTBET].targetX2 = bar[BAR_HEARTBET].x - 80 * _2X;
	bar[BAR_HEARTBET].targetY = bar[BAR_HEARTBET].targetY2 = bar[BAR_HEARTBET].y;
	bar[BAR_HEARTBET].speed2 = bar[BAR_HEARTBET].speed = 8 * _2X;
	bar[BAR_HEARTBET].speedIncrement2 = bar[BAR_HEARTBET].speedIncrement = 1 * _2X;
	bar[BAR_HEARTBET].frame = 1;

	//bar[BAR_HEART].active = false;
	//bar[BAR_HEART].targetX = bar[BAR_HEART].targetX2 = bar[BAR_HEART].x;
	//bar[BAR_HEART].targetY = bar[BAR_HEART].targetY2 = bar[BAR_HEART].y - 128 * _2X;
	//bar[BAR_HEART].speed2 = bar[BAR_HEART].speed = 8 * _2X;
	//bar[BAR_HEART].speedIncrement2 = bar[BAR_HEART].speedIncrement = 1 * _2X;
	//bar[BAR_HEART].frame = 1;

	//bar[BAR_PLAY].active = false;
	//bar[BAR_PLAY].targetX = bar[BAR_PLAY].targetX2 = bar[BAR_PLAY].x;
	//bar[BAR_PLAY].targetY = bar[BAR_PLAY].targetY2 = bar[BAR_PLAY].y - 48 * _2X;
	//bar[BAR_PLAY].speed2 = bar[BAR_PLAY].speed = 8 * _2X;
	//bar[BAR_PLAY].speedIncrement2 = bar[BAR_PLAY].speedIncrement = 1 * _2X;
	//bar[BAR_PLAY].frame = 1;

	//bar[BAR_BOSSHP].active = false;
	bar[BAR_BOSSHP].targetX = bar[BAR_BOSSHP].targetX2 = bar[BAR_BOSSHP].x;
	bar[BAR_BOSSHP].targetY = bar[BAR_BOSSHP].targetY2 = bar[BAR_BOSSHP].y - 40 * _2X;
	bar[BAR_BOSSHP].speed2 = bar[BAR_BOSSHP].speed = 8 * _2X;
	bar[BAR_BOSSHP].speedIncrement2 = bar[BAR_BOSSHP].speedIncrement = 1 * _2X;
	bar[BAR_BOSSHP].frame = 1;
	bar[BAR_BOSSHP].count = 0;
	bar[BAR_BOSSHP].add = 0;
	bar[BAR_BOSSHP].countFrame = 0;
	bar[BAR_BOSSHP].max = 0;
	bar[BAR_BOSSHP].addView = false;
	bar[BAR_BOSSHP].addViewSum = 0;

	//bar[BAR_DAY].active = false;
	bar[BAR_DAY].targetX = bar[BAR_DAY].targetX2 = bar[BAR_DAY].x;
	bar[BAR_DAY].targetY = bar[BAR_DAY].targetY2 = bar[BAR_DAY].y;
	bar[BAR_DAY].zoomEnd = bar[BAR_DAY].zoom * 8;//커졌다가 줄면서
	bar[BAR_DAY].zoomEnd2 = 0;//완전히 사라지면
	bar[BAR_DAY].zoomIncrement = 0.5f;
	bar[BAR_DAY].zoomIncrement2 = 1.0f;
	bar[BAR_DAY].speed2 = bar[BAR_DAY].speed = 8 * _2X;
	bar[BAR_DAY].speedIncrement2 = bar[BAR_DAY].speedIncrement = 0.1f;
	bar[BAR_DAY].frame = 1;



	//bar[BAR_CROWN].active = false;
	//bar[BAR_SHIELD].active = false;
	
	//한 턴 기준으로 획득할 
	//bar[BAR_RAIDCOIN].active = true;

	areaFrame = INFOFRAME;

	//for (i = 0; i < MAXCREW; i++) {
	//	ao[ENEMY + i].coolTime = enemyHouse.crewTime[i];
	//	//ao[ENEMY + i].coolTime = 0;
	//}

	if (curID == -1)
		PlayMusic(M_EVENT_EMERG);

	//bar[BAR_COIN].y += 20 * _2X;
	//bar[BAR_ENEMYUSER].y += 20 * _2X;

	//if (robin.bossRoom == true)
	//	bar[BAR_BOSSHP].active = false;

	//memset(&controlMark, 0, sizeof(controlMark));
	//memset(&cardMark, 0, sizeof(cardMark));

	//InitBar(BAR_ENEMYUSER);

	initControlerFrame = 0;
	//initControlerFrame = 1;
	for (i = 0; i < TOTALCONTROLMARK; i++)
		controlerSpread[i] = true;

	memset(&controlMark, 0, sizeof(controlMark));
	attackSequence = ATTACKSEQUENCE_READY;
	arenaStatus = STATUS_READY;

	betBattle = 0;
	turn = PLAYER;
	turnFrame = 0;
	turnPosition = HERE;

	for (i = 0; i < TOTALOBJECT; i++) {
		ao[i].turn = 0;
		ao[i].turnPosition = HERE;
	}

	arenaStatus = STATUS_PLAY;

	touchDisable = false;
	//dioramaZoom = DIORAMAZOOM_BATTLE;
	//wheelAngle = 0;
	//wheelSpeed = 0;
	//SetHero();
	//SetBattleCrew();

	battleStartFrame = BATTLESTARTFRAME;

	drawHandle = MD_BATTLE;
	keyHandle = MK_BATTLE;

	option.gameMode = ACTIONRPG;
	//보스를 한번 생성
	WaveControler();
	bar[BAR_BOSSHP].max = GetTotalEnemyHp(robin.stage);
	InitBar(BAR_JUMP);
	InitBar(BAR_BATTLECOIN);
	InitBar(BAR_JOYSTICK);

	joyPressed = false;
	joyDir = -1;
}

void SetRaidBox(bool activeVal)
{
	int i;
	int emptySlot;
	int bigSlot;
	long long totalGold = enemyHouse.gold * GetBetHeart(ao[PLAYER].equip[EQUIP_WEAPON].detail, ao[PLAYER].equip[EQUIP_WEAPON].grade, bet);

	int startIdx;

	//HOUSE * house = &stageHouse;
	HOUSE* house = &enemyHouse;

	emptySlot = Random(TOTALRAIDBOX);//꽝결정

	do {
		bigSlot = Random(TOTALRAIDBOX);//대박결정
	} while (emptySlot == bigSlot);

	//루프를 돌면서 꽝인지 대박인지에 따라 슬롯에 골드를 넣어준다.
	for (i = 0; i < TOTALRAIDBOX; i++) {
		raidBox[i].type = OBJ_BOX;
		raidBox[i].active = activeVal;
		//raidBox[i].zoom = 0.2f / MOTIONDIV;
		//raidBox[i].status = BOXSTATUS_APPEAR;
		//raidBox[i].motion = OBJ_BOX0;
		raidBox[i].moveHandler = null;
		raidBox[i].drawHandler = NEUTRALDRAW;
		raidBox[i].attacked = false;
		//raidBox[i].x = xOffset + DX / 2 - (float)DIORAMASIZE_X * dioramaZoom / 2 + (float)houseBoxPos[house->houseType * TOTALRAIDBOX * 2 + i * 2 + 0] * dioramaZoom;
		//raidBox[i].y = STATUSWIN_Y + (rh - 4) * TSIZE - (DY / 2 + (float)DIORAMASIZE_Y * dioramaZoom / 2 + (float)(houseBoxPos[house->houseType * TOTALRAIDBOX * 2 + i * 2 + 1]) * dioramaZoom);
		raidBox[i].frame = 0;
		raidBox[i].cx = (float)ITEMICONSIZE;
		raidBox[i].cy = (float)ITEMICONSIZE;
		raidBox[i].cpx = -(float)ITEMICONSIZE / 2;
		raidBox[i].cpy = +(float)ITEMICONSIZE / 2;

		//꽝이면
		if (i == emptySlot) {
			raidBox[i].gold = 0;
			raidBox[i].str = 0;
		}
		//나머지는 30%
		//하나에 15% x 2
		else if (i != bigSlot) {
			raidBox[i].gold = totalGold * 15 / 100;
			raidBox[i].str = 3;
		}
		//대박이면 70%
		else {
			raidBox[i].gold = totalGold - (totalGold * 15 / 100) * 2;
			raidBox[i].str = 14;
		}

		//ao[ITEMOBJ + i].status = BOXSTATUS_CLOSED;

		//ao[NEUTRAL + i].active = false;
	}

	//bar[BAR_COIN].count = totalGold;
	//bar[BAR_COIN].add = 0;

	//bar[BAR_COIN].active = true;
}

void GotoRaid(void)
{
	int i;
	int doorY = 10 * TSIZE;
	int count;
	int emptySlot;
	int bigSlot;

	OBJECT* pObj = &ao[PLAYER];
	OBJECT* eObj = &ao[ENEMY];

	if (touch) {
		touchMode = TOUCH_PLAY;
		touchModeOld = null;
		touchIndex = 0;
		swipeIndex = 0;
	}

	effect.color = effect.color2 = false;
	memset(&robin.enemyObj, 0, sizeof(robin.enemyObj));
	memcpy(&robin.enemyObj, eObj, sizeof(robin.enemyObj));
	//for (i = 0; i < MAXENEMY * MAXENEMYOBJ; i++)
	//	robin.enemyObj[i].active = false;
	memset(&ao[SOLDIER], 0, sizeof(OBJECT));
	memcpy(&ao[SOLDIER], &ao[PLAYER], sizeof(OBJECT));
	ao[SOLDIER].active = false;

	curMenu = MENU_PLAY;

	drawHandle = MD_RAID;
	keyHandle = MK_RAID;

	SetRaidBox(false);


	//간혹 장비상자가 떨어지기도 한다.

	attackSequence = attackType = attackStr = false;
	sequenceFrame = false;
	//여기서 공격슬롯 관련 정보를 초기화한다.

	//레이드 회수를 초기화하고
	raidChance = TOTALRAIDCHANCE;


	joyStickAni = 0;
	joyStickDir = LEFT;

	//autoPlay = false;

	bar[BAR_BOX].active = false;
#ifdef ENEMYHPBAR
	bar[BAR_ENEMYHP].active = false;
#endif
	bar[BAR_QUEST].active = false;
	bar[BAR_HAMMER].active = false;
	bar[BAR_SHIELD].active = false;
	bar[BAR_CROWN].active = false;
	bar[BAR_GOLD].front = false;

	pObj->active = false;

	pObj->zoom = HOUSEPLAYERZOOM;
	pObj->x = DX / 2;
	//pObj->x = 42 * _2X;

	pObj->dirF = pObj->dirX = RIGHT;
	pObj->dx = 0;

#ifdef ENEMYUSER
	SetHouseCrew(robin.enemyUserIdx, false);
#else
	SetBossCrew(robin.stage);
#endif

	if (curID == -1)
		PlayMusic(M_EVENT_EMERG);

	turn = NEUTRAL;
#ifdef ENEMYHPBAR
	bar[BAR_ENEMYHP].active = false;
#endif
	bar[BAR_BOX].active = false;
	bar[BAR_GOLD].active = false;
	bar[BAR_CROWN].active = false;
	bar[BAR_QUEST].active = false;
	bar[BAR_HAMMER].active = false;
	bar[BAR_SHIELD].active = false;

	bar[BAR_RAIDCOIN].y = STATUSWIN_Y + 128 * _2X;
	bar[BAR_RAIDCOIN].active = false;

	AddBar(&bar[BAR_COIN], -bar[BAR_COIN].count, BARFRAME);

	//bar[BAR_COIN].y += 20 * _2X;
	//bar[BAR_ENEMYUSER].y += 20 * _2X;

	if (robin.bossRoom == true)
		bar[BAR_BOSSHP].active = false;

	memset(&controlMark, 0, sizeof(controlMark));
	memset(&cardMark, 0, sizeof(cardMark));
#ifdef ENEMYHPBAR
	for (i = 0; i < MAXENEMY; i++)
		bar[BAR_ENEMYHP + i].active = false;
#endif

	//bar[BAR_COIN].y = STATUSWIN_Y + DRAWRAIDNUMGAP;
	//bar[BAR_COIN].count = 0;
	//AddBar(&bar[BAR_COIN], 0, BARFRAME);

	InitBar(BAR_ENEMYUSER);

	initControlerFrame = 0;
	wheelAngle = 0;
	wheelSpeed = 0;

	attackSequence = ATTACKSEQUENCE_READY;
	arenaStatus = STATUS_READY;
}

void WhoIsNextTurn(void)
{
	int crewIdx;
	int i;

	turnListIdx++;
	//이러면 전투 속행이고
	if (turnListIdx < totalTurn) {
		turn = turnList[turnListIdx];//누구턴인지 결정
		if (turn < TOTALCHAR) {
			//주인공이면 달려가서 공격을 한다.
			//ao[turn].attack = ATTACK_NORMAL;
			//ao[turn].turnPosition = GOING;
		}
		else {
			crewIdx = GetCrewIdxFromType(ao[turn].type);
			ao[turn].currentSkill = crewData[crewIdx * CREWDATASIZE + CREWDATA_SKILL1 + GetSameRouletteCnt(turn - CREW) - 1];
			ao[turn].etc = enemyAttackPattern[ao[turn].type * ATTACKPATTERNTOTALDATASIZE + 2 + ATTACKPATTERNDATASIZE * GetSameRouletteCnt(turn - CREW) - 1];
		}
		ao[turn].attackFrame = 0;
		ao[turn].frame = 0;
		ao[turn].mainFrame = 0;
		//attackSequence = ATTACKSEQUENCE_READY;
	}
	//한턴이 종료됨.
	else {
		turnListIdx = 0;
		turn = 0;
		attackSequence = ATTACKSEQUENCE_COIN;

		//여기서 hitCount 초기화
		for (i = 0; i < NEUTRAL; i++)
			ao[i].hitCount = 0;
		//remainedTurn--;
		//
		//if (remainedTurn == 0)
		//	GotoPlay();//로비로 돌아간다.
	}

	turnFrame = 0;
#ifndef SPEEDTURN
	ao[turn].turnPosition = HERE;
#endif

	sequenceFrame = 0;
	actionCardCnt = 0;
	memset(&actionCardArr, false, sizeof(actionCardArr));

	BarAddStop(&bar[BAR_BOSSHP]);
	//BarAddStop(&bar[BAR_BATTLECOIN]);
	for (i = 0; i < TOTALCHAR; i++)
		BarAddStop(&bar[BAR_PLAYERHP + i]);
	for (i = 0; i < MAXENEMY; i++)
		BarAddStop(&bar[BAR_ENEMYHP + i]);

}

//일반 스테이지 진행일 때 다음 스테이지로 가는 함수
void GotoNextStage(void)
{
	int i;
	//마지막 스테이지라면
	if (robin.room == TOTALROOM - 1) {
		if (robin.stage == TOTAL_STAGE - 1) {
			//엔딩
		}
		else {
			robin.stage++;
			robin.room = 0;
			if (robin.stage > robin.maxStage[robin.stage]) {
				robin.maxStage[robin.stage] = robin.stage;
				robin.maxRoom[robin.stage] = 0;
			}
			//SetBossObj();

		}
	}
	//마지막 스테이지가 아니면
	else {
		robin.room++;
		if (robin.stage == robin.maxStage[robin.stage]) {
			if (robin.room > robin.maxRoom[robin.stage])
				robin.maxRoom[robin.stage] = robin.room;
		}
	}
	//주인공 포지션을 잡아준다.
	ao[PLAYER].x = BATTLEPOSITION_PLAYER_X;

	SetRoom();

	robin.curWaveIdx = 0;
	robin.waveTimeStamp = MC_knlCurrentTimeStamp();

	GotoPlay();
}
//일반 스테이지 진행일 때 현재 스테이지 처음으로 가는 함수
void GotoCurrentStage(void)
{
	GotoPlay();
}

//GotoGacha의 역할
//GotoGacha는 무엇이고, GotoReward는 무엇인가
//GotoReward는 rewardMark의 배열에 있는 상자와 재화를 처리하는 것이고
//GotoGacha는 상자가 나왔을 때 상자를 어떻게 처리할지를 처리하는 것이다.
//GotoGacha로 갈 때 상자안에 있는 내용물이 픽스되어 있거나 픽스되어 있지 않을수 있다. 
//픽스되어 있지 않은 경우에는 조건을 분석하여 몇개의 어떤 아이템을 내보낼것인지 정리하여 보낸다.

//!!!!! 상자내에서 나오는 아이템은 상자가 될수 없다.(이렇게 되면 재귀호출이 되면서 유저에게는 별 영향이 없으면서 망한다.)

//보상을 받는 프로세스는 2가지 스타트포인트가 있다.
//case 1 상자를 열어서 아이템이 n개 나오면 이건 그냥 흡수하면 된다.(Gacha)

//case 2 상자를 열어서 

//1.어디서 들어오던 rewardMark로부터 시작한다.
//- rewardMark는 상자와 동전, 하트와 같은 재화들이 이미 뒤섞여 있다.
//- rewardMark의 순서대로 획득을 하는데, 첫 아이템이 
//2.박스를 세팅하고,
//3.
void GotoGacha()
{
	int i, j = 0, k = 0, l = 0;
	int boxRewardCnt = 0;
	int boxCardCnt = 0;
	int collectionIdx;
	int houseIdx;
	int tempValue;
	bool sameItem = false;

	before_DrawHandle_Gacha = drawHandle;
	before_KeyHandle_Gacha = keyHandle;
	before_CurMenu_Gacha = curMenu;

	attackSequenceBefore = attackSequence;
	attackTypeBefore = attackType;
	attackStrBefore = attackStr;
	attackDelayBefore = attackDelay;
	rewardItemCntBefore = rewardItemCnt;

	drawHandle = MD_GACHA;
	keyHandle = MK_GACHA;

	playmap = robinmap;

	gachaIndex = 0;

	//박스에서 카드 보상
	memset(&boxCardItemCnt, 0, sizeof(boxCardItemCnt));
	memset(&boxCardItem, 0, sizeof(boxCardItem));

	//연출용 효과를 초기화하고
	for (i = 0; i < TOTALCARDMARK; i++) {
		memset(&boxMark[i], 0, sizeof(ICONMARK));//박스
		memset(&boxCardMark[i], 0, sizeof(ICONMARK));//박스에서 나온 카드
	}

	newItemCnt = 0;
	curNewItemIdx = -1;

	//총 박스 카운트를 확인하고
	for (i = 0; i < TOTALREWARDMARK; i++) {
		if (rewardMark[i].type == ITEM_BOX) {
			for (j = 0; j < BOX1MAXREWARDITEM; j++) {
				switch (rewardBoxData[rewardMark[i].detail * TOTALGRADE * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + rewardMark[i].grade * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + j * REWARDITEMDATASIZE]) {
				case -1:
					break;
				case BOX_EQUIP:
				case BOX_RANDOM:
				case BOX_CREW:
					boxCardItemCnt[boxCnt] = rewardBoxData[rewardMark[i].detail * TOTALGRADE * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + rewardMark[i].grade * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + j * REWARDITEMDATASIZE + 3];

					//일단 아이템을 보상아이템에 할당한다.
					for (k = 0; k < boxCardItemCnt[boxCnt]; k++) {
						do {
							if (rewardBoxData[rewardMark[i].detail * TOTALGRADE * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + rewardMark[i].grade * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + j * REWARDITEMDATASIZE] != BOX_CREW) {
								boxCardItem[boxCnt][k].type = MakeItemType(Random(ITEMTYPESEED));
							}
							//크류면
							else {
								boxCardItem[boxCnt][k].type = ITEM_CREW;
							}

							boxCardItem[boxCnt][k].detail = MakeItemDetail(boxCardItem[boxCnt][k].type, robin.lv + rewardMark[i].detail);
							boxCardItem[boxCnt][k].grade = MakeItemGrade(boxCardItem[boxCnt][k].type, robin.lv + rewardMark[i].detail, boxCardItem[boxCnt][k].detail);
							boxCardItem[boxCnt][k].count = 1;

							sameItem = false;

							for (l = 0; l < k; l++) {
								if (boxCardItem[boxCnt][l].type == boxCardItem[boxCnt][k].type && boxCardItem[boxCnt][l].detail == boxCardItem[boxCnt][k].detail && boxCardItem[boxCnt][l].grade == boxCardItem[boxCnt][k].grade) {
									sameItem = true;
								}
							}
						} while (sameItem == true);

						if (GetInvenIdx(boxCardItem[boxCnt][j].type, boxCardItem[boxCnt][j].detail, boxCardItem[boxCnt][j].grade) == -1) {
							boxCardItem[boxCnt][j].seen = false;
							newItemCnt++;
							//curNewItemIdx = j;
						}
						else
							boxCardItem[boxCnt][j].seen = true;
						//TEST
						//boxCardItem[boxCnt][j].seen = false;
					}


					break;
				default:
					boxCardItem[boxCnt][boxCardItemCnt[boxCnt]].type = rewardBoxData[rewardMark[i].detail * TOTALGRADE * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + rewardMark[i].grade * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + j * REWARDITEMDATASIZE];
					boxCardItem[boxCnt][boxCardItemCnt[boxCnt]].detail = rewardBoxData[rewardMark[i].detail * TOTALGRADE * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + rewardMark[i].grade * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + j * REWARDITEMDATASIZE + 1];
					boxCardItem[boxCnt][boxCardItemCnt[boxCnt]].grade = rewardBoxData[rewardMark[i].detail * TOTALGRADE * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + rewardMark[i].grade * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + j * REWARDITEMDATASIZE + 2];

					boxCardItem[boxCnt][boxCardItemCnt[boxCnt]].count = rewardBoxData[rewardMark[i].detail * TOTALGRADE * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + rewardMark[i].grade * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + j * REWARDITEMDATASIZE + 3] + Random(rewardBoxData[rewardMark[i].detail * TOTALGRADE * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + rewardMark[i].grade * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + j * REWARDITEMDATASIZE + 4] - rewardBoxData[rewardMark[i].detail * TOTALGRADE * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + rewardMark[i].grade * BOX1MAXREWARDITEM * REWARDITEMDATASIZE + j * REWARDITEMDATASIZE + 3]);

					tempValue = pow(10, Max(0, GetNumFigure(boxCardItem[boxCnt][boxCardItemCnt[boxCnt]].count) - 2));

					boxCardItem[boxCnt][boxCardItemCnt[boxCnt]].count = boxCardItem[boxCnt][boxCardItemCnt[boxCnt]].count / tempValue * tempValue;

					boxCardItemCnt[boxCnt]++;
					break;
				}

			}
			//첫박스만 표시해 준다.
			if (boxCnt == 0)
				SetBoxMark(xOffset + DX / 2, DY + REWARDCARDSIZE_Y, xOffset + DX / 2, DY + REWARDCARDSIZE_Y, xOffset + DX / 2, STATUSWIN_Y2, 2 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, 32 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, FPS * 3, FPS * 3, 30, rewardMark[i].detail, rewardMark[i].grade, rewardMark[i].detail == BOX_INGAME ? 3.0f : 2.0f * 2 / 3, rewardMark[i].detail == BOX_INGAME ? 3.0f : 2.0f * 2 / 3, 0.2f / MOTIONDIV, rewardMark[i].detail == BOX_INGAME ? 3.0f : 2.0f * 2 / 3, rewardMark[i].detail == BOX_INGAME ? 3.0f : 2.0f * 2 / 3, 0.2f / MOTIONDIV);

			boxCnt++;

			memcpy(&rewardItem[i], &rewardItem[i + 1], (MAXREWARDITEM - (i + 1)) * sizeof(ITEM));

			memcpy(&rewardMark[i], &rewardMark[i + 1], (TOTALREWARDMARK - (i + 1)) * sizeof(ICONMARK));
			rewardItemCnt--;
		}
	}

	memcpy(&rewardMarkBack, &rewardMark, sizeof(rewardMark));
	memcpy(&rewardItemBack, &rewardItem, sizeof(rewardItem));

	rewardItemCntBefore = rewardItemCnt;

	for (i = 0; i < TOTALREWARDMARK; i++) {
		rewardMark[i].frame = 0;
	}

	gachaDepth = 0;
	gachaFrame = 0;
	gachaIndex = 0;
	gachaCardIdx = 0;

	//oldMap = robinmap;
	//robinmap = CASTLE3;
	//SetRoom();

	//ao[PLAYER].active = false;
	//for (i = ENEMY; i < NEUTRAL; i++)
	//	ao[i].active = false;
	bar[BAR_HEART].front = false;

	attackDelay = 0;

	//rewardMark[curRewardBoxIdx].y = DY;
	//rewardMark[curRewardBoxIdx].targetY = STATUSWIN_Y;

}

void GotoNewCollection(void)
{
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	int collectionIdx = GetCollectionIdx(it->type, it->detail, it->grade);
	before_DrawHandle_Collections = drawHandle;
	before_KeyHandle_Collections = keyHandle;
	drawHandle = MD_NEWCOLLECTION;
	keyHandle = MK_NEWCOLLECTION;

	curNewCollection = 0;

	newCollectionDepth = 0;
	newCollectionFrame = 0;

	newCollection = true;

	PlayMusic(M_CHEER);
}

void GotoNewCard()
{
	before_DrawHandle_NewCard = drawHandle;
	before_KeyHandle_NewCard = keyHandle;
	drawHandle = MD_NEWCARD;
	keyHandle = MK_NEWCARD;

	curNewItemIdx = 0;

	newCardDepth = 0;
	newCardFrame = 0;

	PlayMusic(M_CHEER);
}

void GotoStageClear(void)
{
	int i;
	int plusHp;
	//before_DrawHandle_StageClear = drawHandle;
	//before_KeyHandle_StageClear = keyHandle;
	//drawHandle = MD_STAGECLEAR;
	//keyHandle = MK_STAGECLEAR;
	MainMenuIn();

	SetPopUp(POPUPTYPE_STAGE, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
		false, false, false, false, false,
		false, false, false, false, false,
		false, false, false, false, false);

	stageInfoDepth = STAGEINFO_STAGECLEAR;
	stageInfoFrame = 0;

	//curNewItemIdx = 0;

	//stageInfoDepth = 1;
	//stageInfoFrame = 0;

	//selectedCrew = Proc(proc4, 4);

	//bar[BAR_ENEMYUSER].front = false;

	PlayMusic(M_CHEER);


	for (i = ROBIN; i < TOTALCHAR; i++) {
		plusHp = ao[i].ps[PS_HP] - ao[i].hp;
		ao[i].hp = ao[i].ps[PS_HP];//최대값까지 채워두고
		AddBar(&bar[BAR_PLAYERHP + i], plusHp, BARFRAME);
	}

}

void GotoGameOver(void)
{
	int i, j, temp = 0, temp2 = 0;
	ITEM* it;


}

void OutArena(void)
{
	int i;
	//새로 생긴 투기장의 경우
	robinmap = oldMap;
	areaFrame = 0;
	arenaFrame = 0;
	//loadedMap = -1 ;
	SetRoom();

	ao[PLAYER].x = oldX;
	ao[PLAYER].y = oldY;
	ao[PLAYER].dirF = ao[PLAYER].dirX = LEFT;
	ao[PLAYER].maxhp = ao[PLAYER].hp = ao[PLAYER].ps[PS_HP];
	ao[PLAYER].mp = ao[PLAYER].ps[PS_MP];
	ao[PLAYER].dead = false;
	RefreshStat(&ao[PLAYER]);

	// AI캐릭터 지워주기
	//for (i = PLAYER + 1; i < PLAYERALL; i++)
	//	memset(&ao[i], 0, sizeof(OBJECT));

	memset(boomerangAway, 0, sizeof(boomerangAway));

	memset(ao[PLAYER].buff, 0, sizeof(ao[PLAYER].buff));

	SaveFlag(0);

	GotoPlay();
}


void DemoTrigger(void)
{
	int i;
	int newRoom = false;

	return;

	if (drawHandle == MD_DEMO)
		return;

	if (arenaFloor > robin.stage * TOTALROOM + robin.room) {
		newRoom = true;

		GotoNextStage();
	}

	for (i = 0; i < movie.dCount; i++) {
		int idx = movie.movies[i];

		if (robin.demoSeen[idx] == true)
			continue;

		switch (demoData[idx * DDLEN + 1]) {
		case TRIGGER_ROOM:
			//처음 보는 방인 경우
			if (robin.demoSeen[demoData[idx * DDLEN + 2]] == true && robin.demoSeen[demoData[idx * DDLEN + 3]] == true)
				SetDemo(idx);
			break;
		case TRIGGER_PLACE:
		case TRIGGER_ALWAYS_PLACE:
			if (robin.bossRoom == false && (ao[raidPlayer].x <= demoData[idx * DDLEN + 2] * TSIZE + 4 * _2X && ao[raidPlayer].x >= demoData[idx * DDLEN + 2] * TSIZE - TSIZE - 4 * _2X)) {
				SetDemo(idx);
				return;
			}
			break;
		case TRIGGER_PLACE_SANDWICH:
			//특정 위치에 도달하면
			//if ((d.demoData[idx * DDLEN + 2] == null || (o[PLAYER]->x < d.demoData[idx * DDLEN + 2] * TSIZE && o[PLAYER]->x > d.demoData[idx * DDLEN + 2] * TSIZE - TSIZE)) && (d.demoData[idx * DDLEN + 3] == null || (o[PLAYER]->y < d.demoData[idx * DDLEN + 3] * TSIZE && o[PLAYER]->y > d.demoData[idx * DDLEN + 3] * TSIZE - TSIZE))) {
			if (robin.bossRoom == false && (ao[raidPlayer].x <= demoData[idx * DDLEN + 2] * TSIZE + 1 * _2X && ao[raidPlayer].x >= demoData[idx * DDLEN + 3] * TSIZE - TSIZE - 1 * _2X)) {
				//if ((idx == DEMO_90 || idx == DEMO_168) && robin.bossRoom == true) {
				//	continue;
				//}
				//else if (idx == DEMO_104 && !getBit(robin.demoSeen, DEMO_103)) {
				//	continue;
				//}
				//else {
				SetDemo(idx);
				return;
				//}
			}
			break;
		case TRIGGER_PLACE_LIMIT:
			//특정 이하위치에 도달하면
			if (ao[raidPlayer].x <= demoData[idx * DDLEN + 2] * TSIZE && ao[raidPlayer].y <= demoData[idx * DDLEN + 3] * TSIZE) {
				switch (idx) {
				default:
					SetDemo(idx);
					break;
				}
				return;
			}
			break;
		case TRIGGER_PLACE_LIMIT2:
			//x축으로는 특정 이하, y축으로는 특정 이상
			if (ao[raidPlayer].x < demoData[idx * DDLEN + 2] * TSIZE && ao[raidPlayer].y >= demoData[idx * DDLEN + 3] * TSIZE) {
				SetDemo(idx);
				return;
			}
			break;
		case TRIGGER_PLACE_LIMIT3:
			//X축, Y축 모두 특정 이상
			if (ao[raidPlayer].x >= demoData[idx * DDLEN + 2] * TSIZE && ao[raidPlayer].y >= demoData[idx * DDLEN + 3] * TSIZE) {
				SetDemo(idx);
			}
			break;
		case TRIGGER_PLACE_LIMIT4:
			//x축으로는 특정 이상, y축으로는 특정 이하
			if (ao[raidPlayer].x >= demoData[idx * DDLEN + 2] * TSIZE && ao[raidPlayer].y <= demoData[idx * DDLEN + 3] * TSIZE) {
				SetDemo(idx);
				return;
			}
			break;
		}
	}
}

void AddPlayer(OBJECT* pMom)
{
	int i;

	pMom->dx = 0;
	pMom->dy = 0;
	pMom->jumpFrame = 0;
	pMom->status = WALK;

	for (i = 1; i < 3; i++) {
		memcpy(&ao[i], pMom, sizeof(OBJECT));
		ao[PLAYER + i].cmf = (pMom->cmf + i) % 3;
		ao[PLAYER + i].type = (pMom->cmf + i) % 3;
		ao[PLAYER + i].name = TEXT_MONSTERNAME_START + (pMom->type + i) % 3;
	}

}

void SpreadPlayer(int type1, int type2, int type3)
{
	int i, j;
	OBJECT* tempObj = 0;

	for (i = 0; i < 3; i++) {
		if (ao[i].type == type2) {
			tempObj = &ao[i];
			break;
		}
	}

	tempObj->y += 2;
	GetTile(tempObj);
	tempObj->y -= 2;

	for (i = 0; i < 3; i++) {
		demoPlayerX[i] = 0;

		if (ao[PLAYER + i].type == type2)
			ao[PLAYER + i].dx = 0;
		else {
			ao[PLAYER + i].status = JUMP;
			ao[PLAYER + i].jumpFrame = JUMPFRAME - 1;
			ao[PLAYER + i].dx = (ao[PLAYER + i].type == type1 ? -4 : 4) * _2X;

			if (ao[PLAYER + i].inTile == WATER && ao[PLAYER + i].type == type3)
				ao[PLAYER + i].dx = 2 * _2X;

			j = (ao[PLAYER + i].type == type1 ? tempObj->tileX1 - 1 : tempObj->tileX2 + 1);

			// 공간검사해서 dx 업데이트
			if (mapInfoArray[mapInfoOff + tempObj->tileY2 * rw + j] < TILE_BLOCK ||
				mapInfoArray[mapInfoOff + tempObj->tileY1 * rw + j] >= TILE_BLOCK)
				ao[PLAYER + i].dx = 0;
		}

		ao[PLAYER + i].dirX = ao[PLAYER + i].dirF = ao[PLAYER].dirX;

		ao[PLAYER + i].x += ao[PLAYER + i].dx;
	}

	if (frame % MOTIONDIV == 0)
		demoFrame++;

	if (demoFrame >= 6) {
		for (i = PLAYER; i < TOTALCHAR; i++) {
			ao[PLAYER + i].dx = 0;
			demoPlayerX[PLAYER + i] = 0;
		}

		movie.type = MOVIE_MOVE;
	}
}

// 해당 타일을 type값으로 변경시켜줌
void ChangeTile(int x, int y, int width, int height, int type)
{
	int i, j;

	//마왕성 상층 13번방 특수하게 타일정보, 타일이미지 변경
	if (type >= 50) {
		for (i = y; i < y + height; i++) {
			for (j = x; j < x + width; j++) {
				mapInfoArray[mapInfoOff + i * rw + j] = 0;
				mapArray[i * (rw - 4) + j] = 0;
				//첫 타일줄에는 벽마무리 그림 넣는다.
				if (i == y && j == x) {
					mapArray[(i - 1) * (rw - 4) + j] = 33;
					mapArray[(i - 1) * (rw - 4) + (j + 1)] = 12;
				}

				//마지막 타일줄에는 발판그림을 넣는다.
				else if (i == y + height - 1) {
					mapArray[i * (rw - 4) + j] = 5 + (j % 2);
					mapArray[(i + 1) * (rw - 4) + j] = 13 + (j % 2);
				}
			}
		}
	}

	else {
		for (i = y; i < y + height; i++) {
			for (j = x; j < x + width; j++)
				mapInfoArray[mapInfoOff + i * rw + j] = type;
		}
	}
}

void SaveEtc(void)
{
	//파일 저장
#ifdef CRYPT
	EncryptFile(GAMEFILE, (char*)&game, sizeof(GAMEDATA));
#else
	GameWriteFile(GAMEFILE, (char*)&game, sizeof(GAMEDATA));
#endif
}

// Save & Load
void SaveGame(void)
{
	int i, j;

	running = false;

	//원본 세이브파일 읽어오기
//#ifdef CRYPT
//	DecryptFile(SAVEFILE, saveMem, sizeof(ROBINDATA));
//#else
//	ReadFile(SAVEFILE, saveMem, sizeof(ROBINDATA));
//#endif

	for (i = ROBIN; i < TOTALPLAYER; i++) {
		RefreshStat(&ao[i]);
		memcpy((char*)&robin.charData[i].equip, &ao[i].equip, sizeof(ITEM) * TOTALEQUIP);
		memcpy((char*)&robin.charData[i].getSkillList, &ao[i].getSkillList, MAXCHARSKILL);
		memcpy((char*)&robin.charData[i].skillLv, &ao[i].skillLv, TOTAL_SKILL);

		robin.charData[i].exps = ao[i].exps;
		robin.charData[i].hp = ao[i].hp;
		robin.charData[i].mp = ao[i].mp;
		robin.charData[i].ap = ao[i].ap;
		robin.charData[i].sp = ao[i].sp;

		//robin.totalDmgRecord[i] = ao[i].totalDmgRecord;
		//robin.onceDmgRecord[i] = ao[i].onceDmgRecord;
	}
	//할당된 메모리에 세이브영역 카피
	memcpy(saveMem, &robin, sizeof(ROBINDATA));
#ifdef LOCALSAVE

	//파일쓰기
#ifdef CRYPT
	EncryptFile(SAVEFILE, saveMem, sizeof(ROBINDATA));
#else
	GameWriteFile(SAVEFILE, saveMem, sizeof(ROBINDATA));
#endif

#endif
	//기타 작업
	newStart = 0;
	option.usedResurrection = 0;

	//파일쓰기
	//SaveOption();

	//SaveEtc();

	running = true;
}


void LoadRoulette(void)
{
	curRouletteStart = 0;
	PlayMusic(M_JOYSTICK);

	startX = xOffset + DX / 2 - (float)(ROULETTECARDSIZE_X) * 0.2f / MOTIONDIV / 2;
	startY = STATUSWIN_Y + JOYSTICKGAP + 32 * _2X;

	targetX = xOffset + ROULETTECARDSIZE_X / 2;// +curRouletteStart * (ROULETTECARDSIZE_X + 1 * _2X)
	targetY = STATUSWIN_Y + JOKBOGAP;

	//SetControlMark(xOffset + DX / 2 - (float)(ROULETTECARDSIZE_X) * 0.2f / MOTIONDIV / 2, STATUSWIN_Y + JOYSTICKGAP + 32 * _2X, startX, startY, false, false, 16 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, false, false, FPS / 2, FPS / 2, actionCardData[actionCardArr[actionCardCnt - 1] * ACTIONCARDDATASIZE + 5], 30.0f, 1, actionCardArr[actionCardCnt - 1], 1, 0.2f / MOTIONDIV, 1.0f, 0.2f / MOTIONDIV, false, false, false, false, false, true, false, PLAYER, true);

	joyStickAni++;
	joyStickDir = RIGHT;
}

void LoadGame(void)
{
	int i, j, result;
	int skillIdx;
	ROBINDATA* pRobin;
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	int collectionIdx;

	InitGame();

	//원본 세이브파일 읽어오기
#ifdef CRYPT
	DecryptFile(SAVEFILE, saveMem, sizeof(ROBINDATA));
#else
	LoadFile(SAVEFILE, saveMem, sizeof(ROBINDATA));
#endif

	//세이브구조체에 카피
	//for (i = 0; i < TOTALINVENTORY; i++)
	//	memcpy(&robin.inven[i], saveMem + i * sizeof(ITEM), sizeof(ITEM));
	memcpy((char*)&robin, saveMem, sizeof(ROBINDATA));

	InitMenu();

}

void SaveOption(void)
{
#ifdef CRYPT
	EncryptFile(OPTIONFILE, (char*)&option, sizeof(OPTION));
#else
	GameWriteFile(OPTIONFILE, (char*)&option, sizeof(OPTION));
#endif
}

void LoadHeroObj(int type)
{
	ao[type].type = ao[type].cmf = type;
	InitStat(&ao[type]);
	memcpy(&ao[type].equip, &robin.charData[type].equip, sizeof(robin.charData[type].equip));
	memcpy(&ao[type].hotKey, &robin.charData[type].hotKey, sizeof(robin.charData[type].hotKey));
	memcpy(&ao[type].getSkillList, &robin.charData[type].getSkillList, sizeof(robin.charData[type].getSkillList));
	ao[type].exps = robin.charData[type].exps;
	ao[type].lv = 1;
	LevelUpObj(&ao[type], ao[type].exps);
	memcpy(&ao[type].skillLv, &robin.charData[type].skillLv, sizeof(robin.charData[type].skillLv));
	RefreshStat(&ao[type]);
	//항상 hp는 최대값으로 채워준다.
	ao[type].hp = robin.charData[type].hp = ao[type].ps[PS_HP];
	ao[type].mp = robin.charData[type].mp;
	ao[type].sp = robin.charData[type].sp;
	//if (IsGetHero(type)) {
	//	//InitBar(BAR_INVENTORY + type);
	//	InitBar(BAR_SKILL + type);
	//	//InitBar(BAR_PLAYERHP + type);
	//}

}

void LoadOption(void)
{
#ifdef CRYPT
	DecryptFile(OPTIONFILE, (char*)&option, sizeof(OPTION));
#else
	LoadFile(OPTIONFILE, (char*)&option, sizeof(OPTION));
#endif

#ifdef TOUCH_ADVANCE
	if (touch)
		option.hotSlot = true;
#endif

	//option.effect = false;

	if (option.maxInven < STARTINVENTORY)
		option.maxInven = STARTINVENTORY;

	if (option.gameSpeed != 5.0f && option.gameSpeed != FPS && option.gameSpeed != 20.0f)
		option.gameSpeed = FPS;

	Director::getInstance()->setAnimationInterval(1.0f / option.gameSpeed);
}

void SaveLog(void)
{
#ifdef CRYPT
	EncryptFile(LOGFILE, (char*)battleLog, sizeof(LOG) * TOTAL_LOG);
#else
	GameWriteFile(LOGFILE, (char*)&battleLog, sizeof(LOG) * MAXBATTLELOG);
#endif
}

void LoadLog(void)
{
#ifdef CRYPT
	DecryptFile(LOGFILE, (char*)battleLog, sizeof(LOG) * MAXBATTLELOG);
#else
	LoadFile(LOGFILE, (char*)&battleLog, sizeof(LOG) * MAXBATTLELOG);
#endif
}

void SaveAiHouse(void)
{
#ifdef CRYPT
	EncryptFile(AIDATAFILE, (char*)&aiUserData, sizeof(PVPDATA) * TOTALAI);
#else
	GameWriteFile(AIDATAFILE, (char*)&aiUserHouse, sizeof(HOUSE) * TOTALAI);
#endif
}

void LoadAiHouse(void)
{
#ifdef CRYPT
	DecryptFile(AIDATAFILE, (char*)&aiUserData, sizeof(PVPDATA) * TOTALAI);
#else
	LoadFile(AIDATAFILE, (char*)&aiUserHouse, sizeof(HOUSE) * TOTALAI);
#endif
}

void MakeAiHouse(void)
{
	int i, j, k;
	int aiIndex;

	int houseGoldTier;//현재 골드티어

	int crewCnt;

	//일단 적 순서대로 넣고, 세기 및 티어를 먹인다.
	for (i = 0; i < TOTALAI; i++) {
		aiUserHouse[i].userId = MakeItemId();
		aiUserHouse[i].userProfileImgIdx = i % 31;
		aiUserHouse[i].userName = TEXT_NICKNAME + Random(100);
		for (j = 0; j < TOTALCHAR; j++) {
			for (k = 0; k < TOTALEQUIP; k++) {
				aiUserHouse[i].equipImg[j][k] = Min(Random(i / MAXCREW), 8);
				if (j == k)
					aiUserHouse[i].equipImg[j][k] += 1;
			}
		}
		//aiUserHouse[i].houseType = houseOrder[i / (TOTALAI / TOTALOPENDHOUSE)];//TOTAL_HOUSE 원래 토탈하우스로 해야 되는데
		aiUserHouse[i].houseType = HOUSE_CASTLE;//TOTAL_HOUSE 원래 토탈하우스로 해야 되는데

		//crewCnt = Random(MAXCREW) + 1;
		crewCnt = MAXCREW;
		for (j = 0; j < crewCnt; j++) {
			aiUserHouse[i].crew[j] = crewData[(i / MAXCREW) * CREWDATASIZE + j];
			aiUserHouse[i].crewMaxStar[j] = CREWMAXUPGRADELV;
			aiUserHouse[i].crewCurStar[j] = Random(aiUserHouse[i].crewMaxStar[j]) + 1;
			//if (aiUserHouse[i].crewCurStar[j] < aiUserHouse[i].crewMaxStar[j])
			//	aiUserHouse[i].crewStun[j] = STUN_START_FRAME;
		}

		//현재 공격하는 유저의 상태에 따라 결정해 준다.
		//스테이지 기준 houseGoldStage
		houseGoldTier = aiUserHouse[i].houseType;
		aiUserHouse[i].gold = houseGold[aiUserHouse[i].houseType] + Random(houseGold[aiUserHouse[i + 1].houseType] - houseGold[aiUserHouse[i].houseType]);
	}

	SaveAiHouse();
}
