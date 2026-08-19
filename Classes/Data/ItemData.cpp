//이 파일은 ItemData.h 에 있던 배열 정의를 옮겨 담은 것이다.
//
//헤더에 const로 정의하면 내부 링크라 포함하는 .cpp마다 복제되고,
//무엇보다 런타임에 채울 수가 없다. 정의는 여기 한 곳에만 둔다.
//
//자기 헤더만 가져온다. Data.h를 통째로 끌면 UIData.h의 std::string
//때문에 cocos2d.h가 필요해지고, 그러면 팩 생성기가 이 파일만 따로
//컴파일할 수 없다.
//
//tools/content/datafiles.py 가 갈랐다.

#include "ItemData.h"
#include "../Def.h"
#include "../Cmf.h"

static const unsigned short itemTypeCnt_builtin[] = {
    TOTAL_SWORD,        //robin
    TOTAL_GUN,
    TOTAL_BOOMERANG,
    TOTAL_HELM,         //robin
    TOTAL_HAT,
    TOTAL_CAP,
    TOTAL_ARMOR,        //robin
    TOTAL_VEST,
    TOTAL_COAT,
    TOTAL_GUNTLET,      //robin
    TOTAL_ARMLET,
    TOTAL_GLOVE,
    TOTAL_KILT,         //robin
    TOTAL_SKIRT,
    TOTAL_PANTS,
    TOTAL_GREAVES,      //robin
    TOTAL_SHOES,
    TOTAL_BOOTS,
    TOTAL_NECK,         //robin
    TOTAL_RING,         //robin
    TOTAL_GEM,          //robin
    TOTAL_WASTE,
    TOTAL_IRON,
    TOTAL_LEATHER,
    TOTAL_CLOTH,
    TOTAL_WOOD,
    TOTAL_ESSENCE,
    TOTAL_QUESTITEM,
    TOTAL_NETITEM,
    TOTAL_KEYITEM,
    TOTAL_STATUE,
    TOTAL_BOX,
    TOTAL_CREW,
    TOTAL_SKILL,
};
static const int swordInfoList_builtin[] = {
    ROULETTE_COIN,
    ROULETTE_EQUIP,
    ROULETTE_QUEST,
    ROULETTE_SKILL,
};
static const signed short newCardEffect_builtin[] = {
    HIT_DIANA_SMALL1, 12 * _2X, 23 * _2X,
    HIT_DIANA_SMALL2, 12 * _2X, 23 * _2X,
    HIT_DIANA_SMALL3, 12 * _2X, 23 * _2X,
    HIT_DIANA_SMALL4, 12 * _2X, 23 * _2X,
    HIT_DIANA_SMALL5, 12 * _2X, 23 * _2X,
    HIT_DIANA_SMALL6, 12 * _2X, 23 * _2X,
    HIT_DIANA_SMALL7, 12 * _2X, 23 * _2X,

    HIT_DIANA_SMALL1, 34 * _2X, 48 * _2X,
    HIT_DIANA_SMALL2, 34 * _2X, 48 * _2X,
    HIT_DIANA_SMALL3, 34 * _2X, 48 * _2X,
    HIT_DIANA_SMALL4, 34 * _2X, 48 * _2X,
    HIT_DIANA_SMALL5, 34 * _2X, 48 * _2X,
    HIT_DIANA_SMALL6, 34 * _2X, 48 * _2X,
    HIT_DIANA_SMALL7, 34 * _2X, 48 * _2X,

    HIT_DIANA_SMALL1, 34 * _2X, 23 * _2X,
    HIT_DIANA_SMALL2, 34 * _2X, 23 * _2X,
    HIT_DIANA_SMALL3, 34 * _2X, 23 * _2X,
    HIT_DIANA_SMALL4, 34 * _2X, 23 * _2X,
    HIT_DIANA_SMALL5, 34 * _2X, 23 * _2X,
    HIT_DIANA_SMALL6, 34 * _2X, 23 * _2X,
    HIT_DIANA_SMALL7, 34 * _2X, 23 * _2X,

    HIT_DIANA_SMALL1, 12 * _2X, 48 * _2X,
    HIT_DIANA_SMALL2, 12 * _2X, 48 * _2X,
    HIT_DIANA_SMALL3, 12 * _2X, 48 * _2X,
    HIT_DIANA_SMALL4, 12 * _2X, 48 * _2X,
    HIT_DIANA_SMALL5, 12 * _2X, 48 * _2X,
    HIT_DIANA_SMALL6, 12 * _2X, 48 * _2X,
    HIT_DIANA_SMALL7, 12 * _2X, 48 * _2X,
};
static const int equipDataType_builtin[] = {
    DATATYPE_ABSOLUTE,  //EQUIP_WEAPON = 0
    DATATYPE_PERCENT,   //EQUIP_HELM
    DATATYPE_PERCENT,   //EQUIP_ARMOR
    DATATYPE_PERCENT,   //EQUIP_PANTS
    DATATYPE_PERCENT,   //EQUIP_GLOVE
    DATATYPE_PERCENT,   //EQUIP_BOOTS
};
static const unsigned short openedItemData_builtin[] = {
    OPENEDITEMCNT,  //ITEM_SWORD = 0
    OPENEDITEMCNT,  //ITEM_GUN
    OPENEDITEMCNT,  //ITEM_BOOMERANG
    OPENEDITEMCNT,  //ITEM_HELM
    OPENEDITEMCNT,  //ITEM_HAT
    OPENEDITEMCNT,  //ITEM_CAP
    OPENEDITEMCNT,  //ITEM_ARMOR
    OPENEDITEMCNT,  //ITEM_VEST
    OPENEDITEMCNT,  //ITEM_COAT
    OPENEDITEMCNT,  //ITEM_GUNTLET
    OPENEDITEMCNT,  //ITEM_ARMLET
    OPENEDITEMCNT,  //ITEM_GLOVE
    OPENEDITEMCNT,  //ITEM_KILT
    OPENEDITEMCNT,  //ITEM_SKIRT
    OPENEDITEMCNT,  //ITEM_PANTS
    OPENEDITEMCNT,  //ITEM_GREAVES
    OPENEDITEMCNT,  //ITEM_SHOES
    OPENEDITEMCNT,  //ITEM_BOOTS
    TOTAL_NECK,     //ITEM_NECK
    TOTAL_RING,     //ITEM_RING
};
static const unsigned char itemLevelLimit_builtin[] = {
	5, 0,//★
	5, 5,//★★
	5, 10,//★★★
	5, 15,//★★★★
	5, 20,//★★★★★
	5, 25,//★★★★★★
	5, 30,//★★★★★★★
	5, 35,//★★★★★★★★
};
static const int itemExpAcce_builtin[] = {
	5,
	10,
	15,
	20,
	25,
	30,
	40,
	50,
	60,
	70,//10

	80,
	95,
	110,
	125,
	140,
	155,
	175,
	195,
	215,
	235,//20

	255,
	280,
	305,
	330,
	355,
	380,
	410,
	440,
	470,
	500,//30

	530,
	565,
	600,
	635,
	670,
	705,
	745,
	785,
	825,
	865,//40

	905,
	950,
	995,
	1040,
	1085,
	1130,
	1180,
	1230,
	1280,
	1330,//50
};
static const int itemExp_builtin[] = {
	//★
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,//10

	//★★
	10,
	12,
	14,
	16,
	18,
	20,
	22,
	24,
	26,
	28,
	30,
	32,
	34,
	36,
	38,//15

	//★★★
	50,
	53,
	56,
	59,
	62,
	65,
	68,
	71,
	74,
	77,
	80,
	83,
	86,
	89,
	92,
	95,
	98,
	101,
	104,
	107,//20

	//★★★★
	200,
	206,
	212,
	218,
	224,
	230,
	236,
	242,
	248,
	254,
	260,
	266,
	272,
	278,
	284,
	290,
	296,
	302,
	308,
	314,
	320,
	326,
	332,
	338,
	344,//25

	//★★★★★
	500,
	510,
	520,
	530,
	540,
	550,
	560,
	570,
	580,
	590,
	600,
	610,
	620,
	630,
	640,
	650,
	660,
	670,
	680,
	690,
	700,
	710,
	720,
	730,
	740,
	750,
	760,
	770,
	780,
	790,//30

	//★★★★★★
	1000,
	1025,
	1050,
	1075,
	1100,
	1125,
	1150,
	1175,
	1200,
	1225,
	1250,
	1275,
	1300,
	1325,
	1350,
	1375,
	1400,
	1425,
	1450,
	1475,
	1500,
	1525,
	1550,
	1575,
	1600,
	1625,
	1650,
	1675,
	1700,
	1725,
	1750,
	1775,
	1800,
	1825,
	1850,//35

	//★★★★★★★
	2000,
	2050,
	2100,
	2150,
	2200,
	2250,
	2300,
	2350,
	2400,
	2450,
	2500,
	2550,
	2600,
	2650,
	2700,
	2750,
	2800,
	2850,
	2900,
	2950,
	3000,
	3050,
	3100,
	3150,
	3200,
	3250,
	3300,
	3350,
	3400,
	3450,
	3500,
	3550,
	3600,
	3650,
	3700,
	3750,
	3800,
	3850,
	3900,//40

	//★★★★★★★★
	5000,
	5100,
	5200,
	5300,
	5400,
	5500,
	5600,
	5700,
	5800,
	5900,
	6000,
	6100,
	6200,
	6300,
	6400,
	6500,
	6600,
	6700,
	6800,
	6900,
	7000,
	7100,
	7200,
	7300,
	7400,
	7500,
	7600,
	7700,
	7800,
	7900,
	8000,
	8100,
	8200,
	8300,
	8400,
	8500,
	8600,
	8700,
	8800,
	8900,
	9000,
	9100,
	9200,
	9300,
	9400,
	9500,
	9600,
	9700,
	9800,
	9900,//50
};
static const int itemMaterialExpAcce_builtin[] = {
	10,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,//10

	60,
	65,
	70,
	75,
	80,
	85,
	90,
	95,
	100,
	105,//20

	110,
	115,
	120,
	125,
	130,
	135,
	140,
	145,
	150,
	155,//30

	160,
	165,
	170,
	175,
	180,
	185,
	190,
	195,
	200,
	205,//40

	210,
	215,
	220,
	225,
	230,
	235,
	240,
	245,
	250,
	255,//50
};
static const int itemMaterialExp_builtin[] = {
	//★
	10,
	12,
	14,
	16,
	18,
	20,
	22,
	24,
	26,
	28,//10

	//★★
	50,
	54,
	58,
	62,
	66,
	70,
	74,
	78,
	82,
	86,
	90,
	94,
	98,
	102,
	106,//15

	//★★★
	200,
	210,
	220,
	230,
	240,
	250,
	260,
	270,
	280,
	290,
	300,
	310,
	320,
	330,
	340,
	350,
	360,
	370,
	380,
	390,//20

	//★★★★
	800,
	830,
	860,
	890,
	920,
	950,
	980,
	1010,
	1040,
	1070,
	1100,
	1130,
	1160,
	1190,
	1220,
	1250,
	1280,
	1310,
	1340,
	1370,
	1400,
	1430,
	1460,
	1490,
	1520,//25

	//★★★★★
	2000,
	2060,
	2120,
	2180,
	2240,
	2300,
	2360,
	2420,
	2480,
	2540,
	2600,
	2660,
	2720,
	2780,
	2840,
	2900,
	2960,
	3020,
	3080,
	3140,
	3200,
	3260,
	3320,
	3380,
	3440,
	3500,
	3560,
	3620,
	3680,
	3740,//30

	//★★★★★★
	5000,
	5100,
	5200,
	5300,
	5400,
	5500,
	5600,
	5700,
	5800,
	5900,
	6000,
	6100,
	6200,
	6300,
	6400,
	6500,
	6600,
	6700,
	6800,
	6900,
	7000,
	7100,
	7200,
	7300,
	7400,
	7500,
	7600,
	7700,
	7800,
	7900,
	8000,
	8100,
	8200,
	8300,
	8400,//35

	//★★★★★★★
	10000,
	10200,
	10400,
	10600,
	10800,
	11000,
	11200,
	11400,
	11600,
	11800,
	12000,
	12200,
	12400,
	12600,
	12800,
	13000,
	13200,
	13400,
	13600,
	13800,
	14000,
	14200,
	14400,
	14600,
	14800,
	15000,
	15200,
	15400,
	15600,
	15800,
	16000,
	16200,
	16400,
	16600,
	16800,
	17000,
	17200,
	17400,
	17600,
	17800,//40

	//★★★★★★★★
	20000,
	20500,
	21000,
	21500,
	22000,
	22500,
	23000,
	23500,
	24000,
	24500,
	25000,
	25500,
	26000,
	26500,
	27000,
	27500,
	28000,
	28500,
	29000,
	29500,
	30000,
	30500,
	31000,
	31500,
	32000,
	32500,
	33000,
	33500,
	34000,
	34500,
	35000,
	35500,
	36000,
	36500,
	37000,
	37500,
	38000,
	38500,
	39000,
	39500,
	40000,
	40500,
	41000,
	41500,
	42000,
	42500,
	43000,
	43500,
	44000,
	44500,//50
};
static const long long itemEvolutionItem_builtin[] = {
	//★
1,
2,
3,
4,
5,
6,
7,
9,
10,
12,
12,
12,
14,
14,
19,
20,
20,
20,
21,
21,
21,
22,
22,
22,
23,
23,
24,
25,
27,
29,
31,
32,
36,
38,
40,
42,
45,
47,
51,
55,
55,
58,
60,
64,
68,
72,
76,
84,
91,
93,
94,
97,
101,
107,
115,
116,
123,
128,
137,
144,
151,
161,
168,
174,
181,
189,
197,
210,
220,
232,
242,
258,
283,
300,
307,
313,
320,
333,
350,
367,
400,
433,
467,
473,
483,
493,
500,
533,
567,
600,
633,
667,
700,
733,
750,
767,
800,
867,
900,
933,
967,
1033,
1133,
1167,
1200,
1233,
1267,
1367,
1400,
1533,
1567,
1667,
1767,
1867,
1900,
1933,
2000,
2133,
2233,
2333,
2467,
2600,
2733,
2833,
3000,
3067,
3200,
3400,
3533,
3767,
3933,
4200,
4367,
4500,
4767,
4833,
5033,
5067,
5400,
5933,
6200,
6600,
6900,
7033,
7200,
7333,
7533,
7633,
7800,
7933,
8200,
8267,
8600,
8933,
9400,
9667,
10067,
10167,
10433,
10667,
11200,
11400,
11500,
12000,
12367,
12633,
12933,
13533,
13933,
14600,
15000,
15233,
15533,
16133,
16333,
17100,
17467,
17600,
18667,
19233,
19867,
20467,
21367,
21633,
22333,
22867,
23500,
24300,
25133,
25600,
26367,
27400,
28267,
29100,
29900,
30867,
31800,
32733,
33700,
34733,
35633,
36867,
37933,
39200,
40267,
41467,
42400,
44000,
45300,
46667,
48000,
49600,
51000,
52533,
54000,
55667,
57333,
59000,
60800,
62800,
64700,
66667,
68700,
70800,
72967,
75200,
77500,
79867,
81867,
82300,
87400,
90067,
92833,
95667,
98600,
101600,
104700,
107900,
111200,
114600,
};
static const long long itemUpgradeHammer_builtin[] = {
	//★
1,
2,
3,
5,
10,
20,
};
static const unsigned short arenaFloorGold_builtin[] = {
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	41,
	42,
	43,
	44,
	45,
	46,
	47,
	48,
	49,
	50,
	51,
	52,
	53,
	54,
	55,
	56,
	57,
	58,
	59,
	60,
	61,
	62,
	63,
	64,
	65,
	66,
	67,
	68,
	69,
	70,
	71,
	72,
	73,
	74,
	75,
	76,
	77,
	78,
	79,
	80,
	81,
	82,
	83,
	84,
	85,
	86,
	87,
	88,
	89,
	90,
	91,
	92,
	93,
	94,
	95,
	96,
	97,
	98,
	99,
	100,
	101,
	102,
	103,
	104,
	105,
	106,
	107,
	108,
	109,
	110,
	111,
	112,
	113,
	114,
	115,
	116,
	117,
	118,
	119,
	120,
	121,
	122,
	123,
	124,
	125,
	126,
	127,
	128,
	129,
	130,
	131,
	132,
	133,
	134,
	135,
	136,
	137,
	138,
	139,
	140,
	141,
	142,
	143,
	144,
	145,
	146,
	147,
	148,
	149,
	150,
	151,
	152,
	153,
	154,
	155,
	156,
	157,
	158,
	159,
	160,
	161,
	162,
	163,
	164,
	165,
	166,
	167,
	168,
	169,
	170,
	171,
	172,
	173,
	174,
	175,
	176,
	177,
	178,
	179,
	180,
	181,
	182,
	183,
	184,
	185,
	186,
	187,
	188,
	189,
	190,
	191,
	192,
	193,
	194,
	195,
	196,
	197,
	198,
	199,
	200,
};
static const unsigned short revolutionMedal_builtin[] = {
	10,//★
	50,//★★
	100,//★★★
	300,//★★★★
	1000,//★★★★★
	5000,//★★★★★★
	30000,//★★★★★★★
	65535,//★★★★★★★★
};
static const unsigned int itemColor_builtin[] = {
	0xFFFFFF,	//일반(흰색) 255, 255, 255,
	0x00FF00,	//고급(녹색) 0, 255, 0,
	0xFFFF00,	//희귀(노란색) 255, 255, 0,
	0x3399FF,	//세트(파란색) 51, 153, 255,
	0xCC33FF,	//영웅(보라색) 204, 51, 255,
	0xFF6600,	//전설(주황색)
	0x333333,	//신(블랙)STAR7
	COLOR_BEIGE,	//STAR8
	COLOR_SKY,	//STAR9
	COLOR_STARGREY,	//STAR10
};
static const unsigned int buffBlend_builtin[] = {
	0x000000,	//INC_DAMAGE_RING
	0x000000,	//INC_DEFENSE_RING
	0xFF0000,	//INC_EVASION_RING
	0x00FF00,	//INC_PIERCE_RING
	0x0000FF,	//INC_HIT_RING
	0xFFFF00,	//INC_STUN_RING
	0x00FFFF,	//INC_CRITICAL_RING
	0xFF0000,	//INC_CRITDMG_RING
	0xFFFF00,	//INC_IGNORE_RING
	0x0000FF,	//INC_EXP_RING
	0x00FF00,	//INC_EXTRA_RING
	0x0000FF,	//INC_ABSORB_RING
	0x000000,	//INC_DAMAGE_ARENA
	0x000000,	//INC_DEFENSE_ARENA
	0x000000,	//INC_MAGIC_ARENA
	0x000000,	//INC_SKILL_ARENA
};
static const unsigned char swordMaxBet_builtin[] = {
	5,//연습용 몽둥이
	5,//롱소드
	5,//처형자의 검
	5,//파멸의 참마도
	5,//추적자의 검

	5,//격노의 양날검
	6,//수호자의 검
	6,//왕가의 수호자
	6,//나찰의 검
	6,//소울 크래셔

	6,//플레임소드
	6,//아이스소드
	7,//썬더소드
	7,//어스소드
	7,//레바테인

	7,//스톰브링거
	7,//칼라드볼그
	7,//발뭉
	8,//흐룬팅
	8,//거인의 칼

	8,//미스틸테인
	8,//엑스칼리버
	8,//홀리소드
	8,//다크소드
	8,//레오소드

	8,//사신의 낫
	8,//드래곤 클로우
	8,//황룡의 어금니
	8,//신룡마강검
	8,//드래곤 슬레이어

	8,//얼티밋소드
	8,//차원의 검
	8,//천공의 검
	8,//스타더스트
	8,//패왕의 검

	8,//바리스의 검
	8,//파르메티아소드
	8,//사르바로아소드
	8,//테트라소드
	8,//빅뱅소드
};
static const unsigned char swordHeart_builtin[] = {

	1,//연습용 몽둥이
	1,//롱소드
	1,//처형자의 검
	1,//파멸의 참마도
	1,//추적자의 검

	1,//격노의 양날검
	2,//수호자의 검
	2,//왕가의 수호자
	2,//나찰의 검
	2,//소울 크래셔

	2,//플레임소드
	2,//아이스소드
	3,//썬더소드
	3,//어스소드
	3,//레바테인

	3,//스톰브링거
	3,//칼라드볼그
	3,//발뭉
	5,//흐룬팅
	5,//거인의 칼

	5,//미스틸테인
	5,//엑스칼리버
	10,//홀리소드
	10,//다크소드
	10,//레오소드

	10,//사신의 낫
	10,//드래곤 클로우
	10,//황룡의 어금니
	10,//신룡마강검
	10,//드래곤 슬레이어

	10,//얼티밋소드
	10,//차원의 검
	10,//천공의 검
	10,//스타더스트
	10,//패왕의 검

	10,//바리스의 검
	10,//파르메티아소드
	10,//사르바로아소드
	10,//테트라소드
	10,//빅뱅소드
};
static const long long swordGold_builtin[] = {
	//ITEM_SWORD
	//ITEM_SWORD_STICK
	10000,//GRADE_NORMAL //1
	20000,//GRADE_SUPERIOR //2
	30000,//GRADE_RARE //3
	50000,//GRADE_EPIC //4
	100000,//GRADE_LEGEND //5

	//ITEM_SWORD_LONG
	150000,//GRADE_NORMAL //6
	200000,//GRADE_SUPERIOR //7
	300000,//GRADE_RARE //8
	500000,//GRADE_EPIC //9
	800000,//GRADE_LEGEND //10

	//ITEM_SWORD_CUTTER
	1000000,//GRADE_NORMAL //11
	1200000,//GRADE_SUPERIOR //12
	1500000,//GRADE_RARE //13
	2000000,//GRADE_EPIC //14
	2500000,//GRADE_LEGEND //15

	//ITEM_SWORD_SEEKER
	3000000,//GRADE_NORMAL //16
	4000000,//GRADE_SUPERIOR //17
	5000000,//GRADE_RARE //18
	6000000,//GRADE_EPIC //19
	8000000,//GRADE_LEGEND //20

	//ITEM_SWORD_ELVEN
	10000000,//GRADE_NORMAL //21
	12000000,//GRADE_SUPERIOR //22
	15000000,//GRADE_RARE //23
	20000000,//GRADE_EPIC //24
	25000000,//GRADE_LEGEND //25

	//ITEM_SWORD_GHOST
	30000000,//GRADE_NORMAL //26
	35000000,//GRADE_SUPERIOR //27
	40000000,//GRADE_RARE //28
	45000000,//GRADE_EPIC //29
	50000000,//GRADE_LEGEND //30

	//ITEM_SWORD_DIMENSIONAL
	55000000,//GRADE_NORMAL //31
	60000000,//GRADE_SUPERIOR //32
	65000000,//GRADE_RARE //33
	70000000,//GRADE_EPIC //34
	80000000,//GRADE_LEGEND //35

	//ITEM_SWORD_DRAGONTOOTH
	90000000,//GRADE_NORMAL //36
	100000000,//GRADE_SUPERIOR //37
	110000000,//GRADE_RARE //38
	120000000,//GRADE_EPIC //39
	150000000,//GRADE_LEGEND //40

};
static const unsigned long long itemPrice_builtin[] = {
	//검 : ITEM_SWORD				
1200	,//ITEM_SWORD_STICK = 0,//1//연습용 몽둥이				
2000	,//ITEM_SWORD_LONG,//2//롱소드				
3000	,//ITEM_SWORD_CUTTER,//3//처형자의 검				
4500	,//ITEM_SWORD_RUIN,//4//파멸의 참마도				
6000	,//ITEM_SWORD_SEEKER,//5//추적자의 검				
8000	,//ITEM_SWORD_DOUBLE,//6//격노의 양날검				
12000	,//ITEM_SWORD_ELVEN,//7//수호자의 검				
15000	,//ITEM_SWORD_ROYAL,//8//왕가의 수호자				
18000	,//ITEM_SWORD_GHOST,//9//나찰의 검				
22000	,//ITEM_SWORD_GHOST2,//10//소울 크래셔				
26000	,//ITEM_SWORD_FRAME,//11//플레임소드				
30000	,//ITEM_SWORD_ICE,//12//아이스소드				
35000	,//ITEM_SWORD_THUNDER,//13//썬더소드				
40000	,//ITEM_SWORD_EARTH,//14//어스소드				
45000	,//ITEM_SWORD_LAEVATEINN,//15//레바테인				
50000	,//ITEM_SWORD_STORMBRINGER,//16//스톰브링거				
56000	,//ITEM_SWORD_CALADBOLG,//17//칼라드볼그				
62000	,//ITEM_SWORD_BALMUNG,//18//발뭉				
68000	,//ITEM_SWORD_HRUNTING,//19//흐룬팅				
75000	,//ITEM_SWORD_GIANT,//20//거인의 칼				
82000	,//ITEM_SWORD_MISTILTEINN,//21//미스틸테인				
90000	,//ITEM_SWORD_EXCALIBUR,//22//엑스칼리버				
100000	,//ITEM_SWORD_HOLY,//23//홀리소드				
110000	,//ITEM_SWORD_DARK,//24//다크소드				
120000	,//ITEM_SWORD_LEO,//25//레오소드				
130000	,//ITEM_SWORD_DEATH,//26//사신의 낫				
140000	,//ITEM_SWORD_DRAGONCLOW,//27//드래곤 클로우				
150000	,//ITEM_SWORD_DRAGONTOOTH,//28//황룡의 어금니				
170000	,//ITEM_SWORD_DRAGONGOD,//29//신룡마강검				
190000	,//ITEM_SWORD_DRAGONSLAYER,//30//드래곤 슬레이어				
210000	,//ITEM_SWORD_ULTIMATE,//31//얼티밋소드				
230000	,//ITEM_SWORD_DIMENSIONAL,//32//차원의 검				
250000	,//ITEM_SWORD_HEAVEN,//33//천공의 검				
280000	,//ITEM_SWORD_STARDUST,//34//스타더스트				
310000	,//ITEM_SWORD_KING,//35//패왕의 검				
//TOTAL_SWORD,				

//총 : ITEM_GUN				
1000	,//ITEM_GUN_PISTOL = 0,//발화식 총				
1800	,//ITEM_GUN_REVOLVER,//리볼버 파이슨				
2700	,//ITEM_GUN_MAGNUM,//45구경 오토건 : 사일런트 킬러				
4000	,//ITEM_GUN_AUTOGUN45MM,//고져스 건 : 럭셔리 캐논				
5500	,//ITEM_GUN_JEWELGUN,//회천마도총 : 마도머신건				
7200	,//ITEM_GUN_EXPLOSION,//태양의 총 : 슈퍼노바				
9000	,//ITEM_GUN_CROSSFIRE,//헬파이어 건 : 인페르노 캐논 : 마룡열화포				
10800	,//ITEM_GUN_INFERNO,//크로스 파이어 : 테스타먼트 : 라그나로크				
//TOTAL_GUN,				

//부메랑 : ITEM_BOOMERANG				
1500	,//ITEM_BOOMERANG_BOOMERANG = 0,//사냥용 부메랑				
2300	,//ITEM_BOOMERANG_VOYAGER,//슬라이서				
3200	,//ITEM_BOOMERANG_WINDWALKER,//강철 부메랑 : 윈드 슬래셔				
4300	,//ITEM_BOOMERANG_DOUBLECROSS,//트라이 엣지 : 헬 트라이앵글				
5300	,//ITEM_BOOMERANG_THUNDERMASTER,//라이트닝 엣지 : 한탄의 부메랑				
6800	,//ITEM_BOOMERANG_SOULCHASER,//소울 체이서 : 둠 슬레이어				
8500	,//ITEM_BOOMERANG_GRYPHONWING,//그리폰 윙 : 윙 오브 데스 : 드래곤 윙				
10200	,//ITEM_BOOMERANG_MEGATRIAL,//로커스트 헌트 : 제노사이드 윙 : 디재스터 엣지				
//TOTAL_BOOMERANG,				

//헬멧 : ITEM_HELM				
1300	,//ITEM_HELM_BRONZE = 0,//헤드 가드					
10000	,//ITEM_HELM_BASINET,//바시넷				
18000	,//ITEM_HELM_DROW,//솔저헬름 : 센츄리온 헬멧				
27000	,//ITEM_HELM_SPIKEHEAD,//검투사의 투구 : 블러디 헬멧				
36000	,//ITEM_HELM_GLADITOR,//스파이크 헤드 : 귀신의 투구				
45000	,//ITEM_HELM_GIANT,//그랜드 헬름 : 성기사의 투구				
54000	,//ITEM_HELM_RUINED,//고대의 투구 : 환영의 투구 : 미라주 헬름				
63000	,//ITEM_HELM_TITANIUM,//용자의 투구 : 져지먼트 헬맷 : 오시리스 헬맷				
//TOTAL_HELM,				

//모자 : ITEM_HAT				
700	,//ITEM_HAT_COWBOY		= 0,//카우보이 모자		
1400	,//ITEM_HAT_RIDINGGOGGLE,//산책용 보닛				
2200	,//ITEM_HAT_BERET,//레인저 햇 : 무법자의 모자				
3000	,//ITEM_HAT_WESTERNROMANCE,//서클릿 : 골드 블레스				
4000	,//ITEM_HAT_SCOUT,//올드 윌로우 : 엘븐 햇				
5000	,//ITEM_HAT_SNIPERGOGGLE,//스나이퍼 고글 : 어쌔신 스코프				
6200	,//ITEM_HAT_ELVENCAP,//혼란의 모자 : 카오스 솔져 : 나이트메어 햇				
7600	,//ITEM_HAT_DRAGONSKULL,//프리에스테스 : 발키리 서클렛 : 오딘 크라운				
//TOTAL_HAT,				

//두건 : ,//ITEM_CAP				
1000	,//ITEM_CAP_FEATHER = 0,//공작깃털 모자				
2100	,//ITEM_CAP_BEASTMANE,//귀족의 머리띠				
3200	,//ITEM_CAP_EXPLORERHAT,//거상의 모자 : 캐러벤 리더				
4500	,//ITEM_CAP_ACECAP,//사냥꾼 모자 : 로빈훗 캡				
6000	,//ITEM_CAP_LIONMANE,//투우사의 모자 : 미노타우르스				
7500	,//ITEM_CAP_GREAVE,//해적의 모자 : 졸리로져 캡				
9300	,//ITEM_CAP_DEATH,//에이스 캡 : 브레이브 캡 : 다이너스티 캡				
11400	,//ITEM_CAP_TROLLHEAD,//드래곤 레어캡 : 히드라 헤드 : 리바이어선 캡				
//TOTAL_CAP,				

//갑옷 : ITEM_ARMOR				
2200	,//ITEM_ARMOR_BRONZE = 0,//헌터 튜닉				
16700	,//ITEM_ARMOR_SCALE,//미늘 갑옷						
30000	,//ITEM_ARMOR_BANDED,//하프 플레이트 : 밴디트 메일					
45000	,//ITEM_ARMOR_SKULL,//스컬 메일 : 마검사의 흉갑						
70000	,//ITEM_ARMOR_PLATE,//황금세공 갑옷 : 드워븐 아머					
100000	,//ITEM_ARMOR_RUNIC,//미스릴 아머 : 요정의 갑주				
130000	,//ITEM_ARMOR_MYTHRIL,//고대의 갑옷 : 불멸의 갑주 : 브리건딘			
160000	,//ITEM_ARMOR_DRAGONSKIN,//용비늘 갑옷 : 황룡의 갑옷 : 바하무트 아머				
//TOTAL_ARMOR,				

//조끼 : ITEM_VEST				
1100	,//ITEM_VEST_WESTERN = 0,//카우보이 조끼				
2300	,//ITEM_VEST_LEOPARD,//실크 조끼				
3600	,//ITEM_VEST_SILK,//방랑자의 조끼 : 서바이벌 조끼				
5000	,//ITEM_VEST_PIRATE,//도적의 조끼 : 어쌔신 베스트				
6600	,//ITEM_VEST_BALL,//벨벳 셔츠 : 고딕 셔츠				
8400	,//ITEM_VEST_STAR,//귀족의 조끼 : 은사슬 조끼				
10400	,//ITEM_VEST_SPATIOTEMPORAL,//진홍빛 셔츠 : 불사의 셔츠 : 뱀파이어 로드				
12600	,//ITEM_VEST_QUEEN,//신관의 로브 : 세라핌 로브 : 루시펠 로브				
//TOTAL_VEST,				

//코트 : ITEM_COAT				
1600	,//ITEM_COAT_SIMPLE = 0,//수수한 코트				
3400	,//ITEM_COAT_PADDING,//패딩 아머				
5400	,//ITEM_COAT_LEATHER,//털가죽 코트 : 그리즐리 스킨				
7500	,//ITEM_COAT_CUREBOIL,//큐어 보일 : 코아틀 스케일				
9900	,//ITEM_COAT_BEAST,//귀족의 코트 : 흑까마귀 코트				
12600	,//ITEM_COAT_GRIZZLY,//극지의 코트 : 블리자드 가드				
15600	,//ITEM_COAT_CROCODYLE,//윙 코트 : 가고일 코트 : 페가수스 코트				
18900	,//ITEM_COAT_HYDRASCALE,//바이스 코트 : 종말의 코트 : 카오스 엠페러				
//TOTAL_COAT,				

//건틀렛 : ITEM_GUNTLET				
400	,//ITEM_GUNTLET_IRON = 0,//핸드 가드					
3300	,//ITEM_GUNTLET_CHAIN,//청동 장갑		
6000	,//ITEM_GUNTLET_MONSTER,//체인 건틀렛 : 모험자의 장갑			
9000	,//ITEM_GUNTLET_KNIGHT,//나이트 글로브 : 명성의 장갑				
13000	,//ITEM_GUNTLET_EAGLECLAW,//비스트 핸드 : 오우거 건틀렛			
18000	,//ITEM_GUNTLET_SINE,//라이징 건틀렛 : 무쌍의 장갑				
25000	,//ITEM_GUNTLET_JUSTICEHAND,//광전사의 장갑 : 뇌격파수 : 시바의 손톱				
35000	,//ITEM_GUNTLET_HOLYHAND,//드래곤 핸드 : 백룡의 장갑 : 바하무트 핸드				
//TOTAL_GUNTLET,				

//팔찌 : ITEM_ARMLET				
200	,//ITEM_ARMLET_LEATHER		= 0,//사제의 묵주		
500	,//ITEM_ARMLET_DESERT,//여행자의 팔찌				
700	,//ITEM_ARMLET_EXPLORER,//백금 브레스렛 : 연인의 팔찌				
1000	,//ITEM_ARMLET_RAIDERS,//전사의 암렛 : 임프 암렛				
1300	,//ITEM_ARMLET_NOBLESS,//에메랄드 팔찌 : 노블레스 암렛				
1700	,//ITEM_ARMLET_DEVIL,//이블 암렛 : 몽마의 팔찌				
2100	,//ITEM_ARMLET_DIGNITY,//위엄의 팔찌 : 지배자의 팔찌 : 엠프레스 암렛				
2500	,//ITEM_ARMLET_HERO,//영웅의 팔찌 : 소울 브레스렛 : 갓 핸드				
//TOTAL_ARMLET,				

//장갑 : ITEM_GLOVE				
300	,//ITEM_GLOVE_TRAVELER		= 0,//여행자의 장갑		
700	,//ITEM_GLOVE_DUALTIE,//이중매듭 장갑				
1000	,//ITEM_GLOVE_LINEN,//소매치기 장갑 : 섀도우 핸드				
1500	,//ITEM_GLOVE_RUNE,//실크 글로브 : 귀공자의 장갑				
2000	,//ITEM_GLOVE_FAIRY,//세공사의 장갑 : 마스터 글러브				
2500	,//ITEM_GLOVE_ROCKET,//마법문양 장갑 : 커스드 글로브				
3100	,//ITEM_GLOVE_LACEMITTEN,//심판의 손 : 구원의 손 : 이터널 져지				
3800	,//ITEM_GLOVE_GLORY,//성자의 장갑 : 팔라딘 글로브 : 홀리 핸드				
//TOTAL_GLOVE,				

//킬트 : ITEM_KILT				
1800	,//ITEM_KILT_CHAIN		= 0,//밴딩 킬트						
13400	,//ITEM_KILT_DUALCHAIN,//체인 킬트						
24000	,//ITEM_KILT_BATTLE,//나이트 킬트 : 배틀 킬트					
36000	,//ITEM_KILT_NIGHTMARE,//스컬 킬트 : 사령의 바지				
50000	,//ITEM_KILT_BATTLEFIELD,//수령의 바지 : 토르의 바지			
65000	,//ITEM_KILT_DWARVEN,//미스릴 킬트 : 페어리 킬트					
80000	,//ITEM_KILT_DURAHAN,//에인션트 킬트 : 이터널 킬트 : 언리밋 킬트				
100000	,//ITEM_KILT_EARTHQUAKE,//용수염 킬트 : 청룡의 킬트 : 용기사 바지				
//TOTAL_KILT,				

//바지 : ,//ITEM_SKIRT				
900	,//ITEM_SKIRT_BROCADE = 0,//양단 스커트				
1800	,//ITEM_SKIRT_CARPSKIN,//빈티지 스커트				
2900	,//ITEM_SKIRT_VELVET,//단풍염색 치마 : 홍련의 스커트				
4000	,//ITEM_SKIRT_NOBLE,//벨벳 스커트 : 소공녀의 치마				
5300	,//ITEM_SKIRT_GENERAL,//폭풍의 스커트 : 무지개빛 치마				
6700	,//ITEM_SKIRT_GLORY,//금실의 치마 : 여제의 스커트				
8300	,//ITEM_SKIRT_CHAOS,//영광의 치마 : 현자의 치마 : 성령의 치마				
10100	,//ITEM_SKIRT_HERO,//사제의 스커트 : 비슈누 스커트 : 태양의 스커트				
//TOTAL_SKIRT,				

//바지 : ITEM_PANTS				
1300	,//ITEM_PANTS_RIDING = 0,//승마용 바지				
2700	,//ITEM_PANTS_VINTAGEJEAN,//카프스킨 팬츠				
4200	,//ITEM_PANTS_BLAZE,//망령의 팬츠 : 머미 밴디지				
6000	,//ITEM_PANTS_ASSASSIN,//흑단의 바지 : 어쌔신 팬츠				
8000	,//ITEM_PANTS_TEMPEST,//세일러 팬츠 : 제독의 바지				
10000	,//ITEM_PANTS_SCARLETLEGGINGS,//데저트 팬츠 : 캐러밴 팬츠				
12500	,//ITEM_PANTS_HEAVEN,//카오틱 팬츠 : 침묵의 바지 : 아비스 팬츠				
15200	,//ITEM_PANTS_SATANIC,//가디안 팬츠 : 켈베로스 레더 : 아누비스 바지				
//TOTAL_PANTS,				

//장화 : ITEM_GREAVES				
900	,//ITEM_GREAVES_TRAINER = 0,//코퍼 그리브			
6700	,//ITEM_GREAVES_CHAIN,//밴디트 그리브				
12000	,//ITEM_GREAVES_KNIGHT,//체인 그리브 : 나이트 그리브			
18000	,//ITEM_GREAVES_FROZEN,//프로즌 그리브 : 만년설의 신발				
26000	,//ITEM_GREAVES_GOLEM,//플레이트 부츠 : 드워븐 그리브					
35000	,//ITEM_GREAVES_GIANT,//빅풋 그리브 : 골렘 그리브				
45000	,//ITEM_GREAVES_GHOST,//마검사의 신발 : 사령의 신발 : 종말의 발소리				
58000	,//ITEM_GREAVES_LEGEND,//드래곤 그리브 : 마룡의 발자국 : 가이아 그리브				
//TOTAL_GREAVES,				

//신발 : ITEM_SHOES				
400	,//ITEM_SHOES_CLEAN = 0,//웨스턴 슈즈				
900	,//ITEM_SHOES_CHASER,//스웨이드 슈즈				
1400	,//ITEM_SHOES_LEATHER,//라이딩 슈즈 : 밀리터리 워커				
2000	,//ITEM_SHOES_ROCKY,//칠흑의 슈즈 : 마녀의 슈즈				
2600	,//ITEM_SHOES_CARVING,//귀부인의 신발 : 로얄 셀레브				
3300	,//ITEM_SHOES_NETHERWORLD,//리치 슈즈 : 팬텀 테일즈				
4100	,//ITEM_SHOES_INCARNATION,//프리즘 슈즈 : 미라클 슈즈 : 그라비티 슈즈				
5000	,//ITEM_SHOES_HEAVENS,//베이그란트 : 페이트 슈즈 : 데스티니 슈즈				
//TOTAL_SHOES,				

//부츠 : ITEM_BOOTS				
600	,//ITEM_BOOTS_SUEDE = 0,//스니커즈				
1300	,//ITEM_BOOTS_WESTERN,//스캐빈저 부츠				
2100	,//ITEM_BOOTS_RIDING,//천둥가죽 신발 : 낙뢰의 자국				
3000	,//ITEM_BOOTS_RICH,//가드너 부츠 : 토렌트 루트				
3900	,//ITEM_BOOTS_OGRE,//세일러 부츠 : 캡틴 부츠				
4500	,//ITEM_BOOTS_DARK,//저승의 신발 : 헬 스트라이더				
6200	,//ITEM_BOOTS_MIRACLE,//엘레멘탈 부츠 : 브리징 윈드 : 템페스트 부츠				
7600	,//ITEM_BOOTS_DESTINY,//에어워커 : 클라우드 부츠 : 헤븐리 부츠				
//TOTAL_BOOTS,				

//목걸이 : ITEM_NECK
2100,//ITEM_NECK0	= 0,	//명예의 펜던트
2500,//ITEM_NECK1,	//연옥의 브로치
2400,//ITEM_NECK2,	//찰나의 팔찌
2900,//ITEM_NECK3,	//황금 바늘
2800,//ITEM_NECK4,	//파열의 팔찌
3000,//ITEM_NECK5,	//메피스토 피리
2500,//ITEM_NECK6,	//사멸의 하프
2900,//ITEM_NECK7,	//인어의 머리핀
2500,//ITEM_NECK8,	//찬트의 펜던트
2300,//ITEM_NECK9,	//미래의 거울
2200,//ITEM_NECK10,	//피의 모래시계
3000,//ITEM_NECK11,	//지옥의 만화경
2500,//ITEM_NECK12,	//전능의 브로치
1800,//ITEM_NECK13,	//생명의 보옥
2600,//ITEM_NECK14,	//증식의 목걸이
2800,//ITEM_NECK15,	//천공의 목걸이
1900,//ITEM_NECK16,	//현자의 돌
2600,//ITEM_NECK17,	//꿈의 오카리나
2700,//ITEM_NECK18,	//무한의 나침반
3900,//ITEM_NECK19,	//기억의 오르골
3800,//ITEM_NECK20,	//난쟁이의 공
3700,//ITEM_NECK21,	//탐욕의 항아리
3500,//ITEM_NECK22,	//팬더인형
3300,//ITEM_NECK23,	//스마일 브로치
3100,//ITEM_NECK24,	//토르테 악보
3300,//ITEM_NECK25,	//용자의 시계
3600,//ITEM_NECK26,	//악마의 뿔피리
3400,//ITEM_NECK27,	//아만디움 달걀

//반지 : ITEM_RING
10000,//ITEM_RING0	= 0,	//사신의 반지
9000,//ITEM_RING1,	//통찰의 반지
12000,//ITEM_RING2,	//시공의 반지
10000,//ITEM_RING3,	//해방의 반지
11000,//ITEM_RING4,	//산호석 반지
13000,//ITEM_RING5,	//생환의 반지
12400,//ITEM_RING6,	//희생의 반지
13600,//ITEM_RING7,	//폭주의 반지
14000,//ITEM_RING8,	//골렘의 반지
10000,//ITEM_RING9,	//광대의 반지
12200,//ITEM_RING10,	//원한의 반지
12000,//ITEM_RING11,	//신념의 반지
11200,//ITEM_RING12,	//광포의 반지
14600,//ITEM_RING13,	//승자의 반지
14900,//ITEM_RING14,	//궁극의 반지
15200,//ITEM_RING15,	//차원의 반지
15900,//ITEM_RING16,	//영화의 반지
16600,//ITEM_RING17,	//행운의 반지

//보석 : ITEM_GEM
5000,//ITEM_GEM_RUBY	= 0,	//루비
5000,//ITEM_GEM_SAPPHIRE,	//사파이어
5000,//ITEM_GEM_AMETHYST,	//자수정
5000,//ITEM_GEM_DIAMOND,	//다이아몬드
5000,//ITEM_GEM_PERL,	//진주
5000,//ITEM_GEM_EMERALD,	//에메랄드

//소모아이템 : ITEM_WASTE
1000,//ITEM_WASTE_RETURN	= 0,	//귀환서
500,//ITEM_WASTE_STAR,	//별의 씨앗
2000,//ITEM_WASTE_MOON,	//달의 씨앗
10000,//ITEM_WASTE_SUN,	//태양의 씨앗
800,//ITEM_WASTE_SILVER,	//은빛 허브
3200,//ITEM_WASTE_GOLD,	//금빛 허브
12000,//ITEM_WASTE_SCARLET,	//진홍빛 허브
32000,//ITEM_WASTE_WATER,	//세계수의 물
1500,//ITEM_WASTE_ANTIDOTE,	//해독제
1500,//ITEM_WASTE_FLUTE,	//풀피리
1500,//ITEM_WASTE_EYEWASH,	//안약
1500,//ITEM_WASTE_HOLYWATER,	//성수
1500,//ITEM_WASTE_WING,	//릴의 날개
3000,//ITEM_WASTE_FIRESTONE,	//불의 정령석
3000,//ITEM_WASTE_FROSTSTONE,	//물의 정령석
3000,//ITEM_WASTE_THUNDERSTONE,	//번개의 정령석
3000,//ITEM_WASTE_HOLYSTONE,	//빛의 정령석
3000,//ITEM_WASTE_DARKSTONE,	//어둠의 정령석
10000,//ITEM_WASTE_FIREELEMENTAL,	//화염의 정령석
10000,//ITEM_WASTE_FROSTELEMENTAL,	//얼음의 정령석
10000,//ITEM_WASTE_THUNDERELEMENTAL,	//천둥의 정령석
10000,//ITEM_WASTE_HOLYELEMENTAL,	//섬광의 정령석
10000,//ITEM_WASTE_DARKELEMENTAL,	//칠흑의 정령석
0,//ITEM_WASTE_DAMAGE
0,//ITEM_WASTE_DEFENSE
0,//ITEM_WASTE_MAGIC
0,//ITEM_WASTE_SKILL

//철계열 제작재료 : ITEM_IRON
500,//ITEM_IRON_LV1 = 0,	//철광석(45)
800,//ITEM_IRON_LV2,	//은괴(39)//@@
1300,//ITEM_IRON_LV3,	//토륨 파편(39)
2000,//ITEM_IRON_LV4,	//다마스커스(42)
3300,//ITEM_IRON_LV5,	//아다만티움(39)
4500,//ITEM_IRON_LV6,	//미스릴 결정(42)
6000,//ITEM_IRON_LV7,	//오리하르콘(48)
7500,//ITEM_IRON_LV8,	//이터늄 원석(30)

//가죽계열 제작재료 : ITEM_LEATHER
400,//ITEM_LEATHER_LV1	= 0,	//얇은 가죽(45)
600,//ITEM_LEATHER_LV2,	//반짝이는 비늘(39)
1000,//ITEM_LEATHER_LV3,	//무쇠 가죽(39)
1700,//ITEM_LEATHER_LV4,	//돌연변이 비늘(42)
2500,//ITEM_LEATHER_LV5,	//달빛 가죽(39)
3700,//ITEM_LEATHER_LV6,	//바실리스크 비늘(42)
4800,//ITEM_LEATHER_LV7,	//지옥사자 가죽(48)
6000,//ITEM_LEATHER_LV8,	//붉은 용비늘(30)

//천계열 제작재료 : ITEM_CLOTH
300,//ITEM_CLOTH_LV1	= 0,	//감색 실타래(44)
500,//ITEM_CLOTH_LV2,	//거미줄 옷감(41)
800,//ITEM_CLOTH_LV3,	//비단 실타래(40)
1300,//ITEM_CLOTH_LV4,	//심연의 실타래(41)
2000,//ITEM_CLOTH_LV5,	//은하수 옷감(40)
2800,//ITEM_CLOTH_LV6,	//천고의 옷감(45)
3600,//ITEM_CLOTH_LV7,	//공허의 실타래(45)
4500,//ITEM_CLOTH_LV8,	//룬문자 옷감(28)

//나무계열 제작재료 : ITEM_WOOD
300,//ITEM_WOOD_LV1	= 0,	//벼락맞은 가지(60)
500,//ITEM_WOOD_LV2,	//얼어붙은 가지(29)
800,//ITEM_WOOD_LV3,	//맨드레이 뿌리(44)
1300,//ITEM_WOOD_LV4,	//거인의 뿌리(37)
2200,//ITEM_WOOD_LV5,	//저주받은 뿌리(44)
3200,//ITEM_WOOD_LV6,	//고대의 가지(37)
4200,//ITEM_WOOD_LV7,	//지옥의 뿌리(53)
5200,//ITEM_WOOD_LV8,	//세계수의 가지(20)

//특수재료 : ITEM_ESSENCE
1000,//ITEM_ESSENCE0	= 0,	//단단한 껍질(9)
1200,//ITEM_ESSENCE1,	//오염된 넝쿨(9)
1200,//ITEM_ESSENCE2,	//심연의 눈동자(7)
1500,//ITEM_ESSENCE3,	//저주받은 해골(11)
2800,//ITEM_ESSENCE4,	//푸른 비늘(9)
3300,//ITEM_ESSENCE5,	//반짝이는 심장(9)
3000,//ITEM_ESSENCE6,	//야생의 돌(18)
4000,//ITEM_ESSENCE7,	//갈라진 어금니(18)
5500,//ITEM_ESSENCE8,	//염의 증류수(9)
6000,//ITEM_ESSENCE9,	//빛의 깃털(9)
5000,//ITEM_ESSENCE10,	//질풍의 조각(12)
6000,//ITEM_ESSENCE11,	//눈의 결정(12)
7000,//ITEM_ESSENCE12,	//결빙의 옥루(12)
6000,//ITEM_ESSENCE13,	//우레 가루(6)
8000,//ITEM_ESSENCE14,	//뇌문의 쐐기(6)
5000,//ITEM_ESSENCE15,	//마력의 구슬(6)
8500,//ITEM_ESSENCE16,	//요정의 눈물(27)
9500,//ITEM_ESSENCE17,	//광휘의 염료(27)
11500,//ITEM_ESSENCE18,	//용맹의 증표(9)
10000,//ITEM_ESSENCE19,	//슬라임 윤활액(9)
10000,//ITEM_ESSENCE20,	//혼미의 영석(9)
13000,//ITEM_ESSENCE21,	//월석 파편(9)
13000,//ITEM_ESSENCE22,	//영혼의 꼬리(9)
14500,//ITEM_ESSENCE23,	//농염의 십자가(9)
16000,//ITEM_ESSENCE24,	//황천의 보주(9)
17500,//ITEM_ESSENCE25,	//유혹의 향료(9)
20000,//ITEM_ESSENCE26,	//만고의 뿔(18)
21000,//ITEM_ESSENCE27,	//전능의 수정(18)
16000,//ITEM_ESSENCE28,	//은하수 날개(9)
17500,//ITEM_ESSENCE29,	//뫼비우스의 띠(9)
17000,//ITEM_ESSENCE30,	//영원의 상(9)
17500,//ITEM_ESSENCE31,	//노스 제왕석(9)
22500,//ITEM_ESSENCE32,	//포비든 스톤(18)
35000,//ITEM_ESSENCE33,	//묘지의 반딧불(9)
40000,//ITEM_ESSENCE34,	//지배의 삼지창(9)
42500,//ITEM_ESSENCE35,	//엠페러 스톤(18)
47500,//ITEM_ESSENCE36,	//볼케이노 잼(18)
48500,//ITEM_ESSENCE37,	//프로즌 셸(18)
51000,//ITEM_ESSENCE38,	//인피니티 볼트(18)
57500,//ITEM_ESSENCE39,	//다즐링 램프(6)
60000,//ITEM_ESSENCE40,	//가공된 마석(6)
70000,//ITEM_ESSENCE41,	//황천의 닻(6)
75000,//ITEM_ESSENCE42,	//금단의 과실(6)
72500,//ITEM_ESSENCE43,	//적룡의 숨결(6)
80000,//ITEM_ESSENCE44,	//원혼의 결정(6)

0,
};
static const unsigned int itemSellPrice_builtin[] = {
	//검 : ITEM_SWORD
	1000,//ITEM_SWORD_STICK	= 0,	//연습용 몽둥이
	2000,//ITEM_SWORD_LONG,	//롱소드
	4000,//ITEM_SWORD_CUTTER,	//처형자의 검 : 파멸의 참마도
	8000,//ITEM_SWORD_SEEKER,	//추적자의 검 : 격노의 양날검
	16000,//ITEM_SWORD_ELVEN,	//수호자의 검 : 왕가의 수호자
	32000,//ITEM_SWORD_GHOST,	//나찰의 검 : 소울 크래셔
	64000,//ITEM_SWORD_DIMENSIONAL,	//차원의 검 : 천공의 검 : 스타더스트
	128000,//ITEM_SWORD_DRAGONTOOTH,	//드래곤 클로우 : 황룡의 어금니 : 신룡강마검

	//총 : ITEM_GUN
	1000,//ITEM_GUN_PISTOL	= 0,	//발화식 총
	2000,//ITEM_GUN_REVOLVER,	//리볼버 파이슨
	4000,//ITEM_GUN_MAGNUM,	//45구경 오토건 : 사일런트 킬러
	8000,//ITEM_GUN_AUTOGUN45MM,	//고져스 건 : 럭셔리 캐논
	16000,//ITEM_GUN_JEWELGUN,	//회천마도총 : 마도머신건
	32000,//ITEM_GUN_EXPLOSION,	//태양의 총 : 슈퍼노바
	64000,//ITEM_GUN_CROSSFIRE,	//헬파이어 건 : 인페르노 캐논 : 마룡열화포
	128000,//ITEM_GUN_INFERNO,	//크로스 파이어 : 테스타먼트 : 라그나로크

	//부메랑 : ITEM_BOOMERANG
	1000,//ITEM_BOOMERANG_BOOMERANG	= 0,	//사냥용 부메랑
	2000,//ITEM_BOOMERANG_VOYAGER,	//슬라이서
	4000,//ITEM_BOOMERANG_WINDWALKER,	//강철 부메랑 : 윈드 슬래셔
	8000,//ITEM_BOOMERANG_DOUBLECROSS,	//트라이 엣지 : 헬 트라이앵글
	16000,//ITEM_BOOMERANG_THUNDERMASTER,	//라이트닝 엣지 : 한탄의 부메랑
	32000,//ITEM_BOOMERANG_SOULCHASER,	//소울 체이서 : 둠 슬레이어
	64000,//ITEM_BOOMERANG_GRYPHONWING,	//그리폰 윙 : 윙 오브 데스 : 드래곤 윙
	128000,//ITEM_BOOMERANG_MEGATRIAL,	//로커스트 헌트 : 제노사이드 윙 : 디재스터 엣지

	//헬멧 : ITEM_HELM
	1000,//ITEM_HELM_BRONZE	= 0,	//헤드 가드
	2000,//ITEM_HELM_BASINET,	//바시넷
	4000,//ITEM_HELM_DROW,	//솔저헬름 : 센츄리온 헬멧
	8000,//ITEM_HELM_SPIKEHEAD,	//검투사의 투구 : 블러디 헬멧
	16000,//ITEM_HELM_GLADITOR,	//스파이크 헤드 : 귀신의 투구
	32000,//ITEM_HELM_GIANT,	//그랜드 헬름 : 성기사의 투구
	64000,//ITEM_HELM_RUINED,	//고대의 투구 : 환영의 투구 : 미라주 헬름
	128000,//ITEM_HELM_TITANIUM,	//용자의 투구 : 져지먼트 헬맷 : 오시리스 헬맷

	//모자 : ITEM_HAT
	10,	//산책용 보닛
	20,	//카우보이 모자
	40,	//레인저 햇 : 무법자의 모자
	80,	//서클릿 : 골드 블레스
	160,	//올드 윌로우 : 엘븐 햇
	320,	//스나이퍼 고글 : 어쌔신 스코프
	640,	//혼란의 모자 : 카오스 솔져 : 나이트메어 햇
	1280,	//프리에스테스 : 발키리 서클렛 : 오딘 크라운


	//두건 : ITEM_CAP	
	10,	//공작깃털 모자
	20,	//귀족의 머리띠
	40,	//거상의 모자 : 캐러벤 리더
	80,	//사냥꾼 모자 : 로빈훗 캡
	160,	//투우사의 모자 : 미노타우르스
	320,	//해적의 모자 : 졸리로져 캡
	640,	//에이스 캡 : 브레이브 캡 : 다이너스티 캡
	1280,	//드래곤 레어캡 : 히드라 헤드 : 리바이어선 캡

	//갑옷 : ITEM_ARMOR	
	10,	//헌터 튜닉
	20,	//미늘 갑옷
	40,	//하프 플레이트 : 밴디트 메일
	80,	//스컬 메일 : 마검사의 흉갑
	160,	//황금세공 갑옷 : 드워븐 아머
	320,	//미스릴 아머 : 요정의 갑주
	640,	//고대의 갑옷 : 불멸의 갑주 : 브리건딘
	1280,	//용비늘 갑옷 : 황룡의 갑옷 : 바하무트 아머

	//조끼 : ITEM_VEST	
	10,	//카우보이 조끼
	20,	//실크 조끼
	40,	//방랑자의 조끼 : 서바이벌 조끼
	80,	//도적의 조끼 : 어쌔신 베스트
	160,	//벨벳 셔츠 : 고딕 셔츠
	320,	//귀족의 조끼 : 은사슬 조끼
	640,	//진홍빛 셔츠 : 불사의 셔츠 : 뱀파이어 로드
	1280,	//신관의 로브 : 세라핌 로브 : 루시펠 로브

	//코트 : ITEM_COAT	
	10,	//수수한 코트
	20,	//패딩 아머
	40,	//털가죽 코트 : 그리즐리 스킨
	80,	//큐어 보일 : 코아틀 스케일
	160,	//귀족의 코트 : 코아틀 스케일
	320,	//극지의 코트 : 블리자드 가드
	640,	//윙 코트 : 가고일 코트 : 페가수스 코트
	1280,	//바이스 코트 : 종말의 코트 : 카오스 엠페러

	//건틀렛 : ITEM_GUNTLET	
	10,	//핸드 가드
	20,	//청동 장갑
	40,	//체인 건틀렛 : 모험자의 장갑
	80,	//나이트 글로브 : 명성의 장갑
	160,	//비스트 핸드 : 오우거 건틀렛
	320,	//라이징 건틀렛 : 무쌍의 장갑
	640,	//광전사의 장갑 : 뇌격파수 : 시바의 손톱
	1280,	//드래곤 핸드 : 백룡의 장갑 : 바하무트 핸드

	//팔찌 : ITEM_ARMLET	
	10,	//사제의 묵주
	20,	//여행자의 팔찌
	40,	//백금 브레스렛 : 연인의 팔찌
	80,	//전사의 암렛 : 임프 암렛
	160,	//에메랄드 팔찌 : 노블레스 암렛
	320,	//이블 암렛 : 몽마의 팔찌
	640,	//위엄의 팔찌 : 지배자의 팔찌 : 엠프레스 암렛
	1280,	//영웅의 팔찌 : 소울 브레스렛 : 갓 핸드

	//장갑 : ITEM_GLOVE	
	10,	//여행자의 장갑
	20,	//이중매듭 장갑
	40,	//소매치기 장갑 : 섀도우 핸드
	80,	//실크 글로브 : 귀공자의 장갑
	160,	//세공사의 장갑 : 마스터 글러브
	320,	//마법문양 장갑 : 커스드 글로브
	640,	//심판의 손 : 구원의 손 : 이터널 져지
	1280,	//성자의 장갑 : 팔라딘 글로브 : 홀리 핸드

	//킬트 : ITEM_KILT	
	10,	//밴딩 킬트
	20,	//체인 킬트
	40,	//나이트 킬트 : 배틀 킬트
	80,	//스컬 킬트 : 사령의 바지
	160,	//수령의 바지 : 토르의 바지
	320,	//미스릴 킬트 : 페어리 킬트
	640,	//에인션트 킬트 : 이터널 킬트 : 언리밋 킬트
	1280,	//용수염 킬트 : 청룡의 킬트 : 용기사 바지

	//스커트 : ITEM_SKIRT	
	10,	//양단 스커트
	20,	//빈티지 스커트
	40,	//단풍염색 치마 : 홍련의 스커트
	80,	//벨벳 스커트 : 소공녀의 치마
	160,	//폭풍의 스커트 : 무지개빛 치마
	320,	//금실의 치마 : 여제의 스커트
	640,	//영광의 치마 : 현자의 치마 : 성령의 치마
	1280,	//사제의 스커트 : 비슈누 스커트 : 태양의 스커트

	//바지 : ITEM_PANTS	
	10,	//승마용 바지
	20,	//카프스킨 팬츠
	40,	//망령의 팬츠 : 머미 밴디지
	80,	//흑단의 바지 : 어쌔신 팬츠
	160,	//세일러 팬츠 : 제독의 바지
	320,	//데저트 팬츠 : 캐러밴 팬츠
	640,	//카오틱 팬츠 : 침묵의 바지 : 아비스 팬츠
	1280,	//가디안 팬츠 : 켈베로스 레더 : 아누비스 바지

	//장화 : ITEM_GREAVES	
	10,	//코퍼 그리브
	20,	//밴디트 그리브
	40,	//체인 그리브 : 나이트 그리브
	80,	//프로즌 그리브 : 만년설의 신발
	160,	//플레이트 부츠 : 드워븐 그리브
	320,	//빅풋 그리브 : 골렘 그리브
	640,	//마검사의 신발 : 사령의 신발 : 종말의 발소리
	1280,	//드래곤 그리브 : 마룡의 발자국 : 가이아 그리브

	//신발 : ITEM_SHOES	
	10,	//웨스턴 슈즈
	20,	//스웨이드 슈즈
	40,	//라이딩 슈즈 : 밀리터리 워커
	80,	//칠흑의 슈즈 : 마녀의 슈즈
	160,	//귀부인의 신발 : 로얄 셀레브
	320,	//리치 슈즈 : 팬텀 테일즈
	640,	//프리즘 슈즈 : 미라클 슈즈 : 그라비티 슈즈
	1280,	//베이그란트 : 페이트 슈즈 : 데스티니 슈즈

	//부츠 : :ITEM_BOOTS	
	10,	//스니커즈
	20,	//스캐빈저 부츠
	40,	//천둥가죽 신발 : 낙뢰의 자국
	80,	//가드너 부츠 : 토렌트 루트
	160,	//세일러 부츠 : 캡틴 부츠
	320,	//저승의 신발 : 헬 스트라이더
	640,	//엘레멘탈 부츠 : 브리징 윈드 : 템페스트 부츠
	1280,	//에어워커 : 클라우드 부츠 : 헤븐리 부츠



	//목걸이 : ITEM_NECK
	5000,//ITEM_NECK0	= 0,	//명예의 펜던트
	5000,//ITEM_NECK1,	//연옥의 브로치
	5000,//ITEM_NECK2,	//찰나의 팔찌
	5000,//ITEM_NECK3,	//황금 바늘
	5000,//ITEM_NECK4,	//파열의 팔찌
	5000,//ITEM_NECK5,	//메피스토 피리
	5000,//ITEM_NECK6,	//사멸의 하프
	5000,//ITEM_NECK7,	//인어의 머리핀
	5000,//ITEM_NECK8,	//찬트의 펜던트
	5000,//ITEM_NECK9,	//미래의 거울
	5000,//ITEM_NECK10,	//피의 모래시계
	5000,//ITEM_NECK11,	//지옥의 만화경
	5000,//ITEM_NECK12,	//전능의 브로치
	5000,//ITEM_NECK13,	//생명의 보옥
	5000,//ITEM_NECK14,	//증식의 목걸이
	5000,//ITEM_NECK15,	//천공의 목걸이
	5000,//ITEM_NECK16,	//현자의 돌
	5000,//ITEM_NECK17,	//꿈의 오카리나
	5000,//ITEM_NECK18,	//무한의 나침반
	5000,//ITEM_NECK19,	//기억의 오르골
	5000,//ITEM_NECK20,	//난쟁이의 공
	5000,//ITEM_NECK21,	//탐욕의 항아리
	5000,//ITEM_NECK22,	//팬더인형
	5000,//ITEM_NECK23,	//스마일 브로치
	5000,//ITEM_NECK24,	//토르테 악보
	5000,//ITEM_NECK25,	//용자의 시계
	5000,//ITEM_NECK26,	//악마의 뿔피리
	5000,//ITEM_NECK27,	//아만디움 달걀

	//반지 : ITEM_RING
	5000,//ITEM_RING0	= 0,	//사신의 반지
	5000,//ITEM_RING1,	//통찰의 반지
	5000,//ITEM_RING2,	//시공의 반지
	5000,//ITEM_RING3,	//해방의 반지
	5000,//ITEM_RING4,	//산호석 반지
	5000,//ITEM_RING5,	//생환의 반지
	5000,//ITEM_RING6,	//희생의 반지
	5000,//ITEM_RING7,	//폭주의 반지
	5000,//ITEM_RING8,	//골렘의 반지
	5000,//ITEM_RING9,	//광대의 반지
	5000,//ITEM_RING10,	//원한의 반지
	5000,//ITEM_RING11,	//신념의 반지
	5000,//ITEM_RING12,	//광포의 반지
	5000,//ITEM_RING13,	//승자의 반지
	5000,//ITEM_RING14,	//궁극의 반지
	5000,//ITEM_RING15,	//차원의 반지
	5000,//ITEM_RING16,	//영화의 반지
	5000,//ITEM_RING17,	//행운의 반지

	//보석 : ITEM_GEM
	3000,//ITEM_GEM_RUBY	= 0,	//루비
	3000,//ITEM_GEM_SAPPHIRE,	//사파이어
	3000,//ITEM_GEM_AMETHYST,	//자수정
	3000,//ITEM_GEM_DIAMOND,	//다이아몬드
	3000,//ITEM_GEM_PERL,	//진주
	3000,//ITEM_GEM_EMERALD,	//에메랄드

	//소모아이템 : ITEM_WASTE
	1000,//ITEM_WASTE_RETURN	= 0,	//귀환서
	500,//ITEM_WASTE_STAR,	//별의 씨앗
	2000,//ITEM_WASTE_MOON,	//달의 씨앗
	10000,//ITEM_WASTE_SUN,	//태양의 씨앗
	800,//ITEM_WASTE_SILVER,	//은빛 허브
	3200,//ITEM_WASTE_GOLD,	//금빛 허브
	12000,//ITEM_WASTE_SCARLET,	//진홍빛 허브
	32000,//ITEM_WASTE_WATER,	//세계수의 물
	1500,//ITEM_WASTE_ANTIDOTE,	//해독제
	1500,//ITEM_WASTE_FLUTE,	//풀피리
	1500,//ITEM_WASTE_EYEWASH,	//안약
	1500,//ITEM_WASTE_HOLYWATER,	//성수
	1500,//ITEM_WASTE_WING,	//릴의 날개
	3000,//ITEM_WASTE_FIRESTONE,	//불의 정령석
	3000,//ITEM_WASTE_FROSTSTONE,	//물의 정령석
	3000,//ITEM_WASTE_THUNDERSTONE,	//번개의 정령석
	3000,//ITEM_WASTE_HOLYSTONE,	//빛의 정령석
	3000,//ITEM_WASTE_DARKSTONE,	//어둠의 정령석
	10000,//ITEM_WASTE_FIREELEMENTAL,	//화염의 정령석
	10000,//ITEM_WASTE_FROSTELEMENTAL,	//얼음의 정령석
	10000,//ITEM_WASTE_THUNDERELEMENTAL,	//천둥의 정령석
	10000,//ITEM_WASTE_HOLYELEMENTAL,	//섬광의 정령석
	10000,//ITEM_WASTE_DARKELEMENTAL,	//칠흑의 정령석
	0,
	0,
	0,
	0,

	//철계열 제작재료 : ITEM_IRON
	500,//ITEM_IRON_LV1 = 0,	//철광석(45)
	800,//ITEM_IRON_LV2,	//은괴(39)//@@
	1300,//ITEM_IRON_LV3,	//토륨 파편(39)
	2000,//ITEM_IRON_LV4,	//다마스커스(42)
	3300,//ITEM_IRON_LV5,	//아다만티움(39)
	4500,//ITEM_IRON_LV6,	//미스릴 결정(42)
	6000,//ITEM_IRON_LV7,	//오리하르콘(48)
	7500,//ITEM_IRON_LV8,	//이터늄 원석(30)

	//가죽계열 제작재료 : ITEM_LEATHER
	400,//ITEM_LEATHER_LV1	= 0,	//얇은 가죽(45)
	600,//ITEM_LEATHER_LV2,	//반짝이는 비늘(39)
	1000,//ITEM_LEATHER_LV3,	//무쇠 가죽(39)
	1700,//ITEM_LEATHER_LV4,	//돌연변이 비늘(42)
	2500,//ITEM_LEATHER_LV5,	//달빛 가죽(39)
	3700,//ITEM_LEATHER_LV6,	//바실리스크 비늘(42)
	4800,//ITEM_LEATHER_LV7,	//지옥사자 가죽(48)
	6000,//ITEM_LEATHER_LV8,	//붉은 용비늘(30)

	//천계열 제작재료 : ITEM_CLOTH
	300,//ITEM_CLOTH_LV1	= 0,	//감색 실타래(44)
	500,//ITEM_CLOTH_LV2,	//거미줄 옷감(41)
	800,//ITEM_CLOTH_LV3,	//비단 실타래(40)
	1300,//ITEM_CLOTH_LV4,	//심연의 실타래(41)
	2000,//ITEM_CLOTH_LV5,	//은하수 옷감(40)
	2800,//ITEM_CLOTH_LV6,	//천고의 옷감(45)
	3600,//ITEM_CLOTH_LV7,	//공허의 실타래(45)
	4500,//ITEM_CLOTH_LV8,	//룬문자 옷감(28)

	//나무계열 제작재료 : ITEM_WOOD
	300,//ITEM_WOOD_LV1	= 0,	//벼락맞은 가지(60)
	500,//ITEM_WOOD_LV2,	//얼어붙은 가지(29)
	800,//ITEM_WOOD_LV3,	//맨드레이 뿌리(44)
	1300,//ITEM_WOOD_LV4,	//거인의 뿌리(37)
	2200,//ITEM_WOOD_LV5,	//저주받은 뿌리(44)
	3200,//ITEM_WOOD_LV6,	//고대의 가지(37)
	4200,//ITEM_WOOD_LV7,	//지옥의 뿌리(53)
	5200,//ITEM_WOOD_LV8,	//세계수의 가지(20)

	//특수재료 : ITEM_ESSENCE
	1000,//ITEM_ESSENCE0	= 0,	//단단한 껍질(9)
	1200,//ITEM_ESSENCE1,	//오염된 넝쿨(9)
	1200,//ITEM_ESSENCE2,	//심연의 눈동자(7)
	1500,//ITEM_ESSENCE3,	//저주받은 해골(11)
	2800,//ITEM_ESSENCE4,	//푸른 비늘(9)
	3300,//ITEM_ESSENCE5,	//반짝이는 심장(9)
	3000,//ITEM_ESSENCE6,	//야생의 돌(18)
	4000,//ITEM_ESSENCE7,	//갈라진 어금니(18)
	5500,//ITEM_ESSENCE8,	//염의 증류수(9)
	6000,//ITEM_ESSENCE9,	//빛의 깃털(9)
	5000,//ITEM_ESSENCE10,	//질풍의 조각(12)
	6000,//ITEM_ESSENCE11,	//눈의 결정(12)
	7000,//ITEM_ESSENCE12,	//결빙의 옥루(12)
	6000,//ITEM_ESSENCE13,	//우레 가루(6)
	8000,//ITEM_ESSENCE14,	//뇌문의 쐐기(6)
	5000,//ITEM_ESSENCE15,	//마력의 구슬(6)
	8500,//ITEM_ESSENCE16,	//요정의 눈물(27)
	9500,//ITEM_ESSENCE17,	//광휘의 염료(27)
	11500,//ITEM_ESSENCE18,	//용맹의 증표(9)
	10000,//ITEM_ESSENCE19,	//슬라임 윤활액(9)
	10000,//ITEM_ESSENCE20,	//혼미의 영석(9)
	13000,//ITEM_ESSENCE21,	//월석 파편(9)
	13000,//ITEM_ESSENCE22,	//영혼의 꼬리(9)
	14500,//ITEM_ESSENCE23,	//농염의 십자가(9)
	16000,//ITEM_ESSENCE24,	//황천의 보주(9)
	17500,//ITEM_ESSENCE25,	//유혹의 향료(9)
	20000,//ITEM_ESSENCE26,	//만고의 뿔(18)
	21000,//ITEM_ESSENCE27,	//전능의 수정(18)
	16000,//ITEM_ESSENCE28,	//은하수 날개(9)
	17500,//ITEM_ESSENCE29,	//뫼비우스의 띠(9)
	17000,//ITEM_ESSENCE30,	//영원의 상(9)
	17500,//ITEM_ESSENCE31,	//노스 제왕석(9)
	22500,//ITEM_ESSENCE32,	//포비든 스톤(18)
	35000,//ITEM_ESSENCE33,	//묘지의 반딧불(9)
	40000,//ITEM_ESSENCE34,	//지배의 삼지창(9)
	42500,//ITEM_ESSENCE35,	//엠페러 스톤(18)
	47500,//ITEM_ESSENCE36,	//볼케이노 잼(18)
	48500,//ITEM_ESSENCE37,	//프로즌 셸(18)
	51000,//ITEM_ESSENCE38,	//인피니티 볼트(18)
	57500,//ITEM_ESSENCE39,	//다즐링 램프(6)
	60000,//ITEM_ESSENCE40,	//가공된 마석(6)
	70000,//ITEM_ESSENCE41,	//황천의 닻(6)
	75000,//ITEM_ESSENCE42,	//금단의 과실(6)
	72500,//ITEM_ESSENCE43,	//적룡의 숨결(6)
	80000,//ITEM_ESSENCE44,	//원혼의 결정(6)

	0,
};
static const unsigned short itemStar_builtin[] = {
	//검 : ITEM_SWORD
	100,//ITEM_SWORD_STICK = 000,//1//연습용 몽둥이
	100,//ITEM_SWORD_LONG00,//2//롱소드
	100,//ITEM_SWORD_CUTTER00,//3//처형자의 검
	100,//ITEM_SWORD_RUIN00,//4//파멸의 참마도
	100,//ITEM_SWORD_SEEKER00,//5//추적자의 검
	200,//ITEM_SWORD_DOUBLE00,//6//격노의 양날검
	200,//ITEM_SWORD_ELVEN00,//7//수호자의 검
	200,//ITEM_SWORD_ROYAL00,//8//왕가의 수호자
	200,//ITEM_SWORD_GHOST00,//9//나찰의 검
	200,//ITEM_SWORD_GHOST200,//10//소울 크래셔
	300,//ITEM_SWORD_FRAME00,//11//플레임소드
	300,//ITEM_SWORD_ICE00,//12//아이스소드
	300,//ITEM_SWORD_THUNDER00,//13//썬더소드
	300,//ITEM_SWORD_EARTH00,//14//어스소드
	300,//ITEM_SWORD_LAEVATEINN00,//15//레바테인
	400,//ITEM_SWORD_STORMBRINGER00,//16//스톰브링거
	400,//ITEM_SWORD_CALADBOLG00,//17//칼라드볼그
	400,//ITEM_SWORD_BALMUNG00,//18//발뭉
	400,//ITEM_SWORD_HRUNTING00,//19//흐룬팅
	400,//ITEM_SWORD_GIANT00,//20//거인의 칼
	500,//ITEM_SWORD_MISTILTEINN00,//21//미스틸테인
	500,//ITEM_SWORD_EXCALIBUR00,//22//엑스칼리버
	500,//ITEM_SWORD_HOLY00,//23//홀리소드
	500,//ITEM_SWORD_DARK00,//24//다크소드
	500,//ITEM_SWORD_LEO00,//25//레오소드
	600,//ITEM_SWORD_DEATH00,//26//사신의 낫
	600,//ITEM_SWORD_DRAGONCLOW00,//27//드래곤 클로우
	600,//ITEM_SWORD_DRAGONTOOTH00,//28//황룡의 어금니
	600,//ITEM_SWORD_DRAGONGOD00,//29//신룡마강검
	600,//ITEM_SWORD_DRAGONSLAYER00,//30//드래곤 슬레이어
	600,//ITEM_SWORD_ULTIMATE00,//31//얼티밋소드
	600,//ITEM_SWORD_DIMENSIONAL00,//32//차원의 검
	600,//ITEM_SWORD_HEAVEN00,//33//천공의 검
	600,//ITEM_SWORD_STARDUST00,//34//스타더스트
	600,//ITEM_SWORD_KING00,//35//패왕의 검
	//TOTAL_SWORD,

	//총 : //ITEM_GUN
	100,//ITEM_GUN_PISTOL = 000,//발화식 총
	100,//ITEM_GUN_REVOLVER00,//리볼버 파이슨
	200,//ITEM_GUN_MAGNUM00,//45구경 오토건 : 사일런트 킬러
	200,//ITEM_GUN_AUTOGUN45MM00,//고져스 건 : 럭셔리 캐논
	300,//ITEM_GUN_JEWELGUN00,//회천마도총 : 마도머신건
	400,//ITEM_GUN_EXPLOSION00,//태양의 총 : 슈퍼노바
	500,//ITEM_GUN_CROSSFIRE00,//헬파이어 건 : 인페르노 캐논 : 마룡열화포
	600,//ITEM_GUN_INFERNO00,//크로스 파이어 : 테스타먼트 : 라그나로크
	//TOTAL_GUN,

	//부메랑 : //ITEM_BOOMERANG
	100,//ITEM_BOOMERANG_BOOMERANG = 000,//사냥용 부메랑
	100,//ITEM_BOOMERANG_VOYAGER00,//슬라이서
	200,//ITEM_BOOMERANG_WINDWALKER00,//강철 부메랑 : 윈드 슬래셔
	200,//ITEM_BOOMERANG_DOUBLECROSS00,//트라이 엣지 : 헬 트라이앵글
	300,//ITEM_BOOMERANG_THUNDERMASTER00,//라이트닝 엣지 : 한탄의 부메랑
	400,//ITEM_BOOMERANG_SOULCHASER00,//소울 체이서 : 둠 슬레이어
	500,//ITEM_BOOMERANG_GRYPHONWING00,//그리폰 윙 : 윙 오브 데스 : 드래곤 윙
	600,//ITEM_BOOMERANG_MEGATRIAL00,//로커스트 헌트 : 제노사이드 윙 : 디재스터 엣지
	//TOTAL_BOOMERANG,

	//헬멧 : //ITEM_HELM
	100,//ITEM_HELM_BRONZE = 000,//1//헤드 가드
	200,//ITEM_HELM_BASINET00,//6//바시넷
	300,//ITEM_HELM_DROW00,//9//솔저헬름 : 센츄리온 헬멧
	300,//ITEM_HELM_SPIKEHEAD00,//12//검투사의 투구 : 블러디 헬멧
	400,//ITEM_HELM_GLADITOR00,//15//스파이크 헤드 : 귀신의 투구
	500,//ITEM_HELM_GIANT00,//18//그랜드 헬름 : 성기사의 투구
	600,//ITEM_HELM_RUINED00,//21//고대의 투구 : 환영의 투구 : 미라주 헬름
	600,//ITEM_HELM_TITANIUM00,//24//용자의 투구 : 져지먼트 헬맷 : 오시리스 헬맷
	//TOTAL_HELM,

	//모자 : //ITEM_HAT
	100,//ITEM_HAT_COWBOY = 000,//카우보이 모자
	100,//ITEM_HAT_RIDINGGOGGLE00,//산책용 보닛
	200,//ITEM_HAT_BERET00,//레인저 햇 : 무법자의 모자
	200,//ITEM_HAT_WESTERNROMANCE00,//서클릿 : 골드 블레스
	300,//ITEM_HAT_SCOUT00,//올드 윌로우 : 엘븐 햇
	400,//ITEM_HAT_SNIPERGOGGLE00,//스나이퍼 고글 : 어쌔신 스코프
	500,//ITEM_HAT_ELVENCAP00,//혼란의 모자 : 카오스 솔져 : 나이트메어 햇
	600,//ITEM_HAT_DRAGONSKULL00,//프리에스테스 : 발키리 서클렛 : 오딘 크라운
	//TOTAL_HAT,

	//두건 : //ITEM_CAP
	100,//ITEM_CAP_FEATHER = 000,//공작깃털 모자
	100,//ITEM_CAP_BEASTMANE00,//귀족의 머리띠
	200,//ITEM_CAP_EXPLORERHAT00,//거상의 모자 : 캐러벤 리더
	200,//ITEM_CAP_ACECAP00,//사냥꾼 모자 : 로빈훗 캡
	300,//ITEM_CAP_LIONMANE00,//투우사의 모자 : 미노타우르스
	400,//ITEM_CAP_GREAVE00,//해적의 모자 : 졸리로져 캡
	500,//ITEM_CAP_DEATH00,//에이스 캡 : 브레이브 캡 : 다이너스티 캡
	600,//ITEM_CAP_TROLLHEAD00,//드래곤 레어캡 : 히드라 헤드 : 리바이어선 캡
	//TOTAL_CAP,

	//갑옷 : //ITEM_ARMOR
	100,//ITEM_ARMOR_BRONZE = 000,//1//헌터 튜닉
	200,//ITEM_ARMOR_SCALE00,//6//미늘 갑옷
	300,//ITEM_ARMOR_BANDED00,//9//하프 플레이트 : 밴디트 메일
	300,//ITEM_ARMOR_SKULL00,//12//스컬 메일 : 마검사의 흉갑
	400,//ITEM_ARMOR_PLATE00,//15//황금세공 갑옷 : 드워븐 아머
	500,//ITEM_ARMOR_RUNIC00,//18//미스릴 아머 : 요정의 갑주
	600,//ITEM_ARMOR_MYTHRIL00,//21//고대의 갑옷 : 불멸의 갑주 : 브리건딘
	600,//ITEM_ARMOR_DRAGONSKIN00,//24//용비늘 갑옷 : 황룡의 갑옷 : 바하무트 아머
	//TOTAL_ARMOR,

	//조끼 : //ITEM_VEST
	100,//ITEM_VEST_WESTERN = 000,//카우보이 조끼
	100,//ITEM_VEST_LEOPARD00,//실크 조끼
	200,//ITEM_VEST_SILK00,//방랑자의 조끼 : 서바이벌 조끼
	200,//ITEM_VEST_PIRATE00,//도적의 조끼 : 어쌔신 베스트
	300,//ITEM_VEST_BALL00,//벨벳 셔츠 : 고딕 셔츠
	400,//ITEM_VEST_STAR00,//귀족의 조끼 : 은사슬 조끼
	500,//ITEM_VEST_SPATIOTEMPORAL00,//진홍빛 셔츠 : 불사의 셔츠 : 뱀파이어 로드
	600,//ITEM_VEST_QUEEN00,//신관의 로브 : 세라핌 로브 : 루시펠 로브
	//TOTAL_VEST,

	//코트 : //ITEM_COAT
	100,//ITEM_COAT_SIMPLE = 000,//수수한 코트
	100,//ITEM_COAT_PADDING00,//패딩 아머
	200,//ITEM_COAT_LEATHER00,//털가죽 코트 : 그리즐리 스킨
	200,//ITEM_COAT_CUREBOIL00,//큐어 보일 : 코아틀 스케일
	300,//ITEM_COAT_BEAST00,//귀족의 코트 : 흑까마귀 코트
	400,//ITEM_COAT_GRIZZLY00,//극지의 코트 : 블리자드 가드
	500,//ITEM_COAT_CROCODYLE00,//윙 코트 : 가고일 코트 : 페가수스 코트
	600,//ITEM_COAT_HYDRASCALE00,//바이스 코트 : 종말의 코트 : 카오스 엠페러
	//TOTAL_COAT,

	//건틀렛 : //ITEM_GUNTLET
	100,//ITEM_GUNTLET_IRON = 000,//1//핸드 가드
	200,//ITEM_GUNTLET_CHAIN00,//6//청동 장갑
	300,//ITEM_GUNTLET_MONSTER00,//9//체인 건틀렛 : 모험자의 장갑
	300,//ITEM_GUNTLET_KNIGHT00,//12//나이트 글로브 : 명성의 장갑
	400,//ITEM_GUNTLET_EAGLECLAW00,//15//비스트 핸드 : 오우거 건틀렛
	500,//ITEM_GUNTLET_SINE00,//18//라이징 건틀렛 : 무쌍의 장갑
	600,//ITEM_GUNTLET_JUSTICEHAND00,//21//광전사의 장갑 : 뇌격파수 : 시바의 손톱
	600,//ITEM_GUNTLET_HOLYHAND00,//24//드래곤 핸드 : 백룡의 장갑 : 바하무트 핸드
	//TOTAL_GUNTLET,

	//팔찌 : //ITEM_ARMLET
	100,//ITEM_ARMLET_LEATHER = 000,//사제의 묵주
	100,//ITEM_ARMLET_DESERT00,//여행자의 팔찌
	200,//ITEM_ARMLET_EXPLORER00,//백금 브레스렛 : 연인의 팔찌
	200,//ITEM_ARMLET_RAIDERS00,//전사의 암렛 : 임프 암렛
	300,//ITEM_ARMLET_NOBLESS00,//에메랄드 팔찌 : 노블레스 암렛
	400,//ITEM_ARMLET_DEVIL00,//이블 암렛 : 몽마의 팔찌
	500,//ITEM_ARMLET_DIGNITY00,//위엄의 팔찌 : 지배자의 팔찌 : 엠프레스 암렛
	600,//ITEM_ARMLET_HERO00,//영웅의 팔찌 : 소울 브레스렛 : 갓 핸드
	////TOTAL_ARMLET,

	//장갑 : //ITEM_GLOVE
	100,//ITEM_GLOVE_TRAVELER = 000,//여행자의 장갑
	100,//ITEM_GLOVE_DUALTIE00,//이중매듭 장갑
	200,//ITEM_GLOVE_LINEN00,//소매치기 장갑 : 섀도우 핸드
	200,//ITEM_GLOVE_RUNE00,//실크 글로브 : 귀공자의 장갑
	300,//ITEM_GLOVE_FAIRY00,//세공사의 장갑 : 마스터 글러브
	400,//ITEM_GLOVE_ROCKET00,//마법문양 장갑 : 커스드 글로브
	500,//ITEM_GLOVE_LACEMITTEN00,//심판의 손 : 구원의 손 : 이터널 져지
	600,//ITEM_GLOVE_GLORY00,//성자의 장갑 : 팔라딘 글로브 : 홀리 핸드
	//TOTAL_GLOVE,

	//킬트 : //ITEM_KILT
	100,//ITEM_KILT_CHAIN = 000,//1//밴딩 킬트
	200,//ITEM_KILT_DUALCHAIN00,//6//체인 킬트
	300,//ITEM_KILT_BATTLE00,//9//나이트 킬트 : 배틀 킬트
	300,//ITEM_KILT_NIGHTMARE00,//12//스컬 킬트 : 사령의 바지
	400,//ITEM_KILT_BATTLEFIELD00,//15//수령의 바지 : 토르의 바지
	500,//ITEM_KILT_DWARVEN00,//18//미스릴 킬트 : 페어리 킬트
	600,//ITEM_KILT_DURAHAN00,//21//에인션트 킬트 : 이터널 킬트 : 언리밋 킬트
	600,//ITEM_KILT_EARTHQUAKE00,//24//용수염 킬트 : 청룡의 킬트 : 용기사 바지
	//TOTAL_KILT,

	//바지 : //ITEM_SKIRT
	100,//ITEM_SKIRT_BROCADE = 000,//양단 스커트
	100,//ITEM_SKIRT_CARPSKIN00,//빈티지 스커트
	200,//ITEM_SKIRT_VELVET00,//단풍염색 치마 : 홍련의 스커트
	200,//ITEM_SKIRT_NOBLE00,//벨벳 스커트 : 소공녀의 치마
	300,//ITEM_SKIRT_GENERAL00,//폭풍의 스커트 : 무지개빛 치마
	400,//ITEM_SKIRT_GLORY00,//금실의 치마 : 여제의 스커트
	500,//ITEM_SKIRT_CHAOS00,//영광의 치마 : 현자의 치마 : 성령의 치마
	600,//ITEM_SKIRT_HERO00,//사제의 스커트 : 비슈누 스커트 : 태양의 스커트
	//TOTAL_SKIRT,

	//바지 : //ITEM_PANTS
	100,//ITEM_PANTS_RIDING = 000,//승마용 바지
	100,//ITEM_PANTS_VINTAGEJEAN00,//카프스킨 팬츠
	200,//ITEM_PANTS_BLAZE00,//망령의 팬츠 : 머미 밴디지
	200,//ITEM_PANTS_ASSASSIN00,//흑단의 바지 : 어쌔신 팬츠
	300,//ITEM_PANTS_TEMPEST00,//세일러 팬츠 : 제독의 바지
	400,//ITEM_PANTS_SCARLETLEGGINGS00,//데저트 팬츠 : 캐러밴 팬츠
	500,//ITEM_PANTS_HEAVEN00,//카오틱 팬츠 : 침묵의 바지 : 아비스 팬츠
	600,//ITEM_PANTS_SATANIC00,//가디안 팬츠 : 켈베로스 레더 : 아누비스 바지
	//TOTAL_PANTS,

	//장화 : //ITEM_GREAVES
	100,//ITEM_GREAVES_TRAINER = 000,//1//코퍼 그리브
	200,//ITEM_GREAVES_CHAIN00,//6//밴디트 그리브
	300,//ITEM_GREAVES_KNIGHT00,//9//체인 그리브 : 나이트 그리브
	300,//ITEM_GREAVES_FROZEN00,//12//프로즌 그리브 : 만년설의 신발
	400,//ITEM_GREAVES_GOLEM00,//15//플레이트 부츠 : 드워븐 그리브
	500,//ITEM_GREAVES_GIANT00,//18//빅풋 그리브 : 골렘 그리브
	600,//ITEM_GREAVES_GHOST00,//21//마검사의 신발 : 사령의 신발 : 종말의 발소리
	600,//ITEM_GREAVES_LEGEND00,//24//드래곤 그리브 : 마룡의 발자국 : 가이아 그리브
	//TOTAL_GREAVES,

	//신발 : //ITEM_SHOES
	100,//ITEM_SHOES_CLEAN = 000,//웨스턴 슈즈
	100,//ITEM_SHOES_CHASER00,//스웨이드 슈즈
	200,//ITEM_SHOES_LEATHER00,//라이딩 슈즈 : 밀리터리 워커
	200,//ITEM_SHOES_ROCKY00,//칠흑의 슈즈 : 마녀의 슈즈
	300,//ITEM_SHOES_CARVING00,//귀부인의 신발 : 로얄 셀레브
	400,//ITEM_SHOES_NETHERWORLD00,//리치 슈즈 : 팬텀 테일즈
	500,//ITEM_SHOES_INCARNATION00,//프리즘 슈즈 : 미라클 슈즈 : 그라비티 슈즈
	600,//ITEM_SHOES_HEAVENS00,//베이그란트 : 페이트 슈즈 : 데스티니 슈즈
	//TOTAL_SHOES,

	//부츠 : //ITEM_BOOTS
	100,//ITEM_BOOTS_SUEDE = 000,//스니커즈
	100,//ITEM_BOOTS_WESTERN00,//스캐빈저 부츠
	200,//ITEM_BOOTS_RIDING00,//천둥가죽 신발 : 낙뢰의 자국
	200,//ITEM_BOOTS_RICH00,//가드너 부츠 : 토렌트 루트
	300,//ITEM_BOOTS_OGRE00,//세일러 부츠 : 캡틴 부츠
	400,//ITEM_BOOTS_DARK00,//저승의 신발 : 헬 스트라이더
	500,//ITEM_BOOTS_MIRACLE00,//엘레멘탈 부츠 : 브리징 윈드 : 템페스트 부츠
	600,//ITEM_BOOTS_DESTINY00,//에어워커 : 클라우드 부츠 : 헤븐리 부츠
	//TOTAL_BOOTS,

	//목걸이 : //ITEM_NECK
	100,//ITEM_NECK0 = 000,//명예의 펜던트(0)
	100,//ITEM_NECK100,//연옥의 브로치(1)
	100,//ITEM_NECK200,//찰나의 팔찌(2)
	100,//ITEM_NECK300,//황금 바늘(3)
	200,//ITEM_NECK400,//파열의 팔찌(4)
	200,//ITEM_NECK500,//메피스토 피리(5)
	200,//ITEM_NECK600,//사멸의 하프(6)
	200,//ITEM_NECK700,//인어의 머리핀(7)
	300,//ITEM_NECK800,//찬트의 펜던트(8)
	300,//ITEM_NECK900,//미래의 거울(9)
	300,//ITEM_NECK1000,//피의 모래시계(10)
	300,//ITEM_NECK1100,//지옥의 만화경(11)
	400,//ITEM_NECK1200,//전능의 브로치(12)
	400,//ITEM_NECK1300,//생명의 보옥(13)
	400,//ITEM_NECK1400,//증식의 목걸이(14)
	400,//ITEM_NECK1500,//천공의 목걸이(15)
	500,//ITEM_NECK1600,//현자의 돌(16)
	500,//ITEM_NECK1700,//꿈의 오카리나(17) X
	500,//ITEM_NECK1800,//무한의 나침반(18) X
	500,//ITEM_NECK1900,//기억의 오르골(19) X
	600,//ITEM_NECK2000,//난쟁이의 공(20)
	600,//ITEM_NECK2100,//탐욕의 항아리(21)
	600,//ITEM_NECK2200,//팬더인형(22)
	600,//ITEM_NECK2300,//스마일 브로치(23)
	600,//ITEM_NECK2400,//토르테 악보(24)
	600,//ITEM_NECK2500,//용자의 시계(25)
	600,//ITEM_NECK2600,//악마의 뿔피리(26) X
	600,//ITEM_NECK2700,//아만디움 달걀(27) X
	//TOTAL_NECK,

	//목걸이 : //ITEM_RING
	100,//ITEM_RING0 = 0,	//사신의 반지(28)
	100,//ITEM_RING1,	//통찰의 반지(29)
	100,//ITEM_RING2,	//시공의 반지(30)
	200,//ITEM_RING3,	//해방의 반지(31)//|e사용시|i%d%%|j확률로 상태이상제거
	200,//ITEM_RING4,	//산호석 반지(32)
	200,//ITEM_RING5,	//생환의 반지(33)//|e사용시 |jHP |i%d |j회복
	300,//ITEM_RING6,	//희생의 반지(34)//|e사용시 |i%d%%|j확률로 추가타격
	300,//ITEM_RING7,	//폭주의 반지(35)
	300,//ITEM_RING8,	//골렘의 반지(36)
	400,//ITEM_RING9,	//광대의 반지(37)//|e사용시 |j회피 |i%d%%|j증가
	400,//ITEM_RING10,	//원한의 반지(38)//|e사용시|j관통공격확률|i%d%%|j증가
	400,//ITEM_RING11,	//신념의 반지(39)
	500,//ITEM_RING12,	//광포의 반지(40)
	500,//ITEM_RING13,	//승자의 반지(41)
	500,//ITEM_RING14,	//궁극의 반지(42)
	600,//ITEM_RING15,	//차원의 반지(43)//|e사용시 |j적방어도감소 -|i%d
	600,//ITEM_RING16,	//영화의 반지(44)
	600,//ITEM_RING17,	//행운의 반지(45)
	//TOTAL_RING,

	//보석 : ITEM_GEM
	100,//ITEM_GEM_RUBY = 0,	//루비(46)//PREFIX_FIRE_REGIST
	200,//ITEM_GEM_SAPPHIRE,	//사파이어(47)//PREFIX_FROST_REGIST
	300,//ITEM_GEM_AMETHYST,	//자수정(48)//PREFIX_THUNDER_REGIST
	400,//ITEM_GEM_DIAMOND,	//다이아몬드(49)//PREFIX_HOLY_REGIST
	500,//ITEM_GEM_PERL,	//진주(50)//PREFIX_DARK_REGIST
	600,//ITEM_GEM_EMERALD,	//에메랄드(51)//SUFFIX_ARMOR
	//TOTAL_GEM,

	//소모아이템 : ITEM_WASTE
	100,//ITEM_WASTE_RETURN = 0,	//귀환서(24)
	100,//ITEM_WASTE_STAR,				//별의 씨앗(52)
	200,//ITEM_WASTE_MOON,				//달의 씨앗(53)
	300,//ITEM_WASTE_SUN,					//태양의 씨앗(54) //골드 2배 이벤트
	100,//ITEM_WASTE_SILVER,				//은빛 허브(55)
	200,//ITEM_WASTE_GOLD,				//금빛 허브(56)
	300,//ITEM_WASTE_SCARLET,			//진홍빛 허브(57)
	100,//ITEM_WASTE_WATER,			//세계수의 물(58)
	100,//ITEM_WASTE_FLUTE,				//풀피리(5)
	100,//ITEM_WASTE_EYEWASH,		//안약(60)
	100,//ITEM_WASTE_ANTIDOTE,		//해독제(59)
	100,//ITEM_WASTE_WING,				//릴의 날개(62)
	100,//ITEM_WASTE_HOLYWATER,	//성수(61)
	100,//ITEM_WASTE_FIRESTONE,		//불의 정령석(63)
	100,//ITEM_WASTE_FROSTSTONE,	//물의 정령석(64)
	100,//ITEM_WASTE_THUNDERSTONE,	//번개의 정령석(65)
	100,//ITEM_WASTE_HOLYSTONE,					//빛의 정령석(66)
	100,//ITEM_WASTE_DARKSTONE,					//어둠의 정령석(67)
	200,//ITEM_WASTE_FIREELEMENTAL,			//화염의 정령석(46)
	200,//ITEM_WASTE_FROSTELEMENTAL,			//얼음의 정령석(47)
	200,//ITEM_WASTE_THUNDERELEMENTAL,	//천둥의 정령석(48)
	200,//ITEM_WASTE_HOLYELEMENTAL,			//섬광의 정령석(49)
	200,//ITEM_WASTE_DARKELEMENTAL,			//칠흑의 정령석(50)
	300,//ITEM_WASTE_DAMAGE,			//|e강화의 비약(207)
	300,//ITEM_WASTE_DEFENSE,			//|e인내의 비약(208)
	300,//ITEM_WASTE_MAGIC,				//|e치유의 비약(210)
	300,//ITEM_WASTE_SKILL,				//|e마법의 비약(209)
	//TOTAL_WASTE,

	//철계열 제작재료 : ITEM_IRON
	100,//ITEM_IRON_LV1 = 0,	//철광석(45개 : 68)
	100,//ITEM_IRON_LV2,	//은괴(39개 : 69)
	200,//ITEM_IRON_LV3,	//토륨 파편(39개 : 70)
	200,//ITEM_IRON_LV4,	//다마스커스(42개 : 71)
	300,//ITEM_IRON_LV5,	//아다만티움(39개 : 72)
	400,//ITEM_IRON_LV6,	//미스릴 결정(42개 : 73)
	500,//ITEM_IRON_LV7,	//오리하르콘(48개 : 74)
	600,//ITEM_IRON_LV8,	//이터늄 원석(30개 : 75)
	//TOTAL_IRON,

	//가죽계열 제작재료 : ITEM_LEATHER
	100,//ITEM_LEATHER_LV1 = 0,	//얇은 가죽(45개 : 76)
	100,//ITEM_LEATHER_LV2,	//반짝이는 비늘(39개 : 77)
	200,//ITEM_LEATHER_LV3,	//무쇠 가죽(39개 : 78)
	200,//ITEM_LEATHER_LV4,	//돌연변이 비늘(42개 : 79)
	300,//ITEM_LEATHER_LV5,	//달빛 가죽(39개 : 80)
	400,//ITEM_LEATHER_LV6,	//바실리스크 비늘(42개 : 81)
	500,//ITEM_LEATHER_LV7,	//지옥사자 가죽(48개 : 82)
	600,//ITEM_LEATHER_LV8,	//붉은 용비늘(30개 : 83)
	//TOTAL_LEATHER,

	//천계열 제작재료 : ITEM_CLOTH
	100,//ITEM_CLOTH_LV1 = 0,	//감색 실타래(44개 : 84)
	100,//ITEM_CLOTH_LV2,	//거미줄 옷감(41개 : 7)
	200,//ITEM_CLOTH_LV3,	//비단 실타래(40개 : 85)
	200,//ITEM_CLOTH_LV4,	//심연의 실타래(41개 : 86)
	300,//ITEM_CLOTH_LV5,	//은하수 옷감(40개 : 87)
	400,//ITEM_CLOTH_LV6,	//천고의 옷감(45개 : 88)
	500,//ITEM_CLOTH_LV7,	//공허의 실타래(45개 : 89)
	600,//ITEM_CLOTH_LV8,	//룬문자 옷감(28개 : 90)
	//TOTAL_CLOTH,

	//나무계열 제작재료 : ITEM_WOOD
	100,//ITEM_WOOD_LV1 = 0,	//벼락맞은 가지(60개 : 91)
	100,//ITEM_WOOD_LV2,	//얼어붙은 가지(29개 : 92)
	200,//ITEM_WOOD_LV3,	//맨드레이 뿌리(44개 : 93)
	200,//ITEM_WOOD_LV4,	//거인의 뿌리(37개 : 94)
	300,//ITEM_WOOD_LV5,	//저주받은 뿌리(44개 : 95)
	400,//ITEM_WOOD_LV6,	//고대의 가지(37개 : 96)
	500,//ITEM_WOOD_LV7,	//지옥의 뿌리(53개 : 97)
	600,//ITEM_WOOD_LV8,	//세계수의 가지(20개 : 98)
	//TOTAL_WOOD,

	//특수재료 : ITEM_ESSENCE
	100,//ITEM_ESSENCE0 = 0,	//단단한 껍질(9개 : 99)
	100,//ITEM_ESSENCE1,	//오염된 넝쿨(9개 : 100)
	100,//ITEM_ESSENCE2,	//심연의 눈동자(7개 : 20)
	100,//ITEM_ESSENCE3,	//저주받은 해골(11개 : 101)
	100,//ITEM_ESSENCE4,	//푸른 비늘(9개 : 102)
	100,//ITEM_ESSENCE5,	//반짝이는 심장(9개 : 103)
	100,//ITEM_ESSENCE6,	//야생의 돌(18개 : 104)
	100,//ITEM_ESSENCE7,	//갈라진 어금니(18개 : 105)
	100,//ITEM_ESSENCE8,	//염의 증류수(9개 : 21)
	100,//ITEM_ESSENCE9,	//빛의 깃털(9개 : 106)
	100,//ITEM_ESSENCE10,	//질풍의 조각(12개 : 107)
	100,//ITEM_ESSENCE11,	//눈의 결정(12개 : 8)
	100,//ITEM_ESSENCE12,	//결빙의 옥루(12개 : 108)
	100,//ITEM_ESSENCE13,	//우레 가루(6개 : 109)
	100,//ITEM_ESSENCE14,	//뇌문의 쐐기(6개 : 110)
	100,//ITEM_ESSENCE15,	//마력의 구슬(6개 : 13)
	100,//ITEM_ESSENCE16,	//요정의 눈물(27개 : 61)
	100,//ITEM_ESSENCE17,	//광휘의 염료(27개 : 111)
	100,//ITEM_ESSENCE18,	//용맹의 증표(9개 : 56)
	100,//ITEM_ESSENCE19,	//슬라임 윤활액(9개 : 59)
	100,//ITEM_ESSENCE20,	//혼미의 영석(9개 : 128)
	100,//ITEM_ESSENCE21,	//월석 파편(9개 : 113)
	100,//ITEM_ESSENCE22,	//영혼의 꼬리(9개 : 114)
	100,//ITEM_ESSENCE23,	//농염의 십자가(9개 : 115)
	100,//ITEM_ESSENCE24,	//황천의 보주(9개 : 0)
	100,//ITEM_ESSENCE25,	//유혹의 향료(9개 : 116)
	100,//ITEM_ESSENCE26,	//만고의 뿔(18개 : 117)
	100,//ITEM_ESSENCE27,	//전능의 수정(18개 : 16)
	100,//ITEM_ESSENCE28,	//은하수 날개(9개 : 118)
	100,//ITEM_ESSENCE29,	//뫼비우스의 띠(9개 : 119)
	100,//ITEM_ESSENCE30,	//영원의 상(9개 : 1)
	100,//ITEM_ESSENCE31,	//노스 제왕석(9개 : 27)
	100,//ITEM_ESSENCE32,	//포비든 스톤(18개 : 120)
	100,//ITEM_ESSENCE33,	//묘지의 반딧불(9개 : 121)
	100,//ITEM_ESSENCE34,	//지배의 삼지창(9개 : 122)
	100,//ITEM_ESSENCE35,	//엠페러 스톤(18개 : 123)
	100,//ITEM_ESSENCE36,	//볼케이노 잼(18개 : 124)
	100,//ITEM_ESSENCE37,	//프로즌 셸(18개 : 125)
	100,//ITEM_ESSENCE38,	//인피니티 볼트(18개 : 126)
	100,//ITEM_ESSENCE39,	//다즐링 램프(6개 : 18)
	100,//ITEM_ESSENCE40,	//가공된 마석(6개 : 17)
	100,//ITEM_ESSENCE41,	//황천의 닻(6개 : 127)
	100,//ITEM_ESSENCE42,	//금단의 과실(6개 : 128)
	100,//ITEM_ESSENCE43,	//적룡의 숨결(6개 : 129)
	100,//ITEM_ESSENCE44,	//원혼의 결정(6개 : 19)
	//TOTAL_ESSENCE,

	//퀘스트 아이템 : ITEM_QUEST
	100,//ITEM_QUEST_MUSHROOM = 0,	100,//눅눅한 버섯(112)
	100,//ITEM_QUEST_GOLD,	100,//마일즈의 돈주머니(179)
	100,//ITEM_QUEST_ARMLET,	100,//마일즈의 팔찌(2)
	100,//ITEM_QUEST_DARKPIECE,	100,//어둠의 파편(159)
	100,//ITEM_QUEST_REEF,	100,//산호초(187)
	100,//ITEM_QUEST_GOLDBAR,	100,//황금(160)
	100,//ITEM_QUEST_AMULET,	100,//어둠의 아뮬렛(161)
	100,//ITEM_QUEST_GHOST,	100,//유령옷(188)
	100,//ITEM_QUEST_SCRIPT,	100,//리클루즈의 원고(24)
	100,//ITEM_QUEST_FUND,	100,//네이의 돈주머니(191)
	100,//ITEM_QUEST_FRUIT,	100,//홍염의 과실(189)
	100,//ITEM_QUEST_BIOGRAPHY,	100,//바리스 영웅전(190)
	100,//ITEM_QUEST_FANLETTER,	100,//펜레터(190)
	100,//ITEM_QUEST_NUMMARK,		100,//번호표(190)
	100,//ITEM_QUEST_LETTER,		100,//그을린 편지(191)
	100,//ITEM_QUEST_TRAINER,	100,//조련사의 편지(191)
	100,//ITEM_QUEST_COMPASS,	100,//시간의 나침반(197)
	100,//ITEM_QUEST_SECRET,	100,//기밀 문서(24)
	100,//ITEM_QUEST_SECRET2,	100,//크풀레의 밀서(191)
	100,//ITEM_QUEST_LETTER2,	100,//다리안의 편지(191)
	100,//ITEM_QUEST_INVITATION,	100,//초대장(191)
	100,//ITEM_QUEST_DRUID,	100,//드루이드의 편지(191)
	100,//ITEM_QUEST_GRANDMA,	100,//할머니의 편지(191)
	100,//ITEM_QUEST_KATHERINE,	100,//캐서린의 반지(28)
	100,//ITEM_QUEST_TREASUREMAP,	100,//보물지도(181)
	100,//ITEM_QUEST_REDHEART,	100,//작열의 소울(192)
	100,//ITEM_QUEST_BLUEHEART,	100,//결빙의 소울(193)
	100,//ITEM_QUEST_THUNDERHEART,	100,//전격의 소울(194)
	100,//ITEM_QUEST_HOLYHEART,	100,//위광의 소울(195)
	100,//ITEM_QUEST_DARKHEART,	100,//암흑의 소울(196)
	100,//ITEM_QUEST_FLOWER,	100,//꽃(198)
	100,//ITEM_QUEST_SNOWFLOWER,	100,//백설화 가지(92)
	100,//ITEM_QUEST_MAP_TOTALCOMPLETE,	100,//완벽한 지도(190)
	100,//ITEM_QUEST_MAP,	100,//지도(181)
	100,//ITEM_QUEST_MAP_COMPLETE,	100,//완성된 지도(182)
	//TOTAL_QUESTITEM,

	//유료아이템 : ITEM_NETITEM
	500,//ITEM_NET_COUPON = 0,	//쿠폰(200)	//-1
	500,//ITEM_NET_TICKET,	//입장권(201)	//-1
	500,//ITEM_NET_ENCHANT,	500,//강화석(202)	500,//-1
	500,//ITEM_NET_PROTECT,	500,//보호석(203)	500,//-1
	500,//ITEM_NET_RECIPE,		500,//조합석(204)	500,//-1
	500,//ITEM_NET_RESOLUTION,	500,//분해석(205)	500,//-1
	500,//ITEM_NET_SOCKET,	500,//소켓석(206)	500,//-1
	500,//ITEM_NET_CHARACTER,	500,//캐릭터(167)	500,//-1
	500,//ITEM_NET_RESURRECTION,	500,//부활약(166)	500,//-1
	500,//ITEM_NET_BOX_WEAPON_HIGH, 500,//고급무기상자(168)	500,//BOX_H2
	500,//ITEM_NET_BOX_WEAPON_MID, 500,//중급무기상자(169)	500,//BOX_H1
	500,//ITEM_NET_BOX_WEAPON_LOW, 500,//하급무기상자(170)	500,//BOX_H1
	500,//ITEM_NET_BOX_DEFENSE_HIGH, 500,//고급방어구상자(171)	500,//BOX_H2
	500,//ITEM_NET_BOX_DEFENSE_MID, 500,//중급방어구상자(172)	500,//BOX_H1
	500,//ITEM_NET_BOX_DEFENSE_LOW, 500,//하급방어구상자(173)	500,//BOX_H1
	500,//ITEM_NET_BOX_ACCESSORY_HIGH, 500,//고급악세사리상자(174)	500,//BOX_H2
	500,//ITEM_NET_BOX_ACCESSORY_MID, 500,//중급악세사리상자(175)	500,//BOX_H1
	500,//ITEM_NET_BOX_ACCESSORY_LOW, 500,//하급악세사리상자(176)	500,//BOX_H1
	500,//ITEM_NET_BOX_RANDOM,	500,//랜덤아이템상자(177)	500,//BOX_CHEST1500,//클릭하면 아이템이 나오는 상자. 골드 
	500,//ITEM_NET_BOX_GEM,	500,//고급보석(178)	500,//BOX_S5
	500,//ITEM_NET_SINGLEBAG,	500,//가방(162)	500,//-1
	500,//ITEM_NET_NETBAG,	500,//창고가방(163)	500,//-1
	500,//ITEM_NET_APRESET,	500,//AP초기화(164)	500,//-1
	500,//ITEM_NET_SPRESET,	500,//SP초기화(165)	500,//-1
	500,//ITEM_NET_PACKAGE_NEWBIE,	500,//초심자 스페셜(211)	500,//BOX_S1
	500,//ITEM_NET_PACKAGE_ENCHANT,	500,//슈퍼강화패키지(212)	500,//BOX_S2
	500,//ITEM_NET_PACKAGE_STONE,	500,//스톤패키지(213)	500,//BOX_S3
	500,//ITEM_NET_PACKAGE_ARENA,	500,//투기장 패키지(214)	500,//BOX_S4
	500,//ITEM_NET_PACKAGE_LUCK,	500,//행운 패키지(215)	500,//BOX_S5
	500,//ITEM_NET_EXPORB,	//EXP획득(180)	//-1

	//TOTAL_NETITEM,

	100,//ITEM_GOLD

	//키아이템 : ITEM_KEY
	100,//ITEM_KEY0 = 0,	//금단의 계곡 열쇠(146)
	100,//ITEM_KEY1,	//어둠의 파편 열쇠(147)
	100,//ITEM_KEY2,	//푸른비늘 열쇠(148)
	200,//ITEM_KEY3,	//차원의 열쇠(149)
	200,//ITEM_KEY4,	//얼음의 정령 열쇠(150)
	200,//ITEM_KEY5,	//번개의 정령 열쇠(151)
	300,//ITEM_KEY6,	//빛의 정령 열쇠(152)
	300,//ITEM_KEY7,	//지하수로 열쇠(153)
	300,//ITEM_KEY8,	//골렘 열쇠(154)
	400,//ITEM_KEY9,	//어둠의 열쇠(155)
	400,//ITEM_KEY10,	//드래곤의 무덤 열쇠(156)
	400,//ITEM_KEY11,	//망자의 도시 열쇠(157)
	500,//ITEM_KEY12,	//마왕성의 열쇠(158)
	500,//ITEM_KEY13,	//왕가의 펜던트(15)
	500,//ITEM_KEY14,	//근성의 허리띠(183)
	600,//ITEM_KEY15,	//신기루의 목걸이(184)
	600,//ITEM_KEY16,	//오우거의 장갑(185)
	//TOTAL_KEYITEM,

	//상 : ITEM_STATUE
	100,//ITEM_STATUE_WIND = 0,	//질풍의 상(130)
	100,//ITEM_STATUE_DESTRUCT,	//파괴의 상(131)
	100,//ITEM_STATUE_POWER,		//완력의 상(132)
	200,//ITEM_STATUE_MERMAID,	//인어의 상(133)
	200,//ITEM_STATUE_FLAME,		//불꽃의 상(134)
	200,//ITEM_STATUE_PENGUIN,		//펭귄의 상(135)
	300,//ITEM_STATUE_ICE,				//얼음의 상(136)
	300,//ITEM_STATUE_THUNDER,	//번개의 상(137)
	300,//ITEM_STATUE_SUN,			//태양의 상(138)
	400,//ITEM_STATUE_RABBIT,		//토끼의 상(139)
	400,//ITEM_STATUE_GOLEM,		//골렘의 상(140)
	400,//ITEM_STATUE_DIMENSION,	//차원의 상(141)
	500,//ITEM_STATUE_EAGLE,		//독수리의 상(142)
	500,//ITEM_STATUE_SQUIRREL,	//다람쥐의 상(143)
	500,//ITEM_STATUE_DRAGON,		//드래곤의 상(144)
	600,//ITEM_STATUE_SPIRIT,		//진공의 상(145)
	//TOTAL_STATUE,

	500,//ITEM_HEART
	500,//ITEM_MEDAL
	500,//ITEM_STAR
	300,//ITEM_HAMMER
	200,//ITEM_SHIELD

	//상자아이템 : ITEM_BOX
	//일단 고려해야 되는 것이 상점에서 파는 랜덤상자의 정체는?
	//장비를 처음부터 다 깔아줄건가
	//아니면 칼을 
	100,//BOX_INGAME = 0,
	
	100,//BOX_CASTLE0,
	100,//BOX_CASTLE1,
	100,//BOX_CASTLE2,
	100,//BOX_CASTLE3,
	200,//BOX_CASTLE4,
	200,//BOX_CASTLE5,
	200,//BOX_CASTLE6,
	200,//BOX_CASTLE7,
	300,//BOX_CASTLE8,
	300,//BOX_CASTLE9,
	300,//BOX_CASTLE10,
	300,//BOX_CASTLE11,
	400,//BOX_CASTLE12,
	400,//BOX_CASTLE13,
	400,//BOX_CASTLE14,
	400,//BOX_CASTLE15,
	500,//BOX_CASTLE16,
	500,//BOX_CASTLE17,
	500,//BOX_CASTLE18,

	100,//BOX_REWARD0,
	200,//BOX_REWARD1,
	300,//BOX_REWARD2,
	400,//BOX_REWARD3,
	500,//BOX_REWARD4,
	600,//BOX_REWARD5,
	700,//BOX_REWARD6,
	800,//BOX_REWARD7,


	//TOTAL_BOX,

	//동료들 : ITEM_CREW
	100,//ITEM_CREW_1 = 0,
	100,//ITEM_CREW_2,
	100,//ITEM_CREW_3,
	100,//ITEM_CREW_4,
	100,//ITEM_CREW_5,
	100,//ITEM_CREW_6,
	100,//ITEM_CREW_7,
	100,//ITEM_CREW_8,
	100,//ITEM_CREW_9,
	100,//ITEM_CREW_10,
	200,//ITEM_CREW_11,
	200,//ITEM_CREW_12,
	200,//ITEM_CREW_13,
	200,//ITEM_CREW_14,
	200,//ITEM_CREW_15,
	200,//ITEM_CREW_16,
	200,//ITEM_CREW_17,
	200,//ITEM_CREW_18,
	200,//ITEM_CREW_19,
	200,//ITEM_CREW_20,
	300,//ITEM_CREW_21,
	300,//ITEM_CREW_22,
	300,//ITEM_CREW_23,
	300,//ITEM_CREW_24,
	300,//ITEM_CREW_25,
	300,//ITEM_CREW_26,
	300,//ITEM_CREW_27,
	300,//ITEM_CREW_28,
	300,//ITEM_CREW_29,
	300,//ITEM_CREW_30,
	400,//ITEM_CREW_31,
	400,//ITEM_CREW_32,
	400,//ITEM_CREW_33,
	400,//ITEM_CREW_34,
	400,//ITEM_CREW_35,
	400,//ITEM_CREW_36,
	400,//ITEM_CREW_37,
	400,//ITEM_CREW_38,
	400,//ITEM_CREW_39,
	400,//ITEM_CREW_40,
	500,//ITEM_CREW_41,
	500,//ITEM_CREW_42,
	500,//ITEM_CREW_43,
	500,//ITEM_CREW_44,
	500,//ITEM_CREW_45,
	500,//ITEM_CREW_46,
	500,//ITEM_CREW_47,
	500,//ITEM_CREW_48,
	500,//ITEM_CREW_49,
	500,//ITEM_CREW_50,
	600,//ITEM_CREW_51,
	600,//ITEM_CREW_52,
	600,//ITEM_CREW_53,
	600,//ITEM_CREW_54,
	600,//ITEM_CREW_55,
	600,//ITEM_CREW_56,
	600,//ITEM_CREW_57,
	600,//ITEM_CREW_58,
	600,//ITEM_CREW_59,
	600,//ITEM_CREW_60,
	600,//ITEM_CREW_61,
	600,//ITEM_CREW_62,
	600,//ITEM_CREW_63,
	600,//ITEM_CREW_64,
	600,//ITEM_CREW_65,
	600,//ITEM_CREW_66,
	600,//ITEM_CREW_67,
	600,//ITEM_CREW_68,
	600,//ITEM_CREW_69,
	600,//ITEM_CREW_70,
	600,//ITEM_CREW_71,
	600,//ITEM_CREW_72,
	600,//ITEM_CREW_73,
	600,//ITEM_CREW_74,
	600,//ITEM_CREW_75,
	600,//ITEM_CREW_76,
	600,//ITEM_CREW_77,
	600,//ITEM_CREW_78,
	600,//ITEM_CREW_79,
	600,//ITEM_CREW_80,
	600,//ITEM_CREW_81,
	600,//ITEM_CREW_82,
	600,//ITEM_CREW_83,
	600,//ITEM_CREW_84,
	600,//ITEM_CREW_85,
	600,//ITEM_CREW_86,
	600,//ITEM_CREW_87,
	600,//ITEM_CREW_88,
	600,//ITEM_CREW_89,
	600,//ITEM_CREW_90,
	600,//ITEM_CREW_91,
	600,//ITEM_CREW_92,
	600,//ITEM_CREW_93,
	600,//ITEM_CREW_94,
	600,//ITEM_CREW_95,
	600,//ITEM_CREW_96,
	600,//ITEM_CREW_97,
	600,//ITEM_CREW_98,
	600,//ITEM_CREW_99,
	600,//ITEM_CREW_100,

	//TOTAL_CREW,
};
static const unsigned short itemStartCnt_builtin[] = {
	ITEM_SWORD_START,
	ITEM_GUN_START,
	ITEM_BOOMERANG_START,
	ITEM_HELM_START,
	ITEM_HAT_START,
	ITEM_CAP_START,
	ITEM_ARMOR_START,
	ITEM_VEST_START,
	ITEM_COAT_START,
	ITEM_GUNTLET_START,
	ITEM_ARMLET_START,
	ITEM_GLOVE_START,
	ITEM_KILT_START,
	ITEM_SKIRT_START,
	ITEM_PANTS_START,
	ITEM_GREAVES_START,
	ITEM_SHOES_START,
	ITEM_BOOTS_START,
	ITEM_NECK_START,
	ITEM_RING_START,
	ITEM_GEM_START,
	ITEM_WASTES_START,
	ITEM_IRON_START,
	ITEM_LEATHER_START,
	ITEM_CLOTH_START,
	ITEM_WOOD_START,
	ITEM_ESSENCE_START,
	ITEM_RECIPE_START,
	ITEM_QUEST_START,
	ITEM_NETITEM_START,
	ITEM_GOLD_START,
	ITEM_KEY_START,
	ITEM_STATUE_START,
	ITEM_HEART_START,
	ITEM_MEDAL_START,
	ITEM_STAR_START,
	ITEM_HAMMER_START,
	ITEM_SHIELD_START,
	ITEM_BOX_START,
	ITEM_CREW_START,
	ITEM_SKILL_START,
};
static const unsigned char boxEquipType_builtin[] = {
	ITEM_SWORD,//1
	ITEM_HELM,//2
	ITEM_ARMOR,//3
	ITEM_GUNTLET,//4
	ITEM_KILT,//5
	ITEM_GREAVES,//6
	ITEM_NECK,//7
	ITEM_RING,//8
};
static const unsigned char materialDropData_builtin[] = {
	50 + ITEM_LEATHER_LV1, 40, ITEM_IRON_LV1, 40, 200 + ITEM_ESSENCE0, 20,	//가시껍질 달팽이
	150 + ITEM_WOOD_LV1, 40, 100 + ITEM_CLOTH_LV1, 40, 200 + ITEM_ESSENCE1, 20,	//늪의 주인
	100 + ITEM_CLOTH_LV2, 40, 50 + ITEM_LEATHER_LV2, 40, 200 + ITEM_ESSENCE2, 20,	//아이볼
	150 + ITEM_WOOD_LV2, 40, ITEM_IRON_LV2, 40, 200 + ITEM_ESSENCE3, 20,	//칠흑의 기사
	ITEM_IRON_LV3, 40, 50 + ITEM_LEATHER_LV3, 40, 200 + ITEM_ESSENCE4, 20,	//사하긴 병사
	100 + ITEM_CLOTH_LV3, 40, 150 + ITEM_WOOD_LV3, 40, 200 + ITEM_ESSENCE5, 20,	//맹독 해파리
	ITEM_IRON_LV3, 40, 50 + ITEM_LEATHER_LV3, 40, 200 + ITEM_ESSENCE18, 20,	//타락한 기사
	100 + ITEM_CLOTH_LV3, 40, 150 + ITEM_WOOD_LV3, 40, 200 + ITEM_ESSENCE19, 20,	//슬라임
	ITEM_IRON_LV3, 40, 50 + ITEM_LEATHER_LV3, 40, 200 + ITEM_ESSENCE6, 20,	//평원의 도적
	100 + ITEM_CLOTH_LV3, 40, 150 + ITEM_WOOD_LV3, 40, 200 + ITEM_ESSENCE7, 20,	//거친발 멧돼지
	ITEM_IRON_LV4, 40, 50 + ITEM_LEATHER_LV4, 40, 200 + ITEM_ESSENCE8, 20,	//분노의 정령
	100 + ITEM_CLOTH_LV4, 40, 150 + ITEM_WOOD_LV4, 40, 200 + ITEM_ESSENCE9, 20,	//마성의 불새
	ITEM_IRON_LV4, 40, 50 + ITEM_LEATHER_LV4, 40, 200 + ITEM_ESSENCE10, 20,	//결빙의 석상
	100 + ITEM_CLOTH_LV4, 40, 150 + ITEM_WOOD_LV4, 40, 200 + ITEM_ESSENCE11, 20,	//스노우맨
	ITEM_IRON_LV4, 40, 50 + ITEM_LEATHER_LV4, 40, 200 + ITEM_ESSENCE12, 20,	//아이스 마스크
	ITEM_IRON_LV5, 40, 100 + ITEM_CLOTH_LV5, 40, 200 + ITEM_ESSENCE13, 20,	//스파크
	50 + ITEM_LEATHER_LV5, 40, 150 + ITEM_WOOD_LV5, 40, 200 + ITEM_ESSENCE14, 20,	//다크미스트
	ITEM_IRON_LV5, 40, 100 + ITEM_CLOTH_LV5, 40, 200 + ITEM_ESSENCE15, 20,	//스파크 플랜트
	ITEM_IRON_LV5, 40, 100 + ITEM_CLOTH_LV5, 40, 200 + ITEM_ESSENCE16, 20,	//라이트 스피릿
	50 + ITEM_LEATHER_LV5, 40, 150 + ITEM_WOOD_LV5, 40, 200 + ITEM_ESSENCE17, 20,	//딜루젼소울
	50 + ITEM_LEATHER_LV6, 40, 100 + ITEM_CLOTH_LV6, 40, 200 + ITEM_ESSENCE20, 20,	//스트라이더
	ITEM_IRON_LV6, 40, 150 + ITEM_WOOD_LV6, 40, 200 + ITEM_ESSENCE21, 20,	//주인잃은 골렘
	ITEM_IRON_LV6, 40, 50 + ITEM_LEATHER_LV6, 40, 200 + ITEM_ESSENCE24, 20,	//그레이트 아머
	100 + ITEM_CLOTH_LV6, 40, 150 + ITEM_WOOD_LV6, 40, 200 + ITEM_ESSENCE25, 20,	//우로보로스
	ITEM_IRON_LV7, 40, 50 + ITEM_LEATHER_LV7, 40, 200 + ITEM_ESSENCE26, 20,	//탐욕의 살육자
	100 + ITEM_CLOTH_LV7, 40, 150 + ITEM_WOOD_LV7, 40, 200 + ITEM_ESSENCE27, 20,	//드래곤 좀비
	ITEM_IRON_LV7, 40, 50 + ITEM_LEATHER_LV7, 40, 200 + ITEM_ESSENCE22, 20,	//떠도는 영혼
	100 + ITEM_CLOTH_LV7, 40, 150 + ITEM_WOOD_LV7, 40, 200 + ITEM_ESSENCE23, 20,	//무혼의 기사
	50 + ITEM_LEATHER_LV8, 40, 100 + ITEM_CLOTH_LV8, 40, 200 + ITEM_ESSENCE28, 20,	//공허한 갑주
	ITEM_IRON_LV8, 40, 150 + ITEM_WOOD_LV8, 40, 200 + ITEM_ESSENCE29, 20,	//어둠의 마도사
	50 + ITEM_LEATHER_LV8, 40, 150 + ITEM_WOOD_LV8, 40, 200 + ITEM_ESSENCE30, 20,	//우주1
	ITEM_IRON_LV8, 40, 100 + ITEM_CLOTH_LV8, 40, 200 + ITEM_ESSENCE31, 20,	//우주2
	200 + ITEM_ESSENCE0, 5, 200 + ITEM_ESSENCE1, 5, 200 + ITEM_ESSENCE32, 90,	//토드뮤턴트
	200 + ITEM_ESSENCE3, 5, 200 + ITEM_ESSENCE4, 5, 200 + ITEM_ESSENCE33, 90,	//아르곤
	200 + ITEM_ESSENCE4, 5, 200 + ITEM_ESSENCE5, 5, 200 + ITEM_ESSENCE34, 90,	//카툼
	200 + ITEM_ESSENCE6, 5, 200 + ITEM_ESSENCE7, 5, 200 + ITEM_ESSENCE35, 90,	//고대의 수호자
	200 + ITEM_ESSENCE8, 5, 200 + ITEM_ESSENCE9, 5, 200 + ITEM_ESSENCE36, 90,	//이프리트
	200 + ITEM_ESSENCE10, 5, 200 + ITEM_ESSENCE11, 5, 200 + ITEM_ESSENCE37, 90,	//프로스트
	200 + ITEM_ESSENCE14, 5, 200 + ITEM_ESSENCE15, 5, 200 + ITEM_ESSENCE38, 90,	//라이오너
	200 + ITEM_ESSENCE16, 5, 200 + ITEM_ESSENCE17, 5, 200 + ITEM_ESSENCE39, 90,	//호루스
	200 + ITEM_ESSENCE18, 5, 200 + ITEM_ESSENCE19, 5, 200 + ITEM_ESSENCE40, 90,	//마도합성수
	200 + ITEM_ESSENCE20, 5, 200 + ITEM_ESSENCE21, 5, 200 + ITEM_ESSENCE41, 90,	//고대의 방주
	200 + ITEM_ESSENCE24, 5, 200 + ITEM_ESSENCE25, 5, 200 + ITEM_ESSENCE42, 90,	//아리만
	200 + ITEM_ESSENCE26, 5, 200 + ITEM_ESSENCE27, 5, 200 + ITEM_ESSENCE43, 90,	//바하무트
	200 + ITEM_ESSENCE22, 5, 200 + ITEM_ESSENCE23, 5, 200 + ITEM_ESSENCE44, 90,	//죽음의 신
};
static const unsigned char wasteDropData_builtin[] = {
	17, 27, 6, 1, 15, 3, 1, 0, 3, 3, 3, 3, 3, 3, 0, 2, 1, 3, 0, 3, 0, 2, 1, 0, 0, 0, 0, //가시껍질 달팽이
	17, 27, 6, 1, 15, 3, 1, 0, 3, 3, 3, 3, 3, 3, 0, 3, 0, 2, 1, 2, 1, 3, 0, 0, 0, 0, 0, //늪의 주인
	17, 27, 6, 1, 15, 3, 1, 0, 3, 3, 3, 3, 3, 3, 0, 2, 1, 3, 0, 3, 0, 3, 0, 0, 0, 0, 0, //아이볼
	17, 27, 6, 1, 15, 3, 1, 0, 3, 3, 3, 3, 3, 2, 1, 3, 0, 3, 0, 3, 0, 3, 0, 0, 0, 0, 0, //칠흑의 기사
	17, 27, 6, 1, 15, 3, 1, 0, 3, 3, 3, 3, 3, 3, 0, 2, 1, 3, 0, 3, 0, 3, 0, 0, 0, 0, 0, //멀록
	17, 27, 6, 1, 15, 3, 1, 0, 3, 3, 3, 3, 3, 3, 0, 3, 0, 2, 1, 3, 0, 3, 0, 0, 0, 0, 0, //맹독 해파리
	17, 27, 6, 1, 15, 3, 1, 0, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3, 0, 3, 0, 2, 1, 0, 0, 0, 0, //타락한 기사
	17, 27, 6, 1, 15, 3, 1, 0, 3, 3, 3, 3, 3, 2, 1, 3, 0, 3, 0, 3, 0, 3, 0, 0, 0, 0, 0, //슬라임
	17, 27, 6, 1, 15, 3, 1, 0, 3, 3, 3, 3, 3, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 0, 0, 0, //사냥꾼 연합
	17, 27, 6, 1, 15, 3, 1, 0, 3, 3, 3, 3, 3, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 0, 0, 0, //거친발 멧돼지
	17, 10, 20, 4, 6, 11, 2, 0, 3, 3, 3, 3, 3, 8, 3, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, //요예의 불꽃
	17, 10, 20, 4, 6, 11, 2, 0, 3, 3, 3, 3, 3, 8, 3, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, //불멸의 화조
	17, 10, 20, 4, 6, 11, 2, 0, 3, 3, 3, 3, 3, 0, 1, 8, 3, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, //웬투스
	17, 10, 20, 4, 6, 11, 2, 0, 3, 3, 3, 3, 3, 0, 1, 8, 3, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, //스노우 텀블
	17, 10, 20, 4, 6, 11, 2, 0, 3, 3, 3, 3, 3, 0, 1, 8, 3, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, //엘리오스
	17, 10, 20, 4, 6, 11, 2, 0, 3, 3, 3, 3, 3, 0, 1, 0, 1, 3, 8, 0, 1, 0, 1, 0, 0, 0, 0, //럼블 썬더
	17, 10, 20, 4, 6, 11, 2, 0, 3, 3, 3, 3, 3, 0, 1, 0, 1, 3, 8, 0, 1, 0, 1, 0, 0, 0, 0, //미스트
	17, 10, 20, 4, 6, 11, 2, 0, 3, 3, 3, 3, 3, 0, 1, 0, 1, 3, 8, 0, 1, 0, 1, 0, 0, 0, 0, //언리밋 코어
	17, 10, 20, 4, 6, 11, 2, 0, 3, 3, 3, 3, 3, 0, 1, 0, 1, 0, 1, 3, 8, 0, 1, 0, 0, 0, 0, //페어리
	17, 10, 20, 4, 6, 11, 2, 0, 3, 3, 3, 3, 3, 0, 1, 0, 1, 0, 1, 3, 8, 0, 1, 0, 0, 0, 0, //다가즈
	17, 2, 11, 20, 2, 5, 11, 2, 3, 3, 3, 3, 3, 0, 3, 0, 3, 1, 2, 0, 3, 0, 3, 0, 0, 0, 0, //노블 스파이더
	17, 2, 11, 20, 2, 5, 11, 2, 3, 3, 3, 3, 3, 0, 3, 0, 3, 0, 3, 1, 2, 0, 3, 0, 0, 0, 0, //달빛 골램
	17, 2, 11, 20, 2, 5, 11, 2, 3, 3, 3, 3, 3, 0, 1, 0, 1, 0, 1, 0, 1, 9, 2, 0, 0, 0, 0, //의지의 갑주
	17, 2, 11, 20, 2, 5, 11, 2, 3, 3, 3, 3, 3, 0, 1, 0, 1, 0, 1, 0, 1, 9, 2, 0, 0, 0, 0, //라미아
	17, 2, 9, 19, 2, 5, 11, 5, 3, 3, 3, 3, 3, 2, 1, 3, 0, 3, 0, 3, 0, 3, 0, 0, 0, 0, 0, //드래곤1
	17, 2, 9, 19, 2, 5, 11, 5, 3, 3, 3, 3, 3, 3, 0, 2, 1, 3, 0, 3, 0, 3, 0, 0, 0, 0, 0, //드래곤2
	17, 2, 9, 19, 2, 5, 11, 5, 3, 3, 3, 3, 3, 3, 0, 3, 0, 2, 1, 3, 0, 3, 0, 0, 0, 0, 0, //어둠의 그림자
	17, 2, 9, 19, 2, 5, 11, 5, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3, 0, 2, 1, 3, 0, 0, 0, 0, 0, //무혼의 기사
	17, 1, 2, 28, 1, 2, 12, 7, 3, 3, 3, 3, 3, 3, 0, 3, 0, 3, 0, 3, 0, 2, 1, 0, 0, 0, 0, //마왕1
	17, 1, 2, 28, 1, 2, 12, 7, 3, 3, 3, 3, 3, 2, 1, 3, 0, 3, 0, 3, 0, 3, 0, 0, 0, 0, 0, //마왕2
	17, 1, 2, 28, 1, 2, 12, 7, 3, 3, 3, 3, 3, 3, 0, 2, 1, 3, 0, 3, 0, 3, 0, 0, 0, 0, 0, //우주1
	17, 1, 2, 28, 1, 2, 12, 7, 3, 3, 3, 3, 3, 3, 0, 3, 0, 2, 1, 3, 0, 3, 0, 0, 0, 0, 0, //우주2
	17, 0, 20, 9, 0, 10, 4, 10, 3, 3, 3, 3, 3, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 0, 0, 0, //개구리 보스
	17, 0, 20, 9, 0, 10, 4, 10, 3, 3, 3, 3, 3, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 0, 0, 0, //땅거미 보스
	17, 0, 9, 15, 0, 2, 7, 20, 3, 3, 3, 3, 3, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 0, 0, 0, //보스 멀록
	17, 0, 9, 15, 0, 2, 7, 20, 3, 3, 3, 3, 3, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 0, 0, 0, 0, //골렘
	17, 0, 0, 14, 0, 0, 9, 30, 3, 3, 3, 3, 3, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //이프리트
	17, 0, 0, 14, 0, 0, 9, 30, 3, 3, 3, 3, 3, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //나이아드
	17, 0, 0, 14, 0, 0, 9, 40, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, //드레이크
	17, 0, 0, 14, 0, 0, 9, 40, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, //이그니스
	17, 0, 0, 0, 0, 0, 0, 53, 3, 3, 3, 3, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 0, 0, 0, //키메라
	17, 0, 0, 0, 0, 0, 0, 53, 3, 3, 3, 3, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 0, 0, 0, //전함
	17, 0, 0, 0, 0, 0, 0, 53, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, //알카네
	17, 0, 0, 0, 0, 0, 0, 53, 3, 3, 3, 3, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 0, 0, 0, //바하무트
	17, 0, 0, 0, 0, 0, 0, 53, 3, 3, 3, 3, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 3, 0, 0, 0, 0, //사신
};
static const int itemValueType_builtin[] = {
	ALPHA_DAMAGE,	//ITEM_SWORD
	ALPHA_DAMAGE,	//ITEM_GUN
	ALPHA_DAMAGE,	//ITEM_BOOMERANG
	ALPHA_DEF,	//ITEM_HELM
	ALPHA_DEF,	//ITEM_HAT
	ALPHA_DEF,	//ITEM_CAP
	ALPHA_VIT,	//ITEM_ARMOR
	ALPHA_VIT,	//ITEM_VEST
	ALPHA_VIT,	//ITEM_COAT
	ALPHA_STR,	//ITEM_GUNTLET
	ALPHA_STR,	//ITEM_ARMLET
	ALPHA_STR,	//ITEM_GLOVE
	ALPHA_INT,	//ITEM_KILT
	ALPHA_INT,	//ITEM_SKIRT
	ALPHA_INT,	//ITEM_PANTS
	ALPHA_AGI,	//ITEM_GREAVES
	ALPHA_AGI,	//ITEM_SHOES
	ALPHA_AGI,	//ITEM_BOOTS
	ALPHA_OPTION,	//ITEM_NECK
	ALPHA_USE,	//ITEM_RING
};
static const int itemValueTypeText_builtin[] = {
	TEXT_ALPHA_DAMAGE,	//ITEM_SWORD
	TEXT_ALPHA_DAMAGE,	//ITEM_GUN
	TEXT_ALPHA_DAMAGE,	//ITEM_BOOMERANG
	TEXT_ALPHA_DEFENSE,	//ITEM_HELM
	TEXT_ALPHA_DEFENSE,	//ITEM_HAT
	TEXT_ALPHA_DEFENSE,	//ITEM_CAP
	TEXT_ALPHA_VIT,	//ITEM_ARMOR
	TEXT_ALPHA_VIT,	//ITEM_VEST
	TEXT_ALPHA_VIT,	//ITEM_COAT
	TEXT_ALPHA_STR,	//ITEM_GUNTLET
	TEXT_ALPHA_STR,	//ITEM_ARMLET
	TEXT_ALPHA_STR,	//ITEM_GLOVE
	TEXT_ALPHA_INT,	//ITEM_KILT
	TEXT_ALPHA_INT,	//ITEM_SKIRT
	TEXT_ALPHA_INT,	//ITEM_PANTS
	TEXT_ALPHA_AGI,	//ITEM_GREAVES
	TEXT_ALPHA_AGI,	//ITEM_SHOES
	TEXT_ALPHA_AGI,	//ITEM_BOOTS
	TEXT_ALPHA_OPTION,	//ITEM_NECK
	TEXT_ALPHA_USE,	//ITEM_RING
};
static const unsigned char itemEquipSlot_builtin[] = {
	EQUIP_WEAPON,	//ITEM_SWORD
	EQUIP_WEAPON,	//ITEM_GUN
	EQUIP_WEAPON,	//ITEM_BOOMERANG
	EQUIP_HELM,		//ITEM_HELM
	EQUIP_HELM,		//ITEM_HAT
	EQUIP_HELM,		//ITEM_CAP
	EQUIP_ARMOR,	//ITEM_ARMOR
	EQUIP_ARMOR,	//ITEM_VEST
	EQUIP_ARMOR,	//ITEM_COAT
	EQUIP_GLOVE,	//ITEM_GUNTLET
	EQUIP_GLOVE,	//ITEM_GLOVE
	EQUIP_GLOVE,	//ITEM_ARMLET
	EQUIP_PANTS,	//ITEM_KILT
	EQUIP_PANTS,	//ITEM_PANTS
	EQUIP_PANTS,	//ITEM_SKIRT
	EQUIP_BOOTS,	//ITEM_GREAVES
	EQUIP_BOOTS,	//ITEM_BOOTS
	EQUIP_BOOTS,	//ITEM_SHOES
	//EQUIP_NECK,	//ITEM_NECK
	//EQUIP_RING,	//ITEM_RING
};
static const unsigned char itemSlotEquip_builtin[] = {
	ITEM_SWORD,	//EQUIP_WEAPON
	ITEM_HELM,	//EQUIP_HELM
	ITEM_ARMOR,	//EQUIP_ARMOR
	ITEM_GUNTLET,		//EQUIP_PANTS
	ITEM_KILT,		//EQUIP_GLOVE
	ITEM_GREAVES,		//EQUIP_BOOTS
	ITEM_NECK,			//EQUIP_NECK
	ITEM_RING,		//EQUIP_RING
};
static const unsigned char wasteDrop_builtin[] = {
	ITEM_WASTE_RETURN,
	ITEM_WASTE_RETURN,
	ITEM_WASTE_RETURN,
	ITEM_WASTE_RETURN,
	ITEM_WASTE_RETURN,

	ITEM_WASTE_STAR,
	ITEM_WASTE_STAR,
	ITEM_WASTE_STAR,

	ITEM_WASTE_MOON,
	ITEM_WASTE_MOON,

	ITEM_WASTE_SUN,

	ITEM_WASTE_SILVER,
	ITEM_WASTE_SILVER,
	ITEM_WASTE_SILVER,

	ITEM_WASTE_GOLD,
	ITEM_WASTE_GOLD,

	ITEM_WASTE_SCARLET,

	ITEM_WASTE_ANTIDOTE,
	ITEM_WASTE_ANTIDOTE,
	ITEM_WASTE_FLUTE,
	ITEM_WASTE_FLUTE,
	ITEM_WASTE_EYEWASH,
	ITEM_WASTE_EYEWASH,
	ITEM_WASTE_HOLYWATER,
	ITEM_WASTE_HOLYWATER,
	ITEM_WASTE_WING,
	ITEM_WASTE_WING,

	ITEM_WASTE_FIRESTONE,
	ITEM_WASTE_FIREELEMENTAL,

	ITEM_WASTE_WATER,
};
static const unsigned char wasteValue_builtin[] = {
	0, 5, 20, 40, 3, 10, 30,
};
static const unsigned char weaponRange_builtin[] = {
	10,	//검
	20,	//총
	15,	//부메랑
};
static const unsigned int itemValue_builtin[] = {
	//검 : ITEM_SWORD																																																																																																				
12	,//ITEM_SWORD_STICK = 0,//1//연습용 몽둥이																																																																																																				
20	,//ITEM_SWORD_LONG,//2//롱소드																																																																																																				
30	,//ITEM_SWORD_CUTTER,//3//처형자의 검																																																																																																				
45	,//ITEM_SWORD_RUIN,//4//파멸의 참마도																																																																																																				
60	,//ITEM_SWORD_SEEKER,//5//추적자의 검																																																																																																				
80	,//ITEM_SWORD_DOUBLE,//6//격노의 양날검																																																																																																				
120	,//ITEM_SWORD_ELVEN,//7//수호자의 검																																																																																																				
150	,//ITEM_SWORD_ROYAL,//8//왕가의 수호자																																																																																																				
180	,//ITEM_SWORD_GHOST,//9//나찰의 검																																																																																																				
220	,//ITEM_SWORD_GHOST2,//10//소울 크래셔																																																																																																				
260	,//ITEM_SWORD_FRAME,//11//플레임소드																																																																																																				
300	,//ITEM_SWORD_ICE,//12//아이스소드																																																																																																				
350	,//ITEM_SWORD_THUNDER,//13//썬더소드																																																																																																				
400	,//ITEM_SWORD_EARTH,//14//어스소드																																																																																																				
450	,//ITEM_SWORD_LAEVATEINN,//15//레바테인																																																																																																				
500	,//ITEM_SWORD_STORMBRINGER,//16//스톰브링거																																																																																																				
560	,//ITEM_SWORD_CALADBOLG,//17//칼라드볼그																																																																																																				
620	,//ITEM_SWORD_BALMUNG,//18//발뭉																																																																																																				
680	,//ITEM_SWORD_HRUNTING,//19//흐룬팅																																																																																																				
750	,//ITEM_SWORD_GIANT,//20//거인의 칼																																																																																																				
820	,//ITEM_SWORD_MISTILTEINN,//21//미스틸테인																																																																																																				
900	,//ITEM_SWORD_EXCALIBUR,//22//엑스칼리버																																																																																																				
1000	,//ITEM_SWORD_HOLY,//23//홀리소드																																																																																																				
1100	,//ITEM_SWORD_DARK,//24//다크소드																																																																																																				
1200	,//ITEM_SWORD_LEO,//25//레오소드																																																																																																				
1300	,//ITEM_SWORD_DEATH,//26//사신의 낫																																																																																																				
1400	,//ITEM_SWORD_DRAGONCLOW,//27//드래곤 클로우																																																																																																				
1500	,//ITEM_SWORD_DRAGONTOOTH,//28//황룡의 어금니																																																																																																				
1700	,//ITEM_SWORD_DRAGONGOD,//29//신룡마강검																																																																																																				
1900	,//ITEM_SWORD_DRAGONSLAYER,//30//드래곤 슬레이어																																																																																																				
2100	,//ITEM_SWORD_ULTIMATE,//31//얼티밋소드																																																																																																				
2300	,//ITEM_SWORD_DIMENSIONAL,//32//차원의 검																																																																																																				
2500	,//ITEM_SWORD_HEAVEN,//33//천공의 검																																																																																																				
2800	,//ITEM_SWORD_STARDUST,//34//스타더스트																																																																																																				
3100	,//ITEM_SWORD_KING,//35//패왕의 검																																																																																																				
//TOTAL_SWORD,																																																																																																				

//총 : ITEM_GUN																																																																																																				
10	,//ITEM_GUN_PISTOL = 0,//발화식 총																																																																																																				
18	,//ITEM_GUN_REVOLVER,//리볼버 파이슨																																																																																																				
27	,//ITEM_GUN_MAGNUM,//45구경 오토건 : 사일런트 킬러																																																																																																				
40	,//ITEM_GUN_AUTOGUN45MM,//고져스 건 : 럭셔리 캐논																																																																																																				
55	,//ITEM_GUN_JEWELGUN,//회천마도총 : 마도머신건																																																																																																				
72	,//ITEM_GUN_EXPLOSION,//태양의 총 : 슈퍼노바																																																																																																				
90	,//ITEM_GUN_CROSSFIRE,//헬파이어 건 : 인페르노 캐논 : 마룡열화포																																																																																																				
108	,//ITEM_GUN_INFERNO,//크로스 파이어 : 테스타먼트 : 라그나로크																																																																																																				
//TOTAL_GUN,																																																																																																				

//부메랑 : ITEM_BOOMERANG																																																																																																				
15	,//ITEM_BOOMERANG_BOOMERANG = 0,//사냥용 부메랑																																																																																																				
23	,//ITEM_BOOMERANG_VOYAGER,//슬라이서																																																																																																				
32	,//ITEM_BOOMERANG_WINDWALKER,//강철 부메랑 : 윈드 슬래셔																																																																																																				
43	,//ITEM_BOOMERANG_DOUBLECROSS,//트라이 엣지 : 헬 트라이앵글																																																																																																				
53	,//ITEM_BOOMERANG_THUNDERMASTER,//라이트닝 엣지 : 한탄의 부메랑																																																																																																				
68	,//ITEM_BOOMERANG_SOULCHASER,//소울 체이서 : 둠 슬레이어																																																																																																				
85	,//ITEM_BOOMERANG_GRYPHONWING,//그리폰 윙 : 윙 오브 데스 : 드래곤 윙																																																																																																				
102	,//ITEM_BOOMERANG_MEGATRIAL,//로커스트 헌트 : 제노사이드 윙 : 디재스터 엣지																																																																																																				
//TOTAL_BOOMERANG,																																																																																																				

//헬멧 : ITEM_HELM																																																																																																				
13	,//ITEM_HELM_BRONZE = 0,//헤드 가드																																																																																																			
100	,//ITEM_HELM_BASINET,//바시넷																																																																																																				
180	,//ITEM_HELM_DROW,//솔저헬름 : 센츄리온 헬멧																																																																																																			
270	,//ITEM_HELM_SPIKEHEAD,//검투사의 투구 : 블러디 헬멧																																																																																																			
360	,//ITEM_HELM_GLADITOR,//스파이크 헤드 : 귀신의 투구																																																																																																				
450	,//ITEM_HELM_GIANT,//그랜드 헬름 : 성기사의 투구																																																																																																			
540	,//ITEM_HELM_RUINED,//고대의 투구 : 환영의 투구 : 미라주 헬름																																																																																																			
630	,//ITEM_HELM_TITANIUM,//용자의 투구 : 져지먼트 헬맷 : 오시리스 헬맷																																																																																																				
//TOTAL_HELM,																																																																																																				

//모자 : ITEM_HAT																																																																																																				
7	,//ITEM_HAT_COWBOY		= 0,//카우보이 모자																																																																																																		
14	,//ITEM_HAT_RIDINGGOGGLE,//산책용 보닛																																																																																																				
22	,//ITEM_HAT_BERET,//레인저 햇 : 무법자의 모자																																																																																																				
30	,//ITEM_HAT_WESTERNROMANCE,//서클릿 : 골드 블레스																																																																																																				
40	,//ITEM_HAT_SCOUT,//올드 윌로우 : 엘븐 햇																																																																																																				
50	,//ITEM_HAT_SNIPERGOGGLE,//스나이퍼 고글 : 어쌔신 스코프																																																																																																				
62	,//ITEM_HAT_ELVENCAP,//혼란의 모자 : 카오스 솔져 : 나이트메어 햇																																																																																																				
76	,//ITEM_HAT_DRAGONSKULL,//프리에스테스 : 발키리 서클렛 : 오딘 크라운																																																																																																				
//TOTAL_HAT,																																																																																																				

//두건 : ,//ITEM_CAP																																																																																																				
10	,//ITEM_CAP_FEATHER = 0,//공작깃털 모자																																																																																																				
21	,//ITEM_CAP_BEASTMANE,//귀족의 머리띠																																																																																																				
32	,//ITEM_CAP_EXPLORERHAT,//거상의 모자 : 캐러벤 리더																																																																																																				
45	,//ITEM_CAP_ACECAP,//사냥꾼 모자 : 로빈훗 캡																																																																																																				
60	,//ITEM_CAP_LIONMANE,//투우사의 모자 : 미노타우르스																																																																																																				
75	,//ITEM_CAP_GREAVE,//해적의 모자 : 졸리로져 캡																																																																																																				
93	,//ITEM_CAP_DEATH,//에이스 캡 : 브레이브 캡 : 다이너스티 캡																																																																																																				
114	,//ITEM_CAP_TROLLHEAD,//드래곤 레어캡 : 히드라 헤드 : 리바이어선 캡																																																																																																				
//TOTAL_CAP,

//갑옷 : ITEM_ARMOR																																																																																																				
22	,//ITEM_ARMOR_BRONZE = 0,//헌터 튜닉																																																																																																			
167	,//ITEM_ARMOR_SCALE,//미늘 갑옷																																																																																																					
300	,//ITEM_ARMOR_BANDED,//하프 플레이트 : 밴디트 메일																																																																																																				
450	,//ITEM_ARMOR_SKULL,//스컬 메일 : 마검사의 흉갑																																																																																																						
700	,//ITEM_ARMOR_PLATE,//황금세공 갑옷 : 드워븐 아머																																																																																																					
1000	,//ITEM_ARMOR_RUNIC,//미스릴 아머 : 요정의 갑주																																																																																																				
1300	,//ITEM_ARMOR_MYTHRIL,//고대의 갑옷 : 불멸의 갑주 : 브리건딘																																																																																																			
1600	,//ITEM_ARMOR_DRAGONSKIN,//용비늘 갑옷 : 황룡의 갑옷 : 바하무트 아머																																																																																																				
//TOTAL_ARMOR,																																																																																																				

//조끼 : ITEM_VEST																																																																																																				
11	,//ITEM_VEST_WESTERN = 0,//카우보이 조끼																																																																																																				
23	,//ITEM_VEST_LEOPARD,//실크 조끼																																																																																																				
36	,//ITEM_VEST_SILK,//방랑자의 조끼 : 서바이벌 조끼																																																																																																				
50	,//ITEM_VEST_PIRATE,//도적의 조끼 : 어쌔신 베스트																																																																																																				
66	,//ITEM_VEST_BALL,//벨벳 셔츠 : 고딕 셔츠																																																																																																				
84	,//ITEM_VEST_STAR,//귀족의 조끼 : 은사슬 조끼																																																																																																				
104	,//ITEM_VEST_SPATIOTEMPORAL,//진홍빛 셔츠 : 불사의 셔츠 : 뱀파이어 로드																																																																																																				
126	,//ITEM_VEST_QUEEN,//신관의 로브 : 세라핌 로브 : 루시펠 로브																																																																																																				
//TOTAL_VEST,																																																																																																				

//코트 : ITEM_COAT																																																																																																				
16	,//ITEM_COAT_SIMPLE = 0,//수수한 코트																																																																																																				
34	,//ITEM_COAT_PADDING,//패딩 아머																																																																																																				
54	,//ITEM_COAT_LEATHER,//털가죽 코트 : 그리즐리 스킨																																																																																																				
75	,//ITEM_COAT_CUREBOIL,//큐어 보일 : 코아틀 스케일																																																																																																				
99	,//ITEM_COAT_BEAST,//귀족의 코트 : 흑까마귀 코트																																																																																																				
126	,//ITEM_COAT_GRIZZLY,//극지의 코트 : 블리자드 가드																																																																																																				
156	,//ITEM_COAT_CROCODYLE,//윙 코트 : 가고일 코트 : 페가수스 코트																																																																																																				
189	,//ITEM_COAT_HYDRASCALE,//바이스 코트 : 종말의 코트 : 카오스 엠페러																																																																																																				
//TOTAL_COAT,																																																																																																				

//건틀렛 : ITEM_GUNTLET
4	,//ITEM_GUNTLET_IRON = 0,//핸드 가드
33	,//ITEM_GUNTLET_CHAIN,//청동 장갑
60	,//ITEM_GUNTLET_MONSTER,//체인 건틀렛 : 모험자의 장갑
90	,//ITEM_GUNTLET_KNIGHT,//나이트 글로브 : 명성의 장갑
130	,//ITEM_GUNTLET_EAGLECLAW,//비스트 핸드 : 오우거 건틀렛
180	,//ITEM_GUNTLET_SINE,//라이징 건틀렛 : 무쌍의 장갑
250	,//ITEM_GUNTLET_JUSTICEHAND,//광전사의 장갑 : 뇌격파수 : 시바의 손톱
350	,//ITEM_GUNTLET_HOLYHAND,//드래곤 핸드 : 백룡의 장갑 : 바하무트 핸드
//TOTAL_GUNTLET,


//팔찌 : ITEM_ARMLET																																																																																																				
2	,//ITEM_ARMLET_LEATHER		= 0,//사제의 묵주																																																																																																		
5	,//ITEM_ARMLET_DESERT,//여행자의 팔찌																																																																																																				
7	,//ITEM_ARMLET_EXPLORER,//백금 브레스렛 : 연인의 팔찌																																																																																																				
10	,//ITEM_ARMLET_RAIDERS,//전사의 암렛 : 임프 암렛																																																																																																				
13	,//ITEM_ARMLET_NOBLESS,//에메랄드 팔찌 : 노블레스 암렛																																																																																																				
17	,//ITEM_ARMLET_DEVIL,//이블 암렛 : 몽마의 팔찌																																																																																																				
21	,//ITEM_ARMLET_DIGNITY,//위엄의 팔찌 : 지배자의 팔찌 : 엠프레스 암렛																																																																																																				
25	,//ITEM_ARMLET_HERO,//영웅의 팔찌 : 소울 브레스렛 : 갓 핸드																																																																																																				
//TOTAL_ARMLET,																																																																																																				

//장갑 : ITEM_GLOVE																																																																																																				
3	,//ITEM_GLOVE_TRAVELER		= 0,//여행자의 장갑																																																																																																		
7	,//ITEM_GLOVE_DUALTIE,//이중매듭 장갑																																																																																																				
10	,//ITEM_GLOVE_LINEN,//소매치기 장갑 : 섀도우 핸드																																																																																																				
15	,//ITEM_GLOVE_RUNE,//실크 글로브 : 귀공자의 장갑																																																																																																				
20	,//ITEM_GLOVE_FAIRY,//세공사의 장갑 : 마스터 글러브																																																																																																				
25	,//ITEM_GLOVE_ROCKET,//마법문양 장갑 : 커스드 글로브																																																																																																				
31	,//ITEM_GLOVE_LACEMITTEN,//심판의 손 : 구원의 손 : 이터널 져지																																																																																																				
38	,//ITEM_GLOVE_GLORY,//성자의 장갑 : 팔라딘 글로브 : 홀리 핸드																																																																																																				
//TOTAL_GLOVE,																																																																																																				

//킬트 : ITEM_KILT																																																																																																				
18	,//ITEM_KILT_CHAIN		= 0,//밴딩 킬트																																																																																																					
134	,//ITEM_KILT_DUALCHAIN,//체인 킬트																																																																																																				
240	,//ITEM_KILT_BATTLE,//나이트 킬트 : 배틀 킬트																																																																																																			
360	,//ITEM_KILT_NIGHTMARE,//스컬 킬트 : 사령의 바지																																																																																																			
500	,//ITEM_KILT_BATTLEFIELD,//수령의 바지 : 토르의 바지																																																																																																				
650	,//ITEM_KILT_DWARVEN,//미스릴 킬트 : 페어리 킬트																																																																																																					
800	,//ITEM_KILT_DURAHAN,//에인션트 킬트 : 이터널 킬트 : 언리밋 킬트																																																																																																				
1000	,//ITEM_KILT_EARTHQUAKE,//용수염 킬트 : 청룡의 킬트 : 용기사 바지																																																																																																				
//TOTAL_KILT,																																																																																																				

//바지 : ,//ITEM_SKIRT																																																																																																				
9	,//ITEM_SKIRT_BROCADE = 0,//양단 스커트																																																																																																				
18	,//ITEM_SKIRT_CARPSKIN,//빈티지 스커트																																																																																																				
29	,//ITEM_SKIRT_VELVET,//단풍염색 치마 : 홍련의 스커트																																																																																																				
40	,//ITEM_SKIRT_NOBLE,//벨벳 스커트 : 소공녀의 치마																																																																																																				
53	,//ITEM_SKIRT_GENERAL,//폭풍의 스커트 : 무지개빛 치마																																																																																																				
67	,//ITEM_SKIRT_GLORY,//금실의 치마 : 여제의 스커트																																																																																																				
83	,//ITEM_SKIRT_CHAOS,//영광의 치마 : 현자의 치마 : 성령의 치마																																																																																																				
101	,//ITEM_SKIRT_HERO,//사제의 스커트 : 비슈누 스커트 : 태양의 스커트																																																																																																				
//TOTAL_SKIRT,

//바지 : ITEM_PANTS																																																																																																				
13	,//ITEM_PANTS_RIDING = 0,//승마용 바지																																																																																																				
27	,//ITEM_PANTS_VINTAGEJEAN,//카프스킨 팬츠																																																																																																				
42	,//ITEM_PANTS_BLAZE,//망령의 팬츠 : 머미 밴디지																																																																																																				
60	,//ITEM_PANTS_ASSASSIN,//흑단의 바지 : 어쌔신 팬츠																																																																																																				
80	,//ITEM_PANTS_TEMPEST,//세일러 팬츠 : 제독의 바지																																																																																																				
100	,//ITEM_PANTS_SCARLETLEGGINGS,//데저트 팬츠 : 캐러밴 팬츠																																																																																																				
125	,//ITEM_PANTS_HEAVEN,//카오틱 팬츠 : 침묵의 바지 : 아비스 팬츠																																																																																																				
152	,//ITEM_PANTS_SATANIC,//가디안 팬츠 : 켈베로스 레더 : 아누비스 바지																																																																																																				
//TOTAL_PANTS,																																																																																																				

//장화 : ITEM_GREAVES																																																																																																				
9	,//ITEM_GREAVES_TRAINER = 0,//코퍼 그리브																																																																																																			
67	,//ITEM_GREAVES_CHAIN,//밴디트 그리브																																																																																																				
120	,//ITEM_GREAVES_KNIGHT,//체인 그리브 : 나이트 그리브																																																																																																				
180	,//ITEM_GREAVES_FROZEN,//프로즌 그리브 : 만년설의 신발																																																																																																				
260	,//ITEM_GREAVES_GOLEM,//플레이트 부츠 : 드워븐 그리브																																																																																																					
350	,//ITEM_GREAVES_GIANT,//빅풋 그리브 : 골렘 그리브																																																																																																						
450	,//ITEM_GREAVES_GHOST,//마검사의 신발 : 사령의 신발 : 종말의 발소리																																																																																																				
580	,//ITEM_GREAVES_LEGEND,//드래곤 그리브 : 마룡의 발자국 : 가이아 그리브																																																																																																				
//TOTAL_GREAVES,																																																																																																				

//신발 : ITEM_SHOES																																																																																																				
4	,//ITEM_SHOES_CLEAN = 0,//웨스턴 슈즈																																																																																																				
9	,//ITEM_SHOES_CHASER,//스웨이드 슈즈																																																																																																				
14	,//ITEM_SHOES_LEATHER,//라이딩 슈즈 : 밀리터리 워커																																																																																																				
20	,//ITEM_SHOES_ROCKY,//칠흑의 슈즈 : 마녀의 슈즈																																																																																																				
26	,//ITEM_SHOES_CARVING,//귀부인의 신발 : 로얄 셀레브																																																																																																				
33	,//ITEM_SHOES_NETHERWORLD,//리치 슈즈 : 팬텀 테일즈																																																																																																				
41	,//ITEM_SHOES_INCARNATION,//프리즘 슈즈 : 미라클 슈즈 : 그라비티 슈즈																																																																																																				
50	,//ITEM_SHOES_HEAVENS,//베이그란트 : 페이트 슈즈 : 데스티니 슈즈																																																																																																				
//TOTAL_SHOES,																																																																																																				

//부츠 : ITEM_BOOTS																																																																																																				
6	,//ITEM_BOOTS_SUEDE = 0,//스니커즈																																																																																																				
13	,//ITEM_BOOTS_WESTERN,//스캐빈저 부츠																																																																																																				
21	,//ITEM_BOOTS_RIDING,//천둥가죽 신발 : 낙뢰의 자국																																																																																																				
30	,//ITEM_BOOTS_RICH,//가드너 부츠 : 토렌트 루트																																																																																																				
39	,//ITEM_BOOTS_OGRE,//세일러 부츠 : 캡틴 부츠																																																																																																				
45	,//ITEM_BOOTS_DARK,//저승의 신발 : 헬 스트라이더																																																																																																				
62	,//ITEM_BOOTS_MIRACLE,//엘레멘탈 부츠 : 브리징 윈드 : 템페스트 부츠																																																																																																				
76	,//ITEM_BOOTS_DESTINY,//에어워커 : 클라우드 부츠 : 헤븐리 부츠																																																																																																				
//TOTAL_BOOTS,																																																																																																				

};
static const unsigned char gradeRatio_builtin[] = {
	100, //GRADE_NORMAL
	100, //GRADE_SUPERIOR
	100, //GRADE_RARE
	100, //GRADE_SET
	100, //GRADE_EPIC
	100, //GRADE_LEGEND
};
static const unsigned char typeRatio_builtin[] = {
	100,//ITEM_SWORD = 0,
	100,//ITEM_GUN,//1
	100,//ITEM_BOOMERANG,//2
	50,//ITEM_HELM,//3
	50,//ITEM_HAT,//4
	50,//ITEM_CAP,//5
	40,//ITEM_ARMOR,//6
	40,//ITEM_VEST,//7
	40,//ITEM_COAT,//8
	80,//ITEM_GUNTLET,//9
	80,//ITEM_ARMLET,//10
	80,//ITEM_GLOVE,//11
	60,//ITEM_KILT,//12
	60,//ITEM_SKIRT,//13
	60,//ITEM_PANTS,//14
	70,//ITEM_GREAVES,//15
	70,//ITEM_SHOES,//16
	70,//ITEM_BOOTS,//17
};
static const unsigned char acceOptionStatMatch_builtin[] = {
	SUFFIX_WEAPON_DMG, PS_WEAPONDMG,
	PREFIX_VIT, PS_VIT,
	SUFFIX_ARMOR, PS_ARMOR,
	PREFIX_STR, PS_STR,
	PREFIX_AGI, PS_AGI,
	PREFIX_INT, PS_INT,
};
static const unsigned int acceDefaultStatValue_builtin[] = {
	//WEAPONDMG,
	5,
	10,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,
	60,
	65,
	70,
	75,
	80,
	85,
	90,
	95,
	100,
	105,
	110,
	115,
	120,
	125,
	130,
	135,
	140,
	145,
	150,
	155,
	160,
	165,
	170,
	175,
	180,
	185,
	190,
	195,
	200,
	205,
	210,
	215,
	220,
	225,
	230,
	235,
	240,
	245,
	250,
	//VIT,
	50,
	100,
	150,
	200,
	250,
	300,
	350,
	400,
	450,
	500,
	550,
	600,
	650,
	700,
	750,
	800,
	850,
	900,
	950,
	1000,
	1050,
	1100,
	1150,
	1200,
	1250,
	1300,
	1350,
	1400,
	1450,
	1500,
	1550,
	1600,
	1650,
	1700,
	1750,
	1800,
	1850,
	1900,
	1950,
	2000,
	2050,
	2100,
	2150,
	2200,
	2250,
	2300,
	2350,
	2400,
	2450,
	2500,
	//ARMOR,
	5,
	10,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,
	60,
	65,
	70,
	75,
	80,
	85,
	90,
	95,
	100,
	105,
	110,
	115,
	120,
	125,
	130,
	135,
	140,
	145,
	150,
	155,
	160,
	165,
	170,
	175,
	180,
	185,
	190,
	195,
	200,
	205,
	210,
	215,
	220,
	225,
	230,
	235,
	240,
	245,
	250,
	//STR,
	5,
	10,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,
	60,
	65,
	70,
	75,
	80,
	85,
	90,
	95,
	100,
	105,
	110,
	115,
	120,
	125,
	130,
	135,
	140,
	145,
	150,
	155,
	160,
	165,
	170,
	175,
	180,
	185,
	190,
	195,
	200,
	205,
	210,
	215,
	220,
	225,
	230,
	235,
	240,
	245,
	250,
	//AGI,
	5,
	10,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,
	60,
	65,
	70,
	75,
	80,
	85,
	90,
	95,
	100,
	105,
	110,
	115,
	120,
	125,
	130,
	135,
	140,
	145,
	150,
	155,
	160,
	165,
	170,
	175,
	180,
	185,
	190,
	195,
	200,
	205,
	210,
	215,
	220,
	225,
	230,
	235,
	240,
	245,
	250,
	//INT,
	5,
	10,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,
	60,
	65,
	70,
	75,
	80,
	85,
	90,
	95,
	100,
	105,
	110,
	115,
	120,
	125,
	130,
	135,
	140,
	145,
	150,
	155,
	160,
	165,
	170,
	175,
	180,
	185,
	190,
	195,
	200,
	205,
	210,
	215,
	220,
	225,
	230,
	235,
	240,
	245,
	250,


};
static const unsigned int neckOptionStatValue_builtin[] = {
	//명예의 펜던트(적중)
	//PS_HIT, SUFFIX_HIT, 1, 2, 4, 7, PS_AGI, PREFIX_AGI,//PS_AGI(1)
	//PREFIX_SKILLDMG,
	200,
	215,
	230,
	245,
	260,
	275,
	290,
	305,
	320,
	335,
	350,
	365,
	380,
	395,
	410,
	425,
	440,
	455,
	470,
	485,
	500,
	515,
	530,
	545,
	560,
	575,
	590,
	605,
	620,
	635,
	650,
	665,
	680,
	695,
	710,
	725,
	740,
	755,
	770,
	785,
	800,
	820,
	840,
	860,
	880,
	900,
	920,
	940,
	960,
	1000,

	//연옥의 브로치(치명타)
	//PS_CRITICAL, PREFIX_CRITICAL, 1, 2, 4, 7, PS_AGI, PREFIX_AGI,//PS_AGI(2)
	30,
	32,
	34,
	36,
	38,
	40,
	42,
	44,
	46,
	48,
	50,
	52,
	54,
	56,
	58,
	60,
	62,
	64,
	66,
	68,
	70,
	72,
	74,
	76,
	78,
	80,
	82,
	84,
	86,
	88,
	90,
	92,
	94,
	96,
	98,
	100,
	102,
	104,
	106,
	108,
	110,
	114,
	118,
	122,
	126,
	130,
	134,
	138,
	142,
	150,

	//찰나의 팔찌(치명타 데미지)
	//PS_CRITDMG, SUFFIX_CRITICAL, 2, 5, 10, 20, PS_AGI, PREFIX_AGI,//PS_AGI(3)
	200,
	215,
	230,
	245,
	260,
	275,
	290,
	305,
	320,
	335,
	350,
	365,
	380,
	395,
	410,
	425,
	440,
	455,
	470,
	485,
	500,
	515,
	530,
	545,
	560,
	575,
	590,
	605,
	620,
	635,
	650,
	665,
	680,
	695,
	710,
	725,
	740,
	755,
	770,
	785,
	800,
	820,
	840,
	860,
	880,
	900,
	920,
	940,
	960,
	1000,

	//황금 바늘(관통)
	//PS_PIERCE, PREFIX_PIERCE, 1, 2, 4, 7, PS_INT, PREFIX_INT,//PS_INT(1)
	40,
	43,
	46,
	49,
	52,
	55,
	58,
	61,
	64,
	67,
	70,
	73,
	76,
	79,
	82,
	85,
	88,
	91,
	94,
	97,
	100,
	103,
	106,
	109,
	112,
	115,
	118,
	121,
	124,
	127,
	130,
	133,
	136,
	139,
	142,
	145,
	148,
	151,
	154,
	157,
	160,
	164,
	168,
	172,
	176,
	180,
	184,
	188,
	192,
	200,

	//파열의 팔찌(추가타)
	//PS_EXTRA, PREFIX_EXTRA, 1, 2, 4, 7, PS_STR, PREFIX_STR,//PS_STR(1)
	40,
	43,
	46,
	49,
	52,
	55,
	58,
	61,
	64,
	67,
	70,
	73,
	76,
	79,
	82,
	85,
	88,
	91,
	94,
	97,
	100,
	103,
	106,
	109,
	112,
	115,
	118,
	121,
	124,
	127,
	130,
	133,
	136,
	139,
	142,
	145,
	148,
	151,
	154,
	157,
	160,
	164,
	168,
	172,
	176,
	180,
	184,
	188,
	192,
	200,

	//메피스토 피리(방어무시)
	//PS_IGNORE, SUFFIX_IGNORE, 1, 3, 7, 12, PS_WEAPONDMG, PREFIX_WEAPON_DMG,//PS_WEAPONDMG(1)
	40,
	43,
	46,
	49,
	52,
	55,
	58,
	61,
	64,
	67,
	70,
	73,
	76,
	79,
	82,
	85,
	88,
	91,
	94,
	97,
	100,
	103,
	106,
	109,
	112,
	115,
	118,
	121,
	124,
	127,
	130,
	133,
	136,
	139,
	142,
	145,
	148,
	151,
	154,
	157,
	160,
	164,
	168,
	172,
	176,
	180,
	184,
	188,
	192,
	200,

	//사멸의 하프(기절공격)
	//PS_STUN, SUFFIX_STUN, 1, 3, 7, 12, PS_AGI, PREFIX_AGI,//PS_AGI(4)
	//SUFFIX_STAT,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	42,
	44,
	46,
	48,
	50,
	52,
	54,
	56,
	58,
	60,
	62,
	64,
	66,
	68,
	70,
	72,
	74,
	76,
	78,
	80,
	82,
	84,
	86,
	88,
	90,
	92,
	94,
	96,
	100,

	//인어의 머리핀(적방어력 삭감)
	//PS_DEFENSE, PREFIX_DEFENSE, 20, 50, 100, 200, PS_WEAPONDMG, PREFIX_WEAPON_DMG,//PS_WEAPONDMG(2)
	//SUFFIX_WEAPON_DMG,
	20,
	23,
	29,
	38,
	54,
	74,
	98,
	126,
	158,
	203,
	253,
	308,
	368,
	433,
	573,
	723,
	883,
	1053,
	1233,
	1518,
	1818,
	2133,
	2463,
	2808,
	3288,
	3788,
	4308,
	4848,
	5408,
	6133,
	6883,
	7658,
	8458,
	9283,
	10303,
	11353,
	12433,
	13543,
	14683,
	16048,
	17448,
	18883,
	20353,
	21858,
	23618,
	25418,
	27258,
	29138,
	31058,
	35000,

	//찬트의 펜던트(추가방어)
	//PS_ARMOR, SUFFIX_ARMOR, 10, 30, 60, 100, PS_STR, PREFIX_STR,//PS_STR(2)
	10,
	12,
	14,
	19,
	27,
	37,
	49,
	63,
	79,
	100,
	126,
	159,
	184,
	217,
	287,
	362,
	442,
	527,
	617,
	759,
	909,
	1067,
	1232,
	1404,
	1644,
	1894,
	2154,
	2424,
	2704,
	3067,
	3442,
	3829,
	4229,
	4642,
	5152,
	5677,
	6217,
	6772,
	7342,
	8024,
	8724,
	9442,
	10177,
	10929,
	11809,
	12709,
	13629,
	14569,
	15529,
	17000,

	//미래의 거울(회피)
	//PS_EVASION, SUFFIX_EVASION, 1, 2, 4, 7, PS_AGI, PREFIX_AGI,//PS_AGI(5)
	30,
	32,
	34,
	36,
	38,
	40,
	42,
	44,
	46,
	48,
	50,
	52,
	54,
	56,
	58,
	60,
	62,
	64,
	66,
	68,
	70,
	72,
	74,
	76,
	78,
	80,
	82,
	84,
	86,
	88,
	90,
	92,
	94,
	96,
	98,
	100,
	102,
	104,
	106,
	108,
	110,
	114,
	118,
	122,
	126,
	130,
	134,
	138,
	142,
	150,

	//피의 모래시계(화염저항)
	//PS_FIRE, PREFIX_FIRE_REGIST, 5, 10, 20, 40, PS_ARMOR, SUFFIX_ARMOR,//PS_ARMOR(1)
	//PREFIX_STR,
	10,
	12,
	14,
	16,
	18,
	20,
	22,
	24,
	26,
	30,
	34,
	38,
	42,
	46,
	50,
	54,
	58,
	62,
	66,
	70,
	76,
	82,
	88,
	94,
	100,
	106,
	112,
	118,
	124,
	132,
	140,
	148,
	156,
	164,
	172,
	180,
	188,
	196,
	204,
	214,
	224,
	234,
	244,
	254,
	264,
	274,
	284,
	294,
	304,
	320,

	//지옥의 만화경(번개저항)
	//PS_THUNDER, PREFIX_THUNDER_REGIST, 5, 10, 20, 40, PS_ARMOR, SUFFIX_ARMOR,//PS_ARMOR(2)
	//SUFFIX_DELAY,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	42,
	44,
	46,
	48,
	50,
	52,
	54,
	56,
	58,
	60,
	62,
	64,
	66,
	68,
	70,
	72,
	74,
	76,
	78,
	80,
	82,
	84,
	86,
	88,
	90,
	92,
	94,
	96,
	100,

	//전능의 브로치(냉기저항)
	//PS_FROST, PREFIX_FROST_REGIST, 5, 10, 20, 40, PS_ARMOR, SUFFIX_ARMOR,//PS_ARMOR(3)
	//PREFIX_AGI,
	10,
	12,
	14,
	16,
	18,
	20,
	22,
	24,
	26,
	30,
	34,
	38,
	42,
	46,
	50,
	54,
	58,
	62,
	66,
	70,
	76,
	82,
	88,
	94,
	100,
	106,
	112,
	118,
	124,
	132,
	140,
	148,
	156,
	164,
	172,
	180,
	188,
	196,
	204,
	214,
	224,
	234,
	244,
	254,
	264,
	274,
	284,
	294,
	304,
	320,

	//생명의 보옥(생명력)
	//PS_HP, SUFFIX_HP, 30, 70, 120, 200, PS_VIT, PREFIX_VIT,//PS_VIT(1)
	100,
	120,
	140,
	190,
	270,
	370,
	490,
	630,
	790,
	1000,
	1260,
	1520,
	1840,
	2170,
	2870,
	3620,
	4420,
	5270,
	6170,
	7590,
	9090,
	10670,
	12320,
	14040,
	16440,
	18940,
	21540,
	24240,
	27040,
	30670,
	34420,
	38290,
	42290,
	46420,
	51520,
	56770,
	62170,
	67720,
	73420,
	80240,
	87240,
	94420,
	101770,
	109290,
	118090,
	127090,
	136290,
	145690,
	155290,
	170000,

	//증식의 목걸이(생명회복)
	//PS_HPRESTORE, PREFIX_HPRESTORE, 3, 7, 12, 20, PS_VIT, PREFIX_VIT,//PS_VIT(2)
	60,
	64,
	68,
	72,
	76,
	80,
	84,
	88,
	92,
	96,
	100,
	104,
	108,
	112,
	116,
	120,
	124,
	128,
	132,
	136,
	140,
	144,
	148,
	152,
	156,
	160,
	164,
	168,
	172,
	176,
	180,
	184,
	188,
	192,
	196,
	200,
	204,
	208,
	212,
	216,
	224,
	232,
	240,
	248,
	256,
	264,
	272,
	280,
	288,
	300,

	//천공의 목걸이(생명흡수)
	//PS_HPDRAIN, SUFFIX_HPDRAIN, 1, 2, 3, 5, PS_VIT, PREFIX_VIT,//PS_VIT(3)
	40,
	43,
	46,
	49,
	52,
	55,
	58,
	61,
	64,
	67,
	70,
	73,
	76,
	79,
	82,
	85,
	88,
	91,
	94,
	97,
	100,
	103,
	106,
	109,
	112,
	115,
	118,
	121,
	124,
	127,
	130,
	133,
	136,
	139,
	142,
	145,
	148,
	151,
	154,
	157,
	160,
	164,
	168,
	172,
	176,
	180,
	184,
	188,
	192,
	200,

	//현자의 돌(마력)
	//PS_MP, SUFFIX_MP, 40, 90, 150, 250, PS_INT, PREFIX_INT,//PS_INT(2)
	//PREFIX_VIT,
	60,
	64,
	68,
	72,
	76,
	80,
	84,
	88,
	92,
	96,
	100,
	104,
	108,
	112,
	116,
	120,
	124,
	128,
	132,
	136,
	140,
	144,
	148,
	152,
	156,
	160,
	164,
	168,
	172,
	176,
	180,
	184,
	188,
	192,
	196,
	200,
	204,
	208,
	212,
	216,
	224,
	232,
	240,
	248,
	256,
	264,
	272,
	280,
	288,
	300,

	//꿈의 오카리나(마력회복)
	//PS_MPRESTORE, PREFIX_MPRESTORE, 10, 20, 30, 50, PS_INT, PREFIX_INT,//PS_INT(3)
	//PREFIX_ARMOR,
	60,
	64,
	68,
	72,
	76,
	80,
	84,
	88,
	92,
	96,
	100,
	104,
	108,
	112,
	116,
	120,
	124,
	128,
	132,
	136,
	140,
	144,
	148,
	152,
	156,
	160,
	164,
	168,
	172,
	176,
	180,
	184,
	188,
	192,
	196,
	200,
	204,
	208,
	212,
	216,
	224,
	232,
	240,
	248,
	256,
	264,
	272,
	280,
	288,
	300,

	//무한의 나침반(마력흡수)
	//PS_MPDRAIN, SUFFIX_MPDRAIN, 1, 2, 3, 5, PS_INT, PREFIX_INT,//PS_INT(4)
	//PREFIX_WEAPON_DMG,
	60,
	64,
	68,
	72,
	76,
	80,
	84,
	88,
	92,
	96,
	100,
	104,
	108,
	112,
	116,
	120,
	124,
	128,
	132,
	136,
	140,
	144,
	148,
	152,
	156,
	160,
	164,
	168,
	172,
	176,
	180,
	184,
	188,
	192,
	196,
	200,
	204,
	208,
	212,
	216,
	224,
	232,
	240,
	248,
	256,
	264,
	272,
	280,
	288,
	300,

	//기억의 오르골(경험치 추가)
	//PS_EXPMOD, PREFIX_EXP, 10, 25, 40, 75, PS_WEAPONDMG, PREFIX_WEAPON_DMG,//PS_WEAPONDMG(3)
	//SUFFIX_BOSS,
	200,
	215,
	230,
	245,
	260,
	275,
	290,
	305,
	320,
	335,
	350,
	365,
	380,
	395,
	410,
	425,
	440,
	455,
	470,
	485,
	500,
	515,
	530,
	545,
	560,
	575,
	590,
	605,
	620,
	635,
	650,
	665,
	680,
	695,
	710,
	725,
	740,
	755,
	770,
	785,
	800,
	820,
	840,
	860,
	880,
	900,
	920,
	940,
	960,
	1000,

	//난쟁이의 공(아이템 획득)
	//PS_LUCK, PREFIX_LUCK, 10, 25, 40, 75, PS_WEAPONDMG, PREFIX_WEAPON_DMG,//PS_WEAPONDMG(4)
	//PREFIX_INT,
	100,
	120,
	140,
	160,
	180,
	200,
	220,
	240,
	260,
	300,
	340,
	380,
	420,
	460,
	500,
	540,
	580,
	620,
	660,
	700,
	760,
	820,
	880,
	940,
	1000,
	1060,
	1120,
	1180,
	1240,
	1320,
	1400,
	1480,
	1560,
	1640,
	1720,
	1800,
	1880,
	1960,
	2040,
	2140,
	2240,
	2340,
	2440,
	2540,
	2640,
	2740,
	2840,
	2940,
	3040,
	3200,

	//탐욕의 항아리(골드 획득)
	//PS_GOLDMOD, PREFIX_GOLD, 20, 50, 90, 150, PS_WEAPONDMG, PREFIX_WEAPON_DMG,//PS_WEAPONDMG(5)
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	42,
	44,
	46,
	48,
	50,
	52,
	54,
	56,
	58,
	60,
	62,
	64,
	66,
	68,
	70,
	72,
	74,
	76,
	78,
	80,
	82,
	84,
	86,
	88,
	90,
	92,
	94,
	96,
	100,

	//팬더인형(암흑저항)
	//PS_DARK, PREFIX_DARK_REGIST, 5, 10, 20, 40, PS_ARMOR, SUFFIX_ARMOR,//PS_ARMOR(4)
	//PREFIX_SKILLDMG,
	200,
	215,
	230,
	245,
	260,
	275,
	290,
	305,
	320,
	335,
	350,
	365,
	380,
	395,
	410,
	425,
	440,
	455,
	470,
	485,
	500,
	515,
	530,
	545,
	560,
	575,
	590,
	605,
	620,
	635,
	650,
	665,
	680,
	695,
	710,
	725,
	740,
	755,
	770,
	785,
	800,
	820,
	840,
	860,
	880,
	900,
	920,
	940,
	960,
	1000,

	//스마일 브로치(신성저항)
	//PS_HOLY, PREFIX_HOLY_REGIST, 5, 10, 20, 40, PS_ARMOR, SUFFIX_ARMOR,//PS_ARMOR(5)
	//PREFIX_CRITICAL,
	30,
	32,
	34,
	36,
	38,
	40,
	42,
	44,
	46,
	48,
	50,
	52,
	54,
	56,
	58,
	60,
	62,
	64,
	66,
	68,
	70,
	72,
	74,
	76,
	78,
	80,
	82,
	84,
	86,
	88,
	90,
	92,
	94,
	96,
	98,
	100,
	102,
	104,
	106,
	108,
	110,
	114,
	118,
	122,
	126,
	130,
	134,
	138,
	142,
	150,

	//토르테 악보(디버프 지속)
	//PS_DEBUF, SUFFIX_DEBUF, 10, 20, 30, 50, PS_STR, PREFIX_STR,//PS_STR(3)
	//SUFFIX_CRITICAL,
	200,
	215,
	230,
	245,
	260,
	275,
	290,
	305,
	320,
	335,
	350,
	365,
	380,
	395,
	410,
	425,
	440,
	455,
	470,
	485,
	500,
	515,
	530,
	545,
	560,
	575,
	590,
	605,
	620,
	635,
	650,
	665,
	680,
	695,
	710,
	725,
	740,
	755,
	770,
	785,
	800,
	820,
	840,
	860,
	880,
	900,
	920,
	940,
	960,
	1000,

	//용자의 시계(버프 지속)
	//PS_BUFF, PREFIX_BUFF, 50, 100, 150, 200, PS_STR, PREFIX_STR,//PS_STR(4)
	60,
	64,
	68,
	72,
	76,
	80,
	84,
	88,
	92,
	96,
	100,
	104,
	108,
	112,
	116,
	120,
	124,
	128,
	132,
	136,
	140,
	144,
	148,
	152,
	156,
	160,
	164,
	168,
	172,
	176,
	180,
	184,
	188,
	192,
	196,
	200,
	204,
	208,
	212,
	216,
	224,
	232,
	240,
	248,
	256,
	264,
	272,
	280,
	288,
	300,

	//악마의 뿔피리(리스폰 시간)
	//255, SUFFIX_ENEMYREGEN, 10, 20, 35, 60, PS_STR, PREFIX_STR,//PS_STR(5)
	//SUFFIX_DEBUF,
	40,
	43,
	46,
	49,
	52,
	55,
	58,
	61,
	64,
	67,
	70,
	73,
	76,
	79,
	82,
	85,
	88,
	91,
	94,
	97,
	100,
	103,
	106,
	109,
	112,
	115,
	118,
	121,
	124,
	127,
	130,
	133,
	136,
	139,
	142,
	145,
	148,
	151,
	154,
	157,
	160,
	164,
	168,
	172,
	176,
	180,
	184,
	188,
	192,
	200,

	//아만디움 달걀(포션 회복)
	//PS_POTION, PREFIX_POTION, 30, 60, 100, 150, PS_VIT, PREFIX_VIT,//PS_VIT(4)
	//PREFIX_EXTRA,
	40,
	43,
	46,
	49,
	52,
	55,
	58,
	61,
	64,
	67,
	70,
	73,
	76,
	79,
	82,
	85,
	88,
	91,
	94,
	97,
	100,
	103,
	106,
	109,
	112,
	115,
	118,
	121,
	124,
	127,
	130,
	133,
	136,
	139,
	142,
	145,
	148,
	151,
	154,
	157,
	160,
	164,
	168,
	172,
	176,
	180,
	184,
	188,
	192,
	200,
};
static const unsigned int ringOptionStatValue_builtin[] = {
	//ITEM_RING0,	//사신의 반지(28)
	//저주 제거
	300,
	310,
	320,
	330,
	340,
	350,
	360,
	370,
	380,
	390,
	400,
	410,
	420,
	430,
	440,
	450,
	460,
	470,
	480,
	490,
	500,
	510,
	520,
	530,
	540,
	550,
	560,
	570,
	580,
	590,
	600,
	610,
	620,
	630,
	640,
	650,
	660,
	670,
	680,
	690,
	700,
	710,
	720,
	730,
	740,
	750,
	760,
	770,
	780,
	790,

	//ITEM_RING1,	//통찰의 반지(29)
	//실명 제거
	300,
	310,
	320,
	330,
	340,
	350,
	360,
	370,
	380,
	390,
	400,
	410,
	420,
	430,
	440,
	450,
	460,
	470,
	480,
	490,
	500,
	510,
	520,
	530,
	540,
	550,
	560,
	570,
	580,
	590,
	600,
	610,
	620,
	630,
	640,
	650,
	660,
	670,
	680,
	690,
	700,
	710,
	720,
	730,
	740,
	750,
	760,
	770,
	780,
	790,

	//ITEM_RING2,	//시공의 반지(30)
	//기절 제거
	300,
	310,
	320,
	330,
	340,
	350,
	360,
	370,
	380,
	390,
	400,
	410,
	420,
	430,
	440,
	450,
	460,
	470,
	480,
	490,
	500,
	510,
	520,
	530,
	540,
	550,
	560,
	570,
	580,
	590,
	600,
	610,
	620,
	630,
	640,
	650,
	660,
	670,
	680,
	690,
	700,
	710,
	720,
	730,
	740,
	750,
	760,
	770,
	780,
	790,

	//ITEM_RING3,	//해방의 반지(31)
	//슬로우 제거
	300,
	310,
	320,
	330,
	340,
	350,
	360,
	370,
	380,
	390,
	400,
	410,
	420,
	430,
	440,
	450,
	460,
	470,
	480,
	490,
	500,
	510,
	520,
	530,
	540,
	550,
	560,
	570,
	580,
	590,
	600,
	610,
	620,
	630,
	640,
	650,
	660,
	670,
	680,
	690,
	700,
	710,
	720,
	730,
	740,
	750,
	760,
	770,
	780,
	790,

	//ITEM_RING4,	//산호석 반지(32)
	//독 제거
	300,
	310,
	320,
	330,
	340,
	350,
	360,
	370,
	380,
	390,
	400,
	410,
	420,
	430,
	440,
	450,
	460,
	470,
	480,
	490,
	500,
	510,
	520,
	530,
	540,
	550,
	560,
	570,
	580,
	590,
	600,
	610,
	620,
	630,
	640,
	650,
	660,
	670,
	680,
	690,
	700,
	710,
	720,
	730,
	740,
	750,
	760,
	770,
	780,
	790,

	//ITEM_RING5,	//생환의 반지(33)
	//보스
	200,
	215,
	230,
	245,
	260,
	275,
	290,
	305,
	320,
	335,
	350,
	365,
	380,
	395,
	410,
	425,
	440,
	455,
	470,
	485,
	500,
	515,
	530,
	545,
	560,
	575,
	590,
	605,
	620,
	635,
	650,
	665,
	680,
	695,
	710,
	725,
	740,
	755,
	770,
	785,
	800,
	820,
	840,
	860,
	880,
	900,
	920,
	940,
	960,
	1000,

	//ITEM_RING6,	//희생의 반지(34)
	//추가타격
	40,
	43,
	46,
	49,
	52,
	55,
	58,
	61,
	64,
	67,
	70,
	73,
	76,
	79,
	82,
	85,
	88,
	91,
	94,
	97,
	100,
	103,
	106,
	109,
	112,
	115,
	118,
	121,
	124,
	127,
	130,
	133,
	136,
	139,
	142,
	145,
	148,
	151,
	154,
	157,
	160,
	164,
	168,
	172,
	176,
	180,
	184,
	188,
	192,
	200,

	//ITEM_RING7,	//폭주의 반지(35)
	//공격력 증가
	60,
	64,
	68,
	72,
	76,
	80,
	84,
	88,
	92,
	96,
	100,
	104,
	108,
	112,
	116,
	120,
	124,
	128,
	132,
	136,
	140,
	144,
	148,
	152,
	156,
	160,
	164,
	168,
	172,
	176,
	180,
	184,
	188,
	192,
	196,
	200,
	204,
	208,
	212,
	216,
	224,
	232,
	240,
	248,
	256,
	264,
	272,
	280,
	288,
	300,

	//ITEM_RING8,	//골렘의 반지(36)
	//방어도 증가
	60,
	64,
	68,
	72,
	76,
	80,
	84,
	88,
	92,
	96,
	100,
	104,
	108,
	112,
	116,
	120,
	124,
	128,
	132,
	136,
	140,
	144,
	148,
	152,
	156,
	160,
	164,
	168,
	172,
	176,
	180,
	184,
	188,
	192,
	196,
	200,
	204,
	208,
	212,
	216,
	224,
	232,
	240,
	248,
	256,
	264,
	272,
	280,
	288,
	300,

	//ITEM_RING9,	//광대의 반지(37)
	//회피 증가
	30,
	32,
	34,
	36,
	38,
	40,
	42,
	44,
	46,
	48,
	50,
	52,
	54,
	56,
	58,
	60,
	62,
	64,
	66,
	68,
	70,
	72,
	74,
	76,
	78,
	80,
	82,
	84,
	86,
	88,
	90,
	92,
	94,
	96,
	98,
	100,
	102,
	104,
	106,
	108,
	110,
	114,
	118,
	122,
	126,
	130,
	134,
	138,
	142,
	150,

	//ITEM_RING10,	//원한의 반지(38)
	//관통 증가
	40,
	43,
	46,
	49,
	52,
	55,
	58,
	61,
	64,
	67,
	70,
	73,
	76,
	79,
	82,
	85,
	88,
	91,
	94,
	97,
	100,
	103,
	106,
	109,
	112,
	115,
	118,
	121,
	124,
	127,
	130,
	133,
	136,
	139,
	142,
	145,
	148,
	151,
	154,
	157,
	160,
	164,
	168,
	172,
	176,
	180,
	184,
	188,
	192,
	200,

	//ITEM_RING11,	//신념의 반지(39)
	//체력
	60,
	64,
	68,
	72,
	76,
	80,
	84,
	88,
	92,
	96,
	100,
	104,
	108,
	112,
	116,
	120,
	124,
	128,
	132,
	136,
	140,
	144,
	148,
	152,
	156,
	160,
	164,
	168,
	172,
	176,
	180,
	184,
	188,
	192,
	196,
	200,
	204,
	208,
	212,
	216,
	224,
	232,
	240,
	248,
	256,
	264,
	272,
	280,
	288,
	300,

	//ITEM_RING12,	//광포의 반지(40)
	//스킬 공격력
	200,
	215,
	230,
	245,
	260,
	275,
	290,
	305,
	320,
	335,
	350,
	365,
	380,
	395,
	410,
	425,
	440,
	455,
	470,
	485,
	500,
	515,
	530,
	545,
	560,
	575,
	590,
	605,
	620,
	635,
	650,
	665,
	680,
	695,
	710,
	725,
	740,
	755,
	770,
	785,
	800,
	820,
	840,
	860,
	880,
	900,
	920,
	940,
	960,
	1000,

	//ITEM_RING13,	//승자의 반지(41)
	//치명타 증가
	30,
	32,
	34,
	36,
	38,
	40,
	42,
	44,
	46,
	48,
	50,
	52,
	54,
	56,
	58,
	60,
	62,
	64,
	66,
	68,
	70,
	72,
	74,
	76,
	78,
	80,
	82,
	84,
	86,
	88,
	90,
	92,
	94,
	96,
	98,
	100,
	102,
	104,
	106,
	108,
	110,
	114,
	118,
	122,
	126,
	130,
	134,
	138,
	142,
	150,

	//ITEM_RING14,	//궁극의 반지(42)
	//치명타 데미지 증가
	200,
	215,
	230,
	245,
	260,
	275,
	290,
	305,
	320,
	335,
	350,
	365,
	380,
	395,
	410,
	425,
	440,
	455,
	470,
	485,
	500,
	515,
	530,
	545,
	560,
	575,
	590,
	605,
	620,
	635,
	650,
	665,
	680,
	695,
	710,
	725,
	740,
	755,
	770,
	785,
	800,
	820,
	840,
	860,
	880,
	900,
	920,
	940,
	960,
	1000,

	//ITEM_RING15,	//차원의 반지(43)
	//적 방어도 무시 증가
	40,
	43,
	46,
	49,
	52,
	55,
	58,
	61,
	64,
	67,
	70,
	73,
	76,
	79,
	82,
	85,
	88,
	91,
	94,
	97,
	100,
	103,
	106,
	109,
	112,
	115,
	118,
	121,
	124,
	127,
	130,
	133,
	136,
	139,
	142,
	145,
	148,
	151,
	154,
	157,
	160,
	164,
	168,
	172,
	176,
	180,
	184,
	188,
	192,
	200,

	//ITEM_RING16,	//영화의 반지(44)
	//스킬 재사용 시간 감소
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	42,
	44,
	46,
	48,
	50,
	52,
	54,
	56,
	58,
	60,
	62,
	64,
	66,
	68,
	70,
	72,
	74,
	76,
	78,
	80,
	82,
	84,
	86,
	88,
	90,
	92,
	94,
	96,
	100,

	//ITEM_RING17,	//행운의 반지(45)
	//모든스탯
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	42,
	44,
	46,
	48,
	50,
	52,
	54,
	56,
	58,
	60,
	62,
	64,
	66,
	68,
	70,
	72,
	74,
	76,
	78,
	80,
	82,
	84,
	86,
	88,
	90,
	92,
	94,
	96,
	100,
};
static const unsigned int gemOptionStatValue_builtin[] = {
	//ITEM_GEM_RUBY,	//루비(46)
	//WEAPONDMG
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	41,
	42,
	43,
	44,
	45,
	46,
	47,
	48,
	49,
	50,

	//ITEM_GEM_SAPPHIRE,	//사파이어(47)
	//ARMOR
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	41,
	42,
	43,
	44,
	45,
	46,
	47,
	48,
	49,
	50,

	//ITEM_GEM_AMETHYST,	//자수정(48)
	//VIT
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	41,
	42,
	43,
	44,
	45,
	46,
	47,
	48,
	49,
	50,

	//ITEM_GEM_DIAMOND,	//다이아몬드(49)
	//INT
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	41,
	42,
	43,
	44,
	45,
	46,
	47,
	48,
	49,
	50,

	//ITEM_GEM_PERL,	//진주(50)
	//STR
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	41,
	42,
	43,
	44,
	45,
	46,
	47,
	48,
	49,
	50,

	//ITEM_GEM_EMERALD,	//에메랄드(51)
	//AGI
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	41,
	42,
	43,
	44,
	45,
	46,
	47,
	48,
	49,
	50,
};
static const unsigned int itemUpgradeValue_builtin[] = {
	//1	2 	3 	4 	5 	6 	7 	8 	9 	10 	11 	12 	13 	14 	15 	16 	17 	18 	19 	20 	21 	22 	23 	24 	25 	26 	27 	28 	29 	30 	31 	32 	33 	34 	35 	36 	37 	38 	39 	40 	41 	42 	43 	44 	45 	46 	47 	48 	49 	50 	51 	52 	53 	54 	55 	56 	57 	58 	59 	60 	61 	62 	63 	64 	65 	66 	67 	68 	69 	70 	71 	72 	73 	74 	75 	76 	77 	78 	79 	80 	81 	82 	83 	84 	85 	86 	87 	88 	89 	90 	91 	92 	93 	94 	95 	96 	97 	98 	99 	100 	
10,	11,	12,	13,	14,	15,
11,	12,	13,	14,	15,	16,
12,	13,	14,	15,	16,	17,
13,	14,	15,	16,	17,	18,
14,	15,	16,	17,	18,	19,
15,	16,	17,	18,	19,	20,
16,	17,	18,	19,	20,	21,
17,	18,	19,	20,	21,	22,
18,	19,	20,	21,	22,	23,
19,	20,	21,	22,	23,	24,
20,	21,	22,	23,	24,	25,
21,	22,	23,	24,	25,	26,
22,	23,	24,	25,	26,	27,
23,	24,	25,	26,	27,	28,
24,	25,	26,	27,	28,	29,
25,	26,	27,	28,	29,	30,
26,	27,	28,	29,	30,	31,
27,	28,	29,	30,	31,	32,
28,	29,	30,	31,	32,	33,
29,	30,	31,	32,	33,	34,
30,	31,	32,	33,	34,	35,
31,	32,	33,	34,	35,	36,
32,	33,	34,	35,	36,	37,
33,	34,	35,	36,	37,	38,
10,	11,	12,	13,	14,	15,
11,	12,	13,	14,	15,	16,
12,	13,	14,	15,	16,	17,
13,	14,	15,	16,	17,	18,
14,	15,	16,	17,	18,	19,
15,	16,	17,	18,	19,	20,
16,	17,	18,	19,	20,	21,
17,	18,	19,	20,	21,	22,
18,	19,	20,	21,	22,	23,
19,	20,	21,	22,	23,	24,
20,	21,	22,	23,	24,	25,
21,	22,	23,	24,	25,	26,
22,	23,	24,	25,	26,	27,
23,	24,	25,	26,	27,	28,
24,	25,	26,	27,	28,	29,
25,	26,	27,	28,	29,	30,
26,	27,	28,	29,	30,	31,
27,	28,	29,	30,	31,	32,
28,	29,	30,	31,	32,	33,
29,	30,	31,	32,	33,	34,
30,	31,	32,	33,	34,	35,
31,	32,	33,	34,	35,	36,
32,	33,	34,	35,	36,	37,
33,	34,	35,	36,	37,	38,
10,	11,	12,	13,	14,	15,
11,	12,	13,	14,	15,	16,
12,	13,	14,	15,	16,	17,
13,	14,	15,	16,	17,	18,
14,	15,	16,	17,	18,	19,
15,	16,	17,	18,	19,	20,
16,	17,	18,	19,	20,	21,
17,	18,	19,	20,	21,	22,
18,	19,	20,	21,	22,	23,
19,	20,	21,	22,	23,	24,
20,	21,	22,	23,	24,	25,
21,	22,	23,	24,	25,	26,
22,	23,	24,	25,	26,	27,
23,	24,	25,	26,	27,	28,
24,	25,	26,	27,	28,	29,
25,	26,	27,	28,	29,	30,
26,	27,	28,	29,	30,	31,
27,	28,	29,	30,	31,	32,
28,	29,	30,	31,	32,	33,
29,	30,	31,	32,	33,	34,
30,	31,	32,	33,	34,	35,
31,	32,	33,	34,	35,	36,
32,	33,	34,	35,	36,	37,
33,	34,	35,	36,	37,	38,
1,	2,	3,	4,	5,	6,
2,	3,	4,	5,	6,	7,
3,	4,	5,	6,	7,	8,
4,	5,	6,	7,	8,	9,
5,	6,	7,	8,	9,	10,
6,	7,	8,	9,	10,	11,
7,	8,	9,	10,	11,	12,
8,	9,	10,	11,	12,	13,
9,	10,	11,	12,	13,	14,
10,	11,	12,	13,	14,	15,
11,	12,	13,	14,	15,	16,
12,	13,	14,	15,	16,	17,
13,	14,	15,	16,	17,	18,
14,	15,	16,	17,	18,	19,
15,	16,	17,	18,	19,	20,
16,	17,	18,	19,	20,	21,
17,	18,	19,	20,	21,	22,
18,	19,	20,	21,	22,	23,
19,	20,	21,	22,	23,	24,
20,	21,	22,	23,	24,	25,
21,	22,	23,	24,	25,	26,
22,	23,	24,	25,	26,	27,
23,	24,	25,	26,	27,	28,
24,	25,	26,	27,	28,	29,
1,	2,	3,	4,	5,	6,
2,	3,	4,	5,	6,	7,
3,	4,	5,	6,	7,	8,
4,	5,	6,	7,	8,	9,
5,	6,	7,	8,	9,	10,
6,	7,	8,	9,	10,	11,
7,	8,	9,	10,	11,	12,
8,	9,	10,	11,	12,	13,
9,	10,	11,	12,	13,	14,
10,	11,	12,	13,	14,	15,
11,	12,	13,	14,	15,	16,
12,	13,	14,	15,	16,	17,
13,	14,	15,	16,	17,	18,
14,	15,	16,	17,	18,	19,
15,	16,	17,	18,	19,	20,
16,	17,	18,	19,	20,	21,
17,	18,	19,	20,	21,	22,
18,	19,	20,	21,	22,	23,
19,	20,	21,	22,	23,	24,
20,	21,	22,	23,	24,	25,
21,	22,	23,	24,	25,	26,
22,	23,	24,	25,	26,	27,
23,	24,	25,	26,	27,	28,
24,	25,	26,	27,	28,	29,
1,	2,	3,	4,	5,	6,
2,	3,	4,	5,	6,	7,
3,	4,	5,	6,	7,	8,
4,	5,	6,	7,	8,	9,
5,	6,	7,	8,	9,	10,
6,	7,	8,	9,	10,	11,
7,	8,	9,	10,	11,	12,
8,	9,	10,	11,	12,	13,
9,	10,	11,	12,	13,	14,
10,	11,	12,	13,	14,	15,
11,	12,	13,	14,	15,	16,
12,	13,	14,	15,	16,	17,
13,	14,	15,	16,	17,	18,
14,	15,	16,	17,	18,	19,
15,	16,	17,	18,	19,	20,
16,	17,	18,	19,	20,	21,
17,	18,	19,	20,	21,	22,
18,	19,	20,	21,	22,	23,
19,	20,	21,	22,	23,	24,
20,	21,	22,	23,	24,	25,
21,	22,	23,	24,	25,	26,
22,	23,	24,	25,	26,	27,
23,	24,	25,	26,	27,	28,
24,	25,	26,	27,	28,	29,
1,	2,	3,	4,	5,	6,
2,	3,	4,	5,	6,	7,
3,	4,	5,	6,	7,	8,
4,	5,	6,	7,	8,	9,
5,	6,	7,	8,	9,	10,
6,	7,	8,	9,	10,	11,
7,	8,	9,	10,	11,	12,
8,	9,	10,	11,	12,	13,
9,	10,	11,	12,	13,	14,
10,	11,	12,	13,	14,	15,
11,	12,	13,	14,	15,	16,
12,	13,	14,	15,	16,	17,
13,	14,	15,	16,	17,	18,
14,	15,	16,	17,	18,	19,
15,	16,	17,	18,	19,	20,
16,	17,	18,	19,	20,	21,
17,	18,	19,	20,	21,	22,
18,	19,	20,	21,	22,	23,
19,	20,	21,	22,	23,	24,
20,	21,	22,	23,	24,	25,
21,	22,	23,	24,	25,	26,
22,	23,	24,	25,	26,	27,
23,	24,	25,	26,	27,	28,
24,	25,	26,	27,	28,	29,
1,	2,	3,	4,	5,	6,
2,	3,	4,	5,	6,	7,
3,	4,	5,	6,	7,	8,
4,	5,	6,	7,	8,	9,
5,	6,	7,	8,	9,	10,
6,	7,	8,	9,	10,	11,
7,	8,	9,	10,	11,	12,
8,	9,	10,	11,	12,	13,
9,	10,	11,	12,	13,	14,
10,	11,	12,	13,	14,	15,
11,	12,	13,	14,	15,	16,
12,	13,	14,	15,	16,	17,
13,	14,	15,	16,	17,	18,
14,	15,	16,	17,	18,	19,
15,	16,	17,	18,	19,	20,
16,	17,	18,	19,	20,	21,
17,	18,	19,	20,	21,	22,
18,	19,	20,	21,	22,	23,
19,	20,	21,	22,	23,	24,
20,	21,	22,	23,	24,	25,
21,	22,	23,	24,	25,	26,
22,	23,	24,	25,	26,	27,
23,	24,	25,	26,	27,	28,
24,	25,	26,	27,	28,	29,
1,	2,	3,	4,	5,	6,
2,	3,	4,	5,	6,	7,
3,	4,	5,	6,	7,	8,
4,	5,	6,	7,	8,	9,
5,	6,	7,	8,	9,	10,
6,	7,	8,	9,	10,	11,
7,	8,	9,	10,	11,	12,
8,	9,	10,	11,	12,	13,
9,	10,	11,	12,	13,	14,
10,	11,	12,	13,	14,	15,
11,	12,	13,	14,	15,	16,
12,	13,	14,	15,	16,	17,
13,	14,	15,	16,	17,	18,
14,	15,	16,	17,	18,	19,
15,	16,	17,	18,	19,	20,
16,	17,	18,	19,	20,	21,
17,	18,	19,	20,	21,	22,
18,	19,	20,	21,	22,	23,
19,	20,	21,	22,	23,	24,
20,	21,	22,	23,	24,	25,
21,	22,	23,	24,	25,	26,
22,	23,	24,	25,	26,	27,
23,	24,	25,	26,	27,	28,
24,	25,	26,	27,	28,	29,
1,	2,	3,	4,	5,	6,
2,	3,	4,	5,	6,	7,
3,	4,	5,	6,	7,	8,
4,	5,	6,	7,	8,	9,
5,	6,	7,	8,	9,	10,
6,	7,	8,	9,	10,	11,
7,	8,	9,	10,	11,	12,
8,	9,	10,	11,	12,	13,
9,	10,	11,	12,	13,	14,
10,	11,	12,	13,	14,	15,
11,	12,	13,	14,	15,	16,
12,	13,	14,	15,	16,	17,
13,	14,	15,	16,	17,	18,
14,	15,	16,	17,	18,	19,
15,	16,	17,	18,	19,	20,
16,	17,	18,	19,	20,	21,
17,	18,	19,	20,	21,	22,
18,	19,	20,	21,	22,	23,
19,	20,	21,	22,	23,	24,
20,	21,	22,	23,	24,	25,
21,	22,	23,	24,	25,	26,
22,	23,	24,	25,	26,	27,
23,	24,	25,	26,	27,	28,
24,	25,	26,	27,	28,	29,
1,	2,	3,	4,	5,	6,
2,	3,	4,	5,	6,	7,
3,	4,	5,	6,	7,	8,
4,	5,	6,	7,	8,	9,
5,	6,	7,	8,	9,	10,
6,	7,	8,	9,	10,	11,
7,	8,	9,	10,	11,	12,
8,	9,	10,	11,	12,	13,
9,	10,	11,	12,	13,	14,
10,	11,	12,	13,	14,	15,
11,	12,	13,	14,	15,	16,
12,	13,	14,	15,	16,	17,
13,	14,	15,	16,	17,	18,
14,	15,	16,	17,	18,	19,
15,	16,	17,	18,	19,	20,
16,	17,	18,	19,	20,	21,
17,	18,	19,	20,	21,	22,
18,	19,	20,	21,	22,	23,
19,	20,	21,	22,	23,	24,
20,	21,	22,	23,	24,	25,
21,	22,	23,	24,	25,	26,
22,	23,	24,	25,	26,	27,
23,	24,	25,	26,	27,	28,
24,	25,	26,	27,	28,	29,
1,	2,	3,	4,	5,	6,
2,	3,	4,	5,	6,	7,
3,	4,	5,	6,	7,	8,
4,	5,	6,	7,	8,	9,
5,	6,	7,	8,	9,	10,
6,	7,	8,	9,	10,	11,
7,	8,	9,	10,	11,	12,
8,	9,	10,	11,	12,	13,
9,	10,	11,	12,	13,	14,
10,	11,	12,	13,	14,	15,
11,	12,	13,	14,	15,	16,
12,	13,	14,	15,	16,	17,
13,	14,	15,	16,	17,	18,
14,	15,	16,	17,	18,	19,
15,	16,	17,	18,	19,	20,
16,	17,	18,	19,	20,	21,
17,	18,	19,	20,	21,	22,
18,	19,	20,	21,	22,	23,
19,	20,	21,	22,	23,	24,
20,	21,	22,	23,	24,	25,
21,	22,	23,	24,	25,	26,
22,	23,	24,	25,	26,	27,
23,	24,	25,	26,	27,	28,
24,	25,	26,	27,	28,	29,
1,	2,	3,	4,	5,	6,
2,	3,	4,	5,	6,	7,
3,	4,	5,	6,	7,	8,
4,	5,	6,	7,	8,	9,
5,	6,	7,	8,	9,	10,
6,	7,	8,	9,	10,	11,
7,	8,	9,	10,	11,	12,
8,	9,	10,	11,	12,	13,
9,	10,	11,	12,	13,	14,
10,	11,	12,	13,	14,	15,
11,	12,	13,	14,	15,	16,
12,	13,	14,	15,	16,	17,
13,	14,	15,	16,	17,	18,
14,	15,	16,	17,	18,	19,
15,	16,	17,	18,	19,	20,
16,	17,	18,	19,	20,	21,
17,	18,	19,	20,	21,	22,
18,	19,	20,	21,	22,	23,
19,	20,	21,	22,	23,	24,
20,	21,	22,	23,	24,	25,
21,	22,	23,	24,	25,	26,
22,	23,	24,	25,	26,	27,
23,	24,	25,	26,	27,	28,
24,	25,	26,	27,	28,	29,
1,	2,	3,	4,	5,	6,
2,	3,	4,	5,	6,	7,
3,	4,	5,	6,	7,	8,
4,	5,	6,	7,	8,	9,
5,	6,	7,	8,	9,	10,
6,	7,	8,	9,	10,	11,
7,	8,	9,	10,	11,	12,
8,	9,	10,	11,	12,	13,
9,	10,	11,	12,	13,	14,
10,	11,	12,	13,	14,	15,
11,	12,	13,	14,	15,	16,
12,	13,	14,	15,	16,	17,
13,	14,	15,	16,	17,	18,
14,	15,	16,	17,	18,	19,
15,	16,	17,	18,	19,	20,
16,	17,	18,	19,	20,	21,
17,	18,	19,	20,	21,	22,
18,	19,	20,	21,	22,	23,
19,	20,	21,	22,	23,	24,
20,	21,	22,	23,	24,	25,
21,	22,	23,	24,	25,	26,
22,	23,	24,	25,	26,	27,
23,	24,	25,	26,	27,	28,
24,	25,	26,	27,	28,	29,
1,	2,	3,	4,	5,	6,
2,	3,	4,	5,	6,	7,
3,	4,	5,	6,	7,	8,
4,	5,	6,	7,	8,	9,
5,	6,	7,	8,	9,	10,
6,	7,	8,	9,	10,	11,
7,	8,	9,	10,	11,	12,
8,	9,	10,	11,	12,	13,
9,	10,	11,	12,	13,	14,
10,	11,	12,	13,	14,	15,
11,	12,	13,	14,	15,	16,
12,	13,	14,	15,	16,	17,
13,	14,	15,	16,	17,	18,
14,	15,	16,	17,	18,	19,
15,	16,	17,	18,	19,	20,
16,	17,	18,	19,	20,	21,
17,	18,	19,	20,	21,	22,
18,	19,	20,	21,	22,	23,
19,	20,	21,	22,	23,	24,
20,	21,	22,	23,	24,	25,
21,	22,	23,	24,	25,	26,
22,	23,	24,	25,	26,	27,
23,	24,	25,	26,	27,	28,
24,	25,	26,	27,	28,	29,
1,	2,	3,	4,	5,	6,
2,	3,	4,	5,	6,	7,
3,	4,	5,	6,	7,	8,
4,	5,	6,	7,	8,	9,
5,	6,	7,	8,	9,	10,
6,	7,	8,	9,	10,	11,
7,	8,	9,	10,	11,	12,
8,	9,	10,	11,	12,	13,
9,	10,	11,	12,	13,	14,
10,	11,	12,	13,	14,	15,
11,	12,	13,	14,	15,	16,
12,	13,	14,	15,	16,	17,
13,	14,	15,	16,	17,	18,
14,	15,	16,	17,	18,	19,
15,	16,	17,	18,	19,	20,
16,	17,	18,	19,	20,	21,
17,	18,	19,	20,	21,	22,
18,	19,	20,	21,	22,	23,
19,	20,	21,	22,	23,	24,
20,	21,	22,	23,	24,	25,
21,	22,	23,	24,	25,	26,
22,	23,	24,	25,	26,	27,
23,	24,	25,	26,	27,	28,
24,	25,	26,	27,	28,	29,
1,	2,	3,	4,	5,	6,
2,	3,	4,	5,	6,	7,
3,	4,	5,	6,	7,	8,
4,	5,	6,	7,	8,	9,
5,	6,	7,	8,	9,	10,
6,	7,	8,	9,	10,	11,
7,	8,	9,	10,	11,	12,
8,	9,	10,	11,	12,	13,
9,	10,	11,	12,	13,	14,
10,	11,	12,	13,	14,	15,
11,	12,	13,	14,	15,	16,
12,	13,	14,	15,	16,	17,
13,	14,	15,	16,	17,	18,
14,	15,	16,	17,	18,	19,
15,	16,	17,	18,	19,	20,
16,	17,	18,	19,	20,	21,
17,	18,	19,	20,	21,	22,
18,	19,	20,	21,	22,	23,
19,	20,	21,	22,	23,	24,
20,	21,	22,	23,	24,	25,
21,	22,	23,	24,	25,	26,
22,	23,	24,	25,	26,	27,
23,	24,	25,	26,	27,	28,
24,	25,	26,	27,	28,	29,
1,	2,	3,	4,	5,	6,
2,	3,	4,	5,	6,	7,
3,	4,	5,	6,	7,	8,
4,	5,	6,	7,	8,	9,
5,	6,	7,	8,	9,	10,
6,	7,	8,	9,	10,	11,
7,	8,	9,	10,	11,	12,
8,	9,	10,	11,	12,	13,
9,	10,	11,	12,	13,	14,
10,	11,	12,	13,	14,	15,
11,	12,	13,	14,	15,	16,
12,	13,	14,	15,	16,	17,
13,	14,	15,	16,	17,	18,
14,	15,	16,	17,	18,	19,
15,	16,	17,	18,	19,	20,
16,	17,	18,	19,	20,	21,
17,	18,	19,	20,	21,	22,
18,	19,	20,	21,	22,	23,
19,	20,	21,	22,	23,	24,
20,	21,	22,	23,	24,	25,
21,	22,	23,	24,	25,	26,
22,	23,	24,	25,	26,	27,
23,	24,	25,	26,	27,	28,
24,	25,	26,	27,	28,	29,


};
static const unsigned char itemRatio_builtin[] = {
	100, //EQUIP_WEAPON = 0,		//무기
	50, //EQUIP_HELM,		//투구
	50, //EQUIP_ARMOR,	//갑옷
	50, //EQUIP_PANTS,		//바지
	50, //EQUIP_GLOVE,			//장갑
	50, //EQUIP_BOOTS,		//신발
	50, //EQUIP_NECK,			//목걸이
	50, //EQUIP_RING,		//반지
};
static const unsigned short itemPow_builtin[] = {
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	41,
	42,
	43,
	44,
	45,
	46,
	47,
	48,
	49,
	50,
	51,
	52,
	53,
	54,
	55,
	56,
	57,
	58,
	59,
	60,
	61,
	62,
	63,
	64,
	65,
	66,
	67,
	68,
	69,
	70,
	71,
	72,
	73,
	74,
	75,
	76,
	77,
	78,
	79,
	80,
	81,
	82,
	83,
	84,
	85,
	86,
	87,
	88,
	89,
	90,
	91,
	92,
	93,
	94,
	95,
	96,
	97,
	98,
	99,
	100,
	101,
	102,
	103,
	104,
	105,
	106,
	107,
	108,
	109,
	110,
	111,
	112,
	113,
	114,
	115,
	116,
	117,
	118,
	119,
	120,
	121,
	122,
	123,
	124,
	125,
	126,
	127,
	128,
	129,
	130,
	131,
	132,
	133,
	134,
	135,
	136,
	137,
	138,
	139,
	140,
	141,
	142,
	143,
	144,
	145,
	146,
	147,
	148,
	149,
	150,
	151,
	152,
	153,
	154,
	155,
	156,
	157,
	158,
	159,
	160,
	161,
	162,
	163,
	164,
	165,
	166,
	167,
	168,
	169,
	170,
	171,
	172,
	173,
	174,
	175,
	176,
	177,
	178,
	179,
	180,
	181,
	182,
	183,
	184,
	185,
	186,
	187,
	188,
	189,
	190,
	191,
	192,
	193,
	194,
	195,
	196,
	197,
	198,
	199,
	200,
	201,
	202,
	203,
	204,
	205,
	206,
	207,
	208,
	209,
	210,
	211,
	212,
	213,
	214,
	215,
	216,
	217,
	218,
	219,
	220,
	221,
	222,
	223,
	224,
	225,
	226,
	227,
	228,
	229,
};
static const unsigned char itemLv_builtin[] = {
	//검
	4, 14, 24, 33, 42, 51, 59, 67,
	//총
	4, 14, 23, 32, 41, 49, 57, 65,
	//부메랑
	4, 15, 25, 35, 44, 53, 62, 70,

	//헬멧
	6, 15, 25, 34, 43, 52, 60, 68,
	//모자
	6, 15, 24, 33, 42, 51, 59, 67,
	//두건
	6, 16, 26, 36, 45, 54, 63, 71,

	//갑옷
	2, 9, 19, 29, 38, 47, 55, 63,
	//조끼
	2, 8, 18, 28, 37, 46, 54, 62,
	//코트
	2, 10, 20, 30, 39, 49, 57, 65,

	//건틀렛
	7, 17, 27, 36, 45, 53, 61, 69,
	//팔찌
	7, 16, 26, 35, 44, 52, 60, 68,
	//장갑
	7, 18, 28, 37, 46, 55, 64, 72,

	//킬트
	3, 11, 21, 31, 40, 49, 57, 65,
	//스커트
	3, 10, 20, 30, 39, 47, 55, 63,
	//팬츠
	3, 12, 22, 32, 41, 51, 59, 67,

	//장화
	5, 13, 23, 32, 41, 50, 58, 66,
	//신발
	5, 13, 22, 31, 40, 48, 56, 64,
	//부츠
	5, 14, 24, 34, 43, 52, 61, 69,
};
static const unsigned char itemStat_builtin[] = {
	//검
	7, 24, 41, 56, 71, 87, 100, 114,
	//총
	7, 24, 39, 54, 70, 83, 97, 111,
	//부메랑
	7, 26, 43, 60, 75, 90, 105, 119,

	//헬멧
	10, 26, 43, 58, 73, 88, 102, 116,
	//모자
	10, 26, 41, 56, 71, 87, 100, 114,
	//두건
	10, 27, 44, 61, 77, 92, 107, 121,

	//갑옷
	3, 15, 32, 49, 65, 80, 94, 107,
	//조끼
	3, 14, 31, 48, 63, 78, 92, 105,
	//코트
	3, 17, 34, 51, 66, 83, 97, 111,

	//건틀렛
	12, 29, 46, 61, 77, 90, 104, 117,
	//팔찌
	12, 27, 44, 60, 75, 88, 102, 116,
	//장갑
	12, 31, 48, 63, 78, 94, 109, 122,

	//킬트
	5, 19, 36, 53, 68, 83, 97, 111,
	//스커트
	5, 17, 34, 51, 66, 80, 94, 107,
	//팬츠
	5, 20, 37, 54, 70, 87, 100, 114,

	//장화
	9, 22, 39, 54, 70, 85, 99, 112,
	//신발
	9, 22, 37, 53, 68, 82, 95, 109,
	//부츠
	9, 24, 41, 58, 73, 88, 104, 117,
};
static const unsigned int enchantData_builtin[] = {
	//검 : ITEM_SWORD
	ITEM_IRON_LV1, 6, 150 + ITEM_WOOD_LV1, 6, 255, 0,	//연습용몽둥이
	ITEM_IRON_LV1, 8, 150 + ITEM_WOOD_LV1, 8, 200 + ITEM_ESSENCE0, 1,	//고급
	ITEM_IRON_LV1, 10, 150 + ITEM_WOOD_LV1, 10, 200 + ITEM_ESSENCE0, 1,	//희귀
	ITEM_IRON_LV1, 10, 150 + ITEM_WOOD_LV1, 10, 200 + ITEM_ESSENCE0, 1,	//세트
	ITEM_IRON_LV2, 6, 150 + ITEM_WOOD_LV2, 6, 255, 0,	//롱소드
	ITEM_IRON_LV2, 8, 150 + ITEM_WOOD_LV2, 8, 200 + ITEM_ESSENCE2, 1,	//고급
	ITEM_IRON_LV2, 10, 150 + ITEM_WOOD_LV2, 10, 200 + ITEM_ESSENCE2, 1,	//희귀
	ITEM_IRON_LV2, 10, 150 + ITEM_WOOD_LV2, 10, 200 + ITEM_ESSENCE2, 1,	//세트
	ITEM_IRON_LV3, 6, 150 + ITEM_WOOD_LV3, 6, 255, 0,	//처형자의 검
	ITEM_IRON_LV3, 8, 150 + ITEM_WOOD_LV3, 8, 200 + ITEM_ESSENCE4, 1,	//고급
	ITEM_IRON_LV3, 10, 150 + ITEM_WOOD_LV3, 10, 200 + ITEM_ESSENCE4, 2,	//희귀
	ITEM_IRON_LV3, 10, 150 + ITEM_WOOD_LV3, 10, 200 + ITEM_ESSENCE6, 1,	//세트
	ITEM_IRON_LV3, 12, 150 + ITEM_WOOD_LV3, 12, 200 + ITEM_ESSENCE32, 1,	//파멸의 참마도
	ITEM_IRON_LV4, 6, 150 + ITEM_WOOD_LV4, 6, 255, 0,	//추적자의 검
	ITEM_IRON_LV4, 8, 150 + ITEM_WOOD_LV4, 8, 200 + ITEM_ESSENCE8, 1,	//고급
	ITEM_IRON_LV4, 10, 150 + ITEM_WOOD_LV4, 10, 200 + ITEM_ESSENCE8, 2,	//희귀
	ITEM_IRON_LV4, 10, 150 + ITEM_WOOD_LV4, 10, 200 + ITEM_ESSENCE10, 1,	//세트
	ITEM_IRON_LV4, 12, 150 + ITEM_WOOD_LV4, 12, 200 + ITEM_ESSENCE34, 1,	//격노의 양날검
	ITEM_IRON_LV5, 6, 150 + ITEM_WOOD_LV5, 6, 255, 0,	//수호자의 검
	ITEM_IRON_LV5, 8, 150 + ITEM_WOOD_LV5, 8, 200 + ITEM_ESSENCE13, 1,	//고급
	ITEM_IRON_LV5, 10, 150 + ITEM_WOOD_LV5, 10, 200 + ITEM_ESSENCE13, 2,	//희귀
	ITEM_IRON_LV5, 10, 150 + ITEM_WOOD_LV5, 10, 200 + ITEM_ESSENCE16, 1,	//세트
	ITEM_IRON_LV5, 12, 150 + ITEM_WOOD_LV5, 12, 200 + ITEM_ESSENCE35, 1,	//왕가의 수호자
	ITEM_IRON_LV6, 6, 150 + ITEM_WOOD_LV6, 6, 255, 0,	//나찰의 검
	ITEM_IRON_LV6, 8, 150 + ITEM_WOOD_LV6, 8, 200 + ITEM_ESSENCE18, 1,	//고급
	ITEM_IRON_LV6, 10, 150 + ITEM_WOOD_LV6, 10, 200 + ITEM_ESSENCE18, 2,	//희귀
	ITEM_IRON_LV6, 10, 150 + ITEM_WOOD_LV6, 10, 200 + ITEM_ESSENCE20, 1,	//세트
	ITEM_IRON_LV6, 12, 150 + ITEM_WOOD_LV6, 12, 200 + ITEM_ESSENCE38, 1,	//소울 크래셔
	ITEM_IRON_LV7, 6, 150 + ITEM_WOOD_LV7, 6, 255, 0,	//차원의 검
	ITEM_IRON_LV7, 8, 150 + ITEM_WOOD_LV7, 8, 200 + ITEM_ESSENCE26, 1,	//고급
	ITEM_IRON_LV7, 10, 150 + ITEM_WOOD_LV7, 10, 200 + ITEM_ESSENCE26, 2,	//희귀
	ITEM_IRON_LV7, 10, 150 + ITEM_WOOD_LV7, 10, 200 + ITEM_ESSENCE22, 1,	//세트
	ITEM_IRON_LV7, 12, 150 + ITEM_WOOD_LV7, 12, 200 + ITEM_ESSENCE40, 1,	//천공의 검
	ITEM_IRON_LV7, 15, 150 + ITEM_WOOD_LV7, 15, 200 + ITEM_ESSENCE42, 1,	//스타더스트
	ITEM_IRON_LV8, 6, 150 + ITEM_WOOD_LV8, 6, 255, 0,	//드래곤 클로우
	ITEM_IRON_LV8, 8, 150 + ITEM_WOOD_LV8, 8, 200 + ITEM_ESSENCE28, 1,	//고급
	ITEM_IRON_LV8, 10, 150 + ITEM_WOOD_LV8, 10, 200 + ITEM_ESSENCE28, 2,	//희귀
	ITEM_IRON_LV8, 10, 150 + ITEM_WOOD_LV8, 10, 200 + ITEM_ESSENCE30, 1,	//세트
	ITEM_IRON_LV8, 12, 150 + ITEM_WOOD_LV8, 12, 200 + ITEM_ESSENCE43, 1,	//황룡의 어금니
	ITEM_IRON_LV8, 15, 150 + ITEM_WOOD_LV8, 15, 200 + ITEM_ESSENCE44, 1,	//신룡강마검

	//총 : ITEM_GUN
	ITEM_IRON_LV1, 4, 50 + ITEM_LEATHER_LV1, 4, 255, 0,	//발화식 총
	ITEM_IRON_LV1, 6, 50 + ITEM_LEATHER_LV1, 6, 200 + ITEM_ESSENCE1, 1,	//고급
	ITEM_IRON_LV1, 8, 50 + ITEM_LEATHER_LV1, 8, 200 + ITEM_ESSENCE1, 1,	//희귀
	ITEM_IRON_LV1, 8, 50 + ITEM_LEATHER_LV1, 8, 200 + ITEM_ESSENCE1, 1,	//세트
	ITEM_IRON_LV2, 4, 50 + ITEM_LEATHER_LV2, 4, 255, 0,	//리볼버 파이슨
	ITEM_IRON_LV2, 6, 50 + ITEM_LEATHER_LV2, 6, 200 + ITEM_ESSENCE2, 1,	//고급
	ITEM_IRON_LV2, 8, 50 + ITEM_LEATHER_LV2, 8, 200 + ITEM_ESSENCE2, 1,	//희귀
	ITEM_IRON_LV2, 8, 50 + ITEM_LEATHER_LV2, 8, 200 + ITEM_ESSENCE2, 1,	//세트
	ITEM_IRON_LV3, 4, 50 + ITEM_LEATHER_LV3, 4, 255, 0,	//45구경 오토건
	ITEM_IRON_LV3, 6, 50 + ITEM_LEATHER_LV3, 6, 200 + ITEM_ESSENCE5, 1,	//고급
	ITEM_IRON_LV3, 8, 50 + ITEM_LEATHER_LV3, 8, 200 + ITEM_ESSENCE5, 2,	//희귀
	ITEM_IRON_LV3, 8, 50 + ITEM_LEATHER_LV3, 8, 200 + ITEM_ESSENCE6, 1,	//세트
	ITEM_IRON_LV3, 8, 50 + ITEM_LEATHER_LV3, 8, 200 + ITEM_ESSENCE32, 1,	//사일런트 킬러
	ITEM_IRON_LV4, 4, 50 + ITEM_LEATHER_LV4, 4, 255, 0,	//고져스 건
	ITEM_IRON_LV4, 6, 50 + ITEM_LEATHER_LV4, 6, 200 + ITEM_ESSENCE8, 1,	//고급
	ITEM_IRON_LV4, 8, 50 + ITEM_LEATHER_LV4, 8, 200 + ITEM_ESSENCE8, 2,	//희귀
	ITEM_IRON_LV4, 8, 50 + ITEM_LEATHER_LV4, 8, 200 + ITEM_ESSENCE12, 1,	//세트
	ITEM_IRON_LV4, 12, 50 + ITEM_LEATHER_LV4, 12, 200 + ITEM_ESSENCE34, 1,	//럭셔리 캐논
	ITEM_IRON_LV5, 4, 50 + ITEM_LEATHER_LV5, 4, 255, 0,	//회천마도총
	ITEM_IRON_LV5, 6, 50 + ITEM_LEATHER_LV5, 6, 200 + ITEM_ESSENCE15, 1,	//고급
	ITEM_IRON_LV5, 8, 50 + ITEM_LEATHER_LV5, 8, 200 + ITEM_ESSENCE15, 2,	//희귀
	ITEM_IRON_LV5, 8, 50 + ITEM_LEATHER_LV5, 8, 200 + ITEM_ESSENCE16, 1,	//세트
	ITEM_IRON_LV5, 12, 50 + ITEM_LEATHER_LV5, 12, 200 + ITEM_ESSENCE35, 1,	//마도머신건
	ITEM_IRON_LV6, 4, 50 + ITEM_LEATHER_LV6, 4, 255, 0,	//태양의 총
	ITEM_IRON_LV6, 6, 50 + ITEM_LEATHER_LV6, 6, 200 + ITEM_ESSENCE19, 1,	//고급
	ITEM_IRON_LV6, 8, 50 + ITEM_LEATHER_LV6, 8, 200 + ITEM_ESSENCE19, 2,	//희귀
	ITEM_IRON_LV6, 8, 50 + ITEM_LEATHER_LV6, 8, 200 + ITEM_ESSENCE21, 1,	//세트
	ITEM_IRON_LV6, 12, 50 + ITEM_LEATHER_LV6, 12, 200 + ITEM_ESSENCE38, 1,	//슈퍼노바
	ITEM_IRON_LV7, 4, 50 + ITEM_LEATHER_LV7, 4, 255, 0,	//헬파이어 건
	ITEM_IRON_LV7, 6, 50 + ITEM_LEATHER_LV7, 6, 200 + ITEM_ESSENCE26, 1,	//고급
	ITEM_IRON_LV7, 8, 50 + ITEM_LEATHER_LV7, 8, 200 + ITEM_ESSENCE26, 2,	//희귀
	ITEM_IRON_LV7, 8, 50 + ITEM_LEATHER_LV7, 8, 200 + ITEM_ESSENCE23, 1,	//세트
	ITEM_IRON_LV7, 12, 50 + ITEM_LEATHER_LV7, 12, 200 + ITEM_ESSENCE40, 1,	//인페르노 캐논
	ITEM_IRON_LV7, 15, 50 + ITEM_LEATHER_LV7, 15, 200 + ITEM_ESSENCE42, 1,	//마룡열화포
	ITEM_IRON_LV8, 4, 50 + ITEM_LEATHER_LV8, 4, 255, 0,	//크로스 파이어
	ITEM_IRON_LV8, 6, 50 + ITEM_LEATHER_LV8, 6, 200 + ITEM_ESSENCE29, 1,	//고급
	ITEM_IRON_LV8, 8, 50 + ITEM_LEATHER_LV8, 8, 200 + ITEM_ESSENCE29, 2,	//희귀
	ITEM_IRON_LV8, 8, 50 + ITEM_LEATHER_LV8, 8, 200 + ITEM_ESSENCE30, 1,	//세트
	ITEM_IRON_LV8, 12, 50 + ITEM_LEATHER_LV8, 12, 200 + ITEM_ESSENCE43, 1,	//테스타먼트
	ITEM_IRON_LV8, 15, 50 + ITEM_LEATHER_LV8, 15, 200 + ITEM_ESSENCE44, 1,	//라그나로크

	//부메랑 : ITEM_BOOMERANG
	150 + ITEM_WOOD_LV1, 4, 50 + ITEM_LEATHER_LV1, 4, 255, 0,	//사냥용 부메랑
	150 + ITEM_WOOD_LV1, 6, 50 + ITEM_LEATHER_LV1, 6, 200 + ITEM_ESSENCE1, 1,	//고급
	150 + ITEM_WOOD_LV1, 8, 50 + ITEM_LEATHER_LV1, 8, 200 + ITEM_ESSENCE1, 1,	//희귀
	150 + ITEM_WOOD_LV1, 8, 50 + ITEM_LEATHER_LV1, 8, 200 + ITEM_ESSENCE1, 1,	//세트
	150 + ITEM_WOOD_LV2, 4, 50 + ITEM_LEATHER_LV2, 4, 255, 0,	//슬라이서
	150 + ITEM_WOOD_LV2, 6, 50 + ITEM_LEATHER_LV2, 6, 200 + ITEM_ESSENCE3, 1,	//고급
	150 + ITEM_WOOD_LV2, 8, 50 + ITEM_LEATHER_LV2, 8, 200 + ITEM_ESSENCE3, 1,	//희귀
	150 + ITEM_WOOD_LV2, 8, 50 + ITEM_LEATHER_LV2, 8, 200 + ITEM_ESSENCE3, 1,	//세트
	150 + ITEM_WOOD_LV3, 4, 50 + ITEM_LEATHER_LV3, 4, 255, 0,	//강철 부메랑
	150 + ITEM_WOOD_LV3, 6, 50 + ITEM_LEATHER_LV3, 6, 200 + ITEM_ESSENCE5, 1,	//고급
	150 + ITEM_WOOD_LV3, 8, 50 + ITEM_LEATHER_LV3, 8, 200 + ITEM_ESSENCE5, 2,	//희귀
	150 + ITEM_WOOD_LV3, 8, 50 + ITEM_LEATHER_LV3, 8, 200 + ITEM_ESSENCE7, 1,	//세트
	150 + ITEM_WOOD_LV3, 8, 50 + ITEM_LEATHER_LV3, 8, 200 + ITEM_ESSENCE32, 1,	//윈드 슬래셔
	150 + ITEM_WOOD_LV4, 4, 50 + ITEM_LEATHER_LV4, 4, 255, 0,	//트라이 엣지
	150 + ITEM_WOOD_LV4, 6, 50 + ITEM_LEATHER_LV4, 6, 200 + ITEM_ESSENCE9, 1,	//고급
	150 + ITEM_WOOD_LV4, 8, 50 + ITEM_LEATHER_LV4, 8, 200 + ITEM_ESSENCE9, 2,	//희귀
	150 + ITEM_WOOD_LV4, 8, 50 + ITEM_LEATHER_LV4, 8, 200 + ITEM_ESSENCE11, 1,	//세트
	150 + ITEM_WOOD_LV4, 12, 50 + ITEM_LEATHER_LV4, 12, 200 + ITEM_ESSENCE34, 1,	//헬 트라이앵글
	150 + ITEM_WOOD_LV5, 4, 50 + ITEM_LEATHER_LV5, 4, 255, 0,	//라이트닝엣지
	150 + ITEM_WOOD_LV5, 6, 50 + ITEM_LEATHER_LV5, 6, 200 + ITEM_ESSENCE14, 1,	//고급
	150 + ITEM_WOOD_LV5, 8, 50 + ITEM_LEATHER_LV5, 8, 200 + ITEM_ESSENCE14, 2,	//희귀
	150 + ITEM_WOOD_LV5, 8, 50 + ITEM_LEATHER_LV5, 8, 200 + ITEM_ESSENCE17, 1,	//세트
	150 + ITEM_WOOD_LV5, 12, 50 + ITEM_LEATHER_LV5, 12, 200 + ITEM_ESSENCE35, 1,	//한탄의 부메랑
	150 + ITEM_WOOD_LV6, 4, 50 + ITEM_LEATHER_LV6, 4, 255, 0,	//소울 체이서
	150 + ITEM_WOOD_LV6, 6, 50 + ITEM_LEATHER_LV6, 6, 200 + ITEM_ESSENCE19, 1,	//고급
	150 + ITEM_WOOD_LV6, 8, 50 + ITEM_LEATHER_LV6, 8, 200 + ITEM_ESSENCE19, 2,	//희귀
	150 + ITEM_WOOD_LV6, 8, 50 + ITEM_LEATHER_LV6, 8, 200 + ITEM_ESSENCE24, 1,	//세트
	150 + ITEM_WOOD_LV6, 12, 50 + ITEM_LEATHER_LV6, 12, 200 + ITEM_ESSENCE38, 1,	//둠 슬레이어
	150 + ITEM_WOOD_LV7, 4, 50 + ITEM_LEATHER_LV7, 4, 255, 0,	//그리폰 윙
	150 + ITEM_WOOD_LV7, 6, 50 + ITEM_LEATHER_LV7, 6, 200 + ITEM_ESSENCE27, 1,	//고급
	150 + ITEM_WOOD_LV7, 8, 50 + ITEM_LEATHER_LV7, 8, 200 + ITEM_ESSENCE27, 2,	//희귀
	150 + ITEM_WOOD_LV7, 8, 50 + ITEM_LEATHER_LV7, 8, 200 + ITEM_ESSENCE23, 1,	//세트
	150 + ITEM_WOOD_LV7, 12, 50 + ITEM_LEATHER_LV7, 12, 200 + ITEM_ESSENCE40, 1,	//윙 오브 데스
	150 + ITEM_WOOD_LV7, 15, 50 + ITEM_LEATHER_LV7, 15, 200 + ITEM_ESSENCE42, 1,	//드래곤 윙
	150 + ITEM_WOOD_LV8, 4, 50 + ITEM_LEATHER_LV8, 4, 255, 0,	//로커스트 헌트
	150 + ITEM_WOOD_LV8, 6, 50 + ITEM_LEATHER_LV8, 6, 200 + ITEM_ESSENCE29, 1,	//고급
	150 + ITEM_WOOD_LV8, 8, 50 + ITEM_LEATHER_LV8, 8, 200 + ITEM_ESSENCE29, 2,	//희귀
	150 + ITEM_WOOD_LV8, 8, 50 + ITEM_LEATHER_LV8, 8, 200 + ITEM_ESSENCE31, 1,	//세트
	150 + ITEM_WOOD_LV8, 12, 50 + ITEM_LEATHER_LV8, 12, 200 + ITEM_ESSENCE43, 1,	//제노사이드 윙
	150 + ITEM_WOOD_LV8, 15, 50 + ITEM_LEATHER_LV8, 15, 200 + ITEM_ESSENCE44, 1,	//디재스터 엣지

	//헬멧 : ITEM_HELM
	50 + ITEM_LEATHER_LV1, 2, 100 + ITEM_CLOTH_LV1, 2, 255, 0,	//헤드 가드
	50 + ITEM_LEATHER_LV1, 4, 100 + ITEM_CLOTH_LV1, 4, 200 + ITEM_ESSENCE1, 1,	//고급
	50 + ITEM_LEATHER_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE1, 1,	//희귀
	50 + ITEM_LEATHER_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE1, 1,	//세트
	50 + ITEM_LEATHER_LV2, 2, 100 + ITEM_CLOTH_LV2, 2, 255, 0,	//바시넷
	50 + ITEM_LEATHER_LV2, 4, 100 + ITEM_CLOTH_LV2, 4, 200 + ITEM_ESSENCE3, 1,	//고급
	50 + ITEM_LEATHER_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE3, 1,	//희귀
	50 + ITEM_LEATHER_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE3, 1,	//세트
	50 + ITEM_LEATHER_LV3, 2, 100 + ITEM_CLOTH_LV3, 2, 255, 0,	//솔저헬름
	50 + ITEM_LEATHER_LV3, 4, 100 + ITEM_CLOTH_LV3, 4, 200 + ITEM_ESSENCE5, 1,	//고급
	50 + ITEM_LEATHER_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE5, 2,	//희귀
	50 + ITEM_LEATHER_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE7, 1,	//세트
	50 + ITEM_LEATHER_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE33, 1,	//센츄리온 헬멧
	50 + ITEM_LEATHER_LV4, 2, 100 + ITEM_CLOTH_LV4, 2, 255, 0,	//검투사의 투구
	50 + ITEM_LEATHER_LV4, 4, 100 + ITEM_CLOTH_LV4, 4, 200 + ITEM_ESSENCE9, 1,	//고급
	50 + ITEM_LEATHER_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE9, 2,	//희귀
	50 + ITEM_LEATHER_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE11, 1,	//세트
	50 + ITEM_LEATHER_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE34, 1,	//블러디 헬멧
	50 + ITEM_LEATHER_LV5, 2, 100 + ITEM_CLOTH_LV5, 2, 255, 0,	//스파이크 헤드
	50 + ITEM_LEATHER_LV5, 4, 100 + ITEM_CLOTH_LV5, 4, 200 + ITEM_ESSENCE15, 1,	//고급
	50 + ITEM_LEATHER_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE15, 2,	//희귀
	50 + ITEM_LEATHER_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE17, 1,	//세트
	50 + ITEM_LEATHER_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE36, 1,	//귀신의 투구
	50 + ITEM_LEATHER_LV6, 2, 100 + ITEM_CLOTH_LV6, 2, 255, 0,	//그랜드헬름
	50 + ITEM_LEATHER_LV6, 4, 100 + ITEM_CLOTH_LV6, 4, 200 + ITEM_ESSENCE19, 1,	//고급
	50 + ITEM_LEATHER_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE19, 2,	//희귀
	50 + ITEM_LEATHER_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE25, 1,	//세트
	50 + ITEM_LEATHER_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE39, 1,	//성기사의 투구
	50 + ITEM_LEATHER_LV7, 2, 100 + ITEM_CLOTH_LV7, 2, 255, 0,	//고대의투구
	50 + ITEM_LEATHER_LV7, 4, 100 + ITEM_CLOTH_LV7, 4, 200 + ITEM_ESSENCE27, 1,	//고급
	50 + ITEM_LEATHER_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE27, 2,	//희귀
	50 + ITEM_LEATHER_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE23, 1,	//세트
	50 + ITEM_LEATHER_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE41, 1,	//환영의 투구
	50 + ITEM_LEATHER_LV7, 12, 100 + ITEM_CLOTH_LV7, 12, 200 + ITEM_ESSENCE42, 1,	//미라주 헬름
	50 + ITEM_LEATHER_LV8, 2, 100 + ITEM_CLOTH_LV8, 2, 255, 0,	//용자의 투구
	50 + ITEM_LEATHER_LV8, 4, 100 + ITEM_CLOTH_LV8, 4, 200 + ITEM_ESSENCE29, 1,	//고급
	50 + ITEM_LEATHER_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE29, 2,	//희귀
	50 + ITEM_LEATHER_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE31, 1,	//세트
	50 + ITEM_LEATHER_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE43, 1,	//져지먼트 헬맷
	50 + ITEM_LEATHER_LV8, 12, 100 + ITEM_CLOTH_LV8, 12, 200 + ITEM_ESSENCE44, 1,	//오시리스 헬맷

	//모자 : ITEM_HAT
	150 + ITEM_WOOD_LV1, 2, 100 + ITEM_CLOTH_LV1, 2, 255, 0,	//산책용 보닛
	150 + ITEM_WOOD_LV1, 4, 100 + ITEM_CLOTH_LV1, 4, 200 + ITEM_ESSENCE0, 1,	//고급
	150 + ITEM_WOOD_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE0, 1,	//희귀
	150 + ITEM_WOOD_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE0, 1,	//세트
	150 + ITEM_WOOD_LV2, 2, 100 + ITEM_CLOTH_LV2, 2, 255, 0,	//카우보이 모자
	150 + ITEM_WOOD_LV2, 4, 100 + ITEM_CLOTH_LV2, 4, 200 + ITEM_ESSENCE3, 1,	//고급
	150 + ITEM_WOOD_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE3, 1,	//희귀
	150 + ITEM_WOOD_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE3, 1,	//세트
	150 + ITEM_WOOD_LV3, 2, 100 + ITEM_CLOTH_LV3, 2, 255, 0,	//레인저 햇
	150 + ITEM_WOOD_LV3, 4, 100 + ITEM_CLOTH_LV3, 4, 200 + ITEM_ESSENCE4, 1,	//고급
	150 + ITEM_WOOD_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE4, 2,	//희귀
	150 + ITEM_WOOD_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE7, 1,	//세트
	150 + ITEM_WOOD_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE33, 1,	//무법자의 모자
	150 + ITEM_WOOD_LV4, 2, 100 + ITEM_CLOTH_LV4, 2, 255, 0,	//서클렛
	150 + ITEM_WOOD_LV4, 4, 100 + ITEM_CLOTH_LV4, 4, 200 + ITEM_ESSENCE9, 1,	//고급
	150 + ITEM_WOOD_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE9, 2,	//희귀
	150 + ITEM_WOOD_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE11, 1,	//세트
	150 + ITEM_WOOD_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE34, 1,	//골드 블레스
	150 + ITEM_WOOD_LV5, 2, 100 + ITEM_CLOTH_LV5, 2, 255, 0,	//올드 윌로우
	150 + ITEM_WOOD_LV5, 4, 100 + ITEM_CLOTH_LV5, 4, 200 + ITEM_ESSENCE13, 1,	//고급
	150 + ITEM_WOOD_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE13, 2,	//희귀
	150 + ITEM_WOOD_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE17, 1,	//세트
	150 + ITEM_WOOD_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE36, 1,	//엘븐 햇
	150 + ITEM_WOOD_LV6, 2, 100 + ITEM_CLOTH_LV6, 2, 255, 0,	//스나이퍼 고글
	150 + ITEM_WOOD_LV6, 4, 100 + ITEM_CLOTH_LV6, 4, 200 + ITEM_ESSENCE18, 1,	//고급
	150 + ITEM_WOOD_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE18, 2,	//희귀
	150 + ITEM_WOOD_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE20, 1,	//세트
	150 + ITEM_WOOD_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE39, 1,	//어쌔신 스코프
	150 + ITEM_WOOD_LV7, 2, 100 + ITEM_CLOTH_LV7, 2, 255, 0,	//혼란의 모자
	150 + ITEM_WOOD_LV7, 4, 100 + ITEM_CLOTH_LV7, 4, 200 + ITEM_ESSENCE27, 1,	//고급
	150 + ITEM_WOOD_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE27, 2,	//희귀
	150 + ITEM_WOOD_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE23, 1,	//세트
	150 + ITEM_WOOD_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE41, 1,	//카오스 솔져
	150 + ITEM_WOOD_LV7, 12, 100 + ITEM_CLOTH_LV7, 12, 200 + ITEM_ESSENCE42, 1,	//나이트메어 헷
	150 + ITEM_WOOD_LV8, 2, 100 + ITEM_CLOTH_LV8, 2, 255, 0,	//프리에스테스
	150 + ITEM_WOOD_LV8, 4, 100 + ITEM_CLOTH_LV8, 4, 200 + ITEM_ESSENCE28, 1,	//고급
	150 + ITEM_WOOD_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE28, 2,	//희귀
	150 + ITEM_WOOD_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE31, 1,	//세트
	150 + ITEM_WOOD_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE43, 1,	//발키리 서클렛
	150 + ITEM_WOOD_LV8, 12, 100 + ITEM_CLOTH_LV8, 12, 200 + ITEM_ESSENCE44, 1,	//오딘 크라운

	//두건 : ITEM_CAP
	ITEM_IRON_LV1, 2, 100 + ITEM_CLOTH_LV1, 2, 255, 0,	//공작깃털 모자
	ITEM_IRON_LV1, 4, 100 + ITEM_CLOTH_LV1, 4, 200 + ITEM_ESSENCE0, 1,	//고급
	ITEM_IRON_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE0, 1,	//희귀
	ITEM_IRON_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE0, 1,	//세트
	ITEM_IRON_LV2, 2, 100 + ITEM_CLOTH_LV2, 2, 255, 0,	//귀족의 머리띠
	ITEM_IRON_LV2, 4, 100 + ITEM_CLOTH_LV2, 4, 200 + ITEM_ESSENCE2, 1,	//고급
	ITEM_IRON_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE2, 1,	//희귀
	ITEM_IRON_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE2, 1,	//세트
	ITEM_IRON_LV3, 2, 100 + ITEM_CLOTH_LV3, 2, 255, 0,	//거상의 모자
	ITEM_IRON_LV3, 4, 100 + ITEM_CLOTH_LV3, 4, 200 + ITEM_ESSENCE4, 1,	//고급
	ITEM_IRON_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE4, 2,	//희귀
	ITEM_IRON_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE6, 1,	//세트
	ITEM_IRON_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE33, 1,	//캐러벤 리더
	ITEM_IRON_LV4, 2, 100 + ITEM_CLOTH_LV4, 2, 255, 0,	//사냥꾼 모자
	ITEM_IRON_LV4, 4, 100 + ITEM_CLOTH_LV4, 4, 200 + ITEM_ESSENCE8, 1,	//고급
	ITEM_IRON_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE8, 2,	//희귀
	ITEM_IRON_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE10, 1,	//세트
	ITEM_IRON_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE34, 1,	//로빈훗 캡
	ITEM_IRON_LV5, 2, 100 + ITEM_CLOTH_LV5, 2, 255, 0,	//투우사의 모자
	ITEM_IRON_LV5, 4, 100 + ITEM_CLOTH_LV5, 4, 200 + ITEM_ESSENCE14, 1,	//고급
	ITEM_IRON_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE14, 2,	//희귀
	ITEM_IRON_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE16, 1,	//세트
	ITEM_IRON_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE36, 1,	//미노타우르스
	ITEM_IRON_LV6, 2, 100 + ITEM_CLOTH_LV6, 2, 255, 0,	//해적의 모자
	ITEM_IRON_LV6, 4, 100 + ITEM_CLOTH_LV6, 4, 200 + ITEM_ESSENCE18, 1,	//고급
	ITEM_IRON_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE18, 2,	//희귀
	ITEM_IRON_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE21, 1,	//세트
	ITEM_IRON_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE39, 1,	//졸리로져 캡
	ITEM_IRON_LV7, 2, 100 + ITEM_CLOTH_LV7, 2, 255, 0,	//에이스 캡
	ITEM_IRON_LV7, 4, 100 + ITEM_CLOTH_LV7, 4, 200 + ITEM_ESSENCE26, 1,	//고급
	ITEM_IRON_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE26, 2,	//희귀
	ITEM_IRON_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE22, 1,	//세트
	ITEM_IRON_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE40, 1,	//브레이브 캡
	ITEM_IRON_LV7, 12, 100 + ITEM_CLOTH_LV7, 12, 200 + ITEM_ESSENCE42, 1,	//다이너스티 캡
	ITEM_IRON_LV8, 2, 100 + ITEM_CLOTH_LV8, 2, 255, 0,	//드래곤 레어캡
	ITEM_IRON_LV8, 4, 100 + ITEM_CLOTH_LV8, 4, 200 + ITEM_ESSENCE28, 1,	//고급
	ITEM_IRON_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE28, 2,	//희귀
	ITEM_IRON_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE30, 1,	//세트
	ITEM_IRON_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE43, 1,	//히드라 헤드
	ITEM_IRON_LV8, 12, 100 + ITEM_CLOTH_LV8, 12, 200 + ITEM_ESSENCE44, 1,	//리바이어선 캡

	//갑옷 : ITEM_ARMOR
	50 + ITEM_LEATHER_LV1, 4, 100 + ITEM_CLOTH_LV1, 4, 255, 0,	//헌터 튜닉
	50 + ITEM_LEATHER_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE1, 1,	//고급
	50 + ITEM_LEATHER_LV1, 8, 100 + ITEM_CLOTH_LV1, 8, 200 + ITEM_ESSENCE1, 1,	//희귀
	50 + ITEM_LEATHER_LV1, 8, 100 + ITEM_CLOTH_LV1, 8, 200 + ITEM_ESSENCE1, 1,	//세트
	50 + ITEM_LEATHER_LV2, 4, 100 + ITEM_CLOTH_LV2, 4, 255, 0,	//미늘 갑옷
	50 + ITEM_LEATHER_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE3, 1,	//고급
	50 + ITEM_LEATHER_LV2, 8, 100 + ITEM_CLOTH_LV2, 8, 200 + ITEM_ESSENCE3, 1,	//희귀
	50 + ITEM_LEATHER_LV2, 8, 100 + ITEM_CLOTH_LV2, 8, 200 + ITEM_ESSENCE3, 1,	//세트
	50 + ITEM_LEATHER_LV3, 4, 100 + ITEM_CLOTH_LV3, 4, 255, 0,	//하프 플레이트
	50 + ITEM_LEATHER_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE5, 1,	//고급
	50 + ITEM_LEATHER_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE5, 2,	//희귀
	50 + ITEM_LEATHER_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE7, 1,	//세트
	50 + ITEM_LEATHER_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE32, 1,	//밴디트 메일
	50 + ITEM_LEATHER_LV4, 4, 100 + ITEM_CLOTH_LV4, 4, 255, 0,	//스컬 메일
	50 + ITEM_LEATHER_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE9, 1,	//고급
	50 + ITEM_LEATHER_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE9, 2,	//희귀
	50 + ITEM_LEATHER_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE11, 1,	//세트
	50 + ITEM_LEATHER_LV4, 12, 100 + ITEM_CLOTH_LV4, 12, 200 + ITEM_ESSENCE34, 1,	//마검사의 흉갑
	50 + ITEM_LEATHER_LV5, 4, 100 + ITEM_CLOTH_LV5, 4, 255, 0,	//황금세공 갑옷
	50 + ITEM_LEATHER_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE15, 1,	//고급
	50 + ITEM_LEATHER_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE15, 2,	//희귀
	50 + ITEM_LEATHER_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE17, 1,	//세트
	50 + ITEM_LEATHER_LV5, 12, 100 + ITEM_CLOTH_LV5, 12, 200 + ITEM_ESSENCE37, 1,	//드워븐 헬름
	50 + ITEM_LEATHER_LV6, 4, 100 + ITEM_CLOTH_LV6, 4, 255, 0,	//미스릴 아머
	50 + ITEM_LEATHER_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE19, 1,	//고급
	50 + ITEM_LEATHER_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE19, 2,	//희귀
	50 + ITEM_LEATHER_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE24, 1,	//세트
	50 + ITEM_LEATHER_LV6, 12, 100 + ITEM_CLOTH_LV6, 12, 200 + ITEM_ESSENCE38, 1,	//요정의 갑주
	50 + ITEM_LEATHER_LV7, 4, 100 + ITEM_CLOTH_LV7, 4, 255, 0,	//고대의 갑옷
	50 + ITEM_LEATHER_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE27, 1,	//고급
	50 + ITEM_LEATHER_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE27, 2,	//희귀
	50 + ITEM_LEATHER_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE23, 1,	//세트
	50 + ITEM_LEATHER_LV7, 12, 100 + ITEM_CLOTH_LV7, 12, 200 + ITEM_ESSENCE40, 1,	//불멸의 갑주
	50 + ITEM_LEATHER_LV7, 15, 100 + ITEM_CLOTH_LV7, 15, 200 + ITEM_ESSENCE42, 1,	//브리간다인
	50 + ITEM_LEATHER_LV8, 4, 100 + ITEM_CLOTH_LV8, 4, 255, 0,	//용비늘 갑옷
	50 + ITEM_LEATHER_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE29, 1,	//고급
	50 + ITEM_LEATHER_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE29, 2,	//희귀
	50 + ITEM_LEATHER_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE31, 1,	//세트
	50 + ITEM_LEATHER_LV8, 12, 100 + ITEM_CLOTH_LV8, 12, 200 + ITEM_ESSENCE43, 1,	//황룡의 갑옷
	50 + ITEM_LEATHER_LV8, 15, 100 + ITEM_CLOTH_LV8, 15, 200 + ITEM_ESSENCE44, 1,	//바하무트 아머

	//조끼 : ITEM_VEST
	150 + ITEM_WOOD_LV1, 4, 100 + ITEM_CLOTH_LV1, 4, 255, 0,	//카우보이 조끼
	150 + ITEM_WOOD_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE0, 1,	//고급
	150 + ITEM_WOOD_LV1, 8, 100 + ITEM_CLOTH_LV1, 8, 200 + ITEM_ESSENCE0, 1,	//희귀
	150 + ITEM_WOOD_LV1, 8, 100 + ITEM_CLOTH_LV1, 8, 200 + ITEM_ESSENCE0, 1,	//세트
	150 + ITEM_WOOD_LV2, 4, 100 + ITEM_CLOTH_LV2, 4, 255, 0,	//실크조끼
	150 + ITEM_WOOD_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE3, 1,	//고급
	150 + ITEM_WOOD_LV2, 8, 100 + ITEM_CLOTH_LV2, 8, 200 + ITEM_ESSENCE3, 1,	//희귀
	150 + ITEM_WOOD_LV2, 8, 100 + ITEM_CLOTH_LV2, 8, 200 + ITEM_ESSENCE3, 1,	//세트
	150 + ITEM_WOOD_LV3, 4, 100 + ITEM_CLOTH_LV3, 4, 255, 0,	//서바이벌 조끼
	150 + ITEM_WOOD_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE4, 1,	//고급
	150 + ITEM_WOOD_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE4, 2,	//희귀
	150 + ITEM_WOOD_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE7, 1,	//세트
	150 + ITEM_WOOD_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE32, 1,	//방랑자의 조끼
	150 + ITEM_WOOD_LV4, 4, 100 + ITEM_CLOTH_LV4, 4, 255, 0,	//도적의 조끼
	150 + ITEM_WOOD_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE9, 1,	//고급
	150 + ITEM_WOOD_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE9, 2,	//희귀
	150 + ITEM_WOOD_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE11, 1,	//세트
	150 + ITEM_WOOD_LV4, 12, 100 + ITEM_CLOTH_LV4, 12, 200 + ITEM_ESSENCE34, 1,	//어쌔신 베스트
	150 + ITEM_WOOD_LV5, 4, 100 + ITEM_CLOTH_LV5, 4, 255, 0,	//벨벳 셔츠
	150 + ITEM_WOOD_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE13, 1,	//고급
	150 + ITEM_WOOD_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE13, 2,	//희귀
	150 + ITEM_WOOD_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE17, 1,	//세트
	150 + ITEM_WOOD_LV5, 12, 100 + ITEM_CLOTH_LV5, 12, 200 + ITEM_ESSENCE37, 1,	//고딕 셔츠
	150 + ITEM_WOOD_LV6, 4, 100 + ITEM_CLOTH_LV6, 4, 255, 0,	//귀족의 조끼
	150 + ITEM_WOOD_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE18, 1,	//고급
	150 + ITEM_WOOD_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE18, 2,	//희귀
	150 + ITEM_WOOD_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE25, 1,	//세트
	150 + ITEM_WOOD_LV6, 12, 100 + ITEM_CLOTH_LV6, 12, 200 + ITEM_ESSENCE38, 1,	//은사슬 조끼
	150 + ITEM_WOOD_LV7, 4, 100 + ITEM_CLOTH_LV7, 4, 255, 0,	//진홍빛 셔츠
	150 + ITEM_WOOD_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE27, 1,	//고급
	150 + ITEM_WOOD_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE27, 2,	//희귀
	150 + ITEM_WOOD_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE23, 1,	//세트
	150 + ITEM_WOOD_LV7, 12, 100 + ITEM_CLOTH_LV7, 12, 200 + ITEM_ESSENCE40, 1,	//불사의 셔츠
	150 + ITEM_WOOD_LV7, 15, 100 + ITEM_CLOTH_LV7, 15, 200 + ITEM_ESSENCE42, 1,	//뱀파이어 로드
	150 + ITEM_WOOD_LV8, 4, 100 + ITEM_CLOTH_LV8, 4, 255, 0,	//신관의 로브
	150 + ITEM_WOOD_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE28, 1,	//고급
	150 + ITEM_WOOD_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE28, 2,	//희귀
	150 + ITEM_WOOD_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE31, 1,	//세트
	150 + ITEM_WOOD_LV8, 12, 100 + ITEM_CLOTH_LV8, 12, 200 + ITEM_ESSENCE43, 1,	//세라핌 로브
	150 + ITEM_WOOD_LV8, 15, 100 + ITEM_CLOTH_LV8, 15, 200 + ITEM_ESSENCE44, 1,	//루시펠 로브

	//코트 : ITEM_COAT
	ITEM_IRON_LV1, 4, 100 + ITEM_CLOTH_LV1, 4, 255, 0,	//수수한 코트
	ITEM_IRON_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE0, 1,	//고급
	ITEM_IRON_LV1, 8, 100 + ITEM_CLOTH_LV1, 8, 200 + ITEM_ESSENCE0, 1,	//희귀
	ITEM_IRON_LV1, 8, 100 + ITEM_CLOTH_LV1, 8, 200 + ITEM_ESSENCE0, 1,	//세트
	ITEM_IRON_LV2, 4, 100 + ITEM_CLOTH_LV2, 4, 255, 0,	//패딩 아머
	ITEM_IRON_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE2, 1,	//고급
	ITEM_IRON_LV2, 8, 100 + ITEM_CLOTH_LV2, 8, 200 + ITEM_ESSENCE2, 1,	//희귀
	ITEM_IRON_LV2, 8, 100 + ITEM_CLOTH_LV2, 8, 200 + ITEM_ESSENCE2, 1,	//세트
	ITEM_IRON_LV3, 4, 100 + ITEM_CLOTH_LV3, 4, 255, 0,	//털가죽 코트
	ITEM_IRON_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE4, 1,	//고급
	ITEM_IRON_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE4, 2,	//희귀
	ITEM_IRON_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE6, 1,	//세트
	ITEM_IRON_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE32, 1,	//그리즐리 스킨
	ITEM_IRON_LV4, 4, 100 + ITEM_CLOTH_LV4, 4, 255, 0,	//큐어 보일
	ITEM_IRON_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE8, 1,	//고급
	ITEM_IRON_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE8, 2,	//희귀
	ITEM_IRON_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE10, 1,	//세트
	ITEM_IRON_LV4, 12, 100 + ITEM_CLOTH_LV4, 12, 200 + ITEM_ESSENCE34, 1,	//코아틀 스케일
	ITEM_IRON_LV5, 4, 100 + ITEM_CLOTH_LV5, 4, 255, 0,	//귀족의 코트
	ITEM_IRON_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE14, 1,	//고급
	ITEM_IRON_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE14, 2,	//희귀
	ITEM_IRON_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE16, 1,	//세트
	ITEM_IRON_LV5, 12, 100 + ITEM_CLOTH_LV5, 12, 200 + ITEM_ESSENCE37, 1,	//흑까마귀 코트
	ITEM_IRON_LV6, 4, 100 + ITEM_CLOTH_LV6, 4, 255, 0,	//극지의 코트
	ITEM_IRON_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE18, 1,	//고급
	ITEM_IRON_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE18, 2,	//희귀
	ITEM_IRON_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE20, 1,	//세트
	ITEM_IRON_LV6, 12, 100 + ITEM_CLOTH_LV6, 12, 200 + ITEM_ESSENCE38, 1,	//블리자드 가드
	ITEM_IRON_LV7, 4, 100 + ITEM_CLOTH_LV7, 4, 255, 0,	//윙 코트
	ITEM_IRON_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE26, 1,	//고급
	ITEM_IRON_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE26, 2,	//희귀
	ITEM_IRON_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE22, 1,	//세트
	ITEM_IRON_LV7, 12, 100 + ITEM_CLOTH_LV7, 12, 200 + ITEM_ESSENCE40, 1,	//가고일 코트
	ITEM_IRON_LV7, 15, 100 + ITEM_CLOTH_LV7, 15, 200 + ITEM_ESSENCE42, 1,	//페가수스 코트
	ITEM_IRON_LV8, 4, 100 + ITEM_CLOTH_LV8, 4, 255, 0,	//바이스 코트
	ITEM_IRON_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE28, 1,	//고급
	ITEM_IRON_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE28, 2,	//희귀
	ITEM_IRON_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE30, 1,	//세트
	ITEM_IRON_LV8, 12, 100 + ITEM_CLOTH_LV8, 12, 200 + ITEM_ESSENCE43, 1,	//종말의 코트
	ITEM_IRON_LV8, 15, 100 + ITEM_CLOTH_LV8, 15, 200 + ITEM_ESSENCE44, 1,	//카오스 엠페러

	//건틀렛 : ITEM_GUNTLET
	50 + ITEM_LEATHER_LV1, 2, 100 + ITEM_CLOTH_LV1, 2, 255, 0,	//핸드 가드
	50 + ITEM_LEATHER_LV1, 4, 100 + ITEM_CLOTH_LV1, 4, 200 + ITEM_ESSENCE1, 1,	//고급
	50 + ITEM_LEATHER_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE1, 1,	//희귀
	50 + ITEM_LEATHER_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE1, 1,	//세트
	50 + ITEM_LEATHER_LV2, 2, 100 + ITEM_CLOTH_LV2, 2, 255, 0,	//청동 장갑
	50 + ITEM_LEATHER_LV2, 4, 100 + ITEM_CLOTH_LV2, 4, 200 + ITEM_ESSENCE3, 1,	//고급
	50 + ITEM_LEATHER_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE3, 1,	//희귀
	50 + ITEM_LEATHER_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE3, 1,	//세트
	50 + ITEM_LEATHER_LV3, 2, 100 + ITEM_CLOTH_LV3, 2, 255, 0,	//체인 건틀렛
	50 + ITEM_LEATHER_LV3, 4, 100 + ITEM_CLOTH_LV3, 4, 200 + ITEM_ESSENCE5, 1,	//고급
	50 + ITEM_LEATHER_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE5, 2,	//희귀
	50 + ITEM_LEATHER_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE7, 1,	//세트
	50 + ITEM_LEATHER_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE33, 1,	//모험자의 장갑
	50 + ITEM_LEATHER_LV4, 2, 100 + ITEM_CLOTH_LV4, 2, 255, 0,	//나이트 글로브
	50 + ITEM_LEATHER_LV4, 4, 100 + ITEM_CLOTH_LV4, 4, 200 + ITEM_ESSENCE9, 1,	//고급
	50 + ITEM_LEATHER_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE9, 2,	//희귀
	50 + ITEM_LEATHER_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE11, 1,	//세트
	50 + ITEM_LEATHER_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE34, 1,	//명성의 장갑
	50 + ITEM_LEATHER_LV5, 2, 100 + ITEM_CLOTH_LV5, 2, 255, 0,	//비스트 핸드
	50 + ITEM_LEATHER_LV5, 4, 100 + ITEM_CLOTH_LV5, 4, 200 + ITEM_ESSENCE15, 1,	//고급
	50 + ITEM_LEATHER_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE15, 2,	//희귀
	50 + ITEM_LEATHER_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE17, 1,	//세트
	50 + ITEM_LEATHER_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE35, 1,	//오우거 건틀렛
	50 + ITEM_LEATHER_LV6, 2, 100 + ITEM_CLOTH_LV6, 2, 255, 0,	//라이징 건틀렛
	50 + ITEM_LEATHER_LV6, 4, 100 + ITEM_CLOTH_LV6, 4, 200 + ITEM_ESSENCE19, 1,	//고급
	50 + ITEM_LEATHER_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE19, 2,	//희귀
	50 + ITEM_LEATHER_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE21, 1,	//세트
	50 + ITEM_LEATHER_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE39, 1,	//무쌍의 장갑
	50 + ITEM_LEATHER_LV7, 2, 100 + ITEM_CLOTH_LV7, 2, 255, 0,	//광전사의 장갑
	50 + ITEM_LEATHER_LV7, 4, 100 + ITEM_CLOTH_LV7, 4, 200 + ITEM_ESSENCE27, 1,	//고급
	50 + ITEM_LEATHER_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE27, 2,	//희귀
	50 + ITEM_LEATHER_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE23, 1,	//세트
	50 + ITEM_LEATHER_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE41, 1,	//뇌격파수
	50 + ITEM_LEATHER_LV7, 12, 100 + ITEM_CLOTH_LV7, 12, 200 + ITEM_ESSENCE42, 1,	//시바의 손톱
	50 + ITEM_LEATHER_LV8, 2, 100 + ITEM_CLOTH_LV8, 2, 255, 0,	//드래곤 핸드
	50 + ITEM_LEATHER_LV8, 4, 100 + ITEM_CLOTH_LV8, 4, 200 + ITEM_ESSENCE29, 1,	//고급
	50 + ITEM_LEATHER_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE29, 2,	//희귀
	50 + ITEM_LEATHER_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE31, 1,	//세트
	50 + ITEM_LEATHER_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE43, 1,	//백룡의 장갑
	50 + ITEM_LEATHER_LV8, 12, 100 + ITEM_CLOTH_LV8, 12, 200 + ITEM_ESSENCE44, 1,	//바하무트 크로

	//팔찌 : ITEM_ARMLET
	150 + ITEM_WOOD_LV1, 2, 100 + ITEM_CLOTH_LV1, 2, 255, 0,	//사제의묵주
	150 + ITEM_WOOD_LV1, 4, 100 + ITEM_CLOTH_LV1, 4, 200 + ITEM_ESSENCE0, 1,	//고급
	150 + ITEM_WOOD_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE0, 1,	//희귀
	150 + ITEM_WOOD_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE0, 1,	//세트
	150 + ITEM_WOOD_LV2, 2, 100 + ITEM_CLOTH_LV2, 2, 255, 0,	//여행자의팔찌
	150 + ITEM_WOOD_LV2, 4, 100 + ITEM_CLOTH_LV2, 4, 200 + ITEM_ESSENCE3, 1,	//고급
	150 + ITEM_WOOD_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE3, 1,	//희귀
	150 + ITEM_WOOD_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE3, 1,	//세트
	150 + ITEM_WOOD_LV3, 2, 100 + ITEM_CLOTH_LV3, 2, 255, 0,	//백금 브레스렛
	150 + ITEM_WOOD_LV3, 4, 100 + ITEM_CLOTH_LV3, 4, 200 + ITEM_ESSENCE4, 1,	//고급
	150 + ITEM_WOOD_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE4, 2,	//희귀
	150 + ITEM_WOOD_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE7, 1,	//세트
	150 + ITEM_WOOD_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE33, 1,	//연인의 팔찌
	150 + ITEM_WOOD_LV4, 2, 100 + ITEM_CLOTH_LV4, 2, 255, 0,	//전사의 암렛
	150 + ITEM_WOOD_LV4, 4, 100 + ITEM_CLOTH_LV4, 4, 200 + ITEM_ESSENCE9, 1,	//고급
	150 + ITEM_WOOD_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE9, 2,	//희귀
	150 + ITEM_WOOD_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE11, 1,	//세트
	150 + ITEM_WOOD_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE34, 1,	//임프 암렛
	150 + ITEM_WOOD_LV5, 2, 100 + ITEM_CLOTH_LV5, 2, 255, 0,	//에메랄드 팔찌
	150 + ITEM_WOOD_LV5, 4, 100 + ITEM_CLOTH_LV5, 4, 200 + ITEM_ESSENCE13, 1,	//고급
	150 + ITEM_WOOD_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE13, 2,	//희귀
	150 + ITEM_WOOD_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE17, 1,	//세트
	150 + ITEM_WOOD_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE35, 1,	//노블레스 암렛
	150 + ITEM_WOOD_LV6, 2, 100 + ITEM_CLOTH_LV6, 2, 255, 0,	//이블 암렛
	150 + ITEM_WOOD_LV6, 4, 100 + ITEM_CLOTH_LV6, 4, 200 + ITEM_ESSENCE18, 1,	//고급
	150 + ITEM_WOOD_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE18, 2,	//희귀
	150 + ITEM_WOOD_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE24, 1,	//세트
	150 + ITEM_WOOD_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE39, 1,	//몽마의 팔찌
	150 + ITEM_WOOD_LV7, 2, 100 + ITEM_CLOTH_LV7, 2, 255, 0,	//위엄의 팔찌
	150 + ITEM_WOOD_LV7, 4, 100 + ITEM_CLOTH_LV7, 4, 200 + ITEM_ESSENCE27, 1,	//고급
	150 + ITEM_WOOD_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE27, 2,	//희귀
	150 + ITEM_WOOD_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE23, 1,	//세트
	150 + ITEM_WOOD_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE41, 1,	//지배자의 팔찌
	150 + ITEM_WOOD_LV7, 12, 100 + ITEM_CLOTH_LV7, 12, 200 + ITEM_ESSENCE42, 1,	//엠프레스 암렛
	150 + ITEM_WOOD_LV8, 2, 100 + ITEM_CLOTH_LV8, 2, 255, 0,	//영웅의 팔찌
	150 + ITEM_WOOD_LV8, 4, 100 + ITEM_CLOTH_LV8, 4, 200 + ITEM_ESSENCE28, 1,	//고급
	150 + ITEM_WOOD_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE28, 2,	//희귀
	150 + ITEM_WOOD_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE31, 1,	//세트
	150 + ITEM_WOOD_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE43, 1,	//갓 브레스렛
	150 + ITEM_WOOD_LV8, 12, 100 + ITEM_CLOTH_LV8, 12, 200 + ITEM_ESSENCE44, 1,	//갓 핸드

	//장갑 : ITEM_GLOVE
	ITEM_IRON_LV1, 2, 100 + ITEM_CLOTH_LV1, 2, 255, 0,	//여행자의 장갑
	ITEM_IRON_LV1, 4, 100 + ITEM_CLOTH_LV1, 4, 200 + ITEM_ESSENCE0, 1,	//고급
	ITEM_IRON_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE0, 1,	//희귀
	ITEM_IRON_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE0, 1,	//세트
	ITEM_IRON_LV2, 2, 100 + ITEM_CLOTH_LV2, 2, 255, 0,	//이중매듭 장갑
	ITEM_IRON_LV2, 4, 100 + ITEM_CLOTH_LV2, 4, 200 + ITEM_ESSENCE2, 1,	//고급
	ITEM_IRON_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE2, 1,	//희귀
	ITEM_IRON_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE2, 1,	//세트
	ITEM_IRON_LV3, 2, 100 + ITEM_CLOTH_LV3, 2, 255, 0,	//소매치기 장갑
	ITEM_IRON_LV3, 4, 100 + ITEM_CLOTH_LV3, 4, 200 + ITEM_ESSENCE4, 1,	//고급
	ITEM_IRON_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE4, 2,	//희귀
	ITEM_IRON_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE6, 1,	//세트
	ITEM_IRON_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE33, 1,	//섀도우핸드
	ITEM_IRON_LV4, 2, 100 + ITEM_CLOTH_LV4, 2, 255, 0,	//리넨 글로브
	ITEM_IRON_LV4, 4, 100 + ITEM_CLOTH_LV4, 4, 200 + ITEM_ESSENCE8, 1,	//고급
	ITEM_IRON_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE8, 2,	//희귀
	ITEM_IRON_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE10, 1,	//세트
	ITEM_IRON_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE34, 1,	//귀공자의 장갑
	ITEM_IRON_LV5, 2, 100 + ITEM_CLOTH_LV5, 2, 255, 0,	//레이스 미튼
	ITEM_IRON_LV5, 4, 100 + ITEM_CLOTH_LV5, 4, 200 + ITEM_ESSENCE14, 1,	//고급
	ITEM_IRON_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE14, 2,	//희귀
	ITEM_IRON_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE16, 1,	//세트
	ITEM_IRON_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE35, 1,	//달인의 장갑
	ITEM_IRON_LV6, 2, 100 + ITEM_CLOTH_LV6, 2, 255, 0,	//마법문양 장갑
	ITEM_IRON_LV6, 4, 100 + ITEM_CLOTH_LV6, 4, 200 + ITEM_ESSENCE18, 1,	//고급
	ITEM_IRON_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE18, 2,	//희귀
	ITEM_IRON_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE25, 1,	//세트
	ITEM_IRON_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE39, 1,	//커스드 글로브
	ITEM_IRON_LV7, 2, 100 + ITEM_CLOTH_LV7, 2, 255, 0,	//심판의 손
	ITEM_IRON_LV7, 4, 100 + ITEM_CLOTH_LV7, 4, 200 + ITEM_ESSENCE26, 1,	//고급
	ITEM_IRON_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE26, 2,	//희귀
	ITEM_IRON_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE22, 1,	//세트
	ITEM_IRON_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE40, 1,	//구원의 손
	ITEM_IRON_LV7, 12, 100 + ITEM_CLOTH_LV7, 12, 200 + ITEM_ESSENCE42, 1,	//이터널 져지
	ITEM_IRON_LV8, 2, 100 + ITEM_CLOTH_LV8, 2, 255, 0,	//성자의 장갑
	ITEM_IRON_LV8, 4, 100 + ITEM_CLOTH_LV8, 4, 200 + ITEM_ESSENCE28, 1,	//고급
	ITEM_IRON_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE28, 2,	//희귀
	ITEM_IRON_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE30, 1,	//세트
	ITEM_IRON_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE43, 1,	//팔라딘 글로브
	ITEM_IRON_LV8, 12, 100 + ITEM_CLOTH_LV8, 12, 200 + ITEM_ESSENCE44, 1,	//홀리 핸드

	//킬트 : ITEM_KILT
	50 + ITEM_LEATHER_LV1, 4, 100 + ITEM_CLOTH_LV1, 4, 255, 0,	//밴딩 킬트
	50 + ITEM_LEATHER_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE1, 1,	//고급
	50 + ITEM_LEATHER_LV1, 8, 100 + ITEM_CLOTH_LV1, 8, 200 + ITEM_ESSENCE1, 1,	//희귀
	50 + ITEM_LEATHER_LV1, 8, 100 + ITEM_CLOTH_LV1, 8, 200 + ITEM_ESSENCE1, 1,	//세트
	50 + ITEM_LEATHER_LV2, 4, 100 + ITEM_CLOTH_LV2, 4, 255, 0,	//체인 킬트
	50 + ITEM_LEATHER_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE3, 1,	//고급
	50 + ITEM_LEATHER_LV2, 8, 100 + ITEM_CLOTH_LV2, 8, 200 + ITEM_ESSENCE3, 1,	//희귀
	50 + ITEM_LEATHER_LV2, 8, 100 + ITEM_CLOTH_LV2, 8, 200 + ITEM_ESSENCE3, 1,	//세트
	50 + ITEM_LEATHER_LV3, 4, 100 + ITEM_CLOTH_LV3, 4, 255, 0,	//나이트 킬트
	50 + ITEM_LEATHER_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE5, 1,	//고급
	50 + ITEM_LEATHER_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE5, 2,	//희귀
	50 + ITEM_LEATHER_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE7, 1,	//세트
	50 + ITEM_LEATHER_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE32, 1,	//배틀 킬트
	50 + ITEM_LEATHER_LV4, 4, 100 + ITEM_CLOTH_LV4, 4, 255, 0,	//스컬 킬트
	50 + ITEM_LEATHER_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE9, 1,	//고급
	50 + ITEM_LEATHER_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE9, 2,	//희귀
	50 + ITEM_LEATHER_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE11, 1,	//세트
	50 + ITEM_LEATHER_LV4, 12, 100 + ITEM_CLOTH_LV4, 12, 200 + ITEM_ESSENCE34, 1,	//사령의 바지
	50 + ITEM_LEATHER_LV5, 4, 100 + ITEM_CLOTH_LV5, 4, 255, 0,	//수령의 바지
	50 + ITEM_LEATHER_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE15, 1,	//고급
	50 + ITEM_LEATHER_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE15, 2,	//희귀
	50 + ITEM_LEATHER_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE17, 1,	//세트
	50 + ITEM_LEATHER_LV5, 12, 100 + ITEM_CLOTH_LV5, 12, 200 + ITEM_ESSENCE36, 1,	//토르의 바지
	50 + ITEM_LEATHER_LV6, 4, 100 + ITEM_CLOTH_LV6, 4, 255, 0,	//미스릴 킬트
	50 + ITEM_LEATHER_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE19, 1,	//고급
	50 + ITEM_LEATHER_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE19, 2,	//희귀
	50 + ITEM_LEATHER_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE20, 1,	//세트
	50 + ITEM_LEATHER_LV6, 12, 100 + ITEM_CLOTH_LV6, 12, 200 + ITEM_ESSENCE38, 1,	//페어리 킬트
	50 + ITEM_LEATHER_LV7, 4, 100 + ITEM_CLOTH_LV7, 4, 255, 0,	//에인션트 킬트
	50 + ITEM_LEATHER_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE27, 1,	//고급
	50 + ITEM_LEATHER_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE27, 2,	//희귀
	50 + ITEM_LEATHER_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE23, 1,	//세트
	50 + ITEM_LEATHER_LV7, 12, 100 + ITEM_CLOTH_LV7, 12, 200 + ITEM_ESSENCE40, 1,	//이터널 킬트
	50 + ITEM_LEATHER_LV7, 15, 100 + ITEM_CLOTH_LV7, 15, 200 + ITEM_ESSENCE42, 1,	//언리밋 킬트
	50 + ITEM_LEATHER_LV8, 4, 100 + ITEM_CLOTH_LV8, 4, 255, 0,	//용수염 킬트
	50 + ITEM_LEATHER_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE29, 1,	//고급
	50 + ITEM_LEATHER_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE29, 2,	//희귀
	50 + ITEM_LEATHER_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE31, 1,	//세트
	50 + ITEM_LEATHER_LV8, 12, 100 + ITEM_CLOTH_LV8, 12, 200 + ITEM_ESSENCE43, 1,	//청룡의 킬트
	50 + ITEM_LEATHER_LV8, 15, 100 + ITEM_CLOTH_LV8, 15, 200 + ITEM_ESSENCE44, 1,	//용기사 바지

	//바지 : ITEM_SKIRT
	150 + ITEM_WOOD_LV1, 4, 100 + ITEM_CLOTH_LV1, 4, 255, 0,	//양단 스커트
	150 + ITEM_WOOD_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE0, 1,	//고급
	150 + ITEM_WOOD_LV1, 8, 100 + ITEM_CLOTH_LV1, 8, 200 + ITEM_ESSENCE0, 1,	//희귀
	150 + ITEM_WOOD_LV1, 8, 100 + ITEM_CLOTH_LV1, 8, 200 + ITEM_ESSENCE0, 1,	//세트
	150 + ITEM_WOOD_LV2, 4, 100 + ITEM_CLOTH_LV2, 4, 255, 0,	//빈티지 스커트
	150 + ITEM_WOOD_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE3, 1,	//고급
	150 + ITEM_WOOD_LV2, 8, 100 + ITEM_CLOTH_LV2, 8, 200 + ITEM_ESSENCE3, 1,	//희귀
	150 + ITEM_WOOD_LV2, 8, 100 + ITEM_CLOTH_LV2, 8, 200 + ITEM_ESSENCE3, 1,	//세트
	150 + ITEM_WOOD_LV3, 4, 100 + ITEM_CLOTH_LV3, 4, 255, 0,	//단풍염색 치마
	150 + ITEM_WOOD_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE4, 1,	//고급
	150 + ITEM_WOOD_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE4, 2,	//희귀
	150 + ITEM_WOOD_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE7, 1,	//세트
	150 + ITEM_WOOD_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE32, 1,	//홍련의 스커트
	150 + ITEM_WOOD_LV4, 4, 100 + ITEM_CLOTH_LV4, 4, 255, 0,	//벨벳 스커트
	150 + ITEM_WOOD_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE9, 1,	//고급
	150 + ITEM_WOOD_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE9, 2,	//희귀
	150 + ITEM_WOOD_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE11, 1,	//세트
	150 + ITEM_WOOD_LV4, 12, 100 + ITEM_CLOTH_LV4, 12, 200 + ITEM_ESSENCE34, 1,	//소공녀의 치마
	150 + ITEM_WOOD_LV5, 4, 100 + ITEM_CLOTH_LV5, 4, 255, 0,	//폭풍의 스커트
	150 + ITEM_WOOD_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE13, 1,	//고급
	150 + ITEM_WOOD_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE13, 2,	//희귀
	150 + ITEM_WOOD_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE17, 1,	//세트
	150 + ITEM_WOOD_LV5, 12, 100 + ITEM_CLOTH_LV5, 12, 200 + ITEM_ESSENCE36, 1,	//무지개빛 치마
	150 + ITEM_WOOD_LV6, 4, 100 + ITEM_CLOTH_LV6, 4, 255, 0,	//금실의 치마
	150 + ITEM_WOOD_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE18, 1,	//고급
	150 + ITEM_WOOD_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE18, 2,	//희귀
	150 + ITEM_WOOD_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE21, 1,	//세트
	150 + ITEM_WOOD_LV6, 12, 100 + ITEM_CLOTH_LV6, 12, 200 + ITEM_ESSENCE38, 1,	//여제의 스커트
	150 + ITEM_WOOD_LV7, 4, 100 + ITEM_CLOTH_LV7, 4, 255, 0,	//영광의 치마
	150 + ITEM_WOOD_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE27, 1,	//고급
	150 + ITEM_WOOD_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE27, 2,	//희귀
	150 + ITEM_WOOD_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE23, 1,	//세트
	150 + ITEM_WOOD_LV7, 12, 100 + ITEM_CLOTH_LV7, 12, 200 + ITEM_ESSENCE40, 1,	//현자의 치마
	150 + ITEM_WOOD_LV7, 15, 100 + ITEM_CLOTH_LV7, 15, 200 + ITEM_ESSENCE42, 1,	//성령의 치마
	150 + ITEM_WOOD_LV8, 4, 100 + ITEM_CLOTH_LV8, 4, 255, 0,	//사제의 스커트
	150 + ITEM_WOOD_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE28, 1,	//고급
	150 + ITEM_WOOD_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE28, 2,	//희귀
	150 + ITEM_WOOD_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE31, 1,	//세트
	150 + ITEM_WOOD_LV8, 12, 100 + ITEM_CLOTH_LV8, 12, 200 + ITEM_ESSENCE43, 1,	//비슈누 스커트
	150 + ITEM_WOOD_LV8, 15, 100 + ITEM_CLOTH_LV8, 15, 200 + ITEM_ESSENCE44, 1,	//태양의 스커트

	//바지 : ITEM_PANTS
	ITEM_IRON_LV1, 4, 100 + ITEM_CLOTH_LV1, 4, 255, 0,	//승마용 바지
	ITEM_IRON_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE0, 1,	//고급
	ITEM_IRON_LV1, 8, 100 + ITEM_CLOTH_LV1, 8, 200 + ITEM_ESSENCE0, 1,	//희귀
	ITEM_IRON_LV1, 8, 100 + ITEM_CLOTH_LV1, 8, 200 + ITEM_ESSENCE0, 1,	//세트
	ITEM_IRON_LV2, 4, 100 + ITEM_CLOTH_LV2, 4, 255, 0,	//카프스킨 팬츠
	ITEM_IRON_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE2, 1,	//고급
	ITEM_IRON_LV2, 8, 100 + ITEM_CLOTH_LV2, 8, 200 + ITEM_ESSENCE2, 1,	//희귀
	ITEM_IRON_LV2, 8, 100 + ITEM_CLOTH_LV2, 8, 200 + ITEM_ESSENCE2, 1,	//세트
	ITEM_IRON_LV3, 4, 100 + ITEM_CLOTH_LV3, 4, 255, 0,	//올드 팬츠
	ITEM_IRON_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE4, 1,	//고급
	ITEM_IRON_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE4, 2,	//희귀
	ITEM_IRON_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE6, 1,	//세트
	ITEM_IRON_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE32, 1,	//머미 밴디지
	ITEM_IRON_LV4, 4, 100 + ITEM_CLOTH_LV4, 4, 255, 0,	//흑단의 바지
	ITEM_IRON_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE8, 1,	//고급
	ITEM_IRON_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE8, 2,	//희귀
	ITEM_IRON_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE10, 1,	//세트
	ITEM_IRON_LV4, 12, 100 + ITEM_CLOTH_LV4, 12, 200 + ITEM_ESSENCE34, 1,	//어쌔신 팬츠
	ITEM_IRON_LV5, 4, 100 + ITEM_CLOTH_LV5, 4, 255, 0,	//세일러 팬츠
	ITEM_IRON_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE14, 1,	//고급
	ITEM_IRON_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE14, 2,	//희귀
	ITEM_IRON_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE16, 1,	//세트
	ITEM_IRON_LV5, 12, 100 + ITEM_CLOTH_LV5, 12, 200 + ITEM_ESSENCE36, 1,	//제독의 바지
	ITEM_IRON_LV6, 4, 100 + ITEM_CLOTH_LV6, 4, 255, 0,	//데저트 팬츠
	ITEM_IRON_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE18, 1,	//고급
	ITEM_IRON_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE18, 2,	//희귀
	ITEM_IRON_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE24, 1,	//세트
	ITEM_IRON_LV6, 12, 100 + ITEM_CLOTH_LV6, 12, 200 + ITEM_ESSENCE38, 1,	//캐러밴 팬츠
	ITEM_IRON_LV7, 4, 100 + ITEM_CLOTH_LV7, 4, 255, 0,	//카오틱 팬츠
	ITEM_IRON_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE26, 1,	//고급
	ITEM_IRON_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE26, 2,	//희귀
	ITEM_IRON_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE22, 1,	//세트
	ITEM_IRON_LV7, 12, 100 + ITEM_CLOTH_LV7, 12, 200 + ITEM_ESSENCE40, 1,	//침묵의 바지
	ITEM_IRON_LV7, 15, 100 + ITEM_CLOTH_LV7, 15, 200 + ITEM_ESSENCE42, 1,	//망령의 바지
	ITEM_IRON_LV8, 4, 100 + ITEM_CLOTH_LV8, 4, 255, 0,	//가디안 팬츠
	ITEM_IRON_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE28, 1,	//고급
	ITEM_IRON_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE28, 2,	//희귀
	ITEM_IRON_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE30, 1,	//세트
	ITEM_IRON_LV8, 12, 100 + ITEM_CLOTH_LV8, 12, 200 + ITEM_ESSENCE43, 1,	//켈베로스 레더
	ITEM_IRON_LV8, 15, 100 + ITEM_CLOTH_LV8, 15, 200 + ITEM_ESSENCE44, 1,	//아누비스 바지

	//장화 : ITEM_GREAVES
	50 + ITEM_LEATHER_LV1, 2, 100 + ITEM_CLOTH_LV1, 2, 255, 0,	//코퍼 그리브
	50 + ITEM_LEATHER_LV1, 4, 100 + ITEM_CLOTH_LV1, 4, 200 + ITEM_ESSENCE1, 1,	//고급
	50 + ITEM_LEATHER_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE1, 1,	//희귀
	50 + ITEM_LEATHER_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE1, 1,	//세트
	50 + ITEM_LEATHER_LV2, 2, 100 + ITEM_CLOTH_LV2, 2, 255, 0,	//밴디트 그리브
	50 + ITEM_LEATHER_LV2, 4, 100 + ITEM_CLOTH_LV2, 4, 200 + ITEM_ESSENCE3, 1,	//고급
	50 + ITEM_LEATHER_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE3, 1,	//희귀
	50 + ITEM_LEATHER_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE3, 1,	//세트
	50 + ITEM_LEATHER_LV3, 2, 100 + ITEM_CLOTH_LV3, 2, 255, 0,	//체인 그리브
	50 + ITEM_LEATHER_LV3, 4, 100 + ITEM_CLOTH_LV3, 4, 200 + ITEM_ESSENCE5, 1,	//고급
	50 + ITEM_LEATHER_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE5, 2,	//희귀
	50 + ITEM_LEATHER_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE7, 1,	//세트
	50 + ITEM_LEATHER_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE33, 1,	//나이트 그리브
	50 + ITEM_LEATHER_LV4, 2, 100 + ITEM_CLOTH_LV4, 2, 255, 0,	//프로즌그리브
	50 + ITEM_LEATHER_LV4, 4, 100 + ITEM_CLOTH_LV4, 4, 200 + ITEM_ESSENCE9, 1,	//고급
	50 + ITEM_LEATHER_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE9, 2,	//희귀
	50 + ITEM_LEATHER_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE11, 1,	//세트
	50 + ITEM_LEATHER_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE34, 1,	//만년설의 신발
	50 + ITEM_LEATHER_LV5, 2, 100 + ITEM_CLOTH_LV5, 2, 255, 0,	//플레이트 슈즈
	50 + ITEM_LEATHER_LV5, 4, 100 + ITEM_CLOTH_LV5, 4, 200 + ITEM_ESSENCE15, 1,	//고급
	50 + ITEM_LEATHER_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE15, 2,	//희귀
	50 + ITEM_LEATHER_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE17, 1,	//세트
	50 + ITEM_LEATHER_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE37, 1,	//드워븐 그리브
	50 + ITEM_LEATHER_LV6, 2, 100 + ITEM_CLOTH_LV6, 2, 255, 0,	//빅풋그리브
	50 + ITEM_LEATHER_LV6, 4, 100 + ITEM_CLOTH_LV6, 4, 200 + ITEM_ESSENCE19, 1,	//고급
	50 + ITEM_LEATHER_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE19, 2,	//희귀
	50 + ITEM_LEATHER_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE25, 1,	//세트
	50 + ITEM_LEATHER_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE39, 1,	//골렘 그리브
	50 + ITEM_LEATHER_LV7, 2, 100 + ITEM_CLOTH_LV7, 2, 255, 0,	//마검사의 신발
	50 + ITEM_LEATHER_LV7, 4, 100 + ITEM_CLOTH_LV7, 4, 200 + ITEM_ESSENCE27, 1,	//고급
	50 + ITEM_LEATHER_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE27, 2,	//희귀
	50 + ITEM_LEATHER_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE23, 1,	//세트
	50 + ITEM_LEATHER_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE41, 1,	//사령의 신발
	50 + ITEM_LEATHER_LV7, 12, 100 + ITEM_CLOTH_LV7, 12, 200 + ITEM_ESSENCE42, 1,	//종말의 발소리
	50 + ITEM_LEATHER_LV8, 2, 100 + ITEM_CLOTH_LV8, 2, 255, 0,	//드래곤 그리브
	50 + ITEM_LEATHER_LV8, 4, 100 + ITEM_CLOTH_LV8, 4, 200 + ITEM_ESSENCE29, 1,	//고급
	50 + ITEM_LEATHER_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE29, 2,	//희귀
	50 + ITEM_LEATHER_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE31, 1,	//세트
	50 + ITEM_LEATHER_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE43, 1,	//마룡의 발자국
	50 + ITEM_LEATHER_LV8, 12, 100 + ITEM_CLOTH_LV8, 12, 200 + ITEM_ESSENCE44, 1,	//가이아 그리브

	//신발 : ITEM_SHOES
	150 + ITEM_WOOD_LV1, 2, 100 + ITEM_CLOTH_LV1, 2, 255, 0,	//웨스턴 부츠
	150 + ITEM_WOOD_LV1, 4, 100 + ITEM_CLOTH_LV1, 4, 200 + ITEM_ESSENCE0, 1,	//고급
	150 + ITEM_WOOD_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE0, 1,	//희귀
	150 + ITEM_WOOD_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE0, 1,	//세트
	150 + ITEM_WOOD_LV2, 2, 100 + ITEM_CLOTH_LV2, 2, 255, 0,	//스웨이드 부츠
	150 + ITEM_WOOD_LV2, 4, 100 + ITEM_CLOTH_LV2, 4, 200 + ITEM_ESSENCE3, 1,	//고급
	150 + ITEM_WOOD_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE3, 1,	//희귀
	150 + ITEM_WOOD_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE3, 1,	//세트
	150 + ITEM_WOOD_LV3, 2, 100 + ITEM_CLOTH_LV3, 2, 255, 0,	//라이딩 부츠
	150 + ITEM_WOOD_LV3, 4, 100 + ITEM_CLOTH_LV3, 4, 200 + ITEM_ESSENCE4, 1,	//고급
	150 + ITEM_WOOD_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE4, 2,	//희귀
	150 + ITEM_WOOD_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE7, 1,	//세트
	150 + ITEM_WOOD_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE33, 1,	//밀리터리 워커
	150 + ITEM_WOOD_LV4, 2, 100 + ITEM_CLOTH_LV4, 2, 255, 0,	//리치 부츠
	150 + ITEM_WOOD_LV4, 4, 100 + ITEM_CLOTH_LV4, 4, 200 + ITEM_ESSENCE9, 1,	//고급
	150 + ITEM_WOOD_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE9, 2,	//희귀
	150 + ITEM_WOOD_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE11, 1,	//세트
	150 + ITEM_WOOD_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE34, 1,	//팬텀 테일즈
	150 + ITEM_WOOD_LV5, 2, 100 + ITEM_CLOTH_LV5, 2, 255, 0,	//귀부인의 신발
	150 + ITEM_WOOD_LV5, 4, 100 + ITEM_CLOTH_LV5, 4, 200 + ITEM_ESSENCE13, 1,	//고급
	150 + ITEM_WOOD_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE13, 2,	//희귀
	150 + ITEM_WOOD_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE17, 1,	//세트
	150 + ITEM_WOOD_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE37, 1,	//로얄 셀레브
	150 + ITEM_WOOD_LV6, 2, 100 + ITEM_CLOTH_LV6, 2, 255, 0,	//칠흑의 부츠
	150 + ITEM_WOOD_LV6, 4, 100 + ITEM_CLOTH_LV6, 4, 200 + ITEM_ESSENCE18, 1,	//고급
	150 + ITEM_WOOD_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE18, 2,	//희귀
	150 + ITEM_WOOD_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE20, 1,	//세트
	150 + ITEM_WOOD_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE39, 1,	//마녀의 부츠
	150 + ITEM_WOOD_LV7, 2, 100 + ITEM_CLOTH_LV7, 2, 255, 0,	//프리즘 부츠
	150 + ITEM_WOOD_LV7, 4, 100 + ITEM_CLOTH_LV7, 4, 200 + ITEM_ESSENCE27, 1,	//고급
	150 + ITEM_WOOD_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE27, 2,	//희귀
	150 + ITEM_WOOD_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE23, 1,	//세트
	150 + ITEM_WOOD_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE41, 1,	//미라클 부츠
	150 + ITEM_WOOD_LV7, 12, 100 + ITEM_CLOTH_LV7, 12, 200 + ITEM_ESSENCE42, 1,	//그라비티 부츠
	150 + ITEM_WOOD_LV8, 2, 100 + ITEM_CLOTH_LV8, 2, 255, 0,	//베이그란트
	150 + ITEM_WOOD_LV8, 4, 100 + ITEM_CLOTH_LV8, 4, 200 + ITEM_ESSENCE28, 1,	//고급
	150 + ITEM_WOOD_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE28, 2,	//희귀
	150 + ITEM_WOOD_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE31, 1,	//세트
	150 + ITEM_WOOD_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE43, 1,	//페이트 부츠
	150 + ITEM_WOOD_LV8, 12, 100 + ITEM_CLOTH_LV8, 12, 200 + ITEM_ESSENCE44, 1,	//데스티니 부츠

	//부츠 : ITEM_BOOTS
	ITEM_IRON_LV1, 2, 100 + ITEM_CLOTH_LV1, 2, 255, 0,	//스니커즈
	ITEM_IRON_LV1, 4, 100 + ITEM_CLOTH_LV1, 4, 200 + ITEM_ESSENCE0, 1,	//고급
	ITEM_IRON_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE0, 1,	//희귀
	ITEM_IRON_LV1, 6, 100 + ITEM_CLOTH_LV1, 6, 200 + ITEM_ESSENCE0, 1,	//세트
	ITEM_IRON_LV2, 2, 100 + ITEM_CLOTH_LV2, 2, 255, 0,	//스캐빈저 슈즈
	ITEM_IRON_LV2, 4, 100 + ITEM_CLOTH_LV2, 4, 200 + ITEM_ESSENCE2, 1,	//고급
	ITEM_IRON_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE2, 1,	//희귀
	ITEM_IRON_LV2, 6, 100 + ITEM_CLOTH_LV2, 6, 200 + ITEM_ESSENCE2, 1,	//세트
	ITEM_IRON_LV3, 2, 100 + ITEM_CLOTH_LV3, 2, 255, 0,	//천둥가죽 신발
	ITEM_IRON_LV3, 4, 100 + ITEM_CLOTH_LV3, 4, 200 + ITEM_ESSENCE4, 1,	//고급
	ITEM_IRON_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE4, 2,	//희귀
	ITEM_IRON_LV3, 6, 100 + ITEM_CLOTH_LV3, 6, 200 + ITEM_ESSENCE6, 1,	//세트
	ITEM_IRON_LV3, 8, 100 + ITEM_CLOTH_LV3, 8, 200 + ITEM_ESSENCE33, 1,	//낙뢰의 자국
	ITEM_IRON_LV4, 2, 100 + ITEM_CLOTH_LV4, 2, 255, 0,	//가드너 슈즈
	ITEM_IRON_LV4, 4, 100 + ITEM_CLOTH_LV4, 4, 200 + ITEM_ESSENCE8, 1,	//고급
	ITEM_IRON_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE8, 2,	//희귀
	ITEM_IRON_LV4, 6, 100 + ITEM_CLOTH_LV4, 6, 200 + ITEM_ESSENCE10, 1,	//세트
	ITEM_IRON_LV4, 8, 100 + ITEM_CLOTH_LV4, 8, 200 + ITEM_ESSENCE34, 1,	//토렌트 루트
	ITEM_IRON_LV5, 2, 100 + ITEM_CLOTH_LV5, 2, 255, 0,	//세일러 슈즈
	ITEM_IRON_LV5, 4, 100 + ITEM_CLOTH_LV5, 4, 200 + ITEM_ESSENCE14, 1,	//고급
	ITEM_IRON_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE14, 2,	//희귀
	ITEM_IRON_LV5, 6, 100 + ITEM_CLOTH_LV5, 6, 200 + ITEM_ESSENCE16, 1,	//세트
	ITEM_IRON_LV5, 8, 100 + ITEM_CLOTH_LV5, 8, 200 + ITEM_ESSENCE37, 1,	//캡틴 슈즈
	ITEM_IRON_LV6, 2, 100 + ITEM_CLOTH_LV6, 2, 255, 0,	//저승의 신발
	ITEM_IRON_LV6, 4, 100 + ITEM_CLOTH_LV6, 4, 200 + ITEM_ESSENCE18, 1,	//고급
	ITEM_IRON_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE18, 2,	//희귀
	ITEM_IRON_LV6, 6, 100 + ITEM_CLOTH_LV6, 6, 200 + ITEM_ESSENCE21, 1,	//세트
	ITEM_IRON_LV6, 8, 100 + ITEM_CLOTH_LV6, 8, 200 + ITEM_ESSENCE39, 1,	//헬 스트라이더
	ITEM_IRON_LV7, 2, 100 + ITEM_CLOTH_LV7, 2, 255, 0,	//엘레멘탈 슈즈
	ITEM_IRON_LV7, 4, 100 + ITEM_CLOTH_LV7, 4, 200 + ITEM_ESSENCE26, 1,	//고급
	ITEM_IRON_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE26, 2,	//희귀
	ITEM_IRON_LV7, 6, 100 + ITEM_CLOTH_LV7, 6, 200 + ITEM_ESSENCE22, 1,	//세트
	ITEM_IRON_LV7, 8, 100 + ITEM_CLOTH_LV7, 8, 200 + ITEM_ESSENCE40, 1,	//브리징 윈드
	ITEM_IRON_LV7, 12, 100 + ITEM_CLOTH_LV7, 12, 200 + ITEM_ESSENCE42, 1,	//템페스트 슈즈
	ITEM_IRON_LV8, 2, 100 + ITEM_CLOTH_LV8, 2, 255, 0,	//에어워커
	ITEM_IRON_LV8, 4, 100 + ITEM_CLOTH_LV8, 4, 200 + ITEM_ESSENCE28, 1,	//고급
	ITEM_IRON_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE28, 2,	//희귀
	ITEM_IRON_LV8, 6, 100 + ITEM_CLOTH_LV8, 6, 200 + ITEM_ESSENCE30, 1,	//세트
	ITEM_IRON_LV8, 8, 100 + ITEM_CLOTH_LV8, 8, 200 + ITEM_ESSENCE43, 1,	//클라우드 슈즈
	ITEM_IRON_LV8, 12, 100 + ITEM_CLOTH_LV8, 12, 200 + ITEM_ESSENCE44, 1,	//헤븐리 슈즈
};
static const unsigned char itemCooltime_builtin[] = {
	10,	//귀환서
	10,	//별의 씨앗
	10,	//달의 씨앗
	10,	//태양의 씨앗
	10,	//은빛 허브
	10,	//금빛 허브
	10,	//진홍빛 허브
	10,	//세계수의 물
	10,	//풀피리
	10,	//안약
	10,	//해독제
	10,	//릴의 날개
	10,	//성수
	15,	//불의 정령석
	15,	//물의 정령석
	15,	//번개의 정령석
	15,	//빛의 정령석
	15,	//어둠의 정령석
	20,	//화염의 정령석
	20,	//얼음의 정령석
	20,	//천둥의 정령석
	20,	//섬광의 정령석
	20,	//칠흑의 정령석
};
static const unsigned short itemIconTable_builtin[] = {
	//ITEM_SWORD
	64 * 3 + 24 + 0,//연습용 몽둥이
	64 * 3 + 24 + 1,//롱소드
	64 * 3 + 24 + 2,//처형자의 검
	64 * 6 + 10 + 31,//파멸의 참마도
	64 * 3 + 24 + 3,//추적자의 검
	64 * 6 + 10 + 0,//격노의 양날검
	64 * 3 + 24 + 4,//수호자의 검
	64 * 6 + 10 + 1,//왕가의 수호자
	64 * 3 + 24 + 5,//나찰의 검
	64 * 6 + 10 + 2,//소울 크래셔
	64 * 6 + 10 + 3,//플레임소드
	64 * 6 + 10 + 4,//아이스소드
	64 * 6 + 10 + 5,//썬더소드
	64 * 6 + 10 + 6,//어스소드
	64 * 6 + 10 + 7,//레바테인
	64 * 6 + 10 + 8,//스톰브링거
	64 * 6 + 10 + 9,//칼라드볼그
	64 * 6 + 10 + 10,//발뭉
	64 * 6 + 10 + 13,//흐룬팅
	64 * 6 + 10 + 14,//거인의 칼
	64 * 6 + 10 + 15,//미스틸테인
	64 * 6 + 10 + 16,//엑스칼리버
	64 * 6 + 10 + 11,//홀리소드
	64 * 6 + 10 + 12,//다크소드
	64 * 6 + 10 + 17,//레오소드
	64 * 6 + 10 + 18,//사신의 낫
	64 * 6 + 10 + 19,//드래곤 클로우
	64 * 6 + 10 + 20,//황룡의 어금니
	64 * 3 + 24 + 7,//신룡마강검
	64 * 6 + 10 + 21,//드래곤 슬레이어
	64 * 3 + 24 + 6,//얼티밋소드
	64 * 6 + 10 + 22,//차원의 검
	64 * 6 + 10 + 23,//천공의 검
	64 * 6 + 10 + 24,//스타더스트
	64 * 6 + 10 + 25,//패왕의 검

	//ITEM_GUN
	64 * 3 + 32,//발화식 총
	64 * 3 + 33,//리볼버 파이슨
	64 * 3 + 34,//45구경 오토건
	64 * 3 + 35,//고져스 건
	64 * 3 + 36,//회천마도총
	64 * 3 + 37,//태양의 총
	64 * 3 + 38,//헬파이어 건
	64 * 3 + 39,//크로스 파이어

	//ITEM_BOOMERANG
	64 * 3 + 40,//사냥용 부메랑
	64 * 3 + 41,//슬라이서
	64 * 3 + 42,//강철 부메랑
	64 * 3 + 43,//트라이 엣지
	64 * 3 + 44,//라이트닝 엣지
	64 * 3 + 45,//소울 체이서
	64 * 3 + 46,//그리폰 윙
	64 * 3 + 47,//로커스트 헌트

	//ITEM_HELM
	64 * 3 + 48,//헤드 가드
	64 * 3 + 49,//바시넷
	64 * 3 + 50,//솔저헬름
	64 * 3 + 51,//검투사의 투구
	64 * 3 + 52,//스파이크 헤드
	64 * 3 + 53,//그랜드 헬름
	64 * 3 + 54,//고대의 투구
	64 * 3 + 55,//용자의 투구

	//ITEM_HAT
	64 * 3 + 56,//카우보이 모자
	64 * 3 + 57,//산책용 보닛
	64 * 3 + 58,//레인저 햇
	64 * 3 + 59,//서클릿
	64 * 3 + 60,//올드 윌로우
	64 * 3 + 61,//스나이퍼 고글
	64 * 3 + 62,//혼란의 모자
	64 * 3 + 63,//프리에스테스

	//ITEM_CAP
	64 * 4 + 0,//사냥용 부메랑
	64 * 4 + 1,//슬라이서
	64 * 4 + 2,//강철 부메랑
	64 * 4 + 3,//트라이 엣지
	64 * 4 + 4,//라이트닝 엣지
	64 * 4 + 5,//소울 체이서
	64 * 4 + 6,//그리폰 윙
	64 * 4 + 7,//로커스트 헌트

	//ITEM_ARMOR
	64 * 4 + 8,//헌터 튜닉
	64 * 4 + 9,//미늘 갑옷
	64 * 4 + 10,//하프 플레이트
	64 * 4 + 11,//스컬 메일
	64 * 4 + 12,//황금세공 갑옷
	64 * 4 + 13,//미스릴 아머
	64 * 4 + 14,//고대의 갑옷
	64 * 4 + 15,//용비늘 갑옷

	//ITEM_VEST
	64 * 4 + 16,//카우보이 조끼
	64 * 4 + 17,//실크 조끼
	64 * 4 + 18,//방랑자의 조끼
	64 * 4 + 19,//도적의 조끼
	64 * 4 + 20,//벨벳 셔츠
	64 * 4 + 21,//귀족의 조끼
	64 * 4 + 22,//진홍빛 셔츠
	64 * 4 + 23,//신관의 로브

	//ITEM_COAT
	64 * 4 + 24,//수수한 코트
	64 * 4 + 25,//패딩 아머
	64 * 4 + 26,//털가죽 코트
	64 * 4 + 27,//큐어 보일
	64 * 4 + 28,//귀족의 코트
	64 * 4 + 29,//극지의 코트
	64 * 4 + 30,//윙 코트
	64 * 4 + 31,//바이스 코트

	//ITEM_GUNTLET
	64 * 4 + 32,//핸드 가드
	64 * 4 + 33,///청동 장갑
	64 * 4 + 34,//체인 건틀렛
	64 * 4 + 35,//나이트 글로브
	64 * 4 + 36,//비스트 핸드
	64 * 4 + 37,//라이징 건틀렛
	64 * 4 + 38,//광전사의 장갑
	64 * 4 + 39,//드래곤 핸드

	//ITEM_ARMLET
	64 * 4 + 40,//사제의 묵주
	64 * 4 + 41,//여행자의 팔찌
	64 * 4 + 42,//백금 브레스렛
	64 * 4 + 43,//전사의 암렛
	64 * 4 + 44,//에메랄드 팔찌
	64 * 4 + 45,//이블 암렛
	64 * 4 + 46,//위엄의 팔찌
	64 * 4 + 47,//영웅의 팔찌

	//ITEM_GLOVE
	64 * 4 + 48,//여행자의 장갑
	64 * 4 + 49,//이중매듭 장갑
	64 * 4 + 50,//소매치기 장갑
	64 * 4 + 51,//실크 글로브
	64 * 4 + 52,//세공사의 장갑
	64 * 4 + 53,//마법문양 장갑
	64 * 4 + 54,//심판의 손
	64 * 4 + 55,//성자의 장갑

	//ITEM_KILT
	64 * 4 + 56,//밴딩 킬트
	64 * 4 + 57,//체인 킬트
	64 * 4 + 58,//나이트 킬트
	64 * 4 + 59,//스컬 킬트
	64 * 4 + 60,//수령의 바지
	64 * 4 + 61,//미스릴 킬트
	64 * 4 + 62,//에인션트 킬트
	64 * 4 + 63,//용수염 킬트

	//ITEM_SKIRT
	64 * 5 + 0,//양단 스커트
	64 * 5 + 1,//빈티지 스커트
	64 * 5 + 2,//단풍염색 치마
	64 * 5 + 3,//벨벳 스커트
	64 * 5 + 4,//폭풍의 스커트
	64 * 5 + 5,//금실의 치마
	64 * 5 + 6,//영광의 치마
	64 * 5 + 7,//사제의 스커트

	//ITEM_PANTS
	64 * 5 + 8,//승마용 바지
	64 * 5 + 9,//카프스킨 팬츠
	64 * 5 + 10,//망령의 팬츠
	64 * 5 + 11,//흑단의 바지
	64 * 5 + 12,//세일러 팬츠
	64 * 5 + 13,//데저트 팬츠
	64 * 5 + 14,//카오틱 팬츠
	64 * 5 + 15,//가디안 팬츠

	//ITEM_GREAVES
	64 * 5 + 16,//코퍼 그리브
	64 * 5 + 17,//밴디트 그리브
	64 * 5 + 18,//체인 그리브
	64 * 5 + 19,//프로즌 그리브
	64 * 5 + 20,//플레이트 부츠
	64 * 5 + 21,//빅풋 그리브
	64 * 5 + 22,//마검사의 신발
	64 * 5 + 23,//드래곤 그리브

	//ITEM_SHEOS
	64 * 5 + 24,//웨스턴 슈즈
	64 * 5 + 25,//스웨이드 슈즈
	64 * 5 + 26,//라이딩 슈즈
	64 * 5 + 27,//칠흑의 슈즈
	64 * 5 + 28,//귀부인의 신발
	64 * 5 + 29,//리치 슈즈
	64 * 5 + 30,//프리즘 슈즈
	64 * 5 + 31,//베이그란트

	//ITEM_BOOTS
	64 * 5 + 32,//스니커즈
	64 * 5 + 33,//스캐빈저 부츠
	64 * 5 + 34,//천둥가죽 신발
	64 * 5 + 35,//가드너 부츠
	64 * 5 + 36,//세일러 부츠
	64 * 5 + 37,//저승의 신발
	64 * 5 + 38,//엘레멘탈 부츠
	64 * 5 + 39,//에어워커

	//ITEM_NECK
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,	//28

	//ITEM_RING
	28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45,	//46

	//ITEM_GEM
	46, 47, 48, 49, 50, 51,	//52

	//ITEM_WASTE
	24, 52, 53, 54, 55, 56, 57, 58, 5, 60, 59, 62, 61, 63, 64, 65, 66, 67, 46, 47, 48, 49, 50, 207, 208, 210, 209,	//79

	//ITEM_IRON
	68, 69, 70, 71, 72, 73, 74, 75,	//87

	//ITEM_LEATHER
	76, 77, 78, 79, 80, 81, 82, 83,	//95

	//ITEM_CLOTH
	84, 7, 85, 86, 87, 88, 89, 90,	//103

	//ITEM_WOOD
	91, 92, 93, 94, 95, 96, 97, 98,	//111

	//ITEM_ESSENCE
	99, 100, 20, 101, 102, 103, 104, 105, 21, 106, 107, 8, 108, 109, 110, 13, 61, 111, 56, 59, 128, 113, 114, 115, 0, 116, 117, 16, 118, 119, 1, 27, 120, 121, 122, 123, 124, 125, 126, 18, 17, 127, 128, 129, 19,	//156

	//ITEM_RECIPE
	24,	//157

	//ITEM_QUEST
	112, ITEM_GOLDBAR_ICON, 2, 159, 187, 160, 161, 188, 24, 191, 189, 190, 191, 190, 191, 191, 197, 24, 191, 191, 191, 191, 191, 28, 181, 192, 193, 194, 195, 196, 198, 198, 190, 181, 182,//192

	//ITEM_NETITEM
	200, 201, 202, 203, 204, 205, 206, 167, 166, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 162, 163, 164, 165, 211, 212, 213, 214, 215, 180,

	//ITEM_GOLD
	179,	//223

	//ITEM_KEY
	146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 15, 183, 184, 185,	//240

	//ITEM_STATUE
	130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145,	//256

	//ITEM_HEART
	ICON_HEART,

	//ITEM_MEDAL
	ICON_MEDAL,

	//ITEM_STAR
	ICON_STAR,

	//ITEM_HAMMER
	ICON_HAMMER,

	//ITEM_SHIELD
	ICON_SHIELD,

	//ITEM_BOX
	64 * 7 + 0, 64 * 7 + 1, 64 * 7 + 2, 64 * 7 + 3, 64 * 7 + 4, 64 * 7 + 5, 64 * 7 + 6, 64 * 7 + 7, 64 * 7 + 8, 64 * 7 + 9, 64 * 7 + 10, 64 * 7 + 11, 64 * 7 + 12, 64 * 7 + 13, 64 * 7 + 14,

	//ITEM_CREW


};
static const unsigned int neckOption_builtin[] = {
	//명예의 펜던트(적중)
	PS_HIT, SUFFIX_HIT, 1, 2, 4, 7,
	//연옥의 브로치(치명타)
	PS_CRITICAL, PREFIX_CRITICAL, 1, 2, 4, 7,
	//찰나의 팔찌(치명타 데미지)
	PS_CRITDMG, SUFFIX_CRITICAL, 2, 5, 10, 20,
	//황금 바늘(관통)
	PS_PIERCE, PREFIX_PIERCE, 1, 2, 4, 7,
	//파열의 팔찌(추가타)
	PS_EXTRA, PREFIX_EXTRA, 1, 2, 4, 7,
	//메피스토 피리(방어무시)
	PS_IGNORE, SUFFIX_IGNORE, 1, 3, 7, 12,
	//사멸의 하프(기절공격)
	PS_STUN, SUFFIX_STUN, 1, 3, 7, 12,
	//인어의 머리핀(적방어력 삭감)
	PS_DEFENSE, PREFIX_DEFENSE, 20, 50, 100, 200,
	//찬트의 펜던트(추가방어)
	PS_ARMOR, SUFFIX_ARMOR, 10, 30, 60, 100,
	//미래의 거울(회피)
	PS_EVASION, SUFFIX_EVASION, 1, 2, 4, 7,
	//피의 모래시계(화염저항)
	PS_FIRE, PREFIX_FIRE_REGIST, 5, 10, 20, 40,
	//지옥의 만화경(번개저항)
	PS_THUNDER, PREFIX_THUNDER_REGIST, 5, 10, 20, 40,
	//전능의 브로치(냉기저항)
	PS_FROST, PREFIX_FROST_REGIST, 5, 10, 20, 40,
	//생명의 보옥(생명력)
	PS_HP, SUFFIX_HP, 30, 70, 120, 200,
	//증식의 목걸이(생명회복)
	PS_HPRESTORE, PREFIX_HPRESTORE, 3, 7, 12, 20,
	//천공의 목걸이(생명흡수)
	PS_HPDRAIN, SUFFIX_HPDRAIN, 1, 2, 3, 5,
	//현자의 돌(마력)
	PS_MP, SUFFIX_MP, 40, 90, 150, 250,
	//꿈의 오카리나(마력회복)
	PS_MPRESTORE, PREFIX_MPRESTORE, 10, 20, 30, 50,
	//무한의 나침반(마력흡수)
	PS_MPDRAIN, SUFFIX_MPDRAIN, 1, 2, 3, 5,
	//기억의 오르골(경험치 추가)
	PS_EXPMOD, PREFIX_EXP, 10, 25, 40, 75,
	//난쟁이의 공(아이템 획득)
	PS_LUCK, PREFIX_LUCK, 10, 25, 40, 75,
	//탐욕의 항아리(골드 획득)
	PS_GOLDMOD, PREFIX_GOLD, 20, 50, 90, 150,
	//팬더인형(암흑저항)
	PS_DARK, PREFIX_DARK_REGIST, 5, 10, 20, 40,
	//스마일 브로치(신성저항)
	PS_HOLY, PREFIX_HOLY_REGIST, 5, 10, 20, 40,
	//토르테 악보(디버프 지속)
	PS_DEBUF, SUFFIX_DEBUF, 10, 20, 30, 50,
	//용자의 시계(버프 지속)
	PS_BUFF, PREFIX_BUFF, 50, 100, 150, 200,
	//악마의 뿔피리(리스폰 시간)
	255, SUFFIX_ENEMYREGEN, 10, 20, 35, 60,
	//아만디움 달걀(포션 회복)
	PS_POTION, PREFIX_POTION, 30, 60, 100, 150,
};
static const signed int neckRingDefaultValue_builtin[] = {
	//WEAPONDMG,
	5,
	10,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,
	60,
	65,
	70,
	75,
	80,
	85,
	90,
	95,
	100,
	105,
	110,
	115,
	120,
	125,
	130,
	135,
	140,
	145,
	150,
	155,
	160,
	165,
	170,
	175,
	180,
	185,
	190,
	195,
	200,
	205,
	210,
	215,
	220,
	225,
	230,
	235,
	240,
	245,
	250,
	//VIT,
	50,
	100,
	150,
	200,
	250,
	300,
	350,
	400,
	450,
	500,
	550,
	600,
	650,
	700,
	750,
	800,
	850,
	900,
	950,
	1000,
	1050,
	1100,
	1150,
	1200,
	1250,
	1300,
	1350,
	1400,
	1450,
	1500,
	1550,
	1600,
	1650,
	1700,
	1750,
	1800,
	1850,
	1900,
	1950,
	2000,
	2050,
	2100,
	2150,
	2200,
	2250,
	2300,
	2350,
	2400,
	2450,
	2500,
	//ARMOR,
	5,
	10,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,
	60,
	65,
	70,
	75,
	80,
	85,
	90,
	95,
	100,
	105,
	110,
	115,
	120,
	125,
	130,
	135,
	140,
	145,
	150,
	155,
	160,
	165,
	170,
	175,
	180,
	185,
	190,
	195,
	200,
	205,
	210,
	215,
	220,
	225,
	230,
	235,
	240,
	245,
	250,
	//STR,
	5,
	10,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,
	60,
	65,
	70,
	75,
	80,
	85,
	90,
	95,
	100,
	105,
	110,
	115,
	120,
	125,
	130,
	135,
	140,
	145,
	150,
	155,
	160,
	165,
	170,
	175,
	180,
	185,
	190,
	195,
	200,
	205,
	210,
	215,
	220,
	225,
	230,
	235,
	240,
	245,
	250,
	//AGI,
	5,
	10,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,
	60,
	65,
	70,
	75,
	80,
	85,
	90,
	95,
	100,
	105,
	110,
	115,
	120,
	125,
	130,
	135,
	140,
	145,
	150,
	155,
	160,
	165,
	170,
	175,
	180,
	185,
	190,
	195,
	200,
	205,
	210,
	215,
	220,
	225,
	230,
	235,
	240,
	245,
	250,
	//INT,
	5,
	10,
	15,
	20,
	25,
	30,
	35,
	40,
	45,
	50,
	55,
	60,
	65,
	70,
	75,
	80,
	85,
	90,
	95,
	100,
	105,
	110,
	115,
	120,
	125,
	130,
	135,
	140,
	145,
	150,
	155,
	160,
	165,
	170,
	175,
	180,
	185,
	190,
	195,
	200,
	205,
	210,
	215,
	220,
	225,
	230,
	235,
	240,
	245,
	250,

};
static const signed char ringOption_builtin[] = {
	//0 : 0레벨의 기본값
	//1 : 1레벨당 증가값의 100배
	//2 : 지속시간(12프레임 단위)
	//3 : 일반등급의 쿨타임(120프레임 단위)
	//4 : 고급등급의 쿨타임(120프레임 단위)
	//5 : 희귀등급의 쿨타임(120프레임 단위)
	//6 : 영웅등급의 쿨타임(120프레임 단위)
	19, 7, 0, 18, 15, 12, 9, //사신의 반지(저주 제거)
	19, 7, 0, 18, 15, 12, 9, //통찰의 반지(실명 제거)
	19, 7, 0, 18, 15, 12, 9, //시공의 반지(기절 제거)
	19, 7, 0, 18, 15, 12, 9, //해방의 반지(슬로우 제거)
	19, 7, 0, 18, 15, 12, 9, //산호석 반지(독 제거)
	45, 50, 0, 18, 15, 12, 9, //생환의 반지(체력 회복)
	45, 50, 0, 18, 15, 12, 9, //희생의 반지(마력 회복)
	8, 4, 20, 18, 15, 12, 9, //폭주의 반지(공격력 증가)
	-55, 80, 30, 18, 15, 12, 9, //골렘의 반지(방어도 증가)
	1, 3, 20, 18, 15, 12, 9, //광대의 반지(회피 증가)
	1, 3, 20, 18, 15, 12, 9, //원한의 반지(관통 증가)
	1, 3, 20, 18, 15, 12, 9, //신념의 반지(적중 증가)
	1, 3, 20, 18, 15, 12, 9, //광포의 반지(기절 증가)
	1, 3, 20, 18, 15, 12, 9, //승자의 반지(치명타 증가)
	19, 7, 30, 18, 15, 12, 9, //궁극의 반지(치명타 데미지 증가)
	-55, 80, 30, 18, 15, 12, 9, //차원의 반지(적 방어도 무시 증가)
	19, 7, 0, 18, 15, 12, 9, //영화의 반지(스킬 재사용 시간 감소)
	-24, 20, 20, 18, 15, 12, 9, //행운의 반지(경험치 획득 증가)
};
static const int optionRange_builtin[] = {
	//접두사
	10, 30, 40, 40, 80, 40,		//물리공격력 증가 : (10~40%)/(40~80%)/(80~120%)
	10, 50, 60, 60, 120, 60,		//검 공격력 증가 : (10~60%)/(60~120%)/(120~180%)
	10, 50, 60, 60, 120, 60,		//총 공격력 증가 : (10~60%)/(60~120%)/(120~180%)
	10, 50, 60, 60, 120, 60,		//부메랑 공격력 증가 : (10~60%)/(60~120%)/(120~180%)
	1, 0, 2, 0, 3, 0,					//치명타율 증가 : (1%)/(2%)/(3%)
	1, 0, 2, 0, 3, 0,					//관통력 증가 : (1%)/(2%)/(3%)
	1, 0, 2, 0, 3, 0,					//추가타격 확률 증가 : (1%)/(2%)/(3%)
	1, 4, 5, 5, 10, 10,				//힘 스탯 증가 : (1~5)/(5~10)/(10~20)
	1, 4, 5, 5, 10, 10,				//민 스탯 증가 : (1~5)/(5~10)/(10~20)
	1, 4, 5, 5, 10, 10,				//체 스탯 증가 : (1~5)/(5~10)/(10~20)
	1, 4, 5, 5, 10, 10,				//지 스탯 증가 : (1~5)/(5~10)/(10~20)
	5, 5, 10, 10, 20, 10,			//스킬공격력 증가 : (5~10)/(10~20)/(20~30)
	5, 10, 15, 15, 30, 20,			//적 방어도 감소 : (5~20)/(20~50)/(50~100)
	20, 30, 50, 50, 100, 50,		//방어력 증가 : (20~30%)/(50~100%)/(100~150%)
	1, 4, 5, 5, 10, 5,					//물리피해 감소 : (1~5%)/(5~10%)/(10~15%)
	2, 5, 7, 8, 15, 15,				//화염저항력 증가 : (2~7)/(7~15)/(15~30)
	2, 5, 7, 8, 15, 15,				//냉기저항력 증가 : (2~7)/(7~15)/(15~30)
	2, 5, 7, 8, 15, 15,				//번개저항력 증가 : (2~7)/(7~15)/(15~30)
	2, 5, 7, 8, 15, 15,				//신성저항력 증가 : (2~7)/(7~15)/(15~30)
	2, 5, 7, 8, 15, 15,				//암흑저항력 증가 : (2~7)/(7~15)/(15~30)
	5, 5, 10, 5, 15, 10,				//행운 증가 : (5~10%)/(10~15%)/(15~25%)
	5, 10, 15, 10, 25, 15,			//골드 획득 : (5~15%)/(15~25%)/(25~40%)
	5, 5, 10, 5, 15, 10,				//경험치 획득 : (5~10%)/(10~15%)/(15~25%)
	1, 1, 2, 3, 5, 5,					//HP10초당 X회복 : (1~2)/(2~5)/(5~10)
	2, 2, 4, 6, 10, 10,				//MP10초당 X회복 : (2~4)/(4~10)/(10~20)
	10, 0, 20, 0, 30, 0,				//물약류 효과 X증가(10%)/(20%)/(30%)
	20, 0, 40, 0, 60, 0,				//버프지속시간 증가(20%)/(40%)/(60%)
	0, 0, 0, 0, 0, 0,					//PREFIX_RESERVED1
	0, 0, 0, 0, 0, 0,					//PREFIX_RESERVED2
	0, 0, 0, 0, 0, 0,					//PREFIX_RESERVED3

	//접미사
	1, 14, 15, 20, 35, 35,			//물리공격력 추가 : (1~15)/(15~35)/(35~70)
	1, 19, 20, 30, 50, 50,			//검 공격력 추가 : (1~20)/(20~50)/(50~100)
	1, 19, 20, 30, 50, 50,			//총 공격력 추가 : (1~20)/(20~50)/(50~100)
	1, 19, 20, 30, 50, 50,			//부메랑 공격력 추가 : (1~20)/(20~50)/(50~100)
	5, 0, 10, 0, 20, 0,				//화염속성 공격 확률 : (5%)/(10%)/(20%)
	5, 0, 10, 0, 20, 0,				//냉기속성 공격 확률 : (5%)/(10%)/(20%)
	5, 0, 10, 0, 20, 0,				//번개속성 공격 확률 : (5%)/(10%)/(20%)
	5, 0, 10, 0, 20, 0,				//신성속성 공격 확률 : (5%)/(10%)/(20%)
	5, 0, 10, 0, 20, 0,				//암흑속성 공격 확률 : (5%)/(10%)/(20%)
	1, 0, 2, 0, 3, 0,					//적중률 증가 : (1%)/(2%)/(3%)
	1, 0, 2, 0, 3, 0,					//방어도 무시 공격확률 증가 : (1%)/(2%)/(3%)
	5, 0, 10, 0, 15, 0,				//스킬 재사용 대기시간 감소 : (5%)/(10%)/(15%)
	1, 3, 4, 4, 8, 12,					//치명타 피해 증가 : (1~4%)/(4~8%)/(8~12%)
	1, 0, 2, 0, 3, 0,					//회피율 증가 : (1%)/(2%)/(3%)
	1, 2, 3, 3, 6, 4,					//모든 스탯 증가 : (1~3)/(3~10)/(10~20)
	10, 40, 50, 50, 100, 100,		//생명력 증가 : (10~50)/(50~100)/(100~200)
	10, 40, 50, 50, 100, 100,		//마나 증가 : (10~50)/(50~100)/(100~200)
	1, 0, 2, 0, 3, 0,					//체력흡수 : (1%)/(2~3%)/(3~5%)
	1, 0, 2, 0, 3, 0,					//마나흡수 : (1%)/(2~3%)/(3~5%)
	1, 4, 5, 5, 10, 10,				//모든 저항력 증가 : (1~3)/(3~10)/(10~20)
	5, 10, 15, 25, 40, 60,			//방어력 추가 : (5~15)/(15~40)/(40~100)
	5, 5, 10, 10, 20, 10,			//행운 증가 : (5~10%)/(10~20%)/(20~40%)
	5, 10, 15, 10, 25, 15,			//골드 획득 : (10~20%)/(20~30%)/(30~50%)
	5, 5, 10, 10, 20, 10,			//경험치 획득 : (5~10%)/(10~20%)/(20~40%)
	10, 0, 20, 0, 30, 0,				//요구치 감소 : (10%)/(20%)/(30%)
	10, 0, 20, 0, 30, 0,				//상태이상 지속시간 감소 : (10%)/(20%)/(30%)
	1, 1, 2, 2, 4, 3,					//기절공격 확률 증가 : (1~2%)/(2~4%)/(4~7%)
	0, 0, 0, 0, 1, 0,					//스킬레벨 증가 : (0)/(0)/(1)
	0, 0, 0, 0, 0, 0,					//SUFFIX_RESERVED1
	0, 0, 0, 0, 0, 0,					//SUFFIX_RESERVED2
	0, 0, 0, 0, 0, 0,					//SUFFIX_RESERVED3
};
static const signed char optionValue_builtin[] = {
	3,	//물리공격력 증가 : (10~40%)/(40~80%)/(80~120%)
	3,	//검 공격력 증가 : (10~60%)/(60~120%)/(120~180%)
	3,	//총 공격력 증가 : (10~60%)/(60~120%)/(120~180%)
	3,	//부메랑 공격력 증가 : (10~60%)/(60~120%)/(120~180%)
	2,	//치명타율 증가 : (1%)/(2%)/(3%)
	2,	//관통력 증가 : (1%)/(2%)/(3%)
	2,	//추가타격 확률 증가 : (1%)/(2%)/(3%)
	1,	//힘 스탯 증가 : (1~5)/(5~10)/(10~20)
	1,	//민 스탯 증가 : (1~5)/(5~10)/(10~20)
	1,	//체 스탯 증가 : (1~5)/(5~10)/(10~20)
	1,	//지 스탯 증가 : (1~5)/(5~10)/(10~20)
	2,	//스킬공격력 증가 : (5~10)/(10~20)/(20~30)
	2,	//적 방어도 감소 : (5~20)/(20~50)/(50~100)
	3,	//방어력 증가 : (20~30%)/(50~100%)/(100~150%)
	3,	//물리피해 감소 : (1~5%)/(5~10%)/(10~15%)
	1,	//화염저항력 증가 : (2~7)/(7~15)/(15~30)
	1,	//냉기저항력 증가 : (2~7)/(7~15)/(15~30)
	1,	//번개저항력 증가 : (2~7)/(7~15)/(15~30)
	1,	//신성저항력 증가 : (2~7)/(7~15)/(15~30)
	1,	//암흑저항력 증가 : (2~7)/(7~15)/(15~30)
	3,	//행운 증가 : (5~10%)/(10~15%)/(15~25%)
	3,	//골드 획득 : (5~15%)/(15~25%)/(25~40%)
	3,	//경험치 획득 : (5~10%)/(10~15%)/(15~25%)
	2,	//HP10초당 X회복 : (1~2)/(2~5)/(5~10)
	2,	//MP10초당 X회복 : (2~4)/(4~10)/(10~20)
	2,	//물약류 효과 X증가(10%)/(20%)/(30%)
	2,	//버프지속시간 증가(20%)/(40%)/(60%)
	0,	//PREFIX_RESERVED1
	0,	//PREFIX_RESERVED2
	0,	//PREFIX_RESERVED3

	3, //물리공격력 추가 : (1~15)/(15~35)/(35~70)
	3, //검 공격력 추가 : (1~20)/(20~50)/(50~100)
	3, //총 공격력 추가 : (1~20)/(20~50)/(50~100)
	3, //부메랑 공격력 추가 : (1~20)/(20~50)/(50~100)
	1, //화염속성 공격 확률 : (5%)/(10%)/(20%)
	1, //냉기속성 공격 확률 : (5%)/(10%)/(20%)
	1, //번개속성 공격 확률 : (5%)/(10%)/(20%)
	1, //신성속성 공격 확률 : (5%)/(10%)/(20%)
	1, //암흑속성 공격 확률 : (5%)/(10%)/(20%)
	2, //적중률 증가 : (1%)/(2%)/(3%)
	2, //방어도 무시 공격확률 증가 : (1%)/(2%)/(3%)
	1, //스킬 재사용 대기시간 감소 : (5%)/(10%)/(15%)
	2, //치명타 피해 증가 : (1~4%)/(4~8%)/(8~12%)
	2, //회피율 증가 : (1%)/(2%)/(3%)
	3, //모든 스탯 증가 : (1~3)/(3~10)/(10~20)
	1, //생명력 증가 : (10~50)/(50~100)/(100~200)
	1, //마나 증가 : (10~50)/(50~100)/(100~200)
	3, //체력흡수 : (1%)/(2~3%)/(3~5%)
	3, //마나흡수 : (1%)/(2~3%)/(3~5%)
	2, //모든 저항력 증가 : (1~3)/(3~10)/(10~20)
	3, //방어력 추가 : (5~15)/(15~40)/(40~100)
	3, //행운 증가 : (5~10%)/(10~20%)/(20~40%)
	3, //골드 획득 : (10~20%)/(20~30%)/(30~50%)
	3, //경험치 획득 : (5~10%)/(10~20%)/(20~40%)
	1, //요구치 감소 : (10%)/(20%)/(30%)
	2, //상태이상 지속시간 감소 : (10%)/(20%)/(30%)
	2,	//기절공격 확률 증가 : (1~2%)/(2~4%)/(4~7%)
	3,	//스킬레벨 증가 : (0)/(0)/(1)
	0,	//SUFFIX_RESERVED1
	0,	//SUFFIX_RESERVED2
	0,	//SUFFIX_RESERVED3
};
static const unsigned char setItem_builtin[] = {
	//0 : 세트 번호
	//1 : 옵션 첫번째
	//2 : 옵션 두번째

	//1//연습용몽둥이
	SET_BEGINNER, PREFIX_SWORD_DMG, PREFIX_STR,	//메인
	SET_TRAINING, PREFIX_SWORD_DMG, SUFFIX_HOLY_ATTACK,	//서브
	//2//롱소드
	SET_BEGINNER, PREFIX_SWORD_DMG, PREFIX_EXTRA,	//메인
	SET_ROYAL, PREFIX_SKILLDMG, PREFIX_AGI,	//서브
	//3//처형자의검
	SET_BEGINNER, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_SKULL, PREFIX_DEFENSE, PREFIX_VIT,	//서브
	//4//파멸의 참마도
	SET_BEGINNER, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_SKULL, PREFIX_DEFENSE, PREFIX_VIT,	//서브
	//5//추적자의 검
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_STR,	//메인
	SET_CHASER, PREFIX_SWORD_DMG, PREFIX_VIT,	//서브
	//6//격노의 양날 검
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_STR,	//메인
	SET_CHASER, PREFIX_SWORD_DMG, PREFIX_VIT,	//서브
	//7//수호자의 검
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_AGI,	//메인
	SET_GUARDIAN, SUFFIX_STUN, SUFFIX_HOLY_ATTACK,	//서브
	//8//왕가의 수호자
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_AGI,	//메인
	SET_GUARDIAN, SUFFIX_STUN, SUFFIX_HOLY_ATTACK,	//서브
	//9//나찰의 검
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DEVIL, SUFFIX_IGNORE, PREFIX_SWORD_DMG,//서브
	//10//소울 크래셔
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DEVIL, SUFFIX_IGNORE, PREFIX_SWORD_DMG,//서브
	//11//플레임 소드
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DEVIL, SUFFIX_IGNORE, PREFIX_SWORD_DMG,//서브
	//12//아이스 소드
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DEVIL, SUFFIX_IGNORE, PREFIX_SWORD_DMG,//서브
	//13//썬더 소드
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DEVIL, SUFFIX_IGNORE, PREFIX_SWORD_DMG,//서브
	//14//어스 소드
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DEVIL, SUFFIX_IGNORE, PREFIX_SWORD_DMG,//서브
	//15//레바테인
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DEVIL, SUFFIX_IGNORE, PREFIX_SWORD_DMG,//서브
	//16//스톰브링거
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DEVIL, SUFFIX_IGNORE, PREFIX_SWORD_DMG,//서브
	//17//칼라드볼그
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DEVIL, SUFFIX_IGNORE, PREFIX_SWORD_DMG,//서브
	//18//발뭉
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DEVIL, SUFFIX_IGNORE, PREFIX_SWORD_DMG,//서브
	//19//흐룬팅
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DEVIL, SUFFIX_IGNORE, PREFIX_SWORD_DMG,//서브
	//20//거인의 칼
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DEVIL, SUFFIX_IGNORE, PREFIX_SWORD_DMG,//서브
	//21//미스틸테인
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DEVIL, SUFFIX_IGNORE, PREFIX_SWORD_DMG,//서브
	//22//엑스칼리버
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DEVIL, SUFFIX_IGNORE, PREFIX_SWORD_DMG,//서브
	//23//홀리소드
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DEVIL, SUFFIX_IGNORE, PREFIX_SWORD_DMG,//서브
	//24//다크소드
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DEVIL, SUFFIX_IGNORE, PREFIX_SWORD_DMG,//서브
	//25//레오소드
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DEVIL, SUFFIX_IGNORE, PREFIX_SWORD_DMG,//서브
	//26//사신의 낫
	SET_KINGDOM, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DEVIL, SUFFIX_IGNORE, PREFIX_SWORD_DMG,//서브
	//27//드래곤 클로우
	SET_SPACE, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DRAGON, SUFFIX_HOLY_ATTACK, PREFIX_AGI,	//서브
	//28//황룡의 어금니
	SET_SPACE, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DRAGON, SUFFIX_HOLY_ATTACK, PREFIX_AGI,	//서브
	//29//신룡마강검
	SET_SPACE, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DRAGON, SUFFIX_HOLY_ATTACK, PREFIX_AGI,	//서브
	//30//드래곤 슬레이어
	SET_SPACE, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DRAGON, SUFFIX_HOLY_ATTACK, PREFIX_AGI,	//서브
	//31//얼티밋소드
	SET_SPACE, PREFIX_SWORD_DMG, PREFIX_CRITICAL,	//메인
	SET_DRAGON, SUFFIX_HOLY_ATTACK, PREFIX_AGI,	//서브
	//32//차원의 검
	SET_SPACE, PREFIX_SWORD_DMG, PREFIX_AGI,	//메인
	SET_ANCIENT, PREFIX_SWORD_DMG, PREFIX_AGI,	//서브
	//33//천공의 검
	SET_SPACE, PREFIX_SWORD_DMG, PREFIX_AGI,	//메인
	SET_ANCIENT, PREFIX_SWORD_DMG, PREFIX_AGI,	//서브
	//34//스타더스트
	SET_SPACE, PREFIX_SWORD_DMG, PREFIX_AGI,	//메인
	SET_ANCIENT, PREFIX_SWORD_DMG, PREFIX_AGI,	//서브
	//35//패왕의 검
	SET_SPACE, PREFIX_SWORD_DMG, PREFIX_AGI,	//메인
	SET_ANCIENT, PREFIX_SWORD_DMG, PREFIX_AGI,	//서브
	//발화식 총
	SET_HAWK, PREFIX_GUN_DMG, PREFIX_INT,	//메인
	SET_GUNMAN, PREFIX_GUN_DMG, PREFIX_STR,	//서브
	//리볼버 파이슨
	SET_HAWK, PREFIX_GUN_DMG, PREFIX_PIERCE,	//메인
	SET_OUTLAW, PREFIX_GUN_DMG, PREFIX_AGI,	//서브
	//45구경 오토건
	SET_HAWK, PREFIX_GUN_DMG, SUFFIX_CRITICAL,	//메인
	SET_SMILE, SUFFIX_STUN, SUFFIX_HOLY_ATTACK,	//서브
	//고져스 건
	SET_MAGICGUN, PREFIX_GUN_DMG, PREFIX_INT,	//메인
	SET_ELITE, PREFIX_SKILLDMG, PREFIX_STR,	//서브
	//회천마도총
	SET_MAGICGUN, PREFIX_GUN_DMG, PREFIX_PIERCE,	//메인
	SET_IMMOTAL, PREFIX_GUN_DMG, PREFIX_PIERCE,	//서브
	//태양의 총
	SET_MAGICGUN, PREFIX_GUN_DMG, SUFFIX_CRITICAL,	//메인
	SET_NOBLE, PREFIX_INT, PREFIX_STR,	//서브
	//헬파이어 건
	SET_SUN, PREFIX_GUN_DMG, PREFIX_PIERCE,	//메인
	SET_HELL, PREFIX_GUN_DMG, PREFIX_DEFENSE,	//서브
	//크로스 파이어
	SET_SUN, PREFIX_GUN_DMG, SUFFIX_CRITICAL,	//메인
	SET_DEADMAN, SUFFIX_STUN, SUFFIX_HOLY_ATTACK,	//서브
	//사냥용 부메랑
	SET_WANTED, PREFIX_BOOMERANG_DMG, PREFIX_AGI,	//메인
	SET_ROOTLESS, PREFIX_BOOMERANG_DMG, PREFIX_AGI,	//서브
	//슬라이서
	SET_WANTED, PREFIX_BOOMERANG_DMG, SUFFIX_IGNORE,	//메인
	SET_VAGABOND, PREFIX_DEFENSE, PREFIX_AGI,	//서브
	//강철 부메랑
	SET_WANTED, PREFIX_BOOMERANG_DMG, PREFIX_DEFENSE,	//메인
	SET_MONARCH, PREFIX_VIT, PREFIX_STR,	//서브
	//트라이 엣지
	SET_SOUL, PREFIX_BOOMERANG_DMG, PREFIX_AGI,	//메인
	SET_GUILLOTINE, PREFIX_BOOMERANG_DMG, PREFIX_AGI,	//서브
	//라이트닝엣지
	SET_SOUL, PREFIX_BOOMERANG_DMG, SUFFIX_IGNORE,	//메인
	SET_ELEMENTAL, PREFIX_VIT, PREFIX_DEFENSE,	//서브
	//소울 체이서
	SET_SOUL, PREFIX_BOOMERANG_DMG, PREFIX_DEFENSE,	//메인
	SET_JUDEGMENT, PREFIX_BOOMERANG_DMG, PREFIX_STR,	//서브
	//그리폰 윙
	SET_MOBIUS, PREFIX_BOOMERANG_DMG, SUFFIX_IGNORE,	//메인
	SET_WING, SUFFIX_STUN, SUFFIX_HOLY_ATTACK,	//서브
	//로커스트 헌트
	SET_MOBIUS, PREFIX_BOOMERANG_DMG, PREFIX_DEFENSE,	//메인
	SET_LOCUST, PREFIX_BOOMERANG_DMG, PREFIX_VIT,	//서브
	//1//헤드 가드
	SET_BEGINNER, SUFFIX_HP, SUFFIX_EVASION,	//메인
	SET_MERCENARY, SUFFIX_ARMOR, SUFFIX_DEBUF,	//서브
	//6//바시넷
	SET_BEGINNER, SUFFIX_HP, SUFFIX_HIT,	//메인
	SET_BRONZE, PREFIX_CRITICAL, SUFFIX_HIT,	//서브
	//9//솔저헬름
	SET_BEGINNER, SUFFIX_HP, SUFFIX_CRITICAL,	//메인
	SET_ROYAL, SUFFIX_CRITICAL, PREFIX_DEFENSE,	//서브
	//12//검투사의 투구
	SET_KINGDOM, SUFFIX_HP, SUFFIX_EVASION,	//메인
	SET_ARTHUR, PREFIX_CRITICAL, SUFFIX_HIT,	//서브
	//15//스파이크 헤드
	SET_KINGDOM, SUFFIX_HP, SUFFIX_HIT,	//메인
	SET_MONARCH, PREFIX_PIERCE, PREFIX_THUNDER_REGIST,	//서브
	//18//그랜드헬름
	SET_KINGDOM, SUFFIX_HP, SUFFIX_CRITICAL,	//메인
	SET_GRAND, SUFFIX_IGNORE, SUFFIX_EVASION,	//서브
	//21//고대의투구
	SET_SPACE, SUFFIX_HP, SUFFIX_HIT,	//메인
	SET_ANCIENT, PREFIX_ARMOR, PREFIX_HOLY_REGIST,	//서브
	//24//용자의 투구
	SET_SPACE, SUFFIX_HP, SUFFIX_CRITICAL,	//메인
	SET_LOST, PREFIX_FIRE_REGIST, SUFFIX_DEBUF,	//서브
	//산책용 보닛
	SET_HAWK, PREFIX_HPRESTORE, SUFFIX_EVASION,	//메인
	SET_PICNIC, SUFFIX_CRITICAL, SUFFIX_HIT,	//서브
	//카우보이 모자
	SET_HAWK, PREFIX_HPRESTORE, PREFIX_INT,	//메인
	SET_OUTLAW, PREFIX_DEFENSE, PREFIX_DARK_REGIST,	//서브
	//레인저 햇
	SET_HAWK, PREFIX_HPRESTORE, SUFFIX_HIT,	//메인
	SET_SMILE, PREFIX_VIT, SUFFIX_DEBUF,	//서브
	//서클렛
	SET_MAGICGUN, PREFIX_HPRESTORE, SUFFIX_EVASION,	//메인
	SET_CHALLENGER, SUFFIX_DEBUF, PREFIX_VIT,	//서브
	//올드 윌로우
	SET_MAGICGUN, PREFIX_HPRESTORE, PREFIX_INT,	//메인
	SET_COSTUME, PREFIX_PIERCE, PREFIX_THUNDER_REGIST,	//서브
	//스나이퍼 고글
	SET_MAGICGUN, PREFIX_HPRESTORE, SUFFIX_HIT,	//메인
	SET_ELITE, PREFIX_FROST_REGIST, PREFIX_HOLY_REGIST,	//서브
	//혼란의 모자
	SET_SUN, PREFIX_HPRESTORE, PREFIX_INT,	//메인
	SET_CHAOS, PREFIX_PIERCE, PREFIX_THUNDER_REGIST,	//서브
	//프리에스테스
	SET_SUN, PREFIX_HPRESTORE, SUFFIX_HIT,	//메인
	SET_DEADMAN, PREFIX_DARK_REGIST, SUFFIX_DEBUF,	//서브
	//공작깃털 모자
	SET_WANTED, PREFIX_INT, PREFIX_VIT,	//메인
	SET_VAGABOND, PREFIX_PIERCE, PREFIX_HOLY_REGIST,	//서브
	//귀족의 머리띠
	SET_WANTED, PREFIX_INT, SUFFIX_DEBUF,	//메인
	SET_COSTUME, PREFIX_DEFENSE, PREFIX_BUFF,	//서브
	//거상의 모자
	SET_WANTED, PREFIX_INT, SUFFIX_ARMOR,	//메인
	SET_CARAVAN, PREFIX_CRITICAL, SUFFIX_HIT,	//서브
	//사냥꾼 모자
	SET_SOUL, PREFIX_INT, PREFIX_VIT,	//메인
	SET_GUILLOTINE, PREFIX_ARMOR, SUFFIX_IGNORE,	//서브
	//투우사의 모자
	SET_SOUL, PREFIX_INT, SUFFIX_DEBUF,	//메인
	SET_BULL, SUFFIX_CRITICAL, SUFFIX_HIT,	//서브
	//해적의 모자
	SET_SOUL, PREFIX_INT, SUFFIX_ARMOR,	//메인
	SET_TREASURE, PREFIX_PIERCE, PREFIX_HOLY_REGIST,	//서브
	//에이스 캡
	SET_MOBIUS, PREFIX_INT, SUFFIX_DEBUF,	//메인
	SET_STRANGER, PREFIX_DARK_REGIST, PREFIX_ARMOR,	//서브
	//드래곤 레어캡
	SET_MOBIUS, PREFIX_INT, SUFFIX_ARMOR,	//메인
	SET_DRAGON, PREFIX_CRITICAL, SUFFIX_HIT,	//서브
	//1//헌터 튜닉
	SET_BEGINNER, SUFFIX_DEBUF, PREFIX_VIT,	//메인
	SET_HUNTER, PREFIX_BUFF, PREFIX_INT,	//서브
	//6//미늘 갑옷
	SET_BEGINNER, SUFFIX_DEBUF, PREFIX_PIERCE,	//메인
	SET_MERCENARY, PREFIX_PIERCE, PREFIX_INT,	//서브
	//9//하프 플레이트
	SET_BEGINNER, SUFFIX_DEBUF, PREFIX_EXTRA,	//메인
	SET_ROYAL, PREFIX_BUFF, SUFFIX_HP,	//서브
	//12//스컬 메일
	SET_KINGDOM, SUFFIX_DEBUF, PREFIX_VIT,	//메인
	SET_SKULL, PREFIX_ARMOR, PREFIX_STR,	//서브
	//15//황금세공 갑옷
	SET_KINGDOM, SUFFIX_DEBUF, PREFIX_PIERCE,	//메인
	SET_SMITH, PREFIX_BUFF, PREFIX_INT,	//서브
	//18//미스릴 아머
	SET_KINGDOM, SUFFIX_DEBUF, PREFIX_EXTRA,	//메인
	SET_GRAND, PREFIX_BUFF, SUFFIX_HP,	//서브
	//21//고대의 갑옷
	SET_SPACE, SUFFIX_DEBUF, PREFIX_PIERCE,	//메인
	SET_ANCIENT, PREFIX_BUFF, SUFFIX_HP,	//서브
	//24//용비늘 갑옷
	SET_SPACE, SUFFIX_DEBUF, PREFIX_EXTRA,	//메인
	SET_DRAGON, PREFIX_VIT, SUFFIX_HP,	//서브
	//카우보이 조끼
	SET_HAWK, SUFFIX_HP, PREFIX_PIERCE,	//메인
	SET_OUTLAW, PREFIX_BUFF, PREFIX_STR,	//서브
	//실크 조끼
	SET_HAWK, SUFFIX_HP, PREFIX_CRITICAL,	//메인
	SET_MAPLE, SUFFIX_HPDRAIN, PREFIX_ABSORB,	//서브
	//방랑자의 조끼
	SET_HAWK, SUFFIX_HP, PREFIX_DEFENSE,	//메인
	SET_CHASER, PREFIX_BUFF, SUFFIX_HP,	//서브
	//도적의 조끼
	SET_MAGICGUN, SUFFIX_HP, PREFIX_PIERCE,	//메인
	SET_THIEF, PREFIX_BUFF, SUFFIX_HP,	//서브
	//벨벳 셔츠
	SET_MAGICGUN, SUFFIX_HP, PREFIX_CRITICAL,	//메인
	SET_ELITE, PREFIX_DEFENSE, PREFIX_BUFF,	//서브
	//귀족의 조끼
	SET_MAGICGUN, SUFFIX_HP, PREFIX_DEFENSE,	//메인
	SET_NOBLE, PREFIX_DEFENSE, PREFIX_BUFF,	//서브
	//진홍빛 셔츠
	SET_SUN, SUFFIX_HP, PREFIX_CRITICAL,	//메인
	SET_VICTORY, PREFIX_DEFENSE, PREFIX_BUFF,	//서브
	//신관의 로브
	SET_SUN, SUFFIX_HP, PREFIX_DEFENSE,	//메인
	SET_DEADMAN, PREFIX_CRITICAL, PREFIX_INT,	//서브
	//수수한 코트
	SET_WANTED, SUFFIX_STUN, SUFFIX_DEBUF,	//메인
	SET_GENTLE, PREFIX_DEFENSE, PREFIX_BUFF,	//서브
	//패딩 아머
	SET_WANTED, SUFFIX_STUN, PREFIX_DEFENSE,	//메인
	SET_VAGABOND, PREFIX_BUFF, SUFFIX_HP,	//서브
	//털가죽 코트
	SET_WANTED, SUFFIX_STUN, SUFFIX_IGNORE,	//메인
	SET_SMILE, SUFFIX_DELAY, PREFIX_INT,	//서브
	//큐어보일
	SET_SOUL, SUFFIX_STUN, SUFFIX_DEBUF,	//메인
	SET_GUILLOTINE, PREFIX_BUFF, PREFIX_STR,	//서브
	//귀족의 코트
	SET_SOUL, SUFFIX_STUN, PREFIX_DEFENSE,	//메인
	SET_NOBLE, PREFIX_BUFF, SUFFIX_HP,	//서브
	//극지의 코트
	SET_SOUL, SUFFIX_STUN, SUFFIX_IGNORE,	//메인
	SET_STRANGER, PREFIX_BUFF, SUFFIX_HP,	//서브
	//윙 코트
	SET_MOBIUS, SUFFIX_STUN, PREFIX_DEFENSE,	//메인
	SET_WING, SUFFIX_EVASION, PREFIX_INT,	//서브
	//바이스 코트
	SET_MOBIUS, SUFFIX_STUN, SUFFIX_IGNORE,	//메인
	SET_LOCUST, PREFIX_DEFENSE, PREFIX_BUFF,	//서브
	//1//핸드 가드
	SET_BEGINNER, SUFFIX_IGNORE, PREFIX_PIERCE,	//메인
	SET_TRAINING, SUFFIX_THUNDER_ATTACK, PREFIX_CRITICAL,	//서브
	//6//청동 장갑
	SET_BEGINNER, SUFFIX_IGNORE, PREFIX_DEFENSE,	//메인
	SET_BRONZE, PREFIX_EXTRA, PREFIX_DARK_REGIST,	//서브
	//9//체인 건틀렛
	SET_BEGINNER, SUFFIX_IGNORE, SUFFIX_HIT,	//메인
	SET_ARTHUR, PREFIX_DEFENSE, SUFFIX_FROST_ATTACK,	//서브
	//12//나이트 글로브
	SET_KINGDOM, SUFFIX_IGNORE, PREFIX_PIERCE,	//메인
	SET_ROYAL, PREFIX_CRITICAL, SUFFIX_FIRE_ATTACK,	//서브
	//15//비스트 핸드
	SET_KINGDOM, SUFFIX_IGNORE, PREFIX_DEFENSE,	//메인
	SET_BULL, PREFIX_EXTRA, SUFFIX_THUNDER_ATTACK,	//서브
	//18//라이징 건틀렛
	SET_KINGDOM, SUFFIX_IGNORE, SUFFIX_HIT,	//메인
	SET_STRANGER, PREFIX_CRITICAL, SUFFIX_FROST_ATTACK,	//서브
	//21//광전사의 장갑
	SET_SPACE, SUFFIX_IGNORE, PREFIX_DEFENSE,	//메인
	SET_LOCUST, SUFFIX_ARMOR, SUFFIX_THUNDER_ATTACK,	//서브
	//24//드래곤 핸드
	SET_SPACE, SUFFIX_IGNORE, SUFFIX_HIT,	//메인
	SET_DRAGON, PREFIX_DEFENSE, PREFIX_HOLY_REGIST,	//서브
	//사제의 묵주
	SET_HAWK, SUFFIX_STUN, PREFIX_AGI,	//메인
	SET_MAPLE, PREFIX_BUFF, PREFIX_FROST_REGIST,	//서브
	//여행자의 팔찌
	SET_HAWK, SUFFIX_STUN, SUFFIX_HIT,	//메인
	SET_ROOTLESS, PREFIX_DEFENSE, PREFIX_THUNDER_REGIST,	//서브
	//백금 브레스렛
	SET_HAWK, SUFFIX_STUN, PREFIX_PIERCE,	//메인
	SET_DREAM, SUFFIX_ARMOR, PREFIX_DARK_REGIST,	//서브
	//전사의 암렛
	SET_MAGICGUN, SUFFIX_STUN, PREFIX_AGI,	//메인
	SET_CHALLENGER, PREFIX_BUFF, SUFFIX_HIT,	//서브
	//에메랄드 팔찌
	SET_MAGICGUN, SUFFIX_STUN, SUFFIX_HIT,	//메인
	SET_COSTUME, PREFIX_EXTRA, SUFFIX_ARMOR,	//서브
	//이블 암렛
	SET_MAGICGUN, SUFFIX_STUN, PREFIX_PIERCE,	//메인
	SET_HELL, SUFFIX_ARMOR, SUFFIX_FROST_ATTACK,	//서브
	//위엄의 팔찌
	SET_SUN, SUFFIX_STUN, SUFFIX_HIT,	//메인
	SET_VICTORY, SUFFIX_FIRE_ATTACK, PREFIX_BUFF,	//서브
	//영웅의 팔찌
	SET_SUN, SUFFIX_STUN, PREFIX_PIERCE,	//메인
	SET_LOST, PREFIX_BUFF, SUFFIX_HIT,	//서브
	//여행자의 장갑
	SET_WANTED, PREFIX_SKILLDMG, SUFFIX_FIRE_ATTACK,	//메인
	SET_GUNMAN, PREFIX_CRITICAL, SUFFIX_HOLY_ATTACK,	//서브
	//이중매듭 장갑
	SET_WANTED, PREFIX_SKILLDMG, PREFIX_AGI,	//메인
	SET_SMILE, PREFIX_BUFF, SUFFIX_HIT,	//서브
	//소매치기 장갑
	SET_WANTED, PREFIX_SKILLDMG, PREFIX_BUFF,	//메인
	SET_THIEF, PREFIX_CRITICAL, SUFFIX_FROST_ATTACK,	//서브
	//실크 글로브
	SET_SOUL, PREFIX_SKILLDMG, SUFFIX_FIRE_ATTACK,	//메인
	SET_NOBLE, SUFFIX_HPDRAIN, PREFIX_ABSORB,	//서브
	//세공사의 장갑
	SET_SOUL, PREFIX_SKILLDMG, PREFIX_AGI,	//메인
	SET_SMITH, SUFFIX_HIT, SUFFIX_DARK_ATTACK,	//서브
	//마법문양 장갑
	SET_SOUL, PREFIX_SKILLDMG, PREFIX_BUFF,	//메인
	SET_IMMOTAL, PREFIX_EXTRA, SUFFIX_DARK_ATTACK,	//서브
	//심판의 손
	SET_MOBIUS, PREFIX_SKILLDMG, PREFIX_AGI,	//메인
	SET_JUDEGMENT, PREFIX_PIERCE, SUFFIX_FIRE_ATTACK,	//서브
	//성자의 장갑
	SET_MOBIUS, PREFIX_SKILLDMG, PREFIX_BUFF,	//메인
	SET_DEADMAN, SUFFIX_THUNDER_ATTACK, SUFFIX_HIT,	//서브
	//1//밴딩 킬트
	SET_BEGINNER, PREFIX_ARMOR, SUFFIX_HIT,	//메인
	SET_HUNTER, SUFFIX_EVASION, PREFIX_FIRE_REGIST,	//서브
	//6//체인 킬트
	SET_BEGINNER, PREFIX_ARMOR, PREFIX_VIT,	//메인
	SET_ARTHUR, SUFFIX_HPDRAIN, PREFIX_FIRE_REGIST,	//서브
	//9//나이트 킬트
	SET_BEGINNER, PREFIX_ARMOR, PREFIX_SKILLDMG,	//메인
	SET_ROYAL, SUFFIX_IGNORE, PREFIX_FROST_REGIST,	//서브
	//12//스컬 킬트
	SET_KINGDOM, PREFIX_ARMOR, SUFFIX_HIT,	//메인
	SET_SKULL, SUFFIX_CRITICAL, PREFIX_HOLY_REGIST,	//서브
	//15//수령의 바지
	SET_KINGDOM, PREFIX_ARMOR, PREFIX_VIT,	//메인
	SET_MONARCH, SUFFIX_IGNORE, SUFFIX_EVASION,	//서브
	//18//미스릴 킬트
	SET_KINGDOM, PREFIX_ARMOR, PREFIX_SKILLDMG,	//메인
	SET_GRAND, PREFIX_PIERCE, PREFIX_THUNDER_REGIST,	//서브
	//21//에인션트 킬트
	SET_SPACE, PREFIX_ARMOR, PREFIX_VIT,	//메인
	SET_ANCIENT, SUFFIX_EVASION, PREFIX_FROST_REGIST,	//서브
	//24//용수염 킬트
	SET_SPACE, PREFIX_ARMOR, PREFIX_SKILLDMG,	//메인
	SET_DRAGON, SUFFIX_CRITICAL, PREFIX_FROST_REGIST,	//서브
	//양단 스커트
	SET_HAWK, PREFIX_BUFF, SUFFIX_HIT,	//메인
	SET_PICNIC, SUFFIX_IGNORE, SUFFIX_EVASION,	//서브
	//빈티지 스커트
	SET_HAWK, PREFIX_BUFF, PREFIX_ARMOR,	//메인
	SET_OUTLAW, SUFFIX_HP, PREFIX_FIRE_REGIST,	//서브
	//단풍염색 치마
	SET_HAWK, PREFIX_BUFF, PREFIX_INT,	//메인
	SET_MAPLE, SUFFIX_CRITICAL, SUFFIX_EVASION,	//서브
	//벨벳 스커트
	SET_MAGICGUN, PREFIX_BUFF, SUFFIX_HIT,	//메인
	SET_ELITE, SUFFIX_IGNORE, SUFFIX_EVASION,	//서브
	//폭풍의 스커트
	SET_MAGICGUN, PREFIX_BUFF, PREFIX_ARMOR,	//메인
	SET_ELEMENTAL, SUFFIX_IGNORE, SUFFIX_EVASION,	//서브
	//금실의 치마
	SET_MAGICGUN, PREFIX_BUFF, PREFIX_INT,	//메인
	SET_COSTUME, SUFFIX_IGNORE, SUFFIX_EVASION,	//서브
	//영광의 치마
	SET_SUN, PREFIX_BUFF, PREFIX_ARMOR,	//메인
	SET_VICTORY, SUFFIX_IGNORE, SUFFIX_EVASION,	//서브
	//사제의 스커트
	SET_SUN, PREFIX_BUFF, PREFIX_INT,	//메인
	SET_DEADMAN, SUFFIX_DELAY, PREFIX_BUFF,	//서브
	//승마용 바지
	SET_WANTED, PREFIX_HPRESTORE, PREFIX_BUFF,	//메인
	SET_GENTLE, SUFFIX_IGNORE, SUFFIX_EVASION,	//서브
	//카프스킨 팬츠
	SET_WANTED, PREFIX_HPRESTORE, PREFIX_BUFF,	//메인
	SET_VAGABOND, SUFFIX_CRITICAL, PREFIX_FIRE_REGIST,	//서브
	//망령의 팬츠
	SET_WANTED, PREFIX_HPRESTORE, PREFIX_AGI,	//메인
	SET_DEVIL, PREFIX_SKILLDMG, PREFIX_STR,	//서브
	//흑단의 바지
	SET_SOUL, PREFIX_HPRESTORE, PREFIX_BUFF,	//메인
	SET_GUILLOTINE, SUFFIX_HP, PREFIX_FIRE_REGIST,	//서브
	//세일러 팬츠
	SET_SOUL, PREFIX_HPRESTORE, PREFIX_BUFF,	//메인
	SET_TREASURE, SUFFIX_CRITICAL, PREFIX_FIRE_REGIST,	//서브
	//데저트 팬츠
	SET_SOUL, PREFIX_HPRESTORE, PREFIX_AGI,	//메인
	SET_STRANGER, SUFFIX_HIT, PREFIX_THUNDER_REGIST,	//서브
	//카오틱 팬츠
	SET_MOBIUS, PREFIX_HPRESTORE, PREFIX_BUFF,	//메인
	SET_CHAOS, SUFFIX_DELAY, SUFFIX_EVASION,	//서브
	//가디안 팬츠
	SET_MOBIUS, PREFIX_HPRESTORE, PREFIX_AGI,	//메인
	SET_POET, SUFFIX_IGNORE, SUFFIX_EVASION,	//서브
	//1//코퍼 그리브
	SET_BEGINNER, SUFFIX_ARMOR, PREFIX_EXTRA,	//메인
	SET_BRONZE, SUFFIX_IGNORE, PREFIX_FROST_REGIST,	//서브
	//6//밴디트 그리브
	SET_BEGINNER, SUFFIX_ARMOR, SUFFIX_EVASION,	//메인
	SET_THIEF, SUFFIX_HP, SUFFIX_DEBUF,	//서브
	//9//체인 그리브
	SET_BEGINNER, SUFFIX_ARMOR, PREFIX_DEFENSE,	//메인
	SET_ARTHUR, SUFFIX_ARMOR, PREFIX_ABSORB,	//서브
	//12//프로즌그리브
	SET_KINGDOM, SUFFIX_ARMOR, PREFIX_EXTRA,	//메인
	SET_ELEMENTAL, PREFIX_FIRE_REGIST, PREFIX_DARK_REGIST,	//서브
	//15//플레이트 부츠
	SET_KINGDOM, SUFFIX_ARMOR, SUFFIX_EVASION,	//메인
	SET_SMITH, SUFFIX_HP, SUFFIX_DEBUF,	//서브
	//18//빅풋그리브
	SET_KINGDOM, SUFFIX_ARMOR, PREFIX_DEFENSE,	//메인
	SET_BULL, SUFFIX_DEBUF, PREFIX_DARK_REGIST,	//서브
	//21//마검사의 신발
	SET_SPACE, SUFFIX_ARMOR, SUFFIX_EVASION,	//메인
	SET_IMMOTAL, SUFFIX_HPDRAIN, PREFIX_ABSORB,	//서브
	//24//드래곤 그리브
	SET_SPACE, SUFFIX_ARMOR, PREFIX_DEFENSE,	//메인
	SET_DRAGON, SUFFIX_HPDRAIN, PREFIX_ABSORB,	//서브
	//웨스턴 슈즈
	SET_HAWK, PREFIX_HPRESTORE, PREFIX_EXTRA,	//메인
	SET_OUTLAW, PREFIX_ARMOR, PREFIX_HPRESTORE,	//서브
	//스웨이드 슈즈
	SET_HAWK, PREFIX_HPRESTORE, SUFFIX_CRITICAL,	//메인
	SET_GENTLE, SUFFIX_CRITICAL, PREFIX_FROST_REGIST,	//서브
	//라이딩 슈즈
	SET_HAWK, PREFIX_HPRESTORE, PREFIX_ARMOR,	//메인
	SET_SMILE, SUFFIX_HPDRAIN, PREFIX_HOLY_REGIST,	//서브
	//칠흑의 슈즈
	SET_MAGICGUN, PREFIX_HPRESTORE, PREFIX_EXTRA,	//메인
	SET_GUILLOTINE, PREFIX_HPRESTORE, SUFFIX_DELAY,	//서브
	//귀부인의 신발
	SET_MAGICGUN, PREFIX_HPRESTORE, SUFFIX_CRITICAL,	//메인
	SET_COSTUME, SUFFIX_HP, SUFFIX_DEBUF,	//서브
	//리치 슈즈
	SET_MAGICGUN, PREFIX_HPRESTORE, PREFIX_ARMOR,	//메인
	SET_NOBLE, SUFFIX_HP, SUFFIX_DEBUF,	//서브
	//프리즘 슈즈
	SET_SUN, PREFIX_HPRESTORE, SUFFIX_CRITICAL,	//메인
	SET_CHAOS, PREFIX_ARMOR, PREFIX_ABSORB,	//서브
	//베이그란트
	SET_SUN, PREFIX_HPRESTORE, PREFIX_ARMOR,	//메인
	SET_POET, SUFFIX_HP, SUFFIX_DEBUF,	//서브
	//스니커즈
	SET_WANTED, SUFFIX_DELAY, SUFFIX_HP,	//메인
	SET_PICNIC, SUFFIX_HP, SUFFIX_DEBUF,	//서브
	//스캐빈저 부츠
	SET_WANTED, SUFFIX_DELAY, SUFFIX_ARMOR,	//메인
	SET_CHASER, SUFFIX_HPDRAIN, PREFIX_ABSORB,	//서브
	//천둥가죽 신발
	SET_WANTED, SUFFIX_DELAY, PREFIX_ABSORB,	//메인
	SET_VAGABOND, PREFIX_CRITICAL, SUFFIX_DELAY,	//서브
	//가드너 부츠
	SET_SOUL, SUFFIX_DELAY, SUFFIX_HP,	//메인
	SET_GUARDIAN, SUFFIX_HPDRAIN, PREFIX_DARK_REGIST,	//서브
	//세일러 부츠
	SET_SOUL, SUFFIX_DELAY, SUFFIX_ARMOR,	//메인
	SET_TREASURE, SUFFIX_HPDRAIN, PREFIX_THUNDER_REGIST,	//서브
	//저승의 신발
	SET_SOUL, SUFFIX_DELAY, PREFIX_ABSORB,	//메인
	SET_HELL, SUFFIX_DEBUF, SUFFIX_HP,	//서브
	//엘레멘탈 부츠
	SET_MOBIUS, SUFFIX_DELAY, SUFFIX_ARMOR,	//메인
	SET_ELEMENTAL, SUFFIX_ARMOR, SUFFIX_DELAY,	//서브
	//에어워커
	SET_MOBIUS, SUFFIX_DELAY, PREFIX_ABSORB,	//메인
	SET_WING, SUFFIX_HPDRAIN, PREFIX_DARK_REGIST,	//서브
	//명예의 팬던트
	SET_MAGICGUN, SUFFIX_HPDRAIN, SUFFIX_WEAPON_DMG,	//메인
	SET_STRANGER, SUFFIX_FIRE_ATTACK, PREFIX_AGI,	//서브
	//연옥의 브로치
	SET_SOUL, SUFFIX_HPDRAIN, SUFFIX_HP,	//메인
	SET_ELITE, PREFIX_HPRESTORE, SUFFIX_FROST_ATTACK,	//서브
	//찰나의 팔찌
	SET_SOUL, SUFFIX_HPDRAIN, PREFIX_ABSORB,	//메인
	SET_ARTHUR, SUFFIX_FIRE_ATTACK, PREFIX_INT,	//서브
	//황금 바늘
	SET_SOUL, SUFFIX_HPDRAIN, SUFFIX_WEAPON_DMG,	//메인
	SET_SMITH, SUFFIX_WEAPON_DMG, SUFFIX_EVASION,	//서브
	//파열의 팔찌
	SET_SOUL, SUFFIX_HPDRAIN, PREFIX_ABSORB,	//메인
	SET_SKULL, SUFFIX_EVASION, SUFFIX_DARK_ATTACK,	//서브
	//메피스토 피리
	SET_SOUL, SUFFIX_HPDRAIN, SUFFIX_WEAPON_DMG,	//메인
	SET_POET, SUFFIX_WEAPON_DMG, SUFFIX_FROST_ATTACK,	//서브
	//사멸의 하프
	SET_MOBIUS, SUFFIX_HPDRAIN, PREFIX_ABSORB,	//메인
	SET_CHASER, SUFFIX_THUNDER_ATTACK, PREFIX_AGI,	//서브
	//인어의 머리핀
	SET_MOBIUS, SUFFIX_HPDRAIN, SUFFIX_WEAPON_DMG,	//메인
	SET_TREASURE, SUFFIX_EVASION, SUFFIX_HP,	//서브
	//찬트의 펜던트
	SET_KINGDOM, SUFFIX_ALLREGIST, SUFFIX_FROST_ATTACK,	//메인
	SET_CHAOS, SUFFIX_THUNDER_ATTACK, PREFIX_BUFF,	//서브
	//미래의 거울
	SET_KINGDOM, SUFFIX_ALLREGIST, SUFFIX_WEAPON_DMG,	//메인
	SET_GRAND, PREFIX_BUFF, PREFIX_ABSORB,	//서브
	//피의 모래시계
	SET_KINGDOM, SUFFIX_ALLREGIST, PREFIX_ABSORB,	//메인
	SET_LOCUST, PREFIX_CRITICAL, PREFIX_HPRESTORE,	//서브
	//지옥의 만화경
	SET_SUN, SUFFIX_HPDRAIN, SUFFIX_WEAPON_DMG,	//메인
	SET_BULL, PREFIX_FROST_REGIST, SUFFIX_DARK_ATTACK,	//서브
	//전능의 브로치
	SET_SPACE, SUFFIX_ALLREGIST, SUFFIX_WEAPON_DMG,	//메인
	SET_DRAGON, SUFFIX_FIRE_ATTACK, PREFIX_DEFENSE,	//서브
	//생명의 보옥
	SET_KINGDOM, SUFFIX_ALLREGIST, SUFFIX_WEAPON_DMG,	//메인
	SET_DEADMAN, SUFFIX_IGNORE, PREFIX_HOLY_REGIST,	//서브
	//증식의 목걸이
	SET_KINGDOM, SUFFIX_ALLREGIST, PREFIX_ABSORB,	//메인
	SET_GUARDIAN, PREFIX_EXTRA, SUFFIX_CRITICAL,	//서브
	//천공의 목걸이
	SET_SPACE, SUFFIX_ALLREGIST, SUFFIX_FROST_ATTACK,	//메인
	SET_WING, SUFFIX_IGNORE, PREFIX_HPRESTORE,	//서브
	//현자의 돌
	SET_MAGICGUN, SUFFIX_HPDRAIN, PREFIX_HPRESTORE,	//메인
	SET_IMMOTAL, SUFFIX_FIRE_ATTACK, SUFFIX_WEAPON_DMG,	//서브
	//꿈의 오카리나
	SET_MAGICGUN, SUFFIX_HPDRAIN, SUFFIX_WEAPON_DMG,	//메인
	SET_DREAM, SUFFIX_WEAPON_DMG, SUFFIX_FROST_ATTACK,	//서브
	//무한의 나침반
	SET_MAGICGUN, SUFFIX_HPDRAIN, SUFFIX_WEAPON_DMG,	//메인
	SET_ANCIENT, SUFFIX_FIRE_ATTACK, PREFIX_INT,	//서브
	//기억의 오르골
	SET_SUN, SUFFIX_HPDRAIN, SUFFIX_WEAPON_DMG,	//메인
	SET_VICTORY, SUFFIX_WEAPON_DMG, SUFFIX_DARK_ATTACK,	//서브
	//난쟁이의 공
	SET_SUN, SUFFIX_HPDRAIN, SUFFIX_WEAPON_DMG,	//메인
	SET_THIEF, SUFFIX_WEAPON_DMG, SUFFIX_DARK_ATTACK,	//서브
	//탐욕의 항아리
	SET_MOBIUS, SUFFIX_HPDRAIN, PREFIX_ABSORB,	//메인
	SET_CARAVAN, PREFIX_PIERCE, SUFFIX_HP,	//서브
	//팬더인형
	SET_SUN, SUFFIX_HPDRAIN, SUFFIX_WEAPON_DMG,	//메인
	SET_PICNIC, SUFFIX_WEAPON_DMG, SUFFIX_DARK_ATTACK,	//서브
	//스마일 브로치
	SET_MAGICGUN, SUFFIX_HPDRAIN, PREFIX_HPRESTORE,	//메인
	SET_SMILE, SUFFIX_IGNORE, PREFIX_ABSORB,	//서브
	//토르테 악보
	SET_SPACE, SUFFIX_ALLREGIST, PREFIX_ABSORB,	//메인
	SET_DEVIL, PREFIX_EXTRA, PREFIX_HPRESTORE,	//서브
	//용자의 시계
	SET_SPACE, SUFFIX_ALLREGIST, SUFFIX_WEAPON_DMG,	//메인
	SET_LOST, SUFFIX_CRITICAL, SUFFIX_THUNDER_ATTACK,	//서브
	//악마의 뿔피리
	SET_MOBIUS, SUFFIX_HPDRAIN, SUFFIX_WEAPON_DMG,	//메인
	SET_HELL, PREFIX_HPRESTORE, SUFFIX_THUNDER_ATTACK,	//서브
	//아만디움 달걀
	SET_SPACE, SUFFIX_ALLREGIST, PREFIX_ABSORB,	//메인
	SET_ELEMENTAL, SUFFIX_FIRE_ATTACK, SUFFIX_STUN,	//서브
	//사신의 반지
	SET_KINGDOM, SUFFIX_ARMOR, PREFIX_FIRE_REGIST,	//메인
	SET_DEVIL, SUFFIX_HIT, PREFIX_FIRE_REGIST,	//서브
	//통찰의 반지
	SET_SOUL, SUFFIX_HPDRAIN, SUFFIX_EVASION,	//메인
	SET_STRANGER, PREFIX_PIERCE, PREFIX_HPRESTORE,	//서브
	//시공의 반지
	SET_MAGICGUN, SUFFIX_HPDRAIN, PREFIX_ABSORB,	//메인
	SET_WING, PREFIX_EXTRA, SUFFIX_THUNDER_ATTACK,	//서브
	//해방의 반지
	SET_MAGICGUN, SUFFIX_HPDRAIN, PREFIX_ABSORB,	//메인
	SET_MONARCH, PREFIX_EXTRA, PREFIX_HPRESTORE,	//서브
	//산호석 반지
	SET_SOUL, SUFFIX_HPDRAIN, PREFIX_HPRESTORE,	//메인
	SET_TREASURE, SUFFIX_HIT, PREFIX_HPRESTORE,	//서브
	//생환의 반지
	SET_KINGDOM, SUFFIX_ARMOR, PREFIX_EXTRA,	//메인
	SET_GUILLOTINE, SUFFIX_FROST_ATTACK, PREFIX_HPRESTORE,	//서브
	//희생의 반지
	SET_MAGICGUN, SUFFIX_HPDRAIN, SUFFIX_HP,	//메인
	SET_GUARDIAN, SUFFIX_IGNORE, PREFIX_FIRE_REGIST,	//서브
	//폭주의 반지
	SET_SOUL, SUFFIX_HPDRAIN, PREFIX_HPRESTORE,	//메인
	SET_LOCUST, SUFFIX_WEAPON_DMG, SUFFIX_HOLY_ATTACK,	//서브
	//골렘의 반지
	SET_KINGDOM, SUFFIX_ARMOR, PREFIX_HPRESTORE,	//메인
	SET_ARTHUR, PREFIX_PIERCE, PREFIX_HPRESTORE,	//서브
	//광대의 반지
	SET_SPACE, SUFFIX_ARMOR, PREFIX_EXTRA,	//메인
	SET_CHAOS, PREFIX_EXTRA, PREFIX_STR,	//서브
	//원한의 반지
	SET_SPACE, SUFFIX_ARMOR, PREFIX_HPRESTORE,	//메인
	SET_SKULL, PREFIX_PIERCE, PREFIX_HPRESTORE,	//서브
	//신념의 반지
	SET_SUN, SUFFIX_HPDRAIN, PREFIX_ABSORB,	//메인
	SET_DEADMAN, PREFIX_EXTRA, SUFFIX_EVASION,	//서브
	//광포의 반지
	SET_MOBIUS, SUFFIX_HPDRAIN, PREFIX_HPRESTORE,	//메인
	SET_HELL, PREFIX_EXTRA, PREFIX_HPRESTORE,	//서브
	//승자의 반지
	SET_MOBIUS, SUFFIX_HPDRAIN, PREFIX_HPRESTORE,	//메인
	SET_VICTORY, PREFIX_EXTRA, PREFIX_HPRESTORE,	//서브
	//궁극의 반지
	SET_MOBIUS, SUFFIX_HPDRAIN, PREFIX_HPRESTORE,	//메인
	SET_DRAGON, PREFIX_EXTRA, SUFFIX_IGNORE,	//서브
	//차원의 반지
	SET_SUN, SUFFIX_HPDRAIN, PREFIX_ABSORB,	//메인
	SET_ANCIENT, SUFFIX_STUN, PREFIX_HPRESTORE,	//서브
	//영화의 반지
	SET_SUN, SUFFIX_HPDRAIN, PREFIX_ABSORB,	//메인
	SET_NOBLE, PREFIX_EXTRA, PREFIX_HPRESTORE,	//서브
	//행운의 반지
	SET_SPACE, SUFFIX_ARMOR, PREFIX_HPRESTORE,	//메인
	SET_CARAVAN, SUFFIX_HOLY_ATTACK, SUFFIX_CRITICAL,	//서브
};
static const int setOption_builtin[] = {
	//0 : 첫번째 세트효과가 나올 세트 수
	//1 : 세트효과 첫번째 옵션 종류
	//2 : 세트효과 첫번째 옵션 값
	//3 : 두번째 세트효과가 나올 세트 수
	//4 : 세트효과 두번째 옵션 종류
	//5 : 세트효과 두번째 옵션 값
	//6 : 세번째 세트효과가 나올 세트 수
	//7 : 세트효과 세번째 옵션 종류
	//8 : 세트효과 세번째 옵션 값
	//9 : 세트아이템 총 갯수(= 네번째 세트효과가 나올 세트 수)
	//10 : 세트효과 네번째 옵션 종류
	//11 : 세트효과 네번째 옵션 값

	//SET_BEGINNER
	2, SUFFIX_STUN, 4,
	3, SUFFIX_HPDRAIN, 1,
	4, PREFIX_HPRESTORE, 3,
	6, SUFFIX_STAT, 3,
	6, 255, 0,
	6, 255, 0,

	//SET_KINGDOM
	2, PREFIX_HPRESTORE, 5,
	3, SUFFIX_HP, 50,
	4, SUFFIX_STUN, 7,
	5, SUFFIX_HPDRAIN, 3,
	6, SUFFIX_ARMOR, 80,
	8, SUFFIX_STAT, 10,

	//SET_SPACE
	2, PREFIX_HPRESTORE, 10,
	3, SUFFIX_HP, 100,
	4, SUFFIX_STUN, 10,
	5, SUFFIX_HPDRAIN, 5,
	6, SUFFIX_DELAY, 5,
	8, SUFFIX_STAT, 20,

	//SET_OUTLAW
	2, PREFIX_SKILLDMG, 10,
	3, SUFFIX_DELAY, 5,
	4, SUFFIX_STUN, 4,
	6, SUFFIX_SKILL, 1,
	6, 255, 0,
	6, 255, 0,

	//SET_MAGICGUN
	2, PREFIX_INT, 10,
	3, SUFFIX_STUN, 10,
	4, PREFIX_SKILLDMG, 20,
	5, SUFFIX_DELAY, 10,
	6, SUFFIX_STUN, 7,
	8, SUFFIX_SKILL, 2,

	//SET_SUN
	2, PREFIX_INT, 20,
	3, SUFFIX_HP, 150,
	4, PREFIX_SKILLDMG, 30,
	5, SUFFIX_DELAY, 15,
	6, SUFFIX_STUN, 10,
	8, SUFFIX_SKILL, 3,

	//SET_WANTED
	2, PREFIX_PIERCE, 1,
	3, PREFIX_CRITICAL, 1,
	4, SUFFIX_CRITICAL, 4,
	6, SUFFIX_WEAPON_DMG, 10,
	6, 255, 0,
	6, 255, 0,

	//SET_SOUL
	2, SUFFIX_HIT, 2,
	3, PREFIX_EXTRA, 2,
	4, PREFIX_PIERCE, 2,
	5, PREFIX_CRITICAL, 2,
	6, SUFFIX_CRITICAL, 8,
	8, SUFFIX_WEAPON_DMG, 20,

	//SET_MOBIUS
	2, SUFFIX_HIT, 3,
	3, PREFIX_EXTRA, 3,
	4, PREFIX_PIERCE, 3,
	5, PREFIX_CRITICAL, 3,
	6, SUFFIX_CRITICAL, 12,
	8, SUFFIX_WEAPON_DMG, 30,

	//SET_TRAINING
	2, SUFFIX_ARMOR, 80,
	2, PREFIX_ARMOR, 100,
	2, 255, 0,
	2, 255, 0,
	2, 255, 0,
	2, 255, 0,

	//SET_GUNMAN
	2, PREFIX_INT, 5,
	2, PREFIX_SKILLDMG, 10,
	2, 255, 0,
	2, 255, 0,
	2, 255, 0,
	2, 255, 0,

	//SET_ROOTLESS
	2, PREFIX_CRITICAL, 1,
	2, SUFFIX_CRITICAL, 4,
	2, 255, 0,
	2, 255, 0,
	2, 255, 0,
	2, 255, 0,

	//SET_CHALLENGER
	2, PREFIX_ABSORB, 7,
	2, SUFFIX_ALLREGIST, 10,
	2, 255, 0,
	2, 255, 0,
	2, 255, 0,
	2, 255, 0,

	//SET_HUNTER
	2, PREFIX_CRITICAL, 1,
	2, SUFFIX_CRITICAL, 4,
	2, 255, 0,
	2, 255, 0,
	2, 255, 0,
	2, 255, 0,

	//SET_MERCENARY
	2, SUFFIX_STUN, 3,
	2, PREFIX_SKILLDMG, 7,
	2, 255, 0,
	2, 255, 0,
	2, 255, 0,
	2, 255, 0,

	//SET_JUDEGMENT
	2, SUFFIX_ARMOR, 80,
	2, PREFIX_ARMOR, 100,
	2, 255, 0,
	2, 255, 0,
	2, 255, 0,
	2, 255, 0,

	//SET_CARAVAN
	2, PREFIX_FROST_REGIST, 7,
	3, SUFFIX_DEBUF, 10,
	3, PREFIX_GOLD, 3,
	3, 255, 0,
	3, 255, 0,
	3, 255, 0,

	//SET_MAPLE
	2, PREFIX_INT, 5,
	3, SUFFIX_HP, 100,
	3, PREFIX_LUCK, 10,
	3, 255, 0,
	3, 255, 0,
	3, 255, 0,

	//SET_LOST
	2, PREFIX_ABSORB, 13,
	3, SUFFIX_ARMOR, 80,
	3, PREFIX_ARMOR, 100,
	3, 255, 0,
	3, 255, 0,
	3, 255, 0,

	//SET_DREAM
	2, PREFIX_POTION, 10,
	3, PREFIX_HPRESTORE, 5,
	3, SUFFIX_HPDRAIN, 1,
	3, 255, 0,
	3, 255, 0,
	3, 255, 0,

	//SET_GENTLE
	2, SUFFIX_DELAY, 5,
	3, PREFIX_SKILLDMG, 10,
	3, SUFFIX_SKILL, 1,
	3, 255, 0,
	3, 255, 0,
	3, 255, 0,

	//SET_BRONZE
	2, PREFIX_POTION, 10,
	3, PREFIX_HPRESTORE, 1,
	3, SUFFIX_HP, 100,
	3, 255, 0,
	3, 255, 0,
	3, 255, 0,

	//SET_POET
	2, PREFIX_VIT, 15,
	3, SUFFIX_HP, 100,
	3, PREFIX_GOLD, 2,
	3, 255, 0,
	3, 255, 0,
	3, 255, 0,

	//SET_GUARDIAN
	2, PREFIX_ABSORB, 8,
	3, SUFFIX_ALLREGIST, 8,
	4, SUFFIX_ARMOR, 40,
	4, PREFIX_ARMOR, 100,
	4, 255, 0,
	4, 255, 0,

	//SET_IMMOTAL
	2, PREFIX_SKILLDMG, 15,
	3, SUFFIX_DELAY, 10,
	4, SUFFIX_STUN, 7,
	4, SUFFIX_SKILL, 2,
	4, 255, 0,
	4, 255, 0,

	//SET_MONARCH
	2, PREFIX_SKILLDMG, 15,
	3, SUFFIX_DELAY, 10,
	4, SUFFIX_STUN, 7,
	4, SUFFIX_SKILL, 2,
	4, 255, 0,
	4, 255, 0,

	//SET_CHASER
	2, SUFFIX_HIT, 2,
	3, PREFIX_EXTRA, 2,
	4, PREFIX_PIERCE, 2,
	4, SUFFIX_WEAPON_DMG, 20,
	4, 255, 0,
	4, 255, 0,

	//SET_SMITH
	2, PREFIX_EXTRA, 2,
	3, PREFIX_PIERCE, 2,
	4, PREFIX_CRITICAL, 2,
	4, SUFFIX_CRITICAL, 8,
	4, 255, 0,
	4, 255, 0,

	//SET_THIEF
	2, PREFIX_THUNDER_REGIST, 10,
	3, SUFFIX_STUN, 7,
	4, SUFFIX_HPDRAIN, 1,
	4, PREFIX_LUCK, 20,
	4, 255, 0,
	4, 255, 0,

	//SET_PICNIC
	2, PREFIX_AGI, 5,
	3, SUFFIX_STUN, 4,
	4, PREFIX_BUFF, 20,
	4, SUFFIX_STAT, 3,
	4, 255, 0,
	4, 255, 0,

	//SET_GRAND
	2, PREFIX_FROST_REGIST, 15,
	3, PREFIX_HOLY_REGIST, 15,
	4, SUFFIX_DEBUF, 20,
	4, PREFIX_GOLD, 1,
	4, 255, 0,
	4, 255, 0,

	//SET_BULL
	2, PREFIX_CRITICAL, 8,
	3, SUFFIX_IGNORE, 8,
	4, PREFIX_DEFENSE, 40,
	4, SUFFIX_WEAPON_DMG, 20,
	4, 255, 0,
	4, 255, 0,

	//SET_DEVIL
	2, PREFIX_ABSORB, 5,
	3, SUFFIX_ALLREGIST, 3,
	4, SUFFIX_ARMOR, 15,
	4, PREFIX_ARMOR, 30,
	4, 255, 0,
	4, 255, 0,

	//SET_ROYAL
	2, SUFFIX_HP, 200,
	3, PREFIX_ABSORB, 5,
	4, SUFFIX_ALLREGIST, 3,
	5, SUFFIX_ARMOR, 15,
	5, PREFIX_ARMOR, 30,
	5, 255, 0,

	//SET_OUTLAW
	2, SUFFIX_HP, 100,
	3, PREFIX_SKILLDMG, 10,
	4, SUFFIX_DELAY, 5,
	5, SUFFIX_STUN, 4,
	5, SUFFIX_SKILL, 1,
	5, 255, 0,

	//SET_SKULL
	2, SUFFIX_DEBUF, 20,
	3, PREFIX_POTION, 20,
	4, PREFIX_BUFF, 30,
	5, SUFFIX_STUN, 3,
	5, SUFFIX_HPDRAIN, 3,
	5, 255, 0,

	//SET_TREASURE
	2, PREFIX_INT, 10,
	3, PREFIX_AGI, 10,
	4, SUFFIX_DEBUF, 20,
	5, PREFIX_BUFF, 40,
	5, PREFIX_GOLD, 5,
	5, 255, 0,

	//SET_HELL
	2, SUFFIX_HIT, 2,
	3, PREFIX_CRITICAL, 2,
	4, SUFFIX_CRITICAL, 8,
	5, SUFFIX_WEAPON_DMG, 20,
	5, PREFIX_LUCK, 20,
	5, 255, 0,

	//SET_LOCUST
	2, SUFFIX_HP, 200,
	3, SUFFIX_STUN, 10,
	4, SUFFIX_DELAY, 15,
	5, PREFIX_SKILLDMG, 30,
	5, SUFFIX_SKILL, 3,
	5, 255, 0,

	//SET_VAGABOND
	2, SUFFIX_HP, 50,
	3, SUFFIX_ALLREGIST, 3,
	4, SUFFIX_ARMOR, 15,
	5, PREFIX_ARMOR, 30,
	5, SUFFIX_STAT, 3,
	5, 255, 0,

	//SET_ELEMENTAL
	2, SUFFIX_DEBUF, 20,
	3, PREFIX_BUFF, 40,
	4, PREFIX_POTION, 20,
	5, PREFIX_HPRESTORE, 5,
	5, SUFFIX_HPDRAIN, 3,
	5, 255, 0,

	//SET_ELITE
	2, PREFIX_EXTRA, 2,
	3, PREFIX_PIERCE, 2,
	4, PREFIX_CRITICAL, 2,
	5, SUFFIX_CRITICAL, 8,
	5, SUFFIX_WEAPON_DMG, 20,
	5, 255, 0,

	//SET_CHAOS
	2, PREFIX_ABSORB, 10,
	3, SUFFIX_HP, 150,
	4, PREFIX_HPRESTORE, 10,
	5, PREFIX_PIERCE, 3,
	5, SUFFIX_STAT, 20,
	5, 255, 0,

	//SET_COSTUME
	2, PREFIX_HPRESTORE, 5,
	3, PREFIX_ABSORB, 12,
	4, SUFFIX_STUN, 7,
	5, PREFIX_PIERCE, 5,
	5, SUFFIX_HPDRAIN, 3,
	5, 255, 0,

	//SET_WING
	2, SUFFIX_HP, 100,
	3, PREFIX_ABSORB, 10,
	4, SUFFIX_ALLREGIST, 10,
	5, SUFFIX_ARMOR, 40,
	5, PREFIX_ARMOR, 100,
	5, 255, 0,

	//SET_NOBLE
	2, SUFFIX_HP, 100,
	3, SUFFIX_DELAY, 10,
	4, SUFFIX_STUN, 7,
	5, PREFIX_SKILLDMG, 20,
	5, SUFFIX_SKILL, 2,
	5, 255, 0,

	//SET_SMILE
	2, SUFFIX_EVASION, 1,
	3, SUFFIX_ALLREGIST, 3,
	4, SUFFIX_ARMOR, 15,
	5, PREFIX_ARMOR, 30,
	5, PREFIX_GOLD, 3,
	5, 255, 0,

	//SET_VICTORY
	2, PREFIX_VIT, 20,
	3, PREFIX_INT, 20,
	4, SUFFIX_HPDRAIN, 3,
	5, SUFFIX_HP, 150,
	5, PREFIX_GOLD, 3,
	5, 255, 0,

	//SET_STRANGER
	2, PREFIX_POTION, 20,
	3, SUFFIX_HP, 90,
	4, PREFIX_HPRESTORE, 5,
	5, SUFFIX_STUN, 7,
	6, PREFIX_ABSORB, 7,
	6, SUFFIX_HPDRAIN, 3,

	//SET_GUILLOTINE
	2, PREFIX_AGI, 10,
	3, SUFFIX_HIT, 2,
	4, PREFIX_EXTRA, 2,
	5, PREFIX_PIERCE, 2,
	6, PREFIX_CRITICAL, 2,
	6, SUFFIX_CRITICAL, 8,

	//SET_ANCIENT
	2, SUFFIX_HIT, 3,
	3, PREFIX_EXTRA, 3,
	4, PREFIX_PIERCE, 3,
	5, PREFIX_CRITICAL, 3,
	6, SUFFIX_CRITICAL, 12,
	6, SUFFIX_WEAPON_DMG, 30,

	//SET_ARTHUR
	2, PREFIX_INT, 10,
	3, PREFIX_HPRESTORE, 4,
	4, SUFFIX_DELAY, 10,
	5, SUFFIX_STUN, 7,
	6, PREFIX_SKILLDMG, 20,
	6, SUFFIX_SKILL, 2,

	//SET_DRAGON
	2, PREFIX_STR, 15,
	3, PREFIX_PIERCE, 3,
	4, SUFFIX_ALLREGIST, 20,
	5, SUFFIX_WEAPON_DMG, 30,
	6, PREFIX_SKILLDMG, 30,
	6, SUFFIX_STAT, 20,

	//SET_DEADMAN
	2, SUFFIX_HP, 150,
	3, PREFIX_HPRESTORE, 6,
	4, PREFIX_ARMOR, 150,
	5, SUFFIX_ARMOR, 100,
	6, SUFFIX_ALLREGIST, 20,
	6, SUFFIX_STAT, 20,

	//SET_RA1		
	2, SUFFIX_HPDRAIN, 15,
	3, PREFIX_POTION, 250,
	4, PREFIX_ARMOR, 30,
	5, PREFIX_WEAPON_DMG, 100,
	6, SUFFIX_SKILL, 3,
	8, SUFFIX_EVASION, 50,

	//SET_RA2					
	2, SUFFIX_HP, 100,
	3, PREFIX_HPRESTORE, 60,
	4, SUFFIX_ARMOR, 250,
	5, SUFFIX_IGNORE, 40,
	6, PREFIX_SKILLDMG, 150,
	8, PREFIX_ABSORB, 50,

	//SET_RB1					
	2, SUFFIX_DELAY, 30,
	3, SUFFIX_HPDRAIN, 30,
	4, SUFFIX_CRITICAL, 60,
	5, SUFFIX_EVASION, 40,
	6, PREFIX_WEAPON_DMG, 150,
	8, SUFFIX_SKILL, 5,

	//SET_RB2					
	2, SUFFIX_DEBUF, 30,
	3, SUFFIX_HIT, 30,
	4, PREFIX_CRITICAL, 30,
	5, PREFIX_ABSORB, 40,
	6, SUFFIX_IGNORE, 45,
	8, PREFIX_SKILLDMG, 250,

	//SET_RC1					
	2, PREFIX_DEFENSE, 250,
	3, PREFIX_BUFF, 150,
	4, SUFFIX_WEAPON_DMG, 150,
	5, SUFFIX_SKILL, 2,
	6, SUFFIX_EVASION, 45,
	8, PREFIX_WEAPON_DMG, 250,

	//SET_RC2					
	2, SUFFIX_STUN, 30,
	3, PREFIX_EXTRA, 30,
	4, PREFIX_PIERCE, 30,
	5, PREFIX_SKILLDMG, 100,
	6, PREFIX_ABSORB, 45,
	8, SUFFIX_IGNORE, 50,

	//SET_RD1					
	2, SUFFIX_MINUSHP, 250,
	3, SUFFIX_HPDECREASE, 250,
	4, SUFFIX_MINUSSKILLDMG, 250,
	5, SUFFIX_MINUSDRAIN, 45,
	6, PREFIX_LUCK, 250,
	8, PREFIX_LUCK, 250,

	//SET_RD2					
	2, SUFFIX_HPDECREASE, 150,
	3, SUFFIX_MINUSHP, 150,
	4, SUFFIX_MINUSDRAIN, 30,
	5, SUFFIX_MINUSSKILLDMG, 150,
	6, PREFIX_GOLD, 250,
	8, PREFIX_GOLD, 250,

	//SET_DA1					
	2, SUFFIX_HPDRAIN, 15,
	3, PREFIX_POTION, 250,
	4, PREFIX_ARMOR, 30,
	5, SUFFIX_WEAPON_DMG, 100,
	6, SUFFIX_SKILL, 3,
	8, SUFFIX_EVASION, 50,

	//SET_DA2					
	2, PREFIX_MPRESTORE, 60,
	3, SUFFIX_HP, 100,
	4, SUFFIX_ARMOR, 250,
	5, SUFFIX_IGNORE, 40,
	6, PREFIX_SKILLDMG, 45,
	8, PREFIX_ABSORB, 50,

	//SET_DB1					
	2, SUFFIX_DELAY, 30,
	3, SUFFIX_HPDRAIN, 30,
	4, SUFFIX_CRITICAL, 60,
	5, SUFFIX_EVASION, 40,
	6, PREFIX_WEAPON_DMG, 150,
	8, SUFFIX_SKILL, 5,

	//SET_DB2					
	2, SUFFIX_DEBUF, 30,
	3, SUFFIX_HIT, 30,
	4, PREFIX_CRITICAL, 30,
	5, PREFIX_ABSORB, 40,
	6, SUFFIX_IGNORE, 45,
	8, PREFIX_SKILLDMG, 250,

	//SET_DC1					
	2, PREFIX_DEFENSE, 250,
	3, PREFIX_BUFF, 150,
	4, SUFFIX_WEAPON_DMG, 150,
	5, SUFFIX_SKILL, 2,
	6, SUFFIX_EVASION, 45,
	8, PREFIX_WEAPON_DMG, 250,

	//SET_DC2					
	2, SUFFIX_STUN, 30,
	3, PREFIX_EXTRA, 30,
	4, PREFIX_PIERCE, 30,
	5, PREFIX_SKILLDMG, 100,
	6, PREFIX_ABSORB, 45,
	8, SUFFIX_IGNORE, 50,

	//SET_DD1					
	2, SUFFIX_MINUSHP, 250,
	3, SUFFIX_HPDECREASE, 250,
	4, SUFFIX_MINUSSKILLDMG, 250,
	5, SUFFIX_MINUSDRAIN, 45,
	6, PREFIX_LUCK, 250,
	8, PREFIX_LUCK, 250,

	//SET_DD2					
	2, SUFFIX_HPDECREASE, 150,
	3, SUFFIX_MINUSHP, 150,
	4, SUFFIX_MINUSDRAIN, 30,
	5, SUFFIX_MINUSSKILLDMG, 150,
	6, PREFIX_GOLD, 250,
	8, PREFIX_GOLD, 250,

	//SET_MA1					
	2, SUFFIX_HPDRAIN, 15,
	3, PREFIX_POTION, 250,
	4, PREFIX_ARMOR, 30,
	5, PREFIX_WEAPON_DMG, 100,
	6, SUFFIX_SKILL, 3,
	8, SUFFIX_EVASION, 50,

	//SET_MA2					
	2, SUFFIX_HP, 200,
	3, PREFIX_HPRESTORE, 60,
	4, SUFFIX_ARMOR, 250,
	5, SUFFIX_IGNORE, 40,
	6, PREFIX_SKILLDMG, 45,
	8, PREFIX_ABSORB, 50,

	//SET_MB1					
	2, SUFFIX_DELAY, 30,
	3, SUFFIX_HPDRAIN, 30,
	4, SUFFIX_CRITICAL, 60,
	5, SUFFIX_EVASION, 40,
	6, PREFIX_WEAPON_DMG, 150,
	8, SUFFIX_SKILL, 5,

	//SET_MB2					
	2, SUFFIX_DEBUF, 30,
	3, SUFFIX_HIT, 30,
	4, PREFIX_CRITICAL, 30,
	5, PREFIX_ABSORB, 40,
	6, SUFFIX_IGNORE, 45,
	8, PREFIX_SKILLDMG, 250,

	//SET_MC1					
	2, PREFIX_DEFENSE, 250,
	3, PREFIX_BUFF, 150,
	4, SUFFIX_WEAPON_DMG, 150,
	5, SUFFIX_SKILL, 2,
	6, SUFFIX_EVASION, 45,
	8, PREFIX_WEAPON_DMG, 250,

	//SET_MC2					
	2, SUFFIX_STUN, 30,
	3, PREFIX_EXTRA, 30,
	4, PREFIX_PIERCE, 30,
	5, PREFIX_SKILLDMG, 100,
	6, PREFIX_ABSORB, 45,
	8, SUFFIX_IGNORE, 50,

	//SET_MD1					
	2, SUFFIX_MINUSHP, 250,
	3, SUFFIX_HPDECREASE, 250,
	4, SUFFIX_MINUSSKILLDMG, 250,
	5, SUFFIX_MINUSDRAIN, 45,
	6, PREFIX_LUCK, 250,
	8, PREFIX_LUCK, 250,

	//SET_MD2					
	2, SUFFIX_HPDECREASE, 150,
	3, SUFFIX_MINUSHP, 150,
	4, SUFFIX_MINUSDRAIN, 30,
	5, SUFFIX_MINUSSKILLDMG, 150,
	6, PREFIX_GOLD, 250,
	8, PREFIX_GOLD, 250,
};
static const unsigned int legendItem_builtin[] = {
	//--------- 검 ---------//
	//스타더스트
	PREFIX_SWORD_DMG, 200, 50,
	PREFIX_WEAPON_DMG, 200, 50,
	//SUFFIX_MPDRAIN, 3, 3,
	SUFFIX_IGNORE, 5, 5,
	SUFFIX_HPDRAIN, 10, 5,
	PREFIX_STR, 50, 30,
	PREFIX_DEFENSE, 50, 30,//적의 방어도 감소

	//신룡강마검
	PREFIX_SWORD_DMG, 200, 50,
	PREFIX_WEAPON_DMG, 200, 50,
	//SUFFIX_MPDRAIN, 3, 3,
	SUFFIX_DELAY, 5, 5,
	PREFIX_CRITICAL, 5, 5,
	PREFIX_PIERCE, 5, 5,
	PREFIX_DEFENSE, 50, 30,


	//--------- 총 ---------//
	//마룡열화포
	PREFIX_GUN_DMG, 200, 50,
	PREFIX_WEAPON_DMG, 200, 50,
	PREFIX_SKILLDMG, 20, 10,
	//SUFFIX_SKILL, 1, 1,
	SUFFIX_EVASION, 5, 5,
	PREFIX_INT, 50, 30,
	PREFIX_EXTRA, 5, 5,

	//라그나로크
	PREFIX_GUN_DMG, 200, 50,
	PREFIX_WEAPON_DMG, 200, 50,
	SUFFIX_HPDRAIN, 10, 5,
	SUFFIX_CRITICAL, 20, 10,
	PREFIX_EXTRA, 5, 5,
	PREFIX_PIERCE, 5, 5,

	//--------- 부메랑 ---------//
	//드래곤 윙
	PREFIX_BOOMERANG_DMG, 200, 50,
	PREFIX_WEAPON_DMG, 200, 50,
	SUFFIX_CRITICAL, 20, 10,
	PREFIX_CRITICAL, 5, 5,
	PREFIX_AGI, 50, 30,
	PREFIX_DEFENSE, 50, 30,

	//디재스터 엣지
	PREFIX_BOOMERANG_DMG, 200, 50,
	PREFIX_WEAPON_DMG, 200, 50,
	//SUFFIX_MPDRAIN, 3, 3,
	SUFFIX_HPDRAIN, 10, 5,
	//SUFFIX_SKILL, 1, 1,
	PREFIX_SKILLDMG, 20, 10,
	PREFIX_EXTRA, 5, 5,
	PREFIX_DEFENSE, 50, 30,

	//--------- 헬멧 ---------//
	//미라주 헬름
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	PREFIX_HPRESTORE, 1000, 500,
	//PREFIX_MPRESTORE, 15, 10,
	PREFIX_ABSORB, 5, 5,
	SUFFIX_HP, 1000, 500,
	SUFFIX_ALLREGIST, 20, 10,

	//오시리스 헬맷
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	//PREFIX_MPRESTORE, 15, 10,
	PREFIX_HPRESTORE, 1000, 500,
	SUFFIX_HPDRAIN, 10, 5,
	PREFIX_ABSORB, 5, 5,
	SUFFIX_DEBUF, 10, 10,

	//--------- 모자 ---------//
	//나이트메어 헷
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	PREFIX_HPRESTORE, 1000, 500,
	//PREFIX_MPRESTORE, 15, 10,
	SUFFIX_HP, 10000, 5000,
	//SUFFIX_MP, 150, 50,
	SUFFIX_HIT, 5, 5,
	PREFIX_ABSORB, 5, 5,

	//오딘 크라운
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	PREFIX_HPRESTORE, 1000, 500,
	//SUFFIX_SKILL, 1, 1,
	PREFIX_SKILLDMG, 20, 10,
	SUFFIX_EVASION, 5, 5,
	SUFFIX_STUN, 10, 10,

	//--------- 캡 ---------//
	//다이너스티 캡
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	PREFIX_HPRESTORE, 1000, 500,
	//PREFIX_MPRESTORE, 15, 10,
	PREFIX_SKILLDMG, 20, 10,
	SUFFIX_HP, 10000, 5000,
	SUFFIX_DEBUF, 10, 10,

	//리바이어선 캡
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	//PREFIX_MPRESTORE, 15, 10,
	PREFIX_HPRESTORE, 1000, 500,
	SUFFIX_HPDRAIN, 10, 5,
	SUFFIX_STUN, 5, 5,
	SUFFIX_DEBUF, 10, 10,

	//--------- 갑옷 ---------//
	//브리간다인
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	SUFFIX_STAT, 50, 30,
	//SUFFIX_SKILL, 1, 1,
	PREFIX_SKILLDMG, 20, 10,
	PREFIX_PIERCE, 10, 10,
	PREFIX_VIT, 1000, 500,

	//바하무트 아머
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	SUFFIX_EXP, 30, 20,
	SUFFIX_CRITICAL, 20, 10,
	PREFIX_EXTRA, 5, 5,
	SUFFIX_IGNORE, 5, 5,

	//--------- 조끼 ---------//
	//뱀파이어로드
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	SUFFIX_CRITICAL, 20, 10,
	PREFIX_CRITICAL, 5, 5,
	PREFIX_INT, 15, 5,
	SUFFIX_STUN, 5, 5,

	//루시펠로브
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	PREFIX_CRITICAL, 5, 5,
	SUFFIX_EXP, 30, 20,
	SUFFIX_IGNORE, 5, 5,
	PREFIX_ABSORB, 20, 10,

	//--------- 코트 ---------//
	//페가수스 코트
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	//SUFFIX_SKILL, 1, 1,
	PREFIX_SKILLDMG, 20, 10,
	SUFFIX_STAT, 50, 30,
	PREFIX_VIT, 15, 5,
	SUFFIX_HIT, 5, 5,

	//카오스 엠페러
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	SUFFIX_STAT, 50, 30,
	SUFFIX_CRITICAL, 20, 10,
	PREFIX_PIERCE, 5, 5,
	SUFFIX_IGNORE, 5, 5,

	//--------- 건틀릿 ---------//
	//시바의 손톱
	PREFIX_ARMOR, 200, 50,
	PREFIX_WEAPON_DMG, 200, 50,
	PREFIX_CRITICAL, 5, 5,
	SUFFIX_CRITICAL, 20, 10,
	SUFFIX_HIT, 5, 5,
	PREFIX_STR, 15, 5,

	//바하무트 크로
	PREFIX_ARMOR, 200, 50,
	PREFIX_WEAPON_DMG, 200, 50,
	SUFFIX_LUCK, 30, 20,
	PREFIX_SKILLDMG, 35, 10,
	SUFFIX_STUN, 5, 5,
	PREFIX_EXTRA, 5, 5,

	//--------- 팔찌 ---------//
	//엠프레스 암렛
	PREFIX_ARMOR, 200, 50,
	PREFIX_WEAPON_DMG, 200, 50,
	//SUFFIX_MPDRAIN, 3, 3,
	PREFIX_HPRESTORE, 1000, 500,
	SUFFIX_HPDRAIN, 10, 5,
	PREFIX_AGI, 15, 5,
	SUFFIX_IGNORE, 5, 5,

	//갓 핸드
	PREFIX_ARMOR, 200, 50,
	PREFIX_WEAPON_DMG, 200, 50,
	//SUFFIX_MPDRAIN, 3, 3,
	PREFIX_HPRESTORE, 1000, 500,
	SUFFIX_LUCK, 30, 20,
	PREFIX_DEFENSE, 50, 15,
	SUFFIX_HIT, 5, 5,

	//--------- 장갑 ---------//
	//이터널 져지
	PREFIX_ARMOR, 200, 50,
	PREFIX_WEAPON_DMG, 200, 50,
	//SUFFIX_MPDRAIN, 3, 3,
	PREFIX_HPRESTORE, 1000, 500,
	SUFFIX_HPDRAIN, 10, 5,
	PREFIX_AGI, 50, 30,
	SUFFIX_HIT, 5, 5,

	//홀리 핸드
	PREFIX_ARMOR, 200, 50,
	PREFIX_WEAPON_DMG, 200, 50,
	//SUFFIX_EXP, 30, 20,
	PREFIX_HPRESTORE, 100, 500,
	PREFIX_CRITICAL, 5, 5,
	SUFFIX_STUN, 5, 5,
	PREFIX_DEFENSE, 50, 15,

	//--------- 킬트 ---------//
	//언리밋 킬트
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	SUFFIX_DELAY, 15, 15,
	PREFIX_SKILLDMG, 35, 10,
	PREFIX_AGI, 50, 30,
	SUFFIX_EVASION, 5, 5,

	//용기사 바지
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	SUFFIX_DELAY, 15, 15,
	//SUFFIX_SKILL, 1, 1,
	PREFIX_SKILLDMG, 35, 10,
	PREFIX_ABSORB, 20, 10,
	SUFFIX_HIT, 5, 5,

	//--------- 스커트 ---------//
	//성령의 치마
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	SUFFIX_STAT, 50, 30,
	SUFFIX_DELAY, 15, 15,
	PREFIX_VIT, 50, 30,
	SUFFIX_ALLREGIST, 20, 10,

	//태양의 스커트
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	//PREFIX_MPRESTORE, 15, 10,
	PREFIX_SKILLDMG, 35, 10,
	PREFIX_SKILLDMG, 35, 10,
	SUFFIX_EVASION, 5, 5,
	PREFIX_ABSORB, 20, 10,

	//--------- 바지 ---------//
	//아비스 팬츠
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	PREFIX_SKILLDMG, 35, 10,
	SUFFIX_DELAY, 15, 15,
	PREFIX_ABSORB, 20, 10,
	PREFIX_INT, 50, 30,

	//아누비스 바지
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	PREFIX_HPRESTORE, 1000, 500,
	PREFIX_SKILLDMG, 35, 10,
	SUFFIX_ALLREGIST, 20, 10,
	SUFFIX_EVASION, 5, 5,

	//--------- 그리브 ---------//
	//종말의 발소리
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	//SUFFIX_EXP, 30, 20,
	PREFIX_HPRESTORE, 1000, 500,
	SUFFIX_LUCK, 30, 20,
	PREFIX_INT, 50, 30,
	SUFFIX_DEBUF, 35, 10,

	//가이아그리브
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	SUFFIX_STAT, 50, 30,
	PREFIX_HPRESTORE, 1000, 500,
	SUFFIX_HP, 1000, 500,
	SUFFIX_IGNORE, 5, 5,

	//--------- 슈즈 ---------//
	//그라비티 부츠
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	//SUFFIX_EXP, 30, 20,
	PREFIX_HPRESTORE, 1000, 500,
	SUFFIX_LUCK, 30, 20,
	PREFIX_STR, 50, 30,
	SUFFIX_EVASION, 5, 5,

	//데스티니 부츠
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	SUFFIX_DELAY, 15, 15,
	SUFFIX_STAT, 50, 30,
	SUFFIX_DEBUF, 20, 10,
	SUFFIX_HP, 1000, 500,

	//--------- 부츠 ---------//
	//템페스트 슈즈
	PREFIX_ARMOR, 200, 50,
	SUFFIX_ARMOR, 100, 50,
	//SUFFIX_EXP, 30, 20,
	PREFIX_HPRESTORE, 1000, 500,
	SUFFIX_LUCK, 30, 20,
	PREFIX_STR, 50, 30,
	SUFFIX_DEBUF, 20, 10,

	//헤븐리슈즈
	PREFIX_ARMOR, 50, 50,
	SUFFIX_ARMOR, 1000, 500,
	SUFFIX_LUCK, 30, 20,
	SUFFIX_DELAY, 10, 10,
	SUFFIX_HIT, 5, 5,
	//SUFFIX_MP, 150, 50,
	SUFFIX_HP, 10000, 5000,
};
static const signed char optionStat_builtin[] = {
	//접두사 옵션
	PS_DMGMOD,	//PREFIX_WEAPON_DMG
	PS_DMGMOD,	//PREFIX_SWORD_DMG
	PS_DMGMOD,	//PREFIX_GUN_DMG
	PS_DMGMOD,	//PREFIX_BOOMERANG_DMG
	PS_CRITICAL,	//PREFIX_CRITICAL
	PS_PIERCE,	//PREFIX_PIERCE
	PS_EXTRA,	//PREFIX_EXTRA
	PS_STR,	//PREFIX_STR
	PS_AGI,	//PREFIX_AGI
	PS_VIT,	//PREFIX_VIT
	PS_INT,	//PREFIX_INT
	PS_SKILLDMG,	//PREFIX_SKILLDMG
	PS_DEFENSE,	//PREFIX_DEFENSE
	-1,	//PREFIX_ARMOR
	PS_ABSORB,	//PREFIX_ABSORB
	PS_FIRE,	//PREFIX_FIRE_REGIST
	PS_FROST,	//PREFIX_FROST_REGIST
	PS_THUNDER,	//PREFIX_THUNDER_REGIST
	PS_HOLY,	//PREFIX_HOLY_REGIST
	PS_DARK,	//PREFIX_DARK_REGIST
	PS_LUCK,	//PREFIX_LUCK
	PS_GOLDMOD,	//PREFIX_GOLD
	PS_EXPMOD,	//PREFIX_EXP
	PS_HPRESTORE,	//PREFIX_HPRESTORE
	PS_POTION,	//PREFIX_POTION
	PS_BUFF,	//PREFIX_BUFF
	-1,	//PREFIX_RESERVED1
	-1,	//PREFIX_RESERVED2
	-1,	//PREFIX_RESERVED3

	//접미사 옵션
	PS_DMGADD,	//SUFFIX_WEAPON_DMG
	PS_DMGADD,	//SUFFIX_SWORD_DMG
	PS_DMGADD,	//SUFFIX_GUN_DMG
	PS_DMGADD,	//SUFFIX_BOOMERANG_DMG
	PS_FIREATTACK,	//SUFFIX_FIRE_ATTACK
	PS_FROSTATTACK,	//SUFFIX_FROST_ATTACK
	PS_THUNDERATTACK,	//SUFFIX_THUNDER_ATTACK
	PS_HOLYATTACK,	//SUFFIX_HOLY_ATTACK
	PS_DARKATTACK,	//SUFFIX_DARK_ATTACK
	PS_HIT,	//SUFFIX_HIT
	PS_IGNORE,	//SUFFIX_IGNORE
	PS_DELAY,	//SUFFIX_DELAY
	PS_CRITDMG,	//SUFFIX_CRITICAL
	PS_EVASION,	//SUFFIX_EVASION
	PS_STR,	//SUFFIX_STAT
	PS_HP,	//SUFFIX_HP
	PS_HPDRAIN,	//SUFFIX_HPDRAIN
	PS_FIRE,	//SUFFIX_ALLREGIST
	PS_ARMOR,	//SUFFIX_ARMOR
	PS_LUCK,	//SUFFIX_LUCK
	PS_GOLDMOD,	//SUFFIX_GOLD
	PS_EXPMOD,	//SUFFIX_EXP
	-1,	//SUFFIX_REQUIRE
	PS_DEBUF,	//SUFFIX_DEBUF
	PS_STUN,	//SUFFIX_STUN
	PS_SKILL,	//SUFFIX_SKILL
	-1,	//SUFFIX_RESERVED1
	-1,	//SUFFIX_RESERVED2
	-1,	//SUFFIX_RESERVED3

	-1,	//SUFFIX_ENEMYREGEN
	-1,	//SUFFIX_POISON_IMMUNE
	-1,	//SUFFIX_BLIND_IMMUNE
	-1,	//SUFFIX_SLOW_IMMUNE
	-1,	//SUFFIX_CURSE_IMMUNE
	-1,	//SUFFIX_STUN_IMMUNE
	-1,	//SUFFIX_ALWAYSCURSE
	PS_HPRESTORE,	//SUFFIX_HPDECREASE
	PS_ARMOR,	//SUFFIX_MINUSARMOR
	PS_HPDRAIN,	//SUFFIX_MINUSDRAIN
	PS_HP,	//SUFFIX_MINUSHP
	PS_MP,	//SUFFIX_MINUSMP
	PS_EVASION,	//SUFFIX_MINUSEVASION
	PS_HIT,	//SUFFIX_MINUSHIT
	PS_FIRE,	//SUFFIX_MINUSREGIST
	PS_INT,	//SUFFIX_MINUSINT
	PS_STR,	//SUFFIX_MINUSSTR
	PS_AGI,	//SUFFIX_MINUSAGI
	PS_DEBUF,	//SUFFIX_PLUSDEBUF
	PS_SKILL,	//SUFFIX_MINUSSKILL
	PS_SKILLDMG,	//SUFFIX_MINUSSKILLDMG
};
static const signed char option_prefix_builtin[] = {
	//EQUIP_WEAPON(14)
	PREFIX_WEAPON_DMG,
	PREFIX_SWORD_DMG,
	PREFIX_CRITICAL,
	PREFIX_PIERCE,
	PREFIX_EXTRA,
	PREFIX_STR,
	PREFIX_AGI,
	PREFIX_VIT,
	PREFIX_INT,
	PREFIX_SKILLDMG,
	PREFIX_DEFENSE,
	PREFIX_LUCK,
	PREFIX_GOLD,
	PREFIX_EXP,
	-1,
	-1,

	//EQUIP_HELM(16)
	PREFIX_CRITICAL,
	PREFIX_PIERCE,
	PREFIX_EXTRA,
	PREFIX_DEFENSE,
	PREFIX_ARMOR,
	PREFIX_ABSORB,
	PREFIX_FIRE_REGIST,
	PREFIX_FROST_REGIST,
	PREFIX_THUNDER_REGIST,
	PREFIX_HOLY_REGIST,
	PREFIX_DARK_REGIST,
	PREFIX_LUCK,
	PREFIX_GOLD,
	PREFIX_EXP,
	PREFIX_HPRESTORE,
	PREFIX_MPRESTORE,

	//EQUIP_ARMOR(16)
	PREFIX_CRITICAL,
	PREFIX_PIERCE,
	PREFIX_EXTRA,
	PREFIX_VIT,
	PREFIX_INT,
	PREFIX_DEFENSE,
	PREFIX_ARMOR,
	PREFIX_ABSORB,
	PREFIX_FIRE_REGIST,
	PREFIX_FROST_REGIST,
	PREFIX_THUNDER_REGIST,
	PREFIX_HOLY_REGIST,
	PREFIX_DARK_REGIST,
	PREFIX_LUCK,
	PREFIX_GOLD,
	PREFIX_EXP,

	//EQUIP_PANTS(16)
	PREFIX_STR,
	PREFIX_AGI,
	PREFIX_VIT,
	PREFIX_INT,
	PREFIX_SKILLDMG,
	PREFIX_ARMOR,
	PREFIX_ABSORB,
	PREFIX_FIRE_REGIST,
	PREFIX_FROST_REGIST,
	PREFIX_THUNDER_REGIST,
	PREFIX_HOLY_REGIST,
	PREFIX_DARK_REGIST,
	PREFIX_HPRESTORE,
	PREFIX_MPRESTORE,
	PREFIX_POTION,
	PREFIX_BUFF,

	//EQUIP_GLOVE(14)
	PREFIX_WEAPON_DMG,
	PREFIX_CRITICAL,
	PREFIX_PIERCE,
	PREFIX_EXTRA,
	PREFIX_STR,
	PREFIX_AGI,
	PREFIX_SKILLDMG,
	PREFIX_DEFENSE,
	PREFIX_ARMOR,
	PREFIX_LUCK,
	PREFIX_GOLD,
	PREFIX_EXP,
	PREFIX_POTION,
	PREFIX_BUFF,
	-1,
	-1,

	//EQUIP_BOOTS(14)
	PREFIX_CRITICAL,
	PREFIX_PIERCE,
	PREFIX_EXTRA,
	PREFIX_STR,
	PREFIX_AGI,
	PREFIX_VIT,
	PREFIX_INT,
	PREFIX_DEFENSE,
	PREFIX_ARMOR,
	PREFIX_LUCK,
	PREFIX_GOLD,
	PREFIX_EXP,
	PREFIX_POTION,
	PREFIX_BUFF,
	-1,
	-1,

	//EQUIP_NECK(16)
	PREFIX_WEAPON_DMG,
	PREFIX_PIERCE,
	PREFIX_EXTRA,
	PREFIX_STR,
	PREFIX_AGI,
	PREFIX_ABSORB,
	PREFIX_FIRE_REGIST,
	PREFIX_FROST_REGIST,
	PREFIX_THUNDER_REGIST,
	PREFIX_HOLY_REGIST,
	PREFIX_DARK_REGIST,
	PREFIX_LUCK,
	PREFIX_GOLD,
	PREFIX_EXP,
	PREFIX_HPRESTORE,
	PREFIX_MPRESTORE,

	//EQUIP_RING(16)
	PREFIX_WEAPON_DMG,
	PREFIX_CRITICAL,
	PREFIX_PIERCE,
	PREFIX_EXTRA,
	PREFIX_DEFENSE,
	PREFIX_ABSORB,
	PREFIX_FIRE_REGIST,
	PREFIX_FROST_REGIST,
	PREFIX_THUNDER_REGIST,
	PREFIX_HOLY_REGIST,
	PREFIX_DARK_REGIST,
	PREFIX_LUCK,
	PREFIX_GOLD,
	PREFIX_EXP,
	PREFIX_HPRESTORE,
	PREFIX_MPRESTORE,
};
static const signed char option_suffix_builtin[] = {
	//EQUIP_WEAPON(14)
	SUFFIX_WEAPON_DMG,
	SUFFIX_SWORD_DMG,
	SUFFIX_FIRE_ATTACK,
	SUFFIX_HIT,
	SUFFIX_IGNORE,
	SUFFIX_CRITICAL,
	SUFFIX_HPDRAIN,
	SUFFIX_MPDRAIN,
	SUFFIX_LUCK,
	SUFFIX_GOLD,
	SUFFIX_EXP,
	SUFFIX_REQUIRE,
	SUFFIX_STUN,
	SUFFIX_SKILL,
	-1,
	-1,

	//EQUIP_HELM(16)
	SUFFIX_DELAY,
	SUFFIX_CRITICAL,
	SUFFIX_EVASION,
	SUFFIX_HP,
	SUFFIX_MP,
	SUFFIX_HPDRAIN,
	SUFFIX_MPDRAIN,
	SUFFIX_ALLREGIST,
	SUFFIX_ARMOR,
	SUFFIX_LUCK,
	SUFFIX_GOLD,
	SUFFIX_EXP,
	SUFFIX_REQUIRE,
	SUFFIX_DEBUF,
	SUFFIX_STUN,
	SUFFIX_SKILL,

	//EQUIP_ARMOR(16)
	SUFFIX_HIT,
	SUFFIX_IGNORE,
	SUFFIX_CRITICAL,
	SUFFIX_EVASION,
	SUFFIX_STAT,
	SUFFIX_HP,
	SUFFIX_MP,
	SUFFIX_ALLREGIST,
	SUFFIX_ARMOR,
	SUFFIX_LUCK,
	SUFFIX_GOLD,
	SUFFIX_EXP,
	SUFFIX_REQUIRE,
	SUFFIX_DEBUF,
	SUFFIX_STUN,
	SUFFIX_SKILL,

	//EQUIP_PANTS(16)
	SUFFIX_HIT,
	SUFFIX_IGNORE,
	SUFFIX_DELAY,
	SUFFIX_CRITICAL,
	SUFFIX_EVASION,
	SUFFIX_STAT,
	SUFFIX_HP,
	SUFFIX_MP,
	SUFFIX_HPDRAIN,
	SUFFIX_MPDRAIN,
	SUFFIX_ALLREGIST,
	SUFFIX_ARMOR,
	SUFFIX_REQUIRE,
	SUFFIX_DEBUF,
	SUFFIX_STUN,
	SUFFIX_SKILL,

	//EQUIP_GLOVE(14)
	SUFFIX_WEAPON_DMG,
	SUFFIX_FIRE_ATTACK,
	SUFFIX_HIT,
	SUFFIX_IGNORE,
	SUFFIX_CRITICAL,
	SUFFIX_STAT,
	SUFFIX_HPDRAIN,
	SUFFIX_MPDRAIN,
	SUFFIX_ARMOR,
	SUFFIX_LUCK,
	SUFFIX_GOLD,
	SUFFIX_EXP,
	SUFFIX_REQUIRE,
	SUFFIX_STUN,
	-1,
	-1,

	//EQUIP_BOOTS(14)
	SUFFIX_HIT,
	SUFFIX_IGNORE,
	SUFFIX_DELAY,
	SUFFIX_EVASION,
	SUFFIX_STAT,
	SUFFIX_HP,
	SUFFIX_MP,
	SUFFIX_ARMOR,
	SUFFIX_LUCK,
	SUFFIX_GOLD,
	SUFFIX_EXP,
	SUFFIX_REQUIRE,
	SUFFIX_DEBUF,
	SUFFIX_STUN,
	-1,
	-1,

	//EQUIP_NECK(16)
	SUFFIX_WEAPON_DMG,
	SUFFIX_FIRE_ATTACK,
	SUFFIX_HIT,
	SUFFIX_IGNORE,
	SUFFIX_CRITICAL,
	SUFFIX_EVASION,
	SUFFIX_STAT,
	SUFFIX_HP,
	SUFFIX_MP,
	SUFFIX_HPDRAIN,
	SUFFIX_ALLREGIST,
	SUFFIX_LUCK,
	SUFFIX_GOLD,
	SUFFIX_EXP,
	SUFFIX_STUN,
	SUFFIX_SKILL,

	//EQUIP_RING(16)
	SUFFIX_WEAPON_DMG,
	SUFFIX_FIRE_ATTACK,
	SUFFIX_HIT,
	SUFFIX_IGNORE,
	SUFFIX_CRITICAL,
	SUFFIX_EVASION,
	SUFFIX_STAT,
	SUFFIX_HP,
	SUFFIX_MP,
	SUFFIX_MPDRAIN,
	SUFFIX_ALLREGIST,
	SUFFIX_LUCK,
	SUFFIX_GOLD,
	SUFFIX_EXP,
	SUFFIX_STUN,
	SUFFIX_SKILL,
};
static const unsigned char option_count_prefix_builtin[] = {
	14,	//EQUIP_WEAPON
	16,	//EQUIP_HELM
	16,	//EQUIP_ARMOR
	16,	//EQUIP_PANTS
	14,	//EQUIP_GLOVE
	14,	//EQUIP_BOOTS
	16,	//EQUIP_NECK
	16,	//EQUIP_RING
};
static const unsigned char option_count_suffix_builtin[] = {
	14,	//EQUIP_WEAPON
	16,	//EQUIP_HELM
	16,	//EQUIP_ARMOR
	16,	//EQUIP_PANTS
	14,	//EQUIP_GLOVE
	14,	//EQUIP_BOOTS
	16,	//EQUIP_NECK
	16,	//EQUIP_RING
};
static const unsigned char gemOption_builtin[] = {
	PREFIX_STR, 5, 10,		//GEM_STR
	PREFIX_AGI, 5, 10,		//GEM_AGI
	PREFIX_VIT, 5, 10,		//GEM_VIT
	PREFIX_INT, 5, 10,		//GEM_INT
	SUFFIX_STAT, 2, 4,		//GEM_STAT
	PREFIX_FIRE_REGIST, 7, 15,			//GEM_FIRE_REG
	PREFIX_FROST_REGIST, 7, 15,		//GEM_FROST_REG
	PREFIX_THUNDER_REGIST, 7, 15,		//GEM_THUNDER_REG
	PREFIX_HOLY_REGIST, 7, 15,	//GEM_HOLY_REG
	PREFIX_DARK_REGIST, 7, 15,	//GEM_DARK_REG
	SUFFIX_ALLREGIST, 2, 4,	//GEM_REG
	PREFIX_CRITICAL, 2, 4,	//GEM_CRITICAL
	SUFFIX_EVASION, 2, 4,	//GEM_EVASION
	SUFFIX_HIT, 2, 4,			//GEM_HIT
	PREFIX_PIERCE, 2, 4,		//GEM_PIERCE
	SUFFIX_STUN, 2, 4,	//GEM_STUN
	PREFIX_EXTRA, 2, 4,		//GEM_EXTRA
	SUFFIX_IGNORE, 2, 4,		//GEM_IGNORE
	SUFFIX_HPDRAIN, 2, 4,	//GEM_HPDRAIN
	SUFFIX_MPDRAIN, 2, 4,	//GEM_MPDRAIN
	PREFIX_LUCK, 5, 15,			//GEM_LUCK
	SUFFIX_CRITICAL, 2, 5,	//GEM_CRITICAL_DMG
	PREFIX_GOLD, 5, 15,		//GEM_GOLD
	PREFIX_EXP, 5, 15,			//GEM_EXP
	SUFFIX_REQUIRE, 5, 10,	//GEM_REQUIRE
	PREFIX_WEAPON_DMG, 3, 7,	//GEM_WEAPON_DMG
	SUFFIX_WEAPON_DMG, 5, 10,	//GEM_ADD_DMG
};
static const int gemPrice_builtin[] = {
	10, 50, 100, 300, 500, 1000,
};
static const int enchantRate_builtin[] = {
	//일반, 고급, 희귀, 세트, 영웅, 전설
	//0, 0, 0, 0, 0, 0,//0
	100, 95, 90, 85, 80, 75,//0
	99, 94, 89, 84, 79, 74,//1
	98, 93, 88, 83, 78, 73,//2
	97, 92, 87, 82, 77, 72,//3
	96, 91, 86, 81, 76, 71,//4

	95, 90, 85, 80, 75, 70,//5
	94, 89, 84, 79, 74, 69,//6
	93, 88, 83, 78, 73, 68,//7
	92, 87, 82, 77, 72, 67,//8
	91, 86, 81, 76, 71, 66,//9

	90, 85, 80, 75, 70, 65,//10
	89, 84, 79, 74, 69, 64,//11
	88, 83, 78, 73, 68, 63,//12
	87, 82, 77, 72, 67, 62,//13
	86, 81, 76, 71, 66, 61,//14

	85, 80, 75, 70, 65, 60,//15
	84, 79, 74, 69, 64, 59,//16
	83, 78, 73, 68, 63, 58,//17
	82, 77, 72, 67, 62, 57,//18
	81, 76, 71, 66, 61, 56,//19

	80, 75, 70, 65, 60, 55,//20
	79, 74, 69, 64, 59, 54,//21
	78, 73, 68, 63, 58, 53,//22
	77, 72, 67, 62, 57, 52,//23
	76, 71, 66, 61, 56, 51,//24

	75, 70, 65, 60, 55, 50,//25
	74, 69, 64, 59, 54, 49,//26
	73, 68, 63, 58, 53, 48,//27
	72, 67, 62, 57, 52, 47,//28
	71, 66, 61, 56, 51, 46,//29

	70, 65, 60, 55, 50, 45,//30
	69, 64, 59, 54, 49, 44,//31
	68, 63, 58, 53, 48, 43,//32
	67, 62, 57, 52, 47, 42,//33
	66, 61, 56, 51, 46, 41,//34

	65, 60, 55, 50, 45, 40,//35
	64, 59, 54, 49, 44, 39,//36
	63, 58, 53, 48, 43, 38,//37
	62, 57, 52, 47, 42, 37,//38
	61, 56, 51, 46, 41, 36,//39

	60, 55, 50, 45, 40, 35,//40
	59, 54, 49, 44, 39, 34,//41
	58, 53, 48, 43, 38, 33,//42
	57, 52, 47, 42, 37, 32,//43
	56, 51, 46, 41, 36, 31,//44

	55, 50, 45, 40, 35, 30,//45
	54, 49, 44, 39, 34, 29,//46
	53, 48, 43, 38, 33, 28,//47
	52, 47, 42, 37, 32, 27,//48
	51, 46, 41, 36, 31, 26,//49
};
static const unsigned char extraSetItem_builtin[] = {
	//대원 동굴 장비
	//로빈 동굴 1 흐룬팅						
	SET_RA1, PREFIX_SWORD_DMG, SUFFIX_HIT, //메인
	SET_RA2, PREFIX_SWORD_DMG, SUFFIX_HIT, //서브
	//로빈 동굴 2 그람						
	SET_RB1, PREFIX_SWORD_DMG, SUFFIX_IGNORE, //메인
	SET_RB2, PREFIX_SWORD_DMG, SUFFIX_IGNORE, //서브
	//로빈 동굴 3 아슈겔론						
	SET_RD1, PREFIX_SWORD_DMG, SUFFIX_LUCK, //메인
	SET_RC2, PREFIX_SWORD_DMG, PREFIX_CRITICAL, //서브
	//로빈 동굴 4 스톰브링거						
	SET_RC1, PREFIX_SWORD_DMG, PREFIX_WEAPON_DMG, //메인
	SET_RD2, PREFIX_SWORD_DMG, SUFFIX_GOLD, //서브//23
	//디아나 동굴 1 가에보르그						
	SET_DA1, PREFIX_GUN_DMG, SUFFIX_HIT, //메인
	SET_DA2, PREFIX_GUN_DMG, SUFFIX_HIT, //서브
	//디아나 동굴 2 게이볼그						
	SET_DB1, PREFIX_GUN_DMG, SUFFIX_IGNORE, //메인
	SET_DB2, PREFIX_GUN_DMG, SUFFIX_IGNORE, //서브
	//디아나 동굴 3 롱기누스						
	SET_DD1, PREFIX_GUN_DMG, SUFFIX_LUCK, //메인
	SET_DC2, PREFIX_GUN_DMG, PREFIX_CRITICAL, //서브
	//디아나 동굴 4 마탄 타흘룸						
	SET_DC1, PREFIX_GUN_DMG, PREFIX_WEAPON_DMG,	//메인
	SET_DD2, PREFIX_GUN_DMG, SUFFIX_GOLD, //서브
	//맥스 동굴 1 칼라드볼그						
	SET_MA1, PREFIX_BOOMERANG_DMG, SUFFIX_HIT, //메인
	SET_MA2, PREFIX_BOOMERANG_DMG, SUFFIX_HIT, //서브
	//맥스 동굴 2 궁니르						
	SET_MB1, PREFIX_BOOMERANG_DMG, SUFFIX_IGNORE, //메인
	SET_MB2, PREFIX_BOOMERANG_DMG, SUFFIX_IGNORE, //서브
	//맥스 동굴 3 프라가라흐						
	SET_MD1, PREFIX_BOOMERANG_DMG, SUFFIX_LUCK, //메인
	SET_MC2, PREFIX_BOOMERANG_DMG, PREFIX_CRITICAL, //서브
	//맥스 동굴 4 묠니르						
	SET_MC1, PREFIX_BOOMERANG_DMG, PREFIX_WEAPON_DMG, //메인
	SET_MD2, PREFIX_BOOMERANG_DMG, SUFFIX_GOLD, //서브

	//로빈 동굴 1 아케론 헬름						
	SET_RA1, PREFIX_ARMOR, SUFFIX_DEBUF, //메인
	SET_RA2, PREFIX_ARMOR, SUFFIX_DEBUF, //서브
	//로빈 동굴 2 세이렌 헬름						
	SET_RB1, PREFIX_ARMOR, SUFFIX_DELAY, //메인
	SET_RB2, PREFIX_ARMOR, SUFFIX_DELAY, //서브
	//로빈 동굴 3 타이탄 헬름						
	SET_RC1, PREFIX_ARMOR, SUFFIX_DEBUF, //메인
	SET_RC2, PREFIX_ARMOR, SUFFIX_DEBUF, //서브
	//로빈 동굴 4 티폰 헬름						
	SET_RD1, PREFIX_ARMOR, SUFFIX_LUCK, //메인
	SET_RD2, PREFIX_ARMOR, SUFFIX_GOLD, //서브
	//디아나 동굴 1 네메시스 헷						
	SET_DA1, PREFIX_ARMOR, SUFFIX_DEBUF, //메인
	SET_DA2, PREFIX_ARMOR, SUFFIX_DEBUF, //서브
	//디아나 동굴 2 프시케 헷						
	SET_DB1, PREFIX_ARMOR, SUFFIX_DELAY, //메인
	SET_DB2, PREFIX_ARMOR, SUFFIX_DELAY, //서브
	//디아나 동굴 3 아탈란타 헷						
	SET_DC1, PREFIX_ARMOR, SUFFIX_DEBUF, //메인
	SET_DC2, PREFIX_ARMOR, SUFFIX_DEBUF, //서브
	//디아나 동굴 4 레테 크라운						
	SET_DD1, PREFIX_ARMOR, SUFFIX_LUCK, //메인
	SET_DD2, PREFIX_ARMOR, SUFFIX_GOLD, //서브
	//맥스 동굴 1 플레케톤 캡						
	SET_MA1, PREFIX_ARMOR, SUFFIX_DEBUF, //메인
	SET_MA2, PREFIX_ARMOR, SUFFIX_DEBUF, //서브
	//맥스 동굴 2 타나토스 캡						
	SET_MB1, PREFIX_ARMOR, SUFFIX_DELAY, //메인
	SET_MB2, PREFIX_ARMOR, SUFFIX_DELAY, //서브
	//맥스 동굴 3 미다스 캡						
	SET_MC1, PREFIX_ARMOR, SUFFIX_DEBUF, //메인
	SET_MC2, PREFIX_ARMOR, SUFFIX_DEBUF, //서브
	//맥스 동굴 4 에레보스 캡						
	SET_MD1, PREFIX_ARMOR, SUFFIX_LUCK, //메인
	SET_MD2, PREFIX_ARMOR, SUFFIX_GOLD, //서브

	//로빈 동굴 1 아케론 아머						
	SET_RA1, PREFIX_ARMOR, PREFIX_ABSORB, //메인
	SET_RA2, PREFIX_ARMOR, PREFIX_ABSORB, //서브
	//로빈 동굴 2 세이렌 아머						
	SET_RB1, PREFIX_ARMOR, SUFFIX_HIT, //메인
	SET_RB2, PREFIX_ARMOR, SUFFIX_HIT, //서브
	//로빈 동굴 3 타이탄 아머						
	SET_RD1, PREFIX_ARMOR, SUFFIX_LUCK, //메인
	SET_RC2, PREFIX_ARMOR, PREFIX_WEAPON_DMG, //서브
	//로빈 동굴 4 티폰 아머						
	SET_RC1,PREFIX_ARMOR, PREFIX_WEAPON_DMG, //메인
	SET_RD2, PREFIX_ARMOR, SUFFIX_GOLD, //서브
	//디아나 동굴 1 네메시스 로브						
	SET_DA1, PREFIX_ARMOR, PREFIX_ABSORB, //메인
	SET_DA2, PREFIX_ARMOR, PREFIX_ABSORB, //서브
	//디아나 동굴 2 프시케 드레스						
	SET_DB1, PREFIX_ARMOR, SUFFIX_HIT, //메인
	SET_DB2, PREFIX_ARMOR, SUFFIX_HIT, //서브
	//디아나 동굴 3 아탈란타 로브						
	SET_DD1, PREFIX_ARMOR, SUFFIX_LUCK, //메인
	SET_DC2, PREFIX_ARMOR, PREFIX_WEAPON_DMG, //서브
	//디아나 동굴 4 레테 로브						
	SET_DC1, PREFIX_ARMOR, PREFIX_WEAPON_DMG, //메인
	SET_DD2, PREFIX_ARMOR, SUFFIX_GOLD, //서브
	//맥스 동굴 1 플레케톤 코트						
	SET_MA1, PREFIX_ARMOR, PREFIX_ABSORB, //메인
	SET_MA2, PREFIX_ARMOR, PREFIX_ABSORB, //서브
	//맥스 동굴 2 타나토스 코트						
	SET_MB1, PREFIX_WEAPON_DMG, SUFFIX_HIT, //메인
	SET_MB2, PREFIX_WEAPON_DMG, SUFFIX_HIT, //서브
	//맥스 동굴 3 미다스 코트						
	SET_MD1, PREFIX_ARMOR, SUFFIX_LUCK, //메인
	SET_MC2, PREFIX_ARMOR, PREFIX_WEAPON_DMG, //서브
	//맥스 동굴 4 에레보스 코트						
	SET_MC1, PREFIX_ARMOR, PREFIX_WEAPON_DMG, //메인
	SET_MD2, PREFIX_ARMOR, SUFFIX_GOLD, //서브

	//로빈 동굴 1 아케론 건틀렛						
	SET_RA1, PREFIX_WEAPON_DMG, SUFFIX_EVASION, //메인
	SET_RA2, PREFIX_WEAPON_DMG, SUFFIX_EVASION, //서브
	//로빈 동굴 2 세이렌 건틀렛						
	SET_RB1, PREFIX_WEAPON_DMG, PREFIX_SKILLDMG, //메인
	SET_RB2, PREFIX_WEAPON_DMG, PREFIX_SKILLDMG, //서브
	//로빈 동굴 3 타이탄 건틀렛						
	SET_RD1, PREFIX_WEAPON_DMG, SUFFIX_LUCK, //메인
	SET_RC2, PREFIX_WEAPON_DMG, SUFFIX_WEAPON_DMG, //서브
	//로빈 동굴 4 티폰 건틀렛						
	SET_RC1, PREFIX_WEAPON_DMG, SUFFIX_WEAPON_DMG, //메인
	SET_RD2, PREFIX_WEAPON_DMG, SUFFIX_GOLD, //서브
	//디아나 동굴 1 네메시스 암렛						
	SET_DA1, PREFIX_WEAPON_DMG, SUFFIX_EVASION, //메인
	SET_DA2, PREFIX_WEAPON_DMG, SUFFIX_EVASION, //서브
	//디아나 동굴 2 프시케 암렛						
	SET_DB1, PREFIX_WEAPON_DMG, PREFIX_SKILLDMG, //메인
	SET_DB2, PREFIX_WEAPON_DMG, PREFIX_SKILLDMG, //서브
	//디아나 동굴 3 아탈란타 암렛						
	SET_DD1, PREFIX_WEAPON_DMG, SUFFIX_LUCK, //메인
	SET_DC2, PREFIX_WEAPON_DMG, SUFFIX_WEAPON_DMG, //서브
	//디아나 동굴 4 레트 암렛						
	SET_DC1, PREFIX_WEAPON_DMG, SUFFIX_WEAPON_DMG, //메인
	SET_DD2, PREFIX_WEAPON_DMG, SUFFIX_GOLD, //서브
	//맥스 동굴 1 플레케톤 핸드						
	SET_MA1, PREFIX_WEAPON_DMG, SUFFIX_EVASION, //메인
	SET_MA2, PREFIX_WEAPON_DMG, SUFFIX_EVASION, //서브
	//맥스 동굴 2 타나토스 핸드						
	SET_MB1, PREFIX_WEAPON_DMG, PREFIX_SKILLDMG, //메인
	SET_MB2, PREFIX_WEAPON_DMG, PREFIX_SKILLDMG, //서브
	//맥스 동굴 3 미다스 글러브						
	SET_MD1, PREFIX_WEAPON_DMG, SUFFIX_LUCK, //메인
	SET_MC2, PREFIX_WEAPON_DMG, SUFFIX_WEAPON_DMG, //서브
	//맥스 동굴 4 에레보스 핸드						
	SET_MC1, PREFIX_WEAPON_DMG, SUFFIX_WEAPON_DMG, //메인
	SET_MD2, PREFIX_WEAPON_DMG, SUFFIX_GOLD, //서브

	//로빈 동굴 1 아케론 킬트						
	SET_RA1, PREFIX_ARMOR, SUFFIX_LUCK, //메인
	SET_RA2, PREFIX_ARMOR, PREFIX_ABSORB, //서브
	//로빈 동굴 2 세이렌 킬트						
	SET_RB1, PREFIX_ARMOR, SUFFIX_LUCK, //메인
	SET_RB2, PREFIX_ARMOR, PREFIX_ABSORB, //서브
	//로빈 동굴 3 타이탄 킬트						
	SET_RD1, PREFIX_ARMOR, SUFFIX_LUCK, //메인
	SET_RC2, PREFIX_ARMOR, PREFIX_ABSORB, //서브
	//로빈 동굴 4 티폰 킬트						
	SET_RC1, PREFIX_ARMOR, PREFIX_ABSORB, //메인
	SET_RD2, PREFIX_ARMOR, SUFFIX_GOLD, //서브
	//디아나 동굴 1 네메시스 치마						
	SET_DA1, PREFIX_ARMOR, SUFFIX_LUCK, //메인
	SET_DA2, PREFIX_ARMOR, PREFIX_ABSORB, //서브
	//디아나 동굴 2 프시케 스커트						
	SET_DB1, PREFIX_ARMOR, SUFFIX_LUCK, //메인
	SET_DB2, PREFIX_ARMOR, PREFIX_ABSORB, //서브
	//디아나 동굴 3 아탈란타 치마						
	SET_DD1, PREFIX_ARMOR, SUFFIX_LUCK, //메인
	SET_DC2, PREFIX_ARMOR, PREFIX_ABSORB, //서브
	//디아나 동굴 4 레테 스커트						
	SET_DC1, PREFIX_ARMOR, PREFIX_ABSORB, //메인
	SET_DD2, PREFIX_ARMOR, SUFFIX_GOLD, //서브
	//맥스 동굴 1 플레케톤 팬츠						
	SET_MA1, PREFIX_ARMOR, SUFFIX_LUCK, //메인
	SET_MA2, PREFIX_ARMOR, PREFIX_ABSORB, //서브
	//맥스 동굴 2 타나토스 팬츠						
	SET_MB1, PREFIX_ARMOR, SUFFIX_LUCK, //메인
	SET_MB2, PREFIX_ARMOR, PREFIX_ABSORB, //서브
	//맥스 동굴 3 미다스 팬츠						
	SET_MD1, PREFIX_ARMOR, SUFFIX_LUCK, //메인
	SET_MC2, PREFIX_ARMOR, PREFIX_ABSORB, //서브
	//맥스 동굴 4 에레보스 팬츠						
	SET_MC1, PREFIX_ARMOR, PREFIX_ABSORB, //메인
	SET_MD2, PREFIX_ARMOR, SUFFIX_GOLD, //서브

	//로빈 동굴 1 아케론 그리브						
	SET_RA1, PREFIX_ARMOR, SUFFIX_DELAY, //메인
	SET_RA2, PREFIX_ARMOR, SUFFIX_DELAY, //서브
	//로빈 동굴 2 세이렌 그리브						
	SET_RB1, PREFIX_ARMOR, SUFFIX_ALLREGIST, //메인
	SET_RB2, PREFIX_ARMOR, SUFFIX_ALLREGIST, //서브
	//로빈 동굴 3 타이탄 그리브						
	SET_RC1, PREFIX_ARMOR, SUFFIX_DELAY, //메인
	SET_RC2, PREFIX_ARMOR, SUFFIX_DELAY, //서브
	//로빈 동굴 4 티폰 그리브						
	SET_RD1, PREFIX_ARMOR, SUFFIX_LUCK, //메인
	SET_RD2, PREFIX_ARMOR, SUFFIX_GOLD, //서브
	//디아나 동굴 1 네메시스 슈즈						
	SET_DA1, PREFIX_ARMOR, SUFFIX_DELAY, //메인
	SET_DA2, PREFIX_ARMOR, SUFFIX_DELAY, //서브
	//디아나 동굴 2 프시케 슈즈						
	SET_DB1, PREFIX_ARMOR, SUFFIX_ALLREGIST, //메인
	SET_DB2, PREFIX_ARMOR, SUFFIX_ALLREGIST, //서브
	//디아나 동굴 3 아탈란타 슈즈						
	SET_DC1, PREFIX_ARMOR, SUFFIX_DELAY, //메인
	SET_DC2, PREFIX_ARMOR, SUFFIX_DELAY, //서브
	//디아나 동굴 4 레테 슈즈						
	SET_DD1, PREFIX_ARMOR, SUFFIX_LUCK, //메인
	SET_DD2, PREFIX_ARMOR, SUFFIX_GOLD, //서브
	//맥스 동굴 1 플레케톤 부츠						
	SET_MA1, PREFIX_ARMOR, SUFFIX_DELAY, //메인
	SET_MA2, PREFIX_ARMOR, SUFFIX_DELAY, //서브
	//맥스 동굴 2 타나토스 부츠						
	SET_MB1, PREFIX_ARMOR, SUFFIX_ALLREGIST, //메인
	SET_MB2, PREFIX_ARMOR, SUFFIX_ALLREGIST, //서브
	//맥스 동굴 3 미드사 부츠						
	SET_MC1, PREFIX_ARMOR, SUFFIX_DELAY, //메인
	SET_MC2, PREFIX_ARMOR, SUFFIX_DELAY, //서브
	//맥스 동굴 4 에레보스 부츠						
	SET_MD1, PREFIX_ARMOR, SUFFIX_LUCK, //메인
	SET_MD2, PREFIX_ARMOR, SUFFIX_GOLD, //서브

	//로빈 동굴 1 목걸이						
	SET_RA1, PREFIX_WEAPON_DMG, SUFFIX_HPDRAIN, //메인
	SET_RA2, PREFIX_WEAPON_DMG, SUFFIX_HPDRAIN, //서브
	//로빈 동굴 2 목걸이//세이렌						
	SET_RB1, PREFIX_WEAPON_DMG, PREFIX_CRITICAL, //메인
	SET_RB2, PREFIX_WEAPON_DMG, PREFIX_CRITICAL, //서브
	//로빈 동굴 3 목걸이//황혼의
	SET_RC1, PREFIX_WEAPON_DMG, SUFFIX_IGNORE, //메인
	SET_RC2, PREFIX_WEAPON_DMG, SUFFIX_IGNORE, //서브
	//로빈 동굴 4 목걸이//재앙의
	SET_RD1, PREFIX_WEAPON_DMG, SUFFIX_LUCK, //메인
	SET_RD2, PREFIX_WEAPON_DMG, SUFFIX_GOLD, //서브
	//디아나 동굴 1 목걸이						
	SET_DA1, PREFIX_WEAPON_DMG, SUFFIX_HPDRAIN, //메인
	SET_DA2, PREFIX_WEAPON_DMG, SUFFIX_HPDRAIN, //서브
	//디아나 동굴 2 목걸이						
	SET_DB1, PREFIX_WEAPON_DMG, PREFIX_CRITICAL, //메인
	SET_DB2, PREFIX_WEAPON_DMG, PREFIX_CRITICAL, //서브
	//디아나 동굴 3 목걸이						
	SET_DC1, PREFIX_WEAPON_DMG, SUFFIX_IGNORE, //메인
	SET_DC2, PREFIX_WEAPON_DMG, SUFFIX_IGNORE, //서브
	//디아나 동굴 4 목걸이						
	SET_DD1, PREFIX_WEAPON_DMG, SUFFIX_LUCK, //메인
	SET_DD2, PREFIX_WEAPON_DMG, SUFFIX_GOLD, //서브
	//맥스 동굴 1 목걸이						
	SET_MA1, PREFIX_WEAPON_DMG, SUFFIX_HPDRAIN, //메인
	SET_MA2, PREFIX_WEAPON_DMG, SUFFIX_HPDRAIN, //서브
	//맥스 동굴 2 목걸이						
	SET_MB1, PREFIX_WEAPON_DMG, PREFIX_CRITICAL, //메인
	SET_MB2, PREFIX_WEAPON_DMG, PREFIX_CRITICAL, //서브
	//맥스 동굴 3 목걸이						
	SET_MC1, PREFIX_WEAPON_DMG, SUFFIX_IGNORE, //메인
	SET_MC2, PREFIX_WEAPON_DMG, SUFFIX_IGNORE, //서브
	//맥스 동굴 4 목걸이						
	SET_MD1, PREFIX_WEAPON_DMG, SUFFIX_LUCK, //메인
	SET_MD2, PREFIX_WEAPON_DMG, SUFFIX_GOLD, //서브

	//로빈 동굴 1 반지	//니벨룽겐					
	SET_RA1, PREFIX_WEAPON_DMG, SUFFIX_LUCK, //메인
	SET_RA2, PREFIX_WEAPON_DMG, SUFFIX_IGNORE, //서브
	//로빈 동굴 2 반지						
	SET_RB1, PREFIX_WEAPON_DMG, PREFIX_ABSORB, //메인
	SET_RB2, PREFIX_WEAPON_DMG, PREFIX_ABSORB, //서브
	//로빈 동굴 3 반지						
	SET_RC1, PREFIX_WEAPON_DMG, SUFFIX_HPDRAIN, //메인
	SET_RC2, PREFIX_WEAPON_DMG, SUFFIX_IGNORE, //서브
	//로빈 동굴 4 반지						
	SET_RD1, PREFIX_WEAPON_DMG, SUFFIX_LUCK, //메인
	SET_RD2, PREFIX_WEAPON_DMG, SUFFIX_GOLD, //서브
	//디아나 동굴 1 반지	//절대					
	SET_DA1, PREFIX_WEAPON_DMG, SUFFIX_LUCK, //메인
	SET_DA2, PREFIX_WEAPON_DMG, SUFFIX_HPDRAIN, //서브
	//디아나 동굴 2 반지						
	SET_DB1, PREFIX_WEAPON_DMG, PREFIX_ABSORB, //메인
	SET_DB2, PREFIX_WEAPON_DMG, PREFIX_ABSORB, //서브
	//디아나 동굴 3 반지						
	SET_DC1, PREFIX_WEAPON_DMG, SUFFIX_HPDRAIN, //메인
	SET_DC2, PREFIX_WEAPON_DMG, SUFFIX_HPDRAIN, //서브
	//디아나 동굴 4 반지						
	SET_DD1, PREFIX_WEAPON_DMG, SUFFIX_LUCK, //메인
	SET_DD2, PREFIX_WEAPON_DMG, SUFFIX_GOLD, //서브
	//맥스 동굴 1 반지		//번뇌		
	SET_MA1, PREFIX_WEAPON_DMG, SUFFIX_LUCK, //메인
	SET_MA2, PREFIX_WEAPON_DMG, SUFFIX_HPDRAIN, //서브
	//맥스 동굴 2 반지						
	SET_MB1, PREFIX_WEAPON_DMG, PREFIX_ABSORB, //메인
	SET_MB2, PREFIX_WEAPON_DMG, PREFIX_ABSORB, //서브
	//맥스 동굴 3 반지						
	SET_MC1, PREFIX_WEAPON_DMG, SUFFIX_HPDRAIN, //메인
	SET_MC2, PREFIX_WEAPON_DMG, SUFFIX_HPDRAIN, //서브
	//맥스 동굴 4 반지						
	SET_MD1, PREFIX_WEAPON_DMG, SUFFIX_LUCK, //메인
	SET_MD2, PREFIX_WEAPON_DMG, SUFFIX_GOLD, //서브
};
static const signed int newItemReward_builtin[] = {
	//ITEM_SWORD,
	ITEM_HEART, false, false, 100,//연습용 몽둥이//TEXT_ITEMNAME_SWORD
	ITEM_HEART, false, false, 300,//롱소드
	ITEM_HEART, false, false, 500,//처형자의 검
	ITEM_HEART, false, false, 700,//파멸의 참마도
	ITEM_HEART, false, false, 1000, //추적자의 검
	ITEM_HEART, false, false, 1200, //격노의 양날검
	ITEM_HEART, false, false, 1500,//수호자의 검
	ITEM_HEART, false, false, 1800,//왕가의 수호자
	ITEM_HEART, false, false, 2000,//나찰의 검
	ITEM_HEART, false, false, 2200,//소울 크래셔
	ITEM_HEART, false, false, 2500,//플레임소드
	ITEM_HEART, false, false, 2700,//아이스소드
	ITEM_HEART, false, false, 3000,//썬더소드
	ITEM_HEART, false, false, 3200,//어스소드
	ITEM_HEART, false, false, 3500,//레바테인
	ITEM_HEART, false, false, 3800,//스톰브링거
	ITEM_HEART, false, false, 4000,//칼라드볼그
	ITEM_HEART, false, false, 4500,//발뭉
	ITEM_HEART, false, false, 5000,//흐룬팅
	ITEM_HEART, false, false, 5500,//거인의 칼
	ITEM_HEART, false, false, 6000,//미스틸테인
	ITEM_HEART, false, false, 6500,//엑스칼리버
	ITEM_HEART, false, false, 7000, //홀리소드
	ITEM_HEART, false, false, 7500,//다크소드
	ITEM_HEART, false, false, 8000,//레오소드
	ITEM_HEART, false, false, 8500,//사신의 낫
	ITEM_HEART, false, false, 9000,//드래곤 클로우
	ITEM_HEART, false, false, 9500,//황룡의 어금니
	ITEM_HEART, false, false, 10000,//신룡마강검
	ITEM_HEART, false, false, 10500,//드래곤 슬레이어
	ITEM_HEART, false, false, 11000,//얼티밋소드
	ITEM_HEART, false, false, 11500,//차원의 검
	ITEM_HEART, false, false, 12000, //천공의 검
	ITEM_HEART, false, false, 12500,//스타더스트
	ITEM_HEART, false, false, 13000,//패왕의 검

	//ITEM_GUN,
	ITEM_HEART, false, false, 100,//발화식 총//TEXT_ITEMNAME_GUN
	ITEM_HEART, false, false, 1500, //리볼버 파이슨
	ITEM_HEART, false, false, 1000, //45구경 오토건
	ITEM_HEART, false, false, 1000, //고져스 건
	ITEM_HEART, false, false, 1000, //회천마도총
	ITEM_HEART, false, false, 1000, //태양의 총
	ITEM_HEART, false, false, 1000, //헬파이어 건
	ITEM_HEART, false, false, 1000, //크로스 파이어

	//ITEM_BOOMERANG
	ITEM_HEART, false, false, 1000, //사냥용 부메랑//TEXT_ITEMNAME_BOOMERANG
	ITEM_HEART, false, false, 1000, //슬라이서
	ITEM_HEART, false, false, 1000, //강철 부메랑
	ITEM_HEART, false, false, 1000, //트라이 엣지
	ITEM_HEART, false, false, 1000, //라이트닝 엣지
	ITEM_HEART, false, false, 1000, //소울 체이서
	ITEM_HEART, false, false, 1000, //그리폰 윙
	ITEM_HEART, false, false, 1000, //로커스트 헌트

	//ITEM_HELM
	ITEM_HEART, false, false, 100,//헤드 가드
	ITEM_HEART, false, false, 1200, //바시넷
	ITEM_HEART, false, false, 2000,//솔저 헬름
	ITEM_HEART, false, false, 2700,//검투사의 투구
	ITEM_HEART, false, false, 3500,//스파이크 헤드
	ITEM_HEART, false, false, 4500,//그랜드 헬름
	ITEM_HEART, false, false, 6000,//고대의 투구
	ITEM_HEART, false, false, 7500, //용자의 투구

	//ITEM_HAT
	ITEM_HEART, false, false, 1000, //카우보이 모자//TEXT_ITEMNAME_HAT
	ITEM_HEART, false, false, 1000, //산책용 보닛
	ITEM_HEART, false, false, 1000, //레인저 햇
	ITEM_HEART, false, false, 1000, //서클릿
	ITEM_HEART, false, false, 1000, //올드 윌로우
	ITEM_HEART, false, false, 1000, //스나이퍼 고글
	ITEM_HEART, false, false, 1000, //혼란의 모자
	ITEM_HEART, false, false, 1000, //프리에스테스

	//ITEM_CAP
	ITEM_HEART, false, false, 1000, //공작깃털 모자//TEXT_ITEMNAME_CAP
	ITEM_HEART, false, false, 1000, //귀족의 머리띠
	ITEM_HEART, false, false, 1000, //거상의 모자
	ITEM_HEART, false, false, 1000, //사냥꾼 모자
	ITEM_HEART, false, false, 1000, //투우사의 모자
	ITEM_HEART, false, false, 1000, //해적의 모자
	ITEM_HEART, false, false, 1000, //에이스 캡
	ITEM_HEART, false, false, 1000, //드래곤 레어캡

	//ITEM_ARMOR
	ITEM_HEART, false, false, 100,//헌터 튜닉
	ITEM_HEART, false, false, 1500, //미늘 갑옷
	ITEM_HEART, false, false, 3000,//하프 플레이트
	ITEM_HEART, false, false, 4500,//스컬 메일
	ITEM_HEART, false, false, 6000,//황금세공 갑옷
	ITEM_HEART, false, false, 7500,//미스릴 아머
	ITEM_HEART, false, false, 9000,//고대의 갑옷 
	ITEM_HEART, false, false, 11000, //용비늘 갑옷

	//ITEM_VEST
	ITEM_HEART, false, false, 100, //카우보이 조끼//TEXT_ITEMNAME_VEST
	ITEM_HEART, false, false, 1200, //실크 조끼
	ITEM_HEART, false, false, 2500, //방랑자의 조끼
	ITEM_HEART, false, false, 3800, //도적의 조끼
	ITEM_HEART, false, false, 6000, //벨벳 셔츠
	ITEM_HEART, false, false, 8500, //귀족의 조끼
	ITEM_HEART, false, false, 1000, //진홍빛 셔츠
	ITEM_HEART, false, false, 1000, //신관의 로브

	//ITEM_COAT
	ITEM_HEART, false, false, 1000, //수수한 코트//TEXT_ITEMNAME_COAT
	ITEM_HEART, false, false, 1000, //패딩 아머
	ITEM_HEART, false, false, 1000, //털가죽 코트
	ITEM_HEART, false, false, 1000, //큐어 보일
	ITEM_HEART, false, false, 1000, //귀족의 코트
	ITEM_HEART, false, false, 1000, //극지의 코트
	ITEM_HEART, false, false, 1000, //윙 코트
	ITEM_HEART, false, false, 1000, //바이스 코트

	//ITEM_GUNTLET
	ITEM_HEART, false, false, 100, //핸드 가드
	ITEM_HEART, false, false, 1200, //청동 장갑
	ITEM_HEART, false, false, 2000, //체인 건틀렛
	ITEM_HEART, false, false, 2700, //나이트 글로브
	ITEM_HEART, false, false, 3500, //비스트 핸드
	ITEM_HEART, false, false, 4500, //라이징 건틀렛
	ITEM_HEART, false, false, 6000, //광전사의 장갑
	ITEM_HEART, false, false, 7500, //드래곤 핸드

	//ITEM_ARMLET
	ITEM_HEART, false, false, 100,//사제의 묵주//TEXT_ITEMNAME_ARMLET
	ITEM_HEART, false, false, 1500, //여행자의 팔찌
	ITEM_HEART, false, false, 4000,//백금 브레스렛
	ITEM_HEART, false, false, 6500,//전사의 암렛
	ITEM_HEART, false, false, 9000,//에메랄드 팔찌
	ITEM_HEART, false, false, 13000,//이블 암렛
	ITEM_HEART, false, false, 18000,//위엄의 팔찌
	ITEM_HEART, false, false, 23000,//영웅의 팔찌

	//ITEM_GLOVE
	ITEM_HEART, false, false, 1000, //여행자의 장갑//TEXT_ITEMNAME_GLOVE
	ITEM_HEART, false, false, 1000, //이중매듭 장갑
	ITEM_HEART, false, false, 1000, //소매치기 장갑
	ITEM_HEART, false, false, 1000, //실크 글로브
	ITEM_HEART, false, false, 1000, //세공사의 장갑
	ITEM_HEART, false, false, 1000, //마법문양 장갑
	ITEM_HEART, false, false, 1000, //심판의 손
	ITEM_HEART, false, false, 1000, //성자의 장갑

	//ITEM_KILT
	ITEM_HEART, false, false, 100,//밴딩 킬트
	ITEM_HEART, false, false, 1200, //체인 킬트
	ITEM_HEART, false, false, 2000,//나이트 킬트
	ITEM_HEART, false, false, 2700,//스컬 킬트
	ITEM_HEART, false, false, 3500,//수령의 바지
	ITEM_HEART, false, false, 4500,//미스릴 킬트
	ITEM_HEART, false, false, 6000,//에인션트 킬트
	ITEM_HEART, false, false, 7500,//용수염 킬트

	//ITEM_SKIRT
	ITEM_HEART, false, false, 1000, //양단 스커트//TEXT_ITEMNAME_SKIRT
	ITEM_HEART, false, false, 1000, //빈티지 스커트
	ITEM_HEART, false, false, 1000, //단풍염색 치마
	ITEM_HEART, false, false, 1000, //벨벳 스커트
	ITEM_HEART, false, false, 1000, //폭풍의 스커트
	ITEM_HEART, false, false, 1000, //금실의 치마
	ITEM_HEART, false, false, 1000, //영광의 치마
	ITEM_HEART, false, false, 1000, //사제의 스커트

	//ITEM_PANTS
	ITEM_HEART, false, false, 1000, //승마용 바지//TEXT_ITEMNAME_PANTS
	ITEM_HEART, false, false, 1000, //카프스킨 팬츠
	ITEM_HEART, false, false, 1000, //망령의 팬츠
	ITEM_HEART, false, false, 1000, //흑단의 바지
	ITEM_HEART, false, false, 1000, //세일러 팬츠
	ITEM_HEART, false, false, 1000, //데저트 팬츠
	ITEM_HEART, false, false, 1000, //카오틱 팬츠
	ITEM_HEART, false, false, 1000, //가디안 팬츠

	//ITEM_GREAVES
	ITEM_HEART, false, false, 100,//코퍼 그리브
	ITEM_HEART, false, false, 1200, //밴디트 그리브
	ITEM_HEART, false, false, 2000,//체인 그리브
	ITEM_HEART, false, false, 2700,//프로즌 그리브
	ITEM_HEART, false, false, 3500,//플레이트 부츠
	ITEM_HEART, false, false, 4500,//빅풋 그리브
	ITEM_HEART, false, false, 6000,//마검사의 신발
	ITEM_HEART, false, false, 7500,//드래곤 그리브

	//ITEM_SHOES
	ITEM_HEART, false, false, 1000, //웨스턴 슈즈//TEXT_ITEMNAME_SHOES
	ITEM_HEART, false, false, 1000, //스웨이드 슈즈
	ITEM_HEART, false, false, 1000, //라이딩 슈즈
	ITEM_HEART, false, false, 1000, //칠흑의 슈즈
	ITEM_HEART, false, false, 1000, //귀부인의 신발
	ITEM_HEART, false, false, 1000, //리치 슈즈
	ITEM_HEART, false, false, 1000, //프리즘 슈즈
	ITEM_HEART, false, false, 1000, //베이그란트

	//ITEM_BOOTS
	ITEM_HEART, false, false, 1000, //스니커즈//TEXT_ITEMNAME_BOOTS
	ITEM_HEART, false, false, 1000, //스캐빈저 부츠
	ITEM_HEART, false, false, 1000, //천둥가죽 신발
	ITEM_HEART, false, false, 1000, //가드너 부츠
	ITEM_HEART, false, false, 1000, //세일러 부츠
	ITEM_HEART, false, false, 1000, //저승의 신발
	ITEM_HEART, false, false, 1000, //엘레멘탈 부츠
	ITEM_HEART, false, false, 1000, //에어워커

};
const int upgradeCostCrew[6][2 * 14] = {
	//1스타
	{
		1, 50,//0
		2, 100,//1
		4, 300,//2
		10, 1000,//3
		20, 3000,//4
		50, 8000,//5
		100, 16000,//6
		200, 40000,//7
		400, 80000,//8
		800, 160000,//9
		1000, 400000,//10
		2000, 1000000,//11
		5000, 2000000,//12
		10000, 5000000,//13
	},
	//2스타
	{
		1, 100,//0
		2, 400,//1
		4, 1000,//2
		10, 3000,//3
		20, 8000,//4
		50, 16000,//5
		100, 40000,//6
		200, 80000,//7
		400, 160000,//8
		800, 400000,//9
		1000, 1000000,//10
		2000, 2000000,//11
		0, 0,//12
		0, 0,//13
	},
	//3스타
	{
		1, 1000,//0
		2, 3000,//1
		4, 8000,//2
		10, 16000,//3
		20, 40000,//4
		50, 80000,//5
		100, 160000,//6
		200, 400000,//7
		400, 1000000,//8
		800, 2000000,//9
		0, 0,//10
		0, 0,//11
		0, 0,//12
		0, 0,//13
	},
	//4스타
	{
		1, 8000,//0
		2, 16000,//1
		4, 40000,//2
		10, 80000,//3
		20, 160000,//4
		50, 400000,//5
		100, 1000000,//6
		200, 2000000,//7
		0, 0,//8
		0, 0,//9
		0, 0,//10
		0, 0,//11
		0, 0,//12
		0, 0,//13
	},
	//5스타
	{
		1, 40000,//0
		2, 80000,//1
		4, 160000,//2
		10, 400000,//3
		20, 1000000,//4
		50, 2000000,//5
		0, 0,//6
		0, 0,//7
		0, 0,//8
		0, 0,//9
		0, 0,//10
		0, 0,//11
		0, 0,//12
		0, 0,//13
	},
	//6스타
	{
		1, 160000,//0
		2, 400000,//1
		4, 1000000,//2
		10, 2000000,//3
		20, 5000000,//4
		0, 0,//5
		0, 0,//6
		0, 0,//7
		0, 0,//8
		0, 0,//9
		0, 0,//10
		0, 0,//11
		0, 0,//12
		0, 0,//13
	},
};
const int upgradeCostEquip[6][2 * 14] = {
	//1스타
	{
		0, 0,//0
		2, 100,//1
		4, 300,//2
		10, 1000,//3
		20, 3000,//4
		50, 8000,//5
		100, 16000,//6
		200, 40000,//7
		400, 80000,//8
		800, 160000,//9
		1000, 400000,//10
		2000, 1000000,//11
		5000, 2000000,//12
		10000, 5000000,//13
	},
	//2스타
	{
		0, 0,//0
		2, 400,//1
		4, 1000,//2
		10, 3000,//3
		20, 8000,//4
		50, 16000,//5
		100, 40000,//6
		200, 80000,//7
		400, 160000,//8
		800, 400000,//9
		1000, 1000000,//10
		2000, 2000000,//11
		0, 0,//12
		0, 0,//13
	},
	//3스타
	{
		0, 0,//0
		2, 3000,//1
		4, 8000,//2
		10, 16000,//3
		20, 40000,//4
		50, 80000,//5
		100, 160000,//6
		200, 400000,//7
		400, 1000000,//8
		800, 2000000,//9
		0, 0,//10
		0, 0,//11
		0, 0,//12
		0, 0,//13
	},
	//4스타
	{
		0, 0,//0
		2, 16000,//1
		4, 40000,//2
		10, 80000,//3
		20, 160000,//4
		50, 400000,//5
		100, 1000000,//6
		200, 2000000,//7
		0, 0,//8
		0, 0,//9
		0, 0,//10
		0, 0,//11
		0, 0,//12
		0, 0,//13
	},
	//5스타
	{
		0, 0,//0
		2, 80000,//1
		4, 160000,//2
		10, 400000,//3
		20, 1000000,//4
		50, 2000000,//5
		0, 0,//6
		0, 0,//7
		0, 0,//8
		0, 0,//9
		0, 0,//10
		0, 0,//11
		0, 0,//12
		0, 0,//13
	},
	//6스타
	{
		0, 0,//0
		2, 400000,//1
		4, 1000000,//2
		10, 2000000,//3
		20, 5000000,//4
		0, 0,//5
		0, 0,//6
		0, 0,//7
		0, 0,//8
		0, 0,//9
		0, 0,//10
		0, 0,//11
		0, 0,//12
		0, 0,//13
	},
};

//게임이 읽는 포인터. 처음에는 내장 기본값을 가리키고, 부팅 때
//팩을 읽으면 그쪽으로 옮겨간다. const는 가리키는 대상에 붙으므로
//게임 코드는 대상을 못 건드리고, 로더만 자기 버퍼를 채워 넘긴다.

const unsigned short* itemTypeCnt = itemTypeCnt_builtin;
const int* swordInfoList = swordInfoList_builtin;
const signed short* newCardEffect = newCardEffect_builtin;
const int* equipDataType = equipDataType_builtin;
const unsigned short* openedItemData = openedItemData_builtin;
const unsigned char* itemLevelLimit = itemLevelLimit_builtin;
const int* itemExpAcce = itemExpAcce_builtin;
const int* itemExp = itemExp_builtin;
const int* itemMaterialExpAcce = itemMaterialExpAcce_builtin;
const int* itemMaterialExp = itemMaterialExp_builtin;
const long long* itemEvolutionItem = itemEvolutionItem_builtin;
const long long* itemUpgradeHammer = itemUpgradeHammer_builtin;
const unsigned short* arenaFloorGold = arenaFloorGold_builtin;
const unsigned short* revolutionMedal = revolutionMedal_builtin;
const unsigned int* itemColor = itemColor_builtin;
const unsigned int* buffBlend = buffBlend_builtin;
const unsigned char* swordMaxBet = swordMaxBet_builtin;
const unsigned char* swordHeart = swordHeart_builtin;
const long long* swordGold = swordGold_builtin;
const unsigned long long* itemPrice = itemPrice_builtin;
const unsigned int* itemSellPrice = itemSellPrice_builtin;
const unsigned short* itemStar = itemStar_builtin;
const unsigned short* itemStartCnt = itemStartCnt_builtin;
const unsigned char* boxEquipType = boxEquipType_builtin;
const unsigned char* materialDropData = materialDropData_builtin;
const unsigned char* wasteDropData = wasteDropData_builtin;
const int* itemValueType = itemValueType_builtin;
const int* itemValueTypeText = itemValueTypeText_builtin;
const unsigned char* itemEquipSlot = itemEquipSlot_builtin;
const unsigned char* itemSlotEquip = itemSlotEquip_builtin;
const unsigned char* wasteDrop = wasteDrop_builtin;
const unsigned char* wasteValue = wasteValue_builtin;
const unsigned char* weaponRange = weaponRange_builtin;
const unsigned int* itemValue = itemValue_builtin;
const unsigned char* gradeRatio = gradeRatio_builtin;
const unsigned char* typeRatio = typeRatio_builtin;
const unsigned char* acceOptionStatMatch = acceOptionStatMatch_builtin;
const unsigned int* acceDefaultStatValue = acceDefaultStatValue_builtin;
const unsigned int* neckOptionStatValue = neckOptionStatValue_builtin;
const unsigned int* ringOptionStatValue = ringOptionStatValue_builtin;
const unsigned int* gemOptionStatValue = gemOptionStatValue_builtin;
const unsigned int* itemUpgradeValue = itemUpgradeValue_builtin;
const unsigned char* itemRatio = itemRatio_builtin;
const unsigned short* itemPow = itemPow_builtin;
const unsigned char* itemLv = itemLv_builtin;
const unsigned char* itemStat = itemStat_builtin;
const unsigned int* enchantData = enchantData_builtin;
const unsigned char* itemCooltime = itemCooltime_builtin;
const unsigned short* itemIconTable = itemIconTable_builtin;
const unsigned int* neckOption = neckOption_builtin;
const signed int* neckRingDefaultValue = neckRingDefaultValue_builtin;
const signed char* ringOption = ringOption_builtin;
const int* optionRange = optionRange_builtin;
const signed char* optionValue = optionValue_builtin;
const unsigned char* setItem = setItem_builtin;
const int* setOption = setOption_builtin;
const unsigned int* legendItem = legendItem_builtin;
const signed char* optionStat = optionStat_builtin;
const signed char* option_prefix = option_prefix_builtin;
const signed char* option_suffix = option_suffix_builtin;
const unsigned char* option_count_prefix = option_count_prefix_builtin;
const unsigned char* option_count_suffix = option_count_suffix_builtin;
const unsigned char* gemOption = gemOption_builtin;
const int* gemPrice = gemPrice_builtin;
const int* enchantRate = enchantRate_builtin;
const unsigned char* extraSetItem = extraSetItem_builtin;
const signed int* newItemReward = newItemReward_builtin;
