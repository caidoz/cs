#pragma once
#ifndef _FUNC_GACHA_H_
#define _FUNC_GACHA_H_

#define GACHA_BOX_BOUNCE_FALL		(FPS * 8 / 30)	// 낙하
#define GACHA_BOX_BOUNCE_UP		(FPS * 5 / 30)	// 튀어 오름
#define GACHA_BOX_BOUNCE_DOWN		(FPS * 5 / 30)	// 다시 내려옴
#define GACHA_BOX_BOUNCE_HEIGHT		(32 * _2X)		// 바운스 높이

#define GACHA_MAX_REWARD_CARD     12
#define REWARD_BOX_COUNT		8
#define BOX_GRADE_COUNT			6

enum GACHA_DEPTH
{
	GACHA_DEPTH_BOX = 0,       // 상자 낙하 및 오픈
	GACHA_DEPTH_CARD,          // 보상 한 장씩 공개
	GACHA_DEPTH_SUMMARY,       // 최종 보상 요약
	GACHA_DEPTH_FLYTOBAR,		//요약카드가 각 버튼으로 날라가는 것.
	GACHA_DEPTH_GETITEM        // 인벤토리 반영 후 종료
};

//------------------------------------------------------------
// 공개가 끝난 카드의 이동 연출 정보
//------------------------------------------------------------
typedef struct GACHA_REWARD_CARD_ANIM
{
	bool active;

	bool movingToTray;
	bool arrivedTray;

	bool movingToPopup;
	bool arrivedPopup;

	int moveFrame;

	float startX;
	float startY;
	float startZoom;

	float trayX;
	float trayY;
	float trayZoom;

	float popupX;
	float popupY;
	float popupZoom;

	//--------------------------------------------------------
	// 하단 메뉴로 날아가는 최종 연출
	//--------------------------------------------------------
	bool movingToBar;
	bool arrivedBar;
	bool finishedBar;

	int barMoveFrame;
	int barHoldFrame;

	float barStartX;
	float barStartY;
	float barStartZoom;

	float barTargetX;
	float barTargetY;
	float barTargetZoom;

} GACHA_REWARD_CARD_ANIM;

static GACHA_REWARD_CARD_ANIM
gachaRewardCardAnim[GACHA_MAX_REWARD_CARD];

static bool gachaCardCanAdvance = false;
static bool gachaConfirmReady = false;


struct REWARD_BOX_DATA
{
	//----------------------------------------------------
	// 총 보상 카드 수
	//----------------------------------------------------
	int minCard;
	int maxCard;

	//----------------------------------------------------
	// 하트 수량 범위
	//----------------------------------------------------
	int heartMin;
	int heartMax;

	//----------------------------------------------------
	// 골드 수량 범위 및 등장 확률
	//----------------------------------------------------
	int goldMin;
	int goldMax;
	int goldRate;

	//----------------------------------------------------
	// 동료 / 장비 선택 비율
	//----------------------------------------------------
	int crewRate;
	int equipRate;

	//----------------------------------------------------
	// 동료 / 장비 등급 확률
	//----------------------------------------------------
	int crewGradeRate[
		BOX_GRADE_COUNT];

	int equipGradeRate[
		BOX_GRADE_COUNT];

	//----------------------------------------------------
	// 럭키 상자 확률
	//----------------------------------------------------
	int luckyRate;
};

static const REWARD_BOX_DATA rewardBoxData[8] =
{
	//--------------------------------------------------------
	// BOX_REWARD0
	//--------------------------------------------------------
	{
		2, 3,

		100, 200,
		10000, 20000,
		20,

		70, 30,

		{ 72, 23, 5, 0, 0, 0 },
		{ 78, 19, 3, 0, 0, 0 },

		5
	},

	//--------------------------------------------------------
	// BOX_REWARD1
	//--------------------------------------------------------
	{
		3, 4,

		120, 300,
		20000, 50000,
		35,

		65, 35,

		{ 58, 30, 10, 2, 0, 0 },
		{ 64, 27, 8, 1, 0, 0 },

		5
	},

	//--------------------------------------------------------
	// BOX_REWARD2
	//--------------------------------------------------------
	{
		3, 5,

		140, 420,
		40000, 120000,
		50,

		62, 38,

		{ 45, 32, 18, 5, 0, 0 },
		{ 50, 31, 15, 4, 0, 0 },

		5
	},

	//--------------------------------------------------------
	// BOX_REWARD3
	//--------------------------------------------------------
	{
		4, 6,

		160, 560,
		60000, 210000,
		65,

		60, 40,

		{ 32, 31, 24, 10, 3, 0 },
		{ 38, 31, 22, 8, 1, 0 },

		5
	},

	//--------------------------------------------------------
	// BOX_REWARD4
	//--------------------------------------------------------
	{
		5, 7,

		180, 720,
		100000, 400000,
		75,

		57, 43,

		{ 22, 28, 27, 16, 7, 0 },
		{ 27, 30, 25, 13, 5, 0 },

		5
	},

	//--------------------------------------------------------
	// BOX_REWARD5
	//--------------------------------------------------------
	{
		6, 8,

		200, 900,
		140000, 630000,
		85,

		55, 45,

		{ 14, 23, 27, 22, 11, 3 },
		{ 18, 26, 27, 19, 8, 2 },

		5
	},

	//--------------------------------------------------------
	// BOX_REWARD6
	//--------------------------------------------------------
	{
		7, 10,

		200, 1000,
		180000, 900000,
		95,

		52, 48,

		{ 7, 17, 26, 25, 18, 7 },
		{ 10, 20, 27, 24, 14, 5 },

		5
	},

	//--------------------------------------------------------
	// BOX_REWARD7
	//--------------------------------------------------------
	{
		9, 12,

		200, 1000,
		200000, 1000000,
		100,

		50, 50,

		{ 2, 8, 20, 28, 27, 15 },
		{ 4, 12, 23, 28, 23, 10 },

		5
	}
};

int GetRewardBoxIndex(int boxDetail);
int BoxRandomRange(int minValue, int maxValue);
int RoundBoxCurrency(int itemType, int value);
int RollBoxGrade(
	const int gradeRate[BOX_GRADE_COUNT],
	int* highGradeMissCount);
bool IsDuplicateBoxCard(
	int cardCount,
	int type,
	int detail);
int MakeBoxEquipType();
void MakeBoxCrewReward(
	int cardIndex,
	int boxIndex);
void MakeBoxEquipReward(
	int cardIndex,
	int boxIndex);
void MakeBoxHeartReward(
	int cardIndex,
	const REWARD_BOX_DATA* boxData,
	bool lucky);
void MakeBoxGoldReward(
	int cardIndex,
	const REWARD_BOX_DATA* boxData,
	bool lucky);
void UpgradeLuckyBoxCard(
	int cardCount);
void ShuffleBoxReward(
	int cardCount);
void CheckNewBoxReward(
	int cardCount);
bool GenerateCastleBoxReward(
	int boxDetail);
int GetWeightedNormalizedReward(
	int minValue,
	int maxValue);

void GachaDraw(void);

bool IsGachaBigReward(const ITEM* item);

void DrawGachaItemEffect(
	const ITEM* item,
	float x,
	float y,
	int effectFrame);

void GachaKey(void);

#endif