#pragma once

#ifndef _DEF_CREW_H_
#define _DEF_CREW_H_

typedef enum _crewDef {
	//동료들의 상태
	CREW_STATUS_NEUTRAL = 0,
	CREW_STATUS_CAST,//버프나 구체생성 모션
	CREW_STATUS_BUFF,//상대방이 버프를 받고 있는 중
	CREW_STATUS_SUMMON,//소환을 하는 경우
	CREW_STATUS_SUMMON_ATTACK,//소환된 캐릭이 공격하는 것

	CREW_ATTACK_NORMAL = 0,
	CREW_ATTACK_BUFF,
	CREW_ATTACK_SUMMON,

} CREWDEF;

#endif
