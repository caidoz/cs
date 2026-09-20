#pragma once

//======================================================================
// 몬스터가 끼는 장비
//
// 히어로와 같은 규칙이다. 장착 무기 하나로 제 공격 모션을 내고, 가방에
// 든 무기는 저마다 제 쿨타임으로 검을 날린다.
//
// 값은 상점 표(Func_Draw.cpp 의 kShopPart) 번호다:
//     0 롱소드   1 플레임소드  2 아이스소드  3 엑스칼리버
//     4 강철투구 5 판금갑옷    6 가죽장갑    7 사슬바지  8 가죽신
//     9 반지
// FOEGEAR_NONE 은 빈 칸이다.
//
// 표에 없는 몬스터는 종류와 판 수로 굴려서 정한다(Func_Draw 의
// StageFoeGearList). 세워 두고 싶은 몬스터부터 여기에 한 줄씩 적으면
// 그 줄이 굴림보다 앞선다.
//======================================================================
#define FOEGEAR_NONE	(-1)
#define FOEGEAR_BAGMAX	4

struct FoeGearRow {
	short type;						//ENEMY_* 몬스터 번호
	signed char equip;				//장착 무기. 제 공격 모션으로 친다
	signed char bag[FOEGEAR_BAGMAX];//가방 무기/방어구. 검은 날아간다
};

static const FoeGearRow foeGearRow[] = {
	//달팽이는 껍질이 갑옷이다. 무는 것 말고는 들고 있는 것이 없다.
	{ ENEMY_SNAIL,     FOEGEAR_NONE, { 5, FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE } },

	//늪의 주인은 긴 팔로 후려친다. 긴 검 한 자루와 같다.
	{ ENEMY_TREE,      0, { FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE } },

	//아이볼은 몸이 곧 무기다. 대신 반지를 하나 낀다.
	{ ENEMY_ONEEYE,    FOEGEAR_NONE, { 9, FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE } },

	//칠흑의 기사. 검을 쥐고 투구와 갑옷을 갖춰 입었다.
	{ ENEMY_SKELETON,  0, { 1, 4, 5, FOEGEAR_NONE } },

	//사하긴병사는 창을 든 잡병이다. 갑옷은 가죽뿐이다.
	{ ENEMY_LIZARD,    0, { 6, FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE } },

	//맹독해파리는 때리지 않고 스친다. 장신구만 걸친다.
	{ ENEMY_JELLYFISH, FOEGEAR_NONE, { 9, 8, FOEGEAR_NONE, FOEGEAR_NONE } },

	//타락한 기사. 이 판에서 제일 잘 갖춘 놈이다.
	{ ENEMY_KNIGHT,    1, { 0, 4, 5, 7 } },

	//슬라임은 아무것도 안 낀다. 첫 판의 기준점이다.
	{ ENEMY_SLIME,     FOEGEAR_NONE, { FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE } },

	//평원의 도적은 단검 둘을 번갈아 던진다.
	{ ENEMY_SLING,     0, { 0, 6, FOEGEAR_NONE, FOEGEAR_NONE } },

	//거친발멧돼지는 들이받는다. 가죽신으로 빠르기만 올린다.
	{ ENEMY_BOAR,      FOEGEAR_NONE, { 8, FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE } },

	//분노의 정령과 마성의 불새는 불을 쓴다.
	{ ENEMY_FLAME,     1, { FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE } },
	{ ENEMY_PHOENIX,   1, { 1, 9, FOEGEAR_NONE, FOEGEAR_NONE } },

	//얼음 쪽은 아이스소드를 든다.
	{ ENEMY_FACE,      2, { FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE } },
	{ ENEMY_SNOWMAN,   2, { 4, FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE } },
	{ ENEMY_ICESUN,    2, { 2, 9, FOEGEAR_NONE, FOEGEAR_NONE } },
};

enum { FOEGEARROWCNT = (int)(sizeof(foeGearRow) / sizeof(foeGearRow[0])) };
