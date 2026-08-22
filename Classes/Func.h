#pragma once
#ifndef _FUNC_H_
#define _FUNC_H_

// 분리된 함수 선언 헤더들을 모두 포함
#include "Func_Bar.h"
#include "Func_Battle.h"
#include "Func_Cmf.h"
#include "Func_Combat.h"
#include "Func_Draw.h"
#include "Func_Gacha.h"
#include "Func_Graphics.h"
#include "Func_Input.h"
#include "Func_Item.h"
#include "Func_Map.h"
#include "Func_Math.h"
#include "Func_Menu.h"
#include "Func_Movement.h"
#include "Func_Net.h"
#include "Func_Object.h"
#include "Func_Roulette.h"
#include "Func_Sound.h"
#include "Func_System.h"
#include "Func_Text.h"
#include "Func_Utility.h"
#include "Func_Demo.h"
#include "Content.h"

// wipi-c Function
long MC_knlCurrentTime(void);
//게임이 쓰는 시각. 2000-01-01 부터의 초.
//
//기기 시계에 서버 오프셋(gNetTimeOffset)을 더한 값이다. 기기 시계를 앞으로
//돌려도 일일 초기화나 쿨타임이 안 흔들린다. 서버에 못 붙었으면 오프셋이 0이라
//기기 시계를 그대로 쓴다.
long MC_knlCurrentTimeStamp(void);

//기기 시계 그대로. 오프셋을 안 더한다.
//
//서버 흉내를 내는 쪽(Func_Net.cpp 의 임시 로컬 서버)과 오프셋 계산이 쓴다.
//거기서 MC_knlCurrentTimeStamp() 를 쓰면 "서버 시간으로 서버 시간을 정하는"
//꼴이 되어 값이 자기를 물고 돈다.
long MC_knlRawTimeStamp(void);

void DoubleBuffering(int);
void PaintClet(int x, int y, int w, int h);

#endif