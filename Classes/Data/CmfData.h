#pragma once

#ifndef _DATA_CMF_H_
#define _DATA_CMF_H_
#include "../Def.h"
#include "../Cmf.h"

//CMF
//ONEEYE
//SKELETON
// X충돌에 의해 버그 발생 가능성 많음 - 추후 수정바랍니다.
//JELLYFISH
//LIZARD
//SALAMANDER --BOSS--
//SLING 새총맨
//BOAR
//GIANT 아델평원 보스
//FLAME
//PHOENIX
//SNOWMAN
//FACE 삼두상
//PUMPKIN
// 무브할때 한칸내려감
// 도벨
//가젤
//라베스
//엘케인
//순서 바꿀때 124번 END데모신 참조
//엘레인
//에반
extern const signed short* cmfImgOff;
enum { cmfImgOff_COUNT = 2145 };

//---- cmf 표 ----
//
//예전에는 여기에 { c0Off, c1Off, ... } 하고 주소를 늘어놓았다. 세 가지가
//나빴다. (1) 주소라 팩에 못 담는다. (2) const 라 내부 링크여서 이 헤더를
//포함하는 .cpp 마다 한 벌씩 복제됐다. (3) cmfMoveInfo 는 c0mv 같은 런타임
//포인터로 초기화되는데 그 초기화가 main() 전에 끝나서, 팩을 읽어도
//cmfMoveInfo 는 내장 주소를 그대로 들고 있었다. 팩을 무시하고 있었다.
//
//이제는 CmfBlob 하나에 이어붙여 두고, 부팅 때와 팩을 읽은 뒤에 CmfRelink()
//가 이 표를 채운다. 호출부의 cmfOff[i][j] 는 그대로다.

extern const unsigned short* cmfOff[CAP_CMF];
extern const signed short* cmfMotionImg[CAP_CMF];
extern const unsigned short* cmfMotionImgCnt[CAP_CMF];
extern const signed short* cmfMotionImgSize[CAP_CMF];
extern const signed short* cmfCrashSize[CAP_CMF];
extern const signed short* cmfMoveInfo[CAP_CMF];
extern const unsigned short* cmfHeroLoop[CAP_CMF_HERO];

extern int cmfHeroLoopCnt;

//표를 채운다. 부팅 때 한 번, 팩을 읽을 때마다 한 번 부른다.
void CmfRelink(void);


extern const unsigned short* cmfTotalMotion;
enum { cmfTotalMotion_COUNT = 429 };

extern const unsigned short* cmfTotalOff;
enum { cmfTotalOff_COUNT = 429 };

extern const unsigned short* cmfVar;
enum { cmfVar_COUNT = 429 };

//cmfMove 는 지웠다.
//
//모션 자료 자체가 아니라 "각 mv 배열의 길이"만 담은 429칸짜리 표였다.
//모션 자료는 cmfMoveInfo 가 들고 있고 Func_Cmf.cpp 가 쓴다. 그건 그대로
//살아 있다(CmfBlob 의 cmfMoveInfoBlob).
//
//지운 이유는 둘이다.
//  1. 읽는 곳이 하나도 없다.
//  2. 값이 이미 깨져 있었다. sizeof(c0mv) / 4 로 계산했는데, 07ac979
//     "데이터 배열 482개를 팩 파일로 뺐다" 에서 c0mv 가 배열에서 포인터로
//     바뀌면서 sizeof 가 4를 주게 되어 429칸이 전부 1이 됐다. 아무도 안
//     읽어서 드러나지 않았다.
//
//다시 필요해지면 CmfBlob 에서 그대로 얻을 수 있다. 옛 값은 배열 길이의
//절반이었다(short 배열이라 sizeof / 4 = 원소수 / 2).
//
//    cmfMove[i] == (cmfMoveInfoIdx[i + 1] - cmfMoveInfoIdx[i]) / 2


extern const unsigned short* costumeSize;
enum { costumeSize_COUNT = 36 };

extern const unsigned short* costumeOff;
enum { costumeOff_COUNT = 600 };
#endif