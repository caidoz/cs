// Facilities remain independently upgradeable behind the chassis' alpha holes.
#include "MergeCastleOriginal.inc"
float entryElapsed=-1.f;
float castleScrollSeconds=0.f,castleWheelTravel=0.f;
float castleWheelAngle(float radius){return std::fmod(castleWheelTravel/std::max(1.f,radius)*57.2957795f,360.f);}
bool entering(){return entryElapsed>=0&&entryElapsed<MergeCastleTransition::Duration;}
void drawWorld(const Layout& l,bool combat);
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
 const int c=std::max(0,std::min(9,run.stage));const float s=l.scale;
 const int lv=std::min(5,(int)robin.castleProgress.parts[c][3]);
 const auto& cannon=MergeCastleArt::Parts[c][0][lv];
 const float z=std::min(95*s/cannon.w,77*s/cannon.h);
 return {(int)(246*s),(int)(l.ground+cannon.h*z),(int)(cannon.w*z),(int)(cannon.h*z)};
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
 const Box room=interiorBox(l);const float s=l.scale;
 // One uniform transform per authored castle. Growing boards may crop the
 // castle sides; they never squeeze pillars or stretch room furniture.
 const float lift=castleSceneLift();
 const float z=(l.ground-lift-112*s)/(f.y+f.h-330.f);
 const float outerLeft=(DX-f.w*z)*.5f;
 const float innerLeft=outerLeft+(left-f.x)*z;
 const float innerRight=outerLeft+(right-f.x)*z;
 return {{(float)f.x,(float)left,(float)right,(float)(f.x+f.w)},
         {(float)f.y,(float)top,(float)bottom,(float)(f.y+f.h)},
         {outerLeft,innerLeft,innerRight,outerLeft+f.w*z},
         {112*s+f.h*z+lift,112*s+(f.y+f.h-top)*z+lift,112*s+(f.y+f.h-bottom)*z+lift,112*s+lift}};
}
Box roomBox(const Layout& l,int room){
 if(run.stage==0){const auto p=OriginalCastle::rooms()[room];return OriginalCastle::box((int)p[0].x,(int)p[0].y,(int)(p[1].x-p[0].x),(int)(p[2].y-p[0].y));}
 const int c=std::max(0,std::min(9,run.stage));const auto m=castleMap(l,c);const auto& f=MergeCastleArt::Holes[c][room];
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
   }
  }
  UnSectionClip(false);
 }
}
void drawCastleHull(const Layout& l){
 const int c=std::max(0,std::min(9,run.stage));const auto map=castleMap(l,c);const float s=l.scale;
 if(c==0){
  const int img=MERGE_REBUILD_ROOMS_IMG;if(!sprite[img])LoadImg(img);
  if(sprite[img])for(int i=0;i<5;++i){
   Box b=roomBox(l,i);const auto size=sprite[img]->getTexture()->getContentSizeInPixels();
   const auto f=MergeCastleTransition::RoomFrame(i,std::min(5,(int)robin.castleProgress.rooms[0][i]),(int)size.width,(int)size.height);
   const float z=std::max(b.w/(float)f.w,b.h/(float)f.h);const int sw=std::min(f.w,(int)std::ceil(b.w/z)),sh=std::min(f.h,(int)std::ceil(b.h/z));
   SetSectionClip(b.x,b.y,b.w,b.h,false);
   DrawImageScale(sw,sh,f.x+(f.w-sw)/2,f.y+f.h-sh,b.x,b.y,false,0,0,0,0,z,z,sprite[img],img);UnSectionClip(false);
  }
  OriginalCastle::draw(10);OriginalCastle::draw(11);OriginalCastle::draw(12);
  OriginalCastle::wood(65,1204,160,131);OriginalCastle::wood(867,1202,162,133);
  OriginalCastle::draw(0);OriginalCastle::draw(1);
  const float wheelAngle=castleWheelAngle(99*OriginalCastle::zoom());
  OriginalCastle::wheel(0,wheelAngle);OriginalCastle::wheel(1,wheelAngle);OriginalCastle::draw(8);
  const int xx[5]={270,505,748,300,660},yy[5]={535,535,535,756,756},ww[5]={94,100,96,106,110};
  const char* titles[5]={"식량 재배","장비 공방","식음료","도서·문화","특화 시설"};
  for(int i=0;i<5;++i){Box t=OriginalCastle::box(xx[i]+5,yy[i]+5,ww[i]-10,22);MemRect(t.x,t.y,t.w,t.h,0xD9AF70);label(titles[i],t.x+t.w/2,t.y,.42f,0x23190E);}
  drawRoomResidents(l);return;
 }
 //---- 공성전: 적의 성은 거울로 선다 ----
 //
 //쳐들어간 성이라 방향이 반대다. 포탑·대포가 오른쪽으로 가고 성주가 거기
 //선다. 방 그림·차체·대포를 x 축으로 뒤집어 그린다. 바퀴는 좌우 대칭이라
 //그대로. 판(칸·블록)은 내 퍼즐이므로 뒤집지 않는다.
 const bool mirror=siegeActive;
 int img=MERGE_REBUILD_ROOMS_IMG+c;if(!sprite[img])LoadImg(img);
 if(sprite[img]){
  const auto size=sprite[img]->getTexture()->getContentSizeInPixels();
  for(int i=0;i<5;++i){
   const int lv=std::min(5,(int)robin.castleProgress.rooms[c][i]);
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
 if(sprite[chassisImg])DrawImageScale(chassis.w,chassis.h,chassis.x,chassis.y,(int)(mirror?DX-map.dx[3]:map.dx[0]),(int)map.dy[0],mirror,0,0,0,0,chassisZoom,chassisZoom,sprite[chassisImg],chassisImg);
 const int wheelLv=std::min(5,(int)robin.castleProgress.parts[c][4]);
 const auto& wheel=MergeCastleArt::Parts[c][1][wheelLv];const int partImg=MERGE_REBUILD_PARTS_IMG+c;
 if(!sprite[partImg])LoadImg(partImg);
 if(sprite[partImg])for(int i=0;i<2;++i){
  const int cx=(int)(i?DX-65*s:65*s),cy=(int)(139*s+castleSceneLift());
  RotateImage(wheel.w,wheel.h,wheel.x,wheel.y,cx,cy,false,castleWheelAngle(43*s),0,0,86*s/std::max(wheel.w,wheel.h),cocos2d::Vec2(.5f,.5f),sprite[partImg],partImg);
 }
 const int cannonLv=std::min(5,(int)robin.castleProgress.parts[c][3]);
 {Box cb=castleCannonBox(l);if(mirror)cb.x=DX-cb.x-cb.w;artCutFlip(partImg,MergeCastleArt::Parts[c][0][cannonLv],cb,mirror);}
 drawRoomResidents(l);
}
void drawLobbyControls(const Layout& l,float exit=0.f,bool interactive=false){
 const int drop=(int)(280*l.scale*exit);Box start=lobbyStart(l),keep=lobbyContinue(l),manage=lobbyManage(l);
 start.y-=drop;keep.y-=drop;manage.y-=drop;
 // All lobby buttons share the original canvas transform and aspect ratio.
 OriginalCastle::draw(2,(float)drop);OriginalCastle::draw(3,(float)drop);
 OriginalCastle::draw(4,(float)drop);
 const Box nav=OriginalCastle::box(76,1275,941,163,drop+OriginalCastle::lift());
 OriginalCastle::draw(5,(float)drop);
 const char* names[5]={"상점","영웅","모험","동료","성"};
 const int cx[5]={190,380,552,740,915};
 for(int i=0;i<5;++i){Box text=OriginalCastle::box(cx[i]-62,1382,124,42,drop+OriginalCastle::lift());MemRect(text.x,text.y,text.w,text.h,i==2?0x1748A0:0x633015);label(names[i],(int)(cx[i]*OriginalCastle::zoom()),text.y-(int)(4*l.scale),.67f,0xFFE7B9);}
 const int actions[5]={TOUCH_FUNC_SHOP,TOUCH_FUNC_COLLECTIONS,TOUCH_FUNC_LOBBY_ADVENTURE,TOUCH_FUNC_POPUP_CREWLIST,TOUCH_FUNC_POPUP_CASTLEMENU};
 if(interactive){
  button(lobbyPvp(l),"PVP 디버그","공성전",0x6B2D3F);
  for(int i=0;i<5;++i)SetRectPoint(nav.x+nav.w*i/5,nav.y,nav.w/5,nav.h,actions[i]);
  SetRectPoint(manage.x,manage.y,manage.w,manage.h,TOUCH_FUNC_POPUP_CASTLEMENU);
  for(int i=0;i<5;++i){const Box b=roomBox(l,i);SetRectPoint(b.x,b.y,b.w,b.h,TOUCH_FUNC_POPUP_CASTLEMENU);}
 }
}
