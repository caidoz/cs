#pragma once

#ifndef _DATA_LIST_H_
#define _DATA_LIST_H_

//tools/content/make_pack.py 가 생성한다. 직접 고치지 말 것.
//
//팩에 들어가는 배열 목록이다. 로더(DataPack.cpp)와 팩 생성기가
//이 하나를 같이 쓰므로 둘이 어긋날 수 없다.
//
//X(이름, 원소크기, 종류, 개수)

#include "EnemyData.h"

#define DATA_LIST(X) \
	X(monStr, 8, DPK_INT, 500) \
	X(bossHp, 8, DPK_INT, 100) \
	X(bossStr, 8, DPK_INT, 100) \
	X(summonMotion, 2, DPK_INT, 30) \
	X(slimeMotion, 1, DPK_UINT, 8) \
	X(enemyAttackPattern, 2, DPK_INT, 8620) \
	X(enemyIconZoom, 4, DPK_FLOAT, 431) \
	X(enemyZoom, 4, DPK_FLOAT, 431) \
	X(enemyBossZoom, 4, DPK_FLOAT, 431) \
	X(enemyData, 2, DPK_INT, 3448) \
	X(enemyStatInfo, 8, DPK_INT, 1293) \
	X(enemyAttr, 2, DPK_INT, 5136) \
	/* 끝 */

#endif
