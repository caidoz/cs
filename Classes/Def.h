#pragma once

#ifndef _DEF_H_
#define _DEF_H_


// ================================
// 분리???�정 ?�일??include
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


//매크�?

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
//#define GUIDELINE
//#define MAPTEST

//#define INVINCIBLE

//#define LOCALPUSH
//#define COSTUMETEST


//30�?기�?(?�트 ?�나??30분마???�나??찬다�?보면 ??
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
//GotoObj or GotoObjXY가 ?�동?�기 ?�한 최소�?
#define SPEED_MIN	4
#define DAYS3 3 * 24 * 60 * 60 * 1000 // 3?�을 밀리초�?변??
#define JOYKNOBMAX	42 * _2X

//#define NUMTTF
//#define INITPOPUP

typedef enum _reel {
	SLOTSIZE_X = 512,
	SLOTSIZE_Y = 218,

	REELSIZE_X = 156,
	REELSIZE_Y = 290,

	REEL_BG_NORMAL = 0,   // ?�반(?��?/?�???�정)
	REEL_BG_MASK = 1,   // 가�?중속/감속B)
	REEL_BG_FAST = 2,    // 고속(고속/감속A)

	REEL_TOTAL_FRAME = 120,

	REEL_STATE_IDLE = 0,   // ?��?(?�작 ???��? ?��?)
	REEL_STATE_SLOW,       // ?�??가??초반)
	REEL_STATE_MID,        // 중속
	REEL_STATE_FAST,       // 고속(?�기 ?�과 ON)
	REEL_STATE_DECEL,      // 감속
	REEL_STATE_SNAP        // ?�정 ?�냅 ?�레??
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
	LANGUAGE_KOREAN = 0,//?�국??
	LANGUAGE_ENGLISH,//?�어
	LANGUAGE_JAPAN,//?�어

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
	TIP_INTRODUCE = 0,//?�개
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

	SCREEN1 = 0,    //1?�분�?
	SCREEN2,        //2?�분�?
	SCREEN3,        //3?�분�?

	SCREENDARKEN = 24,

	


	ACCEMAXLEVEL = 50,
	TOTALACCESTATTYPE = 6,

	//공격?�태
	ATTACK_CRITICAL = 0,
	ATTACK_EXTRA,
	ATTACK_STUN,
	ATTACK_IGNORE,
	ATTACK_KNOCKBACK,
	ATTACK_PIERCE,
	ATTACK_MISS,
	ATTACK_BLOCK,
	ATTACK_DODGE,

	//?�태?�상
	SLOW = 0,	//?�로??>공격?�?�밍??2배로 ?�어�?
	BLIND,	//블라?�드(미스가 많이 ??->미스 100% 걸림
	POISON,	//??>?�간??지?�면 ?�데미�?�?받음
	STUN,	//기절->?�정?�간 공격??못함
	CURSE,	//?��?MP�??�용못함)->공격??못함
	KNOCKBACK,	//밀?�내�?
	TOTALDEBUF,

	ATTRWORD = 101,
	ENEMYATTRDATASIZE = 12,



	POISONDMGPER = 2,
	DARKDMGPER = 5,
	PROCPER = 100,

	//강화?�과
	//로빈
	INC_VIT = 0,//INC_VIT	= 0,	//방어?�세 : ?�정?�간 VIT ?�승->?�택???�의 ?��?지�?감소->??방어??감소 
	BARRIER,	//?�신?�모 : MP ?�모?�여 ?��?지 경감->?�군 방어??증�?
#ifdef SKILL_ROBIN15_DAMAGExN
	DAMAGExN,	//?��?지N�?
#else
	HPRESTORE,//,	//?�유?�착 : ??공격 ?�피??HP ?�승->?�정기간?�안 ??공격?�피
#endif	
	MPRESTORE,	//?�정침착 : ?��?지 ?�으�?MP ?�복
	REFLECTION,	//리플?�션 : ?�률로데미�? 반사

	//?�아??
	BERSERK,	//?�분고조 : 방어???�??공격???�승
	MPDRAIN,	//?�마?�마??: 공격??MP ?�수->HP ?�수�?변�?
	INC_CRITICAL,	//?�살집중 : ?�리 ?�승
	INC_IGNORE,	//?�마?�직�?: ?�정?�간 ??방어 무시

	//맥스
	HPDRAIN,	//블러?�헌??: ??공격??HP ?�복
	INC_EVASION,	//?��?무도 : ?�정?�간 ?�피??증�?
#ifdef SKILL_MAXX16_ERASEALLDEBUF 
	EVASIONTOHP,	//?�도?�한??: ??공격 ?�피??HP ?�복
#else
	EVASIONTOMP,	//?�도?�한??: ??공격 ?�피??MP ?�복
#endif
	INC_STUN,	//?�신분리 : 기절 ?�률 ?�승

	TOTALPLAYERBUFF,

	//반�?
	INC_DAMAGE_RING = TOTALPLAYERBUFF,	//공격??증�? : ??��??반�?
	INC_DEFENSE_RING,	//방어??증�? : 골렘??반�?
	INC_EVASION_RING,	//?�피 증�? : 광�???반�?
	INC_PIERCE_RING,	//관??증�? : ?�한??반�?
	INC_HIT_RING,	//?�중 증�? : ?�념??반�?
	INC_STUN_RING,	//기절공격 증�? : 광포??반�?
	INC_CRITICAL_RING,	//치명?� 증�? : ?�자??반�?
	INC_CRITDMG_RING,	//치명?� ?��?지 증�? : 궁극??반�?
	INC_IGNORE_RING,	//??방어??무시 증�? : 차원??반�?
	INC_EXP_RING,	//경험�??�득 증�? : ?�운??반�?(?�용?�함)
	INC_EXTRA_RING,	//추�??� 증�? : ?�운??반�?(?�용)
	INC_ABSORB_RING,	//물리?��?지 ?�수 증�? : ?�생??반�?(?�용)

	//비약
	INC_DAMAGE_ARENA,
	INC_DEFENSE_ARENA,
	INC_MAGIC_ARENA,
	INC_SKILL_ARENA,

	TOTALBUFF,

	//?�트마크
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

	//?�화
	TOTALCURRENCYMARKARR = 10,
	TOTALCURRENCYMARK = 100,
	CURRENCYMOVESPEED = 16 * _2X,
	CURRENCYMARKEFFECTFRAME = FPS / 2,
	CURRENCYDONTERASE = 10000,
	//?�이??
	TOTALITEMMARK = 30,

	SKILLPERSWORD = 12,
	ACTIONCARDDATASIZE = 9,
	SWORDSKILLINFODATASIZE = 3,


	//��ųŸ��
	PASSIVE = 0,//�Ϲ� �нú� ��ų(����� �Ⱦ���)
	ACTIVE,//�Ϲ� ��Ƽ�� ��ų(����� �Ⱦ���)
	CREWBULLET,//��ź ����
	SUMMON,//��ȯ
	HEROSKILL,//������� ��ų�� ȣ��
	SUMMONHERO,//���ΰ� ���� �ٸ� ����� ��ȯ

	//?�류?�??
	// 
	//?�반
	//?�리?�컬(?��?지 2�?
	//관?�공�??�에?�까지 공격)
	//추�??��??��?지)
	
	//?��?�??�턴(1??
	//중독걸기(3?�간 중독 ?��?지)
	//?�화(1?? 멈추??1???�안 공격??받�? ?�음 �??�럴?�는 버프류로 ?�리?�게 좋음) 
	
	//?�염?�??��(?�개 ?�면 ?��?지 1)
	//?�기?�??��(?�개 ?�면 ?��?지 1)
	//번개?�??��(?�개 ?�면 ?��?지 1)
	//?�성?�??��(?�개 ?�면 ?��?지 1)
	//?�흑?�??��(?�개 ?�면 ?��?지 1)

	//골드?�득 증�?(?�득 골드 2�?케?�스?� ?�득 골드 +1000 ??
	//검 공격??추�?
	//?�염공격???�개 ?�면 ?��?지 ?�배)
	//?�기공격???�개 ?�면 ?��?지 ?�배)
	//번개공격???�개 ?�면 ?��?지 ?�배)
	//?�성공격???�개 ?�면 ?��?지 ?�배)
	//?�흑공격???�개 ?�면 ?��?지 ?�배)
	//방어??무시 공격(방어?�이 ?�청 강한 몬스?��? ?��?지�?줘서 ?�방??죽임)
	//?�피(?�턴?�안 ?��?지�?받�? ?�는??)
	//?�면??3?�동???�공격에 걸리지 ?�는??)
	//?�턴면역(3?�동???�턴??걸리지 ?�는??)

	//로빈?�킬-?�어?�래??: 공중?�에�??��?지 2�?
	//로빈?�킬-마구찌르�?
	//로빈?�킬-부?�트?�래??: 기절(100% 기절)
	//로빈?�킬-?�이?�차지 : ?�격공격(?�을 ?�로 ?�린?��? 무슨 ?��?가 ?��??
	//로빈?�킬-?�울?�래??: ?�것??기절?�야?
	//로빈?�킬-?�솔루트?�어??: 찔러???�전
	//로빈?�킬-멸살?�참 : 최강?��?지
	//로빈?�킬-방어?�세 : HP�??�간?�으�?부?�?�서 ???��?지�?받는?? 

	CREWTYPE_NORMAL = 0,
	CREWTYPE_ATTACKSKILL,
	CREWTYPE_BUFFSKILL,
	CREWTYPE_SUMMON,
	CREWTYPE_HEART,

	TOTAL_CREWTYPE,

	MAXHOTKEY = 3,//
	QUICKSLOTGAP = 80 * _2X,

	RINGKEY = MAXHOTKEY,

	//�??�파??
	NORMALROOM = 0,
	ENEMYROOM,

	//맵�???

	MAXMAPSIZE_X = 100 * TSIZE,
	MAXMAPSIZE_Y = 42 * TSIZE,

	MAXTILECOUNT = 88,

	//배경Rect?�자
	MAXRECT = 8,
	//?�경?�브?�트
	MAXBACKOBJ = 65,
	//근경
	MAXFOREOBJ = 51,
	//중립 ?�브?�트
	MAXNEUTRALOBJ = 18,
	//?�직이??배경 ?�브?�트
	MAXBGOBJECT = 32,

	//?�??충돌 관??
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

	//?�탈 ?�테?��?

	STAGELIST_Y = DIORAMASIZE_Y * 2 / 3,
	//?�테?��? 마다 방개?�는 5�?
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

	ARENAITEMFRAME = FPS * 10,//?�기?�에??보스몹잡?�을???�이?�이 ?�랍?�는 최�? ?�레??
	ARENALIMITTIME = 60 * 60 * 24 * 3,//보스?��? 10초안???�리???�야 ?�다.
	ARENABUFFTIME = FPS * 100,

	MINUTES = FPS * 60,

	ARENAANIMATIONFRAME = 8,

	CREWDATA_TYPE = 0,
	CREWDATA_STR,
	CREWDATA_SKILL1,
	CREWDATA_SKILL2,
	CREWDATA_SKILL3,
	CREWDATA_CASTLEIDX,
	CREWDATASIZE,
	//TYPE, STAR, PRICE, BULLETDATA
	CMFFRAMEPOSITIONDATASIZE = 6,

	CREW_MENU = 0,//메뉴�??�려주는 ?�포??
	CREW_GOODS,//?�화�??�산?�는 ?�포??
	CREW_ABILITY,//?�빌리티�??�려주는 ?�포??
	CREW_EQUIP,//?�비�??�산?�는 ?�포??

	//MP�?붙이??
	//MP�??�용?�서 ?�킬???�용. 

	//?�화
	//?�이?�몬??캐시) -> ?�환,  
	//?�메?�드 -> ?�킬?�롯, ?�비개수 ??
	//골드()->?�벨??
	//강화??)->강화
	//?�킬카드()
	//?�금?�쇠(구매�??�면 ?�이???�별)
	//
	//?�을 공격?�면 기본?�으�?골드?� 경험치만 ?�온??

	MENU_PLAY = 0,//캐릭?�메??: 캐릭?��? ?�벨?�하�??�탯(STAT_STR, STAT_VIT, STAT_AGI, STAT_INT)??찍는 부�?
	MENU_HERO,
	MENU_CREW,
	MENU_COLLECTIONS,//?�비, ?�환?? 기�?
	MENU_CASTLE,//?�메??
	MENU_SHOP,//?�점메뉴 : ?�환(무기, 방어�? ?�세?�리, ?�킬카드,  ), ?�키지(), ?�화(), ?�금?�쇠()  
	MENU_STARSHOP,
	MENU_FRIENDS,
	MENU_NEWS,
	MENU_GIFTS,
	MENU_LEADERBOARD,//가???�테?��?�?많이 진행???��? 
	MENU_INVITEFREINDS,
	MENU_CALENDAR,
	MENU_SETTING,
	MENU_JOKBO,

	MENU_LIST,
	MENU_GAMEEVENT,
	MENU_BOSSRAID,
	MENU_STAGEINFO,

	MENU_BATTLE,//?�기?�는 ?�반 몹과 ?�우?�것?�로
	MENU_RAID,

	MENU_GAMERESET,//게임초기??

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
	CURRENCY_GOLD,//기본코인
	CURRENCY_MEDAL,//?�투?�서 ?�리?�면 받는 ?�인?�는 메달 
	CURRENCY_COIN,//뽑기??주로 ?�용?�고, 
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


	LOG_EVENT_QUESTSTART = 0,//?�벤???�픈
	//?�스???�이�?+ ?�스???�름 + ?�스?��? ?�성?�되?�습?�다
	LOG_EVENT_BATTLESTART,
	//배�? ?�이�?+ 배�????�성???�었?�니??
	LOG_EVENT_RAIDSTART,
	//?�이???�이�?+ ?�이?��? ?�성???�었?�니??
	LOG_RAID,//??보스??침공
	//??보스 cmf + ?�어가??골드 + ?�어갔습?�다.
	LOG_BATTLE,//??보스???�료 무력??
	//??보스 cmf + 침공?�서 + 무력?�된 ???�료 ?�이콘이 무력???�었?�니??
	LOG_BOSSGETCOIN,//보스 ??
	//??보스 cmf + ???�료�??�해??+ 골드?�이�?+ 금액 + ?�복?�습?�다.
	LOG_SKILL,//?�킬
	LOG_BETHEART,//?�트 증�?
	LOG_BETCOIN,

	TOTAL_LOG,


	TOTALBUFFSHOP = 3,
	BUFFSHOPDATASIZE = 5,

	TOTALMEDALSHOP = 3,
	MEDALSHOPDATASIZE = 5,

	//?�간?�
	OXYGEN = 200,

	TOTALOPTION = 12,

	END_GAMEDEF
} GAMEDEF;


#define CURRENCYICON_STARTSIZE 1.0f
#define CURRENCYICON_ENDSIZE 1.5f
#define CURRENCYICON_ENDSIZE2 2.0f
/*
//?�성??관???�파??
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

	//카테고리�?�?��
	REPORT_ARENA_COUNT = 9,
	REPORT_VILLAGE_COUNT = 9,
	REPORT_AREA_COUNT = 8,
	REPORT_ITEM_COUNT = 8,
	REPORT_MONSTER_COUNT = 28,
	REPORT_COMBAT_COUNT = 10,
	REPORT_STAT_COUNT = 15,
	REPORT_ETC_COUNT = 10,

	//카테고리�??�작 ?�덱??
	REPORT_ARENA_START = 0,
	REPORT_VILLAGE_START = REPORT_ARENA_START + REPORT_ARENA_COUNT,
	REPORT_AREA_START = REPORT_VILLAGE_START + REPORT_VILLAGE_COUNT,
	REPORT_ITEM_START = REPORT_AREA_START + REPORT_AREA_COUNT,
	REPORT_MONSTER_START = REPORT_ITEM_START + REPORT_ITEM_COUNT,
	REPORT_COMBAT_START = REPORT_MONSTER_START + REPORT_MONSTER_COUNT,
	REPORT_STAT_START = REPORT_COMBAT_START + REPORT_COMBAT_COUNT,
	REPORT_ETC_START = REPORT_STAT_START + REPORT_STAT_COUNT,

	//?�기??�?길드
	REPORT_ARENA0 = 0,	//강자??�??�기???�장 ?�수)
	REPORT_ARENA1,	//지?�의 �??�투기장 ?�장 ?�수)
	REPORT_ARENA2,	//강자??명성(?�기??100�??�달)
	REPORT_ARENA3,	//지?�의 명성(?�투기장 100�??�달)
	REPORT_ARENA4,	//?�극?�인 참여(길드??참여 ?�수)
	REPORT_ARENA5,	//?�기?�의 지배자(?�기?�에??죽인 ???�자)
	REPORT_ARENA6,	//지?�의 지배자(?�투기장?�서 죽인 ???�자)
	REPORT_ARENA7,	//매일 매일 꾸�????�일�??�스???�행 ?�수)
	REPORT_ARENA8,	//거인 ?�치(?�기?�에??NPC ?�치 ?�수)

	//마을
	REPORT_VILLAGE0,		//?�꾸?�기(?��????�용???�수)
	REPORT_VILLAGE1,		//?�골?�님(?�인??�?1명에게서 ?�이??구입????
	REPORT_VILLAGE2,		//강한 ?�비�??�하??강화 ?�수)
	REPORT_VILLAGE3,		//불굴??강화(강화 ?�패 ?�수)
	REPORT_VILLAGE4,		//블랙?��????�비 ?�작 ?�수)
	REPORT_VILLAGE5,		//??��리마?�터(보석 ?�착 ?�수)
	REPORT_VILLAGE6,		//?�뜰??모험???�점?�다가 ?�이?�을 ?�매???�수)
	REPORT_VILLAGE7,		//공간???�리????귀?�서 ?�용???�수)
	REPORT_VILLAGE8,		//?�웃?�촌(?�람?�에�?말을 �??�수)

	//지??
	REPORT_AREA0,	//?�험??추구?�는 ??모든 강적 지??�??�어가�?
	REPORT_AREA1,	//?�상???�험?�는 ??미니�?100%)
	REPORT_AREA2,	//?�괴???�인(찍기 블록 모두 ?�괴??
	REPORT_AREA3,	//?�양???�괴?�는 ??SUN 블록 모두 ?�괴??
	REPORT_AREA4,	//?�간 ?�동???�인(모든 ?�프블록 ?�용??
	REPORT_AREA5,	//?�디???�을�?(?�드???�겨�??�이??모두 찾으�?
	REPORT_AREA6,	//?�레???�터(?� 캐릭?�용 ?�자�??�외??모든 보물?�자 ?�득)
	REPORT_AREA7,	//?�행?�의 ?�내??모든 ?��??�을 ?�으�?

	//?�이??
	REPORT_ITEM0,		//목걸???�집가(?�급??관계없??모든 목걸?��? ?�벤?�리???�을 ??
	REPORT_ITEM1,		//반�????�왕(?�급 관계없??모든 반�?�??�벤?�리??가지�??�으�?
	REPORT_ITEM2,		//무기 ?�집가(모든 무기(?�급 ?��? ?�음)�??�벤?�리??가지�??�으�?
	REPORT_ITEM3,		//갑옷 ?�집가(모든 갑옷(?�급 ?��? ?�음) ?�벤?�리??가지�??�으�?
	REPORT_ITEM4,		//바�? ?�집가(모든 바�?(?�급 ?��? ?�음) ?�벤?�리??가지�??�으�?
	REPORT_ITEM5,		//모자 ?�집가(모든 모자(?�급 ?��? ?�음) ?�벤?�리??가지�??�으�?
	REPORT_ITEM6,		//?�갑 ?�집가(모든 ?�갑(?�급 ?��? ?�음) ?�벤?�리??가지�??�으�?
	REPORT_ITEM7,		//?�발 ?�집가(모든 ?�발(?�급 ?��? ?�음) ?�벤?�리??가지�??�으�?

	//몬스??
	REPORT_MONSTER0,	//?��????�냥�??�레???��??�서 ?�치??몬스??마릿??
	REPORT_MONSTER1,	//계곡???�냥�?금단??계곡?�서 ?�치??몬스??마릿??
	REPORT_MONSTER2,	//바다???�냥�??��??�?�스?�서 ?�치??몬스??마릿??
	REPORT_MONSTER3,	//지?�의 ?�냥�?지?�도?�서 ?�치??몬스??마릿??
	REPORT_MONSTER4,	//?�원???�냥�??�델 ?�원?�서 ?�치??몬스??마릿??
	REPORT_MONSTER5,	//불꽃???�냥�??�염???�지?�서 ?�치??몬스??마릿??
	REPORT_MONSTER6,	//?�음???�냥�??�구??빙원?�서 ?�치??몬스??마릿??
	REPORT_MONSTER7,	//번개???�냥�??�뇌??공방?�서 ?�치??몬스??마릿??
	REPORT_MONSTER8,	//?�혼???�냥�??�혼???�역?�서 ?�치??몬스??마릿??
	REPORT_MONSTER9,	//?�곡???�냥�?골렘???�곡?�서 ?�치??몬스??마릿??
	REPORT_MONSTER10,	//?�연???�냥�?칠흑???�연?�서 ?�치??몬스??마릿??
	REPORT_MONSTER11,	//명계???�냥�?망자???�시?�서 ?�치??몬스??마릿??
	REPORT_MONSTER12,	//?�래�??�레?�어(?�래곤의 무덤?�서 ?�치??몬스??마릿??
	REPORT_MONSTER13,	//캐슬 ?�래??마왕?�에???�치??몬스??마릿??
	REPORT_MONSTER14,	//?�페?�스 마린(?�주?�서 ?�치??몬스??마릿??
	REPORT_MONSTER15,	//?��????�장(?�드 뮤턴?��? ?�치???�수)
	REPORT_MONSTER16,	//계곡???�장(?�르곤을 ?�치???�수)
	REPORT_MONSTER17,	//?��? ?�장(카툼???�치???�수)
	REPORT_MONSTER18,	//고�? ?�장(고�????�호?��? ?�치???�수)
	REPORT_MONSTER19,	//불꽃 ?�장(?�프리트�??�치???�수)
	REPORT_MONSTER20,	//?�음 ?�장(?�로?�트�??�치???�수)
	REPORT_MONSTER21,	//번개 ?�장(?�이?�너�??�치???�수)
	REPORT_MONSTER22,	//빛의 ?�장(?�루?��? ?�치???�수)
	REPORT_MONSTER23,	//지?�도???�장(마도?�성?��? ?�치???�수)
	REPORT_MONSTER24,	//?�곡???�장(고�???방주�??�치???�수)
	REPORT_MONSTER25,	//?�둠???�장(?�리만을 ?�치???�수)
	REPORT_MONSTER26,	//?�흑룡의 ?�장(?�어맷을 ?�치???�수)
	REPORT_MONSTER27,	//명계???�장(죽음???�을 ?�치???�수)

	//?�투
	REPORT_COMBAT0,		//?�길???�는 ?��?(캐릭?�보???�벨??10?�상 ??? 몬스?��? 죽인 ?�수)
	REPORT_COMBAT1,		//?�임?�는 공격(?�에�??�힌 ?��?지???�적총합)
	REPORT_COMBAT2,		//맷집???�계(?�에�?받�? ?�해???�적총합)
	REPORT_COMBAT3,		//???�을 지켜라(방을 ??��지 ?�고 ?��? 몬스??마릿??
	REPORT_COMBAT4,		//진정???�웅(HP가 1???�태?�서 ?�속?�로 몬스???��? ?�수)
	REPORT_COMBAT5,		//버프마스??버프 ?�용 ?�수)
	REPORT_COMBAT6,		//종합병원(?�태?�상 걸린 ?�수)
	REPORT_COMBAT7,		//?�려??기술(버프 ?�외?�스???�용 ?�수)
	REPORT_COMBAT8,		//좀�?부?�약??먹�? ?�수)
	REPORT_COMBAT9,		//?�인(?�을 공격?��? ?�고 ?�속?�로 죽�? ?�수)

	//?�력�?
	REPORT_STAT0,		//?��??�는 ?�벨???�용?��? ?��? AP????
	REPORT_STAT1,		//?�킬?�이 ?�운???�용?��? ?��? SP????
	REPORT_STAT2,		//최강??공격??공격??총합)
	REPORT_STAT3,		//최강??방어??방어??총합)
	REPORT_STAT4,		//?�확??공격(명중�?%)
	REPORT_STAT5,		//?�빠�??�피(?�피 %)
	REPORT_STAT6,		//?�살???�격(?�리?�컬 ?�률 %)
	REPORT_STAT7,		//?�속?�는 공격(추�??� ?�률)
	REPORT_STAT8,		//꿰뚫??공격(관?�공�??�률)
	REPORT_STAT9,		//충격?�인 공격(기절 %)
	REPORT_STAT10,	//막을 ???�는 공격(방어??무시 공격 ?�률)
	REPORT_STAT11,	//??��가???�운 증�? %)
	REPORT_STAT12,	//금전??골드 ?�득 %)
	REPORT_STAT13,	//경험??부??경험�??�득 %)
	REPORT_STAT14,	//?�인??주머??지금까지 ?��? ??총합)

	//기�?
	REPORT_ETC0,	//?��????�적(모든 ?�브 ?�스??)
	REPORT_ETC1,	//?�버?�딩 ?�토�??�레???�??
	REPORT_ETC2,	//?�수부(?�중????�??�어가???�는 ?�간)
	REPORT_ETC3,	//멀미유�??�둠???�편?????�간(?�적))
	REPORT_ETC4,	//글?�이?�처???�강 ?�계?�간)
	REPORT_ETC5,	//?��??��?(?�벤?�리???�는 ??
	REPORT_ETC6,	//방구???�인(??방에???�무것도 ?��? ?�고 ?�는 ?�간)
	REPORT_ETC7,	//지?�선 ?�머(?�으�??�동??거리 (?�평?�로 ?�?�수 측정))
	REPORT_ETC8,	//?�늘 ?�까지(?�로 ?�라�?거리 (?�직?�로 ?�?�수 측정))
	REPORT_ETC9,	//블랙 & ?�이??블랙?� ?�과 ?�수(?�적))

	//?�칭
	PLAYER_TITLE0,		//길드???�등공신(길드?�에??1??
	PLAYER_TITLE1,		//?�중??모험???�세?�리�??�함??모든 ?�비�?갖춰?�었?�때)
	PLAYER_TITLE2,		//?�속???�살??60�??�에 ??15마리�??�치?�다.)
	PLAYER_TITLE3,		//?�트?�이�??�령?�을 ?�져????번에 3마리�??�치?�다.)
	PLAYER_TITLE4,		//?�격?�???�?�어?�으�?몬스?��? 777마리 격파)
	PLAYER_TITLE5,		//?�기?�마?�터(?�기?�을 1???�까지 ?�파?�다.)
	PLAYER_TITLE6,		//보석?�호가(?�켓??3개이?�인 ?�비??모두 보석??박으�?
	PLAYER_TITLE7,		//주제�?모르?????�의 공격 ??방에 ???��? �??�상 깍인 ?�수)
	PLAYER_TITLE8,		//?�아??천정??머리�?부?�힌 ?�수가 500???�프?�이가 천정??머리가 ?�는 ?�상 ?�라갈수?�을??�??�정))
	PLAYER_TITLE9,		//벌거벗�? ?�냥�?무기�??�비?�고 몬스?��? ?�치??마릿?��? 100마리)
	PLAYER_TITLE10,	//?�?�배(?�이?�이 방안??5개이???��??�는??먹�??�고 ?�음방으�??�어간다.)
	PLAYER_TITLE11,	//?�생????��?????�벤???�는 ?�이 7777)
	PLAYER_TITLE12,	//진정??갑�?(?�료 ?�이??구입 개수가 20�?
	PLAYER_TITLE13,	//?�카?�다?�버(?�래곤의 ??먹으???�어?�릴??걸림?�이 바닥까�? 간다.)
	PLAYER_TITLE14,	//?�화???�자 간디(?�을 죽이지 ?�고 ?�속?�로 20개의 방을 ?�동(마을?��??�선 무효. 마을???�어가�?카운?�리??)
	PLAYER_TITLE15,	//?�물중독???�용???�션?�수(?�앗,?�브)가 ?�적 100개에 ?�달)
	PLAYER_TITLE16,	//롤링마스???�둠???�편 ?�이�??�어지지 ?�고 ?�다갔다 ???�수 ?�적 100�?
	PLAYER_TITLE17,	//건망�??�제(?�료?��? ?��? ?�스?��? 10�??�상?�적)
	PLAYER_TITLE18,	//기본기의 ?�인(?�킬 ?�용?��? ?�고 ?�임?�몬?�터�??�치???�수(기본 공격, 찍기, ?�??공격))
	PLAYER_TITLE19,	//4�??�????공격 ??방에 ?�의 체력??�??�상 깍인 ?�수 ?�적 500�?
	PLAYER_TITLE20,	//구제불능 방향�?(?�렘, 벨로?�에??집에 ?�어가???�무?�게??말을 걸�??�고 ?�시 ?�간 ?�수?�적 100??
	PLAYER_TITLE21,	//?�서�??�델?�인 ?�서관??방문???�수)
	PLAYER_TITLE22,	//?�피???�인(HP가 최�?HP??10% ?�하?�때 귀?�서�??�용???�수 ?�적)
	PLAYER_TITLE23,	//?�커(최�? HP가 1000?�파)
	PLAYER_TITLE24,	//코스?�플?�이??무기?�외?�고 ?�른 주인공의 ?�비�??�일?�서 ?�는??)
	PLAYER_TITLE25,	//?�설???�?�장??강화�?10?�계까�? ?�공?�다.)
	PLAYER_TITLE26,	//근성?�치??강자(?�기?�에???�복?��??�고 죽인 ???��? 50마리 ?�상)
	PLAYER_TITLE27,	//?�성???�제(물약?�로 ?�버???�복???�수)
	PLAYER_TITLE28,	//?�전과제???�행??모든 ?�성???�료)
	PLAYER_TITLE29,	//?�주???�명?�사(?�것???�외??모든 ?�칭 ?�수)

	TOTAL_REPORT,

	TOTAL_PLAYERTITLE = 30,

	END_REPORTDEF
} REPORTDEF;
*/

typedef enum _prgDef {
	//Data.h 배열�?기�? ?�기
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

	//각종?�레??
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

	

	//감정
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

	
	MAXCMF = TOTALCMF,//@@ ?�중??계산?�보�?줄여줄것
	REALMAXCMF = TOTALCMF,	//?�스???�라?�언?�용 CMF
	CLIENTCMF = REALMAXCMF,

	

	AIRETRYCOUNT = 100,

	
	HERO_PARAM_DMG = 0,//?��?지
	HERO_PARAM_SDMG,//?�킬?��?지
	HERO_PARAM_ASPD,//공격?�도
	HERO_PARAM_MSPD,//?�동?�도
	HERO_PARAM_HP,//체력
	HERO_PARAM_DEF,//방어??

	TOTAL_HERO_PARAM,

	DIANAACTIVELEVEL = 5,
	MAXXACTIVELEVEL = 10,
	//?�직임 ?�태
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

	ADTYPE_SOLDIER = 0,//?�병광고(?�치?�면 ?�병메뉴�?가지�??�직 ?�병메뉴가 ?�픈?��? ?�았?�면 갈수 ?�다??메시지�??�워준??)
	ADTYPE_GOODS,//?�금 ?�이?�트 구매?�품(?�치?�면 구매?�업?�로)
	ADTYPE_ITEMS,//?�른 ?��?가 6?�이??무기�??�거???�설?�급무기�??�었????


	
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

	//50?� 기본
	LVUPREWARD_HEARTMAX,

	//?�트 ?�성??
	LVUPREWARD_HEARTPERHOUR,

	//방패 최�???
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

	DAILYQUEST_OPEN_BOX_GETEQUIP = 0,//?�자�??�어 ?�비�?3�??�으�?
	DAILYQUEST_UPGRADE_CREW,//3개�? ?�그?�이?�하�??�는�?
	DAILYQUEST_ATTACK_OTHERUSER,//Battle, Raid ?�함
	DAILYQUEST_COLLECT_GOLD,//?�정금액???�을 모으�?
	DAILYQUEST_STAGE_TRY,//?�테?��? ?�투 

	TOTAL_DAILYQUEST_TYPE,

	BOXOPENITEMFRAMEINFOSIZE = 6,


} DAILYQUEST;

enum JumpState {
	JS_IDLE = 0,     // ?��?(?�있??
	JS_SPINNING,     // ?�프 �?+ 공중?�서 계속 교체
	JS_LANDING,      // 착�? 구간(공중?�서 교체?�다가 착�? ?�간 target ?�정)
	JS_HOLD,     // 착�? ???�출 ?��??�로??
	JS_DONE          // ?�정 ??고정
};

#define ITEMTYPESEED 1000
#define ITEMDETAILSEED 10000
#define MAX_POINTS 500 * MOTIONDIV // 최�? 좌표 개수
#define MAX_RADIUS 256 // 최�? 반경
#define MAX_BOXRADIUS	128

#define BOSSROOMTIME	60 * 10//10�?

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
