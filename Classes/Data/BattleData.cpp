//이 파일은 BattleData.h 에 있던 배열 정의를 옮겨 담은 것이다.
//
//헤더에 const로 정의하면 내부 링크라 포함하는 .cpp마다 복제되고,
//무엇보다 런타임에 채울 수가 없다. 정의는 여기 한 곳에만 둔다.
//
//자기 헤더만 가져온다. Data.h를 통째로 끌면 UIData.h의 std::string
//때문에 cocos2d.h가 필요해지고, 그러면 팩 생성기가 이 파일만 따로
//컴파일할 수 없다.
//
//tools/content/datafiles.py 가 갈랐다.

#include "BattleData.h"
#include "../Def.h"
#include "../Cmf.h"

static const int battleMotion_builtin[] = {
    PO_C0_A0,//1
    PO_C0_A0,//2
    PO_C0_A0,//3
    PO_C0_A1,//4
    PO_C0_A1,//5
    PO_C0_A1,//6
    PO_C0_A2,//7
    PO_C0_A2,//8
    PO_C0_A2,//9
    PO_C0_A3,//10
    PO_C0_A3,//11
    PO_C0_A3,//12
    PO_C0_A4,//13
    PO_C0_A4,//14
    PO_C0_A4,//15
    PO_C0_A5,//16
    PO_C0_A5,//17
    PO_C0_A5,//18
    PO_C0_A6,//19
    PO_C0_A6,//20
    PO_C0_A6,//21
    PO_C0_A7,//22
    PO_C0_A7,//23
    PO_C0_A7,//24
    PO_C0_A8,//25
    PO_C0_A8,//26
    PO_C0_A8,//27
    PO_C0_A9,//28
    PO_C0_A9,//29
    PO_C0_A9,//30
    PO_C0_A10,//31
    PO_C0_A10,//32
    PO_C0_A10,//33
    PO_C0_A11,//34
    PO_C0_A11,//35
    PO_C0_A11,//36
    PO_C0_A12,//37
    PO_C0_A12,//38
    PO_C0_A12,//39
    PO_C0_A12,//40
    PO_C0_A12,//41
    PO_C0_A12,//42
    PO_C0_A12,//43
    PO_C0_A12,//44
    PO_C0_A12,//45
    PO_C0_A12,//46
    PO_C0_A12,//47
    PO_C0_A12,//48
    PO_C0_A12,//49
    PO_C0_A12,//50
    PO_C0_A12,//51
    PO_C0_A12,//52
    PO_C0_A12,//53
    PO_C0_A12,//54
    PO_C0_A12,//55
    PO_C0_A12,//56
    PO_C0_A12,//57
    PO_C0_A12,//58
    PO_C0_A12,//59
    PO_C0_A12,//60
    PO_C0_A12,//61
    PO_C0_A12,//62
    PO_C0_A12,//63
    PO_C0_A12,//64
    PO_C0_A12,//65
    PO_C0_A12,//66
    PO_C0_A13,//67
    PO_C0_A13,//68
    PO_C0_A13,//69
    PO_C0_A13,//70
    PO_C0_A13,//71
    PO_C0_A13,//72
    PO_C0_A14,//73
    PO_C0_A14,//74
    PO_C0_A14,//75
    PO_C0_A14,//76
    PO_C0_A14,//77
    PO_C0_A14,//78
    PO_C0_STOP0,//79
    PO_C0_STOP0,//80
    PO_C0_STOP0,//81
    PO_C0_STOP1,//82
    PO_C0_STOP1,//83
    PO_C0_STOP1,//84
    PO_C0_STOP2,//85
    PO_C0_STOP2,//86
    PO_C0_STOP2,//87
    PO_C0_STOP3,//88
    PO_C0_STOP3,//89
    PO_C0_STOP3,//90
};
static const int houseGoldStage_builtin[] = {
    0,//1
    10,//2
    20,//3
    30,//4
    50,//5
    70,//6
    100,//7
    120,//8
    150,//9
    200,//10
    250,//11
    300,//12
};
static const long long houseGold_builtin[] = {
    100000,//1
    300000,//2
    1000000,//3
    3000000,//4
    10000000,//5
    30000000,//6
    100000000,//7
    300000000,//8
    1000000000,//9
    3000000000,///10
    10000000000,//11
    30000000000,//12
};
static const int wheelCrewPos_builtin[] = {
    160 * _2X - 256 * _2X - TSIZE, 420 * _2X + TSIZE - 352 * _2X,//1
    192 * _2X - TSIZE * 4 - 256 * _2X, 308 * _2X + TSIZE - 352 * _2X,//2
    320 * _2X + TSIZE * 4 - 256 * _2X, 308 * _2X + TSIZE - 352 * _2X,//3
    352 * _2X - 256 * _2X + TSIZE, 420 * _2X + TSIZE - 352 * _2X,//4
    256 * _2X - 256 * _2X, 500 * _2X - 352 * _2X,//5
};
static const unsigned short gameEventOpenStage_builtin[] = {
    0 * TOTALROOM + 0,//EVENTTYPE_NONE = 0,//이벤트가 없는것으로 이걸 보고 리스트를 띄울지 알려준다.
#ifdef GAMEDEBUG
    0 * TOTALROOM + 0,//EVENTTYPE_PVP,//족보중에 전투를 하면 발생하는 
    0 * TOTALROOM + 0,//EVENTTYPE_QUEST,//퀘스트 아이템 이벤트 
    0 * TOTALROOM + 0,//EVENTTYPE_SHOP,//상점을 
    0 * TOTALROOM + 0,//EVENTTYPE_DEBTDISCOUNT,//업그레이드 가격을 할인해 주는 이벤트
    0 * TOTALROOM + 0,//EVENTTYPE_DOUBLE,//획득량을 두배로 올려주는 이벤트
    0 * TOTALROOM + 0,//EVENTTYPE_BOSSRAID,//보스골드전투
    0 * TOTALROOM + 0,//EVENTTYPE_TOUCHGAME,//중간에 터치를 해서 아이템을 획득하는 이벤트
    0,//EVENTTYPE_DEBUG_NEWGAME,//초기값
    0,//EVENTTYPE_DEBUG_MAXGAME,//최대값
    0,//EVENTTYPE_DEBUG_ENEMYATTACK,//적에게 공격하게 만드는 것
    0,//EVENTTYPE_DEBUG_NFT,//NFT

#else
    0 * TOTALROOM + 5,//EVENTTYPE_PVP,//족보중에 전투를 하면 발생하는 
    0 * TOTALROOM + 0,//EVENTTYPE_QUEST,//퀘스트 아이템 이벤트 
    0 * TOTALROOM + 0,//EVENTTYPE_SHOP,//상점을 
    5 * TOTALROOM + 0,//EVENTTYPE_DEBTDISCOUNT,//업그레이드 가격을 할인해 주는 이벤트
    6 * TOTALROOM + 0,//EVENTTYPE_DOUBLE,//획득량을 두배로 올려주는 이벤트
    20 * TOTALROOM + 0,//EVENTTYPE_BOSSRAID,//보스골드전투
    7 * TOTALROOM + 0,//EVENTTYPE_TOUCHGAME,//중간에 터치를 해서 아이템을 획득하는 이벤트
    0,//EVENTTYPE_DEBUG_NEWGAME,//초기값
    0,//EVENTTYPE_DEBUG_MAXGAME,//최대값
    0,//EVENTTYPE_DEBUG_ENEMYATTACK,//적에게 공격하게 만드는 것
    0,//EVENTTYPE_DEBUG_NFT,//NFT

#endif
};


static const int rouletteProb_builtin[] = {
    PROB_COIN,// = 700,
    PROB_COIN + PROB_COINBAG,// = 600,
    PROB_COIN + PROB_COINBAG + PROB_HEART,// = 100,
    PROB_COIN + PROB_COINBAG + PROB_HEART + PROB_SKILL,// = 200,
    PROB_COIN + PROB_COINBAG + PROB_HEART + PROB_SKILL + PROB_QUEST,// = 500,
    PROB_COIN + PROB_COINBAG + PROB_HEART + PROB_SKILL + PROB_QUEST + PROB_HIT,// = 400,
    PROB_COIN + PROB_COINBAG + PROB_HEART + PROB_SKILL + PROB_QUEST + PROB_HIT + PROB_RAID,// = 300,
};
static const int activeSkillProb_builtin[][2 * MAXCHARSKILL] = {
    //로빈
    {
        70, SKILL_ROBIN8,//ROBIN_SKILL_BOOSTSLASH,//1
        60, SKILL_ROBIN6,//ROBIN_SKILL_AIRCRASH,//2
        50, SKILL_ROBIN9,//ROBIN_SKILL_HYPERCHARGE,//3
        40, SKILL_ROBIN10,//ROBIN_SKILL_SOULCRASH,//4
        30, SKILL_ROBIN7,//ROBIN_SKILL_STAB,//5
        20, SKILL_ROBIN11,//ROBIN_SKILL_ABSOLUTEPIERCE,//6
        10, SKILL_ROBIN12,//ROBIN_SKILL_KILLALL,//7
    },
    //디아나
    {
        70, SKILL_DIANA6,//DIANA_SKILL_3WAY,//1
        60, SKILL_DIANA7,//DIANA_SKILL_LASER,//2
        50, SKILL_DIANA8,//DIANA_SKILL_FLAMER,//3
        40, SKILL_DIANA9,//DIANA_SKILL_BOMBSHOT,//4
        30, SKILL_DIANA10,//DIANA_SKILL_GUIDEDSHOT,//5
        20, SKILL_DIANA11,//DIANA_SKILL_SPRAYSHOT,//6
        10, SKILL_DIANA12,//DIANA_SKILL_SATELLITESHOT,//7
    },
    //맥스
    {
        70, SKILL_MAXX7,//MAXX_SKILL_KICK//1
        60, SKILL_MAXX8,//MAXX_SKILL_SHORT//2
        50, SKILL_MAXX9,//MAXX_SKILL_AIR//3
        40, SKILL_MAXX10,//MAXX_SKILL_CAMPING//4
        30, SKILL_MAXX11,//MAXX_SKILL_HORMING//5
        20, SKILL_MAXX12,//MAXX_SKILL_CIRCLE//6
        10, SKILL_MAXX13,//MAXX_SKILL_MEGA//7
    }
};

static const float popUpFrameData_builtin[] = {
    0.0f,
    0.1f,
    0.3f,
    0.5f,
    0.7f,
    0.9f,
    1.05f,
    1.0f,
};
static const short hitAlpha_builtin[] = {
    ALPHA_MISS,
    ALPHA_GOOD,
    ALPHA_GREAT,
};
static const short raidAlpha_builtin[] = {
    ALPHA_GOOD,
    ALPHA_GREAT,
    ALPHA_PERFECT,
};
static const int battleData_builtin[] = {
    //chapter1
    30, 30, 30,
};
static const int skillInitData_builtin[] = {
    SKILL_ROBIN8, ROBIN_SKILL_BOOSTSLASH, ITEM_STATUE_WIND,
    SKILL_ROBIN9, ROBIN_SKILL_HYPERCHARGE, ITEM_STATUE_DIMENSION,
    SKILL_ROBIN10, ROBIN_SKILL_SOULCRASH, ITEM_STATUE_SUN,
    SKILL_ROBIN7, ROBIN_SKILL_STAB, ITEM_STATUE_FLAME,
    SKILL_ROBIN11, ROBIN_SKILL_ABSOLUTEPIERCE, ITEM_STATUE_THUNDER,
    SKILL_ROBIN12, ROBIN_SKILL_KILLALL, ITEM_STATUE_DRAGON,
};
static const unsigned short arenaOff_builtin[] = {
    //BMP : C:\SKTWIPI\Projects\Mos5\Resource\c.bmp
    223 * _2X, 173 * _2X, 23 * _2X, 24 * _2X,	//0
    72 * _2X, 184 * _2X, 18 * _2X, 15 * _2X,	//1
    0 * _2X, 194 * _2X, 41 * _2X, 19 * _2X,	//2
    90 * _2X, 183 * _2X, 18 * _2X, 16 * _2X,	//3
    121 * _2X, 150 * _2X, 23 * _2X, 22 * _2X,	//4
    126 * _2X, 84 * _2X, 32 * _2X, 6 * _2X,	//5
    62 * _2X, 84 * _2X, 13 * _2X, 5 * _2X,	//6
    216 * _2X, 220 * _2X, 13 * _2X, 6 * _2X,	//7
    126 * _2X, 89 * _2X, 32 * _2X, 1 * _2X,	//8
    34 * _2X, 224 * _2X, 32 * _2X, 6 * _2X,	//9

    //BMP : C:\Users\main\Desktop\Resources\Mos5\Resource\cc.bmp
    76 * _2X, 62 * _2X, 20 * _2X, 20 * _2X,	//10

    //BMP : C:\Users\main\Desktop\Resources\Mos5\Resource\ef.bmp
    0 * _2X, 0 * _2X, 40 * _2X, 46 * _2X,	//11

    //BMP : C:\Users\main\Desktop\Resources\Mos5\Resource\etc.bmp
    0 * _2X, 28 * _2X, 9 * _2X, 15 * _2X,	//12
    9 * _2X, 28 * _2X, 9 * _2X, 15 * _2X,	//13
    18 * _2X, 28 * _2X, 9 * _2X, 15 * _2X,	//14
    27 * _2X, 28 * _2X, 13 * _2X, 10 * _2X,	//15
    40 * _2X, 28 * _2X, 13 * _2X, 10 * _2X,	//16
    53 * _2X, 28 * _2X, 13 * _2X, 10 * _2X,	//17
};
static const signed short arenaMI_builtin[] = {
    //ARENA_START
    IMG_ARENA_0, -37 * _2X, -13 * _2X, N00T0X1,	//0
    IMG_ARENA_1, -14 * _2X, -13 * _2X, N00T0X1,	//1
    IMG_ARENA_2, -14 * _2X, -7 * _2X, N00T0X1,	//2
    IMG_ARENA_1, 27 * _2X, -12 * _2X, N00T0X1,	//3
    IMG_ARENA_1, 0 * _2X, -12 * _2X, N00T0X1,	//4

    //ARENA_STOP
    IMG_ARENA_0, -28 * _2X, -13 * _2X, N00T0X1,	//5
    IMG_ARENA_1, -6 * _2X, -13 * _2X, N00T0X1,	//6
    IMG_ARENA_4, -4 * _2X, -10 * _2X, N00T0X1,	//7
    IMG_ARENA_3, 19 * _2X, -12 * _2X, N00T0X1,	//8

    //ARENA_FRAME0
    IMG_ARENA_6, -13 * _2X, -5 * _2X, N00E3X1,	//9
    IMG_ARENA_6, 0 * _2X, -5 * _2X, F00E3X1,	//10
    IMG_ARENA_6, 0 * _2X, 0 * _2X, N18E3X1,	//11
    IMG_ARENA_6, -13 * _2X, 0 * _2X, F18E3X1,	//12

    //ARENA_FRAME1
    IMG_ARENA_6, -45 * _2X, -11 * _2X, N00E2X1,	//13
    IMG_ARENA_6, 32 * _2X, -11 * _2X, F00E2X1,	//14
    IMG_ARENA_6, 32 * _2X, 6 * _2X, N18E2X1,	//15
    IMG_ARENA_6, -45 * _2X, 6 * _2X, F18E2X1,	//16
    IMG_ARENA_5, -32 * _2X, -12 * _2X, N00E2X1,	//17
    IMG_ARENA_5, 0 * _2X, -12 * _2X, N00E2X1,	//18
    IMG_ARENA_5, -32 * _2X, 6 * _2X, N18E2X1,	//19
    IMG_ARENA_5, 0 * _2X, 6 * _2X, N18E2X1,	//20

    //ARENA_FRAME2
    IMG_ARENA_6, -109 * _2X, -16 * _2X, N00E1X1,	//21
    IMG_ARENA_6, 96 * _2X, -16 * _2X, F00E1X1,	//22
    IMG_ARENA_6, 96 * _2X, 11 * _2X, N18E1X1,	//23
    IMG_ARENA_6, -109 * _2X, 11 * _2X, F18E1X1,	//24
    IMG_ARENA_5, -32 * _2X, -17 * _2X, N00E1X1,	//25
    IMG_ARENA_5, 0 * _2X, -17 * _2X, N00E1X1,	//26
    IMG_ARENA_5, -96 * _2X, 11 * _2X, N18E1X1,	//27
    IMG_ARENA_5, 0 * _2X, 11 * _2X, N18E1X1,	//28
    IMG_ARENA_5, -64 * _2X, -17 * _2X, N00E1X1,	//29
    IMG_ARENA_5, -96 * _2X, -17 * _2X, N00E1X1,	//30
    IMG_ARENA_5, 32 * _2X, -17 * _2X, N00E1X1,	//31
    IMG_ARENA_5, 64 * _2X, -17 * _2X, N00E1X1,	//32
    IMG_ARENA_5, -64 * _2X, 11 * _2X, N18E1X1,	//33
    IMG_ARENA_5, -32 * _2X, 11 * _2X, N18E1X1,	//34
    IMG_ARENA_5, 32 * _2X, 11 * _2X, N18E1X1,	//35
    IMG_ARENA_5, 64 * _2X, 11 * _2X, N18E1X1,	//36

    //ARENA_FRAME3
    IMG_ARENA_5, -16 * _2X, -20 * _2X, N00E1X1,	//37
    IMG_ARENA_5, -16 * _2X, 14 * _2X, N18E1X1,	//38

    //REPORT_FRAME0
    IMG_ARENA_8, 0 * _2X, -21 * _2X, N00T1X1,	//39

    //REPORT_FRAME1
    IMG_ARENA_5, 0 * _2X, -26 * _2X, N00E0X1,	//40
    IMG_ARENA_5, 0 * _2X, -20 * _2X, F18E0X1,	//41

    //REPORT_FRAME2
    IMG_ARENA_5, 0 * _2X, -29 * _2X, N00E0X1,	//42
    IMG_ARENA_9, 0 * _2X, -23 * _2X, N00T0X1,	//43
    IMG_ARENA_5, 0 * _2X, -17 * _2X, N18E0X1,	//44

    //REPORT_FRAME2_EDGE
    IMG_ARENA_6, -13 * _2X, -28 * _2X, N00E0X1,	//45
    IMG_ARENA_7, -13 * _2X, -23 * _2X, N00E0X1,	//46
    IMG_ARENA_6, -13 * _2X, -17 * _2X, F18E0X1,	//47

    //REPORT_FRAME3
    IMG_ARENA_5, 0 * _2X, -35 * _2X, N00E0X1,	//48
    IMG_ARENA_9, 0 * _2X, -29 * _2X, N00T0X1,	//49
    IMG_ARENA_9, 0 * _2X, -23 * _2X, N00T0X1,	//50
    IMG_ARENA_9, 0 * _2X, -17 * _2X, N00T0X1,	//51
    IMG_ARENA_5, 0 * _2X, -11 * _2X, N18E0X1,	//52

    //REPORT_FRAME3_EDGE
    IMG_ARENA_6, -13 * _2X, -34 * _2X, N00E0X1,	//53
    IMG_ARENA_7, -13 * _2X, -29 * _2X, N00E0X1,	//54
    IMG_ARENA_7, -13 * _2X, -23 * _2X, N00E0X1,	//55
    IMG_ARENA_7, -13 * _2X, -17 * _2X, N00E0X1,	//56
    IMG_ARENA_6, -13 * _2X, -11 * _2X, F18E0X1,	//57

    //REPORT_FRAME4
    IMG_ARENA_5, 0 * _2X, -41 * _2X, N00E0X1,	//58
    IMG_ARENA_9, 0 * _2X, -35 * _2X, N00T0X1,	//59
    IMG_ARENA_9, 0 * _2X, -29 * _2X, N00T0X1,	//60
    IMG_ARENA_9, 0 * _2X, -23 * _2X, N00T0X1,	//61
    IMG_ARENA_9, 0 * _2X, -17 * _2X, N00T0X1,	//62
    IMG_ARENA_5, 0 * _2X, -6 * _2X, F18E0X1,	//63
    IMG_ARENA_9, 0 * _2X, -11 * _2X, N00T0X1,	//64

    //REPORT_FRAME4_EDGE
    IMG_ARENA_6, -13 * _2X, -40 * _2X, N00E0X1,	//65
    IMG_ARENA_7, -13 * _2X, -35 * _2X, N00E0X1,	//66
    IMG_ARENA_7, -13 * _2X, -29 * _2X, N00E0X1,	//67
    IMG_ARENA_7, -13 * _2X, -23 * _2X, N00E0X1,	//68
    IMG_ARENA_7, -13 * _2X, -17 * _2X, N00E0X1,	//69
    IMG_ARENA_7, -13 * _2X, -12 * _2X, N00E0X1,	//70
    IMG_ARENA_6, -13 * _2X, -6 * _2X, F18E0X1,	//71

    //ARENA_CROWN_FRAME0
    IMG_ARENA_10, 120 * _2X, 195 * _2X - 36 * _2X, N00E0X4,	//72

    //ARENA_CROWN_FRAME1
    IMG_ARENA_10, 130 * _2X, 167 * _2X - 36 * _2X, N00E0X3,	//73

    //ARENA_CROWN_FRAME2
    IMG_ARENA_10, 140 * _2X, 133 * _2X - 36 * _2X, N00E0X2,	//74

    //ARENA_CROWN_FRAME3
    IMG_ARENA_10, 140 * _2X, 105 * _2X - 36 * _2X, N00E0X2,	//75

    //ARENA_CROWN_FRAME4
    IMG_ARENA_10, 140 * _2X, 85 * _2X - 36 * _2X, N00E0X2,	//76
    IMG_ARENA_11, 140 * _2X, 80 * _2X - 36 * _2X, N00E0X1,	//77

    //ARENA_CROWN_FRAME5
    IMG_ARENA_10, 140 * _2X, 86 * _2X - 36 * _2X, N00E1X2,	//78
    IMG_ARENA_11, 140 * _2X, 78 * _2X - 36 * _2X, N00E1X1,	//79

    //ARENA_CROWN_FRAME6
    IMG_ARENA_15, 147 * _2X, 96 * _2X - 36 * _2X, N00T0X2,	//80
    IMG_ARENA_10, 140 * _2X, 87 * _2X - 36 * _2X, N00E1X2,	//81
    IMG_ARENA_16, 36 * _2X, 189 * _2X - 36 * _2X, N00T0X4,	//82
    IMG_ARENA_17, 235 * _2X, 245 * _2X - 36 * _2X, N00T0X4,	//83

    //ARENA_CROWN_FRAME7
    IMG_ARENA_15, 147 * _2X, 96 * _2X - 36 * _2X, N00T0X2,	//84
    IMG_ARENA_16, 58 * _2X, 156 * _2X - 36 * _2X, N00T0X3,	//85
    IMG_ARENA_17, 216 * _2X, 202 * _2X - 36 * _2X, N00T0X3,	//86

    //ARENA_CROWN_FRAME8
    IMG_ARENA_15, 147 * _2X, 96 * _2X - 36 * _2X, N00T0X2,	//87
    IMG_ARENA_16, 114 * _2X, 114 * _2X - 36 * _2X, N00T0X2,	//88
    IMG_ARENA_17, 182 * _2X, 132 * _2X - 36 * _2X, N00T0X2,	//89
};
static const unsigned char arenaMIC_builtin[] = {
    0, 5,	//0
    5, 4,	//1
    9, 4,	//2
    13, 8,	//3
    21, 16,	//4
    37, 2,	//5
    39, 1,	//6
    40, 2,	//7
    42, 3,	//8
    45, 3,	//9
    48, 5,	//10
    53, 5,	//11
    58, 7,	//12
    65, 7,	//13
    72, 1,	//14
    73, 1,	//15
    74, 1,	//16
    75, 1,	//17
    76, 2,	//18
    78, 2,	//19
    80, 4,	//20
    84, 3,	//21
    87, 3,	//22
};

//게임이 읽는 포인터. 처음에는 내장 기본값을 가리키고, 부팅 때
//팩을 읽으면 그쪽으로 옮겨간다. const는 가리키는 대상에 붙으므로
//게임 코드는 대상을 못 건드리고, 로더만 자기 버퍼를 채워 넘긴다.

const int* battleMotion = battleMotion_builtin;
const int* houseGoldStage = houseGoldStage_builtin;
const long long* houseGold = houseGold_builtin;
const int* wheelCrewPos = wheelCrewPos_builtin;
const int* rouletteProb = rouletteProb_builtin;
const float* popUpFrameData = popUpFrameData_builtin;
const short* hitAlpha = hitAlpha_builtin;
const short* raidAlpha = raidAlpha_builtin;
const int* battleData = battleData_builtin;
const int* skillInitData = skillInitData_builtin;
const unsigned short* arenaOff = arenaOff_builtin;
const signed short* arenaMI = arenaMI_builtin;
const unsigned char* arenaMIC = arenaMIC_builtin;

//게임이 읽는 포인터. 처음에는 내장 기본값을 가리키고, 부팅 때
//팩을 읽으면 그쪽으로 옮겨간다. const는 가리키는 대상에 붙으므로
//게임 코드는 대상을 못 건드리고, 로더만 자기 버퍼를 채워 넘긴다.

const int (*activeSkillProb)[2 * MAXCHARSKILL] = activeSkillProb_builtin;

//게임이 읽는 포인터. 처음에는 내장 기본값을 가리키고, 부팅 때
//팩을 읽으면 그쪽으로 옮겨간다. const는 가리키는 대상에 붙으므로
//게임 코드는 대상을 못 건드리고, 로더만 자기 버퍼를 채워 넘긴다.

const unsigned short* gameEventOpenStage = gameEventOpenStage_builtin;
