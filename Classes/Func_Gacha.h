#pragma once
#ifndef _FUNC_GACHA_H_
#define _FUNC_GACHA_H_

#define GACHA_BOX_BOUNCE_FALL		(FPS * 8 / 30)	// 낙하
#define GACHA_BOX_BOUNCE_UP		(FPS * 5 / 30)	// Ƣ�� ����
#define GACHA_BOX_BOUNCE_DOWN		(FPS * 5 / 30)	// �ٽ� ������
#define GACHA_BOX_BOUNCE_HEIGHT		(32 * _2X)		// 바운스 높이

#define GACHA_MAX_REWARD_CARD     12
#define REWARD_BOX_COUNT		8
#define BOX_GRADE_COUNT			6

enum GACHA_DEPTH
{
	GACHA_DEPTH_BOX = 0,       // ���� ���� �� ����
	GACHA_DEPTH_CARD,          // 보상 한 장씩 공개
	GACHA_DEPTH_SUMMARY,       // ���� ���� ���
	GACHA_DEPTH_FLYTOBAR,		//���ī�尡 �� ��ư���� ���󰡴� ��.
	GACHA_DEPTH_GETITEM        // 인벤토리 반영 후 종료
};

//------------------------------------------------------------
// ������ ���� ī���� �̵� ���� ����
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
	// �ϴ� �޴��� ���ư��� ���� ����
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
	// ���� / ��� ���� ����
	//----------------------------------------------------
	int crewRate;
	int equipRate;

	//----------------------------------------------------
	// ���� / ��� ��� Ȯ��
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

//성마다 어떤 보상 상자가 나오는지. 한 줄이 100 이 되도록 맞춘다.
//
//[나무상자가 언제나 제일 흔하다]
//전에는 창문이 옆으로 미끄러지는 모양이었다. 성 18 에서
//
//    { 0, 0, 0, 0, 10, 25, 35, 30 }
//
//앞 넷이 0 이라 나무상자가 아예 안 나왔고, 10%인 B4 를 빼면 사실상 세 종류만
//떨어졌다. 상자 그림은 여덟 장(box19~box26) 다 있는데 그 중 셋만 보였다.
//
//지금은 앞을 0 으로 만들지 않는다. 성이 오르면 뒤쪽 상자가 "열릴" 뿐이고,
//꼬리가 길어지면서 상위 상자의 몫이 조금씩 커진다. 그래도 제일 많이 나오는
//것은 끝까지 나무상자다.
//
//    weight[i] = 100 * r^i        (i = 0 .. 열린 칸)
//    열린 칸    = round(성 * 7 / 18)
//    r         = 0.30 -> 0.62      성이 높을수록 완만해진다
//
//표는 tools 없이 손으로 고쳐도 된다. 한 줄 합이 100 이기만 하면 된다.
const int castleRewardBoxRate[CAP_CASTLE][REWARD_BOX_COUNT] =
{
	// B0 B1 B2 B3 B4 B5 B6 B7

	{100,  0,  0,  0,  0,  0,  0,  0}, // 0
	{100,  0,  0,  0,  0,  0,  0,  0}, // 1
	{ 75, 25,  0,  0,  0,  0,  0,  0}, // 2
	{ 74, 26,  0,  0,  0,  0,  0,  0}, // 3
	{ 66, 25,  9,  0,  0,  0,  0,  0}, // 4
	{ 65, 25, 10,  0,  0,  0,  0,  0}, // 5
	{ 63, 26, 11,  0,  0,  0,  0,  0}, // 6
	{ 59, 25, 11,  5,  0,  0,  0,  0}, // 7
	{ 58, 26, 11,  5,  0,  0,  0,  0}, // 8
	{ 56, 25, 12,  5,  2,  0,  0,  0}, // 9
	{ 53, 26, 12,  6,  3,  0,  0,  0}, // 10
	{ 52, 26, 13,  6,  3,  0,  0,  0}, // 11
	{ 50, 25, 13,  7,  3,  2,  0,  0}, // 12
	{ 48, 25, 14,  7,  4,  2,  0,  0}, // 13
	{ 47, 25, 14,  8,  4,  2,  0,  0}, // 14
	{ 44, 25, 14,  8,  5,  3,  1,  0}, // 15
	{ 42, 25, 15,  8,  5,  3,  2,  0}, // 16
	{ 41, 24, 15,  9,  5,  3,  2,  1}, // 17
	{ 39, 24, 15,  9,  6,  4,  2,  1}, // 18
};

int GetRewardBoxIndex(int boxDetail);
int BoxRandomRange(int minValue, int maxValue);
int RollBoxGrade(
	const int gradeRate[BOX_GRADE_COUNT],
	int* highGradeMissCount);
bool IsDuplicateBoxCard(
	int cardCount,
	int type,
	int detail);
int MakeBoxEquipType();
static int GetRandomBoxDetailByStar(
	int itemType,
	int itemGrade,
	int targetStar,
	int detailCount);
static int GetBoxDetailCount(
	int itemType);
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
int SelectCastleRewardBox(
	int castleIndex);
bool GenerateCastleBoxReward(
	int boxDetail);
//인터랙티브 전투 튜토리얼: 이번 상자가 시나리오상 몇 번째인지(0~2), 아니면 -1
int GetTutorialGachaBoxIndex(void);
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