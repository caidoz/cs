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
	cmd_m_cnt[wh] = new unsigned short[sizeof(cmfMotionImgCnt[idx])];
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