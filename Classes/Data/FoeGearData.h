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

//----------------------------------------------------------------------
// 몬스터 53종
//
// 색 변종(_RED, _BLUE ...)은 적지 않는다. 몬스터 등급(별)이 난이도에
// 들어가므로 변종은 저절로 세진다(Func_Draw 의 StageFoeTier).
//
// 한 줄은 "그 놈이 무엇을 끼는가" 일 뿐이다. 실제 등급과 번호는 나오는
// 시점의 난이도가 정한다 - 같은 기사라도 1판과 후반이 다르다.
//
// 무기 없음(FOEGEAR_NONE)은 맨몸으로 친다는 뜻이다. 몸이 곧 무기인 놈
// (슬라임 · 멧돼지 · 유령)을 그렇게 둔다.
//----------------------------------------------------------------------
static const FoeGearRow foeGearRow[] = {
	{ ENEMY_SNAIL,             FOEGEAR_NONE, { 5,            FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE  } },	//껍질이 갑옷이다
	{ ENEMY_TREE,              0,            { FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE  } },	//긴 팔로 후려친다
	{ ENEMY_ONEEYE,            FOEGEAR_NONE, { 9,            FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE  } },	//몸이 곧 무기다
	{ ENEMY_SKELETON,          0,            { 1,            4,            5,            FOEGEAR_NONE  } },	//검을 쥔 해골 기사
	{ ENEMY_LIZARD,            0,            { 6,            FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE  } },	//창을 든 잡병
	{ ENEMY_JELLYFISH,         FOEGEAR_NONE, { 9,            8,            FOEGEAR_NONE, FOEGEAR_NONE  } },	//스쳐서 독을 남긴다
	{ ENEMY_KNIGHT,            1,            { 0,            4,            5,            7             } },	//이 구간에서 가장 잘 갖췄다
	{ ENEMY_SLIME,             FOEGEAR_NONE, { FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE  } },	//맨몸. 첫 판의 기준점
	{ ENEMY_SLING,             0,            { 0,            6,            FOEGEAR_NONE, FOEGEAR_NONE  } },	//단검 둘을 번갈아
	{ ENEMY_BOAR,              FOEGEAR_NONE, { 8,            FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE  } },	//들이받는다
	{ ENEMY_FLAME,             1,            { FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE  } },	//불 그 자체
	{ ENEMY_PHOENIX,           1,            { 1,            9,            FOEGEAR_NONE, FOEGEAR_NONE  } },	//불꽃을 두르고 난다
	{ ENEMY_FACE,              2,            { FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE  } },	//얼어붙은 석상
	{ ENEMY_SNOWMAN,           2,            { 4,            FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE  } },	//눈을 뭉쳐 던진다
	{ ENEMY_ICESUN,            2,            { 2,            9,            FOEGEAR_NONE, FOEGEAR_NONE  } },	//얼음 가면
	{ ENEMY_LIGHTNING,         1,            { 9,            FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE  } },	//번개는 빠르다
	{ ENEMY_THUNDER,           1,            { 2,            9,            FOEGEAR_NONE, FOEGEAR_NONE  } },	//먹구름을 몰고 온다
	{ ENEMY_CRYSTAL,           FOEGEAR_NONE, { 5,            9,            FOEGEAR_NONE, FOEGEAR_NONE  } },	//수정 껍데기
	{ ENEMY_FAIRY,             FOEGEAR_NONE, { 9,            9,            FOEGEAR_NONE, FOEGEAR_NONE  } },	//빛의 정령. 장신구만
	{ ENEMY_CIRCLE,            FOEGEAR_NONE, { 9,            6,            FOEGEAR_NONE, FOEGEAR_NONE  } },	//환영을 두른다
	{ ENEMY_SPIDER,            0,            { 6,            8,            FOEGEAR_NONE, FOEGEAR_NONE  } },	//다리가 많아 빠르다
	{ ENEMY_GOLEM,             FOEGEAR_NONE, { 5,            4,            7,            FOEGEAR_NONE  } },	//돌덩이가 갑옷이다
	{ ENEMY_DARKGIANT,         1,            { 5,            4,            7,            8             } },	//큰 몸에 큰 장비
	{ ENEMY_DARKDRAGON,        3,            { 5,            4,            9,            FOEGEAR_NONE  } },	//어둠의 용
	{ ENEMY_DRAGON1,           3,            { 5,            4,            FOEGEAR_NONE, FOEGEAR_NONE  } },	//비늘이 곧 방어구
	{ ENEMY_DRAGON2,           3,            { 5,            4,            9,            FOEGEAR_NONE  } },	//더 자란 용
	{ ENEMY_GHOST,             FOEGEAR_NONE, { 9,            FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE  } },	//만질 수 없다
	{ ENEMY_PUMPKIN,           0,            { 4,            9,            FOEGEAR_NONE, FOEGEAR_NONE  } },	//호박 머리
	{ ENEMY_CASTLE1,           1,            { 0,            4,            5,            7             } },	//성을 지키는 병사
	{ ENEMY_CASTLE2,           1,            { 1,            4,            5,            7             } },	//성을 지키는 대장
	{ ENEMY_SPACE1,            2,            { 2,            5,            9,            FOEGEAR_NONE  } },	//별에서 온 것
	{ ENEMY_SPACE2,            3,            { 2,            5,            9,            8             } },	//더 먼 별에서
	{ ENEMY_FROG,              FOEGEAR_NONE, { 8,            FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE  } },	//혀로 친다
	{ ENEMY_LARVA,             FOEGEAR_NONE, { FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE  } },	//아직 어리다
	{ ENEMY_SALAMANDER,        1,            { 1,            5,            FOEGEAR_NONE, FOEGEAR_NONE  } },	//불도마뱀
	{ ENEMY_GIANT,             0,            { 5,            4,            7,            FOEGEAR_NONE  } },	//거인의 몽둥이
	{ ENEMY_IFRIT,             1,            { 1,            5,            9,            FOEGEAR_NONE  } },	//불의 군주
	{ ENEMY_MAMMOTH,           FOEGEAR_NONE, { 5,            4,            7,            8             } },	//두꺼운 털가죽
	{ ENEMY_MACHINE,           2,            { 5,            4,            6,            9             } },	//강철 몸체
	{ ENEMY_ANGEL,             3,            { 4,            9,            9,            FOEGEAR_NONE  } },	//빛의 무기
	{ ENEMY_KIMERA,            1,            { 0,            5,            6,            FOEGEAR_NONE  } },	//여럿이 섞인 몸
	{ ENEMY_SHIP,              2,            { 5,            9,            FOEGEAR_NONE, FOEGEAR_NONE  } },	//배 자체가 몸이다
	{ ENEMY_FOGRA,             3,            { 5,            4,            7,            9             } },	//안개의 지배자
	{ ENEMY_BAHAMUT,           3,            { 5,            4,            9,            8             } },	//용왕
	{ ENEMY_DEATH,             3,            { 1,            5,            9,            FOEGEAR_NONE  } },	//죽음 그 자체
	{ ENEMY_CASTLE_BOSS1,      1,            { 0,            4,            5,            7             } },	//성주 1
	{ ENEMY_CASTLE_BOSS2,      2,            { 2,            4,            5,            7             } },	//성주 2
	{ ENEMY_CASTLE_BOSS3,      3,            { 1,            4,            5,            7             } },	//성주 3
	{ ENEMY_CASTLE_BOSS4,      3,            { 3,            4,            5,            9             } },	//마지막 성주
	{ ENEMY_LABETH,            3,            { 3,            5,            9,            FOEGEAR_NONE  } },	//이름난 적
	{ ENEMY_ELKEIN,            3,            { 3,            5,            4,            9             } },	//이름난 적
	{ ENEMY_BULLET_NOSHADOW,   FOEGEAR_NONE, { FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE  } },	//총알. 장비 없음
	{ ENEMY_BULLET_SKEL,       FOEGEAR_NONE, { FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE, FOEGEAR_NONE  } },	//총알. 장비 없음
};

enum { FOEGEARROWCNT = (int)(sizeof(foeGearRow) / sizeof(foeGearRow[0])) };
