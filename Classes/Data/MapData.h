#pragma once
#include "../Def.h"
#include "../Write.h"

#ifndef _DATA_MAP_H_
#define _DATA_MAP_H_

//---- 지도 표 ----
//
//예전에는 여기에 { ma0, ma1, ... } 하고 주소를 늘어놓았다. 주소라 팩에
//못 담고, const 라 내부 링크여서 이 헤더를 포함하는 .cpp 마다 한 벌씩
//복제됐다.
//
//이제 자료는 MapBlob 하나에 이어붙어 있고, 부팅 때와 팩을 읽은 뒤에
//MapRelink() 가 이 표를 채운다. 호출부의 mapPtr[i][j] 는 그대로다.

extern const unsigned char* mapPtr[CAP_MAP];
extern const unsigned char* mapTilePtr[CAP_MAP];
extern const unsigned char* mapRectPtr[CAP_MAP];
extern const signed short* mapBackPtr[CAP_MAP];
extern const signed short* mapObjPtr[CAP_MAP];
extern const signed short* mapNeutralPtr[CAP_MAP];
extern const unsigned short* mapEnemyPtr[CAP_MAP];

//표를 채운다. 부팅 때 한 번, 팩을 읽을 때마다 한 번 부른다.
void MapRelink(void);
extern const unsigned int* mapRectSize;
enum { mapRectSize_COUNT = 425 };

extern const unsigned int* mapBackSize;
enum { mapBackSize_COUNT = 425 };

extern const unsigned int* mapObjSize;
enum { mapObjSize_COUNT = 425 };

extern const unsigned int* mapNeutralSize;
enum { mapNeutralSize_COUNT = 425 };

extern const unsigned int* mapEnemySize;
enum { mapEnemySize_COUNT = 425 };


//맵 배경 기본 색상
extern const unsigned int* mapColor;
enum { mapColor_COUNT = 19 };


extern const signed char* doorToKey;
enum { doorToKey_COUNT = 16 };

extern const unsigned char* doorArray;
enum { doorArray_COUNT = 40 };

extern const unsigned char* pushArray;
enum { pushArray_COUNT = 2 };

extern const unsigned char* boxStar;
enum { boxStar_COUNT = 56 };

extern const unsigned char* boxArray;
enum { boxArray_COUNT = 4 };

extern const unsigned char* markArray;
enum { markArray_COUNT = 7 };

extern const unsigned char* itemArray;
enum { itemArray_COUNT = 6 };

extern const unsigned char* dianaStoneArray;
enum { dianaStoneArray_COUNT = 1 };

extern const unsigned char* magmaArray;
enum { magmaArray_COUNT = 1 };

extern const unsigned char* wormHoleArray;
enum { wormHoleArray_COUNT = 3 };

extern const unsigned char* warpArrayType;
enum { warpArrayType_COUNT = 57 };

extern const signed short* warpArray;
enum { warpArray_COUNT = 280 };

extern const unsigned short* backObjImg;
enum { backObjImg_COUNT = 1148 };

extern const unsigned short* bgObjOff;
enum { bgObjOff_COUNT = 656 };

extern const signed short* bgObjMI;
enum { bgObjMI_COUNT = 3220 };

extern const unsigned short* sunShineOff;
enum { sunShineOff_COUNT = 24 };

extern const signed short* sunShineMI;
enum { sunShineMI_COUNT = 504 };

extern const unsigned char* sunShineMIC;
enum { sunShineMIC_COUNT = 44 };

extern const unsigned char* sateliteMotionCnt;
enum { sateliteMotionCnt_COUNT = 62 };


extern const signed short* neutralData;
enum { neutralData_COUNT = 506 };


extern const unsigned short* mapBg;
enum { mapBg_COUNT = 76 };

extern const signed short* waterfallMI;
enum { waterfallMI_COUNT = 48 };

extern const unsigned short* atlanticeImg;
enum { atlanticeImg_COUNT = 80 };

extern const unsigned short* swampImg;
enum { swampImg_COUNT = 52 };

extern const signed char* swampSplash;
enum { swampSplash_COUNT = 56 };

extern const unsigned char* swampBubble;
enum { swampBubble_COUNT = 164 };

extern const signed char* sunShineMotion;
enum { sunShineMotion_COUNT = 48 };

extern const unsigned char* sewageFallHeight;
enum { sewageFallHeight_COUNT = 10 };


extern const unsigned char* tileEmpty;
enum { tileEmpty_COUNT = 1672 };
#endif