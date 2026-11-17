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
 const bool turret=room<0;const int h=CastleUpgradeBlocks::CardHeight(DY);
 const int level=BlockLevel(c,room,preview),next=preview?(level+1)%6:Min(5,level+1);
 const int command=turret?TOUCH_FUNC_CASTLE_NEW_UPGRADE:TOUCH_FUNC_CASTLE_FACILITY_UPGRADE+room;
 const bool owned=CastleMenuModel::Owned(robin.castleProgress,c);
 const int price=CastleMenuModel::UpgradeCost(c,level,!turret);
 const bool ready=owned&&level<5&&robin.gold>=price&&!SaveConflict();
 Panel(x,top,width,h,0x142E43,0x43859B);
 const char* name=turret?CastleFacilities::TurretNames[c]:CastleFacilities::Rooms[c][room].name;
 Text(name,x+16,top-12,width-32,Min(.8f,(width-32)/Max(1.f,StringWidth(name,1.f))),0xFFE5A0);
 char s[180],a[64],b[64];const int half=width/2,vw=half-38;
 snprintf(s,sizeof(s),"현재 Lv.%d",level);CastleLabel(s,x+half/2,top-36,vw,.65f);
 snprintf(s,sizeof(s),level>=5&&!preview?"최대 단계 Lv.%d":"강화 후 Lv.%d",next);CastleLabel(s,x+half+half/2,top-36,vw,.65f);
 if(turret){
  DrawInventoryCannonIcon(c,level,x+16,top-62,vw,86);
  DrawInventoryCannonIcon(c,next,x+half+22,top-62,vw,86);
 }else{
  FacilityPreview(c,room,level,x+16,top-62,vw,86);
  FacilityPreview(c,room,next,x+half+22,top-62,vw,86);
 }
 CastleLabel(">",x+half,top-96,28,.95f);
 BlockEffect(a,sizeof(a),c,room,level);BlockEffect(b,sizeof(b),c,room,next);
 snprintf(s,sizeof(s),"기능: %s · %s > %s",item.title,a,b);Text(s,x+16,top-158,width-32,.61f,0x82DAC4);
 if(preview)snprintf(s,sizeof(s),"무료 단계 비교 · %d > %d",level,next);
 else if(level>=5)snprintf(s,sizeof(s),"MAX · 강화 완료");
 else if(!owned)snprintf(s,sizeof(s),"미보유 성");
 else snprintf(s,sizeof(s),"강화 · %d 골드",price);
 if(preview||ready)SetRectPoint(x,top,width,h,command);
 UpgradeAction(s,x+half,top-h+56,half-16,command,preview||ready);
 Text(turret?"이 성의 포대 강화":"모든 성에서 방 단계 유지",x+16,top-h+40,half-32,.57f);
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
 DrawCastleMenuBackdrop(left+4,y-4,width-8,ph-8,c);
 SetAlpha(10);MemRect(left+4,y-4,width-8,ph-8,0x071527);SetAlpha(32);
 RebuildPreview(c,left+12,y-42,width-24,ph-96);
 CastleLabel(CastleFacilities::Themes[c],DX/2,y-14,width-32,.85f);
 Button(robin.castle==c?"현재 출정 성":"출정 성 선택",DX/2-100,y-ph+56,200,48,TOUCH_FUNC_CASTLE_NEW_SELECT,owned&&robin.castle!=c);
 y-=ph+12;
 Panel(left,y,width,48,0x142E43,0x43859B);
 snprintf(s,sizeof(s),"출정 성 생산 %lld/시간",CastleIncomePerHour());Text(s,left+12,y-13,width/2,.64f,0x82DAC4);
 snprintf(s,sizeof(s),"%lld 골드 수금",CastleIncomeNow());
 Button(s,left+width/2,y,width/2,48,TOUCH_FUNC_CASTLE_INCOME,CastleIncomeNow()>0&&!SaveConflict());y-=60;
 for(int i=0;i<5;++i)UpgradeBlock(c,i,left,y-i*(CastleUpgradeBlocks::CardHeight(DY)+CastleUpgradeBlocks::Gap),width,preview);
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
 if(castleModal){
  ResetRectPoint();SetAlpha(24);MemRect(0,top,DX,top,COLOR_BLACK);SetAlpha(ALPHA_MAX);
  const bool upgrade=castleModal==2;const int mt=Min(top-12,bottom+360);
  Panel(16,mt,DX-32,344,0x1B344A,0x709BB2);
  CastleLabel(upgrade?"시설 강화":"성 구매 확인",DX/2,mt-16,DX-80,.95f);
  const int room=castleUpgradeIsRoom?castleUpgradePart:-1;
  const char* title=CastleFacilities::Themes[c];
  if(upgrade)title=room<0?CastleFacilities::TurretNames[c]:CastleFacilities::Rooms[c][room].name;
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
