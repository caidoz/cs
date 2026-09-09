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

		//---- 개구리 공격의 보간 프레임을 A2 로 되돌린다 ----
		//
		//60fps 로 늘리면서 원본 한 칸이 두 칸이 됐고, 둘째 칸(보간)에는
		//A2_1/A2_2/A2_3(72/73/74)라는 중간 그림이 들어갔다. 그 그림들의
		//입이 어그러져 있다. A2(10) 한 장은 멀쩡하다.
		//
		//그림을 다시 그리기 전까지는 그 자리에 A2 를 그대로 쓴다. 프레임
		//수와 이동값은 안 건드리므로 동작 길이와 거리는 그대로다.
		//
		//데이터가 아니라 여기서 고치는 것은, cmfMoveInfo 가 도구로 새로
		//뽑히는 표라 손으로 고쳐두면 다음 생성 때 날아가기 때문이다.
		//그림이 고쳐지면 이 블록만 지우면 된다.
		if (wh == CMF_FROG) {
			for (i = 0; i < stateFrames; i++) {
				signed short* m = &cmf_status_data[wh][dataIdx][2 + i];

				if (*m == PO_C5_A2_1 || *m == PO_C5_A2_2 || *m == PO_C5_A2_3)
					*m = PO_C5_A2;
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
