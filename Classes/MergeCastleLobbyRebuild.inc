int castleRoomLevel(int c,int room);
int castleMaterial(int c);
// Facilities remain independently upgradeable behind the chassis' alpha holes.
#include "MergeCastleOriginal.inc"
#include "MergeCastleMist.inc"
float entryElapsed=-1.f;
unsigned panicSeed=0;
int drawnFrontCover=-1;
Box drawnFrontCoverBounds={0,0,0,0};
Box drawnFrontInnerBounds={0,0,0,0};
float castleScrollSeconds=0.f,castleWheelTravel=0.f;
float castleWheelAngle(float radius){return std::fmod(castleWheelTravel/std::max(1.f,radius)*57.2957795f,360.f);}
bool entering(){return entryElapsed>=0&&entryElapsed<MergeCastleTransition::Duration;}
void drawWorld(const Layout& l,bool combat);
int castleRoomLevel(int c,int room){
 const int preview=LobbyCastleDebugFacilityLevel(c,room);
 return std::min(5,preview>=0?preview:(int)robin.castleProgress.rooms[c][room]);
}
int castleMaterial(int c) {
 static const int colors[10]={0x8B582D,0xC7AB77,0x7F94AF,0x366E70,0x333D56,0xA7CCC2,0x612D38,0xBACEDF,0x463251,0xC4D0D6};
 return colors[std::max(0,std::min(9,c))];
}
Box interiorBox(const Layout& l){
 const int w=std::min(DX-(int)(48*l.scale),l.board.w+(int)(64*l.scale));
 return {(DX-w)/2,l.board.y+(int)(26*l.scale),w,l.board.h+(int)(26*l.scale)};
}
//---- 대포가 놓인 자리 ----
//
//데크에 서는 사람들이 이 앞(오른쪽)에 선다. 그리는 쪽과 세우는 쪽이
//같은 상자를 봐야 사람이 포신에 겹치지 않는다.
Box castleCannonBox(const Layout& l){
 const int c=siegeHullStage>=0?siegeHullStage:std::max(0,std::min(9,run.stage));const float s=l.scale;
 const int lv=CastleVisualPartLevel(c,3);
 // Stage five rear flange is inset into the tower socket, not its outer rim.
 // Native hull coordinates: pivot centre for the catapult, rear collar for guns.
 // Follow the actual opening rather than an unrelated height above the deck.
 static const int mounts[10][2]={{286,256},{320,289},{342,278},{364,272},{336,272},
                               {350,270},{330,278},{380,282},{418,266},{352,294}};
 const Box mount=OriginalCastle::box(mounts[c][0],mounts[c][1],0,0);
 float width=(c==0?140.f+2.f*lv:94.f+5.f*c+2.f*lv)*s;
 float height=(c==0?90.f+2.f*lv:52.f+4.f*c+3.f*lv)*s;
 // The catapult is mounted by its pivot, not by a gun's rear flange.
 if(c==0)return {(int)(168*s-width*.85f),(int)(l.ground+80*s+height*.22f),(int)width,(int)height};
 const float fit=std::min(1.f,std::max(.1f,(mount.y-l.ground-3*s)/(height*.5f)));
 width*=fit;height*=fit;
 // Rear collar is seated in the tower socket; only the barrel protrudes.
 return {(int)(mount.x-width*(c==0?.85f:.12f)),
         (int)(mount.y+height*(c==0?.22f:.5f)),(int)width,(int)height};
}
// Draw only the articulated turret; the mounting strip and castle stay fixed.
void turretPart(int img,int sx,int sy,int sw,int sh,const Box& b,float angle=0,float ax=.5f,float ay=.5f,bool flip=false){
 if(!sprite[img])LoadImg(img);if(!sprite[img]||sw<=0||sh<=0)return;
 GetSpriteIndex(img);
 if(getSpriteIdx==totalRenderCnt){
  renderSprite[getSpriteIdx]=cocos2d::Sprite::createWithTexture(sprite[img]->getTexture());renderSprite[getSpriteIdx]->retain();renderSpriteIndex[getSpriteIdx]=getSpriteTexture;
  if(sameRenderSpriteCur[img]<3000)sameRenderSpriteArr[img][sameRenderSpriteCur[img]]=totalRenderCnt;
  ++sameRenderSpriteMax[img];++sameRenderSpriteCur[img];++totalRenderCnt;
 }
 auto* sp=renderSprite[getSpriteIdx];sp->setTexture(sprite[img]->getTexture());
 sp->setTextureRect(cocos2d::Rect(sx,sy,sw,sh));sp->setAnchorPoint({ax,ay});
 sp->setPosition({b.x+b.w*ax,b.y-b.h*(1-ay)});sp->setScaleX(b.w/(float)sw);sp->setScaleY(b.h/(float)sh);
 sp->setRotation(angle);sp->setFlippedX(flip);sp->setFlippedY(false);sp->setColor(cocos2d::Color3B::WHITE);sp->setOpacity(m_lgrpAlpha*255/32);
 sp->setGLProgram(cocos2d::GLProgramCache::getInstance()->getGLProgram(cocos2d::GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
 AfterSpriting(sp);
}
float catapultAngle(int age,int release){
 const float rest=0.f;
 if(age<0)return rest;
 if(age<release-5)return rest-8.f*std::sin(age/(float)std::max(1,release-5)*1.5707963f);
 if(age<release+3)return rest-8.f+113.f*(age-release+5)/8.f;
 return rest+105.f*std::max(0.f,1.f-(age-release-3)/20.f);
}
TurretAttack::Point cannonMuzzle(const Layout& l,int c,bool mirror,int age=-1,int barrel=1){
 const Box b=castleCannonBox(l);
 float x=b.x+b.w*(c==0?.16f:.92f),y=b.y-b.h*(c==0?.70f:.5f);
 if(c==2){
  static const float portY[3]={.20f,.50f,.80f};
  x=b.x+b.w*.98f;y=b.y-b.h*portY[std::max(0,std::min(2,barrel))];
 }
 if(c==3){
  const float a=std::max(0,age)*.32f+barrel*1.04719755f;
  x=b.x+b.w*(.885f+.065f*std::cos(a));
  y=b.y-b.h*(.50f+.23f*std::sin(a));
 }
 if(c==0){
  const float px=b.x+b.w*.85f,py=b.y-b.h*.22f;
  const float a=-catapultAngle(age,turretFire.release)*.0174532925f,dx=x-px,dy=y-py;
  x=px+dx*std::cos(a)-dy*std::sin(a);y=py+dx*std::sin(a)+dy*std::cos(a);
 }
 return {mirror?DX-x:x,y};
}
void drawCastleCannon(const Layout& l,int c,bool mirror){
 const bool firing=turretFire.running()&&turretFire.castle==c;
 const int level=CastleVisualPartLevel(c,3);
 const bool graded=c>0&&level>0;
 const int img=graded?CANNON_UPGRADE_ATLAS_IMG:(c==0&&firing&&turretFire.age>=turretFire.release?CASTLE_MIST_EMPTY_ARM_IMG:CASTLE_MIST_TURRET_FIRST_IMG+c);
 if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 const auto dim=sprite[img]->getTexture()->getContentSizeInPixels();
 const auto grade=MountedCannons::Get(c,level);
 Box b=castleCannonBox(l);if(mirror)b.x=DX-b.x-b.w;
 if(c==0){
  if(level>0){const int plate=CANNON_UPGRADE_ATLAS_IMG;const int sh=Max(1,grade.h/4);
   Box foot={b.x+(int)(b.w*.45f),b.y-(int)(b.h*.70f),(int)(b.w*.65f),(int)(b.h*.30f)};
   if(!sprite[plate])LoadImg(plate);
   if(sprite[plate])DrawImageScale(grade.w,sh,grade.x,grade.y+grade.h-sh,foot.x,foot.y,mirror,0,0,0,0,foot.w/(float)grade.w,foot.h/(float)sh,sprite[plate],plate);}
  turretPart(img,0,0,(int)dim.width,(int)dim.height,b,
   catapultAngle(firing?turretFire.age:-1,firing?turretFire.release:18)*(mirror?-1:1),mirror?.15f:.85f,.78f,mirror);
 }else{
  if(firing)b.x+=(int)((mirror?1:-1)*8*l.scale*turretFire.recoil());
  if(graded)DrawImageScale(grade.w,grade.h,grade.x,grade.y,b.x,b.y,mirror,0,0,0,0,b.w/(float)grade.w,b.h/(float)grade.h,sprite[img],img);
  else turretPart(img,0,0,(int)dim.width,(int)dim.height,b,0,.5f,.5f,mirror);
  if(c==3&&firing){
   // Project the rotating front plate onto the gun's narrow elliptical face.
   // The housing stays seated; only the six barrel mouths orbit the hub.
   const float cx=b.x+b.w*(mirror?.115f:.885f),cy=b.y-b.h*.50f;
   auto ellipse=[&](float x,float y,float rx,float ry,int color){
    const int radius=std::max(1,(int)std::ceil(ry));
    for(int row=-radius;row<=radius;++row){
     const float q=row/(float)radius;
     const int half=std::max(1,(int)(rx*std::sqrt(std::max(0.f,1-q*q))));
     mergeRect((int)x-half,(int)y+row,half*2,1,color);
    }
   };
   ellipse(cx,cy,b.w*.097f,b.h*.36f,0xA87C43);
   ellipse(cx,cy,b.w*.084f,b.h*.33f,0x493B27);
   for(int port=0;port<6;++port){
    const float a=turretFire.age*.32f+port*1.04719755f;
    const float x=cx+(mirror?-1:1)*b.w*.065f*std::cos(a),y=cy-b.h*.23f*std::sin(a);
    ellipse(x,y,b.w*.029f,b.h*.10f,0xBD955A);
    ellipse(x,y,b.w*.021f,b.h*.073f,0x171E1C);
   }
   ellipse(cx,cy,b.w*.024f,b.h*.08f,0xC39B60);
  }
 }
}
Box lobbyStart(const Layout& l){return OriginalCastle::box(294,1037,506,150);}
Box lobbyContinue(const Layout& l){return OriginalCastle::box(411,1196,274,52);}
Box lobbyManage(const Layout& l){return OriginalCastle::box(404,1005,276,49);}
//PVP 디버그(공성전) 버튼. 오른쪽 위, 나가기 자리 아래.
Box lobbyPvp(const Layout& l){const float s=l.scale;return {(int)(DX-152*s),(int)(118*s),(int)(144*s),(int)(32*s)};}
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
    ||LobbyCastleDebugHit(x,y)||lobbyBottomNav().has(x,y)||lobbyManage(l).has(x,y))return false;
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
//---- 방 안의 식솔 ----
//
//[왜 전부인가]
//방마다 한 사람만 서 있으면, 동료를 몇을 모았든 성은 늘 똑같이 비어
//보인다. 모은 것이 보이는 자리가 여기뿐이므로 가진 동료를 전부 세운다.
//
//[나누는 방법]
//다섯 방에 번갈아 넣는다(0,5,10번째가 첫 방). 역할·★ 순으로 모은
//명단을 그대로 돌리므로 한 방에 같은 역할만 몰리지 않는다.
//
//[좁으면 같이 작아진다]
//사람이 늘면 방을 넘친다. 방 하나의 가로폭에 맞춰 그 방 사람들만
//한꺼번에 줄인다 - 한 명씩 줄이면 같은 방 안에서 키가 들쭉날쭉해진다.
//
//[움직임]
//저마다 다른 박자로 제자리 주변을 오간다. 가는 쪽을 보고(dir), 걷는
//동안 쉬는 모션을 돌린다. 방 밖으로는 안 나간다 - 방 상자로 잘린다.
void drawRoomResidents(const Layout& l){
 int crews[64],n=0;
 for(int role=0;role<Roles;++role)for(int star=1;star<=MaxLevel;++star)
  for(int k=0;k<roster.count[role][star]&&n<64;++k){
   const int id=roster.crew[role][star][k];
   // Deployed companions leave the castle rooms for the battle deck.
   bool deployed=false;
   if(active)for(int index=0;index<(int)run.board.size();++index){
    const auto& block=run.board[index];
    if(gridBlockLanded(index)&&block.family<Roles&&block.crew==id){deployed=true;break;}
   }
   if(deployed)continue;
   bool dup=false;for(int j=0;j<n;++j)if(crews[j]==id)dup=true;
   if(!dup)crews[n++]=id;
  }
 if(n==0&&active)return;
 if(n==0){
  //아직 한 명도 없다. 예전처럼 역할 대표를 한 방에 하나씩 세워 둔다.
  for(int i=0;i<4;++i){
   const Box b=roomBox(l,i);const int h=(int)(.84f*std::min(72*l.scale,b.h*.84f)),w=(int)(h*.85f);
   SetSectionClip(b.x,b.y,b.w,b.h,false);
   icon(i%Roles,{b.x+(int)(b.w*.70f)-w/2,b.y-b.h+(int)(9*l.scale)+h,w,h},1.f,false,1,-1);
   UnSectionClip(false);
  }
  return;
 }
 for(int i=0;i<4;++i){
  const Box b=roomBox(l,i);
  int mine[64],cnt=0;
  for(int k=i;k<n;k+=4)mine[cnt++]=crews[k];
  if(cnt==0)continue;

  //---- 크기부터 지킨다 ----
  //
  //전에는 사람이 늘면 다 들어갈 때까지 키를 줄였다. 열 몇이 한 방에
  //들면 점처럼 작아져서 누가 있는지 알아볼 수가 없었다.
  //
  //알아볼 수 있는 크기가 먼저다. 한 줄에 다 못 서면 **뒷줄을 만든다** -
  //뒷줄은 조금 위에, 조금 작게 서서 방이 깊어 보인다(최대 3줄).
  //그래도 넘치면 간격만 좁혀 어깨를 겹친다.
  //.70 → .84: 방 안 사람을 20% 키운다(2026-11-16). 뒷줄은 그대로 12% 씩 줄어든다.
  const int h0=(int)(.84f*std::min(72*l.scale,b.h*.84f));
  const int span=std::max(1,(int)(b.w*.84f));
  const int left=b.x+(b.w-span)/2;
  const int floorY=b.y-b.h+(int)(9*l.scale);
  const int lane=std::max(1,(int)(h0*.56f));         //한 사람이 쓰는 가로
  const int perRank=std::max(1,span/lane);
  const int ranks=std::max(1,std::min(3,(cnt+perRank-1)/perRank));

  SetSectionClip(b.x,b.y,b.w,b.h,false);
  //뒷줄부터 그린다 - 앞줄이 뒷줄을 가려야 깊이가 산다.
  for(int r=ranks-1;r>=0;--r){
   int first=cnt*r/ranks,last=cnt*(r+1)/ranks,mates=last-first;
   if(mates<=0)continue;
   const float shrink=1.f-r*.12f;
   const int h=std::max((int)(28*.84f*l.scale),(int)(h0*shrink));
   const int w=std::max(1,(int)(h*.85f));
   const int lift=(int)(r*h0*.22f);
   for(int k=0;k<mates;++k){
    const int idx=first+k;
    //걷는 그림이 없는 사람은 제자리에 선다. 선 그림을 옆으로 옮기면
    //걷는 게 아니라 미끄러지는 것으로 보인다. 걷는지는 cmf 이동표가
    //정한다(crewWalkMotion) - 대기 장수로는 64명이 다 통과해 버린다.
    //제자리인 사람도 대기 그림이 여러 장이면 그 자리에서 숨을 쉰다.
    const int walkMotion=crewWalkMotion(mine[idx],frame/6+idx*3);
    const bool walks=walkMotion>=0;
    const int motion=walks?walkMotion:crewIdleMotion(mine[idx],frame/8+idx);
    const float t=frame*(.010f+(idx%3)*.004f)+(i*7+idx*3)*.9f;
    const int home=mates==1?left+span/2:left+k*span/(mates-1);
    const int cx=walks?home+(int)(std::sin(t)*h*.26f):home;
    crewArt(mine[idx],{cx-w/2,floorY+lift+h,w,h},1.f,0,motion,
     walks&&std::cos(t)<0.f?LEFT:RIGHT);
    if(entering()&&entryElapsed<MergeCastleTransition::CoverEnd){
     const unsigned hash=panicSeed+(unsigned)mine[idx]*2654435761u;
     const float delay=(hash%18)/100.f;
     if(entryElapsed>=delay){
      const int icons[3]={EMOTICON_SURPRISE,EMOTICON_QUESTION,EMOTICON_SWEAT};
      DrawEmoticon(icons[hash%3],0,4+(int)((entryElapsed-delay)*24),cx,
       std::min(b.y-(int)(8*l.scale),floorY+lift+h),.65f*l.scale);
     }
    }
   }
  }
  UnSectionClip(false);
 }
}
Box battleFrontOuter(const Layout& l,int c){
 Box b=OriginalCastle::box(96,430,912,875);
 if(siegeActive)b.x=DX-b.x-b.w;
 return b;
}
int drawnFrontRimParts=0;
void measureFrontInner(const Layout& l,int c){
 drawnFrontInnerBounds=OriginalCastle::box(196,569,706,406);
 if(siegeActive)drawnFrontInnerBounds.x=DX-drawnFrontInnerBounds.x-drawnFrontInnerBounds.w;
}
void drawBattleCover(const Layout& l){
 drawnFrontCover=-1;drawnFrontRimParts=0;
 const float progress=entryElapsed<0?1.f:MergeCastleTransition::CoverProgress(entryElapsed);
 if(progress<=0)return;
 const int c=siegeHullStage>=0?siegeHullStage:std::max(0,std::min(9,run.stage));
 const Box outer=battleFrontOuter(l,c);drawnFrontCover=MistCastle::image(c,8);drawnFrontCoverBounds=outer;
 Box moving=OriginalCastle::box(96,430,912,875);moving.y+=(int)((1-progress)*moving.h);
 SetSectionClip(outer.x,outer.y,outer.w,outer.h,false);
 MistCastle::part(c,8,moving,siegeActive);
 UnSectionClip(false);measureFrontInner(l,c);
}
void drawDeckSurface(const Layout& l,int c,bool mirror){
 const int img=BATTLE_DECK_SURFACE_IMG;
 if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 sprite[img]->getTexture()->setAliasTexParameters();
 const auto dim=sprite[img]->getTexture()->getContentSizeInPixels();
 const int row=(int)dim.height/10;
 const Box span=OriginalCastle::box(380,0,c==8?610:650,0);
 // Leave visible floor both behind and in front of the characters' feet
 // (ground + 8), including the green/brass fourth castle.
 // The sixth castle's high stone fascia needs a deeper top plane to read
 // as a platform rather than another horizontal wall trim.
 const float depth=c==8?58.f:c>=5?52.f:42.f;
 // The deck's front edge seats into the same registered cap as the hull.
 // Its transparent bevel must overlap that cap, never hover above it.
 const int front=OriginalCastle::box(380,369,0,0).y-std::max(1,(int)(2*l.scale));
 const int height=std::max(1,(int)(depth*l.scale));
 const Box plane={span.x,front+height,span.w,height};
 DrawImageScale((int)dim.width,row,0,c*row,mirror?DX-plane.x-plane.w:plane.x,plane.y,
  mirror,0,0,0,0,plane.w/dim.width,plane.h/(float)row,sprite[img],img);
}
void drawCastleHull(const Layout& l,bool combat){
 const int c=siegeHullStage>=0?siegeHullStage:std::max(0,std::min(9,run.stage));
 const bool debugClosed=!combat&&LobbyCastleDebugActive()&&!LobbyCastleDebugInterior();
 const bool closed=(debugClosed||(combat&&active&&(entryElapsed<0||entryElapsed>=MergeCastleTransition::CoverEnd)))&&!(review&&std::getenv("CS_MERGE_FRONT_REFERENCE"));
 const bool mirror=siegeActive;
 MistCastle::hull(c,closed,castleWheelAngle(92*OriginalCastle::zoom()),mirror,!combat);
 drawDeckSurface(l,c,mirror);
 drawCastleCannon(l,c,mirror);
 if(!closed){
  drawRoomResidents(l);
 }
 if(debugClosed)drawBattleCover(l);
}
Box lobbyBottomNav(){
 const int margin=std::max(1,(int)(8*DX/640.f));
 const int w=DX-2*margin,h=(int)(w*163.f/941.f);
 return {margin,margin+h,w,h};
}
void drawLobbyBottomNav(float drop=0.f,bool interactive=true){
 Box nav=lobbyBottomNav();nav.y-=(int)drop;
 const float z=nav.w/941.f;
 const float originX=nav.x-76*z,originY=nav.y-170*z;

 int selected=2;
 if(popUpCnt>0){const int type=popUp[popUpCnt-1].type;
  if(type==POPUPTYPE_SHOPINFO||type==POPUPTYPE_EVENTSHOP)selected=0;
  else if(type==POPUPTYPE_COLLECTIONS)selected=1;
  else if(type==POPUPTYPE_CREWLIST||type==POPUPTYPE_CREWUPGRADE)selected=3;
  else if(type==POPUPTYPE_CASTLEMENU)selected=4;
 }else if(curMenu==MENU_SHOP)selected=0;
 const char* names[5]={"상점","영웅","모험","동료","성"};
 const int cx[5]={190,380,552,740,915};
 const int actions[5]={TOUCH_FUNC_SHOP,TOUCH_FUNC_COLLECTIONS,TOUCH_FUNC_LOBBY_ADVENTURE,TOUCH_FUNC_POPUP_CREWLIST,TOUCH_FUNC_POPUP_CASTLEMENU};
 OriginalCastle::draw(5,0,0,z,originX,originY,selected);
 for(int i=0;i<5;++i){
  const int x=(int)(originX+(cx[i]-62)*z),y=(int)(originY+63*z);
  MemRect(x,y,(int)(124*z),(int)(42*z),i==selected?0x1748A0:0x633015);
  if(i==selected){
   const int left=nav.x+nav.w*i/5,right=nav.x+nav.w*(i+1)/5;
   MemRectFrameThick(left+2,nav.y-12*z,right-left-4,nav.h-16*z,0xFFCE55,Max(1,(int)(2*z)));
  }
  label(names[i],(int)(originX+cx[i]*z),y-(int)(4*DX/640.f),.67f*z/OriginalCastle::zoom(),i==selected?0xFFFFFF:0xFFE7B9);
  if(interactive)SetRectPoint(nav.x+nav.w*i/5,nav.y,nav.w*(i+1)/5-nav.w*i/5,nav.h,actions[i]);
 }
}
void drawLobbyControls(const Layout& l,float exit=0.f,bool interactive=false){
 const int drop=(int)(280*l.scale*exit);Box start=lobbyStart(l),keep=lobbyContinue(l),manage=lobbyManage(l);
 start.y-=drop;keep.y-=drop;manage.y-=drop;
 // All lobby buttons share the original canvas transform and aspect ratio.
 OriginalCastle::draw(2,(float)drop);OriginalCastle::draw(3,(float)drop);
 OriginalCastle::draw(4,(float)drop);
 drawLobbyBottomNav((float)drop,interactive);
 if(interactive){
  button(lobbyPvp(l),"PVP 디버그","공성전",0x6B2D3F);
  SetRectPoint(manage.x,manage.y,manage.w,manage.h,TOUCH_FUNC_POPUP_CASTLEMENU);
  for(int i=0;i<4;++i){const Box b=roomBox(l,i);SetRectPoint(b.x,b.y,b.w,b.h,TOUCH_FUNC_POPUP_CASTLEMENU);}
 }
}
