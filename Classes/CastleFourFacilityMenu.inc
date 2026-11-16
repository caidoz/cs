// Block upgrade screen, using existing six-stage room and cannon resources.
namespace CastleFinal {
static void UpgradeAction(const char* text,int x,int top,int width,int command,bool enabled){
 const int h=CastleUpgradeBlocks::TouchHeight;
 // Use the approved blue/gold action treatment; the global equipment-button
 // skin otherwise overrides BUTTON_COLOR_BLUE with a dark green panel.
 Panel(x,top,width,h,enabled?0x164EAD:0x19303F,enabled?0xEDBB58:0x607D8C);
 if(enabled){MemRect(x+8,top-5,width-16,2,0x75AEED);MemRect(x+8,top-h+7,width-16,2,0x103574);}
 SetFontColor(enabled?COLOR_WHITE:COLOR_GREY);
 CenterTextStrSolid(text,x+width/2,top-(h-FONT_HEIGHT*.68f)/2,.68f);
 if(enabled)SetRectPoint(x,top,width,h,command);
}
static int BlockLevel(int c,int room,bool preview){
 return preview?(room<0?CastleVisualPartLevel(c,3):LobbyCastleDebugFacilityLevel(c,room)):
  (room<0?robin.castleProgress.parts[c][3]:robin.castleProgress.rooms[c][room]);
}
static void BlockEffect(char* out,size_t size,int c,int room,int level){
 if(room<0)snprintf(out,size,"포격 계수 %d%%",CastleMenuModel::CannonTurnPercent(level));
 else snprintf(out,size,"+%d%%",CastleFacilities::Output(c,room,level));
}
static void UpgradeBlock(int c,int index,int x,int top,int width,bool preview){
 const auto& item=CastleUpgradeBlocks::Items[index];const int room=item.room;
 const bool turret=room<0;const int h=turret?CastleUpgradeBlocks::TurretHeight(DY):CastleUpgradeBlocks::CardHeight(DY);
 const bool compact=DY<1000;
 const int level=BlockLevel(c,room,preview),next=preview?(level+1)%6:Min(5,level+1);
 const int command=turret?TOUCH_FUNC_CASTLE_NEW_UPGRADE:TOUCH_FUNC_CASTLE_FACILITY_UPGRADE+room;
 const bool owned=CastleMenuModel::Owned(robin.castleProgress,c);
 const int price=CastleMenuModel::UpgradeCost(c,level,!turret);
 const bool ready=owned&&level<5&&robin.gold>=price&&!SaveConflict();
 Panel(x,top,width,h,0x1B344A,0x709BB2);
 char s[160],current[64],after[64];
 Text(item.title,x+12,top-10,width-92,compact?.72f:.82f,0xFFE5A0);
 snprintf(s,sizeof(s),"Lv.%d / 5",level);Text(s,x+width-82,top-12,72,.62f);
 if(turret)DrawInventoryCannonIcon(c,level,x+12,top-30,92,compact?76:90);
 else {
  const int icons[4]={ICON_EVENT_HEART,ICON_SHIELD,ICON_EVENT_SWORD,ICON_GOLDBAG};
  // These are the existing native pixel icons, rather than scaled room thumbnails.
  DrawIcon(icons[index],x+18,top-(compact?28:42),(compact?44.f:64.f)/ITEMICONSIZE,0,false,false,1);
 }
 BlockEffect(current,sizeof(current),c,room,level);BlockEffect(after,sizeof(after),c,room,next);
 const int tx=x+108,tw=width-120;
 snprintf(s,sizeof(s),"현재 %s",current);Text(s,tx,top-(compact?32:46),tw,compact?.60f:.66f);
 snprintf(s,sizeof(s),level>=5&&!preview?"최대 단계":"다음 %s",after);Text(s,tx,top-(compact?54:78),tw,compact?.64f:.72f,0x82DAC4);
 const int bx=turret?x+width/2:x+12,bw=turret?width/2-12:width-24;
 if(preview)snprintf(s,sizeof(s),"무료 단계 비교 · %d > %d",level,next);
 else if(level>=5)snprintf(s,sizeof(s),"MAX · 강화 완료");
 else if(!owned)snprintf(s,sizeof(s),"미보유 성");
 else snprintf(s,sizeof(s),"강화 · %d 골드",price);
 // Entire block and its button have the same action.
 if(preview||ready)SetRectPoint(x,top,width,h,command);
 UpgradeAction(s,bx,top-h+56,bw,command,preview||ready);
 if(turret)castleRow=3;
}
}
void CastleMenuNewDraw(){
 using namespace CastleFinal;panelDrawSlot=0;
 CastleProgressEnsure();const auto& p=robin.castleProgress;const int c=castleBrowse;
 const bool owned=CastleMenuModel::Owned(p,c),preview=DebugControlsOpen()&&LobbyCastleDebugActive();
 const int top=HeaderTop(),body=BodyTop(),left=16,width=DX-32,bottom=BodyBottom();
 scT[MENU_CASTLE]=ScrollMax();scY[MENU_CASTLE]=Min(scT[MENU_CASTLE],Max(0,scY[MENU_CASTLE]));
 int y=body+scY[MENU_CASTLE];char s[256];
 ResetRectPoint();SetAlpha(ALPHA_MAX);Panel(0,top,DX,top,0x0C1C2C,0x43859B);
 SetSectionClip(0,body,DX,body-bottom,false);
 const int ph=PreviewHeight();Panel(left,y,width,ph,0x142E43,0x43859B);
 RebuildPreview(c,left+8,y-6,width*54/100,ph-12);
 const int ix=left+width*55/100,iw=width*45/100-12;
 CastleLabel(CastleFacilities::Themes[c],ix+iw/2,y-18,iw,.78f);
 CastleLabel(preview?"DEBUG · 무료 단계 비교":"방 4개 · 대포 1기",ix+iw/2,y-50,iw,.6f);
 Button(robin.castle==c?"현재 출정 성":"출정 성 선택",ix,y-ph+56,iw,48,TOUCH_FUNC_CASTLE_NEW_SELECT,owned&&robin.castle!=c);
 y-=ph+12;
 Panel(left,y,width,44,0x142E43,0x43859B);
 snprintf(s,sizeof(s),"출정 성 생산 %lld/시간",CastleIncomePerHour());Text(s,left+12,y-13,width/2,.64f,0x82DAC4);
 snprintf(s,sizeof(s),"%lld 골드 수금",CastleIncomeNow());
 Button(s,left+width/2,y,width/2,48,TOUCH_FUNC_CASTLE_INCOME,CastleIncomeNow()>0&&!SaveConflict());y-=48;
 const int cw=(width-CastleUpgradeBlocks::Gap)/2;
 for(int i=0;i<4;++i)UpgradeBlock(c,i,left+(i%2)*(cw+CastleUpgradeBlocks::Gap),y-(i/2)*(CastleUpgradeBlocks::CardHeight(DY)+CastleUpgradeBlocks::Gap),cw,preview);
 y-=2*(CastleUpgradeBlocks::CardHeight(DY)+CastleUpgradeBlocks::Gap);
 UpgradeBlock(c,4,left,y,width,preview);
 if(scT[MENU_CASTLE]>0){
  const int track=body-bottom,thumb=Max(36,track*track/ContentHeight());
  MemRect(DX-8,body,4,track,0x142E43);
  MemRect(DX-8,body-scY[MENU_CASTLE]*(track-thumb)/scT[MENU_CASTLE],4,thumb,0x82DAC4);
 }
 UnSectionClip(false);Panel(0,top,DX,54,0x102638,0x43859B);
 snprintf(s,sizeof(s),"성 관리 · %d / 10",c+1);
 CastleLabel(s,DX/2-20,top-15,width-240,.85f);DrawMenuBackButton(12,top-4,TOUCH_FUNC_POPUP_CLOSE);
 Button("<",DX-120,top-3,52,48,TOUCH_FUNC_CASTLE_NEW_PREV,c>0);
 Button(">",DX-62,top-3,52,48,TOUCH_FUNC_CASTLE_NEW_NEXT,c<9);
 MergeRouletteBottomNavDraw();
 if(castleModal){
  ResetRectPoint();SetAlpha(24);MemRect(0,top,DX,top,COLOR_BLACK);SetAlpha(ALPHA_MAX);
  const bool upgrade=castleModal==2;const int mt=Min(top-12,bottom+360);
  Panel(16,mt,DX-32,344,0x1B344A,0x709BB2);
  CastleLabel(upgrade?"시설 강화":"성 구매 확인",DX/2,mt-16,DX-80,.95f);
  const int room=castleUpgradeIsRoom?castleUpgradePart:-1;
  const char* title=CastleFacilities::Themes[c];
  if(upgrade)for(const auto& item:CastleUpgradeBlocks::Items)if(item.room==room)title=item.title;
  snprintf(s,sizeof(s),upgrade?"%s · Lv.%d > Lv.%d":"%s",title,castleUpgradeLevel,castleUpgradeLevel+1);
  CastleLabel(s,DX/2,mt-58,DX-80,.8f);
  if(upgrade){
   if(room<0)DrawInventoryCannonIcon(c,castleUpgradeLevel,40,mt-98,112,80);
   else FacilityIcon(c,room,castleUpgradeLevel,40,mt-94,100);
   char a[64],b[64];BlockEffect(a,sizeof(a),c,room,castleUpgradeLevel);BlockEffect(b,sizeof(b),c,room,castleUpgradeLevel+1);
   snprintf(s,sizeof(s),"현재 %s  >  다음 %s",a,b);Text(s,164,mt-110,DX-204,.74f,0x82DAC4);
   if(room==0)snprintf(s,sizeof(s),"생산 저장 한도 +%d%% > +%d%%",castleUpgradeLevel*50,(castleUpgradeLevel+1)*50);
   else snprintf(s,sizeof(s),room<0?"선택한 성의 지원 포격에 적용":"히어로에게 적용 · 모든 성에서 단계 유지");
   Text(s,164,mt-150,DX-204,.62f);
  }
  GoldPair(upgrade?castleUpgradePrice:CastleMenuModel::GoldPrice(c),robin.gold,40,mt-212,DX-80);
  MenuButton(32,mt-272,DX/3-32,48,"취소",BUTTON_COLOR_BROWN,true,TOUCH_FUNC_CASTLE_NEW_CANCEL,.75f);
  const bool enough=robin.gold>=(upgrade?castleUpgradePrice:CastleMenuModel::GoldPrice(c))&&!SaveConflict();
  UpgradeAction(upgrade?"강화 확정":"구매 확정",DX/3+12,mt-272,DX-DX/3-44,TOUCH_FUNC_CASTLE_NEW_CONFIRM,enough);
 }
 CastleMenuToast(1.f);
}
