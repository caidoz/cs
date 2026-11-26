#include "Data/CastleRoomAtlas.h"
// Single scrolling body. Part indices retain the existing save/model ordering.
#include <chrono>
#include "Data/CastleRoomUpgrades.h"
#include "Data/MergeCastleRebuild.h"
#include "Func_MergeRoulette.h"
#include "MergeCastleTransition.h"
#include "Data/MountedCannonSprites.h"
#include "Data/SoftCastleSectors.h"
#include "Data/IndividualCastleV4.h"
#include "Data/CastleUpgradeCosmetics.h"
#include "Data/HybridSd3d.h"
#include "Data/HybridCastleFleet.h"
#include "Data/CastleUpgradeBlocks.h"
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
static int BodyBottom(){return drawHandle==MD_LOBBY?MergeRouletteBottomNavHeight()+10:16;}
static int PreviewHeight(){return MergeRouletteCastleUpgradeHeight(castleBrowse);}
static int ContentHeight(){return PreviewHeight()+12+60+5*(CastleUpgradeBlocks::CardHeight(DY)+CastleUpgradeBlocks::Gap)+16;}
static int ScrollMax(){return Max(0,ContentHeight()-(BodyTop()-BodyBottom()));}
static int panelDrawSlot=0;
// The rounded panel shader is expensive on large overlapping menu surfaces.
// Rasterize each static style once; scrolling changes only its clipped quad.
static void Panel(int x,int top,int w,int h,int fill,int edge){
 DrawMenuReferencePanel(x,top,w,h,0,fill,edge);
}

static void Button(const char* text,int x,int y,int w,int h,int command,bool enabled=true,bool selected=false){
 UiButtonStyle style;style.fill=selected?0x246873:0x17444A;
 DrawUiButton(x,y,w,h,text,command,selected,enabled,style);
}
static void FacilityPreview(int c,int room,int lv,int x,int top,int width,int height){
 const int img=MERGE_REBUILD_ROOMS_IMG+Min(9,Max(0,c/2));if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 const auto size=sprite[img]->getTexture()->getContentSizeInPixels();const auto f=MergeCastleTransition::RoomFrame(room,lv,(int)size.width,(int)size.height);
 const int cropW=Min(f.w,Max(1,(int)(f.h*width/(float)height)));const float z=Min(width/(float)cropW,height/(float)f.h);
 DrawMenuBackdropCrop(sprite[img]->getTexture(),f.x+(f.w-cropW)/2,f.y,cropW,f.h,x+(int)((width-cropW*z)/2),top,(int)(cropW*z),(int)(f.h*z));
}
static void FacilityIcon(int c,int room,int lv,int x,int top,int size){FacilityPreview(c,room,lv,x,top,size,size);}

}

namespace CastleFinal {
#include "MergeCastleMenuArt.inc"
}
bool CastleMenuFinalDrag(int startX,int startY,int x,int y,int previousY){
 if(curMenu!=MENU_CASTLE || !popUpCnt || popUp[popUpCnt-1].type!=POPUPTYPE_CASTLEMENU || castleModal || gTouchRectLocked) return false;
 if(Abs(startX-x)<8 && Abs(startY-y)<8 && scDir==SCROLL_NOTHING) return true;
 scDir=SCROLL_VERTICAL;isTouchKey=TOUCH_DRAG;scAccelY=0;
 if(startY<=CastleFinal::BodyTop() && startY>=CastleFinal::BodyBottom())
  scY[MENU_CASTLE]=Min(CastleFinal::ScrollMax(),Max(0,scY[MENU_CASTLE]+y-previousY));
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
#include "CastleFourFacilityMenu.inc"

bool CastleMenuBlockPending(int room){
 return castleModal==2&&castleUpgradeIsRoom==(room>=0)&&castleUpgradePart==(room<0?3:room);
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
 for(int c=0;c<10;++c)for(int part=3;part<4;++part){
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
 for(int i=3;i<4;++i){
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
 castleBrowse=robin.castle=castle;gMobileCastleVisual=castle;castleRow=3;castleModal=0;
 robin.castleProgress.version=2;robin.castleProgress.owned=1023u;
 for(int i=0;i<5;++i)robin.castleProgress.parts[castle][i]=variant<6?variant:0;
 if(variant>=6 && variant<11)robin.castleProgress.parts[castle][variant-6]=5;
 if(variant==11){const int mixed[5]={1,5,2,4,3};for(int i=0;i<5;++i)robin.castleProgress.parts[castle][i]=mixed[i];}
 scY[MENU_CASTLE]=0;
}

int CastleMenuGrowthBrowse(){return castleBrowse;}
bool CastleMenuGrowthPending(){return castleModal==3;}
