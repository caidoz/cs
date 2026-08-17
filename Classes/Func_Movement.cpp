#include "Core.h"
#include "Func.h"
#include "Data.h"

// Object 이동관련
int PxlLeft(OBJECT* pObj)
{
	return pObj->x + pObj->cpx;
}

int PxlUp(OBJECT* pObj)
{
	return (pObj->y + pObj->cpy);
}

int PxlRight(OBJECT* pObj)
{
	return pObj->x + pObj->cpx + pObj->cx;
}

int PxlDown(OBJECT* pObj)
{
	return (pObj->y + pObj->cpy + pObj->cy);
}

int GetObjIdxFromType(int type, int startIdx, int endIdx)
{
	int i = endIdx;

	do {
		i--;

		if (ao[i].type == type)
			return i;
	} while (i > startIdx);


	return -1;
}

int GetObjFromPtr(OBJECT* pObj)
{
	int i = TOTALOBJECT;


	do {
		i--;

		if (&ao[i] == pObj)
			return i;
	} while (i != 0);


	return -1;
}

int GetSonObjCnt(int mom)
{
	int i;
	int cnt = 0;
	for (i = BULLET; i < ENEMY; i++) {
		if (ao[i].active && !ao[i].dead) {
			cnt++;
		}
	}

	return cnt;
}

void GetTile(OBJECT* pObj)
{
	pObj->tileX1 = PxlLeft(pObj) / TSIZE;
	pObj->tileX2 = (PxlRight(pObj) - 1) / TSIZE;
	pObj->tileY1 = (pObj->y + pObj->cpy) / TSIZE;
	pObj->tileY2 = (PxlDown(pObj) - 1) / TSIZE;
}

int GetDistanceX(OBJECT* obj1, OBJECT* obj2)
{
	int dist = Abs(obj1->x - obj2->x);

	return dist;
}

int GetDistance(OBJECT* obj1, OBJECT* obj2)
{
	int dist = (obj1->x - obj2->x) * (obj1->x - obj2->x) + (obj1->y - obj2->y) * (obj1->y - obj2->y);

	if (dist < 65536)
		return SqrtX256(dist) >> 8;
	else
		return SqrtX256(dist >> 8) >> 4;
}
//거리가 안에 들어오면
int DistanceCheck(OBJECT* obj1, OBJECT* obj2, int dist)
{
	if ((obj1->x - obj2->x) * (obj1->x - obj2->x) + (obj1->y - obj2->y) * (obj1->y - obj2->y) < dist * dist)
		return true;
	else
		return false;
}

int GetClosestObj(OBJECT* pObj)
{
	int i = ENEMY, gap = 10000, closest = 0;

	do {
		if (ao[i].active && !ao[i].dead && pObj != &ao[i]) {
			if (gap > Abs(pObj->x - ao[i].x) + Abs(pObj->y - ao[i].y)) {
				gap = Abs(pObj->x - ao[i].x) + Abs(pObj->y - ao[i].y);
				closest = i;
			}
		}

		i++;
	} while (i < NEUTRAL);

	return closest;
}

int GetClosestPlayer(OBJECT* pObj)
{
	int i = PLAYER, gap = 10000, closest = 0;

	do {
		if (ao[i].active && !ao[i].dead && pObj != &ao[i]) {
			if (gap > Abs(pObj->x - ao[i].x) + Abs(pObj->y - ao[i].y)) {
				gap = Abs(pObj->x - ao[i].x) + Abs(pObj->y - ao[i].y);
				closest = i;
			}
		}

		i++;
	} while (i < TOTALCHAR);

	return closest;
}

int GetRaidAttackFrameCnt(int type)
{
	switch (type) {
	case ROULETTE_RAID_GOOD:
		return ROBIN_ATTACK_RAID_GOOD_CNT;
	case ROULETTE_RAID_PERFECT:
		return ROBIN_ATTACK_RAID_PERFECT_CNT;
	case ROULETTE_RAID_MISS:
		return false;
	}

	return false;
}


int BoundaryCheck(OBJECT* pObj)
{
	if (pObj->x - rx < -TSIZE * 2 || pObj->x - rx > DX + TSIZE * 2 || pObj->y - ry < -TSIZE * 2 || pObj->y - ry > PLAYAREA_Y + TSIZE * 2)
		return true;
	else
		return false;
}

int GetObjHeight(OBJECT* pObj)
{
	int i, j;
	int height = -PxlDown(pObj) % TSIZE;
	int flag;

	//타일과의 거리 측정
	for (i = PxlDown(pObj) / TSIZE; i < rh; i++) {
		flag = 1;
		j = pObj->tileX1;

		do {
			if (mapInfoArray[mapInfoOff + i * rw + j] >= TILE_WATER || (pObj->inTile == GROUND && pObj->onWater > 0 && mapInfoArray[mapInfoOff + i * rw + j] >= TILE_WATER)) {
				flag = 0;
				break;
			}

			j++;
		} while (j <= pObj->tileX2);

		if (flag)
			height += TSIZE;
		else
			break;
	}

	if (pObj->type == OBJ_SPIKE && GetObjFromPtr(pObj) >= NEUTRAL)
		return height;

	//충돌하는 오브젝트와의 거리 측정
	for (i = ENEMY; i < ITEMOBJ; i++) {
		OBJECT* pCompare = &ao[i];

		if (pCompare->active && pCompare->block && pCompare->drawHandler && PxlLeft(pObj) < PxlRight(pCompare) && PxlLeft(pCompare) < PxlRight(pObj)) {
			j = PxlUp(pCompare) - PxlDown(pObj);

			if (j >= 0 && j < height)
				height = j;
		}
	}

	return height;
}

int GetEmptyObject(int start)
{
	int i;

	for (i = start; i < TOTALOBJECT; i++)
		if ((ao[i].active) == false)
			return i;

	return -1;
}

int BlockObj(OBJECT* pObj, int type)
{
	int i;
	int t = (type == 0) ? pObj->dirX : pObj->dirY;
	int ret = (t == RIGHT) ? 0xFFFF : 0;
	int compare;

	for (i = ENEMY; i < ITEMOBJ; i++) {
		OBJECT* pCompare = &ao[i];

		if (pObj != pCompare && pCompare->active && pCompare->block && !pCompare->dead && ObjCrash(pObj, pCompare)) {
			if (type == 0) {
				compare = (pCompare->type == OBJ_SLED) ? pCompare->hp : pCompare->x;

				if (pObj->x < compare) {
					t = RIGHT;

					if (ret == 0)
						ret = 0xFFFF;
				}
				else {
					t = LEFT;

					if (ret == 0xFFFF)
						ret = 0;
				}
			}
			else {
				compare = (pCompare->type == OBJ_SLED) ? pCompare->maxhp : pCompare->y;

				if (pObj->y < compare) {
					t = DOWN;

					if (ret == 0)
						ret = 0xFFFF;
				}
				else if (pObj->y > compare) {
					t = UP;

					if (ret == 0xFFFF)
						ret = 0;
				}
			}

			if (type == 0)
				ret = (t != false) ? Min(ret, PxlLeft(pCompare)) : Max(ret, PxlRight(pCompare));
			else
				ret = (t != false) ? Min(ret, PxlUp(pCompare)) : Max(ret, PxlDown(pCompare));
		}

		if (i < NEUTRAL) {
			//switch (pCompare->type) {
			//	case NPC_SHIP:
			//		pCompare->etc = 1;
			//		break;
			//}
		}
		else {
			switch (pCompare->type) {
			case OBJ_DOOR:
				if (pCompare->status < OPENED && type == 0 && ObjCrash(pObj, pCompare)) {
					// 인벤이 꽉찼고, 강적보스를 물리치는 퀘라면, 문이 열리지 않는다.
					if ((pObj == &ao[PLAYER] && robin.bossRoom == false) || pObj == &ao[DIANA] || pObj == &ao[MAXX]) {
						pCompare->cy++;
						pCompare->status = OPEN;
						pCompare->mainFrame = 1;
					}
				}
				break;
				//밀리는 돌
			case OBJ_PUSH:
				if (type == 0 && pObj->canPush == true && pObj == &ao[PLAYER] && pObj->dirX == pCompare->dirX && pObj->str == 0) {
					pCompare->dx = Min(2, Abs(pObj->dx)) * DIR(pObj->dirX) * _2X;
					pCompare->dirX = pObj->dirX;
				}
				break;
				//마그마블럭
			case OBJ_MAGMABLOCK:
				if (type == 1 && pObj == &ao[PLAYER] && pObj->dirY == DOWN)
					pObj->onTile = TILE_BLOCK;
				break;
				//썰매
			case OBJ_SLED:
				if (pObj->canSled) {
					if (type == 0 && pCompare->etc == 0 && pCompare->dirX == pObj->dirX) {
						//썰매를 먼저 민다.
						pCompare->etc = 1;
						pObj->hp = 0;
					}
					else if (type == 1 && pCompare->etc == 1 && pObj->y < pCompare->y) {
						//썰매가 밀린 상태에서 Y축으로 충돌하면 탄것으로 인식
						pObj->onSled = i;
						pObj->playerRun = false;

						pObj->moveHandler = PLAYERSLEDMOVE;
						pObj->dirX = pCompare->dirX;
						pObj->dx = pCompare->dx;
						pObj->hp = pObj->x - ao[PLAYER].x;
					}
				}
				break;
			}

			if (pObj->type == OBJ_SPIKE && GetObjFromPtr(pObj) >= NEUTRAL && GetObjFromPtr(pObj) < ITEMOBJ) {
				//떨어지는 고드름
				pObj->etc = 2;
				pObj->cx = 0;
			}
		}
	}

	if (ret == false || ret == 0xFFFF)
		return false;
	else {
		if (t == false) {
			if (type == 0)
				return PxlLeft(pObj) - ret;
			else
				return PxlUp(pObj) - ret;
		}
		else {
			if (type == 0)
				return PxlRight(pObj) - ret;
			else
				return PxlDown(pObj) - ret;
		}
	}
}

int ObjCrash(OBJECT* obj1, OBJECT* obj2)
{
	return ((obj1->cx != 0 && obj2->cx != 0 && obj1->cy != 0 && obj2->cy != 0 && PxlLeft(obj1) < PxlRight(obj2) && PxlLeft(obj2) < PxlRight(obj1) && PxlUp(obj1) < PxlDown(obj2) && PxlUp(obj2) < PxlDown(obj1)) ? 1 : 0);
}
//화면기준의 충돌
int ObjCrash2(OBJECT* obj1, OBJECT* obj2)
{
	if ((obj1->x + obj1->cpx + obj1->cx) < obj2->x || obj1->x > (obj2->x + obj2->cpx + obj2->cx))
		return false;

	if ((obj1->y + obj1->cpy + obj1->cy) < obj2->y || obj1->y > (obj2->y + obj2->cpy + obj2->cy))
		return false;

	return true;
}

int PointCrash(OBJECT* obj, int x, int y)
{
#define POINTCRASHSIZE	4

	return ((obj->cx != 0 && obj->cy != 0 && PxlLeft(obj) - POINTCRASHSIZE < x && PxlRight(obj) + POINTCRASHSIZE > x && PxlDown(obj) + POINTCRASHSIZE > y && PxlUp(obj) - POINTCRASHSIZE < y) ? 1 : 0);
}

int AttackCrash(OBJECT* obj1, OBJECT* obj2)
{
	if (obj1->ax == 0 || obj2->cx == 0)
		return false;

	// NPC-GHOST가 INVISI모드일때는 공격받지 않음.
	switch (obj2->type) {
	case ENEMY_GHOST:
	case ENEMY_GHOST_RED:
	case ENEMY_GHOST_BLUE:
	case ENEMY_GHOST_PURPLE:
	case ENEMY_GHOST_GREEN:
	case ENEMY_GHOST_GOLD:
	case ENEMY_GHOST_BLACK:
		if (obj2->etc == GHOST_INVISIBLED || obj2->etc == GHOST_INVISI_MOVE)
			return false;
		break;
	case ENEMY_CASTLE_BOSS3:
	case ENEMY_CASTLE_BOSS3_RED:
	case ENEMY_CASTLE_BOSS3_BLUE:
	case ENEMY_CASTLE_BOSS3_PURPLE:
	case ENEMY_CASTLE_BOSS3_GREEN:
	case ENEMY_CASTLE_BOSS3_GOLD:
	case ENEMY_CASTLE_BOSS3_BLACK:
		if (obj2->moveHandler == ENEMYMOVE && obj2->attack != 3)
			return false;
		break;
	case ENEMY_DEATH:
	case ENEMY_DEATH_RED:
	case ENEMY_DEATH_BLUE:
	case ENEMY_DEATH_PURPLE:
	case ENEMY_DEATH_GREEN:
	case ENEMY_DEATH_GOLD:
	case ENEMY_DEATH_BLACK:
		if (obj2->etc >= DEATH_BREAK_READY && obj2->etc <= DEATH_BROKEN)
			return false;
		break;
	case ENEMY_MACHINE:
	case ENEMY_MACHINE_RED:
	case ENEMY_MACHINE_BLUE:
	case ENEMY_MACHINE_PURPLE:
	case ENEMY_MACHINE_GREEN:
	case ENEMY_MACHINE_GOLD:
	case ENEMY_MACHINE_BLACK:
		if (GetObjFromPtr(obj2) <= ENEMY + 4)
			return false;
		break;
	case ENEMY_SNOWMAN:
	case ENEMY_SNOWMAN_RED:
	case ENEMY_SNOWMAN_BLUE:
	case ENEMY_SNOWMAN_PURPLE:
	case ENEMY_SNOWMAN_GREEN:
	case ENEMY_SNOWMAN_GOLD:
	case ENEMY_SNOWMAN_BLACK:
		if (obj2->etc >= SNOWMAN_HIDE)
			return false;
	case ENEMY_CASTLE_BOSS1:
	case ENEMY_CASTLE_BOSS1_RED:
	case ENEMY_CASTLE_BOSS1_BLUE:
	case ENEMY_CASTLE_BOSS1_PURPLE:
	case ENEMY_CASTLE_BOSS1_GREEN:
	case ENEMY_CASTLE_BOSS1_GOLD:
	case ENEMY_CASTLE_BOSS1_BLACK:
		if (obj2->moveHandler == DEBRIONBODYMOVE && obj2->tileX2 > 0) {
			return false;
		}
		break;
	case ENEMY_SHIP:
	case ENEMY_SHIP_RED:
	case ENEMY_SHIP_BLUE:
	case ENEMY_SHIP_PURPLE:
	case ENEMY_SHIP_GREEN:
	case ENEMY_SHIP_GOLD:
	case ENEMY_SHIP_BLACK:
		if (obj2->moveHandler == SHIPMAINMOVE && !(obj2->status == 0 && (obj2->etc == SHIP_WEAK || obj2->etc == SHIP_WEAKMOVE || obj2->etc == SHIP_LASER || obj2->etc == SHIP_GUIDESHOT))) {
			return false;
		}
		break;
	}

	crX = Max(obj1->x + obj1->apx, PxlLeft(obj2));
	crY = Max(obj1->y + obj1->apy, PxlUp(obj2));
	crW = Min(obj1->x + obj1->apx + obj1->ax, PxlRight(obj2)) - crX;
	//DEATH 몬스터 아랫부분은 맞지 않음.
	if (obj2->type == ENEMY_DEATH)
		crH = Min(obj1->y + obj1->apy + obj1->ay, PxlDown(obj2) - 32 * _2X) - crY;
	else
		crH = Min(obj1->y + obj1->apy + obj1->ay, PxlDown(obj2)) - crY;

	if (crW > 0 && crH > 0) {
		return true;
	}
	else
		return false;
}

int AttackCrash2(OBJECT* obj1, OBJECT* obj2)
{
	if (obj1->ax == 0 || obj2->ax == 0)
		return false;

	crX = Max(obj1->x + obj1->apx, obj2->x + obj2->apx);
	crY = Max(obj1->y + obj1->apy, obj2->y + obj2->apy);
	crW = Min(obj1->x + obj1->apx + obj1->ax, obj2->x + obj2->apx + obj2->ax) - crX;
	crH = Min(obj1->y + obj1->apy + obj1->ay, obj2->y + obj2->apy + obj2->ay) - crY;

	if (crW > 0 && crH > 0)
		return true;
	else
		return false;
}

int TileCrash(OBJECT* pObj)
{
	int i, j;
	int obj = GetObjFromPtr(pObj);

	GetTile(pObj);

	//주인공이면 수면걷기 체크
	if (pObj->inTile == GROUND && pObj->onWater > 2 && pObj == &ao[PLAYER]) {
		for (j = pObj->tileX1; j <= pObj->tileX2; j++) {
			if (mapInfoArray[mapInfoOff + pObj->tileY1 * rw + j] != TILE_SWAMP && mapInfoArray[mapInfoOff + pObj->tileY1 * rw + j] != TILE_WATER && (mapInfoArray[mapInfoOff + pObj->tileY2 * rw + j] == TILE_SWAMP || mapInfoArray[mapInfoOff + pObj->tileY2 * rw + j] == TILE_WATER))
				//막히는 타일
				return 3;
		}
	}

	for (i = pObj->tileY1; i <= pObj->tileY2; i++) {
		for (j = pObj->tileX1; j <= pObj->tileX2; j++)
			if (mapInfoArray[mapInfoOff + i * rw + j] == TILE_BLOCK || mapInfoArray[mapInfoOff + i * rw + j] >= TILE_ICE)
				//막히는 타일
				return 3;
	}

	//아래서 위로는 통과되는 타일
	if ((mapInfoArray[mapInfoOff + pObj->tileY2 * rw + pObj->tileX1] == TILE_DOWN || mapInfoArray[mapInfoOff + pObj->tileY2 * rw + pObj->tileX2] == TILE_DOWN) && mapInfoArray[mapInfoOff + (pObj->tileY2 - 1) * rw + pObj->tileX1] != TILE_DOWN && mapInfoArray[mapInfoOff + (pObj->tileY2 - 1) * rw + pObj->tileX2] != TILE_DOWN)
		return 2;

	for (i = pObj->tileY1; i <= pObj->tileY2; i++) {
		for (j = pObj->tileX1; j <= pObj->tileX2; j++)
			if (mapInfoArray[mapInfoOff + i * rw + j] > TILE_DOWN)
				//계단
				return 1;
	}

	return 0;
}
//TEST
int GetOnTile(OBJECT* pObj)
{
	return TILE_BLOCK;
	/*
	if (mapInfoArray[mapInfoOff + (PxlDown(pObj) / TSIZE) * rw + pObj->tileX1] == TILE_BLOCK || mapInfoArray[mapInfoOff + (PxlDown(pObj) / TSIZE) * rw + pObj->tileX2] == TILE_BLOCK)
		return TILE_BLOCK;
	else
		return Max(mapInfoArray[mapInfoOff + (PxlDown(pObj) / TSIZE) * rw + pObj->tileX1], mapInfoArray[mapInfoOff + (PxlDown(pObj) / TSIZE) * rw + pObj->tileX2]);
	*/
}

int ClearGap(OBJECT* pObj, int type)
{
	if (type == 0) {
		if (pObj->dirX == LEFT) {
			if (PxlLeft(pObj) % TSIZE != 0)
				return -(PxlLeft(pObj) % TSIZE);
		}
		else {
			if (PxlRight(pObj) % TSIZE != 0)
				return (TSIZE - PxlRight(pObj) % TSIZE);
		}
	}
	else {
		if (pObj->dirY == UP) {
			if ((pObj->y + pObj->cpy) % TSIZE != 0)
				return -((pObj->y + pObj->cpy) % TSIZE);
		}
		else {
			if (PxlDown(pObj) % TSIZE != 0)
				return (TSIZE - PxlDown(pObj) % TSIZE);
		}
	}

	return false;
}

void PressObjCheck(OBJECT* pObj)
{
	int i;

	for (i = PLAYER; i < TOTALOBJECT; i++) {
		OBJECT* pLoop = &ao[i];

		if (pLoop->active && !pLoop->dead && pObj != pLoop && pLoop->moveHandler < BULLET3WAYMOVE) {
			if (ObjCrash(pObj, pLoop) == false) {
				pObj->y--;

				if (ObjCrash(pObj, pLoop)) {
					pLoop->x += pObj->dx;

					if (TileCrash(pLoop)) {
						pLoop->x -= pObj->dx;
						pLoop->dirX = (pObj->dx > 0) ? RIGHT : LEFT;
						pLoop->x += ClearGap(pLoop, 0);
						pObj->y++;

						if (ObjCrash(pObj, pLoop)) {
							pObj->x -= pObj->dx;
							pObj->dirX = 1 - pObj->dirX;
						}

						pObj->y--;
					}

					if (pLoop->status == FALL && pLoop->y + pLoop->cy < pLoop->y)
						pLoop->status = WALK;
				}

				pObj->y++;
			}
		}
	}
}


void MoveBG(void)
{
	int i;

	for (i = 0; i < TOTALHITMARK; i++) {
		if (hitMark[i].frame > 0) {
			hitMark[i].frame++;

			if (hitMark[i].frame == hitMarkData[hitMark[i].type * 3 + 2]) {
				memset(&hitMark[i], 0, sizeof(HITMARK));
			}
		}
	}

	//대미지 숫자
	for (i = 0; i < TOTALHITMARK; i++) {
		if (dmgInfo[i].type > 0) {
			dmgInfo[i].y += dmgInfoData[dmgInfo[i].frame];
			dmgInfo[i].frame++;

			if (dmgInfo[i].frame == DMGNUMFRAME - 1)
				memset(&dmgInfo[i], 0, sizeof(DMGINFO));

		}
	}

	//상태 글자 이미지
	for (i = 0; i < TOTALHITMARK; i++) {
		if (imgText[i].type) {
			imgText[i].frame++;

			if (imgText[i].type == EFFECT_TEXT_UP)
				imgText[i].type = 0;

			//if (imgText[i].frame > 7) {
			//	imgText[i].y -= 3;

			if (imgText[i].frame == IMGTEXTFRAME)
				imgText[i].type = 0;
			//}
		}
	}

	if (splash.frame)
		splash.frame--;

	//겹쳐진 아이템 프레임
	if (itemFrame > 0)
		itemFrame--;

	if (fadeFrame > 0)
		fadeFrame--;
	else if (fadeFrame < 0)
		fadeFrame++;

	i = 0;

	switch (mapData[7]) {
	case MAPTYPE_SWAMP:
		//안개 흘려주기
		do {
			if (bgObj[i].active) {
				bgObj[i].x += bgObj[i].dx;

				if (bgObj[i].dx < 0 && bgObj[i].x < -200 * _2X)
					bgObj[i].x += rw * TSIZE + 200 * _2X;
				else if (bgObj[i].dx > 0 && bgObj[i].x > rw * TSIZE)
					bgObj[i].x -= (rw * TSIZE + 200 * _2X);
			}
			else
				break;

			i++;
		} while (i < MAXBGOBJECT);
		break;
	case MAPTYPE_ATLANTICE:
		//수중효과
		if (mapData[4] && frame % 2 == 0)
			ProcessWave();

		//물고기 움직여주기
		do {
			if (bgObj[i].active) {
				bgObj[i].x += bgObj[i].dx;

				if (bgObj[i].dx < 0 && bgObj[i].x < -30 * _2X)
					bgObj[i].x += rw * TSIZE + 30 * _2X;
				else if (bgObj[i].dx > 0 && bgObj[i].x > rw * TSIZE + 30 * _2X)
					bgObj[i].x -= (rw * TSIZE + 30 * _2X);
			}
			else
				break;

			i++;
		} while (i < MAXBGOBJECT);
		break;
	case MAPTYPE_PLAIN:
		//나비 움직여주기
		do {
			if (bgObj[i].active) {
				bgObj[i].x += bgObj[i].dx;
				bgObj[i].y += signCurve[(robin.playtime + i) % 16];

				if (bgObj[i].dx < 0 && bgObj[i].x < -30 * _2X)
					bgObj[i].x += rw * TSIZE + 30 * _2X;
				else if (bgObj[i].dx > 0 && bgObj[i].x > rw * TSIZE + 30 * _2X)
					bgObj[i].x -= (rw * TSIZE + 30 * _2X);
			}
			else
				break;

			i++;
		} while (i < MAXBGOBJECT);
	case MAPTYPE_TOLEM:
	case MAPTYPE_VALLEY:
	case MAPTYPE_ELF:
	case MAPTYPE_LIGHT:
		break;
	case MAPTYPE_CASTLE:
	case MAPTYPE_FROST:
		//수중효과
		if (mapData[4] && frame % 2 == 0)
			ProcessWave();
		break;
	case MAPTYPE_GOLEMVALLEY:
		//구름 흘려주기
		do {
			if (bgObj[i].active) {
				if (bgObj[i].etc >= 10) {
					bgObj[i].y += bgObj[i].dx;

					if (bgObj[i].y > DY)
						bgObj[i].active = false;
				}
				else {
					bgObj[i].x += bgObj[i].dx;

					if (bgObj[i].dx < 0 && bgObj[i].x < -200 * _2X)
						bgObj[i].x += rw * TSIZE + 200 * _2X;
				}
			}

			i++;
		} while (i < MAXBGOBJECT);

		//땅 흔들어주기
		if (robin.playtime % 100 == 50) {
			//EffectSound(M_KUNG);
			effect.shake = 4;

			for (i = 0; i < 4; i++) {
				bgObj[MAXBGOBJECT - 1 - i].active = true;
				bgObj[MAXBGOBJECT - 1 - i].x = -40 * _2X + Random(DX + 80 * _2X);
				bgObj[MAXBGOBJECT - 1 - i].y = -10 * _2X - Random(70) * _2X;
				bgObj[MAXBGOBJECT - 1 - i].etc = 10 + Random(4);
				bgObj[MAXBGOBJECT - 1 - i].dx = 13 * _2X + Random(7) * _2X;
			}
		}
		break;
	case MAPTYPE_GHOST:
		//망자의 도시 구름 및 안개
		do {
			if (bgObj[i].active) {
				switch (bgObj[i].etc) {
				case 0:
					if (robin.playtime % 10 == 0)
						bgObj[i].x += UpDiv(bgObj[i].dx, 3 * _2X);
					break;
				case 1:
				case 2:
					bgObj[i].x += bgObj[i].dx;

					if (bgObj[i].dx < 0 && bgObj[i].x < -200 * _2X)
						bgObj[i].x += rw * TSIZE + 200 * _2X;
					else if (bgObj[i].dx > 0 && bgObj[i].x > rw * TSIZE)
						bgObj[i].x -= (rw * TSIZE + 200 * _2X);
					break;
				}
			}
			else
				break;

			i++;
		} while (i < MAXBGOBJECT);
		break;
	case MAPTYPE_SPACE:
		//우주 위성
		do {
			if (bgObj[i].active) {
				if (bgObj[i].etc < 3) {
					bgObj[i].x += bgObj[i].dx;

					if (robin.playtime % 8 == 0)
						bgObj[i].y += DIR(Random(2));

					if (bgObj[i].dx < 0 && bgObj[i].x < -100 * _2X)
						bgObj[i].x += rw * TSIZE + 100 * _2X;
					else if (bgObj[i].dx > 0 && bgObj[i].x > rw * TSIZE)
						bgObj[i].x -= (rw * TSIZE + 100 * _2X);
				}
				else {
					bgObj[i].x -= bgObj[i].dx;
					bgObj[i].y += bgObj[i].dx;

					if (bgObj[i].y - ry > DY + 50 * _2X)
						bgObj[i].active = false;
				}
			}

			i++;
		} while (i < MAXBGOBJECT);

		//우주 유성
		if (!Random(4)) {
			for (i = MAXBGOBJECT / 2; i < MAXBGOBJECT; i++) {
				if (bgObj[i].active == false) {
					bgObj[i].active = true;
					bgObj[i].y = 10 * _2X + Random(100) * _2X;
					bgObj[i].x = bgObj[i].y + Random(DX * 2 - 48 * _2X);
					bgObj[i].etc = Random(2) + 3;
					bgObj[i].dx = (bgObj[i].etc == 3) ? 12 * _2X + Random(12) * _2X : 8 * _2X + Random(8) * _2X;
					break;
				}
			}
		}
		break;
	}
}

void MoveObj(OBJECT* pObj)
{
	int obj = GetObjFromPtr(pObj);
	int i;
	int tempSystemKey = systemKey;

	if (pObj->invincible)
		pObj->invincible--;

	if (obj < ITEMOBJ) {
		//타격효과
		if (pObj->attackedFrame > 0) {
			pObj->attackedFrame--;

			if (pObj->attackedFrame == 0)
				pObj->attacked = false;
		}

		//디버프 처리
		if (pObj->dead == false) {
			if (pObj->debuf[SLOW])
				pObj->debuf[SLOW]--;

			if (pObj->debuf[POISON]) {
				pObj->debuf[POISON]--;

				if (pObj->debuf[POISON] % FPS == 1) {
					//주인공 캐릭터가 중독이 되었을 때
					if (obj < PLAYERALL) {
						AttackRobin(ATTACKTYPE_POISON, obj);
					}
					else {
						//몬스터가 중독이 되었을 때
						AttackObj(ATTACKTYPE_POISON, obj);
					}
				}
			}

			if (pObj->debuf[BLIND]) {
				pObj->debuf[BLIND]--;
			}

			if (pObj->debuf[CURSE])
				pObj->debuf[CURSE]--;

			if (obj >= PLAYERALL) {
				if (pObj->debuf[STUN]) {
					pObj->debuf[STUN]--;
					pObj->attack = false;
					effect.alpha = 0;

					// 스턴몬스터 여기서걸리는것이 아님
					switch (pObj->type) {
					case ENEMY_SLIME:
					case ENEMY_SLIME_RED:
					case ENEMY_SLIME_BLUE:
					case ENEMY_SLIME_PURPLE:
					case ENEMY_SLIME_GREEN:
					case ENEMY_SLIME_GOLD:
					case ENEMY_SLIME_BLACK:
					case ENEMY_DARKDRAGON:
					case ENEMY_DARKDRAGON_RED:
					case ENEMY_DARKDRAGON_BLUE:
					case ENEMY_DARKDRAGON_PURPLE:
					case ENEMY_DARKDRAGON_GREEN:
					case ENEMY_DARKDRAGON_GOLD:
					case ENEMY_DARKDRAGON_BLACK:
					case ENEMY_ONEEYE:
					case ENEMY_ONEEYE_RED:
					case ENEMY_ONEEYE_BLUE:
					case ENEMY_ONEEYE_PURPLE:
					case ENEMY_ONEEYE_GREEN:
					case ENEMY_ONEEYE_GOLD:
					case ENEMY_ONEEYE_BLACK:
					case ENEMY_FROG:
					case ENEMY_FROG_RED:
					case ENEMY_FROG_BLUE:
					case ENEMY_FROG_PURPLE:
					case ENEMY_FROG_GREEN:
					case ENEMY_FROG_GOLD:
					case ENEMY_FROG_BLACK:
					case ENEMY_GIANT:
					case ENEMY_GIANT_RED:
					case ENEMY_GIANT_BLUE:
					case ENEMY_GIANT_PURPLE:
					case ENEMY_GIANT_GREEN:
					case ENEMY_GIANT_GOLD:
					case ENEMY_GIANT_BLACK:
					case ENEMY_PHOENIX:
					case ENEMY_PHOENIX_RED:
					case ENEMY_PHOENIX_BLUE:
					case ENEMY_PHOENIX_PURPLE:
					case ENEMY_PHOENIX_GREEN:
					case ENEMY_PHOENIX_GOLD:
					case ENEMY_PHOENIX_BLACK:
					case ENEMY_IFRIT:
					case ENEMY_IFRIT_RED:
					case ENEMY_IFRIT_BLUE:
					case ENEMY_IFRIT_PURPLE:
					case ENEMY_IFRIT_GREEN:
					case ENEMY_IFRIT_GOLD:
					case ENEMY_IFRIT_BLACK:
					case ENEMY_MAMMOTH:
					case ENEMY_MAMMOTH_RED:
					case ENEMY_MAMMOTH_BLUE:
					case ENEMY_MAMMOTH_PURPLE:
					case ENEMY_MAMMOTH_GREEN:
					case ENEMY_MAMMOTH_GOLD:
					case ENEMY_MAMMOTH_BLACK:
					case ENEMY_ANGEL:
					case ENEMY_ANGEL_RED:
					case ENEMY_ANGEL_BLUE:
					case ENEMY_ANGEL_PURPLE:
					case ENEMY_ANGEL_GREEN:
					case ENEMY_ANGEL_GOLD:
					case ENEMY_ANGEL_BLACK:
					case ENEMY_ICESUN:
					case ENEMY_ICESUN_RED:
					case ENEMY_ICESUN_BLUE:
					case ENEMY_ICESUN_PURPLE:
					case ENEMY_ICESUN_GREEN:
					case ENEMY_ICESUN_GOLD:
					case ENEMY_ICESUN_BLACK:
					case ENEMY_LIGHTNING:
					case ENEMY_LIGHTNING_RED:
					case ENEMY_LIGHTNING_BLUE:
					case ENEMY_LIGHTNING_PURPLE:
					case ENEMY_LIGHTNING_GREEN:
					case ENEMY_LIGHTNING_GOLD:
					case ENEMY_LIGHTNING_BLACK:
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
					case ENEMY_CASTLE2:
					case ENEMY_CASTLE2_RED:
					case ENEMY_CASTLE2_BLUE:
					case ENEMY_CASTLE2_PURPLE:
					case ENEMY_CASTLE2_GREEN:
					case ENEMY_CASTLE2_GOLD:
					case ENEMY_CASTLE2_BLACK:
					case ENEMY_SPACE1:
					case ENEMY_SPACE1_RED:
					case ENEMY_SPACE1_BLUE:
					case ENEMY_SPACE1_PURPLE:
					case ENEMY_SPACE1_GREEN:
					case ENEMY_SPACE1_GOLD:
					case ENEMY_SPACE1_BLACK:
					case ENEMY_KIMERA:
					case ENEMY_KIMERA_RED:
					case ENEMY_KIMERA_BLUE:
					case ENEMY_KIMERA_PURPLE:
					case ENEMY_KIMERA_GREEN:
					case ENEMY_KIMERA_GOLD:
					case ENEMY_KIMERA_BLACK:
					case ENEMY_SHIP:
					case ENEMY_SHIP_RED:
					case ENEMY_SHIP_BLUE:
					case ENEMY_SHIP_PURPLE:
					case ENEMY_SHIP_GREEN:
					case ENEMY_SHIP_GOLD:
					case ENEMY_SHIP_BLACK:
					case ENEMY_FOGRA:
					case ENEMY_FOGRA_RED:
					case ENEMY_FOGRA_BLUE:
					case ENEMY_FOGRA_PURPLE:
					case ENEMY_FOGRA_GREEN:
					case ENEMY_FOGRA_GOLD:
					case ENEMY_FOGRA_BLACK:
					case ENEMY_DEATH:
					case ENEMY_DEATH_RED:
					case ENEMY_DEATH_BLUE:
					case ENEMY_DEATH_PURPLE:
					case ENEMY_DEATH_GREEN:
					case ENEMY_DEATH_GOLD:
					case ENEMY_DEATH_BLACK:
					case ENEMY_CASTLE_BOSS1:
					case ENEMY_CASTLE_BOSS1_RED:
					case ENEMY_CASTLE_BOSS1_BLUE:
					case ENEMY_CASTLE_BOSS1_PURPLE:
					case ENEMY_CASTLE_BOSS1_GREEN:
					case ENEMY_CASTLE_BOSS1_GOLD:
					case ENEMY_CASTLE_BOSS1_BLACK:
					case ENEMY_CASTLE_BOSS2:
					case ENEMY_CASTLE_BOSS2_RED:
					case ENEMY_CASTLE_BOSS2_BLUE:
					case ENEMY_CASTLE_BOSS2_PURPLE:
					case ENEMY_CASTLE_BOSS2_GREEN:
					case ENEMY_CASTLE_BOSS2_GOLD:
					case ENEMY_CASTLE_BOSS2_BLACK:
					case ENEMY_CASTLE_BOSS3:
					case ENEMY_CASTLE_BOSS3_RED:
					case ENEMY_CASTLE_BOSS3_BLUE:
					case ENEMY_CASTLE_BOSS3_PURPLE:
					case ENEMY_CASTLE_BOSS3_GREEN:
					case ENEMY_CASTLE_BOSS3_GOLD:
					case ENEMY_CASTLE_BOSS3_BLACK:
					case ENEMY_CASTLE_BOSS4:
					case ENEMY_CASTLE_BOSS4_RED:
					case ENEMY_CASTLE_BOSS4_BLUE:
					case ENEMY_CASTLE_BOSS4_PURPLE:
					case ENEMY_CASTLE_BOSS4_GREEN:
					case ENEMY_CASTLE_BOSS4_GOLD:
					case ENEMY_CASTLE_BOSS4_BLACK:
						break;
					default:
						pObj->etc = 0;	//@@ 위험소지 있음. 스턴걸리면 안되는 몬스터 예외처리 필요할듯?
						break;
					}

					if (!pObj->debuf[KNOCKBACK]) {
						pObj->dx = 0;
						EnemyMoveCommon(pObj);
						goto NEXT;
					}
				}

				if (pObj->debuf[KNOCKBACK]) {

					pObj->attack = false;
					switch (IsKnockBack(pObj->type)) {
					case SMALLMONSTER:
						pObj->dx = -DIR(pObj->dirF) * 4 * _2X;// * (pObj->debuf[KNOCKBACK]) * (pObj->debuf[KNOCKBACK]);
						break;
					case BIGMONSTER:
						pObj->dx = -DIR(pObj->dirF) * (pObj->debuf[KNOCKBACK] * pObj->debuf[KNOCKBACK] * pObj->debuf[KNOCKBACK]) / 512;
						//if (pObj->dx > TSIZE)
						//	pObj->dx = TSIZE;
						break;
					case GIANTMONSTER:
						pObj->dx = 0;
						break;
					}

					if (pObj->debuf[KNOCKBACK] < KNOCKBACK_DELAY) {
						pObj->dx = 0;

						//if (pObj->dirF == 1) {
						//	if (pObj->dx >= 0) {
						//		pObj->dx = 0;
						//	}
						//}
						//else {
						//	if (pObj->dx <= 0) {
						//		pObj->dx = 0;
						//	}
						//}
					}

					if (pObj->debuf[KNOCKBACK] == KNOCKBACK_START_FRAME && IsKnockBack(pObj->type) == SMALLMONSTER) {
						pObj->status = JUMP;
						pObj->jumpFrame = 0;
					}
					pObj->attacked = true;
					pObj->attackedFrame = ATTACKEDFRAME;
#ifdef ATTACKEDINVINCIBLE
					pObj->invincible = ATTACKEDFRAME;
#endif
					effect.alpha = 0;
					EnemyMoveCommon(pObj);
					pObj->frame--;
					pObj->debuf[KNOCKBACK]--;

					if (pObj->debuf[KNOCKBACK] == 1)
						pObj->debuf[KNOCKBACK] = 0;

					goto NEXT;
				}
			}
			else {
				int i, refresh = 0;

				//워프 효과
				if (returnFrame) {
					returnFrame++;

					switch (returnFrame) {
					case 7:
						GetTile(pObj);
						SetRoom();
						break;
					case 13:
					case 25:
					case 37:
						returnFrame = 0;

						if (isDemo == false)
							GotoPlay();
						break;
					case 19:
						robinmap = 115;
						pObj->x = 72 * _2X;
						pObj->y = 256 * _2X;
						GetTile(pObj);
						SetRoom();
						break;
					case 31:
						robinmap = 109 * _2X;
						pObj->x = 184 * _2X;
						pObj->y = 256 * _2X;
						GetTile(pObj);
						SetRoom();
						break;
					}
				}

				//레벨업 효과
				if (pObj->levelUpFrame) {
					pObj->levelUpFrame++;

					if (pObj->levelUpFrame == 20)
						pObj->levelUpFrame = 0;
				}

				//스탯업 효과
				if (pObj->statUpFrame) {
					pObj->statUpFrame++;

					if (pObj->statUpFrame == 20)
						pObj->statUpFrame = 0;
				}

				//마나회복효과
				if (pObj->mpRestore) {
					pObj->mpRestore++;

					if (pObj->mpRestore >= 12)
						pObj->mpRestore = 0;
				}

				//체력회복효과
				if (pObj->hpRestore) {
					pObj->hpRestore++;

					if (pObj->hpRestore >= 12)
						pObj->hpRestore = 0;
				}

				//상태이상회복효과
				if (pObj->statusRestore) {
					pObj->statusRestore++;

					if (pObj->statusRestore >= 12)
						pObj->statusRestore = 0;
				}

				//마나흡수효과
				if (pObj->mpDrain) {
					pObj->mpDrain++;

					if (pObj->mpDrain >= 6)
						pObj->mpDrain = 0;
				}

				//체력흡수 효과
				if (pObj->hpDrain) {
					pObj->hpDrain++;

					if (pObj->hpDrain >= 6)
						pObj->hpDrain = 0;
				}

				if (!isDemo) {
					//for (i = 0; i < TOTALPLAYERBUFF; i++) {
					for (i = 0; i < TOTALBUFF; i++) {
						if (pObj->buff[i] > 0) {
							pObj->buff[i]--;

							if (pObj->buff[i] == 0)
								refresh = 1;
						}
					}
				}

				if (refresh)
					RefreshStat(pObj);
			}
		}

		if (obj < PLAYERALL && pObj->canMagma == false) {
			//용암 밀리기
			if (mapData[7] == MAPTYPE_FLAME && pObj->onTile >= TILE_BLAZE) {
				int dirX = pObj->dirX;

				if (pObj->onTile == TILE_BLAZE_LEFT) {
					pObj->x -= 4;
					pObj->dirX = LEFT;

					if (TileCrash(pObj)) {
						pObj->x += 4;
						pObj->x += ClearGap(pObj, 0);
					}
				}
				else if (pObj->onTile == TILE_BLAZE_RIGHT) {
					pObj->x += 4;
					pObj->dirX = RIGHT;

					if (TileCrash(pObj)) {
						pObj->x -= 4;
						pObj->x += ClearGap(pObj, 0);
					}
				}

				pObj->dirX = dirX;
			}
		}
	}

	switch (pObj->moveHandler) {
	case PLAYERMOVE:
		if (drawHandle == MD_PLAY) {
			//AI캐릭터
			if (pObj->dead == false && waveStatus == WAVESTATUS_PLAY)
				TargetEnemy(obj);
			else
				pObj->pressedKey[0] = NULL;

			systemKey = pObj->pressedKey[0];
			key_released = pObj->released;

			if (systemKey)
				key_released = false;
		}

		PlayerMove(pObj);

		systemKey = tempSystemKey;
		break;
	case PLAYERSLEDMOVE:
		PlayerSledMove(pObj);
		break;
	case PLAYERGOLEMMOVE:
		PlayerGolemMove(pObj);
		break;
	case PLAYERHANDMOVE:
		PlayerHandMove(pObj);
		break;
	case PLAYERENEMYMOVE://적몬스터를 아군으로 쓸 때
		PlayerEnemyMove(pObj);
		break;
	case ENEMYMOVE:
		EnemyMove(pObj);
		break;
	case ENEMYMOVETURN:
		EnemyMoveTurn(pObj);
		break;
	case SUMMONMOVE:
		SummonMove(pObj);
		break;
	case ENEMYPLAYERMOVE://히어로를 적군으로 쓸 때
		//AI캐릭터
		if (pObj->dead == false)
			TargetPlayer(obj);
		else
			pObj->pressedKey[0] = NULL;

		systemKey = pObj->pressedKey[0];
		key_released = pObj->released;

		if (systemKey)
			key_released = false;
		EnemyPlayerMove(pObj);
		break;
	case MOBIUSMOVE:
		MobiusMove(pObj);
		break;
	case DEMOMOVE:
		DemoMove(pObj);
		break;
	case MERCHANTMOVE:
		MerchantMove(pObj);
		break;
	case NPCMOVE:
		NpcMove(pObj);
		break;
	case NPCSHIPMOVE:
		NpcShipMove(pObj);
		break;
	case CREWMOVE:
		CrewMove(pObj);
		break;
	case CUTOFFMOVE:
		CutOffMove(pObj);
		break;
	case SLINGMOVE:
		SlingMove(pObj);
		break;
	case LIGHTNINGMOVE:
		LightningMove(pObj, 4 * _2X);
		break;
	case BUGMOVE:
		BugMove(pObj);
		break;
	case SKELGUIDEMOVE:
		SkelGuideMove(pObj);
		break;
	case CIRCLEMOVE:
		CircleMove(pObj);
		break;
	case SLIMEMOVE:
		SlimeMove(pObj, 4);
		break;
	case STRAIGHTMOVE:
		StraightMove(pObj);
		break;
	case MACHINEMANAGERMOVE:
		MachineManagerMove(pObj);
		break;
	case MACHINEMOVE:
		MachineMove(pObj);
		break;
	case MACHINEBOSSMOVE:
		MachineBossMove(pObj);
		break;
	case BAHAMUTHEADMOVE:
		BahamutHeadMove(pObj);
		break;
	case BAHAMUTNECKMOVE:
		BahamutNeckMove(pObj);
		break;
	case BAHAMUTBODYMOVE:
		BahamutBodyMove(pObj);
		break;
	case SHIPMAINMOVE:
		ShipMainMove(pObj);
		break;
	case SHIPSUBMOVE:
		ShipSubMove(pObj);
		break;
	case DEBRIONBODYMOVE:
		DebrionBodyMove(pObj);
		break;
	case DEBRIONARMMOVE:
		DebrionArmMove(pObj);
		break;
	case SHIPGUIDEMOVE:
		ShipGuideMove(pObj);
		break;
	case FOGRAMOVE:
		FograMove(pObj);
		break;
	case FOGRASUBMOVE:
		FograSubMove(pObj, &ao[pObj->mom]);
		break;
	case SIGNMOVE:
		SignMove(pObj);
		break;
	case GUARDMOVE:
		GuardMove(pObj);
		break;
	case GOLIMOVE:
		GoliMove(pObj);
		break;
	case GUARDMOVE2:
		GuardMove2(pObj);
		break;
	case APPEARBOSSMOVE:
		AppearBossMove(pObj);
		break;
	case BOAREVENTMOVE:
		BoarEventMove(pObj);
		break;
	case BULLET3WAYMOVE:
		Bullet3wayMove(pObj);
		break;
	case BULLETLASERMOVE:
		BulletLaserMove(pObj);
		break;
	case BULLETBOMBMOVE:
		BulletBombMove(pObj);
		break;
	case BULLETGUIDEDMOVE:
		BulletGuidedMove(pObj);
		break;
	case BULLETSATELLITEMOVE:
		BulletSateliteMove(pObj);
		break;
	case BULLETHEALMOVE:
		BulletHealMove(pObj);
		break;
	case BULLETBOOMERANGMOVE:
		BulletBoomerangMove(pObj);
		break;
	case BULLETTONGUEMOVE:
		BulletTongueMove(pObj);
		break;
	case FOLLOWMOMMOVE:
		FollowMomMove(pObj);
		break;
	case HANDMOVE:
		HandMove(pObj);
		break;
	case BULLETSPINMOVE:
		BulletSpinMove(pObj);
		break;
	case BULLETGUIDEMOVE:
		BulletGuideMove(pObj);
		break;
	case BULLET3WAYDIRMOVE:
		Bullet3wayDirMove(pObj);
		break;
	case BULLETITEMMOVE:
		BulletItemMove(pObj);
		break;
	case BULLET4WAYMOVE:
		Bullet4wayMove(pObj);
		break;
	case LABETHMAGICMOVE:
		LabethMagicMove(pObj);
		break;
	case VANISHMOVE:
		VanishMove(pObj);
		break;
	case REGENMOVE:
		RegenMove(pObj);
		break;
	case SIDEMOVE:
		SideMove(pObj);
		break;
	case UPDOWNMOVE:
		UpDownMove(pObj);
		break;
	case DROPMOVE:
		DropMove(pObj);
		break;
	case SEWAGESTONEMOVE:
		SewageStoneMove(pObj);
		break;
	case DOORMOVE:
		DoorMove(pObj);
		break;
	case REPULSIONMOVE:
		RepulsionMove(pObj);
		break;
	case ITEMMOVE:
		ItemMove(pObj);
		break;
	case CLOAKINGMOVE:
		CloakingMove(pObj);
		break;
	case WARPMOVE:
		WarpMove(pObj);
		break;
	case LEVERMOVE:
		LeverMove(pObj);
		break;
	case PUSHMOVE:
		PushMove(pObj);
		break;
	case BOXMOVE:
		BoxMove(pObj);
		break;
	case CARPETMOVE:
		CarpetMove(pObj);
		break;
	case ROBINTRAPMOVE:
		RobinTrapMove(pObj);
		break;
	case DIANATRAPMOVE:
		DianaTrapMove(pObj);
		break;
	case MAXXTRAPMOVE:
		MaxxTrapMove(pObj);
		break;
	case DIANASTONEMOVE:
		DianaStoneMove(pObj);
		break;
	case SUNBLOCKMOVE:
		SunBlockMove(pObj);
		break;
	case BREAKSTONEMOVE:
		BreakStoneMove(pObj);
		break;
	case DARKSTONEMOVE:
		DarkStoneMove(pObj);
		break;
	case DEMODARKMOVE:
		DemoDarkMove(pObj);
		break;
	case BUBBLEMOVE:
		BubbleMove(pObj);
		break;
	case BUBBLEBOBBLEMOVE:
		BubbleBobbleMove(pObj);
		break;
	case MAGMAMOVE:
		MagmaMove(pObj);
		break;
	case MAGMABLOCKMOVE:
		MagmaBlockMove(pObj);
		break;
	case BRIDGEMOVE:
		BridgeMove(pObj);
		break;
	case STALACTITEMOVE:
		StalactiteMove(pObj);
		break;
	case SPIKEMOVE:
		SpikeMove(pObj);
		break;
	case MAGNETMOVE:
		MagnetMove(pObj);
		break;
	case SLEDMOVE:
		SledMove(pObj);
		break;
	case ICEBREAKMOVE:
		IceBreakMove(pObj);
		break;
	case INVISIBLEMOVE:
		InvisibleMove(pObj);
		break;
	case GOLEMBLOCKMOVE:
		GolemBlockMove(pObj);
		break;
	case BALLMOVE:
		BallMove(pObj);
		break;
	case PITCHERMOVE:
		PitcherMove(pObj);
		break;
	case BLACKHOLEMOVE:
		BlackHoleMove(pObj);
		break;
	case WORMHOLEMOVE:
		WormHoleMove(pObj);
		break;
	case ITEMGOTOBOXMOVE:
		ItemGotoBoxMove(pObj);
		break;
	case FOLLOWMOVE:
		FollowMove(pObj);
		break;
	case TREEMOVE:
		//pObj->motion = OBJ_TREE0 + (frame % FPS);
		break;
	}


	if (obj < SOLDIER + MAXENEMYOBJ) {
		if (pObj->moveHandler == PLAYERMOVE) {
			SetPlayerMotion(pObj);
		}

		if (pObj->ax > 0) {
			if ((pObj->attack >= ATTACK_NORMAL && pObj->attack != ATTACK_DASH) || (pObj->attack == ATTACK_NORMAL && ((pObj->cmf == ROBIN && pObj->attackFrame == 20 + ROBIN_ATTACK_DELAY) || (pObj->cmf == DIANA && pObj->attackFrame == 46 + DIANA_ATTACK_DELAY))))
				pObj->attackLv = 2;
			else
				pObj->attackLv = 1;
		}
		else
			pObj->attackLv = 0;

		if (!attackDelay) {
			AttackEnemyCheck(obj);
			AttackPlayerCheck(pObj);
			//@@ 아이템을 닿아서 주는건 없는것으로 한다.
			//ItemCheck(pObj);
		}

		//수중 거품
		{
			int i;
			signed short* bbPtr = bubbleXY;
			unsigned char mapInfo;

			for (i = 0; i < 6; i++, bbPtr += 2) {
				if (*bbPtr || *(bbPtr + 1)) {
					*bbPtr += (Random(5) - 2);
					*(bbPtr + 1) -= 4;

					mapInfo = mapInfoArray[mapInfoOff + (*(bbPtr + 1) >> 5) * rw + (*bbPtr >> 5)];

					if (mapInfo != TILE_WATER && mapInfo != TILE_SWAMP) {
						*bbPtr = 0;
						*(bbPtr + 1) = 0;
					}
				}
			}

			if (pObj->dead == false && (pObj->inTile == WATER || pObj->inTile == SWAMP)) {
				if (robin.playtime % 8 == 0) {
					bbPtr = bubbleXY;

					for (i = 0; i < 6; i++) {
						if (*bbPtr == 0 && *(bbPtr + 1) == 0) {
							*bbPtr = pObj->x + DIR(pObj->dirF) * 8;
							*(bbPtr + 1) = pObj->y - 12 * _2X;
							break;
						}
					}
				}
			}
		}
	}

	if (obj >= ENEMY && obj < NEUTRAL && AlivePlayerCnt() == false) {
		AttackBoxCheck(pObj);
	}
	if (drawHandle == MD_PLAY) {
		if (obj == turn)
		{
			if (pObj->moveHandler == ENEMYPLAYERMOVE) {
				SetPlayerMotion(pObj);
				AttackObj(obj, pObj->target);
			}
		}
	}
NEXT:
	if (obj < NEUTRAL) {
		//아이콘 프레임
		if (pObj->moveHandler < BULLET3WAYMOVE && pObj->icon) {
			pObj->icon += TOTALEMOTICON;

			if (pObj->icon > 65000)
				pObj->icon = pObj->icon % TOTALEMOTICON + TOTALEMOTICON * 3;
		}

		//속성 타격효과 프레임
		if (pObj->attr && pObj->moveHandler < BULLET3WAYMOVE) {
			pObj->attr += 10;

			switch (pObj->attr % 10) {
			case FROST:
				if (pObj->attr > 200)
					pObj->attr = 0;
				break;
			case DARK:
				if (pObj->attr > 200)
					pObj->attr = 0;
				break;
			default:
				if (pObj->attr > 200)
					pObj->attr = 0;
				break;
			}
		}
	}
}

void PlayerMove(OBJECT* pObj)
{
	//60프레임 순환표에서 뽑은 모션. 없으면 -1.
	int loopMotion;
	int released = ((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID) && pObj->dead == false ? key_released : true);
	int motion = -1;
	int obj = GetObjFromPtr(pObj);
	int height = 0;
	int playerMoveKey = systemKey;

	//if (pObj->invincible)
	//	pObj->invincible--;

	if (fadeFrame > (FPS - 8) || fadeFrame < -(FPS - 8))
		return;

	if ((obj == DIANA || obj == MAXX) && IsGetHero(obj) == false) {
		InitMotion(pObj);
		return;
	}
	// 데모신 전용.
	if (pObj->type == DIANA && pObj->motion >= PO_C1_AWAKE0 && pObj->motion <= PO_C1_AWAKE6) {
		pObj->status = FLYING;

		if (pObj->y > 175 * _2X)
			pObj->dy = -3 * _2X;
		else
			pObj->dy = 2 * (robin.playtime % 4 > 1 ? -1 : 1) * _2X;

		if (movie.robinMotion[obj] != PO_C1_DIE0 && pObj->motion >= PO_C1_AWAKE1 && pObj->motion < PO_C1_AWAKE6) {
			movie.robinMotion[obj]++;

			if (movie.robinMotion[obj] == PO_C1_AWAKE6)
				movie.robinMotion[obj] = PO_C1_AWAKE1;
		}
	}

	pObj->dx = Abs(pObj->dx);

	pObj->pDx = pObj->dx;
	pObj->pDy = pObj->dy;

	if (pObj->inTile) {
		pObj->inertia = 1 * _2X;
		pObj->playerRun = false;
	}

	if (drawHandle == MD_PLAY) {
		if (pObj->flamer) {
			pObj->flamer--;
			if (pObj->flamer == 0) {
				/*
				if (skillInfoFrame > SKILLREMAINEDFRAME)
					skillInfoFrame = SKILLREMAINEDFRAME;
				if (skillUsed > SKILLREMAINEDFRAME)
					skillUsed = SKILLREMAINEDFRAME;

				if (attackType == ROULETTE_SKILL) {
					attackSequence = ATTACKSEQUENCE_ATTACKRESULT;
					attackDelay = attackDelayPerType[attackType];
					screenDarken = false;


					//로빈의 스킬이면
					if (curSkill < SKILL_COMMON_DIANA1) {
					}
					//디아나의 스킬이면
					//디아나의 공격을 일단 멈춰준다.
					else if (curSkill < SKILL_COMMON_MAXX1) {
						ao[DIANA].attack = false;
						ReleasePlayer(&ao[DIANA]);
					}
					//맥스의 스킬이면
					//맥스의 공격을 일단 멈춰준다.
					else {
						ao[MAXX].attack = false;
						ReleasePlayer(&ao[MAXX]);
					}

					focus = ROBIN;
				}
				*/
				pObj->moveHandler = VANISHMOVE;
				pObj->drawHandler = VANISHDRAW;
				onceDmgUpdateFrame = 2 * FPS;
				//WhoIsNextTurn();
			}
		}
	}

	if (pObj->debuf[KNOCKBACK] || pObj->debuf[STUN]) {
		effect.alpha = 0;
		pObj->attack = false;

		if (drawHandle == MD_PLAY) {
			if (turn < PLAYERALL) {
				pObj->turnPosition = COMING;
#ifndef WARIGARI
				if (autoPlay == true && drawHandle == MD_PLAY && JoyStickPressPossible() == true) {
					BoxOpen();

				}
#endif
			}
		}

		pObj->concentrate = 0;

		if (pObj->inTile == GROUND) {
			switch (pObj->status) {
			case JUMP:
			case GLIDE:
				pObj->jumpFrame = 0;
				pObj->status = FALL;
				pObj->dirY = DOWN;
				break;
			default:
				if (pObj->jumpFrame < JUMPFRAME + 1)
					pObj->dy = jump[JUMPFRAME - pObj->jumpFrame];
				else
					pObj->dy = FREEFALL;

				pObj->jumpFrame++;
				break;
			}
		}

		pObj->playerRun = false;

		if (pObj->debuf[KNOCKBACK] && darkStone == false) {
			pObj->dirX = 1 - pObj->dirF;
			pObj->dx = DIR(pObj->dirX) * 4 * _2X;// * (pObj->debuf[KNOCKBACK]) * (pObj->debuf[KNOCKBACK]);
			pObj->debuf[KNOCKBACK]--;

			goto chk;
		}
		else {
			pObj->dx = 0;
			pObj->debuf[STUN]--;

			goto chk;
		}
	}

	if (drawHandle == MD_DEMO) {
		if (demoPlayerX[obj] < 0) {
			released = false;
			playerMoveKey = AVK_4;
			pObj->dx = pDx = Abs(demoPlayerX[obj]);
		}
		else if (demoPlayerX[obj] > 0) {
			released = false;
			playerMoveKey = AVK_6;
			pObj->dx = pDx = demoPlayerX[obj];
		}
		else {
			released = true;
			playerMoveKey = null;
		}
	}

	if (pObj->attack) {
		motion = PlayerMove_Attack(pObj, released);

		pObj->x += pObj->dx * DIR(pObj->dirX);
		//공격시 몬스터의 충돌영역과 겹쳤다면 더이상 전진하지 않는다.(몇가지 스킬은 제외)
		if (ObjCrash(pObj, &ao[curEnemy]) && curEnemy != 0 && pObj->currentSkill != SKILL_ROBIN9) {
			//충돌영역만큼 뒤로 빼주고
			pObj->x -= pObj->dx * DIR(pObj->dirX);
			pObj->dx = 0;
			pObj->pDx = 0;
		}
		else
			pObj->x -= pObj->dx * DIR(pObj->dirX);

		if (pObj->magnet)
			goto chk;
	}
	else {
		if (obj < TOTALCHAR) {
			if (drawHandle == MD_PLAY && IsMovingSkill(pObj->currentSkill) == true) {
				//적의 발생지역보다 작으면
				//다시 복귀해라
				if (pObj->x > pObj->nx) {
					pObj->currentSkill = -1;
					//playerMoveKey = AVK_4;
				}
			}
			else {
				pObj->currentSkill = -1;
			}
		}

		if (pObj->magnet)
			goto chk;

		{
			int i;

			if (pObj->inTile)
				motion = PO_C0_SWIM0;
			else {
				switch (playerMoveKey) {
				case AVK_1:
					pObj->inertia = 2 * _2X;

					if (pObj->dirX == RIGHT && pObj->playerRun == true) {
						pObj->inertia = 1 * _2X;
						pObj->playerRun = false;
					}
					break;
				case AVK_3:
					pObj->inertia = 2 * _2X;

					if (pObj->dirX == LEFT && pObj->playerRun == true) {
						pObj->inertia = 1 * _2X;
						pObj->playerRun = false;
					}
					break;
				case AVK_4:
					pObj->inertia = (pObj->dirX == LEFT) ? 2 * _2X : 4 * _2X;

					if (pObj->dirX == RIGHT && pObj->playerRun == true) {
						pObj->inertia = 1 * _2X;
						pObj->playerRun = false;
					}
					break;
				case AVK_6:
					pObj->inertia = (pObj->dirX == LEFT) ? 4 * _2X : 2 * _2X;

					if (pObj->dirX == LEFT && pObj->playerRun == true) {
						pObj->inertia = 1 * _2X;
						pObj->playerRun = false;
					}
					break;
				default:
					pObj->inertia = 4 * _2X;
					break;
				}

				motion = (pObj->flamer == 0) ? PO_C0_N0 : PO_C1_FIREN0;
			}

			//얼음 미끄러지기 관련
			if (!pObj->canOnWater && pObj->onTile == TILE_ICE && !isDemo)
				pObj->inertia = 1 * _2X;

			if (!pObj->attacked && pObj->dead == false) {
				if (!released) {
					//////얼굴 방향 조정////
					switch (playerMoveKey) {

					case AVK_1:
					case AVK_4:
					case AVK_7:
						pObj->dirF = LEFT;
						break;

					case AVK_3:
					case AVK_6:
					case AVK_9:
						pObj->dirF = RIGHT;
						break;
						//case AVK_2:
					case AVK_8:
						pObj->playerRun = false;
						break;
					}

					if (pObj->inTile) {
						switch (playerMoveKey) {
						case AVK_1:
						case AVK_2:
						case AVK_3:
							pObj->oldDy = UP;
							break;
						case AVK_4:
						case AVK_5:
						case AVK_6:
						case AVK_7:
						case AVK_9:
							if (pObj->inTile == SPACE)
								break;
						case AVK_8:
							pObj->oldDy = DOWN;
							break;
						}
					}
				}
			}

			if ((released && pObj->playerRun == false) || returnFrame) {
				pObj->mx = false;

				if (pObj->inTile) {
					pObj->my = true;

					if (pObj->inTile != SPACE && pObj->dy == 0) {
						pObj->pDy = pObj->dy = 1;
						pObj->oldDy = DOWN;
						pObj->dirY = DOWN;
					}
				}
				else
					pObj->my = false;
			}
			else {
				if (!released) {
					////	//////Y축 이동 조정////	/////
					if (pObj->inTile == GROUND) {
						switch (playerMoveKey) {
						case AVK_1:
						case AVK_3:
						case AVK_2:
							switch (pObj->status) {
							case FALL:
							case FALL2:
								if (pObj->canGlide && darkStone == false && pObj->magnet == false && (!pObj->canJumpTwice || pObj->jumpTwice == true)) {
									if (arenaStatus == STATUS_PLAY) {
										pObj->status = GLIDE;
										pObj->dirY = DOWN;
									}
									break;
								}
							case JUMP:
								if (pObj->jumpTwice || pObj->jumpRelease || !pObj->canJumpTwice)
									break;
							case WALK:
								//보통 점프
								pObj->jumpTwice = (pObj->status == WALK) ? false : true;
								pObj->jumpRelease = true;

								pObj->dirY = UP;
								pObj->my = true;
								pObj->status = JUMP;

								if (pObj->onCarpet)
									ao[pObj->onCarpet].jumpFrame = -JUMPFRAME;

								if (darkStone) {
									ao[darkStone].status = 0;
									darkStone = 0;
								}

								if (pObj->jumpTwice == false && pObj->canSuperJump == true && playerMoveKey == AVK_2 && (pObj->pressedKey[1] == AVK_8 || (Abs(touchPressedKey[0][0] - touchPressedKey[1][0]) <= 20 * _2X && touchPressedKey[1][1] - touchPressedKey[0][1] > 80 * _2X))) {
									pObj->superJump = 2;
									pObj->jumpTwice = true;
									pObj->jumpFrame = -(JUMPFRAME - 1);
									if (obj == raidPlayer || ao[obj].soldier == true || (obj >= BULLET && obj < ENEMY && (ao[obj].target == PLAYER || ao[ao[obj].target].soldier == true)))
										effect.shake = 4;
								}
								else {
									pObj->jumpFrame = 0;

									if (pObj->playerRun == false)
#ifdef AGI_MOVESPEED
										pObj->pDx = GetSpeed(obj);
#else
										pObj->pDx = DX_WALK;
#endif
								}
								break;
							case FLYING:
								//공중 날기
								pObj->status = FALL;
								pObj->jumpFrame = 0;
								pObj->dirY = DOWN;
								break;
							}
							break;
						case AVK_8:
							pObj->dirY = DOWN;

							switch (pObj->status) {
							case WALK:
								pObj->my = true;
								pObj->jumpFrame = 0;
								pObj->playerRun = false;

								if (pObj->onTile == TILE_DOWN) {
									pObj->status = (TileCrash(pObj) == 1) ? JUMP3 : JUMP2;
									pObj->jumpFrame = JUMPFRAME - 1;
									pObj->dirY = UP;
									pObj->my = true;
								}

								if (pObj->onCarpet)
									ao[pObj->onCarpet].jumpFrame = -(JUMPFRAME - 1) * 2;

								//수면걷기 해제
								if (pObj->onWater > 0) {
									i = GetOnTile(pObj);

									if (i == TILE_WATER || i == TILE_SWAMP)
										pObj->onWater = 0;
								}
								break;
							case GLIDE:
							case FLYING:
								pObj->status = FALL;
								pObj->jumpFrame = 0;
								break;
							}
							break;
						}
					}
					else {
						if ((pObj->inTile == SPACE && pObj->dy != 0) || (pObj->inTile != SPACE && pObj->dy > 1)) {
							switch (playerMoveKey) {
							case AVK_2:
							case AVK_8:
								switch (pObj->inTile) {
								case WATER:
									pObj->pDy = DX_SWIM * pObj->canSwim;
									break;
								case SWAMP:
									pObj->pDy = DX_SWAMP * pObj->canSwim;
									break;
								case SPACE:
									pObj->pDy = DX_SPACE;
									break;
								}
								break;
								/*
#ifdef TOUCH
							case AVK_7_1:
							case AVK_9_1:
#else
							case AVK_7:
							case AVK_9:
								if (option.hotSlot == true)
									break;
#endif
									 */
							case AVK_1:
							case AVK_3:
								switch (pObj->inTile) {
								case WATER:
									pObj->pDy = DX_SWIM_SLOW * pObj->canSwim;
									break;
								case SWAMP:
									pObj->pDy = DX_SWAMP_SLOW * pObj->canSwim;
									break;
								case SPACE:
									pObj->pDy = DX_SPACE;
									break;
								}
								break;
							default:
								if (pObj->inTile != SPACE)
									pObj->pDy -= 1 * _2X;
								break;
							}
						}
						else {
							pObj->dirY = pObj->oldDy;

							switch (playerMoveKey) {
							case AVK_1:
							case AVK_2:
							case AVK_3:
							case AVK_8:
								pObj->pDy = pObj->dy = DX_SLOW;
								break;
							default:
								pObj->pDy = pObj->dy = (pObj->inTile == SPACE ? 0 : 1);
								break;
							}
						}
					}
				}

				pObj->mx = ((playerMoveKey == AVK_2 && pObj->playerRun == false) || playerMoveKey == AVK_8) ? false : true;

				////	//////X축 이동 조정////	///	//
				switch (pObj->inTile) {
				case GROUND:
					if (pObj->status == WALK || pObj->status == GLIDE) {
						if (pObj->playerRun == true)
							pObj->pDx = DX_RUN;
						else {
							switch (playerMoveKey) {
							case AVK_4:
							case AVK_6:
							case AVK_1:
							case AVK_3:
							case AVK_7:
							case AVK_9:
								pObj->pDx = GetSpeed(obj);
								break;
							case AVK_2:
							case AVK_8:
								pObj->pDx = 0;
								break;
							}
						}
					}
					else if (pObj->dx == 0) {
						switch (playerMoveKey) {

						case AVK_4:
						case AVK_6:
						case AVK_7:
						case AVK_9:
							pObj->dirX = pObj->dirF;
							pObj->pDx = GetSpeed(obj);
							break;
						case AVK_1:
						case AVK_3:
							pObj->dirX = pObj->dirF;
							pObj->pDx = GetSpeed(obj);
							break;
						}
					}
					//제자리에서도 flamer가 있으면 불로 해준다.
					if (pObj->dx != 0) {
						if (pObj->flamer == 0)
							motion = (pObj->playerRun == true) ? PO_C0_R0 : PO_C0_W0;
						else
							motion = PO_C1_FIREW0;
					}
					else {
						if (pObj->flamer)
							motion = PO_C1_FIREW0;
					}
					break;
				case WATER:
					////	//////X축 이동 조정////	///	//
					if (pObj->dx) {
						switch (playerMoveKey) {
						case AVK_4:
						case AVK_6:
						case AVK_7:
						case AVK_9:
							pObj->pDx = DX_SWIM * pObj->canSwim;
							break;

						case AVK_1:
						case AVK_3:
							pObj->pDx = DX_SWIM_SLOW * pObj->canSwim;
							break;
						}
					}
					else {
						switch (playerMoveKey) {

						case AVK_1:
						case AVK_4:
						case AVK_3:
						case AVK_6:
						case AVK_7:
						case AVK_9:
							pObj->dirX = pObj->dirF;
							pObj->pDx = pObj->dx = (pObj->mx == true) ? DX_SLOW : DX_SWIM * pObj->canSwim;
							break;
						}
					}
					break;
				case SWAMP:
					////	//////X축 이동 조정////	///	//
					if (pObj->dx) {
						switch (playerMoveKey) {
						case AVK_4:
						case AVK_6:
						case AVK_7:
						case AVK_9:
							pObj->pDx = DX_SWAMP * pObj->canSwim;
							break;
							/*
#ifdef TOUCH
						case AVK_7_1:
						case AVK_9_1:
#else
						case AVK_7:
						case AVK_9:
							if (option.hotSlot == true)
								break;
#endif
								 */
						case AVK_1:
						case AVK_3:
							pObj->pDx = DX_SWAMP_SLOW * pObj->canSwim;
							break;
						}
					}
					else {
						switch (playerMoveKey) {
							/*
#ifdef TOUCH
						case AVK_7_1:
						case AVK_9_1:
#else
						case AVK_7:
						case AVK_9:
							if (option.hotSlot == true)
								break;
#endif
								 */
						case AVK_1:
						case AVK_4:
						case AVK_3:
						case AVK_6:
						case AVK_7:
						case AVK_9:
							pObj->dirX = pObj->dirF;
							pObj->pDx = pObj->dx = (pObj->mx == true) ? DX_SLOW : DX_SWAMP * pObj->canSwim;
							break;
						}
					}
					break;
				case SPACE:
					////	//////X축 이동 조정////	///	//
					if (pObj->dx) {
						switch (playerMoveKey) {
							/*
#ifdef TOUCH
						case AVK_7_1:
						case AVK_9_1:
#else
						case AVK_7:
						case AVK_9:
							if (option.hotSlot == true)
								break;
#endif
								 */
						case AVK_4:
						case AVK_6:
						case AVK_1:
						case AVK_3:
						case AVK_7:
						case AVK_9:
							pObj->pDx = DX_SPACE;
							break;
						}
					}
					else {
						switch (playerMoveKey) {

						case AVK_1:
						case AVK_4:
						case AVK_3:
						case AVK_6:
						case AVK_7:
						case AVK_9:
							pObj->dirX = pObj->dirF;
							pObj->pDx = pObj->dx = (pObj->mx == true) ? DX_SLOW : DX_SPACE;
							break;
						}
					}
					break;
				}
			}
		}
	}

	//y좌표 변화(점프, 자유낙하 실시)
	if (pObj->inTile == GROUND) {
		switch (pObj->status) {
		case JUMP:	//점프하고 있는 경우
		case JUMP2:
		case JUMP3:

			motion = (pObj->flamer == 0) ? PO_C0_W0 : PO_C1_FIREJU0;
			pObj->onTile = 0;
			pObj->dirY = UP;

			if (pObj->jumpFrame < 0)
				pObj->dy = -FREEFALL + pObj->jumpFrame * _2X;
			else
				pObj->dy = -jump[pObj->jumpFrame];

			pObj->jumpFrame++;
			break;
		case FALL2:
			if (pObj->onTile) {
				motion = PO_C0_LANDING1;
				pObj->status = WALK;
				break;
			}
		default:
			if (pObj->superJump == 2)
				pObj->superJump = 1;

			pObj->onTile = GetOnTile(pObj);

			if (pObj->status != WALK && (pObj->onTile == 0 || pObj->status == THROUGH || pObj->status == THROUGH2)) {
				if (pObj->status == FALL2)
					motion = PO_C0_JD0;
				else
					motion = (pObj->flamer == 0) ? PO_C0_W0 : PO_C1_FIREJD0;
			}

			if (pObj->type == ROBIN && pObj->attack == ATTACK_DOWN) {
				if (pObj->attackFrame < 4)
					pObj->dy = pObj->attackFrame * _2X;
				else if (pObj->attackFrame == 4)
					pObj->dy = GetObjHeight(pObj) % FREEFALL + 1 * _2X;
				else
					pObj->dy = FREEFALL;
			}
			else {
				if (pObj->jumpFrame < JUMPFRAME)
					pObj->dy = jump[JUMPFRAME - 1 - pObj->jumpFrame];
				else
					pObj->dy = FREEFALL;

				pObj->jumpFrame++;
			}

			if (pObj->status == GLIDE) {
				pObj->dy = 1 * _2X;
			}
			break;
			//날고있는 경우
		case FLYING:
			break;
		}
	}
	else {
		if (pObj->status == WALK && pObj->inTile != SPACE)
			pObj->pDy = pObj->dy = 1 * _2X;

		if (pObj->dead)
			pObj->pDy = pObj->dy = 0;
	}

	if (pObj->dx == 0) {
		switch (playerMoveKey) {

		case AVK_1:
		case AVK_4:
		case AVK_7:
			pObj->dirX = LEFT;
			break;

		case AVK_3:
		case AVK_6:
		case AVK_9:
			pObj->dirX = RIGHT;
			break;
		}
	}

	if (pObj->mx == true && pObj->dirX == pObj->dirF && !pObj->attacked && pObj->superJump < 2) {
		if (pObj->inTile == SWAMP || pObj->inTile == WATER)
			pObj->dx = Min(pObj->pDx, pObj->dx + pObj->inertia * 2);
		else
			pObj->dx = Min(pObj->pDx, pObj->dx + pObj->inertia);
	}
	else {
		if (pObj->inTile == SPACE) {
			if (released == false && playerMoveKey != AVK_2 && playerMoveKey != AVK_8)
				pObj->dx = Max(pObj->dx - pObj->inertia, 0);
		}
		else
			pObj->dx = Max(pObj->dx - pObj->inertia, 0);

		if (pObj->inTile == GROUND && motion == -1 && pObj->dx == 0 && pObj->onTile > 0)
			motion = (pObj->flamer == 0) ? PO_C0_N0 : PO_C1_FIREJD0;
	}

	pObj->dx = Max(pObj->dx, 0);

	pObj->dx = pObj->dx * DIR(pObj->dirX);

#ifdef DEBUG
	p[0] = pObj->dx;
#endif

	if (pObj->inTile) {
		if (pObj->inTile == SPACE) {
			if (!pObj->attacked && pObj->dirY == pObj->oldDy)
				pObj->dy = Min(pObj->pDy, pObj->dy + pObj->inertia);
			else if (released == false && playerMoveKey != AVK_4 && playerMoveKey != AVK_6)
				pObj->dy = Max(pObj->dy - pObj->inertia, 0);
		}
		else {
			if (!pObj->attacked && pObj->dirY == pObj->oldDy)
				pObj->dy = Min(pObj->pDy, pObj->dy + pObj->inertia * 2);
			else
				pObj->dy = Max(pObj->dy - pObj->inertia, 0);

			if (pObj->dy == 0 && pObj->dead == false) {
				pObj->dy = 1 * _2X;
				pObj->dirY = DOWN;
			}
		}

		pObj->dy = Max(pObj->dy, 0);
		pObj->dy = pObj->dy * DIR(pObj->dirY);
	}

#ifdef DEBUG
	p[1] = pObj->dy;
#endif

chk:
	{
		int i;
		if (pObj->type == MAXX && pObj->motion == PO_C2_STOP0)
			motion = PO_C2_STOP1;

		if (motion >= 0)
			pObj->motion = motion;

		if (pObj->magnet) {
			OBJECT* mObj = &ao[pObj->magnet % 100];

			pObj->mx = false;
			pObj->playerRun = false;

			pObj->y -= 12 * _2X;

			if (pObj->magnet / 100) {
				if (!pObj->dy) {
					pObj->dirY = 1 - pObj->dirY;
					mObj->jumpFrame = Max(0, mObj->jumpFrame - 2);
				}

				i = (pObj->x > mObj->x) ? 24 * _2X : -24 * _2X;
				mObj->x += i;
				height = GetDistance(mObj, pObj);
				mObj->x -= i;
			}
			else {
				if (!pObj->dx) {
					pObj->dirX = 1 - pObj->dirX;
					mObj->jumpFrame = Max(0, mObj->jumpFrame - 2);
				}

				i = (pObj->y > mObj->y) ? 28 * _2X : -28 * _2X;
				mObj->y += i;
				height = GetDistance(mObj, pObj);
				mObj->y -= i;
			}

			pObj->y += 12 * _2X;

			if (height / 8 == false) {
				pObj->inertia = 0;
				pObj->status = MAGNET;
			}

			if (pObj->status == MAGNET) {
				if (is_key_released == false) {
					switch (playerMoveKey) {

					case AVK_1:
					case AVK_4:
					case AVK_7:
						pObj->dirF = LEFT;
						break;

					case AVK_3:
					case AVK_6:
					case AVK_9:
						pObj->dirF = RIGHT;
						break;
					}

					if (pObj->magnet / 100) {
						switch (playerMoveKey) {
						case AVK_1:
						case AVK_2:
						case AVK_3:
							pObj->dirY = UP;
							break;

						case AVK_8:
							pObj->dirY = DOWN;
							break;
						default:
							goto ELSE;
						}

						pObj->dy = 1 * _2X;
					}
					else {
						switch (playerMoveKey) {

						case AVK_1:
						case AVK_4:
						case AVK_7:
							pObj->dirX = LEFT;
							break;

						case AVK_3:
						case AVK_6:
						case AVK_9:
							pObj->dirX = RIGHT;
							break;
						default:
							goto ELSE;
						}

						pObj->dx = 1 * _2X;
					}

					pObj->motion = PO_C0_W0;
				}
				else {
				ELSE:

					if (pObj->magnet / 100) {
						pObj->dy = (Abs(pObj->y - 12 * _2X - mObj->y) > 1 * _2X) ? Max(height / 2, 1) * _2X : 0 * _2X;
						pObj->dirY = (pObj->y - 12 * _2X > mObj->y) ? UP : DOWN;
					}
					else {
						pObj->dx = (Abs(pObj->x - mObj->x) > 1 * _2X) ? Max(height / 2, 1) * _2X : 0 * _2X;
						pObj->dirX = (pObj->x > mObj->x) ? LEFT : RIGHT;
					}

					pObj->motion = PO_C0_N0;
				}

				pObj->inertia = 0;
			}
			else {
				pObj->motion = PO_C0_W0;

				if (pObj->magnet / 100) {
					pObj->dy = Min(pObj->dy, Min(height / 8, mObj->jumpFrame)) * _2X;

					if (pObj->y - 12 * _2X > mObj->y)
						pObj->inertia = (pObj->dirY) ? 2 * _2X : -2 * _2X;
					else
						pObj->inertia = (pObj->dirY) ? -2 * _2X : 2 * _2X;
				}
				else {
					pObj->dx = Min(pObj->dx, Min(height / 8, mObj->jumpFrame)) * _2X;

					if (pObj->x > mObj->x)
						pObj->inertia = (pObj->dirX) ? 2 * _2X : -2 * _2X;
					else
						pObj->inertia = (pObj->dirX) ? -2 * _2X : 2 * _2X;
				}
			}

			if (pObj->magnet / 100) {
				pObj->dx = Min(mObj->mainFrame, 8) * DIR(pObj->dirX) * _2X;

				height = pObj->status;

				pObj->dy -= pObj->inertia;
				pObj->dy = Max(pObj->dy, 0);
				pObj->dy = pObj->dy * DIR(pObj->dirY);	////로빈의 이동 간격을 결정

				if (!pObj->dy)
					pObj->motion = PO_C0_N0;
			}
			else {
				pObj->dy = Min(mObj->mainFrame, 8) * DIR(pObj->dirY);

				height = pObj->status;

				pObj->dx -= pObj->inertia;
				pObj->dx = Max(pObj->dx, 0);
				pObj->dx = pObj->dx * DIR(pObj->dirX);	////로빈의 이동 간격을 결정

				if (!pObj->dx)
					pObj->motion = PO_C0_N0;
			}
		}

		//어둠의 파편
		if (darkStone) {
			OBJECT* pDark = &ao[darkStone];

			pObj->status = WALK;
			pObj->motion = PO_C0_N0;

			//이동할 각도
			motion = (pDark->dirX == RIGHT) ? 340 : 20;

			pObj->y -= 12 * _2X;
			//각도만큼 평행변환
			pObj->x = pDark->x + (BC_mathCos1024(motion) * (pObj->x - pDark->x) >> 10) - (BC_mathSin1024(motion) * (pObj->y - pDark->y) >> 10);
			pObj->y = pDark->y + (BC_mathSin1024(motion) * (pObj->x - pDark->x) >> 10) + (BC_mathCos1024(motion) * (pObj->y - pDark->y) >> 10);

			//거리 계산
			i = Max(24 * _2X, GetDistance(pDark, pObj));
			pObj->y += 12 * _2X;

			if (i < 36 * _2X) {
				//거리가 짧다면 늘려준다.
				pObj->x = pDark->x + UpDiv((pObj->x - pDark->x) * (i + 2 * _2X), i);
				pObj->y = pDark->y + UpDiv((pObj->y - pDark->y) * (i + 2 * _2X), i);
				i += 2 * _2X;
			}

		}
		else {

			//if (robinmap < ARENA1 || robin.hp > 0)
			switch (drawHandle) {
			default:
				TileCheckX(pObj);
				TileCheckY(pObj);
				break;
			case MD_PLAY:
				if (attackSequence == ATTACKSEQUENCE_ACTION && obj == turn)
				switch (pObj->turnPosition) {
				case HERE:
					pObj->turnPosition = GOING;
					break;
				case GOING:
					GotoObj(&ao[pObj->target], pObj, Max(SPEED_MIN, pObj->pDx));
					pObj->x += pObj->dx;
					pObj->y += pObj->dy;
					loopMotion = GetHeroLoopMotion(pObj->cmf, HEROLOOP_WALK, pObj->frame);
					pObj->motion = (loopMotion < 0) ? PO_C0_W0 + walkFrame[pObj->frame / 2 % 4] : loopMotion;
					if (pObj->x + GetAttackRange(obj) >= ao[pObj->target].x) {
						pObj->x = Max(ao[pObj->target].x - GetAttackRange(obj), pObj->nx);
						pObj->y = ao[pObj->target].y;
						pObj->turnPosition = THERE;
						pObj->attack = ATTACK_NORMAL;
					}
					break;
				case COMING:
					GotoObjXY(pObj, pObj->nx, pObj->ny, Max(SPEED_MIN, pObj->pDx));
					pObj->x += pObj->dx;
					pObj->y += pObj->dy;
					if (pObj->x < pObj->nx)
						pObj->x = pObj->nx;
					/*
					if (pObj->x == pObj->nx && pObj->y != pObj->ny) {
						pObj->y = pObj->ny;
					}
					else if (pObj->x != pObj->nx && pObj->y == pObj->ny) {
						pObj->x = pObj->nx;
					}
					*/
					//이쪽은 원래 /2 가 없어 주기가 절반이다. 표를 두 칸씩 건너뛴다.
					loopMotion = GetHeroLoopMotion(pObj->cmf, HEROLOOP_WALK, pObj->frame * 2);
					pObj->motion = (loopMotion < 0) ? PO_C0_W0 + walkFrame[pObj->frame % 4] : loopMotion;
					pObj->dirX = pObj->dirF = LEFT;
					if (pObj->x == pObj->nx) {
						pObj->y = pObj->ny;
						pObj->attack = false;
						loopMotion = GetHeroLoopMotion(pObj->cmf, HEROLOOP_NEUTRAL, pObj->frame);
						pObj->motion = (loopMotion < 0) ? PO_C0_N0 + walkFrame[pObj->frame / 2 % 4] : loopMotion;
						ReleasePlayer(pObj);
						pObj->dirX = pObj->dirF = RIGHT;
						
						if (GetObjFromPtr(pObj) == turn && GetSonObjCnt(GetObjFromPtr(pObj)) == 0) {
							pObj->turnPosition = DMGUPDATE;
							onceDmgUpdateFrame = 2 * FPS;
						}
						
					}
					break;
				case DMGUPDATE:
#ifndef SPEEDTURN
					loopMotion = GetHeroLoopMotion(pObj->cmf, HEROLOOP_NEUTRAL, pObj->frame);
					pObj->motion = (loopMotion < 0) ? PO_C0_N0 + walkFrame[pObj->frame / 2 % 4] : loopMotion;
					if (onceDmgUpdateFrame == 1) {
						pObj->turnPosition = HERE;
						WhoIsNextTurn();
					}
#endif
					break;
				default:
					
					break;
				}
				else {
					//중괄호가 없어서 flamer일 때 loopMotion이 갱신되지 않은 채
					//아래에서 쓰였다. -1은 "60프레임 표가 없다"는 뜻이라
					//원래 식으로 떨어진다.
					loopMotion = pObj->flamer
						? -1
						: GetHeroLoopMotion(pObj->cmf, HEROLOOP_NEUTRAL, pObj->frame);
					pObj->motion = (loopMotion < 0) ? PO_C0_N0 + walkFrame[pObj->frame / 2 % 4] : loopMotion;
					pObj->dx = pObj->dy = 0;
				}
				//if (pObj->y != pObj->ny)
				//TileCheckY(pObj);
				break;
			}
		}

		if (height == MAGNET)
			pObj->status = MAGNET;
		else {
			if (pObj->inTile) {
				pObj->oldDy = pObj->dy;
				pObj->dy = Abs(pObj->dy);
			}
			else {
				switch (pObj->status) {
				case JUMP2:
				case JUMP3:
					if (pObj->jumpFrame >= JUMPFRAME) {
						pObj->jumpFrame = 0;
						pObj->dirY = DOWN;
						pObj->status = (pObj->status == JUMP2) ? THROUGH : THROUGH2;
					}
					break;
				case JUMP:
					if (pObj->jumpFrame >= JUMPFRAME) {
						pObj->jumpFrame = 0;
						pObj->dirY = DOWN;

						//if (jumpRelease == true && canGlide == true && robin.moveMode == MODE_NORMAL)
						//	pObj->status = GLIDE;
						//else {
						switch (TileCrash(pObj)) {
						case 0:
							pObj->status = FALL;
							break;
						case 1:
							pObj->status = THROUGH2;
							break;
						case 2:
							pObj->status = THROUGH;
							break;
						}
						//}
					}
					break;
				}
			}
		}

		pObj->frame++;

		//스킬시 암전
		if (obj == raidPlayer) {
			if (skillUsed > 0)
				skillUsed--;
			if (buffItemFrame > 0) {
				buffItemFrame--;
				if (buffItemFrame == 0) {
					buffItemUsed = 0;
				}
			}
		}
	}
}

void EnemyPlayerMove(OBJECT* pObj)
{
	int released = ((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID) && pObj->dead == false ? key_released : true);
	int motion = -1;
	int obj = GetObjFromPtr(pObj);
	int height = 0;
	int playerMoveKey = systemKey;

	if (pObj->invincible)
		pObj->invincible--;

	if (fadeFrame)
		return;

	pObj->pDx = pObj->dx;
	pObj->pDy = pObj->dy;

	if (pObj->inTile) {
		pObj->inertia = 1 * _2X;
		pObj->playerRun = false;
	}

	if (pObj->flamer) {

		pObj->flamer--;

		if (pObj->flamer == 0) {
			if (skillInfoFrame > SKILLREMAINEDFRAME)
				skillInfoFrame = SKILLREMAINEDFRAME;
			if (skillUsed > SKILLREMAINEDFRAME)
				skillUsed = SKILLREMAINEDFRAME;
		}
	}

	if (pObj->debuf[KNOCKBACK] || pObj->debuf[STUN]) {
		effect.alpha = 0;
		pObj->attack = false;

		pObj->turnPosition = COMING;
#ifndef WARIGARI
		if (autoPlay == true && drawHandle == MD_PLAY) {
			BoxOpen();

		}
#endif
		pObj->concentrate = 0;

		if (pObj->inTile == GROUND) {
			switch (pObj->status) {
			case JUMP:
			case GLIDE:
				pObj->jumpFrame = 0;
				pObj->status = FALL;
				pObj->dirY = DOWN;
				break;
			default:
				if (pObj->jumpFrame < JUMPFRAME + 1)
					pObj->dy = jump[JUMPFRAME - pObj->jumpFrame];
				else
					pObj->dy = FREEFALL;

				pObj->jumpFrame++;
				break;
			}
		}

		pObj->playerRun = false;

		if (pObj->debuf[KNOCKBACK] && darkStone == false) {
			pObj->dirX = 1 - pObj->dirF;
			pObj->dx = DIR(pObj->dirX) * 4 * _2X;// * (pObj->debuf[KNOCKBACK]) * (pObj->debuf[KNOCKBACK]);
			pObj->debuf[KNOCKBACK]--;

			goto chk;
		}
		else {
			pObj->dx = 0;
			pObj->debuf[STUN]--;

			goto chk;
		}
	}

	if (pObj->attack) {
		motion = PlayerMove_Attack(pObj, released);

		pObj->x += pObj->dx * DIR(pObj->dirX);
		//공격시 몬스터의 충돌영역과 겹쳤다면 더이상 전진하지 않는다.(몇가지 스킬은 제외)
		if (ObjCrash(pObj, &ao[pObj->target]) && pObj->target != 0 && pObj->currentSkill != SKILL_ROBIN9) {
			//충돌영역만큼 뒤로 빼주고
			pObj->x -= pObj->dx * DIR(pObj->dirX);
			pObj->dx = 0;
			pObj->pDx = 0;
		}
		else
			pObj->x -= pObj->dx * DIR(pObj->dirX);

		if (pObj->magnet)
			goto chk;
	}
	else {
		if (obj < PLAYERALL)
			pObj->currentSkill = -1;

		if (pObj->magnet)
			goto chk;

		{
			int i;

			if (pObj->inTile)
				motion = PO_C0_SWIM0;
			else {
				switch (playerMoveKey) {
				case AVK_1:
					pObj->inertia = 2 * _2X;

					if (pObj->dirX == RIGHT && pObj->playerRun == true) {
						pObj->inertia = 1 * _2X;
						pObj->playerRun = false;
					}
					break;
				case AVK_3:
					pObj->inertia = 2 * _2X;

					if (pObj->dirX == LEFT && pObj->playerRun == true) {
						pObj->inertia = 1 * _2X;
						pObj->playerRun = false;
					}
					break;
				case AVK_4:
					pObj->inertia = (pObj->dirX == LEFT) ? 2 * _2X : 4 * _2X;

					if (pObj->dirX == RIGHT && pObj->playerRun == true) {
						pObj->inertia = 1 * _2X;
						pObj->playerRun = false;
					}
					break;
				case AVK_6:
					pObj->inertia = (pObj->dirX == LEFT) ? 4 * _2X : 2 * _2X;

					if (pObj->dirX == LEFT && pObj->playerRun == true) {
						pObj->inertia = 1 * _2X;
						pObj->playerRun = false;
					}
					break;
				default:
					pObj->inertia = 4 * _2X;
					break;
				}

				motion = (pObj->flamer == 0) ? PO_C0_N0 : PO_C1_FIREN0;
			}

			//얼음 미끄러지기 관련
			if (!pObj->canOnWater && pObj->onTile == TILE_ICE && !isDemo)
				pObj->inertia = 1 * _2X;

			if (!pObj->attacked && pObj->dead == false) {
				if (!released) {
					//////얼굴 방향 조정////
					switch (playerMoveKey) {

					case AVK_1:
					case AVK_4:
					case AVK_7:
						pObj->dirF = LEFT;
						break;

					case AVK_3:
					case AVK_6:
					case AVK_9:
						pObj->dirF = RIGHT;
						break;
					case AVK_8:
						pObj->playerRun = false;
						break;
					}

					if (pObj->inTile) {
						switch (playerMoveKey) {
						case AVK_1:
						case AVK_2:
						case AVK_3:
							pObj->oldDy = UP;
							break;
						case AVK_4:
						case AVK_5:
						case AVK_6:
						case AVK_7:
						case AVK_9:
							if (pObj->inTile == SPACE)
								break;

						case AVK_8:
							pObj->oldDy = DOWN;
							break;
						}
					}
				}
			}

			if ((released && pObj->playerRun == false) || returnFrame) {
				pObj->mx = false;

				if (pObj->inTile) {
					pObj->my = true;

					if (pObj->inTile != SPACE && pObj->dy == 0) {
						pObj->pDy = pObj->dy = 1;
						pObj->oldDy = DOWN;
						pObj->dirY = DOWN;
					}
				}
				else
					pObj->my = false;
			}
			else {
				if (!released) {
					////	//////Y축 이동 조정////	/////
					if (pObj->inTile == GROUND) {
						switch (playerMoveKey) {
						case AVK_1:
						case AVK_3:
						case AVK_2:
							switch (pObj->status) {
							case FALL:
							case FALL2:
								if (pObj->canGlide && darkStone == false && pObj->magnet == false && (!pObj->canJumpTwice || pObj->jumpTwice == true)) {
									if (arenaStatus == STATUS_PLAY) {
										pObj->status = GLIDE;
										pObj->dirY = DOWN;
									}
									break;
								}
							case JUMP:
								if (pObj->jumpTwice || pObj->jumpRelease || !pObj->canJumpTwice)
									break;
							case WALK:
								//보통 점프
								pObj->jumpTwice = (pObj->status == WALK) ? false : true;
								pObj->jumpRelease = true;

								pObj->dirY = UP;
								pObj->my = true;
								pObj->status = JUMP;

								if (pObj->onCarpet)
									ao[pObj->onCarpet].jumpFrame = -JUMPFRAME;

								if (darkStone) {
									ao[darkStone].status = 0;
									darkStone = 0;
								}

								if (pObj->jumpTwice == false && pObj->canSuperJump == true && playerMoveKey == AVK_2 && (pObj->pressedKey[1] == AVK_8 || (Abs(touchPressedKey[0][0] - touchPressedKey[1][0]) <= 20 * _2X && touchPressedKey[1][1] - touchPressedKey[0][1] > 80 * _2X))) {
									//superJump : 2(올라가고 있을때), 1(내려오고 있을때), 0이하(점프가 가능할때)
									pObj->superJump = 2;
									pObj->jumpTwice = true;
									pObj->jumpFrame = -(JUMPFRAME - 1);
									if (obj == raidPlayer || ao[obj].soldier == true || (obj >= BULLET && obj < ENEMY && (ao[obj].target == PLAYER || ao[ao[obj].target].soldier == true)))
										effect.shake = 4;
								}
								else {
									pObj->jumpFrame = 0;

									if (pObj->playerRun == false)
										pObj->pDx = GetSpeed(obj);
								}
								break;
							case FLYING:
								//공중 날기
								pObj->status = FALL;
								pObj->jumpFrame = 0;
								pObj->dirY = DOWN;
								break;
							}
							break;
						case AVK_8:
							pObj->dirY = DOWN;

							switch (pObj->status) {
							case WALK:
								pObj->my = true;
								pObj->jumpFrame = 0;
								pObj->playerRun = false;

								if (pObj->onTile == TILE_DOWN) {
									pObj->status = (TileCrash(pObj) == 1) ? JUMP3 : JUMP2;
									pObj->jumpFrame = JUMPFRAME - 1;
									pObj->dirY = UP;
									pObj->my = true;
								}

								if (pObj->onCarpet)
									ao[pObj->onCarpet].jumpFrame = -(JUMPFRAME - 1) * 2;

								//수면걷기 해제
								if (pObj->onWater > 0) {
									i = GetOnTile(pObj);

									if (i == TILE_WATER || i == TILE_SWAMP)
										pObj->onWater = 0;
								}
								break;
							case GLIDE:
							case FLYING:
								pObj->status = FALL;
								pObj->jumpFrame = 0;
								break;
							}
							break;
						}
					}
					else {
						if ((pObj->inTile == SPACE && pObj->dy != 0) || (pObj->inTile != SPACE && pObj->dy > 1)) {
							switch (playerMoveKey) {
							case AVK_2:
							case AVK_8:
								switch (pObj->inTile) {
								case WATER:
									pObj->pDy = DX_SWIM * pObj->canSwim;
									break;
								case SWAMP:
									pObj->pDy = DX_SWAMP * pObj->canSwim;
									break;
								case SPACE:
									pObj->pDy = DX_SPACE;
									break;
								}
								break;

							case AVK_1:
							case AVK_3:
								switch (pObj->inTile) {
								case WATER:
									pObj->pDy = DX_SWIM_SLOW * pObj->canSwim;
									break;
								case SWAMP:
									pObj->pDy = DX_SWAMP_SLOW * pObj->canSwim;
									break;
								case SPACE:
									pObj->pDy = DX_SPACE;
									break;
								}
								break;
							default:
								if (pObj->inTile != SPACE)
									pObj->pDy -= 1 * _2X;
								break;
							}
						}
						else {
							pObj->dirY = pObj->oldDy;

							switch (playerMoveKey) {

							case AVK_1:
							case AVK_2:
							case AVK_3:
							case AVK_8:
								pObj->pDy = pObj->dy = DX_SLOW;
								break;
							default:
								pObj->pDy = pObj->dy = (pObj->inTile == SPACE ? 0 : 1);
								break;
							}
						}
					}
				}

				pObj->mx = ((playerMoveKey == AVK_2 && pObj->playerRun == false) || playerMoveKey == AVK_8) ? false : true;

				////	//////X축 이동 조정////	///	//
				switch (pObj->inTile) {
				case GROUND:
					if (pObj->status == WALK || pObj->status == GLIDE) {
						if (pObj->playerRun == true)
							pObj->pDx = DX_RUN;
						else {
							switch (playerMoveKey) {
							case AVK_4:
							case AVK_6:
							case AVK_1:
							case AVK_3:
							case AVK_7:
							case AVK_9:
								pObj->pDx = GetSpeed(obj);
								break;
							case AVK_2:
							case AVK_8:
								pObj->pDx = 0;
								break;
							}
						}
					}
					else if (pObj->dx == 0) {
						switch (playerMoveKey) {
						case AVK_4:
						case AVK_6:
						case AVK_7:
						case AVK_9:
							pObj->dirX = pObj->dirF;
							pObj->pDx = GetSpeed(obj);
							break;
						case AVK_1:
						case AVK_3:
							pObj->dirX = pObj->dirF;
							pObj->pDx = GetSpeed(obj);
							break;
						}
					}

					if (pObj->dx != 0) {
						if (pObj->flamer == 0)
							motion = (pObj->playerRun == true) ? PO_C0_R0 : PO_C0_W0;
						else
							motion = PO_C1_FIREW0;
					}
					break;
				case WATER:
					////	//////X축 이동 조정////	///	//
					if (pObj->dx) {
						switch (playerMoveKey) {
						case AVK_4:
						case AVK_6:
						case AVK_7:
						case AVK_9:
							pObj->pDx = DX_SWIM * pObj->canSwim;
							break;

						case AVK_1:
						case AVK_3:
							pObj->pDx = DX_SWIM_SLOW * pObj->canSwim;
							break;
						}
					}
					else {
						switch (playerMoveKey) {

						case AVK_1:
						case AVK_4:
						case AVK_3:
						case AVK_6:
						case AVK_7:
						case AVK_9:
							pObj->dirX = pObj->dirF;
							pObj->pDx = pObj->dx = (pObj->mx == true) ? DX_SLOW : DX_SWIM * pObj->canSwim;
							break;
						}
					}
					break;
				case SWAMP:
					////	//////X축 이동 조정////	///	//
					if (pObj->dx) {
						switch (playerMoveKey) {
						case AVK_4:
						case AVK_6:
						case AVK_7:
						case AVK_9:
							pObj->pDx = DX_SWAMP * pObj->canSwim;
							break;

						case AVK_1:
						case AVK_3:
							pObj->pDx = DX_SWAMP_SLOW * pObj->canSwim;
							break;
						}
					}
					else {
						switch (playerMoveKey) {

						case AVK_1:
						case AVK_4:
						case AVK_3:
						case AVK_6:
						case AVK_7:
						case AVK_9:
							pObj->dirX = pObj->dirF;
							pObj->pDx = pObj->dx = (pObj->mx == true) ? DX_SLOW : DX_SWAMP * pObj->canSwim;
							break;
						}
					}
					break;
				case SPACE:
					////	//////X축 이동 조정////	///	//
					if (pObj->dx) {
						switch (playerMoveKey) {

						case AVK_4:
						case AVK_6:
						case AVK_1:
						case AVK_3:
						case AVK_7:
						case AVK_9:
							pObj->pDx = DX_SPACE;
							break;
						}
					}
					else {
						switch (playerMoveKey) {

						case AVK_1:
						case AVK_4:
						case AVK_3:
						case AVK_6:
						case AVK_7:
						case AVK_9:
							pObj->dirX = pObj->dirF;
							pObj->pDx = pObj->dx = (pObj->mx == true) ? DX_SLOW : DX_SPACE;
							break;
						}
					}
					break;
				}
			}
		}
	}

	if (pObj->attacked && pObj->attack < 3) {
		pObj->mx = true;
		pObj->attacked = false;
	}

	//y좌표 변화(점프, 자유낙하 실시)
	if (pObj->inTile == GROUND) {
		switch (pObj->status) {
		case JUMP:	//점프하고 있는 경우
		case JUMP2:
		case JUMP3:

			motion = (pObj->flamer == 0) ? PO_C0_W0 : PO_C1_FIREJU0;
			pObj->onTile = 0;
			pObj->dirY = UP;

			if (pObj->jumpFrame < 0)
				pObj->dy = -FREEFALL + pObj->jumpFrame * _2X;
			else
				pObj->dy = -jump[pObj->jumpFrame];

			pObj->jumpFrame++;
			break;
		case FALL2:
			if (pObj->onTile) {
				motion = PO_C0_LANDING1;
				pObj->status = WALK;
				break;
			}
		default:
			if (pObj->superJump == 2)
				pObj->superJump = 1;

			pObj->onTile = GetOnTile(pObj);

			if (pObj->status != WALK && (pObj->onTile == 0 || pObj->status == THROUGH || pObj->status == THROUGH2)) {
				if (pObj->status == FALL2)
					motion = PO_C0_JD0;
				else
					motion = (pObj->flamer == 0) ? PO_C0_W0 : PO_C1_FIREJD0;
			}

			if (pObj->type == ROBIN && pObj->attack == ATTACK_DOWN) {
				if (pObj->attackFrame < 4)
					pObj->dy = pObj->attackFrame * _2X;
				else if (pObj->attackFrame == 4)
					pObj->dy = GetObjHeight(pObj) % FREEFALL + 1 * _2X;
				else
					pObj->dy = FREEFALL;
			}
			else {
				if (pObj->jumpFrame < JUMPFRAME)
					pObj->dy = jump[JUMPFRAME - 1 - pObj->jumpFrame];
				else
					pObj->dy = FREEFALL;

				pObj->jumpFrame++;
			}

			if (pObj->status == GLIDE) {
				pObj->dy = 1 * _2X;
			}
			break;
			//날고있는 경우
		case FLYING:
			break;
		}
	}
	else {
		if (pObj->status == WALK && pObj->inTile != SPACE)
			pObj->pDy = pObj->dy = 1 * _2X;

		if (pObj->dead)
			pObj->pDy = pObj->dy = 0;
	}

	if (pObj->dx == 0) {
		switch (playerMoveKey) {

		case AVK_1:
		case AVK_4:
		case AVK_7:
			pObj->dirX = LEFT;
			break;

		case AVK_3:
		case AVK_6:
		case AVK_9:
			pObj->dirX = RIGHT;
			break;
		}
	}

	if (pObj->mx == true && pObj->dirX == pObj->dirF && !pObj->attacked && pObj->superJump < 2) {
		if (pObj->inTile == SWAMP || pObj->inTile == WATER)
			pObj->dx = Min(pObj->pDx, pObj->dx + pObj->inertia * 2);
		else
			pObj->dx = Min(pObj->pDx, pObj->dx + pObj->inertia);
	}
	else {
		if (pObj->inTile == SPACE) {
			if (released == false && playerMoveKey != AVK_2 && playerMoveKey != AVK_8)
				pObj->dx = Max(pObj->dx - pObj->inertia, 0);
		}
		else
			pObj->dx = Max(pObj->dx - pObj->inertia, 0);

		if (pObj->inTile == GROUND && motion == -1 && pObj->dx == 0 && pObj->onTile > 0)
			motion = (pObj->flamer == 0) ? PO_C0_N0 : PO_C1_FIREJD0;
	}

	pObj->dx = Max(pObj->dx, 0);

	pObj->dx = pObj->dx * DIR(pObj->dirX);

#ifdef DEBUG
	p[0] = pObj->dx;
#endif

	if (pObj->inTile) {
		if (pObj->inTile == SPACE) {
			if (!pObj->attacked && pObj->dirY == pObj->oldDy)
				pObj->dy = Min(pObj->pDy, pObj->dy + pObj->inertia);
			else if (released == false && playerMoveKey != AVK_4 && playerMoveKey != AVK_6)
				pObj->dy = Max(pObj->dy - pObj->inertia, 0);
		}
		else {
			if (!pObj->attacked && pObj->dirY == pObj->oldDy)
				pObj->dy = Min(pObj->pDy, pObj->dy + pObj->inertia * 2);
			else
				pObj->dy = Max(pObj->dy - pObj->inertia, 0);

			if (pObj->dy == 0 && pObj->dead == false) {
				pObj->dy = 1 * _2X;
				pObj->dirY = DOWN;
			}
		}

		pObj->dy = Max(pObj->dy, 0);
		pObj->dy = pObj->dy * DIR(pObj->dirY);
	}

#ifdef DEBUG
	p[1] = pObj->dy;
#endif

chk:
	{
		int i;
		if (pObj->type == MAXX && pObj->motion == PO_C2_STOP0)
			motion = PO_C2_STOP1;

		if (motion >= 0)
			pObj->motion = motion;

		if (pObj->magnet) {
			OBJECT* mObj = &ao[pObj->magnet % 100];

			pObj->mx = false;
			pObj->playerRun = false;

			pObj->y -= 12 * _2X;

			if (pObj->magnet / 100) {
				if (!pObj->dy) {
					pObj->dirY = 1 - pObj->dirY;
					mObj->jumpFrame = Max(0, mObj->jumpFrame - 2);
				}

				i = (pObj->x > mObj->x) ? 24 * _2X : -24 * _2X;
				mObj->x += i;
				height = GetDistance(mObj, pObj);
				mObj->x -= i;
			}
			else {
				if (!pObj->dx) {
					pObj->dirX = 1 - pObj->dirX;
					mObj->jumpFrame = Max(0, mObj->jumpFrame - 2);
				}

				i = (pObj->y > mObj->y) ? 28 * _2X : -28 * _2X;
				mObj->y += i;
				height = GetDistance(mObj, pObj);
				mObj->y -= i;
			}

			pObj->y += 12 * _2X;

			if (height / 8 == false) {
				pObj->inertia = 0;
				pObj->status = MAGNET;
			}

			if (pObj->status == MAGNET) {
				if (is_key_released == false) {
					switch (playerMoveKey) {

					case AVK_1:
					case AVK_4:
					case AVK_7:
						pObj->dirF = LEFT;
						break;

					case AVK_3:
					case AVK_6:
					case AVK_9:
						pObj->dirF = RIGHT;
						break;
					}

					if (pObj->magnet / 100) {
						switch (playerMoveKey) {
						case AVK_1:
						case AVK_2:
						case AVK_3:
							pObj->dirY = UP;
							break;

						case AVK_8:
							pObj->dirY = DOWN;
							break;
						default:
							goto ELSE;
						}

						pObj->dy = 1 * _2X;
					}
					else {
						switch (playerMoveKey) {

						case AVK_1:
						case AVK_4:
						case AVK_7:
							pObj->dirX = LEFT;
							break;

						case AVK_3:
						case AVK_6:
						case AVK_9:
							pObj->dirX = RIGHT;
							break;
						default:
							goto ELSE;
						}

						pObj->dx = 1 * _2X;
					}

					pObj->motion = PO_C0_W0;
				}
				else {
				ELSE:

					if (pObj->magnet / 100) {
						pObj->dy = (Abs(pObj->y - 12 * _2X - mObj->y) > 1 * _2X) ? Max(height / 2, 1) * _2X : 0 * _2X;
						pObj->dirY = (pObj->y - 12 * _2X > mObj->y) ? UP : DOWN;
					}
					else {
						pObj->dx = (Abs(pObj->x - mObj->x) > 1 * _2X) ? Max(height / 2, 1) * _2X : 0 * _2X;
						pObj->dirX = (pObj->x > mObj->x) ? LEFT : RIGHT;
					}

					pObj->motion = PO_C0_N0;
				}

				pObj->inertia = 0;
			}
			else {
				pObj->motion = PO_C0_W0;

				if (pObj->magnet / 100) {
					pObj->dy = Min(pObj->dy, Min(height / 8, mObj->jumpFrame)) * _2X;

					if (pObj->y - 12 * _2X > mObj->y)
						pObj->inertia = (pObj->dirY) ? 2 * _2X : -2 * _2X;
					else
						pObj->inertia = (pObj->dirY) ? -2 * _2X : 2 * _2X;
				}
				else {
					pObj->dx = Min(pObj->dx, Min(height / 8, mObj->jumpFrame)) * _2X;

					if (pObj->x > mObj->x)
						pObj->inertia = (pObj->dirX) ? 2 * _2X : -2 * _2X;
					else
						pObj->inertia = (pObj->dirX) ? -2 * _2X : 2 * _2X;
				}
			}

			if (pObj->magnet / 100) {
				pObj->dx = Min(mObj->mainFrame, 8) * DIR(pObj->dirX) * _2X;

				height = pObj->status;

				pObj->dy -= pObj->inertia;
				pObj->dy = Max(pObj->dy, 0);
				pObj->dy = pObj->dy * DIR(pObj->dirY);	////로빈의 이동 간격을 결정

				if (!pObj->dy)
					pObj->motion = PO_C0_N0;
			}
			else {
				pObj->dy = Min(mObj->mainFrame, 8) * DIR(pObj->dirY);

				height = pObj->status;

				pObj->dx -= pObj->inertia;
				pObj->dx = Max(pObj->dx, 0);
				pObj->dx = pObj->dx * DIR(pObj->dirX);	////로빈의 이동 간격을 결정

				if (!pObj->dx)
					pObj->motion = PO_C0_N0;
			}
		}

		//어둠의 파편
		if (darkStone) {
			OBJECT* pDark = &ao[darkStone];

			pObj->status = WALK;
			pObj->motion = PO_C0_N0;

			//이동할 각도
			motion = (pDark->dirX == RIGHT) ? 340 : 20;

			pObj->y -= 12 * _2X;
			//각도만큼 평행변환
			pObj->x = pDark->x + (BC_mathCos1024(motion) * (pObj->x - pDark->x) >> 10) - (BC_mathSin1024(motion) * (pObj->y - pDark->y) >> 10);
			pObj->y = pDark->y + (BC_mathSin1024(motion) * (pObj->x - pDark->x) >> 10) + (BC_mathCos1024(motion) * (pObj->y - pDark->y) >> 10);

			//거리 계산
			i = Max(24 * _2X, GetDistance(pDark, pObj));
			pObj->y += 12 * _2X;

			if (i < 36 * _2X) {
				//거리가 짧다면 늘려준다.
				pObj->x = pDark->x + UpDiv((pObj->x - pDark->x) * (i + 2 * _2X), i);
				pObj->y = pDark->y + UpDiv((pObj->y - pDark->y) * (i + 2 * _2X), i);
				i += 2 * _2X;
			}

		}
		else {
			TileCheckX(pObj);

			//if (robinmap < ARENA1 || robin.hp > 0)
			TileCheckY(pObj);
		}

		if (height == MAGNET)
			pObj->status = MAGNET;
		else {
			if (pObj->inTile) {
				pObj->oldDy = pObj->dy;
				pObj->dy = Abs(pObj->dy);
			}
			else {
				switch (pObj->status) {
				case JUMP2:
				case JUMP3:
					if (pObj->jumpFrame >= JUMPFRAME) {
						pObj->jumpFrame = 0;
						pObj->dirY = DOWN;
						pObj->status = (pObj->status == JUMP2) ? THROUGH : THROUGH2;
					}
					break;
				case JUMP:
					if (pObj->jumpFrame >= JUMPFRAME) {
						pObj->jumpFrame = 0;
						pObj->dirY = DOWN;

						switch (TileCrash(pObj)) {
						case 0:
							pObj->status = FALL;
							break;
						case 1:
							pObj->status = THROUGH2;
							break;
						case 2:
							pObj->status = THROUGH;
							break;
						}
						//}
					}
					break;
				}
			}
		}

		pObj->frame++;

		//스킬시 암전
		if (obj == raidPlayer) {
			if (skillUsed > 0)
				skillUsed--;
			if (buffItemFrame > 0) {
				buffItemFrame--;
				if (buffItemFrame == 0) {
					buffItemUsed = 0;
				}
			}
		}
	}
}

int PlayerMove_Attack(OBJECT* pObj, int released)
{
	pObj->playerRun = false;

	if (robin.playtime % MOTIONDIV != 0)
		return false;

	pObj->attackFrame++;

	switch (pObj->attack) {
	case ATTACK_DOWN:
		//찍기공격
		if (pObj->type == ROBIN) {
			if (pObj->status == WALK) {
				//바닥에 닿은 경우
				pObj->attack = ATTACK_AFTERDOWN;
				pObj->attackFrame = ROBIN_ATTACK_AFTER_START;
				PlayMusic(M_KUNG);
				HitCountCheck(pObj);
				return PO_C0_DOA4;
			}
			break;
		}
		//case ATTACK_NORMAL:	//일반공격
		//case ATTACK_DASH:	//대쉬공격
		//case ATTACK_AIR:	//공중공격
		//case ATTACK_AFTERDOWN:	//찍기후 반동
	default:	//스킬 공격
		PlayerMove_SkillAttack(pObj, released);
		break;
	}

	return -1;
}

void PlayerMove_SkillAttack(OBJECT* pObj, int released)
{
	int i, j, cnt;
	int xy;
	const short* sPtr;
	ITEM* it = &pObj->equip[EQUIP_WEAPON];
	int collectionIdx = GetCollectionIdx(it->type, it->detail, it->grade);


	OBJECT* objPtr;

	GetMotionPtr(pObj);

	xy = skillMotion[pObj->attackFrame * 4 - 3];

	if (xy >> 6) {
		pObj->jumpFrame = (xy >> 6) - 1;

		if (xy & _DIRDOWN) {
			pObj->dirY = DOWN;
			pObj->status = FALL;
		}
		else {
			pObj->dirY = UP;
			pObj->status = JUMP;
		}
	}

	if (xy & 0x0F) {
		pObj->mx = true;
		pObj->pDx = pObj->dx = (xy & 0x0F) << 1;

		if (pObj->concentrate > 8) {
			pObj->pDx += pObj->concentrate / 3 * _2X;
			pObj->dx += pObj->concentrate / 3 * _2X;
		}

		if (xy & _DIROPPOSITE)
			pObj->dirX = 1 - pObj->dirF;
		else
			pObj->dirX = pObj->dirF;
	}
	else if (pObj->attack != ATTACK_DASH) {
		if (pObj->attack == ATTACK_AIR)
			pObj->pDx = pObj->dx = pObj->pDx * 2 / 3;
		else {
			pObj->mx = false;
			pObj->pDx = pObj->dx = 0;
		}
	}

	if (pObj->continueAttack == false && released == false && systemKey == AVK_5) {
		if (pObj->type != ROBIN || pObj->attackFrame > attackDelayFrame[pObj->type] + 3)
			PlayRelease(pObj);

	}

	switch (skillMotion[pObj->attackFrame * 4 - 2]) {
	case _WAIT2:
		if (pObj->continueAttack == false)
			pObj->attackFrame = charEtcData[WAIT1FRAME * TOTALPLAYER + pObj->cmf];
		else
	case _WAIT1:
		pObj->continueAttack = false;
		break;
	case _WAIT3:
		if (pObj->continueAttack == false)
			pObj->attackFrame = charEtcData[WAIT2FRAME * TOTALPLAYER + pObj->cmf];
		else
			pObj->continueAttack = false;
		break;
	case _ENDTOFALL:
		pObj->status = FALL2;
		//본드
	case _END:
		switch (drawHandle) {
		case MD_PLAY:
		case MD_BATTLE:
			pObj->concentrate = 0;

			if (pObj->attack >= ATTACK_SKILL) {
				ObjectSkillSetting(pObj);
			}

			pObj->attack = false;
			pObj->attackFrame = 0;
			pObj->turnPosition = COMING;//다시 제위치로 복귀
			//만약 소환이면
			if (GetObjFromPtr(pObj) == SOLDIER) {
				//솔져
				j = 0;
				if (pObj->type == MAXX) {
					for (i = BULLET; i < ENEMYUSEROBJ; i++) {
						if (ao[i].active == true)
							j++;
					}

					if (j == 0) {
						pObj->drawHandler = VANISHDRAW;
						pObj->moveHandler = VANISHMOVE;
						onceDmgUpdateFrame = 2 * FPS;
						pObj->frame = 0;
					}
					return;
				}
			}
			//만약 주인공이고 동료들에 의해 스킬이 발동되었다면
			else if (GetObjFromPtr(pObj) != turn && GetObjFromPtr(pObj) < TOTALCHAR && GetSonObjCnt(GetObjFromPtr(pObj)) == 0) {
				pObj->turnPosition = HERE;
				WhoIsNextTurn();
			}
#ifdef SPEEDTURN
			if (GetObjFromPtr(pObj) == turn && GetSonObjCnt(GetObjFromPtr(pObj)) == 0) {
				pObj->turnPosition = HERE;
				WhoIsNextTurn();
			}
#endif

			break;

		case MD_RAID:
			attackSequence = ATTACKSEQUENCE_ATTACKRESULT;
			attackDelay = ATTACKDELAY_RAIDMODE_START + 2 * FPS / ROULETTEDIV;
			break;
		case MD_BOSSRAID:
			attackSequence = ATTACKSEQUENCE_ATTACKRESULT;
			attackDelay = ATTACKDELAY_BOSSREWARD_START + 2 * FPS / ROULETTEDIV;
			break;
		}
		break;
	case _ADDBUFF:
		
#ifndef WARIGARI
		if (autoPlay == true && drawHandle == MD_PLAY) {
			BoxOpen();

		}
#endif

		for (i = 0; i < TOTALPLAYERBUFF; i++) {
			const unsigned short* ptrBuff = &buffData[i * 4];

			if (pObj->attackFrame == *ptrBuff) {
				pObj->buff[i] = *(ptrBuff + 1);
			}
		}

		pObj->concentrate = 0;

		pObj->attack = false;
		pObj->attackFrame = 0;

		pObj->turnPosition = HERE;
		WhoIsNextTurn();

		//attackSequence = ATTACKSEQUENCE_ATTACKRESULT;
		//attackDelay = attackDelayPerType[attackType];
		break;
	case _CONTINUE:
		pObj->concentrate = 0;
		break;
	case _EDGE3:
		PlayRelease(pObj);
		effect.edge = 3;
		break;
	case _SETFRAMEBYDX:
		//로빈 전용. 대시 블록이 60프레임용으로 2배가 되어 건너뛰는 칸도 2배다.
		pObj->attackFrame = skillStartFrame[ATTACK_DASH] + 2 * Min(4, 5 - pObj->pDx / 4);
		pObj->dx = pObj->pDx += 4 * _2X;
		break;
	case _SETFRAMEBYDX2:
		//맥스 전용. 대시 블록이 60프레임용으로 2배가 되어 건너뛰는 칸도 2배다.
		pObj->attackFrame = 1 + skillStartFrame[ATTACK_DASH] + 2 * Min(4, 5 - pObj->pDx / 4);
		pObj->dx = pObj->pDx += 7 * _2X;
		break;
	case _DXDECREASE4:
		pObj->pDx -= 4 * _2X;
		break;
	case _DXDECREASE2:
		//프레임이 2배인 대시용. 한 프레임당 감속을 절반으로 해 총 감속량을 지킨다.
		pObj->pDx -= 2 * _2X;
		break;
	case _WALKTOEND:
		if (pObj->status == WALK) {
			pObj->attack = false;

			pObj->turnPosition = COMING;
#ifndef WARIGARI
			if (autoPlay == true && drawHandle == MD_PLAY) {
				BoxOpen();
			}
#endif

		}
		break;
	case _ADDJUMPFRAME:
		pObj->jumpFrame++;
		break;
	case _ADDJUMPFRAME2:
		pObj->jumpFrame += 2;
		break;
	case _MINUSJUMPFRAME:
		pObj->jumpFrame--;
		break;
	case _FACEOPPOSITE:
		pObj->dirF = 1 - pObj->dirF;
		break;
	case _ADDBULLETROBIN:
		for (cnt = -1, i = BULLET; i < ENEMY; i++) {
			objPtr = &ao[i];
			if (!objPtr->active) {
				memset(objPtr, 0, sizeof(OBJECT));
				objPtr->active = true;
				objPtr->dirX = objPtr->dirF = pObj->dirF;
				objPtr->zoom = pObj->zoom;
				objPtr->motion = PO_C0_CRASH_BULLET;
				objPtr->moveHandler = BULLET3WAYMOVE;
				objPtr->drawHandler = NORMALDRAW;
				objPtr->x = pObj->x + 40 * DIR(pObj->dirF) * _2X;
				objPtr->y = pObj->y - 50 * _2X;
				objPtr->cmf = pObj->cmf;
				objPtr->status = -1;
				objPtr->target = GetObjFromPtr(pObj);
				break;
			}
		}
		break;
	case _ADDBULLET:
		for (cnt = -1, i = BULLET; i < ENEMY; i++) {
			objPtr = &ao[i];

			if (!objPtr->active) {

				//기본설정
				memset(objPtr, 0, sizeof(OBJECT));
				objPtr->active = true;
				objPtr->dirX = objPtr->dirF = pObj->dirF;
				objPtr->zoom = pObj->zoom;

				//배열 데이터 설정
				objPtr->motion = dianaBulletData[(pObj->attack - DIANA_SKILL_3WAY) * 5];
				objPtr->moveHandler = dianaBulletData[(pObj->attack - DIANA_SKILL_3WAY) * 5 + 1];
				objPtr->drawHandler = dianaBulletData[(pObj->attack - DIANA_SKILL_3WAY) * 5 + 2];
				objPtr->x = pObj->x + dianaBulletData[(pObj->attack - DIANA_SKILL_3WAY) * 5 + 3] * DIR(pObj->dirF);
				objPtr->y = pObj->y - dianaBulletData[(pObj->attack - DIANA_SKILL_3WAY) * 5 + 4];
				objPtr->cmf = pObj->cmf;
				objPtr->target = GetObjFromPtr(pObj);

				//개별 설정
				switch (pObj->attack) {
				case DIANA_SKILL_3WAY:
					if (cnt == 0)
						objPtr->x += DIR(pObj->dirF) * 12 * _2X;

					objPtr->status = cnt;
					objPtr->motion += cnt;
					objPtr->y += objPtr->status * 42 * _2X;
					cnt++;
					break;
				case DIANA_SKILL_BOMBSHOT:
					GetTile(objPtr);

					while (TileCrash(objPtr)) {
						objPtr->x -= DIR(objPtr->dirF) * TSIZE;
						GetTile(objPtr);
					};
					break;
				case DIANA_SKILL_GUIDEDSHOT:
					objPtr->dx = DIR(objPtr->dirF) * 5 * _2X;
					objPtr->dy = 3 * _2X - Random(7) * _2X;
					objPtr->status = 12 + Random(6);
					break;
				case DIANA_SKILL_SATELLITESHOT:
					objPtr->dirX = (objPtr->x - rx > DX / 2) ? LEFT : RIGHT;
					GetTile(objPtr);
					objPtr->y += GetObjHeight(objPtr);
					break;
				}

				if (cnt == 2 || pObj->attack != DIANA_SKILL_3WAY)
					break;
			}
		}
		break;
	case _ADDHEAL:
		cnt = GetEmptyObject(BULLET);
		objPtr = (&ao[cnt]);
		memset(objPtr, 0, sizeof(OBJECT));
		objPtr->active = true;
		objPtr->zoom = pObj->zoom;
		objPtr->cmf = pObj->cmf;
		objPtr->moveHandler = BULLETHEALMOVE;
		objPtr->drawHandler = BULLETHEALDRAW;
		objPtr->mom = GetObjFromPtr(pObj);

		attackSequence = ATTACKSEQUENCE_ATTACKRESULT;
		attackDelay = attackDelayPerType[attackType];
		break;
	case _DIRECTHEAL:
		pObj->attack = false;

		pObj->turnPosition = COMING;

#ifndef WARIGARI
		if (autoPlay == true && drawHandle == MD_PLAY) {
			BoxOpen();
		}
#endif

		PlusHp(pObj, RoundDiv(pObj->ps[PS_HP] * GetSkillValue(GetObjFromPtr(pObj), SKILL_ROBIN16), 100));

		if (GetObjFromPtr(pObj) == raidPlayer && skillUsed > 0) {
			skillInfoFrame = SKILLREMAINEDFRAME;
			skillUsed = SKILLREMAINEDFRAME;
		}

		if (!pObj->hpRestore)
			pObj->hpRestore = 1;

		attackSequence = ATTACKSEQUENCE_ATTACKRESULT;
		attackDelay = attackDelayPerType[attackType];
		break;
	case _ADDBOOMERANG:
		//기본설정
		sPtr = &maxxBoomerangData[(pObj->attack - ATTACK_NORMAL) * 7];
		cnt = GetEmptyObject(BULLET);
		objPtr = (&ao[cnt]);
		memset(objPtr, 0, sizeof(OBJECT));
		objPtr->active = true;
		objPtr->zoom = pObj->zoom * BATTLEZOOM;
		objPtr->type = pObj->type;
		objPtr->cmf = pObj->cmf;
		objPtr->attack = pObj->attack;
		objPtr->dirX = objPtr->dirF = pObj->dirF;
		objPtr->status = GetSkillLv(cnt, SKILL_MAXX2) / 2 + 1;
		objPtr->mom = objPtr->status;
		//맥스가 다수일경우 자신을 생성시킨 오브젝트에게 복귀될수있도록
		objPtr->target = GetObjFromPtr(pObj);

		//배열 데이터 설정
		objPtr->motion = maxxBoomerangData[(pObj->attack - ATTACK_NORMAL) * 7];
		objPtr->moveHandler = BULLETBOOMERANGMOVE;
		objPtr->drawHandler = BULLETBOOMERANGDRAW;
		objPtr->x = pObj->x + *(sPtr + 1) * DIR(pObj->dirF);
		objPtr->y = pObj->y + *(sPtr + 2);
		objPtr->dirY = (maxxBoomerangData[(pObj->attack - ATTACK_NORMAL) * 7 + 4] < 0 ? DOWN : UP);

		if (pObj->attack == ATTACK_NORMAL || pObj->attack == ATTACK_AIR) {
			sPtr = &normalboomerangData[GetSkillLv(GetObjFromPtr(pObj), SKILL_MAXX2) * 4] - 3;
		}

		objPtr->dx = *(sPtr + 3) * DIR(pObj->dirF);
		objPtr->dy = *(sPtr + 4);
		objPtr->hp = -*(sPtr + 5) * DIR(pObj->dirF);
		objPtr->maxhp = *(sPtr + 6);

		if (pObj->attack == ATTACK_AIR)
			objPtr->dy -= 2 * _2X;

		switch (objPtr->attack) {
		case MAXX_SKILL_HORMING:
			//유도미사일 사거리 제한 및 타겟 측정
			//i = GetClosestObj(&ao[cnt]);
			i = ao[PLAYER].target;

			if (i >= ENEMY && EnemyCheck(i) && DistanceCheck(&ao[cnt], &ao[i], 240 * _2X)) {
				objPtr->etc = 2;
				objPtr->attackFrame = i;
			}
			break;
		case MAXX_SKILL_CIRCLE:
			objPtr->etc = 4;
			break;
		case MAXX_SKILL_MEGA:
			objPtr->etc = 5;
			//objPtr->dx = 3 * _2X;
			break;
		default:
			if (Abs(objPtr->dx) < Abs(objPtr->dy))
				objPtr->etc = 1;
			break;
		}

		boomerangAway[objPtr->target] = cnt;
		objPtr->ps[PS_DMG] = objPtr->ps[PS_STR] = ao[objPtr->target].ps[PS_DMG];
		break;
	case _USERING:
		UseRing(pObj, ITEMPTR_EQUIP + GetObjFromPtr(pObj) * TOTALEQUIP + EQUIP_RING);
		pObj->attack = false;

		pObj->turnPosition = COMING;
#ifndef WARIGARI
		if (autoPlay == true && drawHandle == MD_PLAY) {
			BoxOpen();
		}
#endif

		break;
	case _ADDITEMBULLET:
		AddObject(&ao[GetEmptyObject(BULLET)], pObj, ADDOBJ_ITEMBULLET);
		break;
	case _ADDMON:
		objPtr = &ao[SOLDIER];
		objPtr->type = skillData[objPtr->currentSkill * SKILLDATASIZE + SKILLDATA_OBJECTINFO];
		objPtr->zoom = SUMMONZOOM * 4;
		SetEnemy(objPtr);
		objPtr->moveHandler = null;
		objPtr->nx = objPtr->x = DX / 2;
		objPtr->ny = objPtr->y = ao[ROBIN].y + monXYGap[(ao[skillData[objPtr->currentSkill * SKILLDATASIZE + SKILLDATA_TARGET]].type - 3) * 2 + 1];

		switch (objPtr->type) {
		case ENEMY_FOGRA:
		case ENEMY_FOGRA_RED:
		case ENEMY_FOGRA_BLUE:
		case ENEMY_FOGRA_PURPLE:
		case ENEMY_FOGRA_GREEN:
		case ENEMY_FOGRA_GOLD:
		case ENEMY_FOGRA_BLACK:
			objPtr->y += 88 * _2X;
			break;
		case ENEMY_BAHAMUT:
		case ENEMY_BAHAMUT_RED:
		case ENEMY_BAHAMUT_BLUE:
		case ENEMY_BAHAMUT_PURPLE:
		case ENEMY_BAHAMUT_GREEN:
		case ENEMY_BAHAMUT_GOLD:
		case ENEMY_BAHAMUT_BLACK:
			objPtr->y -= 32 * _2X;
			break;
		case ENEMY_CASTLE_BOSS3:
		case ENEMY_CASTLE_BOSS3_RED:
		case ENEMY_CASTLE_BOSS3_BLUE:
		case ENEMY_CASTLE_BOSS3_PURPLE:
		case ENEMY_CASTLE_BOSS3_GREEN:
		case ENEMY_CASTLE_BOSS3_GOLD:
		case ENEMY_CASTLE_BOSS3_BLACK:
			objPtr->y += 10 * _2X;
			break;
		}
		objPtr->dx = objPtr->dy = 0;
		objPtr->dirX = objPtr->dirF = RIGHT;
		objPtr->active = true;

		objPtr->target = ao[PLAYER].target;

		memset(&cardMark, 0, sizeof(cardMark));
		ao[PLAYER].attack = false;
		ao[PLAYER].attackFrame = false;

		//objPtr->moveHandler = REGENMOVE;
		//if (pObj->x <= pObj->nx) {objPtr->drawHandler = REGENDRAW;
		break;
	}

	if (pObj->cmf == ROBIN && pObj->attackFrame == 30 + ROBIN_ATTACK_DELAY) {
		pObj->status = FALL;
		pObj->jumpFrame = JUMPFRAME;
		pObj->dirY = DOWN;
	}
}

bool IsSkillUsable(OBJECT* pObj)
{
	int i, j;
	for (i = 0; i < MAXCHARSKILL; i++) {
		if (pObj->getSkillList[i] != EMPTY) {
			if (skillData[SKILLDATASIZE * pObj->getSkillList[i]] > PASSIVE) {
				for (j = 0; j < MAXHOTKEY; j++) {
					if (pObj->hotKey[j].idx == pObj->getSkillList[i]) {
						temp = j;
						break;
					}
				}

				if (pObj->hotKey[temp].frame == 0)
					return true;
			}
		}
	}
	return false;
}

void SetPlayerMotion(OBJECT* pObj)
{
	int tempMotion = pObj->motion;

	GetMotionPtr(pObj);

	//죽었을때 모션
	if (pObj->dead == true) {
		pObj->motion = deadMotion[pObj->type * 8 + Min(7, pObj->deadFrame / 3)];

		if (pObj->inTile && (pObj->motion == PO_C0_KNEE0 || pObj->motion == PO_C0_DIE0))
			pObj->motion = PO_C0_DROWN;

		pObj->deadFrame++;

		return;
	}
	else if (returnFrame) {
		pObj->motion = PO_C0_WARP0 + (returnFrame - 1) % 12;
		return;
	}

	switch (pObj->attack) {
	case 0:

		switch (pObj->motion) {
		case PO_C0_W0:
		case PO_C0_R0:
			if (pObj->status == GLIDE) {
				pObj->motion = PO_C0_HAPPY0 + (pObj->frame / MOTIONDIV % 16) / 8 * 3;
				break;
			}

			if (pObj->frame / MOTIONDIV % 2 == 1) {
				pObj->motion++;
				break;
			}
		case PO_C0_N0:
		case PO_C1_FIREN0:
		case PO_C1_FIREW0:
		case PO_C1_FIREJU0:
			pObj->motion += (pObj->frame / 2 / MOTIONDIV % 4);
			break;
		case PO_C0_SWIM0:
			if (pObj->dx + pObj->dy > 3)
				pObj->motion += (pObj->frame / 2 / MOTIONDIV % 2 == 1 ? 1 : pObj->frame / 2 / MOTIONDIV % 4);
			else
				pObj->motion += ((pObj->frame / 2 / MOTIONDIV) % 2 == 1 ? 1 : (pObj->frame / 2 / MOTIONDIV) % 4);
			break;
		}

		if (pObj->debuf[KNOCKBACK])
			pObj->motion = (pObj->debuf[KNOCKBACK] > 3) ? PO_C0_SURPRISE1 : PO_C0_KNEE0;
		else if (pObj->debuf[STUN])
			pObj->motion = stunMotion[pObj->debuf[STUN] % 10];
		break;
	case ATTACK_DOWN:
		//찍기공격
		if (pObj->type == ROBIN) {
			pObj->motion = Min(PO_C0_DOA3, PO_C0_DOA0 - 1 + pObj->attackFrame);

			if (pObj->motion == PO_C0_DOA0)
				PlayMusic(M_DOWN);
		}
		else {
			pObj->motion = skillMotion[(pObj->attackFrame - 1) * 4];

			if (skillMotion[(pObj->attackFrame - 1) * 4 + 3] != 0) {
				if (GetObjFromPtr(pObj) == raidPlayer)
					audioVolume[skillMotion[(pObj->attackFrame - 1) * 4 + 3]] = 0.5f;
				else

					audioVolume[skillMotion[(pObj->attackFrame - 1) * 4 + 3]] = Max(0.1f, 0.5f - 0.5f * (GetDistance(&ao[raidPlayer], pObj) / DX));

				PlayMusic(skillMotion[(pObj->attackFrame - 1) * 4 + 3]);
			}
		}
		break;
	case ATTACK_AFTERDOWN:
		//바닥 효과 모션 셋팅
		if (pObj->attackFrame == ROBIN_ATTACK_AFTER_START)
			break;

		if (pObj->attackFrame < ROBIN_ATTACK_AFTER_START + 3) {
			pObj->motion = (pObj->attackFrame < ROBIN_ATTACK_AFTER_START + 2) ? PO_C0_DOAEFFECT0 : PO_C0_DOAEFFECT1;
			InitMotion(pObj);

			//그려주기
			DrawPlayer(pObj, pObj->motion, pObj->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - pObj->y + GetObjHeight(pObj) - ry + OBJIMGGAP, 0, pObj->zoom, false, false, false);

			//본체 모션 복구
			pObj->motion = tempMotion;
		}
	default:
		pObj->motion = skillMotion[(pObj->attackFrame - 1) * 4];

		if (skillMotion[(pObj->attackFrame - 1) * 4 + 3] != 0) {
			if (GetObjFromPtr(pObj) == raidPlayer)
				audioVolume[skillMotion[(pObj->attackFrame - 1) * 4 + 3]] = 0.5f;
			else

				audioVolume[skillMotion[(pObj->attackFrame - 1) * 4 + 3]] = Max(0.1f, 0.5f - 0.5f * (GetDistance(&ao[raidPlayer], pObj) / DX));
			PlayMusic(skillMotion[(pObj->attackFrame - 1) * 4 + 3]);

			audioVolume[skillMotion[(pObj->attackFrame - 1) * 4 + 3]] = 0.3f;
		}

		break;
	}

	InitMotion(pObj);
}

void OutOfSled(void)
{
	ao[PLAYER].moveHandler = PLAYERMOVE;
	ao[PLAYER].jumpFrame = 1;
	ao[PLAYER].status = JUMP;
	ao[PLAYER].dirY = UP;
	ao[PLAYER].onSled = 0;
}

void PlayerSledMove(OBJECT* pObj)
{
	int released = ((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID) && pObj->dead == false ? key_released : true);

	if (robin.playtime % 4 == 0) {
		if (pObj->x < ao[pObj->onSled].x)
			pObj->x += 1 * _2X;
		else if (pObj->x > ao[pObj->onSled].x)
			pObj->x -= 1 * _2X;
	}

	pObj->motion = (robin.playtime / MOTIONDIV / 2 % 2 == 0) ? PO_C0_HAPPY0 : PO_C0_HAPPY3;

	//썰매에 타고 있는지 체크한다.
	pObj->y += 8 * _2X;

	if (ObjCrash(pObj, &ao[pObj->onSled]) == false) {
		pObj->y -= 8 * _2X;
		OutOfSled();

		return;
	}

	pObj->y -= 8 * _2X;

	if (!released) {
		//얼굴 방향 조정
		switch (systemKey) {

		case AVK_1:
		case AVK_4:
		case AVK_7:
			pObj->dirF = LEFT;
			break;

		case AVK_3:
		case AVK_6:
		case AVK_9:
			pObj->dirF = RIGHT;
			break;
		}
	}
}

void PlayerGolemMove(OBJECT* pObj)
{
	int released = ((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID) && pObj->dead == false ? key_released : true);
	int obj = GetObjFromPtr(pObj);

	pObj->playerRun = false;

	if (pObj->invincible)
		pObj->invincible--;

	if (pObj->dead == true) {
		switch (pObj->etc) {
		case GOLEM_DIEREADY:
			if (pObj->status == WALK)
				pObj->etc = GOLEM_DIEMOTION;
			break;
		case GOLEM_DIEMOTION:
			if (pObj->motion >= PO_C26_DIE2)
				pObj->etc = GOLEM_DIE;
			break;
		case GOLEM_DIE:
			break;
		}

		return;
	}
	else if (pObj->debuf[KNOCKBACK] || pObj->debuf[STUN]) {
		effect.alpha = 0;
		pObj->attack = false;

		pObj->turnPosition = COMING;
#ifndef WARIGARI
		if (autoPlay == true && drawHandle == MD_PLAY) {
			BoxOpen();
		}
#endif
		pObj->concentrate = 0;

		switch (pObj->status) {
		case JUMP:
			pObj->jumpFrame = 0;
			pObj->status = FALL;
			pObj->dirY = DOWN;
			break;
		default:
			if (pObj->jumpFrame < JUMPFRAME + 1)
				pObj->dy = jump[JUMPFRAME - pObj->jumpFrame];
			else
				pObj->dy = FREEFALL;

			pObj->jumpFrame++;
			break;
		}

		pObj->playerRun = false;

		if (pObj->debuf[KNOCKBACK]) {
			pObj->dirX = 1 - pObj->dirF;
			pObj->dx = DIR(pObj->dirX) * Min(15, (pObj->debuf[KNOCKBACK] - 2) * 4) * _2X;
			pObj->debuf[KNOCKBACK]--;

			goto chk;
		}
		else {
			pObj->dx = 0;
			pObj->debuf[STUN]--;

			goto chk;
		}
	}

	if (pObj->attack && pObj->status != WALK) {
		pObj->attack = false;
		pObj->turnPosition = COMING;
#ifndef WARIGARI
		if (autoPlay == true && drawHandle == MD_PLAY) {
			BoxOpen();
		}
#endif
	}

	if (pObj->attack == false) {
		if (!pObj->attacked && !released) {
			switch (systemKey) {

			case AVK_7:
				if (option.hotSlot == true)
					break;
			case AVK_1:
			case AVK_4:
				pObj->dirF = pObj->dirX = LEFT;
				break;

			case AVK_9:
				if (option.hotSlot == true)
					break;
			case AVK_3:
			case AVK_6:
				pObj->dirF = pObj->dirX = RIGHT;
				break;
			}
		}

		if (released) {
			pObj->mx = false;
			pObj->my = false;
		}
		else {
			switch (systemKey) {
			case AVK_1:
			case AVK_3:
			case AVK_2:
				if (pObj->status == WALK) {
					//보통 점프
					pObj->dirY = UP;
					pObj->my = true;
					pObj->status = JUMP;
					pObj->jumpFrame = -(JUMPFRAME - 1);
					pObj->frame = 0;
				}
				break;
			}

			pObj->mx = (systemKey == AVK_2 || systemKey == AVK_8) ? false : true;
		}
	}

chk:
	//모션 정하기
	if (pObj->attack) {
		pObj->etc = GOLEM_SPEEDATTACK;

		if (pObj->frame == 9) {
			pObj->attack = false;

			pObj->turnPosition = COMING;
#ifndef WARIGARI
			if (autoPlay == true && drawHandle == MD_PLAY) {
				BoxOpen();
			}
#endif
		}
	}
	else {
		switch (pObj->status) {
		case WALK:
			if (pObj->etc == -2) {
				pObj->motion = PO_C26_LANDING0 - 1 + pObj->frame;

				if (pObj->frame == 3)
					pObj->etc = GOLEM_NEUTRAL;

				pObj->dx = 0;
			}
			else {
				if (pObj->mx) {
					pObj->etc = GOLEM_MOVE;

					if (pObj->frame % 5 == 1) {
						if (obj == raidPlayer || ao[obj].soldier == true || (obj >= BULLET && obj < ENEMY && (ao[obj].target == PLAYER || ao[ao[obj].target].soldier == true)))
							effect.shake = 5;
						//EffectSound(M_KUNG);

						PlayMusic(M_KUNG);
					}
				}
				else
					pObj->etc = GOLEM_NEUTRAL;
			}
			break;
		case JUMP:
		case JUMP2:
		case JUMP3:
			pObj->etc = GOLEM_JUMP;

			if (pObj->frame == 2) {
				if (obj == raidPlayer || ao[obj].soldier == true || (obj >= BULLET && obj < ENEMY && (ao[obj].target == PLAYER || ao[ao[obj].target].soldier == true)))
					effect.shake = 3;
				EffectSound(M_KUNG);
			}
			else if (pObj->frame >= 10) {
				pObj->jumpFrame = 0;
				pObj->dirY = DOWN;
				pObj->status = FALL;
			}
			break;
		default:
			pObj->etc = -1;
			pObj->dx = 6 * _2X * DIR(pObj->dirX);

			if (pObj->jumpFrame < JUMPFRAME)
				pObj->dy = jump[JUMPFRAME - 1 - pObj->jumpFrame];
			else
				pObj->dy = FREEFALL;

			pObj->motion = PO_C26_JD1;
			pObj->jumpFrame++;
			break;
		}
	}

	if (pObj->attack == 0 && pObj->ax) {
		pObj->ax = 0;
		pObj->ay = 0;
	}

	switch (pObj->status) {
	case JUMP2:
	case JUMP3:
		if (pObj->jumpFrame >= JUMPFRAME) {
			pObj->jumpFrame = 0;
			pObj->dirY = DOWN;
			pObj->status = (pObj->status == JUMP2) ? THROUGH : THROUGH2;
		}
		break;
	case JUMP:
		if (pObj->jumpFrame >= JUMPFRAME) {
			pObj->jumpFrame = 0;
			pObj->dirY = DOWN;

			switch (TileCrash(pObj)) {
			case 0:
				pObj->status = FALL;
				break;
			case 1:
				pObj->status = THROUGH2;
				break;
			case 2:
				pObj->status = THROUGH;
				break;
			}
		}
		break;
	}
}

void PlayerHandMove(OBJECT* pObj)
{
	pObj->playerRun = false;

	if (pObj->invincible)
		pObj->invincible--;

	// 활강중일때 풀어주고
	if (ao[GetClosestObj(pObj)].status == GLIDE)
		ao[GetClosestObj(pObj)].status = FALL;

	if (pObj->attack && pObj->status != WALK) {
		pObj->attack = false;

		pObj->turnPosition = COMING;
#ifndef WARIGARI
		if (autoPlay == true && drawHandle == MD_PLAY) {
			BoxOpen();
		}
#endif
	}

	if (!pObj->attacked) {
		switch (systemKey) {

		case AVK_7:
			if (option.hotSlot == true)
				break;

		case AVK_1:
		case AVK_4:
			pObj->dirF = pObj->dirX = LEFT;
			ao[pObj->mom].frame += 10;
			break;

		case AVK_9:
			if (option.hotSlot == true)
				break;

		case AVK_3:
		case AVK_6:
			pObj->dirF = pObj->dirX = RIGHT;
			ao[pObj->mom].frame += 10;
			break;
		}
	}

	pObj->motion = PO_C0_SURPRISE0;
	pObj->x = ao[pObj->mom].x;
	pObj->y = ao[pObj->mom].y - 10 * _2X;
	InitMotion(pObj);
	//Playermove 손가락 덧대서 그리기
	//Player가 바닥에 있을때 잡히지 않음.
}
//적몬스터를 아군으로 쓸 때
void PlayerEnemyMove(OBJECT* pObj)
{
	const signed short* tPtr;
	int loop = false;
	int ret;
	int cmp;
	int i;
	int distance;
	int distance_short;
	int hpInc;
	int obj = GetObjFromPtr(pObj);

	// 맵 밖으로 벗어나면 몬스터들 제거

START:
	tPtr = cmf_status_data[pObj->cmf][pObj->etc];

	if (tPtr == 0 || *tPtr == 0)
		goto END;

	ret = *tPtr;

	if (!pObj->target) {
		//진짜 적이면 아군을 공격한다.
		if (obj >= ENEMY) {
			distance = DX;
			for (i = PLAYER; i < TOTALCHAR; i++) {
				if (Abs(ao[i].x - pObj->x) < distance && ao[i].active == true && ao[i].dead == false) {
					distance = Abs(ao[i].x - pObj->x);
					pObj->target = i;
				}
			}
		}
		//아군몬스터면 적을 공격한다.
		else if (obj < PLAYERALL) {
			distance_short = distance = rw * TSIZE;
			//몬스터의 타겟도 주인공의 타겟을 따라간다.
			pObj->target = ao[PLAYER].target;
			/*
			for (i = ENEMY; i < NEUTRAL; i++) {
				if (Abs(ao[i].x - pObj->x) < distance && ao[i].active == true && ao[i].dead == false) {
					distance = Abs(ao[i].x - pObj->x);
					if (distance < distance_short) {
						distance_short = distance;
						pObj->target = i;
					}
				}
			}
			*/
		}
	}
	else if (pObj->target) {

		if (obj < PLAYERALL && (ao[pObj->target].active == false || ao[pObj->target].dead == true)) {
			pObj->target = false;
		}
		//적 몬스터가 죽으면 타겟을 재설정한다. 
		for (i = ENEMY; i < NEUTRAL; i++)
			if (ao[i].active == true && ao[i].dead == false) {
				pObj->target = i;
				break;
			}
	}

	if (obj < PLAYERALL) {
		pObj->dirF = pObj->dirX = (pObj->x < ao[pObj->target].x) ? RIGHT : LEFT;
	}
	else {
		switch ((*(tPtr + 1)) / 64) {
		case 1:
			//주인공방향
			if (pObj->frame % ret == 0)
				pObj->dirF = pObj->dirX = (pObj->x < ao[pObj->target].x) ? RIGHT : LEFT;
			break;
		case 2:
			//랜덤방향
			if (pObj->frame == 0)
				pObj->dirF = pObj->dirX = Random(2);
			break;
		case 3:
			//반대방향
			if (pObj->frame == 0)
				pObj->dirF = pObj->dirX = (pObj->x > ao[pObj->target].x) ? RIGHT : LEFT;
			break;
		}
	}

	if (pObj->frame % ret == 0) {
		switch (*(tPtr + 1) % 64) {
		case SET_MAINFRAME_RANDOM8:
			pObj->mainFrame = 16 + Random(8);
			break;
		case SET_MAINFRAME_RANDOM12:
			pObj->mainFrame = 24 + Random(12);
			break;
		case RECOVER_HP:
			//if (Random(10) == 0)
			hpInc = Max(1, pObj->maxhp / 1000);
			pObj->hp += hpInc;
			break;
		}
	}

	//Motion
	tPtr += (2 + (pObj->frame % ret));
	pObj->motion = *tPtr;

	//DX
	tPtr += ret;

	if (*tPtr >= 120) {
		ao[pObj->target].y -= 50 * _2X;
		GotoObj(&ao[pObj->target], pObj, (*tPtr - 120) * _2X);
		ao[pObj->target].y += 50 * _2X;
	}
	else if (*tPtr >= 100) {
		GotoObj(&ao[pObj->target], pObj, (*tPtr - 100) * _2X);
	}
	else {
		//해파리일경우 점프중에만 움직인다.
		if (pObj->type == ENEMY_JELLYFISH
			|| pObj->type == ENEMY_JELLYFISH_RED
			|| pObj->type == ENEMY_JELLYFISH_BLUE
			|| pObj->type == ENEMY_JELLYFISH_PURPLE
			|| pObj->type == ENEMY_JELLYFISH_GREEN
			|| pObj->type == ENEMY_JELLYFISH_GOLD
			|| pObj->type == ENEMY_JELLYFISH_BLACK) {
			if (pObj->dirY == UP)
				pObj->dx = *tPtr * DIR(pObj->dirX);
		}
		else {
			pObj->dx = *tPtr * DIR(pObj->dirX);
		}

		//DY
		tPtr += ret;

		if (*tPtr >= 100) {
			//해파리일경우 플레이어가 자기보다 20px 이상 위에있을때만 점프를 뛴다
			if ((pObj->type == ENEMY_JELLYFISH
				|| pObj->type == ENEMY_JELLYFISH_RED
				|| pObj->type == ENEMY_JELLYFISH_BLUE
				|| pObj->type == ENEMY_JELLYFISH_PURPLE
				|| pObj->type == ENEMY_JELLYFISH_GREEN
				|| pObj->type == ENEMY_JELLYFISH_GOLD
				|| pObj->type == ENEMY_JELLYFISH_BLACK)
				&& ao[pObj->target].y - pObj->y - 20 * _2X > 0)
				pObj->dy = 0;
			else {
				pObj->dirY = UP;
				pObj->my = true;
				pObj->status = JUMP;
				pObj->jumpFrame = *tPtr - 100;
			}
		}
		else
			pObj->dy = *tPtr;
	}

	EnemyMove_AddObj2(pObj);
	EnemyMove_AddObj(pObj);

	if (loop == false && pObj->frame % ret == 0) {
		tPtr = cmf_change_data[pObj->cmf];

		while (*tPtr >= 0) {
			if (*tPtr == pObj->etc) {
				ret = 0;

				switch (*(tPtr + 2)) {
				case 0:
					ret++;
					break;
				case DISTANCE_CHECK_XY:
					//주의 : y축의 값을 8 미만으로 해야함
					if (ao[pObj->target].dead == false && DistanceCheck(&ao[pObj->target], pObj, TSIZE * (*(tPtr + 3) / 8)) == true && Abs(pObj->y - ao[pObj->target].y) < TSIZE * (*(tPtr + 3) % 8))
						ret = 1;
					break;
				case DISTANCE_OUT_XY:
					if (ao[pObj->target].dead == true || DistanceCheck(&ao[pObj->target], pObj, TSIZE * (*(tPtr + 3) / 8)) == false || Abs(pObj->y - ao[pObj->target].y) >= TSIZE * (*(tPtr + 3) % 8))
						ret = 1;
					break;
				case ATTACK_CHECK:
					for (i = 0; i < ENEMY; i++) {
						if (ao[i].active && ObjCrash(pObj, &ao[i]) == true) {
							ret = 1;
							break;
						}
					}
					break;
				case COMPARE_FRAME:
					switch (*(tPtr + 3)) {
					case EQUAL_MAINFRAME:
						cmp = pObj->mainFrame;
						break;
					default:
						cmp = *(tPtr + 3);
						break;
					}

					if (pObj->frame >= cmp)
						ret = 1;
					break;
				case COMPARE_LESSHP:
					if (pObj->hp * 100 / pObj->maxhp < *(tPtr + 3))
						ret = 1;
					break;
				case COMPARE_MOREHP:
					if (pObj->hp * 100 / pObj->maxhp >= *(tPtr + 3))
						ret = 1;
					break;
				case COMPARE_LESSFRAME:
					if (pObj->attackFrame <= *(tPtr + 3))
						ret = 1;
					break;
				case DIR_SAME_PLAYER:
					if (ao[pObj->target].dirX == pObj->dirX)
						ret = 1;
					break;
				case DIR_DIFFER_PLAYER:
					if (ao[pObj->target].dirX != pObj->dirX)
						ret = 1;
					break;
				}

				if (ret) {
					switch (*(tPtr + 4)) {
					default:
						ret = 2;
						break;
					case DISTANCE_CHECK_XY:
						if (ao[pObj->target].dead == false && DistanceCheck(&ao[pObj->target], pObj, TSIZE * (*(tPtr + 5) / 8)) == true && Abs(pObj->y - ao[pObj->target].y) < TSIZE * (*(tPtr + 5) % 8) && ((pObj->x >= ao[pObj->target].x && pObj->dirF == LEFT) || (pObj->x < ao[pObj->target].x && pObj->dirF == RIGHT)))
							ret = 2;
						break;
					case RANDOM:
						if (Random(100) < *(tPtr + 5))
							ret = 2;
						break;
					}
				}

				if (ret == 2) {
					if ((pObj->type == ENEMY_CASTLE_BOSS3
						|| pObj->type == ENEMY_CASTLE_BOSS3_RED
						|| pObj->type == ENEMY_CASTLE_BOSS3_BLUE
						|| pObj->type == ENEMY_CASTLE_BOSS3_PURPLE
						|| pObj->type == ENEMY_CASTLE_BOSS3_GREEN
						|| pObj->type == ENEMY_CASTLE_BOSS3_GOLD
						|| pObj->type == ENEMY_CASTLE_BOSS3_BLACK)
						&& *(tPtr + 1) == CASTLEBOSS3_IMPALE) {
						if (pObj->attack == 0)
							pObj->etc = *(tPtr + 1);
						else if (pObj->attack == 3)
							pObj->etc = CASTLEBOSS3_IMPALE3;
						else
							pObj->etc = CASTLEBOSS3_IMPALE2;
					}
					else
						pObj->etc = *(tPtr + 1);
					loop = true;
					pObj->frame = 0;
					pObj->mainFrame = 0;

					goto START;
				}
			}

			tPtr += STATUS_CHANGE_LENGTH;
		}
	}

END:
	EnemyMoveCommon(pObj);
}

void EnemyMove(OBJECT* pObj)
{
	const signed short* tPtr;
	int loop = false;
	int ret;
	int cmp;
	int i;
	int distance;
	int obj = GetObjFromPtr(pObj);

	// 맵 밖으로 벗어나면 몬스터들 제거

START:
	tPtr = cmf_status_data[pObj->cmf][pObj->etc];

	if (tPtr == 0 || *tPtr == 0)
		goto END;

	ret = *tPtr;

	if ((ao[pObj->target].active == false || ao[pObj->target].dead == true) && pObj->target < TOTALCHAR) {
		//진짜 적이면 아군을 공격한다.
		distance = DX;

		for (i = PLAYER; i < TOTALCHAR; i++) {
			if (Abs(ao[i].x - pObj->x) < distance && ao[i].active == true && ao[i].dead == false) {
				distance = Abs(ao[i].x - pObj->x);
				pObj->target = i;
			}
		}

		//모든 캐릭터가 죽었다면
		if (!pObj->target)
			pObj->target = NEUTRAL;
	}

	//주인공방향
	if (pObj->frame % ret == 0)
		pObj->dirF = pObj->dirX = (pObj->x < ao[pObj->target].x) ? RIGHT : LEFT;

	if (pObj->frame % ret == 0) {
		//switch (*(tPtr + 1)) {
		switch (*(tPtr + 1) & 0x3F) {
		case SET_MAINFRAME_RANDOM8:
			pObj->mainFrame = 8 + Random(8);
			break;
		case SET_MAINFRAME_RANDOM12:
			pObj->mainFrame = 12 + Random(12);
			break;
			//case RECOVER_HP:
			//	if (Random(10) == 0)
			//		pObj->hp += pObj->maxhp / 100;
			//	break;
		}
	}

	//Motion
	tPtr += (2 + (pObj->frame % ret));
	pObj->motion = *tPtr;


	//DX
	tPtr += ret;

	/*
	if (turn == obj)
		switch (turnPosition) {
		case HERE:
		case GOING:
		case THERE:
			pObj->dirF = pObj->dirX = (pObj->x < ao[pObj->target].x) ? RIGHT : LEFT;
			break;
		case COMING:
			pObj->dirF = pObj->dirX = (pObj->x > ao[pObj->target].x) ? RIGHT : LEFT;
			break;
		}
	else
		pObj->dirF = pObj->dirX = LEFT;
		*/



	if (*tPtr >= 120) {
		ao[pObj->target].y -= 50 * _2X;
		GotoObj(&ao[pObj->target], pObj, (*tPtr - 120) * _2X);
		ao[pObj->target].y += 50 * _2X;
	}
	else if (*tPtr >= 100) {
		GotoObj(&ao[pObj->target], pObj, (*tPtr - 100) * _2X);
	}
	else {
		//해파리일경우 점프중에만 움직인다.
		if (pObj->type == ENEMY_JELLYFISH
			|| pObj->type == ENEMY_JELLYFISH_RED
			|| pObj->type == ENEMY_JELLYFISH_BLUE
			|| pObj->type == ENEMY_JELLYFISH_PURPLE
			|| pObj->type == ENEMY_JELLYFISH_GREEN
			|| pObj->type == ENEMY_JELLYFISH_GOLD
			|| pObj->type == ENEMY_JELLYFISH_BLACK) {
			if (pObj->dirY == UP)
				pObj->dx = *tPtr * DIR(pObj->dirX);
		}
		else {
			if (GetDistance(pObj, &ao[pObj->target]) < GetAttackRange(obj))
				pObj->dx = 0;
			else
				pObj->dx = *tPtr * DIR(pObj->dirX);
		}

		//DY
		tPtr += ret;

		if (*tPtr >= 100) {
			//해파리일경우 플레이어가 자기보다 20px 이상 위에있을때만 점프를 뛴다
			if ((pObj->type == ENEMY_JELLYFISH
				|| pObj->type == ENEMY_JELLYFISH_RED
				|| pObj->type == ENEMY_JELLYFISH_BLUE
				|| pObj->type == ENEMY_JELLYFISH_PURPLE
				|| pObj->type == ENEMY_JELLYFISH_GREEN
				|| pObj->type == ENEMY_JELLYFISH_GOLD
				|| pObj->type == ENEMY_JELLYFISH_BLACK)
				&& ao[pObj->target].y - pObj->y - 20 * _2X > 0)
				pObj->dy = 0;
			else {
				pObj->dirY = UP;
				pObj->my = true;
				pObj->status = JUMP;
				pObj->jumpFrame = *tPtr - 100;
			}
		}
		else
			pObj->dy = *tPtr;
	}

	EnemyMove_AddObj2(pObj);
	EnemyMove_AddObj(pObj);

	if (loop == false && pObj->frame % ret == 0) {
		tPtr = cmf_change_data[pObj->cmf];

		while (*tPtr >= 0) {
			if (*tPtr == pObj->etc) {
				ret = 0;

				switch (*(tPtr + 2)) {
				case 0:
					ret++;
					break;
				case DISTANCE_CHECK_XY:
					//주의 : y축의 값을 8 미만으로 해야함
					if (ao[pObj->target].dead == false && Abs(ao[pObj->target].x - pObj->x) < TSIZE * (*(tPtr + 3) / 8) && Abs(pObj->y - ao[pObj->target].y) < TSIZE * (*(tPtr + 3) % 8))
						ret = 1;
					break;
				case DISTANCE_OUT_XY:
					if (ao[pObj->target].dead == true || DistanceCheck(&ao[pObj->target], pObj, TSIZE * (*(tPtr + 3) / 8)) == false || Abs(pObj->y - ao[pObj->target].y) >= TSIZE * (*(tPtr + 3) % 8))
						ret = 1;
					break;
				case ATTACK_CHECK:
					for (i = 0; i < ENEMY; i++) {
						if (ao[i].active && ObjCrash(pObj, &ao[i]) == true) {
							ret = 1;
							break;
						}
					}
					break;
				case COMPARE_FRAME:
					switch (*(tPtr + 3)) {
					case EQUAL_MAINFRAME:
						cmp = pObj->mainFrame;
						break;
					default:
						cmp = *(tPtr + 3);
						break;
					}

					if (pObj->frame >= cmp)
						ret = 1;
					break;
				case COMPARE_LESSHP:
					if (pObj->hp * 100 / pObj->maxhp < *(tPtr + 3))
						ret = 1;
					break;
				case COMPARE_MOREHP:
					if (pObj->hp * 100 / pObj->maxhp >= *(tPtr + 3))
						ret = 1;
					break;
				case COMPARE_LESSFRAME:
					if (pObj->attackFrame <= *(tPtr + 3))
						ret = 1;
					break;
				case DIR_SAME_PLAYER:
					if (ao[pObj->target].dirX == pObj->dirX)
						ret = 1;
					break;
				case DIR_DIFFER_PLAYER:
					if (ao[pObj->target].dirX != pObj->dirX)
						ret = 1;
					break;
				}

				if (ret) {
					switch (*(tPtr + 4)) {
					default:
						ret = 2;
						break;
					case DISTANCE_CHECK_XY:
						if (ao[pObj->target].dead == false && DistanceCheck(&ao[pObj->target], pObj, TSIZE * (*(tPtr + 5) / 16)) == true && Abs(pObj->y - ao[pObj->target].y) < TSIZE * (*(tPtr + 5) % 16) && ((pObj->x >= ao[pObj->target].x && pObj->dirF == LEFT) || (pObj->x < ao[pObj->target].x && pObj->dirF == RIGHT)))
							ret = 2;
						break;
					case RANDOM:
						if (Random(100) < *(tPtr + 5))
							ret = 2;
						break;
					}
				}

				if (ret == 2) {
					if ((pObj->type == ENEMY_CASTLE_BOSS3
						|| pObj->type == ENEMY_CASTLE_BOSS3_RED
						|| pObj->type == ENEMY_CASTLE_BOSS3_BLUE
						|| pObj->type == ENEMY_CASTLE_BOSS3_PURPLE
						|| pObj->type == ENEMY_CASTLE_BOSS3_GREEN
						|| pObj->type == ENEMY_CASTLE_BOSS3_GOLD
						|| pObj->type == ENEMY_CASTLE_BOSS3_BLACK)
						&& *(tPtr + 1) == CASTLEBOSS3_IMPALE) {
						if (pObj->attack == 0)
							pObj->etc = *(tPtr + 1);
						else if (pObj->attack == 3)
							pObj->etc = CASTLEBOSS3_IMPALE3;
						else
							pObj->etc = CASTLEBOSS3_IMPALE2;
					}
					else
						pObj->etc = *(tPtr + 1);
					loop = true;
					pObj->frame = 0;
					pObj->mainFrame = 0;

					goto START;
				}
			}

			tPtr += STATUS_CHANGE_LENGTH;
		}
	}

END:
	EnemyMoveCommon(pObj);
}

void MobiusMove(OBJECT* pObj)
{
	int i;
	int obj = GetObjFromPtr(pObj);
	//const signed short *tPtr;
	//int distanceX = Abs(ao[NearPlayer(pObj)].x - pObj->x);
	//int distanceY = Abs((ao[NearPlayer(pObj)].y - 24 * _2X * pObj->zoom) - pObj->y);
	//int distanceX = Abs(ao[NearPlayer(pObj)].x - pObj->x);
	//int distanceY = Abs((ao[NearPlayer(pObj)].y - 24 * _2X * pObj->zoom) - pObj->y);

	//int ret;

	//몬스터 스피드 조절
	//pObj->dx = 6 * DIR(pObj->dirX) * _2X * pObj->zoom;

	if (pObj->frame == 1) {
		//HP에 따라서 스테이터스셋팅
		if (pObj->hp <= pObj->maxhp / 4 * pObj->status) {
			pObj->status--;

			for (i = ENEMY; i < NEUTRAL; i++) {
				if (ao[i].active == true && ao[i].frame == pObj->status + 2) {
					ao[i].motion = PO_C38_NTAIL0;
					ao[i + 1].active = false;
					memset(&ao[i + 1], 0, sizeof(OBJECT));

					if (pObj->status == 0)
						memset(&ao[i], 0, sizeof(OBJECT));
				}
			}
		}

		if (AlivePlayerCnt() == false && (pObj->motion == PO_C38_NHEAD0 || pObj->motion == PO_C38_NHEAD1 || pObj->motion == PO_C38_NHEAD2 || pObj->motion == PO_C38_NHEAD3)) {
			GotoObj(&ao[NEUTRAL], pObj, SPEED_MIN);
			pObj->dirX = pObj->dirF = LEFT;
		}

	}

	if (pObj->frame == 1) {
		if (Abs(pObj->dx) >= 15)
			pObj->dirX = pObj->dirX == RIGHT ? LEFT : RIGHT;

		if (pObj->dirX == LEFT)
			pObj->dx++;
		else if (pObj->dirX == RIGHT)
			pObj->dx--;

		//방향전환 타이밍
		if (pObj->dx == 0)
			pObj->dirF = pObj->dirX == LEFT ? RIGHT : LEFT;

		//y축 가속, 감속 타이밍
		if (Abs(pObj->dy) >= 9)
			pObj->dirY = pObj->dirY == UP ? DOWN : UP;

		if (pObj->dirY == UP)
			pObj->dy++;
		else if (pObj->dirY == DOWN)
			pObj->dy--;

		// 플레이어가 100픽셀안에 있고, dx가 적당하다면 플레이어 방향으로 돌진하게해준다.
		if (GetDistance(&ao[pObj->target], pObj) <= 50 * _2X && pObj->dx > 2 && pObj->dx < 14) {
			if (pObj->dx < 0)
				pObj->dx = -8;
			else
				pObj->dx = 8;

			if (pObj->dy < 0)
				pObj->dy = -5;
			else
				pObj->dy = 5;

		}
		pObj->x += pObj->dx;
		pObj->y += pObj->dy;
	}
	else {

		if (pObj->mainFrame++ % 2 == 0) {
			i = GetObjFromPtr(pObj) - 1;
			pObj->x = ao[i].x;
			pObj->y = ao[i].y;
			pObj->dirF = ao[i].dirF;
		}
	}

	InitMotion(pObj);
}

void SlingMove(OBJECT* pObj)
{
	switch (pObj->etc) {
	case 2:
		pObj->motion = (pObj->frame / MOTIONDIV / 2) % 2 ? PO_C8_SHOT0 : PO_C8_SHOT1;//LarvaShotMotion[pObj->frame % 2];
		pObj->frame++;
	case 3:
		pObj->motion = PO_C35_STAR0 + (pObj->frame / MOTIONDIV / 2) % 4;
		pObj->frame++;
		pObj->y += pObj->dy;
		pObj->dy += 2 * _2X;
		break;
	case 4:
		if (pObj->frame == 0) {
			if (GetObjFromPtr(pObj) < PLAYERALL)
				GotoObj(&ao[pObj->target], pObj, SPEED_MIN);
			else
				GotoObj(&ao[NearPlayer(pObj)], pObj, SPEED_MIN);
			pObj->dy = Max(8 * _2X, pObj->dy);
		}

		pObj->x += pObj->dx;
		pObj->y += pObj->dy;
		pObj->frame++;
		break;
	case 5:
		pObj->dy = Min(pObj->dy++, 3) * _2X;
		pObj->y += pObj->dy;
		pObj->x += pObj->dx;
		pObj->frame++;

		if (pObj->frame > FPS)
			memset(pObj, 0, sizeof(OBJECT));
		break;
	default:
		pObj->x += pObj->dx * DIR(pObj->dirX);
		pObj->y += pObj->dy;
		pObj->dy += 3 * _2X;
		break;
	}

	if (pObj->type == ENEMY_CASTLE_BOSS3 ||
		pObj->type == ENEMY_CASTLE_BOSS3_RED ||
		pObj->type == ENEMY_CASTLE_BOSS3_BLUE ||
		pObj->type == ENEMY_CASTLE_BOSS3_PURPLE ||
		pObj->type == ENEMY_CASTLE_BOSS3_GREEN ||
		pObj->type == ENEMY_CASTLE_BOSS3_GOLD ||
		pObj->type == ENEMY_CASTLE_BOSS3_BLACK) {
		if (pObj->etc == 100) {
			(pObj->motion)++;

			if (pObj->motion > PO_C50_SHOT5) {
				memset(pObj, 0, sizeof(OBJECT));
				return;
			}
			InitMotion(pObj);
		}
		else if (pObj->y >= 264 * _2X) {
			pObj->dx = pObj->dy = 0;
			pObj->etc = 100;
		}
	}

	if (GetObjFromPtr(pObj) < PLAYERALL) {
		if (ObjCrash(&ao[pObj->target], pObj)) {
			AttackPlayerCheck(pObj);
			//memset(pObj, 0, sizeof(OBJECT));
		}
	}
	else {
		if (ObjCrash(&ao[NearPlayer(pObj)], pObj)) {
			if (NearPlayer(pObj) == NEUTRAL)
				AttackBoxCheck(pObj);
			else
				AttackRobin(GetObjFromPtr(pObj), NearPlayer(pObj));
			//memset(pObj, 0, sizeof(OBJECT));
		}
	}

	if (BoundaryCheck(pObj) == true)
		memset(pObj, 0, sizeof(OBJECT));

	if ((pObj->type == ENEMY_SLIME
		|| pObj->type == ENEMY_SLIME_RED
		|| pObj->type == ENEMY_SLIME_BLUE
		|| pObj->type == ENEMY_SLIME_PURPLE
		|| pObj->type == ENEMY_SLIME_GREEN
		|| pObj->type == ENEMY_SLIME_GOLD
		|| pObj->type == ENEMY_SLIME_BLACK)
		&& pObj->frame > FPS)
		memset(pObj, 0, sizeof(OBJECT));
}


void LightningMove(OBJECT* pObj, int speed)
{
	int tempx, tempy;

	tempx = pObj->x;
	tempy = pObj->y;

	pObj->x += pObj->dirX == RIGHT ? speed : -speed;
	pObj->y += pObj->dirY == DOWN ? speed : -speed;

	StuckMove(pObj);

	pObj->dx *= speed;
	pObj->dy *= speed;

	//pObj->x += ClearGap(pObj, 0);
	//pObj->y += ClearGap(pObj, 1);

	pObj->x = tempx;
	pObj->y = tempy;

	pObj->dirF = pObj->dirX;
	pObj->x += pObj->dx;
	pObj->y += pObj->dy;

	// PO_C22_LIGHTNING0 부분 아마 div파일 수정 전에는 에러날듯 합니다.
	// 에러나면 일단 (PO_C22_LIGHTNING0) 이거 나오는 부분 모두주석처리 해주세요
	pObj->motion = ((ao[pObj->mom].type == ENEMY_CRYSTAL
		|| ao[pObj->mom].type == ENEMY_CRYSTAL_RED
		|| ao[pObj->mom].type == ENEMY_CRYSTAL_BLUE
		|| ao[pObj->mom].type == ENEMY_CRYSTAL_PURPLE
		|| ao[pObj->mom].type == ENEMY_CRYSTAL_GREEN
		|| ao[pObj->mom].type == ENEMY_CRYSTAL_GOLD
		|| ao[pObj->mom].type == ENEMY_CRYSTAL_BLACK)
		? PO_C23_LIGHTNING0 : PO_C22_LIGHTNING0) + pObj->frame % 4;

	InitMotion(pObj);

	if (ObjCrash(&ao[pObj->target], pObj)) {
		ao[ao[GetObjFromPtr(pObj)].mom].mx--;

		ao[ao[GetObjFromPtr(pObj)].mom].etc = enemyAttackPattern[ao[ao[GetObjFromPtr(pObj)].mom].type * ATTACKPATTERNTOTALDATASIZE + 2 + ao[ao[GetObjFromPtr(pObj)].mom].currentSkill * ATTACKPATTERNDATASIZE + ao[ao[GetObjFromPtr(pObj)].mom].turnPosition];
		ao[ao[GetObjFromPtr(pObj)].mom].frame = 0;
		ao[ao[GetObjFromPtr(pObj)].mom].mainFrame = 0;
		ao[ao[GetObjFromPtr(pObj)].mom].turnPosition = COMING;
		attackSequence = ATTACKSEQUENCE_SLOT;
		//attackDelay = ENEMYDELAY_COIN_START;
		sequenceFrame = 0;

		AttackRobin(GetObjFromPtr(pObj), pObj->target);
		memset(pObj, 0, sizeof(OBJECT));
	}

	pObj->frame++;
}

void BugMove(OBJECT* pObj)
{
	// 캐릭터와 너무 붙지 않게
	if (pObj->frame % 15 == 0)
		pObj->dirF = pObj->dirX = pObj->x > ao[NearPlayer(pObj)].x ? LEFT : RIGHT;

	pObj->dx = Abs(pObj->dx) * DIR(pObj->dirX);
	TileCheckX2(pObj);
	//pObj->x += pObj->dx * DIR(pObj->dirX);

	pObj->motion = pObj->frame / MOTIONDIV / 2 % 2 == 0 ? PO_C50_BUG0 : PO_C50_BUG1;

	TileCheckY2(pObj);
	InitMotion(pObj);
	pObj->frame++;
}

void SkelGuideMove(OBJECT* pObj)
{
	if (pObj->status == 0 && (ObjCrash(pObj, &ao[NearPlayer(pObj)]) || pObj->frame == FPS * 2)) {
		pObj->frame = 0;
		pObj->status = 1;
	}

	if (pObj->status == 1) {
		pObj->dx = 0;
		pObj->dy = 0;

		if (pObj->frame == FPS) {
			memset(pObj, 0, sizeof(OBJECT));
			return;
		}
	}
	else {
		GotoObj(&ao[NearPlayer(pObj)], pObj, 6 * _2X);
		pObj->x += pObj->dx;
		pObj->y += pObj->dy;
	}

	pObj->motion = c31Shot60[pObj->frame / MOTIONDIV % 8];

	if (BoundaryCheck(pObj))
		memset(pObj, 0, sizeof(OBJECT));
	else {
		InitMotion(pObj);
		pObj->frame++;
	}

	if (pObj->status == 1)
		pObj->ax = pObj->ay = 0;
}

void CircleMove(OBJECT* pObj)
{
	int i, x, y;

	x = ((BC_mathSin1024(pObj->frame % 360) * 65) >> 10) * _2X * pObj->zoom;
	y = ((BC_mathCos1024(pObj->frame % 360) * 65) >> 10) * _2X * pObj->zoom;

	if (pObj->frame < FPS * 33) {
		for (i = ENEMY; i < NEUTRAL; i++) {
			if (ao[i].type == ENEMY_DEATH
				|| ao[i].type == ENEMY_DEATH_RED
				|| ao[i].type == ENEMY_DEATH_BLUE
				|| ao[i].type == ENEMY_DEATH_PURPLE
				|| ao[i].type == ENEMY_DEATH_GREEN
				|| ao[i].type == ENEMY_DEATH_GOLD
				|| ao[i].type == ENEMY_DEATH_BLACK)
				break;
		}

		pObj->x = ao[i].x + x;
		pObj->y = ao[i].y - (50 * (ao[pObj->mom].zoom / 2)) * _2X + y;

		pObj->dx = DIR(ao[i].dirX) * TSIZE * pObj->zoom;
	}
	else if (pObj->status == 2)
		pObj->x += pObj->dx;

	pObj->frame += 10;

	if (ObjCrash(pObj, &ao[NearPlayer(pObj)]))
		memset(pObj, 0, sizeof(OBJECT));
	else if (pObj->frame > FPS * 40)
		memset(pObj, 0, sizeof(OBJECT));
}

void SlimeMove(OBJECT* pObj, int speed)
{
	int tempx, tempy, i;
	int obj = GetObjFromPtr(pObj);
	int startObj;
	int endObj;

	if (obj < PLAYERALL) {
		startObj = BULLET;
		endObj = ENEMYUSEROBJ;
	}
	else {
		startObj = ENEMY;
		endObj = NEUTRAL;
	}

if (drawHandle == MD_PLAY) {
	if (turn == obj)
		switch (pObj->turnPosition) {
		case HERE:
		case GOING:
		case THERE:
			pObj->dirF = pObj->dirX = (pObj->x < ao[pObj->target].x) ? RIGHT : LEFT;
			break;
		case COMING:
			pObj->dirF = pObj->dirX = (pObj->x > ao[pObj->target].x) ? RIGHT : LEFT;
			break;
		}
	else
		pObj->dirF = pObj->dirX = LEFT;

	if (turn != ENEMY) {
		pObj->dx = 0;
		pObj->etc = 0;
		pObj->motion = pObj->frame % *cmf_status_data[pObj->cmf][pObj->etc];
	}
}

	if (pObj->attackFrame == 0) {
		//pObj->dirF = LEFT;
		tempx = pObj->x;
		tempy = pObj->y;

		pObj->x += pObj->dirX == RIGHT ? speed : -speed;
		pObj->y += pObj->dirY == DOWN ? speed : -speed;

		StuckMove(pObj);

		pObj->dx *= speed;
		pObj->dy *= speed;

		pObj->motion = slimeMotion[pObj->status];

		pObj->x = tempx;
		pObj->y = tempy;

		if (isDemo) {
			InitMotion(pObj);
			pObj->frame++;
			return;
		}

		//플레이어가 사거리에 들어오면
		if (DistanceCheck(&ao[NearPlayer(pObj)], pObj, TSIZE * 6) == true && Abs(pObj->y - ao[NearPlayer(pObj)].y) < TSIZE * 6) {
			i = pObj->status;
			pObj->attackFrame = 16;
			pObj->frame = 0;

			switch (pObj->status) {
			default:
				i = 0;
				pObj->motion = (24 + i * 6 + (6 - Min(pObj->attackFrame, 6)));
				break;
			case ROOF_LEFT:
			case ROOF_RIGHT:
				i = 1;
				pObj->motion = (24 + i * 6 + (6 - Min(pObj->attackFrame, 6)));
				break;
			case LEFT_SIDE_DOWN:
				i = 3;
				pObj->motion = (PO_C33_A_LD_0 + (6 - Min(pObj->attackFrame, 6)));
				break;
			case RIGHT_SIDE_DOWN:
				i = 5;
				pObj->motion = (PO_C33_A_RD_0 + (6 - Min(pObj->attackFrame, 6)));
				break;
			case LEFT_SIDE_UP:
				i = 2;
				pObj->motion = (PO_C33_A_RU_0 + (6 - Min(pObj->attackFrame, 6)));
				break;
			case RIGHT_SIDE_UP:
				i = 4;
				pObj->motion = (PO_C33_A_LU_0 + (6 - Min(pObj->attackFrame, 6)));
				break;
			}

			if (pObj->status < LEFT_SIDE_DOWN)
				pObj->dirF = pObj->x > ao[NearPlayer(pObj)].x ? LEFT : RIGHT;
		}
		else {
			pObj->x += pObj->dx;
			pObj->y += pObj->dy;
			pObj->motion += pObj->frame % 4;
		}
	}
	else {
		switch (pObj->status) {
		default:
			i = 0;
			pObj->motion = (24 + i * 6 + (6 - Min(pObj->attackFrame, 6)));
			break;
		case ROOF_LEFT:
		case ROOF_RIGHT:
			i = 1;
			pObj->motion = (24 + i * 6 + (6 - Min(pObj->attackFrame, 6)));
			break;
		case LEFT_SIDE_DOWN:
			i = 3;
			pObj->motion = (PO_C33_A_LD_0 + (6 - Min(pObj->attackFrame, 6)));
			break;
		case RIGHT_SIDE_DOWN:
			i = 5;
			pObj->motion = (PO_C33_A_RD_0 + (6 - Min(pObj->attackFrame, 6)));
			break;
		case LEFT_SIDE_UP:
			i = 2;
			pObj->motion = (PO_C33_A_RU_0 + (6 - Min(pObj->attackFrame, 6)));
			break;
		case RIGHT_SIDE_UP:
			i = 4;
			pObj->motion = (PO_C33_A_LU_0 + (6 - Min(pObj->attackFrame, 6)));
			break;
		}

		if (pObj->status < LEFT_SIDE_DOWN)
			pObj->dirF = pObj->x > ao[NearPlayer(pObj)].x ? LEFT : RIGHT;

		// 모션에 맞춰 공격
		if (pObj->motion == PO_C33_A_D_2 || pObj->motion == PO_C33_A_U_2 || pObj->motion == PO_C33_A_LU_2 || pObj->motion == PO_C33_A_LD_2 || pObj->motion == PO_C33_A_RU_2) {
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_SLIMEBULLET);
					//ao[i].lv = 1;
					ao[i].jumpFrame = 1;
					ao[i].dirX = ao[NearPlayer(pObj)].x < pObj->x ? LEFT : RIGHT;
					InitMotion(&ao[i]);
					break;
				}
			}
		}

		pObj->attackFrame--;
	}

	InitMotion(pObj);
	pObj->frame++;
}

void StuckMove(OBJECT* pObj)
{
	int tile;

	GetTile(pObj);

	//공중인가 체크
	if (pObj->status < LEFT_SIDE_DOWN) {
		tile = (pObj->dirY == UP) ? pObj->tileY1 : pObj->tileY2;

		if (mapInfoArray[mapInfoOff + tile * rw + pObj->tileX2] < TILE_BLOCK && mapInfoArray[mapInfoOff + tile * rw + pObj->tileX1] < TILE_BLOCK) {
			pObj->dx = 0;
			pObj->dy = DIR(pObj->dirY) * _2X;
			pObj->dirX = 1 - pObj->dirX;

			if (pObj->status == RIGHT_WALK)
				pObj->status = LEFT_SIDE_DOWN;
			else
				pObj->status += LEFT_SIDE_DOWN;

			return;
		}
	}
	else {
		tile = (pObj->dirX == LEFT) ? pObj->tileX1 : pObj->tileX2;

		if (mapInfoArray[mapInfoOff + pObj->tileY1 * rw + tile] < TILE_BLOCK && mapInfoArray[mapInfoOff + pObj->tileY2 * rw + tile] < TILE_BLOCK) {
			pObj->dx = DIR(pObj->dirX) * _2X;
			pObj->dy = 0;
			pObj->dirY = 1 - pObj->dirY;
			pObj->status = (pObj->status == LEFT_SIDE_DOWN ? 6 : 7) - pObj->status;

			return;
		}
	}

	//벽인가 체크
	if (pObj->status < LEFT_SIDE_DOWN) {
		tile = (pObj->dirX == LEFT) ? pObj->tileX1 : pObj->tileX2;

		if (mapInfoArray[mapInfoOff + (pObj->tileY1 + 1 - pObj->dirY) * rw + tile] >= TILE_BLOCK || mapInfoArray[mapInfoOff + (pObj->tileY2 - pObj->dirY) * rw + tile] >= TILE_BLOCK) {
			pObj->dirY = 1 - pObj->dirY;
			pObj->dx = 0;
			pObj->dy = DIR(pObj->dirY) * _2X;

			if (pObj->status == ROOF_LEFT)
				pObj->status = LEFT_SIDE_DOWN;
			else
				pObj->status = 7 - pObj->status;

			return;
		}
	}
	else {
		tile = (pObj->dirY == UP) ? pObj->tileY1 : pObj->tileY2;

		if (mapInfoArray[mapInfoOff + tile * rw + pObj->tileX1 + 1 - pObj->dirX] >= TILE_BLOCK || mapInfoArray[mapInfoOff + tile * rw + pObj->tileX2 - pObj->dirX] >= TILE_BLOCK) {
			pObj->dirX = 1 - pObj->dirX;
			pObj->dx = DIR(pObj->dirX) * _2X;
			pObj->dy = 0;
			pObj->status -= (pObj->status == LEFT_SIDE_DOWN ? 3 : 4);

			return;
		}
	}

	if (pObj->status < 4) {
		pObj->dx = DIR(pObj->dirX) * _2X;
		pObj->dy = 0;
	}
	else {
		pObj->dx = 0;
		pObj->dy = DIR(pObj->dirY) * _2X;
	}

	//모션 강제지정
	pObj->motion = slimeMotion[pObj->status];

	if (pObj->status < LEFT_SIDE_DOWN)
		pObj->dirF = pObj->dx < 0 ? LEFT : RIGHT;
	else if (pObj->status < LEFT_SIDE_UP)
		pObj->dirF = pObj->dirX;
	else
		pObj->dirF = 1 - pObj->dirX;
	//화면 바깥을 나갈려고 하면 다시 내려보낸다.
	if (pObj->y <= 0) {
		pObj->status = pObj->x < rw * TSIZE / 2 ? LEFT_SIDE_DOWN : RIGHT_SIDE_DOWN;
		pObj->dx = 0;
		pObj->dirY = 1 - pObj->dirY;
		pObj->dy = DIR(pObj->dirY) * _2X;
		pObj->motion = slimeMotion[pObj->status];
	}
}

void StraightMove(OBJECT* pObj)
{
	if (pObj->type == ENEMY_SHIP
		|| pObj->type == ENEMY_SHIP_RED
		|| pObj->type == ENEMY_SHIP_BLUE
		|| pObj->type == ENEMY_SHIP_PURPLE
		|| pObj->type == ENEMY_SHIP_GREEN
		|| pObj->type == ENEMY_SHIP_GOLD
		|| pObj->type == ENEMY_SHIP_BLACK) {
		switch (pObj->status) {
		case 1:
			if (TileCrash(pObj)) {
				pObj->status = 2;
				pObj->frame = 0;
				pObj->dx = pObj->dy = 0;
				pObj->motion = pObj->attack = PO_C28_SHOTBRE0;
				return;
			}
			break;
		case 2:
			if (pObj->frame > 2) {
				memset(pObj, 0, sizeof(OBJECT));
				return;
			}

			pObj->motion = pObj->attack + 1 + pObj->frame % 3;
			break;
		}
	}

	if (pObj->drawHandler == LASERDRAW) {
		//pObj->apx = -(ao[ENEMY + 4].x - 35 * _2X + (35 * pObj->zoom) * _2X);
		pObj->apx = -(ao[pObj->mom].x + (float)(35 * _2X / 2) * pObj->zoom);

		//if (pObj->zoom == 1) {
		//	pObj->apy -= (float)(4 * _2X) * pObj->zoom;
		//	pObj->ay = (float)(8 * _2X) * pObj->zoom;
		//}
		//else {
		pObj->apy -= (float)(8 * _2X) * pObj->zoom * 2;
		pObj->ay = (float)(16 * _2X) * pObj->zoom * 2;
		//}

		//pObj->ax = ao[ENEMY + 4].x - 35 * _2X + (35 * pObj->zoom) * _2X;
		pObj->ax = ao[pObj->mom].x + (float)(35 * _2X / 2) * pObj->zoom;
	}

	pObj->frame++;
	pObj->x += pObj->dx;
	pObj->y += pObj->dy;

	switch (pObj->type) {
	case ENEMY_BAHAMUT:
	case ENEMY_BAHAMUT_RED:
	case ENEMY_BAHAMUT_BLUE:
	case ENEMY_BAHAMUT_PURPLE:
	case ENEMY_BAHAMUT_GREEN:
	case ENEMY_BAHAMUT_GOLD:
	case ENEMY_BAHAMUT_BLACK:
		if (pObj->frame > 10) {
			if (!isDemo)
				ao[pObj->mom].motion = PO_C43_HEAD_N0;
			memset(pObj, 0, sizeof(OBJECT));
			return;
		}
		(pObj->motion)++;
		InitMotion(pObj);
		break;
	case ENEMY_DRAGON2:
	case ENEMY_DRAGON2_RED:
	case ENEMY_DRAGON2_BLUE:
	case ENEMY_DRAGON2_PURPLE:
	case ENEMY_DRAGON2_GREEN:
	case ENEMY_DRAGON2_GOLD:
	case ENEMY_DRAGON2_BLACK:
		InitMotion(pObj);
		if (pObj->frame > 9) {
			memset(pObj, 0, sizeof(OBJECT));
			return;
		}

		if (pObj->frame % 2 == 0)
			(pObj->motion)++;
		break;
	case ENEMY_SPACE2:
	case ENEMY_SPACE2_RED:
	case ENEMY_SPACE2_BLUE:
	case ENEMY_SPACE2_PURPLE:
	case ENEMY_SPACE2_GREEN:
	case ENEMY_SPACE2_GOLD:
	case ENEMY_SPACE2_BLACK:
		if (pObj->motion == PO_C47_SHOT0) {
			if (TileCrash(pObj) || ObjCrash(&ao[NearPlayer(pObj)], pObj)) {
				pObj->frame = 0;
				pObj->motion = PO_C47_SHOT1;
				pObj->dx = pObj->dy = 0;
				InitMotion(pObj);
			}
		}
		else {
			if (pObj->frame > 16) {
				memset(pObj, 0, sizeof(OBJECT));
				return;
			}

			(pObj->motion)++;
			InitMotion(pObj);

			if (pObj->motion == PO_C47_SHOT4)
				pObj->motion = PO_C47_SHOT1;
		}
		break;
	case ENEMY_CASTLE_BOSS1:
	case ENEMY_CASTLE_BOSS1_RED:
	case ENEMY_CASTLE_BOSS1_BLUE:
	case ENEMY_CASTLE_BOSS1_PURPLE:
	case ENEMY_CASTLE_BOSS1_GREEN:
	case ENEMY_CASTLE_BOSS1_GOLD:
	case ENEMY_CASTLE_BOSS1_BLACK:
		if (pObj->motion >= PO_C48_BOMB0) {
			(pObj->motion)++;
			// 폭탄의 움직임(천천히 따라다님)
			if (pObj->motion <= PO_C48_BOMB10) {
				GotoObj(&ao[NearPlayer(pObj)], pObj, Max(SPEED_MIN, 2 * _2X * pObj->zoom));

				if (pObj->motion == PO_C48_BOMB10)
					pObj->motion = PO_C48_BOMB0;

				if (ObjCrash(pObj, &ao[NearPlayer(pObj)]))
					pObj->motion = PO_C48_BOMB11;
			}

			if (pObj->motion == PO_C48_BOMB14) {
				ao[pObj->mom].tileY1 = 0;
				memset(pObj, 0, sizeof(OBJECT));
				return;
			}
		}
		else
			pObj->motion = pObj->frame / 2 % 2 == 0 ? PO_C48_SHOT0 : PO_C48_SHOT1;

		if (pObj->x < 0 || pObj->y < 0 || pObj->x > rw * TSIZE || pObj->y >(rh - 4) * TSIZE)
			memset(pObj, 0, sizeof(OBJECT));

		InitMotion(pObj);
		break;
	case ENEMY_CASTLE_BOSS3:
	case ENEMY_CASTLE_BOSS3_RED:
	case ENEMY_CASTLE_BOSS3_BLUE:
	case ENEMY_CASTLE_BOSS3_PURPLE:
	case ENEMY_CASTLE_BOSS3_GREEN:
	case ENEMY_CASTLE_BOSS3_GOLD:
	case ENEMY_CASTLE_BOSS3_BLACK:
		(pObj->motion)++;
		InitMotion(pObj);

		if (pObj->frame > 10) {
			memset(pObj, 0, sizeof(OBJECT));
			return;
		}
		break;
	}

	if (BoundaryCheck(pObj) && pObj->drawHandler != LASERDRAW &&
		(pObj->type != ENEMY_CASTLE_BOSS1
			&& pObj->type != ENEMY_CASTLE_BOSS1_RED
			&& pObj->type != ENEMY_CASTLE_BOSS1_BLUE
			&& pObj->type != ENEMY_CASTLE_BOSS1_PURPLE
			&& pObj->type != ENEMY_CASTLE_BOSS1_GREEN
			&& pObj->type != ENEMY_CASTLE_BOSS1_GOLD
			&& pObj->type != ENEMY_CASTLE_BOSS1_BLACK)) {
		if (pObj->type == ENEMY_FOGRA
			|| pObj->type == ENEMY_FOGRA_RED
			|| pObj->type == ENEMY_FOGRA_BLUE
			|| pObj->type == ENEMY_FOGRA_PURPLE
			|| pObj->type == ENEMY_FOGRA_GREEN
			|| pObj->type == ENEMY_FOGRA_GOLD
			|| pObj->type == ENEMY_FOGRA_BLACK) {
			if (pObj->frame > 12)
				memset(pObj, 0, sizeof(OBJECT));
		}
		else
			memset(pObj, 0, sizeof(OBJECT));
	}
}

void MachineManagerMove(OBJECT* pObj)
{
	int i, j = GetObjFromPtr(pObj) - 4, speed = 8 * _2X, etc = 0;
	int obj = GetObjFromPtr(pObj);
	int startObj;
	int endObj;

	if (obj < PLAYERALL) {
		startObj = BULLET;
		endObj = ENEMYUSEROBJ;
	}
	else {
		startObj = ENEMY;
		endObj = NEUTRAL;
	}

	if (pObj->dead == true) {
		memset(pObj, 0, sizeof(OBJECT));
		return;
	}

	if (isDemo && pObj->etc == 0) {
		for (i = 0; i < 4; i++) {
			ao[j + i].etc = 0;

			if (i > 1)
				ao[j + i].motion = PO_C25_LD_N0;
		}

		return;
	}

	if (pObj->frame == 0) {
		for (i = 0; i < 4; i++) {
			ao[j + i].mainFrame = pObj->etc == MACHINE_NEUTRAL ? 5 : 4;

			if (pObj->etc == MACHINE_NEUTRAL) {
				ao[j + i].attack = i >= 2 ? PO_C25_LD_N0 : PO_C25_LU_N0;//기준모션
				pObj->attackFrame = 22;		//스킬 쿨타임 지정
			}
			else {
				ao[j + i].attack = i >= 2 ? PO_C25_LD_READY0 : PO_C25_LU_READY0;
				pObj->attackFrame = pObj->etc >= MACHINE_LASER_SIDE ? 20 : 12;
			}
		}
	}
	else if (pObj->frame >= pObj->attackFrame) {
		pObj->frame = 0;

		if (pObj->etc == MACHINE_NEUTRAL) {
			int temp;

			etc = Random(100);

			if (etc < 60)
				temp = 0;
			else
				temp = etc > 80 ? 1 : 2;

			pObj->etc = 1 + temp;
		}
		else
			pObj->etc = MACHINE_NEUTRAL;

		for (i = 0; i < 4; i++) {
			ao[j + i].frame = 0;
			ao[j + i].etc = pObj->etc;
		}

		if (pObj->etc == MACHINE_LASER_CENTER) {
			int num = GetObjFromPtr(pObj);

			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false && ao[i].type == 0) {
					AddObject(&ao[i], pObj, ADDOBJ_MACHINELASERLINE);
					ao[i].attack = ao[i].motion = PO_C25_DIAGONAL2;
					ao[i].x = ao[num - 2].x + (ao[num - 1].x - ao[num - 2].x) / 2 + 5 * _2X;
					ao[i].y = ao[num - 3].y + (ao[num - 1].y - ao[num - 3].y) / 2 - 5 * _2X;
					ao[i].hp = pObj->hp;
					InitMotion(&ao[i]);
					break;
				}
			}
		}

		//특수 설정 - 보스몬스터 생성
		return;
	}

	if (pObj->etc == MACHINE_APPEAR && pObj->frame == 11) {
		//어디에서, 어느방향으로,
		for (i = startObj; i < endObj; i++) {
			if (ao[i].active == false && ao[i].type == 0) {
				AddObject(&ao[i], pObj, ADDOBJ_MACHINEBOSS);
				ao[i].status = Random(8);
				ao[i].mainFrame = 4;
				ao[i].lv = pObj->lv;
				ao[i].maxhp = pObj->maxhp;
				ao[i].hp = pObj->hp;

				if (ao[i].status <= ROOF_RIGHT) {
					ao[i].attack = PO_C25_APPEAR_L0;
					ao[i].x = ao[j + (3 - ao[i].status)].x;
					ao[i].y = ao[j + (3 - ao[i].status)].y;
					ao[i].attackFrame = PO_C25_A0_L;
					ao[i].jumpFrame = PO_C25_DASH_L;
					ao[i].dirF = ao[i].dirX = ao[i].status % 2 == 0 ? LEFT : RIGHT;
					ao[i].dx = DIR(ao[i].dirX) * speed;
				}
				else {
					ao[i].attack = ao[i].status <= RIGHT_SIDE_DOWN ? PO_C25_APPEAR_D0 : PO_C25_APPEAR_U0;
					ao[i].x = ao[j + ao[i].status - 4].x;
					ao[i].y = ao[j + ao[i].status - 4].y;
					ao[i].attackFrame = ao[i].status <= RIGHT_SIDE_DOWN ? PO_C25_A0_D : PO_C25_A0_U;
					ao[i].jumpFrame = ao[i].status <= RIGHT_SIDE_DOWN ? PO_C25_DASH_D : PO_C25_DASH_U;
					ao[i].dirF = ao[i].dirX = (ao[i].status == RIGHT_SIDE_DOWN || ao[i].status == LEFT_SIDE_UP) ? RIGHT : LEFT;
					ao[i].dy = ao[i].status <= RIGHT_SIDE_DOWN ? speed : -speed;
				}

				ao[i].motion = ao[i].attack;
				break;
			}
		}
	}
	pObj->frame++;
}

void MachineMove(OBJECT* pObj)
{
	int i, num = GetObjFromPtr(pObj);
	int obj = GetObjFromPtr(pObj);
	int startObj;
	int endObj;

	if (obj < PLAYERALL) {
		startObj = BULLET;
		endObj = ENEMYUSEROBJ;
	}
	else {
		startObj = ENEMY;
		endObj = NEUTRAL;
	}

	if (pObj->frame == 0) {
		pObj->dirF = pObj->dirX = num % 2 == 0 ? RIGHT : LEFT;
		pObj->frame++;
		return;
	}

	if (pObj->frame == 1 && pObj->etc == MACHINE_LASER_SIDE) {
		for (i = startObj; i < endObj; i++) {
			if (ao[i].active == false && ao[i].type == 0) {
				AddObject(&ao[i], pObj, ADDOBJ_MACHINELASERLINE);
				ao[i].attack = ao[i].motion = (num == ENEMY + 1 || num == ENEMY + 2) ? PO_C25_HEIGHT2 : PO_C25_WIDTH2;

				switch (num) {
				case ENEMY:
					ao[i].x += (ao[num + 1].x - ao[num].x) / 2;
					ao[i].y += 12 * _2X;
					break;
				case ENEMY + 1:
					ao[i].x -= 20 * _2X;
					ao[i].y += (ao[num + 1].y - ao[num].y) / 2;
					break;
				case ENEMY + 2:
					ao[i].x += 20 * _2X;
					ao[i].y -= (ao[num].y - ao[num - 1].y) / 2;
					break;
				case ENEMY + 3:
					ao[i].x -= (ao[num].x - ao[num - 1].x) / 2;
					ao[i].y -= 14 * _2X;
					break;
				}
				break;
			}
		}
	}

	pObj->motion = pObj->attack + pObj->frame % pObj->mainFrame;
	InitMotion(pObj);
	pObj->frame++;
}

void MachineBossMove(OBJECT* pObj)
{
	int i;
	int obj = GetObjFromPtr(pObj);
	int startObj;
	int endObj;

	if (obj < PLAYERALL) {
		startObj = BULLET;
		endObj = ENEMYUSEROBJ;
	}
	else {
		startObj = ENEMY;
		endObj = NEUTRAL;
	}

	if (isDemo && pObj->frame >= 4)
		return;

	switch (pObj->etc) {
	case 0:
		//처음등장해서 행동 정하기
		if (pObj->frame < 4)
			pObj->motion = pObj->attack + pObj->frame % 4;
		else {
			if (pObj->status <= ROOF_RIGHT) {
				pObj->motion = pObj->attack = PO_C25_W0_L;
				pObj->x += DIR(pObj->dirX) * 60 * _2X;
			}
			else {
				pObj->motion = pObj->attack = pObj->status <= RIGHT_SIDE_DOWN ? PO_C25_W0_D : PO_C25_W0_U;
				pObj->y += pObj->status <= RIGHT_SIDE_DOWN ? 60 * _2X : -60 * _2X;
			}

			pObj->etc = 1 + Random(2);
		}
		break;
	case 1:
		//이후 계속 이동
		pObj->motion = pObj->attack;
		pObj->x += pObj->dx;
		pObj->y += pObj->dy;

		if (pObj->frame >= (pObj->status < LEFT_SIDE_DOWN ? 28 : 26)) {
			if (pObj->status <= ROOF_RIGHT) {
				pObj->motion = pObj->attack = PO_C25_DIS_L0;
				pObj->x += DIR(pObj->dirX) * 22 * _2X;
			}
			else {
				pObj->motion = pObj->attack = pObj->status <= RIGHT_SIDE_DOWN ? PO_C25_DIS_D0 : PO_C25_DIS_U0;
				pObj->y += pObj->status <= RIGHT_SIDE_DOWN ? 22 * _2X : -22 * _2X;
			}

			pObj->frame = 0;
			pObj->etc = 3;
		}

		//미사일쏠경우, 일정프레임 가서 정지후 모션 ㄱㄱ
		if (pObj->frame >= 8 && pObj->frame <= 14) {
			pObj->x -= pObj->dx;
			pObj->y -= pObj->dy;
			pObj->motion = pObj->attackFrame + pObj->frame % 8;

			if (pObj->frame == 13) {
				int count = 0;

				for (i = startObj; i < endObj; i++) {
					if (ao[i].active == false && ao[i].type == 0) {
						AddObject(&ao[i], pObj, ADDOBJ_BOSSSHOT);
						ao[i].etc = count - 1;
						ao[i].status = pObj->status;

						if (pObj->status <= ROOF_RIGHT) {
							ao[i].x += DIR(ao[i].dirX) * 28 * _2X;
							ao[i].y += pObj->status >= ROOF_LEFT ? 10 * _2X : 4 * _2X;
						}
						else {
							ao[i].x += ao[i].status <= RIGHT_SIDE_DOWN ? -20 * DIR(ao[i].dirX) * _2X : 0 * _2X;
							ao[i].y += ao[i].status <= RIGHT_SIDE_DOWN ? 70 * _2X : -28 * _2X;
						}

						count++;

						if (count > 2)
							break;
					}
				}
			}
		}
		break;
	case 2:
		// 대쉬모드 공격
		if (pObj->frame >= (pObj->status < LEFT_SIDE_DOWN ? 17 : 16)) {
			if (pObj->status <= ROOF_RIGHT) {
				pObj->motion = pObj->attack = PO_C25_DIS_L0;
				pObj->x += DIR(pObj->dirX) * 22 * _2X;
			}
			else {
				pObj->motion = pObj->attack = pObj->status <= RIGHT_SIDE_DOWN ? PO_C25_DIS_D0 : PO_C25_DIS_U0;
				pObj->y += pObj->status <= RIGHT_SIDE_DOWN ? 22 * _2X : -22 * _2X;
			}

			pObj->frame = 0;
			pObj->etc = 3;
		}
		else if (pObj->frame > 10) {
			pObj->motion = pObj->jumpFrame;

			if (pObj->status <= ROOF_RIGHT)
				pObj->dx += DIR(pObj->dirX) * _2X;
			else
				pObj->dy += pObj->status <= RIGHT_SIDE_DOWN ? 1 * _2X : -1 * _2X;

			if (pObj->dx == 0)
				pObj->y += pObj->dy * 2;
			else
				pObj->x += pObj->dx * 2;
		}
		break;
	case 3:
		pObj->motion = pObj->attack + pObj->frame % 4;

		if (pObj->frame == 3) {
			memset(pObj, 0, sizeof(OBJECT));
			curEnemy = null;
			return;
		}
		break;
	}

	for (i = GetObjFromPtr(pObj); i > ENEMY; i--) {
		if (ao[i].moveHandler == MACHINEMANAGERMOVE) {
			ao[i].hp = pObj->hp;

			if (pObj->dead == true) {
				ao[i].dead = true;
				ao[i].drawHandler = VANISHDRAW;
				ao[i].moveHandler = VANISHMOVE;
				ao[i].frame = 0;
				memset(ao[i].debuf, 0, sizeof(ao[i].debuf));
				return;
			}
			break;
		}
	}

	InitMotion(pObj);
	pObj->frame++;
}

void BahamutHeadMove(OBJECT* pObj)
{
	const signed short* tPtr;
	int ret;
	int i;
	int obj = GetObjFromPtr(pObj);
	int startObj;
	int endObj;

	if (obj < PLAYERALL) {
		startObj = BULLET;
		endObj = ENEMYUSEROBJ;
	}
	else {
		startObj = ENEMY;
		endObj = NEUTRAL;
	}

	// 모션 잡기
	tPtr = cmf_status_data[pObj->cmf][pObj->etc];

	ret = *tPtr;

	tPtr += (2 + (pObj->frame % ret));
	pObj->motion = *tPtr;

	switch (pObj->etc) {
	case BAHAMUT_HEAD_NEUTRAL:
		if (pObj->frame % 2 == 0) {
			// 머리는 값에 따라 움직이고,
			//x축 감속, 가속 타이밍
			if (Abs(pObj->dx) >= 4 * _2X * pObj->zoom)
				pObj->dirX = pObj->dirX == RIGHT ? LEFT : RIGHT;

			if (pObj->dirX == LEFT)
				pObj->dx += 1 * _2X * pObj->zoom;
			else
				pObj->dx -= 1 * _2X * pObj->zoom;

			//y축 가속, 감속 타이밍
			if (Abs(pObj->dy) >= 3 * _2X * pObj->zoom)
				pObj->dirY = pObj->dirY == UP ? DOWN : UP;

			if (pObj->dirY == UP)
				pObj->dy += 1 * _2X * pObj->zoom;
			else if (pObj->dirY == DOWN)
				pObj->dy -= 1 * _2X * pObj->zoom;

			pObj->x += pObj->dx;
			pObj->y += pObj->dy;
		}
		break;
	case BAHAMUT_HEAD_FIRE:
		if (pObj->frame < 3) {
			pObj->x += 2 * _2X * pObj->zoom;
			pObj->y += 2 * _2X * pObj->zoom;
			pObj->motion = PO_C43_HEAD_N0;
		}
		else if (pObj->frame < 14)
			pObj->motion = PO_C43_HEAD_N0;
		else if (pObj->frame < 20) {
			pObj->x -= 8 * _2X * pObj->zoom;
			pObj->y += 2 * _2X * pObj->zoom;
			pObj->motion = PO_C43_HEAD2;
		}
		else if (pObj->frame < 26) {
			pObj->x += 7 * _2X * pObj->zoom;
			pObj->y -= 3 * _2X * pObj->zoom;
		}
		//미사일 쏘기
		if (pObj->frame == 15) {
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_BAHAMUTFIRE);
					ao[i].mom = GetObjFromPtr(pObj);
					break;
				}
			}
		}
		break;
	case BAHAMUT_HEAD_BULLET:
		if (pObj->frame < 3) {
			pObj->x += 2 * _2X * pObj->zoom;
			pObj->y += 2 * _2X * pObj->zoom;
			pObj->motion = PO_C43_HEAD_N0;
		}
		else if (pObj->frame < 14)
			pObj->motion = PO_C43_HEAD_N0;
		else if (pObj->frame < 20) {
			pObj->x -= 8 * _2X * pObj->zoom;
			pObj->y += 2 * _2X * pObj->zoom;
		}
		else if (pObj->frame < 26) {
			pObj->x += 7 * _2X * pObj->zoom;
			pObj->y -= 3 * _2X * pObj->zoom;
			pObj->motion = PO_C43_HEAD_N0;
		}
		//미사일 쏘기
		if (pObj->frame == 20) {
			int cnt;
			for (i = startObj, cnt = 0; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_BAHAMUTBULLET);
					ao[i].status = cnt;
					ao[i].motion += cnt;
					cnt++;

					if (cnt > 3)
						break;
				}
			}
			pObj->motion = PO_C43_HEAD2;
		}
		break;
	case BAHAMUT_HEAD_ATTACK:
		if (pObj->frame < 3) {
			pObj->x += 2 * _2X * pObj->zoom;
			pObj->y += 2 * _2X * pObj->zoom;
			pObj->motion = PO_C43_HEAD_N0;
		}
		else if (pObj->frame < 20)
			pObj->motion = PO_C43_HEAD_N0;
		else if (pObj->frame < 26) {
			pObj->x -= 32 * _2X * pObj->zoom;
			pObj->y += 20 * _2X * pObj->zoom;
			pObj->motion = pObj->frame / 2 % 2 == 0 ? PO_C43_HEAD0 : PO_C43_HEAD1;
		}
		else {
			pObj->x += 6 * _2X * pObj->zoom;
			pObj->y -= 3 * _2X * pObj->zoom;
			pObj->motion = PO_C43_HEAD_N0;
		}
		break;
	}

	InitMotion(pObj);
	pObj->frame++;
}

void BahamutNeckMove(OBJECT* pObj)
{
	int i;
	int bodyIdx = ENEMY;
	for (i = ENEMY; i < NEUTRAL; i++) {
		if (ao[i].moveHandler == BAHAMUTBODYMOVE) {
			bodyIdx = i;
			break;
		}
	}

	pObj->x = ao[bodyIdx].x - 27 * _2X * pObj->zoom - (ao[bodyIdx].x - 27 * _2X * pObj->zoom - ao[bodyIdx + 4].x + 10 * _2X * pObj->zoom) * pObj->status / 4;
	pObj->y = ao[bodyIdx].y - 33 * _2X * pObj->zoom - (ao[bodyIdx].y - 33 * _2X * pObj->zoom - ao[bodyIdx + 4].y) * pObj->status / 4;

	switch (pObj->status) {
	case 1:
		break;
	case 2:
		pObj->x += 20 * _2X * pObj->zoom;
		pObj->y -= 3 * _2X * pObj->zoom;
		break;
	case 3:
		pObj->x += 30 * _2X * pObj->zoom;
		pObj->y -= 10 * _2X * pObj->zoom;
		break;
	}
}

void BahamutBodyMove(OBJECT* pObj)
{
	const signed short* tPtr;
	int ret;
	int VERTICALPOS = 186 * _2X;

	// 모션 잡기
	tPtr = cmf_status_data[pObj->cmf][pObj->etc];

	ret = *tPtr;

	tPtr += (2 + (pObj->frame % ret));
	pObj->motion = *tPtr;

	switch (pObj->etc) {
	case BAHAMUT_NEUTRAL:
		if (pObj->frame > 30 && ao[pObj->mom].y >= VERTICALPOS && ao[pObj->mom].y <= VERTICALPOS + 2 * _2X) {
			int action = Random(3);

			pObj->frame = 0;
			ao[pObj->mom].y = VERTICALPOS;
			ao[pObj->mom].frame = 0;
			ao[pObj->mom].dx = 0;
			ao[pObj->mom].dy = 0;

			//공격패턴 정하기
			pObj->etc = BAHAMUT_FIRE + action;
			ao[pObj->mom].etc = BAHAMUT_HEAD_FIRE + action;
		}
		break;
	case BAHAMUT_FIRE:
	case BAHAMUT_BULLET:
	case BAHAMUT_ATTACK:
		if (pObj->frame > (pObj->etc == BAHAMUT_ATTACK ? 56 : 30)) {
			ao[pObj->mom].y = VERTICALPOS;// TSIZE * 3;
			ao[pObj->mom].etc = BAHAMUT_HEAD_NEUTRAL;
			ao[pObj->mom].frame = 0;
			pObj->frame = 0;
			pObj->etc = BAHAMUT_NEUTRAL;
		}

		break;
	}

	InitMotion(pObj);
	pObj->frame++;
}

int BahamutReady(OBJECT* pObj)
{
	int cnt, i;
	int obj = GetObjFromPtr(pObj);
	//status : 몇번째 목인가 판단
	//pObj->moveHandler = ENEMYMOVETURN;
	pObj->moveHandler = BAHAMUTBODYMOVE;
	pObj->etc = BAHAMUT_NEUTRAL;
	pObj->frame = 0;

	for (i = obj + 1, cnt = 0; i < NEUTRAL; i++) {
		memcpy(&ao[i], pObj, sizeof(OBJECT));
		ao[i].x = pObj->x - (float)(cnt == 3 ? 45 : (11 + 14 / (cnt + 1))) * _2X * pObj->zoom;
		ao[i].y = pObj->y - (float)(cnt == 3 ? 98 : 45 + 15 * cnt) * _2X * pObj->zoom;
		ao[i].etc = cnt == 3 ? BAHAMUT_HEAD_NEUTRAL : BAHAMUT_NECK;
		ao[i].motion = cnt == 3 ? PO_C43_HEAD_N0 : PO_C43_NECK_N0;
		ao[i].moveHandler = cnt == 3 ? BAHAMUTHEADMOVE : BAHAMUTNECKMOVE;
		if (cnt != 3)
			ao[i].maxhp = 0;
		ao[i].mom = i + 1;
		ao[i].status = cnt + 1;
		InitMotion(&ao[i]);
		cnt++;
		if (cnt == 4) {
			pObj->mom = i;
			break;
		}
	}

	pObj->maxhp = 0;

	InitMotion(pObj);
	return cnt;
}
void ShipMainMove(OBJECT* pObj)
{
	int pos = GetObjFromPtr(pObj);
	int i;
	int target = NearPlayer(pObj);

	//pObj->tileX1 <- 페이즈 나누는데 사용

	if (pObj->etc > SHIP_WEAK) {
		//에너지가 2/3 이하면 (1페이즈)
		if ((pObj->tileX1 == 0 && pObj->hp < pObj->maxhp * 2 / 3) || (pObj->tileX1 == 1 && pObj->hp < pObj->maxhp * 1 / 3)) {
			//if ((pObj->tileX1 == 0 && pObj->hp < pObj->maxhp * 1 / 3)) {
			pObj->etc = SHIP_CLOSEWEAK;
			pObj->frame = 0;
			pObj->tileX1++;
		}
	}

	if (isDemo) {
		pObj->frame = 1;

		if (pObj->etc == SHIP_MOVEIN && pObj->x > 250 * _2X)
			pObj->x -= 4;

		for (i = pos - 1; i >= pos - 4; i--) {
			ao[i].active = true;
			MoveObj(&ao[i]);
		}

		return;
	}

	if (pObj->frame == 0) {
		for (i = pos - 1; i >= pos - 4; i--) {
			if (ao[i].active && ao[i].etc != SHIP_CANNONBREAK)
				ao[i].frame = 0;
		}

		switch (pObj->etc) {
		case SHIP_NEUTRAL:
			pObj->dx = pObj->dy = 0;
			pObj->dirX = LEFT; pObj->dirY = UP;
			//pObj->y = (rh - 7) * TSIZE + (monXYGap[(pObj->type - TOTALPLAYER) * 2 + 1]) - Abs(frame % 32 - 16);
			pObj->etc = SHIP_MOVE;
			return;
		case SHIP_CANNONATTACK:
			for (i = pos - 4; i < pos; i++) {
				if (ao[i].motion == PO_C28_CA4_0 || ao[i].motion == PO_C28_CA3_0 || ao[i].motion == PO_C28_CA2_0 || ao[i].motion == PO_C28_CA1_0) {
					ao[i].etc = SHIP_CANNONATTACK;
					break;
				}
			}
			break;
		case SHIP_APPEARWEAK:
			pObj->attack = PO_C28_C0;
			break;
		case SHIP_LASER:
			pObj->attack = PO_C28_L0;
			break;
		case SHIP_GUIDESHOT:
			pObj->attack = PO_C28_M_BODY0;
			break;
		case SHIP_CLOSEWEAK:
			pObj->attack = PO_C28_N0;
			break;
		case SHIP_MOVEOUT:
			pObj->dx = -5;
			break;
			// 보기
		case SHIP_MOVEIN:
			pObj->attackFrame--;
			pObj->status = 4;
			pObj->x = 500 * _2X;
			pObj->y = 192 * _2X;

			for (i = pos - 1; i >= pos - 4; i--) {
				ao[i] = ao[pos];
				ao[i].motion = ao[i].attack = PO_C28_CA1_0 + 4 * (i - (pos - 4));
				ao[i].moveHandler = SHIPSUBMOVE;
#ifdef ARENAMONDATA
				ao[i].str = RoundDiv(monStr[pObj->lv - 1] * enemyStatInfo[pObj->type * 3 + 1], 100);
#else
				ao[i].str = pObj->lv + (pObj->lv / 5) * enemyStatInfo[pObj->type * 3 + 1] / 50;
#endif
				ao[i].def = ao[i].ps[PS_ARMOR] = enemyStatInfo[pObj->type * 3 + 2];
				ao[i].drawHandler = ENEMYDRAW;
				ao[i].hp = ao[i].maxhp = pObj->maxhp / 10;
				ao[i].dead = false;
				ao[i].frame = 0;
				ao[i].lv = pObj->lv;
				ao[i].mom = pos;
				MoveObj(&ao[i]);
			}

			pObj->dx = -10;
			break;
		default:
			pObj->attack = PO_C28_WEAK0;
			break;
		}
	}
	else {
		switch (pObj->etc) {
		case SHIP_MOVEOUT:
			if (pObj->x <= -70 * _2X) {
				pObj->frame = 0;
				pObj->etc = SHIP_MOVEIN;
				return;
			}

			pObj->dx -= 1;
			pObj->x += pObj->dx;
			break;
		case SHIP_MOVEIN:
			if (pObj->x <= 170 * _2X) {//BATTLEPOSITION_ENEMY_X - 2 * TSIZE) {
				pObj->dx = 0;
				pObj->frame = 0;
				pObj->etc = SHIP_NEUTRAL;
				return;
			}

			pObj->x -= 10;
			pObj->y = PLAYAREA_Y / 2 + 52 * _2X;
			break;
		case SHIP_CLOSEWEAK:
			if (pObj->frame > 4) {
				pObj->frame = 0;
				pObj->etc = SHIP_MOVEOUT;
				return;
			}

			pObj->motion = pObj->attack + (4 - pObj->frame);
			break;
		case SHIP_GUIDESHOT:
			pObj->attack = pObj->frame < 2 ? PO_C28_M_BODY0 : PO_C28_WEAK0;
			pObj->motion = pObj->attack + pObj->frame % (pObj->frame < 2 ? 2 : 4);

			if (pObj->frame > 50) {
				pObj->frame = 0;

				if (pObj->hp * 100 / pObj->maxhp < 35 * pObj->attackFrame) {
					pObj->etc = SHIP_CLOSEWEAK;
					return;
				}

				if (Random(30) > 15)
					pObj->etc = SHIP_WEAKMOVE;

				return;
			}
			else if (pObj->frame <= 31 && pObj->frame % 10 == 1) {
				for (i = pos + 1; i < NEUTRAL; i++) {
					if (ao[i].active == false) {
						AddObject(&ao[i], pObj, ADDOBJ_SHIPGUIDE);
						ao[i].attack = ao[i].motion;
						ao[i].dirY = DOWN;
						ao[i].dy = -4 * _2X;
						break;
					}
				}
			}
			break;
		case SHIP_LASER:
			if (pObj->frame > 34) {
				pObj->frame = 0;
				pObj->etc = SHIP_GUIDESHOT;
				return;
			}

			if (pObj->frame <= 11) {
				if (pObj->frame >= 4)
					pObj->motion = pObj->attack + 4;
				else
					pObj->motion = pObj->attack + pObj->frame % 7;
			}

			if (pObj->motion >= PO_C28_L3 && pObj->motion <= PO_C28_L5) {
				int count;
				int end = (pos < PLAYERALL ? PLAYERALL : NEUTRAL);
				for (i = pos + 1, count = 0; i < end; i++) {
					if (ao[i].active == false) {
						AddObject(&ao[i], pObj, ADDOBJ_SHIPLASER);
						ao[i].zoom = (float)(pObj->motion == PO_C28_L4 ? 2 : 1) * pObj->zoom;
						MoveObj(&ao[i]);
						count++;
						if (count > 5)
							break;
					}
				}
			}
			break;
		case SHIP_WEAKMOVE:
		{
			signed short distance;
			int yGap = 5 * _2X;
			if (Abs(pObj->y - ao[target].y - 52 * _2X) < yGap) {
				pObj->etc = SHIP_LASER;
				pObj->frame = 0;
				return;
			}

			pObj->motion = pObj->attack + pObj->frame % 4;
			distance = ao[target].y - pObj->y + 52 * _2X;

			if (Abs(distance) > yGap)
				pObj->dy = distance > 0 ? yGap : -yGap;

			pObj->y += pObj->dy;
		}
		break;
		case SHIP_WEAK:
			if (pObj->frame > 16) {
				pObj->frame = 0;
				pObj->etc = SHIP_WEAKMOVE;
				return;
			}

			pObj->motion = pObj->attack + pObj->frame % 4;
			break;
		case SHIP_APPEARWEAK:
			if (pObj->frame > 20) {
				pObj->frame = 0;
				pObj->etc = SHIP_WEAK;
				return;
			}
			else if (pObj->frame > 10)
				pObj->motion = pObj->attack + (pObj->frame % 11) / 2;
			break;
		case SHIP_MOVE:
			// x 축 변환
			if (Abs(pObj->dx) >= 10)
				pObj->dirX = pObj->dirX == RIGHT ? LEFT : RIGHT;

			if (pObj->dirX == LEFT)
				pObj->dx += 1;
			else if (pObj->dirX == RIGHT)
				pObj->dx -= 1;

			// y 축 변환
			if (Abs(pObj->dy) >= 5)
				pObj->dirY = pObj->dirY == UP ? DOWN : UP;

			if (pObj->dirY == UP)
				pObj->dy += 1;
			else if (pObj->dirY == DOWN)
				pObj->dy -= 1;

			pObj->x += pObj->dx;
			pObj->y += pObj->dy;

			if (Random(100) > 95) {
				pObj->etc = SHIP_CANNONATTACK;
				pObj->frame = 0;
				return;
			}
			break;
		}
	}

	InitMotion(pObj);
	pObj->frame++;
}

void ShipSubMove(OBJECT* pObj)
{
	int pos = GetObjFromPtr(pObj);
	int i, speed = 5;

	if (pos == pObj->mom - 4) {
		pObj->x = ao[pObj->mom].x - 58 * _2X;
		pObj->y = ao[pObj->mom].y - 20 * _2X;
		bar[BAR_ENEMYHP + GetEnemyBarIdx(pObj->mom) + 4].x = pObj->x - rx;
		bar[BAR_ENEMYHP + GetEnemyBarIdx(pObj->mom) + 4].y = STATUSWIN_Y + (rh - 4) * TSIZE - pObj->y;
	}
	else if (pos == pObj->mom - 3) {
		pObj->x = ao[pObj->mom].x - 39 * _2X;
		pObj->y = ao[pObj->mom].y - 12 * _2X;
		bar[BAR_ENEMYHP + GetEnemyBarIdx(pObj->mom) + 3].x = pObj->x - rx;
		bar[BAR_ENEMYHP + GetEnemyBarIdx(pObj->mom) + 3].y = STATUSWIN_Y + (rh - 4) * TSIZE - pObj->y;
	}
	else if (pos == pObj->mom - 2) {
		pObj->x = ao[pObj->mom].x - 1 * _2X;
		pObj->y = ao[pObj->mom].y + 10 * _2X;
		bar[BAR_ENEMYHP + GetEnemyBarIdx(pObj->mom) + 2].x = pObj->x - rx;
		bar[BAR_ENEMYHP + GetEnemyBarIdx(pObj->mom) + 2].y = STATUSWIN_Y + (rh - 4) * TSIZE - pObj->y;
	}
	else if (pos == pObj->mom - 1) {
		pObj->x = ao[pObj->mom].x + 50 * _2X;
		pObj->y = ao[pObj->mom].y - 21 * _2X;
		bar[BAR_ENEMYHP + GetEnemyBarIdx(pObj->mom) + 1].x = pObj->x - rx;
		bar[BAR_ENEMYHP + GetEnemyBarIdx(pObj->mom) + 1].y = STATUSWIN_Y + (rh - 4) * TSIZE - pObj->y;
	}

	switch (pObj->etc) {
	case SHIP_CANNONATTACK:
		pObj->motion = pObj->attack + pObj->frame;

		if (pObj->frame == 1) {
			for (i = pos; i < NEUTRAL; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_SHIPCANNONSHOT);
					ao[i].dx = pos == pObj->mom - 1 ? speed : -speed * (pObj->mom - 2 - pos) / 2;
					ao[i].dy = speed;
					break;
				}
			}
		}
		else if (pObj->frame == 3) {
			pObj->etc = SHIP_NEUTRAL;
			pObj->frame = 0;

			for (i = pos + 1; i < pObj->mom; i++) {
				if (ao[i].motion == PO_C28_CA4_0 || ao[i].motion == PO_C28_CA3_0 || ao[i].motion == PO_C28_CA2_0 || ao[i].motion == PO_C28_CA1_0) {
					ao[i].frame = 0;
					ao[i].etc = SHIP_CANNONATTACK;
					InitMotion(pObj);
					return;
				}
			}

			ao[pObj->mom].frame = 0;
			ao[pObj->mom].etc = SHIP_MOVE;
		}
		InitMotion(pObj);
		pObj->frame++;
		break;
	case SHIP_MOVE:
	case SHIP_NEUTRAL:
		pObj->frame = 0;
		pObj->motion = pObj->attack;
		break;
	case SHIP_CANNONBREAK:
		if (pObj->frame > 3) {
			pObj->active = false;
			pObj->drawHandler = null;
			return;
		}

		pObj->motion = pObj->attack + pObj->frame++;
		break;
	}

	InitMotion(pObj);
}

void DebrionBodyMove(OBJECT* pObj)
{
	const signed short* tPtr;
	int ret, i;
	int obj = GetObjFromPtr(pObj);
	int startObj;
	int endObj;

	if (obj < PLAYERALL) {
		startObj = BULLET;
		endObj = ENEMYUSEROBJ;
	}
	else {
		startObj = ENEMY;
		endObj = NEUTRAL;
	}

	// tileX1 : 어떤 파츠가 팔을 늘렸는지 저장하는 변수
	// tileY1 : 기뢰폭탄이 생성되었는가 저장하는 변수

	if (pObj->tileX2 == 0)
		pObj->etc = CASTLEBOSS1_BODY_BOMB;

	// 모션 잡기
	tPtr = cmf_status_data[pObj->cmf][pObj->etc];

	ret = *tPtr;

	tPtr += (2 + (pObj->frame % ret));
	pObj->motion = *tPtr;

	if (isDemo)
		return;

	switch (pObj->etc) {
	case CASTLEBOSS1_BODY_BOMB:
		//폭탄 하나 생성
		if (pObj->tileY1 == 0) {
			pObj->tileY1 = 1;
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_DEBRIONBOMB);
					break;
				}
			}
		}
		//폭탄 터지면 또 생성시킬수 있게 pObj->mom의 tileY1 을 0으로 만들어 준다
		break;
	case CASTLEBOSS1_BODY_MOVEWAIT:
	{
		int disX = ao[pObj->tileX1].x - pObj->x;
		int disY = ao[pObj->tileX1].y - pObj->y;

		if (pObj->frame >= 12) {
			pObj->x += disX > 0 ? Min(48 * _2X, disX) : Max(-48 * _2X, disX);
			pObj->y += disY > 0 ? Min(48 * _2X, disY) : Max(-48 * _2X, disY);
		}
		if (pObj->frame == 16) {
			pObj->frame = 0;
			pObj->etc = CASTLEBOSS1_BODY_NEUTRAL;
		}
	}
	break;
	case CASTLEBOSS1_BODY_BULLET:
		if (pObj->motion == PO_C48_BODY_A1) {
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_DEBRIONBULLET);
					GotoObj(&ao[NearPlayer(pObj)], &ao[i], 6 * _2X);
				}
			}
		}

		if (pObj->frame > 12) {
			pObj->frame = 0;
			pObj->etc = CASTLEBOSS1_BODY_NEUTRAL;
		}
		break;
	case CASTLEBOSS1_BODY_NEUTRAL:
		//플레이어가 접근하면 미사일 발사
		if (pObj->frame > 50 && GetDistance(&ao[NearPlayer(pObj)], pObj) < 50 * _2X * pObj->zoom) {
			pObj->etc = CASTLEBOSS1_BODY_BULLET;
			pObj->frame = 0;
		}
		//기본 움직임 넣기
		break;
	}

	InitMotion(pObj);
	pObj->frame++;

}

void DebrionArmMove(OBJECT* pObj)
{
	const signed short* tPtr;
	int ret, i, cnt = 0;
	// 모션 잡기
	// tileX1 : 어떤 파츠가 팔을 늘렸는지 저장하는 변수
	// 팔 다 터지면, mom의 etc를 body_bomb로 바꿔줄것.
	tPtr = cmf_status_data[pObj->cmf][pObj->etc];

	ret = *tPtr;

	tPtr += (2 + (pObj->frame % ret));
	pObj->motion = *tPtr;

	if (isDemo)
		return;

	switch (pObj->etc) {
	case CASTLEBOSS1_DARM_DIE:
	case CASTLEBOSS1_UARM_DIE:
		if (pObj->frame > 4) {
			ao[pObj->mom].tileX2--;
			pObj->active = false;
			return;
		}
		break;
	case CASTLEBOSS1_DARM_MOVE:
	case CASTLEBOSS1_UARM_MOVE:
		//살짝 움츠러 들었다가
		if (pObj->frame < 8) {
			pObj->x += pObj->dirX == RIGHT ? -2 * _2X * pObj->zoom : 2 * _2X * pObj->zoom;
			pObj->y += pObj->etc == CASTLEBOSS1_DARM_MOVE ? -2 * _2X * pObj->zoom : 2 * _2X * pObj->zoom;
		}
		else if (pObj->frame < 12) {
			// 전진하면서 타일과 부딧힐때까지 간다
			while (TileCrash(pObj) == false && cnt < 2) {
				//while (pObj->x > 4 * TSIZE && pObj->x < rw * TSIZE - 4 * TSIZE && pObj->y > 4 * TSIZE && pObj->y < PLAYAREA_Y - 4 * TSIZE && cnt < 2) {
				pObj->x += pObj->dirX == RIGHT ? TSIZE : -TSIZE;
				pObj->y += pObj->etc == CASTLEBOSS1_DARM_MOVE ? TSIZE : -TSIZE;
				cnt++;
			}
		}

		if (pObj->frame >= 15) {
			pObj->frame = 0;
			pObj->etc = pObj->etc == CASTLEBOSS1_DARM_MOVE ? CASTLEBOSS1_DARM_NEUTRAL : CASTLEBOSS1_UARM_NEUTRAL;
		}
		break;
	case CASTLEBOSS1_DARM_BULLET:
	case CASTLEBOSS1_UARM_BULLET:
		if (pObj->motion == PO_C48_ARM1_A1 || pObj->motion == PO_C48_ARM0_A1) {
			for (i = ENEMY, cnt = 1; cnt < 3; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_DEBRIONBULLET);
					ao[i].x += (pObj->dirX == RIGHT ? 27 : -27) * cnt * _2X;
					ao[i].y += (pObj->etc == CASTLEBOSS1_DARM_BULLET ? 27 : -27) * cnt * _2X;
					GotoObj(&ao[NearPlayer(pObj)], &ao[i], (8 - cnt) * _2X);
					cnt++;
				}
			}
		}

		if (pObj->frame > 40) {
			pObj->frame = 0;
			pObj->etc = pObj->etc == CASTLEBOSS1_DARM_BULLET ? CASTLEBOSS1_DARM_NEUTRAL : CASTLEBOSS1_UARM_NEUTRAL;
		}
	case CASTLEBOSS1_DARM_NEUTRAL:
	case CASTLEBOSS1_UARM_NEUTRAL:
		pObj->x = ao[pObj->mom].x;
		pObj->y = ao[pObj->mom].y;

		if (pObj->frame > 50 + Random(100)) {
			pObj->frame = 0;
			pObj->etc = pObj->etc == CASTLEBOSS1_DARM_NEUTRAL ? CASTLEBOSS1_DARM_BULLET : CASTLEBOSS1_UARM_BULLET;
		}
		else if (pObj->frame > 60 && ao[pObj->mom].etc != CASTLEBOSS1_BODY_MOVEWAIT && TileCrash(pObj) == false) {
			pObj->frame = 0;
			pObj->etc = pObj->etc == CASTLEBOSS1_DARM_NEUTRAL ? CASTLEBOSS1_DARM_MOVE : CASTLEBOSS1_UARM_MOVE;
			ao[pObj->mom].etc = CASTLEBOSS1_BODY_MOVEWAIT;
			ao[pObj->mom].frame = 0;
			ao[pObj->mom].tileX1 = GetObjFromPtr(pObj);
		}
		break;
	}

	InitMotion(pObj);
	pObj->frame++;
}

void ShipGuideMove(OBJECT* pObj)
{
	if (pObj->frame < 17) {
		//x축 감속, 가속 타이밍
		if (Abs(pObj->dx) >= 8)
			pObj->dirX = pObj->dirX == RIGHT ? LEFT : RIGHT;

		if (pObj->dirX == LEFT)
			pObj->dx++;
		else if (pObj->dirX == RIGHT)
			pObj->dx--;

		//방향전환 타이밍
		if (pObj->dx == 0)
			pObj->dirF = pObj->dirX == LEFT ? RIGHT : LEFT;

		//y축 가속, 감속 타이밍
		if (Abs(pObj->dy) >= 6)
			pObj->dirY = pObj->dirY == UP ? DOWN : UP;

		if (pObj->dirY == UP)
			pObj->dy++;
		else if (pObj->dirY == DOWN)
			pObj->dy--;
	}
	else if (pObj->frame < 30)
		GotoObj(&ao[NearPlayer(pObj)], pObj, 8);


	pObj->motion = pObj->attack + pObj->frame % 4;
	pObj->x += pObj->dx;
	pObj->y += pObj->dy;

	if (ObjCrash(&ao[pObj->target], pObj)) {
		AttackRobin(GetObjFromPtr(pObj), pObj->target);
		memset(pObj, 0, sizeof(OBJECT));
	}

	pObj->frame++;

	if (pObj->frame > 2 * FPS && BoundaryCheck(pObj))
		memset(pObj, 0, sizeof(OBJECT));
}

void FograMove(OBJECT* pObj)
{
	int x, y;
	int distance = ao[PLAYER].x - pObj->x;
	const signed short* tPtr;
	int ret, i;
	int speed = 4 * _2X;//미사일 스피드
	int obj = GetObjFromPtr(pObj);
	int startObj;
	int endObj;

	if (ao[raidPlayer].active == false)
		distance = 0;

	if (obj < PLAYERALL) {
		startObj = BULLET;
		endObj = ENEMYUSEROBJ;
		distance = ao[ao[PLAYER].target].x - pObj->x;
	}
	else {
		startObj = ENEMY;
		endObj = NEUTRAL;
	}
	// pObj->tileX1 : 미사일 순번
	// pObj->jumpFrame : 원으로 돌때 기준x좌표

	// 모션 잡기
	tPtr = cmf_status_data[pObj->cmf][pObj->etc];

	ret = *tPtr;

	tPtr += (2 + (pObj->frame % ret));
	pObj->motion = *tPtr;

	if (isDemo) {
		InitMotion(pObj);
		pObj->frame++;
		return;
	}

	if (pObj->etc == 0)
		pObj->etc = FOGRA_NEUTRAL;

	// stdx, stdy 선택
	switch (pObj->etc) {
	case FOGRA_NEUTRAL:
		x = ((BC_mathSin1024(pObj->mainFrame % 360) * 35) >> 10) * _2X;
		y = ((BC_mathCos1024(pObj->mainFrame % 360) * 35) >> 10) * _2X;
		pObj->x = pObj->jumpFrame * _2X + x;
		pObj->y = (float)240 * _2X + y;
		//pObj->y = pObj->ny + y;

		//pObj->x = pObj->nx;
		//pObj->y = pObj->ny;
		pObj->mainFrame += 5;

		if (pObj->mainFrame >= 360) {
			pObj->etc = FOGRA_BULLET;
			pObj->frame = 0;
			pObj->mainFrame = 0;
			//Random으로 미사일을 쏠지 레이져를 쏠지 결정
			pObj->etc = FOGRA_MOVE + Random(2);
		}
		break;
	case FOGRA_BULLET:
		if (pObj->motion % 3 == 1) {
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_FOGRABULLET);
					ao[i].dx = (pObj->tileX1 < 7 ? (pObj->tileX1 - 3) : (9 - pObj->tileX1)) * speed;
					ao[i].dy = (3 * speed - Abs(ao[i].dx)) * (pObj->tileX1 < 6 ? -1 : 1);
					ao[i].motion = PO_C40_SHOT0 + pObj->tileX1;
					InitMotion(&ao[i]);
					pObj->tileX1++;
					break;
				}
			}
		}

		if (pObj->frame >= 36) {
			pObj->etc = FOGRA_NEUTRAL;
			pObj->frame = 0;
			pObj->tileX1 = 0;
		}
		break;
	case FOGRA_MOVE:
		// etc 선택
		pObj->x += pObj->dx;
		pObj->jumpFrame += pObj->dx;

		if (Abs(distance) > 10 * _2X)
			pObj->dx = distance > 0 ? Min(distance, 8 * _2X) : Max(distance, -8 * _2X);
		else {
			pObj->frame = 0;
			pObj->etc = FOGRA_LASER;
		}
		break;
	case FOGRA_LASER:
		if (pObj->frame == 54) {
			pObj->etc = FOGRA_NEUTRAL;
			pObj->frame = 0;
			//pObj->dx = 0;
		}
		break;
		/*
	case FOGRA_RETURN:
		distance = pObj->nx - pObj->x;

		pObj->x += pObj->dx;
		pObj->jumpFrame += pObj->dx;

		if (Abs(distance) > 10 * _2X)
			pObj->dx = distance > 0 ? Min(distance, 8 * _2X) : Max(distance, -8 * _2X);
		else {
			pObj->frame = 0;
			pObj->etc = FOGRA_NEUTRAL;
		}
		break;
		*/
	}

	InitMotion(pObj);
	pObj->frame++;
}

//type정하기 : 빠른놈0 느린놈1//tileX1 : 미사일 카운트//tileY1 : 빠른놈 0:느린놈 1
//항상 ENEMY위치에 FOGRA가 있어야함
void FograSubMove(OBJECT* pObj, OBJECT* pMom)
{
	int x, y;
	const signed short* tPtr;
	int distanceX = ao[NearPlayer(pObj)].x - pObj->x;
	int distanceY = (ao[NearPlayer(pObj)].y - 12 * _2X) - pObj->y;
	int ret, i, t;
	int speed = 6 * _2X;
	int obj = GetObjFromPtr(pObj);
	int startObj;
	int endObj;

	if (obj < PLAYERALL) {
		startObj = BULLET;
		endObj = ENEMYUSEROBJ;
	}
	else {
		startObj = ENEMY;
		endObj = NEUTRAL;
	}
	// 모션 잡기
	tPtr = cmf_status_data[pObj->cmf][pObj->etc];

	ret = *tPtr;

	tPtr += (2 + (pObj->frame % ret));
	pObj->motion = *tPtr;

	x = (float)((BC_mathSin1024(pObj->mainFrame % 360) * 95) >> 10) * _2X * pObj->zoom;
	y = (float)((BC_mathCos1024(pObj->mainFrame % 360) * 95) >> 10) * _2X * pObj->zoom;
	pObj->x = pMom->x + x;
	pObj->y = pMom->y - pMom->cy + y;
	pObj->mainFrame += pObj->tileY1 == 0 ? 5 : 8;

	if (isDemo)
		return;

	switch (pObj->etc) {
	case FOGRA_SUBFOGRA:
		if (isDemo == false && pObj->mainFrame >= 720 && Random(100) > 95) {
			pObj->etc = FOGRA_SUBFOGRA_ATTACK;
			pObj->frame = 0;
			pObj->mainFrame %= 360;
		}
		break;
	case FOGRA_SUBFOGRA_ATTACK:
		if (pObj->motion == PO_C40_CIRCLE_A2) {
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_FOGRASUBBULLET);

					if (pObj->tileX1 == 0) {
						//tan값 구하기
						if (distanceX == 0)
							distanceX++;

						t = distanceY * 100 / distanceX * 100;

						//30도 이하일때
						if (t < 57 * 100) {
							if (distanceX > distanceY) {
								ao[i].motion = PO_C40_SHOT6_SMALL;
								if (distanceX < 0)
									ao[i].motion = PO_C40_SHOT12_SMALL;
							}
							else {
								ao[i].motion = PO_C40_SHOT3_SMALL;
								if (distanceY > 0)
									ao[i].motion = PO_C40_SHOT9_SMALL;
							}
						}
						//60도 이하일때
						else if (t < 173 * 100) {
							ao[i].motion = PO_C40_SHOT5_SMALL;
							if (distanceX < 0) {
								ao[i].motion -= 4;
								if (distanceY > 0)
									ao[i].motion += 10;
							}
							if (distanceY > 0)
								ao[i].motion += 2;
						}
						else {
							ao[i].motion = PO_C40_SHOT4_SMALL;
							if (distanceX < 0)
								ao[i].motion -= 2;
							if (distanceY > 0)
								ao[i].motion += 4;
						}
					}
					else
						ao[i].motion = ao[i - pObj->tileX1].motion + (pObj->tileX1 % 2 == 1 ? -1 : 1);

					ao[i].dx = ((ao[i].motion - PO_C40_SHOT0_SMALL) < 7 ? ((ao[i].motion - PO_C40_SHOT0_SMALL) - 3) : (9 - (ao[i].motion - PO_C40_SHOT0_SMALL))) * speed;
					ao[i].dy = (3 * speed - Abs(ao[i].dx)) * ((ao[i].motion - PO_C40_SHOT0_SMALL) < 6 ? -1 : 1);

					InitMotion(&ao[i]);
					pObj->tileX1++;

					if (pObj->tileX1 == 3)
						break;
				}
			}
		}

		if (pObj->frame >= 5) {
			pObj->etc = FOGRA_SUBFOGRA;
			pObj->frame = 0;
			pObj->tileX1 = 0;
		}
		break;
	}

	InitMotion(pObj);
	pObj->frame++;
}

void SignMove(OBJECT* pObj)
{
	const signed short* tPtr;
	int distanceX = Abs(ao[pObj->target].x - pObj->x);
	int distanceY = Abs((ao[pObj->target].y - 12 * _2X) - pObj->y);
	int ret;
	int obj = GetObjFromPtr(pObj);
	int startObj;
	int endObj;

	if (obj < PLAYERALL) {
		startObj = BULLET;
		endObj = ENEMYUSEROBJ;
	}
	else {
		startObj = ENEMY;
		endObj = NEUTRAL;
	}

	//몬스터 스피드 조절
	pObj->dx = 4 * DIR(pObj->dirX) * _2X;

	switch (pObj->etc) {
	case CASTLE1_NEUTRAL:
		if (pObj->frame > 12) {
			pObj->frame = 0;

			if (distanceX < 6 * TSIZE && distanceY < 5 * TSIZE) {
				//20%확률로 워프공격
				pObj->etc = Random(100) >= 80 ? CASTLE1_DISAPPEAR : CASTLE1_ATTACK;
			}
			else
				pObj->etc = CASTLE1_MOVE;
		}
		break;
	case CASTLE1_MOVE:
		//y축 가속, 감속 타이밍
		if ((pObj->dirY == UP && pObj->dy > 4 * _2X) || (pObj->dirY == DOWN && pObj->dy < -4 * _2X))
			pObj->dirY = 1 - pObj->dirY;

		if (pObj->dirY == UP)
			pObj->dy += 1 * _2X;
		else if (pObj->dirY == DOWN)
			pObj->dy -= 1 * _2X;

		pObj->x += pObj->dx;
		pObj->y += pObj->dy;
		if (distanceX < 6 * TSIZE && distanceY < 5 * TSIZE) {
			pObj->frame = 0;
			//20%확률로 워프공격
			pObj->etc = Random(100) >= 80 ? CASTLE1_DISAPPEAR : CASTLE1_ATTACK;
		}
		else {
			if ((pObj->dirX == RIGHT && pObj->x > rw * TSIZE - 50 * _2X) ||
				(pObj->dirX == LEFT && pObj->x < 10 * _2X))
				pObj->dirX = pObj->dirF = 1 - pObj->dirX;
		}
		break;
	case CASTLE1_DISAPPEAR:
		if (pObj->motion == PO_C44_WARP6) {
			pObj->x = Max(10 * _2X, ao[NearPlayer(pObj)].x - 50 * DIR(ao[NearPlayer(pObj)].dirF) * _2X);
			pObj->y = ao[NearPlayer(pObj)].y;
			pObj->dirF = pObj->dirX = ao[NearPlayer(pObj)].x - pObj->x < 0 ? LEFT : RIGHT;
			pObj->etc = CASTLE1_APPEAR;
			pObj->frame = 0;
		}
		break;
	case CASTLE1_APPEAR:
		if (pObj->motion == PO_C44_N1) {
			pObj->frame = 0;
			pObj->etc = CASTLE1_ATTACK;
		}
		break;
	case CASTLE1_ATTACK:
		pObj->dirX = pObj->dirF = ao[NearPlayer(pObj)].x < pObj->x ? LEFT : RIGHT;

		if (pObj->motion == PO_C44_A2) {
			int i;

			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_CASTLE1BULLET);
					break;
				}
			}
		}
		else if (pObj->motion == PO_C44_N0) {
			pObj->frame = 0;
			pObj->etc = CASTLE1_NEUTRAL;
		}
		break;
	}

	// 모션 잡기
	tPtr = cmf_status_data[pObj->cmf][pObj->etc];

	ret = *tPtr;

	tPtr += (2 + (pObj->frame % ret));
	pObj->motion = *tPtr;

	InitMotion(pObj);
	pObj->frame++;
}


void GuardMove(OBJECT* pObj)
{
	const signed short* tPtr;
	int ret;
	int obj = GetObjFromPtr(pObj);
	int i, damage;

	//멧돼지 행턴 정의
	//1차 멧돼지
	if (pObj->mx == 0)
		pObj->mx = 8 + Random(10);//(movie.index == DEMO_QUEST47 ? 35 : 15) + Random(20);

	if (pObj->frame >= pObj->mx && pObj->mainFrame < 10) {
		for (i = ENEMY; i < NEUTRAL; i++) {
			if (!ao[i].active &&
				(ao[i].type == ENEMY_BOAR
					|| ao[i].type == ENEMY_BOAR_RED
					|| ao[i].type == ENEMY_BOAR_BLUE
					|| ao[i].type == ENEMY_BOAR_PURPLE
					|| ao[i].type == ENEMY_BOAR_GREEN
					|| ao[i].type == ENEMY_BOAR_GOLD
					|| ao[i].type == ENEMY_BOAR_BLACK)
				&& ao[i].drawHandler == REGENDRAW) {
				//이벤트 멧돼지 생성 -> 벨런스 조절 추후 필요.
				ao[i].active = true;
				ao[i].dead = false;
				ao[i].x = 400 * _2X;
				ao[i].y = 272 * _2X;
				ao[i].lv = 17 + Random(2);
				ao[i].hp = ao[i].maxhp = 100;
				ao[i].dirF = ao[i].dirX = LEFT;
				ao[i].maxhp = ao[i].hp = 2 * (50 + ao[i].lv * ao[i].lv * 2) / 3;
				ao[i].moveHandler = BOAREVENTMOVE;
				ao[i].drawHandler = ENEMYDRAW;
				ao[i].frame = 0;
				ao[i].etc = 6;

				pObj->frame = 0;
				pObj->mainFrame++;
				break;
			}
		}
	}

	//npc 공격 버전
	for (i = ENEMY; i < NEUTRAL; i++) {
		if (i != obj && ao[i].active && pObj->etc == 0 && GetDistance(&ao[i], pObj) <= 40) {
			pObj->etc = 2;	//공격 etc로 만들어준다
			break;
		}
	}

	if (i == NEUTRAL)
		pObj->etc = 0;

	tPtr = cmf_status_data[pObj->cmf][pObj->etc];

	if (*tPtr == 0) {
		EnemyMoveCommon(pObj);
		return;
	}

	ret = *tPtr;

	//Motion
	tPtr += (2 + (pObj->frame % ret));
	pObj->motion = *tPtr;

	//DX
	tPtr += ret;
	pObj->dx = *tPtr * DIR(pObj->dirX);

	//DY
	tPtr += ret;
	pObj->dy = *tPtr;

	//갈란드의 공격 체크
	AttackEnemyCheck(obj);

	//갈란드 데미지 받았는지 체크
	for (i = ENEMY; i < NEUTRAL; i++) {
		if (i != obj && ao[i].active && pObj->attacked == false && AttackCrash(&ao[i], pObj)) {
			pObj->attacked = true;
			pObj->attackedFrame = ATTACKEDFRAME;
#ifdef ATTACKEDINVINCIBLE
			pObj->invincible = ATTACKEDFRAME;
#endif
			damage = 50 + Random(20);
			pObj->hp -= damage;
			SetDmgNum(i, obj, damage, 1, attackType, DMGNUMZOOM);

		}
	}

	EnemyMoveCommon(pObj);
}

void GoliMove(OBJECT* pObj)
{
	int obj = GetObjFromPtr(pObj);
	int i;

	//골리 데미지 받았는지 체크
	for (i = ENEMY; i < NEUTRAL; i++) {
		if (i != obj && ao[i].active && pObj->attacked == false && AttackCrash(&ao[i], pObj)) {
			pObj->attacked = true;
			pObj->attackedFrame = ATTACKEDFRAME;
#ifdef ATTACKEDINVINCIBLE
			pObj->invincible = ATTACKEDFRAME;
#endif
			pObj->hp -= 20;
		}
	}

	//다음 데모신으로
	for (i = ENEMY; i < NEUTRAL; i++) {
		if (ao[i].active &&
			(ao[i].type == ENEMY_SLING
				|| ao[i].type == ENEMY_SLING_RED
				|| ao[i].type == ENEMY_SLING_BLUE
				|| ao[i].type == ENEMY_SLING_PURPLE
				|| ao[i].type == ENEMY_SLING_GREEN
				|| ao[i].type == ENEMY_SLING_GOLD
				|| ao[i].type == ENEMY_SLING_BLACK))
			break;
	}

	if (i == NEUTRAL) {
		memset(ao[PLAYER].debuf, 0, sizeof(ao[PLAYER].debuf));
		pObj->hp = pObj->maxhp;
	}
}

void GuardMove2(OBJECT* pObj)
{
	const signed short* tPtr;
	int ret;
	int obj = GetObjFromPtr(pObj);
	int i;

	if (isDemo)
		return;

	tPtr = cmf_status_data[pObj->cmf][pObj->etc];

	if (*tPtr == 0) {
		EnemyMoveCommon(pObj);
		return;
	}

	ret = *tPtr;

	//Motion
	tPtr += (2 + (pObj->frame % ret));
	pObj->motion = *tPtr;

	//DX
	tPtr += ret;
	pObj->dx = *tPtr * DIR(pObj->dirX);

	//DY
	tPtr += ret;
	pObj->dy = *tPtr;

	//디브 메로 데미지 받았는지 체크
	for (i = ENEMY; i < NEUTRAL; i++) {
		if (i != obj && ao[i].active && pObj->attacked == false && AttackCrash(&ao[i], pObj)) {
			pObj->attacked = true;
			pObj->attackedFrame = ATTACKEDFRAME;
#ifdef ATTACKEDINVINCIBLE
			pObj->invincible = ATTACKEDFRAME;
#endif
			pObj->hp -= 20;
		}
	}

	EnemyMoveCommon(pObj);
}

void AppearBossMove(OBJECT* pObj)
{
	pObj->y += pObj->dy;
	pObj->dy += 3 * _2X;
}

void BoarEventMove(OBJECT* pObj)
{
	const signed short* tPtr;
	int ret;
	signed char dest = pObj->type == ENEMY;

	//공격시 멈춤

	dest = GetDistance(pObj, &ao[PLAYER]) > GetDistance(pObj, &ao[dest]) ? dest : PLAYER;

	if (GetDistance(pObj, &ao[dest]) <= 30 * _2X) {
		pObj->dirX = pObj->dirF = ao[dest].x < pObj->x ? LEFT : RIGHT;
		pObj->etc = BOAR_ATTACK;
	}
	else if (pObj->type == ENEMY_TREE
		|| pObj->type == ENEMY_TREE_RED
		|| pObj->type == ENEMY_TREE_BLUE
		|| pObj->type == ENEMY_TREE_PURPLE
		|| pObj->type == ENEMY_TREE_GREEN
		|| pObj->type == ENEMY_TREE_GOLD
		|| pObj->type == ENEMY_TREE_BLACK) {
		pObj->dirX = pObj->dirF = ao[dest].x < pObj->x ? LEFT : RIGHT;
		pObj->etc = TREE_MOVE;
	}
	else {
		pObj->dirF = pObj->dirX = LEFT;
		pObj->etc = 6;
	}

	if (pObj->etc >= 0) {
		tPtr = cmf_status_data[pObj->cmf][pObj->etc];

		if (*tPtr == 0) {
			EnemyMoveCommon(pObj);
			return;
		}

		ret = *tPtr;

		//Motion
		tPtr += (2 + (pObj->frame % ret));
		pObj->motion = *tPtr;

		//DX
		tPtr += ret;
		pObj->dx = *tPtr * DIR(pObj->dirX);

		//DY
		tPtr += ret;
		pObj->dy = *tPtr;
	}

	EnemyMoveCommon(pObj);
}

void Bullet3wayMove(OBJECT* pObj)
{
	int obj = GetObjFromPtr(pObj);

	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	int collectionIdx = GetCollectionIdx(it->type, it->detail, it->grade);
	//만약 주인공쪽 공격스킬이면
	if (pObj->mom < PLAYERALL && pObj->hitCount > 0 && IsHitPossible(pObj, &ao[pObj->mom])) {
		switch (pObj->status) {
		case 0:
			pObj->x += DIR(pObj->dirF) * 4 * _2X;
			break;
		case 3:
			pObj->x += DIR(pObj->dirF) * 4 * _2X;
			break;
		default:
			pObj->x += DIR(pObj->dirF) * 4 * _2X;
			break;
		}
	}
	else {
		switch (pObj->status) {
		case 0:
			pObj->x += DIR(pObj->dirF) * 4 * _2X;
			break;
		case 3:
			pObj->x += DIR(pObj->dirF) * 4 * _2X;
			break;
		default:
			pObj->x += DIR(pObj->dirF) * 4 * _2X;
			break;
		}
	}

	if (ao[pObj->mom].type == ENEMY_LABETH
		|| ao[pObj->mom].type == ENEMY_LABETH_RED
		|| ao[pObj->mom].type == ENEMY_LABETH_BLUE
		|| ao[pObj->mom].type == ENEMY_LABETH_PURPLE
		|| ao[pObj->mom].type == ENEMY_LABETH_GREEN
		|| ao[pObj->mom].type == ENEMY_LABETH_GOLD
		|| ao[pObj->mom].type == ENEMY_LABETH_BLACK) {
		InitMotion(pObj);
		pObj->motion++;
		if (pObj->motion > PO_C109_FIRE2)
			pObj->motion = PO_C109_FIRE0;
	}

	if (pObj->status != 3)
		pObj->y += pObj->status * BULLET_3WAY_DY;

	if (BoundaryCheck(pObj))
		memset(pObj, 0, sizeof(OBJECT));

	//적 시작인덱스보다 작으면 적을 공격하고
	if (obj < ENEMYUSEROBJ) {
		AttackEnemyCheck(GetObjFromPtr(pObj));
	}
	//
	else
		AttackPlayerCheck(pObj);

	if (pObj->frame > FPS * 3)
		memset(pObj, 0, sizeof(OBJECT));

	pObj->frame++;
}

void BulletLaserMove(OBJECT* pObj)
{
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	int collectionIdx = GetCollectionIdx(it->type, it->detail, it->grade);

	pObj->status = 0;
	pObj->x += DIR(pObj->dirX) * BULLET_LASER_DX;// *(BULLET_LASER_DX + pObj->frame/*(pObj->frame / (FPS / 5))*/);

	GetTile(pObj);

	if (TileCrash(pObj) || pObj->x < TSIZE) {
		pObj->x -= DIR(pObj->dirX) * BULLET_LASER_DX;// (BULLET_LASER_DX + pObj->frame/*(pObj->frame / (FPS / 5))*/);
		pObj->dirF = pObj->dirX = 1 - pObj->dirX;
		pObj->status = 1;
	}

	pObj->y += DIR(pObj->dirY) * BULLET_LASER_DX;// (BULLET_LASER_DX + pObj->frame/*(pObj->frame / (FPS / 5))*/);

	if (TileCrash(pObj)) {
		pObj->y -= DIR(pObj->dirY) * BULLET_LASER_DX;// (BULLET_LASER_DX + pObj->frame/*(pObj->frame / (FPS / 5))*/);
		pObj->dirY = 1 - pObj->dirY;
		pObj->status += 10;
	}

	pObj->motion = PO_C1_RLAY_SHOT0 + pObj->dirY;

	if (pObj->frame > FPS * 3)
		memset(pObj, 0, sizeof(OBJECT));

	AttackEnemyCheck(GetObjFromPtr(pObj));

	pObj->frame++;
}

void BulletBombMove(OBJECT* pObj)
{
	int loop = 0;

	if (pObj->status == 0) {
		do {
			loop++;
			pObj->x += DIR(pObj->dirF) * BULLET_BOMB_DX;

			//벽과 충돌체크
			GetTile(pObj);

			if (TileCrash(pObj)) {
				pObj->x -= DIR(pObj->dirF) * BULLET_BOMB_DX;
				pObj->frame = 0;
				pObj->status = 1;
				pObj->x += ClearGap(pObj, 0);

				break;
			}
		} while (loop < 2);
	}

	if (pObj->status == 1) {
		if (IsHitPossible(pObj, &ao[DIANA]) == false || ao[pObj->target].dead == true)
			//(ao[ao[PLAYER].target].dead == true || ao[ao[PLAYER].target].active == false) == true)
			memset(pObj, 0, sizeof(OBJECT));
		else
			pObj->motion = bombShotMotion[pObj->frame];
	}
	//else if (BoundaryCheck(pObj))
	//	memset(pObj, 0, sizeof(OBJECT));

	InitMotion(pObj);

	loop = AttackEnemyCheck(GetObjFromPtr(pObj));

	if (loop && pObj->status == 0) {
		if (pObj->dirF == LEFT)
			pObj->x = PxlRight(&ao[loop]);
		else
			pObj->x = PxlLeft(&ao[loop]);

		pObj->ax = 0;
		pObj->frame = 0;
		pObj->status = 1;

		switch (ao[loop].type) {
		default:
			ao[loop].debuf[STUN] = STUN_START_FRAME;
			break;
		}
	}

	pObj->frame++;
}

void BulletGuidedMove(OBJECT* pObj)
{
	int rt;

	if (pObj->status >= 10) {
		pObj->frame += pObj->status;
		pObj->motion = (pObj->frame / 16) % 8;

		if (pObj->dx)
			pObj->dx -= DIR(pObj->dirF) * _2X;

		if (pObj->frame >= 16 * 8) {
			pObj->status = 0;
			pObj->frame = 2;

			pObj->attack = GetClosestObj(pObj);

			if (!pObj->attack) {
				if (pObj->dirF == LEFT)
					pObj->dx = -12 * _2X;
				else
					pObj->dx = 12 * _2X;
			}
		}
	}
	else {
		if (pObj->attack < ENEMY || pObj->attack >= NEUTRAL || EnemyCheck(pObj->attack) == false || ao[pObj->attack].active == false) {
			pObj->dy = 0;

			if (ao[pObj->attack].active == false) {
				pObj->attack = pObj->target;

				pObj->attack = GetClosestObj(pObj);

				if (!pObj->attack) {
					if (pObj->dirF == LEFT)
						pObj->dx = -12 * _2X;
					else
						pObj->dx = 12 * _2X;
				}
			}


			if (BoundaryCheck(pObj))
				memset(pObj, 0, sizeof(OBJECT));
		}
		else if (pObj->attack != pObj->target) {

			if (!pObj->attack) {
				if (pObj->dirF == LEFT)
					pObj->dx = -12 * _2X;
				else
					pObj->dx = 12 * _2X;
			}
			else
				GotoObj(&ao[pObj->attack], pObj, pObj->frame * _2X);

			if (pObj->frame < 12)
				pObj->frame += pObj->frame;
		}

		if (pObj->dx == 0)
			pObj->motion = (pObj->dy <= 0) ? 2 : 6;
		else {
			temp = pObj->dy * 100 / pObj->dx;

			if (pObj->dx > 0) {
				if (temp >= 263)
					pObj->motion = 6;
				else if (temp >= 38)
					pObj->motion = 5;
				else if (temp > -38)
					pObj->motion = 4;
				else if (temp > -263)
					pObj->motion = 3;
				else
					pObj->motion = 2;
			}
			else {
				if (temp >= 263)
					pObj->motion = 2;
				else if (temp >= 38)
					pObj->motion = 1;
				else if (temp > -38)
					pObj->motion = 0;
				else if (temp > -263)
					pObj->motion = 7;
				else
					pObj->motion = 6;
			}
		}

		//pObj->dx += guidedShotDx[(pObj->motion % 8) * 2];
		//pObj->dy += guidedShotDx[(pObj->motion % 8) * 2 + 1];
	}

	pObj->motion += PO_C1_MISSILE_SHOT0;
	pObj->x += pObj->dx;
	pObj->y += pObj->dy;

	if (pObj->attack > pObj->target) {
		InitMotion(pObj);

		rt = AttackEnemyCheck(GetObjFromPtr(pObj));
		if (rt) {
#ifdef POISONMISSILE
			//pObj //미사일
			//pObj->attack //타겟
			//미사일에 맞으면 중독을 발생시킨다.
			ao[rt].debuf[POISON] = POISON_START_FRAME;
			ao[rt].debufOwner[POISON] = pObj->target;
#endif

			memset(pObj, 0, sizeof(OBJECT));
		}
	}
}

void BulletSateliteMove(OBJECT* pObj)
{
	if (pObj->frame == DIANA_SKILL_SATELLITESHOT_CNT)
		memset(pObj, 0, sizeof(OBJECT));
	else if (pObj->frame >= 24 && pObj->frame < DIANA_SKILL_SATELLITESHOT_CNT) {
		pObj->apx = -128 * _2X;
		pObj->ax = 256 * _2X;
		pObj->apy = -pObj->y;
		pObj->ay = pObj->y;
	}

	pObj->frame++;

	AttackEnemyCheck(GetObjFromPtr(pObj));
}

void BulletHealMove(OBJECT* pObj)
{
	int obj = GetObjFromPtr(pObj);
	pObj->motion = pObj->frame + PO_C1_HEAL9 - 1;

	if (pObj->frame == 1) {
		//여기서 힐

		PlusHp(&ao[pObj->mom], RoundDiv(ao[pObj->mom].ps[PS_HP] * GetSkillValue(pObj->mom, SKILL_DIANA13), 100));
		if (!pObj->hpRestore)
			pObj->hpRestore = 1;
	}
	else if (pObj->frame > 8)
		memset(pObj, 0, sizeof(OBJECT));

	pObj->frame++;
}

void BulletBoomerangMove(OBJECT* pObj)
{
	int i, rt;
	
	if (!pObj->motion) {
		boomerangAway[pObj->target] = false;
		memset(pObj, 0, sizeof(OBJECT));
		return;
	}

	switch (pObj->etc) {
	case 0:
		//수평전진
		pObj->icon = pObj->x;
		pObj->name = pObj->y;

		pObj->x += pObj->dx;
		pObj->y += pObj->dy;

		pObj->dx += pObj->hp;
		pObj->dy += pObj->maxhp;

		//if (DistanceCheck(&ao[pObj->target], pObj, 32 * _2X)) {
		//	pObj->dx = -1;
		//	pObj->dy = 0;
		//}

		//else
		//	GotoObj(&ao[pObj->target], pObj, 8 * _2X);

		if (pObj->dx * DIR(pObj->dirF) < 0) {
			//if (DistanceCheck(&ao[pObj->target], pObj, 32 * _2X)) {
			pObj->dy /= 2;

			switch (pObj->attack) {
			case MAXX_SKILL_CAMPING:
				pObj->etc = 3;
				break;
			default:
				pObj->icon = 0;
				pObj->motion = PO_C2_A_BUME0;
			case MAXX_SKILL_HORMING:
				pObj->etc = 6;
				break;
			}
		}
		break;
	case 1:
		//수직전진
		pObj->x += pObj->dx;
		pObj->y += pObj->dy;

		pObj->dx += pObj->hp;
		pObj->dy += pObj->maxhp;

		if (pObj->dy * DIR(pObj->dirY) > 0) {
			pObj->etc = 6;
			pObj->dx /= 2;
			pObj->motion = PO_C2_A_BUME0;

			if (pObj->attack == ATTACK_DOWN)
				pObj->attack = ATTACK_NORMAL;
		}
		break;
	case 2:
		//유도
		pObj->icon = pObj->x;
		pObj->name = pObj->y;

		pObj->hp = pObj->dx / 2;
		pObj->maxhp = pObj->dy / 2;

		GotoObj(&ao[pObj->attackFrame], pObj, 8 * _2X);

		pObj->dx += pObj->hp;
		pObj->dy += pObj->maxhp;

		if (pObj->dx > 24 * _2X)
			pObj->dx = 24 * _2X;
		else if (pObj->dx < -24 * _2X)
			pObj->dx = -24 * _2X;

		if (pObj->dy > 24 * _2X)
			pObj->dy = 24 * _2X;
		else if (pObj->dy < -24 * _2X)
			pObj->dy = -24 * _2X;

		pObj->x += pObj->dx;
		pObj->y += pObj->dy;

		InitMotion(pObj);

		if (DistanceCheck(&ao[pObj->attackFrame], pObj, 32 * _2X))
			pObj->etc = 6;

		pObj->frame++;
		break;
	case 3:
		//캠핑
		pObj->frame++;
		if (IsHitPossible(pObj, &ao[pObj->target]) == false || ao[pObj->target].dead == true || ao[pObj->target].active == false) {
			pObj->frame = 0;
			pObj->etc = 6;
		}
		break;
	case 4:
		//써클

	{
		int degree = (pObj->dirF == LEFT ? 150 + pObj->frame * 30 : 330 + pObj->frame * 330);

		ao[pObj->target].y -= 8 * _2X;
		pObj->x = ao[pObj->target].x + (BC_mathCos1024(degree) * 30 >> 10) * _2X - (BC_mathSin1024(degree) * 30 >> 10) * _2X;
		pObj->y = ao[pObj->target].y + (BC_mathSin1024(degree) * 30 >> 10) * _2X + (BC_mathCos1024(degree) * 30 >> 10) * _2X;
		ao[pObj->target].y += 8 * _2X;
	}

	pObj->frame++;

	if (IsHitPossible(pObj, &ao[pObj->target]) == false) {
		pObj->active = false;
		boomerangAway[pObj->target] = false;
		//ao[pObj->target].attackFrame = skillClosingFrame[ao[pObj->target].attack];

		if (ao[pObj->target].attack == 0) {
			ao[pObj->target].attack = 1;
			ao[pObj->target].attackFrame = 10 + MAXX_ATTACK_DELAY;
			ao[pObj->target].motion = PO_C2_STOP0;
		}
	}
	break;
	case 5:
		//메가

		pObj->x += pObj->dx;

		if (BoundaryCheck(pObj)) {
			pObj->dx /= 2;
			pObj->x += (pObj->dx < 0 ? 480 * _2X : -480 * _2X);
			pObj->frame = -100000;
			pObj->etc = 6;
		}
		break;
	case 6:
		//복귀
		if (pObj->frame < 5) {
			pObj->icon = pObj->x;
			pObj->name = pObj->y;

			if (pObj->frame == 3)
				pObj->status = 1;
		}
		else {
			pObj->motion = PO_C2_A_BUME0;
			pObj->icon = 0;
		}

		if (pObj->attack == MAXX_SKILL_MEGA && Abs(pObj->x - ao[pObj->target].x) < 16 * _2X)
			pObj->motion = PO_C2_A_BUME0;

		pObj->hp = pObj->dx;
		pObj->maxhp = pObj->dy;

		// 자신을 소환한 캐릭터에게 복귀
		GotoObj(&ao[pObj->target], pObj, 3 * _2X);
		pObj->dy *= 2;

		pObj->dx += pObj->hp;
		pObj->dy += pObj->maxhp;

		if (pObj->dx > 24 * _2X)
			pObj->dx = 24 * _2X;
		else if (pObj->dx < -24 * _2X)
			pObj->dx = -24 * _2X;

		if (pObj->dy > 24 * _2X)
			pObj->dy = 24 * _2X;
		else if (pObj->dy < -24 * _2X)
			pObj->dy = -24 * _2X;

		pObj->x += pObj->dx;
		pObj->y += pObj->dy;

		InitMotion(pObj);

		//for (i = PLAYER; i < PLAYERALL; i++) {
		for (i = ROBIN; i < SOLDIER + 1; i++) {
			if (pObj->target == i) {
				if (ObjCrash(&ao[i], pObj)) {
					pObj->active = false;
					boomerangAway[pObj->target] = false;

					//부메랑을 받을때, 다람쥐로 변신한 상태라면 스탑모션을 하지 않는다.
					if (ao[i].attack == 0) {
						ao[i].attack = 1;
						ao[i].attackFrame = 10 + MAXX_ATTACK_DELAY;
						ao[i].motion = PO_C2_STOP0;
					}

					//memset(pObj, 0, sizeof(OBJECT));
				}
			}
		}
		/*
		if (pObj->target == SOLDIER) {
			if (ObjCrash(&ao[SOLDIER], pObj)) {
				pObj->active = false;
				boomerangAway[pObj->target] = false;

				//부메랑을 받을때, 다람쥐로 변신한 상태라면 스탑모션을 하지 않는다.
				if (ao[SOLDIER].attack == 0) {
					ao[SOLDIER].attack = 1;
					ao[SOLDIER].attackFrame = 10 + MAXX_ATTACK_DELAY;
					ao[SOLDIER].motion = PO_C2_STOP0;
				}

				//memset(pObj, 0, sizeof(OBJECT));
			}
		}
		*/
		pObj->frame++;
		break;
	}

	InitMotion(pObj);

	if (pObj->status || pObj->attack >= ATTACK_SKILL) {
		rt = AttackEnemyCheck(GetObjFromPtr(pObj));
		if (rt && pObj->attack == MAXX_SKILL_HORMING) {
#ifdef HOMINGHUNTCURSE
			ao[rt].debuf[CURSE] = CURSE_START_FRAME / 2;//적에게 걸 때는 절반
			ao[rt].debufOwner[CURSE] = pObj->target;
#endif
		}
	}
}

void BulletTongueMove(OBJECT* pObj)
{
	int obj = GetObjFromPtr(pObj);
	if (obj < ENEMYUSEROBJ)
		AttackEnemyCheck(obj);
	else {
		if (AlivePlayerCnt() == false)
			AttackBoxCheck(pObj);
	}

	if (pObj->type != ENEMY_MACHINE
		&& pObj->type != ENEMY_MACHINE_RED
		&& pObj->type != ENEMY_MACHINE_BLUE
		&& pObj->type != ENEMY_MACHINE_PURPLE
		&& pObj->type != ENEMY_MACHINE_GREEN
		&& pObj->type != ENEMY_MACHINE_GOLD
		&& pObj->type != ENEMY_MACHINE_BLACK)
		memset(pObj, 0, sizeof(OBJECT));
	else {
		if (pObj->frame == 10)
			pObj->attack -= 2;

		pObj->motion = pObj->attack + pObj->frame % 2;

		if (pObj->frame > 20)
			memset(pObj, 0, sizeof(OBJECT));
	}

	InitMotion(pObj);
	pObj->frame++;
}

void FollowMove(OBJECT* pObj)
{
	int rt = 0;

	GotoObj(&ao[pObj->target], pObj, 6 * _2X);
	pObj->x += pObj->dx;
	pObj->y += pObj->dy;
	InitMotion(pObj);
	pObj->frame++;

	rt = AttackEnemyCheck(GetObjFromPtr(pObj));
	if (rt) {
#ifndef SPEEDTURN
		//여기서 총탄을 쏜 다음에 다음 턴으로 넘겨준다.
		if (pObj->mom == turn) {
			//WhoIsNextTurn();
			//스킬마크가 없을 수도 있다(GetControlMark()가 -1). 가드 없이 쓰면 배열 밖에 write한다.
			int markIdx = GetControlMark(pObj->mom);

			if (markIdx >= 0)
				controlMark[markIdx].alpha = 1;

			ao[pObj->mom].turnPosition = DMGUPDATE;
			onceDmgUpdateFrame = 2 * FPS;
		}
#endif
		memset(pObj, 0, sizeof(OBJECT));
		return;
	}

	//유도탄은 맞기 전에는 스스로 사라지지 않는다. 그런데 턴을 넘겨주는 경로는 "이 총알이 적에게
	//맞았을 때"뿐이라(위 DMGUPDATE), 대상이 다른 원인으로 먼저 죽거나 사라지면 총알이 시체를
	//영원히 쫓고 크루는 THERE에 갇혀 전투 전체가 멈춘다(다음 턴인 히어로 공격이 아예 안 나감).
	//대상이 사라졌거나 너무 오래 날았으면 총알을 지우고 턴을 진행시킨다.
	if (ao[pObj->target].active == false || ao[pObj->target].dead == true || pObj->frame > 3 * FPS) {
		if (pObj->mom == turn && ao[pObj->mom].turnPosition == THERE) {
			ao[pObj->mom].turnPosition = DMGUPDATE;
			onceDmgUpdateFrame = 2 * FPS;
		}

		memset(pObj, 0, sizeof(OBJECT));
	}
}

void FollowMomMove(OBJECT* pObj)
{
	pObj->x = ao[pObj->mom].x;
	pObj->y = ao[pObj->mom].y;
}

void HandMove(OBJECT* pObj)
{
	const signed short* tPtr;
	int ret, tempEtc;
	int tempX;

	// 모션 잡기
	tPtr = cmf_status_data[pObj->cmf][pObj->etc];

	ret = *tPtr;

	tPtr += (2 + (pObj->frame % ret));
	pObj->motion = *tPtr;

	pObj->x += pObj->dx;
	pObj->y += pObj->dy;
	tempEtc = pObj->etc;

	if (isDemo) {
		pObj->dx = 0;
		pObj->dy = 0;
		pObj->x = GetObjFromPtr(pObj) > pObj->tileX1 ? 72 * _2X : 250 * _2X;
		pObj->y = GetObjFromPtr(pObj) > pObj->tileX1 ? 156 * _2X : 100 * _2X;
		return;
	}

	// ETC 변경하기
	switch (pObj->etc) {
	case CASTLEBOSS4_HAND_NEUTRAL:
		if (isDemo == false)
			pObj->etc = CASTLEBOSS4_HAND_MOVE;
		break;
	case CASTLEBOSS4_HAND_MOVE:
		//y 축방향 전환
		if (Abs(pObj->dy) > 3 * _2X)
			pObj->dirY = 1 - pObj->dirY;
		//dx 조정
		if (pObj->x < 10 * _2X || pObj->x >(rw - 1) * TSIZE - 10 * _2X)
			pObj->dx *= -1;// *_2X;
		//dy 조정
		if (pObj->dirY == UP)
			pObj->dy -= 1;// *_2X;
		else
			pObj->dy += 1;// *_2X;

		//플레이어 잡기로 전환
		if (pObj->jumpFrame > 100 + Random(100) && ao[pObj->tileX1].etc < CASTLEBOSS4_HAND_GRABMOVE) {
			pObj->etc = CASTLEBOSS4_HAND_GRABMOVE;
			pObj->dx = pObj->dy = 0;
		}

		//내려찍기로 전환
		if (pObj->frame > 36 && Abs(pObj->x - ao[NearPlayer(pObj)].x) < 20 * _2X) {
			pObj->etc = CASTLEBOSS4_HAND_DOWN;
			pObj->dx = pObj->dy = 0;
		}
		break;
	case CASTLEBOSS4_HAND_DOWN:
		pObj->dirY = DOWN;
		pObj->dy = Min(16, pObj->dy += 2);// *_2X;

		if (pObj->y >= 280 * _2X) {
			effect.shake = 2;
			pObj->y = 288 * _2X;
			pObj->dy = 0;
			pObj->etc = CASTLEBOSS4_HAND_ATTACK;
		}
		break;
	case CASTLEBOSS4_HAND_ATTACK:
		if (pObj->frame > 6)
			pObj->etc = CASTLEBOSS4_HAND_RETURN;
		break;
	case CASTLEBOSS4_HAND_RETURN:
		pObj->dy = Max(-16, pObj->dy -= 2);

		if (pObj->y <= 160 * _2X + 32 * _2X - (50 * pObj->dirX) * _2X) {
			pObj->dy = 0;
			pObj->dirY = UP;
			pObj->dx = 4 * DIR(pObj->dirX);// *_2X;
			pObj->etc = CASTLEBOSS4_HAND_MOVE;
		}
		break;
	case CASTLEBOSS4_HAND_GRABMOVE:
		pObj->dirY = DOWN;
		GotoObj(&ao[PLAYER], pObj, 8);// *_2X);

		pObj->y -= 10;// *_2X;

		if (GetDistance(&ao[PLAYER], pObj) < 25 * _2X) {
			ao[PLAYER].moveHandler = PLAYERHANDMOVE;
			ao[PLAYER].mom = GetObjFromPtr(pObj);
			pObj->etc = CASTLEBOSS4_HAND_MOMMOVE;
			pObj->dx = pObj->dy = 0;
			pObj->y += 10;// *_2X;
			break;
		}

		pObj->y += 10;// *_2X;

		if (pObj->frame > 30) {
			ao[pObj->tileX1].jumpFrame = 1 + Random(10);//다른손이 바로 잡을수 없도록
			pObj->jumpFrame = 0;
			pObj->etc = CASTLEBOSS4_HAND_RETURN;
			pObj->dy = pObj->dx = 0;
			pObj->dy = 0;
		}
		break;
	case CASTLEBOSS4_HAND_GRAB:
		ao[PLAYER].moveHandler = PLAYERHANDMOVE;
		pObj->etc = CASTLEBOSS4_HAND_MOMMOVE;
		break;
	case CASTLEBOSS4_HAND_MOMMOVE:
		tempX = ao[pObj->mom].x;

		ao[pObj->mom].x += 100 * DIR(ao[pObj->mom].dirX);// *_2X;

		if (GetDistance(&ao[pObj->mom], pObj) > 40 * _2X)
			GotoObj(&ao[pObj->mom], pObj, 4);// *_2X);
		else pObj->dx = pObj->dy = 0;

		ao[pObj->mom].x = tempX;

		// 손이 벽을뚫고 지나갈 수 없게
		//if (pObj->x < 48 * _2X)
		//	pObj->x = 48 * _2X;
		//else if (pObj->x > 272 * _2X)
		//	pObj->x = 272 * _2X;

		// 손이 수직으로만 갈수 있게
		pObj->x = ao[PLAYER].nx;

		if (pObj->frame > 200) {
			ao[PLAYER].moveHandler = PLAYERMOVE;
			ao[pObj->tileX1].jumpFrame = 1 + Random(10);//다른손이 바로 잡을수 없도록
			pObj->jumpFrame = 0;
			pObj->etc = CASTLEBOSS4_HAND_RETURN;
			pObj->dy = pObj->dx = 0;
		}
		break;
	}

	//etc가 바뀌면 frame초기화
	if (pObj->etc != tempEtc)
		pObj->frame = 0;

	InitMotion(pObj);
	pObj->frame++;
	pObj->jumpFrame++;
}

void BulletSpinMove(OBJECT* pObj)
{
	GetTile(pObj);

	if (pObj->frame < 32) {			// 회전 프레임 수(수정필요)
		pObj->status = 0;
		pObj->x += DIR(pObj->dirX) * BULLET_LASER_DX;

		if (TileCrash(pObj) || pObj->y - pObj->cy <= 0) {
			pObj->x -= DIR(pObj->dirX) * BULLET_LASER_DX;
			pObj->dirF = pObj->dirX = 1 - pObj->dirX;
			pObj->status = 1;
		}

		pObj->y += DIR(pObj->dirY) * BULLET_LASER_DX;

		if (TileCrash(pObj)) {
			pObj->y -= DIR(pObj->dirY) * BULLET_LASER_DX;
			pObj->dirY = 1 - pObj->dirY;
			pObj->status += 10;
		}

		pObj->motion = PO_C34_SPINATK4 + (pObj->frame / 2 % 2);
		InitMotion(pObj);

		pObj->frame++;
	}
	else {
		pObj->motion = PO_C34_N3;
		InitMotion(pObj);
		pObj->etc = KIMERA_LAND_READY;
		pObj->moveHandler = ENEMYMOVE;
		//pObj->moveHandler = ENEMYMOVETURN;
		pObj->jumpFrame = 0;
		pObj->status = FALL;
		pObj->dirY = DOWN;
	}
}

void BulletGuideMove(OBJECT* pObj)
{
	if (pObj->status == 0) {
		if (isDemo == true && ObjCrash(pObj, &ao[ao[PLAYER].target])) {
			pObj->frame = 0;
			pObj->status = 1;
		}
		else if (isDemo == false) {
			if (GetObjFromPtr(pObj) < ENEMY && ObjCrash(pObj, &ao[ao[PLAYER].target])) {
				pObj->frame = 0;
				pObj->status = 1;
			}
			else if (GetObjFromPtr(pObj) >= ENEMY && ObjCrash(pObj, &ao[pObj->target])) {
				pObj->frame = 0;
				pObj->status = 1;
			}
		}
		else if (pObj->frame == FPS) {
			pObj->frame = 0;
			pObj->status = 1;
		}
	}

	if (pObj->status == 1) {
		pObj->motion = PO_C37_SHOT0 + pObj->frame / 4;
		pObj->dx = 0;
		pObj->dy = 0;

		if (pObj->frame >= 7 * 4) {
			memset(pObj, 0, sizeof(OBJECT));
			return;
		}
	}
	else {
		if (GetObjFromPtr(pObj) < PLAYERALL)
			GotoObj(&ao[ao[PLAYER].target], pObj, 8 * _2X);
		else
			GotoObj(&ao[NearPlayer(pObj)], pObj, 8 * _2X);
		pObj->motion = PO_C37_SHOT0;
		pObj->x += pObj->dx;
		pObj->y += pObj->dy;
	}

	if (pObj->frame > FPS * 2) {
		pObj->status = 1;
		pObj->frame = 0;
	}

	InitMotion(pObj);
	pObj->frame++;
}

void Bullet3wayDirMove(OBJECT* pObj)
{
	if (pObj->status < 2) {
		pObj->y -= TSIZE >> 1;
		pObj->x += pObj->etc * 8 * _2X;
	}
	else if (pObj->status < 4) {
		pObj->y += TSIZE >> 1;
		pObj->x += pObj->etc * 8 * _2X;
	}
	else if (pObj->status % 2 == 0) {
		pObj->x += TSIZE >> 1;
		pObj->y += pObj->etc * 8 * _2X;
	}
	else {
		pObj->x -= TSIZE >> 1;
		pObj->y += pObj->etc * 8 * _2X;
	}

	if (BoundaryCheck(pObj))
		memset(pObj, 0, sizeof(OBJECT));
}

void BulletItemMove(OBJECT* pObj)
{
	pObj->jumpFrame = pObj->hp;
	pObj->attackFrame = pObj->maxhp;

	pObj->hp = pObj->x;
	pObj->maxhp = pObj->y;

	//터지기 전
	if (pObj->status == 0) {
		pObj->x += pObj->dx * DIR(pObj->dirF);
		pObj->y += pObj->dy;
		pObj->dy += 2 * _2X;

		if (pObj->mainFrame > 4) {
			pObj->apx = -8 * _2X;
			pObj->apy = -8 * _2X;
			pObj->cpx = -8 * _2X;
			pObj->cpy = -8 * _2X;
			pObj->ax = 16 * _2X;
			pObj->ay = 16 * _2X;
			pObj->cx = 16 * _2X;
			pObj->cy = 16 * _2X;

			if (AttackEnemyCheck(GetObjFromPtr(pObj)) || TileCrash(pObj)) {
				pObj->status = 1;
				pObj->mainFrame = 0;
			}
		}
	}
	//터진 후
	else {
		pObj->cx = 0;
		pObj->cy = 0;

		if (pObj->etc) {
			pObj->apx = -32 * _2X;
			pObj->apy = -32 * _2X;
			pObj->ax = 64 * _2X;
			pObj->ay = 64 * _2X;
		}
		else {
			pObj->apx = -16 * _2X;
			pObj->apy = -16 * _2X;
			pObj->ax = 32 * _2X;
			pObj->ay = 32 * _2X;
		}

		if (pObj->mainFrame == 5)
			pObj->active = false;
	}

	pObj->mainFrame++;
}

void Bullet4wayMove(OBJECT* pObj)
{
	switch (pObj->status) {
	case 0:
		pObj->dx = 16 * DIR(pObj->dirF) * _2X;
		pObj->dy = 4 * _2X;
		break;
	case 1:
		pObj->dx = 12 * DIR(pObj->dirF) * _2X;
		pObj->dy = 8 * _2X;
		break;
	case 2:
		pObj->dx = 8 * DIR(pObj->dirF) * _2X;
		pObj->dy = 12 * _2X;
		break;
	case 3:
		pObj->dx = 2 * DIR(pObj->dirF) * _2X;
		pObj->dy = 16 * _2X;
		break;
	}

	pObj->x += pObj->dx;
	pObj->y += pObj->dy;

	if (pObj->frame > 15)
		memset(pObj, 0, sizeof(OBJECT));

	pObj->frame++;
}

void LabethMagicMove(OBJECT* pObj)
{
	int i, cnt;
	int nearObj = NearPlayer(pObj);

	if (pObj->frame < 15) {
		ao[nearObj].y -= 100 * _2X * pObj->zoom;
		if (ao[nearObj].y - pObj->y < 10 * _2X * pObj->zoom) {
			GotoObj(&ao[nearObj], pObj, 10 * _2X * pObj->zoom);
			pObj->x += pObj->dx;
			pObj->y += pObj->dy;
		}
		ao[nearObj].y += 100 * _2X * pObj->zoom;
	}
	else if (pObj->frame == 15) {
		//미사일 쏘기
		for (i = ENEMY, cnt = 0; i < NEUTRAL; i++) {
			if (ao[i].active == false) {

				AddObject(&ao[i], pObj, ADDOBJ_LABETHBULLET);
				ao[i].motion += cnt;
				ao[i].dx = 6 * (cnt - 1) * _2X * pObj->zoom;
				cnt++;
				if (cnt > 2)
					break;
			}
		}
	}
	else if (pObj->frame < 20) {}
	else {
		memset(pObj, 0, sizeof(OBJECT));
		return;
	}

	InitMotion(pObj);
	pObj->frame++;
}

void EnemyMove_AddObj(OBJECT* pObj)
{
	int i, dis = 0, tempX, target;
	int obj = GetObjFromPtr(pObj);
	int startObj;
	int endObj;

	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	int collectionIdx = GetCollectionIdx(it->type, it->detail, it->grade);


	if (obj < PLAYERALL) {
		startObj = BULLET;
		endObj = ENEMYUSEROBJ;
	}
	else {
		startObj = ENEMY;
		endObj = NEUTRAL;
	}


	switch (pObj->type) {
	case ENEMY_IFRIT:
	case ENEMY_IFRIT_RED:
	case ENEMY_IFRIT_BLUE:
	case ENEMY_IFRIT_PURPLE:
	case ENEMY_IFRIT_GREEN:
	case ENEMY_IFRIT_GOLD:
	case ENEMY_IFRIT_BLACK:
		pObj->status = FLYING;

		if (pObj->motion == PO_C17_A5) {
			int count = 0;

			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false && ao[i].type == 0 && count < 4) {
					AddObject(&ao[i], pObj, ADDOBJ_IFRIT);
					ao[i].dx = 9 * count * pObj->zoom;
					ao[i].status = count - 1;
					ao[i].etc = 1;

					PlayMusic(M_FIRE);
					count++;
				}
			}
		}
		else if (pObj->motion == PO_C17_A10) {
			for (i = startObj + 1; i < endObj; i++) {
				if (ao[i].moveHandler == SLINGMOVE) {
					if (ao[i].motion == PO_C17_SHOT1)
						ao[i].motion = PO_C17_SHOT2;
					else {
						ao[i].motion = PO_C17_SHOT1;
						ao[i].dx = 0;
					}
				}
			}
		}
		break;
	case ENEMY_ICESUN:
	case ENEMY_ICESUN_RED:
	case ENEMY_ICESUN_BLUE:
	case ENEMY_ICESUN_PURPLE:
	case ENEMY_ICESUN_GREEN:
	case ENEMY_ICESUN_GOLD:
	case ENEMY_ICESUN_BLACK:
		break;
	case ENEMY_LARVA:
	case ENEMY_LARVA_RED:
	case ENEMY_LARVA_BLUE:
	case ENEMY_LARVA_PURPLE:
	case ENEMY_LARVA_GREEN:
	case ENEMY_LARVA_GOLD:
	case ENEMY_LARVA_BLACK:
		pObj->status = FLYING;

		if (pObj->etc == LARVA_HIDED)
			pObj->x = 120 * _2X + Random(140 * _2X);

		switch (pObj->motion) {
		case PO_C8_S2:
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_LARVA);

					PlayMusic(M_JUMP);
					ao[i].etc = 1;
					break;
				}
			}
			//}
			//else {
			//	pObj->frame = 268;//공격 이후로 보낸다.
			//}
			break;
		}
		break;
	case ENEMY_PHOENIX:
	case ENEMY_PHOENIX_RED:
	case ENEMY_PHOENIX_BLUE:
	case ENEMY_PHOENIX_PURPLE:
	case ENEMY_PHOENIX_GREEN:
	case ENEMY_PHOENIX_GOLD:
	case ENEMY_PHOENIX_BLACK:
		pObj->status = FLYING;

		if (pObj->motion == PO_C16_SHOT0) {
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_PHOENIX);

					PlayMusic(M_FIRE);
					break;
				}
			}
		}

		if (pObj->etc == PHOENIX_DASH) {
			if ((pObj->dirF == LEFT && pObj->dx > 0) || (pObj->dirF == RIGHT && pObj->dx < 0))
				pObj->dx *= -1;
		}
		break;
	case ENEMY_SLING:
	case ENEMY_SLING_RED:
	case ENEMY_SLING_BLUE:
	case ENEMY_SLING_PURPLE:
	case ENEMY_SLING_GREEN:
	case ENEMY_SLING_GOLD:
	case ENEMY_SLING_BLACK:
		if (pObj->motion == PO_C12_A2) {
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_SLING);

					ao[i].jumpFrame = 1;
					ao[i].etc = 1;
					PlayMusic(M_JUMP);
					break;
				}
			}
		}
		break;
	case ENEMY_GIANT:
	case ENEMY_GIANT_RED:
	case ENEMY_GIANT_BLUE:
	case ENEMY_GIANT_PURPLE:
	case ENEMY_GIANT_GREEN:
	case ENEMY_GIANT_GOLD:
	case ENEMY_GIANT_BLACK:
		if (pObj->motion == PO_C14_3WAY7) {
			int count = 0;

			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false && count < 3) {
					AddObject(&ao[i], pObj, ADDOBJ_GIANT);

					ao[i].motion += count;
					ao[i].status += count;
					ao[i].y += (count - 1) * 33 * _2X;
					InitMotion(&ao[i]);
					count++;
				}
			}

			PlayMusic(M_GUNSTRONG);
		}
		break;
	case ENEMY_DRAGON2:
	case ENEMY_DRAGON2_RED:
	case ENEMY_DRAGON2_BLUE:
	case ENEMY_DRAGON2_PURPLE:
	case ENEMY_DRAGON2_GREEN:
	case ENEMY_DRAGON2_GOLD:
	case ENEMY_DRAGON2_BLACK:
		if (pObj->motion == PO_C42_A2) {
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_DRAGON2FIRE);

					break;
				}
			}
			PlayMusic(M_FIRE);
		}
		break;
	case ENEMY_SPACE2:
	case ENEMY_SPACE2_RED:
	case ENEMY_SPACE2_BLUE:
	case ENEMY_SPACE2_PURPLE:
	case ENEMY_SPACE2_GREEN:
	case ENEMY_SPACE2_GOLD:
	case ENEMY_SPACE2_BLACK:
		if (pObj->motion == PO_C47_A5 || pObj->motion == PO_C47_A9) {
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_SPACE2BULLET);

					if (obj < PLAYERALL)
						GotoObj(&ao[pObj->target], &ao[i], 12 * _2X);
					else
						GotoObj(&ao[NearPlayer(&ao[i])], &ao[i], 12 * _2X);
					break;
				}
			}
			PlayMusic(M_MACHINE);
		}
		break;
		//라베스 보스
	case NPC_LABETH:
	case ENEMY_LABETH:
	case ENEMY_LABETH_RED:
	case ENEMY_LABETH_BLUE:
	case ENEMY_LABETH_PURPLE:
	case ENEMY_LABETH_GREEN:
	case ENEMY_LABETH_GOLD:
	case ENEMY_LABETH_BLACK:
		if (pObj->etc == 0)
			pObj->etc = 5;

		switch (pObj->motion) {
		case PO_C109_FLAME11:
		case PO_C109_FLAME12:
		case PO_C109_FLAME13:
			//불 생성
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_LABETHFIRE);

					ao[i].dx *= DIR(pObj->dirX);
					ao[i].dirF = ao[i].dirX = pObj->dirX;
					ao[i].y -= (56 * _2X - 32 * (pObj->motion - 41) * _2X) * pObj->zoom;
					break;
				}
			}
			PlayMusic(M_FIRE);
			break;
		case PO_C109_MAGIC6:
			//움직이는 마법진 생성
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_LABETHMAGIC);

					PlayMusic(M_LASER);
					break;
				}
			}
			break;
		}
		break;
		//엘케인 보스
	case ENEMY_ELKEIN:
	case ENEMY_ELKEIN_RED:
	case ENEMY_ELKEIN_BLUE:
	case ENEMY_ELKEIN_PURPLE:
	case ENEMY_ELKEIN_GREEN:
	case ENEMY_ELKEIN_GOLD:
	case ENEMY_ELKEIN_BLACK:
	case NPC_ELKEIN:
		//미사일 발사
		switch (pObj->motion) {
		case PO_C110_BOSS_SA1:
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false && ao[i].type == 0) {
					AddObject(&ao[i], pObj, ADDOBJ_ELKEINBULLET);

					GotoObj(&ao[NearPlayer(&ao[i])], &ao[i], 8 * _2X);
					PlayMusic(M_GUNSTRONG);
					break;
				}
			}
			break;
		case PO_C110_BOSS_CA10:

			tempX = pObj->x;
			// 얼만큼 이동해도 되는지 체크
			for (i = 0; Abs(i) < 50 * _2X * pObj->zoom; i += TSIZE) {
				pObj->x += TSIZE * DIR(pObj->dirX);
				if (TileCrash(pObj) || pObj->x < 10 * _2X * pObj->zoom)
					break;
				else
					dis += TSIZE * DIR(pObj->dirX);
			}
			//이동 가능한만큼 이동하기
			pObj->x = tempX;
			pObj->x += dis;

			PlayMusic(M_MACHINE);
			break;
		}
		break;
	case NPC_DELPIOS:
		if (pObj->etc == 0)
			pObj->etc = 2;

		switch (pObj->motion) {
		case PO_C95_LASER0:
			break;
		}
		break;

	case ENEMY_CASTLE_BOSS2:
	case ENEMY_CASTLE_BOSS2_RED:
	case ENEMY_CASTLE_BOSS2_BLUE:
	case ENEMY_CASTLE_BOSS2_PURPLE:
	case ENEMY_CASTLE_BOSS2_GREEN:
	case ENEMY_CASTLE_BOSS2_GOLD:
	case ENEMY_CASTLE_BOSS2_BLACK:
		if (pObj->motion == PO_C49_SA2) {
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false && ao[i].type == 0) {
					AddObject(&ao[i], pObj, ADDOBJ_ELKEIN2BULLET);

					GotoObj(&ao[NearPlayer(&ao[i])], &ao[i], 8 * _2X);
					PlayMusic(M_MACHINE);
					break;
				}
			}
		}
		else if (pObj->motion == PO_C49_WEAK17) {
			pObj->hp += (pObj->shieldMax - pObj->shield);
			pObj->shield = pObj->shieldMax;
			PlayMusic(M_POWERUP);
		}
		break;
	case ENEMY_CASTLE_BOSS3:
	case ENEMY_CASTLE_BOSS3_RED:
	case ENEMY_CASTLE_BOSS3_BLUE:
	case ENEMY_CASTLE_BOSS3_PURPLE:
	case ENEMY_CASTLE_BOSS3_GREEN:
	case ENEMY_CASTLE_BOSS3_GOLD:
	case ENEMY_CASTLE_BOSS3_BLACK:
		if (isDemo) {
			pObj->etc = 0;
			return;
		}

		//mainFrame 14초마다 한번씩 벌레생성
		if (robin.playtime % (200 - pObj->attack * 10) == 0) {
			for (i = GetObjFromPtr(pObj) + 1; i < NEUTRAL; i++) {
				if (ao[i].active == false && ao[i].type == 0) {
					AddObject(&ao[i], pObj, ADDOBJ_BOSS3BUG);
					ao[i].hp = ao[i].maxhp = pObj->maxhp / 7; //hp = 약 2만정도
					InitBar(BAR_ENEMYHP + GetEnemyBarIdx(i));
					break;
				}
			}
		}

		if (pObj->etc == CASTLEBOSS3_NEUTRAL)
			pObj->attackFrame = 0;

		if (pObj->motion == PO_C50_B1) {
			if (pObj->etc == CASTLEBOSS3_BOMB) {
				for (i = GetObjFromPtr(pObj) + 1; i < NEUTRAL; i++) {
					if (ao[i].active == false && ao[i].type == 0) {
						AddObject(&ao[i], pObj, ADDOBJ_BOSS3BOMB);
						ao[i].dx += 4 * _2X * pObj->attackFrame;
						pObj->attackFrame++;
						break;
					}
				}
			}
			else {
				for (i = GetObjFromPtr(pObj) + 1; i < NEUTRAL; i++) {
					if (ao[i].active == false && ao[i].type == 0) {
						AddObject(&ao[i], pObj, ADDOBJ_BOSS3IMPALE);
						ao[i].x -= pObj->attackFrame * 35 * _2X;
						pObj->attackFrame++;
						break;
					}
				}
			}
		}
		break;
		//테트라쿤
	case ENEMY_CASTLE_BOSS4:
	case ENEMY_CASTLE_BOSS4_RED:
	case ENEMY_CASTLE_BOSS4_BLUE:
	case ENEMY_CASTLE_BOSS4_PURPLE:
	case ENEMY_CASTLE_BOSS4_GREEN:
	case ENEMY_CASTLE_BOSS4_GOLD:
	case ENEMY_CASTLE_BOSS4_BLACK:
		pObj->status = FLYING;
		break;
	}
}

void EnemyMove_AddObj2(OBJECT* pObj)
{
	int i;
	int obj = GetObjFromPtr(pObj);
	int startObj;
	int endObj;

	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	int collectionIdx = GetCollectionIdx(it->type, it->detail, it->grade);

	if (obj < PLAYERALL) {
		startObj = BULLET;
		endObj = ENEMYUSEROBJ;
	}
	else {
		startObj = ENEMY;
		endObj = NEUTRAL;
	}

	switch (pObj->type) {
	case ENEMY_ONEEYE:
	case ENEMY_ONEEYE_RED:
	case ENEMY_ONEEYE_BLUE:
	case ENEMY_ONEEYE_PURPLE:
	case ENEMY_ONEEYE_GREEN:
	case ENEMY_ONEEYE_GOLD:
	case ENEMY_ONEEYE_BLACK:
		if (pObj->etc == ONEEYE_PLAYER_MOVE) {
			if ((pObj->dirF == LEFT && pObj->dx > 0) || (pObj->dirF == RIGHT && pObj->dx < 0))
				pObj->dx *= -1;
		}
	case ENEMY_THUNDER:
	case ENEMY_THUNDER_RED:
	case ENEMY_THUNDER_BLUE:
	case ENEMY_THUNDER_PURPLE:
	case ENEMY_THUNDER_GREEN:
	case ENEMY_THUNDER_GOLD:
	case ENEMY_THUNDER_BLACK:
	case ENEMY_GHOST:
	case ENEMY_GHOST_RED:
	case ENEMY_GHOST_BLUE:
	case ENEMY_GHOST_PURPLE:
	case ENEMY_GHOST_GREEN:
	case ENEMY_GHOST_GOLD:
	case ENEMY_GHOST_BLACK:
	case ENEMY_CIRCLE:
	case ENEMY_CIRCLE_RED:
	case ENEMY_CIRCLE_BLUE:
	case ENEMY_CIRCLE_PURPLE:
	case ENEMY_CIRCLE_GREEN:
	case ENEMY_CIRCLE_GOLD:
	case ENEMY_CIRCLE_BLACK:
	case ENEMY_SPACE1:
	case ENEMY_SPACE1_RED:
	case ENEMY_SPACE1_BLUE:
	case ENEMY_SPACE1_PURPLE:
	case ENEMY_SPACE1_GREEN:
	case ENEMY_SPACE1_GOLD:
	case ENEMY_SPACE1_BLACK:
		pObj->status = FLYING;
		break;
	case ENEMY_DEATH:
	case ENEMY_DEATH_RED:
	case ENEMY_DEATH_BLUE:
	case ENEMY_DEATH_PURPLE:
	case ENEMY_DEATH_GREEN:
	case ENEMY_DEATH_GOLD:
	case ENEMY_DEATH_BLACK:
		pObj->status = FLYING;

		if (pObj->motion == PO_C31_SKEL11) {
			int random = Random(3), count = 0;

			//random = 2;

			switch (random) {
			case 0:
				for (i = ENEMY; i < NEUTRAL; i++) {
					if (ao[i].active == false) {
						AddObject(&ao[i], pObj, ADDOBJ_SKELGUIDE);
						ao[i].etc = 1;
						InitMotion(&ao[i]);
						break;
					}
				}
				break;
			case 1:
				for (i = ENEMY; i < NEUTRAL; i++) {
					if (ao[i].active == false) {
						AddObject(&ao[i], pObj, ADDOBJ_GIANT);
						ao[i].motion = PO_C31_SHOT0 + count;
						ao[i].mom = GetObjFromPtr(pObj);
						ao[i].status += count;
						ao[i].y += (count - 1) * 10;
						count++;
						InitMotion(&ao[i]);
						if (count > 3)
							break;
					}
				}
				break;
			case 2:
				for (i = ENEMY; i < NEUTRAL; i++) {
					if (ao[i].active == false) {
						AddObject(&ao[i], pObj, ADDOBJ_CIRCLEMOVE);
						ao[i].etc = 1;
						ao[i].status = pObj->etc > DEATH_BROKEN ? 2 : 1;
						ao[i].frame = count * 90;
						InitMotion(&ao[i]);
						count++;

						if (count > 4)
							break;
					}
				}
				break;
			}
		}
		break;
	case ENEMY_SPIDER:
	case ENEMY_SPIDER_RED:
	case ENEMY_SPIDER_BLUE:
	case ENEMY_SPIDER_PURPLE:
	case ENEMY_SPIDER_GREEN:
	case ENEMY_SPIDER_GOLD:
	case ENEMY_SPIDER_BLACK:
		if (pObj->etc >= SPIDER_UP_NEUTRAL)
			pObj->status = FLYING;

		if (pObj->motion == PO_C27_D_JUMP2) {
			pObj->y -= TSIZE * pObj->zoom;
			pObj->etc = SPIDER_UP_LANDING;

			if (TileCrash(pObj)) {
				pObj->y -= 64 * _2X * pObj->zoom;
				pObj->y += (TSIZE - (pObj->y % TSIZE)) * pObj->zoom;
				pObj->etc = SPIDER_UP_LAND;
				pObj->frame = 0;
			}
		}
		else if (pObj->motion == PO_C27_U_JUMP2) {
			pObj->y += 32 * _2X * pObj->zoom;
			pObj->etc = SPIDER_ANCHOR_CHANGE;
		}
		else if (pObj->etc == SPIDER_ANCHOR_CHANGE) {
			pObj->y += 46 * _2X * pObj->zoom;
			pObj->status = FALL;
			pObj->jumpFrame = 0;
			pObj->dirY = DOWN;
		}
		break;
	case ENEMY_CRYSTAL:
	case ENEMY_CRYSTAL_RED:
	case ENEMY_CRYSTAL_BLUE:
	case ENEMY_CRYSTAL_PURPLE:
	case ENEMY_CRYSTAL_GREEN:
	case ENEMY_CRYSTAL_GOLD:
	case ENEMY_CRYSTAL_BLACK:
		//mx : 소환물 최대 갯수
		if (obj < PLAYERALL) {
			if (pObj->motion == PO_C23_A1 && pObj->mx < 3) {
				for (i = SOLDIER; i < PLAYERALL; i++) {
					if (ao[i].active == false && ao[i].type == 0) {
						AddObject(&ao[i], pObj, ADDOBJ_CRYSTAL);
						ao[i].dirF = ao[i].dirX = pObj->dirX;
						ao[i].status = pObj->dirX == LEFT ? LEFT_WALK : RIGHT_WALK;
						ao[i].dirY = DOWN;
						ao[i].etc = LIGHTNING_MOVE;
						ao[i].y += ClearGap(&ao[i], 1);
						ao[i].hp = ao[i].maxhp = pObj->maxhp / 10;
						InitMotion(&ao[i]);
						pObj->mx++;
						break;
					}
				}
			}
		}
		else {
			if (pObj->motion == PO_C23_A1 && pObj->mx < 3) {
				for (i = ENEMY; i < NEUTRAL; i++) {
					if (ao[i].active == false && ao[i].type == 0) {
						switch (pObj->type) {
						case ENEMY_CRYSTAL:
							ao[i].type = ENEMY_LIGHTNING;
							break;
						case ENEMY_CRYSTAL_RED:
							ao[i].type = ENEMY_LIGHTNING_RED;
							break;
						case ENEMY_CRYSTAL_BLUE:
							ao[i].type = ENEMY_LIGHTNING_BLUE;
							break;
						case ENEMY_CRYSTAL_PURPLE:
							ao[i].type = ENEMY_LIGHTNING_PURPLE;
							break;
						case ENEMY_CRYSTAL_GREEN:
							ao[i].type = ENEMY_LIGHTNING_GREEN;
							break;
						case ENEMY_CRYSTAL_GOLD:
							ao[i].type = ENEMY_LIGHTNING_GOLD;
							break;
						case ENEMY_CRYSTAL_BLACK:
							ao[i].type = ENEMY_LIGHTNING_BLACK;
							break;
						}
						SetEnemy(&ao[i]);
						if (drawHandle == MD_BATTLE)
							ao[i].zoom = BATTLEZOOM;
						else
							ao[i].zoom = LOBBYZOOM;
						ao[i].nx = ao[i].x = pObj->x - TSIZE / 2;
						ao[i].ny = ao[i].y = pObj->y;
						ao[i].maxhp = ao[i].hp = pObj->maxhp / 10;

						InitMotion(&ao[i]);
						InitBar(BAR_ENEMYHP + GetEnemyBarIdx(i));
						bar[BAR_ENEMYHP + GetEnemyBarIdx(i)].max = bar[BAR_ENEMYHP + GetEnemyBarIdx(i)].count = ao[i].maxhp;
						//AddBar(&bar[BAR_ENEMYHP + GetEnemyBarIdx(i)], ao[i].maxhp, BARFRAME);

						pObj->mx++;
						pObj->frame = 0;
						pObj->etc = CRYSTAL_NEUTRAL;
						break;
					}
				}
			}
		}
		break;
	case ENEMY_DARKDRAGON:
	case ENEMY_DARKDRAGON_RED:
	case ENEMY_DARKDRAGON_BLUE:
	case ENEMY_DARKDRAGON_PURPLE:
	case ENEMY_DARKDRAGON_GREEN:
	case ENEMY_DARKDRAGON_GOLD:
	case ENEMY_DARKDRAGON_BLACK:
		pObj->moveHandler = MOBIUSMOVE;
		pObj->status = 0;

		for (i = ENEMY; i < NEUTRAL; i++) {
			if (ao[i].active == false && pObj->status <= 3) {
				AddObject(&ao[i], pObj, ADDOBJ_DARKDRAGON);
				//ao[i].dx = pObj->dx;
				//ao[i].dy = pObj->dy;
				ao[i].status = ++pObj->status;

				if (pObj->status == 4) {
					ao[i].attack = ao[i].motion = PO_C38_NTAIL0;
					ao[i].etc = 2;
				}
				else {
					ao[i].attack = ao[i].motion = PO_C38_NBODY0;
					ao[i].etc = 1;
				}
			}
		}

		//pObj->moveHandler = ENEMYMOVETURN;
		pObj->status = 0;
		break;
	case ENEMY_ANGEL:
	case ENEMY_ANGEL_RED:
	case ENEMY_ANGEL_BLUE:
	case ENEMY_ANGEL_PURPLE:
	case ENEMY_ANGEL_GREEN:
	case ENEMY_ANGEL_GOLD:
	case ENEMY_ANGEL_BLACK:
		pObj->status = FLYING;

		if (pObj->etc == ANGEL_ATTACK && pObj->motion == PO_C37_ATK0) {
			int count = 0;

			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false && ao[i].type == 0) {
					AddObject(&ao[i], pObj, ADDOBJ_ANGEL_ICE);
					ao[i].dirX = ao[i].dirF = count % 2;

					switch (count) {
					case 0:
					case 1:
						ao[i].motion = PO_C37_ICESHOT_R;
						break;
					case 2:
						ao[i].motion = PO_C37_ICESHOT_D;
						break;
					case 3:
					case 4:
						ao[i].motion = PO_C37_ICESHOT_L;
						break;
					}

					ao[i].dx = (count - 2) * 3 * _2X * 2 * pObj->zoom;
					InitMotion(&ao[i]);

					count++;
					if (count > 4)
						break;
				}
			}
		}
		else if (pObj->motion == PO_C37_ATK0) {
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false && ao[i].type == 0) {
					AddObject(&ao[i], pObj, ADDOBJ_ANGEL);

					break;
				}
			}
		}
		else if (pObj->motion == PO_C37_DASHATK_L0) {
			if (pObj->frame >= 40) {
				pObj->etc = Random(2) == 1 ? ANGEL_DASHUP : ANGEL_DASHDOWN;
				pObj->x = ao[NearPlayer(pObj)].x;
				pObj->y = pObj->etc == ANGEL_DASHUP ? 400 * _2X : 0 * _2X;
				pObj->frame = 0;
			}
			else {
				pObj->frame++;
			}
		}
		else if (pObj->etc >= ANGEL_DASHUP) {
			if (pObj->frame >= 60) {
				pObj->etc = ANGEL_MOVE_READY;
				pObj->frame = 0;
				pObj->x = rw * TSIZE / 2;// (rw - 4) * TSIZE / 2;			//보스맵의 중앙으로(기획시 맵보고 수정바람)
				pObj->y = 0;// (rh - 4) * TSIZE / 2 - 228 * _2X;
			}
			else {
				pObj->frame++;
			}
		}
		else if (pObj->etc == ANGEL_DASHREADY && pObj->frame <= 1) {
			pObj->dirX = pObj->dirF = ao[NearPlayer(pObj)].x > pObj->x ? RIGHT : LEFT;
		}
		break;
	case ENEMY_KIMERA:
	case ENEMY_KIMERA_RED:
	case ENEMY_KIMERA_BLUE:
	case ENEMY_KIMERA_PURPLE:
	case ENEMY_KIMERA_GREEN:
	case ENEMY_KIMERA_GOLD:
	case ENEMY_KIMERA_BLACK:
		if (pObj->motion == PO_C34_FIREATK3) {
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_KIMERA_FIRE);
					//ao[i].y += TSIZE / 2;

					break;
				}
			}
		}
		else if (pObj->motion == PO_C34_ICEATK1) {
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_KIMERA_ICE);
					//ao[i].y += TSIZE / 2;

					break;
				}
			}
		}
		else if (pObj->etc == KIMERA_SPINED && pObj->motion >= PO_C34_SPINATK4) {
			pObj->status = FLYING;
			pObj->moveHandler = BULLETSPINMOVE;
		}
		break;
	case ENEMY_FAIRY:
	case ENEMY_FAIRY_RED:
	case ENEMY_FAIRY_BLUE:
	case ENEMY_FAIRY_PURPLE:
	case ENEMY_FAIRY_GREEN:
	case ENEMY_FAIRY_GOLD:
	case ENEMY_FAIRY_BLACK:
		pObj->status = FLYING;

		if (pObj->etc == FAIRY_ATTACK && pObj->motion == PO_C35_N2) {
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_FAIRY);
					ao[i].etc = 3;

					break;
				}
			}
		}
		break;
	case ENEMY_FROG:
	case ENEMY_FROG_RED:
	case ENEMY_FROG_BLUE:
	case ENEMY_FROG_PURPLE:
	case ENEMY_FROG_GREEN:
	case ENEMY_FROG_GOLD:
	case ENEMY_FROG_BLACK:
		if (pObj->motion == PO_C5_A2) {
			int count = 0;
			int maxcount = 1 + GetDistanceTile(pObj, 6) / 2;

			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false && count <= maxcount && ao[i].type == 0) {
					AddObject(&ao[i], pObj, ADDOBJ_FROG);

					if (count == maxcount)
						ao[i].motion = PO_C5_SHOT0;
					else
						ao[i].motion = PO_C5_SHOT1;

					InitMotion(&ao[i]);

					ao[i].x = pObj->x + (50 * DIR(pObj->dirF) + (32 * count) * DIR(pObj->dirF)) * pObj->zoom * _2X;
					ao[i].y = pObj->y - ((i == 0 ? 19 : 19 + Random(4))) * pObj->zoom * _2X;

					count++;
				}
			}
		}
		break;
	case ENEMY_MAMMOTH:
	case ENEMY_MAMMOTH_RED:
	case ENEMY_MAMMOTH_BLUE:
	case ENEMY_MAMMOTH_PURPLE:
	case ENEMY_MAMMOTH_GREEN:
	case ENEMY_MAMMOTH_GOLD:
	case ENEMY_MAMMOTH_BLACK:
		if (pObj->motion == PO_C21_RETURN9) {
			pObj->hp += (pObj->shieldMax - pObj->shield);
			pObj->shield = pObj->shieldMax;
		}

		if (pObj->motion == PO_C21_A5) {
			int count = 0;

			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false && ao[i].type == 0 && count < 4) {
					AddObject(&ao[i], pObj, ADDOBJ_MAMMOTH0);

					ao[i].dirX = ao[i].dirF = count % 2;
					ao[i].x = pObj->x + 60 * DIR(pObj->dirF) * _2X + (count * 14) * _2X;
					ao[i].y = pObj->y - 10 * _2X - (count * 6) * _2X;
					count++;
				}
			}
		}
		else if (pObj->motion == PO_C21_SHOT3) {
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false && ao[i].type == 0) {
					AddObject(&ao[i], pObj, ADDOBJ_MAMMOTH1);

					ao[i].dx = 5 * _2X + Random(11) * _2X;
					ao[i].etc = 1;
					break;
				}
			}
		}
		break;
	}
}

void EnemyMoveCommon(OBJECT* pObj)
{
	//@@ CMF로 방향 수정할것
	switch (cmfLoaded[pObj->cmf]) {
	case CMF_NPC_DONALD:
		if (pObj->frame % 16 == 0)
			pObj->dirF = 1 - pObj->dirF;
		break;
	}

	if (!pObj->block)
		InitMotion(pObj);

	switch (pObj->type) {
	case ENEMY_LARVA:
	case ENEMY_LARVA_RED:
	case ENEMY_LARVA_BLUE:
	case ENEMY_LARVA_PURPLE:
	case ENEMY_LARVA_GREEN:
	case ENEMY_LARVA_GOLD:
	case ENEMY_LARVA_BLACK:
		pObj->frame++;
		return;
	case ENEMY_ONEEYE:
	case ENEMY_ONEEYE_RED:
	case ENEMY_ONEEYE_BLUE:
	case ENEMY_ONEEYE_PURPLE:
	case ENEMY_ONEEYE_GREEN:
	case ENEMY_ONEEYE_GOLD:
	case ENEMY_ONEEYE_BLACK:
		pObj->x += pObj->dx;
		pObj->y += pObj->dy;
		pObj->frame++;
		return;
	case ENEMY_ANGEL:
	case ENEMY_ANGEL_RED:
	case ENEMY_ANGEL_BLUE:
	case ENEMY_ANGEL_PURPLE:
	case ENEMY_ANGEL_GREEN:
	case ENEMY_ANGEL_GOLD:
	case ENEMY_ANGEL_BLACK:
		pObj->x += pObj->dx;
		pObj->y += pObj->dy;
		pObj->frame++;
		return;
	case ENEMY_THUNDER:
	case ENEMY_THUNDER_RED:
	case ENEMY_THUNDER_BLUE:
	case ENEMY_THUNDER_PURPLE:
	case ENEMY_THUNDER_GREEN:
	case ENEMY_THUNDER_GOLD:
	case ENEMY_THUNDER_BLACK:
		if (pObj->motion == PO_C24_A4 || pObj->motion == PO_C24_A5) {
			pObj->apx = -9 * _2X * pObj->zoom;
			pObj->apy = -16 * _2X * pObj->zoom;
			pObj->ax = 16 * _2X * pObj->zoom;
			pObj->ay = (GetObjHeight(pObj) + 16 * _2X) * pObj->zoom;
		}
		break;
	case ENEMY_SPIDER:
	case ENEMY_SPIDER_RED:
	case ENEMY_SPIDER_BLUE:
	case ENEMY_SPIDER_PURPLE:
	case ENEMY_SPIDER_GREEN:
	case ENEMY_SPIDER_GOLD:
	case ENEMY_SPIDER_BLACK:
		if (pObj->motion == PO_C27_D_LAY2 || pObj->motion == PO_C27_U_LAY2) {
			pObj->apx = pObj->dirX == LEFT ? -pObj->x : 0;
			pObj->ax = pObj->dirX == LEFT ? pObj->x : (rw * TSIZE - pObj->x);
			pObj->apy = pObj->motion == PO_C27_U_LAY2 ? 10 * _2X * pObj->zoom : -24 * _2X * pObj->zoom;
			pObj->ay = 18 * _2X * pObj->zoom;
		}
		else if (pObj->motion == PO_C27_D_LAY3 || pObj->motion == PO_C27_U_LAY3) {
			pObj->apx = pObj->dirX == LEFT ? -pObj->x : 0;
			pObj->ax = pObj->dirX == LEFT ? pObj->x : (rw * TSIZE - pObj->x);
			pObj->apy = pObj->motion == PO_C27_U_LAY3 ? 13 * _2X * pObj->zoom : -20 * _2X * pObj->zoom;
			pObj->ay = 8 * _2X * pObj->zoom;
		}
		break;
	case ENEMY_CASTLE_BOSS3:
	case ENEMY_CASTLE_BOSS3_RED:
	case ENEMY_CASTLE_BOSS3_BLUE:
	case ENEMY_CASTLE_BOSS3_PURPLE:
	case ENEMY_CASTLE_BOSS3_GREEN:
	case ENEMY_CASTLE_BOSS3_GOLD:
	case ENEMY_CASTLE_BOSS3_BLACK:
		if (pObj->motion >= PO_C50_A7 && pObj->motion <= PO_C50_A16)
			pObj->apx -= 48 * _2X * pObj->zoom;
		break;
	case ENEMY_CASTLE_BOSS4:
	case ENEMY_CASTLE_BOSS4_RED:
	case ENEMY_CASTLE_BOSS4_BLUE:
	case ENEMY_CASTLE_BOSS4_PURPLE:
	case ENEMY_CASTLE_BOSS4_GREEN:
	case ENEMY_CASTLE_BOSS4_GOLD:
	case ENEMY_CASTLE_BOSS4_BLACK:

		break;
	case ENEMY_CIRCLE:
	case ENEMY_CIRCLE_RED:
	case ENEMY_CIRCLE_BLUE:
	case ENEMY_CIRCLE_PURPLE:
	case ENEMY_CIRCLE_GREEN:
	case ENEMY_CIRCLE_GOLD:
	case ENEMY_CIRCLE_BLACK:
		pObj->x += pObj->dx;
		pObj->y += pObj->dy;
		break;
	case ENEMY_MACHINE:
	case ENEMY_MACHINE_RED:
	case ENEMY_MACHINE_BLUE:
	case ENEMY_MACHINE_PURPLE:
	case ENEMY_MACHINE_GREEN:
	case ENEMY_MACHINE_GOLD:
	case ENEMY_MACHINE_BLACK:
		//pObj->x += pObj->dx;
		//pObj->y += pObj->dy;
		break;
	case ENEMY_FOGRA:
	case ENEMY_FOGRA_RED:
	case ENEMY_FOGRA_BLUE:
	case ENEMY_FOGRA_PURPLE:
	case ENEMY_FOGRA_GREEN:
	case ENEMY_FOGRA_GOLD:
	case ENEMY_FOGRA_BLACK:
		pObj->x += pObj->dx;
		pObj->y += pObj->dy;
		break;
	case ENEMY_BAHAMUT:
	case ENEMY_BAHAMUT_RED:
	case ENEMY_BAHAMUT_BLUE:
	case ENEMY_BAHAMUT_PURPLE:
	case ENEMY_BAHAMUT_GREEN:
	case ENEMY_BAHAMUT_GOLD:
	case ENEMY_BAHAMUT_BLACK:
		pObj->status = FLYING;

		break;
	default:
		pObj->x += pObj->dx;
		pObj->y += pObj->dy;
		pObj->frame++;
		return;
	}
	/*
	//if (pObj->type != ENEMY_CASTLE_BOSS3 && pObj->type != ENEMY_BAHAMUT && pObj->type != ENEMY_FROG && pObj->type != ENEMY_LARVA && pObj->type != ENEMY_SHIP && pObj->type != ENEMY_FOGRA)
	if ((pObj->type != ENEMY_CIRCLE
		&& pObj->type != ENEMY_CIRCLE_RED
		&& pObj->type != ENEMY_CIRCLE_BLUE
		&& pObj->type != ENEMY_CIRCLE_PURPLE
		&& pObj->type != ENEMY_CIRCLE_GREEN
		&& pObj->type != ENEMY_CIRCLE_GOLD
		&& pObj->type != ENEMY_CIRCLE_BLACK)
		&& (pObj->type != ENEMY_ONEEYE
			&& pObj->type != ENEMY_ONEEYE_RED
			&& pObj->type != ENEMY_ONEEYE_BLUE
			&& pObj->type != ENEMY_ONEEYE_PURPLE
			&& pObj->type != ENEMY_ONEEYE_GREEN
			&& pObj->type != ENEMY_ONEEYE_GOLD
			&& pObj->type != ENEMY_ONEEYE_BLACK)
		//&& (pObj->type != ENEMY_MACHINE
		//	&& pObj->type != ENEMY_MACHINE_RED
		//	&& pObj->type != ENEMY_MACHINE_BLUE
		//	&& pObj->type != ENEMY_MACHINE_PURPLE
		//	&& pObj->type != ENEMY_MACHINE_GREEN
		//	&& pObj->type != ENEMY_MACHINE_GOLD
		//	&& pObj->type != ENEMY_MACHINE_BLACK)
		&& (pObj->type != ENEMY_FOGRA
			&& pObj->type != ENEMY_FOGRA_RED
			&& pObj->type != ENEMY_FOGRA_BLUE
			&& pObj->type != ENEMY_FOGRA_PURPLE
			&& pObj->type != ENEMY_FOGRA_GREEN
			&& pObj->type != ENEMY_FOGRA_GOLD
			&& pObj->type != ENEMY_FOGRA_BLACK)
		)
		TileCheckX2(pObj);

	if (//(pObj->type != ENEMY_SHIP
		//&& pObj->type != ENEMY_SHIP_RED
		//&& pObj->type != ENEMY_SHIP_BLUE
		//&& pObj->type != ENEMY_SHIP_PURPLE
		//&& pObj->type != ENEMY_SHIP_GREEN
		//&& pObj->type != ENEMY_SHIP_GOLD
		//&& pObj->type != ENEMY_SHIP_BLACK)
		//&&
		(pObj->type != ENEMY_CIRCLE
			&& pObj->type != ENEMY_CIRCLE_RED
			&& pObj->type != ENEMY_CIRCLE_BLUE
			&& pObj->type != ENEMY_CIRCLE_PURPLE
			&& pObj->type != ENEMY_CIRCLE_GREEN
			&& pObj->type != ENEMY_CIRCLE_GOLD
			&& pObj->type != ENEMY_CIRCLE_BLACK)
		&& (pObj->type != ENEMY_CASTLE_BOSS3
			&& pObj->type != ENEMY_CASTLE_BOSS3_RED
			&& pObj->type != ENEMY_CASTLE_BOSS3_BLUE
			&& pObj->type != ENEMY_CASTLE_BOSS3_PURPLE
			&& pObj->type != ENEMY_CASTLE_BOSS3_GREEN
			&& pObj->type != ENEMY_CASTLE_BOSS3_GOLD
			&& pObj->type != ENEMY_CASTLE_BOSS3_BLACK)
		&& (pObj->type != ENEMY_CASTLE_BOSS4
			&& pObj->type != ENEMY_CASTLE_BOSS4_RED
			&& pObj->type != ENEMY_CASTLE_BOSS4_BLUE
			&& pObj->type != ENEMY_CASTLE_BOSS4_PURPLE
			&& pObj->type != ENEMY_CASTLE_BOSS4_GREEN
			&& pObj->type != ENEMY_CASTLE_BOSS4_GOLD
			&& pObj->type != ENEMY_CASTLE_BOSS4_BLACK)
		&& (pObj->type != ENEMY_FOGRA
			&& pObj->type != ENEMY_FOGRA_RED
			&& pObj->type != ENEMY_FOGRA_BLUE
			&& pObj->type != ENEMY_FOGRA_PURPLE
			&& pObj->type != ENEMY_FOGRA_GREEN
			&& pObj->type != ENEMY_FOGRA_GOLD
			&& pObj->type != ENEMY_FOGRA_BLACK)
		&& (pObj->type != ENEMY_ONEEYE
			&& pObj->type != ENEMY_ONEEYE_RED
			&& pObj->type != ENEMY_ONEEYE_BLUE
			&& pObj->type != ENEMY_ONEEYE_PURPLE
			&& pObj->type != ENEMY_ONEEYE_GREEN
			&& pObj->type != ENEMY_ONEEYE_GOLD
			&& pObj->type != ENEMY_ONEEYE_BLACK)
		//&& (pObj->type != ENEMY_MACHINE
		//	&& pObj->type != ENEMY_MACHINE_RED
		//	&& pObj->type != ENEMY_MACHINE_BLUE
		//	&& pObj->type != ENEMY_MACHINE_PURPLE
		//	&& pObj->type != ENEMY_MACHINE_GREEN
		//	&& pObj->type != ENEMY_MACHINE_GOLD
		//	&& pObj->type != ENEMY_MACHINE_BLACK)
		//&& (pObj->type != ENEMY_CASTLE_BOSS1
		//	&& pObj->type != ENEMY_CASTLE_BOSS1_RED
		//	&& pObj->type != ENEMY_CASTLE_BOSS1_BLUE
		//	&& pObj->type != ENEMY_CASTLE_BOSS1_PURPLE
		//	&& pObj->type != ENEMY_CASTLE_BOSS1_GREEN
		//	&& pObj->type != ENEMY_CASTLE_BOSS1_GOLD
		//	&& pObj->type != ENEMY_CASTLE_BOSS1_BLACK)
		//&& pObj->type != NPC_SOUL
		//&& pObj->type != NPC_MERCHANT && pObj->type != NPC_INN
		)
		TileCheckY2(pObj);
	*/
	//if (pObj->x < ao[PLAYER].x + TSIZE)
	//	pObj->x = ao[PLAYER].x + TSIZE;
	//if (robin.playtime % MOTIONDIV == 0 && drawHandle != MD_RAID)
	pObj->frame++;
}

void EnemyMoveTurn(OBJECT* pObj)
{
	const signed short* tPtr;
	int ret;
	int i;
	int distance;
	int obj = GetObjFromPtr(pObj);
	int speed = 4 * _2X;//미사일 스피드

	tPtr = cmf_status_data[pObj->cmf][pObj->etc];

	if (tPtr == 0 || *tPtr == 0)
		goto END;

	ret = *tPtr;
	if (!pObj->target) {
		//진짜 적이면 아군을 공격한다.
		distance = DX;

		for (i = PLAYER; i < TOTALCHAR; i++) {
			if (Abs(ao[i].x - pObj->x) < distance && ao[i].active == true && ao[i].dead == false) {
				distance = Abs(ao[i].x - pObj->x);
				pObj->target = i;
			}
		}
	}
	//pObj->target = PLAYER;

	//Motion
	//예전에는 frame / 2 로 두 프레임에 한 번씩 모션을 넘겼는데,
	//이 핸들러는 frame % ret == 0 에서 frame을 0으로 되돌리므로 frame이 ret을 넘지 못한다.
	//그래서 모션표의 앞쪽 절반만 재생되고 뒤쪽 절반은 한 번도 나오지 않았다.
	//mv 데이터를 쓰는 다른 핸들러들과 똑같이 매 프레임 넘긴다.
	tPtr += (2 + (pObj->frame % ret));
	pObj->motion = *tPtr;

	//DX
	tPtr += ret;

	if (turn == obj) {
		switch (pObj->turnPosition) {
		case HERE://출발전
			pObj->dirF = pObj->dirX = LEFT;

			//해파리일경우 점프중에만 움직인다.
			if (pObj->type == ENEMY_JELLYFISH
				|| pObj->type == ENEMY_JELLYFISH_RED
				|| pObj->type == ENEMY_JELLYFISH_BLUE
				|| pObj->type == ENEMY_JELLYFISH_PURPLE
				|| pObj->type == ENEMY_JELLYFISH_GREEN
				|| pObj->type == ENEMY_JELLYFISH_GOLD
				|| pObj->type == ENEMY_JELLYFISH_BLACK) {
				if (pObj->dirY == UP)
					pObj->dx = *tPtr * DIR(pObj->dirX);
			}
			else {
				pObj->dx = *tPtr * DIR(pObj->dirX);
			}

			//DY
			tPtr += ret;

			if (*tPtr >= 100) {
				//해파리일경우 플레이어가 자기보다 20px 이상 위에있을때만 점프를 뛴다
				if ((pObj->type == ENEMY_JELLYFISH
					|| pObj->type == ENEMY_JELLYFISH_RED
					|| pObj->type == ENEMY_JELLYFISH_BLUE
					|| pObj->type == ENEMY_JELLYFISH_PURPLE
					|| pObj->type == ENEMY_JELLYFISH_GREEN
					|| pObj->type == ENEMY_JELLYFISH_GOLD
					|| pObj->type == ENEMY_JELLYFISH_BLACK)
					&& ao[pObj->target].y - pObj->y - 20 * _2X > 0)
					pObj->dy = 0;
				else {
					pObj->dirY = UP;
					pObj->my = true;
					pObj->status = JUMP;
					pObj->jumpFrame = *tPtr - 100;
				}
			}
			else
				pObj->dy = *tPtr;

			switch (pObj->type) {
			case ENEMY_SHIP:
			case ENEMY_SHIP_RED:
			case ENEMY_SHIP_BLUE:
			case ENEMY_SHIP_PURPLE:
			case ENEMY_SHIP_GREEN:
			case ENEMY_SHIP_GOLD:
			case ENEMY_SHIP_BLACK:
				//ShipMainMove(pObj);
				//pObj->moveHandler = ENEMYMOVETURN;
				break;
			}

			//한번 루프가 돌았으면 다음 턴으로 넘겨준다.
			if (pObj->frame % ret == 0) {
				pObj->currentSkill = 0;
				pObj->etc = enemyAttackPattern[pObj->type * ATTACKPATTERNTOTALDATASIZE + 2 + pObj->currentSkill * ATTACKPATTERNDATASIZE + pObj->turnPosition];
				pObj->frame = 0;
				pObj->mainFrame = 0;
				pObj->turnPosition = GOING;
			}
			break;
		case GOING://가는중
			pObj->dirF = pObj->dirX = LEFT;

			if (*tPtr >= 120) {
				ao[pObj->target].y -= 50 * _2X;
				GotoObj(&ao[pObj->target], pObj, (*tPtr - 120) * _2X);
				ao[pObj->target].y += 50 * _2X;
			}
			else if (*tPtr >= 100) {
				GotoObj(&ao[pObj->target], pObj, (*tPtr - 100) * _2X);
			}
			else {
				//해파리일경우 점프중에만 움직인다.
				if (pObj->type == ENEMY_JELLYFISH
					|| pObj->type == ENEMY_JELLYFISH_RED
					|| pObj->type == ENEMY_JELLYFISH_BLUE
					|| pObj->type == ENEMY_JELLYFISH_PURPLE
					|| pObj->type == ENEMY_JELLYFISH_GREEN
					|| pObj->type == ENEMY_JELLYFISH_GOLD
					|| pObj->type == ENEMY_JELLYFISH_BLACK) {
					//if (pObj->dirY == UP)
					pObj->dx = *tPtr * DIR(pObj->dirX);
				}
				//else if (pObj->type == ENEMY_DARKDRAGON
				//	|| pObj->type == ENEMY_DARKDRAGON_RED
				//	|| pObj->type == ENEMY_DARKDRAGON_BLUE
				//	|| pObj->type == ENEMY_DARKDRAGON_PURPLE
				//	|| pObj->type == ENEMY_DARKDRAGON_GREEN
				//	|| pObj->type == ENEMY_DARKDRAGON_GOLD
				//	|| pObj->type == ENEMY_DARKDRAGON_BLACK) {
				//	//if (pObj->dirY == UP)
				//	MobiusMove(pObj);
				//}
				else {
					//pObj->dx = *tPtr * DIR(pObj->dirX);
					GotoObjXY(pObj, ao[pObj->target].nx, ao[pObj->target].ny, *tPtr);
					//GotoObj(&ao[pObj->target], pObj, *tPtr * _2X);
				}

				//DY
				tPtr += ret;

				if (*tPtr >= 100) {
					//해파리일경우 플레이어가 자기보다 20px 이상 위에있을때만 점프를 뛴다
					if ((pObj->type == ENEMY_JELLYFISH
						|| pObj->type == ENEMY_JELLYFISH_RED
						|| pObj->type == ENEMY_JELLYFISH_BLUE
						|| pObj->type == ENEMY_JELLYFISH_PURPLE
						|| pObj->type == ENEMY_JELLYFISH_GREEN
						|| pObj->type == ENEMY_JELLYFISH_GOLD
						|| pObj->type == ENEMY_JELLYFISH_BLACK)
						&& ao[pObj->target].y - pObj->y - 20 * _2X > 0)
						pObj->dy = 0;
					else {
						pObj->dirY = UP;
						pObj->my = true;
						pObj->status = JUMP;
						pObj->jumpFrame = *tPtr - 100;
					}
				}
				else {
					GotoObjXY(pObj, ao[pObj->target].nx, ao[pObj->target].ny, Max(SPEED_MIN, *tPtr));
					//GotoObj(&ao[pObj->target], pObj, Max(SPEED_MIN, *tPtr));

					//pObj->dy = *tPtr;
				}

			}

			if (pObj->x + pObj->dx < ao[pObj->target].x)
				pObj->dx = ao[pObj->target].x + 8 * _2X - pObj->x;
			//공격거리까지 이동했으면 다음 턴으로 넘겨준다.
			if (Abs(pObj->x - ao[pObj->target].x) <= enemyAttackPattern[pObj->type * ATTACKPATTERNTOTALDATASIZE + 2 + pObj->currentSkill * ATTACKPATTERNDATASIZE + 5] * pObj->zoom) {
				if (pObj->x < ao[pObj->target].x)
					pObj->x = ao[pObj->target].x + 16 * _2X;
				pObj->etc = enemyAttackPattern[pObj->type * ATTACKPATTERNTOTALDATASIZE + 2 + pObj->currentSkill * ATTACKPATTERNDATASIZE + pObj->turnPosition];
				pObj->frame = 0;
				pObj->mainFrame = 0;
				pObj->dx = 0;
				pObj->turnPosition = THERE;
			}
			else if (pObj->dx == 0 && pObj->frame > 0 && pObj->frame % ret == 0) {
				pObj->etc = enemyAttackPattern[pObj->type * ATTACKPATTERNTOTALDATASIZE + 2 + pObj->currentSkill * ATTACKPATTERNDATASIZE + pObj->turnPosition];
				pObj->frame = 0;
				pObj->mainFrame = 0;
				pObj->dx = 0;
				pObj->turnPosition = THERE;
			}
			break;
		case THERE://도착
			pObj->dirF = pObj->dirX = LEFT;

			if (*tPtr >= 120) {
				ao[pObj->target].y -= 50 * _2X;
				GotoObj(&ao[pObj->target], pObj, (*tPtr - 120) * _2X);
				ao[pObj->target].y += 50 * _2X;
			}
			else if (*tPtr >= 100) {
				GotoObj(&ao[pObj->target], pObj, (*tPtr - 100) * _2X);
			}
			else {
				//해파리일경우 점프중에만 움직인다.
				if (pObj->type == ENEMY_JELLYFISH
					|| pObj->type == ENEMY_JELLYFISH_RED
					|| pObj->type == ENEMY_JELLYFISH_BLUE
					|| pObj->type == ENEMY_JELLYFISH_PURPLE
					|| pObj->type == ENEMY_JELLYFISH_GREEN
					|| pObj->type == ENEMY_JELLYFISH_GOLD
					|| pObj->type == ENEMY_JELLYFISH_BLACK) {
					if (pObj->dirY == UP)
						pObj->dx = *tPtr * DIR(pObj->dirX);
				}
				else {
					pObj->dx = *tPtr * DIR(pObj->dirX);
				}

				//DY
				tPtr += ret;

				if (*tPtr >= 100) {
					//해파리일경우 플레이어가 자기보다 20px 이상 위에있을때만 점프를 뛴다
					if ((pObj->type == ENEMY_JELLYFISH
						|| pObj->type == ENEMY_JELLYFISH_RED
						|| pObj->type == ENEMY_JELLYFISH_BLUE
						|| pObj->type == ENEMY_JELLYFISH_PURPLE
						|| pObj->type == ENEMY_JELLYFISH_GREEN
						|| pObj->type == ENEMY_JELLYFISH_GOLD
						|| pObj->type == ENEMY_JELLYFISH_BLACK)
						&& ao[pObj->target].y - pObj->y - 20 * _2X > 0)
						pObj->dy = 0;
					else {
						pObj->dirY = UP;
						pObj->my = true;
						pObj->status = JUMP;
						pObj->jumpFrame = *tPtr - 100;
					}
				}
				else
					pObj->dy = *tPtr;
			}

			if (pObj->x + pObj->dx < ao[PLAYER].x + 16 * _2X)
				pObj->dx = ao[PLAYER].x + 16 * _2X - pObj->x;

			switch (pObj->type) {
			case ENEMY_CASTLE1:
			case ENEMY_CASTLE1_RED:
			case ENEMY_CASTLE1_BLUE:
			case ENEMY_CASTLE1_PURPLE:
			case ENEMY_CASTLE1_GREEN:
			case ENEMY_CASTLE1_GOLD:
			case ENEMY_CASTLE1_BLACK:
				if (pObj->motion == PO_C44_A2) {
					int i;

					for (i = ENEMY; i < NEUTRAL; i++) {
						if (ao[i].active == false) {
							AddObject(&ao[i], pObj, ADDOBJ_CASTLE1BULLET);
							break;
						}
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
				//if (GetObjFromPtr(pObj) == ENEMY) {
				//	pObj->moveHandler = BAHAMUTBODYMOVE;
				//	MoveObj(pObj);
				//	pObj->moveHandler = ENEMYMOVETURN;
				//}
				break;
			}

			//사정거리에 도착했으면 공격을 하고. 공격이 끝나면 복귀?
			if (pObj->frame % ret == 0) {
				switch (pObj->type) {
				case ENEMY_CRYSTAL:
				case ENEMY_CRYSTAL_RED:
				case ENEMY_CRYSTAL_BLUE:
				case ENEMY_CRYSTAL_PURPLE:
				case ENEMY_CRYSTAL_GREEN:
				case ENEMY_CRYSTAL_GOLD:
				case ENEMY_CRYSTAL_BLACK:
					break;
				default:
					pObj->etc = enemyAttackPattern[pObj->type * ATTACKPATTERNTOTALDATASIZE + 2 + pObj->currentSkill * ATTACKPATTERNDATASIZE + pObj->turnPosition];
					pObj->frame = 0;
					pObj->mainFrame = 0;
					pObj->turnPosition = COMING;
					//attackSequence = ATTACKSEQUENCE_ROULETTE;
					//attackDelay = ENEMYDELAY_COIN_START;
					sequenceFrame = 0;
					//#ifdef SPEEDTURN
					//					if (GetObjFromPtr(pObj) == turn)
					//						WhoIsNextTurn();
					//#endif
					break;
				}


				/*
				if (pObj->x < ao[PLAYER].x + 16 * _2X)
					pObj->x = ao[PLAYER].x + 16 * _2X;
				//pObj->etc = enemyAttackPattern[pObj->type * ATTACKPATTERNTOTALDATASIZE + 2 + (pObj->turn % enemyAttackPattern[pObj->type * ATTACKPATTERNTOTALDATASIZE]) * ATTACKPATTERNDATASIZE + pObj->turnPosition];
				pObj->etc = enemyAttackPattern[pObj->type * ATTACKPATTERNTOTALDATASIZE + 2 + (pObj->turn % enemyAttackPattern[pObj->type * ATTACKPATTERNTOTALDATASIZE]) * ATTACKPATTERNDATASIZE + 1];
				pObj->frame = 0;
				pObj->mainFrame = 0;
				attackSequence = ATTACKSEQUENCE_ACTION;
				sequenceFrame = 0;
				switch (pObj->type) {
				case ENEMY_BAHAMUT:
				case ENEMY_BAHAMUT_RED:
				case ENEMY_BAHAMUT_BLUE:
				case ENEMY_BAHAMUT_PURPLE:
				case ENEMY_BAHAMUT_GREEN:
				case ENEMY_BAHAMUT_GOLD:
				case ENEMY_BAHAMUT_BLACK:
					switch (pObj->etc) {
					case BAHAMUT_FIRE:
					case BAHAMUT_BULLET:
					case BAHAMUT_ATTACK:
						ao[pObj->mom].etc = BAHAMUT_HEAD_FIRE + (pObj->etc - BAHAMUT_FIRE);
						ao[pObj->mom].y = TSIZE * 3 * pObj->zoom;
						ao[pObj->mom].dx = 0;
						ao[pObj->mom].dy = 0;
						ao[pObj->mom].frame = 0;
						break;
					case BAHAMUT_NEUTRAL:
						ao[pObj->mom].etc = BAHAMUT_HEAD_NEUTRAL;
						ao[pObj->mom].y = TSIZE * 3 * pObj->zoom;
						ao[pObj->mom].dx = 0;
						ao[pObj->mom].dy = 0;
						ao[pObj->mom].frame = 0;
						break;
					}
					break;
				}

				//pObj->turnPosition = COMING;
				//attackSequence = ATTACKSEQUENCE_ATTACKRESULT;
				//attackDelay = ENEMYDELAY_COIN_START;// attackDelayPerType[attackType];

				//여기서 빼주지 않는다.
				//AddBar(&bar[BAR_COIN], -dmgInfo[dmgIndex].dmg, BARFRAME);

				//tPtr = cmf_status_data[pObj->cmf][pObj->etc];
				//attackDelay = *tPtr;
				*/
			}
			break;
		case COMING://복귀
			pObj->dirF = pObj->dirX = RIGHT;

			if (*tPtr >= 120) {
				ao[pObj->target].y -= 50 * _2X;
				GotoObjXY(pObj, pObj->nx, pObj->ny, (*tPtr - 120) * _2X);
				ao[pObj->target].y += 50 * _2X;
			}
			else if (*tPtr >= 100) {
				//GotoObj(&ao[pObj->target], pObj, (*tPtr - 100) * _2X);
				GotoObjXY(pObj, pObj->nx, pObj->ny, (*tPtr - 100) * _2X);
			}
			else {
				//해파리일경우 점프중에만 움직인다.
				if (pObj->type == ENEMY_JELLYFISH
					|| pObj->type == ENEMY_JELLYFISH_RED
					|| pObj->type == ENEMY_JELLYFISH_BLUE
					|| pObj->type == ENEMY_JELLYFISH_PURPLE
					|| pObj->type == ENEMY_JELLYFISH_GREEN
					|| pObj->type == ENEMY_JELLYFISH_GOLD
					|| pObj->type == ENEMY_JELLYFISH_BLACK) {
					if (pObj->dirY == UP)
						pObj->dx = *tPtr * DIR(pObj->dirX);
				}
				else {
					pObj->dx = *tPtr * DIR(pObj->dirX);
				}

				//DY
				tPtr += ret;

				if (*tPtr >= 100) {
					//해파리일경우 플레이어가 자기보다 20px 이상 위에있을때만 점프를 뛴다
					if (pObj->type == ENEMY_JELLYFISH && ao[pObj->target].y - pObj->y - 20 * _2X > 0)
						pObj->dy = 0;
					else {
						pObj->dirY = UP;
						pObj->my = true;
						pObj->status = JUMP;
						pObj->jumpFrame = *tPtr - 100;
					}
				}
				else
					GotoObjXY(pObj, pObj->nx, pObj->ny, Max(5, *tPtr));

				//pObj->dy = *tPtr;
			}

			//시작포인트에 도착했으면 다시 뉴트럴로 온다.
			if (pObj->x >= pObj->nx) {
				pObj->x = pObj->nx;
				pObj->y = pObj->ny;
				pObj->dx = 0;
				pObj->dy = 0;
				pObj->dirX = pObj->dirF = LEFT;
				if (GetObjFromPtr(pObj) == turn && GetSonObjCnt(GetObjFromPtr(pObj)) == 0) {
					onceDmgUpdateFrame = 2 * FPS;
					pObj->turnPosition = DMGUPDATE;
				}

			}
			break;
		case DMGUPDATE:
			//#ifndef SPEEDTURN
			if (onceDmgUpdateFrame == 1) {
				WhoIsNextTurn();
				pObj->coolTime = MC_knlCurrentTimeStamp();
				//#endif
				turnFrame = 0;
				pObj->turnPosition = HERE;
				pObj->turn++;
				pObj->frame = 0;
				pObj->mainFrame = 0;
				pObj->etc = 0;

				option.gameControl = CONTROL_MANUAL;

				if (autoPlay == true && curtainFrame == 0 && areaFrame == 0) {
					switch (keyHandle) {
					case MK_BATTLE:
						BoxOpen();
						break;
						//case MK_RAID:
						//	JoyStickPressRaid();
						//	break;
					}
				}
				else
					SaveGame();
			}
			break;
		}
	}
	else {
		pObj->dirF = pObj->dirX = LEFT;
		pObj->dx = 0;

		//DY
		tPtr += ret;

		if (*tPtr >= 100) {
			//해파리일경우 플레이어가 자기보다 20px 이상 위에있을때만 점프를 뛴다
			if ((pObj->type == ENEMY_JELLYFISH
				|| pObj->type == ENEMY_JELLYFISH_RED
				|| pObj->type == ENEMY_JELLYFISH_BLUE
				|| pObj->type == ENEMY_JELLYFISH_PURPLE
				|| pObj->type == ENEMY_JELLYFISH_GREEN
				|| pObj->type == ENEMY_JELLYFISH_GOLD
				|| pObj->type == ENEMY_JELLYFISH_BLACK)
				&& ao[pObj->target].y - pObj->y - 8 * _2X > 0)
				pObj->dy = 0;
			else {
				pObj->dirY = UP;
				pObj->my = true;
				pObj->status = JUMP;
				pObj->jumpFrame = *tPtr - 100;
			}
		}
		else
			pObj->dy = *tPtr;

		switch (pObj->type) {
		case ENEMY_DARKDRAGON:
		case ENEMY_DARKDRAGON_RED:
		case ENEMY_DARKDRAGON_BLUE:
		case ENEMY_DARKDRAGON_PURPLE:
		case ENEMY_DARKDRAGON_GREEN:
		case ENEMY_DARKDRAGON_GOLD:
		case ENEMY_DARKDRAGON_BLACK:
			InitMotion(pObj);
			break;
		case ENEMY_CASTLE1:
		case ENEMY_CASTLE1_RED:
		case ENEMY_CASTLE1_BLUE:
		case ENEMY_CASTLE1_PURPLE:
		case ENEMY_CASTLE1_GREEN:
		case ENEMY_CASTLE1_GOLD:
		case ENEMY_CASTLE1_BLACK:
			if (pObj->motion == PO_C44_A2) {
				int i;

				for (i = ENEMY; i < NEUTRAL; i++) {
					if (ao[i].active == false) {
						AddObject(&ao[i], pObj, ADDOBJ_CASTLE1BULLET);
						break;
					}
				}
			}
			break;
		case ENEMY_FOGRA:
		case ENEMY_FOGRA_RED:
		case ENEMY_FOGRA_BLUE:
		case ENEMY_FOGRA_PURPLE:
		case ENEMY_FOGRA_GREEN:
		case ENEMY_FOGRA_GOLD:
		case ENEMY_FOGRA_BLACK:
			switch (pObj->etc) {
			case FOGRA_BULLET:

				break;
			}
			break;
		}

		if (pObj->frame % ret == 0) {
			switch (pObj->deadCount) {
			case 4:
			case 10:
				pObj->deadCount += 3;
				break;
			default:
				pObj->deadCount++;
				break;
			case 16:
				pObj->deadCount = 0;
				break;
			}

			pObj->etc = enemyAttackPattern[pObj->type * ATTACKPATTERNTOTALDATASIZE + 0];
			pObj->frame = 0;
			pObj->mainFrame = 0;
			tPtr = cmf_status_data[pObj->cmf][pObj->etc];

			if (tPtr == 0 || *tPtr == 0)
				goto END;

			ret = *tPtr;

			//Motion
			tPtr += (2 + (pObj->frame % ret));
			pObj->motion = *tPtr;


		}

	}
	/*
	switch (pObj->type) {
	case ENEMY_BAHAMUT:
	case ENEMY_BAHAMUT_RED:
	case ENEMY_BAHAMUT_BLUE:
	case ENEMY_BAHAMUT_PURPLE:
	case ENEMY_BAHAMUT_GREEN:
	case ENEMY_BAHAMUT_GOLD:
	case ENEMY_BAHAMUT_BLACK:

	case ENEMY_CASTLE_BOSS1:
	case ENEMY_CASTLE_BOSS1_RED:
	case ENEMY_CASTLE_BOSS1_BLUE:
	case ENEMY_CASTLE_BOSS1_PURPLE:
	case ENEMY_CASTLE_BOSS1_GREEN:
	case ENEMY_CASTLE_BOSS1_GOLD:
	case ENEMY_CASTLE_BOSS1_BLACK:

		goto END;
	}
	*/
	EnemyMove_AddObj2(pObj);
	EnemyMove_AddObj(pObj);

END:
	EnemyMoveCommon(pObj);

}

void SummonMove(OBJECT* pObj)
{
	const signed short* tPtr;
	int ret;
	int i;
	int distance;
	int obj = GetObjFromPtr(pObj);
	int speed = 4 * _2X;//미사일 스피드

	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	int collectionIdx = GetCollectionIdx(it->type, it->detail, it->grade);

	tPtr = cmf_status_data[pObj->cmf][pObj->etc];

	if (tPtr == 0 || *tPtr == 0)
		goto END;

	ret = *tPtr;

	if (!pObj->target) {
		//진짜 적이면 아군을 공격한다.
		//distance = DX;

		//for (i = ENEMY; i < NEUTRAL; i++) {
		//	if (Abs(ao[i].x - pObj->x) < distance && ao[i].active == true && ao[i].dead == false) {
		//		distance = Abs(ao[i].x - pObj->x);
		//		pObj->target = i;
		//	}
		//}
		pObj->target = ao[PLAYER].target;
	}

	//Motion
	tPtr += (2 + (pObj->frame % ret));
	pObj->motion = *tPtr;

	//DX
	tPtr += ret;

	switch (pObj->turnPosition) {
	case HERE://출발전
		pObj->dirF = pObj->dirX = RIGHT;

		//해파리일경우 점프중에만 움직인다.
		if (pObj->type == ENEMY_JELLYFISH
			|| pObj->type == ENEMY_JELLYFISH_RED
			|| pObj->type == ENEMY_JELLYFISH_BLUE
			|| pObj->type == ENEMY_JELLYFISH_PURPLE
			|| pObj->type == ENEMY_JELLYFISH_GREEN
			|| pObj->type == ENEMY_JELLYFISH_GOLD
			|| pObj->type == ENEMY_JELLYFISH_BLACK) {
			if (pObj->dirY == UP)
				pObj->dx = *tPtr * DIR(pObj->dirX);
		}
		else {
			pObj->dx = *tPtr * DIR(pObj->dirX);
		}

		//DY
		tPtr += ret;

		if (*tPtr >= 100) {
			//해파리일경우 플레이어가 자기보다 20px 이상 위에있을때만 점프를 뛴다
			if ((pObj->type == ENEMY_JELLYFISH
				|| pObj->type == ENEMY_JELLYFISH_RED
				|| pObj->type == ENEMY_JELLYFISH_BLUE
				|| pObj->type == ENEMY_JELLYFISH_PURPLE
				|| pObj->type == ENEMY_JELLYFISH_GREEN
				|| pObj->type == ENEMY_JELLYFISH_GOLD
				|| pObj->type == ENEMY_JELLYFISH_BLACK) && ao[pObj->target].y - pObj->y - 20 * _2X > 0)
				pObj->dy = 0;
			else {
				pObj->dirY = UP;
				pObj->my = true;
				pObj->status = JUMP;
				pObj->jumpFrame = *tPtr - 100;
			}
		}
		else
			pObj->dy = *tPtr;

		//switch (pObj->type) {
		//	case ENEMY_SHIP:
		//		ShipMainMove(pObj);
		//		break;
		//}

		//한번 루프가 돌았으면 다음 턴으로 넘겨준다.
		if (pObj->frame % ret == 0) {
			pObj->etc = enemyAttackPattern[pObj->type * ATTACKPATTERNTOTALDATASIZE + 2 + pObj->currentSkill * ATTACKPATTERNDATASIZE + pObj->turnPosition];
			pObj->frame = 0;
			pObj->mainFrame = 0;
			pObj->turnPosition = GOING;
		}
		break;
	case GOING://가는중
		pObj->dirF = pObj->dirX = RIGHT;

		if (*tPtr >= 120) {
			ao[pObj->target].y -= 50 * _2X;
			GotoObj(&ao[pObj->target], pObj, (*tPtr - 120) * _2X);
			ao[pObj->target].y += 50 * _2X;
		}
		else if (*tPtr >= 100) {
			GotoObj(&ao[pObj->target], pObj, (*tPtr - 100) * _2X);
		}
		else {
			//해파리일경우 점프중에만 움직인다.
			if (pObj->type == ENEMY_JELLYFISH
				|| pObj->type == ENEMY_JELLYFISH_RED
				|| pObj->type == ENEMY_JELLYFISH_BLUE
				|| pObj->type == ENEMY_JELLYFISH_PURPLE
				|| pObj->type == ENEMY_JELLYFISH_GREEN
				|| pObj->type == ENEMY_JELLYFISH_GOLD
				|| pObj->type == ENEMY_JELLYFISH_BLACK) {
				//if (pObj->dirY == UP)
				pObj->dx = *tPtr * DIR(pObj->dirX);
			}
			else {
				pObj->dx = *tPtr * DIR(pObj->dirX);
			}

			//DY
			tPtr += ret;

			if (*tPtr >= 100) {
				//해파리일경우 플레이어가 자기보다 20px 이상 위에있을때만 점프를 뛴다
				if ((pObj->type == ENEMY_JELLYFISH
					|| pObj->type == ENEMY_JELLYFISH_RED
					|| pObj->type == ENEMY_JELLYFISH_BLUE
					|| pObj->type == ENEMY_JELLYFISH_PURPLE
					|| pObj->type == ENEMY_JELLYFISH_GREEN
					|| pObj->type == ENEMY_JELLYFISH_GOLD
					|| pObj->type == ENEMY_JELLYFISH_BLACK)
					&& ao[pObj->target].y - pObj->y - 20 * _2X > 0)
					pObj->dy = 0;
				else {
					pObj->dirY = UP;
					pObj->my = true;
					pObj->status = JUMP;
					pObj->jumpFrame = *tPtr - 100;
				}
			}
			else
				pObj->dy = *tPtr;
		}

		if (pObj->x + pObj->dx > ao[pObj->target].x)
			pObj->dx = ao[pObj->target].x + 8 * _2X - pObj->x;
		//공격거리까지 이동했으면 다음 턴으로 넘겨준다.
		if (Abs(pObj->x - ao[pObj->target].x) <= enemyAttackPattern[pObj->type * ATTACKPATTERNTOTALDATASIZE + 2 + pObj->currentSkill * ATTACKPATTERNDATASIZE + 5] * pObj->zoom) {
			if (pObj->x > ao[pObj->target].x)
				pObj->x = ao[pObj->target].x - 16 * _2X;
			pObj->etc = enemyAttackPattern[pObj->type * ATTACKPATTERNTOTALDATASIZE + 2 + pObj->currentSkill * ATTACKPATTERNDATASIZE + pObj->turnPosition];
			pObj->frame = 1;
			pObj->mainFrame = 0;
			pObj->dx = 0;
			pObj->turnPosition = THERE;
		}
		//else if (pObj->dx == 0 && pObj->frame > 0 && pObj->frame % ret == 0) {
		//	pObj->etc = enemyAttackPattern[pObj->type * ATTACKPATTERNTOTALDATASIZE + 2 + (pObj->turn % enemyAttackPattern[pObj->type * ATTACKPATTERNTOTALDATASIZE]) * ATTACKPATTERNDATASIZE + pObj->turnPosition];
		//	pObj->frame = 1;
		//	pObj->mainFrame = 0;
		//	pObj->dx = 0;
		//	pObj->turnPosition = THERE;
		//}
		break;
	case THERE://도착
		pObj->dirF = pObj->dirX = RIGHT;

		if (*tPtr >= 120) {
			ao[pObj->target].y -= 50 * _2X;
			GotoObj(&ao[pObj->target], pObj, (*tPtr - 120) * _2X);
			ao[pObj->target].y += 50 * _2X;
		}
		else if (*tPtr >= 100) {
			GotoObj(&ao[pObj->target], pObj, (*tPtr - 100) * _2X);
		}
		else {
			//해파리일경우 점프중에만 움직인다.
			if (pObj->type == ENEMY_JELLYFISH
				|| pObj->type == ENEMY_JELLYFISH_RED
				|| pObj->type == ENEMY_JELLYFISH_BLUE
				|| pObj->type == ENEMY_JELLYFISH_PURPLE
				|| pObj->type == ENEMY_JELLYFISH_GREEN
				|| pObj->type == ENEMY_JELLYFISH_GOLD
				|| pObj->type == ENEMY_JELLYFISH_BLACK) {
				if (pObj->dirY == UP)
					pObj->dx = *tPtr * DIR(pObj->dirX);
			}
			else {
				pObj->dx = *tPtr * DIR(pObj->dirX);
			}

			//DY
			tPtr += ret;

			if (*tPtr >= 100) {
				//해파리일경우 플레이어가 자기보다 20px 이상 위에있을때만 점프를 뛴다
				if ((pObj->type == ENEMY_JELLYFISH
					|| pObj->type == ENEMY_JELLYFISH_RED
					|| pObj->type == ENEMY_JELLYFISH_BLUE
					|| pObj->type == ENEMY_JELLYFISH_PURPLE
					|| pObj->type == ENEMY_JELLYFISH_GREEN
					|| pObj->type == ENEMY_JELLYFISH_GOLD
					|| pObj->type == ENEMY_JELLYFISH_BLACK)
					&& ao[pObj->target].y - pObj->y - 20 * _2X > 0)
					pObj->dy = 0;
				else {
					pObj->dirY = UP;
					pObj->my = true;
					pObj->status = JUMP;
					pObj->jumpFrame = *tPtr - 100;
				}
			}
			else
				pObj->dy = *tPtr;
		}

		if (pObj->x + pObj->dx > ao[pObj->target].x - 16 * _2X)
			pObj->dx = ao[pObj->target].x - 16 * _2X - pObj->x;

		switch (pObj->type) {
		case ENEMY_CASTLE1:
		case ENEMY_CASTLE1_RED:
		case ENEMY_CASTLE1_BLUE:
		case ENEMY_CASTLE1_PURPLE:
		case ENEMY_CASTLE1_GREEN:
		case ENEMY_CASTLE1_GOLD:
		case ENEMY_CASTLE1_BLACK:
			if (pObj->motion == PO_C44_A2) {
				int i;

				for (i = SOLDIER; i < PLAYERALL; i++) {
					if (ao[i].active == false) {
						AddObject(&ao[i], pObj, ADDOBJ_CASTLE1BULLET);
						break;
					}
				}
			}
			break;
		}
		//사정거리에 도착했으면 공격을 하고.
		if (pObj->frame % ret == 0) {

			//if (ao[pObj->target].active == true && ao[pObj->target].dead == false) {
			//	pObj->frame = 0;
			//	pObj->mainFrame = 0;
			//}
			//else {
			//	if (pObj->x > ao[pObj->target].x)
			//		pObj->x = ao[pObj->target].x - 16 * _2X;
			//	pObj->etc = enemyAttackPattern[pObj->type * ATTACKPATTERNTOTALDATASIZE + 2 + pObj->turnPosition];
			pObj->frame = 0;
			pObj->mainFrame = 0;
			pObj->etc = enemyAttackPattern[pObj->type * ATTACKPATTERNTOTALDATASIZE + 2 + pObj->currentSkill * ATTACKPATTERNDATASIZE + pObj->turnPosition];
			pObj->turnPosition = COMING;

#ifndef WARIGARI
			if (autoPlay == true && drawHandle == MD_PLAY) {
				BoxOpen();

			}
#endif
		}
		break;
	case COMING://복귀
		pObj->dirF = pObj->dirX = LEFT;

		if (*tPtr >= 120) {
			ao[pObj->target].y -= 50 * _2X;
			GotoObjXY(pObj, pObj->nx, pObj->ny, (*tPtr - 120) * _2X);
			ao[pObj->target].y += 50 * _2X;
		}
		else if (*tPtr >= 100) {
			GotoObjXY(pObj, pObj->nx, pObj->ny, (*tPtr - 100) * _2X);
		}
		else {
			//해파리일경우 점프중에만 움직인다.
			if (pObj->type == ENEMY_JELLYFISH
				|| pObj->type == ENEMY_JELLYFISH_RED
				|| pObj->type == ENEMY_JELLYFISH_BLUE
				|| pObj->type == ENEMY_JELLYFISH_PURPLE
				|| pObj->type == ENEMY_JELLYFISH_GREEN
				|| pObj->type == ENEMY_JELLYFISH_GOLD
				|| pObj->type == ENEMY_JELLYFISH_BLACK) {
				if (pObj->dirY == UP)
					pObj->dx = *tPtr * DIR(pObj->dirX);
			}
			else {
				pObj->dx = *tPtr * DIR(pObj->dirX);
			}

			//DY
			tPtr += ret;

			if (*tPtr >= 100) {
				//해파리일경우 플레이어가 자기보다 20px 이상 위에있을때만 점프를 뛴다
				if ((pObj->type == ENEMY_JELLYFISH
					|| pObj->type == ENEMY_JELLYFISH_RED
					|| pObj->type == ENEMY_JELLYFISH_BLUE
					|| pObj->type == ENEMY_JELLYFISH_PURPLE
					|| pObj->type == ENEMY_JELLYFISH_GREEN
					|| pObj->type == ENEMY_JELLYFISH_GOLD
					|| pObj->type == ENEMY_JELLYFISH_BLACK)
					&& ao[pObj->target].y - pObj->y - 20 * _2X > 0)
					pObj->dy = 0;
				else {
					pObj->dirY = UP;
					pObj->my = true;
					pObj->status = JUMP;
					pObj->jumpFrame = *tPtr - 100;
				}
			}
			else
				pObj->dy = *tPtr;
		}

		//시작포인트에 도착했으면 소환수를 다시 없애준다.
		if (pObj->x <= pObj->nx) {
			//for (i = SOLDIER; i < PLAYERALL; i++) {
			//	ao[i].active = false;
			//}
			//memset(pObj, 0, sizeof(OBJECT));

			pObj->moveHandler = VANISHMOVE;
			pObj->drawHandler = VANISHDRAW;
			pObj->frame = 0;
			//CrewMove에서는 DMGUPDATE만 설정해주고 프레임 활성화는 여기서 해주고 1이 되면 다음턴으로 넘어간다.
			onceDmgUpdateFrame = 2 * FPS;
			//WhoIsNextTurn();

			/*
			pObj->x = pObj->nx;
			pObj->y = pObj->ny;
			pObj->dx = 0;
			pObj->dy = 0;
			pObj->dirX = pObj->dirF = RIGHT;
			pObj->frame = 0;
			pObj->mainFrame = 0;
			pObj->etc = 0;
			*/

			option.gameControl = CONTROL_MANUAL;
		}
		break;
	}

	EnemyMove_AddObj2(pObj);
	EnemyMove_AddObj(pObj);

END:
	EnemyMoveCommon(pObj);

}
void VanishMove(OBJECT* pObj)
{
	int i;
	int obj = GetObjFromPtr(pObj);
	int startObj;
	int endObj;

	if (obj < PLAYERALL) {
		startObj = BULLET;
		endObj = ENEMYUSEROBJ;
	}
	//솔져면
	else if (obj == SOLDIER) {
		startObj = SOLDIER;
		endObj = SOLDIER;
	}
	else {
		startObj = ENEMY;
		endObj = NEUTRAL;
	}

	pObj->frame++;

	if (drawHandle == MD_PLAY || drawHandle == MD_BATTLE || drawHandle == MD_RAID || drawHandle == MD_BOSSRAID) {
		switch (pObj->frame) {
		case 2:
			PlayMusic(M_BANG);
			break;
		}
	}

	if (pObj->frame == FPS && obj >= ENEMY) {
		//여기서 보스를 날려버리는 곳으로 이동시킬것
		//if (robin.bossRoom == true) {
		//	GotoStageClear();
		//}
	}
	else if (pObj->frame > FPS) {
		if (obj >= ENEMY)
			switch (pObj->type) {
			case ENEMY_CASTLE_BOSS3:
			case ENEMY_CASTLE_BOSS3_RED:
			case ENEMY_CASTLE_BOSS3_BLUE:
			case ENEMY_CASTLE_BOSS3_PURPLE:
			case ENEMY_CASTLE_BOSS3_GREEN:
			case ENEMY_CASTLE_BOSS3_GOLD:
			case ENEMY_CASTLE_BOSS3_BLACK:
				memset(pObj, 0, sizeof(OBJECT));
				break;
			case ENEMY_CASTLE_BOSS1:
			case ENEMY_CASTLE_BOSS1_RED:
			case ENEMY_CASTLE_BOSS1_BLUE:
			case ENEMY_CASTLE_BOSS1_PURPLE:
			case ENEMY_CASTLE_BOSS1_GREEN:
			case ENEMY_CASTLE_BOSS1_GOLD:
			case ENEMY_CASTLE_BOSS1_BLACK:
				memset(pObj, 0, sizeof(OBJECT));
				break;
			case ENEMY_FROG:
			case ENEMY_FROG_RED:
			case ENEMY_FROG_BLUE:
			case ENEMY_FROG_PURPLE:
			case ENEMY_FROG_GREEN:
			case ENEMY_FROG_GOLD:
			case ENEMY_FROG_BLACK:
				if (AliveEnemyCnt() == true/* && robin.bossRoom == true*/)
					goto DROP;
			case ENEMY_LARVA:
			case ENEMY_LARVA_RED:
			case ENEMY_LARVA_BLUE:
			case ENEMY_LARVA_PURPLE:
			case ENEMY_LARVA_GREEN:
			case ENEMY_LARVA_GOLD:
			case ENEMY_LARVA_BLACK:
				if (AliveEnemyCnt() == true/* && robin.bossRoom == true*/)
					goto DROP;
			case ENEMY_SALAMANDER:
			case ENEMY_SALAMANDER_RED:
			case ENEMY_SALAMANDER_BLUE:
			case ENEMY_SALAMANDER_PURPLE:
			case ENEMY_SALAMANDER_GREEN:
			case ENEMY_SALAMANDER_GOLD:
			case ENEMY_SALAMANDER_BLACK:
				if (AliveEnemyCnt() == true/* && robin.bossRoom == true*/)
					goto DROP;
			case ENEMY_SNAIL:
			case ENEMY_SNAIL_RED:
			case ENEMY_SNAIL_BLUE:
			case ENEMY_SNAIL_PURPLE:
			case ENEMY_SNAIL_GREEN:
			case ENEMY_SNAIL_GOLD:
			case ENEMY_SNAIL_BLACK:
			case ENEMY_TREE:
			case ENEMY_TREE_RED:
			case ENEMY_TREE_BLUE:
			case ENEMY_TREE_PURPLE:
			case ENEMY_TREE_GREEN:
			case ENEMY_TREE_GOLD:
			case ENEMY_TREE_BLACK:
				if (AliveEnemyCnt() == true/* && robin.bossRoom == true*/)
					goto DROP;
			case ENEMY_SLING:
			case ENEMY_SLING_RED:
			case ENEMY_SLING_BLUE:
			case ENEMY_SLING_PURPLE:
			case ENEMY_SLING_GREEN:
			case ENEMY_SLING_GOLD:
			case ENEMY_SLING_BLACK:
				if (AliveEnemyCnt() == true/* && robin.bossRoom == true*/)
					goto DROP;
				break;
			case ENEMY_MACHINE:
			case ENEMY_MACHINE_RED:
			case ENEMY_MACHINE_BLUE:
			case ENEMY_MACHINE_PURPLE:
			case ENEMY_MACHINE_GREEN:
			case ENEMY_MACHINE_GOLD:
			case ENEMY_MACHINE_BLACK:
				if (pObj->moveHandler == MACHINEMANAGERMOVE && AliveEnemyCnt() == true/* && robin.bossRoom == true*/)
					goto DROP;
				break;
			case ENEMY_GHOST:
			case ENEMY_GHOST_RED:
			case ENEMY_GHOST_BLUE:
			case ENEMY_GHOST_PURPLE:
			case ENEMY_GHOST_GREEN:
			case ENEMY_GHOST_GOLD:
			case ENEMY_GHOST_BLACK:
				if (AliveEnemyCnt() == true/* && robin.bossRoom == true*/)
					goto DROP;
				break;
			case ENEMY_SNOWMAN:
			case ENEMY_SNOWMAN_RED:
			case ENEMY_SNOWMAN_BLUE:
			case ENEMY_SNOWMAN_PURPLE:
			case ENEMY_SNOWMAN_GREEN:
			case ENEMY_SNOWMAN_GOLD:
			case ENEMY_SNOWMAN_BLACK:
				if (AliveEnemyCnt() == true/* && robin.bossRoom == true*/)
					goto DROP;
				break;
			case ENEMY_DARKDRAGON:
			case ENEMY_DARKDRAGON_RED:
			case ENEMY_DARKDRAGON_BLUE:
			case ENEMY_DARKDRAGON_PURPLE:
			case ENEMY_DARKDRAGON_GREEN:
			case ENEMY_DARKDRAGON_GOLD:
			case ENEMY_DARKDRAGON_BLACK:
				for (i = startObj; i < endObj; i++) {
					if ((ao[i].type == ENEMY_DARKDRAGON
						|| ao[i].type == ENEMY_DARKDRAGON_RED
						|| ao[i].type == ENEMY_DARKDRAGON_BLUE
						|| ao[i].type == ENEMY_DARKDRAGON_PURPLE
						|| ao[i].type == ENEMY_DARKDRAGON_GREEN
						|| ao[i].type == ENEMY_DARKDRAGON_GOLD
						|| ao[i].type == ENEMY_DARKDRAGON_BLACK)
						&& i != GetObjFromPtr(pObj)) {
						memset(&ao[i], 0, sizeof(OBJECT));
					}
				}
				if (AliveEnemyCnt() == true/* && robin.bossRoom == true*/)
					goto DROP;
				break;
			case ENEMY_BAHAMUT:
			case ENEMY_BAHAMUT_RED:
			case ENEMY_BAHAMUT_BLUE:
			case ENEMY_BAHAMUT_PURPLE:
			case ENEMY_BAHAMUT_GREEN:
			case ENEMY_BAHAMUT_GOLD:
			case ENEMY_BAHAMUT_BLACK:
				for (i = startObj; i < endObj; i++) {
					if ((ao[i].type == ENEMY_BAHAMUT
						|| ao[i].type == ENEMY_BAHAMUT_RED
						|| ao[i].type == ENEMY_BAHAMUT_BLUE
						|| ao[i].type == ENEMY_BAHAMUT_PURPLE
						|| ao[i].type == ENEMY_BAHAMUT_GREEN
						|| ao[i].type == ENEMY_BAHAMUT_GOLD
						|| ao[i].type == ENEMY_BAHAMUT_BLACK)
						&& i != GetObjFromPtr(pObj)) {
						memset(&ao[i], 0, sizeof(OBJECT));
					}
				}
				if (AliveEnemyCnt() == true/* && robin.bossRoom == true*/)
					goto DROP;
				break;

			case ENEMY_BOAR:
			case ENEMY_BOAR_RED:
			case ENEMY_BOAR_BLUE:
			case ENEMY_BOAR_PURPLE:
			case ENEMY_BOAR_GREEN:
			case ENEMY_BOAR_GOLD:
			case ENEMY_BOAR_BLACK:
				if (AliveEnemyCnt() == true/* && robin.bossRoom == true*/)
					goto DROP;
				break;
			default:
				if (AliveEnemyCnt() == true/* && robin.bossRoom == true*/)
					goto DROP;
			DROP:
				break;
			}

		//투기장이면
		// 투기장에서 몬스터를 다 죽이면 다음 방으로 넘겨준다.
		//몬스터들을 다 죽였는지 체크
		pObj->active = false;
		//if (obj == SOLDIER && pObj->type == MAXX)
		//	WhoIsNextTurn();
#ifdef ENEMYHPBAR
		ArrangeEnemyHpBar();
#endif
		//if (attackSequence != ATTACKSEQUENCE_ACTION)
		ArrangeEnemyTarget();
		arenaKill++;

		//SetBox(pObj, BOX_CASTLE0 + castleOrder[robin.castle]);

		if (robin.curWaveIdx == GetMaxWaveCnt() && AliveEnemyCnt() == 0) {
			//여기서 획득한 
			
			DropItem(pObj, ITEM_BOX);
			//여기서 코인은 획득하게 해준다.
			turnListIdx = 0;
			turn = 0;
			turnFrame = 1;
			attackSequence = ATTACKSEQUENCE_COIN;
			//GotoStageClear();
		}
	}
}

void RegenMove(OBJECT* pObj)
{
	int i, j;
	int obj = GetObjFromPtr(pObj);

	pObj->frame++;
	//부활전에는 
	if (pObj->active == false) {
		if (pObj->frame > REGENFRAME) {
			pObj->active = true;
			pObj->frame = 0;
			pObj->motion = crewPos[pObj->type * 5];
		}

		if (pObj->frame == REGENFRAME - 8) {
			if (obj < PLAYERALL)
				EffectSound(M_JUMP);
			else
				EffectSound(M_ENEMYDEAD);
			//살아날때 디버프 끄기
			memset(pObj->debuf, 0, sizeof(pObj->debuf));
		}
	}
	else {
		if (pObj->type == ENEMY_LIGHTNING
			|| pObj->type == ENEMY_LIGHTNING_RED
			|| pObj->type == ENEMY_LIGHTNING_BLUE
			|| pObj->type == ENEMY_LIGHTNING_PURPLE
			|| pObj->type == ENEMY_LIGHTNING_GREEN
			|| pObj->type == ENEMY_LIGHTNING_GOLD
			|| pObj->type == ENEMY_LIGHTNING_BLACK) {
			// PO_C22_LIGHTNING0 부분 아마 div파일 수정 전에는 에러날듯 합니다.
			// 에러나면 일단 (PO_C22_LIGHTNING0) 이거 나오는 부분 모두주석처리 해주세요
			if (pObj->cmf == CMF_SPARK)
				pObj->motion = PO_C22_N0;
			else
				pObj->motion = PO_C22_LIGHTNING0;
			InitMotion(pObj);
		}
		//여기서 부활전에 슬롯머신에서 점프하면서 커지면서 좌우로 왔다갔다하는 식의 것을 그대로 zoom, y, dirX를 조절한다.
		//참고로 여기 ny는 시작포인트.
		if (pObj->frame < FPS / 2) {
			if (obj < PLAYERALL) {
				// 0) 최초 프레임에서 기본값 저장
				static int   baseDir = 1;

				if (pObj->frame == 1) {
					baseDir = (pObj->dirX == 0) ? 1 : pObj->dirX;  // 0이면 1로
				}

				const float baseY = (float)pObj->ny;   // 시작 포인트
				// 탄력 점프 파라미터
				const float H = 32.0f * _2X;          // 점프 높이 (더 탄력 = 조금 더 높게 가능)
				const float bounceH = 7.0f * _2X;     // 착지 바운스 높이(작게)
				const float zoomUpAmp = pObj->defaultZoom * 0.35f; // 확대 더 급격
				const float zoomDownAmp = pObj->defaultZoom * 0.18f; // 축소(살짝 줄어드는 느낌) 원치 않으면 0으로

				float t = (float)(pObj->frame - 1) / (float)(FPS / 2 - 1);
				if (t < 0.f) t = 0.f;
				if (t > 1.f) t = 1.f;

				// 메인 점프: sin + 곡률 강화(급격하게)
				// pow를 올릴수록 중간이 nnnnnnnnnnnnnn더 '툭' 튄다
				float jump = sinf((float)M_PI * t);
				// ✅ sin 오차 방지: 0~1로 강제
				if (jump < 0.f) jump = 0.f;
				if (jump > 1.f) jump = 1.f;

				float jumpSharp = powf(jump, 0.50f);  // 1보다 작으면 더 급격(0.45~0.7 추천)


				// 착지 바운스: 마지막 20% 구간에 작은 sin 한 번
				float b = 0.f;
				if (t > 0.75f) {
					float tb = (t - 0.75f) / (1.0f - 0.75f);       // 0..1
					if (tb > 1.f) tb = 1.f;
					b = sinf((float)M_PI * tb) * (1.0f - tb); // 점점 줄어드는 바운스
				}

				// y: 위로 + 착지 바운스(아주 작게)
				pObj->y = (int)(baseY - H * jumpSharp + bounceH * b);
				// zoom: 급격 확대/축소
				// 확대는 빠르게 올라가고, 끝에 살짝 축소(원치 않으면 zoomDownAmp=0)
				float zUp = powf(jump, 0.30f);          // 더 급격 확대
				float zDown = (t > 0.82f) ? powf((t - 0.82f) / 0.18f, 0.7f) : 0.f; // 착지하며 축소
				if (zDown > 1.f) zDown = 1.f;

				pObj->zoom = pObj->defaultZoom + zoomUpAmp * zUp - zoomDownAmp * zDown;
				if (pObj->zoom < pObj->defaultZoom)
					pObj->zoom = pObj->defaultZoom;

				int faceDir;

				if (pObj->frame < FPS / 2 * 0.25f)       faceDir = (pObj->frame / 2) % 2;
				else if (pObj->frame < FPS / 2 * 0.50f)  faceDir = (pObj->frame) % 2;
				else                                         faceDir = (pObj->frame / 2) % 2;

				//faceDir = pObj->frame % 2;

				pObj->dirX = faceDir;
				pObj->dirF = faceDir;
			}
		}
		else if (pObj->frame == FPS / 2) {
			pObj->dead = false;
			pObj->frame = 0;
			pObj->zoom = pObj->defaultZoom;
			pObj->x = pObj->nx;
			pObj->y = pObj->ny;
			pObj->dirX = pObj->dirF = RIGHT;
			if (pObj->cmf < TOTALCHAR) {
				//pObj->hp = pObj->ps[PS_HP];
				pObj->moveHandler = PLAYERMOVE;
				pObj->drawHandler = PLAYERDRAW;
				if (drawHandle == MD_PLAY) {
					waveStatus = WAVESTATUS_PLAY;
					j = 0;
					for (i = 0; i < MAXENEMY * MAXENEMYOBJ; i++) {
						if (robin.enemyObj[i].active == true)
							j++;
					}

					//인터랙티브 전투 튜토리얼 중에는 이 블록을 타면 안 된다. 컷씬->실전투 핸드오프에서
					//GotoPlay()가 SetHero()를 부르는 바람에 주인공이 등장 낙하 연출(REGENMOVE)을 다시
					//하는데, 그 착지 시점에 여기서 CopyEnemyObj()로 백업본을 덮어쓰고 살아있는 몬스터를
					//전부 REGENMOVE로 되돌려버린다. 그러면 컷씬에서 막 스폰한 몬스터가 등장 연출을
					//처음부터 다시 하고 BAR_BOSSHP도 다시 InitBar되어, "몬스터 생성이 끝난 뒤에도 계속
					//다시 초기화되는" 증상이 된다. 게다가 moveHandler가 ENEMYMOVETURN에서 벗어나므로
					//WaveControler()의 tutorialWaitingEnemyLand 체크가 터치를 다시 잠근다.
					if (obj == ROBIN && j > 0 && !(robinmap == MAP_DIORAMA_TOLEM && !robin.demoSeen[DEMO_TUTORIAL_END])) {
						CopyEnemyObj();
						InitBar(BAR_BOSSHP);

						for (i = 0; i < MAXENEMY * MAXENEMYOBJ; i++) {
							//일단 리젠무브로 바꾸고
							if (ao[ENEMY + i].active == true && ao[ENEMY + i].mom == ENEMY + i) {
								ao[ENEMY + i].moveHandler = REGENMOVE;
								ao[ENEMY + i].drawHandler = REGENDRAW;
								//AddBar(&bar[BAR_BOSSHP], ao[ENEMY + i].hp, BARFRAME);
							}
						}
					}
				}

				//솔져면 스킬이야.
				if (obj == SOLDIER) {
					SetHotKey(&ao[obj], HOTKEY_SKILL, pObj->currentSkill, 0);
					HotKeyPress(&ao[obj], 0);
					switch (pObj->currentSkill) {
					case SKILL_DIANA8://플레임
						pObj->flamer = FPS * 2;
						break;
					}
				}

				if (bar[BAR_BOSSHP].active == false && drawHandle != MD_DEMO)
					InitBar(BAR_BOSSHP);

				//pObj->currentSkill = 0;
			}
			else if (obj < PLAYERALL) {
				pObj->moveHandler = CREWMOVE;
				pObj->drawHandler = CREWDRAW;
			}
			//SOLDIER~ITEMBOX
			else if (obj < ITEMBOX) {
				pObj->moveHandler = SUMMONMOVE;
				pObj->drawHandler = ENEMYDRAW;
			}
			else {
				pObj->hp = pObj->maxhp;
				//보상 상자(MD_GACHA)처럼 화면만 덮는 연출이 떠 있는 사이에 착지해도
				//아레나는 계속 돌고 있으므로 ENEMYMOVETURN이어야 한다(IsArenaRunning() 주석 참고).
				if (IsArenaRunning())
					pObj->moveHandler = ENEMYMOVETURN;
				else
					pObj->moveHandler = enemyData[pObj->type * ENEMYDATASIZE + ENEMYDATA_MOVEHANDLER];
				pObj->drawHandler = enemyData[pObj->type * ENEMYDATASIZE + ENEMYDATA_DRAWHANDLER];
				AddBar(&bar[BAR_BOSSHP], pObj->hp, BARFRAME);
			}
			//아래 루프의 break가 if 밖에 있어 첫 칸만 보고 빠져나온다.
			//배가 아니면 대입이 없어 초기화도 안 된 값으로 obj와 비교했다.
			int startObj = -1;

			for (i = BULLET; i < NEUTRAL; i++) {
				if (ao[i].type == ENEMY_SHIP ||
					ao[i].type == ENEMY_SHIP_RED ||
					ao[i].type == ENEMY_SHIP_BLUE ||
					ao[i].type == ENEMY_SHIP_PURPLE ||
					ao[i].type == ENEMY_SHIP_GREEN ||
					ao[i].type == ENEMY_SHIP_GOLD ||
					ao[i].type == ENEMY_SHIP_BLACK) {
					startObj = i;
					break;
				}
			}
			//소환수거나 
			if (obj >= SOLDIER) {
				switch (pObj->type) {
				case ENEMY_SHIP:
				case ENEMY_SHIP_RED:
				case ENEMY_SHIP_BLUE:
				case ENEMY_SHIP_PURPLE:
				case ENEMY_SHIP_GREEN:
				case ENEMY_SHIP_GOLD:
				case ENEMY_SHIP_BLACK:
					if (obj == startObj) {
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
							ao[i].mom = i;
							InitBar(BAR_ENEMYHP + GetEnemyBarIdx(i));
							ao[i].mom = obj + 4;
							//bar[BAR_ENEMYHP + GetEnemyBarIdx(i)].active = true;
							//ao[i].mom = obj + 4;
							ao[i].nx = ao[i].x = BATTLEPOSITION_ENEMY_X - 2 * TSIZE;// -(float)GetEnemyBarIdx(obj) * 2 * _2X;
							ao[i].y = ENEMYPOSITION_Y - 3 * TSIZE;

							MoveObj(&ao[i]);
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
					if (pObj->moveHandler != BAHAMUTHEADMOVE && pObj->moveHandler != BAHAMUTNECKMOVE)
						pObj->moveHandler = BAHAMUTBODYMOVE;
					break;
				case ENEMY_CASTLE_BOSS1:
				case ENEMY_CASTLE_BOSS1_RED:
				case ENEMY_CASTLE_BOSS1_BLUE:
				case ENEMY_CASTLE_BOSS1_PURPLE:
				case ENEMY_CASTLE_BOSS1_GREEN:
				case ENEMY_CASTLE_BOSS1_GOLD:
				case ENEMY_CASTLE_BOSS1_BLACK:
					if (pObj->moveHandler != DEBRIONARMMOVE) {
						pObj->moveHandler = DEBRIONBODYMOVE;
						InitMotion(pObj);
					}
					break;
				}

				BackUpEnemyObj();
				SaveGame();
			}
		}

	}
}


void DemoMove(OBJECT* pObj)
{
	const short* tPtr;
	int ret, i;
	int obj = GetObjFromPtr(pObj);
	int startObj;
	int endObj;

	if (obj < PLAYERALL) {
		startObj = PLAYER;
		endObj = PLAYERALL;
	}
	else {
		startObj = ENEMY;
		endObj = NEUTRAL;
	}

	switch (pObj->type) {
	case NPC_WOMANGHOST:
		if (Abs(pObj->dy) >= 2 * _2X)
			pObj->dirY = pObj->dirY == UP ? DOWN : UP;

		if (pObj->dirY == UP)
			pObj->dy += 1 * _2X;
		else if (pObj->dirY == DOWN)
			pObj->dy -= 1 * _2X;

		pObj->status = FLYING;
		pObj->y += pObj->dy;

		tPtr = cmf_status_data[pObj->cmf][pObj->etc];

		//pObj->cmf가 잘못됬을때 예외처리(플레이어는 DEMOMOVE호출안함)
		if (pObj->cmf < 3) {
			memset(pObj, 0, sizeof(OBJECT));
			return;
		}

		ret = *tPtr;

		//Motion
		tPtr += (2 + (pObj->frame % ret));
		pObj->motion = *tPtr;

		pObj->frame++;
		InitMotion(pObj);
		return;
	case ENEMY_LARVA:
	case ENEMY_LARVA_RED:
	case ENEMY_LARVA_BLUE:
	case ENEMY_LARVA_PURPLE:
	case ENEMY_LARVA_GREEN:
	case ENEMY_LARVA_GOLD:
	case ENEMY_LARVA_BLACK:
		pObj->status = FLYING;
		break;
	case NPC_LORA:
		pObj->x += pObj->dx;
		pObj->y += pObj->dy;
		break;
	case NPC_GAGEL:
		pObj->status = FLYING;
		break;
	case ENEMY_IFRIT:
	case ENEMY_IFRIT_RED:
	case ENEMY_IFRIT_BLUE:
	case ENEMY_IFRIT_PURPLE:
	case ENEMY_IFRIT_GREEN:
	case ENEMY_IFRIT_GOLD:
	case ENEMY_IFRIT_BLACK:
		EnemyMove_AddObj(pObj);
		break;
	case NPC_EVAN:
		if (pObj->motion == PO_C112_THROW1) {
			int i;
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_EVANBULLET);
					ao[i].etc = 5;
					ao[i].type = 1;
					InitMotion(&ao[i]);
					break;
				}
			}
		}
		break;
	case ENEMY_ANGEL:
	case ENEMY_ANGEL_RED:
	case ENEMY_ANGEL_BLUE:
	case ENEMY_ANGEL_PURPLE:
	case ENEMY_ANGEL_GREEN:
	case ENEMY_ANGEL_GOLD:
	case ENEMY_ANGEL_BLACK:
		if (pObj->motion == PO_C37_ATK0) {
			int i;
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false && ao[i].type == 0)
					AddObject(&ao[i], pObj, ADDOBJ_ANGEL);
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
		pObj->status = FLYING;

		if (pObj->motion == PO_C43_EVENT_FIRE4) {
			for (i = startObj; i < endObj; i++) {
				if (ao[i].active == false) {
					AddObject(&ao[i], pObj, ADDOBJ_BAHAMUTFIRE);
					ao[i].x += 63 * DIR(pObj->dirX) * _2X;
					ao[i].y -= 94 * _2X;
					ao[i].mom = GetObjFromPtr(pObj);
					break;
				}
			}
		}
		break;
	case ENEMY_THUNDER:
	case ENEMY_THUNDER_RED:
	case ENEMY_THUNDER_BLUE:
	case ENEMY_THUNDER_PURPLE:
	case ENEMY_THUNDER_GREEN:
	case ENEMY_THUNDER_GOLD:
	case ENEMY_THUNDER_BLACK:
	case NPC_MERCHANT:
	case NPC_UNCLE:
	case NPC_AUSTIN:
	case NPC_SOUL:
	case ENEMY_FAIRY:
	case ENEMY_FAIRY_RED:
	case ENEMY_FAIRY_BLUE:
	case ENEMY_FAIRY_PURPLE:
	case ENEMY_FAIRY_GREEN:
	case ENEMY_FAIRY_GOLD:
	case ENEMY_FAIRY_BLACK:
	case ENEMY_SHIP:
	case ENEMY_SHIP_RED:
	case ENEMY_SHIP_BLUE:
	case ENEMY_SHIP_PURPLE:
	case ENEMY_SHIP_GREEN:
	case ENEMY_SHIP_GOLD:
	case ENEMY_SHIP_BLACK:
	case ENEMY_FOGRA:
	case ENEMY_FOGRA_RED:
	case ENEMY_FOGRA_BLUE:
	case ENEMY_FOGRA_PURPLE:
	case ENEMY_FOGRA_GREEN:
	case ENEMY_FOGRA_GOLD:
	case ENEMY_FOGRA_BLACK:
	case ENEMY_DEATH:
	case ENEMY_DEATH_RED:
	case ENEMY_DEATH_BLUE:
	case ENEMY_DEATH_PURPLE:
	case ENEMY_DEATH_GREEN:
	case ENEMY_DEATH_GOLD:
	case ENEMY_DEATH_BLACK:
	case ENEMY_GHOST:
	case ENEMY_GHOST_RED:
	case ENEMY_GHOST_BLUE:
	case ENEMY_GHOST_PURPLE:
	case ENEMY_GHOST_GREEN:
	case ENEMY_GHOST_GOLD:
	case ENEMY_GHOST_BLACK:
	case ENEMY_ICESUN:
	case ENEMY_ICESUN_RED:
	case ENEMY_ICESUN_BLUE:
	case ENEMY_ICESUN_PURPLE:
	case ENEMY_ICESUN_GREEN:
	case ENEMY_ICESUN_GOLD:
	case ENEMY_ICESUN_BLACK:
		pObj->status = FLYING;
		break;
	case NPC_KING:
		break;
	case NPC_DELPIOS:
		if (isDemo == false) {
			pObj->dirX = pObj->dirF = ao[NearPlayer(pObj)].x - pObj->x > 0 ? RIGHT : LEFT;
		}
		break;
	case NPC_BEAD:
		break;
	}

	if (pObj->etc >= 0) {
		tPtr = cmf_status_data[pObj->cmf][pObj->etc];

		//pObj->cmf가 잘못됬을때 예외처리(플레이어는 DEMOMOVE호출안함)
		if (pObj->cmf < 3) {
			memset(pObj, 0, sizeof(OBJECT));
			return;
		}

		if (*tPtr == 0) {
			EnemyMoveCommon(pObj);
			return;
		}

		ret = *tPtr;

		//Motion
		tPtr += (2 + (pObj->frame % ret));
		pObj->motion = *tPtr;

		////DX
		//tPtr += ret;
		//pObj->dx = *tPtr * DIR(pObj->dirX);

		////DY
		//tPtr += ret;
		//pObj->dy = *tPtr;

		//DX
		tPtr += ret;

		if (*tPtr >= 100)
			GotoObj(&ao[NearPlayer(pObj)], pObj, (*tPtr - 100) * _2X / MOTIONDIV);
		else {
			pObj->dx = *tPtr * DIR(pObj->dirX) / MOTIONDIV;

			//DY
			tPtr += ret;

			if (*tPtr >= 100) {
				pObj->dirY = UP;
				pObj->my = true;
				pObj->status = JUMP;
				pObj->jumpFrame = *tPtr - 100;
			}
			else
				pObj->dy = *tPtr;
		}
	}

	if (drawHandle == MD_DEMO)
		switch (pObj->type) {
		case ENEMY_CASTLE_BOSS4:
		case ENEMY_CASTLE_BOSS4_RED:
		case ENEMY_CASTLE_BOSS4_BLUE:
		case ENEMY_CASTLE_BOSS4_PURPLE:
		case ENEMY_CASTLE_BOSS4_GREEN:
		case ENEMY_CASTLE_BOSS4_GOLD:
		case ENEMY_CASTLE_BOSS4_BLACK:
			if (pObj->etc == CASTLEBOSS4_WALK && (pObj->motion == PO_C51_W1 || pObj->motion == PO_C51_W4)) {
				DropItem(pObj, ITEM_GOLD);
				PlayMusic(M_KUNG);
			}
			else if (pObj->etc == CASTLEBOSS4_WIND && (pObj->motion == PO_C51_SA7)) {
				DropItem(&ao[PLAYER], ITEM_GOLD);
				DropItem(&ao[ENEMY], ITEM_GOLD);//NPC_KING
				DropItem(&ao[ENEMY + 1], ITEM_GOLD);//NPC_LORA
				DropItem(&ao[ENEMY + 2], ITEM_GOLD);//NPC_SEBASTIAN
				DropItem(&ao[ENEMY + 3], ITEM_GOLD);//NPC_ADELKNIGHT
				PlayMusic(M_SWORDHIT);
			}
			break;
		}

	if (npcdarkStone && pObj->etc != 2) {
		int i;
		int angle = -1;
		OBJECT* pDark = &ao[npcdarkStone];

		pObj->status = WALK;
		pObj->motion = PO_C0_N0;

		//이동할 각도
		angle = (pDark->dirX == RIGHT) ? 340 : 20;

		pObj->y -= 12 * _2X;
		//각도만큼 평행변환
		pObj->x = pDark->x + (BC_mathCos1024(angle) * (pObj->x - pDark->x) >> 10) - (BC_mathSin1024(angle) * (pObj->y - pDark->y) >> 10);
		pObj->y = pDark->y + (BC_mathSin1024(angle) * (pObj->x - pDark->x) >> 10) + (BC_mathCos1024(angle) * (pObj->y - pDark->y) >> 10);

		//거리 계산
		i = Max(24 * _2X, GetDistance(pDark, pObj));
		pObj->y += 12 * _2X;

		if (i < 36 * _2X) {
			//거리가 짧다면 늘려준다.
			pObj->x = pDark->x + UpDiv((pObj->x - pDark->x) * (i + 2 * _2X), i);
			pObj->y = pDark->y + UpDiv((pObj->y - pDark->y) * (i + 2 * _2X), i);
			i += 2 * _2X;
		}
	}
	else
		EnemyMoveCommon(pObj);
}

void MerchantMove(OBJECT* pObj)
{
	pObj->status = FLYING;
	InitMotion(pObj);
}

void NpcMove(OBJECT* pObj)
{
	if (pObj->status == 100) {
		pObj->frame++;
		pObj->motion = pObj->frame % 3;
		return;
	}

	GetTile(pObj);
	pObj->dirF = pObj->dirX = ao[NearPlayer(pObj)].x > pObj->x ? RIGHT : LEFT;

	if (Abs(ao[NearPlayer(pObj)].x - pObj->x) > 20 * _2X && pObj->status == WALK) {
		if (ao[NearPlayer(pObj)].y + GetObjHeight(&ao[NearPlayer(pObj)]) != pObj->y && (ao[NearPlayer(pObj)].status == JUMP || ao[NearPlayer(pObj)].status == FALL)) {
			//pObj->attack = PO_C61_N0;
			goto NPCEND;
		}
		else if (mapInfoArray[mapInfoOff + pObj->tileY2 * rw + (pObj->dirX == LEFT ? pObj->tileX1 - 1 : pObj->tileX2 + 1)] == TILE_BLOCK || (pObj->y - ao[NearPlayer(pObj)].y >= TSIZE && ao[NearPlayer(pObj)].status == WALK)) {
			pObj->status = JUMP;
			pObj->jumpFrame = 0;
		}

		pObj->attack = PO_C61_W0;
		GotoObj(&ao[NearPlayer(pObj)], pObj, ((pObj->status == JUMP || pObj->status == FALL) ? 8 * _2X : 6 * _2X));
	}
	else if (pObj->y - ao[NearPlayer(pObj)].y >= TSIZE && pObj->y - ao[NearPlayer(pObj)].y <= (TSIZE << 2) && pObj->status == WALK && ao[NearPlayer(pObj)].status == WALK) {
		pObj->attack = PO_C61_W0;
		pObj->status = JUMP;
		pObj->jumpFrame = 0;
		GotoObj(&ao[NearPlayer(pObj)], pObj, ((pObj->status == JUMP || pObj->status == FALL) ? 8 * _2X : 6 * _2X));
	}
	else if (pObj->status == JUMP || pObj->status == FALL) {
		if (Abs(ao[NearPlayer(pObj)].x - pObj->x) > 10) {
			pObj->attack = PO_C61_W0;
			GotoObj(&ao[NearPlayer(pObj)], pObj, ((pObj->status == JUMP || pObj->status == FALL) ? 8 * _2X : 6 * _2X));
		}
	}
	else if (pObj->status == WALK && ao[NearPlayer(pObj)].y > pObj->y && GetOnTile(pObj) == 7) {
		pObj->y += 8 * _2X;
	}
	else {
		pObj->dx = pObj->dy = 0;
		pObj->attack = PO_C61_N0;
	}

	dontWarp = (Abs(pObj->x - ao[NearPlayer(pObj)].x) > 30 * _2X && pObj->status != 100);

NPCEND:
	EnemyMoveCommon(pObj);
	pObj->motion = pObj->attack + pObj->frame % 3;
	pObj->attackFrame = pObj->etc;
	pObj->etc = Abs(pObj->x - ao[NearPlayer(pObj)].x);

	//if (robinmap == 19 && pObj->x <= 50 * _2X)
	//	pObj->status = 100;
}

void RideGolem(OBJECT* pObj)
{
	OBJECT* oPtr = &ao[NearPlayer(pObj)];

	//여기서 태워준다.
	oPtr->x = pObj->x;
	oPtr->y = pObj->y;
	oPtr->type = pObj->type;
	oPtr->drawHandler = pObj->drawHandler;
	oPtr->motion = pObj->motion;
	oPtr->cmf = pObj->cmf;
	oPtr->status = pObj->status;
	oPtr->dirF = pObj->dirF;
	oPtr->dirX = pObj->dirX;
	oPtr->dirY = pObj->dirY;
	oPtr->attack = false;
	oPtr->attackFrame = 0;
	oPtr->moveHandler = PLAYERGOLEMMOVE;

	memset(oPtr->buff, 0, sizeof(oPtr->buff));
	memset(oPtr->debuf, 0, sizeof(oPtr->debuf));
	RefreshStat(pObj);

	InitMotion(oPtr);

	pObj->active = false;
}

void TakeDown(void)
{
	int k;

	for (k = ENEMY; k < NEUTRAL; k++) {
		if (ao[k].active == false) {
			ao[k] = ao[PLAYER];
			//ao[k].moveHandler = DEMOMOVE;
			ao[k].name = TEXT_MONSTERNAME_START + ao[k].type;
			InitMotion(&ao[k]);
			break;
		}
	}

	ao[PLAYER].drawHandler = PLAYERDRAW;
	ao[PLAYER].moveHandler = PLAYERMOVE;
	ao[PLAYER].type = ROBIN;
	ao[PLAYER].cmf = ROBIN;
	InitMotion(&ao[PLAYER]);
}

void NpcShipMove(OBJECT* pObj)
{
	int i;

	pObj->motion = PO_C80_N0;
	InitMotion(pObj);

	//이동처리
	switch (pObj->etc) {
	case 0:
		pObj->dx = 0;
		break;
	case 1:
		pObj->dx = 2 * _2X;
		break;
	case 2:
		pObj->dx = -2 * _2X;
		break;
	}

	pObj->x += pObj->dx;

	pObj->y -= 2 * _2X;

	for (i = 0; i < TOTALOBJECT; i++) {
		OBJECT* pCompare = &ao[i];

		if (ao[i].active && pCompare != pObj && ObjCrash(pObj, pCompare))
			pCompare->x += pObj->dx;
	}

	pObj->y += 2 * _2X;
}

void SideMove(OBJECT* pObj)
{
#define TURNGAP	TSIZE * 2

	if (pObj->mx == true) {
		int o_dirx = DIR(pObj->dirX);

		pObj->dx = 4 * o_dirx * _2X;

		if (pObj->type != OBJ_SEWAGESTONE)
			pObj->x += TURNGAP * o_dirx;

		pObj->x += pObj->dx;

		if (TileCrash(pObj) > 1)
			pObj->dirX = 1 - pObj->dirX;

		if (pObj->type != OBJ_SEWAGESTONE)
			pObj->x -= TURNGAP * o_dirx;

		PressObjCheck(pObj);
	}

#undef TURNGAP
}

void UpDownMove(OBJECT* pObj)
{
#define TURNGAP	TSIZE * 2

	if (pObj->my == true) {
		int i;
		int o_diry = DIR(pObj->dirY);

		pObj->dy = 4 * o_diry * _2X;

		if (pObj->dirY == DOWN) {
			pObj->y -= 1 * _2X;

			for (i = PLAYER; i < TOTALOBJECT; i++) {
				OBJECT* pLoop = &ao[i];

				if (pObj != pLoop && pLoop->active == true && (i < ENEMY || i >= NEUTRAL) && ObjCrash(pObj, pLoop)) {
					pLoop->y += pObj->dy;

					if (TileCrash(pLoop)) {
						pLoop->y -= pObj->dy;
						//pLoop->y += ClearGap(pLoop, 1);
						pObj->y += 1 * _2X;

						if (ObjCrash(pObj, pLoop)) {
							pObj->y -= pObj->dy;
							pObj->dirY = 1 - pObj->dirY;
						}

						pObj->y -= 1 * _2X;
					}

					if (pLoop->status == FALL && pLoop->y + pLoop->cy < pLoop->y)
						pLoop->status = WALK;
				}
			}

			pObj->y++;
		}

		if (pObj->type != OBJ_SEWAGESTONE)
			pObj->y += (TURNGAP * o_diry + pObj->dy);

		pObj->y += pObj->dy;

		if (pObj->y < TURNGAP || TileCrash(pObj) > 1)
			pObj->dirY = 1 - pObj->dirY;

		if (pObj->type != OBJ_SEWAGESTONE)
			pObj->y -= (TURNGAP * o_diry + pObj->dy);

		for (i = PLAYER; i < TOTALOBJECT; i++) {
			OBJECT* pLoop = &ao[i];

			if (pObj != pLoop && pLoop->active == true && (i < ENEMY || i >= NEUTRAL) && ObjCrash(pObj, pLoop)) {
				pLoop->y += pObj->dy;

				if ((i < BULLET || i >= ENEMY) && TileCrash(pLoop)) {
					pLoop->y -= pObj->dy;
					pObj->y -= pObj->dy;
					pObj->dirY = 1 - pObj->dirY;
				}

				if (pLoop->status == FALL && pLoop->y + pLoop->cy < pLoop->y)
					pLoop->status = WALK;
			}
		}
	}

#undef TURNGAP
}

void DropMove(OBJECT* pObj)
{
	OBJECT* player = &ao[PLAYER];
	pObj->dy = 0;
	pObj->y -= 1 * _2X;
	if (ObjCrash(pObj, player)) {
		if (pObj->onTile == 0) {
			pObj->dy = jump[JUMPFRAME - Min(JUMPFRAME - 1, pObj->frame)];
			//pObj->y += 1 * _2X;
			pObj->y += pObj->dy;
			pObj->x += pObj->dx;
			player->dy = pObj->dy;
			TileCheckY(player);
			player->status = WALK;
			player->dirY = DOWN;
		}
		else {
			pObj->y += 1 * _2X;
			return;
		}
	}
	else {
		pObj->frame = 0;
		pObj->dy = -3 * _2X;
		pObj->y += 1 * _2X;
		pObj->y += pObj->dy;
	}
	if (ObjCrash(pObj, player))
		pObj->y += TSIZE / 8;
	if (!pObj->frame && pObj->y < pObj->status)
		pObj->y = pObj->status;
}

void SewageStoneMove(OBJECT* pObj)
{
	unsigned char* tTile;

	//먼저 이동해서 해당 위치에 파이프 타일이 있는지 검사한 후 움직임을 변경한다.

	//x축 방향으로 움직이고 있을때
	if (pObj->mx == true) {
		//왼쪽방향으로 움직이고 있다면
		if (pObj->dirX == LEFT) {
			//이동 후 위치의 타일을 구한다.
			pObj->x -= 4 * _2X;
			tTile = &mapArray[(PxlUp(pObj) >> 5) * (rw - 4) + ((PxlLeft(pObj) + 10) >> 5)];
			pObj->x += 4 * _2X;
		}
		//오른쪽 방향이라면
		else {
			pObj->x += 4 * _2X;
			tTile = &mapArray[(PxlUp(pObj) >> 5) * (rw - 4) + ((PxlRight(pObj) - 10) >> 5)];
			pObj->x -= 4 * _2X;
		}

		//진행방향에 파이프가 더이상 없다면
		if (*tTile < 40) {
			//현재위치의 타일을 구한 후
			tTile = &mapArray[(PxlUp(pObj) >> 5) * (rw - 4) + (pObj->x >> 5)];

			//위쪽에 파이프가 있다면
			if (*(tTile - (rw - 4)) >= 40) {
				//위로 움직이도록 설정한다.
				pObj->mx = false;
				pObj->my = true;
				pObj->dirY = UP;
			}
			//아래쪽에 파이프가 있다면
			else if (*(tTile + (rw - 4)) >= 40) {
				//아래로 움직이도록 설정한다.
				pObj->mx = false;
				pObj->my = true;
				pObj->dirY = DOWN;
			}
			//둘다 아니라면
			else {
				//반대방향으로 돌려보낸다.
				pObj->dirX = 1 - pObj->dirX;
			}
		}
	}
	//y축 방향으로 움직이고 있을때
	else {
		//위쪽방향으로 움직이고 있다면
		if (pObj->dirY == UP) {
			//이동 후 위치의 타일을 구한다.
			pObj->y -= 4 * _2X;
			tTile = &mapArray[((PxlUp(pObj) - 4) >> 5) * (rw - 4) + (pObj->x >> 5)];
			pObj->y += 4 * _2X;
		}
		//아래쪽 방향이라면
		else {
			pObj->y += 4 * _2X;
			tTile = &mapArray[((PxlDown(pObj) - 10) >> 5) * (rw - 4) + (pObj->x >> 5)];
			pObj->y -= 4 * _2X;
		}

		//진행방향에 파이프가 더이상 없다면
		if (*tTile < 40 * _2X) {
			//현재위치의 타일을 구한 후
			tTile = &mapArray[(PxlUp(pObj) >> 5) * (rw - 4) + (pObj->x >> 5)];

			//왼쪽에 파이프가 있다면
			if (*(tTile - 1) >= 40) {
				//왼쪽으로 움직이도록 설정한다.
				pObj->mx = true;
				pObj->my = false;
				pObj->dirX = LEFT;
			}
			//오른쪽에 파이프가 있다면
			else if (*(tTile + 1) >= 40) {
				//오른쪽으로 움직이도록 설정한다.
				pObj->mx = true;
				pObj->my = false;
				pObj->dirX = RIGHT;
			}
			//둘다 아니라면
			else {
				//반대방향으로 돌려보낸다.
				pObj->dirY = 1 - pObj->dirY;
			}
		}
	}

	if (pObj->mx == true)
		SideMove(pObj);
	else
		UpDownMove(pObj);
}

void PushMove(OBJECT* pObj)
{
	int tBlock;

	if (pObj->jumpFrame > 1)
		pObj->mainFrame++;

	if (pObj->str == 0) {
		TileCheckX2(pObj);
		tBlock = BlockObj(pObj, 0);

		if (tBlock)
			pObj->x -= tBlock;

		TileCheckY2(pObj);
		tBlock = BlockObj(pObj, 1);

		if (tBlock) {
			pObj->y -= tBlock;
			pObj->jumpFrame = 0;
		}

		pObj->dx = 0;
		pObj->motion = OBJ_PUSH0 + Abs(3 - (pObj->frame % 6));

		if (pObj->etc && pObj->x == pushArray[pObj->etc * 2] * TSIZE && pObj->y == pushArray[pObj->etc * 2 + 1] * TSIZE) {
			pObj->str = 1;
		}
	}
	else
		pObj->motion = OBJ_PUSH0;

	pObj->frame++;
}

void DoorMove(OBJECT* pObj)
{
	//문 위쪽효과
	if (pObj->mainFrame) {
		pObj->mainFrame++;

		if (pObj->mainFrame >= 8)
			pObj->mainFrame = 0;
	}

	//문 아래쪽 효과
	if (pObj->jumpFrame) {
		pObj->jumpFrame++;

		if (pObj->jumpFrame >= JUMPFRAME - 1)
			pObj->jumpFrame = 0;
	}

	switch (pObj->status) {
	case OPEN:
		pObj->cy -= 5 * _2X;

		if (pObj->cy <= 8 * _2X) {
			pObj->status = OPENED;
			pObj->frame = 0;
		}
		else
			break;
	case OPENED:
		pObj->cy = 20 * _2X;
		pObj->frame++;

		if (!isDemo && pObj->type == OBJ_DOOR && pObj->frame > 5 && !ObjCrash(pObj, &ao[NearPlayer(pObj)])) {
			pObj->status = CLOSE;
			pObj->mainFrame = 1;
		}

		pObj->cy = 8 * _2X;
		break;
	case CLOSE:
		pObj->cy += 5 * _2X;
		/*
		for (i = ENEMY; i < NEUTRAL; i++) {
			if (ObjCrash(pObj, &ao[i])) {
				pObj->status = OPEN;
				pObj->mainFrame = 1;
				pObj->cy -= 5 * _2X;
				break;
			}
		}
		*/
		if (ObjCrash(pObj, &ao[NearPlayer(pObj)])) {
			pObj->status = OPEN;
			pObj->mainFrame = 1;
			pObj->cy -= 5 * _2X;
		}

		if (pObj->cy >= 48 * _2X) {
			pObj->cy = 48 * _2X;
			pObj->status = CLOSED;
			pObj->jumpFrame = 1;
			effect.shake = 4;
		}
		break;
	case CLOSED:
		pObj->cy = 47 * _2X;
		break;
	}
}

void RepulsionMove(OBJECT* pObj)
{
	OBJECT* pPlayer = &ao[NearPlayer(pObj)];

	if (ObjCrash(pPlayer, pObj)) {
		pObj->jumpLock = true;
		pPlayer->attack = false;
		//pPlayer->dirX = (pPlayer->x > pObj->x) ? RIGHT : LEFT;
		pPlayer->jumpFrame = -2;
		pPlayer->status = JUMP;
		pPlayer->dirY = UP;
		pPlayer->dx = 16;
	}
}

void ItemMove(OBJECT* pObj)
{
	int i;
#ifdef GETITEMAUTO
	int targetX, targetY;
#endif
	int barName = BAR_BATTLECOIN;
	int itemStatusFrame;
	// 아이템 떨구기
	// 우주에서는 둥실둥실 떠있음

	if (pObj->jumpFrame)
		TileCheckX2(pObj);
	TileCheckY2(pObj);

	pObj->mainFrame++;

	switch (pObj->def) {
	default:
		itemStatusFrame = FPS;
		break;
	case ITEM_BOX:
		itemStatusFrame = 1 * FPS;
		break;
	}
#ifdef GETITEMAUTO
	if (pObj->mainFrame > itemStatusFrame) {
		switch (drawHandle) {
		case MD_PLAY:
		case MD_BATTLE:
			switch (pObj->def) {
			case ITEM_GOLD:
#ifdef GOLDBARLEFTUP

				startX = xOffset + pObj->x;
				startY = STATUSWIN_Y + (rh - 4) * TSIZE - pObj->y - ry + OBJIMGGAP;
				//플레이어가 골드를 획득하는 것
				if (pObj->target < ENEMY) {
					//targetX = targetX2 = bar[barName].x + (float)(6 * _2X + ITEMICONSIZE * 1.5f / 2) * BAR_BATTLECOIN_ZOOM;
					//targetY = targetY2 = bar[barName].y - (float)(6 * _2X + ITEMICONSIZE * 1.5f / 2) * BAR_BATTLECOIN_ZOOM;

					targetX = targetX2 = xOffset + ao[NEUTRAL].x;
					targetY = targetY2 = STATUSWIN_Y + (rh - 4) * TSIZE - ao[NEUTRAL].y - ry + OBJIMGGAP + 4 * _2X + robin.castle * 4;

				}
				//적이 골드를 획득하는 것
				//그럴려면 어떤 코인의 적이 누군지
				else {
					targetX = targetX2 = xOffset + ao[pObj->target].nx;
					targetY = targetY2 = STATUSWIN_Y + (rh - 4) * TSIZE - ao[pObj->target].y - ry + OBJIMGGAP;

				}

				SetCurrencyMark(startX, startY, targetX, targetY, targetX2, targetY2, 8 * _2X * 2, 2 * _2X * 2, 8 * _2X * 2, 2 * _2X * 2, CURRENCYWAITINGFRAMEMAX, CURRENCYWAITINGFRAMEMAX, ICON_GOLD, 30, pObj->ax, CURRENCY_GOLD, pObj->zoom * CURRENCYICON_STARTSIZE, pObj->zoom * CURRENCYICON_ENDSIZE2, 0.3f, pObj->zoom * CURRENCYICON_ENDSIZE2, pObj->zoom * CURRENCYICON_STARTSIZE, -0.2f, barName);
#else
				targetX = DX / 2 - (GetNumDx(robin.gold, false, NUM_FONT_NORMAL, false) + 32 * _2X + 8 * _2X) / 2;
				targetY = DY - GNBHEIGHT - 8 * _2X;
#endif

				break;
			case ITEM_NETITEM:
				targetX = 8 * _2X;
				targetY = DY - (GNBHEIGHT - GNB_INIT_HEIGHT);

				break;
			case ITEM_BOX:
				//팝업창이 안열려있으면
				if (popUpCnt == 0) {

					if (pObj->mainFrame > 3 * FPS) {
						//여기서 처리

						//DropItem()은 ITEMOBJ부터 훑어서 "빈 슬롯"에 아이템을 배치하는데(Func_Item.cpp),
						//여기서는 ao[ITEMOBJ]를 하드코딩해서 읽고 있었다. 전투 중 떨어진 골드 코인이
						//ITEMOBJ 슬롯을 점유한 상태에서 상자가 떨어지면 상자는 ITEMOBJ+N에 생기고,
						//boxMark에는 상자가 아니라 코인 정보가 들어가서 GotoGacha()가
						//"invalid box type" 으로 조용히 실패했다. 지금 처리 중인 오브젝트를 그대로 쓴다.
						boxMark[0].type = pObj->def;
						boxMark[0].detail = pObj->etc;
						boxMark[0].grade = GRADE_NORMAL;

						GotoGacha();
					}
					else if (pObj->mainFrame == FPS / 2 && bar[BAR_BATTLECOIN].y < DY) {
						bar[BAR_BATTLECOIN].targetY = DY + 32 * _2X;

					}
					//memset(&ao[ITEMOBJ], 0, sizeof(OBJECT));
				}
				return;
				//장비가 떨어졌을 떄
			default:
				switch (pObj->def) {
				case ITEM_SWORD:
					//pObj->def 이 ITEM_SWORD 인 경우에는 
					targetX = 8 * _2X;
					targetY = STATUSWIN_Y - 10 * _2X + ITEMICONSIZE * 2;
					break;
				default:
					//pObj->def 가 ITEM_SWORD 가 아닌 경우				
					targetX = 8 * _2X;
					targetY = DY - (GNBHEIGHT - GNB_INIT_HEIGHT) - ITEMICONSIZE;
					break;
				}

				break;
			}
			SetItemMark(pObj->x - rx - pObj->cpx - 16 * _2X * 2, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (pObj->y - pObj->cpy - OBJIMGGAP) + 16 * _2X * 2, targetX, targetY, 8 * _2X / MOTIONDIV, pObj->ay * 2 / MOTIONDIV, 0, 1);
			pObj->active = false;
			if (pObj->def < ITEM_GEM) {
				attackDelay = FPS / 2;
				effect.color = COLOR_BLACK;
				//focusItem = GetObjFromPtr(pObj);
				itemFrame = INFOFRAME;

				if (option.voice == false) voiceType = VOICE_NOVOICE;
				else voiceType = VOICE_BIGMOUTH;
			}
			break;
		case MD_DEMO:
			switch (movie.index) {
				//동전이 다크나이트한테 날라가는 것
			case DEMO_OPENING_DARKKNIGHT:
				switch (robinmap) {
				case CASTLE3:
					for (i = ENEMY; i < NEUTRAL; i++) {
						if (ao[i].type == ENEMY_CASTLE_BOSS4) {
							//targetX = ao[i].x - rx;// -ao[i].cpx;// -16 * _2X * 2;
							//targetY = STATUSWIN_Y + (rh - 4) * TSIZE - ry - (ao[i].y - OBJIMGGAP);// +ao[i].cpy;// +16 * _2X * 2;
							break;
						}
					}
					ao[i].y -= 128 * _2X;
					GotoObj(&ao[i], pObj, 4 * _2X);
					ao[i].y += 128 * _2X;
					TileCheckX(pObj);
					TileCheckY(pObj);
					break;
				}

				break;
			}
			break;
		}
	}
#endif
}

void CloakingMove(OBJECT* pObj)
{
	pObj->mainFrame = (pObj->mainFrame + 1) % 120;

	if (pObj->mainFrame < 48) {
		mapInfoArray[mapInfoOff + (pObj->y / TSIZE + 1) * rw + pObj->x / TSIZE - 1] = TILE_DOWN;
		mapInfoArray[mapInfoOff + (pObj->y / TSIZE + 1) * rw + pObj->x / TSIZE] = TILE_DOWN;
	}
	else {
		mapInfoArray[mapInfoOff + (pObj->y / TSIZE + 1) * rw + pObj->x / TSIZE - 1] = TILE_VOID;
		mapInfoArray[mapInfoOff + (pObj->y / TSIZE + 1) * rw + pObj->x / TSIZE] = TILE_VOID;
	}
}

void WarpMove(OBJECT* pObj)
{
	int i;
	unsigned char type;
	int doorY = 256 * _2X;
	OBJECT* pPlayer = &ao[PLAYER];

	if (dontWarp == true || robin.bossRoom == true || isDemo == true)
		return;

	//인터랙티브 전투 튜토리얼 중(SEBASTIAN~BOSS)에는 실전투(MD_PLAY)로 넘어가면 isDemo가 false가 되어
	//이 가드를 통과해버린다. 튜토리얼 동안 히어로가 고정된 로비 좌표에 서 있는데, 그 좌표가 실제
	//워프 도어 오브젝트와 겹치면 매 프레임 ObjCrash가 true가 되어 loadedMap=-1 + ao[ENEMY] memset이
	//반복 실행되면서 "방 세팅이 계속 새로 되고 전투가 리셋되는" 증상이 나타난다. 튜토리얼이 끝날
	//때까지(DEMO_TUTORIAL_END) 이 방에서는 워프를 완전히 막는다.
	if (robinmap == MAP_DIORAMA_TOLEM && !robin.demoSeen[DEMO_TUTORIAL_END])
		return;


	//if (robin.bossRoom == false && (pPlayer->y < 1 || pPlayer->y > ((rh - 4) * TSIZE - 1)))
	//	goto SETROOM;

	//여기서 이동시 데모신으로 연결되는지, 아니면 페이드효과를 줄지, 아니면 못가게 할지, 아니면 그냥 갈지를 체크
	if (ObjCrash(pPlayer, pObj) && robin.bossRoom == false) {
		switch (pObj->status) {
		case 0:	//부딪히면 이동하는 워프
			//일반 모드면
			fadeFrame = 0;
			loadedMap = -1;
			focus = PLAYER;
			pPlayer->playerRun = false;
			pPlayer->dx = 0;
			pPlayer->flamer = null;
			skillInfoFrame = 0;
			skillUsed = 0;
			buffItemUsed = 0;
			effect.color = false;
			buffItemFrame = 0;
			GetTile(pPlayer);

			//keyHandle = MK_RAID;
			arenaFloorTime = 0;
			memset(&ao[ENEMY], 0, sizeof(OBJECT) * (NEUTRAL - ENEMY));

			if (tipIndex == -1 && onceAnnounced == true)
				onceAnnounced = false;

			//if (keyHandle == MK_RAID)
			//	SetEnemyUser();

			//마지막 스테이지라면 다시 처음으로 보내준다.
			//보스전은 선택해서 들어가는것이니까!
			if (robin.room == TOTALROOM - 1) {
				robin.room = 0;
				/*
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
					SetBossObj();
				}
				*/
			}
			//마지막 스테이지가 아니면
			else {
				robin.room++;
				if (robin.stage == robin.maxStage[robin.stage]) {
					if (robin.room > robin.maxRoom[robin.stage])
						robin.maxRoom[robin.stage] = robin.room;
				}
			}

			oldMap = robinmap;

			robinmap = MAP_DIORAMA_TOLEM + castleOrder[robin.castle];

			pPlayer->x = pObj->str + (pPlayer->x - pObj->x);
			pPlayer->y = pObj->def + (pPlayer->y - pObj->y);

			focus = PLAYER;
			GetTile(pPlayer);

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
			turnPosition = HERE;

			for (i = 0; i < TOTALOBJECT; i++) {
				ao[i].turn = 0;
				ao[i].turnPosition = HERE;
			}

			/*
			for (i = NEUTRAL; i < ITEMOBJ; i++) {
				if (ao[i].type == OBJ_DOOR) {
					doorY = ao[i].y + 32 * _2X;
					ao[i].status = OPENED;
					MoveObj(&ao[i]);
					break;
				}
			}

			for (i = PLAYER; i < PLAYER + TOTALPLAYER; i++) {
				ao[i].x = LOBBYPOSITION_X;
				ao[i].y = doorY + TSIZE;
				//ao[i].y = (rh - 6) * TSIZE;
				ao[i].playerRun = false;
				ao[i].dx = 0;
				ao[i].flamer = null;
				GetTile(&ao[i]);
				//MoveObj(&ao[i]);
			}
			*/

			memset(&robin.enemyObj, 0, sizeof(robin.enemyObj));
			memset(&ao[ENEMY], 0, sizeof(robin.enemyObj));

			if (touch) {
				touchMode = TOUCH_PLAY;
				touchModeOld = null;
				touchIndex = 0;
				swipeIndex = 0;
			}

			if (tutorialMode == true) {
				switch (arenaFloor) {
				case 2:
					tutorialStep = TUTORIAL_HERO;
					break;
				case 3:
					tutorialStep = TUTORIAL_SOLDIER;
					break;
				}
				popUpFrame = 0;
			}

			attackSequence = ATTACKSEQUENCE_READY;

			crewInitializeFrame = 1;
			for (i = 0; i < TOTALCONTROLMARK; i++)
				controlerSpread[i] = true;

			robin.curWaveIdx = 0;

			SaveGame();

			//if (pObj->cx == 17 * _2X) {
			//	if ((pObj->x % TSIZE == TSIZE - 1 && pPlayer->dirF == RIGHT) || (pObj->x % TSIZE == 0 && pPlayer->dirF == LEFT))
			//		goto SETROOM;
			//}
			//else {
			//	if ((pObj->y % TSIZE == TSIZE - 1 && pPlayer->dirY == DOWN) || (pObj->y % TSIZE == 0 && pPlayer->dirY == UP && (pPlayer->inTile != GROUND || pPlayer->dy >= TSIZE)))
			//		goto SETROOM;
			//}

			break;
		case 1:
		case 2:
		case 3:
			//2키를 누르면 실내로 들어가는 워프(워프 후 주인공 LEFT)
			if (key_released == false && systemKey == AVK_2 && fadeFrame == 0) {

				//ReleaseCore();
				PlayRelease(pPlayer);

				if (pPlayer->playerRun == true) {
					pPlayer->playerRun = false;
					pPlayer->dx = 0;
				}

				if (pObj->status == 1)
					pPlayer->dirF = LEFT;
				else if (pObj->status == 2)
					pPlayer->dirF = RIGHT;

				pPlayer->attack = false;
#ifdef ONEHEARTONEATTACK
				pPlayer->turnPosition = COMING;
#ifndef WARIGARI
				if (autoPlay == true && drawHandle == MD_PLAY) {
					BoxOpen();

				}
#endif
#endif
				zoomFrame = 5;
				warpFrame = 6;
				keyHandle = NULL;

				goto SETROOM;
			}
			break;
		case 4:
			//실내에서 밖으로 나오는 워프
			if (pObj->cx == TSIZE + 1 * _2X) {
				if ((pObj->x % TSIZE == TSIZE - 1 * _2X && pPlayer->dirF == RIGHT) || (pObj->x % TSIZE == 0 && pPlayer->dirF == LEFT)) {
					//ReleaseCore();
					PlayRelease(pObj);

					if (pPlayer->playerRun == true) {
						pPlayer->playerRun = false;
						pPlayer->dx = 0;
					}

					pPlayer->attack = false;
#ifdef ONEHEARTONEATTACK
					pPlayer->turnPosition = COMING;
#ifndef WARIGARI
					if (autoPlay == true && drawHandle == MD_PLAY) {
						BoxOpen();

					}
#endif
#endif
					zoomFrame = 4;
					warpFrame = 5;
					keyHandle = NULL;

					goto SETROOM;
				}
			}
			break;
		}
	}

	return;

SETROOM:
	fadeFrame = 0;
	robinmap = pObj->hp;
	pPlayer->x = pObj->str + (pPlayer->x - pObj->x);
	pPlayer->y = pObj->def + (pPlayer->y - pObj->y);

	focus = PLAYER;
	GetTile(pPlayer);

	SetRoom();

	if (pPlayer->hp == 0)
		pPlayer->dead = true;

	if (pPlayer->dirY == DOWN && pPlayer->y < TSIZE * 3 && TileCrash(pPlayer)) {
		pPlayer->y -= 8 * _2X;
		pPlayer->y += ClearGap(pPlayer, 1 * _2X);
	}
}

void LeverMove(OBJECT* pObj)
{
	if (pObj->status) {
		pObj->cx = 0;
		pObj->motion++;

		if (pObj->motion == OBJ_LEVER5) {
			pObj->moveHandler = NULL;

			SetRoom_Neutral();
		}
	}
}


void BoxMove(OBJECT* pObj)
{
	if (curtainFrame > 0 || infoFrame > 0 || arenaFrame > 0 || areaFrame > 0)
		return;
	if (GetObjFromPtr(pObj) == ITEMBOX) {
		switch (pObj->status) {
		case BOXSTATUS_APPEAR:
			pObj->motion = OBJ_BOX0;


			if (pObj->attackedFrame) {
				pObj->y = pObj->ny - jumpFullFrame[JUMPFULLFRAME - pObj->attackedFrame];
			}
			else {
				pObj->y += FREEFALL * 3 / 2;
				if (pObj->y > BOXPOSITION_Y) {
					pObj->y = BOXPOSITION_Y;
					pObj->attackedFrame = JUMPFULLFRAME + 1;
					PlayMusic(M_KUNG);
				}
			}

			if (pObj->attackedFrame == 1) {
				pObj->status = BOXSTATUS_CLOSED;
				pObj->frame = 0;
				JoyStickRelease();
			}
			break;
		case BOXSTATUS_CLOSED:
			pObj->motion = OBJ_BOX0 + boxNeutralAnimation[((pObj->frame / (MOTIONDIV * 2 * 2)) % 4)];
			break;
		case BOXSTATUS_OPENING:
			pObj->motion = Min(OBJ_BOX5, OBJ_BOX0 + pObj->frame / 2 / MOTIONDIV);
			if (pObj->motion == OBJ_BOX5 && pObj->frame == 2 * (OBJ_BOX5 - OBJ_BOX0 + 1))
				OpenBox(pObj);
			break;
		case BOXSTATUS_OPENED:
			pObj->motion = OBJ_BOX6;
			break;
		case BOXSTATUS_CLOSING:
			pObj->motion = OBJ_BOX5 - pObj->frame / (MOTIONDIV * 2);
			break;
		case BOXSTATUS_EMPTY:
			pObj->motion = OBJ_BOX6;
			break;
		case BOXSTATUS_SHOWGOLD:
			pObj->motion = OBJ_BOX6;
			break;
		}
	}
	else {
		switch (pObj->status) {
		case BOXSTATUS_APPEAR:
		case BOXSTATUS_CLOSED:
			pObj->motion = OBJ_BOX0 + boxNeutralAnimation[((pObj->frame / (MOTIONDIV * 2 * 2)) % 4)];
			break;
		case BOXSTATUS_OPENING:
			pObj->motion = Min(OBJ_BOX5, OBJ_BOX0 + pObj->frame / 2 / MOTIONDIV);
			if (pObj->motion == OBJ_BOX5 && pObj->frame == 2 * (OBJ_BOX5 - OBJ_BOX0 + 1)) {
				OpenBox(pObj);
				SetPopUp(POPUPTYPE_GAMEOVER, DX / 2, POPUPPOSITION_Y, POPUPWINDOWSIZE_X, POPUPWINDOWSIZE_Y, false, false, false,
					false, false, false, false, false,
					false, false, false, false, false,
					false, false, false, false, false);
				gameOverFrame = 0;
			}
			break;
		case BOXSTATUS_OPENED:
			pObj->motion = OBJ_BOX6;
			break;
		case BOXSTATUS_CLOSING:
			pObj->motion = OBJ_BOX5 - pObj->frame / (MOTIONDIV * 2);
			break;
		case BOXSTATUS_EMPTY:
			pObj->motion = OBJ_BOX6;
			break;
		case BOXSTATUS_SHOWGOLD:
			pObj->motion = OBJ_BOX6;
			break;
		}
	}

	pObj->frame++;

}

void CarpetMove(OBJECT* pObj)
{
	OBJECT* pPlayer = &ao[0];

	switch (pObj->status) {
	case 0:
		//기본상태 : 제자리에 떠서 위아래 한두도트씩 흔들거림.
		if (pObj->mainFrame % 4 == 0 && Random(3) == 0) {
			if (pObj->jumpFrame == JUMPFRAME - 1) {
				pObj->jumpFrame--;
				pObj->dy = -1 * _2X;
			}
			else if (pObj->jumpFrame == 0) {
				pObj->jumpFrame++;
				pObj->dy = 1 * _2X;
			}
			else {
				pObj->dy = Random(3) * _2X - 1 * _2X;
				pObj->jumpFrame += pObj->dy;
			}
		}
		else
			pObj->dy = 0;

		pObj->dx = 0;
		pObj->motion = OBJ_CARPET0 + pObj->mainFrame / 3 % 5;
		break;
	case 1:
		//주인공이 타고있는 상태 : 올라타고 있으면 주인공 얼굴방향으로 천천히 상승 전진하고, 아래키를 누르면 일정량 하강한다.
		pObj->jumpFrame = Min(2, pObj->jumpFrame + 1);
		pObj->dx = Max(-4, Min(4, pObj->dx + DIR(pPlayer->dirF) * 2)) * _2X;
		pObj->dy = -pObj->jumpFrame * _2X;
		pObj->motion = OBJ_CARPET0 + pObj->mainFrame % 5;
		break;
	case 2:
		//주인공이 떨어져서 올라가는 상태 : 처음 세프레임은 하강한 후 점점 상승하며, 12프레임이 지나면 투명해지기 시작하여 20프레임째에 없어진다.
		pObj->jumpFrame = Min(JUMPFRAME - 1, pObj->jumpFrame + 1);
		pObj->dy = -pObj->jumpFrame * _2X;
		pObj->motion = OBJ_CARPET0 + pObj->mainFrame / 2 % 5;

		if (pObj->dx > 0)
			pObj->dx -= 1 * _2X;
		else if (pObj->dx < 0)
			pObj->dx += 1 * _2X;

		if (pObj->attackFrame == 0 && pObj->y < pPlayer->y && pObj->jumpFrame == JUMPFRAME - 1) {
			pObj->cx = 0;
			pObj->attackFrame = 1;
		}
		break;
	}

	pObj->dirX = (pObj->dx < 0) ? LEFT : RIGHT;
	pObj->dirY = (pObj->dy < 0) ? UP : DOWN;

	//카페트가 타일과 충돌했다면
	pObj->x += pObj->dx;

	if (TileCrash(pObj) > 1) {
		pObj->x -= pObj->dx;
		//pObj->dx = ClearGap(pObj, 0);
		pObj->dx = 0;
	}
	else
		pObj->x -= pObj->dx;

	pObj->y += pObj->dy;

	if (TileCrash(pObj) > 1) {
		pObj->y -= pObj->dy;
		pObj->dy = ClearGap(pObj, 1);
	}
	else
		pObj->y -= pObj->dy;

	//주인공과의 연산
	pObj->y -= 1 * _2X;

	if (pObj->active == true && ObjCrash(pObj, pPlayer)) {
		if (pObj->onCarpet == 0) {
			pObj->onCarpet = GetObjFromPtr(pObj);
			pObj->status = 1;
			pObj->mainFrame = 0;
		}

		pPlayer->x += pObj->dx;

		if (TileCrash(pPlayer)) {
			pPlayer->x -= pObj->dx;
			pPlayer->x += ClearGap(pPlayer, 0);
			pObj->y += 1 * _2X;

			if (ObjCrash(pObj, pPlayer))
				pObj->x -= pObj->dx;

			pObj->y -= 1 * _2X;
		}

		pPlayer->y += pObj->dy;

		if (TileCrash(pPlayer)) {
			pPlayer->y -= pObj->dy;
			pObj->dy = ClearGap(pPlayer, 1);
			pPlayer->y += pObj->dy;
			//pObj->y +=  1 *_2X;

			//if (ObjCrash(pObj, pPlayer))
			//	pObj->y -= pObj->dy;

			//pObj->y -=  1 *_2X;
		}

		if (pPlayer->status == FALL && pPlayer->y + pPlayer->cy < pPlayer->y)
			pPlayer->status = WALK;
	}
	else if (pObj->onCarpet) {
		pObj->onCarpet = 0;
		pObj->status = 2;
		pObj->mainFrame = 0;
	}

	pObj->y += 1 * _2X;

	//카페트가 이동
	pObj->x += pObj->dx;
	pObj->y += pObj->dy;

	if (pObj->attackFrame) {
		pObj->attackFrame++;

		if (pObj->attackFrame == 16) {
			pObj->attackFrame = 0;
			pObj->mainFrame = 0;
			pObj->jumpFrame = 2;
			pObj->status = 0;
			pObj->x = pObj->str;
			pObj->y = pObj->def;
			pObj->cx = 38;
		}
	}

	pObj->mainFrame++;
}

void RobinTrapMove(OBJECT* pObj)
{
	pObj->motion = OBJ_ROBINWIND0 + pObj->mainFrame % 8;
	pObj->mainFrame++;
}

void DianaTrapMove(OBJECT* pObj)
{
	if (pObj->status == 1) {
		//발판 작동시
		if (dianaTrapFrame == 0)
			dianaTrapFrame = (GetObjFromPtr(pObj) - NEUTRAL) * 10;
		else
			dianaTrapFrame++;

		if (pObj->motion < OBJ_STAMP2)
			pObj->motion++;

		if (pObj->mainFrame == 7) {
			int i;

			for (i = NEUTRAL; i < ITEMOBJ; i++) {
				if (ao[i].type == OBJ_DIANASTONE) {
					ao[i].motion = OBJ_BOARD0 - 1;
					ao[i].active = true;
					mapInfoArray[mapInfoOff + (ao[i].y / TSIZE + 1) * rw + ao[i].x / TSIZE - 1] = TILE_DOWN;
					mapInfoArray[mapInfoOff + (ao[i].y / TSIZE + 1) * rw + ao[i].x / TSIZE] = TILE_DOWN;
				}
			}
		}
		else if (pObj->mainFrame == 8) {
			pObj->mainFrame = 0;
			pObj->status = 2;
			dianaTrapFrame = 0;
		}
	}
	else if (pObj->status == 2)
		//발판 작동 후
		pObj->motion = OBJ_STAMP3 + pObj->mainFrame % 4;

	if (pObj->status)
		pObj->mainFrame++;
}

void MaxxTrapMove(OBJECT* pObj)
{
	if (pObj->status == 0) {
		if (boomerangAway[PLAYER] && AttackCrash(&ao[boomerangAway[PLAYER]], pObj)) {
			pObj->status = 1;
		}
	}
	else {
		if (pObj->motion == OBJ_MAXXSTONE4)
			pObj->active = false;
		else
			pObj->motion++;
	}
}

void SunBlockMove(OBJECT* pObj)
{
	if (pObj->status == 0) {
		//맥스는 부메랑과 체크
		OBJECT* pAttack = (pObj->type == MAXX) ? &ao[boomerangAway[PLAYER]] : &ao[PLAYER];

		if (pObj->canBreak && AttackCrash(pAttack, pObj)) {
			pObj->status = 1;
			pObj->block = false;
			//EffectSound(M_BANG);
			PlayMusic(M_BANG);
		}
	}
	else {
		if (pObj->motion == OBJ_SUNBLOCK4)
			pObj->active = false;
		else
			pObj->motion++;
	}
}

void BreakStoneMove(OBJECT* pObj)
{
	int i, TileX = ((pObj->x - 1) / (16 * _2X)), TileY = ((pObj->y - 17 * _2X) / (16 * _2X));

	if (pObj->status == 0) {
		//맥스는 부메랑과 체크
		OBJECT* pAttack = (pObj->type == MAXX) ? &ao[boomerangAway[PLAYER]] : &ao[PLAYER];

		if (pAttack->attack == ATTACK_DOWN && AttackCrash(pAttack, pObj)) {
			pObj->status = 1;
			pObj->block = false;

			//타일정보 변경
			for (i = TileY; i < TileY + 2; i++) {
				mapInfoArray[mapInfoOff + i * rw + TileX] = 0;
				mapInfoArray[mapInfoOff + i * rw + TileX + 1] = 0;
			}
		}
	}
	else {
		if (pObj->motion == OBJ_BREAK4)
			pObj->active = false;
		else
			pObj->motion++;
	}
}

void DarkStoneMove(OBJECT* pObj)
{
	if (pObj->status)
		pObj->motion = OBJ_DARK6 + pObj->mainFrame % 6;
	else
		pObj->motion = OBJ_DARK0 + pObj->mainFrame / 3 % 6;

	pObj->mainFrame++;
}

void DemoDarkMove(OBJECT* pObj)
{
	int i;

	for (i = PLAYER; i < TOTALCHAR; i++) {
		if (ao[i].cmf == DIANA)
			break;
	}

	if (pObj->etc != 0) {
		pObj->motion = OBJ_DARK6 + pObj->mainFrame % 6;	//6프레임일때(이미지나오면수정)
		pObj->x += pObj->dx;
		pObj->y += pObj->dy;
	}

	switch (pObj->etc) {
	case 1:				//제자리에서 반짝이기 시작
		pObj->dx = pObj->dy = 0;
		break;
	case 2:				//반짝이면서 DIANA에게 움직임
		pObj->motion = OBJ_DARK6 + pObj->mainFrame % 6;
		if (GetDistance(&ao[i], pObj) >= 10) {
			ao[i].y -= 10 * _2X;
			GotoObj(&ao[i], pObj, 4 * _2X);		//이미지 크기에 따라서 Speed조절 바람.
			ao[i].y += 10 * _2X;
		}
		else {
			pObj->dx = 0;
			pObj->dy = 0;
		}
		break;
	case 3:				//반짝이면서 DIANA에게서 나옴
		pObj->motion = OBJ_DARK6 + pObj->mainFrame % 6;
		pObj->dy = -4 * _2X;
		break;
	}

	pObj->mainFrame++;
}

void BubbleMove(OBJECT* pObj)
{
	int i;

	switch (pObj->mainFrame % 30) {
	case 6:
		for (i = NEUTRAL; i < ITEMOBJ; i++) {
			OBJECT* pSub = &ao[i];

			if (pSub->active == false) {
				pSub->active = true;
				pSub->dirY = pObj->etc;
				pSub->type = OBJ_BUBBLE;
				pSub->motion = BUBBLE_UP0 + pSub->dirY * 6;
				pSub->x = pObj->x + 1 * _2X;
				pSub->y = pObj->y + DIR(pObj->etc) * 32 * _2X;
				pSub->cx = 28 * _2X;
				pSub->cy = 32 * _2X;
				pSub->cpx = -14 * _2X;
				pSub->cpy = (pSub->dirY == UP) ? -0 * _2X : -32 * _2X;
				pSub->drawHandler = NEUTRALDRAW;
				pSub->moveHandler = BUBBLEBOBBLEMOVE;
				break;
			}
		}
	case 5:
		pObj->drawHandler = NEUTRALDRAW;
	case 7:
	case 8:
	case 9:
		pObj->motion = OBJ_BUBBLE_UP0 + pObj->etc * 5 + (pObj->mainFrame % 30) - 5;
		break;
	case 10:
		pObj->drawHandler = NULL;
		break;
	}

	pObj->mainFrame++;
}

void BubbleBobbleMove(OBJECT* pObj)
{
	OBJECT* player = &ao[PLAYER];

	pObj->mainFrame++;
	pObj->dy = DIR(pObj->dirY) * 16 * _2X;
	pObj->y += pObj->dy;

	if (ObjCrash(pObj, player)) {
		player->dx /= 2;
		player->dy /= 2;

		player->y += pObj->dy;
		player->dirY = pObj->dirY;

		if (TileCrash(player)) {
			player->y -= pObj->dy;
			player->y += ClearGap(player, 1);
		}
	}

	pObj->motion = BUBBLE_UP0 + pObj->dirY * 6 + (pObj->mainFrame % 6);

	if (TileCrash(pObj) || mapInfoArray[mapInfoOff + ((pObj->y + DIR(pObj->dirY) * 32 * _2X) >> 5) * rw + (pObj->x >> 5)] != TILE_WATER)
		pObj->active = false;
}

void MagmaMove(OBJECT* pObj)
{
	int i, j = pObj->jumpFrame;

	switch (pObj->status) {
	case 0:
		pObj->mainFrame++;

		if (pObj->mainFrame == 30) {
			pObj->mainFrame = 0;
			pObj->status = 1;
		}
		break;
	case 1:
		//상승중
		pObj->jumpFrame += pObj->mainFrame;

		if (pObj->jumpFrame >= magmaArray[pObj->etc]) {
			pObj->jumpFrame = magmaArray[pObj->etc];
			pObj->mainFrame = 0;
			pObj->status = 2;
		}
		else {
			pObj->mainFrame++;
		}
		break;
	case 2:
		//상승후 대기중
		pObj->mainFrame++;

		if (pObj->mainFrame == 2) {
			pObj->mainFrame = 0;
			pObj->status = 3;
		}
		break;
	case 3:
		//하강중
		pObj->jumpFrame -= pObj->mainFrame;

		if (pObj->jumpFrame <= 0) {
			pObj->jumpFrame = 0;
			pObj->mainFrame = 0;
			pObj->status = 0;
		}
		else {
			pObj->mainFrame++;
		}
		break;
	}

	pObj->cy = Max(0, pObj->jumpFrame - 1) * TSIZE;
	pObj->cpy = -pObj->cy;

	j -= pObj->jumpFrame;

	while (j) {
		//마그마블럭과의 충돌체크
		for (i = NEUTRAL; i < ITEMOBJ; i++) {
			//마그마 블럭과 충돌했다면
			if (ao[i].type == OBJ_MAGMABLOCK && ObjCrash(&ao[i], pObj)) {
				ao[i].etc = 3;
				ao[i].y -= 1 * _2X;

				//마그마 블럭 위에 플레이어가 있는지 없는지 체크한다.
				if (ObjCrash(&ao[i], &ao[PLAYER]))
					//플레이어가 발판위에 서있다면 이동시켜준다.
					ao[PLAYER].y += (j > 0 ? TSIZE : -TSIZE);

				ao[i].y += 1 * _2X;

				//블럭을 이동시킨다.
				if (j > 0) {
					ao[i].y += TSIZE;
					ao[i].dirY = DOWN;
					pObj->dirY = UP;
				}
				else {
					ao[i].y -= TSIZE;
					ao[i].dirY = UP;
					pObj->dirY = DOWN;
				}

				ao[i].y -= 1 * _2X;

				//이동된 마그마 블럭 위에 플레이어가 있는지 체크한다.
				if (ObjCrash(&ao[i], &ao[PLAYER])) {
					//플레이어가 있다면 발판 위로 위치시켜준다.
					if (j > 0) {
						ao[PLAYER].y += TSIZE;
						//ao[0].dirY = DOWN;
						//ao[i].dirY = UP;
					}
					else {
						ao[PLAYER].y -= TSIZE;
						//ao[0].dirY = UP;
						//ao[i].dirY = DOWN;
					}

					ao[PLAYER].dirY = DOWN;
					ao[i].dirY = UP;
				}

				ao[i].y++;
			}
		}

		//플레이어와의 충돌체크
		if (ObjCrash(&ao[PLAYER], pObj)) {
			if (pObj->block) {
				if (j > 0) {
					ao[PLAYER].y += TSIZE;
					//ao[0].dirY = DOWN;
					//pObj->dirY = UP;
				}
				else {
					ao[PLAYER].y -= TSIZE;
					//ao[0].dirY = UP;
					//pObj->dirY = DOWN;
				}

				ao[PLAYER].dirY = DOWN;
				pObj->dirY = UP;
				ao[PLAYER].y += ClearGap(pObj, 1);
			}
		}


		if (j < 0)
			j++;
		else
			j--;
	}
}

void MagmaBlockMove(OBJECT* pObj)
{
	int i;

	switch (pObj->etc) {
	case 0:
		pObj->motion++;

		if (pObj->motion == OBJ_MAGMASTONE3)
			pObj->etc = 1;
		break;
	case 1:
		pObj->x += pObj->dx;

		if (TileCrash(pObj) > 1)
			pObj->etc = 2;

		PressObjCheck(pObj);

		TileCheckY2(pObj);
		break;
	case 2:
		pObj->motion--;

		if (pObj->motion == OBJ_MAGMASTONE0) {
			pObj->x = pObj->str;
			pObj->y = pObj->def;
			pObj->etc = 0;
		}
		break;
	case 3:
		pObj->y++;

		for (i = NEUTRAL; i < ITEMOBJ; i++) {
			//마그마 블럭과 충돌했다면
			if (ao[i].type == OBJ_MAGMA && ObjCrash(&ao[i], pObj))
				break;
		}

		if (i == ITEMOBJ)
			pObj->etc = 2;
		break;
	}
}

void BridgeMove(OBJECT* pObj)
{
	if (pObj->status) {
		pObj->mainFrame++;

		if (pObj->mainFrame % 3 == 0)
			effect.shake = 5;

		if (drawHandle == MD_PLAY || drawHandle == MD_BATTLE || drawHandle == MD_RAID || drawHandle == MD_BOSSRAID) {
			int tempX;

			if (mapInfoArray[mapInfoOff + 16 * rw + (pObj->x + TSIZE * 5) / TSIZE] == TILE_BLOCK)
				mapInfoArray[mapInfoOff + 16 * rw + (pObj->x + TSIZE * 5) / TSIZE] = TILE_VOID;

			tempX = (pObj->x + TSIZE * 5 - TSIZE * pObj->mainFrame / 4) / TSIZE;
			// 총 6번에 걸쳐서 양쪽의 타일을 하나씩 제거한다.
			if (pObj->mainFrame % 4 == 0 && mapInfoArray[mapInfoOff + 16 * rw + tempX] == TILE_BLOCK && mapInfoArray[mapInfoOff + (16 + 1) * rw + tempX] == TILE_VOID) {
				mapInfoArray[mapInfoOff + 16 * rw + tempX] = TILE_VOID;
				PlayMusic(M_OPENDOOR);
			}

			tempX += pObj->mainFrame / 2;
			if (pObj->mainFrame % 4 == 0 && mapInfoArray[mapInfoOff + 16 * rw + tempX] == TILE_BLOCK && mapInfoArray[mapInfoOff + (16 + 1) * rw + tempX] == TILE_VOID)
				mapInfoArray[mapInfoOff + 16 * rw + tempX] = TILE_VOID;
		}

		if (pObj->mainFrame == 30) {
			pObj->active = false;
		}
	}
}

void StalactiteMove(OBJECT* pObj)
{
	OBJECT* pPlayer = &ao[0];
	int gapY;

	switch (pObj->etc) {
	case 0:
		//매달려 있는 상태
		pObj->attr = 1;
		gapY = pPlayer->y - PxlDown(pObj);

		GetTile(pObj);
		//주인공이 종유석보다 아래에 있고, 아래까지 타일이 걸리는게 없는 경우, X축으로 거리가 40 이내가 되면 떨어진다.
		if (Abs(pObj->x - pPlayer->x) < 50 * _2X && gapY > 0 && GetObjHeight(pObj) >= gapY)
			pObj->etc = 1;
		break;
	case 1:
		//낙하중인 상태
		pObj->status = FALL;
		pObj->jumpFrame++;

		TileCheckY2(pObj);
		break;
	case 2:
		//낙하 후 퐁당
		pObj->attr = 0;
		pObj->motion++;

		if (pObj->motion > BG9_STALACTITE7) {
			pObj->etc = 3;
			pObj->drawHandler = NULL;
			pObj->mainFrame = 0;
		}
		break;
	case 3:
		//사라진 후 대기
		pObj->mainFrame++;

		if (pObj->mainFrame > 200) {
			pObj->etc = 4;
			pObj->drawHandler = NEUTRALDRAW;
			pObj->mainFrame = 0;
			pObj->x = pObj->str;
			pObj->y = pObj->def;
			pObj->cx = 20 * _2X;
			pObj->motion = BG9_STALACTITE0;
		}
		break;
	case 4:
		//생성
		pObj->attr = 1;
		pObj->mainFrame++;

		if (pObj->mainFrame > 200)
			pObj->etc = 0;
		break;
	}
}

void SpikeMove(OBJECT* pObj)
{
	OBJECT* pPlayer = &ao[0];
	int gapY;

	switch (pObj->etc) {
	case 0:
		//매달려 있는 상태
		gapY = pPlayer->y - PxlDown(pObj);

		GetTile(pObj);

		//주인공이 고드름보다 아래에 있고, 아래까지 타일이 걸리는게 없는 경우, X축으로 거리가 40 이내가 되면 떨어진다.
		if (Abs(pObj->x - pPlayer->x) < 60 * _2X && gapY > 0 && GetObjHeight(pObj) >= gapY) {
			pObj->etc = 1;
			pObj->cx = 20 * _2X;
		}
		break;
	case 1:
		//낙하중인 상태
		pObj->attr = 1;
		pObj->status = FALL;
		pObj->jumpFrame++;

		TileCheckY2(pObj);
		break;
	case 2:
		//부서지는 상태
		pObj->motion++;

		if (pObj->motion > OBJ_SPIKE5) {
			pObj->etc = 3;
			pObj->drawHandler = NULL;
			pObj->mainFrame = 0;
			pObj->attr = 0;
			pObj->cx = 0;
		}
		break;
	case 3:
		//사라진 후 대기
		pObj->mainFrame++;

		if (pObj->mainFrame > 300) {
			pObj->etc = 4;
			pObj->drawHandler = NEUTRALDRAW;
			pObj->mainFrame = 0;
			pObj->x = pObj->str;
			pObj->y = pObj->def;
			pObj->attack = false;
			pObj->motion = OBJ_SPIKE0;
		}
		break;
	case 4:
		//생성
		pObj->attr = 1;
		pObj->mainFrame++;

		if (pObj->mainFrame > 32)
			pObj->etc = 0;
		break;
	}
}

void MagnetMove(OBJECT* pObj)
{
	int i, type = pObj->magnet / 100;
	int smallV, largeV;
	int obj = GetObjFromPtr(pObj);
	OBJECT* pPlayer = &ao[PLAYER];

	//현재 자석오브젝트와 붙지 않은경우
	if (pObj->magnet % 100 != obj) {
		//번개의 상을 발동시키지 않은 경우엔 붙지 않는다.
		if (!pObj->canMagnet)
			return;

		pObj->mainFrame = 0;
		pObj->attackFrame = 0;

		//수직선상으로 일치한 경우
		if (Abs(pPlayer->x - pObj->x) <= 8) {
			//경계값 입력
			if (pPlayer->y > pObj->y) {
				//주인공이 자석보다 아래쪽에 있다면
				smallV = PxlDown(pObj);
				largeV = PxlUp(pPlayer);
			}
			else {
				//주인공이 자석보다 위쪽에 있다면
				smallV = PxlDown(pPlayer);
				largeV = PxlUp(pObj);
			}

			//주인공과 자석 사이에 장애물이 없는지 체크한다.
			for (i = smallV / TSIZE; i < largeV / TSIZE; i++)
				if (mapInfoArray[mapInfoOff + i * rw + (pObj->x - (TSIZE / 2)) / TSIZE] != TILE_VOID && mapInfoArray[mapInfoOff + i * rw + (pObj->x + (TSIZE / 2)) / TSIZE] != TILE_VOID)
					goto NEXT;

			//장애물이 없다면 자석에 붙여준다.
			pObj->status = 1;
			pObj->magnet = obj;
			pObj->jumpFrame = pObj->hp = pPlayer->dx;
			pObj->mainFrame = Abs(pPlayer->dy);

			return;
		}

	NEXT:
		//수평선 상으로 일치한 경우
		if (Abs(pPlayer->y - 12 * _2X - pObj->y) <= 10 * _2X) {
			//경계값 입력
			if (pPlayer->x > pObj->x) {
				//주인공이 자석보다 오른쪽에 있다면
				smallV = PxlRight(pObj);
				largeV = PxlLeft(pPlayer);
			}
			else {
				//주인공이 자석보다 왼쪽에 있다면
				smallV = PxlRight(pPlayer);
				largeV = PxlLeft(pObj);
			}

			//주인공과 자석 사이에 장애물이 없는지 체크한다.
			for (i = smallV / TSIZE; i < largeV / TSIZE; i++)
				if (mapInfoArray[mapInfoOff + (pObj->y - TSIZE / 2) / TSIZE * rw + i] != TILE_VOID && mapInfoArray[mapInfoOff + (pObj->y + (TSIZE / 2)) / TSIZE * rw + i] != TILE_VOID)
					return;

			pObj->status = 1;
			pObj->magnet = obj + 100;
			pObj->jumpFrame = pObj->hp = pPlayer->dy;
			pObj->mainFrame = Abs(pPlayer->dx);
		}
	}
	else {
		//자석에 붙지 않도록 해제한 경우
		if (!pPlayer->canMagnet) {
			pPlayer->magnet = 0;
			pPlayer->status = (pPlayer->dirY == UP) ? WALK : FALL;
			pPlayer->dirY = DOWN;
			pPlayer->jumpFrame = 0;
#ifdef AGI_MOVESPEED
			//pPlayer->dx = dx_walk[pPlayer->type] + (pPlayer->ps[PS_AGI] / 1000);

			pPlayer->pDx = GetSpeed(obj);
#else
			pPlayer->dx = DX_WALK;
#endif
			return;
		}

		//자석의 크기를 증가시킨다
		pObj->cpx -= 1 * _2X;
		pObj->cpy -= 1 * _2X;
		pObj->cx += 2 * _2X;
		pObj->cy += 2 * _2X;

		//플레이어가 자석에 달라붙어 있다면
		if (ObjCrash(pPlayer, pObj)) {
			pObj->mainFrame = 1;
			pPlayer->dx = 0;

			//자석 체크 한계범위를 넘어섰다면
			if ((type == 0 && Abs(pPlayer->x - pObj->x) > 8 * _2X) || (type == 1 && Abs(pPlayer->y - 12 * _2X - pObj->y) > 10 * _2X)) {
				pPlayer->magnet = 0;
				pPlayer->status = (pPlayer->dirY == UP) ? WALK : FALL;
				pPlayer->dirY = DOWN;
				pPlayer->jumpFrame = 0;
#ifdef AGI_MOVESPEED

				pPlayer->pDx = GetSpeed(obj);
#else
				pPlayer->dx = DX_WALK;
#endif
			}
		}

		if (type == 0) {
			smallV = (pPlayer->y > pObj->y) ? LEFT : RIGHT;

			if (pPlayer->status == MAGNET) {
				pObj->mainFrame = 1;
				pPlayer->dirY = smallV;
			}
			else {
				if (!pObj->mainFrame)
					pPlayer->dirY = smallV;

				pObj->mainFrame += (pPlayer->dirY == smallV) ? 1 : -1;
			}
		}
		else {
			smallV = (pPlayer->x > pObj->x) ? LEFT : RIGHT;
			if (pPlayer->status == MAGNET) {
				pObj->mainFrame = 1;
				pPlayer->dirX = smallV;
			}
			else {
				if (!pObj->mainFrame)
					pPlayer->dirX = smallV;

				pObj->mainFrame += (pPlayer->dirX == smallV) ? 1 : -1;
			}
		}

		pObj->mainFrame = Max(0, pObj->mainFrame);

		//자석의 크기를 원래대로 돌린다.
		pObj->cpx += 1 * _2X;
		pObj->cpy += 1 * _2X;
		pObj->cx -= 2 * _2X;
		pObj->cy -= 2 * _2X;

		pObj->attackFrame++;
	}
}

void SledMove(OBJECT* pObj)
{
	switch (pObj->etc) {
	case 0:
		pObj->dx = 0;
		pObj->dy = 0;
		break;
	case 1:
		//dx가 작을때는 천천히 가속하고, dx가 클때는 평소대로 가속
		if ((Abs(pObj->dx) < 3 * _2X && robin.playtime % 6 == 0) || (Abs(pObj->dx) >= 3 * _2X && robin.playtime % 3 == 0)) {
			if (pObj->dirX == LEFT)
				pObj->dx = Max(-15 * _2X, pObj->dx - 1 * _2X);
			else
				pObj->dx = Min(15 * _2X, pObj->dx + 1 * _2X);
		}

		break;
	case 2:
		pObj->x += pObj->dx;
		pObj->motion++;

		if (pObj->motion > OBJ_SLED4) {
			int i;

			for (i = NEUTRAL; i < ITEMOBJ; i++) {
				if (ao[i].active && ao[i].type == OBJ_ICEBREAK)
					break;
			}

			if (i != ITEMOBJ) {
				pObj->status = 0;
				pObj->jumpFrame = 0;
				pObj->dirY = DOWN;
				pObj->mainFrame = 0;
				pObj->cx = 48 * _2X;
				pObj->etc = 3;
				pObj->motion = OBJ_SLED0;
				pObj->x = pObj->str;
				pObj->y = pObj->def;
				pObj->dx = 0;
				pObj->dy = 0;
			}
			else
				pObj->active = false;
		}
		break;
	case 3:
		if (pObj->mainFrame == 32)
			pObj->etc = 0;

		pObj->mainFrame++;
		break;
	}

	if (pObj->etc < 2) {
		TileCheckX2(pObj);
		TileCheckY2(pObj);

		PressObjCheck(pObj);
	}
}

void IceBreakMove(OBJECT* pObj)
{
	if (pObj->status) {
		pObj->motion++;

		if (pObj->motion > OBJ_SLEDSTONE4)
			pObj->active = false;
	}
}

void InvisibleMove(OBJECT* pObj)
{
	if ((pObj->mainFrame < 6 && pObj->canBreak) || (pObj->y + 12 * _2X >= ao[PLAYER].y && ao[PLAYER].status == WALK && ObjCrash(pObj, &ao[PLAYER]))) {
		pObj->status = 1;
		pObj->motion = OBJ_INVISIBLE0 + pObj->mainFrame / 2 % 3;
	}
	else
		pObj->status = 0;

	pObj->mainFrame = (pObj->mainFrame + 1) % 90;
}

void GolemBlockMove(OBJECT* pObj)
{
	int obj = GetObjFromPtr(pObj);

	if (pObj->status) {
		pObj->motion++;

		if (pObj->motion > OBJ_GOLEMBLOCK4)
			pObj->active = false;
	}
	else {
		if (ao[raidPlayer].attack && AttackCrash(&ao[raidPlayer], pObj)) {
			pObj->status = 1;
			//EffectSound(M_BANG);
			PlayMusic(M_BANG);
			if (obj == raidPlayer || ao[obj].soldier == true || (obj >= BULLET && obj < ENEMY && (ao[obj].target == PLAYER || ao[ao[obj].target].soldier == true)))
				effect.shake = 5;
		}
	}
}

void BallMove(OBJECT* pObj)
{
	int i;
	OBJECT* pPlayer = &ao[PLAYER];

	pObj->motion = OBJ_BALL0 + pObj->frame % 4;

	//주인공의 공격과 충돌하였는지 체크한다.
	if (pObj->status == 0 && (AttackCrash(pPlayer, pObj) || (pObj->type == MAXX && boomerangAway[PLAYER] && AttackCrash(&ao[boomerangAway[PLAYER]], pObj)))) {
		//맞은 중간점과 공의 위치를 계산하여 공의 DX, DY를 변경해준다.
		int x = crX + crW / 2;
		int y = crY + crH / 2;

		if (x == pObj->x)
			pObj->dx = DIR(ao[PLAYER].dirF) * 16 * _2X;
		else
			pObj->dx = (x < pObj->x) ? 16 * _2X : -16 * _2X;

		pObj->dy = (y < pObj->y) ? 16 * _2X : -16 * _2X;

		pObj->dx = pObj->dx * 4 / (4 + Abs(x - pObj->x));
		pObj->dy = pObj->dy * (4 + Abs(y - pObj->y)) / 11;

		pObj->status = 1;
		pObj->frame = 0;
	}

	if (pObj->status)
		pObj->dy++;

	pObj->x += pObj->dx;
	pObj->y += pObj->dy;

	for (i = NEUTRAL; i < ITEMOBJ; i++) {
		//공과 포수가 닿았다면
		if (ao[i].active && ao[i].type == OBJ_CATCHER && ObjCrash(pObj, &ao[i])) {
			//공을 없애주고 포수오브젝트 상태를 변경하고 볼블럭 상태비트를 체크한다.
			pObj->active = false;
			ao[i].status = 1;
			ao[i].cx = 0;

			//투수 오브젝트도 없애준다.
			for (i = NEUTRAL; i < ITEMOBJ; i++)
				if (ao[i].type == OBJ_PITCHER)
					ao[i].active = false;

			break;
		}
	}

	//몬스터와 충돌체크하여 공격한다.
	for (i = ENEMY; i < NEUTRAL; i++) {
		if (ao[i].active && !ao[i].dead && ao[i].type < NPC_CAPTAIN && ObjCrash(pObj, &ao[i])) {
			AttackObj(ATTACKTYPE_DARKBALL, i);
			pObj->active = false;
		}
	}

	//플레이어와 충돌체크하여 공격한다.
	//pObj->cpx = -1;
	//pObj->cpy = -1;
	//pObj->cx = 2;
	//pObj->cy = 2;

	if (pPlayer->active == true && pPlayer->dead == false && ObjCrash(pObj, pPlayer)) {
		AttackRobin(ATTACKTYPE_DARKBALL, raidPlayer);
		pObj->active = false;
	}

	pObj->cpx = -8 * _2X;
	pObj->cpy = -8 * _2X;
	pObj->cx = TSIZE;
	pObj->cy = TSIZE;

	pObj->y -= pObj->dy;

	//주인공이 친 상태에서 타일에 충돌하면 꺼준다.
	if (TileCrash(pObj)) {
		pObj->dx = -pObj->dx;
		pObj->x += pObj->dx;

		if (pObj->dx < 0)
			pObj->dx += 1 * _2X;
		else
			pObj->dx -= 1 * _2X;
	}

	pObj->y += pObj->dy;

	if (TileCrash(pObj)) {
		pObj->dy = -pObj->dy;
		pObj->y += pObj->dy;

		if (pObj->dy < 0)
			pObj->dy += 2 * _2X;
	}

	//화면 밖으로 나가면 꺼준다.
	if (pObj->frame >= 100)
		pObj->active = false;

	pObj->frame++;
}

void PitcherMove(OBJECT* pObj)
{
	int i;

	for (i = NEUTRAL; i < ITEMOBJ; i++) {
		if (ao[i].active && ao[i].type == OBJ_BALL)
			return;
	}

	if (pObj->frame % 8 == 0) {
		i = GetEmptyObject(NEUTRAL);
		AddObject(&ao[i], pObj, ADDOBJ_BALL);
		ao[i].type = OBJ_BALL;
	}

	pObj->frame++;
}

void BlackHoleMove(OBJECT* pObj)
{
	//주인공과의 거리를 계산
	int dist = Max(1 * _2X, GetDistance(&ao[PLAYER], pObj));
	int ratioX = Abs(pObj->x - ao[PLAYER].x) * 100 / (Abs(pObj->x - ao[PLAYER].x) + Abs(pObj->y - ao[PLAYER].y) + 1);
	int bhDx = 0;
	int bhDy = 0;

	pObj->motion = OBJ_BLACKHOLE0 + (frame / MOTIONDIV % 15);

	if (dist > 200 * _2X)
		return;

	pObj->frame++;

	if (dist >= 75 * _2X) {
		if ((pObj->frame + 1) % ((dist - 74 * _2X) * 2) == 0) {
			pObj->frame = 0;
			bhDx = RoundDiv(ratioX, 80) * _2X;
			bhDy = RoundDiv((100 - ratioX), 80) * _2X;
		}
		else
			return;
	}
	else {
		bhDx = RoundDiv((85 - dist) * ratioX, 3000) * _2X;
		bhDy = RoundDiv((85 - dist) * (100 - ratioX), 3000) * _2X;
	}

	if (bhDx) {
		if (ao[PLAYER].dx == 0)
			ao[PLAYER].dirX = (ao[PLAYER].x < pObj->x);

		if ((ao[PLAYER].x > pObj->x && ao[PLAYER].dirX == RIGHT) || (ao[PLAYER].x < pObj->x && ao[PLAYER].dirX == LEFT)) {
			ao[PLAYER].dx = ao[PLAYER].dx - bhDx;

			if (ao[PLAYER].dx < 0) {
				ao[PLAYER].dirX = 1 - ao[PLAYER].dirX;
				ao[PLAYER].dx = Abs(ao[PLAYER].dx);
			}
		}
		else
			ao[PLAYER].dx = Min(16 * _2X, ao[PLAYER].dx + bhDx);
	}

	if (bhDy) {
		if (ao[PLAYER].dy == 0)
			ao[PLAYER].dirY = (ao[PLAYER].y < pObj->y);

		if ((ao[PLAYER].y > pObj->y && ao[PLAYER].dirY == DOWN) || (ao[PLAYER].y < pObj->y && ao[PLAYER].dirY == UP)) {
			ao[PLAYER].dy = ao[PLAYER].dy - bhDy;

			if (ao[PLAYER].dx < 0) {
				ao[PLAYER].dirY = 1 - ao[PLAYER].dirY;
				ao[PLAYER].dy = Abs(ao[PLAYER].dy);
			}
		}
		else
			ao[PLAYER].dy = Min(16 * _2X, ao[PLAYER].dy + bhDy);
	}

	//dx, dy를 하향시켜준다
	ao[PLAYER].dx = Min(8 * _2X, ao[PLAYER].dx);
	ao[PLAYER].dy = Min(8 * _2X, ao[PLAYER].dy);

	//블랙홀 충돌시
	if (ObjCrash(pObj, &ao[PLAYER])) {
		//웜홀로 보내준다.
		fadeFrame = 0;
		robinmap = wormHoleArray[pObj->etc * 3] + 200;
		ao[PLAYER].x = wormHoleArray[pObj->etc * 3 + 1] * TSIZE;
		ao[PLAYER].y = wormHoleArray[pObj->etc * 3 + 2] * TSIZE + 12 * _2X;
		ao[PLAYER].dx = 0;
		ao[PLAYER].dy = 0;
		focus = PLAYER;
		GetTile(&ao[PLAYER]);

		SetRoom();
	}
}

void WormHoleMove(OBJECT* pObj)
{
	pObj->motion = OBJ_WORMHOLE0 + (frame % 3);
}

void ItemGotoBoxMove(OBJECT* pObj)
{
	if (pObj->status == 0 && (ObjCrash(pObj, &ao[ITEMBOX]))) {
		pObj->frame = 0;
		pObj->status = 1;
	}

	if (pObj->status == 1) {
		//pObj->motion = PO_C37_SHOT0 + pObj->frame;
		pObj->dx = 0;
		pObj->dy = 0;

		if (pObj->frame >= 7) {
			memset(pObj, 0, sizeof(OBJECT));
			return;
		}
	}
	else {
		GotoObj(&ao[ITEMBOX], pObj, 12 * _2X);
		//pObj->motion = PO_C37_SHOT0;
		pObj->x += pObj->dx;
		pObj->y += pObj->dy;
	}

	if (pObj->frame > 38) {
		pObj->status = 1;
		pObj->frame = 0;
	}

	InitMotion(pObj);
	pObj->frame++;
	pObj->mainFrame++;
}
//동료들의 무브
void CrewMove(OBJECT* pObj)
{
	const signed short* tPtr;
	int ret;
	int i;
	int obj = GetObjFromPtr(pObj);
	int speed = 4 * _2X;//미사일 스피드
	int attackType;
	OBJECT* objPtr;

	tPtr = cmf_status_data[pObj->cmf][pObj->etc];

	if (tPtr == 0 || *tPtr == 0)
		goto END;

	ret = *tPtr;

	//Motion
	tPtr += (2 + (pObj->frame % ret));
	pObj->motion = *tPtr;

	switch (drawHandle) {
	case MD_PLAY:
		switch (attackSequence) {
		case ATTACKSEQUENCE_READY:
		//룰렛이 도는 동안에도 크루는 제자리에서 대기 모션이어야 한다.
		//SLOT 케이스가 없어서 switch를 그냥 빠져나가면, 위에서 잡아둔
		//cmf_status_data[cmf][etc](RouletteAttackStart()가 넣어둔 공격패턴 상태) 모션이 그대로
		//남아 크루가 룰렛 내내 달리는 모션을 재생했다.
		case ATTACKSEQUENCE_SLOT:
		case ATTACKSEQUENCE_COIN:
			pObj->motion = crewPos[pObj->type * 5 + 0] + pObj->frame / 4 % crewPos[pObj->type * 5 + 1];
			break;
		case ATTACKSEQUENCE_ACTION:
			//현재 얘가 움직이는 턴이면
			if (obj == turn) {
				switch (pObj->turnPosition) {
					case HERE:
						if (pObj->frame % ret == 0) {
							pObj->target = NearEnemy(pObj);
							pObj->turnPosition = THERE;//바로 결과로.

							for (i = 0; i < TOTALCONTROLMARK; i++) {
								if (controlMark[i].owner == obj && controlMark[i].attackType == pObj->currentSkill) {
									controlMark[i].alpha = 1;
								}
							}

							attackType = skillData[pObj->currentSkill * SKILLDATASIZE];
							switch (attackType) {
							case CREWBULLET:
							{
								//총알을 실제로 만들었는지 추적한다.
								//바로 위에서 turnPosition을 THERE로 바꿔놨는데, THERE에는 아무 처리가 없고
								//(아래 case THERE: break;) 턴을 넘겨주는 쪽은 총알이 적에게 맞았을 때
								//FollowMove()가 mom의 turnPosition을 DMGUPDATE로 올려주는 경로뿐이다.
								//따라서 총알이 안 만들어지면 이 크루는 THERE에 영원히 머물고 턴이 넘어가지
								//않아 전투 전체가 멈춘다("공격버튼을 눌러도 아무 일도 안 일어남").
								//NearEnemy()는 active하고 dead가 아닌 적이 없으면 0을 돌려주므로,
								//적이 아직 등장 연출 중이거나 이미 죽었으면 여기에 걸린다.
								bool bulletFired = false;

								if (pObj->target >= ENEMY && pObj->target < NEUTRAL) {
									for (i = BULLET; i < ENEMYUSEROBJ; i++) {
										if (ao[i].active == false) {

											AddObject(&ao[i], pObj, ADDOBJ_CREWBULLET);
											ao[i].target = pObj->target;
											//방향성 잡아주고
											if (pObj->x > ao[ao[i].target].x)
												ao[i].dirF = ao[i].dirX = LEFT;
											else
												ao[i].dirF = ao[i].dirX = RIGHT;

											bulletFired = true;

#ifdef SPEEDTURN
											if (GetObjFromPtr(pObj) == turn && GetSonObjCnt(GetObjFromPtr(pObj)) == 0)
												WhoIsNextTurn();
#endif
											break;
										}
									}
								}

								//총알을 못 쐈으면 이 턴은 그냥 넘긴다. DMGUPDATE로 올려두면 아래
								//case DMGUPDATE에서 onceDmgUpdateFrame이 다 되는 시점에 WhoIsNextTurn()이
								//호출되어 다음 턴(주인공)으로 정상 진행된다.
								if (bulletFired == false) {
									pObj->turnPosition = DMGUPDATE;
									onceDmgUpdateFrame = 2 * FPS;
								}
							}
								break;
							case SUMMON:
								objPtr = &ao[skillData[pObj->currentSkill * SKILLDATASIZE + SKILLDATA_TARGET]];
								objPtr->type = skillData[pObj->currentSkill * SKILLDATASIZE + SKILLDATA_OBJECTINFO];
								objPtr->cmf = enemyData[objPtr->type * ENEMYDATASIZE + ENEMYDATA_CMF];
								objPtr->zoom = objPtr->defaultZoom = SUMMONZOOM;
								SetEnemy(objPtr);
								objPtr->moveHandler = REGENMOVE;
								objPtr->drawHandler = REGENDRAW;
								objPtr->nx = objPtr->x = DX / 2;//ao[ROBIN].x + TSIZE;
								objPtr->ny = objPtr->y = ao[ROBIN].y + monXYGap[(objPtr->type - 3) * 2 + 1];

								switch (objPtr->type) {
								case ENEMY_FOGRA:
								case ENEMY_FOGRA_RED:
								case ENEMY_FOGRA_BLUE:
								case ENEMY_FOGRA_PURPLE:
								case ENEMY_FOGRA_GREEN:
								case ENEMY_FOGRA_GOLD:
								case ENEMY_FOGRA_BLACK:
									objPtr->y += 88 * _2X;
									break;
								case ENEMY_BAHAMUT:
								case ENEMY_BAHAMUT_RED:
								case ENEMY_BAHAMUT_BLUE:
								case ENEMY_BAHAMUT_PURPLE:
								case ENEMY_BAHAMUT_GREEN:
								case ENEMY_BAHAMUT_GOLD:
								case ENEMY_BAHAMUT_BLACK:
									objPtr->y -= 32 * _2X;
									//objPtr->x += 80 * _2X;
									//objPtr->nx = objPtr->x;
									break;
								case ENEMY_CASTLE_BOSS3:
								case ENEMY_CASTLE_BOSS3_RED:
								case ENEMY_CASTLE_BOSS3_BLUE:
								case ENEMY_CASTLE_BOSS3_PURPLE:
								case ENEMY_CASTLE_BOSS3_GREEN:
								case ENEMY_CASTLE_BOSS3_GOLD:
								case ENEMY_CASTLE_BOSS3_BLACK:
									objPtr->y += 10 * _2X;
									break;
								}
								objPtr->dx = objPtr->dy = 0;
								switch (objPtr->type) {
								case ENEMY_BAHAMUT:
								case ENEMY_BAHAMUT_RED:
								case ENEMY_BAHAMUT_BLUE:
								case ENEMY_BAHAMUT_PURPLE:
								case ENEMY_BAHAMUT_GREEN:
								case ENEMY_BAHAMUT_GOLD:
								case ENEMY_BAHAMUT_BLACK:
									objPtr->dirX = objPtr->dirF = RIGHT;
									break;
								default:
									objPtr->dirX = objPtr->dirF = RIGHT;
									break;
								}
								objPtr->active = true;

								objPtr->target = pObj->target;
								objPtr->frame = 0;
								pObj->turnPosition = DMGUPDATE;//바로 결과로.

								break;
							case HEROSKILL:
								objPtr = &ao[skillData[pObj->currentSkill * SKILLDATASIZE + SKILLDATA_TARGET]];
								objPtr->currentSkill = skillData[pObj->currentSkill * SKILLDATASIZE + SKILLDATA_OBJECTINFO];
								SetHotKey(objPtr, HOTKEY_SKILL, objPtr->currentSkill, 0);
								HotKeyPress(objPtr, 0);
								break;
							case SUMMONHERO:
								objPtr = &ao[skillData[pObj->currentSkill * SKILLDATASIZE + SKILLDATA_TARGET]];
								objPtr->type = skillData[pObj->currentSkill * SKILLDATASIZE + SKILLDATA_OBJECTINFO];
								objPtr->cmf = enemyData[objPtr->type * ENEMYDATASIZE + ENEMYDATA_CMF];
								objPtr->currentSkill = skillData[pObj->currentSkill * SKILLDATASIZE + SKILLDATA_OBJECTDETAILINFO];
								objPtr->zoom = objPtr->defaultZoom = ao[PLAYER].zoom;
								objPtr->moveHandler = REGENMOVE;
								objPtr->drawHandler = REGENDRAW;
								objPtr->nx = objPtr->x = skillData[pObj->currentSkill * SKILLDATASIZE + SKILLDATA_RESERVED1];
								objPtr->ny = objPtr->y = ao[ROBIN].y;

								objPtr->dx = objPtr->dy = 0;
								
								objPtr->active = true;

								objPtr->target = pObj->target;
								objPtr->frame = 0;
								pObj->turnPosition = DMGUPDATE;//바로 결과로.
								//임시장비세팅
								for (i = EQUIP_WEAPON; i < EQUIP_BOOTS; i++) {
									memset(&tempItem, 0, sizeof(tempItem));
									tempItem.type = 3 * i + objPtr->type;
									tempItem.detail = skillData[pObj->currentSkill * SKILLDATASIZE + SKILLDATA_RESERVED3 + i];
									tempItem.grade = GRADE_NORMAL;
									tempItem.lv = 1;
									tempItem.count = 1;
									EquipItem(objPtr, &tempItem);
								}
								objPtr->ps[PS_DMG] = objPtr->ps[PS_STR] = pObj->ps[PS_DMG];

#ifdef SPEEDTURN
								WhoIsNextTurn();
#endif
								break;
							}
						}
						break;
					case GOING:
						break;
					case THERE:

						break;
					case COMING:
						break;
					case DMGUPDATE:
						if (onceDmgUpdateFrame == 1)
							WhoIsNextTurn();
						break;
					}
					
				}

			break;
		}
		break;
	case MD_BATTLE:
		if (pObj->frame % (FPS * 3 + ret) == 0) {
			for (i = BULLET; i < ENEMYUSEROBJ; i++) {
				pObj->target = NearEnemy(pObj);
				pObj->currentSkill = NPC_GIRL_SKILL2;

				if (ao[i].active == false && pObj->target >= ENEMY && pObj->target < NEUTRAL) {

					AddObject(&ao[i], pObj, ADDOBJ_CREWBULLET);
					ao[i].target = pObj->target;
					//방향성 잡아주고
					if (pObj->x > ao[ao[i].target].x)
						ao[i].dirF = ao[i].dirX = LEFT;
					else
						ao[i].dirF = ao[i].dirX = RIGHT;

	#ifdef SPEEDTURN
					if (GetObjFromPtr(pObj) == turn && GetSonObjCnt(GetObjFromPtr(pObj)) == 0)
						WhoIsNextTurn();
	#endif
					break;
				}
			}
		}
		break;
	}



START:


	//DX
	tPtr += ret;

	pObj->dx = 4 * _2X;
	//pObj->dx = 0;

	//DY
	tPtr += ret;

	pObj->dy = 0;

END:
	if (pObj->target == false || pObj->lv == false)
		pObj->dirX = pObj->dirF = RIGHT;
	else {
		if (ao[pObj->target].x < pObj->x)
			pObj->dirX = pObj->dirF = LEFT;
		else
			pObj->dirX = pObj->dirF = RIGHT;
	}

	if (!pObj->block)
		InitMotion(pObj);

	//TEST
	//pObj->lv = 1;

	if (pObj->lv)
		pObj->frame++;


}

void CutOffMove(OBJECT* pObj)
{
	int xy[] = {
		320, 320,//0
		297, 347,//1
		268, 365,//2
		230, 344,//3

		197, 297,//4
		237, 224,//5
		333, 178,//6
		441, 250,//7

		428, 374,//8
		307, 448,//9
		168, 385,//10
		119, 233,//11

		221, 91,//12
		418, 93,//13
		545, 215,//14
		538, 373,//15

		427, 520,//16
		172, 563,//17
		-32, 360,//18
		11, 72,//19

		342, -112,//20
		749, 8,//21
		919, 308,//22
		719, 758,//23
	};

	if (pObj->active == false)
		return;

	pObj->motion = PO_C0_SURPRISE0 + pObj->frame / 4 % 2;

	InitMotion(pObj);

	if (pObj->frame % 3 == 0) {
		if (pObj->zoom < 8)
			pObj->zoom++;
	}

	pObj->x += xy[(pObj->frame + 1) * 2] - xy[(pObj->frame) * 2];
	pObj->y -= xy[(pObj->frame + 1) * 2 + 1] - xy[(pObj->frame) * 2 + 1];

	if (pObj->frame < 21) {
		pObj->frame++;
	}
	else {
		pObj->active = false;
		pObj->dead = true;
		pObj->deadFrame = FPS;
	}
}

void TileCheckX(OBJECT* pObj)
{
	int dx_block;
	int t_crashed;
	int dx = pObj->dx;
	signed char wx;

	//if (drawHandle == MD_BATTLE && (GetObjFromPtr(pObj) == PLAYER || GetObjFromPtr(pObj) == ENEMY)) {
	//	pObj->x += pObj->dx;
	//	return;
	//}

	if (pObj->debuf[SLOW]) {
		if (dx > 0)
			dx = Max(1 * _2X, dx / 3);
		else if (dx < 0)
			dx = Min(-1 * _2X, dx / 3);
	}

	wx = dx;

	do {
		if (wx > 0)
			dx = Min(TSIZE * _2X, wx);
		else
			dx = Max(-TSIZE * _2X, wx);

		wx -= dx;
		pObj->x += dx;	//x축으로 먼저 이동시킴

		//위치가 방크기를 넘어간 경우
		if (PxlLeft(pObj) < 0)
			pObj->x = -pObj->cpx;
		else if (PxlRight(pObj) > (rw - 4) * TSIZE - 1)
			pObj->x = (rw - 4) * TSIZE - pObj->cpx - pObj->cx;

		t_crashed = TileCrash(pObj);

		if (t_crashed > 2) {
			pObj->x -= dx;	//x축 좌표를 원위치 시킴
			pObj->dx = 0;
			pObj->x += ClearGap(pObj, 0);

			dx = 0;
			wx = 0;
		}
		else if ((mapInfoArray[mapInfoOff + pObj->tileY2 * rw + pObj->tileX1] == TILE_DOWN || mapInfoArray[mapInfoOff + pObj->tileY2 * rw + pObj->tileX2] == TILE_DOWN) && pObj->status == WALK) {
			pObj->status = THROUGH;
		}
		else if (pObj->onTile != TILE_BLOCK && t_crashed == 1 && pObj->status != THROUGH2 && pObj->status != WALK && pObj->status != JUMP2 && pObj->dirY == DOWN) {
			pObj->x -= dx;	//x축 좌표를 원위치 시킴
			pObj->dx = 0;
			pObj->x += ClearGap(pObj, 0);

			dx = 0;
			wx = 0;
		}

		dx_block = BlockObj(pObj, 0);

		if (dx_block)
			pObj->x -= dx_block;

	} while (Abs(wx) > 0);

	pObj->dx = Abs(pObj->dx);
}

void TileCheckY(OBJECT* pObj)
{
	int obj = GetObjFromPtr(pObj);

	signed char o_dirY = pObj->dirY;
	int t_crashed;
	signed char o_dx = pObj->dx;
	signed char o_dy = pObj->dy;
	//int o_j = pObj->jumpFrame;
	unsigned char o_m = pObj->motion;
	signed char wy = pObj->dy;
	int dx_block;

	if (drawHandle == MD_PLAY)
	return;
	//if ((drawHandle == MD_BATTLE || drawHandle == MD_RAID) && (GetObjFromPtr(pObj) == PLAYER || GetObjFromPtr(pObj) == ENEMY))
	//	return;

	do {
		if (wy > 0)
			pObj->dy = Min(TSIZE, wy);
		else
			pObj->dy = Max(-TSIZE, wy);

		wy -= pObj->dy;
		pObj->y += pObj->dy;
		t_crashed = TileCrash(pObj);

		if (t_crashed > 2) {
			if (pObj->dirY == UP) {
				pObj->y -= pObj->dy;
				pObj->y += ClearGap(pObj, 1);

				if (pObj->inTile)
					o_dy = 0;
				else {
					pObj->jumpFrame = 0;
					pObj->status = FALL;
					pObj->dirY = DOWN;
				}
			}
			else {
				if (pObj->status == FALL2)
					pObj->motion = PO_C0_LANDING0;
				else
					pObj->status = WALK;

				pObj->onTile = GetOnTile(pObj);

				if (pObj->superJump == 1)
					pObj->superJump = -24;

				if (GetObjFromPtr(pObj) < PLAYERALL) {
					pObj->jumpLock = false;
					pObj->jumpTwice = false;
				}

				pObj->my = false;
				pObj->jumpFrame = 0;
				pObj->y -= pObj->dy;
				pObj->y += ClearGap(pObj, 1);

				if (pObj->inTile) {
					o_dy = 0;
					pObj->motion = (pObj->dx) ? PO_C0_W0 : PO_C0_N0;
				}

				if (pObj->attack == ATTACK_DOWN && pObj->type == ROBIN)
					if (obj == raidPlayer || ao[obj].soldier == true || (obj >= BULLET && obj < ENEMY && (ao[obj].target == raidPlayer || ao[ao[obj].target].soldier == true)))
						effect.shake = 1;
			}

			pObj->dy = 0;
			wy = 0;
		}
		else if (t_crashed > 0) {
			if (pObj->dirY == DOWN) {
				if ((t_crashed == 2 && pObj->status != THROUGH && pObj->status != THROUGH2) || (t_crashed == 1 && pObj->status != THROUGH2)) {
					pObj->onTile = GetOnTile(pObj);
					pObj->y -= pObj->dy;

					if (TileCrash(pObj) == 2) {
						pObj->y += pObj->dy;
						pObj->motion = o_m;
						pObj->dx = o_dx;
					}

					pObj->y += ClearGap(pObj, 1);
					pObj->my = false;
					pObj->jumpFrame = 0;
					pObj->dy = 0;
					pObj->status = WALK;
					wy = 0;

					if (pObj->attack == ATTACK_DOWN && pObj->type == ROBIN)
						if (obj == raidPlayer || ao[obj].soldier == true || (obj >= BULLET && obj < ENEMY && (ao[obj].target == raidPlayer || ao[ao[obj].target].soldier == true)))
							effect.shake = 1;
				}
				else {
					pObj->onTile = GetOnTile(pObj);

					if (pObj->jumpFrame >= 4 && pObj->onTile == TILE_DOWN && (mapInfoArray[mapInfoOff + pObj->tileY2 * rw + pObj->tileX1] == TILE_DOWN || mapInfoArray[mapInfoOff + pObj->tileY2 * rw + pObj->tileX2] == TILE_DOWN)) {
						pObj->status = WALK;
						pObj->my = false;
						pObj->jumpFrame = 0;
						pObj->y -= pObj->dy;
						pObj->y += ClearGap(pObj, 1);
						pObj->dy = 0;
						break;
					}
				}
			}
		}
		else if (pObj->jumpFrame > 2 && GetOnTile(pObj) == 0 && (pObj->status == THROUGH || pObj->status == THROUGH2))
			pObj->status = FALL;
		else if (pObj->status == WALK)
			pObj->status = FALL;

		dx_block = BlockObj(pObj, 1);

		if (dx_block) {
			pObj->dirY = o_dirY;
			pObj->y -= dx_block;

			if (pObj->dirY == UP) {
				pObj->status = FALL;
				pObj->dirY = DOWN;
				pObj->motion = PO_C0_W0;
			}
			else
				pObj->status = WALK;

			pObj->jumpFrame = 0;
		}
	} while (Abs(wy) > 0);

	pObj->dy = o_dy;

	//if (pObj->onTile >= TILE_BLAZE && pObj->attackedFrame == 0)
	//	AttackRobin(ATTACKTYPE_MAGMA, GetObjFromPtr(pObj));

	pObj->dy = Abs(pObj->dy);
}

void TileCheckX2(OBJECT* pObj)
{
	int dx_block;
	int t_crashed;
	int check = 2;
	signed char wx = pObj->dx;

	if (pObj->block && pObj->type < NPC_CAPTAIN)
		pObj->hp = pObj->x;

	if (pObj->dx == 0)
		goto chk;

	if (pObj->debuf[SLOW])
		pObj->dx /= 2;

	do {
		if (wx > 0)
			pObj->dx = Min(TSIZE, wx);
		else
			pObj->dx = Max(-TSIZE, wx);

		wx -= pObj->dx;
		pObj->x += pObj->dx;	//x축으로 먼저 이동시킴

		//위치가 방크기를 넘어간 경우
		if (PxlLeft(pObj) < 0) {
			pObj->x = -pObj->cpx;
			//do {
			//	pObj->x = -pObj->cpx;
			//} while (PxlLeft(pObj) < 0);
			t_crashed = 4;
		}
		else if (PxlRight(pObj) > rw * TSIZE - 1) {
			pObj->x = rw * TSIZE - pObj->cpx - pObj->cx;
			//do {
			//	pObj->x += -pObj->cpx - pObj->cx;
			//} while (PxlRight(pObj) > rw * TSIZE - 1);

			t_crashed = 4;
		}
		else
			t_crashed = TileCrash(pObj);

		if (t_crashed > check) {
			pObj->x -= pObj->dx;
			//do {
			//	pObj->x -= (pObj->dx > 0 ? 1 * _2X : -1 * _2X);	//x축 좌표를 원위치 시킴
			//} while (TileCrash(pObj) > check);

			wx = 0;

			switch (pObj->type) {
			case PLAYER:
				pObj->x += ClearGap(pObj, 0);
				break;
			case ENEMY_SPIDER:
			case ENEMY_SPIDER_RED:
			case ENEMY_SPIDER_BLUE:
			case ENEMY_SPIDER_PURPLE:
			case ENEMY_SPIDER_GREEN:
			case ENEMY_SPIDER_GOLD:
			case ENEMY_SPIDER_BLACK:
			case ENEMY_PUMPKIN:
			case ENEMY_PUMPKIN_RED:
			case ENEMY_PUMPKIN_BLUE:
			case ENEMY_PUMPKIN_PURPLE:
			case ENEMY_PUMPKIN_GREEN:
			case ENEMY_PUMPKIN_GOLD:
			case ENEMY_PUMPKIN_BLACK:
			case ENEMY_ONEEYE:
			case ENEMY_ONEEYE_RED:
			case ENEMY_ONEEYE_BLUE:
			case ENEMY_ONEEYE_PURPLE:
			case ENEMY_ONEEYE_GREEN:
			case ENEMY_ONEEYE_GOLD:
			case ENEMY_ONEEYE_BLACK:
			case ENEMY_GHOST:
			case ENEMY_GHOST_RED:
			case ENEMY_GHOST_BLUE:
			case ENEMY_GHOST_PURPLE:
			case ENEMY_GHOST_GREEN:
			case ENEMY_GHOST_GOLD:
			case ENEMY_GHOST_BLACK:
				break;
			default:
				pObj->x += ClearGap(pObj, 0);
			}

			if (GetObjFromPtr(pObj) < NEUTRAL) {
				switch (pObj->type) {
				default:
					pObj->dx = 0;
					break;
				}
			}
			else {
				switch (pObj->type) {
				case OBJ_SLED:
					//썰매를 파괴시킨다.
					//EffectSound(M_BANG);
					PlayMusic(M_BANG);
					pObj->etc = 2;
					pObj->cx = 0;

					break;
				default:
					pObj->dx = 0;
					break;
				}
			}
		}

	chk:
		dx_block = BlockObj(pObj, 0);

		if (dx_block) {
			pObj->x -= dx_block;

			switch (pObj->type) {
			default:
				if (pObj->type >= NPC_CAPTAIN) {
					if (pObj->dx != 0) {
						if (dx_block > 0)
							pObj->dirF = pObj->dirX = LEFT;
						else
							pObj->dirF = pObj->dirX = RIGHT;
					}
				}
				else {
					if (pObj->attack == 0 && pObj->debuf[KNOCKBACK] == 0)
						pObj->dirF = pObj->dirX = 1 - pObj->dirX;
				}
				break;
			}
		}
	} while (Abs(wx) > 0);
}

void TileCheckY2(OBJECT* pObj)
{
	int obj = GetObjFromPtr(pObj);
	int dx_block;
	int t_crashed;
	int check = 0;
	int o_y;
	signed char wy;
	signed char o_dy;

	//if (drawHandle == MD_BATTLE && (GetObjFromPtr(pObj) == PLAYER || GetObjFromPtr(pObj) == ENEMY))
	//	return;

	if (pObj->block && pObj->type < NPC_CAPTAIN)
		pObj->maxhp = pObj->y;

	if (obj >= ENEMY && obj < NEUTRAL) {
		pObj->x += 4 * DIR(pObj->dirX) * _2X;
		GetTile(pObj);
		pObj->x -= 4 * DIR(pObj->dirX) * _2X;

		//몬스터 앞길이 막혔으면 점프뛰기
		if (pObj->status != JUMP && pObj->y - ao[NearPlayer(pObj)].y > 10 * _2X && ((pObj->dirX == LEFT && mapInfoArray[mapInfoOff + pObj->tileY2 * rw + pObj->tileX1] >= TILE_BLOCK) || (pObj->dirX == RIGHT && mapInfoArray[mapInfoOff + pObj->tileY2 * rw + pObj->tileX2] >= TILE_BLOCK))) {
			switch (pObj->type) {
			case ENEMY_TREE:
			case ENEMY_TREE_RED:
			case ENEMY_TREE_BLUE:
			case ENEMY_TREE_PURPLE:
			case ENEMY_TREE_GREEN:
			case ENEMY_TREE_GOLD:
			case ENEMY_TREE_BLACK:
				if (pObj->etc == TREE_MOVE) {
					pObj->status = JUMP;
					pObj->jumpFrame = 2;
				}
				break;
			case ENEMY_SNAIL:
			case ENEMY_SNAIL_RED:
			case ENEMY_SNAIL_BLUE:
			case ENEMY_SNAIL_PURPLE:
			case ENEMY_SNAIL_GREEN:
			case ENEMY_SNAIL_GOLD:
			case ENEMY_SNAIL_BLACK:
				if (pObj->etc == SNAIL_MOVE_FAST) {
					pObj->status = JUMP;
					pObj->jumpFrame = 2;
				}
				break;
			case ENEMY_KNIGHT:
			case ENEMY_KNIGHT_RED:
			case ENEMY_KNIGHT_BLUE:
			case ENEMY_KNIGHT_PURPLE:
			case ENEMY_KNIGHT_GREEN:
			case ENEMY_KNIGHT_GOLD:
			case ENEMY_KNIGHT_BLACK:
				if (pObj->etc == KNIGHT_PLAYER_MOVE) {
					pObj->status = JUMP;
					pObj->jumpFrame = 1;
				}
				break;
			case ENEMY_SNOWMAN:
			case ENEMY_SNOWMAN_RED:
			case ENEMY_SNOWMAN_BLUE:
			case ENEMY_SNOWMAN_PURPLE:
			case ENEMY_SNOWMAN_GREEN:
			case ENEMY_SNOWMAN_GOLD:
			case ENEMY_SNOWMAN_BLACK:
				if (pObj->etc == SNOWMAN_MOVE_FAST) {
					pObj->status = JUMP;
					pObj->jumpFrame = 0;
				}
				break;
			case ENEMY_PUMPKIN:
			case ENEMY_PUMPKIN_RED:
			case ENEMY_PUMPKIN_BLUE:
			case ENEMY_PUMPKIN_PURPLE:
			case ENEMY_PUMPKIN_GREEN:
			case ENEMY_PUMPKIN_GOLD:
			case ENEMY_PUMPKIN_BLACK:
				if (pObj->etc == PUMPKIN_RUSH || pObj->etc == PUMPKIN_MOVE_FAST) {
					pObj->status = JUMP;
					pObj->jumpFrame = 0;
				}
				break;
			case ENEMY_DRAGON1:
			case ENEMY_DRAGON1_RED:
			case ENEMY_DRAGON1_BLUE:
			case ENEMY_DRAGON1_PURPLE:
			case ENEMY_DRAGON1_GREEN:
			case ENEMY_DRAGON1_GOLD:
			case ENEMY_DRAGON1_BLACK:
				if (pObj->etc == DRAGON1_MOVE_FAST) {
					pObj->status = JUMP;
					pObj->jumpFrame = 1;
				}
				break;
			}
		}
	}

	//특수 몬스터 특수처리
	switch (pObj->type) {
	default:
		switch (pObj->status) {
		case JUMP:	//점프하고 있는 경우
			pObj->dirY = UP;
			pObj->dy = -jump[pObj->jumpFrame];
			pObj->jumpFrame++;
			break;
		default:
			pObj->dirY = DOWN;
			if (pObj->jumpFrame < JUMPFRAME)
				pObj->dy = jump[JUMPFRAME - 1 - pObj->jumpFrame];
			else
				pObj->dy = FREEFALL;

			pObj->jumpFrame++;
			break;
		case FLYING:
			break;
		}
		break;
	case ENEMY_SPIDER:
	case ENEMY_SPIDER_RED:
	case ENEMY_SPIDER_BLUE:
	case ENEMY_SPIDER_PURPLE:
	case ENEMY_SPIDER_GREEN:
	case ENEMY_SPIDER_GOLD:
	case ENEMY_SPIDER_BLACK:
		if (pObj->status == FALL)
			pObj->dy = TSIZE;
		break;

	}

	wy = o_dy = pObj->dy;

	do {

		if (wy > 0)
			pObj->dy = Min(TSIZE, wy);
		else
			pObj->dy = Max(-TSIZE, wy);

		wy -= pObj->dy;
		o_y = pObj->y + pObj->dy;

		pObj->y += pObj->dy;

		t_crashed = TileCrash(pObj);

		if (!escort.active && obj < NEUTRAL && !robin.bossRoom && !isDemo) {
			switch (pObj->type) {
				//좌우 앞쪽 아래가 빈공간이면 방향을 바꿔준다.
			default:
			DIRNEUTRAL:

				if (pObj->debuf[KNOCKBACK] == 0 && pObj->status == WALK && ((pObj->dirX == LEFT && mapInfoArray[mapInfoOff + pObj->tileY2 * rw + pObj->tileX1] == TILE_VOID) || (pObj->dirX == RIGHT && mapInfoArray[mapInfoOff + pObj->tileY2 * rw + pObj->tileX2] == TILE_VOID))) {
					if (pObj->attack)
						pObj->dx = 0;
					else {
						pObj->dirF = pObj->dirX = 1 - pObj->dirX;
						pObj->dx = Abs(pObj->dx) * DIR(pObj->dirX);
					}
				}

				break;
			case ENEMY_SLIME:
			case ENEMY_SLIME_RED:
			case ENEMY_SLIME_BLUE:
			case ENEMY_SLIME_PURPLE:
			case ENEMY_SLIME_GREEN:
			case ENEMY_SLIME_GOLD:
			case ENEMY_SLIME_BLACK:
			case ENEMY_SPIDER:
			case ENEMY_SPIDER_RED:
			case ENEMY_SPIDER_BLUE:
			case ENEMY_SPIDER_PURPLE:
			case ENEMY_SPIDER_GREEN:
			case ENEMY_SPIDER_GOLD:
			case ENEMY_SPIDER_BLACK:
			case ENEMY_FROG:
			case ENEMY_FROG_RED:
			case ENEMY_FROG_BLUE:
			case ENEMY_FROG_PURPLE:
			case ENEMY_FROG_GREEN:
			case ENEMY_FROG_GOLD:
			case ENEMY_FROG_BLACK:
			case ENEMY_TREE:
			case ENEMY_TREE_RED:
			case ENEMY_TREE_BLUE:
			case ENEMY_TREE_PURPLE:
			case ENEMY_TREE_GREEN:
			case ENEMY_TREE_GOLD:
			case ENEMY_TREE_BLACK:
			case ENEMY_LARVA:
			case ENEMY_LARVA_RED:
			case ENEMY_LARVA_BLUE:
			case ENEMY_LARVA_PURPLE:
			case ENEMY_LARVA_GREEN:
			case ENEMY_LARVA_GOLD:
			case ENEMY_LARVA_BLACK:
			case ENEMY_JELLYFISH:
			case ENEMY_JELLYFISH_RED:
			case ENEMY_JELLYFISH_BLUE:
			case ENEMY_JELLYFISH_PURPLE:
			case ENEMY_JELLYFISH_GREEN:
			case ENEMY_JELLYFISH_GOLD:
			case ENEMY_JELLYFISH_BLACK:
			case ENEMY_SALAMANDER:
			case ENEMY_SALAMANDER_RED:
			case ENEMY_SALAMANDER_BLUE:
			case ENEMY_SALAMANDER_PURPLE:
			case ENEMY_SALAMANDER_GREEN:
			case ENEMY_SALAMANDER_GOLD:
			case ENEMY_SALAMANDER_BLACK:
				break;
			case ENEMY_BOAR:
			case ENEMY_BOAR_RED:
			case ENEMY_BOAR_BLUE:
			case ENEMY_BOAR_PURPLE:
			case ENEMY_BOAR_GREEN:
			case ENEMY_BOAR_GOLD:
			case ENEMY_BOAR_BLACK:
				if (pObj->etc == BOAR_MOVE)
					goto DIRNEUTRAL;
				break;
			case ENEMY_PUMPKIN:
			case ENEMY_PUMPKIN_RED:
			case ENEMY_PUMPKIN_BLUE:
			case ENEMY_PUMPKIN_PURPLE:
			case ENEMY_PUMPKIN_GREEN:
			case ENEMY_PUMPKIN_GOLD:
			case ENEMY_PUMPKIN_BLACK:
				if (pObj->etc == PUMPKIN_MOVE)
					goto DIRNEUTRAL;
				break;
			case ENEMY_KNIGHT:
			case ENEMY_KNIGHT_RED:
			case ENEMY_KNIGHT_BLUE:
			case ENEMY_KNIGHT_PURPLE:
			case ENEMY_KNIGHT_GREEN:
			case ENEMY_KNIGHT_GOLD:
			case ENEMY_KNIGHT_BLACK:
				if (pObj->etc == KNIGHT_MOVE)
					goto DIRNEUTRAL;
				break;
			case ENEMY_SNAIL:
			case ENEMY_SNAIL_RED:
			case ENEMY_SNAIL_BLUE:
			case ENEMY_SNAIL_PURPLE:
			case ENEMY_SNAIL_GREEN:
			case ENEMY_SNAIL_GOLD:
			case ENEMY_SNAIL_BLACK:
				if (pObj->etc == SNAIL_MOVE)
					goto DIRNEUTRAL;
				break;
			case ENEMY_GOLEM:
			case ENEMY_GOLEM_RED:
			case ENEMY_GOLEM_BLUE:
			case ENEMY_GOLEM_PURPLE:
			case ENEMY_GOLEM_GREEN:
			case ENEMY_GOLEM_GOLD:
			case ENEMY_GOLEM_BLACK:
				if (pObj->etc == GOLEM_MOVE)
					goto DIRNEUTRAL;
				break;
			case ENEMY_LIZARD:
			case ENEMY_LIZARD_RED:
			case ENEMY_LIZARD_BLUE:
			case ENEMY_LIZARD_PURPLE:
			case ENEMY_LIZARD_GREEN:
			case ENEMY_LIZARD_GOLD:
			case ENEMY_LIZARD_BLACK:
				if (pObj->etc == LIZARD_MOVE)
					goto DIRNEUTRAL;
				break;
			case ENEMY_SLING:
			case ENEMY_SLING_RED:
			case ENEMY_SLING_BLUE:
			case ENEMY_SLING_PURPLE:
			case ENEMY_SLING_GREEN:
			case ENEMY_SLING_GOLD:
			case ENEMY_SLING_BLACK:
				if (pObj->etc != SLING_RETREAT)
					goto DIRNEUTRAL;
				break;
			case ENEMY_SNOWMAN:
			case ENEMY_SNOWMAN_RED:
			case ENEMY_SNOWMAN_BLUE:
			case ENEMY_SNOWMAN_PURPLE:
			case ENEMY_SNOWMAN_GREEN:
			case ENEMY_SNOWMAN_GOLD:
			case ENEMY_SNOWMAN_BLACK:
				if (pObj->etc == SNOWMAN_MOVE)
					goto DIRNEUTRAL;
				break;
			case ENEMY_SKELETON:
			case ENEMY_SKELETON_RED:
			case ENEMY_SKELETON_BLUE:
			case ENEMY_SKELETON_PURPLE:
			case ENEMY_SKELETON_GREEN:
			case ENEMY_SKELETON_GOLD:
			case ENEMY_SKELETON_BLACK:
				if (pObj->etc == SKELETON_MOVE)
					goto DIRNEUTRAL;
				break;
			case ENEMY_DRAGON1:
			case ENEMY_DRAGON1_RED:
			case ENEMY_DRAGON1_BLUE:
			case ENEMY_DRAGON1_PURPLE:
			case ENEMY_DRAGON1_GREEN:
			case ENEMY_DRAGON1_GOLD:
			case ENEMY_DRAGON1_BLACK:
				if (pObj->etc == DRAGON1_MOVE)
					goto DIRNEUTRAL;
				break;
			}
		}

		if (pObj->type == OBJ_ITEM && obj >= ITEMOBJ) {
			check = 1;

			if (pObj->status == FALL && pObj->mom == 1 && t_crashed < 2)
				pObj->mom = 0;
			if (pObj->mom)
				continue;
		}

		//타일과 충돌하였다면
		if (t_crashed > check) {
			pObj->y -= pObj->dy;

			switch (pObj->type) {
			case ENEMY_ONEEYE:
			case ENEMY_ONEEYE_RED:
			case ENEMY_ONEEYE_BLUE:
			case ENEMY_ONEEYE_PURPLE:
			case ENEMY_ONEEYE_GREEN:
			case ENEMY_ONEEYE_GOLD:
			case ENEMY_ONEEYE_BLACK:
				break;
			default:
				pObj->y += ClearGap(pObj, 1);
			}

			if (pObj->dirY == UP) {
				pObj->status = FALL;
				pObj->dirY = DOWN;
			}
			else {
				if (obj >= NEUTRAL) {
					switch (pObj->type) {
					case OBJ_PUSH:
						if (pObj->status == FALL) {
							effect.shake = Max(1, Min(6, 10 - pObj->jumpFrame));
							//EffectSound(M_KUNG);
							PlayMusic(M_KUNG);
						}
						break;
						//떨어지는 종유석
					case OBJ_STALACTITE:
						pObj->etc = 2;
						pObj->cx = 0;
						break;
						//떨어지는 고드름
					case OBJ_SPIKE:
						pObj->etc = 2;
						pObj->cx = 0;
						break;
					}
				}
				else {
					switch (pObj->type) {
					case ENEMY_KIMERA:
					case ENEMY_KIMERA_RED:
					case ENEMY_KIMERA_BLUE:
					case ENEMY_KIMERA_PURPLE:
					case ENEMY_KIMERA_GREEN:
					case ENEMY_KIMERA_GOLD:
					case ENEMY_KIMERA_BLACK:
						if (pObj->etc == KIMERA_LAND_READY) {
							pObj->etc = KIMERA_LANDING;
							pObj->frame = 0;
						}
						break;
					case ENEMY_LIGHTNING:
					case ENEMY_LIGHTNING_RED:
					case ENEMY_LIGHTNING_BLUE:
					case ENEMY_LIGHTNING_PURPLE:
					case ENEMY_LIGHTNING_GREEN:
					case ENEMY_LIGHTNING_GOLD:
					case ENEMY_LIGHTNING_BLACK:
						if (pObj->etc == LIGHTNING_FALL) {
							pObj->etc = LIGHTNING_MOVE;
							pObj->moveHandler = LIGHTNINGMOVE;
							pObj->dirX = pObj->dirF = LEFT ? LEFT : RIGHT;
							pObj->status = pObj->dirX == LEFT ? LEFT_WALK : RIGHT_WALK;
						}
						break;
					case ENEMY_SPIDER:
					case ENEMY_SPIDER_RED:
					case ENEMY_SPIDER_BLUE:
					case ENEMY_SPIDER_PURPLE:
					case ENEMY_SPIDER_GREEN:
					case ENEMY_SPIDER_GOLD:
					case ENEMY_SPIDER_BLACK:
						if (pObj->etc == SPIDER_DOWN_LANDING) {
							pObj->etc = SPIDER_DOWN_LAND;
							pObj->frame = 0;
						}
						break;
					case ENEMY_DRAGON1:
					case ENEMY_DRAGON1_RED:
					case ENEMY_DRAGON1_BLUE:
					case ENEMY_DRAGON1_PURPLE:
					case ENEMY_DRAGON1_GREEN:
					case ENEMY_DRAGON1_GOLD:
					case ENEMY_DRAGON1_BLACK:
						if (pObj->etc == DRAGON1_FALL) {
							pObj->etc = DRAGON1_LANDINGREADY;
						}
						break;
					}
				}

				pObj->status = WALK;
				pObj->my = false;
			}

			//if (pObj->moveHandler == SLINGMOVE)
			//	pObj->attacked = 1;

			pObj->jumpFrame = 0;
			pObj->dy = 0;
			wy = 0;
		}
		else if (pObj->status == WALK)
			pObj->status = FALL;
	} while (Abs(wy) > 0);

	switch (pObj->type) {
	default:
		if (pObj->status == JUMP && pObj->jumpFrame >= JUMPFRAME) {
			pObj->jumpFrame = 0;
			pObj->dirY = DOWN;
			pObj->status = FALL;
		}
		break;
	}

	dx_block = BlockObj(pObj, 1);

	if (dx_block) {
		pObj->y -= dx_block;

		if (dx_block > 0) {
			pObj->status = FALL;
			pObj->dirY = DOWN;
		}
		else
			pObj->status = WALK;

		pObj->jumpFrame = 0;
	}

	pObj->dy = Abs(pObj->dy);

	if (pObj->y >= pObj->ny)
		pObj->y = pObj->ny;
}

int AlivePlayerCnt(void)
{
	int i;
	int cnt = 0;

	for (i = ROBIN; i < MAXX + 1; i++)
		if (ao[i].active && ao[i].dead == false)
			cnt++;

	return cnt;
}

int AliveEnemyCnt(void)
{
	int i;
	int cnt = 0;

	for (i = ENEMY; i < NEUTRAL; i++) {
		if (ao[i].dead == false && ao[i].active == true && ao[i].moveHandler != VANISHMOVE)
			cnt++;
	}

	return cnt;
}
//
bool IsHitPossible(OBJECT* pObj, OBJECT* mObj)
{
	//미스가 나지 않으면 항상 
	switch (pObj->attack) {

	}
	if (ao[turn].hitCount < skillData[mObj->currentSkill * SKILLDATASIZE + 1])
		return true;

	return false;
}

bool IsMaxBet(void)
{
	if (bet == MAXBET - 1)
		return true;
	else if (robin.heart >= betHeart[bet] && robin.heart < betHeart[bet + 1])
		return true;
	else
		return false;


}

bool IsMaxCoinBet(void)
{
	if (bet == MAXCOINBET - 1)
		return true;
	else if (robin.gold >= betCoin[betBattle] * GetStageAdmissionFee() && robin.gold < betCoin[betBattle + 1] * GetStageAdmissionFee())
		return true;
	else
		return false;


}

int IsKnockBack(int objType)
{
	switch (objType) {
	case ENEMY_TREE:
	case ENEMY_TREE_RED:
	case ENEMY_TREE_BLUE:
	case ENEMY_TREE_PURPLE:
	case ENEMY_TREE_GREEN:
	case ENEMY_TREE_GOLD:
	case ENEMY_TREE_BLACK:
	case ENEMY_BOAR:
	case ENEMY_BOAR_RED:
	case ENEMY_BOAR_BLUE:
	case ENEMY_BOAR_PURPLE:
	case ENEMY_BOAR_GREEN:
	case ENEMY_BOAR_GOLD:
	case ENEMY_BOAR_BLACK:
	case ENEMY_PHOENIX:
	case ENEMY_PHOENIX_RED:
	case ENEMY_PHOENIX_BLUE:
	case ENEMY_PHOENIX_PURPLE:
	case ENEMY_PHOENIX_GREEN:
	case ENEMY_PHOENIX_GOLD:
	case ENEMY_PHOENIX_BLACK:
	case ENEMY_GOLEM:
	case ENEMY_GOLEM_RED:
	case ENEMY_GOLEM_BLUE:
	case ENEMY_GOLEM_PURPLE:
	case ENEMY_GOLEM_GREEN:
	case ENEMY_GOLEM_GOLD:
	case ENEMY_GOLEM_BLACK:
	case ENEMY_GHOST:
	case ENEMY_GHOST_RED:
	case ENEMY_GHOST_BLUE:
	case ENEMY_GHOST_PURPLE:
	case ENEMY_GHOST_GREEN:
	case ENEMY_GHOST_GOLD:
	case ENEMY_GHOST_BLACK:
		return BIGMONSTER;
	case ENEMY_FROG:
	case ENEMY_FROG_RED:
	case ENEMY_FROG_BLUE:
	case ENEMY_FROG_PURPLE:
	case ENEMY_FROG_GREEN:
	case ENEMY_FROG_GOLD:
	case ENEMY_FROG_BLACK:
	case ENEMY_LARVA:
	case ENEMY_LARVA_RED:
	case ENEMY_LARVA_BLUE:
	case ENEMY_LARVA_PURPLE:
	case ENEMY_LARVA_GREEN:
	case ENEMY_LARVA_GOLD:
	case ENEMY_LARVA_BLACK:
	case ENEMY_SALAMANDER:
	case ENEMY_SALAMANDER_RED:
	case ENEMY_SALAMANDER_BLUE:
	case ENEMY_SALAMANDER_PURPLE:
	case ENEMY_SALAMANDER_GREEN:
	case ENEMY_SALAMANDER_GOLD:
	case ENEMY_SALAMANDER_BLACK:
	case ENEMY_GIANT:
	case ENEMY_GIANT_RED:
	case ENEMY_GIANT_BLUE:
	case ENEMY_GIANT_PURPLE:
	case ENEMY_GIANT_GREEN:
	case ENEMY_GIANT_GOLD:
	case ENEMY_GIANT_BLACK:
	case ENEMY_IFRIT:
	case ENEMY_IFRIT_RED:
	case ENEMY_IFRIT_BLUE:
	case ENEMY_IFRIT_PURPLE:
	case ENEMY_IFRIT_GREEN:
	case ENEMY_IFRIT_GOLD:
	case ENEMY_IFRIT_BLACK:
	case ENEMY_FACE:
	case ENEMY_FACE_RED:
	case ENEMY_FACE_BLUE:
	case ENEMY_FACE_PURPLE:
	case ENEMY_FACE_GREEN:
	case ENEMY_FACE_GOLD:
	case ENEMY_FACE_BLACK:
	case ENEMY_MAMMOTH:
	case ENEMY_MAMMOTH_RED:
	case ENEMY_MAMMOTH_BLUE:
	case ENEMY_MAMMOTH_PURPLE:
	case ENEMY_MAMMOTH_GREEN:
	case ENEMY_MAMMOTH_GOLD:
	case ENEMY_MAMMOTH_BLACK:
	case ENEMY_ICESUN:
	case ENEMY_ICESUN_RED:
	case ENEMY_ICESUN_BLUE:
	case ENEMY_ICESUN_PURPLE:
	case ENEMY_ICESUN_GREEN:
	case ENEMY_ICESUN_GOLD:
	case ENEMY_ICESUN_BLACK:
	case ENEMY_CRYSTAL:
	case ENEMY_CRYSTAL_RED:
	case ENEMY_CRYSTAL_BLUE:
	case ENEMY_CRYSTAL_PURPLE:
	case ENEMY_CRYSTAL_GREEN:
	case ENEMY_CRYSTAL_GOLD:
	case ENEMY_CRYSTAL_BLACK:
	case ENEMY_MACHINE:
	case ENEMY_MACHINE_RED:
	case ENEMY_MACHINE_BLUE:
	case ENEMY_MACHINE_PURPLE:
	case ENEMY_MACHINE_GREEN:
	case ENEMY_MACHINE_GOLD:
	case ENEMY_MACHINE_BLACK:
	case ENEMY_ANGEL:
	case ENEMY_ANGEL_RED:
	case ENEMY_ANGEL_BLUE:
	case ENEMY_ANGEL_PURPLE:
	case ENEMY_ANGEL_GREEN:
	case ENEMY_ANGEL_GOLD:
	case ENEMY_ANGEL_BLACK:
	case ENEMY_KIMERA:
	case ENEMY_KIMERA_RED:
	case ENEMY_KIMERA_BLUE:
	case ENEMY_KIMERA_PURPLE:
	case ENEMY_KIMERA_GREEN:
	case ENEMY_KIMERA_GOLD:
	case ENEMY_KIMERA_BLACK:
	case ENEMY_SHIP:
	case ENEMY_SHIP_RED:
	case ENEMY_SHIP_BLUE:
	case ENEMY_SHIP_PURPLE:
	case ENEMY_SHIP_GREEN:
	case ENEMY_SHIP_GOLD:
	case ENEMY_SHIP_BLACK:
	case ENEMY_DARKGIANT:
	case ENEMY_DARKGIANT_RED:
	case ENEMY_DARKGIANT_BLUE:
	case ENEMY_DARKGIANT_PURPLE:
	case ENEMY_DARKGIANT_GREEN:
	case ENEMY_DARKGIANT_GOLD:
	case ENEMY_DARKGIANT_BLACK:
	case ENEMY_DARKDRAGON:
	case ENEMY_DARKDRAGON_RED:
	case ENEMY_DARKDRAGON_BLUE:
	case ENEMY_DARKDRAGON_PURPLE:
	case ENEMY_DARKDRAGON_GREEN:
	case ENEMY_DARKDRAGON_GOLD:
	case ENEMY_DARKDRAGON_BLACK:
	case ENEMY_FOGRA:
	case ENEMY_FOGRA_RED:
	case ENEMY_FOGRA_BLUE:
	case ENEMY_FOGRA_PURPLE:
	case ENEMY_FOGRA_GREEN:
	case ENEMY_FOGRA_GOLD:
	case ENEMY_FOGRA_BLACK:
	case ENEMY_DRAGON2:
	case ENEMY_DRAGON2_RED:
	case ENEMY_DRAGON2_BLUE:
	case ENEMY_DRAGON2_PURPLE:
	case ENEMY_DRAGON2_GREEN:
	case ENEMY_DRAGON2_GOLD:
	case ENEMY_DRAGON2_BLACK:
	case ENEMY_BAHAMUT:
	case ENEMY_BAHAMUT_RED:
	case ENEMY_BAHAMUT_BLUE:
	case ENEMY_BAHAMUT_PURPLE:
	case ENEMY_BAHAMUT_GREEN:
	case ENEMY_BAHAMUT_GOLD:
	case ENEMY_BAHAMUT_BLACK:
	case ENEMY_DEATH:
	case ENEMY_DEATH_RED:
	case ENEMY_DEATH_BLUE:
	case ENEMY_DEATH_PURPLE:
	case ENEMY_DEATH_GREEN:
	case ENEMY_DEATH_GOLD:
	case ENEMY_DEATH_BLACK:
	case ENEMY_CASTLE2:
	case ENEMY_CASTLE2_RED:
	case ENEMY_CASTLE2_BLUE:
	case ENEMY_CASTLE2_PURPLE:
	case ENEMY_CASTLE2_GREEN:
	case ENEMY_CASTLE2_GOLD:
	case ENEMY_CASTLE2_BLACK:
	case ENEMY_CASTLE_BOSS1:
	case ENEMY_CASTLE_BOSS1_RED:
	case ENEMY_CASTLE_BOSS1_BLUE:
	case ENEMY_CASTLE_BOSS1_PURPLE:
	case ENEMY_CASTLE_BOSS1_GREEN:
	case ENEMY_CASTLE_BOSS1_GOLD:
	case ENEMY_CASTLE_BOSS1_BLACK:
	case ENEMY_CASTLE_BOSS2:
	case ENEMY_CASTLE_BOSS2_RED:
	case ENEMY_CASTLE_BOSS2_BLUE:
	case ENEMY_CASTLE_BOSS2_PURPLE:
	case ENEMY_CASTLE_BOSS2_GREEN:
	case ENEMY_CASTLE_BOSS2_GOLD:
	case ENEMY_CASTLE_BOSS2_BLACK:
	case ENEMY_CASTLE_BOSS3:
	case ENEMY_CASTLE_BOSS3_RED:
	case ENEMY_CASTLE_BOSS3_BLUE:
	case ENEMY_CASTLE_BOSS3_PURPLE:
	case ENEMY_CASTLE_BOSS3_GREEN:
	case ENEMY_CASTLE_BOSS3_GOLD:
	case ENEMY_CASTLE_BOSS3_BLACK:
	case ENEMY_CASTLE_BOSS4:
	case ENEMY_CASTLE_BOSS4_RED:
	case ENEMY_CASTLE_BOSS4_BLUE:
	case ENEMY_CASTLE_BOSS4_PURPLE:
	case ENEMY_CASTLE_BOSS4_GREEN:
	case ENEMY_CASTLE_BOSS4_GOLD:
	case ENEMY_CASTLE_BOSS4_BLACK:
		return GIANTMONSTER;

	default:
		return SMALLMONSTER;
	}
}

int IsBigMonster(int objType)
{
	switch (objType) {
		//case ENEMY_TREE:
		//case ENEMY_BOAR:
	case ENEMY_FROG:
	case ENEMY_FROG_RED:
	case ENEMY_FROG_BLUE:
	case ENEMY_FROG_PURPLE:
	case ENEMY_FROG_GREEN:
	case ENEMY_FROG_GOLD:
	case ENEMY_FROG_BLACK:
	case ENEMY_LARVA:
	case ENEMY_LARVA_RED:
	case ENEMY_LARVA_BLUE:
	case ENEMY_LARVA_PURPLE:
	case ENEMY_LARVA_GREEN:
	case ENEMY_LARVA_GOLD:
	case ENEMY_LARVA_BLACK:
	case ENEMY_SALAMANDER:
	case ENEMY_SALAMANDER_RED:
	case ENEMY_SALAMANDER_BLUE:
	case ENEMY_SALAMANDER_PURPLE:
	case ENEMY_SALAMANDER_GREEN:
	case ENEMY_SALAMANDER_GOLD:
	case ENEMY_SALAMANDER_BLACK:
	case ENEMY_GIANT:
	case ENEMY_GIANT_RED:
	case ENEMY_GIANT_BLUE:
	case ENEMY_GIANT_PURPLE:
	case ENEMY_GIANT_GREEN:
	case ENEMY_GIANT_GOLD:
	case ENEMY_GIANT_BLACK:
	case ENEMY_IFRIT:
	case ENEMY_IFRIT_RED:
	case ENEMY_IFRIT_BLUE:
	case ENEMY_IFRIT_PURPLE:
	case ENEMY_IFRIT_GREEN:
	case ENEMY_IFRIT_GOLD:
	case ENEMY_IFRIT_BLACK:
		//case ENEMY_FACE:
		//case ENEMY_FACE_RED:
		//case ENEMY_FACE_BLUE:
		//case ENEMY_FACE_PURPLE:
		//case ENEMY_FACE_GREEN:
		//case ENEMY_FACE_GOLD:
		//case ENEMY_FACE_BLACK:
	case ENEMY_MAMMOTH:
	case ENEMY_MAMMOTH_RED:
	case ENEMY_MAMMOTH_BLUE:
	case ENEMY_MAMMOTH_PURPLE:
	case ENEMY_MAMMOTH_GREEN:
	case ENEMY_MAMMOTH_GOLD:
	case ENEMY_MAMMOTH_BLACK:
		//case ENEMY_ICESUN:
		//case ENEMY_ICESUN_RED:
		//case ENEMY_ICESUN_BLUE:
		//case ENEMY_ICESUN_PURPLE:
		//case ENEMY_ICESUN_GREEN:
		//case ENEMY_ICESUN_GOLD:
		//case ENEMY_ICESUN_BLACK:
		//case ENEMY_GOLEM:
	case ENEMY_ANGEL:
	case ENEMY_ANGEL_RED:
	case ENEMY_ANGEL_BLUE:
	case ENEMY_ANGEL_PURPLE:
	case ENEMY_ANGEL_GREEN:
	case ENEMY_ANGEL_GOLD:
	case ENEMY_ANGEL_BLACK:
	case ENEMY_KIMERA:
	case ENEMY_KIMERA_RED:
	case ENEMY_KIMERA_BLUE:
	case ENEMY_KIMERA_PURPLE:
	case ENEMY_KIMERA_GREEN:
	case ENEMY_KIMERA_GOLD:
	case ENEMY_KIMERA_BLACK:
	case ENEMY_SHIP:
	case ENEMY_SHIP_RED:
	case ENEMY_SHIP_BLUE:
	case ENEMY_SHIP_PURPLE:
	case ENEMY_SHIP_GREEN:
	case ENEMY_SHIP_GOLD:
	case ENEMY_SHIP_BLACK:
	case ENEMY_DARKGIANT:
	case ENEMY_DARKGIANT_RED:
	case ENEMY_DARKGIANT_BLUE:
	case ENEMY_DARKGIANT_PURPLE:
	case ENEMY_DARKGIANT_GREEN:
	case ENEMY_DARKGIANT_GOLD:
	case ENEMY_DARKGIANT_BLACK:
	case ENEMY_FOGRA:
	case ENEMY_FOGRA_RED:
	case ENEMY_FOGRA_BLUE:
	case ENEMY_FOGRA_PURPLE:
	case ENEMY_FOGRA_GREEN:
	case ENEMY_FOGRA_GOLD:
	case ENEMY_FOGRA_BLACK:
	case ENEMY_DRAGON2:
	case ENEMY_DRAGON2_RED:
	case ENEMY_DRAGON2_BLUE:
	case ENEMY_DRAGON2_PURPLE:
	case ENEMY_DRAGON2_GREEN:
	case ENEMY_DRAGON2_GOLD:
	case ENEMY_DRAGON2_BLACK:
	case ENEMY_BAHAMUT:
	case ENEMY_BAHAMUT_RED:
	case ENEMY_BAHAMUT_BLUE:
	case ENEMY_BAHAMUT_PURPLE:
	case ENEMY_BAHAMUT_GREEN:
	case ENEMY_BAHAMUT_GOLD:
	case ENEMY_BAHAMUT_BLACK:
	case ENEMY_DEATH:
	case ENEMY_DEATH_RED:
	case ENEMY_DEATH_BLUE:
	case ENEMY_DEATH_PURPLE:
	case ENEMY_DEATH_GREEN:
	case ENEMY_DEATH_GOLD:
	case ENEMY_DEATH_BLACK:
	case ENEMY_CASTLE2:
	case ENEMY_CASTLE2_RED:
	case ENEMY_CASTLE2_BLUE:
	case ENEMY_CASTLE2_PURPLE:
	case ENEMY_CASTLE2_GREEN:
	case ENEMY_CASTLE2_GOLD:
	case ENEMY_CASTLE2_BLACK:
	case ENEMY_CASTLE_BOSS1:
	case ENEMY_CASTLE_BOSS1_RED:
	case ENEMY_CASTLE_BOSS1_BLUE:
	case ENEMY_CASTLE_BOSS1_PURPLE:
	case ENEMY_CASTLE_BOSS1_GREEN:
	case ENEMY_CASTLE_BOSS1_GOLD:
	case ENEMY_CASTLE_BOSS1_BLACK:
	case ENEMY_CASTLE_BOSS2:
	case ENEMY_CASTLE_BOSS2_RED:
	case ENEMY_CASTLE_BOSS2_BLUE:
	case ENEMY_CASTLE_BOSS2_PURPLE:
	case ENEMY_CASTLE_BOSS2_GREEN:
	case ENEMY_CASTLE_BOSS2_GOLD:
	case ENEMY_CASTLE_BOSS2_BLACK:
	case ENEMY_CASTLE_BOSS3:
	case ENEMY_CASTLE_BOSS3_RED:
	case ENEMY_CASTLE_BOSS3_BLUE:
	case ENEMY_CASTLE_BOSS3_PURPLE:
	case ENEMY_CASTLE_BOSS3_GREEN:
	case ENEMY_CASTLE_BOSS3_GOLD:
	case ENEMY_CASTLE_BOSS3_BLACK:
	case ENEMY_CASTLE_BOSS4:
	case ENEMY_CASTLE_BOSS4_RED:
	case ENEMY_CASTLE_BOSS4_BLUE:
	case ENEMY_CASTLE_BOSS4_PURPLE:
	case ENEMY_CASTLE_BOSS4_GREEN:
	case ENEMY_CASTLE_BOSS4_GOLD:
	case ENEMY_CASTLE_BOSS4_BLACK:
		//case ENEMY_LABETH:
		//case ENEMY_ELKEIN:
		//case ENEMY_DELPIOS:
		//case ENEMY_LORA:
		return true;

	default:
		return false;
	}
}

int IsBigCmf(int cmfIdx)
{
	switch (cmfIdx) {
		//대형폭파신 적들
	case CMF_TREE:
	case CMF_TREE_RED: //129//4
	case CMF_TREE_BLUE: //130//4
	case CMF_TREE_PURPLE: //131//4
	case CMF_TREE_GREEN: //132//4
	case CMF_TREE_GOLD: //133//4
	case CMF_TREE_BLACK: //134//4
	case CMF_FROG:
	case CMF_FROG_RED: //135//5
	case CMF_FROG_BLUE: //136//5
	case CMF_FROG_PURPLE: //137//5
	case CMF_FROG_GREEN: //138//5
	case CMF_FROG_GOLD: //139//5
	case CMF_FROG_BLACK: //140//5
	case CMF_LARVA:
	case CMF_LARVA_RED: //153//8
	case CMF_LARVA_BLUE: //154//8
	case CMF_LARVA_PURPLE: //155//8
	case CMF_LARVA_GREEN: //156//8
	case CMF_LARVA_GOLD: //157//8
	case CMF_LARVA_BLACK: //158//8
	case CMF_SALAMANDER:
	case CMF_SALAMANDER_RED://171//11
	case CMF_SALAMANDER_BLUE://172//11
	case CMF_SALAMANDER_PURPLE://173//11
	case CMF_SALAMANDER_GREEN://174//11
	case CMF_SALAMANDER_GOLD://175//11
	case CMF_SALAMANDER_BLACK://176//11
	case CMF_GIANT:
	case CMF_GIANT_RED://189//14
	case CMF_GIANT_BLUE://190//14
	case CMF_GIANT_PURPLE://191//14
	case CMF_GIANT_GREEN://192//14
	case CMF_GIANT_GOLD://193//14
	case CMF_GIANT_BLACK://194//14
	case CMF_IFRIT:
	case CMF_IFRIT_RED://207//17
	case CMF_IFRIT_BLUE://208//17
	case CMF_IFRIT_PURPLE://209//17
	case CMF_IFRIT_GREEN://210//17
	case CMF_IFRIT_GOLD://211//17
	case CMF_IFRIT_BLACK://212//17
		//case CMF_FACE:
	case CMF_ICESUN:
	case CMF_ICESUN_RED://225//20
	case CMF_ICESUN_BLUE://226//20
	case CMF_ICESUN_PURPLE://227//20
	case CMF_ICESUN_GREEN://228//20
	case CMF_ICESUN_GOLD://229//20
	case CMF_ICESUN_BLACK://230//20
	case CMF_MAMMOTH:
	case CMF_MAMMOTH_RED://231//21
	case CMF_MAMMOTH_BLUE://232//21
	case CMF_MAMMOTH_PURPLE://233//21
	case CMF_MAMMOTH_GREEN://234//21
	case CMF_MAMMOTH_GOLD://235//21
	case CMF_MAMMOTH_BLACK://236//21
	case CMF_GOLEM:
	case CMF_GOLEM_RED://261//26
	case CMF_GOLEM_BLUE://262//26
	case CMF_GOLEM_PURPLE://263//26
	case CMF_GOLEM_GREEN://264//26
	case CMF_GOLEM_GOLD://265//26
	case CMF_GOLEM_BLACK://266//26
	case CMF_SPIDER:
	case CMF_SPIDER_RED://267//27
	case CMF_SPIDER_BLUE://268//27
	case CMF_SPIDER_PURPLE://269//27
	case CMF_SPIDER_GREEN://270//27
	case CMF_SPIDER_GOLD://271//27
	case CMF_SPIDER_BLACK://272//27
	case CMF_SHIP:
	case CMF_SHIP_RED://273//28
	case CMF_SHIP_BLUE://274//28
	case CMF_SHIP_PURPLE://275//28
	case CMF_SHIP_GREEN://276//28
	case CMF_SHIP_GOLD://277//28
	case CMF_SHIP_BLACK://278//28
	case CMF_DARKGIANT:
	case CMF_DARKGIANT_RED://339//39
	case CMF_DARKGIANT_BLUE://340//39
	case CMF_DARKGIANT_PURPLE://341//39
	case CMF_DARKGIANT_GREEN://342//39
	case CMF_DARKGIANT_GOLD://343//39
	case CMF_DARKGIANT_BLACK://344//39
	case CMF_ANGEL:
	case CMF_ANGEL_RED://327//37
	case CMF_ANGEL_BLUE://328//37
	case CMF_ANGEL_PURPLE://329//37
	case CMF_ANGEL_GREEN://330//37
	case CMF_ANGEL_GOLD://331//37
	case CMF_ANGEL_BLACK://332//37
	case CMF_DEATH:
	case CMF_DEATH_RED://291//31
	case CMF_DEATH_BLUE://292//31/
	case CMF_DEATH_PURPLE://293//31
	case CMF_DEATH_GREEN://294//31
	case CMF_DEATH_GOLD://295//31
	case CMF_DEATH_BLACK://296//31
	case CMF_FOGRA:
	case CMF_FOGRA_RED://345//40
	case CMF_FOGRA_BLUE://346//40
	case CMF_FOGRA_PURPLE://347//40
	case CMF_FOGRA_GREEN://348//40
	case CMF_FOGRA_GOLD://349//40
	case CMF_FOGRA_BLACK://350//40
	case CMF_DRAGON2:
	case CMF_DRAGON2_RED://357//42
	case CMF_DRAGON2_BLUE://358//42
	case CMF_DRAGON2_PURPLE://359//42
	case CMF_DRAGON2_GREEN://360//42
	case CMF_DRAGON2_GOLD://361//42
	case CMF_DRAGON2_BLACK://362//42
	case CMF_BAHAMUT:
	case CMF_BAHAMUT_RED://363//43
	case CMF_BAHAMUT_BLUE://364//43
	case CMF_BAHAMUT_PURPLE://365//43
	case CMF_BAHAMUT_GREEN://366//43
	case CMF_BAHAMUT_GOLD://367//43
	case CMF_BAHAMUT_BLACK://368//43
	case CMF_KIMERA:
	case CMF_KIMERA_RED://309//34
	case CMF_KIMERA_BLUE://310//34
	case CMF_KIMERA_PURPLE://311//34
	case CMF_KIMERA_GREEN://312//34
	case CMF_KIMERA_GOLD://313//34
	case CMF_KIMERA_BLACK://314//34
	case CMF_CASTLE2:
	case CMF_CASTLE2_RED://375//45
	case CMF_CASTLE2_BLUE://376//45
	case CMF_CASTLE2_PURPLE://377//45
	case CMF_CASTLE2_GREEN://378//45
	case CMF_CASTLE2_GOLD://379//45
	case CMF_CASTLE2_BLACK://380//45
	case CMF_CASTLE_BOSS1:
	case CMF_CASTLE_BOSS1_RED://393//데브리온48
	case CMF_CASTLE_BOSS1_BLUE://394//데브리온48
	case CMF_CASTLE_BOSS1_PURPLE://395//데브리온48
	case CMF_CASTLE_BOSS1_GREEN://396//데브리온48
	case CMF_CASTLE_BOSS1_GOLD://397//데브리온48
	case CMF_CASTLE_BOSS1_BLACK://398//데브리온48
	case CMF_CASTLE_BOSS2:
	case CMF_CASTLE_BOSS2_RED://399//엘케인 맨티스49
	case CMF_CASTLE_BOSS2_BLUE://400//엘케인 맨티스49
	case CMF_CASTLE_BOSS2_PURPLE://401//엘케인 맨티스49
	case CMF_CASTLE_BOSS2_GREEN://402//엘케인 맨티스49
	case CMF_CASTLE_BOSS2_GOLD://403//엘케인 맨티스49
	case CMF_CASTLE_BOSS2_BLACK://404//엘케인 맨티스49
	case CMF_CASTLE_BOSS3:
	case CMF_CASTLE_BOSS3_RED://405//테트라쿤50
	case CMF_CASTLE_BOSS3_BLUE://406//테트라쿤50
	case CMF_CASTLE_BOSS3_PURPLE://407//테트라쿤50
	case CMF_CASTLE_BOSS3_GREEN://408//테트라쿤50
	case CMF_CASTLE_BOSS3_GOLD://409/테트라쿤50	
	case CMF_CASTLE_BOSS3_BLACK://410//테트라쿤50
	case CMF_CASTLE_BOSS4:
	case CMF_CASTLE_BOSS4_RED://411//다크나이트51
	case CMF_CASTLE_BOSS4_BLUE://412//다크나이트51
	case CMF_CASTLE_BOSS4_PURPLE://413//다크나이트51
	case CMF_CASTLE_BOSS4_GREEN://414//다크나이트51
	case CMF_CASTLE_BOSS4_GOLD://415//다크나이트51
	case CMF_CASTLE_BOSS4_BLACK://416//다크나이트51
		return true;
	default:
		return false;
	}
}

void RegenEnemy(OBJECT* pObj, int type, int x, int y, int dir)
{
	memset(pObj, 0, sizeof(OBJECT));
	pObj->type = type;
	pObj->x = x;
	pObj->y = y;
	pObj->dirF = pObj->dirX = dir;
	SetEnemy(pObj);
	pObj->moveHandler = REGENMOVE;
	pObj->drawHandler = REGENDRAW;
}

int CanRunPlayer(int obj)
{
	//int dst = touchPressedKey[0][0] - touchPressedKey[1][0];

	//if (canRun == true && ((isTouchKey == TOUCH_DRAG && Abs(touchPressedKey[0][1] - touchPressedKey[1][1]) < 10 * _2X && (ao[PLAYER].dirF == LEFT ? dst < 0 : dst > 0)) || pressedKey[1] == systemKey) && ao[PLAYER].status == WALK && ao[PLAYER].attack == false && flamer == 0)
	if (ao[obj].canRun == true && ao[obj].pressedKey[1] == systemKey && ao[obj].status == WALK && ao[obj].attack == false && ao[obj].flamer == 0)
		return true;
	else
		return false;
}
