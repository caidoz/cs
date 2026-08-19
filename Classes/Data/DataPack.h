#pragma once

#ifndef _DATA_PACK_H_
#define _DATA_PACK_H_

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

//팩과 클라이언트가 같은 빌드 상수를 쓰는지 확인하는 목록.
//여기 있는 값이 하나라도 달라지면 옛 팩은 못 쓴다.
#define DATAPACK_ABI_LIST(X) \
	X(_2X) \
	X(TSIZE) \
	X(FPS) \
	X(TOTALENEMY) \
	X(ENEMYDATASIZE) \
	X(ATTACKPATTERNDATASIZE) \
	X(TOTAL_SKILL) \
	X(SKILLDATASIZE) \
	X(TOTAL_CREW) \
	X(CREWDATASIZE) \
	X(TOTALCASTLE)

//값이 아니라 "정의됐는지"만 보는 것들.
//
// 배열 안에 #ifdef 분기가 있어서 설정에 따라 값이 달라지는 것들이 있다
// (alphaData, gameEventOpenStage, robinSkillMotion, battleRewardMedal,
//  skillDescMod, alphaOff, menuOpened).
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

//팩을 읽어 포인터들을 옮긴다. 성공하면 true.
//실패하면 아무것도 바꾸지 않는다. 포인터는 내장 기본값을 계속 가리킨다.
bool DataPackLoad(const char* fileName);

//지금 읽어 쓰고 있는 팩이 있는지. 없으면 내장본으로 도는 중이다.
bool DataPackInUse(void);

#endif
