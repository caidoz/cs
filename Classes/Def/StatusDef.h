#pragma once

#ifndef _DEF_STATUS_H_
#define _DEF_STATUS_H_

typedef enum _statusDef {
	//주인공 상태
	WALK = 0,
	JUMP = 1 + WALK,
	JUMP2 = 1 + JUMP,	//그냥 점프
	JUMP3 = 1 + JUMP2,	//뚫리는 타일에서 아래로 점프
	FALL = 1 + JUMP3,	//계단에서 아래로 점프
	FALL2 = 1 + FALL,	//착지시
	THROUGH = 1 + FALL2,
	THROUGH2 = 1 + THROUGH,
	GLIDE = 1 + THROUGH2,
	FLYING = 1 + GLIDE,
	MAGNET = 1 + FLYING,

	//움직임 종류
	GROUND = 0,
	WATER,
	SWAMP,
	SPACE,

	FREEFALL = 24 * _2X,
	JUMPFRAME = 10,
	JUMPFULLFRAME = 11,
	HIGHJUMPFRAME = 8,
	DOWNATTHEIGHT = 64 * _2X,
	FLOW_DX = 3 * _2X,

	DX_WALK = 6 * _2X,
	DX_RUN = 12 * _2X,
	DX_SLOW = 2 * _2X,
	DX_SWIM = 4 * _2X,
	DX_SWIM_SLOW = 3 * _2X,
	DX_SWAMP = 3 * _2X,
	DX_SWAMP_SLOW = 2 * _2X,
	DX_SPACE = 16 * _2X,


} STATUSDEF;

#endif
