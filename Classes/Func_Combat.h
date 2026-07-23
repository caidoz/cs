#pragma once
#include "Core.h"

// Stat Calculating
void InitStat(OBJECT *);
void RefreshStatAi(OBJECT *);
void RefreshStat(OBJECT *);
void RefreshStat_Fuck(OBJECT *, ITEM *, int);
void RefreshStat_Sub(OBJECT *);
void RefreshSkill(OBJECT *);
void RefreshBuff(OBJECT *);
void RefreshQuestTime(void);
void RefreshHeartTime(void);
void RefreshEnemyTime(void);
void RefreshCalendarTime(void);

// Combat Formula
long long NextExp(int);
int GetExpFromEnchantSlot(void);
int GetGoldFromEnchantSlot(void);
int GetGoldFromSocketSlot(void);
void LevelUpEquip(ITEM * it, int getExp);
int NextExpEquip(ITEM *, int);
int NextLvEquip(ITEM *, int);
int checkEnchantSlotNum(int);
int checkSocketSlotNum(int, int);
int checkExistSocketSlotCnt(int);
int checkEmptySocketSlot(int);
bool checkSameSocketSlot(int, int);
int pushEnchantEquip(int);
int pushSocketSlot(int, int);
int popEnchantEquip(int);
int popSocketSlot(int, int);
int GetLevelUpRewardLv(int type, int userLv);
void LevelUp(int getExp);
void LevelUpObj(OBJECT *, int);
void PlusHp(OBJECT *, long long int);
void PlusMp(OBJECT *, long long int);
long long int GetAbsorb(OBJECT *, long long int);
bool CheckSkillAttack(long long int);
int GetAttackRange(int);
void SetWheel(void);
void SetRouletteTime(void);
int GetSpeed(int);
int GetRaidSpeed(int);
int GetAtk(int);
long long GetRouletteValue(int actioncCardType, int itemType, int itemDetail, int itemGrade, int itemLv);
long long GetMinDmg(OBJECT *);
long long GetMaxDmg(OBJECT *);
int GetTouchGray(int, int);
void AttackRobin(int, int);
int AttackRobin_Back(int, int);
int AttackObj(long long int, int);
int AttackObj2(int, int, int, int);
int AttackEnemyCheck(int);
int EnemyCheck(int);
void AttackPlayerCheck(OBJECT *);
void AttackBoxCheck(OBJECT *);
void NeutralCheck(OBJECT *);
void ItemCheck(OBJECT *);
void SetDmgNum(int, int, long long, int, int, float);
void OrderDmgNum(void);
int SetImgTextPos(int, int, int, int, float);
int SetImgText(int, int, float);
void SetHitMark(int, int, int, int, int, int, float);
void SetCurrencyMarkArr(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, long long amount, int type, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2, int iconMarkCnt, int bar);
void SetCurrencyMarkArr_PopUp(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, long long amount, int type, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2, int iconMarkCnt);
int GetCurrencyMarkDoneCnt(void);
void SetCurrencyMark_PopUp(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, int amount, int type, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2);
void SetCurrencyMark(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, int amount, int type, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2, int bar);
void SetCurrencyMarkGold(int startPosX, int startPosY, int str);
void SetGoldAlphaMark(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, int amount, int type, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2);
int SetSoulMark(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, int speed, int speedIncrement, int speed2, int speedIncrement2, int waitingFrame, int waitingFrame2, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2);
int SetItemMark(int, int, int, int, int, int, int, int);
int GetRewardMarkCnt(void);
void InitEventPos(GAMEEVENT * gEvent, int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, int amount,
	float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2);
int SetRewardMark(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, int amount,
	int type, int detail, int grade, int cooldown, bool text, bool value, bool ani, int owner, bool star, bool cardFrame, bool newItem, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2);
void ArrangeControlMark(int start);
int GetControlMark(int owner);
int SetControlMark(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, int amount,
	int attackType, int attackStr, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2, int alpha, bool text, bool value, bool ani, int owner, bool openFrame);
int GetCardMarkCnt(void);
int SetCardMark(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, int amount,
	int attackType, int attackStr, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2, int alpha, bool text, bool value, bool ani, int owner, bool openFrame);
void SetBox(OBJECT * pObj, int etc);
int SetBoxMark(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int moveAngle, int detail, int grade, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2);
int SetBoxCardMark(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, int amount,
	int type, int detail, int grade, int cooldown, bool text, bool value, bool ani, int owner, bool star, bool cardFrame, bool newItem, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2);

int NearPlayer(OBJECT* pObj);
int NearEnemy(OBJECT* pObj);
int TargetPlayer(int);
int TargetEnemy(int);

long long GetCombatPowerAll(int who);
long long GetCombatPower(OBJECT* pObj);