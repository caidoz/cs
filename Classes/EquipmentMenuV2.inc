// Equipment view uses the existing inventory IDs and detail/equip handlers.
namespace EquipmentV2 {
static int heroOffset=0;
static int Bottom(){return drawHandle==MD_LOBBY?MergeRouletteBottomNavHeight()+10:16;}
static int Top(){return DY-(GNBHEIGHT-GNB_INIT_HEIGHT)-LOBBY_BAR_H-6;}
static int PreviewHeight(){return Min(420,Max(250,(Top()-16)/2));}
static int ListTop(){return Top()-PreviewHeight()-124;}
static int HeroY(){return Top()-58;}
static int DisplayCastle(){const int preview=LobbyCastleDebugCastle();return Max(0,Min(9,preview>=0?preview:(int)robin.castle));}
static int HeroMax(int count){return Max(0,count*184-(DX-32));}
//---- 깨운 히어로만 센다 ----
//
//띠는 원래 TOTALCHAR 를 도는 스크롤 리스트였다. 늘어나는 것은 막지
//않았는데, 못 깨운 히어로까지 빈 자리로 세어 띠가 허공까지 밀렸다.
static int HeroShownCnt(){return TOTALCHAR;}

//이름은 표에서 받는다. 여기 배열로 적어 두면 히어로가 늘 때마다
//같이 늘려야 하고, 안 늘리면 네 번째가 "맥스" 로 나온다(Min(2,h)).
static const char* HeroName(int h){
 static const char* names[]={u8"로빈",u8"다이애나",u8"맥스"};
 if(h>=0&&h<3)return names[h];
 return textId[TEXT_MONSTERNAME_START+Max(0,Min(TOTALCHAR-1,h))];
}

static void HeroStrip(){
 SetSectionClip(24,HeroY(),DX-48,76,false);
 heroOffset=Min(HeroMax(HeroShownCnt()),Max(0,heroOffset));
 int shown=0;
 for(int h=0;h<TOTALCHAR;++h){
  //안 깨운 히어로는 자리를 안 차지한다. 상점의 줄 고르기와 같은 규칙이다.
  const bool unlocked=IsGetHero(h);
  const int x=24+shown*184-heroOffset;
  ++shown;
  DrawPixelPanel(x,HeroY(),174,72,h==curHero?0x225E61:0x12383E,h==curHero?0xF2C17D:0x86ADAD);
  OBJECT portrait=ao[PLAYER];portrait.type=portrait.cmf=h;
  for(int e=0;e<TOTALEQUIP;++e){portrait.equip[e]=robin.charData[h].equip[e];portrait.equipImg[e]=portrait.equip[e].type==EMPTY?0:portrait.equip[e].detail+1;}
  DrawPlayer(&portrait,0,x+44,HeroY()-62,RIGHT,.85f,false,false,true);
  SetFontColor(0xFFF0C9);DrawTextStrSystem(HeroName(h),x+82,HeroY()-26,.78f,LEFT,false);
  if(!unlocked){SetFontColor(0xAAC1C2);DrawTextStrSystem(u8"\uBBF8\uD574\uAE08",x+82,HeroY()-48,.5f,LEFT,false);}
  if(menuDepth==0&&unlocked)SetRectPoint(x,HeroY(),174,72,TOUCH_FUNC_SELECT_HERO+h);
 }
 UnSectionClip(false);
}
}

int EquipmentMenuV2VisibleCastle(){return EquipmentV2::DisplayCastle();}

bool EquipmentMenuV2Drag(int startX,int startY,int x,int y,int previousX,int previousY)
{
 if(curMenu!=MENU_COLLECTIONS || menuDepth!=0 || gTouchRectLocked || IsTutorialPlaying()) return false;
 if(curEquipTab==EQUIPTAB_CODEX)return false; // Keep the codex's own filters and scrolling.
 if(Abs(startX-x)<8 && Abs(startY-y)<8 && scDir==SCROLL_NOTHING) return true;
 if(startY<=EquipmentV2::HeroY() && startY>=EquipmentV2::HeroY()-76){
  EquipmentV2::heroOffset=Min(EquipmentV2::HeroMax(EquipmentV2::HeroShownCnt()),Max(0,EquipmentV2::heroOffset+previousX-x));
  scDir=SCROLL_HORIZONTAL; scAccelY=0;
 } else if(startY<=(curEquipTab==EQUIPTAB_STAT?EquipmentV2::Top()-344:EquipmentV2::ListTop()) && startY>=EquipmentV2::Bottom()){
  const int target=curEquipTab==EQUIPTAB_CREW?MENU_CREW:MENU_COLLECTIONS;
  scY[target]=Min(Max(0,scT[target]),Max(0,scY[target]+previousY-y));
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
 //칸(equip)과 몸(equipImg)·능력치(ps)는 한 물건에서 나와야 한다. 어딘가에서 equip 만 바꾸고
 //RefreshStat 을 안 불렀으면 여기서 맞춘다 - 칸은 비었는데 투구를 쓰고 있거나, 검을 들고도
 //공격 0 으로 보이는 것이 그 흔적이다.
 {
  bool stale=false;
  for(int i=0;i<TOTALEQUIP&&!stale;++i){
   const ITEM& it=hero->equip[i];
   const bool worn=it.type!=EMPTY && it.type>=0 && it.type<=ITEM_RING && itemEquipSlot[it.type]==i && EquipCheck(hero,const_cast<ITEM*>(&it));
   const unsigned char expected=worn?(unsigned char)(it.detail+1):0;
   stale=hero->equipImg[i]!=expected;
  }
  if(!stale && hero->equip[EQUIP_WEAPON].type!=EMPTY && EquipCheck(hero,&hero->equip[EQUIP_WEAPON]) && hero->ps[PS_DMG]<=0) stale=true;
  if(stale) RefreshStat(hero);
 }
 DrawPixelPanel(0,top,DX,top,0x0C1C2C,0x43859B);
 SetFontColor(COLOR_WHITE);
 DrawMenuReferencePanel(0,top,DX,54,0,0x10383D,0x49777A);
 CenterTextStrSolid("장비",DX/2,top-12,1.15f);
 DrawMenuBackButton(12,top-4,TOUCH_FUNC_POPUP_CLOSE);
 HeroStrip();
 const int bodyTop=top-140, slot=72, center=DX/2;
 DrawHeroCastleBackdrop(12,bodyTop,DX-24,preview-114,DisplayCastle());
 SetAlpha(7);MemRect(12,bodyTop,DX-24,preview-114,0x092B30);SetAlpha(32);
 // The circular fitting platform is part of the room painting. Keep the feet
 // at its top surface when a short viewport crops the 2:1 illustration.
 const int roomH=preview-114;
 const float roomScale=Max((DX-24)/2.f,(float)roomH);
 const int heroFeet=bodyTop-roomH/2-(int)(.26f*roomScale);
 // DrawPlayer resolves the selected hero's actual equipped costume parts.
 DrawPlayer(hero,frame/8%4,center,heroFeet,RIGHT,1.9f,false,false,true);
 for(int i=0;i<EQUIP_NECK;++i){
  int sx=i<3?60:DX-60-slot, sy=bodyTop-12-(i%3)*((preview-156)/3);
  const ITEM& it=hero->equip[i];
  const bool valid=it.type>=0 && it.type<=ITEM_RING && itemEquipSlot[it.type]==i && EquipCheck(hero,const_cast<ITEM*>(&it));
  const int border=valid?InvenCardBorderColor(it):menuX==i?0xEDBB58:0x43859B;
  DrawMenuReferencePanel(sx,sy,slot,slot,0,menuX==i?0x205363:0x102638,border);
  if(valid){
   float z=1.0f;
   DrawIcon(GetItemIcon(it.type,it.detail,it.grade),sx+slot/2-ITEMICONSIZE*z/2,sy-slot/2+ITEMICONSIZE*z/2,z,false,false,false,true);
  } else {
   SetFontColor(0x88AABB); CenterTextStrSolid("+",sx+slot/2,sy-slot/2+9,0.9f);
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
 DrawMenuReferencePanel(24,top-preview+6,DX-48,116,1,0x123D43,0xF1C47E);
 char line[180];
 SetFontColor(0xF2CA64);
 sprintf(line,"전투력 %lld",GetCombatPower(hero));
 CenterTextStrSolid(line,center,top-preview-8,1.18f);
 SetFontColor(0xBCD6DF);
 //방어 = 합성 전투의 방어막 통(체력과 같은 크기). 옛 PS_ARMOR 는 힘×3+민첩이라 체력 60 에 880 이 찍혔다.
 sprintf(line,"공격 %lld   방어 %lld   체력 %lld",hero->ps[PS_DMG],MergeRouletteHeroShield(hero),hero->ps[PS_HP]);
 CenterTextStrSolid(line,center,top-preview-38,1.f);
 sprintf(line,"치명타 %lld%%   치명타 피해 +%lld%%",DEFAULTCRITICAL+hero->ps[PS_CRITICAL],hero->ps[PS_CRITDMG]);
 CenterTextStrSolid(line,center,top-preview-68,1.f);
 MenuButton(24,Bottom()+56,(DX-60)/2,56,"일괄 합성",BUTTON_COLOR_BLUE,true,TOUCH_FUNC_EQUIPTAB_MERGE,0.95f);
 MenuButton(DX/2+6,Bottom()+56,(DX-60)/2,56,"판매",BUTTON_COLOR_BROWN,true,TOUCH_FUNC_EQUIPTAB_SELL,0.95f);
 std::vector<int> items(GetMaxInven());int count=0;
 for(int i=0;i<GetMaxInven();++i)
  if(robin.inven[i].type>=ITEM_SWORD && robin.inven[i].type<ITEM_NECK) items[count++]=i;
 for(int i=1;i<count;++i){
  int key=items[i],j=i-1;
  while(j>=0 && (robin.inven[items[j]].grade<robin.inven[key].grade ||
   (robin.inven[items[j]].grade==robin.inven[key].grade && robin.inven[items[j]].value<robin.inven[key].value))){items[j+1]=items[j];--j;}
  items[j+1]=key;
 }
 const int cols=6, gap=8, cell=(DX-32-(cols-1)*gap)/cols, pitch=cell+gap,
  cardHeight=(int)(332.f*cell/240),rowPitch=cardHeight+12,listBottom=Bottom()+74,height=Max(1,listTop-listBottom);
 scT[MENU_COLLECTIONS]=Max(0,((count+cols-1)/cols)*rowPitch-height);
 scY[MENU_COLLECTIONS]=Min(scT[MENU_COLLECTIONS],Max(0,scY[MENU_COLLECTIONS]));
 SetSectionClip(16,listTop,DX-32,height,false);
 for(int i=0;i<count;++i){
  int sx=16+(i%cols)*pitch,sy=listTop-(i/cols)*rowPitch+scY[MENU_COLLECTIONS];
  if(sy<listBottom || sy-cardHeight>listTop) continue;
  DrawInvenSlot(items[i],sx,sy,cell,cardHeight,1.3f);
  if(menuDepth==0) SetRectPoint(sx,Min(listTop,sy),cell,Min(sy, listTop)-Max(listBottom,sy-cardHeight),TOUCH_FUNC_ITEMDETAIL+items[i]);
  if(GetTutorialEquipCardTouchFunc()==TOUCH_FUNC_ITEMDETAIL+items[i]){
   DrawHand(sx,sy,robin.playtime/MOTIONDIV,1.5f);
   SetSpotlight(sx+cell/2,sy-cell/2,cell*0.6f,cell,0.25f);
  }
 }
 UnSectionClip(false);
 DrawScroll(DX-10,listTop,height,MENU_COLLECTIONS);
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

bool EquipmentMenuV2ReviewCards()
{
 int row=0;
 for(int i=0;i<touchIndex;++i)if(touchRect[i][4]>=TOUCH_FUNC_ITEMDETAIL&&
  touchRect[i][4]<TOUCH_FUNC_ITEMDETAIL+INVENTORY_COMMAND_RANGE&&
  touchRect[i][1]==EquipmentV2::ListTop()&&touchRect[i][2]<DX/6)++row;
 return row==6&&sprite[CARDBG_IMG]!=nullptr;
}

bool EquipmentMenuV2ReviewEquipping()
{
 // Exercise the real detail-button command, then restore the isolated review profile.
 ROBINDATA* saved=new ROBINDATA(robin);
 const auto savedOverflow=InventoryOverflowSnapshot();
 std::vector<OBJECT> objects(ao,ao+PLAYERALL);
 const int oldHero=curHero,oldDepth=menuDepth,oldKey=systemKey;
 bool ok=true;
 for(int h=0;h<TOTALCHAR;++h){
  SetPlayerHero(h);
  ITEM item={};item.type=ITEM_GUNTLET+h;item.detail=0;item.grade=0;item.lv=1;
  item.count=1;item.id=190000+h;item.value=100;
  const int index=GetMaxInven()+5;robin.inven[index]=item;
  const long long before=GetCombatPower(&ao[PLAYER]);
  systemKey=AVK_EQUIP_INVENTORY+index;PlayKey(PLAYER);
  ok=ok && ao[PLAYER].equip[EQUIP_GLOVE].id==item.id && GetCombatPower(&ao[PLAYER])>before;
  for(int other=0;other<TOTALCHAR;++other)
   if(other!=h) ok=ok && robin.charData[other].equip[EQUIP_GLOVE].id==saved->charData[other].equip[EQUIP_GLOVE].id;
  robin=*saved;InventoryRestoreOverflow(savedOverflow);for(int i=0;i<PLAYERALL;++i) ao[i]=objects[i];
 }
 delete saved;curHero=oldHero;menuDepth=oldDepth;systemKey=oldKey;
 return ok;
}
