#include "cocos2d.h"

#include "../Def.h"
#include "DataCount.h"
#include "DataPack.h"
#include "CmfBlob.h"

USING_NS_CC;

//팩이 없을 때의 값 = 내장 데이터의 개수.
int gTotalEnemy = TOTALENEMY;
int gTotalCrew = TOTAL_CREW;
int gTotalSkill = TOTAL_SKILL;
int gTotalCastle = TOTALCASTLE;
int gTotalMap = TOTALMAP;

//cmf 개수는 CmfRelink() 가 잡는다. 표를 채우면서 같이 정해지기 때문이다.
int gTotalCmf = CMF_BUILTIN_COUNT;

//팩 안 배열의 길이에서 개수를 얻는다.
//  name  : 개수를 대표하는 배열. 한 칸이 콘텐츠 하나에 해당해야 한다.
//  width : 한 콘텐츠가 차지하는 칸 수. enemyZoom 처럼 1칸이면 1.
//  cap   : 용량. 넘으면 이 클라이언트가 감당 못 한다.
//  def   : 팩에 없을 때 쓸 내장 개수.
static int CountFromPack(const char* name, int width, int cap, int def)
{
	int cells = DataPackCount(name);

	if (cells < 0 || width <= 0)
		return def;

	int n = cells / width;

	if (n > cap) {
		//여기 걸리면 팩이 이 클라이언트의 용량보다 큰 콘텐츠를 담고 있다.
		//Capacity.h 의 CAP_* 를 올려 앱을 새로 올려야 한다. 그 전까지는
		//용량까지만 쓴다. 뒤쪽 콘텐츠는 안 보이지만 죽지는 않는다.
		CCLOG("DataCount: %s 가 %d개다. 용량 %d를 넘는다. 앱을 올려야 한다",
			name, n, cap);
		n = cap;
	}

	return n;
}

void DataCountRefresh(void)
{
	gTotalEnemy = CountFromPack("enemyZoom", 1, CAP_ENEMY, TOTALENEMY);
	gTotalCrew = CountFromPack("crewData", CREWDATASIZE, CAP_CREW, TOTAL_CREW);
	gTotalSkill = CountFromPack("skillData", SKILLDATASIZE, CAP_SKILL, TOTAL_SKILL);
	gTotalCastle = CountFromPack("castleOrder", 1, CAP_CASTLE, TOTALCASTLE);

	//맵 데이터는 아직 Classes/Write.h 에 있어서 팩에 안 들어갔다.
	//그쪽을 팩으로 옮기면 여기도 CountFromPack 으로 바꾼다.
	gTotalMap = TOTALMAP;

	CCLOG("DataCount: 몬스터 %d/%d, 동료 %d/%d, 스킬 %d/%d, 성 %d/%d, 맵 %d/%d",
		gTotalEnemy, CAP_ENEMY, gTotalCrew, CAP_CREW, gTotalSkill, CAP_SKILL,
		gTotalCastle, CAP_CASTLE, gTotalMap, CAP_MAP);
}
