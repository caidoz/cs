#pragma once

#ifndef _FUNC_ITEM_H_
#define _FUNC_ITEM_H_
// Item & Inventory
int * GetDetailGradeFromCollectionIdx(int arr[], int collectionIdx, int type);
ITEM *GetItemPtr(int);
int DropItem(OBJECT *, int);
void MakeBoxDropPercent(void);
void MakeItem(ITEM * it, int type, int lv, int grade, int detail, int set);
void DrawQuickIcon(OBJECT * pObj, int x, int y, float zoom);
void DrawQuick(OBJECT * pObj, int x, int y, int status, float zoom);
void InventoryDraw(OBJECT * pObj, int x, int y, float zoom);
int MakeItemType(int);
int GetDropLv(void);
int MakeItemLevel(int, int);
int MakeItemDetail(int, int);
int MakeItemGrade(int, int, int);
int MakeItemValue(int, int, int, int);
int GetItemUpgradeValue(int type, int detail, int grade, int lv);
int MakeItemId(void);
int GetItem(int, int, int, int, long long, int);
int GetHeroCnt(void);
int GetHeroIdx(int type);
bool IsGetHero(int type);
int GetItemName(int, int, int);
int GetItemIcon(int, int, int);
int GetItemIronPrice(ITEM *);
long long GetUpgradeHammer(int, int, int, int);
int GetStageBossObjectIdx(void);
int GetStageBossIdx(void);
int GetStageBossType();
long long GetStageAdmissionFee(void);
long long GetStageAdmissionHeart(int stage);
int GetItemPrice(ITEM * it);
int GetCharPrice(int);
int GetItemPow(int, int, int);
int GetItemStar(int, int, int);

//동료 레벨업(동료 상세보기)
int GetCrewMaxLevel(void);
long long GetCrewUpgradeCost(ITEM* it, int what);//what: 0=조각, 1=골드
bool CanCrewLevelUp(ITEM* it);
long long GetCrewPower(int detail, int lv);

//---- 장비 강화 ----
//
// 동료 쪽과 같은 얼개다. 비용표도 같은 모양이다.
//     upgradeCostEquip[별 - 1][레벨 * 2 + (0:조각, 1:골드)]
int GetEquipMaxLevel(void);

//강화 배율. 기본 수치에 이것을 곱하면 그 레벨의 값이다. 100 이 등가다.
//
//무기와 방어구가 같은 표를 본다. 예전에는 무기는 등차(+1/레벨), 방어구는
//등비(+10%/레벨)로 서로 다르게 굴어서, 같은 "레벨 5" 가 부위마다 다른 뜻
//이었다. 표는 Config/BalanceConfig.h 에 있다.
int EquipLevelMul(int lv);

//강화까지 반영한 장비 한 점의 값.
//
//부르는 쪽이 배율을 직접 곱하지 않게 한다. 곱하는 자리가 여럿이면 한 곳을
//고치고 다른 곳을 잊는다 - 실제로 무기와 방어구가 그렇게 갈라져 있었다.
long long GetEquipValue(ITEM* it);
long long GetEquipUpgradeCost(ITEM* it, int what);//what: 0=조각, 1=골드
bool CanEquipLevelUp(ITEM* it);

//이 장비를 그 레벨에서 썼을 때의 공격력.
long long GetEquipPower(ITEM* it, int lv);

//가지고 있는 장비인가. 안 가진 것은 상세보기로 안 들어간다.
bool IsEquipOwned(ITEM* it);
int GetCurWeaponCollectionsIndex(void);
int GetHighestCollections(int);
int GetItemCount(int, int, int);
int GetItemLv(int, int, int);
int SetStrongestEquip(int, int, int);
int GetEquipSlot(int, int, int);
void BackUpEnemyObj(void);
void CopyEnemyObj(void);
int GetAttackEnemy(void);
int GetEnemyBarIdx(int idx);
bool IsBossObjActive(void);
void CopyBossObj(void);
int GetBossMomObj(void);
int GetInvenIdx(int type, int detail, int grade);
int CollectionCheck(void);
int GetMaxCollectionIdxFromStage(int stage);
int GetCollectionIdx(int type, int detail, int grade);
int GetCollectionActionCardIdx(int collectionIdx);
int GetRouletteIdx(int collectionIdx, int rouletteType);
bool IsCollectionFull(int collectionIdx);
bool IsCollectionFullEquiped(int collectionIdx);
int GetFullEquipedCollectionIdx(void);
int EraseCopyItem(void);
void EraseItem(ITEM * it);
void ArrangeInven(void);
//void ArrangeNetInven(void);
int EquipCheck(OBJECT *, ITEM * it);
void EquipNewItem(OBJECT* pObj, ITEM * it);
void EquipItem(OBJECT *, ITEM * it);
void UnEquipItem(OBJECT *, ITEM * it);
void UnEquipEffect(OBJECT *, ITEM * it);
void UseRing(OBJECT *, int);
void SetHotKey(OBJECT* pObj, int type, int idx, int where);
void FreeHotKey(OBJECT *, int);
int GetItemValue(ITEM * it);
void SetItemString(ITEM * it, int addDetail, int addCool);
void SetItemString_Gem(ITEM * it);
void SetNetString(ITEM * it);
void SetActiveSkillBodyString(int);
void SetNpcEquip(ITEM * it);
void SetNpcEquipDetail(int npc, int slot, int itemType, int itemDetail, int itemGrade);
void ResurrectionEffect(OBJECT *);
#endif
