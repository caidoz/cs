#pragma once

#ifndef _CREW_LINES_H_
#define _CREW_LINES_H_

//---- 동료 계열과 승급 ----
//
//같은 동료 둘을 합쳐 올리는 방식은 버렸다. 동료 하나가 이미 여러 칸을
//먹는데 같은 것을 둘 들고 있어야 하면, 성 1~2 단계의 가방에서는 아예
//불가능하다. 재료는 1x1 이라 그 문제가 없다.
//
//그래서 승급은 이렇다.
//    같은 계열의 전용 정수를 별 수만큼 먹이면
//    그 계열에서 별이 1 높은 동료 중 하나가 나온다.
//
//어느 동료가 나올지는 고르지 못한다. 고정 사다리였다면 노리고 만들 수
//있는 대신, 같은 계열을 여러 번 키울 때마다 늘 같은 얼굴이 나와
//지루해진다. 계열마다 별 하나에 두셋이 서 있으므로 무작위가 낫다.
//
//표는 tools/crew/lines.py 가 만든다. 그 도구가 계열마다 별이 연속으로
//차 있는지도 같이 본다 - 중간에 빈 별이 있으면 재료를 들고도 그 자리에서
//멈춘다.

#include "CrewLines.inc"

//동료 번호가 맞는 자리인가. 표 밖을 읽으면 엉뚱한 계열이 나온다.
inline bool CrewIdxValid(int crewIdx)
{
	return crewIdx >= 0 && crewIdx < (int)(sizeof(kCrewLine) / sizeof(kCrewLine[0]));
}

inline int CrewLineOf(int crewIdx)
{
	return CrewIdxValid(crewIdx) ? (int)kCrewLine[crewIdx] : -1;
}

inline int CrewStarOf(int crewIdx)
{
	return CrewIdxValid(crewIdx) ? (int)kCrewStar[crewIdx] : 0;
}

//그 계열을 올리는 데 쓰는 정수. ITEM_ESSENCE 의 detail 이다.
inline int CrewLineEssence(int line)
{
	return line >= 0 && line < CREWLINE_CNT ? kCrewLineEssence[line] : -1;
}

//---- 값 ----
//
//별이 오를수록 더 많이 든다. 별 하나짜리를 올리는 데 둘, 다섯짜리를
//올리는 데 여섯이다. 윗 동료가 드물어야 하는데 재료 값이 평평하면
//맨 위까지 가는 길이 그냥 시간 문제가 된다.
inline int CrewUpgradeCost(int star)
{
	return star < 1 ? 0 : star + 1;
}

//---- 승급 결과 ----
//
//같은 계열에서 별이 1 높은 동료 중 하나를 고른다. roll 은 부르는 쪽이
//주는 아무 수다(Random 을 여기서 부르지 않는 것은, 이 헤더가 미리보기와
//실제 승급 양쪽에서 쓰이기 때문이다 - 미리보기가 주사위를 굴려 버리면
//보여 준 것과 다른 것이 나온다).
//
//맨 위에 선 동료는 올릴 데가 없어 -1 을 준다.
inline int CrewUpgradePick(int crewIdx, int roll)
{
	const int line = CrewLineOf(crewIdx);
	const int want = CrewStarOf(crewIdx) + 1;
	const int cnt = (int)(sizeof(kCrewLine) / sizeof(kCrewLine[0]));
	int n = 0;
	int i;

	if (line < 0 || want < 2)
		return -1;

	for (i = 0; i < cnt; i++)
		if ((int)kCrewLine[i] == line && (int)kCrewStar[i] == want)
			n++;

	if (n == 0)
		return -1;

	n = (roll < 0 ? -roll : roll) % n;
	for (i = 0; i < cnt; i++) {
		if ((int)kCrewLine[i] != line || (int)kCrewStar[i] != want)
			continue;
		if (n-- == 0)
			return i;
	}

	return -1;
}

//올릴 수 있는가. 보관함의 정수를 세기 전에, 애초에 위가 있는지부터 본다.
inline bool CrewCanUpgrade(int crewIdx)
{
	return CrewUpgradePick(crewIdx, 0) >= 0;
}

#endif
