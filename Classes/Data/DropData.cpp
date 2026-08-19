//이 파일은 DropData.h 에 있던 배열 정의를 옮겨 담은 것이다.
//
//헤더에 const로 정의하면 내부 링크라 포함하는 .cpp마다 복제되고,
//무엇보다 런타임에 채울 수가 없다. 정의는 여기 한 곳에만 둔다.
//
//자기 헤더만 가져온다. Data.h를 통째로 끌면 UIData.h의 std::string
//때문에 cocos2d.h가 필요해지고, 그러면 팩 생성기가 이 파일만 따로
//컴파일할 수 없다.
//
//tools/content/datafiles.py 가 갈랐다.

#include "DropData.h"
#include "../Def.h"
#include "../Cmf.h"

const int boxDropProc[TOTAL_BOX][TOTAL_BOXDROP] = {
	//BOX_INGAME
	{
		1700,//BOXDROP_COIN = 0
		2000,//BOXDROP_COINBAG
		2700,//BOXDROP_QUESTITEM
		2900,//BOXDROP_QUESTITEMBAG
		3000,//BOXDROP_HEART,
		6500,//BOXDROP_EQUIP,
		8300,//BOXDROP_BATTLE,
		10000,//BOXDROP_RAID,
	},
	//BOX_EQUIP_WOOD
	{
		1700,//BOXDROP_COIN = 0
		2000,//BOXDROP_COINBAG
		2700,//BOXDROP_QUESTITEM
		2900,//BOXDROP_QUESTITEMBAG
		3000,//BOXDROP_HEART,
		6500,//BOXDROP_EQUIP,
		8300,//BOXDROP_BATTLE,
		10000,//BOXDROP_RAID,
	},
	//BOX_EQUIP_SILVER
	{
		1700,//BOXDROP_COIN = 0
		2000,//BOXDROP_COINBAG
		2700,//BOXDROP_QUESTITEM
		2900,//BOXDROP_QUESTITEMBAG
		3000,//BOXDROP_HEART,
		6500,//BOXDROP_EQUIP,
		8300,//BOXDROP_BATTLE,
		10000,//BOXDROP_RAID,
	},
	//BOX_EQUIP_GOLD
	{
		1700,//BOXDROP_COIN = 0
		2000,//BOXDROP_COINBAG
		2700,//BOXDROP_QUESTITEM
		2900,//BOXDROP_QUESTITEMBAG
		3000,//BOXDROP_HEART,
		6500,//BOXDROP_EQUIP,
		8300,//BOXDROP_BATTLE,
		10000,//BOXDROP_RAID,
	},
	//BOX_EQUIP_MAGIC
	{
		1700,//BOXDROP_COIN = 0
		2000,//BOXDROP_COINBAG
		2700,//BOXDROP_QUESTITEM
		2900,//BOXDROP_QUESTITEMBAG
		3000,//BOXDROP_HEART,
		6500,//BOXDROP_EQUIP,
		8300,//BOXDROP_BATTLE,
		10000,//BOXDROP_RAID,
	},
	//BOX_EQUIP_HERO
	{
		1700,//BOXDROP_COIN = 0
		2000,//BOXDROP_COINBAG
		2700,//BOXDROP_QUESTITEM
		2900,//BOXDROP_QUESTITEMBAG
		3000,//BOXDROP_HEART,
		6500,//BOXDROP_EQUIP,
		8300,//BOXDROP_BATTLE,
		10000,//BOXDROP_RAID,
	},
	//BOX_EQUIP_LEGEND
	{
		1700,//BOXDROP_COIN = 0
		2000,//BOXDROP_COINBAG
		2700,//BOXDROP_QUESTITEM
		2900,//BOXDROP_QUESTITEMBAG
		3000,//BOXDROP_HEART,
		6500,//BOXDROP_EQUIP,
		8300,//BOXDROP_BATTLE,
		10000,//BOXDROP_RAID,
	},
	//BOX_CREW_SEBASTIAN
	{
		1700,//BOXDROP_COIN = 0
		2000,//BOXDROP_COINBAG
		2700,//BOXDROP_QUESTITEM
		2900,//BOXDROP_QUESTITEMBAG
		3000,//BOXDROP_HEART,
		6500,//BOXDROP_EQUIP,
		8300,//BOXDROP_BATTLE,
		10000,//BOXDROP_RAID,
	},
	//BOX_CREW_PRINCESS
	{
		1700,//BOXDROP_COIN = 0
		2000,//BOXDROP_COINBAG
		2700,//BOXDROP_QUESTITEM
		2900,//BOXDROP_QUESTITEMBAG
		3000,//BOXDROP_HEART,
		6500,//BOXDROP_EQUIP,
		8300,//BOXDROP_BATTLE,
		10000,//BOXDROP_RAID,
	},
	//BOX_CREW_KING
	{
		1700,//BOXDROP_COIN = 0
		2000,//BOXDROP_COINBAG
		2700,//BOXDROP_QUESTITEM
		2900,//BOXDROP_QUESTITEMBAG
		3000,//BOXDROP_HEART,
		6500,//BOXDROP_EQUIP,
		8300,//BOXDROP_BATTLE,
		10000,//BOXDROP_RAID,
	},
	//BOX_CREW_DEVIL
	{
		1700,//BOXDROP_COIN = 0
		2000,//BOXDROP_COINBAG
		2700,//BOXDROP_QUESTITEM
		2900,//BOXDROP_QUESTITEMBAG
		3000,//BOXDROP_HEART,
		6500,//BOXDROP_EQUIP,
		8300,//BOXDROP_BATTLE,
		10000,//BOXDROP_RAID,
	},
	//BOX_ATTR_FIRE
	{
		1700,//BOXDROP_COIN = 0
		2000,//BOXDROP_COINBAG
		2700,//BOXDROP_QUESTITEM
		2900,//BOXDROP_QUESTITEMBAG
		3000,//BOXDROP_HEART,
		6500,//BOXDROP_EQUIP,
		8300,//BOXDROP_BATTLE,
		10000,//BOXDROP_RAID,
	},
	//BOX_ATTR_FROST
	{
		1700,//BOXDROP_COIN = 0
		2000,//BOXDROP_COINBAG
		2700,//BOXDROP_QUESTITEM
		2900,//BOXDROP_QUESTITEMBAG
		3000,//BOXDROP_HEART,
		6500,//BOXDROP_EQUIP,
		8300,//BOXDROP_BATTLE,
		10000,//BOXDROP_RAID,
	},
	//BOX_ATTR_EARTH
	{
		1700,//BOXDROP_COIN = 0
		2000,//BOXDROP_COINBAG
		2700,//BOXDROP_QUESTITEM
		2900,//BOXDROP_QUESTITEMBAG
		3000,//BOXDROP_HEART,
		6500,//BOXDROP_EQUIP,
		8300,//BOXDROP_BATTLE,
		10000,//BOXDROP_RAID,
	},
	//BOX_ATTR_THUNDER
	{
		1700,//BOXDROP_COIN = 0
		2000,//BOXDROP_COINBAG
		2700,//BOXDROP_QUESTITEM
		2900,//BOXDROP_QUESTITEMBAG
		3000,//BOXDROP_HEART,
		6500,//BOXDROP_EQUIP,
		8300,//BOXDROP_BATTLE,
		10000,//BOXDROP_RAID,
	},
	//BOX_ATTR_LIGHT
	{
		1700,//BOXDROP_COIN = 0
		2000,//BOXDROP_COINBAG
		2700,//BOXDROP_QUESTITEM
		2900,//BOXDROP_QUESTITEMBAG
		3000,//BOXDROP_HEART,
		6500,//BOXDROP_EQUIP,
		8300,//BOXDROP_BATTLE,
		10000,//BOXDROP_RAID,
	},
	//BOX_ATTR_DARK
	{
		1700,//BOXDROP_COIN = 0
		2000,//BOXDROP_COINBAG
		2700,//BOXDROP_QUESTITEM
		2900,//BOXDROP_QUESTITEMBAG
		3000,//BOXDROP_HEART,
		6500,//BOXDROP_EQUIP,
		8300,//BOXDROP_BATTLE,
		10000,//BOXDROP_RAID,
	},
};
static const unsigned short proc1_builtin[] = {
	7000,
	10000
};
static const unsigned short proc2_builtin[] = {
	6000,
	8800,
	10000
};
static const unsigned short proc3_builtin[] = {
	5000,
	7500,
	9200,
	10000
};
static const unsigned short proc4_builtin[] = {
	4500,
	7000,
	8500,
	9500,
	10000
};
static const unsigned short proc5_builtin[] = {
	4000,
	6500,
	8000,
	9000,
	9600,
	10000
};
static const unsigned short proc6_builtin[] = {
	2600,
	4800,
	6600,
	8000,
	9000,
	9600,
	10000
};
static const unsigned short proc7_builtin[] = {
	2200,
	4200,
	5900,
	7300,
	8400,
	9200,
	9700,
	10000,

};
static const unsigned short proc8_builtin[] = {
	2000,
	3700,
	5200,
	6500,
	7600,
	8500,
	9200,
	9700,
	10000,

};
static const unsigned short proc9_builtin[] = {
	1900,
	3600,
	5100,
	6400,
	7400,
	8300,
	9000,
	9500,
	9800,
	10000,

};
static const unsigned short proc10_builtin[] = {
	2000,
	3600,
	5000,
	6200,
	7200,
	8000,
	8600,
	9100,
	9500,
	9800,
	10000

};
static const unsigned short proc11_builtin[] = {
	1700,
	3200,
	4500,
	5600,
	6500,
	7300,
	8000,
	8600,
	9100,
	9500,
	9800,
	10000,

};
static const unsigned short proc12_builtin[] = {
	1800,
	3300,
	4500,
	5500,
	6400,
	7200,
	7900,
	8500,
	9000,
	9400,
	9700,
	9900,
	10000

};
static const unsigned short proc13_builtin[] = {
	1200,
	2350,
	3450,
	4500,
	5500,
	6400,
	7200,
	7900,
	8500,
	9000,
	9400,
	9700,
	9900,
	10000

};
static const unsigned short proc14_builtin[] = {
	1200,
	2300,
	3250,
	4150,
	5000,
	5800,
	6550,
	7250,
	7900,
	8500,
	9000,
	9400,
	9700,
	9900,
	10000

};
static const unsigned short proc15_builtin[] = {
	1150,
	2200,
	3150,
	4000,
	4800,
	5550,
	6250,
	6900,
	7500,
	8050,
	8550,
	9000,
	9400,
	9700,
	9900,
	10000

};
static const unsigned short proc16_builtin[] = {
	1000,
	1950,
	2850,
	3700,
	4500,
	5250,
	5950,
	6600,
	7200,
	7750,
	8250,
	8700,
	9100,
	9450,
	9750,
	9900,
	10000

};
static const unsigned short proc17_builtin[] = {
	1000,
	1950,
	2850,
	3700,
	4500,
	5250,
	5950,
	6600,
	7200,
	7750,
	8250,
	8650,
	9000,
	9300,
	9550,
	9750,
	9900,
	10000,

};
static const unsigned short proc18_builtin[] = {
	1000,
	1950,
	2850,
	3700,
	4500,
	5250,
	5950,
	6600,
	7200,
	7750,
	8200,
	8600,
	8950,
	9250,
	9500,
	9700,
	9850,
	9950,
	10000

};
static const unsigned short proc19_builtin[] = {
	930,
	1810,
	2630,
	3410,
	4150,
	4850,
	5510,
	6130,
	6710,
	7250,
	7750,
	8200,
	8600,
	8950,
	9250,
	9500,
	9700,
	9850,
	9950,
	10000

};
static const unsigned short proc20_builtin[] = {
	870,
	1700,
	2500,
	3260,
	3980,
	4660,
	5300,
	5900,
	6460,
	6980,
	7460,
	7900,
	8300,
	8660,
	8980,
	9260,
	9500,
	9700,
	9850,
	9950,
	10000

};
static const unsigned short proc21_builtin[] = {
	850,
	1660,
	2430,
	3170,
	3880,
	4560,
	5200,
	5800,
	6360,
	6880,
	7360,
	7800,
	8200,
	8560,
	8880,
	9160,
	9400,
	9600,
	9760,
	9880,
	9960,
	10000

};
static const unsigned short proc22_builtin[] = {
	790,
	1540,
	2260,
	2950,
	3610,
	4240,
	4840,
	5410,
	5950,
	6460,
	6940,
	7390,
	7810,
	8200,
	8560,
	8880,
	9160,
	9400,
	9600,
	9760,
	9880,
	9960,
	10000

};
static const unsigned short proc23_builtin[] = {
	750,
	1470,
	2170,
	2850,
	3500,
	4120,
	4710,
	5270,
	5800,
	6300,
	6770,
	7210,
	7620,
	8000,
	8350,
	8670,
	8960,
	9220,
	9450,
	9640,
	9790,
	9900,
	9970,
	10000

};
static const unsigned short proc24_builtin[] = {
	770,
	1500,
	2200,
	2870,
	3510,
	4120,
	4700,
	5250,
	5770,
	6260,
	6720,
	7150,
	7550,
	7920,
	8260,
	8570,
	8850,
	9100,
	9320,
	9510,
	9670,
	9800,
	9900,
	9970,
	10000

};
static const unsigned short proc25_builtin[] = {
	710,
	1390,
	2050,
	2690,
	3310,
	3910,
	4490,
	5050,
	5580,
	6080,
	6550,
	6990,
	7400,
	7780,
	8130,
	8450,
	8740,
	9000,
	9230,
	9430,
	9600,
	9740,
	9850,
	9930,
	9980,
	10000

};
static const unsigned short proc26_builtin[] = {
	650,
	1280,
	1900,
	2500,
	3080,
	3640,
	4180,
	4700,
	5200,
	5680,
	6140,
	6580,
	7000,
	7400,
	7780,
	8130,
	8450,
	8740,
	9000,
	9230,
	9430,
	9600,
	9740,
	9850,
	9930,
	9980,
	10000

};
static const unsigned short proc27_builtin[] = {
	640,
	1260,
	1860,
	2440,
	3000,
	3540,
	4060,
	4560,
	5040,
	5500,
	5940,
	6360,
	6760,
	7140,
	7500,
	7840,
	8160,
	8460,
	8740,
	9000,
	9230,
	9430,
	9600,
	9740,
	9850,
	9930,
	9980,
	10000

};
static const unsigned short proc28_builtin[] = {
	630,
	1240,
	1830,
	2400,
	2950,
	3480,
	3990,
	4480,
	4950,
	5400,
	5830,
	6240,
	6630,
	7000,
	7350,
	7680,
	7990,
	8280,
	8550,
	8800,
	9030,
	9240,
	9430,
	9600,
	9740,
	9850,
	9930,
	9980,
	10000

};
static const unsigned short proc29_builtin[] = {
	660,
	1290,
	1900,
	2480,
	3030,
	3550,
	4050,
	4530,
	4990,
	5430,
	5850,
	6250,
	6630,
	6990,
	7330,
	7650,
	7950,
	8230,
	8490,
	8730,
	8950,
	9150,
	9330,
	9490,
	9630,
	9750,
	9850,
	9930,
	9980,
	10000

};
static const unsigned short proc30_builtin[] = {
	660,
	1290,
	1880,
	2440,
	2980,
	3500,
	4000,
	4480,
	4940,
	5380,
	5800,
	6200,
	6580,
	6940,
	7280,
	7600,
	7900,
	8180,
	8440,
	8680,
	8900,
	9100,
	9280,
	9440,
	9580,
	9700,
	9800,
	9880,
	9940,
	9980,
	10000

};
static const unsigned short proc31_builtin[] = {
	590,
	1150,
	1690,
	2220,
	2740,
	3250,
	3750,
	4240,
	4710,
	5160,
	5590,
	6000,
	6390,
	6760,
	7110,
	7440,
	7750,
	8040,
	8310,
	8560,
	8790,
	9000,
	9190,
	9360,
	9510,
	9640,
	9750,
	9840,
	9910,
	9960,
	9990,
	10000

};
static const unsigned short proc32_builtin[] = {
	530,
	1050,
	1550,
	2040,
	2520,
	2990,
	3450,
	3900,
	4340,
	4770,
	5190,
	5600,
	6000,
	6390,
	6760,
	7110,
	7440,
	7750,
	8040,
	8310,
	8560,
	8790,
	9000,
	9190,
	9360,
	9510,
	9640,
	9750,
	9840,
	9910,
	9960,
	9990,
	10000

};
static const unsigned short proc33_builtin[] = {
	500,
	990,
	1470,
	1940,
	2400,
	2850,
	3290,
	3720,
	4140,
	4550,
	4950,
	5340,
	5720,
	6090,
	6450,
	6790,
	7120,
	7440,
	7750,
	8040,
	8310,
	8560,
	8790,
	9000,
	9190,
	9360,
	9510,
	9640,
	9750,
	9840,
	9910,
	9960,
	9990,
	10000

};
static const unsigned short proc34_builtin[] = {
	490,
	970,
	1440,
	1900,
	2350,
	2790,
	3210,
	3620,
	4020,
	4410,
	4790,
	5160,
	5520,
	5870,
	6210,
	6540,
	6860,
	7170,
	7470,
	7760,
	8040,
	8310,
	8560,
	8790,
	9000,
	9190,
	9360,
	9510,
	9640,
	9750,
	9840,
	9910,
	9960,
	9990,
	10000

};

//게임이 읽는 포인터. 처음에는 내장 기본값을 가리키고, 부팅 때
//팩을 읽으면 그쪽으로 옮겨간다. const는 가리키는 대상에 붙으므로
//게임 코드는 대상을 못 건드리고, 로더만 자기 버퍼를 채워 넘긴다.

const unsigned short* proc1 = proc1_builtin;
const unsigned short* proc2 = proc2_builtin;
const unsigned short* proc3 = proc3_builtin;
const unsigned short* proc4 = proc4_builtin;
const unsigned short* proc5 = proc5_builtin;
const unsigned short* proc6 = proc6_builtin;
const unsigned short* proc7 = proc7_builtin;
const unsigned short* proc8 = proc8_builtin;
const unsigned short* proc9 = proc9_builtin;
const unsigned short* proc10 = proc10_builtin;
const unsigned short* proc11 = proc11_builtin;
const unsigned short* proc12 = proc12_builtin;
const unsigned short* proc13 = proc13_builtin;
const unsigned short* proc14 = proc14_builtin;
const unsigned short* proc15 = proc15_builtin;
const unsigned short* proc16 = proc16_builtin;
const unsigned short* proc17 = proc17_builtin;
const unsigned short* proc18 = proc18_builtin;
const unsigned short* proc19 = proc19_builtin;
const unsigned short* proc20 = proc20_builtin;
const unsigned short* proc21 = proc21_builtin;
const unsigned short* proc22 = proc22_builtin;
const unsigned short* proc23 = proc23_builtin;
const unsigned short* proc24 = proc24_builtin;
const unsigned short* proc25 = proc25_builtin;
const unsigned short* proc26 = proc26_builtin;
const unsigned short* proc27 = proc27_builtin;
const unsigned short* proc28 = proc28_builtin;
const unsigned short* proc29 = proc29_builtin;
const unsigned short* proc30 = proc30_builtin;
const unsigned short* proc31 = proc31_builtin;
const unsigned short* proc32 = proc32_builtin;
const unsigned short* proc33 = proc33_builtin;
const unsigned short* proc34 = proc34_builtin;
