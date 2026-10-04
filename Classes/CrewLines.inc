//이 파일은 tools/crew/lines.py --emit 가 만든다. 손으로 고치지 마라.
//계열을 바꾸려면 그 도구의 CREW_LINES 를 고치고 다시 돌려라.

//동료를 테마로 묶은 것이 계열이다. 승급은 재료를 먹이면 같은
//계열에서 별이 1 높은 동료 중 하나가 나오는 식이라, 고정 사다리는
//없고 계열과 별 두 값만 있으면 된다.
enum {
	CREWLINE_0,	//마을
	CREWLINE_1,	//바다
	CREWLINE_2,	//엘프
	CREWLINE_3,	//기사
	CREWLINE_4,	//주술
	CREWLINE_5,	//상인
	CREWLINE_CNT,
};

//계열마다 전용 재료. ITEM_ESSENCE 의 detail 번호다.
static const int kCrewLineEssence[CREWLINE_CNT] = {
	33,	//마을 - 아이콘 121, 노란 초승달꼴
	34,	//바다 - 아이콘 122, 푸른 삼지창
	12,	//엘프 - 아이콘 108, 녹색 잎
	39,	//기사 - 아이콘 18, 금빛 문장
	38,	//주술 - 아이콘 126, 보라 물약
	 8,	//상인 - 아이콘 21, 주황 호리병
};

//동료 번호 -> 계열. 별은 crewData 가 아니라 GameConfig.h 의 ★ 주석에
//적혀 있어 같이 낸다.
static const unsigned char kCrewLine[64] = {
	CREWLINE_0,  //0  BOY            ★1
	CREWLINE_0,  //1  GIRL           ★1
	CREWLINE_0,  //2  GRANDMA        ★1
	CREWLINE_5,  //3  GRANDFA        ★1
	CREWLINE_0,  //4  MAN            ★1
	CREWLINE_0,  //5  WOMAN          ★1
	CREWLINE_1,  //6  UNCLE          ★1
	CREWLINE_5,  //7  AUNT           ★1
	CREWLINE_1,  //8  SEAUNCLE       ★2
	CREWLINE_1,  //9  SEASOLDIER     ★2
	CREWLINE_0,  //10 MILESE         ★2
	CREWLINE_4,  //11 ALMA           ★2
	CREWLINE_1,  //12 CREW           ★2
	CREWLINE_0,  //13 TRAVEL         ★2
	CREWLINE_2,  //14 ELFBOY         ★2
	CREWLINE_2,  //15 ELFGIRL        ★2
	CREWLINE_5,  //16 ITEM           ★2
	CREWLINE_2,  //17 ELFUNCLE       ★2
	CREWLINE_2,  //18 ELFAUNT        ★2
	CREWLINE_3,  //19 ADELKNIGHT     ★2
	CREWLINE_4,  //20 OWL            ★3
	CREWLINE_0,  //21 MAID           ★3
	CREWLINE_0,  //22 BUNNYGIRL      ★3
	CREWLINE_5,  //23 MAP            ★3
	CREWLINE_0,  //24 MONICA         ★3
	CREWLINE_1,  //25 SEABOY         ★3
	CREWLINE_3,  //26 DOBEL          ★3
	CREWLINE_3,  //27 GAGEL          ★3
	CREWLINE_2,  //28 ELFGRANDFA     ★3
	CREWLINE_2,  //29 ELFWOMAN       ★3
	CREWLINE_2,  //30 ELFMAN         ★3
	CREWLINE_2,  //31 ELFDANCER      ★3
	CREWLINE_3,  //32 NOBLEMAN       ★3
	CREWLINE_4,  //33 SCHOLAR        ★3
	CREWLINE_5,  //34 NETITEM        ★3
	CREWLINE_0,  //35 FATMAN         ★4
	CREWLINE_5,  //36 CRAFTMAN       ★4
	CREWLINE_0,  //37 LUISE          ★4
	CREWLINE_5,  //38 DOG            ★4
	CREWLINE_3,  //39 KNIGHT         ★4
	CREWLINE_4,  //40 WITCH          ★4
	CREWLINE_0,  //41 BISTRO         ★4
	CREWLINE_1,  //42 SEBASTIAN      ★4
	CREWLINE_1,  //43 FISHING        ★5
	CREWLINE_5,  //44 FRAUD          ★5
	CREWLINE_2,  //45 ELFMAGIC       ★4
	CREWLINE_4,  //46 DARIAN         ★4
	CREWLINE_1,  //47 DONALD         ★4
	CREWLINE_2,  //48 ELFDARK        ★4
	CREWLINE_4,  //49 NEZAR          ★4
	CREWLINE_3,  //50 DURAK          ★4
	CREWLINE_4,  //51 WOMANGHOST     ★4
	CREWLINE_4,  //52 MANGHOST       ★4
	CREWLINE_3,  //53 AUSTIN         ★4
	CREWLINE_3,  //54 ELEIN          ★5
	CREWLINE_5,  //55 USERQUEST      ★4
	CREWLINE_0,  //56 CHEF           ★5
	CREWLINE_1,  //57 CAPTAIN        ★5
	CREWLINE_2,  //58 ELKEIN         ★5
	CREWLINE_5,  //59 DELPIOS        ★5
	CREWLINE_4,  //60 LABETH         ★5
	CREWLINE_3,  //61 EVAN           ★6
	CREWLINE_0,  //62 LORA           ★6
	CREWLINE_3,  //63 KING           ★6
};

static const unsigned char kCrewStar[64] = {
	1, 1, 1, 1, 1, 1, 1, 1,	//0~7
	2, 2, 2, 2, 2, 2, 2, 2,	//8~15
	2, 2, 2, 2, 3, 3, 3, 3,	//16~23
	3, 3, 3, 3, 3, 3, 3, 3,	//24~31
	3, 3, 3, 4, 4, 4, 4, 4,	//32~39
	4, 4, 4, 5, 5, 4, 4, 4,	//40~47
	4, 4, 4, 4, 4, 4, 5, 4,	//48~55
	5, 5, 5, 5, 5, 6, 6, 6,	//56~63
};
