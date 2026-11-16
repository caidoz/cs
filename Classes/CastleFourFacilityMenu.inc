// Shared permanent facilities and one castle-specific turret, in one list.
void CastleMenuNewDraw(){
 using namespace CastleFinal;panelDrawSlot=0;
 CastleProgressEnsure();const auto& p=robin.castleProgress;const int c=castleBrowse;
 const bool owned=CastleMenuModel::Owned(p,c);
 const bool preview=DebugControlsOpen()&&LobbyCastleDebugActive();
 const int top=HeaderTop(),body=BodyTop(),left=16,width=DX-32,bottom=HOMEBAR_HEIGHT+16;
 scT[MENU_CASTLE]=ScrollMax();scY[MENU_CASTLE]=Min(scT[MENU_CASTLE],Max(0,scY[MENU_CASTLE]));
 int y=body+scY[MENU_CASTLE];char s[256];
 ResetRectPoint();SetAlpha(ALPHA_MAX);Panel(0,top,DX,top,0x0C1C2C,0x43859B);
 SetSectionClip(0,body,DX,body-bottom,false);
 const int first=Min(7,Max(0,c-1)),tile=(width-16)/3;
 for(int n=0;n<3;++n){const int pick=first+n,x=left+n*(tile+8);
  Button("",x,y,tile,70,TOUCH_FUNC_CASTLE_BROWSE_PICK+pick,true,pick==c);
  RebuildPreview(pick,x+8,y-6,54,54);
  sprintf(s,"%d / 10",pick+1);CastleLabel(s,x+tile*2/3,y-28,tile/2,.75f);
 }
 y-=82;const int ph=PreviewHeight();Panel(left,y,width,ph,0x142E43,0x43859B);
 RebuildPreview(c,left+10,y-8,width*58/100,ph-20);
 const int ix=left+width*60/100,iw=width*40/100-12;
 CastleLabel(CastleFacilities::Themes[c],ix+iw/2,y-28,iw,.78f);
 CastleLabel("방 4개 · 포탑 1기",ix+iw/2,y-70,iw,.7f);
 if(owned)Button(robin.castle==c?"현재 출정 성":"출정 성 선택",ix,y-112,iw,44,TOUCH_FUNC_CASTLE_NEW_SELECT,robin.castle!=c);
 Button("<",left+8,y-ph+46,40,36,TOUCH_FUNC_CASTLE_NEW_PREV,c>0);
 Button(">",left+width-48,y-ph+46,40,36,TOUCH_FUNC_CASTLE_NEW_NEXT,c<9);
 y-=ph+18;
 Text(preview?"디버그 · 무료 외형 미리보기":"성 시설 강화",left+12,y,width-24,.95f,0xFFE5A0);y-=36;
 Text(preview?"단계 변경: Lv.0~5 순환 · 골드 차감/저장 없음":"방 강화는 모든 성에 유지 · 포탑은 성마다 강화",left+12,y,width-24,.65f,0x82DAC4);y-=34;
 sprintf(s,"히어로 공격 +%d%% · 체력 +%d%% · 방어 +%d%%",CastleMenuModel::Attack(p,c),CastleMenuModel::Health(p,c),CastleMenuModel::Defense(p,c));
 Text(s,left+12,y,width-24,.66f);y-=34;
 Text("식량 판매 수익 / 시간",left+12,y,width/2,.65f,0x82DAC4);
 DrawGoldAmount(CastleIncomePerHour(),left+width/2,y,width/2-12,LEFT);y-=38;
 const long long income=CastleIncomeNow();Button("",left,y,width,44,TOUCH_FUNC_CASTLE_INCOME,income>0&&!SaveConflict());
 DrawGoldAmount(income,left+12,y-8,width/2-20,LEFT);Text("수금",left+width-64,y-14,58,.65f);y-=60;
 // Slot order follows the agreed layout and keeps economy first after the turret.
 const int order[5]={-1,1,3,0,2};
 for(int row=0;row<5;++row){
  const int room=order[row];const bool turret=room<0;
  const int level=preview?(turret?CastleVisualPartLevel(c,3):LobbyCastleDebugFacilityLevel(c,room)):(turret?p.parts[c][3]:p.rooms[c][room]),next=preview?(level+1)%6:Min(5,level+1);
  const int imageW=width*36/100,tx=left+imageW+18,tw=width-imageW-30;
  Panel(left,y,width,160,0x142E43,0x43859B);
  if(turret)DrawInventoryCannonIcon(c,level,left+10,y-12,imageW-12,108);
  else FacilityPreview(c,room,level,left+8,y-10,imageW,130);
  const char* name=turret?CastleFacilities::TurretNames[c]:CastleFacilities::Rooms[c][room].name;
  sprintf(s,"%s · Lv.%d / 5",name,level);Text(s,tx,y-12,tw,Min(.75f,tw/Max(1.f,StringWidth(s,1.f))),0xFFE5A0);
  if(turret){
   sprintf(s,"지원포격 계수 %d%% > %d%%",CastleMenuModel::CannonTurnPercent(level),CastleMenuModel::CannonTurnPercent(next));Text(s,tx,y-44,tw,.62f,0x82DAC4);
   Text("성별 강화 · 첨탑 연결부 함께 보강",tx,y-72,tw,.56f);
  }else{
   sprintf(s,"%s +%d%% > +%d%%",CastleFacilities::Effect(c,room),CastleFacilities::Output(c,room,level),CastleFacilities::Output(c,room,next));Text(s,tx,y-44,tw,.62f,0x82DAC4);
   if(room==0)sprintf(s,"저장 한도 +%d%% > +%d%%",level*50,next*50);
   else sprintf(s,"히어로에게 적용 · 성 변경 시 유지");
   Text(s,tx,y-72,tw,.56f);
  }
  const int price=CastleMenuModel::UpgradeCost(c,level,!turret);
  const bool ready=owned&&level<5&&robin.gold>=price&&!SaveConflict();
  Button(preview?"단계 변경":level>=5?"MAX":"강화",tx,y-112,78,34,turret?TOUCH_FUNC_CASTLE_NEW_UPGRADE:TOUCH_FUNC_CASTLE_FACILITY_UPGRADE+room,preview||ready);
  if(turret)castleRow=3;
  if(preview)Text("무료 미리보기",tx+86,y-116,tw-86,.56f,0x82DAC4);
  else if(level<5)DrawGoldAmount(price,tx+86,y-116,tw-86,LEFT);
  y-=172;
 }
 UnSectionClip(false);Panel(0,top,DX,54,0x102638,0x43859B);
 CastleLabel("성",DX/2,top-15,width,.95f);DrawMenuBackButton(12,top-4,TOUCH_FUNC_POPUP_CLOSE);
 if(castleModal){
  ResetRectPoint();SetAlpha(24);MemRect(0,top,DX,top,COLOR_BLACK);SetAlpha(ALPHA_MAX);
  const int mt=DY/2+150;const bool upgrade=castleModal==2;
  Panel(24,mt,DX-48,270,0x102638,0xEDBB58);
  CastleLabel(upgrade?"시설 강화 확인":"성 구매 확인",DX/2,mt-20,DX-80,.9f);
  if(upgrade)sprintf(s,"%s Lv.%d > Lv.%d",castleUpgradeIsRoom?CastleFacilities::Rooms[c][castleUpgradePart].name:CastleFacilities::TurretNames[c],castleUpgradeLevel,castleUpgradeLevel+1);
  else snprintf(s,sizeof(s),"%s",CastleFacilities::Themes[c]);
  CastleLabel(s,DX/2,mt-64,DX-80,.8f);
  GoldPair(upgrade?castleUpgradePrice:CastleMenuModel::GoldPrice(c),robin.gold,40,mt-105,DX-80);
  CastleLabel(castleUpgradeIsRoom?"모든 성에서 강화 단계 유지":"포탑과 첨탑 연결부 외형 함께 강화",DX/2,mt-150,DX-80,.65f);
  Button("취소",40,mt-196,DX/2-48,48,TOUCH_FUNC_CASTLE_NEW_CANCEL);
  Button("강화 확정",DX/2+8,mt-196,DX/2-48,48,TOUCH_FUNC_CASTLE_NEW_CONFIRM,robin.gold>=castleUpgradePrice&&!SaveConflict());
 }
 CastleMenuToast(1.f);
}
