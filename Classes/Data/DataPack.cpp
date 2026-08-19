#include "cocos2d.h"

#include "DataPack.h"
#include "DataList.h"
#include "DataCount.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

USING_NS_CC;

//=============================================================================
// 데이터 팩 로더
//
// 부팅 때 팩을 읽어 Data/*.h 의 포인터들을 팩 안쪽으로 옮긴다.
// 실패하면 아무것도 바꾸지 않는다. 포인터는 내장 기본값을 계속 가리킨다.
//
// 팩이 맞는지 보는 검사는 DataPackCheck.cpp 에 있다. 거기는 cocos를 안 써서
// 게임 없이도 시험할 수 있다(tools/content/check_pack.py).
//
// 팩을 만드는 쪽은 tools/content/make_pack.py 다. 양쪽이 DataList.h 하나를
// 같이 쓰므로 목록이 어긋날 수 없다.
//=============================================================================

//읽어둔 팩. 포인터들이 이 안을 가리키므로 게임이 도는 동안 놓으면 안 된다.
static unsigned char* sPack = NULL;
static bool sInUse = false;

//읽어둔 팩의 목차. DataPackCount 가 쓴다.
static const unsigned char* sDir = NULL;
static int sDirCount = 0;

bool DataPackInUse(void)
{
	return sInUse;
}

bool DataPackLoad(const char* fileName)
{
	std::string path = FileUtils::getInstance()->fullPathForFilename(fileName);

	if (path.empty()) {
		CCLOG("DataPackLoad: %s 를 못 찾았다. 내장 데이터로 간다", fileName);
		return false;
	}

	FILE* fp = fopen(path.c_str(), "rb");

	if (!fp) {
		CCLOG("DataPackLoad: %s 를 못 열었다", path.c_str());
		return false;
	}

	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	if (size < 20) {
		fclose(fp);
		CCLOG("DataPackLoad: 파일이 너무 작다(%ld)", size);
		return false;
	}

	unsigned char* buf = (unsigned char*)malloc((size_t)size);

	if (!buf) {
		fclose(fp);
		return false;
	}

	if (fread(buf, 1, (size_t)size, fp) != (size_t)size) {
		fclose(fp);
		free(buf);
		CCLOG("DataPackLoad: 다 읽지 못했다");
		return false;
	}

	fclose(fp);

	//---- 맞는 팩인지 먼저 다 본다 ----
	char why[4096];
	int keyCount[DPK_KEY_MAX];

	why[0] = 0;

	if (DataPackCheck(buf, size, keyCount, why, (int)sizeof(why)) != 0) {
		free(buf);
		CCLOG("DataPackLoad: 팩이 클라이언트와 안 맞는다. 내장 데이터로 간다\n%s", why);
		return false;
	}

	int count;
	memcpy(&count, buf + 8, 4);

	const unsigned char* dir = buf + 16;
	const unsigned char* dat = dir + (unsigned int)count * DPK_ENTRYSIZE;

	//---- 이제 옮긴다 ----
#define POINT_ONE(N, SZ, K, C, KEY, W, B) \
	{ \
		unsigned int c = 0; \
		int s = 0, k = 0; \
		const unsigned char* e = DataPackFind(dir, count, #N, &c, &s, &k); \
		unsigned int off = 0; \
		memcpy(&off, e + DPK_NAMELEN + 8, 4); \
		N = (decltype(N))(dat + off); \
	}
	DATA_LIST(POINT_ONE)
#undef POINT_ONE

	//예전에 읽어둔 팩이 있으면 이제 놓아준다.
	if (sPack)
		free(sPack);

	sPack = buf;
	sInUse = true;
	sDir = dir;
	sDirCount = count;

	//포인터를 옮겼으니 개수도 팩 기준으로 다시 잡는다.
	DataCountRefresh();

	CCLOG("DataPackLoad: %s 를 읽었다 (배열 %d개, %ld 바이트)", fileName, count, size);
	return true;
}

int DataPackCount(const char* name)
{
	unsigned int c = 0;
	int s = 0, k = 0;

	if (!sDir || !DataPackFind(sDir, sDirCount, name, &c, &s, &k))
		return -1;

	return (int)c;
}
