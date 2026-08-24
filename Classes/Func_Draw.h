#pragma once

#define OPENING_SCENE_COUNT 5
#define OPENING_TEXT_PER_SCENE 3
#define OPENING_TOTAL_TEXT (OPENING_SCENE_COUNT * OPENING_TEXT_PER_SCENE)

enum OpeningState
{
	OPENING_STATE_TEXT,
	OPENING_STATE_TEXT_WAIT,
	OPENING_STATE_SCENE_WAIT,
	OPENING_STATE_END
};

const int openingTextId[] =
{
	TEXT_OPENING_0_0,
	TEXT_OPENING_1_0,
	TEXT_OPENING_2_0,
	TEXT_OPENING_3_0,
	TEXT_OPENING_4_0
};
// Draw핸들
void DrawWindow3(int x, int y, int w, int h, int index, float zoom);
void DrawWindow4(int x, int y, int w, int h, int index, float zoom);
void DrawWindow5(int x, int y, int w, int h, int mapIdx, float zoom, int mapOffsetY);

void VersionDraw(void);
void LogoDraw(void);
void LoadingDraw(void);
void TitleDraw(void);
void TitleSkillViewerCommand(int command);
void OpeningDraw(void);
void DrawCmfPopUp(int, int, int, int, int, int, int, int, int, float zoom, int dir = LEFT);
void GNBDraw(int, int);
void ActiveHelpDraw();
void LogDraw(LOG *);
void KeepLogFromDarken(LOG *);
int GetEventMenuPosX(int eventIdx, int eventStatus);
int GetEventMenuPosY(int eventIdx, int eventStatus);
void EventScheduler(void);
int GetEventMenuIdx(int eventType);
void DeleteEventMenu(int eventIdx);
void InitEventMenu(GAMEEVENT * gEvent, unsigned char type, unsigned char subType, short icon, long limitTime, int touchFunc);
void sortArray(int arr[], int index[], int n);
void MainMenuIn(void);
void ArrangeEventMenu(void);
void EventMenuDraw(GAMEEVENT *);
void GoldQuestMenuDraw(int x, int y, float zoom);
void GameOverDraw(int x, int y, float zoom);
void ClosePopUp(void);
void SetPopUp(int type, int x, int y, int w, int h,
	int itemType, int itemDetail, int itemGrade,
	int rewardType1, int rewardDetail1, int rewardGrade1, long long rewardStartCnt1, long long rewardEndCnt1,
	int rewardType2, int rewardDetail2, int rewardGrade2, long long rewardStartCnt2, long long rewardEndCnt2,
	int rewardType3, int rewardDetail3, int rewardGrade3, long long rewardStartCnt3, long long rewardEndCnt3);
void DrawPopUp(int idx);
void GameMenuDraw(int, int, float zoom);
void BossHpBarDraw(long long count, long long max, int x, int y, float zoom);
