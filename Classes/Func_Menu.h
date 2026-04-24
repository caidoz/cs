#pragma once
#ifndef _FUNC_MENU_H_
#define _FUNC_MENU_H_
// Menu & UI 관련 함수
void NewsDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void GiftDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void GuildEventDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void DailyQuestDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void ShopDraw_Back(int, int, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void ShopDraw(int, int, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
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
void StageProgressDraw(int x, int y, int current, int progress, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void RemainedTurnDraw(int x, int y, int current, int progress, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void StageInfoDraw(int stage, int room, long long combatPower, bool cur, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void StageListDraw(int x, int y, int status, int frame, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void CrewUpgradeMenuDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void HowToGetHeroesDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void HowToGetCrewsDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
int GetItemCntUpgradePossible(void);
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

int GetScrollDy(int);
void SetAlert(int);
void OutOfAlert(void);
void DrawHandleExec(int drawIdx);
void AlertDraw(void);
void GachaDraw(void);
void NewCollectionDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void NewCardDraw(void);
#endif