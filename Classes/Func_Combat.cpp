#include "Core.h"
#include "Func.h"
#include "Data.h"

// Stat Calculating
void InitStat(OBJECT* pObj)
{
	pObj->lv = 1;
	pObj->ap = 5;
	pObj->sp = 0;

	switch (pObj->type) {
	case ROBIN:
		pObj->stat[STAT_STR] = 5;
		pObj->stat[STAT_VIT] = 5;
		pObj->stat[STAT_AGI] = 5;
		pObj->stat[STAT_INT] = 5;
		break;
	case DIANA:
		pObj->stat[STAT_STR] = 5;
		pObj->stat[STAT_VIT] = 5;
		pObj->stat[STAT_AGI] = 5;
		pObj->stat[STAT_INT] = 5;
		break;
	case MAXX:
		pObj->stat[STAT_STR] = 5;
		pObj->stat[STAT_VIT] = 5;
		pObj->stat[STAT_AGI] = 5;
		pObj->stat[STAT_INT] = 5;
		break;
	}
}

void RefreshStat(OBJECT* pObj)
{
	int i, j, mod;
	ITEM* it;
	short requireStat[4];
	unsigned char equipped[TOTALEQUIP];
	int obj = GetObjFromPtr(pObj);

	memset(pObj->ps, 0, sizeof(pObj->ps));
	memset(pObj->immune, 0, sizeof(pObj->immune));
	memset(pObj->setIndex, EMPTY, sizeof(pObj->setIndex));
	memset(pObj->setCount, 0, sizeof(pObj->setCount));
	memset(equipped, 0, sizeof(equipped));

	pObj->decreaseHp = 0;
	pObj->minusDrain = 0;
	extraArmor = 0;

	//기본 스탯 계산

	for (i = 0; i < 4; i++) {
		requireStat[i] = pObj->stat[STAT_STR + i];
	}

	i = 0;

	do {
		//요구치 관련 스탯 업데이트
		for (j = 0; j < 4; j++)
			pObj->ps[PS_STR + j] += UpDiv(requireStat[j] * (100 + GetSkillValue(obj, pObj->type * 30 + j)), 100);

		switch (pObj->type) {
		case ROBIN:
			if (obj < TOTALOBJECT) {
				//지구전 : INT가 높을수록 VIT 상승
				if (pObj->skillLv[SKILL_ROBIN5])
					pObj->ps[PS_VIT] += UpDiv(requireStat[3] * GetSkillValue(obj, SKILL_ROBIN5), 100);
			}
			break;
		case DIANA:
			if (obj < TOTALOBJECT) {
				//집중력유지 : STR이 높을수록 INT 상승
				if (pObj->skillLv[SKILL_DIANA5])
					pObj->ps[PS_INT] += UpDiv(requireStat[0] * GetSkillValue(obj, SKILL_DIANA5), 100);
			}
			break;
		case MAXX:
			if (obj < TOTALOBJECT) {
				//탄력성 : VIT 높을수록 AGI 상승
				if (pObj->skillLv[SKILL_MAXX5])
					pObj->ps[PS_AGI] += UpDiv(requireStat[1] * GetSkillValue(obj, SKILL_MAXX5), 100);
			}
			if (obj < TOTALOBJECT) {
				//효율적사고 : INT가 높을수록 AGI가 올라감
				if (pObj->skillLv[SKILL_MAXX6])
					pObj->ps[PS_AGI] += UpDiv(requireStat[3] * GetSkillValue(obj, SKILL_MAXX6), 100);
			}
			break;
		}

		//기본 아이템 스탯 계산
		it = &pObj->equip[i];

		if (equipped[i] == false && it->type != EMPTY && EquipCheck(pObj, &pObj->equip[i])) {
#ifdef SETITEM
			if (it->grade == GRADE_SET)
				pObj->setIndex[i] = it->set;
#endif

			if (i == EQUIP_NECK && neckOption[it->detail * NECKOPTIONDATASIZE] < EMPTY)
				pObj->ps[neckOption[it->detail * NECKOPTIONDATASIZE]] += pObj->equip[EQUIP_NECK].value;

			for (j = 0, mod = 100; j < TOTALOPTION; j++) {
				int* tPtr = &it->option[j][0];

				if (*tPtr == EMPTYINT)
					continue;

				if (optionStat[*tPtr] >= 0)
					pObj->ps[optionStat[*tPtr]] += (*tPtr >= SUFFIX_HPDECREASE) ? -*(tPtr + 1) : *(tPtr + 1);

				switch (*tPtr) {
				case PREFIX_STR:
				case PREFIX_AGI:
				case PREFIX_VIT:
				case PREFIX_INT:
					requireStat[optionStat[*tPtr] - PS_STR] += *(tPtr + 1);
					break;
				case SUFFIX_MINUSINT:
					requireStat[STAT_INT] -= *(tPtr + 1);
					break;
				case SUFFIX_MINUSSTR:
					requireStat[STAT_STR] -= *(tPtr + 1);
					break;
				case SUFFIX_MINUSAGI:
					requireStat[STAT_AGI] -= *(tPtr + 1);
					break;
				case PREFIX_ARMOR:
					mod += *(tPtr + 1);
					break;
				case SUFFIX_STAT:
					pObj->ps[PS_STR] += *(tPtr + 1);
					pObj->ps[PS_VIT] += *(tPtr + 1);
					pObj->ps[PS_AGI] += *(tPtr + 1);
					pObj->ps[PS_INT] += *(tPtr + 1);

					requireStat[STAT_STR] += *(tPtr + 1);
					requireStat[STAT_VIT] += *(tPtr + 1);
					requireStat[STAT_AGI] += *(tPtr + 1);
					requireStat[STAT_INT] += *(tPtr + 1);
					break;
				case SUFFIX_ALLREGIST:
					pObj->ps[PS_FIRE] += *(tPtr + 1);
					pObj->ps[PS_FROST] += *(tPtr + 1);
					pObj->ps[PS_THUNDER] += *(tPtr + 1);
					pObj->ps[PS_HOLY] += *(tPtr + 1);
					pObj->ps[PS_DARK] += *(tPtr + 1);
					break;
				case SUFFIX_POISON_IMMUNE:
					pObj->immune[POISON] = 1;
					break;
				case SUFFIX_BLIND_IMMUNE:
					pObj->immune[BLIND] = 1;
					break;
				case SUFFIX_SLOW_IMMUNE:
					pObj->immune[SLOW] = 1;
					break;
				case SUFFIX_CURSE_IMMUNE:
					pObj->immune[CURSE] = 1;
					break;
				case SUFFIX_STUN_IMMUNE:
					pObj->immune[STUN] = 1;
					break;
				case SUFFIX_ALWAYSCURSE:
					pObj->alwaysCurse = true;
					break;
				case SUFFIX_HPDECREASE:
					pObj->decreaseHp += *(tPtr + 1);
					break;
				case SUFFIX_MINUSDRAIN:
					pObj->minusDrain += *(tPtr + 1);
					break;
				case SUFFIX_MINUSREGIST:
					pObj->ps[PS_FIRE] -= *(tPtr + 1);
					pObj->ps[PS_FROST] -= *(tPtr + 1);
					pObj->ps[PS_THUNDER] -= *(tPtr + 1);
					pObj->ps[PS_HOLY] -= *(tPtr + 1);
					pObj->ps[PS_DARK] -= *(tPtr + 1);
					break;
				}
			}

			//방어구 합산
			if (i > EQUIP_WEAPON && i < EQUIP_NECK) {
				if (it->cooldown) {
					if (it->value < 10)
						pObj->ps[PS_ARMOR] += RoundDiv((it->value + it->cooldown) * mod, 100);
					else
						pObj->ps[PS_ARMOR] += RoundDiv(RoundDiv(it->value * (100 + it->cooldown * 10), 100) * mod, 100);
				}
				else
					pObj->ps[PS_ARMOR] += RoundDiv(it->value * mod, 100);


				extraArmor += it->detail + 1;
			}

			RefreshStat_Fuck(pObj, it, i);

			equipped[i] = it->detail + 1;

			i = -1;
		}

		i++;
	} while (i < TOTALEQUIP);


	for (i = 0; i < TOTALEQUIP; i++) {

		if (pObj->equipImg[i] != equipped[i]) {
			pObj->equipImg[i] = equipped[i];
		}
	}

#ifdef SETITEM
	//착용중인 세트 입력 및 적용시킬 세트 지정
	for (i = 0, mod = 0; i < TOTALEQUIP; i++) {
		if (pObj->setIndex[i] != EMPTY) {
			for (j = 0; j < TOTALEQUIP; j++) {
				if (pObj->equip[j].grade == GRADE_SET && pObj->equip[j].set == pObj->setIndex[i])
					pObj->setCount[i]++;
			}
		}
	}

	//지정된 세트효과 추가
	for (i = 0, mod = 0; i < TOTALEQUIP; i++) {
		for (j = 0; j < i; j++) {
			if (pObj->setIndex[i] == pObj->setIndex[j])
				break;
		}

		//착용 세트 갯수가 한개 이상이라면
		if (i == j && pObj->setIndex[i] != EMPTY && pObj->setCount[i] > 1) {
			const int* ucPtr = &setOption[(pObj->setIndex[i] % 100) * SETOPTIONDATASIZE];

			for (j = 0; *(ucPtr + 1) != EMPTY && *ucPtr <= pObj->setCount[i] && j < 6; j++, ucPtr += 3) {
				if (*(ucPtr + 1) == PREFIX_ARMOR)
					pObj->ps[PS_ARMORMOD] += *(ucPtr + 2);
				else if (*(ucPtr + 1) == SUFFIX_STAT) {
					pObj->ps[PS_STR] += *(ucPtr + 2);
					pObj->ps[PS_VIT] += *(ucPtr + 2);
					pObj->ps[PS_AGI] += *(ucPtr + 2);
					pObj->ps[PS_INT] += *(ucPtr + 2);
				}
				else if (*(ucPtr + 1) == SUFFIX_ALLREGIST) {
					pObj->ps[PS_FIRE] += *(ucPtr + 2);
					pObj->ps[PS_FROST] += *(ucPtr + 2);
					pObj->ps[PS_THUNDER] += *(ucPtr + 2);
					pObj->ps[PS_HOLY] += *(ucPtr + 2);
					pObj->ps[PS_DARK] += *(ucPtr + 2);
				}
				else
					pObj->ps[optionStat[*(ucPtr + 1)]] += *(ucPtr + 2);
			}
		}
	}

#endif

	RefreshStat_Sub(pObj);


}

void RefreshStat_Fuck(OBJECT* pObj, ITEM* it, int i)
{
	int j;

	if (i > EQUIP_WEAPON && i < EQUIP_NECK && it->type % 3 == pObj->type) {
		switch (pObj->type) {
		case ROBIN:
			pObj->ps[PS_PIERCE] += 5;
			break;
		case DIANA:
			pObj->ps[PS_CRITICAL] += 5;
			break;
		case MAXX:
			pObj->ps[PS_EXTRA] += 5;
			break;
		}
	}

	for (j = 0; j < 6; j++) {
		if (it->socket[j] != EMPTYINT) {
			switch (it->socket[j] % 10) {
			case ITEM_GEM_RUBY:
				pObj->ps[PS_FIRE] += (it->socket[j] / 10 + 2);
				break;
			case ITEM_GEM_SAPPHIRE:
				pObj->ps[PS_FROST] += (it->socket[j] / 10 + 2);
				break;
			case ITEM_GEM_AMETHYST:
				pObj->ps[PS_THUNDER] += (it->socket[j] / 10 + 2);
				break;
			case ITEM_GEM_DIAMOND:
				pObj->ps[PS_HOLY] += (it->socket[j] / 10 + 2);
				break;
			case ITEM_GEM_PERL:
				pObj->ps[PS_DARK] += (it->socket[j] / 10 + 2);
				break;
			case ITEM_GEM_EMERALD:
				pObj->ps[PS_ARMOR] += (it->socket[j] / 10 + 2) * 2;
				break;
			}
		}
	}
}

void RefreshStat_Sub(OBJECT* pObj)
{
	int i;
	int obj = GetObjFromPtr(pObj);
	int psHp, psDmg;


	for (i = 0; i < 5; i++)
		pObj->ps[PS_FIRE + i] = Min(200, pObj->ps[PS_FIRE + i]);

	//스킬효과
	RefreshSkill(pObj);

	// 업적에 반지효과는 적용시키지 않음. 패시브 아이템이나 아이템옵션은 적용됨

	//강화효과
	RefreshBuff(pObj);

	//체력 결정
	pObj->ps[PS_HP] += (pObj->ps[PS_VIT] * VIT_HP + pObj->lv * LVUP_HP + 15);

	//마력 결정
	pObj->ps[PS_MP] += pObj->ps[PS_INT] * INT_MP + pObj->lv * LVUP_MP;

	//생명력강화 적용
	if (pObj->skillLv[SKILL_COMMON_ROBIN5 + pObj->type * TOTALCHARSKILL] > 0) {
		if (obj < TOTALOBJECT)
			pObj->ps[PS_HP] = RoundDiv((100 + GetSkillValue(obj, SKILL_COMMON_ROBIN5 + pObj->type * TOTALCHARSKILL)) * pObj->ps[PS_HP], 100);

	}

	//기력강화 적용
	if (pObj->skillLv[SKILL_COMMON_ROBIN6 + pObj->type * TOTALCHARSKILL] > 0) {
		if (obj < TOTALOBJECT)
			pObj->ps[PS_MP] = RoundDiv((100 + GetSkillValue(obj, SKILL_COMMON_ROBIN6 + pObj->type * TOTALCHARSKILL)) * pObj->ps[PS_MP], 100);
	}

	//체력회복속도 결정
	pObj->ps[PS_HPRESTORE] += UpDiv(pObj->ps[PS_VIT], 4);

	//마력회복속도 결정
	pObj->ps[PS_MPRESTORE] += (UpDiv(pObj->ps[PS_INT], 10) + 1);

	//체력보정
	pObj->hp = Min(pObj->hp, pObj->ps[PS_HP]);
	pObj->mp = Min(pObj->mp, pObj->ps[PS_MP]);

	if (pObj->ps[PS_ARMOR] < 0)
		pObj->ps[PS_ARMOR] = 0;

	if (pObj->ps[PS_HP] < 0)
		pObj->ps[PS_HP] = 1;

	if (pObj->ps[PS_MP] < 0)
		pObj->ps[PS_MP] = 1;

	for (i = 0; i < 4; i++) {
		if (pObj->ps[PS_STR + i] < 0)
			pObj->ps[PS_STR + i] = 0;
	}

	for (i = 0; i < 5; i++) {
		if (pObj->ps[PS_FIRE + i] < 0)
			pObj->ps[PS_FIRE + i] = 0;

		//@@ 상마다 보정해주기
		switch (PS_FIRE + i) {
		case PS_FIRE:
			if (robin.statue[ITEM_STATUE_FLAME])
				pObj->ps[PS_FIRE + i] = Min(200, pObj->ps[PS_FIRE + i] + 10);
			break;
		case PS_FROST:
			if (robin.statue[ITEM_STATUE_ICE])
				pObj->ps[PS_FIRE + i] = Min(200, pObj->ps[PS_FIRE + i] + 10);
			break;
		case PS_THUNDER:
			if (robin.statue[ITEM_STATUE_THUNDER])
				pObj->ps[PS_FIRE + i] = Min(200, pObj->ps[PS_FIRE + i] + 10);
			break;
		case PS_HOLY:
			if (robin.statue[ITEM_STATUE_SUN])
				pObj->ps[PS_FIRE + i] = Min(200, pObj->ps[PS_FIRE + i] + 10);
			break;
		case PS_DARK:
			if (robin.statue[ITEM_STATUE_DIMENSION])
				pObj->ps[PS_FIRE + i] = Min(200, pObj->ps[PS_FIRE + i] + 10);
			break;
		}
	}

	//레벨업 기준으로 올려주기

}

void RefreshSkill(OBJECT* pObj)
{
	int i;
	int obj = GetObjFromPtr(pObj);

	//각종 패시브 스킬 적용
	//공통스킬
	for (i = 0; i < 7; i++) {
		if (skillToStat[i] >= 0 && pObj->skillLv[pObj->type * 30 + i + SKILL_COMMON_ROBIN7])
			pObj->ps[skillToStat[i]] += GetSkillValue(obj, pObj->type * 30 + i + SKILL_COMMON_ROBIN7);
	}

	switch (pObj->type) {
	case ROBIN:
		//로빈 패시브
		//검술숙련 : 관통 발생 확률 상승
		if (pObj->skillLv[SKILL_ROBIN1])
			pObj->ps[PS_PIERCE] += GetSkillValue(obj, SKILL_ROBIN1);

		//긴급방어 : 방어 발동 확률이 올라감(1레벨이면 방어 발동이 시작, 점점 확률 상승)
		if (pObj->skillLv[SKILL_ROBIN2]) {
			pObj->ps[PS_PARRY] += GetSkillValue(obj, SKILL_ROBIN2);
			pObj->ps[PS_PARRYMOD] = 20;
		}

		//방어숙련 : 방어 발동시 경감되는 데미지 퍼센트 상승
		if (pObj->skillLv[SKILL_ROBIN3])
			pObj->ps[PS_PARRYMOD] = GetSkillValue(obj, SKILL_ROBIN3);

		//면역력 : 상태이상에 대한 저항력 상승
		if (pObj->skillLv[SKILL_ROBIN4])
			pObj->ps[PS_DEBUFREGIST] += GetSkillValue(obj, SKILL_ROBIN4);

		////지구전 : INT가 높을수록 VIT 상승
		//if (pObj->skillLv[SKILL_ROBIN5])
		//	pObj->ps[PS_VIT] += UpDiv(pObj->ps[PS_INT], GetSkillValue(obj, SKILL_ROBIN5));
		break;
	case DIANA:
		//디아나 패시브
		//사격숙련 : 기절공격이 발생할 확률이 상승
		if (pObj->skillLv[SKILL_DIANA2])
			pObj->ps[PS_STUN] += GetSkillValue(obj, SKILL_DIANA2);

		////집중력유지 : STR이 높을수록 INT 상승
		//if (pObj->skillLv[SKILL_DIANA5])
		//	pObj->ps[PS_INT] += UpDiv(pObj->ps[PS_STR], GetSkillValue(obj, SKILL_DIANA5));
		break;
	case MAXX:

		//관통력숙련 : 적을 공격했을 때 부메랑의 판정이 남아있을 확률이 상승한다.
		if (pObj->skillLv[SKILL_MAXX1])
			pObj->ps[PS_PIERCE] += GetSkillValue(obj, SKILL_MAXX1);

		//연속공격 : 추가 공격 확률 증가
		if (pObj->skillLv[SKILL_MAXX3])
			pObj->ps[PS_EXTRA] += GetSkillValue(obj, SKILL_MAXX3);

		//탄력성 : VIT 높을수록 AGI 상승
		//if (pObj->skillLv[SKILL_MAXX5])
		//	pObj->ps[PS_AGI] += UpDiv(pObj->ps[PS_VIT], GetSkillValue(obj, SKILL_MAXX5));

		//효율적사고 : INT가 높을수록 AGI가 올라감
		//if (pObj->skillLv[SKILL_MAXX6])
		//	pObj->ps[PS_AGI] += UpDiv(pObj->ps[PS_INT], GetSkillValue(obj, SKILL_MAXX6));
		break;
	}

	pObj->ps[PS_DEBUF] = Min(75, pObj->ps[PS_DEBUF]);
	pObj->ps[PS_DELAY] = Min(75, pObj->ps[PS_DELAY]);
	pObj->ps[PS_ARMOR] += pObj->ps[PS_AGI];
	pObj->ps[PS_ARMOR] += pObj->ps[PS_STR] * 3;
	pObj->ps[PS_CRITICAL] += RoundDiv(pObj->ps[PS_AGI], 20);
	pObj->ps[PS_EVASION] += RoundDiv(pObj->ps[PS_AGI], 20);
	pObj->ps[PS_HIT] += RoundDiv(pObj->ps[PS_AGI], 20);
	pObj->ps[PS_SKILLDMG] += RoundDiv(pObj->ps[PS_INT] * 3, 4);
	pObj->ps[PS_CRITDMG] += RoundDiv(pObj->ps[PS_INT] * 3, 4);
	pObj->ps[PS_FIRE] += RoundDiv(pObj->ps[PS_INT], 4);
	pObj->ps[PS_FROST] += RoundDiv(pObj->ps[PS_INT], 4);
	pObj->ps[PS_THUNDER] += RoundDiv(pObj->ps[PS_INT], 4);
	pObj->ps[PS_HOLY] += RoundDiv(pObj->ps[PS_INT], 4);
	pObj->ps[PS_DARK] += RoundDiv(pObj->ps[PS_INT], 4);

	//방어증가 스킬에 따라서 방어력 결정
	pObj->ps[PS_ARMOR] = RoundDiv(pObj->ps[PS_ARMOR] * (100 + pObj->ps[PS_ARMORMOD]), 100);

	//무기의 공격력 계산
	//소지아이템에 따라서 기본 공격력 결정

	if (pObj->equip[EQUIP_WEAPON].type != EMPTY) {
		pObj->ps[PS_WEAPONDMG] = pObj->equip[EQUIP_WEAPON].value;

		//무기강화레벨을 적용한다.
		if (pObj->equip[EQUIP_WEAPON].cooldown) {
			if (pObj->equip[EQUIP_WEAPON].value < 10)
				pObj->ps[PS_WEAPONDMG] += pObj->equip[EQUIP_WEAPON].cooldown;
			else
				pObj->ps[PS_WEAPONDMG] = RoundDiv(pObj->ps[PS_WEAPONDMG] * (100 + pObj->equip[EQUIP_WEAPON].cooldown * 10), 100);
		}
	}
	else
		pObj->ps[PS_WEAPONDMG] = pObj->lv;

	//무기옵션 + 모든장비의 소켓옵션까지 계산된 공격력
	pObj->ps[PS_DMGMOD] += 100;
	pObj->ps[PS_WEAPONDMG] = RoundDiv(pObj->ps[PS_WEAPONDMG] * pObj->ps[PS_DMGMOD], 100) + pObj->ps[PS_DMGADD] + pObj->ps[PS_DMGSKILLADD];

	//스킬 및 스탯에 의한 공격력 증가는 무기공격력 계산 후에 증가시켜준다.
	//힘에 의한 공격력 증가. 힘 1당 1%의 공격력이 증가한다.
	//pObj->ps[PS_WEAPONDMG] = pObj->ps[PS_WEAPONDMG] * (100 + pObj->ps[PS_STR] * 100 / 1000 + pObj->ps[PS_AGI] * 50 / 1000 + pObj->ps[PS_INT] * 50 / 1000) / 100;
	pObj->ps[PS_DMGSKILLMOD] += pObj->ps[PS_STR] * 3 / 4;
	//
	//캐릭터별로 밸런스 보정을 위한 str, int, agi 값에 따른 공격력 상승
	switch (pObj->type) {
	case ROBIN:
		break;
	case DIANA:
		pObj->ps[PS_DMGSKILLMOD] += pObj->ps[PS_INT] / 3;
		break;
	case MAXX:
		pObj->ps[PS_DMGSKILLMOD] += pObj->ps[PS_AGI] / 3;
		break;
	}

	//패시브스킬을 적용시킨 로빈의 공격력
	pObj->ps[PS_DMG] = RoundDiv(pObj->ps[PS_WEAPONDMG] * (pObj->ps[PS_DMGSKILLMOD] + 100), 100);
}

void RefreshBuff(OBJECT* pObj)
{
	int ringValue = pObj->equip[EQUIP_RING].value;
	int dmgMod = 100;
	int armorMod = 100;
	int obj = GetObjFromPtr(pObj);

	//캐릭터별 액티브 강화스킬 적용
	switch (pObj->type) {
		//로빈
	case ROBIN:
		//방어태세 : 일정시간 VIT 상승
		if (pObj->buff[INC_VIT])
			pObj->ps[PS_VIT] = RoundDiv(pObj->ps[PS_VIT] * (100 + GetSkillValue(obj, SKILL_ROBIN13)), 100);
		break;
		//디아나
	case DIANA:
		//흥분고조 : 방어력 저하 공격력 상승
		if (pObj->buff[BERSERK]) {
			//공격력 상승
			dmgMod += GetSkillValue(obj, SKILL_DIANA14);
			//방어력 하락
			pObj->ps[PS_ARMOR] = RoundDiv(pObj->ps[PS_ARMOR] * (100 - berserkEtcData[GetSkillLv(obj, SKILL_DIANA14) - 1]), 100);
		}

		//필살집중 : 크리 상승
		if (pObj->buff[INC_CRITICAL])
			pObj->ps[PS_CRITICAL] += GetSkillValue(obj, SKILL_DIANA16);

		//파마의직격 : 일정시간 적 방어 무시
		if (pObj->buff[INC_IGNORE])
			pObj->ps[PS_IGNORE] += GetSkillValue(obj, SKILL_DIANA17);

		//흡마의 마탄 : 공격시 MP 흡수 -> 공격시 HP 흡수
		if (pObj->buff[MPDRAIN])
			pObj->ps[PS_MPDRAIN] += GetSkillValue(obj, SKILL_DIANA15);
		break;
		//맥스
	case MAXX:
		//현란무도 : 일정시간 회피율 증가
		if (pObj->buff[INC_EVASION])
			pObj->ps[PS_EVASION] += GetSkillValue(obj, SKILL_MAXX15);

		//혼신분리 : 기절 확률 상승
		if (pObj->buff[INC_STUN])
			pObj->ps[PS_STUN] += GetSkillValue(obj, SKILL_MAXX17);

		//블러드헌트 : 적 공격시 HP 회복
		//블러드헌트 : 관통 100% 타이밍 길게
		if (pObj->buff[HPDRAIN])
			pObj->ps[PS_HPDRAIN] += GetSkillValue(obj, SKILL_MAXX14);
		break;
	}

	//반지 강화버프 적용
	//공격력 증가 : 폭주의 반지
	if (pObj->buff[INC_DAMAGE_RING])
		dmgMod += ringValue;

	//방어도 증가 : 골렘의 반지
	if (pObj->buff[INC_DEFENSE_RING])
		pObj->ps[PS_ARMOR] += ringValue;

	//회피 증가 : 광대의 반지
	if (pObj->buff[INC_EVASION_RING])
		pObj->ps[PS_EVASION] += ringValue;

	//관통 증가 : 원한의 반지
	if (pObj->buff[INC_PIERCE_RING])
		pObj->ps[PS_PIERCE] += ringValue;

	//적중 증가 : 신념의 반지
	if (pObj->buff[INC_HIT_RING])
		pObj->ps[PS_HIT] += ringValue;

	//기절 공격 증가 : 광포의 반지
	if (pObj->buff[INC_STUN_RING])
		pObj->ps[PS_STUN] += ringValue;

	//치명타 증가 : 승자의 반지
	if (pObj->buff[INC_CRITICAL_RING])
		pObj->ps[PS_CRITICAL] += ringValue;

	//치명타 데미지 증가 : 궁극의 반지
	if (pObj->buff[INC_CRITDMG_RING])
		pObj->ps[PS_CRITDMG] += ringValue;

	//적 방어도 무시 증가 : 차원의 반지
	if (pObj->buff[INC_IGNORE_RING])
		pObj->ps[PS_DEFENSE] += ringValue;

	//경험치 획득 증가 : 행운의 반지
	if (pObj->buff[INC_EXP_RING])
		pObj->ps[PS_EXPMOD] += ringValue;

	//물리데미지 흡수 증가 : 회생의 반지
	if (pObj->buff[INC_ABSORB_RING])
		pObj->ps[PS_ABSORB] += ringValue;

	//투기장 강화의 비약 적용
	if (pObj->buff[INC_DAMAGE_ARENA])
		dmgMod += 30;

	//투기장 인내의 비약 적용
	if (pObj->buff[INC_DEFENSE_ARENA])
		armorMod += 50;

	//투기장 마법의 비약
	if (pObj->buff[INC_SKILL_ARENA])
		pObj->ps[PS_SKILLDMG] += 50;

	//패시브스킬을 적용시킨 로빈의 공격력
	pObj->ps[PS_DMG] = RoundDiv(pObj->ps[PS_DMG] * dmgMod, 100);

	//방어력 적용
	pObj->ps[PS_ARMOR] = RoundDiv(pObj->ps[PS_ARMOR] * armorMod, 100);
}

void RefreshQuestTime(void)
{
	int i;
	//생성시간과 현재 시간을 비교하여 그 차이만큼 시간을 배준다.
	if ((long)(currentTimeStamp - robin.questTimeStamp) >= questInfo[robin.quest * QUESTINFODATASIZE + 4]) {
		robin.questTimeStamp = MC_knlCurrentTimeStamp();
		robin.quest++;
		robin.subQuest = 0;
	}
}

void RefreshHeartTime(void)
{
	int i;

	if (robin.heart < GetInitHeart()) {
		if ((long)(currentTimeStamp - robin.heartTimeStamp) >= HEARTTIME) {
			if (robin.heart < GetInitHeart()) {
				robin.heart += GetHeartAmount() * ((long)(currentTimeStamp - robin.heartTimeStamp) / HEARTTIME);
				if (robin.heart > GetInitHeart())
					robin.heart = GetInitHeart();
			}
			robin.heartTimeStamp += (long)(currentTimeStamp - robin.heartTimeStamp) / HEARTTIME * HEARTTIME;
			SaveGame();
		}
	}
	else {
		robin.heartTimeStamp = currentTimeStamp;
	}
	//하트가 베팅된 금액보다 작으면
	if (autoPlay == true && robin.heart < GetBetHeart(ao[PLAYER].equip[EQUIP_WEAPON].detail, ao[PLAYER].equip[EQUIP_WEAPON].grade, bet)) {
		autoPlay = false;
		autoFrame = -1;
		SaveGame();
	}
}

void RefreshEnemyTime(void)
{
	int i;

	//체력이 가득차 있으면 공격하지 않는다.
	if (drawHandle == MD_PLAY || drawHandle == MD_BATTLE) {
		for (i = ENEMY; i < NEUTRAL; i++)
			if (ao[i].active == true && ao[i].dead == false && ao[i].mom == i) {
				if (ao[i].hp == ao[i].maxhp)
					ao[i].coolTime = MC_knlCurrentTimeStamp();
			}
	}
}

void RefreshCalendarTime(void)
{
	int i;

	for (i = 0; i < WEEK; i++) {
		//현재 시간이 찾으면 보상을 얻을 수 있는 곳
		if (robin.calendarDayStatus[i] == CALENDAR_REWARDSTATUS_NOTYET) {
			if (86400 - (MC_knlCurrentTimeStamp() - robin.calendarTimeStamp) <= 0)
				robin.calendarDayStatus[i] = CALENDAR_REWARDSTATUS_CANREWARD;

		}
	}
}

// Combat Formula
//특정 레벨 기준으로 그 다음 레벨에 도달하기 위한 총 경험치를 구한다.

long long NextExp(int lv)
{
	int i;
	int temp = 0;
	long long rt = 0;

	for (i = 0; i < lv + 1; i++)
		rt += lvUpExp[i];

	return rt;
}

//현재 인챈트인 슬롯에 설정되어 있는 장비들로부터 
//1. 인벤토리에서 선택했을 때 행동양식
//- 아직 슬롯이 가득차지 않았을 때 선택마크가 없는 장비를 선택하면 슬롯의 빈곳에 넣어준다.
//- 아직 슬롯이 가득차지 않았을 때 선택마크가 있는 장비를 선택하면 슬롯에서 빼주고 뒤에서부터 땡겨서 빈곳을 채워준다.
//- 이미 슬롯이 가득차 있을때 선택마크가 없는 장비를 선택하면 들어갈 곳이 없기 때문에 아무 반응을 하지 않는다.
//- 이미 슬롯이 가득차 있을 때 선택마크가 있는 장비를 선택하면 해당 장비를 비우고 뒤에서부터 땡겨서 채워준다.

//2. 슬롯에서 선택햇을 때 행동양식이 필요한가?
//- 슬롯에서 선택했을 때는 아래 인벤토리를 해당 아이템에 포커싱이 가도록 페이지를 이동시키고 포커싱 표시를 해주면 될듯 하다.
//- 거기서 한번 더 누르던 하는것은 자유
int GetExpFromEnchantSlot(void)
{
	int i, exps = 0;
	ITEM* it;
	ITEM* itSelected;

	for (i = 0; i < INVEN_HCNT; i++) {
		if (enchantSlot[i] != SLOTEMPTY) {
			it = GetItemPtr(invenRecipe[enchantSlot[i]]);
			switch (it->type) {
			case ITEM_RING:
			case ITEM_NECK:
				exps += itemMaterialExpAcce[it->cooldown];
				break;
			default:
				exps += itemMaterialExp[itemLevelLimit[2 * it->detail + 1] + it->cooldown];
				break;
			}
		}
	}

	itSelected = GetItemPtr(menuItem - 1);

	if (exps > NextExpEquip(itSelected, itemLevelLimit[2 * itSelected->detail]))
		exps = NextExpEquip(itSelected, itemLevelLimit[2 * itSelected->detail]);

	return exps;
}

//골드
int GetGoldFromEnchantSlot(void)
{
	int gold = 0;
	ITEM* it = GetItemPtr(menuItem - 1);
	int nextExp, nextLv, totalExp;

	totalExp = it->exp + GetExpFromEnchantSlot();
	nextExp = NextExpEquip(it, NextLvEquip(it, it->exp + GetExpFromEnchantSlot()) + 1);
	nextLv = NextLvEquip(it, nextExp);
	gold = GetExpFromEnchantSlot();

	if (nextLv > itemLevelLimit[2 * it->detail]) {
		nextLv = itemLevelLimit[2 * it->detail];
		nextExp = NextExpEquip(it, nextLv);
		totalExp = nextExp;
		gold = totalExp - it->exp;
	}

	return gold;
}

//골드
int GetGoldFromSocketSlot(void)
{
	int i, gold = 0;

	for (i = 0; i < INVEN_HCNT; i++) {
		if (enchantSlot[i] != SLOTEMPTY) {
			gold += gemPrice[GetItemPtr(enchantSlot[i])->grade];
		}
	}

	return gold;
}

void LevelUpEquip(ITEM * it, int getExp)
{
	int tempLevel;
	int i, j = 0;

	tempLevel = it->cooldown;
	it->exp += getExp;

	while (it->exp >= NextExpEquip(it, it->cooldown)) {
		it->cooldown++;
		if (it->cooldown > itemLevelLimit[2 * it->cooldown])
			it->cooldown = itemLevelLimit[2 * it->cooldown];
	}

	//it->value = MakeItemValue(it->type, it->detail, it->grade, it->cooldown);

	for (i = ROBIN; i < TOTALPLAYER; i++)
		RefreshStat(&ao[i]);

	PlayMusic(M_LEVELUP);
}

//장비의 특정 레벨까지 필요한 경험치를 합산해서 반환
int NextExpEquip(ITEM* it, int lv)
{
	int i, needExp = 0;

	for (i = 0; i < lv - 1; i++) {
		switch (it->type) {
		case ITEM_RING:
		case ITEM_NECK:
			needExp += itemExpAcce[i];
			break;
		default:
			needExp += itemExp[itemLevelLimit[it->detail * 2 + 1] + i];
			break;
		}
	}

	return needExp;
}

//현재 주어진 경험치로 어디까지 레벨을 올릴 수 있는지 반환
int NextLvEquip(ITEM* it, int getExp)
{
	int tempLevel, tempExp;

	tempLevel = 0;
	tempExp = getExp;

	while (tempExp > 0) {
		switch (it->type) {
		case ITEM_RING:
		case ITEM_NECK:
			tempExp -= itemExpAcce[tempLevel];
			break;
		default:
			tempExp -= itemExp[itemLevelLimit[it->detail * 2 + 1] + tempLevel];
			break;
		}
		if (tempExp >= 0)
			tempLevel++;
	}

	return tempLevel + 1;
}

int checkEnchantSlotNum(int idx)
{
	int i;
	for (i = 0; i < INVEN_HCNT; i++) {
		if (enchantSlot[i] == idx) {
			return i;
		}
	}

	return SLOTEMPTY;
}

int checkSocketSlotNum(int idx, int target)
{
	int i, startEmptySlot = checkExistSocketSlotCnt(target);
	ITEM* it = GetItemPtr(target);

	for (i = startEmptySlot; i < it->count; i++) {
		if (enchantSlot[i - startEmptySlot] == idx) {
			return (i - startEmptySlot);
		}
	}

	return SLOTEMPTY;
}

int checkExistSocketSlotCnt(int idx)
{
	int i, j = 0;
	ITEM* it = GetItemPtr(idx);

	for (i = 0; i < it->count; i++) {
		if (it->socket[i] < EMPTYINT) {
			j++;
		}
	}

	return j;
}

int checkEmptySocketSlot(int target)
{
	int i, fillCnt = 0;;
	ITEM* it = GetItemPtr(target);
	for (i = 0; i < it->count; i++) {
		if (enchantSlot[i] == SLOTEMPTY) {
			fillCnt = i;
			break;
		}
	}

	return (checkExistSocketSlotCnt(target) + fillCnt);
}

bool checkSameSocketSlot(int idx, int target)
{
	int i, j = 0;
	int startEmptySlot = checkExistSocketSlotCnt(target);
	bool same = false;
	ITEM* it = GetItemPtr(target);

	for (i = startEmptySlot; i < it->count; i++) {
		if (enchantSlot[i - startEmptySlot] != SLOTEMPTY &&
			enchantSlot[i - startEmptySlot] == idx) {
			same = true;
		}
	}

	return same;
}

int pushEnchantEquip(int idx)
{
	int i;
	for (i = 0; i < INVEN_HCNT; i++) {
		if (enchantSlot[i] == SLOTEMPTY) {
			enchantSlot[i] = idx;
			break;
		}
	}

	return i;
}

int pushSocketSlot(int idx, int target)
{
	int i, startEmptySlot = checkExistSocketSlotCnt(target);
	ITEM* it = GetItemPtr(target);
	for (i = startEmptySlot; i < it->count; i++) {
		if (enchantSlot[i - startEmptySlot] == SLOTEMPTY || i == it->count - 1) {
			enchantSlot[i - startEmptySlot] = idx;
			break;
		}
	}

	return i;
}

int popEnchantEquip(int idx)
{
	int i;
	enchantSlot[idx] = SLOTEMPTY;

	for (i = idx + 1; i < INVEN_HCNT; i++) {
		if (enchantSlot[i] != SLOTEMPTY) {
			enchantSlot[i - 1] = enchantSlot[i];
			enchantSlot[i] = SLOTEMPTY;
		}
	}
	return i;
}

int popSocketSlot(int idx, int target)
{
	int i, startEmptySlot = checkExistSocketSlotCnt(target);
	ITEM* it = GetItemPtr(target);
	enchantSlot[idx] = SLOTEMPTY;

	for (i = idx + 1; i < it->count; i++) {
		if (enchantSlot[i - startEmptySlot] != SLOTEMPTY) {
			enchantSlot[i - 1 - startEmptySlot] = enchantSlot[i - startEmptySlot];
			enchantSlot[i - startEmptySlot] = SLOTEMPTY;
		}
	}
	return i;
}

int GetLevelUpRewardLv(int type, int userLv)
{
	int i;
	int sameRewardCnt = 0;

	for (i = 0; i < userLv; i++) {
		if (levelUpReward[i * 2 + 0] == type) {
			if (levelUpReward[i * 2 + 1] == MAXLV)
				return MAXLV;
			else
				sameRewardCnt++;
		}
	}
#ifdef GAMEDEBUG
	return 1;
#endif
	return sameRewardCnt;
}

void LevelUp(int getExp)
{
	int tempLevel;

	if (robin.lv >= MAXUSERLEVEL)
		return;

	//로빈의 경험치
	tempLevel = robin.lv;
	robin.exps += getExp;

	while (robin.exps >= NextExp(robin.lv)) {
		robin.lv++;
	}

	if (robin.lv != tempLevel) {
		PlayMusic(M_LEVELUP);
		levelUpFrame = 1;

		if (robin.lv == MAXUSERLEVEL)
			robin.exps = NextExp(robin.lv - 1);
	}

	SaveGame();
}


void LevelUpObj(OBJECT* pObj, int getExp)
{
	int tempLevel;
	tempLevel = pObj->lv;
	pObj->exps += getExp;

	//로빈의 경험치
	while (pObj->exps >= NextExp(pObj->lv)) {
		pObj->lv++;
	}

	if (pObj->lv > tempLevel) {
		PlayMusic(M_LEVELUP);
		Vibration();

		pObj->levelUpFrame = 1;
		pObj->invincible = FPS;//잠시 무적

		RefreshStat(pObj);
	}
	SaveGame();
}

void PlusHp(OBJECT* pObj, long long int hp)
{
	if (pObj->hp + hp > pObj->ps[PS_HP])
		hp = pObj->ps[PS_HP] - pObj->hp;
	AddBar(&bar[BAR_PLAYERHP + GetObjFromPtr(pObj)], hp, BARFRAME);
	pObj->hp += hp;
}

void PlusMp(OBJECT* pObj, long long int mp)
{
	pObj->mp = Min(pObj->mp + mp, pObj->ps[PS_MP]);

}

long long int GetAbsorb(OBJECT* pObj, long long int damage)
{
	long long int absorb = pObj->ps[PS_ABSORB];
	long long int wasteMp;
	int obj = GetObjFromPtr(pObj);

	//대미지 감소율을 최대 75%를 넘을수 없다.
	damage = RoundDiv((100 - Min(75, absorb)) * damage, 100);

	//정신소모스킬에 따라 대미지를 감소시킨다.
	if (pObj->buff[BARRIER] && pObj->mp > 0) {
		//줄어들어야 할 엠피와 현재 엠피간의 비율 계산
		wasteMp = damage * GetSkillValue(obj, SKILL_ROBIN14) * barrierEtcData[GetSkillLv(obj, SKILL_ROBIN14) - 1] / 10000;

		if (wasteMp <= pObj->mp) {
			//엠피가 충분하면 공식대로 엠소모
			absorb = GetSkillValue(obj, SKILL_ROBIN14);
			pObj->mp -= wasteMp;
		}
		else {
			//엠피가 충분하지 않으면 비율대로 엠소모
			absorb = RoundDiv(GetSkillValue(obj, SKILL_ROBIN14) * pObj->mp, wasteMp);
			pObj->mp = 0;
		}

		absorb = GetSkillValue(obj, SKILL_ROBIN14);
		return RoundDiv((100 - absorb) * damage, 100);
	}
	else
		return damage;
}

bool CheckSkillAttack(long long int attacker)
{
	//스킬로 인한 공격력 상승을 반영한다.
	int rt = 100 * SKILLPER;
	temp = -1;

	if (attacker < BULLET) {
		if (ao[attacker].attack == 1) {
			return false;
		}
		else if (ao[attacker].flamer) {
			return true;
		}
		else if (ao[attacker].currentSkill >= 0/* && ao[attacker].hotKey[ao[attacker].currentSkill].type == HOTKEY_SKILL*/) {
			//temp = ao[attacker].hotKey[ao[attacker].currentSkill].idx;
			temp = ao[attacker].currentSkill;

			switch (temp) {
			case SKILL_ROBIN7://마구찌르기
			case SKILL_ROBIN12://멸살연참 : 연속기
			case SKILL_DIANA11://킬링존 : 난사
			case SKILL_MAXX7://돌려차기 : 회전, 기절
			case SKILL_ROBIN6://에어크래쉬 : 몹 뛰우기
			case SKILL_ROBIN8://부스트슬래쉬 : 가로로 크게 배기, 기절
			case SKILL_ROBIN9://하이퍼차지 : 돌격공격, 적을 뒤로 날려버림
			case SKILL_ROBIN10://소울크래쉬 : 기절
			case SKILL_ROBIN11://앱솔루트피어스 : 찔러서회전
				return true;
			}
		}
		else
			return false;
	}
	else if (attacker < ENEMY) {
		//각종 액티브 스킬이나 분노, 광기의 폭주 버프시 공격력을 증가시켜준다
		switch (ao[attacker].moveHandler) {
		case BULLETBOOMERANGMOVE:
			switch (ao[attacker].attack) {
			case MAXX_SKILL_SHORT:
			case MAXX_SKILL_AIR://@@사정거리 더 길게, 45도로 수정
			case MAXX_SKILL_CIRCLE:
			case MAXX_SKILL_CAMPING://@@ 사정거리 상관없이 일정데미지 맞게 모두 수정
			case MAXX_SKILL_HORMING:
			case MAXX_SKILL_MEGA:
				return true;
			}
			break;
		case BULLET3WAYMOVE:
		case BULLETLASERMOVE:
		case BULLETBOMBMOVE:
		case BULLETGUIDEDMOVE:
		case BULLETSATELLITEMOVE:
		case BULLETITEMMOVE:
			return true;
		}
	}
	return false;
}

int GetAttackRange(int obj)
{
	int range;
	OBJECT* pObj = &ao[obj];
	ITEM* it;

	if (pObj->type < TOTALCHAR)
		it = &pObj->equip[EQUIP_WEAPON];

	//몬스터의 사정거리도 따져준다.
	if (obj >= ENEMY) {
		range = ao[obj].cx / 2;
	}
	else
	{
		//크류면
		if (obj >= TOTALCHAR && obj < PLAYERALL)
			range = sqrt(DX * DX + DY * DY);
		//스킬이면
		else if (pObj->type < ENEMY_SNAIL) {
			switch (ao[obj].currentSkill) {
			case SKILL_MAXX7:
				range = 2 * TSIZE;
				break;
			default:
				range = (float)attackRange[ao[obj].type] * ao[obj].zoom;
				switch (pObj->type) {
				case ROBIN:
					range += it->detail * 1 * _2X;
					break;
				case DIANA:
					range += it->detail * 2 * _2X;
					break;
				case MAXX:
					range += it->detail * 4 * _2X;
					break;
				}
				break;
			}

		}
		//몬스터면
		else
			range = ao[obj].cx / 2;
	}
	//else if (attackType <= ROULETTE_SKILL) {
	//	range = float(actionCardData[actionCardIdx * ACTIONCARDDATASIZE + 8]) * pObj->zoom;
	//}
	//ROULETTE_MISS
	//else
	//	range = (float)(3 * TSIZE) * pObj->zoom;

	return range;
}

void SetWheel(void)
{
	wheelFrame = 1;
	wheelSpeed = WHEELINITSPEED;
	arrowTouched = 0;
	switch (attackType) {
		//ROULETTE_MISS:
	default:
		wheelMaxSpeed = WHEELMAXSPEED;
		wheelAccel = WHEELINITACCEL;
		break;
	case ROULETTE_COIN:
		wheelMaxSpeed = WHEELMAXSPEED;
		wheelAccel = WHEELINITACCEL;
		break;
	case ROULETTE_EQUIP:
		wheelMaxSpeed = WHEELMAXSPEED;
		wheelAccel = WHEELINITACCEL;
		break;
	case ROULETTE_HEART:
		wheelMaxSpeed = WHEELMAXSPEED;
		wheelAccel = WHEELINITACCEL;
		break;
	case ROULETTE_QUEST:
		wheelMaxSpeed = WHEELMAXSPEED;
		wheelAccel = WHEELINITACCEL;
		break;
	case ROULETTE_BATTLE:
		wheelMaxSpeed = WHEELMAXSPEED;
		wheelAccel = WHEELINITACCEL;
		break;
	case ROULETTE_RAID:
		wheelMaxSpeed = WHEELMAXSPEED;
		wheelAccel = WHEELINITACCEL;
		break;
	case ROULETTE_SKILL:
		wheelMaxSpeed = WHEELMAXSPEED;
		wheelAccel = WHEELINITACCEL;
		break;
	case ROULETTE_SHIELD:
		wheelMaxSpeed = WHEELMAXSPEED;
		wheelAccel = WHEELINITACCEL;
		break;
	}
}

void SetRouletteTime(void)
{
	ROULETTEWHEELTIME = (ao[ao[PLAYER].target].x - ao[PLAYER].x - GetAttackRange(PLAYER)) / GetSpeed(PLAYER) + MOTIONDIV * 2;
	if (ROULETTEWHEELTIME < ROULETTEDIV)
		ROULETTEWHEELTIME = ROULETTEDIV;
}

int GetSpeed(int obj)
{
	int speed;
	int maxSpeed;
	ITEM* it = &ao[obj].equip[EQUIP_BOOTS];

	int realValue;

	speed = dx_walk[ao[obj].type];

	//스피드에 이동속도
	if (it->type == EMPTY)
		realValue = 0;
	else
		realValue = itemUpgradeValue[it->type * TOTAL_COLLECTIONS * (ITEMMAXLEVEL + 1) + it->detail * TOTALGRADE * (ITEMMAXLEVEL + 1) + it->grade * (ITEMMAXLEVEL + 1) + it->cooldown];

	//장비의 픽셀
	speed += realValue;

	//if (ao[obj].x < BATTLEPOSITION_ENEMY_X - GetAttackRange(obj) - speed && ao[ENEMY].hp && ao[obj].dirX == RIGHT)
	//	maxSpeed = (BATTLEPOSITION_ENEMY_X - ao[obj].x - GetAttackRange(obj)) / TOTALROULETTETYPE;
	//else
	//	maxSpeed = speed;

	//if (speed > maxSpeed)
	//	speed = maxSpeed;


	switch (drawHandle) {
	default:
		return speed / MOTIONDIV;
	}
}

int GetRaidSpeed(int targetObj)
{
	int speed;
	int maxSpeed;
	ITEM* it = &ao[PLAYER].equip[EQUIP_BOOTS];
	int realValue;
	int gameStartPosition = BATTLEPOSITION_PLAYER_X;

	if (it->type == EMPTY)
		realValue = 0;
	else
		realValue = itemUpgradeValue[it->type * TOTAL_COLLECTIONS * (ITEMMAXLEVEL + 1) + it->detail * TOTALGRADE * (ITEMMAXLEVEL + 1) + it->grade * (ITEMMAXLEVEL + 1) + it->cooldown];

	speed = dx_walk[ao[PLAYER].type] + realValue;

	if (ao[PLAYER].x < ao[targetObj].x - GetAttackRange(PLAYER) - speed)
		maxSpeed = (ao[targetObj].x - gameStartPosition - GetAttackRange(PLAYER)) / TOTALROULETTETYPE;
	else
		maxSpeed = speed;

	if (speed > maxSpeed)
		speed = maxSpeed;
	return speed;
}

int GetAtk(int attacker)
{
	//스킬로 인한 공격력 상승을 반영한다.
	int rt = 100 * SKILLPER;
	int curSkill = -1;

	if (attacker < BULLET) {
		if (ao[attacker].attack == 1) {
			//if ((ao[attacker].cmf == ROBIN && ao[attacker].attackFrame == 14 + ROBIN_ATTACK_DELAY) || (ao[attacker].cmf == DIANA && ao[attacker].attackFrame == 23 + DIANA_ATTACK_DELAY))
			//	rt = 200;

			//if (ao[attacker].attackFrame == 2)
			//	rt = rt * (10 + ao[attacker].concentrate) / 10;

			goto RESULT;
		}
		else if (ao[attacker].flamer) {
			//rt = 80;
			rt = rt * skillDescMod[10] / 10;
			curSkill = SKILL_DIANA8;
		}
		else if (ao[attacker].currentSkill >= 0/* && ao[attacker].hotKey[ao[attacker].currentSkill].type == HOTKEY_SKILL*/) {
			//curSkill = ao[attacker].hotKey[ao[attacker].currentSkill].idx;
			curSkill = ao[attacker].currentSkill;

			switch (curSkill) {
			case SKILL_ROBIN6://에어크래쉬 : 몹 뛰우기
				//rt = 200;
				rt = rt * skillDescMod[0] / 10;
				break;
			case SKILL_ROBIN7://마구찌르기
				//rt = 70;
				rt = rt * skillDescMod[1] / 10;
				break;
			case SKILL_ROBIN8://부스트슬래쉬 : 가로로 크게 배기, 기절
				//rt = 200;
				rt = rt * skillDescMod[2] / 10;
				break;
			case SKILL_ROBIN9://하이퍼차지 : 돌격공격, 적을 뒤로 날려버림
				//rt = 200;
				rt = rt * skillDescMod[3] / 10;
				break;
			case SKILL_ROBIN10://소울크래쉬 : 기절
				//rt = 200;
				rt = rt * skillDescMod[4] / 10;
				break;
			case SKILL_ROBIN11://앱솔루트피어스 : 찔러서회전
				//rt = 200;
				rt = rt * skillDescMod[5] / 10;
				break;
			case SKILL_ROBIN12://멸살연참 : 연속기
				//rt = 100;
				rt = rt * skillDescMod[6] / 10;
				break;
			case SKILL_DIANA11://킬링존 : 난사
				//rt = 100;
				rt = rt * skillDescMod[13] / 10;
				break;
			case SKILL_MAXX7://돌려차기 : 회전, 기절
				//rt = 100;
				rt = rt * skillDescMod[17] / 10;
				break;
			}
		}
		else
			goto RESULT;
	}
	else if (attacker < ENEMY) {
		//각종 액티브 스킬이나 분노, 광기의 폭주 버프시 공격력을 증가시켜준다
		switch (ao[attacker].moveHandler) {
		case BULLETBOOMERANGMOVE:
			switch (ao[attacker].attack) {
			case MAXX_SKILL_SHORT:
				//rt = 200;
				rt = rt * skillDescMod[18] / 10;
				curSkill = SKILL_MAXX8;
				break;
			case MAXX_SKILL_AIR://@@사정거리 더 길게, 45도로 수정
				//rt = 250;
				rt = rt * skillDescMod[19] / 10;
				curSkill = SKILL_MAXX9;
				break;
			case MAXX_SKILL_CAMPING://@@ 사정거리 상관없이 일정데미지 맞게 모두 수정
				//rt = 100;
				rt = rt * skillDescMod[20] / 10;
				curSkill = SKILL_MAXX10;
				break;
			case MAXX_SKILL_HORMING:
				//rt = 200;
				rt = rt * skillDescMod[21] / 10;
				curSkill = SKILL_MAXX11;
				break;
			case MAXX_SKILL_CIRCLE:
				//rt = 150;
				rt = rt * skillDescMod[22] / 10;
				curSkill = SKILL_MAXX12;
				break;
			case MAXX_SKILL_MEGA:
				//rt = 300;
				rt = rt * skillDescMod[23] / 10;
				curSkill = SKILL_MAXX13;
				break;
			}
			break;
		case BULLET3WAYMOVE:
			//rt = 150;
			rt = rt * skillDescMod[8] / 10;
			curSkill = SKILL_DIANA6;
			break;
		case BULLETLASERMOVE:
			//rt = 100;
			rt = rt * skillDescMod[9] / 10;
			curSkill = SKILL_DIANA7;
			break;
		case BULLETBOMBMOVE:
			//rt = 200;
			rt = rt * skillDescMod[11] / 10;
			curSkill = SKILL_DIANA9;
			break;
		case BULLETGUIDEDMOVE:
			//rt = 100;
			rt = rt * skillDescMod[12] / 10;
			curSkill = SKILL_DIANA10;
			break;
		case BULLETSATELLITEMOVE:
			//rt = 200;
			rt = rt * (skillDescMod[14] + (ao[attacker].frame / (FPS / 5))) / 10;
			curSkill = SKILL_DIANA12;
			break;
		case BULLETITEMMOVE:
			if (ao[attacker].etc)
				rt = 150;
			else
				rt = 100;
			goto RESULT;
		}
	}

	if (curSkill == -1)
		rt = 100;

RESULT:
	return rt;
}

long long int GetMinDmg(OBJECT* pObj)
{
	if (drawHandle == MD_PLAY || drawHandle == MD_BATTLE || drawHandle == MD_RAID || drawHandle == MD_BOSSRAID)
		return pObj->ps[PS_DMG];
	else
		return pObj->equip[EQUIP_WEAPON].value + (itemUpgradeValue[pObj->equip[EQUIP_WEAPON].type * TOTAL_COLLECTIONS * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_WEAPON].detail * TOTALGRADE * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_WEAPON].grade * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_WEAPON].cooldown] - itemUpgradeValue[pObj->equip[EQUIP_WEAPON].type * TOTAL_SWORD * TOTALGRADE * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_WEAPON].detail * TOTALGRADE * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_WEAPON].grade * (ITEMMAXLEVEL + 1) + 0]) + pObj->ps[PS_DMGADD];
}

long long int GetMaxDmg(OBJECT* pObj)
{
	if (drawHandle == MD_PLAY || drawHandle == MD_BATTLE || drawHandle == MD_RAID || drawHandle == MD_BOSSRAID)
		return pObj->ps[PS_DMG] + pObj->equip[EQUIP_WEAPON].subValue - pObj->equip[EQUIP_WEAPON].value;
	else
		return pObj->equip[EQUIP_WEAPON].subValue + (itemUpgradeValue[pObj->equip[EQUIP_WEAPON].type * TOTAL_SWORD * TOTALGRADE * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_WEAPON].detail * TOTALGRADE * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_WEAPON].grade * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_WEAPON].cooldown] - itemUpgradeValue[pObj->equip[EQUIP_WEAPON].type * TOTAL_SWORD * TOTALGRADE * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_WEAPON].detail * TOTALGRADE * (ITEMMAXLEVEL + 1) + pObj->equip[EQUIP_WEAPON].grade * (ITEMMAXLEVEL + 1) + 0]) + pObj->ps[PS_DMGADD];
}

int GetTouchGray(int x, int y)
{
	y -= DY;

	switch (systemKey) {
	case AVK_1:
		if (x == 0 && y == 0)
			return 1;
		break;
	case AVK_2:
		if (x == 38 && y == 0)
			return 1;
		break;
	case AVK_3:
		if (x == 77 && y == 0)
			return 1;
		break;
	case AVK_4:
		if (x == 0 && y == 26)
			return 1;
		break;
	case AVK_5:
		if (x == 160 && y == 38)
			return 1;
		break;
	case AVK_6:
		if (x == 64 && y == 26)
			return 1;
		break;
	case AVK_7:
		if (x == 0 && y == 55)
			return 1;
		break;
	case AVK_8:
		if (x == 38 && y == 41)
			return 1;
		break;
	case AVK_9:
		if (x == 77 && y == 55)
			return 1;
		break;
	case AVK_0:
		if (x == 187 && y == 0)
			return 1;
		break;
	case AVK_STAR:
		if (x == 160 && y == 0)
			return 1;
		break;
	case AVK_POUND:
		if (x == 214 && y == 0)
			return 1;
		break;
	case AVK_CLR:
		if (x == 115 && y == 38)
			return 1;
		break;
	case AVK_MENU:
		if (x == 115 && y == 19)
			return 1;
		break;
	case AVK_SOFT1:
		if (x == 115 && y == 0)
			return 1;
		break;
	}

	return 0;
}

void AttackRobin(int obj, int dest)
{
	long long int i, damage = 0, gap, ad = 0;
	const signed short* usPtr;
	int attackAttr = 0;
	int attackerLv = ao[dest].lv;
	long long int* attackerPs = ao[dest].ps;
	int attackerType = ao[dest].type;
	int defenseAttr = 0;
	long long recoverHp;

	OBJECT* pObj = &ao[obj];
	ITEM* it = &ao[obj].equip[EQUIP_ARMOR];

	if (dest >= CREW && dest < CREW + MAXCREW)
		return;

	if (ao[dest].attack == 3 || ao[dest].attack == 4 || ao[dest].invincible || ao[dest].dead == true || returnFrame)
		return;
	//모션이 바뀔 때 역할을 한다.


	if (dest < BULLET && obj >= ENEMY && obj < TOTALOBJECT) {
		if (ao[dest].attackedFrame)
			return;
		gap = (ao[obj].lv - attackerLv) + (robin.bossRoom == true ? 15 : 0) + (ao[obj].zoom == 2 ? 10 : 0) + (IsBigMonster(ao[obj].type) ? 5 : 0);
		ad = Random(10000);
#ifndef NOMISS
		if (ao[dest].debuf[STUN] == 0 && ao[dest].debuf[KNOCKBACK] == 0)
			ad -= Max(0, *(attackerPs + PS_EVASION) * 100 - gap * 50);
#endif
		//test
		//if (ad < 0)
		//	ad = 1;

		if (ad < 0) {
			//무적시간
			ao[dest].invincible = ATTACKEDFRAME;
			SetImgText(dest, EFFECT_TEXT_MISS, IMGTEXTZOOM);

			if (dest < PLAYERALL) {
#ifndef SKILL_ROBIN15_DAMAGExN
				//여유포착 스킬버프시 체력을 회복
				if (attackerType == ROBIN && ao[dest].buff[HPRESTORE]) {
					PlusHp(&ao[dest], UpDiv(*(attackerPs + PS_HP) * GetSkillValue(obj, SKILL_ROBIN15), 100));

					if (!ao[dest].hpDrain)
						ao[dest].hpDrain = 1;
				}
#endif

#ifndef SKILL_MAXX16_ERASEALLDEBUF
				//안도의한숨 : 적 공격 회피시 MP 회복
				if (attackerType == MAXX && ao[dest].buff[EVASIONTOMP]) {
					PlusMp(&ao[dest], UpDiv(*(attackerPs + PS_MP) * GetSkillValue(obj, SKILL_MAXX16), 100));

					if (!ao[dest].mpDrain)
						ao[dest].mpDrain = 1;
				}
#endif
			}

			return;
		}

#ifdef NOMISS
		ad = 0;
#else
#ifdef BLINDMISS100PER
		ad -= ao[obj].debuf[BLIND] == 0 ? 0 : 10000;
#else
		//블라인드인 경우 50% 빗맞힘 확률이 증가한다.
		ad -= Max(0, (ao[obj].debuf[BLIND] == 0 ? 1500 : 6500) - gap * 50);
#endif
#endif
		if (ad < 0) {
			//무적시간
			ao[dest].invincible = ATTACKEDFRAME;
			SetImgText(dest, EFFECT_TEXT_MISS, IMGTEXTZOOM);
		}
		else {
			//치명타 계산식
			//몬스터의 기본 치명률은 10%, 플레이어의 기본 치명률은 0%이며, 플레이어의 치명율로 올릴수 있다.
			//레벨차이당 0.5%의 치명확률이 증가한다.
#ifndef NOMONCRITICAL
			if (ad < 1000 + gap * 50)
				ad = 1;
			else
				ad = 0;
#endif

			//몬스터가 타격시
			//기절공격 계산식
			//턴제로 바꿔주기
			if (Random(1000) < gap * 5 && ao[dest].buff[INC_MAGIC_ARENA] == 0) {//check 스턴적용
				ad = 1 << ATTACK_STUN;
				ao[dest].debuf[STUN] = debufStartFrame[STUN] * (100 - *(attackerPs + PS_DEBUF)) / 100;
				ao[dest].debufOwner[STUN] = obj;
			}
			//무기의 기본대미지를 구한다.
			//몬스터는 str의 80~120%사이의 공격력을 가진다.
			damage = (ao[obj].str - extraArmor) * 80 + Random((ao[obj].str - extraArmor) * 40);
			damage = RoundDiv(damage, 180);// (ao[obj].str) * 80 + Random((ao[obj].str) * 40);
			//damage = (ao[obj].str);

			//엘케인 대쉬공격일 경우 무조건 크리대미지
			if (ao[obj].type == NPC_ELKEIN ||
				(ao[obj].type == ENEMY_ELKEIN
					|| ao[obj].type == ENEMY_ELKEIN_RED
					|| ao[obj].type == ENEMY_ELKEIN_BLUE
					|| ao[obj].type == ENEMY_ELKEIN_PURPLE
					|| ao[obj].type == ENEMY_ELKEIN_GREEN
					|| ao[obj].type == ENEMY_ELKEIN_GOLD
					|| ao[obj].type == ENEMY_ELKEIN_BLACK))
				ad = 1;

			//치명타인 경우
			if (ad % 2 == 1) {
				damage *= 2;

			}

			//주인공 방어도에 따라서 대미지를 줄여준다. 방어도로 인한 대미지 감소는 최대 75%까지.
			damage = damage * (25 + Max(0, 75 - RoundDiv(*(attackerPs + PS_ARMOR) * 225, (ao[obj].lv + 19) * (ao[obj].lv + 19)))) / 100;
			//damage = damage * (25 + Max(0, (7500 - *(attackerPs + PS_ARMOR)) / 100)) / 100;
			//damage = damage * (25 + (sqrt(*(attackerPs + PS_ARMOR)) / (sqrt(*(attackerPs + PS_ARMOR)) + 70))) / 100;//방어도 최대값을 75000으로 일단 해준다.
			//damage = damage * (25 + Max(0, (7500 - *(attackerPs + PS_ARMOR)) / 100)) / 100;
			//damage = damage * (10 + Max(0, (900 - *(attackerPs + PS_ARMOR)) / 10)) / 100;

			//몬스터 공격 속성에 따라서 대미지를 계산한다.
			if (ao[obj].type == NPC_LABETH ||
				(ao[obj].type == ENEMY_LABETH
					|| ao[obj].type == ENEMY_LABETH_RED
					|| ao[obj].type == ENEMY_LABETH_BLUE
					|| ao[obj].type == ENEMY_LABETH_PURPLE
					|| ao[obj].type == ENEMY_LABETH_GREEN
					|| ao[obj].type == ENEMY_LABETH_GOLD
					|| ao[obj].type == ENEMY_LABETH_BLACK))
				attackAttr = enemyAttr[51 * ENEMYATTRDATASIZE];
			else if (ao[obj].type == NPC_ELKEIN ||
				(ao[obj].type == ENEMY_ELKEIN
					|| ao[obj].type == ENEMY_ELKEIN_RED
					|| ao[obj].type == ENEMY_ELKEIN_BLUE
					|| ao[obj].type == ENEMY_ELKEIN_PURPLE
					|| ao[obj].type == ENEMY_ELKEIN_GREEN
					|| ao[obj].type == ENEMY_ELKEIN_GOLD
					|| ao[obj].type == ENEMY_ELKEIN_BLACK))
				attackAttr = enemyAttr[52 * ENEMYATTRDATASIZE];
			else if (ao[obj].type == NPC_DELPIOS)
				attackAttr = enemyAttr[53 * ENEMYATTRDATASIZE];
			else {
				//if (ao[obj].type > 53)
				//	ao[obj].type = 56;

				attackAttr = enemyAttr[(ao[obj].type - TOTALPLAYER) * ENEMYATTRDATASIZE];
			}

#ifndef NOATTRDMG
			//주인공의 방어력 속성
			//defenseAttr = collectionData[GetCollectionIdx(it->type, it->detail, it->grade) * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + EQUIP_ARMOR * COLLECTIONSDATASIZE + 4];

			//속성 공격 몬스터라면
			//switch (attackAttr) {
			//case FIRE:
			//	if (defenseAttr == FIRE)
			//		damage /= 2;
			//	else if (defenseAttr == FROST)
			//		damage *= 2;
			//	break;
			//case FROST:
			//	if (defenseAttr == FROST)
			//		damage /= 2;
			//	else if (defenseAttr == FIRE)
			//		damage *= 2;
			//	break;
			//case THUNDER:
			//	if (defenseAttr == THUNDER)
			//		damage /= 2;
			//	else if (defenseAttr == EARTH)
			//		damage *= 2;
			//	break;
			//case EARTH:
			//	if (defenseAttr == EARTH)
			//		damage /= 2;
			//	else if (defenseAttr == THUNDER)
			//		damage *= 2;
			//	break;
			//case HOLY:
			//	if (defenseAttr == HOLY)
			//		damage /= 2;
			//	else if (defenseAttr == DARK)
			//		damage *= 2;
			//	break;
			//case DARK:
			//	if (defenseAttr == DARK)
			//		damage /= 2;
			//	else if (defenseAttr == HOLY)
			//		damage *= 2;
			//	break;
			//}
			//회피면 그냥 damage를 뺀다.
			//if (ao[dest].ps[PS_EVASION]) {
			//	SetImgText(dest, EFFECT_TEXT_EVASION, IMGTEXTZOOM);
			//	damage = 0;
			//	ao[dest].ps[PS_EVASION]--;
			//	if (ao[dest].ps[PS_EVASION] < 0)
			//		ao[dest].ps[PS_EVASION] = 0;
			//}

			//if (ao[dest].ps[PS_DEFENSE]) {
			//	SetImgText(dest, EFFECT_TEXT_GUARD, IMGTEXTZOOM);
			//	damage = damage - damage * ao[dest].ps[PS_DEFENSE] / 100;//여기 실제로는 값을 빼준다.
			//	if (damage < 0)
			//		damage = 0;
			//	ao[dest].ps[PS_DEFENSE]--;
			//	if (ao[dest].ps[PS_DEFENSE] < 0)
			//		ao[dest].ps[PS_DEFENSE] = 0;
			//}

			if (attackAttr)
				damage = RoundDiv(damage * (100 - (Min(ao[obj].lv, *(attackerPs + PS_FIRE - 1 + attackAttr)) * 75 / Max(1, ao[obj].lv))), 66);
#endif

#ifndef NOABSORBDMG
			//대미지 감소율에 따라서 대미지를 줄여준다.
			damage = GetAbsorb(&ao[dest], damage);
#endif

#ifndef NOCURSEDMG
			if (ao[obj].debuf[CURSE])
				damage = UpDiv(damage * 75, 100);
#endif
			//긴급방어에 따라서 방어를 시킨다.
			if (Random(100) < *(attackerPs + PS_PARRY)) {
				damage = UpDiv(damage * (100 - *(attackerPs + PS_PARRYMOD)), 100);

				if ((effectOnlyPlayer == true && (dest == raidPlayer || ao[dest].soldier == true)) || effectOnlyPlayer == false)
					SetImgText(dest, EFFECT_TEXT_GUARD, IMGTEXTZOOM);
			}

#ifndef SKILL_ROBIN16_HPRESTORE 
			//냉정침착 버프에 따라 MP를 받은대미지의 일정량만큼 회복시킨다
			if ((dest >= PLAYER && dest < PLAYERALL) && ao[dest].buff[MPRESTORE]) {
				PlusMp(&ao[dest], UpDiv(damage * GetSkillValue(dest, SKILL_ROBIN16), 100));

				if (!ao[dest].mpDrain)
					ao[dest].mpDrain = 1;
			}
#endif
			//반사
			//
		}

		//주인공 디버프 처리
		if (ao[obj].type == NPC_LABETH ||
			(ao[obj].type == ENEMY_LABETH
				|| ao[obj].type == ENEMY_LABETH_RED
				|| ao[obj].type == ENEMY_LABETH_BLUE
				|| ao[obj].type == ENEMY_LABETH_PURPLE
				|| ao[obj].type == ENEMY_LABETH_GREEN
				|| ao[obj].type == ENEMY_LABETH_GOLD
				|| ao[obj].type == ENEMY_LABETH_BLACK))
			usPtr = &enemyAttr[51 * ENEMYATTRDATASIZE + 6];
		else if (ao[obj].type == NPC_ELKEIN ||
			(ao[obj].type == ENEMY_ELKEIN
				|| ao[obj].type == ENEMY_ELKEIN_RED
				|| ao[obj].type == ENEMY_ELKEIN_BLUE
				|| ao[obj].type == ENEMY_ELKEIN_PURPLE
				|| ao[obj].type == ENEMY_ELKEIN_GREEN
				|| ao[obj].type == ENEMY_ELKEIN_GOLD
				|| ao[obj].type == ENEMY_ELKEIN_BLACK))
			usPtr = &enemyAttr[52 * ENEMYATTRDATASIZE + 6];
		else if (ao[obj].type == NPC_DELPIOS)
			usPtr = &enemyAttr[53 * ENEMYATTRDATASIZE + 6];
		else
			//usPtr = &enemyAttr[(ao[ao[obj].mom].type - TOTALPLAYER) * ENEMYATTRDATASIZE + 6];
			usPtr = &enemyAttr[(ao[ENEMY].type - TOTALPLAYER) * ENEMYATTRDATASIZE + 6];

		ad = 0;

		i = 3;

		do {
			if (*usPtr == 0 || ao[dest].type >= NPC_CAPTAIN)
				break;

			ad += *usPtr % ATTRWORD;
			if (Random(100) < ad && (ao[obj].motion == *(usPtr + 1) || ao[obj].motion == *(usPtr + 2) || ao[obj].motion == *(usPtr + 3) || ao[obj].motion == *(usPtr + 4) || ao[obj].motion == *(usPtr + 5)) && !ao[obj].debuf[CURSE]) {
				gap = *usPtr / ATTRWORD;

				if (ao[dest].buff[INC_MAGIC_ARENA] == 0 && Random(100 - *(attackerPs + PS_DEBUFREGIST)) >= UpDiv(*(attackerPs + debufToAttr[gap] + PS_FIRE - 1) * 3, 4)) {
					ao[dest].debuf[gap] = debufStartFrame[gap] * (100 - *(attackerPs + PS_DEBUF)) / 100;
					ao[dest].debufOwner[gap] = obj;
					SetBit(&game.monsterDebuf[ao[ao[obj].mom].type], gap);

				}
				else
					if ((effectOnlyPlayer == true && (dest == raidPlayer || ao[dest].soldier == true)) || effectOnlyPlayer == false)
						SetImgText(dest, EFFECT_TEXT_REGIST, IMGTEXTZOOM);

				break;
			}
			usPtr++;
			i--;
		} while (i > 0);

		//리플렉터
		if ((dest >= PLAYER && dest < PLAYERALL) && ao[dest].buff[REFLECTION] && ao[obj].maxhp > 0 && (ao[obj].type < NPC_CAPTAIN || ao[obj].type == NPC_ELKEIN || ao[obj].type == NPC_LABETH))
			AttackObj(1000 + dest * 100 + 100000 * RoundDiv(GetSkillValue(dest, SKILL_ROBIN17) * damage, 100), obj);

		//레벨에 따른 데미지 보정식
		if (ao[obj].lv > attackerLv)
			damage = Max(1, damage + ao[obj].lv - attackerLv);

		//최소데미지
		if (damage <= 0)
			damage = 1;

		//무적시간
		ao[dest].attacked = true;
		ao[dest].attackedFrame = ATTACKEDFRAME;
#ifdef ATTACKEDINVINCIBLE
		ao[dest].invincible = ATTACKEDFRAME;
#endif	
		AddBar(&bar[BAR_PLAYERHP + dest], -Min(damage, ao[dest].hp), BARFRAME);
		
		ao[dest].hp -= damage;

		recoverHp = Min(damage, ao[obj].maxhp - ao[obj].hp);

		if (recoverHp > 0) {
			ao[obj].hp += recoverHp;
			AddBar(&bar[ENEMYHPBAR + GetEnemyBarIdx(obj)], recoverHp, BARFRAME);
			AddBar(&bar[BAR_BOSSHP], recoverHp, BARFRAME);
		}

		ao[dest].attr = attackAttr;

		if (ao[obj].mom >= ENEMY && ao[obj].mom < NEUTRAL && ao[ao[obj].mom].active) {
			ao[dest].dirF = (ao[ao[obj].mom].x > ao[dest].x) ? RIGHT : LEFT;
			ao[dest].dirX = 1 - ao[dest].dirF;
		}
	}
	else {
		damage = AttackRobin_Back(obj, dest);
	}

	if (damage > 0) {
		SetHitMark(ao[dest].x, ao[dest].y, RIGHT, HITMARK_SMALL, 0, obj, HITMARKZOOM/*ao[obj].zoom*/);
		curPlayer = dest;

		SetDmgNum(obj, dest, damage, 1, attackType, DMGNUMZOOM);

		if (dest < PLAYERALL && robin.gold < damage)
			damage = robin.gold;

		if (damage > 0) {
			int str;

			if (damage < 10)
				str = 0;
			else if (damage < 100)
				str = 1;
			else if (damage < 1000)
				str = 2;
			else if (damage < 10000)
				str = 3;
			else if (damage < 100000)
				str = 4;
			else if (damage < 1000000)
				str = 5;
			else
				str = 6;
			//for (i = 0; i < 3; i++)
			
			i = DropItem(&ao[dest], ITEM_GOLD);

			ao[i].defaultZoom = ao[i].zoom = 1.5f + str * 0.5f;

			if (dest < ENEMY) {
				ao[i].target = obj;
				ao[i].ax = -damage;
			}
			else {
				ao[i].target = PLAYER;
				ao[i].ax = damage;
			}
		}
	}

	//대미지 머리에 띄워주기
	//SetDmgNum(PLAYER, damage, ad % 2);

	if (ao[dest].hp <= 0) {
		ao[dest].hp = 0;
		ao[dest].dead = true;
		ao[dest].attack = 0;
		ao[dest].attackFrame = 0;
		memset(ao[dest].debuf, 0, sizeof(ao[dest].debuf));
		//ao[dest].drawHandler = VANISHDRAW;
		//ao[dest].moveHandler = VANISHMOVE;
		if (dest >= BULLET && dest < ENEMYUSEROBJ) {
			// 맥스가 죽었다면, 부메랑도 같이 memset시킨다.
			if (ao[dest].type == MAXX) {
				for (i = BULLET; i < ENEMY; i++) {
					if (ao[i].target == dest) {
						memset(&ao[i], 0, sizeof(OBJECT));
						break;
					}
				}
			}

			memset(&ao[dest], 0, sizeof(OBJECT));
		}

		returnFrame = 0;
		ao[dest].hpRestore = 0;
		ao[dest].mpRestore = 0;
		ao[dest].levelUpFrame = 0;
		ao[dest].mpDrain = 0;
		ao[dest].hpDrain = 0;
		gameOverFrame = 0;
		menuDepth = 0;
		keyHandle = null;
		effect.alpha = 0;

		memset(boomerangAway, 0, sizeof(boomerangAway));

		ao[dest].frame = 0;
	}

	BackUpEnemyObj();
	//for (i = ENEMY; i < NEUTRAL; i++)
	//	robin.enemyObj[i - ENEMY].x = ao[i].nx;

	SaveGame();
}

int AttackRobin_Back(int obj, int dest)
{
	int damage = 0;
	switch (obj) {
	case ATTACKTYPE_TILE:
		//가시를 밟은 경우
		if (ao[dest].canOnThorn)
			return 0;

		damage = RoundDiv(ao[dest].ps[PS_HP], 10);
		ao[dest].attacked = true;
		ao[dest].attackedFrame = ATTACKEDFRAME;
#ifdef ATTACKEDINVINCIBLE
		ao[dest].invincible = ATTACKEDFRAME;
#endif	
		ao[dest].dirX = 1 - ao[dest].dirF;
		break;
	case ATTACKTYPE_WATER:
		//수중에서 대미지를 입은 경우
		damage = 5;
		break;
	case ATTACKTYPE_SPACE:
		damage = 100;
		break;
	case ATTACKTYPE_MAGMA:
		//마그마를 밟은 경우
		if (ao[dest].canMagma)
			return 0;

		ao[dest].attacked = true;
		ao[dest].attackedFrame = ATTACKEDFRAME;
#ifdef ATTACKEDINVINCIBLE
		ao[dest].invincible = ATTACKEDFRAME;
#endif	
		damage = RoundDiv(ao[dest].ps[PS_HP], 10);
		break;
	case ATTACKTYPE_MAGMA2:
		if (ao[dest].canMagma)
			return 0;

		ao[dest].attacked = true;
		ao[dest].attackedFrame = ATTACKEDFRAME;
#ifdef ATTACKEDINVINCIBLE
		ao[dest].invincible = ATTACKEDFRAME;
#endif	
		damage = RoundDiv(ao[dest].ps[PS_HP], 5);
		break;
	case ATTACKTYPE_STALACTITE:
		//화염지대 종유석에 맞은 경우
		damage = RoundDiv(ao[dest].ps[PS_HP], 10);
		break;
	case ATTACKTYPE_ICICLE:
		//고드름에 맞은 경우
		damage = RoundDiv(ao[dest].ps[PS_HP], 20);
		ao[dest].attr = FROST;
		ao[dest].debuf[SLOW] = SLOW_START_FRAME;
		break;
	case ATTACKTYPE_POISON:
		damage = Min(ao[dest].hp - 1, Max(1, ao[dest].ps[PS_HP] * POISONDMGPER / 100));
		break;
	case ATTACKTYPE_DARKBALL:
		damage = 1 + ao[dest].maxhp * DARKDMGPER / 100;
		//damage = 50;
		ao[dest].attr = DARK;
		break;
	}

	AddBar(&bar[BAR_PLAYERHP + dest], -Min(damage, ao[dest].hp), BARFRAME);
	ao[dest].hp -= damage;
	return damage;
}

int AttackObj(long long int attacker, int dest)
{
	long long int damage = 0;
	int ad = 0, i;
	int gap = 0, tempVal = 0, attackAttr = 0;
	int extra = 0;
	long long int dmgOrigin = 0;
	OBJECT* pAttack;
	OBJECT* pDest = &ao[dest];
	const signed short* scPtr;
	unsigned char attackerLv;
	long long int* attackerPs;
	unsigned char attackerType;
	unsigned char attackerObj;
	unsigned char maxAttackerLv;
	unsigned char maxDestLv;
	long long int damageGap = 0;

	int currencyIcon;
	int currency;
	int skillIdx;

	OBJECT* pObj = &ao[turn];
	ITEM* it;
	if (turn < TOTALCHAR)
		it = &pObj->equip[EQUIP_WEAPON];

	int collectionIdx = false;
	if (turn < TOTALCHAR)
		GetCollectionIdx(it->type, it->detail, it->grade);

	float startX, startY, targetX, targetY, targetX2, targetY2, speed, speedIncrement, speed2, speedIncrement2, waitingFrame, waitingFrame2, zoom, zoomEnd, zoomIncrement, zoom2, zoomEnd2, zoomIncrement2;

	int realValue[EQUIP_BOOTS + 1];

	int maxZoom = 4.0f;//퀘스트 아이템 최
	int minZoom = 2.0f;//

	int stageCrewIdx;
	int stageCrewType;

	attackerObj = attacker;

	if (ao[attacker].attack >= ATTACK_SKILL)
		rpVar.isUseSkill = 1;

	if (attacker < 0) {
		attacker = -attacker - 1;
		extra = 1;
	}

	//데모신 중에는 충돌처리 하지 않음.
	if (isDemo)
		return 0;

	if (attacker < PLAYERALL) {
		attackerLv = ao[attacker].lv;
		attackerPs = ao[attacker].ps;
		attackerType = ao[attacker].type;
	}
	else {
		if (ao[attacker].mom >= CREW && ao[attacker].mom < CREW + MAXCREW) {
			attackerLv = ao[ao[attacker].mom].lv;
			attackerPs = ao[ao[attacker].mom].ps;
			attackerType = ao[ao[attacker].mom].type;
		}
		else {
			attackerLv = ao[ao[attacker].target].lv;
			attackerPs = ao[ao[attacker].target].ps;
			attackerType = ao[ao[attacker].target].type;
		}
	}
	//공격자가 플레이어가 아니라면
	if (attacker > 1000) {
		//리플렉터.
		damage = attacker / 100000;
		attacker = (attacker % 100000 - 1000) / 100;
		pAttack = &ao[attacker];

		goto NEXT;
	}
	else
		if (attacker >= TOTALOBJECT) {
			//오브젝트가 아닌 환경//디버프등에 의한 공격인 경우
			switch (attacker) {
			case ATTACKTYPE_POISON:
				damage = 1 + pDest->maxhp / 200;
				break;
			case ATTACKTYPE_DARKBALL:
				damage = 1 + pDest->maxhp * DARKDMGPER / 100;

				pDest->attr = DARK;
				break;
			}

			pAttack = 0;

			goto NEXT;
		}
		else if (attacker < TOTALOBJECT && attacker >= ENEMY) {
			ad = 0;
			pAttack = &ao[attacker];

			goto NEXT;
		}

	pAttack = &ao[attacker];


	//두 오브젝트간의 공격이 이루어 질 시 빚맞힘+회피의 확률을 구한다.
	if (attacker < ENEMY)
		gap = (attackerLv - pDest->lv);
	else
		gap = (pAttack->lv - attackerLv);

	//공격테이블은
	//ATTACK_MISS,
	//ATTACK_BLOCK,
	//ATTACK_DODGE,
	//ATTACK_NORMAL,
	//ATTACK_CRITICAL,
	//QUEST_EXTRA,
	//QUEST_STUN,
	//ATTACK_IGNORE,
	//ATTACK_KNOCKBACK,
	ad = Random(10000);

	//몬스터의 기본 적중률은 100%, 기본 회피율은 5%이며, 플레이어의 적중으로 줄일수 있다.
	//플레이어의 기본 적중률은 80%, 기본 회피율은 10%이며, 플레이어의 적중으로 올릴수 있다.
	//레벨차이당 0.5%의 회피/적중/치명확률이 증가한다.
	//빗나갈 확률은 최소 1%는 존재한다.

	//빚맞음 계산식 : 기본 15% + 레벨차이 * 0.5% + 블라인드시 25%
	//tempVal = (ao[attacker].debuf[BLIND] == 0 ? 50 : 300) - gap * 5;
#ifdef BLINDMISS100PER
	if (ao[attacker].debuf[BLIND] == 0 || (attacker < PLAYERALL && ao[attacker].attack >= ATTACK_SKILL) || (attacker >= PLAYERALL && ao[ao[attacker].target].attack >= ATTACK_SKILL))
		tempVal = 0;
	else
		tempVal = 1000;
#else
	tempVal = (ao[attacker].debuf[BLIND] == 0 ? 50 : 300) - gap * 5;
#endif
	//행동불가 상태가 아니라면 회피를 계산한다.
	if (pDest->debuf[STUN] == 0 && pDest->debuf[KNOCKBACK] == 0)
		//회피율 계산식 : 기본 5% + 몬스터 레벨당 0.2% + 레벨차이 * 0.5%
		dmgOrigin = 50 + pDest->lv * 2 - gap * 5;
	//#ifdef NOMISS
	//		dmgOrigin = 0;
	//#else
	//		dmgOrigin = 50;
	//#endif

	ad -= ((tempVal + dmgOrigin) * 10 - *(attackerPs + PS_HIT) * 100);
#ifdef NOMISS
	if (ad < 0)
		ad = 0;
#endif

	//빚맞거나 회피하였다면
	if (ad < 0) {
		//if ((effectOnlyPlayer == true && (attacker == raidPlayer || ao[attacker].soldier == true || (attacker >= BULLET && attacker < ENEMY && (ao[attacker].target == raidPlayer || ao[ao[attacker].target].soldier == true)))) || effectOnlyPlayer == false) {
			//플레이어 적중률이 빚맞힐 확률보다 높다면 회피한것으로 간주한다.
			//if (*(attackerPs + PS_HIT) * 10 >= tempVal)
			//	SetImgText(dest, EFFECT_TEXT_EVASION, IMGTEXTZOOM);
			//else
		SetImgText(ao[dest].mom, EFFECT_TEXT_MISS, IMGTEXTZOOM);
		AfterAttack(pAttack);
		//}
		return 0;
	}
	else {
		//치명타 계산식
		//몬스터의 기본 치명률은 10%, 플레이어의 기본 치명률은 0%이며, 플레이어의 치명율로 올릴수 있다.
		//레벨차이당 0.5%의 치명확률이 증가한다.
		//ad = (ad < *(attackerPs + PS_CRITICAL) * 100 + gap * 50);
		ad = (ad < (DEFAULTCRITICAL + *(attackerPs + PS_CRITICAL)) * 100);

		//기절공격 계산식
		if (!pDest->debuf[STUN] && (Random(100) < *(attackerPs + PS_STUN) + gap)) {
			refreshRate = FPSDOWN_STUN;

			ad += 1 << ATTACK_STUN;
			pAttack->attackFrame += 4;

			switch (pDest->type) {
			case ENEMY_SLIME:
			case ENEMY_SLIME_RED:
			case ENEMY_SLIME_BLUE:
			case ENEMY_SLIME_PURPLE:
			case ENEMY_SLIME_GREEN:
			case ENEMY_SLIME_GOLD:
			case ENEMY_SLIME_BLACK:
			case ENEMY_DARKDRAGON:
			case ENEMY_DARKDRAGON_RED:
			case ENEMY_DARKDRAGON_BLUE:
			case ENEMY_DARKDRAGON_PURPLE:
			case ENEMY_DARKDRAGON_GREEN:
			case ENEMY_DARKDRAGON_GOLD:
			case ENEMY_DARKDRAGON_BLACK:
			case ENEMY_ONEEYE:
			case ENEMY_ONEEYE_RED:
			case ENEMY_ONEEYE_BLUE:
			case ENEMY_ONEEYE_PURPLE:
			case ENEMY_ONEEYE_GREEN:
			case ENEMY_ONEEYE_GOLD:
			case ENEMY_ONEEYE_BLACK:
			case ENEMY_FROG:
			case ENEMY_FROG_RED:
			case ENEMY_FROG_BLUE:
			case ENEMY_FROG_PURPLE:
			case ENEMY_FROG_GREEN:
			case ENEMY_FROG_GOLD:
			case ENEMY_FROG_BLACK:
			case ENEMY_GIANT:
			case ENEMY_GIANT_RED:
			case ENEMY_GIANT_BLUE:
			case ENEMY_GIANT_PURPLE:
			case ENEMY_GIANT_GREEN:
			case ENEMY_GIANT_GOLD:
			case ENEMY_GIANT_BLACK:
			case ENEMY_PHOENIX:
			case ENEMY_PHOENIX_RED:
			case ENEMY_PHOENIX_BLUE:
			case ENEMY_PHOENIX_PURPLE:
			case ENEMY_PHOENIX_GREEN:
			case ENEMY_PHOENIX_GOLD:
			case ENEMY_PHOENIX_BLACK:
			case ENEMY_IFRIT:
			case ENEMY_IFRIT_RED:
			case ENEMY_IFRIT_BLUE:
			case ENEMY_IFRIT_PURPLE:
			case ENEMY_IFRIT_GREEN:
			case ENEMY_IFRIT_GOLD:
			case ENEMY_IFRIT_BLACK:
			case ENEMY_ICESUN:
			case ENEMY_ICESUN_RED:
			case ENEMY_ICESUN_BLUE:
			case ENEMY_ICESUN_PURPLE:
			case ENEMY_ICESUN_GREEN:
			case ENEMY_ICESUN_GOLD:
			case ENEMY_ICESUN_BLACK:
			case ENEMY_LIGHTNING:
			case ENEMY_LIGHTNING_RED:
			case ENEMY_LIGHTNING_BLUE:
			case ENEMY_LIGHTNING_PURPLE:
			case ENEMY_LIGHTNING_GREEN:
			case ENEMY_LIGHTNING_GOLD:
			case ENEMY_LIGHTNING_BLACK:
			case ENEMY_THUNDER:
			case ENEMY_THUNDER_RED:
			case ENEMY_THUNDER_BLUE:
			case ENEMY_THUNDER_PURPLE:
			case ENEMY_THUNDER_GREEN:
			case ENEMY_THUNDER_GOLD:
			case ENEMY_THUNDER_BLACK:
			case ENEMY_FAIRY:
			case ENEMY_FAIRY_RED:
			case ENEMY_FAIRY_BLUE:
			case ENEMY_FAIRY_PURPLE:
			case ENEMY_FAIRY_GREEN:
			case ENEMY_FAIRY_GOLD:
			case ENEMY_FAIRY_BLACK:
			case ENEMY_CIRCLE:
			case ENEMY_CIRCLE_RED:
			case ENEMY_CIRCLE_BLUE:
			case ENEMY_CIRCLE_PURPLE:
			case ENEMY_CIRCLE_GREEN:
			case ENEMY_CIRCLE_GOLD:
			case ENEMY_CIRCLE_BLACK:
			case ENEMY_ANGEL:
			case ENEMY_ANGEL_RED:
			case ENEMY_ANGEL_BLUE:
			case ENEMY_ANGEL_PURPLE:
			case ENEMY_ANGEL_GREEN:
			case ENEMY_ANGEL_GOLD:
			case ENEMY_ANGEL_BLACK:
			case ENEMY_SPIDER:
			case ENEMY_MAMMOTH:
			case ENEMY_MAMMOTH_RED:
			case ENEMY_MAMMOTH_BLUE:
			case ENEMY_MAMMOTH_PURPLE:
			case ENEMY_MAMMOTH_GREEN:
			case ENEMY_MAMMOTH_GOLD:
			case ENEMY_MAMMOTH_BLACK:
			case ENEMY_GHOST:
			case ENEMY_GHOST_RED:
			case ENEMY_GHOST_BLUE:
			case ENEMY_GHOST_PURPLE:
			case ENEMY_GHOST_GREEN:
			case ENEMY_GHOST_GOLD:
			case ENEMY_GHOST_BLACK:
			case ENEMY_CASTLE2:
			case ENEMY_CASTLE2_RED:
			case ENEMY_CASTLE2_BLUE:
			case ENEMY_CASTLE2_PURPLE:
			case ENEMY_CASTLE2_GREEN:
			case ENEMY_CASTLE2_GOLD:
			case ENEMY_CASTLE2_BLACK:
			case ENEMY_SPACE1:
			case ENEMY_SPACE1_RED:
			case ENEMY_SPACE1_BLUE:
			case ENEMY_SPACE1_PURPLE:
			case ENEMY_SPACE1_GREEN:
			case ENEMY_SPACE1_GOLD:
			case ENEMY_SPACE1_BLACK:
			case ENEMY_KIMERA:
			case ENEMY_KIMERA_RED:
			case ENEMY_KIMERA_BLUE:
			case ENEMY_KIMERA_PURPLE:
			case ENEMY_KIMERA_GREEN:
			case ENEMY_KIMERA_GOLD:
			case ENEMY_KIMERA_BLACK:
			case ENEMY_SHIP:
			case ENEMY_SHIP_RED:
			case ENEMY_SHIP_BLUE:
			case ENEMY_SHIP_PURPLE:
			case ENEMY_SHIP_GREEN:
			case ENEMY_SHIP_GOLD:
			case ENEMY_SHIP_BLACK:
			case ENEMY_FOGRA:
			case ENEMY_FOGRA_RED:
			case ENEMY_FOGRA_BLUE:
			case ENEMY_FOGRA_PURPLE:
			case ENEMY_FOGRA_GREEN:
			case ENEMY_FOGRA_GOLD:
			case ENEMY_FOGRA_BLACK:
			case ENEMY_BAHAMUT:
			case ENEMY_DEATH:
			case ENEMY_DEATH_RED:
			case ENEMY_DEATH_BLUE:
			case ENEMY_DEATH_PURPLE:
			case ENEMY_DEATH_GREEN:
			case ENEMY_DEATH_GOLD:
			case ENEMY_DEATH_BLACK:
			case ENEMY_CASTLE_BOSS1:
			case ENEMY_CASTLE_BOSS1_RED:
			case ENEMY_CASTLE_BOSS1_BLUE:
			case ENEMY_CASTLE_BOSS1_PURPLE:
			case ENEMY_CASTLE_BOSS1_GREEN:
			case ENEMY_CASTLE_BOSS1_GOLD:
			case ENEMY_CASTLE_BOSS1_BLACK:
			case ENEMY_CASTLE_BOSS2:
			case ENEMY_CASTLE_BOSS2_RED:
			case ENEMY_CASTLE_BOSS2_BLUE:
			case ENEMY_CASTLE_BOSS2_PURPLE:
			case ENEMY_CASTLE_BOSS2_GREEN:
			case ENEMY_CASTLE_BOSS2_GOLD:
			case ENEMY_CASTLE_BOSS2_BLACK:
			case ENEMY_CASTLE_BOSS3:
			case ENEMY_CASTLE_BOSS3_RED:
			case ENEMY_CASTLE_BOSS3_BLUE:
			case ENEMY_CASTLE_BOSS3_PURPLE:
			case ENEMY_CASTLE_BOSS3_GREEN:
			case ENEMY_CASTLE_BOSS3_GOLD:
			case ENEMY_CASTLE_BOSS3_BLACK:
			case ENEMY_CASTLE_BOSS4:
			case ENEMY_CASTLE_BOSS4_RED:
			case ENEMY_CASTLE_BOSS4_BLUE:
			case ENEMY_CASTLE_BOSS4_PURPLE:
			case ENEMY_CASTLE_BOSS4_GREEN:
			case ENEMY_CASTLE_BOSS4_GOLD:
			case ENEMY_CASTLE_BOSS4_BLACK:
			case ENEMY_LABETH:
			case ENEMY_ELKEIN:
				break;
			default:
				if (robin.bossRoom != true) {
					pDest->debuf[STUN] = STUN_START_FRAME;
					effect.shake = 3;

					//아드레날린 : 기절공격 성공시 MP 회복량 상승
					if (attackerType == DIANA && pAttack->skillLv[SKILL_DIANA3]) {
						PlusMp(pAttack, GetSkillValue(attacker, SKILL_DIANA3));

						if (!pAttack->mpDrain)
							pAttack->mpDrain = 1;
					}
				}
				break;
			}
		}
		else if (Random(48) < pAttack->concentrate) {
			refreshRate = FPSDOWN_STUN;

			ad += 1 << ATTACK_STUN;

			switch (pDest->type) {
			case ENEMY_SLIME:
			case ENEMY_SLIME_RED:
			case ENEMY_SLIME_BLUE:
			case ENEMY_SLIME_PURPLE:
			case ENEMY_SLIME_GREEN:
			case ENEMY_SLIME_GOLD:
			case ENEMY_SLIME_BLACK:
			case ENEMY_DARKDRAGON:
			case ENEMY_DARKDRAGON_RED:
			case ENEMY_DARKDRAGON_BLUE:
			case ENEMY_DARKDRAGON_PURPLE:
			case ENEMY_DARKDRAGON_GREEN:
			case ENEMY_DARKDRAGON_GOLD:
			case ENEMY_DARKDRAGON_BLACK:
			case ENEMY_ONEEYE:
			case ENEMY_ONEEYE_RED:
			case ENEMY_ONEEYE_BLUE:
			case ENEMY_ONEEYE_PURPLE:
			case ENEMY_ONEEYE_GREEN:
			case ENEMY_ONEEYE_GOLD:
			case ENEMY_ONEEYE_BLACK:
			case ENEMY_FROG:
			case ENEMY_FROG_RED:
			case ENEMY_FROG_BLUE:
			case ENEMY_FROG_PURPLE:
			case ENEMY_FROG_GREEN:
			case ENEMY_FROG_GOLD:
			case ENEMY_FROG_BLACK:
			case ENEMY_GIANT:
			case ENEMY_GIANT_RED:
			case ENEMY_GIANT_BLUE:
			case ENEMY_GIANT_PURPLE:
			case ENEMY_GIANT_GREEN:
			case ENEMY_GIANT_GOLD:
			case ENEMY_GIANT_BLACK:
			case ENEMY_PHOENIX:
			case ENEMY_PHOENIX_RED:
			case ENEMY_PHOENIX_BLUE:
			case ENEMY_PHOENIX_PURPLE:
			case ENEMY_PHOENIX_GREEN:
			case ENEMY_PHOENIX_GOLD:
			case ENEMY_PHOENIX_BLACK:
			case ENEMY_ICESUN:
			case ENEMY_ICESUN_RED:
			case ENEMY_ICESUN_BLUE:
			case ENEMY_ICESUN_PURPLE:
			case ENEMY_ICESUN_GREEN:
			case ENEMY_ICESUN_GOLD:
			case ENEMY_ICESUN_BLACK:
			case ENEMY_LIGHTNING:
			case ENEMY_LIGHTNING_RED:
			case ENEMY_LIGHTNING_BLUE:
			case ENEMY_LIGHTNING_PURPLE:
			case ENEMY_LIGHTNING_GREEN:
			case ENEMY_LIGHTNING_GOLD:
			case ENEMY_LIGHTNING_BLACK:
			case ENEMY_THUNDER:
			case ENEMY_THUNDER_RED:
			case ENEMY_THUNDER_BLUE:
			case ENEMY_THUNDER_PURPLE:
			case ENEMY_THUNDER_GREEN:
			case ENEMY_THUNDER_GOLD:
			case ENEMY_THUNDER_BLACK:
			case ENEMY_FAIRY:
			case ENEMY_FAIRY_RED:
			case ENEMY_FAIRY_BLUE:
			case ENEMY_FAIRY_PURPLE:
			case ENEMY_FAIRY_GREEN:
			case ENEMY_FAIRY_GOLD:
			case ENEMY_FAIRY_BLACK:
			case ENEMY_CIRCLE:
			case ENEMY_CIRCLE_RED:
			case ENEMY_CIRCLE_BLUE:
			case ENEMY_CIRCLE_PURPLE:
			case ENEMY_CIRCLE_GREEN:
			case ENEMY_CIRCLE_GOLD:
			case ENEMY_CIRCLE_BLACK:
			case ENEMY_GHOST:
			case ENEMY_GHOST_RED:
			case ENEMY_GHOST_BLUE:
			case ENEMY_GHOST_PURPLE:
			case ENEMY_GHOST_GREEN:
			case ENEMY_GHOST_GOLD:
			case ENEMY_GHOST_BLACK:
			case ENEMY_CASTLE2:
			case ENEMY_CASTLE2_RED:
			case ENEMY_CASTLE2_BLUE:
			case ENEMY_CASTLE2_PURPLE:
			case ENEMY_CASTLE2_GREEN:
			case ENEMY_CASTLE2_GOLD:
			case ENEMY_CASTLE2_BLACK:
			case ENEMY_SPACE1:
			case ENEMY_SPACE1_RED:
			case ENEMY_SPACE1_BLUE:
			case ENEMY_SPACE1_PURPLE:
			case ENEMY_SPACE1_GREEN:
			case ENEMY_SPACE1_GOLD:
			case ENEMY_SPACE1_BLACK:
			case ENEMY_KIMERA:
			case ENEMY_KIMERA_RED:
			case ENEMY_KIMERA_BLUE:
			case ENEMY_KIMERA_PURPLE:
			case ENEMY_KIMERA_GREEN:
			case ENEMY_KIMERA_GOLD:
			case ENEMY_KIMERA_BLACK:
			case ENEMY_SHIP:
			case ENEMY_SHIP_RED:
			case ENEMY_SHIP_BLUE:
			case ENEMY_SHIP_PURPLE:
			case ENEMY_SHIP_GREEN:
			case ENEMY_SHIP_GOLD:
			case ENEMY_SHIP_BLACK:
			case ENEMY_SPIDER:
			case ENEMY_SPIDER_RED:
			case ENEMY_SPIDER_BLUE:
			case ENEMY_SPIDER_PURPLE:
			case ENEMY_SPIDER_GREEN:
			case ENEMY_SPIDER_GOLD:
			case ENEMY_SPIDER_BLACK:
			case ENEMY_MAMMOTH:
			case ENEMY_MAMMOTH_RED:
			case ENEMY_MAMMOTH_BLUE:
			case ENEMY_MAMMOTH_PURPLE:
			case ENEMY_MAMMOTH_GREEN:
			case ENEMY_MAMMOTH_GOLD:
			case ENEMY_MAMMOTH_BLACK:
			case ENEMY_FOGRA:
			case ENEMY_FOGRA_RED:
			case ENEMY_FOGRA_BLUE:
			case ENEMY_FOGRA_PURPLE:
			case ENEMY_FOGRA_GREEN:
			case ENEMY_FOGRA_GOLD:
			case ENEMY_FOGRA_BLACK:
			case ENEMY_BAHAMUT:
			case ENEMY_BAHAMUT_RED:
			case ENEMY_BAHAMUT_BLUE:
			case ENEMY_BAHAMUT_PURPLE:
			case ENEMY_BAHAMUT_GREEN:
			case ENEMY_BAHAMUT_GOLD:
			case ENEMY_BAHAMUT_BLACK:
			case ENEMY_DEATH:
			case ENEMY_DEATH_RED:
			case ENEMY_DEATH_BLUE:
			case ENEMY_DEATH_PURPLE:
			case ENEMY_DEATH_GREEN:
			case ENEMY_DEATH_GOLD:
			case ENEMY_DEATH_BLACK:
			case ENEMY_CASTLE_BOSS1:
			case ENEMY_CASTLE_BOSS1_RED:
			case ENEMY_CASTLE_BOSS1_BLUE:
			case ENEMY_CASTLE_BOSS1_PURPLE:
			case ENEMY_CASTLE_BOSS1_GREEN:
			case ENEMY_CASTLE_BOSS1_GOLD:
			case ENEMY_CASTLE_BOSS1_BLACK:
			case ENEMY_CASTLE_BOSS2:
			case ENEMY_CASTLE_BOSS2_RED:
			case ENEMY_CASTLE_BOSS2_BLUE:
			case ENEMY_CASTLE_BOSS2_PURPLE:
			case ENEMY_CASTLE_BOSS2_GREEN:
			case ENEMY_CASTLE_BOSS2_GOLD:
			case ENEMY_CASTLE_BOSS2_BLACK:
			case ENEMY_CASTLE_BOSS3:
			case ENEMY_CASTLE_BOSS3_RED:
			case ENEMY_CASTLE_BOSS3_BLUE:
			case ENEMY_CASTLE_BOSS3_PURPLE:
			case ENEMY_CASTLE_BOSS3_GREEN:
			case ENEMY_CASTLE_BOSS3_GOLD:
			case ENEMY_CASTLE_BOSS3_BLACK:
			case ENEMY_CASTLE_BOSS4:
			case ENEMY_CASTLE_BOSS4_RED:
			case ENEMY_CASTLE_BOSS4_BLUE:
			case ENEMY_CASTLE_BOSS4_PURPLE:
			case ENEMY_CASTLE_BOSS4_GREEN:
			case ENEMY_CASTLE_BOSS4_GOLD:
			case ENEMY_CASTLE_BOSS4_BLACK:
			case ENEMY_LABETH:
			case ENEMY_ELKEIN:
				break;
			default:
				if (robin.bossRoom != true)
					pDest->debuf[STUN] = STUN_START_FRAME + pAttack->concentrate * FPS;
				break;
			}
		}

		//추가공격 계산식
		if (extra == 0 && Random(1000) < *(attackerPs + PS_EXTRA) * 10 + gap * 5) {
			refreshRate = FPSDOWN_EXTRA;

			ad += 1 << ATTACK_EXTRA;
			pAttack->attackFrame += 4;
			SetImgText(attackerObj, EFFECT_TEXT_EXTRA, IMGTEXTZOOM);
			//SetHitMark(pDest->x, pDest->y, (pAttack->x <= pDest->x) ? LEFT : RIGHT, HITMARK_EXTRA, 0, attacker < PLAYERALL ? attacker : ao[attacker].target, pDest->zoom);
			//i = DropItem(pAttack, ITEM_GOLD);
			//ao[i].target = attacker;
			//ao[i].ax = damage;
			//여기서 동전 떨어뜨려 준다.
			effect.hpShake = true;
			effect.shake = 4;
		}

		//속성공격 계산식
		if (pAttack->flamer)
			attackAttr = FIRE;
		else {
			for (i = 0; i < 5; i++) {
				if (Random(100) < *(attackerPs + PS_FIREATTACK + i)) {
					attackAttr = i + 1;
					break;
				}
			}
		}

		//방어도 무시공격 계산식
		if (attackAttr == 0 && Random(1000) < *(attackerPs + PS_IGNORE) * 10 + gap * 5) {
			refreshRate = FPSDOWN_IGNORE;

			ad += 1 << ATTACK_IGNORE;
			pAttack->attackFrame += 4;
		}

		//관통공격 계산식
		if (Random(1000) < *(attackerPs + PS_PIERCE) * 10) {
			refreshRate = FPSDOWN_PIERCE;

			ad += 1 << ATTACK_PIERCE;
			pAttack->attackFrame += 4;
			SetImgText(attackerObj, EFFECT_TEXT_PIERCE, IMGTEXTZOOM);
			SetHitMark(pDest->x, pDest->y + (float)32 * _2X * pDest->zoom, (pAttack->x <= pDest->x) ? LEFT : RIGHT, HITMARK_PIERCE, 0, attacker < PLAYERALL ? attacker : ao[attacker].target, HITMARKZOOM/*pDest->zoom*/);
			//i = DropItem(pAttack, ITEM_GOLD);
			//ao[i].target = attacker;
			effect.hpShake = true;
			effect.shake = 4;
		}
		else if ((attacker >= PLAYER && attacker < PLAYERALL) && pAttack->currentSkill >= 0 && pAttack->hotKey[pAttack->currentSkill].type == HOTKEY_SKILL && (pAttack->hotKey[pAttack->currentSkill].idx == SKILL_ROBIN9 || pAttack->hotKey[pAttack->currentSkill].idx == SKILL_ROBIN10)) {
			//else if ((attacker >= PLAYER && attacker < PLAYERALL) && pAttack->currentSkill >= 0 && (pAttack->currentSkill == SKILL_ROBIN9 || pAttack->currentSkill == SKILL_ROBIN11)) {
			refreshRate = FPSDOWN_PIERCE;
			ad += 1 << ATTACK_PIERCE;

			SetImgText(dest, EFFECT_TEXT_PIERCE, IMGTEXTZOOM);
			SetHitMark(pDest->x, pDest->y + (float)32 * _2X * pDest->zoom, (pAttack->x <= pDest->x) ? LEFT : RIGHT, HITMARK_PIERCE, 0, attacker < PLAYERALL ? attacker : ao[attacker].target, HITMARKZOOM/*pDest->zoom*/);
			//i = DropItem(pAttack, ITEM_GOLD);
			//ao[i].target = attacker;
			effect.hpShake = true;
			effect.shake = 4;
		}
		else if (attacker >= BULLET && attacker < ENEMY && (ao[attacker].attack == DIANA_SKILL_BOMBSHOT || ao[attacker].attack == MAXX_SKILL_MEGA || ao[attacker].moveHandler == BULLETITEMMOVE)) {
			refreshRate = FPSDOWN_PIERCE;

			ad += 1 << ATTACK_PIERCE;
			SetImgText(dest, EFFECT_TEXT_PIERCE, IMGTEXTZOOM);
			SetHitMark(pDest->x, pDest->y + (float)32 * _2X * pDest->zoom, (pAttack->x <= pDest->x) ? LEFT : RIGHT, HITMARK_PIERCE, 0, attacker < PLAYERALL ? attacker : ao[attacker].target, HITMARKZOOM/*pDest->zoom*/);
			//i = DropItem(pAttack, ITEM_GOLD);
			//ao[i].target = attacker;
			effect.shake = 4;
		}
		//디펜스 타워의 데미지 구하기
		damage = RoundDiv(*(attackerPs + PS_DMG) * GetAtk(attacker), 100);

		//회전력상승 : 추가 공격 성공시 해당 공격에 대해서 데미지 상승
		if (extra && pAttack->skillLv[SKILL_MAXX4])
			damage = RoundDiv(damage * (100 + GetSkillValue(attacker, SKILL_MAXX4)), 100);

		//치명타인경우
		if (ad % 2 == 1) {
			refreshRate = FPSDOWN_CRITICAL;

			damage = RoundDiv(damage * (200 + *(attackerPs + PS_CRITDMG)), 100);
			//i = DropItem(pAttack, ITEM_GOLD);
			//ao[i].target = attacker;
			//SetImgText(attackerObj, EFFECT_TEXT_CRITICAL, IMGTEXTZOOM);
			pAttack->attackFrame += 4;
			pAttack->attackLv++;
		}

		maxAttackerLv = Min(120, attackerLv);
		maxDestLv = Min(120, pDest->lv);

		//방어도 무시 공격이 아니라면 방어도에 따른 감소율을 정한다 (0~100%).
		if ((ad >> ATTACK_IGNORE) % 2 == 0)
			//방어도로 인한 대미지 감소는 최대 75%까지이다.
			damage = damage * (25 + Max(0, 75 - RoundDiv(maxDestLv * 36 * 75, maxAttackerLv * (144 - maxAttackerLv)))) / 100;

		//속성공격인 경우
		if (attackAttr) {
			//몬스터의 레벨과 종류에 따라서 각 속성에 해당하는 저항치를 구한다.
			scPtr = &enemyAttr[(pDest->type - TOTALPLAYER) * ENEMYATTRDATASIZE + attackAttr];
			i = (*scPtr < 0) ? (69 + maxDestLv) * *scPtr / 100 + (maxDestLv - 31) : (131 - maxDestLv) * *scPtr / 100 + (maxDestLv - 31);

			//저항으로 인한 대미지 감소는 최대 75%까지이다.
			damage = (i < 0) ? RoundDiv(damage * (100 - i * 2), 100) : RoundDiv(damage * (100 - i * 3 / 4), 100);
		}

		if (ao[attackerObj].debuf[CURSE])
			damage = UpDiv(damage * 75, 100);

		dmgOrigin = damage;

		//일부러 없앴나?@@
		//if (pAttack->moveHandler == BULLETBOOMERANGMOVE && pAttack->etc != 6)
		//	damage = RoundDiv(damage, pAttack->mom + 1 - pAttack->status);

		//무기에 따라서 최소~최대대미지 사이값을 구한다.
		damage = RoundDiv(damage * (100 - weaponRange[attackerType]), 100) + Random(RoundDiv(damage * weaponRange[attackerType] * 2, 100) + 1);

		//HP흡수
		if (*(attackerPs + PS_HPDRAIN) > 0) {
			int hpObj = GetObjFromPtr(pAttack);
			if (hpObj >= BULLET && hpObj < ENEMY && pAttack->moveHandler == BULLETBOOMERANGMOVE)
				hpObj = pAttack->target;

			temp = UpDiv(*(attackerPs + PS_HPDRAIN) * damage * Max(5, 101 - Min(100, attackerLv)), 10000);
			PlusHp(&ao[hpObj], temp);

			if (!ao[hpObj].hpDrain)
				ao[hpObj].hpDrain = 1;
		}
		//else if (*(attackerPs + PS_HPDRAIN) < 0)
		//	robin.hp = Max(1, robin.hp - UpDiv(*(attackerPs + PS_HPDRAIN) * damage, 100));

		//MP흡수
		if (*(attackerPs + PS_MPDRAIN)) {
			temp = UpDiv(*(attackerPs + PS_MPDRAIN) * damage * Max(5, 101 - Min(100, attackerLv)), 10000);
			PlusMp(pAttack, temp);
			pAttack->mpDrain = 1;
		}
	}

	switch (pDest->type) {
		//case ENEMY_LIGHTNING:
		//	pDest->etc = LIGHTNING_FALL;
		//	pDest->moveHandler = ENEMYMOVE;
		//	pDest->jumpFrame = 0;
		//	pDest->status = FALL;
		//	pDest->dirY = DOWN;
		//	break;
	case ENEMY_SLIME:
	case ENEMY_SLIME_RED:
	case ENEMY_SLIME_BLUE:
	case ENEMY_SLIME_PURPLE:
	case ENEMY_SLIME_GREEN:
	case ENEMY_SLIME_GOLD:
	case ENEMY_SLIME_BLACK:
	case ENEMY_MACHINE:
	case ENEMY_MACHINE_RED:
	case ENEMY_MACHINE_BLUE:
	case ENEMY_MACHINE_PURPLE:
	case ENEMY_MACHINE_GREEN:
	case ENEMY_MACHINE_GOLD:
	case ENEMY_MACHINE_BLACK:
	case ENEMY_SHIP:
	case ENEMY_SHIP_RED:
	case ENEMY_SHIP_BLUE:
	case ENEMY_SHIP_PURPLE:
	case ENEMY_SHIP_GREEN:
	case ENEMY_SHIP_GOLD:
	case ENEMY_SHIP_BLACK:
	case ENEMY_LARVA:
	case ENEMY_LARVA_RED:
	case ENEMY_LARVA_BLUE:
	case ENEMY_LARVA_PURPLE:
	case ENEMY_LARVA_GREEN:
	case ENEMY_LARVA_GOLD:
	case ENEMY_LARVA_BLACK:
	case ENEMY_ANGEL:
	case ENEMY_ANGEL_RED:
	case ENEMY_ANGEL_BLUE:
	case ENEMY_ANGEL_PURPLE:
	case ENEMY_ANGEL_GREEN:
	case ENEMY_ANGEL_GOLD:
	case ENEMY_ANGEL_BLACK:
	case ENEMY_FOGRA:
	case ENEMY_FOGRA_RED:
	case ENEMY_FOGRA_BLUE:
	case ENEMY_FOGRA_PURPLE:
	case ENEMY_FOGRA_GREEN:
	case ENEMY_FOGRA_GOLD:
	case ENEMY_FOGRA_BLACK:
	case ENEMY_SPIDER:
	case ENEMY_SPIDER_RED:
	case ENEMY_SPIDER_BLUE:
	case ENEMY_SPIDER_PURPLE:
	case ENEMY_SPIDER_GREEN:
	case ENEMY_SPIDER_GOLD:
	case ENEMY_SPIDER_BLACK:
	case ENEMY_MAMMOTH:
	case ENEMY_MAMMOTH_RED:
	case ENEMY_MAMMOTH_BLUE:
	case ENEMY_MAMMOTH_PURPLE:
	case ENEMY_MAMMOTH_GREEN:
	case ENEMY_MAMMOTH_GOLD:
	case ENEMY_MAMMOTH_BLACK:
	case ENEMY_BAHAMUT:
	case ENEMY_BAHAMUT_RED:
	case ENEMY_BAHAMUT_BLUE:
	case ENEMY_BAHAMUT_PURPLE:
	case ENEMY_BAHAMUT_GREEN:
	case ENEMY_BAHAMUT_GOLD:
	case ENEMY_BAHAMUT_BLACK:
	case ENEMY_DEATH:
	case ENEMY_DEATH_RED:
	case ENEMY_DEATH_BLUE:
	case ENEMY_DEATH_PURPLE:
	case ENEMY_DEATH_GREEN:
	case ENEMY_DEATH_GOLD:
	case ENEMY_DEATH_BLACK:
	case ENEMY_CASTLE_BOSS1:
	case ENEMY_CASTLE_BOSS1_RED:
	case ENEMY_CASTLE_BOSS1_BLUE:
	case ENEMY_CASTLE_BOSS1_PURPLE:
	case ENEMY_CASTLE_BOSS1_GREEN:
	case ENEMY_CASTLE_BOSS1_GOLD:
	case ENEMY_CASTLE_BOSS1_BLACK:
	case ENEMY_CASTLE_BOSS2:
	case ENEMY_CASTLE_BOSS2_RED:
	case ENEMY_CASTLE_BOSS2_BLUE:
	case ENEMY_CASTLE_BOSS2_PURPLE:
	case ENEMY_CASTLE_BOSS2_GREEN:
	case ENEMY_CASTLE_BOSS2_GOLD:
	case ENEMY_CASTLE_BOSS2_BLACK:
	case ENEMY_CASTLE_BOSS3:
	case ENEMY_CASTLE_BOSS3_RED:
	case ENEMY_CASTLE_BOSS3_BLUE:
	case ENEMY_CASTLE_BOSS3_PURPLE:
	case ENEMY_CASTLE_BOSS3_GREEN:
	case ENEMY_CASTLE_BOSS3_GOLD:
	case ENEMY_CASTLE_BOSS3_BLACK:
	case ENEMY_CASTLE_BOSS4:
	case ENEMY_CASTLE_BOSS4_RED:
	case ENEMY_CASTLE_BOSS4_BLUE:
	case ENEMY_CASTLE_BOSS4_PURPLE:
	case ENEMY_CASTLE_BOSS4_GREEN:
	case ENEMY_CASTLE_BOSS4_GOLD:
	case ENEMY_CASTLE_BOSS4_BLACK:
	case ENEMY_LABETH:
	case ENEMY_ELKEIN:
		break;
	case ENEMY_DARKDRAGON:
		pDest->dirF = 1 - pDest->dirF;
		InitMotion(pDest);
		break;
	default:
		//맥스 부매랑에 맞아도 방향전환 안되는.
		if (robin.bossRoom == false && (attacker < BULLET || attacker >= ENEMY || (ao[attacker].moveHandler == BULLETBOOMERANGMOVE && ao[attacker].etc != 6))) {
			//부매랑에 맞으면 전환되는 v.
			//if (robin.bossRoom == false) {
			if (ao[dest].type == 0 && dest != 0)
				break;

			pDest->dirX = pDest->dirF = (pDest->x > ao[attackerObj].x) ? LEFT : RIGHT;
		}
		break;
	}
	//#ifdef TESTINVINCIBLE

	//pDest->hp -= 10000;

	//#endif

	//#else
	switch (pDest->type) {
	case ENEMY_GOLEM:
	case ENEMY_GOLEM_RED:
	case ENEMY_GOLEM_BLUE:
	case ENEMY_GOLEM_PURPLE:
	case ENEMY_GOLEM_GREEN:
	case ENEMY_GOLEM_GOLD:
	case ENEMY_GOLEM_BLACK:
		if (pDest->etc == GOLEM_GUARD) {//골렘 가드모드일때)
			damage = 0;
		}
		break;
	case ENEMY_KNIGHT:
	case ENEMY_KNIGHT_RED:
	case ENEMY_KNIGHT_BLUE:
	case ENEMY_KNIGHT_PURPLE:
	case ENEMY_KNIGHT_GREEN:
	case ENEMY_KNIGHT_GOLD:
	case ENEMY_KNIGHT_BLACK:
		if (pDest->etc == KNIGHT_GUARDED) {
			damage = 0;
		}
		break;
	case ENEMY_KIMERA:
	case ENEMY_KIMERA_RED:
	case ENEMY_KIMERA_BLUE:
	case ENEMY_KIMERA_PURPLE:
	case ENEMY_KIMERA_GREEN:
	case ENEMY_KIMERA_GOLD:
	case ENEMY_KIMERA_BLACK:
		if (pDest->etc == KIMERA_SPINED) {
			damage = 0;
		}
		break;
	case ENEMY_SPIDER:
	case ENEMY_SPIDER_RED:
	case ENEMY_SPIDER_BLUE:
	case ENEMY_SPIDER_PURPLE:
	case ENEMY_SPIDER_GREEN:
	case ENEMY_SPIDER_GOLD:
	case ENEMY_SPIDER_BLACK:
		if (pDest->etc == SPIDER_GUARD) {
			damage = 0;
		}
		break;
		//case NPC_ELKEIN:
	case ENEMY_ELKEIN:
	case ENEMY_ELKEIN_RED:
	case ENEMY_ELKEIN_BLUE:
	case ENEMY_ELKEIN_PURPLE:
	case ENEMY_ELKEIN_GREEN:
	case ENEMY_ELKEIN_GOLD:
	case ENEMY_ELKEIN_BLACK:
		//데미지 줄여주는 버젼
		if (pDest->etc == ELKEIN_GUARD)
			damage /= (1 + PO_C110_BOSS_G5 - pDest->motion);
		break;
		//달팽이가 몸을 움츠린 상태이면, 데미지 25%로 감소
	case ENEMY_SNAIL:
	case ENEMY_SNAIL_RED:
	case ENEMY_SNAIL_BLUE:
	case ENEMY_SNAIL_PURPLE:
	case ENEMY_SNAIL_GREEN:
	case ENEMY_SNAIL_GOLD:
	case ENEMY_SNAIL_BLACK:
		if (pDest->motion == PO_C3_D2) {
			damage /= 4;
		}
		break;
	}

	//속성공격 이펙트 적용 및 디버프 처리
	if (damage > 0 && attacker < BULLET) {
		//주인공이 공격한 경우

		if (attackAttr) {
			pDest->attr = attackAttr;

			//속성공격시 20% 확률로 디버프 걸어주기
			if (robin.bossRoom == false && Random(100) < *(attackerPs + PS_HPDRAIN)) {
				i = attrToDebuf[attackAttr];
				pDest->debuf[i] = debufStartFrame[i];
				pDest->debufOwner[i] = attacker;
			}
		}
	}
	else {
		//총알이 공격한 경우
		pDest->attr = pAttack->attr;
		//디버프 걸어주기
		if (pAttack->moveHandler == BULLETITEMMOVE && robin.bossRoom == false) {
			i = attrToDebuf[pAttack->attr];

			if (Random(2) <= pAttack->etc) {
				pDest->debuf[i] = debufStartFrame[i];
				pDest->debufOwner[i] = pAttack->target;
			}
		}
	}

NEXT:

	if (damage < 1)
		damage = 1;

	//betHeart
	damage *= betHeart[bet];

	pDest->attackedFrame = ATTACKEDFRAME;

	if (ao[dest].type == ENEMY_MAMMOTH && ao[dest].shield > 0) {
		ao[dest].shield -= damage;

		if (ao[dest].etc <= MAMMOTH_SHOT) {
			if (ao[dest].shieldMax * 7 / 10 > ao[dest].shield) {
				ao[dest].shield = ao[dest].shieldMax * 7 / 10;
				ao[dest].etc = MAMMOTH_BREAK0;
			}
		}
		else if (ao[dest].etc <= MAMMOTH_BREAK0_SHOT) {
			if (ao[dest].shieldMax * 4 / 10 > ao[dest].shield) {
				ao[dest].shield = ao[dest].shieldMax * 4 / 10;
				ao[dest].etc = MAMMOTH_BREAK1;
			}
		}
		else if (ao[dest].etc <= MAMMOTH_BREAK1_SHOCKWAVE) {
			if (0 > ao[dest].shield) {
				ao[dest].shield = 0;
				ao[dest].etc = MAMMOTH_BREAK2;
			}
		}
	}
	else if (pDest->type == ENEMY_CASTLE_BOSS2) {
		if (ao[dest].shield > 0) {
			ao[dest].shield -= damage;
		}
		else {
			if (ao[dest].etc != ELKEIN2_WEAK)
				ao[dest].etc = ELKEIN2_WEAK;
			ao[dest].shield = 0;
			if (damage > ao[dest].hp)
				damage = ao[dest].hp;
			//AddBar(&bar[BAR_ENEMYHP + GetEnemyBarIdx(dest)], Min(-damage, ao[dest].maxhp - ao[dest].hp), BARFRAME);
			AddBar(&bar[BAR_BOSSHP], -damage, BARFRAME);
		}
	}
	else {

		//AddBar(&bar[BAR_ENEMYHP + GetEnemyBarIdx(dest)], Min(-damage, ao[dest].maxhp - ao[dest].hp), BARFRAME);
		if (damage > ao[dest].hp)
			damage = ao[dest].hp;
		ao[dest].hp -= damage;
		AddBar(&bar[BAR_BOSSHP], -damage, BARFRAME);

		if (pDest->moveHandler == DEBRIONARMMOVE || pDest->moveHandler == FOLLOWMOMMOVE)
			pDest->jumpFrame = 24;
		else if (pDest->moveHandler == BUGMOVE)
			pDest->attackFrame = 24;
	}

	if (attacker < ENEMY) {
		effect.shake = 6 - pAttack->attackLv;

	}

	//대미지 머리에 띄워주기
	if ((ad >> ATTACK_EXTRA) % 2 || (ad >> ATTACK_CRITICAL) % 2)
		SetDmgNum(attacker, dest, damage, true, attackType, DMGNUMZOOM);
	else
		SetDmgNum(attacker, dest, damage, false, attackType, DMGNUMZOOM);

	//스킬이면 데미지를 합산해 준다.
	int realAttacker = attacker;
	if (realAttacker >= BULLET && ao[realAttacker].target < TOTALCHAR)
		realAttacker = ao[realAttacker].target;


	//if (ao[realAttacker].attack >= ATTACK_SKILL) {
		ao[realAttacker].hitDmg += damage;
		bar[BAR_BATTLECOIN].max = ao[realAttacker].hitDmg;
	//}

	ad = AttackObj2(attacker, dest, ad, attackerType);

	if (pAttack/* && (ao[attacker].mom < TOTALCHAR)*/) {
		/*
		if ((ad >> ATTACK_EXTRA) % 2 || (ad >> ATTACK_CRITICAL) % 2 || damage >= dmgOrigin * 2) {
			i = HITMARK_LARGE;
			Vibration();
		}
		else if (damage >= dmgOrigin)
			i = HITMARK_MEDIUM;
		else
			i = HITMARK_SMALL;
		*/

		i = HITMARK_SMALL;
		SetHitMark(crX + (crW >> 1) + (Random(2) == 0 ? 1 : -1) * Random(TSIZE / 2), crY + (crH >> 1), (pAttack->x <= pDest->x) ? LEFT : RIGHT, (pAttack->cmf % 3), i, attacker < PLAYERALL ? attacker : ao[attacker].target, HITMARKZOOM/*attacker < PLAYERALL ? ao[attacker].zoom : ao[ao[attacker].target].zoom*/);
		if (refreshRate == FPS)
			refreshRate = FPSDOWN_HIT;

	}

	if (ao[dest].debuf[STUN]) {
		ao[dest].debuf[STUN] = false;
		ao[dest].attacked = false;
		ao[dest].attackedFrame = false;
	}

	switch (drawHandle) {
	case MD_PLAY:
	case MD_BATTLE:
		break;
		/*
		case MD_BATTLE:
			switch (attackType) {
			case ROULETTE_COIN:
				//if (pAttack->hitCount <= 1) {
					i = DropItem(pAttack, ITEM_GOLD);
					ao[i].target = realAttacker;
					//SetCurrencyMarkGold(xOffset + pDest->x - rx, STATUSWIN_Y + (rh - 4) * TSIZE - (pDest->y - OBJIMGGAP) - ry, attackType);
				//}
				break;
			}
			break;
		*/
	}

	BackUpEnemyObj();
	SaveGame();

	return (ad >> ATTACK_PIERCE) % 2;
}

int AttackObj2(int attacker, int dest, int ad, int attackerType)
{
	int i;
	int isDummy = (attacker >= PLAYER && attacker < PLAYERALL) ? true : false;
	//int isDummy = false;
	OBJECT* pAttack = &ao[attacker];
	OBJECT* pDest = &ao[dest];

	if (attacker >= TOTALOBJECT)
		goto NEXT;

	//만약 크리티컬이거나, 모션이 센포즈이면
	if (attackerType < TOTALCHAR)
		EffectSound(M_SWORDHIT + attackerType);
	//CREW의 총탄이면
	else
		EffectSound(M_LASER2);
	//PlayMusic(M_SWORDHIT + attackerType);

	//밀어주기

	//pDest->attacked = true;
	//pDest->attackedFrame = ATTACKEDFRAME;
#ifdef ATTACKEDINVINCIBLE
	//pDest->invincible = ATTACKEDFRAME;
#endif	

NEXT:
	if (pDest->hp <= 0) {
		if ((pDest->type == ENEMY_DEATH
			|| pDest->type == ENEMY_DEATH_RED
			|| pDest->type == ENEMY_DEATH_BLUE
			|| pDest->type == ENEMY_DEATH_PURPLE
			|| pDest->type == ENEMY_DEATH_GREEN
			|| pDest->type == ENEMY_DEATH_GOLD
			|| pDest->type == ENEMY_DEATH_BLACK
			) && pDest->etc < DEATH_BROKEN) {
			pDest->hp = pDest->maxhp;
			pDest->etc = DEATH_BREAK_READY;
			bar[BAR_ENEMYHP + GetEnemyBarIdx(GetObjFromPtr(pDest))].add = bar[BAR_ENEMYHP + GetEnemyBarIdx(GetObjFromPtr(pDest))].count = 0;
			AddBar(&bar[BAR_ENEMYHP + GetEnemyBarIdx(GetObjFromPtr(pDest))], pDest->hp, BARFRAME);

			return false;
		}

		switch (pDest->type) {
			//테트라쿤 소환 벌레들 예외처리
		case ENEMY_CASTLE_BOSS3:
		case ENEMY_CASTLE_BOSS3_RED:
		case ENEMY_CASTLE_BOSS3_BLUE:
		case ENEMY_CASTLE_BOSS3_PURPLE:
		case ENEMY_CASTLE_BOSS3_GREEN:
		case ENEMY_CASTLE_BOSS3_GOLD:
		case ENEMY_CASTLE_BOSS3_BLACK:
			if (pDest->moveHandler == BUGMOVE) {
				memset(pDest, 0, sizeof(OBJECT));
				return 0;
			}
			break;
		case ENEMY_LIGHTNING:
		case ENEMY_LIGHTNING_RED:
		case ENEMY_LIGHTNING_BLUE:
		case ENEMY_LIGHTNING_PURPLE:
		case ENEMY_LIGHTNING_GREEN:
		case ENEMY_LIGHTNING_GOLD:
		case ENEMY_LIGHTNING_BLACK:
			// 크리스탈이 소환하는 라이트닝
			if (ao[pDest->mom].type == ENEMY_CRYSTAL) {
				ao[pDest->mom].mx--;
				memset(pDest, 0, sizeof(OBJECT));

				return 0;
			}
			break;
		case ENEMY_SLING:
			break;
		}

		//int exps = pDest->maxhp;

		//exps = RoundDiv(exps * (100 + pAttack->ps[PS_EXPMOD]), 100);

		switch (pDest->type) {
		case ENEMY_CASTLE_BOSS4:
		case ENEMY_CASTLE_BOSS4_RED:
		case ENEMY_CASTLE_BOSS4_BLUE:
		case ENEMY_CASTLE_BOSS4_PURPLE:
		case ENEMY_CASTLE_BOSS4_GREEN:
		case ENEMY_CASTLE_BOSS4_GOLD:
		case ENEMY_CASTLE_BOSS4_BLACK:
			break;
			//테트라쿤 껍질 예외처리
		case ENEMY_CASTLE_BOSS3:
		case ENEMY_CASTLE_BOSS3_RED:
		case ENEMY_CASTLE_BOSS3_BLUE:
		case ENEMY_CASTLE_BOSS3_PURPLE:
		case ENEMY_CASTLE_BOSS3_GREEN:
		case ENEMY_CASTLE_BOSS3_GOLD:
		case ENEMY_CASTLE_BOSS3_BLACK:
			if (pDest->moveHandler == FOLLOWMOMMOVE) {
				if (pDest->motion == PO_C50_UPSKIN)
					ao[pDest->mom].attack = ao[pDest->mom].attack == 0 ? 1 : 3;
				else if (pDest->motion == PO_C50_DOWNSKIN)
					ao[pDest->mom].attack = ao[pDest->mom].attack == 0 ? 2 : 3;

				pDest->active = 0;
				//pDest->hp = pDest->maxhp;
				//pDest->dead = true;
				//pDest->frame = 0;
				//bar[BAR_ENEMYHP + GetEnemyBarIdx(GetObjFromPtr(pDest))].add = bar[BAR_ENEMYHP + GetEnemyBarIdx(GetObjFromPtr(pDest))].count = 0;
				//AddBar(&bar[BAR_ENEMYHP + GetEnemyBarIdx(GetObjFromPtr(pDest))], pDest->hp, BARFRAME);

				return 0;
			}
			//테트라쿤 본체 예외처리
			else if (pDest->moveHandler == ENEMYMOVE) {
				int t;

				//소환된것들 모두 제거함.
				for (t = pDest->mom + 8; t < NEUTRAL; t++) {
					if (ao[t].type == ENEMY_CASTLE_BOSS3)
						memset(&ao[t], 0, sizeof(OBJECT));
				}

				//pDest->hp = pDest->maxhp;
				//pDest->frame = 0;
				//pDest->attack = false;
				//bar[BAR_ENEMYHP + GetEnemyBarIdx(GetObjFromPtr(pDest))].add = bar[BAR_ENEMYHP + GetEnemyBarIdx(GetObjFromPtr(pDest))].count = 0;
				//AddBar(&bar[BAR_ENEMYHP + GetEnemyBarIdx(GetObjFromPtr(pDest))], pDest->hp, BARFRAME);

				goto ENEMYDIE;
			}
			break;
		case ENEMY_CASTLE_BOSS2:
		case ENEMY_CASTLE_BOSS2_RED:
		case ENEMY_CASTLE_BOSS2_BLUE:
		case ENEMY_CASTLE_BOSS2_PURPLE:
		case ENEMY_CASTLE_BOSS2_GREEN:
		case ENEMY_CASTLE_BOSS2_GOLD:
		case ENEMY_CASTLE_BOSS2_BLACK:
			break;
		case ENEMY_CASTLE_BOSS1:
		case ENEMY_CASTLE_BOSS1_RED:
		case ENEMY_CASTLE_BOSS1_BLUE:
		case ENEMY_CASTLE_BOSS1_PURPLE:
		case ENEMY_CASTLE_BOSS1_GREEN:
		case ENEMY_CASTLE_BOSS1_GOLD:
		case ENEMY_CASTLE_BOSS1_BLACK:
			if (pDest->moveHandler == DEBRIONARMMOVE) {
				pDest->frame = 0;
				pDest->etc = pDest->etc < CASTLEBOSS1_UARM_DIE ? CASTLEBOSS1_UARM_DIE : CASTLEBOSS1_DARM_DIE;

				return 0;
			}
			break;
		case ENEMY_FROG:
		case ENEMY_FROG_RED:
		case ENEMY_FROG_BLUE:
		case ENEMY_FROG_PURPLE:
		case ENEMY_FROG_GREEN:
		case ENEMY_FROG_GOLD:
		case ENEMY_FROG_BLACK:
			break;
		case ENEMY_MACHINE:
		case ENEMY_MACHINE_RED:
		case ENEMY_MACHINE_BLUE:
		case ENEMY_MACHINE_PURPLE:
		case ENEMY_MACHINE_GREEN:
		case ENEMY_MACHINE_GOLD:
		case ENEMY_MACHINE_BLACK:
			break;
		case ENEMY_GIANT:
		case ENEMY_GIANT_RED:
		case ENEMY_GIANT_BLUE:
		case ENEMY_GIANT_PURPLE:
		case ENEMY_GIANT_GREEN:
		case ENEMY_GIANT_GOLD:
		case ENEMY_GIANT_BLACK:
			break;
		case ENEMY_KIMERA:
		case ENEMY_KIMERA_RED:
		case ENEMY_KIMERA_BLUE:
		case ENEMY_KIMERA_PURPLE:
		case ENEMY_KIMERA_GREEN:
		case ENEMY_KIMERA_GOLD:
		case ENEMY_KIMERA_BLACK:
			break;
		case ENEMY_IFRIT:
		case ENEMY_IFRIT_RED:
		case ENEMY_IFRIT_BLUE:
		case ENEMY_IFRIT_PURPLE:
		case ENEMY_IFRIT_GREEN:
		case ENEMY_IFRIT_GOLD:
		case ENEMY_IFRIT_BLACK:
			break;
		case ENEMY_ANGEL:
		case ENEMY_ANGEL_RED:
		case ENEMY_ANGEL_BLUE:
		case ENEMY_ANGEL_PURPLE:
		case ENEMY_ANGEL_GREEN:
		case ENEMY_ANGEL_GOLD:
		case ENEMY_ANGEL_BLACK:
			break;
		case ENEMY_MAMMOTH:
		case ENEMY_MAMMOTH_RED:
		case ENEMY_MAMMOTH_BLUE:
		case ENEMY_MAMMOTH_PURPLE:
		case ENEMY_MAMMOTH_GREEN:
		case ENEMY_MAMMOTH_GOLD:
		case ENEMY_MAMMOTH_BLACK:
			break;
		case ENEMY_FOGRA:
		case ENEMY_FOGRA_RED:
		case ENEMY_FOGRA_BLUE:
		case ENEMY_FOGRA_PURPLE:
		case ENEMY_FOGRA_GREEN:
		case ENEMY_FOGRA_GOLD:
		case ENEMY_FOGRA_BLACK:

			break;
		case ENEMY_BAHAMUT:
		case ENEMY_BAHAMUT_RED:
		case ENEMY_BAHAMUT_BLUE:
		case ENEMY_BAHAMUT_PURPLE:
		case ENEMY_BAHAMUT_GREEN:
		case ENEMY_BAHAMUT_GOLD:
		case ENEMY_BAHAMUT_BLACK:
			break;
		case ENEMY_DEATH:
		case ENEMY_DEATH_RED:
		case ENEMY_DEATH_BLUE:
		case ENEMY_DEATH_PURPLE:
		case ENEMY_DEATH_GREEN:
		case ENEMY_DEATH_GOLD:
		case ENEMY_DEATH_BLACK:
			break;
		case NPC_LABETH:
		case ENEMY_LABETH:
		case ENEMY_LABETH_RED:
		case ENEMY_LABETH_BLUE:
		case ENEMY_LABETH_PURPLE:
		case ENEMY_LABETH_GREEN:
		case ENEMY_LABETH_GOLD:
		case ENEMY_LABETH_BLACK:
		case NPC_ELKEIN:
		case ENEMY_ELKEIN:
		case ENEMY_ELKEIN_RED:
		case ENEMY_ELKEIN_BLUE:
		case ENEMY_ELKEIN_PURPLE:
		case ENEMY_ELKEIN_GREEN:
		case ENEMY_ELKEIN_GOLD:
		case ENEMY_ELKEIN_BLACK:
		case NPC_DELPIOS:
			break;
		}
	ENEMYDIE:
		//잔챙이들 다 없애주기
		for (i = GetObjFromPtr(pDest) + 1; i < NEUTRAL; i++) {
			if (ao[i].mom == GetObjFromPtr(pDest))
				memset(&ao[i], 0, sizeof(OBJECT));
		}

		pDest->hp = 0;
		pDest->dead = true;
		memset(&robin.enemyObj, 0, sizeof(OBJECT));
		pDest->frame = 0;
		//EffectSound(M_ENEMYDEAD);
		PlayMusic(M_ENEMYDEAD);
		//PlayMusic(M_BANG);

		switch (pDest->moveHandler) {
		case SHIPSUBMOVE:
			pDest->frame = 0;
			ao[pDest->mom].status--;

			if (pDest->etc == SHIP_CANNONATTACK) {
				for (i = GetObjFromPtr(pDest) + 1; i < pDest->mom; i++) {
					if (ao[i].motion == PO_C28_CA4_0 || ao[i].motion == PO_C28_CA3_0 || ao[i].motion == PO_C28_CA2_0 || ao[i].motion == PO_C28_CA1_0) {
						ao[i].frame = 0;
						ao[i].etc = SHIP_CANNONATTACK;
						goto CANNON;
					}
				}

				ao[pDest->mom].frame = 0;
				ao[pDest->mom].etc = SHIP_MOVE;
			}

		CANNON:
			pDest->etc = SHIP_CANNONBREAK;
			pDest->attack = PO_C28_CA12_B0;

			if (ao[pDest->mom].status == 0) {
				ao[pDest->mom].etc = SHIP_APPEARWEAK;
				ao[pDest->mom].frame = 0;
			}

			InitMotion(pDest);
			break;
		case SHIPMAINMOVE:

			if (drawHandle == MD_PLAY || drawHandle == MD_BATTLE || drawHandle == MD_RAID || drawHandle == MD_BOSSRAID) {
				pDest->moveHandler = VANISHMOVE;
				break;
			}
			return 0;
		case MACHINEBOSSMOVE:
			break;
		default:
			pDest->moveHandler = VANISHMOVE;
			pDest->frame = 0;
			break;
		}

		switch (pDest->type) {
			//case ENEMY_SHIP:
			//	break;
		default:
			switch (pDest->type) {
			case ENEMY_SHIP:
				break;
			default:
				pDest->drawHandler = VANISHDRAW;
				break;
			}

			if (robin.curWaveIdx == GetMaxWaveCnt() && AliveEnemyCnt() == 0) {
				waveStatus = WAVESTATUS_END;
				for (i = 0; i < TOTALCHAR; i++)
					ao[i].attack = false;


			}
			break;
		}

		//if (pDest->type == ENEMY_SHIP && GetObjFromPtr(pDest) < ENEMY + 4) {
		//	pDest->attack += 4 * Abs(dest - ENEMY + 4);
		//	pDest->drawHandler = MACHINEDRAW;
		//}
		//else
		//	pDest->drawHandler = VANISHDRAW;

		memset(pDest->debuf, 0, sizeof(pDest->debuf));

	}
	else {
		//추가공격을 해준다.
		if ((ad >> ATTACK_EXTRA) % 2 == 1)
			AttackObj(-(attacker + 1), dest);
	}

	return ad;
}

//플레이어가 몬스터를 공격하는
int AttackEnemyCheck(int obj)
{
	int i, j, k, rt = 0, count = 0;
	int distance[ITEMOBJ - ENEMYUSEROBJ];
	int sort[ITEMOBJ - ENEMYUSEROBJ];
	int sorted = false;
	int startObj;
	int endObj;

	//모션이 바뀔 때 역할을 한다.
	if (robin.playtime % MOTIONDIV != 0)
		return false;

	if (obj < PLAYERALL) {
		startObj = PLAYER;
		endObj = ENEMYUSEROBJ;
	}
	else {
		startObj = ENEMYUSEROBJ;
		endObj = ITEMOBJ;
	}

	memset(sort, 0, sizeof(sort));

	for (i = ENEMYUSEROBJ; i < NEUTRAL; i++) {
		if (i != obj && ao[i].active && !ao[i].dead && ao[i].maxhp > 0) {
			distance[i - ENEMYUSEROBJ] = (ao[obj].x - ao[i].x) * (ao[obj].x - ao[i].x) + (ao[obj].y - ao[i].y) * (ao[obj].y - ao[i].y);
			sort[count] = i;
			count++;
		}
	}

	if (count) {
		for (i = 1; i < count && sorted == false; i++) {
			sorted = true;

			for (j = 0; j < count - i; j++) {
				if (distance[sort[j] - ENEMYUSEROBJ] > distance[sort[j + 1] - ENEMYUSEROBJ]) {
					temp = distance[sort[j] - ENEMYUSEROBJ];
					distance[sort[j] - ENEMYUSEROBJ] = distance[sort[j + 1] - ENEMYUSEROBJ];
					distance[sort[j + 1] - ENEMYUSEROBJ] = temp;

					temp = sort[j];
					sort[j] = sort[j + 1];
					sort[j + 1] = temp;

					sorted = false;
				}
			}
		}

		for (i = 0; i < count; i++) {
			if (sort[i]) {
				if (AttackCrash(&ao[obj], &ao[sort[i]])) {

					//달성도 초기화 : 성인(적을 공격하지 않고 연속으로 죽은 횟수)
					rpVar2.saint = 0;

					//내가 때리는 적을 우선으로 창을 보여준다.
					if ((obj >= PLAYER && obj < PLAYERALL) || (ao[obj].moveHandler == BULLETBOOMERANGMOVE && (ao[obj].target >= PLAYER && ao[obj].target < PLAYERALL))) {
						curEnemy = sort[i];
						curEnemyFrame = INFOFRAME;
					}

					rt = sort[i];

					if (!AttackObj(obj, sort[i])) {
						if (ao[obj].moveHandler == BULLETBOOMERANGMOVE) {
							ao[obj].status = Max(0, ao[obj].status - 1);
						}

						break;
					}
				}
			}
		}

		if (curEnemyFrame < 2) {
			if (rt && obj < ENEMYUSEROBJ) {
				if (rt == curEnemy) {
					curEnemyFrame = INFOFRAME - 3;
				}
				else {
					// curEnemy표시되면 안되는 것들 예외처리
					// AttackPlayerCheck에서도 같은 처리 해줘야함.
					switch (ao[rt].type) {
					case ENEMY_CASTLE_BOSS1:
					case ENEMY_CASTLE_BOSS1_RED:
					case ENEMY_CASTLE_BOSS1_BLUE:
					case ENEMY_CASTLE_BOSS1_PURPLE:
					case ENEMY_CASTLE_BOSS1_GREEN:
					case ENEMY_CASTLE_BOSS1_GOLD:
					case ENEMY_CASTLE_BOSS1_BLACK:
						if (ao[obj].moveHandler == DEBRIONBODYMOVE || ao[obj].moveHandler == DEBRIONARMMOVE) {// && pObj->tileX2 > 0) {
							curEnemy = rt;
							curEnemyFrame = INFOFRAME;
						}
						break;
					case ENEMY_MACHINE:
					case ENEMY_MACHINE_RED:
					case ENEMY_MACHINE_BLUE:
					case ENEMY_MACHINE_PURPLE:
					case ENEMY_MACHINE_GREEN:
					case ENEMY_MACHINE_GOLD:
					case ENEMY_MACHINE_BLACK:
						if (ao[obj].moveHandler == MACHINEBOSSMOVE) {
							curEnemy = rt;
							curEnemyFrame = INFOFRAME;
						}
						break;
					case ENEMY_BAHAMUT:
					case ENEMY_BAHAMUT_RED:
					case ENEMY_BAHAMUT_BLUE:
					case ENEMY_BAHAMUT_PURPLE:
					case ENEMY_BAHAMUT_GREEN:
					case ENEMY_BAHAMUT_GOLD:
					case ENEMY_BAHAMUT_BLACK:
						if (ao[obj].moveHandler == BAHAMUTHEADMOVE) {
							curEnemy = rt;
							curEnemyFrame = INFOFRAME;
						}
						break;
					case ENEMY_DARKDRAGON:
					case ENEMY_DARKDRAGON_RED:
					case ENEMY_DARKDRAGON_BLUE:
					case ENEMY_DARKDRAGON_PURPLE:
					case ENEMY_DARKDRAGON_GREEN:
					case ENEMY_DARKDRAGON_GOLD:
					case ENEMY_DARKDRAGON_BLACK:
						if (ao[obj].frame == 1) {
							curEnemy = rt;
							curEnemyFrame = INFOFRAME;
						}
						break;
					case ENEMY_SHIP:
					case ENEMY_SHIP_RED:
					case ENEMY_SHIP_BLUE:
					case ENEMY_SHIP_PURPLE:
					case ENEMY_SHIP_GREEN:
					case ENEMY_SHIP_GOLD:
					case ENEMY_SHIP_BLACK:
						if (ao[obj].moveHandler == SHIPMAINMOVE) {
							curEnemy = rt;
							curEnemyFrame = INFOFRAME;
						}
						break;
					case ENEMY_FOGRA:
					case ENEMY_FOGRA_RED:
					case ENEMY_FOGRA_BLUE:
					case ENEMY_FOGRA_PURPLE:
					case ENEMY_FOGRA_GREEN:
					case ENEMY_FOGRA_GOLD:
					case ENEMY_FOGRA_BLACK:
						if (ao[obj].moveHandler == FOGRAMOVE) {
							curEnemy = rt;
							curEnemyFrame = INFOFRAME;
						}
						break;
					case ENEMY_CASTLE_BOSS3:
					case ENEMY_CASTLE_BOSS3_RED:
					case ENEMY_CASTLE_BOSS3_BLUE:
					case ENEMY_CASTLE_BOSS3_PURPLE:
					case ENEMY_CASTLE_BOSS3_GREEN:
					case ENEMY_CASTLE_BOSS3_GOLD:
					case ENEMY_CASTLE_BOSS3_BLACK:
						if (ao[obj].moveHandler == ENEMYMOVE) {
							curEnemy = rt;
							curEnemyFrame = INFOFRAME;
						}
						break;
					default:
						curEnemy = rt;
						curEnemyFrame = INFOFRAME;
						break;
					}
				}
			}
		}
	}

	return rt;
}

int EnemyCheck(int obj)
{
	switch (ao[obj].type) {
	case ENEMY_SHIP:
	case ENEMY_SHIP_RED:
	case ENEMY_SHIP_BLUE:
	case ENEMY_SHIP_PURPLE:
	case ENEMY_SHIP_GREEN:
	case ENEMY_SHIP_GOLD:
	case ENEMY_SHIP_BLACK:
		if (ao[obj].drawHandler != NULL)
			return true;
		break;
	case ENEMY_MACHINE:
	case ENEMY_MACHINE_RED:
	case ENEMY_MACHINE_BLUE:
	case ENEMY_MACHINE_PURPLE:
	case ENEMY_MACHINE_GREEN:
	case ENEMY_MACHINE_GOLD:
	case ENEMY_MACHINE_BLACK:
		if (ao[obj].moveHandler == MACHINEBOSSMOVE)
			return true;
		break;
	default:
		if (ao[obj].maxhp != 0 && ao[obj].type < NPC_CAPTAIN)
			return true;
	}

	return false;

	//고대의 방주 특수처리
	//if (ao[obj].type == ENEMY_SHIP) {
	//	if (ao[obj].drawHandler != NULL)
	//		return true;
	//}
	//else if (ao[obj].type == ENEMY_MACHINE) {
	//	if (ao[obj].moveHandler != MACHINEMOVE)
	//		return true;
	//}
	//else if (ao[obj].type < NPC_CAPTAIN || ao[obj].type == NPC_DEVIL13_LABETH || ao[obj].type == NPC_LASTDEVIL13_ELKEIN)
	//	return true;

	//return false;
}


//몬스터나 타일이 플레이어를 공격하는
void AttackPlayerCheck(OBJECT* pObj)
{
	int i, j;
	int obj = GetObjFromPtr(pObj);

	//모션이 바뀔 때 역할을 한다.
	if (robin.playtime % MOTIONDIV != 0)
		return;

	for (i = ENEMY; i < ITEMOBJ; i++) {
		//		if (ao[i].active && !ao[i].dead && (cmfLoaded[ao[i].cmf] < NPC_CAPTAIN || ao[i].type == NPC_ELKEIN || ao[i].type == NPC_LABETH)) {
		if (ao[i].active && !ao[i].dead) {
			if (ao[i].maxhp > 0 && DistanceCheck(&ao[i], pObj, 6 * TSIZE) && curEnemyFrame < 2) {
				if (i == curEnemy) {
					curEnemyFrame = INFOFRAME - 3;
				}
				else {
					// curEnemy표시되면 안되는 것들 예외처리
					// AttackEnemyCheck에서도 같은 처리 해줘야함.
					switch (ao[i].type) {
					case ENEMY_CASTLE_BOSS1:
					case ENEMY_CASTLE_BOSS1_RED:
					case ENEMY_CASTLE_BOSS1_BLUE:
					case ENEMY_CASTLE_BOSS1_PURPLE:
					case ENEMY_CASTLE_BOSS1_GREEN:
					case ENEMY_CASTLE_BOSS1_GOLD:
					case ENEMY_CASTLE_BOSS1_BLACK:
						if (ao[i].moveHandler == DEBRIONBODYMOVE || ao[i].moveHandler == DEBRIONARMMOVE) {// && pObj->tileX2 > 0) {
							curEnemy = i;
							curEnemyFrame = INFOFRAME;
						}
						break;
					case ENEMY_MACHINE:
					case ENEMY_MACHINE_RED:
					case ENEMY_MACHINE_BLUE:
					case ENEMY_MACHINE_PURPLE:
					case ENEMY_MACHINE_GREEN:
					case ENEMY_MACHINE_GOLD:
					case ENEMY_MACHINE_BLACK:
						if (ao[i].moveHandler == MACHINEBOSSMOVE) {
							curEnemy = i;
							curEnemyFrame = INFOFRAME;
						}
						break;
					case ENEMY_BAHAMUT:
					case ENEMY_BAHAMUT_RED:
					case ENEMY_BAHAMUT_BLUE:
					case ENEMY_BAHAMUT_PURPLE:
					case ENEMY_BAHAMUT_GREEN:
					case ENEMY_BAHAMUT_GOLD:
					case ENEMY_BAHAMUT_BLACK:
						if (ao[i].moveHandler == BAHAMUTHEADMOVE) {
							curEnemy = i;
							curEnemyFrame = INFOFRAME;
						}
						break;
					case ENEMY_DARKDRAGON:
					case ENEMY_DARKDRAGON_RED:
					case ENEMY_DARKDRAGON_BLUE:
					case ENEMY_DARKDRAGON_PURPLE:
					case ENEMY_DARKDRAGON_GREEN:
					case ENEMY_DARKDRAGON_GOLD:
					case ENEMY_DARKDRAGON_BLACK:
						if (ao[i].frame == 1) {
							curEnemy = i;
							curEnemyFrame = INFOFRAME;
						}
						break;
					case ENEMY_SHIP:	//고대의 방주46
					case ENEMY_SHIP_RED:
					case ENEMY_SHIP_BLUE:
					case ENEMY_SHIP_PURPLE:
					case ENEMY_SHIP_GREEN:
					case ENEMY_SHIP_GOLD:
					case ENEMY_SHIP_BLACK:
						if (ao[i].moveHandler == SHIPMAINMOVE) {
							curEnemy = i;
							curEnemyFrame = INFOFRAME;
						}
						break;
					case ENEMY_FOGRA:	//아리만47
					case ENEMY_FOGRA_RED:
					case ENEMY_FOGRA_BLUE:
					case ENEMY_FOGRA_PURPLE:
					case ENEMY_FOGRA_GREEN:
					case ENEMY_FOGRA_GOLD:
					case ENEMY_FOGRA_BLACK:
						if (ao[i].moveHandler == FOGRAMOVE) {
							curEnemy = i;
							curEnemyFrame = INFOFRAME;
						}
						break;
					case ENEMY_CASTLE_BOSS3:	//쉐도우 테트라쿤52
					case ENEMY_CASTLE_BOSS3_RED:
					case ENEMY_CASTLE_BOSS3_BLUE:
					case ENEMY_CASTLE_BOSS3_PURPLE:
					case ENEMY_CASTLE_BOSS3_GREEN:
					case ENEMY_CASTLE_BOSS3_GOLD:
					case ENEMY_CASTLE_BOSS3_BLACK:
						if (ao[i].moveHandler == ENEMYMOVE) {
							curEnemy = i;
							curEnemyFrame = INFOFRAME;
						}
						break;
					default:
						curEnemy = i;
						curEnemyFrame = INFOFRAME;
					}
				}
			}

			if ((ao[i].type == ENEMY_MACHINE
				|| ao[i].type == ENEMY_MACHINE_RED
				|| ao[i].type == ENEMY_MACHINE_BLUE
				|| ao[i].type == ENEMY_MACHINE_PURPLE
				|| ao[i].type == ENEMY_MACHINE_GREEN
				|| ao[i].type == ENEMY_MACHINE_GOLD
				|| ao[i].type == ENEMY_MACHINE_BLACK)
				&& (ao[i].motion == PO_C25_DIAGONAL0 || ao[i].motion == PO_C25_DIAGONAL1)) {
				for (j = PLAYER; j < TOTALPLAYER; j++) {
					if (TriHeight(ao[ENEMY].x, ao[ENEMY].y, ao[ENEMY + 3].x, ao[ENEMY + 3].y, ao[j].x, ao[j].y - 10) < 324 || TriHeight(ao[ENEMY + 1].x, ao[ENEMY + 1].y, ao[ENEMY + 2].x, ao[ENEMY + 2].y, ao[j].x, ao[j].y - 10) < 324) {
						AttackRobin(i, j);
						break;
					}
				}
			}
			else if (pObj->attacked == false && AttackCrash(&ao[i], pObj)) {
				//if (turnPosition != COMING && turn >= ENEMY)
				AttackRobin(i, GetObjFromPtr(pObj));

				if (ao[i].maxhp > 0) {
					if (i == curEnemy) {
						if (curEnemyFrame < 2)
							curEnemyFrame = INFOFRAME - 3;
					}
					else {
						// curEnemy표시되면 안되는 것들 예외처리
						// AttackEnemyCheck에서도 같은 처리 해줘야함.
						switch (ao[i].type) {
						case ENEMY_CASTLE_BOSS1:
						case ENEMY_CASTLE_BOSS1_RED:
						case ENEMY_CASTLE_BOSS1_BLUE:
						case ENEMY_CASTLE_BOSS1_PURPLE:
						case ENEMY_CASTLE_BOSS1_GREEN:
						case ENEMY_CASTLE_BOSS1_GOLD:
						case ENEMY_CASTLE_BOSS1_BLACK:
							if (ao[i].moveHandler == DEBRIONBODYMOVE || ao[i].moveHandler == DEBRIONARMMOVE) {// && pObj->tileX2 > 0) {
								curEnemy = i;
								curEnemyFrame = INFOFRAME;
							}
							break;
						case ENEMY_MACHINE:
						case ENEMY_MACHINE_RED:
						case ENEMY_MACHINE_BLUE:
						case ENEMY_MACHINE_PURPLE:
						case ENEMY_MACHINE_GREEN:
						case ENEMY_MACHINE_GOLD:
						case ENEMY_MACHINE_BLACK:
							if (ao[i].moveHandler == MACHINEBOSSMOVE) {
								curEnemy = i;
								curEnemyFrame = INFOFRAME;
							}
							break;
						case ENEMY_BAHAMUT:
						case ENEMY_BAHAMUT_RED:
						case ENEMY_BAHAMUT_BLUE:
						case ENEMY_BAHAMUT_PURPLE:
						case ENEMY_BAHAMUT_GREEN:
						case ENEMY_BAHAMUT_GOLD:
						case ENEMY_BAHAMUT_BLACK:
							if (ao[i].moveHandler == BAHAMUTHEADMOVE) {
								curEnemy = i;
								curEnemyFrame = INFOFRAME;
							}
							break;
						case ENEMY_DARKDRAGON:
						case ENEMY_DARKDRAGON_RED:
						case ENEMY_DARKDRAGON_BLUE:
						case ENEMY_DARKDRAGON_PURPLE:
						case ENEMY_DARKDRAGON_GREEN:
						case ENEMY_DARKDRAGON_GOLD:
						case ENEMY_DARKDRAGON_BLACK:
							if (ao[i].frame == 1) {
								curEnemy = i;
								curEnemyFrame = INFOFRAME;
							}
							break;
						case ENEMY_SHIP:
						case ENEMY_SHIP_RED:
						case ENEMY_SHIP_BLUE:
						case ENEMY_SHIP_PURPLE:
						case ENEMY_SHIP_GREEN:
						case ENEMY_SHIP_GOLD:
						case ENEMY_SHIP_BLACK:
							if (ao[i].moveHandler == SHIPMAINMOVE) {
								curEnemy = i;
								curEnemyFrame = INFOFRAME;
							}
							break;
						case ENEMY_FOGRA:
						case ENEMY_FOGRA_RED:
						case ENEMY_FOGRA_BLUE:
						case ENEMY_FOGRA_PURPLE:
						case ENEMY_FOGRA_GREEN:
						case ENEMY_FOGRA_GOLD:
						case ENEMY_FOGRA_BLACK:
							if (ao[i].moveHandler == FOGRAMOVE) {
								curEnemy = i;
								curEnemyFrame = INFOFRAME;
							}
							break;
						case ENEMY_CASTLE_BOSS3:
						case ENEMY_CASTLE_BOSS3_RED:
						case ENEMY_CASTLE_BOSS3_BLUE:
						case ENEMY_CASTLE_BOSS3_PURPLE:
						case ENEMY_CASTLE_BOSS3_GREEN:
						case ENEMY_CASTLE_BOSS3_GOLD:
						case ENEMY_CASTLE_BOSS3_BLACK:
							if (ao[i].moveHandler == ENEMYMOVE || ao[i].moveHandler == BUGMOVE || ao[i].moveHandler == FOLLOWMOMMOVE) {
								curEnemy = i;
								curEnemyFrame = INFOFRAME;
							}
							break;
						default:
							curEnemy = i;
							curEnemyFrame = INFOFRAME;
						}
					}
				}
			}
		}
	}
}
//몬스터나 타일이 플레이어를 공격하는
void AttackBoxCheck(OBJECT* pObj)
{
	int i, j;

	if (AttackCrash(pObj, &ao[NEUTRAL]) && ao[NEUTRAL].status == BOXSTATUS_CLOSED) {
		ao[NEUTRAL].motion = BOXSTATUS_OPENING;
		ao[NEUTRAL].frame = 0;
	}
}

void ItemCheck(OBJECT* pObj)
{
	int i;
	int obj = GetObjFromPtr(pObj);
	int targetX, targetY;

	cItem = 0;

	if (drawHandle == MD_DEMO)
		return;

	for (i = ITEMOBJ; i < TOTALOBJECT; i++) {
		if (ao[i].active && ObjCrash(&ao[i], pObj) && (cItem != i || itemFrame == 0) && ao[cItem].moveHandler != ITEMGOTOBOXMOVE) {
			if (ao[i].type == OBJ_ITEM) {
				cItem = i;

				if (cItem > 0) {

					if (GetItem(ao[cItem].def, ao[cItem].lv, ao[cItem].apx, ao[cItem].apy, ao[cItem].ax, 0)) {
						//gap = blahBlahDrawStartY + 32 * _2X < STATUSWIN_Y ? 0 : (blahBlahDrawStartY + 32 * _2X - STATUSWIN_Y);

						//if (SCREENRATIO <= 150) {
						//	gap = STATUSWIN_Y + 144 * _2X;
						//}
						//else if (SCREENRATIO <= 179) {
						//	gap = STATUSWIN_Y + 32 * _2X;
						//}
						//else {
						//	gap = STATUSWIN_Y - 238 * _2X;
						//}

						switch (ao[cItem].def) {
						case ITEM_GOLD:
#ifdef GOLDBARLEFTUP
							targetX = xOffset + dmgInfo[dmgIndex].x - (GetNumDx(dmgInfo[dmgIndex].dmg, false, NUM_FONT_LARGE, false, true, 2.0f, true) + ITEMICONSIZE * 2 + 12 * _2X) / 2;
							targetY = STATUSWIN_Y + DRAWROULETTENUMGAP + ITEMICONSIZE * 2;

#else
							targetX = DX / 2 - (GetNumDx(robin.gold, false, NUM_FONT_NORMAL, false) + 32 * _2X + 8 * _2X) / 2;
							targetY = DY - GNBHEIGHT - 8 * _2X;
#endif

							SetItemMark(ao[cItem].x - rx - ao[cItem].cpx - 16 * _2X, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (ao[cItem].y - ao[cItem].cpy - OBJIMGGAP) + 16 * _2X, targetX, targetY, 16 * _2X / MOTIONDIV, ao[cItem].ay * 2 / MOTIONDIV, 0, 1);
							PlayMusic(M_COIN);
							break;
						case ITEM_NETITEM:
							switch (ao[cItem].apx) {
							case ITEM_NET_EXPORB:
								targetX = ao[raidPlayer].x - rx - ao[raidPlayer].cpx;
								targetY = STATUSWIN_Y + (rh - 4) * TSIZE - ry - (ao[raidPlayer].y - ao[raidPlayer].cpy - OBJIMGGAP - 64 * _2X);
								break;
							default:
								targetX = 8 * _2X + 16 * _2X;
								targetY = STATUSWIN_Y + 24 * _2X - 8 * _2X;
								break;
							}
							break;
						default:
							targetX = 8 * _2X + 16 * _2X;
							targetY = STATUSWIN_Y + 24 * _2X - 8 * _2X;
							SetItemMark(ao[cItem].x - rx - ao[cItem].cpx, STATUSWIN_Y + (rh - 4) * TSIZE - ry - (ao[cItem].y - ao[cItem].cpy - OBJIMGGAP), targetX, targetY, 16 * _2X / MOTIONDIV, ao[cItem].ay * 2 / MOTIONDIV, 0, 1);
							switch (ao[cItem].def) {
							case ITEM_HEART:
								PlayMusic(M_ITEM);
								break;
							default:
								PlayMusic(M_ITEM);
								break;
							}
							break;
						}



						//PLAYER 나 SOLDIER 가 획득했을 경우는 골드를 PLAYER 한테 날려준다.

						if (!boxOpenFrame) {
							boxOpenFrame = 1;
							PlayMusic(M_OPENDOOR);
						}
						ao[cItem].active = false;
						//memset(&ao[cItem], 0, sizeof(OBJECT));
						//여기서 날라가게 해준다.
						//ao[cItem].moveHandler = ITEMGOTOBOXMOVE;
					}
				}

				/*
				if (ao[i].etc >= HIDDEN_0 && ao[i].lv == EMPTY)
					continue;

				itemFrame = INFOFRAME;

				if (questFrame == 0) {
					if (ao[cItem].def == ITEM_GOLD) {
						memset(infoStr, 0, 100);
						sprintf(infoStr, "%d ∞ÒµÂ", ao[cItem].apx);
					}
					else if (ao[cItem].ax > 1) {
						//ReadString(ao[cItem].name);
						sprintf(infoStr, "%s %d∞≥", TEXTPTR(ao[cItem].name), ao[cItem].ax);
					}
				}
				 */
			}
			//break;
		}
	}
}

void SetDmgNum(int attacker, int obj, long long dmg, int critical, int type, float zoom)
{
	int i, j, extra = 0;
	bool sameOwner = false;
	int str = 0;
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];
	int collectionIdx;
	int currencyObj;

	if (critical >= 100) {
		critical = 1;
		extra = true;
	}
	switch (drawHandle) {
	case MD_PLAY:
	case MD_BATTLE:
		//MD_PLAY에서는 데미지 세팅을 하지 않는다.
		if (obj >= ENEMY && obj < NEUTRAL) {
			//AddBar(&bar[BAR_ENEMYHP + GetEnemyBarIdx(obj)], Min(-dmg, ao[obj].maxhp - ao[obj].hp), BARFRAME);
			startX = xOffset + ao[obj].x;
			startY = STATUSWIN_Y + (rh - 4) * TSIZE - ao[obj].y - ry + 48 * _2X + Random(8 * _2X);// Min(ao[obj].cpy, -48 * _2X);
			//targetX = bar[BAR_GOLD].x + 6 * _2X + ITEMICONSIZE / 2;
			//targetY = bar[BAR_GOLD].y - 6 * _2X - ITEMICONSIZE / 2;
			//SetCurrencyMarkArr(startX, startY, targetX, targetY, targetX, targetY, 16 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV, CURRENCYWAITINGFRAMEMAX, CURRENCYWAITINGFRAMEMAX, ICON_GOLD, 30, dmg, CURRENCY_GOLD, 3.0f, 2.0f, -0.1f, 2.0f, 1.0f, -0.1f, 10);
			
			if (dmg < 10)
				str = 0;
			else if (dmg < 100)
				str = 1;
			else if (dmg < 1000)
				str = 2;
			else if (dmg < 10000)
				str = 3;
			else if (dmg < 100000)
				str = 4;
			else if (dmg < 1000000)
				str = 5;
			else
				str = 6;
			//for (i = 0; i < 3; i++)
			currencyObj = DropItem(&ao[obj], ITEM_GOLD);
			ao[currencyObj].defaultZoom = ao[currencyObj].zoom = 1.5f + str * 0.5f;
			ao[currencyObj].target = attacker;
			if (obj < PLAYERALL)
				ao[currencyObj].ax = -dmg;
			else
				ao[currencyObj].ax = dmg;
			//SetCurrencyMarkGold(startX, startY, str);
			//AddBar(&bar[BAR_GOLD], dmg, BARFRAME);
			GetItem(ITEM_GOLD, false, false, false, dmg, false);

		}
		else {
			GetItem(ITEM_GOLD, false, false, false, -dmg, false);
			//AddBar(&bar[BAR_GOLD], Max(-robin.gold, -dmg), BARFRAME);
		}
		break;
	}

	if (attacker < ENEMY) {
		int realAttacker = turn;

		//if (attacker >= BULLET && ao[attacker].target < TOTALCHAR)
		//	realAttacker = ao[attacker].target;

		if (ao[realAttacker].hitCountPlus == false) {
			//hitCount++; hitCountFrame = VANISHFRAME_DMG;
			ao[realAttacker].hitCountPlus = true;
		}

		//if (ao[realAttacker].attack >= ATTACK_SKILL) {
			ao[realAttacker].hitCount++;
			if (ao[realAttacker].hitCountFrame == 0)
				ao[realAttacker].hitCountFrame = 1;
			else if (ao[realAttacker].hitCountFrame >= 11)
				ao[realAttacker].hitCountFrame = 11;
		//}
	}

	for (i = 0; i < TOTALHITMARK; i++) {
		if (dmgInfo[i].type == 0) {
			dmgInfo[i].type = critical + 1;

			if (attacker < PLAYERALL) {
				dmgInfo[i].owner = attacker;
			}
			else if (attacker >= BULLET && attacker < ENEMY) {
				if (ao[attacker].active == true) {
					dmgInfo[i].owner = ao[attacker].mom;
				}
			}
			else
				dmgInfo[i].owner = attacker;

			dmgInfo[i].frame = 0;
			dmgInfo[i].dmg = dmg;
			dmgInfo[i].x = ao[obj].x;
			//dmgInfo[i].y = STATUSWIN_Y + (rh - 4) * TSIZE - (ao[obj].y - (obj >= ENEMY ? 64 * _2X : 48 * _2X) - Random(8 * _2X)) - ry;// - (ao[obj].y + ao[obj].cpy - 32 * _2X) - ry;
			dmgInfo[i].y = STATUSWIN_Y + (rh - 4) * TSIZE - (ao[obj].y + ao[obj].cpy - 32 * _2X) - ry;// + DMGNUM_Y;//

			//if (obj < ENEMY) {
			//	dmgInfo[i].x = 32 * _2X;
			//}
			//else {

			//	dmgInfo[i].x = DX - 32 * _2X;
			//}
			//dmgInfo[i].y = STATUSWIN_Y + 64 * _2X + Random(8 * _2X);// - (ao[obj].y + ao[obj].cpy - 32 * _2X) - ry;

			dmgInfo[i].zoom = DMGNUMZOOM;

			//if (extra)
			//	dmgInfo[i].y += 36 * _2X;

			dmgInfo[i].pos = obj;

			for (j = 0; j < TOTALHITMARK; j++) {
				if (j != i && dmgInfo[j].pos == obj)
					dmgInfo[j].y += (16 - dmgInfo[j].frame);
			}
			
			switch (ao[attacker].cmf) {
				case ROBIN:
					dmgInfo[i].color = 0xFFF4C6;
					break;
				case DIANA:
					dmgInfo[i].color = 0xFFF4C6;// 0xF7BEFE;
					break;
				case MAXX:
					dmgInfo[i].color = 0xFFF4C6;// 0xBADCD1;
					break;
				default:
					dmgInfo[i].color = 0xFFF4C6;// null;
					break;
			}
			break;
		}
	}
}

void OrderDmgNum(void)
{
	int i, j, k = 0, temp = 0, maxCount = 0;
	int dmgSort[TOTALHITMARK];
	DMGINFO dmgInfoTemp[TOTALHITMARK];

	memset(&dmgSort, 0, sizeof(dmgSort));

	//먼저 주인공에 해당되는 것들을 뽑는다..
	for (i = 0; i < TOTALHITMARK; i++) {
		if (dmgInfo[i].type != 0) {
			dmgSort[temp] = i;
			temp++;
			maxCount++;
		}
	}

	memset(&dmgInfoTemp, 0, sizeof(dmgInfoTemp));

	//그런 다음 역순으로 우선 주인공것을 먼저 놓고, 그 다음에 용병이 있으면 용병을 넣고
	for (i = 0; i < temp; i++) {
		memcpy(&dmgInfoTemp[maxCount - temp + i], &dmgInfo[dmgSort[i]], sizeof(DMGINFO));
	}

	k = 0;
	for (i = 0; i < maxCount - temp; i++) {
		temp = 0;
		for (j = 0; j < temp; j++) {
			if (dmgSort[j] == i) {
				temp++;
			}
		}

		//주인공거랑 인덱스가 같은게 전혀 없다면
		if (temp == 0) {
			memcpy(&dmgInfoTemp[k], &dmgInfo[i], sizeof(DMGINFO));
			k++;
		}
	}

	//최종적으로 제작한 배열을 원본에 카피를 시킨다.
	memcpy(&dmgInfo, &dmgInfoTemp, sizeof(DMGINFO));
}

int SetImgTextPos(int obj, int type, int x, int y, float zoom)
{
	int index = SetImgText(obj, type, zoom);
	imgText[index].x = x;
	imgText[index].y = y;

	return index;
}

int SetImgText(int obj, int type, float zoom)
{
	int i = 0, j;
	int textObj = obj;
	int gap = 0;

	//if (obj != raidPlayer && !(ao[i].soldier && obj == ao[i].soldier))
	//	return false;

	for (i = 0; i < TOTALHITMARK; i++) {
		if (imgText[i].type == 0) {
			imgText[i].type = type;
			imgText[i].frame = 0;
			imgText[i].dmg = obj;
			imgText[i].owner = obj;
			imgText[i].pos = 0;
			imgText[i].zoom = zoom;

			switch (type) {
			default:
				imgText[i].type = EFFECT_TEXT_EXP;
				imgText[i].dmg = type - 100;

				//imgText[i].x = ao[obj].x;
				//imgText[i].y = ao[obj].y + ao[obj].cpy - 23 * _2X;

				imgText[i].x = PLAYAREA_X / 2;

				//if (SCREENRATIO <= 150)
				//	imgText[i].y = 160 * _2X;
				//else
				//	imgText[i].y = DY - GNBHEIGHT - 160 * _2X;
				//imgText[i].y = STATUSWIN_Y + DRAWROULETTENUMGAP - EFFECTTEXT_Y;// 56 * _2X;
				//imgText[i].y = STATUSWIN_Y + (rh - 4) * TSIZE -(ao[obj].y - 88 * _2X) - ry;// - (ao[obj].y + ao[obj].cpy - 32 * _2X) - ry;// 56 * _2X;
				imgText[i].y = STATUSWIN_Y + IMGTEXT_Y;// - (ao[obj].y + ao[obj].cpy - 32 * _2X) - ry;// 56 * _2X;


				//for (j = 0; j < TOTALHITMARK; j++) {
				//	if (j != i && imgText[j].type == EFFECT_TEXT_EXP)
				//		imgText[j].y += 8 * _2X;
				//}
				break;
			case EFFECT_TEXT_CRITICAL:
			case EFFECT_TEXT_PIERCE:
			case EFFECT_TEXT_EXTRA:
			case EFFECT_TEXT_GUARD:
				if (obj < ENEMY) {
					if (textObj >= BULLET)
						textObj = ao[obj].target;
					//imgText[i].x = DX - 5;
					//imgText[i].y = DY / 2;
					
					switch (type) {
						case EFFECT_TEXT_CRITICAL:
							gap = 88 * _2X  / 2;
							break;
						case EFFECT_TEXT_PIERCE:
							gap = 56 * _2X / 2;
							break;
						case EFFECT_TEXT_EXTRA:
							gap = 51 * _2X / 2;
							break;
						case EFFECT_TEXT_GUARD:
							gap = 53 * _2X / 2;
							break;

					}
					//imgText[i].x = ao[textObj].x + gap;
					//imgText[i].y = ao[textObj].y + ao[textObj].cpy - 18 * _2X;

					//imgText[i].x = PLAYAREA_X / 2;

					//if (SCREENRATIO <= 150)
					//	imgText[i].y = 160 * _2X;
					//else
					//	imgText[i].y = DY - GNBHEIGHT - 160 * _2X;
					//imgText[i].y = DY / 2 + MINDY / 2 - 240 * _2X;
					imgText[i].x = ao[textObj].x + gap;
					imgText[i].y = STATUSWIN_Y + (rh - 4) * TSIZE - (ao[textObj].y - 120 * _2X) - ry;// - (ao[obj].y + ao[obj].cpy - 32 * _2X) - ry;// 56 * _2X;
					//imgText[i].y = STATUSWIN_Y + IMGTEXT_Y;// - (ao[obj].y + ao[obj].cpy - 32 * _2X) - ry;// 56 * _2X;


					//for (j = 0; j < TOTALHITMARK; j++) {
					//	if (j != i && imgText[j].type >= EFFECT_TEXT_CRITICAL/* && imgText[j].dmg < ENEMY*/)
					//		imgText[j].y += 8 * _2X;
					//}
					break;
				}
			case EFFECT_TEXT_MISS:
			case EFFECT_TEXT_EVASION:
			case EFFECT_TEXT_REGIST:
				imgText[i].x = ao[obj].x;
				//imgText[i].y = STATUSWIN_Y + (rh - 4) * TSIZE - (ao[obj].y - 88 * _2X) - ry;// - (ao[obj].y + ao[obj].cpy - 32 * _2X) - ry;// 56 * _2X;
				imgText[i].y = STATUSWIN_Y + IMGTEXT_Y;// - (ao[obj].y + ao[obj].cpy - 32 * _2X) - ry;// 56 * _2X;


				//imgText[i].x = PLAYAREA_X / 2;
				//imgText[i].y = STATUSWIN_Y + DRAWROULETTENUMGAP - EFFECTTEXT_Y;// 56 * _2X;

				//if (SCREENRATIO <= 150)
				//	imgText[i].y = 160 * _2X;
				//else
				//	imgText[i].y = DY - GNBHEIGHT - 160 * _2X;


				for (j = 0; j < TOTALHITMARK; j++) {
					if (j != i && imgText[j].type && imgText[j].type < EFFECT_TEXT_EXP && imgText[j].dmg == obj && imgText[j].pos == imgText[i].pos && imgText[j].frame < 5) {
						imgText[i].pos++;
						j = -1;
					}
				}

				//for (j = 0; j < TOTALHITMARK; j++) {
				//	if (j != i && imgText[j].type >= EFFECT_TEXT_CRITICAL/* && imgText[j].dmg < ENEMY*/)
				//		imgText[j].y += 8 * _2X;
				//}
				//imgText[i].x += imgTextPos[imgText[i].pos * 2];
				//imgText[i].y += imgTextPos[imgText[i].pos * 2 + 1];
				break;
			case EFFECT_TEXT_UP:
				break;
			}
			break;
		}
	}

	return i;
}

void SetHitMark(int x, int y, int dir, int type, int etc, int owner, float zoom)
{
	int i;

	//if (option.effect == false)
	//	return;

	//zoom = zoom / 2;

	for (i = 0; i < TOTALHITMARK; i++) {
		if (hitMark[i].frame == 0) {
			hitMark[i].x = x;
			hitMark[i].y = y;
			hitMark[i].dir = dir;
			hitMark[i].frame = 1;
			hitMark[i].type = type;
			hitMark[i].etc = etc;
			hitMark[i].owner = owner;
			hitMark[i].zoom = zoom;
			break;
		}
	}
}

//프레임미다 SetCurrencyMark를 호출하는 함수
void SetCurrencyMarkArr(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, long long amount, int type, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2, int iconMarkCnt, int bar)
{
	int i;

	for (i = 0; i < TOTALCURRENCYMARKARR; i++) {
		if (currencyMarkArr[i].frame == 0) {
			currencyMarkArr[i].x = startPosX/* + Random(moveAngle * _2X)*/;
			currencyMarkArr[i].y = startPosY/* + Random(moveAngle * _2X)*/;
			currencyMarkArr[i].targetX = targetX;
			currencyMarkArr[i].targetY = targetY;
			currencyMarkArr[i].targetX2 = targetX2;
			currencyMarkArr[i].targetY2 = targetY2;
			currencyMarkArr[i].speed = speed;
			currencyMarkArr[i].speedIncrement = speedIncrement;
			currencyMarkArr[i].speed2 = speed2;
			currencyMarkArr[i].speedIncrement2 = speedIncrement2;
			currencyMarkArr[i].waitingFrame = waitingFrame;
			currencyMarkArr[i].waitingFrame2 = waitingFrame2;
			currencyMarkArr[i].frame = 1;
			currencyMarkArr[i].imageDx = 16 * _2X;
			currencyMarkArr[i].imageDy = 16 * _2X;
			currencyMarkArr[i].imageOffX = (iconIdx & 0x07) * 16 * _2X;
			currencyMarkArr[i].imageOffY = ((iconIdx & 0x3F) >> 3) * 16 * _2X;
			currencyMarkArr[i].resNum = ITEM_IMG + (iconIdx >> 6);
			currencyMarkArr[i].moveAngle = moveAngle;
			currencyMarkArr[i].amount = amount;
			currencyMarkArr[i].type = type;
			currencyMarkArr[i].icon = iconIdx;
			currencyMarkArr[i].alpha = 0;
			currencyMarkArr[i].zoom = zoom;
			currencyMarkArr[i].zoomEnd = zoomEnd;
			currencyMarkArr[i].zoomIncrement = zoomIncrement;
			currencyMarkArr[i].zoom2 = zoom2;
			currencyMarkArr[i].zoomEnd2 = zoomEnd2;
			currencyMarkArr[i].zoomIncrement2 = zoomIncrement2;
			currencyMarkArr[i].iconMarkCnt = iconMarkCnt;
			currencyMarkArr[i].bar = bar;
			break;
		}
	}
}

//프레임미다 SetCurrencyMark를 호출하는 함수
void SetCurrencyMarkArr_PopUp(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, long long amount, int type, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2, int iconMarkCnt)
{
	int i;

	for (i = 0; i < TOTALCURRENCYMARKARR; i++) {
		if (currencyMarkArr_PopUp[i].frame == 0) {
			currencyMarkArr_PopUp[i].x = startPosX/* + Random(moveAngle * _2X)*/;
			currencyMarkArr_PopUp[i].y = startPosY/* + Random(moveAngle * _2X)*/;
			currencyMarkArr_PopUp[i].targetX = targetX;
			currencyMarkArr_PopUp[i].targetY = targetY;
			currencyMarkArr_PopUp[i].targetX2 = targetX2;
			currencyMarkArr_PopUp[i].targetY2 = targetY2;
			currencyMarkArr_PopUp[i].speed = speed;
			currencyMarkArr_PopUp[i].speedIncrement = speedIncrement;
			currencyMarkArr_PopUp[i].speed2 = speed2;
			currencyMarkArr_PopUp[i].speedIncrement2 = speedIncrement2;
			currencyMarkArr_PopUp[i].waitingFrame = waitingFrame;
			currencyMarkArr_PopUp[i].waitingFrame2 = waitingFrame2;
			currencyMarkArr_PopUp[i].frame = 1;
			currencyMarkArr_PopUp[i].imageDx = 16 * _2X;
			currencyMarkArr_PopUp[i].imageDy = 16 * _2X;
			currencyMarkArr_PopUp[i].imageOffX = (iconIdx & 0x07) * 16 * _2X;
			currencyMarkArr_PopUp[i].imageOffY = ((iconIdx & 0x3F) >> 3) * 16 * _2X;
			currencyMarkArr_PopUp[i].resNum = ITEM_IMG + (iconIdx >> 6);
			currencyMarkArr_PopUp[i].moveAngle = moveAngle;
			currencyMarkArr_PopUp[i].amount = amount;
			currencyMarkArr_PopUp[i].type = type;
			currencyMarkArr_PopUp[i].icon = iconIdx;
			currencyMarkArr_PopUp[i].alpha = 0;
			currencyMarkArr_PopUp[i].zoom = zoom;
			currencyMarkArr_PopUp[i].zoomEnd = zoomEnd;
			currencyMarkArr_PopUp[i].zoomIncrement = zoomIncrement;
			currencyMarkArr_PopUp[i].zoom2 = zoom2;
			currencyMarkArr_PopUp[i].zoomEnd2 = zoomEnd2;
			currencyMarkArr_PopUp[i].zoomIncrement2 = zoomIncrement2;
			currencyMarkArr_PopUp[i].iconMarkCnt = iconMarkCnt;
			break;
		}
	}
}

//커런시마크 중에 목적지에 도달한 케이스
int GetCurrencyMarkDoneCnt(void)
{
	int i;
	int cnt = 0;

	for (i = 0; i < TOTALCURRENCYMARK; i++) {
		//두번째 타겟팅 위치가 있는 경우
		if (currencyMark[i].targetX2 != 0 && currencyMark[i].targetY2 != 0) {
			if (currencyMark[i].x == currencyMark[i].targetX2 && currencyMark[i].y == currencyMark[i].targetY2) {
				cnt++;
			}
		}
		else if (currencyMark[i].x == currencyMark[i].targetX && currencyMark[i].y == currencyMark[i].targetY) {
			cnt++;
		}
	}

	return cnt;
}

void SetCurrencyMark(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, int amount, int type, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2, int bar)
{
	int i;

	for (i = 0; i < TOTALCURRENCYMARK; i++) {
		if (currencyMark[i].frame == 0) {
			currencyMark[i].x = startPosX/* + Random(moveAngle * _2X)*/;
			currencyMark[i].y = startPosY/* + Random(moveAngle * _2X)*/;
			currencyMark[i].targetX = targetX;
			currencyMark[i].targetY = targetY;
			currencyMark[i].targetX2 = targetX2;
			currencyMark[i].targetY2 = targetY2;
			currencyMark[i].speed = speed;
			currencyMark[i].speedIncrement = speedIncrement;
			currencyMark[i].speed2 = speed2;
			currencyMark[i].speedIncrement2 = speedIncrement2;
			currencyMark[i].waitingFrame = waitingFrame;
			currencyMark[i].waitingFrame2 = waitingFrame2;
			currencyMark[i].frame = 1;
			currencyMark[i].imageDx = 16 * _2X;
			currencyMark[i].imageDy = 16 * _2X;
			currencyMark[i].imageOffX = (iconIdx & 0x07) * 16 * _2X;
			currencyMark[i].imageOffY = ((iconIdx & 0x3F) >> 3) * 16 * _2X;
			currencyMark[i].resNum = ITEM_IMG + (iconIdx >> 6);
			currencyMark[i].moveAngle = moveAngle;
			currencyMark[i].amount = amount;
			currencyMark[i].type = type;
			currencyMark[i].icon = iconIdx;
			currencyMark[i].alpha = 0;
			currencyMark[i].zoom = zoom;
			currencyMark[i].zoomEnd = zoomEnd;
			currencyMark[i].zoomIncrement = zoomIncrement;
			currencyMark[i].zoom2 = zoom2;
			currencyMark[i].zoomEnd2 = zoomEnd2;
			currencyMark[i].zoomIncrement2 = zoomIncrement2;
			currencyMark[i].bar = bar;

			switch (iconIdx) {
			case ICON_GOLD:
				PlayMusic(M_COIN);
				break;
			case ICON_GOLDBAG:
				PlayMusic(M_COIN);
				break;
			case ICON_HEART:
				if (i == 0)
					PlayMusic(M_HEART);
				break;
			case ICON_HAMMER:
				PlayMusic(M_IRON);
				break;
			case ICON_SHIELD:
				PlayMusic(M_SWORDHIT);
				break;
			case ICON_HIT:
				PlayMusic(M_SWORDHIT);
				break;
			case ICON_RAID:
				PlayMusic(M_SWORDHIT);
				break;
			default:
				PlayMusic(M_BUTTON);
				break;
			}

			currencyMarkCnt++;
			break;
		}
	}
}

void SetCurrencyMark_PopUp(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, int amount, int type, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2)
{
	int i;

	for (i = 0; i < TOTALCURRENCYMARK; i++) {
		if (currencyMark_PopUp[i].frame == 0) {
			currencyMark_PopUp[i].x = startPosX/* + Random(moveAngle * _2X)*/;
			currencyMark_PopUp[i].y = startPosY/* + Random(moveAngle * _2X)*/;
			currencyMark_PopUp[i].targetX = targetX;
			currencyMark_PopUp[i].targetY = targetY;
			currencyMark_PopUp[i].targetX2 = targetX2;
			currencyMark_PopUp[i].targetY2 = targetY2;
			currencyMark_PopUp[i].speed = speed;
			currencyMark_PopUp[i].speedIncrement = speedIncrement;
			currencyMark_PopUp[i].speed2 = speed2;
			currencyMark_PopUp[i].speedIncrement2 = speedIncrement2;
			currencyMark_PopUp[i].waitingFrame = waitingFrame;
			currencyMark_PopUp[i].waitingFrame2 = waitingFrame2;
			currencyMark_PopUp[i].frame = 1;
			currencyMark_PopUp[i].imageDx = 16 * _2X;
			currencyMark_PopUp[i].imageDy = 16 * _2X;
			currencyMark_PopUp[i].imageOffX = (iconIdx & 0x07) * 16 * _2X;
			currencyMark_PopUp[i].imageOffY = ((iconIdx & 0x3F) >> 3) * 16 * _2X;
			currencyMark_PopUp[i].resNum = ITEM_IMG + (iconIdx >> 6);
			currencyMark_PopUp[i].moveAngle = moveAngle;
			currencyMark_PopUp[i].amount = amount;
			currencyMark_PopUp[i].type = type;
			currencyMark_PopUp[i].icon = iconIdx;
			currencyMark_PopUp[i].alpha = 0;
			currencyMark_PopUp[i].zoom = zoom;
			currencyMark_PopUp[i].zoomEnd = zoomEnd;
			currencyMark_PopUp[i].zoomIncrement = zoomIncrement;
			currencyMark_PopUp[i].zoom2 = zoom2;
			currencyMark_PopUp[i].zoomEnd2 = zoomEnd2;
			currencyMark_PopUp[i].zoomIncrement2 = zoomIncrement2;

			switch (iconIdx) {
			case ICON_GOLD:
				PlayMusic(M_COIN);
				break;
			case ICON_GOLDBAG:
				PlayMusic(M_COIN);
				break;
			case ICON_HEART:
				if (i == 0)
					PlayMusic(M_HEART);
				break;
			case ICON_HAMMER:
				PlayMusic(M_IRON);
				break;
			case ICON_SHIELD:
				PlayMusic(M_SWORDHIT);
				break;
			case ICON_HIT:
				PlayMusic(M_SWORDHIT);
				break;
			case ICON_RAID:
				PlayMusic(M_SWORDHIT);
				break;
			default:
				PlayMusic(M_BUTTON);
				break;
			}
			break;
		}
	}
}

void SetCurrencyMarkGold(int startPosX, int startPosY, int str)
{
	int i;
	int cnt = 0;
	int strArr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int pos = 0;
	int iconIdx = ICON_GOLD;
	int startX, startY, targetX, targetY, targetX2, targetY2, startSpeed;

	for (i = 0; i < TOTALCURRENCYMARK; i++) {
		if (currencyMark[i].frame == 0) {
			pos = i % 20;
			currencyMark[i].x = startPosX;
			currencyMark[i].y = startPosY;
			currencyMark[i].targetX = startPosX + coinScatterInfo[pos * COINSCATTERINFOSIZE + 0];
			currencyMark[i].targetY = startPosY + coinScatterInfo[pos * COINSCATTERINFOSIZE + 1];
			currencyMark[i].targetX2 = startPosX + coinScatterInfo[pos * COINSCATTERINFOSIZE + 2];
			currencyMark[i].targetY2 = startPosY + coinScatterInfo[pos * COINSCATTERINFOSIZE + 3];
			currencyMark[i].speed = coinScatterInfo[pos * COINSCATTERINFOSIZE + 4] / MOTIONDIV;
			currencyMark[i].speedIncrement = coinScatterInfo[pos * COINSCATTERINFOSIZE + 5] / MOTIONDIV;
			currencyMark[i].speed2 = coinScatterInfo[pos * COINSCATTERINFOSIZE + 6] / MOTIONDIV;
			currencyMark[i].speedIncrement2 = coinScatterInfo[pos * COINSCATTERINFOSIZE + 7] / MOTIONDIV;
			currencyMark[i].waitingFrame = coinScatterInfo[pos * COINSCATTERINFOSIZE + 8];
			currencyMark[i].waitingFrame2 = coinScatterInfo[pos * COINSCATTERINFOSIZE + 9];
			currencyMark[i].frame = 1;
			currencyMark[i].frame2 = 0;
			currencyMark[i].imageDx = 16 * _2X;
			currencyMark[i].imageDy = 16 * _2X;
			currencyMark[i].imageOffX = (iconIdx & 0x07) * 16 * _2X;
			currencyMark[i].imageOffY = ((iconIdx & 0x3F) >> 3) * 16 * _2X;
			currencyMark[i].resNum = ITEM_IMG + (iconIdx >> 6);
			currencyMark[i].moveAngle = 30;
			currencyMark[i].amount = 100;
			currencyMark[i].type = CURRENCY_GOLD;
			currencyMark[i].icon = iconIdx;
			currencyMark[i].alpha = 0;
			currencyMark[i].zoom = coinScatterInfo[pos * COINSCATTERINFOSIZE + 10];
			currencyMark[i].zoomEnd = coinScatterInfo[pos * COINSCATTERINFOSIZE + 11];
			currencyMark[i].zoomIncrement = coinScatterInfo[pos * COINSCATTERINFOSIZE + 12];
			currencyMark[i].zoom2 = coinScatterInfo[pos * COINSCATTERINFOSIZE + 13];
			currencyMark[i].zoomEnd2 = coinScatterInfo[pos * COINSCATTERINFOSIZE + 14];
			currencyMark[i].zoomIncrement2 = coinScatterInfo[pos * COINSCATTERINFOSIZE + 15];

			//cnt++;

			PlayMusic(M_COIN);

			//if (cnt == strArr[str])
			break;
		}
	}
}


void SetGoldAlphaMark(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, int amount, int type, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2)
{
	int i;

	for (i = 0; i < TOTALGOLDALPHAMARK; i++) {
		if (goldAlphaMark[i].frame == 0) {
			goldAlphaMark[i].x = startPosX/* + Random(moveAngle * _2X)*/;
			goldAlphaMark[i].y = startPosY/* + Random(moveAngle * _2X)*/;
			goldAlphaMark[i].targetX = targetX;
			goldAlphaMark[i].targetY = targetY;
			goldAlphaMark[i].targetX2 = targetX2;
			goldAlphaMark[i].targetY2 = targetY2;
			goldAlphaMark[i].speed = speed;
			goldAlphaMark[i].speedIncrement = speedIncrement;
			goldAlphaMark[i].speed2 = speed2;
			goldAlphaMark[i].speedIncrement2 = speedIncrement2;
			goldAlphaMark[i].waitingFrame = waitingFrame;
			goldAlphaMark[i].waitingFrame2 = waitingFrame2;
			goldAlphaMark[i].frame = 1;
			goldAlphaMark[i].imageDx = 16 * _2X;
			goldAlphaMark[i].imageDy = 16 * _2X;
			goldAlphaMark[i].imageOffX = (iconIdx & 0x07) * 16 * _2X;
			goldAlphaMark[i].imageOffY = ((iconIdx & 0x3F) >> 3) * 16 * _2X;
			goldAlphaMark[i].resNum = ITEM_IMG + (iconIdx >> 6);
			goldAlphaMark[i].moveAngle = moveAngle;
			goldAlphaMark[i].amount = amount;
			goldAlphaMark[i].type = type;
			goldAlphaMark[i].icon = iconIdx;
			goldAlphaMark[i].alpha = 0;
			goldAlphaMark[i].zoom = zoom;
			goldAlphaMark[i].zoomEnd = zoomEnd;
			goldAlphaMark[i].zoomIncrement = zoomIncrement;
			goldAlphaMark[i].zoom2 = zoom2;
			goldAlphaMark[i].zoomEnd2 = zoomEnd2;
			goldAlphaMark[i].zoomIncrement2 = zoomIncrement2;

			switch (goldAlphaMark[i].type) {
			case MISS:
				PlayMusic(M_ERROR);
				break;
			case GOOD:
				PlayMusic(M_DRUM_GOOD);
				break;
			case PERFECT:
				PlayMusic(M_DRUM_PERFECT);
				break;
			}

			return;
		}
	}
}

int SetSoulMark(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, int speed, int speedIncrement, int speed2, int speedIncrement2, int waitingFrame, int waitingFrame2, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2)
{
	soulMark.x = startPosX;
	soulMark.y = startPosY;
	soulMark.targetX = targetX;
	soulMark.targetY = targetY;
	soulMark.targetX2 = targetX2;
	soulMark.targetY2 = targetY2;
	soulMark.speed = speed;
	soulMark.speedIncrement = speedIncrement;
	soulMark.speed2 = speed2;
	soulMark.speedIncrement2 = speedIncrement2;
	soulMark.waitingFrame = waitingFrame;
	soulMark.waitingFrame2 = waitingFrame2;
	soulMark.frame = 1;
	soulMark.frame2 = 0;
	soulMark.zoom = zoom;
	soulMark.zoomEnd = zoomEnd;
	soulMark.zoomIncrement = zoomIncrement;
	soulMark.zoom2 = zoom2;
	soulMark.zoomEnd2 = zoomEnd2;
	soulMark.zoomIncrement2 = zoomIncrement2;

	PlayMusic(M_LASER);

	return true;
}

int SetItemMark(int startPosX, int startPosY, int targetX, int targetY, int startSpeed, int iconIdx, int moveAngle, int amount)
{
	int i;

	for (i = 0; i < TOTALITEMMARK; i++) {
		if (itemMark[i].frame == 0) {
			itemMark[i].x = startPosX;
			itemMark[i].y = startPosY;
			itemMark[i].targetX = targetX;
			itemMark[i].targetY = targetY;
			itemMark[i].speed = startSpeed;
			itemMark[i].frame = 1;
			itemMark[i].imageDx = 16 * _2X;
			itemMark[i].imageDy = 16 * _2X;
			itemMark[i].imageOffX = (iconIdx & 0x07) * 16 * _2X;
			itemMark[i].imageOffY = ((iconIdx & 0x3F) >> 3) * 16 * _2X;
			itemMark[i].resNum = ITEM_IMG + (iconIdx >> 6);
			itemMark[i].moveAngle = moveAngle;
			itemMark[i].amount = amount;
			itemMark[i].icon = iconIdx;
			itemMark[i].alpha = 0;

			switch (iconIdx) {
			case ICON_GOLD:
				PlayMusic(M_COIN);
				break;
			case ICON_GOLDBAG:
				PlayMusic(M_COIN);
				break;
			case ICON_HEART:
				PlayMusic(M_ITEM);
				break;
			case ICON_HAMMER:
				PlayMusic(M_IRON);
				break;
			case ICON_HIT:
				PlayMusic(M_SWORDHIT);
				break;
			case ICON_RAID:
				PlayMusic(M_SWORDHIT);
				break;
			default:
				PlayMusic(M_BUTTON);
				break;
			}
			return i;
		}
	}
}

int GetRewardMarkCnt(void)
{
	int i;
	int cnt = 0;
	for (i = 0; i < TOTALREWARDMARK; i++) {
		if (rewardMark[i].frame > 0)
			cnt++;
	}
	return cnt;
}

void InitEventPos(GAMEEVENT* gEvent, int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, int amount,
	float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2)
{

	gEvent->x = startPosX;
	gEvent->y = startPosY;
	gEvent->targetX = targetX;
	gEvent->targetY = targetY;
	gEvent->targetX2 = targetX2;
	gEvent->targetY2 = targetY2;
	gEvent->speed = speed;
	gEvent->speedIncrement = speedIncrement;
	gEvent->speed2 = speed2;
	gEvent->speedIncrement2 = speedIncrement2;
	gEvent->waitingFrame = waitingFrame;
	gEvent->waitingFrame2 = waitingFrame2;
	gEvent->zoom = zoom;
	gEvent->zoomEnd = zoomEnd;
	gEvent->zoomIncrement = zoomIncrement;
	gEvent->zoom2 = zoom2;
	gEvent->zoomEnd2 = zoomEnd2;
	gEvent->zoomIncrement2 = zoomIncrement2;
}


int SetRewardMark(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, int amount,
	int type, int detail, int grade, int cooldown, bool text, bool value, bool ani, int owner, bool star, bool cardFrame, bool newItem, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2)
{
	int i;

	if (type < ITEM_GEM) {
		cardFrame = true;
	}

	for (i = 0; i < TOTALREWARDMARK; i++) {
		if (rewardMark[i].frame == 0) {
			rewardMark[i].x = startPosX;
			rewardMark[i].y = startPosY;
			rewardMark[i].targetX = targetX;
			rewardMark[i].targetY = targetY;
			rewardMark[i].targetX2 = targetX2;
			rewardMark[i].targetY2 = targetY2;
			rewardMark[i].speed = speed;
			rewardMark[i].speedIncrement = speedIncrement;
			rewardMark[i].speed2 = speed2;
			rewardMark[i].speedIncrement2 = speedIncrement2;
			rewardMark[i].waitingFrame = waitingFrame;
			rewardMark[i].waitingFrame2 = waitingFrame2;
			rewardMark[i].frame = 1;
			rewardMark[i].imageDx = 16 * _2X;
			rewardMark[i].imageDy = 16 * _2X;
			rewardMark[i].imageOffX = (iconIdx & 0x07) * 16 * _2X;
			rewardMark[i].imageOffY = ((iconIdx & 0x3F) >> 3) * 16 * _2X;
			rewardMark[i].resNum = ITEM_IMG + (iconIdx >> 6);
			rewardMark[i].moveAngle = moveAngle;
			rewardMark[i].amount = amount;
			rewardMark[i].icon = iconIdx;

			rewardMark[i].type = type;
			rewardMark[i].detail = detail;
			rewardMark[i].grade = grade;
			rewardMark[i].zoom = zoom;
			rewardMark[i].zoomEnd = zoomEnd;
			rewardMark[i].zoomIncrement = zoomIncrement;
			rewardMark[i].zoom2 = zoom2;
			rewardMark[i].zoomEnd2 = zoomEnd2;
			rewardMark[i].zoomIncrement2 = zoomIncrement2;
			rewardMark[i].cooldown = cooldown;
			rewardMark[i].alpha = 0;
			rewardMark[i].text = text;
			rewardMark[i].value = value;
			rewardMark[i].ani = ani;
			rewardMark[i].owner = owner;
			rewardMark[i].star = star;

			rewardMark[i].cardFrame = cardFrame;
			rewardMark[i].newItem = newItem;

			PlayMusic(M_SELECT);

			return i;
		}
	}

}

void ArrangeControlMark(int start)
{
	int i, j = 0;
	if (start < actionCardCnt) {
		memcpy(&controlMark[start], &controlMark[start + 1], sizeof(ICONMARK) * (actionCardCnt - start));
		memcpy(&actionCardArr[start], &actionCardArr[start + 1], sizeof(actionCardArr[0]) * (actionCardCnt - start));
		memcpy(&controlerSpread[start], &controlerSpread[start + 1], sizeof(controlerSpread[0]) * (actionCardCnt - start));
		memset(&controlMark[actionCardCnt - 1], 0, sizeof(ICONMARK));
	}

	if (actionCardCnt > 0)
		actionCardCnt--;

	SaveGame();
}

int GetControlMark(int owner) {
	for (int i = 0; i < TOTALCONTROLMARK; i++) {
		if (controlMark[i].owner == owner) {
			return i;
		}
	}
}

int SetControlMark(
	int startPosX, int startPosY,
	int targetX, int targetY,
	int targetX2, int targetY2,
	float speed, float speedIncrement,
	float speed2, float speedIncrement2,
	int waitingFrame, int waitingFrame2,
	int iconIdx,
	int moveAngle, int amount,
	int attackType, int attackStr,
	float zoom, float zoomEnd, float zoomIncrement,
	float zoom2, float zoomEnd2, float zoomIncrement2,
	int alpha,
	bool text, bool value, bool ani,
	int owner,
	bool jokboIcon)
{
	int i;

	for (i = 0; i < TOTALCONTROLMARK; i++) {
		if (controlMark[i].frame == 0) {
			controlMark[i].x = startPosX;
			controlMark[i].y = startPosY;
			controlMark[i].targetX = targetX;
			controlMark[i].targetY = targetY;
			controlMark[i].targetX2 = targetX2;
			controlMark[i].targetY2 = targetY2;
			controlMark[i].speed = speed;
			controlMark[i].speedIncrement = speedIncrement;
			controlMark[i].speed2 = speed2;
			controlMark[i].speedIncrement2 = speedIncrement2;
			controlMark[i].waitingFrame = waitingFrame;
			controlMark[i].waitingFrame2 = waitingFrame2;
			controlMark[i].frame = 1;
			controlMark[i].imageDx = 16 * _2X;
			controlMark[i].imageDy = 16 * _2X;
			controlMark[i].imageOffX = (iconIdx & 0x07) * 16 * _2X;
			controlMark[i].imageOffY = ((iconIdx & 0x3F) >> 3) * 16 * _2X;
			controlMark[i].resNum = ITEM_IMG + (iconIdx >> 6);
			controlMark[i].moveAngle = moveAngle;
			controlMark[i].amount = amount;
			controlMark[i].icon = iconIdx;

			controlMark[i].attackType = attackType;
			controlMark[i].attackStr = attackStr;
			controlMark[i].zoom = zoom;
			controlMark[i].zoomEnd = zoomEnd;
			controlMark[i].zoomIncrement = zoomIncrement;
			controlMark[i].zoom2 = zoom2;
			controlMark[i].zoomEnd2 = zoomEnd2;
			controlMark[i].zoomIncrement2 = zoomIncrement2;
			controlMark[i].alpha = alpha;
			controlMark[i].text = text;
			controlMark[i].value = value;
			controlMark[i].ani = false; //controlMark[i].ani = ani;
			controlMark[i].owner = owner;
			controlMark[i].jokboIcon = jokboIcon;

			PlayMusic(M_CARDSPLIT);

			return i;
		}
	}
}

int GetCardMarkCnt(void)
{
	int i;
	int cnt = 0;
	for (i = 0; i < TOTALCARDMARK; i++) {
		if (cardMark[i].frame > 0)
			cnt++;
	}
	return cnt;

}

int SetCardMark(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, int amount,
	int attackType, int attackStr, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2, int alpha, bool text, bool value, bool ani, int owner, bool jokboIcon)
{
	int i;

	for (i = 0; i < TOTALCARDMARK; i++) {
		if (cardMark[i].frame == 0) {
			cardMark[i].x = startPosX;
			cardMark[i].y = startPosY;
			cardMark[i].targetX = targetX;
			cardMark[i].targetY = targetY;
			cardMark[i].targetX2 = targetX2;
			cardMark[i].targetY2 = targetY2;
			cardMark[i].speed = speed;
			cardMark[i].speedIncrement = speedIncrement;
			cardMark[i].speed2 = speed2;
			cardMark[i].speedIncrement2 = speedIncrement2;
			cardMark[i].waitingFrame = waitingFrame;
			cardMark[i].waitingFrame2 = waitingFrame2;
			cardMark[i].frame = 1;
			cardMark[i].imageDx = 16 * _2X;
			cardMark[i].imageDy = 16 * _2X;
			cardMark[i].imageOffX = (iconIdx & 0x07) * 16 * _2X;
			cardMark[i].imageOffY = ((iconIdx & 0x3F) >> 3) * 16 * _2X;
			cardMark[i].resNum = ITEM_IMG + (iconIdx >> 6);
			cardMark[i].moveAngle = moveAngle;
			cardMark[i].amount = amount;
			cardMark[i].icon = iconIdx;

			cardMark[i].attackType = attackType;
			cardMark[i].attackStr = attackStr;
			cardMark[i].zoom = zoom;
			cardMark[i].zoomEnd = zoomEnd;
			cardMark[i].zoomIncrement = zoomIncrement;
			cardMark[i].zoom2 = zoom2;
			cardMark[i].zoomEnd2 = zoomEnd2;
			cardMark[i].zoomIncrement2 = zoomIncrement2;
			cardMark[i].alpha = alpha;
			cardMark[i].text = text;
			cardMark[i].value = value;
			cardMark[i].ani = false; //cardMark[i].ani = ani;
			cardMark[i].owner = owner;
			cardMark[i].jokboIcon = jokboIcon;

			PlayMusic(M_CARDSPLIT);

			return i;
		}
	}
}

void SetBox(OBJECT* pObj, int etc)
{
	const signed short* sPtr;

	pObj->active = true;
	pObj->type = OBJ_BOX;
	pObj->x = BOXPOSITION_X;
	pObj->y = BOXPOSITION_Y;
	pObj->etc = etc;// bet;//BOX_INGAME;
	pObj->drawHandler = NEUTRALDRAW;
	pObj->cmf = -1;
	switch (pObj->etc) {
	case BOX_CASTLE0:
	case BOX_CASTLE1:
	case BOX_CASTLE2:
	case BOX_CASTLE3:
	case BOX_CASTLE4:
	case BOX_CASTLE5:
	case BOX_CASTLE6:
	case BOX_CASTLE7:
	case BOX_CASTLE8:
	case BOX_CASTLE9:
	case BOX_CASTLE10:
	case BOX_CASTLE11:
	case BOX_CASTLE12:
	case BOX_CASTLE13:
	case BOX_CASTLE14:
	case BOX_CASTLE15:
	case BOX_CASTLE16:
	case BOX_CASTLE17:
	case BOX_CASTLE18:
		pObj->zoom = BOXCASTLEZOOM * (1.0f + (float)0.05f * robin.castle);
		break;
	case BOX_REWARD0:
	case BOX_REWARD1:
	case BOX_REWARD2:
	case BOX_REWARD3:
	case BOX_REWARD4:
	case BOX_REWARD5:
	case BOX_REWARD6:
	case BOX_REWARD7:
		pObj->zoom = BOXCASTLEZOOM * (0.2f + (float)0.02f * (pObj->etc - BOX_REWARD0));
		break;
	default:
	//case BOX_INGAME:
		pObj->zoom = BOXZOOM;
		break;
	}

	sPtr = &neutralData[pObj->type * NEUTRALDATASIZE];

	pObj->block = *sPtr;

	pObj->attr = *(sPtr + 1);
	pObj->x += *(sPtr + 2);
	pObj->y += *(sPtr + 3);
	pObj->cpx = (float)*(sPtr + 4) * pObj->zoom;
	pObj->cpy = (float)*(sPtr + 5) * pObj->zoom;
	pObj->cx = (float)*(sPtr + 6) * pObj->zoom;
	pObj->cy = (float)*(sPtr + 7) * pObj->zoom;
	pObj->status = *(sPtr + 8);
	pObj->motion = *(sPtr + 9) & 0xFF;
	pObj->moveHandler = *(sPtr + 10);

	pObj->drawHandler = BOXDRAW;

	//pObj->etc = etc;

	pObj->nx = pObj->x;
	pObj->ny = pObj->y;

	//pObj->dx = pObj->dy = 0;

	pObj->status = BOXSTATUS_APPEAR;
	pObj->y += BOXPOSITION_INIT;

	PlayMusic(M_DOWN);

}

int SetBoxMark(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int moveAngle, int detail, int grade, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2)
{
	int i;

	for (i = 0; i < TOTALBOXMARK; i++) {
		if (boxMark[i].frame == 0) {
			boxMark[i].x = startPosX;
			boxMark[i].y = startPosY;
			boxMark[i].targetX = targetX;
			boxMark[i].targetY = targetY;
			boxMark[i].targetX2 = targetX2;
			boxMark[i].targetY2 = targetY2;
			boxMark[i].speed = speed;
			boxMark[i].speedIncrement = speedIncrement;
			boxMark[i].speed2 = speed2;
			boxMark[i].speedIncrement2 = speedIncrement2;
			boxMark[i].waitingFrame = waitingFrame;
			boxMark[i].waitingFrame2 = waitingFrame2;
			boxMark[i].frame = 1;
			boxMark[i].moveAngle = moveAngle;

			boxMark[i].type = ITEM_BOX;
			boxMark[i].detail = detail;
			boxMark[i].grade = grade;
			boxMark[i].zoom = zoom;
			boxMark[i].zoomEnd = zoomEnd;
			boxMark[i].zoomIncrement = zoomIncrement;
			boxMark[i].zoom2 = zoom2;
			boxMark[i].zoomEnd2 = zoomEnd2;
			boxMark[i].zoomIncrement2 = zoomIncrement2;
			boxMark[i].alpha = 0;
			boxMark[i].jokboIcon = false;
			PlayMusic(M_SELECT);

			return i;
		}
	}

}

int SetBoxCardMark(int startPosX, int startPosY, int targetX, int targetY, int targetX2, int targetY2, float speed, float speedIncrement, float speed2, float speedIncrement2, int waitingFrame, int waitingFrame2, int iconIdx, int moveAngle, int amount,
	int type, int detail, int grade, int cooldown, bool text, bool value, bool ani, int owner, bool star, bool cardFrame, bool newItem, float zoom, float zoomEnd, float zoomIncrement, float zoom2, float zoomEnd2, float zoomIncrement2)
{
	int i;

	if (type < ITEM_GEM || type == ITEM_CREW || type == ITEM_SKILL) {
		cardFrame = true;
	}

	for (i = 0; i < TOTALCARDMARK; i++) {
		if (boxCardMark[i].frame == 0) {
			boxCardMark[i].x = startPosX;
			boxCardMark[i].y = startPosY;
			boxCardMark[i].targetX = targetX;
			boxCardMark[i].targetY = targetY;
			boxCardMark[i].targetX2 = targetX2;
			boxCardMark[i].targetY2 = targetY2;
			boxCardMark[i].speed = speed;
			boxCardMark[i].speedIncrement = speedIncrement;
			boxCardMark[i].speed2 = speed2;
			boxCardMark[i].speedIncrement2 = speedIncrement2;
			boxCardMark[i].waitingFrame = waitingFrame;
			boxCardMark[i].waitingFrame2 = waitingFrame2;
			boxCardMark[i].frame = 1;
			boxCardMark[i].imageDx = 16 * _2X;
			boxCardMark[i].imageDy = 16 * _2X;
			boxCardMark[i].imageOffX = (iconIdx & 0x07) * 16 * _2X;
			boxCardMark[i].imageOffY = ((iconIdx & 0x3F) >> 3) * 16 * _2X;
			boxCardMark[i].resNum = ITEM_IMG + (iconIdx >> 6);
			boxCardMark[i].moveAngle = moveAngle;
			boxCardMark[i].amount = amount;
			boxCardMark[i].icon = iconIdx;

			boxCardMark[i].type = type;
			boxCardMark[i].detail = detail;
			boxCardMark[i].grade = grade;
			boxCardMark[i].zoom = zoom;
			boxCardMark[i].zoomEnd = zoomEnd;
			boxCardMark[i].zoomIncrement = zoomIncrement;
			boxCardMark[i].zoom2 = zoom2;
			boxCardMark[i].zoomEnd2 = zoomEnd2;
			boxCardMark[i].zoomIncrement2 = zoomIncrement2;
			boxCardMark[i].cooldown = cooldown;
			boxCardMark[i].alpha = 0;
			boxCardMark[i].text = text;
			boxCardMark[i].value = value;
			boxCardMark[i].ani = ani;
			boxCardMark[i].owner = owner;
			boxCardMark[i].star = star;

			boxCardMark[i].cardFrame = cardFrame;
			boxCardMark[i].newItem = newItem;

			PlayMusic(M_CARDSPLIT);

			return i;
		}
	}

}

//적에게 가장 가까운 유저
int NearPlayer(OBJECT* pObj)
{
	int i, j, distance, target = -1;

	distance = DX;
	for (i = PLAYER; i < TOTALCHAR; i++) {
		if (GetDistance(pObj, &ao[i]) < distance && ao[i].active == true && !ao[i].dead) {
			distance = GetDistance(pObj, &ao[i]);
			target = i;
		}
	}
	//target = PLAYER;

	if (target == -1)
		target = NEUTRAL;
	return target;
}

//아군에게 가장 가까운 적
int NearEnemy(OBJECT* pObj)
{
	int i, j, distance = DX, target = 0;

	for (i = ENEMY; i < NEUTRAL; i++) {
		if (GetDistance(pObj, &ao[i]) < distance && ao[i].active == true && ao[i].dead == false) {
			switch (ao[i].type) {
			case ENEMY_SHIP:
			case ENEMY_SHIP_RED:
			case ENEMY_SHIP_BLUE:
			case ENEMY_SHIP_PURPLE:
			case ENEMY_SHIP_GREEN:
			case ENEMY_SHIP_GOLD:
			case ENEMY_SHIP_BLACK:
				if (ao[i].moveHandler == SHIPMAINMOVE && !(ao[i].status == 0 && (ao[i].etc == SHIP_WEAK || ao[i].etc == SHIP_WEAKMOVE || ao[i].etc == SHIP_LASER || ao[i].etc == SHIP_GUIDESHOT))) {
					continue;
				}
				break;
			case ENEMY_CASTLE_BOSS1:
			case ENEMY_CASTLE_BOSS1_RED:
			case ENEMY_CASTLE_BOSS1_BLUE:
			case ENEMY_CASTLE_BOSS1_PURPLE:
			case ENEMY_CASTLE_BOSS1_GREEN:
			case ENEMY_CASTLE_BOSS1_GOLD:
			case ENEMY_CASTLE_BOSS1_BLACK:
				if (ao[i].moveHandler == DEBRIONBODYMOVE && ao[i].tileX2 > 0) {
					continue;
				}
				if (ao[i].moveHandler != DEBRIONBODYMOVE && ao[i].moveHandler != DEBRIONARMMOVE) {
					continue;
				}
				break;
			case ENEMY_CASTLE_BOSS3:
			case ENEMY_CASTLE_BOSS3_RED:
			case ENEMY_CASTLE_BOSS3_BLUE:
			case ENEMY_CASTLE_BOSS3_PURPLE:
			case ENEMY_CASTLE_BOSS3_GREEN:
			case ENEMY_CASTLE_BOSS3_GOLD:
			case ENEMY_CASTLE_BOSS3_BLACK:
				if (ao[i].moveHandler == ENEMYMOVE && ao[i].attack != 3)
					continue;
				if (ao[i].moveHandler != ENEMYMOVE && ao[i].moveHandler != FOLLOWMOMMOVE && ao[i].moveHandler != BUGMOVE)
					continue;
				break;
			default:
				if (i != ao[i].mom)
					continue;
				break;

			}
			distance = GetDistance(pObj, &ao[i]);
			target = i;
		}
	}

	return target;
}

int TargetPlayer(int obj)
{
	int i, j, distance = rw * TSIZE, tempDis;
	int range;

	switch (arenaStatus) {
	case STATUS_READY:

		break;
	case STATUS_PLAY:

		tempDis = 0;

		if (tempDis == 0) {

			// 나중에 스킬별로 사거리 늘어나는것 체크해서 적용시키면 됨
			range = GetAttackRange(obj);

			// 타겟인 적이 가까이 있다면, 그적을 계속 공격함
			if (ao[obj].target >= PLAYER && ao[obj].target < TOTALCHAR && ao[ao[obj].target].active && GetDistance(&ao[ao[obj].target], &ao[obj]) < range && ao[ao[obj].target].cx > 0)
				goto ACTION;

			//타겟이 없다면 타겟한테 이동
			//적이 나오면 먼저 죽이러 간다.
			for (i = PLAYER; i < TOTALCHAR; i++) {
				if (ao[i].active && ao[i].hp > 0) {
					switch (ao[i].moveHandler) {
						//바하무트의 몸통과 목은 제외
					case BAHAMUTNECKMOVE:
					case BAHAMUTBODYMOVE:
						break;
					default:
						tempDis = GetDistance(&ao[i], &ao[obj]);
						if (tempDis < distance) {
							ao[obj].target = i;
							distance = tempDis;
						}
						break;
					}
				}
			}

			// 캐릭터들이 어떤행동을 할지 결정
			if (range >= distance) {
			ACTION:
				if (!ao[obj].attack) {
					if (ao[obj].y - ao[ao[obj].target].y > TSIZE) {
						ao[obj].pressedKey[2] = ao[obj].pressedKey[1];
						ao[obj].pressedKey[1] = ao[obj].pressedKey[0];
						ao[obj].pressedKey[0] = ao[ao[obj].target].x > ao[obj].x ? AVK_1 : AVK_3;

						if (ao[obj].status == WALK) {
							//보통 점프
							ao[obj].jumpTwice = false;
							ao[obj].jumpFrame = 0;
							ao[obj].dirY = UP;
							ao[obj].my = true;
							ao[obj].status = JUMP;
							ao[obj].frame = 0;
						}
						else if (ao[obj].jumpTwice == false) {
							ao[obj].jumpTwice = true;
							ao[obj].jumpFrame = 0;
							ao[obj].dirY = UP;
							ao[obj].my = true;
							ao[obj].status = JUMP;
							ao[obj].frame = 0;
						}

					}
					else if ((ao[obj].status == WALK || (ao[obj].dirY == UP && ao[obj].jumpFrame > 2)) && (ao[obj].type != MAXX || boomerangAway[obj] == false)) {

						if (ao[obj].debuf[CURSE] || autoSkill == false)
							goto PRESSATTACK;
						else
							goto HOTKEYPRESS;

					HOTKEYPRESS:
						for (i = 0; i < TOTALCHARSKILL; i++) {
							if (ao[obj].hotKey[i].type == HOTKEY_SKILL && ao[obj].hotKey[i].frame == 0 && autoSkill == true) {
								HotKeyPress(&ao[obj], i);
								break;
							}
						}


					PRESSATTACK:
						if (!ao[obj].attack) {
							if (!(ao[obj].type == DIANA && ao[obj].flamer > 0)) {
								ao[obj].pressedKey[2] = ao[obj].pressedKey[1];
								ao[obj].pressedKey[1] = ao[obj].pressedKey[0];
								ao[obj].pressedKey[0] = AVK_5;
								ao[obj].turnPosition = THERE;
								GetMotionPtr(&ao[obj]);
								if (ao[obj].playerRun == true) {
									ao[obj].attack = ATTACK_DASH;
									ao[obj].attackFrame = skillStartFrame[ATTACK_DASH];
									HitCountCheck(&ao[obj]);
								}
								else if (ao[obj].status == WALK) {
									ao[obj].attack = ATTACK_NORMAL;
									ao[obj].attackFrame = skillStartFrame[ao[obj].attack];
									HitCountCheck(&ao[obj]);
									if (option.gameControl == CONTROL_MANUAL && ((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID) && obj == raidPlayer)) {
									}
									else
										ao[obj].dirX = ao[obj].dirF = ao[ao[obj].target].x > ao[obj].x ? RIGHT : LEFT;
								}
								else if (ao[obj].jumpTwice == true) {

									ao[obj].attack = ATTACK_AIR;
									ao[obj].attackFrame = skillStartFrame[ATTACK_AIR];
									HitCountCheck(&ao[obj]);
									if (option.gameControl == CONTROL_MANUAL && ((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID) && obj == raidPlayer)) {
									}
									else
										ao[obj].dirX = ao[obj].dirF = ao[ao[obj].target].x > ao[obj].x ? RIGHT : LEFT;
								}
								else {
									ao[obj].attack = ATTACK_AIR;
									ao[obj].attackFrame = skillStartFrame[ATTACK_AIR];
									HitCountCheck(&ao[obj]);
									if (option.gameControl == CONTROL_MANUAL && ((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID) && obj == raidPlayer)) {
									}
									else
										ao[obj].dirX = ao[obj].dirF = ao[ao[obj].target].x > ao[obj].x ? RIGHT : LEFT;
								}
							}
						}
						else if (ao[obj].attack == ATTACK_NORMAL) {

						}
					}
				}
				else if (ao[obj].attack == ATTACK_NORMAL) {

				}
			}
			else {
				if (!ao[obj].attack) {

					//일단 레인지 범위까지 이동하고
					if (Abs(ao[ao[obj].target].x - ao[obj].x) >= range) {
						{
							ao[obj].pressedKey[2] = ao[obj].pressedKey[1];
							ao[obj].pressedKey[1] = ao[obj].pressedKey[0];
							ao[obj].pressedKey[0] = ao[ao[obj].target].x > ao[obj].x ? AVK_6 : AVK_4;
							if (CanRunPlayer(obj))
								ao[obj].playerRun = true;
						}
					}
					//만약 범위 안인데 높이가 안맞으면 점프하고
					else if (ao[obj].y - ao[ao[obj].target].y > TSIZE) {
						ao[obj].pressedKey[2] = ao[obj].pressedKey[1];
						ao[obj].pressedKey[1] = ao[obj].pressedKey[0];
						ao[obj].pressedKey[0] = ao[ao[obj].target].x > ao[obj].x ? AVK_1 : AVK_3;

						if (ao[obj].status == WALK) {
							//보통 점프
							ao[obj].jumpTwice = false;
							ao[obj].jumpFrame = 0;
							ao[obj].dirY = UP;
							ao[obj].my = true;
							ao[obj].status = JUMP;
							ao[obj].frame = 0;
						}
						else if (ao[obj].jumpTwice == false) {
							ao[obj].jumpTwice = true;
							ao[obj].jumpFrame = 0;
							ao[obj].dirY = UP;
							ao[obj].my = true;
							ao[obj].status = JUMP;
							ao[obj].frame = 0;
						}
					}
				}
			}
		}
		else {
			ao[obj].pressedKey[2] = ao[obj].pressedKey[1];
			ao[obj].pressedKey[1] = ao[obj].pressedKey[0];
			ao[obj].pressedKey[0] = ao[ao[obj].target].x > ao[obj].x ? AVK_6 : AVK_4;

			if (CanRunPlayer(obj))
				ao[obj].playerRun = true;
		}
		break;
	case STATUS_ENEMYDEAD:
		break;
	case STATUS_BRIDGEOPEN:
		break;
	case STATUS_RAIDCLEAR:
		break;
	}

	return distance;
}

// ao[obj].target == PLAYER면 무조건 실행
int TargetEnemy(int obj)
{
	int i, j, distance = rw * TSIZE, tempDis;
	int range;
	int gameStartPosition = BATTLEPOSITION_PLAYER_X;
	OBJECT* pObj = &ao[obj];
	ITEM* it = &pObj->equip[EQUIP_WEAPON];
	int collectionIdx = GetCollectionIdx(it->type, it->detail, it->grade);

	if (drawHandle == MD_PLAY) {

	switch (arenaStatus) {
	case STATUS_READY:
		if (fadeFrame > 1 && ao[obj].x < gameStartPosition)
			ao[obj].pressedKey[0] = AVK_6;
		else {
			ao[obj].pressedKey[0] = ao[obj].pressedKey[1] = ao[obj].pressedKey[2] = null;
			ao[obj].dx = 0;
			ao[obj].turnPosition = HERE;

			turn = NEUTRAL;
			turnFrame = 0;
			turnPosition = HERE;

		}


		break;
	case STATUS_PLAY:
		if (turn < PLAYERALL && ao[obj].turnPosition == COMING && ao[SOLDIER].active == false) {
			if (ao[obj].x > ao[obj].nx) {
#ifdef WARIGARI
				ao[obj].pressedKey[2] = ao[obj].pressedKey[1];
				ao[obj].pressedKey[1] = ao[obj].pressedKey[0];
				ao[obj].pressedKey[0] = AVK_4;
				ao[obj].dirF = ao[obj].dirX = LEFT;

				return true;
#else
				if (autoPlay == false ||
					(ONLYATTACKMODE && (drawHandle == MD_PLAY && (MC_knlCurrentTimeStamp() - ao[ENEMY].coolTime >= enemyAttackPattern[ao[ENEMY].type * (3 + ATTACKPATTERNDATASIZE * 3) + 2])))
					) {
					ao[obj].pressedKey[2] = ao[obj].pressedKey[1];
					ao[obj].pressedKey[1] = ao[obj].pressedKey[0];
					ao[obj].pressedKey[0] = AVK_4;
					return true;
				}
				else if (autoPlay == true && attackSequence == ATTACKSEQUENCE_READY) {
					if (ONLYATTACKMODE)
						turn = NEUTRAL;
					else {
						if (drawHandle == MD_PLAY) {
							ao[PLAYER].dead = true;
							turn = GetAttackEnemy();
							PlayMusic(M_EVENT_SAD);
							attackSequence = ATTACKSEQUENCE_ATTACKRESULT;
							attackDelay = ENEMYDELAY_COIN_PLAYER_ATTACK - 1;
							autoPlay = false;
						}
						else if (drawHandle == MD_PLAY && enemyAttackPattern[ao[ENEMY].type * (3 + ATTACKPATTERNDATASIZE * 3) + 2] > 0 && MC_knlCurrentTimeStamp() - ao[ENEMY].coolTime >= enemyAttackPattern[ao[ENEMY].type * (3 + ATTACKPATTERNDATASIZE * 3) + 2] && robin.bossRoom == true) {
							turn = GetAttackEnemy();
							attackType = ROULETTE_COIN;
							attackSequence = ATTACKSEQUENCE_ROULETTE;
							sequenceFrame = 0;
							ao[ENEMY].coolTime = MC_knlCurrentTimeStamp();
						}
						else {
							turn = NEUTRAL;
						}
					}
					ao[obj].turn++;
					turnFrame = 0;
					turnPosition = HERE;
					PlayRelease(&ao[obj]);
					systemKey = ao[obj].pressedKey[2] = ao[obj].pressedKey[1] = ao[obj].pressedKey[0] = null;
					ao[obj].dx = ao[obj].dy = 0;
					ao[obj].dirF = ao[obj].dirX = RIGHT;

					switch (drawHandle) {
					case MD_PLAY:
						SaveGame();
						break;
					};
					if (autoPlay == true) {
						switch (keyHandle) {
						case MK_PLAY:
							if (ao[ENEMY].hp != 0)
								BoxOpen();
							break;
							//case MK_RAID:
							//	JoyStickPressRaid();
							//	break;
						}
					}
					else {
						autoPlay = false;
						option.gameControl = CONTROL_MANUAL;
					}
				}
#endif
			}
			//autoPlay
			else if (ao[obj].x <= ao[obj].nx && ao[SOLDIER].active == false) {
				/*
				ao[obj].x = ao[obj].nx;
				effect.color = effect.color2 = false;
				ao[obj].turn++;
				ao[obj].turnPosition = HERE;
				PlayRelease(&ao[obj]);
				systemKey = ao[obj].pressedKey[2] = ao[obj].pressedKey[1] = ao[obj].pressedKey[0] = null;
				ao[obj].dx = ao[obj].dy = 0;
				ao[obj].dirF = ao[obj].dirX = RIGHT;
#ifndef SPEEDTURN
				//if (obj == turn)
				//	WhoIsNextTurn();
#endif
				bar[BAR_COIN].add = bar[BAR_COIN].count = 0;

				//여기서 적을
				//for (i = ENEMY; i < NEUTRAL; i++) {
				//	if (ao[i].dead == false && ao[i].active == true)
				//		MoveObj(&ao[i]);
				//}

				if (turn >= ENEMY) {
					if (autoPlay == true) {
						switch (keyHandle) {
						case MK_PLAY:
							if (AliveEnemyCnt() == false && turn == NEUTRAL)
								BoxOpen();
							break;
							//case MK_RAID:
							//	JoyStickPressRaid();
							//	break;
						}
					}
					else {
						//autoPlay = false;
						option.gameControl = CONTROL_MANUAL;
					}

					//여기가 유저 액션이 끝나는 것
					//만약 레이드 중이면
					//레이드챈스가 다 소모되면 결과화면으로 넘어간다.
					if (keyHandle == MK_RAID && raidChance == 0) {
						attackSequence = ATTACKSEQUENCE_REWARD;
						sequenceDelay = ATTACKDELAY_RAIDREWARD_START + 2 * FPS / ROULETTEDIV;

					}
				}

				if (AliveEnemyCnt() == true) {
					//arenaStatus = STATUS_READY;
#ifdef PHASEFRAME
					phaseFrame = INFOFRAME;
#endif
				}

				return true;
				*/
			}
		}

		tempDis = 0;

		if (tempDis == 0) {

			// 나중에 스킬별로 사거리 늘어나는것 체크해서 적용시키면 됨
			range = GetAttackRange(obj);

			// 타겟인 적이 가까이 있다면, 그적을 계속 공격함
			if (ao[obj].target >= ENEMY && ao[ao[obj].target].active && GetDistance(&ao[ao[obj].target], &ao[obj]) < range && ao[ao[obj].target].cx > 0)
				goto ACTION;

			if (drawHandle == MD_RAID) {
				//distance = GetDistance(&ao[ao[obj].target], &ao[obj]) - (ao[ao[obj].target].cx / 5);
				distance = GetDistance(&ao[ao[obj].target], &ao[obj]);
			}
			else if (drawHandle == MD_BATTLE) {
				//	ao[obj].target = ENEMY;
				distance = GetDistance(&ao[ao[obj].target], &ao[obj]);
			}
			else {
				//타겟을 수동으로 지정하기 때문에 타겟을 별도로 지정하지 않는다.
				//화염방사기 같은 경우는 해당 쪽으로 이동한다.
				//타겟이 없다면 타겟한테 이동
				//적이 나오면 먼저 죽이러 간다.
				if (obj == DIANA && ao[obj].currentSkill == SKILL_DIANA8 && attackSequence == ATTACKSEQUENCE_ACTION)
					for (i = ENEMY; i < NEUTRAL; i++) {
						if (ao[i].active && ao[i].hp > 0) {
							switch (ao[i].moveHandler) {
								//바하무트의 몸통과 목은 제외
							case BAHAMUTNECKMOVE:
							case BAHAMUTBODYMOVE:
								break;
							default:
								//tempDis = GetDistance(&ao[i], &ao[obj]) - (ao[i].cx / 5);
								tempDis = GetDistance(&ao[i], &ao[obj]) - range;
								if (tempDis < distance) {
									ao[obj].target = i;
									distance = tempDis;
								}
								break;
							}
						}
					}
			}

			// 캐릭터들이 어떤행동을 할지 결정
			if (range >= distance) {
			ACTION:
				if (!ao[obj].attack) {

					if (ao[obj].y - ao[ao[obj].target].y > TSIZE * 3) {
						ao[obj].pressedKey[2] = ao[obj].pressedKey[1];
						ao[obj].pressedKey[1] = ao[obj].pressedKey[0];
						ao[obj].pressedKey[0] = ao[ao[obj].target].x > ao[obj].x ? AVK_1 : AVK_3;

						if (ao[obj].status == WALK) {
							//보통 점프
							ao[obj].jumpTwice = false;
							ao[obj].jumpFrame = 0;
							ao[obj].dirY = UP;
							ao[obj].my = true;
							ao[obj].status = JUMP;
							ao[obj].frame = 0;
						}
						else if (ao[obj].jumpTwice == false) {
							ao[obj].jumpTwice = true;
							ao[obj].jumpFrame = 0;
							ao[obj].dirY = UP;
							ao[obj].my = true;
							ao[obj].status = JUMP;
							ao[obj].frame = 0;
						}

					}
					else if ((ao[obj].status == WALK || (ao[obj].dirY == UP && ao[obj].jumpFrame > 2)) && (ao[obj].type != MAXX || boomerangAway[obj] == false)) {

						if (option.gameControl == CONTROL_MANUAL || option.gameControl == CONTROL_AUTO) {
							if (((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID) && obj != raidPlayer) || ((drawHandle == MD_PLAY || drawHandle == MD_RAID || drawHandle == MD_BATTLE || drawHandle == MD_BOSSRAID) && obj != raidPlayer))
								goto USERING;
							else
								goto PRESSATTACK;
						}
						else
							goto PRESSATTACK;
					USERING:
						if (ao[obj].equip[EQUIP_RING].type != EMPTY && (((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID) && (obj != raidPlayer || option.gameControl == CONTROL_AI)) || (keyHandle == MK_RAID && obj != raidPlayer)) && ao[obj].hotKey[RINGKEY].frame == 0) {
							//ao[obj].dirX = ao[obj].dirF = ao[ao[obj].target].x > ao[obj].x ? RIGHT : LEFT;

							switch (ao[obj].equip[EQUIP_RING].detail) {
							case ITEM_RING0:	//사신의 반지(28)
								if (ao[obj].debuf[CURSE])
									HotKeyPress(&ao[obj], RINGKEY);
								break;
							case ITEM_RING1:	//통찰의 반지(29)
								if (ao[obj].debuf[BLIND])
									HotKeyPress(&ao[obj], RINGKEY);
								break;
							case ITEM_RING2:	//시공의 반지(30)
								if (ao[obj].debuf[STUN])
									HotKeyPress(&ao[obj], RINGKEY);
								break;
							case ITEM_RING3:	//해방의 반지(31)
#ifdef RINGERASEALLDEBUF
								if (ao[obj].debuf[BLIND] || ao[obj].debuf[STUN] || ao[obj].debuf[SLOW] || ao[obj].debuf[POISON])
#else
								if (ao[obj].debuf[SLOW])
#endif
									HotKeyPress(&ao[obj], RINGKEY);
								break;
							case ITEM_RING4:	//산호석 반지(32)
								if (ao[obj].debuf[POISON])
									HotKeyPress(&ao[obj], RINGKEY);
								break;
							case ITEM_RING5:	//생환의 반지(33)
								//체력의 절반 이하이면
								if (ao[obj].hp < ao[obj].maxhp / 2)
									HotKeyPress(&ao[obj], RINGKEY);
								break;
							case ITEM_RING6:	//희생의 반지(34)
								HotKeyPress(&ao[obj], RINGKEY);
								break;
							case ITEM_RING7:	//폭주의 반지(35)
								HotKeyPress(&ao[obj], RINGKEY);
								break;
							case ITEM_RING8:	//골렘의 반지(36)
								HotKeyPress(&ao[obj], RINGKEY);
								break;
							case ITEM_RING9:	//광대의 반지(37)
								HotKeyPress(&ao[obj], RINGKEY);
								break;
							case ITEM_RING10:	//원한의 반지(38)
								HotKeyPress(&ao[obj], RINGKEY);
								break;
							case ITEM_RING11:	//신념의 반지(39)
								HotKeyPress(&ao[obj], RINGKEY);
								break;
							case ITEM_RING12:	//광포의 반지(40)
								HotKeyPress(&ao[obj], RINGKEY);
								break;
							case ITEM_RING13:	//승자의 반지(41)
								HotKeyPress(&ao[obj], RINGKEY);
								break;
							case ITEM_RING14:	//궁극의 반지(42)
								HotKeyPress(&ao[obj], RINGKEY);
								break;
							case ITEM_RING15:	//차원의 반지(43)
								HotKeyPress(&ao[obj], RINGKEY);
								break;
							case ITEM_RING16:	//영화의 반지(44)
								HotKeyPress(&ao[obj], RINGKEY);
								break;
							case ITEM_RING17:	//행운의 반지(45)
								HotKeyPress(&ao[obj], RINGKEY);
								break;
							}

						}

						if (option.gameControl == CONTROL_MANUAL || option.gameControl == CONTROL_AUTO) {
							if (((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID) && obj != raidPlayer)) {
								if (ao[obj].debuf[CURSE])
									goto PRESSATTACK;
								else
									goto HOTKEYPRESS;
							}
							else
								goto PRESSATTACK;
						}
						else
							goto HOTKEYPRESS;

					HOTKEYPRESS:
						for (i = 0; i < TOTALCHARSKILL; i++) {
							if ((((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID))) && ao[obj].hotKey[i].type == HOTKEY_SKILL && ao[obj].hotKey[i].frame == 0) {
								//ao[obj].dirX = ao[obj].dirF = ao[ao[obj].target].x > ao[obj].x ? RIGHT : LEFT;
								HotKeyPress(&ao[obj], i);
								break;
							}
						}


					PRESSATTACK:
						ao[obj].pressedKey[2] = ao[obj].pressedKey[1];
						ao[obj].pressedKey[1] = ao[obj].pressedKey[0];
						ao[obj].pressedKey[0] = null;
						ao[obj].dx = ao[obj].dy = 0;

					}
				}
				else if (ao[obj].attack == ATTACK_NORMAL) {
				}
			}
			else {
				if ((option.gameControl == CONTROL_MANUAL &&
					(((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID) && obj != raidPlayer)))
					|| ((option.gameControl == CONTROL_AUTO || option.gameControl == CONTROL_AI) && attackSequence == ATTACKSEQUENCE_SLOT)) {
					if (!ao[obj].attack) {

						//일단 레인지 범위까지 이동하고
						if (range <= distance) {
							{
								ao[obj].pressedKey[2] = ao[obj].pressedKey[1];
								ao[obj].pressedKey[1] = ao[obj].pressedKey[0];
								if (turn == obj)
									ao[obj].pressedKey[0] = AVK_6;
								else
									ao[obj].pressedKey[0] = null;
							}
						}
						//만약 범위 안인데 높이가 안맞으면 점프하고
						else if (ao[obj].y - ao[ao[obj].target].y > TSIZE) {
							ao[obj].pressedKey[2] = ao[obj].pressedKey[1];
							ao[obj].pressedKey[1] = ao[obj].pressedKey[0];
							ao[obj].pressedKey[0] = ao[ao[obj].target].x > ao[obj].x ? AVK_1 : AVK_3;

							if (ao[obj].status == WALK) {
								//보통 점프
								ao[obj].jumpTwice = false;
								ao[obj].jumpFrame = 0;
								ao[obj].dirY = UP;
								ao[obj].my = true;
								ao[obj].status = JUMP;
								ao[obj].frame = 0;
							}
							else if (ao[obj].jumpTwice == false) {
								ao[obj].jumpTwice = true;
								ao[obj].jumpFrame = 0;
								ao[obj].dirY = UP;
								ao[obj].my = true;
								ao[obj].status = JUMP;
								ao[obj].frame = 0;
							}
						}
					}

				}
			}
		}
		else if ((option.gameControl == CONTROL_MANUAL && !((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID) && obj == raidPlayer))
			|| (option.gameControl == CONTROL_AUTO || option.gameControl == CONTROL_AI)) {
			ao[obj].pressedKey[2] = ao[obj].pressedKey[1];
			ao[obj].pressedKey[1] = ao[obj].pressedKey[0];
			if (drawHandle == MD_PLAY || drawHandle == MD_BATTLE) {
				if (ao[ao[obj].target].x > ao[obj].x + range)
					ao[obj].pressedKey[0] = AVK_6;
				else
					ao[obj].pressedKey[0] = null;
			}
			else
				ao[obj].pressedKey[0] = AVK_6;
			//if (ao[ao[obj].target].x > ao[obj].x + range)
			//	ao[obj].pressedKey[0] = AVK_6;
			//else
			//	ao[obj].pressedKey[0] = AVK_4;

			if (CanRunPlayer(obj))
				ao[obj].playerRun = true;
		}
		break;
	case STATUS_ENEMYDEAD:
		//아이템을 획득하러 간다.
		tempDis = 0;
		for (i = ITEMOBJ; i < TOTALOBJECT; i++) {
			if (ao[i].active) {
				tempDis = GetDistance(&ao[i], &ao[obj]);
				if (tempDis < distance) {
					ao[obj].target = i;
					distance = tempDis;
				}
			}
		}

		if (tempDis == 0) {
			switch (drawHandle) {
			case MD_RAID:
				for (i = NEUTRAL; i < ITEMOBJ; i++) {
					//다리가 열리는 중이면 센터로 모은다.
					if (ao[i].moveHandler == BRIDGEMOVE && ao[i].status)
					{
						for (j = NEUTRAL; j < ITEMOBJ; j++) {
							if (ao[j].moveHandler == WARPMOVE) {
								ao[obj].target = j;
								ao[obj].pressedKey[0] = ao[ao[obj].target].x + ao[ao[obj].target].cx / 2 > ao[obj].x ? AVK_3 : AVK_1;
								ao[obj].flamer = null;
								if (skillInfoFrame > SKILLREMAINEDFRAME)
									skillInfoFrame = SKILLREMAINEDFRAME;
								if (skillUsed > SKILLREMAINEDFRAME)
									skillUsed = SKILLREMAINEDFRAME;
								if (buffItemFrame > BUFFITEMREMAINEDFRAME)
									buffItemFrame = BUFFITEMREMAINEDFRAME;
								return j;
							}
						}
					}
				}
				break;
			}
		}
		else {
			if (ao[obj].y - ao[ao[obj].target].y > TSIZE) {
				if (ao[obj].status == WALK) {
					ao[obj].pressedKey[0] = ao[ao[obj].target].x > ao[obj].x ? AVK_3 : AVK_1;
				}
				else {
					ao[obj].jumpTwice = true;
					ao[obj].jumpFrame = 0;
					ao[obj].dirY = UP;
					ao[obj].my = true;
					ao[obj].status = JUMP;
					ao[obj].frame = 0;
				}
			}
			else {
				if (ao[ao[obj].target].x > ao[obj].x)
					ao[obj].pressedKey[0] = AVK_6;
				else
					ao[obj].pressedKey[0] = AVK_4;
			}
		}
		break;
	case STATUS_BRIDGEOPEN:
		for (i = NEUTRAL; i < ITEMOBJ; i++) {
			//다리가 열리는 중이면 센터로 모은다.
			if (ao[i].moveHandler == BRIDGEMOVE && ao[i].status)
			{
				for (j = NEUTRAL; j < ITEMOBJ; j++) {
					if (ao[j].moveHandler == WARPMOVE) {
						ao[obj].target = j;
						ao[obj].pressedKey[0] = ao[ao[obj].target].x + ao[ao[obj].target].cx / 2 > ao[obj].x ? AVK_3 : AVK_1;
						ao[obj].flamer = null;
						ao[obj].attack = false;
#ifdef ONEHEARTONEATTACK
						ao[obj].turnPosition = COMING;
#ifndef WARIGARI
						if (autoPlay == true && drawHandle == MD_PLAY) {
							BoxOpen();

						}
#endif
#endif
						ao[obj].concentrate = 0;
						if (skillInfoFrame > SKILLREMAINEDFRAME)
							skillInfoFrame = SKILLREMAINEDFRAME;
						if (skillUsed > SKILLREMAINEDFRAME)
							skillUsed = SKILLREMAINEDFRAME;
						if (buffItemFrame > BUFFITEMREMAINEDFRAME)
							buffItemFrame = BUFFITEMREMAINEDFRAME;
						return j;
					}
				}
			}
		}

		if (fadeFrame == 0 && obj == raidPlayer) {
			for (i = ROBIN; i < TOTALPLAYER; i++) {
				memcpy(&ao[i], &ao[PLAYER + i], sizeof(OBJECT));
				ao[i].active = false;
			}
			SaveGame();
			switch (drawHandle) {
			case MD_PLAY:
			case MD_BATTLE:
				GotoNextStage();
				break;
			}
		}
		break;
	case STATUS_RAIDCLEAR:
		for (i = PLAYER; i < PLAYER + TOTALPLAYER; i++)
			ao[i].pressedKey[0] = AVK_6;
		break;
	}

	return distance;

}
else {
	switch (arenaStatus) {
	case STATUS_READY:


		break;
	case STATUS_PLAY:
		tempDis = 0;

		if (tempDis == 0) {
			// 나중에 스킬별로 사거리 늘어나는것 체크해서 적용시키면 됨
			range = GetAttackRange(obj);

			// 타겟인 적이 가까이 있다면, 그적을 계속 공격함
			if (ao[obj].target >= ENEMY && ao[ao[obj].target].active && GetDistance(&ao[ao[obj].target], &ao[obj]) < range && ao[ao[obj].target].cx > 0)
				goto ACTION2;

			for (i = ENEMY; i < NEUTRAL; i++) {
				if (ao[i].active && ao[i].hp > 0) {
					switch (ao[i].moveHandler) {
					case BAHAMUTNECKMOVE:
					case BAHAMUTBODYMOVE:
						break;
					default:
						if (ao[i].moveHandler == SHIPMAINMOVE && ao[i].status != 0)
							continue;
						//tempDis = GetDistance(&ao[i], &ao[obj]) - (ao[i].cx / 5);
						tempDis = GetDistance(&ao[i], &ao[obj]);
						if (tempDis < distance) {
							ao[obj].target = i;
							distance = tempDis;
						}
						break;
					}
				}
			}

			// 캐릭터들이 어떤행동을 할지 결정
			if (range >= distance) {
			ACTION2:
				if (!ao[obj].attack) {
					if (ao[obj].y - ao[ao[obj].target].y > TSIZE) {
						ao[obj].pressedKey[2] = ao[obj].pressedKey[1];
						ao[obj].pressedKey[1] = ao[obj].pressedKey[0];
						ao[obj].pressedKey[0] = AVK_2;// ao[ao[obj].target].x > ao[obj].x ? AVK_1 : AVK_3;

						if (ao[obj].status == WALK) {
							//보통 점프
							ao[obj].jumpTwice = false;
							ao[obj].jumpFrame = 0;
							ao[obj].dirY = UP;
							ao[obj].my = true;
							ao[obj].status = JUMP;
							ao[obj].frame = 0;
						}
						else if (ao[obj].jumpTwice == false) {
							ao[obj].jumpTwice = true;
							ao[obj].jumpFrame = 0;
							ao[obj].dirY = UP;
							ao[obj].my = true;
							ao[obj].status = JUMP;
							ao[obj].frame = 0;
						}

					}
					else
						if ((ao[obj].status == WALK || (ao[obj].dirY == UP && ao[obj].jumpFrame > 2)) && (ao[obj].type != MAXX || boomerangAway[obj] == false)) {

							//if (option.gameControl == CONTROL_MANUAL || option.gameControl == CONTROL_AUTO) {
							//	if (((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID) && obj != raidPlayer) || ((drawHandle == MD_PLAY || drawHandle == MD_RAID || drawHandle == MD_BATTLE || drawHandle == MD_BOSSRAID) && obj != raidPlayer))
							//		goto USERING;
							//	else
							//		goto PRESSATTACK;
							//}
							//else
							goto PRESSATTACK;
						USERING2:
							if (ao[obj].equip[EQUIP_RING].type != EMPTY && (((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID) && (obj != raidPlayer || option.gameControl == CONTROL_AI)) || (keyHandle == MK_RAID && obj != raidPlayer)) && ao[obj].hotKey[RINGKEY].frame == 0) {
								//ao[obj].dirX = ao[obj].dirF = ao[ao[obj].target].x > ao[obj].x ? RIGHT : LEFT;

								switch (ao[obj].equip[EQUIP_RING].detail) {
								case ITEM_RING0:	//사신의 반지(28)
									if (ao[obj].debuf[CURSE])
										HotKeyPress(&ao[obj], RINGKEY);
									break;
								case ITEM_RING1:	//통찰의 반지(29)
									if (ao[obj].debuf[BLIND])
										HotKeyPress(&ao[obj], RINGKEY);
									break;
								case ITEM_RING2:	//시공의 반지(30)
									if (ao[obj].debuf[STUN])
										HotKeyPress(&ao[obj], RINGKEY);
									break;
								case ITEM_RING3:	//해방의 반지(31)
#ifdef RINGERASEALLDEBUF
									if (ao[obj].debuf[BLIND] || ao[obj].debuf[STUN] || ao[obj].debuf[SLOW] || ao[obj].debuf[POISON])
#else
									if (ao[obj].debuf[SLOW])
#endif
										HotKeyPress(&ao[obj], RINGKEY);
									break;
								case ITEM_RING4:	//산호석 반지(32)
									if (ao[obj].debuf[POISON])
										HotKeyPress(&ao[obj], RINGKEY);
									break;
								case ITEM_RING5:	//생환의 반지(33)
									//체력의 절반 이하이면
									if (ao[obj].hp < ao[obj].maxhp / 2)
										HotKeyPress(&ao[obj], RINGKEY);
									break;
								case ITEM_RING6:	//희생의 반지(34)
									HotKeyPress(&ao[obj], RINGKEY);
									break;
								case ITEM_RING7:	//폭주의 반지(35)
									HotKeyPress(&ao[obj], RINGKEY);
									break;
								case ITEM_RING8:	//골렘의 반지(36)
									HotKeyPress(&ao[obj], RINGKEY);
									break;
								case ITEM_RING9:	//광대의 반지(37)
									HotKeyPress(&ao[obj], RINGKEY);
									break;
								case ITEM_RING10:	//원한의 반지(38)
									HotKeyPress(&ao[obj], RINGKEY);
									break;
								case ITEM_RING11:	//신념의 반지(39)
									HotKeyPress(&ao[obj], RINGKEY);
									break;
								case ITEM_RING12:	//광포의 반지(40)
									HotKeyPress(&ao[obj], RINGKEY);
									break;
								case ITEM_RING13:	//승자의 반지(41)
									HotKeyPress(&ao[obj], RINGKEY);
									break;
								case ITEM_RING14:	//궁극의 반지(42)
									HotKeyPress(&ao[obj], RINGKEY);
									break;
								case ITEM_RING15:	//차원의 반지(43)
									HotKeyPress(&ao[obj], RINGKEY);
									break;
								case ITEM_RING16:	//영화의 반지(44)
									HotKeyPress(&ao[obj], RINGKEY);
									break;
								case ITEM_RING17:	//행운의 반지(45)
									HotKeyPress(&ao[obj], RINGKEY);
									break;
								}

							}

							if (option.gameControl == CONTROL_MANUAL || option.gameControl == CONTROL_AUTO) {
								//if (((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID))) {
								//	if (ao[obj].debuf[CURSE])
								//		goto PRESSATTACK;
								//	else
								//		goto HOTKEYPRESS;
								//}
								//else
								if (ao[obj].currentSkill == -1 || IsMovingSkill(ao[obj].currentSkill) == false)
									goto HOTKEYPRESS;
								else
									goto PRESSATTACK2;
							}
							else
								goto HOTKEYPRESS2;

						HOTKEYPRESS2:
							//for (i = 0; i < TOTALCHARSKILL; i++) {
							//	if ((((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID))) && ao[obj].hotKey[i].type == HOTKEY_SKILL && ao[obj].hotKey[i].frame == 0 && autoSkill == true) {
							//		//ao[obj].dirX = ao[obj].dirF = ao[ao[obj].target].x > ao[obj].x ? RIGHT : LEFT;
							//		HotKeyPress(&ao[obj], i);
							//		break;
							//	}
							//}


						PRESSATTACK2:
							ao[obj].pressedKey[2] = ao[obj].pressedKey[1];
							ao[obj].pressedKey[1] = ao[obj].pressedKey[0];
							ao[obj].pressedKey[0] = AVK_5;
							ao[obj].attack = ATTACK_NORMAL;
							ao[obj].attackFrame = skillStartFrame[ATTACK_NORMAL];
							ao[obj].dx = ao[obj].dy = 0;

						}
				}
				else if (ao[obj].attack == ATTACK_NORMAL) {
				}
			}
			else {
				if ((option.gameControl == CONTROL_MANUAL &&
					(((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID) && obj != raidPlayer)))
					|| ((option.gameControl == CONTROL_AUTO || option.gameControl == CONTROL_AI))) {
					if (!ao[obj].attack) {

						//일단 레인지 범위까지 이동하고
						if (range <= distance) {
							{
								ao[obj].pressedKey[2] = ao[obj].pressedKey[1];
								ao[obj].pressedKey[1] = ao[obj].pressedKey[0];
								if (drawHandle == MD_PLAY) {
#ifdef DEFENSEGAME
									//앞으로 뛰어가는 경우는 거리가 짧은 스킬에 대해서만이다.
									if (IsMovingSkill(ao[obj].currentSkill) == true) {
										if (ao[ao[obj].target].x > ao[obj].x + range)
											ao[obj].pressedKey[0] = AVK_6;
										else
											ao[obj].pressedKey[0] = null;
									}
									else
										ao[obj].pressedKey[0] = null;

#else
									if (ao[ao[obj].target].x > ao[obj].x + range &&
										!(obj == PLAYER && (attackType == ROULETTE_BATTLE || attackType == ROULETTE_RAID || (attackType == ROULETTE_SKILL && (actionCardData[actionCardIdx * ACTIONCARDDATASIZE + 2] == PASSIVE || actionCardData[actionCardIdx * ACTIONCARDDATASIZE + 2] == SUMMON || actionCardIdx >= ACTIONCARD_SKILL_ROBIN_DEFENSE)))))
										ao[obj].pressedKey[0] = AVK_6;
									else
										ao[obj].pressedKey[0] = null;
#endif
								}
								else
									ao[obj].pressedKey[0] = AVK_6;
							}
						}
						//만약 범위 안인데 높이가 안맞으면 점프하고
						else if (ao[obj].y - ao[ao[obj].target].y > TSIZE) {
							ao[obj].pressedKey[2] = ao[obj].pressedKey[1];
							ao[obj].pressedKey[1] = ao[obj].pressedKey[0];
							ao[obj].pressedKey[0] = ao[ao[obj].target].x > ao[obj].x ? AVK_1 : AVK_3;

							if (ao[obj].status == WALK) {
								//보통 점프
								ao[obj].jumpTwice = false;
								ao[obj].jumpFrame = 0;
								ao[obj].dirY = UP;
								ao[obj].my = true;
								ao[obj].status = JUMP;
								ao[obj].frame = 0;
							}
							else if (ao[obj].jumpTwice == false) {
								ao[obj].jumpTwice = true;
								ao[obj].jumpFrame = 0;
								ao[obj].dirY = UP;
								ao[obj].my = true;
								ao[obj].status = JUMP;
								ao[obj].frame = 0;
							}
						}
					}

				}
			}
		}
		else if ((option.gameControl == CONTROL_MANUAL && !((keyHandle == MK_PLAY || keyHandle == MK_BATTLE || keyHandle == MK_RAID || keyHandle == MK_BOSSRAID) && obj == raidPlayer))
			|| (option.gameControl == CONTROL_AUTO || option.gameControl == CONTROL_AI)) {
			ao[obj].pressedKey[2] = ao[obj].pressedKey[1];
			ao[obj].pressedKey[1] = ao[obj].pressedKey[0];
			if (drawHandle == MD_PLAY) {
#ifdef DEFENSEGAME
				if (IsMovingSkill(ao[obj].currentSkill) == true) {
					if (ao[ao[obj].target].x > ao[obj].x + range)
						ao[obj].pressedKey[0] = AVK_6;
					else
						ao[obj].pressedKey[0] = null;
				}
				else
					ao[obj].pressedKey[0] = null;
#else
				if (ao[ao[obj].target].x > ao[obj].x + range)
					ao[obj].pressedKey[0] = AVK_6;
				else
					ao[obj].pressedKey[0] = null;
#endif
			}
			else
				ao[obj].pressedKey[0] = AVK_6;
			//if (ao[ao[obj].target].x > ao[obj].x + range)
			//	ao[obj].pressedKey[0] = AVK_6;
			//else
			//	ao[obj].pressedKey[0] = AVK_4;

			if (CanRunPlayer(obj))
				ao[obj].playerRun = true;
		}
		break;
	case STATUS_ENEMYDEAD:
		//아이템을 획득하러 간다.
		tempDis = 0;
		for (i = ITEMOBJ; i < TOTALOBJECT; i++) {
			if (ao[i].active) {
				tempDis = GetDistance(&ao[i], &ao[obj]);
				if (tempDis < distance) {
					ao[obj].target = i;
					distance = tempDis;
				}
			}
		}

		if (tempDis == 0) {
			switch (drawHandle) {
			case MD_RAID:
				for (i = NEUTRAL; i < ITEMOBJ; i++) {
					//다리가 열리는 중이면 센터로 모은다.
					if (ao[i].moveHandler == BRIDGEMOVE && ao[i].status)
					{
						for (j = NEUTRAL; j < ITEMOBJ; j++) {
							if (ao[j].moveHandler == WARPMOVE) {
								ao[obj].target = j;
								ao[obj].pressedKey[0] = ao[ao[obj].target].x + ao[ao[obj].target].cx / 2 > ao[obj].x ? AVK_3 : AVK_1;
								ao[obj].flamer = null;
								if (skillInfoFrame > SKILLREMAINEDFRAME)
									skillInfoFrame = SKILLREMAINEDFRAME;
								if (skillUsed > SKILLREMAINEDFRAME)
									skillUsed = SKILLREMAINEDFRAME;
								if (buffItemFrame > BUFFITEMREMAINEDFRAME)
									buffItemFrame = BUFFITEMREMAINEDFRAME;
								return j;
							}
						}
					}
				}
				break;
			}
		}
		else {
			if (ao[obj].y - ao[ao[obj].target].y > TSIZE) {
				if (ao[obj].status == WALK) {
					ao[obj].pressedKey[0] = ao[ao[obj].target].x > ao[obj].x ? AVK_3 : AVK_1;
				}
				else {
					ao[obj].jumpTwice = true;
					ao[obj].jumpFrame = 0;
					ao[obj].dirY = UP;
					ao[obj].my = true;
					ao[obj].status = JUMP;
					ao[obj].frame = 0;
				}
			}
			else {
#ifdef DEFENSEGAME
				if (IsMovingSkill(ao[obj].currentSkill) == true) {
					if (ao[ao[obj].target].x > ao[obj].x + range)
						ao[obj].pressedKey[0] = AVK_6;
					else
						ao[obj].pressedKey[0] = null;
				}
				else
					ao[obj].pressedKey[0] = null;
#else
				if (ao[ao[obj].target].x > ao[obscj].x)
					ao[obj].pressedKey[0] = AVK_6;
				else
					ao[obj].pressedKey[0] = AVK_4;
#endif
			}
		}
		break;
	case STATUS_BRIDGEOPEN:
		for (i = NEUTRAL; i < ITEMOBJ; i++) {
			//다리가 열리는 중이면 센터로 모은다.
			if (ao[i].moveHandler == BRIDGEMOVE && ao[i].status)
			{
				for (j = NEUTRAL; j < ITEMOBJ; j++) {
					if (ao[j].moveHandler == WARPMOVE) {
						ao[obj].target = j;
						ao[obj].pressedKey[0] = ao[ao[obj].target].x + ao[ao[obj].target].cx / 2 > ao[obj].x ? AVK_3 : AVK_1;
						ao[obj].flamer = null;
						ao[obj].attack = false;
#ifdef ONEHEARTONEATTACK
						ao[obj].turnPosition = COMING;
#ifndef WARIGARI
						if (autoPlay == true && drawHandle == MD_PLAY) {
							BoxOpen();

						}
#endif
#endif
						ao[obj].concentrate = 0;
						if (skillInfoFrame > SKILLREMAINEDFRAME)
							skillInfoFrame = SKILLREMAINEDFRAME;
						if (skillUsed > SKILLREMAINEDFRAME)
							skillUsed = SKILLREMAINEDFRAME;
						if (buffItemFrame > BUFFITEMREMAINEDFRAME)
							buffItemFrame = BUFFITEMREMAINEDFRAME;
						return j;
					}
				}
			}
		}

		if (fadeFrame == 0 && obj == raidPlayer) {
			for (i = ROBIN; i < TOTALPLAYER; i++) {
				memcpy(&ao[i], &ao[PLAYER + i], sizeof(OBJECT));
				ao[i].active = false;
			}
			SaveGame();
			switch (drawHandle) {
			case MD_PLAY:
				GotoNextStage();
				break;
			}
		}
		break;
	case STATUS_RAIDCLEAR:
		for (i = PLAYER; i < PLAYER + TOTALPLAYER; i++)
			ao[i].pressedKey[0] = AVK_6;
		break;
	}


	return distance;
	}

}

long long GetCombatPowerAll(int who)
{
	int i, j;
	long long value = 0;
	switch (who) {
	case PLAYER:
		//일단 주인공들
		for (i = ROBIN; i < PLAYERALL; i++) {
			for (j = 0; j < TOTALPLAYERSTAT; j++)
				value += ao[i].ps[i];
		}

		break;
	case ENEMY:
		break;
	}

	return value;
}

long long GetCombatPower(OBJECT* pObj)
{
	int i;
	long long value = 0;
	//전투력 계산식
	//Step 1
	//
	switch (pObj->type) {
	case ROBIN:
	case DIANA:
	case MAXX:
		for (i = 0; i < TOTALPLAYERSTAT; i++)
			value += pObj->ps[i];
		break;
	default:
		for (i = 0; i < TOTALPLAYERSTAT; i++)
			value += pObj->ps[i];
		break;
	}


	return value;
}