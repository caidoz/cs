#include "cocos2d.h"

#include "Content.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <atomic>
#include <mutex>
#include <thread>

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
//   3. 임시 로컬 CDN   - ★ 진짜 CDN이 붙으면 여기만 갈아끼운다
//   4. 부팅            - 다 받아둔 것을 반영한다 (빠르다)
//   5. 뒤에서 받기     - 딴 실 하나로 받는다. 게임은 계속 돈다
//
// 자세한 얼개는 Content.h 를 보라.
//=============================================================================

//지금 쓰는 콘텐츠. 검색 경로 맨 앞에 들어간다.
#define CONTENT_DIR "content"

//받는 중인 다음 판. 다 받으면 부팅 때 위로 옮긴다.
#define STAGING_DIR "content.next"

#define CONTENT_MANIFEST "manifest.tsv"

//한 파일이 이만큼 넘으면 이상한 것이다. 잘못된 매니페스트로 디스크를 안 채운다.
#define CONTENT_MAXFILE (256 * 1024 * 1024)

static long long sVersion = 0;

//딴 실이 건드리는 것들. 읽는 쪽은 게임 루프다.
static std::atomic<int> sState(CONTENT_IDLE);
static std::atomic<int> sDone(0);
static std::atomic<int> sTotal(0);
static std::atomic<bool> sQuit(false);

static std::mutex sMsgLock;
static char sMessage[256] = "아직 갱신한 적 없다";

static std::thread sWorker;
static bool sStarted = false;

//딴 실에서도 쓰므로 부팅 때 한 번 잡아 둔다.
//FileUtils 를 딴 실에서 부르지 않기 위해서다.
static std::string sWritable;

static void Say(const char* fmt, ...)
{
	char buf[256];
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	{
		std::lock_guard<std::mutex> lock(sMsgLock);
		memcpy(sMessage, buf, sizeof(buf));
	}

	CCLOG("Content: %s", buf);
}

const char* ContentLastMessage(void)
{
	//짧은 문자열이라 그대로 돌려준다. 읽는 쪽은 게임 루프 하나뿐이다.
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

//"a/b/c.png" 의 중간 폴더를 만든다. FileUtils 를 안 쓴다. 딴 실에서 부른다.
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
		//부팅 때만 부르므로 딴 실 문제가 없다.
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
// 3. 임시 로컬 CDN
//
// ★ 진짜 CDN이 붙으면 이 구획만 갈아끼운다.
//
// 지금은 서버가 없다. 그래서 "먼 곳"을 폴더 하나로 흉내낸다.
//
//     cdn/manifest.tsv
//     cdn/data/content.pack
//     cdn/res/aa.png
//
// 진짜로 바꿀 때 고칠 것은 아래 둘뿐이다.
//   CdnFetchManifest : GET <베이스>/manifest.tsv
//   CdnFetchFile     : GET <베이스>/<경로>
//
// 이미 딴 실에서 불리므로, 막히는 HTTP 호출을 그대로 넣어도 게임은 안 멈춘다.
//=============================================================================

static bool CdnFetchManifest(std::string* out)
{
	return ReadWhole(CdnDir() + CONTENT_MANIFEST, out);
}

static bool CdnFetchFile(const std::string& path, std::string* out)
{
	return ReadWhole(CdnDir() + path, out);
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

	std::string stage = StageDir();
	std::string live = LiveDir();
	int moved = 0;

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

	//매니페스트를 맨 나중에 옮긴다. 중간에 죽으면 staging 매니페스트가
	//남아서 다음 부팅 때 마저 옮긴다.
	if (WriteWhole(live + CONTENT_MANIFEST, text))
		remove((stage + CONTENT_MANIFEST).c_str());

	sVersion = ver;
	Say("판 %lld 로 바꿔 넣었다 (파일 %d개)", ver, moved);
}

void ContentBoot(void)
{
	FileUtils* fu = FileUtils::getInstance();

	sWritable = fu->getWritablePath();

	MKDIR((sWritable + CONTENT_DIR).c_str());
	MKDIR((sWritable + STAGING_DIR).c_str());

	//뒤에서 다 받아둔 것이 있으면 지금 넣는다. 게임이 아직 아무것도 안 읽었다.
	CommitStaged();

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
// 5. 뒤에서 받기
//
// 딴 실 하나가 돈다. 게임 루프는 ContentPoll 로 상태만 본다.
// 받은 것은 staging 에 쌓이고, 반영은 다음 부팅 때 한다.
//=============================================================================

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

		if (!same)
			out->push_back(w);
	}
}

static void Worker(void)
{
	sState = CONTENT_CHECKING;

	std::string text;

	if (!CdnFetchManifest(&text)) {
		Say("CDN 매니페스트를 못 읽었다. 지금 콘텐츠를 그대로 쓴다");
		sState = CONTENT_FAILED;
		return;
	}

	long long remoteVer = 0;
	std::vector<ContentFile> remote;

	if (!ParseManifest(text, &remoteVer, &remote)) {
		Say("CDN 매니페스트 형식이 다르다");
		sState = CONTENT_FAILED;
		return;
	}

	long long localVer = 0;
	std::vector<ContentFile> local;

	ReadLiveManifest(&localVer, &local);

	if (remoteVer == localVer) {
		Say("최신이다 (판 %lld, 파일 %d개)", localVer, (int)local.size());
		sState = CONTENT_UPTODATE;
		return;
	}

	std::vector<ContentFile> todo;

	PickChanged(remote, local, &todo);

	sTotal = (int)todo.size();
	sDone = 0;
	sState = CONTENT_DOWNLOADING;

	Say("판 %lld -> %lld, 받을 파일 %d개", localVer, remoteVer, (int)todo.size());

	std::string stage = StageDir();

	for (size_t i = 0; i < todo.size(); i++) {
		if (sQuit) {
			Say("받기를 멈췄다");
			sState = CONTENT_IDLE;
			return;
		}

		const ContentFile& f = todo[i];
		std::string body;

		if (!CdnFetchFile(f.path, &body)) {
			Say("%s 를 못 받았다", f.path.c_str());
			sState = CONTENT_FAILED;
			return;
		}

		//받은 것이 온전한지 본다. 크기만 보면 내용이 바뀐 것을 못 잡는다.
		if (body.size() != f.size) {
			Say("%s 크기가 다르다 (받은 %u, 적힌 %u)",
				f.path.c_str(), (unsigned int)body.size(), f.size);
			sState = CONTENT_FAILED;
			return;
		}

		if (ContentHash(body.data(), (unsigned int)body.size()) != f.hash) {
			Say("%s 가 깨졌다 (지문 불일치)", f.path.c_str());
			sState = CONTENT_FAILED;
			return;
		}

		if (!WriteWhole(stage + f.path, body)) {
			Say("%s 를 못 썼다", f.path.c_str());
			sState = CONTENT_FAILED;
			return;
		}

		sDone = (int)(i + 1);
	}

	//매니페스트를 맨 나중에 쓴다. 이게 있어야 "다 받았다"는 뜻이다.
	//중간에 죽으면 이게 없어서 다음에 처음부터 다시 받는다.
	if (!WriteWhole(stage + CONTENT_MANIFEST, BuildManifest(remoteVer, remote))) {
		Say("매니페스트를 못 썼다. 다음에 다시 받는다");
		sState = CONTENT_FAILED;
		return;
	}

	Say("판 %lld 를 다 받았다 (파일 %d개). 다음에 켤 때 반영된다",
		remoteVer, (int)todo.size());
	sState = CONTENT_READY;
}

void ContentUpdateBegin(void)
{
	if (sStarted)
		return;

	sStarted = true;
	sQuit = false;
	sWorker = std::thread(Worker);
}

ContentState ContentPoll(int* doneFiles, int* totalFiles)
{
	if (doneFiles)
		*doneFiles = sDone;

	if (totalFiles)
		*totalFiles = sTotal;

	return (ContentState)sState.load();
}

void ContentShutdown(void)
{
	sQuit = true;

	if (sWorker.joinable())
		sWorker.join();
}
