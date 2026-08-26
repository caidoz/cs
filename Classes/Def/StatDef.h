#pragma once

#ifndef _DEF_STAT_H_
#define _DEF_STAT_H_

typedef enum _statDef {
	STAT_STR = 0,
	STAT_VIT,
	STAT_AGI,
	STAT_INT,

	PS_DMGMOD = 0,
	PS_CRITICAL,
	PS_PIERCE,
	PS_EXTRA,
	PS_STR,
	PS_VIT,
	PS_AGI,
	PS_INT,
	PS_SKILLDMG,
	PS_DEFENSE,
	PS_ABSORB,
	PS_FIRE,
	PS_FROST,
	PS_THUNDER,
	PS_HOLY,
	PS_DARK,
	PS_LUCK,
	PS_GOLDMOD,
	PS_EXPMOD,
	PS_HPRESTORE,
	PS_MPRESTORE,
	PS_POTION,
	PS_BUFF,
	PS_DMGADD,
	PS_FIREATTACK,
	PS_FROSTATTACK,
	PS_THUNDERATTACK,
	PS_HOLYATTACK,
	PS_DARKATTACK,
	PS_HIT,
	PS_IGNORE,
	PS_DELAY,
	PS_CRITDMG,
	PS_EVASION,
	PS_HP,
	PS_MP,
	PS_HPDRAIN,
	PS_MPDRAIN,
	PS_ARMOR,
	PS_DEBUF,
	PS_STUN,
	PS_SKILL,
	PS_WEAPONDMG,
	PS_DMGSKILLMOD,
	PS_DMGSKILLADD,
	PS_ARMORMOD,
	PS_PARRY,
	PS_PARRYMOD,
	PS_DEBUFREGIST,
	PS_DMG,

	//허리와 신발이 더해 놓는 값. 이것 자체가 체력은 아니다.
	//
	//RefreshStat 의 "체력 결정" 이 HERO_HP_PER_ARMOR 배로 부풀려 PS_HP 에
	//더한다. 부위마다 그 자리에서 바로 더하면 계수가 여러 군데로 흩어져
	//"장비가 체력의 몇 할인가" 를 만질 수가 없다.
	//
	//ps[] 는 RefreshStat 이 매번 memset 하고 다시 채운다. 저장에도 안 들어
	//가므로 칸을 늘려도 옛 세이브와 어긋나지 않는다.
	PS_HPEQUIP,

	TOTALPLAYERSTAT,

	NOWEAPON = -1,
	ONEHAND = 0,
	TWOHANDS = 1,
	STAFF = 2,

	STR = 1,
	INTEL = 4,
} STATDEF;

#endif
