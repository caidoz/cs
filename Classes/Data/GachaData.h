#pragma once

#ifndef _DATA_GACHA_H_
#define _DATA_GACHA_H_

#include "../Def.h"

#ifdef TIERMAP

const unsigned short gachaRate[TOTALSTAR] = {
	0, 7000, 9500, 9900, 9990, 10000, 10000, 10000,
};
#else
const unsigned short gachaRate[8] = {
	//1,  2,  3,  4,  5, 6, 7, 8,
	//0, 20, 35, 30, 10, 5, 0, 0, 
	0, 5000, 8000, 9500, 9900, 10000, 10000, 10000,
	//0, 5000, 3000, 1500, 400, 100
};
#endif

const int miniGachaDetailRate[] = {
	//º°1, 2, 3, 4, 5, 6, 7, 8 
	9000, 900, 90, 9, 1, 0, 0, 0,
};
#endif