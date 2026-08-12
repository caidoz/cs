#pragma once

#ifndef _DEF_SOUND_H_
#define _DEF_SOUND_H_

typedef enum _musicDef {
	M_TITLE = 0,	//타이틀음악//0
	M_TOLEAVIL,	//톨레아마을//1
	M_TOLEASWAMP,	//톨레아습지//2
	M_VALLEY,	//금단의계곡//3
	M_ATLANTICE,	//아틀란티스//4
	M_ADELSEWAGE,	//아델지하도//5
	M_ADELCASTLE,	//아델라인성//6
	M_ADELPLAIN,	//아델라인평원//7
	M_ELFVIL,	//엘프마을//8
	M_FIRESPIRIT,	//불의정령//9
	M_ICESPIRIT,	//얼음의정령//10
	M_THUNDERSPIRIT,	//번개의정령//11
	M_LIGHTSPIRIT,	//빛의정령//12
	M_GOLEM,	//골렘의협곡//13
	M_DARKSPIRIT,	//어둠의정령//14
	M_DRAGON,	//드래곤의무덤//15
	M_DEADVIL,	//망자들의도시//16
	M_DEVIL,	//마왕성//17
	M_EVENT_EMERG,	//긴박한 이벤트//18
	M_EVENT_FUNNY,	//일반 및 유머이벤트//19
	M_EVENT_SAD,	//슬픈이벤트//20
	M_BOSS,	//보스와 만났을때 나오는 보스음악//21
	M_ENDING,	//엔딩//22

	M_ROULETTEUP,//룰렛이 돌아갈 때 나오는 삐비비빙 //23

	M_INN,	//여관에서 잘때 음악//24
	M_TALK,	//대화시에 나오는 타자기 소리//25
	M_RUN,	//달리기//26//
	M_SWORD,	//약검	//27
	M_SWORDSTRONG,//강검	//28
	M_GUN,//약총	//29
	M_GUNSTRONG,//강총	//30
	M_BOOMERANG,//약부메랑	//31
	M_BOOMERANGSTRONG,//강부메랑	//32
	M_SWORDHIT,//칼맞음			//33
	M_GUNHIT,//총맞음			//34
	M_BOOMERANGHIT,//부메랑맞음		//35
	M_RELOAD,//재장전	//36
	M_LASER,//레이저		//37
	M_FIRE,//화염방사기		//38
	M_BUFF_PINK,//핑크색버프	//39
	M_BUFF_YELLOW,//노란색버프	//40
	M_BUFF_BLUE,//파란색버프	//41
	M_BUFF_RED,//빨간색버프	//42
	M_BANG,//터지는소리	//43
	M_ENEMYDEAD,	//적이 죽을 때 나는 소리(?)	//44
	M_KUNG,	//거대몬스터가 점프했다가 떨어지거나~(쿵)	//45
	M_OPENDOOR,	//문열때 나는 소리	//46
	M_ITEM,	//아이템 이용시 소리//47(삐링)
	M_LEVELUP,	//레벨업 및 퀘스트 중요 아이템등 창이 떠서 뭔가를 얻거나 완료할때 등	//48(짧은 빵파레)
	M_DOWN,//휙 떨어질때//49
	M_DRUM_GOOD,//북소리 두둥//50
	M_DRUM_PERFECT,//북소리 타닥//51
	M_HEART,//심장두근두근//52
	M_COIN,//53
	M_SELECT,//54
	M_ERROR,//55
	M_BUTTON,//56
	M_JUMP,//57
	M_NEW,//58
	M_WARP,//59
	M_MACHINE,//60
	M_IRON,//61
	M_OPENWINDOW,//62
	M_CLOSEWINDOW,//63
	M_POWERUP,//64
	M_LASER2,//65
	M_CARDSPLIT,//66
	M_CHEER,//67
	M_CASHIER,//68
	M_EMERGENCY,//69

	M_JOYSTICK,//70
	M_SHAKIN,//71

	/*
	M_V0,//70
	M_V1,//71
	M_V2,//72
	M_V3,//73
	M_V4,//74
	M_V5,//75
	M_V6,//76
	M_V7,//77
	M_V8,//78
	M_V9,//79
	M_V10,//80
	M_V11,//81
	M_V12,//82
	M_V13,//83
	M_V14,//84
	M_V15,//85
	M_V16,//86
	M_V17,//87
	M_V18,//88
	M_V19,//89
	M_V20,//90
	M_V21,//91
	M_V22,//92
	M_V23,//93
	M_V24,//94
	M_V25,//95
	M_V26,//96
	M_V27,//97
	M_V28,//98
	M_V29,//99
	*/

	TOTALMUSIC,

	EFFECTSOUND_NORMAL = 0,
	EFFECTSOUND_DASH,
	EFFECTSOUND_AIR,
	EFFECTSOUND_DOWN,
	EFFECTSOUND_AFTERDOWN,
	EFFECTSOUND_SKILL,

	END_MUSICDEF
} MUSICDEF;
#endif
