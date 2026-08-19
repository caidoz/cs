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
// [갱신 순서]
// 매니페스트를 맨 나중에 쓴다. 중간에 죽으면 옛 매니페스트가 남아서 다음
// 부팅 때 같은 갱신을 다시 한다. 반쯤 갱신된 상태로 굳지 않는다.
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

//부팅 아주 초기에 부른다. 내려받은 폴더를 검색 경로 맨 앞에 넣는다.
//리소스를 하나라도 읽기 전에 불러야 한다.
void ContentInstallSearchPath(void);

//지금 갖고 있는 콘텐츠 판번호. 0이면 앱에 딸려온 것 그대로다.
long long ContentVersion(void);

//갱신을 한 번 돌린다. 받은 파일 수를 돌려준다. 실패하면 -1.
//실패해도 지금 쓰던 콘텐츠는 그대로다.
int ContentUpdate(void);

//마지막 갱신에서 무슨 일이 있었는지. 화면에 띄우거나 로그로 남긴다.
const char* ContentLastMessage(void);

#endif
