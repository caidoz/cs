#pragma once

#ifndef _DEF_EVENT_H_
#define _DEF_EVENT_H_

typedef enum _event {
	EVENTTYPE_NONE = 0,//이벤트가 없는것으로 이걸 보고 리스트를 띄울지 알려준다.
	EVENTTYPE_PVP,//족보중에 전투를 하면 발생하는 
	EVENTTYPE_QUEST,//퀘스트 아이템 이벤트 
	EVENTTYPE_SHOP,//상점을 
	EVENTTYPE_DEBTDISCOUNT,//빚을 할인해 주는 이벤트
	EVENTTYPE_DOUBLE,//획득량을 두배로 올려주는 이벤트
	EVENTTYPE_BOSSRAID,//보스골드전투
	EVENTTYPE_TOUCHGAME,//중간에 터치를 해서 아이템을 획득하는 이벤트
	EVENTTYPE_DEBUG_NEWGAME,//초기값
	EVENTTYPE_DEBUG_MAXGAME,//최대값
	EVENTTYPE_DEBUG_ENEMYATTACK,//적에게 공격하게 만드는 것

	TOTALEVENTTYPE,

	EVENT_OPEN = 0,
	EVENT_DOING,
	EVENT_CLOSE,

	TOTALEVENTACTION,

	EVENT_BAR_NEW = 0,
	EVENT_BAR_ITEMGET,
	EVENT_BAR_GUAGE_FILL,
	EVENT_BAR_REWARDGET,
	EVENT_BAR_NEXT,
	EVENT_BAR_CLOSE,

	TOTALEVENTBARACTION,

	MAXGAMEEVENT = 10,

	EVENTMOVE_DX = 4 * _2X,
	EVENTMOVE_DY = 4 * _2X,

	//순서를 정하자
	//1. 팝업으로 일단 개요를 보여준다.
	//2. 팝업이 사라지면서 아이콘이 한번 꿈틀하고
	//3. 만약 부가적인 추가 옵션이 있다면 해당 내용을 반영하여 보여준다.(ex 메인퀘스트에 시간제 퀘스트가 붙는 경우)

	//연출의 방법은
	//1. 팝업이 애니메이션으로 뜨고
	//2. 홀드된 상태에서 팝업이 보여지고, 유저의 입력을 기다린다.
	//3. 입력을 받으면 창닫히는 애니메이션과 동시에 
	//

	START_PAGE_DAILY = 0,//데일리 보상
	START_PAGE_MAINQUEST,//메인 퀘스트(메인 퀘스트를 보여줄 때는 팝업으로 퀘스트 개요를 보여준 다음에 서브퀘스트가 있으면 어필하면서 보여준다.)
	START_PAGE_PVPQUEST,//PVP 퀘스트,,팝업으로 보여주고 아이콘을 띄워준다.
	START_PAGE_BOSSRAID,//골드 퀘스트의 경우는 골드를 써서 기타 재화로 바꾸는 일종의 보스레이드이다.
	//START_PAGE_

	TOTAL_START_PAGE_TYPE,

	MAXSTARTPAGE = 10,
};

#endif
