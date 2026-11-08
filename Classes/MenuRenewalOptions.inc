static void RenewalOptionsDraw(){
 ResetRectPoint();const int top=DY-(GNBHEIGHT-GNB_INIT_HEIGHT)-LOBBY_BAR_H-6;
 DrawPixelPanel(0,top,DX,top,0x152D37,0x65827F);
 DrawMenuRoomBackdrop(0,top-58,DX,top-58,1,0);
 SetAlpha(18);MemRect(0,top-58,DX,top-58,0x092B30);SetAlpha(32);
 DrawMenuPlaque("설정",0,top,DX,56,1.15f);
 DrawMenuBackButton(12,top-4,TOUCH_FUNC_POPUP_CLOSE);
 const char* names[]={"배경음악","효과음","진동","푸시 알림"};
 const int commands[]={TOUCH_FUNC_OPTION_BGM,TOUCH_FUNC_OPTION_SE,TOUCH_FUNC_OPTION_VIBRATION,TOUCH_FUNC_OPTION_PUSHALARM};
 const bool values[]={option.bgm!=0,option.se!=0,option.vibration!=0,option.pushAlarm!=0};
 const int row=Max(56,Min(86,(top-220)/9));int y=top-100;
 for(int i=0;i<4;++i){
  DrawPixelPanel(24,y,DX-48,row-8,0x152D37,0x65827F);
  SetFontColor(0xF2E7CB);DrawTextStrSystem(names[i],48,y-(row-8)/2+10,.95f,LEFT,false);
  const int st=y-(row-40)/2;
  DrawPixelPanel(DX-116,st,70,32,values[i]?0x387B36:0x1D393E,0xC5A269);
  DrawPixelPanel(values[i]?DX-78:DX-112,st-4,24,24,0xFFF0C9,0xFFF0C9);
  SetRectPoint(24,y,DX-48,row-8,commands[i]);y-=row;
 }
 DrawPixelPanel(24,y,DX-48,row-8,0x152D37,0x65827F);
 SetFontColor(0xF2E7CB);DrawTextStrSystem("언어",48,y-(row-8)/2+10,.95f,LEFT,false);
 DrawUiButton(DX-232,y-8,192,row-24,textId[TEXT_KOREAN+option.language],TOUCH_FUNC_OPTION_LANGUAGE);y-=row+8;
 const char* links[]={"고객센터","이용약관","개인정보 처리방침","확률정보"};
 const int actions[]={TOUCH_FUNC_OPTION_HELP,TOUCH_FUNC_OPTION_POLICY,TOUCH_FUNC_OPTION_PRIVACY,TOUCH_FUNC_OPTION_RATES};
 DrawMenuPlaque("고객 지원",DX/4,y-4,DX/2,38,.74f);y-=54;
 for(int i=0;i<4;++i){
  DrawPixelPanel(24,y,DX-48,row-8,0x12383E,0xC5A269);
  SetFontColor(0xFFF0C9);DrawTextStrSystem(links[i],48,y-(row-8)/2+10,.87f,LEFT,false);
  DrawTextStrSystem(">",DX-54,y-(row-8)/2+10,.9f,RIGHT,false);
  SetRectPoint(24,y,DX-48,row-8,actions[i]);y-=row;
 }
 SetFontColor(0xE1D0AD);DrawTextStrSystem(textId[TEXT_VERSION],DX/2,Max(24,y-16),.7f,CENTER,false);
}
