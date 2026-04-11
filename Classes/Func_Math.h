#pragma once
#ifndef _FUNC_MATH_H_
#define _FUNC_MATH_H_
// 수학함수
unsigned int SqrtX256(unsigned int);
int BC_mathSin1024(int);
int BC_mathCos1024(int);
int BC_mathTan1024(int);
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
signed char GetBit(signed char *, int);
void SetBit(signed char *, int);
void UnSetBit(signed char *, int);
int TriHeight(int, int, int, int, int, int);

double degreesToRadians(double degrees);
Point rotatePoint(const Point& point, double angle);
Point translatePoint(const Point& point, double dx, double dy);

bool IsActionCardActive(int arr[], int size, int index, int value, int numConsecutive);
void bubble_sort(long long int list[], int n, long long int orderList[]);
void bubble_sort_int(int list[], int n, int orderList[]);
int arrValueIdx(int list[], int val, int cnt);
int bestOfThree(int value1, int value2, int value3);
#endif