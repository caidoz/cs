#pragma once

#ifndef _DATA_GEARROLE_H_
#define _DATA_GEARROLE_H_

//---- 장비 역할 표 (CLAUDE.md 4장) ----
//
//가방에 오르는 모든 장비는 네 역할축 가운데 주 역할 하나와 부 역할 하나를
//반드시 가진다. 역할 없는 장식 아이템은 두지 않는다.
//
//수치는 두 갈래다. 섞으면 한쪽이 다른 쪽을 삼킨다.
//
//    크기값(defPer, hpPer)   아이템 값(price)에 비례한다. 방어막과 체력은
//                            장비가 좋아질수록 통째로 커져야 하는 양이다.
//    비율값(그 나머지)       (등급+1) x 겹친 레벨에만 비례한다. 공격력 %,
//                            치명타, 쿨감, 회피, 흡혈, 재생, 골드다. 여기에
//                            price 를 곱하면 비싼 장비 하나로 100% 를 넘는다.
//
//모든 비율값은 1/10 % 자리까지 적는다(25 = 2.5%). 크기값도 1/10 자리다.
//합계 상한은 GridQueryGearRoles 가 건다 - 표에는 상한을 적지 않는다.
typedef enum _gearRoleAxis {
	GEAR_AXIS_NONE = 0,
	GEAR_AXIS_ATK,		//공격: 타격 피해, 공격 주기, 치명타
	GEAR_AXIS_DEF,		//방어: 방어막 최대치, 피해 경감
	GEAR_AXIS_REGEN,	//회복: 체력 재생, 방어막 재충전, 흡혈
	GEAR_AXIS_UTIL,		//보조: 최대 체력, 회피, 골드, 쿨감
	TOTAL_GEAR_AXES
} GEARROLEAXIS;

//---- 부위마다 세 줄, 그 셋은 히어로다 ----
//
//티어가 아니다. 아이템 종류 셋씩이 히어로 셋에 1:1 로 묶여 있다 - 게임이
//처음부터 그렇게 지어졌다(MakeItemType 의 `ITEM_SWORD + type`, ImgDef.h 의
//COSTUME_*_ROBIN/DIANA/MAXX).
//
//    부위    로빈(0)      다이애나(1)   맥스(2)
//    무기    SWORD        GUN           BOOMERANG
//    머리    HELM         HAT           CAP
//    몸통    ARMOR        VEST          COAT
//    손      GUNTLET      ARMLET        GLOVE
//    하체    KILT         SKIRT         PANTS
//    발      GREAVES      SHOES         BOOTS
//
//그래서 창고도 히어로마다 다르다(GearGrantEnsure). 역할축의 성향이 곧
//캐릭터의 성격이다 - 로빈은 방어와 공격을 겸한 중장, 다이애나는 쿨감과
//회피의 경장, 맥스는 체력과 회복의 전사다.
//
//방패·장신구는 셋이 같이 쓴다(GEAR_LINE_COMMON).
typedef enum _gearRoleLine {
	GEAR_LINE_ROBIN = 0,	//로빈 (curHero 0)
	GEAR_LINE_DIANA,		//다이애나 (curHero 1)
	GEAR_LINE_MAXX,			//맥스 (curHero 2)
	GEAR_LINE_COMMON,		//셋이 같이 쓴다: 방패, 목걸이, 반지
	GEAR_LINE_SOCKET,		//보석: 인접 장비의 주 역할을 증폭한다
	GEAR_LINE_TACTIC		//작전서/대포: 역할축이 아니라 제 전용 길로 간다
} GEARROLELINE;

struct GearRoleSpec {
	short type;				//ITEM_*
	unsigned char primary;	//주 역할
	unsigned char second;	//부 역할
	unsigned char line;		//어느 히어로의 줄인가 (GEAR_LINE_*)

	//크기값 (price 1 당, 1/10 자리)
	short defPer;			//방어막 최대치
	short hpPer;			//최대 체력

	//비율값 ((등급+1) x 레벨 당, 1/10 % 자리)
	short atkPct;			//가방 검 피해
	short critPct;			//치명타율
	short coolPct;			//공격 준비 단축
	short dodgePct;			//회피
	short leechPct;			//적중 시 흡혈
	short hpRegen;			//초당 체력 재생 (1/10 점)
	short shieldRegen;		//초당 방어막 재생 (1/10 점)
	short gold;				//웨이브 클리어 골드 (1/10 원)
};

//6부위 x 히어로 셋 + 방패 + 장신구 3종. CLAUDE.md 4-2 표와 한 줄씩 맞선다.
//
//한 줄(히어로)을 통째로 읽으면 그 캐릭터의 성격이 보인다. 한 부위를 세로로
//읽으면 같은 자리를 셋이 어떻게 달리 쓰는지가 보인다.
static const GearRoleSpec kGearRole[] = {
	//무기: 피해의 본줄기는 GridTestSwords 가 들고 있다. 여기서는 부 역할만
	//얹는다 - 같은 피해를 두 군데서 더하면 두 배가 된다.
	{ ITEM_SWORD,     GEAR_AXIS_ATK,   GEAR_AXIS_REGEN, GEAR_LINE_ROBIN,     0,   0,   0,  10,   0,  0, 10,  0,  0,  0 },
	{ ITEM_GUN,       GEAR_AXIS_ATK,   GEAR_AXIS_ATK,   GEAR_LINE_DIANA,     0,   0,   0,  15,  10,  0,  0,  0,  0,  0 },
	{ ITEM_BOOMERANG, GEAR_AXIS_ATK,   GEAR_AXIS_UTIL,  GEAR_LINE_MAXX,      0,   0,   0,   5, 100,  0,  0,  0,  0,  0 },

	//머리
	{ ITEM_HELM,      GEAR_AXIS_DEF,   GEAR_AXIS_ATK,   GEAR_LINE_ROBIN,    25,   0,   0,  10,   0,  0,  0,  0,  0,  0 },
	{ ITEM_HAT,       GEAR_AXIS_UTIL,  GEAR_AXIS_ATK,   GEAR_LINE_DIANA,     0,   0,   0,  15, 150,  0,  0,  0,  0,  0 },
	{ ITEM_CAP,       GEAR_AXIS_UTIL,  GEAR_AXIS_DEF,   GEAR_LINE_MAXX,     12,   0,   0,   5, 100,  0,  0,  0,  0,  0 },

	//몸통
	{ ITEM_ARMOR,     GEAR_AXIS_DEF,   GEAR_AXIS_DEF,   GEAR_LINE_ROBIN,    40,   0,   0,   0,   0,  0,  0,  0,  0,  0 },
	{ ITEM_VEST,      GEAR_AXIS_DEF,   GEAR_AXIS_UTIL,  GEAR_LINE_DIANA,    25,  80,   0,   0,   0,  0,  0,  0,  0,  0 },
	{ ITEM_COAT,      GEAR_AXIS_DEF,   GEAR_AXIS_REGEN, GEAR_LINE_MAXX,     20,   0,   0,   0,   0,  0,  0,  0,  5,  0 },

	//손
	{ ITEM_GUNTLET,   GEAR_AXIS_ATK,   GEAR_AXIS_DEF,   GEAR_LINE_ROBIN,    10,   0,  30,   0,   0,  0,  0,  0,  0,  0 },
	{ ITEM_ARMLET,    GEAR_AXIS_ATK,   GEAR_AXIS_UTIL,  GEAR_LINE_DIANA,     0,   0,  20,   0,  20,  0,  0,  0,  0,  0 },
	{ ITEM_GLOVE,     GEAR_AXIS_ATK,   GEAR_AXIS_REGEN, GEAR_LINE_MAXX,      0,   0,  15,   0,   0,  0, 10,  0,  0,  0 },

	//하체
	{ ITEM_KILT,      GEAR_AXIS_UTIL,  GEAR_AXIS_REGEN, GEAR_LINE_ROBIN,     0, 180,   0,   0,   0,  0,  0,  4,  0,  0 },
	{ ITEM_SKIRT,     GEAR_AXIS_UTIL,  GEAR_AXIS_ATK,   GEAR_LINE_DIANA,     0, 120,   0,  10,   0, 10,  0,  0,  0,  0 },
	{ ITEM_PANTS,     GEAR_AXIS_UTIL,  GEAR_AXIS_DEF,   GEAR_LINE_MAXX,     10, 250,   0,   0,   0,  0,  0,  0,  0,  0 },

	//발
	{ ITEM_GREAVES,   GEAR_AXIS_DEF,   GEAR_AXIS_REGEN, GEAR_LINE_ROBIN,    20,   0,   0,   0,   0,  0,  0,  0,  4, 10 },
	{ ITEM_SHOES,     GEAR_AXIS_UTIL,  GEAR_AXIS_REGEN, GEAR_LINE_DIANA,     0,   0,   0,   0,   0, 15,  0,  3,  0, 10 },
	{ ITEM_BOOTS,     GEAR_AXIS_REGEN, GEAR_AXIS_DEF,   GEAR_LINE_MAXX,     10,   0,   0,   0,   0,  0,  0,  0,  8, 20 },

	//방패: 즉시 펄스는 GridTestShields 가 들고 있다. 여기서는 최대치만 얹는다.
	{ ITEM_SHIELD,    GEAR_AXIS_DEF,   GEAR_AXIS_REGEN, GEAR_LINE_COMMON,   30,   0,   0,   0,   0,  0,  0,  0,  6,  0 },

	//장신구: 셋이 같이 쓴다
	{ ITEM_NECK,      GEAR_AXIS_REGEN, GEAR_AXIS_UTIL,  GEAR_LINE_COMMON,    0,  50,   0,   0,   0,  0,  0,  8,  0,  0 },
	{ ITEM_RING,      GEAR_AXIS_ATK,   GEAR_AXIS_REGEN, GEAR_LINE_COMMON,    0,   0,  10,  20,   0,  0,  5,  0,  0,  0 },

	//보석: 제 수치는 없다. 인접 장비의 주 역할을 25% 불린다.
	{ ITEM_GEM,       GEAR_AXIS_NONE,  GEAR_AXIS_NONE,  GEAR_LINE_SOCKET,    0,   0,   0,   0,   0,  0,  0,  0,  0,  0 },
};

enum { TOTAL_GEAR_ROLE = sizeof(kGearRole) / sizeof(kGearRole[0]) };

//보석 하나가 인접 장비의 주 역할을 올리는 비율(%)
enum { GEAR_GEM_AMPLIFY_PCT = 25 };

//합계 상한. 장비를 다 좋은 것으로 채운 판에서도 수치가 터지지 않게 막는다.
enum {
	GEAR_CAP_ATK_PCT = 150,
	GEAR_CAP_CRIT_PCT = 50,
	GEAR_CAP_COOL_PCT = 40,
	GEAR_CAP_DODGE_PCT = 30,
	GEAR_CAP_LEECH_PCT = 20,
};

inline const GearRoleSpec* GearRoleOf(int itemType)
{
	for (int i = 0; i < TOTAL_GEAR_ROLE; ++i) {
		if (kGearRole[i].type == itemType)
			return &kGearRole[i];
	}
	return 0;
}

//이 종류가 어느 히어로의 것인가. 방패·장신구·보석처럼 셋이 같이 쓰는
//것은 -1 이다. 창고 지급(GearGrantEnsure)이 이것으로 가른다.
inline int GearRoleHeroOf(int itemType)
{
	const GearRoleSpec* spec = GearRoleOf(itemType);

	if (!spec)
		return -1;

	if (spec->line == GEAR_LINE_ROBIN || spec->line == GEAR_LINE_DIANA
		|| spec->line == GEAR_LINE_MAXX)
		return (int)spec->line;

	return -1;
}

inline const char* GearRoleLineName(int line)
{
	switch (line) {
	case GEAR_LINE_ROBIN:  return "로빈";
	case GEAR_LINE_DIANA:  return "다이애나";
	case GEAR_LINE_MAXX:   return "맥스";
	case GEAR_LINE_COMMON: return "공용";
	default:               return "";
	}
}

inline const char* GearRoleAxisName(int axis)
{
	switch (axis) {
	case GEAR_AXIS_ATK:   return "공격";
	case GEAR_AXIS_DEF:   return "방어";
	case GEAR_AXIS_REGEN: return "회복";
	case GEAR_AXIS_UTIL:  return "보조";
	default:              return "";
	}
}

inline int GearRoleAxisColor(int axis)
{
	switch (axis) {
	case GEAR_AXIS_ATK:   return 0xFF6655;
	case GEAR_AXIS_DEF:   return 0xE0B040;
	case GEAR_AXIS_REGEN: return 0x44DD88;
	case GEAR_AXIS_UTIL:  return 0x6AB4FF;
	default:              return 0xDFD9C0;
	}
}

#endif
