#pragma once

#ifndef _DATA_MAPBLOB_H_
#define _DATA_MAPBLOB_H_

//tools/content/pack_map.py 가 생성한다. 직접 고치지 말 것.
//
//Classes/Write.h 에 흩어져 있던 지도 배열을 가족별로 하나씩 이어붙인
//것이다. 어느 맵이 어디서 시작하는지는 <이름>Idx 가 들고 있다.
//
//    i번 맵의 자료 = Blob[Idx[i]] .. Blob[Idx[i + 1]] 앞까지
//
//평범한 1차원 배열이라 팩에 그대로 들어간다. 표(mapPtr 등)는 부팅 때
//MapRelink() 가 이 둘로 채운다.

#include "../Def.h"

extern const unsigned char* mapPtrBlob;
enum { mapPtrBlob_COUNT = 246959 };

extern const unsigned int* mapPtrIdx;
enum { mapPtrIdx_COUNT = 426 };

extern const unsigned char* mapTilePtrBlob;
enum { mapTilePtrBlob_COUNT = 246959 };

extern const unsigned int* mapTilePtrIdx;
enum { mapTilePtrIdx_COUNT = 426 };

extern const unsigned char* mapRectPtrBlob;
enum { mapRectPtrBlob_COUNT = 1058 };

extern const unsigned int* mapRectPtrIdx;
enum { mapRectPtrIdx_COUNT = 426 };

extern const signed short* mapBackPtrBlob;
enum { mapBackPtrBlob_COUNT = 15581 };

extern const unsigned int* mapBackPtrIdx;
enum { mapBackPtrIdx_COUNT = 426 };

extern const signed short* mapObjPtrBlob;
enum { mapObjPtrBlob_COUNT = 1963 };

extern const unsigned int* mapObjPtrIdx;
enum { mapObjPtrIdx_COUNT = 426 };

extern const signed short* mapNeutralPtrBlob;
enum { mapNeutralPtrBlob_COUNT = 981 };

extern const unsigned int* mapNeutralPtrIdx;
enum { mapNeutralPtrIdx_COUNT = 426 };

extern const unsigned short* mapEnemyPtrBlob;
enum { mapEnemyPtrBlob_COUNT = 505 };

extern const unsigned int* mapEnemyPtrIdx;
enum { mapEnemyPtrIdx_COUNT = 426 };

//맵 개수. 표를 채울 때 쓴다.
enum { MAP_BUILTIN_COUNT = 425 };

#endif

