#pragma once
#include "Core.h"
#include "Func.h"
#include "Text.h"
#include "Data.h"

static float GachaClamp01(float value)
{
	if (value < 0.0f)
		return 0.0f;

	if (value > 1.0f)
		return 1.0f;

	return value;
}

static float GachaEaseOutCubic(float value)
{
	value = GachaClamp01(value);

	float inverse =
		1.0f - value;

	return 1.0f -
		inverse *
		inverse *
		inverse;
}

static float GachaEaseInOutCubic(float value)
{
	value = GachaClamp01(value);

	if (value < 0.5f)
	{
		return
			4.0f *
			value *
			value *
			value;
	}

	float inverse =
		-2.0f *
		value +
		2.0f;

	return
		1.0f -
		inverse *
		inverse *
		inverse /
		2.0f;
}

static float GachaLerp(
	float start,
	float end,
	float progress)
{
	return
		start +
		(end - start) *
		progress;
}

int GetRewardBoxIndex(int boxDetail)
{
	switch (boxDetail)
	{
	case BOX_REWARD0:		return 0;
	case BOX_REWARD1:		return 1;
	case BOX_REWARD2:		return 2;
	case BOX_REWARD3:		return 3;
	case BOX_REWARD4:		return 4;
	case BOX_REWARD5:		return 5;
	case BOX_REWARD6:		return 6;
	case BOX_REWARD7:		return 7;
	case BOX_PAID0:			return 2;
	case BOX_PAID1:			return 3;
	case BOX_PAID2:			return 4;
	case BOX_PAID3:			return 5;
	case BOX_PAID4:			return 6;
	case BOX_PAID5:			return 7;
	}

	return -1;
}

int BoxRandomRange(int minValue, int maxValue)
{
	if (maxValue <= minValue)
		return minValue;

	return minValue +
		Random(maxValue - minValue + 1);
}

int RollBoxGrade(
	const int gradeRate[BOX_GRADE_COUNT],
	int* highGradeMissCount)
{
	int weight[BOX_GRADE_COUNT];

	for (int i = 0;
		i < BOX_GRADE_COUNT;
		i++)
	{
		weight[i] =
			gradeRate[i];
	}

	//----------------------------------------------------
	// 30번 연속으로 5성 이상이 나오지 않은 경우
	//----------------------------------------------------
	if (*highGradeMissCount >= 30)
	{
		int pityBonus =
			*highGradeMissCount - 29;

		//------------------------------------------------
		// 5성 가중치만 증가
		//------------------------------------------------
		weight[4] += pityBonus;
	}

	int totalWeight = 0;

	for (int i = 0;
		i < BOX_GRADE_COUNT;
		i++)
	{
		totalWeight +=
			weight[i];
	}

	if (totalWeight <= 0)
		return GRADE_NORMAL;

	int randomValue =
		Random(totalWeight);

	int selectedGrade =
		0;

	for (int i = 0;
		i < BOX_GRADE_COUNT;
		i++)
	{
		if (randomValue <
			weight[i])
		{
			selectedGrade =
				i;

			break;
		}

		randomValue -=
			weight[i];
	}

	//----------------------------------------------------
	// 5성 이상이면 천장 초기화
	//----------------------------------------------------
	if (selectedGrade >= 4)
	{
		*highGradeMissCount =
			0;
	}
	else
	{
		(*highGradeMissCount)++;
	}

	//----------------------------------------------------
	// GRADE_NORMAL이 0이고 등급이 연속이라는 전제
	//----------------------------------------------------
	return GRADE_NORMAL +
		selectedGrade;
}

bool IsDuplicateBoxCard(
	int cardCount,
	int type,
	int detail)
{
	for (int i = 0; i < cardCount; i++)
	{
		if (boxCardItem[0][i].type == type &&
			boxCardItem[0][i].detail == detail)
		{
			return true;
		}
	}

	return false;
}

int MakeBoxEquipType()
{
	static const int equipType[6] =
	{
		ITEM_SWORD,
		ITEM_HELM,
		ITEM_ARMOR,
		ITEM_GUNTLET,
		ITEM_KILT,
		ITEM_GREAVES
	};

	return equipType[
		Random(6)];
}
//--------------------------------------------------------
// 지정한 별 개수에 해당하는 detail 중 무작위 선택
//
// detailCount는 해당 itemType의 전체 종류 개수
//--------------------------------------------------------
static int GetRandomBoxDetailByStar(
	int itemType,
	int itemGrade,
	int targetStar,
	int detailCount)
{
	if (detailCount <= 0)
	{
		return -1;
	}

	//----------------------------------------------------
	// detail 개수가 지나치게 커질 가능성이 없다면
	// 프로젝트 최대 종류 수에 맞춰 고정 배열 사용
	//----------------------------------------------------
	int candidate[256];

	int candidateCount =
		0;

	for (int detailType = 0;
		detailType < detailCount;
		detailType++)
	{
		int star =
			GetItemStar(
				itemType,
				detailType,
				itemGrade);

		if (star != targetStar)
		{
			continue;
		}

		if (candidateCount >= 256)
		{
			break;
		}

		candidate[
			candidateCount] =
			detailType;

			candidateCount++;
	}

	if (candidateCount <= 0)
	{
		CCLOG(
			"GetRandomBoxDetailByStar FAILED: "
			"type=%d grade=%d star=%d count=%d",
			itemType,
			itemGrade,
			targetStar,
			detailCount);

		return -1;
	}

	return candidate[
		Random(candidateCount)];
}

//--------------------------------------------------------
// 상자에서 나올 수 있는 detail 개수
//
// "그 종류가 몇 개인가" 가 아니라 "상자가 어디까지 낼 수
// 있는가" 다. 둘이 다른 것이 검이다.
//
// 검은 35 자루인데 상자에서는 24 자루(0~23, 홀리소드와
// 다크소드까지)만 나온다. 그 위 열한 자루는 나중에 특별한
// 방법으로 얻게 할 것들이라, 상자에서 미리 나오면 그 방법이
// 생겼을 때 줄 것이 없다.
//
// 경계를 별과 겹쳐 두었다. 레오소드의 별을 5 에서 6 으로
// 올렸으므로(Data/ItemData.cpp) 상자 풀은 정확히 1~5 성이고
// 6 성 검은 하나도 없다. 그래서 규칙이 "상자는 5 성까지" 한
// 줄로 끝난다 - 자루 번호를 외울 필요가 없다.
//
// 6 성 장비를 뽑았는데 부위가 검으로 걸리면 낼 것이 없다.
// 그 처리는 MakeBoxEquipReward 가 한다.
//--------------------------------------------------------
static int GetBoxDetailCount(
	int itemType)
{
	switch (itemType)
	{
	case ITEM_CREW:
		return gTotalCrew;

	case ITEM_SWORD:
		return Min(TOTAL_SWORD, EQUIP_BOX_SWORD_MAX);

	case ITEM_HELM:
		return TOTAL_HELM;

	case ITEM_ARMOR:
		return TOTAL_ARMOR;

	case ITEM_GUNTLET:
		return TOTAL_GUNTLET;

	case ITEM_KILT:
		return TOTAL_KILT;

	case ITEM_GREAVES:
		return TOTAL_GREAVES;
	}

	return 0;
}

//상자에서 절대 안 나오는 장비인가.
//
//지금은 6 성 검 열한 자루(레오소드~왕의 검)가 여기 걸린다. 나중에
//특별한 방법으로 얻게 할 것들이라 상자 풀에서 빼 두었다.
//
//번호가 아니라 별로 묻는다. GetBoxDetailCount 가 개수로 자르는 것과
//같은 경계를 보되(레오소드부터 6 성), 목록 쪽은 카드 하나만 들고
//있으면 되므로 별이 더 편하다. 검을 더 그려 넣어도 별만 6 으로 주면
//상자에서 빠지는 것과 자물쇠가 붙는 것이 같이 따라온다.
//
//장비 목록에서 자물쇠를 붙일지 정하는 데 쓴다(Func_Menu.cpp).
bool IsBoxLockedItem(
	int itemType,
	int itemDetail,
	int itemGrade)
{
	if (itemType != ITEM_SWORD)
		return false;

	return GetItemStar(itemType, itemDetail, itemGrade) >
		EQUIP_BOX_SWORD_STAR_MAX;
}

void MakeBoxCrewReward(
	int cardIndex,
	int boxIndex)
{
	const REWARD_BOX_DATA* boxData =
		&rewardBoxData[
			boxIndex];

	//----------------------------------------------------
	// 해당 카드 슬롯 초기화
	//----------------------------------------------------
	memset(
		&boxCardItem[0][
			cardIndex],
			0,
			sizeof(ITEM));

	//----------------------------------------------------
	// 상자 확률을 이용한 카드 등급 선택
	//----------------------------------------------------
	int grade =
		RollBoxGrade(
			boxData->
			crewGradeRate,
			&robin.
			crewHighGradeMissCount);

	//----------------------------------------------------
	// [수정]
	// RollBoxGrade가 0~5를 반환한다는 전제로
	// 실제 별 개수는 1~6으로 변환
	//----------------------------------------------------
	int targetStar =
		grade + 1;

	int detail =
		-1;

	int retryCount =
		0;

	int detailCount =
		GetBoxDetailCount(
			ITEM_CREW);

	do
	{
		//------------------------------------------------
		// [수정]
		// MakeItemDetail을 사용하지 않고,
		// 해당 별의 모든 동료 중 하나를 선택
		//------------------------------------------------
		detail =
			GetRandomBoxDetailByStar(
				ITEM_CREW,
				grade,
				targetStar,
				detailCount);

		if (detail < 0)
		{
			break;
		}

		retryCount++;

	} while (
		IsDuplicateBoxCard(
			cardIndex,
			ITEM_CREW,
			detail) &&
		retryCount < 100);

	//----------------------------------------------------
	// 해당 등급 후보가 전혀 없는 경우 방어
	//----------------------------------------------------
	if (detail < 0)
	{
		CCLOG(
			"MakeBoxCrewReward FAILED: "
			"grade=%d star=%d",
			grade,
			targetStar);

		//------------------------------------------------
		// 최종 방어용 기존 선택
		//------------------------------------------------
		detail =
			MakeItemDetail(
				ITEM_CREW,
				robin.lv +
				boxIndex);
	}

	ITEM* item =
		&boxCardItem[0][
			cardIndex];

	item->type =
		ITEM_CREW;

	//----------------------------------------------------
	// 실제 캐릭터 종류
	//----------------------------------------------------
	item->detail =
		detail;

	item->grade =
		grade;

	item->count =
		1;

	item->lv =
		1;

	item->cooldown =
		0;

	//----------------------------------------------------
	// 신규 여부 저장
	//----------------------------------------------------
	item->seen =
		GetInvenIdx(
			item->type,
			item->detail,
			item->grade) >= 0;
}

void MakeBoxEquipReward(
	int cardIndex,
	int boxIndex)
{
	const REWARD_BOX_DATA* boxData =
		&rewardBoxData[
			boxIndex];

	memset(
		&boxCardItem[0][
			cardIndex],
			0,
			sizeof(ITEM));

	//----------------------------------------------------
	// 장비 카드 등급 선택
	//----------------------------------------------------
	int grade =
		RollBoxGrade(
			boxData->
			equipGradeRate,
			&robin.
			equipHighGradeMissCount);

	//----------------------------------------------------
	// [수정]
	// grade가 0~5라면 실제 별은 1~6
	//----------------------------------------------------
	int targetStar =
		grade + 1;

	int type =
		ITEM_SWORD;

	int detail =
		-1;

	int retryCount =
		0;

	do
	{
		//------------------------------------------------
		// 장비 카테고리 선택
		//------------------------------------------------
		type =
			MakeBoxEquipType();

		//------------------------------------------------
		// 6 성에는 검이 없다.
		//
		// 상자 풀이 1~5 성까지라(EQUIP_BOX_SWORD_MAX) 6 성
		// 검이 하나도 없다. 그냥 두면 아래에서 detail 이
		// -1 로 나와 백 번을 다시 뽑다가 다른 부위로 흘러
		// 간다. 결과는 같지만 왜 그런지가 코드에 안 적혀
		// 있어서, 나중에 보면 우연히 도는 것처럼 보인다.
		//
		// 여기서 미리 갈라 둔다. 검이 걸리면 다시 뽑는다.
		//------------------------------------------------
		if (type == ITEM_SWORD &&
			targetStar > EQUIP_BOX_SWORD_STAR_MAX)
		{
			retryCount++;
			continue;
		}

		int detailCount =
			GetBoxDetailCount(
				type);

		//------------------------------------------------
		// [수정]
		// 선택된 장비 타입 안에서
		// 해당 별의 detail을 무작위 선택
		//------------------------------------------------
		detail =
			GetRandomBoxDetailByStar(
				type,
				grade,
				targetStar,
				detailCount);

		retryCount++;

		//------------------------------------------------
		// 선택된 장비 타입에 해당 별 장비가 없으면
		// 다른 장비 타입을 다시 선택
		//------------------------------------------------
		if (detail < 0)
		{
			continue;
		}

		if (IsDuplicateBoxCard(
			cardIndex,
			type,
			detail) ==
			false)
		{
			break;
		}

	} while (
		retryCount < 100);

	//----------------------------------------------------
	// 선택 실패 방어
	//----------------------------------------------------
	if (detail < 0)
	{
		CCLOG(
			"MakeBoxEquipReward FAILED: "
			"grade=%d star=%d",
			grade,
			targetStar);

		type =
			MakeBoxEquipType();

		detail =
			MakeItemDetail(
				type,
				robin.lv +
				boxIndex);
	}

	ITEM* item =
		&boxCardItem[0][
			cardIndex];

	item->type =
		type;

	//----------------------------------------------------
	// 실제 무기 또는 장비 종류
	//----------------------------------------------------
	item->detail =
		detail;

	item->grade =
		grade;

	item->count =
		1;

	item->lv =
		1;

	item->cooldown =
		0;

	item->seen =
		GetInvenIdx(
			item->type,
			item->detail,
			item->grade) >= 0;
}

void MakeBoxHeartReward(
	int writeIndex,
	const REWARD_BOX_DATA* boxData,
	bool lucky)
{
	ITEM* item =
		&boxCardItem[0][
			writeIndex];

	memset(
		item,
		0,
		sizeof(ITEM));

	item->type =
		ITEM_HEART;

	item->detail =
		0;

	item->grade =
		GRADE_NORMAL;

	//----------------------------------------------------
	// 하트는 "얼마를 주는가"가 아니라 "어디까지 채우는가"다.
	//
	// 하트는 공격 횟수라서(ONEHEARTONEATTACK) 잡몹 하나를 잡는 데 한 뭉치가
	// 나간다. 상자가 딱 그만큼만 돌려주면 영원히 제자리라 아무것도 쌓이지
	// 않고, 고정 수량으로 주면 맥스치(GetInitHeart())가 레벨을 따라 오르는
	// 후반에 상자가 무의미해진다. 그래서 맥스치의 몇 % 까지 채울지로 적는다.
	//
	// 잡몹 상자는 꽉 채우고 조금 남기고(HEART_REFILL_PCT), 보스를 잡은
	// 상자는 맥스의 두 배까지 얹어준다(HEART_REFILL_BOSS_PCT). 그 넘친 몫이
	// 쌓여서 대보스(잡몹 체력 100배) 앞에서 한 번에 쓰인다.
	//
	// robin.waveIdx 는 상자를 다 열고 나서야 오르므로(Func_Gacha.cpp의
	// OutOfGacha 부근) 여기서는 방금 잡은 웨이브를 그대로 가리킨다.
	{
		int maxHeart =
			GetInitHeart();

		int targetPct =
			GetWaveKind(robin.waveIdx) >= MONSTERTYPE_BOSS ?
			HEART_REFILL_BOSS_PCT :
			HEART_REFILL_PCT;

		//럭키 상자는 한 걸음 더 채운다. 카드 추가/승급만으로는 하트가 손해다.
		if (lucky)
			targetPct += HEART_REFILL_PCT - 100;

		long long target =
			(long long)maxHeart * targetPct / 100;

		long long amount =
			target - robin.heart;

		//이미 목표보다 많이 들고 있어도 빈 카드를 낼 수는 없다.
		//상자 표가 정한 최소치는 언제나 준다.
		if (amount < boxData->heartMin)
			amount = boxData->heartMin;

		amount = Max(10LL, ((amount + 9) / 10) * 10);

		item->count =
			(int)amount;
	}

	item->seen =
		true;
}

void MakeBoxGoldReward(
	int writeIndex,
	const REWARD_BOX_DATA* boxData,
	bool lucky)
{
	ITEM* item =
		&boxCardItem[0][
			writeIndex];

	memset(
		item,
		0,
		sizeof(ITEM));

	item->type =
		ITEM_GOLD;

	item->detail =
		0;

	item->grade =
		GRADE_NORMAL;

	item->count =
		GetWeightedNormalizedReward(
			boxData->goldMin,
			boxData->goldMax);

	item->count = Max(100, ((item->count + 99) / 100) * 100);

	if (lucky)
	{
		// 현재 럭키 효과를 카드 추가와 승급으로만 쓸 경우
		// 별도 수량 보너스는 주지 않는다.
	}

	item->seen =
		true;
}

void UpgradeLuckyBoxCard(
	int cardCount)
{
	int candidate[
		GACHA_MAX_REWARD_CARD];

	int candidateCount = 0;

	for (int i = 0;
		i < cardCount;
		i++)
	{
		int type =
			boxCardItem[0][i].type;

		if (type == ITEM_CREW ||
			type == ITEM_SWORD ||
			type == ITEM_HELM ||
			type == ITEM_ARMOR ||
			type == ITEM_GUNTLET ||
			type == ITEM_KILT ||
			type == ITEM_GREAVES)
		{
			//------------------------------------------------
			// 이미 6성이면 승급 대상에서 제외
			//------------------------------------------------
			if (boxCardItem[0][i].grade <
				GRADE_NORMAL + 5)
			{
				candidate[candidateCount] =
					i;

				candidateCount++;
			}
		}
	}

	if (candidateCount <= 0)
		return;

	int selectedIndex =
		candidate[
			Random(candidateCount)];

	boxCardItem[0][selectedIndex].grade++;

	if (boxCardItem[0][selectedIndex].grade >=
		GRADE_NORMAL + 4)
	{
		if (boxCardItem[0][selectedIndex].type ==
			ITEM_CREW)
		{
			robin.crewHighGradeMissCount =
				0;
		}
		else
		{
			robin.equipHighGradeMissCount =
				0;
		}
	}
}

//카드를 깔 순서를 잡는다. 하트 -> 골드 -> 동료 -> 장비.
//
//[왜 섞지 않는가]
//전에는 무작위로 섞었다. 그러면 첫 장에 5성 장비가 나오고 마지막 장이
//하트인 상자가 나온다. 그 상자는 첫 장에서 끝나 버리고 나머지는 치우는
//작업이 된다. 순서를 고정하면 재화 -> 동료 -> 장비로 값이 올라가면서
//끝까지 간다.
//
//[같은 무리 안에서는 약한 것부터]
//동료끼리, 장비끼리는 등급이 낮은 것부터 깐다. 뒤로 갈수록 좋아지므로
//마지막 한 장을 남겨둔 순간이 그 상자에서 가장 기대되는 자리가 된다.
//같은 등급이면 원래 뽑힌 차례를 지킨다(안정 정렬).
int GetBoxRewardOrder(
	const ITEM* item)
{
	switch (item->type)
	{
	case ITEM_HEART:	return 0;
	case ITEM_GOLD:		return 1;
	case ITEM_CREW:		return 2;
	}

	return 3;
}

void OrderBoxReward(
	int cardCount)
{
	//카드는 GACHA_MAX_REWARD_CARD 장뿐이라 삽입 정렬이면 충분하고,
	//삽입 정렬은 그 자체로 안정 정렬이다.
	for (int i = 1;
		i < cardCount;
		i++)
	{
		ITEM key;

		memcpy(
			&key,
			&boxCardItem[0][i],
			sizeof(ITEM));

		int keyOrder =
			GetBoxRewardOrder(
				&key);

		int j = i - 1;

		while (j >= 0)
		{
			int order =
				GetBoxRewardOrder(
					&boxCardItem[0][j]);

			//무리가 앞서면 그대로 두고, 같은 무리면 등급으로 가른다.
			if (order < keyOrder)
				break;

			if (order == keyOrder &&
				boxCardItem[0][j].grade <=
				key.grade)
			{
				break;
			}

			memcpy(
				&boxCardItem[0][j + 1],
				&boxCardItem[0][j],
				sizeof(ITEM));

			j--;
		}

		memcpy(
			&boxCardItem[0][j + 1],
			&key,
			sizeof(ITEM));
	}
}

void CheckNewBoxReward(
	int cardCount)
{
	for (int i = 0;
		i < cardCount;
		i++)
	{
		int type =
			boxCardItem[0][i].type;

		//------------------------------------------------
		// 재화는 신규 아이템이 아님
		//------------------------------------------------
		if (type == ITEM_HEART ||
			type == ITEM_GOLD)
		{
			boxCardItem[0][i].seen =
				true;

			continue;
		}

		if (GetInvenIdx(
			boxCardItem[0][i].type,
			boxCardItem[0][i].detail,
			boxCardItem[0][i].grade) == -1)
		{
			boxCardItem[0][i].seen =
				false;

			newItemCnt++;
		}
		else
		{
			boxCardItem[0][i].seen =
				true;
		}
	}
}


//상자 표(castleRewardBoxRate)의 몇 번째 줄을 쓸 것인가.
//
//원래는 robin.castle 만 봤다. 그런데 robin.castle 은 지금 아무 데서도
//오르지 않는다(디버그 메뉴에서 0 이나 18 로 찍을 뿐이다). 그래서 표가
//영원히 0번 줄에 머물렀고, 나무상자만 나오니 동료도 장비도 좋아지지
//않았다 - "뒤로 갈수록 좋은 게 나온다"가 성립하지 않았다.
//
//웨이브 진행을 같이 본다. 10000 웨이브를 표의 줄 수에 고르게 나눠서,
//끝까지 가면 마지막 줄에 닿는다. 성이 실제로 오르기 시작하면 둘 중
//높은 쪽을 쓰므로 이 함수를 다시 고칠 필요가 없다.
int GetWaveRewardBoxTier(int waveIdx)
{
	const int rows = wave_COUNT / (MAXWAVEENEMY * WAVEDATASIZE);

	if (waveIdx <= 0 || rows <= 0)
		return 0;

	int tier =
		(int)((long long)waveIdx * gTotalCastle / rows);

	if (tier < 0)
		tier = 0;

	if (tier >= gTotalCastle)
		tier = gTotalCastle - 1;

	return tier;
}

int SelectCastleRewardBox(
	int castleIndex)
{
	int waveTier =
		GetWaveRewardBoxTier(
			robin.waveIdx);

	if (castleIndex < waveTier)
		castleIndex = waveTier;

	if (castleIndex < 0)
		castleIndex = 0;

	if (castleIndex >= gTotalCastle)
		castleIndex = gTotalCastle - 1;

	int totalRate = 0;

	for (int i = 0;
		i < REWARD_BOX_COUNT;
		i++)
	{
		totalRate +=
			castleRewardBoxRate
			[castleIndex][i];
	}

	if (totalRate <= 0)
	{
		return BOX_REWARD0;
	}

	int roll =
		Random(totalRate);

	int sum = 0;

	for (int i = 0;
		i < REWARD_BOX_COUNT;
		i++)
	{
		sum +=
			castleRewardBoxRate
			[castleIndex][i];

		if (roll < sum)
		{
			return BOX_REWARD0 + i;
		}
	}

	return BOX_REWARD0;
}

//인터랙티브 전투 튜토리얼: 이번에 여는 상자가 시나리오상 몇 번째 상자인지.
//0=첫 처치, 1=두번째 처치, 2=하트베팅 처치. 튜토리얼이 아니거나 지정 상자가 아니면 -1.
//robin.waveIdx는 첫 상자와 두번째 상자가 둘 다 0(SNAIL)이라 구분이 안 되므로,
//진행 플래그(robin.demoSeen[])로 판별한다. 이 순서는 Func_Combat.cpp의 사망 훅이
//nextTutorialDemo를 고르는 순서와 1:1로 같다.
int GetTutorialGachaBoxIndex(void)
{
	if (robinmap != MAP_DIORAMA_TOLEM || robin.demoSeen[DEMO_TUTORIAL_END])
		return -1;

	if (!robin.demoSeen[DEMO_TUTORIAL_FIRSTKILL])
		return 0;

	//두번째 상자(하트+동료+갑옷)는 그 갑옷을 가르치는 DEMO_TUTORIAL_EQUIP을 기준으로 본다.
	//DEMO_TUTORIAL_SECONDKILL("다시 공격해보자")은 이제 동료 편성을 마친 자리에서 걸려
	//두번째 처치보다 먼저 seen이 되므로 여기에 쓸 수 없다.
	if (!robin.demoSeen[DEMO_TUTORIAL_EQUIP])
		return 1;

	if (!robin.demoSeen[DEMO_TUTORIAL_ROULETTE])
		return 2;

	//마지막 보스를 잡고 여는 상자. 5성 동료 한 명이 들어 있다.
	if (!robin.demoSeen[DEMO_TUTORIAL_BOSS])
		return 3;

	return -1;
}

//튜토리얼 상자의 확정 카드 구성.
//보상 내용은 demoItem[](Data/DemoData.h)을 그대로 쓴다 - 예전에는 데모의
//EFFECT_TUTORIAL_REWARD가 같은 표를 읽어 직접 GetItem()으로 지급했는데, 지금은 카드를
//뒤집어 받는 가챠 쪽으로 지급을 옮겼다(이중 지급을 막기 위해 DemoData.h의 해당 행은 제거).
//DEMOITEM_TUTORIAL_FIRSTKILL_BOX는 "떨어지는 상자" 자체라서 카드 목록에서 제외한다.
static bool MakeTutorialBoxReward(int tutorialBoxIndex)
{
	static const int cardCount[4] = { 2, 3, 4, 1 };

	static const int cardItemIdx[4][4] = {
		{ DEMOITEM_TUTORIAL_FIRSTKILL_HEART,	DEMOITEM_TUTORIAL_FIRSTKILL_CREW,	-1,									-1 },
		{ DEMOITEM_TUTORIAL_SECONDKILL_HEART,	DEMOITEM_TUTORIAL_SECONDKILL_CREW,	DEMOITEM_TUTORIAL_SECONDKILL_EQUIP,	-1 },
		{ DEMOITEM_TUTORIAL_HEARTBET_HEART,		DEMOITEM_TUTORIAL_HEARTBET_CREW1,	DEMOITEM_TUTORIAL_HEARTBET_CREW2,	DEMOITEM_TUTORIAL_HEARTBET_CREW3 },
		{ DEMOITEM_TUTORIAL_BOSS_CREW,			-1,									-1,									-1 },
	};

	int i;
	int writeIndex = 0;

	if (tutorialBoxIndex < 0 || tutorialBoxIndex > 3)
		return false;

	memset(&boxCardItem[0], 0, sizeof(boxCardItem[0]));
	boxCardItemCnt[0] = 0;

	for (i = 0; i < cardCount[tutorialBoxIndex] && writeIndex < GACHA_MAX_REWARD_CARD; i++) {
		int idx = cardItemIdx[tutorialBoxIndex][i];

		if (idx < 0)
			continue;

		ITEM* item = &boxCardItem[0][writeIndex];

		//demoItem[]의 한 행 = [0]NPC [1]type [2]detail [3]grade [4]count
		item->type = demoItem[idx * 5 + 1];
		item->detail = demoItem[idx * 5 + 2];
		item->grade = demoItem[idx * 5 + 3];
		item->count = demoItem[idx * 5 + 4];

		//하트/골드는 수량 아이템이라 lv/cooldown이 의미없다. 나머지는 MakeBoxCrewReward()/
		//MakeBoxEquipReward()와 같은 값으로 맞춰준다.
		switch (item->type) {
		case ITEM_HEART:
		case ITEM_GOLD:
			item->seen = true;
			break;
		default:
			item->lv = 1;
			item->cooldown = 0;
			item->seen = GetInvenIdx(item->type, item->detail, item->grade) >= 0;
			break;
		}

		writeIndex++;
	}

	boxCardItemCnt[0] = writeIndex;

	//순서는 시나리오대로 고정이므로 OrderBoxReward()를 부르지 않는다.
	CheckNewBoxReward(boxCardItemCnt[0]);

	return boxCardItemCnt[0] > 0;
}

//아직 안 가진 것 중에서 그 별에 해당하는 놈을 하나 고른다.
//
//시험용이다. 없으면 소유 여부를 포기하고 아무거나 그 별로 고른다 -
//연출을 보려는 것이지 미보유 판정을 시험하려는 게 아니기 때문이다.
static int FindUnownedBoxDetailByStar(
	int itemType,
	int itemGrade,
	int targetStar)
{
	int detailCount =
		GetBoxDetailCount(
			itemType);

	int fallback = -1;

	for (int detail = 0;
		detail < detailCount;
		detail++)
	{
		if (GetItemStar(
			itemType,
			detail,
			itemGrade) != targetStar)
		{
			continue;
		}

		if (fallback < 0)
			fallback = detail;

		if (GetInvenIdx(
			itemType,
			detail,
			itemGrade) < 0)
		{
			return detail;
		}
	}

	return fallback;
}

//시험용 상자. 하트 / 골드 / 미보유 5성 동료 / 미보유 5성 장비 네 장을 낸다.
//
//BalanceConfig.h 의 GACHA_TEST_FORCE_REWARD 로 켠다. 순서 규칙(하트 ->
//골드 -> 동료 -> 장비)과 카드 문구(ALPHA_FIRSTFIND / ALPHA_LEGENDARY)를
//한 번에 확인하려는 것이다.
static bool MakeTestForceBoxReward(
	const REWARD_BOX_DATA* boxData)
{
	memset(
		&boxCardItem[0],
		0,
		sizeof(boxCardItem[0]));

	boxCardItemCnt[0] = 0;

	int writeIndex = 0;

	MakeBoxHeartReward(
		writeIndex++,
		boxData,
		false);

	MakeBoxGoldReward(
		writeIndex++,
		boxData,
		false);

	//5성은 등급 4다(GetItemStar 가 1~6을 돌려주고 별 = 등급 + 1).
	const int testGrade = 4;
	const int testStar = testGrade + 1;

	//------------------------------------------------------------
	// 미보유 5성 동료
	//------------------------------------------------------------
	{
		int detail =
			FindUnownedBoxDetailByStar(
				ITEM_CREW,
				testGrade,
				testStar);

		if (detail >= 0)
		{
			ITEM* item =
				&boxCardItem[0][
					writeIndex];

			item->type = ITEM_CREW;
			item->detail = detail;
			item->grade = testGrade;
			item->count = 1;
			item->lv = 1;
			item->cooldown = 0;

			item->seen =
				GetInvenIdx(
					item->type,
					item->detail,
					item->grade) >= 0;

			writeIndex++;
		}
		else
		{
			CCLOG(
				"MakeTestForceBoxReward: no crew at star=%d",
				testStar);
		}
	}

	//------------------------------------------------------------
	// 미보유 5성 장비
	//------------------------------------------------------------
	{
		int equipType =
			MakeBoxEquipType();

		int detail =
			FindUnownedBoxDetailByStar(
				equipType,
				testGrade,
				testStar);

		if (detail >= 0)
		{
			ITEM* item =
				&boxCardItem[0][
					writeIndex];

			item->type = equipType;
			item->detail = detail;
			item->grade = testGrade;
			item->count = 1;
			item->lv = 1;
			item->cooldown = 0;

			item->seen =
				GetInvenIdx(
					item->type,
					item->detail,
					item->grade) >= 0;

			writeIndex++;
		}
		else
		{
			CCLOG(
				"MakeTestForceBoxReward: no equip at star=%d type=%d",
				testStar,
				equipType);
		}
	}

	boxCardItemCnt[0] = writeIndex;

	OrderBoxReward(
		boxCardItemCnt[0]);

	CheckNewBoxReward(
		boxCardItemCnt[0]);

	return boxCardItemCnt[0] > 0;
}

bool GenerateCastleBoxReward(
	int boxDetail)
{
	int boxIndex =
		GetRewardBoxIndex(
			boxDetail);

	if (boxIndex < 0 ||
		boxIndex >=
		REWARD_BOX_COUNT)
	{
		CCLOG(
			"GenerateCastleBoxReward FAILED: boxDetail=%d boxIndex=%d",
			boxDetail,
			boxIndex);

		return false;
	}

	const REWARD_BOX_DATA*
		boxData =
		&rewardBoxData[boxIndex];

	//----------------------------------------------------
	// 인터랙티브 전투 튜토리얼: 확률을 전혀 쓰지 않고 시나리오가 정한 카드만 낸다.
	// 몇 번째 상자인지는 GetTutorialGachaBoxIndex()가 진행 플래그로 판별한다.
	//----------------------------------------------------
	{
		const int tutorialBoxIndex =
			GetTutorialGachaBoxIndex();

		if (tutorialBoxIndex >= 0)
		{
			gachaLuckyBox =
				false;

			return MakeTutorialBoxReward(
				tutorialBoxIndex);
		}
	}

	//----------------------------------------------------
	// 시험용 강제 보상 (BalanceConfig.h)
	//----------------------------------------------------
#if GACHA_TEST_FORCE_REWARD
	gachaLuckyBox =
		false;

	return MakeTestForceBoxReward(
		boxData);
#endif

	//----------------------------------------------------
	// 럭키 상자 판정
	//----------------------------------------------------
	gachaLuckyBox =
		Random(100) <
		boxData->luckyRate;

	//----------------------------------------------------
	// 기본 카드 수
	//----------------------------------------------------
	int cardCount =
		BoxRandomRange(
			boxData->minCard,
			boxData->maxCard);

	//----------------------------------------------------
	// 럭키 시 카드 한 장 추가
	//----------------------------------------------------
	if (gachaLuckyBox)
	{
		cardCount =
			Min(
				GACHA_MAX_REWARD_CARD,
				cardCount + 1);
	}

	cardCount =
		Min(
			cardCount,
			GACHA_MAX_REWARD_CARD);

	//----------------------------------------------------
	// 골드 등장 여부
	//----------------------------------------------------
	bool makeGold =
		boxData->goldMax > 0 &&
		Random(100) <
		boxData->goldRate;

	//----------------------------------------------------
	// 카드가 2장인데 골드가 나오면
	// 하트 + 골드만 남으므로 최소 3장으로 보정
	//----------------------------------------------------
	if (makeGold &&
		cardCount < 3)
	{
		cardCount =
			Min(
				3,
				GACHA_MAX_REWARD_CARD);
	}

	//----------------------------------------------------
	// 기존 보상 초기화
	//----------------------------------------------------
	memset(
		&boxCardItem[0],
		0,
		sizeof(boxCardItem[0]));

	boxCardItemCnt[0] =
		0;

	int writeIndex =
		0;

	//----------------------------------------------------
	// 하트는 항상 한 장
	//----------------------------------------------------
	if (writeIndex <
		cardCount)
	{
		MakeBoxHeartReward(
			writeIndex,
			boxData,
			gachaLuckyBox);

		writeIndex++;
	}

	//----------------------------------------------------
	// 골드는 goldRate 확률로 한 장
	//----------------------------------------------------
	if (makeGold &&
		writeIndex <
		cardCount)
	{
		MakeBoxGoldReward(
			writeIndex,
			boxData,
			gachaLuckyBox);

		writeIndex++;
	}

	//----------------------------------------------------
	// 나머지는 동료 또는 장비
	//----------------------------------------------------
	while (writeIndex <
		cardCount)
	{
		int totalTypeRate =
			boxData->crewRate +
			boxData->equipRate;

		//------------------------------------------------
		// 비정상 데이터 방어
		//------------------------------------------------
		if (totalTypeRate <= 0)
		{
			CCLOG(
				"GenerateCastleBoxReward FAILED: invalid type rate boxIndex=%d",
				boxIndex);

			return false;
		}

		int typeRoll =
			Random(
				totalTypeRate);

		if (typeRoll <
			boxData->crewRate)
		{
			MakeBoxCrewReward(
				writeIndex,
				boxIndex);
		}
		else
		{
			MakeBoxEquipReward(
				writeIndex,
				boxIndex);
		}

		writeIndex++;
	}

	boxCardItemCnt[0] =
		writeIndex;

	//----------------------------------------------------
	// 럭키 카드 한 장 승급
	//----------------------------------------------------
	if (gachaLuckyBox)
	{
		UpgradeLuckyBoxCard(
			boxCardItemCnt[0]);
	}

	//----------------------------------------------------
	// 표시 순서 : 하트 -> 골드 -> 동료 -> 장비
	//----------------------------------------------------
	OrderBoxReward(
		boxCardItemCnt[0]);

	//----------------------------------------------------
	// 신규 카드 확인
	//----------------------------------------------------
	CheckNewBoxReward(
		boxCardItemCnt[0]);

	//----------------------------------------------------
	// 확인 로그
	//----------------------------------------------------
	CCLOG(
		"GenerateCastleBoxReward: detail=%d boxIndex=%d lucky=%d cards=%d gold=%d",
		boxDetail,
		boxIndex,
		gachaLuckyBox,
		boxCardItemCnt[0],
		makeGold);

	return boxCardItemCnt[0] > 0;
}

int GetWeightedNormalizedReward(
	int minValue,
	int maxValue)
{
	if (minValue <= 0)
	{
		return 0;
	}

	if (maxValue <= minValue)
	{
		return minValue;
	}

	//----------------------------------------------------
	// 시작값의 1/10 단위
	//----------------------------------------------------
	int unit =
		minValue / 10;

	if (unit <= 0)
	{
		unit =
			1;
	}

	//----------------------------------------------------
	// 최대값을 지급 단위에 맞춰 내림
	//----------------------------------------------------
	int normalizedMax =
		(maxValue / unit) *
		unit;

	if (normalizedMax <
		minValue)
	{
		normalizedMax =
			minValue;
	}

	int levelCount =
		(normalizedMax -
			minValue) /
		unit +
		1;

	if (levelCount <= 1)
	{
		return minValue;
	}

	//----------------------------------------------------
	// 낮은 금액일수록 높은 가중치
	//----------------------------------------------------
	int totalWeight =
		levelCount *
		(levelCount + 1) /
		2;

	int roll =
		Random(
			totalWeight);

	int accumulatedWeight =
		0;

	for (int i = 0;
		i < levelCount;
		i++)
	{
		int weight =
			levelCount -
			i;

		accumulatedWeight +=
			weight;

		if (roll <
			accumulatedWeight)
		{
			return minValue +
				i *
				unit;
		}
	}

	return minValue;
}

void GachaDraw(void)
{
	int i;

	//문구는 매 프레임 다시 세운다. 카드가 넘어가면 저절로 사라진다.
	gachaAlphaBannerIdx = -1;

	//--------------------------------------------------------
	// GotoGacha에서 생성 완료되지 않았으면 처리하지 않음
	//--------------------------------------------------------
	if (gachaPrepared == false)
	{
		return;
	}

	//--------------------------------------------------------
	// 상자 또는 보상 생성 실패 방어
	//--------------------------------------------------------
	if (boxCnt <= 0 ||
		boxCardItemCnt[0] <= 0)
	{
		CCLOG(
			"GachaDraw INVALID: boxCnt=%d cardCnt=%d",
			boxCnt,
			boxCardItemCnt[0]);

		return;
	}

	//--------------------------------------------------------
	// 가챠 단계 변경 확인
	//--------------------------------------------------------
	if (previousGachaDepth !=
		gachaDepth)
	{
		switch (gachaDepth)
		{
		case GACHA_DEPTH_SUMMARY:
			summaryFrame =
				0;
			break;

		case GACHA_DEPTH_FLYTOBAR:
			flyToBarFrame =
				0;
			break;

		case GACHA_DEPTH_GETITEM:
			getItemFrame =
				0;
			break;
		}

		previousGachaDepth =
			gachaDepth;
	}

	//--------------------------------------------------------
	// 가챠 배경 어둡기
	//
	// 카드가 메뉴로 날아가는 동안에는
	// 어두운 오버레이를 서서히 제거한다.
	//--------------------------------------------------------
	int gachaScreenDarken =
		SCREENDARKEN;

	if (gachaDepth ==
		GACHA_DEPTH_FLYTOBAR)
	{
		const int BRIGHTEN_FRAME =
			12 * MOTIONDIV;

		float brightenProgress =
			(float)flyToBarFrame /
			(float)BRIGHTEN_FRAME;

		brightenProgress =
			GachaClamp01(
				brightenProgress);

		//----------------------------------------------------
		// 초반에는 천천히, 후반에는 빠르게 밝아짐
		//----------------------------------------------------
		float brightenCurve =
			GachaEaseInOutCubic(
				brightenProgress);

		gachaScreenDarken =
			(int)GachaLerp(
				(float)SCREENDARKEN,
				0.0f,
				brightenCurve);
	}

	ScreenDarken(
		gachaScreenDarken);

	switch (gachaDepth)
	{
		//--------------------------------------------------------
		// 상자 등장 및 오픈
		//--------------------------------------------------------
	case GACHA_DEPTH_BOX:
	{
		const int WAIT_END = 8;
		const int SQUASH_END = 13;
		const int RISE_END = 19;
		const int APEX_END = 23;
		const int FALL_END = 29;
		const int LAND_END = 33;
		const int FINISH_END = 43;

		//----------------------------------------------------
		// 상자 최하단 위치
		//----------------------------------------------------
		const float baseY =
			BOTTOMMENUHEIGHT +
			32.0f * _2X;

		const float apexY =
			baseY +
			GACHA_BOX_BOUNCE_HEIGHT * 1.45f;

		float baseZoom =
			boxMark[0].zoomEnd2;

		if (baseZoom <= 0.0f)
			baseZoom = boxMark[0].zoom2;

		float targetY =
			baseY;

		float targetZoom =
			baseZoom;

		//----------------------------------------------------
		// 기존 상자 낙하 완료 확인
		//----------------------------------------------------
		if (boxMark[0].motionFrame < 0)
		{
			const float POSITION_EPSILON =
				0.5f * _2X;

			const float ZOOM_EPSILON =
				0.001f;

			bool positionArrived =
				fabsf(
					boxMark[0].y -
					baseY) <=
				POSITION_EPSILON;

			bool zoomArrived =
				fabsf(
					boxMark[0].zoom2 -
					baseZoom) <=
				ZOOM_EPSILON;

			if (positionArrived &&
				zoomArrived)
			{
				boxMark[0].motionFrame =
					0;

				boxMark[0].y =
					baseY;

				boxMark[0].targetY2 =
					baseY;

				boxMark[0].speed2 =
					0.0f;

				boxMark[0].speedIncrement2 =
					0.0f;

				boxMark[0].zoom2 =
					baseZoom;

				boxMark[0].zoomIncrement2 =
					0.0f;
			}
			else
			{
				break;
			}
		}

		//----------------------------------------------------
		// 상자 바운스 및 오픈
		//----------------------------------------------------
		if (boxMark[0].motionFrame >= 0)
		{
			int animFrame =
				boxMark[0].motionFrame;

			float progress =
				0.0f;

			float curve =
				0.0f;

			targetY =
				baseY;

			targetZoom =
				baseZoom;

			//------------------------------------------------
			// 바닥 대기
			//------------------------------------------------
			if (animFrame < WAIT_END)
			{
				targetY =
					baseY;

				targetZoom =
					baseZoom;
			}

			//------------------------------------------------
			// 점프 전 웅크리기
			//------------------------------------------------
			else if (animFrame < SQUASH_END)
			{
				progress =
					(float)(
						animFrame -
						WAIT_END) /
					(float)(
						SQUASH_END -
						WAIT_END);

				curve =
					progress *
					progress;

				targetY =
					baseY -
					3.0f *
					_2X *
					curve;

				targetZoom =
					baseZoom *
					(1.0f -
						0.05f *
						curve);
			}

			// ------------------------------------------------
			// 빠르게 상승
			//------------------------------------------------
			else if (animFrame < RISE_END)
			{
				progress =
					(float)(
						animFrame -
						SQUASH_END) /
					(float)(
						RISE_END -
						SQUASH_END);

				curve =
					1.0f -
					powf(
						1.0f -
						progress,
						3.0f);

				targetY =
					baseY +
					(apexY -
						baseY) *
					curve;

				targetZoom =
					baseZoom *
					(0.95f +
						0.05f *
						curve);
			}

			//------------------------------------------------
			// 최고점에서 상자 오픈
			//------------------------------------------------
			else if (animFrame < APEX_END)
			{
				targetY =
					apexY;

				targetZoom =
					baseZoom;

				if (animFrame == RISE_END)
				{
					boxMark[0].motion =
						BOXSTATUS_OPENED;

					PlayMusic(M_OPENDOOR);
				}
			}

			//------------------------------------------------
			// 급강하
			//------------------------------------------------
			else if (animFrame < FALL_END)
			{
				progress =
					(float)(
						animFrame -
						APEX_END) /
					(float)(
						FALL_END -
						APEX_END);

				curve =
					progress *
					progress *
					progress;

				targetY =
					apexY -
					(apexY -
						baseY) *
					curve;

				targetZoom =
					baseZoom;
			}

			//------------------------------------------------
			// 착지 충격
			//------------------------------------------------
			else if (animFrame < LAND_END)
			{
				progress =
					(float)(
						animFrame -
						FALL_END) /
					(float)(
						LAND_END -
						FALL_END);

				curve =
					sinf(
						progress *
						3.141592f);

				targetY =
					baseY -
					2.5f *
					_2X *
					curve;

				targetZoom =
					baseZoom *
					(1.0f -
						0.045f *
						curve);

				if (animFrame < LAND_END - 1)
				{
					PlayMusic(M_KUNG);
				}
			}

			//------------------------------------------------
			// 열린 상태로 대기
			//------------------------------------------------
			else
			{
				targetY =
					baseY;

				targetZoom =
					baseZoom;
			}

			boxMark[0].y =
				targetY;

			boxMark[0].targetY2 =
				targetY;

			boxMark[0].zoom2 =
				targetZoom;

			boxMark[0].zoomIncrement2 =
				0.0f;

			//------------------------------------------------
			// 상자 연출 완료
			//------------------------------------------------
			if (animFrame >= FINISH_END)
			{
				boxMark[0].y =
					baseY;

				boxMark[0].targetY2 =
					baseY;

				boxMark[0].zoom2 =
					baseZoom;

				gachaDepth =
					GACHA_DEPTH_CARD;

				gachaOpenCardIdx =
					-1;

				gachaCurrentCardReady =
					false;

				manualCardMarkIdx =
					-1;
			}
			else
			{
				boxMark[0].motionFrame++;
			}
		}

		break;
	}

	//--------------------------------------------------------
	// 카드 한 장씩 공개
	//--------------------------------------------------------
	//--------------------------------------------------------
// 카드 한 장씩 공개
//--------------------------------------------------------
	case GACHA_DEPTH_CARD:
	{
		//----------------------------------------------------
		// [특수연출 수정 1]
		// 카드 공개 특수 연출 단계
		//----------------------------------------------------
		enum
		{
			GACHA_SPECIAL_NORMAL,
			GACHA_SPECIAL_GOOD,
			GACHA_SPECIAL_RARE,
			GACHA_SPECIAL_JACKPOT
		};

		//----------------------------------------------------
		// 카드 공개 연출 프레임
		//----------------------------------------------------
		const int CARD_RISE_FRAME =
			8 * MOTIONDIV;

		const int CARD_IMPACT_FRAME =
			2 * MOTIONDIV;

		const int CARD_RECOVER_FRAME =
			3 * MOTIONDIV;

		const int CARD_HOLD_FRAME =
			4 * MOTIONDIV;

		const int CARD_FLIP_INTERVAL =
			2 * MOTIONDIV;

		const int CARD_BACK_FRAME_COUNT =
			7;

		const int CARD_RISE_END =
			CARD_RISE_FRAME;

		const int CARD_IMPACT_END =
			CARD_RISE_END +
			CARD_IMPACT_FRAME;

		const int CARD_RECOVER_END =
			CARD_IMPACT_END +
			CARD_RECOVER_FRAME;

		const int CARD_HOLD_END =
			CARD_RECOVER_END +
			CARD_HOLD_FRAME;

		const int CARD_FLIP_END =
			CARD_HOLD_END +
			CARD_FLIP_INTERVAL *
			CARD_BACK_FRAME_COUNT;

		const int CARD_TOUCH_DELAY =
			FPS / 6;

		//----------------------------------------------------
		// 공개 카드 크기
		//----------------------------------------------------
		const float CARD_START_ZOOM =
			0.38f;

		const float CARD_FINAL_ZOOM =
			0.95f;

		const float CARD_OVERSHOOT_ZOOM =
			1.02f;

		const float CARD_PRESSED_ZOOM =
			0.90f;

		//----------------------------------------------------
		// 하단으로 이동하는 연출
		//----------------------------------------------------
		const int CARD_TO_TRAY_FRAME =
			10 * MOTIONDIV;

		//항상 한 줄이다. 2행으로 접었더니 윗줄이 상자에 가렸다.
		//대신 폭이 모자라면 카드를 줄이지 않고 서로 겹쳐 깐다. 손패처럼 보이고,
		//무엇보다 카드 크기가 획득 개수와 무관하게 항상 같다. 개수에 따라
		//작아지면 많이 받을수록 연출이 초라해진다.
		const float TRAY_GAP =
			4.0f * _2X;

		//겹치더라도 카드 폭의 이만큼은 보이게 한다.
		const float TRAY_MIN_SHOW =
			0.40f;

		const float TRAY_CARD_ZOOM =
			0.38f;

		//----------------------------------------------------
		// 공개 카드 위치
		//----------------------------------------------------
		const float CARD_START_OFFSET_Y =
			120.0f * _2X;

		const float CARD_END_OFFSET_Y =
			240.0f * _2X;

		const float CARD_CENTER_X =
			boxMark[0].x;

		const float CARD_START_Y =
			boxMark[0].y +
			CARD_START_OFFSET_Y;

		const float CARD_END_Y =
			boxMark[0].y +
			CARD_END_OFFSET_Y;

		int rewardCount =
			boxCardItemCnt[0];

		if (rewardCount >
			GACHA_MAX_REWARD_CARD)
		{
			rewardCount =
				GACHA_MAX_REWARD_CARD;
		}

		//----------------------------------------------------
		// 하단 카드 정렬 위치 계산
		//
		// 한 줄. 폭이 모자라면 간격(pitch)을 좁혀 겹쳐 깐다.
		//----------------------------------------------------
		float trayCardW =
			240.0f *
			TRAY_CARD_ZOOM;

		float trayUsableW =
			(float)(DX - 2 * xOffset) -
			8.0f * _2X;

		//안 겹쳤을 때의 간격. 이대로 다 들어가면 그냥 나란히 깐다.
		float trayPitch =
			trayCardW + TRAY_GAP;

		if (rewardCount > 1) {
			float need =
				trayCardW + (rewardCount - 1) * trayPitch;

			if (need > trayUsableW) {
				trayPitch =
					(trayUsableW - trayCardW) / (rewardCount - 1);
			}

			//너무 겹치면 앞 카드가 아이콘까지 가린다.
			if (trayPitch < trayCardW * TRAY_MIN_SHOW)
				trayPitch = trayCardW * TRAY_MIN_SHOW;
		}

		float trayTotalW =
			trayCardW + (rewardCount - 1) * trayPitch;

		float trayStartX =
			xOffset +
			DX / 2.0f -
			trayTotalW / 2.0f;

		//y는 카드의 윗변이고 값이 클수록 화면 위다.
		float trayY =
			BOTTOMMENUHEIGHT +
			12.0f * _2X;

		//----------------------------------------------------
		// 모든 카드의 하단 목표 위치 갱신
		//
		// 뒤 카드일수록 나중에 그려져 앞 카드를 덮는다. 손패처럼 보인다.
		//----------------------------------------------------
		for (i = 0;
			i < rewardCount;
			i++)
		{
			gachaRewardCardAnim[i].trayX =
				trayStartX + i * trayPitch;

			gachaRewardCardAnim[i].trayY =
				trayY;

			gachaRewardCardAnim[i].trayZoom =
				TRAY_CARD_ZOOM;
		}

		//----------------------------------------------------
		// 카드 번호가 변경됨
		//
		// 이전 카드가 선택 완료된 것이므로
		// 현재 위치에서 하단 정렬 위치로 날려 보낸다.
		//----------------------------------------------------
		if (previousOpenCardIdx !=
			gachaOpenCardIdx)
		{
			if (previousOpenCardIdx >= 0 &&
				previousOpenCardIdx <
				rewardCount)
			{
				GACHA_REWARD_CARD_ANIM* anim =
					&gachaRewardCardAnim[
						previousOpenCardIdx];

				anim->active =
					true;

				anim->movingToTray =
					true;

				anim->arrivedTray =
					false;

				anim->movingToPopup =
					false;

				anim->arrivedPopup =
					false;

				anim->moveFrame =
					0;

				//------------------------------------------------
				// 현재 공개 카드 위치에서 출발
				//------------------------------------------------
				if (manualCardMarkIdx >= 0)
				{
					ICONMARK* previousCard =
						&boxCardMark[
							manualCardMarkIdx];

					anim->startX =
						previousCard->x;

					anim->startY =
						previousCard->y;

					anim->startZoom =
						previousCard->zoom;

					memset(
						previousCard,
						0,
						sizeof(ICONMARK));

					manualCardMarkIdx =
						-1;
				}
				else
				{
					anim->startX =
						CARD_CENTER_X -
						240.0f *
						CARD_FINAL_ZOOM /
						2.0f;

					anim->startY =
						CARD_END_Y;

					anim->startZoom =
						CARD_FINAL_ZOOM;
				}

				trayCardCount =
					previousOpenCardIdx +
					1;

				PlayMusic(M_ITEM);
			}

			previousOpenCardIdx =
				gachaOpenCardIdx;

			gachaCurrentCardReady =
				false;

			gachaCardCanAdvance =
				false;
		}

		//----------------------------------------------------
		// 하단으로 이동 중인 카드와 도착한 카드 출력
		//----------------------------------------------------
		bool allTrayCardsArrived =
			true;

		for (i = 0;
			i < trayCardCount &&
			i < rewardCount;
			i++)
		{
			GACHA_REWARD_CARD_ANIM* anim =
				&gachaRewardCardAnim[i];

			if (anim->active == false)
				continue;

			float drawX =
				anim->trayX;

			float drawY =
				anim->trayY;

			float drawZoom =
				anim->trayZoom;

			if (anim->movingToTray)
			{
				float progress =
					(float)anim->moveFrame /
					(float)CARD_TO_TRAY_FRAME;

				progress =
					GachaClamp01(progress);

				float moveCurve =
					GachaEaseInOutCubic(
						progress);

				float zoomCurve =
					GachaEaseOutCubic(
						progress);

				drawX =
					GachaLerp(
						anim->startX,
						anim->trayX,
						moveCurve);

				//------------------------------------------------
				// 직선 이동보다 약간 위로 솟는 곡선
				//------------------------------------------------
				float linearY =
					GachaLerp(
						anim->startY,
						anim->trayY,
						moveCurve);

				float arcY =
					sinf(
						progress *
						3.141592f) *
					32.0f *
					_2X;

				drawY =
					linearY +
					arcY;

				drawZoom =
					GachaLerp(
						anim->startZoom,
						anim->trayZoom,
						zoomCurve);

				anim->moveFrame++;

				if (anim->moveFrame >=
					CARD_TO_TRAY_FRAME)
				{
					anim->movingToTray =
						false;

					anim->arrivedTray =
						true;

					anim->moveFrame =
						0;

					drawX =
						anim->trayX;

					drawY =
						anim->trayY;

					drawZoom =
						anim->trayZoom;
				}
			}

			if (anim->arrivedTray == false)
			{
				allTrayCardsArrived =
					false;
			}

			ITEM* trayItem =
				&boxCardItem[0][i];

			DrawItemCard(
				trayItem->type,
				trayItem->detail,
				trayItem->grade,
				trayItem->lv,
				trayItem->count,
				false,
				(int)drawX,
				(int)drawY,
				false,
				drawZoom,
				false,
				0,
				0,
				true,
				0);
		}

		//----------------------------------------------------
		// 아직 첫 카드를 뽑기 전
		//----------------------------------------------------
		if (gachaOpenCardIdx < 0)
		{
			SetAlpha(
				32 -
				Abs(
					frame /
					MOTIONDIV %
					32 -
					16));

			DrawGoldAlpha(
				xOffset + DX / 2,
				BOTTOMMENUHEIGHT,
				ALPHA_TABTOCOLLECT,
				FONT_GOLD_LARGE,
				1,
				CENTER,
				false,
				false);

			SetAlpha(32);

			gachaCardCanAdvance =
				true;

			SetRectPoint(
				0,
				DY,
				DX,
				DY,
				TOUCH_FUNC_GETGACHACARD);

			break;
		}

		//----------------------------------------------------
		// 모든 카드 선택 완료
		//----------------------------------------------------
		if (gachaOpenCardIdx >=
			rewardCount)
		{
			waitingForTrayComplete =
				true;

			gachaCurrentCardReady =
				false;

			gachaCardCanAdvance =
				false;

			//------------------------------------------------
			// 마지막 카드까지 하단에 도착하면 요약 화면
			//------------------------------------------------
			if (waitingForTrayComplete &&
				trayCardCount >= rewardCount &&
				allTrayCardsArrived)
			{
				waitingForTrayComplete =
					false;

				gachaDepth =
					GACHA_DEPTH_SUMMARY;

				summaryFrame =
					0;

				previousGachaDepth =
					GACHA_DEPTH_CARD;
			}

			break;
		}

		ITEM* item =
			&boxCardItem[0][
				gachaOpenCardIdx];

		//----------------------------------------------------
		// [특수연출 수정 2]
		// 현재 보상의 신규 / 별 / 대박 재화 판정
		//----------------------------------------------------
		bool isCrew =
			item->type ==
			ITEM_CREW;

		bool isHeart =
			item->type ==
			ITEM_HEART;

		bool isGold =
			item->type ==
			ITEM_GOLD;

		//----------------------------------------------------
		// 기존 코드의 장비 분류 기준을 그대로 사용한다.
		//----------------------------------------------------
		bool isEquip =
			item->type != ITEM_CREW &&
			item->type != ITEM_HEART &&
			item->type != ITEM_GOLD &&
			item->type != ITEM_STAR &&
			item->type < ITEM_NETITEM;

		bool isStarCard =
			isCrew ||
			isEquip;

		//----------------------------------------------------
		// 동료 / 장비만 GetItemStar를 호출한다.
		// 반환값: 1 ~ 6성
		//----------------------------------------------------
		int itemStar =
			0;

		if (isStarCard)
		{
			itemStar =
				GetItemStar(
					item->type,
					item->detail,
					item->grade);
		}

		//----------------------------------------------------
		// 신규 카드는 인벤토리에 같은 카드가 없을 때이다.
		//----------------------------------------------------
		bool isNewCard =
			false;

		if (isStarCard)
		{
			isNewCard =
				GetInvenIdx(
					item->type,
					item->detail,
					item->grade) < 0;

			//------------------------------------------------
			// 같은 상자 안에 동일 신규 카드가 여러 장이면
			// 첫 번째 카드에만 NEW 연출을 적용한다.
			//------------------------------------------------
			if (isNewCard)
			{
				for (int checkIdx = 0;
					checkIdx < gachaOpenCardIdx;
					checkIdx++)
				{
					ITEM* previousItem =
						&boxCardItem[0][
							checkIdx];

					if (previousItem->type ==
						item->type &&
						previousItem->detail ==
						item->detail &&
						previousItem->grade ==
						item->grade)
					{
						isNewCard =
							false;

						break;
					}
				}
			}
		}

		bool isHighGrade =
			isStarCard &&
			itemStar >= 4;

		bool isVeryHighGrade =
			isStarCard &&
			itemStar >= 5;

		bool isMaxGrade =
			isStarCard &&
			itemStar >= 6;

		//----------------------------------------------------
		// 재화는 별이 없으므로 획득량으로 판정한다.
		//
		// 현재 전체 상자 최대값 기준:
		// 하트 800 이상 강조, 950 이상 대박
		// 골드 800,000 이상 강조, 950,000 이상 대박
		//----------------------------------------------------
		bool isBigResource =
			(isHeart &&
				item->count >= 800) ||
			(isGold &&
				item->count >= 800000);

		bool isJackpotResource =
			(isHeart &&
				item->count >= 950) ||
			(isGold &&
				item->count >= 950000);

		int specialLevel =
			GACHA_SPECIAL_NORMAL;

		//----------------------------------------------------
		// 여러 조건이 겹치면 가장 높은 연출 하나만 사용한다.
		//----------------------------------------------------
		if (isJackpotResource ||
			isMaxGrade ||
			(isNewCard &&
				isVeryHighGrade) ||
			isVeryHighGrade ||
			(isNewCard &&
				isHighGrade))
		{
			specialLevel =
				GACHA_SPECIAL_JACKPOT;
		}
		else if (isNewCard ||
			isHighGrade)
		{
			specialLevel =
				GACHA_SPECIAL_RARE;
		}
		else if (isBigResource)
		{
			specialLevel =
				GACHA_SPECIAL_GOOD;
		}

		//----------------------------------------------------
		// 카드에 얹을 문구
		//
		// 처음 얻은 것과 5성 이상은 같은 카드라도 의미가 다르다. 카드 크기와
		// 소리만으로는 그 둘이 구별되지 않아서 글자로 말해준다.
		// 둘 다 해당하면 5성 쪽이 세므로 그쪽을 쓴다.
		//
		// 그리는 것은 Core::Run() 이 카드 마크를 다 그린 뒤에 한다. 여기서
		// 바로 그리면 뒤이어 그려지는 카드에 덮인다.
		//----------------------------------------------------
		int bannerAlpha = -1;

		if (isVeryHighGrade)
			bannerAlpha = ALPHA_LEGENDARY;
		else if (isNewCard)
			bannerAlpha = ALPHA_FIRSTFIND;

		int specialHoldFrame =
			0;

		switch (specialLevel)
		{
		case GACHA_SPECIAL_GOOD:
			specialHoldFrame =
				FPS * 20 / 30;
			break;

		case GACHA_SPECIAL_RARE:
			specialHoldFrame =
				FPS;
			break;

		case GACHA_SPECIAL_JACKPOT:
			specialHoldFrame =
				FPS * 3 / 2;
			break;
		}

		//----------------------------------------------------
	// 현재 공개 카드 생성
	//----------------------------------------------------
		if (gachaCurrentCardReady == false)
		{
			float startCenterX =
				CARD_CENTER_X;

			float startCenterY =
				CARD_START_Y;

			int markIdx =
				SetBoxCardMark(
					startCenterX,
					startCenterY,

					CARD_CENTER_X,
					CARD_END_Y,

					0,
					0,

					0,
					0,

					0,
					0,

					FPS,
					FPS,

					GetItemIcon(
						item->type,
						item->detail,
						item->grade),

					0,

					item->count,
					item->type,
					item->detail,
					item->grade,
					item->cooldown,

					false,
					true,
					true,

					PLAYER,

					1,

					CARD_START_ZOOM,
					CARD_FINAL_ZOOM,
					0.0f,

					CARD_FINAL_ZOOM,
					CARD_FINAL_ZOOM,
					0.0f,

					false,

					item->seen == false);

			if (markIdx >= 0)
			{
				ICONMARK* card =
					&boxCardMark[
						markIdx];

				manualCardMarkIdx =
					markIdx;

				card->manual =
					true;

				card->frame =
					1;

				card->frame2 =
					0;

				card->motionFrame =
					0;

				card->openFrame =
					1;

				card->x =
					startCenterX;

				card->y =
					startCenterY;

				card->targetX =
					CARD_CENTER_X;

				card->targetY =
					CARD_END_Y;

				card->targetX2 =
					0.0f;

				card->targetY2 =
					0.0f;

				card->zoom =
					CARD_START_ZOOM;

				card->zoom2 =
					CARD_START_ZOOM;

				card->zoomEnd =
					CARD_FINAL_ZOOM;

				card->zoomEnd2 =
					CARD_FINAL_ZOOM;

				card->zoomIncrement =
					0.0f;

				card->zoomIncrement2 =
					0.0f;

				card->speed =
					0.0f;

				card->speed2 =
					0.0f;

				card->speedIncrement =
					0.0f;

				card->speedIncrement2 =
					0.0f;

				gachaCurrentCardReady =
					true;

				gachaCardCanAdvance =
					false;

				PlayMusic(M_ITEM);
			}
			else
			{
				gachaCurrentCardReady =
					false;

				manualCardMarkIdx =
					-1;

				CCLOG(
					"SetBoxCardMark FAILED: openCardIdx=%d",
					gachaOpenCardIdx);
			}
		}
		//----------------------------------------------------
		// 현재 카드 수동 공개 애니메이션
		//----------------------------------------------------
		if (manualCardMarkIdx >= 0)
		{
			ICONMARK* card =
				&boxCardMark[
					manualCardMarkIdx];

			//----------------------------------------------------
	// [추가]
	// 터치가 들어오면 현재 애니메이션 단계의
	// 마지막 프레임으로 즉시 이동한다.
	//----------------------------------------------------
			if (gachaCardSkipRequested)
			{
				gachaCardSkipRequested =
					false;

				//------------------------------------------------
				// 1단계
				// 카드 상승·충격·복원 중
				//
				// 중앙에 완전히 올라온 뒷면 상태로 이동한다.
				//------------------------------------------------
				if (card->motionFrame <
					CARD_HOLD_END)
				{
					card->motionFrame =
						CARD_HOLD_END;

					card->x =
						CARD_CENTER_X;

					card->y =
						CARD_END_Y;

					card->zoom =
						CARD_FINAL_ZOOM;

					card->zoom2 =
						CARD_FINAL_ZOOM;

					card->openFrame =
						1;
				}

				//------------------------------------------------
				// 2단계
				// 카드 뒷면 정지 또는 회전 중
				//
				// 즉시 앞면으로 이동한다.
				//------------------------------------------------
				else if (card->motionFrame <
					CARD_FLIP_END)
				{
					card->motionFrame =
						CARD_FLIP_END;

					card->x =
						CARD_CENTER_X;

					card->y =
						CARD_END_Y;

					card->zoom =
						CARD_FINAL_ZOOM;

					card->zoom2 =
						CARD_FINAL_ZOOM;

					card->openFrame =
						0;

					//------------------------------------------------
					// 회전 완료 효과음을 한 번 재생
					//------------------------------------------------
					PlayMusic(
						M_CARDSPLIT);
				}

				//------------------------------------------------
				// 3단계
				// 앞면 공개 후 특수 연출 또는 강제 대기 중
				//
				// 특수 연출과 터치 지연을 끝낸다.
				// 이번 터치로 바로 하단 이동까지 하지는 않는다.
				//------------------------------------------------
				else if (card->motionFrame <
					CARD_FLIP_END +
					specialHoldFrame +
					CARD_TOUCH_DELAY +
					1)
				{
					card->motionFrame =
						CARD_FLIP_END +
						specialHoldFrame +
						CARD_TOUCH_DELAY +
						1;

					card->x =
						CARD_CENTER_X;

					card->y =
						CARD_END_Y;

					card->zoom =
						CARD_FINAL_ZOOM;

					card->zoom2 =
						CARD_FINAL_ZOOM;

					card->openFrame =
						0;

					//------------------------------------------------
					// 다음 터치부터 하단 이동 가능
					//------------------------------------------------
					gachaCardCanAdvance =
						true;
				}
			}

			int cardAnimFrame =
				card->motionFrame;

			float drawCenterX =
				CARD_CENTER_X;

			float drawCenterY =
				CARD_END_Y;

			float drawZoom =
				CARD_FINAL_ZOOM;

			float progress =
				0.0f;

			float curve =
				0.0f;

			if (cardAnimFrame <
				CARD_RISE_END)
			{
				progress =
					(float)cardAnimFrame /
					(float)CARD_RISE_FRAME;

				progress =
					GachaClamp01(
						progress);

				curve =
					GachaEaseOutCubic(
						progress);

				drawCenterY =
					CARD_START_Y +
					(CARD_END_Y -
						CARD_START_Y) *
					curve;

				drawZoom =
					CARD_START_ZOOM +
					(CARD_OVERSHOOT_ZOOM -
						CARD_START_ZOOM) *
					curve;

				card->openFrame =
					1;
			}
			else if (cardAnimFrame <
				CARD_IMPACT_END)
			{
				progress =
					(float)(
						cardAnimFrame -
						CARD_RISE_END) /
					(float)CARD_IMPACT_FRAME;

				progress =
					GachaClamp01(
						progress);

				drawZoom =
					CARD_OVERSHOOT_ZOOM +
					(CARD_PRESSED_ZOOM -
						CARD_OVERSHOOT_ZOOM) *
					progress;

				card->openFrame =
					1;
			}
			else if (cardAnimFrame <
				CARD_RECOVER_END)
			{
				progress =
					(float)(
						cardAnimFrame -
						CARD_IMPACT_END) /
					(float)CARD_RECOVER_FRAME;

				progress =
					GachaClamp01(
						progress);

				curve =
					1.0f -
					(1.0f - progress) *
					(1.0f - progress);

				drawZoom =
					CARD_PRESSED_ZOOM +
					(CARD_FINAL_ZOOM -
						CARD_PRESSED_ZOOM) *
					curve;

				card->openFrame =
					1;
			}
			else if (cardAnimFrame <
				CARD_HOLD_END)
			{
				card->openFrame =
					1;
			}
			else if (cardAnimFrame <
				CARD_FLIP_END)
			{
				int flipElapsed =
					cardAnimFrame -
					CARD_HOLD_END;

				int backFrame =
					flipElapsed /
					CARD_FLIP_INTERVAL +
					1;

				if (backFrame < 1)
				{
					backFrame =
						1;
				}

				if (backFrame ==
					CARD_BACK_FRAME_COUNT - 1 &&
					flipElapsed %
					CARD_FLIP_INTERVAL ==
					0)
				{
					PlayMusic(
						M_CARDSPLIT);
				}

				if (backFrame >
					CARD_BACK_FRAME_COUNT)
				{
					backFrame =
						CARD_BACK_FRAME_COUNT;
				}

				card->openFrame =
					backFrame;
			}
			else
			{
				card->openFrame =
					0;

				//------------------------------------------------
				// [특수연출 수정 3]
				// 앞면 공개 직후 특수 보상은 잠시 정지하면서
				// 카드가 한 번 팝업되도록 한다.
				//------------------------------------------------
				int specialElapsed =
					cardAnimFrame -
					CARD_FLIP_END;

				if (specialLevel !=
					GACHA_SPECIAL_NORMAL &&
					specialElapsed >= 0 &&
					specialElapsed <
					specialHoldFrame)
				{
					float specialProgress =
						(float)specialElapsed /
						(float)specialHoldFrame;

					specialProgress =
						GachaClamp01(
							specialProgress);

					float popPower =
						0.04f;

					if (specialLevel ==
						GACHA_SPECIAL_RARE)
					{
						popPower =
							0.07f;
					}
					else if (specialLevel ==
						GACHA_SPECIAL_JACKPOT)
					{
						popPower =
							0.11f;
					}

					drawZoom =
						CARD_FINAL_ZOOM *
						(1.0f +
							sinf(
								specialProgress *
								3.141592f) *
							popPower);

					//------------------------------------------------
					// 특수 연출 시작 효과음은 한 번만 재생
					//------------------------------------------------
					if (specialElapsed == 0)
					{
						if (specialLevel ==
							GACHA_SPECIAL_JACKPOT)
						{
							PlayMusic(
								M_KUNG);

							PlayMusic(
								M_CARDSPLIT);
						}
						else
						{
							PlayMusic(
								M_ITEM);
						}
					}
				}
			}

			card->x =
				drawCenterX;

			card->y =
				drawCenterY;

			card->zoom =
				drawZoom;

			card->zoom2 =
				drawZoom;

			card->manual =
				true;

			card->frame =
				1;

			card->frame2 =
				0;

			card->motionFrame++;

			//------------------------------------------------
			// 앞면이 보이는 동안에만 문구를 얹는다. 카드 위쪽에 세워서
			// 아이콘과 등급별을 가리지 않게 한다.
			//------------------------------------------------
			if (bannerAlpha >= 0 &&
				card->openFrame == 0 &&
				cardAnimFrame >= CARD_FLIP_END)
			{
				gachaAlphaBannerIdx =
					bannerAlpha;

				gachaAlphaBannerX =
					drawCenterX;

				gachaAlphaBannerY =
					drawCenterY +
					GACHA_BANNER_GAP_Y * drawZoom;

				//5성은 더 크게, 그리고 숨쉬듯 흔들리게 세운다.
				gachaAlphaBannerZoom =
					(bannerAlpha == ALPHA_LEGENDARY ?
						GACHA_BANNER_ZOOM_BIG :
						GACHA_BANNER_ZOOM) *
					drawZoom *
					(1.0f +
						sinf((float)(frame % 60) / 60.0f * 3.141592f * 2) *
						0.05f);
			}
		}

		//----------------------------------------------------
		// 앞면 공개 완료 후 다음 카드 허용
		//----------------------------------------------------
		if (manualCardMarkIdx >= 0)
		{
			ICONMARK* card =
				&boxCardMark[
					manualCardMarkIdx];

			//------------------------------------------------
			// [특수연출 수정 4]
			// 특수 연출이 끝난 뒤에만 다음 카드 터치를 허용
			//------------------------------------------------
			if (card->motionFrame >
				CARD_FLIP_END +
				specialHoldFrame +
				CARD_TOUCH_DELAY)
			{
				gachaCardCanAdvance =
					true;

				SetAlpha(
					32 -
					Abs(
						frame /
						MOTIONDIV %
						32 -
						16));

				DrawGoldAlpha(
					xOffset + DX / 2,
					BOTTOMMENUHEIGHT,
					ALPHA_TABTOCOLLECT,
					FONT_GOLD_LARGE,
					1,
					CENTER,
					false,
					false);

				SetAlpha(32);

				SetRectPoint(
					0,
					DY,
					DX,
					DY,
					TOUCH_FUNC_GETGACHACARD);
			}
		}


		//----------------------------------------------------
	// 카드 진행 중에도 터치 입력 등록
	//----------------------------------------------------
		if (manualCardMarkIdx >= 0 &&
			gachaOpenCardIdx >= 0 &&
			gachaOpenCardIdx < rewardCount)
		{
			SetRectPoint(
				0,
				DY,
				DX,
				DY,
				TOUCH_FUNC_GETGACHACARD);
		}

		break;
	}

	//--------------------------------------------------------
// 모든 보상 요약 화면
//--------------------------------------------------------
	case GACHA_DEPTH_SUMMARY:
	{
		//----------------------------------------------------
		// MENU_IMG 창
		//----------------------------------------------------
		const int PANEL_SRC_X =
			0;

		const int PANEL_SRC_Y =
			606;

		const int PANEL_SRC_W =
			400;

		const int PANEL_SRC_H =
			409;

		//----------------------------------------------------
		// MENU_IMG 확인 버튼
		//----------------------------------------------------
		const int BTN_SRC_X =
			401;

		const int BTN_SRC_Y =
			606;

		const int BTN_SRC_W =
			216;

		const int BTN_SRC_H =
			68;

		//----------------------------------------------------
		// 연출 프레임
		//----------------------------------------------------
		const int SUMMARY_ENTER_FRAME =
			14 * MOTIONDIV;

		const int SUMMARY_CARD_FRAME =
			16 * MOTIONDIV;

		const int SUMMARY_BUTTON_DELAY =
			4 * MOTIONDIV;

		const float PANEL_FINAL_ZOOM =
			1.6f;

		const float PANEL_START_ZOOM =
			0.20f;

		int rewardCount =
			boxCardItemCnt[0];

		if (rewardCount >
			GACHA_MAX_REWARD_CARD)
		{
			rewardCount =
				GACHA_MAX_REWARD_CARD;
		}

		//----------------------------------------------------
		// 요약 화면 최초 진입
		//----------------------------------------------------
		if (summaryFrame == 0)
		{
			manualCardMarkIdx =
				-1;

			gachaCurrentCardReady =
				false;

			gachaCardCanAdvance =
				false;

			gachaConfirmReady =
				false;

			memset(
				boxCardMark,
				0,
				sizeof(boxCardMark));

			for (i = 0;
				i < rewardCount;
				i++)
			{
				gachaRewardCardAnim[i].
					movingToPopup =
					true;

				gachaRewardCardAnim[i].
					arrivedPopup =
					false;

				gachaRewardCardAnim[i].
					moveFrame =
					0;
			}

			PlayMusic(M_CARDSPLIT);
		}

		//----------------------------------------------------
		// 팝업 확대율
		//----------------------------------------------------
		float panelProgress =
			(float)summaryFrame /
			(float)SUMMARY_ENTER_FRAME;

		panelProgress =
			GachaClamp01(
				panelProgress);

		float panelCurve =
			GachaEaseOutCubic(
				panelProgress);

		//----------------------------------------------------
		// 처음 약간 크게 넘어갔다가 복원
		//----------------------------------------------------
		float panelZoom;

		if (panelProgress < 0.75f)
		{
			float firstProgress =
				panelProgress /
				0.75f;

			panelZoom =
				GachaLerp(
					PANEL_START_ZOOM,
					PANEL_FINAL_ZOOM *
					1.05f,
					GachaEaseOutCubic(
						firstProgress));
		}
		else
		{
			float recoverProgress =
				(panelProgress -
					0.75f) /
				0.25f;

			panelZoom =
				GachaLerp(
					PANEL_FINAL_ZOOM *
					1.05f,
					PANEL_FINAL_ZOOM,
					recoverProgress);
		}

		float panelDisplayW =
			PANEL_SRC_W *
			panelZoom;

		float panelDisplayH =
			PANEL_SRC_H *
			panelZoom * 1.15f;

		float panelCX =
			xOffset +
			DX / 2.0f;

		float panelCY =
			DY / 2.0f + 24 * _2X;

		//----------------------------------------------------
		// 상자가 아래로 빠지는 연출
		//----------------------------------------------------
		float boxExitProgress =
			GachaEaseInOutCubic(
				panelProgress);

		float boxExitY =
			GachaLerp(
				BOTTOMMENUHEIGHT +
				32.0f * _2X,
				-300.0f * _2X,
				boxExitProgress);

		boxMark[0].y =
			boxExitY;

		boxMark[0].targetY2 =
			boxExitY;

		//----------------------------------------------------
		// 팝업 출력
		//----------------------------------------------------
		DrawImageScale(
			PANEL_SRC_W,
			PANEL_SRC_H,
			PANEL_SRC_X,
			PANEL_SRC_Y,

			panelCX -
			panelDisplayW /
			2.0f,

			panelCY +
			panelDisplayH /
			2.0f,

			false,
			false,
			false,
			false,
			false,

			panelZoom,
			panelZoom * 1.15f,

			sprite[MENU_IMG],
			MENU_IMG);

		//----------------------------------------------------
		// 리본 제목
		//
		// 창 그림 위쪽에 파란 리본이 붙어 있는데 글자가 없어서 비어 보였다.
		// 위치와 크기를 창 크기에서 뽑아 쓰므로 창이 커지거나 연출로
		// 확대되는 동안에도 리본 한가운데를 따라간다.
		//----------------------------------------------------
		{
			//창 그림의 윗변. 리본은 여기서부터 아래로 조금 내려온 자리에 있다.
			float panelTop =
				panelCY + panelDisplayH / 2.0f;

			//리본 한가운데까지의 거리(창 높이 대비)와 리본 안쪽 폭.
			const float TITLE_CENTER_RATIO = 0.058f;
			const float TITLE_WIDTH_RATIO = 0.68f;

			float titleY =
				panelTop - panelDisplayH * TITLE_CENTER_RATIO;

			float titleZoom =
				panelZoom * 1.1f;

			//리본을 넘치면 그만큼 줄인다. 글자가 길어지거나
			//다른 언어로 바뀌어도 리본 밖으로 안 나간다.
			float titleW =
				StringWidth(TEXTPTR(TEXT_GACHAREWARD_TITLE), titleZoom);

			float titleMaxW =
				panelDisplayW * TITLE_WIDTH_RATIO;

			if (titleW > titleMaxW && titleW > 0.0f)
				titleZoom *= titleMaxW / titleW;

			SetFontColor(COLOR_WHITE);

			//글자 높이의 절반만큼 올려야 리본 세로 한가운데에 온다.
			CenterText(TEXT_GACHAREWARD_TITLE,
				panelCX,
				titleY + (float)FONT_HEIGHT * titleZoom / 2.0f,
				titleZoom);
		}

		//----------------------------------------------------
		// 카드 배치
		//
		// 최대 4열 x 3행 = 12장 격자를 고정으로 잡고, 맨 윗줄 왼쪽부터 한 장씩 채운다.
		// 열 수를 장수에 맞춰 줄이면(2장이면 2열) 격자 폭이 달라져서 가운데로 몰리기 때문에
		// 장수와 무관하게 항상 최대 열 수를 쓴다. 그래야 왼쪽 시작 위치가 고정된다.
		//----------------------------------------------------
		const int POPUP_MAX_COLS =
			4;

		const int POPUP_MAX_ROWS =
			(GACHA_MAX_REWARD_CARD +
				POPUP_MAX_COLS -
				1) /
			POPUP_MAX_COLS;

		int numCols =
			POPUP_MAX_COLS;

		int numRows =
			(rewardCount +
				numCols -
				1) /
			numCols;

		//----------------------------------------------------
		// 팝업 최종 크기를 기준으로 카드 크기 계산
		//----------------------------------------------------
		float finalPanelW =
			PANEL_SRC_W *
			PANEL_FINAL_ZOOM;

		float finalPanelH =
			PANEL_SRC_H *
			PANEL_FINAL_ZOOM;

		float popupGapX =
			2.0f * _2X;

		float popupGapY =
			2.0f * _2X;

		float popupInnerW =
			finalPanelW *
			0.88f;

		float popupInnerH =
			finalPanelH *
			0.8f;

		//----------------------------------------------------
		// 카드 크기는 이번에 나온 장수와 무관하게 고정한다.
		//
		// 예전에는 numCols/numRows(= 실제 장수)로 맞춰서, 장수가 적으면 그만큼 카드가 커져
		// 창을 가득 채웠다(2장이면 거대하게, 12장이면 작게). 최대 구성인 12장(4열 x 3행)이
		// 들어갈 크기로 계산해두고 항상 그 값을 쓴다.
		//----------------------------------------------------
		float popupCardZoomByW =
			(popupInnerW -
				popupGapX *
				(POPUP_MAX_COLS - 1)) /
			(POPUP_MAX_COLS *
				240.0f);

		float popupCardZoomByH =
			(popupInnerH -
				popupGapY *
				(POPUP_MAX_ROWS - 1)) /
			(POPUP_MAX_ROWS *
				332.0f);

		float popupCardZoom =
			popupCardZoomByW;

		if (popupCardZoom >
			popupCardZoomByH)
		{
			popupCardZoom =
				popupCardZoomByH;
		}

		float popupCardW =
			240.0f *
			popupCardZoom;

		float popupCardH =
			332.0f *
			popupCardZoom;

		float popupGridW =
			numCols *
			popupCardW +
			(numCols - 1) *
			popupGapX;

		float popupGridH =
			numRows *
			popupCardH +
			(numRows - 1) *
			popupGapY;

		float popupGridStartX =
			panelCX -
			popupGridW /
			2.0f;

		//----------------------------------------------------
		// 팝업 중앙보다 약간 위에 카드 배치
		//----------------------------------------------------
		float popupGridTop =
			panelCY +
			finalPanelH *
			0.4f;

		bool allPopupCardsArrived =
			true;

		//----------------------------------------------------
		// 카드 이동 및 출력
		//----------------------------------------------------
		for (i = 0;
			i < rewardCount;
			i++)
		{
			int col =
				i %
				numCols;

			int row =
				i /
				numCols;

			float targetX =
				popupGridStartX +
				col *
				(popupCardW +
					popupGapX);

			float targetY =
				popupGridTop -
				row *
				(popupCardH +
					popupGapY);

			GACHA_REWARD_CARD_ANIM* anim =
				&gachaRewardCardAnim[i];

			anim->popupX =
				targetX;

			anim->popupY =
				targetY;

			anim->popupZoom =
				popupCardZoom;

			float drawX =
				targetX;

			float drawY =
				targetY;

			float drawZoom =
				popupCardZoom;

			if (anim->movingToPopup)
			{
				//------------------------------------------------
				// 팝업 자체가 어느 정도 보인 뒤 카드가 이동
				//------------------------------------------------
				int cardStartDelay =
					i *
					MOTIONDIV /
					2;

				int cardElapsed =
					summaryFrame -
					cardStartDelay;

				if (cardElapsed < 0)
				{
					cardElapsed =
						0;
				}

				float cardProgress =
					(float)cardElapsed /
					(float)SUMMARY_CARD_FRAME;

				cardProgress =
					GachaClamp01(
						cardProgress);

				float cardCurve =
					GachaEaseInOutCubic(
						cardProgress);

				drawX =
					GachaLerp(
						anim->trayX,
						targetX,
						cardCurve);

				float linearY =
					GachaLerp(
						anim->trayY,
						targetY,
						cardCurve);

				float arcY =
					sinf(
						cardProgress *
						3.141592f) *
					38.0f *
					_2X;

				drawY =
					linearY +
					arcY;

				drawZoom =
					GachaLerp(
						anim->trayZoom,
						popupCardZoom,
						GachaEaseOutCubic(
							cardProgress));

				if (cardProgress >=
					1.0f)
				{
					anim->movingToPopup =
						false;

					anim->arrivedPopup =
						true;

					drawX =
						targetX;

					drawY =
						targetY;

					drawZoom =
						popupCardZoom;
				}
			}

			if (anim->arrivedPopup == false)
			{
				allPopupCardsArrived =
					false;
			}

			ITEM* item =
				&boxCardItem[0][i];

			DrawItemCard(
				item->type,
				item->detail,
				item->grade,
				item->lv,
				item->count,
				false,
				(int)drawX,
				(int)drawY,
				false,
				drawZoom,
				false,
				0,
				0,
				true,
				0);
		}

		//----------------------------------------------------
		// 모든 카드가 박힌 후 확인 버튼 활성화
		//----------------------------------------------------
		if (allPopupCardsArrived &&
			summaryFrame >
			SUMMARY_CARD_FRAME +
			SUMMARY_BUTTON_DELAY)
		{
			gachaConfirmReady =
				true;

			float btnZoom =
				(100.0f * _2X) /
				BTN_SRC_W;

			float btnDisplayW =
				BTN_SRC_W *
				btnZoom;

			float btnDisplayH =
				BTN_SRC_H *
				btnZoom;

			float btnX =
				panelCX -
				btnDisplayW /
				2.0f;

			float btnY =
				panelCY -
				finalPanelH /
				2.0f + btnDisplayH
				- 4.0f *
				_2X;

			DrawImage(
				BTN_SRC_W,
				BTN_SRC_H,
				BTN_SRC_X,
				BTN_SRC_Y,
				btnX,
				btnY,
				false,
				false,
				false,
				false,
				false,
				btnZoom,
				sprite[MENU_IMG],
				MENU_IMG);

			CenterText(TEXT_CONFIRM, btnX + (float)BTN_SRC_W * btnZoom / 2, btnY - (float)BTN_SRC_H * btnZoom / 2 + (float)8 * _2X * btnZoom, 1.5f * btnZoom);

			SetAlpha(
				32 -
				Abs(
					frame /
					MOTIONDIV %
					32 -
					16));

			DrawGoldAlpha(
				(int)panelCX,
				BOTTOMMENUHEIGHT,
				ALPHA_TABTOCOLLECT,
				FONT_GOLD_LARGE,
				1,
				CENTER,
				false,
				false);

			SetAlpha(32);

			//------------------------------------------------
			// 화면 전체가 아니라 확인 버튼만 터치
			//------------------------------------------------
			SetRectPoint(
				(int)btnX,
				(int)(
					btnY +
					btnDisplayH),
				(int)(
					btnX +
					btnDisplayW),
				(int)btnY,
				TOUCH_FUNC_GETGACHACARD);
		}

		summaryFrame++;

		break;
	}

	//--------------------------------------------------------
	// 요약 카드가 하단 메뉴로 날아가는 연출
	//--------------------------------------------------------
	case GACHA_DEPTH_FLYTOBAR:
	{
		//----------------------------------------------------
		// 연출 시간
		//----------------------------------------------------
		const int PANEL_CLOSE_FRAME =
			FPS / 2;

		const int CARD_FLY_FRAME =
			FPS;

		const int CARD_GLOW_HOLD_FRAME =
			FPS;

		const int CARD_FADE_FRAME =
			FPS / 2;

		//----------------------------------------------------
		// 카드마다 약간씩 순차 출발
		//----------------------------------------------------
		const int CARD_START_INTERVAL =
			FPS / 6;

		//----------------------------------------------------
		// 도착했을 때 크기
		//
		// 팝업에서 보이던 크기의 20%
		//----------------------------------------------------
		const float CARD_TARGET_ZOOM_RATE =
			0.35f;

		//----------------------------------------------------
		// 팝업 정보
		//----------------------------------------------------
		const int PANEL_SRC_X =
			0;

		const int PANEL_SRC_Y =
			606;

		const int PANEL_SRC_W =
			400;

		const int PANEL_SRC_H =
			409;

		const float PANEL_FINAL_ZOOM =
			1.5f;

		float panelCX =
			xOffset +
			DX / 2.0f;

		float panelCY =
			DY / 2.0f;

		int rewardCount =
			boxCardItemCnt[0];

		if (rewardCount >
			GACHA_MAX_REWARD_CARD)
		{
			rewardCount =
				GACHA_MAX_REWARD_CARD;
		}

		//----------------------------------------------------
		// 최초 진입
		//----------------------------------------------------
		if (flyToBarFrame == 0)
		{
			gachaConfirmReady =
				false;

			for (i = 0;
				i < rewardCount;
				i++)
			{
				GACHA_REWARD_CARD_ANIM* anim =
					&gachaRewardCardAnim[i];

				ITEM* item =
					&boxCardItem[0][i];

				anim->movingToBar =
					true;

				anim->arrivedBar =
					false;

				anim->finishedBar =
					false;

				anim->barMoveFrame =
					0;

				anim->barHoldFrame =
					0;

				//------------------------------------------------
				// 팝업 안에 박혀 있던 위치에서 출발
				//------------------------------------------------
				anim->barStartX =
					anim->popupX;

				anim->barStartY =
					anim->popupY;

				anim->barStartZoom =
					anim->popupZoom;

				//------------------------------------------------
				// 하트와 골드는 카드째로 날리지 않는다
				//
				// 카드에 그려진 아이콘 자리에서 재화 마크를 쏟아 보낸다.
				// 상자를 열었을 때와 같은 연출이다(Func_Battle의 보상 처리 참고).
				// 개수는 수량/10이되 CURRENCYMARK_MAX개를 넘지 않는다.
				// 82만 골드를 8만 개로 쏟으면 마크 풀이 감당하지 못한다.
				//------------------------------------------------
				if (item->type == ITEM_GOLD ||
					item->type == ITEM_HEART)
				{
					//DrawItemCard이 아이콘을 놓는 자리와 같은 식으로 중심을 잡는다.
					const float CARD_ICON_X = 72.0f;
					const float CARD_ICON_Y = 122.0f;
					const float CARD_ICON_ZOOM = 3.3f;

					float iconHalf =
						(float)ITEMICONSIZE * CARD_ICON_ZOOM / 2.0f;

					float markX =
						anim->popupX +
						(CARD_ICON_X + iconHalf) * anim->popupZoom;

					float markY =
						anim->popupY -
						(CARD_ICON_Y + iconHalf) * anim->popupZoom;

					long long amount =
						item->count;

					int markCnt =
						(int)Min((long long)CURRENCYMARK_MAX,
							Max((long long)1, amount / 10));

					//값이 클수록 크게. 1000부터 자릿수가 하나 늘 때마다 한 단계씩
					//키우고 상한에서 멈춘다.
					float markScale =
						CURRENCYMARK_ZOOMBASE;

					for (long long v = amount; v >= 1000; v /= 10)
					{
						markScale += CURRENCYMARK_ZOOMSTEP;

						if (markScale >= CURRENCYMARK_ZOOMMAX)
						{
							markScale = CURRENCYMARK_ZOOMMAX;
							break;
						}
					}

					if (item->type == ITEM_GOLD)
					{
						//골드바의 동전 아이콘 자리. 바 좌표는 왼쪽 위라
						//아이콘 반만큼 안쪽으로 넣어야 한다.
						float goldX =
							bar[BAR_GOLD].x + 8 * _2X + ITEMICONSIZE / 2;

						float goldY =
							bar[BAR_GOLD].y - 8 * _2X - ITEMICONSIZE / 2;

						SetCurrencyMarkArr(markX, markY,
							goldX, goldY,
							goldX, goldY,
							16 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV,
							2 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV,
							CURRENCYWAITINGFRAMEMAX, CURRENCYWAITINGFRAMEMAX,
							ICON_GOLD, 30, amount, CURRENCY_GOLD,
							3.0f * markScale, 2.0f * markScale, -0.2f / MOTIONDIV,
							2.0f * markScale, 1.0f * markScale, -0.2f / MOTIONDIV,
							markCnt, BAR_GOLD);
					}
					else
					{
						//하트바의 하트 아이콘은 바 맨 왼쪽에 있다.
						//bar[].x는 바 한가운데이므로 바 길이의 절반만 왼쪽으로
						//가야 왼쪽 끝이다. 길이만큼 통째로 빼면 두 배로 넘어간다.
						float heartX =
							bar[BAR_HEART].x - HEARTBARWIDTH / 2 + ITEMICONSIZE / 2;

						float heartY =
							bar[BAR_HEART].y - 8 * _2X - ITEMICONSIZE / 2;

						SetCurrencyMarkArr(markX, markY,
							markX, markY,
							heartX, heartY,
							2 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV,
							16 * _2X / MOTIONDIV, 2 * _2X / MOTIONDIV,
							FPS / 2, FPS / 2,
							ICON_HEART, 30, amount, CURRENCY_HEART,
							2.0f * markScale, 3.0f * markScale, 0.2f / MOTIONDIV,
							3.0f * markScale, 1.5f * markScale, -0.2f / MOTIONDIV,
							markCnt, BAR_HEART);
					}

					//카드 자체는 더 이상 그리지도, 날리지도 않는다.
					anim->movingToBar = false;
					anim->arrivedBar = false;
					anim->finishedBar = true;

					continue;
				}

				//------------------------------------------------
				// 카드 종류별 도착 바 위치
				//------------------------------------------------
				float destinationCX =
					panelCX;

				float destinationCY =
					BOTTOMMENUHEIGHT;

				if (item->type ==
					ITEM_CREW)
				{
					destinationCX =
						bar[BAR_CREW].x;

					destinationCY =
						bar[BAR_CREW].y;
				}
				else if (item->type ==
					ITEM_HEART)
				{
					destinationCX =
						bar[BAR_HEART].x;

					destinationCY =
						bar[BAR_HEART].y;
				}
				else if (item->type ==
					ITEM_GOLD)
				{
					destinationCX =
						bar[BAR_GOLD].x;

					destinationCY =
						bar[BAR_GOLD].y;
				}
				else if (item->type <
					ITEM_NETITEM)
				{
					destinationCX =
						bar[BAR_EQUIP].x;

					destinationCY =
						bar[BAR_EQUIP].y;
				}

				//------------------------------------------------
				// 최종 카드 크기
				//------------------------------------------------
				anim->barTargetZoom =
					anim->barStartZoom *
					CARD_TARGET_ZOOM_RATE;

				//------------------------------------------------
				// DrawItemCard 좌표는 카드의 좌측 하단 기준
				//
				// bar 좌표는 중심점으로 보고 보정
				//------------------------------------------------
				anim->barTargetX =
					destinationCX -
					240.0f *
					anim->barTargetZoom /
					2.0f;

				anim->barTargetY =
					destinationCY +
					332.0f *
					anim->barTargetZoom /
					2.0f;
			}

			PlayMusic(M_ITEM);
		}

		//----------------------------------------------------
		// 팝업 닫힘 연출
		//----------------------------------------------------
		float panelCloseProgress =
			(float)flyToBarFrame /
			(float)PANEL_CLOSE_FRAME;

		panelCloseProgress =
			GachaClamp01(
				panelCloseProgress);

		float panelCloseCurve =
			GachaEaseInOutCubic(
				panelCloseProgress);

		float panelZoom =
			GachaLerp(
				PANEL_FINAL_ZOOM,
				0.0f,
				panelCloseCurve);

		//----------------------------------------------------
		// 팝업이 작아지는 동안만 출력
		//----------------------------------------------------
		if (panelZoom > 0.03f)
		{
			float panelDisplayW =
				PANEL_SRC_W *
				panelZoom;

			float panelDisplayH =
				PANEL_SRC_H *
				panelZoom;

			DrawImage(
				PANEL_SRC_W,
				PANEL_SRC_H,
				PANEL_SRC_X,
				PANEL_SRC_Y,

				panelCX -
				panelDisplayW /
				2.0f,

				panelCY +
				panelDisplayH /
				2.0f,

				false,
				false,
				false,
				false,
				false,

				panelZoom,

				sprite[MENU_IMG],
				MENU_IMG);
		}

		//----------------------------------------------------
		// 모든 카드의 최종 연출 완료 여부
		//----------------------------------------------------
		bool allCardsFinished =
			true;

		for (i = 0;
			i < rewardCount;
			i++)
		{
			GACHA_REWARD_CARD_ANIM* anim =
				&gachaRewardCardAnim[i];

			ITEM* item =
				&boxCardItem[0][i];

			//------------------------------------------------
			// 카드별 출발 지연
			//------------------------------------------------
			int startDelay =
				i *
				CARD_START_INTERVAL;

			int elapsedFrame =
				flyToBarFrame -
				startDelay;

			float drawX =
				anim->barStartX;

			float drawY =
				anim->barStartY;

			float drawZoom =
				anim->barStartZoom;

			//------------------------------------------------
			// 아직 출발 전
			//------------------------------------------------
			if (elapsedFrame < 0)
			{
				allCardsFinished =
					false;
			}

			//------------------------------------------------
			// 하단 바로 날아가는 중
			//------------------------------------------------
			else if (anim->movingToBar)
			{
				float progress =
					(float)elapsedFrame /
					(float)CARD_FLY_FRAME;

				progress =
					GachaClamp01(
						progress);

				float moveCurve =
					GachaEaseInOutCubic(
						progress);

				float zoomCurve =
					GachaEaseOutCubic(
						progress);

				drawX =
					GachaLerp(
						anim->barStartX,
						anim->barTargetX,
						moveCurve);

				//------------------------------------------------
				// 기본 Y 이동
				//------------------------------------------------
				float linearY =
					GachaLerp(
						anim->barStartY,
						anim->barTargetY,
						moveCurve);

				//------------------------------------------------
				// 이동 중 살짝 위로 솟는 포물선
				//------------------------------------------------
				float arcY =
					sinf(
						progress *
						3.141592f) *
					48.0f *
					_2X;

				drawY =
					linearY +
					arcY;

				drawZoom =
					GachaLerp(
						anim->barStartZoom,
						anim->barTargetZoom,
						zoomCurve);

				//------------------------------------------------
				// 목적지 도착
				//------------------------------------------------
				if (progress >= 1.0f)
				{
					anim->movingToBar =
						false;

					anim->arrivedBar =
						true;

					anim->barHoldFrame =
						0;

					drawX =
						anim->barTargetX;

					drawY =
						anim->barTargetY;

					drawZoom =
						anim->barTargetZoom;

					//------------------------------------------------
					// 메뉴에 들어가는 느낌을 주는 도착 효과음
					//------------------------------------------------
					PlayMusic(M_ITEM);
				}

				allCardsFinished =
					false;
			}

			//------------------------------------------------
			// 해당 바 위에서 잠시 정지
			//------------------------------------------------
			//------------------------------------------------
	// 해당 바 위에서 글로우와 함께 잠시 정지
	//------------------------------------------------
			else if (anim->arrivedBar)
			{
				drawX =
					anim->barTargetX;

				drawY =
					anim->barTargetY;

				drawZoom =
					anim->barTargetZoom;

				//------------------------------------------------
	// [추가]
	// 바에 도착해서 머무르기 시작하는 첫 프레임에
	// 해당 카드 보상을 실제 지급한다.
	//
	// barHoldFrame은 도착 직후 0이며,
	// 아래에서 매 프레임 증가하므로 정확히 한 번만 실행된다.
	//------------------------------------------------
				if (anim->barHoldFrame == 0)
				{
					GetItem(
						item->type,
						item->lv,
						item->detail,
						item->grade,
						item->count,
						false);

					//------------------------------------------------
					// 골드 및 하트 표시값 갱신
					//
					// 중요:
					// GetItem()이 이미 robin.gold/heart를 증가시키고
					// AddBar()는 표시 연출만 시작하는 구조여야 한다.
					//------------------------------------------------
					if (item->type == ITEM_GOLD)
					{
						AddBar(
							&bar[BAR_GOLD],
							item->count, BARFRAME);
					}
					else if (item->type == ITEM_HEART)
					{
						AddBar(
							&bar[BAR_HEART],
							item->count, BARFRAME);
					}

					//------------------------------------------------
					// 장비 획득 직후 가장 강한 장비 갱신
					//------------------------------------------------
					if (item->type != ITEM_CREW &&
						item->type != ITEM_GOLD &&
						item->type != ITEM_HEART &&
						item->type != ITEM_STAR &&
						item->type < ITEM_NETITEM)
					{
						//SetStrongestEquip(
						//	item->type,
						//	item->detail,
						//	item->grade);
					}

					//------------------------------------------------
					// 카드가 바에 흡수되는 순간의 효과음
					//------------------------------------------------
					PlayMusic(M_ITEM);
				}

				int totalFinishFrame =
					CARD_GLOW_HOLD_FRAME +
					CARD_FADE_FRAME;

				//------------------------------------------------
				// 1단계: 메뉴 위에서 글로우 유지
				//------------------------------------------------
				if (anim->barHoldFrame <
					CARD_GLOW_HOLD_FRAME)
				{
					//------------------------------------------------
					// 도착 직후 살짝 커졌다 돌아오는 팝 효과
					//------------------------------------------------
					float holdProgress =
						(float)anim->barHoldFrame /
						(float)CARD_GLOW_HOLD_FRAME;

					holdProgress =
						GachaClamp01(
							holdProgress);

					float popScale =
						sinf(
							holdProgress *
							3.141592f) *
						0.15f;

					drawZoom =
						anim->barTargetZoom *
						(1.0f + popScale);

					allCardsFinished =
						false;
				}

				//------------------------------------------------
				// 2단계: 잠시 머문 뒤 페이드아웃
				//------------------------------------------------
				else if (anim->barHoldFrame <
					totalFinishFrame)
				{
					float fadeProgress =
						(float)(
							anim->barHoldFrame -
							CARD_GLOW_HOLD_FRAME) /
						(float)CARD_FADE_FRAME;

					fadeProgress =
						GachaClamp01(
							fadeProgress);

					//------------------------------------------------
					// 사라질 때 조금 더 작아짐
					//------------------------------------------------
					drawZoom =
						GachaLerp(
							anim->barTargetZoom,
							anim->barTargetZoom *
							0.65f,
							fadeProgress);

					allCardsFinished =
						false;
				}

				//------------------------------------------------
				// 3단계: 완전히 제거
				//------------------------------------------------
				else
				{
					anim->arrivedBar =
						false;

					anim->finishedBar =
						true;
				}

				anim->barHoldFrame++;
			}

			//------------------------------------------------
	// 아직 사라지지 않은 카드만 출력
	//------------------------------------------------
			if (anim->finishedBar == false)
			{
				int cardAlpha =
					32;

				bool drawGlow =
					false;

				float glowZoom =
					drawZoom;

				//------------------------------------------------
				// 도착 후의 진행 상황
				//------------------------------------------------
				if (anim->arrivedBar)
				{
					//------------------------------------------------
					// 글로우 유지 구간
					//------------------------------------------------
					if (anim->barHoldFrame <
						CARD_GLOW_HOLD_FRAME)
					{
						drawGlow =
							true;

						//------------------------------------------------
						// 글로우 맥동
						//------------------------------------------------
						float glowPulse =
							0.5f +
							0.5f *
							sinf(
								(float)anim->barHoldFrame *
								0.45f);

						glowZoom =
							drawZoom *
							(1.12f +
								0.08f *
								glowPulse);
					}
					//------------------------------------------------
					// 페이드아웃 구간
					//------------------------------------------------
					else
					{
						float fadeProgress =
							(float)(
								anim->barHoldFrame -
								CARD_GLOW_HOLD_FRAME) /
							(float)CARD_FADE_FRAME;

						fadeProgress =
							GachaClamp01(
								fadeProgress);

						cardAlpha =
							(int)GachaLerp(
								32.0f,
								0.0f,
								fadeProgress);

						//------------------------------------------------
						// 페이드 초반까지는 글로우 유지
						//------------------------------------------------
						if (fadeProgress <
							0.65f)
						{
							drawGlow =
								true;

							glowZoom =
								drawZoom *
								1.14f;
						}
					}
				}

				//------------------------------------------------
				// 카드 뒤쪽 글로우
				//
				// 전용 글로우 이미지가 없으므로
				// 반투명 확대 카드를 여러 방향으로 겹쳐 표현
				//------------------------------------------------
				if (drawGlow)
				{
					SetAlpha(5);

					const float GLOW_OFFSET =
						1.5f * _2X;

					DrawItemCard(
						item->type,
						item->detail,
						item->grade,
						item->lv,
						item->count,
						false,
						(int)(drawX -
							GLOW_OFFSET),
						(int)drawY,
						false,
						glowZoom,
						false,
						0,
						0,
						true,
						0);

					DrawItemCard(
						item->type,
						item->detail,
						item->grade,
						item->lv,
						item->count,
						false,
						(int)(drawX +
							GLOW_OFFSET),
						(int)drawY,
						false,
						glowZoom,
						false,
						0,
						0,
						true,
						0);

					DrawItemCard(
						item->type,
						item->detail,
						item->grade,
						item->lv,
						item->count,
						false,
						(int)drawX,
						(int)(drawY +
							GLOW_OFFSET),
						false,
						glowZoom,
						false,
						0,
						0,
						true,
						0);
				}

				//------------------------------------------------
				// 실제 카드
				//------------------------------------------------
				SetAlpha(
					cardAlpha);

				DrawItemCard(
					item->type,
					item->detail,
					item->grade,
					item->lv,
					item->count,
					false,
					(int)drawX,
					(int)drawY,
					false,
					drawZoom,
					false,
					0,
					0,
					true,
					0);

				SetAlpha(32);
			}
		}

		//----------------------------------------------------
		// 모든 카드가 목적지에서 잠시 머문 후 사라짐
		//----------------------------------------------------
		if (allCardsFinished)
		{
			gachaDepth =
				GACHA_DEPTH_GETITEM;

			getItemFrame =
				0;

			previousGachaDepth =
				GACHA_DEPTH_FLYTOBAR;
		}

		flyToBarFrame++;

		break;
	}

	//--------------------------------------------------------
	// 보상 실제 지급
	//--------------------------------------------------------
	case GACHA_DEPTH_GETITEM:
	{
		if (gachaRewardReceived == false)
		{
			gachaRewardReceived =
				true;

			for (i = 0;
				i < boxCardItemCnt[0];
				i++)
			{
				ITEM* item =
					&boxCardItem[0][i];

				GetItem(
					item->type,
					item->lv,
					item->detail,
					item->grade,
					item->count,
					false);

				//튜토리얼에서 장착을 가르치기 전(DEMO_TUTORIAL_EQUIP)까지는 자동장착하지 않는다.
				//첫 상자에서 나온 것을 플레이어가 직접 장착해봐야 하는데, 자동으로 껴버리면
				//"장비창의 장착 버튼을 눌러보자" 안내가 할 일이 없어진다.
				if (item->type != ITEM_CREW &&
					item->type != ITEM_GOLD &&
					item->type != ITEM_HEART &&
					item->type != ITEM_STAR &&
					!(IsTutorialPlaying() && !robin.demoSeen[DEMO_TUTORIAL_EQUIP]))
				{
					SetStrongestEquip(
						item->type,
						item->detail,
						item->grade);
				}
			}

			PlayMusic(M_ITEM);
		}

		if (getItemFrame > FPS / 3)
		{
			gachaPrepared =
				false;

			manualCardMarkIdx =
				-1;

			previousOpenCardIdx =
				-1;

			trayCardCount =
				0;

			waitingForTrayComplete =
				false;

			flyToBarFrame =
				0;

			gachaCurrentCardReady =
				false;

			gachaCardCanAdvance =
				false;

			gachaConfirmReady =
				false;

			memset(
				gachaRewardCardAnim,
				0,
				sizeof(gachaRewardCardAnim));

			memset(controlMark, 0, sizeof(controlMark));

			OutOfGacha();
			robin.waveIdx++;
			robin.curWaveIdx = 0;
			memset(&robin.waveActive, 0, sizeof(robin.waveActive));
			bar[BAR_BOSSHP].max = GetTotalWaveHp(robin.waveIdx);
			return;
		}

		getItemFrame++;

		break;
	}
	}

	gachaFrame++;
}



bool IsGachaBigReward(const ITEM* item)
{
	if (item == NULL)
		return false;

	switch (item->type)
	{
	case ITEM_GOLD:
		return item->count >= 1000000;

	case ITEM_CREW:
		return item->grade >= 4;

	default:
		// 장비 아이템 범위는 프로젝트 상수에 맞게 조정
		if (item->type >= ITEM_SWORD &&
			item->grade >= 4)
		{
			return true;
		}

		break;
	}

	return false;
}

void DrawGachaItemEffect(
	const ITEM* item,
	float x,
	float y,
	int effectFrame)
{
	if (item == NULL)
		return;

	int effectImg = GACHA_IMG;
	float effectZoom = 1.0f;

	bool bigReward =
		IsGachaBigReward(item);

	if (bigReward)
	{
		effectImg = GACHA_IMG;

		effectZoom =
			1.1f +
			sin(effectFrame * 5) *
			0.08f;
	}
	else if (item->grade >= 5)
	{
		effectImg = GACHA_IMG;

		effectZoom =
			1.0f +
			sin(effectFrame * 4) *
			0.04f;
	}

	//--------------------------------------------------------
	// 카드 뒤 방사형 빛
	//--------------------------------------------------------
	DrawImage(
		512,
		512,

		0,
		0,

		x - 256.0f * effectZoom,
		y + 256.0f * effectZoom,

		false,
		false,
		false,
		false,
		false,

		effectZoom,

		sprite[effectImg],
		effectImg);

	//--------------------------------------------------------
	// 고가치 보상 테두리 효과
	//--------------------------------------------------------
	if (bigReward)
	{
		int GACHA_RIM_SIZE_X = 128 * _2X;
		int GACHA_RIM_SIZE_Y = 128 * _2X;

		float rimZoom =
			1.0f +
			sin(effectFrame * 6) *
			0.03f;

		DrawImage(
			GACHA_RIM_SIZE_X,
			GACHA_RIM_SIZE_Y,

			0,
			0,

			x -
			(float)GACHA_RIM_SIZE_X *
			rimZoom / 2,

			y +
			(float)GACHA_RIM_SIZE_Y *
			rimZoom / 2,

			false,
			false,
			false,
			false,
			false,

			rimZoom,

			sprite[GACHA_IMG],
			GACHA_IMG);
	}

	//--------------------------------------------------------
	// NEW는 SetBoxCardMark 마지막 인자로 이미 전달
	//--------------------------------------------------------
}

void GachaKey(void)
{
	if (gachaPrepared == false)
		return;

	//--------------------------------------------------------
	// 실제 프로젝트에서 터치 함수 체크를 쓴다면 활성화
	//--------------------------------------------------------
	//if (touchFunc != TOUCH_FUNC_GETGACHACARD)
	//	return;

	//--------------------------------------------------------
	// 실제 프로젝트에서 터치 업 조건을 쓴다면 활성화
	//--------------------------------------------------------
	//if (touchUp == false)
	//	return;

	//touchFunc = TOUCH_FUNC_NONE;

	switch (gachaDepth)
	{
		//--------------------------------------------------------
		// 카드 공개
		//--------------------------------------------------------
	case GACHA_DEPTH_CARD:
	{
		//----------------------------------------------------
		// 아직 첫 카드를 꺼내기 전
		//----------------------------------------------------
		if (gachaOpenCardIdx < 0)
		{
			if (gachaCardCanAdvance == false)
				break;

			gachaCardCanAdvance =
				false;

			gachaOpenCardIdx =
				0;

			gachaCurrentCardReady =
				false;

			gachaCardSkipRequested =
				false;

			break;
		}

		//----------------------------------------------------
		// 모든 카드 공개가 이미 끝난 상태
		//----------------------------------------------------
		if (gachaOpenCardIdx >=
			boxCardItemCnt[0])
		{
			break;
		}

		//----------------------------------------------------
		// 현재 카드 애니메이션이 진행 중이면
		// 다음 단계 끝으로 이동하도록 요청
		//----------------------------------------------------
		if (gachaCardCanAdvance == false)
		{
			if (manualCardMarkIdx >= 0)
			{
				gachaCardSkipRequested =
					true;
			}

			break;
		}

		//----------------------------------------------------
		// 앞면 공개와 특수 연출까지 끝난 상태
		//
		// 이번 터치로 현재 카드를 하단으로 보내고
		// 다음 카드를 준비한다.
		//----------------------------------------------------
		gachaCardCanAdvance =
			false;

		gachaCardSkipRequested =
			false;

		gachaOpenCardIdx++;

		gachaCurrentCardReady =
			false;

		break;
	}


	//--------------------------------------------------------
	// 최종 보상 팝업
	//--------------------------------------------------------
	case GACHA_DEPTH_SUMMARY:
	{
		if (gachaConfirmReady == false)
			break;

		gachaConfirmReady =
			false;

		//------------------------------------------------
		// 바로 아이템 지급 화면으로 넘어가지 않고
		// 카드가 각 메뉴 바로 날아가는 연출 시작
		//------------------------------------------------
		gachaDepth =
			GACHA_DEPTH_FLYTOBAR;

		break;
	}

	//--------------------------------------------------------
	// 카드가 메뉴로 날아가는 동안에는 입력 무시
	//--------------------------------------------------------
	case GACHA_DEPTH_FLYTOBAR:
	{
		break;
	}

	//--------------------------------------------------------
	// 지급 처리 중 입력 무시
	//--------------------------------------------------------
	case GACHA_DEPTH_GETITEM:
	{
		break;
	}
	}
}


