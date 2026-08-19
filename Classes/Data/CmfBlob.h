#pragma once

#ifndef _DATA_CMFBLOB_H_
#define _DATA_CMFBLOB_H_

//tools/content/pack_cmf.py 가 생성한다. 직접 고치지 말 것.
//
//Classes/Cmf/c*.h 에 흩어져 있던 모션 배열을 가족별로 하나씩 이어붙인
//것이다. 어느 cmf가 어디서 시작하는지는 <이름>Idx 가 들고 있다.
//
//    i번 cmf의 자료 = Blob[Idx[i]] .. Blob[Idx[i + 1]] 앞까지
//
//평범한 1차원 배열이라 팩에 그대로 들어간다. 표(cmfOff 등)는 부팅 때
//CmfRelink() 가 이 둘로 채운다.

#include "../Def.h"

extern const unsigned short* cmfOffBlob;
enum { cmfOffBlob_COUNT = 12692 };

extern const unsigned int* cmfOffSlot;
enum { cmfOffSlot_COUNT = 429 };

extern const signed short* cmfMotionImgBlob;
enum { cmfMotionImgBlob_COUNT = 311556 };

extern const unsigned int* cmfMotionImgSlot;
enum { cmfMotionImgSlot_COUNT = 429 };

extern const unsigned short* cmfMotionImgCntBlob;
enum { cmfMotionImgCntBlob_COUNT = 18364 };

extern const unsigned int* cmfMotionImgCntSlot;
enum { cmfMotionImgCntSlot_COUNT = 429 };

extern const signed short* cmfMotionImgSizeBlob;
enum { cmfMotionImgSizeBlob_COUNT = 36728 };

extern const unsigned int* cmfMotionImgSizeSlot;
enum { cmfMotionImgSizeSlot_COUNT = 429 };

extern const signed short* cmfCrashSizeBlob;
enum { cmfCrashSizeBlob_COUNT = 73456 };

extern const unsigned int* cmfCrashSizeSlot;
enum { cmfCrashSizeSlot_COUNT = 429 };

extern const unsigned short* cmfHeroLoopBlob;
enum { cmfHeroLoopBlob_COUNT = 192 };

extern const unsigned int* cmfHeroLoopIdx;
enum { cmfHeroLoopIdx_COUNT = 4 };

extern const signed short* cmfMoveInfoBlob;
enum { cmfMoveInfoBlob_COUNT = 50382 };

extern const unsigned int* cmfMoveInfoSlot;
enum { cmfMoveInfoSlot_COUNT = 429 };

//cmf 개수. 표를 채울 때 쓴다.
enum { CMF_BUILTIN_COUNT = 429, CMF_HERO_COUNT = 3 };

#endif

