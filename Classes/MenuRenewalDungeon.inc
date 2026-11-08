// Preview only: no new entry cost, unlock requirement or reward is invented.
static bool gRenewDungeon=false;
bool MenuRenewalDungeonOpen(){return gRenewDungeon;}
bool MenuRenewalCommand(int command){
 if(drawHandle!=MD_LOBBY){gRenewDungeon=false;return false;}
 if(command==TOUCH_FUNC_LOBBY_DUNGEON){gRenewDungeon=true;PlayMusic(M_SELECT);return true;}
 if(command==TOUCH_FUNC_RENEW_DUNGEON_CLOSE||(gRenewDungeon&&popUpCnt==0&&command==TOUCH_FUNC_POPUP_CLOSE)){
  gRenewDungeon=false;PlayMusic(M_BUTTON);return true;
 }
 if(command==TOUCH_FUNC_SHOP||command==TOUCH_FUNC_COLLECTIONS||command==TOUCH_FUNC_LOBBY_CASTLE||command==TOUCH_FUNC_LOBBY_ADVENTURE)gRenewDungeon=false;
 return false;
}
static void MenuRenewalDungeonDraw(){
 if(!gRenewDungeon||popUpCnt>0)return; // Settings/alerts stay above this page.
 ResetRectPoint();const int top=DY-(GNBHEIGHT-GNB_INIT_HEIGHT)-LOBBY_BAR_H-6;
 const int bottom=BOTTOMMENUHEIGHT+12,available=top-bottom;
 DrawPixelPanel(0,top,DX,available,0x0D3038,0xC5A269);
 const int artTop=top-58,artH=Max(190,Min(430,available*48/100));
 const int scene=MENU_RENEWAL_DUNGEON_IMG;if(!sprite[scene])LoadImg(scene);
 if(sprite[scene]){const auto sz=sprite[scene]->getContentSize();
  const float z=Max(DX/sz.width,artH/sz.height);const int sw=Min((int)sz.width,(int)(DX/z)),sh=Min((int)sz.height,(int)(artH/z));
  DrawImageScale(sw,sh,(sz.width-sw)/2,(sz.height-sh)/2,0,artTop,false,0,0,0,0,DX/(float)sw,artH/(float)sh,sprite[scene],scene);}
 CastlePartsDrawMenuPreview(robin.castle+1,8,artTop-artH/3,DX*38/100,artH*58/100);
 DrawPlayer(&ao[PLAYER],0,DX*45/100,artTop-artH*75/100,RIGHT,1.35f,false,false,true);
 DrawIcon(ICON_EVENT_LOCK,DX*69/100,artTop-artH*48/100,1.4f,false,false,false,true);
 int y=artTop-artH-12;
 DrawMenuPlaque("새로운 원정을 준비 중입니다",DX/6,y+40,DX*2/3,48,.86f);y-=24;
 const char* names[]={"보스 토벌","보급 원정","성채 시련"};
 const char* descriptions[]={"강력한 보스에 도전하는 편성","성장을 위한 보급 원정","배치와 시너지를 시험하는 전투"};
 const int rowH=Max(66,Min(140,(y-bottom-78)/3));
 for(int i=0;i<3;++i){
  DrawPixelPanel(20,y,DX-40,rowH-10,0x123D43,0xF2C17D);
  if(i==1)DrawMenuRoomBackdrop(DX/2,y-6,DX/2-26,rowH-22,0,0);
  else if(sprite[scene]){const auto sz=sprite[scene]->getContentSize();
   DrawImageScale((int)sz.width/2,(int)sz.height/3,(int)sz.width/2,i==0?0:(int)sz.height/2,DX/2,y-6,false,0,0,0,0,(DX/2-26)/(sz.width/2),(rowH-22)/(sz.height/3),sprite[scene],scene);}
  SetFontColor(0xFFF0C9);DrawTextStrSystem(names[i],42,y-10,.95f,LEFT,false);
  DrawIcon(ICON_EVENT_LOCK,44,y-rowH+24,.5f,false,false,false,true);
  SetFontColor(0xF1D8AB);DrawTextStrSystem("준비 중",72,y-rowH+22,.58f,LEFT,false);
  y-=rowH;
 }
 DrawUiButton(32,bottom+60,DX-64,48,"로비로 돌아가기",TOUCH_FUNC_RENEW_DUNGEON_CLOSE,true);
 DrawPixelPanel(0,top,DX,54,0x152D37,0xC5A269);
 SetFontColor(0xF2E7CB);CenterTextStrSolid("던전",DX/2,top-12,.95f);
 DrawMenuBackButton(12,top-4,TOUCH_FUNC_RENEW_DUNGEON_CLOSE);
}
