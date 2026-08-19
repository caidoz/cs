#include "DataPack.h"
#include "DataList.h"

#include <stdio.h>
#include <string.h>

//=============================================================================
// 팩 검사
//
// 팩이 이 클라이언트와 맞는지만 본다. 포인터는 안 건드린다.
//
// [왜 따로 뒀나]
// cocos를 안 쓴다. 그래서 게임을 띄우지 않고도 시험할 수 있다.
// tools/content/check_pack.py 가 이 파일만 컴파일해서, CDN이 내려줄 팩을
// 클라이언트가 정말로 받아들이는지 확인한다.
//
// 검사가 DataPackLoad 안에 박혀 있었을 때는 그걸 확인할 방법이 게임을
// 띄우는 것뿐이었다. 그래서 매크로 인자 수가 어긋난 것을 못 잡았다.
// (MSVC는 매크로 인자가 남으면 오류가 아니라 경고만 낸다)
//=============================================================================

//팩 안에서 이름으로 항목을 찾는다.
const unsigned char* DataPackFind(const unsigned char* dir, int count,
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

int DataPackCapOf(int key)
{
	switch (key) {
	case DPK_KEY_ENEMY:		return CAP_ENEMY;
	case DPK_KEY_CREW:		return CAP_CREW;
	case DPK_KEY_SKILL:		return CAP_SKILL;
	case DPK_KEY_CASTLE:	return CAP_CASTLE;
	case DPK_KEY_MAP:		return CAP_MAP;
	}

	return 0;
}

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
//개수(TOTALENEMY 등)는 여기 안 들어간다. 들어가면 콘텐츠를 못 늘린다.
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

//msg 에 실패 사유를 적는다. 성공하면 0, 실패하면 실패한 항목 수.
//outKeyCount 는 키별 콘텐츠 개수(-1 이면 그 키를 쓰는 배열이 없다).
int DataPackCheck(const unsigned char* buf, long size,
	int* outKeyCount, char* msg, int msglen)
{
	unsigned int magic, abi, body, crc;
	int count;
	int bad = 0;
	int ki;
	int at = 0;

	//msg 에 한 줄 보태는 매크로. 넘치면 그냥 안 쓴다.
#define SAY(...) \
	do { \
		if (msg && at < msglen - 1) \
			at += snprintf(msg + at, (size_t)(msglen - at), __VA_ARGS__); \
	} while (0)

	int keyCount[DPK_KEY_MAX];

	for (ki = 0; ki < DPK_KEY_MAX; ki++)
		keyCount[ki] = -1;

	if (size < 20) {
		SAY("파일이 너무 작다(%ld)\n", size);
		return 1;
	}

	memcpy(&magic, buf + 0, 4);
	memcpy(&abi, buf + 4, 4);
	memcpy(&count, buf + 8, 4);
	memcpy(&body, buf + 12, 4);

	if (magic != DPK_MAGIC) {
		SAY("팩이 아니다\n");
		return 1;
	}

	//디스크가 차거나 다운로드가 끊겨 반쯤 쓰인 파일을 걸러낸다.
	memcpy(&crc, buf + size - 4, 4);

	if (DataPackCrc(buf, (unsigned int)size - 4) != crc) {
		SAY("체크섬이 안 맞는다\n");
		return 1;
	}

	//값에 TSIZE, _2X 같은 빌드 상수가 이미 곱해져 들어 있다. 클라이언트가
	//그 상수를 바꿨다면 옛 팩은 조용히 틀린 값이 된다. 여기서 막는다.
	if (abi != DataPackAbi()) {
		SAY("빌드 상수가 다르다(팩 %08x, 클라 %08x)\n", abi, DataPackAbi());
		return 1;
	}

	if (count <= 0 ||
		(long)(16 + (unsigned int)count * DPK_ENTRYSIZE + body + 4) > size) {
		SAY("크기가 앞뒤가 안 맞는다\n");
		return 1;
	}

	const unsigned char* dir = buf + 16;

	//하나라도 어긋나면 아무것도 옮기지 않는다. 절반만 팩을 가리키는 상태가
	//제일 나쁘다. 그래서 옮기기 전에 전부 본다.
#define CHECK_ONE(N, SZ, K, C, KEY, W, B) \
	{ \
		unsigned int c = 0; \
		int s = 0, k = 0; \
		const unsigned char* e = DataPackFind(dir, count, #N, &c, &s, &k); \
		if (!e) { \
			SAY("%s 가 팩에 없다\n", #N); \
			bad++; \
		} \
		else if (s != (SZ) || k != (K)) { \
			SAY("%s 의 원소 형식이 다르다(팩 %d/%d, 클라 %d/%d)\n", \
				#N, s, k, (int)(SZ), (int)(K)); \
			bad++; \
		} \
		else if ((KEY) == DPK_KEY_NONE) { \
			/* 길이가 고정인 배열. 정확히 같아야 한다. */ \
			if (c != (unsigned int)(C)) { \
				SAY("%s 의 칸 수가 다르다(팩 %u, 클라 %d)\n", #N, c, (int)(C)); \
				bad++; \
			} \
		} \
		else if ((W) <= 0 || c % (unsigned int)(W)) { \
			SAY("%s 의 칸 수 %u 가 폭 %d 로 안 나눠진다\n", #N, c, (int)(W)); \
			bad++; \
		} \
		else { \
			/* 콘텐츠에 맞춰 길어지는 배열. 용량 안이면 받는다. */ \
			/* 0번부터 안 담는 배열이 있다. 그래서 시작번호를 더한다. */ \
			int n = (int)(c / (unsigned int)(W)) + (B); \
			if (n > DataPackCapOf(KEY)) { \
				SAY("%s 가 %d개다. 용량 %d를 넘는다. 앱을 올려야 한다\n", \
					#N, n, DataPackCapOf(KEY)); \
				bad++; \
			} \
			else if (keyCount[KEY] < 0) { \
				keyCount[KEY] = n; \
			} \
			else if (keyCount[KEY] != n) { \
				SAY("%s 가 %d개인데 같은 종류의 다른 배열은 %d개다\n", \
					#N, n, keyCount[KEY]); \
				bad++; \
			} \
		} \
	}
	DATA_LIST(CHECK_ONE)
#undef CHECK_ONE

	if (outKeyCount) {
		for (ki = 0; ki < DPK_KEY_MAX; ki++)
			outKeyCount[ki] = keyCount[ki];
	}

#undef SAY
	return bad;
}
