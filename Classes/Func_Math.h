#pragma once
#ifndef _FUNC_MATH_H_
#define _FUNC_MATH_H_
// 수학함수
unsigned int SqrtX256(unsigned int);
int BC_mathSin1024(int);
int BC_mathCos1024(int);
int Random(int);
int GotoObjXY(OBJECT *pObj, int targetX, int targetY, int speed);
int GotoObjZoom(OBJECT *target, OBJECT *pObj, int speed, int xPlus, int yPlus, float zoomInc, float zoomEnd);
int GotoObj(OBJECT *, OBJECT *, int);
int GotoPositionLog(int, int, int, int, int);
int GotoPositionBar(BAR * bar, int targetX, int targetY, int speed);
int GotoEventMenu(int targetX, int targetY, int eventMenuIdx, int speed, int type);
int GotoPosition(int, int, int, int, int);
int Proc(const unsigned short *, int);
long long int RoundDiv(long long int num, long long int divider);
long long int UpDiv(long long int, long long int);
void SetBit(signed char *, int);
int TriHeight(int, int, int, int, int, int);


#endif