#pragma once

#ifndef _DATA_PACK_H_
#define _DATA_PACK_H_

//아래에서 #ifdef SETITEM 같은 것을 본다. 그 매크로가 여기 오기 전에 이미
//정의돼 있어야 한다. 포함하는 쪽 순서에 맡기면, DataPack.cpp 처럼 Def.h
//보다 먼저 이 헤더를 넣는 곳에서는 전부 "정의 안 됨"으로 읽힌다. 그러면
//클라이언트가 계산한 ABI 지문이 팩과 영원히 달라진다.
#include "../Config/BuildConfig.h"
#include "../Config/Capacity.h"

//=============================================================================
// 데이터 팩
//
// 게임 데이터를 소스에서 빼내 파일로 옮기기 위한 형식이다.
//
// [왜]
// 지금 데이터가 전부 소스에 박혀 있어서, 몬스터 하나를 추가하거나 밸런스
// 숫자 하나를 고쳐도 앱을 새로 올려야 한다. 파일로 빼면 CDN으로 갈아끼울 수
// 있다.
//
// [만드는 쪽]
// 값의 59%가 CMF_SNAIL, TSIZE * 3 같은 이름과 식이라 로더가 못 읽는다.
// 그래서 팩은 빌드 때 만든다. 다만 파이썬으로 식을 해석하지 않는다.
// 데이터 .cpp를 그대로 컴파일해서 "컴파일러가 이미 계산해 둔 배열"을 그대로
// 써낸다(tools/content/make_pack.py). 값이 어긋날 여지가 없다.
//
// [읽는 쪽]
// 배열마다 포인터가 하나씩 있고(Data/*.h), 부팅 때 그 포인터를 팩 안쪽으로
// 옮긴다. 호출부의 enemyData[i] 는 그대로 동작한다.
// 팩이 없거나 깨졌으면 포인터는 내장 기본값을 그대로 가리킨다.
//
// [ABI]
// 값에는 TSIZE, _2X 같은 빌드 상수가 이미 곱해진 채로 들어간다. 클라이언트를
// 올리면서 그 상수를 바꾸면 옛 팩은 조용히 틀린 값이 된다. 그래서 팩 머리에
// 상수 지문을 적고, 다르면 팩을 거부하고 내장본을 쓴다.
//=============================================================================

//원소 종류. 크기만으로는 float와 int를 구분할 수 없다.
enum {
	DPK_INT = 0,	//signed
	DPK_UINT,		//unsigned
	DPK_FLOAT,
};

enum {
	DPK_MAGIC = 0x314B5049,		//"IPK1"
	DPK_NAMELEN = 32,
	DPK_ENTRYSIZE = 48,
};

//배열이 무엇에 맞춰 길어지는가.
//
//enemyZoom 은 몬스터가 늘면 같이 는다. unicode_table 은 안 는다. 이걸
//구분해야 "몬스터가 늘어난 팩"을 받아들일 수 있다. 예전에는 모든 배열의
//길이가 내장본과 똑같아야 해서, 콘텐츠를 하나도 못 늘렸다.
//
//  NONE  : 길이가 고정. 내장본과 정확히 같아야 한다.
//  그 외 : 길이 = 개수 * 폭. 개수가 용량 이하이기만 하면 된다.
//          같은 키를 쓰는 배열끼리는 개수가 서로 같아야 한다.
enum {
	DPK_KEY_NONE = 0,
	DPK_KEY_ENEMY,
	DPK_KEY_CREW,
	DPK_KEY_SKILL,
	DPK_KEY_CASTLE,
	DPK_KEY_MAP,
	DPK_KEY_CMF,
	DPK_KEY_CMF_HERO,

	//길이가 아무래도 되는 것. blob 이 여기 든다. 몇 칸이든 Idx 가 어디서
	//끊어 읽을지 말해주므로 길이 자체에는 뜻이 없다. 그래서 안 잰다.
	DPK_KEY_FREE,

	DPK_KEY_MAX,
};

//키별 용량. Config/Capacity.h 의 CAP_* 와 짝이다.
int DataPackCapOf(int key);

//팩과 클라이언트가 같은 빌드 상수를 쓰는지 확인하는 목록.
//여기 있는 값이 하나라도 달라지면 옛 팩은 못 쓴다.
//
//"용량"은 들어가고 "개수"는 안 들어간다. 이게 핵심이다.
//예전에는 TOTALENEMY(개수)가 여기 있었다. 그러면 몬스터를 하나 늘린 팩을
//기존 클라이언트가 거부해서, CDN으로 콘텐츠를 추가할 수가 없었다.
//지금은 CAP_ENEMY(용량)를 본다. 용량 안에서 몇 마리든 팩이 정하면 된다.
//개수는 팩 안의 배열 길이가 말해준다(DataCount.h 의 gTotalEnemy 등).
//
//행 너비(ENEMYDATASIZE 등)는 그대로 둔다. 이건 개수가 아니라 형식이라,
//달라지면 팩을 못 읽는 게 맞다.
#define DATAPACK_ABI_LIST(X) \
	X(_2X) \
	X(TSIZE) \
	X(FPS) \
	X(CAP_ENEMY) \
	X(CAP_CREW) \
	X(CAP_SKILL) \
	X(CAP_CASTLE) \
	X(CAP_MAP) \
	X(CAP_CMF) \
	X(CAP_CMF_HERO) \
	X(ENEMYDATASIZE) \
	X(ATTACKPATTERNDATASIZE) \
	X(SKILLDATASIZE) \
	X(CREWDATASIZE)

//값이 아니라 "정의됐는지"만 보는 것들.
//
// 배열 안에 #ifdef 분기가 있어서 설정에 따라 값이 달라지는 것들이 있다
// (gameEventOpenStage, robinSkillMotion, battleRewardMedal,
//  skillDescMod, menuOpened).
// 팩에는 만들 때의 설정으로 정해진 값이 들어가므로, 설정이 바뀐 클라이언트가
// 옛 팩을 쓰면 조용히 틀린 값이 된다. 지문에 넣어 막는다.
//
// 문자열 이어붙이기로 쓴다. 매크로 전개 안에서는 #ifdef 를 못 쓴다.
#define DATAPACK_ABI_FLAGS \
	"SETITEM=" DPK_F_SETITEM ";" \
	"GAMEDEBUG=" DPK_F_GAMEDEBUG ";" \
	"ATTACK_INIT_DELAY=" DPK_F_ATTACK_INIT_DELAY ";" \
	"ROBINDEFAULTATTACKSTING=" DPK_F_ROBINDEFAULTATTACKSTING ";" \
	"BATTLEABSOLUTE=" DPK_F_BATTLEABSOLUTE ";" \
	"AIR2XDMG=" DPK_F_AIR2XDMG ";" \
	"IRON=" DPK_F_IRON ";"

#ifdef SETITEM
#define DPK_F_SETITEM "1"
#else
#define DPK_F_SETITEM "0"
#endif

#ifdef GAMEDEBUG
#define DPK_F_GAMEDEBUG "1"
#else
#define DPK_F_GAMEDEBUG "0"
#endif

#ifdef ATTACK_INIT_DELAY
#define DPK_F_ATTACK_INIT_DELAY "1"
#else
#define DPK_F_ATTACK_INIT_DELAY "0"
#endif

#ifdef ROBINDEFAULTATTACKSTING
#define DPK_F_ROBINDEFAULTATTACKSTING "1"
#else
#define DPK_F_ROBINDEFAULTATTACKSTING "0"
#endif

#ifdef BATTLEABSOLUTE
#define DPK_F_BATTLEABSOLUTE "1"
#else
#define DPK_F_BATTLEABSOLUTE "0"
#endif

#ifdef AIR2XDMG
#define DPK_F_AIR2XDMG "1"
#else
#define DPK_F_AIR2XDMG "0"
#endif

#ifdef IRON
#define DPK_F_IRON "1"
#else
#define DPK_F_IRON "0"
#endif

unsigned int DataPackAbi(void);
unsigned int DataPackCrc(const void* buf, unsigned int len);

//팩 안에서 이름으로 항목을 찾는다. 없으면 NULL.
const unsigned char* DataPackFind(const unsigned char* dir, int count,
	const char* name, unsigned int* outCount, int* outSize, int* outKind);

//팩이 이 클라이언트와 맞는지 본다. 0이면 맞는다. 아니면 어긋난 항목 수.
//msg 에 사유를 적고, outKeyCount 에 키별 콘텐츠 개수를 담는다(없으면 -1).
//cocos를 안 쓴다. DataPackCheck.cpp 참고.
int DataPackCheck(const unsigned char* buf, long size,
	int* outKeyCount, char* msg, int msglen);

//팩을 읽어 포인터들을 옮긴다. 성공하면 true.
//실패하면 아무것도 바꾸지 않는다. 포인터는 내장 기본값을 계속 가리킨다.
bool DataPackLoad(const char* fileName);

//지금 읽어 쓰고 있는 팩이 있는지. 없으면 내장본으로 도는 중이다.
bool DataPackInUse(void);

//읽어둔 팩에서 배열의 칸 수를 돌려준다. 팩이 없거나 그 배열이 없으면 -1.
//콘텐츠 개수를 여기서 얻는다(DataCount.cpp).
int DataPackCount(const char* name);

#endif
