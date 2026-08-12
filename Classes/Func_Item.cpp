#include "Core.h"
#include "Data.h"
#include "Func.h"
#include "Text.h"

long long GetStageAdmissionFee(void)
{
	long long betGold;// = GetCharPrice(ROBIN);

	//robin.stage = 10;
	//robin.room = 4;

	//TEST
	betGold = (robin.stage * TOTALROOM + robin.room + 1) * stageGold[robin.stage * TOTALROOM + robin.room];

	return betGold;

	betGold = GetCharPrice(ROBIN);

	if (robin.heroesSetting[DIANA])
		betGold += GetCharPrice(DIANA);
	if (robin.heroesSetting[MAXX])
		betGold += GetCharPrice(MAXX);
	
	return betGold;
}

long long GetStageAdmissionHeart(int stage)
{
	long long betHeart;// = GetCharPrice(ROBIN);

	//TEST
	betHeart = 10 + stage;

	return betHeart;
}

ITEM* GetItemPtr(int idx)
{
	//포인터 -> 인덱스 규칙
	//0 ~ 120 : robin.inven
	//300 ~ 400 : a.shop
	//400 ~ 600 : robin.charData[pObj->type].equip
	//600 : tempItem
	//700 ~ 1000 : rankerDetail.costume
	//1000 ~ 1500 : rewardItem

	if (idx < ITEMPTR_SHOP)
		return &robin.inven[idx - ITEMPTR_INVEN];
	else if (idx < ITEMPTR_EQUIP)
		return &a.shop[idx - ITEMPTR_SHOP];
	else if (idx < ITEMPTR_TEMPITEM) {
		return &ao[(idx - ITEMPTR_EQUIP) / TOTALEQUIP].equip[(idx - ITEMPTR_EQUIP) % TOTALEQUIP];
	}
	else if (idx == ITEMPTR_TEMPITEM)
		return &tempItem;
	//else if (idx >= ITEMPTR_RANKERITEM && idx < ITEMPTR_RANKERITEM + 100)
	//	return &rankerDetail.costume[idx - ITEMPTR_RANKERITEM];
	else if (idx >= ITEMPTR_ARENAITEM && idx < ITEMPTR_ARENAITEM + MAXARENAITEM)
		return &rewardItem[idx - ITEMPTR_ARENAITEM];
	else if (idx >= ITEMPTR_HELPITEM && idx < ITEMPTR_HELPITEM + MAXHELPITEM)
		return &helpItem[idx - ITEMPTR_HELPITEM];
	else
		return 0;
}

//������Ʈ ���·� �������� ������Ų��
int DropItem(OBJECT* pObj, int type)
{
	int i, j, rand, dropSum;
	const unsigned char* uPtr;
	int tempHp = pObj->maxhp;

	PlayMusic(M_JUMP);//PlayMusic(M_JUMP);
	//��õ���� �������?�÷��̾ ���?��
	//1. ��õ������ �ش��ϴ� ����ġ
	//2. 2.5%(�뷫 100��)�� �����?18���� �������? 1.8���� ������, 0.18���� �������?
	//3. �� 225000�� ���?������ 150�� ���?
	//4. 1.4%(�뷫 70��)�� �������� 7���� ���޷�����, 7���� ��ͷ�����?
	//5. 650개의 소모성아이템
	//6. 140���� ������ 25���� ���޺���, 2.5���� ��ͺ���? 0.25���� ��������
	//7. 1150개의 재료들
	for (i = ITEMOBJ; i < TOTALOBJECT; i++) {
		OBJECT* pNew = &ao[i];

		if (pNew->active == false) {
			memset(pNew, 0, sizeof(OBJECT));
			pNew->active = true;
			pNew->zoom = DROPITEMZOOM;
			pNew->x = pNew->nx = pObj->x;
			pNew->y = pObj->y;// -(float)5 * _2X * pNew->zoom;
			pNew->ny = pObj->y;
			pNew->cx = (float)16 * _2X * pNew->zoom;
			pNew->cy = (float)16 * _2X * pNew->zoom;
			pNew->cpx = (float)-8 * _2X * pNew->zoom;
			pNew->cpy = (float)-16 * _2X * pNew->zoom;
			pNew->type = OBJ_ITEM;
			pNew->dirY = UP;
			pNew->status = JUMP;
			pNew->str = 1;
			pNew->moveHandler = ITEMMOVE;
			pNew->drawHandler = NEUTRALDRAW;
			pNew->def = type;	//type
			pNew->ax = 1;
			pNew->mom = 1;

			if (type == ITEM_BOX) {
				pNew->etc = SelectCastleRewardBox(
					robin.castle);
				pNew->drawHandler = BOXDRAW;
				pNew->zoom = 0.2f + 0.02f * (pNew->etc - BOX_REWARD0);
			}
			else {
				//����Ʈ�� || ������ || �Ź� �� �������� �ٷ� �Ʒ��� ����߸���?(�����ɸ�)
				if (robinmap == GACHAROOM) {
					//pNew->y = pObj->y;
					//pNew->jumpFrame = 0;
					pNew->y -= (float)64 * _2X * pNew->zoom;
					pNew->jumpFrame = 3;
					pNew->dx = (float)(-12 * _2X + Random(24) * _2X) * pNew->zoom;
				}
				else if (drawHandle == MD_DEMO) {
					if (type == ITEM_GOLD) {
						pNew->y -= (float)(64 * _2X) * pNew->zoom;
						pNew->jumpFrame = 3;
						pNew->dx = (float)(-12 * _2X + Random(24) * _2X) * pNew->zoom;
					}
				}
				else {
					pNew->y -= (float)(32 * _2X) * pNew->zoom;
					pNew->jumpFrame = 3;
					pNew->dx = (float)(-2 * _2X + Random(4 * _2X)) * pNew->zoom;
				}

				if (type >= 2000) {		//가챠
					rand = Random(10000);

					pNew->def = type - 2000;


					// ����ϰ�� ���� ���߱�
					int k, randSum = 0;

					for (k = 0; k < 8; k++) {
						if (rand < gachaRate[k]) {
							pNew->lv = (k + 1) * 10 + Random(10);
							break;
						}
					}

					if (drawHandle == MD_DEMO) {
						pNew->apx = itemArray[pObj->etc * 3 + 1];
						pNew->apy = itemArray[pObj->etc * 3 + 2];
					}
					else {
						//detail 결정
						if (pNew->def == ITEM_NECK || pNew->def == ITEM_RING)
							pNew->apx = MakeItemDetail(pNew->def, pNew->lv);
						else {
							for (k = 0; k < 8; k++) {
								if (rand < gachaRate[k]) {
									pNew->apx = k;
									//if (pNew->apx == GRADE_SET)
									//	pNew->apx--;
									break;
								}
							}
						}
						//type과 lv, detail로 grade 결정
						pNew->apy = MakeItemGrade(pNew->def, pNew->lv, pNew->apx);
					}
					//위의 결정사항을 통해 아이콘을 결정
					pNew->ay = GetItemIcon(pNew->def, pNew->apx, pNew->apy);
					//아이템 이름
					pNew->name = TEXT_ITEMNAME_START + GetItemName(pNew->def, pNew->apx, pNew->apy);

					//�� 4�� �̻��̸� ȭ���� ��������
				}
				else if (type >= 1000) {
					pNew->def = type - 1000;

					if (pNew->def == ITEM_GOLD) {
						pNew->apy = GRADE_NORMAL;
						//
						pNew->apx = RoundDiv(((4 + pObj->lv) * 2 + Random(pObj->lv + 1)) * (100 + pObj->ps[PS_GOLDMOD]), 40);
						pNew->name = -1;
						pNew->ay = ICON_GOLD;
					}
					else {
						if (pNew->def <= ITEM_GEM) {
							//���?���� ���?
							rand = Random(10000);
							//rand = 9999;
							caveItemGrade = false;

							if (rand <= caveItemPer[caveMap - 1][caveMapData * 4])
								pNew->apy = GRADE_NORMAL;
							else if (rand <= caveItemPer[caveMap - 1][caveMapData * 4 + 1])
								pNew->apy = GRADE_SUPERIOR;
							else if (rand <= caveItemPer[caveMap - 1][caveMapData * 4 + 2])
								pNew->apy = GRADE_RARE;
							else if (rand <= caveItemPer[caveMap - 1][caveMapData * 4 + 3]) {

								pNew->apy = GRADE_SET;

								caveItemGrade = true;
								caveItemText = caveItemType * 4;
							}
						}
						caveItemDetail = caveMap - 1;

						//detail 결정
						//장비
						if (pNew->def < ITEM_NECK) {

							pNew->lv = MakeItemLevel(pNew->def, pObj->lv) + (caveItemGrade == true && pNew->apy == GRADE_SET ? Random(20) : 0);
							pNew->apx = (caveItemGrade == true && pNew->apy == GRADE_SET ? caveMap - 1 + 4 : MakeItemDetail(pNew->def, pObj->lv));

						}
						else if (pNew->def == ITEM_RING || pNew->def == ITEM_NECK) {

							pNew->lv = MakeItemLevel(pNew->def, 30 + (pNew->apy == GRADE_SET ? 50 + Random(20) : Random(30)));
							if (pNew->apy != GRADE_SET)
								pNew->apx = MakeItemDetail(pNew->def, pObj->lv);
							else if (pNew->apy == GRADE_SET)
								pNew->apx = (Random(3) * 4) + caveItemDetail + (caveItemType == ITEM_RING ? 12 : 0);

						}
						else if (pNew->def == ITEM_GEM) {
							rand = Random(1000);
							if (rand < 200)
								pNew->apy = GRADE_NORMAL;
							else if (rand < 600)
								pNew->apy = GRADE_SUPERIOR;
							else if (rand < 900)
								pNew->apy = GRADE_RARE;
							else if (rand <= 1000)
								pNew->apy = GRADE_EPIC;

							caveItemGrade = false;

							pNew->apx = ITEM_GEM_RUBY + Random(6);
						}


						if ((pNew->def == ITEM_NECK || pNew->def == ITEM_RING) && pNew->apy == GRADE_SET) {
							pNew->ay = caveItemAcc[pNew->apx] + (caveItemType == ITEM_RING ? 28 : 0);
							pNew->name = TEXT_RA1_NECK + pNew->apx;
						}
						else {

							//위의 결정사항을 통해 아이콘을 결정
							pNew->ay = GetItemIcon(pNew->def, pNew->apx, pNew->apy);
							//아이템 이름
							pNew->name = TEXT_ITEMNAME_START + (caveItemGrade == true ? (pNew->def * 4) + TEXT_RA1_SWORD - TEXT_ITEMNAME_START + caveItemDetail : GetItemName(pNew->def, pNew->apx, pNew->apy));

						}

					}
				}
				// 투기장에서의 드랍템
				else if (type >= 300) {
					rand = Random(10000);

					pNew->def = type - 300;

					if (pNew->def == ITEM_GOLD) {
						pNew->apy = GRADE_NORMAL;
						pNew->apx = RoundDiv(((4 + pObj->lv) * 2 + Random(pObj->lv + 1)) * (100 + pObj->ps[PS_GOLDMOD]), 40);
						pNew->name = -1;
						pNew->ay = ICON_GOLD;
					}
					// �����ϰ��?���������
					else if (pNew->def == ITEM_GEM) {
						//보석의 등급
						//고급 : 80%
						//���?: 18% : 30���� �̻� ���� ���?
						//���� : 2% : 60���� �̻� ���� ���?
						pNew->apy = MakeItemGrade(pNew->def, pObj->lv, MakeItemDetail(pNew->def, pObj->lv));

						if (pNew->apy == GRADE_SET || pNew->apy == GRADE_LEGEND)
							pNew->apy--;
						pNew->apx = ITEM_GEM_RUBY + Random(6);
					}
					else if (pNew->def == ITEM_RING || pNew->def == ITEM_NECK) {
						pNew->lv = MakeItemLevel(pNew->def, pObj->lv);

						//detail 결정
						pNew->apx = MakeItemDetail(pNew->def, pObj->lv);
						//type과 lv, detail로 grade 결정
						pNew->apy = MakeItemGrade(pNew->def, pObj->lv, pNew->apx);
					}
					// ����ϰ�� ���� ���߱�
					else {
						int k, randSum = 0;
						pNew->lv = pObj->lv;

						if (pNew->apy == GRADE_LEGEND)
							pNew->apx = 6 + Random(2);
						else if (pNew->apy == GRADE_EPIC)
							pNew->apx = 3 + Random(4);
						else
							pNew->apx = MakeItemDetail(pNew->def, pNew->lv);
					}

					pNew->apx = MakeItemDetail(pNew->def, pNew->lv);
					pNew->apy = MakeItemGrade(pNew->def, pNew->lv, pNew->apx);
				}

				pNew->ay = GetItemIcon(pNew->def, pNew->apx, pNew->apy);
				pNew->name = TEXT_ITEMNAME_START + GetItemName(pNew->def, pNew->apx, pNew->apy);
			}
			return i;
		}
	}

	switch (type) {
	case ITEM_GOLD:
		PlayMusic(M_COIN);
		break;
	}

	return -1;
}

void MakeBoxDropPercent(void)
{
	int i, j;

	for (i = 0; i < TOTAL_BOX; i++) {
		for (j = 0; j < TOTAL_BOXDROP; j++) {
			boxDropPercent[i][j] = (j == 0 ? (float)boxDropProc[i][j] / 100 : (float)(boxDropProc[i][j] - boxDropProc[i][j - 1]) / 100);
		}
	}
}

void MakeItem(ITEM* it, int type, int lv, int grade, int detail, int set)
{
	int i, j, prefix, suffix, t = 0, optionGrade[6];
	char gr[3];
	char pr[100];
	char su[100];
	char name[100];
	int originVal;

	int name_idx1 = -1, name_idx2 = -1;

	//초기화
	memset(it, 0, sizeof(ITEM));

	for (i = 0; i < 12; i++)
		it->option[i][0] = EMPTYINT;

	for (i = 0; i < 6; i++)
		it->socket[i] = EMPTYINT;

	switch (type) {
		//default:
		//    break;
	case ITEM_NECK:
	case ITEM_RING:
		if (grade == GRADE_LEGEND)
			grade = GRADE_EPIC;

		if (grade == GRADE_SET)
			grade = GRADE_RARE;

		break;
	case ITEM_GEM:
		if (grade == GRADE_LEGEND)
			grade = GRADE_EPIC;

		else if (grade == GRADE_SET)
			grade = GRADE_RARE;

		else if (grade == GRADE_NORMAL)
			grade = GRADE_SUPERIOR;
		break;
	}

	//등급은 무조건 0으로 고정한다.
	//위 switch가 타입별로 등급을 올려주는 경우(ITEM_GEM의 GRADE_NORMAL -> GRADE_SUPERIOR)가
	//있어서 함수 첫머리가 아니라 그 뒤에서 덮어써야 결과가 확실히 0이 된다.
	//아래 값/옵션 계산도 이 지역변수를 보므로 여기서 한 번만 바꿔주면 전부 따라간다.
	grade = 0;

	it->type = type;
	it->lv = lv;
	it->detail = detail;
	it->grade = grade;

#ifdef SOCKET
	it->count = 1;
#else
	it->count = 0;
#endif
	it->cooldown = Proc(proc10, Min(10, lv / 10 + 1));
	it->exp = 0;

	//it->materialExp = itemExp[itemLevelLimit[2 * it->detail + 1]];//장비 별개수의 초기 업그레이드에 드는 값으로 수정해 준다.

	//�����?���?
	switch (type) {
	default:
		if (caveMap) {
			switch (it->type) {
			case ITEM_NECK:
			case ITEM_RING:

				it->value = MakeItemValue(type, (it->grade == GRADE_SET ? caveItemAcc[it->detail] : it->detail), grade, lv);

				break;
			default:
				it->value = MakeItemValue(type, 7, grade, lv);

				if (grade == GRADE_SET) {
					if (it->type < ITEM_HELM) //무기
						it->value += UpDiv(it->value, 4) + Random(30);
					//else //장비
					//	it->value += UpDiv(it->value, 10) + Random(30);
				}

				break;
			}
		}
		else
			it->value = MakeItemValue(type, detail, grade, lv);

		if (grade == GRADE_LEGEND) {

			int what = type * 2 + detail - 6;

			it->count = Proc(proc6, Min(6, lv / 10 + 1));
			it->value += UpDiv(it->value, 7);

			for (i = 0; i < 6; i++) {
				it->option[i][0] = legendItem[what * LEGENDITEMDATASIZE + i * 3];
				it->option[i][1] = legendItem[what * LEGENDITEMDATASIZE + i * 3 + 1] + Random(legendItem[what * LEGENDITEMDATASIZE + i * 3 + 2] + 1);
			}
		}
		else {
			//�ӽ�����ҿ�?���������?�������� ��ȭ/�ɼǻ������� ���� �ʴ´�.
#ifdef DEBUG
			if (idx == ITEMPTR_TEMPITEM && drawHandle != MD_SIMUL) {
				j = 0;
				break;
			}
#else
			if (it == &tempItem) {
				j = 0;
				break;
			}
#endif

			//기본값 결정

			it->value += Random(UpDiv(it->value * 20, 100) + 1);
			it->subValue += Random(UpDiv(it->value * 20, 100) + 1);

			if (type == ITEM_RING && it->detail < 5)
				it->value = Min(100, it->value);

			//소켓 생성
			switch (grade) {
			case GRADE_RARE:
			case GRADE_SET:
				//최대 4개의 소켓까지 생성
				it->count = Proc(proc4, Min(4, lv / 15 + 1));
				break;
			case GRADE_EPIC:
				//최대 5개의 소켓까지 생성
				it->count = Proc(proc5, Min(5, lv / 12 + 1));
				break;
			case GRADE_LEGEND:
			case GRADE_NORMAL:
			case GRADE_SUPERIOR:
				//최대 6개의 소켓까지 생성
				it->count = Proc(proc6, Min(6, lv / 10 + 1));
				break;
			}

			//강화레벨
			if (grade < GRADE_RARE && caveItemGrade == false)
				it->cooldown = Proc(proc10, Min(10, lv / 10 + 1));

			//�ɼ� ���� ����
			switch (grade) {
			default:
				//case GRADE_NORMAL:
					//�Ϲ� �������� ���� ������ �ɼǻ����� ���� �ʴ´�.
				j = 0;
				break;
			case GRADE_SUPERIOR:

				//1~2���� �ɼ��� ������ Ȯ���� ����
				j = Random(2) + 1;
				break;
			case GRADE_RARE:
				//3~5���� �ɼ��� ������ Ȯ���� ����
				j = Random(4) + 2;
				break;
			case GRADE_SET:
				//세트번호 입력
				if (set == 0) {
					j = Random(2);
					if (caveMap == 0)
						it->set = j * 100 + setItem[((itemStartCnt[type] + detail) * 2 + j) * 3];
					else {
						switch (it->type) {
						default:
							it->set = j * 100 + extraSetItem[((type * 4 + caveItemDetail) * 2 + j) * 3];
							break;
						case ITEM_NECK:
							it->set = j * 100 + extraSetItem[((type * 4 + caveItemDetail) * 2 + j) * 3 + ((it->detail - caveItemDetail) * 6)];
							break;
						case ITEM_RING:
							it->set = j * 100 + extraSetItem[(((type + 2) * 4 + caveItemDetail) * 2 + j) * 3 + ((it->detail - 12 - caveItemDetail) * 6)];
							break;
						}
					}
				}
				else
					it->set = set - 1;

				//2~4���� �ɼ��� ������ Ȯ���� ����

				j = Random((caveMap == 0 ? 3 : 5)) + 2;
				break;
			case GRADE_EPIC:
				//5~6���� �ɼ��� ����
				j = Random(2) + 5;
				break;
			}

		PREFIXSUFFIX:

			prefix = Random(2) * (j % 2) + j / 2;
			suffix = j - prefix;

			for (i = 0; i < prefix + suffix; i++) {
				//���� �ɼ��� ������ ����
				if (grade == GRADE_SET && i < 2) {
					//if (robinmap >= CAVE_A_1 && it->grade == GRADE_SET)
					//	t = extraSetItem[((type * 4 + caveItemDetail) * 2 + it->set / 100) * 3 + 1 + i + (it->type == ITEM_RING ? 72 : 0)];
					//else
					t = setItem[((itemStartCnt[type] + detail) * 2 + it->set / 100) * 3 + 1 + i];
				}
				else {
					if (i < prefix)
						//접두사
						t = option_prefix[itemEquipSlot[type] * 16 + Random(option_count_prefix[itemEquipSlot[type]])];
					else
						//접미사
						t = option_suffix[itemEquipSlot[type] * 16 + Random(option_count_suffix[itemEquipSlot[type]])];
				}
				//���� �ɼ��� ���� ���±��� ���� �ɼ��� ���?
				for (j = 0; j < i; j++) {
					if (it->option[j][0] == t || (t == SUFFIX_REQUIRE && it->grade == GRADE_SET) ||
						((t >= PREFIX_SWORD_DMG && t <= PREFIX_BOOMERANG_DMG) && (it->option[j][0] >= PREFIX_SWORD_DMG && it->option[j][0] <= PREFIX_BOOMERANG_DMG)) ||
						((t >= SUFFIX_SWORD_DMG && t <= SUFFIX_BOOMERANG_DMG) && (it->option[j][0] >= SUFFIX_SWORD_DMG && it->option[j][0] <= SUFFIX_BOOMERANG_DMG)) ||
						((t >= SUFFIX_FIRE_ATTACK && t <= SUFFIX_DARK_ATTACK) && (it->option[j][0] >= SUFFIX_FIRE_ATTACK && it->option[j][0] <= SUFFIX_DARK_ATTACK))) {
						i--;
						goto END;
					}
				}

				it->option[i][0] = t;

				//���� �ɼ��� �����?����
				switch ((lv - 1) / 10) {
				case 0:
					//1~10 : 하급만
					optionGrade[i] = 0;
					break;
				case 1:
				case 2:
				case 3:
				case 4:
					//50레벨 이하의 아이템은 하급 또는 중급
					optionGrade[i] = Random(40) < (lv - 11) / 10 ? 1 : 0;
					break;
				case 5:
				case 6:
				case 7:
				case 8:
					if (grade == GRADE_RARE)
						//�����?���� ������ �߱޿ɼ�
						optionGrade[i] = 1;
					else
						//중급 또는 상급
						optionGrade[i] = Random(40) < (lv - 51) / 10 ? 2 : 1;
					break;
				default:
					//case 9:
					//case 10:
					//case 11:
					//case 12:
					//case 13:
					//case 14:
					//case 15:
					if (grade == GRADE_RARE)
						//�����?���� ������ �߱޿ɼ�
						optionGrade[i] = 1;
					else
						//레벨 91 이상의 아이템은 무조건 상급
						optionGrade[i] = 2;
					break;
				}

				if (grade == GRADE_SUPERIOR)
					optionGrade[i] = (Random(lv + 50) >= 100 ? 1 : 0);

				if (optionRange[it->option[i][0] * 6 + optionGrade[i] * 2]) {
					//�ɼǰ��� ������ ���Ѵ�.
					it->option[i][1] = optionRange[it->option[i][0] * 6 + optionGrade[i] * 2] + Random(optionRange[it->option[i][0] * 6 + optionGrade[i] * 2 + 1] + 1);
					if (lv > 99)
						it->option[i][1] = Min(250, RoundDiv(it->option[i][1] * (10 + (lv - 90) / 10), 10));
				}
				else {
					//�ɼǰ��� 0�̸� ���� �޸��� ���� �ɼ��̴� �ٽ� ������ ������.
					i--;

					goto END;
				}

				//�迭���� ����Ǿ�� �ϴ� �ɼ��� ���?���� ���������� ���߾ �ɼ��� ����
				switch (it->option[i][0]) {
				case PREFIX_SWORD_DMG:
				case SUFFIX_SWORD_DMG:
					if (type == ITEM_GUN)
						it->option[i][0]++;
					else if (type == ITEM_BOOMERANG)
						it->option[i][0] += 2;
					break;
				case SUFFIX_FIRE_ATTACK:
					it->option[i][0] += Random(5);
					break;
				}

			END:;
			}

			//������ �ɼ��߿� �̸����� �� �ɼ��� ���Ѵ�.


			if (grade < GRADE_SET && grade) {
				if (grade == GRADE_SUPERIOR)
					name_idx1 = Random(prefix + suffix);
				else {
					name_idx1 = Random(prefix);
					name_idx2 = Random(suffix) + prefix;
				}
				if (name_idx1 >= 0) {
					memset(pr, 0, 100);
					t = TEXT_OPTION_PREFIX + it->option[name_idx1][0] * 3 + optionGrade[name_idx1];
					sprintf(pr, "%s", TEXTPTR(t));
				}

				if (name_idx2 >= 0) {
					memset(su, 0, 100);
					t = TEXT_OPTION_PREFIX + it->option[name_idx2][0] * 3 + optionGrade[name_idx2];
					sprintf(su, "%s", TEXTPTR(t));
				}
			}
			else if (grade == GRADE_SET) {
				memset(pr, 0, 100);
				name_idx1 = TEXT_SETNAME_START + (it->set % 100);
				//sprintf(pr, "|q%s:", TEXTPTR(name_idx1));
				sprintf(pr, "|r%s:", TEXTPTR(name_idx1));

				if (caveMap == 0) {
					it->option[prefix + suffix][0] = SUFFIX_REQUIRE;
					it->option[prefix + suffix][1] = 10;
				}
			}
		}
		break;
	case ITEM_GEM:			//보석

		if (grade == GRADE_SET)
			grade = GRADE_RARE;

		if (set)
			t = set - 1;
		else {
			switch (grade) {
			case GRADE_NORMAL:
				t = Random(4);
				break;
			case GRADE_SUPERIOR:
				t = Random(5);
				break;
			case GRADE_RARE:
			case GRADE_EPIC:
				t = Random(TOTALGEMOPTION);
				break;
			}
		}

		t *= 3;

		switch (grade) {
		case GRADE_NORMAL:
			it->option[0][0] = gemOption[t];
			it->option[0][1] = 2;
			break;
		case GRADE_SUPERIOR:
			it->option[0][0] = gemOption[t];
			it->option[0][1] = (it->option[0][0] == SUFFIX_STAT ? 1 : 3);
			break;
		case GRADE_RARE:
		case GRADE_EPIC:
			it->option[0][0] = gemOption[t];
			it->option[0][1] = gemOption[t + (grade == GRADE_RARE ? 1 : 2)];
			break;
		}
		break;
	case ITEM_WASTE:
	case ITEM_IRON:
	case ITEM_LEATHER:
	case ITEM_CLOTH:
	case ITEM_WOOD:
	case ITEM_ESSENCE:
	case ITEM_KEY:
	case ITEM_GOLD:
	case ITEM_NETITEM:
		break;
	case ITEM_RECIPE:
		//레시피류
		memset(pr, 0, 100);
		name_idx1 = TEXT_ITEMNAME_START + GetItemName(it->detail >> 3, it->detail & 0x07, it->grade + 1);
		sprintf(pr, "%s", TEXTPTR(name_idx1));

		//세트 정하기
		if (it->grade == GRADE_RARE) {
			if (set)
				it->set = set - 1;
			else {
				j = Random(2);
				it->set = j * 100 + setItem[((itemStartCnt[it->detail >> 3] + (it->detail & 0x07)) * 2 + j) * 3];
			}
		}
		break;
	}

	//if (robin.map >= CAVE_A_1 && it->set >= 100)
	//	it->set -= 100;

	//SetRequire(it);
	it->gold = GetItemPrice(it);

	//이름 정하기
	//등급별로 색을 지정한다.
	memset(gr, 0, 3);
	gr[0] = '|';
	gr[1] = (caveMap != 0 && it->grade == GRADE_SET ? 'c' : itemColorText[grade]);

	if (caveMap && (it->type == ITEM_NECK || it->type == ITEM_RING) && it->grade == GRADE_SET)
		it->icon = caveItemAcc[it->detail] + (it->type == ITEM_RING ? 28 : 0);
	else
		it->icon = GetItemIcon(type, detail, grade);

	memset(name, 0, 100);


	if (caveMap != 0 && grade == GRADE_SET && (type == ITEM_RING || type == ITEM_NECK)) {
		t = TEXT_RA1_NECK + it->detail;
	}
	else if (caveMap != 0 && it->grade == GRADE_SET && type < ITEM_NECK)
		t = TEXT_ITEMNAME_START + ((type * 4) + TEXT_RA1_SWORD - TEXT_ITEMNAME_START + caveItemDetail);
	else
		t = TEXT_ITEMNAME_START + GetItemName(type, detail, grade);

	caveItemGrade = false;
	sprintf(name, "%s", TEXTPTR(t));

	if (name_idx2 >= 0) {
		if (name_idx1 >= 0)
			sprintf(it->name, "%s%s %s %s", gr, pr, su, name);
		else
			sprintf(it->name, "%s%s %s", gr, su, name);
	}
	else if (name_idx1 >= 0) {
		if (type == ITEM_RECIPE) {
			sprintf(it->name, "|b%s%s %s", pr, gr, name);
			it->name[1] = itemColorText[grade + 1];
		}
		else {

			if (grade == GRADE_SET)
				sprintf(it->name, "%s%s%s", pr, gr, name);
			else
				sprintf(it->name, "%s%s %s", gr, pr, name);
		}
	}
	else
		sprintf(it->name, "%s%s", gr, name);


	if (caveMap && (it->type == ITEM_RING || it->type == ITEM_NECK) && it->grade == GRADE_SET) {
		it->detail = caveItemAcc[it->detail];
	}
}

void DrawQuickIcon(OBJECT* pObj, int x, int y, float zoom)
{
	int i = (option.hotSlot == true ? 0 : 1);
	int tempX = x;
	int curRandomIdx;

	switch (pObj->hotKey[0].type) {
	case HOTKEY_SKILL:
		//TEST
		//pObj->hotKey[0].random = true;
		//TEST
		//현재 랜덤으로 돌고 있으면
		if (pObj->hotKey[0].random == true) {
			curRandomIdx = pObj->getSkillList[frame % MAXCHARSKILL];

			//TEST
			//curRandomIdx = activeSkillProb[pObj->type][(frame % MAXCHARSKILL) * 2 + 1];

			//TEST
			DrawSkillIcon(skillData[SKILLDATASIZE * curRandomIdx + 5], x + (float)4 * _2X * zoom, y - (float)4 * _2X * zoom, SKILLICONZOOM * zoom);
		}
		else
			DrawSkillIcon(skillData[SKILLDATASIZE * pObj->hotKey[0].idx + 5], x + (float)4 * _2X * zoom, y - (float)4 * _2X * zoom, SKILLICONZOOM * zoom);

		//pObj->hotKey[0].frame = frame % FPS;
		//pObj->hotKey[0].inven = FPS;

		if (pObj->hotKey[0].frame && pObj->hotKey[0].random == false)
			DrawCycle(x + (float)4 * _2X * zoom, y - (float)4 * _2X * zoom, (float)16 * _2X * zoom * SKILLICONZOOM, (float)16 * _2X * zoom * SKILLICONZOOM, pObj->hotKey[0].frame, pObj->hotKey[0].inven, zoom);

		if (pObj->hotKey[0].randomFrame > 0) {
			pObj->hotKey[0].randomFrame--;
			if (pObj->hotKey[0].randomFrame == 0) {
				pObj->hotKey[0].randomFrame = 0;
				pObj->hotKey[0].random = false;//랜덤 취소
				pObj->hotKey[0].frame = pObj->hotKey[0].inven;
			}
		}
		if (pObj->hotKey[0].randomFrame == 0 && pObj->hotKey[0].random == false && pObj->hotKey[0].frame == 0) {
			MemRectFrameThick(x + (float)2 * _2X * zoom, y - (float)2 * _2X * zoom, (float)18 * _2X * zoom * SKILLICONZOOM, (float)18 * _2X * zoom * SKILLICONZOOM, itemColor[frame % 6], 2 * _2X);
			DrawHand(x - (float)4 * _2X * zoom, y + (float)4 * _2X * zoom, robin.playtime / MOTIONDIV, 2.0f * zoom);

			SetRectPoint(x + (float)2 * _2X * zoom, y - (float)2 * _2X * zoom, (float)18 * _2X * zoom * SKILLICONZOOM, (float)18 * _2X * zoom * SKILLICONZOOM, TOUCH_FUNC_HOTKEYPRESS1 + pObj->type);
		}
		break;
	case HOTKEY_ITEM:
		DrawItemIcon(GetItemPtr(ITEMPTR_INVEN + GetInvenIdx(ITEM_WASTE, pObj->hotKey[0].idx, 0)), pObj, x + (float)4 * _2X * zoom, y - (float)4 * _2X * zoom, SKILLICONZOOM * zoom);
		break;
	case HOTKEY_STATUE:
		DrawIcon(GetItemIcon(ITEM_STATUE, pObj->hotKey[0].idx, false), x + (float)4 * _2X * zoom, y - (float)4 * _2X * zoom, SKILLICONZOOM * zoom, false, false, false, true);

		if (pObj->hotKey[0].frame)
			DrawCycle(x + (float)4 * _2X * zoom, y - (float)4 * _2X * zoom, (float)16 * _2X * zoom * SKILLICONZOOM, (float)16 * _2X * zoom * SKILLICONZOOM, pObj->hotKey[0].frame, pObj->hotKey[0].inven, zoom);
		break;
	case HOTKEY_RING:
		DrawItemIcon(&pObj->equip[EQUIP_RING], pObj, x + (float)4 * _2X * zoom, y - (float)4 * _2X * zoom, zoom * SKILLICONZOOM);

		if (pObj->hotKey[0].frame)
			DrawCycle(x + (float)4 * _2X * zoom, y - (float)4 * _2X * zoom, (float)16 * _2X * zoom * SKILLICONZOOM, (float)16 * _2X * zoom * SKILLICONZOOM, pObj->hotKey[0].frame, pObj->hotKey[0].inven, zoom);
		break;
	}

	x = tempX;

	//hotKeyFrame = frame % 10;

	if (hotKeyFrame && hotKeyFrame / 10 < MAXHOTKEY) {
		DrawEffect(EFFECT_SLOT0 + 7 - (hotKeyFrame % 10), x + (float)(20 * _2X + (int)(hotKeyFrame / 10) * 44 * _2X) * zoom, y + (float)(-20 * _2X) * zoom, LEFT, false, zoom);
		hotKeyFrame--;

		if (hotKeyFrame % 10 == 0)
			hotKeyFrame = 0;
	}

}


void DrawQuick(OBJECT* pObj, int x, int y, int status, float zoom)
{
	int i = 0, count = MAXHOTKEY;
	long long upgradePrice;

	int xGap = 0 * _2X;
	int yGap = 4 * _2X;

	//if (drawHandle == MD_PLAY)
	//DrawLabel(x + (float)(32 * _2X) * zoom, y - (float)(46 * _2X) * zoom, TEXT_ALPHA_SKILL, 0.72f * zoom, cvtDest, cvtLayer, buffering);

	EnemyProfileDraw(x + xGap, y + (float)-2 * _2X * zoom + yGap, pObj->type, false, false, 1.0f * zoom);

	DrawFrame(x + xGap + (float)36 * _2X * zoom, y + yGap, (float)40 * _2X * zoom, (float)40 * _2X * zoom, FRAME_NORMAL);

	if (IsGetHero(GetObjFromPtr(pObj)) == false) {
		DrawLock(getSkillSlotLv[i], x + 4 * _2X * zoom + xGap, y + yGap - (float)5 * _2X * zoom, 1.8f * zoom);
	}
	else if (pObj->hotKey[0].idx == false) {
		CenterText(TEXT_ALPHA_SKILL, x + xGap + (float)36 * _2X * zoom + (float)40 * _2X * zoom / 2, y + yGap - (float)10 * _2X * zoom, 0.8f * zoom);
		CenterText(TEXT_ALPHA_EMPTY, x + xGap + (float)36 * _2X * zoom + (float)40 * _2X * zoom / 2, y + yGap - (float)22 * _2X * zoom, 0.8f * zoom);
		//SetAlpha(32 - Abs(frame / MOTIONDIV % 32 - 16));
		//DrawImage(8 * _2X, 8 * _2X, 224 * _2X, 0 * _2X, x - (float)( - 12 * _2X) * zoom + xGap + (float)37 * _2X * zoom, y - (float)13 * _2X * zoom + yGap, false, false, false, false, false, 2.0f * zoom, sprite[COMMON_IMG], cvtDest, cvtLayer, COMMON_IMG, buffering);
		//SetAlpha(32);
	}

	//upgradePrice = 100;
	//DrawBuyButton(x + xGap, y + (float)-40 * _2X * zoom + yGap, (float)BUYSMALLBUTTON_X * UPGRADEBUTTONPER * zoom, (float)BUYSMALLBUTTON_Y * UPGRADEBUTTONPER * zoom, frame, robin.gold >= upgradePrice ? false : true, upgradePrice, CURRENCY_GOLD, UPGRADEBUTTONPER * zoom, false, false, false, cvtDest, cvtLayer, buffering);
	//SetRectPoint(x + xGap, y + (float)-40 * _2X * zoom + yGap, (float)BUYSMALLBUTTON_X * UPGRADEBUTTONPER * zoom, (float)BUYSMALLBUTTON_Y * UPGRADEBUTTONPER * zoom, TOUCH_FUNC_HOTKEYPRESS1 + i);

	grayScale = 0;
	//else {
	//	DrawBuyButton()
	//}

	//�ϴ� empty�� 
	//if (status)
	//	MemRectFrame(x + (float)((40 * _2X + 8 * _2X) * i) * zoom, y, (float)32 * _2X * zoom, (float)32 * _2X * zoom, colorData[18 + Abs(8 - frame % 16)], cvtDest, cvtLayer, buffering);
	//else
	//	MemRectFrame(x + (float)((40 * _2X + 8 * _2X) * i) * zoom, y, (float)32 * _2X * zoom, (float)32 * _2X * zoom, colorData[18], cvtDest, cvtLayer, buffering);

	DrawQuickIcon(pObj, x + xGap + (float)36 * _2X * zoom, y + yGap, zoom);
	/*
	if (curMenu == 6 && menuCur == 1) {
		if (count == 5) {
			MemImage(5, 7, 99, 9, x + 2, y + 1, COMMON_IMG);
			DrawArray(IMG_STAR, x + 24, y + 1);
			MemImage(5, 7, 109, 9, x + 94, y + 1, COMMON_IMG);
			MemImageRotate(9, 9, 81, 194, x, y, _E | (Abs(3 - menuFrame % 6) * _1), MY_GrpFactor(imgBuffer[HIT_IMG]), MY_GrpFactor(gScreenBuffer));
			MemImageRotate(9, 9, 81, 194, x + 23, y, _E | (Abs(3 - menuFrame % 6) * _1), MY_GrpFactor(imgBuffer[HIT_IMG]), MY_GrpFactor(gScreenBuffer));
			MemImageRotate(9, 9, 81, 194, x + 4 * 23, y, _E | (Abs(3 - menuFrame % 6) * _1), MY_GrpFactor(imgBuffer[HIT_IMG]), MY_GrpFactor(gScreenBuffer));
		}
		else {
			DrawArray(IMG_STAR, x + 1, y + 1);
			MemImageRotate(9, 9, 81, 194, x, y, _E | (Abs(3 - menuFrame % 6) * _1), MY_GrpFactor(imgBuffer[HIT_IMG]), MY_GrpFactor(gScreenBuffer));
		}

		SetAlpha(16);

		if (robin.hotKey[2].type)
			MemRect(x + 8 + 23 * (count == 5 ? 2 : 1), y + 1, 16, 16, 0x000000);

		if (robin.hotKey[3].type && count == 5)
			MemRect(x + 8 + 23 * (count == 5 ? 3 : 2), y + 1, 16, 16, 0x000000);

		SetAlpha(32);
	}
	else {
		if (count == 5) {
			MemImage(5, 7, 99, 9, x + 2, y + 1, COMMON_IMG);
			DrawArray(IMG_STAR, x + 24, y + 1);
			DrawArray(IMG_ZERO, x + 48, y + 1);
			DrawArray(IMG_POUND, x + 70, y + 1);
			MemImage(5, 7, 109, 9, x + 94, y + 1, COMMON_IMG);
		}
		else {
			DrawArray(IMG_STAR, x + 1, y + 1);
			DrawArray(IMG_ZERO, x + 25, y + 1);
			DrawArray(IMG_POUND, x + 47, y + 1);
		}

		if (status) {
			for (i = 0; i < count; i++)
				//hit.bmp
				MemImageRotate(9, 9, 81, 194, x + i * 23, y, _E | (Abs(3 - menuFrame % 6) * _1), MY_GrpFactor(imgBuffer[HIT_IMG]), MY_GrpFactor(gScreenBuffer));
		}
	}

	if (hotKeyFrame && hotKeyFrame / 10 < 5) {
		DrawEffect(EFFECT_SLOT0 + 7 - (hotKeyFrame % 10), x + 16 + (count == 3 ? -23 : 0) + hotKeyFrame / 10 * 23, y + 9, 0, 1);
		hotKeyFrame--;

		if (hotKeyFrame % 10 == 0)
			hotKeyFrame = 0;
	}
	*/
}

void InventoryDraw(OBJECT* pObj, int x, int y, float zoom)
{
	int i;
	int divide = 8;//4단위로 나누라는것
	int xGap = ITEMICONSIZE * 2 + 8 * _2X;
	int yGap = ITEMICONSIZE * 2 + 20 * _2X;
	int star;
	float plusX = (float)(12 * _2X + 1.5f * 36 * _2X) * zoom;
	float plusY = (float)(-16 * _2X) * zoom;
	const signed short* usPtr;

	//프로필 사진 그려주기
	EnemyProfileDraw(x, y - (float)4 * _2X * zoom, GetObjFromPtr(pObj), false, pObj->lv, 1.5f * zoom);

	//프레임 잡아주기
	DrawFrame(x + (float)1.5f * 36 * _2X * zoom, y + (float)0 * _2X * zoom, (float)(34 * 3 * _2X + 20 * _2X) * zoom, (float)(yGap * 2 + 0 * _2X) * zoom, FRAME_NORMAL);
	
	//현재 장비
	//DrawLabel(x - (float)(6 * _2X) * zoom, y + (float)8 * _2X * zoom, TEXT_ALPHA_EQUIP, 0.72f * zoom, cvtDest, cvtLayer, buffering);

	for (i = EQUIP_NECK - 1; i >= 0; i--) {
		usPtr = &equipSlotPos[i * 4];

		DrawEmptyBox(x + plusX + (float)*(usPtr + 2) * zoom, y + plusY + (float)*(usPtr + 3) * zoom, (float)16 * _2X * zoom * 2, (float)16 * _2X * zoom * 2);
		DrawArray(*(usPtr + 1), x + plusX + (float)*(usPtr + 2) * zoom + (float)4 * _2X * zoom, y + plusY + (float)*(usPtr + 3) * zoom - (float)4 * _2X * zoom, zoom * 2);

		if (pObj->equip[*usPtr].type < EMPTY) {
			if (pObj->equipImg[*usPtr] == 0)
				grayScale = 20;

			DrawItemIcon(&pObj->equip[*usPtr], pObj, x + plusX + (float)*(usPtr + 2) * zoom, y + plusY + (float)*(usPtr + 3) * zoom, zoom * 2);

			MemRectFrameThick(x + plusX + (float)*(usPtr + 2) * zoom - (float)2 * _2X * zoom, y + plusY + (float)*(usPtr + 3) * zoom + (float)2 * _2X * zoom, (float)(ITEMICONSIZE * 2 + 4 * _2X) * zoom, (float)(ITEMICONSIZE * 2 + 4 * _2X) * zoom, itemColor[pObj->equip[*usPtr].grade], (float)1 * _2X * zoom);

			//if (*usPtr == EQUIP_RING && pObj->equip[EQUIP_RING].cooldown)
			//	DrawCycle(x + plusX + (float)*(usPtr + 2) * zoom, y + plusY + (float)*(usPtr + 3) * zoom, (float)16 * _2X * 2 * zoom, (float)16 * _2X * 2 * zoom, pObj->equip[EQUIP_RING].cooldown, ringOption[pObj->equip[EQUIP_RING].detail * 7 + 3 + Min(3, pObj->equip[EQUIP_RING].grade)] * 120, zoom, cvtDest, cvtLayer, buffering);

			if (pObj->equipImg[*usPtr] == 0) {
				grayScale = 0;
				SetAlpha(8);
				MemRect(x + plusX + (float)*(usPtr + 2) * zoom, y + plusY + (float)*(usPtr + 3) * zoom, (float)16 * _2X * 2 * zoom, (float)16 * _2X * 2 * zoom, 0xFF0000);
				SetAlpha(32);
			}

			SetRectPoint(x + plusX + (float)*(usPtr + 2) * zoom, y + plusY + (float)*(usPtr + 3) * zoom, (float)16 * _2X * zoom * 2, (float)16 * _2X * zoom * 2, TOUCH_FUNC_EQUIPDETAIL + i);
		}

		if (hotKeyFrame && hotKeyFrame / 10 == *usPtr + 10) {
			DrawEffect(EFFECT_SLOT0 + 7 - (hotKeyFrame % 10), x + plusX + (float)*(usPtr + 2) * zoom + (float)8 * _2X * 2 * zoom, y + plusY + (float)*(usPtr + 3) * zoom - (float)8 * _2X * 2 * zoom, LEFT, false, zoom);
			hotKeyFrame--;

			if (hotKeyFrame % 10 == 0)
				hotKeyFrame = 0;
		}
	}

	//���� ����
	//HeroListDraw(x + (float)(156 * _2X) * zoom, y + (float)8 * _2X * zoom, zoom, false, 64 * _2X, cvtDest, cvtLayer, buffering);

	//���� �����?������ �ִ� ����
	//CrewListDraw(x + (float)(156 * _2X) * zoom, y - (float)62 * _2X * zoom, zoom, false, 48 * _2X, cvtDest, cvtLayer, buffering);
}

int MakeItemType(int seed)
{
	int i;
	int rt = 0;
	int maxType = 0;
	int type;
	//if (seed > 350 - Min(50, UpDiv(ao[PLAYER].ps[PS_LUCK], 20)))
	//	seed = Random(20);
	for (i = ROBIN; i < TOTALCHAR; i++)
		if (IsGetHero(i) == true)
			maxType++;
	type = Random(maxType);

	//10% 확률로 장비
	if (seed < 167)
		return ITEM_SWORD + type;
	//10% 확률로 뚜껑
	else if (seed < 334)
		return ITEM_HELM + type;
	//10% Ȯ���� ����
	else if (seed < 501)
		return ITEM_ARMOR + type;
	//10% 확률로 장갑
	else if (seed < 668)
		return ITEM_GUNTLET + type;
	//10% 확률로 바지
	else if (seed < 835)
		return ITEM_KILT + type;
	//10% Ȯ���� �Ź�
	else //if (seed < 900)
		return ITEM_GREAVES + type;
	//10% 확률로 목걸이
	//else if (seed < 950)
	//	return ITEM_NECK;
	//10% 확률로 반지
	//else //if (seed < 800)
	//	return ITEM_RING;
	//1% 확률로 하트
	//else if (seed < 810)
	//	return ITEM_HEART;
	//4% Ȯ���� ����Ʈ ������
	//else if (seed < 850)
	//	return ITEM_QUEST;
	//15% 확률로 골드
	//else
	//	return ITEM_GOLD;
}

int MakeArenaItem()
{
	int temp = Random(1000);
	// 50% Ȯ���� �����? //������ 1���� ������������ 0.5%�� ����������(100�������� 100%�� �����?
	//if (temp > (500 - arenaFloor * 5)) {
	if (temp < 300) {
		temp = Random(100);
		// 장비 중에 15%확률로 무기
		if (temp < 15)
			return ITEM_SWORD + Random(3);
		else if (temp < 25)
			return ITEM_NECK + Random(2);
		else
			return 3 + Random(14);
	}
	else if (temp < 600)
		return ITEM_GEM;
	else
		return ITEM_GOLD;
}

int MakeCaveItem()
{
	int temp = Random(1000);
	//temp = 999;
	caveMapData = mapData[11];

	if (temp <= 400)
		return -1;
	else if (temp <= 500) {
		caveItemType = ITEM_GEM;
		return 1000 + caveItemType;
	}
	else if (temp <= 700) {
		caveItemType = ITEM_GOLD;
		return 1000 + caveItemType;
	}
	else if (temp <= 1000) {
		switch (mapData[11]) {
		case 0:	//일반방	
			temp = Random(2);
			caveItemType = (temp == 0 ? ITEM_HELM + Random(3) : ITEM_GREAVES + Random(3));
			break;
		case 1:	//강적방
			temp = Random(2);
			caveItemType = (temp == 0 ? ITEM_ARMOR + Random(3) : ITEM_KILT + Random(3));
			break;
		case 2:	//보스방
			temp = Random(2);
			caveItemType = (temp == 0 ? ITEM_NECK : ITEM_RING);
			break;
		case 3:	//강적보스방
			temp = Random(2);
			caveItemType = (temp == 0 ? ITEM_SWORD + Random(3) : ITEM_GUNTLET + Random(3));
			break;
		}
		//return 1000 + ITEM_NECK;
		return 1000 + caveItemType;
	}
	return -1;
}

int MakeGachaItem()
{
	int temp = Random(1000);

	//19������ ���?���� 5.2%Ȯ��
	//if (temp < ITEM_RING * 52)
	return 2000 + ITEM_SWORD + Random(ITEM_RING);
	//2���� �Ǽ��縮�� ���� 1.8% Ȯ��
	//else
	//	return 2000 + ITEM_RING;
	//else
	//	return 2000 + ITEM_SWORD + Random(ITEM_NECK);
	/*
	//18������ ���?���� 5.2%Ȯ��
	if (temp < ITEM_NECK * 52)
		return 2000 + ITEM_SWORD + Random(ITEM_NECK);
	//2���� �Ǽ��縮�� ���� 1.8% Ȯ��
	else if (temp < ITEM_NECK * 52 + 2 * 18)
		return 2000 + ITEM_NECK + Random(2);
	else
		return 2000 + ITEM_SWORD + Random(ITEM_NECK);
	*/
	//������ ���� 3.0%�� Ȯ��
	//else //if (temp < ITEM_NECK * 45 + 2 * 50 + 50)
	//	return 2000 + ITEM_GEM;
	//else
	//	return 2000 + ITEM_GOLD;
}

int MakeItemLevel(int type, int lv)
{
	int rt;

	if (type < ITEM_WASTE || type == ITEM_RECIPE)
		rt = Max(1, lv - 10 + Random(15 + Min(15, UpDiv(ao[PLAYER].ps[PS_LUCK], 20))));
	else
		rt = 1;

	if (rt <= 0)
		return 1;
	else if (rt > 98)
		return 99;
	else
		return rt;
}

//드롭 아이템의 티어/레벨을 정할 때 쓰는 기준 레벨.
//MakeItemDetail()은 lv / 10을 티어 인덱스로 쓰는데, 여기에 플레이어 레벨을 그대로 넣으면
//성을 진행하지 않고 레벨만 올려도 최상위 티어가 나온다. 드롭의 품질은 성 진행도를 따라야 하므로
//성 번호를 기존 1~99 레벨 눈금으로 환산해서 넘긴다. 마지막 성이 99가 된다.
int GetDropLv(void)
{
	int castle = robin.castle;

	if (castle < 0)
		castle = 0;
	else if (castle > TOTALCASTLE - 1)
		castle = TOTALCASTLE - 1;

	return castle * 99 / (TOTALCASTLE - 1);
}

int MakeItemDetail(int type, int lv)
{
	int i, randSum = 0, r;
	int rand = Random(10000);

	switch (type) {
	default:
		//������ ������ ���� �⺻ Ÿ���� ��������.
		r = Min(itemTypeCnt[type], lv / 10);

		if (Random(100) < 50)
			return r;
		else {
			switch (r) {
			default:
				return 0;
			case 2:
				return 1 - Proc(proc1, 1);
			case 3:
				return 2 - Proc(proc2, 2);
			case 4:
				return 3 - Proc(proc3, 3);
			case 5:
				return 4 - Proc(proc4, 4);
			case 6:
				return 5 - Proc(proc5, 5);
			case 7:
				return 6 - Proc(proc6, 6);
			case 8:
				return 7 - Proc(proc7, 7);
			case 9:
				return 8 - Proc(proc8, 8);
			case 10:
				return 9 - Proc(proc9, 9);
			case 11:
				return 10 - Proc(proc10, 10);
			case 12:
				return 11 - Proc(proc11, 11);
			case 13:
				return 12 - Proc(proc12, 12);
			case 14:
				return 13 - Proc(proc13, 13);
			case 15:
				return 14 - Proc(proc14, 14);
			case 16:
				return 15 - Proc(proc15, 15);
			case 17:
				return 16 - Proc(proc16, 16);
			case 18:
				return 17 - Proc(proc17, 17);
			case 19:
				return 18 - Proc(proc18, 18);
			case 20:
				return 19 - Proc(proc19, 19);
			case 21:
				return 20 - Proc(proc20, 20);
			case 22:
				return 21 - Proc(proc21, 21);
			case 23:
				return 22 - Proc(proc22, 22);
			case 24:
				return 23 - Proc(proc23, 23);
			case 25:
				return 24 - Proc(proc24, 24);
			case 26:
				return 25 - Proc(proc25, 25);
			case 27:
				return 26 - Proc(proc26, 26);
			case 28:
				return 27 - Proc(proc27, 27);
			case 29:
				return 28 - Proc(proc28, 28);
			case 30:
				return 29 - Proc(proc29, 29);
			case 31:
				return 30 - Proc(proc30, 30);
			case 32:
				return 31 - Proc(proc31, 31);
			case 33:
				return 32 - Proc(proc32, 32);
			case 34:
				return 33 - Proc(proc33, 33);
			case 35:
				return 34 - Proc(proc34, 34);
			}
		}
		break;
	case ITEM_NECK:
		r = Random(TOTAL_NECK);
		return r;
	case ITEM_RING:
		r = Random(TOTAL_RING);
		return r;
	case ITEM_GEM:
		return Random(TOTAL_GEM);
	case ITEM_WASTE:
		r = wasteDrop[Random(59) / 2];

		if (r >= ITEM_WASTE_FIRESTONE)
			r += Random(5);

		return r;
	case ITEM_IRON:
	case ITEM_LEATHER:
	case ITEM_CLOTH:
	case ITEM_WOOD:
		//재료들
		return Min(7, lv / 12);
	case ITEM_RECIPE:
		//레시피의 종류를 결정
		r = MakeItemType(Random(ITEM_NECK));

		return (r << 3) + MakeItemDetail(r, lv + 10);
	case ITEM_ESSENCE:
		return Random(TOTAL_ESSENCE);
	case ITEM_QUEST:
	case ITEM_NETITEM:
	case ITEM_GOLD:
	case ITEM_KEY:
	case ITEM_STATUE:
		return 0;
	}
}

int MakeItemGrade(int type, int lv, int detail)
{
	int basis = Random(10000);
	int rt = 0;

	switch (type) {
	default:
		//장비의 등급
		//일반 : 80%
		//고급 : 16%
		//희귀 : 3%
		//세트 : 0.89%
		//���� : 0.1%
		//전설 : 0.01%
		if (basis < (8000 - ao[PLAYER].ps[PS_LUCK] * 5))
			rt = GRADE_NORMAL;
		else if (basis < (9600 - ao[PLAYER].ps[PS_LUCK]))
			rt = GRADE_SUPERIOR;
		else if (basis < (9900 - ao[PLAYER].ps[PS_LUCK] / 2))
			rt = GRADE_RARE;
		else if (basis < (9989 - ao[PLAYER].ps[PS_LUCK] / 20))
			rt = GRADE_SET;
		else if (basis < (9999 - ao[PLAYER].ps[PS_LUCK] / 250))
			rt = GRADE_EPIC;
		else
			rt = GRADE_LEGEND;

		return enchantGrade[itemDataOrder[detail * TOTALGRADE + rt]];
	case ITEM_NECK:
	case ITEM_RING:
		//악세사리의 등급
		//일반 : 80%
		//고급 : 16%
		//희귀 : 3%
		//세트 : 0.9%
		//���� : 0.1%
		if (basis < (8000 - ao[PLAYER].ps[PS_LUCK] * 5))
			return GRADE_NORMAL;
		else if (basis < (9600 - ao[PLAYER].ps[PS_LUCK]))
			return GRADE_SUPERIOR;
		else if (basis < (9900 - ao[PLAYER].ps[PS_LUCK] / 2))
			return GRADE_RARE;
		else if (basis < (9990 - ao[PLAYER].ps[PS_LUCK] / 20))
			return GRADE_SET;
		else
			return GRADE_EPIC;
		break;
	case ITEM_GEM:
		//보석의 등급
		//고급 : 80%
		//���?: 18% : 30���� �̻� ���� ���?
		//���� : 2% : 60���� �̻� ���� ���?
		if (basis < (8000 - ao[PLAYER].ps[PS_LUCK] * 5) || lv < 30)
			return GRADE_SUPERIOR;
		else if (basis < (9800 - ao[PLAYER].ps[PS_LUCK] / 2) || lv < 60)
			return GRADE_RARE;
		else
			return GRADE_EPIC;
	case ITEM_WASTE:
	case ITEM_IRON:
	case ITEM_LEATHER:
	case ITEM_CLOTH:
	case ITEM_WOOD:
	case ITEM_ESSENCE:
	case ITEM_QUEST:
	case ITEM_NETITEM:
	case ITEM_GOLD:
	case ITEM_KEY:
	case ITEM_STATUE:
		return GRADE_NORMAL;
	case ITEM_RECIPE:
		//조합서의 등급
		//일반 : 80%
		//고급 : 15%
		//희귀 : 4%
		//세트 : 1%
		if (basis < (8000 - ao[PLAYER].ps[PS_LUCK] * 3))
			rt = GRADE_NORMAL;
		else if (basis < (9500 - ao[PLAYER].ps[PS_LUCK]))
			rt = GRADE_SUPERIOR;
		else if (basis < (9900 - ao[PLAYER].ps[PS_LUCK] / 2))
			rt = GRADE_RARE;
		else
			rt = GRADE_SET;


		//�������� ���� �������� ��Ʈ�� ���?�����ش�.
		if (rt == GRADE_SET && (detail & 0x07) < 2)
			rt = GRADE_RARE;

		return rt;
	}
}

int MakeItemValue(int type, int detail, int grade, int lv)
{
	int rt;

	//�̰����� ������ �뷱�� ����
	switch (type) {
#ifdef NECKRING_8STAR
	case ITEM_NECK:
		rt = neckOptionStatValue[detail * 220 + itemLevelLimit[grade * 2 + 1]];
		break;
#else
	case ITEM_NECK:
		rt = neckOption[detail * NECKOPTIONDATASIZE + Min(3, grade) + 2];
		break;
#endif
	case ITEM_RING:
		//rt = ringOption[detail * RINGOPTIONDATASIZE + 1] * lv / 10 + ringOption[detail * RINGOPTIONDATASIZE];
#ifdef NECKRING_8STAR
		rt = ringOptionStatValue[detail * 220 + itemLevelLimit[grade * 2 + 1]];
#else
		rt = ringOption[detail * RINGOPTIONDATASIZE];
#endif
		break;
	case ITEM_SWORD:
	case ITEM_GUN:
	case ITEM_BOOMERANG:
	default:
		rt = itemValue[itemStartCnt[type] + detail];
		break;
	}

#ifdef GRADEPOW
	rt = RoundDiv(rt * gradeRatio[grade], 100);
#endif

	return rt;
}

int MakeItemId(void)
{
	//아이템 고유 아이디를 넣어준다.
	//고유 아이디 관련 값 : 밀리세컨, 전화번호, 방번호, 아이템 x, y위치
	//0xAAABCDEF
	//AAA : 밀리세컨값
	//B : 전화번호 국번 % 256
	//C : 전화번호 뒷자리 % 256
	//D : 방번호 % 16
#ifdef DEBUG
	if (drawHandle == MD_SIMUL)
		return 1111111111;
#endif

	tms = MC_knlCurrentTime();

	//return (int)(((tms & 0x0000FFFF) << 16) + (Random(16) << 12) + phoneId);
	return (int)(tms);
}

int GetItem(int type, int lv, int detail, int grade, long long count, int set)
{
	int i, j;
	ITEM* it;

	//동료 카드는 lv 0을 "미획득"으로 표시한다(TEXT_NOTACQUIRED).
	//획득한 동료가 lv 0으로 남으면 미획득으로 보이고 튜토리얼 포커싱도 잡히지 않는다.
	if (type == ITEM_CREW && lv < 1)
		lv = 1;

	//占싸븝옙占썰리占쏙옙 占쏙옙占쏙옙占쏙옙占?占쏙옙載ο옙占?占쏙옙占싹댐옙 占싸븝옙
	switch (type) {
	default:
		//case ITEM_WASTE:
		//case ITEM_IRON:
		//case ITEM_LEATHER:
		//case ITEM_CLOTH:
		//case ITEM_WOOD:                                                        
		//case ITEM_ESSENCE:
		//case ITEM_QUEST:
	chk1:

		//같은종류가 있으면 수량을 더해준다.
		for (i = 0; i < robin.maxInven; i++) {
			if (robin.inven[i].type == type && robin.inven[i].detail == detail/* && robin.inven[i].grade == grade*/) {
				//수량을 더해준다.
				if (robin.inven[i].count + count < MAXNUM) {
					robin.inven[i].count += count;
					itemObj = i;

					//이미 칸이 있으면 수량만 더하고 지나가므로 lv이 0인 채로 남는다.
					//여기서 올려줘야 미획득 표시가 풀린다.
					if (robin.inven[i].lv < lv)
						robin.inven[i].lv = lv;

				}
				else {

					return 0;
				}
				break;
			}
		}

		if (i < robin.maxInven)
			break;
	case -1:
	chk2:

		//비어있는 인벤토리를 찾는다.
		//for (i = 0, temp = robin.maxInven; i < robin.maxInven; i++) {
		for (i = 0, temp = TOTALINVENTORY; i < TOTALINVENTORY; i++) {
			if (robin.inven[i].type == EMPTY) {
				temp = i;
				break;
			}
		}

		//최대값이 가장 큰
		//if (temp < robin.maxInven) {
		if (temp < TOTALINVENTORY) {
			//������ �κ��丮�� �������� �ִ´�.
			itemObj = temp;
			MakeItem(&robin.inven[itemObj], type, lv, grade, detail, set);


			if (count > 1)
				robin.inven[itemObj].count = count;

			robin.inven[itemObj].id = MakeItemId();
			it = GetItemPtr(ITEMPTR_INVEN + itemObj);
			robin.equipGet[itemStartCnt[it->type] + it->detail] = true;

			robin.count++;

		}
		else {
			//가방 풀

			return 0;
		}
		break;

	case ITEM_GOLD:
		itemObj = EMPTY;
		robin.gold += count;
		if (robin.gold < 0)
			robin.gold = 0;

		goldFrame = FPS / 2;
		break;
	case ITEM_KEY:
		itemObj = EMPTY;

		break;
	case ITEM_STATUE:
		//�� ȹ���?���� â�� ���� ����
		itemObj = detail;
		robin.statue[detail] = true;
		InitStatue(&ao[raidPlayer]);

		infoFrame = 0;
		npcGetFrame = 0;
		drawHandle = MD_PLAY;
		keyHandle = MK_PLAY;

		break;
	case ITEM_HEART:
		itemObj = EMPTY;
		robin.heart += count;
		//heartFrame = FPS / 2;
		break;
	case ITEM_MEDAL:
		itemObj = EMPTY;
		robin.medal += count;
		medalFrame = FPS;
		break;
	case ITEM_STAR:
		itemObj = EMPTY;
		robin.star += count;
		starFrame = FPS;
		break;
	case ITEM_HAMMER:
		itemObj = EMPTY;
		robin.hammer += count;
		hammerFrame = FPS;
		break;
	case ITEM_SHIELD:
		itemObj = EMPTY;
		robin.shield += count;
		if (robin.shield > GetMaxShield())
			robin.shield = GetMaxShield();
		shieldFrame = FPS;
		break;
	}

	//ITEM_CREW falls through to the default inventory-grant path above; auto-assign to an empty crew slot here.
	//단 튜토리얼에서 동료 편성을 가르치기 전(DEMO_TUTORIAL_CREWMENU)까지는 자동배치하지 않는다.
	//상자에서 얻자마자 편성칸에 들어가 버리면 "동료를 전투에 참가시켜볼까요?" 안내가 할 일이 없다.
	if (type == ITEM_CREW && !(IsTutorialPlaying() && !robin.demoSeen[DEMO_TUTORIAL_CREWMENU])) {
		int crewType = crewData[detail * CREWDATASIZE + CREWDATA_TYPE];
		int emptySlot = -1;
		bool alreadySet = false;

		for (i = 0; i < MAXCREW; i++) {
			if (robin.slotCrew[i] == crewType) {
				alreadySet = true;
				break;
			}
			if (emptySlot == -1 && robin.slotCrew[i] == -1)
				emptySlot = i;
		}

		if (!alreadySet && emptySlot != -1) {
			robin.slotCrew[emptySlot] = crewType;
			crewCnt = GetSlotCrewCnt();
			SetBattleCrew();
		}
	}

	arenaRewardType = type;
	arenaRewardDetail = detail;
	arenaRewardGrade = grade;
	arenaRewardCnt = count;

	SaveGame();

	return 1;
}

void ItemSetString(std::string str, int type, int lv, int detail, int grade, int cnt)
{
	int temp;

	str = null;

	switch (type) {
		// 수량성 아이템
	case ITEM_WASTE:
	case ITEM_IRON:
	case ITEM_LEATHER:
	case ITEM_CLOTH:
	case ITEM_WOOD:
	case ITEM_ESSENCE:
		//str = textId[TEXT_ITEMNAME_START + GetItemName(type, detail, grade)] + " " + std::to_string(cnt) + "개";
		break;
		// 골드
	case ITEM_GOLD:
		str = std::to_string(cnt) + textId[TEXT_SPACE_GOLD];
		break;
		//장비나 보석
	default:
		str = textId[TEXT_ITEMNAME_START + GetItemName(type, detail, grade)];
		break;
	}
}

int GetHeroCnt(void)
{
	int i;
	int cnt = 0;
	for (i = 0; i < TOTALCHAR; i++) {
		if (IsGetHero(i) == true) {
			cnt++;
		}
	}

	return cnt;
}

int GetHeroIdx(int type)
{
	int i;
	int cnt = GetHeroCnt();
	int idx = 0;
	for (i = 0; i < TOTALCHAR; i++) {
		if (IsGetHero(i) == true) {
			if (i == type)
				return idx;
			idx++;
		}
	}

	return cnt;
}

bool IsGetHero(int type)
{
	//if (type != MAXX)
	//	return true;
#ifdef GAMEDEBUG
	//return true;
#endif
	if (robin.lv < getHeroLv[type])
		return false;
	return true;
}

int GetItemName(int type, int detail, int grade)
{
	int tName = detail;

	switch (type) {
	default:
		//if (type < ITEM_NECK)
		//	tName = itemNameOrder[detail * TOTALGRADE + grade];
		break;
	case ITEM_RECIPE:
	case ITEM_GOLD:
		tName = 0;
		break;
	case ITEM_CREW:
		return TEXT_MONSTERNAME_START + crewData[detail * CREWDATASIZE + CREWDATA_TYPE];
	case ITEM_SKILL:
		return TEXT_SKILLNAME_COMMON_ROBIN1 + detail;
	case ITEM_KEY:
		if (detail == ITEM_KEY14)
			tName += ROBIN;
		break;
	}

	return tName + itemNameStart[type];
}

int GetItemIcon(int type, int detail, int grade)
{
	if (type == ITEM_RECIPE)
		return 24;

	//if (type == ITEM_GOLD)
	if (type == ITEM_GOLD)
		return ICON_GOLD;

	if (type == ITEM_HEART)
		return ICON_HEART;

	if (type == ITEM_MEDAL)
		return ICON_MEDAL;

	if (type == ITEM_STAR)
		return ICON_STAR;

	if (type == ITEM_HAMMER)
		return ICON_HAMMER;

	if (type == ITEM_BOX)
		return ICON_BOX + detail;

	if (type == ITEM_KEY && detail == ITEM_KEY14)
		detail += ROBIN;

	return itemIconTable[itemStartCnt[type] + detail];
}

int GetItemSellPrice(int idx)
{
	int i, j, rt;
	int mod = 100;
	ITEM* it = GetItemPtr(idx);

	if (it->type < ITEM_WASTE) {
		//등급별 가격조정
		switch (it->grade) {
		default:
			mod = 100;
			break;
		case GRADE_SUPERIOR:
			//mod = 110;
			mod = 120;
			break;
		case GRADE_RARE:
			mod = 140;
			break;
#ifdef SETITEM
		case GRADE_SET:
			//mod = 150;
			mod = 190;
			break;
#endif
		case GRADE_EPIC:
			//mod = 180;
			mod = 250;
			break;
		case GRADE_LEGEND:
			//mod = 250;
			mod = 390;
			break;
		}

		//소켓별 가격조정
		mod += it->count * 5;

		//강화단계
		mod += it->cooldown * 5;

		for (i = 0; i < 6; i++) {
			if (it->option[i][0] != EMPTYINT) {
				const int* orPtr;

				j = Min(SUFFIX_RESERVED3, it->option[i][0]);
				orPtr = &optionRange[it->option[i][0] * 6];

				if (it->option[i][1] > *(orPtr + 4) + *(orPtr + 5))
					mod += optionValue[j] * 12;
				else if (it->option[i][1] > *(orPtr + 2) + *(orPtr + 3))
					mod += optionValue[j] * 9;
				else if (it->option[i][1] > *orPtr + *(orPtr + 1))
					mod += optionValue[j] * 6;
				else
					mod += optionValue[j] * 3;
			}
		}
	}

	if (it->type == ITEM_RECIPE) {
		mod += it->grade * 20;
		rt = itemSellPrice[itemStartCnt[it->detail >> 3] + (it->detail & 0x07)] / RECIPEGOLDRATIO;
	}
	else
		rt = itemSellPrice[itemStartCnt[it->type] + it->detail];

	rt = rt * mod / 100;

	return rt;
}


long long GetUpgradeHammer(int type, int detail, int grade, int lv)
{
	return itemUpgradeHammer[lv] * (detail * TOTALGRADE + grade + 1);
}

int GetStageBossObjectIdx(void)
{
	int i;
	int bossType = GetStageBossType();//보스타입이 중복이 되지 않는다는 전제하
	for (i = ENEMY; i < NEUTRAL; i++) {
		if (ao[i].active == true && ao[i].type == bossType && ao[i].mom == i) {
			return i;
		}
	}

	return false;
}

int GetStageBossIdx(void)
{
	int i;

	for (i = 0; i < MAXWAVEENEMY; i++) {
		if (wave[(robin.stage * MAXWAVE * MAXWAVEENEMY * WAVEDATASIZE) + robin.room * MAXWAVEENEMY * WAVEDATASIZE + i * WAVEDATASIZE + 2] == MONSTERTYPE_BOSS)
			return (robin.stage * MAXWAVE + robin.room + i);
		//return wave[(robin.stage * MAXWAVE * WAVEDATASIZE) + i * WAVEDATASIZE + 0];
	}

	return (robin.stage * MAXWAVE + robin.room * MAXWAVEENEMY + i);
}

int GetStageBossType()
{
	return wave[GetStageBossIdx() * WAVEDATASIZE + 0];
}

int GetItemPrice(ITEM* it)
{
	int i, j, rt;
	int mod = 100;

	if (it->type < ITEM_WASTE) {
		//등급별 가격조정
		switch (it->grade) {
		default:
			mod = 100;
			break;
		case GRADE_SUPERIOR:
			//mod = 110;
			mod = 120;
			break;
		case GRADE_RARE:
			mod = 140;
			break;
#ifdef SETITEM
		case GRADE_SET:
			//mod = 150;
			mod = 190;
			break;
#endif
		case GRADE_EPIC:
			//mod = 180;
			mod = 250;
			break;
		case GRADE_LEGEND:
			//mod = 250;
			mod = 390;
			break;
		}

		//소켓별 가격조정
		mod += it->count * 5;

		//강화단계
		mod += it->cooldown * 10;

		for (i = 0; i < 6; i++) {
			if (it->option[i][0] != EMPTYINT) {
				const int* orPtr;

				j = Min(SUFFIX_RESERVED3, it->option[i][0]);
				orPtr = &optionRange[it->option[i][0] * 6];

				if (it->option[i][1] > *(orPtr + 4) + *(orPtr + 5))
					mod += optionValue[j] * 12;
				else if (it->option[i][1] > *(orPtr + 2) + *(orPtr + 3))
					mod += optionValue[j] * 9;
				else if (it->option[i][1] > *orPtr + *(orPtr + 1))
					mod += optionValue[j] * 6;
				else
					mod += optionValue[j] * 3;
			}
		}
	}

	if (it->type == ITEM_RECIPE) {
		mod += it->grade * 20;
		rt = itemPrice[itemStartCnt[it->detail >> 3] + (it->detail & 0x07)] / RECIPEGOLDRATIO;
	}
	else
		rt = itemPrice[itemStartCnt[it->type] + it->detail];

	rt = rt * mod / 100;

	if (it->type == ITEM_GEM || it->type == ITEM_RING || it->type == ITEM_NECK)
		rt = 100 + arenaFloor / 10 * 10 + Max(100, Random(100 * (arenaFloor / 10) * ((arenaFloor / 10) - 1)));

	//if (rt < 10)
	//	rt = 10;
	//else if (rt > 65535)
	//	rt = 65535;

	return rt;
}

int GetCharPrice(int obj)
{
	int i, value;

	value = 0;
	for (i = 0; i < TOTALEQUIP; i++) {
		if (ao[obj].equip[i].type != EMPTY)
			value += GetItemPow(ao[obj].equip[i].type, ao[obj].equip[i].detail, ao[obj].equip[i].cooldown);
	}

	//value /= GOLDRATIO * 100;

	return value;
}

int GetCharPow(OBJECT* obj)
{
	int i, value = 0;

	for (i = 0; i < TOTALEQUIP; i++) {
		//for (i = 0; i < EQUIP_WEAPON + 1; i++) {
		if (obj->equip[i].type != EMPTY)
			value += GetItemPow(obj->equip[i].type, obj->equip[i].detail, obj->equip[i].cooldown);
	}

	return value;
}

int GetItemPow(int type, int detail, int cooldown)
{
	int value;
	unsigned char ratio;

	switch (type) {
	case ITEM_SWORD://0
	case ITEM_GUN://1
	case ITEM_BOOMERANG://2
	case ITEM_HELM://3
	case ITEM_HAT://4
	case ITEM_CAP://5
	case ITEM_ARMOR://6
	case ITEM_VEST://7
	case ITEM_COAT://8
	case ITEM_GUNTLET://9
	case ITEM_ARMLET://10
	case ITEM_GLOVE://11
	case ITEM_KILT://12
	case ITEM_SKIRT://13
	case ITEM_PANTS://14
	case ITEM_GREAVES://15
	case ITEM_SHOES://16
	case ITEM_BOOTS://17
		ratio = itemRatio[type / 3];
		break;
	case ITEM_NECK://18
		ratio = itemRatio[EQUIP_NECK];
		break;
	case ITEM_RING://19
		ratio = itemRatio[EQUIP_RING];
		break;
	}
	value = itemPow[itemLevelLimit[2 * detail + 1] + cooldown] * ratio / 100;

	return value;
}

int GetItemStar(int type, int detail, int grade)
{
	int i;
	int idx;

	return itemStar[itemStartCnt[type] + detail] / 100;
	//for (i = 0; i < TOTAL_COLLECTIONS * COLLECTIONSITEMCNT; i++) {
	//	if (collectionData[i * COLLECTIONSDATASIZE + 0] == type && collectionData[i * COLLECTIONSDATASIZE + 1] == detail && collectionData[i * COLLECTIONSDATASIZE + 2] == grade)
	//		return collectionData[i * COLLECTIONSDATASIZE + 3] + 1;
	//}

	//return false;

	//switch (type) {
	//default:
	//	return detail + 1;

	//case ITEM_NECK:
	//	return (detail / 3) + 2;

	//case ITEM_RING:
	//	return (detail / 3) + 3;
	//}
}

int GetCurWeaponCollectionsIndex(void)
{
	int i, j;
	ITEM* it = &ao[PLAYER].equip[EQUIP_WEAPON];

	for (i = 0; i < TOTAL_COLLECTIONS; i++) {
		if (collectionData[i * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + 0 * COLLECTIONSDATASIZE + 0] == it->type
			&& collectionData[i * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + 0 * COLLECTIONSDATASIZE + 1] == it->detail
			&& collectionData[i * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + 0 * COLLECTIONSDATASIZE + 2] == it->grade) {
			return i;
		}
	}
}

int GetNextWeaponCollectionsIndex(void)
{
	int curCollectionIdx = GetCurWeaponCollectionsIndex();

	do {
		curCollectionIdx = ++curCollectionIdx % TOTAL_COLLECTIONS;

	} while (GetInvenIdx(collectionData[curCollectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + 0 * COLLECTIONSDATASIZE + 0], collectionData[curCollectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + 0 * COLLECTIONSDATASIZE + 1], collectionData[curCollectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + 0 * COLLECTIONSDATASIZE + 2]) == -1);

	return curCollectionIdx;
}

bool EquipNextWeapon(void)
{
	int i;
	int curCollectionIdx = GetCurWeaponCollectionsIndex();
	int nextCollectionIdx = GetNextWeaponCollectionsIndex();

	//���Ⱑ �ϳ��ۿ� ���� ���?
	if (curCollectionIdx == nextCollectionIdx)
		return false;

	for (i = 0; i < COLLECTIONSITEMCNT; i++) {
		if (GetInvenIdx(collectionData[nextCollectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 0], collectionData[nextCollectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 1], collectionData[nextCollectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 2]) != -1)
			EquipItem(&ao[PLAYER], &robin.inven[GetInvenIdx(collectionData[nextCollectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 0], collectionData[nextCollectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 1], collectionData[nextCollectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 2])]);
	}



	return true;
}

int GetHighestCollections(int index)
{
	int i;
	int highest = 0;
	int star = collectionData[index * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + 0 * COLLECTIONSDATASIZE + 3];
	for (i = 1; i < COLLECTIONSITEMCNT; i++) {
		if (collectionData[index * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 3] > star) {
			star = collectionData[index * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 3];
			highest++;
		}
	}

	return highest;
}

//�� ������������ ����
int GetItemCount(int type, int detail, int grade)
{
	int i, j;

	for (i = 0, j = 0; i < robin.maxInven; i++) {
		if (robin.inven[i].type == type && robin.inven[i].detail == detail && robin.inven[i].grade == grade) {
			j += Max(1, robin.inven[i].count);
		}
	}

	return j;
}

//�� ������ ���� �κ��丮 ������ ����ȭ�� ����Ǿ�� ��.
int GetItemLv(int type, int detail, int grade)
{
	int i, j;

	for (i = 0, j = 0; i < robin.maxInven; i++) {
		if (robin.inven[i].type == type && robin.inven[i].detail == detail && robin.inven[i].grade == grade) {
			j = Max(0, robin.inven[i].cooldown);
			return j;
		}
	};

	return j;
}

int SetStrongestEquip(int type, int detail, int grade)
{
	int slot = itemEquipSlot[type];
	//���������� ���?�ְų�
	if (ao[PLAYER].equip[slot].type == EMPTY) {
		EquipItem(&ao[PLAYER], &robin.inven[GetInvenIdx(type, detail, grade)]);
		return slot;
	}
	//더 좋은 아이템이면
	else if (ao[PLAYER].equip[slot].detail * TOTALGRADE + ao[PLAYER].equip[slot].grade < detail * TOTALGRADE + grade) {
		EquipItem(&ao[PLAYER], &robin.inven[GetInvenIdx(type, detail, grade)]);
		return slot;
	}

	return -1;
}

int GetEquipSlot(int type, int detail, int grade)
{
	int i;
	OBJECT* pObj = &ao[PLAYER];

	for (i = 0; i < TOTALEQUIP; i++) {
		if (pObj->equip[i].type == EMPTY)
			continue;

		if (pObj->equip[i].type == type && pObj->equip[i].detail == detail && pObj->equip[i].grade == grade)
			return i;
	}

	return -1;
}


bool isEnemyObjActive(void)
{
	int i, j;
	for (i = ENEMY, j = 0; i < NEUTRAL; i++) {
		if (robin.enemyObj[i - ENEMY].active == true)
			j++;
	}

	if (j > 0)
		return true;
	else
		return false;
}

void BackUpEnemyObj(void)
{
	memcpy(&robin.enemyObj, &ao[ENEMY], sizeof(OBJECT) * MAXENEMY * MAXENEMYOBJ);
}

void CopyEnemyObj(void)
{
	int i;
	memcpy(&ao[ENEMY], &robin.enemyObj, sizeof(OBJECT) * MAXENEMY * MAXENEMYOBJ);
	for (i = 0; i < MAXENEMY * MAXENEMYOBJ; i++) {
		if (ao[ENEMY + i].active == true) {
			ao[ENEMY + i].x = ao[ENEMY + i].nx;
			ao[ENEMY + i].y = ao[ENEMY + i].ny;
			ao[ENEMY + i].turn = 0;
			ao[ENEMY + i].turnPosition = HERE;
			ao[ENEMY + i].frame = ao[ENEMY + i].jumpFrame = ao[ENEMY + i].mainFrame = ao[ENEMY + i].attackedFrame = 0;
			
		}
	}
}

int RemainMonstersCnt(void)
{
	int i, j = 0;
	for (i = ENEMY; i < NEUTRAL; i++) {
		if (ao[i].mom == i && ao[i].active == true && ao[i].dead == false) {
			j++;
		}
	}

	return j;
}

int GetEnemyDmgIdx(int enemyObj)
{
	int i;
	for (i = 0; TOTALHITMARK; i++) {
		if (dmgInfo[i].target == enemyObj)
			return i;
	}

	return -1;
}

int GetEnemyMomObj(int idx)
{
	int i;
	for (i = ENEMY; i < NEUTRAL; i++) {
		if (robin.enemyObj[idx - ENEMY].mom == i) {
			return i;
		}
	}
	return false;
}

//n��° ���� ������Ʈ �ѹ��� ������ Ȯ���ϴ� �Լ�
int GetObjectNumFromEnemyIdx(int idx)
{
	int i, before_idx, after_idx, j = 0;
	before_idx = robin.enemyObj[j].mom;
	after_idx = 0;
	for (i = ENEMY; i < NEUTRAL; i++) {
		after_idx = robin.enemyObj[i - ENEMY].mom;
		if (before_idx != after_idx) {
			j++;
			before_idx = after_idx;
		}

		if (j == idx)
			return i;
	}
	return false;
}

int GetAttackEnemy(void)
{
	int i, j = ENEMY;
	long long bestCoolTime = MC_knlCurrentTimeStamp();

	for (i = ENEMY; i < NEUTRAL; i++) {
		if (ao[i].active == true && ao[i].dead == false && ao[i].coolTime > 0 && ao[i].coolTime < bestCoolTime && ao[i].hp < ao[i].maxhp) {
			bestCoolTime = ao[i].coolTime;
			j = i;
		}
	}

	return j;
}
//������Ʈ �ѹ��� ���� ����?������ Ȯ���ϴ� �Լ�
int GetEnemyBarIdx(int idx)
{
	int i, before_idx, after_idx, j = 0;
	//빈 바가 있고,
	//체력이 있고 ,
	before_idx = ao[ENEMY].mom;
	after_idx = 0;
	for (i = ENEMY; i <= idx; i++) {
		after_idx = ao[i].mom;
		if (before_idx != after_idx) {
			j++;
			before_idx = after_idx;
		}
	}
	return j;
}

int GetSlotIdx(int type, int detail, int grade)
{
	int i;

	for (i = 0; i < TOTALEQUIP; i++) {
		if (ao[PLAYER].equip[i].type == EMPTY)
			break;

		if (ao[PLAYER].equip[i].type == type && ao[PLAYER].equip[i].detail == detail && ao[PLAYER].equip[i].grade == grade)
			return i;
	}

	return -1;
}

int GetInvenIdx(int type, int detail, int grade)
{
	int i;

	for (i = 0; i < robin.maxInven; i++) {
		if (robin.inven[i].type == EMPTY)
			break;

		if (robin.inven[i].type == type && robin.inven[i].detail == detail && robin.inven[i].grade == grade)
			return i;
	}

	return -1;
}
//for문을 돌면서 콜렉션을 다 모았는데 아직 보상을 받지 않은 인덱스를 던진다.
int CollectionCheck(void)
{
	int i, j, k;
	int itemType, itemDetail, itemGrade;

	for (i = 0; i < TOTAL_COLLECTIONS; i++) {
		k = 0;
		for (j = 0; j < COLLECTIONSITEMCNT; j++) {
			itemType = collectionData[i * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + j * COLLECTIONSDATASIZE + 0];
			itemDetail = collectionData[i * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + j * COLLECTIONSDATASIZE + 1];
			itemGrade = collectionData[i * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + j * COLLECTIONSDATASIZE + 2];

			if (GetInvenIdx(itemType, itemDetail, itemGrade) != -1)
				k++;
		}
		//���� �̹��� ���� �������� 
		if (k == COLLECTIONSITEMCNT)
			return i;
	}

	return -1;
}

int GetCollectionIdx(int type, int detail, int grade)
{
	int i, j;
	for (i = 0; i < TOTAL_COLLECTIONS; i++) {
		for (j = 0; j < COLLECTIONSITEMCNT; j++) {
			if (collectionData[i * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + j * COLLECTIONSDATASIZE + 0] == type &&
				collectionData[i * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + j * COLLECTIONSDATASIZE + 1] == detail &&
				collectionData[i * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + j * COLLECTIONSDATASIZE + 2] == grade) {
				return i;
			}
		}
	}

	return false;
}

//다음 두가지 함수가 필요하다.
//1. 현재 컬렉션에 모든 장비가 획득된 상태인지.
//-> �̰��� ���� ���� ��ų�� Ȱ��ȭ�� �� �ִ� ���������� Ȯ���� �� �ִ�.
//2. 현재 컬렉션에 모든 장비가 획득되고 장비된 상태인지
//-> �̰��� ���� ���� ��ų�� �������?���������� Ȯ���� �� �ִ�.
//3. 컬렉션 중에 풀장착된 컬렉션이 있다면 이 컬렉션 인덱스를 리턴하는 
//->
bool IsCollectionFull(int collectionIdx)
{
	int i;
	int collectionsItemCnt = 0;

	for (i = 0; i < COLLECTIONSITEMCNT; i++) {
		if (GetItemCount(
			collectionData[collectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 0],
			collectionData[collectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 1],
			collectionData[collectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 2]
		) > 0) {
			collectionsItemCnt++;
		}
	}

	if (collectionsItemCnt == COLLECTIONSITEMCNT)
		return true;
	return false;
}

bool IsCollectionFullEquiped(int collectionIdx)
{
	int i;
	int collectionsItemCnt = 0;

	for (i = 0; i < COLLECTIONSITEMCNT; i++) {
		if (GetEquipSlot(
			collectionData[collectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 0],
			collectionData[collectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 1],
			collectionData[collectionIdx * COLLECTIONSITEMCNT * COLLECTIONSDATASIZE + i * COLLECTIONSDATASIZE + 2]
		) > -1) {
			collectionsItemCnt++;
		}
	}

	if (collectionsItemCnt == COLLECTIONSITEMCNT)
		return true;
	return false;
}

int GetFullEquipedCollectionIdx(void)
{
	int i;
	int collectionsItemCnt = 0;

	for (i = 0; i < TOTAL_COLLECTIONS; i++) {
		if (IsCollectionFullEquiped(i) == true) {
			return i;
		}
	}

	return -1;
}
/*
int EraseCopyItem(void)
{
	int i, j, rt, rt2 = 0, chk = 0;

	memset(needErase, 0, sizeof(needErase));

	for (i = 0; i < nInvenCnt; i++) {
		rt = 0;

		if (a.shop[i + NETINVENSTART].type < EMPTY) {
			for (j = 0; j < TOTALEQUIP; j++) {
				if (ao[PLAYER].equip[j].type < EMPTY && CompareItem(&a.shop[NETINVENSTART + i], &ao[PLAYER].equip[j])) {
					needErase[rt2] = NetItemData[i].idx;
					EraseNetItem(&a.shop[NetItemData[i].idx + NETINVENSTART]);
					chk = 1;
					rt++;
					rt2++;
					break;
				}
			}

			if (rt == 0) {
				for (j = 0; j < TOTALINVENTORY; j++) {
					if (robin.inven[j].type < EMPTY && CompareItem(&a.shop[NETINVENSTART + i], &robin.inven[j])) {
						needErase[rt2] = NetItemData[i].idx;
						EraseNetItem(&a.shop[NetItemData[i].idx + NETINVENSTART]);
						chk = 1;
						rt++;
						rt2++;
						break;
					}
				}
			}

			if (rt)
				i--;
		}
	}

	return rt2;
}
*/
int CompareItem(ITEM* it, ITEM* nt)
{
	int i;

	if (it->id != nt->id || it->type != nt->type || it->detail != nt->detail || it->grade != nt->grade || it->value != nt->value || it->count != nt->count || it->lv != nt->lv)
		return false;

	for (i = 0; i < 6; i++) {
		if (it->option[i][0] != nt->option[i][0] || it->option[i][1] != nt->option[i][1])
			return false;
	}

	return true;
}

void BreakItem(ITEM* it)
{
	it->broken = 1;
	it->name[1] = 'j';
	it->cooldown = Max(0, it->cooldown - 3);
	it->cooldown = 0;
}

void RestoreItem(ITEM* it)
{
	it->broken = 0;
	it->name[1] = itemColorText[it->grade];
}

void EraseItem(ITEM* it)
{
	int i;
	int type = it->type;
	int detail = it->detail;
	const signed char* ucPtr = 0;

	switch (it->type) {
	case ITEM_SWORD:
	case ITEM_BOOMERANG:
	case ITEM_GUN:
		ucPtr = &rpVar2.itemWeapon[(it->type % 3) * 8 + it->detail];
		break;
	case ITEM_HELM:
	case ITEM_HAT:
	case ITEM_CAP:
		ucPtr = &rpVar2.itemHelm[(it->type % 3) * 8 + it->detail];
		break;
	case ITEM_ARMOR:
	case ITEM_VEST:
	case ITEM_COAT:
		ucPtr = &rpVar2.itemArmor[(it->type % 3) * 8 + it->detail];
		break;
	case ITEM_GUNTLET:
	case ITEM_ARMLET:
	case ITEM_GLOVE:
		ucPtr = &rpVar2.itemGlove[(it->type % 3) * 8 + it->detail];
		break;
	case ITEM_KILT:
	case ITEM_SKIRT:
	case ITEM_PANTS:
		ucPtr = &rpVar2.itemPants[(it->type % 3) * 8 + it->detail];
		break;
	case ITEM_GREAVES:
	case ITEM_SHOES:
	case ITEM_BOOTS:
		ucPtr = &rpVar2.itemBoots[(it->type % 3) * 8 + it->detail];
		break;
	case ITEM_NECK:
		ucPtr = &rpVar2.itemNeck[it->detail];
		break;
	case ITEM_RING:
		ucPtr = &rpVar2.itemRing[it->detail];
		break;
	}

	//if (ucPtr)
	//	*ucPtr = Max(0, *ucPtr - 1);

	memset(it, 0, sizeof(ITEM));

	it->type = EMPTY;

	for (i = 0; i < 12; i++)
		it->option[i][0] = EMPTYINT;

	for (i = 0; i < 6; i++)
		it->socket[i] = EMPTYINT;

	robin.count--;
	ArrangeInven();
}

void EraseNetItem(ITEM* it)
{
	int i;

	memset(it, 0, sizeof(ITEM));
	it->type = EMPTY;

	for (i = 0; i < 12; i++)
		it->option[i][0] = EMPTYINT;

	for (i = 0; i < 6; i++)
		it->socket[i] = EMPTYINT;

	nInvenCnt--;
	//ArrangeNetInven();
}

void ArrangeInven(void)
{
	int i, j;
	int writeIdx = 0;

	ITEM tempInven[TOTALINVENTORY];

	// 전체 초기화
	for (i = 0; i < TOTALINVENTORY; i++) {
		memset(&tempInven[i], 0, sizeof(ITEM));

		tempInven[i].type = EMPTY;

		for (j = 0; j < 12; j++)
			tempInven[i].option[j][0] = EMPTYINT;

		for (j = 0; j < 6; j++)
			tempInven[i].socket[j] = EMPTYINT;
	}

	// EMPTY가 아닌 아이템만 앞으로 복사
	for (i = 0; i < TOTALINVENTORY; i++) {
		if (robin.inven[i].type != EMPTY) {
			memcpy(&tempInven[writeIdx], &robin.inven[i], sizeof(ITEM));
			writeIdx++;
		}
	}

	robin.count = writeIdx;

	// 정렬: type -> detail -> grade
	for (i = 0; i < robin.count - 1; i++) {
		for (j = i + 1; j < robin.count; j++) {

			bool swapFlag = false;

			if (tempInven[i].type > tempInven[j].type)
				swapFlag = true;
			else if (tempInven[i].type == tempInven[j].type) {
				if (tempInven[i].detail > tempInven[j].detail)
					swapFlag = true;
				else if (tempInven[i].detail == tempInven[j].detail) {
					if (tempInven[i].grade > tempInven[j].grade)
						swapFlag = true;
				}
			}

			if (swapFlag) {
				ITEM temp;
				memcpy(&temp, &tempInven[i], sizeof(ITEM));
				memcpy(&tempInven[i], &tempInven[j], sizeof(ITEM));
				memcpy(&tempInven[j], &temp, sizeof(ITEM));
			}
		}
	}

	// �ٽ� robin.inven�� �ݿ�
	for (i = 0; i < TOTALINVENTORY; i++) {
		memcpy(&robin.inven[i], &tempInven[i], sizeof(ITEM));
	}
}
/*
void ArrangeNetInven(void)
{
	int i, j;

	//인벤토리를 정렬한다.
	for (i = 0; i < nInvenMax; i++) {
		if (a.shop[i + NETINVENSTART].type == EMPTY) {
			if (i < nInvenMax - 1) {
				memcpy(&a.shop[i + NETINVENSTART], &a.shop[i + NETINVENSTART + 1], sizeof(ITEM) * (nInvenMax - i - 1));
				memcpy(&NetItemData[i], &NetItemData[i + 1], sizeof(NETITEMDATA) * (nInvenMax - i - 1));
			}

			memset(&a.shop[nInvenMax - 1 + NETINVENSTART], 0, sizeof(ITEM));
			a.shop[nInvenMax - 1 + NETINVENSTART].type = EMPTY;

			for (j = 0; j < 12; j++)
				a.shop[nInvenMax - 1 + NETINVENSTART].option[j][0] = EMPTYINT;
			for (j = 0; j < 6; j++)
				a.shop[nInvenMax - 1 + NETINVENSTART].socket[j] = EMPTYINT;

			memset(&NetItemData[nInvenMax - 1], 0, sizeof(NETITEMDATA));
			break;
		}
	}

	for (i = 0; i < nInvenMax; i++) {
		if (a.shop[i + NETINVENSTART].type == EMPTY)
			break;
	}

	nInvenCnt = i;
}
*/
// �켱������, �κ��� ��ȣ�� ���ͼ�, �켱�������� �����ѵ�, �ش��κ��� ��ȣ�������� �����Ѵ�.
void OrderInven(void)
{
	int i;
	int invenSort[2 * TOTALINVENTORY];

	memset(&invenSort, 0, sizeof(invenSort));

	if (robin.count <= 1)
		return;

	//�������� �켱�������� �޾ƿ´�.
	for (i = 0; i < robin.count; i++) {
		invenSort[i] = i;
		invenSort[TOTALINVENTORY + i] = GetOrder(&robin.inven[i], i);	//�������� �켱���� ��ȣ�� �˾ƿ´�.
	}

	//QuickSort(invenSort, 0, robin.count);
	RadixSort(invenSort, robin.count);

	//�ش� �ε��� ��ȣ�� ���� shop�� �����Ѵ�
	memset(&a.shop, 0, sizeof(a.shop));

	for (i = 0; i < TOTALINVENTORY; i++)
		a.shop[i].type = EMPTY;

	for (i = 0; i < robin.count; i++)
		memcpy(&a.shop[i], &robin.inven[invenSort[i]], sizeof(ITEM));

	memcpy(&robin.inven, &a.shop, sizeof(robin.inven));
}

//case �������?�켱����
//�����?���?������ �켱���� �������? ����̰�?���� ����
//�����?���?������ �� �ִ� ���?�켱���� ����
//�����?���?detail�� �������� �켱���� ����
int GetOrder(ITEM* it, int index) {
	int tempOrder = 0;

	switch (it->type) {
	case ITEM_WASTE:
		return TOTAL_WASTE - it->detail;
	case ITEM_RING:
		return TOTAL_WASTE + TOTAL_RING - it->detail;
	default:
		if (EquipCheck(&ao[PLAYER], &robin.inven[index]) == false)
			tempOrder = 1000;

		return TOTAL_WASTE + TOTAL_RING + tempOrder + it->type * 8 + 8 - it->detail;
	case ITEM_NECK:
		return 5000 + TOTAL_WASTE + TOTAL_RING + ITEM_BOOTS * 8 + TOTAL_NECK - it->detail;
	case ITEM_GEM:
		return 5000 + TOTAL_WASTE + TOTAL_RING + ITEM_BOOTS * 8 + TOTAL_NECK + TOTAL_GEM - it->detail;
	case ITEM_RECIPE:
		return 5000 + TOTAL_WASTE + TOTAL_RING + ITEM_BOOTS * 8 + TOTAL_NECK + TOTAL_GEM + 1;
	case ITEM_IRON:
	case ITEM_LEATHER:
	case ITEM_CLOTH:
	case ITEM_WOOD:
		return 5000 + TOTAL_WASTE + TOTAL_RING + ITEM_BOOTS * 8 + TOTAL_NECK + TOTAL_GEM + 1 + (ITEM_IRON - it->type) * 8 + it->detail;
	case ITEM_ESSENCE:
		return 5000 + TOTAL_WASTE + TOTAL_RING + ITEM_BOOTS * 8 + TOTAL_NECK + TOTAL_GEM + 1 + 4 * 8 + it->detail;
	case ITEM_QUEST:
		return 5000 + TOTAL_WASTE + TOTAL_RING + ITEM_BOOTS * 8 + TOTAL_NECK + TOTAL_GEM + 1 + 4 * 8 + TOTAL_ESSENCE + it->detail;
	case ITEM_NETITEM:
		return 5000 + TOTAL_WASTE + TOTAL_RING + ITEM_BOOTS * 8 + TOTAL_NECK + TOTAL_GEM + 1 + 4 * 8 + TOTAL_ESSENCE + TOTAL_QUESTITEM + it->detail;
	}

	return 0;
}

void RadixSort(int* array, int size)
{
	int count[10], temp[2 * TOTALINVENTORY];
	int index, pval, i, j, n;

	memcpy(temp, array, sizeof(temp));

	for (n = 0, pval = 1; n < 4; n++, pval *= 10) {
		for (i = 0; i < 10; i++)
			count[i] = 0;

		for (j = 0; j < size; j++) {
			index = (int)(array[TOTALINVENTORY + j] / pval) % 10;
			count[index] = count[index] + 1;
		}

		for (i = 1; i < 10; i++)
			count[i] = count[i] + count[i - 1];

		for (j = size - 1; j >= 0; j--) {
			index = (int)(array[TOTALINVENTORY + j] / pval) % 10;
			temp[TOTALINVENTORY + count[index] - 1] = array[TOTALINVENTORY + j];
			temp[count[index] - 1] = array[j];
			count[index] = count[index] - 1;
		}

		memcpy(array, temp, sizeof(temp));
	}
}

int RemainedItemCheck(void)
{
	int i, cnt = 0;
	for (i = ITEMOBJ; i < TOTALOBJECT; i++)
		if (ao[i].active == true)
			cnt++;

	return cnt;
}

bool NewItemCheck(void)
{
	int i, newItemCnt = 0;
	for (i = 0; i < robin.count; i++) {
		if (robin.inven[i].seen == false)
			newItemCnt++;
	}

	if (newItemCnt > 0)
		return true;
	else
		return false;
}

bool EmptySlotCheck(int itemType)
{
	int i;
	if (ao[itemType % 3].equip[itemEquipSlot[itemType]].type == EMPTY)
		return true;
	return false;
}

int EquipCheck(OBJECT* pObj, ITEM* it)
{

	//return true;

	if (it->broken)
		return false;

	switch (it->type) {
	case ITEM_SWORD:
	case ITEM_HELM:
	case ITEM_ARMOR:
	case ITEM_GUNTLET:
	case ITEM_KILT:
	case ITEM_GREAVES:
		//robin.lv, robin.str
		if (pObj->type == ROBIN)
			return true;
		break;
	case ITEM_GUN:
	case ITEM_HAT:
	case ITEM_VEST:
	case ITEM_ARMLET:
	case ITEM_SKIRT:
	case ITEM_SHOES:
		//robin.lv, robin.agi
		if (pObj->type == DIANA)
			return true;
		break;
	case ITEM_BOOMERANG:
	case ITEM_CAP:
	case ITEM_COAT:
	case ITEM_GLOVE:
	case ITEM_PANTS:
	case ITEM_BOOTS:
		//robin.lv, robin.ints
		//if (pObj->lv >= it->requireLv && pObj->ps[PS_AGI] >= it->requireStat)
		if (pObj->type == MAXX)
			return true;
		break;
	case ITEM_NECK:
	case ITEM_RING:
		//robin.lv
		//if (pObj->lv >= it->requireLv)
		return true;
		break;
	case ITEM_GEM:
		return false;
	default:
		return false;
	}

	return false;
}

void EquipNewItem(OBJECT* pObj, ITEM* it)
{
	int tEquip = itemEquipSlot[it->type];
	int i;

	//�켱 ������ �� �ִ��� üũ
	if (!EquipCheck(pObj, it)) {
		if (it->broken)
			menuResult = 20;
		else
			menuResult = 40;

		return;
	}

	menuResult = 0;

	//�κ��丮�� �������� �����̱� ������ �׳� �������ش�.
	//���׷��̵带 �ϸ� �κ��丮�� ���׷��̵� ��Ű��, ���� �� �������� ���� �����Ǿ� �ִ� �Ŷ��?���������?�ѹ� �� ���ش�.

	//memcpy(&pObj->equip[tEquip], it, sizeof(ITEM));	//임시저장소에 있는것을 장비해준다.

	if (pObj->equip[tEquip].type == EMPTY) {
		//비어있으면 그냥 넣는다
		memcpy(&pObj->equip[tEquip], it, sizeof(ITEM));	//임시저장소에 있는것을 장비해준다.

		memset(it, 0, sizeof(ITEM));
		it->type = EMPTY;

		for (i = 0; i < 12; i++)
			it->option[i][0] = EMPTYINT;

		for (i = 0; i < 6; i++)
			it->socket[i] = EMPTYINT;
	}
	else {
		//차있으면 교체한다
		memcpy(&tempItem, it, sizeof(ITEM));	//인벤것을 임시 저장소에 넣고
		memcpy(it, &pObj->equip[tEquip], sizeof(ITEM));	//장비되어 있는것을 인벤으로 넣고
		memcpy(&pObj->equip[tEquip], &tempItem, sizeof(ITEM));	//임시저장소에 있는것을 장비해준다.
	}

	SetNpcEquip(it);

	//if (menuResult == 0 && drawHandle == MD_GAMEMENU) {
	menuAni = 12;
	hotKeyFrame = 100 + 7 + tEquip * 10;
	pObj->statUpFrame = 1;
	//pObj->buff[ = 1;
	PlayMusic(M_BUTTON);
	//}

	RefreshStat(pObj);

	if (GetObjFromPtr(pObj) == PLAYER)
		AddBar(&bar[BAR_COMBATPOWER], GetCombatPower(pObj) - (bar[BAR_COMBATPOWER].count + bar[BAR_COMBATPOWER].add), BARFRAME);

	SaveGame();

}

void EquipItem(OBJECT* pObj, ITEM* it)
{
	int tEquip = itemEquipSlot[it->type];
	int collectionIdx = GetCollectionIdx(it->type, it->detail, it->grade);
	int i;

	//�켱 ������ �� �ִ��� üũ
	if (!EquipCheck(pObj, it)) {
		if (it->broken)
			menuResult = 20;
		else
			menuResult = 40;

		return;
	}

	menuResult = 0;

	//�κ��丮�� �������� �����̱� ������ �׳� �������ش�.
	//���׷��̵带 �ϸ� �κ��丮�� ���׷��̵� ��Ű��, ���� �� �������� ���� �����Ǿ� �ִ� �Ŷ��?���������?�ѹ� �� ���ش�.

	memcpy(&pObj->equip[tEquip], it, sizeof(ITEM));	//임시저장소에 있는것을 장비해준다.
	/*
	if (pObj->equip[tEquip].type == EMPTY) {
		//비어있으면 그냥 넣는다
		memcpy(&pObj->equip[tEquip], it, sizeof(ITEM));	//임시저장소에 있는것을 장비해준다.

		memset(it, 0, sizeof(ITEM));
		it->type = EMPTY;

		for (i = 0; i < 12; i++)
			it->option[i][0] = EMPTYINT;

		for (i = 0; i < 6; i++)
			it->socket[i] = EMPTYINT;

		robin.count--;
	}
	else {
		//차있으면 교체한다
		memcpy(&tempItem, it, sizeof(ITEM));	//인벤것을 임시 저장소에 넣고
		memcpy(it, &pObj->equip[tEquip], sizeof(ITEM));	//장비되어 있는것을 인벤으로 넣고
		memcpy(&pObj->equip[tEquip], &tempItem, sizeof(ITEM));	//임시저장소에 있는것을 장비해준다.
	}
	*/

	SetNpcEquip(it);

	//if (menuResult == 0 && drawHandle == MD_GAMEMENU) {
	menuAni = 12;
	hotKeyFrame = 100 + 7 + tEquip * 10;
	//pObj->statUpFrame = 1;
	//pObj->buff[ = 1;
	PlayMusic(M_BUTTON);
	//}

	RefreshStat(pObj);

	if (GetObjFromPtr(pObj) == PLAYER)
		AddBar(&bar[BAR_COMBATPOWER], GetCombatPower(pObj) - (bar[BAR_COMBATPOWER].count + bar[BAR_COMBATPOWER].add), BARFRAME);

	ArrangeInven();

	SaveGame();

}

//���� ��Ţ�� �ִ� ���?�κ��丮�� �ְ� ��Ţ�����͸� �����ϸ鼭 �̹����� �����ش�.
void UnEquipItem(OBJECT* pObj, ITEM* it)
{
	int i;

	if (robin.count < robin.maxInven) {
		//memcpy(&robin.inven[robin.count], it, sizeof(ITEM));
		//robin.equipGet[it->type][it->detail][it->grade] = true;
		//robin.count++;
		//ArrangeInven();

		memset(it, 0, sizeof(ITEM));
		it->type = EMPTY;

		for (i = 0; i < 12; i++)
			it->option[i][0] = EMPTYINT;

		for (i = 0; i < 6; i++)
			it->socket[i] = EMPTYINT;

		UnEquipEffect(pObj, it);
	}
	else
		menuResult = 50;

	SaveGame();
}

void UnEquipEffect(OBJECT* pObj, ITEM* it)
{
	int i;

	//������ ���?
	if (itemEquipSlot[it->type] == EQUIP_WEAPON) {
		//공격을 중단시킨다.
		pObj->attack = false;
#ifdef ONEHEARTONEATTACK
		//turnPosition = COMING;
#ifndef WARIGARI
		//if (autoPlay == true && drawHandle == MD_PLAY) {
		//	BoxOpen();
		//}
#endif
#endif
	}
	//������ ���?
	else if (itemEquipSlot[it->type] == EQUIP_RING) {
		//단축슬롯에서 삭제한다.
		for (i = 0; i < MAXHOTKEY; i++) {
			if (pObj->hotKey[i].type == HOTKEY_RING)
				FreeHotKey(pObj, i);
		}
	}

	SetNpcEquip(it);

	RefreshStat(pObj);
}

int UseItem(OBJECT* pObj, int idx)
{
	ITEM* it = GetItemPtr(idx);

	if (it->count == 0)
		return false;

	//if (it->cooldown) {
	//	infoFrame = INFOFRAME;
		//infoText = TEXT_CANNOTUSE;

	//	return false;
	//}

	switch (it->type) {
	case ITEM_WASTE:
		//���?�Ұ� ����
		switch (it->detail) {
			const unsigned char* ucPtr;

		case ITEM_WASTE_STAR:
		case ITEM_WASTE_MOON:
		case ITEM_WASTE_SUN:
			if (pObj->hp == pObj->ps[PS_HP]) {
				infoFrame = INFOFRAME;
				//infoText = TEXT_CANNOTHPFULL;

				return false;
			}

			PlusHp(pObj, wasteValue[it->detail] * 10 * (100 + pObj->ps[PS_POTION]) / 100);
			if (!pObj->hpRestore)
				pObj->hpRestore = 1;
			//EffectSound(M_BUFF_YELLOW);
			PlayMusic(M_BUFF_YELLOW);
			break;
		case ITEM_WASTE_SILVER:
		case ITEM_WASTE_GOLD:
		case ITEM_WASTE_SCARLET:
			if (pObj->mp == pObj->ps[PS_MP]) {
				infoFrame = INFOFRAME;
				//infoText = TEXT_CANNOTMPFULL;

				return false;
			}

			PlusMp(pObj, wasteValue[it->detail] * 10 * (100 + pObj->ps[PS_POTION]) / 100);
			pObj->mpRestore = 1;
			//EffectSound(M_BUFF_BLUE);
			PlayMusic(M_BUFF_BLUE);
			break;
		case ITEM_WASTE_WATER:
			if (pObj->hp == pObj->ps[PS_HP] && pObj->mp == pObj->ps[PS_MP]) {
				infoFrame = INFOFRAME;
				//infoText = TEXT_CANNOTHPFULL;

				return false;
			}

			PlusHp(pObj, 5 * (100 + pObj->ps[PS_POTION]));
			PlusMp(pObj, 3 * (100 + pObj->ps[PS_POTION]));
			pObj->mpRestore = 1;
			pObj->hpRestore = 1;
			//EffectSound(M_BUFF_BLUE);
			PlayMusic(M_BUFF_BLUE);
			break;
		case ITEM_WASTE_FLUTE:	//풀피리
		case ITEM_WASTE_EYEWASH:	//안약
		case ITEM_WASTE_ANTIDOTE:	//해독제
		case ITEM_WASTE_WING:	//릴의 날개
		case ITEM_WASTE_HOLYWATER:	//성수
			if (pObj->debuf[it->detail - ITEM_WASTE_FLUTE])
				pObj->debuf[it->detail - ITEM_WASTE_FLUTE] = 0;
			else {
				infoFrame = INFOFRAME;
				//infoText = it->detail - ITEM_WASTE_FLUTE + TEXT_NOTSLOW;

				return false;
			}

			pObj->statusRestore = 1;
			//EffectSound(M_BUFF_RED);
			PlayMusic(M_BUFF_RED);
			break;
		case ITEM_WASTE_DAMAGE:
		case ITEM_WASTE_DEFENSE:
		case ITEM_WASTE_MAGIC:
		case ITEM_WASTE_SKILL:
			if (robinmap < ARENA1) {
				infoFrame = INFOFRAME;
				infoText = TEXT_CANNOTUSE;
				//infoText = TEXT_CANNOTARENA;
				return false;
			}

			if (pObj->buff[INC_DAMAGE_ARENA - ITEM_WASTE_DAMAGE + it->detail]) {
				infoFrame = INFOFRAME;
				infoText = TEXT_CANNOTUSE;
				//infoText = TEXT_CANNOTALREADY;
				return false;
			}

			pObj->buff[INC_DAMAGE_ARENA - ITEM_WASTE_DAMAGE + it->detail] = ARENABUFFTIME;
			RefreshStat(pObj);
			break;
		default:
			//던지는 아이템
			if (pObj->attack != 0 || pObj->debuf[STUN] || pObj->debuf[KNOCKBACK]) {
				rpVar2.item = 0;
				infoFrame = INFOFRAME;
				infoText = TEXT_CANNOTUSE;
				//infoText = TEXT_CANNOTUSE;

				return false;
			}

			GetMotionPtr(pObj);

			pObj->currentBullet = it->detail;
			pObj->attack = ATTACK_ITEM;
			pObj->attackFrame = skillStartFrame[ATTACK_ITEM];
			//EffectSound(M_DOWN);
			PlayMusic(M_DOWN);
			break;
		}
		break;
	case ITEM_NETITEM:
		switch (it->detail) {
		case ITEM_NET_BOX_WEAPON_HIGH:
		case ITEM_NET_BOX_WEAPON_MID:
		case ITEM_NET_BOX_WEAPON_LOW:
		case ITEM_NET_BOX_DEFENSE_HIGH:
		case ITEM_NET_BOX_DEFENSE_MID:
		case ITEM_NET_BOX_DEFENSE_LOW:
		case ITEM_NET_BOX_ACCESSORY_HIGH:
		case ITEM_NET_BOX_ACCESSORY_MID:
		case ITEM_NET_BOX_ACCESSORY_LOW:
		case ITEM_NET_BOX_RANDOM:
		case ITEM_NET_BOX_GEM:
			UseItemBox(it);
			//EffectSound(M_ITEM);
			PlayMusic(M_ITEM);
			return false;
		case ITEM_NET_RESURRECTION:
			ResurrectionEffect(pObj);
			//EffectSound(M_BUFF_BLUE);
			PlayMusic(M_BUFF_BLUE);
			break;
		case ITEM_NET_EXPORB:
			LevelUpObj(pObj, NextExp(it->value));
			//SaveFlag(0);
			break;
		}
		break;
	}

	it->count--;

	if (it->type == ITEM_WASTE) {
		if (it->count == 0) {
			int i;

			for (i = 0; i < MAXHOTKEY; i++) {
				if (pObj->hotKey[i].type == HOTKEY_ITEM && pObj->hotKey[i].idx == it->detail)
					FreeHotKey(pObj, i);
			}

			EraseItem(it);
		}
		else
			it->cooldown = itemCooltime[it->detail] * 12;
	}
	else if (it->type == ITEM_NETITEM && !it->count)
		EraseItem(it);

	return true;
}

void UseStatue(OBJECT* pObj, int idx)
{
	switch (idx) {
	case ITEM_STATUE_THUNDER:

		pObj->canMagnet = 1 - pObj->canMagnet;
		//EffectSound(M_BUFF_RED);
		PlayMusic(M_BUFF_RED);
		break;
	case ITEM_STATUE_DIMENSION:
		if (robin.bossRoom == true || escort.active == true) {
			infoFrame = INFOFRAME;

			return;
		}

		ao[raidPlayer].attack = ATTACK_WARP;
		ao[raidPlayer].attackFrame = skillStartFrame[ATTACK_WARP];
		//EffectSound(M_BUFF_PINK);
		PlayMusic(M_BUFF_PINK);
		break;
	case ITEM_STATUE_SQUIRREL:
		pObj->canMagnet = null;
		pObj->flamer = null;
		skillInfoFrame = 0;
		skillUsed = 0;
		buffItemUsed = 0;
		effect.color = false;
		buffItemFrame = 0;
		GetMotionPtr(pObj);

		memset(pObj->buff, 0, sizeof(pObj->buff));
		RefreshStat(pObj);

		pObj->attack = ATTACK_SQUIRELL;
		pObj->attackFrame = skillStartFrame[ATTACK_SQUIRELL];
		//EffectSound(M_ENEMYDEAD);
		PlayMusic(M_ENEMYDEAD);
		break;
	}
}

void UseRing(OBJECT* pObj, int idx)
{
	ITEM* it = GetItemPtr(idx);
	signed int* debuf = pObj->debuf;
	int i, j, useV = 0;
	int valueDiv10 = it->value / 10;

	switch (it->detail) {
	case ITEM_RING0:	//사신의 반지(저주 제거)
		useV = CURSE;
#ifdef USERINGFORALL
		for (i = PLAYER; i < PLAYERALL; i++)
			if (ao[i].active == true && ao[i].dead == false)
				ao[i].statusRestore = 1;
#else
		pObj->statusRestore = 1;
#endif
		break;
	case ITEM_RING1:	//������ ����(�Ǹ� ����)
		useV = BLIND;
#ifdef USERINGFORALL
		for (i = PLAYER; i < PLAYERALL; i++)
			if (ao[i].active == true && ao[i].dead == false)
				ao[i].statusRestore = 1;
#else
		pObj->statusRestore = 1;
#endif
		break;
	case ITEM_RING2:	//�ð��� ����(���� ����)
		useV = STUN;
#ifdef USERINGFORALL
		for (i = PLAYER; i < PLAYERALL; i++)
			if (ao[i].active == true && ao[i].dead == false)
				ao[i].statusRestore = 1;
#else
		pObj->statusRestore = 1;
#endif
		break;
	case ITEM_RING3:	//�ع��� ����(���ο� ����)
		useV = SLOW;
#ifdef USERINGFORALL
		for (i = PLAYER; i < PLAYERALL; i++)
			if (ao[i].active == true && ao[i].dead == false) {
				ao[i].statusRestore = 1;
			}
#else
		pObj->statusRestore = 1;
#endif
		break;
	case ITEM_RING4:	//산호석 반지(독 제거)
		useV = POISON;
#ifdef USERINGFORALL
		for (i = PLAYER; i < PLAYERALL; i++)
			if (ao[i].active == true && ao[i].dead == false)
				ao[i].statusRestore = 1;
#else
		pObj->statusRestore = 1;
#endif
		break;
	case ITEM_RING5:	//생환의 반지(체력 회복)
#ifdef USERINGFORALL
		for (i = PLAYER; i < PLAYERALL; i++)
			if (ao[i].active == true && ao[i].dead == false) {
				ao[i].ringValue[ITEM_RING5] = Min(ao[i].ps[PS_HP], ao[i].hp + UpDiv(it->value * (100 + ao[i].ps[PS_POTION]), 100));
				ao[i].hp = Min(ao[i].ps[PS_HP], ao[i].hp + UpDiv(it->value * (100 + ao[i].ps[PS_POTION]), 100));
				ao[i].hpRestore = 1;
			}
#else
		pObj->hp = Min(pObj->ps[PS_HP], pObj->hp + UpDiv(it->value * (100 + pObj->ps[PS_POTION]), 100));
		pObj->hpRestore = 1;
#endif
		break;
	case ITEM_RING6:	//희생의 반지(마력 회복x 물리데미지 흡수 증가)
		//|e���� |i%d%%|jȮ���� �߰�Ÿ��
	//	pObj->mp = Min(pObj->ps[PS_MP], pObj->mp + UpDiv(it->value * (100 + pObj->ps[PS_POTION]), 100));
	//	pObj->mpRestore = 1;
		useV = INC_EXTRA_RING;
#ifdef USERINGFORALL
		for (i = PLAYER; i < PLAYERALL; i++)
			if (ao[i].active == true && ao[i].dead == false) {
				ao[i].ringValue[ITEM_RING6] = UpDiv(ringOption[it->detail * RINGOPTIONDATASIZE + 2] * 12 * (100 + ao[i].ps[PS_BUFF]), 100);
				ao[i].buff[useV] = ao[i].ringValue[ITEM_RING6];
				ao[i].mpRestore = 1;//마나회복 효과지만 추가타격 효과로 일단 씀
				RefreshStat(&ao[i]);
			}
#else
		pObj->buff[useV] = UpDiv(ringOption[it->detail * RINGOPTIONDATASIZE + 2] * 12 * (100 + pObj->ps[PS_BUFF]), 100);
		RefreshStat(pObj);
#endif
		break;
	case ITEM_RING16:	//��ȭ�� ����(��ų ���� �ð� ����)
#ifdef USERINGFORALL
		for (i = PLAYER; i < PLAYERALL; i++)
			if (ao[i].active == true && ao[i].dead == false)
				for (j = 0; j < MAXHOTKEY; j++) {
					if (ao[i].hotKey[j].type != HOTKEY_NOTHING && ao[i].hotKey[j].frame)
						ao[i].ringValue[ITEM_RING16] = (ao[i].hotKey[j].frame * it->value) / 100;
					ao[i].hotKey[j].frame = ao[i].ringValue[ITEM_RING16];
				}
#else
		for (i = 0; i < MAXHOTKEY; i++) {
			if (pObj->hotKey[i].type != HOTKEY_NOTHING && pObj->hotKey[i].frame)
				pObj->hotKey[i].frame = (pObj->hotKey[i].frame * it->value) / 100;
		}
#endif
		break;
	default:
		//case ITEM_RING7:	//폭주의 반지(공격력 증가)
		//case ITEM_RING8:	//골렘의 반지(방어도 증가)
		//case ITEM_RING9:	//광대의 반지(회피 증가)
		//case ITEM_RING10:	//������ ����(���� ����)
		//case ITEM_RING11:	//�ų��� ����(���� ����)
		//case ITEM_RING12:	//광포의 반지(기절공격 증가)
		//case ITEM_RING13:	//������ ����(ġ��Ÿ ����)
		//case ITEM_RING14:	//궁극의 반지(치명타 데미지 증가)
		//case ITEM_RING15:	//������ ����(�� ���?���� ����)
#ifdef USERINGFORALL
		for (i = PLAYER; i < PLAYERALL; i++)
			if (ao[i].active == true && ao[i].dead == false) {
				if (it->detail == ITEM_RING9) {//������ ����(37)//|e���� |bȸ�� |i%d%% |b����
					ao[i].mpRestore = 1;
				}
				else if (it->detail == ITEM_RING10) {//������ ����(38)//|e���� |b��������?���?|i%d%% |b����
					ao[i].mpDrain = 1;
				}
				else if (it->detail == ITEM_RING15) {//������ ����(43)//|en.���� |b��������?|i%d
					ao[i].hpDrain = 1;
				}
			}
#endif
		useV = (it->detail - ITEM_RING7) + INC_DAMAGE_RING;
		break;
	case ITEM_RING17:	//�����?����(����ġ ȹ��)
		useV = INC_EXP_RING;
		break;
	}

	if (useV) {
		switch (it->detail) {
		case ITEM_RING3:	//�ع��� ����(31)//|e����|i%d%%|jȮ���� �����̻�����
#ifdef RINGERASEALLDEBUF
#ifdef USERINGFORALL
			for (i = PLAYER; i < PLAYERALL; i++)
				if (ao[i].active == true && ao[i].dead == false)
					if (pObj->equip[EQUIP_RING].value > Random(1000)) {
						ao[i].ringValue[ITEM_RING3] = pObj->equip[EQUIP_RING].value;//ȸ���� �����ϸ�
						for (j = 0; j < TOTALDEBUF; j++)
							ao[i].debuf[j] = 0;
					}
					else
						ao[i].ringValue[ITEM_RING3] = 1;//ȸ���� �����ϸ�
#else
			if (Random(100) < it->value)
				for (j = 0; j < TOTALDEBUF; j++)
					pObj->debuf[j] = 0;
#endif
#else
			if (Random(100) < it->value && debuf[useV])
				debuf[useV] = 0;
#endif
			break;
		case ITEM_RING0:	//사신의 반지(28)
		case ITEM_RING1:	//통찰의 반지(29)
		case ITEM_RING2:	//�ð��� ����(30)
		case ITEM_RING4:	//산호석 반지(32)
#ifdef USERINGFORALL
			for (i = PLAYER; i < PLAYERALL; i++)
				if (ao[i].active == true && ao[i].dead == false)
					if (Random(100) < valueDiv10 && ao[i].debuf[useV])
						ao[i].debuf[useV] = 0;
#else
			if (Random(100) < it->value && debuf[useV])
				debuf[useV] = 0;
#endif
			break;
		case ITEM_RING5:	//��ȯ�� ����(33)//|e���� |jHP |i%d |jȸ��
			break;

		case ITEM_RING6:	//�����?����(34)//|e���� |i%d%%|jȮ���� �߰�Ÿ��
		case ITEM_RING7:	//폭주의 반지(35)
		case ITEM_RING8:	//골렘의 반지(36)
		case ITEM_RING9:	//������ ����(37)//|e���� |jȸ�� |i%d%%|j����
		case ITEM_RING10:	//������ ����(38)//|e����|j��������?���?i%d%%|j����
		case ITEM_RING11:	//�ų��� ����(39)
		case ITEM_RING12:	//광포의 반지(40)
		case ITEM_RING13:	//������ ����(41)
		case ITEM_RING14:	//궁극의 반지(42)
		case ITEM_RING15:	//������ ����(43)//|e���� |j��������?-|i%d
		case ITEM_RING16:	//��ȭ�� ����(44)
		case ITEM_RING17:	//�����?����(45)
#ifdef USERINGFORALL
			for (i = PLAYER; i < PLAYERALL; i++)
				if (ao[i].active == true && ao[i].dead == false) {
					pObj->buff[useV] = UpDiv(valueDiv10 * (100 + pObj->ps[PS_BUFF]), 100);
					ao[i].ringValue[it->detail] = pObj->buff[useV] * 10;
					RefreshStat(pObj);
				}
#else
			pObj->buff[useV] = UpDiv(ringOption[it->detail * RINGOPTIONDATASIZE + 2] * 12 * (100 + pObj->ps[PS_BUFF]), 100);
			RefreshStat(pObj);
#endif
			break;
		}
	}

	pObj->hotKey[pObj->currentSkill].frame = pObj->hotKey[pObj->currentSkill].inven;

}

void UseItemBox(ITEM* it)
{
	int tUse;
	//레벨 결정
	arenaRewardLv = 20 + Random(90);

	//타입 결정
	switch (it->detail) {
	case ITEM_NET_BOX_WEAPON_HIGH:
		arenaRewardType = ROBIN;
		break;
	case ITEM_NET_BOX_DEFENSE_HIGH:
		arenaRewardType = ITEM_HELM + Random(15);
		break;
	case ITEM_NET_BOX_ACCESSORY_HIGH:
		arenaRewardType = ITEM_NECK + Random(2);
		break;
	case ITEM_NET_BOX_RANDOM:
		arenaRewardType = Random(ITEM_GEM);
		break;
	case ITEM_NET_BOX_GEM:
		arenaRewardType = ITEM_GEM;
		arenaRewardLv = 1;
		break;
	}

	//등급 결정
	switch (it->detail) {
	case ITEM_NET_BOX_WEAPON_HIGH:
	case ITEM_NET_BOX_DEFENSE_HIGH:
	case ITEM_NET_BOX_ACCESSORY_HIGH:
		tUse = Random(1000);

		//고급 10%
		//희귀 50%
		//세트 30%
		//���� 9.7%
		//전설 0.3%
		if (tUse < 100)
			arenaRewardGrade = GRADE_SUPERIOR;
		else if (tUse < 600)
			arenaRewardGrade = GRADE_RARE;
#ifdef SETITEM
		else if (tUse < 900)
			arenaRewardGrade = GRADE_SET;
#endif
		else if (tUse < 997 || arenaRewardType >= ITEM_NECK)
			arenaRewardGrade = GRADE_EPIC;
		else
			arenaRewardGrade = GRADE_LEGEND;
		break;
	case ITEM_NET_BOX_RANDOM:
		tUse = Random(100);

		if (tUse < 40)
			arenaRewardGrade = GRADE_NORMAL;
		else if (tUse < 75)
			arenaRewardGrade = GRADE_SUPERIOR;
		else if (tUse < 90)
			arenaRewardGrade = GRADE_RARE;
#ifdef SETITEM
		else if (tUse < 97)
			arenaRewardGrade = GRADE_SET;
#endif
		else
			arenaRewardGrade = GRADE_EPIC;
		break;
	case ITEM_NET_BOX_GEM:
		tUse = Random(100);

		if (tUse < 40)
			arenaRewardGrade = GRADE_SUPERIOR;
		else if (tUse < 80)
			arenaRewardGrade = GRADE_RARE;
		else
			arenaRewardGrade = GRADE_EPIC;
		break;
	}

	if (arenaRewardGrade == GRADE_LEGEND && (arenaRewardType >= ITEM_NECK || arenaRewardDetail < 6))
		arenaRewardGrade = GRADE_EPIC;

	//디테일 결정
	arenaRewardDetail = Max(2, MakeItemDetail(arenaRewardType, arenaRewardLv));
	EraseItem(it);
	GetItem(arenaRewardType, arenaRewardLv, arenaRewardDetail, arenaRewardGrade, 1, 0);
	menuItem = robin.count - 1 + ITEMPTR_INVEN;
	SetItemString(it, 0, 0);

	//SaveFlag(0);
}

void SetTestHotKey()
{
#ifdef GAMEDEBUG
	SetHotKey(&ao[ROBIN], HOTKEY_SKILL, SKILL_ROBIN12, 0);
	SetHotKey(&ao[DIANA], HOTKEY_SKILL, SKILL_DIANA7, 0);
	SetHotKey(&ao[MAXX], HOTKEY_SKILL, SKILL_MAXX11, 0);
#endif
}

void SetHotKey(OBJECT* pObj, int type, int idx, int where)
{
	int i;

	FreeHotKey(pObj, where);

	//단축정보 입력
	pObj->hotKey[where].type = type;
	pObj->hotKey[where].idx = idx;
	pObj->hotKey[where].frame = 0;

	switch (type) {
	case HOTKEY_SKILL:
		pObj->hotKey[where].inven = RoundDiv(skillData[pObj->hotKey[where].idx * SKILLDATASIZE + 2] * (100 - pObj->ps[PS_DELAY]), 100);
		if (pObj->hotKey[where].idx == SKILL_MAXX16) {
			pObj->hotKey[where].inven -= GetSkillValue(GetObjFromPtr(pObj), SKILL_MAXX16);
		}
		pObj->hotKey[where].frame = pObj->hotKey[where].inven;
		//TEST
		//pObj->hotKey[where].frame = 0;
		//TEST
		break;
	case HOTKEY_RING:
		pObj->hotKey[where].inven = ringOption[pObj->equip[EQUIP_RING].detail * RINGOPTIONDATASIZE + 3 + Min(3, pObj->equip[EQUIP_RING].grade)] * FPS * 20;
		break;
	case HOTKEY_ITEM:
		pObj->hotKey[where].idx = robin.inven[idx].detail;
		pObj->hotKey[where].inven = idx;
		break;
	}

	//���� ��ų�� ����Ű�� �����Ǿ����� �˻�
	for (i = 0; i < MAXHOTKEY; i++) {
		if (i != where && pObj->hotKey[i].type == type) {
			if (type == HOTKEY_ITEM) {
				//���� ��ų�� �ִ°��?���������ش�
				if (pObj->hotKey[i].idx == pObj->hotKey[where].idx)
					FreeHotKey(pObj, i);
			}
			else {
				//���� ��ų�� �ִ°��?���������ش�
				if (pObj->hotKey[i].idx == idx)
					FreeHotKey(pObj, i);
			}
		}
	}

	if (GetObjFromPtr(pObj) == PLAYER) {
		hotKeyFrame = where * 10 + 7;
	}
}

void FreeHotKey(OBJECT* pObj, int where)
{
	if (pObj->hotKey[where].type == HOTKEY_RING) {
		int i;

		//����ȿ���� �����ش�.
		for (i = INC_DAMAGE_RING; i < INC_DAMAGE_ARENA; i++)
			pObj->buff[i] = 0;

		if (pObj->attack == ATTACK_MAGIC) {
			pObj->attack = false;
#ifdef ONEHEARTONEATTACK
			pObj->turnPosition = COMING;
#ifndef WARIGARI
			if (autoPlay == true && drawHandle == MD_PLAY) {
				BoxOpen();

			}
#endif
#endif
		}

		RefreshStat(pObj);
	}

	memset(&pObj->hotKey[where], 0, sizeof(HOTKEY));
}

int GetItemValue(ITEM* it)
{
	int i;
	long long int value, value2, tv1, tv2;
	int valueInt;
	float valueFloat;
	int* ucPtr = &it->option[0][0];

	value = it->value;

	if (it->type < ITEM_NECK) {
		if (it->cooldown) {
			if (value < 10)
				value += it->cooldown;
			else
				value = RoundDiv(value * (100 + it->cooldown * 10), 100);
		}
	}
	switch (it->type) {
	case ITEM_SWORD:
	case ITEM_GUN:
	case ITEM_BOOMERANG:
		tv1 = 100, tv2 = 0;

		for (i = 0; i < TOTALOPTION; i++, ucPtr += 2) {
			if (*ucPtr <= PREFIX_BOOMERANG_DMG)
				tv1 += *(ucPtr + 1);
			else if (*ucPtr >= SUFFIX_WEAPON_DMG && *ucPtr <= SUFFIX_BOOMERANG_DMG)
				tv2 += *(ucPtr + 1);
		}

		value = RoundDiv((RoundDiv(value * tv1, 100) + tv2) * (100), 100);
		break;
	default:
		if (it->type < ITEM_WASTE) {
			for (i = 0, tv1 = 100, tv2 = 0; i < 6; i++, ucPtr += 2) {
				if (*ucPtr == PREFIX_ARMOR)
					tv1 += *(ucPtr + 1);
				else if (*ucPtr == SUFFIX_ARMOR)
					tv2 += *(ucPtr + 1);
			}

			for (i = 0; i < 6; i++) {
				if (it->socket[i] != EMPTYINT && it->socket[i] % 10 == ITEM_GEM_EMERALD)
					tv2 += (it->socket[i] / 10 + 2) * 2;
			}

			value = RoundDiv(value * tv1, 100) + tv2;
		}
		break;
	case ITEM_NECK:
		break;
	case ITEM_RING:
		break;
	case ITEM_GEM:
		break;
	case ITEM_RECIPE:
		break;
	case ITEM_NETITEM:
		break;
	}

	return value;

}

void SetItemString(ITEM* it, int addDetail, int addCool)
{
	long long int value, value2, tv1, tv2;
	int valueInt;
	float valueFloat;
	int i;
	int min, max;
	int* ucPtr = &it->option[0][0];

	if (it->type == EMPTY)
		return;

	memset(tempStr, 0, sizeof(tempStr));

	if (shopType == SHOPTYPE_QUICK && menuFocus < 100 && shopDesc[scS[MENU_SHOP] * 4 + menuFocus]) {
		sprintf(tempStr, "%s", TEXTPTR(shopDesc[scS[MENU_SHOP] * 4 + menuFocus]));
		//가격 텍스트 합성
		SetNetString(it);
	}
	else {
		switch (it->type) {
		case ITEM_QUEST:
		default:
			//�������� ������ ���?�ִ� �������� ��ų�?�Ĵ� ����â�� ���?
			if (menuDepth == 2 && shopType != SHOPTYPE_CRAFT && it->type >= ITEM_WASTE && it->type < ITEM_RECIPE) {
				memset(dmgStr, 0, 100);
				sprintf(dmgStr, textId[TEXT_SHOP_COUNT], it->name, menuItemCount);
			}
			temp = TEXT_ITEMDESC_START + GetItemName(it->type, it->detail + addDetail, it->grade);
			//ReadString(temp);
			sprintf(tempStr, "%s", TEXTPTR(temp));
			break;
		case ITEM_RING:
			//쿨타임
			memset(dmgStr, 0, 100);
			//ReadString(TEXT_COOLTIME);
			sprintf(dmgStr, TEXTPTR(TEXT_COOLTIME), ringOption[it->detail * RINGOPTIONDATASIZE + 3 + Min(3, it->grade)] * 10);

			temp = TEXT_ITEMDESC_START + (it->set >= SET_RA1 ? TEXT_ITEMDESC_NECK - TEXT_ITEMDESC_START + it->detail + 28 : GetItemName(it->type, it->detail, it->grade));
			//ReadString(temp);
			sprintf(tempStr, TEXTPTR(temp), dmgStr);
			break;
		case ITEM_RECIPE:
			temp = TEXT_ITEMNAME_START + GetItemName(it->detail >> 3, it->detail & 0x07, it->grade + 1);
			//ReadString(temp);
			//ReadString(TEXT_ITEMDESC_RECIPE);

			switch (it->grade) {
			default:
				//ReadString(TEXT_SUPERIOR + it->grade);
				sprintf(tempStr, "|b%s %s|b%s", TEXTPTR(TEXT_SUPERIOR + it->grade), TEXTPTR(temp), TEXTPTR(TEXT_ITEMDESC_RECIPE));
				tempStr[1] = itemColorText[it->grade + 1];
				//TextFree(TEXT_SUPERIOR + it->grade);
				break;
			case GRADE_RARE:
				//ReadString(TEXT_SETNAME_START + (it->set % 100));
				sprintf(tempStr, "|q%s:|i%s|b%s", TEXTPTR(TEXT_SETNAME_START + (it->set % 100)), TEXTPTR(temp), TEXTPTR(TEXT_ITEMDESC_RECIPE));
				//TextFree(TEXT_SETNAME_START + (it->set % 100));
				break;
#ifdef SETITEM
			case GRADE_SET:
				sprintf(tempStr, "|g%s|b%s", TEXTPTR(temp), TEXTPTR(TEXT_ITEMDESC_RECIPE));
				break;
#endif
			}

			//TextFree(TEXT_ITEMDESC_RECIPE);
			//TextFree(temp);
			break;
		case ITEM_NETITEM:
			//�������� ������ ���?�ִ� �������� ��ų�?�Ĵ� ����â�� ���?
			if (menuDepth == 2 && menuItemCount > 1) {
				memset(dmgStr, 0, 100);
				sprintf(dmgStr, textId[TEXT_SHOP_COUNT], it->name, menuItemCount);
			}

			temp = TEXT_ITEMDESC_START + GetItemName(it->type, it->detail, it->grade);
			//ReadString(temp);

			if (it->detail == ITEM_NET_EXPORB)
				sprintf(tempStr, TEXTPTR(temp), it->lv);
			else
				sprintf(tempStr, "%s", TEXTPTR(temp));
			break;
		}

		//TextFree(temp);
	}

	isT = 0;
	isC = 0;

	//��ȭ�� ���� �⺻�� ����
	value = it->value;



	memset(dmgStr, 0, 100);
	//memset(dmgSubStr, 0, 100);

	if (it->type < ITEM_NECK) {
		if (it->cooldown) {
			if (value < 10)
				value += it->cooldown;
			else
				value = RoundDiv(value * (100 + it->cooldown * 10), 100);
		}
		//if (addDetail) {
		//	value = itemUpgradeValue[it->type * TOTAL_COLLECTIONS * (ITEMMAXLEVEL + 1) + (it->detail + addDetail) * TOTALGRADE * (ITEMMAXLEVEL + 1) + it->grade * (ITEMMAXLEVEL + 1) + it->cooldown];
		//}
		//else {
		//	value = itemUpgradeValue[it->type * TOTAL_COLLECTIONS * (ITEMMAXLEVEL + 1) + (it->detail) * TOTALGRADE * (ITEMMAXLEVEL + 1) + it->grade * (ITEMMAXLEVEL + 1) + it->cooldown + addCool];
		//}
	}

	switch (it->type) {
	case ITEM_SWORD:
	case ITEM_GUN:
	case ITEM_BOOMERANG:
		//���� �������� ������ ���?
		//if (it == &robin.charDatap[pObj->type].equip[EQUIP_WEAPON]) {
		//	tv1 = robin.ps[PS_DMGMOD];
		//	tv2 = robin.ps[PS_DMGADD];

		//	//if (it->cooldown && drawHandle == MD_GAMEMENU)
		//	//	sprintf(dmgStr, "|b%d~%d |p[lv %d]", RoundDiv(robin.ps[PS_WEAPONDMG] * (100 - weaponRange[it->type]), 100), RoundDiv(robin.ps[PS_WEAPONDMG] * (100 + weaponRange[it->type]), 100), it->cooldown);
		//	//else
		//		sprintf(dmgStr, "|b%d~%d", RoundDiv(robin.ps[PS_WEAPONDMG] * (100 - weaponRange[it->type]), 100), RoundDiv(robin.ps[PS_WEAPONDMG] * (100 + weaponRange[it->type]), 100));
		//}
		//else {
		tv1 = 100, tv2 = 0;

		for (i = 0; i < TOTALOPTION; i++, ucPtr += 2) {
			if (*ucPtr <= PREFIX_BOOMERANG_DMG)
				tv1 += *(ucPtr + 1);
			else if (*ucPtr >= SUFFIX_WEAPON_DMG && *ucPtr <= SUFFIX_BOOMERANG_DMG)
				tv2 += *(ucPtr + 1);
		}

		//sprintf(dmgStr, "|b%lld ~ %lld", RoundDiv((RoundDiv(value * tv1, 100) + tv2) * (100 - weaponRange[it->type]), 100), RoundDiv((RoundDiv(value * tv1, 100) + tv2) * (100 + weaponRange[it->type]), 100));
		sprintf(dmgStr, "|b%lld", RoundDiv((RoundDiv(value * tv1, 100) + tv2) * (100), 100));
		if (tv1 > 100 || tv2 > 0 || it->cooldown)
			dmgStr[1] = 'e';

		isT += 54 * _2X;
		break;
	default:
		if (it->type < ITEM_WASTE) {
			for (i = 0, tv1 = 100, tv2 = 0; i < 6; i++, ucPtr += 2) {
				if (*ucPtr == PREFIX_ARMOR)
					tv1 += *(ucPtr + 1);
				else if (*ucPtr == SUFFIX_ARMOR)
					tv2 += *(ucPtr + 1);
			}

			for (i = 0; i < 6; i++) {
				if (it->socket[i] != EMPTYINT && it->socket[i] % 10 == ITEM_GEM_EMERALD)
					tv2 += (it->socket[i] / 10 + 2) * 2;
			}

			sprintf(dmgStr, "|e%lld", RoundDiv(value * tv1, 100) + tv2);
			if (tv1 == 100 && tv2 == 0 && it->cooldown == 0)
				dmgStr[1] = 'b';

			isT += 54 * _2X;
		}
		break;
	case ITEM_NECK:
		temp = TEXT_PREFIX_DESC + neckOption[it->detail * NECKOPTIONDATASIZE + 1];
		sprintf(dmgStr, TEXTPTR(temp), it->value);
		break;
	case ITEM_RING:
		temp = TEXT_RING_OPTION + it->detail;
		sprintf(dmgStr, TEXTPTR(temp), it->value);
		break;
	case ITEM_GEM:
		memset(optionStr[0], 0, 50);
		sprintf(optionStr[0], TEXTPTR(TEXT_PREFIX_DESC + *ucPtr), *(ucPtr + 1));

		memset(recipeName, 0, sizeof(recipeName));
		sprintf(recipeName, "%s:%s", it->name, optionStr[0]);
		break;
	case ITEM_RECIPE:
		memset(dmgStr, 0, 100);
		value = MakeItemValue(it->detail >> 3, it->detail & 0x07, it->grade + 1, 0);

		if (it->detail >> 3 < ITEM_HELM)
			sprintf(dmgStr, "|b%lld - %lld", RoundDiv(value * (100 - weaponRange[it->detail >> 3]), 100), RoundDiv(value * (100 + weaponRange[it->detail >> 3]), 100));
		else
			sprintf(dmgStr, "|b%lld", value);

		memset(recipeDesc, 0, sizeof(recipeDesc));
		sprintf(recipeDesc, textId[TEXT_SPACE_GOLD_COUNT], itemPrice[itemStartCnt[it->detail >> 3] + (it->detail & 0x07)] / 2);
		break;
	case ITEM_NETITEM:
		SetNetString(it);
		break;
	}

	SetItemString_Gem(it);
}

void SetItemString_Gem(ITEM* it)
{
	int i, j, value;
	int valueInt;
	float valueFloat;
	unsigned char mark[12];
	unsigned char gem[6];
	const int* ucPtr;

	if (it->type < ITEM_GEM) {
		//보석 효과
		memset(gem, 0, sizeof(gem));
		memset(gemStr, 0, sizeof(gemStr));

		for (i = 0; i < 6; i++) {
			if (it->socket[i] != EMPTYINT)
				gem[it->socket[i] % 10] += it->socket[i] / 10 + 2;
		}

		memset(mark, 0, 12);

		ucPtr = &it->option[0][0];

		for (i = 0; i < 12; i++, ucPtr += 2) {
			memset(optionStr[i], 0, 50);

			if (*ucPtr != EMPTYINT && mark[i] == 0) {
				int* tPtr = &it->option[i + 1][0];

				mark[i] = 1;
				value = *(ucPtr + 1);

				for (j = i + 1; j < 12; j++, tPtr += 2) {
					if (*tPtr == *ucPtr || (*tPtr == PREFIX_LUCK && *ucPtr == SUFFIX_LUCK) || (*tPtr == SUFFIX_LUCK && *ucPtr == PREFIX_LUCK) || (*tPtr == PREFIX_GOLD && *ucPtr == SUFFIX_GOLD) || (*tPtr == SUFFIX_GOLD && *ucPtr == PREFIX_GOLD) || (*tPtr == PREFIX_EXP && *ucPtr == SUFFIX_EXP) || (*tPtr == SUFFIX_EXP && *ucPtr == PREFIX_EXP)) {
						mark[j] = 1;
						value += *(tPtr + 1);
					}
				}

				switch (*ucPtr) {
				case PREFIX_FIRE_REGIST:
				case PREFIX_FROST_REGIST:
				case PREFIX_THUNDER_REGIST:
				case PREFIX_HOLY_REGIST:
				case PREFIX_DARK_REGIST:
					value += gem[*ucPtr - PREFIX_FIRE_REGIST];
					gem[*ucPtr - PREFIX_FIRE_REGIST] = 0;
					break;
				case SUFFIX_ARMOR:
					value += gem[5] * 2;
					gem[5] = 0;
					break;
				}

				/*
				switch (*ucPtr) {
				case PREFIX_AGI:
				case PREFIX_INT:
					temp = TEXT_PREFIX_DESC_SEP + *ucPtr * 2;
					valueFloat = value / 100;
					sprintf(optionStr[i], "%s |e%.2f %s", TEXTPTR(temp), valueFloat, TEXTPTR(temp + 1));
					//sprintf(optionStr[i], TEXTPTR(temp), (float)(Abs(ao[idx].ps[optionInfo[i * 2]])) / 100);
					break;
				case PREFIX_ARMOR:
				case SUFFIX_ARMOR:
				case PREFIX_SKILLDMG:
				case PREFIX_DEFENSE:
				case PREFIX_BUFF:
				case SUFFIX_DELAY:
					temp = TEXT_PREFIX_DESC_SEP + *ucPtr * 2;
					valueFloat = (float)(Abs(value)) / 10;
					sprintf(optionStr[i], "%s |e%.1f%% %s", TEXTPTR(temp), valueFloat, TEXTPTR(temp + 1));
					//sprintf(optionStr[i], TEXTPTR(temp), (float)Abs(ao[idx].ps[optionInfo[i * 2]]) / 10);
					break;
				case PREFIX_CRITICAL:
				case PREFIX_PIERCE:
				case PREFIX_EXTRA:
				case SUFFIX_CRITICAL:
				case SUFFIX_EVASION:
					temp = TEXT_PREFIX_DESC_SEP + *ucPtr * 2;
					valueFloat = (float)(Abs(value));
					sprintf(optionStr[i], "%s |e%.1f%% %s", TEXTPTR(temp), valueFloat, TEXTPTR(temp + 1));
					//sprintf(optionStr[i], TEXTPTR(temp), (float)Abs(ao[idx].ps[optionInfo[i * 2]]) / 10);
					break;
				case PREFIX_VIT:
					temp = TEXT_PREFIX_DESC_SEP + *ucPtr * 2;
					valueFloat = Abs(value) - defaultStat[3 * 0 + it->type % 3];
					sprintf(optionStr[i], "%s |e%f %s", TEXTPTR(temp), valueInt, TEXTPTR(temp + 1));
					//sprintf(optionStr[i], TEXTPTR(temp), Abs(ao[idx].ps[optionInfo[i * 2]]) - defaultStat[3 * 0 + ao[idx].type]);
					break;
					//�ƹ��͵� ���� ���?
				case SUFFIX_ENEMYREGEN:
				case SUFFIX_POISON_IMMUNE:
				case SUFFIX_BLIND_IMMUNE:
				case SUFFIX_SLOW_IMMUNE:
				case SUFFIX_CURSE_IMMUNE:
				case SUFFIX_STUN_IMMUNE:
				case SUFFIX_ALWAYSCURSE:
					temp = TEXT_PREFIX_DESC_SEP + *ucPtr * 2;
					sprintf(optionStr[i], "%s", TEXTPTR(temp));
					//sprintf(optionStr[i], TEXTPTR(temp), Abs(ao[idx].ps[optionInfo[i * 2]]));
					break;
					//���밪�� ���?
				case PREFIX_STR:
				case PREFIX_FIRE_REGIST:
				case PREFIX_FROST_REGIST:
				case PREFIX_THUNDER_REGIST:
				case PREFIX_HOLY_REGIST:
				case PREFIX_DARK_REGIST:
				case PREFIX_HPRESTORE:
				case PREFIX_MPRESTORE:

				case SUFFIX_WEAPON_DMG:
				case SUFFIX_SWORD_DMG:
				case SUFFIX_GUN_DMG:
				case SUFFIX_STAT:
				case SUFFIX_HP:
				case SUFFIX_MP:
				case SUFFIX_ALLREGIST:
				case SUFFIX_SKILL:

				case SUFFIX_HPDECREASE:
				case SUFFIX_MINUSARMOR:
				case SUFFIX_MINUSHP:
				case SUFFIX_MINUSMP:
				case SUFFIX_MINUSREGIST:
				case SUFFIX_MINUSINT:
				case SUFFIX_MINUSSTR:
				case SUFFIX_MINUSAGI:
				case SUFFIX_MINUSSKILL:
					temp = TEXT_PREFIX_DESC_SEP + *ucPtr * 2;
					valueFloat = Abs(value);
					sprintf(optionStr[i], "%s |e%.0f %s", TEXTPTR(temp), valueFloat, TEXTPTR(temp + 1));

					//sprintf(optionStr[i], "%s |e%ld% %s", TEXTPTR(temp), valueInt, TEXTPTR(temp + 1));
					//sprintf(optionStr[i], TEXTPTR(temp), Abs(ao[idx].ps[optionInfo[i * 2]]));
					break;
					//%�� ���?
				default:
					temp = TEXT_PREFIX_DESC_SEP + *ucPtr * 2;
					//valueInt = Abs(value);
					valueFloat = Abs(value);

					sprintf(optionStr[i], "%s |e%.0f %s", TEXTPTR(temp), valueFloat, TEXTPTR(temp + 1));

					//sprintf(optionStr[i], "%s |e%d% %s", TEXTPTR(temp), valueInt, TEXTPTR(temp + 1));
					//sprintf(optionStr[i], TEXTPTR(temp), Abs(ao[idx].ps[optionInfo[i * 2]]));
					break;
				}
				*/
				sprintf(optionStr[i], TEXTPTR(TEXT_PREFIX_DESC + *ucPtr), value);
				//TextFree(TEXT_PREFIX_DESC + *ucPtr);
				isT += 13;
			}
		}

		for (i = 0; i < 6; i++) {
			if (gem[i]) {
				switch (i) {
				case ITEM_GEM_RUBY:
					temp = PREFIX_FIRE_REGIST;
					break;
				case ITEM_GEM_SAPPHIRE:
					temp = PREFIX_FROST_REGIST;
					break;
				case ITEM_GEM_AMETHYST:
					temp = PREFIX_THUNDER_REGIST;
					break;
				case ITEM_GEM_DIAMOND:
					temp = PREFIX_HOLY_REGIST;
					break;
				case ITEM_GEM_PERL:
					temp = PREFIX_DARK_REGIST;
					break;
				case ITEM_GEM_EMERALD:
					temp = SUFFIX_ARMOR;
					gem[i] *= 2;
					break;
				}

				//ReadString(TEXT_PREFIX_DESC + temp);
				sprintf(gemStr[i], TEXTPTR(TEXT_PREFIX_DESC + temp), gem[i]);
				//TextFree(TEXT_PREFIX_DESC + temp);
				isT += 13;
			}
		}

#ifdef SETITEM
		//��Ʈ ȿ�� �ɼ� �ؽ�Ʈ ����
		if (it->grade == GRADE_SET) {
			ucPtr = &setOption[(it->set % 100) * SETOPTIONDATASIZE];
			memset(setStr, 0, sizeof(setStr));

			//세트 이름 및 세트 개수
			sprintf(setStr[0], "|q%s|h(%d/%d)", TEXTPTR(TEXT_SETNAME_START + (it->set % 100)), ao[PLAYER].setCount[itemEquipSlot[it->type]], *(ucPtr + 15));
			isT += 20;

			//��Ʈ �ɼ�
			for (i = 1; i < 7 && *(ucPtr + 1) < EMPTY; i++, ucPtr += 3) {
				sprintf(setStr[i], TEXTPTR(TEXT_PREFIX_DESC + *(ucPtr + 1)), *(ucPtr + 2));
				sprintf(setStr[i], "%s|k(%dp)", setStr[i], *ucPtr);
				isT += 13;
			}
		}
#endif
	}
}

void SetNetString(ITEM* it)
{
	memset(skillStr, 0, sizeof(skillStr));

	if (menuFocus >= 100)
		sprintf(skillStr, textId[TEXT_PRICE_GOLD], it->gold * GOLDRATIO);
}

void SetRecipeString(int type, int detail, int grade, int set)
{
	int tName;

	//제작아이템 이름 : recipeName
	memset(recipeName, 0, 30);
	tName = TEXT_ITEMNAME_START + GetItemName(type, detail, grade);

	switch (grade) {
	default:
		sprintf(recipeName, "|b%s %s", TEXTPTR(TEXT_NORMAL + grade), TEXTPTR(tName));
		recipeName[1] = itemColorText[grade];
		break;
#ifdef SETITEM
	case GRADE_SET:
		sprintf(recipeName, "|q%s:|i%s", TEXTPTR(TEXT_SETNAME_START + (set % 100)), TEXTPTR(tName));
		break;
#endif
	case GRADE_EPIC:
		sprintf(recipeName, "|g%s", TEXTPTR(tName));
		break;
	}

	//제작아이템 대미지 : recipeDmg
	memset(recipeDmg, 0, 20);

	//무기
	if (detail / 10 < ITEM_HELM)
		sprintf(recipeDmg, "|b%d - %d", RoundDiv(itemUpgradeValue[(detail / 10) * TOTAL_COLLECTIONS * (ITEMMAXLEVEL + 1) + (detail % 10) * TOTALGRADE * (ITEMMAXLEVEL + 1) + grade * (ITEMMAXLEVEL + 1)] * (100 - weaponRange[detail / 10]), 100), RoundDiv(itemUpgradeValue[(detail / 10) * TOTAL_COLLECTIONS * (ITEMMAXLEVEL + 1) + (detail % 10) * TOTALGRADE * (ITEMMAXLEVEL + 1) + grade * (ITEMMAXLEVEL + 1)] * (100 + weaponRange[detail / 10]), 100));
	else
		sprintf(recipeDmg, "%d", itemUpgradeValue[(detail / 10) * TOTAL_COLLECTIONS * (ITEMMAXLEVEL + 1) + itemLevelLimit[(detail % 10) * 2 + 1]]);
}

void SetMaterialString(unsigned char* ed, int type)
{
	if (type == 1)
		temp = GetItemName(ed[0], ed[1], GRADE_NORMAL);
	else
		temp = GetItemName(ed[3 * type - 4], ed[3 * type - 3], 0);

	memset(recipeName, 0, 40);
	memset(recipeDesc, 0, 80);
	sprintf(recipeName, "%s", TEXTPTR(TEXT_ITEMNAME_START + temp));
	sprintf(recipeDesc, "%s", TEXTPTR(TEXT_ITEMDESC_START + temp));
}

void SetSocketString(int idx, int type)
{
	ITEM* it = GetItemPtr(idx);

	memset(recipeDesc, 0, 80);

	//소켓에 장착된 보석 설명 셋팅
	if (it->socket[type] < EMPTYINT) {
		//���� �ɼ� ���� �ؽ�Ʈ ����
		memset(tempStr, 0, sizeof(tempStr));
		temp = TEXT_PREFIX_DESC + it->option[6 + type][0];
		sprintf(tempStr, TEXTPTR(temp), it->option[6 + type][1]);

		//���� �̸��� �ɼ� �ؽ�Ʈ�� ����
		temp = TEXT_ITEMNAME_GEM + it->socket[type] % 10;
		sprintf(recipeDesc, "|b%s|b:%s", TEXTPTR(temp), tempStr);
		recipeDesc[1] = itemColorText[it->socket[type] / 10];
	}
	else {
		//보석이 박혀있지 않다면
		sprintf(recipeDesc, "%s", TEXTPTR(TEXT_EMPTYSOCKET));
	}
}

void SetActiveSkillString(int index, char* str, unsigned short width, unsigned short height)
{
	const signed int* skPtr2 = &skillData[SKILLDATASIZE * index];
	int skillValue, i, skillLv, skillLv2;
	char* strPtr;
	int seconds = BUFFINITSECONDS;

	//문자열 합성

	skillLv = ao[raidPlayer].skillLv[index];
	skillLv2 = GetSkillLv(raidPlayer, index);
	skillValue = skillLv2 - 1;

	for (i = 0, strPtr = &str[0]; i < 2; i++, skillValue++, strPtr = &tempStr2[0]) {
		memset(strPtr, 0, 256);

		if (skillValue == MAXSKILLLV || (skillValue < 0 && index != SKILL_DIANA1 && index != SKILL_MAXX2))
			continue;

		//초기화
		memset(tempStr, 0, sizeof(tempStr));

		if (*skPtr2 == PASSIVE) {
			//패시브라면 : 기본적으로 능력치 하나만을 합성한다.
			if (skillValue < 0) {
				if (index == SKILL_DIANA1)
					temp = TEXT_GUN0;
				else
					temp = TEXT_BOOMERANG0;

				sprintf(strPtr, "%s", TEXTPTR(temp));
			}
			else {
				if (index == SKILL_ROBIN2)
					sprintf(strPtr, TEXTPTR(TEXT_SKILLDESC_COMMON_ROBIN1 + index), *(skPtr2 + 6 + skillValue), GetSkillLv(raidPlayer, index) == 0 ? 20 : GetSkillValue(raidPlayer, index + 1));
				else if (index == SKILL_MAXX2)
					sprintf(strPtr, TEXTPTR(TEXT_SKILLDESC_COMMON_ROBIN1 + index), *(skPtr2 + 6 + skillValue), skillLv2 / 2 + 1);
				else
					sprintf(strPtr, TEXTPTR(TEXT_SKILLDESC_COMMON_ROBIN1 + index), *(skPtr2 + 6 + skillValue));
			}
		}
		else {
			//액티브라면
			switch (index) {
			default:
				sprintf(strPtr, "%s %s |r%d%%|b%s %s%d%s", TEXTPTR(TEXT_SKILLDESC_COMMON_ROBIN1 + index), TEXTPTR(TEXT_SKILL_DEFAULTATK), (int)RoundDiv(skillDescMod[ao[raidPlayer].type * 8 + (index % 30) - SKILL_ROBIN6] * (100 + *(skPtr2 + 6 + skillValue)), 10), TEXTPTR(TEXT_SKILL_POWER), TEXTPTR(TEXT_SKILL_COOLTIME), (int)RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[raidPlayer].ps[PS_DELAY] : 0)), FPS * 100), TEXTPTR(TEXT_SKILL_SECONDS));
				break;
			case SKILL_ROBIN13:	//VIT가 |r%d%%|b만큼 증가한다. %s
			case SKILL_ROBIN14:	//�޴� �������� |i%d%%|b�� �ش��ϴ� MP�� �Ҹ��Ͽ� ���ظ� |r%d%%|b��ŭ ���ҽ�Ų��. %s
			case SKILL_ROBIN15:	//������ �ִ� �������� |r%d%%|b��ŭ ������ŵ�ϴ�. %s//ȸ�� ������ �ִ� HP�� |r%d%%|b��ŭ HP�� ȸ���Ѵ�. %s
			case SKILL_ROBIN16:	//최대 HP의 |i%d%%|b만큼 HP를 회복합니다. %s
			case SKILL_ROBIN17:	//���ظ� ���� �� ���� �������� |r%d%%|b�� ������ �ݻ��Ѵ�. %s
			case SKILL_DIANA14:	//방어력의 |r%d%%|b를 희생하면서 공격력을 |r%d%%|b만큼 증가시킨다. %s
			case SKILL_DIANA15:	//������ ���� �������� |i%d%%|b��ŭ MP�� ȸ���Ѵ�. %s
			case SKILL_DIANA16:	//크리티컬 성공률이 |r%d%%|b만큼 증가한다. %s
			case SKILL_MAXX14:	//������ ���� �������� |r%d%%|b��ŭ HP�� ȸ���Ѵ�. %s
			case SKILL_MAXX15:	//회피 성공률이 |r%d%%|b만큼 상승한다. %s
			case SKILL_MAXX17:	//기절 공격 성공률이 |r%d%%|b만큼 증가한다. %s
				memset(strPtr, 0, sizeof(strPtr));
#ifdef SKILL_MAXX14_TO_SKILL_MAXX1
				if (index == SKILL_MAXX14)
					seconds += *(skPtr2 + 6 + skillValue) / FPS;
#endif
				//|e%d%%�� |b���� %s
				switch (index) {
				case SKILL_ROBIN13:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s %s%d%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_ROBIN13_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_ROBIN13_SEP2), TEXTPTR(TEXT_SKILL_COOLTIME), (int)RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[raidPlayer].ps[PS_DELAY] : 0)), FPS * 100), TEXTPTR(TEXT_SKILL_SECONDS));
					break;
				case SKILL_ROBIN14:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s %s%d%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_ROBIN14_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_ROBIN14_SEP2), TEXTPTR(TEXT_SKILL_COOLTIME), (int)RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[raidPlayer].ps[PS_DELAY] : 0)), FPS * 100), TEXTPTR(TEXT_SKILL_SECONDS));
					break;
				case SKILL_ROBIN15:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s %s%d%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_ROBIN15_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_ROBIN15_SEP2), TEXTPTR(TEXT_SKILL_COOLTIME), (int)RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[raidPlayer].ps[PS_DELAY] : 0)), FPS * 100), TEXTPTR(TEXT_SKILL_SECONDS));
					break;
				case SKILL_ROBIN16:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s %s%d%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_ROBIN16_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_ROBIN16_SEP2), TEXTPTR(TEXT_SKILL_COOLTIME), (int)RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[raidPlayer].ps[PS_DELAY] : 0)), FPS * 100), TEXTPTR(TEXT_SKILL_SECONDS));
					break;
				case SKILL_ROBIN17:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s %s%d%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_ROBIN17_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_ROBIN17_SEP2), TEXTPTR(TEXT_SKILL_COOLTIME), (int)RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[raidPlayer].ps[PS_DELAY] : 0)), FPS * 100), TEXTPTR(TEXT_SKILL_SECONDS));
					break;

				case SKILL_DIANA14:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s %s%d%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_DIANA14_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_DIANA14_SEP2), TEXTPTR(TEXT_SKILL_COOLTIME), (int)RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[raidPlayer].ps[PS_DELAY] : 0)), FPS * 100), TEXTPTR(TEXT_SKILL_SECONDS));
					break;
				case SKILL_DIANA15:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s %s%d%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_DIANA15_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_DIANA15_SEP2), TEXTPTR(TEXT_SKILL_COOLTIME), (int)RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[raidPlayer].ps[PS_DELAY] : 0)), FPS * 100), TEXTPTR(TEXT_SKILL_SECONDS));
					break;
				case SKILL_DIANA16:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s %s%d%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_DIANA16_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_DIANA16_SEP2), TEXTPTR(TEXT_SKILL_COOLTIME), (int)RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[raidPlayer].ps[PS_DELAY] : 0)), FPS * 100), TEXTPTR(TEXT_SKILL_SECONDS));
					break;

				case SKILL_MAXX14:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s %s%d%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_MAXX14_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_MAXX14_SEP2), TEXTPTR(TEXT_SKILL_COOLTIME), (int)RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[raidPlayer].ps[PS_DELAY] : 0)), FPS * 100), TEXTPTR(TEXT_SKILL_SECONDS));
					break;
				case SKILL_MAXX15:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s %s%d%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_MAXX15_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_MAXX15_SEP2), TEXTPTR(TEXT_SKILL_COOLTIME), (int)RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[raidPlayer].ps[PS_DELAY] : 0)), FPS * 100), TEXTPTR(TEXT_SKILL_SECONDS));
					break;
				case SKILL_MAXX17:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s %s%d%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_MAXX17_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_MAXX17_SEP2), TEXTPTR(TEXT_SKILL_COOLTIME), (int)RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[raidPlayer].ps[PS_DELAY] : 0)), FPS * 100), TEXTPTR(TEXT_SKILL_SECONDS));
					break;
				}
				break;
			case SKILL_DIANA13:	//회복탄을 발사하여 최대 HP의 |r%d%%|b만큼 HP를 회복한다. %s
				sprintf(strPtr, "|e%s |r%d%%|b%s %s%d%s", TEXTPTR(TEXT_SKILL_DIANA13_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_DIANA13_SEP2), TEXTPTR(TEXT_SKILL_COOLTIME), (int)RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[raidPlayer].ps[PS_DELAY] : 0)), FPS * 100), TEXTPTR(TEXT_SKILL_SECONDS));
				break;
			case SKILL_DIANA17:	//적의 방어도를 |r%d%%|b만큼 무시하여 추가피해를 입힌다. %s
				seconds = ao[raidPlayer].buff[INC_IGNORE];
				sprintf(strPtr, "|e%d%s %s |b%s %s%d%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_DIANA17_SEP1), TEXTPTR(TEXT_SKILL_DIANA17_SEP2), TEXTPTR(TEXT_SKILL_COOLTIME), (int)RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[raidPlayer].ps[PS_DELAY] : 0)), FPS * 100), TEXTPTR(TEXT_SKILL_SECONDS));
				break;
			case SKILL_MAXX16:	//ȸ�� ������ |i%d|b��ŭ MP�� ȸ���Ѵ�. %s
				sprintf(strPtr, "|b%s %s%d%s", TEXTPTR(TEXT_SKILL_DIANA16_SEP1), TEXTPTR(TEXT_SKILL_COOLTIME), (int)RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[raidPlayer].ps[PS_DELAY] : 0)), FPS * 100), TEXTPTR(TEXT_SKILL_SECONDS));
				break;
			}
		}
	}

	memcpy(str, strPtr, sizeof(str));
	isT = (LineTextStr(str, 1000, 1000, width, -1, -1, 1.0f)) * 13 * _2X + height;
}

void SetActiveSkillBodyString(int index)
{
	const signed int* skPtr2 = &skillData[SKILLDATASIZE * index];
	int skillValue, i, skillLv, skillLv2;
	char* strPtr;
	int seconds = BUFFINITSECONDS;

	//문자열 합성

	skillLv = ao[raidPlayer].skillLv[index];
	skillLv2 = GetSkillLv(raidPlayer, index);
	skillValue = Max(-1, skillLv2 - 2);

	for (i = 0, strPtr = &skillBodyStr[0]; i < 2; i++, skillValue++, strPtr = &tempStr2[0]) {
		memset(strPtr, 0, 256);

		if (skillValue == MAXSKILLLV || (skillValue < 0 && index != SKILL_DIANA1 && index != SKILL_MAXX2))
			continue;

		//초기화
		memset(tempStr, 0, sizeof(tempStr));

		if (*skPtr2 == PASSIVE) {
			//패시브라면 : 기본적으로 능력치 하나만을 합성한다.
			if (skillValue < 0) {
				if (index == SKILL_DIANA1)
					temp = TEXT_GUN0;
				else
					temp = TEXT_BOOMERANG0;

				sprintf(strPtr, "%s", TEXTPTR(temp));
			}
			else {
				if (index == SKILL_ROBIN2)
					sprintf(strPtr, TEXTPTR(TEXT_SKILLEFFECTDESC_COMMON_ROBIN1 + index), *(skPtr2 + 6 + skillValue), GetSkillLv(PLAYER, index) == 0 ? 20 : GetSkillValue(PLAYER, index + 1));
				else if (index == SKILL_MAXX2)
					sprintf(strPtr, TEXTPTR(TEXT_SKILLEFFECTDESC_COMMON_ROBIN1 + index), *(skPtr2 + 6 + skillValue), skillLv2 / 2 + 1);
				else
					sprintf(strPtr, TEXTPTR(TEXT_SKILLEFFECTDESC_COMMON_ROBIN1 + index), *(skPtr2 + 6 + skillValue));
			}
		}
		else {
			//액티브라면
			switch (index) {
			default:
				//case SKILL_ROBIN6:		//�Ʒ��������� ���� ���� ����ø���?���? %s
				//case SKILL_ROBIN7:		//��ī�ο� ���� ����?���� �����Ѵ�. %s
				//case SKILL_ROBIN8:		//���η� ���� �ֵѷ� ������ ���� ���� ���ÿ� �����Ѵ�. %s
				//case SKILL_ROBIN9:		//몸통박치기로 적을 뒤로 날려버린다. %s
				//case SKILL_ROBIN10:	//Į������ ������ ���� ������Ų��. %s
				//case SKILL_ROBIN11:	//검을 회전시키며 찌르는 강력한 찌르기. %s
				//case SKILL_ROBIN12:	//������ ���Ӱ����� ���ϴ� ���ʻ��? %s
				//case SKILL_DIANA6:		//3방향으로 동시에 총을 발사한다. %s
				//case SKILL_DIANA7:		//������ ���� �ݻ�Ǵ�?�������� �߻��Ѵ�. %s
				//case SKILL_DIANA8:		//������ ȭ���� ����Ͽ�?���� ��Ÿ�Ѵ�. %s
				//case SKILL_DIANA9:		//���̳� ���� �����ϸ� �����ϴ� ����ź�� �߻��Ѵ�. %s
				//case SKILL_DIANA10:	//적을 추적하는 유도미사일을 발사한다. %s
				//case SKILL_DIANA11:	//총을 난사하여 주위의 적을 공격하는 초필살기. %s
				//case SKILL_DIANA12:	//적을 조준한 뒤 위성레이저가 발사된다. %s
				//case SKILL_MAXX7:		//���������?������ ���� �����ϸ�, �θ޶��� ��� �����?�����ϴ�. %s
				//case SKILL_MAXX8:		//사정거리가 짧고 관통력이 좋은 투척기술. %s
				//case SKILL_MAXX9:		//위쪽의 적을 공격하는 투척기술. %s
				//case SKILL_MAXX10:		//날아간 부메랑이 앞에서 머물며 회전한다. %s
				//case SKILL_MAXX11:		//�θ޶��� ���� �����?���� �����Ͽ� ������ �� ���ƿ´�. %s
				//case SKILL_MAXX12:		//던져진 부메랑이 주위의 적을 모두 공격하는 투척기술. %s
				//case SKILL_MAXX13:		//������ ������ �ְ��� ������ ���� �����ϴ� ���ʻ��? %s
				/*
				//공격스킬류
					//(���� ���ð�:|j%d��|b)
				//sprintf(strPtr, TEXTPTR(TEXT_SKILL_ETC2), RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[PLAYER].ps[PS_DELAY] : 0)), 1200));

				//MP를 |i%d%%|b만큼 소비한다. %s
				//sprintf(strPtr, TEXTPTR(TEXT_SKILL_ETC1), RoundDiv(*(skPtr2 + 1) * (100 + 20 * skillValue), 100), tempStr);
				//memset(tempStr, 0, sizeof(tempStr));

				//기본 공격력의 |r%d%%|b의 위력을 지니며, %s
				//sprintf(tempStr, TEXTPTR(TEXT_SKILL_ETC0), RoundDiv(skillDescMod[pObj->type * 8 + (index % 30) - SKILL_ROBIN6] * (100 + *(skPtr2 + 6 + skillValue)), 10), strPtr);
				sprintf(tempStr, TEXTPTR(TEXT_SKILLDESC_ETC0), RoundDiv(skillDescMod[ao[PLAYER].type * 8 + (index % 30) - SKILL_ROBIN6] * (100 + *(skPtr2 + 6 + skillValue)), 10));
				//sprintf(tempStr, "%s", strPtr);

				memset(strPtr, 0, sizeof(strPtr));

				//메인 설명
				sprintf(strPtr, TEXTPTR(TEXT_SKILLEFFECTDESC_COMMON_ROBIN1 + index), tempStr);
				*/
				sprintf(strPtr, "%s %s |r%d%%|b%s", TEXTPTR(TEXT_SKILLDESC_COMMON_ROBIN1 + index), TEXTPTR(TEXT_SKILL_DEFAULTATK), (int)RoundDiv(skillDescMod[ao[raidPlayer].type * 8 + (index % 30) - SKILL_ROBIN6] * (100 + *(skPtr2 + 6 + skillValue)), 10), TEXTPTR(TEXT_SKILL_POWER));
				break;
			case SKILL_ROBIN13:	//VIT가 |r%d%%|b만큼 증가한다. %s
			case SKILL_ROBIN14:	//�޴� �������� |i%d%%|b�� �ش��ϴ� MP�� �Ҹ��Ͽ� ���ظ� |r%d%%|b��ŭ ���ҽ�Ų��. %s
			case SKILL_ROBIN15:	//������ �ִ� �������� |r%d%%|b��ŭ ������ŵ�ϴ�. %s//ȸ�� ������ �ִ� HP�� |r%d%%|b��ŭ HP�� ȸ���Ѵ�. %s
			case SKILL_ROBIN16:	//최대 HP의 |i%d%%|b만큼 HP를 회복합니다. %s
			case SKILL_ROBIN17:	//���ظ� ���� �� ���� �������� |r%d%%|b�� ������ �ݻ��Ѵ�. %s
			case SKILL_DIANA14:	//방어력의 |r%d%%|b를 희생하면서 공격력을 |r%d%%|b만큼 증가시킨다. %s
			case SKILL_DIANA15:	//������ ���� �������� |i%d%%|b��ŭ MP�� ȸ���Ѵ�. %s
			case SKILL_DIANA16:	//크리티컬 성공률이 |r%d%%|b만큼 증가한다. %s
			case SKILL_MAXX14:	//������ ���� �������� |r%d%%|b��ŭ HP�� ȸ���Ѵ�. %s
			case SKILL_MAXX15:	//회피 성공률이 |r%d%%|b만큼 상승한다. %s
			case SKILL_MAXX17:	//기절 공격 성공률이 |r%d%%|b만큼 증가한다. %s
				/*
								//(���� ���ð�:|j%d��|b)
				//sprintf(strPtr, TEXTPTR(TEXT_SKILL_ETC2), RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[PLAYER].ps[PS_DELAY] : 0)), 1200));

				//MP를 |i%d%%|b만큼 소비한다. %s
				//sprintf(strPtr, TEXTPTR(TEXT_SKILL_ETC1), RoundDiv(*(skPtr2 + 1) * (100 + 20 * skillValue), 100), tempStr);
				//memset(tempStr, 0, sizeof(tempStr));

				//메인 설명
				//if (index == SKILL_ROBIN14)
				//	sprintf(tempStr, TEXTPTR(TEXT_SKILLEFFECTDESC_COMMON_ROBIN1 + index), barrierEtcData[skillValue], *(skPtr2 + 6 + skillValue), strPtr);
				//else if (index == SKILL_DIANA14)
				//	sprintf(tempStr, TEXTPTR(TEXT_SKILLEFFECTDESC_COMMON_ROBIN1 + index), berserkEtcData[skillValue], *(skPtr2 + 6 + skillValue), strPtr);
				//else
					sprintf(tempStr, TEXTPTR(TEXT_SKILLEFFECTDESC_COMMON_ROBIN1 + index), *(skPtr2 + 6 + skillValue), strPtr);

				memset(strPtr, 0, sizeof(strPtr));

				//|e%d%%�� |b���� %s
				sprintf(strPtr, TEXTPTR(TEXT_SKILL_ETC3), 30, tempStr);
				*/
				memset(strPtr, 0, sizeof(strPtr));
#ifdef SKILL_MAXX14_TO_SKILL_MAXX1
				if (index == SKILL_MAXX14)
					seconds += *(skPtr2 + 6 + skillValue) / FPS;
#endif
				//|e%d%%�� |b���� %s
				switch (index) {
				case SKILL_ROBIN13:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_ROBIN13_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_ROBIN13_SEP2));
					break;
				case SKILL_ROBIN14:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_ROBIN14_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_ROBIN14_SEP2));
					break;
				case SKILL_ROBIN15:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_ROBIN15_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_ROBIN15_SEP2));
					break;
				case SKILL_ROBIN16:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_ROBIN16_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_ROBIN16_SEP2));
					break;
				case SKILL_ROBIN17:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_ROBIN17_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_ROBIN17_SEP2));
					break;

				case SKILL_DIANA14:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_DIANA14_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_DIANA14_SEP2));
					break;
				case SKILL_DIANA15:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_DIANA15_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_DIANA15_SEP2));
					break;
				case SKILL_DIANA16:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_DIANA16_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_DIANA16_SEP2));
					break;

				case SKILL_MAXX14:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_MAXX14_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_MAXX14_SEP2));
					break;
				case SKILL_MAXX15:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_MAXX15_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_MAXX15_SEP2));
					break;
				case SKILL_MAXX17:
					sprintf(strPtr, "|e%d%s %s |r%d%%|b%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_MAXX17_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_MAXX17_SEP2));
					break;
				}
				break;
			case SKILL_DIANA13:	//회복탄을 발사하여 최대 HP의 |r%d%%|b만큼 HP를 회복한다. %s
				/*
				//(���� ���ð�:|j%d��|b)
				//sprintf(tempStr, TEXTPTR(TEXT_SKILL_ETC2), RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[PLAYER].ps[PS_DELAY] : 0)), 1200));

				//MP를 |i%d%%|b만큼 소비한다. %s
				//sprintf(tempStr, TEXTPTR(TEXT_SKILL_ETC1), RoundDiv(*(skPtr2 + 1) * (100 + 20 * skillValue), 100), strPtr);
				memset(strPtr, 0, sizeof(strPtr));

				//메인 설명
				sprintf(strPtr, TEXTPTR(TEXT_SKILLEFFECTDESC_COMMON_ROBIN1 + index), *(skPtr2 + 6 + skillValue), tempStr);
				*/
				sprintf(strPtr, "|e%s |r%d%%|b%s", TEXTPTR(TEXT_SKILL_DIANA13_SEP1), (int)*(skPtr2 + 6 + skillValue), TEXTPTR(TEXT_SKILL_DIANA13_SEP2));

				break;
			case SKILL_DIANA17:	//적의 방어도를 |r%d%%|b만큼 무시하여 추가피해를 입힌다. %s
				/*
				//공격스킬류
				//(���� ���ð�:|j%d��|b)
				sprintf(tempStr, TEXTPTR(TEXT_SKILL_ETC2), RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[raidPlayer].ps[PS_DELAY] : 0)), FPS * 100));

				//메인 설명
				sprintf(strPtr, TEXTPTR(TEXT_SKILLDESC_COMMON_ROBIN1 + index), 10 + *(skPtr2 + 6 + skillValue) / FPS, tempStr);
				*/
				seconds = ao[raidPlayer].buff[INC_IGNORE];
				sprintf(strPtr, "|e%d%s %s |b%s", (int)seconds, TEXTPTR(TEXT_SKILL_SECONDS_WHILE), TEXTPTR(TEXT_SKILL_DIANA17_SEP1), TEXTPTR(TEXT_SKILL_DIANA17_SEP2));
				break;
			case SKILL_MAXX16:	//ȸ�� ������ |i%d|b��ŭ MP�� ȸ���Ѵ�. %s
				/*
				//공격스킬류
				//(���� ���ð�:|j%d��|b)
				sprintf(tempStr, TEXTPTR(TEXT_SKILL_ETC2), RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[raidPlayer].ps[PS_DELAY] : 0)), FPS * 100) + (*(skPtr2 + 6 + skillValue) / FPS));

				//메인 설명
				sprintf(strPtr, TEXTPTR(TEXT_SKILLDESC_COMMON_ROBIN1 + index), tempStr);
				*/
				sprintf(strPtr, "|b%s %s%d%s", TEXTPTR(TEXT_SKILL_DIANA16_SEP1), TEXTPTR(TEXT_SKILL_COOLTIME), (int)RoundDiv(*(skPtr2 + 2) * (100 - (drawHandle == MD_GAMEMENU ? ao[raidPlayer].ps[PS_DELAY] : 0)), FPS * 100), TEXTPTR(TEXT_SKILL_SECONDS));
				break;
			}
		}
	}

	memcpy(skillBodyStr, strPtr, sizeof(skillBodyStr));
	isT = (LineTextStr(skillBodyStr, 1000, 1000, 144 * _2X - 8 * _2X - 2 * _2X, -1, -1, 1.0f)) * 13 * _2X + 24 * _2X + 8 * _2X;
}

void SetNpcEquip(ITEM* it)
{
	int i;
	int equipItem = itemEquipSlot[it->type];

	for (i = 1; i < 3; i++) {
		//memcpy(optionStr[11], equipImg, TOTALEQUIP);

		//if (ao[i].equipImg[equipItem])
		//	ao[i].equipImg[equipItem] = ((ao[i].equipImg[equipItem] - 1) % 8 + ao[PLAYER + i].type * 8) + 1;
		//else
		//	ao[i].equipImg[equipItem] = 0;
		if (ao[i].equip[equipItem].type != EMPTY)
			ao[i].equipImg[equipItem] = it->detail + 1;
		else
			ao[i].equipImg[equipItem] = 0;

		//LoadImg(ROBIN_PART_IMG + ao[PLAYER + i].type * ROBIN_IMG_CNT + equipItem);
		//memcpy(equipImg, optionStr[11], TOTALEQUIP);
	}
}

void SetNpcEquipDetail(int npc, int slot, int itemType, int itemDetail, int itemGrade)
{
	ao[npc].equip[slot].type = itemType;
	ao[npc].equip[slot].detail = itemDetail;
	ao[npc].equip[slot].grade = itemGrade;
	ao[npc].equipImg[slot] = itemDetail + 1;

}

void ResurrectionEffect(OBJECT* pObj)
{
	if (pObj->moveHandler == CUTOFFMOVE)
		return;

	pObj->levelUpFrame = 1;
	pObj->invincible = FPS;
	pObj->hp = pObj->ps[PS_HP];
	pObj->mp = pObj->ps[PS_MP];
	memset(pObj->debuf, 0, sizeof(pObj->debuf));
	pObj->dead = false;
	pObj->O2 = OXYGEN;
}

void StoneRecipe(ITEM* it)
{
	int i;
	int idx = GetInvenIdx(it->type, it->detail, it->grade);

	//조합석을 줄여준다.
	i = GetInvenIdx(ITEM_NETITEM, ITEM_NET_RECIPE, GRADE_NORMAL);

	if (robin.inven[i].count > 1)
		robin.inven[i].count--;
	else {
		if (i < GetInvenIdx(it->type, it->detail, it->grade))
			idx--;

		EraseItem(&robin.inven[i]);
	}

	//조합처리
	memcpy(&tempItem, &robin.inven[idx], sizeof(ITEM));
	MakeItem(&robin.inven[idx], tempItem.detail >> 3, tempItem.lv, tempItem.grade + 1, tempItem.detail & 0x07, tempItem.set + 1);

	//�ش� �������� ����ش�?
	SetItemString(it, 0, 0);
	menuItem = idx;

	//저장한다.
	//SaveFlag(0);

	menuDepth = ((menuFocus < 100 && stoneWhere == 1)) ? 1 : 2;
}

void StoneResolution(int idx)
{
	int i, count;
	ITEM* it = GetItemPtr(idx);

	//분해처리
	for (i = 0, count = 0; i < 6; i++) {
		if (it->socket[i] != EMPTYINT)
			count++;
	}

	i = GetItemCount(ITEM_NETITEM, ITEM_NET_RESOLUTION, GRADE_NORMAL);

	//�κ��丮�� ���� ������ŭ�� �������?�ִٸ�
	if (count == 0) {
		menuDepth = 19;
		//menuResult = TEXT_NOGEM_SOCKET;
		return;
	}
	else if (robin.count + count <= robin.maxInven || (robin.count + count - 1 == robin.maxInven && i == 1)) {
		//분해석을 하나 소비한다.
		count = GetInvenIdx(ITEM_NETITEM, ITEM_NET_RESOLUTION, GRADE_NORMAL);

		if (i == 1) {
			EraseItem(&robin.inven[count]);

			if (idx < ITEMPTR_EQUIP && count < idx) {
				idx -= 1;
				it = GetItemPtr(idx);
			}
		}
		else
			robin.inven[count].count--;

		//소켓을 검사한다.
		for (i = 0; i < 6; i++) {
			//보석이 장착되어 있다면
			if (it->socket[i] != EMPTYINT) {
				//������ �κ��丮�� �ִ´�.
				MakeItem(&tempItem, ITEM_GEM, 1, it->socket[i] / 10, it->socket[i] % 10, 0);
				tempItem.option[0][0] = it->option[i + 6][0];
				tempItem.option[0][1] = it->option[i + 6][1];
				memcpy(&robin.inven[robin.count], &tempItem, sizeof(ITEM));
				robin.count++;

				//�����?����ĭ�� ����ش�?
				it->socket[i] = EMPTYINT;
				it->option[i + 6][0] = EMPTYINT;
				it->option[i + 6][1] = 0;
			}
		}

		//���¸� �����Ѵ�.
		RefreshStat(&ao[PLAYER]);

		//�ش� �������� ����ش�?
		SetItemString(it, 0, 0);
		menuItem = idx;

		//저장한다.
		//SaveFlag(0);

		menuDepth = ((menuFocus < 100 && stoneWhere == 1)) ? 1 : 2;
	}
	else {
		//menuResult = TEXT_INVENTORY_LACK;
		return;
	}
}

void StoneSocket(int idx)
{
	int i, count;
	ITEM* it = GetItemPtr(idx);

	//소켓을 다시 뚫어준다.
	it->count = 2 + Proc(proc4, 4);

	//�����?����ĭ�� ����ش�?
	for (i = 0; i < 6; i++) {
		it->socket[i] = EMPTYINT;
		it->option[i + 6][0] = EMPTYINT;
		it->option[i + 6][1] = 0;
	}

	//소켓석을 하나 소비한다.
	count = GetInvenIdx(ITEM_NETITEM, ITEM_NET_SOCKET, GRADE_NORMAL);

	if (robin.inven[count].count == 1) {
		EraseItem(&robin.inven[count]);

		if (idx < ITEMPTR_EQUIP && count < idx) {
			idx -= 1;
			it = GetItemPtr(idx);
		}
	}
	else
		robin.inven[count].count--;

	//���¸� �����Ѵ�.
	RefreshStat(&ao[PLAYER]);

	//�ش� �������� ����ش�?
	SetItemString(&robin.inven[idx], 0, 0);
	menuItem = idx;

	//저장한다.
	//SaveFlag(0);

	menuDepth = ((menuFocus < 100 && stoneWhere == 1)) ? 1 : 2;
}