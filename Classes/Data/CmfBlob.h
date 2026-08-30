#pragma once

#ifndef _DATA_CMFBLOB_H_
#define _DATA_CMFBLOB_H_

//tools/content/pack_cmf.py 가 생성한다. 직접 고치지 말 것.
//
//Classes/Cmf/c*.h 에 흩어져 있던 모션 배열을 가족별로 하나씩 이어붙인
//것이다. 슬롯마다 어디서 시작하는지는 <이름>Slot 이 들고 있다.
//
//    i번 슬롯의 자료 = Blob + Slot[i] 부터
//
//슬롯은 429개인데 서로 다른 자료는 123개다. 슬롯 123부터는 몬스터
//변종이라 앞 cmf 를 나눠 쓴다. 그래서 여러 슬롯이 같은 자리를 가리킨다.
//
//평범한 1차원 배열이라 팩에 그대로 들어간다. 표(cmfOff 등)는 부팅 때
//CmfRelink() 가 이 둘로 채운다.

#include "../Def.h"

extern const unsigned short* cmfOffBlob;
enum { cmfOffBlob_COUNT = 12692 };

extern const unsigned int* cmfOffSlot;
enum { cmfOffSlot_COUNT = 429 };

extern const signed short* cmfMotionImgBlob;
enum { cmfMotionImgBlob_COUNT = 306052 };

extern const unsigned int* cmfMotionImgSlot;
enum { cmfMotionImgSlot_COUNT = 429 };

extern const unsigned short* cmfMotionImgCntBlob;
enum { cmfMotionImgCntBlob_COUNT = 18002 };

extern const unsigned int* cmfMotionImgCntSlot;
enum { cmfMotionImgCntSlot_COUNT = 429 };

extern const signed short* cmfMotionImgSizeBlob;
enum { cmfMotionImgSizeBlob_COUNT = 36004 };

extern const unsigned int* cmfMotionImgSizeSlot;
enum { cmfMotionImgSizeSlot_COUNT = 429 };

extern const signed short* cmfCrashSizeBlob;
enum { cmfCrashSizeBlob_COUNT = 72008 };

extern const unsigned int* cmfCrashSizeSlot;
enum { cmfCrashSizeSlot_COUNT = 429 };

extern const unsigned short* cmfHeroLoopBlob;
enum { cmfHeroLoopBlob_COUNT = 192 };

extern const unsigned int* cmfHeroLoopSlot;
enum { cmfHeroLoopSlot_COUNT = 3 };

extern const signed short* cmfMoveInfoBlob;
enum { cmfMoveInfoBlob_COUNT = 49476 };

extern const unsigned int* cmfMoveInfoSlot;
enum { cmfMoveInfoSlot_COUNT = 429 };

//슬롯 개수. 표를 채울 때 쓴다. 서로 다른 자료 수가 아니다.
//슬롯 칸수다. 자료 가짓수(123)가 아니다. 몬스터 변종은 앞 cmf 의 자료를
//나눠 쓰므로 자료는 123 벌뿐이지만 슬롯은 429 칸이다. 여기에 123 을 적으면
//CmfRelink 가 123 번 이후 슬롯을 전부 0 번으로 접어, 색만 다른 변종이
//죄다 cmf 0 의 그림으로 나온다.
enum { CMF_BUILTIN_COUNT = 429, CMF_HERO_COUNT = 3 };

#endif

