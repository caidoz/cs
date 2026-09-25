//이 파일은 CastleData.h 에 있던 배열 정의를 옮겨 담은 것이다.
//
//헤더에 const로 정의하면 내부 링크라 포함하는 .cpp마다 복제되고,
//무엇보다 런타임에 채울 수가 없다. 정의는 여기 한 곳에만 둔다.
//
//자기 헤더만 가져온다. Data.h를 통째로 끌면 UIData.h의 std::string
//때문에 cocos2d.h가 필요해지고, 그러면 팩 생성기가 이 파일만 따로
//컴파일할 수 없다.
//
//tools/content/datafiles.py 가 갈랐다.

#include "CastleData.h"
#include "../Def.h"
#include "../Cmf.h"

static const int castleOrder_builtin[] = {
	//이 배열은 content/ 의 tsv에서 생성된다. 직접 고치지 말 것.
	//고치려면 tsv를 고치고 tools/content/content_table.py 를 돌린다.

	CASTLE_TOLEM,	//0 (무명)
	CASTLE_SWAMP,	//1 (무명)
	CASTLE_VALLEY,	//2 (무명)
	CASTLE_ATLANTICE,	//3 (무명)
	CASTLE_PLAIN,	//4 (무명)
	CASTLE_ELF,	//5 (무명)
	CASTLE_FLAME,	//6 (무명)
	CASTLE_FROST,	//7 (무명)
	CASTLE_SEWAGE,	//8 (무명)
	CASTLE_THUNDER,	//9 (무명)
	CASTLE_GOLEMVALLEY,	//10 (무명)
	CASTLE_DARKNESS,	//11 (무명)
	CASTLE_LIGHT,	//12 (무명)
	CASTLE_GHOST,	//13 (무명)
	CASTLE_DRAGON,	//14 (무명)
	CASTLE_ADELINE,	//15 (무명)
	CASTLE_DEVILCASTLE,	//16 (무명)
	CASTLE_SPACE,	//17 (무명)
	CASTLE_ARENA,	//18 (무명)
};
static const int castleBoxColor_builtin[] = {
	//이 배열은 content/ 의 tsv에서 생성된다. 직접 고치지 말 것.
	//고치려면 tsv를 고치고 tools/content/content_table.py 를 돌린다.

	0xDBBA8F,	//0 (무명)
	0xF3D58F,	//1 (무명)
	0x00FF00,	//2 (무명)
	0x54BBF7,	//3 (무명)
	0xF8DFA8,	//4 (무명)
	0x888D6D,	//5 (무명)
	0xFFFFFF,	//6 (무명)
	0xB9F3FD,	//7 (무명)
	0xD9F567,	//8 (무명)
	0xF56A15,	//9 (무명)
	0xFFFFFF,	//10 (무명)
	0x511C6B,	//11 (무명)
	0xFDCE4D,	//12 (무명)
	0xC5B9AE,	//13 (무명)
	0xFCE9BD,	//14 (무명)
	0x5E4272,	//15 (무명)
	0x592965,	//16 (무명)
	0xFFFFFF,	//17 (무명)
	0xFFFFFF,	//18 (무명)
};
static const long long castleBoxGold_builtin[] = {
	//이 배열은 content/ 의 tsv에서 생성된다. 직접 고치지 말 것.
	//고치려면 tsv를 고치고 tools/content/content_table.py 를 돌린다.

	10000,	//0 (무명)
	500000000,	//1 (무명)
	50000,	//2 (무명)
	100000,	//3 (무명)
	200000,	//4 (무명)
	6000000,	//5 (무명)
	100000000,	//6 (무명)
	500000,	//7 (무명)
	1000000,	//8 (무명)
	2000000,	//9 (무명)
	3500000,	//10 (무명)
	10000000,	//11 (무명)
	35000000,	//12 (무명)
	15000000,	//13 (무명)
	23000000,	//14 (무명)
	70000000,	//15 (무명)
	50000000,	//16 (무명)
	150000000,	//17 (무명)
	300000000,	//18 (무명)
};
static const int castleStarLimit_builtin[] = {
	//이 배열은 content/ 의 tsv에서 생성된다. 직접 고치지 말 것.
	//고치려면 tsv를 고치고 tools/content/content_table.py 를 돌린다.

	20,	//0 (무명)
	110,	//1 (무명)
	25,	//2 (무명)
	30,	//3 (무명)
	35,	//4 (무명)
	40,	//5 (무명)
	45,	//6 (무명)
	50,	//7 (무명)
	115,	//8 (무명)
	55,	//9 (무명)
	60,	//10 (무명)
	70,	//11 (무명)
	75,	//12 (무명)
	80,	//13 (무명)
	85,	//14 (무명)
	90,	//15 (무명)
	95,	//16 (무명)
	100,	//17 (무명)
	105,	//18 (무명)
};
static const int setHeroPos_builtin[] = {
	//CASTLE_TOLEM
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

	//CASTLE_ARENA
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

	//CASTLE_SWAMP
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

	//CASTLE_VALLEY
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

	//CASTLE_ATLANTICE
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

	//CASTLE_SEWAGE
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

	//CASTLE_ADELINE
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

	//CASTLE_PLAIN
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

	//CASTLE_ELF
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

	//CASTLE_FLAME
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

	//CASTLE_FROST
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

	//CASTLE_THUNDER
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

	//CASTLE_LIGHT
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

	//CASTLE_GOLEMVALLEY
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

	//CASTLE_DARKNESS
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

	//CASTLE_DRAGON
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

	//CASTLE_GHOST
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

	//CASTLE_DEVILCASTLE
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

	//CASTLE_SPACE
	LOBBYPOSITION_X, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP, 17 * TSIZE,
	LOBBYPOSITION_X - HEROPOSITIONGAP * 2, 17 * TSIZE,

};
static const int setEnemyPos_builtin[] = {
	//CASTLE_TOLEM
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

	//CASTLE_ARENA
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

	//CASTLE_SWAMP
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

	//CASTLE_VALLEY
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

	//CASTLE_ATLANTICE
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

	//CASTLE_SEWAGE
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

	//CASTLE_ADELINE�
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

	//CASTLE_PLAIN
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

	//CASTLE_ELF
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

	//CASTLE_FLAME
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

	//CASTLE_FROST
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

	//CASTLE_THUNDER
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

	//CASTLE_LIGHT
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

	//CASTLE_GOLEMVALLEY
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

	//CASTLE_DARKNESS
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

	//CASTLE_DRAGON
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

	//CASTLE_GHOST
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

	//CASTLE_DEVILCASTLE
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

	//CASTLE_SPACE
	BATTLEPOSITION_ENEMY_X, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 2, TSIZE * 17,
	BATTLEPOSITION_ENEMY_X + (TSIZE + TSIZE / 3) * 4, TSIZE * 17,

};
static const int castleCrewPosition_builtin[] = {
	//CASTLE_TOLEM
	TSIZE * 4 - TSIZE / 2, TSIZE * 9,
	TSIZE * 6 - TSIZE / 2, TSIZE * 9,
	TSIZE * 8 - TSIZE / 2, TSIZE * 9,
	TSIZE * 12 + TSIZE / 2, TSIZE * 9,
	TSIZE * 14 + TSIZE / 2, TSIZE * 9,
	TSIZE * 16 + TSIZE / 2, TSIZE * 9,
	//CASTLE_ARENA
	TSIZE * 3, TSIZE * 10,
	TSIZE * 3, TSIZE * 7 - TSIZE / 2,
	TSIZE * 8, TSIZE * 8,
	TSIZE * 12, TSIZE * 8,
	TSIZE * 17 - TSIZE / 4, TSIZE * 7 - TSIZE / 2,
	TSIZE * 17 - TSIZE / 4, TSIZE * 10,
	//CASTLE_SWAMP
	TSIZE * 4 - TSIZE / 2, TSIZE * 9 + TSIZE / 2,
	TSIZE * 6 - TSIZE / 2, TSIZE * 9 + TSIZE * 3 / 4,
	TSIZE * 8 - TSIZE / 2, TSIZE * 9 + TSIZE,
	TSIZE * 12 + TSIZE / 2, TSIZE * 9 + TSIZE,
	TSIZE * 14 + TSIZE / 2, TSIZE * 9 + TSIZE * 3 / 4,
	TSIZE * 16 + TSIZE / 2, TSIZE * 9 + TSIZE / 2,
	//CASTLE_VALLEY
	TSIZE * 4 - TSIZE / 2, TSIZE * 9 + TSIZE * 3 / 4,
	TSIZE * 6 - TSIZE / 2, TSIZE * 9 + TSIZE,
	TSIZE * 8 - TSIZE / 2, TSIZE * 9 + TSIZE,
	TSIZE * 12, TSIZE * 9 + TSIZE,
	TSIZE * 14, TSIZE * 9 + TSIZE,
	TSIZE * 16, TSIZE * 9 + TSIZE * 3 / 4,
	//CASTLE_ATLANTICE
	TSIZE * 4 + TSIZE / 2, TSIZE * 9 + TSIZE * 3 / 4,
	TSIZE * 6, TSIZE * 9 + TSIZE,
	TSIZE * 7 + TSIZE / 2, TSIZE * 9 + TSIZE,
	TSIZE * 12 + TSIZE / 2, TSIZE * 9 + TSIZE,
	TSIZE * 14, TSIZE * 9 + TSIZE,
	TSIZE * 16 - TSIZE / 2, TSIZE * 9 + TSIZE * 3 / 4,
	//CASTLE_SEWAGE
	TSIZE * 4 - TSIZE / 2 + TSIZE / 4, TSIZE * 11,
	TSIZE * 6 - TSIZE / 2 + TSIZE / 8, TSIZE * 11,
	TSIZE * 8 - TSIZE / 2, TSIZE * 11,
	TSIZE * 12 + TSIZE / 2, TSIZE * 11,
	TSIZE * 14 + TSIZE / 2 - TSIZE / 8, TSIZE * 11,
	TSIZE * 16 + TSIZE / 2 - TSIZE / 4, TSIZE * 11,
	//CASTLE_ADELINE
	TSIZE * 3 - TSIZE / 4, TSIZE * 9 + TSIZE * 1 / 2,
	TSIZE * 5 + TSIZE / 4, TSIZE * 11,
	TSIZE * 8 + TSIZE / 2, TSIZE * 11,
	TSIZE * 12 - TSIZE / 4, TSIZE * 11,
	TSIZE * 15 - TSIZE / 4, TSIZE * 10 + TSIZE / 2,
	TSIZE * 18 - TSIZE / 4, TSIZE * 9 + TSIZE * 1 / 2,
	//CASTLE_PLAIN
	TSIZE * 5, TSIZE * 8,
	TSIZE * 7 - TSIZE / 4, TSIZE * 8,
	TSIZE * 9 - TSIZE / 2, TSIZE * 8,
	TSIZE * 11 + TSIZE / 2, TSIZE * 8,
	TSIZE * 13 + TSIZE / 4, TSIZE * 8,
	TSIZE * 15, TSIZE * 8,
	//CASTLE_ELF
	TSIZE * 4, TSIZE * 9,
	TSIZE * 6 - TSIZE / 2, TSIZE * 9,
	TSIZE * 7, TSIZE * 9,
	TSIZE * 13, TSIZE * 9,
	TSIZE * 14 + TSIZE / 2, TSIZE * 9,
	TSIZE * 16, TSIZE * 9,
	//CASTLE_FLAME
	TSIZE * 4, TSIZE * 10,
	TSIZE * 6 - TSIZE / 2, TSIZE * 10,
	TSIZE * 7, TSIZE * 10,
	TSIZE * 13, TSIZE * 10,
	TSIZE * 14 + TSIZE / 2, TSIZE * 10,
	TSIZE * 16, TSIZE * 10,
	//CASTLE_FROST
	TSIZE * 4 - TSIZE / 2, TSIZE * 9 + TSIZE * 3 / 4,
	TSIZE * 6 - TSIZE / 2, TSIZE * 9 + TSIZE + TSIZE / 8,
	TSIZE * 8 - TSIZE / 2, TSIZE * 9 + TSIZE + TSIZE / 4,
	TSIZE * 12 + TSIZE / 2, TSIZE * 9 + TSIZE + TSIZE / 4,
	TSIZE * 14 + TSIZE / 2, TSIZE * 9 + TSIZE + TSIZE / 8,
	TSIZE * 16 + TSIZE / 2, TSIZE * 9 + TSIZE * 3 / 4,
	//CASTLE_THUNDER
	TSIZE * 4, TSIZE * 11,
	TSIZE * 6, TSIZE * 11,
	TSIZE * 8, TSIZE * 11,
	TSIZE * 12, TSIZE * 11,
	TSIZE * 14, TSIZE * 11,
	TSIZE * 16, TSIZE * 11,
	//CASTLE_LIGHT
	TSIZE * 4 - TSIZE / 2, TSIZE * 11,
	TSIZE * 6 - TSIZE / 2 - TSIZE / 4, TSIZE * 11,
	TSIZE * 8 - TSIZE / 2 - TSIZE / 2, TSIZE * 11,
	TSIZE * 12 + TSIZE / 2 + TSIZE / 4, TSIZE * 11,
	TSIZE * 14 + TSIZE / 4 + TSIZE / 4, TSIZE * 11,
	TSIZE * 16 + TSIZE / 4, TSIZE * 11,
	//CASTLE_GOLEMVALLEY
	TSIZE * 5 - TSIZE / 4, TSIZE * 8 - TSIZE / 4,
	TSIZE * 7 - TSIZE / 2, TSIZE * 8 - TSIZE / 4,
	TSIZE * 9 - TSIZE / 2, TSIZE * 9,
	TSIZE * 11 + TSIZE / 2, TSIZE * 9,
	TSIZE * 13 + TSIZE / 2, TSIZE * 8 - TSIZE / 4,
	TSIZE * 15 + TSIZE / 4, TSIZE * 8 - TSIZE / 4,
	//CASTLE_DARKNESS
	TSIZE * 4 - TSIZE / 2, TSIZE * 11 - TSIZE / 4,
	TSIZE * 6 - TSIZE / 2, TSIZE * 11 - TSIZE / 4,
	TSIZE * 8 - TSIZE / 2, TSIZE * 11 - TSIZE / 4,
	TSIZE * 12 + TSIZE / 2, TSIZE * 11 - TSIZE / 4,
	TSIZE * 14 + TSIZE / 2, TSIZE * 11 - TSIZE / 4,
	TSIZE * 16 + TSIZE / 2, TSIZE * 11 - TSIZE / 4,
	//CASTLE_DRAGON
	TSIZE * 2 - TSIZE / 4, TSIZE * 10,
	TSIZE * 5 - TSIZE / 4, TSIZE * 11 - TSIZE / 4,
	TSIZE * 7 - TSIZE / 2, TSIZE * 11 - TSIZE / 4,
	TSIZE * 13 + TSIZE / 2, TSIZE * 11 - TSIZE / 4,
	TSIZE * 15 + TSIZE / 4, TSIZE * 11 - TSIZE / 4,
	TSIZE * 18 + TSIZE / 4, TSIZE * 10,
	//CASTLE_GHOST
	TSIZE * 5, TSIZE * 8 + TSIZE / 4,
	TSIZE * 7 - TSIZE / 4, TSIZE * 8 + TSIZE / 4,
	TSIZE * 8 + TSIZE / 2, TSIZE * 7 + TSIZE / 4 + TSIZE / 8,
	TSIZE * 12 - TSIZE / 2 + TSIZE / 4, TSIZE * 7 + TSIZE / 4 + TSIZE / 8,
	TSIZE * 13 + TSIZE / 4 + TSIZE / 8, TSIZE * 8 + TSIZE / 4,
	TSIZE * 15 + TSIZE / 4, TSIZE * 8 + TSIZE / 4,
	//CASTLE_DEVILCASTLE
	TSIZE * 4, TSIZE * 12,
	TSIZE * 6, TSIZE * 12,
	TSIZE * 8, TSIZE * 12,
	TSIZE * 12, TSIZE * 12,
	TSIZE * 14, TSIZE * 12,
	TSIZE * 16, TSIZE * 12,
	//CASTLE_SPACE
	TSIZE * 4, TSIZE * 9 + TSIZE * 3 / 4,
	TSIZE * 6 - TSIZE / 4, TSIZE * 10 + TSIZE / 4,
	TSIZE * 8 - TSIZE / 2, TSIZE * 10 + TSIZE / 4,
	TSIZE * 12, TSIZE * 10 + TSIZE / 4,
	TSIZE * 14, TSIZE * 10 + TSIZE / 4,
	TSIZE * 16, TSIZE * 9 + TSIZE * 3 / 4,
};

// x, y, width, height. castleOrder가 가리키는 실제 성 번호 순서다.
static const int lobbyCrewArea_builtin[] = {
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // TOLEM courtyard: y grows downwards
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // ARENA courtyard: y grows downwards
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // SWAMP courtyard: y grows downwards
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // VALLEY courtyard: y grows downwards
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // ATLANTICE courtyard: y grows downwards
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // SEWAGE courtyard: y grows downwards
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // ADELINE courtyard: y grows downwards
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // PLAIN courtyard: y grows downwards
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // ELF courtyard: y grows downwards
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // FLAME courtyard: y grows downwards
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // FROST courtyard: y grows downwards
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // THUNDER courtyard: y grows downwards
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // LIGHT courtyard: y grows downwards
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // GOLEMVALLEY courtyard: y grows downwards
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // DARKNESS courtyard: y grows downwards
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // DRAGON courtyard: y grows downwards
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // GHOST courtyard: y grows downwards
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // DEVILCASTLE courtyard: y grows downwards
	TSIZE * 3, TSIZE * 16 + TSIZE / 2, TSIZE * 14, TSIZE * 5 / 2, // SPACE courtyard: y grows downwards
};

//게임이 읽는 포인터. 처음에는 내장 기본값을 가리키고, 부팅 때
//팩을 읽으면 그쪽으로 옮겨간다. const는 가리키는 대상에 붙으므로
//게임 코드는 대상을 못 건드리고, 로더만 자기 버퍼를 채워 넘긴다.

const int* castleOrder = castleOrder_builtin;
const int* castleBoxColor = castleBoxColor_builtin;
const long long* castleBoxGold = castleBoxGold_builtin;
const int* castleStarLimit = castleStarLimit_builtin;
const int* setHeroPos = setHeroPos_builtin;
const int* setEnemyPos = setEnemyPos_builtin;
const int* castleCrewPosition = castleCrewPosition_builtin;
const int* lobbyCrewArea = lobbyCrewArea_builtin;
//---- 성의 가방 칸 ----
//
//성마다 가방으로 쓰는 격자 칸을 적은 표다. 칸 하나가 {열, 행} 한 쌍이고,
//행 0 이 맨 아랫줄이다(성은 아래가 넓다). 열과 행은 GRIDTEST_W x GRIDTEST_H
//(12 x 6) 안에 있어야 한다.
//
//castleGridCellStart[성] 에서부터 castleGridCellCnt[성] 쌍이 그 성의 칸이다.
//
//처음 값은 "두 줄마다 양옆을 한 칸씩 들이는" 사다리꼴 식으로 뽑았다.
//식으로 두지 않고 표로 둔 것은 모양을 성마다 손으로 다듬을 수 있어야
//해서다 - 탑 모양, 가운데가 빈 모양처럼 식으로는 못 만드는 것이 많다.
//칸을 더하거나 빼면 Cnt 와 그 뒤 성들의 Start 도 같이 고친다.
//---- 성 열 단계의 가방 ----
//
//검이 2x4(8칸)까지로 줄면서 가방도 그 규격에 맞췄다. 템빨용사가 26칸에서
//48칸이라 그 틀을 따라 24 -> 48 로 간다. 아래가 넓고 위로 갈수록 좁아지는
//성 실루엣이며, 폭 12 · 높이 6 안에서 가운데를 맞춰 쌓는다(행 0 이 맨 아랫줄).
//
//tools 로 뽑은 표다. 모양을 손으로 다듬어도 된다 - 칸을 더하거나 빼면
//Cnt 와 그 뒤 성들의 Start 도 같이 고친다.
static const signed char castleGridCell_builtin[] = {
	//성 1 - 24칸
	0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0,
	8, 0, 9, 0, 10, 0, 11, 0, 0, 1, 1, 1, 2, 1, 3, 1,
	4, 1, 5, 1, 6, 1, 7, 1, 8, 1, 9, 1, 10, 1, 11, 1,
	//성 2 - 26칸
	0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0,
	8, 0, 9, 0, 10, 0, 11, 0, 0, 1, 1, 1, 2, 1, 3, 1,
	4, 1, 5, 1, 6, 1, 7, 1, 8, 1, 9, 1, 10, 1, 11, 1,
	5, 2, 6, 2,
	//성 3 - 29칸
	0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0,
	8, 0, 9, 0, 10, 0, 11, 0, 0, 1, 1, 1, 2, 1, 3, 1,
	4, 1, 5, 1, 6, 1, 7, 1, 8, 1, 9, 1, 10, 1, 11, 1,
	3, 2, 4, 2, 5, 2, 6, 2, 7, 2,
	//성 4 - 32칸
	0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0,
	8, 0, 9, 0, 10, 0, 11, 0, 0, 1, 1, 1, 2, 1, 3, 1,
	4, 1, 5, 1, 6, 1, 7, 1, 8, 1, 9, 1, 10, 1, 11, 1,
	2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 2, 8, 2, 9, 2,
	//성 5 - 35칸
	0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0,
	8, 0, 9, 0, 10, 0, 11, 0, 0, 1, 1, 1, 2, 1, 3, 1,
	4, 1, 5, 1, 6, 1, 7, 1, 8, 1, 9, 1, 10, 1, 11, 1,
	1, 2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 2, 8, 2,
	9, 2, 10, 2, 5, 3,
	//성 6 - 38칸
	0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0,
	8, 0, 9, 0, 10, 0, 11, 0, 0, 1, 1, 1, 2, 1, 3, 1,
	4, 1, 5, 1, 6, 1, 7, 1, 8, 1, 9, 1, 10, 1, 11, 1,
	1, 2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 2, 8, 2,
	9, 2, 10, 2, 4, 3, 5, 3, 6, 3, 7, 3,
	//성 7 - 41칸
	0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0,
	8, 0, 9, 0, 10, 0, 11, 0, 0, 1, 1, 1, 2, 1, 3, 1,
	4, 1, 5, 1, 6, 1, 7, 1, 8, 1, 9, 1, 10, 1, 11, 1,
	1, 2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 2, 8, 2,
	9, 2, 10, 2, 2, 3, 3, 3, 4, 3, 5, 3, 6, 3, 7, 3,
	8, 3,
	//성 8 - 44칸
	0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0,
	8, 0, 9, 0, 10, 0, 11, 0, 0, 1, 1, 1, 2, 1, 3, 1,
	4, 1, 5, 1, 6, 1, 7, 1, 8, 1, 9, 1, 10, 1, 11, 1,
	1, 2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 2, 8, 2,
	9, 2, 10, 2, 2, 3, 3, 3, 4, 3, 5, 3, 6, 3, 7, 3,
	8, 3, 9, 3, 5, 4, 6, 4,
	//성 9 - 46칸
	0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0,
	8, 0, 9, 0, 10, 0, 11, 0, 0, 1, 1, 1, 2, 1, 3, 1,
	4, 1, 5, 1, 6, 1, 7, 1, 8, 1, 9, 1, 10, 1, 11, 1,
	1, 2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 2, 8, 2,
	9, 2, 10, 2, 2, 3, 3, 3, 4, 3, 5, 3, 6, 3, 7, 3,
	8, 3, 9, 3, 4, 4, 5, 4, 6, 4, 7, 4,
	//성 10 - 48칸
	0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0,
	8, 0, 9, 0, 10, 0, 11, 0, 0, 1, 1, 1, 2, 1, 3, 1,
	4, 1, 5, 1, 6, 1, 7, 1, 8, 1, 9, 1, 10, 1, 11, 1,
	1, 2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 2, 8, 2,
	9, 2, 10, 2, 2, 3, 3, 3, 4, 3, 5, 3, 6, 3, 7, 3,
	8, 3, 9, 3, 3, 4, 4, 4, 5, 4, 6, 4, 7, 4, 8, 4,

};

const int castleGridCellCnt[TOTALCASTLE] = {
	24, 26, 29, 32, 35, 38, 41, 44, 46, 48,
	//열 단계 뒤의 성은 쓰지 않는다(gTotalCastle 이 10 이다).
	48, 48, 48, 48, 48, 48, 48, 48, 48,
};

const int castleGridCellStart[TOTALCASTLE] = {
	0, 24, 50, 79, 111, 146, 184, 225, 269, 315,
	315, 315, 315, 315, 315, 315, 315, 315, 315,
};

const signed char* castleGridCell = castleGridCell_builtin;

