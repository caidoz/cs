// Native UI primitives keep all text, hit boxes and equipment live at any ratio.
void portraitFrame(const Box& b,bool amber,bool enabled){
 const int alpha=m_lgrpAlpha;grayScale=enabled?0:8;SetAlpha(alpha);
 Box face=b;if(enabled&&finger>=0&&b.has(downX,downY)&&b.has(pointerX,pointerY))face.y-=std::max(1,DX/320);
 portraitSkin(amber?3:2,face);grayScale=0;SetAlpha(alpha);
}
void portraitShortAmount(char* out,size_t size,long long value){
 if(value<1000){std::snprintf(out,size,"%lld",value);return;}
 static const char units[4]={'K','M','B','T'};double n=value/1000.;int unit=0;
 while(n>=999.5&&unit<3){n/=1000.;++unit;}
 std::snprintf(out,size,n<10?"%.1f%c":"%.0f%c",n,units[unit]);
}
void portraitCommaAmount(char* out,size_t size,long long value){
 char digits[24];const int n=std::snprintf(digits,sizeof(digits),"%lld",std::max(0LL,value));size_t at=0;
 for(int i=0;i<n&&at+2<size;++i){if(i&&(n-i)%3==0)out[at++]=',';out[at++]=digits[i];}
 out[at]=0;
}
void portraitStat(const Box& b,int kind,long long value,long long maximum,bool enemy=false){
 int& count=enemy?hostileStatCount:friendlyStatCount;
 if(count<3){(enemy?hostileStatBounds:friendlyStatBounds)[count]=b;(enemy?hostileStatKind:friendlyStatKind)[count]=kind;(enemy?hostileStatValue:friendlyStatValue)[count]=value;}++count;
 const float s=DX/640.f;const bool compact=b.w<150*s;
 portraitSkin(enemy?3:4,b);
 const int size=(int)((compact?24:39)*s),y=b.y-(int)(6*s);
 const Box icon={b.x-(int)(6*s),b.y+(int)(4*s),size,size};
 const int inset=size-(int)(6*s);
 char a[32],z[32],number[80];
 //적 체력은 K/M 으로 줄이지 않고 콤마 숫자 그대로 보인다.
 void(*amount)(char*,size_t,long long)=enemy&&kind==2?portraitCommaAmount:portraitShortAmount;
 amount(a,sizeof(a),value);amount(z,sizeof(z),maximum);
 if(kind==2)std::snprintf(number,sizeof(number),"%s/%s",a,z);else std::snprintf(number,sizeof(number),"%s",a);
 if(compact&&StringWidth(number,UiMinimumTextZoom())>b.w-inset-14*s)std::snprintf(number,sizeof(number),"%s",a);
 const float zoom=std::max(.28f,std::min(compact?.48f:.66f,(b.w-inset-16*s)/std::max(1.f,StringWidth(number,s))));
 label(number,b.x+inset+(b.w-inset)/2,y,zoom,enemy?0xFFE4D4:0xF1EFE3);
 const int gap=std::max(1,(int)(2*s)),width=b.w-(int)(16*s),height=std::max(3,(int)(6*s));
 const int n=std::max(1,(width+gap)/(height+gap));
 const int left=b.x+(b.w-(n*height+(n-1)*gap))/2;
 const float fill=kind==2?std::max(0.f,std::min(1.f,value/(float)std::max(1LL,maximum))):value>0?1.f:0.f;
 const int ally[3]={0xCFA75A,0x77B8D8,0x58CC98},hostile[3]={0xF293A8,0xECAE72,0xED6D81};
 for(int i=0;i<n;++i){const int x0=left+i*(height+gap);
  bevel({x0,b.y-b.h+(int)(12*s),height,height},(i+.5f)/n<=fill?(enemy?hostile[kind]:ally[kind]):0x2B303E,std::max(1,(int)s));}
 // Status symbols overlap the frame in front, rather than shrinking inside it.
 if(enemy&&kind==2){portraitImage(PORTRAIT_DEMON_HEART_IMG,icon);drawnEnemyHeartIcon=icon;}
 else portraitGlyph(kind==0?1:kind==1?4:5,icon);
}
void portraitStatTrio(const Box& b,long long attack,long long defense,long long hp,long long maximum,bool enemy){
 const int gap=std::max(2,(int)(4*DX/640.f)),usable=b.w-2*gap;
 const int narrow=usable*2/7;const int widths[3]={narrow,narrow,usable-2*narrow};
 const long long values[3]={attack,defense,hp};int x=b.x;
 for(int slot=0;slot<3;++slot){const int kind=enemy?2-slot:slot;portraitStat({x,b.y,widths[kind],b.h},kind,values[kind],kind==2?maximum:values[kind],enemy);x+=widths[kind]+gap;}
}
void drawPortraitStats(const Box& b,long long attack,long long defense,long long hp,long long maximum){
 if(siegeActive&&Siege::swapped){attack=Siege::foe.preview(Siege::foeStats);defense=run.enemyGuard;hp=run.enemyHp;maximum=run.enemyMax;}
 portraitStatTrio(b,attack,defense,hp,maximum,false);
}
void drawPortraitEnemyHealth(const Layout& l){
 const float s=l.scale;const Box right={DX/2+(int)(8*s),l.arenaBottom,DX/2-(int)(32*s),l.plateH};
 if(siegeActive){
  const auto& foe=Siege::swapped?run:Siege::foe;const auto& power=Siege::swapped?stats:Siege::foeStats;
  portraitStatTrio(right,foe.preview(power),Siege::swapped?currentGuard():run.enemyGuard,Siege::swapped?run.lives:run.enemyHp,Siege::swapped?run.maxLives:run.enemyMax,true);
 }else portraitStat(right,2,std::max(0LL,(long long)enemyHealthDisplay.value),run.enemyMax,true);
}
void drawPortraitEnergy(const Layout& l){
 const float s=l.scale;const Box b=l.heart;
 drawnBattleEnergyBounds={b.x,b.y,b.w-(int)(68*s),b.h};
 portraitGlyph(3,{b.x-(int)(32*s),b.y,(int)(26*s),(int)(26*s)});
 const int w=b.w-(int)(68*s);portraitSkin(0,{b.x,b.y,w,b.h});
 for(int i=0;i<Run::BattleEnergyMax;++i){const int x=b.x+(int)(8*s)+i*(w-(int)(16*s))/5;
  bool filled=i<heartDisplay;if(i==spentHeart&&heartBlink>0)filled=((int)(heartBlink/.09f)%2)==0;
  bevel({x,b.y-(int)(6*s),(w-(int)(24*s))/5,(int)(14*s)},filled?0x5DD69C:0x2D3B46,(int)(2*s));}
 char n[20];std::snprintf(n,sizeof(n),"%d / %d",heartDisplay,Run::BattleEnergyMax);label(n,b.x+b.w-(int)(24*s),b.y-(int)(3*s),.66f);
}
void drawPortraitLobby(const Layout& l){
 UnSectionClip(false);
 const float s=l.scale;const auto p=PortraitGame::lobby(DX,DY);
 const float leaving=-(DY+100*s)*BaseCamp::uiExit(lobbyDepartureAge);
 // Keep the rail arches and fading piers visible behind the separate lobby panels.
 const int stage=std::max(0,std::min(18,run.stage));
 char line[96];std::snprintf(line,sizeof(line),u8"%s \u00b7 %d\ub2e8\uacc4",PortraitCastleArt::Names[stage],stage+1);
 uiSceneMotionY=leaving+(titleLobbyClock>=0?-160*s*(1.f-TitleLobbyEase(.64f,1.1f)):0);
 const Box castleTag={DX/2-(int)(150*s),p.statsTop+(int)(36*s),(int)(300*s),(int)(28*s)};portraitSkin(4,castleTag);
 label(line,DX/2,castleTag.y-(int)(3*s),.48f,0xF3E4A5);
 uiSceneMotionY=leaving+(titleLobbyClock>=0?-260*s*(1.f-TitleLobbyEase(.76f,1.24f)):0);
 const Box destination={(int)(24*s),p.stageTop+(int)(16*s),DX-(int)(48*s),(int)(88*s)};portraitSkin(4,destination);
 portraitImage(PORTRAIT_NIGHT_IMG,{destination.x+(int)(16*s),destination.y-(int)(16*s),(int)(100*s),(int)(56*s)});
 const int textCenter=destination.x+(destination.w+(int)(120*s))/2;
 label(StageBg::RegionName(stage/10),textCenter,destination.y-(int)(14*s),.62f);
 std::snprintf(line,sizeof(line),"STAGE %02d \u00b7 WAVE %02d / 15",stage+1,std::max(1,std::min(15,(int)robin.curWaveIdx+1)));
 label(line,textCenter,destination.y-(int)(48*s),.52f,0xEFE5BF);
 uiSceneMotionY=leaving+(titleLobbyClock>=0?-240*s*(1.f-TitleLobbyEase(.88f,1.36f)):0);
 const Box start=lobbyStart(l);drawLobbyStartButton(start);
 uiSceneMotionY=leaving;
 drawLobbyBottomNav(0,true);
 // Existing expeditions/PVP remain reachable; upgrades keep their existing UI.
 Box pvp=lobbyPvp(l);
 portraitFrame(pvp,false,true);label("PVP",pvp.x+pvp.w/2,pvp.y-(int)(5*s),.46f);
 uiSceneMotionY=0;
 // MergeRouletteTouch owns the PVP hit box.
}

void drawPortraitTopbar(){
 const float s=DX/640.f;const int top=DY-(int)(10*s),h=(int)(54*s);
 const int xs[5]={12,164,310,410,572},ws[5]={152,146,100,150,56};
 portraitSkin(4,{(int)(12*s),top,(int)(548*s),h});portraitSkin(2,{(int)(572*s),top,(int)(56*s),h});
 portraitSkin(2,{(int)(12*s),top,(int)(56*s),h});
 portraitHeroIcon({(int)(18*s),top-(int)(4*s),(int)(44*s),(int)(44*s)});
 char n[64];std::snprintf(n,sizeof(n),"Lv.%d",robin.lv+1);label(n,(int)(115*s),top-(int)(17*s),.62f);
 const int glyphs[3]={6,7,3},positions[3]={170,314,416};
 const long long values[3]={std::max(0LL,robin.gold-gLobbyGoldInFlight),robin.coin,robin.heart};
 for(int i=0;i<3;++i){portraitGlyph(glyphs[i],{(int)(positions[i]*s),top-(int)(12*s),(int)(28*s),(int)(28*s)});
  if(i==2)std::snprintf(n,sizeof(n),"%lld/%d",values[i],GetInitHeart());
  else if(values[i]>=1000000)std::snprintf(n,sizeof(n),"%.1fM",values[i]/1000000.);else std::snprintf(n,sizeof(n),"%lld",values[i]);
  label(n,(int)((positions[i]+(i==1?64:86))*s),top-(int)(17*s),.60f);
 }
 portraitGlyph(8,{(int)(582*s),top-(int)(10*s),(int)(36*s),(int)(34*s)});
 const int actions[5]={TOUCH_FUNC_POPUP_LVUPREWARD,TOUCH_FUNC_GOTO_GOLD_IAP,TOUCH_FUNC_GOTO_RAINBOW_IAP,TOUCH_FUNC_GOTO_ENERGY_IAP,TOUCH_FUNC_SETTING};
 for(int i=0;i<5;++i)SetRectPoint(xs[i]*s,top,ws[i]*s,h,actions[i]);
}

//wheelTravel 가 0 이상이면 그만큼 굴러간 각도로 바퀴를 돌린다(제목 화면). 음수면 그대로 선 바퀴.
void drawPortraitCastlePreview(int castle,const Box& b,float wheelTravel,bool rollLeft,float fixedScale){
 const int c=std::max(0,std::min(18,castle));const auto& size=PortraitCastleArt::Sizes[c];
 const float wheel=PortraitCastleArt::WheelSize(c);
 const float z=fixedScale>0?fixedScale:std::min(b.w/(size.w+80.f),b.h/(size.h+wheel));
 const int w=(int)(size.w*z),h=(int)(size.h*z),bottom=b.y-b.h+(int)(wheel*.58f*z);
 int x=b.x+(b.w-w)/2;
 if(fixedScale>0){
  const int gun=PORTRAIT_TURRET_FIRST_IMG+c;if(!sprite[gun])LoadImg(gun);
  const float gw=c==0?StarterCastleRig::W*z:sprite[gun]?sprite[gun]->getTexture()->getContentSizeInPixels().width*z:0;
  const float right=std::max((float)w,w*PortraitCastleArt::FrontWheelAt(c)-PortraitCastleArt::CannonFootX[c]*z+gw);
  x=b.x+(int)((b.w-right)/2);
 }
 drawPortraitFarWheels(c,{x,bottom+h,w,h},z,wheelTravel,false,rollLeft);
 // Management thumbnails keep the complete exterior, independent of lobby reveal.
 portraitImage(PORTRAIT_CASTLE_FIRST_IMG+c,{x,bottom+h,w,h});
 const int diameter=(int)(wheel*z);for(int i=0;i<PortraitCastleArt::WheelCount(c);++i){const float at=PortraitCastleArt::WheelAt(c,i);
  const Box wb={x+(int)(w*at)-diameter/2,bottom+(int)(diameter*.42f),diameter,diameter};
  const int img=PORTRAIT_WHEEL_FIRST_IMG+c;if(wheelTravel<0){portraitImage(img,wb);continue;}
  if(!sprite[img])LoadImg(img);if(!sprite[img])continue;
  const auto sz=sprite[img]->getTexture()->getContentSizeInPixels();const float wz=std::min(wb.w/sz.width,wb.h/sz.height);
  const float angle=(rollLeft?-1.f:1.f)*std::fmod(wheelTravel/std::max(1.f,sz.height*wz*.5f)*57.2957795f,360.f);
  RotateImage((int)sz.width,(int)sz.height,0,0,wb.x+wb.w/2,wb.y-wb.h/2,false,angle,0,0,wz,cocos2d::Vec2(.5f,.5f),sprite[img],img);}
 const int gun=PORTRAIT_TURRET_FIRST_IMG+c;if(!sprite[gun])LoadImg(gun);
 if(sprite[gun]){const auto dim=sprite[gun]->getTexture()->getContentSizeInPixels();
  if(c==0){
   using namespace StarterCastleRig;const int axle=x+(int)(w*PortraitCastleArt::FrontWheelAt(c));
   const Box mount={axle-(int)(FootX*z),bottom+(int)((BaseFromFloor+StarterCastleRig::H)*z),(int)(StarterCastleRig::W*z),(int)(StarterCastleRig::H*z)};
   turretPart(gun,0,0,StarterCastleRig::W,StarterCastleRig::H,mount);
   turretPart(gun,RockX,RockY,RockW,RockH,{mount.x+(int)((CupX-RockDrawW*.5f)*z),mount.y-(int)((CupY-RockDrawH*.5f)*z),(int)(RockDrawW*z),(int)(RockDrawH*z)});
   turretPart(gun,StarterCastleRig::W,0,StarterCastleRig::W,StarterCastleRig::H,mount);
   return;
  }
  const int gw=(int)(dim.width*z),gh=(int)(dim.height*z);
  const int axle=x+(int)(w*PortraitCastleArt::FrontWheelAt(c));
  drawMountedPortraitGun(gun,{axle-(int)(PortraitCastleArt::CannonFootX[c]*z),bottom+(int)(PortraitCastleArt::CannonBaseFromFloor(c)*z)+gh,gw,gh},
   {x,bottom+h,w,h},false);}

}

bool portraitCameraTouch(int phase,int id,float x,float y){
 if(siegeActive||RewardPopup::open()||entryChoiceOpen||resumePromptOpen||quitPromptOpen||popUpCnt>0||LoadoutOpen())return false;
 if(active&&(run.attacking||introActive()||entering()||startEventActive()))return false;
 const Layout l=layout();const float s=l.scale;
 const int fixedGround=l.ground-(int)portraitCameraY;
 const Box hull=portraitCastleBox(l);
 const Box body=!active&&starterInteriorReveal>=.999f?portraitInteriorBox(std::max(0,std::min(18,run.stage)),hull):hull;const float ceiling=DY-78*s;
 const float maximum=std::max(0.f,body.y-portraitCameraY-ceiling);
 const int floor=active?l.arenaBottom:PortraitGame::lobby(DX,DY).statsTop;
 //성 디버그가 켜진 로비에서는 누르기(phase 0)를 디버그 터치(방·포탑·몸체 순환)에 넘기고, 끌기만 카메라가 받는다.
 const bool debugLobby=!active&&DebugControlsOpen()&&LobbyCastleDebugActive();
 if(phase==0&&y>floor+12*s&&y<ceiling&&maximum>0){portraitCameraFinger=id;portraitCameraDown=y;portraitCameraStart=portraitCameraY;return !debugLobby;}
 if(id!=portraitCameraFinger)return false;
 if(phase==1)portraitCameraY=std::max(-maximum,std::min(0.f,portraitCameraStart+y-portraitCameraDown));
 if(phase==2||phase==3)portraitCameraFinger=-1;
 (void)fixedGround;(void)x;return true;
}

// A held touch reveals a circular window; three seconds latches the full interior.
bool portraitStarterInteriorTouch(int phase,int id,float x,float y){
 if(active||drawHandle!=MD_LOBBY||siegeActive||RewardPopup::open()||entryChoiceOpen||resumePromptOpen||quitPromptOpen||popUpCnt>0||LoadoutOpen()||DebugControlsOpen()||LobbyCastleDebugActive()){
  if(id==starterInteriorFinger){starterInteriorFinger=-1;starterInteriorHeld=0;}return false;
 }
 const Layout l=layout();
 if(phase==0){
  const Box hull=portraitCastleBox(l),inside=portraitInteriorBox(std::max(0,std::min(18,run.stage)),hull);
  if(!(hull.has(x,y)||inside.has(x,y))||y<l.arenaBottom+12*l.scale||y>DY-78*l.scale)return false;
  starterInteriorFinger=id;starterInteriorHeld=0;starterInteriorStart=starterInteriorReveal;starterInteriorAxis=0;starterInteriorDownX=x;starterInteriorDownY=y;
  starterInteriorTouchX=x;starterInteriorTouchY=y;return true;
 }
 if(id!=starterInteriorFinger)return false;
 if(phase==1){
  const float dx=x-starterInteriorDownX,dy=y-starterInteriorDownY;
  if(!starterInteriorAxis&&std::abs(dy)>12*l.scale&&std::abs(dy)>std::abs(dx)*1.2f){
   if(portraitCameraTouch(0,id,starterInteriorDownX,starterInteriorDownY)){starterInteriorAxis=2;starterInteriorHeld=0;}
  }
  if(starterInteriorAxis==2){portraitCameraTouch(1,id,x,y);return true;}
  starterInteriorTouchX=x;starterInteriorTouchY=y;
 }
 if(phase==2||phase==3){
  if(starterInteriorAxis==2)portraitCameraTouch(phase,id,x,y);
  if(phase==3)starterInteriorReveal=starterInteriorStart;
  starterInteriorFinger=-1;starterInteriorHeld=0;starterInteriorAxis=0;
 }
 return true;
}
