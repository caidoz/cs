#pragma once
#include "../Def.h"

#ifndef _DATA_COLLECTION_H_
#define _DATA_COLLECTION_H_

extern const int* collectionLvLimit;
enum { collectionLvLimit_COUNT = 24 };

//소팅을 별이 낮은것부터 높은것까지 해야 된다.
extern const int* collectionData;
enum { collectionData_COUNT = 720 };

extern const unsigned char* collectionsCategoryInfo;
enum { collectionsCategoryInfo_COUNT = 72 };
#endif