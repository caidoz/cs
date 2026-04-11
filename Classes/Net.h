#pragma once

#ifndef _CORE_H_
#include "Core.h"
#endif

#ifndef _NET_H_
#define _NET_H_

typedef enum _network {
	NET_RANK = 1,//랭킹전송 및 결과값 받아오기
	NET_SHOP,//넷샵으로 접속하여 샵에 있는 아이템들과 넷인벤토리에 있는 아이템들을 받아오기 위해서
	NET_INVEN,//넷인벤으로 접속하여 인벤토리에 있는것들을 불러온다.
	NET_SAVE,//서버에 데이터 저장(인벤토리부분 제외)
	NET_LOAD,//서버에 있는 데이터 로드(인벤토리부분 제외)
	NET_SCREEN,//스크린샷
	NET_RANK_REFRESH,//랭킹메뉴에서 1,3번키로 돌릴때
	NET_RANK_ADD,//랭킹메뉴에서 위아래키로 상/하위 유저 보려고 할때
	NET_RANK_DETAIL,//선택된 유저의 상세정보를 보려 할때
	NET_SHOPONLY,//상점 정보만 다운로드 하는 경우(타이틀+NPC상점)
	NET_SHOP_BUY,//넷샵에서 아이템 구매 요청(타이틀, 응급부활약)
	NET_SHOP_COUPON,//쿠폰으로 구매
	NET_SHOP_BUYSUCCESS,//아이템 구매 완료
	NET_SHOP_DOWNLOAD, //넷샵에서 싱글인벤으로 다운로드
	NET_SHOP_ERASE,	//넷샵에서 아이템 버리기
	NET_INVENTOSHOP,//인벤토리 화면에서 상점으로 바로 넘어갈때(타이틀)
	NET_INVEN_DOWNLOAD,//넷인벤에서 싱글인벤으로 다운로드
	NET_INVEN_UPLOAD,//싱글인벤에서 넷인벤으로 업로드
	NET_INVEN_PRESENTS,//넷인벤에서 다른 유저에게로 아이템 전송
	NET_INVEN_ERASE,//
	NET_ARENA_NOTICE,
	NET_SERVER_CLOSE,
	NET_AGREE,
	NET_VERIFY,
	NET_GAME_BUY,
	NET_GAME_BUYSUCCESS,
	NET_FILE_DOWNLOAD,
	NET_STONE_ENCHANT,
	NET_STONE_PROTECT,
	NET_STONE_RECIPE,
	NET_STONE_RESOLUTION,
	NET_STONE_SOCKET,
	NET_DAILY_GETQUEST,
	NET_DAILY_ENDQUEST,
	NET_GUILD_START,
	NET_GUILD_CURRENT,
	NET_GUILD_REWARD,
	NET_GUILD_RECORD,
	NET_GUILD_RANKING,
	NET_ARENA_RESULT,
	NET_USER_CHECK,
	NET_RECOMMEND,

	#ifdef ADDKOIN
	NET_KHUB_BALANCE,
	#endif

	NET_ASSA,

	NETSTATUS_OFFLINE	= 0,				///<	네트워크 비활성화 상태
	NETSTATUS_ERROR,						///<	에러 발생에 따른 에러 출력 화면 상태
	NETSTATUS_LOCK,							///<	접속불가 메세지
	NETSTATUS_CONNECTED,				///<	서버와 연결이 된 상태
	NETSTATUS_CONNECT,					///<	서버와 연결시도중인 상태
	NETSTATUS_INIT,							///<	인증중
	NETSTATUS_SEND,							///<	데이타 송, 수신 성공 상태
	NETSTATUS_RECEIVE,						///<	데이타 송, 수신 성공 상태
	NETSTATUS_RESULT,						///<	결과화면
	NETSTATUS_WAIT,						///<	대기상태

	END_NETWORK
} NETWORK;

//#ifdef SKT
//#ifdef SIMULATOR
//#pragma pack(1)
//#endif
//#else
//#pragma pack(1)
//#endif

typedef enum _pktDef {
	//Client -> Server
	PTC_CHARRANKING	= 0x10,	//(클라이언트에서 스토리모드 랭킹전송)
	PTC_ARENARANKING,			//(클라이언트에서 서바이벌 랭킹 전송)
	PTC_NOTICE_RANKING,		//(클라이언트에서 공지사항을 받아온다)
	PTC_NOTICE_SHOP,			//(클라이언트에서 공지사항을 받아온다)
	PTC_NOTICE_ARENA,			//(클라이언트에서 공지사항을 받아온다)
	PTC_NOTICE_GUILD,			//(클라이언트에서 공지사항을 받아온다)
	PTC_RANKING_ADD,
	PTC_RANKING_DETAIL,
	PTC_SHOPINFO,					//(클라이언트에서 샵+넷 인벤토리 정보 요청)
	PTC_SHOPONLYINFO,			//(클라이언트에서 샵 정보 요청)
	PTC_GETITEMATSHOP,		//(클라이언트가 넷 인벤토리에서 장비를 내릴때)
	PTC_ERASEITEMATSHOP,	//(클라이언트가 넷 인벤토리에서 장비를 내릴때)
	PTC_BUYITEM,					//(클라이언트에서 샵 아이템 구매 요청)
	PTC_BUYSUCCESS,				//(클라이언트에서 샵 아이템 구매 요청)
	PTC_INVENINFO,					//(클라이언트에서 넷 인벤토리 정보 요청)
	PTC_INVENTOSHOP,
	PTC_SENDITEM,					//(클라이언트에서 넷 인벤토리로 장비를 올릴때)
	PTC_GETITEM,					//(클라이언트가 넷 인벤토리에서 장비를 내릴때)
	PTC_PRESENT,					//(클라이언트에서 선물 보내기를 요청한다)
	PTC_SENDCHARACTOR,		//(클라이언트에서 캐릭터 정보를 백업한다)
	PTC_GETCHARACTOR,			//(클라이언트가 서버에 백업된 캐릭터를 받아온다)
	PTC_ERASEITEM,
	PTC_SERVERCLOSE,
	PTC_ERASECOPYITEM,
	PTC_AGREE,
	PTC_VERIFY,
	PTC_VERIFY_PANG,
	PTC_VERIFY_GXG,
	PTC_VERIFY_NHN,
	PTC_VERIFY_NATE,
	PTC_VERIFY_DAUM,
	PTC_VERIFY_MOKI,
	PTC_QUICKBUYITEM,
	PTC_QUICKBUYSUCCESS,
	PTC_FILE,
	PTC_VIEW_RANKER,
	PTC_SCREENSHOT,
	PTC_STONE_BUY,
	PTC_DAILYGET,
	PTC_DAILYEND,
	PTC_GUILDSTART,
	PTC_GUILDCURRENT,
	PTC_GUILDREWARD,
	PTC_GUILDRECORD,
	PTC_GUILDRANKING,
	PTC_ARENARESULT,
	PTC_USERCHECK,
	PTC_RECOMMEND,

	//Server -> Client
	PTS_CHARRANKING	= 0x10,	//(클라이언트에서 스토리모드 랭킹전송)
	PTS_ARENARANKING,			//(클라이언트에서 서바이벌 랭킹 전송)
	PTS_NOTICE_RANKING,		//(클라이언트에서 공지사항을 받아온다)
	PTS_NOTICE_SHOP,			//(클라이언트에서 공지사항을 받아온다)
	PTS_NOTICE_ARENA,			//(클라이언트에서 공지사항을 받아온다)
	PTS_NOTICE_GUILD,			//(클라이언트에서 공지사항을 받아온다)
	PTS_RANKING_ADD,
	PTS_RANKING_DETAIL,
	PTS_SHOPINFO,					//(클라이언트에서 샵 정보 요청)
	PTS_SHOPONLYINFO,			//(클라이언트에서 샵 정보 요청)
	PTS_INVENONLYINFO,			//(클라이언트에서 넷 인벤토리 정보 요청)
	PTS_GETITEMATSHOP,		//(클라이언트가 넷 인벤토리에서 장비를 내릴때)
	PTS_ERASEITEMATSHOP,	//(클라이언트가 넷 인벤토리에서 장비를 내릴때)
	PTS_BUYITEM,					//(클라이언트에서 샵 아이템 구매 요청)
	PTS_BUYSUCCESS,				//(클라이언트에서 샵 아이템 구매 요청)
	PTS_INVENINFO,					//(클라이언트에서 넷 인벤토리 정보 요청)
	PTS_INVENTOSHOP,
	PTS_SENDITEM,					//(클라이언트에서 넷 인벤토리로 장비를 올릴때)
	PTS_GETITEM,					//(클라이언트가 넷 인벤토리에서 장비를 내릴때)
	PTS_PRESENT,					//(클라이언트에서 선물 보내기를 요청한다)
	PTS_SENDCHARACTOR,		//(클라이언트에서 캐릭터 정보를 백업한다)
	PTS_GETCHARACTOR,			//(클라이언트가 서버에 백업된 캐릭터를 받아온다)
	PTS_ERASEITEM,
	PTS_SERVERCLOSE,
	PTS_ERASECOPYITEM,
	PTS_AGREE,
	PTS_VERIFY,
	PTS_VERIFY_PANG,
	PTS_VERIFY_GXG,
	PTS_VERIFY_NHN,
	PTS_VERIFY_NATE,
	PTS_VERIFY_DAUM,
	PTS_VERIFY_MOKI,
	PTS_QUICKBUYITEM,
	PTS_QUICKBUYSUCCESS,
	PTS_FILE,
	PTS_VIEW_RANKER,
	PTS_SCREENSHOT,
	PTS_DAILYGET,
	PTS_DAILYEND,
	PTS_GUILDSTART,
	PTS_GUILDCURRENT,
	PTS_GUILDREWARD,
	PTS_GUILDRECORD,
	PTS_GUILDRANKING,
	PTS_ARENARESULT,
	PTS_USERCHECK,
	PTS_RECOMMEND,

	END_PKTDEF
} PKTDEF;


typedef struct {
	//signed int playtime;
	//signed int exps;
	//int score[TOTALSCORE];
	//int ps[TOTALPLAYERSTAT];
	//unsigned short stat[4];
	//signed short hp;
	//signed short mp;
	//unsigned short ap;
	//signed short map;	//현재 방
	//signed short home;
	//signed short x, y;	//현재 위치
	//signed short buff[TOTALBUFF];
	//signed short debuf[TOTALDEBUF];

	//unsigned char sp;
	//unsigned char maxInven;
	//unsigned char lv;
	//signed char equipped[TOTALEQUIP];
	//signed char curArea;
	//signed char phoneNum[12];
	//signed char skillLv[TOTALSKILL];
	//signed char statue[(TOTAL_STATUE + 7) / 8];
	//signed char keyItem[(TOTAL_KEYITEM + 7) / 8];
	//signed char mapSeen[(TOTALMAP + 7) / 8];
	//signed char demoSeen[(TOTALDEMO + 7) / 8];
	//signed char itemCheck[(TOTALITEM + 7) / 8];
	//signed char leverCheck[(TOTALLEVER + 7) / 8];
	//signed char pushCheck[(TOTALPUSH + 7) / 8];
	//signed char boxCheck[(TOTALBOX + 7) / 8];
	//signed char dianaTrapCheck[(TOTALDIANATRAP + 7) / 8];
	//signed char maxxTrapCheck[(TOTALMAXXTRAP + 7) / 8];
	//signed char gateCheck[(TOTALGATE + 7) / 8];
	//signed char sunBlockCheck[(TOTALSUNBLOCK + 7) / 8];
	//signed char breakStoneCheck[(TOTALBREAKSTONE + 7) / 8];
	//signed char iceBreakCheck[(TOTALICEBREAK + 7) / 8];
	//signed char golemBlockCheck[(TOTALGOLEMBLOCK + 7) / 8];
	//signed char ballBlockCheck[(TOTALBALLBLOCK + 7) / 8];
	//signed char soulCheck[1];
	//signed char immune[TOTALDEBUF];
	//signed char type;
	//unsigned char questStatus[TOTALQUEST];
	//unsigned char questExtra[TOTALQUESTREQUEST];
	//unsigned char currentTitle;
	//unsigned char count;
	//unsigned char head;
	//unsigned char moveMode;
	//unsigned char O2;
	//unsigned char fishCount;
	//unsigned char Guild;			//현재가입한길드
	//unsigned char guildCount;		//길드가입횟수
	//unsigned char questItemDetail[32];
	//unsigned char questItemCount[32];

	ROBINDATA robinData[3];
	GAMEDATA gameData;
	OPTION option;
} CHARSAVE;

typedef struct {
	unsigned short index;
	unsigned short icon;		//아이콘
	unsigned short value;	//대표값(무기-공격력, 방어구-방어도 등등
	unsigned char shop;
	unsigned char coupon;
	unsigned char type;
	unsigned char detail;	//세부
	unsigned char grade;
	unsigned char count;
	unsigned char broken;
	unsigned char sale;
	unsigned char hot;
	char length;
	char name[20];
	char desc[60];
} ShopItem;

typedef struct {
	int idx;		//서버상의 인덱스
	int uploader;
	char date[4];	//올라간 날짜
	unsigned int id;
	unsigned short value;	//대표값(무기-공격력, 방어구-방어도 등등
	unsigned short icon;		//아이콘
	unsigned short count;	//갯수(장비인 경우는 소켓의 숫자)
	unsigned short gold;	//가격
	unsigned short cooldown;	//사용효과가 있는 아이템의 쿨다운(장비의 경우 강화레벨)
	unsigned char lv;	//레벨
	unsigned char requireLv;	//요구레벨
	unsigned char requireStat;	//요구스탯
	unsigned char type;		//타입
	unsigned char detail;	//세부
	unsigned char grade;	//등급
	unsigned char broken;	//파괴되었는지
	unsigned char set;	//어떤 세트인지
	unsigned char socket[6];	//소켓
	unsigned char option[12][2];
	signed char name[40];
} ServerItem;

typedef struct {
	int userIdx;
	int nCharCurTitle;	//byte(1)
	int nCharLv;		//byte(1)
	int nCharType;
	int nCharDamage;	//short(2)
	int nCharDefense;	//short(2)
	int nScore;		//int(4)
	char phone[4];
	unsigned char nCharCos[8];
} RANKDEFAULT;

typedef struct {
	int userIdx;	//어떤 유저의 데이터인가
	unsigned short nCharStr;	//short(2)
	signed char nCharSkill[30];
	unsigned char nCharRegist[5];
	unsigned char nCharTitle;
	unsigned short nCharAgi;	//short(2)
	unsigned short nCharInt;	//short(2)
	unsigned short nCharVit;	//short(2)
	unsigned short nCharQuest;
	unsigned short nCharReport;
	unsigned short nCharHp;
	unsigned short nCharMp;
	signed int nCharGold;	//int(4)
	ITEM costume[TOTALEQUIP];
} RANKDETAIL;

//1) PTC_CHARRANKING(클라이언트에서 스토리모드 랭킹전송)				Client -> Server
//nCode	byte(1)	0x10	패킷 구분자
//설명 : 게임도중 보낼 수 있는 클라이언트에서 보내는 스토리 모드용 랭킹 전송입니다. 점수는 이전 전송보다 높을 경우 업데이트합니다
//패킷 전체 크기 : 22Byte

//3) PTC_SURVIVALRANKING(클라이언트에서 서바이벌 랭킹 전송)				Client -> Server
//nCode	byte(1)	0x11	패킷 구분자
//설명 : 투기장 서바이벌 모드에서 보내는 랭킹입니다. 점수는 이전 전송보다 높을 경우 업데이트 합니다.

//5) PTC_TIMERANKING(클라이언트에서 타임어택 랭킹 전송)				Client -> Server
//nCode	byte(1)	0x12	패킷 구분자
//설명 : 투기장 타임어택 모드에서 보내는 랭킹입니다. 점수는 이전 전송보다 높을 경우 업데이트 합니다.
//단 길드전의 경우 길드전 점수는 합산하는 방식을 사용합니다.
//길드전 중 서버에 저장될때 투기장 타임어택 모드 점수는 이전 전송보다 높을 경우 업데이트하고 길드전 점수쪽은 이전 점수에 계속 합산합니다.

//7) PTC_SUDDENRANKING(클라이언트에서 서든데스 랭킹 전송)				Client -> Server
//nCode	byte(1)	0x13	패킷 구분자
//설명 : 투기장 보스모드에서 보내는 랭킹입니다. 점수는 이전 전송보다 높을 경우 업데이트 합니다.

//typedef __packed struct {
//	char nCode;			//byte(1)	0x11	패킷 구분자
//	char nPhoneNum[11];	//전화번호
//	prBlock myData;
//	unsigned char nEnd;	//종료 비트 설정
//} C2S_STORYRANKING;

//2) PTS_CHARRANKING(서버에서 클라이언트로 스토리모드 랭킹 결과 전송)				Server -> Client
//nCode	byte(1)	0x10	패킷 구분자
//설명 : 서버에서 보내는 스토리 모드용 랭킹 전송입니다. 현재 보내는 사람의 랭킹만 보내고 있는데 게임 처리 부분에 따라 자신의 코스튬및 점수도 전송이 가능합니다.
//패킷 전체 크기 : 99Byte
//자신현재랭킹 : select count(*) from MOS4Ranking where storyScore > 자기점수
//랭킹가져오기 : select charCos, phoneNum, charLv, charDamage, charDefense, storySocre from MOS4Ranking order by storyScore desc limit 0, 5

//4) PTS_SURVIVALRANKING(서버에서 클라이언트로 서바이벌 랭킹 결과 전송)				Server -> Client
//nCode	byte(1)	0x11	패킷 구분자
//자신현재랭킹	select count(*) from MOS4Ranking where surScore > 자기점수
//랭킹가져오기	select charCos, phoneNum, charLv, charDamage, charDefense, surSocre from MOS4Ranking order by surScore desc limit 0, 5

//6) PTS_TIMERANKING(서버에서 클라이언트로 타임어택 랭킹 결과 전송)				Server -> Client
//nCode	byte(1)	0x12	패킷 구분자
//자신현재랭킹	select count(*) from MOS4Ranking where timeScore > 자기점수
//랭킹가져오기	select charCos, phoneNum, charLv, charDamage, charDefense, timeSocre from MOS4Ranking order by timeScore desc limit 0, 5

//8) PTS_SUDDENRANKING(서버에서 클라이언트로 서든데스 랭킹 결과 전송)				Server -> Client
//nCode	byte(1)	0x13	패킷 구분자
//자신현재랭킹	select count(*) from MOS4Ranking where suddenScore > 자기점수
//랭킹가져오기	select charCos, phoneNum, charLv, charDamage, charDefense, suddenSocre from MOS4Ranking order by suddenScore desc limit 0, 5

//9) PTC_VIEWRANKING(클라이언트에서 전체 랭킹 조회)				Client -> Server
//nCode	byte(1)	0x14	패킷 구분자
//설명 : 클라이언트에서 랭킹보기로 전체 랭킹을 조회할때 사용합니다.

typedef struct {
	char nCode;			//byte(1)	0x14	패킷 구분자
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	int nCharDamage;	//short(2)
	int nCharDefense;	//short(2)
	unsigned char nCharSkill[TOTALCHARSKILL];
	unsigned char nCharCurTitle;	//byte(1)
	unsigned char nCharTitle;
	unsigned char nCharRegist[6];
	unsigned char nCharLv;		//byte(1)
	unsigned char nCharType;
	unsigned short nCharHp;
	unsigned short nCharMp;
	unsigned short nCharStr;	//short(2)
	unsigned short nCharAgi;	//short(2)
	unsigned short nCharInt;	//short(2)
	unsigned short nCharVit;	//short(2)
	unsigned short nCharQuest;
	unsigned short nCharReport;
	signed int nCharGold;	//int(4)
	int nConnectCount;
	int nScore;		//int(4)
	int nRankStart;
	ITEM costume[TOTALEQUIP];
	char nGuild;
	unsigned char nEnd;				//byte(1)	0x01	종료 비트 설정
} C2S_VIEWRANKING;

//10) PTS_VIEWRANKING(서버에서 클라이언트로 전체 랭킹 결과 전송)				Server -> Client
//nCode	byte(1)	0x14	패킷 구분자

typedef struct {
	char nCode;			//byte(1)	0x14	패킷 구분자
	char dummy[3];
	int myRank;
	int startRank;
	int endRank;

	RANKDEFAULT ranker[10];

	unsigned char nEnd;				//byte(1)	0x01	종료 비트 설정
} S2C_VIEWRANKING;


typedef struct {
	char nCode;			//byte(1)	0x14	패킷 구분자
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	int type;	//어떤 종류의 랭킹인가
	int rank;	//몇등부터 받을 것인가
	unsigned char nEnd;				//byte(1)	0x01	종료 비트 설정
} C2S_ADDRANKING;



typedef struct {
	char nCode;			//byte(1)	0x14	패킷 구분자
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	int userIdx;	//어떤 유저의 데이터인가
	unsigned char nEnd;				//byte(1)	0x01	종료 비트 설정
} C2S_DETAILRANKING;


typedef struct {
	char nCode;			//byte(1)	0x14	패킷 구분자
	char dummy[3];
	RANKDETAIL ranker;
	unsigned char nEnd;				//byte(1)	0x01	종료 비트 설정
} S2C_DETAILRANKING;



//13) PTC_SHOPINFO (클라이언트에서 넷 인벤토리 정보 요청)				Client -> Server
//nCode	byte(1)	0x16	패킷 구분자

typedef struct {
	char nCode;	//byte(1)	0x16	패킷 구분자
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	unsigned char nType;
	unsigned char nEnd;		//byte(1)	0x01	종료 비트 설정
} C2S_SHOPINFO;



//14) PTS_SHOPNFO(서버에서 넷 인벤토리 정보 전송)				Server -> Client
//nCode	byte(1)	0x16	패킷 구분자
//설명 : 서버에서 넷 인벤토리에 들어있는 물품의 정보를 전송합니다. 전송할때 현재 설정된 넷 인벤토리 최대 개수와 넷 인벤토리내 물품의 개수를 같이 보냅니다.
//아이템 정보는 넷 인벤토리내 있는 물품의 개수 만큼 정보를 보냅니다.

//Client 에서 패킷 요청 -> Server에서 넷인벤최대수 가져옴 -> 서버 넷인벤 최대수 만큼 루프를 돌면서
//Client번호의 아이템 정보를 가져옮 이때 iLv > 0이상인것만 가져옴

//넷인벤 최대수	select invenCount from MOS4Ranking where phoneNum = 'clientPhone'
//아이템 정보	select iIndex, iFirst, iLv, iRequireLv, iRequireStat, iName, iIcon, iType, iDetail, iGrade, iBroken, iCount, iCooldown, iSocket, iValue, iOption, iGold, iPreUser from MOS4Inven
//		where iLv > 0 and userNum = (select rIndex from MOS4Ranking where phoneNum = 'clientPhone')
//iFirst초기화	update MOS4Inven set iFirst = 0 where userNum = (select rIndex from MOS4Ranking where phoneNum = 'clientPhone')

typedef struct {
	char nCode;	//byte(1)	0x16	패킷 구분자
	char nSize;	//byte(1)	기본 30 최대 50	넷 인벤토리 최대 개수
	char nCurrentSize;	//byte(1)		넷 인벤토리내 물품 갯수
	char nShopCount;
	ServerItem item[52];
	ShopItem shopItem[48];
	unsigned char nEnd;
} S2C_SHOPINFO;

typedef struct {
	char nCode;	//byte(1)	0x16	패킷 구분자
	char nShopCount;
	char dummy[2];
	ShopItem shopItem[48];
	unsigned char nEnd;
} S2C_SHOPONLYINFO;





//13) PTC_BUYITEM (클라이언트에서 넷 인벤토리 정보 요청)				Client -> Server
//nCode	byte(1)	0x16	패킷 구분자

typedef struct {
	char nCode;	//byte(1)	0x16	패킷 구분자
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	int index;
	unsigned char nEnd;		//byte(1)	0x01	종료 비트 설정
} C2S_BUYITEM;



//12) PTS_CHARGE (서버에서 클라이언트에 과금에 관한 내용을 보낸다)				Server -> Client
//nCode	byte(1)	0x15	패킷 구분자
//현재까지 충전액	select charge from MOS4Ranking where phoneNum = 'clientPhoneNum'
//현재까지 충전액을 가져와서 최대 과금금액보다 작을 경우 충전 성공 패킷을 보낸다.
//충전성공	update MOS4Ranking set charge = charge + 충전액, maxCharge = maxCharge + 충전액 where phoneNum = 'clientPhoneNum'

typedef struct {
	char nCode;			//byte(1)	0x15	패킷 구분자
	char nResult;			//byte(1)	"1: 성공 0: 실패 2: 한도초과 3: 예외(LGT는 임직원단말기)"	과금 결과
	char nItem[30];

	int nCurrentCharge;	//int(4)		현재까지 과금된 금액
	int nMaxCharge;		//int(4)	30000	최대 과금될 수 있는 금액

	unsigned char nCount;
	unsigned char nEnd;				//byte(1)	0x01	종료 비트 설정
} S2C_BUYITEM;



typedef struct {
	char nCode;	//byte(1)	0x16	패킷 구분자
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	int index;
	int id;
	unsigned char type;
	unsigned char nEnd;		//byte(1)	0x01	종료 비트 설정
} C2S_BUYSUCCESS;



//12) PTS_CHARGE (서버에서 클라이언트에 과금에 관한 내용을 보낸다)				Server -> Client
//nCode	byte(1)	0x15	패킷 구분자
//현재까지 충전액	select charge from MOS4Ranking where phoneNum = 'clientPhoneNum'
//현재까지 충전액을 가져와서 최대 과금금액보다 작을 경우 충전 성공 패킷을 보낸다.
//충전성공	update MOS4Ranking set charge = charge + 충전액, maxCharge = maxCharge + 충전액 where phoneNum = 'clientPhoneNum'

typedef struct {
	char nCode;			//byte(1)	0x15	패킷 구분자
	unsigned char nEnd;				//byte(1)	0x01	종료 비트 설정
} S2C_BUYSUCCESS;




//13) PTC_INVENINFO (클라이언트에서 넷 인벤토리 정보 요청)				Client -> Server
//nCode	byte(1)	0x16	패킷 구분자

typedef struct {
	char nCode;	//byte(1)	0x16	패킷 구분자
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	unsigned char nEnd;		//byte(1)	0x01	종료 비트 설정
} C2S_INVENINFO;



//14) PTS_INVENINFO(서버에서 넷 인벤토리 정보 전송)				Server -> Client
//nCode	byte(1)	0x16	패킷 구분자
//설명 : 서버에서 넷 인벤토리에 들어있는 물품의 정보를 전송합니다. 전송할때 현재 설정된 넷 인벤토리 최대 개수와 넷 인벤토리내 물품의 개수를 같이 보냅니다.
//아이템 정보는 넷 인벤토리내 있는 물품의 개수 만큼 정보를 보냅니다.

//Client 에서 패킷 요청 -> Server에서 넷인벤최대수 가져옴 -> 서버 넷인벤 최대수 만큼 루프를 돌면서
//Client번호의 아이템 정보를 가져옮 이때 iLv > 0이상인것만 가져옴

//넷인벤 최대수	select invenCount from MOS4Ranking where phoneNum = 'clientPhone'
//아이템 정보	select iIndex, iFirst, iLv, iRequireLv, iRequireStat, iName, iIcon, iType, iDetail, iGrade, iBroken, iCount, iCooldown, iSocket, iValue, iOption, iGold, iPreUser from MOS4Inven
//		where iLv > 0 and userNum = (select rIndex from MOS4Ranking where phoneNum = 'clientPhone')
//iFirst초기화	update MOS4Inven set iFirst = 0 where userNum = (select rIndex from MOS4Ranking where phoneNum = 'clientPhone')

typedef struct {
	char nCode;	//byte(1)	0x16	패킷 구분자
	char nSize;	//byte(1)	기본 30 최대 50	넷 인벤토리 최대 개수
	short nCurrentSize;	//byte(1)		넷 인벤토리내 물품 갯수
	ServerItem item[52];
	unsigned char nEnd;
} S2C_INVENINFO;



//15) PTC_SENDITEM(클라이언트에서 넷 인벤토리로 장비를 올릴때)				Client -> Server
//nCode	byte(1)	0x17	패킷 구분자

typedef struct {
	char nCode;	//byte(1)	0x17	패킷 구분자
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	ITEM item;
	unsigned char nEnd;		//byte(1)	0x01	종료 비트 설정
} C2S_SENDITEM;



//16) PTS_SENDITEM(서버에서 넷 인벤토리 장비 등록 결과 전송)				Server -> Client
//nCode	byte(1)	0x17	패킷 구분자
//인벤토리 빈곳	select iIndex from MOS4Inven where iLv = 0 and userNum = (select rIndex from MOS4Ranking where phoneNum = 'clientPhone')
//	iIndex 값이 0이면 빈곳이 없으므로 nResult값을 2로 전송한다
//물약같은 아이템의 경우 개수가 여러 개가 되면 하나의 인벤에 여러 개가 같이 들어가니 따로 체크
//넷인벤장비등록	update MOS4Inven set iLv = Lv, iRequireLv = iReLv, iRequireStat = iReStat, iName = name, iIcon = icon, iDetail = detail, iGrade = grade, iBroken = broken, iCount = count
//		iCooldown = cooldown, iSocket = socket, iValue = value, iOption = option, iGold = gold where iIndex = 빈곳

typedef struct {
	char nCode;	//byte(1)	0x17	패킷 구분자
	char nResult;	//byte(1)	1 : 성공 0 : 실패 2 : 인벤부족
	short dummy;

	int nIndex;		//int(4)

	unsigned char nEnd;		//byte(1)	0x01	종료 비트 설정
} S2C_SENDITEM;




//17) PTC_GETITEM(클라이언트가 넷 인벤토리에서 장비를 내릴때)				Client -> Server
//nCode	byte(1)	0x18	패킷 구분자

typedef struct {
	char nCode;	//byte(1)	0x18	패킷 구분자
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	int nIndex;		//int(4)
	unsigned char nEnd;		//byte(1)	0x01	종료 비트 설정
} C2S_GETITEM;



//18) PTS_GETITEM(서버에서 넷 인벤토리 장비를 내려준다)				Server -> Client
//nCode	byte(1)	0x18	패킷 구분자
//설명 : 서버에서 넷인벤토리 장비를 내려준 후 넷 인벤토리 상 장비는 삭제한다
//클라이언트에서 요청한 장비 인덱스에 iLv과 iCount 값을 초기화 한다
//	update MOS4Inven set iLv = 0, iCount = 0 where iIndex = nIndex and userNum = (select rIndex from MOS4Ranking where phoneNum = 'clientPhone')

typedef struct {
	char nCode;	//byte(1)	0x18	패킷 구분자
	char nResult;	//byte(1)	1 : 성공 0 : 실패
	unsigned char nEnd;		//byte(1)	0x01	종료 비트 설정
} S2C_GETITEM;



//19) PTC_PRESENT(클라이언트에서 선물 보내기를 요청한다)				Client -> Server
//nCode	byte(1)	0x19	패킷 구분자
//선물하기의 경우 인벤 한공간에 여러 개를 둘수 있는것과 없는것으로 나뉜다

typedef struct {
	char nCode;		//byte(1)	0x19	패킷 구분자
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	int nIndex;			//int(4)		서버 물품 인덱스
	char nPhone[11];	//char(11)		선물 받을 핸드폰 번호
	unsigned char nEnd;			//byte(1)	0x01	종료 비트 설정
} C2S_PRESENT;



//20) PTS_PRESENT(서버에서 선물 보내기 결과를 전송한다)				Server -> Client
//nCode	byte(1)	0x19	패킷 구분자
//선물받는유저검색	select count(*) from MOS4Ranking where pcs = nPhone			1이면 유저 존재 0이면 없는 사용자
//아이템 정보	select iIndex, iFirst, iLv, iRequireLv, iRequireStat, iName, iIcon, iType, iDetail, iGrade, iBroken, iCount, iCooldown, iSocket, iValue, iOption, iGold from MOS4Inven
//		where iLv > 0 and userNum = (select rIndex from MOS4Ranking where phoneNum = 'clientPhone')
//받는유저인벤갱신	update MOS4Inven set iFirst = 1, iLv = lv, iRequireLv = iReLv, iRequireStat = iReStat, iName = name, iIcon = icon, iType = type, iDetail = detail, iGrade = grade, iBroken = broken,
//		iCount = count, iCooldown = cooldown, iSocket = socket, iValue = value, iOption = option iGold = gold iPreUser = userNum where iIndex = 받는유저의인벤번호
//보낸유저인벤갱신	update MOS4Inven set iLv = 0, iCount = iCount - nCount iPreUser = userNum where iIndex = nIndex and userNum = (select rIndex from MOSRanking where phoneNum = 'clientPhone')

typedef struct {
	char nCode;	//byte(1)	0x19	패킷 구분자
	char nResult;	//byte(1)	1 : 성공 0 : 실패 2 : 사용자X	선물 보낸 결과
	unsigned char nEnd;		//byte(1)	0x01	종료 비트 설정
} S2C_PRESENT;



//21) PTC_SENDCHARACTOR (클라이언트에서 캐릭터 정보를 백업한다)				Client -> Server
//byte(1)	0x20	패킷 구분자

typedef struct {
	char nCode;	//byte(1)	0x20	패킷 구분자
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	int size;
	int index;
	char data[36864];
	unsigned char nEnd;		//byte(1)	0x01	종료 비트 설정
} C2S_SENDCHARACTOR;



//22) PTS_SENDCHARACTOR (서버에서 캐릭터 백업 결과를 전송한다)				Server -> Client
//byte(1)	0x20	패킷 구분자
//캐릭터 백업	update MOS4Ranking set saveChar = nData where phoneNum = 'clientPhoneNum'

typedef struct {
	char nCode;	//byte(1)	0x20	패킷 구분자
	char nResult;	//byte(1)	1 : 성공 0 : 실패
	unsigned char nEnd;		//byte(1)	0x01	종료 비트 설정
} S2C_SENDCHARACTOR;



//23) PTC_GETCHARACTOR (클라이언트가 서버에 백업된 캐릭터를 받아온다)				Client -> Server
//byte(1)	0x21	패킷 구분자

typedef struct {
	char nCode;	//byte(1)	0x21	패킷 구분자
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	int size;
	unsigned char nEnd;		//byte(1)	0x01	종료 비트 설정
} C2S_GETCHARACTOR;



//24) PTS_GETCHARACTOR (서버에서 백업된 캐릭터 전송 결과를 보내준다)
//byte(1)	0x21	패킷 구분자
//캐릭터정보받기	select saveChar from MOS4Ranking where phoneNum = 'clientPhoneNum'

typedef struct {
	char nCode;	//byte(1)	0x21	패킷 구분자
	char nResult;	//byte(1)	1 : 성공 0 : 실패 2 : 정보없음
	char dummy[2];
	int offset[4];
	char data[36864];
	unsigned char nEnd;		//byte(1)	0x01	종료 비트 설정
} S2C_GETCHARACTOR;



//23) PTC_SCREENSHOT
//byte(1)	0x21	패킷 구분자

typedef struct {
	char nCode;	//byte(1)	0x21	패킷 구분자
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	short dx;
	short dy;
	int size;
	short data[176 * 220];
	unsigned char nEnd;
} C2S_SCREENSHOT;



//24) PTS_GETCHARACTOR (서버에서 백업된 캐릭터 전송 결과를 보내준다)
//byte(1)	0x21	패킷 구분자
//캐릭터정보받기	select saveChar from MOS4Ranking where phoneNum = 'clientPhoneNum'

typedef struct {
	char nCode;	//byte(1)	0x21	패킷 구분자
	char nResult;	//byte(1)	1 : 성공 0 : 실패 2 : 정보없음
	char fileName[24];
	unsigned char nEnd;		//byte(1)	0x01	종료 비트 설정
} S2C_SCREENSHOT;






//25) PTC_NOTICE (클라이언트에서 공지사항을 받아온다)				Client -> Server
//byte(1)	0x22	패킷 구분자
//설명 : 메인 공지사항은 1번부터 시작하고 투기장용 공지사항은 10번부터 시작

typedef struct {
	char nCode;	//byte(1)	0x22	패킷 구분자
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	char nIndex;	//byte(1)	1 : 메인공지 10 : 투기장공지
	unsigned char nEnd;		//byte(1)	0x01	종료 비트 설정
} C2S_NOTICE;

//26) PTS_NOTICE (서버에서 클라이언트에 공지사항을 전송한다)				Server -> Client
//byte(1)	0x22	패킷 구분자
//설명 : nNext값으로 다음 공지사항이 있는지 확인한다 다음 공지사항이 있으면 공지사항 번호를 넘겨주고
//클라이언트는 받은 공지사항 번호를 nIndex에 넣어서 다시 서버에 전송한다
//단 다음 공지사항이 없을경우 nNext값은 0을 전송한다.
//공지받기	select nBody from MOS4Notice where nIndex = nIndex
//다음공지 확인	select count(*) from MOS4Notice where nIndex = (nIndex + 1)			값이 1이면 다음 공지 있음
//만일 공지사항이 투기장 공지일 경우 10번은 자신의 길드 정보를 전송한다
//전체길드포인트	select gPoint, gName from MOS4Guild where gIndex = (select guildNum from MOS4Ranking where phoneNum = 'clientPhoneNum')
//자기길드포인트	select guildScore from MOS4Ranking where phoneNum = 'clientPhoneNum'
//전송내용	OO 길드의 총 포인트는 OO 점이고 OOOO님이 올리신 총 포인트는 OO점입니다.

typedef struct {
	unsigned char nLen;			//byte(1)		다음 공지사항번호
	char nBody[255];	//char(255)		공지사항내요
	unsigned char nEnd;
} S2C_NOTICE;


//PTC_ERASEITEM
typedef struct {
	char nCode;	//byte(1)	0x22	패킷 구분자
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	int nCount;	//지워야 할 아이템의 갯수

	int eIndex[10];	//지울 아이템 인덱스

	unsigned char nEnd;		//byte(1)	0x01	종료 비트 설정
} C2S_ERASEITEM;


//PTS_ERASEITEM
typedef struct {
	char nCode;			//byte(1)	0x22	패킷 구분자
	char nSuccess;
	unsigned char nEnd;				//byte(1)	0x01	종료 비트 설정
} S2C_ERASEITEM;

typedef struct {
	char nCode;
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	unsigned char nEnd;
} C2S_SERVERCLOSE;

typedef struct {
	char nCode;
	char nSuccess;
	unsigned char nEnd;
} S2C_SERVERCLOSE;


typedef struct {
	char nCode;
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	unsigned char nEnd;
} C2S_AGREE;

typedef struct {
	char nCode;
	char nLength;
	char nBody[255];
	unsigned char nEnd;
} S2C_AGREE;


typedef struct {
	char nCode;
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	unsigned char nEnd;
} C2S_VERIFY;

typedef struct {
	char nCode;
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	int nType;	//어떤 타입인가
	unsigned char nEnd;
} C2S_VERIFY2;

typedef struct {
	char nCode;
	char nResult;
	char nLength;
	char nBody[100];
	unsigned char nEnd;
} S2C_VERIFY;


typedef struct {
	char nCode;
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	unsigned int nIndex;
	unsigned char nEnd;
} C2S_FILE;



typedef struct {
	char nCode;
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	unsigned char nEnd;
} C2S_DAILYGET;

typedef struct {
	char nCode;
	char questType;
	char questDetail;
	char questCount;
	char questName[32];
	char questDesc[240];
	char rewardType;
	char rewardDetail;
	char rewardGrade;
	char rewardCount;
	char questDetail2;
	char questIndex;
	unsigned char nEnd;
} S2C_DAILYGET;

typedef struct {
	char nCode;
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	unsigned char guildNum;
	unsigned char questIndex;
	unsigned char nEnd;
} C2S_DAILYEND;

typedef struct {
	char nCode;
	char nFlag;
	char nNextMon;
	char nNextDay;
	char nNextTime1;
	char nNextTime2;
	char length;
	char data;
	unsigned char nEnd;
} S2C_GUILDSTART;

typedef struct {
	char nCode;
	char lastWinGuild;
	char rewardItemType;
	char rewardItemDetail;

	int goldReward;
	int score[4];

	char rewardItemCount;
	char canReward;
	char myRank;
	char length;
	char data;
	unsigned char nEnd;
} S2C_GUILDCURRENT;

typedef struct {
	char nCode;
	char week;
	char dummy[2];

	int score[16];

	char length;
	char data;

	unsigned char nEnd;
} S2C_GUILDRECORD;



typedef struct {
	char nCode;
	char nPhoneNum[11];	//전화번호
	int nVersion;//버전
	char receiver[12];
	unsigned char nEnd;
} C2S_RECOMMEND;

typedef struct {
	char nCode;
	char nResult;
	unsigned char nEnd;
} S2C_RECOMMEND;



typedef struct _netItemData {
	int idx;
	char phone[4];
	char date[4];
} NETITEMDATA;


#ifdef ASSA
typedef struct _assa_out_Data {
	short length;
	short command;
	short data;
	short dummy;
} ASSA_OUT_DATA;

typedef struct _assa_in_Data {
	short length;
	short command;
	signed char result;
	char data[900];
} ASSA_IN_DATA;
#endif

#ifdef SKT
#include		"GXGNet.h"

// 디버깅 설정
//#define		GXG_DEBUG_MODE


/* == == == == == == == == == == == == == == == == == == == == == ===
			테스트를 위한 사용자 모드
= == == == == == == == == == == == == == == == == == == == == == ===*/


/* == == == == == == == == == == == == == == == == == == == == == ===
			프로그램 상태 정보
= == == == == == == == == == == == == == == == == == == == == == ===*/
#define _MCID								"0080597903"	///< Master ID
//#define _MCID								"0070270220"	///< Master ID

#ifdef TESTBILL
#define USE_DOMAIN						false
#define GXG_GW_SERVER_ADDRESS	"211.39.23.212"	///< GXG 게이트웨이 접속 주소
#define GXG_GW_SERVER_PORT		8004					///< GXG 게이트웨이 접속 포트
#else
#define USE_DOMAIN						true
#define GXG_GW_SERVER_ADDRESS	"ngw.gxg.com"	///<	GXG 게이트웨이 접속 도메인
#define GXG_GW_SERVER_PORT		7300					///< GXG 게이트웨이 접속 포트
#endif

/* == == == == == == == == == == == == == == == == == == == == == ===
		요금제 구입 관련 상태 정보
= == == == == == == == == == == == == == == == == == == == == == ===*/
typedef enum GXG_BUY_UI_STATE
{
	UI_BUY_INFO_1 = 1,				///< 구매 info 출력 1
	UI_BUY_INFO_2,					///< 구매 info 출력 2
	UI_BUY_CONFIRM,					///< 구매 확인
	UI_BUY_OK,						///< 구매 완료
	UI_BUY_WAIT,					///< 구매 요청 후 대기상태
	UI_BUY_WAIT2					///< 구매 요청 후 대기상태2
} gxgBuyUIState;

GXG_InitConfirm				g_InitCfm;		//인증 결과
GXG_Confirm					g_Confirm;		//과금, 서버변경 결과
GXG_PricingQueryConfirm	g_QueryCfm;	//요금제 조회 결과
GXG_PricingBuyConfirm		g_BuyCfm;		//요금제 구매 결과
GXG_Header					g_Header;		//GXG 헤더를 넘겨 받을 구조체

void ConnectCB(int type, int err, void *param);
void GXGLibCB(int type, int err, int errParam, void *param);

#else


#define EMERGENCY		10

//Timer* rtimer;
int sockFD, bNetConnected, bSockConnected;
int netFrame;
int net_Offset;
int net_RemainSize;
char size_recevied;

void OpenSocket(void);
void ConnectCB(int error, void *param);
#ifdef LGT
void SocketConnectCB(int fd, int error, void *param);
#else
void SocketConnectCB(int error, void *param);
#endif
int SendPacket(void);
int SendPacket0(void);
static void SockWriteCB(int fd, int error, void *param);
int RecvPacket0(int cmd);
static void SockReadCB(int fd, int error, void *param);
//void ReceiveTimer(Timer *ptm, void *param);
int ConvertToINAddr(char *psz);

#endif


#define BP_SERVER_IP					"211.55.29.156"	///< BP 서버 접속 주소

#ifdef TESTBILL
#define BP_SERVER_PORT				1245					///< BP 서버 접속 포트
#define BP_SAVE_PORT					1246
#define BILLCOMMMODE		"TEST_BILLSOCK"

#else
#define BP_SERVER_PORT				1242					///< BP 서버 접속 포트
#define BP_SAVE_PORT					1246
#define BILLCOMMMODE		NULL
#endif





char netStatus;
char netType;
unsigned int nDataLen;
int nBuff_Send;
int nBuff_Recv;
int nBuff_Screen;
int screenOffset;
int screenRemain;
//Timer ntimer, stimer;
NETITEMDATA NetItemData[MAXNETINVEN];
int needErase[10];
int eraseCnt;
char chargeStatus;
char showNotice;
char couponBilled;


#ifdef DOWNLOAD
unsigned short curFile;
unsigned int receiveSize;
#endif


RANKDEFAULT ranker[10];
RANKDETAIL rankerDetail;
int rankRecent[16];



void SetData(int type);
void GotoNetwork(int type);
void Close(bool bConnected, bool bPPPClose);
void Connect(void);
void NetError(int err);
void Authorize(void);
void Charge(int cPkt);
void SendData(void);
void ReceiveData(void);
void ResultData(void);
void AfterCharge(void);
void AfterCharge2(void);
//void NetTimer(Timer *ptm, void *param);
//void ScreenTimer(Timer *ptm, void *param);
void NetConnectDraw(void);

#endif