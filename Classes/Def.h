#pragma once

#ifndef _DEF_H_
#define _DEF_H_


// ================================
// ºÐ¸®µÈ ¼³Á¤ ÆÄÀÏµé include
// ================================
#include "Config/BuildConfig.h"
#include "Config/GameConstants.h"
#include "Config/RenderConstants.h"
#include "Config/FileConstants.h"
#include "Config/TimeConstants.h"
#include "Config/GameConfig.h"


#include "Def/TimeDef.h"
#include "Def/AlphaDef.h"
#include "Def/AttackSequenceDef.h"
#include "Def/CastleDef.h"
#include "Def/CmfDef.h"
#include "Def/ColorDef.h"
#include "Def/CrewDef.h"
#include "Def/DemoDef.h"
#include "Def/EnemyDef.h"
#include "Def/EventDef.h"
#include "Def/HandlerDef.h"
#include "Def/IconDef.h"
#include "Def/MapDef.h"
#include "Def/ObjectDef.h"
#include "Def/ItemDef.h"
#include "Def/ImgDef.h"
#include "Def/NumDef.h"
#include "Def/QuestDef.h"
#include "Def/RouletteDef.h"
#include "Def/SkillDef.h"
#include "Def/SoundDef.h"
#include "Def/StatDef.h"
#include "Def/StatusDef.h"
#include "Def/TextDef.h"
#include "Def/TouchKeyDef.h"
#include "Def/TutoralDef.h"
#include "Def/UIDef.h"

//#ifdef NULL
//#undef NULL
//#endif

//#define NULL 0


//ë§¤í¬ë¡?

/*
hexcolor to rgb & rgb to hexcolor
int r = ( hexcolor >> 16 ) & 0xFF;
int g = ( hexcolor >> 8 ) & 0xFF;
int b = hexcolor & 0xFF;
int hexcolor = (r << 16) + (g << 8) + b;
*/
#define Abs(a)			((a < 0) ? - (a) : (a))
#define Max(a, b)		(((a) > (b)) ? (a) : (b))
#define Min(a, b)		(((a) < (b)) ? (a) : (b))
//#define DIR(a)			((a == 0) ? -1 : 1)
#define DIR(a)			(((a) << 1) - 1)
#define GetSkillLv(obj, a)		(Min(15, (ao[obj].skillLv[a] == 0 ? 0 : ao[SKILL_DIANA1].skillLv[a] + ao[obj].ps[PS_SKILL])))
#define GetSkillValue(obj, a)	(ao[obj].skillLv[a] == 0 ? 0 : GetSkillLv(obj, a) + 10)

#define LOCALSAVE
#ifndef LOCALSAVE
#define SEVERSAVE
#endif

#define TEXTPTR(b)		((textId[b]))

#define DEFENSEGAME
//#define ATTACKEDINVINCIBLE
//#define SPEEDTURN
#define ENEMYHPBAR
#define GUIDELINE
//#define MAPTEST

//#define INVINCIBLE

//#define LOCALPUSH
//#define COSTUMETEST


//30ºÐ ±âÁØ(ÇÏÆ® ÇÏ³ª´ç 30ºÐ¸¶´Ù ÇÏ³ª¾¿ Âù´Ù°í º¸¸é µÊ)
#define HEARTPER	10
#define NEWITEMMARKSHOW
#define COINPER	10
#define QUESTPER	5
#define MAXBET	5
#define MAXCOINBET	5

#define MAXNUM	2147483647

#define SOCKET

#define FRAMEPER	1

#define RELEASEEXEC

#define LOG_COUNT		5

#define GOLDBARLEFTUP

#define WEAPONABSOLUTE
#define HELMABSOLUTE
#define HEARTABSOLUTE
//#define SKILLABSOLUTE
#define QUESTABSOLUTE
#define BATTLEABSOLUTE
#define RAIDABSOLUTE
#define EQUIPSKILL

#define NOMISS
//GotoObj or GotoObjXY°¡ ÀÛµ¿ÇÏ±â À§ÇÑ ÃÖ¼Ò°ª
#define SPEED_MIN	4
#define DAYS3 3 * 24 * 60 * 60 * 1000 // 3ÀÏ
#define JOYKNOBMAX	42 * _2X

#define CARDDEFAULTZOOM		0.6f
//#define NUMTTF
//#define INITPOPUP

typedef enum _reel {
	SLOTSIZE_X = 512,
	SLOTSIZE_Y = 218,

	CHAINLOCK_W = 479,
	CHAINLOCK_H	= 215,
	LOCK_W = 145,
	LOCK_H = 169,

	REELSIZE_X = 156,
	REELSIZE_Y = 290,

	REEL_BG_NORMAL = 0,   // ÀÏ¹Ý(Á¤Áö/Àú¼Ó/È®Á¤)
	REEL_BG_MASK = 1,    // °¡¸²(Áß¼Ó/°¨¼ÓB)
	REEL_BG_FAST = 2,   // °í¼Ó(°í¼Ó/°¨¼ÓA)

	REEL_TOTAL_FRAME = 120,

	REEL_STATE_IDLE = 0,   // Á¤Áö(½ÃÀÛ Àü/Á¤Áö À¯Áö)
	REEL_STATE_SLOW,        // Àú¼Ó(°¡¼Ó ÃÊ¹Ý)
	REEL_STATE_MID,        // Áß¼Ó
	REEL_STATE_FAST,       // °í¼Ó(Àü±â È¿°ú ON)
	REEL_STATE_DECEL,      // °¨¼Ó
	REEL_STATE_SNAP        // È®Á¤ ½º³À ÇÁ·¹ÀÓ
} REEL;

typedef enum _stageInfo {
	STAGEINFO_CREWDROP = 0,
	STAGEINFO_CREWGACHA,
	STAGEINFO_STAGECLEAR,
	STAGEINFO_NEWSTAGE,

	TOTAL_STAGEINFO,

	STAGELISTINFO_NORMAL = 0,
	STAGELISTINFO_LEAVE,
	STAGELISTINFO_GOING,
	STAGELISTINFO_ARRIVE,

	TOTAL_STAGELISTINFO,



} STAGEINFO;




typedef enum _turnRpgInfo {
	HERE = 0,
	GOING = 1,
	THERE = 2,
	COMING = 3,
	DMGUPDATE = 4,
	NEXTROOM = 5,

	ATTACKPATTERNDATASIZE = 6,
	ATTACKPATTERNTOTALDATASIZE = 6 * 3 + 2,

	WIDEAREAWIDTH = 128 * _2X,

} TURNRPGINFO;

typedef enum _controlMode {
	CONTROL_MANUAL = 0,
	CONTROL_AUTO,
	CONTROL_AI,

	TOTAL_CONTROL_TYPE,

} CONTROLMODE;

//#define TIERREWARDS
typedef enum _rewardType {
	REWARD_CURRENCY = 0,
	REWARD_ITEM,
	REWARD_SKILL,

	TOTAL_REWARD_TYPE,

} REWARDTYPE;



//#define ENGLISHOPTION
typedef enum _language {
	LANGUAGE_KOREAN = 0,//ÇÑ±¹¾î
	LANGUAGE_ENGLISH,//¿µ¾î
	LANGUAGE_JAPAN,//ÀÏ¾î

	TOTAL_LANGUAGE,
} LANGUAGE;

typedef enum _login {
	LOGIN_FACEBOOK = 0,
	LOGIN_GOOGLE,
	LOGIN_APPLE,
	LOGIN_GUEST,

	TOTAL_LOGIN,
} LOGIN;

typedef enum _tip {
	TIP_INTRODUCE = 0,//¼Ò°³
	TIP_GAMEPLAY,
	TIP_STAGEREWARD,
	TIP_SKILL,
	TIP_ITEMS,
	TIP_RANK1,
	TIP_RANK23,
	TIP_RANK10,
	TIP_YAK,
	TIP_BOSS1,
	TIP_BOSS2,
	TIP_BOSS3,
	TIP_BOSS4,
	TIP_BOSS5,
	TIP_BOSS6,
	TIP_BOSS7,
	TIP_BOSS8,
	TIP_BOSS9,
	TIP_BOSS10,
	TIP_BOSS11,
	TIP_BOSS12,
	TIP_BOSS13,
	TIP_BOSS14,
	TIP_BOSS15,
	TIP_BOSS16,
	TIP_BOSS17,
	TIP_BOSS18,
	TIP_BOSS19,
	TIP_SOLDIER,
	TIP_GAMEOVERREWARD,
	TIP_STATE,

	TIP_OPENING1,
	TIP_OPENING2,
	TIP_OPENING3,
	TIP_OPENING4,

	TOTALTIP,
};

typedef enum _BATTLEMODE_DEF {
	TOTALBATTLECHANCE = 1,

	END_BATTLEMODE
};

typedef enum _RAID_DEF {
	RAIDSKILLSLOT = 12,

	TOTALRAIDCHANCE = 3,

	END_RAID
} RAIDS;

typedef enum _gameDef {
	FIRE = 1,
	FROST,
	THUNDER,
	EARTH,
	HOLY,
	DARK,

	LEVELUPTERM = 1,
	LVUP_HP = 10,
	LVUP_MP = 5,
	LVUP_AP = 4,
	LVUP_SP = 1,

	LVUP_STR = 5,
	LVUP_AGI = 3,
	LVUP_INT = 2,
	LVUP_CRITICAL = 2,
	LVUP_SKILLDMG = 2,

	DEFAULT_EXPS = 1,

	MAXUSERLEVEL = 150,

	IRONGOLDPER = 1,
	SHIELDPERHP = 2,
	MINSHIELD = 3,
	MAXSHIELD = 5,
	LVUP_MAX = 100,

	VIT_HP = 10,
	INT_MP = 5,

	GETHEARTAMOUNT = 10,
	GETHEARTSECONDS = 3600,

	TOUCH_NULL = 0,
	TOUCH_RELEASE,
	TOUCH_PRESS,
	TOUCH_DRAG,

	SCREEN1 = 0,    //1»çºÐ¸é
	SCREEN2,        //2»çºÐ¸é
	SCREEN3,        //3»çºÐ¸é

	SCREENDARKEN = 24,

	


	ACCEMAXLEVEL = 50,
	TOTALACCESTATTYPE = 6,

	//°ø°Ý»óÅÂ
	ATTACK_CRITICAL = 0,
	ATTACK_EXTRA,
	ATTACK_STUN,
	ATTACK_IGNORE,
	ATTACK_KNOCKBACK,
	ATTACK_PIERCE,
	ATTACK_MISS,
	ATTACK_BLOCK,
	ATTACK_DODGE,

	//»óÅÂÀÌ»ó
	SLOW = 0,	//½½·Î¿ì->°ø°ÝÅ¸ÀÌ¹ÖÀÌ 2¹è·Î ´Ã¾îÁü
	BLIND,	//ºí¶óÀÎµå(¹Ì½º°¡ ¸¹ÀÌ ³²)->¹Ì½º 100% °É¸²
	POISON,	//µ¶->ÅÏ¸¶´Ù µ¶µ¥¹ÌÁö¸¦ ¹ÞÀ½
	STUN,	//±âÀý->1ÅÏµ¿¾È °ø°ÝÀ» ¸øÇÔ
	CURSE,	//ÀúÁÖ(MP¸¦ »ç¿ë¸øÇÔ)->°ø°ÝÀ» ¸øÇÔ
	KNOCKBACK,	//¹Ð¾î³»±â? ÀÌ°Ç ¾µ ÇÊ¿ä°¡ ¾øÀ»µí.(Á¦°Å)
	TOTALDEBUF,

	ATTRWORD = 101,
	ENEMYATTRDATASIZE = 12,



	POISONDMGPER = 2,
	DARKDMGPER = 5,
	PROCPER = 100,

	//ê°•í™”?¨ê³¼
	//ë¡œë¹ˆ
	INC_VIT = 0,//INC_VIT	= 0,	//¹æ¾îÅÂ¼¼ : ÀÏÁ¤½Ã°£ VIT »ó½Â->¼±ÅÃµÈ ÀûÀÇ µ¥¹ÌÁö¸¦ °¨¼Ò->Àû ¹æ¾î·Â °¨¼Ò 
	BARRIER,	//Á¤½Å¼Ò¸ð : MP ¼Ò¸ðÇÏ¿© µ¥¹ÌÁö °æ°¨->¾Æ±º ¹æ¾î·Â Áõ°¡
#ifdef SKILL_ROBIN15_DAMAGExN
	DAMAGExN,	//µ¥¹ÌÁöN¹è
#else
	HPRESTORE,//,	//¿©À¯Æ÷Âø : Àû °ø°Ý È¸ÇÇ½Ã HP »ó½Â->ÀÏÁ¤ÅÏµ¿¾È Àû °ø°ÝÈ¸ÇÇ
#endif	
	MPRESTORE,	//³ÃÁ¤Ä§Âø : µ¥¹ÌÁö ÀÔÀ¸¸é MP È¸º¹
	REFLECTION,	//¸®ÇÃ·º¼Ç : ÇÑÅÏ µ¥¹ÌÁö ¹Ý»ç

	//?”ì•„??
	BERSERK,	//ÈïºÐ°íÁ¶ : ¹æ¾î·Â ÀúÇÏ °ø°Ý·Â »ó½Â
	MPDRAIN,	//Èí¸¶ÀÇ¸¶Åº : °ø°Ý½Ã MP Èí¼ö->HP Èí¼ö·Î º¯°æ
	INC_CRITICAL,	//ÇÊ»ìÁýÁß : Å©¸® »ó½Â
	INC_IGNORE,	//ÆÄ¸¶ÀÇÁ÷°Ý : ÀÏÁ¤½Ã°£ Àû ¹æ¾î ¹«½Ã

	//ë§¥ìŠ¤
	HPDRAIN,	//ºí·¯µåÇåÆ® : Àû °ø°Ý½Ã HP È¸º¹
	INC_EVASION,	//Çö¶õ¹«µµ : ÀÏÁ¤½Ã°£ È¸ÇÇÀ² Áõ°¡, ÇÑÅÏ ±×³É È¸ÇÇ
#ifdef SKILL_MAXX16_ERASEALLDEBUF 
	EVASIONTOHP,	//¾ÈµµÀÇÇÑ¼û : Àû °ø°Ý È¸ÇÇ½Ã HP È¸º¹
#else
	EVASIONTOMP,	//¾ÈµµÀÇÇÑ¼û : Àû °ø°Ý È¸ÇÇ½Ã MP È¸º¹. È¸ÇÇÇÏ¸é Ã¼·Â È¸º¹
#endif
	INC_STUN,	//È¥½ÅºÐ¸® : ±âÀý È®·ü »ó½Â

	TOTALPLAYERBUFF,

	//¹ÝÁö
	INC_DAMAGE_RING = TOTALPLAYERBUFF,	//°ø°Ý·Â Áõ°¡ : ÆøÁÖÀÇ ¹ÝÁö
	INC_DEFENSE_RING,	//¹æ¾îµµ Áõ°¡ : °ñ·½ÀÇ ¹ÝÁö
	INC_EVASION_RING,	//È¸ÇÇ Áõ°¡ : ±¤´ëÀÇ ¹ÝÁö
	INC_PIERCE_RING,	//°üÅë Áõ°¡ : ¿øÇÑÀÇ ¹ÝÁö
	INC_HIT_RING,	//ÀûÁß Áõ°¡ : ½Å³äÀÇ ¹ÝÁö
	INC_STUN_RING,	//±âÀý°ø°Ý Áõ°¡ : ±¤Æ÷ÀÇ ¹ÝÁö
	INC_CRITICAL_RING,	//Ä¡¸íÅ¸ Áõ°¡ : ½ÂÀÚÀÇ ¹ÝÁö
	INC_CRITDMG_RING,	//Ä¡¸íÅ¸ µ¥¹ÌÁö Áõ°¡ : ±Ã±ØÀÇ ¹ÝÁö
	INC_IGNORE_RING,	//Àû ¹æ¾îµµ ¹«½Ã Áõ°¡ : Â÷¿øÀÇ ¹ÝÁö
	INC_EXP_RING,	//°æÇèÄ¡ È¹µæ Áõ°¡ : Çà¿îÀÇ ¹ÝÁö(»ç¿ë¾ÈÇÔ)
	INC_EXTRA_RING,	//Ãß°¡Å¸ Áõ°¡ : Çà¿îÀÇ ¹ÝÁö(»ç¿ë)
	INC_ABSORB_RING,	//¹°¸®µ¥¹ÌÁö Èí¼ö Áõ°¡ : È¸»ýÀÇ ¹ÝÁö(»ç¿ë)

	//ºñ¾à
	INC_DAMAGE_ARENA,
	INC_DEFENSE_ARENA,
	INC_MAGIC_ARENA,
	INC_SKILL_ARENA,

	TOTALBUFF,

	//È÷Æ®¸¶Å©
	HITMARK_SMALL = 0,
	HITMARK_MEDIUM,
	HITMARK_LARGE,
	HITMARK_EXTRA,
	HITMARK_PIERCE,
	//HITMARK_FULL,

	TOTALHITMARK = 100,

	ICONMARK_CURRENCY = 0,
	ICONMARK_ITEM,
	ICONMARK_CARD,
	ICONMARK_REWARD,
	ICONMARK_BOX,
	ICONMARK_BOXCARD,
	ICONMARK_SOUL,
	ICONMARK_GOLDALPHA,
	ICONMARK_CONTROLMARK,
	ICONMARK_CURRENCY_POPUP,

	TOTALICONMARKTYPE,

	//ÀçÈ­
	TOTALCURRENCYMARKARR = 10,
	TOTALCURRENCYMARK = 100,
	CURRENCYMOVESPEED = 16 * _2X,
	CURRENCYMARKEFFECTFRAME = FPS / 2,
	CURRENCYDONTERASE = 10000,
	//¾ÆÀÌÅÛ
	TOTALITEMMARK = 30,

	SKILLPERSWORD = 12,
	ACTIONCARDDATASIZE = 9,
	SWORDSKILLINFODATASIZE = 3,


	//½ºÅ³Å¸ÀÔ
	PASSIVE = 0,//ÀÏ¹Ý ÆÐ½Ãºê ½ºÅ³(ÇöÀç´Â ¾È¾²°í)
	ACTIVE,//ÀÏ¹Ý ¾×Æ¼ºê ½ºÅ³(ÇöÀç´Â ¾È¾²°í)
	CREWBULLET,//ÃÑÅº °ø°Ý
	SUMMON,//¼ÒÈ¯
	HEROSKILL,//È÷¾î·ÎÀÇ ½ºÅ³À» È£Ãâ
	SUMMONHERO,//ÁÖÀÎ°ø »©°í ´Ù¸¥ È÷¾î·Î ¼ÒÈ¯

	//Å©·ùÅ¸ÀÔ
	// 
	//ÀÏ¹Ý
	//Å©¸®Æ¼ÄÃ(µ¥¹ÌÁö 2¹è)
	//°üÅë°ø°Ý(µÚ¿¡Àû±îÁö °ø°Ý)
	//Ãß°¡Å¸°Ý(µ¥¹ÌÁö)

	//»ó´ë¹æ ½ºÅÏ(1ÅÏ)
	//Áßµ¶°É±â(3ÅÏ°£ Áßµ¶ µ¥¹ÌÁö)
	//¼®È­(1ÅÏ, ¸ØÃßµÇ 1ÅÏ µ¿¾È °ø°ÝÀ» ¹ÞÁö ¾ÊÀ½ Áï ÀÌ·²¶§´Â ¹öÇÁ·ù·Î µ¹¸®´Â°Ô ÁÁÀ½) 

	//È­¿°ÀúÇ×·Â(¼¼°³ ¶ß¸é µ¥¹ÌÁö 1)
	//³Ã±âÀúÇ×·Â(¼¼°³ ¶ß¸é µ¥¹ÌÁö 1)
	//¹ø°³ÀúÇ×·Â(¼¼°³ ¶ß¸é µ¥¹ÌÁö 1)
	//½Å¼ºÀúÇ×·Â(¼¼°³ ¶ß¸é µ¥¹ÌÁö 1)
	//¾ÏÈæÀúÇ×·Â(¼¼°³ ¶ß¸é µ¥¹ÌÁö 1)

	//°ñµåÈ¹µæ Áõ°¡(È¹µæ °ñµå 2¹è ÄÉÀÌ½º¿Í È¹µæ °ñµå +1000 µî)
	//°Ë °ø°Ý·Â Ãß°¡
	//È­¿°°ø°Ý·Â(¼¼°³ ¶ß¸é µ¥¹ÌÁö µÎ¹è)
	//³Ã±â°ø°Ý·Â(¼¼°³ ¶ß¸é µ¥¹ÌÁö µÎ¹è)
	//¹ø°³°ø°Ý·Â(¼¼°³ ¶ß¸é µ¥¹ÌÁö µÎ¹è)
	//½Å¼º°ø°Ý·Â(¼¼°³ ¶ß¸é µ¥¹ÌÁö µÎ¹è)
	//¾ÏÈæ°ø°Ý·Â(¼¼°³ ¶ß¸é µ¥¹ÌÁö µÎ¹è)
	//¹æ¾î·Â ¹«½Ã °ø°Ý(¹æ¾î·ÂÀÌ ¾öÃ» °­ÇÑ ¸ó½ºÅÍ¸¦ µ¥¹ÌÁö¸¦ Áà¼­ ÇÑ¹æ¿¡ Á×ÀÓ)
	//È¸ÇÇ(ÇÑÅÏµ¿¾È µ¥¹ÌÁö¸¦ ¹ÞÁö ¾Ê´Â´Ù.)
	//µ¶¸é¿ª(3ÅÏµ¿¾È µ¶°ø°Ý¿¡ °É¸®Áö ¾Ê´Â´Ù.)
	//½ºÅÏ¸é¿ª(3ÅÏµ¿¾È ½ºÅÏ¿¡ °É¸®Áö ¾Ê´Â´Ù.)

	//·Îºó½ºÅ³-¿¡¾îÅ©·¡½¬ : °øÁßÀû¿¡°Ô µ¥¹ÌÁö 2¹è
	//·Îºó½ºÅ³-¸¶±¸Âî¸£±â
	//·Îºó½ºÅ³-ºÎ½ºÆ®½½·¡½Ã : ±âÀý(100% ±âÀý)
	//·Îºó½ºÅ³-ÇÏÀÌÆÛÂ÷Áö : µ¹°Ý°ø°Ý(ÀûÀ» µÚ·Î ³¯¸°´Ù°¡ ¹«½¼ ÀÇ¹Ì°¡ ÀÖÁö?
	//·Îºó½ºÅ³-¼Ò¿ïÅ©·¡½Ã : ÀÌ°Íµµ ±âÀýÀÌ¾ß?
	//·Îºó½ºÅ³-¾Û¼Ö·çÆ®ÇÇ¾î½º : Âñ·¯¼­ È¸Àü
	//·Îºó½ºÅ³-¸ê»ì¿¬Âü : ÃÖ°­µ¥¹ÌÁö
	//·Îºó½ºÅ³-¹æ¾îÅÂ¼¼ : HP¸¦ ¼ø°£ÀûÀ¸·Î ºÎÇ®·Á¼­ Å« µ¥¹ÌÁö¸¦ ¹Þ´Â´Ù. 

	CREWTYPE_NORMAL = 0,
	CREWTYPE_ATTACKSKILL,
	CREWTYPE_BUFFSKILL,
	CREWTYPE_SUMMON,
	CREWTYPE_HEART,

	TOTAL_CREWTYPE,

	MAXHOTKEY = 3,//
	QUICKSLOTGAP = 80 * _2X,

	RINGKEY = MAXHOTKEY,

	//¹æ µðÆÄÀÎ
	NORMALROOM = 0,
	ENEMYROOM,

	//¸Ê°ü·Ã

	MAXMAPSIZE_X = 100 * TSIZE,
	MAXMAPSIZE_Y = 42 * TSIZE,

	MAXTILECOUNT = 88,

	//¹è°æRect¼ýÀÚ
	MAXRECT = 8,
	//¿ø°æ¿ÀºêÁ§Æ®
	MAXBACKOBJ = 65,
	//±Ù°æ
	MAXFOREOBJ = 51,
	//Áß¸³ ¿ÀºêÁ§Æ®
	MAXNEUTRALOBJ = 18,
	//¿òÁ÷ÀÌ´Â ¹è°æ ¿ÀºêÁ§Æ®
	MAXBGOBJECT = 32,

	//Å¸ÀÏ Ãæµ¹ °ü·Ã
	TILE_VOID = 0,
	TILE_SPACE,
	TILE_WATER,
	TILE_SWAMP,
	TILE_DAMAGE,
	TILE_WATERDAMAGE,
	TILE_BLOCK = 6,
	TILE_DOWN,
	TILE_ICE,
	TILE_BLAZE,
	TILE_BLAZE_LEFT,
	TILE_BLAZE_RIGHT,

	MAXTILE = 8,
	TPL = 10,

	STATUS_READY = 0,
	STATUS_PLAY,
	STATUS_ENEMYDEAD,
	STATUS_BRIDGEOPEN,
	STATUS_RAIDCLEAR,
	STATUS_RESULT,

	//MOTION
	ARENA_START = 0,
	ARENA_STOP = 1,
	ARENA_FRAME0 = 2,
	ARENA_FRAME1 = 3,
	ARENA_FRAME2 = 4,
	ARENA_FRAME3 = 5,
	REPORT_FRAME0 = 6,
	REPORT_FRAME1 = 7,
	REPORT_FRAME2 = 8,
	REPORT_FRAME2_EDGE = 9,
	REPORT_FRAME3 = 10,
	REPORT_FRAME3_EDGE = 11,
	REPORT_FRAME4 = 12,
	REPORT_FRAME4_EDGE = 13,
	ARENA_CROWN_FRAME0 = 14,
	ARENA_CROWN_FRAME1 = 15,
	ARENA_CROWN_FRAME2 = 16,
	ARENA_CROWN_FRAME3 = 17,
	ARENA_CROWN_FRAME4 = 18,
	ARENA_CROWN_FRAME5 = 19,
	ARENA_CROWN_FRAME6 = 20,
	ARENA_CROWN_FRAME7 = 21,
	ARENA_CROWN_FRAME8 = 22,

	TOTALARENAMOTION,

	//IMAGE
	IMG_ARENA_0 = 0,
	IMG_ARENA_1 = 1,
	IMG_ARENA_2 = 2,
	IMG_ARENA_3 = 3,
	IMG_ARENA_4 = 4,
	IMG_ARENA_5 = 5,
	IMG_ARENA_6 = 6,
	IMG_ARENA_7 = 7,
	IMG_ARENA_8 = 8,
	IMG_ARENA_9 = 9,
	IMG_ARENA_10 = 10,
	IMG_ARENA_11 = 11,
	IMG_ARENA_12 = 12,
	IMG_ARENA_13 = 13,
	IMG_ARENA_14 = 14,
	IMG_ARENA_15 = 15,
	IMG_ARENA_16 = 16,
	IMG_ARENA_17 = 17,

	TOTALARENAOFF,

	MAXENEMYGAUGE = 1000,
	TIMEATTACKFRAME = 1800,

	//AREA_SWAMP
	//AREA_VALLEY
	//AREA_ATLANTICE
	//AREA_SEWAGE
	//AREA_PLAIN

	//AREA_FLAME
	//AREA_FROST
	//AREA_THUNDER
	//AREA_LIGHT
	//AREA_DARKNESS

	//AREA_GOLEMVALLEY
	//AREA_DRAGON
	//AREA_GHOST
	//AREA_DEVILCASTLE
	//AREA_SPACE

	//ÅäÅ» ½ºÅ×ÀÌÁö

	STAGELIST_Y = DIORAMASIZE_Y * 2 / 3,
	//?¤í…Œ?´ì? ë§ˆë‹¤ ë°©ê°œ?˜ëŠ” 5ê°?
	TOTALROOM = 5,

	WAVESTATUS_READY = 0,
	WAVESTATUS_PLAY,
	WAVESTATUS_END,

	WAVETYPE_SWAMP = 0,
	WAVETYPE_VALLEY,
	WAVETYPE_ATLANTICE,
	WAVETYPE_SEWAGE,
	WAVETYPE_PLAIN,
	WAVETYPE_FLAME,
	WAVETYPE_FROST,
	WAVETYPE_THUNDER,
	WAVETYPE_LIGHT,
	WAVETYPE_GOLEMVALLEY,
	WAVETYPE_DARKNESS,
	WAVETYPE_DRAGON,
	WAVETYPE_GHOST,
	WAVETYPE_DEVILCASTLE,
	WAVETYPE_SPACE,

	TOTALWAVETYPE,

	MAXWAVEENEMY = 3,
	MAXWAVE = 100,
	WAVEDATASIZE = 3,
	TOTALARENA = 100,
	TOTALRAID = 50,
	TOTALRAIDSELECTED = 12,
	RAIDARRAYDATASIZE = 4,
	TOTALARENAMENU = 3,
	ARENAINFODATASIZE = 13,
	TOTALDMGQUEST = 100,
	ONCEDMGQUEST = 100,

	ARENAITEMFRAME = FPS * 10,//Åõ±âÀå¿¡¼­ º¸½º¸÷Àâ¾ÒÀ»¶§ ¾ÆÀÌÅÛÀÌ µå¶øµÇ´Â ÃÖ´ë ÇÁ·¹ÀÓ
	ARENALIMITTIME = 60 * 60 * 24 * 3,//º¸½ºÀüÀº 10ÃÊ¾È¿¡ Å¬¸®¾î µÇ¾ß µÈ´Ù.
	ARENABUFFTIME = FPS * 100,

	MINUTES = FPS * 60,

	ARENAANIMATIONFRAME = 8,

	CREWDATA_TYPE = 0,
	CREWDATA_STR,
	CREWDATA_SKILL1,
	CREWDATA_SKILL2,
	CREWDATA_SKILL3,
	CREWDATA_CARDBG,//Ä«µå·Î ³ª¿ÔÀ» ¶§ ¾î¶»°Ô µÇ´ÂÁö.
	CREWDATASIZE,
	//TYPE, STAR, PRICE, BULLETDATA
	CMFFRAMEPOSITIONDATASIZE = 6,

	CREW_MENU = 0,//¸Þ´º¸¦ ¿Ã·ÁÁÖ´Â ¼­Æ÷ÅÍ
	CREW_GOODS,//ÀçÈ­¸¦ »ý»êÇÏ´Â ¼­Æ÷ÅÍ
	CREW_ABILITY,//¾îºô¸®Æ¼¸¦ ¿Ã·ÁÁÖ´Â ¼­Æ÷ÅÍ
	CREW_EQUIP,//Àåºñ¸¦ »ý»êÇÏ´Â ¼­Æ÷ÅÍ

	//MP¸¦ ºÙÀÌÀÚ
	//MP¸¦ »ç¿ëÇØ¼­ ½ºÅ³À» »ç¿ë. 

	//ÀçÈ­
	//´ÙÀÌ¾Æ¸óµå(Ä³½Ã) -> ¼ÒÈ¯,  
	//¿¡¸Þ¶öµå -> ½ºÅ³½½·Ô, Àåºñ°³¼ö µî
	//°ñµå()->·¹º§¾÷
	//°­È­¼®()->°­È­
	//½ºÅ³Ä«µå()
	//È²±Ý¿­¼è(±¸¸Å¸¦ ÇÏ¸é ½×ÀÌ´Â Æ¯º°)
	//
	//ÀûÀ» °ø°ÝÇÏ¸é ±âº»ÀûÀ¸·Î °ñµå¿Í °æÇèÄ¡¸¸ ³ª¿Â´Ù.

	MENU_PLAY = 0,//Ä³¸¯ÅÍ¸Þ´º : Ä³¸¯ÅÍ¸¦ ·¹º§¾÷ÇÏ°í ½ºÅÈ(STAT_STR, STAT_VIT, STAT_AGI, STAT_INT)À» Âï´Â ºÎºÐ
	MENU_HERO,
	MENU_CREW,
	MENU_COLLECTIONS,//Àåºñ, ¼ÒÈ¯¼ö, ±âÅ¸
	MENU_CASTLE,//¼º °ü·Ã
	MENU_SHOP,//»óÁ¡ : ´ÙÀÌ¾Æ¸óµå(Ä³½Ã) -> ¼ÒÈ¯, ¿¡¸Þ¶öµå -> ½ºÅ³½½·Ô, Àåºñ°³¼ö µî, °ñµå()->·¹º§¾÷, °­È­¼®()->°­È­, ½ºÅ³Ä«µå(), È²±Ý¿­¼è(±¸¸Å¸¦ ÇÏ¸é ½×ÀÌ´Â Æ¯º°)
	MENU_STARSHOP,
	MENU_FRIENDS,
	MENU_NEWS,
	MENU_GIFTS,
	MENU_LEADERBOARD,//°¡Àå ½ºÅ×ÀÌÁö¸¦ ¸¹ÀÌ ÁøÇàÇÑ À¯Àú 
	MENU_INVITEFREINDS,
	MENU_CALENDAR,
	MENU_SETTING,
	MENU_JOKBO,

	MENU_LIST,
	MENU_GAMEEVENT,
	MENU_BOSSRAID,
	MENU_STAGEINFO,

	MENU_BATTLE,//¿©±â¼­´Â º¸½º ¸÷°ú ½Î¿ì´Â°ÍÀ¸·Î
	MENU_RAID,

	MENU_GAMERESET,//°ÔÀÓÃÊ±âÈ­

	TOTAL_MENU,

	MENUICON_COLLECTIONS = 0,
	MENUICON_HERO,
	MENUICON_GRAB,
	MENUICON_DAILYQUEST,
	MENUICON_SHOP,
	MENUICON_GIFT,
	MENUICON_STARSHOP,
	MENUICON_MARKET,
	MENUICON_SETTING,
	MENUICON_GUILD,

	TOTALMENUICON,

	TOTAL_LISTMENU = MENU_LIST,

	MENU_LOADING = 0,
	MENU_LOGIN,
	MENU_POLICY,

	TOTALINITMENU,

	SELECTEDMENU_WIDTH = TSIZE * 5,

	SCROLL_NOTHING = 0,
	SCROLL_HORIZONTAL,
	SCROLL_VERTICAL,

	CURRENCY_EXP = 0,
	CURRENCY_GOLD,//±âº»ÄÚÀÎ
	CURRENCY_MEDAL,//ÀüÅõ¿¡¼­ ½Â¸®ÇÏ¸é ¹Þ´Â Æ÷ÀÎÆ®´Â ¸Þ´Þ 
	CURRENCY_COIN,//»Ì±â¿¡ ÁÖ·Î »ç¿ëµÇ°í, 
	CURRENCY_CASH,
	CURRENCY_HAMMER,
	CURRENCY_SHIELD,
	CURRENCY_HEART,
	CURRENCY_QUEST,
	CURRENCY_STAR,
	CURRENCY_CREW,
	CURRENCY_EQUIP,

	TOTAL_CURRENCY,


	COINSCATTERINFOSIZE = 16,

	COINSCATTERRAIDINFOSIZE = 14,

	CURRENCYWAITINGFRAMEMAX = FPS / 2,
	CURRENCYWAITINGFRAMEMAX2 = FPS * 2,


	LOG_EVENT_QUESTSTART = 0,//ÀÌº¥Æ® ¿ÀÇÂ
	//Äù½ºÆ® ¾ÆÀÌÄÜ + Äù½ºÆ® ÀÌ¸§ + Äù½ºÆ®°¡ È°¼ºÈ­µÇ¾ú½À´Ï´Ù
	LOG_EVENT_BATTLESTART,
	//¹èÆ² ¾ÆÀÌÄÜ + ¹èÆ²ÀÌ È°¼ºÈ­ µÇ¾ú½À´Ï´Ù!
	LOG_EVENT_RAIDSTART,
	//·¹ÀÌµå ¾ÆÀÌÄÜ + ·¹ÀÌµå°¡ È°¼ºÈ­ µÇ¾ú½À´Ï´Ù!
	LOG_RAID,//Àû º¸½ºÀÇ Ä§°ø
	//Àû º¸½º cmf + ÅÐ¾î°¡´Â °ñµå + ÅÐ¾î°¬½À´Ï´Ù.
	LOG_BATTLE,//Àû º¸½ºÀÇ µ¿·á ¹«·ÂÈ­
	//Àû º¸½º cmf + Ä§°øÇØ¼­ + ¹«·ÂÈ­µÈ ³» µ¿·á ¾ÆÀÌÄÜÀÌ ¹«·ÂÈ­ µÇ¾ú½À´Ï´Ù.
	LOG_BOSSGETCOIN,//º¸½º Èú
	//Àû º¸½º cmf + Àû µ¿·á¸¦ ÅëÇØ¼­ + °ñµå¾ÆÀÌÄÜ + ±Ý¾× + È¸º¹Çß½À´Ï´Ù.
	LOG_SKILL,//½ºÅ³
	LOG_BETHEART,//ÇÏÆ® Áõ°¡
	LOG_BETCOIN,

	TOTAL_LOG,


	TOTALBUFFSHOP = 3,
	BUFFSHOPDATASIZE = 5,

	TOTALMEDALSHOP = 3,
	MEDALSHOPDATASIZE = 5,

	//?œê°„?€
	OXYGEN = 200,

	TOTALOPTION = 12,

	END_GAMEDEF
} GAMEDEF;


#define CURRENCYICON_STARTSIZE 1.0f
#define CURRENCYICON_ENDSIZE 1.5f
#define CURRENCYICON_ENDSIZE2 2.0f
/*
//´Þ¼ºµµ °ü·Ã µðÆÄÀÎ
typedef enum _reportDef {
	REPORT_ARENA = 0,
	REPORT_VILLAGE,
	REPORT_AREA,
	REPORT_ITEM,
	REPORT_MONSTER,
	REPORT_COMBAT,
	REPORT_STAT,
	REPORT_ETC,

	TOTAL_REPORT_CATEGORY,

	//Ä«Å×°í¸®º° °¹¼ö
	REPORT_ARENA_COUNT = 9,
	REPORT_VILLAGE_COUNT = 9,
	REPORT_AREA_COUNT = 8,
	REPORT_ITEM_COUNT = 8,
	REPORT_MONSTER_COUNT = 28,
	REPORT_COMBAT_COUNT = 10,
	REPORT_STAT_COUNT = 15,
	REPORT_ETC_COUNT = 10,

	//Ä«Å×°í¸®º° ½ÃÀÛ ÀÎµ¦½º
	REPORT_ARENA_START = 0,
	REPORT_VILLAGE_START = REPORT_ARENA_START + REPORT_ARENA_COUNT,
	REPORT_AREA_START = REPORT_VILLAGE_START + REPORT_VILLAGE_COUNT,
	REPORT_ITEM_START = REPORT_AREA_START + REPORT_AREA_COUNT,
	REPORT_MONSTER_START = REPORT_ITEM_START + REPORT_ITEM_COUNT,
	REPORT_COMBAT_START = REPORT_MONSTER_START + REPORT_MONSTER_COUNT,
	REPORT_STAT_START = REPORT_COMBAT_START + REPORT_COMBAT_COUNT,
	REPORT_ETC_START = REPORT_STAT_START + REPORT_STAT_COUNT,

	//Åõ±âÀå ¹× ±æµå
	REPORT_ARENA0 = 0,	//°­ÀÚÀÇ ±æ(Åõ±âÀå ÀÔÀå È½¼ö)
	REPORT_ARENA1,	//Áö¿ÁÀÇ ±æ(ÇïÅõ±âÀå ÀÔÀå È½¼ö)
	REPORT_ARENA2,	//°­ÀÚÀÇ ¸í¼º(Åõ±âÀå 100Ãþ µµ´Þ)
	REPORT_ARENA3,	//Áö¿ÁÀÇ ¸í¼º(ÇïÅõ±âÀå 100Ãþ µµ´Þ)
	REPORT_ARENA4,	//Àû±ØÀûÀÎ Âü¿©(±æµåÀü Âü¿© È½¼ö)
	REPORT_ARENA5,	//Åõ±âÀåÀÇ Áö¹èÀÚ(Åõ±âÀå¿¡¼­ Á×ÀÎ Àû ¼ýÀÚ)
	REPORT_ARENA6,	//Áö¿ÁÀÇ Áö¹èÀÚ(ÇïÅõ±âÀå¿¡¼­ Á×ÀÎ Àû ¼ýÀÚ)
	REPORT_ARENA7,	//¸ÅÀÏ ¸ÅÀÏ ²ÙÁØÈ÷(µ¥ÀÏ¸® Äù½ºÆ® ¼öÇà È½¼ö)
	REPORT_ARENA8,	//°ÅÀÎ ÅðÄ¡(Åõ±âÀå¿¡¼­ NPC ÅðÄ¡ È½¼ö)

	//¸¶À»
	REPORT_VILLAGE0,		//Àá²Ù·¯±â(¿©°üÀ» ÀÌ¿ëÇÑ È½¼ö)
	REPORT_VILLAGE1,		//´Ü°ñ¼Õ´Ô(»óÀÎµé Áß 1¸í¿¡°Ô¼­ ¾ÆÀÌÅÛ ±¸ÀÔÇÑ ¼ö)
	REPORT_VILLAGE2,		//°­ÇÑ Àåºñ¸¦ À§ÇÏ¿©(°­È­ È½¼ö)
	REPORT_VILLAGE3,		//ºÒ±¼ÀÇ °­È­(°­È­ ½ÇÆÐ È½¼ö)
	REPORT_VILLAGE4,		//ºí·¢½º¹Ì½º(Àåºñ Á¦ÀÛ È½¼ö)
	REPORT_VILLAGE5,		//·°¼Å¸®¸¶½ºÅÍ(º¸¼® ÀåÂø È½¼ö)
	REPORT_VILLAGE6,		//¾Ë¶ãÇÑ ¸ðÇèÀÚ(»óÁ¡¿¡´Ù°¡ ¾ÆÀÌÅÛÀ» ÆÇ¸ÅÇÑ È½¼ö)
	REPORT_VILLAGE7,		//°ø°£À» ´Þ¸®´Â ÀÚ(±ÍÈ¯¼­ »ç¿ëÇÑ È½¼ö)
	REPORT_VILLAGE8,		//ÀÌ¿ô»çÃÌ(»ç¶÷µé¿¡°Ô ¸»À» °Ç È½¼ö)

	//Áö¿ª
	REPORT_AREA0,	//À§ÇèÀ» Ãß±¸ÇÏ´Â ÀÚ(¸ðµç °­Àû Áö¿ª ¹æ µé¾î°¡¸é)
	REPORT_AREA1,	//¼¼»óÀ» Å½ÇèÇÏ´Â ÀÚ(¹Ì´Ï¸Ê 100%)
	REPORT_AREA2,	//ÆÄ±«ÀÇ ´ÞÀÎ(Âï±â ºí·Ï ¸ðµÎ ÆÄ±«½Ã)
	REPORT_AREA3,	//ÅÂ¾çÀ» ÆÄ±«ÇÏ´Â ÀÚ(SUN ºí·Ï ¸ðµÎ ÆÄ±«½Ã)
	REPORT_AREA4,	//¼ø°£ ÀÌµ¿ÀÇ ´ÞÀÎ(¸ðµç ¿öÇÁºí·Ï ÀÌ¿ë½Ã)
	REPORT_AREA5,	//¾îµð¿¡ ÀÖÀ»±î?(ÇÊµå¿¡ ¼û°ÜÁø ¾ÆÀÌÅÛ ¸ðµÎ Ã£À¸¸é)
	REPORT_AREA6,	//Æ®·¹Á® ÇåÅÍ(Å¸ Ä³¸¯ÅÍ¿ë »óÀÚ¸¦ Á¦¿ÜÇÑ ¸ðµç º¸¹°»óÀÚ È¹µæ)
	REPORT_AREA7,	//¿©ÇàÀÚÀÇ ¾È³»¼­(¸ðµç Ç¥ÁöÆÇÀ» ÀÐÀ¸¸é)

	//¾ÆÀÌÅÛ
	REPORT_ITEM0,		//¸ñ°ÉÀÌ ¼öÁý°¡(µî±Þ¿¡ °ü°è¾øÀÌ ¸ðµç ¸ñ°ÉÀÌ°¡ ÀÎº¥Åä¸®¿¡ ÀÖÀ» ¶§)
	REPORT_ITEM1,		//¹ÝÁöÀÇ Á¦¿Õ(µî±Þ °ü°è¾øÀÌ ¸ðµç ¹ÝÁö¸¦ ÀÎº¥Åä¸®¿¡ °¡Áö°í ÀÖÀ¸¸é)
	REPORT_ITEM2,		//¹«±â ¼öÁý°¡(¸ðµç ¹«±â(µî±Þ »ó°ü ¾øÀ½)¸¦ ÀÎº¥Åä¸®¿¡ °¡Áö°í ÀÖÀ¸¸é)
	REPORT_ITEM3,		//°©¿Ê ¼öÁý°¡(¸ðµç °©¿Ê(µî±Þ »ó°ü ¾øÀ½) ÀÎº¥Åä¸®¿¡ °¡Áö°í ÀÖÀ¸¸é)
	REPORT_ITEM4,		//¹ÙÁö ¼öÁý°¡(¸ðµç ¹ÙÁö(µî±Þ »ó°ü ¾øÀ½) ÀÎº¥Åä¸®¿¡ °¡Áö°í ÀÖÀ¸¸é)
	REPORT_ITEM5,		//¸ðÀÚ ¼öÁý°¡(¸ðµç ¸ðÀÚ(µî±Þ »ó°ü ¾øÀ½) ÀÎº¥Åä¸®¿¡ °¡Áö°í ÀÖÀ¸¸é)
	REPORT_ITEM6,		//Àå°© ¼öÁý°¡(¸ðµç Àå°©(µî±Þ »ó°ü ¾øÀ½) ÀÎº¥Åä¸®¿¡ °¡Áö°í ÀÖÀ¸¸é)
	REPORT_ITEM7,		//½Å¹ß ¼öÁý°¡(¸ðµç ½Å¹ß(µî±Þ »ó°ü ¾øÀ½) ÀÎº¥Åä¸®¿¡ °¡Áö°í ÀÖÀ¸¸é)

	//¸ó½ºÅÍ
	REPORT_MONSTER0,	//½ÀÁöÀÇ »ç³É²Û(Åç·¹¾Æ ½ÀÁö¿¡¼­ ÅðÄ¡ÇÑ ¸ó½ºÅÍ ¸¶¸´¼ö)
	REPORT_MONSTER1,	//°è°îÀÇ »ç³É²Û(±Ý´ÜÀÇ °è°î¿¡¼­ ÅðÄ¡ÇÑ ¸ó½ºÅÍ ¸¶¸´¼ö)
	REPORT_MONSTER2,	//¹Ù´ÙÀÇ »ç³É²Û(¾ÆÆ²¶õÆ¼½º¿¡¼­ ÅðÄ¡ÇÑ ¸ó½ºÅÍ ¸¶¸´¼ö)
	REPORT_MONSTER3,	//ÁöÇÏÀÇ »ç³É²Û(ÁöÇÏµµ¿¡¼­ ÅðÄ¡ÇÑ ¸ó½ºÅÍ ¸¶¸´¼ö)
	REPORT_MONSTER4,	//Æò¿øÀÇ »ç³É²Û(¾Æµ¨ Æò¿ø¿¡¼­ ÅðÄ¡ÇÑ ¸ó½ºÅÍ ¸¶¸´¼ö)
	REPORT_MONSTER5,	//ºÒ²ÉÀÇ »ç³É²Û(È«¿°ÀÇ ´ëÁö¿¡¼­ ÅðÄ¡ÇÑ ¸ó½ºÅÍ ¸¶¸´¼ö)
	REPORT_MONSTER6,	//¾óÀ½ÀÇ »ç³É²Û(À¯±¸ÇÑ ºù¿ø¿¡¼­ ÅðÄ¡ÇÑ ¸ó½ºÅÍ ¸¶¸´¼ö)
	REPORT_MONSTER7,	//¹ø°³ÀÇ »ç³É²Û(Àü³úÀÇ °ø¹æ¿¡¼­ ÅðÄ¡ÇÑ ¸ó½ºÅÍ ¸¶¸´¼ö)
	REPORT_MONSTER8,	//È²È¥ÀÇ »ç³É²Û(È²È¥ÀÇ ¼º¿ª¿¡¼­ ÅðÄ¡ÇÑ ¸ó½ºÅÍ ¸¶¸´¼ö)
	REPORT_MONSTER9,	//Çù°îÀÇ »ç³É²Û(°ñ·½ÀÇ Çù°î¿¡¼­ ÅðÄ¡ÇÑ ¸ó½ºÅÍ ¸¶¸´¼ö)
	REPORT_MONSTER10,	//½É¿¬ÀÇ »ç³É²Û(Ä¥ÈæÀÇ ½É¿¬¿¡¼­ ÅðÄ¡ÇÑ ¸ó½ºÅÍ ¸¶¸´¼ö)
	REPORT_MONSTER11,	//¸í°èÀÇ »ç³É²Û(¸ÁÀÚÀÇ µµ½Ã¿¡¼­ ÅðÄ¡ÇÑ ¸ó½ºÅÍ ¸¶¸´¼ö)
	REPORT_MONSTER12,	//µå·¡°ï ½½·¹ÀÌ¾î(µå·¡°ïÀÇ ¹«´ý¿¡¼­ ÅðÄ¡ÇÑ ¸ó½ºÅÍ ¸¶¸´¼ö)
	REPORT_MONSTER13,	//Ä³½½ Å©·¡¼Å(¸¶¿Õ¼º¿¡¼­ ÅðÄ¡ÇÑ ¸ó½ºÅÍ ¸¶¸´¼ö)
	REPORT_MONSTER14,	//½ºÆäÀÌ½º ¸¶¸°(¿ìÁÖ¿¡¼­ ÅðÄ¡ÇÑ ¸ó½ºÅÍ ¸¶¸´¼ö)
	REPORT_MONSTER15,	//½ÀÁöÀÇ ÀüÀå(Åäµå ¹ÂÅÏÆ®¸¦ ÅðÄ¡ÇÑ È½¼ö)
	REPORT_MONSTER16,	//°è°îÀÇ ÀüÀå(¾Æ¸£°ïÀ» ÅðÄ¡ÇÑ È½¼ö)
	REPORT_MONSTER17,	//ÇØÀú ÀüÀå(Ä«ÅùÀ» ÅðÄ¡ÇÑ È½¼ö)
	REPORT_MONSTER18,	//°í´ë ÀüÀå(°í´ëÀÇ ¼öÈ£ÀÚ¸¦ ÅðÄ¡ÇÑ È½¼ö)
	REPORT_MONSTER19,	//ºÒ²É ÀüÀå(ÀÌÇÁ¸®Æ®¸¦ ÅðÄ¡ÇÑ È½¼ö)
	REPORT_MONSTER20,	//¾óÀ½ ÀüÀå(ÇÁ·Î½ºÆ®¸¦ ÅðÄ¡ÇÑ È½¼ö)
	REPORT_MONSTER21,	//¹ø°³ ÀüÀå(¶óÀÌ¿À³Ê¸¦ ÅðÄ¡ÇÑ È½¼ö)
	REPORT_MONSTER22,	//ºûÀÇ ÀüÀå(È£·ç½º¸¦ ÅðÄ¡ÇÑ È½¼ö)
	REPORT_MONSTER23,	//ÁöÇÏµµÀÇ ÀüÀå(¸¶µµÇÕ¼º¼ö¸¦ ÅðÄ¡ÇÑ È½¼ö)
	REPORT_MONSTER24,	//Çù°îÀÇ ÀüÀå(°í´ëÀÇ ¹æÁÖ¸¦ ÅðÄ¡ÇÑ È½¼ö)
	REPORT_MONSTER25,	//¾îµÒÀÇ ÀüÀå(¾Æ¸®¸¸À» ÅðÄ¡ÇÑ È½¼ö)
	REPORT_MONSTER26,	//¾ÏÈæ·æÀÇ ÀüÀå(Æ¼¾î¸ËÀ» ÅðÄ¡ÇÑ È½¼ö)
	REPORT_MONSTER27,	//¸í°èÀÇ ÀüÀå(Á×À½ÀÇ ½ÅÀ» ÅðÄ¡ÇÑ È½¼ö)

	//ÀüÅõ
	REPORT_COMBAT0,		//ÀÌ±æ¼ö ÀÖ´Â ½Î¿ò(Ä³¸¯ÅÍº¸´Ù ·¹º§ÀÌ 10ÀÌ»ó ³·Àº ¸ó½ºÅÍ¸¦ Á×ÀÎ È½¼ö)
	REPORT_COMBAT1,		//²÷ÀÓ¾ø´Â °ø°Ý(Àû¿¡°Ô ÀÔÈù µ¥¹ÌÁöÀÇ ´©ÀûÃÑÇÕ)
	REPORT_COMBAT2,		//¸ËÁýÀÇ ÇÑ°è(Àû¿¡°Ô ¹ÞÀº ÇÇÇØÀÇ ´©ÀûÃÑÇÕ)
	REPORT_COMBAT3,		//ÀÌ ¶¥À» ÁöÄÑ¶ó(¹æÀ» ¿Å±âÁö ¾Ê°í ÀâÀº ¸ó½ºÅÍ ¸¶¸´¼ö)
	REPORT_COMBAT4,		//ÁøÁ¤ÇÑ ¿µ¿õ(HP°¡ 1ÀÎ »óÅÂ¿¡¼­ ¿¬¼ÓÀ¸·Î ¸ó½ºÅÍ ÀâÀº È½¼ö)
	REPORT_COMBAT5,		//¹öÇÁ¸¶½ºÅÍ(¹öÇÁ »ç¿ë È½¼ö)
	REPORT_COMBAT6,		//Á¾ÇÕº´¿ø(»óÅÂÀÌ»ó °É¸° È½¼ö)
	REPORT_COMBAT7,		//È­·ÁÇÑ ±â¼ú(¹öÇÁ ÀÌ¿ÜÀÇ½ºÅ³ »ç¿ë È½¼ö)
	REPORT_COMBAT8,		//Á»ºñ(ºÎÈ°¾àÀ» ¸ÔÀº È½¼ö)
	REPORT_COMBAT9,		//¼ºÀÎ(ÀûÀ» °ø°ÝÇÏÁö ¾Ê°í ¿¬¼ÓÀ¸·Î Á×Àº È½¼ö)

	//´É·ÂÄ¡
	REPORT_STAT0,		//ÀÇ¹Ì¾ø´Â ·¹º§¾÷(»ç¿ëÇÏÁö ¾ÊÀº APÀÇ ÇÕ)
	REPORT_STAT1,		//½ºÅ³¾øÀÌ ½Î¿î´Ù(»ç¿ëÇÏÁö ¾ÊÀº SPÀÇ ÇÕ)
	REPORT_STAT2,		//ÃÖ°­ÀÇ °ø°Ý·Â(°ø°Ý·Â ÃÑÇÕ)
	REPORT_STAT3,		//ÃÖ°­ÀÇ ¹æ¾î·Â(¹æ¾î·Â ÃÑÇÕ)
	REPORT_STAT4,		//Á¤È®ÇÑ °ø°Ý(¸íÁß·ü %)
	REPORT_STAT5,		//Àçºü¸¥ È¸ÇÇ(È¸ÇÇ %)
	REPORT_STAT6,		//ÇÊ»ìÀÇ ÀÏ°Ý(Å©¸®Æ¼ÄÃ È®·ü %)
	REPORT_STAT7,		//¿¬¼ÓµÇ´Â °ø°Ý(Ãß°¡Å¸ È®·ü)
	REPORT_STAT8,		//²ç¶Õ´Â °ø°Ý(°üÅë°ø°Ý È®·ü)
	REPORT_STAT9,		//Ãæ°ÝÀûÀÎ °ø°Ý(±âÀý %)
	REPORT_STAT10,	//¸·À» ¼ö ¾ø´Â °ø°Ý(¹æ¾îµµ ¹«½Ã °ø°Ý È®·ü)
	REPORT_STAT11,	//·°Å°°¡ÀÌ(Çà¿î Áõ°¡ %)
	REPORT_STAT12,	//±ÝÀü¿î(°ñµå È¹µæ %)
	REPORT_STAT13,	//°æÇèÀÇ ºÎÀû(°æÇèÄ¡ È¹µæ %)
	REPORT_STAT14,	//»óÀÎÀÇ ÁÖ¸Ó´Ï(Áö±Ý±îÁö ¾òÀº µ· ÃÑÇÕ)

	//±âÅ¸
	REPORT_ETC0,	//À§´ëÇÑ ¾÷Àû(¸ðµç ¼­ºê Äù½ºÆ®))
	REPORT_ETC1,	//³×¹ö¿£µù ½ºÅä¸®(ÇÃ·¹ÀÌ Å¸ÀÓ)
	REPORT_ETC2,	//Àá¼öºÎ(¼öÁß¿¡ ÇÑ ¹ø µé¾î°¡¼­ ÀÖ´Â ½Ã°£)
	REPORT_ETC3,	//¸Ö¹ÌÀ¯¹ß(¾îµÒÀÇ ÆÄÆíÀ» Åº ½Ã°£(´©Àû))
	REPORT_ETC4,	//±Û¶óÀÌ´õÃ³·³(È°°­ ÇÕ°è½Ã°£)
	REPORT_ETC5,	//ÀúÃà ½À°ü(ÀÎº¥Åä¸®¿¡ ÀÖ´Â µ·)
	REPORT_ETC6,	//¹æ±¸¼® ÆäÀÎ(ÇÑ ¹æ¿¡¼­ ¾Æ¹«°Íµµ ÇÏÁö ¾Ê°í ÀÖ´Â ½Ã°£)
	REPORT_ETC7,	//ÁöÆò¼± ³Ê¸Ó(¿·À¸·Î ÀÌµ¿ÇÑ °Å¸® (¼öÆòÀ¸·Î Å¸ÀÏ¼ö ÃøÁ¤))
	REPORT_ETC8,	//ÇÏ´Ã ³¡±îÁö(À§·Î ¿Ã¶ó°£ °Å¸® (¼öÁ÷À¸·Î Å¸ÀÏ¼ö ÃøÁ¤))
	REPORT_ETC9,	//ºí·¢ & È­ÀÌÆ®(ºí·¢È¦ Åë°ú È½¼ö(´©Àû))

	//È£Äª
	PLAYER_TITLE0,		//±æµåÀÇ ÀÏµî°ø½Å(±æµåÀü¿¡¼­ 1µî)
	PLAYER_TITLE1,		//½ÅÁßÇÑ ¸ðÇèÀÚ(¾Ç¼¼¼­¸®¸¦ Æ÷ÇÔÇÑ ¸ðµç Àåºñ¸¦ °®ÃçÀÔ¾úÀ»¶§)
	PLAYER_TITLE2,		//À½¼ÓÀÇ ¾Ï»ìÀÚ(60ÃÊ ¾È¿¡ Àû 15¸¶¸®¸¦ ÅðÄ¡ÇÑ´Ù.)
	PLAYER_TITLE3,		//½ºÆ®¶óÀÌÄ¿(Á¤·É¼®À» ´øÁ®¼­ ÇÑ ¹ø¿¡ 3¸¶¸®¸¦ ÇØÄ¡¿î´Ù.)
	PLAYER_TITLE4,		//µ¹°Ý´ëÀå(´ë½¬¾îÅÃÀ¸·Î ¸ó½ºÅÍ¸¦ 777¸¶¸® °ÝÆÄ)
	PLAYER_TITLE5,		//Åõ±âÀå¸¶½ºÅÍ(Åõ±âÀåÀ» 1È¸ ³¡±îÁö µ¹ÆÄÇÑ´Ù.)
	PLAYER_TITLE6,		//º¸¼®¾ÖÈ£°¡(¼ÒÄÏÀÌ 3°³ÀÌ»óÀÎ Àåºñ¿¡ ¸ðµÎ º¸¼®À» ¹ÚÀ¸¸é)
	PLAYER_TITLE7,		//ÁÖÁ¦¸¦ ¸ð¸£´Â ÀÚ(ÀûÀÇ °ø°Ý ÇÑ ¹æ¿¡ ³» ÇÇ°¡ ¹Ý ÀÌ»ó ±ïÀÎ È½¼ö)
	PLAYER_TITLE8,		//µ¹¾ÆÀÌ(ÃµÁ¤¿¡ ¸Ó¸®¸¦ ºÎµúÈù È½¼ö°¡ 500È¸(Á¡ÇÁ³ôÀÌ°¡ ÃµÁ¤¿¡ ¸Ó¸®°¡ ´ê´Â ÀÌ»ó ¿Ã¶ó°¥¼öÀÖÀ»¶§ ·Î ÆÇÁ¤))
	PLAYER_TITLE9,		//¹ú°Å¹þÀº »ç³É²Û(¹«±â¸¸ ÀåºñÇÏ°í ¸ó½ºÅÍ¸¦ ÇØÄ¡¿î ¸¶¸´¼ö°¡ 100¸¶¸®)
	PLAYER_TITLE10,	//´ëÀÎ¹è(¾ÆÀÌÅÛÀÌ ¹æ¾È¿¡ 5°³ÀÌ»ó ³ª¿ÍÀÖ´Âµ¥ ¸ÔÁö¾Ê°í ´ÙÀ½¹æÀ¸·Î ³Ñ¾î°£´Ù.)
	PLAYER_TITLE11,	//ÀÎ»ýÀ» ¿ªÀüÇÑ ÀÚ(ÀÎº¥¿¡ ÀÖ´Â µ·ÀÌ 7777)
	PLAYER_TITLE12,	//ÁøÁ¤ÇÑ °©ºÎ(À¯·á ¾ÆÀÌÅÛ ±¸ÀÔ °³¼ö°¡ 20°³)
	PLAYER_TITLE13,	//½ºÄ«ÀÌ´ÙÀÌ¹ö(µå·¡°ïÀÇ »ó ¸ÔÀ¸·¯ ¶Ù¾î³»¸±¶§ °É¸²¾øÀÌ ¹Ù´Ú±îÁö °£´Ù.)
	PLAYER_TITLE14,	//ÆòÈ­ÀÇ »çÀÚ °£µð(ÀûÀ» Á×ÀÌÁö ¾Ê°í ¿¬¼ÓÀ¸·Î 20°³ÀÇ ¹æÀ» ÀÌµ¿(¸¶À»³»ºÎ¿¡¼± ¹«È¿. ¸¶À»¿¡ µé¾î°¡¸é Ä«¿îÆ®¸®¼Â))
	PLAYER_TITLE15,	//¾à¹°Áßµ¶ÀÚ(»ç¿ëÇÑ Æ÷¼ÇÈ½¼ö(¾¾¾Ñ,Çãºê)°¡ ´©Àû 100°³¿¡ µµ´Þ)
	PLAYER_TITLE16,	//·Ñ¸µ¸¶½ºÅÍ(¾îµÒÀÇ ÆÄÆí »çÀÌ¸¦ ¶³¾îÁöÁö ¾Ê°í ¿Ô´Ù°¬´Ù ÇÑ È½¼ö ´©Àû 100¹ø)
	PLAYER_TITLE17,	//°Ç¸ÁÁõ È²Á¦(¿Ï·áÇÏÁö ¾ÊÀº Äù½ºÆ®°¡ 10°³ ÀÌ»ó´©Àû)
	PLAYER_TITLE18,	//±âº»±âÀÇ ´ÞÀÎ(½ºÅ³ »ç¿ëÇÏÁö ¾Ê°í ³×ÀÓµå¸ó½ºÅÍ¸¦ ÅðÄ¡ÇÑ È½¼ö(±âº» °ø°Ý, Âï±â, ´ë½¬ °ø°Ý))
	PLAYER_TITLE19,	//4¹ø Å¸ÀÚ(³» °ø°Ý ÇÑ ¹æ¿¡ ÀûÀÇ Ã¼·ÂÀÌ ¹Ý ÀÌ»ó ±ïÀÎ È½¼ö ´©Àû 500¹ø)
	PLAYER_TITLE20,	//±¸Á¦ºÒ´É ¹æÇâÄ¡((Åç·½, º§·Î³×¿¡¼­)Áý¿¡ µé¾î°¡¼­ ¾Æ¹«¿¡°Ôµµ ¸»À» °ÉÁö¾Ê°í ´Ù½Ã ³ª°£ È½¼ö´©Àû 100È¸)
	PLAYER_TITLE21,	//µ¶¼­±¤(¾Æµ¨¶óÀÎ µµ¼­°ü¿¡ ¹æ¹®ÇÑ È½¼ö)
	PLAYER_TITLE22,	//È¸ÇÇÀÇ ´ÞÀÎ(HP°¡ ÃÖ´ëHPÀÇ 10% ÀÌÇÏÀÏ¶§ ±ÍÈ¯¼­¸¦ »ç¿ëÇÑ È½¼ö ´©Àû)
	PLAYER_TITLE23,	//ÅÊÄ¿(ÃÖ´ë HP°¡ 1000µ¹ÆÄ)
	PLAYER_TITLE24,	//ÄÚ½ºÆ¬ÇÃ·¹ÀÌ¾î(¹«±âÁ¦¿ÜÇÏ°í ´Ù¸¥ ÁÖÀÎ°øÀÇ Àåºñ¸¦ ÅëÀÏÇØ¼­ ÀÔ´Â´Ù.)
	PLAYER_TITLE25,	//Àü¼³ÀÇ ´ëÀåÀåÀÌ(°­È­¸¦ 10´Ü°è±îÁö ¼º°øÇÑ´Ù.)
	PLAYER_TITLE26,	//±Ù¼º³ÑÄ¡´Â °­ÀÚ(Åõ±âÀå¿¡¼­ È¸º¹ÇÏÁö¾Ê°í Á×ÀÎ Àû ¼ö°¡ 50¸¶¸® ÀÌ»ó)
	PLAYER_TITLE27,	//½Å¼ºÇÑ »çÁ¦(¹°¾àÀ¸·Î µð¹öÇÁ È¸º¹ÇÑ È½¼ö)
	PLAYER_TITLE28,	//µµÀü°úÁ¦ÀÇ ¼öÇàÀÚ(¸ðµç ´Þ¼ºµµ ¿Ï·á)
	PLAYER_TITLE29,	//¿ìÁÖÀû À¯¸íÀÎ»ç(ÀÌ°ÍÀ» Á¦¿ÜÇÑ ¸ðµç È£Äª ÀÔ¼ö)

	TOTAL_REPORT,

	TOTAL_PLAYERTITLE = 30,

	END_REPORTDEF
} REPORTDEF;
*/

typedef enum _prgDef {
	//Data.h ¹è¿­º° ±âÁØ Å©±â
	SETITEMDATASIZE = 3,
	SETOPTIONDATASIZE = 18,
	LEGENDITEMDATASIZE = 18,
	ENCHANTDATASIZE = 6,
#ifdef IRON
	ENCHANTDATASIZE_TYPE = 42,
#else
#ifdef ALLEQUIPLEGENDGRADE
	ENCHANTDATASIZE_TYPE = 5 * 8,
#else
	ENCHANTDATASIZE_TYPE = 40,
#endif
#endif
	ENCHANTIRONDATA_NEEDIRON = 0,
	ENCHANTIRONDATA_NEEDGOLD,
	ENCHANTIRONDATA_PERCENT,
	ENCHANTIRONDATA_SELLIRON,
	ENCHANTIRONDATASIZE,
	
	PVPQUESTINFODATASIZE = 3,
	QUESTINFODATASIZE = 6,
	QUESTREWARDDATASIZE = 4,
	NEUTRALDATASIZE = 11,
	NECKOPTIONDATASIZE = 6,
	NECKOPTIONVALUEDATASIZE = 50,
	RINGOPTIONDATASIZE = 7,
	RINGOPTIONVALUEDATASIZE = 50,
	AISAMPLEDATASIZE = 4 * TOTALEQUIP,
	WINDOWBGDATASIZE = 6,
	MONSTERREWARDDATASIZE = 4,
	REWARDDATASIZE = 4,

	//°¢Á¾ÇÁ·¹ÀÓ
	AREAFRAME = 24 * MOTIONDIV,
	INFOFRAME = 24 * MOTIONDIV,
	BATTLESTARTFRAME = FPS,
	VANISHFRAME = 11,
	VANISHFRAME_DMG = FPS * 3,
	DMGNUMFRAME = FPS,
	SKILLREMAINEDFRAME = 1,
	BUFFITEMREMAINEDFRAME = 1,

	ALERT_NOGOLD = 0,
	ALERT_EQUIP,
	ALERT_INVENFULL,
	ALERT_NOTICE,
	ALERT_NETFAIL,
	ALERT_ARENARESULT,
	ALERT_EXIT,
	ALERT_SELL,
	ALERT_BUY,

	TOTALALERT,

	ALERT_OX = 0,
	ALERT_O,

	ALERTDATASIZE = 5,

	WAVE_RADIUS = 40 * _2X,
	WAVE_DIAMETER = WAVE_RADIUS * 2 + 1,

	LENZ_RADIUS = 72 * _2X,
	LENZ_DISTORTION = 18 * _2X,

	

	//°¨Á¤
	EMOTICON_ZZZ = 1,
	EMOTICON_TALK,
	EMOTICON_FLASH,
	EMOTICON_SCOWL,
	EMOTICON_SWEAT,
	EMOTICON_MUNG,
	EMOTICON_QUESTION,
	EMOTICON_SURPRISE,
	EMOTICON_HEART,
	EMOTICON_HAPPY,
	EMOTICON_CRY,
	EMOTICON_REWARDICON,
	EMOTICON_REWARDBOX,

	TOTALEMOTICON,

	EMOTICONFRAME = 10,

	
	MAXCMF = TOTALCMF,//@@ ³ªÁß¿¡ °è»êÇØº¸°í ÁÙ¿©ÁÙ°Í
	REALMAXCMF = TOTALCMF,	//Äù½ºÆ® Å¬¶óÀÌ¾ðÆ®¿ë CMF
	CLIENTCMF = REALMAXCMF,

	

	AIRETRYCOUNT = 100,

	
	HERO_PARAM_DMG = 0,//µ¥¹ÌÁö
	HERO_PARAM_SDMG,//½ºÅ³µ¥¹ÌÁö
	HERO_PARAM_ASPD,//°ø°Ý¼Óµµ
	HERO_PARAM_MSPD,//ÀÌµ¿¼Óµµ
	HERO_PARAM_HP,//Ã¼·Â
	HERO_PARAM_DEF,//¹æ¾î·Â

	TOTAL_HERO_PARAM,

	DIANAACTIVELEVEL = 5,
	MAXXACTIVELEVEL = 10,
	//¿òÁ÷ÀÓ »óÅÂ
	MODE_NORMAL = 0,
	MODE_GOLEM,
	MODE_SQUIRREL,
	MODE_SLED,

	
	TOTALGAMEMENU = 5,

	OPTION_BGM = 0,
	OPTION_SE,
	OPTION_VOICE,
	OPTION_SCREENEFFECT,
	OPTION_PUSHALARM,
	OPTION_HELP,
	OPTION_GAMEOVER,
	OPTION_ACCOUNT,
	OPTION_POLICY,
	OPTION_COMMNUNITY,

	TOTALOPTIONMENU = 10,

	HELP_GAMESTORY = 0,
	HELP_GAMEGOAL,//1
	HELP_HOWTOPLAY,//2
	HELP_PLAYSCREEN,//3
	HELP_HEROES,//4
	HELP_STATS,//5
	HELP_DEBUF,//6
	HELP_GAMEOVER,//7
	HELP_EQUIP,//8
	HELP_ENCHANT,//9
	HELP_ITEM,//10
	HELP_CREW,//11
	HELP_SOLDIER,//12

	TOTALHELP,

	TOTALHINT = 74,

	


	BUYMULTINUM = 1,

	ADTYPE_SOLDIER = 0,//¿ëº´±¤°í(ÅÍÄ¡ÇÏ¸é ¿ëº´¸Þ´º·Î °¡Áö¸¸ ¾ÆÁ÷ ¿ëº´¸Þ´º°¡ ¿ÀÇÂµÇÁö ¾Ê¾ÒÀ¸¸é °¥¼ö ¾ø´Ù´Â ¸Þ½ÃÁö¸¸ ¶ç¿öÁØ´Ù.)
	ADTYPE_GOODS,//Çö±Ý ´ÙÀÌ·ºÆ® ±¸¸Å»óÇ°(ÅÍÄ¡ÇÏ¸é ±¸¸ÅÆË¾÷À¸·Î)
	ADTYPE_ITEMS,//´Ù¸¥ À¯Àú°¡ 6¼ºÀÌ»ó ¹«±â¸¦ ¾ò°Å³ª Àü¼³µî±Þ¹«±â¸¦ ¾ò¾úÀ» ¶§

	
	LIGHTENALPHA = 4,

	//N00T0X1 = _N | _00 | _T | _0 | _X1,


	
	
	END_PRGDEF
} PRGDEF;

typedef enum _charDef {

	

	

	
	
	


	END_CHARDEF
} CHARDEF;

typedef enum _rouletteDef {
	MAXROULETTE = TOTALCHAR + MAXHOTKEY + MAXCREW,

} ROULETTEDEF;


typedef enum _helpDef {
	IDLEHELP_MOVE_LEFT = 0,
	IDLEHELP_MOVE_RIGHT,
	IDLEHELP_PRESS_ATTACK,
	IDLEHELP_SELECT_SKILL,
	IDLEHELP_PRESS_SKILL,

	TOTALIDLEHELPTYPE,
} HELPDEF;

typedef enum _levelUpReward {
	LVUPREWARD_AUTOROLL = 0,

	LVUPREWARD_COLLECTIONS,

	LVUPREWARD_DAILYREWARDS,

	LVUPREWARD_DAILYQUEST,

	//50?€ ê¸°ë³¸
	LVUPREWARD_HEARTMAX,

	//?˜íŠ¸ ?ì„±??
	LVUPREWARD_HEARTPERHOUR,

	//ë°©íŒ¨ ìµœë???
	LVUPREWARD_SHILED,

	LVUPREWARD_GETHERO,

	LVUPREWARD_GETSKILL,

	LVUPREWARD_STARBOX,

	LVUPREWARD_HEART,

	TOTAL_LVUPREWARD,


} LEVELUPREWARD;

typedef enum _dailyQuest {
	//Monopoly go
	//Upgrade three Landmarks
	//Find three Stickers
	//Collect Money
	//Pass GO
	//Roll Doubles
	//Complete a Heist
	//Complete a Shutdown
	//Land on Chance

	DAILYQUEST_OPEN_BOX_GETEQUIP = 0,//?ìžë¥??´ì–´ ?¥ë¹„ë¥?3ë²??»ìœ¼ë©?
	DAILYQUEST_UPGRADE_CREW,//3ê°œë? ?…ê·¸?ˆì´?œí•˜ë©??˜ëŠ”ê²?
	DAILYQUEST_ATTACK_OTHERUSER,//Battle, Raid ?¬í•¨
	DAILYQUEST_COLLECT_GOLD,//?¼ì •ê¸ˆì•¡???ˆì„ ëª¨ìœ¼ë©?
	DAILYQUEST_STAGE_TRY,//?¤í…Œ?´ì? ?„íˆ¬ 

	TOTAL_DAILYQUEST_TYPE,

	BOXOPENITEMFRAMEINFOSIZE = 6,


} DAILYQUEST;

enum JumpState {
	JS_IDLE = 0,     // ?•ì?(?œìžˆ??
	JS_SPINNING,     // ?í”„ ì¤?+ ê³µì¤‘?ì„œ ê³„ì† êµì²´
	JS_LANDING,      // ì°©ì? êµ¬ê°„(ê³µì¤‘?ì„œ êµì²´?˜ë‹¤ê°€ ì°©ì? ?œê°„ target ?•ì •)
	JS_HOLD,     // ì°©ì? ???°ì¶œ ?€ê¸??¬ë¡œ??
	JS_DONE          // ?•ì • ??ê³ ì •
};

#define ITEMTYPESEED 1000
#define ITEMDETAILSEED 10000
#define MAX_POINTS 500 * MOTIONDIV // ìµœë? ì¢Œí‘œ ê°œìˆ˜
#define MAX_RADIUS 256 // ìµœë? ë°˜ê²½
#define MAX_BOXRADIUS	128

#define BOSSROOMTIME	60 * 10//10ë¶?

#define INFO_Y	
#ifdef TUTORIAL
#define TOTALAI (TOTAL_TIER - 1) * TOTAL_SUBTIER * SUBTIERGAP
#else
#define TOTALAI TOTAL_CREW
#endif

#define MONSTERTYPE_JACO	0
#define MONSTERTYPE_BOSS	1

#define BOOMERANGGAP		4


enum {
	BL_REVEAL,
	BL_JOIN,
	BL_RUN_ALL,
	BL_FINISH
};

#endif
