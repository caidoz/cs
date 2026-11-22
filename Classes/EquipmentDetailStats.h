namespace EquipDetailStats {
struct Row {int icon;std::string text,value;};
static int selected=-1,finger=-1,left=0,top=0,width=0,height=0;
static float scroll=0,limit=0,lastY=0;
static bool visible=false;
int index(const ITEM* it){for(int i=0;i<GetMaxInven();++i)if(it==&robin.inven[i])return i;return -1;}
bool equipped(const ITEM* it){
 const ITEM& worn=ao[PLAYER].equip[itemEquipSlot[it->type]];
 return worn.type==it->type&&worn.id!=0&&worn.id==it->id;
}
int icon(int option){
 if(option==PREFIX_CRITICAL||option==SUFFIX_CRITICAL)return SKILLICON_QUEST_CRITICAL;
 if(option==PREFIX_ARMOR||option==SUFFIX_ARMOR)return ICON_SHIELD;
 if(option==SUFFIX_HP||option==PREFIX_VIT||option==PREFIX_HPRESTORE||option==SUFFIX_HPDRAIN)return ICON_EVENT_HEART;
 if(option==SUFFIX_MP||option==PREFIX_MPRESTORE||option==SUFFIX_MPDRAIN)return ICON_EVENT_BLUEJEWEL;
 if(option==PREFIX_GOLD||option==SUFFIX_GOLD)return ICON_GOLD;
 if(option==PREFIX_PIERCE)return ICON_EVENT_AXE;
 if(option==SUFFIX_EVASION)return GetItemIcon(ITEM_GREAVES,0,GRADE_NORMAL);
 if(option==PREFIX_EXP||option==SUFFIX_EXP)return EXP_ICON;
 if(option>=SUFFIX_FIRE_ATTACK&&option<=SUFFIX_DARK_ATTACK)return SKILLICON_QUEST_FIRE+option-SUFFIX_FIRE_ATTACK;
 if(option>=PREFIX_FIRE_REGIST&&option<=PREFIX_DARK_REGIST)return SKILLICON_QUEST_FIRE+option-PREFIX_FIRE_REGIST;
 return ICON_EVENT_SWORD;
}
std::vector<Row> rows(ITEM* it){
 std::vector<Row> out;const int slot=itemEquipSlot[it->type];
 if(it->type<ITEM_NECK){
  long long value=GetEquipValue(it);int image=ICON_EVENT_SWORD;const char* title=u8"공격력";
  if(slot==EQUIP_HELM||slot==EQUIP_ARMOR){image=ICON_SHIELD;title=u8"방어력";}
  if(slot==EQUIP_PANTS||slot==EQUIP_BOOTS){image=ICON_EVENT_HEART;title=u8"체력";value=RoundDiv(value*HERO_HP_PER_ARMOR,100);}
  char amount[64];snprintf(amount,sizeof(amount),"+%lld",value);
  out.push_back({image,title,amount});
 }
 SetItemString_Gem(it);
 for(int n=0;n<12;++n)if(it->option[n][0]!=EMPTYINT&&optionStr[n][0])out.push_back({icon(it->option[n][0]),optionStr[n],""});
 for(int n=0;n<6;++n)if(gemStr[n][0])out.push_back({n<5?SKILLICON_QUEST_FIRE+n:ICON_SHIELD,gemStr[n],""});
 if(it->grade==GRADE_SET)for(int n=0;n<7;++n)if(setStr[n][0])out.push_back({ITEM_COLLECTIONS_ICON,setStr[n],""});
 return out;
}
}

bool EquipDetailStatsTouch(int phase,int id,float x,float y){
 using namespace EquipDetailStats;
 if(drawHandle!=MD_LOBBY||menuDepth!=1||popUpCnt<=0||popUp[popUpCnt-1].type!=POPUPTYPE_COLLECTIONS||IsTutorialPlaying()||menuItem<0||menuItem>=GetMaxInven()||!IsEquipItemType(robin.inven[menuItem].type)||!visible){finger=-1;return false;}
 if(phase==0){
  if(x<left||x>left+width||y>top||y<top-height)return false;
  if(finger<0){finger=id;lastY=y;}return true;
 }
 if(finger!=id)return false;
 if(phase==1){scroll=Max(0.f,Min(limit,scroll+y-lastY));lastY=y;}
 if(phase==2||phase==3)finger=-1;
 return true;
}

static void DrawLobbyEquipmentDetail(ITEM* it){
 using namespace EquipDetailStats;
 const int idx=index(it);if(idx!=selected){selected=idx;scroll=0;finger=-1;}
 const auto stats=rows(it);const bool worn=equipped(it);
 const int screenTop=DY-(GNBHEIGHT-GNB_INIT_HEIGHT)-LOBBY_BAR_H-6;
 const int dialogH=Min(Max(600,360+(int)stats.size()*40),screenTop-12),upper=screenTop-Max(0,(screenTop-dialogH)/2),art=150;
 DrawPixelPanel(8,upper,DX-16,dialogH,0x12383E,0xC5A269);
 DrawMenuRoomBackdrop(12,upper-56,DX-24,art);
 DrawMenuPlaque("장비 상세",8,upper,DX-16,56,1.1f);
 DrawUiButton(DX-62,upper-6,44,44,"X",TOUCH_FUNC_CLOSEALERT);
 const int foot=upper-56-art+18;
 DrawPixelPanel(DX/2-88,foot+32,176,32,0x8B623C,0xDEBB86);
 const float iz=Min(2.8f,(art-42)/(float)ITEMICONSIZE);
 DrawIcon(GetItemIcon(it->type,it->detail,it->grade),DX/2-ITEMICONSIZE*iz/2,foot+ITEMICONSIZE*iz+18,iz,false,false,false,true);
 const char* name=textId[GetItemName(it->type,it->detail,it->grade)+TEXT_ITEMNAME_START];
 SetFontColor(0xFFF0C9);CenterTextStrSolid(name,DX/2,foot-16,Min(1.f,(DX-64)/Max(1.f,StringWidth(name,1.f))));
 const int footer=upper-dialogH+76;
 left=24;top=foot-60;width=DX-48;height=Max(40,top-footer-20);visible=true;
 limit=Max(0.f,(float)stats.size()*40-height);scroll=Max(0.f,Min(limit,scroll));
 DrawPixelPanel(left,top,width,height,0x102F36,0x43859B);
 SetSectionClip(left+4,top-4,width-8,height-8,false);
 for(int n=0;n<(int)stats.size();++n){
  const Row& row=stats[n];const int y=top-6-n*40+(int)scroll;
  DrawIcon(row.icon,left+12,y,30.f/ITEMICONSIZE,false,false,false,true);
  SetFontColor(0xEAF3F0);
  DrawTextStr(row.text.c_str(),left+54,y-7,Min(.78f,(width-(row.value.empty()?78:184))/Max(1.f,StringWidth(row.text.c_str(),1.f))));
  if(!row.value.empty()){SetFontColor(0x8FE0BA);DrawTextStrSystem(row.value.c_str(),left+width-20,y-7,.86f,RIGHT,true);}
 }
 UnSectionClip(false);
 if(limit>0){const int thumb=Max(24,height*height/((int)stats.size()*40));MemRect(left+width-6,top-(int)(scroll*(height-thumb)/limit),3,thumb,0xEBC587);}
 sEquipBtnX=24;sEquipBtnY=footer;sEquipBtnW=(DX-60)/2;sEquipBtnH=48;
 DrawUiButton(24,footer,(DX-60)/2,48,worn?"현재 장착 중":"장착하기",TOUCH_FUNC_EQUIP_INVENTORY+Max(0,idx),true,!worn&&idx>=0);
 DrawUiButton(DX/2+6,footer,(DX-60)/2,48,it->locked?"잠금 해제":"잠금",TOUCH_FUNC_ITEM_LOCK,it->locked);
 SetFontColor(COLOR_WHITE);
}

bool EquipmentDetailStatsReview(int step){
 using namespace EquipDetailStats;
 if(!getenv("CS_EQUIP_STATS_REVIEW"))return false;
 ITEM* it=&robin.inven[menuItem];
 if(step==0){
  bool exact=false;for(int n=0;n<touchIndex;++n)if(touchRect[n][4]==TOUCH_FUNC_EQUIP_INVENTORY+20)exact=true;
  const auto data=rows(it);
  return exact&&!equipped(it)&&data.size()==13&&data[0].value=="+100";
 }
 if(step==1){
  if(limit<=0)return true;
  EquipDetailStatsTouch(0,997,left+width/2,top-height/2);
  EquipDetailStatsTouch(1,997,left+width/2,top-height/2+80);
  EquipDetailStatsTouch(2,997,left+width/2,top-height/2+80);
  return scroll>0&&scroll<=limit;
 }
 if(step==2){
  ExecTouchFunc(sEquipBtnX+sEquipBtnW/2,sEquipBtnY-sEquipBtnH/2);PlayKey(PLAYER);systemKey=0;
  it=&robin.inven[menuItem];return it->id==880002&&equipped(it)&&menuItem!=20;
 }
 if(step==3){
  for(int n=0;n<GetMaxInven();++n)if(robin.inven[n].type!=EMPTY&&robin.inven[n].id==880001)menuItem=n;
  return !equipped(&robin.inven[menuItem])&&ao[PLAYER].equip[EQUIP_WEAPON].id==880002;
 }
 return false;
}
