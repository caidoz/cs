#include "cocos2d.h"

#include "DataPack.h"
#include "DataList.h"

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
// 팩을 만드는 쪽은 tools/content/make_pack.py 다. 양쪽이 DataList.h 하나를
// 같이 쓰므로 목록이 어긋날 수 없다.
//=============================================================================

//읽어둔 팩. 포인터들이 이 안을 가리키므로 게임이 도는 동안 놓으면 안 된다.
static unsigned char* sPack = NULL;
static bool sInUse = false;

unsigned int DataPackCrc(const void* buf, unsigned int len)
{
	const unsigned char* p = (const unsigned char*)buf;
	unsigned int crc = 0xFFFFFFFFu;
	unsigned int i;
	int k;

	for (i = 0; i < len; i++) {
		crc ^= p[i];

		for (k = 0; k < 8; k++)
			crc = (crc >> 1) ^ (0xEDB88320u & (0u - (crc & 1u)));
	}

	return ~crc;
}

//빌드 상수 지문. 팩을 만든 쪽과 같은 방식으로 만든다.
//TSIZE나 _2X가 바뀌면 값이 달라져서 옛 팩을 거부하게 된다.
unsigned int DataPackAbi(void)
{
	char buf[1024];
	int at = 0;

#define ABI_ONE(N) at += sprintf(buf + at, "%s=%d;", #N, (int)(N));
	DATAPACK_ABI_LIST(ABI_ONE)
#undef ABI_ONE

	//정의 여부만 보는 것들
	at += sprintf(buf + at, "%s", DATAPACK_ABI_FLAGS);

	return DataPackCrc(buf, (unsigned int)at);
}

bool DataPackInUse(void)
{
	return sInUse;
}

//팩 안에서 이름으로 항목을 찾는다.
static const unsigned char* FindEntry(const unsigned char* dir, int count,
	const char* name, unsigned int* outCount, int* outSize, int* outKind)
{
	int i;

	for (i = 0; i < count; i++) {
		const unsigned char* e = dir + (unsigned int)i * DPK_ENTRYSIZE;

		if (strncmp((const char*)e, name, DPK_NAMELEN - 1) != 0)
			continue;

		*outSize = e[DPK_NAMELEN + 0];
		*outKind = e[DPK_NAMELEN + 1];
		memcpy(outCount, e + DPK_NAMELEN + 4, 4);

		return e;
	}

	return NULL;
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

	//---- 머리 검사 ----
	unsigned int magic, abi, body, crc;
	int count;

	memcpy(&magic, buf + 0, 4);
	memcpy(&abi, buf + 4, 4);
	memcpy(&count, buf + 8, 4);
	memcpy(&body, buf + 12, 4);

	if (magic != DPK_MAGIC) {
		free(buf);
		CCLOG("DataPackLoad: 팩이 아니다");
		return false;
	}

	//디스크가 차거나 다운로드가 끊겨 반쯤 쓰인 파일을 걸러낸다.
	memcpy(&crc, buf + size - 4, 4);

	if (DataPackCrc(buf, (unsigned int)size - 4) != crc) {
		free(buf);
		CCLOG("DataPackLoad: 체크섬이 안 맞는다. 내장 데이터로 간다");
		return false;
	}

	//값에 TSIZE, _2X 같은 빌드 상수가 이미 곱해져 들어 있다. 클라이언트가
	//그 상수를 바꿨다면 옛 팩은 조용히 틀린 값이 된다. 여기서 막는다.
	if (abi != DataPackAbi()) {
		free(buf);
		CCLOG("DataPackLoad: 빌드 상수가 다르다(팩 %08x, 클라 %08x). 내장 데이터로 간다",
			abi, DataPackAbi());
		return false;
	}

	if (count <= 0 || (long)(16 + (unsigned int)count * DPK_ENTRYSIZE + body + 4) > size) {
		free(buf);
		CCLOG("DataPackLoad: 크기가 앞뒤가 안 맞는다");
		return false;
	}

	const unsigned char* dir = buf + 16;
	const unsigned char* dat = dir + (unsigned int)count * DPK_ENTRYSIZE;

	//---- 먼저 전부 찾아본다 ----
	//하나라도 없거나 어긋나면 아무것도 바꾸지 않는다. 절반만 팩을 가리키는
	//상태가 제일 나쁘다.
	bool ok = true;

#define CHECK_ONE(N, SZ, K, C) \
	{ \
		unsigned int c = 0; \
		int s = 0, k = 0; \
		const unsigned char* e = FindEntry(dir, count, #N, &c, &s, &k); \
		if (!e) { \
			CCLOG("DataPackLoad: %s 가 팩에 없다", #N); \
			ok = false; \
		} \
		else if (c != (unsigned int)(C) || s != (SZ) || k != (K)) { \
			CCLOG("DataPackLoad: %s 가 안 맞는다(팩 %u/%d/%d, 클라 %d/%d/%d)", \
				#N, c, s, k, (int)(C), (int)(SZ), (int)(K)); \
			ok = false; \
		} \
	}
	DATA_LIST(CHECK_ONE)
#undef CHECK_ONE

	if (!ok) {
		free(buf);
		CCLOG("DataPackLoad: 팩이 클라이언트와 안 맞는다. 내장 데이터로 간다");
		return false;
	}

	//---- 이제 옮긴다 ----
#define POINT_ONE(N, SZ, K, C) \
	{ \
		unsigned int c = 0; \
		int s = 0, k = 0; \
		const unsigned char* e = FindEntry(dir, count, #N, &c, &s, &k); \
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

	CCLOG("DataPackLoad: %s 를 읽었다 (배열 %d개, %ld 바이트)", fileName, count, size);
	return true;
}
