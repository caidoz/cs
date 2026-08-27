#pragma once

#ifndef _CONTENT_H_
#define _CONTENT_H_

#include <string>
#include <vector>

//=============================================================================
// 콘텐츠 배포
//
// 앱을 새로 올리지 않고 몬스터나 캐릭터를 추가하려면 두 가지가 내려와야 한다.
//
//   1. 데이터 : Resources/data/content.pack   (팩 하나)
//   2. 아트   : Resources/res/*.png, sounds/*.mp3
//
// 데이터 쪽은 이미 팩 하나로 모였다. 아트는 파일 이름이 데이터에서 나온다
// ("res/" + textId[...] + ".png"). 그래서 새 캐릭터의 그림도 파일만 놓이면
// 코드를 안 고치고 쓰인다.
//
// [어떻게 갈아끼우나]
// 내려받은 파일은 쓰기 가능한 곳에 두고, 그 폴더를 검색 경로 맨 앞에 넣는다.
// cocos 의 FileUtils 가 이름을 찾을 때 거기부터 보므로, 같은 이름이 있으면
// 내려받은 쪽이 이긴다. 호출부는 한 줄도 안 바뀐다.
//
//     쓰기가능/content/res/aa.png   <- 내려받은 것. 이게 이긴다
//     (앱에 딸려온) res/aa.png      <- 없으면 이것
//
// [왜 게임 도중에 안 바꾸나]
// 팩을 읽으면 Data/*.h 의 포인터 수백 개가 팩 버퍼 안쪽을 가리킨다. 게임이
// 도는 중에 그 버퍼를 바꾸면 읽고 있던 자리가 사라진다. 아트도 마찬가지로
// 이미 GPU에 올라간 텍스처와 새 파일이 섞인다.
//
// 그래서 받는 것과 쓰는 것을 갈랐다.
//
//     받기 : 게임이 도는 동안 staging 폴더로 조금씩 내려받는다.
//     쓰기 : 다음 부팅 때 파일 이름만 바꿔 넣는다. 순식간이고 안전하다.
//
// 이러면 로딩 화면으로 기다릴 일이 없다. 갱신이 있어도 이번 판은 그대로
// 놀고, 다음에 켤 때 새 콘텐츠로 시작한다.
//
// [중간에 죽어도 안전하다]
// staging 에 다 받고 나서야 매니페스트를 쓴다. 매니페스트가 없으면 덜 받은
// 것이므로 다음에 처음부터 다시 받는다. 반쯤 갱신된 채로 굳지 않는다.
//=============================================================================

//매니페스트 한 줄. 파일 하나를 가리킨다.
struct ContentFile {
	std::string path;		//"res/aa.png" 처럼 Resources 기준 상대 경로
	unsigned int size;
	unsigned long long hash;	//FNV-1a 64. ContentHash() 참고
};

//파일 지문. tools/content/make_manifest.py 의 fnv1a64 와 같아야 한다.
//
//CRC-32 를 쓰면 안 된다. 팩은 끝에 자기 CRC-32 를 담는데, 메시지 뒤에 자기
//CRC 를 붙이면 전체 CRC 가 늘 같은 값(0x2144DF1C)이 된다. 그러면 어떤 판의
//팩이든 지문이 똑같아서, 바뀐 것을 크기로만 가리게 된다.
unsigned long long ContentHash(const void* buf, unsigned int len);

//---- 부팅 ----

//부팅 아주 초기에 부른다. 리소스를 하나라도 읽기 전이어야 한다.
//  1. 뒤에서 다 받아둔 것이 있으면 이때 반영한다(파일 이름 바꾸기뿐).
//  2. 내려받은 폴더를 검색 경로 맨 앞에 넣는다.
void ContentBoot(void);

//---- 손으로 덮어쓰기 (개발용) ----
//
// 아래 폴더에 파일을 넣으면 그것이 이긴다. 팩이든 그림이든 소리든,
// 이름만 같으면 된다.
//
//     <쓰기가능경로>/override/
//         data/content.pack      <- 팩을 통째로 갈아끼운다
//         res/aa.png             <- 그림 한 장만 바꾼다
//
// 쓰기 가능 경로는 부팅 로그가 알려준다(Content: 내려받기 폴더 ...).
// win32 라면 C:/Users/<이름>/AppData/Local/cs/override/ 다.
//
// 왜 필요한가. 데이터를 하나 고쳐 보려면 지금은 팩을 다시 내고 프로젝트를
// 다시 빌드해야 한다. 밸런스처럼 값 하나를 바꿔 보고 되돌리기를 반복하는
// 일에는 그 왕복이 너무 길다.
//
// 켜져 있으면 부팅 로그에 크게 남는다. 조용히 다른 데이터로 도는 것이
// 제일 나쁘다 - 왜 안 고쳐지는지 한참 헤매게 된다.
void ContentOverrideBoot(void);

//덮어쓰기 폴더가 켜져 있는가. 화면에 표시하고 싶을 때 쓴다.
bool ContentOverrideOn(void);

//지금 갖고 있는 콘텐츠 판번호. 0이면 앱에 딸려온 것 그대로다.
long long ContentVersion(void);

//---- 뒤에서 받기 ----

enum ContentState {
	CONTENT_IDLE = 0,	//아직 시작 안 했다
	CONTENT_CHECKVER,	//판번호만 먼저 보는 중
	CONTENT_CHECKING,	//매니페스트를 보는 중
	CONTENT_DOWNLOADING,	//받는 중
	CONTENT_READY,		//다 받았다. 다음 부팅 때 반영된다
	CONTENT_UPTODATE,	//받을 것이 없었다
	CONTENT_FAILED,		//실패했다. 지금 콘텐츠는 그대로다
};

//뒤에서 갱신을 시작한다. 곧바로 돌아온다. 두 번 불러도 하나만 돈다.
void ContentUpdateBegin(void);

//게임 루프에서 매 프레임 부른다. 갱신을 한 칸 굴린다.
//네트워크는 HttpClient 가 자기 실에서 하므로 여기서 안 막힌다.
void ContentUpdateStep(void);

//진행 상태. doneFiles/totalFiles 는 화면에 띄울 때 쓴다.
ContentState ContentPoll(int* doneFiles, int* totalFiles);

//무슨 일이 있었는지 한 줄. 화면에 띄우거나 로그로 남긴다.
const char* ContentLastMessage(void);

//다 받아서 다음 부팅 때 반영될 것이 있는가.
bool ContentHasStaged(void);

//끝날 때 부른다. 받던 중이면 그만둔다.
void ContentShutdown(void);

#endif
