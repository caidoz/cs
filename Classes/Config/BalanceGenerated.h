#pragma once

//이 파일은 content/balance.tsv 에서 자동으로 났다.
//손으로 고치지 마라 - 다음 생성에서 지워진다.
//값을 고칠 곳은 content/balance.tsv (또는 content/balance.xlsx) 다.
//    python tools/content/make_balance.py


#ifndef _CONFIG_BALANCE_GENERATED_H_
#define _CONFIG_BALANCE_GENERATED_H_

//첫 몬스터의 체력. 보통 공격 열 대
#define WAVE_HP_BASE              330

//계단 하나마다 체력 배수(100 분). 35자루로 얻는 배수 270의 35제곱근
#define WAVE_HP_TIER_MUL          117

//계단 상한. 넘으면 long long 이 넘친다
#define WAVE_HP_MAX_TIER          120

//소보스 체력 배수
#define WAVE_HP_SUBBOSS_MUL       5

//중보스 체력 배수
#define WAVE_HP_MIDBOSS_MUL       10

//대보스 체력 배수
#define WAVE_HP_BIGBOSS_MUL       100

//소보스 크기(%). 체력 배수와 짝이다
#define WAVE_SIZE_SUBBOSS_PCT     120

//중보스 크기(%)
#define WAVE_SIZE_MIDBOSS_PCT     145

//대보스 크기(%). 넘으면 머리가 화면 밖으로 나간다
#define WAVE_SIZE_BIGBOSS_PCT     180

//처치 기본 골드
#define STAGE_KILL_GOLD           20

//체력 몇 점이 금화 하나인가. 올리면 전체 보상이 내려간다
#define STAGE_KILL_GOLD_HP_DIV    25

//출정 점수의 바닥값. 한 점이 한 칸이다
#define LOADOUT_BASE              10

//성 한 단계가 더 주는 점수
#define LOADOUT_PER_CASTLE        2

//창고 장비 크기값의 첫 품목
#define GEAR_UNIT_BASE            4

//부위 안 번호 하나당
#define GEAR_UNIT_STEP            2

//크기값 상한
#define GEAR_UNIT_MAX             40

//적 방어막 바닥값
#define STAGE_FOE_ARMOR_BASE      60

//적 방어 스탯 1 당 방어막
#define STAGE_FOE_ARMOR_PER       3

//방어구가 이만큼 쌓이면 피해가 절반
#define STAGE_ARMOR_SOFT          400

//에너지 상한의 바닥
#define HEART_MAX_BASE            20

//성 한 단계마다 에너지 상한
#define HEART_MAX_PER_CASTLE      1

//주기마다 차는 에너지
#define HEART_REGEN_BASE          1

//디버그 빌드의 에너지 상한
#define HEART_TEST_MAX            100

//방 안 사람의 화면 키(640 기준 픽셀)
#define CASTLE_ROOM_CREW_SCREEN_H 35.0f

//방 높이 중 사람 키(%)
#define CASTLE_ROOM_CREW_FILL_H   0.82f

//방 폭 중 사람들이 쓰는 몫(%)
#define CASTLE_ROOM_CREW_FILL_W   0.86f

//한 방에 설 수 있는 최대 인원
#define CASTLE_ROOM_CREW_PER_ROOM 7

//앞줄 뒷줄 몇 줄까지
#define CASTLE_ROOM_CREW_RANKS    2

//출정 준비 위로 성을 더 띄우는 몫(_2X 배)
#define STAGE_LOADOUT_HEADROOM    10

//가방에 올릴 수 있는 동료 수
#define PVP_GRID_CREW_MAX         3

#endif
