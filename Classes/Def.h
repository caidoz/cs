#pragma once

#ifndef _DEF_H_
#define _DEF_H_


// ================================
// 분리된 설정 파일들 include
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


//매크로

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


//30분 기준(하트 하나당 30분마다 하나씩 찬다고 보면 됨)
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
//GotoObj or GotoObjXY가 작동하기 위한 최소값
#define SPEED_MIN	4
#define DAYS3 3 * 24 * 60 * 60 * 1000 // 3일을 밀리초로 변환
#define JOYKNOBMAX	42 * _2X

//#define NUMTTF
//#define INITPOPUP

typedef enum _reel {
	SLOTSIZE_X = 512,
	SLOTSIZE_Y = 218,

	REELSIZE_X = 156,
	REELSIZE_Y = 290,

	REEL_BG_NORMAL = 0,   // 일반(정지/저속/확정)
	REEL_BG_MASK = 1,   // 가림(중속/감속B)
	REEL_BG_FAST = 2,    // 고속(고속/감속A)

	REEL_TOTAL_FRAME = 120,

	REEL_STATE_IDLE = 0,   // 정지(시작 전/정지 유지)
	REEL_STATE_SLOW,       // 저속(가속 초반)
	REEL_STATE_MID,        // 중속
	REEL_STATE_FAST,       // 고속(전기 효과 ON)
	REEL_STATE_DECEL,      // 감속
	REEL_STATE_SNAP        // 확정 스냅 프레임
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
	LANGUAGE_KOREAN = 0,//한국어
	LANGUAGE_ENGLISH,//영어
	LANGUAGE_JAPAN,//일어

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
	TIP_INTRODUCE = 0,//소개
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

	SCREEN1 = 0,    //1사분면
	SCREEN2,        //2사분면
	SCREEN3,        //3사분면

	SCREENDARKEN = 24,

	


	ACCEMAXLEVEL = 50,
	TOTALACCESTATTYPE = 6,

	//공격상태
	ATTACK_CRITICAL = 0,
	ATTACK_EXTRA,
	ATTACK_STUN,
	ATTACK_IGNORE,
	ATTACK_KNOCKBACK,
	ATTACK_PIERCE,
	ATTACK_MISS,
	ATTACK_BLOCK,
	ATTACK_DODGE,

	//상태이상
	SLOW = 0,	//슬로우->공격타이밍이 2배로 늘어짐
	BLIND,	//블라인드(미스가 많이 남)->미스 100% 걸림
	POISON,	//독->시간이 지나면 독데미지를 받음
	STUN,	//기절->일정시간 공격을 못함
	CURSE,	//저주(MP를 사용못함)->공격을 못함
	KNOCKBACK,	//밀어내기
	TOTALDEBUF,

	ATTRWORD = 101,
	ENEMYATTRDATASIZE = 12,



	POISONDMGPER = 2,
	DARKDMGPER = 5,
	PROCPER = 100,

	//강화효과
	//로빈
	INC_VIT = 0,//INC_VIT	= 0,	//방어태세 : 일정시간 VIT 상승->선택된 적의 데미지를 감소->적 방어력 감소 
	BARRIER,	//정신소모 : MP 소모하여 데미지 경감->아군 방어력 증가
#ifdef SKILL_ROBIN15_DAMAGExN
	DAMAGExN,	//데미지N배
#else
	HPRESTORE,//,	//여유포착 : 적 공격 회피시 HP 상승->일정기간동안 적 공격회피
#endif	
	MPRESTORE,	//냉정침착 : 데미지 입으면 MP 회복
	REFLECTION,	//리플렉션 : 확률로데미지 반사

	//디아나
	BERSERK,	//흥분고조 : 방어력 저하 공격력 상승
	MPDRAIN,	//흡마의마탄 : 공격시 MP 흡수->HP 흡수로 변경
	INC_CRITICAL,	//필살집중 : 크리 상승
	INC_IGNORE,	//파마의직격 : 일정시간 적 방어 무시

	//맥스
	HPDRAIN,	//블러드헌트 : 적 공격시 HP 회복
	INC_EVASION,	//현란무도 : 일정시간 회피율 증가
#ifdef SKILL_MAXX16_ERASEALLDEBUF 
	EVASIONTOHP,	//안도의한숨 : 적 공격 회피시 HP 회복
#else
	EVASIONTOMP,	//안도의한숨 : 적 공격 회피시 MP 회복
#endif
	INC_STUN,	//혼신분리 : 기절 확률 상승

	TOTALPLAYERBUFF,

	//반지
	INC_DAMAGE_RING = TOTALPLAYERBUFF,	//공격력 증가 : 폭주의 반지
	INC_DEFENSE_RING,	//방어도 증가 : 골렘의 반지
	INC_EVASION_RING,	//회피 증가 : 광대의 반지
	INC_PIERCE_RING,	//관통 증가 : 원한의 반지
	INC_HIT_RING,	//적중 증가 : 신념의 반지
	INC_STUN_RING,	//기절공격 증가 : 광포의 반지
	INC_CRITICAL_RING,	//치명타 증가 : 승자의 반지
	INC_CRITDMG_RING,	//치명타 데미지 증가 : 궁극의 반지
	INC_IGNORE_RING,	//적 방어도 무시 증가 : 차원의 반지
	INC_EXP_RING,	//경험치 획득 증가 : 행운의 반지(사용안함)
	INC_EXTRA_RING,	//추가타 증가 : 행운의 반지(사용)
	INC_ABSORB_RING,	//물리데미지 흡수 증가 : 회생의 반지(사용)

	//비약
	INC_DAMAGE_ARENA,
	INC_DEFENSE_ARENA,
	INC_MAGIC_ARENA,
	INC_SKILL_ARENA,

	TOTALBUFF,

	//히트마크
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

	//재화
	TOTALCURRENCYMARKARR = 10,
	TOTALCURRENCYMARK = 100,
	CURRENCYMOVESPEED = 16 * _2X,
	CURRENCYMARKEFFECTFRAME = FPS / 2,
	CURRENCYDONTERASE = 10000,
	//아이템
	TOTALITEMMARK = 30,

	SKILLPERSWORD = 12,
	ACTIONCARDDATASIZE = 9,
	SWORDSKILLINFODATASIZE = 3,


	//스킬관련 정의
	PASSIVE = 0,//패시브에서는 아무것도 없다.
	ACTIVE,//일반공격 혹은 버프
	CREWBULLET,//크류의 공격
	SUMMON,//소환
	HEROSKILL,//히어로 공격스킬

	//크류타입
	// 
	//일반
	//크리티컬(데미지 2배)
	//관통공격(뒤에적까지 공격)
	//추가타격(데미지)
	
	//상대방 스턴(1턴)
	//중독걸기(3턴간 중독 데미지)
	//석화(1턴, 멈추되 1턴 동안 공격을 받지 않음 즉 이럴때는 버프류로 돌리는게 좋음) 
	
	//화염저항력(세개 뜨면 데미지 1)
	//냉기저항력(세개 뜨면 데미지 1)
	//번개저항력(세개 뜨면 데미지 1)
	//신성저항력(세개 뜨면 데미지 1)
	//암흑저항력(세개 뜨면 데미지 1)

	//골드획득 증가(획득 골드 2배 케이스와 획득 골드 +1000 등)
	//검 공격력 추가
	//화염공격력(세개 뜨면 데미지 두배)
	//냉기공격력(세개 뜨면 데미지 두배)
	//번개공격력(세개 뜨면 데미지 두배)
	//신성공격력(세개 뜨면 데미지 두배)
	//암흑공격력(세개 뜨면 데미지 두배)
	//방어력 무시 공격(방어력이 엄청 강한 몬스터를 데미지를 줘서 한방에 죽임)
	//회피(한턴동안 데미지를 받지 않는다.)
	//독면역(3턴동안 독공격에 걸리지 않는다.)
	//스턴면역(3턴동안 스턴에 걸리지 않는다.)

	//로빈스킬-에어크래쉬 : 공중적에게 데미지 2배
	//로빈스킬-마구찌르기
	//로빈스킬-부스트슬래시 : 기절(100% 기절)
	//로빈스킬-하이퍼차지 : 돌격공격(적을 뒤로 날린다가 무슨 의미가 있지?
	//로빈스킬-소울크래시 : 이것도 기절이야?
	//로빈스킬-앱솔루트피어스 : 찔러서 회전
	//로빈스킬-멸살연참 : 최강데미지
	//로빈스킬-방어태세 : HP를 순간적으로 부풀려서 큰 데미지를 받는다. 

	CREWTYPE_NORMAL = 0,
	CREWTYPE_ATTACKSKILL,
	CREWTYPE_BUFFSKILL,
	CREWTYPE_SUMMON,
	CREWTYPE_HEART,

	TOTAL_CREWTYPE,

	MAXHOTKEY = 3,//
	QUICKSLOTGAP = 80 * _2X,

	RINGKEY = MAXHOTKEY,

	//방 디파인
	NORMALROOM = 0,
	ENEMYROOM,

	//맵관련

	MAXMAPSIZE_X = 100 * TSIZE,
	MAXMAPSIZE_Y = 42 * TSIZE,

	MAXTILECOUNT = 88,

	//배경Rect숫자
	MAXRECT = 8,
	//원경오브젝트
	MAXBACKOBJ = 65,
	//근경
	MAXFOREOBJ = 51,
	//중립 오브젝트
	MAXNEUTRALOBJ = 18,
	//움직이는 배경 오브젝트
	MAXBGOBJECT = 32,

	//타일 충돌 관련
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

	//토탈 스테이지

	STAGELIST_Y = DIORAMASIZE_Y * 2 / 3,
	//스테이지 마다 방개수는 5개
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

	ARENAITEMFRAME = FPS * 10,//투기장에서 보스몹잡았을때 아이템이 드랍되는 최대 프레임
	ARENALIMITTIME = 60 * 60 * 24 * 3,//보스전은 10초안에 클리어 되야 된다.
	ARENABUFFTIME = FPS * 100,

	MINUTES = FPS * 60,

	ARENAANIMATIONFRAME = 8,

	CREWDATA_TYPE = 0,
	CREWDATA_DETAILTYPE,
	CREWDATA_SKILL1,
	CREWDATA_SKILL2,
	CREWDATA_SKILL3,
	CREWDATA_CASTLEIDX,
	CREWDATASIZE,
	//TYPE, STAR, PRICE, BULLETDATA
	CMFFRAMEPOSITIONDATASIZE = 6,

	CREW_MENU = 0,//메뉴를 올려주는 서포터
	CREW_GOODS,//재화를 생산하는 서포터
	CREW_ABILITY,//어빌리티를 올려주는 서포터
	CREW_EQUIP,//장비를 생산하는 서포터

	//MP를 붙이자
	//MP를 사용해서 스킬을 사용. 

	//재화
	//다이아몬드(캐시) -> 소환,  
	//에메랄드 -> 스킬슬롯, 장비개수 등
	//골드()->레벨업
	//강화석()->강화
	//스킬카드()
	//황금열쇠(구매를 하면 쌓이는 특별)
	//
	//적을 공격하면 기본적으로 골드와 경험치만 나온다.

	MENU_PLAY = 0,//캐릭터메뉴 : 캐릭터를 레벨업하고 스탯(STAT_STR, STAT_VIT, STAT_AGI, STAT_INT)을 찍는 부분
	MENU_HERO,
	MENU_CREW,
	MENU_COLLECTIONS,//장비, 소환수, 기타
	MENU_CASTLE,//성메뉴
	MENU_SHOP,//상점메뉴 : 소환(무기, 방어구, 악세사리, 스킬카드,  ), 패키지(), 재화(), 황금열쇠()  
	MENU_STARSHOP,
	MENU_FRIENDS,
	MENU_NEWS,
	MENU_GIFTS,
	MENU_LEADERBOARD,//가장 스테이지를 많이 진행한 유저 
	MENU_INVITEFREINDS,
	MENU_CALENDAR,
	MENU_SETTING,
	MENU_JOKBO,

	MENU_LIST,
	MENU_GAMEEVENT,
	MENU_BOSSRAID,
	MENU_STAGEINFO,

	MENU_BATTLE,//여기서는 일반 몹과 싸우는것으로
	MENU_RAID,

	MENU_GAMERESET,//게임초기화

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
	CURRENCY_MEDAL,//전투에서 승리하면 받는 포인트는 메달 
	CURRENCY_COIN,//뽑기에 주로 사용되고, 
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


	LOG_EVENT_QUESTSTART = 0,//이벤트 오픈
	//퀘스트 아이콘 + 퀘스트 이름 + 퀘스트가 활성화되었습니다
	LOG_EVENT_BATTLESTART,
	//배틀 아이콘 + 배틀이 활성화 되었습니다!
	LOG_EVENT_RAIDSTART,
	//레이드 아이콘 + 레이드가 활성화 되었습니다!
	LOG_RAID,//적 보스의 침공
	//적 보스 cmf + 털어가는 골드 + 털어갔습니다.
	LOG_BATTLE,//적 보스의 동료 무력화
	//적 보스 cmf + 침공해서 + 무력화된 내 동료 아이콘이 무력화 되었습니다.
	LOG_BOSSGETCOIN,//보스 힐
	//적 보스 cmf + 적 동료를 통해서 + 골드아이콘 + 금액 + 회복했습니다.
	LOG_SKILL,//스킬
	LOG_BETHEART,//하트 증가
	LOG_BETCOIN,

	TOTAL_LOG,


	TOTALBUFFSHOP = 3,
	BUFFSHOPDATASIZE = 5,

	TOTALMEDALSHOP = 3,
	MEDALSHOPDATASIZE = 5,

	//시간은
	OXYGEN = 200,

	TOTALOPTION = 12,

	END_GAMEDEF
} GAMEDEF;


#define CURRENCYICON_STARTSIZE 1.0f
#define CURRENCYICON_ENDSIZE 1.5f
#define CURRENCYICON_ENDSIZE2 2.0f
/*
//달성도 관련 디파인
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

	//카테고리별 갯수
	REPORT_ARENA_COUNT = 9,
	REPORT_VILLAGE_COUNT = 9,
	REPORT_AREA_COUNT = 8,
	REPORT_ITEM_COUNT = 8,
	REPORT_MONSTER_COUNT = 28,
	REPORT_COMBAT_COUNT = 10,
	REPORT_STAT_COUNT = 15,
	REPORT_ETC_COUNT = 10,

	//카테고리별 시작 인덱스
	REPORT_ARENA_START = 0,
	REPORT_VILLAGE_START = REPORT_ARENA_START + REPORT_ARENA_COUNT,
	REPORT_AREA_START = REPORT_VILLAGE_START + REPORT_VILLAGE_COUNT,
	REPORT_ITEM_START = REPORT_AREA_START + REPORT_AREA_COUNT,
	REPORT_MONSTER_START = REPORT_ITEM_START + REPORT_ITEM_COUNT,
	REPORT_COMBAT_START = REPORT_MONSTER_START + REPORT_MONSTER_COUNT,
	REPORT_STAT_START = REPORT_COMBAT_START + REPORT_COMBAT_COUNT,
	REPORT_ETC_START = REPORT_STAT_START + REPORT_STAT_COUNT,

	//투기장 및 길드
	REPORT_ARENA0 = 0,	//강자의 길(투기장 입장 횟수)
	REPORT_ARENA1,	//지옥의 길(헬투기장 입장 횟수)
	REPORT_ARENA2,	//강자의 명성(투기장 100층 도달)
	REPORT_ARENA3,	//지옥의 명성(헬투기장 100층 도달)
	REPORT_ARENA4,	//적극적인 참여(길드전 참여 횟수)
	REPORT_ARENA5,	//투기장의 지배자(투기장에서 죽인 적 숫자)
	REPORT_ARENA6,	//지옥의 지배자(헬투기장에서 죽인 적 숫자)
	REPORT_ARENA7,	//매일 매일 꾸준히(데일리 퀘스트 수행 횟수)
	REPORT_ARENA8,	//거인 퇴치(투기장에서 NPC 퇴치 횟수)

	//마을
	REPORT_VILLAGE0,		//잠꾸러기(여관을 이용한 횟수)
	REPORT_VILLAGE1,		//단골손님(상인들 중 1명에게서 아이템 구입한 수)
	REPORT_VILLAGE2,		//강한 장비를 위하여(강화 횟수)
	REPORT_VILLAGE3,		//불굴의 강화(강화 실패 횟수)
	REPORT_VILLAGE4,		//블랙스미스(장비 제작 횟수)
	REPORT_VILLAGE5,		//럭셔리마스터(보석 장착 횟수)
	REPORT_VILLAGE6,		//알뜰한 모험자(상점에다가 아이템을 판매한 횟수)
	REPORT_VILLAGE7,		//공간을 달리는 자(귀환서 사용한 횟수)
	REPORT_VILLAGE8,		//이웃사촌(사람들에게 말을 건 횟수)

	//지역
	REPORT_AREA0,	//위험을 추구하는 자(모든 강적 지역 방 들어가면)
	REPORT_AREA1,	//세상을 탐험하는 자(미니맵 100%)
	REPORT_AREA2,	//파괴의 달인(찍기 블록 모두 파괴시)
	REPORT_AREA3,	//태양을 파괴하는 자(SUN 블록 모두 파괴시)
	REPORT_AREA4,	//순간 이동의 달인(모든 워프블록 이용시)
	REPORT_AREA5,	//어디에 있을까?(필드에 숨겨진 아이템 모두 찾으면)
	REPORT_AREA6,	//트레져 헌터(타 캐릭터용 상자를 제외한 모든 보물상자 획득)
	REPORT_AREA7,	//여행자의 안내서(모든 표지판을 읽으면)

	//아이템
	REPORT_ITEM0,		//목걸이 수집가(등급에 관계없이 모든 목걸이가 인벤토리에 있을 때)
	REPORT_ITEM1,		//반지의 제왕(등급 관계없이 모든 반지를 인벤토리에 가지고 있으면)
	REPORT_ITEM2,		//무기 수집가(모든 무기(등급 상관 없음)를 인벤토리에 가지고 있으면)
	REPORT_ITEM3,		//갑옷 수집가(모든 갑옷(등급 상관 없음) 인벤토리에 가지고 있으면)
	REPORT_ITEM4,		//바지 수집가(모든 바지(등급 상관 없음) 인벤토리에 가지고 있으면)
	REPORT_ITEM5,		//모자 수집가(모든 모자(등급 상관 없음) 인벤토리에 가지고 있으면)
	REPORT_ITEM6,		//장갑 수집가(모든 장갑(등급 상관 없음) 인벤토리에 가지고 있으면)
	REPORT_ITEM7,		//신발 수집가(모든 신발(등급 상관 없음) 인벤토리에 가지고 있으면)

	//몬스터
	REPORT_MONSTER0,	//습지의 사냥꾼(톨레아 습지에서 퇴치한 몬스터 마릿수)
	REPORT_MONSTER1,	//계곡의 사냥꾼(금단의 계곡에서 퇴치한 몬스터 마릿수)
	REPORT_MONSTER2,	//바다의 사냥꾼(아틀란티스에서 퇴치한 몬스터 마릿수)
	REPORT_MONSTER3,	//지하의 사냥꾼(지하도에서 퇴치한 몬스터 마릿수)
	REPORT_MONSTER4,	//평원의 사냥꾼(아델 평원에서 퇴치한 몬스터 마릿수)
	REPORT_MONSTER5,	//불꽃의 사냥꾼(홍염의 대지에서 퇴치한 몬스터 마릿수)
	REPORT_MONSTER6,	//얼음의 사냥꾼(유구한 빙원에서 퇴치한 몬스터 마릿수)
	REPORT_MONSTER7,	//번개의 사냥꾼(전뇌의 공방에서 퇴치한 몬스터 마릿수)
	REPORT_MONSTER8,	//황혼의 사냥꾼(황혼의 성역에서 퇴치한 몬스터 마릿수)
	REPORT_MONSTER9,	//협곡의 사냥꾼(골렘의 협곡에서 퇴치한 몬스터 마릿수)
	REPORT_MONSTER10,	//심연의 사냥꾼(칠흑의 심연에서 퇴치한 몬스터 마릿수)
	REPORT_MONSTER11,	//명계의 사냥꾼(망자의 도시에서 퇴치한 몬스터 마릿수)
	REPORT_MONSTER12,	//드래곤 슬레이어(드래곤의 무덤에서 퇴치한 몬스터 마릿수)
	REPORT_MONSTER13,	//캐슬 크래셔(마왕성에서 퇴치한 몬스터 마릿수)
	REPORT_MONSTER14,	//스페이스 마린(우주에서 퇴치한 몬스터 마릿수)
	REPORT_MONSTER15,	//습지의 전장(토드 뮤턴트를 퇴치한 횟수)
	REPORT_MONSTER16,	//계곡의 전장(아르곤을 퇴치한 횟수)
	REPORT_MONSTER17,	//해저 전장(카툼을 퇴치한 횟수)
	REPORT_MONSTER18,	//고대 전장(고대의 수호자를 퇴치한 횟수)
	REPORT_MONSTER19,	//불꽃 전장(이프리트를 퇴치한 횟수)
	REPORT_MONSTER20,	//얼음 전장(프로스트를 퇴치한 횟수)
	REPORT_MONSTER21,	//번개 전장(라이오너를 퇴치한 횟수)
	REPORT_MONSTER22,	//빛의 전장(호루스를 퇴치한 횟수)
	REPORT_MONSTER23,	//지하도의 전장(마도합성수를 퇴치한 횟수)
	REPORT_MONSTER24,	//협곡의 전장(고대의 방주를 퇴치한 횟수)
	REPORT_MONSTER25,	//어둠의 전장(아리만을 퇴치한 횟수)
	REPORT_MONSTER26,	//암흑룡의 전장(티어맷을 퇴치한 횟수)
	REPORT_MONSTER27,	//명계의 전장(죽음의 신을 퇴치한 횟수)

	//전투
	REPORT_COMBAT0,		//이길수 있는 싸움(캐릭터보다 레벨이 10이상 낮은 몬스터를 죽인 횟수)
	REPORT_COMBAT1,		//끊임없는 공격(적에게 입힌 데미지의 누적총합)
	REPORT_COMBAT2,		//맷집의 한계(적에게 받은 피해의 누적총합)
	REPORT_COMBAT3,		//이 땅을 지켜라(방을 옮기지 않고 잡은 몬스터 마릿수)
	REPORT_COMBAT4,		//진정한 영웅(HP가 1인 상태에서 연속으로 몬스터 잡은 횟수)
	REPORT_COMBAT5,		//버프마스터(버프 사용 횟수)
	REPORT_COMBAT6,		//종합병원(상태이상 걸린 횟수)
	REPORT_COMBAT7,		//화려한 기술(버프 이외의스킬 사용 횟수)
	REPORT_COMBAT8,		//좀비(부활약을 먹은 횟수)
	REPORT_COMBAT9,		//성인(적을 공격하지 않고 연속으로 죽은 횟수)

	//능력치
	REPORT_STAT0,		//의미없는 레벨업(사용하지 않은 AP의 합)
	REPORT_STAT1,		//스킬없이 싸운다(사용하지 않은 SP의 합)
	REPORT_STAT2,		//최강의 공격력(공격력 총합)
	REPORT_STAT3,		//최강의 방어력(방어력 총합)
	REPORT_STAT4,		//정확한 공격(명중률 %)
	REPORT_STAT5,		//재빠른 회피(회피 %)
	REPORT_STAT6,		//필살의 일격(크리티컬 확률 %)
	REPORT_STAT7,		//연속되는 공격(추가타 확률)
	REPORT_STAT8,		//꿰뚫는 공격(관통공격 확률)
	REPORT_STAT9,		//충격적인 공격(기절 %)
	REPORT_STAT10,	//막을 수 없는 공격(방어도 무시 공격 확률)
	REPORT_STAT11,	//럭키가이(행운 증가 %)
	REPORT_STAT12,	//금전운(골드 획득 %)
	REPORT_STAT13,	//경험의 부적(경험치 획득 %)
	REPORT_STAT14,	//상인의 주머니(지금까지 얻은 돈 총합)

	//기타
	REPORT_ETC0,	//위대한 업적(모든 서브 퀘스트))
	REPORT_ETC1,	//네버엔딩 스토리(플레이 타임)
	REPORT_ETC2,	//잠수부(수중에 한 번 들어가서 있는 시간)
	REPORT_ETC3,	//멀미유발(어둠의 파편을 탄 시간(누적))
	REPORT_ETC4,	//글라이더처럼(활강 합계시간)
	REPORT_ETC5,	//저축 습관(인벤토리에 있는 돈)
	REPORT_ETC6,	//방구석 페인(한 방에서 아무것도 하지 않고 있는 시간)
	REPORT_ETC7,	//지평선 너머(옆으로 이동한 거리 (수평으로 타일수 측정))
	REPORT_ETC8,	//하늘 끝까지(위로 올라간 거리 (수직으로 타일수 측정))
	REPORT_ETC9,	//블랙 & 화이트(블랙홀 통과 횟수(누적))

	//호칭
	PLAYER_TITLE0,		//길드의 일등공신(길드전에서 1등)
	PLAYER_TITLE1,		//신중한 모험자(악세서리를 포함한 모든 장비를 갖춰입었을때)
	PLAYER_TITLE2,		//음속의 암살자(60초 안에 적 15마리를 퇴치한다.)
	PLAYER_TITLE3,		//스트라이커(정령석을 던져서 한 번에 3마리를 해치운다.)
	PLAYER_TITLE4,		//돌격대장(대쉬어택으로 몬스터를 777마리 격파)
	PLAYER_TITLE5,		//투기장마스터(투기장을 1회 끝까지 돌파한다.)
	PLAYER_TITLE6,		//보석애호가(소켓이 3개이상인 장비에 모두 보석을 박으면)
	PLAYER_TITLE7,		//주제를 모르는 자(적의 공격 한 방에 내 피가 반 이상 깍인 횟수)
	PLAYER_TITLE8,		//돌아이(천정에 머리를 부딪힌 횟수가 500회(점프높이가 천정에 머리가 닿는 이상 올라갈수있을때 로 판정))
	PLAYER_TITLE9,		//벌거벗은 사냥꾼(무기만 장비하고 몬스터를 해치운 마릿수가 100마리)
	PLAYER_TITLE10,	//대인배(아이템이 방안에 5개이상 나와있는데 먹지않고 다음방으로 넘어간다.)
	PLAYER_TITLE11,	//인생을 역전한 자(인벤에 있는 돈이 7777)
	PLAYER_TITLE12,	//진정한 갑부(유료 아이템 구입 개수가 20개)
	PLAYER_TITLE13,	//스카이다이버(드래곤의 상 먹으러 뛰어내릴때 걸림없이 바닥까지 간다.)
	PLAYER_TITLE14,	//평화의 사자 간디(적을 죽이지 않고 연속으로 20개의 방을 이동(마을내부에선 무효. 마을에 들어가면 카운트리셋))
	PLAYER_TITLE15,	//약물중독자(사용한 포션횟수(씨앗,허브)가 누적 100개에 도달)
	PLAYER_TITLE16,	//롤링마스터(어둠의 파편 사이를 떨어지지 않고 왔다갔다 한 횟수 누적 100번)
	PLAYER_TITLE17,	//건망증 황제(완료하지 않은 퀘스트가 10개 이상누적)
	PLAYER_TITLE18,	//기본기의 달인(스킬 사용하지 않고 네임드몬스터를 퇴치한 횟수(기본 공격, 찍기, 대쉬 공격))
	PLAYER_TITLE19,	//4번 타자(내 공격 한 방에 적의 체력이 반 이상 깍인 횟수 누적 500번)
	PLAYER_TITLE20,	//구제불능 방향치((톨렘, 벨로네에서)집에 들어가서 아무에게도 말을 걸지않고 다시 나간 횟수누적 100회)
	PLAYER_TITLE21,	//독서광(아델라인 도서관에 방문한 횟수)
	PLAYER_TITLE22,	//회피의 달인(HP가 최대HP의 10% 이하일때 귀환서를 사용한 횟수 누적)
	PLAYER_TITLE23,	//탱커(최대 HP가 1000돌파)
	PLAYER_TITLE24,	//코스튬플레이어(무기제외하고 다른 주인공의 장비를 통일해서 입는다.)
	PLAYER_TITLE25,	//전설의 대장장이(강화를 10단계까지 성공한다.)
	PLAYER_TITLE26,	//근성넘치는 강자(투기장에서 회복하지않고 죽인 적 수가 50마리 이상)
	PLAYER_TITLE27,	//신성한 사제(물약으로 디버프 회복한 횟수)
	PLAYER_TITLE28,	//도전과제의 수행자(모든 달성도 완료)
	PLAYER_TITLE29,	//우주적 유명인사(이것을 제외한 모든 호칭 입수)

	TOTAL_REPORT,

	TOTAL_PLAYERTITLE = 30,

	END_REPORTDEF
} REPORTDEF;
*/

typedef enum _prgDef {
	//Data.h 배열별 기준 크기
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

	//각종프레임
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

	
	MAXCMF = TOTALCMF,//@@ 나중에 계산해보고 줄여줄것
	REALMAXCMF = TOTALCMF,	//퀘스트 클라이언트용 CMF
	CLIENTCMF = REALMAXCMF,

	

	AIRETRYCOUNT = 100,

	
	HERO_PARAM_DMG = 0,//데미지
	HERO_PARAM_SDMG,//스킬데미지
	HERO_PARAM_ASPD,//공격속도
	HERO_PARAM_MSPD,//이동속도
	HERO_PARAM_HP,//체력
	HERO_PARAM_DEF,//방어력

	TOTAL_HERO_PARAM,

	DIANAACTIVELEVEL = 5,
	MAXXACTIVELEVEL = 10,
	//움직임 상태
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

	ADTYPE_SOLDIER = 0,//용병광고(터치하면 용병메뉴로 가지만 아직 용병메뉴가 오픈되지 않았으면 갈수 없다는 메시지만 띄워준다.)
	ADTYPE_GOODS,//현금 다이렉트 구매상품(터치하면 구매팝업으로)
	ADTYPE_ITEMS,//다른 유저가 6성이상 무기를 얻거나 전설등급무기를 얻었을 때


	
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

	//50은 기본
	LVUPREWARD_HEARTMAX,

	//하트 생성량
	LVUPREWARD_HEARTPERHOUR,

	//방패 최대량
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

	DAILYQUEST_OPEN_BOX_GETEQUIP = 0,//상자를 열어 장비를 3번 얻으면
	DAILYQUEST_UPGRADE_CREW,//3개를 업그레이드하면 되는것
	DAILYQUEST_ATTACK_OTHERUSER,//Battle, Raid 포함
	DAILYQUEST_COLLECT_GOLD,//일정금액의 돈을 모으면
	DAILYQUEST_STAGE_TRY,//스테이지 전투 

	TOTAL_DAILYQUEST_TYPE,

	BOXOPENITEMFRAMEINFOSIZE = 6,


} DAILYQUEST;

enum JumpState {
	JS_IDLE = 0,     // 정지(서있음)
	JS_SPINNING,     // 점프 중 + 공중에서 계속 교체
	JS_LANDING,      // 착지 구간(공중에서 교체하다가 착지 순간 target 확정)
	JS_HOLD,     // 착지 후 연출 대기(슬로우)
	JS_DONE          // 확정 후 고정
};

#define ITEMTYPESEED 1000
#define ITEMDETAILSEED 10000
#define MAX_POINTS 500 * MOTIONDIV // 최대 좌표 개수
#define MAX_RADIUS 256 // 최대 반경
#define MAX_BOXRADIUS	128

#define BOSSROOMTIME	60 * 10//10분	

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
