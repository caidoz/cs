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
long MC_knlCurrentTimeStamp(void);

void DoubleBuffering(int);
void PaintClet(int x, int y, int w, int h);

#endif