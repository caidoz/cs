#pragma once

#ifndef _IAPCONFIG_H_
#define _IAPCONFIG_H_

//=============================================================================
// 결제 설정
//
// 상품이 무엇을 주는지는 여기 없다. 서버의 product 표에 있다.
// 여기 있는 것은 "어떤 상품을 파는가" 와 "화면에 뭐라고 적는가" 뿐이다.
//
// 지급량을 클라이언트에 두면, 그 값을 고친 빌드가 서버에 "천만 개짜리를
// 샀다" 고 말할 수 있다. 서버는 상품 ID 만 받고 나머지는 자기가 정한다.
//=============================================================================

//결제를 켤 것인가.
//
//0 이면 상점의 현금 상품이 안 보이고, IapBuy() 는 아무것도 안 한다.
//스토어 등록과 영수증 검증이 끝나기 전에는 0 이어야 한다.
//
//★ 출시 전에 확인할 것: 서버의 영수증 검증(server/go/purchase.go 의
//   Verifier)이 아직 다 통과시키는 상태다. 그걸 붙이기 전에 이 값을 1 로
//   두면 아무나 아무 상품이나 받아간다.
#define IAP_ENABLED 1

//시험용 가짜 스토어.
//
//1 이면 진짜 스토어 대신 클라이언트 안의 흉내내기가 답한다. 실기 없이
//결제 흐름 전체(대기 장부, 재시도, 서버 지급)를 돌려볼 수 있다.
//win32 에는 스토어가 없으므로 여기서는 늘 이쪽이다.
#if defined(WIN32) || defined(_WIN32)
	#define IAP_FAKESTORE 1
#else
	#define IAP_FAKESTORE 0
#endif

//가짜 스토어가 답하는 데 걸리는 시간(프레임). 진짜 결제도 시간이 걸린다.
//그 사이에 앱을 끄는 시험을 하려면 눈에 보일 만큼 길어야 한다.
enum {
	IAP_FAKEDELAY = 90,		//60프레임 = 1초
};

//대기 장부 파일. 스토어에 값을 내기 전에 여기 적고, 서버가 지급한 뒤에
//지운다. 이 파일이 있다는 것은 "돈은 나갔을 수 있는데 아직 못 받았다"는
//뜻이다. 부팅할 때마다 확인한다.
#define IAP_JOURNALFILE	"purchase.dat"

//한 번에 들고 있을 수 있는 대기 건수.
//
//보통 1 이다. 여러 개가 쌓이는 것은 서버에 계속 못 붙는 동안 사용자가
//계속 사는 경우인데, 그때도 잃지는 않아야 한다.
enum {
	IAP_MAXPENDING = 8,
};

//다시 보내기까지 기다리는 시간(프레임).
enum {
	IAP_RETRYWAIT = 60 * 10,
};

//패스가 무엇을 해주는가.
//
//서버가 주는 것은 "언제까지" 하나뿐이다(player.heart_pass_ts). 그 기간에
//무엇이 달라지는지는 게임이 정한다 - 값이 아니라 규칙이라 클라이언트에 둔다.
//
//서버가 지급량을 쥐는 것과 어긋나 보이지만 다르다. 지급량은 돈과 바로
//바꾸는 값이라 속이면 이득이 되고, 이 배율은 기간 안에서만 도는 규칙이라
//고쳐봐야 기간이 늘지 않는다. 기간은 서버가 쥐고 있다.
enum {
	//하트 패스 : 상한 +50, 회복 2배
	HEARTPASS_MAXBONUS = 50,
	HEARTPASS_REGENMUL = 2,

	//성장 패스 : 전투 골드 +20%
	GROWTHPASS_GOLDPER = 20,
};

//상품 목록.
//
//문자열은 스토어(App Store Connect / Play Console)에 등록한 상품 ID 와
//글자 하나까지 같아야 한다. 서버의 product 표의 product_id 와도 같다.
//셋이 어긋나면 결제는 되고 지급이 안 된다 — 제일 나쁜 고장이다.
//서버의 product 표와 글자 하나까지 같아야 한다.
//서버의 product 표, 그리고 스토어에 등록할 ID 와 글자 하나까지 같아야 한다.
//
//셋째 칸은 스토어가 답하기 전에 띄울 이름이다. 스토어가 답하면 그쪽
//이름으로 바뀐다 - 나라마다 다른 말로 보여야 하기 때문이다.
//서버의 product 표, 그리고 스토어에 등록할 ID 와 글자 하나까지 같아야 한다.
//
//셋째 칸은 스토어가 답하기 전에 띄울 이름이다. 스토어가 답하면 그쪽
//이름으로 바뀐다 - 나라마다 다른 말로 보여야 하기 때문이다.
//
//넷째 칸은 카드에 그릴 아이콘이다(Def/IconDef.h). 상품 그림을 따로
//그리기 전까지 게임에 있는 아이콘을 빌려 쓴다.
#define IAP_PRODUCT_LIST \
	X(IAP_COIN_01,     "coin_01",        "코인 1,000",        ICON_GOLDBAG) \
	X(IAP_COIN_02,     "coin_02",        "코인 2,200",        ICON_GOLDBAG) \
	X(IAP_COIN_03,     "coin_03",        "코인 6,000",        ITEM_GOLDBAR_ICON) \
	X(IAP_COIN_04,     "coin_04",        "코인 25,000",       ITEM_GOLDBAR_ICON) \
	X(IAP_COIN_05,     "coin_05",        "코인 65,000",       ITEM_GOLDBAR_ICON) \
	X(IAP_COIN_06,     "coin_06",        "코인 140,000",      ITEM_GOLDBAR_ICON) \
	X(IAP_HEART_01,    "heart_01",       "하트 100",          ICON_HEART) \
	X(IAP_HEART_02,    "heart_02",       "하트 300",          ICON_HEART) \
	X(IAP_HEART_03,    "heart_03",       "하트 1,000",        ICON_HEART) \
	X(IAP_HEART_04,    "heart_04",       "하트 5,000",        ICON_HEART) \
	X(IAP_HEART_05,    "heart_05",       "하트 15,000",       ICON_HEART) \
	X(IAP_HEART_06,    "heart_06",       "하트 50,000",       ICON_HEART) \
	X(IAP_CASH_01,     "cash_01",        "캐시 코인 60",      ICON_STAR) \
	X(IAP_CASH_02,     "cash_02",        "캐시 코인 180",     ICON_STAR) \
	X(IAP_CASH_03,     "cash_03",        "캐시 코인 600",     ICON_STAR) \
	X(IAP_CASH_04,     "cash_04",        "캐시 코인 1,500",   ICON_STAR) \
	X(IAP_CASH_05,     "cash_05",        "캐시 코인 3,500",   ICON_STAR) \
	X(IAP_CASH_06,     "cash_06",        "캐시 코인 8,000",   ICON_STAR) \
	X(IAP_PASS_HEART,  "pass_heart_30",  "하트 패스 30일",       ICON_HEART) \
	X(IAP_PASS_GROWTH, "pass_growth_30", "성장 패스 30일",       ICON_CROWN) \
	X(IAP_STARTER,     "starter",        "초심자 패키지",         ITEM_GACHABOX_ICON) \
	X(IAP_INVEN_20,    "inven_20",       "가방 +20칸",         ITEM_SHOP_ICON)

//상품 번호.
//
//목록과 같은 자리에 둔다. TouchKeyDef.h 가 상품 개수만큼 터치 자리를
//잡아야 해서, Func_Iap.h 보다 앞에서 알 수 있어야 한다.
#define X(name, id, label, icon)	name,
typedef enum _iapProduct {
	IAP_PRODUCT_LIST
	TOTALIAPPRODUCT,
} IAPPRODUCTDEF;
#undef X

#endif
