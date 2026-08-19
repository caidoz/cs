//이 파일은 ShopData.h 에 있던 배열 정의를 옮겨 담은 것이다.
//
//헤더에 const로 정의하면 내부 링크라 포함하는 .cpp마다 복제되고,
//무엇보다 런타임에 채울 수가 없다. 정의는 여기 한 곳에만 둔다.
//
//자기 헤더만 가져온다. Data.h를 통째로 끌면 UIData.h의 std::string
//때문에 cocos2d.h가 필요해지고, 그러면 팩 생성기가 이 파일만 따로
//컴파일할 수 없다.
//
//tools/content/datafiles.py 가 갈랐다.

#include "ShopData.h"
#include "../Def.h"
#include "../Cmf.h"

static const int currencyShop_builtin[] = {
	//상품이름, 아이콘, 할인율, 아이템 종류, 지급량, 지급화폐종류, 지급화폐수량
	TEXT_CURRENCY_HEART, ICON_HEART, 0, CURRENCY_HEART, 100, CURRENCY_CASH, 1000,
	TEXT_CURRENCY_HEART, ICON_HEART, 20, CURRENCY_HEART, 300, CURRENCY_CASH, 2000,
	TEXT_CURRENCY_HEART, ICON_HEART, 50, CURRENCY_HEART, 1000, CURRENCY_CASH, 5000,
	TEXT_CURRENCY_HEART, ICON_HEART, 80, CURRENCY_HEART, 5000, CURRENCY_CASH, 20000,
	TEXT_CURRENCY_HEART, ICON_HEART, 120, CURRENCY_HEART, 15000, CURRENCY_CASH, 50000,
	TEXT_CURRENCY_HEART, ICON_HEART, 140, CURRENCY_HEART, 50000, CURRENCY_CASH, 100000,
	//장비뽑기
	TEXT_CURRENCY_COIN, 64 * 3 + 19, 1, 64 * 3 + 19, 1, CURRENCY_GOLD, 1000000,
	TEXT_CURRENCY_COIN, 64 * 3 + 20, 2, 64 * 3 + 20, 2, CURRENCY_GOLD, 3000000,
	TEXT_CURRENCY_COIN, 64 * 3 + 21, 3, 64 * 3 + 21, 3, CURRENCY_GOLD, 5000000,
	//코인 
	TEXT_CURRENCY_COIN, ICON_GOLD, 0, CURRENCY_GOLD, 1000000, CURRENCY_CASH, 10000,
	TEXT_CURRENCY_COIN, ICON_GOLD, 10, CURRENCY_GOLD, 2500000, CURRENCY_CASH, 20000,
	TEXT_CURRENCY_COIN, ITEM_GOLDBAR_ICON, 30, CURRENCY_GOLD, 7000000, CURRENCY_CASH, 50000,
	TEXT_CURRENCY_COIN, ITEM_GOLDBAR_ICON, 60, CURRENCY_GOLD, 15000000, CURRENCY_CASH, 20000,
	TEXT_CURRENCY_COIN, ICON_GOLDBAG, 85, CURRENCY_GOLD, 50000000, CURRENCY_CASH, 50000,
	TEXT_CURRENCY_COIN, ICON_GOLDBAG, 120, CURRENCY_GOLD, 125000000, CURRENCY_CASH, 100000,
	//메달
	TEXT_CURRENCY_MEDAL, ICON_MEDAL, 1, CURRENCY_MEDAL, 100, CURRENCY_COIN, 100,
	TEXT_CURRENCY_MEDAL, ICON_MEDAL, 2, CURRENCY_MEDAL, 500, CURRENCY_COIN, 500,
	TEXT_CURRENCY_MEDAL, ICON_MEDAL, 3, CURRENCY_MEDAL, 1000, CURRENCY_COIN, 1000,

};
static const unsigned char quickShopData_builtin[] = {
	//1 : type
	//2 : detail
	//3 : broken
	//4 : 가격
	//5 : count
	20,	29,	24,	5,		19,	1,		//|i초심자 패키지
	21,	29,	25,	2,		29,	1,		//|i슈퍼강화 패키지
	22,	29,	26,	5,		29,	1,		//|i스톤 패키지
	23,	29,	27,	4,		29,	1,		//|i투기장 패키지
	34,	29,	28,	3,		20,	1,		//|i행운 패키지
	10,	29,	9,		1,		9,		1,		//|g고급무기상자
	11,	29,	12,	1,		7,		1,		//|g고급방어구상자
	12,	29,	15,	1,		9,		1,		//|g고급악세사리상자
	14,	29,	19,	1,		3,		1,		//|d고급보석상자
	13,	29,	18,	1,		1,		1,		//|e랜덤아이템상자
	15,	29,	20,	0,		7,		1,		//|e가방
	18,	29,	22,	0,		7,		1,		//|dAP초기화
	19,	29,	23,	0,		7,		1,		//|dSP초기화
	//35,	29,	3,		1,		4,		1,		//|e보호석
	32,	29,	8,		1,		8,		10,	//|e부활약
	9,		29,	8,		1,		19,	25,	//|e부활약
	2,		29,	1,		1,		5,		1,		//|d투기장 입장권
	3,		29,	2,		1,		19,	20,	//|e강화석
	4,		29,	3,		1,		19,	5,		//|e보호석
	5,		29,	4,		1,		19,	5,		//|e조합석
	6,		29,	5,		1,		19,	20,	//|e분해석
	7,		29,	6,		1,		19,	20,	//|e소켓석
	31,	29,	0,		1,		2,		5,		//|b쿠폰
	1,		29,	0,		1,		29,	100,	//|b쿠폰
	24,	21,	23,	1,		9,		20,	//|e강화의 비약
	25,	21,	24,	1,		9,		20,	//|e인내의 비약
	26,	21,	25,	1,		9,		20,	//|e치유의 비약
	27,	21,	26,	1,		9,		20,	//|e마법의 비약
};

//게임이 읽는 포인터. 처음에는 내장 기본값을 가리키고, 부팅 때
//팩을 읽으면 그쪽으로 옮겨간다. const는 가리키는 대상에 붙으므로
//게임 코드는 대상을 못 건드리고, 로더만 자기 버퍼를 채워 넘긴다.

const int* currencyShop = currencyShop_builtin;
const unsigned char* quickShopData = quickShopData_builtin;
