#pragma once
#include "../Def.h"

#ifndef _DATA_FONT_H_
#define _DATA_FONT_H_

const unsigned short goldNumData[10 * 6] = {
	//dx, dy, srcx, srcy, offsetx, offsety,

	//0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	 41,  25,  34,  35,  40,  37,  38,  37,  40,  39,
	 39,  39,  37,  37,  37,  38,  40,  38,  37,  37,
	348,  10,  37,  72, 110, 150, 189, 228, 266, 307,
	290, 290, 290, 290, 290, 290, 290, 291, 291, 291,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,

};

const unsigned short largeNumData[10 * 4] = {
	//LARGE
	1, 28, 45, 74, 103, 132, 163, 190, 217, 246,
	13 * _2X, 8 * _2X, 14 * _2X, 14 * _2X, 14 * _2X, 15 * _2X, 13 * _2X, 13 * _2X, 14 * _2X, 13 * _2X,
	0 * _2X, 1 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

const unsigned short mediumNumData[10 * 4] = {
	//MEDIUM
	1, 20, 33, 54, 73, 92, 113, 132, 149, 168,
	9 * _2X, 6 * _2X, 10 * _2X, 9 * _2X, 9 * _2X, 10 * _2X, 9 * _2X, 8 * _2X, 9 * _2X, 9 * _2X,
	0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X,
	38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
};


#ifdef DMGINFOEFFECT
const signed char dmgInfoData[5 * DMGNUMFRAME] = {
	//Y이동폭
	//0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, -3 * _2X, -3 * _2X, -3 * _2X, -3 * _2X, 0 * _2X,
	-8 * _2X, -4 * _2X, -2 * _2X, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	//폰트 종류
	NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_LARGE_FORELIGHTEN, NUM_FONT_LARGE_BACKLIGHTEN, NUM_FONT_LARGE_BACKLIGHTEN2, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE,
	//NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE, NUM_FONT_LARGE,
	//투명도
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	//32, 32, 32, 32, 32, 26, 20, 14, 8,
};
#else
const signed char dmgInfoData[3 * DMGNUMFRAME] = {
	//Y이동폭
	//0 * _2X, 0 * _2X, 0 * _2X, 0 * _2X, -3 * _2X, -3 * _2X, -3 * _2X, -3 * _2X, 0 * _2X,
	0, 0, 0, 0, -1, -1, -1, -1, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	//폰트 종류
	NUM_FONT_LARGE_FORELIGHTEN, NUM_FONT_LARGE_BACKLIGHTEN, NUM_FONT_LARGE_BACKLIGHTEN2, NUM_FONT_LARGE, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL,
	NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL,
	NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL, NUM_FONT_NORMAL,
	//투명도
	32, 32, 32, 32, 32, 31, 30, 29, 28, 27,
	26, 25, 24, 23, 22, 21, 20, 19, 18, 17,
	16, 15, 14, 13, 12, 11, 10, 9, 8, 7,
};

#endif

//아이템 컬러 테이블
const signed char itemColorText[6] = {
	'b', 'e', 'd', 'i', 'g', 'h',
};

const signed short fontInfo[128] = {
	-128,	//0 : "Ctrl-@ NUL"
	-128,	//1 : "Ctrl-A SOH"
	-128,	//2 : "Ctrl-B STX"
	-128,	//3 : "Ctrl-C ETX"
	-128,	//4 : "Ctrl-D EOT"
	-128,	//5 : "Ctrl-E ENQ"
	-128,	//6 : "Ctrl-F ACK"
	-128,	//7 : "Ctrl-G BEL"
	-128,	//8 : "Ctrl-H BS"
	-128,	//9 : "Ctrl-I HT"
	-128,	//10 : "Ctrl-J LF"
	-128,	//11 : "Ctrl-K VT"
	-128,	//12 : "Ctrl-L FF"
	-128,	//13 : "Ctrl-M CR"
	-128,	//14 : "Ctrl-N SO"
	-128,	//15 : "Ctrl-O SI"
	-128,	//16 : "Ctrl-P DLE"
	-128,	//17 : "Ctrl-Q DCI"
	-128,	//18 : "Ctrl-R DC2"
	-128,	//19 : "Ctrl-S DC3"
	-128,	//20 : "Ctrl-T DC4"
	-128,	//21 : "Ctrl-U NAK"
	-128,	//22 : "Ctrl-V SYN"
	-128,	//23 : "Ctrl-W ETB"
	-128,	//24 : "Ctrl-X CAN"
	-128,	//25 : "Ctrl-Y EM"
	-128,	//26 : "Ctrl-Z SUB"
	-128,	//27 : "Ctrl-[ ESC"
	-128,	//28 : "Ctrl-\ FS"
	-128,	//29 : "Ctrl-] GS"
	-128,	//30 : "Ctrl-^ RS"
	-128,	//31 : "Ctrl_ US"
	-128,	//32 : "Space"
	0,	//33 : "!"
	1,	//34 : """
	2,	//35 : "#"
	3,	//36 : "$"
	4,	//37 : "%"
	5,	//38 : "&"
	26,	//39 : "'"
	7,	//40 : "("
	8,	//41 : ")"
	9,	//42 : "*"
	10,	//43 : "+"
	11,	//44 : ","
	12,	//45 : "-"
	13,	//46 : "."
	14,	//47 : "/"
	100,	//48 : "0"
	100,	//49 : "1"
	100,	//50 : "2"
	100,	//51 : "3"
	100,	//52 : "4"
	100,	//53 : "5"
	100,	//54 : "6"
	100,	//55 : "7"
	100,	//56 : "8"
	100,	//57 : "9"
	15,	//58 : ":"
	16,	//59 : ";"
	17,	//60 : "<"
	18,	//61 : "="
	19,	//62 : ">"
	20,	//63 : "?"
	30,	//64 : "@"
	110,	//65 : "A"
	110,	//66 : "B"
	110,	//67 : "C"
	110,	//68 : "D"
	110,	//69 : "E"
	110,	//70 : "F"
	110,	//71 : "G"
	110,	//72 : "H"
	110,	//73 : "I"
	110,	//74 : "J"
	110,	//75 : "K"
	110,	//76 : "L"
	110,	//77 : "M"
	110,	//78 : "N"
	110,	//79 : "O"
	110,	//80 : "P"
	110,	//81 : "Q"
	110,	//82 : "R"
	110,	//83 : "S"
	110,	//84 : "T"
	110,	//85 : "U"
	110,	//86 : "V"
	110,	//87 : "W"
	110,	//88 : "X"
	110,	//89 : "Y"
	110,	//90 : "Z"
	21,	//91 : "["
	6,	//92 : "\"
	23,	//93 : "]"
	24,	//94 : "^"
	25,	//95 : "_"
	26,	//96 : "`"
	120,	//97 : "a"
	120,	//98 : "b"
	120,	//99 : "c"
	120,	//100 : "d"
	120,	//101 : "e"
	120,	//102 : "f"
	122,	//103 : "g"
	120,	//104 : "h"
	120,	//105 : "i"
	120,	//106 : "j"
	120,	//107 : "k"
	120,	//108 : "l"
	120,	//109 : "m"
	120,	//110 : "n"
	120,	//111 : "o"
	122,	//112 : "p"
	122,	//113 : "q"
	120,	//114 : "r"
	120,	//115 : "s"
	120,	//116 : "t"
	120,	//117 : "u"
	120,	//118 : "v"
	120,	//119 : "w"
	120,	//120 : "x"
	122,	//121 : "y"
	120,	//122 : "z"
	27,	//123 : "{"
	127,	//124 : "|"
	28,	//125 : "}"
	29,	//126 : "~"
	-128,	//127 : "DEL"
};
#endif