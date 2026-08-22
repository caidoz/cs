#pragma once
#include "Core.h"

#ifndef _FUNC_NET_H_
#define _FUNC_NET_H_

//=============================================================================
// 서버 통신 계층
//
// 서버가 아직 없다. 그래서 지금은 클라이언트 안의 "임시 서버"가 요청을 받아
// 파일로 처리한다. 그 파일 형식은 server/dumpformat.md에 적힌 대로이고,
// MariaDB의 LOAD DATA INFILE이 그대로 읽을 수 있다.
//
// 임시 서버라도 진짜 서버처럼 굴게 만드는 것이 이 계층의 목적이다.
//   - 요청하면 바로 답이 오지 않는다. 몇 프레임 뒤에 온다.
//   - 그 사이 게임은 계속 돌아야 한다.
//   - 실패할 수 있다. 충돌(NETRESULT_CONFLICT)로 거절당할 수 있다.
// 이걸 지금 견디게 만들어 두어야, 나중에 전송만 HttpClient로 갈아끼우면 된다.
//
// 갈아끼울 자리는 Func_Net.cpp의 "임시 로컬 서버" 구역 하나뿐이다.
//=============================================================================

//요청 종류
typedef enum _netReq {
	NETREQ_NONE = 0,
	NETREQ_LOGIN,	//게스트 로그인. user_id를 받는다. 없으면 서버가 만든다.
	NETREQ_LOAD,	//세이브 내려받기
	NETREQ_SAVE,	//세이브 올리기
	TOTALNETREQ,
} NETREQDEF;

//요청 결과
typedef enum _netResult {
	NETRESULT_NONE = 0,		//아직 안 끝났다
	NETRESULT_OK,
	NETRESULT_ERR_NETWORK,	//못 붙었다
	NETRESULT_ERR_NOTFOUND,	//서버에 데이터가 없다(첫 실행)
	NETRESULT_ERR_CONFLICT,	//다른 기기가 먼저 저장했다. 이번 저장은 버려진다.
	NETRESULT_ERR_FORMAT,	//받은 것이 규격에 안 맞는다
	TOTALNETRESULT,
} NETRESULTDEF;

//임시 서버가 쓰는 파일. 진짜 서버가 붙으면 이 파일은 캐시로만 남는다.
#define SERVERDBFILE	"serverdb.dat"
#define SERVERDBTEMP	"serverdb.new"

enum {
	//통신에 걸리는 시간. 진짜 서버를 붙이기 전에 "기다림"을 견디는 코드를
	//만들어 두려고 일부러 준다. 60프레임 = 1초.
	NETDELAY_MIN = 12,
	NETDELAY_MAX = 40,

	//저장 요청을 묶는 시간. SaveGame()이 32곳에서 불리는데 그때마다 보내면
	//초당 몇 번씩 나간다. 변경이 생긴 뒤 이만큼 조용하면 한 번에 보낸다.
	NETSAVE_HOLDFRAME = 45,

	//묶는 데도 상한이 필요하다. SaveGame()이 계속 불리면(전투 중이 그렇다)
	//조용해질 때를 기다리다 영영 못 보낸다. 처음 변경이 생긴 뒤 이만큼
	//지나면 잠잠해지길 기다리지 않고 보낸다.
	NETSAVE_MAXHOLDFRAME = 60 * 5,
};

//---- 켜고 끄기 ----
void NetInit(void);
void NetUpdate(void);	//매 프레임 한 번. Core::Run()이 부른다.

//---- 요청 ----
//이미 다른 요청이 도는 중이면 false를 주고 아무것도 하지 않는다.
bool NetRequest(int reqType);

bool NetIsBusy(void);
int NetLastRequest(void);
int NetLastResult(void);

//---- 저장 ----
//SaveGame()이 부른다. 바로 보내지 않고 "보낼 것이 생겼다"고 표시만 한다.
//실제 전송은 NetUpdate()가 NETSAVE_HOLDFRAME 뒤에 묶어서 한다.
void NetMarkDirty(void);

//지금 당장 보낸다. 앱이 백그라운드로 갈 때처럼 기다릴 수 없을 때 쓴다.
void NetFlush(void);

//---- 부팅 ----
//로그인과 첫 로드를 한 번에 끝낸다. 게임 시작 전이라 기다릴 화면이 없으므로
//여기서만 지연 없이 즉시 처리한다. 진짜 서버가 붙으면 이 함수가 로딩 화면을
//띄우는 비동기 흐름으로 바뀐다.
//돌려주는 값은 NETRESULT_*. NETRESULT_ERR_NOTFOUND면 새 게임을 시작하면 된다.
int NetBootstrap(void);

//---- 충돌 ----
//
// 다른 기기가 먼저 저장하면 서버가 이쪽 저장을 거절한다(NETRESULT_ERR_CONFLICT).
// 그러면 이 계층이 알아서 서버 것을 다시 받아 덮는다. 이 기기에서 마지막 저장
// 뒤에 한 일은 사라진다. 먼저 저장한 쪽을 남기기로 정했기 때문이다.
//
// 사라진다는 것을 사용자가 알아야 한다. 아래 둘로 알린다.
//   - NetIndicatorDraw()가 잠시 문구를 띄운다.
//   - 게임 쪽에서 제대로 된 팝업을 띄우고 싶으면 NetTakeConflictNotice()를 쓴다.

//충돌로 서버 것을 다시 받았는가. 한 번 물으면 지워진다(같은 것을 두 번 안 띄우게).
bool NetTakeConflictNotice(void);

//---- 화면 ----
//통신 중이라는 것을 구석에 표시한다. 지연이 눈에 보여야 한다.
void NetIndicatorDraw(void);

//---- 서버 시간 ----
//
// 게임 시간을 기기 시계에 맡기면 안 된다. 시계를 앞으로 돌리면 일일 초기화,
// 하트 회복, 쿨타임을 공짜로 건너뛴다. 뒤로 돌리면 반대로 꼬인다.
//
// 그래서 서버가 답할 때마다 서버의 지금 시각을 같이 받아, 기기 시계와의
// 차이를 기억한다. MC_knlCurrentTimeStamp() 가 그 차이를 더해 돌려주므로
// 시간을 보는 코드는 하나도 안 고쳐도 된다.
//
//     게임이 보는 시각 = 기기 시계 + gNetTimeOffset
//
// 서버에 못 붙었으면 0이다. 그러면 기기 시계를 그대로 쓴다. 오프라인에서도
// 게임은 돌아야 하므로 막지는 않는다.

//서버 시각 - 기기 시각. 초 단위.
extern long gNetTimeOffset;

//서버가 알려준 지금 시각으로 오프셋을 다시 잡는다.
//임시 로컬 서버는 자기가 곧 이 기기라 오프셋이 0이 된다. 진짜 서버가 붙으면
//여기서 처음으로 0이 아닌 값이 나온다.
void NetSetServerTime(long serverNow);

//서버가 준 것들
extern long long gNetUserId;
extern long long gNetRevision;

#endif
