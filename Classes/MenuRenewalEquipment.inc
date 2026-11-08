namespace RenewEquipment {
static void Header(const char* title){
 const int top=EquipmentV2::Top();DrawPixelPanel(0,top,DX,top,0x152D37,0x65827F);
 SetFontColor(0xF2E7CB);CenterTextStrSolid(title,DX/2,top-10,.9f);
 DrawMenuBackButton(12,top-4,TOUCH_FUNC_POPUP_CLOSE);
 EquipmentV2::HeroStrip();
}
static void Tabs(int y){
 const int width=(DX-32)/EQUIPTAB_CNT;
 for(int i=0;i<EQUIPTAB_CNT;++i)MenuButton(16+i*width,y,width-4,36,kEquipTabName[i],curEquipTab==i?BUTTON_COLOR_BLUE:BUTTON_COLOR_BROWN,true,curEquipTab==i?0:TOUCH_FUNC_EQUIPTAB+i,.64f);
}
static void CrewPortrait(int detail,int x,int foot,int height){
 if(detail<0||detail>=gTotalCrew)return;
 const int type=crewData[detail*CREWDATASIZE+CREWDATA_TYPE],cmf=enemyData[type*ENEMYDATASIZE+ENEMYDATA_CMF],motion=crewPos[type*5];
 if(cmf<0||!cmd_m_cnt[cmf]||!cmfMotionImgSize[cmf])return;
 
 const float z=height/(float)Max(1,(int)cmfMotionImgSize[cmf][motion*4+3]);
 const int bottom=cmfMotionImgSize[cmf][motion*4+1]+cmfMotionImgSize[cmf][motion*4+3];
 DrawCmfDetailShadow(cmf,motion,x,foot+(int)(bottom*z),RIGHT,z);
}
}
static void RenewalCrewDraw(){
 using namespace RenewEquipment;using namespace EquipmentV2;
 Header("동료");const int top=Top(),preview=PreviewHeight(),listTop=ListTop();
 const int body=top-130,foot=top-preview+22;
 DrawMenuRoomBackdrop(0,body,DX,preview-114,1,0);
 DrawPixelPanel(26,foot+16,146,24,0x8B623C,0xDEBB86);
 DrawPlayer(&ao[PLAYER],frame/8%4,98,foot+12,RIGHT,2.0f,false,false,true);
 int stars=0;
 const int pitch=(DX-184)/3,slotH=Max(54,Min(88,(preview-166)/2));
 for(int i=0;i<MAXCREW;++i){
  const int x=168+(i%3)*pitch,y=body-12-(i/3)*(slotH+8);
  DrawPixelPanel(x,y,pitch-8,slotH,menuX==i?0x2F6570:0x152D37,menuX==i?0xC5A269:0x65827F);
  const int inv=robin.slotCrew[i]>=0?GetCrewInventoryIdx(robin.slotCrew[i]):-1;
  if(inv>=0&&inv<TOTALINVENTORY){
   CrewPortrait(robin.inven[inv].detail,x+(pitch-8)/2,y-slotH+12,50);
   stars+=GetItemStar(ITEM_CREW,robin.inven[inv].detail,robin.inven[inv].grade);
  }else{SetFontColor(0xA6BAB1);CenterTextStrSolid("+",x+(pitch-8)/2,y-18,.85f);}
  if(menuDepth==0)SetRectPoint(x,y,pitch-8,slotH,TOUCH_FUNC_MENUX_1+i);
 }
 DrawPixelPanel(32,top-preview+4,DX-64,80,0x123D43,0xF2C17D);
 char text[100];SetFontColor(0xF2E7CB);sprintf(text,"편성 보급력 %d / %d",stars,castleStarLimit[robin.castle]);
 CenterTextStrSolid(text,DX/2,top-preview-12,1.f);
 SetFontColor(0xAEC4B9);CenterTextStrSolid("슬롯을 고르고 동료를 선택하세요",DX/2,top-preview-46,.62f);
 Tabs(top-preview-86);
 int items[TOTALINVENTORY],count=0;
 for(int i=0;i<TOTALINVENTORY;++i)if(robin.inven[i].type==ITEM_CREW)items[count++]=i;
 const int cols=4,pitchX=(DX-32)/cols,cell=pitchX-8,rowH=120,height=listTop-20;
 scT[MENU_CREW]=Max(0,((count+cols-1)/cols)*rowH-height);scY[MENU_CREW]=Min(scT[MENU_CREW],Max(0,scY[MENU_CREW]));
 SetSectionClip(16,listTop,DX-32,height,false);
 for(int i=0;i<count;++i){
  const int x=16+(i%cols)*pitchX,y=listTop-(i/cols)*rowH+scY[MENU_CREW];if(y<20||y-rowH>listTop)continue;
  const auto& it=robin.inven[items[i]];
  bool equipped=false;for(int n=0;n<MAXCREW;++n)equipped|=robin.slotCrew[n]>=0&&GetCrewInventoryIdx(robin.slotCrew[n])==items[i];
  DrawPixelPanel(x,y,cell,rowH-8,0x152D37,equipped?0xC5A269:0x65827F);
  CrewPortrait(it.detail,x+cell*34/100,y-78,62);
  sprintf(text,"Lv.%d",it.lv);SetFontColor(0xF2E7CB);DrawTextStrSystem(text,x+cell-8,y-14,.6f,RIGHT,false);
  const int crewType=crewData[it.detail*CREWDATASIZE+CREWDATA_TYPE];
  const char* name=textId[TEXT_MONSTERNAME_START+crewType];
  DrawTextStrSystem(name,x+cell/2,y-90,Min(.62f,(cell-14)/Max(1.f,StringWidth(name,1.f))),CENTER,false);
  if(equipped){SetFontColor(0xA7E5AC);DrawTextStrSystem("✓",x+6,y-4,.65f,LEFT,false);}
  if(menuDepth==0)SetRectPoint(x,y,cell,rowH-8,TOUCH_FUNC_ITEMDETAIL+items[i]);
 }
 UnSectionClip(false);DrawScroll(DX-10,listTop,height,MENU_CREW);
 if(count==0){SetFontColor(0xAEC4B9);CenterTextStrSolid("보유한 동료가 없습니다",DX/2,listTop-36,.7f);}
 if(menuDepth==1){ResetRectPoint();ScreenDarken(SCREENDARKEN);CrewDetailDraw(&robin.inven[menuItem],0,top,1.f,top-16);gTouchRectLocked=true;}
}

static void RenewalStatsDraw(){
 using namespace RenewEquipment;const int top=EquipmentV2::Top();Header("능력치");
 auto* hero=&ao[PLAYER];const int body=top-130;
 DrawMenuRoomBackdrop(0,body,DX,150);DrawPlayer(hero,0,110,body-136,RIGHT,1.8f,false,false,true);
 char line[160];sprintf(line,"전투력 %lld",GetCombatPower(hero));DrawMenuPlaque(line,DX/3,body-40,DX*2/3-24,62,1.05f);
 Tabs(body-164);
 const int ids[]={PS_DMG,PS_ARMOR,PS_HP,PS_CRITICAL,PS_CRITDMG,PS_STR,PS_VIT,PS_AGI,PS_INT,PS_LUCK,PS_GOLDMOD,PS_EXPMOD};
 const char* names[]={"공격력","방어력","체력","치명타","치명타 피해","힘","체력 능력치","민첩","지능","행운","골드 획득","경험치 획득"};
 const int start=body-214,width=(DX-44)/2,row=Max(60,Min(86,(start-24)/6));
 const int optionRows=(TOTALMENUOPTION+1)/2;
 const int content=6*row+48+3*66+48+optionRows*60;
 const int height=Max(1,start-20);
 scT[MENU_COLLECTIONS]=Max(0,content-height);
 scY[MENU_COLLECTIONS]=Min(scT[MENU_COLLECTIONS],Max(0,scY[MENU_COLLECTIONS]));
 SetSectionClip(16,start,DX-32,height,false);
 for(int i=0;i<12;++i){
  const int x=16+(i%2)*(width+12),y=start-(i/2)*row+scY[MENU_COLLECTIONS];
  DrawPixelPanel(x,y,width,row-8,0x152D37,0x65827F);
  SetFontColor(0xAEC4B9);DrawTextStrSystem(names[i],x+12,y-12,.62f,LEFT,false);
  const long long value=hero->ps[ids[i]]+(ids[i]==PS_CRITICAL?DEFAULTCRITICAL:0);
  sprintf(line,"%lld%s",value,i==3||i==4||i>=10?"%":"");
  SetFontColor(0xF2E7CB);DrawTextStrSystem(line,x+width-12,y-12,.78f,RIGHT,false);
 }
 int y=start-6*row-12+scY[MENU_COLLECTIONS];
 SetFontColor(0xC5A269);DrawTextStrSystem("속성 저항",24,y,.72f,LEFT,false);y-=36;
 const char* elements[]={"화염 저항","냉기 저항","번개 저항","신성 저항","암흑 저항"};
 for(int i=0;i<5;++i){
  const int x=16+(i%2)*(width+12),sy=y-(i/2)*66;
  DrawPixelPanel(x,sy,width,58,0x152D37,0x65827F);
  SetFontColor(0xAEC4B9);DrawTextStrSystem(elements[i],x+12,sy-14,.62f,LEFT,false);
  sprintf(line,"%lld",hero->ps[PS_FIRE+i]);SetFontColor(0xF2E7CB);DrawTextStrSystem(line,x+width-12,sy-14,.72f,RIGHT,false);
 }
 y-=3*66+12;
 SetFontColor(0xC5A269);DrawTextStrSystem("추가 능력치",24,y,.72f,LEFT,false);y-=36;
 for(int i=0;i<TOTALMENUOPTION;++i){
  const int x=16+(i%2)*(width+12),sy=y-(i/2)*60;
  DrawPixelPanel(x,sy,width,52,0x152D37,0x65827F);
  snprintf(line,sizeof(line),TEXTPTR(TEXT_PREFIX_DESC+optionInfo[i*2+1]),Abs(hero->ps[optionInfo[i*2]]));
  SetFontColor(0xF2E7CB);DrawTextStrSystem(line,x+10,sy-16,Min(.58f,(width-20)/Max(1.f,StringWidth(line,1.f))),LEFT,false);
 }
 UnSectionClip(false);DrawScroll(DX-10,start,height,MENU_COLLECTIONS);
}
