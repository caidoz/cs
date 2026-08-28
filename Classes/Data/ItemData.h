#pragma once
#include "../Def.h"

#ifndef _DATA_ITEM_H_
#define _DATA_ITEM_H_

extern const unsigned short* itemTypeCnt;
enum { itemTypeCnt_COUNT = 34 };

extern const int* swordInfoList;
enum { swordInfoList_COUNT = 4 };

extern const signed short* newCardEffect;
enum { newCardEffect_COUNT = 84 };

// ===== 장비 아이템 데이터 타입 =====
extern const int* equipDataType;
enum { equipDataType_COUNT = 6 };

// ===== 개방된 아이템 초기값 =====
extern const unsigned short* openedItemData;
enum { openedItemData_COUNT = 20 };


//장비레벨업 맥스값
extern const unsigned char* itemLevelLimit;
enum { itemLevelLimit_COUNT = 16 };

extern const int* itemExpAcce;
enum { itemExpAcce_COUNT = 50 };

extern const int* itemExp;
enum { itemExp_COUNT = 224 };

extern const int* itemMaterialExpAcce;
enum { itemMaterialExpAcce_COUNT = 50 };

extern const int* itemMaterialExp;
enum { itemMaterialExp_COUNT = 225 };

extern const long long* itemEvolutionItem;
enum { itemEvolutionItem_COUNT = 240 };

extern const long long* itemUpgradeHammer;
enum { itemUpgradeHammer_COUNT = 6 };

extern const unsigned short* arenaFloorGold;
enum { arenaFloorGold_COUNT = 200 };

extern const unsigned short* revolutionMedal;
enum { revolutionMedal_COUNT = 8 };


extern const unsigned int* itemColor;
enum { itemColor_COUNT = 10 };


extern const unsigned int* buffBlend;
enum { buffBlend_COUNT = 16 };


extern const unsigned char* swordMaxBet;
enum { swordMaxBet_COUNT = 40 };

extern const unsigned char* swordHeart;
enum { swordHeart_COUNT = 40 };

extern const long long* swordGold;
enum { swordGold_COUNT = 40 };

extern const unsigned long long* itemPrice;
enum { itemPrice_COUNT = 328 };

extern const unsigned int* itemSellPrice;
enum { itemSellPrice_COUNT = 301 };

//선언이 559 였는데 ItemData.cpp 의 값은 565 개다. 뒤 여섯 개가 선언
//밖이라 팩에는 안 실리고 내장본에만 있었다 - 팩을 쓰는 실기와 안 쓰는
//경우가 다른 값을 읽을 수 있는 상태였다. 실제에 맞춘다.
//
//주석을 extern 과 enum 사이에 두면 안 된다. make_pack.py 가 그 둘을
//짝으로 읽어서, 사이가 갈리면 배열이 통째로 팩에서 빠진다.
extern const unsigned short* itemStar;
enum { itemStar_COUNT = 565 };

extern const unsigned short* itemStartCnt;
enum { itemStartCnt_COUNT = 41 };


extern const unsigned char* boxEquipType;
enum { boxEquipType_COUNT = 8 };


extern const unsigned char* materialDropData;
enum { materialDropData_COUNT = 270 };

extern const unsigned char* wasteDropData;
enum { wasteDropData_COUNT = 1215 };

extern const int* itemValueType;
enum { itemValueType_COUNT = 20 };

extern const int* itemValueTypeText;
enum { itemValueTypeText_COUNT = 20 };

extern const unsigned char* itemEquipSlot;
enum { itemEquipSlot_COUNT = 18 };

extern const unsigned char* itemSlotEquip;
enum { itemSlotEquip_COUNT = 8 };


extern const unsigned char* wasteDrop;
enum { wasteDrop_COUNT = 30 };

extern const unsigned char* wasteValue;
enum { wasteValue_COUNT = 7 };
extern const unsigned char* weaponRange;
enum { weaponRange_COUNT = 3 };

//초기무기 - 공격력 : 7/5/10 요구레벨 : 1 요구스탯 : 1
extern const unsigned int* itemValue;
enum { itemValue_COUNT = 171 };

extern const unsigned char* gradeRatio;
enum { gradeRatio_COUNT = 6 };

extern const unsigned char* typeRatio;
enum { typeRatio_COUNT = 18 };

extern const unsigned char* acceOptionStatMatch;
enum { acceOptionStatMatch_COUNT = 12 };

extern const unsigned int* acceDefaultStatValue;
enum { acceDefaultStatValue_COUNT = 300 };

extern const unsigned int* neckOptionStatValue;
enum { neckOptionStatValue_COUNT = 1400 };
#ifdef TIERMAP
const unsigned int tierMapNeck[TOTAL_NECK_TIERMAP] = {
	ITEM_NECK0,	//명예의 펜던트(0)
	ITEM_NECK1,	//연옥의 브로치(1)
	ITEM_NECK2,	//찰나의 팔찌(2)
	ITEM_NECK3,	//황금 바늘(3)
	ITEM_NECK4,	//파열의 팔찌(4)
	ITEM_NECK5,	//메피스토 피리(5)
};

const unsigned int tierMapRing[TOTAL_RING_TIERMAP] = {
	ITEM_RING5,	//생환의 반지(33)//|e사용시 |bHP |i%d |b회복
	ITEM_RING3,	//해방의 반지(31)//|e사용시|i%d%%|j확률로 상태이상제거
	ITEM_RING6,	//희생의 반지(34)//|e사용시 |i%d%% |b확률로 추가타격
	ITEM_RING9,	//광대의 반지(37)//|e사용시 |b회피 |i%d%% |b증가
	ITEM_RING10,	//원한의 반지(38)//|e사용시 |b관통공격확률 |i%d%% |b증가
	ITEM_RING15,	//차원의 반지(43)//|en.사용시 |b적방어도감소 |i%d
};
#endif

extern const unsigned int* ringOptionStatValue;
enum { ringOptionStatValue_COUNT = 900 };

extern const unsigned int* gemOptionStatValue;
enum { gemOptionStatValue_COUNT = 300 };
//초기무기 - 공격력 : 7/5/10 요구레벨 : 1 요구스탯 : 1
extern const unsigned int* itemUpgradeValue;
enum { itemUpgradeValue_COUNT = 2592 };

extern const unsigned char* itemRatio;
enum { itemRatio_COUNT = 8 };

extern const unsigned short* itemPow;
enum { itemPow_COUNT = 220 };

extern const unsigned char* itemLv;
enum { itemLv_COUNT = 144 };

extern const unsigned char* itemStat;
enum { itemStat_COUNT = 144 };
#ifdef IRON
const unsigned char itemNameOrder[TOTALSTAR * TOTALGRADE] = {
	0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 3, 3,
	4, 4, 4, 4, 5, 5,
	6, 6, 6, 6, 7, 7,
	8, 8, 8, 8, 9, 9,
	10, 10, 10, 10, 11, 12,
	13, 13, 13, 13, 14, 15,
};

const unsigned char itemDataOrder[TOTALSTAR * TOTALGRADE] = {
	0, 1, 2, 3, 3, 3,
	4, 5, 6, 7, 7, 7,
	8, 9, 10, 11, 12, 12,
	13, 14, 15, 16, 17, 17,
	18, 19, 20, 21, 22, 23,
	24, 25, 26, 27, 28, 29,
	30, 31, 32, 33, 34, 35,
	36, 37, 38, 39, 40, 41,
};

const unsigned char enchantGrade[ENCHANTDATASIZE_TYPE] = {
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_SET,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_SET,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_SET, GRADE_EPIC,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_SET, GRADE_EPIC,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_SET, GRADE_EPIC, GRADE_LEGEND,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_SET, GRADE_EPIC, GRADE_LEGEND,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_SET, GRADE_EPIC, GRADE_LEGEND,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_SET, GRADE_EPIC, GRADE_LEGEND,
};
#else
#ifdef SETITEM
const unsigned char itemNameOrder[TOTAL_SWORD * TOTALGRADE] = {
	0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4,
	5, 5, 5, 5, 5, 5,
	6, 6, 6, 6, 6, 6,
	7, 7, 7, 7, 7, 7,
	8, 8, 8, 8, 8, 8,
	9, 9, 9, 9, 9, 9,
	10, 10, 10, 10, 10, 10,
	11, 11, 11, 11, 11, 11,
	12, 12, 12, 12, 12, 12,
	13, 13, 13, 13, 13, 13,
	14, 14, 14, 14, 14, 14,
	15, 15, 15, 15, 15, 15,
	16, 16, 16, 16, 16, 16,
	17, 17, 17, 17, 17, 17,
	18, 18, 18, 18, 18, 18,
	19, 19, 19, 19, 19, 19,
	20, 20, 20, 20, 20, 20,
	21, 21, 21, 21, 21, 21,
	22, 22, 22, 22, 22, 22,
	23, 23, 23, 23, 23, 23,
	24, 24, 24, 24, 24, 24,
	25, 25, 25, 25, 25, 25,
	26, 26, 26, 26, 26, 26,
	27, 27, 27, 27, 27, 27,
	28, 28, 28, 28, 28, 28,
	29, 29, 29, 29, 29, 29,
	30, 30, 30, 30, 30, 30,
};

const unsigned char itemDataOrder[TOTALSTAR * TOTALGRADE] = {
	0, 1, 2, 3, 3, 3,
	4, 5, 6, 7, 7, 7,
	8, 9, 10, 11, 12, 12,
	13, 14, 15, 16, 17, 17,
	18, 19, 20, 21, 22, 22,
	23, 24, 25, 26, 27, 27,
	28, 29, 30, 31, 32, 33,
	34, 35, 36, 37, 38, 39,
};
#else
const unsigned char itemNameOrder[TOTALSTAR * TOTALGRADE] = {
	0, 1, 2, 3, 4,
	5, 6, 7, 8, 9,
	10, 11, 12, 13, 14,
	15, 16, 17, 18, 19,
	20, 21, 22, 23, 24,
	25, 26, 27, 28, 29,
	30, 31, 32, 33, 34,
	35, 36, 37, 38, 39,
};

const unsigned char itemDataOrder[TOTALSTAR * TOTALGRADE] = {
	0, 1, 2, 3, 4,
	5, 6, 7, 8, 9,
	10, 11, 12, 13, 14,
	15, 16, 17, 18, 19,
	20, 21, 22, 23, 24,
	25, 26, 27, 28, 29,
	30, 31, 32, 33, 34,
	35, 36, 37, 38, 39,
};

#endif
#ifdef ALLEQUIPLEGENDGRADE
const unsigned char enchantGrade[ENCHANTDATASIZE_TYPE] = {
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_EPIC, GRADE_LEGEND,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_EPIC, GRADE_LEGEND,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_EPIC, GRADE_LEGEND,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_EPIC, GRADE_LEGEND,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_EPIC, GRADE_LEGEND,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_EPIC, GRADE_LEGEND,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_EPIC, GRADE_LEGEND,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_EPIC, GRADE_LEGEND,
};
#else
const unsigned char enchantGrade[ENCHANTDATASIZE_TYPE] = {
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_SET,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_SET,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_SET, GRADE_EPIC,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_SET, GRADE_EPIC,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_SET, GRADE_EPIC,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_SET, GRADE_EPIC,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_SET, GRADE_EPIC, GRADE_LEGEND,
	GRADE_NORMAL, GRADE_SUPERIOR, GRADE_RARE, GRADE_SET, GRADE_EPIC, GRADE_LEGEND,
};
#endif
#endif

#ifdef IRON
const unsigned int neckPrice[] = {
	100, 20,
	500, 100,
	1000, 200,
	3000, 600,
	5000, 1000,
	10000, 2000,
	20000, 4000,
	30000, 6000,
};

const unsigned int ringPrice[] = {
	100, 20,
	500, 100,
	1000, 200,
	3000, 600,
	5000, 1000,
	10000, 2000,
	20000, 4000,
	30000, 6000,
};
#endif

//철광석대 골드 비율
//검        15:50
//총        10:40
//부메랑    20:60

//헬멧      8:20
//모자      6:25
//두건      10:30

//갑옷		10:20
//조끼		8:25
//코트		6:30

//건틀렛	10:20
//팔찌		10:20
//장갑		10:20

//킬트		15:50
//스커트	10:45
//바지		8:40

//장화		10:20
//신발		10:20
//부츠		10:20

//목걸이	30:15

//반지		35:10
extern const unsigned int* enchantData;
enum { enchantData_COUNT = 4320 };

extern const unsigned char* itemCooltime;
enum { itemCooltime_COUNT = 23 };

//아이템 종류-아이콘 매칭 테이블
extern const unsigned short* itemIconTable;
enum { itemIconTable_COUNT = 447 };

extern const unsigned int* neckOption;
enum { neckOption_COUNT = 168 };

extern const signed int* neckRingDefaultValue;
enum { neckRingDefaultValue_COUNT = 300 };

extern const signed char* ringOption;
enum { ringOption_COUNT = 126 };

extern const int* optionRange;
enum { optionRange_COUNT = 366 };

extern const signed char* optionValue;
enum { optionValue_COUNT = 61 };

extern const unsigned char* setItem;
enum { setItem_COUNT = 1302 };

extern const int* setOption;
enum { setOption_COUNT = 1404 };

extern const unsigned int* legendItem;
enum { legendItem_COUNT = 648 };

//옵션<->스탯 테이블
extern const signed char* optionStat;
enum { optionStat_COUNT = 79 };

//옵션 테이블
extern const signed char* option_prefix;
enum { option_prefix_COUNT = 128 };

extern const signed char* option_suffix;
enum { option_suffix_COUNT = 128 };

extern const unsigned char* option_count_prefix;
enum { option_count_prefix_COUNT = 8 };

extern const unsigned char* option_count_suffix;
enum { option_count_suffix_COUNT = 8 };

//보석옵션 테이블
//ITEM_GEM_RUBY//루비//물리
//ITEM_GEM_SAPPHIRE//사파이어//GEM_FIRE_REG
//ITEM_GEM_AMETHYST//자수정//GEM_FROST_REG
//ITEM_GEM_DIAMOND//다이아몬드//GEM_THUNDER_REG
//ITEM_GEM_PERL//진주//GEM_HOLY_REG
//ITEM_GEM_EMERALD//에메랄드//GEM_DARK_REG
extern const unsigned char* gemOption;
enum { gemOption_COUNT = 81 };

//보석 장착 가격
extern const int* gemPrice;
enum { gemPrice_COUNT = 6 };


extern const int* enchantRate;
enum { enchantRate_COUNT = 300 };

extern const unsigned char* extraSetItem;
enum { extraSetItem_COUNT = 576 };


extern const signed int* newItemReward;
enum { newItemReward_COUNT = 684 };

extern const int (*upgradeCostCrew)[2 * 14];
enum { upgradeCostCrew_ROWS = 6, upgradeCostCrew_COLS = (2 * 14),
	   upgradeCostCrew_COUNT = upgradeCostCrew_ROWS * upgradeCostCrew_COLS };

extern const int (*upgradeCostEquip)[2 * 14];
enum { upgradeCostEquip_ROWS = 6, upgradeCostEquip_COLS = (2 * 14),
	   upgradeCostEquip_COUNT = upgradeCostEquip_ROWS * upgradeCostEquip_COLS };

#endif