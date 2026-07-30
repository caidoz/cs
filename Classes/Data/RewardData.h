#pragma once
#include "../Def.h"

#ifndef _DATA_REWARD_H_
#define _DATA_REWARD_H_

// 전투 및 레이드 보상 데이터
const int battleRewardMedal[] = {
#ifdef BATTLEABSOLUTE
	2,  //꽝
	3,  //굳
#else
	2,  //꽝
	3,  //굳
	4,  //그레이트
	6,  //퍼펙트
#endif
};

// 스테이지별 전투 보상 골드
const long long battleRewardGold[] = {
	1000,
	1200,
	1400,
	1600,
	1800,
	2000,
	2200,
	2400,
	2800,
	3000,
	3400,
	3800,
	4200,
	4600,
	5200,
	5800,
	6400,
	7000,
	7800,
	8600,
	10000,
	11000,
	13000,
	15000,
	17000,
	19000,
	21000,
	24000,
	27000,
	30000,
	33000,
	37000,
	41000,
	46000,
	51000,
	28500,
	31500,
	35000,
	38500,
	42500,
	50000,
	55000,
	65000,
	75000,
	85000,
	95000,
	105000,
	120000,
	135000,
	150000,
	165000,
	185000,
	205000,
	230000,
	255000,
	285000,
	315000,
	350000,
	385000,
	425000,
	500000,
	550000,
	650000,
	750000,
	850000,
	950000,
	10500000,
	12000000,
	13500000,
	15000000,
	16500000,
	18500000,
	20500000,
	23000000,
	25500000,
	28500000,
	31500000,
	35000000,
	38500000,
	42500000,
};

// 스테이지별 보스 레이드 골드
const long long bossGold[] = {
	10000 * 3,
	11000 * 3,
	13000 * 3,
	15000 * 3,
	17000 * 3,
	19000 * 3,
	21000 * 3,
	24000 * 3,
	27000 * 3,
	30000 * 3,
	33000 * 3,
	37000 * 3,
	41000 * 3,
	46000 * 3,
	51000 * 3,
	57000 * 3,
	63000 * 3,
	70000 * 3,
	77000 * 3,
	85000 * 3,
	100000 * 3,
	110000 * 3,
	130000 * 3,
	150000 * 3,
	170000 * 3,
	190000 * 3,
	210000 * 3,
	240000 * 3,
	270000 * 3,
	300000 * 3,
	330000 * 3,
	370000 * 3,
	410000 * 3,
	460000 * 3,
	510000 * 3,
	570000 * 3,
	630000 * 3,
	700000 * 3,
	770000 * 3,
	850000 * 3,
	1000000 * 3,
	1100000 * 3,
	1300000 * 3,
	1500000 * 3,
	1700000 * 3,
	1900000 * 3,
	2100000 * 3,
	2400000 * 3,
	2700000 * 3,
	3000000 * 3,
	3300000 * 3,
	3700000 * 3,
	4100000 * 3,
	4600000 * 3,
	5100000 * 3,
	5700000 * 3,
	6300000 * 3,
	7000000 * 3,
	7700000 * 3,
	8500000 * 3,
	10000000 * 3,
	11000000 * 3,
	13000000 * 3,
	15000000 * 3,
	17000000 * 3,
	19000000 * 3,
	21000000 * 3,
	24000000 * 3,
	27000000 * 3,
	30000000 * 3,
	33000000 * 3,
	37000000 * 3,
	41000000 * 3,
	46000000 * 3,
	51000000 * 3,
	57000000 * 3,
	63000000 * 3,
	70000000 * 3,
	77000000 * 3,
	85000000 * 3,
	100000000 * 3,
	110000000 * 3,
	130000000 * 3,
	150000000 * 3,
	170000000 * 3,
	190000000 * 3,
	210000000 * 3,
	240000000 * 3,
	270000000 * 3,
	300000000 * 3,
	330000000 * 3,
	370000000 * 3,
	410000000 * 3,
	460000000 * 3,
	510000000 * 3,
	570000000 * 3,
	630000000 * 3,
	700000000 * 3,
	770000000 * 3,
	850000000 * 3,
};

const int raidRewardMedal[] = {
#ifdef RAIDABSOLUTE
	3,  //굳
	4,  //그레이트
	6,  //퍼펙트
#else
	5,  //굳
	7,  //그레이트
	9,  //퍼펙트
#endif
};


const long long stageClearBox[] = {//TOTALSTAGE
	BOX_REWARD0,//1
	BOX_REWARD0,//2
	BOX_REWARD0,//3
	BOX_REWARD0,//4
	BOX_REWARD0,//5
	BOX_REWARD0,//6
	BOX_REWARD0,//7
	BOX_REWARD0,//8
	BOX_REWARD0,//9
	BOX_REWARD0,//10
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD0,//11
	BOX_REWARD1,//2
	BOX_REWARD2,//3
	BOX_REWARD3,//4
	BOX_REWARD4,//5
	BOX_REWARD5,//6

};

const int levelUpCategory[] = {
	LVUPREWARD_AUTOROLL,//1
	LVUPREWARD_COLLECTIONS,//2
	LVUPREWARD_DAILYREWARDS,//3
	LVUPREWARD_DAILYQUEST,//4
	LVUPREWARD_HEARTMAX,//5
	LVUPREWARD_HEARTPERHOUR,//6
	LVUPREWARD_SHILED,//7
	LVUPREWARD_GETHERO,//8
	LVUPREWARD_GETSKILL,//9

};

//없으면 -1로 해준다.
const signed long long levelUpReward[] = {
	LVUPREWARD_AUTOROLL, MAXLV, //1//Automatic dice rolling
	LVUPREWARD_COLLECTIONS, MAXLV, //2//Albums
	LVUPREWARD_DAILYREWARDS, MAXLV, //3//Everyday gifts
	LVUPREWARD_DAILYQUEST, MAXLV, //4//Quick wins
	LVUPREWARD_HEARTMAX, 40,//5//Number of throws

	LVUPREWARD_GETSKILL, ROBIN_SKILL_AIRCRASH,//6//Case départ
	LVUPREWARD_GETHERO, DIANA,//7//Rent targets 
	LVUPREWARD_GETSKILL, DIANA_SKILL_3WAY,//8//Closing
	LVUPREWARD_SHILED, 4,//9//Shields 
	LVUPREWARD_GETHERO, MAXX,//10//Bank robbery

	LVUPREWARD_HEARTMAX, 50,//11//Number of throws
	LVUPREWARD_GETSKILL, MAXX_SKILL_KICK,//12//Properties
	LVUPREWARD_GETSKILL, ROBIN_SKILL_STAB,//13//Chance card
	LVUPREWARD_HEARTPERHOUR, 6,//14//Throw regeneration 
	LVUPREWARD_GETSKILL, DIANA_SKILL_LASER,//15//Stickers for rewards

	LVUPREWARD_GETSKILL, MAXX_SKILL_SHORT,//16//Increase in daily gifts
	LVUPREWARD_GETSKILL, ROBIN_SKILL_BOOSTSLASH,//17//Closing 
	LVUPREWARD_HEART, 300,//18// 350 dice + Number of throws 
	LVUPREWARD_HEARTMAX, 60,//19//RENT
	LVUPREWARD_GETSKILL, DIANA_SKILL_FLAMER,//20//Rent targets

	LVUPREWARD_HEART, 400,//21//
	LVUPREWARD_HEARTMAX, 70,//22
	LVUPREWARD_HEART, 1000,//23
	LVUPREWARD_HEART, 500,//24
	LVUPREWARD_HEARTPERHOUR, 7,//25

	LVUPREWARD_GETSKILL, MAXX_SKILL_AIR,//26//Closing 
	LVUPREWARD_HEART, 500,//27//
	LVUPREWARD_HEARTMAX, 80,//28//Number of throws The maximum number of throws is increased from 70 to 80.
	LVUPREWARD_GETSKILL, ROBIN_SKILL_HYPERCHARGE,//29//Stickers for rewards
	LVUPREWARD_GETSKILL, DIANA_SKILL_BOMBSHOT,//30//Bank robbery

	LVUPREWARD_SHILED, 5,//31//Shields 
	LVUPREWARD_HEART, 500,//32
	LVUPREWARD_HEARTPERHOUR, 8,//33//hrow regeneration Generates 9 dice per hour
	LVUPREWARD_GETSKILL, MAXX_SKILL_CAMPING,//34//Chance card
	LVUPREWARD_GETSKILL, ROBIN_SKILL_SOULCRASH,//35//Properties

	LVUPREWARD_HEART, 2000,//36
	LVUPREWARD_HEARTMAX, 90,//37//Compagnie de Service Public
	LVUPREWARD_GETSKILL, DIANA_SKILL_GUIDEDSHOT,//38//Rent //Case départ : Bonus when you pass the starting square +500K
	LVUPREWARD_HEART, 3000,//39
	LVUPREWARD_HEARTPERHOUR, 9,//40

	LVUPREWARD_GETSKILL, MAXX_SKILL_HORMING,//41
	LVUPREWARD_GETSKILL, ROBIN_SKILL_ABSOLUTEPIERCE,//42
	LVUPREWARD_GETSKILL, DIANA_SKILL_SPRAYSHOT,//43
	LVUPREWARD_HEARTMAX, 100,//44
	LVUPREWARD_GETSKILL, MAXX_SKILL_CIRCLE,//45

	LVUPREWARD_GETSKILL, ROBIN_SKILL_KILLALL,//46
	LVUPREWARD_GETSKILL, DIANA_SKILL_SATELLITESHOT,//47
	LVUPREWARD_HEARTPERHOUR, 10,//48
	LVUPREWARD_GETSKILL, MAXX_SKILL_MEGA,//49
	LVUPREWARD_HEART, 5000,//50

	-1, -1,//51
	-1, -1,//52
	-1, -1,//53
	-1, -1,//54
	-1, -1,//55

	-1, -1,//56
	-1, -1,//57
	-1, -1,//58
	-1, -1,//59
	-1, -1,//60

	-1, -1,//61
	-1, -1,//62
	-1, -1,//63
	-1, -1,//64
	-1, -1,//65

	-1, -1,//66
	-1, -1,//67
	-1, -1,//68
	-1, -1,//69
	-1, -1,//70

	-1, -1,//71
	-1, -1,//72
	-1, -1,//73
	-1, -1,//74
	-1, -1,//75

	-1, -1,//76
	-1, -1,//77
	-1, -1,//78
	-1, -1,//79
	-1, -1,//80

	-1, -1,//81
	-1, -1,//82
	-1, -1,//83
	-1, -1,//84
	-1, -1,//85

	-1, -1,//86
	-1, -1,//87
	-1, -1,//88
	-1, -1,//89
	-1, -1,//90

	-1, -1,//91
	-1, -1,//92
	-1, -1,//93
	-1, -1,//94
	-1, -1,//95

	-1, -1,//96
	-1, -1,//97
	-1, -1,//98
	-1, -1,//99
	-1, -1,//100


};


//없으면 -1로 해준다.
const signed long long stageClearReward[] = {//TOTALSTAGE * BOX1MAXREWARDITEM * REWARDDATASIZE
	ITEM_SKILL, SKILL_ROBIN8, false,  1,//1
	-1, false, false, false,
	-1, false, false, false,

	ITEM_CREW, NPC_BOY, false,  1,//2
	-1, false, false, false,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//3
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//4
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//5
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//6
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//7
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//8
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//9
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//10
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//1
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//2
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//3
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//4
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//5
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//6
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//7
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//8
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//9
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//10
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//1
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//2
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//3
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//4
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//5
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//6
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//7
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//8
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//9
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false,  30,//10
	ITEM_GOLD, false, false,  1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//1
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//2
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//3
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//4
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//5
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//6
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//7
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//8
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//9
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//10
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//1
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//2
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//3
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//4
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//5
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//6
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//7
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//8
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//9
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//10
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//1
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//2
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//3
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//4
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//5
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//6
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//7
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//8
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//9
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//10
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//1
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//2
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//3
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//4
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//5
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//6
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//7
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//8
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//9
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//10
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//1
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//2
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//3
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//4
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//5
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//6
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//7
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//8
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//9
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//10
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//1
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//2
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//3
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//4
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//5
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//6
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//7
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//8
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//9
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//10
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//1
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//2
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//3
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//4
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//5
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//6
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//7
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//8
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//9
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,

	ITEM_HEART, false, false, 30,//10
	ITEM_GOLD, false, false, 1000,
	-1, false, false, false,
};

const long long equipGetRewardHeart[] = {
	//ITEM_SWORD
	100,//1
	200,//2
	300,//3
	400,//4
	500,//5
	600,//6
	700,//7
	800,//8
	900,//9
	1000,//10
	1100,//11
	1200,//12
	1300,//13
	1400,//14
	1500,//15
	1600,//16
	1700,//17
	1800,//18
	1900,//19
	2000,//20
	2100,//21
	2200,//22
	2300,//23
	2400,//24

	//ITEM_GUN
	100,//1
	200,//2
	300,//3
	400,//4
	500,//5
	600,//6
	700,//7
	800,//8
	900,//9
	1000,//10
	1100,//11
	1200,//12
	1300,//13
	1400,//14
	1500,//15
	1600,//16
	1700,//17
	1800,//18
	1900,//19
	2000,//20
	2100,//21
	2200,//22
	2300,//23
	2400,//24

	//ITEM_BOOMERANG
	100,//1
	200,//2
	300,//3
	400,//4
	500,//5
	600,//6
	700,//7
	800,//8
	900,//9
	1000,//10
	1100,//11
	1200,//12
	1300,//13
	1400,//14
	1500,//15
	1600,//16
	1700,//17
	1800,//18
	1900,//19
	2000,//20
	2100,//21
	2200,//22
	2300,//23
	2400,//24

	//ITEM_HELM
	100,//1
	200,//2
	300,//3
	400,//4
	500,//5
	600,//6
	700,//7
	800,//8
	900,//9
	1000,//10
	1100,//11
	1200,//12
	1300,//13
	1400,//14
	1500,//15
	1600,//16
	1700,//17
	1800,//18
	1900,//19
	2000,//20
	2100,//21
	2200,//22
	2300,//23
	2400,//24

	//ITEM_HAT
	100,//1
	200,//2
	300,//3
	400,//4
	500,//5
	600,//6
	700,//7
	800,//8
	900,//9
	1000,//10
	1100,//11
	1200,//12
	1300,//13
	1400,//14
	1500,//15
	1600,//16
	1700,//17
	1800,//18
	1900,//19
	2000,//20
	2100,//21
	2200,//22
	2300,//23
	2400,//24

	//ITEM_CAP
	100,//1
	200,//2
	300,//3
	400,//4
	500,//5
	600,//6
	700,//7
	800,//8
	900,//9
	1000,//10
	1100,//11
	1200,//12
	1300,//13
	1400,//14
	1500,//15
	1600,//16
	1700,//17
	1800,//18
	1900,//19
	2000,//20
	2100,//21
	2200,//22
	2300,//23
	2400,//24

	//ITEM_ARMOR
	100,//1
	200,//2
	300,//3
	400,//4
	500,//5
	600,//6
	700,//7
	800,//8
	900,//9
	1000,//10
	1100,//11
	1200,//12
	1300,//13
	1400,//14
	1500,//15
	1600,//16
	1700,//17
	1800,//18
	1900,//19
	2000,//20
	2100,//21
	2200,//22
	2300,//23
	2400,//24

	//ITEM_VEST
	100,//1
	200,//2
	300,//3
	400,//4
	500,//5
	600,//6
	700,//7
	800,//8
	900,//9
	1000,//10
	1100,//11
	1200,//12
	1300,//13
	1400,//14
	1500,//15
	1600,//16
	1700,//17
	1800,//18
	1900,//19
	2000,//20
	2100,//21
	2200,//22
	2300,//23
	2400,//24

	//ITEM_COAT
	100,//1
	200,//2
	300,//3
	400,//4
	500,//5
	600,//6
	700,//7
	800,//8
	900,//9
	1000,//10
	1100,//11
	1200,//12
	1300,//13
	1400,//14
	1500,//15
	1600,//16
	1700,//17
	1800,//18
	1900,//19
	2000,//20
	2100,//21
	2200,//22
	2300,//23
	2400,//24

	//ITEM_GUNTLET
	100,//1
	200,//2
	300,//3
	400,//4
	500,//5
	600,//6
	700,//7
	800,//8
	900,//9
	1000,//10
	1100,//11
	1200,//12
	1300,//13
	1400,//14
	1500,//15
	1600,//16
	1700,//17
	1800,//18
	1900,//19
	2000,//20
	2100,//21
	2200,//22
	2300,//23
	2400,//24

	//ITEM_ARMLET
	100,//1
	200,//2
	300,//3
	400,//4
	500,//5
	600,//6
	700,//7
	800,//8
	900,//9
	1000,//10
	1100,//11
	1200,//12
	1300,//13
	1400,//14
	1500,//15
	1600,//16
	1700,//17
	1800,//18
	1900,//19
	2000,//20
	2100,//21
	2200,//22
	2300,//23
	2400,//24

	//ITEM_GLOVE
	100,//1
	200,//2
	300,//3
	400,//4
	500,//5
	600,//6
	700,//7
	800,//8
	900,//9
	1000,//10
	1100,//11
	1200,//12
	1300,//13
	1400,//14
	1500,//15
	1600,//16
	1700,//17
	1800,//18
	1900,//19
	2000,//20
	2100,//21
	2200,//22
	2300,//23
	2400,//24

	//ITEM_KILT
	100,//1
	200,//2
	300,//3
	400,//4
	500,//5
	600,//6
	700,//7
	800,//8
	900,//9
	1000,//10
	1100,//11
	1200,//12
	1300,//13
	1400,//14
	1500,//15
	1600,//16
	1700,//17
	1800,//18
	1900,//19
	2000,//20
	2100,//21
	2200,//22
	2300,//23
	2400,//24

	//ITEM_SKIRT
	100,//1
	200,//2
	300,//3
	400,//4
	500,//5
	600,//6
	700,//7
	800,//8
	900,//9
	1000,//10
	1100,//11
	1200,//12
	1300,//13
	1400,//14
	1500,//15
	1600,//16
	1700,//17
	1800,//18
	1900,//19
	2000,//20
	2100,//21
	2200,//22
	2300,//23
	2400,//24

	//ITEM_PANTS
	100,//1
	200,//2
	300,//3
	400,//4
	500,//5
	600,//6
	700,//7
	800,//8
	900,//9
	1000,//10
	1100,//11
	1200,//12
	1300,//13
	1400,//14
	1500,//15
	1600,//16
	1700,//17
	1800,//18
	1900,//19
	2000,//20
	2100,//21
	2200,//22
	2300,//23
	2400,//24

	//ITEM_GREAVES
	100,//1
	200,//2
	300,//3
	400,//4
	500,//5
	600,//6
	700,//7
	800,//8
	900,//9
	1000,//10
	1100,//11
	1200,//12
	1300,//13
	1400,//14
	1500,//15
	1600,//16
	1700,//17
	1800,//18
	1900,//19
	2000,//20
	2100,//21
	2200,//22
	2300,//23
	2400,//24

	//ITEM_SHOES
	100,//1
	200,//2
	300,//3
	400,//4
	500,//5
	600,//6
	700,//7
	800,//8
	900,//9
	1000,//10
	1100,//11
	1200,//12
	1300,//13
	1400,//14
	1500,//15
	1600,//16
	1700,//17
	1800,//18
	1900,//19
	2000,//20
	2100,//21
	2200,//22
	2300,//23
	2400,//24

	//ITEM_BOOTS
	100,//1
	200,//2
	300,//3
	400,//4
	500,//5
	600,//6
	700,//7
	800,//8
	900,//9
	1000,//10
	1100,//11
	1200,//12
	1300,//13
	1400,//14
	1500,//15
	1600,//16
	1700,//17
	1800,//18
	1900,//19
	2000,//20
	2100,//21
	2200,//22
	2300,//23
	2400,//24

};


//0, 1, 2 : 아이템 데이터 type, detail, grade
//4, 5 : 생산량, 생산텀(second)
const unsigned long long crewReward[] = {

	//HOUSE_SWAMP
	ITEM_GOLD, false, false, 10000, 86400 * 1,//NPC_BOY
	ITEM_GOLD, false, false, 20000, 86400 * 2,//NPC_GIRL
	ITEM_BOX, BOX_REWARD0, false, 1, 86400 * 3,//ENEMY_SNAIL
	ITEM_GOLD, false, false, 50000, 86400 * 4,//NPC_GRANDFA
	ITEM_HEART, false, false, 100, 86400 * 5,//ENEMY_TREE

	//HOUSE_VALLEY
	ITEM_GOLD, false, false, 10000, 86400 * 1,//NPC_WOMAN
	ITEM_GOLD, false, false, 20000, 86400 * 2,//NPC_MAN
	ITEM_BOX, BOX_REWARD0, false, 1, 86400 * 3,//ENEMY_ONEEYE
	ITEM_GOLD, false, false, 50000, 86400 * 4,//NPC_MONICA
	ITEM_HEART, false, false, 100, 86400 * 5,//ENEMY_SKELETON

	//HOUSE_ATLANTICE
	ITEM_GOLD, false, false, 10000, 86400 * 1,//NPC_SEASOLDIER
	ITEM_GOLD, false, false, 20000, 86400 * 2,//NPC_LUISE
	ITEM_BOX, BOX_REWARD0, false, 1, 86400 * 3,//NPC_DARIAN
	ITEM_GOLD, false, false, 50000, 86400 * 4,//NPC_FRAUD
	ITEM_HEART, false, false, 100, 86400 * 5,//NPC_FISHING

	//HOUSE_SEWAGE
	ITEM_GOLD, false, false, 10000, 86400 * 1,//NPC_CREW
	ITEM_GOLD, false, false, 20000, 86400 * 2,//ENEMY_SLIME
	ITEM_BOX, BOX_REWARD0, false, 1, 86400 * 3,//NPC_DOBEL
	ITEM_GOLD, false, false, 50000, 86400 * 4,//NPC_GAGEL
	ITEM_HEART, false, false, 100, 86400 * 5,//NPC_CAPTAIN

	//HOUSE_CASTLE
	ITEM_GOLD, false, false, 10000, 86400 * 1,//NPC_ADELKNIGHT
	ITEM_GOLD, false, false, 20000, 86400 * 2,//NPC_MAID
	ITEM_BOX, BOX_REWARD0, false, 1, 86400 * 3,//NPC_SEBASTIAN
	ITEM_GOLD, false, false, 50000, 86400 * 4,//NPC_LORA
	ITEM_HEART, false, false, 100, 86400 * 5,//NPC_KING

	//HOUSE_PLAIN
	ITEM_GOLD, false, false, 10000, 86400 * 1,//ENEMY_SLING
	ITEM_GOLD, false, false, 20000, 86400 * 2,//NPC_GALLAND
	ITEM_BOX, BOX_REWARD0, false, 1, 86400 * 3,//NPC_DURAK

};

const unsigned int crewGetReward[] = {
	//0
	ITEM_HEART, false, false, 100,
	ITEM_HEART, false, false, 300,
	ITEM_HEART, false, false, 500,
	ITEM_HEART, false, false, 700,
	ITEM_HEART, false, false, 1000,
	ITEM_HEART, false, false, 1500,
	ITEM_HEART, false, false, 2000,
	ITEM_HEART, false, false, 2500,
	ITEM_HEART, false, false, 3000,
	ITEM_HEART, false, false, 3500,
	//10
	ITEM_HEART, false, false, 4000,
	ITEM_HEART, false, false, 4500,
	ITEM_HEART, false, false, 5000,
	ITEM_HEART, false, false, 5500,
	ITEM_HEART, false, false, 6000,
	ITEM_HEART, false, false, 6500,
	ITEM_HEART, false, false, 7000,
	ITEM_HEART, false, false, 7500,
	ITEM_HEART, false, false, 8000,
	ITEM_HEART, false, false, 8500,
	//20
	ITEM_HEART, false, false, 9000,
	ITEM_HEART, false, false, 9500,
	ITEM_HEART, false, false, 10000,
	ITEM_HEART, false, false, 11000,
	ITEM_HEART, false, false, 12000,
	ITEM_HEART, false, false, 13000,
	ITEM_HEART, false, false, 14000,
	ITEM_HEART, false, false, 15000,
	ITEM_HEART, false, false, 16000,
	ITEM_HEART, false, false, 17000,
	//30
	ITEM_HEART, false, false, 18000,
	ITEM_HEART, false, false, 19000,
	ITEM_HEART, false, false, 20000,
};

const long long bossReward[] = {//TOTALSTAGE * MONSTERREWARDDATASIZE
	ITEM_GOLD, null, null, 100000,//0
	ITEM_GOLD, null, null, 100000,//1
	ITEM_GOLD, null, null, 100000,//2
	ITEM_GOLD, null, null, 100000,//3
	ITEM_GOLD, null, null, 100000,//4
	ITEM_GOLD, null, null, 100000,//5
	ITEM_GOLD, null, null, 100000,//6
	ITEM_GOLD, null, null, 100000,//7
	ITEM_GOLD, null, null, 100000,//8
	ITEM_GOLD, null, null, 100000,//9

	ITEM_GOLD, null, null, 100000,//10
	ITEM_GOLD, null, null, 100000,//11
	ITEM_GOLD, null, null, 100000,//12
	ITEM_GOLD, null, null, 100000,//13
	ITEM_GOLD, null, null, 100000,//14
	ITEM_GOLD, null, null, 100000,//15
	ITEM_GOLD, null, null, 100000,//16
	ITEM_GOLD, null, null, 100000,//17
	ITEM_GOLD, null, null, 100000,//18
	ITEM_GOLD, null, null, 100000,//19

	ITEM_GOLD, null, null, 100000,//20
	ITEM_GOLD, null, null, 100000,//21
	ITEM_GOLD, null, null, 100000,//22
	ITEM_GOLD, null, null, 100000,//23
	ITEM_GOLD, null, null, 100000,//24
	ITEM_GOLD, null, null, 100000,//25
	ITEM_GOLD, null, null, 100000,//26
	ITEM_GOLD, null, null, 100000,//27
	ITEM_GOLD, null, null, 100000,//28
	ITEM_GOLD, null, null, 100000,//29

	ITEM_GOLD, null, null, 100000,//30
	ITEM_GOLD, null, null, 100000,//31
	ITEM_GOLD, null, null, 100000,//32
	ITEM_GOLD, null, null, 100000,//33
	ITEM_GOLD, null, null, 100000,//34
	ITEM_GOLD, null, null, 100000,//35
	ITEM_GOLD, null, null, 100000,//36
	ITEM_GOLD, null, null, 100000,//37
	ITEM_GOLD, null, null, 100000,//38
	ITEM_GOLD, null, null, 100000,//39

	ITEM_GOLD, null, null, 100000,//40
	ITEM_GOLD, null, null, 100000,//41
	ITEM_GOLD, null, null, 100000,//42
	ITEM_GOLD, null, null, 100000,//43
	ITEM_GOLD, null, null, 100000,//44
	ITEM_GOLD, null, null, 100000,//45
	ITEM_GOLD, null, null, 100000,//46
	ITEM_GOLD, null, null, 100000,//47
	ITEM_GOLD, null, null, 100000,//48
	ITEM_GOLD, null, null, 100000,//49

	ITEM_GOLD, null, null, 100000,//50
	ITEM_GOLD, null, null, 100000,//51
	ITEM_GOLD, null, null, 100000,//52
	ITEM_GOLD, null, null, 100000,//53
	ITEM_GOLD, null, null, 100000,//54
	ITEM_GOLD, null, null, 100000,//55
	ITEM_GOLD, null, null, 100000,//56
	ITEM_GOLD, null, null, 100000,//57
	ITEM_GOLD, null, null, 100000,//58
	ITEM_GOLD, null, null, 100000,//59

	ITEM_GOLD, null, null, 100000,//60
	ITEM_GOLD, null, null, 100000,//61
	ITEM_GOLD, null, null, 100000,//62
	ITEM_GOLD, null, null, 100000,//63
	ITEM_GOLD, null, null, 100000,//64
	ITEM_GOLD, null, null, 100000,//65
	ITEM_GOLD, null, null, 100000,//66
	ITEM_GOLD, null, null, 100000,//67
	ITEM_GOLD, null, null, 100000,//68
	ITEM_GOLD, null, null, 100000,//69

	ITEM_GOLD, null, null, 100000,//70
	ITEM_GOLD, null, null, 100000,//71
	ITEM_GOLD, null, null, 100000,//72
	ITEM_GOLD, null, null, 100000,//73
	ITEM_GOLD, null, null, 100000,//74
	ITEM_GOLD, null, null, 100000,//75
	ITEM_GOLD, null, null, 100000,//76
	ITEM_GOLD, null, null, 100000,//77
	ITEM_GOLD, null, null, 100000,//78
	ITEM_GOLD, null, null, 100000,//79

	ITEM_GOLD, null, null, 100000,//80
	ITEM_GOLD, null, null, 100000,//81
	ITEM_GOLD, null, null, 100000,//82
	ITEM_GOLD, null, null, 100000,//83
	ITEM_GOLD, null, null, 100000,//84
	ITEM_GOLD, null, null, 100000,//85
	ITEM_GOLD, null, null, 100000,//86
	ITEM_GOLD, null, null, 100000,//87
	ITEM_GOLD, null, null, 100000,//88
	ITEM_GOLD, null, null, 100000,//89

	ITEM_GOLD, null, null, 100000,//90
	ITEM_GOLD, null, null, 100000,//91
	ITEM_GOLD, null, null, 100000,//92
	ITEM_GOLD, null, null, 100000,//93
	ITEM_GOLD, null, null, 100000,//94
	ITEM_GOLD, null, null, 100000,//95
	ITEM_GOLD, null, null, 100000,//96
	ITEM_GOLD, null, null, 100000,//97
	ITEM_GOLD, null, null, 100000,//98
	ITEM_GOLD, null, null, 100000,//99
};


const int calendarPos[] = {
	16 * _2X, -20 * _2X, POPUPWINDOWSIZE_X - 32 * _2X, REWARDCARDSIZE_Y + 24 * _2X, //타이틀

	16 * _2X, -156 * _2X, REWARDCARDSIZE_X, REWARDCARDSIZE_Y, //MONDAY
	116 * _2X, -156 * _2X, REWARDCARDSIZE_X, REWARDCARDSIZE_Y, //TUESDAY
	216 * _2X, -156 * _2X, REWARDCARDSIZE_X, REWARDCARDSIZE_Y, //WEDNESDAY
	16 * _2X, -256 * _2X, REWARDCARDSIZE_X, REWARDCARDSIZE_Y, //THURSDAY
	116 * _2X, -256 * _2X, REWARDCARDSIZE_X, REWARDCARDSIZE_Y, //FRIDAY
	216 * _2X, -256 * _2X, REWARDCARDSIZE_X, REWARDCARDSIZE_Y, //SATURDAY

	16 * _2X, -360 * _2X, CALENDAR_WIDTH + 16 * _2X, REWARDCARDSIZE_Y + 16 * _2X, //SUNDAY

};

const int calendarMonthlyRewardDay[] = {
	8,
	15,
	22,
	30,
};

//박스 아이콘, 카운트, 1번째 박스 보상, 2번째 박스 보상, 3번째 박스 보상, 4번째 박스 보상
//각 박스는 최대 3개의 아이템 보상을 주고
//아이템 정보는 type, detail, (grade or count) 이렇게 3개 데이터를 사용한다.
const long long calendarInfo1Month[] = {
	//chapter1
	//8일차 보상
	ITEM_BOX, BOX_REWARD2, GRADE_NORMAL,
	//15일차 보상
	ITEM_BOX, BOX_REWARD3, GRADE_NORMAL,
	//22일차 보상
	ITEM_BOX, BOX_REWARD4, GRADE_NORMAL,
	//30일차 보상
	ITEM_BOX, BOX_REWARD5, GRADE_NORMAL,

	//chapter2
	//8일차 보상
	ITEM_BOX, BOX_REWARD2, GRADE_NORMAL,
	//15일차 보상
	ITEM_BOX, BOX_REWARD3, GRADE_NORMAL,
	//22일차 보상
	ITEM_BOX, BOX_REWARD4, GRADE_NORMAL,
	//30일차 보상
	ITEM_BOX, BOX_REWARD5, GRADE_NORMAL,

	//chapter3
	//8일차 보상
	ITEM_BOX, BOX_REWARD2, GRADE_NORMAL,
	//15일차 보상
	ITEM_BOX, BOX_REWARD3, GRADE_NORMAL,
	//22일차 보상
	ITEM_BOX, BOX_REWARD4, GRADE_NORMAL,
	//30일차 보상
	ITEM_BOX, BOX_REWARD5, GRADE_NORMAL,

	//chapter4
	//8일차 보상
	ITEM_BOX, BOX_REWARD2, GRADE_NORMAL,
	//15일차 보상
	ITEM_BOX, BOX_REWARD3, GRADE_NORMAL,
	//22일차 보상
	ITEM_BOX, BOX_REWARD4, GRADE_NORMAL,
	//30일차 보상
	ITEM_BOX, BOX_REWARD5, GRADE_NORMAL,

	//chapter5
	//8일차 보상
	ITEM_BOX, BOX_REWARD2, GRADE_NORMAL,
	//15일차 보상
	ITEM_BOX, BOX_REWARD3, GRADE_NORMAL,
	//22일차 보상
	ITEM_BOX, BOX_REWARD4, GRADE_NORMAL,
	//30일차 보상
	ITEM_BOX, BOX_REWARD5, GRADE_NORMAL,

	//chapter6
	//8일차 보상
	ITEM_BOX, BOX_REWARD2, GRADE_NORMAL,
	//15일차 보상
	ITEM_BOX, BOX_REWARD3, GRADE_NORMAL,
	//22일차 보상
	ITEM_BOX, BOX_REWARD4, GRADE_NORMAL,
	//30일차 보상
	ITEM_BOX, BOX_REWARD5, GRADE_NORMAL,

	//chapter7
	//8일차 보상
	ITEM_BOX, BOX_REWARD2, GRADE_NORMAL,
	//15일차 보상
	ITEM_BOX, BOX_REWARD3, GRADE_NORMAL,
	//22일차 보상
	ITEM_BOX, BOX_REWARD4, GRADE_NORMAL,
	//30일차 보상
	ITEM_BOX, BOX_REWARD5, GRADE_NORMAL,

	//chapter8
	//8일차 보상
	ITEM_BOX, BOX_REWARD2, GRADE_NORMAL,
	//15일차 보상
	ITEM_BOX, BOX_REWARD3, GRADE_NORMAL,
	//22일차 보상
	ITEM_BOX, BOX_REWARD4, GRADE_NORMAL,
	//30일차 보상
	ITEM_BOX, BOX_REWARD5, GRADE_NORMAL,

	//chapter9
	//8일차 보상
	ITEM_BOX, BOX_REWARD2, GRADE_NORMAL,
	//15일차 보상
	ITEM_BOX, BOX_REWARD3, GRADE_NORMAL,
	//22일차 보상
	ITEM_BOX, BOX_REWARD4, GRADE_NORMAL,
	//30일차 보상
	ITEM_BOX, BOX_REWARD5, GRADE_NORMAL,

	//chapter10
	//8일차 보상
	ITEM_BOX, BOX_REWARD2, GRADE_NORMAL,
	//15일차 보상
	ITEM_BOX, BOX_REWARD3, GRADE_NORMAL,
	//22일차 보상
	ITEM_BOX, BOX_REWARD4, GRADE_NORMAL,
	//30일차 보상
	ITEM_BOX, BOX_REWARD5, GRADE_NORMAL,

};

//여기는 실제 들어갈 보상
//여기도 최대 3가지 들어갈 수 있고, 여기에는 대표 아이콘이 없고 레어하게 그냥 나열한다.
const long long calendarInfo1Week[] = {
	//chapter1
	ITEM_GOLD, null, null, 10000, //1일차 보상
	ITEM_HEART, null, null, 50, //2일차 보상
	ITEM_BOX, BOX_REWARD0, null, 1, //3일차 보상
	ITEM_GOLD, null, null, 20000, //4일차 보상
	ITEM_HEART, null, null, 100, //5일차 보상
	ITEM_BOX, BOX_REWARD0, null, 1, //6일차 보상
	ITEM_BOX, BOX_REWARD0, null, 1, //7일차 보상
	ITEM_GOLD, null, null, 1000,
	ITEM_HEART, null, null, 1000,
	ITEM_BOX, BOX_REWARD0, null, 1,

	//chapter2
	//1일차 보상
	//2일차 보상
	//3일차 보상
	//4일차 보상
	//5일차 보상
	//6일차 보상
	//7일차 보상

	//chapter3
	//1일차 보상
	//2일차 보상
	//3일차 보상
	//4일차 보상
	//5일차 보상
	//6일차 보상
	//7일차 보상

	//chapter4
	//1일차 보상
	//2일차 보상
	//3일차 보상
	//4일차 보상
	//5일차 보상
	//6일차 보상
	//7일차 보상

	//chapter5
	//1일차 보상
	//2일차 보상
	//3일차 보상
	//4일차 보상
	//5일차 보상
	//6일차 보상
	//7일차 보상

	//chapter6
	//1일차 보상
	//2일차 보상
	//3일차 보상
	//4일차 보상
	//5일차 보상
	//6일차 보상
	//7일차 보상

	//chapter7
	//1일차 보상
	//2일차 보상
	//3일차 보상
	//4일차 보상
	//5일차 보상
	//6일차 보상
	//7일차 보상

	//chapter8
	//1일차 보상
	//2일차 보상
	//3일차 보상
	//4일차 보상
	//5일차 보상
	//6일차 보상
	//7일차 보상

	//chapter9
	//1일차 보상
	//2일차 보상
	//3일차 보상
	//4일차 보상
	//5일차 보상
	//6일차 보상
	//7일차 보상

	//chapter10
	//1일차 보상
	//2일차 보상
	//3일차 보상
	//4일차 보상
	//5일차 보상
	//6일차 보상
	//7일차 보상

	//chapter11
	//1일차 보상
	//2일차 보상
	//3일차 보상
	//4일차 보상
	//5일차 보상
	//6일차 보상
	//7일차 보상

	//chapter12
	//1일차 보상
	//2일차 보상
	//3일차 보상
	//4일차 보상
	//5일차 보상
	//6일차 보상
	//7일차 보상

	//chapter13
	//1일차 보상
	//2일차 보상
	//3일차 보상
	//4일차 보상
	//5일차 보상
	//6일차 보상
	//7일차 보상

	//chapter14
	//1일차 보상
	//2일차 보상
	//3일차 보상
	//4일차 보상
	//5일차 보상
	//6일차 보상
	//7일차 보상

	//chapter15
	//1일차 보상
	//2일차 보상
	//3일차 보상
	//4일차 보상
	//5일차 보상
	//6일차 보상
	//7일차 보상
};

//종류, 수량
const int collectionReward[TOTAL_COLLECTIONS * 4] = {
	//"초보검사 컬렉션",//TEXT_COLLECTIONS,//0
	ITEM_HEART, false, false, 100,
	//"카우보이 컬렉션",//1
	ITEM_HEART, false, false, 200,
	//"여행자 컬렉션",//2
	ITEM_HEART, false, false, 500,
	//"베이비 컬렉션",//3
	ITEM_HEART, false, false, 700,
	//"귀족 컬렉션",//4
	ITEM_HEART, false, false, 1000,
	//"금속 컬렉션",//5
	ITEM_HEART, false, false, 1500,
	//"방랑자 컬렉션",//6
	ITEM_HEART, false, false, 2000,
	//"방한 컬렉션",//7
	ITEM_HEART, false, false, 2300,
	//"플레이트 컬렉션",//8
	ITEM_HEART, false, false, 2800,
	//"도적 컬렉션",//9
	ITEM_HEART, false, false, 5000,
	//"사냥꾼 컬렉션",//10
	ITEM_HEART, false, false, 4800,
	//"검투사 컬렉션",//11
	ITEM_HEART, false, false, 4200,
	//"벨벳 컬렉션",//12
	ITEM_HEART, false, false, 7000,
	//"투우사 컬렉션",//13
	ITEM_HEART, false, false, 8000,
	//"스파이크 컬렉션",//14
	ITEM_HEART, false, false, 7500,
	//"스나이퍼 컬렉션",//15
	ITEM_HEART, false, false, 10000,
	//"해적 컬렉션",//16
	ITEM_HEART, false, false, 9000,
	//"그랜드 컬렉션",//17
	ITEM_HEART, false, false, 8000,
	//"혼란 컬렉션",//18
	ITEM_HEART, false, false, 12000,
	//"에이스 컬렉션",//19
	ITEM_HEART, false, false, 15000,
	//"고대 컬렉션",//20
	ITEM_HEART, false, false, 18000,
	//"프리스트 컬렉션",//21
	ITEM_HEART, false, false, 20000,
	//"드래곤 컬렉션",//22
	ITEM_HEART, false, false, 22000,
	//"용자 컬렉션",//23
	ITEM_HEART, false, false, 25000,
};
#endif