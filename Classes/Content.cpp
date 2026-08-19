#include "cocos2d.h"

#include "Content.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

USING_NS_CC;

//=============================================================================
// 콘텐츠 배포
//
//   1. 경로            - 내려받은 폴더를 검색 경로 맨 앞에
//   2. 매니페스트      - 무슨 파일이 어떤 판인지 적은 표
//   3. 임시 로컬 CDN   - ★ 진짜 CDN이 붙으면 여기만 갈아끼운다
//   4. 갱신 흐름       - 비교 -> 받기 -> 검사 -> 확정
//
// 자세한 얼개는 Content.h 를 보라.
//=============================================================================

//내려받은 것을 두는 곳. 쓰기 가능 경로 아래 이 이름으로 만든다.
#define CONTENT_DIR "content"

//매니페스트 파일 이름. 내려받은 폴더와 앱 양쪽에 같은 이름으로 있다.
#define CONTENT_MANIFEST "manifest.tsv"

//한 번에 이만큼 넘으면 이상한 것이다. 잘못된 매니페스트로 디스크를 채우지 않는다.
#define CONTENT_MAXFILE (256 * 1024 * 1024)

static long long sVersion = 0;
static char sMessage[256] = "아직 갱신한 적 없다";

static void Say(const char* fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(sMessage, sizeof(sMessage), fmt, ap);
	va_end(ap);

	CCLOG("Content: %s", sMessage);
}

//파일 지문. make_manifest.py 의 fnv1a64 와 같은 것이어야 한다.
//왜 CRC-32 가 아닌지는 Content.h 주석을 보라.
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

const char* ContentLastMessage(void)
{
	return sMessage;
}

long long ContentVersion(void)
{
	return sVersion;
}

//=============================================================================
// 1. 경로
//=============================================================================

//내려받은 것을 두는 폴더. 끝에 / 가 붙는다.
static std::string LocalDir(void)
{
	return FileUtils::getInstance()->getWritablePath() + CONTENT_DIR + "/";
}

void ContentInstallSearchPath(void)
{
	FileUtils* fu = FileUtils::getInstance();
	std::string dir = LocalDir();

	fu->createDirectory(dir);

	//맨 앞에 넣는다. 같은 이름이 있으면 내려받은 쪽이 이긴다.
	//
	//이 한 줄이 이 기능의 전부다. "res/aa.png" 를 읽는 코드가 수백 군데
	//있지만 하나도 안 고쳐도 된다. 이름을 찾는 일은 전부 FileUtils 가 한다.
	std::vector<std::string> paths = fu->getSearchPaths();

	if (std::find(paths.begin(), paths.end(), dir) == paths.end()) {
		paths.insert(paths.begin(), dir);
		fu->setSearchPaths(paths);
	}

	CCLOG("Content: 내려받기 폴더 %s", dir.c_str());
}

//=============================================================================
// 2. 매니페스트
//
// 형식은 세이브 덤프와 같은 결로 맞췄다. 탭으로 나눈 표다.
//
//     #content 1
//     version <탭> 2026082001
//     res/aa.png <탭> 12345 <탭> a1b2c3d4e5f60718
//     ...
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

//내려받은 폴더의 매니페스트. 없으면 앱에 딸려온 것을 본다.
static bool ReadLocalManifest(long long* ver, std::vector<ContentFile>* fs)
{
	FileUtils* fu = FileUtils::getInstance();
	std::string p = LocalDir() + CONTENT_MANIFEST;
	std::string text;

	if (fu->isFileExist(p))
		text = fu->getStringFromFile(p);
	else
		text = fu->getStringFromFile(CONTENT_MANIFEST);

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
// 지금은 서버가 없다. 그래서 "먼 곳"을 폴더 하나로 흉내낸다. 그 폴더에
// manifest.tsv 와 파일들을 놓으면 갱신이 도는지 그대로 확인할 수 있다.
//
//     cdn/manifest.tsv
//     cdn/data/content.pack
//     cdn/res/aa.png
//
// 진짜로 바꿀 때 고칠 것은 아래 두 함수뿐이다.
//   CdnFetchManifest : GET <베이스>/manifest.tsv
//   CdnFetchFile     : GET <베이스>/<경로>
//
// 둘 다 지금은 곧바로 돌려주지만, 진짜 CDN은 느리다. 그때는 여기가 비동기가
// 되고 부르는 쪽이 로딩 화면을 띄우는 흐름으로 바뀐다.
//=============================================================================

//흉내낼 CDN 폴더. 실행 파일 옆의 cdn/ 을 본다.
static std::string CdnDir(void)
{
	return FileUtils::getInstance()->getWritablePath() + "cdn/";
}

static bool CdnFetchManifest(std::string* out)
{
	std::string p = CdnDir() + CONTENT_MANIFEST;
	FILE* fp = fopen(p.c_str(), "rb");

	if (!fp)
		return false;

	char buf[4096];
	size_t n;

	out->clear();

	while ((n = fread(buf, 1, sizeof(buf), fp)) > 0)
		out->append(buf, n);

	fclose(fp);
	return true;
}

static bool CdnFetchFile(const std::string& path, std::string* out)
{
	std::string p = CdnDir() + path;
	FILE* fp = fopen(p.c_str(), "rb");

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

//=============================================================================
// 4. 갱신 흐름
//=============================================================================

//"res/x/y.png" 처럼 중간에 폴더가 있으면 미리 만들어 둔다.
static void MakeDirs(const std::string& full)
{
	FileUtils* fu = FileUtils::getInstance();
	size_t at = 0;

	for (;;) {
		size_t sl = full.find('/', at);

		if (sl == std::string::npos)
			break;

		std::string dir = full.substr(0, sl + 1);

		if (!fu->isDirectoryExist(dir))
			fu->createDirectory(dir);

		at = sl + 1;
	}
}

//먼저 임시 이름으로 쓰고 나서 옮긴다. 쓰다 죽어도 반쪽 파일이 안 남는다.
static bool WriteFile(const std::string& full, const std::string& body)
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

//지금 갖고 있는 것과 견줘 무엇을 받아야 하는지 고른다.
static void PickChanged(const std::vector<ContentFile>& want,
	const std::vector<ContentFile>& have, std::vector<ContentFile>* out)
{
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
		if (same && !FileUtils::getInstance()->isFileExist(LocalDir() + w.path))
			same = false;

		if (!same)
			out->push_back(w);
	}
}

int ContentUpdate(void)
{
	std::string text;

	if (!CdnFetchManifest(&text)) {
		Say("CDN 매니페스트를 못 읽었다. 지금 콘텐츠를 그대로 쓴다");
		return -1;
	}

	long long remoteVer = 0;
	std::vector<ContentFile> remote;

	if (!ParseManifest(text, &remoteVer, &remote)) {
		Say("CDN 매니페스트 형식이 다르다");
		return -1;
	}

	long long localVer = 0;
	std::vector<ContentFile> local;

	ReadLocalManifest(&localVer, &local);
	sVersion = localVer;

	if (remoteVer == localVer) {
		Say("최신이다 (판 %lld, 파일 %d개)", localVer, (int)local.size());
		return 0;
	}

	std::vector<ContentFile> todo;

	PickChanged(remote, local, &todo);

	Say("판 %lld -> %lld, 받을 파일 %d개", localVer, remoteVer, (int)todo.size());

	std::string dir = LocalDir();
	int got = 0;

	for (size_t i = 0; i < todo.size(); i++) {
		const ContentFile& f = todo[i];
		std::string body;

		if (!CdnFetchFile(f.path, &body)) {
			Say("%s 를 못 받았다. 갱신을 멈춘다", f.path.c_str());
			return -1;
		}

		//받은 것이 온전한지 본다. 크기만 보면 내용이 바뀐 것을 못 잡는다.
		if (body.size() != f.size) {
			Say("%s 크기가 다르다 (받은 %u, 적힌 %u)",
				f.path.c_str(), (unsigned int)body.size(), f.size);
			return -1;
		}

		if (ContentHash(body.data(), (unsigned int)body.size()) != f.hash) {
			Say("%s 가 깨졌다 (지문 불일치)", f.path.c_str());
			return -1;
		}

		if (!WriteFile(dir + f.path, body)) {
			Say("%s 를 못 썼다", f.path.c_str());
			return -1;
		}

		got++;
	}

	//매니페스트를 맨 나중에 쓴다. 중간에 죽으면 옛 매니페스트가 남아서
	//다음 부팅 때 같은 갱신을 다시 한다. 반쯤 갱신된 채로 굳지 않는다.
	if (!WriteFile(dir + CONTENT_MANIFEST, BuildManifest(remoteVer, remote))) {
		Say("매니페스트를 못 썼다. 다음에 다시 받는다");
		return -1;
	}

	sVersion = remoteVer;

	//파일이 바뀌었으니 이미 읽어둔 것을 버린다. 안 그러면 옛 그림이 남는다.
	Director::getInstance()->getTextureCache()->removeAllTextures();
	SpriteFrameCache::getInstance()->removeSpriteFrames();

	Say("판 %lld 로 갱신했다 (파일 %d개)", remoteVer, got);
	return got;
}
