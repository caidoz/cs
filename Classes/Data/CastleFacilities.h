#pragma once
// Existing save slots are retained. Facilities follow production, armory,
// food/entertainment, culture and royal specialization, with six visual states.
namespace CastleFacilities {
struct Facility { const char* name; const char* product; int basePerHour; };
static const int Counts[10]={5,5,5,5,5,5,5,5,5,5};
// Logical facility -> existing physical sector. Industrial castles keep their
// original lower forge and middle farm; no room position or dimensions change.
static const int SectorIndex[10][5]={
 {0},{0,1},{0,1},{0,1,2},{1,0,2},{1,0,2,3},
 {0,1,2,3},{0,1,2,3,4},{0,1,2,3,4},{0,1,2,3,4}
};
static const char* Themes[10]={"목재 개척 농장","사암 보급 요새","백석 기사단","비취 수산 요새","강철 공업 요새","청록 공학 성","붉은 봉황 성","백조 학술 궁전","수정 마법 성","태양 왕실 궁전"};
static const Facility Rooms[10][5]={
 {{"개척 곡물·낙농장","식량",12},{"개척 장비 공방","장비",4},{"개척 조리실","먹거리",4},{"개척 필사실","고급 문화",4},{"개척 약초원","왕실 특화",4}},
 {{"사암 곡물 생산실","식량",18},{"보급 요새 대장간","장비",6},{"보급 제빵소","먹거리",6},{"사암 기록실","고급 문화",6},{"사암 약초원","왕실 특화",6}},
 {{"기사단 곡물·낙농장","식량",24},{"기사단 무기 연구실","장비",10},{"백석 제빵소","먹거리",8},{"백석 필사실","고급 문화",8},{"백석 약초원","왕실 특화",8}},
 {{"비취 양식장","식량",30},{"비취 갑옷 대장간","장비",14},{"항구 식당·주점","먹거리",8},{"비취 항해 도서관","고급 문화",10},{"비취 수생 약초원","왕실 특화",10}},
 {{"기계식 곡물·낙농장","식량",36},{"강철 장비 개발소","장비",20},{"공업 요새 양조 식당","먹거리",12},{"강철 기술 서고","고급 문화",12},{"강철 약초 온실","왕실 특화",12}},
 {{"공학 수경 재배실","식량",42},{"태엽 장비 연구실","장비",24},{"청록 식당·음악 주점","먹거리",16},{"공학 도서관·성소","고급 문화",12},{"청록 공학 온실","왕실 특화",16}},
 {{"봉황 곡물·제빵소","식량",48},{"봉황 갑옷 대장간","장비",28},{"봉황 연회·공연 주점","먹거리",14},{"봉황 도서관·성당","고급 문화",22},{"봉황 약초 온실","왕실 특화",20}},
 {{"백조 수산·허브 농장","식량",54},{"학술 장비 연구실","장비",24},{"백조 식당·음악당","먹거리",14},{"학술 도서관·예배당","고급 문화",30},{"백조 왕실 온실","왕실 특화",24}},
 {{"마법 곡물·양식장","식량",60},{"수정 장비 연구 대장간","장비",32},{"마법 식당·공연 주점","먹거리",30},{"비전 도서관·수정 성소","고급 문화",32},{"왕실 연금 정원","왕실 특화",38}},
 {{"왕실 곡물·낙농장","식량",42},{"왕립 장비 연구 대장간","장비",38},{"왕실 식당·공연 살롱","먹거리",44},{"왕립 도서관·태양 성당","고급 문화",40},{"태양 왕실 연회 정원","왕실 특화",48}}
};
inline int Output(int castle,int room,int level){
 if(castle<0||castle>=10||room<0||room>=Counts[castle])return 0;
 level=level<0?0:level>5?5:level;
 return Rooms[castle][room].basePerHour*(4+level)/4;
}
static const unsigned int FoodMask[10]={1,1,1,1,1,1,1,1,1,1};
inline bool Food(int castle,int room){return castle>=0&&castle<10&&room>=0&&room<Counts[castle]&&(FoodMask[castle]&(1u<<room))!=0;}
inline bool Armory(int castle,int room){return castle>=0&&castle<10&&room==1&&room<Counts[castle];}
inline int AttackUpgrade(int castle,int room,int level){return Armory(castle,room)?Output(castle,room,level)-Output(castle,room,0):0;}
inline const char* Effect(int castle,int room){return Food(castle,room)?"에너지 회복 속도":"골드 생산량";}
template<class Progress> inline int Bonus(const Progress& p,int castle,bool food){
 if(castle<0||castle>=10||!(p.owned&(1u<<castle)))return 0;
 int sum=0;for(int i=0;i<Counts[castle];++i)if(Food(castle,i)==food)sum+=Output(castle,i,p.rooms[castle][i]);
 return sum;
}
}
