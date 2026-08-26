#include "Core.h"
#include "Data.h"
#include "Func.h"
#include "Config/IapConfig.h"

//=============================================================================
// 대기 장부
//
// 이 파일에서 제일 중요한 부분이다. 나머지는 이 장부를 채우고 비우는 일이다.
//
// 규칙은 둘.
//   - 스토어에 값을 내기 전에 적는다.
//   - 서버가 "끝났다"고 답해야 지운다.
//
// 그래서 어느 지점에서 앱이 죽어도 장부가 남고, 다음 부팅이 이어서 한다.
// 장부가 비어 있지 않다는 것은 "돈은 나갔을 수 있는데 아직 못 받았다" 는
// 뜻이다.
//
// 파일 형식은 덤프와 같은 결이다. 탭으로 나누고, 값 안의 탭과 줄바꿈은
// 죽여서 넣는다. 영수증이 무엇을 담고 있을지 모르기 때문이다.
//=============================================================================

typedef struct _iapPending {
	int state;					//IAPSTATE_*
	int product;				//상품 번호
	std::string orderId;		//스토어가 준 거래 ID
	std::string receipt;		//스토어가 준 영수증
	long startTime;				//시작한 시각. 오래된 것을 알아보려고.
} IAPPENDING;

static IAPPENDING sPending[IAP_MAXPENDING];
static int sPendingCnt = 0;

static int sResult = IAPRESULT_NONE;
static int sResultProduct = -1;
static int sRetryWait = 0;
static int sSending = -1;		//지금 서버에 보내는 중인 대기 번호. 없으면 -1

//상품 문자열 표.
#define X(name, id)		id,
static const char* sProductId[TOTALIAPPRODUCT] = {
	IAP_PRODUCT_LIST
};
#undef X

const char* IapProductId(int product)
{
	if (product < 0 || product >= TOTALIAPPRODUCT)
		return "";

	return sProductId[product];
}

static int IapProductByIdStr(const std::string& id)
{
	int i;

	for (i = 0; i < TOTALIAPPRODUCT; i++) {
		if (id == sProductId[i])
			return i;
	}

	return -1;
}

//---- 파일 ----

static std::string IapPath(const char* name)
{
	return cocos2d::FileUtils::getInstance()->getWritablePath() + name;
}

static std::string IapEscape(const std::string& s)
{
	std::string out;
	size_t i;

	for (i = 0; i < s.size(); i++) {
		switch (s[i]) {
		case '\\': out += "\\\\"; break;
		case '\t': out += "\\t"; break;
		case '\n': out += "\\n"; break;
		case '\r': out += "\\r"; break;
		default:   out += s[i]; break;
		}
	}

	return out;
}

static std::string IapUnescape(const std::string& s)
{
	std::string out;
	size_t i;

	for (i = 0; i < s.size(); i++) {
		if (s[i] != '\\' || i + 1 >= s.size()) {
			out += s[i];
			continue;
		}

		i++;

		switch (s[i]) {
		case 't': out += '\t'; break;
		case 'n': out += '\n'; break;
		case 'r': out += '\r'; break;
		default:  out += s[i]; break;
		}
	}

	return out;
}

//장부를 쓴다. 원자적으로 바꾼다 — 쓰다 만 장부는 없는 것만 못하다.
static bool IapSaveJournal(void)
{
	std::string text = "#iap\t1\n";
	std::string tmp = IapPath(IAP_JOURNALFILE ".new");
	std::string dst = IapPath(IAP_JOURNALFILE);
	char line[128];
	int i;

	//빈 장부는 파일을 지운다. 남겨두면 부팅마다 읽고 버리는 일을 한다.
	if (sPendingCnt == 0) {
		remove(dst.c_str());
		return true;
	}

	for (i = 0; i < sPendingCnt; i++) {
		sprintf(line, "%d\t%d\t%ld\t", sPending[i].state, sPending[i].product,
			sPending[i].startTime);

		text += line;
		text += IapEscape(sPending[i].orderId);
		text += "\t";
		text += IapEscape(sPending[i].receipt);
		text += "\n";
	}

	FILE* fp = fopen(tmp.c_str(), "wb");

	if (!fp) {
		CCLOG("Iap: 장부를 못 연다 %s", tmp.c_str());
		return false;
	}

	if (fwrite(text.c_str(), 1, text.size(), fp) != text.size()) {
		fclose(fp);
		remove(tmp.c_str());
		CCLOG("Iap: 장부를 다 못 썼다");
		return false;
	}

	fflush(fp);
	fclose(fp);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	remove(dst.c_str());
#endif

	if (rename(tmp.c_str(), dst.c_str()) != 0) {
		remove(tmp.c_str());
		CCLOG("Iap: 장부 rename 실패");
		return false;
	}

	return true;
}

static void IapLoadJournal(void)
{
	std::string path = IapPath(IAP_JOURNALFILE);
	std::string text;

	sPendingCnt = 0;

	FILE* fp = fopen(path.c_str(), "rb");

	if (!fp)
		return;

	char buf[4096];
	size_t n;

	while ((n = fread(buf, 1, sizeof(buf), fp)) > 0)
		text.append(buf, n);

	fclose(fp);

	//줄 단위로 읽는다. 첫 줄은 머리다.
	size_t at = 0;

	while (at < text.size() && sPendingCnt < IAP_MAXPENDING) {
		size_t end = text.find('\n', at);

		if (end == std::string::npos)
			end = text.size();

		std::string line = text.substr(at, end - at);
		at = end + 1;

		if (line.empty() || line[0] == '#')
			continue;

		//state \t product \t startTime \t orderId \t receipt
		std::string f[5];
		size_t p = 0;
		int i;

		for (i = 0; i < 5; i++) {
			size_t t = line.find('\t', p);

			if (i == 4 || t == std::string::npos) {
				f[i] = line.substr(p);
				break;
			}

			f[i] = line.substr(p, t - p);
			p = t + 1;
		}

		IAPPENDING* e = &sPending[sPendingCnt];

		e->state = atoi(f[0].c_str());
		e->product = atoi(f[1].c_str());
		e->startTime = atol(f[2].c_str());
		e->orderId = IapUnescape(f[3]);
		e->receipt = IapUnescape(f[4]);

		if (e->product < 0 || e->product >= TOTALIAPPRODUCT) {
			CCLOG("Iap: 모르는 상품이 장부에 있다 (%d). 버린다", e->product);
			continue;
		}

		//물어보던 중에 죽었으면 결과를 모른다. 스토어에 다시 물어야 하는데
		//그 길은 스토어 붙일 때 만든다. 지금은 남겨두고 사람이 보게 한다.
		sPendingCnt++;
	}

	if (sPendingCnt > 0)
		CCLOG("Iap: 아직 못 받은 결제가 %d건 있다", sPendingCnt);
}

static void IapRemovePending(int idx)
{
	int i;

	if (idx < 0 || idx >= sPendingCnt)
		return;

	for (i = idx; i < sPendingCnt - 1; i++)
		sPending[i] = sPending[i + 1];

	sPendingCnt--;
	IapSaveJournal();
}

//=============================================================================
// 스토어
//
// 진짜 스토어는 플랫폼마다 다르다(StoreKit, Play Billing). 그 둘을 여기서
// 갈라 쓰지 않고, 아래 세 함수만 맞춰 두면 위쪽은 안 바뀌게 한다.
//
//   IapStoreBuy()   결제를 시작한다
//   IapStorePoll()  끝났는지 본다
//   IapStoreDone()  다 받았다고 스토어에 알린다 (소비 처리)
//
// IapStoreDone() 이 중요하다. 이걸 안 부르면 스토어가 "아직 안 끝난 결제"로
// 알고 다음 실행마다 다시 내놓는다. 반대로 서버 지급 전에 부르면, 그 사이
// 앱이 죽었을 때 결제가 영영 사라진다. 그래서 서버가 답한 뒤에 부른다.
//
// 지금 들어 있는 것은 흉내내기다. 실기 없이 흐름 전체를 돌려보려고 둔다.
//=============================================================================

#if IAP_FAKESTORE

static int sFakeFrame = 0;
static int sFakeProduct = -1;

static bool IapStoreBuy(int product)
{
	sFakeProduct = product;
	sFakeFrame = IAP_FAKEDELAY;

	CCLOG("Iap(가짜): %s 결제 시작", IapProductId(product));

	return true;
}

//아직이면 IAPRESULT_NONE. 끝났으면 결과와 함께 orderId/receipt 를 채운다.
static int IapStorePoll(std::string& orderId, std::string& receipt)
{
	char buf[64];

	if (sFakeProduct < 0)
		return IAPRESULT_NONE;

	if (sFakeFrame > 0) {
		sFakeFrame--;
		return IAPRESULT_NONE;
	}

	//거래 ID 는 스토어가 준다. 흉내내기는 시각과 난수로 만든다. 같은 값이
	//두 번 나오면 서버가 "이미 준 것"으로 보고 안 준다. 그건 진짜 스토어의
	//동작과 같으므로 흉내로서도 맞다.
	sprintf(buf, "fake-%ld-%d", (long)MC_knlCurrentTimeStamp(), Random(100000));

	orderId = buf;
	receipt = "fake-receipt";
	sFakeProduct = -1;

	CCLOG("Iap(가짜): 결제됐다 order=%s", orderId.c_str());

	return IAPRESULT_OK;
}

static void IapStoreDone(const std::string& orderId)
{
	CCLOG("Iap(가짜): 소비 처리 order=%s", orderId.c_str());
}

#else

//진짜 스토어. 아직 안 붙였다.
//
//붙일 때 여기만 채우면 위쪽은 한 줄도 안 바뀐다. iOS 는 SKPaymentQueue,
//안드로이드는 BillingClient 다. 둘 다 콜백으로 오므로 그 결과를 받아
//IapStorePoll() 이 읽을 수 있는 자리에 놓아 두는 식이 된다.
static bool IapStoreBuy(int product)
{
	CCLOG("Iap: 스토어가 아직 안 붙었다");
	return false;
}

static int IapStorePoll(std::string& orderId, std::string& receipt)
{
	return IAPRESULT_NONE;
}

static void IapStoreDone(const std::string& orderId)
{
}

#endif

//=============================================================================
// 흐름
//=============================================================================

void IapInit(void)
{
	sResult = IAPRESULT_NONE;
	sResultProduct = -1;
	sSending = -1;
	sRetryWait = 0;

	IapLoadJournal();
}

bool IapIsBusy(void)
{
	int i;

	for (i = 0; i < sPendingCnt; i++) {
		if (sPending[i].state == IAPSTATE_ASKING)
			return true;
	}

	return false;
}

int IapPendingCount(void)
{
	return sPendingCnt;
}

int IapTakeResult(void)
{
	int got = sResult;

	sResult = IAPRESULT_NONE;

	return got;
}

int IapLastProduct(void)
{
	return sResultProduct;
}

bool IapBuy(int product)
{
#if !IAP_ENABLED
	CCLOG("Iap: 결제가 꺼져 있다 (IapConfig.h 의 IAP_ENABLED)");
	return false;
#else
	if (product < 0 || product >= TOTALIAPPRODUCT)
		return false;

	//한 번에 하나만. 두 개를 동시에 걸면 어느 답이 어느 것인지 헷갈린다.
	if (IapIsBusy())
		return false;

	if (sPendingCnt >= IAP_MAXPENDING) {
		CCLOG("Iap: 대기가 %d건이라 더 못 받는다", sPendingCnt);
		return false;
	}

	//----------------------------------------------------------------------
	// 스토어를 부르기 전에 적는다.
	//
	// 순서가 뒤집히면 안 된다. 스토어를 먼저 부르고 적으려 하면, 그 사이에
	// 앱이 죽었을 때 결제는 됐는데 아무 기록도 없는 상태가 된다.
	//----------------------------------------------------------------------
	IAPPENDING* e = &sPending[sPendingCnt];

	e->state = IAPSTATE_ASKING;
	e->product = product;
	e->orderId.clear();
	e->receipt.clear();
	e->startTime = (long)MC_knlCurrentTimeStamp();

	sPendingCnt++;

	if (!IapSaveJournal()) {
		//장부를 못 적었으면 시작하지 않는다. 적지 못한 채로 사면 잃는다.
		sPendingCnt--;
		CCLOG("Iap: 장부를 못 적어 결제를 시작하지 않는다");
		return false;
	}

	if (!IapStoreBuy(product)) {
		sPendingCnt--;
		IapSaveJournal();
		return false;
	}

	return true;
#endif
}

//서버에 보낼 것을 하나 고른다. 오래 기다린 것부터.
static int IapPickToSend(void)
{
	int i;

	for (i = 0; i < sPendingCnt; i++) {
		if (sPending[i].state == IAPSTATE_BOUGHT)
			return i;
	}

	return -1;
}

void IapUpdate(void)
{
	std::string orderId, receipt;
	int i;

	//---- 1. 스토어 답 ----
	if (IapIsBusy()) {
		int got = IapStorePoll(orderId, receipt);

		if (got != IAPRESULT_NONE) {
			for (i = 0; i < sPendingCnt; i++) {
				if (sPending[i].state != IAPSTATE_ASKING)
					continue;

				if (got == IAPRESULT_OK) {
					//----------------------------------------------------
					// 돈이 나갔다. 이 순간부터는 반드시 줘야 한다.
					//
					// 장부부터 고친다. 서버에 보내는 것은 그 다음이다.
					// 여기서 죽어도 다음 부팅이 이어서 보낸다.
					//----------------------------------------------------
					sPending[i].state = IAPSTATE_BOUGHT;
					sPending[i].orderId = orderId;
					sPending[i].receipt = receipt;

					IapSaveJournal();
				}
				else {
					//취소나 실패다. 돈이 안 나갔으므로 장부에서 지운다.
					sResult = got;
					sResultProduct = sPending[i].product;

					IapRemovePending(i);
				}

				break;
			}
		}
	}

	//---- 2. 서버에 보내기 ----
	if (sSending >= 0) {
		//답을 기다리는 중이다.
		if (NetLastRequest() != NETREQ_PURCHASE || NetIsBusy())
			return;

		int res = NetLastResult();
		const char* state = NetTakePurchaseState();
		int idx = sSending;

		sSending = -1;

		if (idx >= sPendingCnt)
			return;

		if (res == NETRESULT_OK && state[0]) {
			//------------------------------------------------------------
			// 서버가 답했다. granted 든 rejected 든 "그 거래는 끝났다".
			//
			// 거절도 장부에서 지운다. 안 지우면 영영 다시 보낸다. 다만
			// 사용자에게는 알려야 한다 — 돈이 나갔을 수 있기 때문이다.
			//------------------------------------------------------------
			bool ok = (strcmp(state, "granted") == 0);

			IapStoreDone(sPending[idx].orderId);

			sResult = ok ? IAPRESULT_OK : IAPRESULT_REJECT;
			sResultProduct = sPending[idx].product;

			CCLOG("Iap: %s -> %s", IapProductId(sPending[idx].product), state);

			IapRemovePending(idx);
		}
		else {
			//못 붙었다. 장부는 그대로 두고 나중에 다시 보낸다.
			sPending[idx].state = IAPSTATE_BOUGHT;
			sRetryWait = IAP_RETRYWAIT;

			CCLOG("Iap: 서버에 못 보냈다. %d초 뒤에 다시 한다",
				IAP_RETRYWAIT / FPS);
		}

		return;
	}

	if (sRetryWait > 0) {
		sRetryWait--;
		return;
	}

	//보낼 것이 있으면 보낸다. 다른 요청이 도는 중이면 다음 프레임에.
	i = IapPickToSend();

	if (i < 0 || NetIsBusy())
		return;

	if (!NetPurchaseBegin(NetPlatformName(), IapProductId(sPending[i].product),
		sPending[i].orderId.c_str(), sPending[i].receipt.c_str())) {
		return;
	}

	sPending[i].state = IAPSTATE_SENDING;
	sSending = i;
}
