#pragma once
#include "../Def.h"

#ifndef _DATA_SKILL_H_
#define _DATA_SKILL_H_

//일단 슬롯에서 선택된 것 외에는 히어로가 공격을 할것이냐? 기본적으로 해주는게 좋을것 같은데.
// 

//6~20:증가율
//21~25:습득조건레벨 5단계, 26:스킬시전시 데이터
//27: 사운드->사거리
//28: 최대 히트카운트
//스킬이 몇성짜리인지 확인
//스킬이 하트 몇개 이상 베팅해야 나오는지 확인
extern const signed int* skillData;
enum { skillData_COUNT = 8787 };

extern const unsigned short* barrierEtcData;
enum { barrierEtcData_COUNT = 15 };

extern const unsigned short* berserkEtcData;
enum { berserkEtcData_COUNT = 15 };

extern const signed char* skillToStat;
enum { skillToStat_COUNT = 7 };

//GetAtk와 동기화 되어야 함
extern const unsigned char* skillDescMod;
enum { skillDescMod_COUNT = 27 };

//총탄 아이콘별로 날아가는 모양(CREWBULLETANI_*).
//순서는 crewBullet.png의 아이콘 순서(가로 16개씩)와 1:1이다.
//표에 없는 번호는 GetCrewBulletAni()가 NONE으로 처리하므로 뒤쪽은 비워둬도 된다.
//
//기준: 구르거나 휘둘러 던지는 단단한 물건은 SPIN, 물렁하거나 살아있는 것은 PULSE,
//방향이 뚜렷해서 돌면 어색한 것은 NONE.
extern const unsigned char* crewBulletAni;
enum { crewBulletAni_COUNT = 78 };
#endif