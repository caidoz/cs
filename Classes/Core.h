#pragma once

#ifndef _CORE_H_
#define _CORE_H_

// ??===== 1?¨ê³„: Windows ?¤ë” (ê°€??ë¨¼ì?) =====
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
// WinSock2ë¥??¬ìš©?˜ëŠ” ì½”ë“œê°€ ?ˆìœ¼ë¯€ë¡??¬ë°”ë¥??œì„œë¡??¬í•¨
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
#endif

// ===== 3?¨ê³„: cocos2d (ê¸°ë³¸ ?¼ì´ë¸ŒëŸ¬ë¦? =====
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Def.h"
#include "ui/UIWebView.h"
#include <vector>

using namespace cocos2d;
using namespace cocos2d::experimental;


//Json


#ifdef SDKBOX_ENABLED

#endif


#ifdef SDKBOX_ENABLED
//#include "PluginAdMob/PluginAdMob.h"
#endif
//#import <AVFoundation/AVFoundation.h>
//#include "OpenGLES/ES2/gl.h"
//#include "OpenGLES/ES2/glext.h"

#define USE_AUDIO_ENGINE 1
//#define USE_SIMPLE_AUDIO_ENGINE 1

#ifdef USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
#else //USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif


#define GL_BLEND_BLENDMODE { GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA }
#define GL_BLEND_MULTIFLYMODE { GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA }
#define GL_BLEND_SCREENMODE { GL_ONE_MINUS_DST_COLOR, GL_ONE }
#define GL_BLEND_LINEARDODGEMODE { GL_ONE, GL_ONE }
#define GL_BLEND_DARKEN { GL_ONE, GL_ONE }

//Shader ê´€??

// Shader ë¬¸ì??- extern ? ì–¸
extern const char* vsh_gray;
extern const char* fsh_gray;
extern const char* vsh_white;
extern const char* fsh_white;
extern const char* vsh_lighten;
extern const char* fsh_lighten;

extern GLProgram* shader_gray;
extern GLProgram* shader_white;
extern GLProgram* shader_lighten;
extern GLProgram* shader_outline;
extern GLProgramState* shader_state_outline;
extern GLProgramState* shader_state_default;

extern BlendFunc BLEND_ORIGIN;
extern BlendFunc BLEND_BLENDMODE;
extern BlendFunc BLEND_LIGHTEN;
extern BlendFunc BLEND_SHADOW;

#pragma pack (1)
typedef struct _button {
	int visualState;
	int buttonEventListener;//
	int x, y, w, h;//ë²„íŠ¼???„ì¹˜ ?¬ê¸° ?•ë³´
	float zoomX;//ë²„íŠ¼??

} BUTTON;

typedef struct _popUp {
	bool active;
	int type;
	int x, y, w, h;

	int itemType;//?ì—…???±ì¥?˜ëŠ” ?€??
	int itemDetail;
	int itemGrade;

	int rewardType[BOX1MAXREWARDITEM];
	int rewardDetail[BOX1MAXREWARDITEM];
	int rewardGrade[BOX1MAXREWARDITEM];
	long long rewardStartCnt[BOX1MAXREWARDITEM];
	long long rewardEndCnt[BOX1MAXREWARDITEM];

	int frame;
	int popUpFrame;
	float zoom;
} POPUP;

typedef struct _currencyEffect {
	int frame;
	int totalFrame;
	int startValue;
	int endValue;
	int iconFrame;
} CURRENCYEFFECT;

typedef struct _hotKey {
	signed short frame;    //?«í‚¤ë¡??¥ì°©???¤í‚¬???¸ìˆ˜ ?ˆì„??
	signed short inven;
	signed short idx;    //?¤í‚¬??ê²½ìš°???¤í‚¬?¸ë±?? ?„ì´?œì¼ ê²½ìš°?ëŠ” ì£¼ì¸ê³??¸ë²¤? ë¦¬?´ì˜ ?¸ë±?? ?ì´ë©??ì¢…ë¥? ë°˜ì?ë©?ë°˜ì???ì¢…ë¥˜
	signed short type;    //0?´ë©´ ? ë‹¹?œê²Œ ?†ìŒ, 1?´ë©´ ?¤í‚¬, 2?´ë©´ ?„ì´?? 3?´ë©´ ?? 4ë©?ë°˜ì?
	bool random;//true ë©??Œë¦¬ê³??ˆëŠ”ê±°ê³  false ë©??•ì •
	signed short randomFrame;//?œë¤??ê°’ì´ ê²°ì •???Œê¹Œì§€ 
	signed char randomCnt;//?Œë¦¬??ì¹´ìš´??
} HOTKEY;

typedef struct _item {
	long long id;
	int value;    //?€?œê°’(ë¬´ê¸°-ê³µê²©?? ë°©ì–´êµ?ë°©ì–´???±ë“±
	int subValueType;//?ë²ˆì§??€?œê°’??ì¢…ë¥˜(ëª©ê±¸?? ë°˜ì???ì§€?•ë˜??ê°?
	int subValue;    //?ë²ˆì§??€?œê°’(ëª©ê±¸?? ë°˜ì???ì§€?•ë˜??ê°?
	unsigned short icon;        //?„ì´ì½?
	unsigned int count;    //ê°?ˆ˜(?¥ë¹„??ê²½ìš°???Œì¼“???«ì)
	unsigned int gold;    //ê°€ê²?
	unsigned short cooldown;    //?¬ìš©?¨ê³¼ê°€ ?ˆëŠ” ?„ì´?œì˜ ì¿¨ë‹¤???¥ë¹„??ê²½ìš° ê°•í™”?ˆë²¨)
	unsigned char lv;    //?ˆë²¨
	unsigned char type;        //?€??
	unsigned char detail;    //?¸ë?
	unsigned char grade;    //?±ê¸‰
	bool broken;    //?Œê´´?˜ì—ˆ?”ì?
	long set;    //?´ë–¤ ?¸íŠ¸?¸ì? //?¤í‚¬??ë°œë™?˜ë©´ ??set???°ë„ë¡??˜ì
	int socket[6];    //?Œì¼“
	int option[12][2];
	char name[40];
	int exp;//?„ì¬ ?„ì ??ê²½í—˜ì¹?
	bool seen;//?ì„¸?•ë³´ë¥??•ì¸?ˆëŠ”ì§€

	template <class Archive>
	void serialize(Archive & ar)
	{
		ar(
			id,
			value,
			subValueType,
			subValue,
			icon,
			count,
			gold,
			cooldown,
			lv,
			type,
			detail,
			grade,
			broken,
			set,
			socket[6],
			option[12][2],
			name[40],
			exp,
			seen
		);
	}
} ITEM;

//Structure
typedef struct _obj {
	signed char active;
	int jumpFrame, attackFrame, mainFrame, frame, attackedFrame, levelUpFrame, delayFrame, statUpFrame;
	int turn;//ìºë¦­?°ê? ëª‡ë²ˆì§?ê³µê²©???˜ê³  ?ˆëŠ”ì§€ ë³´ì—¬ì£¼ëŠ” ë³€??
	int x, y;
	int nx, ny;//ê²Œì„?œì‘???„ì¹˜, ê³µê²©???¤ì— ?¤ì‹œ ?Œì•„ê°€???„ì¹˜
	int type;
	int etc;
	int apx;
	long long int ps[TOTALPLAYERSTAT];
	unsigned char setIndex[TOTALEQUIP];
	unsigned char setCount[TOTALEQUIP];
	signed char skillLv[TOTAL_SKILL];
	signed short buff[TOTALBUFF];
	unsigned char buffOwner[TOTALBUFF];
	signed int debuf[TOTALDEBUF];
	unsigned char debufOwner[TOTALDEBUF];
	signed short cpx, cpy, cx, cy;
	signed short apy, ax, ay;
	long long int hp, maxhp;
	int mp, maxmp;
	unsigned short ap;
	unsigned char sp;
	int shield, shieldMax;
	unsigned short icon;
	unsigned short iconFrame;
	long long int str, def;
	signed short name;	//?´ë¦„
	int lv;
	unsigned short motion;
	unsigned char tileX1, tileX2, tileY1, tileY2;
	unsigned char moveHandler;
	unsigned char drawHandler;
	//signed char ipx, ipy, ix, iy;
	signed short dx, dy;
	signed char dead;
	signed short attack;
	signed char attacked;
	signed char block;
	signed short cmf;
	signed char status;
	signed char mx, my;
	signed char dirF, dirX, dirY;
	unsigned short attr;
	float zoom, defaultZoom;
	unsigned short mom;
	unsigned short target;
	
	int pressedKey[3];
	int released;
	HOTKEY hotKey[MAXHOTKEY];//?¸ê²Œ?„ì—???ë“?˜ëŠ”
	ITEM equip[TOTALEQUIP];//?„ì¬ ?¥ì°©???¥ë¹„??3ê°?ìºë¦­??ë¡œë¹ˆ, ?”ì•„?? ë§¥ìŠ¤ë³„ë¡œ ?ˆë‹¤.
	unsigned char equipImg[TOTALEQUIP];
	unsigned char equipped[TOTALEQUIP];
	signed char immune[TOTALDEBUF];
	long long int stat[4];
	unsigned char continueAttack;
	unsigned char decreaseHp, minusDrain, alwaysCurse;
	unsigned char invincible;
	unsigned char hpRestore, mpRestore, statusRestore;
	unsigned char hpDrain, mpDrain;
	
	//?ê³¼ ê´€?¨ëœ ë³€??
	unsigned char canRun;
	unsigned char canDown;
	unsigned char canPush;
	unsigned char canSwim;
	unsigned char canMagma;
	unsigned char canSled;
	unsigned char canOnWater;
	unsigned char canMagnet;
	unsigned char canBreak;
	unsigned char canJumpTwice;
	unsigned char canOnThorn;
	unsigned char canGlide;
	unsigned char canSuperJump;
	unsigned char canSpace;
	unsigned char canBreath;
	
	unsigned char concentrate;
	signed char isWind;
	signed short pDx, pDy;
	signed char oldDy;
	signed char onTile, inTile;
	unsigned char playerRun;
	unsigned char attackLv;
	int currentSkill;
	signed char currentBullet;
	unsigned char inertia;
	unsigned char nHeight;
	unsigned char jumpTwice;
	unsigned char jumpRelease;
	signed char superJump;
	unsigned char onSled;
	unsigned char onCarpet;
	unsigned char onWater;
	unsigned char magnet;
	unsigned char jumpLock;
	signed short flamer;
	
	unsigned char head;
	unsigned char O2;

	long long int totalDmg;
	unsigned char skillIdx;
	
	int deadFrame;
	int deadCount;
	long long gold;

	int getSkillList[MAXCHARSKILL];
	int exps, remainedExps;
	int rank;
	int ai;
	int tier;
	int subTier;

	bool soldier;

	int stress;
	int curStar;
	int maxStar;
	int curHeart;
	int maxHeart;
	int playCnt;
	
	long long int totalDmgRecord;
	long long int onceDmgRecord;
	long long int curDmg;

	int ringValue[TOTAL_RING];
	long long int id;

	int castle;

	std::string nickname;

	long coolTime;//???¤í‚¬ ë°œë™?œê°„

	float rotation;//?Œì „ê°?

	int hitCount;
	int hitCountFrame;
	long long hitDmg;

	bool hitCountPlus;

	int turnPosition;

} OBJECT;

typedef struct _gameEvent {
	unsigned char type;//EVENTTYPE_QUEST, EVENTTYPE_PVP, EVENTTYPE_SHOP
	unsigned char subType;//
	short icon;//?„ì´ì½??¸ë±??
	long timeStamp;//?œì‘???œê°„
	long limitTime;//ëª‡ì‹œê°„ì§œë¦??´ë²¤?¸ì¸ì§€

	int barFrame;
	//EVENT_OPEN
	//EVENT_DOING
	//EVENT_CLOSE
	unsigned char status;//?ì„±, ì§„í–‰ì¤? ?Œë©¸ ?¸ê?ì§€ ?¤í…Œ?´í„°??
	//PVP ?„ì´???ë“???Œì²˜??ë°”ê? ?€?´ë‚˜?€??ê±°ê¸°ë¡??°ì´?°ê? ? ë¼ê°€??ê²½ìš°
	//EVENT_BAR_NEW
	//EVENT_BAR_ITEMGET
	//EVENT_BAR_REWARDGET
	//EVENT_BAR_NEXT
	//EVENT_BAR_CLOSE
	unsigned char barStatus;//?ì„±, ?ë“ì¤? ë³´ìƒ, ?¥ìŠ¤?¸ë°”, ì¢…ë£Œ 4ê°€ì§€ ?¤í…Œ?´í„°??
	
	int x;//?¼ìª½ ?¤ë¥¸ìª??¸ë±??
	int y;//?„ì—??ë¶€??ëª‡ë²ˆì§??¸ë±??
	int dirX;
	int dirY;
	int nx;
	int ny;
	int targetX, targetY;//ëª©ì ì§€ XY 
	int targetX2, targetY2;//ëª©ì ì§€ XY 
	float dx, dy;//x, yì¶??´ë™ê±°ë¦¬
	float speed;//?´ë™?ë„
	float speedIncrement;//?´ë™?ë„ ì¦ê???
	float speed2;//?´ë™?ë„2
	float speedIncrement2;//?´ë™?ë„ ì¦ê???
	int waitingFrame;//?œì‘?ˆì„ ??ë¨¸ë¬´ë¥´ëŠ” ?„ë ˆ??
	int waitingFrame2;//ì¤‘ê°„???´ë™?ë„ ì²´ì¸ì§€ ?ˆì„ ??ë¨¸ë¬´???„ë ˆ??
	int frame;//?„ì¬ ?„ë ˆ??
	int frame2;//
	float zoom;
	float zoomEnd;//ì¤?
	float zoomIncrement;
	float zoom2;
	float zoomEnd2;//ì¤?
	float zoomIncrement2;

	int touchFunc;

	float value;

	bool front;
} GAMEEVENT;

typedef struct _bar {
	bool active;
	unsigned char type;//BAR_GOLD, BAR_STAR, BAR_HEART, BAR_QUEST, BAR_ENEMYHP

	signed long long count;//?«ì(robin.gold, robin.heart...)
	signed long long add;//?”í•´???˜ëŠ” ê°??ë“ê°?
	signed long long max;//?”í•´???˜ëŠ” ê°’ì„ ?©ì‚°???œí„´ ?©ì‚°ê°?                                                  
	
	bool addView;
	signed long long addViewSum;//?„ë ˆ?„ì´ ?ë‚˜ì§€ ?Šìœ¼ë©?

	int countFrame;//ì¹´ìš´???”í•´ì§€???™ì•ˆ ?¬ë¼ê°€???„ë ˆ??

	short icon;//?„ì´ì½??¸ë±??
	int iconFrame;//???„ë ˆ?„ì— 0ë³´ë‹¤ ?¬ë©´ ?„ì´ì½˜ì´ ?€ì§ì¸??

	//ë³´ìƒ ?„ì´ì½˜ì´ ?œì‹œ?¬ë?
	//false ë©??ˆë³´?¬ì£¼?”ê±°ê³?
	//ê°’ì´ ?ˆìœ¼ë©?1?´ë©´ ê·¸ëƒ¥ ë³´ì—¬ì£¼ëŠ” ê±´ë°
	//ê°’ì´ 1ë³´ë‹¤ ?¬ë©´ ë³´ìƒ ?„ì´?œì´ ?•ë?->ì¶•ì†Œë¡??€ì§ì´ë©´ì„œ ë³´ìƒ???‹íŒ…?˜ëŠ” ê²ƒì„ ë³´ì—¬ì¤€??
	float enemyIcon;
	float rewardIcon;
	bool bonusRewardIcon;//ë³´ë„ˆ???„ì´ì½?
	long bonusRewardTimeStamp;//ë³´ë„ˆ???€?„ìŠ¤?¬í”„

	int x;//x?„ì¹˜
	int y;//y?„ì¹˜

	int nx;//?´ë™??x?„ì¹˜
	int ny;//?´ë™??y?„ì¹˜

	int targetX, targetY;//ëª©ì ì§€ XY 
	int targetX2, targetY2;//ëª©ì ì§€ XY 
	float speed;//?´ë™?ë„
	float speedIncrement;//?´ë™?ë„ ì¦ê???
	float speed2;//?´ë™?ë„2
	float speedIncrement2;//?´ë™?ë„ ì¦ê???
	int waitingFrame;//?œì‘?ˆì„ ??ë¨¸ë¬´ë¥´ëŠ” ?„ë ˆ??
	int waitingFrame2;//ì¤‘ê°„???´ë™?ë„ ì²´ì¸ì§€ ?ˆì„ ??ë¨¸ë¬´???„ë ˆ??
	int frame;//?„ì¬ ?„ë ˆ??
	int frame2;//
	int aniFrame;

	bool front;//trueë©?attackSequenceDraw ê°™ì??°ì„œ ê·¸ë ¤ì¤€??

	int drawFunc;

	float zoom;
	float zoomEnd;
	float zoomIncrement;
	float zoom2;
	float zoomEnd2;
	float zoomIncrement2;

	int owner;

	int dirX;
	int dirY;

	int dx;
	int dy;

	int alpha;
} BAR;

typedef struct _log {
	bool active;
	unsigned char type;//LOG_EVENTSTART, LOG_JOKBOOPEN, LOG_RAID, LOG_BATTLE, LOG_BOSSHEAL

	unsigned short cmf;//?„ê? ?ˆëƒ. ë³´ìŠ¤ë©?cmf ê°€, ?˜ìŠ¤?¸ë©´ ì¡±ë³´ ?¸ë±?¤ê? ?¬ë‹¤.
	unsigned short cmf2;//?ì´ ?°ë¦¬??npcë¥??¸ë©´

	unsigned short icon;//?„ì´ì½?
	long long count;//?«ì ?•ë³´ê°€ ?„ìš”??ê²½ìš°

	int x;//x?„ì¹˜
	int y;//y?„ì¹˜

	signed char dirX, dirY;//ë°©í–¥
	float dx, dy;//x, yì¶??´ë™ê±°ë¦¬

	int targetX, targetY;//ëª©ì ì§€ XY 
	int targetX2, targetY2;//ëª©ì ì§€ XY 
	float speed;//?´ë™?ë„
	float speedIncrement;//?´ë™?ë„ ì¦ê???
	float speed2;//?´ë™?ë„2
	float speedIncrement2;//?´ë™?ë„ ì¦ê???
	int waitingFrame;//?œì‘?ˆì„ ??ë¨¸ë¬´ë¥´ëŠ” ?„ë ˆ??
	int waitingFrame2;//ì¤‘ê°„???´ë™?ë„ ì²´ì¸ì§€ ?ˆì„ ??ë¨¸ë¬´ë¥´ëŠ” ?„ë ˆ??
	int frame;//?„ì¬ ?„ë ˆ??
	int frame2;//

	float zoom;
	float zoomEnd;
	float zoomIncrement;
	float zoom2;
	float zoomEnd2;
	float zoomIncrement2;

	char text[256];
} LOG;
//?„íˆ¬ì°½ì—??ë³´ì—¬ì¤?ë¶€ë¶?
typedef struct _battleLog {
	unsigned char type;//LOG_EVENTSTART, LOG_JOKBOOPEN, LOG_RAID, LOG_BATTLE, LOG_BOSSHEAL

	unsigned short who;//?„ê? ?ˆëƒ. ë³´ìŠ¤ë©?cmf ê°€, ?˜ìŠ¤?¸ë©´ ì¡±ë³´ ?¸ë±?¤ê? ?¬ë‹¤.

	unsigned short icon;//?„ì´ì½?
	long long count;//?«ì ?•ë³´ê°€ ?„ìš”??ê²½ìš°

	std::string text;
} BATTLELOG;

typedef struct _charData {
	ITEM equip[TOTALEQUIP];//ìºë¦­??3ëª…ì— ?€?´ì„œ??
	HOTKEY hotKey[MAXHOTKEY];//?¸íŒ…?˜ì–´ ?ˆëŠ” ?¤í‚¬(1ê°??€ ?Œí™˜??1ê°??€ ?™ë£Œ(1ê°?ë¥??œë¤?˜ê²Œ ?Œë ¤??ì¶œë™?œí‚¨??
	int exps;//?´ê²Œ ?ˆìœ¼ë©???œ¼ë¡?stat?€ ?¸íŒ…?????ˆë‹¤.
	long long int hp;
	int mp;
	unsigned short ap;
	unsigned char sp;

	signed char skillLv[TOTAL_SKILL];
	unsigned char getSkillList[MAXCHARSKILL];

	//?„ë˜ê³„ì—´?¤ì? RefreshStat?œë²ˆ ?˜ë©´ ?ë™?¼ë¡œ ê°’ì´ ? ë‹¹?˜ê±°???„íˆ¬ì¤??„ì‹œ ê°’ì´ë¯€ë¡??¨ìŠ¤
	//signed short buff[TOTALBUFF];
	//signed int debuf[TOTALDEBUF];
	//signed char immune[TOTALDEBUF];

	template <class Archive>
	void serialize(Archive & ar)
	{
		ar(
			equip[TOTALEQUIP]
		);
	}
} CHARDATA;

//PVP ?°ì´??
//?¼ë‹¨ ? ì?ë²ˆí˜¸ê°€ ?ˆê³ 
typedef struct _house {
	long long idx;//ì§??¸ë±??
	long long userId;//??ì§‘ì˜ ?Œìœ ì£¼ì¸ ?œë²„?ì˜ ? ì? ?„ì´??
	long long userProfileImgIdx;//? ì??„ë¡œ???´ë?ì§€ ?¸ë±??
	long long userName;//? ì? ?´ë¦„
	unsigned char equipImg[TOTALCHAR][TOTALEQUIP];//??ì§??Œìœ ì£¼ì˜ ì½”ìŠ¤?¬ì´ë¯¸ì?
	long long gold;//??ì§??Œìœ ì£¼ì˜ ?„íˆ¬???ë“?????ˆëŠ” ê³¨ë“œ
	unsigned char houseType;//??ì§??Œìœ ì£¼ì˜ ì§??¸ë±??
	unsigned short crew[MAXCREW];//?¬ë¥˜???¸ë±??
	unsigned char crewMaxStar[MAXCREW];//?¬ë¥˜??ìµœë? ?ˆë²¨
	unsigned char crewCurStar[MAXCREW];//?¬ë¥˜???„ì¬ ?ˆë²¨
} HOUSE;

//ë¡œë¹ˆêµ¬ì¡°ì²´ëŠ” ê²Œì„ ?„ì²´???€???€?¥ì†Œ?´ë‹¤.
//
//?¬ê¸°???€?¥ë˜???°ì´?°ë§Œ
typedef struct _robin {
	CHARDATA charData[TOTALPLAYER];//?œë²„???€?¥ë˜??ë¡œë¹ˆ???€???°ì´??/ì°¨í›„???ë?ë°?? ì?ê°€ 
	ITEM inven[TOTALINVENTORY];//?¸ë²¤? ë¦¬??ê³µìœ ?œë‹¤.
	ITEM newItem;
	//?±ì—?œëŠ” ?„ì¬ ?ë“???¬ë¥˜?¤ì´ ?ìœ ?¤ëŸ½ê²??Œì•„?¤ë‹ˆ??ê²ƒì´ ?„ë‹ˆ?? ?•í•´ì§??„ì¹˜??ë°•í????˜ì˜¤?”ê²ƒ?¼ë¡œ ?˜ì.
	//
	int curCrew[MAXCREW];//?„ì¬ ëª‡ë²ˆ crewê°€ ?¸íŒ…?˜ì–´ ?ˆëŠ”ì§€

	int stage;
	int room; 
	int maxStage[TOTALCASTLE];//?„ì¬ ?´ë””ê¹Œì? ê°”ëŠ”ì§€.
	int maxRoom[TOTALCASTLE];

	bool demoSeen[TOTALDEMO];

	unsigned short count;//?¸ë²¤? ë¦¬?ˆì— ?ˆëŠ” ?„ì´?œì˜ ê°œìˆ˜
	unsigned short maxInven;//?¸ë²¤? ë¦¬?ˆì— ?ˆëŠ” ?„ì´?œì˜ ê°œìˆ˜

	long long gold;//ê³¨ë“œ
	long long heart;//?˜íŠ¸
	long long medal;//PVP ?„ìš© ì¹´ìš´??
	long long star;//
	long long hammer;//?©ì„±??
	int shield;//ë°©ì–´
	long long coin;//ë¸”ë¡ì²´ì¸ ì½”ì¸

	long heartTimeStamp;

	int buffItem[TOTAL_WASTE];
	unsigned short medalShop[TOTALMEDALSHOP * MEDALSHOPDATASIZE];

	int playtime;//?Œë ˆ?´í???

	bool statue[TOTAL_STATUE];
	std::string nickname;

	bool equipGet[ITEM_GEM_START];//

	int maxStatusCnt;

	int enemyUserIdx;//?„ì¬ ?¸íŒ…?˜ì–´ ?ˆëŠ” ?ë?ë°?

	int quest;//?„ì¬ ?˜ìŠ¤??
	int subQuest;//
	int questCnt;//?„ì¬ ?˜ìŠ¤??ì¹´ìš´??

	long questTimeStamp;
	long long remainQuestItem;
	long long thisTimeQuestItem;

	int pvpQuest;
	int pvpSubQuest;
	int pvpDetailQuest;
	int pvpQuestCnt;

	long pvpQuestTimeStamp;
	long long remainPvpQuestItem;
	long long thisTimePvpQuestItem;

	OBJECT enemyObj[MAXENEMY * MAXENEMYOBJ];

	long freeRewardTimeStamp;

	GAMEEVENT gameEvent[MAXGAMEEVENT];

	unsigned char openedMenu[TOTAL_MENU];

	int eventCnt;

	signed char bossRoom;//
	//false ë©??¼ë°˜ë°?
	//true ë©?ë³´ìŠ¤ë°?
	//2 ë©?ê³¨ë“œ?´ë²¤??

	//?¼ì¼ ë³´ìƒ
	long calendarTimeStamp;
	//ìº˜ë¦°?”ì˜ ?¼ë³„ ?¤í…Œ?´í„°?¤ë¡œ 
	//0?´ë©´ 
	int calendarDayStatus[WEEK];
	int calendarMonthDay;

	int waveIdx;//ëª‡ë²ˆì§??¨ì´ë¸Œì¸ì§€
	int curWaveIdx;//?„ì¬ê¹Œì? ëª‡ê°œ???ì´ ?±ì¥?ˆëŠ”ì§€ ë³´ì—¬ì£¼ëŠ” 
	bool waveActive[MAXENEMY];//ìµœë? ?ë„¤ë¯?
	long waveTimeStamp;

	OBJECT boxObj;
	//?„ì¬ ì¡±ë³´ê°€ ?´ë–»ê²??˜ì—ˆ?”ì?ë¥?
	//1000ë²ˆë§ˆ??ìµœë? 2ë²ˆì´ ?˜ì˜¬ ???ˆë‹¤.
	int rouletteLog[MAXROULETTELOG];
	int rouletteLogIdx;//?„ì¬ ëª‡ë²ˆì§??¸ë±?¤ë? ?°ê³  ?ˆëŠ”ì§€
	int rouletteLog_HeartCnt;//?„ì¬ ?˜íŠ¸ê°€ MAXROULETTELOG ê¸°ì??¼ë¡œ ëª‡ë²ˆ ?˜ì? ?ˆëŠ”ì§€
	int rouletteLog_RaidCnt;//?„ì¬ ?ˆì´?œê? MAXROULETTELOG ê¸°ì??¼ë¡œ ëª‡ë²ˆ ?˜ì? ?ˆëŠ”ì§€

	bool heroesSetting[TOTALCHAR];//?¥ì°©???˜ì–´ ?ˆëŠ”ì§€
	//ëª‡ë²ˆ ìºë¦­?°ë? ?˜ëŠ”ì§€
	int slotCrew[MAXCREW];

	int lv;
	int exps;

	// ?ˆë¡œ??ë£°ë › ?œìŠ¤??ë³€??
	int currentDay;           // ?„ì¬ Day
	int lifeRemaining;        // ?¨ì? ?˜ëª…
	
	int castle;

	long long startTime;

	template <class Archive>
	void serialize(Archive & ar)
	{
		ar(
			charData,
			inven,

			stage,
			room,

			demoSeen,

			count,

			gold,
			heart,
			medal,
			star,
			hammer,
			shield,
			coin,

			heartTimeStamp,

			buffItem,
			medalShop,

			playtime,

			statue,
			nickname,

			equipGet,

			maxStatusCnt,

			quest,
			subQuest,
			questCnt,

			questTimeStamp,
			remainQuestItem,
			thisTimeQuestItem,

			pvpQuest,
			pvpSubQuest,
			pvpDetailQuest,
			pvpQuestCnt,

			pvpQuestTimeStamp,
			remainPvpQuestItem,
			thisTimePvpQuestItem,

			freeRewardTimeStamp,

			gameEvent,

			openedMenu,

			eventCnt,

			bossRoom,

			calendarTimeStamp,

			calendarDayStatus,
			calendarMonthDay,

			boxObj,

			lv,
			exps,

			currentDay,
			lifeRemaining
		);
	}
} ROBINDATA;

typedef struct _alloced {
	ITEM shop[TOTALINVENTORY];
	signed short* cmf_pos[REALMAXCMF];
	unsigned short tempPtr[320 * 18];
	signed short waves[WAVE_DIAMETER * WAVE_DIAMETER];
} ALLOCED;

typedef struct _screen {
	unsigned char date[4];
	int type;
	int location;
	char url[24];
} SCREEN;

typedef struct _option {
	SCREEN screen[12];

	char verify[8];

	unsigned char usedResurrection;
	unsigned short maxInven;
	signed char curSlot;
	signed char saveSlot;

	bool BuyGame;
	bool bgm;
	bool se;
	bool voice;
	bool vibration;

	signed char speed;
	signed char effect;
	signed char pushAlarm;
	signed char hotSlot;

	signed char screenShot;
	signed char cleared;
	signed char change;

	unsigned char gameControl;
	float gameSpeed;
	bool macro;
	unsigned char language;

	bool facebook;
	bool google;
	bool gameCenter;
	bool guest;
	unsigned char gameMode;
	unsigned char cutOff;
} OPTION;

typedef struct _efffect {
	int color;
	int alpha;
	int frame;
	int gray;
	signed char edge;
	signed char sound;
	signed char shake;
	signed char type;
	int hpShake;
	int color2;//ë°”ë‚˜?¤ê¸°
} EFFECT;

typedef struct _movie {
	signed short start;
	signed short end;
	unsigned short text;
	unsigned short frame;
	unsigned short dCount;
	unsigned short index;
	unsigned char talker;
	unsigned short robinMotion[TOTALOBJECT];
	unsigned short movies[11];
	signed char type;
	signed char face;
} MOVIE;

typedef struct _poptalk {
	int temp;
	int obj;
	int frame;
	int menu[4];
	int count;
	int cur;
	int clr;
	int width;
} POPTALK;

typedef struct _hitMark {
	signed short x;
	signed short y;
	int frame;
	signed char type;
	unsigned char dir;
	unsigned char etc;
	unsigned short owner;
	unsigned short target;
	float zoom;
} HITMARK;

typedef struct _dmgInfo {
	signed short x;
	signed short y;
	long long dmg;
	int frame;
	signed char type;
	signed short pos;
	unsigned short owner;//?°ë?ì§€ë¥?ì¤€ ?ê? ?„êµ°ì§€
	unsigned short target;//?°ë?ì§€ë¥?ë°›ì? ?ê? ?„êµ°ì§€
	int color;

	float zoom;
} DMGINFO;

typedef struct _iconMark {
	int imageOffX, imageOffY; //?´ë?ì§€ ?¤í”„??X, Y
	int imageDx, imageDy; //?´ë?ì§€ ë©´ì  dx, dy
	int resNum;//?´ë?ì§€ ?¸ë±??
	int x, y;//?„ì¬ x, y?„ì¹˜
	int targetX, targetY;//ëª©ì ì§€ XY 
	int targetX2, targetY2;//ëª©ì ì§€ XY 
	signed char dirX, dirY;//ë°©í–¥
	float dx, dy;//x, yì¶??´ë™ê±°ë¦¬
	float speed;//?´ë™?ë„
	float speedIncrement;//?´ë™?ë„ ì¦ê???
	float speed2;//?´ë™?ë„2
	float speedIncrement2;//?´ë™?ë„ ì¦ê???
	int waitingFrame;//?œì‘?ˆì„ ??ë¨¸ë¬´ë¥´ëŠ” ?„ë ˆ??
	int waitingFrame2;//ì¤‘ê°„???´ë™?ë„ ì²´ì¸ì§€ ?ˆì„ ??ë¨¸ë¬´???„ë ˆ??
	int frame;//?„ì¬ ?„ë ˆ??
	int frame2;//
	int lockOpenFrame;//? ê????´ë¦¬???„ë ˆ??
	int moveAngle;
	int amount;
	int type;//ì¹´ë“œ?ì„œ???´íƒ?€??
	int detail;
	int grade;
	int cooldown;
	int icon;

	int attackType;
	int attackStr;

	float zoom;
	float zoomEnd;//ì¤?
	float zoomIncrement;
	float zoom2;
	float zoomEnd2;//ì¤?
	float zoomIncrement2;
	int alpha;
	bool text;
	bool value;
	bool ani;

	int owner;//ao???¸ë±??
	int jokboIcon;//ë°•ìŠ¤??ê²½ìš°?ëŠ” ?¸ë£¨
	bool star;
	bool cardFrame;
	bool newItem;

	int bar;//?´ë–¤ ë°”ë? ?¥í•´ ê°€???˜ëŠ”ì§€.
} ICONMARK;

typedef struct _iconMarkArr {
	int imageOffX, imageOffY; //?´ë?ì§€ ?¤í”„??X, Y
	int imageDx, imageDy; //?´ë?ì§€ ë©´ì  dx, dy
	int resNum;//?´ë?ì§€ ?¸ë±??
	int x, y;//?„ì¬ x, y?„ì¹˜
	int targetX, targetY;//ëª©ì ì§€ XY
	int targetX2, targetY2;//ëª©ì ì§€ XY 
	signed char dirX, dirY;//ë°©í–¥
	float dx, dy;//x, yì¶??´ë™ê±°ë¦¬
	float speed;//?´ë™?ë„
	float speedIncrement;//?´ë™?ë„ ì¦ê???
	float speed2;//?´ë™?ë„2
	float speedIncrement2;//?´ë™?ë„ ì¦ê???
	int waitingFrame;//?œì‘?ˆì„ ??ë¨¸ë¬´ë¥´ëŠ” ?„ë ˆ??
	int waitingFrame2;//ì¤‘ê°„???´ë™?ë„ ì²´ì¸ì§€ ?ˆì„ ??ë¨¸ë¬´???„ë ˆ??
	int frame;//?„ì¬ ?„ë ˆ??
	int frame2;//?„ì¬ ?„ë ˆ??
	int endFrame;//ì¢…ë£Œ ?„ë ˆ??
	int endFrame2;//ì¢…ë£Œ ?„ë ˆ??
	int moveAngle;
	int amount;
	int type;//ì¹´ë“œ?ì„œ???´íƒ?€??
	int detail;
	int grade;
	int cooldown;
	int icon;

	int attackType;
	int attackStr;

	float zoom;
	float zoomEnd;
	float zoomIncrement;
	float zoom2;
	float zoomEnd2;//ì¤?
	float zoomIncrement2;
	int alpha;
	bool text;
	bool value;
	bool ani;

	int owner;//ao???¸ë±??
	bool jokboIcon;//ë°•ìŠ¤??ê²½ìš°?ëŠ” ?¸ë£¨
	bool star;
	bool cardFrame;

	int iconMarkCnt;//?¼ë§ˆ???„ì´ì½˜ë§ˆ?¬ë? ?ì„±?´ì•¼ ?˜ëŠ”ì§€ 
	float gap;

	int collectionIdx;
	int bar;
} ICONMARKARR;

typedef struct _position {
	signed short x;
	signed short y;
	signed char frame;
	signed char dir;
} POSITION;

typedef struct _bgObj {
	signed short x;
	signed short y;
	signed char active;
	signed char etc;
	signed char dx;
	signed char frame;
} BGOBJ;

typedef struct _escort {
	int frame;
	unsigned short start, end;
	signed short x;
	signed short y;
	unsigned short movie;
	signed short map;
	unsigned char type;
	unsigned char active;
} ESCORT;

typedef struct _gameData {
	//ëª¬ìŠ¤?°ë? ?¡ì? ?Ÿìˆ˜
	unsigned int monsterKill[NPC_CAPTAIN * 3];
	unsigned int monsterKill2[TOTALMAPTYPE];

	//ëª¬ìŠ¤?°í•œ??ì£½ì? ?Ÿìˆ˜
	unsigned short monsterVictim[NPC_CAPTAIN * 3];

	//ëª¬ìŠ¤?°í•œ??ê±¸ë ¤ë³??”ë²„??
	signed char monsterDebuf[NPC_CAPTAIN];

	//ëª¬ìŠ¤?°ì—ê²Œì„œ ?»ì–´ë³??¬ë£Œ
	signed char monsterMaterial[NPC_CAPTAIN];

	unsigned char currentTitle;

	unsigned char shopCount[3];

	// ê¸¸ë“œ??ê´€??ë³€??
	int guildTime;
	int guildLength;
} GAMEDATA;

typedef struct _tempSave {
	unsigned int playtime;
	unsigned int gold;
	unsigned char equipImg[TOTALEQUIP];
	unsigned char type;
	signed char curArea;
	signed char seenFrog;
	unsigned char lv;
	unsigned char coupon;
	unsigned char playMode;
} TEMPSAVE;

//SetRoom ??ì´ˆê¸°???œí‚¬ë³€?˜ë“¤
typedef struct _reportVar {
	unsigned short stayMonster;
	signed char isTalked;
	signed char isUseSkill;
	signed char activeItem;
} REPORTVAR;

//NewGame??ì´ˆê¸°???œí‚¬ë³€?˜ë“¤
typedef struct _reportVar2 {
	int roomFrame;
	int gandhi;
	int darkStone;
	unsigned short noPotion;	//ê²€?Œí•œ ê°•ì(?¬ì…˜???¬ìš©?˜ì? ?Šê³  ?¡ì? ëª¬ìŠ¤??ë§ˆë¦¿??
	unsigned short saint;
	unsigned short diver;
	unsigned short fallHeight;
	unsigned char hp1;
	unsigned char item;
	signed char itemWeapon[24];
	signed char itemHelm[24];
	signed char itemArmor[24];
	signed char itemPants[24];
	signed char itemGlove[24];
	signed char itemBoots[24];
	signed char itemNeck[TOTAL_NECK];
	signed char itemRing[TOTAL_RING];
} REPORTVAR2;

// UI ?ŒíŠ¸ êµ¬ì¡°ì²?
struct UiImagePart
{
	const char* name;
	int srcIdx;          // ?´ë?ì§€ ?¸ë±??(sprite ë°°ì—´)

	// source rect
	int xs;
	int ys;
	int w;
	int h;

	// destination position
	int x;
	int y;

	bool flipX;
	int cmfRotation;
	float rotation;
	int effect;
	int alpha;
	float zoom;
};

// =========================
// Jump Roulette State
// =========================

struct ReelJumpState {
	JumpState state;
	float jumpY;        // ?„ì¬ ?í”„ ?’ì´(px)
	float jumpV;        // ?í”„ ?ë„(px/frame)

	float maxJumpY;     // ê·¸ë¦¼???°ì¶œ??ìµœë? ?’ì´)
	int curShowPos;     // ?„ì¬ ë³´ì—¬ì£¼ëŠ” alivePos
	int landedPos;      // ì°©ì? ?•ì • alivePos
	int lastSwapF;      // ë§ˆì?ë§?êµì²´ ?„ë ˆ??

	bool started;     // ?´ë²ˆ ?¬ë¡¯ ?°ì¶œ?ì„œ ?´ë‹¹ ë¦´ì´ ?œì‘?ˆëŠ”ì§€
	int holdEndFrame;   // slotFrame ê¸°ì?, ?¬ê¸°ê¹Œì? JS_HOLD ? ì?

	// --- ì¶”ê? ---
	bool  flipLR;         // ì¢???? ê?(?Œì „ ?ë‚Œ)
	int   lastFlipF;      // ë§ˆì?ë§?? ê? ?„ë ˆ??
	int   flashEndF;         // ë°˜ì§ FX ì¢…ë£Œ ?„ë ˆ??
	int   vortexEndF;        // ?Œì˜¤ë¦?FX ì¢…ë£Œ ?„ë ˆ??

	// [MOD-R1] ?¤ì§‘ê¸??Œì „) ?¤ì¿¼???°ì¶œ??
	int   flipSquashEndF;   // ???„ë ˆ?„ê¹Œì§€ ?¤ì¿¼???ìš©
	int   flipSquashLen;    // ì§€???„ë ˆ??2~4 ì¶”ì²œ)

	int bounceLeft; // 1?´ë©´ ì°©ì? ??ë¯¸ë‹ˆë°”ìš´??1ë²?
};

extern ReelJumpState gReelJump[TOTALREEL];
// [MOD-G] ??ê°??•ì • ??ì¢…ë£Œ ?œë ˆ?´â€?ì¹´ìš´??
extern int sEndDelayLeft;

extern int logIndex;

//?œìŠ¤??
extern cocos2d::Sprite* sprite[TOTALIMG];
extern cocos2d::Texture2D* texture[TOTALIMG];
//?†ìœ¼ë©??´ë?ì§€ ì¶”ê?(?†ë‹¤??ê¸°ì??€ rendeSpriteIndex == -1 ?´ë©´
extern cocos2d::Sprite* renderSprite[MAXRENDERCNT];//?´ë?ì§€ ? ê·œ?ì„±???¬ìš©
extern int renderSpriteIndex[MAXRENDERCNT];//?´ë?ì§€ ? ê·œ?ì„±???¬ìš© - ?Œë”?¤í”„?¼ì´?¸ê? TOTALIMG ì¤‘ì— ëª‡ë²ˆ???´ì•˜?”ê?
//0ê°’ì´ ê¸°ë³¸?´ê³  ?´ë?ì§€ê°€ ?ì„±?˜ë©´ ì¹´ìš´?¸ê? ?˜ë‚˜ ?˜ì–´?˜ëŠ”ê±°ì?
extern int sameRenderSpriteMax[TOTALIMG];//?„ì¬ ìµœë? ëª‡ê°œê¹Œì? ì¶”ê??˜ì—ˆ?”ê?
//?„ì¬ sameRenderSpriteMax???„ë‹¬?˜ì? ?Šì•˜?”ì?ë¥??ë‹¨?´ì„œ ê¸°ì¡´ê²ƒì„ ?¬ìš©?˜ê³  ?˜ë‚˜??ì¹´ìš´?¸ë? ì¦ê??œí‚¤?”ê±°ì§€
extern int sameRenderSpriteCur[TOTALIMG];//?´ë²ˆ ?œë¡œ?°ì— ëª‡ê°œê¹Œì? ?°ê³  ?ˆëŠ”ê°€.(?„ë ˆ?„ë§ˆ??ì´ˆê¸°?”ë¨)
extern int sameRenderSpriteArr[TOTALIMG][3000];//ë°°ì—´???¹ì •?¸ë±?¤ì˜ ?´ë?ì§€ë¥??Œë”?¤í”„?¼ì´??ëª‡ë²ˆ???¤ì–´ê°€?ˆëŠ”ì§€ë¥??€?¥í•˜??ë°°ì—´
extern int curRenderSpriteArr[MAXRENDERCNT];
extern int getSpriteIdx;
extern int getSpriteTexture;
extern int totalRenderCnt;//?„ì¬ ê·¸ë ¤???˜ëŠ” ì´?ê°œìˆ˜
extern int curRenderCnt;//?„ì¬ ê·¸ë ¤???˜ëŠ” ì´?ê°œìˆ˜

//?†ìœ¼ë©??´ë?ì§€ ì¶”ê?(?†ë‹¤??ê¸°ì??€ rendeSpriteIndex == -1 ?´ë©´
extern cocos2d::Sprite* bufferSprite[MAXBUFFERSPRITECNT];//?´ë?ì§€ ? ê·œ?ì„±???¬ìš©
extern int bufferSpriteIndex[MAXBUFFERSPRITECNT];//?´ë?ì§€ ? ê·œ?ì„±???¬ìš© - ?Œë”?¤í”„?¼ì´?¸ê? TOTALIMG ì¤‘ì— ëª‡ë²ˆ???´ì•˜?”ê?
//0ê°’ì´ ê¸°ë³¸?´ê³  ?´ë?ì§€ê°€ ?ì„±?˜ë©´ ì¹´ìš´?¸ê? ?˜ë‚˜ ?˜ì–´?˜ëŠ”ê±°ì?
extern int sameBufferSpriteMax[TOTALIMG];//?„ì¬ ìµœë? ëª‡ê°œê¹Œì? ì¶”ê??˜ì—ˆ?”ê?
//?„ì¬ sameRenderSpriteMax???„ë‹¬?˜ì? ?Šì•˜?”ì?ë¥??ë‹¨?´ì„œ ê¸°ì¡´ê²ƒì„ ?¬ìš©?˜ê³  ?˜ë‚˜??ì¹´ìš´?¸ë? ì¦ê??œí‚¤?”ê±°ì§€
extern int sameBufferSpriteCur[TOTALIMG];//?´ë²ˆ ?œë¡œ?°ì— ëª‡ê°œê¹Œì? ?°ê³  ?ˆëŠ”ê°€.(?„ë ˆ?„ë§ˆ??ì´ˆê¸°?”ë¨)
extern int sameBufferSpriteArr[TOTALIMG][60 * 47];//ë°°ì—´???¹ì •?¸ë±?¤ì˜ ?´ë?ì§€ë¥??Œë”?¤í”„?¼ì´??ëª‡ë²ˆ???¤ì–´ê°€?ˆëŠ”ì§€ë¥??€?¥í•˜??ë°°ì—´
extern int curBufferSpriteArr[MAXBUFFERSPRITECNT];
extern int getBufferSpriteIdx;
extern int getBufferSpriteTexture;
extern int totalBufferCnt;
extern int curBufferCnt;

extern int bufferSpriteCnt;

extern int tileBufferSpriteIndex;

//#ifdef TTFFONT
extern Vec2 labelPosition;
extern std::string compareString;
extern std::string labelString;

extern TTFConfig ttfconfig;
extern cocos2d::Label* fontLabelWidth;//?°íŠ¸ ?“ì´???“ì´
extern cocos2d::Label* fontLabel[MAXFONTLABELCNT];//?¼ë²¨ ? ê·œ?ì„±???¬ìš©
extern int fontLabelIndex[MAXFONTLABELCNT];//?¼ë²¨ ? ê·œ?ì„±???¬ìš© - ?ìŠ¤?¸ë¼ë²¨ì´ ?°íŠ¸?¼ë²¨ ì¤?ëª‡ë²ˆ???´ì•˜?”ê?
extern int fontLabelMotherIndex[MAXFONTLABELCNT];//ë§Œì•½ ë³µì œê°€ ?˜ëŠ” ê²½ìš° ëª‡ë²ˆ??ë³µì œ??ê²ƒì¸ê°€
extern int sameFontLabelMax[TEXT_LENGTH];//?„ì¬ ìµœë? ëª‡ê°œê¹Œì? ì¶”ê??˜ì—ˆ?”ê?
extern int sameFontLabelCur[TEXT_LENGTH];//?´ë²ˆ ?œë¡œ?°ì— ëª‡ê°œê¹Œì? ?°ê³  ?ˆëŠ”ê°€.(?„ë ˆ?„ë§ˆ??ì´ˆê¸°?”ë¨)
extern int sameFontLabelArr[TEXT_LENGTH][100];//ë°°ì—´???¹ì •?¸ë±?¤ì˜ ?¼ë²¨???Œë”?¤í”„?¼ì´??ëª‡ë²ˆ???¤ì–´ê°€?ˆëŠ”ì§€ë¥??€?¥í•˜??ë°°ì—´
extern int curFontLabelArr[MAXFONTLABELCNT];//?˜ë‚˜ ì¶”ê?? ë•Œë§ˆë‹¤ ?¸ë±?¤ë? ì¶”ê??œë‹¤

extern int getFontLabelIdx;
extern int getFontLabelTexture;

extern int totalFontLabelCnt;
extern int curFontLabelCnt;
#ifdef BMFONT
extern cocos2d::LabelBMFont* textLabel[MAXLABELCNT];
#else
extern cocos2d::Label* textLabel[MAXLABELCNT];
#endif

extern int textLabelIndex[MAXLABELCNT];//?¼ë²¨ ? ê·œ?ì„±???¬ìš© - ?ìŠ¤?¸ë¼ë²¨ì´ TOTALIMG ì¤‘ì— ëª‡ë²ˆ???´ì•˜?”ê?
//0ê°’ì´ ê¸°ë³¸?´ê³  ?´ë?ì§€ê°€ ?ì„±?˜ë©´ ì¹´ìš´?¸ê? ?˜ë‚˜ ?˜ì–´?˜ëŠ”ê±°ì?
extern int sameTextLabelMax[TEXT_LENGTH];//?„ì¬ ìµœë? ëª‡ê°œê¹Œì? ì¶”ê??˜ì—ˆ?”ê?
//?„ì¬ sameRenderSpriteMax???„ë‹¬?˜ì? ?Šì•˜?”ì?ë¥??ë‹¨?´ì„œ ê¸°ì¡´ê²ƒì„ ?¬ìš©?˜ê³  ?˜ë‚˜??ì¹´ìš´?¸ë? ì¦ê??œí‚¤?”ê±°ì§€
extern int sameTextLabelCur[TEXT_LENGTH];//?´ë²ˆ ?œë¡œ?°ì— ëª‡ê°œê¹Œì? ?°ê³  ?ˆëŠ”ê°€.(?„ë ˆ?„ë§ˆ??ì´ˆê¸°?”ë¨)
extern int sameTextLabelArr[TEXT_LENGTH][100];//ë°°ì—´???¹ì •?¸ë±?¤ì˜ ?´ë?ì§€ë¥??Œë”?¤í”„?¼ì´??ëª‡ë²ˆ???¤ì–´ê°€?ˆëŠ”ì§€ë¥??€?¥í•˜??ë°°ì—´
extern int curTextLabelArr[MAXLABELCNT];
extern int getTextLabelIdx;
extern int getTextLabelTexture;

extern int totalTextLabelCnt;
extern int curTextLabelCnt;

//MC_GrpContext gContext;
extern cocos2d::RenderTexture* gScreenBuffer;//Screen Buffer
extern cocos2d::Layer* gScreenLayer;//Screen Buffer

extern cocos2d::Layer* bufferLayer[TOTALBUFFER];
extern cocos2d::RenderTexture* bufferTexture[TOTALBUFFER];

#ifdef ATLAS
extern cocos2d::Sprite* renderAtlas;
#endif

extern cocos2d::CCImage* fontImage;
extern int fontImageWidth;
extern int fontImageHeight;
extern long fontImageDataLen;

//cocos2d::Sprite* fontImageSolid;
extern unsigned char *fontImageData;


extern int *gScreenPtr, *gImagePtr;
extern cocos2d::Sprite* atlas;
extern cocos2d::SpriteFrameCache  *Cache;

extern int fontColorIdx[MAXFONTCOLOR];
extern float global_z;
extern int nextSeed, tms;
extern char selectedChar;

extern int audioID[TOTALMUSIC];
extern float audioVolume[TOTALMUSIC];

extern signed short curID;
extern char netCritical;
extern char phone[20];
extern signed char touchQuick;
extern signed char touchQuickIcon;
extern signed char touchDrawButton;
extern signed char touchDrawYesNo;
extern signed char touch;
extern int touchIndex;
extern int touchRect[TOTALTOUCHCNT][5];//int rx, int ry, int width, int height, int func
extern int startTouchRect[5];
extern int swipeIndex;
extern int swipeRect[TOTALSWIPECNT][5];//int rx, int ry, int width, int height, int func
extern bool swipeLock;
extern unsigned char rapidSwipe;
extern signed char DrawButton_OK;
extern int touch_Select;
extern signed char touchDownBar;
extern signed char touchOK;
extern signed char touchYESNO;
extern signed int pointX;
extern signed int pointY;
extern signed int pointType;
extern signed int clipX;
extern signed int clipY;
extern signed int clipX2;
extern signed int clipY2;
extern signed int clipX3;
extern signed int clipY3;
extern signed int clipX4;
extern signed int clipY4;
extern ClippingNode * clipNode;
extern signed short STATUSWIN_Y;//?„íˆ¬ë¥??„í•œ 
extern signed short STATUSWIN_Y_INIT;//?„íˆ¬ë¥??„í•œ
extern signed short STATUSWIN_Y2;
extern signed short PLAYAREA_X;
extern signed short PLAYAREA_Y;
extern signed char yesnoFrame;
extern signed char buy_Mode;

extern unsigned char imgLoaded;

//ì¶”ê? ?¤ìš´ë¡œë“œ ë³€??
#ifdef DOWNLOAD
extern signed char isDown;	//ì¶”ê??¤ìš´ ë°›ì•˜?”ì? ?¬ë?//startCelt?ì„œ ê²€??
extern signed char oldDraw;	//?¬ë“œë³€?˜ë? ?€?¥í•˜ê³ ìˆ?¤ê?, ?¤ìš´ë¡œë“œ ?„ë£Œ???´ë‹¹ ?íƒœë¡??Œë ¤ì¤€??
#endif

extern int thickColor;
extern int fontColor, oldColor;
extern int baseColor;

extern const char* textString;	//?„ë ˆ?„í…?¤íŠ¸???¤íŠ¸ë§?
extern unsigned short textStringLength[50];
extern unsigned short textStringOffset[50];
extern unsigned char textStartColor[50];
extern unsigned short textFrame;	//?„ë ˆ?„ë”°???ì  ì°í???¬ìš©
extern unsigned char textPage;	//?ë˜ ê¸¸ì´ê°€ ëª‡í˜?´ì? ì§œë¦¬?¸ì? ?¬ìš©
extern unsigned char textCurPage;	//?„ì¬ ëª‡ë²ˆì§??˜ì´ì§€?¸ê?
extern unsigned char textLines;	//ëª‡ì¤„ì§œë¦¬??
extern unsigned char textBalloonFrame;

extern int popUpFrame;

extern int VERSION;
extern signed char m_lgrpAlpha;
extern signed char zoomFrame;
extern unsigned short waveFrame;
extern unsigned char* viewRadius;
extern unsigned char* viewRadius2;
extern signed char grayScale;
extern signed char blendDepth;
extern int blendColor;


extern unsigned short realRate;
extern unsigned short refreshRate;
extern unsigned char mustRefresh;
extern signed char running;
extern signed char resumeFlag;

//?¤ì¡°??
extern int systemKey;
extern int systemRelease;
extern int lastPressedKey;
extern int realPressedKey;
extern int releasedKey;
extern int releaseFrame;
extern int touchPressedKey[MAXKEYPRESSED][2];
extern int touchX, touchY;
extern int startTouchX, startTouchY;
extern int endTouchX, endTouchY;
extern bool startTouchCheck;

extern signed char touchMode;
extern signed char touchModeOld;
extern signed char isTouchKey;
extern signed char twice_released;
extern signed char is_key_pressed;
extern signed char is_key_released;
extern signed char is_press_finished;
extern signed char is_release_finished;
extern signed char key_released;
extern signed char keyLock;
extern signed char multiKey;
extern signed char keyStatus;
extern int clearFrame;
extern int releaseClearFrame;
extern signed char is_touchkey_pressed;

//int keyCount = 0;

extern unsigned char keyHandle, drawHandle, before_DrawHandle, before_KeyHandle, before_DrawHandle_Gacha, before_CurMenu_Gacha, before_KeyHandle_Gacha, before_DrawHandle_Collections, before_KeyHandle_Collections, before_DrawHandle_NewCard, before_KeyHandle_NewCard, next_DrawHandle, next_KeyHandle, before_DrawHandle_StageClear, before_KeyHandle_StageClear;
extern unsigned short DX, DY;
extern unsigned short TILEDX, TILEDY;
extern unsigned short REALDX, REALDY;
extern unsigned short SCREENRATIO;
extern unsigned short BLAHBLAHDRAWSTARTY;
extern unsigned short RANKINGDRAWSTARTY;
extern unsigned short SKILLDRAWSTARTY;
extern unsigned short POPUPPOSITION_Y;
extern unsigned short notch;
extern signed int offX, offY;
extern signed int xOffset;
extern signed int rw, rh, rx, ry;
extern int frame, demoFrame, timeFrame, touchFrame, touchedFrame, cageFrame;
extern unsigned char infoType, infoData;
extern unsigned short infoText, infoFrame, explainFrame, explainText, battleStartFrame;
extern unsigned short skillInfoFrame;
extern unsigned short ringFrame;
extern signed int curSkill;
extern signed int areaFrame;
extern signed int phaseFrame;
extern unsigned char itemFrame;
extern unsigned char npcGetFrame;
extern unsigned char stageClearFrame;
extern unsigned short skillGetFrame;
extern unsigned short buffItemFrame;
extern unsigned short getSkill;
extern unsigned char totalDmgUpdateFrame;
extern unsigned char onceDmgUpdateFrame;
extern unsigned char nameFrame, nameObj;
extern signed char warpFrame, returnFrame;
extern unsigned char curEnemyFrame;	//?„ì¬ ???´ë¦„??ëª‡í”„?ˆì„?™ì•ˆ ???ˆë‚˜
extern signed int curEnemy;	//?„ì¬ ê³µê²©ì¤‘ì¸ ëª¬ìŠ¤?°ê? ?„êµ¬??
extern signed int curPlayer;	//?„ì¬ ê³µê²©ë°›ê³  ?ˆëŠ” ì£¼ì¸ê³µì? ?„êµ¬??
extern signed char newStart;
extern signed int gameOverFrame;
extern signed int questFrame;
extern signed int alert;
extern unsigned char minimapFrame;
extern unsigned char dianaTrapFrame;
extern signed int volumeFrame;
extern unsigned char vibrationFrame;
extern signed int lenzFlag;
extern unsigned char radiusStatus;


extern char tempStr[256];
extern char tempStr2[256];
extern char tempStr3[256];
extern char labelStr[256];
extern char labelStr2[256];
extern char labelStr3[256];
extern char skillStr[256];
extern char ringStr[256];
extern char skillStr2[256];//?¤í‚¬?ì„¸?¤ëª…
extern char ringStr2[256];
extern char skillStr3[256];//?¤í‚¬?´ë¦„
extern char skillToolTips[256];//?¤í‚¬?´ë¦„
extern char skillBodyStr[256];
extern char buffItemStr[256];
extern char buffItemStr2[256];
extern char infoStr[100];
extern LOG gameLog[MAXLOG];
extern LOG battleLog[MAXBATTLELOG];
extern char optionStr[TOTALMENUOPTION][50];
extern char itemOptionStr[50];
extern char screenStr[100];
extern char playerTitle[24];
extern char phoneStr[10][8];
extern int bmFontColor[256];

#ifndef KTF

extern ROBINDATA robin;
extern GAMEDATA game;
extern ALLOCED a;

#else

#ifdef RELOCATE
extern int dRes;
extern int robinRes;
extern int gameRes;
extern int ac;

extern DATA *d;
extern ROBINDATA *robin;
extern GAMEDATA *game;
extern ALLOCED *a;
#else
extern DATA d;
extern ROBINDATA robin;
extern GAMEDATA game;
extern ALLOCED a;
#endif

#endif

extern char setStr[7][36];
extern char gemStr[6][20];
extern char dmgStr[100];
extern char recipeName[40];
extern char recipeDesc[TOTALARENA];
extern char recipeDmg[20];
extern char itemName[40];
extern char defaultStatStr[40];

extern OPTION option;
extern EFFECT effect;
extern MOVIE movie;
extern POPTALK talk;
extern DMGINFO dmgInfo[TOTALHITMARK];
extern DMGINFO imgText[TOTALHITMARK];
extern HITMARK hitMark[TOTALHITMARK];
extern ICONMARKARR currencyMarkArr[TOTALCURRENCYMARKARR];
extern ICONMARKARR currencyMarkArr_PopUp[TOTALCURRENCYMARKARR];
extern ICONMARK currencyMark[TOTALCURRENCYMARK];
extern ICONMARK currencyMark_PopUp[TOTALCURRENCYMARK];
extern ICONMARK itemMark[TOTALITEMMARK];
extern ICONMARK controlMark[TOTALCONTROLMARK];
extern ICONMARK controlMarkBack[TOTALCONTROLMARK];
extern bool controlerSpread[TOTALCONTROLMARK];
extern ICONMARK cardMark[TOTALCARDMARK];
extern ICONMARK cardMarkBack[TOTALCARDMARK];
//ë©”ì¸ë³´ìƒë¦¬ìŠ¤???¬ê¸°???œë²ˆ ë°›ëŠ” ëª¨ë“  ë³´ìƒ ?œí€€??1depthê°€ ?¤ì–´ê°„ë‹¤.)
extern ICONMARK rewardMark[TOTALREWARDMARK];
extern ICONMARK rewardMarkBack[TOTALREWARDMARK];
extern ICONMARK rewardMark_PopUp[TOTALREWARDMARK];
//ê°€ì± ìš© ë°•ìŠ¤ë§ˆí¬. (ê°€ì± ë? ?¤ì–´ê°”ì„ ???¬ëŸ¬ê°œì˜ ë°•ìŠ¤ê°€ ?ˆìœ¼ë©?ëª¨ë‘ ?¬ê¸° ?¤ì–´ê°„ë‹¤.)
extern ICONMARK boxMark[TOTALBOXMARK];
//ë°•ìŠ¤?ì„œ ì¹´ë“œë¥?ê¹????˜ì˜¤??ê²ƒë“¤
extern ICONMARK boxCardMark[TOTALCARDMARK];//ë³´ì¡°ë°•ìŠ¤?ì„œ ?˜ì˜¨ ë¦¬ì›Œ?œë§ˆ??
//?Œìš¸ë§ˆí¬
extern ICONMARK soulMark;
extern ICONMARK goldAlphaMark[TOTALGOLDALPHAMARK];

//ë°°í??ì„œ ?°ì´???„íˆ¬
extern OBJECT ao[TOTALOBJECT];
extern BAR bar[TOTAL_BAR];

extern TEMPSAVE tempSave[3];
extern CURRENCYEFFECT currencyEffect[TOTAL_CURRENCY];
extern signed short crX, crY, crW, crH;

extern char saveMem[sizeof(ROBINDATA)];
extern char backupMem[sizeof(ROBINDATA)];

//ë§?ê´€??ë³€??
extern unsigned short focus;
extern signed short loadedMap;
extern unsigned char mapData[15];
extern unsigned char mapArray[3000];
extern unsigned char mapInfoArray[3000];
extern unsigned short mapInfoOff;
extern unsigned char mapRect[MAXRECT * 5];
extern signed short mapBackObj[MAXBACKOBJ * 3];
extern signed short mapForeObj[MAXFOREOBJ * 3];
extern signed short mapNeutralObj[MAXNEUTRALOBJ * 4];
extern unsigned short mapEnemyObj[TOTALARENA * 4];
extern signed short bubbleXY[6 * 2];
extern signed char fadeFrame;
extern signed char dontWarp;
extern int fadeColor;


//Splash
extern POSITION splash;
extern BGOBJ bgObj[MAXBGOBJECT];
extern unsigned char splashType;

//TALK ê´€??ë³€??
extern unsigned char talkShakeFrame;

extern int touchCount;

//cmf ê´€??ë³€??
extern unsigned char costumeImg[MAXPLAYER];
extern signed short cmfLoaded[REALMAXCMF];	//Loaded Cmf Num
extern unsigned short cmf_m_cnt[REALMAXCMF];	//Motion Count
extern unsigned short cmf_i_cnt[REALMAXCMF];	//Image Count
extern unsigned short cmf_v_cnt[REALMAXCMF];	//Variable Array Length
extern signed short cmf_i_div[REALMAXCMF][6];	//Image Sprite Relation Info
extern signed short *old_cmf_ptr[REALMAXCMF];
const extern unsigned short* cmd_i_offset[REALMAXCMF];	//Image Offset
const extern unsigned short* cmd_m_cnt[REALMAXCMF];	//Image Count Per Motion
const extern signed short* cmd_m_crash[REALMAXCMF];	//Crash Area Per Motion
const extern signed short* cmd_m_img[REALMAXCMF];	//Part Image Num And Offset

extern signed short cmf_status_data[REALMAXCMF][MAXSTATUS][1024];
const extern signed short * cmf_change_data[REALMAXCMF];

//?Œë ˆ?´ì–´ ?€ì§ì„ ê´€??ë³€??
const extern unsigned short* skillStartFrame;
const extern unsigned short* skillClosingFrame;
const extern unsigned char * skillMotion;
extern unsigned char whichPlayer;
extern unsigned char isDemo;
extern unsigned short attackDelay;
extern int sequenceDelay;
extern unsigned char skillUsed;
extern unsigned char buffItemUsed;
extern unsigned char ringUsed;
extern unsigned char ringUser;

extern ESCORT escort;
extern signed char demoPlayerX[PLAYERALL];
extern signed char boomerangAway[PLAYERALL];
extern signed short pDx, pDy;
extern unsigned char currentQuest;
extern unsigned char currentTimeQuest; //?„ì¬ ?€?„í€˜ìŠ¤???€??
extern unsigned short TimeFailDemo;    // ?€?„í€˜ìŠ¤???¤íŒ¨???™ì‘?´ì•¼?˜ëŠ” ?°ëª¨???€??
extern unsigned char darkStone;
extern unsigned char npcdarkStone;

//?Œë ˆ?´ì–´ ?´ë?ì§€ ê´€??ë³€??

//ë¬??´ë?ì§€ ê´€??ë³€??
extern unsigned char doorCmf[MAXDOOR];
extern unsigned char doorCnt;

//?„ì´??ê´€??ë³€??
extern ITEM tempItem;
extern ITEM helpItem[MAXHELPITEM];
extern int tempItemIdx;//?¸ë²¤? ë¦¬??ëª‡ë²ˆ?¸ì?
extern signed short itemObj;
extern unsigned char tempFishItem;
extern unsigned char nInvenMax, nInvenCnt, nShopCnt;
//int needErase[10];
extern int shopDesc[MAXNETSHOP];
extern int cItem;
extern ITEM focusItem;
extern int boxNeutral;
extern int cNeutral;
extern int progress;
extern unsigned char extraArmor;
extern int shopGachaItemCnt;

//ë©”ë‰´ê´€??ë³€??
extern signed char yesNo;
extern signed char menuDepth;
extern signed char rewardDepth;
extern signed char gachaDepth;
extern signed char newCardDepth;
extern signed char newCollectionDepth;
extern signed char stageInfoDepth;
extern signed int curMenu;//?€?´í?ë©”ë‰´, ê²Œì„ë©”ë‰´??ë©”ì¸ê°?
extern signed int curHouse;//?„ì¬ ? íƒ?˜ì–´ ?ˆëŠ” ì§?
extern signed int curHero;//?„ì¬ ?ˆì–´ë¡?
extern signed int curMenuBack;
extern signed int curEventIdx;//?„ì¬ ?´ë²¤??
extern int menuFrame;//ë©”ë‰´ ?„ë ˆ??
extern int menuTalkFrame;//ë©”ë‰´ ?„ë ˆ??ë³´ì¡°
extern int menuWinFrame;//ë©”ë‰´ ?ˆë„???„ë ˆ??
extern int menuPage, menuPage2;//ë©”ë‰´?˜ì´ì§€
extern int menuCur;	//?„ì•„?˜ë¡œ ?˜ê¸°??ë©”ë‰´?ì„œ ?¬ìš©
extern int menuX, menuY;//x, yë¡??´ë™?˜ëŠ” ë©”ë‰´?ì„œ ?¬ìš©
extern int menuResult;
extern int hotKeyFrame;
extern int menuAni;
extern int winAniFrame;
extern int winUpgradeFrame;
extern int rewardFrame;
extern int gachaFrame;
extern int newCardFrame;
extern int newCollectionFrame;
extern int stageInfoFrame;
extern int gachaIndex;//?„ì¬ ë½‘ê³  ?ˆëŠ” ?ì???¸ë±??
extern int gachaCardIdx;
extern int stageRewardIdx;
extern int helpPage;
extern int helpScene;
extern int helpFrame;
extern unsigned char enchantResult;
extern unsigned char shopType;

extern int menuIdx, menuIdx2;	//ë§??ë‹¨ ?˜ì´ì§€
extern int menuFocus, menuFocus2;	//?„ì¬ ?´ë””??
extern int menuInfo, menuWindow;	//?•ë³´ì°½ì„ ?„ìš¸ ê²½ìš°
extern int menuMessage;//?‘ì? ì°?0?´ë©´ off
extern int menuItem, menuItem2, menuItem3, menuItem4;
extern int menuCount;
extern int menuType;
extern int menuCountCursor;	//?ì ?ì„œ ?¬ê³  ?”ë•Œ ê°?ˆ˜ ?•í•˜?”ê±°
extern int menuItemCount;	//?ì ?ì„œ ?œì‹œ?˜ëŠ” ê°?ˆ˜
extern int menuIcon;
extern signed short invenRecipe[TOTALINVENTORY];	//?¸ë²¤? ë¦¬???ˆì‹œ??
extern signed short invenRecipeCnt;	//?¸ë²¤? ë¦¬??ì´?ëª‡ê°œê°€ ?ˆëŠ”ì§€
extern int enchantSlot[INVEN_HCNT];
extern int enchatSlotCnt;
extern signed short invenGemCnt;

//?¤í¬ë¡?ê´€??ë³€??
//scS, scE, scT, scC, scP (?¸ë²¤? ë¦¬)
//scS2, scE2, scT2, scC2, scP2 (?¸ë²¤? ë¦¬)

//?¤í¬ë¡¤ì´ ?„ìš”??ë©”ë‰´

extern signed int scS[TOTAL_MENU];
extern signed int scE[TOTAL_MENU];
extern signed int scT[TOTAL_MENU];
extern signed int scC[TOTAL_MENU];
extern signed int scP[TOTAL_MENU];

extern signed int isS, isT, isE, isC;
//scY??ì¶”ê? ?ê?ì§€???˜ë‚˜??
extern signed int scX, scY[TOTAL_MENU], snapTargetY[TOTAL_MENU];//x, y ?¤í¬ë¡?
extern signed int scY_Log, scT_Log;

extern unsigned char scDir;//0?´ë©´ ?¤í¬ë¡¤ì´ ?†ëŠ”ê±°ê³ , 1?´ë©´ ?˜í‰, 2ëª??˜ì§?´ë‹¤.
extern signed short scRecoveryFrameX, scRecoveryFrameY, scAccelY;//ë³µêµ¬
extern int autoScroll;//?ë™?¼ë¡œ ?¤í¬ë¡¤ì„ ?œí‚¬ê±´ì?
extern int autoScrollGap;//?´ë‹¹ ?„ë ˆ?„ì— ì§„í–‰???¤í¬ë¡??¬ê¸°

extern bool keyCoreDisable;
extern unsigned char vibLevel;
extern unsigned char stoneWhere;
extern unsigned short charInfoPage;

extern int INVEN_VCNT;//?¸ë²¤? ë¦¬ ?¸ë¡œ ëª‡ê°œ?¸ê?
extern int INVEN_TCNT;
extern int GNBHEIGHT;//?”ê±°??
extern int BOTTOMMENUHEIGHT;
extern int NORCH_HEIGHT;
extern int HOMEBAR_HEIGHT;

extern REPORTVAR rpVar;
extern REPORTVAR2 rpVar2;
extern signed char *rpPtr;

//?¬ê¸°??& ?ˆì´??ê´€??ë³€??
extern unsigned char startFrame;	//ê²Œì„?ì²´ê°€ ë¡œë“œê°€ ?˜ì„œ ?œì‘?????°ëŠ” ?„ë ˆ??
extern unsigned char startPageCur;	//?„ì¬ ëª‡ë²ˆì§??˜ì´ì§€ë¥?ê°€ë¥´í‚¤ê³??ˆëŠ”ì§€
extern unsigned char startPageMax;	//ìµœë? ë³´ì—¬ì¤˜ì•¼ ?˜ëŠ” ?¤í????˜ì´ì§€?¤ì´ ëª‡ì¥?¸ì? ë³´ì—¬ì£¼ëŠ” ?„ë ˆ??
extern unsigned char startPage[MAXSTARTPAGE];

extern unsigned char arenaFrame;	//?¬ê¸°???œì‘, ?•ì? ?„ë ˆ??
extern unsigned char arenaFloorTime;	//?¤ë¦¬ ?´ë¦¬???œê°„
extern int arenaLimitTime;	//?¬ê¸°???¨ì? ?œê°„
extern long arenaTotalTime;	//?¬ê¸°???€??(?„ì¬ 1800ì´?30ë¶?ë¡??¤ì •?? ë³€ê²½ì‹œ ArenaResult ?Œìš”?œê°„ ?˜ì •?´ì•¼??
extern unsigned char arenaNpcCnt;
extern unsigned char arenaResultMember[2];
extern int arenaGold;
extern int arenaMedal;
extern int arenaSoldier;
extern int arenaIron;
extern int arenaGoldForGetItem;
extern unsigned short oldMap;
extern unsigned short oldX, oldY;
extern unsigned char oldO2;

extern int raidInfo[TOTALRAIDSELECTED * RAIDARRAYDATASIZE];//?´ë–¤ ë³´ìŠ¤ë¥??´ë³´?´ê³ , ?´ë–¤ ë³´ìƒ??ì¤„ì? ê²°ì •(ë³´ìƒ?€ ?€?? ?”í…Œ?? ?±ê¸‰ ?¸ê?ì§€ë¡?ê²°ì •)


extern unsigned short arenaFloor;//?„ì¬ ëª‡ì¸µ?¸ì?(ì§€??ì¸µë???~)
extern signed short arenaScore;
extern unsigned short arenaKill;	//??ì£½ì¸ ê°?ˆ˜
extern signed short arenaItemFrame;	//?„ì¬ ?¨ì? ?„ë ˆ??
extern signed short arenaDebuf[TOTALDEBUF];	//?¬ê¸°???¤ì–´ê°€ê¸°ì „ ?íƒœ?€??
extern unsigned char arenaRewardType, arenaRewardLv, arenaRewardDetail, arenaRewardGrade, arenaRewardCnt;	//ë³´ìƒ ?„ì´ì½˜ì„ ê·¸ë ¤ì£¼ê¸° ?„í•œ ?°ì´??
extern unsigned char arenaStatus;//0?´ë©´ ?œì‘?? 1?´ë©´ ?„íˆ¬ì¤? 2ë©??´ë¦¬??

extern long long int dmg[MAXPLAYER];//?„ì¬ ?Œë ˆ?´ì–´??? íƒˆ?°ë?ì§€ë¥??…ë ¥?˜ëŠ” ê³?
extern long long int dmgOrder[MAXPLAYER];//ê·¸ì— ?°ë¥¸ ?œìœ„

extern unsigned short arenaMotion[MAXPLAYER];

extern long long int arenaItemPrice[MAXARENAITEM];//?„ì¬ ?„ë ˆ??ë³´ìƒ ?„ì´?œì˜ ê°€ê²©ì„ ?‰ê???ê²?
extern long long int arenaItemOrder[MAXARENAITEM];//ê°€ê²©ì— ?°ë¥¸ ?œì„œë¥?ì¡°ì •??ê²?
extern unsigned short arenaItemEffectFrame[MAXARENAITEM];//?„ì¬ ?„ì´?œì„ ë³´ì—¬ì£¼ê¸° ?„í•œ ?„ë ˆ??

extern unsigned short startItemIdx;
extern unsigned short totalItemCnt;
extern unsigned short totalItemFrame;

extern unsigned short arenaDeadCount;
extern unsigned short arenaItemCount;
extern unsigned short arenaHitCount;

//0 ? ë“¤ ?±ì¥
//1 ?œìœ„ ?•ê? ?±ì¥
//2 1??ìºë¦­??ì¦ê±°?Œí•˜??ëª¨ìŠµ
//3 1??ìºë¦­?°ì—ê²??„ì´???„ë‹¬
//4 1??ìºë¦­???„ì´??ë°›ê³  ì¦ê±°?Œí•˜??ëª¨ìŠµ
//5 2??ìºë¦­?°ì—ê²??„ì´???„ë‹¬
//6 3??ìºë¦­?°ì—ê²??„ì´???„ë‹¬
//7 4??ìºë¦­?°ì—ê²??„ì´???„ë‹¬
//8 5??ìºë¦­?°ì—ê²??„ì´???„ë‹¬
//9 6??ìºë¦­?°ì—ê²??„ì´???„ë‹¬
//10 7??ìºë¦­?°ì—ê²??„ì´???„ë‹¬
//11 8??ìºë¦­?°ì—ê²??„ì´???„ë‹¬
//12 9??ìºë¦­?°ì—ê²??„ì´???„ë‹¬
//13 10??ìºë¦­?°ì—ê²??„ì´???„ë‹¬
//14 ? ì? ë³´ìƒ ë°•ê¸°
//15 ?„ì´??ë¦¬ìŠ¤??ë°•ê¸°

extern unsigned char playResultStatus; 
extern unsigned char raidPlayer;

extern unsigned char skillSlot[RAIDSKILLSLOT];


//ê¸¸ë“œ??ê´€??ë³€??
extern unsigned char guildTimeStr[20];	//?¨ì??œê°„ ?œì‹œ ë³€??
extern unsigned int guildTotalScore;	//ê¸¸ë“œ???„ì  ?ìˆ˜
extern int curTime;
extern signed int rankRecord[16];	//ê·¸ë˜???œì‹œ??ê²??€?¥ë???
extern signed int rankWeek;		//ëª‡ì£¼ì°??¸ì?
extern char rankScore[4][15];	//?ìˆ˜ ?€??ë³€??|ê¸¸ë“œ?„í˜„??>?„ì¬ê¸¸ë“œ?„ìŠ¤ì½”ì–´
extern unsigned char guildCur;		//ê·¸ë˜?„ì—??ì»¤ì„œ?´ë™???¬ìš©
extern signed char guildWinner;
extern unsigned char guildReward[5];		//0 : type, 1:lv, 2:detail, 3:grade, 4:count, 5:ì²«ë²ˆì§¸ë³´?ê³¨?œê¸ˆ??1ì²œë‹¨??
extern int goldReward;
extern unsigned char guildRewardReceive;

extern int goldEffectFrame;
extern int medalEffectFrame;
extern int coinEffectFrame;

extern int gachaSupporterGrade;
extern int gachaSupporterIdx;

extern int temp;
extern int tempHint;

extern unsigned char netLock;
//ë³µì œë°©ì?
extern char phoneMatch;
extern char isScreenShot;

extern char isDragging;//?”ë©´??ë¬´ì–¸ê°€ê°€ ?„ë¥´ê³??ˆë‹¤??ë³€???œë˜ê¹…ì¤‘?´ë¼?”ê²ƒ)
extern int pointed;//?„ë¥¸ê³³ì´ ?´ë–¤ ?ì—­?¸ê????´ë‹¹?˜ëŠ” ë³€??

extern unsigned char saveFlag[3];//0:SaveGame, 1:SaveOption, 2:SaveEtc
extern unsigned char soundLoad;

extern unsigned char toolTip;
extern unsigned char gameMenuPop;
extern unsigned char gameMenuDepth;

//#include "automata.h"

//cocos2d::experimental::ui::WebView *_webView;

#ifdef MEMORYTEST
extern int tempMemory;
extern int temp1;
extern int temp2;
extern int temp3;
extern int temp4;
extern int temp5;
extern int temp6;
extern int temp7;
extern int temp8;
extern int temp9;
extern int temp10;
extern int freeMemory;

extern int dMoveCnt;
extern M_Uint32 *dMove;
#endif

#ifdef DEBUG
extern int demoSkip;
extern int debug, g_bDebugDetail, g_bDebugType;
extern M_Int64 g_lOldTime, g_lCurTime, g_lResultTime;
extern int tempValue, tempGrade, tempEnemy;
extern int g_nTestCnt1, g_nTestCnt2, g_nTestCnt3, g_nTestCnt4, g_nTestCnt5, g_nTestCnt6, g_nTestCnt7, g_nTestCnt8, g_nTestCnt9, g_nTestCnt10;
extern int g_nTestAvg1, g_nTestAvg2, g_nTestAvg3, g_nTestAvg4, g_nTestAvg5, g_nTestAvg6, g_nTestAvg7, g_nTestAvg8, g_nTestAvg9, g_nTestAvg10;
extern unsigned long p[15], e[15];
extern char debugStr[256];
extern int tempMemory;
extern int freeMemory;
#endif

#ifdef EXPVERSION
extern M_Boolean yesno_Draw;
extern M_Boolean buy_Confirm;
#endif

//ì¶”ê????¬ê¸°??ê´€??ë³€??
extern unsigned short caveMap;			//?„ì¬ ?´ë”” ?¬ê¸°?¥ì¸ì§€.
extern unsigned short caveEnemyAlive[159 * 2];

extern unsigned short caveCountEmy;
extern unsigned short caveCountEmy2;
extern unsigned short caveKill;		//?¬ê¸°??ëª¬ìŠ¤???´ì¹˜??(? ê·œ ?¬ê¸°?¥ì? ëª¬ìŠ¤?°ë? ëª¨ë‘ ?¡ìœ¼ë©??ë‚¨)
extern unsigned short caveItemType;
extern unsigned short caveItemText;
extern unsigned short caveItemDetail;
extern unsigned short caveItemCnt;
extern unsigned short caveItemGrade;
extern unsigned char caveMapData;

extern unsigned char cave1TotalEmy[15];//75
extern unsigned char cave2TotalEmy[18];//66
extern unsigned char cave3TotalEmy[30];//159
extern unsigned char cave4TotalEmy[28];//117
//433//5
//436//5
//439//5
//459//5
//488//7
//493//7
extern unsigned short caveItemPer[4][16];

extern unsigned char caveItemAcc[24];


//?¤ë¹„?œìŠ¤ ?ë£¨	: ë¯¸ë˜??ê±°ìš¸ / 9
//?¸ì´?Œì˜ ?¼ë¦¬	: ?©ì???œê³„ / 25
//?©í˜¼???±ë°°	: ë©”í”¼?¤í†  ?¼ë¦¬ / 5
//ë¡œì ¤ë¦°ì˜ ê½?: ?œìŸ?´ì˜ ê³?/ 20

//?¬ì•™??ê±°ìš¸	: ë¯¸ë˜??ê±°ìš¸ / 9
//?ì›…???œì‚¬??: ?©ì???œê³„ / 25
//? ë‹ˆì½˜ì˜ ë¿?: ë©”í”¼?¤í†  ?¼ë¦¬ / 5
//?©ê¸ˆ ì¡°ê°œ		: ?œìŸ?´ì˜ ê³?/ 20

//ì²œì‚¬??? ê°œ	: ë¯¸ë˜??ê±°ìš¸ / 9
//ê¸ˆë‹¨??ê³¼ì‹¤	: ?©ì???œê³„ / 25
//ì£½ìŒ???¬ê?ë¯?: ë©”í”¼?¤í†  ?¼ë¦¬ / 5
//ì¡°ê°???í˜¼	: ?œìŸ?´ì˜ ê³?/ 20
//
//ì¶©ì„±??ë°˜ì?	: ?¹ì??ë°˜ì? / 13
//?©ì œ??ë°˜ì?	: ê¶ê·¹??ë°˜ì? / 14
//?ˆë? ë°˜ì?		: ??£¼??ë°˜ì? / 7
//?ˆë²¨ë£½ê² ë°˜ì?	: ? ë…??ë°˜ì? / 11

//?€?˜ìˆ˜ ë°˜ì?	: ?¹ì??ë°˜ì? / 13
//?½ì†??ë°˜ì?	: ê¶ê·¹??ë°˜ì? / 14
//?”ì •??ë°˜ì?	: ??£¼??ë°˜ì? / 7
//?¡ë§ˆ ë°˜ì?		: ? ë…??ë°˜ì? / 11

//ë²ˆë‡Œ??ë°˜ì?	: ?¹ì??ë°˜ì? / 13
//ë¶ˆì‚¬??ë°˜ì?	: ê¶ê·¹??ë°˜ì? / 14
//?©ê¸ˆ ë°˜ì?		: ??£¼??ë°˜ì? / 7
//ë´‰ì¸??ë°˜ì?	: ? ë…??ë°˜ì? / 11
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
extern experimental::ui::WebView       *_webView;
#endif



extern int adX; //ê´‘ê³ ??x?¬ì???
extern int adY; //ê´‘ê³ ??y?¬ì???
extern int adFrame;//ê´‘ê³ ???„ë ˆ??
extern int adType;//ê´‘ê³ ???€??
extern int adProfile;//ê´‘ê³ ???„ë¡œ???¬ì§„
extern int adHero;

extern int tipIndex;

extern int mapSeenCount;
extern int mapSeenCountHelp;

extern int boxOpenFrame;
extern unsigned char voiceType;

extern cocos2d::Scene * curScene;

extern int wholeFrame;

extern bool screenBuffer;
extern bool doubleBuffer;

extern signed short robinmap;
extern signed short playmap;
extern signed short dioramaType;//?„ì¬ ?”ì˜¤?¼ë§ˆ


//CCLabelTTF * textLabel;

extern bool onceAnnounced;
extern int profileImg[MAXPLAYER];
extern unsigned char playerHeadZoom;//ALLHEADZOOM;//PLAYERHEADZOOM;// false;//
extern bool effectOnlyPlayer;//EFFECT_ONLY_PLAYER
extern bool focusOnPlayer;//FOCUSONPLAYER
extern bool onlyPlayerDmgNumBig;//ONLYPLAYERDMGNUMBIG
extern int skillSelectTime;
extern int macroTimes;

extern Mat4 parentTransform;
extern Renderer * renderer;

extern std::random_device rd;

extern int touchIdleFrame;
extern int idleHelpCnt;
extern int idleHelpType;//?´ë™???œí‚¬ì§€, ê³µê²©???˜ë¼ê³?? ì?
extern int idleHelpObj;

extern int MINDY;
extern int EQUIP_WIN_HEIGHT;

#ifdef DEVELOPMENT
extern int DEBUG_STAR;
#else
extern int TOTAL_OPENED_TIER;
extern int DEBUG_STAR;
#endif

extern bool tutorialMode;
extern int tutorialStep;

extern int floatingMessage;

extern bool playClear;

extern ITEM gachaItem[MAXGACHAITEM];

extern int miniGacha;
extern int miniGachaCnt;
extern int miniGachaIcon;
extern int miniGachaType;
extern int miniGachaTypeFrom;
extern int miniGachaTypeTo;
extern int miniGachaDetail;
extern int miniGachaDetailFrom;
extern int miniGachaDetailTo;
extern int miniGachaGrade;
extern int miniGachaGradeFrom;
extern int miniGachaGradeTo;
extern int miniGachaFloor;

extern int HEARTTIME;
extern int FREEITEMTIME;
extern int realPlayerCnt;

extern bool textInput;

extern unsigned short gachaIcon[5];
extern unsigned char gachaGrade[5];

extern int SOLDIERSALE;

extern int curLabMain;
extern int curLabSub;

extern int GNB_GAP;

extern int outline;
#ifdef ONESKILLTEST
extern int oneSkillTest;
#endif

extern float VOLUME_BGM;
extern float VOLUME_SE;
extern float VOLUME_BGM_MUTE;

extern int ironFrame;
extern int medalFrame;
extern int heartFrame;
extern int goldFrame;
extern int starFrame;
extern int hammerFrame;
extern int shieldFrame;

extern int goldCount;
extern int goldCountFrame;
extern int joyStickFrame;
extern int joyStickAni;
extern int joyStickDir;

extern int raidChance;//ì²˜ìŒ??5ë²ˆì„ ì£¼ê³  ?œë²ˆ ?¸ìš¸?Œë§ˆ??

extern int dmgIndex;
extern int subDmgIndex;

extern long currentTimeStamp;

extern int remainedTurn;
extern int remainedTurnFrame;//
//NEUTRAL	ê°€ë§Œíˆ ?ˆì„ ??
//PLAYER	ì£¼ì¸ê³µì´ ê³µê²©??
//ENEMY		?ì—ê²?ê³µê²©??
//ê³µê²©??
extern int turn;
extern int turnFrame;
extern int turnPosition;

extern int rouletteSequence;
extern int curRouletteStart;//ëª‡ë²ˆì§?ë¶€???œì‘?˜ëŠ”ê±´ì?
extern int totalRouletteCnt;//ìµœì¢…?ìœ¼ë¡??˜ì????˜ëŠ” ë£°ë ›ê°œìˆ˜//?„ì¬ ?„ì— ?¬ë¼ê°€ ?ˆëŠ” ë£°ë › ê°œìˆ˜

//ê³µê²©?°ì¶œê´€??
extern int attackSequence;//
extern int attackSequenceBack;
extern int attackType;//
extern int actionCardIdx;
extern int attackStr;//
extern int attackStartIdx;
extern int questRewardType;
extern int attackAttr;
extern int boxDropItemType;

extern int attackSequenceBefore;

//?¬ê¸°?œë????„ì¬ ë£°ë ›???´ë–¤ê²??˜ì™”?”ì? ?°ì´?? ???°ì´?°ë? ê¸°ë°˜?¼ë¡œ ?´ë–¤ê²ƒì„ ?´ë³´?´ëŠ”ì§€ ?•í•œ??
//extern unsigned char roulette
extern int actionCardArr[TOTALCONTROLMARK];
extern int actionCardCnt;

extern int curtainFrame;

extern int subAttackType;//ì¶”ê??€?¼ë˜ê°€ ?´ëŸ°ê²ƒë“¤
extern int subAttackStr;
extern int subAttackIcon;
//?„ì¬ ì¹´ë“œë©”ë‰´ê°€ ?·ë©´???¸ì¶œ?˜ì—ˆ?”ì?
extern char cardMenuBack[TOTALEQUIP];
//+ë©??«íˆ???íƒœë¡?1??ë¹¼ì£¼ë©´ì„œ 0?¼ë¡œ ê°„ë‹¤.
//-ë©??´ë¦¬???íƒœë¡?1???”í•´ì£¼ë©´??0?¼ë¡œ ê°„ë‹¤.

extern int totalProb;
extern int probSum[TOTALJOKBO];

extern int totalBattleProb;
extern int battleProbSum[TOTALBATTLEJOKBO];

extern int totalBossRaidProb;
extern int bossRaidProbSum[TOTALBOSSRAIDJOKBO];

extern int totalQuestRequestItemCnt;
extern unsigned int questRequestItemCnt[TOTALQUESTREQUEST * TOTALSUBQUEST];

extern int startX, startY, targetX, targetY, targetX2, targetY2;

extern long long rouletteNum;
extern long long rouletteNumSub;
extern long long rouletteNumBar;
extern long long rouletteNumPvpBar;

extern long long rouletteNum_before;

extern int debugAttack;

extern ITEM rewardItem[MAXREWARDITEM];//ë©”ì¸ ë¦¬ì›Œ???„ì´??
extern ITEM rewardItemBack[MAXREWARDITEM];//ë°±ì—…
extern int rewardItemCnt;//?„ì¬ ?ë“???„ì´??
extern int curRewardItem;//?„ì¬ ?ë“ì§„í–‰ì¤‘ì— ?ˆëŠ” ?„ì´??
extern int focusedItem;//ë©”ì¸ë¦¬ìŠ¤?¸ì—??
extern int focusedSubItem;//?œë¸Œë¦¬ìŠ¤??
extern bool newItem;

extern int boxCnt;//? íƒˆ ë°•ìŠ¤ ì¹´ìš´??
extern int newCollectionCnt;//?´ë²ˆ???ˆë¡œ??ì»¬ë ‰?˜ì´ ?„ì„±??ì¹´ìš´??
extern int newCardCnt;//?ˆë¡œ??ì¹´ë“œ ì¹´ìš´??
extern int curBox;

extern ITEM boxCardItem[TOTALBOXMARK][MAXCARDREWARDITEM];
extern int boxCardItemCnt[TOTALBOXMARK];

extern int rewardIndex;
extern int pvpRewardIndex;

extern int newItemCnt;
extern int newItemIdx[MAXBOXREWARDITEM];
extern int newItemType[MAXBOXREWARDITEM];
extern int newItemDetail[MAXBOXREWARDITEM];
extern int newItemGrade[MAXBOXREWARDITEM];


extern int curNewItemIdx;

extern int curRewardBoxIdx;

extern bool ONLYATTACKMODE;


extern int ROULETTEINTERVAL;

extern int ROULETTEWHEELTIME;

extern int ROULETTESPREADTIME;
extern int ROULETTESELECTTIME;

extern int TOTAL_OPENEDMENU;


//?ë??„ì¹˜

#ifdef MYKING
extern int DRAWROULETTENUMGAP;
extern int DRAWROULETTENUMGAP_SUB;
extern int QUESTBARYGAP;
extern int DRAWROULETTENUMGAP_RAID;
#else
extern int DRAWROULETTENUMGAP;// 192 * _2X - 8 * _2X;
extern int DRAWROULETTENUMGAP_SUB;
extern int QUESTBARYGAP;
extern int DRAWROULETTENUMGAP_RAID;
extern int DRAWRAIDNUMGAP;
extern int RAIDUSERPROFILEGAP;
extern int HPBARGAP;
extern int BAR_UPPERMENUGAP;
extern int BAR_BOTTOMMENUGAP;
extern int BOXPOSITION_Y;//160 * _2X;//300 * _2X;//408 * _2X;//

extern int BOXITEM_Y;
#endif

extern int STAGELABELGAP;

extern int DRAWROULETTENUMGAP_BATTLE;
extern int DRAWROULETTENUMGAP_ALPHA;

extern int ENEMYUSERINFOGAP;
extern int STAGEBOSSINFOGAP;
extern int ENEMYHPBARYGAP;

extern int HITPOSITIONGAP;
extern int HITPOSITIONGAP2;

extern int JOKBOGAP_INIT;
extern int JOKBOGAP;
extern int HEARTBARGAP;
#ifdef MYKING
extern int CARDPOSITIONGAP;
#else
extern int CARDPOSITIONGAP;
#endif

extern int HITPOSITION_CREW;
extern int HITPOSITION_HITSTART;
extern int HITPOSITION_HITMODE;

extern int PLAYINFO_GAP;

extern POPUP popUp[MAXPOPUP];

extern int arr[2];

extern int newCollectionIdx[MAXNEWCOLLECTIONLIST];
extern int curNewCollection;

extern int initControlerFrame;
extern int crewInitializeFrame;

extern GAMEEVENT gameEventArr[MAXGAMEEVENT];

extern int pvpRewardPosition[3][2];

extern int joyStick;

extern int curStar, curMaxStar, maxStar;

extern int totalHouse;
extern int popUpCnt;


extern int points[MAX_POINTS][2]; // ì¢Œí‘œë¥??€?¥í•  ë°°ì—´ (x, y ê°ê°??1ì°¨ì› ë°°ì—´ë¡??€??
extern int boxPoints[MAX_POINTS][2];

extern int selectedCrew;

extern bool rouletteOpen[SKILLPERSWORD];
extern bool loadRoulette;
extern int newCollection;

extern int attackedCrewIdx;//ê³µê²©?¹í•œ ?¸ë±??
extern int bossGetCoinCrewIdx;//ë³´ìŠ¤?ê²Œ ?„ì???ì¤€ ?¸ë±??

//?¤í…Œ?´ì??ì„œ ë¹šê°š?„ì£¼ë©?? ë‹ˆë©”ì´???˜ëŠ”ê±?
extern int stageUpgradeMotion[MAXCREW];

extern int bossRaidMode;//ê·¸ëƒ¥ ?¼ë°˜ë³´ìŠ¤??bossRoom?€ true?´ê³ ,	ë³´ìŠ¤?ˆì´?œëŠ” ??ë³€?˜ë? ?´ë‹¤. 

extern int subQuestCnt[TOTALQUEST];

extern GAMEEVENT * gEvent;

extern int swordSkillCnt[TOTAL_COLLECTIONS];//ê²€ë³??¤í‚¬ ê°œìˆ˜
extern int swordSkillProb[TOTAL_COLLECTIONS * SKILLPERSWORD];//ì»¬ë ‰???•ë¥  

//?¬ê¸°???œë²„ë¡œë???ë¡œë”©???¤ëŠ” ê²ƒì¸???¼ë‹¨ ë¡œì»¬???€?¥í•œê±?ë¶ˆëŸ¬?¤ëŠ” ?•ì‹?¼ë¡œ ?˜ì.
extern HOUSE enemyHouse;
extern HOUSE stageHouse;//
//?„ì‹œ?œë²„?°ì´??
extern HOUSE aiUserHouse[TOTALAI];//?œë²„ êµì‹ ???†ëŠ” ?íƒœ?ì„œ??AI
extern HOUSE * selectedHouse;//?„ì¬ ? íƒ???˜ìš°??
extern HOUSE tempHouse;

extern int curCardMark;
extern int currencyMarkCnt;


extern int wheelSpeed;
extern int wheelAngle;
extern int wheelAccel;
extern int wheelFrame;
extern int wheelMaxSpeed;
extern int arrowTouched;
extern int WHEELMAXSPEED;
extern int WHEELINITSPEED;
extern int WHEELINITACCEL;

//ë°°í???ê±¸ë ¸?????•ë³´
extern int battleTarget;//?„ì¬ ?ì˜ crew ?¸ë±?¤ë¡œ null?´ê±°???„ë‹ˆê±°ë‚˜ ?ê??†ì´ ? íƒ??crew[i]??ië¥??˜ë??œë‹¤.
extern bool battleShield;
extern long long battleGold;

extern int raidTarget;
extern long long raidGold;
extern int raidAttack;

extern OBJECT raidBox[TOTALRAIDBOX];

extern int bet;
extern int betBattle;

extern int rouletteArr[SKILLPERSWORD];

extern int tabMenuFrame[TOTALEQUIP];
extern int maxRouletteCnt;

extern float boxDropPercent[TOTAL_BOX][TOTAL_BOXDROP];


extern int XNUMGAP;
extern int YNUMGAP;

extern int nearestIndex;

extern int curMaxCrew;

extern int slotFrame;
extern int turnListIdx;
extern int enemyTurnStartIdx;
extern int totalTurn;
extern int turnList[PLAYERALL + MAXWAVEENEMY];
extern int slotCrew[MAXCREW];
extern int crewIdList[MAXCREW];
extern int crewCnt;
extern int heroCnt;
extern int showCrewCnt; // ë¡œë”© ?”ë©´?ì„œ ?„ì¬ê¹Œì? "ê³µê°œ/?©ë¥˜ ?°ì¶œë¡?ë³´ì—¬ì¤? ?¬ë£¨ ??0..crewCnt)
extern int showHeroCnt;

extern int leaderCrewId;   // 0..TOTAL_CREW-1 or -1
extern bool hasLeader;

// ì¤‘ì•™ ì¹´ë“œ???œì‹œ???„ì¬ ê³µê°œ ìºë¦­??robin.slotCrew[showCrewCnt]ë¥?ê¸°ë°˜?¼ë¡œ)
extern int cardCmf;
extern int cardAlpha;

// 1) ?€ê²?ê²°ê³¼ (?ˆì‹œ) : aoOffset(0~8)ë¡?ë°›ëŠ”?¤ê³  ê°€??
extern int  gRouletteStartAoOffset[TOTALREEL];
extern int  gRouletteResultAoOffset[TOTALREEL];  // ìµœì¢… ?•ì • 3ëª?(aoOffset)
extern int gRouletteSkillIdx[TOTALREEL];
extern int rouletteFrame;
// 3ê°????•ì • ??"??ë²ˆë§Œ" ?©ì„±/?´ë™ ?°ì¶œ ?¸ë¦¬ê±?
extern bool gRouletteSkillDispatchStarted ;

extern bool gRouletteResultValid;

extern int blState;
extern int blStateFrame;
extern int blFrame;

extern int finishOffsetX;

extern int bgScrollX;
extern int bgScrollY;

// ===== ?Œí™˜ ?°ì¶œ =====
extern int summonCrewId;
extern int summonCmf;
extern int summonFromX, summonFromY;
extern int summonX, summonY;
extern int summonToX, summonToY;
extern int summonMidX, summonMidY;
extern float summonScale;
extern int summonHold;          // ?¼í„° ë°•íˆ???€???„ë ˆ??ì¹´ìš´???µì…˜)
extern int summonStar;          // ?„ì¬ ?Œí™˜ ?¬ë£¨??ë³„ë“±ê¸?1~9)
extern int celebFlash;          // ì¶•í•˜ ?Œë˜??0?´ë©´ ?†ìŒ)
extern int shake;               // ?”ë©´ ?”ë“¤ë¦?ê°•ë„(0?´ë©´ ?†ìŒ)
extern int joinFromX;
extern int joinFromY;

extern bool needPickSummonFromBg;
extern bool pickedSummonFromBg;
extern bool hideSummonBgTile;
extern int  hideBgCmf;
extern int summonType;

// ë¡œë”©ë°?ì§„í–‰ë¥??œë“±???¨ê³„??ê¸°ë°˜)
extern int loadPct;

// ---------- pity ?íƒœ ----------
extern int gNoHighStarCount; // STAR7+ ???˜ì˜¨ ?°ì† ?Ÿìˆ˜

// ---------- ?Œí”„??ë¶„ì‚° ?íƒœ ----------
extern int gRecentRegionCount[TOTALCASTLE]; // ìµœê·¼ ?±ì¥ ?Ÿìˆ˜
extern int gRecentStarCount[10];            // STAR ?°ì† ?¨ë„??

// ================================
// ê²Œì„ ?íƒœ ?„ì—­ ë³€??? ì–¸ (extern)
// ?¤ì œ ?•ì˜??GameState.cpp???ˆìŒ
// ================================

// ?„íˆ¬ ê´€??
extern int attackDelayBefore;
extern int attackTypeBefore;
extern int attackStrBefore;
extern int rewardItemCntBefore;
extern int maxHitCnt;
extern int sequenceFrame;
extern int raidFrame;
extern int continuousAttackFrame;
extern int raidCnt;

// ?ë™ ?Œë ˆ??
extern bool autoPlay;
extern bool autoSelect;
extern bool autoSkill;
extern int autoFrame;
extern bool autoButtonText;

// ?”ë©´
extern float screenZoom;
extern float dioramaZoom;
extern float dioramaZoomGap;
extern float battleZoom;
extern int screenDarken;

// ê²Œì„ ?íƒœ
extern int waveStatus;
extern int levelUpFrame;
extern int levelUpStatus;
extern int maxUserLv;
extern bool bossOn;
extern int touchDisable;


extern int floatOffsetY;


extern int openingScene;
extern int openingText;
extern int openingWaitFrame;
extern int openingState;
extern int openingPrevTextPage;
extern int openingTextPage;
extern bool openingSceneWait;

extern float joyStartX;
extern float joyStartY;
extern float joyDx;
extern float joyDy;
extern float joyPower;
extern int joyDir;
extern bool joyPressed;
extern bool joyReturning;
extern float joyReturnSpeed; // ³ôÀ»¼ö·Ï ºü¸£°Ô º¹±Í
#endif
