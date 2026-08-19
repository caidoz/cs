#include "../Def.h"
#include "MapBlob.h"
#include "DataCount.h"
#include "DataPack.h"

//=============================================================================
// 지도 표 채우기
//
// CmfLink.cpp 와 같은 얼개다. 자세한 이유는 그쪽 주석을 보라.
//
// 예전에는 MapData.h 안에서 { ma0, ma1, ... } 하고 주소를 늘어놓았다.
// 주소라 팩에 못 담고, const 라 내부 링크여서 헤더를 포함하는 .cpp 마다
// 한 벌씩 복제됐다.
//
// 이제 자료는 MapBlob 하나에 이어붙어 있고, 표는 여기서 채운다.
//=============================================================================

const unsigned char* mapPtr[CAP_MAP];
const unsigned char* mapTilePtr[CAP_MAP];
const unsigned char* mapRectPtr[CAP_MAP];
const signed short* mapBackPtr[CAP_MAP];
const signed short* mapObjPtr[CAP_MAP];
const signed short* mapNeutralPtr[CAP_MAP];
const unsigned short* mapEnemyPtr[CAP_MAP];

//표에 남는 칸은 0번을 가리키게 둔다. 잘못된 번호로 들어와도 죽지는 않는다.
#define FILL(TABLE, BLOB, IDX, N) \
	{ \
		int i; \
		for (i = 0; i < CAP_MAP; i++) \
			TABLE[i] = (BLOB) + (IDX)[i < (N) ? i : 0]; \
	}

void MapRelink(void)
{
	//팩이 idx 를 들고 있으면 그 길이가 곧 맵 개수다. 없으면 내장 개수.
	int cells = DataPackCount("mapPtrIdx");
	int n = (cells > 1) ? cells - 1 : MAP_BUILTIN_COUNT;

	if (n > CAP_MAP)
		n = CAP_MAP;

	FILL(mapPtr, mapPtrBlob, mapPtrIdx, n);
	FILL(mapTilePtr, mapTilePtrBlob, mapTilePtrIdx, n);
	FILL(mapRectPtr, mapRectPtrBlob, mapRectPtrIdx, n);
	FILL(mapBackPtr, mapBackPtrBlob, mapBackPtrIdx, n);
	FILL(mapObjPtr, mapObjPtrBlob, mapObjPtrIdx, n);
	FILL(mapNeutralPtr, mapNeutralPtrBlob, mapNeutralPtrIdx, n);
	FILL(mapEnemyPtr, mapEnemyPtrBlob, mapEnemyPtrIdx, n);

	gTotalMap = n;
}
