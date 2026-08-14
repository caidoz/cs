#pragma once

#ifndef _DATA_CMF_H_
#define _DATA_CMF_H_
#include "../Def.h"
#include "../Cmf.h"

//CMF
const signed short c0mv[] = {
	//상태 데이터
	//SNAIL_NEUTRAL
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C3_N0, PO_C3_N0, PO_C3_N1, PO_C3_N1, PO_C3_N2, PO_C3_N2, PO_C3_N3, PO_C3_N3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c1mv[] = {
	//상태 데이터
	//SNAIL_NEUTRAL
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C3_N0, PO_C3_N0, PO_C3_N1, PO_C3_N1, PO_C3_N2, PO_C3_N2, PO_C3_N3, PO_C3_N3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c2mv[] = {
	//상태 데이터
	//SNAIL_NEUTRAL
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C3_N0, PO_C3_N0, PO_C3_N1, PO_C3_N1, PO_C3_N2, PO_C3_N2, PO_C3_N3, PO_C3_N3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c3mv[] = {
	//상태 데이터
	//SNAIL_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C3_N0, PO_C3_N0_1, PO_C3_N0_2, PO_C3_N0_3, PO_C3_N1, PO_C3_N1_1, PO_C3_N1_2, PO_C3_N1_3,
	PO_C3_N2, PO_C3_N2_N3_1, PO_C3_N2_N3_2, PO_C3_N2_N3_3, PO_C3_N3, PO_C3_N3_1, PO_C3_N3_2, PO_C3_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SNAIL_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_RANDOM,	//초기화 조건
	PO_C3_W0, PO_C3_W0_1, PO_C3_W0_2, PO_C3_W0_3, PO_C3_W1, PO_C3_W1_1, PO_C3_W1_2, PO_C3_W1_3,
	PO_C3_W2, PO_C3_W2_1, PO_C3_W2_2, PO_C3_W2_3, PO_C3_W3, PO_C3_W3_1, PO_C3_W3_2, PO_C3_W3_3,	//상태 프레임별 모션
	1, 1, 0 * _2X, 0 * _2X, 1, 1, 0 * _2X, 0 * _2X,
	1, 1, 0 * _2X, 0 * _2X, 1, 1, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SNAIL_MOVE_FAST
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C3_W0, PO_C3_W0_2, PO_C3_W1, PO_C3_W1_2, PO_C3_W2, PO_C3_W2_2, PO_C3_W3, PO_C3_W3_2,
	PO_C3_W0, PO_C3_W0_2, PO_C3_W1, PO_C3_W1_2, PO_C3_W2, PO_C3_W2_2, PO_C3_W3, PO_C3_W3_2,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SNAIL_ATTACK
	60,	//상태 프레임 카운트
	SET_DIR_PLAYER,	//초기화 조건
	PO_C3_A0, PO_C3_A0, PO_C3_A0_1, PO_C3_A0_1, PO_C3_A0_2, PO_C3_A0_2, PO_C3_A0_3, PO_C3_A0_3,
	PO_C3_A1, PO_C3_A1, PO_C3_A1, PO_C3_A1_1, PO_C3_A1_1, PO_C3_A1_1, PO_C3_A1_2, PO_C3_A1_2,
	PO_C3_A1_2, PO_C3_A1_3, PO_C3_A1_3, PO_C3_A1_3, PO_C3_A2, PO_C3_A2, PO_C3_A2, PO_C3_A2,
	PO_C3_A2, PO_C3_A2_1, PO_C3_A2_1, PO_C3_A2_1, PO_C3_A2_1, PO_C3_A2_1, PO_C3_A2_2, PO_C3_A2_2,
	PO_C3_A2_2, PO_C3_A2_2, PO_C3_A2_2, PO_C3_A2_3, PO_C3_A2_3, PO_C3_A2_3, PO_C3_A2_3, PO_C3_A2_3,
	PO_C3_A3, PO_C3_A3, PO_C3_A3, PO_C3_A3_1, PO_C3_A3_1, PO_C3_A3_1, PO_C3_A3_2, PO_C3_A3_2,
	PO_C3_A3_2, PO_C3_A3_3, PO_C3_A3_3, PO_C3_A3_3, PO_C3_A4, PO_C3_A4, PO_C3_A4, PO_C3_A4,
	PO_C3_A4, PO_C3_A4, PO_C3_A4, PO_C3_A4,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SNAIL_IN
	16,	//상태 프레임 카운트
	0,	//초기화 조건
	PO_C3_N2, PO_C3_N2_D0_1, PO_C3_N2_D0_2, PO_C3_N2_D0_3, PO_C3_D0, PO_C3_D0_D1_1, PO_C3_D0_D1_2, PO_C3_D0_D1_3,
	PO_C3_D1, PO_C3_D1_D2_1, PO_C3_D1_D2_2, PO_C3_D1_D2_3, PO_C3_D2, PO_C3_D2, PO_C3_D2, PO_C3_D2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SNAIL_HIDE
	8,	//상태 프레임 카운트
	RECOVER_HP,	//초기화 조건
	PO_C3_D2, PO_C3_D2, PO_C3_D2, PO_C3_D2, PO_C3_D2, PO_C3_D2, PO_C3_D2, PO_C3_D2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SNAIL_COME
	16,	//상태 프레임 카운트
	0,	//초기화 조건
	PO_C3_D2, PO_C3_D2_1, PO_C3_D2_2, PO_C3_D2_3, PO_C3_D1, PO_C3_D1_D0_1, PO_C3_D1_D0_2, PO_C3_D1_D0_3,
	PO_C3_D0, PO_C3_D0_N2_1, PO_C3_D0_N2_2, PO_C3_D0_N2_3, PO_C3_N2, PO_C3_N2, PO_C3_N2, PO_C3_N2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	SNAIL_NEUTRAL,	SNAIL_IN,	COMPARE_LESSHP,	20,	RANDOM,	20,
	SNAIL_NEUTRAL,	SNAIL_ATTACK,	DISTANCE_CHECK_XY,	3 * 8 + 2,	0,	0,
	SNAIL_NEUTRAL,	SNAIL_MOVE_FAST,	DISTANCE_CHECK_XY,	7 * 8 + 2,	0,	0,
	SNAIL_NEUTRAL,	SNAIL_MOVE,	COMPARE_FRAME,	8,	0,	0,
	SNAIL_MOVE,	SNAIL_IN,	COMPARE_LESSHP,	20,	RANDOM,	20,
	SNAIL_MOVE,	SNAIL_ATTACK,	DISTANCE_CHECK_XY,	3 * 8 + 2,	0,	0,
	SNAIL_MOVE,	SNAIL_MOVE_FAST,	DISTANCE_CHECK_XY,	7 * 8 + 3,	0,	0,
	SNAIL_MOVE,	SNAIL_NEUTRAL,	COMPARE_FRAME,	EQUAL_MAINFRAME,	RANDOM,	33,
	SNAIL_MOVE_FAST,	SNAIL_ATTACK,	DISTANCE_CHECK_XY,	3 * 8 + 2,	0,	0,
	SNAIL_MOVE_FAST,	SNAIL_MOVE,	DISTANCE_OUT_XY,	8 * 8 + 3,	0,	0,
	SNAIL_ATTACK,	SNAIL_MOVE_FAST,	DISTANCE_CHECK_XY,	4 * 8 + 2,	0,	0,
	SNAIL_ATTACK,	SNAIL_NEUTRAL,	0,	0,	0,	0,
	SNAIL_IN,	SNAIL_HIDE,	0,	0,	0,	0,
	SNAIL_HIDE,	SNAIL_COME,	COMPARE_MOREHP,	50,	0,	0,
	SNAIL_COME,	SNAIL_MOVE,	0,	0,	0,	0,
	-1,
};

const signed short c4mv[] = {
	//상태 데이터
	//TREE_STOP
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C4_N0, PO_C4_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//TREE_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C4_W0, PO_C4_W0_1, PO_C4_W0_2, PO_C4_W0_3, PO_C4_W1, PO_C4_W1_1, PO_C4_W1_2, PO_C4_W1_3,
	PO_C4_W2, PO_C4_W2_1, PO_C4_W2_2, PO_C4_W2_3, PO_C4_W3, PO_C4_W3_1, PO_C4_W3_2, PO_C4_W3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//TREE_NEUTRAL
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C4_N0, PO_C4_N0_1, PO_C4_N0_2, PO_C4_N0_3, PO_C4_N1, PO_C4_N1_1, PO_C4_N1_2, PO_C4_N1_3,
	PO_C4_N2, PO_C4_N2_1, PO_C4_N2_2, PO_C4_N2_3, PO_C4_N3, PO_C4_N3_1, PO_C4_N3_2, PO_C4_N3_3,
	PO_C4_N0, PO_C4_N0_1, PO_C4_N0_2, PO_C4_N0_3, PO_C4_N1, PO_C4_N1_1, PO_C4_N1_2, PO_C4_N1_3,
	PO_C4_N2, PO_C4_N2_1, PO_C4_N2_2, PO_C4_N2_3, PO_C4_N3, PO_C4_N3_1, PO_C4_N3_2, PO_C4_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//TREE_ATTACK
	56,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C4_A0, PO_C4_A0_1, PO_C4_A0_2, PO_C4_A0_3, PO_C4_A1, PO_C4_A1_1, PO_C4_A1_2, PO_C4_A1_3,
	PO_C4_A2, PO_C4_A2_1, PO_C4_A2_2, PO_C4_A2_3, PO_C4_A3, PO_C4_A3_1, PO_C4_A3_2, PO_C4_A3_3,
	PO_C4_A4, PO_C4_A4, PO_C4_A4, PO_C4_A4, PO_C4_A4_1, PO_C4_A4_1, PO_C4_A4_1, PO_C4_A4_1,
	PO_C4_A4_2, PO_C4_A4_2, PO_C4_A4_2, PO_C4_A4_2, PO_C4_A4_3, PO_C4_A4_3, PO_C4_A4_3, PO_C4_A4_3,
	PO_C4_A5, PO_C4_A5_1, PO_C4_A5_2, PO_C4_A5_3, PO_C4_A6, PO_C4_A6_1, PO_C4_A6_2, PO_C4_A6_3,
	PO_C4_A7, PO_C4_A7, PO_C4_A7, PO_C4_A7, PO_C4_A7, PO_C4_A7, PO_C4_A7, PO_C4_A7,
	PO_C4_A7, PO_C4_A7, PO_C4_A7, PO_C4_A7, PO_C4_A7, PO_C4_A7, PO_C4_A7, PO_C4_A7,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 4 * _2X, 4 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 4 * _2X, 4 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	TREE_STOP,	TREE_MOVE,	DISTANCE_CHECK_XY,	8 * 8 + 3,	0,	0,
	TREE_NEUTRAL,	TREE_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 3,	0,	0,
	TREE_NEUTRAL,	TREE_MOVE,	DISTANCE_CHECK_XY,	8 * 8 + 3,	0,	0,
	TREE_NEUTRAL,	TREE_STOP,	DISTANCE_OUT_XY,	8 * 8 + 3,	0,	0,
	TREE_MOVE,	TREE_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 3,	0,	0,
	TREE_MOVE,	TREE_STOP,	DISTANCE_OUT_XY,	8 * 8 + 3,	0,	0,
	TREE_ATTACK,	TREE_MOVE,	DISTANCE_OUT_XY,	4 * 8 + 3,	0,	0,
	TREE_ATTACK,	TREE_NEUTRAL,	0,	0,	0,	0,
	-1,
};

const signed short c5mv[] = {
	//상태 데이터
	//FROG_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C5_N0, PO_C5_N0_1, PO_C5_N0_2, PO_C5_N0_3, PO_C5_N1, PO_C5_N1_1, PO_C5_N1_2, PO_C5_N1_3,
	PO_C5_N2, PO_C5_N2_1, PO_C5_N2_2, PO_C5_N2_3, PO_C5_N3, PO_C5_N3, PO_C5_N3, PO_C5_N3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//FROG_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C5_W0, PO_C5_W0_1, PO_C5_W0_2, PO_C5_W0_3, PO_C5_W1, PO_C5_W1_1, PO_C5_W1_2, PO_C5_W1_3,
	PO_C5_W2, PO_C5_W2_1, PO_C5_W2_2, PO_C5_W2_3, PO_C5_W3, PO_C5_W3_1, PO_C5_W3_2, PO_C5_W3_3,	//상태 프레임별 모션
	1, 1, 0 * _2X, 0 * _2X, 1, 1, 0 * _2X, 0 * _2X,
	1, 1, 0 * _2X, 0 * _2X, 1, 1, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//FROG_JUMP
	72,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C5_J0, PO_C5_J0_1, PO_C5_J0_2, PO_C5_J0_3, PO_C5_J1, PO_C5_J1, PO_C5_J1, PO_C5_J1,
	PO_C5_J1, PO_C5_J1_1, PO_C5_J1_1, PO_C5_J1_1, PO_C5_J1_1, PO_C5_J1_2, PO_C5_J1_2, PO_C5_J1_2,
	PO_C5_J1_2, PO_C5_J1_2, PO_C5_J1_3, PO_C5_J1_3, PO_C5_J1_3, PO_C5_J1_3, PO_C5_J2, PO_C5_J2,
	PO_C5_J2, PO_C5_J2_1, PO_C5_J2_1, PO_C5_J2_1, PO_C5_J2_2, PO_C5_J2_2, PO_C5_J2_2, PO_C5_J2_3,
	PO_C5_J2_3, PO_C5_J2_3, PO_C5_J3, PO_C5_J3_2, PO_C5_J4, PO_C5_J4_2, PO_C5_J5, PO_C5_J5_2,
	PO_C5_LANDING0, PO_C5_LANDING0_2, PO_C5_LANDING1, PO_C5_LANDING1_2, PO_C5_LANDING2, PO_C5_LANDING2, PO_C5_LANDING2, PO_C5_LANDING2,
	PO_C5_LANDING2, PO_C5_LANDING2, PO_C5_LANDING2, PO_C5_LANDING2_1, PO_C5_LANDING2_1, PO_C5_LANDING2_1, PO_C5_LANDING2_1, PO_C5_LANDING2_1,
	PO_C5_LANDING2_1, PO_C5_LANDING2_2, PO_C5_LANDING2_2, PO_C5_LANDING2_2, PO_C5_LANDING2_2, PO_C5_LANDING2_2, PO_C5_LANDING2_2, PO_C5_LANDING2_2,
	PO_C5_LANDING2_3, PO_C5_LANDING2_3, PO_C5_LANDING2_3, PO_C5_LANDING2_3, PO_C5_LANDING2_3, PO_C5_LANDING2_3, PO_C5_LANDING3, PO_C5_LANDING3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 1 * _2X, 3,
	5, 5, 5, 5, 5, 5, 5, 5,
	1 * _2X, 3, 1 * _2X, 3, 1 * _2X, 3, 1 * _2X, 3,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 1 * _2X, 3, 0 * _2X, 0 * _2X, -1 * _2X, -3,
	0 * _2X, 0 * _2X, 1 * _2X, 3, 0 * _2X, 0 * _2X, -1 * _2X, -3,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 50 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//FROG_RETREAT
	44,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_OPPOSITE,	//초기화 조건
	PO_C5_J0, PO_C5_J0_1, PO_C5_J0_2, PO_C5_J0_3, PO_C5_J1, PO_C5_J1_1, PO_C5_J1_2, PO_C5_J1_3,
	PO_C5_J2, PO_C5_J2, PO_C5_J2, PO_C5_J2, PO_C5_J2, PO_C5_J2, PO_C5_J2_1, PO_C5_J2_1,
	PO_C5_J2_1, PO_C5_J2_1, PO_C5_J2_1, PO_C5_J2_1, PO_C5_J2_2, PO_C5_J2_2, PO_C5_J2_2, PO_C5_J2_2,
	PO_C5_J2_2, PO_C5_J2_2, PO_C5_J2_3, PO_C5_J2_3, PO_C5_J2_3, PO_C5_J2_3, PO_C5_J2_3, PO_C5_J2_3,
	PO_C5_J3, PO_C5_J3_1, PO_C5_J3_2, PO_C5_J3_3, PO_C5_J4, PO_C5_J4_1, PO_C5_J4_2, PO_C5_J4_3,
	PO_C5_J5, PO_C5_J5, PO_C5_J5, PO_C5_J5,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	50 * _2X, 0 * _2X, 50 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C5_LANDING0, PO_C5_LANDING0_2, PO_C5_LANDING1, PO_C5_LANDING1_2, PO_C5_LANDING2, PO_C5_LANDING2, PO_C5_LANDING2, PO_C5_LANDING2,
	PO_C5_LANDING2, PO_C5_LANDING2, PO_C5_LANDING2, PO_C5_LANDING2_1, PO_C5_LANDING2_1, PO_C5_LANDING2_1, PO_C5_LANDING2_1, PO_C5_LANDING2_1,
	PO_C5_LANDING2_1, PO_C5_LANDING2_2, PO_C5_LANDING2_2, PO_C5_LANDING2_2, PO_C5_LANDING2_2, PO_C5_LANDING2_2, PO_C5_LANDING2_2, PO_C5_LANDING2_2,
	PO_C5_LANDING2_3, PO_C5_LANDING2_3, PO_C5_LANDING2_3, PO_C5_LANDING2_3, PO_C5_LANDING2_3, PO_C5_LANDING2_3, PO_C5_LANDING3, PO_C5_LANDING3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 5, 5, 0 * _2X, 0 * _2X, -5, -5,
	0 * _2X, 0 * _2X, 5, 5, 0 * _2X, 0 * _2X, -5, -5,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	56,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C5_A0, PO_C5_A0, PO_C5_A0_1, PO_C5_A0_1, PO_C5_A0_2, PO_C5_A0_2, PO_C5_A0_3, PO_C5_A0_3,
	PO_C5_A1, PO_C5_A1, PO_C5_A1, PO_C5_A1, PO_C5_A1, PO_C5_A1, PO_C5_A1_1, PO_C5_A1_1,
	PO_C5_A1_1, PO_C5_A1_1, PO_C5_A1_1, PO_C5_A1_1, PO_C5_A1_2, PO_C5_A1_2, PO_C5_A1_2, PO_C5_A1_2,
	PO_C5_A1_2, PO_C5_A1_2, PO_C5_A1_3, PO_C5_A1_3, PO_C5_A1_3, PO_C5_A1_3, PO_C5_A1_3, PO_C5_A1_3,
	PO_C5_A2, PO_C5_A2, PO_C5_A2, PO_C5_A2, PO_C5_A2_1, PO_C5_A2_1, PO_C5_A2_1, PO_C5_A2_1,
	PO_C5_A2_2, PO_C5_A2_2, PO_C5_A2_2, PO_C5_A2_2, PO_C5_A2_3, PO_C5_A2_3, PO_C5_A2_3, PO_C5_A2_3,
	PO_C5_A1, PO_C5_A1, PO_C5_A1, PO_C5_A1, PO_C5_A1, PO_C5_A1, PO_C5_A1, PO_C5_A1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	FROG_NEUTRAL,	FROG_ATTACK,	0,	0,	RANDOM,	60,
	FROG_NEUTRAL,	FROG_JUMP,	DISTANCE_OUT_XY,	6 * 8 + 3,	RANDOM,	33,
	FROG_NEUTRAL,	FROG_RETREAT,	DISTANCE_CHECK_XY,	4 * 8 + 3,	RANDOM,	40,
	FROG_NEUTRAL,	FROG_MOVE,	0,	0,	0,	0,
	FROG_MOVE,	FROG_JUMP,	DISTANCE_OUT_XY,	6 * 8 + 3,	RANDOM,	33,
	FROG_MOVE,	FROG_RETREAT,	DISTANCE_CHECK_XY,	4 * 8 + 3,	RANDOM,	40,
	FROG_MOVE,	FROG_NEUTRAL,	0,	0,	RANDOM,	20,
	FROG_RETREAT,	FROG_LANDING,	0,	0,	0,	0,
	FROG_JUMP,	FROG_LANDING,	0,	0,	0,	0,
	FROG_LANDING,	FROG_NEUTRAL,	0,	0,	0,	0,
	FROG_ATTACK,	FROG_NEUTRAL,	0,	0,	0,	0,
	-1,
};

//ONEEYE
const signed short c6mv[] = {
	//상태 데이터
	//ONEEYE_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C6_N0, PO_C6_N0_1, PO_C6_N0_2, PO_C6_N0_3, PO_C6_N1, PO_C6_N1_1, PO_C6_N1_2, PO_C6_N1_3,
	PO_C6_N2, PO_C6_N2_1, PO_C6_N2_2, PO_C6_N2_3, PO_C6_N3, PO_C6_N3_1, PO_C6_N3_2, PO_C6_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ONEEYE_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C6_N0, PO_C6_N0_2, PO_C6_N1, PO_C6_N1_2, PO_C6_N2, PO_C6_N2_2, PO_C6_N3, PO_C6_N3_2,
	PO_C6_N0, PO_C6_N0_2, PO_C6_N1, PO_C6_N1_2, PO_C6_N2, PO_C6_N2_2, PO_C6_N3, PO_C6_N3_2,	//상태 프레임별 모션
	51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ONEEYE_PLAYER_MOVE
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C6_N0, PO_C6_N0, PO_C6_N0, PO_C6_N0, PO_C6_N0, PO_C6_N0_1, PO_C6_N0_1, PO_C6_N0_1,
	PO_C6_N0_1, PO_C6_N0_2, PO_C6_N0_2, PO_C6_N0_2, PO_C6_N0_2, PO_C6_N0_2, PO_C6_N0_3, PO_C6_N0_3,
	PO_C6_N0_3, PO_C6_N0_3, PO_C6_N1, PO_C6_N1_2, PO_C6_N2, PO_C6_N2_2, PO_C6_N3, PO_C6_N3_2,
	PO_C6_N0, PO_C6_N0_2, PO_C6_N1, PO_C6_N1_2, PO_C6_N2, PO_C6_N2_2, PO_C6_N3, PO_C6_N3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ONEEYE_PLAYER_MOVE
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C6_N0, PO_C6_N0, PO_C6_N0, PO_C6_N0, PO_C6_N0, PO_C6_N0_1, PO_C6_N0_1, PO_C6_N0_1,
	PO_C6_N0_1, PO_C6_N0_2, PO_C6_N0_2, PO_C6_N0_2, PO_C6_N0_2, PO_C6_N0_2, PO_C6_N0_3, PO_C6_N0_3,
	PO_C6_N0_3, PO_C6_N0_3, PO_C6_N1, PO_C6_N1_2, PO_C6_N2, PO_C6_N2_2, PO_C6_N3, PO_C6_N3_2,
	PO_C6_N0, PO_C6_N0_2, PO_C6_N1, PO_C6_N1_2, PO_C6_N2, PO_C6_N2_2, PO_C6_N3, PO_C6_N3_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	51 * _2X, 0 * _2X, 55 * _2X, 0 * _2X, 115, 0 * _2X, 55 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	ONEEYE_NEUTRAL,	ONEEYE_PLAYER_MOVE,	DISTANCE_CHECK_XY,	6 * 8 + 7,	0,	0,
	ONEEYE_NEUTRAL,	ONEEYE_MOVE,	COMPARE_FRAME,	10,	RANDOM,	30,
	ONEEYE_MOVE,	ONEEYE_PLAYER_MOVE,	DISTANCE_CHECK_XY,	6 * 8 + 7,	0,	0,
	ONEEYE_MOVE,	ONEEYE_NEUTRAL,	COMPARE_FRAME,	10,	RANDOM,	30,
	ONEEYE_PLAYER_MOVE,	ONEEYE_NEUTRAL,	0,	0,	0,	0,
	-1,
};

//SKELETON
const signed short c7mv[] = {
	//상태 데이터
	//SKELETON_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C7_N0, PO_C7_N0_1, PO_C7_N0_2, PO_C7_N0_3, PO_C7_N1, PO_C7_N1_1, PO_C7_N1_2, PO_C7_N1_3,
	PO_C7_N2, PO_C7_N2_1, PO_C7_N2_2, PO_C7_N2_3, PO_C7_N3, PO_C7_N3_1, PO_C7_N3_2, PO_C7_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SKELETON_MOVE
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_RANDOM,	//초기화 조건
	PO_C7_W0, PO_C7_W0_W1_1, PO_C7_W0_W1_2, PO_C7_W0_W1_3, PO_C7_W1, PO_C7_W1, PO_C7_W1_W2_1, PO_C7_W1_W2_1,
	PO_C7_W1_W2_2, PO_C7_W1_W2_2, PO_C7_W1_W2_3, PO_C7_W1_W2_3, PO_C7_W2, PO_C7_W2_W3_1, PO_C7_W2_W3_2, PO_C7_W2_W3_3,
	PO_C7_W3, PO_C7_W3, PO_C7_W3_W0_1, PO_C7_W3_W0_1, PO_C7_W3_W0_2, PO_C7_W3_W0_2, PO_C7_W3_W0_3, PO_C7_W3_W0_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SKELETON_MOVE_FAST
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C7_W0, PO_C7_W0_W1_2, PO_C7_W1, PO_C7_W1_W2_2, PO_C7_W2, PO_C7_W2_W3_2, PO_C7_W3, PO_C7_W3_W0_2,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SKELETON_ATTACK
	130,	//상태 프레임 카운트
	SET_DIR_PLAYER,	//초기화 조건
	PO_C7_A0, PO_C7_A0_2, PO_C7_A1, PO_C7_A1, PO_C7_A1, PO_C7_A1, PO_C7_A1, PO_C7_A1,
	PO_C7_A1_1, PO_C7_A1_1, PO_C7_A1_1, PO_C7_A1_1, PO_C7_A1_1, PO_C7_A1_2, PO_C7_A1_2, PO_C7_A1_2,
	PO_C7_A1_2, PO_C7_A1_2, PO_C7_A1_2, PO_C7_A1_3, PO_C7_A1_3, PO_C7_A1_3, PO_C7_A1_3, PO_C7_A1_3,
	PO_C7_A2, PO_C7_A2, PO_C7_A2, PO_C7_A2, PO_C7_A2, PO_C7_A2, PO_C7_A2, PO_C7_A2,
	PO_C7_A2, PO_C7_A2, PO_C7_A2, PO_C7_A2, PO_C7_A2, PO_C7_A2, PO_C7_A2, PO_C7_A2,
	PO_C7_A2, PO_C7_A2, PO_C7_A2, PO_C7_A2, PO_C7_A2, PO_C7_A2, PO_C7_A2_1, PO_C7_A2_1,
	PO_C7_A2_1, PO_C7_A2_1, PO_C7_A2_1, PO_C7_A2_1, PO_C7_A2_1, PO_C7_A2_1, PO_C7_A2_1, PO_C7_A2_1,
	PO_C7_A2_1, PO_C7_A2_1, PO_C7_A2_1, PO_C7_A2_1, PO_C7_A2_1, PO_C7_A2_1, PO_C7_A2_1, PO_C7_A2_1,
	PO_C7_A2_1, PO_C7_A2_1, PO_C7_A2_1, PO_C7_A2_2, PO_C7_A2_2, PO_C7_A2_2, PO_C7_A2_2, PO_C7_A2_2,
	PO_C7_A2_2, PO_C7_A2_2, PO_C7_A2_2, PO_C7_A2_2, PO_C7_A2_2, PO_C7_A2_2, PO_C7_A2_2, PO_C7_A2_2,
	PO_C7_A2_2, PO_C7_A2_2, PO_C7_A2_2, PO_C7_A2_2, PO_C7_A2_2, PO_C7_A2_2, PO_C7_A2_2, PO_C7_A2_2,
	PO_C7_A2_2, PO_C7_A2_3, PO_C7_A2_3, PO_C7_A2_3, PO_C7_A2_3, PO_C7_A2_3, PO_C7_A2_3, PO_C7_A2_3,
	PO_C7_A2_3, PO_C7_A2_3, PO_C7_A2_3, PO_C7_A2_3, PO_C7_A2_3, PO_C7_A2_3, PO_C7_A2_3, PO_C7_A2_3,
	PO_C7_A2_3, PO_C7_A2_3, PO_C7_A2_3, PO_C7_A2_3, PO_C7_A2_3, PO_C7_A2_3, PO_C7_A3, PO_C7_A3_1,
	PO_C7_A3_2, PO_C7_A3_3, PO_C7_A4, PO_C7_A4, PO_C7_A4, PO_C7_A4, PO_C7_A4_1, PO_C7_A4_1,
	PO_C7_A4_1, PO_C7_A4_1, PO_C7_A4_2, PO_C7_A4_2, PO_C7_A4_2, PO_C7_A4_2, PO_C7_A4_3, PO_C7_A4_3,
	PO_C7_A4_3, PO_C7_A4_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	4 * _2X, 4 * _2X, 1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	4 * _2X, 4 * _2X, 1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	12,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C7_W0, PO_C7_W0_W3_2, PO_C7_W3, PO_C7_W3_W2_1, PO_C7_W3_W2_2, PO_C7_W3_W2_3, PO_C7_W2, PO_C7_W2_W1_2,
	PO_C7_W1, PO_C7_W1_W0_1, PO_C7_W1_W0_2, PO_C7_W1_W0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	SKELETON_NEUTRAL,	SKELETON_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 4,	0,	0,
	SKELETON_NEUTRAL,	SKELETON_MOVE_FAST,	DISTANCE_CHECK_XY,	6 * 8 + 4,	0,	0,
	SKELETON_NEUTRAL,	SKELETON_MOVE,	COMPARE_FRAME,	16,	0,	0,
	SKELETON_MOVE,	SKELETON_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 4,	0,	0,
	SKELETON_MOVE,	SKELETON_MOVE_FAST,	DISTANCE_CHECK_XY,	6 * 8 + 4,	0,	0,
	SKELETON_MOVE,	SKELETON_NEUTRAL,	COMPARE_FRAME,	20,	RANDOM,	33,
	SKELETON_MOVE_FAST,	SKELETON_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 4,	0,	0,
	SKELETON_MOVE_FAST,	SKELETON_MOVE,	DISTANCE_OUT_XY,	6 * 8 + 4,	0,	0,
	SKELETON_ATTACK,	SKELETON_RETREAT,	0,	0,	RANDOM,	40,
	SKELETON_ATTACK,	SKELETON_MOVE_FAST,	DISTANCE_CHECK_XY,	4 * 8 + 4,	0,	0,
	SKELETON_ATTACK,	SKELETON_NEUTRAL,	DISTANCE_OUT_XY,	6 * 8 + 4,	0,	0,
	SKELETON_RETREAT,	SKELETON_MOVE_FAST,	DISTANCE_CHECK_XY,	8 * 8 + 4,	RANDOM,	40,
	SKELETON_RETREAT,	SKELETON_ATTACK,	DISTANCE_OUT_XY,	4 * 8 + 4,	0,	0,
	-1,
};

// X충돌에 의해 버그 발생 가능성 많음 - 추후 수정바랍니다.
const signed short c8mv[] = {
	//상태 데이터
	//LARVA_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C8_N0, PO_C8_N0_1, PO_C8_N0_2, PO_C8_N0_3, PO_C8_N1, PO_C8_N1_1, PO_C8_N1_2, PO_C8_N1_3,
	PO_C8_N2, PO_C8_N2_1, PO_C8_N2_2, PO_C8_N2_3, PO_C8_N3, PO_C8_N3, PO_C8_N3, PO_C8_N3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LARVA_APPERAR
	46,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C8_D5, PO_C8_D5_1, PO_C8_D5_2, PO_C8_D5_3, PO_C8_D6, PO_C8_D6_D7_1, PO_C8_D6_D7_2, PO_C8_D6_D7_3,
	PO_C8_D7, PO_C8_D7_1, PO_C8_D7_2, PO_C8_D7_3, PO_C8_D6, PO_C8_D6_D5_1, PO_C8_D6_D5_2, PO_C8_D6_D5_3,
	PO_C8_D5, PO_C8_D5_1, PO_C8_D5_2, PO_C8_D5_3, PO_C8_D6, PO_C8_D6_D7_1, PO_C8_D6_D7_2, PO_C8_D6_D7_3,
	PO_C8_D7, PO_C8_D7_1, PO_C8_D7_2, PO_C8_D7_3, PO_C8_D6, PO_C8_D6_U0_1, PO_C8_D6_U0_2, PO_C8_D6_U0_3,
	PO_C8_U0, PO_C8_U0_2, PO_C8_U1, PO_C8_U1_2, PO_C8_U2, PO_C8_U2_2, PO_C8_U3, PO_C8_U3_2,
	PO_C8_U4, PO_C8_U4_2, PO_C8_U5, PO_C8_U5, PO_C8_U5, PO_C8_U5,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LARVA_HIDE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C8_D0, PO_C8_D0_2, PO_C8_D1, PO_C8_D1_2, PO_C8_D2, PO_C8_D2_2, PO_C8_D3, PO_C8_D3_2,
	PO_C8_D4, PO_C8_D4_2, PO_C8_D5, PO_C8_D5_2, PO_C8_D6, PO_C8_D6_D7_2, PO_C8_D7, PO_C8_D7,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LARVA_HIDED
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C8_D7, PO_C8_D7,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LARVA_ATTACK
	72,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C8_A0, PO_C8_A0_2, PO_C8_A1, PO_C8_A1, PO_C8_A1, PO_C8_A1, PO_C8_A1, PO_C8_A1,
	PO_C8_A1, PO_C8_A1, PO_C8_A1, PO_C8_A1, PO_C8_A1_A2_1, PO_C8_A1_A2_1, PO_C8_A1_A2_1, PO_C8_A1_A2_1,
	PO_C8_A1_A2_1, PO_C8_A1_A2_1, PO_C8_A1_A2_1, PO_C8_A1_A2_1, PO_C8_A1_A2_1, PO_C8_A1_A2_2, PO_C8_A1_A2_2, PO_C8_A1_A2_2,
	PO_C8_A1_A2_2, PO_C8_A1_A2_2, PO_C8_A1_A2_2, PO_C8_A1_A2_2, PO_C8_A1_A2_2, PO_C8_A1_A2_2, PO_C8_A1_A2_2, PO_C8_A1_A2_3,
	PO_C8_A1_A2_3, PO_C8_A1_A2_3, PO_C8_A1_A2_3, PO_C8_A1_A2_3, PO_C8_A1_A2_3, PO_C8_A1_A2_3, PO_C8_A1_A2_3, PO_C8_A1_A2_3,
	PO_C8_A2, PO_C8_A2_1, PO_C8_A2_2, PO_C8_A2_3, PO_C8_A3, PO_C8_A3_A2_1, PO_C8_A3_A2_2, PO_C8_A3_A2_3,
	PO_C8_A2, PO_C8_A2_1, PO_C8_A2_2, PO_C8_A2_3, PO_C8_A3, PO_C8_A3_A2_1, PO_C8_A3_A2_2, PO_C8_A3_A2_3,
	PO_C8_A2, PO_C8_A2_1, PO_C8_A2_2, PO_C8_A2_3, PO_C8_A3, PO_C8_A3_A1_1, PO_C8_A3_A1_2, PO_C8_A3_A1_3,
	PO_C8_A1, PO_C8_A1_A0_2, PO_C8_A0, PO_C8_A0, PO_C8_A0, PO_C8_A0, PO_C8_A0, PO_C8_A0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LARVA_SHOT
	80,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C8_SR0, PO_C8_SR0_2, PO_C8_SR1, PO_C8_SR1, PO_C8_SR1, PO_C8_SR1, PO_C8_SR1, PO_C8_SR1,
	PO_C8_SR1, PO_C8_SR1, PO_C8_SR1, PO_C8_SR1_1, PO_C8_SR1_1, PO_C8_SR1_1, PO_C8_SR1_1, PO_C8_SR1_1,
	PO_C8_SR1_1, PO_C8_SR1_1, PO_C8_SR1_1, PO_C8_SR1_2, PO_C8_SR1_2, PO_C8_SR1_2, PO_C8_SR1_2, PO_C8_SR1_2,
	PO_C8_SR1_2, PO_C8_SR1_2, PO_C8_SR1_2, PO_C8_SR1_2, PO_C8_SR1_3, PO_C8_SR1_3, PO_C8_SR1_3, PO_C8_SR1_3,
	PO_C8_SR1_3, PO_C8_SR1_3, PO_C8_SR1_3, PO_C8_SR1_3, PO_C8_SR2, PO_C8_SR2_2, PO_C8_SR3, PO_C8_SR3_2,
	PO_C8_S0, PO_C8_S0_2, PO_C8_S1, PO_C8_S1_1, PO_C8_S1_2, PO_C8_S1_3, PO_C8_S2, PO_C8_S2_2,
	PO_C8_S3, PO_C8_S3_2, PO_C8_S4, PO_C8_S4_2, PO_C8_S5, PO_C8_S5_S2_1, PO_C8_S5_S2_2, PO_C8_S5_S2_3,
	PO_C8_S2, PO_C8_S2_2, PO_C8_S3, PO_C8_S3_2, PO_C8_S4, PO_C8_S4_2, PO_C8_S5, PO_C8_S5_S2_1,
	PO_C8_S5_S2_2, PO_C8_S5_S2_3, PO_C8_S2, PO_C8_S2_2, PO_C8_S3, PO_C8_S3_2, PO_C8_S4, PO_C8_S4_2,
	PO_C8_S5, PO_C8_S5_S1_1, PO_C8_S5_S1_2, PO_C8_S5_S1_3, PO_C8_S1, PO_C8_S1, PO_C8_S1, PO_C8_S1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	LARVA_NEUTRAL,	LARVA_SHOT,	DISTANCE_CHECK_XY,	10 * 8 + 4,	RANDOM,	40,
	LARVA_NEUTRAL,	LARVA_ATTACK,	DISTANCE_CHECK_XY,	8 * 8 + 4,	RANDOM,	80,
	LARVA_NEUTRAL,	LARVA_HIDE,	0,	0,	0,	0,
	LARVA_APPEAR,	LARVA_NEUTRAL,	0,	0,	0,	0,
	LARVA_HIDE,	LARVA_HIDED,	0,	0,	0,	0,
	LARVA_HIDED,	LARVA_APPEAR,	0,	0,	RANDOM,	15,
	LARVA_ATTACK,	LARVA_NEUTRAL,	0,	0,	0,	0,
	LARVA_SHOT,	LARVA_NEUTRAL,	0,	0,	0,	0,
	-1,
};


//JELLYFISH
const signed short c9mv[] = {
	//상태 데이터
	//JELLYFISH_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C9_D0, PO_C9_D0, PO_C9_D0_1, PO_C9_D0_1, PO_C9_D0_2, PO_C9_D0_2, PO_C9_D0_3, PO_C9_D0_3,
	PO_C9_D1, PO_C9_D1, PO_C9_D1_D0_1, PO_C9_D1_D0_1, PO_C9_D1_D0_2, PO_C9_D1_D0_2, PO_C9_D1_D0_3, PO_C9_D1_D0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	101, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	40,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_RANDOM,	//초기화 조건
	PO_C9_D0, PO_C9_D0_1, PO_C9_D0_2, PO_C9_D0_3, PO_C9_D1, PO_C9_D1_U0_1, PO_C9_D1_U0_2, PO_C9_D1_U0_3,
	PO_C9_U0, PO_C9_U0_1, PO_C9_U0_2, PO_C9_U0_3, PO_C9_U1, PO_C9_U1_U0_1, PO_C9_U1_U0_2, PO_C9_U1_U0_3,
	PO_C9_U0, PO_C9_U0_1, PO_C9_U0_2, PO_C9_U0_3, PO_C9_U1, PO_C9_U1_N0_1, PO_C9_U1_N0_2, PO_C9_U1_N0_3,
	PO_C9_N0, PO_C9_N0, PO_C9_N0, PO_C9_N0, PO_C9_N0_1, PO_C9_N0_1, PO_C9_N0_1, PO_C9_N0_1,
	PO_C9_N0_2, PO_C9_N0_2, PO_C9_N0_2, PO_C9_N0_2, PO_C9_N0_3, PO_C9_N0_3, PO_C9_N0_3, PO_C9_N0_3,	//상태 프레임별 모션
	0 * _2X, 1, 0 * _2X, 1, 0 * _2X, 1, 0 * _2X, 1,
	0 * _2X, 1, 0 * _2X, 1, 0 * _2X, 1, 0 * _2X, 1,
	0 * _2X, 1, 0 * _2X, 1, 0 * _2X, 1, 0 * _2X, 1,
	0 * _2X, 1, 0 * _2X, 1, 0 * _2X, 1, 0 * _2X, 1,
	0 * _2X, 1, 0 * _2X, 1, 0 * _2X, 1, 0 * _2X, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	101, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C9_D0, PO_C9_D0_2, PO_C9_D1, PO_C9_D1_U0_2, PO_C9_U0, PO_C9_U0_2, PO_C9_U1, PO_C9_U1_U0_2,
	PO_C9_U0, PO_C9_U0_2, PO_C9_U1, PO_C9_U1_N0_2, PO_C9_N0, PO_C9_N0, PO_C9_N0, PO_C9_N0,
	PO_C9_N0, PO_C9_N0, PO_C9_N0, PO_C9_N0, PO_C9_N0, PO_C9_N0, PO_C9_N0, PO_C9_N0,
	PO_C9_N0, PO_C9_N0, PO_C9_N0, PO_C9_N0, PO_C9_N0, PO_C9_N0, PO_C9_N0, PO_C9_N0,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 50 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	JELLYFISH_NEUTRAL,	JELLYFISH_MOVE_FAST,	DISTANCE_CHECK_XY,	6 * 8 + 5,	0,	0,
	JELLYFISH_NEUTRAL,	JELLYFISH_MOVE,	0,	0,	RANDOM,	40,
	JELLYFISH_MOVE,	JELLYFISH_MOVE_FAST,	DISTANCE_CHECK_XY,	6 * 8 + 5,	0,	0,
	JELLYFISH_MOVE,	JELLYFISH_NEUTRAL,	0,	0,	RANDOM,	50,
	JELLYFISH_MOVE_FAST,	JELLYFISH_NEUTRAL,	0,	0,	0,	0,
	-1,
};


//LIZARD
const signed short c10mv[] = {
	//상태 데이터
	//LIZARD_NEUTRAL
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C10_N0, PO_C10_N0_1, PO_C10_N0_2, PO_C10_N0_3, PO_C10_N1, PO_C10_N1_N2_1, PO_C10_N1_N2_2, PO_C10_N1_N2_3,
	PO_C10_N2, PO_C10_N2_N3_1, PO_C10_N2_N3_2, PO_C10_N2_N3_3, PO_C10_N3, PO_C10_N3_1, PO_C10_N3_2, PO_C10_N3_3,
	PO_C10_N2, PO_C10_N2_N1_1, PO_C10_N2_N1_2, PO_C10_N2_N1_3, PO_C10_N1, PO_C10_N1_N0_1, PO_C10_N1_N0_2, PO_C10_N1_N0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LIZARD_MOVE
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_RANDOM,	//초기화 조건
	PO_C10_W0, PO_C10_W0_W1_1, PO_C10_W0_W1_2, PO_C10_W0_W1_3, PO_C10_W1, PO_C10_W1, PO_C10_W1_W2_1, PO_C10_W1_W2_1,
	PO_C10_W1_W2_2, PO_C10_W1_W2_2, PO_C10_W1_W2_3, PO_C10_W1_W2_3, PO_C10_W2, PO_C10_W2_W3_1, PO_C10_W2_W3_2, PO_C10_W2_W3_3,
	PO_C10_W3, PO_C10_W3, PO_C10_W3_W0_1, PO_C10_W3_W0_1, PO_C10_W3_W0_2, PO_C10_W3_W0_2, PO_C10_W3_W0_3, PO_C10_W3_W0_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LIZARD_MOVE_FAST
	12,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C10_W0, PO_C10_W0_W1_2, PO_C10_W1, PO_C10_W1_W2_1, PO_C10_W1_W2_2, PO_C10_W1_W2_3, PO_C10_W2, PO_C10_W2_W3_2,
	PO_C10_W3, PO_C10_W3_W0_1, PO_C10_W3_W0_2, PO_C10_W3_W0_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LIZARD_ATTACK
	40,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C10_A0, PO_C10_A0_2, PO_C10_A1, PO_C10_A1, PO_C10_A1, PO_C10_A1, PO_C10_A1, PO_C10_A1_1,
	PO_C10_A1_1, PO_C10_A1_1, PO_C10_A1_1, PO_C10_A1_2, PO_C10_A1_2, PO_C10_A1_2, PO_C10_A1_2, PO_C10_A1_2,
	PO_C10_A1_3, PO_C10_A1_3, PO_C10_A1_3, PO_C10_A1_3, PO_C10_A2, PO_C10_A2_1, PO_C10_A2_2, PO_C10_A2_3,
	PO_C10_A3, PO_C10_A3_1, PO_C10_A3_2, PO_C10_A3_3, PO_C10_A4, PO_C10_A4, PO_C10_A4, PO_C10_A4,
	PO_C10_A4, PO_C10_A4, PO_C10_A4, PO_C10_A4, PO_C10_A4, PO_C10_A4, PO_C10_A4, PO_C10_A4,	//상태 프레임별 모션
	-1 * _2X, -1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 2 * _2X, 2 * _2X,
	1 * _2X, 1 * _2X, 1, 1, 2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_OPPOSITE,	//초기화 조건
	PO_C10_W3, PO_C10_W3_W2_2, PO_C10_W2, PO_C10_W2_W1_2, PO_C10_W1, PO_C10_W1_W0_2, PO_C10_W0, PO_C10_W0_W3_2,	//상태 프레임별 모션
	3, 3, 3, 3, 1 * _2X, 1 * _2X, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	LIZARD_NEUTRAL,	LIZARD_RETREAT,	DISTANCE_CHECK_XY,	4 * 8 + 2,	RANDOM,	40,
	LIZARD_NEUTRAL,	LIZARD_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 3,	0,	0,
	LIZARD_NEUTRAL,	LIZARD_MOVE_FAST,	DISTANCE_CHECK_XY,	6 * 8 + 4,	0,	0,
	LIZARD_NEUTRAL,	LIZARD_MOVE,	DISTANCE_OUT_XY,	8 * 8 + 5,	0,	0,
	LIZARD_MOVE,	LIZARD_RETREAT,	DISTANCE_CHECK_XY,	4 * 8 + 2,	RANDOM,	40,
	LIZARD_MOVE,	LIZARD_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 3,	0,	0,
	LIZARD_MOVE,	LIZARD_MOVE_FAST,	DISTANCE_CHECK_XY,	6 * 8 + 4,	0,	0,
	LIZARD_MOVE,	LIZARD_MOVE,	DISTANCE_OUT_XY,	8 * 8 + 5,	0,	0,
	LIZARD_MOVE_FAST,	LIZARD_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 3,	0,	0,
	LIZARD_MOVE_FAST,	LIZARD_MOVE,	DISTANCE_OUT_XY,	8 * 8 + 5,	0,	0,
	LIZARD_ATTACK,	LIZARD_MOVE,	DISTANCE_CHECK_XY,	4 * 8 + 2,	0,	0,
	LIZARD_ATTACK,	LIZARD_NEUTRAL,	0,	0,	0,	0,
	LIZARD_RETREAT,	LIZARD_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 4,	RANDOM,	40,
	LIZARD_RETREAT,	LIZARD_NEUTRAL,	DISTANCE_OUT_XY,	8 * 8 + 4,	0,	0,
	-1,
};


//SALAMANDER --BOSS--
const signed short c11mv[] = {
	//상태 데이터
	//SALAMANDER_NEUTRAL
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C11_N0, PO_C11_N0_N1_1, PO_C11_N0_N1_2, PO_C11_N0_N1_3, PO_C11_N1, PO_C11_N1_N2_1, PO_C11_N1_N2_2, PO_C11_N1_N2_3,
	PO_C11_N2, PO_C11_N2_N3_1, PO_C11_N2_N3_2, PO_C11_N2_N3_3, PO_C11_N3, PO_C11_N3, PO_C11_N3_1, PO_C11_N3_1,
	PO_C11_N3_2, PO_C11_N3_2, PO_C11_N3_3, PO_C11_N3_3, PO_C11_N2, PO_C11_N2_N1_1, PO_C11_N2_N1_2, PO_C11_N2_N1_3,
	PO_C11_N1, PO_C11_N1_N0_1, PO_C11_N1_N0_2, PO_C11_N1_N0_3, PO_C11_N0, PO_C11_N0, PO_C11_N0, PO_C11_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SALAMANDER_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C11_W0, PO_C11_W0_1, PO_C11_W0_2, PO_C11_W0_3, PO_C11_W1, PO_C11_W1_1, PO_C11_W1_2, PO_C11_W1_3,
	PO_C11_W2, PO_C11_W2_1, PO_C11_W2_2, PO_C11_W2_3, PO_C11_W3, PO_C11_W3_1, PO_C11_W3_2, PO_C11_W3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	60,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C11_N0, PO_C11_N0, PO_C11_N0, PO_C11_N0, PO_C11_N0_A0_1, PO_C11_N0_A0_1, PO_C11_N0_A0_1, PO_C11_N0_A0_1,
	PO_C11_N0_A0_2, PO_C11_N0_A0_2, PO_C11_N0_A0_2, PO_C11_N0_A0_2, PO_C11_N0_A0_3, PO_C11_N0_A0_3, PO_C11_N0_A0_3, PO_C11_N0_A0_3,
	PO_C11_A0, PO_C11_A0_2, PO_C11_A1, PO_C11_A1_A2_2, PO_C11_A2, PO_C11_A2_2, PO_C11_A3, PO_C11_A3_A0_2,
	PO_C11_A0, PO_C11_A0_2, PO_C11_A1, PO_C11_A1_A2_2, PO_C11_A2, PO_C11_A2_2, PO_C11_A3, PO_C11_A3_A1_2,
	PO_C11_A1, PO_C11_A1_A4_1, PO_C11_A1_A4_2, PO_C11_A1_A4_3, PO_C11_A4, PO_C11_A4, PO_C11_A4, PO_C11_A4,
	PO_C11_A4, PO_C11_A4, PO_C11_A4, PO_C11_A4, PO_C11_A4, PO_C11_A4, PO_C11_A4, PO_C11_A4,
	PO_C11_A4, PO_C11_A4, PO_C11_A4, PO_C11_A4, PO_C11_A4, PO_C11_A4, PO_C11_A4, PO_C11_A4,
	PO_C11_A4, PO_C11_A4, PO_C11_A4, PO_C11_A4,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, -1 * _2X, -1 * _2X,
	0 * _2X, 0 * _2X, 1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, -1 * _2X, -1 * _2X,
	0 * _2X, 0 * _2X, 1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	94,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C11_JA0, PO_C11_JA0, PO_C11_JA0, PO_C11_JA0, PO_C11_JA0, PO_C11_JA0, PO_C11_JA0, PO_C11_JA0,
	PO_C11_JA0_1, PO_C11_JA0_1, PO_C11_JA0_1, PO_C11_JA0_1, PO_C11_JA0_1, PO_C11_JA0_1, PO_C11_JA0_1, PO_C11_JA0_1,
	PO_C11_JA0_2, PO_C11_JA0_2, PO_C11_JA0_2, PO_C11_JA0_2, PO_C11_JA0_2, PO_C11_JA0_2, PO_C11_JA0_2, PO_C11_JA0_2,
	PO_C11_JA0_3, PO_C11_JA0_3, PO_C11_JA0_3, PO_C11_JA0_3, PO_C11_JA0_3, PO_C11_JA0_3, PO_C11_JA0_3, PO_C11_JA0_3,
	PO_C11_JA1, PO_C11_JA1_1, PO_C11_JA1_2, PO_C11_JA1_3, PO_C11_JA2, PO_C11_JA2, PO_C11_JA2_JA3_1, PO_C11_JA2_JA3_2,
	PO_C11_JA2_JA3_2, PO_C11_JA2_JA3_3, PO_C11_JA3, PO_C11_JA3_1, PO_C11_JA3_2, PO_C11_JA3_3, PO_C11_JA4, PO_C11_JA4,
	PO_C11_JA4, PO_C11_JA4_1, PO_C11_JA4_1, PO_C11_JA4_2, PO_C11_JA4_2, PO_C11_JA4_2, PO_C11_JA4_3, PO_C11_JA4_3,
	PO_C11_JA5, PO_C11_JA5_2, PO_C11_JA6, PO_C11_JA6_2, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1,
	PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1,
	PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1,
	PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1,
	PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, -1 * _2X, -1 * _2X,
	2 * _2X, 2 * _2X, -1 * _2X, -1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 50 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	20,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C11_JA0, PO_C11_JA0_2, PO_C11_JA1, PO_C11_JA1_1, PO_C11_JA1_2, PO_C11_JA1_3, PO_C11_JA2, PO_C11_JA2,
	PO_C11_JA2_JA1_1, PO_C11_JA2_JA1_2, PO_C11_JA2_JA1_2, PO_C11_JA2_JA1_3, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1,
	PO_C11_JA1, PO_C11_JA1, PO_C11_JA1, PO_C11_JA1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, -11, -6 * _2X,
	-11, -6 * _2X, -9, -5 * _2X, -7, -4 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 50 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	SALAMANDER_NEUTRAL,	SALAMANDER_JUMPATTACK,	DISTANCE_OUT_XY,	6 * 8 + 6,	RANDOM,	50,
	SALAMANDER_NEUTRAL,	SALAMANDER_RETREAT,	DISTANCE_CHECK_XY,	5 * 8 + 6,	RANDOM,	25,
	SALAMANDER_NEUTRAL,	SALAMANDER_ATTACK,	DISTANCE_CHECK_XY,	5 * 8 + 6,	0,	0,
	SALAMANDER_NEUTRAL,	SALAMANDER_MOVE,	0,	0,	0,	0,
	SALAMANDER_MOVE,	SALAMANDER_JUMPATTACK,	DISTANCE_OUT_XY,	6 * 8 + 6,	RANDOM,	50,
	SALAMANDER_MOVE,	SALAMANDER_ATTACK,	DISTANCE_CHECK_XY,	5 * 8 + 6,	0,	0,
	SALAMANDER_ATTACK,	SALAMANDER_NEUTRAL,	0,	0,	0,	0,
	SALAMANDER_JUMPATTACK,	SALAMANDER_NEUTRAL,	0,	0,	0,	0,
	SALAMANDER_RETREAT,	SALAMANDER_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 6,	0,	0,
	SALAMANDER_RETREAT,	SALAMANDER_JUMPATTACK,	DISTANCE_OUT_XY,	6 * 8 + 4,	RANDOM,	60,
	SALAMANDER_RETREAT,	SALAMANDER_MOVE,	DISTANCE_OUT_XY,	8 * 8 + 6,	0,	0,
	SALAMANDER_RETREAT,	SALAMANDER_NEUTRAL,	0,	0,	0,	0,
	-1,
};


//SLING 새총맨
const signed short c12mv[] = {
	//상태 데이터
	//SLING_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C12_N0, PO_C12_N0_1, PO_C12_N0_2, PO_C12_N0_3, PO_C12_N1, PO_C12_N1_1, PO_C12_N1_2, PO_C12_N1_3,
	PO_C12_N2, PO_C12_N2_1, PO_C12_N2_2, PO_C12_N2_3, PO_C12_N3, PO_C12_N3_1, PO_C12_N3_2, PO_C12_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SLING_MOVE
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_RANDOM,	//초기화 조건
	PO_C12_W0, PO_C12_W0_1, PO_C12_W0_2, PO_C12_W0_3, PO_C12_W1, PO_C12_W1, PO_C12_W1_1, PO_C12_W1_1,
	PO_C12_W1_2, PO_C12_W1_2, PO_C12_W1_3, PO_C12_W1_3, PO_C12_W2, PO_C12_W2_1, PO_C12_W2_2, PO_C12_W2_3,
	PO_C12_W3, PO_C12_W3, PO_C12_W3_1, PO_C12_W3_1, PO_C12_W3_2, PO_C12_W3_2, PO_C12_W3_3, PO_C12_W3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SLING_ATTACK
	38,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C12_A0, PO_C12_A0_1, PO_C12_A0_2, PO_C12_A0_3, PO_C12_A1, PO_C12_A1, PO_C12_A1, PO_C12_A1,
	PO_C12_A1, PO_C12_A1, PO_C12_A1, PO_C12_A1_1, PO_C12_A1_1, PO_C12_A1_1, PO_C12_A1_1, PO_C12_A1_1,
	PO_C12_A1_1, PO_C12_A1_2, PO_C12_A1_2, PO_C12_A1_2, PO_C12_A1_2, PO_C12_A1_2, PO_C12_A1_2, PO_C12_A1_2,
	PO_C12_A1_3, PO_C12_A1_3, PO_C12_A1_3, PO_C12_A1_3, PO_C12_A1_3, PO_C12_A1_3, PO_C12_A2, PO_C12_A2_2,
	PO_C12_A3, PO_C12_A3_2, PO_C12_A4, PO_C12_A4_2, PO_C12_A0, PO_C12_A0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SLING_RETREAT
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_OPPOSITE,	//초기화 조건
	PO_C12_W0, PO_C12_W0_2, PO_C12_W1, PO_C12_W1_2, PO_C12_W2, PO_C12_W2_2, PO_C12_W3, PO_C12_W3_2,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SLING_BACK
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C12_W0, PO_C12_W0_2, PO_C12_W1, PO_C12_W1_2, PO_C12_W2, PO_C12_W2_2, PO_C12_W3, PO_C12_W3_2,	//상태 프레임별 모션
	-1, -1, -1, -1, -1, -1, -1, -1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SLING_SWORD
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C12_SWORD0, PO_C12_SWORD0_2, PO_C12_SWORD1, PO_C12_SWORD1_2, PO_C12_SWORD2, PO_C12_SWORD2_2, PO_C12_SWORD3, PO_C12_SWORD3_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SLING_SWORDMOVE
	12,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_RANDOM,	//초기화 조건
	PO_C12_SWORDMOVE0, PO_C12_SWORDMOVE0_2, PO_C12_SWORDMOVE1, PO_C12_SWORDMOVE1_1, PO_C12_SWORDMOVE1_2, PO_C12_SWORDMOVE1_3, PO_C12_SWORDMOVE2, PO_C12_SWORDMOVE2_2,
	PO_C12_SWORDMOVE3, PO_C12_SWORDMOVE3_1, PO_C12_SWORDMOVE3_2, PO_C12_SWORDMOVE3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SLING_SWORDBACK
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C12_SWORDMOVE0, PO_C12_SWORDMOVE0_2, PO_C12_SWORDMOVE1, PO_C12_SWORDMOVE1_2, PO_C12_SWORDMOVE2, PO_C12_SWORDMOVE2_2, PO_C12_SWORDMOVE3, PO_C12_SWORDMOVE3_2,	//상태 프레임별 모션
	-1, -1, -1, -1, -1, -1, -1, -1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	SLING_NEUTRAL,	SLING_RETREAT,	DISTANCE_CHECK_XY,	4 * 8 + 3,	0,	0,
	SLING_NEUTRAL,	SLING_ATTACK,	DISTANCE_CHECK_XY,	7 * 8 + 3,	0,	0,
	SLING_NEUTRAL,	SLING_MOVE,	COMPARE_FRAME,	16,	RANDOM,	25,
	SLING_MOVE,	SLING_ATTACK,	DISTANCE_CHECK_XY,	7 * 8 + 3,	0,	0,
	SLING_MOVE,	SLING_NEUTRAL,	COMPARE_FRAME,	20,	RANDOM,	40,
	SLING_ATTACK,	SLING_NEUTRAL,	0,	0,	0,	0,
	SLING_RETREAT,	SLING_ATTACK,	0,	0,	RANDOM,	30,
	SLING_RETREAT,	SLING_NEUTRAL,	DISTANCE_OUT_XY,	4 * 8 + 3,	0,	0,
	-1,
};


//BOAR
const signed short c13mv[] = {
	//상태 데이터
	//BOAR_NEUTRAL
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C13_N0, PO_C13_N0, PO_C13_N0_1, PO_C13_N0_1, PO_C13_N0_2, PO_C13_N0_2, PO_C13_N0_3, PO_C13_N0_3,
	PO_C13_N1, PO_C13_N1_1, PO_C13_N1_2, PO_C13_N1_3, PO_C13_N2, PO_C13_N2, PO_C13_N2_1, PO_C13_N2_1,
	PO_C13_N2_2, PO_C13_N2_2, PO_C13_N2_3, PO_C13_N2_3, PO_C13_N3, PO_C13_N3_1, PO_C13_N3_2, PO_C13_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BOAR_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_RANDOM,	//초기화 조건
	PO_C13_W0, PO_C13_W0_1, PO_C13_W0_2, PO_C13_W0_3, PO_C13_W1, PO_C13_W1_1, PO_C13_W1_2, PO_C13_W1_3,
	PO_C13_W2, PO_C13_W2_1, PO_C13_W2_2, PO_C13_W2_3, PO_C13_W3, PO_C13_W3_1, PO_C13_W3_2, PO_C13_W3_3,	//상태 프레임별 모션
	1, 1, 0 * _2X, 0 * _2X, 1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X,
	1, 1, 0 * _2X, 0 * _2X, 1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BOAR_MOVE_FAST
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C13_W0, PO_C13_W0_2, PO_C13_W1, PO_C13_W1_2, PO_C13_W2, PO_C13_W2_2, PO_C13_W3, PO_C13_W3_2,	//상태 프레임별 모션
	51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BOAR_ATTACK
	72,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C13_A0, PO_C13_A0_1, PO_C13_A0_2, PO_C13_A0_3, PO_C13_A1, PO_C13_A1, PO_C13_A1_1, PO_C13_A1_1,
	PO_C13_A1_2, PO_C13_A1_2, PO_C13_A1_3, PO_C13_A1_3, PO_C13_A7, PO_C13_A7_A8_1, PO_C13_A7_A8_2, PO_C13_A7_A8_3,
	PO_C13_A8, PO_C13_A8, PO_C13_A8_1, PO_C13_A8_1, PO_C13_A8_2, PO_C13_A8_2, PO_C13_A8_3, PO_C13_A8_3,
	PO_C13_A9, PO_C13_A9_1, PO_C13_A9_2, PO_C13_A9_3, PO_C13_A10, PO_C13_A10, PO_C13_A10, PO_C13_A10,
	PO_C13_A10, PO_C13_A10, PO_C13_A10, PO_C13_A10, PO_C13_A10, PO_C13_A10_1, PO_C13_A10_1, PO_C13_A10_1,
	PO_C13_A10_1, PO_C13_A10_1, PO_C13_A10_1, PO_C13_A10_1, PO_C13_A10_1, PO_C13_A10_1, PO_C13_A10_2, PO_C13_A10_2,
	PO_C13_A10_2, PO_C13_A10_2, PO_C13_A10_2, PO_C13_A10_2, PO_C13_A10_2, PO_C13_A10_2, PO_C13_A10_2, PO_C13_A10_3,
	PO_C13_A10_3, PO_C13_A10_3, PO_C13_A10_3, PO_C13_A10_3, PO_C13_A10_3, PO_C13_A10_3, PO_C13_A10_3, PO_C13_A10_3,
	PO_C13_A7, PO_C13_A7_A0_1, PO_C13_A7_A0_2, PO_C13_A7_A0_3, PO_C13_A0, PO_C13_A0, PO_C13_A0, PO_C13_A0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,
	-1, -1, -1, -1, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3, 3, 1, 1, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BOAR_DASH
	30,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C13_A2, PO_C13_A2_2, PO_C13_A3, PO_C13_A3_1, PO_C13_A3_2, PO_C13_A3_3, PO_C13_A4, PO_C13_A4_2,
	PO_C13_A5, PO_C13_A5_1, PO_C13_A5_2, PO_C13_A5_3, PO_C13_A6, PO_C13_A6, PO_C13_A6, PO_C13_A6,
	PO_C13_A6, PO_C13_A6, PO_C13_A6, PO_C13_A6, PO_C13_A6, PO_C13_A6, PO_C13_A6, PO_C13_A6,
	PO_C13_A6, PO_C13_A6, PO_C13_A6, PO_C13_A6, PO_C13_A6, PO_C13_A6,	//상태 프레임별 모션
	5, 5, 5, 5, 5, 5, 2 * _2X, 2 * _2X,
	3, 3, 1 * _2X, 1 * _2X, 1, 1, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BOAR_EVENTNEUTRAL
	12,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C13_N0, PO_C13_N0_1, PO_C13_N0_2, PO_C13_N0_3, PO_C13_N1, PO_C13_N1_2, PO_C13_N2, PO_C13_N2_1,
	PO_C13_N2_2, PO_C13_N2_3, PO_C13_N3, PO_C13_N3_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BOAR_EVENTMOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C13_W0, PO_C13_W0_1, PO_C13_W0_2, PO_C13_W0_3, PO_C13_W1, PO_C13_W1_1, PO_C13_W1_2, PO_C13_W1_3,
	PO_C13_W2, PO_C13_W2_1, PO_C13_W2_2, PO_C13_W2_3, PO_C13_W3, PO_C13_W3_1, PO_C13_W3_2, PO_C13_W3_3,	//상태 프레임별 모션
	4 * _2X, 4 * _2X, 2 * _2X, 2 * _2X, 4 * _2X, 4 * _2X, 2 * _2X, 2 * _2X,
	4 * _2X, 4 * _2X, 2 * _2X, 2 * _2X, 4 * _2X, 4 * _2X, 2 * _2X, 2 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BOAR_EVENTATTACK
	20,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C13_A0, PO_C13_A0_2, PO_C13_A1, PO_C13_A1_1, PO_C13_A1_2, PO_C13_A1_3, PO_C13_A7, PO_C13_A7_A8_2,
	PO_C13_A8, PO_C13_A8_1, PO_C13_A8_2, PO_C13_A8_3, PO_C13_A9, PO_C13_A9_2, PO_C13_A10, PO_C13_A10_2,
	PO_C13_A7, PO_C13_A7_A0_2, PO_C13_A0, PO_C13_A0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 5, 5,
	-1 * _2X, -1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3, 3, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BOAR_EVENTDASH
	14,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C13_A2, PO_C13_A2_2, PO_C13_A3, PO_C13_A3_1, PO_C13_A3_2, PO_C13_A3_3, PO_C13_A4, PO_C13_A4_2,
	PO_C13_A5, PO_C13_A5_1, PO_C13_A5_2, PO_C13_A5_3, PO_C13_A6, PO_C13_A6_2,	//상태 프레임별 모션
	105, 0 * _2X, 105, 0 * _2X, 105, 0 * _2X, 52 * _2X, 0 * _2X,
	103, 0 * _2X, 51 * _2X, 0 * _2X, 101, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	BOAR_NEUTRAL,	BOAR_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 4,	0,	0,
	BOAR_NEUTRAL,	BOAR_MOVE_FAST,	DISTANCE_CHECK_XY,	10 * 8 + 4,	0,	0,
	BOAR_NEUTRAL,	BOAR_MOVE,	COMPARE_FRAME,	16,	RANDOM,	50,
	BOAR_MOVE,	BOAR_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 4,	0,	0,
	BOAR_NEUTRAL,	BOAR_MOVE_FAST,	DISTANCE_CHECK_XY,	10 * 8 + 4,	0,	0,
	BOAR_MOVE,	BOAR_NEUTRAL,	COMPARE_FRAME,	20,	RANDOM,	30,
	BOAR_MOVE_FAST,	BOAR_DASH,	DISTANCE_CHECK_XY,	6 * 8 + 4,	0,	0,
	BOAR_MOVE_FAST,	BOAR_NEUTRAL,	DISTANCE_OUT_XY,	10 * 8 + 4,	0,	0,
	BOAR_DASH,	BOAR_NEUTRAL,	0,	0,	0,	0,
	BOAR_ATTACK,	BOAR_NEUTRAL,	0,	0,	0,	0,
	-1,
};


//GIANT 아델평원 보스
const signed short c14mv[] = {
	//상태 데이터
	//GIANT_NEUTRAL
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C14_N0, PO_C14_N0_1, PO_C14_N0_2, PO_C14_N0_3, PO_C14_N1, PO_C14_N1_N2_1, PO_C14_N1_N2_2, PO_C14_N1_N2_3,
	PO_C14_N2, PO_C14_N2_N3_1, PO_C14_N2_N3_2, PO_C14_N2_N3_3, PO_C14_N3, PO_C14_N3, PO_C14_N3_1, PO_C14_N3_1,
	PO_C14_N3_2, PO_C14_N3_2, PO_C14_N3_3, PO_C14_N3_3, PO_C14_N2, PO_C14_N2_N1_1, PO_C14_N2_N1_2, PO_C14_N2_N1_3,
	PO_C14_N1, PO_C14_N1_N0_1, PO_C14_N1_N0_2, PO_C14_N1_N0_3, PO_C14_N0, PO_C14_N0, PO_C14_N0, PO_C14_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GIANT_MOVE
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C14_W0, PO_C14_W0_1, PO_C14_W0_2, PO_C14_W0_3, PO_C14_W1, PO_C14_W1, PO_C14_W1_1, PO_C14_W1_2,
	PO_C14_W1_2, PO_C14_W1_3, PO_C14_W2, PO_C14_W2, PO_C14_W2_W3_1, PO_C14_W2_W3_2, PO_C14_W2_W3_2, PO_C14_W2_W3_3,
	PO_C14_W3, PO_C14_W3_1, PO_C14_W3_2, PO_C14_W3_3, PO_C14_W4, PO_C14_W4, PO_C14_W4_1, PO_C14_W4_2,
	PO_C14_W4_2, PO_C14_W4_3, PO_C14_W5, PO_C14_W5, PO_C14_W5_W0_1, PO_C14_W5_W0_2, PO_C14_W5_W0_2, PO_C14_W5_W0_3,	//상태 프레임별 모션
	1, 1, 0 * _2X, 0 * _2X, 1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	5, 5, 0 * _2X, 0 * _2X, 1, 1, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 2 * _2X, 2 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GIANT_ATTACK
	64,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C14_A0, PO_C14_A0_1, PO_C14_A0_2, PO_C14_A0_3, PO_C14_A1, PO_C14_A1, PO_C14_A1, PO_C14_A1,
	PO_C14_A1, PO_C14_A1_1, PO_C14_A1_1, PO_C14_A1_1, PO_C14_A1_1, PO_C14_A1_1, PO_C14_A1_2, PO_C14_A1_2,
	PO_C14_A1_2, PO_C14_A1_2, PO_C14_A1_2, PO_C14_A1_3, PO_C14_A1_3, PO_C14_A1_3, PO_C14_A1_3, PO_C14_A1_3,
	PO_C14_A2, PO_C14_A2, PO_C14_A2_1, PO_C14_A2_1, PO_C14_A2_2, PO_C14_A2_2, PO_C14_A2_3, PO_C14_A2_3,
	PO_C14_A3, PO_C14_A3_1, PO_C14_A3_2, PO_C14_A3_3, PO_C14_A4, PO_C14_A4_2, PO_C14_A5, PO_C14_A5_1,
	PO_C14_A5_2, PO_C14_A5_3, PO_C14_A6, PO_C14_A6, PO_C14_A6, PO_C14_A6, PO_C14_A6, PO_C14_A6,
	PO_C14_A6, PO_C14_A6, PO_C14_A6, PO_C14_A6, PO_C14_A6, PO_C14_A6, PO_C14_A6, PO_C14_A6,
	PO_C14_A6, PO_C14_A6, PO_C14_A6, PO_C14_A6, PO_C14_A6, PO_C14_A6, PO_C14_A6, PO_C14_A6,	//상태 프레임별 모션
	-5, -5, -3, -3, -1 * _2X, -1 * _2X, -1, -1,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 3, 3, 3, 3,
	3, 3, 3, 3, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,
	1, 1, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GIANT_RETREAT
	20,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C14_W0, PO_C14_W0_2, PO_C14_W1, PO_C14_W1_2, PO_C14_W2, PO_C14_W2_W1_2, PO_C14_W1, PO_C14_W1_2,
	PO_C14_W2, PO_C14_W2_W3_2, PO_C14_W3, PO_C14_W3_2, PO_C14_W4, PO_C14_W4_2, PO_C14_W5, PO_C14_W5_W4_2,
	PO_C14_W4, PO_C14_W4_2, PO_C14_W5, PO_C14_W5_W0_2,	//상태 프레임별 모션
	-1, -1, -1 * _2X, -1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, -5, -5, -1, -1, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, -2 * _2X, -2 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GIANT_BULLET
	74,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C14_3WAY0, PO_C14_3WAY0_2, PO_C14_3WAY1, PO_C14_3WAY1, PO_C14_3WAY1_3WAY2_1, PO_C14_3WAY1_3WAY2_2, PO_C14_3WAY1_3WAY2_2, PO_C14_3WAY1_3WAY2_3,
	PO_C14_3WAY2, PO_C14_3WAY2_2, PO_C14_3WAY3, PO_C14_3WAY3_2, PO_C14_3WAY4, PO_C14_3WAY4_2, PO_C14_3WAY5, PO_C14_3WAY5_3WAY3_2,
	PO_C14_3WAY3, PO_C14_3WAY3_2, PO_C14_3WAY4, PO_C14_3WAY4_2, PO_C14_3WAY5, PO_C14_3WAY5_3WAY3_2, PO_C14_3WAY3, PO_C14_3WAY3_2,
	PO_C14_3WAY4, PO_C14_3WAY4_2, PO_C14_3WAY5, PO_C14_3WAY5_3WAY3_2, PO_C14_3WAY3, PO_C14_3WAY3_2, PO_C14_3WAY4, PO_C14_3WAY4_2,
	PO_C14_3WAY5, PO_C14_3WAY5_3WAY4_2, PO_C14_3WAY4, PO_C14_3WAY4_2, PO_C14_3WAY5, PO_C14_3WAY5_3WAY4_2, PO_C14_3WAY4, PO_C14_3WAY4_2,
	PO_C14_3WAY5, PO_C14_3WAY5_3WAY6_2, PO_C14_3WAY6, PO_C14_3WAY6_2, PO_C14_3WAY7, PO_C14_3WAY7_2, PO_C14_3WAY8, PO_C14_3WAY8_2,
	PO_C14_3WAY9, PO_C14_3WAY9_2, PO_C14_3WAY10, PO_C14_3WAY10_2, PO_C14_3WAY11, PO_C14_3WAY11_2, PO_C14_3WAY1, PO_C14_3WAY1_3WAY0_2,
	PO_C14_3WAY0, PO_C14_3WAY0, PO_C14_3WAY0, PO_C14_3WAY0, PO_C14_3WAY0, PO_C14_3WAY0, PO_C14_3WAY0, PO_C14_3WAY0,
	PO_C14_3WAY0, PO_C14_3WAY0, PO_C14_3WAY0, PO_C14_3WAY0, PO_C14_3WAY0, PO_C14_3WAY0, PO_C14_3WAY0, PO_C14_3WAY0,
	PO_C14_3WAY0, PO_C14_3WAY0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	GIANT_NEUTRAL,	GIANT_BULLET,	0,	0,	RANDOM,	30,
	GIANT_NEUTRAL,	GIANT_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 6,	0,	0,
	GIANT_NEUTRAL,	GIANT_MOVE,	0,	0,	0,	0,
	GIANT_MOVE,	GIANT_BULLET,	0,	0,	RANDOM,	30,
	GIANT_MOVE,	GIANT_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 6,	0,	0,
	GIANT_NEUTRAL,	GIANT_MOVE,	0,	0,	RANDOM,	33,
	GIANT_ATTACK,	GIANT_RETREAT,	DISTANCE_CHECK_XY,	4 * 8 + 6,	RANDOM,	40,
	GIANT_ATTACK,	GIANT_NEUTRAL,	0,	0,	0,	0,
	GIANT_RETREAT,	GIANT_BULLET,	0,	0,	RANDOM,	50,
	GIANT_RETREAT,	GIANT_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 6,	0,	0,
	GIANT_RETREAT,	GIANT_MOVE,	DISTANCE_OUT_XY,	6 * 8 + 6,	0,	0,
	GIANT_BULLET,	GIANT_NEUTRAL,	0,	0,	0,	0,
	-1,
};


//FLAME
const signed short c15mv[] = {
	//상태 데이터
	//FLAME_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C15_N0, PO_C15_N0_1, PO_C15_N0_2, PO_C15_N0_3, PO_C15_N1, PO_C15_N1_1, PO_C15_N1_2, PO_C15_N1_3,
	PO_C15_N2, PO_C15_N2_N3_1, PO_C15_N2_N3_2, PO_C15_N2_N3_3, PO_C15_N3, PO_C15_N3_1, PO_C15_N3_2, PO_C15_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//FLAME_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C15_N0, PO_C15_N0_1, PO_C15_N0_2, PO_C15_N0_3, PO_C15_N1, PO_C15_N1_1, PO_C15_N1_2, PO_C15_N1_3,
	PO_C15_N2, PO_C15_N2_N3_1, PO_C15_N2_N3_2, PO_C15_N2_N3_3, PO_C15_N3, PO_C15_N3_1, PO_C15_N3_2, PO_C15_N3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//FLAME_MOVE_FAST
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C15_N0, PO_C15_N0_2, PO_C15_N1, PO_C15_N1_2, PO_C15_N2, PO_C15_N2_N3_2, PO_C15_N3, PO_C15_N3_2,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//FLAME_ATTACK
	72,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C15_A0, PO_C15_A0, PO_C15_A0, PO_C15_A0_1, PO_C15_A0_1, PO_C15_A0_1, PO_C15_A0_2, PO_C15_A0_2,
	PO_C15_A0_2, PO_C15_A0_3, PO_C15_A0_3, PO_C15_A0_3, PO_C15_A1, PO_C15_A1, PO_C15_A1, PO_C15_A1,
	PO_C15_A1_1, PO_C15_A1_1, PO_C15_A1_1, PO_C15_A1_1, PO_C15_A1_2, PO_C15_A1_2, PO_C15_A1_2, PO_C15_A1_2,
	PO_C15_A1_3, PO_C15_A1_3, PO_C15_A1_3, PO_C15_A1_3, PO_C15_A2, PO_C15_A2_2, PO_C15_A3, PO_C15_A3_A4_2,
	PO_C15_A4, PO_C15_A4_A5_2, PO_C15_A5, PO_C15_A5_A4_1, PO_C15_A5_A4_2, PO_C15_A5_A4_3, PO_C15_A4, PO_C15_A4_A3_2,
	PO_C15_A3, PO_C15_A3_A2_2, PO_C15_A2, PO_C15_A2_1, PO_C15_A2_2, PO_C15_A2_3, PO_C15_A3, PO_C15_A3_A4_2,
	PO_C15_A4, PO_C15_A4_A5_2, PO_C15_A5, PO_C15_A5_A4_1, PO_C15_A5_A4_2, PO_C15_A5_A4_3, PO_C15_A4, PO_C15_A4_A3_2,
	PO_C15_A3, PO_C15_A3_A2_2, PO_C15_A2, PO_C15_A2_1, PO_C15_A2_2, PO_C15_A2_3, PO_C15_A3, PO_C15_A3_A4_2,
	PO_C15_A4, PO_C15_A4_A5_2, PO_C15_A5, PO_C15_A5_N0_2, PO_C15_N0, PO_C15_N0_2, PO_C15_N1, PO_C15_N1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 101, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//FLAME_GUARD_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C15_N0, PO_C15_N0_1, PO_C15_N0_2, PO_C15_N0_3, PO_C15_N1, PO_C15_N1_1, PO_C15_N1_2, PO_C15_N1_3,
	PO_C15_N2, PO_C15_N2_N3_1, PO_C15_N2_N3_2, PO_C15_N2_N3_3, PO_C15_N3, PO_C15_N3_1, PO_C15_N3_2, PO_C15_N3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//FLAME_GUARD_MOVE
	12,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C15_N0, PO_C15_N0_1, PO_C15_N0_2, PO_C15_N0_3, PO_C15_N1, PO_C15_N1_1, PO_C15_N1_2, PO_C15_N1_3,
	PO_C15_N2, PO_C15_N2_N0_1, PO_C15_N2_N0_2, PO_C15_N2_N0_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	FLAME_NEUTRAL,	FLAME_MOVE_FAST,	DISTANCE_CHECK_XY,	3 * 8 + 5,	0,	0,
	FLAME_NEUTRAL,	FLAME_ATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 4,	0,	0,
	FLAME_NEUTRAL,	FLAME_MOVE,	COMPARE_FRAME,	20,	RANDOM,	30,
	FLAME_MOVE,	FLAME_MOVE_FAST,	DISTANCE_CHECK_XY,	3 * 8 + 5,	0,	0,
	FLAME_MOVE,	FLAME_ATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 4,	0,	0,
	FLAME_MOVE,	FLAME_NEUTRAL,	COMPARE_FRAME,	20,	RANDOM,	30,
	FLAME_ATTACK,	FLAME_NEUTRAL,	0,	0,	0,	0,
	FLAME_MOVE_FAST,	FLAME_NEUTRAL,	DISTANCE_OUT_XY,	6 * 8 + 4,	0,	0,
	FLAME_MOVE_FAST,	FLAME_ATTACK,	DISTANCE_OUT_XY,	3 * 8 + 5,	0,	0,
	-1,
};


//PHOENIX
const signed short c16mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C16_N0, PO_C16_N0_1, PO_C16_N0_2, PO_C16_N0_3, PO_C16_N1, PO_C16_N1_1, PO_C16_N1_2, PO_C16_N1_3,
	PO_C16_N2, PO_C16_N2_1, PO_C16_N2_2, PO_C16_N2_3, PO_C16_N3, PO_C16_N3_1, PO_C16_N3_2, PO_C16_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C16_N0, PO_C16_N0_1, PO_C16_N0_2, PO_C16_N0_3, PO_C16_N1, PO_C16_N1_1, PO_C16_N1_2, PO_C16_N1_3,
	PO_C16_N2, PO_C16_N2_1, PO_C16_N2_2, PO_C16_N2_3, PO_C16_N3, PO_C16_N3_1, PO_C16_N3_2, PO_C16_N3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	72,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C16_DASHATT1, PO_C16_DASHATT1, PO_C16_DASHATT1, PO_C16_DASHATT1, PO_C16_DASHATT1, PO_C16_DASHATT1, PO_C16_DASHATT1_DASHATT0_1, PO_C16_DASHATT1_DASHATT0_1,
	PO_C16_DASHATT1_DASHATT0_1, PO_C16_DASHATT1_DASHATT0_1, PO_C16_DASHATT1_DASHATT0_1, PO_C16_DASHATT1_DASHATT0_1, PO_C16_DASHATT1_DASHATT0_2, PO_C16_DASHATT1_DASHATT0_2, PO_C16_DASHATT1_DASHATT0_2, PO_C16_DASHATT1_DASHATT0_2,
	PO_C16_DASHATT1_DASHATT0_2, PO_C16_DASHATT1_DASHATT0_2, PO_C16_DASHATT1_DASHATT0_3, PO_C16_DASHATT1_DASHATT0_3, PO_C16_DASHATT1_DASHATT0_3, PO_C16_DASHATT1_DASHATT0_3, PO_C16_DASHATT1_DASHATT0_3, PO_C16_DASHATT1_DASHATT0_3,
	PO_C16_DASHATT0, PO_C16_DASHATT0, PO_C16_DASHATT0, PO_C16_DASHATT0, PO_C16_DASHATT0, PO_C16_DASHATT0, PO_C16_DASHATT0_1, PO_C16_DASHATT0_1,
	PO_C16_DASHATT0_1, PO_C16_DASHATT0_1, PO_C16_DASHATT0_1, PO_C16_DASHATT0_2, PO_C16_DASHATT0_2, PO_C16_DASHATT0_2, PO_C16_DASHATT0_2, PO_C16_DASHATT0_2,
	PO_C16_DASHATT0_2, PO_C16_DASHATT0_3, PO_C16_DASHATT0_3, PO_C16_DASHATT0_3, PO_C16_DASHATT0_3, PO_C16_DASHATT0_3, PO_C16_DASHATT1, PO_C16_DASHATT1_STAND0_2,
	PO_C16_STAND0, PO_C16_STAND0_STAND1_2, PO_C16_STAND1, PO_C16_STAND1_2, PO_C16_STAND2, PO_C16_STAND2_2, PO_C16_STAND3, PO_C16_STAND3_2,
	PO_C16_STAND0, PO_C16_STAND0_STAND1_2, PO_C16_STAND1, PO_C16_STAND1_2, PO_C16_STAND2, PO_C16_STAND2_2, PO_C16_STAND3, PO_C16_STAND3_2,
	PO_C16_STAND0, PO_C16_STAND0_STAND1_2, PO_C16_STAND1, PO_C16_STAND1_2, PO_C16_STAND2, PO_C16_STAND2_2, PO_C16_STAND3, PO_C16_STAND3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 119, 0 * _2X, 59 * _2X, 0 * _2X,
	117, 0 * _2X, 58 * _2X, 0 * _2X, 115, 0 * _2X, 57 * _2X, 0 * _2X,
	113, 0 * _2X, 56 * _2X, 0 * _2X, 111, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	44,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C16_STAND0, PO_C16_STAND0, PO_C16_STAND0, PO_C16_STAND0, PO_C16_STAND0_A0_1, PO_C16_STAND0_A0_1, PO_C16_STAND0_A0_1, PO_C16_STAND0_A0_1,
	PO_C16_STAND0_A0_2, PO_C16_STAND0_A0_2, PO_C16_STAND0_A0_2, PO_C16_STAND0_A0_2, PO_C16_STAND0_A0_3, PO_C16_STAND0_A0_3, PO_C16_STAND0_A0_3, PO_C16_STAND0_A0_3,
	PO_C16_A0, PO_C16_A0_2, PO_C16_A1, PO_C16_A1_2, PO_C16_A2, PO_C16_A2_1, PO_C16_A2_2, PO_C16_A2_3,
	PO_C16_A3, PO_C16_A3_2, PO_C16_SHOT0, PO_C16_SHOT0_2, PO_C16_STAND0, PO_C16_STAND0_STAND1_2, PO_C16_STAND1, PO_C16_STAND1_2,
	PO_C16_STAND2, PO_C16_STAND2_2, PO_C16_STAND3, PO_C16_STAND3_2, PO_C16_STAND0, PO_C16_STAND0_STAND1_2, PO_C16_STAND1, PO_C16_STAND1_2,
	PO_C16_STAND2, PO_C16_STAND2_2, PO_C16_STAND3, PO_C16_STAND3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	PHOENIX_NEUTRAL,	PHOENIX_DASH,	DISTANCE_CHECK_XY,	6 * 8 + 6,	RANDOM,	33,
	PHOENIX_NEUTRAL,	PHOENIX_ATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 3,	0,	0,
	PHOENIX_NEUTRAL,	PHOENIX_MOVE,	DISTANCE_OUT_XY,	6 * 8 + 6,	RANDOM,	50,
	PHOENIX_MOVE,	PHOENIX_NEUTRAL,	DISTANCE_CHECK_XY,	8 * 8 + 6,	0,	0,
	PHOENIX_MOVE,	PHOENIX_NEUTRAL,	0,	0,	RANDOM,	40,
	PHOENIX_DASH,	PHOENIX_NEUTRAL,	0,	0,	0,	0,
	PHOENIX_ATTACK,	PHOENIX_NEUTRAL,	0,	0,	0,	0,
	-1,
};

const signed short c17mv[] = {
	//상태 데이터
	//IFRIT_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C17_N0, PO_C17_N0_1, PO_C17_N0_2, PO_C17_N0_3, PO_C17_N1, PO_C17_N1_1, PO_C17_N1_2, PO_C17_N1_3,
	PO_C17_N2, PO_C17_N2_1, PO_C17_N2_2, PO_C17_N2_3, PO_C17_N3, PO_C17_N3, PO_C17_N3, PO_C17_N3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//IFRIT_NEUTRAL_UP
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C17_N0, PO_C17_N0_1, PO_C17_N0_2, PO_C17_N0_3, PO_C17_N1, PO_C17_N1_1, PO_C17_N1_2, PO_C17_N1_3,
	PO_C17_N2, PO_C17_N2_1, PO_C17_N2_2, PO_C17_N2_3, PO_C17_N3, PO_C17_N3_1, PO_C17_N3_2, PO_C17_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//IFRIT_NEUTRAL_DOWN
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C17_N0, PO_C17_N0_1, PO_C17_N0_2, PO_C17_N0_3, PO_C17_N1, PO_C17_N1_1, PO_C17_N1_2, PO_C17_N1_3,
	PO_C17_N2, PO_C17_N2_1, PO_C17_N2_2, PO_C17_N2_3, PO_C17_N3, PO_C17_N3_1, PO_C17_N3_2, PO_C17_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//IFRIT_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C17_N0, PO_C17_N0_1, PO_C17_N0_2, PO_C17_N0_3, PO_C17_N1, PO_C17_N1_1, PO_C17_N1_2, PO_C17_N1_3,
	PO_C17_N2, PO_C17_N2_1, PO_C17_N2_2, PO_C17_N2_3, PO_C17_N3, PO_C17_N3_1, PO_C17_N3_2, PO_C17_N3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//IFRIT_ATTACK
	60,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C17_A0, PO_C17_A0_1, PO_C17_A0_2, PO_C17_A0_3, PO_C17_A1, PO_C17_A1_1, PO_C17_A1_2, PO_C17_A1_3,
	PO_C17_A2, PO_C17_A2_1, PO_C17_A2_2, PO_C17_A2_3, PO_C17_A3, PO_C17_A3_1, PO_C17_A3_2, PO_C17_A3_3,
	PO_C17_A4, PO_C17_A4, PO_C17_A4_1, PO_C17_A4_2, PO_C17_A4_2, PO_C17_A4_3, PO_C17_A5, PO_C17_A5_2,
	PO_C17_A6, PO_C17_A6_1, PO_C17_A6_2, PO_C17_A6_3, PO_C17_A7, PO_C17_A7_1, PO_C17_A7_2, PO_C17_A7_3,
	PO_C17_A8, PO_C17_A8_1, PO_C17_A8_2, PO_C17_A8_3, PO_C17_A9, PO_C17_A9_1, PO_C17_A9_2, PO_C17_A9_3,
	PO_C17_A10, PO_C17_A10, PO_C17_A10, PO_C17_A10, PO_C17_A10, PO_C17_A10, PO_C17_A10, PO_C17_A10,
	PO_C17_A10, PO_C17_A10, PO_C17_A10, PO_C17_A10, PO_C17_A10, PO_C17_A10, PO_C17_A10, PO_C17_A10,
	PO_C17_A10, PO_C17_A10, PO_C17_A10, PO_C17_A10,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//IFRIT_DASH
	136,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C17_DASHATT0, PO_C17_DASHATT0_2, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1,
	PO_C17_DASHATT1_1, PO_C17_DASHATT1_1, PO_C17_DASHATT1_1, PO_C17_DASHATT1_1, PO_C17_DASHATT1_1, PO_C17_DASHATT1_2, PO_C17_DASHATT1_2, PO_C17_DASHATT1_2,
	PO_C17_DASHATT1_2, PO_C17_DASHATT1_2, PO_C17_DASHATT1_2, PO_C17_DASHATT1_3, PO_C17_DASHATT1_3, PO_C17_DASHATT1_3, PO_C17_DASHATT1_3, PO_C17_DASHATT1_3,
	PO_C17_DASHATT2, PO_C17_DASHATT2, PO_C17_DASHATT2, PO_C17_DASHATT2, PO_C17_DASHATT2, PO_C17_DASHATT2_1, PO_C17_DASHATT2_1, PO_C17_DASHATT2_1,
	PO_C17_DASHATT2_1, PO_C17_DASHATT2_1, PO_C17_DASHATT2_2, PO_C17_DASHATT2_2, PO_C17_DASHATT2_2, PO_C17_DASHATT2_2, PO_C17_DASHATT2_2, PO_C17_DASHATT2_3,
	PO_C17_DASHATT2_3, PO_C17_DASHATT2_3, PO_C17_DASHATT2_3, PO_C17_DASHATT2_3, PO_C17_DASHATT3, PO_C17_DASHATT3, PO_C17_DASHATT3, PO_C17_DASHATT3,
	PO_C17_DASHATT3, PO_C17_DASHATT3_DASHATT2_1, PO_C17_DASHATT3_DASHATT2_1, PO_C17_DASHATT3_DASHATT2_1, PO_C17_DASHATT3_DASHATT2_1, PO_C17_DASHATT3_DASHATT2_1, PO_C17_DASHATT3_DASHATT2_2, PO_C17_DASHATT3_DASHATT2_2,
	PO_C17_DASHATT3_DASHATT2_2, PO_C17_DASHATT3_DASHATT2_2, PO_C17_DASHATT3_DASHATT2_2, PO_C17_DASHATT3_DASHATT2_3, PO_C17_DASHATT3_DASHATT2_3, PO_C17_DASHATT3_DASHATT2_3, PO_C17_DASHATT3_DASHATT2_3, PO_C17_DASHATT3_DASHATT2_3,
	PO_C17_DASHATT2, PO_C17_DASHATT2, PO_C17_DASHATT2, PO_C17_DASHATT2, PO_C17_DASHATT2, PO_C17_DASHATT2_1, PO_C17_DASHATT2_1, PO_C17_DASHATT2_1,
	PO_C17_DASHATT2_1, PO_C17_DASHATT2_1, PO_C17_DASHATT2_2, PO_C17_DASHATT2_2, PO_C17_DASHATT2_2, PO_C17_DASHATT2_2, PO_C17_DASHATT2_2, PO_C17_DASHATT2_3,
	PO_C17_DASHATT2_3, PO_C17_DASHATT2_3, PO_C17_DASHATT2_3, PO_C17_DASHATT2_3, PO_C17_DASHATT3, PO_C17_DASHATT3, PO_C17_DASHATT3, PO_C17_DASHATT3,
	PO_C17_DASHATT3, PO_C17_DASHATT3_DASHATT4_1, PO_C17_DASHATT3_DASHATT4_1, PO_C17_DASHATT3_DASHATT4_1, PO_C17_DASHATT3_DASHATT4_1, PO_C17_DASHATT3_DASHATT4_1, PO_C17_DASHATT3_DASHATT4_2, PO_C17_DASHATT3_DASHATT4_2,
	PO_C17_DASHATT3_DASHATT4_2, PO_C17_DASHATT3_DASHATT4_2, PO_C17_DASHATT3_DASHATT4_2, PO_C17_DASHATT3_DASHATT4_3, PO_C17_DASHATT3_DASHATT4_3, PO_C17_DASHATT3_DASHATT4_3, PO_C17_DASHATT3_DASHATT4_3, PO_C17_DASHATT3_DASHATT4_3,
	PO_C17_DASHATT4, PO_C17_DASHATT4, PO_C17_DASHATT4_1, PO_C17_DASHATT4_1, PO_C17_DASHATT4_2, PO_C17_DASHATT4_2, PO_C17_DASHATT4_3, PO_C17_DASHATT4_3,
	PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1,
	PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1,
	PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1, PO_C17_DASHATT1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	8 * _2X, 8 * _2X, 15, 15, 7 * _2X, 7 * _2X, 13, 13,
	6 * _2X, 6 * _2X, 11, 11, 5 * _2X, 5 * _2X, 9, 9,
	4 * _2X, 4 * _2X, 7, 7, 3 * _2X, 3 * _2X, 5, 5,
	2 * _2X, 2 * _2X, 3, 3, 1 * _2X, 1 * _2X, 1, 1,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//IFRIT_UP
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C17_N0, PO_C17_N0_1, PO_C17_N0_2, PO_C17_N0_3, PO_C17_N1, PO_C17_N1_1, PO_C17_N1_2, PO_C17_N1_3,
	PO_C17_N2, PO_C17_N2_1, PO_C17_N2_2, PO_C17_N2_3, PO_C17_N3, PO_C17_N3, PO_C17_N3, PO_C17_N3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	-3 * _2X, -3 * _2X, -3 * _2X, -3 * _2X, -3 * _2X, -3 * _2X, -3 * _2X, -3 * _2X,
	-3 * _2X, -3 * _2X, -3 * _2X, -3 * _2X, -3 * _2X, -3 * _2X, -3 * _2X, -3 * _2X,	//상태 프레임별 이동폭 Y

	//IFRIT_DOWN
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C17_N0, PO_C17_N0_1, PO_C17_N0_2, PO_C17_N0_3, PO_C17_N1, PO_C17_N1_1, PO_C17_N1_2, PO_C17_N1_3,
	PO_C17_N2, PO_C17_N2_1, PO_C17_N2_2, PO_C17_N2_3, PO_C17_N3, PO_C17_N3, PO_C17_N3, PO_C17_N3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X,
	3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	IFRIT_NEUTRAL,	IFRIT_NEUTRAL_UP,	0,	0,	0,	0,
	IFRIT_NEUTRAL_UP,	IFRIT_ATTACK,	0,	0,	RANDOM,	50,
	IFRIT_NEUTRAL_UP,	IFRIT_MOVE,	0,	0,	RANDOM,	33,
	IFRIT_NEUTRAL_UP,	IFRIT_DOWN,	0,	0,	RANDOM,	33,
	IFRIT_NEUTRAL_DOWN,	IFRIT_DASH,	0,	0,	RANDOM,	50,
	IFRIT_NEUTRAL_DOWN,	IFRIT_UP,	0,	0,	RANDOM,	33,
	IFRIT_MOVE,	IFRIT_DOWN,	0,	0,	RANDOM,	30,
	IFRIT_MOVE,	IFRIT_NEUTRAL_UP,	0,	0,	RANDOM,	25,
	IFRIT_ATTACK,	IFRIT_NEUTRAL_UP,	0,	0,	0,	0,
	IFRIT_DASH,	IFRIT_NEUTRAL_DOWN,	0,	0,	0,	0,
	IFRIT_DOWN,	IFRIT_DASH,	0,	0,	RANDOM,	33,
	IFRIT_DOWN,	IFRIT_NEUTRAL_DOWN,	0,	0,	0,	0,
	IFRIT_UP,	IFRIT_ATTACK,	0,	0,	RANDOM,	33,
	IFRIT_UP,	IFRIT_MOVE,	0,	0,	RANDOM,	30,
	IFRIT_UP,	IFRIT_NEUTRAL_UP,	0,	0,	0,	0,
	-1,
};


//SNOWMAN
const signed short c18mv[] = {
	//상태 데이터
	12,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C18_N0, PO_C18_N0_1, PO_C18_N0_2, PO_C18_N0_3, PO_C18_N1, PO_C18_N1_1, PO_C18_N1_2, PO_C18_N1_3,
	PO_C18_N2, PO_C18_N2_1, PO_C18_N2_2, PO_C18_N2_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C18_W0, PO_C18_W0, PO_C18_W0_1, PO_C18_W0_2, PO_C18_W0_2, PO_C18_W0_3, PO_C18_W1, PO_C18_W1,
	PO_C18_W1_1, PO_C18_W1_2, PO_C18_W1_2, PO_C18_W1_3, PO_C18_W2, PO_C18_W2, PO_C18_W2_1, PO_C18_W2_2,
	PO_C18_W2_2, PO_C18_W2_3, PO_C18_W3, PO_C18_W3, PO_C18_W3_1, PO_C18_W3_2, PO_C18_W3_2, PO_C18_W3_3,	//상태 프레임별 모션
	1, 1, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 1, 1,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 1, 1, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 1, 1, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C18_W0, PO_C18_W0_1, PO_C18_W0_2, PO_C18_W0_3, PO_C18_W1, PO_C18_W1_1, PO_C18_W1_2, PO_C18_W1_3,
	PO_C18_W2, PO_C18_W2_1, PO_C18_W2_2, PO_C18_W2_3, PO_C18_W3, PO_C18_W3_1, PO_C18_W3_2, PO_C18_W3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	40,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C18_A0, PO_C18_A0_2, PO_C18_A1, PO_C18_A1, PO_C18_A1, PO_C18_A1, PO_C18_A1, PO_C18_A1,
	PO_C18_A1, PO_C18_A1_1, PO_C18_A1_1, PO_C18_A1_1, PO_C18_A1_1, PO_C18_A1_1, PO_C18_A1_1, PO_C18_A1_1,
	PO_C18_A1_2, PO_C18_A1_2, PO_C18_A1_2, PO_C18_A1_2, PO_C18_A1_2, PO_C18_A1_2, PO_C18_A1_2, PO_C18_A1_3,
	PO_C18_A1_3, PO_C18_A1_3, PO_C18_A1_3, PO_C18_A1_3, PO_C18_A1_3, PO_C18_A1_3, PO_C18_A2, PO_C18_A2_2,
	PO_C18_A3, PO_C18_A3_2, PO_C18_A4, PO_C18_A4_2, PO_C18_A5, PO_C18_A5_2, PO_C18_W0, PO_C18_W0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 5 * _2X, 5 * _2X,
	5 * _2X, 5 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	20,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C18_HIDE0, PO_C18_HIDE0_1, PO_C18_HIDE0_2, PO_C18_HIDE0_3, PO_C18_HIDE1, PO_C18_HIDE1_1, PO_C18_HIDE1_2, PO_C18_HIDE1_3,
	PO_C18_HIDE2, PO_C18_HIDE2_1, PO_C18_HIDE2_2, PO_C18_HIDE2_3, PO_C18_HIDE3, PO_C18_HIDE3_1, PO_C18_HIDE3_2, PO_C18_HIDE3_3,
	PO_C18_HIDE4, PO_C18_HIDE4, PO_C18_HIDE4, PO_C18_HIDE4,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C18_HIDE4, PO_C18_HIDE4, PO_C18_HIDE4, PO_C18_HIDE4, PO_C18_HIDE4, PO_C18_HIDE4, PO_C18_HIDE4, PO_C18_HIDE4,
	PO_C18_HIDE4, PO_C18_HIDE4, PO_C18_HIDE4, PO_C18_HIDE4, PO_C18_HIDE4, PO_C18_HIDE4, PO_C18_HIDE4, PO_C18_HIDE4,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	12,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C18_APPEAR0, PO_C18_APPEAR0_1, PO_C18_APPEAR0_2, PO_C18_APPEAR0_3, PO_C18_APPEAR1, PO_C18_APPEAR1_1, PO_C18_APPEAR1_2, PO_C18_APPEAR1_3,
	PO_C18_APPEAR2, PO_C18_APPEAR2, PO_C18_APPEAR2, PO_C18_APPEAR2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	SNOWMAN_NEUTRAL,	SNOWMAN_HIDE,	DISTANCE_CHECK_XY,	4 * 8 + 3,	RANDOM,	20,
	SNOWMAN_NEUTRAL,	SNOWMAN_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 3,	0,	0,
	SNOWMAN_NEUTRAL,	SNOWMAN_MOVE_FAST,	DISTANCE_CHECK_XY,	8 * 8 + 3,	0,	0,
	SNOWMAN_NEUTRAL,	SNOWMAN_MOVE,	COMPARE_FRAME,	20,	RANDOM,	50,
	SNOWMAN_MOVE,	SNOWMAN_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 3,	0,	0,
	SNOWMAN_MOVE,	SNOWMAN_MOVE_FAST,	DISTANCE_CHECK_XY,	8 * 8 + 3,	0,	0,
	SNOWMAN_MOVE,	SNOWMAN_NEUTRAL,	COMPARE_FRAME,	20,	RANDOM,	50,
	SNOWMAN_MOVE_FAST,	SNOWMAN_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 3,	0,	0,
	SNOWMAN_MOVE_FAST,	SNOWMAN_NEUTRAL,	DISTANCE_OUT_XY,	8 * 8 + 3,	0,	0,
	SNOWMAN_ATTACK,	SNOWMAN_NEUTRAL,	0,	0,	0,	0,
	SNOWMAN_HIDE,	SNOWMAN_HIDED,	0,	0,	0,	0,
	SNOWMAN_HIDED,	SNOWMAN_APPEAR,	DISTANCE_OUT_XY,	6 * 8 + 3,	0,	0,
	SNOWMAN_APPEAR,	SNOWMAN_NEUTRAL,	0,	0,	0,	0,
	-1,
};


//FACE 삼두상
const signed short c19mv[] = {
	//상태 데이터
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C19_N0, PO_C19_N0_1, PO_C19_N0_2, PO_C19_N0_3, PO_C19_N1, PO_C19_N1_N2_1, PO_C19_N1_N2_2, PO_C19_N1_N2_3,
	PO_C19_N2, PO_C19_N2_N3_1, PO_C19_N2_N3_2, PO_C19_N2_N3_3, PO_C19_N3, PO_C19_N3, PO_C19_N3_1, PO_C19_N3_1,
	PO_C19_N3_2, PO_C19_N3_2, PO_C19_N3_3, PO_C19_N3_3, PO_C19_N2, PO_C19_N2_N1_1, PO_C19_N2_N1_2, PO_C19_N2_N1_3,
	PO_C19_N1, PO_C19_N1_N0_1, PO_C19_N1_N0_2, PO_C19_N1_N0_3, PO_C19_N0, PO_C19_N0, PO_C19_N0, PO_C19_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C19_N0, PO_C19_N0_2, PO_C19_N1, PO_C19_N1_N2_2, PO_C19_N2, PO_C19_N2_N3_2, PO_C19_N3, PO_C19_N3_1,
	PO_C19_N3_2, PO_C19_N3_3, PO_C19_N2, PO_C19_N2_N1_2, PO_C19_N1, PO_C19_N1_N0_2, PO_C19_N0, PO_C19_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C19_N0, PO_C19_N0_2, PO_C19_N1, PO_C19_N1_N2_2, PO_C19_N2, PO_C19_N2_N3_2, PO_C19_N3, PO_C19_N3_1,
	PO_C19_N3_2, PO_C19_N3_3, PO_C19_N2, PO_C19_N2_N1_2, PO_C19_N1, PO_C19_N1_N0_2, PO_C19_N0, PO_C19_N0,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	26,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C19_A0, PO_C19_A0, PO_C19_A0_1, PO_C19_A0_1, PO_C19_A0_2, PO_C19_A0_2, PO_C19_A0_3, PO_C19_A0_3,
	PO_C19_A1, PO_C19_A1_2, PO_C19_A2, PO_C19_A2_2, PO_C19_A3, PO_C19_A3_2, PO_C19_A4, PO_C19_A4_2,
	PO_C19_A5, PO_C19_A5_2, PO_C19_A6, PO_C19_A6_2, PO_C19_A7, PO_C19_A7_2, PO_C19_A8, PO_C19_A8_2,
	PO_C19_A9, PO_C19_A9,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	FACE_STOP,	FACE_NEUTRAL,	DISTANCE_CHECK_XY,	6 * 8 + 3,	0,	0,
	FACE_NEUTRAL,	FACE_ATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 3,	0,	0,
	FACE_NEUTRAL,	FACE_STOP,	DISTANCE_OUT_XY,	6 * 8 + 3,	0,	0,
	FACE_ATTACK,	FACE_STOP,	0,	0,	0,	0,
	-1,
};

const signed short c20mv[] = {
	//상태 데이터
	//ICESUN_MOVE
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C20_N0, PO_C20_N0_1, PO_C20_N0_2, PO_C20_N0_3, PO_C20_N1, PO_C20_N1_N2_1, PO_C20_N1_N2_2, PO_C20_N1_N2_3,
	PO_C20_N2, PO_C20_N2_N3_1, PO_C20_N2_N3_2, PO_C20_N2_N3_3, PO_C20_N3, PO_C20_N3, PO_C20_N3_1, PO_C20_N3_1,
	PO_C20_N3_2, PO_C20_N3_2, PO_C20_N3_3, PO_C20_N3_3, PO_C20_N2, PO_C20_N2_N1_1, PO_C20_N2_N1_2, PO_C20_N2_N1_3,
	PO_C20_N1, PO_C20_N1_N0_1, PO_C20_N1_N0_2, PO_C20_N1_N0_3, PO_C20_N0, PO_C20_N0, PO_C20_N0, PO_C20_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C20_A0, PO_C20_A0, PO_C20_A0_1, PO_C20_A0_1, PO_C20_A0_2, PO_C20_A0_2, PO_C20_A0_3, PO_C20_A0_3,
	PO_C20_A1, PO_C20_A1, PO_C20_A1_A0_1, PO_C20_A1_A0_1, PO_C20_A1_A0_2, PO_C20_A1_A0_2, PO_C20_A1_A0_3, PO_C20_A1_A0_3,
	PO_C20_A0, PO_C20_A0, PO_C20_A0_1, PO_C20_A0_1, PO_C20_A0_2, PO_C20_A0_2, PO_C20_A0_3, PO_C20_A0_3,
	PO_C20_A1, PO_C20_A1, PO_C20_A1_A0_1, PO_C20_A1_A0_1, PO_C20_A1_A0_2, PO_C20_A1_A0_2, PO_C20_A1_A0_3, PO_C20_A1_A0_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	72,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C20_A0, PO_C20_A0, PO_C20_A0_1, PO_C20_A0_1, PO_C20_A0_2, PO_C20_A0_2, PO_C20_A0_3, PO_C20_A0_3,
	PO_C20_A1, PO_C20_A1, PO_C20_A1, PO_C20_A1, PO_C20_A1_A2_1, PO_C20_A1_A2_1, PO_C20_A1_A2_1, PO_C20_A1_A2_1,
	PO_C20_A1_A2_2, PO_C20_A1_A2_2, PO_C20_A1_A2_2, PO_C20_A1_A2_2, PO_C20_A1_A2_3, PO_C20_A1_A2_3, PO_C20_A1_A2_3, PO_C20_A1_A2_3,
	PO_C20_A2, PO_C20_A2, PO_C20_A2_1, PO_C20_A2_1, PO_C20_A2_2, PO_C20_A2_2, PO_C20_A2_3, PO_C20_A2_3,
	PO_C20_A3, PO_C20_A3, PO_C20_A3_1, PO_C20_A3_1, PO_C20_A3_2, PO_C20_A3_2, PO_C20_A3_3, PO_C20_A3_3,
	PO_C20_A4, PO_C20_A4, PO_C20_A4_1, PO_C20_A4_1, PO_C20_A4_2, PO_C20_A4_2, PO_C20_A4_3, PO_C20_A4_3,
	PO_C20_A5, PO_C20_A5, PO_C20_A5_1, PO_C20_A5_1, PO_C20_A5_2, PO_C20_A5_2, PO_C20_A5_3, PO_C20_A5_3,
	PO_C20_A6, PO_C20_A6, PO_C20_A6_1, PO_C20_A6_1, PO_C20_A6_2, PO_C20_A6_2, PO_C20_A6_3, PO_C20_A6_3,
	PO_C20_A7, PO_C20_A7, PO_C20_A7, PO_C20_A7, PO_C20_A7, PO_C20_A7, PO_C20_A7, PO_C20_A7,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	ICESUN_NEUTRAL,	ICESUN_ATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 6,	0,	0,
	ICESUN_ATTACK,	ICESUN_NEUTRAL,	0,	0,	0,	0,
	-1,
};

const signed short c21mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C21_N0, PO_C21_N0_1, PO_C21_N0_2, PO_C21_N0_3, PO_C21_N1, PO_C21_N1_1, PO_C21_N1_2, PO_C21_N1_3,
	PO_C21_N2, PO_C21_N2_1, PO_C21_N2_2, PO_C21_N2_3, PO_C21_N3, PO_C21_N3, PO_C21_N3, PO_C21_N3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	30,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C21_W0, PO_C21_W0_2, PO_C21_W1, PO_C21_W1_2, PO_C21_W2, PO_C21_W2_2, PO_C21_W3, PO_C21_W3_2,
	PO_C21_W4, PO_C21_W4_2, PO_C21_W5, PO_C21_W5_2, PO_C21_W6, PO_C21_W6_2, PO_C21_W7, PO_C21_W7_2,
	PO_C21_W8, PO_C21_W8_2, PO_C21_W9, PO_C21_W9_2, PO_C21_W10, PO_C21_W10_2, PO_C21_W11, PO_C21_W11_2,
	PO_C21_W12, PO_C21_W12_2, PO_C21_W13, PO_C21_W13_2, PO_C21_N3, PO_C21_N3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	70,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C21_N0, PO_C21_N0_2, PO_C21_N1, PO_C21_N1_1, PO_C21_N1_2, PO_C21_N1_3, PO_C21_N2, PO_C21_N2_1,
	PO_C21_N2_2, PO_C21_N2_3, PO_C21_N3, PO_C21_N3_A1_1, PO_C21_N3_A1_2, PO_C21_N3_A1_3, PO_C21_A1, PO_C21_A1_2,
	PO_C21_A2, PO_C21_A2_A1_2, PO_C21_A1, PO_C21_A1_2, PO_C21_A2, PO_C21_A2_A1_2, PO_C21_A1, PO_C21_A1_2,
	PO_C21_A2, PO_C21_A2_A3_2, PO_C21_A3, PO_C21_A3_2, PO_C21_A4, PO_C21_A4_2, PO_C21_A5, PO_C21_A5_2,
	PO_C21_A6, PO_C21_A6, PO_C21_A6, PO_C21_A6, PO_C21_A6, PO_C21_A6, PO_C21_A6, PO_C21_A6,
	PO_C21_A6, PO_C21_A6_1, PO_C21_A6_1, PO_C21_A6_1, PO_C21_A6_1, PO_C21_A6_1, PO_C21_A6_1, PO_C21_A6_1,
	PO_C21_A6_1, PO_C21_A6_1, PO_C21_A6_2, PO_C21_A6_2, PO_C21_A6_2, PO_C21_A6_2, PO_C21_A6_2, PO_C21_A6_2,
	PO_C21_A6_2, PO_C21_A6_2, PO_C21_A6_2, PO_C21_A6_3, PO_C21_A6_3, PO_C21_A6_3, PO_C21_A6_3, PO_C21_A6_3,
	PO_C21_A6_3, PO_C21_A6_3, PO_C21_A6_3, PO_C21_A6_3, PO_C21_N0, PO_C21_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	82,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C21_SHOT0, PO_C21_SHOT0_2, PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2,
	PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2,
	PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2,
	PO_C21_SHOT2, PO_C21_SHOT2_SHOT3_2, PO_C21_SHOT3, PO_C21_SHOT3_2, PO_C21_SHOT4, PO_C21_SHOT4_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2,
	PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT3_2, PO_C21_SHOT3, PO_C21_SHOT3_2,
	PO_C21_SHOT4, PO_C21_SHOT4_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2,
	PO_C21_SHOT2, PO_C21_SHOT2_SHOT3_2, PO_C21_SHOT3, PO_C21_SHOT3_2, PO_C21_SHOT4, PO_C21_SHOT4_SHOT2_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2,
	PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2,
	PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2,
	PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2,
	PO_C21_SHOT1, PO_C21_SHOT1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	92,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C21_BREAK2_0, PO_C21_BREAK2_0_2, PO_C21_BREAK2_1, PO_C21_BREAK2_1_2, PO_C21_BREAK2_2, PO_C21_BREAK2_2_2, PO_C21_BREAK2_3, PO_C21_BREAK2_3_2,
	PO_C21_BREAK2_4, PO_C21_BREAK2_4_2, PO_C21_BREAK2_5, PO_C21_BREAK2_5_2, PO_C21_BREAK2_6, PO_C21_BREAK2_6_2, PO_C21_BREAK2_7, PO_C21_BREAK2_7_2,
	PO_C21_BREAK2_8, PO_C21_BREAK2_8_2, PO_C21_BREAK2_9, PO_C21_BREAK2_9_BREAK2_6_2, PO_C21_BREAK2_6, PO_C21_BREAK2_6_2, PO_C21_BREAK2_7, PO_C21_BREAK2_7_2,
	PO_C21_BREAK2_8, PO_C21_BREAK2_8_2, PO_C21_BREAK2_9, PO_C21_BREAK2_9_BREAK2_6_2, PO_C21_BREAK2_6, PO_C21_BREAK2_6_2, PO_C21_BREAK2_7, PO_C21_BREAK2_7_2,
	PO_C21_BREAK2_8, PO_C21_BREAK2_8_2, PO_C21_BREAK2_9, PO_C21_BREAK2_9_BREAK2_6_2, PO_C21_BREAK2_6, PO_C21_BREAK2_6_2, PO_C21_BREAK2_7, PO_C21_BREAK2_7_2,
	PO_C21_BREAK2_8, PO_C21_BREAK2_8_2, PO_C21_BREAK2_9, PO_C21_BREAK2_9_BREAK2_6_2, PO_C21_BREAK2_6, PO_C21_BREAK2_6_2, PO_C21_BREAK2_7, PO_C21_BREAK2_7_2,
	PO_C21_BREAK2_8, PO_C21_BREAK2_8_2, PO_C21_BREAK2_9, PO_C21_BREAK2_9_BREAK2_6_2, PO_C21_BREAK2_6, PO_C21_BREAK2_6_2, PO_C21_BREAK2_7, PO_C21_BREAK2_7_2,
	PO_C21_BREAK2_8, PO_C21_BREAK2_8_2, PO_C21_BREAK2_9, PO_C21_BREAK2_9_BREAK2_6_2, PO_C21_BREAK2_6, PO_C21_BREAK2_6_2, PO_C21_BREAK2_7, PO_C21_BREAK2_7_2,
	PO_C21_BREAK2_8, PO_C21_BREAK2_8_2, PO_C21_BREAK2_9, PO_C21_BREAK2_9_RETURN0_2, PO_C21_RETURN0, PO_C21_RETURN0_2, PO_C21_RETURN1, PO_C21_RETURN1_2,
	PO_C21_RETURN2, PO_C21_RETURN2_2, PO_C21_RETURN3, PO_C21_RETURN3_2, PO_C21_RETURN4, PO_C21_RETURN4_2, PO_C21_RETURN5, PO_C21_RETURN5,
	PO_C21_RETURN5_1, PO_C21_RETURN5_2, PO_C21_RETURN5_2, PO_C21_RETURN5_3, PO_C21_RETURN6, PO_C21_RETURN6_2, PO_C21_RETURN7, PO_C21_RETURN7_2,
	PO_C21_RETURN8, PO_C21_RETURN8_2, PO_C21_RETURN9, PO_C21_RETURN9,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 101, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 101, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C21_BREAK0_0, PO_C21_BREAK0_0_1, PO_C21_BREAK0_0_2, PO_C21_BREAK0_0_3, PO_C21_BREAK0_1, PO_C21_BREAK0_1_1, PO_C21_BREAK0_1_2, PO_C21_BREAK0_1_3,
	PO_C21_BREAK0_2, PO_C21_BREAK0_2_1, PO_C21_BREAK0_2_2, PO_C21_BREAK0_2_3, PO_C21_BREAK0_3, PO_C21_BREAK0_3_1, PO_C21_BREAK0_3_2, PO_C21_BREAK0_3_3,
	PO_C21_BREAK0_4, PO_C21_BREAK0_4_1, PO_C21_BREAK0_4_2, PO_C21_BREAK0_4_3, PO_C21_BREAK0_5, PO_C21_BREAK0_5, PO_C21_BREAK0_5, PO_C21_BREAK0_5,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C21_N0, PO_C21_N0_1, PO_C21_N0_2, PO_C21_N0_3, PO_C21_N1, PO_C21_N1_1, PO_C21_N1_2, PO_C21_N1_3,
	PO_C21_N2, PO_C21_N2_1, PO_C21_N2_2, PO_C21_N2_3, PO_C21_N3, PO_C21_N3_N0_1, PO_C21_N3_N0_2, PO_C21_N3_N0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	62,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C21_A0, PO_C21_A0_2, PO_C21_A1, PO_C21_A1_2, PO_C21_A2, PO_C21_A2_A1_2, PO_C21_A1, PO_C21_A1_2,
	PO_C21_A2, PO_C21_A2_A1_2, PO_C21_A1, PO_C21_A1_2, PO_C21_A2, PO_C21_A2_A1_2, PO_C21_A1, PO_C21_A1_2,
	PO_C21_A2, PO_C21_A2_A3_2, PO_C21_A3, PO_C21_A3_2, PO_C21_A4, PO_C21_A4_2, PO_C21_A5, PO_C21_A5_2,
	PO_C21_A6, PO_C21_A6, PO_C21_A6, PO_C21_A6, PO_C21_A6, PO_C21_A6, PO_C21_A6, PO_C21_A6,
	PO_C21_A6, PO_C21_A6_1, PO_C21_A6_1, PO_C21_A6_1, PO_C21_A6_1, PO_C21_A6_1, PO_C21_A6_1, PO_C21_A6_1,
	PO_C21_A6_1, PO_C21_A6_1, PO_C21_A6_2, PO_C21_A6_2, PO_C21_A6_2, PO_C21_A6_2, PO_C21_A6_2, PO_C21_A6_2,
	PO_C21_A6_2, PO_C21_A6_2, PO_C21_A6_2, PO_C21_A6_3, PO_C21_A6_3, PO_C21_A6_3, PO_C21_A6_3, PO_C21_A6_3,
	PO_C21_A6_3, PO_C21_A6_3, PO_C21_A6_3, PO_C21_A6_3, PO_C21_N0, PO_C21_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	114,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C21_SHOT0, PO_C21_SHOT0_2, PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2,
	PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2,
	PO_C21_SHOT2, PO_C21_SHOT2_SHOT3_2, PO_C21_SHOT3, PO_C21_SHOT3_2, PO_C21_SHOT4, PO_C21_SHOT4_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2,
	PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT3_2, PO_C21_SHOT3, PO_C21_SHOT3_2,
	PO_C21_SHOT4, PO_C21_SHOT4_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2,
	PO_C21_SHOT2, PO_C21_SHOT2_SHOT3_2, PO_C21_SHOT3, PO_C21_SHOT3_2, PO_C21_SHOT4, PO_C21_SHOT4_SHOT2_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2,
	PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2,
	PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2,
	PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2, PO_C21_SHOT1, PO_C21_SHOT1_2, PO_C21_SHOT2, PO_C21_SHOT2_SHOT1_2,
	PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1,
	PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1,
	PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1,
	PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1,
	PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1, PO_C21_SHOT1,
	PO_C21_SHOT1, PO_C21_SHOT1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C21_BREAK1_0, PO_C21_BREAK1_0_1, PO_C21_BREAK1_0_2, PO_C21_BREAK1_0_3, PO_C21_BREAK1_1, PO_C21_BREAK1_1_1, PO_C21_BREAK1_1_2, PO_C21_BREAK1_1_3,
	PO_C21_BREAK1_2, PO_C21_BREAK1_2_1, PO_C21_BREAK1_2_2, PO_C21_BREAK1_2_3, PO_C21_BREAK1_3, PO_C21_BREAK1_3_1, PO_C21_BREAK1_3_2, PO_C21_BREAK1_3_3,
	PO_C21_BREAK1_4, PO_C21_BREAK1_4_1, PO_C21_BREAK1_4_2, PO_C21_BREAK1_4_3, PO_C21_BREAK1_5, PO_C21_BREAK1_5, PO_C21_BREAK1_5, PO_C21_BREAK1_5,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C21_N0, PO_C21_N0_1, PO_C21_N0_2, PO_C21_N0_3, PO_C21_N1, PO_C21_N1_1, PO_C21_N1_2, PO_C21_N1_3,
	PO_C21_N2, PO_C21_N2_1, PO_C21_N2_2, PO_C21_N2_3, PO_C21_N3, PO_C21_N3, PO_C21_N3, PO_C21_N3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	54,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C21_A0, PO_C21_A0_2, PO_C21_A1, PO_C21_A1_2, PO_C21_A2, PO_C21_A2_A1_2, PO_C21_A1, PO_C21_A1_2,
	PO_C21_A2, PO_C21_A2_A3_2, PO_C21_A3, PO_C21_A3_2, PO_C21_A4, PO_C21_A4_2, PO_C21_A5, PO_C21_A5_2,
	PO_C21_A6, PO_C21_A6, PO_C21_A6, PO_C21_A6, PO_C21_A6, PO_C21_A6, PO_C21_A6, PO_C21_A6,
	PO_C21_A6, PO_C21_A6_1, PO_C21_A6_1, PO_C21_A6_1, PO_C21_A6_1, PO_C21_A6_1, PO_C21_A6_1, PO_C21_A6_1,
	PO_C21_A6_1, PO_C21_A6_1, PO_C21_A6_2, PO_C21_A6_2, PO_C21_A6_2, PO_C21_A6_2, PO_C21_A6_2, PO_C21_A6_2,
	PO_C21_A6_2, PO_C21_A6_2, PO_C21_A6_2, PO_C21_A6_3, PO_C21_A6_3, PO_C21_A6_3, PO_C21_A6_3, PO_C21_A6_3,
	PO_C21_A6_3, PO_C21_A6_3, PO_C21_A6_3, PO_C21_A6_3, PO_C21_N0, PO_C21_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C21_BREAK2_0, PO_C21_BREAK2_0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	MAMMOTH_NEUTRAL,	MAMMOTH_SHOT,	0,	0,	RANDOM,	60,
	MAMMOTH_NEUTRAL,	MAMMOTH_SHOCKWAVE,	0,	0,	RANDOM,	60,
	MAMMOTH_NEUTRAL,	MAMMOTH_MOVE,	0,	0,	0,	0,
	MAMMOTH_MOVE,	MAMMOTH_NEUTRAL,	0,	0,	0,	0,
	MAMMOTH_SHOCKWAVE,	MAMMOTH_NEUTRAL,	0,	0,	0,	0,
	MAMMOTH_SHOT,	MAMMOTH_NEUTRAL,	0,	0,	0,	0,
	MAMMOTH_BREAK0,	MAMMOTH_NEUTRAL0,	0,	0,	0,	0,
	MAMMOTH_BREAK1,	MAMMOTH_NEUTRAL1,	0,	0,	0,	0,
	MAMMOTH_BREAK2,	MAMMOTH_RETURN,	0,	0,	0,	0,
	MAMMOTH_RETURN,	MAMMOTH_NEUTRAL,	0,	0,	0,	0,
	MAMMOTH_BREAK0_SHOCKWAVE,	MAMMOTH_NEUTRAL0,	0,	0,	0,	0,
	MAMMOTH_BREAK0_SHOT,	MAMMOTH_NEUTRAL0,	0,	0,	0,	0,
	MAMMOTH_BREAK1_SHOCKWAVE,	MAMMOTH_NEUTRAL1,	0,	0,	0,	0,
	MAMMOTH_NEUTRAL0,	MAMMOTH_BREAK0_SHOT,	0,	0,	RANDOM,	60,
	MAMMOTH_NEUTRAL0,	MAMMOTH_BREAK0_SHOCKWAVE,	0,	0,	RANDOM,	60,
	MAMMOTH_NEUTRAL1,	MAMMOTH_BREAK1_SHOCKWAVE,	0,	0,	0,	0,
	-1,
};

const signed short c22mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C22_N0, PO_C22_N0_1, PO_C22_N0_2, PO_C22_N0_3, PO_C22_N1, PO_C22_N1_1, PO_C22_N1_2, PO_C22_N1_3,
	PO_C22_N2, PO_C22_N2_1, PO_C22_N2_2, PO_C22_N2_3, PO_C22_N3, PO_C22_N3_1, PO_C22_N3_2, PO_C22_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C22_N0, PO_C22_N0_1, PO_C22_N0_2, PO_C22_N0_3, PO_C22_N1, PO_C22_N1_1, PO_C22_N1_2, PO_C22_N1_3,
	PO_C22_N2, PO_C22_N2_1, PO_C22_N2_2, PO_C22_N2_3, PO_C22_N3, PO_C22_N3_1, PO_C22_N3_2, PO_C22_N3_3,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C22_N0, PO_C22_N0_1, PO_C22_N0_2, PO_C22_N0_3, PO_C22_N1, PO_C22_N1_1, PO_C22_N1_2, PO_C22_N1_3,
	PO_C22_N2, PO_C22_N2_1, PO_C22_N2_2, PO_C22_N2_3, PO_C22_N3, PO_C22_N3_1, PO_C22_N3_2, PO_C22_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c23mv[] = {
	//상태 데이터
	//CRYSTAL_NEUTRAL
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C23_N0, PO_C23_N0_1, PO_C23_N0_2, PO_C23_N0_3, PO_C23_N1, PO_C23_N1_1, PO_C23_N1_2, PO_C23_N1_3,
	PO_C23_N2, PO_C23_N2_1, PO_C23_N2_2, PO_C23_N2_3, PO_C23_N3, PO_C23_N3_1, PO_C23_N3_2, PO_C23_N3_3,
	PO_C23_N4, PO_C23_N4_1, PO_C23_N4_2, PO_C23_N4_3, PO_C23_N5, PO_C23_N5_1, PO_C23_N5_2, PO_C23_N5_3,
	PO_C23_N6, PO_C23_N6_1, PO_C23_N6_2, PO_C23_N6_3, PO_C23_N7, PO_C23_N7_1, PO_C23_N7_2, PO_C23_N7_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CRYSTAL_STOP
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C23_N0, PO_C23_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CRYSTAL_ATTACK
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C23_A0, PO_C23_A0, PO_C23_A0_1, PO_C23_A0_2, PO_C23_A0_2, PO_C23_A0_3, PO_C23_A1, PO_C23_A1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C23_LIGHTNING0, PO_C23_LIGHTNING0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C23_LIGHTNING0, PO_C23_LIGHTNING0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	CRYSTAL_NEUTRAL,	CRYSTAL_ATTACK,	0,	0,	RANDOM,	15,
	CRYSTAL_STOP,	CRYSTAL_NEUTRAL,	DISTANCE_OUT_XY,	10 * 8 + 7,	0,	0,
	CRYSTAL_ATTACK,	CRYSTAL_NEUTRAL,	0,	0,	0,	0,
	-1,
};

const signed short c24mv[] = {
	//상태 데이터
	//THUNDER_NEUTRAL
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C24_N0, PO_C24_N0_1, PO_C24_N0_2, PO_C24_N0_3, PO_C24_N1, PO_C24_N1_1, PO_C24_N1_2, PO_C24_N1_3,
	PO_C24_N2, PO_C24_N2_1, PO_C24_N2_2, PO_C24_N2_3, PO_C24_N3, PO_C24_N3_1, PO_C24_N3_2, PO_C24_N3_3,
	PO_C24_N4, PO_C24_N4_1, PO_C24_N4_2, PO_C24_N4_3, PO_C24_N5, PO_C24_N5_1, PO_C24_N5_2, PO_C24_N5_3,
	PO_C24_N6, PO_C24_N6_1, PO_C24_N6_2, PO_C24_N6_3, PO_C24_N7, PO_C24_N7_1, PO_C24_N7_2, PO_C24_N7_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//THUNDER_MOVE
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C24_N0, PO_C24_N0_1, PO_C24_N0_2, PO_C24_N0_3, PO_C24_N1, PO_C24_N1_1, PO_C24_N1_2, PO_C24_N1_3,
	PO_C24_N2, PO_C24_N2_1, PO_C24_N2_2, PO_C24_N2_3, PO_C24_N3, PO_C24_N3_1, PO_C24_N3_2, PO_C24_N3_3,
	PO_C24_N4, PO_C24_N4_1, PO_C24_N4_2, PO_C24_N4_3, PO_C24_N5, PO_C24_N5_1, PO_C24_N5_2, PO_C24_N5_3,
	PO_C24_N6, PO_C24_N6_1, PO_C24_N6_2, PO_C24_N6_3, PO_C24_N7, PO_C24_N7_1, PO_C24_N7_2, PO_C24_N7_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//THUNDER_PLAYER_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C24_N0, PO_C24_N0_2, PO_C24_N1, PO_C24_N1_2, PO_C24_N2, PO_C24_N2_2, PO_C24_N3, PO_C24_N3_2,
	PO_C24_N4, PO_C24_N4_2, PO_C24_N5, PO_C24_N5_2, PO_C24_N6, PO_C24_N6_2, PO_C24_N7, PO_C24_N7_2,	//상태 프레임별 모션
	121, 0 * _2X, 121, 0 * _2X, 121, 0 * _2X, 121, 0 * _2X,
	121, 0 * _2X, 121, 0 * _2X, 121, 0 * _2X, 121, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//THUNDER_ATTACK
	56,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C24_A0, PO_C24_A0_1, PO_C24_A0_2, PO_C24_A0_3, PO_C24_A1, PO_C24_A1_1, PO_C24_A1_2, PO_C24_A1_3,
	PO_C24_A2, PO_C24_A2_1, PO_C24_A2_2, PO_C24_A2_3, PO_C24_A3, PO_C24_A3, PO_C24_A3, PO_C24_A3_1,
	PO_C24_A3_1, PO_C24_A3_1, PO_C24_A3_2, PO_C24_A3_2, PO_C24_A3_2, PO_C24_A3_3, PO_C24_A3_3, PO_C24_A3_3,
	PO_C24_A4, PO_C24_A4_1, PO_C24_A4_2, PO_C24_A4_3, PO_C24_A5, PO_C24_A5_A4_1, PO_C24_A5_A4_2, PO_C24_A5_A4_3,
	PO_C24_A4, PO_C24_A4_1, PO_C24_A4_2, PO_C24_A4_3, PO_C24_A5, PO_C24_A5_A4_1, PO_C24_A5_A4_2, PO_C24_A5_A4_3,
	PO_C24_A4, PO_C24_A4_1, PO_C24_A4_2, PO_C24_A4_3, PO_C24_A5, PO_C24_A5_A6_1, PO_C24_A5_A6_2, PO_C24_A5_A6_3,
	PO_C24_A6, PO_C24_A6_1, PO_C24_A6_2, PO_C24_A6_3, PO_C24_A7, PO_C24_A7, PO_C24_A7, PO_C24_A7,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	THUNDER_NEUTRAL,	THUNDER_ATTACK,	DISTANCE_CHECK_XY,	1 * 8 + 7,	RANDOM,	60,
	THUNDER_NEUTRAL,	THUNDER_PLAYER_MOVE,	DISTANCE_CHECK_XY,	7 * 8 + 7,	0,	0,
	THUNDER_NEUTRAL,	THUNDER_MOVE,	COMPARE_FRAME,	16,	RANDOM,	30,
	THUNDER_PLAYER_MOVE,	THUNDER_ATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 7,	0,	0,
	THUNDER_PLAYER_MOVE,	THUNDER_NEUTRAL,	COMPARE_FRAME,	16,	RANDOM,	30,
	THUNDER_MOVE,	THUNDER_ATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 7,	RANDOM,	70,
	THUNDER_MOVE,	THUNDER_PLAYER_MOVE,	DISTANCE_CHECK_XY,	7 * 8 + 7,	0,	0,
	THUNDER_MOVE,	THUNDER_NEUTRAL,	COMPARE_FRAME,	16,	RANDOM,	30,
	THUNDER_ATTACK,	THUNDER_NEUTRAL,	0,	0,	0,	0,
	-1,
};

const signed short c25mv[] = {
	//상태 데이터
	//THUNDERBOSS_NEUTRAL
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C25_W0_L, PO_C25_W0_L, PO_C25_W0_L, PO_C25_W0_L, PO_C25_W0_L, PO_C25_W0_L, PO_C25_W0_L, PO_C25_W0_L,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//THUNDERBOSS_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C25_A0_L, PO_C25_A0_L_1, PO_C25_A0_L_2, PO_C25_A0_L_3, PO_C25_A1_L, PO_C25_A1_L_1, PO_C25_A1_L_2, PO_C25_A1_L_3,
	PO_C25_A2_L, PO_C25_A2_L_1, PO_C25_A2_L_2, PO_C25_A2_L_3, PO_C25_A3_L, PO_C25_A3_L_1, PO_C25_A3_L_2, PO_C25_A3_L_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//THUNDERBOSS_ATTACK
	32,	//상태 프레임 카운트
	SET_DIR_PLAYER,	//초기화 조건
	PO_C25_A4_L, PO_C25_A4_L_1, PO_C25_A4_L_2, PO_C25_A4_L_3, PO_C25_A5_L, PO_C25_A5_L_1, PO_C25_A5_L_2, PO_C25_A5_L_3,
	PO_C25_A6_L, PO_C25_A6_L_1, PO_C25_A6_L_2, PO_C25_A6_L_3, PO_C25_A7_L, PO_C25_A7_L_1, PO_C25_A7_L_2, PO_C25_A7_L_3,
	PO_C25_DASH_L, PO_C25_DASH_L, PO_C25_DASH_L, PO_C25_DASH_L, PO_C25_DASH_L_1, PO_C25_DASH_L_1, PO_C25_DASH_L_1, PO_C25_DASH_L_1,
	PO_C25_DASH_L_2, PO_C25_DASH_L_2, PO_C25_DASH_L_2, PO_C25_DASH_L_2, PO_C25_DASH_L_3, PO_C25_DASH_L_3, PO_C25_DASH_L_3, PO_C25_DASH_L_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c26mv[] = {
	//상태 데이터
	//GOLEM_STOP
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C26_N0, PO_C26_N0_N1_1, PO_C26_N0_N1_2, PO_C26_N0_N1_3, PO_C26_N1, PO_C26_N1_1, PO_C26_N1_2, PO_C26_N1_3,
	PO_C26_N2, PO_C26_N2_1, PO_C26_N2_2, PO_C26_N2_3, PO_C26_N3, PO_C26_N3, PO_C26_N3, PO_C26_N3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GOLEM_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C26_N0, PO_C26_N0_N1_1, PO_C26_N0_N1_2, PO_C26_N0_N1_3, PO_C26_N1, PO_C26_N1_1, PO_C26_N1_2, PO_C26_N1_3,
	PO_C26_N2, PO_C26_N2_1, PO_C26_N2_2, PO_C26_N2_3, PO_C26_N3, PO_C26_N3_1, PO_C26_N3_2, PO_C26_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GOLEM_MOVE
	40,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_RANDOM,	//초기화 조건
	PO_C26_W2, PO_C26_W2_1, PO_C26_W2_2, PO_C26_W2_3, PO_C26_W3, PO_C26_W3_1, PO_C26_W3_2, PO_C26_W3_3,
	PO_C26_W4, PO_C26_W4_1, PO_C26_W4_2, PO_C26_W4_3, PO_C26_W5, PO_C26_W5, PO_C26_W5, PO_C26_W5_1,
	PO_C26_W5_1, PO_C26_W5_1, PO_C26_W5_2, PO_C26_W5_2, PO_C26_W5_2, PO_C26_W5_3, PO_C26_W5_3, PO_C26_W5_3,
	PO_C26_W0, PO_C26_W0_1, PO_C26_W0_2, PO_C26_W0_3, PO_C26_W1, PO_C26_W1_1, PO_C26_W1_2, PO_C26_W1_3,
	PO_C26_W2, PO_C26_W2, PO_C26_W2, PO_C26_W2, PO_C26_W2, PO_C26_W2, PO_C26_W2, PO_C26_W2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 1, 1, 1, 1,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GOLEM_MOVE_FAST
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C26_W2, PO_C26_W2_1, PO_C26_W2_2, PO_C26_W2_3, PO_C26_W3, PO_C26_W3_1, PO_C26_W3_2, PO_C26_W3_3,
	PO_C26_W4, PO_C26_W4_1, PO_C26_W4_2, PO_C26_W4_3, PO_C26_W5, PO_C26_W5_1, PO_C26_W5_2, PO_C26_W5_3,
	PO_C26_W0, PO_C26_W0_1, PO_C26_W0_2, PO_C26_W0_3, PO_C26_W1, PO_C26_W1_1, PO_C26_W1_2, PO_C26_W1_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GOLEM_ATTACK
	52,	//상태 프레임 카운트
	SET_DIR_PLAYER,	//초기화 조건
	PO_C26_A0, PO_C26_A0, PO_C26_A0_1, PO_C26_A0_1, PO_C26_A0_2, PO_C26_A0_2, PO_C26_A0_3, PO_C26_A0_3,
	PO_C26_A1, PO_C26_A1, PO_C26_A1, PO_C26_A1, PO_C26_A1_1, PO_C26_A1_1, PO_C26_A1_1, PO_C26_A1_1,
	PO_C26_A1_2, PO_C26_A1_2, PO_C26_A1_2, PO_C26_A1_2, PO_C26_A1_3, PO_C26_A1_3, PO_C26_A1_3, PO_C26_A1_3,
	PO_C26_A2, PO_C26_A2_1, PO_C26_A2_2, PO_C26_A2_3, PO_C26_A3, PO_C26_A3_1, PO_C26_A3_2, PO_C26_A3_3,
	PO_C26_A4, PO_C26_A4, PO_C26_A4, PO_C26_A4, PO_C26_A4, PO_C26_A4_A0_1, PO_C26_A4_A0_1, PO_C26_A4_A0_1,
	PO_C26_A4_A0_1, PO_C26_A4_A0_1, PO_C26_A4_A0_2, PO_C26_A4_A0_2, PO_C26_A4_A0_2, PO_C26_A4_A0_2, PO_C26_A4_A0_2, PO_C26_A4_A0_3,
	PO_C26_A4_A0_3, PO_C26_A4_A0_3, PO_C26_A4_A0_3, PO_C26_A4_A0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	7 * _2X, 7 * _2X, 4 * _2X, 4 * _2X, 3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GOLEM_GUARD
	24,	//상태 프레임 카운트
	SET_DIR_PLAYER,	//초기화 조건
	PO_C26_G0, PO_C26_G0_1, PO_C26_G0_2, PO_C26_G0_3, PO_C26_G1, PO_C26_G1, PO_C26_G1, PO_C26_G1,
	PO_C26_G1, PO_C26_G1_1, PO_C26_G1_1, PO_C26_G1_1, PO_C26_G1_1, PO_C26_G1_1, PO_C26_G1_2, PO_C26_G1_2,
	PO_C26_G1_2, PO_C26_G1_2, PO_C26_G1_2, PO_C26_G1_3, PO_C26_G1_3, PO_C26_G1_3, PO_C26_G1_3, PO_C26_G1_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GOLEM_COUNTER
	20,	//상태 프레임 카운트
	0,	//초기화 조건
	PO_C26_A2, PO_C26_A2_1, PO_C26_A2_2, PO_C26_A2_3, PO_C26_A3, PO_C26_A3_1, PO_C26_A3_2, PO_C26_A3_3,
	PO_C26_A4, PO_C26_A4, PO_C26_A4_N0_1, PO_C26_A4_N0_1, PO_C26_A4_N0_2, PO_C26_A4_N0_2, PO_C26_A4_N0_3, PO_C26_A4_N0_3,
	PO_C26_N0, PO_C26_N0, PO_C26_N0, PO_C26_N0,	//상태 프레임별 모션
	15 * _2X, 15 * _2X, 15 * _2X, 15 * _2X, 5, 5, 5, 5,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GOLEM_JUMP
	44,	//상태 프레임 카운트
	0,	//초기화 조건
	PO_C26_JU0, PO_C26_JU0_1, PO_C26_JU0_2, PO_C26_JU0_3, PO_C26_JU1, PO_C26_JU1, PO_C26_JU1_1, PO_C26_JU1_1,
	PO_C26_JU1_2, PO_C26_JU1_2, PO_C26_JU1_3, PO_C26_JU1_3, PO_C26_JU2, PO_C26_JU2, PO_C26_JU2, PO_C26_JU2_1,
	PO_C26_JU2_1, PO_C26_JU2_1, PO_C26_JU2_2, PO_C26_JU2_2, PO_C26_JU2_2, PO_C26_JU2_3, PO_C26_JU2_3, PO_C26_JU2_3,
	PO_C26_JD0, PO_C26_JD0, PO_C26_JD0, PO_C26_JD0, PO_C26_JD0, PO_C26_JD0_1, PO_C26_JD0_1, PO_C26_JD0_1,
	PO_C26_JD0_1, PO_C26_JD0_1, PO_C26_JD0_2, PO_C26_JD0_2, PO_C26_JD0_2, PO_C26_JD0_2, PO_C26_JD0_2, PO_C26_JD0_3,
	PO_C26_JD0_3, PO_C26_JD0_3, PO_C26_JD0_3, PO_C26_JD0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X,
	3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X,
	3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X,
	3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X,
	3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, -12 * _2X, -12 * _2X, -12 * _2X, -12 * _2X,
	-12 * _2X, -12 * _2X, -12 * _2X, -12 * _2X, -12 * _2X, -12 * _2X, -12 * _2X, -12 * _2X,
	-11 * _2X, -11 * _2X, -11 * _2X, -11 * _2X, -9 * _2X, -9 * _2X, -9 * _2X, -9 * _2X,
	-7 * _2X, -7 * _2X, -7 * _2X, -7 * _2X, -9, -9, -9, -9,
	-2 * _2X, -2 * _2X, -2 * _2X, -2 * _2X,	//상태 프레임별 이동폭 Y

	//GOLEM_SPEEDATTACK
	40,	//상태 프레임 카운트
	SET_DIR_PLAYER,	//초기화 조건
	PO_C26_A0, PO_C26_A0_1, PO_C26_A0_2, PO_C26_A0_3, PO_C26_A1, PO_C26_A1, PO_C26_A1, PO_C26_A1_1,
	PO_C26_A1_1, PO_C26_A1_1, PO_C26_A1_2, PO_C26_A1_2, PO_C26_A1_2, PO_C26_A1_3, PO_C26_A1_3, PO_C26_A1_3,
	PO_C26_A2, PO_C26_A2_1, PO_C26_A2_2, PO_C26_A2_3, PO_C26_A3, PO_C26_A3_1, PO_C26_A3_2, PO_C26_A3_3,
	PO_C26_A4, PO_C26_A4, PO_C26_A4, PO_C26_A4_N0_1, PO_C26_A4_N0_1, PO_C26_A4_N0_1, PO_C26_A4_N0_2, PO_C26_A4_N0_2,
	PO_C26_A4_N0_2, PO_C26_A4_N0_3, PO_C26_A4_N0_3, PO_C26_A4_N0_3, PO_C26_N0, PO_C26_N0_A0_1, PO_C26_N0_A0_2, PO_C26_N0_A0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	12 * _2X, 12 * _2X, 12 * _2X, 12 * _2X, 6 * _2X, 6 * _2X, 6 * _2X, 6 * _2X,
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GOLEM_OPEN
	20,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C26_OPEN0, PO_C26_OPEN0, PO_C26_OPEN0, PO_C26_OPEN0, PO_C26_OPEN0_1, PO_C26_OPEN0_1, PO_C26_OPEN0_1, PO_C26_OPEN0_1,
	PO_C26_OPEN0_2, PO_C26_OPEN0_2, PO_C26_OPEN0_2, PO_C26_OPEN0_2, PO_C26_OPEN0_3, PO_C26_OPEN0_3, PO_C26_OPEN0_3, PO_C26_OPEN0_3,
	PO_C26_OPEN1, PO_C26_OPEN1_1, PO_C26_OPEN1_2, PO_C26_OPEN1_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GOLEM_OPENED
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C26_OPEN1, PO_C26_OPEN1, PO_C26_OPEN1, PO_C26_OPEN1, PO_C26_OPEN1, PO_C26_OPEN1, PO_C26_OPEN1_1, PO_C26_OPEN1_1,
	PO_C26_OPEN1_1, PO_C26_OPEN1_1, PO_C26_OPEN1_1, PO_C26_OPEN1_1, PO_C26_OPEN1_2, PO_C26_OPEN1_2, PO_C26_OPEN1_2, PO_C26_OPEN1_2,
	PO_C26_OPEN1_2, PO_C26_OPEN1_2, PO_C26_OPEN1_3, PO_C26_OPEN1_3, PO_C26_OPEN1_3, PO_C26_OPEN1_3, PO_C26_OPEN1_3, PO_C26_OPEN1_3,
	PO_C26_OPEN0, PO_C26_OPEN0, PO_C26_OPEN0_1, PO_C26_OPEN0_1, PO_C26_OPEN0_2, PO_C26_OPEN0_2, PO_C26_OPEN0_3, PO_C26_OPEN0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GOLEM_BACKSTEP
	40,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C26_W2, PO_C26_W2_1, PO_C26_W2_2, PO_C26_W2_3, PO_C26_W3, PO_C26_W3_1, PO_C26_W3_2, PO_C26_W3_3,
	PO_C26_W4, PO_C26_W4_1, PO_C26_W4_2, PO_C26_W4_3, PO_C26_W5, PO_C26_W5, PO_C26_W5, PO_C26_W5_1,
	PO_C26_W5_1, PO_C26_W5_1, PO_C26_W5_2, PO_C26_W5_2, PO_C26_W5_2, PO_C26_W5_3, PO_C26_W5_3, PO_C26_W5_3,
	PO_C26_W0, PO_C26_W0_1, PO_C26_W0_2, PO_C26_W0_3, PO_C26_W1, PO_C26_W1_1, PO_C26_W1_2, PO_C26_W1_3,
	PO_C26_W2, PO_C26_W2, PO_C26_W2, PO_C26_W2, PO_C26_W2, PO_C26_W2, PO_C26_W2, PO_C26_W2,	//상태 프레임별 모션
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GOLEM_DIEREADY
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C26_OPEN1, PO_C26_OPEN1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GOLEM_DIEMOTION
	6,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C26_DIE0, PO_C26_DIE0_2, PO_C26_DIE1, PO_C26_DIE1_2, PO_C26_DIE2, PO_C26_DIE2_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GOLEM_DIE
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C26_DIE2, PO_C26_DIE2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	GOLEM_STOP,	GOLEM_NEUTRAL,	0,	0,	0,	0,
	GOLEM_NEUTRAL,	GOLEM_GUARD,	ATTACK_CHECK,	0,	RANDOM,	30,
	GOLEM_NEUTRAL,	GOLEM_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 3,	0,	0,
	GOLEM_NEUTRAL,	GOLEM_MOVE_FAST,	DISTANCE_CHECK_XY,	8 * 8 + 4,	0,	0,
	GOLEM_NEUTRAL,	GOLEM_MOVE,	COMPARE_FRAME,	16,	0,	0,
	GOLEM_MOVE,	GOLEM_GUARD,	ATTACK_CHECK,	0,	RANDOM,	30,
	GOLEM_MOVE,	GOLEM_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 3,	0,	0,
	GOLEM_MOVE,	GOLEM_MOVE_FAST,	DISTANCE_CHECK_XY,	8 * 8 + 4,	0,	0,
	GOLEM_MOVE,	GOLEM_NEUTRAL,	COMPARE_FRAME,	20,	RANDOM,	33,
	GOLEM_MOVE_FAST,	GOLEM_GUARD,	ATTACK_CHECK,	0,	RANDOM,	30,
	GOLEM_MOVE_FAST,	GOLEM_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 3,	0,	0,
	GOLEM_MOVE_FAST,	GOLEM_MOVE,	DISTANCE_OUT_XY,	12 * 8 + 4,	0,	0,
	GOLEM_ATTACK,	GOLEM_GUARD,	ATTACK_CHECK,	0,	RANDOM,	30,
	GOLEM_ATTACK,	GOLEM_MOVE_FAST,	DISTANCE_OUT_XY,	4 * 8 + 3,	0,	0,
	GOLEM_GUARD,	GOLEM_COUNTER,	COMPARE_FRAME,	10,	DISTANCE_CHECK_XY,	4 * 8 + 3,
	GOLEM_GUARD,	GOLEM_MOVE_FAST,	COMPARE_FRAME,	11,	0,	0,
	GOLEM_COUNTER,	GOLEM_MOVE_FAST,	0,	0,	0,	0,
	-1,
};

const signed short c27mv[] = {
	//상태 데이터
	//SPIDER_DOWN_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C27_D_N0, PO_C27_D_N0_1, PO_C27_D_N0_2, PO_C27_D_N0_3, PO_C27_D_N1, PO_C27_D_N1_1, PO_C27_D_N1_2, PO_C27_D_N1_3,
	PO_C27_D_N2, PO_C27_D_N2_1, PO_C27_D_N2_2, PO_C27_D_N2_3, PO_C27_D_N3, PO_C27_D_N3_1, PO_C27_D_N3_2, PO_C27_D_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SPIDER_DOWN_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C27_D_W0, PO_C27_D_W0_1, PO_C27_D_W0_2, PO_C27_D_W0_3, PO_C27_D_W1, PO_C27_D_W1_1, PO_C27_D_W1_2, PO_C27_D_W1_3,
	PO_C27_D_W2, PO_C27_D_W2_1, PO_C27_D_W2_2, PO_C27_D_W2_3, PO_C27_D_W3, PO_C27_D_W3_1, PO_C27_D_W3_2, PO_C27_D_W3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SPIDER_DOWN_LASER
	120,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C27_D_LAY0, PO_C27_D_LAY0_2, PO_C27_D_LAY1, PO_C27_D_LAY1, PO_C27_D_LAY1, PO_C27_D_LAY1, PO_C27_D_LAY1, PO_C27_D_LAY1_1,
	PO_C27_D_LAY1_1, PO_C27_D_LAY1_1, PO_C27_D_LAY1_1, PO_C27_D_LAY1_1, PO_C27_D_LAY1_2, PO_C27_D_LAY1_2, PO_C27_D_LAY1_2, PO_C27_D_LAY1_2,
	PO_C27_D_LAY1_2, PO_C27_D_LAY1_3, PO_C27_D_LAY1_3, PO_C27_D_LAY1_3, PO_C27_D_LAY1_3, PO_C27_D_LAY1_3, PO_C27_D_LAY3, PO_C27_D_LAY3_1,
	PO_C27_D_LAY3_2, PO_C27_D_LAY3_3, PO_C27_D_LAY2, PO_C27_D_LAY2, PO_C27_D_LAY2, PO_C27_D_LAY2, PO_C27_D_LAY2, PO_C27_D_LAY2,
	PO_C27_D_LAY2, PO_C27_D_LAY2, PO_C27_D_LAY2, PO_C27_D_LAY2, PO_C27_D_LAY2, PO_C27_D_LAY2, PO_C27_D_LAY2, PO_C27_D_LAY2,
	PO_C27_D_LAY2, PO_C27_D_LAY2, PO_C27_D_LAY2, PO_C27_D_LAY2, PO_C27_D_LAY2, PO_C27_D_LAY2, PO_C27_D_LAY2, PO_C27_D_LAY2,
	PO_C27_D_LAY2, PO_C27_D_LAY2_1, PO_C27_D_LAY2_1, PO_C27_D_LAY2_1, PO_C27_D_LAY2_1, PO_C27_D_LAY2_1, PO_C27_D_LAY2_1, PO_C27_D_LAY2_1,
	PO_C27_D_LAY2_1, PO_C27_D_LAY2_1, PO_C27_D_LAY2_1, PO_C27_D_LAY2_1, PO_C27_D_LAY2_1, PO_C27_D_LAY2_1, PO_C27_D_LAY2_1, PO_C27_D_LAY2_1,
	PO_C27_D_LAY2_1, PO_C27_D_LAY2_1, PO_C27_D_LAY2_1, PO_C27_D_LAY2_1, PO_C27_D_LAY2_1, PO_C27_D_LAY2_1, PO_C27_D_LAY2_1, PO_C27_D_LAY2_2,
	PO_C27_D_LAY2_2, PO_C27_D_LAY2_2, PO_C27_D_LAY2_2, PO_C27_D_LAY2_2, PO_C27_D_LAY2_2, PO_C27_D_LAY2_2, PO_C27_D_LAY2_2, PO_C27_D_LAY2_2,
	PO_C27_D_LAY2_2, PO_C27_D_LAY2_2, PO_C27_D_LAY2_2, PO_C27_D_LAY2_2, PO_C27_D_LAY2_2, PO_C27_D_LAY2_2, PO_C27_D_LAY2_2, PO_C27_D_LAY2_2,
	PO_C27_D_LAY2_2, PO_C27_D_LAY2_2, PO_C27_D_LAY2_2, PO_C27_D_LAY2_2, PO_C27_D_LAY2_2, PO_C27_D_LAY2_2, PO_C27_D_LAY2_3, PO_C27_D_LAY2_3,
	PO_C27_D_LAY2_3, PO_C27_D_LAY2_3, PO_C27_D_LAY2_3, PO_C27_D_LAY2_3, PO_C27_D_LAY2_3, PO_C27_D_LAY2_3, PO_C27_D_LAY2_3, PO_C27_D_LAY2_3,
	PO_C27_D_LAY2_3, PO_C27_D_LAY2_3, PO_C27_D_LAY2_3, PO_C27_D_LAY2_3, PO_C27_D_LAY2_3, PO_C27_D_LAY2_3, PO_C27_D_LAY2_3, PO_C27_D_LAY2_3,
	PO_C27_D_LAY2_3, PO_C27_D_LAY2_3, PO_C27_D_LAY2_3, PO_C27_D_LAY2_3, PO_C27_D_LAY3, PO_C27_D_LAY3, PO_C27_D_LAY3, PO_C27_D_LAY3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SPIDER_GUARD
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C27_D_GUARD0, PO_C27_D_GUARD0_1, PO_C27_D_GUARD0_2, PO_C27_D_GUARD0_3, PO_C27_D_GUARD1, PO_C27_D_GUARD1, PO_C27_D_GUARD1, PO_C27_D_GUARD1_1,
	PO_C27_D_GUARD1_1, PO_C27_D_GUARD1_1, PO_C27_D_GUARD1_2, PO_C27_D_GUARD1_2, PO_C27_D_GUARD1_2, PO_C27_D_GUARD1_3, PO_C27_D_GUARD1_3, PO_C27_D_GUARD1_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SPIDER_JUMP
	12,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C27_D_JUMP0, PO_C27_D_JUMP0_1, PO_C27_D_JUMP0_2, PO_C27_D_JUMP0_3, PO_C27_D_JUMP1, PO_C27_D_JUMP1, PO_C27_D_JUMP1_1, PO_C27_D_JUMP1_2,
	PO_C27_D_JUMP1_2, PO_C27_D_JUMP1_3, PO_C27_D_JUMP2, PO_C27_D_JUMP2_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	102 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SPIDER_DOWN_LANDING
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C27_D_N0, PO_C27_D_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SPIDER_DOWN_LAND
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C27_D_LAND0, PO_C27_D_LAND0_2, PO_C27_D_LAND1, PO_C27_D_LAND1_2, PO_C27_D_JUMP1, PO_C27_D_JUMP1, PO_C27_D_JUMP1, PO_C27_D_JUMP1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SPIDER_UP_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C27_U_N0, PO_C27_U_N0_1, PO_C27_U_N0_2, PO_C27_U_N0_3, PO_C27_U_N1, PO_C27_U_N1_1, PO_C27_U_N1_2, PO_C27_U_N1_3,
	PO_C27_U_N2, PO_C27_U_N2_1, PO_C27_U_N2_2, PO_C27_U_N2_3, PO_C27_U_N3, PO_C27_U_N3_1, PO_C27_U_N3_2, PO_C27_U_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SPIDER_UP_MOVE
	116,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C27_U_LAY0, PO_C27_U_LAY0_2, PO_C27_U_LAY1, PO_C27_U_LAY1, PO_C27_U_LAY1, PO_C27_U_LAY1, PO_C27_U_LAY1, PO_C27_U_LAY1_1,
	PO_C27_U_LAY1_1, PO_C27_U_LAY1_1, PO_C27_U_LAY1_1, PO_C27_U_LAY1_1, PO_C27_U_LAY1_2, PO_C27_U_LAY1_2, PO_C27_U_LAY1_2, PO_C27_U_LAY1_2,
	PO_C27_U_LAY1_2, PO_C27_U_LAY1_3, PO_C27_U_LAY1_3, PO_C27_U_LAY1_3, PO_C27_U_LAY1_3, PO_C27_U_LAY1_3, PO_C27_U_LAY3, PO_C27_U_LAY3_2,
	PO_C27_U_LAY2, PO_C27_U_LAY2, PO_C27_U_LAY2, PO_C27_U_LAY2, PO_C27_U_LAY2, PO_C27_U_LAY2, PO_C27_U_LAY2, PO_C27_U_LAY2,
	PO_C27_U_LAY2, PO_C27_U_LAY2, PO_C27_U_LAY2, PO_C27_U_LAY2, PO_C27_U_LAY2, PO_C27_U_LAY2, PO_C27_U_LAY2, PO_C27_U_LAY2,
	PO_C27_U_LAY2, PO_C27_U_LAY2, PO_C27_U_LAY2, PO_C27_U_LAY2, PO_C27_U_LAY2, PO_C27_U_LAY2, PO_C27_U_LAY2, PO_C27_U_LAY2_1,
	PO_C27_U_LAY2_1, PO_C27_U_LAY2_1, PO_C27_U_LAY2_1, PO_C27_U_LAY2_1, PO_C27_U_LAY2_1, PO_C27_U_LAY2_1, PO_C27_U_LAY2_1, PO_C27_U_LAY2_1,
	PO_C27_U_LAY2_1, PO_C27_U_LAY2_1, PO_C27_U_LAY2_1, PO_C27_U_LAY2_1, PO_C27_U_LAY2_1, PO_C27_U_LAY2_1, PO_C27_U_LAY2_1, PO_C27_U_LAY2_1,
	PO_C27_U_LAY2_1, PO_C27_U_LAY2_1, PO_C27_U_LAY2_1, PO_C27_U_LAY2_1, PO_C27_U_LAY2_1, PO_C27_U_LAY2_2, PO_C27_U_LAY2_2, PO_C27_U_LAY2_2,
	PO_C27_U_LAY2_2, PO_C27_U_LAY2_2, PO_C27_U_LAY2_2, PO_C27_U_LAY2_2, PO_C27_U_LAY2_2, PO_C27_U_LAY2_2, PO_C27_U_LAY2_2, PO_C27_U_LAY2_2,
	PO_C27_U_LAY2_2, PO_C27_U_LAY2_2, PO_C27_U_LAY2_2, PO_C27_U_LAY2_2, PO_C27_U_LAY2_2, PO_C27_U_LAY2_2, PO_C27_U_LAY2_2, PO_C27_U_LAY2_2,
	PO_C27_U_LAY2_2, PO_C27_U_LAY2_2, PO_C27_U_LAY2_2, PO_C27_U_LAY2_2, PO_C27_U_LAY2_3, PO_C27_U_LAY2_3, PO_C27_U_LAY2_3, PO_C27_U_LAY2_3,
	PO_C27_U_LAY2_3, PO_C27_U_LAY2_3, PO_C27_U_LAY2_3, PO_C27_U_LAY2_3, PO_C27_U_LAY2_3, PO_C27_U_LAY2_3, PO_C27_U_LAY2_3, PO_C27_U_LAY2_3,
	PO_C27_U_LAY2_3, PO_C27_U_LAY2_3, PO_C27_U_LAY2_3, PO_C27_U_LAY2_3, PO_C27_U_LAY2_3, PO_C27_U_LAY2_3, PO_C27_U_LAY2_3, PO_C27_U_LAY2_3,
	PO_C27_U_LAY2_3, PO_C27_U_LAY2_3, PO_C27_U_LAY3, PO_C27_U_LAY3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SPIDER_UP_LASER
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C27_U_LAND0, PO_C27_U_LAND0_2, PO_C27_U_LAND1, PO_C27_U_LAND1_2, PO_C27_U_JUMP1, PO_C27_U_JUMP1, PO_C27_U_JUMP1, PO_C27_U_JUMP1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SPIDER_UP_LAND
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C27_D_JUMP2, PO_C27_D_JUMP2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SPIDER_UP_LANDING
	12,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C27_U_JUMP0, PO_C27_U_JUMP0_1, PO_C27_U_JUMP0_2, PO_C27_U_JUMP0_3, PO_C27_U_JUMP1, PO_C27_U_JUMP1, PO_C27_U_JUMP1_1, PO_C27_U_JUMP1_2,
	PO_C27_U_JUMP1_2, PO_C27_U_JUMP1_3, PO_C27_U_JUMP2, PO_C27_U_JUMP2_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SPIDER_DOWN
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C27_D_N2, PO_C27_D_N2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	SPIDER_DOWN_NEUTRAL,	SPIDER_DOWN_LASER,	DISTANCE_CHECK_XY,	10 * 8 + 3,	RANDOM,	50,
	SPIDER_DOWN_NEUTRAL,	SPIDER_JUMP,	DISTANCE_CHECK_XY,	6 * 8 + 3,	RANDOM,	20,
	SPIDER_DOWN_NEUTRAL,	SPIDER_GUARD,	ATTACK_CHECK,	0,	RANDOM,	40,
	SPIDER_DOWN_NEUTRAL,	SPIDER_DOWN_MOVE,	COMPARE_FRAME,	10,	RANDOM,	25,
	SPIDER_DOWN_MOVE,	SPIDER_DOWN_LASER,	DISTANCE_CHECK_XY,	10 * 8 + 3,	RANDOM,	50,
	SPIDER_DOWN_MOVE,	SPIDER_JUMP,	DISTANCE_CHECK_XY,	6 * 8 + 3,	RANDOM,	20,
	SPIDER_DOWN_MOVE,	SPIDER_DOWN_NEUTRAL,	COMPARE_FRAME,	10,	RANDOM,	25,
	SPIDER_GUARD,	SPIDER_JUMP,	DISTANCE_CHECK_XY,	6 * 8 + 3,	RANDOM,	30,
	SPIDER_GUARD,	SPIDER_DOWN_LASER,	DISTANCE_CHECK_XY,	10 * 8 + 3,	RANDOM,	50,
	SPIDER_GUARD,	SPIDER_DOWN_NEUTRAL,	COMPARE_FRAME,	10,	RANDOM,	25,
	SPIDER_DOWN_LASER,	SPIDER_DOWN_NEUTRAL,	0,	0,	0,	0,
	SPIDER_UP_LAND,	SPIDER_UP_NEUTRAL,	0,	0,	0,	0,
	SPIDER_UP_NEUTRAL,	SPIDER_UP_LASER,	DISTANCE_CHECK_XY,	10 * 8 + 5,	RANDOM,	50,
	SPIDER_UP_NEUTRAL,	SPIDER_DOWN,	0,	0,	RANDOM,	20,
	SPIDER_UP_NEUTRAL,	SPIDER_UP_LASER,	DISTANCE_CHECK_XY,	10 * 8 + 5,	RANDOM,	50,
	SPIDER_UP_NEUTRAL,	SPIDER_DOWN,	0,	0,	RANDOM,	20,
	SPIDER_UP_LASER,	SPIDER_UP_NEUTRAL,	0,	0,	0,	0,
	SPIDER_DOWN_LAND,	SPIDER_DOWN_NEUTRAL,	0,	0,	0,	0,
	SPIDER_ANCHOR_CHANGE,	SPIDER_DOWN_LANDING,	0,	0,	0,	0,
	-1,
};

const signed short c28mv[] = {
	//상태 데이터
	//SHIP_NEUTRAL
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C28_N0, PO_C28_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SHIP_MOVE
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C28_N0, PO_C28_N0,	//상태 프레임별 모션
	1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};


//PUMPKIN
const signed short c29mv[] = {
	//상태 데이터
	//PUMPKIN_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C29_N0, PO_C29_N0_1, PO_C29_N0_2, PO_C29_N0_3, PO_C29_N1, PO_C29_N1_1, PO_C29_N1_2, PO_C29_N1_3,
	PO_C29_N2, PO_C29_N2_1, PO_C29_N2_2, PO_C29_N2_3, PO_C29_N3, PO_C29_N3_1, PO_C29_N3_2, PO_C29_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//PUMPKIN_MOVE
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C29_W0, PO_C29_W0_1, PO_C29_W0_2, PO_C29_W0_3, PO_C29_W1, PO_C29_W1, PO_C29_W1_1, PO_C29_W1_1,
	PO_C29_W1_2, PO_C29_W1_2, PO_C29_W1_3, PO_C29_W1_3, PO_C29_W2, PO_C29_W2_1, PO_C29_W2_2, PO_C29_W2_3,
	PO_C29_W3, PO_C29_W3, PO_C29_W3_1, PO_C29_W3_1, PO_C29_W3_2, PO_C29_W3_2, PO_C29_W3_3, PO_C29_W3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 1, 1, 1, 1,
	1, 1, 1, 1, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//PUMPKIN_MOVE_FAST
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C29_W0, PO_C29_W0_1, PO_C29_W0_2, PO_C29_W0_3, PO_C29_W1, PO_C29_W1_1, PO_C29_W1_2, PO_C29_W1_3,
	PO_C29_W2, PO_C29_W2_1, PO_C29_W2_2, PO_C29_W2_3, PO_C29_W3, PO_C29_W3_1, PO_C29_W3_2, PO_C29_W3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//PUMPKIN_RUSH
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C29_R0, PO_C29_R0_1, PO_C29_R0_2, PO_C29_R0_3, PO_C29_R1, PO_C29_R1, PO_C29_R1_1, PO_C29_R1_1,
	PO_C29_R1_2, PO_C29_R1_2, PO_C29_R1_3, PO_C29_R1_3, PO_C29_R2, PO_C29_R2_1, PO_C29_R2_2, PO_C29_R2_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//PUMPKIN_RUSHATTACK
	46,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C29_A0, PO_C29_A0_1, PO_C29_A0_2, PO_C29_A0_3, PO_C29_A1, PO_C29_A1_1, PO_C29_A1_2, PO_C29_A1_3,
	PO_C29_A2, PO_C29_A2_1, PO_C29_A2_2, PO_C29_A2_3, PO_C29_A3, PO_C29_A3_1, PO_C29_A3_2, PO_C29_A3_3,
	PO_C29_A4, PO_C29_A4_1, PO_C29_A4_2, PO_C29_A4_3, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5,
	PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5,
	PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5,
	PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//PUMPKIN_ATTACK
	46,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C29_A0, PO_C29_A0_1, PO_C29_A0_2, PO_C29_A0_3, PO_C29_A1, PO_C29_A1_1, PO_C29_A1_2, PO_C29_A1_3,
	PO_C29_A2, PO_C29_A2_1, PO_C29_A2_2, PO_C29_A2_3, PO_C29_A3, PO_C29_A3_1, PO_C29_A3_2, PO_C29_A3_3,
	PO_C29_A4, PO_C29_A4_1, PO_C29_A4_2, PO_C29_A4_3, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5,
	PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5,
	PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5,
	PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5, PO_C29_A5,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3, 3, 0 * _2X, 0 * _2X, 1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X,
	1, 1, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	PUMPKIN_NEUTRAL,	PUMPKIN_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 4,	0,	0,
	PUMPKIN_NEUTRAL,	PUMPKIN_RUSH,	DISTANCE_CHECK_XY,	8 * 8 + 4,	0,	0,
	PUMPKIN_NEUTRAL,	PUMPKIN_MOVE,	COMPARE_FRAME,	20,	RANDOM,	30,
	PUMPKIN_MOVE,	PUMPKIN_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 4,	0,	0,
	PUMPKIN_MOVE,	PUMPKIN_RUSH,	DISTANCE_CHECK_XY,	8 * 8 + 4,	0,	0,
	PUMPKIN_MOVE,	PUMPKIN_NEUTRAL,	COMPARE_FRAME,	20,	RANDOM,	30,
	PUMPKIN_MOVE_FAST,	PUMPKIN_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 4,	0,	0,
	PUMPKIN_MOVE_FAST,	PUMPKIN_RUSH,	DISTANCE_CHECK_XY,	8 * 8 + 4,	0,	0,
	PUMPKIN_MOVE_FAST,	PUMPKIN_NEUTRAL,	DISTANCE_OUT_XY,	8 * 8 + 4,	0,	0,
	PUMPKIN_RUSH,	PUMPKIN_RUSHATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 4,	0,	0,
	PUMPKIN_RUSHATTACK,	PUMPKIN_NEUTRAL,	0,	0,	0,	0,
	PUMPKIN_ATTACK,	PUMPKIN_MOVE_FAST,	DISTANCE_CHECK_XY,	4 * 8 + 4,	0,	0,
	PUMPKIN_ATTACK,	PUMPKIN_NEUTRAL,	0,	0,	0,	0,
	-1,
};

const signed short c30mv[] = {
	//상태 데이터
	//GHOST_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C30_N0, PO_C30_N0_1, PO_C30_N0_2, PO_C30_N0_3, PO_C30_N1, PO_C30_N1_1, PO_C30_N1_2, PO_C30_N1_3,
	PO_C30_N2, PO_C30_N2_1, PO_C30_N2_2, PO_C30_N2_3, PO_C30_N3, PO_C30_N3_1, PO_C30_N3_2, PO_C30_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GHOST_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C30_N0, PO_C30_N0_1, PO_C30_N0_2, PO_C30_N0_3, PO_C30_N1, PO_C30_N1_1, PO_C30_N1_2, PO_C30_N1_3,
	PO_C30_N2, PO_C30_N2_1, PO_C30_N2_2, PO_C30_N2_3, PO_C30_N3, PO_C30_N3_1, PO_C30_N3_2, PO_C30_N3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GHOST_PLAYER_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C30_N0, PO_C30_N0_1, PO_C30_N0_2, PO_C30_N0_3, PO_C30_N1, PO_C30_N1_1, PO_C30_N1_2, PO_C30_N1_3,
	PO_C30_N2, PO_C30_N2_1, PO_C30_N2_2, PO_C30_N2_3, PO_C30_N3, PO_C30_N3_1, PO_C30_N3_2, PO_C30_N3_3,	//상태 프레임별 모션
	101, 0 * _2X, 101, 0 * _2X, 101, 0 * _2X, 101, 0 * _2X,
	101, 0 * _2X, 101, 0 * _2X, 101, 0 * _2X, 101, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GHOST_INVISIBLE
	20,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C30_D0, PO_C30_D0_1, PO_C30_D0_2, PO_C30_D0_3, PO_C30_D1, PO_C30_D1_1, PO_C30_D1_2, PO_C30_D1_3,
	PO_C30_D2, PO_C30_D2_1, PO_C30_D2_2, PO_C30_D2_3, PO_C30_D3, PO_C30_D3_1, PO_C30_D3_2, PO_C30_D3_3,
	PO_C30_D4, PO_C30_D4, PO_C30_D4, PO_C30_D4,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GHOST_INVISIBLED
	20,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C30_T0, PO_C30_T0_1, PO_C30_T0_2, PO_C30_T0_3, PO_C30_T1, PO_C30_T1_1, PO_C30_T1_2, PO_C30_T1_3,
	PO_C30_T2, PO_C30_T2_1, PO_C30_T2_2, PO_C30_T2_3, PO_C30_T3, PO_C30_T3_1, PO_C30_T3_2, PO_C30_T3_3,
	PO_C30_T4, PO_C30_T4_1, PO_C30_T4_2, PO_C30_T4_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GHOST_INVISI_MOVE
	20,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C30_T0, PO_C30_T0_1, PO_C30_T0_2, PO_C30_T0_3, PO_C30_T1, PO_C30_T1_1, PO_C30_T1_2, PO_C30_T1_3,
	PO_C30_T2, PO_C30_T2_1, PO_C30_T2_2, PO_C30_T2_3, PO_C30_T3, PO_C30_T3_1, PO_C30_T3_2, PO_C30_T3_3,
	PO_C30_T4, PO_C30_T4_1, PO_C30_T4_2, PO_C30_T4_3,	//상태 프레임별 모션
	101, 0 * _2X, 101, 0 * _2X, 101, 0 * _2X, 101, 0 * _2X,
	101, 0 * _2X, 101, 0 * _2X, 101, 0 * _2X, 101, 0 * _2X,
	101, 0 * _2X, 101, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GHOST_ATTACK
	56,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C30_A0, PO_C30_A0_2, PO_C30_A1, PO_C30_A1, PO_C30_A1, PO_C30_A1, PO_C30_A1, PO_C30_A1,
	PO_C30_A1_1, PO_C30_A1_1, PO_C30_A1_1, PO_C30_A1_1, PO_C30_A1_1, PO_C30_A1_2, PO_C30_A1_2, PO_C30_A1_2,
	PO_C30_A1_2, PO_C30_A1_2, PO_C30_A1_2, PO_C30_A1_3, PO_C30_A1_3, PO_C30_A1_3, PO_C30_A1_3, PO_C30_A1_3,
	PO_C30_A2, PO_C30_A2_2, PO_C30_A3, PO_C30_A3_2, PO_C30_A4, PO_C30_A4_2, PO_C30_A5, PO_C30_A5,
	PO_C30_A5, PO_C30_A5, PO_C30_A5, PO_C30_A5, PO_C30_A5, PO_C30_A5, PO_C30_A5, PO_C30_A5,
	PO_C30_A5, PO_C30_A5, PO_C30_A5, PO_C30_A5, PO_C30_A5, PO_C30_A5, PO_C30_A5, PO_C30_A5,
	PO_C30_A5, PO_C30_A5, PO_C30_A5, PO_C30_A5, PO_C30_A5, PO_C30_A5, PO_C30_A5, PO_C30_A5,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	53 * _2X, 0 * _2X, 103, 0 * _2X, 51 * _2X, 0 * _2X, 101, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	GHOST_NEUTRAL,	GHOST_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 3,	RANDOM,	60,
	GHOST_NEUTRAL,	GHOST_INVISIBLE,	DISTANCE_CHECK_XY,	8 * 8 + 7,	RANDOM,	20,
	GHOST_NEUTRAL,	GHOST_PLAYER_MOVE,	DISTANCE_CHECK_XY,	8 * 8 + 7,	0,	0,
	GHOST_NEUTRAL,	GHOST_MOVE,	0,	0,	RANDOM,	40,
	GHOST_MOVE,	GHOST_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 3,	RANDOM,	60,
	GHOST_MOVE,	GHOST_INVISIBLE,	DISTANCE_CHECK_XY,	8 * 8 + 7,	RANDOM,	20,
	GHOST_MOVE,	GHOST_PLAYER_MOVE,	DISTANCE_CHECK_XY,	8 * 8 + 7,	0,	0,
	GHOST_MOVE,	GHOST_NEUTRAL,	0,	0,	RANDOM,	20,
	GHOST_PLAYER_MOVE,	GHOST_INVISIBLE,	ATTACK_CHECK,	0,	RANDOM,	40,
	GHOST_PLAYER_MOVE,	GHOST_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 3,	RANDOM,	65,
	GHOST_PLAYER_MOVE,	GHOST_NEUTRAL,	DISTANCE_OUT_XY,	8 * 8 + 7,	0,	0,
	GHOST_INVISIBLE,	GHOST_INVISIBLED,	0,	0,	0,	0,
	GHOST_INVISIBLED,	GHOST_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 3,	RANDOM,	20,
	GHOST_INVISIBLED,	GHOST_INVISI_MOVE,	DISTANCE_CHECK_XY,	8 * 8 + 7,	0,	0,
	GHOST_INVISIBLED,	GHOST_NEUTRAL,	DISTANCE_OUT_XY,	8 * 8 + 7,	0,	0,
	GHOST_INVISI_MOVE,	GHOST_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 3,	RANDOM,	20,
	GHOST_INVISI_MOVE,	GHOST_NEUTRAL,	DISTANCE_OUT_XY,	8 * 8 + 7,	0,	0,
	GHOST_ATTACK,	GHOST_NEUTRAL,	0,	0,	0,	0,
	-1,
};

const signed short c31mv[] = {
	//상태 데이터
	//DEATH_NEUTRAL
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C31_N0, PO_C31_N0, PO_C31_N0_1, PO_C31_N0_2, PO_C31_N0_2, PO_C31_N0_3, PO_C31_N1, PO_C31_N1,
	PO_C31_N1_1, PO_C31_N1_2, PO_C31_N1_2, PO_C31_N1_3, PO_C31_N2, PO_C31_N2, PO_C31_N2_1, PO_C31_N2_2,
	PO_C31_N2_2, PO_C31_N2_3, PO_C31_N3, PO_C31_N3, PO_C31_N3, PO_C31_N3, PO_C31_N3, PO_C31_N3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DEATH_ATTACK
	72,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C31_A0, PO_C31_A0_2, PO_C31_A1, PO_C31_A1_2, PO_C31_A2, PO_C31_A2_2, PO_C31_A3, PO_C31_A3_A2_2,
	PO_C31_A2, PO_C31_A2_2, PO_C31_A3, PO_C31_A3_A2_2, PO_C31_A2, PO_C31_A2_2, PO_C31_A3, PO_C31_A3_A2_2,
	PO_C31_A2, PO_C31_A2_1, PO_C31_A2_2, PO_C31_A2_3, PO_C31_A3, PO_C31_A3_A2_2, PO_C31_A2, PO_C31_A2_2,
	PO_C31_A3, PO_C31_A3_A2_2, PO_C31_A2, PO_C31_A2_2, PO_C31_A3, PO_C31_A3_A2_2, PO_C31_A2, PO_C31_A2_2,
	PO_C31_A3, PO_C31_A3_A4_2, PO_C31_A4, PO_C31_A4_2, PO_C31_A5, PO_C31_A5_2, PO_C31_A6, PO_C31_A6_2,
	PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7,
	PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7,
	PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7,
	PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 9, 9, 5, 5, 1 * _2X, 3,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DEATH_SUMMONS
	36,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C31_SKEL0, PO_C31_SKEL0_SKEL1_2, PO_C31_SKEL1, PO_C31_SKEL1, PO_C31_SKEL1, PO_C31_SKEL1, PO_C31_SKEL1_1, PO_C31_SKEL1_1,
	PO_C31_SKEL1_1, PO_C31_SKEL1_2, PO_C31_SKEL1_2, PO_C31_SKEL1_2, PO_C31_SKEL1_2, PO_C31_SKEL1_3, PO_C31_SKEL1_3, PO_C31_SKEL1_3,
	PO_C31_SKEL2, PO_C31_SKEL2_SKEL3_2, PO_C31_SKEL3, PO_C31_SKEL3_SKEL4_2, PO_C31_SKEL4, PO_C31_SKEL4_SKEL5_2, PO_C31_SKEL5, PO_C31_SKEL5_SKEL6_2,
	PO_C31_SKEL6, PO_C31_SKEL6_SKEL3_2, PO_C31_SKEL3, PO_C31_SKEL3_SKEL4_2, PO_C31_SKEL4, PO_C31_SKEL4_SKEL5_2, PO_C31_SKEL5, PO_C31_SKEL5_SKEL6_2,
	PO_C31_SKEL6, PO_C31_SKEL6_SKEL11_2, PO_C31_SKEL11, PO_C31_SKEL11,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DEATH_FINISH
	44,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C31_SKEL6, PO_C31_SKEL6_SKEL5_2, PO_C31_SKEL5, PO_C31_SKEL5_SKEL4_2, PO_C31_SKEL4, PO_C31_SKEL4_SKEL3_2, PO_C31_SKEL3, PO_C31_SKEL3_SKEL6_2,
	PO_C31_SKEL6, PO_C31_SKEL6_SKEL5_2, PO_C31_SKEL5, PO_C31_SKEL5_SKEL4_2, PO_C31_SKEL4, PO_C31_SKEL4_SKEL3_2, PO_C31_SKEL3, PO_C31_SKEL3_SKEL2_2,
	PO_C31_SKEL2, PO_C31_SKEL2_SKEL0_2, PO_C31_SKEL0, PO_C31_SKEL0_N0_2, PO_C31_N0, PO_C31_N0, PO_C31_N0_1, PO_C31_N0_2,
	PO_C31_N0_2, PO_C31_N0_3, PO_C31_N1, PO_C31_N1, PO_C31_N1_1, PO_C31_N1_2, PO_C31_N1_2, PO_C31_N1_3,
	PO_C31_N2, PO_C31_N2, PO_C31_N2_1, PO_C31_N2_2, PO_C31_N2_2, PO_C31_N2_3, PO_C31_N3, PO_C31_N3,
	PO_C31_N3, PO_C31_N3, PO_C31_N3, PO_C31_N3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DEATH_SKELHEAD
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C31_SHOT0, PO_C31_SHOT0_2, PO_C31_SHOT1, PO_C31_SHOT1_2, PO_C31_SHOT2, PO_C31_SHOT2_2, PO_C31_SHOT3, PO_C31_SHOT3_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DEATH_BREAK_READY
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C31_BREAK0, PO_C31_BREAK0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DEATH_BREAK
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C31_BREAK0, PO_C31_BREAK0_2, PO_C31_BREAK1, PO_C31_BREAK1_2, PO_C31_BREAK2, PO_C31_BREAK2_2, PO_C31_BREAK3, PO_C31_BREAK3_2,
	PO_C31_BREAK0, PO_C31_BREAK0_2, PO_C31_BREAK1, PO_C31_BREAK1_2, PO_C31_BREAK2, PO_C31_BREAK2_2, PO_C31_BREAK3, PO_C31_BREAK3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DEATH_BROKEN
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C31_BROKEN0, PO_C31_BROKEN0_1, PO_C31_BROKEN0_2, PO_C31_BROKEN0_3, PO_C31_BROKEN1, PO_C31_BROKEN1_2, PO_C31_BROKEN2, PO_C31_BROKEN2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DEATH_BROKEN_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C31_N0, PO_C31_N0_1, PO_C31_N0_2, PO_C31_N0_3, PO_C31_N1, PO_C31_N1_1, PO_C31_N1_2, PO_C31_N1_3,
	PO_C31_N2, PO_C31_N2_1, PO_C31_N2_2, PO_C31_N2_3, PO_C31_N3, PO_C31_N3, PO_C31_N3, PO_C31_N3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DEATH_BROKEN_ATTACK
	56,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C31_A0, PO_C31_A0_2, PO_C31_A1, PO_C31_A1_2, PO_C31_A2, PO_C31_A2_2, PO_C31_A3, PO_C31_A3_A2_2,
	PO_C31_A2, PO_C31_A2_1, PO_C31_A2_2, PO_C31_A2_3, PO_C31_A3, PO_C31_A3_A2_2, PO_C31_A2, PO_C31_A2_2,
	PO_C31_A3, PO_C31_A3_A2_2, PO_C31_A2, PO_C31_A2_2, PO_C31_A3, PO_C31_A3_A2_2, PO_C31_A2, PO_C31_A2_2,
	PO_C31_A3, PO_C31_A3_A4_2, PO_C31_A4, PO_C31_A4_2, PO_C31_A5, PO_C31_A5_2, PO_C31_A6, PO_C31_A6_2,
	PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7,
	PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7,
	PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7, PO_C31_A7,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 2 * _2X, 2 * _2X, 1 * _2X, 1 * _2X, 1, 1,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DEATH_BROKEN_SUMMONS
	36,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C31_SKEL0, PO_C31_SKEL0_SKEL1_2, PO_C31_SKEL1, PO_C31_SKEL1, PO_C31_SKEL1, PO_C31_SKEL1, PO_C31_SKEL1_1, PO_C31_SKEL1_1,
	PO_C31_SKEL1_1, PO_C31_SKEL1_2, PO_C31_SKEL1_2, PO_C31_SKEL1_2, PO_C31_SKEL1_2, PO_C31_SKEL1_3, PO_C31_SKEL1_3, PO_C31_SKEL1_3,
	PO_C31_SKEL2, PO_C31_SKEL2_SKEL3_2, PO_C31_SKEL3, PO_C31_SKEL3_SKEL4_2, PO_C31_SKEL4, PO_C31_SKEL4_SKEL5_2, PO_C31_SKEL5, PO_C31_SKEL5_SKEL6_2,
	PO_C31_SKEL6, PO_C31_SKEL6_SKEL3_2, PO_C31_SKEL3, PO_C31_SKEL3_SKEL4_2, PO_C31_SKEL4, PO_C31_SKEL4_SKEL5_2, PO_C31_SKEL5, PO_C31_SKEL5_SKEL6_2,
	PO_C31_SKEL6, PO_C31_SKEL6_SKEL11_2, PO_C31_SKEL11, PO_C31_SKEL11,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DEATH_BROKEN_FINISH
	44,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C31_SKEL6, PO_C31_SKEL6_SKEL5_2, PO_C31_SKEL5, PO_C31_SKEL5_SKEL4_2, PO_C31_SKEL4, PO_C31_SKEL4_SKEL3_2, PO_C31_SKEL3, PO_C31_SKEL3_SKEL6_2,
	PO_C31_SKEL6, PO_C31_SKEL6_SKEL5_2, PO_C31_SKEL5, PO_C31_SKEL5_SKEL4_2, PO_C31_SKEL4, PO_C31_SKEL4_SKEL3_2, PO_C31_SKEL3, PO_C31_SKEL3_SKEL2_2,
	PO_C31_SKEL2, PO_C31_SKEL2_SKEL0_2, PO_C31_SKEL0, PO_C31_SKEL0_N0_2, PO_C31_N0, PO_C31_N0, PO_C31_N0_1, PO_C31_N0_2,
	PO_C31_N0_2, PO_C31_N0_3, PO_C31_N1, PO_C31_N1, PO_C31_N1_1, PO_C31_N1_2, PO_C31_N1_2, PO_C31_N1_3,
	PO_C31_N2, PO_C31_N2, PO_C31_N2_1, PO_C31_N2_2, PO_C31_N2_2, PO_C31_N2_3, PO_C31_N3, PO_C31_N3,
	PO_C31_N3, PO_C31_N3, PO_C31_N3, PO_C31_N3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	DEATH_NEUTRAL,	DEATH_ATTACK,	DISTANCE_CHECK_XY,	8 * 8 + 5,	RANDOM,	40,
	DEATH_NEUTRAL,	DEATH_SUMMONS,	0,	0,	0,	0,
	DEATH_ATTACK,	DEATH_NEUTRAL,	0,	0,	0,	0,
	DEATH_SUMMONS,	DEATH_FINISH,	0,	0,	0,	0,
	DEATH_FINISH,	DEATH_NEUTRAL,	0,	0,	0,	0,
	DEATH_BREAK_READY,	DEATH_BREAK,	0,	0,	0,	0,
	DEATH_BREAK,	DEATH_BROKEN,	0,	0,	0,	0,
	DEATH_BROKEN,	DEATH_BROKEN_NEUTRAL,	0,	0,	0,	0,
	DEATH_BROKEN_NEUTRAL,	DEATH_BROKEN_ATTACK,	DISTANCE_CHECK_XY,	8 * 8 + 5,	RANDOM,	40,
	DEATH_BROKEN_NEUTRAL,	DEATH_BROKEN_SUMMONS,	0,	0,	0,	0,
	DEATH_BROKEN_ATTACK,	DEATH_BROKEN_NEUTRAL,	0,	0,	0,	0,
	DEATH_BROKEN_SUMMONS,	DEATH_BROKEN_FINISH,	0,	0,	0,	0,
	DEATH_BROKEN_FINISH,	DEATH_BROKEN_NEUTRAL,	0,	0,	0,	0,
	-1,
};

const signed short c32mv[] = {
	//상태 데이터
	//KNIGHT_NEUTRAL
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C32_N0, PO_C32_N0_1, PO_C32_N0_2, PO_C32_N0_3, PO_C32_N1, PO_C32_N1_N2_1, PO_C32_N1_N2_2, PO_C32_N1_N2_3,
	PO_C32_N2, PO_C32_N2_1, PO_C32_N2_2, PO_C32_N2_3, PO_C32_N3, PO_C32_N3_1, PO_C32_N3_2, PO_C32_N3_3,
	PO_C32_N1, PO_C32_N1_N0_1, PO_C32_N1_N0_2, PO_C32_N1_N0_3, PO_C32_N0, PO_C32_N0, PO_C32_N0, PO_C32_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//KNIGHT_MOVE
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C32_W0, PO_C32_W0_1, PO_C32_W0_2, PO_C32_W0_3, PO_C32_W1, PO_C32_W1_1, PO_C32_W1_2, PO_C32_W1_3,
	PO_C32_W2, PO_C32_W2_1, PO_C32_W2_2, PO_C32_W2_3, PO_C32_W3, PO_C32_W3_1, PO_C32_W3_2, PO_C32_W3_3,
	PO_C32_W4, PO_C32_W4_1, PO_C32_W4_2, PO_C32_W4_3, PO_C32_W5, PO_C32_W5_1, PO_C32_W5_2, PO_C32_W5_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//KNIGHT_PLAYER_MOVE
	12,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C32_W0, PO_C32_W0_2, PO_C32_W1, PO_C32_W1_2, PO_C32_W2, PO_C32_W2_2, PO_C32_W3, PO_C32_W3_2,
	PO_C32_W4, PO_C32_W4_2, PO_C32_W5, PO_C32_W5,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//KNIGHT_ATTACK
	60,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C32_A0, PO_C32_A0_2, PO_C32_A1, PO_C32_A1, PO_C32_A1, PO_C32_A1, PO_C32_A1, PO_C32_A1,
	PO_C32_A1, PO_C32_A1_1, PO_C32_A1_1, PO_C32_A1_1, PO_C32_A1_1, PO_C32_A1_1, PO_C32_A1_1, PO_C32_A1_2,
	PO_C32_A1_2, PO_C32_A1_2, PO_C32_A1_2, PO_C32_A1_2, PO_C32_A1_2, PO_C32_A1_2, PO_C32_A1_3, PO_C32_A1_3,
	PO_C32_A1_3, PO_C32_A1_3, PO_C32_A1_3, PO_C32_A1_3, PO_C32_A2, PO_C32_A2_2, PO_C32_A3, PO_C32_A3_2,
	PO_C32_A4, PO_C32_A4_2, PO_C32_A5, PO_C32_A5, PO_C32_A5, PO_C32_A5, PO_C32_A5, PO_C32_A5,
	PO_C32_A5, PO_C32_A5, PO_C32_A5, PO_C32_A5, PO_C32_A5, PO_C32_A5, PO_C32_A5, PO_C32_A5,
	PO_C32_A5, PO_C32_A5, PO_C32_A5, PO_C32_A5, PO_C32_A5, PO_C32_A5, PO_C32_A5, PO_C32_A5,
	PO_C32_A5, PO_C32_A5, PO_C32_A5, PO_C32_A5,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 5 * _2X, 5 * _2X,
	5 * _2X, 5 * _2X, 5, 5, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 102 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//KNIGHT_GUARD
	4,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C32_D0, PO_C32_D0, PO_C32_D0, PO_C32_D0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//KNIGHT_GUARDED
	48,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1,
	PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1,
	PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1,
	PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1,
	PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1,
	PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1, PO_C32_D1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	KNIGHT_NEUTRAL,	KNIGHT_GUARD,	DISTANCE_CHECK_XY,	6 * 8 + 4,	RANDOM,	60,
	KNIGHT_NEUTRAL,	KNIGHT_ATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 4,	0,	0,
	KNIGHT_NEUTRAL,	KNIGHT_PLAYER_MOVE,	DISTANCE_CHECK_XY,	8 * 8 + 3,	0,	0,
	KNIGHT_NEUTRAL,	KNIGHT_MOVE,	0,	0,	RANDOM,	40,
	KNIGHT_MOVE,	KNIGHT_ATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 4,	RANDOM,	50,
	KNIGHT_MOVE,	KNIGHT_GUARD,	DISTANCE_CHECK_XY,	6 * 8 + 4,	RANDOM,	60,
	KNIGHT_MOVE,	KNIGHT_PLAYER_MOVE,	DISTANCE_CHECK_XY,	8 * 8 + 3,	0,	0,
	KNIGHT_MOVE,	KNIGHT_NEUTRAL,	0,	0,	RANDOM,	30,
	KNIGHT_PLAYER_MOVE,	KNIGHT_ATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 4,	RANDOM,	60,
	KNIGHT_PLAYER_MOVE,	KNIGHT_GUARD,	ATTACK_CHECK,	0,	RANDOM,	60,
	KNIGHT_PLAYER_MOVE,	KNIGHT_NEUTRAL,	0,	0,	0,	0,
	KNIGHT_ATTACK,	KNIGHT_NEUTRAL,	0,	0,	0,	0,
	KNIGHT_GUARD,	KNIGHT_GUARDED,	0,	0,	0,	0,
	KNIGHT_GUARDED,	KNIGHT_ATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 4,	RANDOM,	60,
	KNIGHT_GUARDED,	KNIGHT_PLAYER_MOVE,	DISTANCE_CHECK_XY,	8 * 8 + 3,	RANDOM,	40,
	KNIGHT_GUARDED,	KNIGHT_NEUTRAL,	DISTANCE_OUT_XY,	8 * 8 + 3,	0,	0,
	-1,
};

const signed short c33mv[] = {
	//상태 데이터
	//SLIME_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C33_N_D_0, PO_C33_N_D_0_1, PO_C33_N_D_0_2, PO_C33_N_D_0_3, PO_C33_N_D_1, PO_C33_N_D_1_1, PO_C33_N_D_1_2, PO_C33_N_D_1_3,
	PO_C33_N_D_2, PO_C33_N_D_2_1, PO_C33_N_D_2_2, PO_C33_N_D_2_3, PO_C33_N_D_3, PO_C33_N_D_3_1, PO_C33_N_D_3_2, PO_C33_N_D_3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SLIME_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C33_N_D_0, PO_C33_N_D_0_1, PO_C33_N_D_0_2, PO_C33_N_D_0_3, PO_C33_N_D_1, PO_C33_N_D_1_1, PO_C33_N_D_1_2, PO_C33_N_D_1_3,
	PO_C33_N_D_2, PO_C33_N_D_2_1, PO_C33_N_D_2_2, PO_C33_N_D_2_3, PO_C33_N_D_3, PO_C33_N_D_3_1, PO_C33_N_D_3_2, PO_C33_N_D_3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SLIME_ATTACK
	48,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C33_A_D_0, PO_C33_A_D_0_1, PO_C33_A_D_0_2, PO_C33_A_D_0_3, PO_C33_A_D_1, PO_C33_A_D_1_A_D_0_1, PO_C33_A_D_1_A_D_0_2, PO_C33_A_D_1_A_D_0_3,
	PO_C33_A_D_0, PO_C33_A_D_0_1, PO_C33_A_D_0_2, PO_C33_A_D_0_3, PO_C33_A_D_1, PO_C33_A_D_1_A_D_2_1, PO_C33_A_D_1_A_D_2_2, PO_C33_A_D_1_A_D_2_3,
	PO_C33_A_D_2, PO_C33_A_D_2, PO_C33_A_D_2_1, PO_C33_A_D_2_1, PO_C33_A_D_2_2, PO_C33_A_D_2_2, PO_C33_A_D_2_3, PO_C33_A_D_2_3,
	PO_C33_A_D_3, PO_C33_A_D_3, PO_C33_A_D_3_1, PO_C33_A_D_3_1, PO_C33_A_D_3_2, PO_C33_A_D_3_2, PO_C33_A_D_3_3, PO_C33_A_D_3_3,
	PO_C33_A_D_4, PO_C33_A_D_4, PO_C33_A_D_4_1, PO_C33_A_D_4_1, PO_C33_A_D_4_2, PO_C33_A_D_4_2, PO_C33_A_D_4_3, PO_C33_A_D_4_3,
	PO_C33_A_D_5, PO_C33_A_D_5, PO_C33_A_D_5_1, PO_C33_A_D_5_1, PO_C33_A_D_5_2, PO_C33_A_D_5_2, PO_C33_A_D_5_3, PO_C33_A_D_5_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c34mv[] = {
	//상태 데이터
	//KIMERA_NEUTRAL
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C34_N0, PO_C34_N0, PO_C34_N0_1, PO_C34_N0_2, PO_C34_N0_2, PO_C34_N0_3, PO_C34_N1, PO_C34_N1,
	PO_C34_N1_1, PO_C34_N1_2, PO_C34_N1_2, PO_C34_N1_3, PO_C34_N2, PO_C34_N2, PO_C34_N2_1, PO_C34_N2_2,
	PO_C34_N2_2, PO_C34_N2_3, PO_C34_N3, PO_C34_N3, PO_C34_N3_1, PO_C34_N3_2, PO_C34_N3_2, PO_C34_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//KIMERA_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C34_W0, PO_C34_W0_1, PO_C34_W0_2, PO_C34_W0_3, PO_C34_W1, PO_C34_W1_1, PO_C34_W1_2, PO_C34_W1_3,
	PO_C34_W2, PO_C34_W2_1, PO_C34_W2_2, PO_C34_W2_3, PO_C34_W3, PO_C34_W3_1, PO_C34_W3_2, PO_C34_W3_3,	//상태 프레임별 모션
	1, 1, 0 * _2X, 0 * _2X, 3, 3, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//KIMERA_FIRESHOT
	120,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C34_FIREATK0, PO_C34_FIREATK0_2, PO_C34_FIREATK1, PO_C34_FIREATK1, PO_C34_FIREATK1, PO_C34_FIREATK1, PO_C34_FIREATK1, PO_C34_FIREATK1,
	PO_C34_FIREATK1_1, PO_C34_FIREATK1_1, PO_C34_FIREATK1_1, PO_C34_FIREATK1_1, PO_C34_FIREATK1_1, PO_C34_FIREATK1_2, PO_C34_FIREATK1_2, PO_C34_FIREATK1_2,
	PO_C34_FIREATK1_2, PO_C34_FIREATK1_2, PO_C34_FIREATK1_2, PO_C34_FIREATK1_3, PO_C34_FIREATK1_3, PO_C34_FIREATK1_3, PO_C34_FIREATK1_3, PO_C34_FIREATK1_3,
	PO_C34_FIREATK2, PO_C34_FIREATK2_2, PO_C34_FIREATK3, PO_C34_FIREATK3_2, PO_C34_FIREATK4, PO_C34_FIREATK4_2, PO_C34_FIREATK5, PO_C34_FIREATK5,
	PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5,
	PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5,
	PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5,
	PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5,
	PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5,
	PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5,
	PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5,
	PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5,
	PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5,
	PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5,
	PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5, PO_C34_FIREATK5,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//KIMERA_ICESHOT
	120,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C34_ICEATK0, PO_C34_ICEATK0, PO_C34_ICEATK0, PO_C34_ICEATK0, PO_C34_ICEATK0, PO_C34_ICEATK0, PO_C34_ICEATK0_1, PO_C34_ICEATK0_1,
	PO_C34_ICEATK0_1, PO_C34_ICEATK0_1, PO_C34_ICEATK0_1, PO_C34_ICEATK0_2, PO_C34_ICEATK0_2, PO_C34_ICEATK0_2, PO_C34_ICEATK0_2, PO_C34_ICEATK0_2,
	PO_C34_ICEATK0_2, PO_C34_ICEATK0_3, PO_C34_ICEATK0_3, PO_C34_ICEATK0_3, PO_C34_ICEATK0_3, PO_C34_ICEATK0_3, PO_C34_ICEATK1, PO_C34_ICEATK1_2,
	PO_C34_ICEATK2, PO_C34_ICEATK2_2, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3,
	PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3,
	PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3,
	PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3,
	PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3,
	PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3,
	PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3,
	PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3,
	PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3,
	PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3,
	PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3,
	PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3, PO_C34_ICEATK3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//KIMERA_SPIN
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C34_SPINATK0, PO_C34_SPINATK0_1, PO_C34_SPINATK0_2, PO_C34_SPINATK0_3, PO_C34_SPINATK1, PO_C34_SPINATK1_1, PO_C34_SPINATK1_2, PO_C34_SPINATK1_3,
	PO_C34_SPINATK2, PO_C34_SPINATK2_1, PO_C34_SPINATK2_2, PO_C34_SPINATK2_3, PO_C34_SPINATK3, PO_C34_SPINATK3_1, PO_C34_SPINATK3_2, PO_C34_SPINATK3_3,
	PO_C34_SPINATK4, PO_C34_SPINATK4_1, PO_C34_SPINATK4_2, PO_C34_SPINATK4_3, PO_C34_SPINATK5, PO_C34_SPINATK5_SPINATK6_1, PO_C34_SPINATK5_SPINATK6_2, PO_C34_SPINATK5_SPINATK6_3,
	PO_C34_SPINATK6, PO_C34_SPINATK6_1, PO_C34_SPINATK6_2, PO_C34_SPINATK6_3, PO_C34_SPINATK7, PO_C34_SPINATK7, PO_C34_SPINATK7, PO_C34_SPINATK7,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 103, 0 * _2X,	//상태 프레임별 이동폭 Y

	//KIMERA_SPINED
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C34_SPINATK2, PO_C34_SPINATK2_1, PO_C34_SPINATK2_2, PO_C34_SPINATK2_3, PO_C34_SPINATK3, PO_C34_SPINATK3_1, PO_C34_SPINATK3_2, PO_C34_SPINATK3_3,
	PO_C34_SPINATK4, PO_C34_SPINATK4_1, PO_C34_SPINATK4_2, PO_C34_SPINATK4_3, PO_C34_SPINATK5, PO_C34_SPINATK5_SPINATK2_1, PO_C34_SPINATK5_SPINATK2_2, PO_C34_SPINATK5_SPINATK2_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	-18 * _2X, -18 * _2X, -18 * _2X, -18 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//KIMERA_LAND_READY
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C34_N0, PO_C34_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//KIMERA_LANDING
	56,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C34_SPINATK6, PO_C34_SPINATK6_1, PO_C34_SPINATK6_2, PO_C34_SPINATK6_3, PO_C34_SPINATK7, PO_C34_SPINATK7_1, PO_C34_SPINATK7_2, PO_C34_SPINATK7_3,
	PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1,
	PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1,
	PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1,
	PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1,
	PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1,
	PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1, PO_C34_SPINATK1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	KIMERA_NEUTRAL,	KIMERA_FIRESHOT,	0,	0,	RANDOM,	33,
	KIMERA_NEUTRAL,	KIMERA_ICESHOT,	0,	0,	RANDOM,	20,
	KIMERA_NEUTRAL,	KIMERA_SPIN,	0,	0,	RANDOM,	25,
	KIMERA_NEUTRAL,	KIMERA_MOVE,	0,	0,	RANDOM,	20,
	KIMERA_MOVE,	KIMERA_FIRESHOT,	0,	0,	RANDOM,	30,
	KIMERA_MOVE,	KIMERA_ICESHOT,	0,	0,	RANDOM,	30,
	KIMERA_MOVE,	KIMERA_SPIN,	0,	0,	RANDOM,	30,
	KIMERA_MOVE,	KIMERA_NEUTRAL,	0,	0,	RANDOM,	20,
	KIMERA_FIRESHOT,	KIMERA_ICESHOT,	0,	0,	0,	0,
	KIMERA_ICESHOT,	KIMERA_NEUTRAL,	0,	0,	0,	0,
	KIMERA_SPIN,	KIMERA_SPINED,	0,	0,	0,	0,
	KIMERA_LANDING,	KIMERA_NEUTRAL,	0,	0,	0,	0,
	-1,
};

const signed short c35mv[] = {
	//상태 데이터
	//FAIRY_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C35_N0, PO_C35_N0_1, PO_C35_N0_2, PO_C35_N0_3, PO_C35_N1, PO_C35_N1_1, PO_C35_N1_2, PO_C35_N1_3,
	PO_C35_N2, PO_C35_N2_1, PO_C35_N2_2, PO_C35_N2_3, PO_C35_N3, PO_C35_N3_1, PO_C35_N3_2, PO_C35_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//FAIRY_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C35_W0, PO_C35_W0_1, PO_C35_W0_2, PO_C35_W0_3, PO_C35_W1, PO_C35_W1_1, PO_C35_W1_2, PO_C35_W1_3,
	PO_C35_W2, PO_C35_W2_1, PO_C35_W2_2, PO_C35_W2_3, PO_C35_W3, PO_C35_W3_1, PO_C35_W3_2, PO_C35_W3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//FAIRY_ATTACK
	22,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C35_N0, PO_C35_N0_1, PO_C35_N0_2, PO_C35_N0_3, PO_C35_N1, PO_C35_N1_1, PO_C35_N1_2, PO_C35_N1_3,
	PO_C35_N2, PO_C35_N2_2, PO_C35_N3, PO_C35_N3_1, PO_C35_N3_2, PO_C35_N3_3, PO_C35_N0, PO_C35_N0_2,
	PO_C35_N1, PO_C35_N1_2, PO_C35_N2, PO_C35_N2_2, PO_C35_N3, PO_C35_N3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 1 * _2X, 1 * _2X,
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	FAIRY_NEUTRAL,	FAIRY_ATTACK,	DISTANCE_CHECK_XY,	2 * 8 + 7,	0,	0,
	FAIRY_NEUTRAL,	FAIRY_MOVE,	DISTANCE_CHECK_XY,	8 * 8 + 7,	0,	0,
	FAIRY_MOVE,	FAIRY_ATTACK,	DISTANCE_CHECK_XY,	2 * 8 + 7,	0,	0,
	FAIRY_MOVE,	FAIRY_NEUTRAL,	DISTANCE_OUT_XY,	8 * 8 + 7,	0,	0,
	FAIRY_ATTACK,	FAIRY_MOVE,	0,	0,	0,	0,
	-1,
};

const signed short c36mv[] = {
	//상태 데이터
	//CIRCLE_NEUTRAL
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C36_N0, PO_C36_N0, PO_C36_N0_1, PO_C36_N0_2, PO_C36_N0_2, PO_C36_N0_3, PO_C36_N1, PO_C36_N1,
	PO_C36_N1_1, PO_C36_N1_2, PO_C36_N1_2, PO_C36_N1_3, PO_C36_N2, PO_C36_N2, PO_C36_N2_1, PO_C36_N2_2,
	PO_C36_N2_2, PO_C36_N2_3, PO_C36_N3, PO_C36_N3, PO_C36_N3_1, PO_C36_N3_2, PO_C36_N3_2, PO_C36_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CIRCLE_PLAYER_MOVE
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C36_N0, PO_C36_N0_1, PO_C36_N0_2, PO_C36_N0_3, PO_C36_N1, PO_C36_N1_1, PO_C36_N1_2, PO_C36_N1_3,
	PO_C36_N2, PO_C36_N2_1, PO_C36_N2_2, PO_C36_N2_3, PO_C36_N3, PO_C36_N3_1, PO_C36_N3_2, PO_C36_N3_3,
	PO_C36_N0, PO_C36_N0_1, PO_C36_N0_2, PO_C36_N0_3, PO_C36_N1, PO_C36_N1_1, PO_C36_N1_2, PO_C36_N1_3,
	PO_C36_N2, PO_C36_N2_1, PO_C36_N2_2, PO_C36_N2_3, PO_C36_N3, PO_C36_N3_1, PO_C36_N3_2, PO_C36_N3_3,	//상태 프레임별 모션
	51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X,
	51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X,
	51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X,
	51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 52 * _2X, 0 * _2X, 51 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X,
	51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X,
	51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X,
	51 * _2X, 0 * _2X, 51 * _2X, 0 * _2X, 52 * _2X, 0 * _2X, 51 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CIRCLE_RETREAT
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C36_N0, PO_C36_N0_1, PO_C36_N0_2, PO_C36_N0_3, PO_C36_N1, PO_C36_N1_1, PO_C36_N1_2, PO_C36_N1_3,
	PO_C36_N2, PO_C36_N2_1, PO_C36_N2_2, PO_C36_N2_3, PO_C36_N3, PO_C36_N3_1, PO_C36_N3_2, PO_C36_N3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CIRCLE_DASH
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C36_N0, PO_C36_N0_2, PO_C36_N1, PO_C36_N1_2, PO_C36_N2, PO_C36_N2_2, PO_C36_N3, PO_C36_N3_2,
	PO_C36_N0, PO_C36_N0_2, PO_C36_N1, PO_C36_N1_2, PO_C36_N2, PO_C36_N2_2, PO_C36_N3, PO_C36_N3_2,
	PO_C36_N0, PO_C36_N0_2, PO_C36_N1, PO_C36_N1_2, PO_C36_N2, PO_C36_N2_2, PO_C36_N3, PO_C36_N3_2,	//상태 프레임별 모션
	54 * _2X, 0 * _2X, 54 * _2X, 0 * _2X, 54 * _2X, 0 * _2X, 54 * _2X, 0 * _2X,
	54 * _2X, 0 * _2X, 54 * _2X, 0 * _2X, 54 * _2X, 0 * _2X, 54 * _2X, 0 * _2X,
	54 * _2X, 0 * _2X, 54 * _2X, 0 * _2X, 54 * _2X, 0 * _2X, 54 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CIRCLE_STOP
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C36_N0, PO_C36_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	CIRCLE_NEUTRAL,	CIRCLE_DASH,	ATTACK_CHECK,	0,	0,	0,
	CIRCLE_NEUTRAL,	CIRCLE_STOP,	DIR_DIFFER_PLAYER,	0,	0,	0,
	CIRCLE_NEUTRAL,	CIRCLE_PLAYER_MOVE,	DISTANCE_CHECK_XY,	8 * 8 + 6,	0,	0,
	CIRCLE_PLAYER_MOVE,	CIRCLE_DASH,	ATTACK_CHECK,	0,	0,	0,
	CIRCLE_PLAYER_MOVE,	CIRCLE_STOP,	DIR_DIFFER_PLAYER,	0,	0,	0,
	CIRCLE_PLAYER_MOVE,	CIRCLE_NEUTRAL,	DISTANCE_OUT_XY,	8 * 8 + 6,	0,	0,
	CIRCLE_RETREAT,	CIRCLE_DASH,	ATTACK_CHECK,	0,	0,	0,
	CIRCLE_RETREAT,	CIRCLE_NEUTRAL,	COMPARE_FRAME,	10,	0,	0,
	CIRCLE_DASH,	CIRCLE_RETREAT,	COMPARE_FRAME,	10,	0,	0,
	CIRCLE_STOP,	CIRCLE_DASH,	ATTACK_CHECK,	0,	0,	0,
	CIRCLE_STOP,	CIRCLE_PLAYER_MOVE,	DIR_SAME_PLAYER,	0,	0,	0,
	CIRCLE_STOP,	CIRCLE_NEUTRAL,	DISTANCE_OUT_XY,	8 * 8 + 6,	0,	0,
	-1,
};

const signed short c37mv[] = {
	//상태 데이터
	//ANGEL_NEUTRAL
	28,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C37_N0, PO_C37_N0_1, PO_C37_N0_2, PO_C37_N0_3, PO_C37_N1, PO_C37_N1_N2_1, PO_C37_N1_N2_2, PO_C37_N1_N2_3,
	PO_C37_N2, PO_C37_N2_N3_1, PO_C37_N2_N3_2, PO_C37_N2_N3_3, PO_C37_N3, PO_C37_N3_N2_1, PO_C37_N3_N2_2, PO_C37_N3_N2_3,
	PO_C37_N2, PO_C37_N2_N1_1, PO_C37_N2_N1_2, PO_C37_N2_N1_3, PO_C37_N1, PO_C37_N1_N0_1, PO_C37_N1_N0_2, PO_C37_N1_N0_3,
	PO_C37_N0, PO_C37_N0, PO_C37_N0, PO_C37_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ANGEL_ATTACK
	72,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C37_ATKREAD0, PO_C37_ATKREAD0_1, PO_C37_ATKREAD0_2, PO_C37_ATKREAD0_3, PO_C37_ATKREAD1, PO_C37_ATKREAD1, PO_C37_ATKREAD1, PO_C37_ATKREAD1,
	PO_C37_ATKREAD1, PO_C37_ATKREAD1, PO_C37_ATKREAD1, PO_C37_ATKREAD1, PO_C37_ATKREAD1_1, PO_C37_ATKREAD1_1, PO_C37_ATKREAD1_1, PO_C37_ATKREAD1_1,
	PO_C37_ATKREAD1_1, PO_C37_ATKREAD1_1, PO_C37_ATKREAD1_1, PO_C37_ATKREAD1_1, PO_C37_ATKREAD1_2, PO_C37_ATKREAD1_2, PO_C37_ATKREAD1_2, PO_C37_ATKREAD1_2,
	PO_C37_ATKREAD1_2, PO_C37_ATKREAD1_2, PO_C37_ATKREAD1_2, PO_C37_ATKREAD1_2, PO_C37_ATKREAD1_3, PO_C37_ATKREAD1_3, PO_C37_ATKREAD1_3, PO_C37_ATKREAD1_3,
	PO_C37_ATKREAD1_3, PO_C37_ATKREAD1_3, PO_C37_ATKREAD1_3, PO_C37_ATKREAD1_3, PO_C37_SHOTATK0, PO_C37_SHOTATK0_1, PO_C37_SHOTATK0_2, PO_C37_SHOTATK0_3,
	PO_C37_SHOTATK1, PO_C37_SHOTATK1_2, PO_C37_ATK0, PO_C37_ATK0_2, PO_C37_ATK1, PO_C37_ATK1_2, PO_C37_ATK2, PO_C37_ATK2_2,
	PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3,
	PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3,
	PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ANGEL_MOVE_DOWN
	20,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C37_N0, PO_C37_N0_1, PO_C37_N0_2, PO_C37_N0_3, PO_C37_N1, PO_C37_N1_N2_1, PO_C37_N1_N2_2, PO_C37_N1_N2_3,
	PO_C37_N2, PO_C37_N2_N3_1, PO_C37_N2_N3_2, PO_C37_N2_N3_3, PO_C37_N3, PO_C37_N3_N2_1, PO_C37_N3_N2_2, PO_C37_N3_N2_3,
	PO_C37_N2, PO_C37_N2, PO_C37_N2, PO_C37_N2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,	//상태 프레임별 이동폭 Y

	//ANGEL_MOVE_READY
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C37_N0, PO_C37_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ANGEL_MOVE_CENTER
	20,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C37_N0, PO_C37_N0_1, PO_C37_N0_2, PO_C37_N0_3, PO_C37_N1, PO_C37_N1_N2_1, PO_C37_N1_N2_2, PO_C37_N1_N2_3,
	PO_C37_N2, PO_C37_N2_N3_1, PO_C37_N2_N3_2, PO_C37_N2_N3_3, PO_C37_N3, PO_C37_N3_N2_1, PO_C37_N3_N2_2, PO_C37_N3_N2_3,
	PO_C37_N2, PO_C37_N2, PO_C37_N2, PO_C37_N2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X,
	4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X,
	4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X,	//상태 프레임별 이동폭 Y

	//ANGEL_SHOT
	76,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C37_ATKREAD0, PO_C37_ATKREAD0_1, PO_C37_ATKREAD0_2, PO_C37_ATKREAD0_3, PO_C37_ATKREAD1, PO_C37_ATKREAD1, PO_C37_ATKREAD1, PO_C37_ATKREAD1,
	PO_C37_ATKREAD1, PO_C37_ATKREAD1, PO_C37_ATKREAD1, PO_C37_ATKREAD1, PO_C37_ATKREAD1_1, PO_C37_ATKREAD1_1, PO_C37_ATKREAD1_1, PO_C37_ATKREAD1_1,
	PO_C37_ATKREAD1_1, PO_C37_ATKREAD1_1, PO_C37_ATKREAD1_1, PO_C37_ATKREAD1_1, PO_C37_ATKREAD1_2, PO_C37_ATKREAD1_2, PO_C37_ATKREAD1_2, PO_C37_ATKREAD1_2,
	PO_C37_ATKREAD1_2, PO_C37_ATKREAD1_2, PO_C37_ATKREAD1_2, PO_C37_ATKREAD1_2, PO_C37_ATKREAD1_3, PO_C37_ATKREAD1_3, PO_C37_ATKREAD1_3, PO_C37_ATKREAD1_3,
	PO_C37_ATKREAD1_3, PO_C37_ATKREAD1_3, PO_C37_ATKREAD1_3, PO_C37_ATKREAD1_3, PO_C37_SHOTATK0, PO_C37_SHOTATK0_1, PO_C37_SHOTATK0_2, PO_C37_SHOTATK0_3,
	PO_C37_SHOTATK1, PO_C37_SHOTATK1_2, PO_C37_ATK0, PO_C37_ATK0_2, PO_C37_ATK1, PO_C37_ATK1_2, PO_C37_ATK2, PO_C37_ATK2_2,
	PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3,
	PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3,
	PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3,
	PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3, PO_C37_ATK3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ANGEL_DASHREADY
	20,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C37_DASHREADY_L0, PO_C37_DASHREADY_L0_1, PO_C37_DASHREADY_L0_2, PO_C37_DASHREADY_L0_3, PO_C37_DASHREADY_L1, PO_C37_DASHREADY_L1_1, PO_C37_DASHREADY_L1_2, PO_C37_DASHREADY_L1_3,
	PO_C37_DASHREADY_L2, PO_C37_DASHREADY_L2, PO_C37_DASHREADY_L2, PO_C37_DASHREADY_L2, PO_C37_DASHREADY_L2, PO_C37_DASHREADY_L2, PO_C37_DASHREADY_L2, PO_C37_DASHREADY_L2,
	PO_C37_DASHREADY_L2, PO_C37_DASHREADY_L2, PO_C37_DASHREADY_L2, PO_C37_DASHREADY_L2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ANGEL_DASH
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C37_DASHATK_L0, PO_C37_DASHATK_L0,	//상태 프레임별 모션
	4 * _2X, 4 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ANGEL_DASHUP
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C37_DASHATK_U0, PO_C37_DASHATK_U0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	-4 * _2X, -4 * _2X,	//상태 프레임별 이동폭 Y

	//ANGEL_DASHDOWN
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C37_DASHATK_D0, PO_C37_DASHATK_D0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	4 * _2X, 4 * _2X,	//상태 프레임별 이동폭 Y

	//ANGEL_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C37_N0, PO_C37_N0_1, PO_C37_N0_2, PO_C37_N0_3, PO_C37_N1, PO_C37_N1_N2_1, PO_C37_N1_N2_2, PO_C37_N1_N2_3,
	PO_C37_N2, PO_C37_N2_N3_1, PO_C37_N2_N3_2, PO_C37_N2_N3_3, PO_C37_N3, PO_C37_N3_N0_1, PO_C37_N3_N0_2, PO_C37_N3_N0_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ANGEL_DASHATTACK
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C37_DASHATK_L1, PO_C37_DASHATK_L1, PO_C37_DASHATK_L1, PO_C37_DASHATK_L1, PO_C37_DASHATK_L1, PO_C37_DASHATK_L1, PO_C37_DASHATK_L1, PO_C37_DASHATK_L1,
	PO_C37_DASHATK_L1_1, PO_C37_DASHATK_L1_1, PO_C37_DASHATK_L1_1, PO_C37_DASHATK_L1_1, PO_C37_DASHATK_L1_1, PO_C37_DASHATK_L1_1, PO_C37_DASHATK_L1_1, PO_C37_DASHATK_L1_2,
	PO_C37_DASHATK_L1_2, PO_C37_DASHATK_L1_2, PO_C37_DASHATK_L1_2, PO_C37_DASHATK_L1_2, PO_C37_DASHATK_L1_2, PO_C37_DASHATK_L1_2, PO_C37_DASHATK_L1_2, PO_C37_DASHATK_L1_3,
	PO_C37_DASHATK_L1_3, PO_C37_DASHATK_L1_3, PO_C37_DASHATK_L1_3, PO_C37_DASHATK_L1_3, PO_C37_DASHATK_L1_3, PO_C37_DASHATK_L1_3, PO_C37_DASHATK_L0, PO_C37_DASHATK_L0_2,	//상태 프레임별 모션
	4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X,
	4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X,
	4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X,
	4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	ANGEL_NEUTRAL,	ANGEL_SHOT,	0,	0,	RANDOM,	30,
	ANGEL_NEUTRAL,	ANGEL_ATTACK,	0,	0,	RANDOM,	30,
	ANGEL_NEUTRAL,	ANGEL_MOVE_DOWN,	0,	0,	0,	0,
	ANGEL_SHOT,	ANGEL_NEUTRAL,	0,	0,	0,	0,
	ANGEL_ATTACK,	ANGEL_NEUTRAL,	0,	0,	0,	0,
	ANGEL_MOVE_DOWN,	ANGEL_DASHREADY,	0,	0,	0,	0,
	ANGEL_MOVE_READY,	ANGEL_MOVE_CENTER,	0,	0,	0,	0,
	ANGEL_MOVE_CENTER,	ANGEL_NEUTRAL,	0,	0,	0,	0,
	ANGEL_DASHREADY,	ANGEL_DASH,	0,	0,	0,	0,
	-1,
};

const signed short c38mv[] = {
	//상태 데이터
	//DARKDRAGON_HEAD
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C38_NHEAD0, PO_C38_NHEAD0_2, PO_C38_NHEAD1, PO_C38_NHEAD1_2, PO_C38_NHEAD2, PO_C38_NHEAD2_2, PO_C38_NHEAD3, PO_C38_NHEAD3_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DARKDRAGON_BODY
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C38_NBODY0, PO_C38_NBODY0_2, PO_C38_NBODY1, PO_C38_NBODY1_2, PO_C38_NBODY2, PO_C38_NBODY2_2, PO_C38_NBODY3, PO_C38_NBODY3_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DARKDRAGON_TAIL
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C38_NTAIL0, PO_C38_NTAIL0_2, PO_C38_NTAIL1, PO_C38_NTAIL1_2, PO_C38_NTAIL2, PO_C38_NTAIL2_2, PO_C38_NTAIL3, PO_C38_NTAIL3_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c39mv[] = {
	//상태 데이터
	//DARKGIANT_NEUTRAL
	48,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C39_N0, PO_C39_N0, PO_C39_N0_1, PO_C39_N0_1, PO_C39_N0_2, PO_C39_N0_2, PO_C39_N0_3, PO_C39_N0_3,
	PO_C39_N1, PO_C39_N1, PO_C39_N1_1, PO_C39_N1_1, PO_C39_N1_2, PO_C39_N1_2, PO_C39_N1_3, PO_C39_N1_3,
	PO_C39_N2, PO_C39_N2, PO_C39_N2_1, PO_C39_N2_1, PO_C39_N2_2, PO_C39_N2_2, PO_C39_N2_3, PO_C39_N2_3,
	PO_C39_N3, PO_C39_N3, PO_C39_N3_1, PO_C39_N3_1, PO_C39_N3_2, PO_C39_N3_2, PO_C39_N3_3, PO_C39_N3_3,
	PO_C39_N4, PO_C39_N4, PO_C39_N4_1, PO_C39_N4_1, PO_C39_N4_2, PO_C39_N4_2, PO_C39_N4_3, PO_C39_N4_3,
	PO_C39_N5, PO_C39_N5, PO_C39_N5_1, PO_C39_N5_1, PO_C39_N5_2, PO_C39_N5_2, PO_C39_N5_3, PO_C39_N5_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DARKGIANT_MOVE
	288,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C39_W0, PO_C39_W0_1, PO_C39_W0_2, PO_C39_W0_3, PO_C39_W1, PO_C39_W1_1, PO_C39_W1_2, PO_C39_W1_3,
	PO_C39_W2, PO_C39_W2_1, PO_C39_W2_2, PO_C39_W2_3, PO_C39_W3, PO_C39_W3_1, PO_C39_W3_2, PO_C39_W3_3,
	PO_C39_W4, PO_C39_W4_T1, PO_C39_W4_2, PO_C39_W4_3, PO_C39_W4_1, PO_C39_W4_1, PO_C39_W4_1, PO_C39_W4_1,
	PO_C39_W4_1_1, PO_C39_W4_1_1, PO_C39_W4_1_1, PO_C39_W4_1_1, PO_C39_W4_1_2, PO_C39_W4_1_2, PO_C39_W4_1_2, PO_C39_W4_1_2,
	PO_C39_W4_1_3, PO_C39_W4_1_3, PO_C39_W4_1_3, PO_C39_W4_1_3, PO_C39_W5, PO_C39_W5_1, PO_C39_W5_2, PO_C39_W5_3,
	PO_C39_W6, PO_C39_W6_1, PO_C39_W6_2, PO_C39_W6_3, PO_C39_W7, PO_C39_W7_1, PO_C39_W7_2, PO_C39_W7_3,
	PO_C39_W8, PO_C39_W8_1, PO_C39_W8_2, PO_C39_W8_3, PO_C39_W9, PO_C39_W9_T1, PO_C39_W9_2, PO_C39_W9_3,
	PO_C39_W9_1, PO_C39_W9_1, PO_C39_W9_1, PO_C39_W9_1, PO_C39_W9_1_1, PO_C39_W9_1_1, PO_C39_W9_1_1, PO_C39_W9_1_1,
	PO_C39_W9_1_2, PO_C39_W9_1_2, PO_C39_W9_1_2, PO_C39_W9_1_2, PO_C39_W9_1_3, PO_C39_W9_1_3, PO_C39_W9_1_3, PO_C39_W9_1_3,
	PO_C39_W0, PO_C39_W0_1, PO_C39_W0_2, PO_C39_W0_3, PO_C39_W1, PO_C39_W1_1, PO_C39_W1_2, PO_C39_W1_3,
	PO_C39_W2, PO_C39_W2_1, PO_C39_W2_2, PO_C39_W2_3, PO_C39_W3, PO_C39_W3_1, PO_C39_W3_2, PO_C39_W3_3,
	PO_C39_W4, PO_C39_W4_T1, PO_C39_W4_2, PO_C39_W4_3, PO_C39_W4_1, PO_C39_W4_1, PO_C39_W4_1, PO_C39_W4_1,
	PO_C39_W4_1_1, PO_C39_W4_1_1, PO_C39_W4_1_1, PO_C39_W4_1_1, PO_C39_W4_1_2, PO_C39_W4_1_2, PO_C39_W4_1_2, PO_C39_W4_1_2,
	PO_C39_W4_1_3, PO_C39_W4_1_3, PO_C39_W4_1_3, PO_C39_W4_1_3, PO_C39_W5, PO_C39_W5_1, PO_C39_W5_2, PO_C39_W5_3,
	PO_C39_W6, PO_C39_W6_1, PO_C39_W6_2, PO_C39_W6_3, PO_C39_W7, PO_C39_W7_1, PO_C39_W7_2, PO_C39_W7_3,
	PO_C39_W8, PO_C39_W8_1, PO_C39_W8_2, PO_C39_W8_3, PO_C39_W9, PO_C39_W9_T1, PO_C39_W9_2, PO_C39_W9_3,
	PO_C39_W9_1, PO_C39_W9_1, PO_C39_W9_1, PO_C39_W9_1, PO_C39_W9_1_1, PO_C39_W9_1_1, PO_C39_W9_1_1, PO_C39_W9_1_1,
	PO_C39_W9_1_2, PO_C39_W9_1_2, PO_C39_W9_1_2, PO_C39_W9_1_2, PO_C39_W9_1_3, PO_C39_W9_1_3, PO_C39_W9_1_3, PO_C39_W9_1_3,
	PO_C39_W0, PO_C39_W0_1, PO_C39_W0_2, PO_C39_W0_3, PO_C39_W1, PO_C39_W1_1, PO_C39_W1_2, PO_C39_W1_3,
	PO_C39_W2, PO_C39_W2_1, PO_C39_W2_2, PO_C39_W2_3, PO_C39_W3, PO_C39_W3_1, PO_C39_W3_2, PO_C39_W3_3,
	PO_C39_W4, PO_C39_W4_T1, PO_C39_W4_2, PO_C39_W4_3, PO_C39_W4_1, PO_C39_W4_1, PO_C39_W4_1, PO_C39_W4_1,
	PO_C39_W4_1_1, PO_C39_W4_1_1, PO_C39_W4_1_1, PO_C39_W4_1_1, PO_C39_W4_1_2, PO_C39_W4_1_2, PO_C39_W4_1_2, PO_C39_W4_1_2,
	PO_C39_W4_1_3, PO_C39_W4_1_3, PO_C39_W4_1_3, PO_C39_W4_1_3, PO_C39_W5, PO_C39_W5_1, PO_C39_W5_2, PO_C39_W5_3,
	PO_C39_W6, PO_C39_W6_1, PO_C39_W6_2, PO_C39_W6_3, PO_C39_W7, PO_C39_W7_1, PO_C39_W7_2, PO_C39_W7_3,
	PO_C39_W8, PO_C39_W8_1, PO_C39_W8_2, PO_C39_W8_3, PO_C39_W9, PO_C39_W9_T1, PO_C39_W9_2, PO_C39_W9_3,
	PO_C39_W9_1, PO_C39_W9_1, PO_C39_W9_1, PO_C39_W9_1, PO_C39_W9_1_1, PO_C39_W9_1_1, PO_C39_W9_1_1, PO_C39_W9_1_1,
	PO_C39_W9_1_2, PO_C39_W9_1_2, PO_C39_W9_1_2, PO_C39_W9_1_2, PO_C39_W9_1_3, PO_C39_W9_1_3, PO_C39_W9_1_3, PO_C39_W9_1_3,
	PO_C39_W0, PO_C39_W0_1, PO_C39_W0_2, PO_C39_W0_3, PO_C39_W1, PO_C39_W1_1, PO_C39_W1_2, PO_C39_W1_3,
	PO_C39_W2, PO_C39_W2_1, PO_C39_W2_2, PO_C39_W2_3, PO_C39_W3, PO_C39_W3_1, PO_C39_W3_2, PO_C39_W3_3,
	PO_C39_W4, PO_C39_W4_T1, PO_C39_W4_2, PO_C39_W4_3, PO_C39_W4_1, PO_C39_W4_1, PO_C39_W4_1, PO_C39_W4_1,
	PO_C39_W4_1_1, PO_C39_W4_1_1, PO_C39_W4_1_1, PO_C39_W4_1_1, PO_C39_W4_1_2, PO_C39_W4_1_2, PO_C39_W4_1_2, PO_C39_W4_1_2,
	PO_C39_W4_1_3, PO_C39_W4_1_3, PO_C39_W4_1_3, PO_C39_W4_1_3, PO_C39_W5, PO_C39_W5_1, PO_C39_W5_2, PO_C39_W5_3,
	PO_C39_W6, PO_C39_W6_1, PO_C39_W6_2, PO_C39_W6_3, PO_C39_W7, PO_C39_W7_1, PO_C39_W7_2, PO_C39_W7_3,
	PO_C39_W8, PO_C39_W8_1, PO_C39_W8_2, PO_C39_W8_3, PO_C39_W9, PO_C39_W9_T1, PO_C39_W9_2, PO_C39_W9_3,
	PO_C39_W9_1, PO_C39_W9_1, PO_C39_W9_1, PO_C39_W9_1, PO_C39_W9_1_1, PO_C39_W9_1_1, PO_C39_W9_1_1, PO_C39_W9_1_1,
	PO_C39_W9_1_2, PO_C39_W9_1_2, PO_C39_W9_1_2, PO_C39_W9_1_2, PO_C39_W9_1_3, PO_C39_W9_1_3, PO_C39_W9_1_3, PO_C39_W9_1_3,	//상태 프레임별 모션
	5, 5, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 5, 5, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	5, 5, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 5, 5, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	5, 5, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 5, 5, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	5, 5, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 5, 5, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	DARKGIANT_NEUTRAL,	DARKGIANT_MOVE,	DISTANCE_CHECK_XY,	8 * 8 + 4,	0,	0,
	DARKGIANT_MOVE,	DARKGIANT_NEUTRAL,	DISTANCE_OUT_XY,	8 * 8 + 4,	0,	0,
	-1,
};

const signed short c40mv[] = {
	//상태 데이터
	//FOGRA_CLOSEEYE
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C40_OPENEYE0, PO_C40_OPENEYE0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//FOGRA_OPENEYE
	40,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C40_OPENEYE0, PO_C40_OPENEYE0, PO_C40_OPENEYE0_1, PO_C40_OPENEYE0_1, PO_C40_OPENEYE0_2, PO_C40_OPENEYE0_2, PO_C40_OPENEYE0_3, PO_C40_OPENEYE0_3,
	PO_C40_OPENEYE1, PO_C40_OPENEYE1, PO_C40_OPENEYE1_1, PO_C40_OPENEYE1_1, PO_C40_OPENEYE1_2, PO_C40_OPENEYE1_2, PO_C40_OPENEYE1_3, PO_C40_OPENEYE1_3,
	PO_C40_OPENEYE2, PO_C40_OPENEYE2, PO_C40_OPENEYE2_OPENEYE3_1, PO_C40_OPENEYE2_OPENEYE3_1, PO_C40_OPENEYE2_OPENEYE3_2, PO_C40_OPENEYE2_OPENEYE3_2, PO_C40_OPENEYE2_OPENEYE3_3, PO_C40_OPENEYE2_OPENEYE3_3,
	PO_C40_OPENEYE3, PO_C40_OPENEYE3, PO_C40_OPENEYE3, PO_C40_OPENEYE3, PO_C40_OPENEYE3_OPENEYE0_1, PO_C40_OPENEYE3_OPENEYE0_1, PO_C40_OPENEYE3_OPENEYE0_1, PO_C40_OPENEYE3_OPENEYE0_1,
	PO_C40_OPENEYE3_OPENEYE0_2, PO_C40_OPENEYE3_OPENEYE0_2, PO_C40_OPENEYE3_OPENEYE0_2, PO_C40_OPENEYE3_OPENEYE0_2, PO_C40_OPENEYE3_OPENEYE0_3, PO_C40_OPENEYE3_OPENEYE0_3, PO_C40_OPENEYE3_OPENEYE0_3, PO_C40_OPENEYE3_OPENEYE0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//FOGRA_NEUTRAL
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C40_OPENEYE4, PO_C40_OPENEYE4, PO_C40_OPENEYE4_OPENEYE5_1, PO_C40_OPENEYE4_OPENEYE5_2, PO_C40_OPENEYE4_OPENEYE5_2, PO_C40_OPENEYE4_OPENEYE5_3, PO_C40_OPENEYE5, PO_C40_OPENEYE5,
	PO_C40_OPENEYE5_OPENEYE6_1, PO_C40_OPENEYE5_OPENEYE6_2, PO_C40_OPENEYE5_OPENEYE6_2, PO_C40_OPENEYE5_OPENEYE6_3, PO_C40_OPENEYE6, PO_C40_OPENEYE6, PO_C40_OPENEYE6_1, PO_C40_OPENEYE6_1,
	PO_C40_OPENEYE6_2, PO_C40_OPENEYE6_2, PO_C40_OPENEYE6_3, PO_C40_OPENEYE6_3, PO_C40_OPENEYE5, PO_C40_OPENEYE5, PO_C40_OPENEYE5_OPENEYE4_1, PO_C40_OPENEYE5_OPENEYE4_2,
	PO_C40_OPENEYE5_OPENEYE4_2, PO_C40_OPENEYE5_OPENEYE4_3, PO_C40_OPENEYE4, PO_C40_OPENEYE4, PO_C40_OPENEYE4, PO_C40_OPENEYE4, PO_C40_OPENEYE4, PO_C40_OPENEYE4,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//FOGRA_MOVE
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C40_OPENEYE3, PO_C40_OPENEYE3_OPENEYE4_1, PO_C40_OPENEYE3_OPENEYE4_2, PO_C40_OPENEYE3_OPENEYE4_3, PO_C40_OPENEYE4, PO_C40_OPENEYE4_OPENEYE5_1, PO_C40_OPENEYE4_OPENEYE5_2, PO_C40_OPENEYE4_OPENEYE5_3,
	PO_C40_OPENEYE5, PO_C40_OPENEYE5_OPENEYE6_1, PO_C40_OPENEYE5_OPENEYE6_2, PO_C40_OPENEYE5_OPENEYE6_3, PO_C40_OPENEYE6, PO_C40_OPENEYE6, PO_C40_OPENEYE6_1, PO_C40_OPENEYE6_1,
	PO_C40_OPENEYE6_2, PO_C40_OPENEYE6_2, PO_C40_OPENEYE6_3, PO_C40_OPENEYE6_3, PO_C40_OPENEYE5, PO_C40_OPENEYE5_OPENEYE4_1, PO_C40_OPENEYE5_OPENEYE4_2, PO_C40_OPENEYE5_OPENEYE4_3,
	PO_C40_OPENEYE4, PO_C40_OPENEYE4_OPENEYE3_1, PO_C40_OPENEYE4_OPENEYE3_2, PO_C40_OPENEYE4_OPENEYE3_3, PO_C40_OPENEYE3, PO_C40_OPENEYE3, PO_C40_OPENEYE3, PO_C40_OPENEYE3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//FOGRA_BULLET
	72,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C40_A0, PO_C40_A0_2, PO_C40_A1, PO_C40_A1_2, PO_C40_A2, PO_C40_A2_2, PO_C40_A0, PO_C40_A0_2,
	PO_C40_A1, PO_C40_A1_2, PO_C40_A2, PO_C40_A2_2, PO_C40_A0, PO_C40_A0_2, PO_C40_A1, PO_C40_A1_2,
	PO_C40_A2, PO_C40_A2_2, PO_C40_A0, PO_C40_A0_2, PO_C40_A1, PO_C40_A1_2, PO_C40_A2, PO_C40_A2_2,
	PO_C40_A0, PO_C40_A0_2, PO_C40_A1, PO_C40_A1_2, PO_C40_A2, PO_C40_A2_2, PO_C40_A0, PO_C40_A0_2,
	PO_C40_A1, PO_C40_A1_2, PO_C40_A2, PO_C40_A2_2, PO_C40_A0, PO_C40_A0_2, PO_C40_A1, PO_C40_A1_2,
	PO_C40_A2, PO_C40_A2_2, PO_C40_A0, PO_C40_A0_2, PO_C40_A1, PO_C40_A1_2, PO_C40_A2, PO_C40_A2_2,
	PO_C40_A0, PO_C40_A0_2, PO_C40_A1, PO_C40_A1_2, PO_C40_A2, PO_C40_A2_2, PO_C40_A0, PO_C40_A0_2,
	PO_C40_A1, PO_C40_A1_2, PO_C40_A2, PO_C40_A2_2, PO_C40_A0, PO_C40_A0_2, PO_C40_A1, PO_C40_A1_2,
	PO_C40_A2, PO_C40_A2_2, PO_C40_A0, PO_C40_A0_2, PO_C40_A1, PO_C40_A1_2, PO_C40_A2, PO_C40_A2_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//FOGRA_LASER
	108,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C40_OPENEYE2, PO_C40_OPENEYE2_OPENEYE1_1, PO_C40_OPENEYE2_OPENEYE1_2, PO_C40_OPENEYE2_OPENEYE1_3, PO_C40_OPENEYE1, PO_C40_OPENEYE1_1, PO_C40_OPENEYE1_2, PO_C40_OPENEYE1_3,
	PO_C40_OPENEYE2, PO_C40_OPENEYE2_LASER0_1, PO_C40_OPENEYE2_LASER0_2, PO_C40_OPENEYE2_LASER0_3, PO_C40_LASER0, PO_C40_LASER0_LASER1_1, PO_C40_LASER0_LASER1_2, PO_C40_LASER0_LASER1_3,
	PO_C40_LASER1, PO_C40_LASER1_LASER2_1, PO_C40_LASER1_LASER2_2, PO_C40_LASER1_LASER2_3, PO_C40_LASER2, PO_C40_LASER2_1, PO_C40_LASER2_2, PO_C40_LASER2_3,
	PO_C40_LASER3, PO_C40_LASER3_1, PO_C40_LASER3_2, PO_C40_LASER3_3, PO_C40_LASER4, PO_C40_LASER4, PO_C40_LASER4, PO_C40_LASER4_1,
	PO_C40_LASER4_1, PO_C40_LASER4_1, PO_C40_LASER4_2, PO_C40_LASER4_2, PO_C40_LASER4_2, PO_C40_LASER4_3, PO_C40_LASER4_3, PO_C40_LASER4_3,
	PO_C40_LASER5, PO_C40_LASER5, PO_C40_LASER5, PO_C40_LASER5_1, PO_C40_LASER5_1, PO_C40_LASER5_1, PO_C40_LASER5_2, PO_C40_LASER5_2,
	PO_C40_LASER5_2, PO_C40_LASER5_3, PO_C40_LASER5_3, PO_C40_LASER5_3, PO_C40_LASER6, PO_C40_LASER6, PO_C40_LASER6, PO_C40_LASER6_1,
	PO_C40_LASER6_1, PO_C40_LASER6_1, PO_C40_LASER6_2, PO_C40_LASER6_2, PO_C40_LASER6_2, PO_C40_LASER6_3, PO_C40_LASER6_3, PO_C40_LASER6_3,
	PO_C40_LASER7, PO_C40_LASER7, PO_C40_LASER7, PO_C40_LASER7_1, PO_C40_LASER7_1, PO_C40_LASER7_1, PO_C40_LASER7_2, PO_C40_LASER7_2,
	PO_C40_LASER7_2, PO_C40_LASER7_3, PO_C40_LASER7_3, PO_C40_LASER7_3, PO_C40_LASER8, PO_C40_LASER8_1, PO_C40_LASER8_2, PO_C40_LASER8_3,
	PO_C40_LASER9, PO_C40_LASER9_1, PO_C40_LASER9_2, PO_C40_LASER9_3, PO_C40_LASER1, PO_C40_LASER1_LASER0_1, PO_C40_LASER1_LASER0_2, PO_C40_LASER1_LASER0_3,
	PO_C40_LASER0, PO_C40_LASER0_OPENEYE0_1, PO_C40_LASER0_OPENEYE0_2, PO_C40_LASER0_OPENEYE0_3, PO_C40_OPENEYE0, PO_C40_OPENEYE0_1, PO_C40_OPENEYE0_2, PO_C40_OPENEYE0_3,
	PO_C40_OPENEYE1, PO_C40_OPENEYE1_1, PO_C40_OPENEYE1_2, PO_C40_OPENEYE1_3, PO_C40_OPENEYE2, PO_C40_OPENEYE2, PO_C40_OPENEYE2, PO_C40_OPENEYE2,
	PO_C40_OPENEYE2, PO_C40_OPENEYE2, PO_C40_OPENEYE2, PO_C40_OPENEYE2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//FOGRA_SUBFOGRA
	12,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C40_CIRCLE0, PO_C40_CIRCLE0_2, PO_C40_CIRCLE1, PO_C40_CIRCLE1_CIRCLE2_2, PO_C40_CIRCLE2, PO_C40_CIRCLE2_CIRCLE3_2, PO_C40_CIRCLE3, PO_C40_CIRCLE3_2,
	PO_C40_CIRCLE2, PO_C40_CIRCLE2_CIRCLE1_2, PO_C40_CIRCLE1, PO_C40_CIRCLE1_CIRCLE0_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//FOGRA_SUBFOGRA_ATTACK
	10,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C40_CIRCLE_A0, PO_C40_CIRCLE_A0_2, PO_C40_CIRCLE_A1, PO_C40_CIRCLE_A1_2, PO_C40_CIRCLE_A2, PO_C40_CIRCLE_A2_2, PO_C40_CIRCLE_A3, PO_C40_CIRCLE_A3_2,
	PO_C40_CIRCLE_A4, PO_C40_CIRCLE_A4_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c41mv[] = {
	//상태 데이터
	//DRAGON1_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C41_N0, PO_C41_N0_1, PO_C41_N0_2, PO_C41_N0_3, PO_C41_N1, PO_C41_N1_1, PO_C41_N1_2, PO_C41_N1_3,
	PO_C41_N2, PO_C41_N2_1, PO_C41_N2_2, PO_C41_N2_3, PO_C41_N3, PO_C41_N3_1, PO_C41_N3_2, PO_C41_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DRAGON1_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C41_W0, PO_C41_W0_1, PO_C41_W0_2, PO_C41_W0_3, PO_C41_W1, PO_C41_W1_1, PO_C41_W1_2, PO_C41_W1_3,
	PO_C41_W2, PO_C41_W2_1, PO_C41_W2_2, PO_C41_W2_3, PO_C41_W3, PO_C41_W3_1, PO_C41_W3_2, PO_C41_W3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DRAGON1_MOVE_FAST
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C41_W0, PO_C41_W0_2, PO_C41_W1, PO_C41_W1_2, PO_C41_W2, PO_C41_W2_2, PO_C41_W3, PO_C41_W3_2,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DRAGON1_ATTACK
	38,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C41_A0, PO_C41_A0_2, PO_C41_A1, PO_C41_A1, PO_C41_A1, PO_C41_A1, PO_C41_A1, PO_C41_A1,
	PO_C41_A1, PO_C41_A1_1, PO_C41_A1_1, PO_C41_A1_1, PO_C41_A1_1, PO_C41_A1_1, PO_C41_A1_1, PO_C41_A1_1,
	PO_C41_A1_2, PO_C41_A1_2, PO_C41_A1_2, PO_C41_A1_2, PO_C41_A1_2, PO_C41_A1_2, PO_C41_A1_2, PO_C41_A1_3,
	PO_C41_A1_3, PO_C41_A1_3, PO_C41_A1_3, PO_C41_A1_3, PO_C41_A1_3, PO_C41_A1_3, PO_C41_A2, PO_C41_A2_1,
	PO_C41_A2_2, PO_C41_A2_3, PO_C41_A3, PO_C41_A3, PO_C41_A3, PO_C41_A3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 5, 5,
	5, 5, 5, 5, 5, 5,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 50 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DRAGON1_FALL
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C41_A4, PO_C41_A4,	//상태 프레임별 모션
	5, 5,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DRAGON1_LANDINGREADY
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C41_A4, PO_C41_A4,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DRAGON1_LANDING
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C41_A5, PO_C41_A5_2, PO_C41_A6, PO_C41_A6_1, PO_C41_A6_2, PO_C41_A6_3, PO_C41_A1, PO_C41_A1,
	PO_C41_A1, PO_C41_A1, PO_C41_A1, PO_C41_A1, PO_C41_A1, PO_C41_A1, PO_C41_A1, PO_C41_A1,
	PO_C41_A1, PO_C41_A1, PO_C41_A1, PO_C41_A1, PO_C41_A1, PO_C41_A1, PO_C41_A1, PO_C41_A1,
	PO_C41_A1, PO_C41_A1, PO_C41_A1, PO_C41_A1, PO_C41_A1, PO_C41_A1, PO_C41_A1, PO_C41_A1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	DRAGON1_NEUTRAL,	DRAGON1_MOVE,	0,	0,	RANDOM,	30,
	DRAGON1_NEUTRAL,	DRAGON1_MOVE_FAST,	DISTANCE_CHECK_XY,	10 * 8 + 6,	0,	0,
	DRAGON1_NEUTRAL,	DRAGON1_ATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 6,	0,	0,
	DRAGON1_MOVE,	DRAGON1_MOVE_FAST,	DISTANCE_CHECK_XY,	10 * 8 + 6,	0,	0,
	DRAGON1_MOVE,	DRAGON1_ATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 6,	0,	0,
	DRAGON1_MOVE,	DRAGON1_NEUTRAL,	0,	0,	RANDOM,	30,
	DRAGON1_MOVE_FAST,	DRAGON1_NEUTRAL,	DISTANCE_OUT_XY,	10 * 8 + 6,	0,	0,
	DRAGON1_MOVE_FAST,	DRAGON1_ATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 6,	0,	0,
	DRAGON1_ATTACK,	DRAGON1_FALL,	0,	0,	0,	0,
	DRAGON1_LANDINGREADY,	DRAGON1_LANDING,	0,	0,	0,	0,
	DRAGON1_LANDING,	DRAGON1_NEUTRAL,	0,	0,	0,	0,
	-1,
};

const signed short c42mv[] = {
	//상태 데이터
	//DRAGON2_NEUTRAL
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C42_N0, PO_C42_N0, PO_C42_N0_1, PO_C42_N0_2, PO_C42_N0_2, PO_C42_N0_3, PO_C42_N1, PO_C42_N1,
	PO_C42_N1_1, PO_C42_N1_2, PO_C42_N1_2, PO_C42_N1_3, PO_C42_N2, PO_C42_N2, PO_C42_N2_1, PO_C42_N2_2,
	PO_C42_N2_2, PO_C42_N2_3, PO_C42_N3, PO_C42_N3, PO_C42_N3_1, PO_C42_N3_2, PO_C42_N3_2, PO_C42_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DRAGON2_ATTACK
	86,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C42_A0, PO_C42_A0, PO_C42_A0_1, PO_C42_A0_1, PO_C42_A0_2, PO_C42_A0_2, PO_C42_A0_3, PO_C42_A0_3,
	PO_C42_A1, PO_C42_A1, PO_C42_A1, PO_C42_A1, PO_C42_A1, PO_C42_A1, PO_C42_A1, PO_C42_A1,
	PO_C42_A1_1, PO_C42_A1_1, PO_C42_A1_1, PO_C42_A1_1, PO_C42_A1_1, PO_C42_A1_1, PO_C42_A1_1, PO_C42_A1_2,
	PO_C42_A1_2, PO_C42_A1_2, PO_C42_A1_2, PO_C42_A1_2, PO_C42_A1_2, PO_C42_A1_2, PO_C42_A1_2, PO_C42_A1_3,
	PO_C42_A1_3, PO_C42_A1_3, PO_C42_A1_3, PO_C42_A1_3, PO_C42_A1_3, PO_C42_A1_3, PO_C42_A2, PO_C42_A2_2,
	PO_C42_A3, PO_C42_A3, PO_C42_A3_1, PO_C42_A3_2, PO_C42_A3_2, PO_C42_A3_3, PO_C42_A4, PO_C42_A4_A3_1,
	PO_C42_A4_A3_2, PO_C42_A4_A3_3, PO_C42_A3, PO_C42_A3_1, PO_C42_A3_2, PO_C42_A3_3, PO_C42_A4, PO_C42_A4_A3_1,
	PO_C42_A4_A3_2, PO_C42_A4_A3_3, PO_C42_A3, PO_C42_A3_1, PO_C42_A3_2, PO_C42_A3_3, PO_C42_A4, PO_C42_A4_A3_1,
	PO_C42_A4_A3_2, PO_C42_A4_A3_3, PO_C42_A3, PO_C42_A3_1, PO_C42_A3_2, PO_C42_A3_3, PO_C42_A4, PO_C42_A4_A3_1,
	PO_C42_A4_A3_2, PO_C42_A4_A3_3, PO_C42_A3, PO_C42_A3_1, PO_C42_A3_2, PO_C42_A3_3, PO_C42_A4, PO_C42_A4_A5_1,
	PO_C42_A4_A5_2, PO_C42_A4_A5_3, PO_C42_A5, PO_C42_A5, PO_C42_A5, PO_C42_A5,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	DRAGON2_NEUTRAL,	DRAGON2_ATTACK,	DISTANCE_CHECK_XY,	10 * 8 + 6,	0,	0,
	DRAGON2_ATTACK,	DRAGON2_NEUTRAL,	0,	0,	0,	0,
	-1,
};

const signed short c43mv[] = {
	//상태 데이터
	//BAHAMUT_NEUTRAL
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C43_N0, PO_C43_N0, PO_C43_N0_1, PO_C43_N0_1, PO_C43_N0_2, PO_C43_N0_2, PO_C43_N0_3, PO_C43_N0_3,
	PO_C43_N1, PO_C43_N1, PO_C43_N1_1, PO_C43_N1_1, PO_C43_N1_2, PO_C43_N1_2, PO_C43_N1_3, PO_C43_N1_3,
	PO_C43_N2, PO_C43_N2, PO_C43_N2_1, PO_C43_N2_1, PO_C43_N2_2, PO_C43_N2_2, PO_C43_N2_3, PO_C43_N2_3,
	PO_C43_N3, PO_C43_N3, PO_C43_N3_1, PO_C43_N3_1, PO_C43_N3_2, PO_C43_N3_2, PO_C43_N3_3, PO_C43_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BAHAMUT_FIRE
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C43_FIREATTACK0, PO_C43_FIREATTACK0, PO_C43_FIREATTACK0_1, PO_C43_FIREATTACK0_2, PO_C43_FIREATTACK0_2, PO_C43_FIREATTACK0_3, PO_C43_FIREATTACK1, PO_C43_FIREATTACK1,
	PO_C43_FIREATTACK1_1, PO_C43_FIREATTACK1_1, PO_C43_FIREATTACK1_2, PO_C43_FIREATTACK1_2, PO_C43_FIREATTACK1_3, PO_C43_FIREATTACK1_3, PO_C43_FIREATTACK2, PO_C43_FIREATTACK2,
	PO_C43_FIREATTACK2_1, PO_C43_FIREATTACK2_1, PO_C43_FIREATTACK2_2, PO_C43_FIREATTACK2_2, PO_C43_FIREATTACK2_3, PO_C43_FIREATTACK2_3, PO_C43_FIREATTACK3, PO_C43_FIREATTACK3_1,
	PO_C43_FIREATTACK3_2, PO_C43_FIREATTACK3_3, PO_C43_FIREATTACK4, PO_C43_FIREATTACK4, PO_C43_FIREATTACK4_1, PO_C43_FIREATTACK4_2, PO_C43_FIREATTACK4_2, PO_C43_FIREATTACK4_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BAHAMUT_BULLET
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C43_FIREATTACK0, PO_C43_FIREATTACK0, PO_C43_FIREATTACK0_1, PO_C43_FIREATTACK0_2, PO_C43_FIREATTACK0_2, PO_C43_FIREATTACK0_3, PO_C43_FIREATTACK1, PO_C43_FIREATTACK1,
	PO_C43_FIREATTACK1_1, PO_C43_FIREATTACK1_1, PO_C43_FIREATTACK1_2, PO_C43_FIREATTACK1_2, PO_C43_FIREATTACK1_3, PO_C43_FIREATTACK1_3, PO_C43_FIREATTACK2, PO_C43_FIREATTACK2,
	PO_C43_FIREATTACK2_1, PO_C43_FIREATTACK2_1, PO_C43_FIREATTACK2_2, PO_C43_FIREATTACK2_2, PO_C43_FIREATTACK2_3, PO_C43_FIREATTACK2_3, PO_C43_FIREATTACK3, PO_C43_FIREATTACK3_1,
	PO_C43_FIREATTACK3_2, PO_C43_FIREATTACK3_3, PO_C43_FIREATTACK4, PO_C43_FIREATTACK4, PO_C43_FIREATTACK4_1, PO_C43_FIREATTACK4_2, PO_C43_FIREATTACK4_2, PO_C43_FIREATTACK4_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BAHAMUT_ATTACK
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C43_FIREATTACK0, PO_C43_FIREATTACK0, PO_C43_FIREATTACK0_1, PO_C43_FIREATTACK0_2, PO_C43_FIREATTACK0_2, PO_C43_FIREATTACK0_3, PO_C43_FIREATTACK1, PO_C43_FIREATTACK1,
	PO_C43_FIREATTACK1_1, PO_C43_FIREATTACK1_1, PO_C43_FIREATTACK1_2, PO_C43_FIREATTACK1_2, PO_C43_FIREATTACK1_3, PO_C43_FIREATTACK1_3, PO_C43_FIREATTACK2, PO_C43_FIREATTACK2,
	PO_C43_FIREATTACK2_1, PO_C43_FIREATTACK2_1, PO_C43_FIREATTACK2_2, PO_C43_FIREATTACK2_2, PO_C43_FIREATTACK2_3, PO_C43_FIREATTACK2_3, PO_C43_FIREATTACK3, PO_C43_FIREATTACK3_1,
	PO_C43_FIREATTACK3_2, PO_C43_FIREATTACK3_3, PO_C43_FIREATTACK4, PO_C43_FIREATTACK4, PO_C43_FIREATTACK4_1, PO_C43_FIREATTACK4_2, PO_C43_FIREATTACK4_2, PO_C43_FIREATTACK4_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BAHAMUT_EVENT
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C43_EVENT0, PO_C43_EVENT0, PO_C43_EVENT0_1, PO_C43_EVENT0_1, PO_C43_EVENT0_2, PO_C43_EVENT0_2, PO_C43_EVENT0_3, PO_C43_EVENT0_3,
	PO_C43_EVENT1, PO_C43_EVENT1, PO_C43_EVENT1_1, PO_C43_EVENT1_1, PO_C43_EVENT1_2, PO_C43_EVENT1_2, PO_C43_EVENT1_3, PO_C43_EVENT1_3,
	PO_C43_EVENT2, PO_C43_EVENT2, PO_C43_EVENT2_1, PO_C43_EVENT2_1, PO_C43_EVENT2_2, PO_C43_EVENT2_2, PO_C43_EVENT2_3, PO_C43_EVENT2_3,
	PO_C43_EVENT3, PO_C43_EVENT3, PO_C43_EVENT3_1, PO_C43_EVENT3_1, PO_C43_EVENT3_2, PO_C43_EVENT3_2, PO_C43_EVENT3_3, PO_C43_EVENT3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BAHAMUT_EVENT2
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C43_EVENT4, PO_C43_EVENT4, PO_C43_EVENT4_1, PO_C43_EVENT4_1, PO_C43_EVENT4_2, PO_C43_EVENT4_2, PO_C43_EVENT4_3, PO_C43_EVENT4_3,
	PO_C43_EVENT5, PO_C43_EVENT5, PO_C43_EVENT5_1, PO_C43_EVENT5_1, PO_C43_EVENT5_2, PO_C43_EVENT5_2, PO_C43_EVENT5_3, PO_C43_EVENT5_3,
	PO_C43_EVENT6, PO_C43_EVENT6, PO_C43_EVENT6_1, PO_C43_EVENT6_1, PO_C43_EVENT6_2, PO_C43_EVENT6_2, PO_C43_EVENT6_3, PO_C43_EVENT6_3,
	PO_C43_EVENT7, PO_C43_EVENT7, PO_C43_EVENT7_1, PO_C43_EVENT7_1, PO_C43_EVENT7_2, PO_C43_EVENT7_2, PO_C43_EVENT7_3, PO_C43_EVENT7_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BAHAMUT_EVENT_NEUTRAL
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C43_EVENT_N0, PO_C43_EVENT_N0, PO_C43_EVENT_N0_1, PO_C43_EVENT_N0_1, PO_C43_EVENT_N0_2, PO_C43_EVENT_N0_2, PO_C43_EVENT_N0_3, PO_C43_EVENT_N0_3,
	PO_C43_EVENT_N1, PO_C43_EVENT_N1, PO_C43_EVENT_N1_1, PO_C43_EVENT_N1_1, PO_C43_EVENT_N1_2, PO_C43_EVENT_N1_2, PO_C43_EVENT_N1_3, PO_C43_EVENT_N1_3,
	PO_C43_EVENT_N2, PO_C43_EVENT_N2, PO_C43_EVENT_N2_1, PO_C43_EVENT_N2_1, PO_C43_EVENT_N2_2, PO_C43_EVENT_N2_2, PO_C43_EVENT_N2_3, PO_C43_EVENT_N2_3,
	PO_C43_EVENT_N3, PO_C43_EVENT_N3, PO_C43_EVENT_N3_1, PO_C43_EVENT_N3_1, PO_C43_EVENT_N3_2, PO_C43_EVENT_N3_2, PO_C43_EVENT_N3_3, PO_C43_EVENT_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BAHAMUT_EVENT_FIRE
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C43_EVENT_FIRE0, PO_C43_EVENT_FIRE0_2, PO_C43_EVENT_FIRE1, PO_C43_EVENT_FIRE1_EVENT_FIRE4_1, PO_C43_EVENT_FIRE1_EVENT_FIRE4_2, PO_C43_EVENT_FIRE1_EVENT_FIRE4_3, PO_C43_EVENT_FIRE4, PO_C43_EVENT_FIRE4_2,
	PO_C43_EVENT_FIRE2, PO_C43_EVENT_FIRE2, PO_C43_EVENT_FIRE2_1, PO_C43_EVENT_FIRE2_2, PO_C43_EVENT_FIRE2_2, PO_C43_EVENT_FIRE2_3, PO_C43_EVENT_FIRE3, PO_C43_EVENT_FIRE3,
	PO_C43_EVENT_FIRE3_EVENT_FIRE2_1, PO_C43_EVENT_FIRE3_EVENT_FIRE2_2, PO_C43_EVENT_FIRE3_EVENT_FIRE2_2, PO_C43_EVENT_FIRE3_EVENT_FIRE2_3, PO_C43_EVENT_FIRE2, PO_C43_EVENT_FIRE2, PO_C43_EVENT_FIRE2_1, PO_C43_EVENT_FIRE2_2,
	PO_C43_EVENT_FIRE2_2, PO_C43_EVENT_FIRE2_3, PO_C43_EVENT_FIRE3, PO_C43_EVENT_FIRE3_EVENT_FIRE1_2, PO_C43_EVENT_FIRE1, PO_C43_EVENT_FIRE1_EVENT_FIRE0_2, PO_C43_EVENT_FIRE0, PO_C43_EVENT_FIRE0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BAHAMUT_HEAD_NEUTRAL
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C43_HEAD_N0, PO_C43_HEAD_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BAHAMUT_HEAD_FIRE
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C43_HEAD_N0, PO_C43_HEAD_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BAHAMUT_HEAD_BULLET
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C43_HEAD_N0, PO_C43_HEAD_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BAHAMUT_HEAD_ATTACK
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C43_HEAD2, PO_C43_HEAD2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//BAHAMUT_NECK
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C43_NECK_N0, PO_C43_NECK_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c44mv[] = {
	//상태 데이터
	//CASTLE1_NEUTRAL
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C44_N0, PO_C44_N0, PO_C44_N0_N1_1, PO_C44_N0_N1_2, PO_C44_N0_N1_2, PO_C44_N0_N1_3, PO_C44_N1, PO_C44_N1,
	PO_C44_N1_N2_1, PO_C44_N1_N2_2, PO_C44_N1_N2_2, PO_C44_N1_N2_3, PO_C44_N2, PO_C44_N2, PO_C44_N2_1, PO_C44_N2_2,
	PO_C44_N2_2, PO_C44_N2_3, PO_C44_N3, PO_C44_N3, PO_C44_N3_1, PO_C44_N3_2, PO_C44_N3_2, PO_C44_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLE1_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C44_W0, PO_C44_W0_1, PO_C44_W0_2, PO_C44_W0_3, PO_C44_W1, PO_C44_W1_1, PO_C44_W1_2, PO_C44_W1_3,
	PO_C44_W2, PO_C44_W2_1, PO_C44_W2_2, PO_C44_W2_3, PO_C44_W3, PO_C44_W3_1, PO_C44_W3_2, PO_C44_W3_3,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLE1_DISAPPEAR
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C44_WARP0, PO_C44_WARP0, PO_C44_WARP0_1, PO_C44_WARP0_1, PO_C44_WARP0_2, PO_C44_WARP0_2, PO_C44_WARP0_3, PO_C44_WARP0_3,
	PO_C44_WARP1, PO_C44_WARP1_1, PO_C44_WARP1_2, PO_C44_WARP1_3, PO_C44_WARP2, PO_C44_WARP2_1, PO_C44_WARP2_2, PO_C44_WARP2_3,
	PO_C44_WARP3, PO_C44_WARP3_1, PO_C44_WARP3_2, PO_C44_WARP3_3, PO_C44_WARP4, PO_C44_WARP4_1, PO_C44_WARP4_2, PO_C44_WARP4_3,
	PO_C44_WARP5, PO_C44_WARP5_1, PO_C44_WARP5_2, PO_C44_WARP5_3, PO_C44_WARP6, PO_C44_WARP6_1, PO_C44_WARP6_2, PO_C44_WARP6_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLE1_APPEAR
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C44_APPEAR0, PO_C44_APPEAR0_1, PO_C44_APPEAR0_2, PO_C44_APPEAR0_3, PO_C44_APPEAR1, PO_C44_APPEAR1_1, PO_C44_APPEAR1_2, PO_C44_APPEAR1_3,
	PO_C44_N0, PO_C44_N0_N1_1, PO_C44_N0_N1_2, PO_C44_N0_N1_3, PO_C44_N1, PO_C44_N1_APPEAR0_1, PO_C44_N1_APPEAR0_2, PO_C44_N1_APPEAR0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLE1_ATTACK
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C44_A0, PO_C44_A0, PO_C44_A0, PO_C44_A0_1, PO_C44_A0_1, PO_C44_A0_1, PO_C44_A0_2, PO_C44_A0_2,
	PO_C44_A0_2, PO_C44_A0_3, PO_C44_A0_3, PO_C44_A0_3, PO_C44_A1, PO_C44_A1_1, PO_C44_A1_2, PO_C44_A1_3,
	PO_C44_A2, PO_C44_A2_2, PO_C44_A3, PO_C44_A3_1, PO_C44_A3_2, PO_C44_A3_3, PO_C44_A4, PO_C44_A4,
	PO_C44_A4_1, PO_C44_A4_1, PO_C44_A4_2, PO_C44_A4_2, PO_C44_A4_3, PO_C44_A4_3, PO_C44_N0, PO_C44_N0_A0_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c45mv[] = {
	//상태 데이터
	//CASTLE2_NEUTRAL
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C45_N0, PO_C45_N0, PO_C45_N0_1, PO_C45_N0_2, PO_C45_N0_2, PO_C45_N0_3, PO_C45_N1, PO_C45_N1,
	PO_C45_N1_1, PO_C45_N1_2, PO_C45_N1_2, PO_C45_N1_3, PO_C45_N2, PO_C45_N2, PO_C45_N2_1, PO_C45_N2_2,
	PO_C45_N2_2, PO_C45_N2_3, PO_C45_N3, PO_C45_N3, PO_C45_N3_1, PO_C45_N3_2, PO_C45_N3_2, PO_C45_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLE2_MOVE
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C45_W0, PO_C45_W0_1, PO_C45_W0_2, PO_C45_W0_3, PO_C45_W1, PO_C45_W1_1, PO_C45_W1_2, PO_C45_W1_3,
	PO_C45_W2, PO_C45_W2_1, PO_C45_W2_2, PO_C45_W2_3, PO_C45_W3, PO_C45_W3_1, PO_C45_W3_2, PO_C45_W3_3,
	PO_C45_W4, PO_C45_W4_1, PO_C45_W4_2, PO_C45_W4_3, PO_C45_W5, PO_C45_W5_1, PO_C45_W5_2, PO_C45_W5_3,	//상태 프레임별 모션
	1, 1, 0 * _2X, 0 * _2X, 1, 1, 0 * _2X, 0 * _2X,
	1, 1, 0 * _2X, 0 * _2X, 1, 1, 0 * _2X, 0 * _2X,
	1, 1, 0 * _2X, 0 * _2X, 1, 1, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLE2_ATTACK
	80,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C45_A0, PO_C45_A0_1, PO_C45_A0_2, PO_C45_A0_3, PO_C45_A1, PO_C45_A1_1, PO_C45_A1_2, PO_C45_A1_3,
	PO_C45_A2, PO_C45_A2, PO_C45_A2, PO_C45_A2, PO_C45_A2, PO_C45_A2, PO_C45_A2, PO_C45_A2,
	PO_C45_A2, PO_C45_A2, PO_C45_A2, PO_C45_A2_1, PO_C45_A2_1, PO_C45_A2_1, PO_C45_A2_1, PO_C45_A2_1,
	PO_C45_A2_1, PO_C45_A2_1, PO_C45_A2_1, PO_C45_A2_1, PO_C45_A2_1, PO_C45_A2_2, PO_C45_A2_2, PO_C45_A2_2,
	PO_C45_A2_2, PO_C45_A2_2, PO_C45_A2_2, PO_C45_A2_2, PO_C45_A2_2, PO_C45_A2_2, PO_C45_A2_2, PO_C45_A2_2,
	PO_C45_A2_3, PO_C45_A2_3, PO_C45_A2_3, PO_C45_A2_3, PO_C45_A2_3, PO_C45_A2_3, PO_C45_A2_3, PO_C45_A2_3,
	PO_C45_A2_3, PO_C45_A2_3, PO_C45_A3, PO_C45_A3, PO_C45_A3_1, PO_C45_A3_2, PO_C45_A3_2, PO_C45_A3_3,
	PO_C45_A4, PO_C45_A4, PO_C45_A4_1, PO_C45_A4_2, PO_C45_A4_2, PO_C45_A4_3, PO_C45_A5, PO_C45_A5_2,
	PO_C45_A6, PO_C45_A6, PO_C45_A6, PO_C45_A6, PO_C45_A6, PO_C45_A6, PO_C45_A6, PO_C45_A6,
	PO_C45_A6, PO_C45_A6, PO_C45_A6, PO_C45_A6, PO_C45_A6, PO_C45_A6, PO_C45_A6, PO_C45_A6,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	CASTLE2_NEUTRAL,	CASTLE2_MOVE,	0,	0,	RANDOM,	30,
	CASTLE2_NEUTRAL,	CASTLE2_ATTACK,	DISTANCE_CHECK_XY,	8 * 8 + 6,	0,	0,
	CASTLE2_MOVE,	CASTLE2_ATTACK,	DISTANCE_CHECK_XY,	8 * 8 + 6,	0,	0,
	CASTLE2_MOVE,	CASTLE2_NEUTRAL,	0,	0,	RANDOM,	30,
	CASTLE2_ATTACK,	CASTLE2_NEUTRAL,	0,	0,	0,	0,
	-1,
};

const signed short c46mv[] = {
	//상태 데이터
	//SPACE1_NEUTRAL
	48,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C46_A0, PO_C46_A0, PO_C46_A0_1, PO_C46_A0_1, PO_C46_A0_2, PO_C46_A0_2, PO_C46_A0_3, PO_C46_A0_3,
	PO_C46_A1, PO_C46_A1, PO_C46_A1_1, PO_C46_A1_1, PO_C46_A1_2, PO_C46_A1_2, PO_C46_A1_3, PO_C46_A1_3,
	PO_C46_A2, PO_C46_A2, PO_C46_A2_1, PO_C46_A2_1, PO_C46_A2_2, PO_C46_A2_2, PO_C46_A2_3, PO_C46_A2_3,
	PO_C46_A3, PO_C46_A3, PO_C46_A3_1, PO_C46_A3_1, PO_C46_A3_2, PO_C46_A3_2, PO_C46_A3_3, PO_C46_A3_3,
	PO_C46_A4, PO_C46_A4, PO_C46_A4_1, PO_C46_A4_1, PO_C46_A4_2, PO_C46_A4_2, PO_C46_A4_3, PO_C46_A4_3,
	PO_C46_A5, PO_C46_A5, PO_C46_A5_1, PO_C46_A5_1, PO_C46_A5_2, PO_C46_A5_2, PO_C46_A5_3, PO_C46_A5_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SPACE1_MOVE
	12,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C46_A0, PO_C46_A0_2, PO_C46_A1, PO_C46_A1_2, PO_C46_A2, PO_C46_A2_2, PO_C46_A3, PO_C46_A3_2,
	PO_C46_A4, PO_C46_A4_2, PO_C46_A5, PO_C46_A5_2,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SPACE1_ATTACK
	12,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C46_A0, PO_C46_A0_2, PO_C46_A1, PO_C46_A1_2, PO_C46_A2, PO_C46_A2_2, PO_C46_A3, PO_C46_A3_2,
	PO_C46_A4, PO_C46_A4_2, PO_C46_A5, PO_C46_A5_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	SPACE1_NEUTRAL,	SPACE1_ATTACK,	ATTACK_CHECK,	0,	0,	0,
	SPACE1_NEUTRAL,	SPACE1_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 4,	0,	0,
	SPACE1_NEUTRAL,	SPACE1_MOVE,	DIR_DIFFER_PLAYER,	0,	0,	0,
	SPACE1_MOVE,	SPACE1_ATTACK,	ATTACK_CHECK,	0,	0,	0,
	SPACE1_MOVE,	SPACE1_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 4,	0,	0,
	SPACE1_MOVE,	SPACE1_NEUTRAL,	DIR_DIFFER_PLAYER,	0,	0,	0,
	SPACE1_ATTACK,	SPACE1_NEUTRAL,	COMPARE_FRAME,	10,	0,	0,
	-1,
};

const signed short c47mv[] = {
	//상태 데이터
	64,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C47_N0, PO_C47_N0, PO_C47_N0_1, PO_C47_N0_1, PO_C47_N0_2, PO_C47_N0_2, PO_C47_N0_3, PO_C47_N0_3,
	PO_C47_N1, PO_C47_N1, PO_C47_N1_1, PO_C47_N1_1, PO_C47_N1_2, PO_C47_N1_2, PO_C47_N1_3, PO_C47_N1_3,
	PO_C47_N2, PO_C47_N2, PO_C47_N2_1, PO_C47_N2_1, PO_C47_N2_2, PO_C47_N2_2, PO_C47_N2_3, PO_C47_N2_3,
	PO_C47_N3, PO_C47_N3, PO_C47_N3_1, PO_C47_N3_1, PO_C47_N3_2, PO_C47_N3_2, PO_C47_N3_3, PO_C47_N3_3,
	PO_C47_N4, PO_C47_N4, PO_C47_N4_1, PO_C47_N4_1, PO_C47_N4_2, PO_C47_N4_2, PO_C47_N4_3, PO_C47_N4_3,
	PO_C47_N5, PO_C47_N5, PO_C47_N5_1, PO_C47_N5_1, PO_C47_N5_2, PO_C47_N5_2, PO_C47_N5_3, PO_C47_N5_3,
	PO_C47_N6, PO_C47_N6, PO_C47_N6_1, PO_C47_N6_1, PO_C47_N6_2, PO_C47_N6_2, PO_C47_N6_3, PO_C47_N6_3,
	PO_C47_N7, PO_C47_N7, PO_C47_N7_1, PO_C47_N7_1, PO_C47_N7_2, PO_C47_N7_2, PO_C47_N7_3, PO_C47_N7_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C47_W0, PO_C47_W0_2, PO_C47_W1, PO_C47_W1_W2_2, PO_C47_W2, PO_C47_W2_2, PO_C47_W1, PO_C47_W1_W0_2,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	60,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C47_A0, PO_C47_A0_2, PO_C47_A1, PO_C47_A1_2, PO_C47_A2, PO_C47_A2, PO_C47_A2, PO_C47_A2,
	PO_C47_A2, PO_C47_A2_1, PO_C47_A2_1, PO_C47_A2_1, PO_C47_A2_1, PO_C47_A2_1, PO_C47_A2_2, PO_C47_A2_2,
	PO_C47_A2_2, PO_C47_A2_2, PO_C47_A2_2, PO_C47_A2_3, PO_C47_A2_3, PO_C47_A2_3, PO_C47_A2_3, PO_C47_A2_3,
	PO_C47_A3, PO_C47_A3_2, PO_C47_A4, PO_C47_A4_2, PO_C47_A5, PO_C47_A5_2, PO_C47_A6, PO_C47_A6_2,
	PO_C47_A7, PO_C47_A7_2, PO_C47_A8, PO_C47_A8_2, PO_C47_A9, PO_C47_A9_2, PO_C47_A10, PO_C47_A10_2,
	PO_C47_A11, PO_C47_A11, PO_C47_A11, PO_C47_A11, PO_C47_A11, PO_C47_A11, PO_C47_A11, PO_C47_A11,
	PO_C47_A11, PO_C47_A11, PO_C47_A11, PO_C47_A11, PO_C47_A11, PO_C47_A11, PO_C47_A11, PO_C47_A11,
	PO_C47_A11, PO_C47_A11, PO_C47_A11, PO_C47_A11,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	SPACE2_NEUTRAL,	SPACE2_ATTACK,	ATTACK_CHECK,	0,	0,	0,
	SPACE2_NEUTRAL,	SPACE2_ATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 6,	0,	0,
	SPACE2_NEUTRAL,	SPACE2_MOVE,	0,	0,	RANDOM,	30,
	SPACE2_MOVE,	SPACE2_ATTACK,	ATTACK_CHECK,	0,	0,	0,
	SPACE2_MOVE,	SPACE2_ATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 6,	0,	0,
	SPACE2_MOVE,	SPACE2_NEUTRAL,	0,	0,	RANDOM,	30,
	SPACE2_ATTACK,	SPACE2_NEUTRAL,	0,	0,	0,	0,
	-1,
};

const signed short c48mv[] = {
	//상태 데이터
	//CASTLEBOSS1_BODY_NEUTRAL
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C48_BODY_EYE0, PO_C48_BODY_EYE0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS1_BODY_BULLET
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C48_BODY_EYE0, PO_C48_BODY_EYE0_2, PO_C48_BODY_EYE1, PO_C48_BODY_EYE1_BODY_EYE2_2, PO_C48_BODY_EYE2, PO_C48_BODY_EYE2_BODY_EYE3_2, PO_C48_BODY_EYE3, PO_C48_BODY_EYE3_BODY_A0_2,
	PO_C48_BODY_A0, PO_C48_BODY_A0_2, PO_C48_BODY_A1, PO_C48_BODY_A1_2, PO_C48_BODY_A2, PO_C48_BODY_A2_2, PO_C48_BODY_A3, PO_C48_BODY_A3_BODY_EYE3_2,
	PO_C48_BODY_EYE3, PO_C48_BODY_EYE3_BODY_EYE2_2, PO_C48_BODY_EYE2, PO_C48_BODY_EYE2_BODY_EYE1_2, PO_C48_BODY_EYE1, PO_C48_BODY_EYE1_BODY_EYE0_2, PO_C48_BODY_EYE0, PO_C48_BODY_EYE0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS1_BODY_MOVEWAIT
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C48_BODY_EYE0, PO_C48_BODY_EYE0_2, PO_C48_BODY_EYE1, PO_C48_BODY_EYE1_BODY_EYE2_2, PO_C48_BODY_EYE2, PO_C48_BODY_EYE2_BODY_EYE3_2, PO_C48_BODY_EYE3, PO_C48_BODY_EYE3_BODY_A0_2,
	PO_C48_BODY_A0, PO_C48_BODY_A0_2, PO_C48_BODY_A1, PO_C48_BODY_A1_2, PO_C48_BODY_A2, PO_C48_BODY_A2_2, PO_C48_BODY_A3, PO_C48_BODY_A3_BODY_A0_2,
	PO_C48_BODY_A0, PO_C48_BODY_A0_2, PO_C48_BODY_A1, PO_C48_BODY_A1_2, PO_C48_BODY_A2, PO_C48_BODY_A2_2, PO_C48_BODY_A3, PO_C48_BODY_A3_BODY_EYE3_2,
	PO_C48_BODY_EYE3, PO_C48_BODY_EYE3_BODY_EYE2_2, PO_C48_BODY_EYE2, PO_C48_BODY_EYE2_BODY_EYE1_2, PO_C48_BODY_EYE1, PO_C48_BODY_EYE1_BODY_EYE0_2, PO_C48_BODY_EYE0, PO_C48_BODY_EYE0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS1_BODY_BOMB
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C48_BODY_EYE0, PO_C48_BODY_EYE0_2, PO_C48_BODY_EYE1, PO_C48_BODY_EYE1_BODY_EYE2_2, PO_C48_BODY_EYE2, PO_C48_BODY_EYE2_BODY_EYE3_2, PO_C48_BODY_EYE3, PO_C48_BODY_EYE3,
	PO_C48_BODY_EYE3, PO_C48_BODY_EYE3_BODY_EYE2_1, PO_C48_BODY_EYE3_BODY_EYE2_1, PO_C48_BODY_EYE3_BODY_EYE2_1, PO_C48_BODY_EYE3_BODY_EYE2_2, PO_C48_BODY_EYE3_BODY_EYE2_2, PO_C48_BODY_EYE3_BODY_EYE2_2, PO_C48_BODY_EYE3_BODY_EYE2_3,
	PO_C48_BODY_EYE3_BODY_EYE2_3, PO_C48_BODY_EYE3_BODY_EYE2_3, PO_C48_BODY_EYE2, PO_C48_BODY_EYE2_BODY_EYE1_2, PO_C48_BODY_EYE1, PO_C48_BODY_EYE1_BODY_EYE0_2, PO_C48_BODY_EYE0, PO_C48_BODY_EYE0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS1_UARM_NEUTRAL
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C48_ARM0_EYE0, PO_C48_ARM0_EYE0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS1_UARM_BULLET
	80,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C48_ARM0_EYE0, PO_C48_ARM0_EYE0_2, PO_C48_ARM0_EYE1, PO_C48_ARM0_EYE1_ARM0_EYE2_2, PO_C48_ARM0_EYE2, PO_C48_ARM0_EYE2_ARM0_EYE3_2, PO_C48_ARM0_EYE3, PO_C48_ARM0_EYE3,
	PO_C48_ARM0_EYE3, PO_C48_ARM0_EYE3, PO_C48_ARM0_EYE3, PO_C48_ARM0_EYE3, PO_C48_ARM0_EYE3, PO_C48_ARM0_EYE3, PO_C48_ARM0_EYE3, PO_C48_ARM0_EYE3_ARM0_A0_1,
	PO_C48_ARM0_EYE3_ARM0_A0_1, PO_C48_ARM0_EYE3_ARM0_A0_1, PO_C48_ARM0_EYE3_ARM0_A0_1, PO_C48_ARM0_EYE3_ARM0_A0_1, PO_C48_ARM0_EYE3_ARM0_A0_1, PO_C48_ARM0_EYE3_ARM0_A0_1, PO_C48_ARM0_EYE3_ARM0_A0_1, PO_C48_ARM0_EYE3_ARM0_A0_2,
	PO_C48_ARM0_EYE3_ARM0_A0_2, PO_C48_ARM0_EYE3_ARM0_A0_2, PO_C48_ARM0_EYE3_ARM0_A0_2, PO_C48_ARM0_EYE3_ARM0_A0_2, PO_C48_ARM0_EYE3_ARM0_A0_2, PO_C48_ARM0_EYE3_ARM0_A0_2, PO_C48_ARM0_EYE3_ARM0_A0_2, PO_C48_ARM0_EYE3_ARM0_A0_2,
	PO_C48_ARM0_EYE3_ARM0_A0_3, PO_C48_ARM0_EYE3_ARM0_A0_3, PO_C48_ARM0_EYE3_ARM0_A0_3, PO_C48_ARM0_EYE3_ARM0_A0_3, PO_C48_ARM0_EYE3_ARM0_A0_3, PO_C48_ARM0_EYE3_ARM0_A0_3, PO_C48_ARM0_EYE3_ARM0_A0_3, PO_C48_ARM0_EYE3_ARM0_A0_3,
	PO_C48_ARM0_A0, PO_C48_ARM0_A0_ARM0_A1_2, PO_C48_ARM0_A1, PO_C48_ARM0_A1_2, PO_C48_ARM0_A2, PO_C48_ARM0_A2_ARM0_A0_2, PO_C48_ARM0_A0, PO_C48_ARM0_A0_ARM0_EYE3_2,
	PO_C48_ARM0_EYE3, PO_C48_ARM0_EYE3, PO_C48_ARM0_EYE3, PO_C48_ARM0_EYE3, PO_C48_ARM0_EYE3, PO_C48_ARM0_EYE3, PO_C48_ARM0_EYE3, PO_C48_ARM0_EYE3_ARM0_EYE2_1,
	PO_C48_ARM0_EYE3_ARM0_EYE2_1, PO_C48_ARM0_EYE3_ARM0_EYE2_1, PO_C48_ARM0_EYE3_ARM0_EYE2_1, PO_C48_ARM0_EYE3_ARM0_EYE2_1, PO_C48_ARM0_EYE3_ARM0_EYE2_1, PO_C48_ARM0_EYE3_ARM0_EYE2_2, PO_C48_ARM0_EYE3_ARM0_EYE2_2, PO_C48_ARM0_EYE3_ARM0_EYE2_2,
	PO_C48_ARM0_EYE3_ARM0_EYE2_2, PO_C48_ARM0_EYE3_ARM0_EYE2_2, PO_C48_ARM0_EYE3_ARM0_EYE2_2, PO_C48_ARM0_EYE3_ARM0_EYE2_2, PO_C48_ARM0_EYE3_ARM0_EYE2_3, PO_C48_ARM0_EYE3_ARM0_EYE2_3, PO_C48_ARM0_EYE3_ARM0_EYE2_3, PO_C48_ARM0_EYE3_ARM0_EYE2_3,
	PO_C48_ARM0_EYE3_ARM0_EYE2_3, PO_C48_ARM0_EYE3_ARM0_EYE2_3, PO_C48_ARM0_EYE2, PO_C48_ARM0_EYE2_ARM0_EYE1_2, PO_C48_ARM0_EYE1, PO_C48_ARM0_EYE1_ARM0_EYE0_2, PO_C48_ARM0_EYE0, PO_C48_ARM0_EYE0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS1_UARM_MOVE
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C48_ARM0_EYE0, PO_C48_ARM0_EYE0_2, PO_C48_ARM0_EYE1, PO_C48_ARM0_EYE1_ARM0_EYE2_2, PO_C48_ARM0_EYE2, PO_C48_ARM0_EYE2_ARM0_EYE3_2, PO_C48_ARM0_EYE3, PO_C48_ARM0_EYE3_ARM0_A0_2,
	PO_C48_ARM0_A0, PO_C48_ARM0_A0_ARM0_A1_2, PO_C48_ARM0_A1, PO_C48_ARM0_A1_2, PO_C48_ARM0_A2, PO_C48_ARM0_A2_ARM0_A3_2, PO_C48_ARM0_A3, PO_C48_ARM0_A3,
	PO_C48_ARM0_A3, PO_C48_ARM0_A3_1, PO_C48_ARM0_A3_1, PO_C48_ARM0_A3_2, PO_C48_ARM0_A3_2, PO_C48_ARM0_A3_2, PO_C48_ARM0_A3_3, PO_C48_ARM0_A3_3,
	PO_C48_ARM0_A4, PO_C48_ARM0_A4_2, PO_C48_ARM0_A5, PO_C48_ARM0_A5_2, PO_C48_ARM0_A6, PO_C48_ARM0_A6_2, PO_C48_ARM0_EYE0, PO_C48_ARM0_EYE0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS1_UARM_DIE
	10,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C48_ARM0_B0, PO_C48_ARM0_B0_2, PO_C48_ARM0_B1, PO_C48_ARM0_B1_2, PO_C48_ARM0_B2, PO_C48_ARM0_B2_2, PO_C48_ARM0_B3, PO_C48_ARM0_B3_2,
	PO_C48_ARM0_B4, PO_C48_ARM0_B4_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS1_DARM_NEUTRAL
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C48_ARM1_EYE0, PO_C48_ARM1_EYE0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS1_DARM_BULLET
	80,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C48_ARM1_EYE0, PO_C48_ARM1_EYE0_2, PO_C48_ARM1_EYE1, PO_C48_ARM1_EYE1_ARM1_EYE2_2, PO_C48_ARM1_EYE2, PO_C48_ARM1_EYE2_ARM1_EYE3_2, PO_C48_ARM1_EYE3, PO_C48_ARM1_EYE3,
	PO_C48_ARM1_EYE3, PO_C48_ARM1_EYE3, PO_C48_ARM1_EYE3, PO_C48_ARM1_EYE3, PO_C48_ARM1_EYE3, PO_C48_ARM1_EYE3, PO_C48_ARM1_EYE3, PO_C48_ARM1_EYE3_ARM1_A0_1,
	PO_C48_ARM1_EYE3_ARM1_A0_1, PO_C48_ARM1_EYE3_ARM1_A0_1, PO_C48_ARM1_EYE3_ARM1_A0_1, PO_C48_ARM1_EYE3_ARM1_A0_1, PO_C48_ARM1_EYE3_ARM1_A0_1, PO_C48_ARM1_EYE3_ARM1_A0_1, PO_C48_ARM1_EYE3_ARM1_A0_1, PO_C48_ARM1_EYE3_ARM1_A0_2,
	PO_C48_ARM1_EYE3_ARM1_A0_2, PO_C48_ARM1_EYE3_ARM1_A0_2, PO_C48_ARM1_EYE3_ARM1_A0_2, PO_C48_ARM1_EYE3_ARM1_A0_2, PO_C48_ARM1_EYE3_ARM1_A0_2, PO_C48_ARM1_EYE3_ARM1_A0_2, PO_C48_ARM1_EYE3_ARM1_A0_2, PO_C48_ARM1_EYE3_ARM1_A0_2,
	PO_C48_ARM1_EYE3_ARM1_A0_3, PO_C48_ARM1_EYE3_ARM1_A0_3, PO_C48_ARM1_EYE3_ARM1_A0_3, PO_C48_ARM1_EYE3_ARM1_A0_3, PO_C48_ARM1_EYE3_ARM1_A0_3, PO_C48_ARM1_EYE3_ARM1_A0_3, PO_C48_ARM1_EYE3_ARM1_A0_3, PO_C48_ARM1_EYE3_ARM1_A0_3,
	PO_C48_ARM1_A0, PO_C48_ARM1_A0_ARM1_A1_2, PO_C48_ARM1_A1, PO_C48_ARM1_A1_2, PO_C48_ARM1_A2, PO_C48_ARM1_A2_ARM1_A0_2, PO_C48_ARM1_A0, PO_C48_ARM1_A0_ARM1_EYE3_2,
	PO_C48_ARM1_EYE3, PO_C48_ARM1_EYE3, PO_C48_ARM1_EYE3, PO_C48_ARM1_EYE3, PO_C48_ARM1_EYE3, PO_C48_ARM1_EYE3, PO_C48_ARM1_EYE3, PO_C48_ARM1_EYE3_ARM1_EYE2_1,
	PO_C48_ARM1_EYE3_ARM1_EYE2_1, PO_C48_ARM1_EYE3_ARM1_EYE2_1, PO_C48_ARM1_EYE3_ARM1_EYE2_1, PO_C48_ARM1_EYE3_ARM1_EYE2_1, PO_C48_ARM1_EYE3_ARM1_EYE2_1, PO_C48_ARM1_EYE3_ARM1_EYE2_2, PO_C48_ARM1_EYE3_ARM1_EYE2_2, PO_C48_ARM1_EYE3_ARM1_EYE2_2,
	PO_C48_ARM1_EYE3_ARM1_EYE2_2, PO_C48_ARM1_EYE3_ARM1_EYE2_2, PO_C48_ARM1_EYE3_ARM1_EYE2_2, PO_C48_ARM1_EYE3_ARM1_EYE2_2, PO_C48_ARM1_EYE3_ARM1_EYE2_3, PO_C48_ARM1_EYE3_ARM1_EYE2_3, PO_C48_ARM1_EYE3_ARM1_EYE2_3, PO_C48_ARM1_EYE3_ARM1_EYE2_3,
	PO_C48_ARM1_EYE3_ARM1_EYE2_3, PO_C48_ARM1_EYE3_ARM1_EYE2_3, PO_C48_ARM1_EYE2, PO_C48_ARM1_EYE2_ARM1_EYE1_2, PO_C48_ARM1_EYE1, PO_C48_ARM1_EYE1_ARM1_EYE0_2, PO_C48_ARM1_EYE0, PO_C48_ARM1_EYE0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS1_DARM_MOVE
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C48_ARM1_EYE0, PO_C48_ARM1_EYE0_2, PO_C48_ARM1_EYE1, PO_C48_ARM1_EYE1_ARM1_EYE2_2, PO_C48_ARM1_EYE2, PO_C48_ARM1_EYE2_ARM1_EYE3_2, PO_C48_ARM1_EYE3, PO_C48_ARM1_EYE3_ARM1_A0_2,
	PO_C48_ARM1_A0, PO_C48_ARM1_A0_ARM1_A1_2, PO_C48_ARM1_A1, PO_C48_ARM1_A1_2, PO_C48_ARM1_A2, PO_C48_ARM1_A2_ARM1_A3_2, PO_C48_ARM1_A3, PO_C48_ARM1_A3,
	PO_C48_ARM1_A3, PO_C48_ARM1_A3_1, PO_C48_ARM1_A3_1, PO_C48_ARM1_A3_2, PO_C48_ARM1_A3_2, PO_C48_ARM1_A3_2, PO_C48_ARM1_A3_3, PO_C48_ARM1_A3_3,
	PO_C48_ARM1_A4, PO_C48_ARM1_A4_2, PO_C48_ARM1_A5, PO_C48_ARM1_A5_2, PO_C48_ARM1_A6, PO_C48_ARM1_A6_2, PO_C48_ARM1_EYE0, PO_C48_ARM1_EYE0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS1_DARM_DIE
	10,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C48_ARM1_B0, PO_C48_ARM1_B0_2, PO_C48_ARM1_B1, PO_C48_ARM1_B1_2, PO_C48_ARM1_B2, PO_C48_ARM1_B2_2, PO_C48_ARM1_B3, PO_C48_ARM1_B3_2,
	PO_C48_ARM1_B4, PO_C48_ARM1_B4_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c49mv[] = {
	//상태 데이터
	//ELKEIN2_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C49_N0, PO_C49_N0_1, PO_C49_N0_2, PO_C49_N0_3, PO_C49_N1, PO_C49_N1_N2_1, PO_C49_N1_N2_2, PO_C49_N1_N2_3,
	PO_C49_N2, PO_C49_N2_1, PO_C49_N2_2, PO_C49_N2_3, PO_C49_N1, PO_C49_N1_N0_1, PO_C49_N1_N0_2, PO_C49_N1_N0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ELKEIN2_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C49_W0, PO_C49_W0_1, PO_C49_W0_2, PO_C49_W0_3, PO_C49_W1, PO_C49_W1_1, PO_C49_W1_2, PO_C49_W1_3,
	PO_C49_W2, PO_C49_W2_1, PO_C49_W2_2, PO_C49_W2_3, PO_C49_W3, PO_C49_W3_1, PO_C49_W3_2, PO_C49_W3_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ELKEIN2_ATTACK
	84,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C49_A0, PO_C49_A0_2, PO_C49_A1, PO_C49_A1, PO_C49_A1, PO_C49_A1, PO_C49_A1, PO_C49_A1,
	PO_C49_A1, PO_C49_A1_1, PO_C49_A1_1, PO_C49_A1_1, PO_C49_A1_1, PO_C49_A1_1, PO_C49_A1_1, PO_C49_A1_2,
	PO_C49_A1_2, PO_C49_A1_2, PO_C49_A1_2, PO_C49_A1_2, PO_C49_A1_2, PO_C49_A1_2, PO_C49_A1_3, PO_C49_A1_3,
	PO_C49_A1_3, PO_C49_A1_3, PO_C49_A1_3, PO_C49_A1_3, PO_C49_A2, PO_C49_A2_2, PO_C49_A3, PO_C49_A3_2,
	PO_C49_A4, PO_C49_A4_2, PO_C49_A5, PO_C49_A5, PO_C49_A5, PO_C49_A5_1, PO_C49_A5_1, PO_C49_A5_2,
	PO_C49_A5_2, PO_C49_A5_2, PO_C49_A5_3, PO_C49_A5_3, PO_C49_A6, PO_C49_A6_2, PO_C49_A7, PO_C49_A7_2,
	PO_C49_A8, PO_C49_A8_2, PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9,
	PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9,
	PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9,
	PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9,
	PO_C49_A9, PO_C49_A9, PO_C49_A9, PO_C49_A9,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X,
	3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X,
	3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ELKEIN2_UPATTACK
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C49_SA0, PO_C49_SA0_2, PO_C49_SA1, PO_C49_SA1_2, PO_C49_SA2, PO_C49_SA2_2, PO_C49_SA3, PO_C49_SA3_2,
	PO_C49_SA4, PO_C49_SA4_2, PO_C49_SA5, PO_C49_SA5, PO_C49_SA5, PO_C49_SA5, PO_C49_SA5, PO_C49_SA5,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ELKEIN2_JUMPATTACK
	110,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C49_JA0, PO_C49_JA0, PO_C49_JA0, PO_C49_JA0, PO_C49_JA0, PO_C49_JA0, PO_C49_JA0_1, PO_C49_JA0_1,
	PO_C49_JA0_1, PO_C49_JA0_1, PO_C49_JA0_1, PO_C49_JA0_2, PO_C49_JA0_2, PO_C49_JA0_2, PO_C49_JA0_2, PO_C49_JA0_2,
	PO_C49_JA0_2, PO_C49_JA0_3, PO_C49_JA0_3, PO_C49_JA0_3, PO_C49_JA0_3, PO_C49_JA0_3, PO_C49_JA1, PO_C49_JA1_1,
	PO_C49_JA1_2, PO_C49_JA1_3, PO_C49_JA2, PO_C49_JA2_1, PO_C49_JA2_2, PO_C49_JA2_3, PO_C49_JA3, PO_C49_JA3_1,
	PO_C49_JA3_2, PO_C49_JA3_3, PO_C49_JA4, PO_C49_JA4_1, PO_C49_JA4_2, PO_C49_JA4_3, PO_C49_JA5, PO_C49_JA5_JA1_1,
	PO_C49_JA5_JA1_2, PO_C49_JA5_JA1_3, PO_C49_JA1, PO_C49_JA1_1, PO_C49_JA1_2, PO_C49_JA1_3, PO_C49_JA2, PO_C49_JA2_1,
	PO_C49_JA2_2, PO_C49_JA2_3, PO_C49_JA3, PO_C49_JA3_1, PO_C49_JA3_2, PO_C49_JA3_3, PO_C49_JA4, PO_C49_JA4_1,
	PO_C49_JA4_2, PO_C49_JA4_3, PO_C49_JA5, PO_C49_JA5_JA1_1, PO_C49_JA5_JA1_2, PO_C49_JA5_JA1_3, PO_C49_JA1, PO_C49_JA1_1,
	PO_C49_JA1_2, PO_C49_JA1_3, PO_C49_JA2, PO_C49_JA2_1, PO_C49_JA2_2, PO_C49_JA2_3, PO_C49_JA3, PO_C49_JA3_1,
	PO_C49_JA3_2, PO_C49_JA3_3, PO_C49_JA4, PO_C49_JA4_1, PO_C49_JA4_2, PO_C49_JA4_3, PO_C49_JA5, PO_C49_JA5_JA6_2,
	PO_C49_JA6, PO_C49_JA6, PO_C49_JA6, PO_C49_JA6, PO_C49_JA6, PO_C49_JA6, PO_C49_JA6, PO_C49_JA6,
	PO_C49_JA6, PO_C49_JA6, PO_C49_JA6, PO_C49_JA6, PO_C49_JA6, PO_C49_JA6, PO_C49_JA6, PO_C49_JA6,
	PO_C49_JA6, PO_C49_JA6, PO_C49_JA6, PO_C49_JA6, PO_C49_JA6, PO_C49_JA6, PO_C49_JA6, PO_C49_JA6,
	PO_C49_JA6, PO_C49_JA6, PO_C49_JA6, PO_C49_JA6, PO_C49_JA6, PO_C49_JA6,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 101, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ELKEIN2_WEAK
	84,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C49_WEAK0, PO_C49_WEAK0_2, PO_C49_WEAK1, PO_C49_WEAK1_2, PO_C49_WEAK2, PO_C49_WEAK2_2, PO_C49_WEAK3, PO_C49_WEAK3_2,
	PO_C49_WEAK4, PO_C49_WEAK4_2, PO_C49_WEAK5, PO_C49_WEAK5_2, PO_C49_WEAK6, PO_C49_WEAK6_2, PO_C49_WEAK7, PO_C49_WEAK7_2,
	PO_C49_WEAK8, PO_C49_WEAK8_2, PO_C49_WEAK9, PO_C49_WEAK9_2, PO_C49_WEAK10, PO_C49_WEAK10_WEAK7_2, PO_C49_WEAK7, PO_C49_WEAK7_2,
	PO_C49_WEAK8, PO_C49_WEAK8_2, PO_C49_WEAK9, PO_C49_WEAK9_2, PO_C49_WEAK10, PO_C49_WEAK10_WEAK7_2, PO_C49_WEAK7, PO_C49_WEAK7_2,
	PO_C49_WEAK8, PO_C49_WEAK8_2, PO_C49_WEAK9, PO_C49_WEAK9_2, PO_C49_WEAK10, PO_C49_WEAK10_WEAK7_2, PO_C49_WEAK7, PO_C49_WEAK7_2,
	PO_C49_WEAK8, PO_C49_WEAK8_2, PO_C49_WEAK9, PO_C49_WEAK9_2, PO_C49_WEAK10, PO_C49_WEAK10_WEAK7_2, PO_C49_WEAK7, PO_C49_WEAK7_2,
	PO_C49_WEAK8, PO_C49_WEAK8_2, PO_C49_WEAK9, PO_C49_WEAK9_2, PO_C49_WEAK10, PO_C49_WEAK10_WEAK7_2, PO_C49_WEAK7, PO_C49_WEAK7_2,
	PO_C49_WEAK8, PO_C49_WEAK8_2, PO_C49_WEAK9, PO_C49_WEAK9_2, PO_C49_WEAK10, PO_C49_WEAK10_WEAK7_2, PO_C49_WEAK7, PO_C49_WEAK7_2,
	PO_C49_WEAK8, PO_C49_WEAK8_2, PO_C49_WEAK9, PO_C49_WEAK9_2, PO_C49_WEAK10, PO_C49_WEAK10_WEAK11_2, PO_C49_WEAK11, PO_C49_WEAK11_2,
	PO_C49_WEAK12, PO_C49_WEAK12_2, PO_C49_WEAK13, PO_C49_WEAK13_2, PO_C49_WEAK14, PO_C49_WEAK14_2, PO_C49_WEAK15, PO_C49_WEAK15_2,
	PO_C49_WEAK16, PO_C49_WEAK16_2, PO_C49_WEAK17, PO_C49_WEAK17,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	ELKEIN2_NEUTRAL,	ELKEIN2_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 4,	RANDOM,	50,
	ELKEIN2_NEUTRAL,	ELKEIN2_JUMPATTACK,	0,	0,	RANDOM,	30,
	ELKEIN2_NEUTRAL,	ELKEIN2_UPATTACK,	DISTANCE_OUT_XY,	4 * 8 + 4,	RANDOM,	30,
	ELKEIN2_NEUTRAL,	ELKEIN2_MOVE,	0,	0,	RANDOM,	30,
	ELKEIN2_MOVE,	ELKEIN2_ATTACK,	DISTANCE_CHECK_XY,	4 * 8 + 4,	0,	0,
	ELKEIN2_MOVE,	ELKEIN2_JUMPATTACK,	0,	0,	RANDOM,	30,
	ELKEIN2_MOVE,	ELKEIN2_UPATTACK,	DISTANCE_OUT_XY,	4 * 8 + 4,	RANDOM,	30,
	ELKEIN2_MOVE,	ELKEIN2_NEUTRAL,	0,	0,	RANDOM,	30,
	ELKEIN2_ATTACK,	ELKEIN2_NEUTRAL,	0,	0,	0,	0,
	ELKEIN2_JUMPATTACK,	ELKEIN2_NEUTRAL,	0,	0,	0,	0,
	ELKEIN2_UPATTACK,	ELKEIN2_NEUTRAL,	0,	0,	0,	0,
	ELKEIN2_WEAK,	ELKEIN2_NEUTRAL,	0,	0,	0,	0,
	-1,
};

const signed short c50mv[] = {
	//상태 데이터
	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C50_N0, PO_C50_N0, PO_C50_N0_1, PO_C50_N0_2, PO_C50_N0_2, PO_C50_N0_3, PO_C50_N1, PO_C50_N1,
	PO_C50_N1_1, PO_C50_N1_2, PO_C50_N1_2, PO_C50_N1_3, PO_C50_N2, PO_C50_N2, PO_C50_N2_1, PO_C50_N2_2,
	PO_C50_N2_2, PO_C50_N2_3, PO_C50_N3, PO_C50_N3, PO_C50_N3_1, PO_C50_N3_2, PO_C50_N3_2, PO_C50_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	120,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C50_A0, PO_C50_A0, PO_C50_A0_1, PO_C50_A0_2, PO_C50_A0_2, PO_C50_A0_3, PO_C50_A1, PO_C50_A1,
	PO_C50_A1_1, PO_C50_A1_2, PO_C50_A1_2, PO_C50_A1_3, PO_C50_A2, PO_C50_A2, PO_C50_A2_1, PO_C50_A2_2,
	PO_C50_A2_2, PO_C50_A2_3, PO_C50_A3, PO_C50_A3, PO_C50_A3_1, PO_C50_A3_2, PO_C50_A3_2, PO_C50_A3_3,
	PO_C50_A4, PO_C50_A4, PO_C50_A4_1, PO_C50_A4_2, PO_C50_A4_2, PO_C50_A4_3, PO_C50_A5, PO_C50_A5,
	PO_C50_A5_1, PO_C50_A5_2, PO_C50_A5_2, PO_C50_A5_3, PO_C50_A6, PO_C50_A6, PO_C50_A6_1, PO_C50_A6_2,
	PO_C50_A6_2, PO_C50_A6_3, PO_C50_A7, PO_C50_A7, PO_C50_A7_1, PO_C50_A7_2, PO_C50_A7_2, PO_C50_A7_3,
	PO_C50_A8, PO_C50_A8, PO_C50_A8_1, PO_C50_A8_2, PO_C50_A8_2, PO_C50_A8_3, PO_C50_A9, PO_C50_A9,
	PO_C50_A9_1, PO_C50_A9_2, PO_C50_A9_2, PO_C50_A9_3, PO_C50_A10, PO_C50_A10, PO_C50_A10_1, PO_C50_A10_2,
	PO_C50_A10_2, PO_C50_A10_3, PO_C50_A11, PO_C50_A11, PO_C50_A11_1, PO_C50_A11_2, PO_C50_A11_2, PO_C50_A11_3,
	PO_C50_A12, PO_C50_A12, PO_C50_A12_1, PO_C50_A12_2, PO_C50_A12_2, PO_C50_A12_3, PO_C50_A13, PO_C50_A13,
	PO_C50_A13_1, PO_C50_A13_2, PO_C50_A13_2, PO_C50_A13_3, PO_C50_A14, PO_C50_A14, PO_C50_A14_1, PO_C50_A14_2,
	PO_C50_A14_2, PO_C50_A14_3, PO_C50_A15, PO_C50_A15, PO_C50_A15_1, PO_C50_A15_2, PO_C50_A15_2, PO_C50_A15_3,
	PO_C50_A16, PO_C50_A16, PO_C50_A16_1, PO_C50_A16_2, PO_C50_A16_2, PO_C50_A16_3, PO_C50_A17, PO_C50_A17,
	PO_C50_A17_1, PO_C50_A17_2, PO_C50_A17_2, PO_C50_A17_3, PO_C50_A18, PO_C50_A18, PO_C50_A18_1, PO_C50_A18_2,
	PO_C50_A18_2, PO_C50_A18_3, PO_C50_A19, PO_C50_A19, PO_C50_A19, PO_C50_A19, PO_C50_A19, PO_C50_A19,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, -1, -1, -1, -1,
	-1, -1, 1, 1, 1, 1, 1, 1,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	96,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C50_B0, PO_C50_B0_2, PO_C50_B1, PO_C50_B1_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2,
	PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B0_2,
	PO_C50_B0, PO_C50_B0_2, PO_C50_B1, PO_C50_B1_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2,
	PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B0_2,
	PO_C50_B0, PO_C50_B0_2, PO_C50_B1, PO_C50_B1_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2,
	PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B0_2,
	PO_C50_B0, PO_C50_B0_2, PO_C50_B1, PO_C50_B1_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2,
	PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B0_2,
	PO_C50_B0, PO_C50_B0_2, PO_C50_B1, PO_C50_B1_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2,
	PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B0_2,
	PO_C50_B0, PO_C50_B0_2, PO_C50_B1, PO_C50_B1_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2,
	PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	48,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C50_B0, PO_C50_B0_2, PO_C50_B1, PO_C50_B1_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2,
	PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B0_2,
	PO_C50_B0, PO_C50_B0_2, PO_C50_B1, PO_C50_B1_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2,
	PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B0_2,
	PO_C50_B0, PO_C50_B0_2, PO_C50_B1, PO_C50_B1_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2,
	PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	48,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C50_B0, PO_C50_B0_2, PO_C50_B1, PO_C50_B1_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2,
	PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B0_2,
	PO_C50_B0, PO_C50_B0_2, PO_C50_B1, PO_C50_B1_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2,
	PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B0_2,
	PO_C50_B0, PO_C50_B0_2, PO_C50_B1, PO_C50_B1_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2,
	PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	64,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C50_B0, PO_C50_B0_2, PO_C50_B1, PO_C50_B1_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2,
	PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B0_2,
	PO_C50_B0, PO_C50_B0_2, PO_C50_B1, PO_C50_B1_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2,
	PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B0_2,
	PO_C50_B0, PO_C50_B0_2, PO_C50_B1, PO_C50_B1_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2,
	PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B0_2,
	PO_C50_B0, PO_C50_B0_2, PO_C50_B1, PO_C50_B1_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2,
	PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3_B2_2, PO_C50_B2, PO_C50_B2_2, PO_C50_B3, PO_C50_B3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	CASTLEBOSS3_NEUTRAL,	CASTLEBOSS3_IMPALE,	0,	0,	RANDOM,	30,
	CASTLEBOSS3_NEUTRAL,	CASTLEBOSS3_BOMB,	0,	0,	RANDOM,	30,
	CASTLEBOSS3_NEUTRAL,	CASTLEBOSS3_LASER,	0,	0,	RANDOM,	30,
	CASTLEBOSS3_IMPALE,	CASTLEBOSS3_NEUTRAL,	0,	0,	0,	0,
	CASTLEBOSS3_IMPALE2,	CASTLEBOSS3_NEUTRAL,	0,	0,	0,	0,
	CASTLEBOSS3_IMPALE3,	CASTLEBOSS3_NEUTRAL,	0,	0,	0,	0,
	CASTLEBOSS3_BOMB,	CASTLEBOSS3_NEUTRAL,	0,	0,	0,	0,
	CASTLEBOSS3_LASER,	CASTLEBOSS3_NEUTRAL,	0,	0,	0,	0,
	-1,
};
// 무브할때 한칸내려감
const signed short c51mv[] = {
	//상태 데이터
	//CASTLEBOSS4_NEUTRAL
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C51_N0, PO_C51_N0, PO_C51_N0_1, PO_C51_N0_1, PO_C51_N0_2, PO_C51_N0_2, PO_C51_N0_3, PO_C51_N0_3,
	PO_C51_N1, PO_C51_N1, PO_C51_N1_1, PO_C51_N1_1, PO_C51_N1_2, PO_C51_N1_2, PO_C51_N1_3, PO_C51_N1_3,
	PO_C51_N2, PO_C51_N2, PO_C51_N2_1, PO_C51_N2_1, PO_C51_N2_2, PO_C51_N2_2, PO_C51_N2_3, PO_C51_N2_3,
	PO_C51_N3, PO_C51_N3, PO_C51_N3_1, PO_C51_N3_1, PO_C51_N3_2, PO_C51_N3_2, PO_C51_N3_3, PO_C51_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS4_WALK
	96,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C51_W0, PO_C51_W0, PO_C51_W0_1, PO_C51_W0_1, PO_C51_W0_2, PO_C51_W0_2, PO_C51_W0_3, PO_C51_W0_3,
	PO_C51_W1, PO_C51_W1, PO_C51_W1_1, PO_C51_W1_1, PO_C51_W1_2, PO_C51_W1_2, PO_C51_W1_3, PO_C51_W1_3,
	PO_C51_W2, PO_C51_W2, PO_C51_W2_1, PO_C51_W2_1, PO_C51_W2_2, PO_C51_W2_2, PO_C51_W2_3, PO_C51_W2_3,
	PO_C51_W3, PO_C51_W3, PO_C51_W3_1, PO_C51_W3_1, PO_C51_W3_2, PO_C51_W3_2, PO_C51_W3_3, PO_C51_W3_3,
	PO_C51_W4, PO_C51_W4, PO_C51_W4_1, PO_C51_W4_1, PO_C51_W4_2, PO_C51_W4_2, PO_C51_W4_3, PO_C51_W4_3,
	PO_C51_W5, PO_C51_W5, PO_C51_W5_1, PO_C51_W5_1, PO_C51_W5_2, PO_C51_W5_2, PO_C51_W5_3, PO_C51_W5_3,
	PO_C51_W0, PO_C51_W0, PO_C51_W0_1, PO_C51_W0_1, PO_C51_W0_2, PO_C51_W0_2, PO_C51_W0_3, PO_C51_W0_3,
	PO_C51_W1, PO_C51_W1, PO_C51_W1_1, PO_C51_W1_1, PO_C51_W1_2, PO_C51_W1_2, PO_C51_W1_3, PO_C51_W1_3,
	PO_C51_W2, PO_C51_W2, PO_C51_W2_1, PO_C51_W2_1, PO_C51_W2_2, PO_C51_W2_2, PO_C51_W2_3, PO_C51_W2_3,
	PO_C51_W3, PO_C51_W3, PO_C51_W3_1, PO_C51_W3_1, PO_C51_W3_2, PO_C51_W3_2, PO_C51_W3_3, PO_C51_W3_3,
	PO_C51_W4, PO_C51_W4, PO_C51_W4_1, PO_C51_W4_1, PO_C51_W4_2, PO_C51_W4_2, PO_C51_W4_3, PO_C51_W4_3,
	PO_C51_W5, PO_C51_W5, PO_C51_W5_1, PO_C51_W5_1, PO_C51_W5_2, PO_C51_W5_2, PO_C51_W5_3, PO_C51_W5_3,	//상태 프레임별 모션
	3, 3, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	5, 5, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1, 1, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3, 3, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	5, 5, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1, 1, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS4_ATTACK
	72,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C51_A0, PO_C51_A0_1, PO_C51_A0_2, PO_C51_A0_3, PO_C51_A1, PO_C51_A1_2, PO_C51_A2, PO_C51_A2_2,
	PO_C51_A3, PO_C51_A3_2, PO_C51_A4, PO_C51_A4_A1_2, PO_C51_A1, PO_C51_A1_2, PO_C51_A2, PO_C51_A2_2,
	PO_C51_A3, PO_C51_A3_2, PO_C51_A4, PO_C51_A4_A1_2, PO_C51_A1, PO_C51_A1_2, PO_C51_A2, PO_C51_A2_2,
	PO_C51_A3, PO_C51_A3_2, PO_C51_A4, PO_C51_A4_A1_2, PO_C51_A1, PO_C51_A1_2, PO_C51_A2, PO_C51_A2_2,
	PO_C51_A3, PO_C51_A3_2, PO_C51_A4, PO_C51_A4_A5_2, PO_C51_A5, PO_C51_A5_2, PO_C51_A6, PO_C51_A6_2,
	PO_C51_A7, PO_C51_A7_2, PO_C51_A8, PO_C51_A8_2, PO_C51_A9, PO_C51_A9, PO_C51_A9, PO_C51_A9,
	PO_C51_A9, PO_C51_A9, PO_C51_A9_1, PO_C51_A9_1, PO_C51_A9_1, PO_C51_A9_1, PO_C51_A9_1, PO_C51_A9_1,
	PO_C51_A9_2, PO_C51_A9_2, PO_C51_A9_2, PO_C51_A9_2, PO_C51_A9_2, PO_C51_A9_2, PO_C51_A9_3, PO_C51_A9_3,
	PO_C51_A9_3, PO_C51_A9_3, PO_C51_A9_3, PO_C51_A9_3, PO_C51_RETURN0, PO_C51_RETURN0_2, PO_C51_N0, PO_C51_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS4_WIND
	162,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C51_SA0, PO_C51_SA0, PO_C51_SA0_1, PO_C51_SA0_2, PO_C51_SA0_2, PO_C51_SA0_3, PO_C51_SA1, PO_C51_SA1,
	PO_C51_SA1_1, PO_C51_SA1_2, PO_C51_SA1_2, PO_C51_SA1_3, PO_C51_SA2, PO_C51_SA2, PO_C51_SA2_1, PO_C51_SA2_2,
	PO_C51_SA2_2, PO_C51_SA2_3, PO_C51_SA3, PO_C51_SA3, PO_C51_SA3_1, PO_C51_SA3_2, PO_C51_SA3_2, PO_C51_SA3_3,
	PO_C51_SA4, PO_C51_SA4, PO_C51_SA4_SA2_1, PO_C51_SA4_SA2_2, PO_C51_SA4_SA2_2, PO_C51_SA4_SA2_3, PO_C51_SA2, PO_C51_SA2,
	PO_C51_SA2_1, PO_C51_SA2_2, PO_C51_SA2_2, PO_C51_SA2_3, PO_C51_SA3, PO_C51_SA3, PO_C51_SA3_1, PO_C51_SA3_2,
	PO_C51_SA3_2, PO_C51_SA3_3, PO_C51_SA4, PO_C51_SA4, PO_C51_SA4_SA2_1, PO_C51_SA4_SA2_2, PO_C51_SA4_SA2_2, PO_C51_SA4_SA2_3,
	PO_C51_SA2, PO_C51_SA2, PO_C51_SA2_1, PO_C51_SA2_2, PO_C51_SA2_2, PO_C51_SA2_3, PO_C51_SA3, PO_C51_SA3,
	PO_C51_SA3_1, PO_C51_SA3_2, PO_C51_SA3_2, PO_C51_SA3_3, PO_C51_SA4, PO_C51_SA4, PO_C51_SA4_SA5_1, PO_C51_SA4_SA5_2,
	PO_C51_SA4_SA5_2, PO_C51_SA4_SA5_3, PO_C51_SA5, PO_C51_SA5_2, PO_C51_SA6, PO_C51_SA6_2, PO_C51_SA7, PO_C51_SA7_2,
	PO_C51_SA8, PO_C51_SA8_SA5_2, PO_C51_SA5, PO_C51_SA5_2, PO_C51_SA6, PO_C51_SA6_2, PO_C51_SA7, PO_C51_SA7_2,
	PO_C51_SA8, PO_C51_SA8_SA5_2, PO_C51_SA5, PO_C51_SA5_2, PO_C51_SA6, PO_C51_SA6_2, PO_C51_SA7, PO_C51_SA7_2,
	PO_C51_SA8, PO_C51_SA8_SA5_2, PO_C51_SA5, PO_C51_SA5_2, PO_C51_SA6, PO_C51_SA6_2, PO_C51_SA7, PO_C51_SA7_2,
	PO_C51_SA8, PO_C51_SA8_SA5_2, PO_C51_SA5, PO_C51_SA5_2, PO_C51_SA6, PO_C51_SA6_2, PO_C51_SA7, PO_C51_SA7_2,
	PO_C51_SA8, PO_C51_SA8_SA5_2, PO_C51_SA5, PO_C51_SA5_2, PO_C51_SA6, PO_C51_SA6_2, PO_C51_SA7, PO_C51_SA7_2,
	PO_C51_SA8, PO_C51_SA8_SA5_2, PO_C51_SA5, PO_C51_SA5_2, PO_C51_SA6, PO_C51_SA6_2, PO_C51_SA7, PO_C51_SA7_2,
	PO_C51_SA8, PO_C51_SA8_SA5_2, PO_C51_SA5, PO_C51_SA5_2, PO_C51_SA6, PO_C51_SA6_2, PO_C51_SA7, PO_C51_SA7_2,
	PO_C51_SA8, PO_C51_SA8_SA5_2, PO_C51_SA5, PO_C51_SA5_2, PO_C51_SA6, PO_C51_SA6_2, PO_C51_SA7, PO_C51_SA7_2,
	PO_C51_SA8, PO_C51_SA8, PO_C51_SA8_SA10_1, PO_C51_SA8_SA10_1, PO_C51_SA8_SA10_2, PO_C51_SA8_SA10_2, PO_C51_SA8_SA10_3, PO_C51_SA8_SA10_3,
	PO_C51_SA10, PO_C51_SA10, PO_C51_SA10_1, PO_C51_SA10_2, PO_C51_SA10_2, PO_C51_SA10_3, PO_C51_SA11, PO_C51_SA11,
	PO_C51_SA11_1, PO_C51_SA11_2, PO_C51_SA11_2, PO_C51_SA11_3, PO_C51_SA12, PO_C51_SA12, PO_C51_SA12, PO_C51_SA12,
	PO_C51_SA12, PO_C51_SA12,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS4_DEAD
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C51_DEAD, PO_C51_DEAD,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS4_HAND_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C51_HAND0, PO_C51_HAND0_1, PO_C51_HAND0_2, PO_C51_HAND0_3, PO_C51_HAND1, PO_C51_HAND1_1, PO_C51_HAND1_2, PO_C51_HAND1_3,
	PO_C51_HAND2, PO_C51_HAND2_1, PO_C51_HAND2_2, PO_C51_HAND2_3, PO_C51_HAND3, PO_C51_HAND3_1, PO_C51_HAND3_2, PO_C51_HAND3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS4_HAND_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C51_HAND0, PO_C51_HAND0_1, PO_C51_HAND0_2, PO_C51_HAND0_3, PO_C51_HAND1, PO_C51_HAND1_1, PO_C51_HAND1_2, PO_C51_HAND1_3,
	PO_C51_HAND2, PO_C51_HAND2_1, PO_C51_HAND2_2, PO_C51_HAND2_3, PO_C51_HAND3, PO_C51_HAND3_1, PO_C51_HAND3_2, PO_C51_HAND3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS4_HAND_DOWN
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C51_HANDDOWN0, PO_C51_HANDDOWN0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS4_HAND_ATTACK
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C51_HANDDOWN1, PO_C51_HANDDOWN1_2, PO_C51_HANDDOWN2, PO_C51_HANDDOWN2_2, PO_C51_HANDDOWN3, PO_C51_HANDDOWN3_2, PO_C51_HANDDOWN4, PO_C51_HANDDOWN4_2,
	PO_C51_HANDDOWN0, PO_C51_HANDDOWN0, PO_C51_HANDDOWN0_1, PO_C51_HANDDOWN0_1, PO_C51_HANDDOWN0_2, PO_C51_HANDDOWN0_2, PO_C51_HANDDOWN0_3, PO_C51_HANDDOWN0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS4_HAND_GRABMOVE
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C51_HANDDOWN0, PO_C51_HANDDOWN0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//CASTLEBOSS4_HAND_MOMMOVE
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C51_HANDGRAB0, PO_C51_HANDGRAB0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C51_HANDGRAB1, PO_C51_HANDGRAB1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C51_HANDGRAB1, PO_C51_HANDGRAB1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	CASTLEBOSS4_NEUTRAL,	CASTLEBOSS4_ATTACK,	0,	0,	RANDOM,	40,
	CASTLEBOSS4_NEUTRAL,	CASTLEBOSS4_WIND,	0,	0,	RANDOM,	40,
	CASTLEBOSS4_NEUTRAL,	CASTLEBOSS4_WALK,	0,	0,	RANDOM,	40,
	CASTLEBOSS4_WALK,	CASTLEBOSS4_ATTACK,	0,	0,	RANDOM,	40,
	CASTLEBOSS4_WALK,	CASTLEBOSS4_WIND,	0,	0,	RANDOM,	40,
	CASTLEBOSS4_WALK,	CASTLEBOSS4_NEUTRAL,	0,	0,	RANDOM,	40,
	CASTLEBOSS4_ATTACK,	CASTLEBOSS4_NEUTRAL,	0,	0,	0,	0,
	CASTLEBOSS4_WIND,	CASTLEBOSS4_NEUTRAL,	0,	0,	0,	0,
	-1,
};

const signed short c52mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C52_N0, PO_C52_N0_1, PO_C52_N0_2, PO_C52_N0_3, PO_C52_N1, PO_C52_N1_1, PO_C52_N1_2, PO_C52_N1_3,
	PO_C52_N2, PO_C52_N2_1, PO_C52_N2_2, PO_C52_N2_3, PO_C52_N3, PO_C52_N3_1, PO_C52_N3_2, PO_C52_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c53mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C53_N0, PO_C53_N0_1, PO_C53_N0_2, PO_C53_N0_3, PO_C53_N1, PO_C53_N1_1, PO_C53_N1_2, PO_C53_N1_3,
	PO_C53_N2, PO_C53_N2_1, PO_C53_N2_2, PO_C53_N2_3, PO_C53_N3, PO_C53_N3_1, PO_C53_N3_2, PO_C53_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c54mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C54_N0, PO_C54_N0_1, PO_C54_N0_2, PO_C54_N0_3, PO_C54_N1, PO_C54_N1_1, PO_C54_N1_2, PO_C54_N1_3,
	PO_C54_N2, PO_C54_N2_1, PO_C54_N2_2, PO_C54_N2_3, PO_C54_N3, PO_C54_N3_1, PO_C54_N3_2, PO_C54_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C54_W0, PO_C54_W0, PO_C54_W0_1, PO_C54_W0_1, PO_C54_W0_2, PO_C54_W0_2, PO_C54_W0_3, PO_C54_W0_3,
	PO_C54_W1, PO_C54_W1, PO_C54_W1_W2_1, PO_C54_W1_W2_1, PO_C54_W1_W2_2, PO_C54_W1_W2_2, PO_C54_W1_W2_3, PO_C54_W1_W2_3,
	PO_C54_W2, PO_C54_W2, PO_C54_W2_1, PO_C54_W2_1, PO_C54_W2_2, PO_C54_W2_2, PO_C54_W2_3, PO_C54_W2_3,
	PO_C54_W1, PO_C54_W1, PO_C54_W1_W0_1, PO_C54_W1_W0_1, PO_C54_W1_W0_2, PO_C54_W1_W0_2, PO_C54_W1_W0_3, PO_C54_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	NPCMOVE_STAND,	NPCMOVE_WALKSLOW,	0,	0,	RANDOM,	20,
	NPCMOVE_WALKSLOW,	NPCMOVE_STAND,	0,	0,	RANDOM,	40,
	-1,
};

const signed short c55mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C55_N0, PO_C55_N0_1, PO_C55_N0_2, PO_C55_N0_3, PO_C55_N1, PO_C55_N1_1, PO_C55_N1_2, PO_C55_N1_3,
	PO_C55_N2, PO_C55_N2_1, PO_C55_N2_2, PO_C55_N2_3, PO_C55_N3, PO_C55_N3_1, PO_C55_N3_2, PO_C55_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C55_W0, PO_C55_W0, PO_C55_W0_1, PO_C55_W0_1, PO_C55_W0_2, PO_C55_W0_2, PO_C55_W0_3, PO_C55_W0_3,
	PO_C55_W1, PO_C55_W1, PO_C55_W1_W2_1, PO_C55_W1_W2_1, PO_C55_W1_W2_2, PO_C55_W1_W2_2, PO_C55_W1_W2_3, PO_C55_W1_W2_3,
	PO_C55_W2, PO_C55_W2, PO_C55_W2_1, PO_C55_W2_1, PO_C55_W2_2, PO_C55_W2_2, PO_C55_W2_3, PO_C55_W2_3,
	PO_C55_W1, PO_C55_W1, PO_C55_W1_W0_1, PO_C55_W1_W0_1, PO_C55_W1_W0_2, PO_C55_W1_W0_2, PO_C55_W1_W0_3, PO_C55_W1_W0_3,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	7, 7, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	5, 5, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C55_D, PO_C55_D, PO_C55_D, PO_C55_D, PO_C55_D, PO_C55_D, PO_C55_D, PO_C55_D,
	PO_C55_D, PO_C55_D, PO_C55_D, PO_C55_D, PO_C55_D, PO_C55_D, PO_C55_D, PO_C55_D,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	NPCMOVE_STAND,	NPCMOVE_WALKSLOW,	0,	0,	RANDOM,	40,
	NPCMOVE_WALKSLOW,	NPCMOVE_STAND,	0,	0,	RANDOM,	30,
	-1,
};

const signed short c56mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C56_N0, PO_C56_N0_1, PO_C56_N0_2, PO_C56_N0_3, PO_C56_N1, PO_C56_N1_1, PO_C56_N1_2, PO_C56_N1_3,
	PO_C56_N2, PO_C56_N2_1, PO_C56_N2_2, PO_C56_N2_3, PO_C56_N3, PO_C56_N3_1, PO_C56_N3_2, PO_C56_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_RANDOM,	//초기화 조건
	PO_C56_W0, PO_C56_W0, PO_C56_W0_1, PO_C56_W0_1, PO_C56_W0_2, PO_C56_W0_2, PO_C56_W0_3, PO_C56_W0_3,
	PO_C56_W1, PO_C56_W1, PO_C56_W1_W2_1, PO_C56_W1_W2_1, PO_C56_W1_W2_2, PO_C56_W1_W2_2, PO_C56_W1_W2_3, PO_C56_W1_W2_3,
	PO_C56_W2, PO_C56_W2, PO_C56_W2_1, PO_C56_W2_1, PO_C56_W2_2, PO_C56_W2_2, PO_C56_W2_3, PO_C56_W2_3,
	PO_C56_W1, PO_C56_W1, PO_C56_W1_W0_1, PO_C56_W1_W0_1, PO_C56_W1_W0_2, PO_C56_W1_W0_2, PO_C56_W1_W0_3, PO_C56_W1_W0_3,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	NPCMOVE_STAND,	NPCMOVE_WALKSLOW,	0,	0,	RANDOM,	30,
	NPCMOVE_WALKSLOW,	NPCMOVE_STAND,	0,	0,	RANDOM,	30,
	-1,
};

const signed short c57mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C57_N0, PO_C57_N0_1, PO_C57_N0_2, PO_C57_N0_3, PO_C57_N1, PO_C57_N1_1, PO_C57_N1_2, PO_C57_N1_3,
	PO_C57_N2, PO_C57_N2_1, PO_C57_N2_2, PO_C57_N2_3, PO_C57_N3, PO_C57_N3_1, PO_C57_N3_2, PO_C57_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C57_W0, PO_C57_W0, PO_C57_W0_1, PO_C57_W0_1, PO_C57_W0_2, PO_C57_W0_2, PO_C57_W0_3, PO_C57_W0_3,
	PO_C57_W1, PO_C57_W1, PO_C57_W1_W2_1, PO_C57_W1_W2_1, PO_C57_W1_W2_2, PO_C57_W1_W2_2, PO_C57_W1_W2_3, PO_C57_W1_W2_3,
	PO_C57_W2, PO_C57_W2, PO_C57_W2_1, PO_C57_W2_1, PO_C57_W2_2, PO_C57_W2_2, PO_C57_W2_3, PO_C57_W2_3,
	PO_C57_W1, PO_C57_W1, PO_C57_W1_W0_1, PO_C57_W1_W0_1, PO_C57_W1_W0_2, PO_C57_W1_W0_2, PO_C57_W1_W0_3, PO_C57_W1_W0_3,	//상태 프레임별 모션
	3, 3, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	5, 5, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	7, 7, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C57_TUMBLE0, PO_C57_TUMBLE0_1, PO_C57_TUMBLE0_2, PO_C57_TUMBLE0_3, PO_C57_TUMBLE1, PO_C57_TUMBLE1_1, PO_C57_TUMBLE1_2, PO_C57_TUMBLE1_3,
	PO_C57_TUMBLE2, PO_C57_TUMBLE2_1, PO_C57_TUMBLE2_2, PO_C57_TUMBLE2_3, PO_C57_TUMBLE3, PO_C57_TUMBLE3_1, PO_C57_TUMBLE3_2, PO_C57_TUMBLE3_3,	//상태 프레임별 모션
	5, 5, 0 * _2X, 0 * _2X, 5, 5, 0 * _2X, 0 * _2X,
	5, 5, 0 * _2X, 0 * _2X, 5, 5, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C57_DIE, PO_C57_DIE, PO_C57_DIE, PO_C57_DIE, PO_C57_DIE, PO_C57_DIE, PO_C57_DIE, PO_C57_DIE,
	PO_C57_DIE, PO_C57_DIE, PO_C57_DIE, PO_C57_DIE, PO_C57_DIE, PO_C57_DIE, PO_C57_DIE, PO_C57_DIE,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	NPCMOVE_STAND,	NPCMOVE_WALKSLOW,	0,	0,	RANDOM,	30,
	NPCMOVE_WALKSLOW,	NPCMOVE_STAND,	0,	0,	RANDOM,	30,
	-1,
};

const signed short c58mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C58_N0, PO_C58_N0_1, PO_C58_N0_2, PO_C58_N0_3, PO_C58_N1, PO_C58_N1_1, PO_C58_N1_2, PO_C58_N1_3,
	PO_C58_N2, PO_C58_N2_1, PO_C58_N2_2, PO_C58_N2_3, PO_C58_N3, PO_C58_N3_1, PO_C58_N3_2, PO_C58_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C58_W0, PO_C58_W0, PO_C58_W0_1, PO_C58_W0_1, PO_C58_W0_2, PO_C58_W0_2, PO_C58_W0_3, PO_C58_W0_3,
	PO_C58_W1, PO_C58_W1, PO_C58_W1_W2_1, PO_C58_W1_W2_1, PO_C58_W1_W2_2, PO_C58_W1_W2_2, PO_C58_W1_W2_3, PO_C58_W1_W2_3,
	PO_C58_W2, PO_C58_W2, PO_C58_W2_1, PO_C58_W2_1, PO_C58_W2_2, PO_C58_W2_2, PO_C58_W2_3, PO_C58_W2_3,
	PO_C58_W1, PO_C58_W1, PO_C58_W1_W0_1, PO_C58_W1_W0_1, PO_C58_W1_W0_2, PO_C58_W1_W0_2, PO_C58_W1_W0_3, PO_C58_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C58_W0, PO_C58_W0_1, PO_C58_W0_2, PO_C58_W0_3, PO_C58_W1, PO_C58_W1_W2_1, PO_C58_W1_W2_2, PO_C58_W1_W2_3,
	PO_C58_W2, PO_C58_W2_1, PO_C58_W2_2, PO_C58_W2_3, PO_C58_W1, PO_C58_W1_W0_1, PO_C58_W1_W0_2, PO_C58_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	NPCMOVE_STAND,	NPCMOVE_WALKSLOW,	0,	0,	RANDOM,	30,
	NPCMOVE_WALKSLOW,	NPCMOVE_STAND,	0,	0,	RANDOM,	30,
	-1,
};

const signed short c59mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C59_N0, PO_C59_N0_1, PO_C59_N0_2, PO_C59_N0_3, PO_C59_N1, PO_C59_N1_1, PO_C59_N1_2, PO_C59_N1_3,
	PO_C59_N2, PO_C59_N2_1, PO_C59_N2_2, PO_C59_N2_3, PO_C59_N3, PO_C59_N3_1, PO_C59_N3_2, PO_C59_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C59_W0, PO_C59_W0, PO_C59_W0_1, PO_C59_W0_1, PO_C59_W0_2, PO_C59_W0_2, PO_C59_W0_3, PO_C59_W0_3,
	PO_C59_W1, PO_C59_W1, PO_C59_W1_W2_1, PO_C59_W1_W2_1, PO_C59_W1_W2_2, PO_C59_W1_W2_2, PO_C59_W1_W2_3, PO_C59_W1_W2_3,
	PO_C59_W2, PO_C59_W2, PO_C59_W2_1, PO_C59_W2_1, PO_C59_W2_2, PO_C59_W2_2, PO_C59_W2_3, PO_C59_W2_3,
	PO_C59_W1, PO_C59_W1, PO_C59_W1_W0_1, PO_C59_W1_W0_1, PO_C59_W1_W0_2, PO_C59_W1_W0_2, PO_C59_W1_W0_3, PO_C59_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C59_W1, PO_C59_W1_W2_1, PO_C59_W1_W2_2, PO_C59_W1_W2_3, PO_C59_W2, PO_C59_W2_1, PO_C59_W2_2, PO_C59_W2_3,
	PO_C59_W1, PO_C59_W1_W0_1, PO_C59_W1_W0_2, PO_C59_W1_W0_3, PO_C59_W0, PO_C59_W0_1, PO_C59_W0_2, PO_C59_W0_3,	//상태 프레임별 모션
	-1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X,
	-1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	NPCMOVE_STAND,	NPCMOVE_WALKSLOW,	0,	0,	RANDOM,	33,
	NPCMOVE_WALKSLOW,	NPCMOVE_STAND,	0,	0,	RANDOM,	15,
	-1,
};

const signed short c60mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C60_N0, PO_C60_N0_1, PO_C60_N0_2, PO_C60_N0_3, PO_C60_N1, PO_C60_N1_1, PO_C60_N1_2, PO_C60_N1_3,
	PO_C60_N2, PO_C60_N2_1, PO_C60_N2_2, PO_C60_N2_3, PO_C60_N3, PO_C60_N3_1, PO_C60_N3_2, PO_C60_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C60_W0, PO_C60_W0, PO_C60_W0_1, PO_C60_W0_1, PO_C60_W0_2, PO_C60_W0_2, PO_C60_W0_3, PO_C60_W0_3,
	PO_C60_W1, PO_C60_W1, PO_C60_W1_W2_1, PO_C60_W1_W2_1, PO_C60_W1_W2_2, PO_C60_W1_W2_2, PO_C60_W1_W2_3, PO_C60_W1_W2_3,
	PO_C60_W2, PO_C60_W2, PO_C60_W2_1, PO_C60_W2_1, PO_C60_W2_2, PO_C60_W2_2, PO_C60_W2_3, PO_C60_W2_3,
	PO_C60_W1, PO_C60_W1, PO_C60_W1_W0_1, PO_C60_W1_W0_1, PO_C60_W1_W0_2, PO_C60_W1_W0_2, PO_C60_W1_W0_3, PO_C60_W1_W0_3,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	NPCMOVE_STAND,	NPCMOVE_WALKSLOW,	0,	0,	RANDOM,	33,
	NPCMOVE_WALKSLOW,	NPCMOVE_STAND,	0,	0,	RANDOM,	33,
	-1,
};

const signed short c61mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C61_N0, PO_C61_N0_1, PO_C61_N0_2, PO_C61_N0_3, PO_C61_N1, PO_C61_N1_1, PO_C61_N1_2, PO_C61_N1_3,
	PO_C61_N2, PO_C61_N2_1, PO_C61_N2_2, PO_C61_N2_3, PO_C61_N3, PO_C61_N3_1, PO_C61_N3_2, PO_C61_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C61_W0, PO_C61_W0, PO_C61_W0_1, PO_C61_W0_1, PO_C61_W0_2, PO_C61_W0_2, PO_C61_W0_3, PO_C61_W0_3,
	PO_C61_W1, PO_C61_W1, PO_C61_W1_W2_1, PO_C61_W1_W2_1, PO_C61_W1_W2_2, PO_C61_W1_W2_2, PO_C61_W1_W2_3, PO_C61_W1_W2_3,
	PO_C61_W2, PO_C61_W2, PO_C61_W2_1, PO_C61_W2_1, PO_C61_W2_2, PO_C61_W2_2, PO_C61_W2_3, PO_C61_W2_3,
	PO_C61_W1, PO_C61_W1, PO_C61_W1_W0_1, PO_C61_W1_W0_1, PO_C61_W1_W0_2, PO_C61_W1_W0_2, PO_C61_W1_W0_3, PO_C61_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	7, 7, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C61_W0, PO_C61_W0_1, PO_C61_W0_2, PO_C61_W0_3, PO_C61_W1, PO_C61_W1_W2_1, PO_C61_W1_W2_2, PO_C61_W1_W2_3,
	PO_C61_W2, PO_C61_W2_1, PO_C61_W2_2, PO_C61_W2_3, PO_C61_W1, PO_C61_W1_W0_1, PO_C61_W1_W0_2, PO_C61_W1_W0_3,	//상태 프레임별 모션
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 4 * _2X, 4 * _2X, 0 * _2X, 0 * _2X,
	9, 9, 0 * _2X, 0 * _2X, 3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C61_D0, PO_C61_D0, PO_C61_D0, PO_C61_D0, PO_C61_D0, PO_C61_D0, PO_C61_D0, PO_C61_D0,
	PO_C61_D0, PO_C61_D0, PO_C61_D0, PO_C61_D0, PO_C61_D0, PO_C61_D0, PO_C61_D0, PO_C61_D0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	NPCMOVE_STAND,	NPCMOVE_WALKSLOW,	0,	0,	RANDOM,	33,
	NPCMOVE_WALKSLOW,	NPCMOVE_STAND,	0,	0,	RANDOM,	33,
	-1,
};

const signed short c62mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C62_N0, PO_C62_N0_1, PO_C62_N0_2, PO_C62_N0_3, PO_C62_N1, PO_C62_N1_1, PO_C62_N1_2, PO_C62_N1_3,
	PO_C62_N2, PO_C62_N2_1, PO_C62_N2_2, PO_C62_N2_3, PO_C62_N3, PO_C62_N3_1, PO_C62_N3_2, PO_C62_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C62_W0, PO_C62_W0, PO_C62_W0_1, PO_C62_W0_1, PO_C62_W0_2, PO_C62_W0_2, PO_C62_W0_3, PO_C62_W0_3,
	PO_C62_W1, PO_C62_W1, PO_C62_W1_W2_1, PO_C62_W1_W2_1, PO_C62_W1_W2_2, PO_C62_W1_W2_2, PO_C62_W1_W2_3, PO_C62_W1_W2_3,
	PO_C62_W2, PO_C62_W2, PO_C62_W2_1, PO_C62_W2_1, PO_C62_W2_2, PO_C62_W2_2, PO_C62_W2_3, PO_C62_W2_3,
	PO_C62_W1, PO_C62_W1, PO_C62_W1_W0_1, PO_C62_W1_W0_1, PO_C62_W1_W0_2, PO_C62_W1_W0_2, PO_C62_W1_W0_3, PO_C62_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C62_W0, PO_C62_W0_1, PO_C62_W0_2, PO_C62_W0_3, PO_C62_W1, PO_C62_W1_W2_1, PO_C62_W1_W2_2, PO_C62_W1_W2_3,
	PO_C62_W2, PO_C62_W2_1, PO_C62_W2_2, PO_C62_W2_3, PO_C62_W1, PO_C62_W1_W0_1, PO_C62_W1_W0_2, PO_C62_W1_W0_3,	//상태 프레임별 모션
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C62_D, PO_C62_D, PO_C62_D, PO_C62_D, PO_C62_D, PO_C62_D, PO_C62_D, PO_C62_D,
	PO_C62_D, PO_C62_D, PO_C62_D, PO_C62_D, PO_C62_D, PO_C62_D, PO_C62_D, PO_C62_D,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c63mv[] = {
	//상태 데이터
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C63_N0, PO_C63_N0_1, PO_C63_N0_2, PO_C63_N0_3, PO_C63_N1, PO_C63_N1_1, PO_C63_N1_2, PO_C63_N1_3,
	PO_C63_N2, PO_C63_N2, PO_C63_N2, PO_C63_N2, PO_C63_N2_1, PO_C63_N2_1, PO_C63_N2_1, PO_C63_N2_1,
	PO_C63_N2_2, PO_C63_N2_2, PO_C63_N2_2, PO_C63_N2_2, PO_C63_N2_3, PO_C63_N2_3, PO_C63_N2_3, PO_C63_N2_3,
	PO_C63_N3, PO_C63_N3, PO_C63_N3_1, PO_C63_N3_1, PO_C63_N3_2, PO_C63_N3_2, PO_C63_N3_3, PO_C63_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c64mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C64_N0, PO_C64_N0_1, PO_C64_N0_2, PO_C64_N0_3, PO_C64_N1, PO_C64_N1_1, PO_C64_N1_2, PO_C64_N1_3,
	PO_C64_N2, PO_C64_N2_1, PO_C64_N2_2, PO_C64_N2_3, PO_C64_N3, PO_C64_N3_1, PO_C64_N3_2, PO_C64_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C64_W0, PO_C64_W0, PO_C64_W0_1, PO_C64_W0_1, PO_C64_W0_2, PO_C64_W0_2, PO_C64_W0_3, PO_C64_W0_3,
	PO_C64_W1, PO_C64_W1, PO_C64_W1_W2_1, PO_C64_W1_W2_1, PO_C64_W1_W2_2, PO_C64_W1_W2_2, PO_C64_W1_W2_3, PO_C64_W1_W2_3,
	PO_C64_W2, PO_C64_W2, PO_C64_W2_1, PO_C64_W2_1, PO_C64_W2_2, PO_C64_W2_2, PO_C64_W2_3, PO_C64_W2_3,
	PO_C64_W1, PO_C64_W1, PO_C64_W1_W0_1, PO_C64_W1_W0_1, PO_C64_W1_W0_2, PO_C64_W1_W0_2, PO_C64_W1_W0_3, PO_C64_W1_W0_3,	//상태 프레임별 모션
	3, 3, 0 * _2X, 0 * _2X, 5, 5, 0 * _2X, 0 * _2X,
	3, 3, 0 * _2X, 0 * _2X, 5, 5, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 5, 5, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 5, 5, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	NPCMOVE_STAND,	NPCMOVE_WALKSLOW,	0,	0,	RANDOM,	30,
	NPCMOVE_WALKSLOW,	NPCMOVE_STAND,	0,	0,	RANDOM,	40,
	-1,
};

const signed short c65mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C65_N0, PO_C65_N0_1, PO_C65_N0_2, PO_C65_N0_3, PO_C65_N1, PO_C65_N1_1, PO_C65_N1_2, PO_C65_N1_3,
	PO_C65_N2, PO_C65_N2_1, PO_C65_N2_2, PO_C65_N2_3, PO_C65_N3, PO_C65_N3_1, PO_C65_N3_2, PO_C65_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C65_W0, PO_C65_W0, PO_C65_W0_1, PO_C65_W0_1, PO_C65_W0_2, PO_C65_W0_2, PO_C65_W0_3, PO_C65_W0_3,
	PO_C65_W1, PO_C65_W1, PO_C65_W1_W2_1, PO_C65_W1_W2_1, PO_C65_W1_W2_2, PO_C65_W1_W2_2, PO_C65_W1_W2_3, PO_C65_W1_W2_3,
	PO_C65_W2, PO_C65_W2, PO_C65_W2_1, PO_C65_W2_1, PO_C65_W2_2, PO_C65_W2_2, PO_C65_W2_3, PO_C65_W2_3,
	PO_C65_W1, PO_C65_W1, PO_C65_W1_W0_1, PO_C65_W1_W0_1, PO_C65_W1_W0_2, PO_C65_W1_W0_2, PO_C65_W1_W0_3, PO_C65_W1_W0_3,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3, 3, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3, 3, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	NPCMOVE_STAND,	NPCMOVE_WALKSLOW,	0,	0,	RANDOM,	33,
	NPCMOVE_WALKSLOW,	NPCMOVE_STAND,	0,	0,	RANDOM,	33,
	-1,
};

const signed short c66mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C66_N0, PO_C66_N0_1, PO_C66_N0_2, PO_C66_N0_3, PO_C66_N1, PO_C66_N1_1, PO_C66_N1_2, PO_C66_N1_3,
	PO_C66_N2, PO_C66_N2_1, PO_C66_N2_2, PO_C66_N2_3, PO_C66_N3, PO_C66_N3_1, PO_C66_N3_2, PO_C66_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C66_W0, PO_C66_W0, PO_C66_W0_1, PO_C66_W0_1, PO_C66_W0_2, PO_C66_W0_2, PO_C66_W0_3, PO_C66_W0_3,
	PO_C66_W1, PO_C66_W1, PO_C66_W1_1, PO_C66_W1_1, PO_C66_W1_2, PO_C66_W1_2, PO_C66_W1_3, PO_C66_W1_3,
	PO_C66_W2, PO_C66_W2, PO_C66_W2_1, PO_C66_W2_1, PO_C66_W2_2, PO_C66_W2_2, PO_C66_W2_3, PO_C66_W2_3,
	PO_C66_W3, PO_C66_W3, PO_C66_W3_1, PO_C66_W3_1, PO_C66_W3_2, PO_C66_W3_2, PO_C66_W3_3, PO_C66_W3_3,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 3, 3, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 3, 3, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 3, 3, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 3, 3, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	NPCMOVE_STAND,	NPCMOVE_WALKSLOW,	0,	0,	RANDOM,	30,
	NPCMOVE_WALKSLOW,	NPCMOVE_STAND,	0,	0,	RANDOM,	30,
	-1,
};

const signed short c67mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C67_N0, PO_C67_N0_1, PO_C67_N0_2, PO_C67_N0_3, PO_C67_N1, PO_C67_N1_1, PO_C67_N1_2, PO_C67_N1_3,
	PO_C67_N2, PO_C67_N2_1, PO_C67_N2_2, PO_C67_N2_3, PO_C67_N3, PO_C67_N3_1, PO_C67_N3_2, PO_C67_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c68mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C68_N0, PO_C68_N0_1, PO_C68_N0_2, PO_C68_N0_3, PO_C68_N1, PO_C68_N1_1, PO_C68_N1_2, PO_C68_N1_3,
	PO_C68_N2, PO_C68_N2_1, PO_C68_N2_2, PO_C68_N2_3, PO_C68_N3, PO_C68_N3_1, PO_C68_N3_2, PO_C68_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c69mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C69_N0, PO_C69_N0_1, PO_C69_N0_2, PO_C69_N0_3, PO_C69_N1, PO_C69_N1_1, PO_C69_N1_2, PO_C69_N1_3,
	PO_C69_N2, PO_C69_N2_1, PO_C69_N2_2, PO_C69_N2_3, PO_C69_N3, PO_C69_N3_1, PO_C69_N3_2, PO_C69_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c70mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C70_N0, PO_C70_N0_1, PO_C70_N0_2, PO_C70_N0_3, PO_C70_N1, PO_C70_N1_1, PO_C70_N1_2, PO_C70_N1_3,
	PO_C70_N2, PO_C70_N2_1, PO_C70_N2_2, PO_C70_N2_3, PO_C70_N3, PO_C70_N3_1, PO_C70_N3_2, PO_C70_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c71mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C71_N0, PO_C71_N0_1, PO_C71_N0_2, PO_C71_N0_3, PO_C71_N1, PO_C71_N1_1, PO_C71_N1_2, PO_C71_N1_3,
	PO_C71_N2, PO_C71_N2_1, PO_C71_N2_2, PO_C71_N2_3, PO_C71_N3, PO_C71_N3_1, PO_C71_N3_2, PO_C71_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C71_W0, PO_C71_W0, PO_C71_W0_1, PO_C71_W0_1, PO_C71_W0_2, PO_C71_W0_2, PO_C71_W0_3, PO_C71_W0_3,
	PO_C71_W1, PO_C71_W1, PO_C71_W1_W2_1, PO_C71_W1_W2_1, PO_C71_W1_W2_2, PO_C71_W1_W2_2, PO_C71_W1_W2_3, PO_C71_W1_W2_3,
	PO_C71_W2, PO_C71_W2, PO_C71_W2_1, PO_C71_W2_1, PO_C71_W2_2, PO_C71_W2_2, PO_C71_W2_3, PO_C71_W2_3,
	PO_C71_W1, PO_C71_W1, PO_C71_W1_W0_1, PO_C71_W1_W0_1, PO_C71_W1_W0_2, PO_C71_W1_W0_2, PO_C71_W1_W0_3, PO_C71_W1_W0_3,	//상태 프레임별 모션
	3, 3, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3, 3, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	NPCMOVE_STAND,	NPCMOVE_WALKSLOW,	0,	0,	RANDOM,	30,
	NPCMOVE_WALKSLOW,	NPCMOVE_STAND,	0,	0,	RANDOM,	30,
	-1,
};

const signed short c72mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C72_N0, PO_C72_N0_1, PO_C72_N0_2, PO_C72_N0_3, PO_C72_N1, PO_C72_N1_1, PO_C72_N1_2, PO_C72_N1_3,
	PO_C72_N2, PO_C72_N2_1, PO_C72_N2_2, PO_C72_N2_3, PO_C72_N3, PO_C72_N3_1, PO_C72_N3_2, PO_C72_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C72_W0, PO_C72_W0, PO_C72_W0_1, PO_C72_W0_1, PO_C72_W0_2, PO_C72_W0_2, PO_C72_W0_3, PO_C72_W0_3,
	PO_C72_W1, PO_C72_W1, PO_C72_W1_W2_1, PO_C72_W1_W2_1, PO_C72_W1_W2_2, PO_C72_W1_W2_2, PO_C72_W1_W2_3, PO_C72_W1_W2_3,
	PO_C72_W2, PO_C72_W2, PO_C72_W2_1, PO_C72_W2_1, PO_C72_W2_2, PO_C72_W2_2, PO_C72_W2_3, PO_C72_W2_3,
	PO_C72_W1, PO_C72_W1, PO_C72_W1_W0_1, PO_C72_W1_W0_1, PO_C72_W1_W0_2, PO_C72_W1_W0_2, PO_C72_W1_W0_3, PO_C72_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	NPCMOVE_STAND,	NPCMOVE_WALKSLOW,	0,	0,	RANDOM,	30,
	NPCMOVE_WALKSLOW,	NPCMOVE_STAND,	0,	0,	RANDOM,	45,
	-1,
};

const signed short c73mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C73_N0, PO_C73_N0_1, PO_C73_N0_2, PO_C73_N0_3, PO_C73_N1, PO_C73_N1_N2_1, PO_C73_N1_N2_2, PO_C73_N1_N2_3,
	PO_C73_N2, PO_C73_N2_1, PO_C73_N2_2, PO_C73_N2_3, PO_C73_N1, PO_C73_N1_N0_1, PO_C73_N1_N0_2, PO_C73_N1_N0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C73_READY, PO_C73_READY, PO_C73_READY, PO_C73_READY, PO_C73_READY, PO_C73_READY, PO_C73_READY, PO_C73_READY,
	PO_C73_READY, PO_C73_READY, PO_C73_READY, PO_C73_READY, PO_C73_READY, PO_C73_READY, PO_C73_READY, PO_C73_READY,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	64,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C73_READY, PO_C73_READY, PO_C73_READY, PO_C73_READY, PO_C73_READY_BOX0_1, PO_C73_READY_BOX0_1, PO_C73_READY_BOX0_1, PO_C73_READY_BOX0_1,
	PO_C73_READY_BOX0_2, PO_C73_READY_BOX0_2, PO_C73_READY_BOX0_2, PO_C73_READY_BOX0_2, PO_C73_READY_BOX0_3, PO_C73_READY_BOX0_3, PO_C73_READY_BOX0_3, PO_C73_READY_BOX0_3,
	PO_C73_BOX0, PO_C73_BOX0_1, PO_C73_BOX0_2, PO_C73_BOX0_3, PO_C73_BOX1, PO_C73_BOX1_1, PO_C73_BOX1_2, PO_C73_BOX1_3,
	PO_C73_BOX2, PO_C73_BOX2_1, PO_C73_BOX2_2, PO_C73_BOX2_3, PO_C73_BOX3, PO_C73_BOX3_1, PO_C73_BOX3_2, PO_C73_BOX3_3,
	PO_C73_BOX4, PO_C73_BOX4_1, PO_C73_BOX4_2, PO_C73_BOX4_3, PO_C73_BOX5, PO_C73_BOX5, PO_C73_BOX5_1, PO_C73_BOX5_1,
	PO_C73_BOX5_2, PO_C73_BOX5_2, PO_C73_BOX5_3, PO_C73_BOX5_3, PO_C73_BOX6, PO_C73_BOX6_BOX5_1, PO_C73_BOX6_BOX5_2, PO_C73_BOX6_BOX5_3,
	PO_C73_BOX5, PO_C73_BOX5_1, PO_C73_BOX5_2, PO_C73_BOX5_3, PO_C73_BOX6, PO_C73_BOX6_BOX5_1, PO_C73_BOX6_BOX5_2, PO_C73_BOX6_BOX5_3,
	PO_C73_BOX5, PO_C73_BOX5_1, PO_C73_BOX5_2, PO_C73_BOX5_3, PO_C73_BOX6, PO_C73_BOX6_READY_1, PO_C73_BOX6_READY_2, PO_C73_BOX6_READY_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C73_BOXGIVE0, PO_C73_BOXGIVE0_1, PO_C73_BOXGIVE0_2, PO_C73_BOXGIVE0_3, PO_C73_BOXGIVE1, PO_C73_BOXGIVE1_1, PO_C73_BOXGIVE1_2, PO_C73_BOXGIVE1_3,
	PO_C73_BOXGIVE2, PO_C73_BOXGIVE2_1, PO_C73_BOXGIVE2_2, PO_C73_BOXGIVE2_3, PO_C73_BOXGIVE3, PO_C73_BOXGIVE3_1, PO_C73_BOXGIVE3_2, PO_C73_BOXGIVE3_3,
	PO_C73_BOXGIVE0, PO_C73_BOXGIVE0_1, PO_C73_BOXGIVE0_2, PO_C73_BOXGIVE0_3, PO_C73_BOXGIVE1, PO_C73_BOXGIVE1_1, PO_C73_BOXGIVE1_2, PO_C73_BOXGIVE1_3,
	PO_C73_BOXGIVE2, PO_C73_BOXGIVE2_1, PO_C73_BOXGIVE2_2, PO_C73_BOXGIVE2_3, PO_C73_BOXGIVE3, PO_C73_BOXGIVE3_1, PO_C73_BOXGIVE3_2, PO_C73_BOXGIVE3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	64,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C73_READY, PO_C73_READY, PO_C73_READY, PO_C73_READY, PO_C73_READY_FISH0_1, PO_C73_READY_FISH0_1, PO_C73_READY_FISH0_1, PO_C73_READY_FISH0_1,
	PO_C73_READY_FISH0_2, PO_C73_READY_FISH0_2, PO_C73_READY_FISH0_2, PO_C73_READY_FISH0_2, PO_C73_READY_FISH0_3, PO_C73_READY_FISH0_3, PO_C73_READY_FISH0_3, PO_C73_READY_FISH0_3,
	PO_C73_FISH0, PO_C73_FISH0_1, PO_C73_FISH0_2, PO_C73_FISH0_3, PO_C73_FISH1, PO_C73_FISH1_1, PO_C73_FISH1_2, PO_C73_FISH1_3,
	PO_C73_FISH2, PO_C73_FISH2_1, PO_C73_FISH2_2, PO_C73_FISH2_3, PO_C73_FISH3, PO_C73_FISH3_1, PO_C73_FISH3_2, PO_C73_FISH3_3,
	PO_C73_FISH4, PO_C73_FISH4_1, PO_C73_FISH4_2, PO_C73_FISH4_3, PO_C73_FISH5, PO_C73_FISH5, PO_C73_FISH5_1, PO_C73_FISH5_1,
	PO_C73_FISH5_2, PO_C73_FISH5_2, PO_C73_FISH5_3, PO_C73_FISH5_3, PO_C73_FISH6, PO_C73_FISH6_FISH5_1, PO_C73_FISH6_FISH5_2, PO_C73_FISH6_FISH5_3,
	PO_C73_FISH5, PO_C73_FISH5_1, PO_C73_FISH5_2, PO_C73_FISH5_3, PO_C73_FISH6, PO_C73_FISH6_FISH5_1, PO_C73_FISH6_FISH5_2, PO_C73_FISH6_FISH5_3,
	PO_C73_FISH5, PO_C73_FISH5_1, PO_C73_FISH5_2, PO_C73_FISH5_3, PO_C73_FISH6, PO_C73_FISH6_READY_1, PO_C73_FISH6_READY_2, PO_C73_FISH6_READY_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C73_FISHGIVE0, PO_C73_FISHGIVE0_1, PO_C73_FISHGIVE0_2, PO_C73_FISHGIVE0_3, PO_C73_FISHGIVE1, PO_C73_FISHGIVE1_1, PO_C73_FISHGIVE1_2, PO_C73_FISHGIVE1_3,
	PO_C73_FISHGIVE2, PO_C73_FISHGIVE2_1, PO_C73_FISHGIVE2_2, PO_C73_FISHGIVE2_3, PO_C73_FISHGIVE3, PO_C73_FISHGIVE3_1, PO_C73_FISHGIVE3_2, PO_C73_FISHGIVE3_3,
	PO_C73_FISHGIVE0, PO_C73_FISHGIVE0_1, PO_C73_FISHGIVE0_2, PO_C73_FISHGIVE0_3, PO_C73_FISHGIVE1, PO_C73_FISHGIVE1_1, PO_C73_FISHGIVE1_2, PO_C73_FISHGIVE1_3,
	PO_C73_FISHGIVE2, PO_C73_FISHGIVE2_1, PO_C73_FISHGIVE2_2, PO_C73_FISHGIVE2_3, PO_C73_FISHGIVE3, PO_C73_FISHGIVE3_1, PO_C73_FISHGIVE3_2, PO_C73_FISHGIVE3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c74mv[] = {
	//상태 데이터
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C74_N0, PO_C74_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c75mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C75_N0, PO_C75_N0_1, PO_C75_N0_2, PO_C75_N0_3, PO_C75_N1, PO_C75_N1_1, PO_C75_N1_2, PO_C75_N1_3,
	PO_C75_N2, PO_C75_N2_1, PO_C75_N2_2, PO_C75_N2_3, PO_C75_N3, PO_C75_N3_1, PO_C75_N3_2, PO_C75_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c76mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C76_N0, PO_C76_N0_1, PO_C76_N0_2, PO_C76_N0_3, PO_C76_N1, PO_C76_N1_1, PO_C76_N1_2, PO_C76_N1_3,
	PO_C76_N2, PO_C76_N2_1, PO_C76_N2_2, PO_C76_N2_3, PO_C76_N3, PO_C76_N3_1, PO_C76_N3_2, PO_C76_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C76_W0, PO_C76_W0, PO_C76_W0_1, PO_C76_W0_1, PO_C76_W0_2, PO_C76_W0_2, PO_C76_W0_3, PO_C76_W0_3,
	PO_C76_W1, PO_C76_W1, PO_C76_W1_W2_1, PO_C76_W1_W2_1, PO_C76_W1_W2_2, PO_C76_W1_W2_2, PO_C76_W1_W2_3, PO_C76_W1_W2_3,
	PO_C76_W2, PO_C76_W2, PO_C76_W2_1, PO_C76_W2_1, PO_C76_W2_2, PO_C76_W2_2, PO_C76_W2_3, PO_C76_W2_3,
	PO_C76_W1, PO_C76_W1, PO_C76_W1_W0_1, PO_C76_W1_W0_1, PO_C76_W1_W0_2, PO_C76_W1_W0_2, PO_C76_W1_W0_3, PO_C76_W1_W0_3,	//상태 프레임별 모션
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C76_W0, PO_C76_W0_1, PO_C76_W0_2, PO_C76_W0_3, PO_C76_W1, PO_C76_W1_W2_1, PO_C76_W1_W2_2, PO_C76_W1_W2_3,
	PO_C76_W2, PO_C76_W2_1, PO_C76_W2_2, PO_C76_W2_3, PO_C76_W1, PO_C76_W1_W0_1, PO_C76_W1_W0_2, PO_C76_W1_W0_3,	//상태 프레임별 모션
	9, 9, 0 * _2X, 0 * _2X, 3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X,
	9, 9, 0 * _2X, 0 * _2X, 3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C76_D, PO_C76_D, PO_C76_D, PO_C76_D, PO_C76_D, PO_C76_D, PO_C76_D, PO_C76_D,
	PO_C76_D, PO_C76_D, PO_C76_D, PO_C76_D, PO_C76_D, PO_C76_D, PO_C76_D, PO_C76_D,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	20,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C76_PUNCH0, PO_C76_PUNCH0_1, PO_C76_PUNCH0_2, PO_C76_PUNCH0_3, PO_C76_PUNCH1, PO_C76_PUNCH1, PO_C76_PUNCH1, PO_C76_PUNCH1,
	PO_C76_PUNCH1_1, PO_C76_PUNCH1_1, PO_C76_PUNCH1_1, PO_C76_PUNCH1_1, PO_C76_PUNCH1_2, PO_C76_PUNCH1_2, PO_C76_PUNCH1_2, PO_C76_PUNCH1_2,
	PO_C76_PUNCH1_3, PO_C76_PUNCH1_3, PO_C76_PUNCH1_3, PO_C76_PUNCH1_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C76_SHAKEHAND0, PO_C76_SHAKEHAND0, PO_C76_SHAKEHAND0_1, PO_C76_SHAKEHAND0_1, PO_C76_SHAKEHAND0_2, PO_C76_SHAKEHAND0_2, PO_C76_SHAKEHAND0_3, PO_C76_SHAKEHAND0_3,
	PO_C76_SHAKEHAND1, PO_C76_SHAKEHAND1, PO_C76_SHAKEHAND1_1, PO_C76_SHAKEHAND1_1, PO_C76_SHAKEHAND1_2, PO_C76_SHAKEHAND1_2, PO_C76_SHAKEHAND1_3, PO_C76_SHAKEHAND1_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

// 도벨
const signed short c77mv[] = {
	//상태 데이터
	//DOBEL_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C77_N0, PO_C77_N0_1, PO_C77_N0_2, PO_C77_N0_3, PO_C77_N1, PO_C77_N1_1, PO_C77_N1_2, PO_C77_N1_3,
	PO_C77_N2, PO_C77_N2_1, PO_C77_N2_2, PO_C77_N2_3, PO_C77_N3, PO_C77_N3_1, PO_C77_N3_2, PO_C77_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DOBEL_MOVE
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C77_W0, PO_C77_W0, PO_C77_W0_1, PO_C77_W0_1, PO_C77_W0_2, PO_C77_W0_2, PO_C77_W0_3, PO_C77_W0_3,
	PO_C77_W1, PO_C77_W1, PO_C77_W1_W2_1, PO_C77_W1_W2_1, PO_C77_W1_W2_2, PO_C77_W1_W2_2, PO_C77_W1_W2_3, PO_C77_W1_W2_3,
	PO_C77_W2, PO_C77_W2, PO_C77_W2_1, PO_C77_W2_1, PO_C77_W2_2, PO_C77_W2_2, PO_C77_W2_3, PO_C77_W2_3,
	PO_C77_W1, PO_C77_W1, PO_C77_W1_W0_1, PO_C77_W1_W0_1, PO_C77_W1_W0_2, PO_C77_W1_W0_2, PO_C77_W1_W0_3, PO_C77_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DOBEL_NEUTRAL_SWORD
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C77_N2_SWORD, PO_C77_N2_SWORD_N1_SWORD_1, PO_C77_N2_SWORD_N1_SWORD_2, PO_C77_N2_SWORD_N1_SWORD_3, PO_C77_N1_SWORD, PO_C77_N1_SWORD_1, PO_C77_N1_SWORD_2, PO_C77_N1_SWORD_3,
	PO_C77_N2_SWORD, PO_C77_N2_SWORD_N3_SWORD_1, PO_C77_N2_SWORD_N3_SWORD_2, PO_C77_N2_SWORD_N3_SWORD_3, PO_C77_N3_SWORD, PO_C77_N3_SWORD_1, PO_C77_N3_SWORD_2, PO_C77_N3_SWORD_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DOBEL_DOWN
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C77_D0, PO_C77_D0, PO_C77_D0, PO_C77_D0, PO_C77_D0, PO_C77_D0, PO_C77_D0, PO_C77_D0,
	PO_C77_D0, PO_C77_D0, PO_C77_D0, PO_C77_D0, PO_C77_D0, PO_C77_D0, PO_C77_D0, PO_C77_D0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DOBEL_DOWN_HEAD
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C77_D1, PO_C77_D1, PO_C77_D1, PO_C77_D1, PO_C77_D1, PO_C77_D1, PO_C77_D1, PO_C77_D1,
	PO_C77_D1, PO_C77_D1, PO_C77_D1, PO_C77_D1, PO_C77_D1, PO_C77_D1, PO_C77_D1, PO_C77_D1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DOBEL_VICTORY
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C77_HAPPY0, PO_C77_HAPPY0, PO_C77_HAPPY0, PO_C77_HAPPY0, PO_C77_HAPPY0, PO_C77_HAPPY0, PO_C77_HAPPY0, PO_C77_HAPPY0,
	PO_C77_HAPPY0, PO_C77_HAPPY0, PO_C77_HAPPY0, PO_C77_HAPPY0, PO_C77_HAPPY0, PO_C77_HAPPY0, PO_C77_HAPPY0, PO_C77_HAPPY0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DOBEL_KNEE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C77_KNEE0, PO_C77_KNEE0, PO_C77_KNEE0, PO_C77_KNEE0, PO_C77_KNEE0, PO_C77_KNEE0, PO_C77_KNEE0, PO_C77_KNEE0,
	PO_C77_KNEE0, PO_C77_KNEE0, PO_C77_KNEE0, PO_C77_KNEE0, PO_C77_KNEE0, PO_C77_KNEE0, PO_C77_KNEE0, PO_C77_KNEE0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DOBEL_SLEEP_CLOSEEYE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C77_HEAD0, PO_C77_HEAD0, PO_C77_HEAD0, PO_C77_HEAD0, PO_C77_HEAD0, PO_C77_HEAD0, PO_C77_HEAD0, PO_C77_HEAD0,
	PO_C77_HEAD0, PO_C77_HEAD0, PO_C77_HEAD0, PO_C77_HEAD0, PO_C77_HEAD0, PO_C77_HEAD0, PO_C77_HEAD0, PO_C77_HEAD0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//DOBEL_SLEEP_OPENEYE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C77_HEAD1, PO_C77_HEAD1, PO_C77_HEAD1, PO_C77_HEAD1, PO_C77_HEAD1, PO_C77_HEAD1, PO_C77_HEAD1, PO_C77_HEAD1,
	PO_C77_HEAD1, PO_C77_HEAD1, PO_C77_HEAD1, PO_C77_HEAD1, PO_C77_HEAD1, PO_C77_HEAD1, PO_C77_HEAD1, PO_C77_HEAD1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

//가젤
const signed short c78mv[] = {
	//상태 데이터
	//GAGEL_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C78_N0, PO_C78_N0_1, PO_C78_N0_2, PO_C78_N0_3, PO_C78_N1, PO_C78_N1_1, PO_C78_N1_2, PO_C78_N1_3,
	PO_C78_N2, PO_C78_N2_1, PO_C78_N2_2, PO_C78_N2_3, PO_C78_N3, PO_C78_N3_1, PO_C78_N3_2, PO_C78_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GAGEL_MOVE
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C78_W0, PO_C78_W0, PO_C78_W0_1, PO_C78_W0_1, PO_C78_W0_2, PO_C78_W0_2, PO_C78_W0_3, PO_C78_W0_3,
	PO_C78_W1, PO_C78_W1, PO_C78_W1_W2_1, PO_C78_W1_W2_1, PO_C78_W1_W2_2, PO_C78_W1_W2_2, PO_C78_W1_W2_3, PO_C78_W1_W2_3,
	PO_C78_W2, PO_C78_W2, PO_C78_W2_1, PO_C78_W2_1, PO_C78_W2_2, PO_C78_W2_2, PO_C78_W2_3, PO_C78_W2_3,
	PO_C78_W1, PO_C78_W1, PO_C78_W1_W0_1, PO_C78_W1_W0_1, PO_C78_W1_W0_2, PO_C78_W1_W0_2, PO_C78_W1_W0_3, PO_C78_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GAGEL_NEUTRAL_SWORD
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C78_N0_SWORD, PO_C78_N0_SWORD_1, PO_C78_N0_SWORD_2, PO_C78_N0_SWORD_3, PO_C78_N1_SWORD, PO_C78_N1_SWORD_1, PO_C78_N1_SWORD_2, PO_C78_N1_SWORD_3,
	PO_C78_N2_SWORD, PO_C78_N2_SWORD_1, PO_C78_N2_SWORD_2, PO_C78_N2_SWORD_3, PO_C78_N3_SWORD, PO_C78_N3_SWORD_1, PO_C78_N3_SWORD_2, PO_C78_N3_SWORD_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GAGEL_DOWN
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C78_D0, PO_C78_D0, PO_C78_D0, PO_C78_D0, PO_C78_D0, PO_C78_D0, PO_C78_D0, PO_C78_D0,
	PO_C78_D0, PO_C78_D0, PO_C78_D0, PO_C78_D0, PO_C78_D0, PO_C78_D0, PO_C78_D0, PO_C78_D0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GAGEL_DOWN_HEAD
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C78_D1, PO_C78_D1, PO_C78_D1, PO_C78_D1, PO_C78_D1, PO_C78_D1, PO_C78_D1, PO_C78_D1,
	PO_C78_D1, PO_C78_D1, PO_C78_D1, PO_C78_D1, PO_C78_D1, PO_C78_D1, PO_C78_D1, PO_C78_D1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GAGEL_VICTORY
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C78_HAPPY, PO_C78_HAPPY, PO_C78_HAPPY, PO_C78_HAPPY, PO_C78_HAPPY, PO_C78_HAPPY, PO_C78_HAPPY, PO_C78_HAPPY,
	PO_C78_HAPPY, PO_C78_HAPPY, PO_C78_HAPPY, PO_C78_HAPPY, PO_C78_HAPPY, PO_C78_HAPPY, PO_C78_HAPPY, PO_C78_HAPPY,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GAGEL_KNEE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C78_KNEE0, PO_C78_KNEE0, PO_C78_KNEE0, PO_C78_KNEE0, PO_C78_KNEE0, PO_C78_KNEE0, PO_C78_KNEE0, PO_C78_KNEE0,
	PO_C78_KNEE0, PO_C78_KNEE0, PO_C78_KNEE0, PO_C78_KNEE0, PO_C78_KNEE0, PO_C78_KNEE0, PO_C78_KNEE0, PO_C78_KNEE0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GAGEL_SLEEP_CLOSEEYE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C78_HEAD0, PO_C78_HEAD0, PO_C78_HEAD0, PO_C78_HEAD0, PO_C78_HEAD0, PO_C78_HEAD0, PO_C78_HEAD0, PO_C78_HEAD0,
	PO_C78_HEAD0, PO_C78_HEAD0, PO_C78_HEAD0, PO_C78_HEAD0, PO_C78_HEAD0, PO_C78_HEAD0, PO_C78_HEAD0, PO_C78_HEAD0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GAGEL_SLEEP_OPENEYE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C78_HEAD1, PO_C78_HEAD1, PO_C78_HEAD1, PO_C78_HEAD1, PO_C78_HEAD1, PO_C78_HEAD1, PO_C78_HEAD1, PO_C78_HEAD1,
	PO_C78_HEAD1, PO_C78_HEAD1, PO_C78_HEAD1, PO_C78_HEAD1, PO_C78_HEAD1, PO_C78_HEAD1, PO_C78_HEAD1, PO_C78_HEAD1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//GAGEL_BOMB
	48,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C78_THROW0, PO_C78_THROW0_1, PO_C78_THROW0_2, PO_C78_THROW0_3, PO_C78_THROW1, PO_C78_THROW1_1, PO_C78_THROW1_2, PO_C78_THROW1_3,
	PO_C78_THROW2, PO_C78_THROW2_1, PO_C78_THROW2_2, PO_C78_THROW2_3, PO_C78_THROW3, PO_C78_THROW3_1, PO_C78_THROW3_2, PO_C78_THROW3_3,
	PO_C78_THROW4, PO_C78_THROW4_1, PO_C78_THROW4_2, PO_C78_THROW4_3, PO_C78_THROW5, PO_C78_THROW5_1, PO_C78_THROW5_2, PO_C78_THROW5_3,
	PO_C78_THROW6, PO_C78_THROW6_1, PO_C78_THROW6_2, PO_C78_THROW6_3, PO_C78_THROW7, PO_C78_THROW7_1, PO_C78_THROW7_2, PO_C78_THROW7_3,
	PO_C78_THROW8, PO_C78_THROW8_1, PO_C78_THROW8_2, PO_C78_THROW8_3, PO_C78_THROW9, PO_C78_THROW9_THROW8_1, PO_C78_THROW9_THROW8_2, PO_C78_THROW9_THROW8_3,
	PO_C78_THROW8, PO_C78_THROW8_1, PO_C78_THROW8_2, PO_C78_THROW8_3, PO_C78_THROW9, PO_C78_THROW9_THROW0_1, PO_C78_THROW9_THROW0_2, PO_C78_THROW9_THROW0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c79mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C79_N0, PO_C79_N0_1, PO_C79_N0_2, PO_C79_N0_3, PO_C79_N1, PO_C79_N1_1, PO_C79_N1_2, PO_C79_N1_3,
	PO_C79_N2, PO_C79_N2_1, PO_C79_N2_2, PO_C79_N2_3, PO_C79_N3, PO_C79_N3_1, PO_C79_N3_2, PO_C79_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C79_W0, PO_C79_W0, PO_C79_W0_1, PO_C79_W0_1, PO_C79_W0_2, PO_C79_W0_2, PO_C79_W0_3, PO_C79_W0_3,
	PO_C79_W1, PO_C79_W1, PO_C79_W1_W2_1, PO_C79_W1_W2_1, PO_C79_W1_W2_2, PO_C79_W1_W2_2, PO_C79_W1_W2_3, PO_C79_W1_W2_3,
	PO_C79_W2, PO_C79_W2, PO_C79_W2_1, PO_C79_W2_1, PO_C79_W2_2, PO_C79_W2_2, PO_C79_W2_3, PO_C79_W2_3,
	PO_C79_W1, PO_C79_W1, PO_C79_W1_W0_1, PO_C79_W1_W0_1, PO_C79_W1_W0_2, PO_C79_W1_W0_2, PO_C79_W1_W0_3, PO_C79_W1_W0_3,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c80mv[] = {
	//상태 데이터
	-1,

	//상태변경
	-1,
};

const signed short c81mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C81_N0, PO_C81_N0_1, PO_C81_N0_2, PO_C81_N0_3, PO_C81_N1, PO_C81_N1_1, PO_C81_N1_2, PO_C81_N1_3,
	PO_C81_N2, PO_C81_N2_1, PO_C81_N2_2, PO_C81_N2_3, PO_C81_N3, PO_C81_N3_1, PO_C81_N3_2, PO_C81_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C81_W0, PO_C81_W0, PO_C81_W0_1, PO_C81_W0_1, PO_C81_W0_2, PO_C81_W0_2, PO_C81_W0_3, PO_C81_W0_3,
	PO_C81_W1, PO_C81_W1, PO_C81_W1_W2_1, PO_C81_W1_W2_1, PO_C81_W1_W2_2, PO_C81_W1_W2_2, PO_C81_W1_W2_3, PO_C81_W1_W2_3,
	PO_C81_W2, PO_C81_W2, PO_C81_W2_1, PO_C81_W2_1, PO_C81_W2_2, PO_C81_W2_2, PO_C81_W2_3, PO_C81_W2_3,
	PO_C81_W1, PO_C81_W1, PO_C81_W1_W0_1, PO_C81_W1_W0_1, PO_C81_W1_W0_2, PO_C81_W1_W0_2, PO_C81_W1_W0_3, PO_C81_W1_W0_3,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C81_W0, PO_C81_W0_1, PO_C81_W0_2, PO_C81_W0_3, PO_C81_W1, PO_C81_W1_W2_1, PO_C81_W1_W2_2, PO_C81_W1_W2_3,
	PO_C81_W2, PO_C81_W2_1, PO_C81_W2_2, PO_C81_W2_3, PO_C81_W1, PO_C81_W1_W0_1, PO_C81_W1_W0_2, PO_C81_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c82mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C82_N0, PO_C82_N0_1, PO_C82_N0_2, PO_C82_N0_3, PO_C82_N1, PO_C82_N1_1, PO_C82_N1_2, PO_C82_N1_3,
	PO_C82_N2, PO_C82_N2_1, PO_C82_N2_2, PO_C82_N2_3, PO_C82_N3, PO_C82_N3_1, PO_C82_N3_2, PO_C82_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c83mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C83_N0, PO_C83_N0_1, PO_C83_N0_2, PO_C83_N0_3, PO_C83_N1, PO_C83_N1_1, PO_C83_N1_2, PO_C83_N1_3,
	PO_C83_N2, PO_C83_N2_1, PO_C83_N2_2, PO_C83_N2_3, PO_C83_N3, PO_C83_N3_1, PO_C83_N3_2, PO_C83_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C83_W0, PO_C83_W0, PO_C83_W0_1, PO_C83_W0_1, PO_C83_W0_2, PO_C83_W0_2, PO_C83_W0_3, PO_C83_W0_3,
	PO_C83_W1, PO_C83_W1, PO_C83_W1_W2_1, PO_C83_W1_W2_1, PO_C83_W1_W2_2, PO_C83_W1_W2_2, PO_C83_W1_W2_3, PO_C83_W1_W2_3,
	PO_C83_W2, PO_C83_W2, PO_C83_W2_1, PO_C83_W2_1, PO_C83_W2_2, PO_C83_W2_2, PO_C83_W2_3, PO_C83_W2_3,
	PO_C83_W1, PO_C83_W1, PO_C83_W1_W0_1, PO_C83_W1_W0_1, PO_C83_W1_W0_2, PO_C83_W1_W0_2, PO_C83_W1_W0_3, PO_C83_W1_W0_3,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c84mv[] = {
	//상태 데이터
	//LUISE_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C84_N0, PO_C84_N0_1, PO_C84_N0_2, PO_C84_N0_3, PO_C84_N1, PO_C84_N1_1, PO_C84_N1_2, PO_C84_N1_3,
	PO_C84_N2, PO_C84_N2_1, PO_C84_N2_2, PO_C84_N2_3, PO_C84_N3, PO_C84_N3_1, PO_C84_N3_2, PO_C84_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LUISE_MOVE
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C84_W0, PO_C84_W0, PO_C84_W0_1, PO_C84_W0_1, PO_C84_W0_2, PO_C84_W0_2, PO_C84_W0_3, PO_C84_W0_3,
	PO_C84_W1, PO_C84_W1, PO_C84_W1_W2_1, PO_C84_W1_W2_1, PO_C84_W1_W2_2, PO_C84_W1_W2_2, PO_C84_W1_W2_3, PO_C84_W1_W2_3,
	PO_C84_W2, PO_C84_W2, PO_C84_W2_1, PO_C84_W2_1, PO_C84_W2_2, PO_C84_W2_2, PO_C84_W2_3, PO_C84_W2_3,
	PO_C84_W1, PO_C84_W1, PO_C84_W1_W0_1, PO_C84_W1_W0_1, PO_C84_W1_W0_2, PO_C84_W1_W0_2, PO_C84_W1_W0_3, PO_C84_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LUISE_ATTACK
	64,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C84_A0, PO_C84_A0_1, PO_C84_A0_2, PO_C84_A0_3, PO_C84_A1, PO_C84_A1_A2_1, PO_C84_A1_A2_2, PO_C84_A1_A2_3,
	PO_C84_A2, PO_C84_A2_A3_1, PO_C84_A2_A3_2, PO_C84_A2_A3_3, PO_C84_A3, PO_C84_A3_1, PO_C84_A3_2, PO_C84_A3_3,
	PO_C84_A4, PO_C84_A4_1, PO_C84_A4_2, PO_C84_A4_3, PO_C84_A5, PO_C84_A5_1, PO_C84_A5_2, PO_C84_A5_3,
	PO_C84_A6, PO_C84_A6_A3_1, PO_C84_A6_A3_2, PO_C84_A6_A3_3, PO_C84_A3, PO_C84_A3_1, PO_C84_A3_2, PO_C84_A3_3,
	PO_C84_A4, PO_C84_A4_1, PO_C84_A4_2, PO_C84_A4_3, PO_C84_A5, PO_C84_A5_1, PO_C84_A5_2, PO_C84_A5_3,
	PO_C84_A6, PO_C84_A6_A1_1, PO_C84_A6_A1_2, PO_C84_A6_A1_3, PO_C84_A1, PO_C84_A1_A7_1, PO_C84_A1_A7_2, PO_C84_A1_A7_3,
	PO_C84_A7, PO_C84_A7_1, PO_C84_A7_2, PO_C84_A7_3, PO_C84_A8, PO_C84_A8_1, PO_C84_A8_2, PO_C84_A8_3,
	PO_C84_A2, PO_C84_A2_A1_1, PO_C84_A2_A1_2, PO_C84_A2_A1_3, PO_C84_A1, PO_C84_A1_A0_1, PO_C84_A1_A0_2, PO_C84_A1_A0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 101 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LUISE_KNEE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C84_KNEE0, PO_C84_KNEE0, PO_C84_KNEE0, PO_C84_KNEE0, PO_C84_KNEE0, PO_C84_KNEE0, PO_C84_KNEE0, PO_C84_KNEE0,
	PO_C84_KNEE0, PO_C84_KNEE0, PO_C84_KNEE0, PO_C84_KNEE0, PO_C84_KNEE0, PO_C84_KNEE0, PO_C84_KNEE0, PO_C84_KNEE0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C84_W0, PO_C84_W0_1, PO_C84_W0_2, PO_C84_W0_3, PO_C84_W1, PO_C84_W1_W2_1, PO_C84_W1_W2_2, PO_C84_W1_W2_3,
	PO_C84_W2, PO_C84_W2_1, PO_C84_W2_2, PO_C84_W2_3, PO_C84_W1, PO_C84_W1_W0_1, PO_C84_W1_W0_2, PO_C84_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c85mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C85_N0, PO_C85_N0_1, PO_C85_N0_2, PO_C85_N0_3, PO_C85_N1, PO_C85_N1_1, PO_C85_N1_2, PO_C85_N1_3,
	PO_C85_N2, PO_C85_N2_1, PO_C85_N2_2, PO_C85_N2_3, PO_C85_N3, PO_C85_N3_1, PO_C85_N3_2, PO_C85_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c86mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C86_N0, PO_C86_N0_1, PO_C86_N0_2, PO_C86_N0_3, PO_C86_N1, PO_C86_N1_N2_1, PO_C86_N1_N2_2, PO_C86_N1_N2_3,
	PO_C86_N2, PO_C86_N2_1, PO_C86_N2_2, PO_C86_N2_3, PO_C86_N3, PO_C86_N3_1, PO_C86_N3_2, PO_C86_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C86_W0, PO_C86_W0, PO_C86_W0_1, PO_C86_W0_1, PO_C86_W0_2, PO_C86_W0_2, PO_C86_W0_3, PO_C86_W0_3,
	PO_C86_W1, PO_C86_W1, PO_C86_W1_W2_1, PO_C86_W1_W2_1, PO_C86_W1_W2_2, PO_C86_W1_W2_2, PO_C86_W1_W2_3, PO_C86_W1_W2_3,
	PO_C86_W2, PO_C86_W2, PO_C86_W2_1, PO_C86_W2_1, PO_C86_W2_2, PO_C86_W2_2, PO_C86_W2_3, PO_C86_W2_3,
	PO_C86_W1, PO_C86_W1, PO_C86_W1_W0_1, PO_C86_W1_W0_1, PO_C86_W1_W0_2, PO_C86_W1_W0_2, PO_C86_W1_W0_3, PO_C86_W1_W0_3,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C86_N0, PO_C86_N0_1, PO_C86_N0_2, PO_C86_N0_3, PO_C86_N1, PO_C86_N1_N2_1, PO_C86_N1_N2_2, PO_C86_N1_N2_3,
	PO_C86_N2, PO_C86_N2_1, PO_C86_N2_2, PO_C86_N2_3, PO_C86_N3, PO_C86_N3_1, PO_C86_N3_2, PO_C86_N3_3,
	PO_C86_N0, PO_C86_N0_1, PO_C86_N0_2, PO_C86_N0_3, PO_C86_N1, PO_C86_N1_N0_1, PO_C86_N1_N0_2, PO_C86_N1_N0_3,	//상태 프레임별 모션
	-1 * _2X, -1 * _2X, 0 * _2X, 0 * _2X, -1 * _2X, -1 * _2X, 0 * _2X, 0 * _2X,
	-1 * _2X, -1 * _2X, 0 * _2X, 0 * _2X, -1 * _2X, -1 * _2X, 0 * _2X, 0 * _2X,
	-1 * _2X, -1 * _2X, 0 * _2X, 0 * _2X, -1 * _2X, -1 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	102 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c87mv[] = {
	//상태 데이터
	64,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C87_N4, PO_C87_N4_1, PO_C87_N4_2, PO_C87_N4_3, PO_C87_N5, PO_C87_N5_N4_1, PO_C87_N5_N4_2, PO_C87_N5_N4_3,
	PO_C87_N4, PO_C87_N4_1, PO_C87_N4_2, PO_C87_N4_3, PO_C87_N5, PO_C87_N5_N6_1, PO_C87_N5_N6_2, PO_C87_N5_N6_3,
	PO_C87_N6, PO_C87_N6_1, PO_C87_N6_2, PO_C87_N6_3, PO_C87_N7, PO_C87_N7_N6_1, PO_C87_N7_N6_2, PO_C87_N7_N6_3,
	PO_C87_N6, PO_C87_N6_1, PO_C87_N6_2, PO_C87_N6_3, PO_C87_N7, PO_C87_N7_N0_1, PO_C87_N7_N0_2, PO_C87_N7_N0_3,
	PO_C87_N0, PO_C87_N0_1, PO_C87_N0_2, PO_C87_N0_3, PO_C87_N1, PO_C87_N1_N0_1, PO_C87_N1_N0_2, PO_C87_N1_N0_3,
	PO_C87_N0, PO_C87_N0_1, PO_C87_N0_2, PO_C87_N0_3, PO_C87_N1, PO_C87_N1_N2_1, PO_C87_N1_N2_2, PO_C87_N1_N2_3,
	PO_C87_N2, PO_C87_N2_1, PO_C87_N2_2, PO_C87_N2_3, PO_C87_N3, PO_C87_N3_N2_1, PO_C87_N3_N2_2, PO_C87_N3_N2_3,
	PO_C87_N2, PO_C87_N2_1, PO_C87_N2_2, PO_C87_N2_3, PO_C87_N3, PO_C87_N3_N4_1, PO_C87_N3_N4_2, PO_C87_N3_N4_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c88mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C88_N0, PO_C88_N0_1, PO_C88_N0_2, PO_C88_N0_3, PO_C88_N1, PO_C88_N1_1, PO_C88_N1_2, PO_C88_N1_3,
	PO_C88_N2, PO_C88_N2_1, PO_C88_N2_2, PO_C88_N2_3, PO_C88_N3, PO_C88_N3_1, PO_C88_N3_2, PO_C88_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C88_MAGIC0, PO_C88_MAGIC0_1, PO_C88_MAGIC0_2, PO_C88_MAGIC0_3, PO_C88_MAGIC1, PO_C88_MAGIC1_1, PO_C88_MAGIC1_2, PO_C88_MAGIC1_3,
	PO_C88_MAGIC2, PO_C88_MAGIC2_1, PO_C88_MAGIC2_2, PO_C88_MAGIC2_3, PO_C88_MAGIC3, PO_C88_MAGIC3_1, PO_C88_MAGIC3_2, PO_C88_MAGIC3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c89mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C89_N0, PO_C89_N0_1, PO_C89_N0_2, PO_C89_N0_3, PO_C89_N1, PO_C89_N1_1, PO_C89_N1_2, PO_C89_N1_3,
	PO_C89_N2, PO_C89_N2_1, PO_C89_N2_2, PO_C89_N2_3, PO_C89_N3, PO_C89_N3_1, PO_C89_N3_2, PO_C89_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c90mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C90_N0, PO_C90_N0_1, PO_C90_N0_2, PO_C90_N0_3, PO_C90_N1, PO_C90_N1_1, PO_C90_N1_2, PO_C90_N1_3,
	PO_C90_N2, PO_C90_N2_1, PO_C90_N2_2, PO_C90_N2_3, PO_C90_N3, PO_C90_N3_1, PO_C90_N3_2, PO_C90_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c91mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C91_N0, PO_C91_N0_1, PO_C91_N0_2, PO_C91_N0_3, PO_C91_N1, PO_C91_N1_1, PO_C91_N1_2, PO_C91_N1_3,
	PO_C91_N2, PO_C91_N2_1, PO_C91_N2_2, PO_C91_N2_3, PO_C91_N3, PO_C91_N3_1, PO_C91_N3_2, PO_C91_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C91_W0, PO_C91_W0, PO_C91_W0_1, PO_C91_W0_1, PO_C91_W0_2, PO_C91_W0_2, PO_C91_W0_3, PO_C91_W0_3,
	PO_C91_W1, PO_C91_W1, PO_C91_W1_W2_1, PO_C91_W1_W2_1, PO_C91_W1_W2_2, PO_C91_W1_W2_2, PO_C91_W1_W2_3, PO_C91_W1_W2_3,
	PO_C91_W2, PO_C91_W2, PO_C91_W2_1, PO_C91_W2_1, PO_C91_W2_2, PO_C91_W2_2, PO_C91_W2_3, PO_C91_W2_3,
	PO_C91_W1, PO_C91_W1, PO_C91_W1_W0_1, PO_C91_W1_W0_1, PO_C91_W1_W0_2, PO_C91_W1_W0_2, PO_C91_W1_W0_3, PO_C91_W1_W0_3,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c92mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C92_N0, PO_C92_N0_1, PO_C92_N0_2, PO_C92_N0_3, PO_C92_N1, PO_C92_N1_1, PO_C92_N1_2, PO_C92_N1_3,
	PO_C92_N2, PO_C92_N2_1, PO_C92_N2_2, PO_C92_N2_3, PO_C92_N3, PO_C92_N3_1, PO_C92_N3_2, PO_C92_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C92_W0, PO_C92_W0_1, PO_C92_W0_2, PO_C92_W0_3, PO_C92_W1, PO_C92_W1_W2_1, PO_C92_W1_W2_2, PO_C92_W1_W2_3,
	PO_C92_W2, PO_C92_W2_1, PO_C92_W2_2, PO_C92_W2_3, PO_C92_W1, PO_C92_W1_W0_1, PO_C92_W1_W0_2, PO_C92_W1_W0_3,	//상태 프레임별 모션
	4 * _2X, 4 * _2X, 0 * _2X, 0 * _2X, 4 * _2X, 4 * _2X, 0 * _2X, 0 * _2X,
	4 * _2X, 4 * _2X, 0 * _2X, 0 * _2X, 4 * _2X, 4 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c93mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C93_N0, PO_C93_N0_1, PO_C93_N0_2, PO_C93_N0_3, PO_C93_N1, PO_C93_N1_1, PO_C93_N1_2, PO_C93_N1_3,
	PO_C93_N2, PO_C93_N2_1, PO_C93_N2_2, PO_C93_N2_3, PO_C93_N3, PO_C93_N3_1, PO_C93_N3_2, PO_C93_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C93_W0, PO_C93_W0, PO_C93_W0_1, PO_C93_W0_1, PO_C93_W0_2, PO_C93_W0_2, PO_C93_W0_3, PO_C93_W0_3,
	PO_C93_W1, PO_C93_W1, PO_C93_W1_W2_1, PO_C93_W1_W2_1, PO_C93_W1_W2_2, PO_C93_W1_W2_2, PO_C93_W1_W2_3, PO_C93_W1_W2_3,
	PO_C93_W2, PO_C93_W2, PO_C93_W2_1, PO_C93_W2_1, PO_C93_W2_2, PO_C93_W2_2, PO_C93_W2_3, PO_C93_W2_3,
	PO_C93_W1, PO_C93_W1, PO_C93_W1_W0_1, PO_C93_W1_W0_1, PO_C93_W1_W0_2, PO_C93_W1_W0_2, PO_C93_W1_W0_3, PO_C93_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c94mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C94_N0, PO_C94_N0_1, PO_C94_N0_2, PO_C94_N0_3, PO_C94_N1, PO_C94_N1_1, PO_C94_N1_2, PO_C94_N1_3,
	PO_C94_N2, PO_C94_N2_1, PO_C94_N2_2, PO_C94_N2_3, PO_C94_N3, PO_C94_N3_1, PO_C94_N3_2, PO_C94_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c95mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C95_N0, PO_C95_N0_1, PO_C95_N0_2, PO_C95_N0_3, PO_C95_N1, PO_C95_N1_1, PO_C95_N1_2, PO_C95_N1_3,
	PO_C95_N2, PO_C95_N2_1, PO_C95_N2_2, PO_C95_N2_3, PO_C95_N3, PO_C95_N3_1, PO_C95_N3_2, PO_C95_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C95_W0, PO_C95_W0, PO_C95_W0_1, PO_C95_W0_1, PO_C95_W0_2, PO_C95_W0_2, PO_C95_W0_3, PO_C95_W0_3,
	PO_C95_W1, PO_C95_W1, PO_C95_W1_W2_1, PO_C95_W1_W2_1, PO_C95_W1_W2_2, PO_C95_W1_W2_2, PO_C95_W1_W2_3, PO_C95_W1_W2_3,
	PO_C95_W2, PO_C95_W2, PO_C95_W2_1, PO_C95_W2_1, PO_C95_W2_2, PO_C95_W2_2, PO_C95_W2_3, PO_C95_W2_3,
	PO_C95_W1, PO_C95_W1, PO_C95_W1_W0_1, PO_C95_W1_W0_1, PO_C95_W1_W0_2, PO_C95_W1_W0_2, PO_C95_W1_W0_3, PO_C95_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	72,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C95_LASER0, PO_C95_LASER0_1, PO_C95_LASER0_2, PO_C95_LASER0_3, PO_C95_LASER1, PO_C95_LASER1_1, PO_C95_LASER1_2, PO_C95_LASER1_3,
	PO_C95_LASER2, PO_C95_LASER2_1, PO_C95_LASER2_2, PO_C95_LASER2_3, PO_C95_LASER3, PO_C95_LASER3_1, PO_C95_LASER3_2, PO_C95_LASER3_3,
	PO_C95_LASER4, PO_C95_LASER4_1, PO_C95_LASER4_2, PO_C95_LASER4_3, PO_C95_LASER5, PO_C95_LASER5_1, PO_C95_LASER5_2, PO_C95_LASER5_3,
	PO_C95_LASER6, PO_C95_LASER6_LASER2_1, PO_C95_LASER6_LASER2_2, PO_C95_LASER6_LASER2_3, PO_C95_LASER2, PO_C95_LASER2_1, PO_C95_LASER2_2, PO_C95_LASER2_3,
	PO_C95_LASER3, PO_C95_LASER3_1, PO_C95_LASER3_2, PO_C95_LASER3_3, PO_C95_LASER4, PO_C95_LASER4_1, PO_C95_LASER4_2, PO_C95_LASER4_3,
	PO_C95_LASER5, PO_C95_LASER5_1, PO_C95_LASER5_2, PO_C95_LASER5_3, PO_C95_LASER6, PO_C95_LASER6_LASER7_1, PO_C95_LASER6_LASER7_2, PO_C95_LASER6_LASER7_3,
	PO_C95_LASER7, PO_C95_LASER7_1, PO_C95_LASER7_2, PO_C95_LASER7_3, PO_C95_LASER8, PO_C95_LASER8_1, PO_C95_LASER8_2, PO_C95_LASER8_3,
	PO_C95_LASER9, PO_C95_LASER9_LASER7_1, PO_C95_LASER9_LASER7_2, PO_C95_LASER9_LASER7_3, PO_C95_LASER7, PO_C95_LASER7_1, PO_C95_LASER7_2, PO_C95_LASER7_3,
	PO_C95_LASER8, PO_C95_LASER8_1, PO_C95_LASER8_2, PO_C95_LASER8_3, PO_C95_LASER9, PO_C95_LASER9_LASER0_1, PO_C95_LASER9_LASER0_2, PO_C95_LASER9_LASER0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C95_N0_GHOST, PO_C95_N0_GHOST_2, PO_C95_N1_GHOST, PO_C95_N1_GHOST_2, PO_C95_N2_GHOST, PO_C95_N2_GHOST_2, PO_C95_N3_GHOST, PO_C95_N3_GHOST_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C95_W0_GHOST, PO_C95_W0_GHOST_2, PO_C95_W1_GHOST, PO_C95_W1_GHOST_W2_GHOST_2, PO_C95_W2_GHOST, PO_C95_W2_GHOST_2, PO_C95_W1_GHOST, PO_C95_W1_GHOST_W0_GHOST_2,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C95_SURPRISE0_GHOST, PO_C95_SURPRISE0_GHOST_2, PO_C95_SURPRISE1_GHOST, PO_C95_SURPRISE1_GHOST_2, PO_C95_SURPRISE2_GHOST, PO_C95_SURPRISE2_GHOST_2, PO_C95_SURPRISE3_GHOST, PO_C95_SURPRISE3_GHOST_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c96mv[] = {
	//상태 데이터
	//LORA_NEUTRAL_DRESS
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C96_N0_DRESS, PO_C96_N0_DRESS_1, PO_C96_N0_DRESS_2, PO_C96_N0_DRESS_3, PO_C96_N1_DRESS, PO_C96_N1_DRESS_1, PO_C96_N1_DRESS_2, PO_C96_N1_DRESS_3,
	PO_C96_N2_DRESS, PO_C96_N2_DRESS_1, PO_C96_N2_DRESS_2, PO_C96_N2_DRESS_3, PO_C96_N3_DRESS, PO_C96_N3_DRESS_1, PO_C96_N3_DRESS_2, PO_C96_N3_DRESS_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LORA_MOVE_DRESS
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C96_W0_DRESS, PO_C96_W0_DRESS, PO_C96_W0_DRESS_1, PO_C96_W0_DRESS_1, PO_C96_W0_DRESS_2, PO_C96_W0_DRESS_2, PO_C96_W0_DRESS_3, PO_C96_W0_DRESS_3,
	PO_C96_W1_DRESS, PO_C96_W1_DRESS, PO_C96_W1_DRESS_W2_DRESS_1, PO_C96_W1_DRESS_W2_DRESS_1, PO_C96_W1_DRESS_W2_DRESS_2, PO_C96_W1_DRESS_W2_DRESS_2, PO_C96_W1_DRESS_W2_DRESS_3, PO_C96_W1_DRESS_W2_DRESS_3,
	PO_C96_W2_DRESS, PO_C96_W2_DRESS, PO_C96_W2_DRESS_1, PO_C96_W2_DRESS_1, PO_C96_W2_DRESS_2, PO_C96_W2_DRESS_2, PO_C96_W2_DRESS_3, PO_C96_W2_DRESS_3,
	PO_C96_W1_DRESS, PO_C96_W1_DRESS, PO_C96_W1_DRESS_W0_DRESS_1, PO_C96_W1_DRESS_W0_DRESS_1, PO_C96_W1_DRESS_W0_DRESS_2, PO_C96_W1_DRESS_W0_DRESS_2, PO_C96_W1_DRESS_W0_DRESS_3, PO_C96_W1_DRESS_W0_DRESS_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LORA_SAD_DRESS
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C96_SAD0, PO_C96_SAD0, PO_C96_SAD0, PO_C96_SAD0, PO_C96_SAD0, PO_C96_SAD0, PO_C96_SAD0, PO_C96_SAD0,
	PO_C96_SAD0, PO_C96_SAD0, PO_C96_SAD0, PO_C96_SAD0, PO_C96_SAD0, PO_C96_SAD0, PO_C96_SAD0, PO_C96_SAD0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LORA_SUPRISE_DRESS
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C96_SURPRISE0_DRESS, PO_C96_SURPRISE0_DRESS, PO_C96_SURPRISE0_DRESS, PO_C96_SURPRISE0_DRESS, PO_C96_SURPRISE0_DRESS, PO_C96_SURPRISE0_DRESS, PO_C96_SURPRISE0_DRESS, PO_C96_SURPRISE0_DRESS,
	PO_C96_SURPRISE0_DRESS, PO_C96_SURPRISE0_DRESS, PO_C96_SURPRISE0_DRESS, PO_C96_SURPRISE0_DRESS, PO_C96_SURPRISE0_DRESS, PO_C96_SURPRISE0_DRESS, PO_C96_SURPRISE0_DRESS, PO_C96_SURPRISE0_DRESS,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LORA_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C96_N0, PO_C96_N0_1, PO_C96_N0_2, PO_C96_N0_3, PO_C96_N1, PO_C96_N1_1, PO_C96_N1_2, PO_C96_N1_3,
	PO_C96_N2, PO_C96_N2_1, PO_C96_N2_2, PO_C96_N2_3, PO_C96_N3, PO_C96_N3_1, PO_C96_N3_2, PO_C96_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LORA_MOVE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C96_W0, PO_C96_W0_1, PO_C96_W0_2, PO_C96_W0_3, PO_C96_W1, PO_C96_W1_W2_1, PO_C96_W1_W2_2, PO_C96_W1_W2_3,
	PO_C96_W2, PO_C96_W2_1, PO_C96_W2_2, PO_C96_W2_3, PO_C96_W1, PO_C96_W1_W0_1, PO_C96_W1_W0_2, PO_C96_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C96_SAD0, PO_C96_SAD0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c97mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C97_N0, PO_C97_N0_1, PO_C97_N0_2, PO_C97_N0_3, PO_C97_N1, PO_C97_N1_1, PO_C97_N1_2, PO_C97_N1_3,
	PO_C97_N2, PO_C97_N2_1, PO_C97_N2_2, PO_C97_N2_3, PO_C97_N3, PO_C97_N3_1, PO_C97_N3_2, PO_C97_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	64,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C97_M0, PO_C97_M0_1, PO_C97_M0_2, PO_C97_M0_3, PO_C97_M1, PO_C97_M1_1, PO_C97_M1_2, PO_C97_M1_3,
	PO_C97_M2, PO_C97_M2_1, PO_C97_M2_2, PO_C97_M2_3, PO_C97_M3, PO_C97_M3_M0_1, PO_C97_M3_M0_2, PO_C97_M3_M0_3,
	PO_C97_M0, PO_C97_M0_1, PO_C97_M0_2, PO_C97_M0_3, PO_C97_M1, PO_C97_M1_1, PO_C97_M1_2, PO_C97_M1_3,
	PO_C97_M2, PO_C97_M2_1, PO_C97_M2_2, PO_C97_M2_3, PO_C97_M3, PO_C97_M3_M4_1, PO_C97_M3_M4_2, PO_C97_M3_M4_3,
	PO_C97_M4, PO_C97_M4_1, PO_C97_M4_2, PO_C97_M4_3, PO_C97_M5, PO_C97_M5_1, PO_C97_M5_2, PO_C97_M5_3,
	PO_C97_M6, PO_C97_M6_1, PO_C97_M6_2, PO_C97_M6_3, PO_C97_M7, PO_C97_M7_M4_1, PO_C97_M7_M4_2, PO_C97_M7_M4_3,
	PO_C97_M4, PO_C97_M4_1, PO_C97_M4_2, PO_C97_M4_3, PO_C97_M5, PO_C97_M5_1, PO_C97_M5_2, PO_C97_M5_3,
	PO_C97_M6, PO_C97_M6_1, PO_C97_M6_2, PO_C97_M6_3, PO_C97_M7, PO_C97_M7_M0_1, PO_C97_M7_M0_2, PO_C97_M7_M0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};


const signed short c98mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C98_N0, PO_C98_N0_1, PO_C98_N0_2, PO_C98_N0_3, PO_C98_N1, PO_C98_N1_1, PO_C98_N1_2, PO_C98_N1_3,
	PO_C98_N2, PO_C98_N2_1, PO_C98_N2_2, PO_C98_N2_3, PO_C98_N3, PO_C98_N3_1, PO_C98_N3_2, PO_C98_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c99mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C99_N0, PO_C99_N0_1, PO_C99_N0_2, PO_C99_N0_3, PO_C99_N1, PO_C99_N1_1, PO_C99_N1_2, PO_C99_N1_3,
	PO_C99_N2, PO_C99_N2_1, PO_C99_N2_2, PO_C99_N2_3, PO_C99_N3, PO_C99_N3_1, PO_C99_N3_2, PO_C99_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C99_W0, PO_C99_W0, PO_C99_W0_1, PO_C99_W0_1, PO_C99_W0_2, PO_C99_W0_2, PO_C99_W0_3, PO_C99_W0_3,
	PO_C99_W1, PO_C99_W1, PO_C99_W1_W2_1, PO_C99_W1_W2_1, PO_C99_W1_W2_2, PO_C99_W1_W2_2, PO_C99_W1_W2_3, PO_C99_W1_W2_3,
	PO_C99_W2, PO_C99_W2, PO_C99_W2_1, PO_C99_W2_1, PO_C99_W2_2, PO_C99_W2_2, PO_C99_W2_3, PO_C99_W2_3,
	PO_C99_W1, PO_C99_W1, PO_C99_W1_W0_1, PO_C99_W1_W0_1, PO_C99_W1_W0_2, PO_C99_W1_W0_2, PO_C99_W1_W0_3, PO_C99_W1_W0_3,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	7, 7, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	5, 5, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	NPCMOVE_STAND,	NPCMOVE_WALKSLOW,	0,	0,	RANDOM,	40,
	NPCMOVE_WALKSLOW,	NPCMOVE_STAND,	0,	0,	RANDOM,	30,
	-1,
};

const signed short c100mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C100_N0, PO_C100_N0_1, PO_C100_N0_2, PO_C100_N0_3, PO_C100_N1, PO_C100_N1_1, PO_C100_N1_2, PO_C100_N1_3,
	PO_C100_N2, PO_C100_N2_1, PO_C100_N2_2, PO_C100_N2_3, PO_C100_N3, PO_C100_N3_1, PO_C100_N3_2, PO_C100_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c101mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C101_N0, PO_C101_N0_1, PO_C101_N0_2, PO_C101_N0_3, PO_C101_N1, PO_C101_N1_1, PO_C101_N1_2, PO_C101_N1_3,
	PO_C101_N2, PO_C101_N2_1, PO_C101_N2_2, PO_C101_N2_3, PO_C101_N3, PO_C101_N3_1, PO_C101_N3_2, PO_C101_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C101_W0, PO_C101_W0, PO_C101_W0_1, PO_C101_W0_1, PO_C101_W0_2, PO_C101_W0_2, PO_C101_W0_3, PO_C101_W0_3,
	PO_C101_W1, PO_C101_W1, PO_C101_W1_W2_1, PO_C101_W1_W2_1, PO_C101_W1_W2_2, PO_C101_W1_W2_2, PO_C101_W1_W2_3, PO_C101_W1_W2_3,
	PO_C101_W2, PO_C101_W2, PO_C101_W2_1, PO_C101_W2_1, PO_C101_W2_2, PO_C101_W2_2, PO_C101_W2_3, PO_C101_W2_3,
	PO_C101_W1, PO_C101_W1, PO_C101_W1_W0_1, PO_C101_W1_W0_1, PO_C101_W1_W0_2, PO_C101_W1_W0_2, PO_C101_W1_W0_3, PO_C101_W1_W0_3,	//상태 프레임별 모션
	3, 3, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	5, 5, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	7, 7, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C101_W0, PO_C101_W0_1, PO_C101_W0_2, PO_C101_W0_3, PO_C101_W1, PO_C101_W1_W2_1, PO_C101_W1_W2_2, PO_C101_W1_W2_3,
	PO_C101_W2, PO_C101_W2_1, PO_C101_W2_2, PO_C101_W2_3, PO_C101_W1, PO_C101_W1_W0_1, PO_C101_W1_W0_2, PO_C101_W1_W0_3,	//상태 프레임별 모션
	-3, -3, 0 * _2X, 0 * _2X, -5, -5, 0 * _2X, 0 * _2X,
	-7, -7, 0 * _2X, 0 * _2X, -3 * _2X, -3 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	NPCMOVE_STAND,	NPCMOVE_WALKSLOW,	0,	0,	RANDOM,	30,
	NPCMOVE_WALKSLOW,	NPCMOVE_STAND,	0,	0,	RANDOM,	30,
	-1,
};

const signed short c102mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C102_N0, PO_C102_N0_1, PO_C102_N0_2, PO_C102_N0_3, PO_C102_N1, PO_C102_N1_1, PO_C102_N1_2, PO_C102_N1_3,
	PO_C102_N2, PO_C102_N2_1, PO_C102_N2_2, PO_C102_N2_3, PO_C102_N3, PO_C102_N3_1, PO_C102_N3_2, PO_C102_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C102_W0, PO_C102_W0, PO_C102_W0_1, PO_C102_W0_1, PO_C102_W0_2, PO_C102_W0_2, PO_C102_W0_3, PO_C102_W0_3,
	PO_C102_W1, PO_C102_W1, PO_C102_W1_W2_1, PO_C102_W1_W2_1, PO_C102_W1_W2_2, PO_C102_W1_W2_2, PO_C102_W1_W2_3, PO_C102_W1_W2_3,
	PO_C102_W2, PO_C102_W2, PO_C102_W2_1, PO_C102_W2_1, PO_C102_W2_2, PO_C102_W2_2, PO_C102_W2_3, PO_C102_W2_3,
	PO_C102_W1, PO_C102_W1, PO_C102_W1_W0_1, PO_C102_W1_W0_1, PO_C102_W1_W0_2, PO_C102_W1_W0_2, PO_C102_W1_W0_3, PO_C102_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C102_W0, PO_C102_W0_1, PO_C102_W0_2, PO_C102_W0_3, PO_C102_W1, PO_C102_W1_W2_1, PO_C102_W1_W2_2, PO_C102_W1_W2_3,
	PO_C102_W2, PO_C102_W2_1, PO_C102_W2_2, PO_C102_W2_3, PO_C102_W1, PO_C102_W1_W0_1, PO_C102_W1_W0_2, PO_C102_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	NPCMOVE_STAND,	NPCMOVE_WALKSLOW,	0,	0,	RANDOM,	30,
	NPCMOVE_WALKSLOW,	NPCMOVE_STAND,	0,	0,	RANDOM,	30,
	-1,
};

const signed short c103mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C103_N0, PO_C103_N0_1, PO_C103_N0_2, PO_C103_N0_3, PO_C103_N1, PO_C103_N1_1, PO_C103_N1_2, PO_C103_N1_3,
	PO_C103_N2, PO_C103_N2_1, PO_C103_N2_2, PO_C103_N2_3, PO_C103_N3, PO_C103_N3_1, PO_C103_N3_2, PO_C103_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C103_W0, PO_C103_W0, PO_C103_W0_1, PO_C103_W0_1, PO_C103_W0_2, PO_C103_W0_2, PO_C103_W0_3, PO_C103_W0_3,
	PO_C103_W1, PO_C103_W1, PO_C103_W1_W2_1, PO_C103_W1_W2_1, PO_C103_W1_W2_2, PO_C103_W1_W2_2, PO_C103_W1_W2_3, PO_C103_W1_W2_3,
	PO_C103_W2, PO_C103_W2, PO_C103_W2_1, PO_C103_W2_1, PO_C103_W2_2, PO_C103_W2_2, PO_C103_W2_3, PO_C103_W2_3,
	PO_C103_W1, PO_C103_W1, PO_C103_W1_W0_1, PO_C103_W1_W0_1, PO_C103_W1_W0_2, PO_C103_W1_W0_2, PO_C103_W1_W0_3, PO_C103_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	5, 5, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C103_W1, PO_C103_W1_W2_1, PO_C103_W1_W2_2, PO_C103_W1_W2_3, PO_C103_W2, PO_C103_W2_1, PO_C103_W2_2, PO_C103_W2_3,
	PO_C103_W1, PO_C103_W1_W0_1, PO_C103_W1_W0_2, PO_C103_W1_W0_3, PO_C103_W0, PO_C103_W0_1, PO_C103_W0_2, PO_C103_W0_3,	//상태 프레임별 모션
	-1 * _2X, -1 * _2X, 0 * _2X, 0 * _2X, -1 * _2X, -1 * _2X, 0 * _2X, 0 * _2X,
	-1 * _2X, -1 * _2X, 0 * _2X, 0 * _2X, -1 * _2X, -1 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C103_CAP0, PO_C103_CAP0_1, PO_C103_CAP0_2, PO_C103_CAP0_3, PO_C103_CAP1, PO_C103_CAP1_1, PO_C103_CAP1_2, PO_C103_CAP1_3,
	PO_C103_CAP2, PO_C103_CAP2_1, PO_C103_CAP2_2, PO_C103_CAP2_3, PO_C103_CAP3, PO_C103_CAP3_1, PO_C103_CAP3_2, PO_C103_CAP3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C103_CAPMOVE0, PO_C103_CAPMOVE0_1, PO_C103_CAPMOVE0_2, PO_C103_CAPMOVE0_3, PO_C103_CAPMOVE1, PO_C103_CAPMOVE1_CAPMOVE2_1, PO_C103_CAPMOVE1_CAPMOVE2_2, PO_C103_CAPMOVE1_CAPMOVE2_3,
	PO_C103_CAPMOVE2, PO_C103_CAPMOVE2_1, PO_C103_CAPMOVE2_2, PO_C103_CAPMOVE2_3, PO_C103_CAPMOVE1, PO_C103_CAPMOVE1_CAPMOVE0_1, PO_C103_CAPMOVE1_CAPMOVE0_2, PO_C103_CAPMOVE1_CAPMOVE0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 5, 5, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	NPCMOVE_STAND,	NPCMOVE_WALKSLOW,	0,	0,	RANDOM,	33,
	NPCMOVE_WALKSLOW,	NPCMOVE_STAND,	0,	0,	RANDOM,	15,
	-1,
};

const signed short c104mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C104_N0, PO_C104_N0_1, PO_C104_N0_2, PO_C104_N0_3, PO_C104_N1, PO_C104_N1_1, PO_C104_N1_2, PO_C104_N1_3,
	PO_C104_N2, PO_C104_N2_1, PO_C104_N2_2, PO_C104_N2_3, PO_C104_N3, PO_C104_N3_1, PO_C104_N3_2, PO_C104_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c105mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C105_N0, PO_C105_N0_1, PO_C105_N0_2, PO_C105_N0_3, PO_C105_N1, PO_C105_N1_1, PO_C105_N1_2, PO_C105_N1_3,
	PO_C105_N2, PO_C105_N2_1, PO_C105_N2_2, PO_C105_N2_3, PO_C105_N3, PO_C105_N3_1, PO_C105_N3_2, PO_C105_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C105_W0, PO_C105_W0, PO_C105_W0_1, PO_C105_W0_1, PO_C105_W0_2, PO_C105_W0_2, PO_C105_W0_3, PO_C105_W0_3,
	PO_C105_W1, PO_C105_W1, PO_C105_W1_W2_1, PO_C105_W1_W2_1, PO_C105_W1_W2_2, PO_C105_W1_W2_2, PO_C105_W1_W2_3, PO_C105_W1_W2_3,
	PO_C105_W2, PO_C105_W2, PO_C105_W2_1, PO_C105_W2_1, PO_C105_W2_2, PO_C105_W2_2, PO_C105_W2_3, PO_C105_W2_3,
	PO_C105_W1, PO_C105_W1, PO_C105_W1_W0_1, PO_C105_W1_W0_1, PO_C105_W1_W0_2, PO_C105_W1_W0_2, PO_C105_W1_W0_3, PO_C105_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c106mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C106_N0, PO_C106_N0_N1_1, PO_C106_N0_N1_2, PO_C106_N0_N1_3, PO_C106_N1, PO_C106_N1_1, PO_C106_N1_2, PO_C106_N1_3,
	PO_C106_N2, PO_C106_N2_1, PO_C106_N2_2, PO_C106_N2_3, PO_C106_N3, PO_C106_N3_1, PO_C106_N3_2, PO_C106_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C106_W0, PO_C106_W0, PO_C106_W0_1, PO_C106_W0_1, PO_C106_W0_2, PO_C106_W0_2, PO_C106_W0_3, PO_C106_W0_3,
	PO_C106_W1, PO_C106_W1, PO_C106_W1_W2_1, PO_C106_W1_W2_1, PO_C106_W1_W2_2, PO_C106_W1_W2_2, PO_C106_W1_W2_3, PO_C106_W1_W2_3,
	PO_C106_W2, PO_C106_W2, PO_C106_W2_1, PO_C106_W2_1, PO_C106_W2_2, PO_C106_W2_2, PO_C106_W2_3, PO_C106_W2_3,
	PO_C106_W1, PO_C106_W1, PO_C106_W1_W0_1, PO_C106_W1_W0_1, PO_C106_W1_W0_2, PO_C106_W1_W0_2, PO_C106_W1_W0_3, PO_C106_W1_W0_3,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C106_COMPASS5, PO_C106_COMPASS5_COMPASS6_1, PO_C106_COMPASS5_COMPASS6_2, PO_C106_COMPASS5_COMPASS6_3, PO_C106_COMPASS6, PO_C106_COMPASS6_COMPASS7_1, PO_C106_COMPASS6_COMPASS7_2, PO_C106_COMPASS6_COMPASS7_3,
	PO_C106_COMPASS7, PO_C106_COMPASS7_COMPASS6_1, PO_C106_COMPASS7_COMPASS6_2, PO_C106_COMPASS7_COMPASS6_3, PO_C106_COMPASS6, PO_C106_COMPASS6_COMPASS5_1, PO_C106_COMPASS6_COMPASS5_2, PO_C106_COMPASS6_COMPASS5_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C106_COMPASS0, PO_C106_COMPASS0_1, PO_C106_COMPASS0_2, PO_C106_COMPASS0_3, PO_C106_COMPASS1, PO_C106_COMPASS1_COMPASS2_1, PO_C106_COMPASS1_COMPASS2_2, PO_C106_COMPASS1_COMPASS2_3,
	PO_C106_COMPASS2, PO_C106_COMPASS2_COMPASS3_1, PO_C106_COMPASS2_COMPASS3_2, PO_C106_COMPASS2_COMPASS3_3, PO_C106_COMPASS3, PO_C106_COMPASS3_COMPASS4_1, PO_C106_COMPASS3_COMPASS4_2, PO_C106_COMPASS3_COMPASS4_3,
	PO_C106_COMPASS4, PO_C106_COMPASS4_COMPASS5_1, PO_C106_COMPASS4_COMPASS5_2, PO_C106_COMPASS4_COMPASS5_3, PO_C106_COMPASS5, PO_C106_COMPASS5_COMPASS6_1, PO_C106_COMPASS5_COMPASS6_2, PO_C106_COMPASS5_COMPASS6_3,
	PO_C106_COMPASS6, PO_C106_COMPASS6_COMPASS7_1, PO_C106_COMPASS6_COMPASS7_2, PO_C106_COMPASS6_COMPASS7_3, PO_C106_COMPASS7, PO_C106_COMPASS7_COMPASS0_1, PO_C106_COMPASS7_COMPASS0_2, PO_C106_COMPASS7_COMPASS0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C106_COMPASS7, PO_C106_COMPASS7_COMPASS6_1, PO_C106_COMPASS7_COMPASS6_2, PO_C106_COMPASS7_COMPASS6_3, PO_C106_COMPASS6, PO_C106_COMPASS6_COMPASS5_1, PO_C106_COMPASS6_COMPASS5_2, PO_C106_COMPASS6_COMPASS5_3,
	PO_C106_COMPASS5, PO_C106_COMPASS5_COMPASS4_1, PO_C106_COMPASS5_COMPASS4_2, PO_C106_COMPASS5_COMPASS4_3, PO_C106_COMPASS4, PO_C106_COMPASS4_COMPASS3_1, PO_C106_COMPASS4_COMPASS3_2, PO_C106_COMPASS4_COMPASS3_3,
	PO_C106_COMPASS3, PO_C106_COMPASS3_COMPASS2_1, PO_C106_COMPASS3_COMPASS2_2, PO_C106_COMPASS3_COMPASS2_3, PO_C106_COMPASS2, PO_C106_COMPASS2_COMPASS1_1, PO_C106_COMPASS2_COMPASS1_2, PO_C106_COMPASS2_COMPASS1_3,
	PO_C106_COMPASS1, PO_C106_COMPASS1_N0_1, PO_C106_COMPASS1_N0_2, PO_C106_COMPASS1_N0_3, PO_C106_N0, PO_C106_N0_COMPASS7_1, PO_C106_N0_COMPASS7_2, PO_C106_N0_COMPASS7_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C106_D0, PO_C106_D0, PO_C106_D0, PO_C106_D0, PO_C106_D0, PO_C106_D0, PO_C106_D0, PO_C106_D0,
	PO_C106_D0, PO_C106_D0, PO_C106_D0, PO_C106_D0, PO_C106_D0, PO_C106_D0, PO_C106_D0, PO_C106_D0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c107mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C107_N0, PO_C107_N0_1, PO_C107_N0_2, PO_C107_N0_3, PO_C107_N1, PO_C107_N1_1, PO_C107_N1_2, PO_C107_N1_3,
	PO_C107_N2, PO_C107_N2_1, PO_C107_N2_2, PO_C107_N2_3, PO_C107_N3, PO_C107_N3_1, PO_C107_N3_2, PO_C107_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_RANDOM,	//초기화 조건
	PO_C107_M0, PO_C107_M0_1, PO_C107_M0_2, PO_C107_M0_3, PO_C107_M1, PO_C107_M1_M2_1, PO_C107_M1_M2_2, PO_C107_M1_M2_3,
	PO_C107_M2, PO_C107_M2_1, PO_C107_M2_2, PO_C107_M2_3, PO_C107_M1, PO_C107_M1_M0_1, PO_C107_M1_M0_2, PO_C107_M1_M0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c108mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C108_N0, PO_C108_N0_1, PO_C108_N0_2, PO_C108_N0_3, PO_C108_N1, PO_C108_N1_1, PO_C108_N1_2, PO_C108_N1_3,
	PO_C108_N2, PO_C108_N2_1, PO_C108_N2_2, PO_C108_N2_3, PO_C108_N3, PO_C108_N3_1, PO_C108_N3_2, PO_C108_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8 | SET_DIR_PLAYER,	//초기화 조건
	PO_C108_LOOK0, PO_C108_LOOK0_1, PO_C108_LOOK0_2, PO_C108_LOOK0_3, PO_C108_LOOK1, PO_C108_LOOK1_1, PO_C108_LOOK1_2, PO_C108_LOOK1_3,
	PO_C108_LOOK2, PO_C108_LOOK2_1, PO_C108_LOOK2_2, PO_C108_LOOK2_3, PO_C108_LOOK3, PO_C108_LOOK3_1, PO_C108_LOOK3_2, PO_C108_LOOK3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	NPCMOVE_STAND,	NPCMOVE_WALKSLOW,	DISTANCE_OUT_XY,	3 * 8 + 3,	0,	0,
	NPCMOVE_WALKSLOW,	NPCMOVE_STAND,	DISTANCE_CHECK_XY,	3 * 8 + 3,	0,	0,
	-1,
};

//라베스
const signed short c109mv[] = {
	//상태 데이터
	//BOSS
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C109_N0, PO_C109_N0_1, PO_C109_N0_2, PO_C109_N0_3, PO_C109_N1, PO_C109_N1_1, PO_C109_N1_2, PO_C109_N1_3,
	PO_C109_N2, PO_C109_N2_1, PO_C109_N2_2, PO_C109_N2_3, PO_C109_N3, PO_C109_N3_1, PO_C109_N3_2, PO_C109_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LABETH_NEUTRAL
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C109_W0, PO_C109_W0, PO_C109_W0_1, PO_C109_W0_1, PO_C109_W0_2, PO_C109_W0_2, PO_C109_W0_3, PO_C109_W0_3,
	PO_C109_W1, PO_C109_W1, PO_C109_W1_W2_1, PO_C109_W1_W2_1, PO_C109_W1_W2_2, PO_C109_W1_W2_2, PO_C109_W1_W2_3, PO_C109_W1_W2_3,
	PO_C109_W2, PO_C109_W2, PO_C109_W2_1, PO_C109_W2_1, PO_C109_W2_2, PO_C109_W2_2, PO_C109_W2_3, PO_C109_W2_3,
	PO_C109_W1, PO_C109_W1, PO_C109_W1_W0_1, PO_C109_W1_W0_1, PO_C109_W1_W0_2, PO_C109_W1_W0_2, PO_C109_W1_W0_3, PO_C109_W1_W0_3,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ELKEIN2_MOVE
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C109_DOWN0, PO_C109_DOWN0,	//상태 프레임별 모션
	1 * _2X, 1 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LABETH_LASER
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C109_THINK0, PO_C109_THINK0,	//상태 프레임별 모션
	1 * _2X, 1 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LABETH_FLAME
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C109_DOWN0, PO_C109_DOWN0, PO_C109_DOWN0, PO_C109_DOWN0, PO_C109_DOWN0, PO_C109_DOWN0, PO_C109_DOWN0, PO_C109_DOWN0,	//상태 프레임별 모션
	-1 * _2X, -1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	103, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//LABETH_MAGIC
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C109_N0, PO_C109_N0_1, PO_C109_N0_2, PO_C109_N0_3, PO_C109_N1, PO_C109_N1_1, PO_C109_N1_2, PO_C109_N1_3,
	PO_C109_N2, PO_C109_N2_1, PO_C109_N2_2, PO_C109_N2_3, PO_C109_N3, PO_C109_N3_1, PO_C109_N3_2, PO_C109_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C109_W0, PO_C109_W0_1, PO_C109_W0_2, PO_C109_W0_3, PO_C109_W1, PO_C109_W1_W2_1, PO_C109_W1_W2_2, PO_C109_W1_W2_3,
	PO_C109_W2, PO_C109_W2_1, PO_C109_W2_2, PO_C109_W2_3, PO_C109_W1, PO_C109_W1_W0_1, PO_C109_W1_W0_2, PO_C109_W1_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X,
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	270,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0,
	PO_C109_LASER0, PO_C109_LASER0_1, PO_C109_LASER0_1, PO_C109_LASER0_1, PO_C109_LASER0_1, PO_C109_LASER0_1, PO_C109_LASER0_1, PO_C109_LASER0_1,
	PO_C109_LASER0_1, PO_C109_LASER0_1, PO_C109_LASER0_2, PO_C109_LASER0_2, PO_C109_LASER0_2, PO_C109_LASER0_2, PO_C109_LASER0_2, PO_C109_LASER0_2,
	PO_C109_LASER0_2, PO_C109_LASER0_2, PO_C109_LASER0_2, PO_C109_LASER0_3, PO_C109_LASER0_3, PO_C109_LASER0_3, PO_C109_LASER0_3, PO_C109_LASER0_3,
	PO_C109_LASER0_3, PO_C109_LASER0_3, PO_C109_LASER0_3, PO_C109_LASER0_3, PO_C109_LASER1, PO_C109_LASER1, PO_C109_LASER1_1, PO_C109_LASER1_2,
	PO_C109_LASER1_2, PO_C109_LASER1_3, PO_C109_LASER2, PO_C109_LASER2, PO_C109_LASER2_1, PO_C109_LASER2_2, PO_C109_LASER2_2, PO_C109_LASER2_3,
	PO_C109_LASER3, PO_C109_LASER3, PO_C109_LASER3_1, PO_C109_LASER3_2, PO_C109_LASER3_2, PO_C109_LASER3_3, PO_C109_LASER4, PO_C109_LASER4,
	PO_C109_LASER4_1, PO_C109_LASER4_2, PO_C109_LASER4_2, PO_C109_LASER4_3, PO_C109_LASER5, PO_C109_LASER5, PO_C109_LASER5_1, PO_C109_LASER5_2,
	PO_C109_LASER5_2, PO_C109_LASER5_3, PO_C109_LASER6, PO_C109_LASER6, PO_C109_LASER6_1, PO_C109_LASER6_2, PO_C109_LASER6_2, PO_C109_LASER6_3,
	PO_C109_LASER7, PO_C109_LASER7, PO_C109_LASER7_1, PO_C109_LASER7_2, PO_C109_LASER7_2, PO_C109_LASER7_3, PO_C109_LASER8, PO_C109_LASER8,
	PO_C109_LASER8_1, PO_C109_LASER8_2, PO_C109_LASER8_2, PO_C109_LASER8_3, PO_C109_LASER9, PO_C109_LASER9, PO_C109_LASER9_1, PO_C109_LASER9_2,
	PO_C109_LASER9_2, PO_C109_LASER9_3, PO_C109_LASER10, PO_C109_LASER10, PO_C109_LASER10_1, PO_C109_LASER10_2, PO_C109_LASER10_2, PO_C109_LASER10_3,
	PO_C109_LASER11, PO_C109_LASER11, PO_C109_LASER11_1, PO_C109_LASER11_2, PO_C109_LASER11_2, PO_C109_LASER11_3, PO_C109_LASER12, PO_C109_LASER12,
	PO_C109_LASER12_1, PO_C109_LASER12_2, PO_C109_LASER12_2, PO_C109_LASER12_3, PO_C109_LASER13, PO_C109_LASER13, PO_C109_LASER13_1, PO_C109_LASER13_2,
	PO_C109_LASER13_2, PO_C109_LASER13_3, PO_C109_LASER14, PO_C109_LASER14, PO_C109_LASER14_1, PO_C109_LASER14_2, PO_C109_LASER14_2, PO_C109_LASER14_3,
	PO_C109_LASER15, PO_C109_LASER15, PO_C109_LASER15_1, PO_C109_LASER15_2, PO_C109_LASER15_2, PO_C109_LASER15_3, PO_C109_LASER16, PO_C109_LASER16,
	PO_C109_LASER16_1, PO_C109_LASER16_2, PO_C109_LASER16_2, PO_C109_LASER16_3, PO_C109_LASER17, PO_C109_LASER17, PO_C109_LASER17_1, PO_C109_LASER17_2,
	PO_C109_LASER17_2, PO_C109_LASER17_3, PO_C109_LASER18, PO_C109_LASER18, PO_C109_LASER18, PO_C109_LASER18_1, PO_C109_LASER18_1, PO_C109_LASER18_1,
	PO_C109_LASER18_2, PO_C109_LASER18_2, PO_C109_LASER18_2, PO_C109_LASER18_3, PO_C109_LASER18_3, PO_C109_LASER18_3, PO_C109_LASER0, PO_C109_LASER0,
	PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0,
	PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0,
	PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0,
	PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0,
	PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0,
	PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0,
	PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0,
	PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0,
	PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0,
	PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0,
	PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0,
	PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0,
	PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0,
	PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0,
	PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0, PO_C109_LASER0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	80,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C109_FLAME0, PO_C109_FLAME0_2, PO_C109_FLAME1, PO_C109_FLAME1_2, PO_C109_FLAME2, PO_C109_FLAME2_2, PO_C109_FLAME3, PO_C109_FLAME3_2,
	PO_C109_FLAME4, PO_C109_FLAME4_2, PO_C109_FLAME5, PO_C109_FLAME5_2, PO_C109_FLAME6, PO_C109_FLAME6_2, PO_C109_FLAME7, PO_C109_FLAME7_2,
	PO_C109_FLAME8, PO_C109_FLAME8_2, PO_C109_FLAME9, PO_C109_FLAME9, PO_C109_FLAME9, PO_C109_FLAME9, PO_C109_FLAME9, PO_C109_FLAME9,
	PO_C109_FLAME9_1, PO_C109_FLAME9_1, PO_C109_FLAME9_1, PO_C109_FLAME9_1, PO_C109_FLAME9_1, PO_C109_FLAME9_2, PO_C109_FLAME9_2, PO_C109_FLAME9_2,
	PO_C109_FLAME9_2, PO_C109_FLAME9_2, PO_C109_FLAME9_2, PO_C109_FLAME9_3, PO_C109_FLAME9_3, PO_C109_FLAME9_3, PO_C109_FLAME9_3, PO_C109_FLAME9_3,
	PO_C109_FLAME10, PO_C109_FLAME10_2, PO_C109_FLAME11, PO_C109_FLAME11_2, PO_C109_FLAME12, PO_C109_FLAME12_2, PO_C109_FLAME13, PO_C109_FLAME13_2,
	PO_C109_FLAME14, PO_C109_FLAME14_2, PO_C109_FLAME15, PO_C109_FLAME15_2, PO_C109_FLAME16, PO_C109_FLAME16_2, PO_C109_FLAME17, PO_C109_FLAME17_2,
	PO_C109_FLAME18, PO_C109_FLAME18, PO_C109_FLAME18, PO_C109_FLAME18, PO_C109_FLAME18, PO_C109_FLAME18, PO_C109_FLAME18, PO_C109_FLAME18,
	PO_C109_FLAME18, PO_C109_FLAME18, PO_C109_FLAME18, PO_C109_FLAME18, PO_C109_FLAME18, PO_C109_FLAME18, PO_C109_FLAME18, PO_C109_FLAME18,
	PO_C109_FLAME18, PO_C109_FLAME18, PO_C109_FLAME18, PO_C109_FLAME18, PO_C109_FLAME18, PO_C109_FLAME18, PO_C109_FLAME18, PO_C109_FLAME18,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	80,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C109_MAGIC0, PO_C109_MAGIC0_2, PO_C109_MAGIC1, PO_C109_MAGIC1_2, PO_C109_MAGIC2, PO_C109_MAGIC2_2, PO_C109_MAGIC3, PO_C109_MAGIC3_2,
	PO_C109_MAGIC4, PO_C109_MAGIC4_2, PO_C109_MAGIC5, PO_C109_MAGIC5_2, PO_C109_MAGIC6, PO_C109_MAGIC6_2, PO_C109_MAGIC7, PO_C109_MAGIC7,
	PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7,
	PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7,
	PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7,
	PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7,
	PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7,
	PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7,
	PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7,
	PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7, PO_C109_MAGIC7,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C109_DOWN0, PO_C109_DOWN0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	LABETH_NEUTRAL,	LABETH_FLAME,	0,	0,	RANDOM,	30,
	LABETH_NEUTRAL,	LABETH_MAGIC,	0,	0,	RANDOM,	30,
	LABETH_NEUTRAL,	LABETH_LASER,	0,	0,	RANDOM,	30,
	LABETH_NEUTRAL,	LABETH_MOVE,	0,	0,	RANDOM,	30,
	LABETH_MOVE,	LABETH_FLAME,	0,	0,	RANDOM,	30,
	LABETH_MOVE,	LABETH_MAGIC,	0,	0,	RANDOM,	30,
	LABETH_MOVE,	LABETH_LASER,	0,	0,	RANDOM,	30,
	LABETH_MOVE,	LABETH_NEUTRAL,	0,	0,	RANDOM,	30,
	LABETH_FLAME,	LABETH_NEUTRAL,	0,	0,	0,	0,
	LABETH_MAGIC,	LABETH_NEUTRAL,	0,	0,	0,	0,
	LABETH_LASER,	LABETH_NEUTRAL,	0,	0,	0,	0,
	-1,
};

//엘케인
//순서 바꿀때 124번 END데모신 참조
const signed short c110mv[] = {
	//상태 데이터
	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C110_N0, PO_C110_N0_2, PO_C110_N1, PO_C110_N1_2, PO_C110_N2, PO_C110_N2_2, PO_C110_N3, PO_C110_N3_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_RANDOM,	//초기화 조건
	PO_C110_W0, PO_C110_W0_2, PO_C110_W1, PO_C110_W1_W2_2, PO_C110_W2, PO_C110_W2_2, PO_C110_W1, PO_C110_W1_W0_2,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 2 * _2X, 2 * _2X, 3, 3, 1 * _2X, 1 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C110_GRAB0, PO_C110_GRAB0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C110_EXTRACT0, PO_C110_EXTRACT0, PO_C110_EXTRACT0_1, PO_C110_EXTRACT0_1, PO_C110_EXTRACT0_2, PO_C110_EXTRACT0_2, PO_C110_EXTRACT0_3, PO_C110_EXTRACT0_3,
	PO_C110_EXTRACT1, PO_C110_EXTRACT1, PO_C110_EXTRACT1_1, PO_C110_EXTRACT1_1, PO_C110_EXTRACT1_2, PO_C110_EXTRACT1_2, PO_C110_EXTRACT1_3, PO_C110_EXTRACT1_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	-1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C110_N0_SWORD, PO_C110_N0_SWORD_2, PO_C110_N1_SWORD, PO_C110_N1_SWORD_2, PO_C110_N2_SWORD, PO_C110_N2_SWORD_2, PO_C110_N3_SWORD, PO_C110_N3_SWORD_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C110_EXTRACT2, PO_C110_EXTRACT2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	10,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C110_A0, PO_C110_A0_2, PO_C110_A1, PO_C110_A1_2, PO_C110_A2, PO_C110_A2_2, PO_C110_A3, PO_C110_A3_2,
	PO_C110_A4, PO_C110_A4_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C110_KNEE0, PO_C110_KNEE0,	//상태 프레임별 모션
	-4 * _2X, -4 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C110_KNEE0, PO_C110_KNEE0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C110_BOSS_N0, PO_C110_BOSS_N0_1, PO_C110_BOSS_N0_2, PO_C110_BOSS_N0_3, PO_C110_BOSS_N1, PO_C110_BOSS_N1_1, PO_C110_BOSS_N1_2, PO_C110_BOSS_N1_3,
	PO_C110_BOSS_N2, PO_C110_BOSS_N2_1, PO_C110_BOSS_N2_2, PO_C110_BOSS_N2_3, PO_C110_BOSS_N3, PO_C110_BOSS_N3_1, PO_C110_BOSS_N3_2, PO_C110_BOSS_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12 | SET_DIR_PLAYER,	//초기화 조건
	PO_C110_BOSS_W0, PO_C110_BOSS_W0_1, PO_C110_BOSS_W0_2, PO_C110_BOSS_W0_3, PO_C110_BOSS_W1, PO_C110_BOSS_W1_BOSS_W2_1, PO_C110_BOSS_W1_BOSS_W2_2, PO_C110_BOSS_W1_BOSS_W2_3,
	PO_C110_BOSS_W2, PO_C110_BOSS_W2_1, PO_C110_BOSS_W2_2, PO_C110_BOSS_W2_3, PO_C110_BOSS_W1, PO_C110_BOSS_W1_BOSS_W0_1, PO_C110_BOSS_W1_BOSS_W0_2, PO_C110_BOSS_W1_BOSS_W0_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	64,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C110_BOSS_G0, PO_C110_BOSS_G0, PO_C110_BOSS_G0_1, PO_C110_BOSS_G0_1, PO_C110_BOSS_G0_2, PO_C110_BOSS_G0_2, PO_C110_BOSS_G0_3, PO_C110_BOSS_G0_3,
	PO_C110_BOSS_G1, PO_C110_BOSS_G1, PO_C110_BOSS_G1_1, PO_C110_BOSS_G1_1, PO_C110_BOSS_G1_2, PO_C110_BOSS_G1_2, PO_C110_BOSS_G1_3, PO_C110_BOSS_G1_3,
	PO_C110_BOSS_G2, PO_C110_BOSS_G2, PO_C110_BOSS_G2_1, PO_C110_BOSS_G2_1, PO_C110_BOSS_G2_2, PO_C110_BOSS_G2_2, PO_C110_BOSS_G2_3, PO_C110_BOSS_G2_3,
	PO_C110_BOSS_G3, PO_C110_BOSS_G3, PO_C110_BOSS_G3_1, PO_C110_BOSS_G3_1, PO_C110_BOSS_G3_2, PO_C110_BOSS_G3_2, PO_C110_BOSS_G3_3, PO_C110_BOSS_G3_3,
	PO_C110_BOSS_G4, PO_C110_BOSS_G4, PO_C110_BOSS_G4_1, PO_C110_BOSS_G4_1, PO_C110_BOSS_G4_2, PO_C110_BOSS_G4_2, PO_C110_BOSS_G4_3, PO_C110_BOSS_G4_3,
	PO_C110_BOSS_G5, PO_C110_BOSS_G5, PO_C110_BOSS_G5, PO_C110_BOSS_G5, PO_C110_BOSS_G5, PO_C110_BOSS_G5, PO_C110_BOSS_G5, PO_C110_BOSS_G5,
	PO_C110_BOSS_G5, PO_C110_BOSS_G5, PO_C110_BOSS_G5, PO_C110_BOSS_G5, PO_C110_BOSS_G5, PO_C110_BOSS_G5, PO_C110_BOSS_G5, PO_C110_BOSS_G5,
	PO_C110_BOSS_G5, PO_C110_BOSS_G5, PO_C110_BOSS_G5, PO_C110_BOSS_G5, PO_C110_BOSS_G5, PO_C110_BOSS_G5, PO_C110_BOSS_G5, PO_C110_BOSS_G5,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	64,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C110_BOSS_JA0, PO_C110_BOSS_JA0, PO_C110_BOSS_JA0, PO_C110_BOSS_JA0, PO_C110_BOSS_JA0_1, PO_C110_BOSS_JA0_1, PO_C110_BOSS_JA0_1, PO_C110_BOSS_JA0_1,
	PO_C110_BOSS_JA0_2, PO_C110_BOSS_JA0_2, PO_C110_BOSS_JA0_2, PO_C110_BOSS_JA0_2, PO_C110_BOSS_JA0_3, PO_C110_BOSS_JA0_3, PO_C110_BOSS_JA0_3, PO_C110_BOSS_JA0_3,
	PO_C110_BOSS_JA1, PO_C110_BOSS_JA1_1, PO_C110_BOSS_JA1_2, PO_C110_BOSS_JA1_3, PO_C110_BOSS_JA2, PO_C110_BOSS_JA2_2, PO_C110_BOSS_JA3, PO_C110_BOSS_JA3_2,
	PO_C110_BOSS_JA4, PO_C110_BOSS_JA4_2, PO_C110_BOSS_JA5, PO_C110_BOSS_JA5_2, PO_C110_BOSS_JA6, PO_C110_BOSS_JA6_2, PO_C110_BOSS_JA7, PO_C110_BOSS_JA7_2,
	PO_C110_BOSS_JA8, PO_C110_BOSS_JA8_2, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9,
	PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9,
	PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9,
	PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9, PO_C110_BOSS_JA9,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 3 * _2X, 3 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X,
	4 * _2X, 4 * _2X, 4 * _2X, 4 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	50 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	160,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C110_BOSS_CA0, PO_C110_BOSS_CA0_1, PO_C110_BOSS_CA0_2, PO_C110_BOSS_CA0_3, PO_C110_BOSS_CA1, PO_C110_BOSS_CA1_1, PO_C110_BOSS_CA1_2, PO_C110_BOSS_CA1_3,
	PO_C110_BOSS_CA2, PO_C110_BOSS_CA2_1, PO_C110_BOSS_CA2_2, PO_C110_BOSS_CA2_3, PO_C110_BOSS_CA3, PO_C110_BOSS_CA3_1, PO_C110_BOSS_CA3_2, PO_C110_BOSS_CA3_3,
	PO_C110_BOSS_CA4, PO_C110_BOSS_CA4_1, PO_C110_BOSS_CA4_2, PO_C110_BOSS_CA4_3, PO_C110_BOSS_CA5, PO_C110_BOSS_CA5_BOSS_CA1_1, PO_C110_BOSS_CA5_BOSS_CA1_2, PO_C110_BOSS_CA5_BOSS_CA1_3,
	PO_C110_BOSS_CA1, PO_C110_BOSS_CA1_1, PO_C110_BOSS_CA1_2, PO_C110_BOSS_CA1_3, PO_C110_BOSS_CA2, PO_C110_BOSS_CA2_1, PO_C110_BOSS_CA2_2, PO_C110_BOSS_CA2_3,
	PO_C110_BOSS_CA3, PO_C110_BOSS_CA3_1, PO_C110_BOSS_CA3_2, PO_C110_BOSS_CA3_3, PO_C110_BOSS_CA4, PO_C110_BOSS_CA4_1, PO_C110_BOSS_CA4_2, PO_C110_BOSS_CA4_3,
	PO_C110_BOSS_CA5, PO_C110_BOSS_CA5_BOSS_CA6_1, PO_C110_BOSS_CA5_BOSS_CA6_2, PO_C110_BOSS_CA5_BOSS_CA6_3, PO_C110_BOSS_CA6, PO_C110_BOSS_CA6_1, PO_C110_BOSS_CA6_2, PO_C110_BOSS_CA6_3,
	PO_C110_BOSS_CA7, PO_C110_BOSS_CA7_1, PO_C110_BOSS_CA7_2, PO_C110_BOSS_CA7_3, PO_C110_BOSS_CA8, PO_C110_BOSS_CA8, PO_C110_BOSS_CA8, PO_C110_BOSS_CA8,
	PO_C110_BOSS_CA8, PO_C110_BOSS_CA8, PO_C110_BOSS_CA8, PO_C110_BOSS_CA8, PO_C110_BOSS_CA8, PO_C110_BOSS_CA8_1, PO_C110_BOSS_CA8_1, PO_C110_BOSS_CA8_1,
	PO_C110_BOSS_CA8_1, PO_C110_BOSS_CA8_1, PO_C110_BOSS_CA8_1, PO_C110_BOSS_CA8_1, PO_C110_BOSS_CA8_1, PO_C110_BOSS_CA8_1, PO_C110_BOSS_CA8_2, PO_C110_BOSS_CA8_2,
	PO_C110_BOSS_CA8_2, PO_C110_BOSS_CA8_2, PO_C110_BOSS_CA8_2, PO_C110_BOSS_CA8_2, PO_C110_BOSS_CA8_2, PO_C110_BOSS_CA8_2, PO_C110_BOSS_CA8_2, PO_C110_BOSS_CA8_3,
	PO_C110_BOSS_CA8_3, PO_C110_BOSS_CA8_3, PO_C110_BOSS_CA8_3, PO_C110_BOSS_CA8_3, PO_C110_BOSS_CA8_3, PO_C110_BOSS_CA8_3, PO_C110_BOSS_CA8_3, PO_C110_BOSS_CA8_3,
	PO_C110_BOSS_CA9, PO_C110_BOSS_CA9_1, PO_C110_BOSS_CA9_2, PO_C110_BOSS_CA9_3, PO_C110_BOSS_CA10, PO_C110_BOSS_CA10, PO_C110_BOSS_CA10_1, PO_C110_BOSS_CA10_1,
	PO_C110_BOSS_CA10_2, PO_C110_BOSS_CA10_2, PO_C110_BOSS_CA10_3, PO_C110_BOSS_CA10_3, PO_C110_BOSS_CA11, PO_C110_BOSS_CA11_1, PO_C110_BOSS_CA11_2, PO_C110_BOSS_CA11_3,
	PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12,
	PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12,
	PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12,
	PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12,
	PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12,
	PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12,
	PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12, PO_C110_BOSS_CA12,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	72,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C110_BOSS_SA0, PO_C110_BOSS_SA0, PO_C110_BOSS_SA0, PO_C110_BOSS_SA0, PO_C110_BOSS_SA0, PO_C110_BOSS_SA0, PO_C110_BOSS_SA0_1, PO_C110_BOSS_SA0_1,
	PO_C110_BOSS_SA0_1, PO_C110_BOSS_SA0_1, PO_C110_BOSS_SA0_1, PO_C110_BOSS_SA0_1, PO_C110_BOSS_SA0_2, PO_C110_BOSS_SA0_2, PO_C110_BOSS_SA0_2, PO_C110_BOSS_SA0_2,
	PO_C110_BOSS_SA0_2, PO_C110_BOSS_SA0_2, PO_C110_BOSS_SA0_3, PO_C110_BOSS_SA0_3, PO_C110_BOSS_SA0_3, PO_C110_BOSS_SA0_3, PO_C110_BOSS_SA0_3, PO_C110_BOSS_SA0_3,
	PO_C110_BOSS_SA1, PO_C110_BOSS_SA1_2, PO_C110_BOSS_SA2, PO_C110_BOSS_SA2_2, PO_C110_BOSS_SA3, PO_C110_BOSS_SA3_2, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4,
	PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4,
	PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4,
	PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4,
	PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4,
	PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4, PO_C110_BOSS_SA4,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C110_CRAWL0, PO_C110_CRAWL0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	8,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM12,	//초기화 조건
	PO_C110_CRAWL0, PO_C110_CRAWL0_2, PO_C110_CRAWL1, PO_C110_CRAWL1_2, PO_C110_CRAWL2, PO_C110_CRAWL2_2, PO_C110_CRAWL3, PO_C110_CRAWL3_2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,

	//ACTIONRPG
	//상태변경
	ELKEIN_NEUTRAL,	ELKEIN_DASH,	DISTANCE_OUT_XY,	6 * 8 + 6,	RANDOM,	20,
	ELKEIN_NEUTRAL,	ELKEIN_BULLET,	DISTANCE_OUT_XY,	6 * 8 + 6,	RANDOM,	20,
	ELKEIN_NEUTRAL,	ELKEIN_JUMPATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 6,	RANDOM,	30,
	ELKEIN_NEUTRAL,	ELKEIN_GUARD,	DISTANCE_CHECK_XY,	6 * 8 + 6,	RANDOM,	70,
	ELKEIN_NEUTRAL,	ELKEIN_MOVE,	0,	0,	RANDOM,	30,
	ELKEIN_MOVE,	ELKEIN_DASH,	DISTANCE_OUT_XY,	6 * 8 + 6,	RANDOM,	20,
	ELKEIN_MOVE,	ELKEIN_BULLET,	DISTANCE_OUT_XY,	6 * 8 + 6,	RANDOM,	20,
	ELKEIN_MOVE,	ELKEIN_JUMPATTACK,	DISTANCE_CHECK_XY,	6 * 8 + 6,	RANDOM,	30,
	ELKEIN_MOVE,	ELKEIN_GUARD,	DISTANCE_CHECK_XY,	6 * 8 + 6,	RANDOM,	70,
	ELKEIN_MOVE,	ELKEIN_NEUTRAL,	0,	0,	RANDOM,	30,
	ELKEIN_DASH,	ELKEIN_NEUTRAL,	0,	0,	0,	0,
	ELKEIN_BULLET,	ELKEIN_NEUTRAL,	0,	0,	0,	0,
	ELKEIN_GUARD,	ELKEIN_NEUTRAL,	0,	0,	0,	0,
	ELKEIN_JUMPATTACK,	ELKEIN_NEUTRAL,	0,	0,	0,	0,
	-1,
};

//엘레인
const signed short c111mv[] = {
	//상태 데이터
	//ELEIN_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C111_N0, PO_C111_N0_1, PO_C111_N0_2, PO_C111_N0_3, PO_C111_N1, PO_C111_N1_1, PO_C111_N1_2, PO_C111_N1_3,
	PO_C111_N2, PO_C111_N2_1, PO_C111_N2_2, PO_C111_N2_3, PO_C111_N3, PO_C111_N3_1, PO_C111_N3_2, PO_C111_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ELEIN_DOWN
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C111_DIE1, PO_C111_DIE1, PO_C111_DIE1, PO_C111_DIE1, PO_C111_DIE1, PO_C111_DIE1, PO_C111_DIE1, PO_C111_DIE1,
	PO_C111_DIE1, PO_C111_DIE1, PO_C111_DIE1, PO_C111_DIE1, PO_C111_DIE1, PO_C111_DIE1, PO_C111_DIE1, PO_C111_DIE1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ELEIN_DOWNHOLD
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C111_DIE2, PO_C111_DIE2, PO_C111_DIE2, PO_C111_DIE2, PO_C111_DIE2_1, PO_C111_DIE2_1, PO_C111_DIE2_1, PO_C111_DIE2_1,
	PO_C111_DIE2_2, PO_C111_DIE2_2, PO_C111_DIE2_2, PO_C111_DIE2_2, PO_C111_DIE2_3, PO_C111_DIE2_3, PO_C111_DIE2_3, PO_C111_DIE2_3,
	PO_C111_DIE3, PO_C111_DIE3, PO_C111_DIE3, PO_C111_DIE3, PO_C111_DIE3_1, PO_C111_DIE3_1, PO_C111_DIE3_1, PO_C111_DIE3_1,
	PO_C111_DIE3_2, PO_C111_DIE3_2, PO_C111_DIE3_2, PO_C111_DIE3_2, PO_C111_DIE3_3, PO_C111_DIE3_3, PO_C111_DIE3_3, PO_C111_DIE3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ELEIN_NEUTRAL_GHOST
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C111_DIE3, PO_C111_DIE3, PO_C111_DIE3, PO_C111_DIE3, PO_C111_DIE3, PO_C111_DIE3, PO_C111_DIE3, PO_C111_DIE3,
	PO_C111_DIE3, PO_C111_DIE3, PO_C111_DIE3, PO_C111_DIE3, PO_C111_DIE3, PO_C111_DIE3, PO_C111_DIE3, PO_C111_DIE3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ELEIN_SURPRISE_GHOST
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C111_N0_GHOST, PO_C111_N0_GHOST_1, PO_C111_N0_GHOST_2, PO_C111_N0_GHOST_3, PO_C111_N1_GHOST, PO_C111_N1_GHOST_1, PO_C111_N1_GHOST_2, PO_C111_N1_GHOST_3,
	PO_C111_N2_GHOST, PO_C111_N2_GHOST_1, PO_C111_N2_GHOST_2, PO_C111_N2_GHOST_3, PO_C111_N3_GHOST, PO_C111_N3_GHOST_1, PO_C111_N3_GHOST_2, PO_C111_N3_GHOST_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ELEIN_HUG_GHOST
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C111_ARREST0_GHOST, PO_C111_ARREST0_GHOST_1, PO_C111_ARREST0_GHOST_2, PO_C111_ARREST0_GHOST_3, PO_C111_ARREST1_GHOST, PO_C111_ARREST1_GHOST_1, PO_C111_ARREST1_GHOST_2, PO_C111_ARREST1_GHOST_3,
	PO_C111_ARREST2_GHOST, PO_C111_ARREST2_GHOST_1, PO_C111_ARREST2_GHOST_2, PO_C111_ARREST2_GHOST_3, PO_C111_ARREST3_GHOST, PO_C111_ARREST3_GHOST_1, PO_C111_ARREST3_GHOST_2, PO_C111_ARREST3_GHOST_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ELEIN_LIGHT_GHOST
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C111_SURPRISE0_GHOST, PO_C111_SURPRISE0_GHOST_1, PO_C111_SURPRISE0_GHOST_2, PO_C111_SURPRISE0_GHOST_3, PO_C111_SURPRISE1_GHOST, PO_C111_SURPRISE1_GHOST_1, PO_C111_SURPRISE1_GHOST_2, PO_C111_SURPRISE1_GHOST_3,
	PO_C111_SURPRISE2_GHOST, PO_C111_SURPRISE2_GHOST_1, PO_C111_SURPRISE2_GHOST_2, PO_C111_SURPRISE2_GHOST_3, PO_C111_SURPRISE3_GHOST, PO_C111_SURPRISE3_GHOST_1, PO_C111_SURPRISE3_GHOST_2, PO_C111_SURPRISE3_GHOST_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//ELEIN_DISAPPEAR_GHOST
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C111_HUG0, PO_C111_HUG0_1, PO_C111_HUG0_2, PO_C111_HUG0_3, PO_C111_HUG1, PO_C111_HUG1_1, PO_C111_HUG1_2, PO_C111_HUG1_3,
	PO_C111_HUG2, PO_C111_HUG2_1, PO_C111_HUG2_2, PO_C111_HUG2_3, PO_C111_HUG3, PO_C111_HUG3_1, PO_C111_HUG3_2, PO_C111_HUG3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C111_LIGHT0, PO_C111_LIGHT0_1, PO_C111_LIGHT0_2, PO_C111_LIGHT0_3, PO_C111_LIGHT1, PO_C111_LIGHT1_1, PO_C111_LIGHT1_2, PO_C111_LIGHT1_3,
	PO_C111_LIGHT2, PO_C111_LIGHT2_1, PO_C111_LIGHT2_2, PO_C111_LIGHT2_3, PO_C111_LIGHT3, PO_C111_LIGHT3_1, PO_C111_LIGHT3_2, PO_C111_LIGHT3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C111_DIS0, PO_C111_DIS0_1, PO_C111_DIS0_2, PO_C111_DIS0_3, PO_C111_DIS1, PO_C111_DIS1_1, PO_C111_DIS1_2, PO_C111_DIS1_3,
	PO_C111_DIS2, PO_C111_DIS2_1, PO_C111_DIS2_2, PO_C111_DIS2_3, PO_C111_DIS3, PO_C111_DIS3_1, PO_C111_DIS3_2, PO_C111_DIS3_3,
	PO_C111_DIS4, PO_C111_DIS4_1, PO_C111_DIS4_2, PO_C111_DIS4_3, PO_C111_DIS5, PO_C111_DIS5_1, PO_C111_DIS5_2, PO_C111_DIS5_3,
	PO_C111_DIS6, PO_C111_DIS6_1, PO_C111_DIS6_2, PO_C111_DIS6_3, PO_C111_DIS7, PO_C111_DIS7_1, PO_C111_DIS7_2, PO_C111_DIS7_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

//에반
const signed short c112mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_N0, PO_C112_N0_1, PO_C112_N0_2, PO_C112_N0_3, PO_C112_N1, PO_C112_N1_1, PO_C112_N1_2, PO_C112_N1_3,
	PO_C112_N2, PO_C112_N2_1, PO_C112_N2_2, PO_C112_N2_3, PO_C112_N3, PO_C112_N3_1, PO_C112_N3_2, PO_C112_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_W0, PO_C112_W0_1, PO_C112_W0_2, PO_C112_W0_3, PO_C112_W1, PO_C112_W1_W2_1, PO_C112_W1_W2_2, PO_C112_W1_W2_3,
	PO_C112_W2, PO_C112_W2_1, PO_C112_W2_2, PO_C112_W2_3, PO_C112_W1, PO_C112_W1_W0_1, PO_C112_W1_W0_2, PO_C112_W1_W0_3,	//상태 프레임별 모션
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X, 3 * _2X, 3 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_A0, PO_C112_A0, PO_C112_A0_1, PO_C112_A0_1, PO_C112_A0_2, PO_C112_A0_2, PO_C112_A0_3, PO_C112_A0_3,
	PO_C112_A1, PO_C112_A1_1, PO_C112_A1_2, PO_C112_A1_3, PO_C112_A2, PO_C112_A2_1, PO_C112_A2_2, PO_C112_A2_3,
	PO_C112_A3, PO_C112_A3_1, PO_C112_A3_2, PO_C112_A3_3, PO_C112_A4, PO_C112_A4_1, PO_C112_A4_2, PO_C112_A4_3,
	PO_C112_A5, PO_C112_A5_1, PO_C112_A5_2, PO_C112_A5_3, PO_C112_A6, PO_C112_A6_1, PO_C112_A6_2, PO_C112_A6_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 5, 5, 5, 5,
	5, 5, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 5, 5, 5, 5,
	5, 5, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_D0, PO_C112_D0, PO_C112_D0, PO_C112_D0, PO_C112_D0, PO_C112_D0, PO_C112_D0, PO_C112_D0,
	PO_C112_D0, PO_C112_D0, PO_C112_D0, PO_C112_D0, PO_C112_D0, PO_C112_D0, PO_C112_D0, PO_C112_D0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0,
	PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	20,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0,
	PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0,
	PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0, PO_C112_KNEE0,	//상태 프레임별 모션
	-5, -5, -5, -5, -2 * _2X, -2 * _2X, -2 * _2X, -2 * _2X,
	-3, -3, -3, -3, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X,
	-1, -1, -1, -1,	//상태 프레임별 이동폭 X
	102 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_W0, PO_C112_W0_2, PO_C112_W1, PO_C112_W1_W2_2, PO_C112_W2, PO_C112_W2_2, PO_C112_W1, PO_C112_W1_W0_2,
	PO_C112_W0, PO_C112_W0_2, PO_C112_W1, PO_C112_W1_W2_2, PO_C112_W2, PO_C112_W2_2, PO_C112_W1, PO_C112_W1_W0_2,
	PO_C112_W0, PO_C112_W0_2, PO_C112_W1, PO_C112_W1_W2_2, PO_C112_W2, PO_C112_W2_2, PO_C112_W1, PO_C112_W1_W0_2,
	PO_C112_W0, PO_C112_W0_2, PO_C112_W1, PO_C112_W1_W2_2, PO_C112_W2, PO_C112_W2_2, PO_C112_W1, PO_C112_W1_W0_2,	//상태 프레임별 모션
	5 * _2X, 5 * _2X, 4 * _2X, 4 * _2X, 5 * _2X, 5 * _2X, 4 * _2X, 4 * _2X,
	5 * _2X, 5 * _2X, 4 * _2X, 4 * _2X, 5 * _2X, 5 * _2X, 4 * _2X, 4 * _2X,
	5 * _2X, 5 * _2X, 4 * _2X, 4 * _2X, 5 * _2X, 5 * _2X, 4 * _2X, 4 * _2X,
	5 * _2X, 5 * _2X, 4 * _2X, 4 * _2X, 5 * _2X, 5 * _2X, 4 * _2X, 4 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_THROW0, PO_C112_THROW0, PO_C112_THROW0, PO_C112_THROW0, PO_C112_THROW0, PO_C112_THROW0, PO_C112_THROW0_1, PO_C112_THROW0_1,
	PO_C112_THROW0_1, PO_C112_THROW0_1, PO_C112_THROW0_1, PO_C112_THROW0_1, PO_C112_THROW0_2, PO_C112_THROW0_2, PO_C112_THROW0_2, PO_C112_THROW0_2,
	PO_C112_THROW0_2, PO_C112_THROW0_2, PO_C112_THROW0_3, PO_C112_THROW0_3, PO_C112_THROW0_3, PO_C112_THROW0_3, PO_C112_THROW0_3, PO_C112_THROW0_3,
	PO_C112_THROW1, PO_C112_THROW1, PO_C112_THROW1_1, PO_C112_THROW1_1, PO_C112_THROW1_2, PO_C112_THROW1_2, PO_C112_THROW1_3, PO_C112_THROW1_3,	//상태 프레임별 모션
	-1, -1, -1, -1, -1, -1, -1, -1,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_N0_BABY, PO_C112_N0_BABY_1, PO_C112_N0_BABY_2, PO_C112_N0_BABY_3, PO_C112_N1_BABY, PO_C112_N1_BABY_1, PO_C112_N1_BABY_2, PO_C112_N1_BABY_3,
	PO_C112_N2_BABY, PO_C112_N2_BABY_1, PO_C112_N2_BABY_2, PO_C112_N2_BABY_3, PO_C112_N3_BABY, PO_C112_N3_BABY_1, PO_C112_N3_BABY_2, PO_C112_N3_BABY_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_GA0, PO_C112_GA0, PO_C112_GA0, PO_C112_GA0, PO_C112_GA0, PO_C112_GA0, PO_C112_GA0, PO_C112_GA0,
	PO_C112_GA0, PO_C112_GA0, PO_C112_GA0, PO_C112_GA0, PO_C112_GA0, PO_C112_GA0, PO_C112_GA0, PO_C112_GA0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1,
	PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1,	//상태 프레임별 모션
	-1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X,
	-1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1,
	PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1, PO_C112_GA1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_GA2, PO_C112_GA2, PO_C112_GA2, PO_C112_GA2, PO_C112_GA2, PO_C112_GA2, PO_C112_GA2, PO_C112_GA2,
	PO_C112_GA2, PO_C112_GA2, PO_C112_GA2, PO_C112_GA2, PO_C112_GA2, PO_C112_GA2, PO_C112_GA2, PO_C112_GA2,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	40,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_SHOW0, PO_C112_SHOW0_1, PO_C112_SHOW0_2, PO_C112_SHOW0_3, PO_C112_SHOW1, PO_C112_SHOW1_1, PO_C112_SHOW1_2, PO_C112_SHOW1_3,
	PO_C112_SHOW2, PO_C112_SHOW2_1, PO_C112_SHOW2_2, PO_C112_SHOW2_3, PO_C112_SHOW3, PO_C112_SHOW3_1, PO_C112_SHOW3_2, PO_C112_SHOW3_3,
	PO_C112_SHOW4, PO_C112_SHOW4, PO_C112_SHOW4, PO_C112_SHOW4, PO_C112_SHOW4, PO_C112_SHOW4, PO_C112_SHOW4_1, PO_C112_SHOW4_1,
	PO_C112_SHOW4_1, PO_C112_SHOW4_1, PO_C112_SHOW4_1, PO_C112_SHOW4_1, PO_C112_SHOW4_2, PO_C112_SHOW4_2, PO_C112_SHOW4_2, PO_C112_SHOW4_2,
	PO_C112_SHOW4_2, PO_C112_SHOW4_2, PO_C112_SHOW4_3, PO_C112_SHOW4_3, PO_C112_SHOW4_3, PO_C112_SHOW4_3, PO_C112_SHOW4_3, PO_C112_SHOW4_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_N0_SWORD, PO_C112_N0_SWORD_1, PO_C112_N0_SWORD_2, PO_C112_N0_SWORD_3, PO_C112_N1_SWORD, PO_C112_N1_SWORD_1, PO_C112_N1_SWORD_2, PO_C112_N1_SWORD_3,
	PO_C112_N2_SWORD, PO_C112_N2_SWORD_1, PO_C112_N2_SWORD_2, PO_C112_N2_SWORD_3, PO_C112_N3_SWORD, PO_C112_N3_SWORD_1, PO_C112_N3_SWORD_2, PO_C112_N3_SWORD_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_JA1, PO_C112_JA1_1, PO_C112_JA1_2, PO_C112_JA1_3, PO_C112_JA2, PO_C112_JA2_1, PO_C112_JA2_2, PO_C112_JA2_3,
	PO_C112_JA3, PO_C112_JA3_1, PO_C112_JA3_2, PO_C112_JA3_3, PO_C112_JA4, PO_C112_JA4_1, PO_C112_JA4_2, PO_C112_JA4_3,
	PO_C112_JA5, PO_C112_JA5, PO_C112_JA5, PO_C112_JA5, PO_C112_JA5_1, PO_C112_JA5_1, PO_C112_JA5_1, PO_C112_JA5_1,
	PO_C112_JA5_2, PO_C112_JA5_2, PO_C112_JA5_2, PO_C112_JA5_2, PO_C112_JA5_3, PO_C112_JA5_3, PO_C112_JA5_3, PO_C112_JA5_3,	//상태 프레임별 모션
	3, 3, 1 * _2X, 1 * _2X, 3, 3, 1 * _2X, 1 * _2X,
	3, 3, 1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	3 * _2X, 3 * _2X, 2 * _2X, 2 * _2X, 3 * _2X, 3 * _2X, 2 * _2X, 2 * _2X,
	3 * _2X, 3 * _2X, 2 * _2X, 2 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 100 * _2X, 0 * _2X, 100 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_D1, PO_C112_D1, PO_C112_D1, PO_C112_D1, PO_C112_D1, PO_C112_D1, PO_C112_D1, PO_C112_D1,
	PO_C112_D1, PO_C112_D1, PO_C112_D1, PO_C112_D1, PO_C112_D1, PO_C112_D1, PO_C112_D1, PO_C112_D1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_SWORD, PO_C112_SWORD, PO_C112_SWORD, PO_C112_SWORD, PO_C112_SWORD, PO_C112_SWORD, PO_C112_SWORD, PO_C112_SWORD,
	PO_C112_SWORD, PO_C112_SWORD, PO_C112_SWORD, PO_C112_SWORD, PO_C112_SWORD, PO_C112_SWORD, PO_C112_SWORD, PO_C112_SWORD,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C112_HAND0, PO_C112_HAND0, PO_C112_HAND0_1, PO_C112_HAND0_1, PO_C112_HAND0_2, PO_C112_HAND0_2, PO_C112_HAND0_3, PO_C112_HAND0_3,
	PO_C112_HAND1, PO_C112_HAND1, PO_C112_HAND1_1, PO_C112_HAND1_1, PO_C112_HAND1_2, PO_C112_HAND1_2, PO_C112_HAND1_3, PO_C112_HAND1_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c113mv[] = {
	//상태 데이터
	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C113_N0, PO_C113_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	2,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C113_N1, PO_C113_N1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c114mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C114_N0, PO_C114_N0, PO_C114_N0, PO_C114_N0, PO_C114_N0, PO_C114_N0, PO_C114_N0, PO_C114_N0,
	PO_C114_N0, PO_C114_N0, PO_C114_N0, PO_C114_N0, PO_C114_N0, PO_C114_N0, PO_C114_N0, PO_C114_N0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	88,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C114_MAGIC0, PO_C114_MAGIC0, PO_C114_MAGIC0_1, PO_C114_MAGIC0_1, PO_C114_MAGIC0_2, PO_C114_MAGIC0_2, PO_C114_MAGIC0_3, PO_C114_MAGIC0_3,
	PO_C114_MAGIC1, PO_C114_MAGIC1, PO_C114_MAGIC1_1, PO_C114_MAGIC1_1, PO_C114_MAGIC1_2, PO_C114_MAGIC1_2, PO_C114_MAGIC1_3, PO_C114_MAGIC1_3,
	PO_C114_MAGIC2, PO_C114_MAGIC2, PO_C114_MAGIC2_1, PO_C114_MAGIC2_1, PO_C114_MAGIC2_2, PO_C114_MAGIC2_2, PO_C114_MAGIC2_3, PO_C114_MAGIC2_3,
	PO_C114_MAGIC3, PO_C114_MAGIC3, PO_C114_MAGIC3_1, PO_C114_MAGIC3_1, PO_C114_MAGIC3_2, PO_C114_MAGIC3_2, PO_C114_MAGIC3_3, PO_C114_MAGIC3_3,
	PO_C114_MAGIC4, PO_C114_MAGIC4, PO_C114_MAGIC4_1, PO_C114_MAGIC4_1, PO_C114_MAGIC4_2, PO_C114_MAGIC4_2, PO_C114_MAGIC4_3, PO_C114_MAGIC4_3,
	PO_C114_N0, PO_C114_N0_1, PO_C114_N0_2, PO_C114_N0_3, PO_C114_N1, PO_C114_N1_N0_1, PO_C114_N1_N0_2, PO_C114_N1_N0_3,
	PO_C114_N0, PO_C114_N0_1, PO_C114_N0_2, PO_C114_N0_3, PO_C114_N1, PO_C114_N1_N0_1, PO_C114_N1_N0_2, PO_C114_N1_N0_3,
	PO_C114_N0, PO_C114_N0_1, PO_C114_N0_2, PO_C114_N0_3, PO_C114_N1, PO_C114_N1_N0_1, PO_C114_N1_N0_2, PO_C114_N1_N0_3,
	PO_C114_N0, PO_C114_N0_1, PO_C114_N0_2, PO_C114_N0_3, PO_C114_N1, PO_C114_N1_N0_1, PO_C114_N1_N0_2, PO_C114_N1_N0_3,
	PO_C114_N0, PO_C114_N0_1, PO_C114_N0_2, PO_C114_N0_3, PO_C114_N1, PO_C114_N1_N0_1, PO_C114_N1_N0_2, PO_C114_N1_N0_3,
	PO_C114_N0, PO_C114_N0_1, PO_C114_N0_2, PO_C114_N0_3, PO_C114_N1, PO_C114_N1_MAGIC0_1, PO_C114_N1_MAGIC0_2, PO_C114_N1_MAGIC0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	48,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C114_WATER0, PO_C114_WATER0_1, PO_C114_WATER0_2, PO_C114_WATER0_3, PO_C114_WATER1, PO_C114_WATER1_1, PO_C114_WATER1_2, PO_C114_WATER1_3,
	PO_C114_WATER2, PO_C114_WATER2_1, PO_C114_WATER2_2, PO_C114_WATER2_3, PO_C114_WATER0, PO_C114_WATER0_2, PO_C114_WATER1, PO_C114_WATER1_2,
	PO_C114_WATER2, PO_C114_WATER2_2, PO_C114_WATER0, PO_C114_WATER0_2, PO_C114_WATER1, PO_C114_WATER1_2, PO_C114_WATER2, PO_C114_WATER2_2,
	PO_C114_WATER0, PO_C114_WATER0_2, PO_C114_WATER1, PO_C114_WATER1_2, PO_C114_WATER2, PO_C114_WATER2_2, PO_C114_WATER0, PO_C114_WATER0_2,
	PO_C114_WATER1, PO_C114_WATER1_2, PO_C114_WATER2, PO_C114_WATER2_2, PO_C114_WATER0, PO_C114_WATER0_1, PO_C114_WATER0_2, PO_C114_WATER0_3,
	PO_C114_WATER1, PO_C114_WATER1_1, PO_C114_WATER1_2, PO_C114_WATER1_3, PO_C114_WATER2, PO_C114_WATER2_1, PO_C114_WATER2_2, PO_C114_WATER2_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c115mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C115_N0, PO_C115_N0_1, PO_C115_N0_2, PO_C115_N0_3, PO_C115_N1, PO_C115_N1_1, PO_C115_N1_2, PO_C115_N1_3,
	PO_C115_N2, PO_C115_N2_1, PO_C115_N2_2, PO_C115_N2_3, PO_C115_N3, PO_C115_N3_1, PO_C115_N3_2, PO_C115_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C115_MAGIC0, PO_C115_MAGIC0_1, PO_C115_MAGIC0_2, PO_C115_MAGIC0_3, PO_C115_MAGIC1, PO_C115_MAGIC1_1, PO_C115_MAGIC1_2, PO_C115_MAGIC1_3,
	PO_C115_MAGIC2, PO_C115_MAGIC2_1, PO_C115_MAGIC2_2, PO_C115_MAGIC2_3, PO_C115_MAGIC3, PO_C115_MAGIC3_1, PO_C115_MAGIC3_2, PO_C115_MAGIC3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c116mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C116_N0, PO_C116_N0_1, PO_C116_N0_2, PO_C116_N0_3, PO_C116_N1, PO_C116_N1_1, PO_C116_N1_2, PO_C116_N1_3,
	PO_C116_N2, PO_C116_N2_1, PO_C116_N2_2, PO_C116_N2_3, PO_C116_N3, PO_C116_N3_1, PO_C116_N3_2, PO_C116_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C116_W0, PO_C116_W0_1, PO_C116_W0_2, PO_C116_W0_3, PO_C116_W1, PO_C116_W1_W2_1, PO_C116_W1_W2_2, PO_C116_W1_W2_3,
	PO_C116_W2, PO_C116_W2_1, PO_C116_W2_2, PO_C116_W2_3, PO_C116_W1, PO_C116_W1_W0_1, PO_C116_W1_W0_2, PO_C116_W1_W0_3,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	24,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C116_A0, PO_C116_A0_1, PO_C116_A0_2, PO_C116_A0_3, PO_C116_A1, PO_C116_A1_1, PO_C116_A1_2, PO_C116_A1_3,
	PO_C116_A2, PO_C116_A2_1, PO_C116_A2_2, PO_C116_A2_3, PO_C116_A3, PO_C116_A3_1, PO_C116_A3_2, PO_C116_A3_3,
	PO_C116_A4, PO_C116_A4, PO_C116_A4_1, PO_C116_A4_1, PO_C116_A4_2, PO_C116_A4_2, PO_C116_A4_3, PO_C116_A4_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C116_D0, PO_C116_D0, PO_C116_D0, PO_C116_D0, PO_C116_D0, PO_C116_D0, PO_C116_D0, PO_C116_D0,
	PO_C116_D0, PO_C116_D0, PO_C116_D0, PO_C116_D0, PO_C116_D0, PO_C116_D0, PO_C116_D0, PO_C116_D0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c117mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C117_N0, PO_C117_N0_1, PO_C117_N0_2, PO_C117_N0_3, PO_C117_N1, PO_C117_N1_1, PO_C117_N1_2, PO_C117_N1_3,
	PO_C117_N2, PO_C117_N2_1, PO_C117_N2_2, PO_C117_N2_3, PO_C117_N3, PO_C117_N3_1, PO_C117_N3_2, PO_C117_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C117_W0, PO_C117_W0_1, PO_C117_W0_2, PO_C117_W0_3, PO_C117_W1, PO_C117_W1_W2_1, PO_C117_W1_W2_2, PO_C117_W1_W2_3,
	PO_C117_W2, PO_C117_W2_1, PO_C117_W2_2, PO_C117_W2_3, PO_C117_W1, PO_C117_W1_W0_1, PO_C117_W1_W0_2, PO_C117_W1_W0_3,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c118mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C118_N0, PO_C118_N0_1, PO_C118_N0_2, PO_C118_N0_3, PO_C118_N1, PO_C118_N1_1, PO_C118_N1_2, PO_C118_N1_3,
	PO_C118_N2, PO_C118_N2_1, PO_C118_N2_2, PO_C118_N2_3, PO_C118_N3, PO_C118_N3_1, PO_C118_N3_2, PO_C118_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	48,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C118_W0, PO_C118_W0, PO_C118_W0, PO_C118_W0_1, PO_C118_W0_1, PO_C118_W0_1, PO_C118_W0_2, PO_C118_W0_2,
	PO_C118_W0_2, PO_C118_W0_3, PO_C118_W0_3, PO_C118_W0_3, PO_C118_W1, PO_C118_W1, PO_C118_W1, PO_C118_W1_W2_1,
	PO_C118_W1_W2_1, PO_C118_W1_W2_1, PO_C118_W1_W2_2, PO_C118_W1_W2_2, PO_C118_W1_W2_2, PO_C118_W1_W2_3, PO_C118_W1_W2_3, PO_C118_W1_W2_3,
	PO_C118_W2, PO_C118_W2, PO_C118_W2, PO_C118_W2_1, PO_C118_W2_1, PO_C118_W2_1, PO_C118_W2_2, PO_C118_W2_2,
	PO_C118_W2_2, PO_C118_W2_3, PO_C118_W2_3, PO_C118_W2_3, PO_C118_W1, PO_C118_W1, PO_C118_W1, PO_C118_W1_W0_1,
	PO_C118_W1_W0_1, PO_C118_W1_W0_1, PO_C118_W1_W0_2, PO_C118_W1_W0_2, PO_C118_W1_W0_2, PO_C118_W1_W0_3, PO_C118_W1_W0_3, PO_C118_W1_W0_3,	//상태 프레임별 모션
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C118_WEAK, PO_C118_WEAK, PO_C118_WEAK, PO_C118_WEAK, PO_C118_WEAK, PO_C118_WEAK, PO_C118_WEAK, PO_C118_WEAK,
	PO_C118_WEAK, PO_C118_WEAK, PO_C118_WEAK, PO_C118_WEAK, PO_C118_WEAK, PO_C118_WEAK, PO_C118_WEAK, PO_C118_WEAK,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C118_CHAIR, PO_C118_CHAIR, PO_C118_CHAIR, PO_C118_CHAIR, PO_C118_CHAIR, PO_C118_CHAIR, PO_C118_CHAIR, PO_C118_CHAIR,
	PO_C118_CHAIR, PO_C118_CHAIR, PO_C118_CHAIR, PO_C118_CHAIR, PO_C118_CHAIR, PO_C118_CHAIR, PO_C118_CHAIR, PO_C118_CHAIR,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c119mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C119_N0, PO_C119_N0_1, PO_C119_N0_2, PO_C119_N0_3, PO_C119_N1, PO_C119_N1_1, PO_C119_N1_2, PO_C119_N1_3,
	PO_C119_N2, PO_C119_N2_1, PO_C119_N2_2, PO_C119_N2_3, PO_C119_N3, PO_C119_N3_1, PO_C119_N3_2, PO_C119_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c120mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C120_N0, PO_C120_N0_1, PO_C120_N0_2, PO_C120_N0_3, PO_C120_N1, PO_C120_N1_1, PO_C120_N1_2, PO_C120_N1_3,
	PO_C120_N2, PO_C120_N2_1, PO_C120_N2_2, PO_C120_N2_3, PO_C120_N3, PO_C120_N3_1, PO_C120_N3_2, PO_C120_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C120_N0, PO_C120_N0_1, PO_C120_N0_2, PO_C120_N0_3, PO_C120_N1, PO_C120_N1_1, PO_C120_N1_2, PO_C120_N1_3,
	PO_C120_N2, PO_C120_N2_1, PO_C120_N2_2, PO_C120_N2_3, PO_C120_N3, PO_C120_N3_1, PO_C120_N3_2, PO_C120_N3_3,	//상태 프레임별 모션
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,
	2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X, 2 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C120_N0, PO_C120_N0_1, PO_C120_N0_2, PO_C120_N0_3, PO_C120_N1, PO_C120_N1_1, PO_C120_N1_2, PO_C120_N1_3,
	PO_C120_N2, PO_C120_N2_1, PO_C120_N2_2, PO_C120_N2_3, PO_C120_N3, PO_C120_N3_1, PO_C120_N3_2, PO_C120_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	-1 * _2X, -1 * _2X, 0 * _2X, 0 * _2X, 1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X,
	-1 * _2X, -1 * _2X, 0 * _2X, 0 * _2X, 1 * _2X, 1 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c121mv[] = {
	//상태 데이터
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C121_N0, PO_C121_N0_1, PO_C121_N0_2, PO_C121_N0_3, PO_C121_N1, PO_C121_N1_1, PO_C121_N1_2, PO_C121_N1_3,
	PO_C121_N2, PO_C121_N2_1, PO_C121_N2_2, PO_C121_N2_3, PO_C121_N3, PO_C121_N3_1, PO_C121_N3_2, PO_C121_N3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C121_STATUE0, PO_C121_STATUE0_1, PO_C121_STATUE0_2, PO_C121_STATUE0_3, PO_C121_STATUE1, PO_C121_STATUE1_1, PO_C121_STATUE1_2, PO_C121_STATUE1_3,
	PO_C121_STATUE2, PO_C121_STATUE2_1, PO_C121_STATUE2_2, PO_C121_STATUE2_3, PO_C121_STATUE3, PO_C121_STATUE3_1, PO_C121_STATUE3_2, PO_C121_STATUE3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C121_LIGHT0, PO_C121_LIGHT0_1, PO_C121_LIGHT0_2, PO_C121_LIGHT0_3, PO_C121_LIGHT1, PO_C121_LIGHT1_1, PO_C121_LIGHT1_2, PO_C121_LIGHT1_3,
	PO_C121_LIGHT2, PO_C121_LIGHT2_1, PO_C121_LIGHT2_2, PO_C121_LIGHT2_3, PO_C121_LIGHT3, PO_C121_LIGHT3_1, PO_C121_LIGHT3_2, PO_C121_LIGHT3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	36,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C121_DIS0, PO_C121_DIS0, PO_C121_DIS0_1, PO_C121_DIS0_2, PO_C121_DIS0_2, PO_C121_DIS0_3, PO_C121_DIS1, PO_C121_DIS1,
	PO_C121_DIS1_1, PO_C121_DIS1_2, PO_C121_DIS1_2, PO_C121_DIS1_3, PO_C121_DIS2, PO_C121_DIS2, PO_C121_DIS2_1, PO_C121_DIS2_2,
	PO_C121_DIS2_2, PO_C121_DIS2_3, PO_C121_DIS3, PO_C121_DIS3, PO_C121_DIS3_1, PO_C121_DIS3_2, PO_C121_DIS3_2, PO_C121_DIS3_3,
	PO_C121_DIS4, PO_C121_DIS4, PO_C121_DIS4_1, PO_C121_DIS4_2, PO_C121_DIS4_2, PO_C121_DIS4_3, PO_C121_DIS5, PO_C121_DIS5,
	PO_C121_DIS5_1, PO_C121_DIS5_2, PO_C121_DIS5_2, PO_C121_DIS5_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short c122mv[] = {
	//상태 데이터
	//SOUL_4_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_4_0, PO_C122_4_0_1, PO_C122_4_0_2, PO_C122_4_0_3, PO_C122_4_1, PO_C122_4_1_1, PO_C122_4_1_2, PO_C122_4_1_3,
	PO_C122_4_2, PO_C122_4_2_1, PO_C122_4_2_2, PO_C122_4_2_3, PO_C122_4_3, PO_C122_4_3_1, PO_C122_4_3_2, PO_C122_4_3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	-1 * _2X, -1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, -1 * _2X, -1 * _2X,
	-1 * _2X, -1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, -1 * _2X, -1 * _2X,	//상태 프레임별 이동폭 Y

	//SOUL_4_NEUTRAL_RISE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_4_0, PO_C122_4_0_1, PO_C122_4_0_2, PO_C122_4_0_3, PO_C122_4_1, PO_C122_4_1_1, PO_C122_4_1_2, PO_C122_4_1_3,
	PO_C122_4_2, PO_C122_4_2_1, PO_C122_4_2_2, PO_C122_4_2_3, PO_C122_4_3, PO_C122_4_3_1, PO_C122_4_3_2, PO_C122_4_3_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	-2 * _2X, -2 * _2X, -2 * _2X, -2 * _2X, -2 * _2X, -2 * _2X, -2 * _2X, -2 * _2X,
	-2 * _2X, -2 * _2X, -2 * _2X, -2 * _2X, -2 * _2X, -2 * _2X, -2 * _2X, -2 * _2X,	//상태 프레임별 이동폭 Y

	//SOUL_DARK
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0,
	PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SOUL_DARK_AWAY
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0,
	PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0,	//상태 프레임별 모션
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,	//상태 프레임별 이동폭 X
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,	//상태 프레임별 이동폭 Y

	//SOUL_5_NEUTRAL
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_5_0, PO_C122_5_0_1, PO_C122_5_0_2, PO_C122_5_0_3, PO_C122_5_1, PO_C122_5_1_1, PO_C122_5_1_2, PO_C122_5_1_3,
	PO_C122_5_2, PO_C122_5_2_1, PO_C122_5_2_2, PO_C122_5_2_3, PO_C122_5_3, PO_C122_5_3_1, PO_C122_5_3_2, PO_C122_5_3_3,
	PO_C122_5_4, PO_C122_5_4_1, PO_C122_5_4_2, PO_C122_5_4_3, PO_C122_5_5, PO_C122_5_5_1, PO_C122_5_5_2, PO_C122_5_5_3,
	PO_C122_5_6, PO_C122_5_6_1, PO_C122_5_6_2, PO_C122_5_6_3, PO_C122_5_7, PO_C122_5_7_1, PO_C122_5_7_2, PO_C122_5_7_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X,
	-1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X,
	-1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,	//상태 프레임별 이동폭 Y

	//SOUL_6_NEUTRAL
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_6_0, PO_C122_6_0_1, PO_C122_6_0_2, PO_C122_6_0_3, PO_C122_6_1, PO_C122_6_1_1, PO_C122_6_1_2, PO_C122_6_1_3,
	PO_C122_6_2, PO_C122_6_2_1, PO_C122_6_2_2, PO_C122_6_2_3, PO_C122_6_3, PO_C122_6_3_1, PO_C122_6_3_2, PO_C122_6_3_3,
	PO_C122_6_4, PO_C122_6_4_1, PO_C122_6_4_2, PO_C122_6_4_3, PO_C122_6_5, PO_C122_6_5_1, PO_C122_6_5_2, PO_C122_6_5_3,
	PO_C122_6_6, PO_C122_6_6_1, PO_C122_6_6_2, PO_C122_6_6_3, PO_C122_6_7, PO_C122_6_7_1, PO_C122_6_7_2, PO_C122_6_7_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X,
	-1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X,
	-1 * _2X, -1 * _2X, -1 * _2X, -1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,	//상태 프레임별 이동폭 Y

	//SOUL_SPARK
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_SPARK0, PO_C122_SPARK0_SPARK1_1, PO_C122_SPARK0_SPARK1_2, PO_C122_SPARK0_SPARK1_3, PO_C122_SPARK1, PO_C122_SPARK1_1, PO_C122_SPARK1_2, PO_C122_SPARK1_3,
	PO_C122_SPARK2, PO_C122_SPARK2_1, PO_C122_SPARK2_2, PO_C122_SPARK2_3, PO_C122_SPARK3, PO_C122_SPARK3_1, PO_C122_SPARK3_2, PO_C122_SPARK3_3,
	PO_C122_SPARK4, PO_C122_SPARK4_1, PO_C122_SPARK4_2, PO_C122_SPARK4_3, PO_C122_SPARK5, PO_C122_SPARK5_1, PO_C122_SPARK5_2, PO_C122_SPARK5_3,
	PO_C122_SPARK6, PO_C122_SPARK6_1, PO_C122_SPARK6_2, PO_C122_SPARK6_3, PO_C122_SPARK7, PO_C122_SPARK7_1, PO_C122_SPARK7_2, PO_C122_SPARK7_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SOUL_NEUTRAL
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_HEART, PO_C122_HEART, PO_C122_HEART, PO_C122_HEART, PO_C122_HEART, PO_C122_HEART, PO_C122_HEART, PO_C122_HEART,
	PO_C122_HEART, PO_C122_HEART, PO_C122_HEART, PO_C122_HEART, PO_C122_HEART, PO_C122_HEART, PO_C122_HEART, PO_C122_HEART,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SOUL_BURST
	60,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_BURST0, PO_C122_BURST0, PO_C122_BURST0, PO_C122_BURST0, PO_C122_BURST0, PO_C122_BURST0_1, PO_C122_BURST0_1, PO_C122_BURST0_1,
	PO_C122_BURST0_1, PO_C122_BURST0_1, PO_C122_BURST0_2, PO_C122_BURST0_2, PO_C122_BURST0_2, PO_C122_BURST0_2, PO_C122_BURST0_2, PO_C122_BURST0_3,
	PO_C122_BURST0_3, PO_C122_BURST0_3, PO_C122_BURST0_3, PO_C122_BURST0_3, PO_C122_BURST1, PO_C122_BURST1_1, PO_C122_BURST1_2, PO_C122_BURST1_3,
	PO_C122_BURST2, PO_C122_BURST2_1, PO_C122_BURST2_2, PO_C122_BURST2_3, PO_C122_BURST3, PO_C122_BURST3_1, PO_C122_BURST3_2, PO_C122_BURST3_3,
	PO_C122_BURST4, PO_C122_BURST4_BURST3_1, PO_C122_BURST4_BURST3_2, PO_C122_BURST4_BURST3_3, PO_C122_BURST3, PO_C122_BURST3_1, PO_C122_BURST3_2, PO_C122_BURST3_3,
	PO_C122_BURST4, PO_C122_BURST4_BURST3_1, PO_C122_BURST4_BURST3_2, PO_C122_BURST4_BURST3_3, PO_C122_BURST3, PO_C122_BURST3_1, PO_C122_BURST3_2, PO_C122_BURST3_3,
	PO_C122_BURST4, PO_C122_BURST4_BURST3_1, PO_C122_BURST4_BURST3_2, PO_C122_BURST4_BURST3_3, PO_C122_BURST3, PO_C122_BURST3_1, PO_C122_BURST3_2, PO_C122_BURST3_3,
	PO_C122_BURST4, PO_C122_BURST4_BURST0_1, PO_C122_BURST4_BURST0_2, PO_C122_BURST4_BURST0_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SOUL_PART0
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0,
	PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0, PO_C122_PART0,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SOUL_6_ROTATION
	120,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_6_C0, PO_C122_6_C0, PO_C122_6_C0, PO_C122_6_C0_1, PO_C122_6_C0_1, PO_C122_6_C0_1, PO_C122_6_C0_2, PO_C122_6_C0_2,
	PO_C122_6_C0_2, PO_C122_6_C0_3, PO_C122_6_C0_3, PO_C122_6_C0_3, PO_C122_6_C1, PO_C122_6_C1, PO_C122_6_C1, PO_C122_6_C1_1,
	PO_C122_6_C1_1, PO_C122_6_C1_1, PO_C122_6_C1_2, PO_C122_6_C1_2, PO_C122_6_C1_2, PO_C122_6_C1_3, PO_C122_6_C1_3, PO_C122_6_C1_3,
	PO_C122_6_C2, PO_C122_6_C2, PO_C122_6_C2, PO_C122_6_C2_1, PO_C122_6_C2_1, PO_C122_6_C2_1, PO_C122_6_C2_2, PO_C122_6_C2_2,
	PO_C122_6_C2_2, PO_C122_6_C2_3, PO_C122_6_C2_3, PO_C122_6_C2_3, PO_C122_6_C3, PO_C122_6_C3, PO_C122_6_C3, PO_C122_6_C3_1,
	PO_C122_6_C3_1, PO_C122_6_C3_1, PO_C122_6_C3_2, PO_C122_6_C3_2, PO_C122_6_C3_2, PO_C122_6_C3_3, PO_C122_6_C3_3, PO_C122_6_C3_3,
	PO_C122_6_C4, PO_C122_6_C4, PO_C122_6_C4, PO_C122_6_C4_1, PO_C122_6_C4_1, PO_C122_6_C4_1, PO_C122_6_C4_2, PO_C122_6_C4_2,
	PO_C122_6_C4_2, PO_C122_6_C4_3, PO_C122_6_C4_3, PO_C122_6_C4_3, PO_C122_6_C5, PO_C122_6_C5, PO_C122_6_C5, PO_C122_6_C5_1,
	PO_C122_6_C5_1, PO_C122_6_C5_1, PO_C122_6_C5_2, PO_C122_6_C5_2, PO_C122_6_C5_2, PO_C122_6_C5_3, PO_C122_6_C5_3, PO_C122_6_C5_3,
	PO_C122_6_C6, PO_C122_6_C6, PO_C122_6_C6, PO_C122_6_C6_1, PO_C122_6_C6_1, PO_C122_6_C6_1, PO_C122_6_C6_2, PO_C122_6_C6_2,
	PO_C122_6_C6_2, PO_C122_6_C6_3, PO_C122_6_C6_3, PO_C122_6_C6_3, PO_C122_6_C7, PO_C122_6_C7, PO_C122_6_C7, PO_C122_6_C7_1,
	PO_C122_6_C7_1, PO_C122_6_C7_1, PO_C122_6_C7_2, PO_C122_6_C7_2, PO_C122_6_C7_2, PO_C122_6_C7_3, PO_C122_6_C7_3, PO_C122_6_C7_3,
	PO_C122_6_C8, PO_C122_6_C8, PO_C122_6_C8, PO_C122_6_C8_1, PO_C122_6_C8_1, PO_C122_6_C8_1, PO_C122_6_C8_2, PO_C122_6_C8_2,
	PO_C122_6_C8_2, PO_C122_6_C8_3, PO_C122_6_C8_3, PO_C122_6_C8_3, PO_C122_6_C9, PO_C122_6_C9, PO_C122_6_C9, PO_C122_6_C9_1,
	PO_C122_6_C9_1, PO_C122_6_C9_1, PO_C122_6_C9_2, PO_C122_6_C9_2, PO_C122_6_C9_2, PO_C122_6_C9_3, PO_C122_6_C9_3, PO_C122_6_C9_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SOUL_6_TOGETHER
	32,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_6_SUM0, PO_C122_6_SUM0_1, PO_C122_6_SUM0_2, PO_C122_6_SUM0_3, PO_C122_6_SUM1, PO_C122_6_SUM1_1, PO_C122_6_SUM1_2, PO_C122_6_SUM1_3,
	PO_C122_6_SUM2, PO_C122_6_SUM2_1, PO_C122_6_SUM2_2, PO_C122_6_SUM2_3, PO_C122_6_SUM3, PO_C122_6_SUM3_1, PO_C122_6_SUM3_2, PO_C122_6_SUM3_3,
	PO_C122_6_SUM4, PO_C122_6_SUM4_1, PO_C122_6_SUM4_2, PO_C122_6_SUM4_3, PO_C122_SPARK0, PO_C122_SPARK0_HEART_1, PO_C122_SPARK0_HEART_2, PO_C122_SPARK0_HEART_3,
	PO_C122_HEART, PO_C122_HEART, PO_C122_HEART_1, PO_C122_HEART_1, PO_C122_HEART_2, PO_C122_HEART_2, PO_C122_HEART_3, PO_C122_HEART_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SOUL_5_ROTATION
	120,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_5_C0, PO_C122_5_C0, PO_C122_5_C0, PO_C122_5_C0_1, PO_C122_5_C0_1, PO_C122_5_C0_1, PO_C122_5_C0_2, PO_C122_5_C0_2,
	PO_C122_5_C0_2, PO_C122_5_C0_3, PO_C122_5_C0_3, PO_C122_5_C0_3, PO_C122_5_C1, PO_C122_5_C1, PO_C122_5_C1, PO_C122_5_C1_1,
	PO_C122_5_C1_1, PO_C122_5_C1_1, PO_C122_5_C1_2, PO_C122_5_C1_2, PO_C122_5_C1_2, PO_C122_5_C1_3, PO_C122_5_C1_3, PO_C122_5_C1_3,
	PO_C122_5_C2, PO_C122_5_C2, PO_C122_5_C2, PO_C122_5_C2_1, PO_C122_5_C2_1, PO_C122_5_C2_1, PO_C122_5_C2_2, PO_C122_5_C2_2,
	PO_C122_5_C2_2, PO_C122_5_C2_3, PO_C122_5_C2_3, PO_C122_5_C2_3, PO_C122_5_C3, PO_C122_5_C3, PO_C122_5_C3, PO_C122_5_C3_1,
	PO_C122_5_C3_1, PO_C122_5_C3_1, PO_C122_5_C3_2, PO_C122_5_C3_2, PO_C122_5_C3_2, PO_C122_5_C3_3, PO_C122_5_C3_3, PO_C122_5_C3_3,
	PO_C122_5_C4, PO_C122_5_C4, PO_C122_5_C4, PO_C122_5_C4_1, PO_C122_5_C4_1, PO_C122_5_C4_1, PO_C122_5_C4_2, PO_C122_5_C4_2,
	PO_C122_5_C4_2, PO_C122_5_C4_3, PO_C122_5_C4_3, PO_C122_5_C4_3, PO_C122_5_C5, PO_C122_5_C5, PO_C122_5_C5, PO_C122_5_C5_1,
	PO_C122_5_C5_1, PO_C122_5_C5_1, PO_C122_5_C5_2, PO_C122_5_C5_2, PO_C122_5_C5_2, PO_C122_5_C5_3, PO_C122_5_C5_3, PO_C122_5_C5_3,
	PO_C122_5_C6, PO_C122_5_C6, PO_C122_5_C6, PO_C122_5_C6_1, PO_C122_5_C6_1, PO_C122_5_C6_1, PO_C122_5_C6_2, PO_C122_5_C6_2,
	PO_C122_5_C6_2, PO_C122_5_C6_3, PO_C122_5_C6_3, PO_C122_5_C6_3, PO_C122_5_C7, PO_C122_5_C7, PO_C122_5_C7, PO_C122_5_C7_1,
	PO_C122_5_C7_1, PO_C122_5_C7_1, PO_C122_5_C7_2, PO_C122_5_C7_2, PO_C122_5_C7_2, PO_C122_5_C7_3, PO_C122_5_C7_3, PO_C122_5_C7_3,
	PO_C122_5_C8, PO_C122_5_C8, PO_C122_5_C8, PO_C122_5_C8_1, PO_C122_5_C8_1, PO_C122_5_C8_1, PO_C122_5_C8_2, PO_C122_5_C8_2,
	PO_C122_5_C8_2, PO_C122_5_C8_3, PO_C122_5_C8_3, PO_C122_5_C8_3, PO_C122_5_C9, PO_C122_5_C9, PO_C122_5_C9, PO_C122_5_C9_1,
	PO_C122_5_C9_1, PO_C122_5_C9_1, PO_C122_5_C9_2, PO_C122_5_C9_2, PO_C122_5_C9_2, PO_C122_5_C9_3, PO_C122_5_C9_3, PO_C122_5_C9_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SOUL_FLAME
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_PART1, PO_C122_PART1, PO_C122_PART1, PO_C122_PART1, PO_C122_PART1, PO_C122_PART1, PO_C122_PART1, PO_C122_PART1,
	PO_C122_PART1, PO_C122_PART1, PO_C122_PART1, PO_C122_PART1, PO_C122_PART1, PO_C122_PART1, PO_C122_PART1, PO_C122_PART1,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SOUL_ICE
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_PART2, PO_C122_PART2, PO_C122_PART2, PO_C122_PART2, PO_C122_PART2, PO_C122_PART2, PO_C122_PART2, PO_C122_PART2,
	PO_C122_PART2, PO_C122_PART2, PO_C122_PART2, PO_C122_PART2, PO_C122_PART2, PO_C122_PART2, PO_C122_PART2, PO_C122_PART2,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SOUL_THUNDER
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_PART3, PO_C122_PART3, PO_C122_PART3, PO_C122_PART3, PO_C122_PART3, PO_C122_PART3, PO_C122_PART3, PO_C122_PART3,
	PO_C122_PART3, PO_C122_PART3, PO_C122_PART3, PO_C122_PART3, PO_C122_PART3, PO_C122_PART3, PO_C122_PART3, PO_C122_PART3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SOUL_LIGHT
	16,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_PART4, PO_C122_PART4, PO_C122_PART4, PO_C122_PART4, PO_C122_PART4, PO_C122_PART4, PO_C122_PART4, PO_C122_PART4,
	PO_C122_PART4, PO_C122_PART4, PO_C122_PART4, PO_C122_PART4, PO_C122_PART4, PO_C122_PART4, PO_C122_PART4, PO_C122_PART4,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SOUL_NEUTRAL2
	20,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_1_0, PO_C122_1_0_1, PO_C122_1_0_2, PO_C122_1_0_3, PO_C122_1_1, PO_C122_1_1_1, PO_C122_1_1_2, PO_C122_1_1_3,
	PO_C122_1_2, PO_C122_1_2_1, PO_C122_1_2_2, PO_C122_1_2_3, PO_C122_1_3, PO_C122_1_3_1, PO_C122_1_3_2, PO_C122_1_3_3,
	PO_C122_1_4, PO_C122_1_4_1, PO_C122_1_4_2, PO_C122_1_4_3,	//상태 프레임별 모션
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 X
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,	//상태 프레임별 이동폭 Y

	//SOUL_NEUTRAL3
	20,	//상태 프레임 카운트
	SET_MAINFRAME_RANDOM8,	//초기화 조건
	PO_C122_1_0, PO_C122_1_0_1, PO_C122_1_0_2, PO_C122_1_0_3, PO_C122_1_1, PO_C122_1_1_1, PO_C122_1_1_2, PO_C122_1_1_3,
	PO_C122_1_2, PO_C122_1_2_1, PO_C122_1_2_2, PO_C122_1_2_3, PO_C122_1_3, PO_C122_1_3_1, PO_C122_1_3_2, PO_C122_1_3_3,
	PO_C122_1_4, PO_C122_1_4_1, PO_C122_1_4_2, PO_C122_1_4_3,	//상태 프레임별 모션
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,
	1 * _2X, 1 * _2X, 1 * _2X, 1 * _2X,	//상태 프레임별 이동폭 X
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1,	//상태 프레임별 이동폭 Y

	-1,
	-1,
};

const signed short cmfImgOff[TOTALCMF * 5] = {
	//C0
	255,
	255, 0,
	255, 0,

	//C1
	255,
	255, 0,
	255, 0,

	//C2
	255,
	255, 0,
	255, 0,
	//C3
	IMG_C3_8,
	255, 0,
	255, 0,
	//C4
	IMG_C4_8,
	255, 0,
	255, 0,
	//C5
	IMG_C5_8,
	255, 0,
	255, 0,
	//C6
	IMG_C6_8,
	255, 0,
	255, 0,
	//C7
	IMG_C7_8,
	255, 0,
	255, 0,

	//C8
	IMG_C8_8,
	255, 0,
	255, 0,

	//C9
	IMG_C9_8,
	255, 0,
	255, 0,

	//C10
	IMG_C10_8,
	255, 0,
	255, 0,

	//C11
	IMG_C11_8,
	255, 0,
	255, 0,

	//C12
	IMG_C12_9,
	255, 0,
	255, 0,

	//C13
	IMG_C13_8,
	IMG_C13_25, WEAPON_EFFECT_IMG,
	255, 0,
	//C14
	IMG_C14_9,
	IMG_C14_25, WEAPON_EFFECT_IMG,
	255, 0,
	//C15
	IMG_C15_8,
	255, 0,
	255, 0,

	//C16
	IMG_C16_8,
	255, 0,
	255, 0,

	//C17
	IMG_C17_8,
	255, 0,
	255, 0,

	//C18
	IMG_C18_8,
	IMG_C18_21, WEAPON_EFFECT_IMG,
	255, 0,
	//C19
	IMG_C19_8,
	IMG_C19_20, COMMON_IMG,
	255, 0,
	//C20
	IMG_C20_8,
	IMG_C20_17, COMMON_IMG,
	255, 0,
	//C21
	IMG_C21_9,
	IMG_C21_27, WEAPON_EFFECT_IMG,
	IMG_C21_29, ATTR_IMG,
	//C22
	IMG_C22_8,
	255, 0,
	255, 0,

	//C23
	IMG_C23_9,
	IMG_C23_24, ATTR_IMG,
	255, 0,
	//C24
	IMG_C24_8,
	IMG_C24_29, ATTR_IMG,
	255, 0,
	//C25
	IMG_C25_9,
	255, 0,
	255, 0,

	//C26
	IMG_C26_8,
	IMG_C26_19, WEAPON_EFFECT_IMG,
	255, 0,
	//C27
	IMG_C27_8,
	255, 0,
	255, 0,

	//C28
	IMG_C28_8,
	IMG_C28_35, WEAPON_EFFECT_IMG,
	255, 0,
	//C29
	IMG_C29_8,
	255, 0,
	255, 0,

	//C30
	IMG_C30_14,
	255, 0,
	255, 0,

	//C31
	IMG_C31_12,
	255, 0,
	255, 0,

	//C32
	IMG_C32_8,
	255, 0,
	255, 0,

	//C33
	IMG_C33_9,
	255, 0,
	255, 0,

	//C34
	IMG_C34_8,
	IMG_C34_34, WEAPON_EFFECT_IMG,
	IMG_C34_35, ATTR_IMG,
	//C35
	IMG_C35_9,
	255, 0,
	255, 0,

	//C36
	IMG_C36_9,
	255, 0,
	255, 0,

	//C37
	IMG_C37_9,
	IMG_C37_37, ATTR_IMG,
	255, 0,
	//C38
	IMG_C38_8,
	255, 0,
	255, 0,

	//C39
	IMG_C39_8,
	255, 0,
	255, 0,

	//C40
	IMG_C40_8,
	IMG_C40_28, ATTR_IMG,
	255, 0,
	//C41
	IMG_C41_8,
	255, 0,
	255, 0,

	//C42
	IMG_C42_8,
	255, 0,
	255, 0,

	//C43
	IMG_C43_10,
	255, 0,
	255, 0,

	//C44
	IMG_C44_9,
	255, 0,
	255, 0,

	//C45
	IMG_C45_8,
	255, 0,
	255, 0,

	//C46
	IMG_C46_8,
	255, 0,
	255, 0,

	//C47
	IMG_C47_8,
	255, 0,
	255, 0,

	//C48
	IMG_C48_8,
	255, 0,
	255, 0,

	//C49
	IMG_C49_9,
	255, 0,
	255, 0,

	//C50
	IMG_C50_9,
	255, 0,
	255, 0,

	//C51
	IMG_C51_8,
	255, 0,
	255, 0,

	//C52
	IMG_C52_8,
	255, 0,
	255, 0,

	//C53
	IMG_C53_8,
	255, 0,
	255, 0,

	//C54
	IMG_C54_8,
	255, 0,
	255, 0,

	//C55
	IMG_C55_8,
	255, 0,
	255, 0,

	//C56
	IMG_C56_8,
	255, 0,
	255, 0,

	//C57
	IMG_C57_8,
	255, 0,
	255, 0,

	//C58
	IMG_C58_8,
	255, 0,
	255, 0,

	//C59
	IMG_C59_8,
	255, 0,
	255, 0,

	//C60
	IMG_C60_8,
	255, 0,
	255, 0,

	//C61
	IMG_C61_8,
	255, 0,
	255, 0,

	//C62
	IMG_C62_8,
	255, 0,
	255, 0,

	//C63
	IMG_C63_8,
	255, 0,
	255, 0,

	//C64
	IMG_C64_8,
	255, 0,
	255, 0,

	//C65
	IMG_C65_8,
	255, 0,
	255, 0,

	//C66
	IMG_C66_8,
	255, 0,
	255, 0,

	//C67
	IMG_C67_8,
	255, 0,
	255, 0,

	//C68
	IMG_C68_8,
	255, 0,
	255, 0,

	//C69
	IMG_C69_8,
	255, 0,
	255, 0,

	//C70
	IMG_C70_8,
	255, 0,
	255, 0,

	//C71
	IMG_C71_8,
	255, 0,
	255, 0,

	//C72
	IMG_C72_8,
	255, 0,
	255, 0,

	//C73
	IMG_C73_8,
	255, 0,
	255, 0,

	//C74
	IMG_C74_8,
	255, 0,
	255, 0,

	//C75
	IMG_C75_8,
	255, 0,
	255, 0,

	//C76
	IMG_C76_8,
	255, 0,
	255, 0,

	//C77
	IMG_C77_8,
	255, 0,
	255, 0,

	//C78
	IMG_C78_8,
	255, 0,
	255, 0,

	//C79
	IMG_C79_8,
	255, 0,
	255, 0,

	//C80
	IMG_C80_8,
	255, 0,
	255, 0,

	//C81
	IMG_C81_8,
	255, 0,
	255, 0,

	//C82
	IMG_C82_8,
	255, 0,
	255, 0,

	//C83
	IMG_C83_8,
	255, 0,
	255, 0,

	//C84
	IMG_C84_8,
	IMG_C84_42, WEAPON_EFFECT_IMG,
	255, 0,
	//C85
	IMG_C85_8,
	255, 0,
	255, 0,

	//C86
	IMG_C86_8,
	255, 0,
	255, 0,

	//C87
	IMG_C87_8,
	255, 0,
	255, 0,

	//C88
	IMG_C88_8,
	255, 0,
	255, 0,

	//C89
	IMG_C89_8,
	255, 0,
	255, 0,

	//C90
	IMG_C90_8,
	255, 0,
	255, 0,

	//C91
	IMG_C91_8,
	255, 0,
	255, 0,

	//C92
	IMG_C92_8,
	255, 0,
	255, 0,

	//C93
	IMG_C93_8,
	255, 0,
	255, 0,

	//C94
	IMG_C94_8,
	255, 0,
	255, 0,

	//C95
	IMG_C95_15,
	255, 0,
	255, 0,

	//C96
	IMG_C96_8,
	255, 0,
	255, 0,

	//C97
	IMG_C97_11,
	255, 0,
	255, 0,

	//C98
	IMG_C98_8,
	255, 0,
	255, 0,

	//C99
	IMG_C99_8,
	255, 0,
	255, 0,

	//C100
	IMG_C100_8,
	255, 0,
	255, 0,

	//C101
	IMG_C101_8,
	255, 0,
	255, 0,

	//C102
	IMG_C102_8,
	255, 0,
	255, 0,

	//C103
	IMG_C103_8,
	255, 0,
	255, 0,

	//C104
	IMG_C104_8,
	255, 0,
	255, 0,

	//C105
	IMG_C105_8,
	255, 0,
	255, 0,

	//C106
	IMG_C106_8,
	255, 0,
	255, 0,

	//C107
	IMG_C107_11,
	255, 0,
	255, 0,

	//C108
	IMG_C108_8,
	255, 0,
	255, 0,

	//C109
	IMG_C109_8,
	255, 0,
	255, 0,

	//C110
	IMG_C110_12,
	255, 0,
	255, 0,

	//C111
	IMG_C111_19,
	255, 0,
	255, 0,

	//C112
	IMG_C112_12,
	IMG_C112_45, HIT_IMG,
	255, 0,
	//C113
	IMG_C113_8,
	255, 0,
	255, 0,

	//C114
	IMG_C114_9,
	255, 0,
	255, 0,

	//C115
	IMG_C115_11,
	255, 0,
	255, 0,

	//C116
	IMG_C116_8,
	255, 0,
	255, 0,

	//C117
	IMG_C117_8,
	255, 0,
	255, 0,

	//C118
	IMG_C118_8,
	255, 0,
	255, 0,

	//C119
	IMG_C119_12,
	255, 0,
	255, 0,

	//C120
	IMG_C120_12,
	255, 0,
	255, 0,

	//C121
	IMG_C121_17,
	255, 0,
	255, 0,

	//C122
	IMG_C122_11,
	255, 0,
	255, 0,

	//C3
	IMG_C3_8,
	255, 0,
	255, 0,
	IMG_C3_8,
	255, 0,
	255, 0,
	IMG_C3_8,
	255, 0,
	255, 0,
	IMG_C3_8,
	255, 0,
	255, 0,
	IMG_C3_8,
	255, 0,
	255, 0,
	IMG_C3_8,
	255, 0,
	255, 0,
	//C4
	IMG_C4_8,
	255, 0,
	255, 0,
	IMG_C4_8,
	255, 0,
	255, 0,
	IMG_C4_8,
	255, 0,
	255, 0,
	IMG_C4_8,
	255, 0,
	255, 0,
	IMG_C4_8,
	255, 0,
	255, 0,
	IMG_C4_8,
	255, 0,
	255, 0,
	//C5
	IMG_C5_8,
	255, 0,
	255, 0,
	IMG_C5_8,
	255, 0,
	255, 0,
	IMG_C5_8,
	255, 0,
	255, 0,
	IMG_C5_8,
	255, 0,
	255, 0,
	IMG_C5_8,
	255, 0,
	255, 0,
	IMG_C5_8,
	255, 0,
	255, 0,
	//C6
	IMG_C6_8,
	255, 0,
	255, 0,
	IMG_C6_8,
	255, 0,
	255, 0,
	IMG_C6_8,
	255, 0,
	255, 0,
	IMG_C6_8,
	255, 0,
	255, 0,
	IMG_C6_8,
	255, 0,
	255, 0,
	IMG_C6_8,
	255, 0,
	255, 0,
	//C7
	IMG_C7_8,
	255, 0,
	255, 0,
	IMG_C7_8,
	255, 0,
	255, 0,
	IMG_C7_8,
	255, 0,
	255, 0,
	IMG_C7_8,
	255, 0,
	255, 0,
	IMG_C7_8,
	255, 0,
	255, 0,
	IMG_C7_8,
	255, 0,
	255, 0,
	//C8
	IMG_C8_8,
	255, 0,
	255, 0,
	IMG_C8_8,
	255, 0,
	255, 0,
	IMG_C8_8,
	255, 0,
	255, 0,
	IMG_C8_8,
	255, 0,
	255, 0,
	IMG_C8_8,
	255, 0,
	255, 0,
	IMG_C8_8,
	255, 0,
	255, 0,
	//C9
	IMG_C9_8,
	255, 0,
	255, 0,
	IMG_C9_8,
	255, 0,
	255, 0,
	IMG_C9_8,
	255, 0,
	255, 0,
	IMG_C9_8,
	255, 0,
	255, 0,
	IMG_C9_8,
	255, 0,
	255, 0,
	IMG_C9_8,
	255, 0,
	255, 0,
	//C10
	IMG_C10_8,
	255, 0,
	255, 0,
	IMG_C10_8,
	255, 0,
	255, 0,
	IMG_C10_8,
	255, 0,
	255, 0,
	IMG_C10_8,
	255, 0,
	255, 0,
	IMG_C10_8,
	255, 0,
	255, 0,
	IMG_C10_8,
	255, 0,
	255, 0,
	//C11
	IMG_C11_8,
	255, 0,
	255, 0,
	IMG_C11_8,
	255, 0,
	255, 0,
	IMG_C11_8,
	255, 0,
	255, 0,
	IMG_C11_8,
	255, 0,
	255, 0,
	IMG_C11_8,
	255, 0,
	255, 0,
	IMG_C11_8,
	255, 0,
	255, 0,
	//C12
	IMG_C12_9,
	255, 0,
	255, 0,
	IMG_C12_9,
	255, 0,
	255, 0,
	IMG_C12_9,
	255, 0,
	255, 0,
	IMG_C12_9,
	255, 0,
	255, 0,
	IMG_C12_9,
	255, 0,
	255, 0,
	IMG_C12_9,
	255, 0,
	255, 0,
	//C13
	IMG_C13_8,
	IMG_C13_25, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C13_8,
	IMG_C13_25, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C13_8,
	IMG_C13_25, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C13_8,
	IMG_C13_25, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C13_8,
	IMG_C13_25, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C13_8,
	IMG_C13_25, WEAPON_EFFECT_IMG,
	255, 0,
	//C14
	IMG_C14_9,
	IMG_C14_25, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C14_9,
	IMG_C14_25, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C14_9,
	IMG_C14_25, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C14_9,
	IMG_C14_25, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C14_9,
	IMG_C14_25, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C14_9,
	IMG_C14_25, WEAPON_EFFECT_IMG,
	255, 0,
	//C15
	IMG_C15_8,
	255, 0,
	255, 0,
	IMG_C15_8,
	255, 0,
	255, 0,
	IMG_C15_8,
	255, 0,
	255, 0,
	IMG_C15_8,
	255, 0,
	255, 0,
	IMG_C15_8,
	255, 0,
	255, 0,
	IMG_C15_8,
	255, 0,
	255, 0,
	//C16
	IMG_C16_8,
	255, 0,
	255, 0,
	IMG_C16_8,
	255, 0,
	255, 0,
	IMG_C16_8,
	255, 0,
	255, 0,
	IMG_C16_8,
	255, 0,
	255, 0,
	IMG_C16_8,
	255, 0,
	255, 0,
	IMG_C16_8,
	255, 0,
	255, 0,
	//C17
	IMG_C17_8,
	255, 0,
	255, 0,
	IMG_C17_8,
	255, 0,
	255, 0,
	IMG_C17_8,
	255, 0,
	255, 0,
	IMG_C17_8,
	255, 0,
	255, 0,
	IMG_C17_8,
	255, 0,
	255, 0,
	IMG_C17_8,
	255, 0,
	255, 0,
	//C18
	IMG_C18_8,
	IMG_C18_21, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C18_8,
	IMG_C18_21, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C18_8,
	IMG_C18_21, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C18_8,
	IMG_C18_21, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C18_8,
	IMG_C18_21, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C18_8,
	IMG_C18_21, WEAPON_EFFECT_IMG,
	255, 0,
	//C19
	IMG_C19_8,
	IMG_C19_20, COMMON_IMG,
	255, 0,
	IMG_C19_8,
	IMG_C19_20, COMMON_IMG,
	255, 0,
	IMG_C19_8,
	IMG_C19_20, COMMON_IMG,
	255, 0,
	IMG_C19_8,
	IMG_C19_20, COMMON_IMG,
	255, 0,
	IMG_C19_8,
	IMG_C19_20, COMMON_IMG,
	255, 0,
	IMG_C19_8,
	IMG_C19_20, COMMON_IMG,
	255, 0,
	//C20
	IMG_C20_8,
	IMG_C20_17, COMMON_IMG,
	255, 0,
	IMG_C20_8,
	IMG_C20_17, COMMON_IMG,
	255, 0,
	IMG_C20_8,
	IMG_C20_17, COMMON_IMG,
	255, 0,
	IMG_C20_8,
	IMG_C20_17, COMMON_IMG,
	255, 0,
	IMG_C20_8,
	IMG_C20_17, COMMON_IMG,
	255, 0,
	IMG_C20_8,
	IMG_C20_17, COMMON_IMG,
	255, 0,
	//C21
	IMG_C21_9,
	IMG_C21_27, WEAPON_EFFECT_IMG,
	IMG_C21_29, ATTR_IMG,
	IMG_C21_9,
	IMG_C21_27, WEAPON_EFFECT_IMG,
	IMG_C21_29, ATTR_IMG,
	IMG_C21_9,
	IMG_C21_27, WEAPON_EFFECT_IMG,
	IMG_C21_29, ATTR_IMG,
	IMG_C21_9,
	IMG_C21_27, WEAPON_EFFECT_IMG,
	IMG_C21_29, ATTR_IMG,
	IMG_C21_9,
	IMG_C21_27, WEAPON_EFFECT_IMG,
	IMG_C21_29, ATTR_IMG,
	IMG_C21_9,
	IMG_C21_27, WEAPON_EFFECT_IMG,
	IMG_C21_29, ATTR_IMG,
	//C22
	IMG_C22_8,
	255, 0,
	255, 0,
	IMG_C22_8,
	255, 0,
	255, 0,
	IMG_C22_8,
	255, 0,
	255, 0,
	IMG_C22_8,
	255, 0,
	255, 0,
	IMG_C22_8,
	255, 0,
	255, 0,
	IMG_C22_8,
	255, 0,
	255, 0,
	//C23
	IMG_C23_9,
	IMG_C23_24, ATTR_IMG,
	255, 0,
	IMG_C23_9,
	IMG_C23_24, ATTR_IMG,
	255, 0,
	IMG_C23_9,
	IMG_C23_24, ATTR_IMG,
	255, 0,
	IMG_C23_9,
	IMG_C23_24, ATTR_IMG,
	255, 0,
	IMG_C23_9,
	IMG_C23_24, ATTR_IMG,
	255, 0,
	IMG_C23_9,
	IMG_C23_24, ATTR_IMG,
	255, 0,
	//C24
	IMG_C24_8,
	IMG_C24_29, ATTR_IMG,
	255, 0,
	IMG_C24_8,
	IMG_C24_29, ATTR_IMG,
	255, 0,
	IMG_C24_8,
	IMG_C24_29, ATTR_IMG,
	255, 0,
	IMG_C24_8,
	IMG_C24_29, ATTR_IMG,
	255, 0,
	IMG_C24_8,
	IMG_C24_29, ATTR_IMG,
	255, 0,
	IMG_C24_8,
	IMG_C24_29, ATTR_IMG,
	255, 0,
	//C25
	IMG_C25_9,
	255, 0,
	255, 0,
	IMG_C25_9,
	255, 0,
	255, 0,
	IMG_C25_9,
	255, 0,
	255, 0,
	IMG_C25_9,
	255, 0,
	255, 0,
	IMG_C25_9,
	255, 0,
	255, 0,
	IMG_C25_9,
	255, 0,
	255, 0,
	//C26
	IMG_C26_8,
	IMG_C26_19, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C26_8,
	IMG_C26_19, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C26_8,
	IMG_C26_19, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C26_8,
	IMG_C26_19, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C26_8,
	IMG_C26_19, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C26_8,
	IMG_C26_19, WEAPON_EFFECT_IMG,
	255, 0,
	//C27
	IMG_C27_8,
	255, 0,
	255, 0,
	IMG_C27_8,
	255, 0,
	255, 0,
	IMG_C27_8,
	255, 0,
	255, 0,
	IMG_C27_8,
	255, 0,
	255, 0,
	IMG_C27_8,
	255, 0,
	255, 0,
	IMG_C27_8,
	255, 0,
	255, 0,
	//C28
	IMG_C28_8,
	IMG_C28_35, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C28_8,
	IMG_C28_35, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C28_8,
	IMG_C28_35, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C28_8,
	IMG_C28_35, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C28_8,
	IMG_C28_35, WEAPON_EFFECT_IMG,
	255, 0,
	IMG_C28_8,
	IMG_C28_35, WEAPON_EFFECT_IMG,
	255, 0,
	//C29
	IMG_C29_8,
	255, 0,
	255, 0,
	IMG_C29_8,
	255, 0,
	255, 0,
	IMG_C29_8,
	255, 0,
	255, 0,
	IMG_C29_8,
	255, 0,
	255, 0,
	IMG_C29_8,
	255, 0,
	255, 0,
	IMG_C29_8,
	255, 0,
	255, 0,
	//C30
	IMG_C30_14,
	255, 0,
	255, 0,
	IMG_C30_14,
	255, 0,
	255, 0,
	IMG_C30_14,
	255, 0,
	255, 0,
	IMG_C30_14,
	255, 0,
	255, 0,
	IMG_C30_14,
	255, 0,
	255, 0,
	IMG_C30_14,
	255, 0,
	255, 0,
	//C31
	IMG_C31_12,
	255, 0,
	255, 0,
	IMG_C31_12,
	255, 0,
	255, 0,
	IMG_C31_12,
	255, 0,
	255, 0,
	IMG_C31_12,
	255, 0,
	255, 0,
	IMG_C31_12,
	255, 0,
	255, 0,
	IMG_C31_12,
	255, 0,
	255, 0,
	//C32
	IMG_C32_8,
	255, 0,
	255, 0,
	IMG_C32_8,
	255, 0,
	255, 0,
	IMG_C32_8,
	255, 0,
	255, 0,
	IMG_C32_8,
	255, 0,
	255, 0,
	IMG_C32_8,
	255, 0,
	255, 0,
	IMG_C32_8,
	255, 0,
	255, 0,
	//C33
	IMG_C33_9,
	255, 0,
	255, 0,
	IMG_C33_9,
	255, 0,
	255, 0,
	IMG_C33_9,
	255, 0,
	255, 0,
	IMG_C33_9,
	255, 0,
	255, 0,
	IMG_C33_9,
	255, 0,
	255, 0,
	IMG_C33_9,
	255, 0,
	255, 0,
	//C34
	IMG_C34_8,
	IMG_C34_34, WEAPON_EFFECT_IMG,
	IMG_C34_35, ATTR_IMG,
	IMG_C34_8,
	IMG_C34_34, WEAPON_EFFECT_IMG,
	IMG_C34_35, ATTR_IMG,
	IMG_C34_8,
	IMG_C34_34, WEAPON_EFFECT_IMG,
	IMG_C34_35, ATTR_IMG,
	IMG_C34_8,
	IMG_C34_34, WEAPON_EFFECT_IMG,
	IMG_C34_35, ATTR_IMG,
	IMG_C34_8,
	IMG_C34_34, WEAPON_EFFECT_IMG,
	IMG_C34_35, ATTR_IMG,
	IMG_C34_8,
	IMG_C34_34, WEAPON_EFFECT_IMG,
	IMG_C34_35, ATTR_IMG,
	//C35
	IMG_C35_9,
	255, 0,
	255, 0,
	IMG_C35_9,
	255, 0,
	255, 0,
	IMG_C35_9,
	255, 0,
	255, 0,
	IMG_C35_9,
	255, 0,
	255, 0,
	IMG_C35_9,
	255, 0,
	255, 0,
	IMG_C35_9,
	255, 0,
	255, 0,
	//C36
	IMG_C36_9,
	255, 0,
	255, 0,
	IMG_C36_9,
	255, 0,
	255, 0,
	IMG_C36_9,
	255, 0,
	255, 0,
	IMG_C36_9,
	255, 0,
	255, 0,
	IMG_C36_9,
	255, 0,
	255, 0,
	IMG_C36_9,
	255, 0,
	255, 0,
	//C37
	IMG_C37_9,
	IMG_C37_37, ATTR_IMG,
	255, 0,
	IMG_C37_9,
	IMG_C37_37, ATTR_IMG,
	255, 0,
	IMG_C37_9,
	IMG_C37_37, ATTR_IMG,
	255, 0,
	IMG_C37_9,
	IMG_C37_37, ATTR_IMG,
	255, 0,
	IMG_C37_9,
	IMG_C37_37, ATTR_IMG,
	255, 0,
	IMG_C37_9,
	IMG_C37_37, ATTR_IMG,
	255, 0,
	//C38
	IMG_C38_8,
	255, 0,
	255, 0,
	IMG_C38_8,
	255, 0,
	255, 0,
	IMG_C38_8,
	255, 0,
	255, 0,
	IMG_C38_8,
	255, 0,
	255, 0,
	IMG_C38_8,
	255, 0,
	255, 0,
	IMG_C38_8,
	255, 0,
	255, 0,
	//C39
	IMG_C39_8,
	255, 0,
	255, 0,
	IMG_C39_8,
	255, 0,
	255, 0,
	IMG_C39_8,
	255, 0,
	255, 0,
	IMG_C39_8,
	255, 0,
	255, 0,
	IMG_C39_8,
	255, 0,
	255, 0,
	IMG_C39_8,
	255, 0,
	255, 0,
	//C40
	IMG_C40_8,
	IMG_C40_28, ATTR_IMG,
	255, 0,
	IMG_C40_8,
	IMG_C40_28, ATTR_IMG,
	255, 0,
	IMG_C40_8,
	IMG_C40_28, ATTR_IMG,
	255, 0,
	IMG_C40_8,
	IMG_C40_28, ATTR_IMG,
	255, 0,
	IMG_C40_8,
	IMG_C40_28, ATTR_IMG,
	255, 0,
	IMG_C40_8,
	IMG_C40_28, ATTR_IMG,
	255, 0,
	//C41
	IMG_C41_8,
	255, 0,
	255, 0,
	IMG_C41_8,
	255, 0,
	255, 0,
	IMG_C41_8,
	255, 0,
	255, 0,
	IMG_C41_8,
	255, 0,
	255, 0,
	IMG_C41_8,
	255, 0,
	255, 0,
	IMG_C41_8,
	255, 0,
	255, 0,
	//C42
	IMG_C42_8,
	255, 0,
	255, 0,
	IMG_C42_8,
	255, 0,
	255, 0,
	IMG_C42_8,
	255, 0,
	255, 0,
	IMG_C42_8,
	255, 0,
	255, 0,
	IMG_C42_8,
	255, 0,
	255, 0,
	IMG_C42_8,
	255, 0,
	255, 0,
	//C43
	IMG_C43_10,
	255, 0,
	255, 0,
	IMG_C43_10,
	255, 0,
	255, 0,
	IMG_C43_10,
	255, 0,
	255, 0,
	IMG_C43_10,
	255, 0,
	255, 0,
	IMG_C43_10,
	255, 0,
	255, 0,
	IMG_C43_10,
	255, 0,
	255, 0,
	//C44
	IMG_C44_9,
	255, 0,
	255, 0,
	IMG_C44_9,
	255, 0,
	255, 0,
	IMG_C44_9,
	255, 0,
	255, 0,
	IMG_C44_9,
	255, 0,
	255, 0,
	IMG_C44_9,
	255, 0,
	255, 0,
	IMG_C44_9,
	255, 0,
	255, 0,
	//C45
	IMG_C45_8,
	255, 0,
	255, 0,
	IMG_C45_8,
	255, 0,
	255, 0,
	IMG_C45_8,
	255, 0,
	255, 0,
	IMG_C45_8,
	255, 0,
	255, 0,
	IMG_C45_8,
	255, 0,
	255, 0,
	IMG_C45_8,
	255, 0,
	255, 0,
	//C46
	IMG_C46_8,
	255, 0,
	255, 0,
	IMG_C46_8,
	255, 0,
	255, 0,
	IMG_C46_8,
	255, 0,
	255, 0,
	IMG_C46_8,
	255, 0,
	255, 0,
	IMG_C46_8,
	255, 0,
	255, 0,
	IMG_C46_8,
	255, 0,
	255, 0,
	//C47
	IMG_C47_8,
	255, 0,
	255, 0,
	IMG_C47_8,
	255, 0,
	255, 0,
	IMG_C47_8,
	255, 0,
	255, 0,
	IMG_C47_8,
	255, 0,
	255, 0,
	IMG_C47_8,
	255, 0,
	255, 0,
	IMG_C47_8,
	255, 0,
	255, 0,
	//C48
	IMG_C48_8,
	255, 0,
	255, 0,
	IMG_C48_8,
	255, 0,
	255, 0,
	IMG_C48_8,
	255, 0,
	255, 0,
	IMG_C48_8,
	255, 0,
	255, 0,
	IMG_C48_8,
	255, 0,
	255, 0,
	IMG_C48_8,
	255, 0,
	255, 0,
	//C49
	IMG_C49_9,
	255, 0,
	255, 0,
	IMG_C49_9,
	255, 0,
	255, 0,
	IMG_C49_9,
	255, 0,
	255, 0,
	IMG_C49_9,
	255, 0,
	255, 0,
	IMG_C49_9,
	255, 0,
	255, 0,
	IMG_C49_9,
	255, 0,
	255, 0,
	//C50
	IMG_C50_9,
	255, 0,
	255, 0,
	IMG_C50_9,
	255, 0,
	255, 0,
	IMG_C50_9,
	255, 0,
	255, 0,
	IMG_C50_9,
	255, 0,
	255, 0,
	IMG_C50_9,
	255, 0,
	255, 0,
	IMG_C50_9,
	255, 0,
	255, 0,
	//C51
	IMG_C51_8,
	255, 0,
	255, 0,
	IMG_C51_8,
	255, 0,
	255, 0,
	IMG_C51_8,
	255, 0,
	255, 0,
	IMG_C51_8,
	255, 0,
	255, 0,
	IMG_C51_8,
	255, 0,
	255, 0,
	IMG_C51_8,
	255, 0,
	255, 0,
	//C109
	IMG_C109_8,
	255, 0,
	255, 0,
	IMG_C109_8,
	255, 0,
	255, 0,
	IMG_C109_8,
	255, 0,
	255, 0,
	IMG_C109_8,
	255, 0,
	255, 0,
	IMG_C109_8,
	255, 0,
	255, 0,
	IMG_C109_8,
	255, 0,
	255, 0,
	//C110
	IMG_C110_12,
	255, 0,
	255, 0,
	IMG_C110_12,
	255, 0,
	255, 0,
	IMG_C110_12,
	255, 0,
	255, 0,
	IMG_C110_12,
	255, 0,
	255, 0,
	IMG_C110_12,
	255, 0,
	255, 0,
	IMG_C110_12,
	255, 0,
	255, 0,
};

const unsigned short* const cmfOff[] = {
	c0Off, c1Off, c2Off, c3Off, c4Off, c5Off, c6Off, c7Off, c8Off, c9Off,
	c10Off, c11Off, c12Off, c13Off, c14Off, c15Off, c16Off, c17Off, c18Off, c19Off,
	c20Off, c21Off, c22Off, c23Off, c24Off, c25Off, c26Off, c27Off, c28Off, c29Off,
	c30Off, c31Off, c32Off, c33Off, c34Off, c35Off, c36Off, c37Off, c38Off, c39Off,
	c40Off, c41Off, c42Off, c43Off, c44Off, c45Off, c46Off, c47Off, c48Off, c49Off,
	c50Off, c51Off, c52Off, c53Off, c54Off, c55Off, c56Off, c57Off, c58Off, c59Off,
	c60Off, c61Off, c62Off, c63Off, c64Off, c65Off, c66Off, c67Off, c68Off, c69Off,
	c70Off, c71Off, c72Off, c73Off, c74Off, c75Off, c76Off, c77Off, c78Off, c79Off,
	c80Off, c81Off, c82Off, c83Off, c84Off, c85Off, c86Off, c87Off, c88Off, c89Off,
	c90Off, c91Off, c92Off, c93Off, c94Off, c95Off, c96Off, c97Off, c98Off, c99Off,
	c100Off, c101Off, c102Off, c103Off, c104Off, c105Off, c106Off, c107Off, c108Off, c109Off,
	c110Off, c111Off, c112Off, c113Off, c114Off, c115Off, c116Off, c117Off, c118Off, c119Off,
	c120Off, c121Off, c122Off,

	c3Off, c3Off, c3Off, c3Off, c3Off, c3Off,
	c4Off, c4Off, c4Off, c4Off, c4Off, c4Off,
	c5Off, c5Off, c5Off, c5Off, c5Off, c5Off,
	c6Off, c6Off, c6Off, c6Off, c6Off, c6Off,
	c7Off, c7Off, c7Off, c7Off, c7Off, c7Off,
	c8Off, c8Off, c8Off, c8Off, c8Off, c8Off,
	c9Off, c9Off, c9Off, c9Off, c9Off, c9Off,
	c10Off, c10Off, c10Off, c10Off, c10Off, c10Off,
	c11Off, c11Off, c11Off, c11Off, c11Off, c11Off,
	c12Off, c12Off, c12Off, c12Off, c12Off, c12Off,
	c13Off, c13Off, c13Off, c13Off, c13Off, c13Off,
	c14Off, c14Off, c14Off, c14Off, c14Off, c14Off,
	c15Off, c15Off, c15Off, c15Off, c15Off, c15Off,
	c16Off, c16Off, c16Off, c16Off, c16Off, c16Off,
	c17Off, c17Off, c17Off, c17Off, c17Off, c17Off,
	c18Off, c18Off, c18Off, c18Off, c18Off, c18Off,
	c19Off, c19Off, c19Off, c19Off, c19Off, c19Off,
	c20Off, c20Off, c20Off, c20Off, c20Off, c20Off,
	c21Off, c21Off, c21Off, c21Off, c21Off, c21Off,
	c22Off, c22Off, c22Off, c22Off, c22Off, c22Off,
	c23Off, c23Off, c23Off, c23Off, c23Off, c23Off,
	c24Off, c24Off, c24Off, c24Off, c24Off, c24Off,
	c25Off, c25Off, c25Off, c25Off, c25Off, c25Off,
	c26Off, c26Off, c26Off, c26Off, c26Off, c26Off,
	c27Off, c27Off, c27Off, c27Off, c27Off, c27Off,
	c28Off, c28Off, c28Off, c28Off, c28Off, c28Off,
	c29Off, c29Off, c29Off, c29Off, c29Off, c29Off,
	c30Off, c30Off, c30Off, c30Off, c30Off, c30Off,
	c31Off, c31Off, c31Off, c31Off, c31Off, c31Off,
	c32Off, c32Off, c32Off, c32Off, c32Off, c32Off,
	c33Off, c33Off, c33Off, c33Off, c33Off, c33Off,
	c34Off, c34Off, c34Off, c34Off, c34Off, c34Off,
	c35Off, c35Off, c35Off, c35Off, c35Off, c35Off,
	c36Off, c36Off, c36Off, c36Off, c36Off, c36Off,
	c37Off, c37Off, c37Off, c37Off, c37Off, c37Off,
	c38Off, c38Off, c38Off, c38Off, c38Off, c38Off,
	c39Off, c39Off, c39Off, c39Off, c39Off, c39Off,
	c40Off, c40Off, c40Off, c40Off, c40Off, c40Off,
	c41Off, c41Off, c41Off, c41Off, c41Off, c41Off,
	c42Off, c42Off, c42Off, c42Off, c42Off, c42Off,
	c43Off, c43Off, c43Off, c43Off, c43Off, c43Off,
	c44Off, c44Off, c44Off, c44Off, c44Off, c44Off,
	c45Off, c45Off, c45Off, c45Off, c45Off, c45Off,
	c46Off, c46Off, c46Off, c46Off, c46Off, c46Off,
	c47Off, c47Off, c47Off, c47Off, c47Off, c47Off,
	c48Off, c48Off, c48Off, c48Off, c48Off, c48Off,
	c49Off, c49Off, c49Off, c49Off, c49Off, c49Off,
	c50Off, c50Off, c50Off, c50Off, c50Off, c50Off,
	c51Off, c51Off, c51Off, c51Off, c51Off, c51Off,
	c109Off, c109Off, c109Off, c109Off, c109Off, c109Off,
	c110Off, c110Off, c110Off, c110Off, c110Off, c110Off,
};

const signed short* const cmfMotionImg[] = {
	c0MI, c1MI, c2MI, c3MI, c4MI, c5MI, c6MI, c7MI, c8MI, c9MI,
	c10MI, c11MI, c12MI, c13MI, c14MI, c15MI, c16MI, c17MI, c18MI, c19MI,
	c20MI, c21MI, c22MI, c23MI, c24MI, c25MI, c26MI, c27MI, c28MI, c29MI,
	c30MI, c31MI, c32MI, c33MI, c34MI, c35MI, c36MI, c37MI, c38MI, c39MI,
	c40MI, c41MI, c42MI, c43MI, c44MI, c45MI, c46MI, c47MI, c48MI, c49MI,
	c50MI, c51MI, c52MI, c53MI, c54MI, c55MI, c56MI, c57MI, c58MI, c59MI,
	c60MI, c61MI, c62MI, c63MI, c64MI, c65MI, c66MI, c67MI, c68MI, c69MI,
	c70MI, c71MI, c72MI, c73MI, c74MI, c75MI, c76MI, c77MI, c78MI, c79MI,
	c80MI, c81MI, c82MI, c83MI, c84MI, c85MI, c86MI, c87MI, c88MI, c89MI,
	c90MI, c91MI, c92MI, c93MI, c94MI, c95MI, c96MI, c97MI, c98MI, c99MI,
	c100MI, c101MI, c102MI, c103MI, c104MI, c105MI, c106MI, c107MI, c108MI, c109MI,
	c110MI, c111MI, c112MI, c113MI, c114MI, c115MI, c116MI, c117MI, c118MI, c119MI,
	c120MI, c121MI, c122MI,

	c3MI, c3MI, c3MI, c3MI, c3MI, c3MI,
	c4MI, c4MI, c4MI, c4MI, c4MI, c4MI,
	c5MI, c5MI, c5MI, c5MI, c5MI, c5MI,
	c6MI, c6MI, c6MI, c6MI, c6MI, c6MI,
	c7MI, c7MI, c7MI, c7MI, c7MI, c7MI,
	c8MI, c8MI, c8MI, c8MI, c8MI, c8MI,
	c9MI, c9MI, c9MI, c9MI, c9MI, c9MI,
	c10MI, c10MI, c10MI, c10MI, c10MI, c10MI,
	c11MI, c11MI, c11MI, c11MI, c11MI, c11MI,
	c12MI, c12MI, c12MI, c12MI, c12MI, c12MI,
	c13MI, c13MI, c13MI, c13MI, c13MI, c13MI,
	c14MI, c14MI, c14MI, c14MI, c14MI, c14MI,
	c15MI, c15MI, c15MI, c15MI, c15MI, c15MI,
	c16MI, c16MI, c16MI, c16MI, c16MI, c16MI,
	c17MI, c17MI, c17MI, c17MI, c17MI, c17MI,
	c18MI, c18MI, c18MI, c18MI, c18MI, c18MI,
	c19MI, c19MI, c19MI, c19MI, c19MI, c19MI,
	c20MI, c20MI, c20MI, c20MI, c20MI, c20MI,
	c21MI, c21MI, c21MI, c21MI, c21MI, c21MI,
	c22MI, c22MI, c22MI, c22MI, c22MI, c22MI,
	c23MI, c23MI, c23MI, c23MI, c23MI, c23MI,
	c24MI, c24MI, c24MI, c24MI, c24MI, c24MI,
	c25MI, c25MI, c25MI, c25MI, c25MI, c25MI,
	c26MI, c26MI, c26MI, c26MI, c26MI, c26MI,
	c27MI, c27MI, c27MI, c27MI, c27MI, c27MI,
	c28MI, c28MI, c28MI, c28MI, c28MI, c28MI,
	c29MI, c29MI, c29MI, c29MI, c29MI, c29MI,
	c30MI, c30MI, c30MI, c30MI, c30MI, c30MI,
	c31MI, c31MI, c31MI, c31MI, c31MI, c31MI,
	c32MI, c32MI, c32MI, c32MI, c32MI, c32MI,
	c33MI, c33MI, c33MI, c33MI, c33MI, c33MI,
	c34MI, c34MI, c34MI, c34MI, c34MI, c34MI,
	c35MI, c35MI, c35MI, c35MI, c35MI, c35MI,
	c36MI, c36MI, c36MI, c36MI, c36MI, c36MI,
	c37MI, c37MI, c37MI, c37MI, c37MI, c37MI,
	c38MI, c38MI, c38MI, c38MI, c38MI, c38MI,
	c39MI, c39MI, c39MI, c39MI, c39MI, c39MI,
	c40MI, c40MI, c40MI, c40MI, c40MI, c40MI,
	c41MI, c41MI, c41MI, c41MI, c41MI, c41MI,
	c42MI, c42MI, c42MI, c42MI, c42MI, c42MI,
	c43MI, c43MI, c43MI, c43MI, c43MI, c43MI,
	c44MI, c44MI, c44MI, c44MI, c44MI, c44MI,
	c45MI, c45MI, c45MI, c45MI, c45MI, c45MI,
	c46MI, c46MI, c46MI, c46MI, c46MI, c46MI,
	c47MI, c47MI, c47MI, c47MI, c47MI, c47MI,
	c48MI, c48MI, c48MI, c48MI, c48MI, c48MI,
	c49MI, c49MI, c49MI, c49MI, c49MI, c49MI,
	c50MI, c50MI, c50MI, c50MI, c50MI, c50MI,
	c51MI, c51MI, c51MI, c51MI, c51MI, c51MI,
	c109MI, c109MI, c109MI, c109MI, c109MI, c109MI,
	c110MI, c110MI, c110MI, c110MI, c110MI, c110MI,
};

const unsigned short* const cmfMotionImgCnt[] = {
	c0MIC, c1MIC, c2MIC, c3MIC, c4MIC, c5MIC, c6MIC, c7MIC, c8MIC, c9MIC,
	c10MIC, c11MIC, c12MIC, c13MIC, c14MIC, c15MIC, c16MIC, c17MIC, c18MIC, c19MIC,
	c20MIC, c21MIC, c22MIC, c23MIC, c24MIC, c25MIC, c26MIC, c27MIC, c28MIC, c29MIC,
	c30MIC, c31MIC, c32MIC, c33MIC, c34MIC, c35MIC, c36MIC, c37MIC, c38MIC, c39MIC,
	c40MIC, c41MIC, c42MIC, c43MIC, c44MIC, c45MIC, c46MIC, c47MIC, c48MIC, c49MIC,
	c50MIC, c51MIC, c52MIC, c53MIC, c54MIC, c55MIC, c56MIC, c57MIC, c58MIC, c59MIC,
	c60MIC, c61MIC, c62MIC, c63MIC, c64MIC, c65MIC, c66MIC, c67MIC, c68MIC, c69MIC,
	c70MIC, c71MIC, c72MIC, c73MIC, c74MIC, c75MIC, c76MIC, c77MIC, c78MIC, c79MIC,
	c80MIC, c81MIC, c82MIC, c83MIC, c84MIC, c85MIC, c86MIC, c87MIC, c88MIC, c89MIC,
	c90MIC, c91MIC, c92MIC, c93MIC, c94MIC, c95MIC, c96MIC, c97MIC, c98MIC, c99MIC,
	c100MIC, c101MIC, c102MIC, c103MIC, c104MIC, c105MIC, c106MIC, c107MIC, c108MIC, c109MIC,
	c110MIC, c111MIC, c112MIC, c113MIC, c114MIC, c115MIC, c116MIC, c117MIC, c118MIC, c119MIC,
	c120MIC, c121MIC, c122MIC,

	c3MIC, c3MIC, c3MIC, c3MIC, c3MIC, c3MIC,
	c4MIC, c4MIC, c4MIC, c4MIC, c4MIC, c4MIC,
	c5MIC, c5MIC, c5MIC, c5MIC, c5MIC, c5MIC,
	c6MIC, c6MIC, c6MIC, c6MIC, c6MIC, c6MIC,
	c7MIC, c7MIC, c7MIC, c7MIC, c7MIC, c7MIC,
	c8MIC, c8MIC, c8MIC, c8MIC, c8MIC, c8MIC,
	c9MIC, c9MIC, c9MIC, c9MIC, c9MIC, c9MIC,
	c10MIC, c10MIC, c10MIC, c10MIC, c10MIC, c10MIC,
	c11MIC, c11MIC, c11MIC, c11MIC, c11MIC, c11MIC,
	c12MIC, c12MIC, c12MIC, c12MIC, c12MIC, c12MIC,
	c13MIC, c13MIC, c13MIC, c13MIC, c13MIC, c13MIC,
	c14MIC, c14MIC, c14MIC, c14MIC, c14MIC, c14MIC,
	c15MIC, c15MIC, c15MIC, c15MIC, c15MIC, c15MIC,
	c16MIC, c16MIC, c16MIC, c16MIC, c16MIC, c16MIC,
	c17MIC, c17MIC, c17MIC, c17MIC, c17MIC, c17MIC,
	c18MIC, c18MIC, c18MIC, c18MIC, c18MIC, c18MIC,
	c19MIC, c19MIC, c19MIC, c19MIC, c19MIC, c19MIC,
	c20MIC, c20MIC, c20MIC, c20MIC, c20MIC, c20MIC,
	c21MIC, c21MIC, c21MIC, c21MIC, c21MIC, c21MIC,
	c22MIC, c22MIC, c22MIC, c22MIC, c22MIC, c22MIC,
	c23MIC, c23MIC, c23MIC, c23MIC, c23MIC, c23MIC,
	c24MIC, c24MIC, c24MIC, c24MIC, c24MIC, c24MIC,
	c25MIC, c25MIC, c25MIC, c25MIC, c25MIC, c25MIC,
	c26MIC, c26MIC, c26MIC, c26MIC, c26MIC, c26MIC,
	c27MIC, c27MIC, c27MIC, c27MIC, c27MIC, c27MIC,
	c28MIC, c28MIC, c28MIC, c28MIC, c28MIC, c28MIC,
	c29MIC, c29MIC, c29MIC, c29MIC, c29MIC, c29MIC,
	c30MIC, c30MIC, c30MIC, c30MIC, c30MIC, c30MIC,
	c31MIC, c31MIC, c31MIC, c31MIC, c31MIC, c31MIC,
	c32MIC, c32MIC, c32MIC, c32MIC, c32MIC, c32MIC,
	c33MIC, c33MIC, c33MIC, c33MIC, c33MIC, c33MIC,
	c34MIC, c34MIC, c34MIC, c34MIC, c34MIC, c34MIC,
	c35MIC, c35MIC, c35MIC, c35MIC, c35MIC, c35MIC,
	c36MIC, c36MIC, c36MIC, c36MIC, c36MIC, c36MIC,
	c37MIC, c37MIC, c37MIC, c37MIC, c37MIC, c37MIC,
	c38MIC, c38MIC, c38MIC, c38MIC, c38MIC, c38MIC,
	c39MIC, c39MIC, c39MIC, c39MIC, c39MIC, c39MIC,
	c40MIC, c40MIC, c40MIC, c40MIC, c40MIC, c40MIC,
	c41MIC, c41MIC, c41MIC, c41MIC, c41MIC, c41MIC,
	c42MIC, c42MIC, c42MIC, c42MIC, c42MIC, c42MIC,
	c43MIC, c43MIC, c43MIC, c43MIC, c43MIC, c43MIC,
	c44MIC, c44MIC, c44MIC, c44MIC, c44MIC, c44MIC,
	c45MIC, c45MIC, c45MIC, c45MIC, c45MIC, c45MIC,
	c46MIC, c46MIC, c46MIC, c46MIC, c46MIC, c46MIC,
	c47MIC, c47MIC, c47MIC, c47MIC, c47MIC, c47MIC,
	c48MIC, c48MIC, c48MIC, c48MIC, c48MIC, c48MIC,
	c49MIC, c49MIC, c49MIC, c49MIC, c49MIC, c49MIC,
	c50MIC, c50MIC, c50MIC, c50MIC, c50MIC, c50MIC,
	c51MIC, c51MIC, c51MIC, c51MIC, c51MIC, c51MIC,
	c109MIC, c109MIC, c109MIC, c109MIC, c109MIC, c109MIC,
	c110MIC, c110MIC, c110MIC, c110MIC, c110MIC, c110MIC,
};

const signed short* const cmfMotionImgSize[] = {
	c0MIS, c1MIS, c2MIS, c3MIS, c4MIS, c5MIS, c6MIS, c7MIS, c8MIS, c9MIS,
	c10MIS, c11MIS, c12MIS, c13MIS, c14MIS, c15MIS, c16MIS, c17MIS, c18MIS, c19MIS,
	c20MIS, c21MIS, c22MIS, c23MIS, c24MIS, c25MIS, c26MIS, c27MIS, c28MIS, c29MIS,
	c30MIS, c31MIS, c32MIS, c33MIS, c34MIS, c35MIS, c36MIS, c37MIS, c38MIS, c39MIS,
	c40MIS, c41MIS, c42MIS, c43MIS, c44MIS, c45MIS, c46MIS, c47MIS, c48MIS, c49MIS,
	c50MIS, c51MIS, c52MIS, c53MIS, c54MIS, c55MIS, c56MIS, c57MIS, c58MIS, c59MIS,
	c60MIS, c61MIS, c62MIS, c63MIS, c64MIS, c65MIS, c66MIS, c67MIS, c68MIS, c69MIS,
	c70MIS, c71MIS, c72MIS, c73MIS, c74MIS, c75MIS, c76MIS, c77MIS, c78MIS, c79MIS,
	c80MIS, c81MIS, c82MIS, c83MIS, c84MIS, c85MIS, c86MIS, c87MIS, c88MIS, c89MIS,
	c90MIS, c91MIS, c92MIS, c93MIS, c94MIS, c95MIS, c96MIS, c97MIS, c98MIS, c99MIS,
	c100MIS, c101MIS, c102MIS, c103MIS, c104MIS, c105MIS, c106MIS, c107MIS, c108MIS, c109MIS,
	c110MIS, c111MIS, c112MIS, c113MIS, c114MIS, c115MIS, c116MIS, c117MIS, c118MIS, c119MIS,
	c120MIS, c121MIS, c122MIS,

	c3MIS, c3MIS, c3MIS, c3MIS, c3MIS, c3MIS,
	c4MIS, c4MIS, c4MIS, c4MIS, c4MIS, c4MIS,
	c5MIS, c5MIS, c5MIS, c5MIS, c5MIS, c5MIS,
	c6MIS, c6MIS, c6MIS, c6MIS, c6MIS, c6MIS,
	c7MIS, c7MIS, c7MIS, c7MIS, c7MIS, c7MIS,
	c8MIS, c8MIS, c8MIS, c8MIS, c8MIS, c8MIS,
	c9MIS, c9MIS, c9MIS, c9MIS, c9MIS, c9MIS,
	c10MIS, c10MIS, c10MIS, c10MIS, c10MIS, c10MIS,
	c11MIS, c11MIS, c11MIS, c11MIS, c11MIS, c11MIS,
	c12MIS, c12MIS, c12MIS, c12MIS, c12MIS, c12MIS,
	c13MIS, c13MIS, c13MIS, c13MIS, c13MIS, c13MIS,
	c14MIS, c14MIS, c14MIS, c14MIS, c14MIS, c14MIS,
	c15MIS, c15MIS, c15MIS, c15MIS, c15MIS, c15MIS,
	c16MIS, c16MIS, c16MIS, c16MIS, c16MIS, c16MIS,
	c17MIS, c17MIS, c17MIS, c17MIS, c17MIS, c17MIS,
	c18MIS, c18MIS, c18MIS, c18MIS, c18MIS, c18MIS,
	c19MIS, c19MIS, c19MIS, c19MIS, c19MIS, c19MIS,
	c20MIS, c20MIS, c20MIS, c20MIS, c20MIS, c20MIS,
	c21MIS, c21MIS, c21MIS, c21MIS, c21MIS, c21MIS,
	c22MIS, c22MIS, c22MIS, c22MIS, c22MIS, c22MIS,
	c23MIS, c23MIS, c23MIS, c23MIS, c23MIS, c23MIS,
	c24MIS, c24MIS, c24MIS, c24MIS, c24MIS, c24MIS,
	c25MIS, c25MIS, c25MIS, c25MIS, c25MIS, c25MIS,
	c26MIS, c26MIS, c26MIS, c26MIS, c26MIS, c26MIS,
	c27MIS, c27MIS, c27MIS, c27MIS, c27MIS, c27MIS,
	c28MIS, c28MIS, c28MIS, c28MIS, c28MIS, c28MIS,
	c29MIS, c29MIS, c29MIS, c29MIS, c29MIS, c29MIS,
	c30MIS, c30MIS, c30MIS, c30MIS, c30MIS, c30MIS,
	c31MIS, c31MIS, c31MIS, c31MIS, c31MIS, c31MIS,
	c32MIS, c32MIS, c32MIS, c32MIS, c32MIS, c32MIS,
	c33MIS, c33MIS, c33MIS, c33MIS, c33MIS, c33MIS,
	c34MIS, c34MIS, c34MIS, c34MIS, c34MIS, c34MIS,
	c35MIS, c35MIS, c35MIS, c35MIS, c35MIS, c35MIS,
	c36MIS, c36MIS, c36MIS, c36MIS, c36MIS, c36MIS,
	c37MIS, c37MIS, c37MIS, c37MIS, c37MIS, c37MIS,
	c38MIS, c38MIS, c38MIS, c38MIS, c38MIS, c38MIS,
	c39MIS, c39MIS, c39MIS, c39MIS, c39MIS, c39MIS,
	c40MIS, c40MIS, c40MIS, c40MIS, c40MIS, c40MIS,
	c41MIS, c41MIS, c41MIS, c41MIS, c41MIS, c41MIS,
	c42MIS, c42MIS, c42MIS, c42MIS, c42MIS, c42MIS,
	c43MIS, c43MIS, c43MIS, c43MIS, c43MIS, c43MIS,
	c44MIS, c44MIS, c44MIS, c44MIS, c44MIS, c44MIS,
	c45MIS, c45MIS, c45MIS, c45MIS, c45MIS, c45MIS,
	c46MIS, c46MIS, c46MIS, c46MIS, c46MIS, c46MIS,
	c47MIS, c47MIS, c47MIS, c47MIS, c47MIS, c47MIS,
	c48MIS, c48MIS, c48MIS, c48MIS, c48MIS, c48MIS,
	c49MIS, c49MIS, c49MIS, c49MIS, c49MIS, c49MIS,
	c50MIS, c50MIS, c50MIS, c50MIS, c50MIS, c50MIS,
	c51MIS, c51MIS, c51MIS, c51MIS, c51MIS, c51MIS,
	c109MIS, c109MIS, c109MIS, c109MIS, c109MIS, c109MIS,
	c110MIS, c110MIS, c110MIS, c110MIS, c110MIS, c110MIS,
};

const signed short* const cmfCrashSize[] = {
	c0CS, c1CS, c2CS, c3CS, c4CS, c5CS, c6CS, c7CS, c8CS, c9CS,
	c10CS, c11CS, c12CS, c13CS, c14CS, c15CS, c16CS, c17CS, c18CS, c19CS,
	c20CS, c21CS, c22CS, c23CS, c24CS, c25CS, c26CS, c27CS, c28CS, c29CS,
	c30CS, c31CS, c32CS, c33CS, c34CS, c35CS, c36CS, c37CS, c38CS, c39CS,
	c40CS, c41CS, c42CS, c43CS, c44CS, c45CS, c46CS, c47CS, c48CS, c49CS,
	c50CS, c51CS, c52CS, c53CS, c54CS, c55CS, c56CS, c57CS, c58CS, c59CS,
	c60CS, c61CS, c62CS, c63CS, c64CS, c65CS, c66CS, c67CS, c68CS, c69CS,
	c70CS, c71CS, c72CS, c73CS, c74CS, c75CS, c76CS, c77CS, c78CS, c79CS,
	c80CS, c81CS, c82CS, c83CS, c84CS, c85CS, c86CS, c87CS, c88CS, c89CS,
	c90CS, c91CS, c92CS, c93CS, c94CS, c95CS, c96CS, c97CS, c98CS, c99CS,
	c100CS, c101CS, c102CS, c103CS, c104CS, c105CS, c106CS, c107CS, c108CS, c109CS,
	c110CS, c111CS, c112CS, c113CS, c114CS, c115CS, c116CS, c117CS, c118CS, c119CS,
	c120CS, c121CS, c122CS,

	c3CS, c3CS, c3CS, c3CS, c3CS, c3CS,
	c4CS, c4CS, c4CS, c4CS, c4CS, c4CS,
	c5CS, c5CS, c5CS, c5CS, c5CS, c5CS,
	c6CS, c6CS, c6CS, c6CS, c6CS, c6CS,
	c7CS, c7CS, c7CS, c7CS, c7CS, c7CS,
	c8CS, c8CS, c8CS, c8CS, c8CS, c8CS,
	c9CS, c9CS, c9CS, c9CS, c9CS, c9CS,
	c10CS, c10CS, c10CS, c10CS, c10CS, c10CS,
	c11CS, c11CS, c11CS, c11CS, c11CS, c11CS,
	c12CS, c12CS, c12CS, c12CS, c12CS, c12CS,
	c13CS, c13CS, c13CS, c13CS, c13CS, c13CS,
	c14CS, c14CS, c14CS, c14CS, c14CS, c14CS,
	c15CS, c15CS, c15CS, c15CS, c15CS, c15CS,
	c16CS, c16CS, c16CS, c16CS, c16CS, c16CS,
	c17CS, c17CS, c17CS, c17CS, c17CS, c17CS,
	c18CS, c18CS, c18CS, c18CS, c18CS, c18CS,
	c19CS, c19CS, c19CS, c19CS, c19CS, c19CS,
	c20CS, c20CS, c20CS, c20CS, c20CS, c20CS,
	c21CS, c21CS, c21CS, c21CS, c21CS, c21CS,
	c22CS, c22CS, c22CS, c22CS, c22CS, c22CS,
	c23CS, c23CS, c23CS, c23CS, c23CS, c23CS,
	c24CS, c24CS, c24CS, c24CS, c24CS, c24CS,
	c25CS, c25CS, c25CS, c25CS, c25CS, c25CS,
	c26CS, c26CS, c26CS, c26CS, c26CS, c26CS,
	c27CS, c27CS, c27CS, c27CS, c27CS, c27CS,
	c28CS, c28CS, c28CS, c28CS, c28CS, c28CS,
	c29CS, c29CS, c29CS, c29CS, c29CS, c29CS,
	c30CS, c30CS, c30CS, c30CS, c30CS, c30CS,
	c31CS, c31CS, c31CS, c31CS, c31CS, c31CS,
	c32CS, c32CS, c32CS, c32CS, c32CS, c32CS,
	c33CS, c33CS, c33CS, c33CS, c33CS, c33CS,
	c34CS, c34CS, c34CS, c34CS, c34CS, c34CS,
	c35CS, c35CS, c35CS, c35CS, c35CS, c35CS,
	c36CS, c36CS, c36CS, c36CS, c36CS, c36CS,
	c37CS, c37CS, c37CS, c37CS, c37CS, c37CS,
	c38CS, c38CS, c38CS, c38CS, c38CS, c38CS,
	c39CS, c39CS, c39CS, c39CS, c39CS, c39CS,
	c40CS, c40CS, c40CS, c40CS, c40CS, c40CS,
	c41CS, c41CS, c41CS, c41CS, c41CS, c41CS,
	c42CS, c42CS, c42CS, c42CS, c42CS, c42CS,
	c43CS, c43CS, c43CS, c43CS, c43CS, c43CS,
	c44CS, c44CS, c44CS, c44CS, c44CS, c44CS,
	c45CS, c45CS, c45CS, c45CS, c45CS, c45CS,
	c46CS, c46CS, c46CS, c46CS, c46CS, c46CS,
	c47CS, c47CS, c47CS, c47CS, c47CS, c47CS,
	c48CS, c48CS, c48CS, c48CS, c48CS, c48CS,
	c49CS, c49CS, c49CS, c49CS, c49CS, c49CS,
	c50CS, c50CS, c50CS, c50CS, c50CS, c50CS,
	c51CS, c51CS, c51CS, c51CS, c51CS, c51CS,
	c109CS, c109CS, c109CS, c109CS, c109CS, c109CS,
	c110CS, c110CS, c110CS, c110CS, c110CS, c110CS,
};

//히어로의 대기/걷기/달리기/수영은 mv 데이터가 아니라 코드가 모션을 직접 고른다.
//60프레임용으로 4배 늘린 순환표가 있는 cmf만 여기 채운다. 0이면 예전 식을 그대로 쓴다.
const unsigned short* const cmfHeroLoop[] = {
	c0Loop60,	//c0 로빈
	c1Loop60,	//c1 디아나
	c2Loop60,	//c2 맥스
};

const int cmfHeroLoopCnt = sizeof(cmfHeroLoop) / sizeof(cmfHeroLoop[0]);

const signed short* const cmfMoveInfo[] = {
	c0mv, c1mv, c2mv, c3mv, c4mv, c5mv, c6mv, c7mv, c8mv, c9mv,
	c10mv, c11mv, c12mv, c13mv, c14mv, c15mv, c16mv, c17mv, c18mv, c19mv,
	c20mv, c21mv, c22mv, c23mv, c24mv, c25mv, c26mv, c27mv, c28mv, c29mv,
	c30mv, c31mv, c32mv, c33mv, c34mv, c35mv, c36mv, c37mv, c38mv, c39mv,
	c40mv, c41mv, c42mv, c43mv, c44mv, c45mv, c46mv, c47mv, c48mv, c49mv,
	c50mv, c51mv, c52mv, c53mv, c54mv, c55mv, c56mv, c57mv, c58mv, c59mv,
	c60mv, c61mv, c62mv, c63mv, c64mv, c65mv, c66mv, c67mv, c68mv, c69mv,
	c70mv, c71mv, c72mv, c73mv, c74mv, c75mv, c76mv, c77mv, c78mv, c79mv,
	c80mv, c81mv, c82mv, c83mv, c84mv, c85mv, c86mv, c87mv, c88mv, c89mv,
	c90mv, c91mv, c92mv, c93mv, c94mv, c95mv, c96mv, c97mv, c98mv, c99mv,
	c100mv, c101mv, c102mv, c103mv, c104mv, c105mv, c106mv, c107mv, c108mv, c109mv,
	c110mv, c111mv, c112mv, c113mv, c114mv, c115mv, c116mv, c117mv, c118mv, c119mv,
	c120mv, c121mv, c122mv,

	c3mv, c3mv, c3mv, c3mv, c3mv, c3mv,
	c4mv, c4mv, c4mv, c4mv, c4mv, c4mv,
	c5mv, c5mv, c5mv, c5mv, c5mv, c5mv,
	c6mv, c6mv, c6mv, c6mv, c6mv, c6mv,
	c7mv, c7mv, c7mv, c7mv, c7mv, c7mv,
	c8mv, c8mv, c8mv, c8mv, c8mv, c8mv,
	c9mv, c9mv, c9mv, c9mv, c9mv, c9mv,
	c10mv, c10mv, c10mv, c10mv, c10mv, c10mv,
	c11mv, c11mv, c11mv, c11mv, c11mv, c11mv,
	c12mv, c12mv, c12mv, c12mv, c12mv, c12mv,
	c13mv, c13mv, c13mv, c13mv, c13mv, c13mv,
	c14mv, c14mv, c14mv, c14mv, c14mv, c14mv,
	c15mv, c15mv, c15mv, c15mv, c15mv, c15mv,
	c16mv, c16mv, c16mv, c16mv, c16mv, c16mv,
	c17mv, c17mv, c17mv, c17mv, c17mv, c17mv,
	c18mv, c18mv, c18mv, c18mv, c18mv, c18mv,
	c19mv, c19mv, c19mv, c19mv, c19mv, c19mv,
	c20mv, c20mv, c20mv, c20mv, c20mv, c20mv,
	c21mv, c21mv, c21mv, c21mv, c21mv, c21mv,
	c22mv, c22mv, c22mv, c22mv, c22mv, c22mv,
	c23mv, c23mv, c23mv, c23mv, c23mv, c23mv,
	c24mv, c24mv, c24mv, c24mv, c24mv, c24mv,
	c25mv, c25mv, c25mv, c25mv, c25mv, c25mv,
	c26mv, c26mv, c26mv, c26mv, c26mv, c26mv,
	c27mv, c27mv, c27mv, c27mv, c27mv, c27mv,
	c28mv, c28mv, c28mv, c28mv, c28mv, c28mv,
	c29mv, c29mv, c29mv, c29mv, c29mv, c29mv,
	c30mv, c30mv, c30mv, c30mv, c30mv, c30mv,
	c31mv, c31mv, c31mv, c31mv, c31mv, c31mv,
	c32mv, c32mv, c32mv, c32mv, c32mv, c32mv,
	c33mv, c33mv, c33mv, c33mv, c33mv, c33mv,
	c34mv, c34mv, c34mv, c34mv, c34mv, c34mv,
	c35mv, c35mv, c35mv, c35mv, c35mv, c35mv,
	c36mv, c36mv, c36mv, c36mv, c36mv, c36mv,
	c37mv, c37mv, c37mv, c37mv, c37mv, c37mv,
	c38mv, c38mv, c38mv, c38mv, c38mv, c38mv,
	c39mv, c39mv, c39mv, c39mv, c39mv, c39mv,
	c40mv, c40mv, c40mv, c40mv, c40mv, c40mv,
	c41mv, c41mv, c41mv, c41mv, c41mv, c41mv,
	c42mv, c42mv, c42mv, c42mv, c42mv, c42mv,
	c43mv, c43mv, c43mv, c43mv, c43mv, c43mv,
	c44mv, c44mv, c44mv, c44mv, c44mv, c44mv,
	c45mv, c45mv, c45mv, c45mv, c45mv, c45mv,
	c46mv, c46mv, c46mv, c46mv, c46mv, c46mv,
	c47mv, c47mv, c47mv, c47mv, c47mv, c47mv,
	c48mv, c48mv, c48mv, c48mv, c48mv, c48mv,
	c49mv, c49mv, c49mv, c49mv, c49mv, c49mv,
	c50mv, c50mv, c50mv, c50mv, c50mv, c50mv,
	c51mv, c51mv, c51mv, c51mv, c51mv, c51mv,
	c109mv, c109mv, c109mv, c109mv, c109mv, c109mv,
	c110mv, c110mv, c110mv, c110mv, c110mv, c110mv,
};

const unsigned short cmfTotalMotion[] = {
	TOTALC0MOTION, TOTALC1MOTION, TOTALC2MOTION, TOTALC3MOTION, TOTALC4MOTION, TOTALC5MOTION, TOTALC6MOTION, TOTALC7MOTION, TOTALC8MOTION, TOTALC9MOTION,
	TOTALC10MOTION, TOTALC11MOTION, TOTALC12MOTION, TOTALC13MOTION, TOTALC14MOTION, TOTALC15MOTION, TOTALC16MOTION, TOTALC17MOTION, TOTALC18MOTION, TOTALC19MOTION,
	TOTALC20MOTION, TOTALC21MOTION, TOTALC22MOTION, TOTALC23MOTION, TOTALC24MOTION, TOTALC25MOTION, TOTALC26MOTION, TOTALC27MOTION, TOTALC28MOTION, TOTALC29MOTION,
	TOTALC30MOTION, TOTALC31MOTION, TOTALC32MOTION, TOTALC33MOTION, TOTALC34MOTION, TOTALC35MOTION, TOTALC36MOTION, TOTALC37MOTION, TOTALC38MOTION, TOTALC39MOTION,
	TOTALC40MOTION, TOTALC41MOTION, TOTALC42MOTION, TOTALC43MOTION, TOTALC44MOTION, TOTALC45MOTION, TOTALC46MOTION, TOTALC47MOTION, TOTALC48MOTION, TOTALC49MOTION,
	TOTALC50MOTION, TOTALC51MOTION, TOTALC52MOTION, TOTALC53MOTION, TOTALC54MOTION, TOTALC55MOTION, TOTALC56MOTION, TOTALC57MOTION, TOTALC58MOTION, TOTALC59MOTION,
	TOTALC60MOTION, TOTALC61MOTION, TOTALC62MOTION, TOTALC63MOTION, TOTALC64MOTION, TOTALC65MOTION, TOTALC66MOTION, TOTALC67MOTION, TOTALC68MOTION, TOTALC69MOTION,
	TOTALC70MOTION, TOTALC71MOTION, TOTALC72MOTION, TOTALC73MOTION, TOTALC74MOTION, TOTALC75MOTION, TOTALC76MOTION, TOTALC77MOTION, TOTALC78MOTION, TOTALC79MOTION,
	TOTALC80MOTION, TOTALC81MOTION, TOTALC82MOTION, TOTALC83MOTION, TOTALC84MOTION, TOTALC85MOTION, TOTALC86MOTION, TOTALC87MOTION, TOTALC88MOTION, TOTALC89MOTION,
	TOTALC90MOTION, TOTALC91MOTION, TOTALC92MOTION, TOTALC93MOTION, TOTALC94MOTION, TOTALC95MOTION, TOTALC96MOTION, TOTALC97MOTION, TOTALC98MOTION, TOTALC99MOTION,
	TOTALC100MOTION, TOTALC101MOTION, TOTALC102MOTION, TOTALC103MOTION, TOTALC104MOTION, TOTALC105MOTION, TOTALC106MOTION, TOTALC107MOTION, TOTALC108MOTION, TOTALC109MOTION,
	TOTALC110MOTION, TOTALC111MOTION, TOTALC112MOTION, TOTALC113MOTION, TOTALC114MOTION, TOTALC115MOTION, TOTALC116MOTION, TOTALC117MOTION, TOTALC118MOTION, TOTALC119MOTION,
	TOTALC120MOTION, TOTALC121MOTION, TOTALC122MOTION,

	TOTALC3MOTION, TOTALC3MOTION, TOTALC3MOTION, TOTALC3MOTION, TOTALC3MOTION, TOTALC3MOTION,
	TOTALC4MOTION, TOTALC4MOTION, TOTALC4MOTION, TOTALC4MOTION, TOTALC4MOTION, TOTALC4MOTION,
	TOTALC5MOTION, TOTALC5MOTION, TOTALC5MOTION, TOTALC5MOTION, TOTALC5MOTION, TOTALC5MOTION,
	TOTALC6MOTION, TOTALC6MOTION, TOTALC6MOTION, TOTALC6MOTION, TOTALC6MOTION, TOTALC6MOTION,
	TOTALC7MOTION, TOTALC7MOTION, TOTALC7MOTION, TOTALC7MOTION, TOTALC7MOTION, TOTALC7MOTION,
	TOTALC8MOTION, TOTALC8MOTION, TOTALC8MOTION, TOTALC8MOTION, TOTALC8MOTION, TOTALC8MOTION,
	TOTALC9MOTION, TOTALC9MOTION, TOTALC9MOTION, TOTALC9MOTION, TOTALC9MOTION, TOTALC9MOTION,
	TOTALC10MOTION, TOTALC10MOTION, TOTALC10MOTION, TOTALC10MOTION, TOTALC10MOTION, TOTALC10MOTION,
	TOTALC11MOTION, TOTALC11MOTION, TOTALC11MOTION, TOTALC11MOTION, TOTALC11MOTION, TOTALC11MOTION,
	TOTALC12MOTION, TOTALC12MOTION, TOTALC12MOTION, TOTALC12MOTION, TOTALC12MOTION, TOTALC12MOTION,
	TOTALC13MOTION, TOTALC13MOTION, TOTALC13MOTION, TOTALC13MOTION, TOTALC13MOTION, TOTALC13MOTION,
	TOTALC14MOTION, TOTALC14MOTION, TOTALC14MOTION, TOTALC14MOTION, TOTALC14MOTION, TOTALC14MOTION,
	TOTALC15MOTION, TOTALC15MOTION, TOTALC15MOTION, TOTALC15MOTION, TOTALC15MOTION, TOTALC15MOTION,
	TOTALC16MOTION, TOTALC16MOTION, TOTALC16MOTION, TOTALC16MOTION, TOTALC16MOTION, TOTALC16MOTION,
	TOTALC17MOTION, TOTALC17MOTION, TOTALC17MOTION, TOTALC17MOTION, TOTALC17MOTION, TOTALC17MOTION,
	TOTALC18MOTION, TOTALC18MOTION, TOTALC18MOTION, TOTALC18MOTION, TOTALC18MOTION, TOTALC18MOTION,
	TOTALC19MOTION, TOTALC19MOTION, TOTALC19MOTION, TOTALC19MOTION, TOTALC19MOTION, TOTALC19MOTION,
	TOTALC20MOTION, TOTALC20MOTION, TOTALC20MOTION, TOTALC20MOTION, TOTALC20MOTION, TOTALC20MOTION,
	TOTALC21MOTION, TOTALC21MOTION, TOTALC21MOTION, TOTALC21MOTION, TOTALC21MOTION, TOTALC21MOTION,
	TOTALC22MOTION, TOTALC22MOTION, TOTALC22MOTION, TOTALC22MOTION, TOTALC22MOTION, TOTALC22MOTION,
	TOTALC23MOTION, TOTALC23MOTION, TOTALC23MOTION, TOTALC23MOTION, TOTALC23MOTION, TOTALC23MOTION,
	TOTALC24MOTION, TOTALC24MOTION, TOTALC24MOTION, TOTALC24MOTION, TOTALC24MOTION, TOTALC24MOTION,
	TOTALC25MOTION, TOTALC25MOTION, TOTALC25MOTION, TOTALC25MOTION, TOTALC25MOTION, TOTALC25MOTION,
	TOTALC26MOTION, TOTALC26MOTION, TOTALC26MOTION, TOTALC26MOTION, TOTALC26MOTION, TOTALC26MOTION,
	TOTALC27MOTION, TOTALC27MOTION, TOTALC27MOTION, TOTALC27MOTION, TOTALC27MOTION, TOTALC27MOTION,
	TOTALC28MOTION, TOTALC28MOTION, TOTALC28MOTION, TOTALC28MOTION, TOTALC28MOTION, TOTALC28MOTION,
	TOTALC29MOTION, TOTALC29MOTION, TOTALC29MOTION, TOTALC29MOTION, TOTALC29MOTION, TOTALC29MOTION,
	TOTALC30MOTION, TOTALC30MOTION, TOTALC30MOTION, TOTALC30MOTION, TOTALC30MOTION, TOTALC30MOTION,
	TOTALC31MOTION, TOTALC31MOTION, TOTALC31MOTION, TOTALC31MOTION, TOTALC31MOTION, TOTALC31MOTION,
	TOTALC32MOTION, TOTALC32MOTION, TOTALC32MOTION, TOTALC32MOTION, TOTALC32MOTION, TOTALC32MOTION,
	TOTALC33MOTION, TOTALC33MOTION, TOTALC33MOTION, TOTALC33MOTION, TOTALC33MOTION, TOTALC33MOTION,
	TOTALC34MOTION, TOTALC34MOTION, TOTALC34MOTION, TOTALC34MOTION, TOTALC34MOTION, TOTALC34MOTION,
	TOTALC35MOTION, TOTALC35MOTION, TOTALC35MOTION, TOTALC35MOTION, TOTALC35MOTION, TOTALC35MOTION,
	TOTALC36MOTION, TOTALC36MOTION, TOTALC36MOTION, TOTALC36MOTION, TOTALC36MOTION, TOTALC36MOTION,
	TOTALC37MOTION, TOTALC37MOTION, TOTALC37MOTION, TOTALC37MOTION, TOTALC37MOTION, TOTALC37MOTION,
	TOTALC38MOTION, TOTALC38MOTION, TOTALC38MOTION, TOTALC38MOTION, TOTALC38MOTION, TOTALC38MOTION,
	TOTALC39MOTION, TOTALC39MOTION, TOTALC39MOTION, TOTALC39MOTION, TOTALC39MOTION, TOTALC39MOTION,
	TOTALC40MOTION, TOTALC40MOTION, TOTALC40MOTION, TOTALC40MOTION, TOTALC40MOTION, TOTALC40MOTION,
	TOTALC41MOTION, TOTALC41MOTION, TOTALC41MOTION, TOTALC41MOTION, TOTALC41MOTION, TOTALC41MOTION,
	TOTALC42MOTION, TOTALC42MOTION, TOTALC42MOTION, TOTALC42MOTION, TOTALC42MOTION, TOTALC42MOTION,
	TOTALC43MOTION, TOTALC43MOTION, TOTALC43MOTION, TOTALC43MOTION, TOTALC43MOTION, TOTALC43MOTION,
	TOTALC44MOTION, TOTALC44MOTION, TOTALC44MOTION, TOTALC44MOTION, TOTALC44MOTION, TOTALC44MOTION,
	TOTALC45MOTION, TOTALC45MOTION, TOTALC45MOTION, TOTALC45MOTION, TOTALC45MOTION, TOTALC45MOTION,
	TOTALC46MOTION, TOTALC46MOTION, TOTALC46MOTION, TOTALC46MOTION, TOTALC46MOTION, TOTALC46MOTION,
	TOTALC47MOTION, TOTALC47MOTION, TOTALC47MOTION, TOTALC47MOTION, TOTALC47MOTION, TOTALC47MOTION,
	TOTALC48MOTION, TOTALC48MOTION, TOTALC48MOTION, TOTALC48MOTION, TOTALC48MOTION, TOTALC48MOTION,
	TOTALC49MOTION, TOTALC49MOTION, TOTALC49MOTION, TOTALC49MOTION, TOTALC49MOTION, TOTALC49MOTION,
	TOTALC50MOTION, TOTALC50MOTION, TOTALC50MOTION, TOTALC50MOTION, TOTALC50MOTION, TOTALC50MOTION,
	TOTALC51MOTION, TOTALC51MOTION, TOTALC51MOTION, TOTALC51MOTION, TOTALC51MOTION, TOTALC51MOTION,
	TOTALC109MOTION, TOTALC109MOTION, TOTALC109MOTION, TOTALC109MOTION, TOTALC109MOTION, TOTALC109MOTION,
	TOTALC110MOTION, TOTALC110MOTION, TOTALC110MOTION, TOTALC110MOTION, TOTALC110MOTION, TOTALC110MOTION,
};

const unsigned short cmfTotalOff[] = {
	TOTALC0OFF, TOTALC1OFF, TOTALC2OFF, TOTALC3OFF, TOTALC4OFF, TOTALC5OFF, TOTALC6OFF, TOTALC7OFF, TOTALC8OFF, TOTALC9OFF,
	TOTALC10OFF, TOTALC11OFF, TOTALC12OFF, TOTALC13OFF, TOTALC14OFF, TOTALC15OFF, TOTALC16OFF, TOTALC17OFF, TOTALC18OFF, TOTALC19OFF,
	TOTALC20OFF, TOTALC21OFF, TOTALC22OFF, TOTALC23OFF, TOTALC24OFF, TOTALC25OFF, TOTALC26OFF, TOTALC27OFF, TOTALC28OFF, TOTALC29OFF,
	TOTALC30OFF, TOTALC31OFF, TOTALC32OFF, TOTALC33OFF, TOTALC34OFF, TOTALC35OFF, TOTALC36OFF, TOTALC37OFF, TOTALC38OFF, TOTALC39OFF,
	TOTALC40OFF, TOTALC41OFF, TOTALC42OFF, TOTALC43OFF, TOTALC44OFF, TOTALC45OFF, TOTALC46OFF, TOTALC47OFF, TOTALC48OFF, TOTALC49OFF,
	TOTALC50OFF, TOTALC51OFF, TOTALC52OFF, TOTALC53OFF, TOTALC54OFF, TOTALC55OFF, TOTALC56OFF, TOTALC57OFF, TOTALC58OFF, TOTALC59OFF,
	TOTALC60OFF, TOTALC61OFF, TOTALC62OFF, TOTALC63OFF, TOTALC64OFF, TOTALC65OFF, TOTALC66OFF, TOTALC67OFF, TOTALC68OFF, TOTALC69OFF,
	TOTALC70OFF, TOTALC71OFF, TOTALC72OFF, TOTALC73OFF, TOTALC74OFF, TOTALC75OFF, TOTALC76OFF, TOTALC77OFF, TOTALC78OFF, TOTALC79OFF,
	TOTALC80OFF, TOTALC81OFF, TOTALC82OFF, TOTALC83OFF, TOTALC84OFF, TOTALC85OFF, TOTALC86OFF, TOTALC87OFF, TOTALC88OFF, TOTALC89OFF,
	TOTALC90OFF, TOTALC91OFF, TOTALC92OFF, TOTALC93OFF, TOTALC94OFF, TOTALC95OFF, TOTALC96OFF, TOTALC97OFF, TOTALC98OFF, TOTALC99OFF,
	TOTALC100OFF, TOTALC101OFF, TOTALC102OFF, TOTALC103OFF, TOTALC104OFF, TOTALC105OFF, TOTALC106OFF, TOTALC107OFF, TOTALC108OFF, TOTALC109OFF,
	TOTALC110OFF, TOTALC111OFF, TOTALC112OFF, TOTALC113OFF, TOTALC114OFF, TOTALC115OFF, TOTALC116OFF, TOTALC117OFF, TOTALC118OFF, TOTALC119OFF,
	TOTALC120OFF, TOTALC121OFF, TOTALC122OFF,

	TOTALC3OFF, TOTALC3OFF, TOTALC3OFF, TOTALC3OFF, TOTALC3OFF, TOTALC3OFF,
	TOTALC4OFF, TOTALC4OFF, TOTALC4OFF, TOTALC4OFF, TOTALC4OFF, TOTALC4OFF,
	TOTALC5OFF, TOTALC5OFF, TOTALC5OFF, TOTALC5OFF, TOTALC5OFF, TOTALC5OFF,
	TOTALC6OFF, TOTALC6OFF, TOTALC6OFF, TOTALC6OFF, TOTALC6OFF, TOTALC6OFF,
	TOTALC7OFF, TOTALC7OFF, TOTALC7OFF, TOTALC7OFF, TOTALC7OFF, TOTALC7OFF,
	TOTALC8OFF, TOTALC8OFF, TOTALC8OFF, TOTALC8OFF, TOTALC8OFF, TOTALC8OFF,
	TOTALC9OFF, TOTALC9OFF, TOTALC9OFF, TOTALC9OFF, TOTALC9OFF, TOTALC9OFF,
	TOTALC10OFF, TOTALC10OFF, TOTALC10OFF, TOTALC10OFF, TOTALC10OFF, TOTALC10OFF,
	TOTALC11OFF, TOTALC11OFF, TOTALC11OFF, TOTALC11OFF, TOTALC11OFF, TOTALC11OFF,
	TOTALC12OFF, TOTALC12OFF, TOTALC12OFF, TOTALC12OFF, TOTALC12OFF, TOTALC12OFF,
	TOTALC13OFF, TOTALC13OFF, TOTALC13OFF, TOTALC13OFF, TOTALC13OFF, TOTALC13OFF,
	TOTALC14OFF, TOTALC14OFF, TOTALC14OFF, TOTALC14OFF, TOTALC14OFF, TOTALC14OFF,
	TOTALC15OFF, TOTALC15OFF, TOTALC15OFF, TOTALC15OFF, TOTALC15OFF, TOTALC15OFF,
	TOTALC16OFF, TOTALC16OFF, TOTALC16OFF, TOTALC16OFF, TOTALC16OFF, TOTALC16OFF,
	TOTALC17OFF, TOTALC17OFF, TOTALC17OFF, TOTALC17OFF, TOTALC17OFF, TOTALC17OFF,
	TOTALC18OFF, TOTALC18OFF, TOTALC18OFF, TOTALC18OFF, TOTALC18OFF, TOTALC18OFF,
	TOTALC19OFF, TOTALC19OFF, TOTALC19OFF, TOTALC19OFF, TOTALC19OFF, TOTALC19OFF,
	TOTALC20OFF, TOTALC20OFF, TOTALC20OFF, TOTALC20OFF, TOTALC20OFF, TOTALC20OFF,
	TOTALC21OFF, TOTALC21OFF, TOTALC21OFF, TOTALC21OFF, TOTALC21OFF, TOTALC21OFF,
	TOTALC22OFF, TOTALC22OFF, TOTALC22OFF, TOTALC22OFF, TOTALC22OFF, TOTALC22OFF,
	TOTALC23OFF, TOTALC23OFF, TOTALC23OFF, TOTALC23OFF, TOTALC23OFF, TOTALC23OFF,
	TOTALC24OFF, TOTALC24OFF, TOTALC24OFF, TOTALC24OFF, TOTALC24OFF, TOTALC24OFF,
	TOTALC25OFF, TOTALC25OFF, TOTALC25OFF, TOTALC25OFF, TOTALC25OFF, TOTALC25OFF,
	TOTALC26OFF, TOTALC26OFF, TOTALC26OFF, TOTALC26OFF, TOTALC26OFF, TOTALC26OFF,
	TOTALC27OFF, TOTALC27OFF, TOTALC27OFF, TOTALC27OFF, TOTALC27OFF, TOTALC27OFF,
	TOTALC28OFF, TOTALC28OFF, TOTALC28OFF, TOTALC28OFF, TOTALC28OFF, TOTALC28OFF,
	TOTALC29OFF, TOTALC29OFF, TOTALC29OFF, TOTALC29OFF, TOTALC29OFF, TOTALC29OFF,
	TOTALC30OFF, TOTALC30OFF, TOTALC30OFF, TOTALC30OFF, TOTALC30OFF, TOTALC30OFF,
	TOTALC31OFF, TOTALC31OFF, TOTALC31OFF, TOTALC31OFF, TOTALC31OFF, TOTALC31OFF,
	TOTALC32OFF, TOTALC32OFF, TOTALC32OFF, TOTALC32OFF, TOTALC32OFF, TOTALC32OFF,
	TOTALC33OFF, TOTALC33OFF, TOTALC33OFF, TOTALC33OFF, TOTALC33OFF, TOTALC33OFF,
	TOTALC34OFF, TOTALC34OFF, TOTALC34OFF, TOTALC34OFF, TOTALC34OFF, TOTALC34OFF,
	TOTALC35OFF, TOTALC35OFF, TOTALC35OFF, TOTALC35OFF, TOTALC35OFF, TOTALC35OFF,
	TOTALC36OFF, TOTALC36OFF, TOTALC36OFF, TOTALC36OFF, TOTALC36OFF, TOTALC36OFF,
	TOTALC37OFF, TOTALC37OFF, TOTALC37OFF, TOTALC37OFF, TOTALC37OFF, TOTALC37OFF,
	TOTALC38OFF, TOTALC38OFF, TOTALC38OFF, TOTALC38OFF, TOTALC38OFF, TOTALC38OFF,
	TOTALC39OFF, TOTALC39OFF, TOTALC39OFF, TOTALC39OFF, TOTALC39OFF, TOTALC39OFF,
	TOTALC40OFF, TOTALC40OFF, TOTALC40OFF, TOTALC40OFF, TOTALC40OFF, TOTALC40OFF,
	TOTALC41OFF, TOTALC41OFF, TOTALC41OFF, TOTALC41OFF, TOTALC41OFF, TOTALC41OFF,
	TOTALC42OFF, TOTALC42OFF, TOTALC42OFF, TOTALC42OFF, TOTALC42OFF, TOTALC42OFF,
	TOTALC43OFF, TOTALC43OFF, TOTALC43OFF, TOTALC43OFF, TOTALC43OFF, TOTALC43OFF,
	TOTALC44OFF, TOTALC44OFF, TOTALC44OFF, TOTALC44OFF, TOTALC44OFF, TOTALC44OFF,
	TOTALC45OFF, TOTALC45OFF, TOTALC45OFF, TOTALC45OFF, TOTALC45OFF, TOTALC45OFF,
	TOTALC46OFF, TOTALC46OFF, TOTALC46OFF, TOTALC46OFF, TOTALC46OFF, TOTALC46OFF,
	TOTALC47OFF, TOTALC47OFF, TOTALC47OFF, TOTALC47OFF, TOTALC47OFF, TOTALC47OFF,
	TOTALC48OFF, TOTALC48OFF, TOTALC48OFF, TOTALC48OFF, TOTALC48OFF, TOTALC48OFF,
	TOTALC49OFF, TOTALC49OFF, TOTALC49OFF, TOTALC49OFF, TOTALC49OFF, TOTALC49OFF,
	TOTALC50OFF, TOTALC50OFF, TOTALC50OFF, TOTALC50OFF, TOTALC50OFF, TOTALC50OFF,
	TOTALC51OFF, TOTALC51OFF, TOTALC51OFF, TOTALC51OFF, TOTALC51OFF, TOTALC51OFF,
	TOTALC109OFF, TOTALC109OFF, TOTALC109OFF, TOTALC109OFF, TOTALC109OFF, TOTALC109OFF,
	TOTALC110OFF, TOTALC110OFF, TOTALC110OFF, TOTALC110OFF, TOTALC110OFF, TOTALC110OFF,
};

const unsigned short cmfVar[] = {
	sizeof(c0MI) / 4, sizeof(c1MI) / 4, sizeof(c2MI) / 4, sizeof(c3MI) / 4, sizeof(c4MI) / 4, sizeof(c5MI) / 4, sizeof(c6MI) / 4, sizeof(c7MI) / 4, sizeof(c8MI) / 4, sizeof(c9MI) / 4,
	sizeof(c10MI) / 4, sizeof(c11MI) / 4, sizeof(c12MI) / 4, sizeof(c13MI) / 4, sizeof(c14MI) / 4, sizeof(c15MI) / 4, sizeof(c16MI) / 4, sizeof(c17MI) / 4, sizeof(c18MI) / 4, sizeof(c19MI) / 4,
	sizeof(c20MI) / 4, sizeof(c21MI) / 4, sizeof(c22MI) / 4, sizeof(c23MI) / 4, sizeof(c24MI) / 4, sizeof(c25MI) / 4, sizeof(c26MI) / 4, sizeof(c27MI) / 4, sizeof(c28MI) / 4, sizeof(c29MI) / 4,
	sizeof(c30MI) / 4, sizeof(c31MI) / 4, sizeof(c32MI) / 4, sizeof(c33MI) / 4, sizeof(c34MI) / 4, sizeof(c35MI) / 4, sizeof(c36MI) / 4, sizeof(c37MI) / 4, sizeof(c38MI) / 4, sizeof(c39MI) / 4,
	sizeof(c40MI) / 4, sizeof(c41MI) / 4, sizeof(c42MI) / 4, sizeof(c43MI) / 4, sizeof(c44MI) / 4, sizeof(c45MI) / 4, sizeof(c46MI) / 4, sizeof(c47MI) / 4, sizeof(c48MI) / 4, sizeof(c49MI) / 4,
	sizeof(c50MI) / 4, sizeof(c51MI) / 4, sizeof(c52MI) / 4, sizeof(c53MI) / 4, sizeof(c54MI) / 4, sizeof(c55MI) / 4, sizeof(c56MI) / 4, sizeof(c57MI) / 4, sizeof(c58MI) / 4, sizeof(c59MI) / 4,
	sizeof(c60MI) / 4, sizeof(c61MI) / 4, sizeof(c62MI) / 4, sizeof(c63MI) / 4, sizeof(c64MI) / 4, sizeof(c65MI) / 4, sizeof(c66MI) / 4, sizeof(c67MI) / 4, sizeof(c68MI) / 4, sizeof(c69MI) / 4,
	sizeof(c70MI) / 4, sizeof(c71MI) / 4, sizeof(c72MI) / 4, sizeof(c73MI) / 4, sizeof(c74MI) / 4, sizeof(c75MI) / 4, sizeof(c76MI) / 4, sizeof(c77MI) / 4, sizeof(c78MI) / 4, sizeof(c79MI) / 4,
	sizeof(c80MI) / 4, sizeof(c81MI) / 4, sizeof(c82MI) / 4, sizeof(c83MI) / 4, sizeof(c84MI) / 4, sizeof(c85MI) / 4, sizeof(c86MI) / 4, sizeof(c87MI) / 4, sizeof(c88MI) / 4, sizeof(c89MI) / 4,
	sizeof(c90MI) / 4, sizeof(c91MI) / 4, sizeof(c92MI) / 4, sizeof(c93MI) / 4, sizeof(c94MI) / 4, sizeof(c95MI) / 4, sizeof(c96MI) / 4, sizeof(c97MI) / 4, sizeof(c98MI) / 4, sizeof(c99MI) / 4,
	sizeof(c100MI) / 4, sizeof(c101MI) / 4, sizeof(c102MI) / 4, sizeof(c103MI) / 4, sizeof(c104MI) / 4, sizeof(c105MI) / 4, sizeof(c106MI) / 4, sizeof(c107MI) / 4, sizeof(c108MI) / 4, sizeof(c109MI) / 4,
	sizeof(c110MI) / 4, sizeof(c111MI) / 4, sizeof(c112MI) / 4, sizeof(c113MI) / 4, sizeof(c114MI) / 4, sizeof(c115MI) / 4, sizeof(c116MI) / 4, sizeof(c117MI) / 4, sizeof(c118MI) / 4, sizeof(c119MI) / 4,
	sizeof(c120MI) / 4, sizeof(c121MI) / 4, sizeof(c122MI) / 4,

	sizeof(c3MI) / 4, sizeof(c3MI) / 4, sizeof(c3MI) / 4, sizeof(c3MI) / 4, sizeof(c3MI) / 4, sizeof(c3MI) / 4,
	sizeof(c4MI) / 4, sizeof(c4MI) / 4, sizeof(c4MI) / 4, sizeof(c4MI) / 4, sizeof(c4MI) / 4, sizeof(c4MI) / 4,
	sizeof(c5MI) / 4, sizeof(c5MI) / 4, sizeof(c5MI) / 4, sizeof(c5MI) / 4, sizeof(c5MI) / 4, sizeof(c5MI) / 4,
	sizeof(c6MI) / 4, sizeof(c6MI) / 4, sizeof(c6MI) / 4, sizeof(c6MI) / 4, sizeof(c6MI) / 4, sizeof(c6MI) / 4,
	sizeof(c7MI) / 4, sizeof(c7MI) / 4, sizeof(c7MI) / 4, sizeof(c7MI) / 4, sizeof(c7MI) / 4, sizeof(c7MI) / 4,
	sizeof(c8MI) / 4, sizeof(c8MI) / 4, sizeof(c8MI) / 4, sizeof(c8MI) / 4, sizeof(c8MI) / 4, sizeof(c8MI) / 4,
	sizeof(c9MI) / 4, sizeof(c9MI) / 4, sizeof(c9MI) / 4, sizeof(c9MI) / 4, sizeof(c9MI) / 4, sizeof(c9MI) / 4,
	sizeof(c10MI) / 4, sizeof(c10MI) / 4, sizeof(c10MI) / 4, sizeof(c10MI) / 4, sizeof(c10MI) / 4, sizeof(c10MI) / 4,
	sizeof(c11MI) / 4, sizeof(c11MI) / 4, sizeof(c11MI) / 4, sizeof(c11MI) / 4, sizeof(c11MI) / 4, sizeof(c11MI) / 4,
	sizeof(c12MI) / 4, sizeof(c12MI) / 4, sizeof(c12MI) / 4, sizeof(c12MI) / 4, sizeof(c12MI) / 4, sizeof(c12MI) / 4,
	sizeof(c13MI) / 4, sizeof(c13MI) / 4, sizeof(c13MI) / 4, sizeof(c13MI) / 4, sizeof(c13MI) / 4, sizeof(c13MI) / 4,
	sizeof(c14MI) / 4, sizeof(c14MI) / 4, sizeof(c14MI) / 4, sizeof(c14MI) / 4, sizeof(c14MI) / 4, sizeof(c14MI) / 4,
	sizeof(c15MI) / 4, sizeof(c15MI) / 4, sizeof(c15MI) / 4, sizeof(c15MI) / 4, sizeof(c15MI) / 4, sizeof(c15MI) / 4,
	sizeof(c16MI) / 4, sizeof(c16MI) / 4, sizeof(c16MI) / 4, sizeof(c16MI) / 4, sizeof(c16MI) / 4, sizeof(c16MI) / 4,
	sizeof(c17MI) / 4, sizeof(c17MI) / 4, sizeof(c17MI) / 4, sizeof(c17MI) / 4, sizeof(c17MI) / 4, sizeof(c17MI) / 4,
	sizeof(c18MI) / 4, sizeof(c18MI) / 4, sizeof(c18MI) / 4, sizeof(c18MI) / 4, sizeof(c18MI) / 4, sizeof(c18MI) / 4,
	sizeof(c19MI) / 4, sizeof(c19MI) / 4, sizeof(c19MI) / 4, sizeof(c19MI) / 4, sizeof(c19MI) / 4, sizeof(c19MI) / 4,
	sizeof(c20MI) / 4, sizeof(c20MI) / 4, sizeof(c20MI) / 4, sizeof(c20MI) / 4, sizeof(c20MI) / 4, sizeof(c20MI) / 4,
	sizeof(c21MI) / 4, sizeof(c21MI) / 4, sizeof(c21MI) / 4, sizeof(c21MI) / 4, sizeof(c21MI) / 4, sizeof(c21MI) / 4,
	sizeof(c22MI) / 4, sizeof(c22MI) / 4, sizeof(c22MI) / 4, sizeof(c22MI) / 4, sizeof(c22MI) / 4, sizeof(c22MI) / 4,
	sizeof(c23MI) / 4, sizeof(c23MI) / 4, sizeof(c23MI) / 4, sizeof(c23MI) / 4, sizeof(c23MI) / 4, sizeof(c23MI) / 4,
	sizeof(c24MI) / 4, sizeof(c24MI) / 4, sizeof(c24MI) / 4, sizeof(c24MI) / 4, sizeof(c24MI) / 4, sizeof(c24MI) / 4,
	sizeof(c25MI) / 4, sizeof(c25MI) / 4, sizeof(c25MI) / 4, sizeof(c25MI) / 4, sizeof(c25MI) / 4, sizeof(c25MI) / 4,
	sizeof(c26MI) / 4, sizeof(c26MI) / 4, sizeof(c26MI) / 4, sizeof(c26MI) / 4, sizeof(c26MI) / 4, sizeof(c26MI) / 4,
	sizeof(c27MI) / 4, sizeof(c27MI) / 4, sizeof(c27MI) / 4, sizeof(c27MI) / 4, sizeof(c27MI) / 4, sizeof(c27MI) / 4,
	sizeof(c28MI) / 4, sizeof(c28MI) / 4, sizeof(c28MI) / 4, sizeof(c28MI) / 4, sizeof(c28MI) / 4, sizeof(c28MI) / 4,
	sizeof(c29MI) / 4, sizeof(c29MI) / 4, sizeof(c29MI) / 4, sizeof(c29MI) / 4, sizeof(c29MI) / 4, sizeof(c29MI) / 4,
	sizeof(c30MI) / 4, sizeof(c30MI) / 4, sizeof(c30MI) / 4, sizeof(c30MI) / 4, sizeof(c30MI) / 4, sizeof(c30MI) / 4,
	sizeof(c31MI) / 4, sizeof(c31MI) / 4, sizeof(c31MI) / 4, sizeof(c31MI) / 4, sizeof(c31MI) / 4, sizeof(c31MI) / 4,
	sizeof(c32MI) / 4, sizeof(c32MI) / 4, sizeof(c32MI) / 4, sizeof(c32MI) / 4, sizeof(c32MI) / 4, sizeof(c32MI) / 4,
	sizeof(c33MI) / 4, sizeof(c33MI) / 4, sizeof(c33MI) / 4, sizeof(c33MI) / 4, sizeof(c33MI) / 4, sizeof(c33MI) / 4,
	sizeof(c34MI) / 4, sizeof(c34MI) / 4, sizeof(c34MI) / 4, sizeof(c34MI) / 4, sizeof(c34MI) / 4, sizeof(c34MI) / 4,
	sizeof(c35MI) / 4, sizeof(c35MI) / 4, sizeof(c35MI) / 4, sizeof(c35MI) / 4, sizeof(c35MI) / 4, sizeof(c35MI) / 4,
	sizeof(c36MI) / 4, sizeof(c36MI) / 4, sizeof(c36MI) / 4, sizeof(c36MI) / 4, sizeof(c36MI) / 4, sizeof(c36MI) / 4,
	sizeof(c37MI) / 4, sizeof(c37MI) / 4, sizeof(c37MI) / 4, sizeof(c37MI) / 4, sizeof(c37MI) / 4, sizeof(c37MI) / 4,
	sizeof(c38MI) / 4, sizeof(c38MI) / 4, sizeof(c38MI) / 4, sizeof(c38MI) / 4, sizeof(c38MI) / 4, sizeof(c38MI) / 4,
	sizeof(c39MI) / 4, sizeof(c39MI) / 4, sizeof(c39MI) / 4, sizeof(c39MI) / 4, sizeof(c39MI) / 4, sizeof(c39MI) / 4,
	sizeof(c40MI) / 4, sizeof(c40MI) / 4, sizeof(c40MI) / 4, sizeof(c40MI) / 4, sizeof(c40MI) / 4, sizeof(c40MI) / 4,
	sizeof(c41MI) / 4, sizeof(c41MI) / 4, sizeof(c41MI) / 4, sizeof(c41MI) / 4, sizeof(c41MI) / 4, sizeof(c41MI) / 4,
	sizeof(c42MI) / 4, sizeof(c42MI) / 4, sizeof(c42MI) / 4, sizeof(c42MI) / 4, sizeof(c42MI) / 4, sizeof(c42MI) / 4,
	sizeof(c43MI) / 4, sizeof(c43MI) / 4, sizeof(c43MI) / 4, sizeof(c43MI) / 4, sizeof(c43MI) / 4, sizeof(c43MI) / 4,
	sizeof(c44MI) / 4, sizeof(c44MI) / 4, sizeof(c44MI) / 4, sizeof(c44MI) / 4, sizeof(c44MI) / 4, sizeof(c44MI) / 4,
	sizeof(c45MI) / 4, sizeof(c45MI) / 4, sizeof(c45MI) / 4, sizeof(c45MI) / 4, sizeof(c45MI) / 4, sizeof(c45MI) / 4,
	sizeof(c46MI) / 4, sizeof(c46MI) / 4, sizeof(c46MI) / 4, sizeof(c46MI) / 4, sizeof(c46MI) / 4, sizeof(c46MI) / 4,
	sizeof(c47MI) / 4, sizeof(c47MI) / 4, sizeof(c47MI) / 4, sizeof(c47MI) / 4, sizeof(c47MI) / 4, sizeof(c47MI) / 4,
	sizeof(c48MI) / 4, sizeof(c48MI) / 4, sizeof(c48MI) / 4, sizeof(c48MI) / 4, sizeof(c48MI) / 4, sizeof(c48MI) / 4,
	sizeof(c49MI) / 4, sizeof(c49MI) / 4, sizeof(c49MI) / 4, sizeof(c49MI) / 4, sizeof(c49MI) / 4, sizeof(c49MI) / 4,
	sizeof(c50MI) / 4, sizeof(c50MI) / 4, sizeof(c50MI) / 4, sizeof(c50MI) / 4, sizeof(c50MI) / 4, sizeof(c50MI) / 4,
	sizeof(c51MI) / 4, sizeof(c51MI) / 4, sizeof(c51MI) / 4, sizeof(c51MI) / 4, sizeof(c51MI) / 4, sizeof(c51MI) / 4,
	sizeof(c109MI) / 4, sizeof(c109MI) / 4, sizeof(c109MI) / 4, sizeof(c109MI) / 4, sizeof(c109MI) / 4, sizeof(c109MI) / 4,
	sizeof(c110MI) / 4, sizeof(c110MI) / 4, sizeof(c110MI) / 4, sizeof(c110MI) / 4, sizeof(c110MI) / 4, sizeof(c110MI) / 4,
};

const signed short cmfMove[] = {
	sizeof(c0mv) / 4, sizeof(c1mv) / 4, sizeof(c2mv) / 4, sizeof(c3mv) / 4, sizeof(c4mv) / 4, sizeof(c5mv) / 4, sizeof(c6mv) / 4, sizeof(c7mv) / 4, sizeof(c8mv) / 4, sizeof(c9mv) / 4,
	sizeof(c10mv) / 4, sizeof(c11mv) / 4, sizeof(c12mv) / 4, sizeof(c13mv) / 4, sizeof(c14mv) / 4, sizeof(c15mv) / 4, sizeof(c16mv) / 4, sizeof(c17mv) / 4, sizeof(c18mv) / 4, sizeof(c19mv) / 4,
	sizeof(c20mv) / 4, sizeof(c21mv) / 4, sizeof(c22mv) / 4, sizeof(c23mv) / 4, sizeof(c24mv) / 4, sizeof(c25mv) / 4, sizeof(c26mv) / 4, sizeof(c27mv) / 4, sizeof(c28mv) / 4, sizeof(c29mv) / 4,
	sizeof(c30mv) / 4, sizeof(c31mv) / 4, sizeof(c32mv) / 4, sizeof(c33mv) / 4, sizeof(c34mv) / 4, sizeof(c35mv) / 4, sizeof(c36mv) / 4, sizeof(c37mv) / 4, sizeof(c38mv) / 4, sizeof(c39mv) / 4,
	sizeof(c40mv) / 4, sizeof(c41mv) / 4, sizeof(c42mv) / 4, sizeof(c43mv) / 4, sizeof(c44mv) / 4, sizeof(c45mv) / 4, sizeof(c46mv) / 4, sizeof(c47mv) / 4, sizeof(c48mv) / 4, sizeof(c49mv) / 4,
	sizeof(c50mv) / 4, sizeof(c51mv) / 4, sizeof(c52mv) / 4, sizeof(c53mv) / 4, sizeof(c54mv) / 4, sizeof(c55mv) / 4, sizeof(c56mv) / 4, sizeof(c57mv) / 4, sizeof(c58mv) / 4, sizeof(c59mv) / 4,
	sizeof(c60mv) / 4, sizeof(c61mv) / 4, sizeof(c62mv) / 4, sizeof(c63mv) / 4, sizeof(c64mv) / 4, sizeof(c65mv) / 4, sizeof(c66mv) / 4, sizeof(c67mv) / 4, sizeof(c68mv) / 4, sizeof(c69mv) / 4,
	sizeof(c70mv) / 4, sizeof(c71mv) / 4, sizeof(c72mv) / 4, sizeof(c73mv) / 4, sizeof(c74mv) / 4, sizeof(c75mv) / 4, sizeof(c76mv) / 4, sizeof(c77mv) / 4, sizeof(c78mv) / 4, sizeof(c79mv) / 4,
	sizeof(c80mv) / 4, sizeof(c81mv) / 4, sizeof(c82mv) / 4, sizeof(c83mv) / 4, sizeof(c84mv) / 4, sizeof(c85mv) / 4, sizeof(c86mv) / 4, sizeof(c87mv) / 4, sizeof(c88mv) / 4, sizeof(c89mv) / 4,
	sizeof(c90mv) / 4, sizeof(c91mv) / 4, sizeof(c92mv) / 4, sizeof(c93mv) / 4, sizeof(c94mv) / 4, sizeof(c95mv) / 4, sizeof(c96mv) / 4, sizeof(c97mv) / 4, sizeof(c98mv) / 4, sizeof(c99mv) / 4,
	sizeof(c100mv) / 4, sizeof(c101mv) / 4, sizeof(c102mv) / 4, sizeof(c103mv) / 4, sizeof(c104mv) / 4, sizeof(c105mv) / 4, sizeof(c106mv) / 4, sizeof(c107mv) / 4, sizeof(c108mv) / 4, sizeof(c109mv) / 4,
	sizeof(c110mv) / 4, sizeof(c111mv) / 4, sizeof(c112mv) / 4, sizeof(c113mv) / 4, sizeof(c114mv) / 4, sizeof(c115mv) / 4, sizeof(c116mv) / 4, sizeof(c117mv) / 4, sizeof(c118mv) / 4, sizeof(c119mv) / 4,
	sizeof(c120mv) / 4, sizeof(c121mv) / 4, sizeof(c122mv) / 4,

	sizeof(c3mv) / 4, sizeof(c3mv) / 4, sizeof(c3mv) / 4, sizeof(c3mv) / 4, sizeof(c3mv) / 4, sizeof(c3mv) / 4,
	sizeof(c4mv) / 4, sizeof(c4mv) / 4, sizeof(c4mv) / 4, sizeof(c4mv) / 4, sizeof(c4mv) / 4, sizeof(c4mv) / 4,
	sizeof(c5mv) / 4, sizeof(c5mv) / 4, sizeof(c5mv) / 4, sizeof(c5mv) / 4, sizeof(c5mv) / 4, sizeof(c5mv) / 4,
	sizeof(c6mv) / 4, sizeof(c6mv) / 4, sizeof(c6mv) / 4, sizeof(c6mv) / 4, sizeof(c6mv) / 4, sizeof(c6mv) / 4,
	sizeof(c7mv) / 4, sizeof(c7mv) / 4, sizeof(c7mv) / 4, sizeof(c7mv) / 4, sizeof(c7mv) / 4, sizeof(c7mv) / 4,
	sizeof(c8mv) / 4, sizeof(c8mv) / 4, sizeof(c8mv) / 4, sizeof(c8mv) / 4, sizeof(c8mv) / 4, sizeof(c8mv) / 4,
	sizeof(c9mv) / 4, sizeof(c9mv) / 4, sizeof(c9mv) / 4, sizeof(c9mv) / 4, sizeof(c9mv) / 4, sizeof(c9mv) / 4,
	sizeof(c10mv) / 4, sizeof(c10mv) / 4, sizeof(c10mv) / 4, sizeof(c10mv) / 4, sizeof(c10mv) / 4, sizeof(c10mv) / 4,
	sizeof(c11mv) / 4, sizeof(c11mv) / 4, sizeof(c11mv) / 4, sizeof(c11mv) / 4, sizeof(c11mv) / 4, sizeof(c11mv) / 4,
	sizeof(c12mv) / 4, sizeof(c12mv) / 4, sizeof(c12mv) / 4, sizeof(c12mv) / 4, sizeof(c12mv) / 4, sizeof(c12mv) / 4,
	sizeof(c13mv) / 4, sizeof(c13mv) / 4, sizeof(c13mv) / 4, sizeof(c13mv) / 4, sizeof(c13mv) / 4, sizeof(c13mv) / 4,
	sizeof(c14mv) / 4, sizeof(c14mv) / 4, sizeof(c14mv) / 4, sizeof(c14mv) / 4, sizeof(c14mv) / 4, sizeof(c14mv) / 4,
	sizeof(c15mv) / 4, sizeof(c15mv) / 4, sizeof(c15mv) / 4, sizeof(c15mv) / 4, sizeof(c15mv) / 4, sizeof(c15mv) / 4,
	sizeof(c16mv) / 4, sizeof(c16mv) / 4, sizeof(c16mv) / 4, sizeof(c16mv) / 4, sizeof(c16mv) / 4, sizeof(c16mv) / 4,
	sizeof(c17mv) / 4, sizeof(c17mv) / 4, sizeof(c17mv) / 4, sizeof(c17mv) / 4, sizeof(c17mv) / 4, sizeof(c17mv) / 4,
	sizeof(c18mv) / 4, sizeof(c18mv) / 4, sizeof(c18mv) / 4, sizeof(c18mv) / 4, sizeof(c18mv) / 4, sizeof(c18mv) / 4,
	sizeof(c19mv) / 4, sizeof(c19mv) / 4, sizeof(c19mv) / 4, sizeof(c19mv) / 4, sizeof(c19mv) / 4, sizeof(c19mv) / 4,
	sizeof(c20mv) / 4, sizeof(c20mv) / 4, sizeof(c20mv) / 4, sizeof(c20mv) / 4, sizeof(c20mv) / 4, sizeof(c20mv) / 4,
	sizeof(c21mv) / 4, sizeof(c21mv) / 4, sizeof(c21mv) / 4, sizeof(c21mv) / 4, sizeof(c21mv) / 4, sizeof(c21mv) / 4,
	sizeof(c22mv) / 4, sizeof(c22mv) / 4, sizeof(c22mv) / 4, sizeof(c22mv) / 4, sizeof(c22mv) / 4, sizeof(c22mv) / 4,
	sizeof(c23mv) / 4, sizeof(c23mv) / 4, sizeof(c23mv) / 4, sizeof(c23mv) / 4, sizeof(c23mv) / 4, sizeof(c23mv) / 4,
	sizeof(c24mv) / 4, sizeof(c24mv) / 4, sizeof(c24mv) / 4, sizeof(c24mv) / 4, sizeof(c24mv) / 4, sizeof(c24mv) / 4,
	sizeof(c25mv) / 4, sizeof(c25mv) / 4, sizeof(c25mv) / 4, sizeof(c25mv) / 4, sizeof(c25mv) / 4, sizeof(c25mv) / 4,
	sizeof(c26mv) / 4, sizeof(c26mv) / 4, sizeof(c26mv) / 4, sizeof(c26mv) / 4, sizeof(c26mv) / 4, sizeof(c26mv) / 4,
	sizeof(c27mv) / 4, sizeof(c27mv) / 4, sizeof(c27mv) / 4, sizeof(c27mv) / 4, sizeof(c27mv) / 4, sizeof(c27mv) / 4,
	sizeof(c28mv) / 4, sizeof(c28mv) / 4, sizeof(c28mv) / 4, sizeof(c28mv) / 4, sizeof(c28mv) / 4, sizeof(c28mv) / 4,
	sizeof(c29mv) / 4, sizeof(c29mv) / 4, sizeof(c29mv) / 4, sizeof(c29mv) / 4, sizeof(c29mv) / 4, sizeof(c29mv) / 4,
	sizeof(c30mv) / 4, sizeof(c30mv) / 4, sizeof(c30mv) / 4, sizeof(c30mv) / 4, sizeof(c30mv) / 4, sizeof(c30mv) / 4,
	sizeof(c31mv) / 4, sizeof(c31mv) / 4, sizeof(c31mv) / 4, sizeof(c31mv) / 4, sizeof(c31mv) / 4, sizeof(c31mv) / 4,
	sizeof(c32mv) / 4, sizeof(c32mv) / 4, sizeof(c32mv) / 4, sizeof(c32mv) / 4, sizeof(c32mv) / 4, sizeof(c32mv) / 4,
	sizeof(c33mv) / 4, sizeof(c33mv) / 4, sizeof(c33mv) / 4, sizeof(c33mv) / 4, sizeof(c33mv) / 4, sizeof(c33mv) / 4,
	sizeof(c34mv) / 4, sizeof(c34mv) / 4, sizeof(c34mv) / 4, sizeof(c34mv) / 4, sizeof(c34mv) / 4, sizeof(c34mv) / 4,
	sizeof(c35mv) / 4, sizeof(c35mv) / 4, sizeof(c35mv) / 4, sizeof(c35mv) / 4, sizeof(c35mv) / 4, sizeof(c35mv) / 4,
	sizeof(c36mv) / 4, sizeof(c36mv) / 4, sizeof(c36mv) / 4, sizeof(c36mv) / 4, sizeof(c36mv) / 4, sizeof(c36mv) / 4,
	sizeof(c37mv) / 4, sizeof(c37mv) / 4, sizeof(c37mv) / 4, sizeof(c37mv) / 4, sizeof(c37mv) / 4, sizeof(c37mv) / 4,
	sizeof(c38mv) / 4, sizeof(c38mv) / 4, sizeof(c38mv) / 4, sizeof(c38mv) / 4, sizeof(c38mv) / 4, sizeof(c38mv) / 4,
	sizeof(c39mv) / 4, sizeof(c39mv) / 4, sizeof(c39mv) / 4, sizeof(c39mv) / 4, sizeof(c39mv) / 4, sizeof(c39mv) / 4,
	sizeof(c40mv) / 4, sizeof(c40mv) / 4, sizeof(c40mv) / 4, sizeof(c40mv) / 4, sizeof(c40mv) / 4, sizeof(c40mv) / 4,
	sizeof(c41mv) / 4, sizeof(c41mv) / 4, sizeof(c41mv) / 4, sizeof(c41mv) / 4, sizeof(c41mv) / 4, sizeof(c41mv) / 4,
	sizeof(c42mv) / 4, sizeof(c42mv) / 4, sizeof(c42mv) / 4, sizeof(c42mv) / 4, sizeof(c42mv) / 4, sizeof(c42mv) / 4,
	sizeof(c43mv) / 4, sizeof(c43mv) / 4, sizeof(c43mv) / 4, sizeof(c43mv) / 4, sizeof(c43mv) / 4, sizeof(c43mv) / 4,
	sizeof(c44mv) / 4, sizeof(c44mv) / 4, sizeof(c44mv) / 4, sizeof(c44mv) / 4, sizeof(c44mv) / 4, sizeof(c44mv) / 4,
	sizeof(c45mv) / 4, sizeof(c45mv) / 4, sizeof(c45mv) / 4, sizeof(c45mv) / 4, sizeof(c45mv) / 4, sizeof(c45mv) / 4,
	sizeof(c46mv) / 4, sizeof(c46mv) / 4, sizeof(c46mv) / 4, sizeof(c46mv) / 4, sizeof(c46mv) / 4, sizeof(c46mv) / 4,
	sizeof(c47mv) / 4, sizeof(c47mv) / 4, sizeof(c47mv) / 4, sizeof(c47mv) / 4, sizeof(c47mv) / 4, sizeof(c47mv) / 4,
	sizeof(c48mv) / 4, sizeof(c48mv) / 4, sizeof(c48mv) / 4, sizeof(c48mv) / 4, sizeof(c48mv) / 4, sizeof(c48mv) / 4,
	sizeof(c49mv) / 4, sizeof(c49mv) / 4, sizeof(c49mv) / 4, sizeof(c49mv) / 4, sizeof(c49mv) / 4, sizeof(c49mv) / 4,
	sizeof(c50mv) / 4, sizeof(c50mv) / 4, sizeof(c50mv) / 4, sizeof(c50mv) / 4, sizeof(c50mv) / 4, sizeof(c50mv) / 4,
	sizeof(c51mv) / 4, sizeof(c51mv) / 4, sizeof(c51mv) / 4, sizeof(c51mv) / 4, sizeof(c51mv) / 4, sizeof(c51mv) / 4,
	sizeof(c109mv) / 4, sizeof(c109mv) / 4, sizeof(c109mv) / 4, sizeof(c109mv) / 4, sizeof(c109mv) / 4, sizeof(c109mv) / 4,
	sizeof(c110mv) / 4, sizeof(c110mv) / 4, sizeof(c110mv) / 4, sizeof(c110mv) / 4, sizeof(c110mv) / 4, sizeof(c110mv) / 4,
};


const unsigned short costumeSize[6 * 2 * 3] = {
	//weapon
	41 * _2X, 51 * _2X,
	32 * _2X, 14 * _2X,
	78 * _2X, 35 * _2X,

	//helm
	49 * _2X, 25 * _2X,
	49 * _2X, 25 * _2X,
	49 * _2X, 25 * _2X,

	//armor
	36 * _2X, 9 * _2X,
	29 * _2X, 8 * _2X,
	31 * _2X, 8 * _2X,

	//pants
	22 * _2X, 7 * _2X,
	16 * _2X, 6 * _2X,
	22 * _2X, 7 * _2X,

	//glove
	62 * _2X, 26 * _2X,
	31 * _2X, 24 * _2X,
	31 * _2X, 19 * _2X,

	//boots
	70 * _2X, 16 * _2X,
	74 * _2X, 17 * _2X,
	88 * _2X, 16 * _2X,
};

const unsigned short costumeOff[100 * 6] = {
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,//w0.png
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,

	5 * _2X, 9 * _2X, 21 * _2X, 15 * _2X, 97 * _2X, 68 * _2X,//w1.png
	4 * _2X, 37 * _2X, 24 * _2X, 7 * _2X, 0 * _2X, 111 * _2X,
	3 * _2X, 9 * _2X, 22 * _2X, 16 * _2X, 158 * _2X, 103 * _2X,//w2.png
	5 * _2X, 34 * _2X, 25 * _2X, 12 * _2X, 170 * _2X, 87 * _2X,
	4 * _2X, 7 * _2X, 23 * _2X, 19 * _2X, 89 * _2X, 93 * _2X,//w3.png
	5 * _2X, 33 * _2X, 26 * _2X, 13 * _2X, 169 * _2X, 74 * _2X,
	4 * _2X, 6 * _2X, 24 * _2X, 19 * _2X, 65 * _2X, 101 * _2X,//w4.png
	5 * _2X, 31 * _2X, 29 * _2X, 16 * _2X, 166 * _2X, 58 * _2X,
	2 * _2X, 8 * _2X, 28 * _2X, 18 * _2X, 100 * _2X, 49 * _2X,//w5.png
	3 * _2X, 33 * _2X, 31 * _2X, 13 * _2X, 127 * _2X, 107 * _2X,
	3 * _2X, 2 * _2X, 30 * _2X, 24 * _2X, 70 * _2X, 53 * _2X,//w6.png
	5 * _2X, 33 * _2X, 33 * _2X, 15 * _2X, 162 * _2X, 43 * _2X,
	0 * _2X, 0 * _2X, 34 * _2X, 27 * _2X, 36 * _2X, 57 * _2X,//w7.png
	0 * _2X, 33 * _2X, 38 * _2X, 17 * _2X, 157 * _2X, 26 * _2X,
	3 * _2X, 2 * _2X, 35 * _2X, 27 * _2X, 42 * _2X, 29 * _2X,//w8.png
	5 * _2X, 29 * _2X, 36 * _2X, 22 * _2X, 0 * _2X, 67 * _2X,

	2 * _2X, 3 * _2X, 7 * _2X, 9 * _2X, 155 * _2X, 49 * _2X,//w9.png
	19 * _2X, 6 * _2X, 10 * _2X, 5 * _2X, 89 * _2X, 112 * _2X,
	1 * _2X, 1 * _2X, 10 * _2X, 12 * _2X, 39 * _2X, 106 * _2X,//w10.png
	16 * _2X, 4 * _2X, 14 * _2X, 7 * _2X, 138 * _2X, 41 * _2X,
	0 * _2X, 1 * _2X, 11 * _2X, 11 * _2X, 184 * _2X, 110 * _2X,//w11.png
	15 * _2X, 3 * _2X, 15 * _2X, 10 * _2X, 112 * _2X, 101 * _2X,
	0 * _2X, 1 * _2X, 11 * _2X, 11 * _2X, 184 * _2X, 99 * _2X,//w12.png
	16 * _2X, 2 * _2X, 15 * _2X, 10 * _2X, 97 * _2X, 83 * _2X,
	0 * _2X, 1 * _2X, 11 * _2X, 11 * _2X, 137 * _2X, 70 * _2X,//w13.png
	15 * _2X, 3 * _2X, 14 * _2X, 9 * _2X, 134 * _2X, 82 * _2X,
	0 * _2X, 2 * _2X, 11 * _2X, 10 * _2X, 24 * _2X, 111 * _2X,//w14.png
	15 * _2X, 3 * _2X, 15 * _2X, 9 * _2X, 112 * _2X, 111 * _2X,
	0 * _2X, 0 * _2X, 15 * _2X, 13 * _2X, 134 * _2X, 91 * _2X,//w15.png
	15 * _2X, 0 * _2X, 17 * _2X, 11 * _2X, 140 * _2X, 30 * _2X,
	2 * _2X, 0 * _2X, 12 * _2X, 14 * _2X, 154 * _2X, 58 * _2X,//w16.png
	15 * _2X, 0 * _2X, 16 * _2X, 12 * _2X, 49 * _2X, 106 * _2X,

	9 * _2X, 11 * _2X, 18 * _2X, 14 * _2X, 118 * _2X, 70 * _2X,//w17.png
	41 * _2X, 8 * _2X, 32 * _2X, 19 * _2X, 106 * _2X, 30 * _2X,
	8 * _2X, 10 * _2X, 19 * _2X, 15 * _2X, 148 * _2X, 72 * _2X,//w18.png
	41 * _2X, 7 * _2X, 32 * _2X, 22 * _2X, 37 * _2X, 84 * _2X,
	7 * _2X, 9 * _2X, 22 * _2X, 17 * _2X, 112 * _2X, 84 * _2X,//w19.png
	38 * _2X, 6 * _2X, 37 * _2X, 22 * _2X, 0 * _2X, 89 * _2X,
	5 * _2X, 5 * _2X, 21 * _2X, 20 * _2X, 149 * _2X, 87 * _2X,//w20.png
	39 * _2X, 2 * _2X, 35 * _2X, 30 * _2X, 119 * _2X, 0 * _2X,
	4 * _2X, 5 * _2X, 26 * _2X, 22 * _2X, 128 * _2X, 48 * _2X,//w21.png
	37 * _2X, 5 * _2X, 41 * _2X, 26 * _2X, 154 * _2X, 0 * _2X,
	5 * _2X, 4 * _2X, 28 * _2X, 24 * _2X, 69 * _2X, 77 * _2X,//w22.png
	37 * _2X, 3 * _2X, 41 * _2X, 29 * _2X, 43 * _2X, 0 * _2X,
	5 * _2X, 3 * _2X, 29 * _2X, 23 * _2X, 77 * _2X, 30 * _2X,//w23.png
	36 * _2X, 2 * _2X, 42 * _2X, 32 * _2X, 0 * _2X, 35 * _2X,
	0 * _2X, 0 * _2X, 35 * _2X, 30 * _2X, 84 * _2X, 0 * _2X,//w24.png
	35 * _2X, 0 * _2X, 43 * _2X, 35 * _2X, 0 * _2X, 0 * _2X,

	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,//h0.png
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	4 * _2X, 10 * _2X, 14 * _2X, 14 * _2X, 0 * _2X, 39 * _2X,//h1.png
	29 * _2X, 10 * _2X, 14 * _2X, 14 * _2X, 14 * _2X, 39 * _2X,
	2 * _2X, 8 * _2X, 16 * _2X, 16 * _2X, 0 * _2X, 82 * _2X,//h2.png
	28 * _2X, 8 * _2X, 16 * _2X, 16 * _2X, 16 * _2X, 82 * _2X,
	2 * _2X, 4 * _2X, 17 * _2X, 20 * _2X, 38 * _2X, 19 * _2X,//h3.png
	28 * _2X, 4 * _2X, 19 * _2X, 20 * _2X, 55 * _2X, 19 * _2X,
	3 * _2X, 5 * _2X, 15 * _2X, 19 * _2X, 123 * _2X, 57 * _2X,//h4.png
	29 * _2X, 5 * _2X, 15 * _2X, 19 * _2X, 108 * _2X, 58 * _2X,
	2 * _2X, 7 * _2X, 17 * _2X, 17 * _2X, 0 * _2X, 53 * _2X,//h5.png
	28 * _2X, 8 * _2X, 16 * _2X, 17 * _2X, 17 * _2X, 53 * _2X,
	0 * _2X, 5 * _2X, 20 * _2X, 19 * _2X, 0 * _2X, 0 * _2X,//h6.png
	28 * _2X, 5 * _2X, 17 * _2X, 19 * _2X, 20 * _2X, 0 * _2X,
	0 * _2X, 4 * _2X, 21 * _2X, 20 * _2X, 74 * _2X, 19 * _2X,//h7.png
	28 * _2X, 4 * _2X, 15 * _2X, 20 * _2X, 95 * _2X, 19 * _2X,
	0 * _2X, 5 * _2X, 23 * _2X, 19 * _2X, 71 * _2X, 0 * _2X,//h8.png
	28 * _2X, 5 * _2X, 19 * _2X, 19 * _2X, 94 * _2X, 0 * _2X,

	2 * _2X, 9 * _2X, 18 * _2X, 10 * _2X, 73 * _2X, 53 * _2X,//h9.png
	28 * _2X, 9 * _2X, 17 * _2X, 10 * _2X, 101 * _2X, 39 * _2X,
	1 * _2X, 9 * _2X, 19 * _2X, 16 * _2X, 32 * _2X, 82 * _2X,//h10.png
	27 * _2X, 9 * _2X, 20 * _2X, 16 * _2X, 51 * _2X, 82 * _2X,
	0 * _2X, 8 * _2X, 24 * _2X, 11 * _2X, 71 * _2X, 87 * _2X,//h11.png
	26 * _2X, 8 * _2X, 21 * _2X, 11 * _2X, 72 * _2X, 76 * _2X,
	2 * _2X, 10 * _2X, 21 * _2X, 10 * _2X, 117 * _2X, 88 * _2X,//h12.png
	30 * _2X, 10 * _2X, 18 * _2X, 10 * _2X, 110 * _2X, 27 * _2X,
	1 * _2X, 7 * _2X, 22 * _2X, 14 * _2X, 58 * _2X, 39 * _2X,//h13.png
	27 * _2X, 7 * _2X, 21 * _2X, 14 * _2X, 80 * _2X, 39 * _2X,
	3 * _2X, 10 * _2X, 15 * _2X, 14 * _2X, 28 * _2X, 39 * _2X,//h14.png
	29 * _2X, 10 * _2X, 15 * _2X, 14 * _2X, 43 * _2X, 39 * _2X,
	1 * _2X, 0 * _2X, 25 * _2X, 21 * _2X, 113 * _2X, 0 * _2X,//h15.png
	27 * _2X, 0 * _2X, 22 * _2X, 21 * _2X, 95 * _2X, 77 * _2X,
	0 * _2X, 3 * _2X, 22 * _2X, 20 * _2X, 0 * _2X, 19 * _2X,//h16.png
	29 * _2X, 3 * _2X, 16 * _2X, 20 * _2X, 22 * _2X, 19 * _2X,

	5 * _2X, 9 * _2X, 20 * _2X, 9 * _2X, 108 * _2X, 49 * _2X,//h17.png
	30 * _2X, 10 * _2X, 17 * _2X, 8 * _2X, 91 * _2X, 68 * _2X,
	4 * _2X, 13 * _2X, 13 * _2X, 6 * _2X, 123 * _2X, 21 * _2X,//h18.png
	30 * _2X, 13 * _2X, 13 * _2X, 6 * _2X, 110 * _2X, 21 * _2X,
	2 * _2X, 2 * _2X, 17 * _2X, 19 * _2X, 37 * _2X, 0 * _2X,//h19.png
	28 * _2X, 2 * _2X, 17 * _2X, 19 * _2X, 54 * _2X, 0 * _2X,
	4 * _2X, 5 * _2X, 17 * _2X, 15 * _2X, 91 * _2X, 53 * _2X,//h20.png
	29 * _2X, 7 * _2X, 18 * _2X, 13 * _2X, 73 * _2X, 63 * _2X,
	2 * _2X, 8 * _2X, 20 * _2X, 12 * _2X, 117 * _2X, 76 * _2X,//h21.png
	29 * _2X, 8 * _2X, 17 * _2X, 14 * _2X, 122 * _2X, 36 * _2X,
	1 * _2X, 8 * _2X, 21 * _2X, 12 * _2X, 0 * _2X, 70 * _2X,//h22.png
	29 * _2X, 8 * _2X, 16 * _2X, 12 * _2X, 21 * _2X, 70 * _2X,
	2 * _2X, 8 * _2X, 18 * _2X, 12 * _2X, 37 * _2X, 70 * _2X,//h23.png
	28 * _2X, 8 * _2X, 17 * _2X, 12 * _2X, 55 * _2X, 70 * _2X,
	2 * _2X, 5 * _2X, 21 * _2X, 17 * _2X, 33 * _2X, 53 * _2X,//h24.png
	28 * _2X, 5 * _2X, 19 * _2X, 17 * _2X, 54 * _2X, 53 * _2X,
};
#endif