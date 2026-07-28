#pragma once
#ifndef _FUNC_MENU_H_
#define _FUNC_MENU_H_

#define MENUUIDATACNT 7

#define BUTTON_COLOR_WHITE 0
#define BUTTON_COLOR_PURPLE 1
#define BUTTON_COLOR_GREEN 2
#define BUTTON_COLOR_BLUE 3
#define BUTTON_COLOR_BROWN 4
#define BUTTON_COLOR_BEIGE 5

#define BUTTON_TOTALCOLOR 6

#define BUTTON_SIZE_LARGE 0
#define BUTTON_SIZE_MID 1
#define BUTTON_SIZE_SMALL 2

#define BUTTON_TOTALSIZE 3

const signed int crewMenuUiData[] = {
	640, 153, 0, 0, 0, 0, MENU_IMG,//상단창
	
	332, 114, 641, 0, 154, 4, MENU_IMG,//타이틀 창
};

const signed int equipMenuUiData[] = {
	640, 149, 0, 154, 0, 0, MENU_IMG,//상단창

	290, 128, 641, 155, 176, 4, MENU_IMG,//타이틀 창

	//597, 326, 0, 543, 19, 130, MENU_IMG,//현재 캐릭터 셋업
};

const signed int shopMenuUiData[] = {
	640, 137, 0, 304, 0, 0, MENU_IMG,//상단창

	337, 114, 641, 305, 152, 16, MENU_IMG,//타이틀 창
};

const signed int castleMenuUiData[] = {
	640, 163, 0, 442, 0, -17, MENU_IMG,//상단창

	346, 112, 654, 453, 147, 12, MENU_IMG,//타이틀 창
};

const int buttonImgData[] = {
	176, 40, 1, 638, UI_NEW_IMG,//화이트 Large
	//128, 40, 178, 638, UI_NEW_IMG,//화이트 Mid
	//80, 40, 307, 638, UI_NEW_IMG,//화이트 Small

	176, 40, 1, 720, UI_NEW_IMG,//보라 Large
	//128, 40, 178, 720, UI_NEW_IMG,//보라 Mid
	//80, 40, 307, 720, UI_NEW_IMG,//보라 Small

	176, 40, 1, 761, UI_NEW_IMG,//초록 Large
	//128, 40, 178, 761, UI_NEW_IMG,//초록 Mid
	//80, 40, 307, 761, UI_NEW_IMG,//초록 Small

	176, 40, 1, 802, UI_NEW_IMG,//파랑 Large
	//128, 40, 178, 802, UI_NEW_IMG,//파랑 Mid
	//80, 40, 307, 802, UI_NEW_IMG,//파랑 Small	

	176, 40, 1, 843, UI_NEW_IMG,//갈색 Large
	//128, 40, 178, 843, UI_NEW_IMG,//갈색 Mid
	//80, 40, 307, 843, UI_NEW_IMG,//갈색 Small

	176, 40, 1, 884, UI_NEW_IMG,//베이지 Large
	//128, 40, 178, 884, UI_NEW_IMG,//베이지 Mid
	//80, 40, 307, 884, UI_NEW_IMG,//베이지 Small	

	176, 40, 1, 925, UI_NEW_IMG,//다크그레이 Large
	//128, 40, 178, 884, UI_NEW_IMG,//베이지 Mid
	//80, 40, 307, 884, UI_NEW_IMG,//베이지 Small	

};

const int equipBgData[] = {
	240, 332, 0, 0, 0, 0,
	240, 332, 240, 0, 0, 0,
	240, 332, 240 * 2, 0, 0, 0,
	240, 332, 240 * 3, 0, 0, 0,
	240, 332, 0, 332, 0, 0,
	240, 332, 240, 332, 0, 0,
	
};

// Menu & UI 관련 함수
void NewsDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void GiftDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void GuildEventDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void DailyQuestDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void ShopDraw_Back(int, int, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void ShopDraw(int, int, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void CastleMenuDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void StarShopDraw(int, int);
void HeroDraw(int type, int x, int y, int dirX, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void HeroListDraw(int x, int y, float zoom, bool checkBox, int gap, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void CrewListDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void HeroSelectButtonList(int x, int y, float zoom, int selected, bool touchActive, bool horizontal, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void HeroStatDraw(OBJECT * pObj, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void ItemDetailDraw(ITEM * it, int x, int y, float zoom, bool equipped, bool onlyInfo, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void ItemOptionCompareDraw(ITEM * it1, ITEM * it2, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void ItemOptionDraw(ITEM * it, int x, int y, float zoom, bool equipped, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void EquipInfoDraw(ITEM * it, int x, int y, int itemType, int itemDetail, int itemGrade, int depth, int menuX, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void DrawCombatPower(long long pow, int icon, int x, int y, int alpha, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void StarBarDraw(long long pow, int icon, int x, int y, int alpha, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void StageProgressDraw(int x, int y, int current, int progress, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void RemainedTurnDraw(int x, int y, int current, int progress, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void StageInfoDraw(int stage, int room, long long combatPower, bool cur, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void StageListDraw(int x, int y, int status, int frame, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void CrewUpgradeMenuDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void HowToGetHeroesDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void HowToGetCrewsDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
int GetItemCntUpgradePossible(void);
void DrawEquipItemCard(int itemType, int itemDetail, int itemGrade, int itemLv, int itemCnt, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void CollectionsDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void CollectionDetailListDraw(int x, int y, int collectionIdx, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void CalendarDraw(int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void OptionDraw(int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void JokboDraw(int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void LevelUpMenuDraw(int lv, int status, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void DeptDiscountDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void DoubleGoldDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void LimitScrollY(void);

int GetBoxCurrency(int, int);
int GetBoxGold(int boxType);
int GetBoxQuestItem(int boxType);
int GetBoxHeartItem(int boxType);
int GetBoxPrice(int, int);

int GetItemCategoryCnt(int category);
int GetScrollDy(int);
void SetAlert(int);
void OutOfAlert(void);
void DrawHandleExec(int drawIdx);
void AlertDraw(void);
void GachaDraw(void);
void NewCollectionDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void NewCardDraw(void);

void DrawItemCardBack(
	int itemStar,
	int x,
	int y,
	float zoom,
	int backFrame,
	cocos2d::RenderTexture* cvtDest,
	cocos2d::Layer* cvtLayer,
	bool buffering
);

// 동료 편성 메뉴 그리기
void DrawItemCard(
	int itemType,
	int itemDetail,
	int itemGrade,
	int itemLv,
	bool empty,
	int x,
	int y,
	int text,
	float zoom,
	bool ani,
	int buttonTouchFunc,
	int cardTouchFunc,
	int selectedFrame,
	int backFrame,	// 0: 앞면, 1~7: 카드 뒷면 프레임
	cocos2d::RenderTexture* cvtDest,
	cocos2d::Layer* cvtLayer,
	bool buffering
);

int GetCrewInventoryIdx(int type);
void CrewMenuDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void CrewPannelDraw(int crewIdx, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
bool IsCrewSet(int crewIdx);
void DrawButton(int x, int y, int color, int size, int icon, int text, bool ani, float zoomX, float zoomY, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
#endif