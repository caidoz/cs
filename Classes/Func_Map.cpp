#include "Func.h"
#include "Write.h"
#include "Data.h"

// 방 셋팅 및 그리기 함수
void ReadMap(int idx)
{
	int i, j;

	//맵 기본정보
	mapData[0] = mapDatas[idx][0];	//맵타입
	mapData[1] = mapDatas[idx][1];	//X타일갯수
	mapData[2] = mapDatas[idx][2];	//Y타일갯수
	mapData[3] = mapDatas[idx][3];	//배경색인덱스
	mapData[4] = mapRectSize[idx];
	mapData[5] = mapBackSize[idx];
	mapData[6] = mapObjSize[idx];
	mapData[7] = mapDatas[idx][4];	//타일의 이미지 넘버
	mapData[8] = mapNeutralSize[idx];
	mapData[9] = mapEnemySize[idx];
	mapData[10] = mapDatas[idx][5];	//현재 방의 사운드(특수상황일때는 다른사운드를 틀어준다.)
	mapData[11] = mapDatas[idx][6];	//현재 방의 타입(보스방인지 일반방인지)
	mapData[12] = mapDatas[idx][7];	//지역명(현재 지역의 이름)
	mapData[13] = mapDatas[idx][8];	//현재 방의 몬스터 레벨
	mapData[14] = mapDatas[idx][9];	//minimapIdx

	//맵 렉트정보 부분
	if (mapData[4] > 0)
		memcpy(mapRect, mapRectPtr[idx], mapData[4] * 5 * sizeof(unsigned char));

	//맵 배경정보 부분
	if (mapData[5] > 0)
		memcpy(mapBackObj, mapBackPtr[idx], mapData[5] * 3 * sizeof(signed short));

	//맵 전경정보 부분
	if (mapData[6] > 0)
		memcpy(mapForeObj, mapObjPtr[idx], mapData[6] * 3 * sizeof(signed short));

	//맵 중립오브젝트정보 부분
	if (mapData[8] > 0)
		memcpy(mapNeutralObj, mapNeutralPtr[idx], mapData[8] * 4 * sizeof(signed short));

	//맵 적오브젝트정보 부분
	if (mapData[9] > 0)
		memcpy(mapEnemyObj, mapEnemyPtr[idx], mapData[9] * 4 * sizeof(unsigned short));

	//맵 타일이미지 부분
	for (i = 0; i < mapData[1] * mapData[2]; i++)
		mapArray[i] = mapPtr[idx][i];

	//맵 타일정보 부분
	for (i = 0; i < mapData[1] * mapData[2]; i++)
		mapInfoArray[i] = mapTilePtr[idx][i];

	rw = mapData[1];
	rh = mapData[2];
	loadedMap = idx;

	i = rh;

	do {
		i--;

		memset(&mapInfoArray[(i + 2) * (rw + 4)], TILE_BLOCK, rw + 4);
		memcpy(&mapInfoArray[(i + 2) * (rw + 4) + 2], &mapInfoArray[i * rw], rw);
		mapInfoArray[(i + 2) * (rw + 4) + 2 + rw] = mapInfoArray[(i + 2) * (rw + 4) + 1 + rw];
		mapInfoArray[(i + 2) * (rw + 4) + 1] = mapInfoArray[(i + 2) * (rw + 4) + 2];
	} while (i != 0);

	memcpy(&mapInfoArray[0], &mapInfoArray[2 * (rw + 4)], rw + 4);
	memcpy(&mapInfoArray[rw + 4], &mapInfoArray[2 * (rw + 4)], rw + 4);
	memcpy(&mapInfoArray[(rw + 4) * (rh + 2)], &mapInfoArray[(rw + 4) * (rh + 1)], rw + 4);
	memcpy(&mapInfoArray[(rw + 4) * (rh + 3)], &mapInfoArray[(rw + 4) * (rh + 1)], rw + 4);

	rw += 4;
	rh += 4;
	mapInfoOff = (unsigned char)rw * 2 + 2;

	/*
	i = rh - 4;

	do {
		i--;
		j = rw - 4;

		do {
			j--;

			switch (mapInfoArray[mapInfoOff + i * rw + j]) {
			default:

				break;
			case TILE_VOID:
			case TILE_SPACE:
				SetColor(0x000000);
				break;
			case TILE_WATER:
				SetColor(0x3399FF);
				break;
			case TILE_SWAMP:
				SetColor(0x663333);
				break;
			}

		} while (j);
	} while (i);
	*/
}

void SetRoom(void)
{
	int i = 0, j, count, k;

	SetScreenRatio();

	if (loadedMap != robinmap) {
		//DEBUG: 튜토리얼 중 SetRoom() 리로드가 왜 다시 도는지 추적. 원인 확인되면 제거.
		if (robinmap == MAP_DIORAMA_TOLEM) {
			gDebugSetRoomReloadCount++;
			gDebugSetRoomReloadFrame = frame;
			gDebugSetRoomReloadAttackSeq = attackSequence;
			gDebugSetRoomReloadArenaStatus = arenaStatus;
			gDebugSetRoomReloadWaveStatus = waveStatus;
		}

		ReadMap(robinmap);
		DoubleBuffering(drawHandle);

		arenaStatus = STATUS_READY;
		ReleasePlayer(&ao[raidPlayer]);
		if (viewRadius) {
			delete viewRadius;
			viewRadius = 0;
			radiusStatus = 0;
		}

		if (mapData[7] == MAPTYPE_PLAIN || mapData[7] == MAPTYPE_TOLEM || mapData[7] == MAPTYPE_VALLEY || mapData[7] == MAPTYPE_ELF || mapData[7] == MAPTYPE_LIGHT)
			radiusStatus = 13;


		//카메라 위치 셋팅
		for (i = 0; i < 20; i++)
			SetCamera();

		//오브젝트 초기화
		for (i = BULLET; i < TOTALOBJECT; i++)
			memset(&ao[i], 0, sizeof(OBJECT));

		SetRoom_BGObj();
		SetRoom_Neutral();
		SetRoom_Demo();
		//SetRoom_Enemy();

		//골드오브젝트 세팅

		//하트, 방패 오브젝트 세팅

		//


		//달성도 초기화 : 평화의 사자 간디(적을 죽이지 않고 연속으로 20개의 방을 이동(마을내부에선 무효. 마을에 들어가면 카운트리셋))
		for (i = ENEMY, j = 0; i < NEUTRAL; i++) {
			if (ao[i].active == false)
				break;

			if (ao[i].type < NPC_CAPTAIN)
				j++;
		}

		curEnemyFrame = 0;
		curEnemy = 0;
		nameFrame = 0;
		itemFrame = 0;
		infoFrame = 0;
		dianaTrapFrame = 0;
		darkStone = 0;
		npcdarkStone = 0;
		arenaItemFrame = 0;

		systemKey = null;
		key_released = true;

		for (i = ROBIN; i < TOTALCHAR; i++) {
			ao[i].onCarpet = 0;
			ao[i].magnet = 0;
			ao[i].pressedKey[0] = NULL;
			ao[i].playerRun = false;
			ao[i].flamer = false;
			boomerangAway[i] = false;
		}

		memset(imgText, 0, sizeof(imgText));
		memset(dmgInfo, 0, sizeof(dmgInfo));
		memset(hitMark, 0, sizeof(hitMark));

		//배경음이 달라지면 틀어주고
		if (drawHandle != MD_DEMO)
			if (robin.bossRoom == false && curID != mapData[10] && drawHandle != MD_BATTLE && drawHandle != MD_RAID) {

				if (ao[raidPlayer].type == DIANA && ao[raidPlayer].flamer && ao[raidPlayer].attack)
					PlayMusic(M_FIRE);
				//TimerMusic();
			}
			else if (robin.bossRoom == true) {
				//TimerMusic();
			}
			else if (bossRaidMode == true) {
			}

		splash.frame = 0;

		//부메랑 초기화
		memset(boomerangAway, 0, sizeof(boomerangAway));

		//엔피씨 이름
		nameFrame = 0;
		nameObj = 0;
		i = 1;

	}

	SetRoom_Etc(i);

	if (drawHandle == MD_PLAY || drawHandle == MD_DEMO)
		//크류는 타일체크를 해서 위치를 보정해 주지 않는다.
		for (k = PLAYER; k < CREW; k++) {

			if (TileCrash(&ao[k]) > 2/* && (ao[k].moveHandler < BULLET3WAYMOVE) && ao[k].type <= MAXX*/) {
				i = 4 * _2X;
				j = ao[k].x;
				count = ao[k].y;

				while (i <= TSIZE * 2 && isDemo == false) {
					ao[k].x = j - i + Random(i * 2);
					ao[k].y = count - i + Random(i * 2);

					if (ao[k].x < TSIZE)
						ao[k].x = TSIZE;
					else if (ao[k].x > (rw - 4) * TSIZE - TSIZE)
						ao[k].x = (rw - 4) * TSIZE - TSIZE;

					if (ao[k].y < TSIZE)
						ao[k].y = TSIZE;
					else if (ao[k].y > (rh - 4) * TSIZE - TSIZE)
						ao[k].y = (rh - 4) * TSIZE - TSIZE;

					if (TileCrash(&ao[k]) < 3)
						break;
					else {
						ao[k].x = j;
						ao[k].y = count;
					}

					i += 4 * _2X;
				}
			}

			ResetLabel();
		}
}

void SetRoom_BGObj(void)
{
	int i = 0, j, count;

	//배경오브젝트 위치 결정
	memset(bgObj, 0, sizeof(bgObj));

	//수중효과 초기화
	if (mapData[4] && (mapData[7] == MAPTYPE_ATLANTICE || mapData[7] == MAPTYPE_CASTLE || mapData[7] == MAPTYPE_FROST))
		InitGraphics();

	switch (mapData[7]) {
	case MAPTYPE_SWAMP:
		//습지 안개
		i = (rw * TSIZE + 199) / 200;
		count = 0;

		do {
			i--;
			j = ((rh - 4) * TSIZE + 79) / 80;

			do {
				j--;

				//활성화
				bgObj[count].active = true;
				//X위치
				bgObj[count].x = i * 200 * _2X + Random(150) * _2X;
				//Y위치
				bgObj[count].y = j * 80 * _2X + Random(60) * _2X;
				//안개 모습
				bgObj[count].etc = Random(2);
				//이동속도
				bgObj[count].dx = -1 * _2X + Random(3) * _2X;

				count++;
			} while (j > 0 && count < MAXBGOBJECT);
		} while (i > 0 && count < MAXBGOBJECT);
		break;
	case MAPTYPE_VALLEY:
		//계곡 흔들리는 갈대
		for (i = 0; i < MAXBGOBJECT; i++)
			bgObj[i].frame = Random(50) + 20;
		break;
	case MAPTYPE_ATLANTICE:
		//아틀란티스 물고기
		i = (rw * TSIZE + 159) / 160;
		count = 0;

		do {
			i--;
			j = ((rh - 4) * TSIZE + 119) / 120;

			do {
				j--;

				//활성화
				bgObj[count].active = true;
				//X위치
				bgObj[count].x = i * 160 * _2X + Random(120) * _2X;
				//Y위치
				bgObj[count].y = j * 120 * _2X + Random(90) * _2X;
				//안개 모습
				bgObj[count].etc = Random(2);
				//이동속도
				bgObj[count].dx = (Random(2) == 0 ? -1 : 1) * (2 + Random(6)) * _2X;

				count++;
			} while (j > 0 && count < MAXBGOBJECT);
		} while (i > 0 && count < MAXBGOBJECT);
		break;
	case MAPTYPE_PLAIN:
		//아델라인평원 나비
		i = (rw * TSIZE + 239) / 240;
		count = 0;

		do {
			i--;
			j = ((rh - 4) * TSIZE + 159) / 160;

			do {
				j--;

				//활성화
				bgObj[count].active = true;
				//X위치
				bgObj[count].x = i * 240 * _2X + Random(180) * _2X;
				//Y위치
				bgObj[count].y = j * 160 * _2X + Random(120) * _2X;
				//이동 방향
				bgObj[count].etc = Random(2);
				//이동속도
				bgObj[count].dx = (2 + Random(3)) * DIR(bgObj[count].etc) * _2X;

				count++;
			} while (j > 0 && count < MAXBGOBJECT);
		} while (i > 0 && count < MAXBGOBJECT);
		break;
	case MAPTYPE_GOLEMVALLEY:
		//골렘 협곡 구름
		i = (rw * TSIZE + 159) / 160;
		count = 0;

		do {
			i--;
			j = ((rh - 4) * TSIZE + 79) / 80;

			do {
				j--;

				//활성화
				bgObj[count].active = true;
				//X위치
				bgObj[count].x = i * 160 * _2X + Random(120) * _2X;
				//Y위치
				bgObj[count].y = j * 80 * _2X + Random(60) * _2X;
				//안개 모습
				bgObj[count].etc = Random(6);
				//이동속도
				bgObj[count].dx = -1 * _2X - Random(2) * _2X;

				count++;
			} while (j > 0 && count < MAXBGOBJECT - 4);
		} while (i > 0 && count < MAXBGOBJECT - 4);
		break;
	case MAPTYPE_DARKNESS:
		//어둠의 정령 별
		count = 0;

		do {
			//활성화
			bgObj[count].active = true;
			//X위치
			bgObj[count].x = -4 + Random(rw * TSIZE + 8);
			//Y위치
			bgObj[count].y = -4 + Random(120);
			//etc
			bgObj[count].etc = Random(64);

			count++;
		} while (count < MAXBGOBJECT);
		break;
	case MAPTYPE_GHOST:
		//망자의 도시 구름 및 안개
		i = (rw * TSIZE + 159) / 160;
		count = 0;

		do {
			i--;
			j = ((rh - 4) * TSIZE + 79) / 80;

			do {
				j--;

				//활성화
				bgObj[count].active = true;
				//X위치
				bgObj[count].x = i * 160 * _2X + Random(120) * _2X;
				//Y위치
				bgObj[count].y = j * 80 * _2X + Random(60) * _2X;
				//안개 모습
				bgObj[count].etc = Random(3);
				//이동속도
				bgObj[count].dx = -1 * _2X - Random(2) * _2X;

				count++;
			} while (j > 0 && count < MAXBGOBJECT);
		} while (i > 0 && count < MAXBGOBJECT);
		break;
	case MAPTYPE_SPACE:
		//우주 위성
		i = (rw * TSIZE + 159) / 160;
		count = 0;

		do {
			i--;
			j = ((rh - 4) * TSIZE + 119) / 120;

			do {
				j--;

				//활성화
				bgObj[count].active = true;
				//X위치
				bgObj[count].x = i * 160 * _2X + Random(120) * _2X;
				//Y위치
				bgObj[count].y = j * 120 * _2X + Random(90) * _2X;
				//안개 모습
				bgObj[count].etc = Random(3);
				//이동속도
				bgObj[count].dx = -1 * _2X - Random(2) * _2X;

				count++;
			} while (j > 0 && count < MAXBGOBJECT / 2);
		} while (i > 0 && count < MAXBGOBJECT / 2);
		break;
	}
}


void SetRoom_Neutral(void)
{
	int i, j, k;

	//중립오브젝트
	for (i = 0, j = 0; i < ITEMOBJ - NEUTRAL; i++) {
		OBJECT* pObj = &ao[NEUTRAL + j];
		const signed short* sPtr;

		if (i < mapData[8]) {
			pObj->active = true;
			pObj->type = mapNeutralObj[i * 4];
			pObj->x = mapNeutralObj[i * 4 + 1];
			pObj->y = mapNeutralObj[i * 4 + 2];
			pObj->etc = mapNeutralObj[i * 4 + 3];
			pObj->drawHandler = NEUTRALDRAW;
			pObj->cmf = -1;
			if (pObj->type == OBJ_DOOR)
				pObj->zoom = 1.0f;
			else if (pObj->type == OBJ_BOX) {
				if (GetObjFromPtr(pObj) == ITEMBOX)
					pObj->zoom = BOXCASTLEZOOM * (1.0f + (float)0.05f * robin.castle);// BOXZOOM;
				else
					pObj->zoom = BOXCASTLEZOOM * (1.0f + (float)0.05f * robin.castle);//dioramaZoom
				pObj->defaultZoom = pObj->zoom;
			}
			else {
				if (drawHandle == MD_BATTLE)
					pObj->zoom = BATTLEZOOM;
				else
					pObj->zoom = LOBBYZOOM;
			}

			sPtr = &neutralData[pObj->type * NEUTRALDATASIZE];

			pObj->block = *sPtr;

			pObj->attr = *(sPtr + 1);
			pObj->x += *(sPtr + 2);
			pObj->y += *(sPtr + 3);
			pObj->cpx = (float)*(sPtr + 4) * pObj->zoom;
			pObj->cpy = (float)*(sPtr + 5) * pObj->zoom;
			pObj->cx = (float)*(sPtr + 6) * pObj->zoom;
			pObj->cy = (float)*(sPtr + 7) * pObj->zoom;
			pObj->status = *(sPtr + 8);
			pObj->motion = *(sPtr + 9) & 0xFF;
			pObj->moveHandler = *(sPtr + 10);

			switch (pObj->type) {
			case OBJ_GOLD:
				pObj->cpx = Min(-16 * _2X, (float)*(sPtr + 4) * pObj->zoom);
				pObj->cpy = Min(-32 * _2X, (float)*(sPtr + 5) * pObj->zoom);
				pObj->cx = Max(32 * _2X, (float)*(sPtr + 6) * pObj->zoom);
				pObj->cy = Max(32 * _2X, (float)*(sPtr + 7) * pObj->zoom);
				pObj->maxhp = pObj->hp = enemyHouse.gold;
				break;

			case OBJ_MOVE:
				switch (mapData[7]) {
				case MAPTYPE_FROST:
					pObj->motion = IMG_OBJ_ICESTONE;
					break;
				case MAPTYPE_DEVILCASTLE:
					pObj->motion = IMG_OBJ_DEVILSTEP;
					break;
				}

				if (pObj->etc / MOVE_VERTICAL) {
					pObj->moveHandler = UPDOWNMOVE;
					pObj->etc %= MOVE_VERTICAL;
				}

				if (pObj->etc == 0) {
					//움직여준다
					pObj->mx = true;
					pObj->my = true;
				}
				break;
			case OBJ_SEWAGESTONE:
				if (pObj->etc / MOVE_VERTICAL) {
					pObj->mx = false;
					pObj->my = true;
					pObj->dirY = pObj->etc & 0x01;
				}
				else {
					pObj->mx = true;
					pObj->my = false;
					pObj->dirX = pObj->etc & 0x01;
				}
				break;
			case OBJ_DOOR:

				pObj->icon = doorArray[pObj->etc];

				//필요한 열쇠 입력
				//주인공이 문과 닿아있으면 열린상태로 만들어 준다.
				if (ObjCrash(&ao[PLAYER], pObj)) {
					pObj->status = OPENED;
					pObj->cy = 8 * _2X;
				}
				break;
			case OBJ_BOX:
				//pObj->active = false;
				//if (drawHandle == MD_DEMO) {
				//	pObj->active = true;
				//}
				pObj->drawHandler = BOXDRAW;

				pObj->etc = BOX_CASTLE0 + castleOrder[robin.castle];//BOX_INGAME;

				if (GetObjFromPtr(pObj) == ITEMBOX) {
					pObj->status = BOXSTATUS_APPEAR;
					//pObj->y -= 16 * TSIZE;
				}
				else
					pObj->status = BOXSTATUS_CLOSED;

				if (pObj->x < rw * TSIZE / 2)
					pObj->dirX = pObj->dirF = RIGHT;
				else
					pObj->dirX = pObj->dirF = LEFT;

				switch (pObj->etc) {
					case BOX_CASTLE0:
					case BOX_CASTLE1:
					case BOX_CASTLE2:
					case BOX_CASTLE3:
					case BOX_CASTLE4:
					case BOX_CASTLE5:
					case BOX_CASTLE6:
					case BOX_CASTLE7:
					case BOX_CASTLE8:
					case BOX_CASTLE9:
					case BOX_CASTLE10:
					case BOX_CASTLE11:
					case BOX_CASTLE12:
					case BOX_CASTLE13:
					case BOX_CASTLE14:
					case BOX_CASTLE15:
					case BOX_CASTLE16:
					case BOX_CASTLE17:
					case BOX_CASTLE18:
						pObj->zoom = BOXCASTLEZOOM * (1.0f + (float)0.05f * robin.castle);
						break;
					case BOX_REWARD0:
					case BOX_REWARD1:
					case BOX_REWARD2:
					case BOX_REWARD3:
					case BOX_REWARD4:
					case BOX_REWARD5:
					case BOX_REWARD6:
					case BOX_REWARD7:
						pObj->zoom = BOXCASTLEZOOM * (0.3f + (float)0.02f * (pObj->etc - BOX_REWARD0));
						break;
					default:
						//case BOX_INGAME:
						pObj->zoom = BOXZOOM;
						break;
				}
				break;
			case OBJ_ITEM:
				pObj->active = false;

				if (!(drawHandle == MD_PLAY || drawHandle == MD_BATTLE || drawHandle == MD_RAID || drawHandle == MD_BOSSRAID)) {
					// 상 아이템일때//차원의상일때 - 3개의 오브젝트를 다 setbit했다면
					if (itemArray[pObj->etc * 3] == ITEM_STATUE) {
						if (robin.statue[itemArray[pObj->etc * 3 + 1]])
							break;
					}

					k = DropItem(pObj, itemArray[pObj->etc * 3]);

					ao[k].type = OBJ_ITEM;
					ao[k].def = itemArray[pObj->etc * 3];

					if (pObj->etc >= HIDDEN_0) {
						if (ao[k].def == ITEM_GOLD)
							ao[k].apx = itemArray[pObj->etc * 3 + 1] * 100;
						else {
							ao[k].apx = itemArray[pObj->etc * 3 + 1];
							ao[k].ax = itemArray[pObj->etc * 3 + 2];
						}

						ao[k].ay = GetItemIcon(ao[k].def, ao[k].apx, GRADE_NORMAL);
						ao[k].name = TEXT_ITEMNAME_START + GetItemName(ao[k].def, ao[k].apx, GRADE_NORMAL);
						ao[k].lv = EMPTY;
					}
					else {
						if (pObj->type == ITEM_QUEST && itemArray[pObj->etc * 3 + 2] == ITEM_QUEST_LETTER)
							break;

						ao[k].apx = itemArray[pObj->etc * 3 + 1];
						ao[k].name = TEXT_ITEMNAME_START + GetItemName(ao[k].def, ao[k].apx, GRADE_NORMAL);

						if (ao[k].def == ITEM_QUEST && ao[k].apx != ITEM_QUEST_REDHEART && ao[k].apx != ITEM_QUEST_HOLYHEART && ao[k].apx != ITEM_QUEST_DARKHEART && ao[k].apx != ITEM_QUEST_BLUEHEART && ao[k].apx != ITEM_QUEST_THUNDERHEART && ao[k].apx != ITEM_QUEST_FRUIT && ao[k].apx != ITEM_QUEST_LETTER && ao[k].apx != ITEM_QUEST_KATHERINE)
							ao[k].motion = itemArray[pObj->etc * 3 + 2];
						else
							ao[k].ay = itemArray[pObj->etc * 3 + 2];
					}

					ao[k].etc = pObj->etc;
				}
				break;
			case OBJ_CLOAKING:
			case OBJ_INVISIBLE:
				pObj->y -= TSIZE;
				pObj->mainFrame = pObj->etc * 12;
				break;
			case OBJ_WARP:
				pObj->status = warpArrayType[pObj->etc];
				pObj->cx = warpArray[pObj->etc * 5];
				pObj->cy = warpArray[pObj->etc * 5 + 1];
				pObj->hp = warpArray[pObj->etc * 5 + 2];	//이동할 맵 인덱스
				pObj->str = warpArray[pObj->etc * 5 + 3];	//이동할 맵 X
				pObj->def = warpArray[pObj->etc * 5 + 4];	//이동할 맵 Y

				if (pObj->cx == 1) {
					pObj->cx = TSIZE + 1 * _2X;

					if (pObj->x < rw * TSIZE / 2 * _2X)
						pObj->cpx = -TSIZE;
				}
				else if (pObj->cy == 1 * _2X) {
					pObj->cy = TSIZE + 1 * _2X;

					if (pObj->y < (rh - 4) * TSIZE / 2 * _2X)
						pObj->cpy = -TSIZE;
				}
				break;
			case OBJ_CARPET:
				pObj->str = pObj->x;
				pObj->def = pObj->y;
				pObj->jumpFrame = 2;
				break;
			case OBJ_ROBINTRAP:
				if (pObj->etc == RIGHT) {
					pObj->dirX = pObj->dirF = 1;
					pObj->cpx = 1 * _2X;
				}
				break;
			case OBJ_BUBBLE:
				pObj->drawHandler = NULL;
				break;
			case OBJ_MAGMA:
				if (!pObj->canMagma)
					pObj->block = false;
				break;
			case OBJ_MAGMABLOCK:
				pObj->dx = 4 * (pObj->etc - 1) * _2X;
				pObj->etc = 0;
			case OBJ_STALACTITE:
			case OBJ_SPIKE:
				pObj->str = pObj->x;
				pObj->def = pObj->y;
				break;
			case OBJ_BRIDGE:
				pObj->cx = 192 * _2X;
				break;
			case OBJ_MAGNET:
				pObj->etc = 0;
				break;
			case OBJ_SLED:
				//생성되어있는 발판을 꺼준다.
				for (k = NEUTRAL; k < ITEMOBJ; k++) {
					if (ao[k].active == true && ao[k].type == OBJ_ICEBREAK)
						break;
				}

				if (k == ITEMOBJ)
					pObj->active = false;
				else {
					pObj->dirX = pObj->dirF = pObj->etc;
					pObj->etc = 0;
					pObj->str = pObj->x;
					pObj->def = pObj->y;
				}
				break;
			case OBJ_DIMENSION:
				if (ObjCrash(&ao[raidPlayer], pObj))
					pObj->status = 1;
				break;
			case OBJ_PITCHER:
				pObj->drawHandler = NULL;
			case OBJ_FLOWER:
				break;
			case OBJ_TREE:
				pObj->motion = OBJ_TREE1;
				pObj->zoom = 0.8f;
				pObj->moveHandler = TREEMOVE;
				break;
			case OBJ_FLAG:
				break;
			}

			if (pObj->active || pObj->type == OBJ_BRIDGE || pObj->type == OBJ_BOX)
				j++;
			else
				memset(pObj, 0, sizeof(OBJECT));
		}
	}
}

void SetStageBoss(void)
{
	int i, j;
#ifdef ENEMYHPBAR
	for (i = ENEMY, j = 0; i < NEUTRAL; i++) {
		//몬스터 몸통이면 hp바를 붙여준다.
		if (ao[i].active && ao[i].mom == i) {
			bar[BAR_ENEMYHP + j].count = ao[i].hp;
			j++;
		}
	}
#endif
	for (i = ENEMY; i < NEUTRAL; i++) {
		if (ao[i].active) {
			MoveObj(&ao[i]);
			InitMotion(&ao[i]);
			ao[i].coolTime = MC_knlCurrentTimeStamp();
		}
	}
}


long long CompareCombatPower(ITEM* it1, ITEM* it2)
{
	long long combatPower1;
	long long combatPower2;

	memcpy(&ao[NPC], &ao[it1->type % 3], sizeof(OBJECT));
	memcpy(&ao[NPC].equip[itemEquipSlot[it1->type]], it1, sizeof(ITEM));
	RefreshStat(&ao[NPC]);
	combatPower1 = GetCombatPower(&ao[NPC]);

	memcpy(&ao[NPC], &ao[it2->type % 3], sizeof(OBJECT));
	memcpy(&ao[NPC].equip[itemEquipSlot[it2->type]], it2, sizeof(ITEM));
	RefreshStat(&ao[NPC]);
	combatPower2 = GetCombatPower(&ao[NPC]);

	memset(&ao[NPC], 0, sizeof(OBJECT));

	return combatPower1 - combatPower2;
}

void SetRoom_Etc(int i)
{
	int count;
	int j;
	unsigned char *ucPtr;


	for (j = PLAYER; j < TOTALCHAR; j++) {
		ucPtr = &mapInfoArray[mapInfoOff + ((ao[j].y - 8 * _2X) >> 5) * rw + (ao[j].x >> 5)];

		if (ao[j].onWater > 0 && ao[j].onWater < 3)
			ao[j].onWater++;

		switch (*ucPtr) {
		case TILE_DAMAGE:
			if (ao[j].attackedFrame == 0)
				AttackRobin(ATTACKTYPE_TILE, j);
		default:
			count = GROUND;
			break;
		case TILE_SPACE:
			count = SPACE;
			break;
		case TILE_WATERDAMAGE:
			if (ao[j].attackedFrame == 0)
				AttackRobin(ATTACKTYPE_TILE, j);
		case TILE_WATER:
			count = WATER;
			break;
		case TILE_SWAMP:
			count = SWAMP;
			break;
		}

		//상단 함정타일이 공격하게
		ucPtr = &mapInfoArray[mapInfoOff + ((ao[j].y - 32 + 8) >> 5) * rw + (ao[j].x >> 5)];
		switch (*ucPtr) {
		case TILE_DAMAGE:
		case TILE_WATERDAMAGE:
			if (ao[j].attackedFrame == 0)
				AttackRobin(ATTACKTYPE_TILE, j);
			break;
		}

		if (count != ao[j].inTile) {
			//움직임이 바뀐 경우
			switch (count) {
			case GROUND:
				if (ao[j].canOnWater == true)
					ao[j].onWater = 1;

				ao[j].status = (ao[j].dirY == UP) ? JUMP : FALL;
				ao[j].jumpFrame = 1;
				ao[j].canBreath = true;
				break;
			case SWAMP:
			case WATER:
				ao[j].flamer = 0;
				ao[j].dx = Min(ao[j].dx, 4 * _2X);
				ao[j].dy = Min(ao[j].dy, 4 * _2X);
				ao[j].canBreath = robin.statue[ITEM_STATUE_MERMAID];
				break;
			case SPACE:
				ao[j].canBreath = robin.statue[ITEM_STATUE_SPIRIT];
				break;
			}

			//물이나 습지에 들어간 경우 또는 물이나 습지에서 나온경우
			if (i == 0 && (count == SWAMP || ao[j].inTile == SWAMP || count == WATER || ao[j].inTile == WATER)) {
				splashType = 0;

				//물에 들어간 경우
				if (count == WATER) {
					//바로 위나 아래쪽에 물타일이 있다면
					if (*(ucPtr - rw * 2) != TILE_VOID && *(ucPtr + rw * 2) != TILE_VOID)
						splashType = (ao[j].dirX == LEFT) ? 2 : 3;
					else
						splashType = (ao[j].dirY == UP) ? 1 : 0;

					rpVar2.diver = 0;
				}
				//물에서 나온 경우
				else if (ao[j].inTile == WATER) {
					//바로 위나 아래쪽에 물타일이 있다면
					if (*(ucPtr - rw * 2) == TILE_WATER || *(ucPtr + rw * 2) == TILE_WATER)
						splashType = (ao[j].dirY == UP) ? 0 : 1;
					else
						splashType = (ao[j].dirX == LEFT) ? 3 : 2;

					//달성도 초기화 : 잠수부(수중에 한 번 들어가서 있는 시간)
					rpVar2.diver = 0;
				}
				else if (count == SWAMP) {
					//달성도 초기화 : 잠수부(수중에 한 번 들어가서 있는 시간)
					rpVar2.diver = 0;
				}

				if (mapData[7] == MAPTYPE_FROST)
					splashType = 0;

				splash.frame = 3;

				if (splashType < 2) {
					splash.x = ao[j].x;
					splash.dir = ao[j].dirF;

					for (i = 0; i < mapData[4]; i++) {
						if (mapRect[i * 5 + 4] == EMPTY - splashType && ao[j].x >= (mapRect[i * 5] << 4) * _2X && ao[j].x <= ((mapRect[i * 5] + mapRect[i * 5 + 2]) << 4) * _2X) {
							splash.y = (mapRect[i * 5 + 1] << 4) * _2X + 20 * _2X - splashType * 30 * _2X;
							break;
						}
					}
				}
				else {
					for (i = 0; i < mapData[4]; i++) {
						if (mapRect[i * 5 + 4] < 254 && ao[j].y >= (mapRect[i * 5 + 1] << 3) * _2X && ao[j].y <= ((mapRect[i * 5 + 1] + mapRect[i * 5 + 3]) << 3) * _2X) {
							if (ao[j].x >> 3 <= mapRect[i * 5])
								splash.x = (mapRect[i * 5] << 3) * _2X;
							else
								splash.x = ((mapRect[i * 5] + mapRect[i * 5 + 2]) << 3) * _2X;
						}
					}

					splash.dir = splashType - 2;
					splash.y = ao[j].y;
				}
			}

			ao[j].attack = 0;
			ao[j].inTile = count;
		}
	}

	DemoTrigger();
}

void SetEnemyUser()
{
	//실제로는 pri num을 해야되나 일단은 땜빵으로
	//robin.enemyUserIdx = Random(TOTALAI);
	long long limit = TOTALAI;// *(robin.stage + 1) / TOTAL_STAGE;
	//0번은 제외
	if (!robin.enemyUserIdx) {
		do {
			robin.enemyUserIdx = Random(limit);
		} while (robin.enemyUserIdx == PLAYER);
	}

	//에네미 유저를 세팅하자
	memcpy(&enemyHouse, &aiUserHouse[robin.enemyUserIdx], sizeof(HOUSE));

	

	//enemyHouse 를 셋팅하는 파트

}

//wave[] 의 몇 번째 행인가.
//
//행은 wave_COUNT / (MAXWAVEENEMY * WAVEDATASIZE) 개다(지금 10000). 마지막
//웨이브를 넘어서면 그 뒤는 배열 밖이라 무엇이 읽힐지 알 수 없다. robin.waveIdx
//는 상자를 열 때마다(Func_Gacha.cpp) 끝없이 오르므로 언젠가 반드시 넘는다.
//체력 곡선(GetWaveHp)은 waveIdx 를 그대로 쓰니 계속 세지고, 등장하는 몬스터만
//마지막 행에서 멈춘다.
int GetWaveRow(int waveIdx)
{
	const int rows = wave_COUNT / (MAXWAVEENEMY * WAVEDATASIZE);

	if (waveIdx < 0)
		return 0;
	if (waveIdx >= rows)
		return rows - 1;

	return waveIdx;
}

//그 웨이브가 무슨 자리인가(MONSTERTYPE_*). wave[] 세번째 칸이다.
//
//한 웨이브 안에서는 슬롯 0 이 자리를 대표한다 - 보스 자리는 언제나 한 마리고,
//여러 마리가 나오는 자리는 전부 잡몹이다(tools/content/make_waves.py).
int GetWaveKind(int waveIdx)
{
	return wave[GetWaveRow(waveIdx) * MAXWAVEENEMY * WAVEDATASIZE + 0 * WAVEDATASIZE + 2];
}

//그 자리가 잡몹 체력의 몇 배인가. 100 을 나눈 값이 아니라 그냥 배수다.
int GetWaveHpMul(int waveIdx)
{
	switch (GetWaveKind(waveIdx)) {
	case MONSTERTYPE_BOSS:
		return WAVE_HP_SUBBOSS_MUL;
	case MONSTERTYPE_MIDBOSS:
		return WAVE_HP_MIDBOSS_MUL;
	case MONSTERTYPE_BIGBOSS:
		return WAVE_HP_BIGBOSS_MUL;
	}

	return 1;
}

int GetMaxWaveCnt(void)
{
	int i;

	//AVK_MAXGAME 시연에서는 스킬과 함께 몬스터 세 마리의 모션도 본다.
	if (gDemoForceRoulette)
		return 3;

	//인터랙티브 전투 튜토리얼: 단계마다 몬스터를 딱 한 마리만 상대하게 한다.
	//이 값은 WaveControler()의 스폰 상한이면서 동시에 VanishMove()의 상자 드롭 조건
	//(robin.curWaveIdx == GetMaxWaveCnt() && AliveEnemyCnt() == 0)과 Func_Combat.cpp의
	//waveStatus = WAVESTATUS_END 조건으로도 쓰인다. 여기서 1로 고정해야 한 마리만 스폰되고,
	//그 한 마리를 잡았을 때 정상적으로 상자가 떨어지면서 가챠까지 이어진다.
	if (robinmap == MAP_DIORAMA_TOLEM && !robin.demoSeen[DEMO_TUTORIAL_END])
		return 1;

	//WaveControler()가 스폰하는 행은 robin.waveIdx 다. 여기서 robin.stage/robin.room
	//으로 다른 행을 읽으면 "몇 마리가 나오는가"와 "무엇이 나오는가"가 서로 다른
	//웨이브에서 온다. robin.room 은 아무 데서도 오르지 않으므로 실제로는 늘
	//stage*MAXWAVE 행만 읽혔고, 그래서 wave[] 에 두세 마리를 깔아도 한 마리만
	//나왔다. 스폰하는 쪽과 같은 행을 본다.
	for (i = 0; i < MAXWAVEENEMY; i++) {
		if (wave[GetWaveRow(robin.waveIdx) * MAXWAVEENEMY * WAVEDATASIZE + i * WAVEDATASIZE + 0] == false)
			return i;
	}

	return MAXWAVEENEMY;
}
//획득한 스킬이 있는지 체크
int GetSkillCnt(int acquiredSkills[MAXCHARSKILL])
{
	int i;
	int cnt = 0;
	for (i = 0; i < MAXCHARSKILL; i++) {
		if (acquiredSkills[i] > 0)
			cnt++;
	}
	return cnt;
}

//현재 획득한 스킬이 있을 때 
// 스킬을 확률적으로 선택하는 함수
int selectRandomSkill(int characterID, int acquiredSkills[MAXCHARSKILL])
{
	int i, j;
	int cumulativeProb = 0;
	int accumulatedProb = 0;
	int skillProb;
	int skillID;
	bool isSkillAcquired;
	int randomValue;

	// 현재 획득한 스킬 중에서만 확률에 따라 선택
	for (i = 0; i < MAXCHARSKILL; i++) {
		skillProb = activeSkillProb[characterID][2 * i];
		skillID = activeSkillProb[characterID][2 * i + 1];

		// 스킬이 획득되었는지 확인
		isSkillAcquired = false;
		for (j = 0; j < MAXCHARSKILL; j++) {
			if (acquiredSkills[j] == skillID) {
				isSkillAcquired = true;
				break;
			}
		}

		// 획득된 스킬에 대해 확률을 더함
		if (isSkillAcquired) {
			cumulativeProb += skillProb;
		}
	}

	// 누적된 확률이 0이라면 획득한 스킬이 없다는 뜻이므로 -1 반환
	if (cumulativeProb == 0) {
		return -1;  // 스킬 없음
	}

	// 랜덤한 값을 생성하여 그 값에 따라 스킬을 선택
	randomValue = rand() % cumulativeProb;
	
	for (i = 0; i < MAXCHARSKILL; i++) {
		skillProb = activeSkillProb[characterID][2 * i];
		skillID = activeSkillProb[characterID][2 * i + 1];

		// 스킬이 획득되었는지 확인
		isSkillAcquired = false;
		for (j = 0; j < MAXCHARSKILL; j++) {
			if (acquiredSkills[j] == skillID) {
				isSkillAcquired = true;
				break;
			}
		}

		// 획득된 스킬에 대해 누적 확률을 계산
		if (isSkillAcquired) {
			accumulatedProb += skillProb;
			if (randomValue < accumulatedProb) {
				return skillID;  // 선택된 스킬 ID 반환
			}
		}
	}

	return -1;  // 이 경우는 발생하지 않겠지만 안전을 위해 추가
}

void ObjectSkillSetting(OBJECT * pObj)
{
	int skillIdx;
	skillIdx = selectRandomSkill(GetObjFromPtr(pObj), pObj->getSkillList);
	switch (skillIdx) {
		//스킬이 없음
	case -1:
		break;
	default:
		SetHotKey(pObj, HOTKEY_SKILL, skillIdx, 0);
		//스킬이 하나면
		pObj->hotKey[0].randomCnt = GetSkillCnt(pObj->getSkillList);
		if (pObj->hotKey[0].randomCnt == 1) {
			pObj->hotKey[0].random = false;
		}
		//그렇지 않으면
		else {
			pObj->hotKey[0].random = true;
			pObj->hotKey[0].randomFrame = FPS;
		}
		break;
	}
}

void WaveControler()
{
	int i;
	OBJECT * pObj = nullptr;
	int obj = 0;
	int positionX, positionY;

	//인터랙티브 전투 튜토리얼: 스폰한 몬스터가 RegenMove() 점프 연출을 다 마치고 moveHandler가
	//ENEMYMOVETURN이 될 때까지 touchDisable을 true로 묶어둔다. 그 전에 공격하면 몬스터가 아직
	//active 상태가 아니라서 공격이 제대로 안 먹는다("생성될 때까지 타이밍을 기다리는" 부분).
	//반드시 tutorialWaitingEnemyLand 전용 플래그로만 판단해야 한다 - touchDisable==true를 직접 보면
	//공격 직후 쿨다운으로 touchDisable이 true가 될 때도 이 블록이 매 프레임 돌면서, 피격/사망으로
	//moveHandler가 ENEMYMOVETURN을 벗어난 적을 "아직 스폰 중"으로 오인해 touchDisable을 영원히
	//풀어주지 못하는 버그가 있었다(공격 버튼을 누르면 그대로 멈추는 현상의 원인).
	if (tutorialWaitingEnemyLand && robinmap == MAP_DIORAMA_TOLEM && (drawHandle == MD_PLAY || drawHandle == MD_DEMO)) {
		bool stillSpawning = false;

		for (i = ENEMY; i < NEUTRAL; i++) {
			if (ao[i].type != 0 && ao[i].moveHandler != ENEMYMOVETURN) {
				stillSpawning = true;
				break;
			}
		}

		if (!stillSpawning) {
			touchDisable = false;
			tutorialWaitingEnemyLand = false;
		}
	}

	//인터랙티브 전투 튜토리얼: 세바스찬의 "공격버튼을 눌러주세요" 대사에서 누른 입력은 컷씬을
	//닫는 데 소비됐으므로, 전투 준비가 끝나는 첫 프레임에 그 입력을 실제 공격으로 실행해준다.
	//AfterDemo() -> GotoPlay()가 SetHero()/SetBattleCrew()로 주인공과 크루를 다시 등장 연출
	//(REGENMOVE)에 태우기 때문에, 핸드오프 직후에 바로 부르면 RouletteAttackStart()가 turnList[]를
	//만들 때 아직 active가 아닌 캐릭터가 빠진다. 특히 크루가 빠지면 "세바스찬만 공격하지 않는"
	//증상이 되고, 디버거로 지연시키면 그 사이 등장 연출이 끝나 우연히 동작하는 타이밍 레이스가 된다.
	//그래서 주인공/크루/몬스터가 전부 제자리에 선 뒤에만 실행한다.
	if (tutorialAttackPending && drawHandle == MD_PLAY && arenaStatus == STATUS_PLAY
		&& attackSequence == ATTACKSEQUENCE_READY && !attackDelay
		&& ao[PLAYER].active == true && ao[PLAYER].dead == false && ao[PLAYER].moveHandler == PLAYERMOVE) {
		bool everyoneReady = true;

		//크루(세바스찬)가 등장 연출을 마치고 CREWMOVE로 바뀌어 있어야 turnList에 포함된다.
		for (i = CREW; i < CREW + crewCnt; i++) {
			if (ao[i].active == false || ao[i].moveHandler == REGENMOVE) {
				everyoneReady = false;
				break;
			}
		}

		//몬스터는 최소 한 마리가 착지(ENEMYMOVETURN)해 있어야 한다.
		if (everyoneReady) {
			bool enemyReady = false;

			for (i = ENEMY; i < NEUTRAL; i++) {
				if (ao[i].type == 0)
					continue;

				if (ao[i].active == true && ao[i].moveHandler == ENEMYMOVETURN)
					enemyReady = true;
				else {
					//아직 등장 연출 중인 몬스터가 하나라도 있으면 더 기다린다.
					enemyReady = false;
					break;
				}
			}

			everyoneReady = enemyReady;
		}

		if (everyoneReady) {
			tutorialWaitingEnemyLand = false;

			RouletteAttackStart();

			//RouletteAttackStart()는 attackDelay가 남아있으면 아무 것도 하지 않고 그냥 return한다.
			//그때 예약을 소진하고 touchDisable까지 걸어버리면 공격도 안 되고 다시 누를 수도 없는
			//교착이 된다. 실제로 시퀀스가 시작됐을 때만 예약을 소진한다.
			if (attackSequence != ATTACKSEQUENCE_READY) {
				tutorialAttackPending = false;

				bar[BAR_PLAY].aniFrame = 1;
				touchDisable = true;
			}
		}
	}

	for (i = ENEMY; i < NEUTRAL; i++) {
		if (!ao[i].type && ao[i].active == false) {
			obj = i;
			pObj = &ao[obj];
			break;
		}
	}

	//빈 슬롯이 하나도 없으면 아래에서 초기화되지 않은 pObj를 그대로 역참조하게 된다.
	if (pObj == nullptr)
		return;

	switch (drawHandle) {
	case MD_DEMO:
	case MD_PLAY:
		if (robin.curWaveIdx < GetMaxWaveCnt() && robin.waveActive[robin.curWaveIdx] == false && (MC_knlCurrentTimeStamp() - robin.waveTimeStamp >= wave[GetWaveRow(robin.waveIdx) * MAXWAVEENEMY * WAVEDATASIZE + robin.curWaveIdx * WAVEDATASIZE + 1] / FPS/* || AliveEnemyCnt() == 0*/)) {
			if (gDemoForceRoulette) {
				static const int demoEnemy[3] = {
					ENEMY_JELLYFISH, ENEMY_KNIGHT, ENEMY_SLIME
				};
				pObj->type = demoEnemy[Min(2, robin.curWaveIdx)];
			}
			else
				pObj->type = wave[GetWaveRow(robin.waveIdx) * MAXWAVEENEMY * WAVEDATASIZE + robin.curWaveIdx * WAVEDATASIZE + 0];
			//pObj->type = ENEMY_SLIME_GOLD;
			pObj->nx = pObj->x = positionX = setEnemyPos[robin.castle * 2 * MAXWAVEENEMY + 2 * robin.curWaveIdx + 0];
			pObj->ny = pObj->y = positionY = setEnemyPos[robin.castle * 2 * MAXWAVEENEMY + 2 * robin.curWaveIdx + 1];

			switch (pObj->type) {
			case ENEMY_FACE:
			case ENEMY_FACE_RED:
			case ENEMY_FACE_BLUE:
			case ENEMY_FACE_PURPLE:
			case ENEMY_FACE_GREEN:
			case ENEMY_FACE_GOLD:
			case ENEMY_FACE_BLACK:
			case ENEMY_ICESUN:
			case ENEMY_ICESUN_RED:
			case ENEMY_ICESUN_BLUE:
			case ENEMY_ICESUN_PURPLE:
			case ENEMY_ICESUN_GREEN:
			case ENEMY_ICESUN_GOLD:
			case ENEMY_ICESUN_BLACK:
			case ENEMY_LARVA:
			case ENEMY_LARVA_RED:
			case ENEMY_LARVA_BLUE:
			case ENEMY_LARVA_PURPLE:
			case ENEMY_LARVA_GREEN:
			case ENEMY_LARVA_GOLD:
			case ENEMY_LARVA_BLACK:
				positionX -= 2 * TSIZE;
				break;
			case ENEMY_ONEEYE:
			case ENEMY_ONEEYE_RED:
			case ENEMY_ONEEYE_BLUE:
			case ENEMY_ONEEYE_PURPLE:
			case ENEMY_ONEEYE_GREEN:
			case ENEMY_ONEEYE_GOLD:
			case ENEMY_ONEEYE_BLACK:
			case ENEMY_PHOENIX:
			case ENEMY_PHOENIX_RED:
			case ENEMY_PHOENIX_BLUE:
			case ENEMY_PHOENIX_PURPLE:
			case ENEMY_PHOENIX_GREEN:
			case ENEMY_PHOENIX_GOLD:
			case ENEMY_PHOENIX_BLACK:
			case ENEMY_THUNDER:
			case ENEMY_THUNDER_RED:
			case ENEMY_THUNDER_BLUE:
			case ENEMY_THUNDER_PURPLE:
			case ENEMY_THUNDER_GREEN:
			case ENEMY_THUNDER_GOLD:
			case ENEMY_THUNDER_BLACK:
			case ENEMY_FAIRY:
			case ENEMY_FAIRY_RED:
			case ENEMY_FAIRY_BLUE:
			case ENEMY_FAIRY_PURPLE:
			case ENEMY_FAIRY_GREEN:
			case ENEMY_FAIRY_GOLD:
			case ENEMY_FAIRY_BLACK:
			case ENEMY_CIRCLE:
			case ENEMY_CIRCLE_RED:
			case ENEMY_CIRCLE_BLUE:
			case ENEMY_CIRCLE_PURPLE:
			case ENEMY_CIRCLE_GREEN:
			case ENEMY_CIRCLE_GOLD:
			case ENEMY_CIRCLE_BLACK:
			case ENEMY_GHOST:
			case ENEMY_GHOST_RED:
			case ENEMY_GHOST_BLUE:
			case ENEMY_GHOST_PURPLE:
			case ENEMY_GHOST_GREEN:
			case ENEMY_GHOST_GOLD:
			case ENEMY_GHOST_BLACK:
				//case ENEMY_SPACE1:
				//case ENEMY_SPACE1_RED:
				//case ENEMY_SPACE1_BLUE:
				//case ENEMY_SPACE1_PURPLE:
				//case ENEMY_SPACE1_GREEN:
				//case ENEMY_SPACE1_GOLD:
				//case ENEMY_SPACE1_BLACK:
				pObj->ny = pObj->y -= 2 * TSIZE;
				break;
			case ENEMY_SHIP:
			case ENEMY_SHIP_RED:
			case ENEMY_SHIP_BLUE:
			case ENEMY_SHIP_PURPLE:
			case ENEMY_SHIP_GREEN:
			case ENEMY_SHIP_GOLD:
			case ENEMY_SHIP_BLACK:
				positionX -= 2 * TSIZE;
				pObj->ny = pObj->y -= 2 * TSIZE;
				break;
			case ENEMY_FOGRA:
			case ENEMY_FOGRA_RED:
			case ENEMY_FOGRA_BLUE:
			case ENEMY_FOGRA_PURPLE:
			case ENEMY_FOGRA_GREEN:
			case ENEMY_FOGRA_GOLD:
			case ENEMY_FOGRA_BLACK:
				positionX -= 2 * TSIZE;
				pObj->ny = pObj->y -= 2 * TSIZE;
				break;
			case ENEMY_DEATH:
			case ENEMY_DEATH_RED:
			case ENEMY_DEATH_BLUE:
			case ENEMY_DEATH_PURPLE:
			case ENEMY_DEATH_GREEN:
			case ENEMY_DEATH_GOLD:
			case ENEMY_DEATH_BLACK:
				//position -= 2 * TSIZE;
				//pObj->ny = pObj->y -= 1 * TSIZE;
				break;
			case ENEMY_CASTLE_BOSS1:
			case ENEMY_CASTLE_BOSS1_RED:
			case ENEMY_CASTLE_BOSS1_BLUE:
			case ENEMY_CASTLE_BOSS1_PURPLE:
			case ENEMY_CASTLE_BOSS1_GREEN:
			case ENEMY_CASTLE_BOSS1_GOLD:
			case ENEMY_CASTLE_BOSS1_BLACK:
				positionX -= 0 * TSIZE;
				pObj->ny = pObj->y -= 3 * TSIZE;
				break;
			case ENEMY_DARKDRAGON:
			case ENEMY_DARKDRAGON_RED:
			case ENEMY_DARKDRAGON_BLUE:
			case ENEMY_DARKDRAGON_PURPLE:
			case ENEMY_DARKDRAGON_GREEN:
			case ENEMY_DARKDRAGON_GOLD:
			case ENEMY_DARKDRAGON_BLACK:
				positionX -= 2 * TSIZE;
				pObj->ny = pObj->y -= 1 * TSIZE;
				break;
			case ENEMY_ANGEL:
			case ENEMY_ANGEL_RED:
			case ENEMY_ANGEL_BLUE:
			case ENEMY_ANGEL_PURPLE:
			case ENEMY_ANGEL_GREEN:
			case ENEMY_ANGEL_GOLD:
			case ENEMY_ANGEL_BLACK:
				positionX -= 4 * TSIZE + TSIZE / 2;
				pObj->ny = pObj->y -= 2 * TSIZE;
				break;
				//case ENEMY_CASTLE_BOSS3:
				//case ENEMY_CASTLE_BOSS3_RED:
				//case ENEMY_CASTLE_BOSS3_BLUE:
				//case ENEMY_CASTLE_BOSS3_PURPLE:
				//case ENEMY_CASTLE_BOSS3_GREEN:
				//case ENEMY_CASTLE_BOSS3_GOLD:
				//case ENEMY_CASTLE_BOSS3_BLACK:
					//positionX -= -1 * TSIZE;
					//pObj->ny = pObj->y += 1 * TSIZE;
					//break;
			}

			pObj->dirX = pObj->dirF = LEFT;
			pObj->defaultZoom = pObj->zoom = MONSTERZOOM;

			//튜토리얼 마무리 보스는 같은 달팽이라도 두 배로 커야 "보스"로 보인다.
			//wave[] 한 줄에는 타입/등장타이밍/몬스터종류 세 값뿐이라 크기를 적어둘 자리가 없다.
			//스폰은 다른 몬스터와 똑같이 정식 경로를 타고, 크기만 여기서 키운다.
			if (IsTutorialPlaying() && robin.waveIdx == TUTORIAL_WAVEIDX_BOSS)
				pObj->defaultZoom = pObj->zoom = MONSTERZOOM * TUTORIAL_BOSS_ZOOM;

			pObj->mom = obj;

			SetEnemy(pObj);
			InitMotion(pObj);


			switch (pObj->type) {
			case ENEMY_SHIP:
			case ENEMY_SHIP_RED:
			case ENEMY_SHIP_BLUE:
			case ENEMY_SHIP_PURPLE:
			case ENEMY_SHIP_GREEN:
			case ENEMY_SHIP_GOLD:
			case ENEMY_SHIP_BLACK:
				break;
			default:
				InitBar(BAR_ENEMYHP + GetEnemyBarIdx(obj));
				break;
			}

			InitMotion(pObj);

			robin.waveActive[robin.curWaveIdx] = true;

			robin.curWaveIdx++;

			SaveGame();

			switch (pObj->type) {
			case ENEMY_CASTLE_BOSS1:
			case ENEMY_CASTLE_BOSS1_RED:
			case ENEMY_CASTLE_BOSS1_BLUE:
			case ENEMY_CASTLE_BOSS1_PURPLE:
			case ENEMY_CASTLE_BOSS1_GREEN:
			case ENEMY_CASTLE_BOSS1_GOLD:
			case ENEMY_CASTLE_BOSS1_BLACK:
				pObj->moveHandler = REGENMOVE;
				pObj->drawHandler = REGENDRAW;
				break;
			default:
				pObj->moveHandler = REGENMOVE;
				pObj->drawHandler = REGENDRAW;
				break;
			}
			pObj->dead = true;
			pObj->active = false;

			//웨이브 총합은 놔두고, 현재값만 올려준다.
			BackUpEnemyObj();
			SaveGame();
		}
		break;
	case MD_BATTLE:
		//현재 적이 없으면 보스를 만들어라.
		if (robin.bossRoom == false) {
			pObj->type = boss[robin.stage];
			//pObj->type = ENEMY_SLIME_GOLD;
			pObj->nx = pObj->x = positionX = BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4;
			pObj->ny = pObj->y = positionY = TSIZE * 17;

			switch (pObj->type) {
			case ENEMY_FACE:
			case ENEMY_FACE_RED:
			case ENEMY_FACE_BLUE:
			case ENEMY_FACE_PURPLE:
			case ENEMY_FACE_GREEN:
			case ENEMY_FACE_GOLD:
			case ENEMY_FACE_BLACK:
			case ENEMY_ICESUN:
			case ENEMY_ICESUN_RED:
			case ENEMY_ICESUN_BLUE:
			case ENEMY_ICESUN_PURPLE:
			case ENEMY_ICESUN_GREEN:
			case ENEMY_ICESUN_GOLD:
			case ENEMY_ICESUN_BLACK:
			case ENEMY_LARVA:
			case ENEMY_LARVA_RED:
			case ENEMY_LARVA_BLUE:
			case ENEMY_LARVA_PURPLE:
			case ENEMY_LARVA_GREEN:
			case ENEMY_LARVA_GOLD:
			case ENEMY_LARVA_BLACK:
				positionX -= 2 * TSIZE;
				break;
			case ENEMY_ONEEYE:
			case ENEMY_ONEEYE_RED:
			case ENEMY_ONEEYE_BLUE:
			case ENEMY_ONEEYE_PURPLE:
			case ENEMY_ONEEYE_GREEN:
			case ENEMY_ONEEYE_GOLD:
			case ENEMY_ONEEYE_BLACK:
			case ENEMY_PHOENIX:
			case ENEMY_PHOENIX_RED:
			case ENEMY_PHOENIX_BLUE:
			case ENEMY_PHOENIX_PURPLE:
			case ENEMY_PHOENIX_GREEN:
			case ENEMY_PHOENIX_GOLD:
			case ENEMY_PHOENIX_BLACK:
			case ENEMY_THUNDER:
			case ENEMY_THUNDER_RED:
			case ENEMY_THUNDER_BLUE:
			case ENEMY_THUNDER_PURPLE:
			case ENEMY_THUNDER_GREEN:
			case ENEMY_THUNDER_GOLD:
			case ENEMY_THUNDER_BLACK:
			case ENEMY_FAIRY:
			case ENEMY_FAIRY_RED:
			case ENEMY_FAIRY_BLUE:
			case ENEMY_FAIRY_PURPLE:
			case ENEMY_FAIRY_GREEN:
			case ENEMY_FAIRY_GOLD:
			case ENEMY_FAIRY_BLACK:
			case ENEMY_CIRCLE:
			case ENEMY_CIRCLE_RED:
			case ENEMY_CIRCLE_BLUE:
			case ENEMY_CIRCLE_PURPLE:
			case ENEMY_CIRCLE_GREEN:
			case ENEMY_CIRCLE_GOLD:
			case ENEMY_CIRCLE_BLACK:
			case ENEMY_GHOST:
			case ENEMY_GHOST_RED:
			case ENEMY_GHOST_BLUE:
			case ENEMY_GHOST_PURPLE:
			case ENEMY_GHOST_GREEN:
			case ENEMY_GHOST_GOLD:
			case ENEMY_GHOST_BLACK:
				//case ENEMY_SPACE1:
				//case ENEMY_SPACE1_RED:
				//case ENEMY_SPACE1_BLUE:
				//case ENEMY_SPACE1_PURPLE:
				//case ENEMY_SPACE1_GREEN:
				//case ENEMY_SPACE1_GOLD:
				//case ENEMY_SPACE1_BLACK:
				pObj->ny = pObj->y -= 2 * TSIZE;
				break;
			case ENEMY_SHIP:
			case ENEMY_SHIP_RED:
			case ENEMY_SHIP_BLUE:
			case ENEMY_SHIP_PURPLE:
			case ENEMY_SHIP_GREEN:
			case ENEMY_SHIP_GOLD:
			case ENEMY_SHIP_BLACK:
				positionX -= 2 * TSIZE;
				pObj->ny = pObj->y -= 2 * TSIZE;
				break;
			case ENEMY_FOGRA:
			case ENEMY_FOGRA_RED:
			case ENEMY_FOGRA_BLUE:
			case ENEMY_FOGRA_PURPLE:
			case ENEMY_FOGRA_GREEN:
			case ENEMY_FOGRA_GOLD:
			case ENEMY_FOGRA_BLACK:
				positionX -= 2 * TSIZE;
				pObj->ny = pObj->y -= 2 * TSIZE;
				break;
			case ENEMY_DEATH:
			case ENEMY_DEATH_RED:
			case ENEMY_DEATH_BLUE:
			case ENEMY_DEATH_PURPLE:
			case ENEMY_DEATH_GREEN:
			case ENEMY_DEATH_GOLD:
			case ENEMY_DEATH_BLACK:
				//position -= 2 * TSIZE;
				//pObj->ny = pObj->y -= 1 * TSIZE;
				break;
			case ENEMY_CASTLE_BOSS1:
			case ENEMY_CASTLE_BOSS1_RED:
			case ENEMY_CASTLE_BOSS1_BLUE:
			case ENEMY_CASTLE_BOSS1_PURPLE:
			case ENEMY_CASTLE_BOSS1_GREEN:
			case ENEMY_CASTLE_BOSS1_GOLD:
			case ENEMY_CASTLE_BOSS1_BLACK:
				positionX -= 0 * TSIZE;
				pObj->ny = pObj->y -= 3 * TSIZE;
				break;
			case ENEMY_DARKDRAGON:
			case ENEMY_DARKDRAGON_RED:
			case ENEMY_DARKDRAGON_BLUE:
			case ENEMY_DARKDRAGON_PURPLE:
			case ENEMY_DARKDRAGON_GREEN:
			case ENEMY_DARKDRAGON_GOLD:
			case ENEMY_DARKDRAGON_BLACK:
				positionX -= 2 * TSIZE;
				pObj->ny = pObj->y -= 1 * TSIZE;
				break;
			case ENEMY_ANGEL:
			case ENEMY_ANGEL_RED:
			case ENEMY_ANGEL_BLUE:
			case ENEMY_ANGEL_PURPLE:
			case ENEMY_ANGEL_GREEN:
			case ENEMY_ANGEL_GOLD:
			case ENEMY_ANGEL_BLACK:
				positionX -= 4 * TSIZE + TSIZE / 2;
				pObj->ny = pObj->y -= 2 * TSIZE;
				break;
				//case ENEMY_CASTLE_BOSS3:
				//case ENEMY_CASTLE_BOSS3_RED:
				//case ENEMY_CASTLE_BOSS3_BLUE:
				//case ENEMY_CASTLE_BOSS3_PURPLE:
				//case ENEMY_CASTLE_BOSS3_GREEN:
				//case ENEMY_CASTLE_BOSS3_GOLD:
				//case ENEMY_CASTLE_BOSS3_BLACK:
					//positionX -= -1 * TSIZE;
					//pObj->ny = pObj->y += 1 * TSIZE;
					//break;
			}

			pObj->dirX = pObj->dirF = LEFT;
			pObj->defaultZoom = pObj->zoom = BOSSZOOM;
			pObj->mom = obj;

			SetEnemy(pObj);
			InitMotion(pObj);


			switch (pObj->type) {
			case ENEMY_SHIP:
			case ENEMY_SHIP_RED:
			case ENEMY_SHIP_BLUE:
			case ENEMY_SHIP_PURPLE:
			case ENEMY_SHIP_GREEN:
			case ENEMY_SHIP_GOLD:
			case ENEMY_SHIP_BLACK:
				break;
			default:
				InitBar(BAR_ENEMYHP + GetEnemyBarIdx(obj));
				break;
			}

			InitMotion(pObj);

			//현재 보스면
			arenaFrame = INFOFRAME * 2;
			bossOn = true;

			SaveGame();

			switch (pObj->type) {
			case ENEMY_CASTLE_BOSS1:
			case ENEMY_CASTLE_BOSS1_RED:
			case ENEMY_CASTLE_BOSS1_BLUE:
			case ENEMY_CASTLE_BOSS1_PURPLE:
			case ENEMY_CASTLE_BOSS1_GREEN:
			case ENEMY_CASTLE_BOSS1_GOLD:
			case ENEMY_CASTLE_BOSS1_BLACK:
				pObj->moveHandler = REGENMOVE;
				pObj->drawHandler = REGENDRAW;
				break;
			default:
				pObj->moveHandler = REGENMOVE;
				pObj->drawHandler = REGENDRAW;
				break;
			}
			pObj->dead = true;
			pObj->active = false;

			//웨이브 총합은 놔두고, 현재값만 올려준다.
			//BackUpEnemyObj();
			//SaveGame();

			robin.bossRoom = true;
			bar[BAR_DAY].active = false;
		}
		break;
	}
}

long long GetTotalWaveHp(int waveIdx)
{
	int i;
	long long curHp;
	long long totalHp = 0;
	int monType;
	int waveCount = MAXWAVEENEMY;

	// AVK_MAXGAME에서는 원래 wave[]의 몬스터 수와 관계없이 세 마리를
	// 강제로 소환한다. 현재 HP는 세 마리 모두 BAR_BOSSHP에 더해지므로
	// 최대 HP도 같은 세 슬롯을 합산해야 바의 비율이 1을 넘지 않는다.
	if (gDemoForceRoulette)
		waveCount = GetMaxWaveCnt();

	for (i = 0; i < waveCount; i++) {
		monType = wave[GetWaveRow(waveIdx) * MAXWAVEENEMY * WAVEDATASIZE + i * WAVEDATASIZE + 0];
		if (monType != false || gDemoForceRoulette) {
			curHp = GetWaveHp(waveIdx, i); 
			
			totalHp += curHp;
		}
	}

	return totalHp;
}


long long GetTotalEnemyHp(int stage)
{
	int i;
	long long totalHp = 0;

	for (i = ENEMY; i < NEUTRAL; i++) {
		if ((ao[i].active == true || ao[i].moveHandler == REGENMOVE) && ao[i].mom == i) {
			totalHp += ao[i].maxhp;
		}
	}

	return totalHp;
}

//몇 번째 계단의 기본 체력인가. WAVE_HP_BASE 에서 시작해 계단마다 x1.17 이다.
//
//곱셈을 반복해서 구한다. 100 으로 나누는 자리가 계단마다 잘리지만 그게
//오히려 낫다 - 어느 기기에서 돌려도 똑같은 값이 나온다.
long long GetWaveHpTier(int tier)
{
	long long v = WAVE_HP_BASE;
	int i;

	if (tier < 0)
		tier = 0;
	if (tier > WAVE_HP_MAX_TIER)
		tier = WAVE_HP_MAX_TIER;

	for (i = 0; i < tier; i++)
		v = v * WAVE_HP_TIER_MUL / 100;

	return v;
}

long long GetWaveHp(int waveIdx, int curWave)
{
	//한 웨이브가 차지하는 칸은 MAXWAVEENEMY * WAVEDATASIZE 다. 여기만 MAXENEMY(50)
	//로 잡혀 있어서 waveIdx 가 조금만 올라가도 배열 밖을 읽었고, 그 쓰레기 값을
	//monType 으로 써서 ADDHP 를 가져왔다. 체력이 웨이브마다 널뛰던 원인이다.
	int monType = wave[GetWaveRow(waveIdx) * MAXWAVEENEMY * WAVEDATASIZE + curWave * WAVEDATASIZE + 0];

	//인터랙티브 전투 튜토리얼은 몬스터 타입/스폰 타이밍만 wave[]를 그대로 쓰고 체력은 여기서
	//웨이브 순번에 맞춰 한 대씩 늘려간다(0:2, 1:3, 2:4 ...). 정규 공식을 그대로 쓰면 수천 단위라
	//튜토리얼에서 몇 대를 때려도 안 죽는다.
	//튜토리얼 4연전은 정규 공식(수천 단위)을 쓰면 몇 대를 때려도 안 죽는다.
	//단계마다 "무엇을 배웠는지"가 드러나도록 체력을 직접 잡는다.
	if (IsTutorialPlaying()) {
		switch (waveIdx) {
		case TUTORIAL_WAVEIDX_1ST:
			//"세바스찬이 때린다 -> HP가 남는다 -> 주인공이 마무리한다"를 보여줘야 해서 최소 2가 필요하다.
			//크루의 공격이 마지막 1을 못 깎게 막는 처리는 AttackObj()에 있다.
			return 2;
		case TUTORIAL_WAVEIDX_2ND:
			//동료가 한 명 늘었으니 그만큼만 더 준다.
			return 3;
		case TUTORIAL_WAVEIDX_3RD:
			//하트 3배 베팅 공격에만 죽도록.
			return 100;
		case TUTORIAL_WAVEIDX_BOSS:
			//동료 3중첩 강공격 한 방에 죽도록.
			return TUTORIAL_BOSS_HP;
		}

		return 2 + waveIdx;
	}

	//----------------------------------------------------------------------
	// 등비로 오른다
	//
	// 무기 한 자루(WAVE_STAGE_PER_TIER 스테이지)마다 한 계단씩 x1.17 이다.
	// 계단 안에서는 등차로 이어 붙여 다음 계단까지 매끄럽게 오른다.
	//
	// 왜 이 모양이어야 하는지는 Config/BalanceConfig.h 에 적어 뒀다.
	//
	// 전부 정수다. pow() 를 쓰면 기기마다 마지막 자리가 달라져 같은
	// 스테이지의 몬스터 체력이 서로 다르게 나온다.
	//----------------------------------------------------------------------
	{
		int tier = waveIdx / WAVE_STAGE_PER_TIER;
		int within = waveIdx % WAVE_STAGE_PER_TIER;
		long long lo = GetWaveHpTier(tier);
		long long hi = GetWaveHpTier(tier + 1);
		long long base = lo + (hi - lo) * within / WAVE_STAGE_PER_TIER;

		//ADDHP 는 몬스터마다 붙는 덧살이다. 0 이면 그 계단의 기본 체력이고
		//1900 이면 스무 배다. 보스가 이 칸으로 튄다.
		//
		//WAVE_HP_TEST_MUL 은 시연용 배수다(평소 1). 곡선은 그대로 두고
		//전체를 같이 올려서 연출을 끝까지 볼 수 있게 한다.
		//보스 자리는 그 자리 잡몹 체력에 배수를 곱한다(BalanceConfig.h).
		//ADDHP 와 곱해지므로 덩치가 큰 놈이 보스로 서면 그만큼 더 두꺼워진다.
		return base * (100 + enemyData[monType * ENEMYDATASIZE + ENEMYDATA_ADDHP]) / 100
			* GetWaveHpMul(waveIdx)
			* WAVE_HP_TEST_MUL;
	}
}

//아레나가 밑에서 계속 돌고 있는 모드인지.
//보상 상자(MD_GACHA)나 스테이지클리어는 화면만 덮을 뿐 Core::Run()에서 Play()를 그대로 돌린다.
//그래서 그 연출이 떠 있는 동안에도 WaveControler()가 다음 웨이브를 스폰하고 몬스터가 착지한다.
//이때 drawHandle만 보고 enemyData의 기본 무브핸들러(ENEMYMOVE)로 떨어뜨리면, 그 몬스터는
//다가오지도 돌지도 않고 제자리에서 공격만 하는 상태로 굳어버린다.
//튜토리얼 2번째 웨이브(ENEMY_TREE)가 첫 몬스터 보상 상자가 열려 있는 사이에 스폰되면서
//1번째(ENEMY_SNAIL)와 달리 ENEMYMOVE를 받던 것이 이 경우였다.
bool IsArenaRunning(void)
{
	switch (drawHandle) {
	case MD_PLAY:
	case MD_DEMO:
	case MD_GACHA:
	case MD_STAGECLEAR:
		return true;
	}

	return false;
}

int SetEnemy(OBJECT *pObj)
{
	const signed short *uPtr = &enemyData[pObj->type * ENEMYDATASIZE];
	int idx = 0;
	long long int lv;
	int i, cnt = 0;
	int obj = GetObjFromPtr(pObj);

	pObj->active = true;
	pObj->dead = false;

	pObj->dirY = DOWN;

	//투기장이면
	pObj->lv = robin.stage * TOTALROOM + robin.room;
	lv = pObj->lv;

	//CMF
	pObj->cmf = *uPtr;

	//MoveHandler
	if (IsArenaRunning())
		pObj->moveHandler = ENEMYMOVETURN;
	else
		pObj->moveHandler = *(uPtr + 1);
	//DrawHandler
	if (pObj->type < NPC_CAPTAIN)
		pObj->drawHandler = *(uPtr + 2);
	else
		pObj->drawHandler = ENEMYDRAW;
	//Name
	pObj->name = TEXT_MONSTERNAME_START + (pObj->type == 0 ? idx : pObj->type);
	//Hp
	switch (drawHandle) {
	case MD_PLAY:
	case MD_BATTLE:
	case MD_RAID:
		//pObj->maxhp = pObj->hp = (50 + pObj->lv * 23 + pObj->lv * pObj->lv * 12 / 10) * 10;
		//TEST
		pObj->maxhp = pObj->hp = GetWaveHp(robin.waveIdx, robin.curWaveIdx);
		//pObj->maxhp = pObj->hp = (robin.stage + 10) * (100 + enemyData[pObj->type * ENEMYDATASIZE + ENEMYDATA_ADDHP]);
		//if (wave[robin.waveIdx * MAXWAVEENEMY * WAVEDATASIZE + robin.curWaveIdx * WAVEDATASIZE + 2] == MONSTERTYPE_BOSS) {
		//	pObj->maxhp *= 5;
		//	pObj->hp = pObj->maxhp;
		//}
#ifdef ENEMYHPDISCOUNT
		pObj->maxhp = pObj->hp = ENEMYHPDISCOUNT;
#endif
		//pObj->str = (pObj->lv * pObj->lv / 25 + pObj->lv * 11 / 3) + 15;
		//pObj->str = (robin.stage + 1) * 10;
		pObj->str = (robin.stage + 10) * 10;
		break;
	case MD_BOSSRAID:
		pObj->maxhp = pObj->hp = goldQuestNpc[robin.gameEvent[GetEventMenuIdx(EVENTTYPE_BOSSRAID)].barStatus * BOSSRAIDSIZE + 3 + robin.gameEvent[GetEventMenuIdx(EVENTTYPE_BOSSRAID)].barFrame * 15];
		break;
	}

	//인터랙티브 전투 튜토리얼: 체력은 GetWaveHp()가 튜토리얼 값으로 돌려준다.
	//다만 위 switch(drawHandle)는 MD_PLAY/MD_BATTLE/MD_RAID에서만 GetWaveHp()를 부르는데,
	//컷씬 중(MD_DEMO의 EFFECT_WAVE)에 스폰되는 경우도 있으므로 여기서 한 번 더 확정한다.
	if (IsTutorialPlaying()) {
		pObj->maxhp = pObj->hp = GetWaveHp(robin.waveIdx, robin.curWaveIdx);

		//빨간 HP바(BAR_BOSSHP)의 분모는 이번 웨이브 전체 합으로 확정한다.
		//누적(+=)하면 안 된다. 상자 연출이 끝날 때 Func_Gacha.cpp가 이미
		//bar[BAR_BOSSHP].max = GetTotalWaveHp(robin.waveIdx)로 채워두기 때문에, 여기서 한 번 더
		//더하면 분모가 두 배가 되어 갓 소환한 몬스터의 바가 절반만 차 있는 것처럼 보인다.
		//대입으로 두면 SetEnemy()가 몇 번 불리든 값이 흔들리지 않는다.
		bar[BAR_BOSSHP].max = GetTotalWaveHp(robin.waveIdx);
	}

	//Str
	//Armor
	pObj->ps[PS_ARMOR] = enemyStatInfo[pObj->type * 3 + 2];

	pObj->mom = GetObjFromPtr(pObj);
	//각방의 대장은 체력 5배, 공격력 1배를 해준다.	

	//타겟을 세팅해준다.

	pObj->target = NearPlayer(pObj);

	switch (drawHandle) {
	default:

		break;
	case MD_BOSSRAID:
		bar[BAR_ENEMYUSER].count = ao[GetEnemyBarIdx(ENEMY)].hp;
		break;
	}

	switch (pObj->type) {
	case ENEMY_CASTLE_BOSS4:
	case ENEMY_CASTLE_BOSS4_RED:
	case ENEMY_CASTLE_BOSS4_BLUE:
	case ENEMY_CASTLE_BOSS4_PURPLE:
	case ENEMY_CASTLE_BOSS4_GREEN:
	case ENEMY_CASTLE_BOSS4_GOLD:
	case ENEMY_CASTLE_BOSS4_BLACK:
		//tileX1 : 서로 손의 obj번호를 알고있음.
		for (i = GetObjFromPtr(pObj) + 1, cnt = 0; cnt < 2; i++) {
			if (ao[i].active == false && ao[i].type == 0) {
				pObj->drawHandler = ENEMYDRAW;
				memcpy(&ao[i], pObj, sizeof(OBJECT));
				ao[i].etc = CASTLEBOSS4_HAND_NEUTRAL;
				ao[i].moveHandler = HANDMOVE;
				ao[i].x = (float)(cnt == 0 ? 72 * _2X : 250 * _2X) * ao[i].zoom;
				ao[i].y = (float)(cnt == 0 ? 156 * _2X + 32 * _2X : 100 * _2X + 32 * _2X) * ao[i].zoom;
				ao[i].dirF = ao[i].dirX = cnt == 0 ? LEFT : RIGHT;
				ao[i].dx = (float)(4 * _2X) * DIR(ao[i].dirX) * ao[i].zoom;
				ao[i].tileX1 = GetObjFromPtr(&ao[i]) + (cnt == 0 ? 1 : -1);
				ao[i].mom = GetObjFromPtr(pObj);
				MoveObj(&ao[i]);
				InitMotion(&ao[i]);
				cnt++;
			}
		}
		break;
	case ENEMY_CASTLE_BOSS3:
	case ENEMY_CASTLE_BOSS3_RED:
	case ENEMY_CASTLE_BOSS3_BLUE:
	case ENEMY_CASTLE_BOSS3_PURPLE:
	case ENEMY_CASTLE_BOSS3_GREEN:
	case ENEMY_CASTLE_BOSS3_GOLD:
	case ENEMY_CASTLE_BOSS3_BLACK:
		//attack 변수 : 윗껍질 벗겨진상태, 아랫껍질 벗겨진 상태 등 저장
		for (i = GetObjFromPtr(pObj) + 2, cnt = 0; cnt < 2; i++) {
			if (ao[i].active == false && ao[i].type == 0) {
				memcpy(&ao[i], pObj, sizeof(OBJECT));
				ao[i].motion = PO_C50_UPSKIN + cnt;
				ao[i].moveHandler = FOLLOWMOMMOVE;
				ao[i].mom = GetObjFromPtr(pObj);
				InitMotion(&ao[i]);
				InitBar(BAR_ENEMYHP + GetEnemyBarIdx(i));
				cnt++;
			}
		}
		break;
	case ENEMY_CASTLE_BOSS1:
	case ENEMY_CASTLE_BOSS1_RED:
	case ENEMY_CASTLE_BOSS1_BLUE:
	case ENEMY_CASTLE_BOSS1_PURPLE:
	case ENEMY_CASTLE_BOSS1_GREEN:
	case ENEMY_CASTLE_BOSS1_GOLD:
	case ENEMY_CASTLE_BOSS1_BLACK:
		pObj->moveHandler = DEBRIONBODYMOVE;
		InitMotion(pObj);

		for (i = ENEMY; i < NEUTRAL; i++) {
			if (ao[i].active == false) {
				memcpy(&ao[i], pObj, sizeof(OBJECT));
				ao[i].etc = pObj->tileX2 < 2 ? CASTLEBOSS1_UARM_NEUTRAL : CASTLEBOSS1_DARM_NEUTRAL;
				ao[i].dirF = ao[i].dirX = pObj->tileX2 % 2 == 0 ? LEFT : RIGHT;
				ao[i].moveHandler = DEBRIONARMMOVE;
				//ao[i].moveHandler = null;
				ao[i].mom = GetObjFromPtr(pObj);
				MoveObj(&ao[i]);
				InitMotion(&ao[i]);
				pObj->tileX2++;

				if (pObj->tileX2 == 4)
					break;
			}
		}
		break;
	case ENEMY_CASTLE_BOSS2:
	case ENEMY_CASTLE_BOSS2_RED:
	case ENEMY_CASTLE_BOSS2_BLUE:
	case ENEMY_CASTLE_BOSS2_PURPLE:
	case ENEMY_CASTLE_BOSS2_GREEN:
	case ENEMY_CASTLE_BOSS2_GOLD:
	case ENEMY_CASTLE_BOSS2_BLACK:
	case ENEMY_MAMMOTH:
	case ENEMY_MAMMOTH_RED:
	case ENEMY_MAMMOTH_BLUE:
	case ENEMY_MAMMOTH_PURPLE:
	case ENEMY_MAMMOTH_GREEN:
	case ENEMY_MAMMOTH_GOLD:
	case ENEMY_MAMMOTH_BLACK:
		pObj->shield = pObj->shieldMax = pObj->maxhp / SHIELDPERHP;
		break;
	case ENEMY_MACHINE:
	case ENEMY_MACHINE_RED:
	case ENEMY_MACHINE_BLUE:
	case ENEMY_MACHINE_PURPLE:
	case ENEMY_MACHINE_GREEN:
	case ENEMY_MACHINE_GOLD:
	case ENEMY_MACHINE_BLACK:
		//MoveObj(pObj);
		//InitMotion(pObj);

		pObj->moveHandler = MACHINEMOVE;
		pObj->mainFrame = 4;

		if (GetObjFromPtr(pObj) == ENEMY + 4) {
			pObj->mainFrame = 0;
			pObj->drawHandler = NULL;
			pObj->moveHandler = MACHINEMANAGERMOVE;
			pObj->hp = pObj->maxhp;
		}
		else if (GetObjFromPtr(pObj) >= ENEMY + 2)
			pObj->attack = PO_C25_LD_N0;
		break;
	case ENEMY_DARKDRAGON:
	case ENEMY_DARKDRAGON_RED:
	case ENEMY_DARKDRAGON_BLUE:
	case ENEMY_DARKDRAGON_PURPLE:
	case ENEMY_DARKDRAGON_GREEN:
	case ENEMY_DARKDRAGON_GOLD:
	case ENEMY_DARKDRAGON_BLACK:
		pObj->dirF = 1 - pObj->dirX;
		InitMotion(pObj);
		break;
	case ENEMY_SLIME:
	case ENEMY_SLIME_RED:
	case ENEMY_SLIME_BLUE:
	case ENEMY_SLIME_PURPLE:
	case ENEMY_SLIME_GREEN:
	case ENEMY_SLIME_GOLD:
	case ENEMY_SLIME_BLACK:
		//status에따른 모션잡아주기
		if (pObj->status <= RIGHT_WALK) {
			pObj->dirY = DOWN;
			pObj->motion = PO_C33_N_D_0;
		}
		else {
			pObj->dirY = UP;
			pObj->motion = PO_C33_N_U_0;
		}

		InitMotion(pObj);
		break;
	case ENEMY_FOGRA:
	case ENEMY_FOGRA_RED:
	case ENEMY_FOGRA_BLUE:
	case ENEMY_FOGRA_PURPLE:
	case ENEMY_FOGRA_GREEN:
	case ENEMY_FOGRA_GOLD:
	case ENEMY_FOGRA_BLACK:
		pObj->jumpFrame = 206;

		for (i = GetObjFromPtr(pObj) + 1, cnt = 0; i < NEUTRAL; i++) {
			if (ao[i].active == false) {
				memcpy(&ao[i], pObj, sizeof(OBJECT));
				ao[i].moveHandler = FOGRASUBMOVE;
				ao[i].x -= (float)(95 * _2X + cnt * 190 * _2X) * pObj->zoom;
				ao[i].etc = FOGRA_SUBFOGRA;
				ao[i].tileY1 = cnt;
				ao[i].motion = PO_C40_CIRCLE0;
				InitMotion(&ao[i]);
				cnt++;
				if (cnt == 2)
					break;
			}
		}
		break;
	case ENEMY_BAHAMUT:
	case ENEMY_BAHAMUT_RED:
	case ENEMY_BAHAMUT_BLUE:
	case ENEMY_BAHAMUT_PURPLE:
	case ENEMY_BAHAMUT_GREEN:
	case ENEMY_BAHAMUT_GOLD:
	case ENEMY_BAHAMUT_BLACK:
		// mainFrame용도 : 검은색으로 칠하기.
		//pObj->mainFrame = 28;

		//pObj->etc = BAHAMUT_EVENT;
		pObj->etc = BAHAMUT_NEUTRAL;
		cnt = BahamutReady(pObj);
		break;
	case ENEMY_SHIP:
	case ENEMY_SHIP_RED:
	case ENEMY_SHIP_BLUE:
	case ENEMY_SHIP_PURPLE:
	case ENEMY_SHIP_GREEN:
	case ENEMY_SHIP_GOLD:
	case ENEMY_SHIP_BLACK:
		/*
		//배 몸이 알아서 포를 생성
		for (i = obj + 4; i >= obj; i--) {
			//ao[i] = ao[ENEMY];
			memcpy(&ao[i], pObj, sizeof(OBJECT));

			if (i == obj + 4) {
				ao[i].moveHandler = SHIPMAINMOVE;
				ao[i].status = 4;
			}
			else {
				ao[i].motion = ao[i].attack = PO_C28_CA1_0 + 4 * (i - ENEMY);
				ao[i].drawHandler = ENEMYDRAW;
				ao[i].hp = ao[i].maxhp = pObj->maxhp / 2;
				ao[i].dead = false;
				ao[i].moveHandler = SHIPSUBMOVE;
			}

			InitBar(BAR_ENEMYHP + GetEnemyBarIdx(i));
			//ao[i].moveHandler = REGENMOVE;
			//ao[i].drawHandler = REGENDRAW;

			//ao[i].nx = ao[i].x = BATTLEPOSITION_ENEMY_X - 2 * TSIZE;// -(float)GetEnemyBarIdx(obj) * 2 * _2X;
			//ao[i].y = ENEMYPOSITION_Y - 3 * TSIZE;

			MoveObj(&ao[i]);
		}
		*/
		break;
	case ENEMY_LIGHTNING:
	case ENEMY_LIGHTNING_RED:
	case ENEMY_LIGHTNING_BLUE:
	case ENEMY_LIGHTNING_PURPLE:
	case ENEMY_LIGHTNING_GREEN:
	case ENEMY_LIGHTNING_GOLD:
	case ENEMY_LIGHTNING_BLACK:
		pObj->type = ENEMY_LIGHTNING;
		// PO_C22_LIGHTNING0 부분 아마 div파일 수©정 전에는 에러날듯 합니다.
		// 에러나면 일단 (PO_C22_LIGHTNING0) 이거 나오는 부분 모두주석처리 해주세요
		if (pObj->cmf == CMF_SPARK)
			pObj->motion = PO_C22_N0;
		else
			pObj->motion = PO_C22_LIGHTNING0;
		InitMotion(pObj);
		break;
	case ENEMY_LABETH:
	case ENEMY_LABETH_RED:
	case ENEMY_LABETH_BLUE:
	case ENEMY_LABETH_PURPLE:
	case ENEMY_LABETH_GREEN:
	case ENEMY_LABETH_GOLD:
	case ENEMY_LABETH_BLACK:
		pObj->etc = 5;
		pObj->motion = PO_C109_N0;
		InitMotion(pObj);
		break;
	case ENEMY_ELKEIN:
	case ENEMY_ELKEIN_RED:
	case ENEMY_ELKEIN_BLUE:
	case ENEMY_ELKEIN_PURPLE:
	case ENEMY_ELKEIN_GREEN:
	case ENEMY_ELKEIN_GOLD:
	case ENEMY_ELKEIN_BLACK:
		pObj->etc = 9;
		pObj->motion = PO_C110_BOSS_N0;
		InitMotion(pObj);
		break;
	case NPC_DELPIOS:
		pObj->etc = 0;
		pObj->motion = PO_C95_N0;
		InitMotion(pObj);
		break;
	case NPC_LORA:
		pObj->etc = 0;
		pObj->motion = PO_C96_N0_DRESS;
		InitMotion(pObj);
		break;
	}
	cnt++;

	pObj->etc = enemyAttackPattern[pObj->type * ATTACKPATTERNTOTALDATASIZE + 0];

	pObj->nx = pObj->x;
	pObj->ny = pObj->y;

	if (robin.bossRoom == true)
		pObj->id = MC_knlCurrentTimeStamp() + 3600;

	pObj->coolTime = MC_knlCurrentTimeStamp();

	//소환된 몬스터를 보여준다. 보스방은 한 번뿐이라 우선순위를 올리고,
	//일반 몬스터는 수십 번 반복되므로 가장 낮게 둔다 - 겹치면 밀려서 그냥 넘어간다.
	//한 웨이브에 여러 마리가 같이 나오면 큐가 전부 담는 줌으로 묶어 준다.
	RequestFocusZoom(obj, robin.bossRoom ? FOCUSPRI_BOSSSUMMON : FOCUSPRI_SUMMON);

	return cnt;
}

void SetNpc(OBJECT *pObj)
{
	pObj->active = enemyData[pObj->type * ENEMYDATASIZE + ENEMYDATA_ADDEXP];
	pObj->motion = crewPos[pObj->type * 5 + 0];

	pObj->dirY = DOWN;
	pObj->lv = mapData[13];
	//if (pObj->type < NPC_CAPTAIN)
	//	pObj->moveHandler = enemyData[pObj->type * ENEMYDATASIZE + ENEMYDATA_MOVEHANDLER];
	//else
	//	pObj->moveHandler = enemyData[pObj->type * ENEMYDATASIZE + ENEMYDATA_DRAWHANDLER];
	pObj->moveHandler = NPCMOVE;

	pObj->drawHandler = ENEMYDRAW;
	pObj->name = TEXT_MONSTERNAME_START + pObj->type;

	pObj->maxhp = pObj->hp = 1;

	//if (enemyData[pObj->type * ENEMYDATASIZE] < EMPTY)
		pObj->cmf = enemyData[pObj->type * ENEMYDATASIZE + ENEMYDATA_CMF];
	//else
	//	pObj->drawHandler = null;

	switch (pObj->type) {
	case NPC_KING:
		//pObj->etc = 3;
		//pObj->dirF = pObj->dirX = LEFT;
		break;
	case ENEMY_LARVA:
	case ENEMY_LARVA_RED:
	case ENEMY_LARVA_BLUE:
	case ENEMY_LARVA_PURPLE:
	case ENEMY_LARVA_GREEN:
	case ENEMY_LARVA_GOLD:
	case ENEMY_LARVA_BLACK:
		pObj->status = FLYING;
		break;
	}

#ifndef ENEMYSKILLTEST
	if (robin.bossRoom == true)
#endif
		pObj->skillIdx = true;
}

void SetRoom_Demo(void)
{
	int i;

	for (i = 0, movie.dCount = 0; i < TOTALDEMO; i++) {
		//만약 현재 방이
		if (robin.demoSeen[i] == false && demoData[i * DDLEN] == robinmap) {
			switch (i) {
				//여기부터는 앞에 특정데모를 봐야지만 형성되는 데모
			default:
				switch (demoData[i * DDLEN + 1]) {
				case TRIGGER_ALWAYS_ROOM:
				case TRIGGER_ROOM:
					if (robin.demoSeen[demoData[i * DDLEN + 2]] == true && robin.demoSeen[demoData[i * DDLEN + 3]] == true) {
						movie.movies[movie.dCount] = i;
						movie.dCount++;
					}
					break;
					//case TRIGGER_TALK:
					//case TRIGGER_PLACE:
				default:
					if (robin.demoSeen[demoData[i * DDLEN + 3]] == true || demoData[i * DDLEN + 3] == null) {
						movie.movies[movie.dCount] = i;
						movie.dCount++;
					}
					break;
				}
				break;
			}
		}
	}
}

void SetRoom_Quest(void)
{

}

void AddObject(OBJECT *pObj, OBJECT *pMom, int idx)
{
	const signed short *scPtr = &objectData[idx * OBJDATA_SIZE];
	int tempIdx = idx;
	int crewIdx = GetCrewIdxFromType(pMom->type);
	//if (robin.playtime % MOTIONDIV != 0)
	//	return;

	memset(pObj, 0, sizeof(OBJECT));
	//크류가 쏘는 총알
	if (tempIdx == ADDOBJ_CREWBULLET) {
		idx = skillData[pMom->currentSkill * SKILLDATASIZE + SKILLDATA_OBJECTDETAILINFO];
		scPtr = &objectData[idx * OBJDATA_SIZE];
		//TEST
		pObj->icon = skillData[pMom->currentSkill * SKILLDATASIZE + SKILLDATA_TARGET];
	}

	pObj->active = true;
	pObj->dirX = pObj->dirF = pMom->dirF;
	pObj->motion = *(scPtr + OBJDATA_MOTION);
	if (tempIdx == ADDOBJ_CREWBULLET) {
		pObj->cmf = enemyData[*(scPtr + OBJDATA_TYPE) * ENEMYDATASIZE + ENEMYDATA_CMF];
		pObj->type = GetTypeFromCmf(pObj->cmf);
		pObj->zoom = CREWBULLETZOOM + (float)0.25f * CREWBULLETZOOM * (pObj->icon % 3);// 1.0f;// enemyZoom[pObj->type] * ENEMYICONZOOM/* pMom->zoom*/;

	}
	else {
		pObj->cmf = pMom->cmf;
		pObj->type = pMom->type;
		pObj->zoom = pMom->zoom;
	}
	pObj->str = pMom->str;
	pObj->dx = *(scPtr + OBJDATA_DX) * pObj->zoom;
	pObj->dy = *(scPtr + OBJDATA_DY) * pObj->zoom;
	pObj->status = *(scPtr + OBJDATA_STATUS);
	pObj->lv = pMom->lv;
	pObj->mom = GetObjFromPtr(pMom);

	switch (*(scPtr + OBJDATA_TYPE)) {
	case -5:
		pObj->type = ENEMY_ELKEIN;
		break;
	case -4:
		pObj->type = ENEMY_LABETH;
		pObj->dirX = pObj->dirF = LEFT;
		break;
	case -3:
		pObj->type = NPC_EVAN;
		break;
	case -2:
		pObj->type = ENEMY_BULLET_SKEL;
		break;
	case -1:
		pObj->type = ENEMY_BULLET_NOSHADOW;
		break;
	default:
		pObj->type = *(scPtr + OBJDATA_TYPE);
		break;
	case OBJ_ITEM:
		pObj->attack = pObj->currentBullet;
		pObj->icon = GetItemIcon(ITEM_WASTE, pObj->attack, false);
		pObj->etc = (pObj->attack >= ITEM_WASTE_FIREELEMENTAL) ? 1 : 0;
		pObj->attr = (pObj->attack - ITEM_WASTE_FIRESTONE) % 5 + 1;
		break;
	}

	if (tempIdx == ADDOBJ_CREWBULLET) {
		pObj->x = pMom->x;
		pObj->y = pMom->y;

		pObj->drawHandler = BULLETCREWDRAW;
		pObj->moveHandler = FOLLOWMOVE;
		
		switch (idx) {
		case ADDOBJ_GIANT:
			pObj->motion = PO_C14_SHOT2;
			break;
		}
	}
	else {
		pObj->x = pMom->x + *(scPtr + OBJDATA_X) * DIR(pObj->dirF) * pObj->zoom;
		pObj->y = pMom->y + *(scPtr + OBJDATA_Y) * pObj->zoom;

		pObj->drawHandler = *(scPtr + OBJDATA_DRAW);
		pObj->moveHandler = *(scPtr + OBJDATA_MOVE);
	}

	if (*(scPtr + OBJDATA_TYPE) == OBJ_ITEM) {
		pObj->x -= 2 * DIR(pObj->dirF);
		pObj->y += 1 * _2X;
	}

	if (*(scPtr + OBJDATA_MOTION))
		InitMotion(pObj);
}

void SetCamera(void)
{
	int decider;
	int ryTemp = ry;

	decider = ao[focus].dirF;

	switch (drawHandle) {
	default:
		rx += ((Max(DX / 2 - 16 * _2X - ao[focus].dx * 2, Min((rw - 4) * TSIZE - DX / 2 + 16 * _2X + ao[focus].dx * 2, ao[focus].x)) - rx) - DX / 2 + (decider == LEFT ? -16 * _2X - ao[focus].dx * 2 : 16 * _2X + ao[focus].dx * 2)) / 4;
		ry += ((Max(REALDY * 2 / 3, Min((rh - 4) * TSIZE - REALDY / 3, ao[focus].y)) - ry) - REALDY * 2 / 3) / 3;
		rx = Max(0, Min(rx, (rw - 4) * TSIZE - DX));
		ry = -Max(0, Min(ry, (rh - 4) * TSIZE - REALDY));
		if (Abs(ryTemp - ry) < 1 * _2X)
			ry = ryTemp;
		break;
	case MD_RAID:

		break;
	}
}

//@@부하처리
void PopTalk(void)
{
	signed int i, distance;

	distance = -1;

	//만약 현재 누군가가 대화상대로 잡혀있다면
	if (talk.obj) {
		//그런데 만약 거리가 일정수준 이상 떨어졌다면 제거해주고
		if ((Abs(ao[raidPlayer].y - ao[talk.obj].y) > 2 * TSIZE) || (Abs(ao[raidPlayer].x - ao[talk.obj].x) > 1 * TSIZE)) {
			ao[talk.obj].icon = ao[talk.obj].iconFrame = null;
			talk.obj = talk.clr = talk.temp = null;
			talk.cur = 0;
			talk.frame = 0;
			talk.temp = 0;
			talk.width = 0;
			nameFrame = 0;
		}
		else
			distance = Abs(ao[raidPlayer].x - ao[talk.obj].x);
	}

	if (distance == -1)
		distance = 1 * TSIZE + 1;

	talk.temp = 0;

	if (talk.temp && talk.temp != talk.obj && talk.clr != talk.temp) {
		talk.obj = talk.clr = talk.temp;
		talk.cur = 0;
		talk.frame = 0;
		talk.temp = 0;
		talk.width = 0;

		for (i = ENEMY; i < NEUTRAL; i++) {
			ao[i].icon = ao[i].iconFrame = null;
		}

		ao[talk.obj].icon = EMOTICON_TALK;
		ao[talk.obj].iconFrame = EMOTICONFRAME;

		if (talk.obj != raidPlayer) {
			nameObj = talk.obj;
			nameFrame = INFOFRAME;
		}
	}
}



void DrawBackMapFar(int xPos, int yPos, int mapIdx, int dx, float zoom)
{
	int i = 0, j, y;
	const unsigned short* bgPtr;

	if (robinmap != mapIdx) {
		ReadMap(mapIdx);
	}

	//원경
	bgPtr = &mapBg[mapData[7] * 4];
	y = yPos + (float)((*(bgPtr + 3)) ? (PLAYAREA_Y + *(bgPtr + 3)) / 2 : 0 + *(bgPtr + 1)) * zoom;

	if (mapIdx != CASTLE11)
		MemRect(0, DY, dx, DY, mapColor[mapData[3]]);

	if (*(bgPtr + 3) > 0) {
		switch (mapData[7]) {
		case MAPTYPE_VALLEY:
			MemRect(0, yPos + (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, (float)dx * zoom, (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, 0x5F3B2D);
			break;
		case MAPTYPE_ELF:
			MemRect(0, yPos + (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, (float)dx * zoom, (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, 0x242B31);
			break;
		case MAPTYPE_GOLEMVALLEY:
			MemRect(0, yPos + (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, (float)dx * zoom, (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, 0x0A0208);
			break;
		case MAPTYPE_DRAGON:
			MemRect(0, yPos + (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, (float)dx * zoom, (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, 0x170805);
			break;
		case MAPTYPE_DARKNESS:
			MemRect(0, yPos + (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, (float)dx * zoom, (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, 0x0A2F3D);
			break;
		case MAPTYPE_GHOST:
			MemRect(0, yPos + (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, (float)dx * zoom, (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, 0x2B2F20);
			break;
		case MAPTYPE_DEVILCASTLE:
			MemRect(0, yPos + (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, (float)dx * zoom, (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, 0x182429);
			break;
		default:
			if (mapIdx != CASTLE11)
				MemRect(0, yPos + (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, (float)dx * zoom, (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, mapColor[mapData[3]]);
			break;
		}
	}

	if (*bgPtr) {
		do {
			int x = i * *(bgPtr + 2) - rx / TSIZE * _2X;

			DrawImage(*bgPtr, *(bgPtr + 1), 0, 0, xPos + (float)x * zoom, y - (float)TSIZE * zoom, false, false, false, false, false, zoom, sprite[MAP_BG_IMG + mapData[7]], MAP_BG_IMG + mapData[7]);

			if (*bgPtr != *(bgPtr + 2))
				DrawImage(*bgPtr, *(bgPtr + 1), 0, 0, xPos + (float)(x + *bgPtr) * zoom, y - (float)TSIZE * zoom, true, false, false, false, false, zoom, sprite[MAP_BG_IMG + mapData[7]], MAP_BG_IMG + mapData[7]);

			switch (mapData[7]) {
			case MAPTYPE_TOLEM:
				j = -1;

				do {
					j++;

					//b0.bmp
					DrawImage(48 * _2X, 25 * _2X, 0, 230 * _2X, xPos + (float)x * zoom, y + (float)(-*(bgPtr + 1) - 25 * _2X * j) * zoom, false, false, false, false, false, zoom, sprite[MAP_BG_IMG + mapData[7]], MAP_BG_IMG + mapData[7]);
					DrawImage(48 * _2X, 25 * _2X, 0 * _2X, 230 * _2X, xPos + (float)(x + *bgPtr) * zoom, y + (float)(-*(bgPtr + 1) - 25 * _2X * j) * zoom, true, false, false, false, false, zoom, sprite[MAP_BG_IMG + mapData[7]], MAP_BG_IMG + mapData[7]);
				} while (y - *(bgPtr + 1) - 25 * j * _2X > 0);

				DrawBgEffect((i + robin.playtime) % 5 + BG0_WATER0, xPos + (float)(x + *bgPtr) * zoom, y + (float)(-152 * _2X) * zoom, 0, zoom);

				if (robin.playtime % 1000 < 256) {
					if (robin.playtime % 1000 < 4)
						j = robin.playtime % 1000 + BG0_WATER_SIDE0;
					else if (robin.playtime % 1000 > 252)
						j = BG0_WATER_SIDE0 + EMPTY - robin.playtime % 1000;
					else
						j = robin.playtime % 4 + BG0_WATER_SIDE4;

					DrawBgEffect(j, xPos + (float)(x + *bgPtr) * zoom, y - (float)152 * _2X * zoom, 0, zoom);
					DrawBgEffect(j, xPos + (float)(x + *bgPtr) * zoom, y - (float)152 * _2X * zoom, 1, zoom);
				}

				break;
			case MAPTYPE_ATLANTICE:
				DrawBgEffect(BG4_AQUA0 + robin.playtime / 2 % 4, xPos + (float)(x + 64 * _2X) * zoom, y - (float)80 * _2X * zoom, 0, zoom);
				break;
			case MAPTYPE_FLAME:
				//왼쪽 바위부분
				SetAlpha(Abs(16 - ((robin.playtime + i * 8) % 32)) * 2);
				//bg.bmp
				DrawImage(17 * _2X, 36 * _2X, 102 * _2X, 38 * _2X, xPos + (float)(x + 4 * _2X) * zoom, y - (float)92 * _2X * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);

				//아래쪽 용암
				j = Abs(16 - ((robin.playtime + 16 + i * 8) % 32)) * 2;
				SetAlpha(j);
				DrawBgEffect(BG9_MAGMA, xPos + (float)x * zoom, y - (float)208 * _2X * zoom, 0, zoom);

				//불꽃1
				SetAlpha(32 - j);
				DrawBgEffect(BG9_MAGMA_FIRE0, xPos + (float)(x + 48 * _2X) * zoom, y + (float)(-208 * _2X + (32 - j) / 2 * _2X) * zoom, 0, zoom);

				//불꽃2
				j = (robin.playtime + 16 + i * 8) % 32;

				SetAlpha(40 - j);

				if (j >= 10 && j < 18)
					DrawBgEffect(BG9_MAGMA_FIRE1, xPos + (float)(x + 48 * _2X) * zoom, y + (float)(-208 * _2X + (j - 20) / 2 * _2X) * zoom, 0, zoom);

				SetAlpha(32);

				//떨어지는 종유석
				j = (robin.playtime + i * 36) % 100;

				if (j < 42) {
					SetAlpha(j);
					DrawBgEffect(BG9_ETC0, xPos + (float)x * zoom, y, 0, zoom);
				}
				else if (j < 58)
					DrawBgEffect(BG9_ETC0, xPos + (float)(x + robin.playtime % 3 - 1 * _2X) * zoom, y, 0, zoom);
				else if (j < 64) {
					SetAlpha((64 - j) * 6);
					DrawBgEffect(BG9_ETC0, xPos + (float)x * zoom, y + (float)(-(j - 57) * (j - 57) * 3 * _2X) * zoom, 0, zoom);
				}
				else if (j < 68) {
					SetAlpha((68 - j) * 8);
					DrawBgEffect(BG9_ETC1 + j % 2, xPos + (float)x * zoom, y + (float)(-144 * _2X) * zoom, 0, zoom);
				}

				SetAlpha(32);
				break;
			case MAPTYPE_THUNDER:
				//번개지대 원경효과
				DrawBgEffect(BG11_BACK0 + robin.playtime / 2 % 3, xPos + (float)x * zoom, y, 0, zoom);
				DrawBgEffect(BG11_BACK3 + robin.playtime % 8, xPos + (float)x * zoom, y, 0, zoom);
				break;
			case MAPTYPE_LIGHT:
				//빛의지대 원경효과
				j = (robin.playtime + i * 36) % 100;

				if (j < 15)
					DrawBgEffect(BG12_LIGHT0 + j, xPos + (float)x * zoom, y - (float)64 * _2X * zoom, 0, zoom);
				break;
			case MAPTYPE_DARKNESS:
				//어둠의 지대 오오라
				j = (robin.playtime + i * 3) % 30;

				if (j < 15)
					DrawBgEffect(BG14_AURORA0 + j, xPos + (float)(x + 42 * _2X) * zoom, y - (float)7 * _2X * zoom, 0, zoom);

				j = (robin.playtime + i * 3 + 15) % 30;

				if (j < 15)
					DrawBgEffect(BG14_AURORA0 + j, xPos + x + (float)12 * _2X * zoom, y - (float)36 * _2X * zoom, 0, zoom);
				break;
			}
			i++;
		} while (i * *(bgPtr + 2) - rx / 16 < dx);
	}

	//원경 효과들
	switch (mapData[7]) {
	case MAPTYPE_ATLANTICE:
		//물고기
		for (i = 0; i < MAXBGOBJECT; i++) {
			if (bgObj[i].active)
				DrawBgEffect(BG4_FISH0 + 7 * bgObj[i].etc + (robin.playtime / 2 + i) % 7, xPos + (float)(bgObj[i].x - rx) * zoom, y + (float)(*(bgPtr + 1) - bgObj[i].y - ry) * zoom, (bgObj[i].dx > 0 ? 1 : 0), zoom);
			else
				break;
		}
	case MAPTYPE_FROST:
	case MAPTYPE_CASTLE:
		break;
	case MAPTYPE_GOLEMVALLEY:
		//골렘 협곡 구름
		for (i = 0; i < MAXBGOBJECT - 4; i++) {
			if (bgObj[i].active == true && bgObj[i].etc < 3)
				DrawBgEffect(BG13_CLOUD0 + bgObj[i].etc % 3, xPos + (float)(bgObj[i].x - rx) * zoom, y + (float)(*(bgPtr + 1) - bgObj[i].y - ry) * zoom, 0, zoom);
		}
		break;
	case MAPTYPE_DARKNESS:
		for (i = 0; i < MAXBGOBJECT; i++) {
			SetAlpha(Abs(32 - (robin.playtime + bgObj[i].etc) % 64));
			//bg14.bmp
			DrawImage(5 * _2X, 5 * _2X, 18 * _2X, 172 * _2X, xPos + (float)(bgObj[i].x - rx) * zoom, y + (float)(*(bgPtr + 1) - bgObj[i].y) * zoom, false, false, false, true, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			SetAlpha(32);
		}
		break;
	case MAPTYPE_GHOST:
		//망자의 도시 구름 및 안개
		for (i = 0; i < MAXBGOBJECT; i++) {
			if (bgObj[i].active == true && bgObj[i].etc)
				DrawBgEffect(BG16_CLOUD0 + bgObj[i].etc, xPos + (float)(bgObj[i].x - rx) * zoom, y + (float)(*(bgPtr + 1) - bgObj[i].y - ry) * zoom, 0, zoom);
		}
		break;
	case MAPTYPE_SPACE:
		//우주지역 위성 및 유성
		for (i = 0; i < MAXBGOBJECT; i++) {
			if (bgObj[i].active) {
				if (bgObj[i].etc < 3)
					DrawBgEffect(BG18_SATELITE0 + bgObj[i].etc, xPos + (float)(bgObj[i].x - rx) * zoom, y + (float)(-bgObj[i].y - ry) * zoom, 0, zoom);
				else {
					SetAlpha(16 - Abs(DY / 2 - bgObj[i].y) / 8);
					DrawBgEffect(BG18_METEOR0 - 3 + bgObj[i].etc, xPos + (float)(bgObj[i].x - rx) * zoom, y + (float)(*(bgPtr + 1) - bgObj[i].y - ry) * zoom, 0, zoom);
					SetAlpha(32);
				}
			}
		}
		break;
	}
	//보스방이면
	if (robin.bossRoom == true) {
		//if (frame % 200 >= 100 && frame % 200 < 119) {
		if (frame % (FPS * 3) == 0) {
			effect.shake = 2;
		}
		//if (frame % (FPS * 3) >= 0 && frame % (FPS * 3) < 19) {
		//}
		//}	
	}
}

void DrawBackMapFront(int xPos, int yPos, int mapIdx, float zoom)
{
	int i, j, y;
	const unsigned short* bgPtr;

	if (robinmap != mapIdx) {
		ReadMap(mapIdx);
	}

	//근경 파트1
	for (i = 0, j = 0; i < mapData[5]; i++) {
		signed short* mbObj = &mapBackObj[i * 3];

		temp = 0;
		bgPtr = &backObjImg[Abs(*mbObj) * 4];

		switch (Abs(*mbObj)) {
		case IMG_BG0_2:
			//굴뚝 연기
			if ((robin.playtime + *(mbObj + 1)) / 2 % 20 < 8)
				DrawBgEffect(BG0_SMOKE0 + (robin.playtime + *(mbObj + 1)) / 2 % 20, xPos + (float)*(mbObj + 1) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, 0, zoom);
			break;
		case IMG_BG0_39:
		case IMG_BG0_42:
			//톨렘마을 수면
			SetAlpha(20);

			bgPtr += 4 * (robin.playtime / 2 % 3);
			break;
		case IMG_BG3_3:
			//계곡 갈대
			if (bgObj[j].frame == 0)
				bgObj[j].frame = 1;

			y = robin.playtime / 2 % bgObj[j].frame;

			if (y > 3 && y < 9)
				DrawBgEffect(BG3_REED_SEED0 - 4 + y, xPos + (float)*(mbObj + 1) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, 0, zoom);

			if (y < 10)
				y %= 3;
			else
				y = 0;

			DrawBgEffect((*mbObj > 0 ? BG3_REED0 : BG3_REED3) + (y % 3), xPos + (float)*(mbObj + 1) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, 0, zoom);

			j++;
			continue;
		case IMG_BG6_64:
			//분수대 물
			if (robin.playtime / MOTIONDIV % 2 == 0) {
				bgPtr += 4;
				temp = -1;
			}
			break;
		case IMG_BG12_1:
			//빛의지대 스탠드 : bg12.bmp
			SetAlpha(32 - Abs(robin.playtime % 32 - 16));
			DrawImage(14 * _2X, 14 * _2X, 14 * _2X, 54 * _2X, xPos + (float)(*(mbObj + 1) + 2 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) - 1 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			SetAlpha(32);
			break;
		case IMG_BG9_1:
			//홍염의 대지
			DrawImage(34 * _2X, 30 * _2X, 119 * _2X, 32 * _2X, xPos + (float)(*(mbObj + 1) + 4 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) - 16 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG17_12:
		case IMG_BG17_13:
		case IMG_BG17_14:
		case IMG_BG17_15:
		case IMG_BG17_16:
			//마왕성 발판 : bg17.bmp
			DrawImage(16 * _2X, 24 * _2X, 17 * _2X, 112 * _2X, xPos + (float)(*(mbObj + 1) - 8 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) + 3 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			DrawImage(16 * _2X, 24 * _2X, 17 * _2X, 112 * _2X, xPos + (float)(*(mbObj + 1) + 8 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) + 3 * _2X) * zoom, true, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG17_4:
			//마왕성 기타 : bg17.bmp
			if (*mbObj > 0)
				DrawImage(16 * _2X, 32 * _2X, 40 * _2X, 124 * _2X, xPos + (float)*(mbObj + 1) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			else
				DrawImage(16 * _2X, 32 * _2X, 40 * _2X, 124 * _2X, xPos + (float)(*(mbObj + 1) - 7 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG_WITCHHOUSE:
			DrawImage(114 * _2X, 136 * _2X, 0 * _2X, 0 * _2X, xPos + (float)*(mbObj + 1) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, false, false, false, false, false, zoom, sprite[CASTLE_IMG], CASTLE_IMG);
			continue;
		case IMG_BG_BOSSSTATUE:
			//보스 표지판 : c.bmp
			if (*mbObj < 0)
				DrawImage(32 * _2X, 48 * _2X, 214 * _2X, 93 * _2X, xPos + (float)(*(mbObj + 1) - 16 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) + 54 * _2X) * zoom, true, false, false, false, false, zoom, sprite[COMMON_IMG], COMMON_IMG);
			else
				DrawImage(32 * _2X, 48 * _2X, 214 * _2X, 93 * _2X, xPos + (float)(*(mbObj + 1) - 16 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) + 54 * _2X) * zoom, false, false, false, false, false, zoom, sprite[COMMON_IMG], COMMON_IMG);
			continue;
		case IMG_BG_REDORB:
		case IMG_BG_YELLOWORB:
		case IMG_BG_PURPLEORB:
		case IMG_BG_GRAYORB:
		case IMG_BG_BLUEORB:

			SetAlpha(Abs(8 - robin.playtime % 16) * 4);
			DrawImage(10 * _2X, 20 * _2X, 28 * _2X, 136 * _2X, xPos + (float)(*(mbObj + 1) - 10 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) + 10 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			DrawImage(10 * _2X, 20 * _2X, 28 * _2X, 136 * _2X, xPos + (float)*(mbObj + 1) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) + 10 * _2X) * zoom, true, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			SetAlpha(32);

			DrawImage(8 * _2X, 16 * _2X, 106 * _2X, 0 + 16 * _2X * (*mbObj - IMG_BG_REDORB), xPos + (float)(*(mbObj + 1) - 8 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) + 8 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			DrawImage(8 * _2X, 16 * _2X, 106 * _2X, 0 + 16 * _2X * (*mbObj - IMG_BG_REDORB), xPos + (float)*(mbObj + 1) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) + 8 * _2X) * zoom, true, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);

			continue;
		}

		if (*mbObj < 0)
			DrawImage(*(bgPtr + 2), *(bgPtr + 3), *bgPtr, *(bgPtr + 1), xPos + (float)*(mbObj + 1) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, true, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
		else
			DrawImage(*(bgPtr + 2), *(bgPtr + 3), *bgPtr, *(bgPtr + 1), xPos + (float)(*(mbObj + 1) + temp) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);

		switch (*mbObj) {
		case IMG_BG0_29:
			//풍향계
			if (robin.playtime % 14 < 7)
				DrawBgEffect(BG0_WINDMETER0 + robin.playtime % 7, xPos + (float)*(mbObj + 1) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, 0, zoom);
			else
				DrawBgEffect(BG0_WINDMETER6 - robin.playtime % 7, xPos + (float)(*(mbObj + 1) + 7 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, 1, zoom);
			break;
		case IMG_BG0_39:
		case IMG_BG0_41:
			SetAlpha(32);
			break;
		case IMG_BG11_0:
			//번개지대 플라스크 : bg11.bmp
			DrawImage(5 * _2X, 17 * _2X, 18 * _2X, 23 * _2X, xPos + (float)(*(mbObj + 1) + 6 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) - 4 * _2X + Random(3) * _2X) * zoom, false, false, false, false, false, 1.0f, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG11_1:
			//번개지대 등불 : bg11.bmp
			SetAlpha(32 - Abs(robin.playtime % 32 - 16) * 2);
			DrawImage(5 * _2X, 5 * _2X, 59 * _2X, 21 * _2X, xPos + (float)(*(mbObj + 1) + 4 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) - 8 * _2X) * zoom, false, false, false, false, false, 1.0f, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			SetAlpha(32);
			break;
		case IMG_BG12_0:
			//빛의지대 꽃잔
			j = (robin.playtime + i * 20) % 160;

			if (j < 120) {
				if (j < 7)
					DrawBgEffect(BG12_FLOWER0 + j, xPos + (float)*(mbObj + 1) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, 0, zoom);
				else if (j > 113)
					DrawBgEffect(BG12_FLOWER0 + 120 - j, xPos + (float)*(mbObj + 1) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, 0, zoom);
				else
					DrawBgEffect(BG12_FLOWER7, xPos + (float)*(mbObj + 1) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, 0, zoom);
			}
			break;
		case IMG_BG1_10:
			//집 내부 난로 파이프
			DrawImage(32 * _2X, 8 * _2X, 132 * _2X, 20 * _2X, xPos + (float)(*(mbObj + 1) - 22 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) - 28 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			DrawImage(11 * _2X, 14 * _2X, 177 * _2X, 109 * _2X, xPos + (float)(*(mbObj + 1) - 23 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) - 36 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG1_37:
			//집 내부 램프
			DrawImage(15 * _2X, 29 * _2X, 60 * _2X, 77 * _2X, xPos + (float)(*(mbObj + 1) - 7 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) - 15 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG1_39:
			//집 내부 커튼
			DrawImage(23 * _2X, 22 * _2X, 109 * _2X, 34 * _2X, xPos + (float)(*(mbObj + 1) + 27 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG2_0:
			//톨레아 습지 나무
			DrawImage(66 * _2X, 32 * _2X, 0 * _2X, 80 * _2X, xPos + (float)(*(mbObj + 1) + 24 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) - 80 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG6_2:
			//아델성 깃발
			DrawImage(13 * _2X, 48 * _2X, 158 * _2X, 0 * _2X, xPos + (float)(*(mbObj + 1) + 13 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, true, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG6_4:
			//아델성 문
			DrawImage(25 * _2X, 57 * _2X, 0 * _2X, 130 * _2X, xPos + (float)(*(mbObj + 1) + 25 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, true, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG6_5:
			//아델성 창문
			DrawImage(30 * _2X, 8 * _2X, 171 * _2X, 24 * _2X, xPos + (float)*(mbObj + 1) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) - 24 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG6_8:
			//아델성 책장
			DrawImage(16 * _2X, 42 * _2X, 195 * _2X, 127 * _2X, xPos + (float)(*(mbObj + 1) + 16 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, true, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG6_10:
			//아델성 커튼
			DrawImage(10 * _2X, 60 * _2X, 201 * _2X, 0 * _2X, xPos + (float)(*(mbObj + 1) + 10 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - ry - *(mbObj + 2)) * zoom, true, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG6_12:
			//아델성 석상
			DrawImage(24 * _2X, 24 * _2X, 83 * _2X, 48 * _2X, xPos + (float)(*(mbObj + 1) - 1 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) - 37 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG6_13:
			//아델성 석상2
			DrawImage(24 * _2X, 24 * _2X, 83 * _2X, 48 * _2X, xPos + (float)(*(mbObj + 1) - 1 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) - 36 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG6_17:
			//아델성 난간
			DrawImage(15 * _2X, 18 * _2X, 113 * _2X, 134 * _2X, xPos + (float)(*(mbObj + 1) + 15 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, true, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG6_66:
			//아델성 문장식
			DrawImage(24 * _2X, 26 * _2X, 171 * _2X, 143 * _2X, xPos + (float)(*(mbObj + 1) + 6 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) + 20 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			DrawImage(24 * _2X, 26 * _2X, 171 * _2X, 143 * _2X, xPos + (float)(*(mbObj + 1) + 30 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) + 20 * _2X) * zoom, true, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			DrawImage(7 * _2X, 25 * _2X, 204 * _2X, 98 * _2X, xPos + (float)(*(mbObj + 1) + 53 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG6_26:
			//아델성 문장식2
			DrawImage(24 * _2X, 26 * _2X, 171 * _2X, 143 * _2X, xPos + (float)(*(mbObj + 1) + 24 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG6_25:
			//아델성 문장식2
			DrawImage(19 * _2X, 28 * _2X, 25 * _2X, 146 * _2X, xPos + (float)(*(mbObj + 1) + 19 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, true, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG6_58:
			//아델성 조리기구
			DrawImage(24 * _2X, 24 * _2X, 131 * _2X, 152 * _2X, xPos + (float)(*(mbObj + 1) + 20 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, true, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG13_1:
			//골렘지대 석상
			SetAlpha(Abs(8 - robin.playtime % 16) * 4);
			DrawBgEffect(BG13_STATUE0, xPos + (float)*(mbObj + 1) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, 0, zoom);
			SetAlpha(32);
			break;
		case IMG_BG13_9:
			//골렘지역 난간 : bg13.bmp
			DrawImage(23 * _2X, 6 * _2X, 61 * _2X, 75 * _2X, xPos + (float)(*(mbObj + 1) + 5 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			DrawImage(6 * _2X, 14 * _2X, 16 * _2X, 99 * _2X, xPos + (float)(*(mbObj + 1) + 26 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG14_8:
			//어둠의 정령 투수 : bg14.bmp
			DrawImage(16 * _2X, 32 * _2X, 16 * _2X, 71 * _2X, xPos + (float)(*(mbObj + 1) + 16 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, true, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG15_2:
			DrawBgEffect(BG15_FLAG0 + robin.playtime / 2 % 3, xPos + (float)*(mbObj + 1) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, 0, zoom);
			break;
		case IMG_BG15_3:
			//드래곤의 무덤 : bg15.bmp
			DrawImage(39 * _2X, 13 * _2X, 0 * _2X, 158 * _2X, xPos + (float)(*(mbObj + 1) - 1 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) - 25 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			DrawImage(60 * _2X, 34 * _2X, 0 * _2X, 70 * _2X, xPos + (float)(*(mbObj + 1) + 29 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) - 6 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG16_2:
			//망자의 도시 나무 : bg16.bmp
			DrawImage(27 * _2X, 27 * _2X, 109 * _2X, 20 * _2X, xPos + (float)(*(mbObj + 1) + 15 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) - 43 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG17_10:
			//마왕성 창문 하단 : bg17.bmp
			DrawImage(16 * _2X, 16 * _2X, 34 * _2X, 48 * _2X, xPos + (float)*(mbObj + 1) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) + 16 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			DrawImage(16 * _2X, 16 * _2X, 34 * _2X, 48 * _2X, xPos + (float)(*(mbObj + 1) + 16 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) + 16 * _2X) * zoom, true, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			DrawImage(16 * _2X, 16 * _2X, 34 * _2X, 64 * _2X, xPos + (float)(*(mbObj + 1) + *(bgPtr + 2)) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, true, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG17_6:
			//마왕성 오망성 : bg17.bmp
			DrawImage(78 * _2X, 156 * _2X, 114 * _2X, 0 * _2X, xPos + (float)186 * _2X * zoom, yPos + (float)((rh - 4) * TSIZE - 296 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			DrawImage(78 * _2X, 156 * _2X, 114 * _2X, 0 * _2X, xPos + (float)264 * _2X * zoom, yPos + (float)((rh - 4) * TSIZE - 296 * _2X) * zoom, true, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			//덮어그리는 타일

			break;
		case IMG_BG17_7:
			//마왕성 샹들리에 : bg17.bmp
			DrawImage(4 * _2X, 10 * _2X, 64 * _2X, 50 * _2X, xPos + (float)(*(mbObj + 1) + 16 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) + 10 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
		case IMG_BG16_6:
			//망자의 도시 철창 : bg16.bmp
		case IMG_BG17_8:
			//마왕성 창문 상단 : bg17.bmp
		case IMG_BG17_9:
			//마왕성 창문 중단 : bg17.bmp
		case IMG_BG17_17:
			//마왕성 소켓 : bg17.bmp
			DrawImage(*(bgPtr + 2), *(bgPtr + 3), *bgPtr, *(bgPtr + 1), xPos + (float)(*(mbObj + 1) + *(bgPtr + 2)) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, true, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		case IMG_BG16_7:
			//망자의 도시 촛불
			DrawBgEffect(BG16_CANDLE0 + Abs(4 - robin.playtime % 8), xPos + (float)*(mbObj + 1) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, 0, zoom);
			break;
		case IMG_BG17_1:
			//마왕성 촛불
			DrawBgEffect(BG17_CANDLE0 + robin.playtime / 2 % 4, xPos + (float)(*(mbObj + 1)) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, 0, zoom);
			break;
		case IMG_BG17_11:
			DrawBgEffect(BG17_MIRROR, xPos + (float)(*(mbObj + 1)) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, 0, zoom);
			break;
		case IMG_BG17_18:
			DrawImage(10 * _2X, 29 * _2X, 96 * _2X, 0 * _2X, xPos + (float)(*(mbObj + 1) - 10 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) - 19 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			DrawImage(10 * _2X, 48 * _2X, 96 * _2X, 106 * _2X, xPos + (float)(*(mbObj + 1) + 10 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2)) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			DrawImage(10 * _2X, 29 * _2X, 96 * _2X, 77 * _2X, xPos + (float)(*(mbObj + 1) + 20 * _2X) * zoom, yPos + (float)((rh - 4) * TSIZE - *(mbObj + 2) - 19 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			break;
		}
	}
}

void DrawBackMap_Back(int xPos, int yPos, int mapIdx, float zoom)
{
	int i = 0, j, y, t;
	int iStart, iEnd, jStart, jEnd;
	const unsigned char* bgPtrChar;

	DrawBackMapFar(xPos, yPos, mapIdx, rw * TSIZE, zoom);

	//타일
	iStart = 0;
	iEnd = rh - 4;
	jStart = 0;
	jEnd = rw - 4;


	switch (mapData[7]) {
	default:
		for (i = 0; i < iEnd; i++) {
			for (j = 0; j < jEnd; j++) {
				y = mapArray[i * mapData[1] + j] - 1;

				if (y >= 0) {
					DrawImage(TSIZE, TSIZE, (y % MAXTILE) * TSIZE, y / MAXTILE * TSIZE, xPos + (float)(-rx + TSIZE * j) * zoom, yPos - ry + (float)((rh - 4) * TSIZE - TSIZE * i) * zoom, false, false, false, false, false, zoom, sprite[MAP_TILE_IMG + mapData[7]], MAP_TILE_IMG + mapData[7]);
				}
			}
		}
		break;
	case MAPTYPE_FLAME:
		for (i = iStart; i < iEnd; i++) {
			for (j = jStart; j < jEnd; j++) {
				y = mapArray[i * mapData[1] + j] - 1;

				if (y >= 0) {
					if (y < 44 * _2X)
						t = y;
					else {
						bgPtrChar = &mapInfoArray[mapInfoOff + (i + 1) * rw + j];
						t = (*bgPtrChar == TILE_BLAZE) ? robin.playtime / 4 : robin.playtime;

						if (y >= 62 * _2X)
							t = (y - (t % 2) * 14 * _2X);
						else if (y >= 58 * _2X) {
							if (*bgPtrChar == TILE_BLAZE_RIGHT)
								t = 61 * _2X - (y + t * 3) % 4 * _2X;
							else
								t = 58 * _2X + (y + t) % 4 * _2X;
						}
						else if (y >= 48 * _2X)
							t = y + (t % 2) * 14 * _2X;
						else if (y >= 44 * _2X) {
							if (*bgPtrChar == TILE_BLAZE_RIGHT)
								t = 47 * _2X - (y + t * 3) % 4 * _2X;
							else
								t = 44 * _2X + (y + t) % 4 * _2X;
						}
					}

					DrawImage(TSIZE, TSIZE, (t % MAXTILE) * TSIZE, t / MAXTILE * TSIZE, xPos + (float)(-rx + TSIZE * j) * zoom, yPos - ry + (float)((rh - 4) * TSIZE - TSIZE * i) * zoom, false, false, false, false, false, zoom, sprite[MAP_TILE_IMG + mapData[7]], MAP_TILE_IMG + mapData[7]);

				}
			}
		}
		break;
	}


	DrawBackMapFront(xPos, yPos, mapIdx, zoom);
}


void DrawBackMap(int xPos, int yPos, int mapIdx, float zoom)
{
	int i = 0, y;
	const unsigned short* bgPtr;

	if (robinmap != mapIdx) {
		ReadMap(mapIdx);
	}

	//원경
	bgPtr = &mapBg[mapData[7] * 4];
	y = yPos + (float)((*(bgPtr + 3)) ? (PLAYAREA_Y + *(bgPtr + 3)) / 2 : 0 + *(bgPtr + 1)) * zoom;

	DrawBackMap_Back(xPos, yPos, mapIdx, zoom);

	//근경 이후 그려지는 추가효과
	switch (mapData[7]) {
	case MAPTYPE_SWAMP:
		//톨레아습지 수면
		for (i = 0; i < TOTALBUBBLE; i++) {
			if (swampBubble[i * 4] == robinmap && (robin.playtime + swampBubble[i * 4 + 3]) % 9 < 5) {
				const signed char* swPtr = &swampSplash[(9 + (robin.playtime + swampBubble[i * 4 + 3]) % 9) * 4];

				bgPtr = &swampImg[*swPtr * 4];
				DrawImage(*(bgPtr + 2), *(bgPtr + 3), *bgPtr, *(bgPtr + 1), xPos + (float)(swampBubble[i * 4 + 1] * 4 + *(swPtr + 1) - rx) * zoom, yPos + (float)((rh - 4) * TSIZE - swampBubble[i * 4 + 2] * 4 - *(swPtr + 2) + ry - 3 * _2X) * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);
			}
		}
		break;
	case MAPTYPE_ATLANTICE:
		//아틀란티스 수면
		break;
	}

	if (robinmap != mapIdx) {
		ReadMap(robinmap);
	}
}
void DrawBg(int mapIdx, int yPos, float zoom)
{
	int i = 0, j, y;
	const unsigned short* bgPtr;

	SetSectionClip(0, yPos + (float)(PLAYAREA_Y)*zoom, (float)(DX)*zoom, (float)(PLAYAREA_Y)*zoom, IsOffscreenTarget());
	ReadMap(mapIdx);

	//원경
	bgPtr = &mapBg[mapData[7] * 4];

	y = yPos + ((*(bgPtr + 3)) ? (PLAYAREA_Y + *(bgPtr + 3)) / 2 : 0 + *(bgPtr + 1));

	MemRect(0, DY, DX, REALDY, mapColor[mapData[3]]);

	if (*(bgPtr + 3) > 0) {
		switch (mapData[7]) {
		case MAPTYPE_VALLEY:
			MemRect(0, yPos + (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, (float)(rw * TSIZE) * zoom, (float)((REALDY - *(bgPtr + 3))) * zoom, 0x5F3B2D);
			break;
		case MAPTYPE_ELF:
			MemRect(0, yPos + (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, (float)(rw * TSIZE) * zoom, (float)((REALDY - *(bgPtr + 3))) * zoom, 0x242B31);
			break;
		case MAPTYPE_GOLEMVALLEY:
			MemRect(0, yPos + (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, (float)(rw * TSIZE) * zoom, (float)((REALDY - *(bgPtr + 3))) * zoom, 0x0A0208);
			break;
		case MAPTYPE_DRAGON:
			MemRect(0, yPos + (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, (float)(rw * TSIZE) * zoom, (float)((REALDY - *(bgPtr + 3))) * zoom, 0x170805);
			break;
		case MAPTYPE_DARKNESS:
			MemRect(0, yPos + (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, (float)(rw * TSIZE) * zoom, (float)((REALDY - *(bgPtr + 3))) * zoom, 0x0A2F3D);
			break;
		case MAPTYPE_GHOST:
			MemRect(0, yPos + (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, (float)(rw * TSIZE) * zoom, (float)((REALDY - *(bgPtr + 3))) * zoom, 0x2B2F20);
			break;
		case MAPTYPE_DEVILCASTLE:
			MemRect(0, yPos + (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, (float)(rw * TSIZE) * zoom, (float)((REALDY - *(bgPtr + 3))) * zoom, 0x182429);
			break;
		default:
			MemRect(0, yPos + (float)((REALDY - *(bgPtr + 3)) / 2) * zoom, (float)(rw * TSIZE) * zoom, (float)((REALDY - *(bgPtr + 3))) * zoom, mapColor[mapData[3]]);
			break;
		}
	}

	if (*bgPtr) {
		do {
			int x = i * *(bgPtr + 2);

			DrawImage(*bgPtr, *(bgPtr + 1), 0, 0, x, y, false, false, false, false, false, zoom, sprite[MAP_BG_IMG + mapData[7]], MAP_BG_IMG + mapData[7]);

			if (*bgPtr != *(bgPtr + 2))
				DrawImage(*bgPtr, *(bgPtr + 1), 0, 0, x + (float)*bgPtr * zoom, y, true, false, false, false, false, zoom, sprite[MAP_BG_IMG + mapData[7]], MAP_BG_IMG + mapData[7]);

			switch (mapData[7]) {
			case MAPTYPE_TOLEM:
				j = -1;

				do {
					j++;

					//b0.bmp
					DrawImage(48 * _2X, 25 * _2X, 0 * _2X, 230 * _2X, x, y + (float)(-*(bgPtr + 1) - 25 * _2X * j) * zoom, false, false, false, false, false, zoom, sprite[MAP_BG_IMG + mapData[7]], MAP_BG_IMG + mapData[7]);
					DrawImage(48 * _2X, 25 * _2X, 0 * _2X, 230 * _2X, x + (float)*bgPtr * zoom, y + (float)(-*(bgPtr + 1) - 25 * _2X * j) * zoom, true, false, false, false, false, zoom, sprite[MAP_BG_IMG + mapData[7]], MAP_BG_IMG + mapData[7]);
				} while (y - *(bgPtr + 1) - 25 * _2X * j > 0);

				DrawBgEffect((i + robin.playtime) % 5 + BG0_WATER0, x + (float)*bgPtr * zoom, y - (float)152 * _2X * zoom, 0, zoom);

				if (robin.playtime % 1000 < 256) {
					if (robin.playtime % 1000 < 4)
						j = robin.playtime % 1000 + BG0_WATER_SIDE0;
					else if (robin.playtime % 1000 > 252)
						j = BG0_WATER_SIDE0 + EMPTY - robin.playtime % 1000;
					else
						j = robin.playtime % 4 + BG0_WATER_SIDE4;

					DrawBgEffect(j, x + (float)*bgPtr * zoom, y - (float)152 * _2X * zoom, 0, zoom);
					DrawBgEffect(j, x + (float)*bgPtr * zoom, y - (float)152 * _2X * zoom, 1, zoom);
				}

				break;
			case MAPTYPE_ATLANTICE:
				DrawBgEffect(BG4_AQUA0 + robin.playtime / 2 % 4, x + (float)64 * _2X * zoom, y - (float)80 * _2X * zoom, 0, zoom);
				break;
			case MAPTYPE_FLAME:
				//왼쪽 바위부분
				SetAlpha(Abs(16 - ((robin.playtime + i * 8) % 32)) * 2);
				//bg.bmp
				DrawImage(17 * _2X, 36 * _2X, 102 * _2X, 38 * _2X, x + (float)4 * _2X * zoom, y - (float)92 * _2X * zoom, false, false, false, false, false, zoom, sprite[MAP_OBJ_IMG + mapData[7]], MAP_OBJ_IMG + mapData[7]);

				//아래쪽 용암
				j = Abs(16 - ((robin.playtime + 16 + i * 8) % 32)) * 2;
				SetAlpha(j);
				DrawBgEffect(BG9_MAGMA, x, y - (float)208 * _2X * zoom, 0, zoom);

				//불꽃1
				SetAlpha(32 - j);
				DrawBgEffect(BG9_MAGMA_FIRE0, x + (float)48 * _2X * zoom, y + (float)(-208 * _2X + (32 - j) * _2X / 2) * zoom, 0, zoom);

				//불꽃2
				j = (robin.playtime + 16 + i * 8) % 32;

				SetAlpha(40 - j);

				if (j >= 10 && j < 18)
					DrawBgEffect(BG9_MAGMA_FIRE1, x + (float)48 * _2X * zoom, y + (float)(-208 * _2X + (j - 20) * _2X / 2) * zoom, 0, zoom);

				SetAlpha(32);

				//떨어지는 종유석
				j = (robin.playtime + i * 36) % 100;

				if (j < 42) {
					SetAlpha(j);
					DrawBgEffect(BG9_ETC0, x, y, 0, zoom);
				}
				else if (j < 58)
					DrawBgEffect(BG9_ETC0, x + (float)(robin.playtime % 3 - 1 * _2X) * zoom, y, 0, zoom);
				else if (j < 64) {
					SetAlpha((64 - j) * 6);
					DrawBgEffect(BG9_ETC0, x, y + (float)(-(j - 57) * (j - 57) * 3 * _2X) * zoom, 0, zoom);
				}
				else if (j < 68) {
					SetAlpha((68 - j) * 8);
					DrawBgEffect(BG9_ETC1 + j % 2, x, y - (float)144 * _2X * zoom, 0, zoom);
				}

				SetAlpha(32);
				break;
			case MAPTYPE_THUNDER:
				//번개지대 원경효과
				DrawBgEffect(BG11_BACK0 + robin.playtime / 2 % 3, x, y, 0, zoom);
				DrawBgEffect(BG11_BACK3 + robin.playtime % 8, x, y, 0, zoom);
				break;
			case MAPTYPE_LIGHT:
				//빛의지대 원경효과
				j = (robin.playtime + i * 36) % 100;

				if (j < 15)
					DrawBgEffect(BG12_LIGHT0 + j, x, y - (float)64 * _2X * zoom, 0, zoom);
				break;
			case MAPTYPE_DARKNESS:
				//어둠의 지대 오오라
				j = (robin.playtime + i * 3) % 30;

				if (j < 15)
					DrawBgEffect(BG14_AURORA0 + j, x + (float)42 * _2X * zoom, y - (float)7 * _2X * zoom, 0, zoom);

				j = (robin.playtime + i * 3 + 15) % 30;

				if (j < 15)
					DrawBgEffect(BG14_AURORA0 + j, x + (float)12 * _2X * zoom, y - (float)36 * _2X * zoom, 0, zoom);
				break;
			}

			i++;
		} while (i * *(bgPtr + 2) < rw * TSIZE);
	}

	UnSectionClip(IsOffscreenTarget());

}

void DrawTileDirect(int mapIdx, int x, int yPos, float zoom)
{
	int i = 0, j, y, t;
	int iStart, iEnd, jStart, jEnd;
	const unsigned short* bgPtr;
	const unsigned char* bgPtrChar;
	int tempMap = robinmap;

	ReadMap(mapIdx);

	//원경
	bgPtr = &mapBg[mapData[7] * 4];

	y = yPos + (PLAYAREA_Y + *(bgPtr + 3)) / 2;


	iStart = 0;
	iEnd = rh - 4;
	jStart = 0;
	jEnd = rw - 4;

	switch (mapData[7]) {
	default:
		for (i = 0; i < iEnd; i++) {
			for (j = 0; j < jEnd; j++) {
				y = mapArray[i * mapData[1] + j] - 1;

				if (y >= 0) {
					DrawImage(TSIZE, TSIZE, (y % MAXTILE) * TSIZE, y / MAXTILE * TSIZE, x + (float)TSIZE * j * zoom, yPos + (float)((rh - 4) * TSIZE - TSIZE * i) * zoom, false, false, false, false, false, zoom, sprite[MAP_TILE_IMG + mapData[7]], MAP_TILE_IMG + mapData[7]);
				}
			}
		}
		break;
	case MAPTYPE_FLAME:
		for (i = iStart; i < iEnd; i++) {
			for (j = jStart; j < jEnd; j++) {
				y = mapArray[i * mapData[1] + j] - 1;

				if (y >= 0) {
					if (y < 44)
						t = y;
					else {
						bgPtrChar = &mapInfoArray[mapInfoOff + (i + 1) * rw + j];
						t = (*bgPtrChar == TILE_BLAZE) ? robin.playtime / 4 : robin.playtime;

						if (y >= 62)
							t = (y - (t % 2) * 14);
						else if (y >= 58) {
							if (*bgPtrChar == TILE_BLAZE_RIGHT)
								t = 61 - (y + t * 3) % 4;
							else
								t = 58 + (y + t) % 4;
						}
						else if (y >= 48)
							t = y + (t % 2) * 14;
						else if (y >= 44) {
							if (*bgPtrChar == TILE_BLAZE_RIGHT)
								t = 47 - (y + t * 3) % 4;
							else
								t = 44 + (y + t) % 4;
						}
					}
					DrawImage(TSIZE, TSIZE, (y % MAXTILE) * TSIZE, y / MAXTILE * TSIZE, x + (float)(TSIZE * j) * zoom, yPos + (float)((rh - 4) * TSIZE - TSIZE * i) * zoom, false, false, false, false, false, zoom, sprite[MAP_TILE_IMG + mapData[7]], MAP_TILE_IMG + mapData[7]);

				}
			}
		}
		break;
	}

	DrawBackMapFront(x, yPos, mapIdx, zoom);

	//UnSectionClip(false);

	robinmap = tempMap;
	ReadMap(robinmap);
}

void DrawTile(int mapIdx, int yPos, float zoom)
{
	int i = 0, j, y, t;
	int iStart, iEnd, jStart, jEnd;
	const unsigned short* bgPtr;
	const unsigned char* bgPtrChar;

	SetSectionClip(0, yPos + TILEDY, TILEDX, TILEDY, IsOffscreenTarget());

	//타겟 클리어는 PushRenderTarget(..., true)가 beginWithClear로 처리한다.

	ReadMap(mapIdx);

	//원경
	bgPtr = &mapBg[mapData[7] * 4];

	y = yPos + ((*(bgPtr + 3)) ? (PLAYAREA_Y + *(bgPtr + 3)) / 2 : 0 + *(bgPtr + 1));


	iStart = 0;
	iEnd = rh - 4;
	jStart = 0;
	jEnd = rw - 4;

	switch (mapData[7]) {
	default:
		for (i = 0; i < iEnd; i++) {
			for (j = 0; j < jEnd; j++) {
				y = mapArray[i * mapData[1] + j] - 1;

				if (y >= 0) {
					DrawImage(TSIZE, TSIZE, (y % MAXTILE) * TSIZE, y / MAXTILE * TSIZE, (float)TSIZE * j * zoom, yPos + (float)((rh - 4) * TSIZE - TSIZE * i) * zoom, false, false, false, false, false, zoom, sprite[MAP_TILE_IMG + mapData[7]], MAP_TILE_IMG + mapData[7]);
				}
			}
		}
		break;
	case MAPTYPE_FLAME:
		for (i = iStart; i < iEnd; i++) {
			for (j = jStart; j < jEnd; j++) {
				y = mapArray[i * mapData[1] + j] - 1;

				if (y >= 0) {
					if (y < 44)
						t = y;
					else {
						bgPtrChar = &mapInfoArray[mapInfoOff + (i + 1) * rw + j];
						t = (*bgPtrChar == TILE_BLAZE) ? robin.playtime / 4 : robin.playtime;

						if (y >= 62)
							t = (y - (t % 2) * 14);
						else if (y >= 58) {
							if (*bgPtrChar == TILE_BLAZE_RIGHT)
								t = 61 - (y + t * 3) % 4;
							else
								t = 58 + (y + t) % 4;
						}
						else if (y >= 48)
							t = y + (t % 2) * 14;
						else if (y >= 44) {
							if (*bgPtrChar == TILE_BLAZE_RIGHT)
								t = 47 - (y + t * 3) % 4;
							else
								t = 44 + (y + t) % 4;
						}
					}
					DrawImage(TSIZE, TSIZE, (y % MAXTILE) * TSIZE, y / MAXTILE * TSIZE, (float)TSIZE * j * zoom, yPos + (float)((rh - 4) * TSIZE - TSIZE * i) * zoom, false, false, false, false, false, zoom, sprite[MAP_TILE_IMG + mapData[7]], MAP_TILE_IMG + mapData[7]);

				}
			}
		}
		break;
	}

	UnSectionClip(false);
}

void DrawScreen(int x, int y, float zoom)
{
	int i;
	float dioramaZoomOnScreen = zoom * dioramaZoom;
	int castleX, castleY;
	
	//for (i = 0; i < TOTALCASTLE; i++)
	switch (drawHandle) {
	case MD_DEMO:
	case MD_PLAY:
	case MD_BATTLE:
	case MD_GACHA:

		SetScreenRatio();

		DrawBackMapFar(xOffset + x / TSIZE - (float)DX / 2 * zoom - (frame % DX), y / TSIZE + STATUSWIN_Y - (DIORAMA_GAPY - 0 * _2X) - (SCREENRATIO - 134), MAP_DIORAMA_SPACE, (float)DX * 2 / screenZoom * zoom, zoom);
		robinmap = MAP_DIORAMA_TOLEM + castleOrder[robin.castle];

		// 사용
		castleX = xOffset + (float)DX / 2 * zoom - (float)DIORAMASIZE_X / 2 * dioramaZoomOnScreen;
		castleY = (float)(STATUSWIN_Y - 16 * _2X) * zoom + (float)DIORAMASIZE_Y * dioramaZoomOnScreen;

		// 부유 효과 적용
		floatOffsetY = GetDioramaFloatY(frame);
		castleY += floatOffsetY * zoom;
		//STATUSWIN_Y = STATUSWIN_Y_INIT;
		STATUSWIN_Y += floatOffsetY * zoom;

		//robin.castle = 1;

		DrawDiorama(castleX, castleY, castleOrder[robin.castle], dioramaZoomOnScreen);

		break;
	}

}

void TheaterDraw()
{
	int tempOffX = offX;
	int tempOffY = offY;
	int i;

	return;

	offX = 0;
	offY = 0;
	//본체
	if (curtainFrame == 0)
		DrawImage(525, 707, 0, 0, xOffset + DX / 2 - 525 * _2X / 2, /*DY / 2 + 707 * _2X / 2*/707 * _2X, false, false, false, false, false, 2.0f, sprite[THEATER_IMG], THEATER_IMG);
	else
		ResetRectPoint();

	//이러면 닫는다.
	if (curtainFrame > 0) {
		//왼쪽 커튼
		for (i = 0; i < 3; i++) {
			DrawImage(71, 424, 527, 0, xOffset + DX / 2 - 525 * _2X / 2 + 50 * _2X + curtainPosX[(CURTAINFRAME - curtainFrame) * 3 + i] - CURTAINSTARTPOSX - 64 * _2X, Max(DY / 2 + 707 * _2X / 2 - 16 * _2X - 114 * _2X, DY - 114 * _2X), false, false, false, false, false, 2.0f, sprite[THEATER_IMG], THEATER_IMG);
		}
		//오른쪽 커튼
		for (i = 0; i < 3; i++) {
			DrawImage(71, 424, 527, 0, xOffset + DX / 2 - 525 * _2X / 2 + 404 * _2X - curtainPosX[(CURTAINFRAME - curtainFrame) * 3 + i] + CURTAINSTARTPOSX + 64 * _2X, Max(DY / 2 + 707 * _2X / 2 - 16 * _2X - 114 * _2X, DY - 114 * _2X), true, false, false, false, false, 2.0f, sprite[THEATER_IMG], THEATER_IMG);
		}

		curtainFrame -= CURTAINSPEED;

		if (curtainFrame < 0)
			curtainFrame = 0;
	}
	//이러면 연다.
	else if (curtainFrame < 0) {
		//왼쪽 커튼
		for (i = 0; i < 3; i++) {
			DrawImage(71, 424, 527, 0, xOffset + DX / 2 - 525 * _2X / 2 + 50 * _2X + curtainPosX[Abs(curtainFrame + 1) * 3 + i], Max(DY / 2 + 707 * _2X / 2 - 16 * _2X - 114 * _2X, DY - 114 * _2X), false, false, false, false, false, 2.0f, sprite[THEATER_IMG], THEATER_IMG);
		}

		//오른쪽 커튼
		for (i = 0; i < 3; i++) {
			DrawImage(71, 424, 527, 0, xOffset + DX / 2 - 525 * _2X / 2 + 404 * _2X - curtainPosX[Abs(curtainFrame + 1) * 3 + i], Max(DY / 2 + 707 * _2X / 2 - 16 * _2X - 114 * _2X, DY - 114 * _2X), true, false, false, false, false, 2.0f, sprite[THEATER_IMG], THEATER_IMG);
		}

		curtainFrame += CURTAINSPEED;

		if (curtainFrame > 0)
			curtainFrame = 0;
	}

	//상단 장막
	DrawImage(487, 243, 0, 708, xOffset + DX / 2 - 525 * _2X / 2 + 19 * _2X, Max(DY / 2 + 707 * _2X / 2 - 16 * _2X, DY), false, false, false, false, false, 2.0f, sprite[THEATER_IMG], THEATER_IMG);

	offX = tempOffX;
	offX = tempOffY;
}

// Ease-In-Out 함수 (부드러운 시작과 끝)
float EaseInOutSine(float t)
{
	return -(cos(3.141592f * t) - 1.0f) / 2.0f;
}

// 부드러운 상하 부유 (추천)
float GetDioramaFloatY(int frame)
{
	const int MOVE_TIME = 5 * FPS;    // 5초 이동
	const int PAUSE_TIME = 1 * FPS;   // 1초 정지
	const float RANGE = 20.0f;        // ±20픽셀

	const int TOTAL_CYCLE = (MOVE_TIME + PAUSE_TIME) * 2;  // 12초 주기
	int currentFrame = frame % TOTAL_CYCLE;

	// Ease-In-Out 함수 (부드러운 가속/감속)
	auto EaseInOutSine = [](float t) -> float {
		return -(cosf(3.141592f * t) - 1.0f) / 2.0f;
		};

	float offset = 0.0f;

	if (currentFrame < MOVE_TIME) {
		// 아래 → 위
		float t = (float)currentFrame / (float)MOVE_TIME;
		float eased = EaseInOutSine(t);
		offset = -RANGE + (eased * RANGE * 2.0f);
	}
	else if (currentFrame < MOVE_TIME + PAUSE_TIME) {
		// 최상단 정지
		offset = RANGE;
	}
	else if (currentFrame < MOVE_TIME * 2 + PAUSE_TIME) {
		// 위 → 아래
		int moveFrame = currentFrame - (MOVE_TIME + PAUSE_TIME);
		float t = (float)moveFrame / (float)MOVE_TIME;
		float eased = EaseInOutSine(t);
		offset = RANGE - (eased * RANGE * 2.0f);
	}
	else {
		// 최하단 정지
		offset = -RANGE;
	}

	return offset;
}
