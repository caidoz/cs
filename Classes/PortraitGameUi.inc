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
void portraitStat(const Box& b,int kind,long long value,long long maximum){
 const float s=DX/640.f;portraitSkin(4,b);
 const int size=(int)(28*s),x=b.x+(int)(8*s),y=b.y-(int)(5*s);
 portraitGlyph(kind==0?1:kind==1?4:5,{x,y,size,size});
 char number[80];if(kind==2)std::snprintf(number,sizeof(number),"%lld / %lld",value,maximum);else std::snprintf(number,sizeof(number),"%lld",value);
 if(StringWidth(number,UiMinimumTextZoom())>b.w-size-20*s){
  char a[32],z[32];portraitShortAmount(a,sizeof(a),value);portraitShortAmount(z,sizeof(z),maximum);
  if(kind==2)std::snprintf(number,sizeof(number),"%s/%s",a,z);else std::snprintf(number,sizeof(number),"%s",a);
 }
 const float zoom=std::max(.32f,std::min(.68f,(b.w-size-22*s)/std::max(1.f,StringWidth(number,s))));
 label(number,b.x+size+(b.w-size)/2,y,zoom,0xF1EFE3);
 const int n=8,gap=std::max(1,(int)(2*s)),left=b.x+(int)(10*s),width=b.w-(int)(20*s),height=std::max(3,(int)(7*s));
 const float fill=kind==2?std::max(0.f,std::min(1.f,value/(float)std::max(1LL,maximum))):value>0?1.f:0.f;
 const int colors[3]={0xCFA75A,0x77B8D8,0x58CC98};
 for(int i=0;i<n;++i){const int x0=left+i*width/n,x1=left+(i+1)*width/n;
  bevel({x0,b.y-b.h+(int)(13*s),x1-x0-gap,height},(i+.5f)/n<=fill?colors[kind]:0x2B3B46,std::max(1,(int)s));}
}
void drawPortraitStats(const Box& b,long long attack,long long defense,long long hp,long long maxHp){
 const int gap=std::max(2,(int)(8*DX/640.f)),unit=(b.w-2*gap)/3;
 portraitStat({b.x,b.y,unit,b.h},0,attack,attack);
 portraitStat({b.x+unit+gap,b.y,unit,b.h},1,defense,defense);
 portraitStat({b.x+2*(unit+gap),b.y,b.w-2*(unit+gap),b.h},2,hp,maxHp);
}
void drawPortraitEnemyHealth(const Layout& l){
 const float s=l.scale;const int x=(int)(DX*.73f),width=(int)(DX*.23f),y=l.arenaBottom+(int)(17*s),h=(int)(9*s);
 bevel({x,y,width,h},0x204248,(int)(3*s));
 const double ratio=run.enemyMax>0?std::max(0.,std::min(1.,enemyHealthDisplay.value/run.enemyMax)):0;
 if(ratio>0)bevel({x+2,y-2,(int)((width-4)*ratio),h-4},0x72D0A3,(int)(2*s));
 const Box ally={(int)(48*s),y,(int)(DX*.46f),h};portraitSkin(0,ally);
 const float life=run.maxLives>0?std::max(0.f,std::min(1.f,run.lives/(float)run.maxLives)):0.f;
 if(life>0)bevel({ally.x+2,ally.y-2,(int)((ally.w-4)*life),h-4},0x64E7AD,(int)(2*s));
}
void drawPortraitEnergy(const Layout& l){
 const float s=l.scale;const Box b=l.heart;
 portraitGlyph(3,{b.x-(int)(32*s),b.y,(int)(26*s),(int)(26*s)});
 const int w=b.w-(int)(68*s);portraitSkin(0,{b.x,b.y,w,b.h});
 for(int i=0;i<Run::BattleEnergyMax;++i){const int x=b.x+(int)(8*s)+i*(w-(int)(16*s))/5;
  bool filled=i<heartDisplay;if(i==spentHeart&&heartBlink>0)filled=((int)(heartBlink/.09f)%2)==0;
  bevel({x,b.y-(int)(6*s),(w-(int)(24*s))/5,(int)(14*s)},filled?0x5DD69C:0x2D3B46,(int)(2*s));}
 char n[20];std::snprintf(n,sizeof(n),"%d / %d",heartDisplay,Run::BattleEnergyMax);label(n,b.x+b.w-(int)(24*s),b.y-(int)(3*s),.66f);
 char capacity[32];std::snprintf(capacity,sizeof(capacity),u8"판 %d칸",portraitGridCapacity());
 label(capacity,(int)(560*s),b.y-(int)(3*s),.48f,0xA2CFD0);
}
void drawPortraitLobby(const Layout& l){
 UnSectionClip(false);
 const float s=l.scale;const auto p=PortraitGame::lobby(DX,DY);
 MemRect(0,p.statsTop+(int)(6*s),DX,p.statsTop+(int)(6*s),0x030A13);
 const int stage=std::max(0,std::min(18,run.stage));
 char line[96];std::snprintf(line,sizeof(line),u8"%s \u00b7 %d\ub2e8\uacc4",PortraitCastleArt::Names[stage],stage+1);
 const Box castleTag={DX/2-(int)(150*s),p.statsTop+(int)(36*s),(int)(300*s),(int)(28*s)};portraitSkin(4,castleTag);
 label(line,DX/2,castleTag.y-(int)(3*s),.48f,0xF3E4A5);
 const Box destination={(int)(24*s),p.stageTop,DX-(int)(48*s),(int)(88*s)};portraitSkin(4,destination);
 portraitImage(PORTRAIT_NIGHT_IMG,{destination.x+(int)(16*s),destination.y-(int)(16*s),(int)(100*s),(int)(56*s)});
 const int textCenter=destination.x+(destination.w+(int)(120*s))/2;
 label(StageBg::RegionName(stage/10),textCenter,destination.y-(int)(14*s),.62f);
 std::snprintf(line,sizeof(line),"STAGE %02d \u00b7 WAVE %02d / 15",stage+1,std::max(1,std::min(15,(int)robin.curWaveIdx+1)));
 label(line,textCenter,destination.y-(int)(48*s),.52f,0xEFE5BF);
 const Box start=lobbyStart(l);drawLobbyStartButton(start);
 drawLobbyBottomNav(0,true);
 // Existing expeditions/PVP remain reachable; upgrades keep their existing UI.
 Box pvp=lobbyPvp(l);pvp={DX-(int)(80*s),l.ground+(int)(38*s),(int)(64*s),(int)(28*s)};
 portraitFrame(pvp,false,true);label("PVP",pvp.x+pvp.w/2,pvp.y-(int)(5*s),.46f);
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
void drawPortraitCastlePreview(int castle,const Box& b,float wheelTravel,bool rollLeft){
 const int c=std::max(0,std::min(18,castle));const auto& size=PortraitCastleArt::Sizes[c];
 const float wheel=PortraitCastleArt::WheelSize(c);
 const float z=std::min(b.w/(size.w+80.f),b.h/(size.h+wheel));
 const int w=(int)(size.w*z),h=(int)(size.h*z),x=b.x+(b.w-w)/2,bottom=b.y-b.h+(int)(wheel*.58f*z);
 drawPortraitFarWheels(c,{x,bottom+h,w,h},z,wheelTravel,false,rollLeft);
 portraitImage(portraitHullImage(c),{x,bottom+h,w,h});
 const int diameter=(int)(wheel*z);for(int i=0;i<(c<5?2:3);++i){const float at=c<5?(i?PortraitCastleArt::FrontWheelAt(c):.17f):(.15f+.345f*i);
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
 const Box body=portraitCastleBox(l);const float ceiling=DY-78*s;
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
