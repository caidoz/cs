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
int GetBuffDurationMode(int buffIdx);
void ActivateBuff(OBJECT *pObj, int buffIdx, int value);
bool ConsumeBuffUse(OBJECT *pObj, int buffIdx);
void AdvanceTurnBuffs(void);
void RefreshQuestTime(void);
void RefreshHeartTime(void);
void RefreshEnemyTime(void);

// Combat Formula
long long NextExp(int);
int NextExpEquip(ITEM *, int);
int GetLevelUpRewardLv(int type, int userLv);
void LevelUp(int getExp);
void LevelUpObj(OBJECT *, int);
void PlusHp(OBJECT *, long long int);
void PlusMp(OBJECT *, long long int);
long long int GetAbsorb(OBJECT *, long long int);
int GetAttackRange(int);
void SetWheel(void);
int GetSpeed(int);
int GetAtk(int);
long long GetRouletteValue(int actioncCardType, int itemType, int itemDetail, int itemGrade, int itemLv);
void AttackRobin(int, int);
int AttackRobin_Back(int, int);
int AttackObj(long long int, int);
int AttackObj2(int, int, int, int);
int AttackEnemyCheck(int);
int EnemyCheck(int);
void AttackPlayerCheck(OBJECT *);
void AttackBoxCheck(OBJECT *);
void NeutralCheck(OBJECT *);
void SetDmgNum(int, int, long long, int, int, float);
int SetImgText(int, int, float);
void SetHitMark(int, int, int, int, int, int, float);
void SetCurrencyMarkArr(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, long long amount, int type, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2, int iconMarkCnt, int bar);
void SetCurrencyMarkArr_PopUp(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, long long amount, int type, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2, int iconMarkCnt);
void SetCurrencyMark_PopUp(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, int amount, int type, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2);
void SetCurrencyMark(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, int amount, int type, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2, int bar);
int SetItemMark(int, int, int, int, int, int, int, int);
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
int SetBoxMark(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int moveAngle, int detail, int grade, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2);
int SetBoxCardMark(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, int amount,
	int type, int detail, int grade, int cooldown, bool text, bool value, bool ani, int owner, bool star, bool cardFrame, bool newItem, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2);

int NearPlayer(OBJECT* pObj);
int NearEnemy(OBJECT* pObj);
int TargetPlayer(int);
int TargetEnemy(int);

long long GetCombatPowerAll(int who);
long long GetCombatPower(OBJECT* pObj);
