// Included after the existing catalog/card helpers in Func_Menu.cpp.
#include "ShopCatalogModel.h"
#include <memory>
#include <chrono>
namespace ShopSpec {
int tab=ShopCatalog::Gear,hero=0,detail=-1,page=0;
bool resultOpen=false,purchasing=false;
int resultUntil=0;
int currencyCardsDrawn=0;
std::chrono::steady_clock::time_point lastPurchaseTime;
std::string message;
struct Candidate {int type,detail;};
std::vector<ITEM> granted;
const char* HeroName(int h) {static const char* names[]={"로빈","디아나","맥스"};return names[Max(0,Min(2,h))];}
const char* KindName(int k) {static const char* names[]={"무기 보급","방어구 보급","동료 모집","특수 아이템 보급"};return names[Max(0,Min(3,k))];}
void Label(const char* text,int x,int y,int width,float size=.75f,int color=COLOR_WHITE) {
 SetFontColor(color);CenterTextStrSolid(text,x,y,Min(size,width/Max(1.0f,StringWidth(text,1))));
}
void Button(const char* text,int x,int y,int w,int h,int command,bool enabled=true,bool selected=false) {
 DrawPixelPanel(x,y,w,h,selected?0x17653E:0x102638,selected?0xEDBB58:0x43859B);
 Label(text,x+w/2,y-(h-(int)(FONT_HEIGHT*.75f))/2,w-12,.75f,enabled?COLOR_WHITE:0x8AA0AC);
 if(command&&enabled)SetRectPoint(x,y,w,h,command);
}
std::vector<Candidate> Pool(int kind,int who) {
 std::vector<Candidate> out;
 const auto add=[&](int type,int count) {for(int d=0;d<count;++d)
  if(!IsBoxLockedItem(type,d,GRADE_NORMAL))out.push_back({type,d});};
 if(kind==0) add(ITEM_SWORD+who,who==0?TOTAL_SWORD:who==1?TOTAL_GUN:TOTAL_BOOMERANG);
 else if(kind==1) {
  const int base[]={ITEM_HELM,ITEM_ARMOR,ITEM_GUNTLET,ITEM_KILT,ITEM_GREAVES};
  const int counts[]={TOTAL_HELM,TOTAL_ARMOR,TOTAL_GUNTLET,TOTAL_KILT,TOTAL_GREAVES};
  for(int i=0;i<5;++i)add(base[i]+who,counts[i]);
 } else if(kind==2) add(ITEM_CREW,gTotalCrew);
 else {add(ITEM_NECK,TOTAL_NECK);add(ITEM_RING,TOTAL_RING);add(ITEM_ESSENCE,TOTAL_ESSENCE);}
 return out;
}
const char* CandidateName(const Candidate& c) {
 if(c.type==ITEM_CREW) return textId[TEXT_MONSTERNAME_START+crewData[c.detail*CREWDATASIZE+CREWDATA_TYPE]];
 return textId[TEXT_ITEMNAME_START+GetItemName(c.type,c.detail,GRADE_NORMAL)];
}
//재화 묶음인가. 재화 탭이 따로 받으므로 패키지 탭에서는 뺀다 - 안 빼면
//같은 상품이 두 탭에 나온다(옛 추천/보급품이 그랬다).
bool IsCurrencyProduct(int product) {
 return (product>=IAP_HEART_01&&product<=IAP_HEART_06)
     || (product>=IAP_CASH_01 &&product<=IAP_CASH_06);
}
void SupplyCard(int kind,int x,int y,int w,int h) {
 const auto product=ShopCatalog::Supply(kind,hero);
 DrawPixelPanel(x,y,w,h,0x142E43);
 char name[96];sprintf(name,product.hero<0?"공용 %s":"%s %s",product.hero<0?KindName(kind):HeroName(hero),KindName(kind));
 Label(name,x+w/2,y-10,w-16,.82f);
 const auto pool=Pool(kind,hero);
 if(!pool.empty())DrawIcon(GetItemIcon(pool[0].type,pool[0].detail,GRADE_NORMAL),x+w/2-24,y-45,
  48.0f/ITEMICONSIZE,false,false,false,true);
 Label("영구 보관함 지급",x+w/2,y-102,w-12,.6f,0x8FE0BA);
 Button("구성 보기 · 준비 중",x+8,y-h+42,w-16,34,TOUCH_FUNC_SHOP_SUPPLY_DETAIL+kind);
}
void Overlay(int top) {
 if(detail<0&&!resultOpen)return;
 ResetRectPoint();SetAlpha(24);MemRect(0,top,DX,top,0);SetAlpha(ALPHA_MAX);
 const int x=16,w=DX-32,y=top-18,h=Min(top-36,560);
 DrawPixelPanel(x,y,w,h);
 Button("닫기",x+w-70,y-8,60,34,resultOpen?TOUCH_FUNC_SHOP_RESULT_CLOSE:TOUCH_FUNC_SHOP_CATALOG_CLOSE);
 if(resultOpen) {
  Label(message.c_str(),DX/2,y-54,w-32,.8f,0x8FE0BA);
  Label("지급 완료 · 영구 보관함에서 확인하세요",DX/2,y-84,w-32,.7f);
  for(int i=0;i<(int)granted.size()&&i<12;++i) {
   const ITEM& it=granted[i];const int cx=x+18+(i%4)*(w-36)/4,cy=y-128-(i/4)*104;
   DrawIcon(GetItemIcon(it.type,it.detail,it.grade),cx+16,cy,1,false,false,false,true);
   char amount[32];sprintf(amount,"x%lld",(long long)it.count);Label(amount,cx+40,cy-48,80,.65f);
  }
  return;
 }
 const auto pool=Pool(detail,hero);const int rows=Max(1,Min(3,(h-190)/92)),per=rows*4;
 const int pages=Max(1,((int)pool.size()+per-1)/per);page=Min(page,pages-1);
 Label(KindName(detail),DX/2,y-44,w-130,.95f);
 Label("영구 지급 · 실제 데이터 후보 목록",DX/2,y-76,w-24,.7f,0x8FE0BA);
 Label("가격·등급 확률 미정 / 구매 준비 중",DX/2,y-102,w-24,.7f,0xE6C56B);
 Label("장비는 개별 보관 · 동료 중복은 기존 수량 합산",DX/2,y-126,w-24,.6f);
 for(int i=0;i<per&&page*per+i<(int)pool.size();++i) {
  const auto& c=pool[page*per+i];const int cell=(w-32)/4,cx=x+16+(i%4)*cell,cy=y-158-(i/4)*92;
  DrawPixelPanel(cx,cy,cell-4,86);
  DrawIcon(GetItemIcon(c.type,c.detail,GRADE_NORMAL),cx+cell/2-16,cy-8,1,false,false,false,true);
  Label(CandidateName(c),cx+cell/2,cy-52,cell-12,.5f);
 }
 Button("<",x+16,y-h+42,44,32,TOUCH_FUNC_SHOP_POOL_PREV,page>0);
 char label[48];sprintf(label,"%d / %d · %d종",page+1,pages,(int)pool.size());Label(label,DX/2,y-h+34,w-140,.7f);
 Button(">",x+w-60,y-h+42,44,32,TOUCH_FUNC_SHOP_POOL_NEXT,page+1<pages);
}
void Draw(float x,float y,float w,float h,float zoom) {
 currencyCardsDrawn=0;
 const int top=(int)y,head=58,tabH=46,pad=18;
 //장비 탭만 히어로 줄을 따로 고른다. 그만큼 본문이 내려온다.
 const int bodyTop=top-head-tabH-12,bottom=12;
 const char* tabs[]={"장비","패키지","재화"};
 for(int i=0;i<ShopCatalog::TabCount;++i)Button(tabs[i],(int)x+pad+i*((int)w-2*pad)/ShopCatalog::TabCount,top-head,
  ((int)w-2*pad)/ShopCatalog::TabCount-4,tabH,TOUCH_FUNC_SHOP_MAIN_TAB+i,true,tab==i);

 // Live treasure products are shared; no hero picker or unavailable cards precede them.
 SetSectionClip((int)x,bodyTop,(int)w,Max(1,bodyTop-bottom),false);
 int cy=bodyTop+scY[MENU_SHOP];const int inner=(int)w-2*pad,cw=(inner-8)/2;
 if(tab==ShopCatalog::Gear) {
  //---- 무료 수령 ----
  if(ShopCatalog::DailyConfigured()) {
   const long long now=MC_knlCurrentTimeStamp(),next=robin.freeRewardTimeStamp+SHOP_DAILY_RESET_SECONDS;
   char text[100];sprintf(text,"골드 %lld · 다음 보급까지 %lld초",SHOP_DAILY_GOLD,Max(0LL,next-now));
   DrawMenuPlaque("오늘의 보급",(int)x+inner/6,cy,inner*2/3,48,.94f);cy-=60;
   Label(text,(int)(x+w/2),cy-16,inner-20,.7f);
   Button(next>now?"수령 완료":"무료 수령",(int)x+pad+12,cy-38,inner-24,30,TOUCH_FUNC_SHOP_DAILY_CLAIM,next<=now);
   cy-=88;
  }

  DrawMenuRoomBackdrop((int)x,cy,(int)w,112,0,0);
  const int merchant=MENU_REFERENCE_SHOPKEEPER_IMG;if(!sprite[merchant])LoadImg(merchant);
  if(sprite[merchant])DrawImageScale(748,1135,235,36,(int)x+(int)w/5,cy-3,false,0,0,0,0,108.f/1135.f,108.f/1135.f,sprite[merchant],merchant);
  // Reuse the lower counter pixels over the merchant so she stands behind it.
  if(sprite[MENU_RENEWAL_ROOM_IMG]){
   const auto sz=sprite[MENU_RENEWAL_ROOM_IMG]->getContentSize();const int strip=(int)sz.height/3;
   const float cover=Max(w/sz.width,112.f/strip);const int sw=(int)(w/cover),sh=(int)(112/cover),cut=(int)(54/cover);
   const int sx=((int)sz.width-sw)/2,sy=strip*2+(strip-sh)/2;
   DrawImageScale(sw,sh-cut,sx,sy+cut,(int)x,cy-54,false,0,0,0,0,w/sw,58.f/(sh-cut),sprite[MENU_RENEWAL_ROOM_IMG],MENU_RENEWAL_ROOM_IMG);
   SetAlpha(4);MemRect((int)x,cy-54,(int)w,58,0x092B30);SetAlpha(32);
  }
  cy-=88;

  //---- 종합 상자 ----
  DrawMenuPlaque("보물상자",(int)x+inner/5,cy,inner*3/5,54,1.05f);cy-=68;
  const int cardH=Max(190,Min(224,(int)(cw*.73f))),pitch=cardH+10;
  for(int k=0;k<6;++k)ShopBoxCard(k,x+pad+(k%2)*(cw+8),cy-(k/2)*pitch,cw,cardH,1);
  cy-=pitch*3;
 } else if(tab==ShopCatalog::Packages) {
  int shown=0;
  for(int i=0;i<TOTALIAPPRODUCT;++i)if(i!=IAP_INVEN_20&&IapCanPurchase(i)&&!IsCurrencyProduct(i)) {
   ShopCard(i,x+pad+(shown%2)*(cw+8),cy-(shown/2)*216,cw,206,1);++shown;
  }
  if(!shown) {
   DrawPixelPanel((int)x+pad,cy,inner,132);
   Label("현재 구매 가능한 패키지가 없습니다",(int)(x+w/2),cy-24,inner-24,.85f);
   Label("스토어 연결 후 현지 가격으로 안내합니다",(int)(x+w/2),cy-64,inner-24,.7f);
   Label("광고 제거·미연결 패스는 판매하지 않습니다",(int)(x+w/2),cy-96,inner-24,.6f,0x8AA0AC);cy-=148;
  } else cy-=((shown+1)/2)*216;
 } else {
  //---- 재화 ----
  //
  //골드는 안 판다. 판에서 벌어 상자와 성에 쓰는 순환 재화이지 사고파는
  //물건이 아니다. 팔기 시작하면 성장 곡선을 돈으로 건너뛴다.
  int shown=0;
  DrawMenuPlaque("하트",(int)x+inner/6,cy,inner*2/3,48,.94f);cy-=62;
  const int columns=3,cardW=(inner-16)/columns,cardH=202,pitch=cardH+10;
  for(int i=IAP_HEART_01;i<=IAP_HEART_06;++i) {
   ShopCard(i,x+pad+(shown%columns)*(cardW+8),cy-(shown/columns)*pitch,cardW,cardH,1);++shown;++currencyCardsDrawn;
  }
  cy-=((shown+columns-1)/columns)*pitch+14;shown=0;
  DrawMenuPlaque("캐시",(int)x+inner/6,cy,inner*2/3,48,.94f);cy-=62;
  for(int i=IAP_CASH_01;i<=IAP_CASH_06;++i) {
   ShopCard(i,x+pad+(shown%columns)*(cardW+8),cy-(shown/columns)*pitch,cardW,cardH,1);++shown;++currencyCardsDrawn;
  }
  cy-=((shown+columns-1)/columns)*pitch;
 }
 if(IapPendingCount()>0) {Label("미지급 결제를 복구하고 있습니다",(int)(x+w/2),cy,inner,.7f,0xE6C56B);cy-=36;}
 UnSectionClip(false);
 scT[MENU_SHOP]=Max(0,bodyTop+scY[MENU_SHOP]-cy-(bodyTop-bottom));
 scY[MENU_SHOP]=Max(0,Min(scY[MENU_SHOP],scT[MENU_SHOP]));
 if(scT[MENU_SHOP]>0){
  const int view=bodyTop-bottom,content=view+scT[MENU_SHOP],thumb=Max(32,view*view/content);
  MemRect((int)(x+w-8),bodyTop,3,view,0x183D40);
  MemRect((int)(x+w-8),bodyTop-scY[MENU_SHOP]*(view-thumb)/scT[MENU_SHOP],3,thumb,0xEBC587);
 }
 if(!message.empty()&&!resultOpen&&frame<resultUntil) {
  DrawPixelPanel(16,bodyTop-8,DX-32,50,0x422C35,0xC49D4D);Label(message.c_str(),DX/2,bodyTop-24,DX-56,.7f);
 }
 Overlay(top);
}
}

bool ShopCurrencyReviewChecks(){
 if(ShopSpec::tab!=ShopCatalog::Currency||ShopSpec::currencyCardsDrawn!=12)return false;
 for(int i=0;i<6;++i)if(!sprite[HEART_0_IMG+i])return false;
 if(!sprite[SHOP_CASH_PILES_IMG])return false;
 for(int i=0;i<touchIndex;++i){const int p=touchRect[i][4]-TOUCH_FUNC_SHOP_IAP;
  if(p>=0&&p<TOTALIAPPRODUCT&&!IapCanPurchase(p))return false;}
 return true;
}
bool ShopCatalogTouch(int command) {
 using namespace ShopSpec;
 if(command>=TOUCH_FUNC_SHOP_MAIN_TAB&&command<TOUCH_FUNC_SHOP_MAIN_TAB+3) {
  tab=command-TOUCH_FUNC_SHOP_MAIN_TAB;detail=-1;resultOpen=false;granted.clear();message.clear();
  if(tab==ShopCatalog::Gear)hero=Max(0,Min(TOTALCHAR-1,(int)curHero));
  scY[MENU_SHOP]=scT[MENU_SHOP]=0;return true;
 }
 if(command>=TOUCH_FUNC_SHOP_HERO&&command<TOUCH_FUNC_SHOP_HERO+TOTALCHAR) {
  hero=command-TOUCH_FUNC_SHOP_HERO;detail=-1;scY[MENU_SHOP]=scT[MENU_SHOP]=0;return true;
 }
 if(command>=TOUCH_FUNC_SHOP_SUPPLY_DETAIL&&command<TOUCH_FUNC_SHOP_SUPPLY_DETAIL+4) {
  detail=command-TOUCH_FUNC_SHOP_SUPPLY_DETAIL;page=0;return true;
 }
 if(command==TOUCH_FUNC_SHOP_CATALOG_CLOSE){detail=-1;return true;}
 if(command==TOUCH_FUNC_SHOP_POOL_PREV){page=Max(0,page-1);return true;}
 if(command==TOUCH_FUNC_SHOP_POOL_NEXT){++page;return true;}
 if(command==TOUCH_FUNC_SHOP_RESULT_CLOSE){resultOpen=false;granted.clear();message.clear();return true;}
 if(command==TOUCH_FUNC_SHOP_DAILY_CLAIM) {
  long long stamp=robin.freeRewardTimeStamp,gold=robin.gold;
  if(!IsStageRealtime()&&!StageRunPersistentEquipment(0)&&!purchasing&&ShopCatalog::ClaimDaily(MC_knlCurrentTimeStamp(),SHOP_DAILY_RESET_SECONDS,
     SHOP_DAILY_GOLD,ShopCatalog::DailyConfigured(),stamp,gold,GOLD_MAX)) {
   robin.gold=gold;robin.freeRewardTimeStamp=(long)stamp;SaveGame();
   ITEM reward={};reward.type=ITEM_GOLD;reward.count=SHOP_DAILY_GOLD;granted={reward};resultOpen=true;message="무료 보급 수령 완료";
  } else {message="아직 수령할 수 없거나 골드 보유 한도에 도달했습니다";resultUntil=frame+FPS*4;}
  return true;
 }
 return false;
}

bool ShopPurchaseExistingBox(int boxDetail) {
 using namespace ShopSpec;
 const long long cost=GetBoxPrice(boxDetail,GRADE_NORMAL);
 const bool gems=ShopTreasure::UsesGems(boxDetail-BOX_PAID0);
 const auto fail=[&](const char* why){message=why;resultUntil=frame+FPS*5;return false;};
 const auto now=std::chrono::steady_clock::now();
 if(purchasing||std::chrono::duration_cast<std::chrono::milliseconds>(now-lastPurchaseTime).count()<500||IapIsBusy()||IsStageRealtime()||StageRunPersistentEquipment(0))return fail("다른 구매 또는 탐험이 진행 중입니다");
 if(boxDetail<BOX_PAID0||boxDetail>BOX_PAID5||cost<0)return fail("판매하지 않는 상품입니다");
 if((gems?robin.coin:robin.gold)<cost)return fail(gems?"보석이 부족합니다":"골드가 부족합니다");
 int empty=0;for(int i=0;i<GetMaxInven();++i)if(robin.inven[i].type==EMPTY)++empty;
 if(empty<GACHA_MAX_REWARD_CARD)return fail("보관함에 빈칸 12개를 확보해주세요. 재화는 차감되지 않았습니다");
 purchasing=true;
 // SaveGame only queues a whole-profile update; no network callback/frame occurs
 // within this synchronous transaction. On any failure restore the complete profile.
 std::unique_ptr<ROBINDATA> before(new ROBINDATA(robin));
 if(!GenerateCastleBoxReward(boxDetail)) {robin=*before;purchasing=false;return fail("보물상자 구성을 불러오지 못했습니다");}
 if(gems)robin.coin-=cost;else robin.gold-=cost;
 const int count=boxCardItemCnt[0];granted.clear();
 bool ok=count>0&&count<=GACHA_MAX_REWARD_CARD;
 for(int i=0;i<count&&ok;++i) {
  ITEM item=boxCardItem[0][i];
  if(item.type==ITEM_GOLD)item.count=ShopTreasure::GoldReward(boxDetail-BOX_PAID0,(int)item.count);
  if(item.type==ITEM_HEART)item.count=ShopTreasure::HeartReward(boxDetail-BOX_PAID0,(int)item.count);
  ok=GetItem(item.type,item.lv,item.detail,item.grade,item.count,false)!=0;
  if(ok) {
   ITEM actual=item;
   // MakeItem currently normalizes grade to zero. Report the actual stored
   // instance rather than promising the intermediate gacha roll's grade.
   if((IsEquipItemType(item.type)||item.type==ITEM_CREW)&&itemObj>=0&&itemObj<GetMaxInven()) {
    actual=robin.inven[itemObj];actual.count=item.count;
   }
   granted.push_back(actual);
  }
 }
 if(!ok) {
  robin=*before;granted.clear();SaveGame();purchasing=false;
  for(int i=ROBIN;i<TOTALPLAYER;++i)RefreshStat(&ao[i]);
  return fail("지급하지 못해 구매를 취소했습니다. 재화는 보존됩니다");
 }
 SaveGame();lastPurchaseTime=now;purchasing=false;resultOpen=true;
 CCLOG("shop grant box=%d profile_count=%d rewards=%d",boxDetail,(int)robin.count,count);
 message="보물상자 구매 완료";PlayMusic(M_ITEM);return true;
}

bool ShopSpecReviewChecks() {
 using namespace ShopSpec;
 std::unique_ptr<ROBINDATA> saved(new ROBINDATA(robin));
 std::unique_ptr<OBJECT[]> savedActors(new OBJECT[PLAYERALL]);for(int i=0;i<PLAYERALL;++i)savedActors[i]=ao[i];
 const int savedCrewCount=crewCnt,savedVisual=gMobileCastleVisual;
 const auto savedTime=lastPurchaseTime;const auto savedMessage=message;
 bool ok=true;
 const auto trace=[&](const char* step) {
  if(const char* path=getenv("CS_CASTLE_REVIEW_PATH")) {
   FILE* f=fopen((std::string(path)+"checks.log").c_str(),"a");
   if(f){fprintf(f,"%s ok=%d gold=%lld granted=%d message=%s\n",step,ok,(long long)robin.gold,(int)granted.size(),message.c_str());fclose(f);}
  }
 };
 for(int h=0;h<3;++h) {
  const auto weapon=Pool(0,h),armor=Pool(1,h),companions=Pool(2,h);
  ok=ok&&!weapon.empty()&&!armor.empty()&&(int)companions.size()==gTotalCrew;
  for(const auto& c:weapon)ok=ok&&c.type==ITEM_SWORD+h;
  for(const auto& c:armor)ok=ok&&c.type%3==h&&c.type>=ITEM_HELM&&c.type<=ITEM_BOOTS;
  for(int k=0;k<4;++k)ok=ok&&!ShopCatalog::CanPurchase(ShopCatalog::Supply(k,h));
 }
 for(int i=0;i<TOTALIAPPRODUCT;++i)ok=ok&&!IapCanPurchase(i);
 trace("pools and IAP");
 ok=ok&&ShopCatalog::Forbidden("inven_20")&&ShopCatalog::Forbidden("SHOP_CASTLE_LEVEL_UP");
 long long last=100,gold=10;
 ok=ok&&!ShopCatalog::ClaimDaily(200,100,1,false,last,gold,1000)&&last==100&&gold==10;
 ok=ok&&ShopCatalog::ClaimDaily(200,100,1,true,last,gold,1000);
 ok=ok&&!ShopCatalog::ClaimDaily(200,100,1,true,last,gold,1000)&&last==200&&gold==11;
 trace("daily");
 robin.stage=0;robin.castle=0;robin.castleProgress.version=1;robin.castleProgress.owned=1;
 robin.demoSeen[DEMO_TUTORIAL_END]=true;
 const long long cost=GetBoxPrice(BOX_PAID0,GRADE_NORMAL);
 robin.gold=cost-1;const long long lowGold=robin.gold;
 ok=ok&&!ShopPurchaseExistingBox(BOX_PAID0)&&robin.gold==lowGold;
 trace("insufficient");
 robin.gold=cost*4;
 for(int i=0;i<TOTALINVENTORY;++i){memset(&robin.inven[i],0,sizeof(ITEM));robin.inven[i].type=ITEM_SWORD;robin.inven[i].count=1;}
 const long long fullGold=robin.gold;
 ok=ok&&!ShopPurchaseExistingBox(BOX_PAID0)&&robin.gold==fullGold;
 trace("full");
 for(int i=0;i<TOTALINVENTORY;++i){memset(&robin.inven[i],0,sizeof(ITEM));robin.inven[i].type=EMPTY;}
 lastPurchaseTime={};ok=ok&&ShopPurchaseExistingBox(BOX_PAID0)&&!granted.empty();
 trace("grant");
 long long rewardGold=0;
 for(const ITEM& item:granted) {
  if(item.type==ITEM_GOLD)rewardGold+=item.count;
  else if(IsEquipItemType(item.type)||item.type==ITEM_CREW)ok=ok&&GetItemCount(item.type,item.detail,item.grade)>0;
 }
 ok=ok&&robin.gold==fullGold-cost+rewardGold;
 ok=ok&&rewardGold<=ShopTreasure::GoldReward(0,1000000);
 trace("grant accounting");
 const long long paidGold=robin.gold;
 ok=ok&&!ShopPurchaseExistingBox(BOX_PAID0)&&robin.gold==paidGold;
 trace("duplicate");
 // Every premium tier must charge gems, reject insufficient gems even when
 // gold is plentiful, and leave both currencies intact on duplicate attempts.
 for(int tier=2;tier<6;++tier){
  for(int i=0;i<TOTALINVENTORY;++i){memset(&robin.inven[i],0,sizeof(ITEM));robin.inven[i].type=EMPTY;}
  const long long price=GetBoxPrice(BOX_PAID0+tier,GRADE_NORMAL);
  robin.gold=700;robin.coin=price-1;lastPurchaseTime={};
  ok=ok&&!ShopPurchaseExistingBox(BOX_PAID0+tier)&&robin.gold==700&&robin.coin==price-1;
  robin.coin=price;lastPurchaseTime={};
  ok=ok&&ShopPurchaseExistingBox(BOX_PAID0+tier)&&robin.coin==0&&!granted.empty();
  long long goldDrop=0;for(const auto& item:granted)if(item.type==ITEM_GOLD)goldDrop+=item.count;
  ok=ok&&robin.gold==700+goldDrop&&goldDrop<=ShopTreasure::GoldReward(tier,1000000);
  const long long afterGold=robin.gold,afterGems=robin.coin;
  ok=ok&&!ShopPurchaseExistingBox(BOX_PAID0+tier)&&robin.gold==afterGold&&robin.coin==afterGems;
 }
 trace("premium gems charges and duplicate guards");
 // Fixed self-test grants only: no live price, invented random distribution,
 // or sellable development SKU is created for the proposed supplies.
 // Isolate this case from random box loot: repeated companion/material drops
 // can otherwise reach their stack cap before these independent grant checks.
 for(int i=0;i<TOTALINVENTORY;++i){memset(&robin.inven[i],0,sizeof(ITEM));robin.inven[i].type=EMPTY;}
 for(int h=0;h<3;++h)for(int kind=0;kind<4;++kind) {
  const auto pool=Pool(kind,h);
  if(pool.empty()){ok=false;continue;}
  const auto item=pool.front();
  const bool received=GetItem(item.type,1,item.detail,GRADE_NORMAL,1,false)!=0;
  ok=ok&&received&&GetItemCount(item.type,item.detail,GRADE_NORMAL)>0;
  if(!received||GetItemCount(item.type,item.detail,GRADE_NORMAL)<=0)trace("fixed supply grant mismatch");
 }
 trace("fixed development supply grants");
 robin.castle=0;robin.castleProgress.owned=1;
 for(int i=0;i<5;++i)robin.castleProgress.parts[0][i]=5;
 robin.gold=CastleMenuModel::GoldPrice(1);robin.coin=777;
 const int previousCapacity=GetMaxInven();
 CastleMenuOpen();CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_NEXT);
 // All castles are already owned in the current design. Selection is free;
 // upgrades still consume gold exactly once through the confirmation handler.
 robin.castleIncomeTs=MC_knlCurrentTimeStamp();
 CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_SELECT);
 ok=ok&&robin.castle==1&&robin.gold==CastleMenuModel::GoldPrice(1)&&robin.coin==777&&GetMaxInven()>=previousCapacity;
 trace("free owned castle selection");
 const long long beforeUpgrade=robin.gold;
 const int level=robin.castleProgress.parts[1][0];
 const int upgradeCost=CastleMenuModel::UpgradeCost(1,level,false);
 CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_ROW);
 robin.castleIncomeTs=MC_knlCurrentTimeStamp();
 CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_UPGRADE);CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_CONFIRM);
 ok=ok&&level<5&&robin.castleProgress.parts[1][0]==level+1&&robin.gold==beforeUpgrade-upgradeCost;
 const long long afterUpgrade=robin.gold;
 trace("single gold upgrade");
 CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_CONFIRM);
 ok=ok&&robin.gold==afterUpgrade;
 CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_PAID_UPGRADE);
 ok=ok&&robin.coin==777&&robin.gold==afterUpgrade;
 trace("gold-only castle runtime and automatic capacity");
 robin=*saved;for(int i=0;i<PLAYERALL;++i)ao[i]=savedActors[i];crewCnt=savedCrewCount;
 gMobileCastleVisual=savedVisual;CastleMenuOpen();
 lastPurchaseTime=savedTime;message=savedMessage;
 purchasing=resultOpen=false;detail=-1;granted.clear();NetMarkDirty();
 return ok;
}
