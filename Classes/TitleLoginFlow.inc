// Title controls are separate from artwork and survive InitMenu during bootstrap.
namespace TitleLogin {
static bool requested=false;
static int ticks=0;
static bool ready=false;
static void Button(int x,int y,int w,int h,const char* label,int command,bool enabled){
 DrawPixelPanel(x,y,w,h,enabled?0x29483E:0x202C3A,enabled?0xC7AA69:0x688794);
 SetFontColor(enabled?0xFFF1C2:0xA9B6BE);
 CenterTextStrSolid(label,x+w/2,y-h/2+10,.86f);
 if(enabled)SetRectPoint(x,y,w,h,command);
}
static void Draw(){
 ResetRectPoint();
 const int w=Min(DX-48,320),h=44,gap=10,x=(DX-w)/2;
 const int guestY=Max(86,Min(150,DY/9));
 if(requested){
  const int progress=ready?Min(100,ticks*100/36):Min(90,ticks*90/36);
  DrawPixelPanel(x,guestY,w,24,0x182A36,0x73949C);
  if(progress>0)MemRect(x+4,guestY-4,(w-8)*progress/100,16,0x80B892);
  SetFontColor(COLOR_WHITE);char label[48];sprintf(label,"%d%%",progress);
  CenterTextStrSolid(label,DX/2,guestY-5,.60f);return;
 }
 int row=1;
#if CC_TARGET_PLATFORM != CC_PLATFORM_IOS
 Button(x,guestY+(h+gap)*row++,w,h,"Google 로그인",TOUCH_FUNC_TITLE_LOGIN_GOOGLE,NetLoginProviderAvailable(LOGIN_GOOGLE));
#endif
#if CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID
 Button(x,guestY+(h+gap)*row++,w,h,"Apple 로그인",TOUCH_FUNC_TITLE_LOGIN_APPLE,NetLoginProviderAvailable(LOGIN_APPLE));
#endif
 Button(x,guestY,w,h,"게스트 로그인",TOUCH_FUNC_TITLE_LOGIN_GUEST,true);
}
}
bool TitleLoginBusy(){return drawHandle==MD_TITLE&&TitleLogin::requested;}
void TitleLoginStart(int provider){
 if(drawHandle!=MD_TITLE||TitleLogin::requested||!NetLoginProviderAvailable(provider))return;
 if(NetBootstrapPoll()==NETRESULT_NONE && !NetChooseLogin(provider))return;
 TitleLogin::requested=true;TitleLogin::ticks=0;curMenu=MENU_LOADING;touchDisable=false;
}
void TitleLoginStep(bool dataReady){
 TitleLogin::ready=dataReady;
 if(drawHandle!=MD_TITLE){TitleLogin::requested=false;TitleLogin::ticks=0;return;}
 if(!TitleLogin::requested && NetHasRememberedGuestLogin())TitleLoginStart(LOGIN_GUEST);
 if(!TitleLogin::requested)return;
 curMenu=MENU_LOADING;++TitleLogin::ticks;
 if(dataReady && TitleLogin::ticks>=36){
  NetRememberGuestLogin();TitleLogin::requested=false;TitleLogin::ticks=0;
  GotoLobby();
 }
}
