#include "Core.h"
#include "Func.h"
#include "Cmf.h"

void CmfRead(int wh, int idx)
{

	cmfLoaded[wh] = idx;
	old_cmf_ptr[wh] = 0;
	cmf_m_cnt[wh] = cmfTotalMotion[idx];
	cmf_i_cnt[wh] = cmfTotalOff[idx];
	cmf_v_cnt[wh] = cmfVar[idx];
	memcpy(&cmf_i_div[wh][1], &cmfImgOff[idx * 5], 5 * 2);
	cmf_i_div[wh][0] = cmf_i_div[wh][1];
	cmf_i_div[wh][1] = MONSTER_IMG + wh;
	cmd_i_offset[wh] = cmfOff[idx];
	//바로 아래에서 상수 테이블을 가리키게 덮어쓰므로 할당은 통째로 새는 값이었다.
	cmd_m_cnt[wh] = cmfMotionImgCnt[idx];
	cmd_m_crash[wh] = cmfCrashSize[idx];
	cmd_m_img[wh] = cmfMotionImg[idx];

	int dataPos = 0;
	int dataIdx = 0;
	int i;
	while (cmfMoveInfo[idx][dataPos] >= 0) {
		for (i = dataPos; i < dataPos + (cmfMoveInfo[idx][dataPos] * 3 + 2); i++)
			cmf_status_data[wh][dataIdx][i - dataPos] = cmfMoveInfo[idx][i];
		dataPos += cmfMoveInfo[idx][dataPos] * 3 + 2;
		dataIdx++;
	}

	dataPos++;

	cmf_change_data[wh] = &cmfMoveInfo[idx][dataPos];
}

//히어로의 대기/걷기/달리기/수영은 mv 데이터가 아니라 코드가 모션을 직접 골라 쓴다.
//60프레임용으로 4배 늘린 순환표가 있으면 매 프레임 한 칸씩 넘겨주고,
//아직 30프레임 데이터인 cmf는 -1을 돌려줘서 호출한 쪽이 예전 식을 쓰게 한다.
int GetHeroLoopMotion(int cmfSlot, int chain, int frameIdx)
{
	int idx;

	if (cmfSlot < 0 || cmfSlot >= REALMAXCMF)
		return -1;

	idx = cmfLoaded[cmfSlot];

	if (idx < 0 || idx >= cmfHeroLoopCnt || cmfHeroLoop[idx] == 0)
		return -1;

	if (frameIdx < 0)
		frameIdx = -frameIdx;

	return cmfHeroLoop[idx][chain * HEROLOOP_FRAME + frameIdx % HEROLOOP_FRAME];
}
