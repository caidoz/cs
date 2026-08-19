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
//     cmfOff[i] = cmfOffBlob + cmfOffSlot[i]
//
// 호출부의 cmfOff[i][j] 는 그대로 동작한다.
//
// [슬롯과 자료는 개수가 다르다]
// 슬롯은 429개(MAXCMF)인데 서로 다른 모션 자료는 123개뿐이다. 슬롯 123부터는
// 몬스터 변종이라 앞 cmf 를 6개씩 나눠 쓴다. 그래서 여러 슬롯이 blob 의 같은
// 자리를 가리킨다. 이 별칭 구조가 예전 표에 들어 있던 것이고, 지금은
// cmfOffSlot 이 들고 있다.
//
// [언제 부르나]
// 부팅 때 한 번, 팩을 읽은 뒤에 한 번 더. 팩을 읽으면 Blob 과 Slot 이 팩
// 안쪽을 가리키게 되므로 표도 다시 채워야 한다. 이걸 안 하면 표가 옛 주소를
// 그대로 들고 있게 된다. 예전 cmfMoveInfo 가 딱 그 상태였다.
//
// 반드시 CmfRead 보다 먼저 불러야 한다. CmfRead 가 이 표를 읽는다.
//=============================================================================

const unsigned short* cmfOff[CAP_CMF];
const signed short* cmfMotionImg[CAP_CMF];
const unsigned short* cmfMotionImgCnt[CAP_CMF];
const signed short* cmfMotionImgSize[CAP_CMF];
const signed short* cmfCrashSize[CAP_CMF];
const signed short* cmfMoveInfo[CAP_CMF];
const unsigned short* cmfHeroLoop[CAP_CMF_HERO];

int cmfHeroLoopCnt = CMF_HERO_COUNT;

//표를 채운다.
//  slot 은 n칸이다. 표는 CAP칸이라 남는 칸은 0번을 가리키게 둔다.
//  잘못된 번호로 들어와도 죽지는 않게 한다.
#define FILL(TABLE, BLOB, SLOT, CAP, N) \
	{ \
		int i; \
		for (i = 0; i < (CAP); i++) \
			TABLE[i] = (BLOB) + (SLOT)[i < (N) ? i : 0]; \
	}

void CmfRelink(void)
{
	//팩이 슬롯표를 들고 있으면 그 길이가 곧 슬롯 수다. 없으면 내장 개수.
	int cells = DataPackCount("cmfOffSlot");
	int n = (cells > 0) ? cells : CMF_BUILTIN_COUNT;

	if (n > CAP_CMF)
		n = CAP_CMF;

	int hcells = DataPackCount("cmfHeroLoopIdx");
	int hn = (hcells > 1) ? hcells - 1 : CMF_HERO_COUNT;

	if (hn > CAP_CMF_HERO)
		hn = CAP_CMF_HERO;

	FILL(cmfOff, cmfOffBlob, cmfOffSlot, CAP_CMF, n);
	FILL(cmfMotionImg, cmfMotionImgBlob, cmfMotionImgSlot, CAP_CMF, n);
	FILL(cmfMotionImgCnt, cmfMotionImgCntBlob, cmfMotionImgCntSlot, CAP_CMF, n);
	FILL(cmfMotionImgSize, cmfMotionImgSizeBlob, cmfMotionImgSizeSlot, CAP_CMF, n);
	FILL(cmfCrashSize, cmfCrashSizeBlob, cmfCrashSizeSlot, CAP_CMF, n);
	FILL(cmfMoveInfo, cmfMoveInfoBlob, cmfMoveInfoSlot, CAP_CMF, n);
	FILL(cmfHeroLoop, cmfHeroLoopBlob, cmfHeroLoopIdx, CAP_CMF_HERO, hn);

	cmfHeroLoopCnt = hn;
	gTotalCmf = n;
}
