#include "Core.h"
#include "Data.h"
#include "Func.h"


// =========================
// 캐릭터 점수 계산 (등급 기준)
// =========================
int GetUnitScore(OBJECT* pObj)
{
	int idx = GetCrewIdxFromType(pObj->type);
	if (idx < 0) {
		// 매칭 실패하면 최하점 처리 (정렬에서 맨 앞으로 오게)
		return -1000000;
	}

	int star = enemyData[crewData[idx * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_STAR];       // 1~9
	int castle = crewData[crewData[idx * CREWDATASIZE + CREWDATA_CARDBG] * ENEMYDATASIZE + ENEMYDATA_STAR];  // 0~TOTALCASTLE-1

	// 별이 높을수록 우선, 별이 같으면 후반 지역(castle 큰 값) 우선
	return star * 100 + castle;
}

// crewDataKey -> 점수(별*100 + 지역)
static inline int ScoreFromCrewKey(int key)
{
	int star = enemyData[crewData[key * CREWDATASIZE + CREWDATA_TYPE] * ENEMYDATASIZE + ENEMYDATA_STAR];
	int region = enemyData[crewData[key * CREWDATASIZE + CREWDATA_CARDBG] * ENEMYDATASIZE + ENEMYDATA_STAR];
	return star * 100 + region;
}

// crewDataKey -> type
static inline int TypeFromCrewKey(int key)
{
	return crewData[key * CREWDATASIZE + CREWDATA_TYPE];
}

// type으로 현재 ao[CREW + k]에서 매칭되는 k(aoOffset)를 찾는다.
// used[k]=true면 이미 매칭된 슬롯이므로 건너뜀.
static int FindCrewAoOffsetByType(int type, bool used[], int maxCrew)
{
	for (int k = 0; k < maxCrew; k++) {
		if (used[k]) continue;
		OBJECT* u = &ao[CREW + k];
		if (!u->active) continue;
		if (u->type == type) return k;
	}
	return -1;
}

void DecideRouletteResult(void)
{
	gRouletteResultValid = false;

	// 로딩에서 뽑힌 크루 수(최대 9)가 crewCnt라고 가정
	// (리더 포함 9칸)
	if (crewCnt < MINCREW) return;

	// -----------------------------
	// 1) robin.slotCrew[0..crewCnt-1]를 점수로 정렬 (오름차순)
	// -----------------------------
	std::vector<int> idx;
	idx.reserve(crewCnt);
	for (int i = 0; i < crewCnt; i++) idx.push_back(i);

	std::sort(idx.begin(), idx.end(), [&](int a, int b) {
		int keyA = robin.slotCrew[a]; // crewDataKey
		int keyB = robin.slotCrew[b];
		int sA = ScoreFromCrewKey(keyA);
		int sB = ScoreFromCrewKey(keyB);
		if (sA != sB) return sA < sB;
		// tie-break: crewId나 인덱스로 안정화
		return a < b;
		});

	// -----------------------------
	// 2) 정렬된 robin.slotCrew 인덱스 -> 실제 aoOffset(k)로 매핑
	// -----------------------------
	// 룰렛 시스템은 gRouletteStartAoOffset / gRouletteResultAoOffset에
	// "CREW 배열 내부의 offset(k)"를 넣어야 함.
	bool used[MAXCREW] = { false, };

	auto MapCrewIndexToAoOffset = [&](int crewIndex)->int {
		if (crewIndex < 0 || crewIndex >= crewCnt) return -1;

		int type = robin.slotCrew[crewIndex];   // ✅ robin.slotCrew는 type
		if (type < 0 || type >= TOTALENEMY) return -1;

		int k = FindCrewAoOffsetByType(type, used, MAXCREW);
		if (k >= 0) {
			used[k] = true;
			return k;
		}

		// ✅ fallback 1: 남아있는 아무 ao 슬롯이라도 하나 집기 (중복 방지)
		for (int t = 0; t < MAXCREW; ++t) {
			if (used[t]) continue;
			if (!ao[CREW + t].active) continue;
			used[t] = true;
			return t;
		}

		// ✅ fallback 2: 그냥 실패 처리(그 프레임 스킵)
		return -1;
		};

	// 시작 3명 = 최약 3개 (crewIndex 저장)
	for (int r = 0; r < TOTALREEL; r++) {
		gRouletteStartAoOffset[r] = idx[r]; // <-- crewIndex
	}

	// 결과 3명 = 최강 3개 (crewIndex 저장)
	for (int r = 0; r < TOTALREEL; r++) {
		gRouletteResultAoOffset[r] = idx[crewCnt - TOTALREEL + r]; // <-- crewIndex
	}

	// -----------------------------
	// 5) 유효
	// -----------------------------
	gRouletteResultValid = true;

	//TEST
	gRouletteStartAoOffset[0] = 0;
	gRouletteStartAoOffset[1] = 1;
	gRouletteStartAoOffset[2] = 2;
	//TEST
	//gRouletteResultAoOffset[0] = 0;
	//gRouletteResultAoOffset[1] = 1;
	//gRouletteResultAoOffset[2] = 2;
}

void InitRouletteJump(void)
{
	// [MOD-G2] 슬롯 시작 시 종료 딜레이 리셋
	sEndDelayLeft = -1;

	for (int i = 0; i < TOTALREEL; i++) {
		gReelJump[i].state = JS_IDLE;
		gReelJump[i].jumpY = 0.0f;
		gReelJump[i].jumpV = 0.0f;
		gReelJump[i].maxJumpY = 1.0f;

		gReelJump[i].curShowPos = 0;
		gReelJump[i].landedPos = 0;
		gReelJump[i].lastSwapF = -9999;

		gReelJump[i].started = false;
		gReelJump[i].holdEndFrame = -1;

		gReelJump[i].flipLR = false;
		gReelJump[i].lastFlipF = -9999;
		gReelJump[i].flashEndF = -1;
		gReelJump[i].vortexEndF = -1;

		gReelJump[i].flipSquashEndF = -1;
		gReelJump[i].flipSquashLen = -3;

		gRouletteSkillIdx[i] = -1;
	}

	rouletteFrame = 0;
}

void RouletteAttackStart(void)
{
	int i, j;
	int crewIdx;

	if (attackDelay)
		return;
	//방어가 되는 케이스
	//애초에 공격을 당해서 생산불능인 상태면 대상에서 제외
	//생산가능한 상태인 대상을 공격했을 때 방어막이 있으면 실패
	//방어막이 없으면 성공
	rouletteSequence = 0;

	j = 0;

	//CREW가 아예 없는 경우는 히어로가 바로 공격한다.
	if (crewCnt == 0) {
		attackSequence = ATTACKSEQUENCE_ACTION;
		InitBar(BAR_BATTLECOIN);
	}
	//CREW가 있지만 3마리 이하라서 룰렛을 안돌리면 그냥 공격을 해준다.
	else if (crewCnt < MAXCREW)
	{
		attackSequence = ATTACKSEQUENCE_ACTION;
		//ao[NEUTRAL].status = BOXSTATUS_OPENED;
		InitBar(BAR_BATTLECOIN);
		//그 다음에는 전체 순서를 정해준다.
		//일단 크류를 배치했고
		for (i = 0; i < MAXCREW; i++) {
			if (ao[CREW + i].active) {
				turnList[j] = CREW + i;
				j++;
			}
		}
	}
	//CREW가 6마리 이상이면 룰렛을 돌리고 공격해준다.
	else {
		attackSequence = ATTACKSEQUENCE_SLOT;
		//여기서 어떤 CREW를 뽑을건지 결정한다.
		DecideRouletteResult();
		//그 다음에는 전체 순서를 정해준다.
		//일단 크류를 배치했고
		for (i = 0; i < TOTALREEL; i++) {
			turnList[j] = CREW + gRouletteResultAoOffset[i];
			j++;
		}
	}

	//그 다음에는 히어로를 더 해준다.
	for (i = MAXX; i >= ROBIN; i--) {
		if (ao[i].active) {
			turnList[j] = i;
			j++;
		}
	}
	//적턴
	enemyTurnStartIdx = j;

	//그 다음에 적들을 넣어준다.
	for (i = ENEMY; i < NEUTRAL; i++) {
		//적이고 본체면
		if (ao[i].active && ao[i].mom == i) {
			turnList[j] = i;
			j++;
		}
	}
	//최대턴
	totalTurn = j;
	//어떤놈이 시작할거냐.
	turnListIdx = 0;
	turn = turnList[turnListIdx];
	crewIdx = GetCrewIdxFromType(ao[turn].type);
	ao[turn].currentSkill = crewData[crewIdx * CREWDATASIZE + CREWDATA_SKILL1 + GetSameRouletteCnt(turn - CREW) - 1];
	ao[turn].etc = enemyAttackPattern[ao[turn].type * ATTACKPATTERNTOTALDATASIZE + 2 + ATTACKPATTERNDATASIZE * GetSameRouletteCnt(turn - CREW) - 1];
	ao[turn].frame = 0;
	ao[turn].mainFrame = 0;
	//if (turn >= CREW && turn < PLAYERALL) {
	//	ao[turn].status = 
	//}

	sequenceFrame = -1;

	rouletteNum = 0;
	rouletteNumSub = 0;
	rouletteNumBar = 0;
	rouletteNumPvpBar = 0;


	PlayMusic(M_SHAKIN);

	joyStickAni++;
	joyStickDir = RIGHT;

	SetWheel();

	wheelSpeed = WHEELINITSPEED;
	totalRouletteCnt = TOTALROULETTECHANCE;

	actionCardCnt = 0;

	InitRouletteJump();

	AddBar(&bar[BAR_HEART], -betHeart[bet], BARFRAME);
}

//현재 캐릭터 타입과 같은 개수를 구해라
int GetSameRouletteCnt(int objIdx)
{
	int i, j = 0;

	for (i = 0; i < TOTALREEL; i++) {
		if (gRouletteResultAoOffset[i] == objIdx) {
			j++;
		}
	}

	return j;
}

// count=1 -> 그대로, count=2 -> 레벨2, count=3 -> 레벨3
int UpgradeSkillIdx(int reelIdx, int count)
{
	return crewData[GetCrewIdxFromType(ao[(CREW + gRouletteResultAoOffset[reelIdx])].type) * CREWDATASIZE + CREWDATA_SKILL1 + count - 1];
}

void RouletteDraw(int x, int y, float zoom,
	cocos2d::RenderTexture* cvtDest,
	cocos2d::Layer* cvtLayer,
	bool buffering)
{
	// -----------------------------
	// [CFG] 점프 연출 파라미터 (짧고 탄력)
	// -----------------------------
	static const float AIRTIME_FACTOR = 1.18f;

	const float GRAVITY_BASE = 1.55f;
	const float JUMP_V0_BASE = 16.5f;

	const float GRAVITY = GRAVITY_BASE * AIRTIME_FACTOR;
	const float JUMP_V0 = JUMP_V0_BASE * sqrtf(AIRTIME_FACTOR);
	const float MAX_JUMP_Y = (JUMP_V0 * JUMP_V0) / (2.0f * GRAVITY);

	auto GetSwapInterval = [&](bool slowMode)->int { return slowMode ? 4 : 1; };


	// -----------------------------
// [GUARD]
// -----------------------------
//if (!gRouletteResultValid) return;
	//if (crewCnt < MINCREW) return;

	auto WrapCrew = [&](int v)->int {
		v %= crewCnt;
		if (v < 0) v += crewCnt;
		return v;
		};

	bool isSlotPlaying = (attackSequence >= ATTACKSEQUENCE_SLOT);

	if (ao[PLAYER].active == false)
		return;

	// -----------------------------
// [INTRO POP] 1회 등장: 밖에서 yDest로 "등장" -> 점프/바운스
// -----------------------------
	static bool  sIntroDone = false;

	static bool  sIntroStarted = false;
	static float sIntroY = 0.0f;
	static float sIntroV = 0.0f;     // 현재 속도(인트로 전용)
	static float sIntroV_atDest = 0.0f; // yDest 통과 속도(= 점프 크기 결정)
	static int   sIntroBounceLeft = 1;


	// -----------------------------
// [INTRO ONLY] 최초 등장 1회만 (단일 포물선)
// -----------------------------
	if (!isSlotPlaying && !sIntroDone)
	{
		const float yDest = (float)y;

		// ✅ 화면 밖 시작 거리(등장 거리)
		const float INTRO_FROM_DIST = 220.0f * _2X;

		// ✅ yDest를 얼마나 "넘어서" 올라갈지(등장거리 대비)
		// 너 요구: "지금의 1/5도 안되게" => 0.12~0.18 추천
		const float JUMP_H_RATIO = 0.15f;

		// ✅ y축 방향: 위로 갈수록 y가 증가하면 +1, 감소하면 -1
		const float Y_UP_SIGN = +1.0f;

		// 시작점(화면 밖 아래에서 출발해서 위로 올라오게)
		const float yStartOutside = yDest - (INTRO_FROM_DIST * Y_UP_SIGN);

		// 인트로 시작 1회 초기화
		if (!sIntroStarted)
		{
			sIntroStarted = true;
			sIntroBounceLeft = 1;

			sIntroY = yStartOutside;

			const float GRAV = 1.55f * _2X;

			// 등장거리
			const float riseDist = fabsf(yDest - yStartOutside);

			// yDest를 "넘어서" 올라갈 높이(점프 높이)
			const float jumpH = riseDist * JUMP_H_RATIO;

			// 핵심:
			// yDest에서의 위로 속도 Vdest를 정하면,
			// yDest를 통과해서 추가로 올라갈 높이는 jumpH = Vdest^2/(2G)
			// => Vdest = sqrt(2GjumpH)
			sIntroV_atDest = sqrtf(2.0f * GRAV * jumpH);

			// 시작점에서 yDest까지 올라오며 감속되므로,
			// 시작 속도 V0는 에너지 보존으로:
			// V0^2 = Vdest^2 + 2G*riseDist
			const float V0 = sqrtf(sIntroV_atDest * sIntroV_atDest + 2.0f * GRAV * riseDist);

			sIntroV = V0;  // ✅ 여기서부터 끝까지 "한 번의 포물선" (yDest에서 속도 재부여 X)			
		}

		// ---- 물리 업데이트(단일 포물선)
		{
			const float GRAV = 1.55f * _2X;

			// 위치/속도 업데이트
			sIntroY += sIntroV * Y_UP_SIGN;
			sIntroV -= GRAV;

			// 착지 판정: 내려오는 중에 yDest를 "지나치면" 착지
			bool falling = (sIntroV < 0.0f);

			bool passedDest =
				(Y_UP_SIGN > 0.0f) ? (sIntroY <= yDest) : (sIntroY >= yDest);

			if (falling && passedDest)
			{
				// 착지 고정
				sIntroY = yDest;

				if (sIntroBounceLeft > 0)
				{
					sIntroBounceLeft--;

					// ✅ 바운스는 "착지 순간"에만 1회
					// 속도를 새로 크게 주면 또 이상해지니,
					// 현재 낙하 속도의 일부만 반발시키는 게 자연스럽다.
					// (sIntroV는 음수 상태이므로 abs해서 올림)
					const float BOUNCE_MUL = 0.28f; // 0.22~0.33 사이 취향
					float fallSpeed = -sIntroV;     // 양수
					sIntroV = fallSpeed * BOUNCE_MUL;

					// 바운스가 너무 커지면(혹시) 상한
					if (sIntroV > sIntroV_atDest * 0.40f)
						sIntroV = sIntroV_atDest * 0.40f;
				}
				else
				{
					// 종료
					sIntroDone = true;
					sIntroStarted = false;
					sIntroV = 0.0f;
					sIntroY = yDest;
					touchDisable = false;

					InitBar(BAR_HEARTBET);
					InitBar(BAR_PLAY);
				}
			}
		}

		// 최종 적용
		y = (int)sIntroY;
	}

	// -----------------------------
	// [FRAME] slotFrame 증가는 SLOT일 때만
	// -----------------------------
	if (attackSequence == ATTACKSEQUENCE_SLOT) {
		ScreenDarken(SCREENDARKEN);
		bar[BAR_ROULETTE].front = true;
		slotFrame++;
	}

	// -----------------------------
	// [DRAW] 슬롯 베이스
	// -----------------------------
	DrawImage(SLOTSIZE_X, SLOTSIZE_Y, 0, 0,
		x - (float)SLOTSIZE_X / 2 * zoom, y,
		false, false, false, false, false,
		zoom, sprite[SLOT_IMG], cvtDest, cvtLayer, SLOT_IMG, buffering);

	// ============================================================
	// [SKILL PHASE] 합성/임팩트/발사 상태 머신
	// ============================================================
	enum SkillPhase { SP_NONE = 0, SP_MERGE, SP_IMPACT, SP_DISPATCH, SP_DONE };
	static SkillPhase sSkillPhase = SP_NONE;
	static int sSkillPhaseStartFrame = 0;

	static int sMergeFrames = 10;
	static int sImpactFrames = 0;
	static int sEndDelayFrames = 10;
	static int sEndDelayLeft = -1;

	// “유니크 스킬 그룹” 정보(최대 3그룹)
	static int sGroupCount = 0;                    // 1~3
	static int sGroupBaseSkill[3] = { -1,-1,-1 };  // 원본 skillIdx(키)
	static int sGroupDupCount[3] = { 1, 1, 1 };    // 1/2/3
	static int sGroupUpSkill[3] = { -1,-1,-1 };    // 업그레이드된 skillIdx
	static int sGroupRepReel[3] = { -1,-1,-1 };    // 대표 릴 index
	static int sGroupRepMarkId[3] = { -1,-1,-1 };  // (미사용 유지)

	// DISPATCH 1회 세팅 플래그
	static bool sDispatched = false;

	// 각 릴의 center 좌표를 저장 (미사용이어도 유지)
	static int sReelCenterX[3] = { 0,0,0 };
	static int sReelCenterY[3] = { 0,0,0 };

	// ==============================
	// [PATCH] Skill merge plan & motion
	// ==============================
	static bool sMergePlanBuilt = false;      // (미사용이어도 유지)
	static bool sGroupMerged[3] = { false,false,false };
	static int  sGroupArrived[3] = { 0,0,0 };
	static int  sGroupMemberCnt[3] = { 0,0,0 };
	static int  sGroupMembers[3][3] = { { -1,-1,-1 },{ -1,-1,-1 },{ -1,-1,-1 } };

	enum MergeStep { MS_NONE = 0, MS_UP, MS_SLIDE, MS_DOWN, MS_DONE };
	static MergeStep sMergeStep[3] = { MS_NONE, MS_NONE, MS_NONE };

	static int sMergeTargetX[3] = { 0,0,0 };
	static int sMergeTargetY[3] = { 0,0,0 };

	static const int SKILL_MERGE_LIFT_Y = 64 * _2X;

	// -----------------------------
	// [EDIT-A] 리프트/모으기 상태 변수 (SP_NONE 내부 static으로 두지 말고 여기로)
	// -----------------------------
	static bool sMergeMoveCalled = false;
	static int  sMergeMoveStartFrame = 0;
	static bool sMergePostDone = false;

	static int  sMoveFrom[2] = { -1, -1 };
	static int  sMoveTo[2] = { -1, -1 };
	static int  sMoveCount = 0;

	static bool sLiftCalled = false;
	static bool sLiftHideApplied = false;
	static int  sLiftStartFrame = 0;

	// SLOT이 아니면 리셋
	static bool sSlotInited = false;
	if (!isSlotPlaying) {
		sSlotInited = false;

		sSkillPhase = SP_NONE;
		sSkillPhaseStartFrame = 0;
		sEndDelayLeft = -1;

		sGroupCount = 0;
		sMergePlanBuilt = false;

		for (int i = 0; i < 3; i++) {
			sGroupBaseSkill[i] = -1;
			sGroupDupCount[i] = 1;
			sGroupUpSkill[i] = -1;
			sGroupRepReel[i] = -1;
			sGroupRepMarkId[i] = -1;
			sReelCenterX[i] = 0;
			sReelCenterY[i] = 0;

			sGroupMerged[i] = false;
			sGroupArrived[i] = 0;
			sGroupMemberCnt[i] = 0;
			sMergeStep[i] = MS_NONE;
			for (int k = 0; k < 3; k++) sGroupMembers[i][k] = -1;
		}

		sDispatched = false;
		gRouletteSkillDispatchStarted = false;

		// [EDIT-A] 모으기/리프트 상태 초기화
		sMergeMoveCalled = false;
		sMergeMoveStartFrame = 0;
		sMergePostDone = false;
		sMoveCount = 0;
		sMoveFrom[0] = sMoveFrom[1] = -1;
		sMoveTo[0] = sMoveTo[1] = -1;

		sLiftCalled = false;
		sLiftHideApplied = false;
		sLiftStartFrame = 0;

		// ✅ 2) 로딩 상태에서도 "기본 3릴 캐릭터"는 보여줘야 함
		for (int i = 0; i < TOTALREEL; i++)
		{
			float centerX = x - (float)SLOTSIZE_X * zoom / 2 + (float)reelPostion[i * 2 + 0] * zoom;
			float centerY = y + (float)reelPostion[i * 2 + 1] * zoom;

			float baseScale = 2.5f * zoom * enemyIconZoom[ao[CREW + gRouletteStartAoOffset[i]].type];

			ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X,
				centerX - (float)12 * _2X * 2.5f * zoom,
				centerY + (float)8 * _2X * 2.5f * zoom,
				SHADOW_IMG, 2.5f * zoom, cvtDest, cvtLayer, buffering);

			DrawCmfDetail(ao[CREW + gRouletteStartAoOffset[i]].cmf,
				crewPos[ao[CREW + gRouletteStartAoOffset[i]].type * 5 + 0],
				centerX, centerY,
				RIGHT, baseScale,
				false, false, cvtDest, cvtLayer, buffering);
		}

		// ✅ 인트로 팝업은 “로딩에서 1번만”
		// 공격 눌러 SLOT 들어가도 다시 안 나오게 유지
		// (만약 UI를 완전히 닫았다가 다시 열면 초기화해야 한다면, 그 타이밍에서 sIntroDone=false 처리)
		return;
	}

	// -----------------------------
	// [INIT] SLOT 진입 1회 초기화
	// -----------------------------
	if (isSlotPlaying && !sSlotInited) {
		sSlotInited = true;

		sSkillPhase = SP_NONE;
		sSkillPhaseStartFrame = slotFrame;
		sEndDelayLeft = -1;
		sDispatched = false;

		gRouletteSkillDispatchStarted = false;

		// [EDIT-A] 모으기/리프트도 슬롯 진입 시 초기화
		sMergeMoveCalled = false;
		sMergeMoveStartFrame = 0;
		sMergePostDone = false;
		sMoveCount = 0;
		sMoveFrom[0] = sMoveFrom[1] = -1;
		sMoveTo[0] = sMoveTo[1] = -1;

		sLiftCalled = false;
		sLiftHideApplied = false;
		sLiftStartFrame = 0;

		for (int i = 0; i < 3; i++) {
			sGroupMerged[i] = false;
			sGroupArrived[i] = 0;
			sGroupMemberCnt[i] = 0;
			sMergeStep[i] = MS_NONE;
			for (int k = 0; k < 3; k++) sGroupMembers[i][k] = -1;
		}

		for (int r = 0; r < TOTALREEL; r++) {
			ReelJumpState& rs = gReelJump[r];
			rs.state = JS_IDLE;
			rs.started = false;

			rs.jumpY = 0.0f;
			rs.jumpV = 0.0f;
			rs.maxJumpY = 1.0f;

			rs.lastSwapF = -9999;
			rs.holdEndFrame = -1;

			rs.flipLR = false;
			rs.lastFlipF = -9999;
			rs.flipSquashEndF = -1;

			rs.bounceLeft = 1;

			rs.curShowPos = gRouletteStartAoOffset[r];
			rs.landedPos = gRouletteStartAoOffset[r];
		}
	}

	// -----------------------------
	// [ACTIVE] 현재 진행 중 릴 계산 (순차)
	// -----------------------------
	int activeReel = -1;
	for (int r = 0; r < TOTALREEL; r++) {
		ReelJumpState& rs = gReelJump[r];

		if (slotFrame < reelStartFrame[r]) continue;

		if (rs.state == JS_HOLD) {
			if (slotFrame < rs.holdEndFrame) { activeReel = r; break; }
			rs.state = JS_DONE;
		}

		if (rs.state != JS_DONE) { activeReel = r; break; }
	}

	// -----------------------------
	// [REEL DRAW]
	// -----------------------------
	for (int i = 0; i < TOTALREEL; i++)
	{
		ReelJumpState& rs = gReelJump[i];

		bool canStartThisReel = (slotFrame >= reelStartFrame[i]);
		bool shouldAnimate = (canStartThisReel && (i == activeReel));

		float centerX = x - (float)SLOTSIZE_X * zoom / 2 + (float)reelPostion[i * 2 + 0] * zoom;
		float centerY = y + (float)reelPostion[i * 2 + 1] * zoom;

		if (shouldAnimate)
		{
			if (!rs.started) {
				rs.started = true;
				rs.state = JS_SPINNING;

				rs.jumpY = 0.0f;
				rs.jumpV = JUMP_V0;
				rs.maxJumpY = MAX_JUMP_Y;

				rs.lastSwapF = -9999;
				rs.lastFlipF = -9999;

				rs.curShowPos = gRouletteStartAoOffset[i];
				rs.landedPos = gRouletteStartAoOffset[i];
			}

			if (rs.state == JS_SPINNING || rs.state == JS_LANDING) {
				rs.jumpY += rs.jumpV;
				rs.jumpV -= GRAVITY;

				if (rs.jumpV < 0.0f && rs.state == JS_SPINNING)
					rs.state = JS_LANDING;

				if (rs.jumpY <= 0.0f) {

					if (rs.bounceLeft > 0) {
						rs.bounceLeft--;

						rs.curShowPos = gRouletteResultAoOffset[i];
						rs.landedPos = gRouletteResultAoOffset[i];

						rs.jumpY = 0.0f;
						rs.jumpV = JUMP_V0 * 0.25f;
						rs.state = JS_LANDING;
					}
					else {
						rs.jumpY = 0.0f;
						rs.jumpV = 0.0f;

						rs.curShowPos = gRouletteResultAoOffset[i];
						rs.landedPos = gRouletteResultAoOffset[i];

						rs.state = JS_HOLD;
						rs.holdEndFrame = slotFrame + 8;

						if (!controlMark[i].frame)
						{
							gRouletteSkillIdx[i] = ao[CREW + gRouletteResultAoOffset[i]].getSkillList[0];

							float z0 = 0.10f;
							float z1 = 0.60f;

							int iconX = (int)centerX;
							int iconY = (int)(centerY + 64 * _2X);

							int markId = SetControlMark(
								iconX, iconY - 64 * _2X,
								iconX, iconY,
								iconX, iconY,
								8 * _2X, 1 * _2X,
								8 * _2X, 1 * _2X,
								FPS / 4, FPS / 4,     // ✅ 2단 시간 0
								false,
								0, 1,
								gRouletteSkillIdx[i], 1,
								z0, z1 + 0.5f, 0.10f / MOTIONDIV,
								z1 + 0.5f, z1, 0.10f / MOTIONDIV,
								false,
								false, false, false,
								CREW + gRouletteResultAoOffset[i],
								false
							);
						}
					}
				}
			}

			if (rs.jumpY > 0.01f && (rs.state == JS_SPINNING || rs.state == JS_LANDING))
			{
				bool allowShuffle = (rs.bounceLeft > 0);

				int swapInterval = GetSwapInterval(false);
				int flipInterval = 1;

				if (allowShuffle)
				{
					if (slotFrame - rs.lastSwapF >= swapInterval) {
						rs.lastSwapF = slotFrame;
						int rpos = (slotFrame * 37 + i * 101) % crewCnt;
						if (rpos == rs.curShowPos && crewCnt > 1) rpos = (rpos + 1) % crewCnt;
						rs.curShowPos = rpos;
					}

					if (slotFrame - rs.lastFlipF >= flipInterval) {
						rs.lastFlipF = slotFrame;
						rs.flipLR = !rs.flipLR;
						rs.flipSquashEndF = slotFrame + rs.flipSquashLen;
					}
				}
			}
		}

		if (rs.state == JS_HOLD && slotFrame >= rs.holdEndFrame) {
			rs.state = JS_DONE;
		}

		int showPos = (rs.state == JS_DONE || rs.state == JS_HOLD) ? rs.landedPos : rs.curShowPos;

		int aoOffset = WrapCrew(showPos);          // ✅ 여기서 결정
		OBJECT* u = &ao[CREW + aoOffset];          // ✅ 바로 사용 (type/cm f/skill 등)

		if (!u->active) continue;

		float ratio = rs.jumpY / (rs.maxJumpY > 0.01f ? rs.maxJumpY : 1.0f);
		if (ratio < 0.0f) ratio = 0.0f;
		if (ratio > 1.0f) ratio = 1.0f;


		float baseScale = 2.5f * zoom * enemyIconZoom[u->type];
		float maxScale = 4.0f * zoom * enemyIconZoom[u->type];
		float scaleT = sinf(ratio * 3.141592f * 0.5f);
		float drawScale = baseScale + (maxScale - baseScale) * scaleT;

		if (shouldAnimate && rs.flipSquashEndF >= 0 && slotFrame <= rs.flipSquashEndF) {
			int remain = rs.flipSquashEndF - slotFrame;
			int len = rs.flipSquashLen; if (len < 1) len = 1;

			float t = 1.0f - (float)remain / (float)len;
			if (t < 0.0f) t = 0.0f;
			if (t > 1.0f) t = 1.0f;

			float minMul = 0.25f;
			float wave = sinf(t * 3.141592f);
			float squashMul = minMul + (1.0f - minMul) * (1.0f - wave);
			drawScale *= squashMul;
		}

		float yPos = centerY + rs.jumpY * zoom;

		float shadowBase = 2.5f * zoom;
		float minShadow = 0.82f;
		float shadowScale = shadowBase * (minShadow + (1.0f - ratio) * (1.0f - minShadow));

		ShadowImage(24 * _2X, 16 * _2X, 1 * _2X, 1 * _2X,
			centerX - (float)12 * _2X * 2.5f * zoom,
			centerY + (float)8 * _2X * 2.5f * zoom,
			SHADOW_IMG, shadowScale, cvtDest, cvtLayer, buffering);

		int drawDir = RIGHT;
		if (shouldAnimate && rs.jumpY > 0.01f) drawDir = rs.flipLR ? LEFT : RIGHT;

		DrawCmfDetail(u->cmf,
			crewPos[u->type * 5 + 0],
			centerX, yPos,
			drawDir, drawScale,
			false, false, cvtDest, cvtLayer, buffering);
	}

	// ============================================================
	// [SKILL] 3릴 모두 DONE이면 -> 합성/임팩트/발사 진행
	// ============================================================
	bool allDone = true;
	for (int r = 0; r < TOTALREEL; r++) {
		if (gReelJump[r].state != JS_DONE) { allDone = false; break; }
	}
	if (!allDone) {
		sEndDelayLeft = -1;
		return;
	}

	bool allMarksReady = true;
	for (int r = 0; r < TOTALREEL; r++) {
		if (gRouletteSkillIdx[r] < 0) { allMarksReady = false; break; }
	}
	if (!allMarksReady) {
		return;
	}

	// -----------------------------
	// [PHASE ENTER] 그룹 계산 1회
	// -----------------------------
	if (sSkillPhase == SP_NONE)
	{
		// ============================================================
		// [EDIT-B] (1) 모으기: 2개면 왼쪽, 3개면 센터(1)로 (SetControlMark 1단 이동만)
		// ============================================================
		if (!sMergeMoveCalled)
		{
			bool eq01 = (gRouletteSkillIdx[0] >= 0 && gRouletteSkillIdx[0] == gRouletteSkillIdx[1]);
			bool eq12 = (gRouletteSkillIdx[1] >= 0 && gRouletteSkillIdx[1] == gRouletteSkillIdx[2]);
			bool eq02 = (gRouletteSkillIdx[0] >= 0 && gRouletteSkillIdx[0] == gRouletteSkillIdx[2]);

			sMoveCount = 0;
			sMoveFrom[0] = sMoveFrom[1] = -1;
			sMoveTo[0] = sMoveTo[1] = -1;

			if (eq01 && eq12) {
				sMoveFrom[sMoveCount] = 0; sMoveTo[sMoveCount] = 1; sMoveCount++;
				sMoveFrom[sMoveCount] = 2; sMoveTo[sMoveCount] = 1; sMoveCount++;
			}
			else {
				if (eq01) { sMoveFrom[sMoveCount] = 1; sMoveTo[sMoveCount] = 0; sMoveCount++; }
				else if (eq12) { sMoveFrom[sMoveCount] = 2; sMoveTo[sMoveCount] = 1; sMoveCount++; }
				else if (eq02) { sMoveFrom[sMoveCount] = 2; sMoveTo[sMoveCount] = 0; sMoveCount++; }
			}

			if (sMoveCount > 0) {
				sMergeMoveCalled = true;
				sMergeMoveStartFrame = slotFrame;

				const int MOVE_T = FPS / 2;

				for (int m = 0; m < sMoveCount; m++)
				{
					int from = sMoveFrom[m];
					int to = sMoveTo[m];

					controlMark[from].frame = 0;
					controlMark[from].frame2 = 0;

					SetControlMark(
						controlMark[from].x, controlMark[from].y,
						controlMark[to].x, controlMark[to].y,
						controlMark[to].x, controlMark[to].y,
						4 * _2X, 1 * _2X,
						0, 0,            // ✅ 2단 제거
						MOVE_T, 0,        // ✅ time2=0 (1단만)
						false,
						30, 1,
						controlMark[from].attackType, 1,
						controlMark[from].zoom, controlMark[from].zoomEnd, controlMark[from].zoomIncrement,
						controlMark[from].zoom2, controlMark[from].zoomEnd2, controlMark[from].zoomIncrement2,
						false,
						false, false, false,
						controlMark[from].owner,
						false
					);
				}
			}
		}

		gRouletteSkillDispatchStarted = true;
		sSkillPhase = SP_MERGE;
		sSkillPhaseStartFrame = slotFrame;
		sEndDelayLeft = -1;
		sDispatched = false;

		// 1) 그룹 생성(유니크 키 = 스냅샷 skillIdx)
		sGroupCount = 0;
		for (int i = 0; i < TOTALREEL; i++) {
			int skillKey = gRouletteSkillIdx[i];

			int g = -1;
			for (int k = 0; k < sGroupCount; k++) {
				if (sGroupBaseSkill[k] == skillKey) { g = k; break; }
			}

			if (g < 0) {
				g = sGroupCount++;
				sGroupBaseSkill[g] = skillKey;
				sGroupDupCount[g] = 1;
				sGroupRepReel[g] = i;
			}
			else {
				sGroupDupCount[g]++;
			}
		}

		// 2) 업그레이드 스킬 idx 계산
		int maxDup = 1;
		for (int g = 0; g < sGroupCount; g++) {
			if (sGroupDupCount[g] > maxDup) maxDup = sGroupDupCount[g];
			sGroupUpSkill[g] = sGroupBaseSkill[g] + sGroupDupCount[g] - 1;
		}

		// 3) 시간(1/2/3에 따라 길어짐)
		if (maxDup == 1) {
			gRouletteSkillDispatchStarted = true;

			sSkillPhase = SP_DISPATCH;
			sSkillPhaseStartFrame = slotFrame;

			sDispatched = false;

			// 날아가는 후딜도 짧게(원하는 만큼)
			sEndDelayFrames = FPS / 6;     // 기존 8 같은 값보다 짧게
			sEndDelayLeft = -1;

			// SP_NONE 블록 나가서 아래 DISPATCH 로직이 같은 프레임에 실행되게
		}
		else if (maxDup == 2) {
			sMergeFrames = 10 * 3 * 2;
			sImpactFrames = 16 * 2;
			sEndDelayFrames = 12 * 2;
		}
		else {
			sMergeFrames = 12 * 3 * 2;
			sImpactFrames = 26 * 2;
			sEndDelayFrames = 16 * 2;
		}

		// ============================================================
		// [EDIT-B] (2) 중복(2개 이상)만 레인 위로 올리기 (1단 이동만)
		// ============================================================
		if (!sLiftCalled && (maxDup > 1))
		{
			sLiftCalled = true;
			sLiftStartFrame = slotFrame;
			sLiftHideApplied = false;

			for (int b = 0; b < TOTALREEL; b++)
			{
				int skillKey = gRouletteSkillIdx[b];

				int gFound = -1;
				for (int g = 0; g < sGroupCount; g++) {
					if (sGroupBaseSkill[g] == skillKey) { gFound = g; break; }
				}
				if (gFound < 0) continue;

				if (sGroupDupCount[gFound] < 2) continue;

				controlMark[b].frame = 0;
				controlMark[b].frame2 = 0;

				int sx = controlMark[b].x;
				int sy = controlMark[b].y;

				int tx = sx;
				int ty = sy + (32 * _2X);

				SetControlMark(
					sx, sy,
					tx, ty,
					tx, ty,
					4 * _2X, 1 * _2X,
					4 * _2X, 1 * _2X,               // ✅ 2단 제거
					FPS / 2, FPS / 2,          // ✅ time2=0
					false,
					30, 1,
					controlMark[b].attackType, 1,
					controlMark[b].zoom, controlMark[b].zoomEnd + 0.1f, controlMark[b].zoomIncrement,
					controlMark[b].zoom2 + 0.1f, controlMark[b].zoomEnd2 + 0.1f, controlMark[b].zoomIncrement2,
					false,
					false, false, false,
					controlMark[b].owner,
					false
				);
			}
		}

		// (참고) 네가 원하면 여기서 “리프트 끝난 뒤 alpha 처리”를 넣을 수 있지만
		// 지금 단계는 "끝까지 구현"이 목표라서, 대표 숨김은 SP_MERGE에서 post로 통일하는 게 안전함.
	}

	// -------------------------------------------------
	// [MERGE]
	// -------------------------------------------------
	if (sSkillPhase == SP_MERGE)
	{
		// ============================================================
		// [EDIT-C] 모으기 이동 끝난 뒤에만: from 투명 + target 업그레이드 (1회)
		// ============================================================
		if (sMergeMoveCalled && !sMergePostDone)
		{
			const int MOVE_T = FPS / 2;

			if (slotFrame - sMergeMoveStartFrame >= MOVE_T)
			{
				// 이동된 애들만 투명 처리
				for (int m = 0; m < sMoveCount; m++) {
					int from = sMoveFrom[m];
					if (from >= 0) controlMark[from].alpha = 1;
				}

				// 합쳐진(남은) 타겟을 업그레이드로 변경
				int target = -1;
				int dup = 1;

				if (sMoveCount == 2) { target = 1; dup = 3; }           // 3개 동일 -> 센터(1)
				else if (sMoveCount == 1) { target = sMoveTo[0]; dup = 2; } // 2개 동일 -> 왼쪽 타겟

				if (target >= 0) {
					int upSkill = UpgradeSkillIdx(target, dup);
					controlMark[target].attackType = upSkill;
					controlMark[target].attackStr = 1;
				}

				sMergePostDone = true;
			}
		}
	}

	// -----------------------------
	// [PHASE UPDATE] MERGE -> IMPACT -> DISPATCH -> DONE
	// -----------------------------
	if (sSkillPhase == SP_MERGE) {
		if (slotFrame - sSkillPhaseStartFrame >= sMergeFrames) {
			sSkillPhase = (sImpactFrames > 0) ? SP_IMPACT : SP_DISPATCH;
			sSkillPhaseStartFrame = slotFrame;
		}
	}

	// IMPACT
	if (sSkillPhase == SP_IMPACT)
	{
		int local = slotFrame - sSkillPhaseStartFrame;
		float t = (sImpactFrames > 0) ? (float)local / (float)sImpactFrames : 1.0f;
		if (t < 0) t = 0; if (t > 1) t = 1;

		float pulse = sinf(t * 3.141592f);

		for (int g = 0; g < sGroupCount; g++) {
			if (sGroupDupCount[g] < 2) continue;

			int gx = controlMark[sMoveTo[0]].x;
			int gy = controlMark[sMoveTo[0]].y + 64 * _2X;

			int alphaIdx = (sGroupDupCount[g] == 2) ? ALPHA_GOOD : ALPHA_GREAT;

			float gZoom = (sGroupDupCount[g] == 2)
				? (1.00f + 0.20f * pulse) * 2
				: (1.15f + 0.35f * pulse) * 2;

			float rot = (sGroupDupCount[g] == 3) ? (sinf(t * 6.28318f) * 0.08f) : 0.0f;

			DrawGoldAlpha(
				gx, gy,
				alphaIdx,
				FONT_GOLD_LARGE,
				gZoom * zoom,
				CENTER,
				(sGroupDupCount[g] == 3),
				rot,
				cvtDest, cvtLayer, buffering
			);
		}

		if (local >= sImpactFrames) {
			sSkillPhase = SP_DISPATCH;
			sSkillPhaseStartFrame = slotFrame;
		}
	}

	// DISPATCH
	if (sSkillPhase == SP_DISPATCH)
	{
		if (!sDispatched) {
			sDispatched = true;

			// ============================================================
			// [EDIT-D] 살아있는 controlMark만 맵 위치로 날리기 (SetControlMark 1단 이동만)
			// ============================================================
			int destX;
			int destY;

			const int FLY_T = FPS / 3;

			for (int i = 0; i < TOTALREEL; i++)
			{
				if (controlMark[i].frame2 > 0) {

					//스킬인덱스가 controlMark[i].attackType

					int targetObj;
					switch (skillData[controlMark[i].attackType * SKILLDATASIZE + SKILLDATA_ACTIVEPASSIVE]) {
					case ACTIVE:
					case PASSIVE:
					case HEROSKILL:
						targetObj = skillData[controlMark[i].attackType * SKILLDATASIZE + SKILLDATA_TARGET];
						destX = xOffset + ao[targetObj].x - rx;
						destY = STATUSWIN_Y + (rh - 4) * TSIZE - (ao[targetObj].y - 48 * _2X - ry - OBJIMGGAP);

						break;
					case SUMMON:
						targetObj = skillData[controlMark[i].attackType * SKILLDATASIZE + SKILLDATA_TARGET];
						destX = ao[targetObj].nx = ao[targetObj].x = DX / 2;//ao[ROBIN].x + TSIZE;
						destY = ao[targetObj].ny = ao[targetObj].y = ao[ROBIN].y + monXYGap[(ao[targetObj].type - 3) * 2 + 1];// -32 * _2X;
						break;
					default:
						targetObj = controlMark[i].owner;
						destX = xOffset + ao[targetObj].x - rx;
						destY = STATUSWIN_Y + (rh - 4) * TSIZE - (ao[targetObj].y - 48 * _2X - ry - OBJIMGGAP);

						break;
					}


					controlMark[i].frame = 0;
					controlMark[i].frame2 = 0;

					SetControlMark(
						controlMark[i].x, controlMark[i].y,
						destX, destY + 8 * _2X,
						destX, destY,
						8 * _2X, 1 * _2X,
						8 * _2X, 1 * _2X,            // ✅ 2단 제거
						FLY_T, FLY_T,         // ✅ time2=0
						false,
						30, 1,
						controlMark[i].attackType, 1,
						controlMark[i].zoom, controlMark[i].zoom - 0.1f, controlMark[i].zoomIncrement,
						controlMark[i].zoom - 0.1f, controlMark[i].zoom - 0.3f, controlMark[i].zoomIncrement2,
						false,
						false, false, false,
						controlMark[i].owner,
						false
					);
				}
			}

			sEndDelayLeft = sEndDelayFrames;
		}

		if (sEndDelayLeft > 0) sEndDelayLeft--;
		else sSkillPhase = SP_DONE;
	}

	// DONE
	if (sSkillPhase == SP_DONE && attackSequence == ATTACKSEQUENCE_SLOT)
	{
		attackSequence = ATTACKSEQUENCE_ACTION;
		turn = CREW + gRouletteResultAoOffset[0];
		InitBar(BAR_BATTLECOIN);

		//여기서 남은 턴을 줄여준다.
		remainedTurn--;
		remainedTurnFrame = 1;

		bar[BAR_ROULETTE].front = false;

		ao[NEUTRAL].motion = BOXSTATUS_OPENING;
	}
}

// Crew 관련
int GetHouseFromCrewIdx(int crewIdx)
{
	int i;
	for (i = 0; i < TOTAL_HOUSE; i++) {
		if (crewData[crewIdx * CREWDATASIZE + CREWDATASIZE - 2] == i)
			return i;
	}

	return -1;
}

int GetCrewDmg(int crewIdx, int lv)
{
	//return crewData[crewIdx * CREWDATASIZE + CREWDATA_DMG] * crewBulletLvUpDmgPercent[lv] / 100;
	return 100;
}

int GetCrewIdxFromType(int type)
{
	// hero 3개는 로비 편의 데이터라, 크루 검색에서 제외하려면 3부터 시작
	const int START_KEY = 0;

	// TOTAL_CREW_DATA_KEY 같은 총 엔트리 수가 있다면 그걸 쓰고,
	// 없으면 기존 TOTALCREWKEY / TOTALENEMYKEY 등 "crewData 엔트리 개수"로 돌려야 함.
	for (int key = START_KEY; key < TOTAL_CREW; key++)
	{
		int t = crewData[key * CREWDATASIZE + CREWDATA_TYPE];
		if (t == type) return key; // ✅ key(=crewData 인덱스) 반환
	}
	return -1;
}

int GetCrewPrice(int crewIdx)
{
	return crewData[crewIdx * CREWDATASIZE + 2];
}

int GetCrewPositionX(int crewIdx)
{
	int realX;

	realX = 2 * _2X + (crewIdx % COLLECTION_XCOUNT) * (COLLECTIONCARDSIZE_X + 4 * _2X) + TSIZE + 2 * _2X;

	return realX;
}

int GetCrewPositionY(int crewIdx)
{
	int i, j;
	int gapY = 0;
	int realY = 0;

	for (i = 0; i < crewIdx; i++) {
		if (i % 3 == 2) {
			gapY = 0;
			for (j = i + 1; j < i + 1 + 3; j++) {
				//switch (enemyData[crewData[j * CREWDATASIZE + 0] * ENEMYDATASIZE]) {
				//default:
					if (gapY < CREW_GAPY)
						gapY = 0;
				//	break;
				//}
			}

			realY -= gapY + CREWLISTSIZE_Y;
		}
	}
	return realY - 16 * _2X;
}