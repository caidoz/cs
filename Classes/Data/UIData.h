#pragma once

#ifndef _DATA_UI_H_
#define _DATA_UI_H_
//이 헤더가 std::string(fontList)을 쓴다. 예전에는 Data.h 를 포함하는
//.cpp 들이 앞서 cocos2d.h 를 가져와 우연히 가려져 있었을 뿐이다.
//이제 UIData.cpp 가 이 헤더만 가지고 컴파일되므로 직접 가져와야 한다.
#include <string>
#include "../Def.h"
#include "../Cmf.h"

// ===== UI 아이콘 및 그래픽 데이터 =====

extern const int* colorSet;
enum { colorSet_COUNT = 52 };

extern const unsigned short* currencyIcon;
enum { currencyIcon_COUNT = 10 };

extern const int* solidPosition;
enum { solidPosition_COUNT = 8 };

extern const int* openFrame;
enum { openFrame_COUNT = 7 };

extern const short* statIcon;
enum { statIcon_COUNT = 6 };

// ===== 메뉴 상태 및 아이콘 데이터 =====
// CLOSED: 아예 시스템이 없는 것
// OPEN: 시스템은 있으나 아직 게임 진행상 오픈이 되지 않은 상태
extern const unsigned char* menuOpened;
enum { menuOpened_COUNT = 24 };

extern const unsigned short* listMenuIcon;
enum { listMenuIcon_COUNT = 22 };


extern const signed short* crewPos;
enum { crewPos_COUNT = 2155 };

extern const signed short* enemyIconPos;
enum { enemyIconPos_COUNT = 1293 };

extern const signed short* enemyBigIconPos;
enum { enemyBigIconPos_COUNT = 1293 };


extern const signed short* enemySkillIconPos;
enum { enemySkillIconPos_COUNT = 1293 };


extern const signed short* cardImgBg;
enum { cardImgBg_COUNT = 114 };


extern const int* equipIconPos;
enum { equipIconPos_COUNT = 12 };

extern const int* runMotion;
enum { runMotion_COUNT = 4 };

extern const int* curtainPosX;
enum { curtainPosX_COUNT = 240 };

extern const signed short* raidEquipPos;
enum { raidEquipPos_COUNT = 12 };

extern const int* scrollDx;
enum { scrollDx_COUNT = 6 };


static std::string fontList[] =

{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	// info.plist 에 사용자가 추가한 ttf 를 정의해야 한다.
	"NanumBarunGothicLight",
#else
	"NanumBarunGothicLight.ttf",
#endif

};


extern const int* cardFrameColorData;
enum { cardFrameColorData_COUNT = 60 };

extern const int* colorData;
enum { colorData_COUNT = 56 };



extern const int* activeSkillCardBg;
enum { activeSkillCardBg_COUNT = 21 };

extern const unsigned short* mainMenuWidth;
enum { mainMenuWidth_COUNT = 5 };


extern const unsigned short* titleMIC;
enum { titleMIC_COUNT = 6 };


extern const unsigned short* effectMIC;
enum { effectMIC_COUNT = 556 };

extern const unsigned short* hitMIC;
enum { hitMIC_COUNT = 102 };

extern const unsigned short* objMIC;
enum { objMIC_COUNT = 604 };

extern const unsigned short* bgObjMIC;
enum { bgObjMIC_COUNT = 402 };

extern const unsigned char* palette;
enum { palette_COUNT = 2048 };


extern const unsigned char* blindFrame;
enum { blindFrame_COUNT = 9 };

extern const unsigned short* alertData;
enum { alertData_COUNT = 45 };

extern const unsigned short* skillTreePos;
enum { skillTreePos_COUNT = 360 };

extern const unsigned int* fontGradiation;
enum { fontGradiation_COUNT = 21 };

extern const signed short* enemyWinPos;
enum { enemyWinPos_COUNT = 8 };


extern const int* shakePosX;
enum { shakePosX_COUNT = 6 };
extern const int* shakePosY;
enum { shakePosY_COUNT = 6 };

extern const unsigned int* selectColor;
enum { selectColor_COUNT = 4 };


extern const int* goldQuestPositionData;
enum { goldQuestPositionData_COUNT = 20 };
#endif