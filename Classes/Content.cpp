#include "cocos2d.h"

#include "Content.h"
#include "Config/ContentConfig.h"	//CONTENT_CDN_URL
#include "network/HttpClient.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <direct.h>
#define MKDIR(p) _mkdir(p)
#else
#include <sys/stat.h>
#define MKDIR(p) mkdir(p, 0775)
#endif

USING_NS_CC;

//=============================================================================
// 콘텐츠 배포
//
//   1. 경로            - 어디에 받고 어디서 읽나
//   2. 매니페스트      - 무슨 파일이 어떤 판인지 적은 표
//   3. 받아오기        - CONTENT_CDN_URL 이 비면 폴더, 차면 HTTP
//   4. 부팅            - 다 받아둔 것을 반영한다 (빠르다)
//   5. 갱신 굴리기     - 게임 루프가 한 칸씩 굴린다
//
// 자세한 얼개는 Content.h 를 보라.
//=============================================================================

//지금 쓰는 콘텐츠. 검색 경로 맨 앞에 들어간다.
#define CONTENT_DIR "content"

//받는 중인 다음 판. 다 받으면 부팅 때 위로 옮긴다.
#define STAGING_DIR "content.next"

#define CONTENT_MANIFEST "manifest.tsv"

//판번호 한 줄만 든 파일. 갱신 확인은 이것부터 본다.
//
//매니페스트는 32KB 인데 대개는 "안 바뀌었다"를 확인하려고 받는다. 유저가
//백만이면 그 확인만으로 달마다 수백 GB 가 나간다. 스무 바이트짜리를 먼저
//보면 그게 거의 사라진다.
#define CONTENT_VERSIONFILE "version.txt"

//한 파일이 이만큼 넘으면 이상한 것이다. 잘못된 매니페스트로 디스크를 안 채운다.
#define CONTENT_MAXFILE (256 * 1024 * 1024)

static long long sVersion = 0;

//앱에 딸려온 목록. ContentBoot() 이 한 번 읽어 둔다.
//
//받을 것을 고를 때 쓴다. 앱 안에 이미 같은 파일이 있으면 받을 이유가 없다.
static long long sBundledVer = 0;
static std::vector<ContentFile> sBundled;

//전부 게임 루프 하나만 건드린다. 딴 실이 없으므로 잠글 것도 없다.
static int sState = CONTENT_IDLE;
static int sDone = 0;
static int sTotal = 0;

static char sMessage[256] = "아직 갱신한 적 없다";

//부팅 때 한 번 잡아 둔다. 경로를 물을 때마다 FileUtils 를 안 타려는 것이다.
static std::string sWritable;

static void Say(const char* fmt, ...)
{
	char buf[256];
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	memcpy(sMessage, buf, sizeof(buf));

	CCLOG("Content: %s", buf);
}

const char* ContentLastMessage(void)
{
	return sMessage;
}

long long ContentVersion(void)
{
	return sVersion;
}

unsigned long long ContentHash(const void* buf, unsigned int len)
{
	const unsigned char* p = (const unsigned char*)buf;
	unsigned long long h = 0xCBF29CE484222325ULL;
	unsigned int i;

	for (i = 0; i < len; i++) {
		h ^= p[i];
		h *= 0x100000001B3ULL;
	}

	return h;
}

//=============================================================================
// 1. 경로
//=============================================================================

static std::string LiveDir(void) { return sWritable + CONTENT_DIR "/"; }
static std::string StageDir(void) { return sWritable + STAGING_DIR "/"; }
static std::string CdnDir(void) { return sWritable + "cdn/"; }

//"a/b/c.png" 의 중간 폴더를 만든다. FileUtils 를 안 쓴다.
static void MakeDirs(const std::string& full)
{
	size_t at = full.find('/');

	while (at != std::string::npos) {
		MKDIR(full.substr(0, at).c_str());
		at = full.find('/', at + 1);
	}
}

static bool ReadWhole(const std::string& path, std::string* out)
{
	FILE* fp = fopen(path.c_str(), "rb");

	if (!fp)
		return false;

	char buf[65536];
	size_t n;

	out->clear();

	while ((n = fread(buf, 1, sizeof(buf), fp)) > 0) {
		out->append(buf, n);

		if (out->size() > CONTENT_MAXFILE) {
			fclose(fp);
			return false;
		}
	}

	fclose(fp);
	return true;
}

//먼저 임시 이름으로 쓰고 나서 옮긴다. 쓰다 죽어도 반쪽 파일이 안 남는다.
static bool WriteWhole(const std::string& full, const std::string& body)
{
	std::string tmp = full + ".part";

	MakeDirs(full);

	FILE* fp = fopen(tmp.c_str(), "wb");

	if (!fp)
		return false;

	size_t wrote = body.empty() ? 0 : fwrite(body.data(), 1, body.size(), fp);
	bool ok = (wrote == body.size());

	if (fclose(fp) != 0)
		ok = false;

	if (!ok) {
		remove(tmp.c_str());
		return false;
	}

	//윈도우의 rename 은 목적지가 있으면 실패한다. 먼저 치운다.
	remove(full.c_str());

	if (rename(tmp.c_str(), full.c_str()) != 0) {
		remove(tmp.c_str());
		return false;
	}

	return true;
}

//=============================================================================
// 2. 매니페스트
//
//     #content 1
//     version <탭> 2026082001
//     res/aa.png <탭> 12345 <탭> a1b2c3d4e5f60718
//
// 판번호는 사람이 읽을 수 있게 날짜+번호로 둔다. 크기와 지문을 같이 적어
// 받은 것이 온전한지 본다. 크기만으로는 내용이 바뀐 것을 못 잡는다.
//=============================================================================

static bool ParseManifest(const std::string& text, long long* outVer,
	std::vector<ContentFile>* out)
{
	size_t at = 0;
	bool head = false;

	*outVer = 0;
	out->clear();

	while (at < text.size()) {
		size_t nl = text.find('\n', at);

		if (nl == std::string::npos)
			nl = text.size();

		std::string line = text.substr(at, nl - at);
		at = nl + 1;

		while (!line.empty() && (line[line.size() - 1] == '\r' ||
			line[line.size() - 1] == ' '))
			line.erase(line.size() - 1);

		if (line.empty())
			continue;

		if (line[0] == '#') {
			//머리글. 형식이 바뀌면 여기 숫자가 올라간다.
			head = (line.compare(0, 9, "#content ") == 0);
			continue;
		}

		size_t t1 = line.find('\t');

		if (t1 == std::string::npos)
			continue;

		std::string key = line.substr(0, t1);

		if (key == "version") {
			*outVer = atoll(line.c_str() + t1 + 1);
			continue;
		}

		size_t t2 = line.find('\t', t1 + 1);

		if (t2 == std::string::npos)
			continue;

		ContentFile f;
		f.path = key;
		f.size = (unsigned int)strtoul(line.c_str() + t1 + 1, NULL, 10);
		f.hash = strtoull(line.c_str() + t2 + 1, NULL, 16);
		out->push_back(f);
	}

	return head;
}

static std::string BuildManifest(long long ver, const std::vector<ContentFile>& fs)
{
	std::string out = "#content 1\nversion\t";
	char buf[64];

	snprintf(buf, sizeof(buf), "%lld\n", ver);
	out += buf;

	for (size_t i = 0; i < fs.size(); i++) {
		out += fs[i].path;
		snprintf(buf, sizeof(buf), "\t%u\t%016llx\n", fs[i].size, fs[i].hash);
		out += buf;
	}

	return out;
}

//지금 쓰고 있는 콘텐츠의 매니페스트. 없으면 앱에 딸려온 것.
static bool ReadLiveManifest(long long* ver, std::vector<ContentFile>* fs)
{
	std::string text;

	if (!ReadWhole(LiveDir() + CONTENT_MANIFEST, &text)) {
		//앱에 딸려온 것은 apk 안에 있을 수 있어 FileUtils 로 읽는다.
		text = FileUtils::getInstance()->getStringFromFile(CONTENT_MANIFEST);
	}

	if (text.empty()) {
		*ver = 0;
		fs->clear();
		return false;
	}

	return ParseManifest(text, ver, fs);
}

//=============================================================================
// 3. 받아오기
//
// 어디서 받을지는 Config/ContentConfig.h 의 CONTENT_CDN_URL 이 정한다.
//
//   비어 있으면 : 쓰기 가능 경로의 cdn/ 폴더를 본다. 서버 없이 시험할 때.
//   채워져 있으면 : 그 주소에 GET 을 보낸다.
//
// 요청 하나를 띄우고 곧바로 돌아온다. 답이 오면 Take() 로 꺼낸다. 네트워크는
// HttpClient 가 자기 실에서 하므로 게임 루프는 안 막힌다.
//=============================================================================

//한 번에 몇 개까지 띄울지.
//
//처음에는 한 개씩만 받았다. 그런데 요청 하나에 프레임을 두세 개 쓰다 보니,
//지연이 0인 localhost 에서도 903개에 48초가 걸렸다. 네트워크가 아니라
//"한 프레임에 한 걸음"이 병목이었다.
//
//진짜 CDN 이면 여기에 왕복 지연이 파일마다 붙는다. 50ms 만 잡아도 903개면
//45초가 더 든다. 여러 개를 겹쳐 띄우면 그 지연이 서로 가려진다.
//
//너무 크게 잡지 않는다. 모바일에서 연결을 많이 열면 오히려 느려지고,
//받은 것을 메모리에 들고 있으므로 큰 파일이 여럿 겹치면 메모리도 는다.
#define FETCH_SLOTS 6

//받아오기 한 건.
struct Fetch {
	bool busy;			//답을 기다리는 중
	bool done;			//답이 왔다
	bool ok;			//성공했나
	int at;				//sTodo 의 몇 번째인가. 매니페스트를 받을 때는 -1
	std::string body;

	//이 슬롯이 계속 쓰는 요청 객체. 만드는 이유는 FetchBegin() 주석 참고.
	network::HttpRequest* req;
};

static Fetch sFetch[FETCH_SLOTS];

static bool UsingNetwork(void)
{
	return CONTENT_CDN_URL[0] != 0;
}

//요청을 띄운다. 슬롯 번호를 넘긴다.
static void FetchBegin(int slot, const std::string& path, int at,
	const char* tag = "")
{
	Fetch* f = &sFetch[slot];

	f->busy = true;
	f->done = false;
	f->ok = false;
	f->at = at;
	f->body.clear();

	if (!UsingNetwork()) {
		//서버가 없을 때. 폴더에서 곧바로 읽는다.
		f->ok = ReadWhole(CdnDir() + path, &f->body);
		f->done = true;
		return;
	}

	//슬롯마다 요청 객체를 하나씩 만들어 계속 쓴다.
	//
	//매번 new 하면 안 된다. 지우는 것은 libcocos2d.dll 안의 Ref::release()
	//인데 만드는 것은 이쪽(cs.exe)이다. 모듈이 다르면 힙이 어긋나서, 지우는
	//순간 힙이 깨지거나 잠긴다. Func_Net.cpp 에서 그 증상으로 게임 루프가
	//통째로 멈추는 것을 겪었다.
	//
	//슬롯 하나에는 한 번에 한 요청만 도므로(busy) 슬롯당 하나면 충분하다.
	if (f->req == NULL) {
		f->req = new (std::nothrow) network::HttpRequest();

		if (f->req == NULL) {
			f->done = true;
			return;
		}

		//놓지 않는다. 계수가 0이 되면 위에 적은 그 delete 가 일어난다.
		f->req->retain();
	}

	network::HttpRequest* req = f->req;

	//꼬리표는 그 파일의 지문이다. 내용이 바뀌면 주소도 바뀌므로 캐시를
	//영원히 걸어둘 수 있다. 붙이지 않으면 주소는 그대로인데 내용이 바뀔 수
	//있어서 캐시를 길게 못 건다.
	req->setUrl(std::string(CONTENT_CDN_URL) + path + tag);
	req->setRequestType(network::HttpRequest::Type::GET);

	//어느 슬롯의 답인지 알아야 한다. 여러 개가 동시에 날아다니므로
	//끝나는 차례가 보낸 차례와 다르다.
	req->setResponseCallback([slot](network::HttpClient* /*c*/,
		network::HttpResponse* res) {
		//여기는 메인 실이다. HttpClient 가 게임 루프로 넘겨준다.
		Fetch* g = &sFetch[slot];

		g->ok = false;

		if (res && res->isSucceed()) {
			long code = res->getResponseCode();

			if (code == 200) {
				std::vector<char>* d = res->getResponseData();

				if (d->size() <= CONTENT_MAXFILE) {
					g->body.assign(d->begin(), d->end());
					g->ok = true;
				}
				else {
					CCLOG("Content: 받은 것이 너무 크다 (%d)", (int)d->size());
				}
			}
			else {
				CCLOG("Content: HTTP %ld", code);
			}
		}
		else if (res) {
			CCLOG("Content: 못 받았다 (%s)", res->getErrorBuffer());
		}

		g->done = true;
	});

	network::HttpClient::getInstance()->send(req);
}

//비어 있는 슬롯을 찾는다. 없으면 -1.
static int FetchFreeSlot(void)
{
	int i;

	for (i = 0; i < FETCH_SLOTS; i++)
		if (!sFetch[i].busy)
			return i;

	return -1;
}

//띄워둔 것이 하나라도 있나.
static bool FetchAnyBusy(void)
{
	int i;

	for (i = 0; i < FETCH_SLOTS; i++)
		if (sFetch[i].busy)
			return true;

	return false;
}

static void FetchClearAll(void)
{
	int i;

	for (i = 0; i < FETCH_SLOTS; i++) {
		sFetch[i].busy = false;
		sFetch[i].done = false;
		sFetch[i].at = -1;
		sFetch[i].body.clear();
	}
}

//=============================================================================
// 4. 부팅
//
// 다 받아둔 것이 있으면 여기서 반영한다. 파일을 옮기기만 하므로 순식간이다.
// 네트워크를 안 탄다. 그래서 부팅이 안 느려진다.
//=============================================================================

//staging 에 매니페스트가 있으면 다 받은 것이다.
bool ContentHasStaged(void)
{
	std::string dummy;
	return ReadWhole(StageDir() + CONTENT_MANIFEST, &dummy);
}

//staging 의 파일들을 지금 쓰는 폴더로 옮긴다.
static void CommitStaged(void)
{
	std::string text;

	if (!ReadWhole(StageDir() + CONTENT_MANIFEST, &text))
		return;		//덜 받았다. 다음에 다시 받는다.

	long long ver = 0;
	std::vector<ContentFile> fs;

	if (!ParseManifest(text, &ver, &fs))
		return;

	//옮기기 전에 지금 목록을 들고 있는다. 새 목록에 없는 파일을 지우려면
	//옛 목록이 있어야 한다.
	long long oldVer = 0;
	std::vector<ContentFile> old;

	ReadLiveManifest(&oldVer, &old);

	std::string stage = StageDir();
	std::string live = LiveDir();
	int moved = 0;
	int gone = 0;

	for (size_t i = 0; i < fs.size(); i++) {
		std::string from = stage + fs[i].path;
		std::string to = live + fs[i].path;

		//이번 판에서 안 바뀐 파일은 staging 에 없다. 그건 그대로 둔다.
		FILE* fp = fopen(from.c_str(), "rb");

		if (!fp)
			continue;

		fclose(fp);
		MakeDirs(to);
		remove(to.c_str());

		if (rename(from.c_str(), to.c_str()) == 0)
			moved++;
	}

	//새 목록에 없는 것은 지운다.
	//
	//이게 없으면 매니페스트에서 뺀 파일이 content/ 에 영영 남는다. 검색
	//경로가 앞이라 앱에 들어 있는 원본을 계속 가리므로, "잘못 올린 그림을
	//매니페스트에서 빼서 되돌리기"가 안 된다. 폐기된 것이 기기에 쌓이기도 한다.
	for (size_t i = 0; i < old.size(); i++) {
		bool still = false;

		for (size_t j = 0; j < fs.size(); j++) {
			if (fs[j].path == old[i].path) {
				still = true;
				break;
			}
		}

		if (!still && remove((live + old[i].path).c_str()) == 0)
			gone++;
	}

	//매니페스트를 맨 나중에 옮긴다. 중간에 죽으면 staging 매니페스트가
	//남아서 다음 부팅 때 마저 옮긴다.
	if (WriteWhole(live + CONTENT_MANIFEST, text))
		remove((stage + CONTENT_MANIFEST).c_str());

	sVersion = ver;
	Say("판 %lld 로 바꿔 넣었다 (바꾼 파일 %d개, 지운 파일 %d개)", ver, moved, gone);
}

//내려받은 것을 통째로 버린다.
static void ClearLive(const std::vector<ContentFile>& fs)
{
	std::string live = LiveDir();

	for (size_t i = 0; i < fs.size(); i++)
		remove((live + fs[i].path).c_str());

	remove((live + CONTENT_MANIFEST).c_str());
}

void ContentBoot(void)
{
	FileUtils* fu = FileUtils::getInstance();
	long long bundledVer = 0;

	sWritable = fu->getWritablePath();

	MKDIR((sWritable + CONTENT_DIR).c_str());
	MKDIR((sWritable + STAGING_DIR).c_str());

	//앱에 딸려온 판번호를 먼저 본다. 아래에서 검색 경로에 LiveDir 을 넣기
	//전이라 여기서는 앱 안의 것이 잡힌다.
	{
		std::string text = fu->getStringFromFile(CONTENT_MANIFEST);

		if (!text.empty())
			ParseManifest(text, &bundledVer, &sBundled);

		sBundledVer = bundledVer;
	}

	//뒤에서 다 받아둔 것이 있으면 지금 넣는다. 게임이 아직 아무것도 안 읽었다.
	CommitStaged();

	//스토어로 새 앱이 깔렸는데 내려받은 것이 더 낡았으면 덧칠을 버린다.
	//
	//안 그러면 앱을 새로 올려도 옛 CDN 파일이 검색 경로 앞에서 계속 이긴다.
	//1월에 A 를 넣고, 2월에 CDN 으로 A' 를 덮고, 3월에 앱으로 A'' 를 내보내도
	//유저 화면에는 2월의 A' 가 그대로 남는 일이 생긴다.
	{
		long long liveVer = 0;
		std::vector<ContentFile> live;

		if (ReadLiveManifest(&liveVer, &live) && bundledVer > liveVer) {
			ClearLive(live);
			CCLOG("Content: 앱이 더 새것이다 (판 %lld > %lld). 내려받은 것을 버린다",
				bundledVer, liveVer);
		}
	}

	//맨 앞에 넣는다. 같은 이름이 있으면 내려받은 쪽이 이긴다.
	//
	//이 한 줄이 이 기능의 전부다. "res/aa.png" 를 읽는 코드가 수백 군데
	//있지만 하나도 안 고쳐도 된다. 이름을 찾는 일은 전부 FileUtils 가 한다.
	std::string dir = LiveDir();
	std::vector<std::string> paths = fu->getSearchPaths();

	if (std::find(paths.begin(), paths.end(), dir) == paths.end()) {
		paths.insert(paths.begin(), dir);
		fu->setSearchPaths(paths);
	}

	long long ver = 0;
	std::vector<ContentFile> fs;

	ReadLiveManifest(&ver, &fs);
	sVersion = ver;

	CCLOG("Content: 판 %lld, 내려받기 폴더 %s", ver, dir.c_str());
}

//=============================================================================
// 5. 갱신 굴리기
//
// 딴 실을 안 쓴다. 게임 루프가 매 프레임 ContentUpdateStep() 을 부르면 한
// 칸씩 나아간다. 네트워크는 HttpClient 가 자기 실에서 하므로 안 막힌다.
//
// 딴 실을 안 쓰는 이유가 있다. HttpClient 는 답을 메인 실로 넘겨준다.
// 딴 실에서 그 답을 기다리면, 앱이 백그라운드로 가서 메인 루프가 멈출 때
// 영영 안 깨어난다. 상태기계로 두면 그런 일이 없다.
//
//     CHECKING -> 매니페스트를 받아 견준다
//     DOWNLOADING -> 한 번에 한 파일씩 받아 staging 에 쓴다
//     READY -> 매니페스트를 쓰고 끝낸다. 반영은 다음 부팅 때.
//=============================================================================

//받아야 할 것과 어디까지 했는지.
static std::vector<ContentFile> sTodo;
static std::vector<ContentFile> sRemote;
static long long sRemoteVer = 0;
static int sAt = 0;

static void PickChanged(const std::vector<ContentFile>& want,
	const std::vector<ContentFile>& have, std::vector<ContentFile>* out)
{
	std::string live = LiveDir();

	out->clear();

	for (size_t i = 0; i < want.size(); i++) {
		const ContentFile& w = want[i];
		bool same = false;

		for (size_t j = 0; j < have.size(); j++) {
			if (have[j].path == w.path) {
				same = (have[j].hash == w.hash && have[j].size == w.size);
				break;
			}
		}

		//목록이 같다고 해도 파일이 실제로 있어야 한다. 지워졌을 수 있다.
		if (same) {
			FILE* fp = fopen((live + w.path).c_str(), "rb");

			if (fp)
				fclose(fp);
			else
				same = false;
		}

		//내려받기 폴더에 없더라도, 앱에 딸려온 것과 같으면 받을 필요가 없다.
		//FileUtils 가 앱 안에서 찾아준다.
		//
		//이게 없으면 첫 패치 때 안 바뀐 파일까지 전부 받는다. 유저 한 명당
		//113MB 다. 백만 명이면 그것만으로 100TB 가 넘게 나간다.
		if (!same) {
			for (size_t k = 0; k < sBundled.size(); k++) {
				if (sBundled[k].path == w.path) {
					if (sBundled[k].hash == w.hash && sBundled[k].size == w.size)
						same = true;

					break;
				}
			}
		}

		if (!same)
			out->push_back(w);
	}
}

void ContentUpdateBegin(void)
{
	if (sState != CONTENT_IDLE)
		return;

	sTodo.clear();
	sRemote.clear();
	sAt = 0;
	sDone = 0;
	sTotal = 0;
	sState = CONTENT_CHECKVER;

	FetchClearAll();

	//판번호에는 꼬리표를 안 붙인다. 이것만은 늘 새것을 받아야 한다.
	FetchBegin(0, CONTENT_VERSIONFILE, -1);
}

//받은 파일 하나를 검사하고 staging 에 쓴다.
static bool KeepFile(const ContentFile& f, const std::string& body)
{
	//받은 것이 온전한지 본다. 크기만 보면 내용이 바뀐 것을 못 잡는다.
	if (body.size() != f.size) {
		Say("%s 크기가 다르다 (받은 %u, 적힌 %u)",
			f.path.c_str(), (unsigned int)body.size(), f.size);
		return false;
	}

	if (ContentHash(body.data(), (unsigned int)body.size()) != f.hash) {
		Say("%s 가 깨졌다 (지문 불일치)", f.path.c_str());
		return false;
	}

	if (!WriteWhole(StageDir() + f.path, body)) {
		Say("%s 를 못 썼다", f.path.c_str());
		return false;
	}

	return true;
}

//판번호만 먼저 본다. 같으면 여기서 끝이고 매니페스트를 안 받는다.
static void StepCheckVersion(void)
{
	Fetch* f = &sFetch[0];
	char tag[32];

	if (!f->busy || !f->done)
		return;

	bool ok = f->ok;
	std::string body;

	body.swap(f->body);
	f->busy = false;
	f->done = false;

	if (!ok) {
		Say("CDN 판번호를 못 읽었다. 지금 콘텐츠를 그대로 쓴다");
		sState = CONTENT_FAILED;
		return;
	}

	sRemoteVer = atoll(body.c_str());

	if (sRemoteVer <= 0) {
		Say("CDN 판번호가 이상하다");
		sState = CONTENT_FAILED;
		return;
	}

	long long localVer = 0;
	std::vector<ContentFile> local;

	ReadLiveManifest(&localVer, &local);

	//더 낡은 판은 받지 않는다.
	//
	//같을 때만 멈추면, 스토어로 새 앱이 깔린 뒤 CDN 이 아직 옛 판일 때
	//"앱이 새것이라 내려받은 것을 버린다 -> 옛 CDN 판을 다시 받는다"를
	//부팅마다 되풀이한다. 유저마다 무한히 받는 셈이다.
	//
	//되돌리고 싶으면 옛 내용을 새 판번호로 다시 올리면 된다.
	if (sRemoteVer <= localVer) {
		Say("최신이다 (판 %lld)", localVer);
		sState = CONTENT_UPTODATE;
		return;
	}

	//판이 다르다. 그제서야 매니페스트를 받는다. 판번호를 꼬리표로 달아
	//판마다 캐시가 따로 잡히게 한다.
	snprintf(tag, sizeof(tag), "?v=%lld", sRemoteVer);

	sState = CONTENT_CHECKING;
	FetchBegin(0, CONTENT_MANIFEST, -1, tag);
}

//매니페스트를 받아 무엇을 받을지 정한다.
static void StepChecking(void)
{
	Fetch* f = &sFetch[0];

	if (!f->busy || !f->done)
		return;

	bool ok = f->ok;
	std::string body;

	body.swap(f->body);
	f->busy = false;
	f->done = false;

	if (!ok) {
		Say("CDN 매니페스트를 못 읽었다. 지금 콘텐츠를 그대로 쓴다");
		sState = CONTENT_FAILED;
		return;
	}

	if (!ParseManifest(body, &sRemoteVer, &sRemote)) {
		Say("CDN 매니페스트 형식이 다르다");
		sState = CONTENT_FAILED;
		return;
	}

	long long localVer = 0;
	std::vector<ContentFile> local;

	ReadLiveManifest(&localVer, &local);

	//판번호 단계와 같은 이유로 더 낡은 판은 받지 않는다.
	if (sRemoteVer <= localVer) {
		Say("최신이다 (판 %lld, 파일 %d개)", localVer, (int)local.size());
		sState = CONTENT_UPTODATE;
		return;
	}

	PickChanged(sRemote, local, &sTodo);

	sAt = 0;
	sDone = 0;
	sTotal = (int)sTodo.size();
	sState = CONTENT_DOWNLOADING;

	Say("판 %lld -> %lld, 받을 파일 %d개",
		localVer, sRemoteVer, (int)sTodo.size());
}

//받기. 빈 슬롯을 채우고, 답이 온 것을 거둔다.
//
//여러 개를 겹쳐 띄우므로 끝나는 차례가 보낸 차례와 다르다. 그래서 "몇 번째까지
//했나"가 아니라 슬롯마다 자기가 맡은 파일 번호(at)를 들고 있는다.
static void StepDownloading(void)
{
	int i;

	//---- 답이 온 것 거두기 ----
	for (i = 0; i < FETCH_SLOTS; i++) {
		Fetch* f = &sFetch[i];

		if (!f->busy || !f->done)
			continue;

		int at = f->at;
		bool ok = f->ok;
		std::string body;

		body.swap(f->body);
		f->busy = false;
		f->done = false;

		if (!ok) {
			Say("%s 를 못 받았다", sTodo[at].path.c_str());
			sState = CONTENT_FAILED;
			return;
		}

		if (!KeepFile(sTodo[at], body)) {
			sState = CONTENT_FAILED;
			return;
		}

		sDone = sDone + 1;
	}

	//---- 빈 슬롯 채우기 ----
	while (sAt < (int)sTodo.size()) {
		int slot = FetchFreeSlot();

		if (slot < 0)
			break;

		char tag[32];

		snprintf(tag, sizeof(tag), "?v=%016llx", sTodo[sAt].hash);
		FetchBegin(slot, sTodo[sAt].path, sAt, tag);
		sAt++;
	}

	//---- 다 끝났나 ----
	//보낼 것도 없고 기다리는 것도 없어야 끝이다.
	if (sAt < (int)sTodo.size() || FetchAnyBusy())
		return;

	//매니페스트를 맨 나중에 쓴다. 이게 있어야 "다 받았다"는 뜻이다.
	//중간에 죽으면 이게 없어서 다음에 처음부터 다시 받는다.
	if (!WriteWhole(StageDir() + CONTENT_MANIFEST,
		BuildManifest(sRemoteVer, sRemote))) {
		Say("매니페스트를 못 썼다. 다음에 다시 받는다");
		sState = CONTENT_FAILED;
		return;
	}

	Say("판 %lld 를 다 받았다 (파일 %d개). 다음에 켤 때 반영된다",
		sRemoteVer, (int)sTodo.size());
	sState = CONTENT_READY;
}

void ContentUpdateStep(void)
{
	if (sState == CONTENT_CHECKVER)
		StepCheckVersion();

	if (sState == CONTENT_CHECKING)
		StepChecking();

	if (sState == CONTENT_DOWNLOADING)
		StepDownloading();
}

ContentState ContentPoll(int* doneFiles, int* totalFiles)
{
	if (doneFiles)
		*doneFiles = sDone;

	if (totalFiles)
		*totalFiles = sTotal;

	return (ContentState)sState;
}

void ContentShutdown(void)
{
	//받던 것이 있으면 버린다. staging 에 매니페스트를 안 썼으므로 덜 받은
	//것으로 남고, 다음에 켤 때 처음부터 다시 받는다.
	FetchClearAll();
	sState = CONTENT_IDLE;
}
