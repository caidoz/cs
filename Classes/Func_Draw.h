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
// DrawÇÚµé
void DrawWindow3(int x, int y, int w, int h, int index, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void DrawWindow4(int x, int y, int w, int h, int index, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void DrawWindow5(int x, int y, int w, int h, int mapIdx, float zoom, int mapOffsetY, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);

void VersionDraw(void);
void NoSpaceDraw(void);
void LogoDraw(void);
void LoadingDraw(void);
void TitleDraw(void);
void OpeningDraw(void);
void DrawCmfPopUp(int, int, int, int, int, int, int, int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void GNBDraw(int, int, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void ActiveHelpDraw(cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void LogDraw(LOG *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
int GetEventMenuPosX(int eventIdx, int eventStatus);
int GetEventMenuPosY(int eventIdx, int eventStatus);
void EventScheduler(void);
int GetEventMenuIdx(int eventType);
void DeleteEventMenu(int eventIdx);
void InitEventMenu(GAMEEVENT * gEvent, unsigned char type, unsigned char subType, short icon, long limitTime, int touchFunc);
void sortArray(int arr[], int index[], int n);
void MainMenuOut(void);
void MainMenuIn(void);
void ArrangeEventMenu(void);
void EventMenuDraw(GAMEEVENT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void GoldQuestMenuDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void GameOverDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void ClosePopUp(void);
void SetPopUp(int type, int x, int y, int w, int h,
	int itemType, int itemDetail, int itemGrade,
	int rewardType1, int rewardDetail1, int rewardGrade1, long long rewardStartCnt1, long long rewardEndCnt1,
	int rewardType2, int rewardDetail2, int rewardGrade2, long long rewardStartCnt2, long long rewardEndCnt2,
	int rewardType3, int rewardDetail3, int rewardGrade3, long long rewardStartCnt3, long long rewardEndCnt3);
void DrawPopUp(int idx, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void GameMenuDraw(int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void BossHpBarDraw(long long count, long long max, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
