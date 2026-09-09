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
void ActivateDebuf(OBJECT* pObj, int debufIdx, int frameValue, int owner);
void AdvanceTurnDebuffs(void);
bool AdvanceActorDebuffs(int obj);
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
	int attackType, int attackStr, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2, int alpha, bool text, bool value, bool ani, int owner, bool openFrame, bool screenSpace);
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

//전투 확률 눈금을 비운다. 개체가 새로 설 때 부른다.
void ClearProcAcc(int obj);

/*---------------------------------------------------------------------------
 * 데미지 계산에 들어가는 값.
 *
 * AttackObj 가 여기저기서 긁어 쓰던 것을 한 자리에 모았다. 이 구조체가 곧
 * "한 대의 데미지를 내려면 무엇을 알아야 하는가"의 답이고, 나중에 서버가
 * 같은 값을 내려면 넘겨받아야 할 목록이기도 하다.
 *-------------------------------------------------------------------------*/
typedef struct _dmgInput {
	//때리는 쪽
	long long int atk;		//GetAtk(공격자)
	int dmgPct;			//ps[PS_DMG]
	int critDmgPct;			//ps[PS_CRITDMG]
	int extraSkillPct;		//회전력상승. 안 걸렸으면 0
	int attackerLv;
	int attackerType;		//weaponRange 를 찾는 자리
	bool cursed;			//공격자가 저주에 걸렸나

	//맞는 쪽
	int destLv;
	int destType;
	int destEtc;
	int destMotion;
	long long int destArmor;	//ps[PS_ARMOR]

	//이번 한 대의 성질
	bool critical;
	bool ignoreArmor;
	int attackAttr;			//0 이면 무속성

	//바깥에서 정해지는 배수
	int betMul;			//betHeart[bet]
	int skillPct;			//동료 스킬 배수. 없으면 100
} DMGINPUT;

//셋을 차례로 밟는다. 중간에 낄 일이 없는 쪽(룰렛 시점 예측)은 이것만 부른다.
long long int CalcDamage(const DMGINPUT* in);

long long int CalcBaseDamage(const DMGINPUT* in, long long int* outBeforeRange);
long long int CalcGuardReduction(long long int damage, const DMGINPUT* in);
long long int CalcArmorBetSkill(long long int damage, const DMGINPUT* in);

//액션 계획. 룰렛이 확정될 때 세우고, 턴이 끝날 때 지운다.
//자세한 설명은 Func_Combat.cpp 의 정의부에 있다.
void ActionPlanBegin(int owner, int skill);
void ActionPlanEnd(void);
long long int ActionPlanTake(int attacker, int dest, long long int oneHit);

//계획이 정해 둔 치명타 여부. 계획에 속하지 않으면 false 를 준다.
bool ActionPlanCriticalOf(int attacker, bool* outCritical);
