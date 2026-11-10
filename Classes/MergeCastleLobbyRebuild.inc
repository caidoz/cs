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
Box lobbyStart(const Layout& l){return OriginalCastle::box(294,1037,506,150);}
Box lobbyContinue(const Layout& l){return OriginalCastle::box(411,1196,274,52);}
Box lobbyManage(const Layout& l){return OriginalCastle::box(404,1005,276,49);}
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
 const float z=(l.ground-112*s)/(f.y+f.h-330.f);
 const float outerLeft=(DX-f.w*z)*.5f;
 const float innerLeft=outerLeft+(left-f.x)*z;
 const float innerRight=outerLeft+(right-f.x)*z;
 return {{(float)f.x,(float)left,(float)right,(float)(f.x+f.w)},
         {(float)f.y,(float)top,(float)bottom,(float)(f.y+f.h)},
         {outerLeft,innerLeft,innerRight,outerLeft+f.w*z},
         {112*s+f.h*z,112*s+(f.y+f.h-top)*z,112*s+(f.y+f.h-bottom)*z,112*s}};
}
Box roomBox(const Layout& l,int room){
 if(run.stage==0){const auto p=OriginalCastle::rooms()[room];return OriginalCastle::box((int)p[0].x,(int)p[0].y,(int)(p[1].x-p[0].x),(int)(p[2].y-p[0].y));}
 const int c=std::max(0,std::min(9,run.stage));const auto m=castleMap(l,c);const auto& f=MergeCastleArt::Holes[c][room];
 int x=(int)std::floor(m.x(f.x)),right=(int)std::ceil(m.x(f.x+f.w));
 int top=(int)std::ceil(m.y(f.y)),bottom=(int)std::floor(m.y(f.y+f.h));
 return {x,top,right-x,top-bottom};
}
void drawRoomResidents(const Layout& l){
 for(int i=0;i<5;++i){
  const Box b=roomBox(l,i);const int role=i%Roles;
  int crew=-1,ordinal=i/4;
  for(int star=1;star<=MaxLevel&&crew<0;++star)for(int k=0;k<roster.count[role][star];++k)
   if(ordinal--==0){crew=roster.crew[role][star][k];break;}
  if(crew<0)crew=roster.first(role,1);
  if(crew<0)crew=MergeTrees::CrewAt(role,1,i/4);
  if(crew<0)crew=MergeTrees::CrewAt(role,1,0);
  const int h=(int)std::min(60*l.scale,b.h*.70f),w=(int)(h*.85f);
  Box resident={b.x+(int)(b.w*.70f)-w/2,b.y-b.h+(int)(9*l.scale)+h,w,h};
  SetSectionClip(b.x,b.y,b.w,b.h,false);
  icon(role,resident,1.f,false,MergeTrees::Star(crew),crew);
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
  OriginalCastle::wood(294,1035,507,153);OriginalCastle::wood(403,1003,279,53);OriginalCastle::wood(410,1194,277,56);
  OriginalCastle::wood(65,1204,160,131);OriginalCastle::wood(867,1202,162,133);
  OriginalCastle::draw(0);OriginalCastle::draw(1);
  const float wheelAngle=castleWheelAngle(99*OriginalCastle::zoom());
  OriginalCastle::wheel(0,wheelAngle);OriginalCastle::wheel(1,wheelAngle);OriginalCastle::draw(8);
  const int xx[5]={270,505,748,300,660},yy[5]={535,535,535,756,756},ww[5]={94,100,96,106,110};
  const char* titles[5]={"식량 재배","장비 공방","식음료","도서·문화","특화 시설"};
  for(int i=0;i<5;++i){Box t=OriginalCastle::box(xx[i]+5,yy[i]+5,ww[i]-10,22);MemRect(t.x,t.y,t.w,t.h,0xD9AF70);label(titles[i],t.x+t.w/2,t.y,.42f,0x23190E);}
  drawRoomResidents(l);return;
 }
 int img=MERGE_REBUILD_ROOMS_IMG+c;if(!sprite[img])LoadImg(img);
 if(sprite[img]){
  const auto size=sprite[img]->getTexture()->getContentSizeInPixels();
  for(int i=0;i<5;++i){
   const int lv=std::min(5,(int)robin.castleProgress.rooms[c][i]);
   const auto f=MergeCastleTransition::RoomFrame(i,lv,(int)size.width,(int)size.height);
   Box b=roomBox(l,i);b.x-=2;b.y+=2;b.w+=4;b.h+=4;
   const float z=std::max(b.w/(float)f.w,b.h/(float)f.h);
   const int sw=std::min(f.w,(int)std::ceil(b.w/z)),sh=std::min(f.h,(int)std::ceil(b.h/z));
   SetSectionClip(b.x,b.y,b.w,b.h,false);
   DrawImageScale(sw,sh,f.x+(f.w-sw)/2,f.y+f.h-sh,b.x,b.y,false,0,0,0,0,z,z,sprite[img],img);
   UnSectionClip(false);
  }
 }
 const auto& chassis=MergeCastleArt::Chassis[c];
 const int chassisImg=MERGE_REBUILD_CHASSIS_IMG+c;if(!sprite[chassisImg])LoadImg(chassisImg);
 const float chassisZoom=(map.dx[3]-map.dx[0])/chassis.w;
 if(sprite[chassisImg])DrawImageScale(chassis.w,chassis.h,chassis.x,chassis.y,(int)map.dx[0],(int)map.dy[0],false,0,0,0,0,chassisZoom,chassisZoom,sprite[chassisImg],chassisImg);
 const int wheelLv=std::min(5,(int)robin.castleProgress.parts[c][4]);
 const auto& wheel=MergeCastleArt::Parts[c][1][wheelLv];const int partImg=MERGE_REBUILD_PARTS_IMG+c;
 if(!sprite[partImg])LoadImg(partImg);
 if(sprite[partImg])for(int i=0;i<2;++i){
  const int cx=(int)(i?DX-65*s:65*s),cy=(int)(139*s);
  RotateImage(wheel.w,wheel.h,wheel.x,wheel.y,cx,cy,false,castleWheelAngle(43*s),0,0,86*s/std::max(wheel.w,wheel.h),cocos2d::Vec2(.5f,.5f),sprite[partImg],partImg);
 }
 const int cannonLv=std::min(5,(int)robin.castleProgress.parts[c][3]);
 const auto& cannon=MergeCastleArt::Parts[c][0][cannonLv];
 const float z=std::min(95*s/cannon.w,77*s/cannon.h);
 artCut(partImg,cannon,{(int)(246*s),(int)(l.ground+cannon.h*z),(int)(cannon.w*z),(int)(cannon.h*z)});
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
  for(int i=0;i<5;++i)SetRectPoint(nav.x+nav.w*i/5,nav.y,nav.w/5,nav.h,actions[i]);
  SetRectPoint(manage.x,manage.y,manage.w,manage.h,TOUCH_FUNC_POPUP_CASTLEMENU);
  for(int i=0;i<5;++i){const Box b=roomBox(l,i);SetRectPoint(b.x,b.y,b.w,b.h,TOUCH_FUNC_POPUP_CASTLEMENU);}
 }
}
