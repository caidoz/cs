#pragma once

#ifndef _CORE_H_
#define _CORE_H_

// ✅ ===== 1단계: Windows 헤더 (가장 먼저) =====
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
// WinSock2를 사용하는 코드가 있으므로 올바른 순서로 포함
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
#endif

// ===== 3단계: cocos2d (기본 라이브러리) =====
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

//Shader 관련

// Shader 문자열 - extern 선언
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
	int x, y, w, h;//버튼의 위치 크기 정보
	float zoom;//버튼의 
} BUTTON;

typedef struct _popUp {
	bool active;
	int type;
	int x, y, w, h;

	int itemType;//팝업에 등장하는 타입
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
	signed short frame;    //핫키로 장착된 스킬을 쓸수 있을때
	signed short inven;
	signed char idx;    //스킬일 경우는 스킬인덱스, 아이템일 경우에는 주인공 인벤토리내의 인덱스, 상이면 상종류, 반지면 반지의 종류
	signed char type;    //0이면 할당된게 없음, 1이면 스킬, 2이면 아이템, 3이면 상, 4면 반지
	bool random;//true 면 돌리고 있는거고 false 면 확정
	signed short randomFrame;//랜덤한 값이 결정될 때까지 
	signed char randomCnt;//돌리는 카운트
} HOTKEY;

typedef struct _item {
	long long id;
	int value;    //대표값(무기-공격력, 방어구-방어도 등등
	int subValueType;//두번째 대표값의 종류(목걸이, 반지에 지정되는 값)
	int subValue;    //두번째 대표값(목걸이, 반지에 지정되는 값)
	unsigned short icon;        //아이콘
	unsigned int count;    //갯수(장비인 경우는 소켓의 숫자)
	unsigned int gold;    //가격
	unsigned short cooldown;    //사용효과가 있는 아이템의 쿨다운(장비의 경우 강화레벨)
	unsigned char lv;    //레벨
	unsigned char type;        //타입
	unsigned char detail;    //세부
	unsigned char grade;    //등급
	bool broken;    //파괴되었는지
	long set;    //어떤 세트인지 //스킬이 발동되면 이 set을 쓰도록 하자
	int socket[6];    //소켓
	int option[12][2];
	char name[40];
	int exp;//현재 누적된 경험치
	bool seen;//상세정보를 확인했는지

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
	int jumpFrame, attackFrame, mainFrame, frame, attackedFrame, levelUpFrame, delayFrame, statUpFrame;
	int turn;//캐릭터가 몇번째 공격을 하고 있는지 보여주는 변수
	int x, y;
	int nx, ny;//게임시작시 위치, 공격한 뒤에 다시 돌아가는 위치
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
	signed short name;	//이름
	int lv;
	unsigned short motion;
	unsigned char tileX1, tileX2, tileY1, tileY2;
	unsigned char moveHandler;
	unsigned char drawHandler;
	//signed char ipx, ipy, ix, iy;
	signed short dx, dy;
	signed char active;
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
	HOTKEY hotKey[MAXHOTKEY];//인게임에서 획득하는
	ITEM equip[TOTALEQUIP];//현재 장착된 장비는 3개 캐릭터 로빈, 디아나, 맥스별로 있다.
	unsigned char equipImg[TOTALEQUIP];
	unsigned char equipped[TOTALEQUIP];
	signed char immune[TOTALDEBUF];
	long long int stat[4];
	unsigned char continueAttack;
	unsigned char decreaseHp, minusDrain, alwaysCurse;
	unsigned char invincible;
	unsigned char hpRestore, mpRestore, statusRestore;
	unsigned char hpDrain, mpDrain;
	
	//상과 관련된 변수
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

	int house;

	std::string nickname;

	long coolTime;//적 스킬 발동시간

	float rotation;//회전각

	int hitCount;
	int hitCountFrame;
	long long hitDmg;

	bool hitCountPlus;

	int turnPosition;

} OBJECT;

typedef struct _gameEvent {
	unsigned char type;//EVENTTYPE_QUEST, EVENTTYPE_PVP, EVENTTYPE_SHOP
	unsigned char subType;//
	short icon;//아이콘 인덱스
	long timeStamp;//시작된 시간
	long limitTime;//몇시간짜리 이벤트인지

	int barFrame;
	//EVENT_OPEN
	//EVENT_DOING
	//EVENT_CLOSE
	unsigned char status;//생성, 진행중, 소멸 세가지 스테이터스
	//PVP 아이템 획득할 때처럼 바가 튀어나와서 거기로 데이터가 날라가는 경우
	//EVENT_BAR_NEW
	//EVENT_BAR_ITEMGET
	//EVENT_BAR_REWARDGET
	//EVENT_BAR_NEXT
	//EVENT_BAR_CLOSE
	unsigned char barStatus;//생성, 획득중, 보상, 넥스트바, 종료 4가지 스테이터스
	
	int x;//왼쪽 오른쪽 인덱스
	int y;//위에서 부터 몇번째 인덱스
	int dirX;
	int dirY;
	int nx;
	int ny;
	int targetX, targetY;//목적지 XY 
	int targetX2, targetY2;//목적지 XY 
	float dx, dy;//x, y축 이동거리
	float speed;//이동속도
	float speedIncrement;//이동속도 증가량
	float speed2;//이동속도2
	float speedIncrement2;//이동속도 증가량
	int waitingFrame;//시작했을 때 머무르는 프레임
	int waitingFrame2;//중간에 이동속도 체인지 했을 때 머무는 프레임
	int frame;//현재 프레임
	int frame2;//
	float zoom;
	float zoomEnd;//줌
	float zoomIncrement;
	float zoom2;
	float zoomEnd2;//줌
	float zoomIncrement2;

	int touchFunc;

	float value;

	bool front;
} GAMEEVENT;

typedef struct _bar {
	bool active;
	unsigned char type;//BAR_GOLD, BAR_STAR, BAR_HEART, BAR_QUEST, BAR_ENEMYHP

	signed long long count;//숫자(robin.gold, robin.heart...)
	signed long long add;//더해야 되는 값(획득값)
	signed long long max;//더해야 되는 값을 합산한 한턴 합산값                                                   
	
	bool addView;

	int countFrame;//카운트(더해지는 동안 올라가는 프레임)

	short icon;//아이콘 인덱스
	int iconFrame;//이 프레임에 0보다 크면 아이콘이 움직인다.

	//보상 아이콘이 표시여부
	//false 면 안보여주는거고
	//값이 있으면 1이면 그냥 보여주는 건데
	//값이 1보다 크면 보상 아이템이 확대->축소로 움직이면서 보상이 셋팅되는 것을 보여준다.
	float enemyIcon;
	float rewardIcon;
	bool bonusRewardIcon;//보너스 아이콘
	long bonusRewardTimeStamp;//보너스 타임스탬프

	int x;//x위치
	int y;//y위치

	int nx;//이동전 x위치
	int ny;//이동전 y위치

	int targetX, targetY;//목적지 XY 
	int targetX2, targetY2;//목적지 XY 
	float speed;//이동속도
	float speedIncrement;//이동속도 증가량
	float speed2;//이동속도2
	float speedIncrement2;//이동속도 증가량
	int waitingFrame;//시작했을 때 머무르는 프레임
	int waitingFrame2;//중간에 이동속도 체인지 했을 때 머무는 프레임
	int frame;//현재 프레임
	int frame2;//
	int aniFrame;

	bool front;//true면 attackSequenceDraw 같은데서 그려준다.

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

	unsigned short cmf;//누가 했냐. 보스면 cmf 가, 퀘스트면 족보 인덱스가 뜬다.
	unsigned short cmf2;//적이 우리편 npc를 털면

	unsigned short icon;//아이콘
	long long count;//숫자 정보가 필요한 경우

	int x;//x위치
	int y;//y위치

	signed char dirX, dirY;//방향
	float dx, dy;//x, y축 이동거리

	int targetX, targetY;//목적지 XY 
	int targetX2, targetY2;//목적지 XY 
	float speed;//이동속도
	float speedIncrement;//이동속도 증가량
	float speed2;//이동속도2
	float speedIncrement2;//이동속도 증가량
	int waitingFrame;//시작했을 때 머무르는 프레임
	int waitingFrame2;//중간에 이동속도 체인지 했을 때 머무는 프레임
	int frame;//현재 프레임
	int frame2;//

	float zoom;
	float zoomEnd;
	float zoomIncrement;
	float zoom2;
	float zoomEnd2;
	float zoomIncrement2;

	char text[256];
} LOG;
//전투창에서 보여줄 부분
typedef struct _battleLog {
	unsigned char type;//LOG_EVENTSTART, LOG_JOKBOOPEN, LOG_RAID, LOG_BATTLE, LOG_BOSSHEAL

	unsigned short who;//누가 했냐. 보스면 cmf 가, 퀘스트면 족보 인덱스가 뜬다.

	unsigned short icon;//아이콘
	long long count;//숫자 정보가 필요한 경우

	std::string text;
} BATTLELOG;

typedef struct _charData {
	ITEM equip[TOTALEQUIP];//캐릭터 3명에 대해서는
	HOTKEY hotKey[MAXHOTKEY];//세팅되어 있는 스킬(1개)와 소환수(1개)와 동료(1개)를 랜덤하게 돌려서 출동시킨다.
	int exps;//이게 있으면 역으로 stat은 세팅할 수 있다.
	long long int hp;
	int mp;
	unsigned short ap;
	unsigned char sp;

	signed char skillLv[TOTAL_SKILL];
	unsigned char getSkillList[MAXCHARSKILL];

	//아래계열들은 RefreshStat한번 하면 자동으로 값이 할당되거나 전투중 임시 값이므로 패스
	//signed short buff[TOTALBUFF];
	//signed int debuf[TOTALDEBUF];
	//signed char immune[TOTALDEBUF];

	template <class Archive>
	void serialize(Archive & ar)
	{
		ar(
			type,
			mapSeenCount,
			equip[TOTALEQUIP]
		);
	}
} CHARDATA;

//PVP 데이터
//일단 유저번호가 있고
typedef struct _house {
	long long idx;//집 인덱스
	long long userId;//이 집의 소유주인 서버상의 유저 아이디
	long long userProfileImgIdx;//유저프로필 이미지 인덱스
	long long userName;//유저 이름
	unsigned char equipImg[TOTALCHAR][TOTALEQUIP];//이 집 소유주의 코스튬이미지
	long long gold;//이 집 소유주의 전투시 획득할 수 있는 골드
	unsigned char houseType;//이 집 소유주의 집 인덱스
	unsigned short crew[MAXCREW];//크류의 인덱스.
	unsigned char crewMaxStar[MAXCREW];//크류의 최대 레벨
	unsigned char crewCurStar[MAXCREW];//크류의 현재 레벨
} HOUSE;

//로빈구조체는 게임 전체에 대한 저장소이다.
//
//여기는 저장되는 데이터만
typedef struct _robin {
	CHARDATA charData[TOTALPLAYER];//서버에 저장되는 로빈에 대한 데이터//차후에 상대방 유저가 
	ITEM inven[TOTALINVENTORY];//인벤토리는 공유한다.
	ITEM newItem;
	//성에서는 현재 획득한 크류들이 자유스럽게 돌아다니는 것이 아니라, 정해진 위치에 박혀서 나오는것으로 하자.
	//
	int curCrew[MAXCREW];//현재 몇번 crew가 세팅되어 있는지

	int stage;
	int room; 
	int maxStage[TOTALCASTLE];//현재 어디까지 갔는지.
	int maxRoom[TOTALCASTLE];

	bool demoSeen[TOTALDEMO];

	unsigned short count;//인벤토리안에 있는 아이템의 개수
	unsigned short maxInven;//인벤토리안에 있는 아이템의 개수

	long long gold;//골드
	long long heart;//하트
	long long medal;//PVP 전용 카운트
	long long star;//
	long long hammer;//합성용
	int shield;//방어
	long long coin;//블록체인 코인

	long heartTimeStamp;

	int buffItem[TOTAL_WASTE];
	unsigned short medalShop[TOTALMEDALSHOP * MEDALSHOPDATASIZE];

	int playtime;//플레이타임

	bool statue[TOTAL_STATUE];
	std::string nickname;

	bool equipGet[ITEM_GEM_START];//

	int maxStatusCnt;

	int enemyUserIdx;//현재 세팅되어 있는 상대방

	int quest;//현재 퀘스트
	int subQuest;//
	int questCnt;//현재 퀘스트 카운트

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
	//false 면 일반방
	//true 면 보스방
	//2 면 골드이벤트

	//일일 보상
	long calendarTimeStamp;
	//캘린더의 일별 스테이터스로 
	//0이면 
	int calendarDayStatus[WEEK];
	int calendarMonthDay;

	int waveIdx;//몇번째 웨이브인지
	int curWaveIdx;//현재까지 몇개의 적이 등장했는지 보여주는 
	bool waveActive[MAXENEMY];//최대 에네미
	long waveTimeStamp;

	OBJECT boxObj;
	//현재 족보가 어떻게 되었는지를 
	//1000번마다 최대 2번이 나올 수 있다.
	int rouletteLog[MAXROULETTELOG];
	int rouletteLogIdx;//현재 몇번째 인덱스를 쓰고 있는지
	int rouletteLog_HeartCnt;//현재 하트가 MAXROULETTELOG 기준으로 몇번 나와 있는지
	int rouletteLog_RaidCnt;//현재 레이드가 MAXROULETTELOG 기준으로 몇번 나와 있는지

	bool heroesSetting[TOTALCHAR];//장착이 되어 있는지
	//몇번 캐릭터를 하는지
	bool getCrews[TOTAL_CREW];
	int crewStar[TOTAL_CREW];
	int crewMaxStar[TOTAL_CREW];
	int crew[MAXCREW];
	int crewStage;
	bool crewSetting[MAXCREW];//현재 장착이 되어 있는지
	int crewReader;//크류리더가 누군지.

	int lv;
	int exps;

	template <class Archive>
	void serialize(Archive & ar)
	{
		ar(
			charData,
			inven[TOTALINVENTORY],

			stage,
			room,

			demoSeen[TOTALDEMO],

			count,

			gold,
			heart,
			medal,
			star,
			hammer,
			shield,
			coin,

			heartTimeStamp,

			buffItem[TOTAL_WASTE],
			medalShop[TOTALMEDALSHOP * MEDALSHOPDATASIZE],

			playtime,

			statue[TOTAL_STATUE],
			nickname,

			equipGet[ITEM_GEM_START],

			maxStatusCnt,

			enemyUserIdx,

			quest,//현재 퀘스트
			subQuest,//
			questCnt,//현재 퀘스트 카운트

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

			gameEvent[MAXGAMEEVENT],

			openedMenu[TOTAL_MENU],

			eventCnt,

			bossRoom,

			calendarTimeStamp,

			calendarDayStatus[WEEK],
			calendarMonthDay,

			boxObj,

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
	unsigned char maxInven;
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
	int color2;//바나오기
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
	unsigned short owner;//데미지를 준 자가 누군지
	unsigned short target;//데미지를 받은 자가 누군지
	int color;

	float zoom;
} DMGINFO;

typedef struct _iconMark {
	int imageOffX, imageOffY; //이미지 오프셋 X, Y
	int imageDx, imageDy; //이미지 면적 dx, dy
	int resNum;//이미지 인덱스
	int x, y;//현재 x, y위치
	int targetX, targetY;//목적지 XY 
	int targetX2, targetY2;//목적지 XY 
	signed char dirX, dirY;//방향
	float dx, dy;//x, y축 이동거리
	float speed;//이동속도
	float speedIncrement;//이동속도 증가량
	float speed2;//이동속도2
	float speedIncrement2;//이동속도 증가량
	int waitingFrame;//시작했을 때 머무르는 프레임
	int waitingFrame2;//중간에 이동속도 체인지 했을 때 머무는 프레임
	int frame;//현재 프레임
	int frame2;//
	int lockOpenFrame;//잠김이 열리는 프레임
	int moveAngle;
	int amount;
	int type;//카드에서는 어택타입
	int detail;
	int grade;
	int cooldown;
	int icon;

	int attackType;
	int attackStr;

	float zoom;
	float zoomEnd;//줌
	float zoomIncrement;
	float zoom2;
	float zoomEnd2;//줌
	float zoomIncrement2;
	int alpha;
	bool text;
	bool value;
	bool ani;

	int owner;//ao의 인덱스
	int jokboIcon;//박스의 경우에는 트루
	bool star;
	bool cardFrame;
	bool newItem;

	int bar;//어떤 바를 향해 가야 하는지.
} ICONMARK;

typedef struct _iconMarkArr {
	int imageOffX, imageOffY; //이미지 오프셋 X, Y
	int imageDx, imageDy; //이미지 면적 dx, dy
	int resNum;//이미지 인덱스
	int x, y;//현재 x, y위치
	int targetX, targetY;//목적지 XY
	int targetX2, targetY2;//목적지 XY 
	signed char dirX, dirY;//방향
	float dx, dy;//x, y축 이동거리
	float speed;//이동속도
	float speedIncrement;//이동속도 증가량
	float speed2;//이동속도2
	float speedIncrement2;//이동속도 증가량
	int waitingFrame;//시작했을 때 머무르는 프레임
	int waitingFrame2;//중간에 이동속도 체인지 했을 때 머무는 프레임
	int frame;//현재 프레임
	int frame2;//현재 프레임
	int endFrame;//종료 프레임
	int endFrame2;//종료 프레임
	int moveAngle;
	int amount;
	int type;//카드에서는 어택타입
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
	float zoomEnd2;//줌
	float zoomIncrement2;
	int alpha;
	bool text;
	bool value;
	bool ani;

	int owner;//ao의 인덱스
	bool jokboIcon;//박스의 경우에는 트루
	bool star;
	bool cardFrame;

	int iconMarkCnt;//얼마나 아이콘마크를 생성해야 되는지 
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
	//몬스터를 잡은 횟수
	unsigned int monsterKill[NPC_CAPTAIN * 3];
	unsigned int monsterKill2[TOTALMAPTYPE];

	//몬스터한테 죽은 횟수
	unsigned short monsterVictim[NPC_CAPTAIN * 3];

	//몬스터한테 걸려본 디버프
	signed char monsterDebuf[NPC_CAPTAIN];

	//몬스터에게서 얻어본 재료
	signed char monsterMaterial[NPC_CAPTAIN];

	unsigned char currentTitle;

	unsigned char shopCount[3];

	// 길드전 관련 변수
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

//SetRoom 때 초기화 시킬변수들
typedef struct _reportVar {
	unsigned short stayMonster;
	signed char isTalked;
	signed char isUseSkill;
	signed char activeItem;
} REPORTVAR;

//NewGame시 초기화 시킬변수들
typedef struct _reportVar2 {
	int roomFrame;
	int gandhi;
	int darkStone;
	unsigned short noPotion;	//검소한 강자(포션을 사용하지 않고 잡은 몬스터 마릿수)
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

// =========================
// Jump Roulette State
// =========================

struct ReelJumpState {
	JumpState state;
	float jumpY;        // 현재 점프 높이(px)
	float jumpV;        // 점프 속도(px/frame)

	float maxJumpY;     // 그림자 연출용(최대 높이)
	int curShowPos;     // 현재 보여주는 alivePos
	int landedPos;      // 착지 확정 alivePos
	int lastSwapF;      // 마지막 교체 프레임

	bool started;     // 이번 슬롯 연출에서 해당 릴이 시작했는지
	int holdEndFrame;   // slotFrame 기준, 여기까지 JS_HOLD 유지

	// --- 추가 ---
	bool  flipLR;         // 좌/우 토글(회전 느낌)
	int   lastFlipF;      // 마지막 토글 프레임
	int   flashEndF;         // 반짝 FX 종료 프레임
	int   vortexEndF;        // 회오리 FX 종료 프레임

	// [MOD-R1] 뒤집기(회전) 스쿼시 연출용
	int   flipSquashEndF;   // 이 프레임까지 스쿼시 적용
	int   flipSquashLen;    // 지속 프레임(2~4 추천)

	int bounceLeft; // 1이면 착지 후 미니바운스 1번
};

extern ReelJumpState gReelJump[TOTALREEL];
// [MOD-G] “3개 확정 후 종료 딜레이” 카운터
extern int sEndDelayLeft;

extern int logIndex;

//시스템
extern cocos2d::Sprite* sprite[TOTALIMG];
extern cocos2d::Texture2D* texture[TOTALIMG];
//없으면 이미지 추가(없다는 기준은 rendeSpriteIndex == -1 이면
extern cocos2d::Sprite* renderSprite[MAXRENDERCNT];//이미지 신규생성시 사용
extern int renderSpriteIndex[MAXRENDERCNT];//이미지 신규생성시 사용 - 렌더스프라이트가 TOTALIMG 중에 몇번을 담았는가
//0값이 기본이고 이미지가 생성되면 카운트가 하나 늘어나는거지
extern int sameRenderSpriteMax[TOTALIMG];//현재 최대 몇개까지 추가되었는가
//현재 sameRenderSpriteMax에 도달하지 않았는지를 판단해서 기존것을 사용하고 하나씩 카운트를 증가시키는거지
extern int sameRenderSpriteCur[TOTALIMG];//이번 드로우에 몇개까지 쓰고 있는가.(프레임마다 초기화됨)
extern int sameRenderSpriteArr[TOTALIMG][3000];//배열에 특정인덱스의 이미지를 렌더스프라이트 몇번에 들어가있는지를 저장하는 배열
extern int curRenderSpriteArr[MAXRENDERCNT];
extern int getSpriteIdx;
extern int getSpriteTexture;
extern int totalRenderCnt;//현재 그려야 하는 총 개수
extern int curRenderCnt;//현재 그려야 하는 총 개수

//없으면 이미지 추가(없다는 기준은 rendeSpriteIndex == -1 이면
extern cocos2d::Sprite* bufferSprite[MAXBUFFERSPRITECNT];//이미지 신규생성시 사용
extern int bufferSpriteIndex[MAXBUFFERSPRITECNT];//이미지 신규생성시 사용 - 렌더스프라이트가 TOTALIMG 중에 몇번을 담았는가
//0값이 기본이고 이미지가 생성되면 카운트가 하나 늘어나는거지
extern int sameBufferSpriteMax[TOTALIMG];//현재 최대 몇개까지 추가되었는가
//현재 sameRenderSpriteMax에 도달하지 않았는지를 판단해서 기존것을 사용하고 하나씩 카운트를 증가시키는거지
extern int sameBufferSpriteCur[TOTALIMG];//이번 드로우에 몇개까지 쓰고 있는가.(프레임마다 초기화됨)
extern int sameBufferSpriteArr[TOTALIMG][60 * 47];//배열에 특정인덱스의 이미지를 렌더스프라이트 몇번에 들어가있는지를 저장하는 배열
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
extern cocos2d::Label* fontLabelWidth;//폰트 넓이용 넓이
extern cocos2d::Label* fontLabel[MAXFONTLABELCNT];//라벨 신규생성시 사용
extern int fontLabelIndex[MAXFONTLABELCNT];//라벨 신규생성시 사용 - 텍스트라벨이 폰트라벨 중 몇번을 담았는가
extern int fontLabelMotherIndex[MAXFONTLABELCNT];//만약 복제가 되는 경우 몇번을 복제한 것인가
extern int sameFontLabelMax[TEXT_LENGTH];//현재 최대 몇개까지 추가되었는가
extern int sameFontLabelCur[TEXT_LENGTH];//이번 드로우에 몇개까지 쓰고 있는가.(프레임마다 초기화됨)
extern int sameFontLabelArr[TEXT_LENGTH][100];//배열에 특정인덱스의 라벨을 렌더스프라이트 몇번에 들어가있는지를 저장하는 배열
extern int curFontLabelArr[MAXFONTLABELCNT];//하나 추가될때마다 인덱스를 추가한다

extern int getFontLabelIdx;
extern int getFontLabelTexture;

extern int totalFontLabelCnt;
extern int curFontLabelCnt;
#ifdef BMFONT
extern cocos2d::LabelBMFont* textLabel[MAXLABELCNT];
#else
extern cocos2d::Label* textLabel[MAXLABELCNT];
#endif

extern int textLabelIndex[MAXLABELCNT];//라벨 신규생성시 사용 - 텍스트라벨이 TOTALIMG 중에 몇번을 담았는가
//0값이 기본이고 이미지가 생성되면 카운트가 하나 늘어나는거지
extern int sameTextLabelMax[TEXT_LENGTH];//현재 최대 몇개까지 추가되었는가
//현재 sameRenderSpriteMax에 도달하지 않았는지를 판단해서 기존것을 사용하고 하나씩 카운트를 증가시키는거지
extern int sameTextLabelCur[TEXT_LENGTH];//이번 드로우에 몇개까지 쓰고 있는가.(프레임마다 초기화됨)
extern int sameTextLabelArr[TEXT_LENGTH][100];//배열에 특정인덱스의 이미지를 렌더스프라이트 몇번에 들어가있는지를 저장하는 배열
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
extern signed short STATUSWIN_Y;//전투를 위한 
extern signed short STATUSWIN_Y2;
extern signed short PLAYAREA_X;
extern signed short PLAYAREA_Y;
extern signed char yesnoFrame;
extern signed char buy_Mode;

extern unsigned char imgLoaded;

//추가 다운로드 변수
#ifdef DOWNLOAD
extern signed char isDown;	//추가다운 받았는지 여부//startCelt에서 검색
extern signed char oldDraw;	//올드변수를 저장하고있다가, 다운로드 완료시 해당 상태로 돌려준다.
#endif

extern int thickColor;
extern int fontColor, oldColor;
extern int baseColor;

extern const char* textString;	//프레임텍스트용 스트링
extern unsigned short textStringLength[50];
extern unsigned short textStringOffset[50];
extern unsigned char textStartColor[50];
extern unsigned short textFrame;	//프레임따라 점점 찍힐때 사용
extern unsigned char textPage;	//원래 길이가 몇페이지 짜리인지 사용
extern unsigned char textCurPage;	//현재 몇번째 페이지인가
extern unsigned char textLines;	//몇줄짜리냐
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

//키조작
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
extern unsigned char curEnemyFrame;	//현재 적 이름이 몇프레임동안 떠 있나
extern signed int curEnemy;	//현재 공격중인 몬스터가 누구냐
extern signed int curPlayer;	//현재 공격받고 있는 주인공은 누구냐
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
extern char skillStr2[256];//스킬상세설명
extern char ringStr2[256];
extern char skillStr3[256];//스킬이름
extern char skillToolTips[256];//스킬이름
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
//메인보상리스트(여기에 한번 받는 모든 보상 시퀀스 1depth가 들어간다.)
extern ICONMARK rewardMark[TOTALREWARDMARK];
extern ICONMARK rewardMarkBack[TOTALREWARDMARK];
extern ICONMARK rewardMark_PopUp[TOTALREWARDMARK];
//가챠용 박스마크. (가챠를 들어갔을 때 여러개의 박스가 있으면 모두 여기 들어간다.)
extern ICONMARK boxMark[TOTALBOXMARK];
//박스에서 카드를 깔 때 나오는 것들
extern ICONMARK boxCardMark[TOTALCARDMARK];//보조박스에서 나온 리워드마크
//소울마크
extern ICONMARK soulMark;
extern ICONMARK goldAlphaMark[TOTALGOLDALPHAMARK];

//배틀에서 쓰이는 전투
extern OBJECT ao[TOTALOBJECT];
extern BAR bar[TOTAL_BAR];

extern TEMPSAVE tempSave[3];
extern CURRENCYEFFECT currencyEffect[TOTAL_CURRENCY];
extern signed short crX, crY, crW, crH;

extern char saveMem[sizeof(ROBINDATA)];
extern char backupMem[sizeof(ROBINDATA)];

//맵 관련 변수
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

//TALK 관련 변수
extern unsigned char talkShakeFrame;

extern int touchCount;

//cmf 관련 변수
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

//플레이어 움직임 관련 변수
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
extern unsigned char currentTimeQuest; //현재 타임퀘스트 저장.
extern unsigned short TimeFailDemo;    // 타임퀘스트 실패시 동작해야하는 데모신 저장
extern unsigned char darkStone;
extern unsigned char npcdarkStone;

//플레이어 이미지 관련 변수

//문 이미지 관련 변수
extern unsigned char doorCmf[MAXDOOR];
extern unsigned char doorCnt;

//아이템 관련 변수
extern ITEM tempItem;
extern ITEM helpItem[MAXHELPITEM];
extern int tempItemIdx;//인벤토리의 몇번인지
extern signed short itemObj;
extern unsigned char tempFishItem;
extern unsigned char nInvenMax, nInvenCnt, nShopCnt;
//int needErase[10];
extern int shopDesc[MAXNETSHOP];
extern int cItem;
extern int focusItem;
extern int boxNeutral;
extern int cNeutral;
extern int progress;
extern unsigned char extraArmor;
extern int shopGachaItemCnt;

//메뉴관련 변수
extern signed char yesNo;
extern signed char menuDepth;
extern signed char rewardDepth;
extern signed char gachaDepth;
extern signed char newCardDepth;
extern signed char newCollectionDepth;
extern signed char stageInfoDepth;
extern signed int curMenu;//타이틀메뉴, 게임메뉴의 메인값
extern signed int curHouse;//현재 선택되어 있는 집
extern signed int curHero;//현재 히어로
extern signed int curMenuBack;
extern signed int curEventIdx;//현재 이벤트
extern int menuFrame;//메뉴 프레임
extern int menuTalkFrame;//메뉴 프레임 보조
extern int menuWinFrame;//메뉴 윈도우 프레임
extern int menuPage, menuPage2;//메뉴페이지
extern int menuCur;	//위아래로 넘기는 메뉴에서 사용
extern int menuX, menuY;//x, y로 이동하는 메뉴에서 사용
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
extern int gachaIndex;//현재 뽑고 있는 상자의 인덱스
extern int gachaCardIdx;
extern int stageRewardIdx;
extern int helpPage;
extern int helpScene;
extern int helpFrame;
extern unsigned char enchantResult;
extern unsigned char shopType;

extern int menuIdx, menuIdx2;	//맨 상단 페이지
extern int menuFocus, menuFocus2;	//현재 어디냐
extern int menuInfo, menuWindow;	//정보창을 띄울 경우
extern int menuMessage;//작은 창 0이면 off
extern int menuItem, menuItem2, menuItem3, menuItem4;
extern int menuCount;
extern int menuType;
extern int menuCountCursor;	//상점에서 사고 팔때 갯수 정하는거
extern int menuItemCount;	//상점에서 표시되는 갯수
extern int menuIcon;
extern signed short invenRecipe[TOTALINVENTORY];	//인벤토리에 레시피
extern signed short invenRecipeCnt;	//인벤토리에 총 몇개가 있는지
extern int enchantSlot[INVEN_HCNT];
extern int enchatSlotCnt;
extern signed short invenGemCnt;

//스크롤 관련 변수
//scS, scE, scT, scC, scP (인벤토리)
//scS2, scE2, scT2, scC2, scP2 (인벤토리)

//스크롤이 필요한 메뉴

extern signed int scS[TOTAL_MENU];
extern signed int scE[TOTAL_MENU];
extern signed int scT[TOTAL_MENU];
extern signed int scC[TOTAL_MENU];
extern signed int scP[TOTAL_MENU];

extern signed int isS, isT, isE, isC;
//scY의 추가 두가지는 하나는 
extern signed int scX, scY[TOTAL_MENU], snapTargetY[TOTAL_MENU];//x, y 스크롤
extern signed int scY_Log, scT_Log;

extern unsigned char scDir;//0이면 스크롤이 없는거고, 1이면 수평, 2명 수직이다.
extern signed short scRecoveryFrameX, scRecoveryFrameY, scAccelY;//복구
extern int autoScroll;//자동으로 스크롤을 시킬건지
extern int autoScrollGap;//해당 프레임에 진행할 스크롤 크기

extern bool keyCoreDisable;
extern unsigned char vibLevel;
extern unsigned char stoneWhere;
extern unsigned short charInfoPage;

extern int INVEN_VCNT;//인벤토리 세로 몇개인가
extern int INVEN_TCNT;
extern int GNBHEIGHT;
extern int BOTTOMMENUHEIGHT;

extern REPORTVAR rpVar;
extern REPORTVAR2 rpVar2;
extern signed char *rpPtr;

//투기장 & 레이드 관련 변수
extern unsigned char startFrame;	//게임자체가 로드가 되서 시작할 때 쓰는 프레임
extern unsigned char startPageCur;	//현재 몇번째 페이지를 가르키고 있는지
extern unsigned char startPageMax;	//최대 보여줘야 되는 스타트 페이지들이 몇장인지 보여주는 프레임
extern unsigned char startPage[MAXSTARTPAGE];

extern unsigned char arenaFrame;	//투기장 시작, 정지 프레임
extern unsigned char arenaFloorTime;	//다리 열리는 시간
extern int arenaLimitTime;	//투기장 남은 시간
extern long arenaTotalTime;	//투기장 타임 (현재 1800초(30분)로 설정됨. 변경시 ArenaResult 소요시간 수정해야함.
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

extern int raidInfo[TOTALRAIDSELECTED * RAIDARRAYDATASIZE];//어떤 보스를 내보내고, 어떤 보상을 줄지 결정(보상은 타입, 디테일, 등급 세가지로 결정)


extern unsigned short arenaFloor;//현재 몇층인지(지하1층부터~~)
extern signed short arenaScore;
extern unsigned short arenaKill;	//적 죽인 갯수
extern signed short arenaItemFrame;	//현재 남은 프레임
extern signed short arenaDebuf[TOTALDEBUF];	//투기장 들어가기전 상태저장
extern unsigned char arenaRewardType, arenaRewardLv, arenaRewardDetail, arenaRewardGrade, arenaRewardCnt;	//보상 아이콘을 그려주기 위한 데이터
extern unsigned char arenaStatus;//0이면 시작전, 1이면 전투중, 2면 클리어

extern long long int dmg[MAXPLAYER];//현재 플레이어의 토탈데미지를 입력하는 곳
extern long long int dmgOrder[MAXPLAYER];//그에 따른 순위

extern unsigned short arenaMotion[MAXPLAYER];

extern long long int arenaItemPrice[MAXARENAITEM];//현재 아레나 보상 아이템의 가격을 평가한 것
extern long long int arenaItemOrder[MAXARENAITEM];//가격에 따른 순서를 조정한 것
extern unsigned short arenaItemEffectFrame[MAXARENAITEM];//현재 아이템을 보여주기 위한 프레임

extern unsigned short startItemIdx;
extern unsigned short totalItemCnt;
extern unsigned short totalItemFrame;

extern unsigned short arenaDeadCount;
extern unsigned short arenaItemCount;
extern unsigned short arenaHitCount;

//0 애들 등장
//1 순위 왕관 등장
//2 1등 캐릭터 즐거워하는 모습
//3 1등 캐릭터에게 아이템 전달
//4 1등 캐릭터 아이템 받고 즐거워하는 모습
//5 2등 캐릭터에게 아이템 전달
//6 3등 캐릭터에게 아이템 전달
//7 4등 캐릭터에게 아이템 전달
//8 5등 캐릭터에게 아이템 전달
//9 6등 캐릭터에게 아이템 전달
//10 7등 캐릭터에게 아이템 전달
//11 8등 캐릭터에게 아이템 전달
//12 9등 캐릭터에게 아이템 전달
//13 10등 캐릭터에게 아이템 전달
//14 유저 보상 박기
//15 아이템 리스트 박기

extern unsigned char playResultStatus; 
extern unsigned char raidPlayer;

extern unsigned char skillSlot[RAIDSKILLSLOT];


//길드전 관련 변수
extern unsigned char guildTimeStr[20];	//남은시간 표시 변수
extern unsigned int guildTotalScore;	//길드전 누적 점수
extern int curTime;
extern signed int rankRecord[16];	//그래프 표시할 것 저장변수
extern signed int rankWeek;		//몇주차 인지
extern char rankScore[4][15];	//점수 저장 변수||길드전현황->현재길드전스코어
extern unsigned char guildCur;		//그래프에서 커서이동때 사용
extern signed char guildWinner;
extern unsigned char guildReward[5];		//0 : type, 1:lv, 2:detail, 3:grade, 4:count, 5:첫번째보상골드금액(1천단위)
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
//복제방지
extern char phoneMatch;
extern char isScreenShot;

extern char isDragging;//화면을 무언가가 누르고 있다는 변수(드래깅중이라는것)
extern int pointed;//누른곳이 어떤 영역인가에 해당하는 변수

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

//추가된 투기장 관련 변수
extern unsigned short caveMap;			//현재 어디 투기장인지.
extern unsigned short caveEnemyAlive[159 * 2];

extern unsigned short caveCountEmy;
extern unsigned short caveCountEmy2;
extern unsigned short caveKill;		//투기장 몬스터 퇴치수.(신규 투기장은 몬스터를 모두 잡으면 끝남)
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


//키비시스 자루	: 미래의 거울 / 9
//세이렌의 피리	: 용자의 시계 / 25
//황혼의 성배	: 메피스토 피리 / 5
//로젤린의 꽃	: 난쟁이의 공 / 20

//재앙의 거울	: 미래의 거울 / 9
//영웅의 서사시	: 용자의 시계 / 25
//유니콘의 뿔	: 메피스토 피리 / 5
//황금 조개		: 난쟁이의 공 / 20

//천사의 날개	: 미래의 거울 / 9
//금단의 과실	: 용자의 시계 / 25
//죽음의 올가미	: 메피스토 피리 / 5
//조각난 영혼	: 난쟁이의 공 / 20
//
//충성의 반지	: 승자의 반지 / 13
//황제의 반지	: 궁극의 반지 / 14
//절대 반지		: 폭주의 반지 / 7
//니벨룽겐 반지	: 신념의 반지 / 11

//은하수 반지	: 승자의 반지 / 13
//약속의 반지	: 궁극의 반지 / 14
//요정의 반지	: 폭주의 반지 / 7
//흡마 반지		: 신념의 반지 / 11

//번뇌의 반지	: 승자의 반지 / 13
//불사의 반지	: 궁극의 반지 / 14
//황금 반지		: 폭주의 반지 / 7
//봉인된 반지	: 신념의 반지 / 11
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
extern experimental::ui::WebView       *_webView;
#endif



extern int adX; //광고의 x포지션
extern int adY; //광고의 y포지션
extern int adFrame;//광고의 프레임
extern int adType;//광고의 타입
extern int adProfile;//광고의 프로필 사진
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
extern signed short dioramaType;//현재 디오라마


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
extern int idleHelpType;//이동을 시킬지, 공격을 하라고 할지
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

extern int raidChance;//처음에 5번을 주고 한번 싸울때마다 

extern int dmgIndex;
extern int subDmgIndex;

extern long currentTimeStamp;

//NEUTRAL	가만히 있을 때
//PLAYER	주인공이 공격시
//ENEMY		적에게 공격시
//공격시 
extern int turn;
extern int turnFrame;
extern int turnPosition;

extern int rouletteSequence;
extern int curRouletteStart;//몇번째 부터 시작하는건지
extern int totalRouletteCnt;//최종적으로 나와야 되는 룰렛개수//현재 위에 올라가 있는 룰렛 개수

//공격연출관련
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

//여기서부터 현재 룰렛이 어떤게 나왔는지 데이터. 이 데이터를 기반으로 어떤것을 내보내는지 정한다
//extern unsigned char roulette
extern int actionCardArr[TOTALCONTROLMARK];
extern int actionCardCnt;

extern int curtainFrame;

extern int subAttackType;//추가타라던가 이런것들
extern int subAttackStr;
extern int subAttackIcon;
//현재 카드메뉴가 뒷면이 노출되었는지
extern char cardMenuBack[TOTALEQUIP];
//+면 닫히는 상태로 1씩 빼주면서 0으로 간다.
//-면 열리는 상태로 1씩 더해주면서 0으로 간다.

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

extern ITEM rewardItem[MAXREWARDITEM];//메인 리워드 아이템
extern ITEM rewardItemBack[MAXREWARDITEM];//백업
extern int rewardItemCnt;//현재 획득된 아이템
extern int curRewardItem;//현재 획득진행중에 있는 아이템
extern int focusedItem;//메인리스트에서
extern int focusedSubItem;//서브리스트
extern bool newItem;

extern int boxCnt;//토탈 박스 카운트
extern int newCollectionCnt;//이번에 새로운 컬렉션이 완성된 카운트
extern int newCardCnt;//새로운 카드 카운트
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


//상대위치

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


extern int points[MAX_POINTS][2]; // 좌표를 저장할 배열 (x, y 각각을 1차원 배열로 저장)
extern int boxPoints[MAX_POINTS][2];

extern int selectedCrew;

extern bool rouletteOpen[SKILLPERSWORD];
extern bool loadRoulette;
extern int newCollection;

extern int attackedCrewIdx;//공격당한 인덱스
extern int bossGetCoinCrewIdx;//보스에게 도움을 준 인덱스

//스테이지에서 빚갚아주면 애니메이션 하는거
extern int stageUpgradeMotion[MAXCREW];

extern int bossRaidMode;//그냥 일반보스는 bossRoom은 true이고,	보스레이드는 이 변수를 쓴다. 

extern int subQuestCnt[TOTALQUEST];

extern GAMEEVENT * gEvent;

extern int swordSkillCnt[TOTAL_COLLECTIONS];//검별 스킬 개수
extern int swordSkillProb[TOTAL_COLLECTIONS * SKILLPERSWORD];//컬렉션 확률 

//여기는 서버로부터 로딩해 오는 것인데 일단 로컬에 저장한걸 불러오는 형식으로 하자.
extern HOUSE enemyHouse;
extern HOUSE stageHouse;//
//임시서버데이터
extern HOUSE aiUserHouse[TOTALAI];//서버 교신이 없는 상태에서의 AI
extern HOUSE * selectedHouse;//현재 선택된 하우스
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

//배틀이 걸렸을 때 정보
extern int battleTarget;//현재 적의 crew 인덱스로 null이거나 아니거나 상관없이 선택된 crew[i]의 i를 의미한다.
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
extern int crewList[MAXCREW];
extern int crewIdList[MAXCREW];
extern int crewCnt;
extern int heroCnt;
extern int showCrewCnt; // 로딩 화면에서 현재까지 "공개/합류 연출로 보여줄" 크루 수(0..crewCnt)
extern int showHeroCnt;

extern int leaderCrewId;   // 0..TOTAL_CREW-1 or -1
extern bool hasLeader;

// 중앙 카드에 표시할 현재 공개 캐릭터(crewList[showCrewCnt]를 기반으로)
extern int cardCmf;
extern int cardAlpha;

// 1) 타겟 결과 (예시) : aoOffset(0~8)로 받는다고 가정
extern int  gRouletteStartAoOffset[TOTALREEL];
extern int  gRouletteResultAoOffset[TOTALREEL];  // 최종 확정 3명 (aoOffset)
extern int gRouletteSkillIdx[TOTALREEL];
extern int rouletteFrame;
// 3개 다 확정 후 "한 번만" 합성/이동 연출 트리거
extern bool gRouletteSkillDispatchStarted ;

extern bool gRouletteResultValid;

extern int blState;
extern int blStateFrame;
extern int blFrame;

extern int finishOffsetX;

extern int bgScrollX;
extern int bgScrollY;

// ===== 소환 연출 =====
extern int summonCrewId;
extern int summonCmf;
extern int summonFromX, summonFromY;
extern int summonX, summonY;
extern int summonToX, summonToY;
extern int summonMidX, summonMidY;
extern float summonScale;
extern int summonHold;          // 센터 박히는 홀드 프레임 카운터(옵션)
extern int summonStar;          // 현재 소환 크루의 별등급(1~9)
extern int celebFlash;          // 축하 플래시(0이면 없음)
extern int shake;               // 화면 흔들림 강도(0이면 없음)
extern int joinFromX;
extern int joinFromY;

extern bool needPickSummonFromBg;
extern bool pickedSummonFromBg;
extern bool hideSummonBgTile;
extern int  hideBgCmf;
extern int summonType;

// 로딩바 진행률(“등장 단계” 기반)
extern int loadPct;

// ---------- pity 상태 ----------
extern int gNoHighStarCount; // STAR7+ 안 나온 연속 횟수

// ---------- 소프트 분산 상태 ----------
extern int gRecentRegionCount[TOTALCASTLE]; // 최근 등장 횟수
extern int gRecentStarCount[10];            // STAR 연속 패널티

// ================================
// 게임 상태 전역 변수 선언 (extern)
// 실제 정의는 GameState.cpp에 있음
// ================================

// 전투 관련
extern int attackDelayBefore;
extern int attackTypeBefore;
extern int attackStrBefore;
extern int rewardItemCntBefore;
extern int maxHitCnt;
extern int sequenceFrame;
extern int raidFrame;
extern int continuousAttackFrame;
extern int raidCnt;

// 자동 플레이
extern bool autoPlay;
extern bool autoSelect;
extern bool autoSkill;
extern int autoFrame;
extern bool autoButtonText;

// 화면
extern float screenZoom;
extern float dioramaZoom;
extern float battleZoom;
extern int screenDarken;

// 게임 상태
extern int waveStatus;
extern int levelUpFrame;
extern int levelUpStatus;
extern int maxUserLv;
extern bool bossOn;
extern int touchDisable;

#endif
