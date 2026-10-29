// Equipment view uses the existing inventory IDs and detail/equip handlers.
namespace EquipmentV2 {
static int heroOffset=0;
static int Top(){return DY-(GNBHEIGHT-GNB_INIT_HEIGHT)-LOBBY_BAR_H-6;}
static int PreviewHeight(){return Min(420,Max(250,(Top()-16)/2));}
static int ListTop(){return Top()-PreviewHeight()-148;}
static int HeroY(){return Top()-44;}
static int HeroMax(int count){return Max(0,count*104-(DX-32));}
}

bool EquipmentMenuV2Drag(int startX,int startY,int x,int y,int previousX,int previousY)
{
 if(curMenu!=MENU_COLLECTIONS || curEquipTab!=EQUIPTAB_GEAR || menuDepth!=0 || gTouchRectLocked || IsTutorialPlaying()) return false;
 if(Abs(startX-x)<8 && Abs(startY-y)<8 && scDir==SCROLL_NOTHING) return true;
 if(startY<=EquipmentV2::HeroY() && startY>=EquipmentV2::HeroY()-76){
  EquipmentV2::heroOffset=Min(EquipmentV2::HeroMax(TOTALCHAR),Max(0,EquipmentV2::heroOffset+previousX-x));
  scDir=SCROLL_HORIZONTAL; scAccelY=0;
 } else if(startY<=EquipmentV2::ListTop() && startY>=16){
  scY[MENU_COLLECTIONS]=Min(Max(0,scT[MENU_COLLECTIONS]),Max(0,scY[MENU_COLLECTIONS]+previousY-y));
  scDir=SCROLL_VERTICAL; scAccelY=0;
 } else { scDir=SCROLL_HORIZONTAL; }
 isTouchKey=TOUCH_DRAG;
 return true;
}

static void EquipmentMenuV2Draw()
{
 using namespace EquipmentV2;
 const int top=Top(), preview=PreviewHeight(), listTop=ListTop();
 OBJECT* hero=&ao[PLAYER];
 DrawPixelPanel(0,top,DX,top,0x0C1C2C,0x43859B);
 SetFontColor(COLOR_WHITE);
 CenterTextStrSolid("장비",DX/2,top-10,0.9f);
 DrawUiButton(DX-48,top-6,36,32,"<",TOUCH_FUNC_POPUP_CLOSE);
 SetSectionClip(16,HeroY(),DX-32,76,false);
 heroOffset=Min(HeroMax(TOTALCHAR),Max(0,heroOffset));
 for(int h=0;h<TOTALCHAR;++h){
  int hx=16+h*104-heroOffset;
  DrawPixelPanel(hx,HeroY(),96,72,h==curHero?0x205363:0x142E43,h==curHero?0xEDBB58:0x43859B);
  OBJECT portrait=ao[PLAYER];portrait.type=portrait.cmf=h;
  for(int e=0;e<TOTALEQUIP;++e){portrait.equip[e]=robin.charData[h].equip[e];portrait.equipImg[e]=portrait.equip[e].type==EMPTY?0:portrait.equip[e].detail+1;}
  DrawPlayer(&portrait,h==curHero?frame/4%4:0,hx+48,HeroY()-62,RIGHT,0.85f,false,false,true);
  if(menuDepth==0) SetRectPoint(Max(16,hx),HeroY(),Max(0,Min(DX-16,hx+96)-Max(16,hx)),72,TOUCH_FUNC_SELECT_HERO+h);
 }
 UnSectionClip(false);
 const int bodyTop=top-130, slot=52, center=DX/2;
 DrawPixelPanel(16,bodyTop,DX-32,preview-138,0x142E43,0x28566D);
 // DrawPlayer resolves the selected hero's actual equipped costume parts.
 DrawPlayer(hero,frame/8%4,center,top-preview+34,RIGHT,1.8f,false,false,true);
 for(int i=0;i<TOTALEQUIP;++i){
  int sx=i<4?40:DX-92, sy=bodyTop-12-(i%4)*((preview-156)/4);
  DrawPixelPanel(sx,sy,slot,slot,menuX==i?0x205363:0x102638,menuX==i?0xEDBB58:0x43859B);
  const ITEM& it=hero->equip[i];
  const bool valid=it.type>=0 && it.type<=ITEM_RING && itemEquipSlot[it.type]==i && EquipCheck(hero,const_cast<ITEM*>(&it));
  if(valid){
   float z=0.85f;
   DrawIcon(GetItemIcon(it.type,it.detail,it.grade),sx+slot/2-ITEMICONSIZE*z/2,sy-slot/2+ITEMICONSIZE*z/2,z,false,false,false,true);
  } else {
   SetFontColor(0x88AABB); CenterTextStrSolid("+",sx+slot/2,sy-22,0.9f);
  }
  if(menuDepth==0){
   int idx=valid?GetInvenIdx(it.type,it.detail,it.grade):-1;
   SetRectPoint(sx,sy,slot,slot,idx>=0?TOUCH_FUNC_ITEMDETAIL+idx:(i<EQUIP_NECK?TOUCH_FUNC_MENUX_1+i:TOUCH_FUNC_EQUIPMENT_V2_CATEGORY+i));
  }
  if(GetTutorialEquipSlotTouchFunc()==TOUCH_FUNC_MENUX_1+i){
   DrawHand(sx,sy,robin.playtime/MOTIONDIV,1.5f);
   SetSpotlight(sx+slot/2,sy-slot/2,slot*0.6f,slot,0.25f);
  }
 }
 char line[180];
 SetFontColor(0xF2CA64);
 sprintf(line,"전투력 %lld",GetCombatPower(hero));
 CenterTextStrSolid(line,center,top-preview-8,0.8f);
 SetFontColor(0xBCD6DF);
 sprintf(line,"공격 %d   방어 %d   체력 %d",hero->ps[PS_WEAPONDMG]+hero->ps[PS_DMG],hero->ps[PS_ARMOR],hero->ps[PS_HP]);
 CenterTextStrSolid(line,center,top-preview-36,0.65f);
 sprintf(line,"치명타 %d%%   치명타 피해 +%d%%",DEFAULTCRITICAL+hero->ps[PS_CRITICAL],hero->ps[PS_CRITDMG]);
 CenterTextStrSolid(line,center,top-preview-60,0.6f);
 for(int i=0;i<EQUIPTAB_CNT;++i){
  int w=(DX-32)/EQUIPTAB_CNT;
  MenuButton(16+i*w,top-preview-86,w-4,34,kEquipTabName[i],curEquipTab==i?BUTTON_COLOR_BLUE:BUTTON_COLOR_BROWN,true,curEquipTab==i?0:TOUCH_FUNC_EQUIPTAB+i,0.6f);
 }
 // Keep existing category, merge and sell actions without the old card decoration.
 for(int i=0;i<TOTALEQUIP;++i){
  int w=(DX-200)/TOTALEQUIP;
  MenuButton(16+i*w,listTop+24,w-3,24,"",menuX==i?BUTTON_COLOR_BLUE:BUTTON_COLOR_BROWN,true,TOUCH_FUNC_EQUIPMENT_V2_CATEGORY+i,0.5f);
  DrawIcon(GetItemIcon(i<EQUIP_NECK?i*TOTALCHAR+curHero:ITEM_NECK+i-EQUIP_NECK,0,0),16+i*w+w/2-12,listTop+24,0.5f,false,false,false,true);
 }
 MenuButton(DX-182,listTop+24,80,24,"합성",BUTTON_COLOR_BLUE,true,TOUCH_FUNC_EQUIPTAB_MERGE,0.5f);
 MenuButton(DX-96,listTop+24,80,24,"판매",BUTTON_COLOR_BROWN,true,TOUCH_FUNC_EQUIPTAB_SELL,0.5f);
 int items[TOTALINVENTORY], count=0;
 for(int i=0;i<TOTALINVENTORY;++i)
  if(robin.inven[i].type==(menuX<EQUIP_NECK?menuX*TOTALCHAR+curHero:ITEM_NECK+menuX-EQUIP_NECK)) items[count++]=i;
 for(int i=1;i<count;++i){
  int key=items[i],j=i-1;
  while(j>=0 && (robin.inven[items[j]].grade<robin.inven[key].grade ||
   (robin.inven[items[j]].grade==robin.inven[key].grade && robin.inven[items[j]].value<robin.inven[key].value))){items[j+1]=items[j];--j;}
  items[j+1]=key;
 }
 const int cols=8, pitch=(DX-32)/cols, cell=pitch-6, height=Max(1,listTop-16);
 scT[MENU_COLLECTIONS]=Max(0,((count+cols-1)/cols)*pitch-height);
 scY[MENU_COLLECTIONS]=Min(scT[MENU_COLLECTIONS],Max(0,scY[MENU_COLLECTIONS]));
 SetSectionClip(16,listTop,DX-32,height,false);
 for(int i=0;i<count;++i){
  int sx=16+(i%cols)*pitch,sy=listTop-(i/cols)*pitch+scY[MENU_COLLECTIONS];
  if(sy<16 || sy-cell>listTop) continue;
  DrawInvenSlot(items[i],sx,sy,cell,cell,0.8f);
  if(menuDepth==0) SetRectPoint(sx,Min(listTop,sy),cell,Min(sy, listTop)-Max(16,sy-cell),TOUCH_FUNC_ITEMDETAIL+items[i]);
  if(GetTutorialEquipCardTouchFunc()==TOUCH_FUNC_ITEMDETAIL+items[i]){
   DrawHand(sx,sy,robin.playtime/MOTIONDIV,1.5f);
   SetSpotlight(sx+cell/2,sy-cell/2,cell*0.6f,cell,0.25f);
  }
 }
 UnSectionClip(false);
 if(count==0){SetFontColor(0x88AABB);CenterTextStrSolid("보유 장비가 없습니다",center,listTop-32,0.65f);}
 if(menuDepth==1){
  ResetRectPoint();ScreenDarken(SCREENDARKEN);EquipDetailDraw(&robin.inven[menuItem]);gTouchRectLocked=true;
  if(GetTutorialEquipButtonTouchFunc()){
   DrawHand(sEquipBtnX+sEquipBtnW/2,sEquipBtnY,robin.playtime/MOTIONDIV,1.5f);
   SetSpotlight(sEquipBtnX+sEquipBtnW/2,sEquipBtnY-sEquipBtnH/2,sEquipBtnH,sEquipBtnH*1.6f,0.25f);
  }
 }
}

bool EquipmentMenuV2ReviewChecks()
{
 using namespace EquipmentV2;
 const int oldY=scY[MENU_COLLECTIONS],oldT=scT[MENU_COLLECTIONS],oldDir=scDir,oldTouch=isTouchKey;
 scT[MENU_COLLECTIONS]=300;scY[MENU_COLLECTIONS]=0;
 bool ok=HeroMax(20)>DX && HeroMax(1)==0 && ListTop()>120;
 ok=EquipmentMenuV2Drag(100,ListTop()-20,100,ListTop()-120,100,ListTop()-20) && scY[MENU_COLLECTIONS]==100 && ok;
 EquipmentMenuV2Drag(100,ListTop()-20,100,-2000,100,ListTop()-120);
 ok=ok && scY[MENU_COLLECTIONS]==300;
 scY[MENU_COLLECTIONS]=oldY;scT[MENU_COLLECTIONS]=oldT;scDir=oldDir;isTouchKey=oldTouch;
 return ok;
}

bool EquipmentMenuV2ReviewEquipping()
{
 // Exercise the real detail-button command, then restore the isolated review profile.
 ROBINDATA* saved=new ROBINDATA(robin);
 std::vector<OBJECT> objects(ao,ao+PLAYERALL);
 const int oldHero=curHero,oldDepth=menuDepth,oldKey=systemKey;
 bool ok=true;
 for(int h=0;h<TOTALCHAR;++h){
  SetPlayerHero(h);
  ITEM item={};item.type=ITEM_GUNTLET+h;item.detail=0;item.grade=0;item.lv=1;
  item.count=1;item.id=190000+h;item.value=100;
  robin.inven[TOTALINVENTORY-1]=item;
  const long long before=GetCombatPower(&ao[PLAYER]);
  systemKey=AVK_EQUIP_INVENTORY+TOTALINVENTORY-1;PlayKey(PLAYER);
  ok=ok && ao[PLAYER].equip[EQUIP_GLOVE].id==item.id && GetCombatPower(&ao[PLAYER])>before;
  for(int other=0;other<TOTALCHAR;++other)
   if(other!=h) ok=ok && robin.charData[other].equip[EQUIP_GLOVE].id==saved->charData[other].equip[EQUIP_GLOVE].id;
  robin=*saved;for(int i=0;i<PLAYERALL;++i) ao[i]=objects[i];
 }
 delete saved;curHero=oldHero;menuDepth=oldDepth;systemKey=oldKey;
 return ok;
}
