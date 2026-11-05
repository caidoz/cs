#include "Data/CastleRoomAtlas.h"
// Single scrolling body. Part indices retain the existing save/model ordering.
#include "Data/CastleRoomUpgrades.h"
#include "Data/MountedCannonSprites.h"
#include "Data/SoftCastleSectors.h"
#include "Data/IndividualCastleV4.h"
#include "Data/CastleUpgradeCosmetics.h"
#include "Data/HybridSd3d.h"
#include "Data/HybridCastleFleet.h"
namespace CastleFinal {
static const int Order[5]={0,3,1,2,4};
static void GoldPair(long long needed,long long owned,int left,int top,int width){
 SetFontColor(0xBCD6DF);DrawTextStrSystem("필요",left,top-4,.62f,LEFT,false);
 DrawGoldAmount(needed,left+46,top,width/2-58,LEFT);
 DrawTextStrSystem("보유",left+width/2,top-4,.62f,LEFT,false);
 DrawGoldAmount(owned,left+width/2+46,top,width/2-58,LEFT);
}
static int HeaderTop(){return DY-(GNBHEIGHT-GNB_INIT_HEIGHT)-LOBBY_BAR_H-6;}
static int BodyTop(){return HeaderTop()-54;}
static int ContentHeight(){return 1244+CastleFacilities::Counts[castleBrowse]*148;}
static int ScrollMax(){return Max(0,ContentHeight()-(BodyTop()-HOMEBAR_HEIGHT-16));}
static void Button(const char* text,int x,int y,int w,int h,int command,bool enabled=true){
 DrawPixelPanel(x,y,w,h,enabled?0x205363:0x182A38,enabled?0xEDBB58:0x3D5262);
 SetFontColor(enabled?0xFFE5A0:0x84949C);
 CenterTextStrSolid(text,x+w/2,y-h/2+8,Min(.7f,(w-12)/Max(1.0f,StringWidth(text,1))));
 if(enabled) SetRectPoint(x,y,w,h,command);
}
static void FacilityIcon(int c,int room,int lv,int x,int top,int size){
 const int img=c==9?CASTLE_FINAL_ROOM_FIRST_IMG+lv:CASTLE_ROOM_UPGRADE_FIRST_IMG+c;
 if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 const auto tex=sprite[img]->getTexture()->getContentSizeInPixels();
 const auto f=CastleRoomUpgrades::Frame(c,room,lv,(int)tex.width,(int)tex.height);
 const float z=Min(size/(float)f.w,size/(float)f.h);
 DrawImageScale(f.w,f.h,f.x,f.y,x+(size-f.w*z)/2,top-(size-f.h*z)/2,false,0,0,0,0,z,z,sprite[img],img);
}
static void PartIcon(int c,int part,int lv,int x,int top,int size){
 if(part==3){DrawInventoryCannonIcon(c,lv,x,top,size,size);return;}
 if(part==0||part==1){
  const int img=CASTLE_SOFT_FIRST_IMG+c;const auto& f=SoftCastle::Bodies[c][0];
  if(!sprite[img])LoadImg(img);if(!sprite[img])return;
  const int h=part==0?f.h*2/5:f.h;const float z=Min((size-8)/(float)f.w,(size-8)/(float)h);
  DrawImageScale(f.w,h,f.x,f.y,x+(size-f.w*z)/2,top-(size-h*z)/2,false,0,0,0,0,z,z,sprite[img],img);return;
 }
 if(part==4&&lv>0){
  const auto& f=CastleUpgradeCosmetics::Frames[c][3][Min(5,lv)];const int img=CASTLE_UPGRADE_COSMETICS_IMG+c;
  if(!sprite[img])LoadImg(img);if(sprite[img]){const float z=(size-8)/(float)Max(f.w,f.h);
   DrawImage(f.w,f.h,f.x,f.y,x+(size-f.w*z)/2,top-(size-f.h*z)/2,false,0,0,0,0,z,sprite[img],img);return;}
 }
 const auto& r=IndividualCastleV4::Rigs[c];
 int img=CASTLE_UNARMED_FIRST_IMG+c,sx=r.x,sy=r.y,sw=r.w,sh=r.h;
 if(part==0){sh=r.h/3;}
 if(part==1){sx+=r.w/5;sy+=r.h/3;sw=r.w*3/5;sh=r.h/3;}
 if(part==2){
  FacilityIcon(c,0,robin.castleProgress.rooms[c][0],x,top,size);return;
 }
 if(part==4){img=CASTLE_INDIVIDUAL_V4_FIRST_IMG+c*IndividualCastleV4::Stride+1;sx=sy=0;sw=sh=r.wheels[0].r*2;}
 if(!sprite[img]) LoadImg(img);
 if(!sprite[img]) return;
 float z=Min((size-8)/(float)sw,(size-8)/(float)sh);
 DrawImageScale(sw,sh,sx,sy,x+(size-sw*z)/2,top-(size-sh*z)/2,false,0,0,0,0,z,z,sprite[img],img);
}
}

bool CastleMenuFinalDrag(int startX,int startY,int x,int y,int previousY){
 if(curMenu!=MENU_CASTLE || !popUpCnt || popUp[popUpCnt-1].type!=POPUPTYPE_CASTLEMENU || castleModal || gTouchRectLocked) return false;
 if(Abs(startX-x)<8 && Abs(startY-y)<8 && scDir==SCROLL_NOTHING) return true;
 scDir=SCROLL_VERTICAL;isTouchKey=TOUCH_DRAG;scAccelY=0;
 if(startY<=CastleFinal::BodyTop() && startY>=HOMEBAR_HEIGHT+16)
  scY[MENU_CASTLE]=Min(CastleFinal::ScrollMax(),Max(0,scY[MENU_CASTLE]+previousY-y));
 return true;
}

namespace CastleFinal {
static void EffectText(char* out,size_t size,const CastleMenuModel::Progress& p,int c,int part){
 auto baseline=p;baseline.parts[c][part]=0;
 switch(part){
 case 0:snprintf(out,size,"아군 공격력 +%d%%",CastleMenuModel::Attack(p,c)-CastleMenuModel::Attack(baseline,c));break;
 case 1:snprintf(out,size,"아군 방어력 +%d%%",CastleMenuModel::Defense(p,c)-CastleMenuModel::Defense(baseline,c));break;
 case 2:snprintf(out,size,"아군 체력 +%d%%",CastleMenuModel::Health(p,c)-CastleMenuModel::Health(baseline,c));break;
 case 3:snprintf(out,size,"포 피해 %d%% / 쿨타임 %.1f초 / 공격 +%d%%",CastleArtillery::Of(c).damagePercent*CastleMenuModel::CannonDamageMultiplier(p,c)/100,CastleArtillery::Of(c).cooldown*CastleMenuModel::CannonCooldownMultiplier(p,c)/(100.0f*FPS),CastleMenuModel::Attack(p,c)-CastleMenuModel::Attack(baseline,c));break;
 case 4:snprintf(out,size,"아군 전체 능력치 +%d%%",CastleMenuModel::All(p,c)-CastleMenuModel::All(baseline,c));break;
 default:snprintf(out,size,"효과 정보 없음");break;
 }
}
static void Text(const char* s,int x,int y,int width,float z=.7f,int color=COLOR_WHITE){
 SetFontColor(color);LineTextStrSolid(s,x,y,width,-1,-1,z);
}
static bool SaveConflict(){return NetLastRequest()==NETREQ_SAVE && NetLastResult()==NETRESULT_ERR_CONFLICT;}
}
void CastleMenuNewDraw(){
 using namespace CastleFinal;
 CastleProgressEnsure();const auto& p=robin.castleProgress;const int c=castleBrowse;
 const bool owned=CastleMenuModel::Owned(p,c);
 const int top=HeaderTop(),body=BodyTop(),left=16,width=DX-32,bottom=HOMEBAR_HEIGHT+16;
 scT[MENU_CASTLE]=ScrollMax();scY[MENU_CASTLE]=Min(scT[MENU_CASTLE],Max(0,scY[MENU_CASTLE]));
 int y=body+scY[MENU_CASTLE];char s[256],effect[180];
 ResetRectPoint();SetAlpha(ALPHA_MAX);
 DrawPixelPanel(0,top,DX,top,0x0C1C2C,0x43859B);
 SetSectionClip(0,body,DX,body-bottom,false);
 // The actual castle is the only costume preview, and belongs to the scroll body.
 DrawPixelPanel(left,y,width,296,0x142E43,0x28566D);
 if(!CastlePartsDrawMenuPreview(c+1,left+30,y-16,width-60,264))
  CastleLabel("성 리소스를 불러오지 못했습니다",DX/2,y-130,width-32,.7f);
 y-=308;
 DrawPixelPanel(left,y,width,180,0x142E43,0x43859B);
 Button("<",left+10,y-10,44,44,TOUCH_FUNC_CASTLE_NEW_PREV,c>0);
 Button(">",DX-left-54,y-10,44,44,TOUCH_FUNC_CASTLE_NEW_NEXT,c<9);
 CastleLabel(CastleStageAt(c)->title,DX/2,y-14,width-136,.85f);
 sprintf(s,"성 Lv.%d / 10  ·  %d구역  ·  %s",c+1,CastleFacilities::Counts[c],owned?(robin.castle==c?"출정 중":"보유 중"):"미보유");
 CastleLabel(s,DX/2,y-47,width-24,.65f);
 sprintf(s,"전투 그리드 %d칸 · 배치 한도 %d칸 · 창고 %d개",GridTestCellCnt(c),CastleEquipmentCapacity(c),CastleInventoryCapacity(c));
 CastleLabel(s,DX/2,y-76,width-24,.62f);
 if(owned)Button(robin.castle==c?"현재 출정 성":"출정 성으로 선택",left+12,y-116,width-24,48,TOUCH_FUNC_CASTLE_NEW_SELECT,robin.castle!=c);
 else {Button("",left+12,y-116,width-24,48,TOUCH_FUNC_CASTLE_NEW_BUY_GOLD);
  Text("성 구매",left+28,y-132,90,.7f);DrawGoldAmount(CastleMenuModel::GoldPrice(c),DX/2+40,y-125,width-160);}
 y-=192;
 const int gap=8,card=(width-gap*4)/5;
 for(int row=0;row<5;++row){
  const int part=Order[row],lv=p.parts[c][part],x=left+row*(card+gap);
  const bool selected=part==castleRow,ready=owned&&lv<CastleMenuModel::MaxLevel&&robin.gold>=CastleMenuModel::UpgradeCost(c,lv,false);
  DrawPixelPanel(x,y,card,132,selected?0x205363:0x142E43,selected?0xEDBB58:0x43859B);
  PartIcon(c,part,lv,x+(card-64)/2,y-8,64);
  CastleLabel(castlePartNames[part],x+card/2,y-77,card-8,.68f);
  sprintf(s,lv>=CastleMenuModel::MaxLevel?"MAX":"Lv.%d",lv);CastleLabel(s,x+card/2,y-104,card-8,.6f);
  if(ready)MemRect(x+card-12,y-8,6,6,0x6CE3AC);
  SetRectPoint(x,y,card,132,TOUCH_FUNC_CASTLE_NEW_ROW+part);
 }
 y-=144;
 const int part=castleRow,lv=p.parts[c][part];const bool max=lv>=CastleMenuModel::MaxLevel;
 const int cost=max?0:CastleMenuModel::UpgradeCost(c,lv,false);
 DrawPixelPanel(left,y,width,330,0x142E43,0xEDBB58);
 sprintf(s,"%s  %s",castlePartNames[part],max?"MAX":"");Text(s,left+20,y-16,width-40,.95f);
 sprintf(s,max?"현재 Lv.%d / %d":"현재 Lv.%d / %d  >  다음 Lv.%d",lv,CastleMenuModel::MaxLevel,lv+1);
 Text(s,left+20,y-52,width-40,.72f);
 EffectText(effect,sizeof(effect),p,c,part);sprintf(s,"현재 효과  %s",effect);Text(s,left+20,y-92,width-40,.65f,0xBCD6DF);
 if(max) sprintf(s,"다음 효과  최대 레벨");else {auto next=p;++next.parts[c][part];EffectText(effect,sizeof(effect),next,c,part);sprintf(s,"다음 효과  %s",effect);}
 Text(s,left+20,y-132,width-40,.65f,0x82DAC4);
 if(max)sprintf(s,"최대 레벨입니다");else if(!owned)sprintf(s,"성을 획득한 뒤 강화할 수 있습니다");
 if(max||!owned)Text(s,left+20,y-180,width-40,.7f,0xFFE5A0);
 else GoldPair(cost,robin.gold,left+20,y-174,width-40);
 const bool conflict=SaveConflict();
 Button(max?"MAX":conflict?"저장 충돌 확인 중":"골드 업그레이드",left+20,y-222,width-40,52,TOUCH_FUNC_CASTLE_NEW_UPGRADE,owned&&!max&&robin.gold>=cost&&!conflict);
 if(NetLastRequest()==NETREQ_SAVE && NetLastResult()!=NETRESULT_OK && NetLastResult()!=NETRESULT_NONE)
  CastleLabel(conflict?"서버 저장 데이터를 다시 불러옵니다":"저장 실패 · 기존 캐시 및 재시도 정책으로 보관 중",DX/2,y-292,width-40,.57f);
 y-=346;
 sprintf(s,"%s · 시설 %d개",CastleFacilities::Themes[c],CastleFacilities::Counts[c]);
 Text(s,left+20,y,width-40,.78f,0xFFE5A0);y-=38;
 sprintf(s,"선택한 성 · 에너지 회복 속도 +%d%%",CastleFacilities::Bonus(p,c,true));
 Text(s,left+16,y,width-32,.62f,0x82DAC4);y-=28;
 sprintf(s,"선택한 성 · 골드 생산량 +%d%%",CastleFacilities::Bonus(p,c,false));
 Text(s,left+16,y,width-32,.62f,0x82DAC4);y-=28;
 Text("출정 성 / h",left+16,y-4,110,.65f,0x82DAC4);
 DrawGoldAmount(CastleIncomePerHour(),left+130,y,width-164,LEFT);y-=36;
 const long long income=CastleIncomeNow();
 Button("",left+16,y,width-32,40,TOUCH_FUNC_CASTLE_INCOME,income>0&&!SaveConflict());
 DrawGoldAmount(income,left+32,y-6,width/2-66,LEFT);
 Text("/",left+width/2-28,y-10,20,.65f);
 DrawGoldAmount(CastleIncomeCap(),left+width/2,y-6,width/2-110,LEFT);
 Text("수금",left+width-72,y-12,60,.65f);y-=62;
 for(int i=0;i<CastleFacilities::Counts[c];++i){
  const auto& f=CastleFacilities::Rooms[c][i];const int level=p.rooms[c][i];
  DrawPixelPanel(left,y,width,136,0x142E43,0x43859B);
  FacilityIcon(c,i,level,left+12,y-10,64);
  sprintf(s,"%s  %s",f.name,level>=5?"MAX":"");Text(s,left+88,y-10,width-104,.68f);
  sprintf(s,"Lv.%d / 5 · %s",level,f.product);Text(s,left+88,y-36,width-104,.60f,0xBCD6DF);
  if(CastleFacilities::Armory(c,i))sprintf(s,"골드 +%d%% · 공격력 +%d%% > +%d%%",CastleFacilities::Output(c,i,level),CastleFacilities::AttackUpgrade(c,i,level),CastleFacilities::AttackUpgrade(c,i,level+1));
  else sprintf(s,"%s +%d%%  >  +%d%%",CastleFacilities::Effect(c,i),CastleFacilities::Output(c,i,level),CastleFacilities::Output(c,i,level+1));
  Text(s,left+88,y-60,width-104,.58f,0x82DAC4);
  const int price=CastleMenuModel::UpgradeCost(c,level,true);
  Button(level>=5?"MAX":"",left+16,y-90,width-32,36,TOUCH_FUNC_CASTLE_FACILITY_UPGRADE+i,owned&&level<5&&robin.gold>=price&&!SaveConflict());
  if(level<5){Text("강화",left+32,y-100,64,.65f);DrawGoldAmount(price,DX/2+36,y-94,width-160);}
  y-=148;
 }
 if(scT[MENU_CASTLE]>0){
  const int view=body-bottom,thumb=Max(24,view*view/ContentHeight());
  MemRect(DX-8,body,4,view,0x142E43);
  MemRect(DX-8,body-scY[MENU_CASTLE]*(view-thumb)/scT[MENU_CASTLE],4,thumb,0x72B8C9);
 }
 UnSectionClip(false);
 DrawPixelPanel(0,top,DX,54,0x102638,0x43859B);
 CastleLabel("성",DX/2,top-15,width,.95f);Button("<",16,top-6,44,44,TOUCH_FUNC_POPUP_CLOSE);
 if(castleModal){
  ResetRectPoint();SetAlpha(24);MemRect(0,top,DX,top,COLOR_BLACK);SetAlpha(ALPHA_MAX);
  const int mt=DY/2+150;const bool upgrade=castleModal==2;
  DrawPixelPanel(24,mt,DX-48,270,0x102638,0xEDBB58);
  CastleLabel(upgrade?(castleUpgradeIsRoom?"생산 시설 강화 확인":"파츠 업그레이드 확인"):"성 구매 확인",DX/2,mt-20,DX-80,.9f);
  if(upgrade)sprintf(s,"%s Lv.%d > Lv.%d",(castleUpgradeIsRoom?CastleFacilities::Rooms[c][castleUpgradePart].name:castlePartNames[castleUpgradePart]),castleUpgradeLevel,castleUpgradeLevel+1);
  else snprintf(s,sizeof(s),"%s",CastleStageAt(c)->title);
  CastleLabel(s,DX/2,mt-64,DX-80,.8f);
  const int price=upgrade?castleUpgradePrice:CastleMenuModel::GoldPrice(c);
  GoldPair(price,robin.gold,40,mt-105,DX-80);
  if(upgrade&&castleUpgradeIsRoom){
   if(CastleFacilities::Armory(c,castleUpgradePart))sprintf(s,"공격력 +%d%% > +%d%% · 골드 생산 증가",CastleFacilities::AttackUpgrade(c,castleUpgradePart,castleUpgradeLevel),CastleFacilities::AttackUpgrade(c,castleUpgradePart,castleUpgradeLevel+1));
   else sprintf(s,"%s +%d%% > +%d%%",CastleFacilities::Effect(c,castleUpgradePart),
    CastleFacilities::Output(c,castleUpgradePart,castleUpgradeLevel),CastleFacilities::Output(c,castleUpgradePart,castleUpgradeLevel+1));
   CastleLabel(s,DX/2,mt-150,DX-80,.65f);
  }
  Button("취소",40,mt-196,DX/2-48,48,TOUCH_FUNC_CASTLE_NEW_CANCEL);
  Button(upgrade?"강화 확정":"구매 확정",DX/2+8,mt-196,DX/2-48,48,TOUCH_FUNC_CASTLE_NEW_CONFIRM,robin.gold>=price&&!SaveConflict());
 }
 CastleMenuToast(1.0f);
}

bool CastleMenuFinalReviewChecks(){
 const auto saved=robin.castleProgress;const long long gold=robin.gold,coin=robin.coin;
 bool ok=true;
 for(int c=0;c<10;++c)for(int room=0;room<CastleFacilities::Counts[c];++room){
  auto p=saved;p.owned=1023u;p.rooms[c][room]=0;
  for(int lv=0;lv<5;++lv){
   long long funds=CastleMenuModel::UpgradeCost(c,lv,true)-1;
   ok=ok&&!CastleMenuModel::Upgrade(p,c,room,true,funds)&&p.rooms[c][room]==lv;
   funds=CastleMenuModel::UpgradeCost(c,lv,true);
   ok=ok&&CastleMenuModel::Upgrade(p,c,room,true,funds)&&funds==0&&p.rooms[c][room]==lv+1;
   ok=ok&&CastleFacilities::Output(c,room,lv+1)>CastleFacilities::Output(c,room,lv);
  }
  long long funds=1000000;ok=ok&&!CastleMenuModel::Upgrade(p,c,room,true,funds)&&funds==1000000;
 }
 for(int c=0;c<10;++c)for(int part=0;part<5;++part){
  auto p=saved;p.owned=1023u;p.parts[c][part]=0;
  for(int lv=0;lv<5;++lv){
   long long funds=CastleMenuModel::UpgradeCost(c,lv,false)-1;
   ok=ok && !CastleMenuModel::Upgrade(p,c,part,false,funds) && p.parts[c][part]==lv;
   funds=CastleMenuModel::UpgradeCost(c,lv,false);
   ok=ok && CastleMenuModel::Upgrade(p,c,part,false,funds) && funds==0 && p.parts[c][part]==lv+1;
  }
  long long funds=1000000;
  ok=ok && !CastleMenuModel::Upgrade(p,c,part,false,funds) && funds==1000000;
 }
 const int savedRow=castleRow,savedCategory=castleCategory,savedScroll=scY[MENU_CASTLE];
 castleModal=0;
 for(int i=0;i<5;++i){
  robin.castleProgress.parts[castleBrowse][i]=0;robin.gold=0;
  CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_ROW+i);
  ok=ok && castleRow==i && robin.castleProgress.parts[castleBrowse][i]==0 && scY[MENU_CASTLE]==savedScroll;
  CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_UPGRADE);
  ok=ok && castleModal==0 && robin.gold==0 && robin.castleProgress.parts[castleBrowse][i]==0;
  robin.gold=1000000;
  CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_UPGRADE);
  ok=ok && castleModal==2 && robin.gold==1000000 && robin.castleProgress.parts[castleBrowse][i]==0;
  CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_CONFIRM);
  const long long charged=robin.gold;
  CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_CONFIRM);
  ok=ok && robin.gold==charged && charged==1000000-CastleMenuModel::UpgradeCost(castleBrowse,0,false)
   && CastleVisualPartLevel(castleBrowse,i)==1 && robin.coin==coin && scY[MENU_CASTLE]==savedScroll;
 }
 CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_UPGRADE);const long long cancelledGold=robin.gold;
 CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_CANCEL);
 ok=ok && robin.gold==cancelledGold && castleModal==0;
 CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_UPGRADE);
 ++robin.castleProgress.parts[castleBrowse][castleRow];
 CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_CONFIRM);
 ok=ok && robin.gold==cancelledGold && castleModal==0;
 for(int c=0;c<10;++c)for(int i=0;i<5;++i)ok=ok && robin.castleProgress.rooms[c][i]==saved.rooms[c][i];
 robin.castleProgress=saved;robin.gold=gold;robin.coin=coin;castleRow=savedRow;castleCategory=savedCategory;
 CastleSaveChanges();castleMessage="";
 return ok;
}

void CastleMenuModuleReviewSet(int castle,int variant){
 castleBrowse=robin.castle=castle;gMobileCastleVisual=castle;castleRow=0;castleModal=0;
 robin.castleProgress.version=1;robin.castleProgress.owned=1023u;
 for(int i=0;i<5;++i)robin.castleProgress.parts[castle][i]=variant<6?variant:0;
 if(variant>=6 && variant<11)robin.castleProgress.parts[castle][variant-6]=5;
 if(variant==11){const int mixed[5]={1,5,2,4,3};for(int i=0;i<5;++i)robin.castleProgress.parts[castle][i]=mixed[i];}
 scY[MENU_CASTLE]=0;
}
