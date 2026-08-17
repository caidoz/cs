#pragma once
#ifndef _FUNC_INPUT_H_
#define _FUNC_INPUT_H_
// KeyPress
void KeyCore(void);
void TitleKey(void);
void PlayKey(int);
void DemoKey(void);
void AlertKey(void);
void ClearRoom(void);
bool IsMovingSkill(int idx);
void HotKeyPress(OBJECT *, int);
void GachaKey(void);
void NewCardKey(void);

// KeyRelease
void ReleaseCore(bool dispatchKey = true);
void PlayRelease(OBJECT *);
void ReleasePlayer(OBJECT *);

// Touch 관련
int GetTouchFunc(int, int);
void ExecTouchFunc(int, int);
int GetRectPoint(int, int, int, int, int, int);
void ResetRectPoint(void);
bool IsTouchFuncEnabled(int func);
void SetRectPoint(int rx, int ry, int width, int height, int func);
void touchFunc(int func);
void RaiseHeartBet(void);
void SaveFlag(int whitch);

// JoyStick 관련
bool JoyStickPressPossible(void);
bool menuPressPossible(void);
void JoyStickPressGoldQuest(void);
void BoxOpen(void);
void JoyStickRelease(void);

int GetBetHeart(int itemDetail, int itemGrade, int betGrade);

int printCoords(void);
int printBoxCoords(void);
bool rectContainsTouchPoint(int x, int y, int w, int h);
#endif