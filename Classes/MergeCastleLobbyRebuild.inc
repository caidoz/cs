int castleRoomLevel(int c,int room);
// Facilities remain independently upgradeable behind the chassis' alpha holes.
#include "MergeCastleOriginal.inc"
#include "MergeCastleMist.inc"
float battleRailLift(){
 const float s=DX/640.f;
 const int c=siegeHullStage>=0?siegeHullStage:std::max(0,std::min(9,run.stage));
 const auto& wheels=MistCastle::wheelAnchors[c];
 const int contact=std::max(wheels[0][1]+wheels[0][2],wheels[1][1]+wheels[1][2]);
 const bool lobby=drawHandle==MD_LOBBY&&!active&&!nativeTitleIsolate;
 const int ground=lobby?PortraitGame::lobby(DX,DY).ground:PortraitGame::battle(DX,DY).ground;
 return ground-(1445-contact)*castleDisplayScale(c)-34*s;
}
float entryElapsed=-1.f;
constexpr float StartEventDuration=3.2f;
float startEventElapsed=-1.f;
bool startEventActive(){return startEventElapsed>=0.f&&startEventElapsed<StartEventDuration;}
unsigned panicSeed=0;
int drawnFrontCover=-1;
Box drawnFrontCoverBounds={0,0,0,0};
Box drawnFrontInnerBounds={0,0,0,0};
float castleWheelTravel=0.f;
float castleWheelAngle(float radius){return std::fmod(castleWheelTravel/std::max(1.f,radius)*57.2957795f,360.f);}
void drawPortraitFarWheels(int c,const Box& hull,float z,float travel,bool mirror=false,bool rollLeft=false){
 const int img=PORTRAIT_WHEEL_FIRST_IMG+c;if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 const auto size=sprite[img]->getTexture()->getContentSizeInPixels();
 const float angle=(mirror||rollLeft?-1.f:1.f)*std::fmod(std::max(0.f,travel)/std::max(1.f,size.height*z*.5f)*57.2957795f,360.f);
 const int previous=baseColor;SetColor(0xABB3C0);
 const float depth=PortraitCastleArt::Sizes[c].w/256.f;
 const int count=c<5?2:3;
 for(int i=0;i<count;++i){const float at=count==2?(i?PortraitCastleArt::FrontWheelAt(c):.17f):(.15f+.345f*i);
  const int x=hull.x+(int)(hull.w*(mirror?1.f-at:at))+(int)((mirror?-1.f:1.f)*StarterCastleRig::FarWheelDx*depth*z);
  const int y=hull.y-hull.h-(int)(size.height*z*.08f)+(int)(StarterCastleRig::FarWheelDy*depth*z);
  RotateImage((int)size.width,(int)size.height,0,0,x,y,false,angle,0,0,z,cocos2d::Vec2(.5f,.5f),sprite[img],img);
 }
 SetColor(previous);
}
bool entering(){return entryElapsed>=0&&entryElapsed<MergeCastleTransition::Duration;}
void drawWorld(const Layout& l,bool combat);
int castleRoomLevel(int c,int room){
 const int preview=LobbyCastleDebugFacilityLevel(c,room);
 return std::min(5,preview>=0?preview:(int)robin.castleProgress.rooms[c][room]);
}
//---- 대포가 놓인 자리 ----
//
//데크에 서는 사람들이 이 앞(오른쪽)에 선다. 그리는 쪽과 세우는 쪽이
//같은 상자를 봐야 사람이 포신에 겹치지 않는다.
bool portraitLobbyWorld(){return !active&&!nativeTitleIsolate&&!siegeActive;}
bool portraitAssembledSample(){return review&&run.stage==0&&std::getenv("CS_PORTRAIT_SAMPLE_ASSEMBLED")&&std::getenv("CS_PORTRAIT_SAMPLE_ASSETS");}
float portraitCannonFootX(int c){
 if(review&&c==0&&std::getenv("CS_PORTRAIT_SAMPLE_ASSETS"))
  if(const char* foot=std::getenv("CS_PORTRAIT_SAMPLE_FOOT_X"))return (float)std::atof(foot);
 return PortraitCastleArt::CannonFootX[c];
}
int portraitHullImage(int c){
 // Keep the approved exterior; the starter cutaway is a separate debug view.
 const bool interior=c==0&&((LobbyCastleDebugActive()&&LobbyCastleDebugInterior())||(review&&std::getenv("CS_PORTRAIT_INTERIOR")));
 return (interior||(c==0&&portraitLobbyWorld()&&popUpCnt==0&&!titleCampOnly&&starterInteriorReveal>=.999f))?PORTRAIT_STARTER_INTERIOR_IMG:PORTRAIT_CASTLE_FIRST_IMG+c;
}
PortraitCastleArt::Size portraitHullSize(int c){
 if(review&&c==0&&std::getenv("CS_PORTRAIT_SAMPLE_ASSETS")){
  const int img=PORTRAIT_CASTLE_FIRST_IMG;if(!sprite[img])LoadImg(img);
  if(sprite[img]){const auto s=sprite[img]->getTexture()->getContentSizeInPixels();return {(int)s.width,(int)s.height};}
 }
 return PortraitCastleArt::Sizes[c];
}
float portraitCastleZoom(const Layout& l){
 if(portraitAssembledSample()){
  if(!portraitLobbyWorld())return .85f*l.scale;
  const auto size=portraitHullSize(0);const float t=std::max(0.f,std::min(1.f,(DY/l.scale-850.f)/558.f));
  return std::min((243.2f+230.4f*t)*l.scale/256.f,std::min((DX-48*l.scale)/size.w,(DY-78*l.scale-PortraitGame::lobby(DX,DY).ground)/size.h));
 }
 if(!portraitLobbyWorld()){
  const int c=std::max(0,std::min(18,siegeHullStage>=0?siegeHullStage:run.stage));
  const int img=PORTRAIT_TURRET_FIRST_IMG+c;if(!sprite[img])LoadImg(img);
  const float gunH=c==0?StarterCastleRig::H:sprite[img]?sprite[img]->getTexture()->getContentSizeInPixels().height:96.f;
  // The fixed inventory leaves less arena headroom late in the game. Keep the
  // complete weapon visible with one uniform camera scale, never squash art.
  const float room=std::max(32.f*l.scale,DY-78*l.scale-(l.ground-portraitCameraY));
  const float socket=std::max(16*l.scale,std::min(32*l.scale,room*.40f));
  return std::min(.85f*l.scale,std::max(.18f*l.scale,2.f*(room-socket-8*l.scale)/gunH));
 }
 const int c=std::max(0,std::min(18,run.stage));
 const float t=std::max(0.f,std::min(1.f,(DY/l.scale-850.f)/558.f));
 const auto firstSize=portraitHullSize(0);
 const float starterFit=std::max(1.f,DY-78*l.scale-PortraitGame::lobby(DX,DY).ground)*256.f/(firstSize.h+PortraitCastleArt::WheelSize(0)*.58f);
 // One uniform camera scale for every native hull: later widths grow with the art.
 const float assemblyFit=(DX-32*l.scale)/(PortraitCastleArt::MaxAssemblyRatio*PortraitCastleArt::Sizes[18].w/256.f);
 const float base=std::min(std::min((243.2f+230.4f*t)*l.scale,starterFit),assemblyFit)/256.f;
 const float moving=BaseCamp::travel(lobbyDepartureAge);return base*(1-moving)+.85f*l.scale*moving;
}
Box portraitCastleBox(const Layout& l){
 const int c=std::max(0,std::min(18,siegeHullStage>=0?siegeHullStage:run.stage));
 const auto size=portraitHullSize(c);const float z=portraitCastleZoom(l);
 if(portraitAssembledSample())return {portraitLobbyWorld()?(DX-(int)(size.w*z))/2:(int)(16*l.scale),l.ground+(int)(size.h*z),(int)(size.w*z),(int)(size.h*z)};
 const float wheel=PortraitCastleArt::WheelSize(c)*z;
 const int gun=PORTRAIT_TURRET_FIRST_IMG+c;if(!sprite[gun])LoadImg(gun);
 const float gunHeight=c==0?StarterCastleRig::H:sprite[gun]?sprite[gun]->getTexture()->getContentSizeInPixels().height:75.f;
 const float fixedGround=l.ground-portraitCameraY;
 const float socket=std::max(16*l.scale,std::min(32*l.scale,(DY-78*l.scale-fixedGround)*.40f));
 const bool fitsWeapon=wheel*.58f+(PortraitCastleArt::CannonBaseFromFloor(c)+gunHeight)*z<=DY-78*l.scale-fixedGround;
 const float lift=portraitLobbyWorld()||c==0||fitsWeapon?0.f:std::min(0.f,socket-wheel*.58f-(PortraitCastleArt::CannonBaseFromFloor(c)+gunHeight*.5f)*z);
 Box b={(int)(16*l.scale),l.ground+(int)(wheel*.58f+size.h*z+lift),(int)(size.w*z),(int)(size.h*z)};
 if(portraitLobbyWorld()){
  const float gunWidth=c==0?StarterCastleRig::W*z:sprite[gun]?sprite[gun]->getTexture()->getContentSizeInPixels().width*z:100*z;
  const float left=std::min(0.f,b.w*.15f-wheel*.5f);
  const float right=std::max((float)b.w,b.w*PortraitCastleArt::FrontWheelAt(c)+gunWidth-portraitCannonFootX(c)*z);
  b.x=(int)((28*l.scale-left)*(1-BaseCamp::travel(lobbyDepartureAge))+16*l.scale*BaseCamp::travel(lobbyDepartureAge));
 }
 if(siegeActive)b.x=DX-b.x-b.w;return b;
}
Box castleCannonBox(const Layout& l){
 const int c=std::max(0,std::min(18,siegeHullStage>=0?siegeHullStage:run.stage));
 const int img=PORTRAIT_TURRET_FIRST_IMG+c;if(!sprite[img])LoadImg(img);if(!sprite[img])return {0,0,0,0};
 const auto size=sprite[img]->getTexture()->getContentSizeInPixels();const Box hull=portraitCastleBox(l);
 const float z=portraitCastleZoom(l);const int w=(int)((c==0?StarterCastleRig::W:size.width)*z),h=(int)((c==0?StarterCastleRig::H:size.height)*z);
 const float at=PortraitCastleArt::FrontWheelAt(c);
 const int axle=hull.x+(int)(hull.w*(siegeActive?1.f-at:at));
 const int foot=(int)(portraitCannonFootX(c)*z);
 const int bottom=hull.y-hull.h+(int)(PortraitCastleArt::CannonBaseFromFloor(c)*z);
 return {axle-(siegeActive?w-foot:foot),bottom+h,w,h};
}

// Draw only the articulated turret; the mounting strip and castle stay fixed.
void turretPart(int img,int sx,int sy,int sw,int sh,const Box& b,float angle=0,float ax=.5f,float ay=.5f,bool flip=false,int color=0xFFFFFF,bool animatedBeam=false){
 if(!sprite[img])LoadImg(img);if(!sprite[img]||sw<=0||sh<=0)return;
 GetSpriteIndex(img);
 if(getSpriteIdx==totalRenderCnt){
  renderSprite[getSpriteIdx]=cocos2d::Sprite::createWithTexture(sprite[img]->getTexture());renderSprite[getSpriteIdx]->retain();renderSpriteIndex[getSpriteIdx]=getSpriteTexture;
  if(sameRenderSpriteCur[img]<3000)sameRenderSpriteArr[img][sameRenderSpriteCur[img]]=totalRenderCnt;
  ++sameRenderSpriteMax[img];++sameRenderSpriteCur[img];++totalRenderCnt;
 }
 auto* sp=renderSprite[getSpriteIdx];sp->setTexture(sprite[img]->getTexture());
 sp->setTextureRect(cocos2d::Rect(sx,sy,sw,sh));sp->setAnchorPoint({ax,ay});
 sp->setPosition({b.x+b.w*ax,b.y-b.h*(1-ay)});sp->setScale(std::min(b.w/(float)sw,b.h/(float)sh));
 if(animatedBeam){sp->setScaleX(b.w/(float)sw);sp->setScaleY(b.h/(float)sh);}
 sp->setRotation(angle);sp->setFlippedX(flip);sp->setFlippedY(false);sp->setColor(cocos2d::Color3B::WHITE);sp->setOpacity(m_lgrpAlpha*255/32);
 sp->setGLProgram(cocos2d::GLProgramCache::getInstance()->getGLProgram(cocos2d::GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
 sp->setColor(cocos2d::Color3B((color>>16)&255,(color>>8)&255,color&255));
 AfterSpriting(sp);
}
float catapultAngle(int age,int release){
 return StarterCastleRig::angle(age,release);
}
void drawMountedPortraitGun(int img,const Box& b,const Box& hull,bool mirror,float recoil=0){
 if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 const auto dim=sprite[img]->getTexture()->getContentSizeInPixels();
 const int split=(int)(dim.height*.72f);const float z=std::min(b.w/dim.width,b.h/dim.height);
 // Draw the whole mount in front of the near deck; barrel recoil is independent.
 turretPart(img,0,split,(int)dim.width,(int)dim.height-split,
  {b.x,b.y-(int)(split*z),b.w,(int)((dim.height-split)*z)},0,.5f,.5f,mirror);
 Box barrel={b.x+(int)((mirror?1:-1)*recoil),b.y,b.w,(int)(split*z)};
 turretPart(img,0,0,(int)dim.width,split,barrel,0,.5f,.5f,mirror);
}
TurretAttack::Point cannonMuzzle(const Layout& l,int c,bool mirror,int age=-1,int barrel=1){
 const Box b=castleCannonBox(l);
 if(c==0){
  const auto p=StarterCastleRig::cup(age);const float z=portraitCastleZoom(l);
  const float left=siegeActive?DX-b.x-b.w:b.x;
  const float x=left+p.x*z;
  return {mirror?DX-x:x,b.y-p.y*z};
 }
 const float left=siegeActive?DX-b.x-b.w:b.x;
 float x=left+b.w*.94f,y=b.y-b.h*.33f;
 if(c==1){x=left+b.w*.91f;y=b.y-b.h*.12f;}
 if(c==2){x=left+b.w*.12f;y=b.y-b.h*.12f;}
 if(c==6){
  static const float portY[3]={.18f,.38f,.58f};
  x=left+b.w*.98f;y=b.y-b.h*portY[std::max(0,std::min(2,barrel))];
 }
 if(c==8){x=left+b.w*.95f;y=b.y-b.h*(barrel%2?.43f:.13f);}
 if(c==10){x=left+b.w*(barrel%2?.78f:.48f);y=b.y-b.h*.07f;}
 if(c>=17){
  const bool auxiliary=barrel<TurretAttack::burstCount(c)-1;
  x=left+b.w*(auxiliary?.46f:.96f);y=b.y-b.h*(auxiliary?(barrel%2?.75f:.58f):.35f);
 }
 if(TurretAttack::kind(c)==TurretAttack::Rapid){
  const float a=std::max(0,age)*.32f+barrel*1.04719755f;
  x=left+b.w*(.94f+.012f*std::cos(a));
  y=b.y-b.h*(.33f+.03f*std::sin(a));
 }
 return {mirror?DX-x:x,y};
}
void drawCastleCannon(const Layout& l,int c,bool mirror){
 (void)c;const int stage=std::max(0,std::min(18,siegeHullStage>=0?siegeHullStage:run.stage));
 const int img=PORTRAIT_TURRET_FIRST_IMG+stage;if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 const auto dim=sprite[img]->getTexture()->getContentSizeInPixels();const Box b=castleCannonBox(l);
 if(stage==0){
  using namespace StarterCastleRig;
  const bool firing=active&&turretFire.running()&&turretFire.castle==0;
  const int age=firing?turretFire.age:-1;const float z=portraitCastleZoom(l),angle=catapultAngle(age,turretFire.release);
  turretPart(img,0,0,StarterCastleRig::W,StarterCastleRig::H,b,0,.5f,.5f,mirror);
  const float loaded=loadAlpha(age,turretFire.release,turretFire.impact());
  if(loaded>0){const auto p=cannonMuzzle(l,0,mirror,age);const int alpha=m_lgrpAlpha;SetAlpha((int)(alpha*loaded));
   turretPart(img,RockX,RockY,RockW,RockH,{(int)(p.x-RockDrawW*z*.5f),(int)(p.y+RockDrawH*z*.5f),(int)(RockDrawW*z),(int)(RockDrawH*z)},mirror?-angle:angle);SetAlpha(alpha);}
  turretPart(img,StarterCastleRig::W,0,StarterCastleRig::W,StarterCastleRig::H,b,mirror?-angle:angle,mirror?1.f-PivotX/(float)StarterCastleRig::W:PivotX/(float)StarterCastleRig::W,1.f-PivotY/(float)StarterCastleRig::H,mirror);
  // The articulated carriage sits on the near deck plane and stays in front of its edge.
  return;
 }
 const float z=portraitCastleZoom(l);const Box hull=portraitCastleBox(l);
 drawMountedPortraitGun(img,b,hull,mirror,turretFire.running()?5*l.scale*turretFire.recoil():0);

}

Box lobbyStart(const Layout& l){const auto p=PortraitGame::lobby(DX,DY);const int w=(int)(360*l.scale);return {(DX-w)/2,p.startTop-(int)(10*l.scale),w,(int)(64*l.scale)};}

//원정 단추: 옛 "이어서" 줄의 오른쪽. 왼쪽은 행동력 게이지다.
//PVP 디버그(공성전) 버튼. 오른쪽 위, 나가기 자리 아래.
Box lobbyPvp(const Layout& l){const float s=l.scale;return {DX-(int)(80*s),l.ground+(int)(125*s),(int)(64*s),(int)(28*s)};}
struct CastleMap {
 float sx[4],sy[4],dx[4],dy[4];
 float x(float p) const {int k=p<sx[1]?0:p<sx[2]?1:2;return dx[k]+(p-sx[k])*(dx[k+1]-dx[k])/(sx[k+1]-sx[k]);}
 float y(float p) const {int k=p<sy[1]?0:p<sy[2]?1:2;return dy[k]+(p-sy[k])*(dy[k+1]-dy[k])/(sy[k+1]-sy[k]);}
};
CastleMap castleMap(const Layout& l,int c){
 const auto& f=MergeCastleArt::Chassis[c];const auto* holes=MergeCastleArt::Holes[c];
 int left=holes[0].x,top=holes[0].y,right=left,bottom=top;
 for(int i=0;i<5;++i){left=std::min(left,holes[i].x);top=std::min(top,holes[i].y);right=std::max(right,holes[i].x+holes[i].w);bottom=std::max(bottom,holes[i].y+holes[i].h);}
 // All castle skins occupy the first castle's fixed exterior bounds.
 // Board growth and artillery upgrades never resize the castle itself.
 const Box bounds=OriginalCastle::box(48,83,1000,1252);
 const float zx=bounds.w/(float)f.w,zy=bounds.h/(float)f.h;
 const float outerLeft=bounds.x;
 const float innerLeft=outerLeft+(left-f.x)*zx;
 const float innerRight=outerLeft+(right-f.x)*zx;
 return {{(float)f.x,(float)left,(float)right,(float)(f.x+f.w)},
         {(float)f.y,(float)top,(float)bottom,(float)(f.y+f.h)},
         {outerLeft,innerLeft,innerRight,outerLeft+bounds.w},
         {(float)bounds.y,bounds.y-(top-f.y)*zy,bounds.y-(bottom-f.y)*zy,(float)(bounds.y-bounds.h)}};
}
Box roomBox(const Layout& l,int room){
 const auto p=OriginalCastle::rooms()[room];
 return OriginalCastle::box((int)p[0].x,(int)p[0].y,(int)(p[1].x-p[0].x),(int)(p[2].y-p[0].y));
}
Box lobbyBottomNav();
bool lobbyDebugTouch(const Layout& l,float x,float y){
 if(!DebugControlsOpen() || !LobbyCastleDebugActive())return false;
 // Keep the dock, HUD, debug toolbar and ordinary lobby buttons accessible.
 if(y>=DY-28*_2X || (x<=288*_2X&&y<=DY-30*_2X&&y>=DY-54*_2X)
    ||LobbyCastleDebugHit(x,y)||lobbyBottomNav().has(x,y)||lobbyStart(l).has(x,y))return false;
 const int c=LobbyCastleDebugCastle();
 for(int room=0;room<4;++room)if(roomBox(l,room).has(x,y)){LobbyCastleDebugCycle(c,room);return true;}
 if(castleCannonBox(l).has(x,y)){LobbyCastleDebugCycle(c,-1);return true;}
 const float nativeY=OriginalCastle::H-(y-OriginalCastle::lift())/OriginalCastle::zoom();
 bool body=false;
 for(auto span:OriginalCastle::spans(OriginalCastle::outline(),nativeY)){
  const Box b=OriginalCastle::box((int)span.a,(int)nativeY,(int)(span.b-span.a)+1,1);
  if(x>=b.x&&x<=b.x+b.w){body=true;break;}
 }
 for(int wheel=0;wheel<2;++wheel){
  const Box b=OriginalCastle::box(wheel?867:27,1204,198,198);
  const float dx=(x-b.x-b.w*.5f)/(b.w*.5f),dy=(y-b.y+b.h*.5f)/(b.h*.5f);
  body=body||dx*dx+dy*dy<=1.f;
 }
 if(body){LobbyCastleDebugCommand(TOUCH_FUNC_LOBBY_CASTLE_NEXT);run.stage=LobbyCastleDebugCastle();}
 else StageBgDebugNextBackdrop();
 return true;
}
int drawnFrontRimParts=0;
Box portraitHabitatBounds(int castle,const Box& hull){
 if(castle==0)return {hull.x+(int)(15*hull.w/256.f),hull.y-(int)(85*hull.h/190.f),(int)(135*hull.w/256.f),(int)(72*hull.h/190.f)};
 return {hull.x+(int)(hull.w*.16f),hull.y-(int)(hull.h*.25f),(int)(hull.w*.62f),(int)(hull.h*.57f)};
}
int portraitHabitatFloors(int castle){return castle==0?1:std::max(2,std::min(5,PortraitCastleArt::Sizes[castle].h/180));}
void drawPortraitHabitatShell(int castle,const Box& hull){
 portraitImage(portraitHullImage(castle),hull);
 // Only the starter has a registered cutaway for the current exterior series.
 // Legacy rectangular rooms belong to the previous hulls, not these facades.
 if(castle!=0)return;
 if(starterInteriorReveal<=0)return;
 const Box b=portraitHabitatBounds(castle,hull);const int floors=portraitHabitatFloors(castle);
 const int cx=clipX,cy=clipY,cx2=clipX2,cy2=clipY2;
 clipX=std::max(cx,b.x);clipX2=std::min(cx2,b.x+b.w);clipY=std::min(cy,b.y-b.h+(int)(b.h*starterInteriorReveal));clipY2=std::max(cy2,b.y-b.h);
 if(clipX2>clipX&&clipY>clipY2){
  MemRect(b.x,b.y,b.w,b.h,0x191720);
  const int img=MERGE_REBUILD_ROOMS_IMG+std::min(9,castle/2);if(!sprite[img])LoadImg(img);
  if(sprite[img]){const auto sz=sprite[img]->getTexture()->getContentSizeInPixels();
   for(int floor=0;floor<floors;++floor){
    const auto f=MergeCastleTransition::RoomFrame(floor%4,castleRoomLevel(std::min(9,castle),floor%4),(int)sz.width,(int)sz.height);
    const int top=b.y-floor*b.h/floors,h=b.h/floors;const float z=std::min(b.w/(float)f.w,h/(float)f.h);
    MemRect(b.x,top,b.w,h,0x37333B);
    for(int beam=0;beam<5;++beam)MemRect(b.x+beam*b.w/4,top,2,h,0x49434A);
    MemRect(b.x,top,b.w,4,0x77583C);
    artCut(img,{f.x,f.y,f.w,f.h},{b.x+(int)((b.w-f.w*z)*.5f),top-(int)(h-f.h*z),(int)(f.w*z),(int)(f.h*z)});
    MemRect(b.x,top-h+2,b.w,2,0x77583C);
   }
  }
 }
 clipX=cx;clipY=cy;clipX2=cx2;clipY2=cy2;
}
void drawPortraitStarterHull(const Box& hull,bool mirror){
 const bool forced=lobbyDepartureAge<0&&portraitHullImage(0)==PORTRAIT_STARTER_INTERIOR_IMG;
 const float reveal=forced?1.f:std::max(0.f,std::min(1.f,starterInteriorReveal));
 if(reveal<=0||reveal>=1){portraitImage(reveal>=1?PORTRAIT_STARTER_INTERIOR_IMG:PORTRAIT_CASTLE_FIRST_IMG,hull,mirror);return;}
 const float z=hull.w/256.f;const int shown=(int)(72*reveal);
 auto piece=[&](int img,int x,int y,int w,int h){if(w<=0||h<=0)return;
  turretPart(img,x,y,w,h,{hull.x+(int)((mirror?256-x-w:x)*z),hull.y-(int)(y*z),(int)(w*z),(int)(h*z)},0,.5f,.5f,mirror);
 };
 piece(PORTRAIT_CASTLE_FIRST_IMG,0,0,256,85);piece(PORTRAIT_CASTLE_FIRST_IMG,0,157,256,33);
 piece(PORTRAIT_CASTLE_FIRST_IMG,0,85,15,72);piece(PORTRAIT_CASTLE_FIRST_IMG,150,85,106,72);
 piece(PORTRAIT_CASTLE_FIRST_IMG,15,85,135,72-shown);
 piece(PORTRAIT_STARTER_INTERIOR_IMG,15,157-shown,135,shown);
}
void drawCastleHull(const Layout& l,bool combat){
 (void)combat;const int c=std::max(0,std::min(18,siegeHullStage>=0?siegeHullStage:run.stage));
 castleWheelTravel=castleScrollSeconds*110.f*l.scale;
 const Box hull=portraitCastleBox(l);
 if(!nativeTitleBodyOnly&&!portraitAssembledSample())drawPortraitFarWheels(c,hull,portraitCastleZoom(l),castleWheelTravel,siegeActive);
 if(c==0&&portraitLobbyWorld()&&!titleCampOnly)drawPortraitStarterHull(hull,siegeActive);
 else if(portraitLobbyWorld()&&!titleCampOnly)drawPortraitHabitatShell(c,hull);
 else portraitImage(portraitHullImage(c),hull,siegeActive);
 if(portraitAssembledSample())return;
 if(!nativeTitleBodyOnly){
  const int img=PORTRAIT_WHEEL_FIRST_IMG+c;if(!sprite[img])LoadImg(img);
  if(sprite[img]){const auto sz=sprite[img]->getTexture()->getContentSizeInPixels();const float z=portraitCastleZoom(l);
   const int count=c<5?2:3;for(int i=0;i<count;++i){const float at=count==2?(i?PortraitCastleArt::FrontWheelAt(c):.17f):(.15f+.345f*i);
    RotateImage((int)sz.width,(int)sz.height,0,0,hull.x+(int)(hull.w*(siegeActive?1.f-at:at)),hull.y-hull.h-(int)(sz.height*z*.08f),false,(siegeActive?-1.f:1.f)*castleWheelAngle(sz.height*z*.5f),0,0,z,cocos2d::Vec2(.5f,.5f),sprite[img],img);}}
 }
 drawCastleCannon(l,c,siegeActive);
}

Box lobbyBottomNav(){const float s=DX/640.f;return {(int)(24*s),PortraitGame::lobby(DX,DY).navTop,DX-(int)(48*s),(int)(74*s)};}
void legacyLobbyIcon(int index,const Box& b){
 const int img=LEGACY_LOBBY_ICONS_IMG;if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 static const int bounds[5][4]={{19,34,103,100},{21,27,91,101},{21,24,107,106},{7,31,102,101},{17,29,105,100}};
 const auto& q=bounds[std::max(0,std::min(4,index))];const int w=q[2]-q[0],h=q[3]-q[1];
 const float z=std::min(b.w/(float)w,b.h/(float)h);
 artCut(img,{index*128+q[0],q[1],w,h},{b.x+(int)((b.w-w*z)*.5f),b.y-(int)((b.h-h*z)*.5f),(int)(w*z),(int)(h*z)});
}
void drawLobbyStartButton(const Box& b){
 const float s=DX/640.f;portraitSkin(3,b);
 portraitGlyph(3,{b.x+(int)(74*s),b.y-(int)(13*s),(int)(32*s),(int)(38*s)});
 label(u8"\uc804\ud22c \uc2dc\uc791",b.x+b.w/2+(int)(24*s),b.y-(int)(19*s),.78f,0xF6E9C8);
}
void drawLobbyBottomNav(float drop=0.f,bool interactive=true){
 if(!MergeRouletteLobbyDockVisible()&&lobbyDepartureAge<0)return;
 if(lobbyDepartureAge>=0)interactive=false;
 Box nav=lobbyBottomNav();nav.y-=(int)drop;const float s=DX/640.f;

 const int actions[5]={TOUCH_FUNC_SHOP,TOUCH_FUNC_COLLECTIONS,TOUCH_FUNC_LOBBY_ADVENTURE,TOUCH_FUNC_POPUP_CREWLIST,TOUCH_FUNC_POPUP_CASTLEMENU};
 int selected=2;if(popUpCnt>0){const int t=popUp[0].type;if(t==POPUPTYPE_CREWLIST||t==POPUPTYPE_CREWUPGRADE)selected=3;else if(t==POPUPTYPE_COLLECTIONS)selected=1;else if(t==POPUPTYPE_SHOPINFO||t==POPUPTYPE_EVENTSHOP)selected=0;else if(t==POPUPTYPE_CASTLEMENU)selected=4;}else if(curMenu==MENU_SHOP)selected=0;
 for(int i=0;i<5;++i){
  const Box base={nav.x+i*nav.w/5,nav.y,nav.w*(i+1)/5-nav.w*i/5-std::max(1,(int)(2*s)),nav.h};
  const float pop=LobbyNavPop(i);if(pop<=.001f)continue;
  const Box b={base.x+(int)(base.w*(1-pop)*.5f),base.y-(int)(base.h*(1-pop)*.5f),(int)(base.w*pop),(int)(base.h*pop)};
  portraitSkin(i==selected?3:2,b);
  const int iconWidth=(int)((nav.w*(i+1)/5-nav.w*i/5-22*s)*pop);
  legacyLobbyIcon(i,{b.x+(b.w-iconWidth)/2,b.y-(int)(6*s*pop),iconWidth,b.h-(int)(12*s*pop)});
  if(interactive)SetRectPoint(b.x,b.y,b.w,b.h,actions[i]);
 }
}

void drawLobbyControls(const Layout& l,float exit=0.f,bool interactive=false){
 const int drop=(int)(280*l.scale*exit);Box start=lobbyStart(l);
 start.y-=drop;
 // Keep the start action below the wheels, clear of all five room interiors.
 drawLobbyStartButton(start);
 drawLobbyBottomNav((float)drop,interactive);
 if(interactive){
  button(lobbyPvp(l),"PVP",nullptr,0x6B2D3F);
  for(int i=0;i<4;++i){const Box b=roomBox(l,i);SetRectPoint(b.x,b.y,b.w,b.h,TOUCH_FUNC_POPUP_CASTLEMENU);}
 }
}
