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
void NewsDraw(int x, int y, float zoom);
void GiftDraw(int x, int y, float zoom);
void GuildEventDraw(int x, int y, float zoom);
void DailyQuestDraw(int x, int y, float zoom);
void ShopDraw(int, int, float zoom);
void CastleMenuDraw(int x, int y, float zoom);
void StarShopDraw(int, int);
void CrewListDraw(int x, int y, float zoom);
void HeroSelectButtonList(int x, int y, float zoom, int selected, bool touchActive, bool horizontal);
void HeroStatDraw(OBJECT * pObj, int x, int y, float zoom);
void ItemDetailDraw(ITEM * it, int x, int y, float zoom, bool equipped, bool onlyInfo);
//동료 상세보기. winH는 (x, y)부터 아래로 쓸 수 있는 높이(픽셀)다.
void CrewDetailDraw(ITEM* it, int x, int y, float zoom, float winH);

//장비 상세보기(팝업). 동료 상세와 같은 틀을 쓴다.
//얻지 않은 장비는 여기까지 오지 않는다(Func_Input.cpp에서 막는다).
void EquipDetailDraw(ITEM* it);
void ItemOptionCompareDraw(ITEM * it1, ITEM * it2, int x, int y, float zoom);
void ItemOptionDraw(ITEM * it, int x, int y, float zoom, bool equipped);
void EquipInfoDraw(ITEM * it, int x, int y, int itemType, int itemDetail, int itemGrade, int depth, int menuX, float zoom);
void DrawCombatPower(long long pow, int icon, int x, int y, int alpha, float zoom);
void StarBarDraw(long long pow, int icon, int x, int y, int alpha, float zoom, bool rainbowShop = false);
void IapConfirmDraw(int itemType, int detail, int x, int y, float zoom);
void GachaRatesDraw(int boxDetail);
void ShopJumpToIapSection(int section);
void StageProgressDraw(int x, int y, int current, int progress, float zoom);
void RemainedTurnDraw(int x, int y, int current, int progress, float zoom);
void StageInfoDraw(int stage, int room, long long combatPower, bool cur, int x, int y, float zoom);
void StageListDraw(int x, int y, int status, int frame);
void CrewUpgradeMenuDraw(int x, int y, float zoom);
void HowToGetHeroesDraw(int x, int y, float zoom);
void HowToGetCrewsDraw(int x, int y, float zoom);
void CollectionsDraw(int x, int y, float zoom);
void CollectionDetailListDraw(int x, int y, int collectionIdx, float zoom);
void CalendarDraw(int, int, float zoom);
void OptionDraw(int, int, float zoom);
void OptionLanguageDraw(int x, int y, float zoom);
void OptionPushAlarmDraw(int x, int y, float zoom);
void OptionHelpDraw(int x, int y, float zoom);
void JokboDraw(int, int, float zoom);
void LevelUpMenuDraw(int lv, int status, int x, int y, float zoom);
void DeptDiscountDraw(int x, int y, float zoom);
void DoubleGoldDraw(int x, int y, float zoom);

int GetBoxCurrency(int, int);
int GetBoxGold(int boxType);
int GetBoxQuestItem(int boxType);
int GetBoxHeartItem(int boxType);
long long GetBoxPrice(int, int);

int GetItemCategoryCnt(int category);
int GetScrollDy(int);
void SetAlert(int);
void OutOfAlert(void);
void DrawHandleExec(int drawIdx);
void AlertDraw(void);
void GachaDraw(void);
void NewCollectionDraw(int x, int y, float zoom);
void NewCardDraw(void);

void DrawItemCardBack(
	int itemStar,
	int x,
	int y,
	float zoom,
	int backFrame);

// 동료 편성 메뉴 그리기
void DrawItemCard(
	int itemType,
	int itemDetail,
	int itemGrade,
	int itemLv,
	long itemCnt,
	bool empty,
	int x,
	int y,
	int text,
	float zoom,
	bool ani,
	int buttonTouchFunc,
	int cardTouchFunc,
	int selectedFrame,
	int backFrame);

int GetCrewInventoryIdx(int type);
void CrewMenuDraw(int x, int y, float zoom);
void DrawButton(int x, int y, int color, int size, int icon, int text, bool ani, float zoomX, float zoomY);

#endif
