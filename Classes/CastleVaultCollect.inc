//---- 성 금고 수거 (로비) ----
//
//성은 들어와 있지 않은 동안에도 골드를 쌓는다(Func_Item 의 CastleIncome*:
//시간에 비례해 차고, 생산 시설이 올리는 상한에서 멈춘다). 전에는 성 메뉴
//안의 글자 단추로만 걷을 수 있어서 로비에서는 쌓인 것이 보이지 않았다.
//
//여기서는 로비에 금고 단추(아이콘) 하나를 두고, 누르면 걷은 것이 제자리로
//날아간다. 옛 뽑기의 "요약 카드가 하단 메뉴로 날아가는 연출"
//(Func_Gacha 의 GACHA_DEPTH_FLYTOBAR)과 같은 규칙이다:
//  · 골드  → 상단 자원 띠의 골드 동전 자리(LobbyResourceBarAnchor)
//  · 장비  → 하단 메뉴 '영웅'(장비·컬렉션)
//  · 동료  → 하단 메뉴 '동료'
//
//무엇을 주는가는 골드가 기준이다(BalanceConfig 의 VAULT_*): 상한 대비 찬
//비율이 VAULT_GEAR_PCT 를 넘고 장비를 가진 플레이어면 히어로 라인 장비 카드
//한 장, 가득 찼고 동료를 가진 플레이어면 보유 동료 조각 하나를 얹는다. 없는
//종류는 주지 않는다 - 날아갈 메뉴가 그 사람에게는 아직 빈 방이다.
//
//지급은 누르는 순간 끝난다(저장도 그때). 연출은 그림일 뿐이라 앱이 중간에
//꺼져도 잃는 것이 없다. 상단 숫자만 동전이 닿을 때 오르도록 날아가는 중인
//골드(gLobbyGoldInFlight)를 표시에서 뺀다.
namespace CastleVault {
enum { FlyFrames=40, Stagger=4, HoldFrames=12, FadeFrames=10 };
struct Flight {
 int type=0,detail=0,grade=0,lv=1; long long count=1;
 float sx=0,sy=0,tx=0,ty=0,z0=1,z1=1; int start=0; bool arrived=false;
};
static std::vector<Flight> flights;
static int age=-1,finger=-1,pulse=0;
static bool pressed=false;
//검증용 - 마지막 수거에서 무엇이 나갔나.
static long long lastGold=0; static int lastGear=0,lastCrew=0;

//단추 자리: 오른쪽 위, 환경설정 톱니의 터치 영역(GNB_GEAR_TOUCHH) 아래. 성 지붕은
//가운데에 있어 이 구석은 하늘이다. 왼쪽 위는 로비 디버그 단추가 쓴다.
//자원 띠(y >= DY-LOBBY_BAR_H) 안에는 두지 않는다 - 원본 상단 띠 검증이 그 줄에
//수거 단추가 없기를 본다.
inline Box box(){const float s=DX/640.f;const int w=(int)(116*s),h=(int)(92*s);return {DX-(int)(10*s)-w,DY-GNB_GEAR_TOUCHH-(int)(6*s),w,h};}
inline int barTop(){return DY-(int)(2*DX/640.f);}   //MergeRouletteLobbySceneDraw 가 자원 띠를 그리는 y
inline bool busy(){return age>=0;}
inline float ease(float t){t=std::max(0.f,std::min(1.f,t));return t<.5f?4*t*t*t:1-std::pow(-2*t+2,3.f)/2;}
inline int percent(){const long long cap=CastleIncomeCap();return cap>0?(int)std::min(100LL,CastleIncomeNow()*100/cap):0;}
inline bool ownsGear(){
 for(int i=0;i<GetMaxInven();++i)if(robin.inven[i].type!=EMPTY&&IsEquipItemType(robin.inven[i].type))return true;
 for(int e=0;e<TOTALEQUIP;++e)if(ao[PLAYER].equip[e].type!=EMPTY&&IsEquipItemType(ao[PLAYER].equip[e].type))return true;
 return false;
}
//보유 동료 중 하나(가방 칸 번호). 동료 카드는 lv 0 이 '미획득'이고(GetItem 이 얻는 순간
//lv 1 로 올린다) count 는 그 위에 쌓인 조각 수라 0 일 수 있다. 주인 히어로를 아직 못
//얻은 동료는 거른다.
inline int ownedCrew(){
 std::vector<int> owned;
 for(int i=0;i<GetMaxInven();++i){const ITEM& it=robin.inven[i];
  if(it.type==ITEM_CREW&&it.lv>=1&&MergeCrewAvailable(it.detail))owned.push_back(i);}
 return owned.empty()?-1:owned[Random((int)owned.size())];
}
struct Plan{long long gold=0;int percent=0;bool gear=false,crew=false;};
inline Plan plan(){
 Plan p;p.gold=CastleIncomeNow();p.percent=percent();
 p.gear=p.gold>0&&p.percent>=VAULT_GEAR_PCT&&ownsGear();
 p.crew=p.gold>0&&p.percent>=VAULT_CREW_PCT&&ownedCrew()>=0;
 return p;
}
inline void navCenter(int i,float* x,float* y){const Box nav=lobbyBottomNav();*x=nav.x+nav.w*(i+.5f)/5;*y=nav.y-nav.h*.5f;}
inline bool collect(){
 if(busy()||RewardPopup::open())return false;
 const Plan p=plan();
 if(p.gold<=0){message=u8"금고가 비어 있습니다";PlayMusic(M_ERROR);return false;}
 if(robin.gold>GOLD_MAX-p.gold){message=u8"골드 보유 한도를 확인해주세요.";PlayMusic(M_ERROR);return false;}
 const Box b=box();const float s=DX/640.f,cx=b.x+b.w*.5f,cy=b.y-b.h*.5f;
 const long long got=CastleIncomeTake();   //여기서 골드가 들어가고 금고 시계가 다시 선다
 flights.clear();age=0;lastGold=got;lastGear=lastCrew=0;
 int gx,gy;LobbyResourceBarAnchor(barTop(),0,&gx,&gy);
 const int coins=(int)std::max((long long)VAULT_COIN_MIN,std::min((long long)VAULT_COIN_MAX,got/50));
 for(int i=0;i<coins;++i){
  Flight f;f.type=ITEM_GOLD;f.count=got/coins+(i==coins-1?got%coins:0);
  const float a=i*2.399f,r=b.w*.2f*(i%3)*.5f;   //단추 안에서 조금씩 흩어져 출발
  f.sx=cx+std::cos(a)*r;f.sy=cy+std::sin(a)*r;f.tx=(float)gx;f.ty=(float)gy;
  f.z0=1.15f*s;f.z1=.7f*s;f.start=i*Stagger;flights.push_back(f);
 }
 gLobbyGoldInFlight=got;
 int tail=coins*Stagger+6;
 if(p.gear){
  const long long power=std::max(0LL,GetCombatPower(&ao[PLAYER]));
  const MergeExpedition::Row& row=MergeExpedition::rowFor(power);
  const int type=treeEquipment[Random(GearCount)][0].type;
  if(type!=EMPTY){
   const int lv=std::max(1,std::min(GetEquipMaxLevel(),row.gearLevel));
   const int detail=MakeItemDetail(type,lv),grade=MakeItemGrade(type,lv,detail);
   if(GetItem(type,lv,detail,grade,1,0)){   //가방이 가득 차면 장비만 조용히 거른다. 골드는 이미 들어갔다
    Flight f;f.type=type;f.detail=detail;f.grade=grade;f.lv=lv;f.count=1;
    f.sx=cx;f.sy=cy;navCenter(1,&f.tx,&f.ty);f.z0=.30f*s;f.z1=.11f*s;f.start=tail;tail+=8;
    flights.push_back(f);lastGear=1;
   }
  }
 }
 if(p.crew){
  const int idx=ownedCrew();
  if(idx>=0){
   const ITEM c=robin.inven[idx];
   if(GetItem(ITEM_CREW,std::max(1,(int)c.lv),c.detail,c.grade,1,0)){   //같은 동료의 조각 하나(count +1)
    Flight f;f.type=ITEM_CREW;f.detail=c.detail;f.grade=c.grade;f.lv=std::max(1,(int)c.lv);f.count=1;
    f.sx=cx;f.sy=cy;navCenter(3,&f.tx,&f.ty);f.z0=.30f*s;f.z1=.11f*s;f.start=tail;tail+=8;
    flights.push_back(f);lastCrew=1;
   }
  }
 }
 SaveGame();PlayMusic(M_COIN);message.clear();
 return true;
}
inline void drawButton(){
 if(LoadoutOpen())return;
 const Box b=box();const float s=DX/640.f;const Plan p=plan();
 const bool ready=p.gold>0&&!busy();
 const Box d=b;
 UiButtonStyle style;style.fill=0x7A4E18;style.frame=mergeButtonFrame;style.stacked=true;
 char amount[32];std::snprintf(amount,sizeof(amount),"%lld",p.gold);
 grayScale=ready?0:32;
 DrawUiButtonIcon(d.x,d.y,d.w,d.h,ICON_GOLDBAG,amount,0,false,ready,style);grayScale=0;
 const int gw=std::max(3,(int)(6*s)),gh=d.h-(int)(16*s),gx=d.x+(int)(7*s),gy=d.y-(int)(8*s);
 MemRect(gx,gy,gw,gh,0x1A1410);
 const int fill=gh*p.percent/100;
 if(fill>0)MemRect(gx,gy-(gh-fill),gw,fill,p.percent>=100?0xFFE27A:0x6FD28A);
 //가득 찼으면 테두리가 숨 쉰다 - "지금 걷어라".
 if(p.percent>=100&&!busy()){
  ++pulse;const float k=.5f+.5f*std::sin(pulse*.18f);
  SetAlpha((int)(12+18*k));MemRectFrameThick(d.x-2,d.y+2,d.w+4,d.h+4,0xFFE27A,std::max(1,(int)(2*s)));SetAlpha(32);
 }
}
//자원 띠와 하단 메뉴 위에 그린다 - 도착점이 그 위에 있다.
inline void drawFlights(){
 if(!busy())return;
 ++age;bool allDone=true,coinLanded=false;
 const float s=DX/640.f;
 for(auto& f:flights){
  const int e=age-f.start;
  if(e<0){allDone=false;continue;}
  const float u=ease(e/(float)FlyFrames);
  //위로 볼록한 2차 곡선. 동전은 높이, 카드는 낮게 뜬다.
  const float mx=(f.sx+f.tx)*.5f,my=std::max(f.sy,f.ty)+(f.type==ITEM_GOLD?70.f:50.f)*s;
  const float x=(1-u)*(1-u)*f.sx+2*(1-u)*u*mx+u*u*f.tx;
  const float y=(1-u)*(1-u)*f.sy+2*(1-u)*u*my+u*u*f.ty;
  const float z=f.z0+(f.z1-f.z0)*u;
  if(e>=FlyFrames&&!f.arrived){
   f.arrived=true;
   if(f.type==ITEM_GOLD){gLobbyGoldInFlight=std::max(0LL,gLobbyGoldInFlight-f.count);coinLanded=true;}
   else PlayMusic(M_ITEM);
  }
  const int after=e-FlyFrames;
  if(after>=HoldFrames+FadeFrames)continue;
  allDone=false;
  int alpha=32;if(after>HoldFrames)alpha=32*(HoldFrames+FadeFrames-after)/FadeFrames;
  SetAlpha(std::max(1,alpha));
  if(f.type==ITEM_GOLD){const float half=ITEMICONSIZE*z*.5f;DrawIcon(ICON_GOLD,(int)(x-half),(int)(y+half),z,0,false,false,1);}
  else{const float w=240*z,h=332*z;DrawItemCard(f.type,f.detail,f.grade,f.lv,(long)f.count,false,(int)(x-w*.5f),(int)(y+h*.5f),0,z,false,0,0,0,0);}
  SetAlpha(32);
 }
 if(coinLanded)PlayMusic(M_COIN);
 if(allDone){flights.clear();age=-1;gLobbyGoldInFlight=0;}
}
//로비 터치. 단추 위에서 떼면 걷는다. 디버그 외형 미리보기의 도구줄이 같은 구석을
//쓰므로 그때는 비킨다.
inline bool touch(int phase,int id,float x,float y){
 if(LoadoutOpen()||popUpCnt>0||(DebugControlsOpen()&&LobbyCastleDebugActive()))return false;
 const Box b=box();
 if(phase==0){if(finger>=0||!b.has(x,y))return false;finger=id;pressed=true;return true;}
 if(finger!=id)return false;
 if(phase==1){pressed=b.has(x,y);return true;}
 finger=-1;const bool hit=pressed&&phase==2&&b.has(x,y);pressed=false;
 if(hit){PlayMusic(M_BUTTON);collect();}
 return true;
}
}
