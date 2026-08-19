//이 파일은 GachaData.h 에 있던 배열 정의를 옮겨 담은 것이다.
//
//헤더에 const로 정의하면 내부 링크라 포함하는 .cpp마다 복제되고,
//무엇보다 런타임에 채울 수가 없다. 정의는 여기 한 곳에만 둔다.
//
//자기 헤더만 가져온다. Data.h를 통째로 끌면 UIData.h의 std::string
//때문에 cocos2d.h가 필요해지고, 그러면 팩 생성기가 이 파일만 따로
//컴파일할 수 없다.
//
//tools/content/datafiles.py 가 갈랐다.

#include "GachaData.h"
#include "../Def.h"
#include "../Cmf.h"

static const int miniGachaDetailRate_builtin[] = {
	//별1, 2, 3, 4, 5, 6, 7, 8 
	9000, 900, 90, 9, 1, 0, 0, 0,
};

//게임이 읽는 포인터. 처음에는 내장 기본값을 가리키고, 부팅 때
//팩을 읽으면 그쪽으로 옮겨간다. const는 가리키는 대상에 붙으므로
//게임 코드는 대상을 못 건드리고, 로더만 자기 버퍼를 채워 넘긴다.

const int* miniGachaDetailRate = miniGachaDetailRate_builtin;
