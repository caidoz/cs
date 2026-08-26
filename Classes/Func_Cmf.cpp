#include "Core.h"
#include "Func.h"
#include "Cmf.h"

//60fps 확장 데이터는 원본 한 프레임을 두 칸으로 늘렸다. 두 칸의 이동량을
//기준 프레임(첫 칸)에 모두 모으고 보간 프레임(둘째 칸)은 움직이지 않게 한다.
//두 칸의 합은 그대로 보존하므로 원본의 1 * _2X 이동량도 다시 2가 된다.
static void FoldCmfMovePair(signed short* first, signed short* tween)
{
	if (*first >= 100 || *first <= -100) {
		*tween = 0;
		return;
	}
	if (*tween >= 100 || *tween <= -100) {
		*first = *tween;
		*tween = 0;
		return;
	}

	*first = (signed short)((int)*first + (int)*tween);
	*tween = 0;
}

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
		int stateFrames = cmfMoveInfo[idx][dataPos];
		if (dataIdx >= MAXSTATUS || stateFrames * 3 + 2 > 1024) {
			CCLOG("CmfRead: cmf %d state %d exceeds runtime buffer (frames=%d)",
				idx, dataIdx, stateFrames);
			break;
		}
		for (i = dataPos; i < dataPos + (stateFrames * 3 + 2); i++)
			cmf_status_data[wh][dataIdx][i - dataPos] = cmfMoveInfo[idx][i];

		//[count, condition, motion[count], dx[count], dy[count]]에서 X/Y를
		//각각 두 칸씩 접는다. 홀수 번째(보간) 프레임의 이동값은 항상 0이다.
		for (i = 0; i < stateFrames; i += 2) {
			int dxPos = 2 + stateFrames + i;
			int dyPos = 2 + stateFrames * 2 + i;
			if (i + 1 < stateFrames) {
				FoldCmfMovePair(&cmf_status_data[wh][dataIdx][dxPos], &cmf_status_data[wh][dataIdx][dxPos + 1]);
				FoldCmfMovePair(&cmf_status_data[wh][dataIdx][dyPos], &cmf_status_data[wh][dataIdx][dyPos + 1]);
			}
		}

		dataPos += stateFrames * 3 + 2;
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
