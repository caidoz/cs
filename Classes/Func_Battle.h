#pragma once
#include "Core.h"

// Battle 관련 함수
void Play(void);
void AttackSequenceDraw(void);
void EnemySequenceDraw(void);
void RaidSequenceDraw(void);
void PvpEventBarDraw(GAMEEVENT * gEvent, int x, int y, int icon, int count, int max, bool animation, bool questAni, float zoom);
void InfoDraw(void);
void DiscountMenuDraw(int, int, float zoom);
void PvpQuestMenuDraw(int, int, float zoom);
void QuestMenuDraw(int, int, float zoom);
void QuestDraw(int x, int y, int icon, int count, int max, float animation, bool questAni, int enemyIconShow, int rewardIconShow, int alpha, float zoom);
void RaidControlerDraw(void);
void SetScreenRatio(void);
void SetHero(void);
void SetBattleCrew(void);

// 3-day boss raid combat state (no admission fee or attack cost).
void InitBossRaidMercenarySystem(void);
void ResetBossRaidMercenarySystem(void);
void AddBossRaidEarnedHeart(int count);

//이번 판에서 지금까지 먹은 하트.
int GetBossRaidEarnedHeart(void);

//이번 판에서 먹을 수 있는 하트의 최대치. 보스 체력에서 나온다.
//
//일반 하트바처럼 robin.heart 에 더해 가는 것이 아니라, 이 판 안에서만
//차오르는 별도의 목표다. 그래서 최대치도 보스가 정한다.
long long GetBossRaidHeartMax(void);
bool BossRaidConsumeBasicShot(int crewSlot);
bool BossRaidActivateCrewSkill(int crewSlot, int skillLevel);
void BossRaidFinishCrewSkill(OBJECT* pObj);
int GetBossRaidSkillFreezeOwner(void);
void DrawBossRaidMercenaryUI(void);
//보스 난입 때 기존 HUD 가 빠져나가는 데 걸리는 프레임.
//
//sequenceDelay 를 이 값으로 세우고, GetBossRaidEntranceProgress() 가
//같은 값으로 나눈다. 두 자리가 어긋나면 진행도가 1 을 넘거나 못 미친다.
#define BOSSRAID_EXIT_FRAMES	(FPS * 3 / 4)

void BeginBossRaidEntrance(void);
void StartBossRaidBattleIntro(void);
float GetBossRaidEntranceProgress(void);
float GetBossRaidWorldScale(void);
// 시작 대기 중 첫 입력을 소비했으면 true를 반환한다.
bool BossRaidNotifyControlInput(void);

//보스전이 첫 터치를 기다리는 중인가. TAP TO START 가 떠 있는 동안 참이다.
bool IsBossRaidWaitingForControl(void);

//그 동료가 지금 실제로 공격 동작을 돌리고 있는가.
//보스전은 턴이 없어 전역 turn 하나로 여섯을 가릴 수 없다.
bool IsBossRaidCrewActing(int crewSlot);
