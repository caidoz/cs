#pragma once
#include "../Def.h"

#ifndef _ALPHA_DATA_H_
#define _ALPHA_DATA_H_

const unsigned char demoAlpha[10 * 5] = {
	ALPHA_DIRECTOR,	//0
	0,
	ALPHA_SHINNJONGMU,	//1
	0,
	0,

	ALPHA_GAMEDESIGN,	//2
	0,
	ALPHA_KIMDAEWON,	//3
	ALPHA_SHINNJONGMU,	//4
	ALPHA_CHOIJINHYOUNG,	//5

	ALPHA_PROGRAM,	//6
	0,
	ALPHA_CHOIJINHYOUNG,	//7
	ALPHA_KIMKYOUNGHO,	//9
	ALPHA_KIMHYUN,	//8

	ALPHA_GRAPHICSDESIGN,	//10
	0,
	ALPHA_LEEKYUWON,	//11
	ALPHA_SHINNJONGMU,	//12
	ALPHA_SONMINSEOK,	//13

	ALPHA_SOUNDDESIGN,	//14
	0,
	ALPHA_NAUTS,	//15
	ALPHA_NIEN,	//16
	0,

	ALPHA_ARTWORK,	//17
	0,
	ALPHA_SONMINSEOK,	//18
	0,
	0,

	ALPHA_DEBUG,	//19
	0,
	ALPHA_JEONGCHUNGWOO,	//20
	0,
	0,

	ALPHA_ADVERTISEMENT,	//21
	0,
	ALPHA_LEEKYUSEUNG,	//22
	0,
	0,

	ALPHA_SPECIALTHANKSTO,	//23
	0,
	ALPHA_HWANGSEONGWON,	//24
	ALPHA_PARKJUNHYOUNG,	//25
	0,

	ALPHA_EXECUTIVEPRODUCER,	//26
	0,
	ALPHA_LEEKYUSEUNG,	//27
	0,
	0,
};

const unsigned char alphaData[TOTAL_ALPHA_OFF] = {
	L,	//ALPHA_L
	F,	//ALPHA_F
	H, P,	//ALPHA_HP
	M, P,	//ALPHA_MP
	E, X, P,	//ALPHA_EXP
	S, T, R,	//ALPHA_STR
	V, I, T,	//ALPHA_VIT
	A, G, I,	//ALPHA_AGI
	I, N, T,	//ALPHA_INT
	P, O, I, N, T,	//ALPHA_POINT
	P, O, I, S, O, N,	//ALPHA_POISON
	S, L, O, W,	//ALPHA_SLOW
	B, L, I, N, D,	//ALPHA_BLIND
	S, T, U, N,	//ALPHA_STUN
	C, U, R, S, E,	//ALPHA_CURSE
	P, H, Y, S, I, C, A, L,//ALPHA_PHYSICAL
	F, L, A, M, E,//ALPHA_FLAME
	I, C, E,//ALPHA_ICE
	L, I, G, H, T, N, I, N, G,//ALPHA_LIGHTNING
	H, O, L, Y,//ALPHA_HOLY
	D, A, R, K, N, E, S, S,//ALPHA_DARKNESS
	S, E, L, E, C,
	B, A, C, K,
	T, COLON, SPC, O, K,
	T, COLON, SPC, O, Z,
	COLON, SPC, C, L, R,
	B, A, C, K, SPC, COLON, SPC, C, L, R,	//ALPHA_BACKCLR
	C, L, R,		//ALPHA_CLR
	S, E, L, E, C, T, SPC, COLON, SPC, O, K,	//ALPHA_SELECTOK
	S, E, L, E, C, T, SPC, COLON, SPC, O, Z,	//ALPHA_SELECTOZ
	B, U, Y,	//ALPHA_BUY
	S, E, L, L,	//ALPHA_SELL
	E, X, I, T,	//ALPHA_EXIT
	E, N, C, H, A, N, T,	//ALPHA_ENCHANT
	S, O, C, K, E, T,	//ALPHA_SOCKET
	O, SPC, COLON, SPC, D, A, I, L, Y,	//ALPHA_DAILY
	G, U, I, L, D, SPC, V, S,	//ALPHA_GUILDVS
	E, X, I, T, SPC, A, R, E, N, A,	//ALPHA_EXITARENA,
	E, X, I, T, SPC, D, U, N, G, E, O, N,	//ALPHA_EXITDUNGEON
	E, R, A, S, E, SPC, COLON, SPC, C, L, R,	//ALPHA_ERASE

	S,
	I,
	Q,
	M,
	O,
	PAR_L,
	PAR_R,
	V, DOT,
	S, T, A, T, U, E,
	K, E, Y, SPC, I, T, E, M,
	I, T, E, M,
	I, N, F, O, SPC, COLON, SPC, POUND,
	S, T, A, T, U, S, SPC, COLON, SPC, POUND,
	SLA,
	R, E, G, I, S, T,
	PLUS,
	MINUS,
	PER,
	T,
	A,
	U,
	N,
	V,
	E,
	Y,
	G,
	K,
	X,

	B,
	C,
	D,
	R,
	S, S,
	S, S, S,

	COLON,
	STAR,
	POUND,
	Q, U, I, C, K,
	A, C, T, I, V, E,
	P, A, S, S, I, V, E,
	S, E, N, D, SPC, COLON, SPC, N, E, T, SPC, I, N, V, E, N,
	S, E, N, D, SPC, COLON, SPC, S, I, N, G, L, E, SPC, I, N, V, E, N,

	O, K,
	O, Z,
	D, M, G,
	L, V,
	N, E, T, W, O, R, K,
	S, I, N, G, L, E,
	M, A, I, N,
	S, U, B,

	S, T, A, T, U, S,
	I, N, V, E, N, T, O, R, Y,
	S, K, I, L, L,
	Q, U, E, S, T,
	M, A, P,
	H, I, N, T,
	O, P, T, I, O, N,
	V, I, E, W, SPC, R, A, N, K, I, N, G,
	I, T, E, M, SPC, S, H, O, P,
	N, E, T, SPC, I, N, V, E, N, T, O, R, Y,
	R, E, C, O, M, M, E, N, D,
	P, L, A, Y, E, R, SPC, T, I, T, L, E,
	R, E, P, O, R, T, S,
	M, O, N, S, T, E, R,
	O, N,
	O, F, F,
	D, A, M, A, G, E,
	D, E, F, E, N, S, E,
	U, S, E,
	R, E, W, A, R, D,
	R, E, Q, U, I, R, E,

	S, W, O, R, D,
	G, U, N,
	B, O, O, M, E, R, A, N, G,
	H, E, L, M,
	H, A, T,
	C, A, P,
	A, R, M, O, R,
	V, E, S, T,
	C, O, A, T,
	G, U, N, T, L, E, T,
	A, R, M, L, E, T,
	G, L, O, V, E,
	K, I, L, T,
	S, K, I, R, T,
	P, A, N, T, S,
	G, R, E, A, V, E, S,
	S, H, O, E, S,
	B, O, O, T, S,
	N, E, C, K, L, A, C, E,
	R, I, N, G,
	G, E, M,
	W, A, S, T, E, S,
	I, R, O, N,
	L, E, A, T, H, E, R,
	C, L, O, T, H,
	W, O, O, D,
	E, S, S, E, N, C, E,
	R, E, C, I, P, E,
	Q, U, E, S, T, SPC, I, T, E, M,
	N, E, T, SPC, I, T, E, M,
	T, A, L, K,
	P, R, I, C, E,
	S, H, O, P,
	S, T, A, R, SPC, S, H, O, P,
	E, Q, U, I, P,
	S, A, V, E,
	S, C, R, E, E, N, SPC, S, H, O, T,
	H, E, L, P,
	S, E, T, U, P,
	Q, U, I, T,
	R, O, B, I, N,
	D, I, A, N, A,
	M, A, X, X,
	S, L, O, T,
	N, O, SPC, D, A, T, A,
	POUND, SPC, D, A, T, A, SPC, R, E, S, E, T,
	H, E, L, L, SPC, M, O, D, E,
	G, A, M, E, SPC, O, V, E, R,
	P, R, E, S, S, SPC, A, N, Y, SPC, K, E, Y,
	T, O, U, C, H, SPC, S, C, R, E, E, N,
	T, O, U, C, H,
	N, O,
	G, O, L, D,
	S, K, I, P,
	G, E, T, SPC, Q, U, E, S, T,
	D, A, I, L, Y, SPC, Q, U, E, S, T,
	F, A, I, L, SPC, Q, U, E, S, T,
	C, L, I, E, N, T,
	T, I, M, E,
	G, I, V, E,
	G, E, T,
	R, E, S, U, L, T,
	F, R, O, M,
	T, O,
	L, O, A, D, I, N, G,
	DOT,
	N, O, W,
	T, I, M, E, SPC, L, E, F, T,
	M, E, N, U, SPC, COLON,
	O, R, D, E, R,
	T, O, T, A, L,
	A, R, E, N, A,
	M, I, N, I, G, A, M, E, SPC, 1,
	M, I, N, I, G, A, M, E, SPC, 2,
	M, I, N, I, G, A, M, E, SPC, 3,
	M, I, N, I, G, A, M, E, SPC, 4,
	M, I, N, I, G, A, M, E, SPC, 5,
	R, A, N, K,
	S, C, O, R, E,
	M, A, S, T, E, R,
	N, E, T, SPC, I, N, V, E, N,
	N, E, T, SPC, S, H, O, P,
	S, A, L, E, SPC, S, H, O, P,
	C, O, U, P, O, N, SPC, S, H, O, P,
	G, I, F, T,
	P, H, O, N, E, SPC, N, U, M, B, E, R,
	C, O, U, P, O, N,
	V, I, E, W,
	V, E, R, SPC,
	M, Y,
	T, O, P,
	M, A, X,
	B, E, T,
	S, A, L, E,
	W, E, E, K,
	G, O, A, L,			//ALPAH_GOAL
	P, L, A, Y, E, R,	//ALPHA_PLAYER

	P, L, U, S, SPC, D, M, G,
	P, E, R, C, E, N, T, SPC, D, M, G,
	P, I, E, R, C, E, SPC, A, T, K,
	M, E, N, U, SPC, O, P, E, N,
	A, B, I, L, I, T, Y,
	E, X, T, R, A, SPC, A, T, K,
	H, P, SPC, R, E, S, T, O, R, E,
	B, U, F, F, T, I, M, E, SPC, U, P,
	I, G, N, O, R, E, SPC, D, E, F,
	H, P, SPC, D, R, A, I, N,
	D, E, B, U, F, SPC, D, O, W, N,
	S, K, I, L, L, SPC, D, M, G,
	S, T, A, T, U, S, SPC, U, P,
	S, K, I, L, L, SPC, C, O, O, L,
	C, R, I, T, I, C, A, L, SPC, P, R, O, B,
	C, R, I, T, I, C, A, L, SPC, D, M, G,

	D, I, R, E, C, T, O, R,	//ALPHA_DIRECTOR
	S, H, I, N, N, SPC, J, O, N, G, SPC, M, U,	//ALPHA_SHINNJONGMU

	G, A, M, E, SPC, D, E, S, I, G, N,	//ALPHA_GAMEDESIGN
	K, I, M, SPC, D, A, E, SPC, W, O, N,	//ALPHA_KIMDAEWON
	C, H, O, I, SPC, J, I, N, SPC, H, Y, O, U, N, G,	//ALPHA_CHOIJINHYOUNG

	P, R, O, G, R, A, M,	//ALPHA_PROGRAM
	K, I, M, SPC, K, Y, O, U, N, G, SPC, H, O,	//ALPHA_KIMKYOUNGHO
	K, I, M, SPC, H, Y, U, N,	//ALPHA_KIMHYUN

	G, R, A, P, H, I, C, S, SPC, D, E, S, I, G, N,	//ALPHA_GRAPHICSDESIGN
	L, E, E, SPC, K, Y, U, SPC, W, O, N,	//ALPHA_LEEKYUWON
	S, O, N, SPC, M, I, N, SPC, S, E, O, K,	//ALPHA_SONMINSEOK

	S, O, U, N, D, SPC, D, E, S, I, G, N,	//ALPHA_SOUNDDESIGN
	N, A, U, T, S,	//ALPHA_NAUTS
	N, I, E, N,	//ALPHA_NIEN

	A, R, T, W, O, R, K,	//ALPHA_ARTWORK

	D, E, B, U, G,	//ALPHA_DEBUG
	J, E, O, N, G, SPC, C, H, U, N, G, SPC, W, O, O,	//ALPHA_JEONGCHUNGWOO

	A, D, V, E, R, T, I, S, E, M, E, N, T,	//ALPHA_ADVERTISEMENT
	L, E, E, SPC, K, Y, U, SPC, S, E, U, N, G,	//ALPHA_LEEKYUSEUNG

	S, P, E, C, I, A, L, SPC, T, H, A, N, K, S, SPC, T, O,	//ALPHA_SPECIALTHANKSTO
	H, W, A, N, G, SPC, S, E, O, N, G, SPC, W, O, N,	//ALPHA_HWANGSEONGWON
	P, A, R, K, SPC, J, U, N, SPC, H, Y, O, U, N, G,	//ALPHA_PARKJUNHYOUNG

	E, X, E, C, U, T, I, V, E, SPC, P, R, O, D, U, C, E, R,	//ALPHA_EXECUTIVEPRODUCER

	C, R, E, W,	//ALPHA_CREW
	G, O, O, G, L, E,	//ALPHA_GOOGLE
	G, U, E, S, T,	//ALPHA_GUEST

	K, N, I, G, H, T,	//ALPHA_KNIGHT
	G, U, N, N, E, R,	//ALPHA_GUNNER
	H, U, N, T, E, R,//ALPHA_HUNTER

	P, L, A, Y, //ALPHA_PLAY,
	H, O, U, S, E,//ALPHA_HOUSE,
	N, E, W, S,//ALPHA_NEWS,
	G, I, F, T, S,//ALPHA_GIFTS,
	S,W,O,R,D, SPC, C, O, L, L, E, C, T, I, O, N, S,//ALPHA_SWORD_COLLECTIONS,
	H, E, L, M, SPC, C, O, L, L, E, C, T, I, O, N, S,//ALPHA_HELM_COLLECTIONS,
	A, R, M, O, R, SPC, C, O, L, L, E, C, T, I, O, N, S,//ALPHA_ARMOR_COLLECTIONS,
	P, A, N, T, S, SPC, C, O, L, L, E, C, T, I, O, N, S,//ALPHA_PANTS_COLLECTIONS,
	G, L, O, V, E, SPC, C, O, L, L, E, C, T, I, O, N, S,//ALPHA_GLOVE_COLLECTIONS,
	B, O, O, T, S, SPC, C, O, L, L, E, C, T, I, O, N, S,//ALPHA_BOOTS_COLLECTIONS,
	C, R, E, W, S,//ALPHA_CREWS,
	L, E, A, D, E, R, B, O, A, R, D,//ALPHA_LEADERBOARD,
	F, R, I, E, N, D, S,//ALPHA_FRIENDS,
	I, N, V, I, T, E, SPC, F, R, I, E, N, D, S,//ALPHA_INVITE_FREINDS,
	R, E, W, A, R, D, SPC, C, A, L, L, E, N, D, A, R,//ALPHA_REWARD_CALLENDER,
	S, E, T, T, I, N, G,//ALPHA_SETTING,
	C, O, L, L, E, C, T, I, O, N, S,//ALPHA_COLLECTIONS
	C, O, M, P, L, E, T, E, D,//ALPHA_COMPLETED

	N, O, R, M, A, L,//ALPHA_GRADE_NORMAL
	S, U, P, E, R, I, O, R,//ALPHA_GRADE_SUPERIOR
	R, A, R, E,//ALPHA_GRADE_RARE
#ifdef SETITEM
	S, E, T,//ALPHA_GRADE_SET
#endif
	E, P, I, C,//ALPHA_GRADE_EPIC
	L, E, G, E, N, D,//ALPHA_GRADE_LEGEND

	D, E, F,//ALPHA_DEF
	P, A, G, E,//ALPHA_PAGE
	M, E, D, A, L,//ALPHA_MEDAL
	M, A, I, L,//ALPHA_MAIL
	F, R, E, E,//ALPHA_FREE
	D, U, N, G, E, O, N,//ALPHA_DUNGEON
	A, R, B, E, I, T,//ALPHA_ARBEIT
	B, O, S, S,//ALPHA_BOSS
	B, O, S, S, R, A, I, D,//ALPHA_BOSSRAID
	B, O, S, S, D, M, G,//ALPHA_BOSSDMG
	T, R, A, D, E,//ALPHA_TRADE
	H, I, R, E, D,//ALPHA_HIRED

	C, U, R, R, E, N, T,//ALPHA_CURRENT
	U, S, E, R, SPC, I, N, F, O,//ALPHA_USERINFO
	C, L, A, S, S,//ALPHA_CLASS
	N, I, C, K, N, A, M, E,//ALPHA_NICKNAME

	S, T, A, G, E,//ALPHA_STAGE
	S, T, A, G, E, SPC, C, L, E, A, R,//ALPHA_STAGECLEAR
	S, T, A, G, E, SPC, F, A, I, L, E, D,//ALPHA_STAGEFAILED
	N, E, W, SPC, S, T, A, G, E,//ALPHA_NEWSTAGE
	B, A, S, E,//ALPHA_BASE
	R, A, N, K, I, N, G,//ALPHA_RANKING
	I, N, T, E, R, E, S, T,//ALPHA_INTEREST
	R, E, M, A, I, N, E, D,//ALPHA_REMAINED

	B, I, G, SPC, P, I, X, E, L,//ALPHA_BIGPIXEL
	D, A, M, A, G, E, SPC, B, I, G, SPC, B, A, N, G,//ALPHA_DAMAGEBIGBANG

	C, O, N, N, E, C, T, I, N, G, SPC, T, O, SPC, S, E, R, V, E, R, DOT, DOT,//ALPHA_CONNECTINGTOSERVER
	C, H, E, C, K, I, N, G, SPC, V, E, R, S, I, O, N, DOT, DOT,//ALPHA_CHEKINGVERSION
	L, O, A, D, I, N, G, SPC, D, A, T, A, DOT, DOT,//ALPHA_LOADINGDATA
	A, U, T, O,//ALPHA_AUTO

	A, B, S, O, R, B,//ALPHA_ABSORB
	E, V, A, S, I, O, N,//ALPHA_EVASION
	N, O, T, I, C, E,//ALPHA_NOTICE

	F, I, R, E, SPC, R, E, G, I, S, T,//ALPHA_FIREREGIST
	F, R, O, S, T, SPC, R, E, G, I, S, T,//ALPHA_FROSTREGIST
	T, H, U, N, D, E, R, SPC, R, E, G, I, S, T,//ALPHA_THUNDERREGIST
	H, O, L, Y, SPC, R, E, G, I, S, T,//ALPHA_HOLYREGIST
	D, A, R, K, SPC, R, E, G, I, S, T,//ALPHA_DARKREGIST
	F, I, R, E, SPC, A, T, T, A, C, K,//ALPHA_FIREATTACK
	F, R, O, S, T, SPC, A, T, T, A, C, K,//ALPHA_FROSTATTACK
	T, H, U, N, D, E, R, SPC, A, T, T, A, C, K,//ALPHA_THUNDERATTACK
	H, O, L, Y, SPC, A, T, T, A, C, K,//ALPHA_HOLYATTACK
	D, A, R, K, SPC, A, T, T, A, C, K,//ALPHA_DARKATTACK

	C, O, N, G, R, A, T, U, L, A, T, I, O, N, S, //ALPHA_CONGRATULATIONS

	N, E, W, SPC, G, A, M, E,//ALPHA_NEWGAME
	M, A, X, SPC, G, A, M, E,//ALPHA_MAXGAME

	N, O, R, M, A, L, A, I,//ALPHA_NORMAL
	F, U, L, L, A, I,//ALPHA_FULLAI
	T, O, G, G, L, E,//ALPHA_TOGGLE
	S, W, I, P, E,//ALPHA_SWIPE
	A, I,//ALPHA_AI
	M, A, N, U, A, L,//ALPHA_MANUAL

	F, R, O, M, SPC, O, N, E,//ALPHA_FROMONE
	F, R, O, M, SPC, T, E, N,//ALPHA_FROMTEN

	C, U, T, O, F, F,//ALPHA_CUTOFF
	O, U, T,//ALPHA_OUT
	H, E, A, D,//ALPHA_HEAD
	E, F, F, E, C, T,//ALPHA_EFFECT
	B, I, G, N, U, M,//ALPHA_DMGNUM

	A, T, K,//ALPHA_ATK
	S, A, T, K,//ALPHA_SATK
	A, S, P, D,//ALPHA_ASPD
	S, P, D,//ALPHA_SPD
	M, R, S,//ALPHA_MRS
	G, R, A, D, E,//ALPHA_GRADE
	T, Y, P, E,//ALPHA_TYPE

	B, R, O, N, Z, E,//ALPHA_BRONZE
	S, I, L, V, E, R,//ALPHA_SILVER
	P, L, A, T, I, N, U, M,//ALPHA_PLATINUM
	D, I, A, M, O, N, D,//ALPHA_DIAMOND
	C, H, A, L, L, E, N, G, E, R,//ALPHA_CHALLENGER
	H, E, R, O,//ALPHA_HERO
	L, E, G, E, N, D,//ALPHA_LEGEND
	G, R, A, N, D, SPC, M, A, S, T, E, R,//ALPHA_GRANDMASTER
	C, H, A, M, P, I, O, N,//ALPHA_CHAMPION
	G, R, A, N, D, SPC, C, H, A, M, P, I, O, N,//ALPHA_GRANDCHAMPION

	T, I, E, R,//ALPHA_TIER
	R, E, S, E, T,//ALPHA_RESET

	C, H, A, L, L, E, N, G, E,//ALPHA_CHALLENGE
	L, A, B,//ALPHA_LAB
	S, O, C, I, A, L,//ALPHA_SOCIAL
	B, A, T, T, L, E,//ALPHA_BATTLE

	F, R, E, E, SPC, P, A, S, S,//ALPHA_FREEPASS
	R, O, Y, A, L, SPC, P, A, S, S,//ALPHA_ROYALPASS

	T, R, A, I, N, I, N, G,//ALPHA_TRAINING

	L, O, G,//ALPHA_LOG
	S, P, E, E, D,//ALPHA_SPEED
	M, A, C, R, O,//ALPHA_MACRO

	G, R, E, E, N,//ALPHA_GREEN
	B, L, U, E,//ALPHA_BLUE
	P, U, R, P, L, E,//ALPHA_PURPLE

	C, H, E, S, T,//ALPHA_CHEST
	R, A, I, D,//ALPHA_RAID

	Y, O, U, SPC, W, I, N, SPC, EXCLAMATIONMARK,//ALPHA_YOUWIN
	T, A, B, SPC, T, O, SPC, C, O, L, L, E, C, T,//ALPHA_TABTOCOLLECT
	T, A, B, SPC, T, O, SPC, S, T, A, R, T,//ALPHA_TABTOSTART

	M, I, S, S,//ALPHA_MISS
	G, O, O, D,//ALPHA_GOOD
	G, R, E, A, T,//ALPHA_GREAT
	P, E, R, F, E, C, T,//ALPHA_PERFECT

	Y, O, U, SPC, G, O, T, SPC, A,//ALPHA_YOUGOTA
	N, E, W, SPC, EXCLAMATIONMARK,//ALPHA_NEW
	N, E, W, SPC, C, A, R, D, SPC, EXCLAMATIONMARK,//ALPHA_NEWCARD

	R, A, N, D, O, M, //ALPHA_RANDOM

	C, O, I, N,//ALPHA_COIN

	G, O, T, SPC, A, SPC, C, R, E, W,//ALPHA_GOTACREW

	P, U, L, L,//ALPHA_PULL
	S, T, O, P,//ALPHA_STOP

	C, L, E, A, R,//ALPHA_CLEAR

	B, O, S, S, SPC, D, U, E, L,//ALPHA_BOSSDUEL
	S, T, A, R, T,//ALPHA_START

	U, P,//ALPHA_UP
	C, A, S, T, L, E,//ALPHA_CASTLE
	H, I, T,//ALPHA_HIT
	D, A, Y,//ALPHA_DAY
	L, I, F, E,//ALPHA_LIFE

	B, O, S, S, SPC, S, U, M, M, O, N, SPC, I, N,//ALPHA_BOSS_SUMMON_IN

	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	A, A,
	A, B,
	A, C,
	A, D,
	A, E,
	A, F,
	A, G,
	A, H,
	A, I,
	A, J,
	A, K,
	A, L,
	A, M,
	A, N,
	A, O,
	A, P,
	A, Q,
	A, R,
	A, S,
	A, T,
	A, U,
	A, V,
	A, W,
	A, X,
	A, Y,
	A, Z,
	B, A,
	B, B,
	B, C,
	B, D,
	B, E,
	B, F,
	B, G,
	B, H,
	B, I,
	B, J,
	B, K,
	B, L,
	B, M,
	B, N,
	B, O,
	B, P,
	B, Q,
	B, R,
	B, S,
	B, T,
	B, U,
	B, V,
	B, W,
	B, X,
	B, Y,
	B, Z,
	C, A,
	C, B,
	C, C,
	C, D,
	C, E,
	C, F,
	C, G,
	C, H,
	C, I,
	C, J,
	C, K,
	C, L,
	C, M,
	C, N,
	C, O,
	C, P,
	C, Q,
	C, R,
	C, S,
	C, T,
	C, U,
	C, V,
	C, W,
	C, X,
};


const unsigned short alphaX[TOTALALPHA * 12] = {
	//알파벳 26개, COLON,SLA,PLUS,MINUS,STAR,POUND,PER,PAR_L,PAR_R,DOT
	//FONT_SMALL
	0 * _2X, 6 * _2X, 12 * _2X, 18 * _2X, 24 * _2X, 30 * _2X, 36 * _2X, 42 * _2X, 48 * _2X, 53 * _2X, 59 * _2X, 65 * _2X, 71 * _2X, 78 * _2X, 84 * _2X, 90 * _2X, 96 * _2X, 102 * _2X, 108 * _2X, 114 * _2X, 121 * _2X, 127 * _2X, 134 * _2X, 141 * _2X, 148 * _2X, 155 * _2X, 161 * _2X, 164 * _2X, 168 * _2X, 175 * _2X, 182 * _2X, 189 * _2X, 196 * _2X, 201 * _2X, 205 * _2X, 209 * _2X, 212 * _2X,
	6 * _2X, 6 * _2X, 6 * _2X, 6 * _2X, 6 * _2X, 6 * _2X, 6 * _2X, 6 * _2X, 5 * _2X, 6 * _2X, 6 * _2X, 6 * _2X, 7 * _2X, 6 * _2X, 6 * _2X, 6 * _2X, 6 * _2X, 6 * _2X, 6 * _2X, 7 * _2X, 6 * _2X, 7 * _2X, 7 * _2X, 7 * _2X, 7 * _2X, 6 * _2X, 3 * _2X, 4 * _2X, 7 * _2X, 7 * _2X, 7 * _2X, 7 * _2X, 5 * _2X, 4 * _2X, 4 * _2X, 3 * _2X, 3 * _2X,
	//FONT_LARGE
	0 * _2X, 10 * _2X, 19 * _2X, 28 * _2X, 37 * _2X, 46 * _2X, 55 * _2X, 65 * _2X, 75 * _2X, 81 * _2X, 89 * _2X, 99 * _2X, 108 * _2X, 118 * _2X, 128 * _2X, 138 * _2X, 147 * _2X, 157 * _2X, 167 * _2X, 176 * _2X, 185 * _2X, 195 * _2X, 206 * _2X, 218 * _2X, 228 * _2X, 237 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 104 * _2X, 0 * _2X,
	10 * _2X, 9 * _2X, 9 * _2X, 9 * _2X, 9 * _2X, 9 * _2X, 10 * _2X, 10 * _2X, 6 * _2X, 8 * _2X, 10 * _2X, 9 * _2X, 10 * _2X, 10 * _2X, 10 * _2X, 9 * _2X, 10 * _2X, 10 * _2X, 9 * _2X, 9 * _2X, 10 * _2X, 11 * _2X, 12 * _2X, 10 * _2X, 9 * _2X, 9 * _2X, 7 * _2X, 7 * _2X, 7 * _2X, 7 * _2X, 7 * _2X, 7 * _2X, 7 * _2X, 7 * _2X, 7 * _2X, 3 * _2X, 7 * _2X,
	//FONT_SMALL2
	0 * _2X, 65 * _2X, 70 * _2X, 75 * _2X, 4 * _2X, 80 * _2X, 8 * _2X, 12 * _2X, 16 * _2X, 95 * _2X, 18 * _2X, 85 * _2X, 22 * _2X, 27 * _2X, 32 * _2X, 56 * _2X, 109 * _2X, 36 * _2X, 40 * _2X, 90 * _2X, 44 * _2X, 99 * _2X, 103 * _2X, 48 * _2X, 60 * _2X, 52 * _2X, 0 * _2X, 0 * _2X, 116 * _2X, 124 * _2X, 129 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 3 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 6 * _2X, 6 * _2X, 5 * _2X, 5 * _2X, 6 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 7 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	//FONT_NORMAL
	0 * _2X, 3 * _2X, 59 * _2X, 15 * _2X, 10 * _2X, 20 * _2X, 25 * _2X, 56 * _2X, 63 * _2X, 100 * _2X, 35 * _2X, 30 * _2X, 52 * _2X, 44 * _2X, 67 * _2X, 47 * _2X, 70 * _2X, 96 * _2X, 76 * _2X, 104 * _2X, 7 * _2X, 91 * _2X, 40 * _2X, 81 * _2X, 86 * _2X, 108 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 4 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 6 * _2X, 5 * _2X, 5 * _2X, 4 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 4 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 5 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
};

const signed short alpha2[TOTALALPHA * 6] = {
	//대문자 알파벳 26개, PLUS, MINUS, DOT
	//dx, dy, srcx, srcy, offsetx, offsety
	//A
	67, 82, 1, 97, 0, 0,
	//B
	65, 82, 74, 97, 0, 0,
	//C
	61, 82, 145, 97, 0, 0,
	//D
	64, 82, 212, 97, 0, 0,
	//E
	59, 82, 282, 97, 0, 0,
	//F
	59, 82, 347, 97, 0, 0,
	//G
	65, 82, 410, 97, 0, 0,
	//H
	64, 82, 480, 97, 0, 0,
	//I
	49, 82, 550, 97, 0, 0,
	//J
	58, 82, 602, 97, 0, 0,
	//K
	58, 82, 665, 97, 0, 0,
	//L
	54, 82, 729, 97, 0, 0,
	//M
	81, 82, 786, 97, 0, 0,
	//N
	62, 82, 1, 194, 0, 0,
	//O
	65, 82, 67, 194, 0, 0,
	//P
	62, 82, 136, 194, 0, 0,
	//Q
	66, 86, 202, 194, 0, 0,
	//R
	63, 82, 273, 194, 0, 0,
	//S
	62, 82, 340, 194, 0, 0,
	//T
	65, 82, 405, 194, 0, 0,
	//U
	65, 82, 474, 194, 0, 0,
	//V
	69, 82, 546, 195, 0, 0,
	//W
	100, 82, 621, 194, 0, 0,
	//X
	68, 82, 729, 194, 0, 0,
	//Y
	69, 82, 800, 194, 0, 0,
	//Z
	61, 82, 872, 194, 0, 0,

	//COLON
	0, 0, 0, 0, 0, 0,
	//SLA
	0, 0, 0, 0, 0, 0,
	//PLUS
	52, 53, 698, 15, 0, -16,
	//MINUS
	53, 21, 756, 31, 0, -32,
	//STAR
	0, 0, 0, 0, 0, 0,
	//POUND
	0, 0, 0, 0, 0, 0,
	//PER
	0, 0, 0, 0, 0, 0,
	//PAR_L
	0, 0, 0, 0, 0, 0,
	//PAR_R
	0, 0, 0, 0, 0, 0,
	//DOT
	22, 22, 669, 58, 0, -58,
	//SPC
	0, 0, 0, 0, 0, 0,
};

const unsigned short goldAlphaInfo[TOTALALPHA * 6 * 2] = {
	//dx, dy, srcx, srcy, offsetx, offsety,

	//알파벳 26개, COLON,SLA,PLUS,MINUS,STAR,POUND,PER,PAR_L,PAR_R,DOT
	//FONT_GOLD_SMALLf
	50,  41,  47,  43,  35,  34,  43,  41,  18,  27,  46,  31,  55,  44,  48,  40,  51,  44,  37,  36,  38,  49,  72,  51,  44,  44,  18,  18,  31,  27,  58,  45,  19,  22,  22,  17,  16,
	46,  46,  47,  46,  46,  46,  47,  46,  46,  46,  46,  46,  46,  46,  47,  46,  47,  46,  47,  46,  46,  46,  46,  46,  46,  46,  43,  24,  31,  16,  57,  45,  46,  58,  58,  17,  47,
	 1,  52,  94, 142, 186, 222, 257, 301, 343, 362, 390, 437,   1,  57, 102, 151, 192, 244, 289, 327, 364, 403,   1,  74, 126, 171, 211, 211, 277, 309,   1,  60, 432, 231, 254, 193, 393,
	 1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,  49,  49,  49,  49,  49,  49,  49,  49,  49,  49,  97,  97,  97,  98, 329, 348, 323, 331, 318, 318, 262, 313, 313, 348, 261,
	 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,

	 //FONT_GOLD_LARGE
	 51,  43,  41,  46,	 40,  37,  45,  47,  23,  26,  50,  40,  56,  45,  48,  43,  51,  46,  41,  42,  47,  47,  64,  47,  44,  40,  18,  18,  31,  27,  58,  45,  19,  22,  22,  17,  16,
	 41,  41,  43,  41,  42,  41,  43,  42,  42,  48,  42,  42,  42,  42,  44,  42,  53,  42,  44,  42,  43,  42,  43,  43,  43,  43,  43,  24,  31,  16,  57,  45,  46,  58,  58,  17,  47,
	  2,  53,  96, 138, 184, 224, 261, 306, 354, 377, 403, 453,  14,  71, 119, 167, 211, 262, 308, 349, 391, 438,  15,  79, 126, 171, 211, 211, 277, 309,   1,  60, 432, 231, 254, 193, 393,
	  3,   5,   2,   3,   2,   3,   2,   2,   2,   2,   2,   2,  56,  56,  55,  56,  55,  56,  55,  56,  56,  56, 114, 114, 114, 114, 329, 348, 323, 331, 318, 318, 262, 313, 313, 348, 261,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
};

const unsigned short alphaY[8] = { 27 * _2X, 16 * _2X, 27 * _2X, 58 * _2X, 7 * _2X, 11 * _2X, 7 * _2X, 9 * _2X };
#endif
