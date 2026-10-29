// Single scrolling body. Part indices retain the existing save/model ordering.
#include "Data/IndividualCastleV4.h"
namespace CastleFinal {
static const int Order[5]={0,3,1,2,4};
static int HeaderTop(){return DY-(GNBHEIGHT-GNB_INIT_HEIGHT)-LOBBY_BAR_H-6;}
static int BodyTop(){return HeaderTop()-54;}
static int ContentHeight(){return 1392;}
static int ScrollMax(){return Max(0,ContentHeight()-(BodyTop()-16));}
static void Button(const char* text,int x,int y,int w,int h,int command,bool enabled=true){
 DrawPixelPanel(x,y,w,h,enabled?0x205363:0x182A38,enabled?0xEDBB58:0x3D5262);
 SetFontColor(enabled?0xFFE5A0:0x84949C);
 CenterTextStrSolid(text,x+w/2,y-h/2+8,Min(.7f,(w-12)/Max(1.0f,StringWidth(text,1))));
 if(enabled) SetRectPoint(x,y,w,h,command);
}
static void PartIcon(int c,int part,int lv,int x,int top,int size){
 if(part==3){DrawInventoryCannonIcon(c,lv,x,top,size,size);return;}
 const auto& r=IndividualCastleV4::Rigs[c];
 int img=CASTLE_UNARMED_FIRST_IMG+c,sx=r.x,sy=r.y,sw=r.w,sh=r.h;
 if(part==0){sh=r.h/3;}
 if(part==1){sx+=r.w/5;sy+=r.h/3;sw=r.w*3/5;sh=r.h/3;}
 if(part==2){img=CASTLE_RECTANGULAR_ROOM_FIRST_IMG+c*6+lv;sx=sy=0;sw=512;sh=128;}
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
 if(startY<=CastleFinal::BodyTop() && startY>=16)
  scY[MENU_CASTLE]=Min(CastleFinal::ScrollMax(),Max(0,scY[MENU_CASTLE]+previousY-y));
 return true;
}

void CastleMenuNewDraw(){
 using namespace CastleFinal;
 CastleProgressEnsure();const auto& p=robin.castleProgress;const int c=castleBrowse;
 const bool owned=CastleMenuModel::Owned(p,c);
 const int top=HeaderTop(),body=BodyTop(),left=16,width=DX-32;
 scT[MENU_CASTLE]=ScrollMax();scY[MENU_CASTLE]=Min(scT[MENU_CASTLE],Max(0,scY[MENU_CASTLE]));
 int y=body+scY[MENU_CASTLE];char s[256];
 ResetRectPoint();SetAlpha(ALPHA_MAX);
 DrawPixelPanel(0,top,DX,top,0x0C1C2C,0x43859B);
 SetSectionClip(0,body,DX,body-16,false);
 DrawPixelPanel(left,y,width,100,0x142E43,0x43859B);
 Button("<",left+12,y-28,40,42,TOUCH_FUNC_CASTLE_NEW_PREV,c>0);
 Button(">",DX-left-52,y-28,40,42,TOUCH_FUNC_CASTLE_NEW_NEXT,c<9);
 CastleLabel(CastleStageAt(c)->title,DX/2,y-12,width-140,.9f);
 sprintf(s,"%d / 10   %s",c+1,owned?(robin.castle==c?"출정 중":"보유 중"):"미보유");
 CastleLabel(s,DX/2,y-50,width-140,.65f);
 y-=112;
 DrawPixelPanel(left,y,width,292,0x142E43,0x28566D);
 CastlePartsDrawMenuPreview(c+1,left+30,y-14,width-60,264);
 y-=304;
 DrawPixelPanel(left,y,width,124,0x142E43,0x43859B);
 sprintf(s,"성 전투력 %lld",CastleTotalPower(p,c));CastleLabel(s,DX/2,y-12,width-24,.9f);
 sprintf(s,"공격 +%d%%   방어 +%d%%   체력 +%d%%",CastleMenuModel::Attack(p,c)+CastleMenuModel::All(p,c),CastleMenuModel::Defense(p,c)+CastleMenuModel::All(p,c),CastleMenuModel::Health(p,c)+CastleMenuModel::All(p,c));
 CastleLabel(s,DX/2,y-46,width-24,.65f);
 sprintf(s,"배치 %d칸   적재 %d개",CastleEquipmentCapacity(c),CastleInventoryCapacity(c));CastleLabel(s,DX/2,y-78,width-24,.65f);
 y-=136;
 if(owned) Button(robin.castle==c?"현재 출정 성":"출정 성으로 선택",left,y,width,42,TOUCH_FUNC_CASTLE_NEW_SELECT,robin.castle!=c);
 else {sprintf(s,"골드 %d · 성 구매",CastleMenuModel::GoldPrice(c));Button(s,left,y,width,42,TOUCH_FUNC_CASTLE_NEW_BUY_GOLD);}
 y-=56;
 for(int row=0;row<5;++row){
  int part=Order[row],lv=p.parts[c][part];const int h=144;
  DrawPixelPanel(left,y,width,h,0x142E43,0x43859B);
  PartIcon(c,part,lv,left+12,y-18,84);
  sprintf(s,"%s  Lv.%d / %d",castlePartNames[part],lv,CastleMenuModel::MaxLevel);
  SetFontColor(COLOR_WHITE);LineTextStrSolid(s,left+108,y-12,width-124,-1,-1,.8f);
  SetFontColor(0xBCD6DF);LineTextStrSolid(castlePartEffects[part],left+108,y-42,width-124,-1,-1,.58f);
  auto next=p;if(lv<5)++next.parts[c][part];
  sprintf(s,"전투력 %lld > %lld",CastleTotalPower(p,c),CastleTotalPower(next,c));
  SetFontColor(0x82DAC4);LineTextStrSolid(s,left+108,y-68,width-124,-1,-1,.62f);
  for(int n=0;n<5;++n) MemRect(left+12+n*16,y-118,12,6,n<lv?0xF2CA64:0x28475A);
  if(lv>=5) sprintf(s,"최대 단계");else if(!owned) sprintf(s,"성 획득 필요");else sprintf(s,"%d G · 업그레이드",CastleMenuModel::UpgradeCost(c,lv,false));
  Button(s,DX-left-230,y-100,218,32,TOUCH_FUNC_CASTLE_NEW_ROW+part,owned&&lv<5&&robin.gold>=CastleMenuModel::UpgradeCost(c,lv,false));
  y-=156;
 }
 if(scT[MENU_CASTLE]>0){
  const int view=body-16,thumb=Max(24,view*view/ContentHeight());
  MemRect(DX-8,body,4,view,0x142E43);
  MemRect(DX-8,body-scY[MENU_CASTLE]*(view-thumb)/scT[MENU_CASTLE],4,thumb,0x72B8C9);
 }
 UnSectionClip(false);
 // Header is fixed and registered after clipped body controls.
 DrawPixelPanel(0,top,DX,54,0x102638,0x43859B);
 CastleLabel("성 관리",DX/2,top-15,width,.95f);
 Button("<",16,top-10,40,34,TOUCH_FUNC_POPUP_CLOSE);
 if(castleModal){
  ResetRectPoint();SetAlpha(24);MemRect(0,top,DX,top,COLOR_BLACK);SetAlpha(ALPHA_MAX);
  const int mt=DY/2+130;
  DrawPixelPanel(24,mt,DX-48,230,0x102638,0xEDBB58);
  CastleLabel("성 구매 확인",DX/2,mt-20,DX-80,.95f);
  CastleLabel(CastleStageAt(c)->title,DX/2,mt-64,DX-80,.8f);
  sprintf(s,"필요 골드 %d / 보유 %lld",CastleMenuModel::GoldPrice(c),robin.gold);CastleLabel(s,DX/2,mt-104,DX-80,.65f);
  Button("취소",40,mt-166,DX/2-48,40,TOUCH_FUNC_CASTLE_NEW_CANCEL);
  Button("구매 확정",DX/2+8,mt-166,DX/2-48,40,TOUCH_FUNC_CASTLE_NEW_CONFIRM,robin.gold>=CastleMenuModel::GoldPrice(c));
 }
 CastleMenuToast(1.0f);
}

bool CastleMenuFinalReviewChecks(){
 const auto saved=robin.castleProgress;const long long gold=robin.gold,coin=robin.coin;
 bool ok=true;
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
 const int savedRow=castleRow,savedCategory=castleCategory;
 for(int i=0;i<5;++i){
  robin.castleProgress.parts[castleBrowse][i]=0;robin.gold=0;
  CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_ROW+i);
  ok=ok && robin.gold==0 && robin.castleProgress.parts[castleBrowse][i]==0;
  robin.gold=1000000;
  CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_ROW+i);
  ok=ok && robin.gold==1000000-CastleMenuModel::UpgradeCost(castleBrowse,0,false)
   && CastleVisualPartLevel(castleBrowse,i)==1 && robin.coin==coin;
 }
 for(int c=0;c<10;++c)for(int i=0;i<5;++i)ok=ok && robin.castleProgress.rooms[c][i]==saved.rooms[c][i];
 robin.castleProgress=saved;robin.gold=gold;robin.coin=coin;castleRow=savedRow;castleCategory=savedCategory;
 CastleSaveChanges();castleMessage="";
 return ok;
}
