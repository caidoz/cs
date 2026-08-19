#include "../Def.h"
#include "CmfBlob.h"
#include "DataCount.h"
#include "DataPack.h"

#include <string.h>

//=============================================================================
// cmf 표 채우기
//
// cmfOff 같은 표는 예전에 CmfData.h 안에서 { c0Off, c1Off, ... } 하고 주소를
// 늘어놓은 것이었다. 주소라 팩에 못 담고, const 라 내부 링크여서 헤더를
// 포함하는 .cpp 마다 복제됐다.
//
// 이제 자료는 CmfBlob 하나에 이어붙어 있고, 표는 여기서 채운다.
//
//     cmfOff[i] = cmfOffBlob + cmfOffIdx[i]
//
// 호출부의 cmfOff[i][j] 는 그대로 동작한다.
//
// 부팅 때 한 번, 팩을 읽은 뒤에 한 번 더 부른다. 팩을 읽으면 Blob 과 Idx 가
// 팩 안쪽을 가리키게 되므로, 표도 다시 채워야 한다. 이걸 안 하면 표가 옛
// 주소를 그대로 들고 있게 된다. 예전 cmfMoveInfo 가 딱 그 상태였다.
//=============================================================================

const unsigned short* cmfOff[CAP_CMF];
const signed short* cmfMotionImg[CAP_CMF];
const unsigned short* cmfMotionImgCnt[CAP_CMF];
const signed short* cmfMotionImgSize[CAP_CMF];
const signed short* cmfCrashSize[CAP_CMF];
const signed short* cmfMoveInfo[CAP_CMF];
const unsigned short* cmfHeroLoop[CAP_CMF_HERO];

int cmfHeroLoopCnt = CMF_HERO_COUNT;

//한 가족을 채운다.
//  idx 는 n + 1 칸이다. 마지막 칸은 blob 의 끝을 가리킨다.
//  표에 남는 칸은 0번을 가리키게 둔다. 잘못된 번호로 들어와도 죽지는 않는다.
#define FILL(TABLE, BLOB, IDX, CAP, N) \
	{ \
		int i; \
		for (i = 0; i < (CAP); i++) \
			TABLE[i] = (BLOB) + (IDX)[i < (N) ? i : 0]; \
	}

void CmfRelink(void)
{
	//팩이 idx 를 들고 있으면 그 길이가 곧 cmf 개수다. 없으면 내장 개수.
	int cells = DataPackCount("cmfOffIdx");
	int n = (cells > 1) ? cells - 1 : CMF_BUILTIN_COUNT;

	if (n > CAP_CMF)
		n = CAP_CMF;

	int hcells = DataPackCount("cmfHeroLoopIdx");
	int hn = (hcells > 1) ? hcells - 1 : CMF_HERO_COUNT;

	if (hn > CAP_CMF_HERO)
		hn = CAP_CMF_HERO;

	FILL(cmfOff, cmfOffBlob, cmfOffIdx, CAP_CMF, n);
	FILL(cmfMotionImg, cmfMotionImgBlob, cmfMotionImgIdx, CAP_CMF, n);
	FILL(cmfMotionImgCnt, cmfMotionImgCntBlob, cmfMotionImgCntIdx, CAP_CMF, n);
	FILL(cmfMotionImgSize, cmfMotionImgSizeBlob, cmfMotionImgSizeIdx, CAP_CMF, n);
	FILL(cmfCrashSize, cmfCrashSizeBlob, cmfCrashSizeIdx, CAP_CMF, n);
	FILL(cmfMoveInfo, cmfMoveInfoBlob, cmfMoveInfoIdx, CAP_CMF, n);
	FILL(cmfHeroLoop, cmfHeroLoopBlob, cmfHeroLoopIdx, CAP_CMF_HERO, hn);

	cmfHeroLoopCnt = hn;
	gTotalCmf = n;
}
