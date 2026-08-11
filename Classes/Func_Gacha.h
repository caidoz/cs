#pragma once
#ifndef _FUNC_GACHA_H_
#define _FUNC_GACHA_H_

#define GACHA_BOX_BOUNCE_FALL		(FPS * 8 / 30)	// ³«ÇÏ
#define GACHA_BOX_BOUNCE_UP		(FPS * 5 / 30)	// Æ¢ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
#define GACHA_BOX_BOUNCE_DOWN		(FPS * 5 / 30)	// ï¿½Ù½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
#define GACHA_BOX_BOUNCE_HEIGHT		(32 * _2X)		// ¹Ù¿î½º ³ôÀÌ

#define GACHA_MAX_REWARD_CARD     12
#define REWARD_BOX_COUNT		8
#define BOX_GRADE_COUNT			6

enum GACHA_DEPTH
{
	GACHA_DEPTH_BOX = 0,       // ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	GACHA_DEPTH_CARD,          // º¸»ó ÇÑ Àå¾¿ °ø°³
	GACHA_DEPTH_SUMMARY,       // ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½
	GACHA_DEPTH_FLYTOBAR,		//ï¿½ï¿½ï¿½Ä«ï¿½å°¡ ï¿½ï¿½ ï¿½ï¿½Æ°ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ó°¡´ï¿½ ï¿½ï¿½.
	GACHA_DEPTH_GETITEM        // ÀÎº¥Åä¸® ¹İ¿µ ÈÄ Á¾·á
};

//------------------------------------------------------------
// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ Ä«ï¿½ï¿½ï¿½ï¿½ ï¿½Ìµï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
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
	// ï¿½Ï´ï¿½ ï¿½Ş´ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Æ°ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
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
	// ÃÑ º¸»ó Ä«µå ¼ö
	//----------------------------------------------------
	int minCard;
	int maxCard;

	//----------------------------------------------------
	// ÇÏÆ® ¼ö·® ¹üÀ§
	//----------------------------------------------------
	int heartMin;
	int heartMax;

	//----------------------------------------------------
	// °ñµå ¼ö·® ¹üÀ§ ¹× µîÀå È®·ü
	//----------------------------------------------------
	int goldMin;
	int goldMax;
	int goldRate;

	//----------------------------------------------------
	// ï¿½ï¿½ï¿½ï¿½ / ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
	//----------------------------------------------------
	int crewRate;
	int equipRate;

	//----------------------------------------------------
	// ï¿½ï¿½ï¿½ï¿½ / ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ È®ï¿½ï¿½
	//----------------------------------------------------
	int crewGradeRate[
		BOX_GRADE_COUNT];

	int equipGradeRate[
		BOX_GRADE_COUNT];

	//----------------------------------------------------
	// ·°Å° »óÀÚ È®·ü
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

const int castleRewardBoxRate[TOTALCASTLE][REWARD_BOX_COUNT] =
{
	// B0 B1 B2 B3 B4 B5 B6 B7

	{100,  0,  0,  0,  0,  0,  0,  0}, // 0
	{ 80, 20,  0,  0,  0,  0,  0,  0}, // 1
	{ 60, 35,  5,  0,  0,  0,  0,  0}, // 2
	{ 45, 40, 15,  0,  0,  0,  0,  0}, // 3
	{ 30, 40, 25,  5,  0,  0,  0,  0}, // 4
	{ 20, 35, 30, 15,  0,  0,  0,  0}, // 5
	{ 10, 25, 35, 25,  5,  0,  0,  0}, // 6
	{  5, 20, 35, 25, 15,  0,  0,  0}, // 7
	{  0, 15, 35, 30, 15,  5,  0,  0}, // 8
	{  0, 10, 30, 30, 20, 10,  0,  0}, // 9
	{  0,  5, 25, 30, 25, 15,  0,  0}, // 10
	{  0,  0, 20, 30, 30, 15,  5,  0}, // 11
	{  0,  0, 15, 25, 30, 20, 10,  0}, // 12
	{  0,  0, 10, 20, 30, 25, 15,  0}, // 13
	{  0,  0,  5, 15, 30, 30, 20,  0}, // 14
	{  0,  0,  0, 10, 25, 30, 25, 10}, // 15
	{  0,  0,  0,  5, 20, 30, 30, 15}, // 16
	{  0,  0,  0,  0, 15, 30, 35, 20}, // 17
	{  0,  0,  0,  0, 10, 25, 35, 30}, // 18
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
//ì¸í„°ë™í‹°ë¸Œ ì „íˆ¬ íŠœí† ë¦¬ì–¼: ì´ë²ˆ ìƒìê°€ ì‹œë‚˜ë¦¬ì˜¤ìƒ ëª‡ ë²ˆì§¸ì¸ì§€(0~2), ì•„ë‹ˆë©´ -1
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