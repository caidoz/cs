// Facilities remain independently upgradeable behind the chassis' alpha holes.
#include "MergeCastleOriginal.inc"
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
 // Growth favors the bore, not barrel length. Even castle 10 at +5 remains
 // inside the same 140px mounting zone, leaving the actors' deck clear.
 const float width=(110.f+c+4.f*lv)*s;
 const float height=(78.f+4.f*c+10.f*lv)*s;
 return {(int)(190*s),(int)(l.ground+24*s+height),(int)width,(int)height};
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
 if(age<0)return 0;
 if(age<release-5)return -12.f*std::sin(age/(float)(release-5)*1.5707963f);
 if(age<release+3)return -12.f+60.f*(age-release+5)/8.f;
 return 48.f*std::max(0.f,1.f-(age-release-3)/20.f);
}
TurretAttack::Point cannonMuzzle(const Layout& l,int c,bool mirror,int age=-1){
 const auto& f=MountedCannons::Get(c,CastleVisualPartLevel(c,3));const Box b=castleCannonBox(l);
 float x=b.x+b.w*f.mx/(float)f.w,y=b.y-b.h*f.my/(float)f.h;
 if(c==0&&age>=0){
  const float px=b.x+b.w*.55f,py=b.y-b.h*.40f;
  const float a=-catapultAngle(age,turretFire.release)*.0174532925f,dx=x-px,dy=y-py;
  x=px+dx*std::cos(a)-dy*std::sin(a);y=py+dx*std::sin(a)+dy*std::cos(a);
 }
 return {mirror?DX-x:x,y};
}
void drawCastleCannon(const Layout& l,int c,bool mirror){
 const auto& f=MountedCannons::Get(c,CastleVisualPartLevel(c,3));
 Box b=castleCannonBox(l);if(mirror)b.x=DX-b.x-b.w;
 const int strip=std::max(1,(int)(f.h*.18f)),rim=std::max(1,(int)(6*l.scale));
 artCutFlip(CANNON_UPGRADE_ATLAS_IMG,{f.x,f.y+f.h-strip,f.w,strip},
  {b.x-rim,b.y-b.h+(int)(5*l.scale),b.w+2*rim,(int)(42*l.scale)},mirror);
 const bool firing=turretFire.running()&&turretFire.castle==c;
 if(!firing){artCutFlip(CANNON_UPGRADE_ATLAS_IMG,{f.x,f.y,f.w,f.h},b,mirror);return;}
 // Base never recoils. Upper assembly snaps back once for each fired round.
 const int bodyH=f.h-strip,bodyPixels=(int)(b.h*bodyH/(float)f.h);
 Box body={b.x,b.y,b.w,bodyPixels};
 artCutFlip(CANNON_UPGRADE_ATLAS_IMG,{f.x,f.y+bodyH,f.w,strip},
  {b.x,b.y-bodyPixels,b.w,b.h-bodyPixels},mirror);
 if(c==0){
  turretPart(CANNON_UPGRADE_ATLAS_IMG,f.x,f.y,f.w,bodyH,body,
   catapultAngle(turretFire.age,turretFire.release)*(mirror?-1:1),mirror?.45f:.55f,1.f-.40f*f.h/bodyH,mirror);
 }else{
  body.x+=(int)((mirror?1:-1)*8*l.scale*turretFire.recoil());
  body.h-=std::max(0,(int)(3*l.scale*turretFire.recoil()));
  turretPart(CANNON_UPGRADE_ATLAS_IMG,f.x,f.y,f.w,bodyH,body,0,.5f,.5f,mirror);
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
 if((siegeHullStage>=0?siegeHullStage:run.stage)==0){const auto p=OriginalCastle::rooms()[room];return OriginalCastle::box((int)p[0].x,(int)p[0].y,(int)(p[1].x-p[0].x),(int)(p[2].y-p[0].y));}
 const int c=siegeHullStage>=0?siegeHullStage:std::max(0,std::min(9,run.stage));const auto m=castleMap(l,c);const auto& f=MergeCastleArt::Holes[c][room];
 int x=(int)std::floor(m.x(f.x)),right=(int)std::ceil(m.x(f.x+f.w));
 int top=(int)std::ceil(m.y(f.y)),bottom=(int)std::floor(m.y(f.y+f.h));
 return {x,top,right-x,top-bottom};
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
  for(int i=0;i<5;++i){
   const Box b=roomBox(l,i);const int h=(int)std::min(72*l.scale,b.h*.84f),w=(int)(h*.85f);
   SetSectionClip(b.x,b.y,b.w,b.h,false);
   icon(i%Roles,{b.x+(int)(b.w*.70f)-w/2,b.y-b.h+(int)(9*l.scale)+h,w,h},1.f,false,1,-1);
   UnSectionClip(false);
  }
  return;
 }
 for(int i=0;i<5;++i){
  const Box b=roomBox(l,i);
  int mine[64],cnt=0;
  for(int k=i;k<n;k+=5)mine[cnt++]=crews[k];
  if(cnt==0)continue;

  //---- 크기부터 지킨다 ----
  //
  //전에는 사람이 늘면 다 들어갈 때까지 키를 줄였다. 열 몇이 한 방에
  //들면 점처럼 작아져서 누가 있는지 알아볼 수가 없었다.
  //
  //알아볼 수 있는 크기가 먼저다. 한 줄에 다 못 서면 **뒷줄을 만든다** -
  //뒷줄은 조금 위에, 조금 작게 서서 방이 깊어 보인다(최대 3줄).
  //그래도 넘치면 간격만 좁혀 어깨를 겹친다.
  const int h0=(int)std::min(72*l.scale,b.h*.84f);
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
   const int h=std::max((int)(28*l.scale),(int)(h0*shrink));
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
 Box b=OriginalCastle::box(48,430,1000,610);
 if(siegeActive)b.x=DX-b.x-b.w;
 return b;
}
int drawnFrontRimParts=0;
void measureFrontInner(const Layout& l,int c){
 if(c==0){drawnFrontInnerBounds=OriginalCastle::box(196,569,706,406);return;}
 const auto m=castleMap(l,c);int left=2000,right=0,top=2000,bottom=0;
 for(const auto& h:MergeCastleArt::Holes[c]){left=std::min(left,h.x);right=std::max(right,h.x+h.w);top=std::min(top,h.y);bottom=std::max(bottom,h.y+h.h);}
 const int x=(int)std::floor(m.x(left)),r=(int)std::ceil(m.x(right));
 const int y=(int)std::ceil(m.y(top)),floor=(int)std::floor(m.y(bottom));
 drawnFrontInnerBounds={siegeActive?DX-r:x,y,r-x,y-floor};
}
void drawBattleCover(const Layout& l){
 drawnFrontCover=-1;drawnFrontRimParts=0;
 const float progress=entryElapsed<0?1.f:MergeCastleTransition::CoverProgress(entryElapsed);
 if(progress<=0)return;
 const int c=siegeHullStage>=0?siegeHullStage:std::max(0,std::min(9,run.stage));
 const int img=MergeCastleFronts::Image(c);
 if(!sprite[img])LoadImg(img);
 if(!sprite[img])return;
 const Box outer=battleFrontOuter(l,c);const auto& source=MergeCastleFronts::Frames[c];
 drawnFrontCover=img;drawnFrontCoverBounds=outer;
 SetSectionClip(outer.x,outer.y,outer.w,outer.h,false);
 const bool reference=review&&std::getenv("CS_MERGE_FRONT_REFERENCE");
 if(!reference){
  // The facade's alpha silhouette has gaps between its projecting beams.
  // A closed wall needs an opaque substrate after the room mesh is hidden.
  const int inset=std::max(1,(int)(20*l.scale));
  const int top=outer.y+(int)((1-progress)*outer.h);
  MemRect(outer.x+inset,top,outer.w-2*inset,outer.h,castleMaterial(c));
  DrawImageScale(source.w,source.h,source.x,source.y,outer.x,outer.y+(int)((1-progress)*outer.h),siegeActive,0,0,0,0,
      outer.w/(float)source.w,outer.h/(float)source.h,sprite[img],img);
 }
 UnSectionClip(false);
 measureFrontInner(l,c);
}
void drawCastleHull(const Layout& l,bool combat){
 const int c=siegeHullStage>=0?siegeHullStage:std::max(0,std::min(9,run.stage));const auto map=castleMap(l,c);const float s=l.scale;
 const bool debugClosed=!combat&&LobbyCastleDebugActive()&&!LobbyCastleDebugInterior();
 const bool closed=(debugClosed||(combat&&active&&(entryElapsed<0||entryElapsed>=MergeCastleTransition::CoverEnd)))&&!(review&&std::getenv("CS_MERGE_FRONT_REFERENCE"));
 if(c==0){
  const int img=MERGE_REBUILD_ROOMS_IMG;if(!sprite[img])LoadImg(img);
  if(sprite[img]&&!closed)for(int i=0;i<5;++i){
   Box b=roomBox(l,i);const auto size=sprite[img]->getTexture()->getContentSizeInPixels();
   const auto f=MergeCastleTransition::RoomFrame(i,castleRoomLevel(0,i),(int)size.width,(int)size.height);
   const float z=std::max(b.w/(float)f.w,b.h/(float)f.h);const int sw=std::min(f.w,(int)std::ceil(b.w/z)),sh=std::min(f.h,(int)std::ceil(b.h/z));
   SetSectionClip(b.x,b.y,b.w,b.h,false);
   DrawImageScale(sw,sh,f.x+(f.w-sw)/2,f.y+f.h-sh,b.x,b.y,false,0,0,0,0,z,z,sprite[img],img);UnSectionClip(false);
  }
  OriginalCastle::draw(10);OriginalCastle::draw(11);OriginalCastle::draw(12);
  OriginalCastle::wood(65,1204,160,131);OriginalCastle::wood(867,1202,162,133);
  OriginalCastle::draw(closed?14:0);OriginalCastle::draw(1);
  const float wheelAngle=castleWheelAngle(99*OriginalCastle::zoom());
  OriginalCastle::wheel(0,wheelAngle);OriginalCastle::wheel(1,wheelAngle);
  drawCastleCannon(l,c,false);
  const int xx[5]={270,505,748,300,660},yy[5]={535,535,535,756,756},ww[5]={94,100,96,106,110};
  const char* titles[5]={"식량 재배","장비 공방","식음료","도서·문화","특화 시설"};
  if(!active||entryElapsed<MergeCastleTransition::CoverEnd)for(int i=0;i<5;++i){Box t=OriginalCastle::box(xx[i]+5,yy[i]+5,ww[i]-10,22);MemRect(t.x,t.y,t.w,t.h,0xD9AF70);label(titles[i],t.x+t.w/2,t.y,.42f,0x23190E);}
  if(!closed)drawRoomResidents(l);
  if(debugClosed)drawBattleCover(l);
  return;
 }
 //---- 공성전: 적의 성은 거울로 선다 ----
 //
 //쳐들어간 성이라 방향이 반대다. 포탑·대포가 오른쪽으로 가고 성주가 거기
 //선다. 방 그림·차체·대포를 x 축으로 뒤집어 그린다. 바퀴는 좌우 대칭이라
 //그대로. 판(칸·블록)은 내 퍼즐이므로 뒤집지 않는다.
 const bool mirror=siegeActive;
 int img=MERGE_REBUILD_ROOMS_IMG+c;if(!sprite[img])LoadImg(img);
 if(sprite[img]&&!closed){
  const auto size=sprite[img]->getTexture()->getContentSizeInPixels();
  for(int i=0;i<5;++i){
   const int lv=castleRoomLevel(c,i);
   const auto f=MergeCastleTransition::RoomFrame(i,lv,(int)size.width,(int)size.height);
   Box b=roomBox(l,i);b.x-=2;b.y+=2;b.w+=4;b.h+=4;
   if(mirror)b.x=DX-b.x-b.w;
   const float z=std::max(b.w/(float)f.w,b.h/(float)f.h);
   const int sw=std::min(f.w,(int)std::ceil(b.w/z)),sh=std::min(f.h,(int)std::ceil(b.h/z));
   SetSectionClip(b.x,b.y,b.w,b.h,false);
   DrawImageScale(sw,sh,f.x+(f.w-sw)/2,f.y+f.h-sh,b.x,b.y,mirror,0,0,0,0,z,z,sprite[img],img);
   UnSectionClip(false);
  }
 }
 const auto& chassis=MergeCastleArt::Chassis[c];
 const int chassisImg=MERGE_REBUILD_CHASSIS_IMG+c;if(!sprite[chassisImg])LoadImg(chassisImg);
 const float chassisZoom=(map.dx[3]-map.dx[0])/chassis.w;
 const float chassisZoomY=(map.dy[0]-map.dy[3])/chassis.h;
 const auto chassisDraw=[&](){if(sprite[chassisImg])DrawImageScale(chassis.w,chassis.h,chassis.x,chassis.y,(int)(mirror?DX-map.dx[3]:map.dx[0]),(int)map.dy[0],mirror,0,0,0,0,chassisZoom,chassisZoomY,sprite[chassisImg],chassisImg);};
 if(closed){
  const Box covered=battleFrontOuter(l,c);
  SetSectionClip(0,DY,DX,std::max(0,DY-covered.y),false);chassisDraw();UnSectionClip(false);
  const int under=covered.y-covered.h;
  if(under>0){SetSectionClip(0,under,DX,under,false);chassisDraw();UnSectionClip(false);}
 }else chassisDraw();
 const int wheelLv=CastleVisualPartLevel(c,4);
 const auto& wheel=MergeCastleArt::Parts[c][1][wheelLv];const int partImg=MERGE_REBUILD_PARTS_IMG+c;
 if(!sprite[partImg])LoadImg(partImg);
 if(sprite[partImg])for(int i=0;i<2;++i){
  const int cx=(int)(i?DX-65*s:65*s),cy=(int)(139*s+castleSceneLift());
  RotateImage(wheel.w,wheel.h,wheel.x,wheel.y,cx,cy,false,castleWheelAngle(43*s),0,0,86*s/std::max(wheel.w,wheel.h),cocos2d::Vec2(.5f,.5f),sprite[partImg],partImg);
 }
 drawCastleCannon(l,c,mirror);
 if(!closed)drawRoomResidents(l);
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
  for(int i=0;i<5;++i){const Box b=roomBox(l,i);SetRectPoint(b.x,b.y,b.w,b.h,TOUCH_FUNC_POPUP_CASTLEMENU);}
 }
}
