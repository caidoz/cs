// Complete authored castle bodies, registered once for all five independent upgrades.
// Source cells and all sockets share a single uniform source-pixel scale.
static void HybridFleetCut(int castle,int kind,int level,int x,int y,int w,int h){
 const auto& r=HybridFleet::Rigs[castle-1];const auto& p=sdPlacement;
 const int img=HybridFleet::Image(castle,kind),lv=Min(5,Max(0,level));
 if(!HybridImageReady(img))return;
 const float u=p.width/r.w,dx=p.left+x*u,dy=p.top-y*u;
 DrawImage(w,h,(lv%3)*r.w+x,(lv/3)*r.stride+y,(int)std::lround(MirrorX(dx,w*u)),
  (int)std::lround(dy),gMirror,0,0,0,0,u,sprite[img],img);
}
static void DrawHybridFleetFacade(int castle){
 const auto& r=HybridFleet::Rigs[castle-1];
 HybridFleetCut(castle,0,CastleVisualPartLevel(castle,1),0,r.roof,r.facadeWidth,r.facadeBottom-r.roof);
}
static bool DrawHybridFleet(int castle,float left,float bottom,float scale){
 if(castle<1||castle>9)return false;
 for(int kind=0;kind<3;++kind)if(!HybridImageReady(HybridFleet::Image(castle,kind)))return false;
 const auto& a=HybridFleet::Rigs[castle-1];const auto& original=IndividualCastleV4::Rigs[castle];
 const bool world=!gFreePlace&&(drawHandle==MD_PLAY||(drawHandle==MD_LOBBY&&popUpCnt==0));
 float width=world?DX/640.0f*original.width*CastlePartsViewZoom():1056.0f*original.width/342.0f*scale;
 const float ground=bottom-252*scale+54.0f*scale+StageCastleGroundingPx()-kStarterRailOverlapPx;
 // Uniformly fit tall late-game silhouettes below the lobby information card.
 if(world&&drawHandle==MD_LOBBY){
  const float available=Max(180.0f*DX/640.0f,DY-174.0f*DX/640.0f-ground);
  width=Min(width,available*a.w/a.totalH*CastlePartsViewZoom());
 }
 const float u=width/a.w;
 auto& p=sdPlacement;p=SdPlacement();p.valid=true;p.castle=castle;
 p.left=world?CastlePartsViewLeft(Max(4.0f*DX/640.0f,left)):left;
 p.width=width;p.height=a.totalH*u;p.top=ground+p.height;p.sourceWidth=a.w;
 p.scale=width/960.0f;p.fitScale=width/(1056.0f*original.width/342.0f*scale);
 p.commanderX=p.left+.95f*width;p.commanderY=p.top-a.deckY*u;
 p.deckLeft=p.left+.64f*width;p.deckWidth=.30f*width;p.deckTop=p.deckSurface=p.commanderY;
 // Visual apertures follow authored floors; gameplay room capacity stays in Progress.
 p.roomCount=a.rooms;p.roomColumns=1;p.interiorLeft=p.left+a.roomX*u;
 p.interiorTop=p.top-a.roomY*u;p.interiorWidth=a.roomW*u;
 p.interiorFloor=p.interiorTop-a.roomH*u;p.roomFloorGap=a.roomH*u/a.rooms;
 auto& cover=roomCover[castle];cover=RoomCoverRect();cover.material=HybridFleet::Image(castle,0);
 cover.left=(int)p.interiorLeft;cover.top=(int)p.interiorTop;cover.width=(int)p.interiorWidth;cover.height=(int)(a.roomH*u);
 const bool reveal=RoomRevealRequested(castle);roomCoverRevealed[castle]=reveal;
 HybridFleetCut(castle,1,CastleVisualPartLevel(castle,2),0,0,a.w,a.h);
 HybridFleetCut(castle,0,CastleVisualPartLevel(castle,0),0,0,a.w,a.roof);
 if(!reveal)DrawHybridFleetFacade(castle);
 const float angle=WheelAngleNow(a.radius*u);p.wheelAngle=angle;
 const auto& wf=a.wheels[Min(5,CastleVisualPartLevel(castle,4))];
 const int partsImg=HybridFleet::Image(castle,2);
 for(int i=0;i<a.wheelCount;++i){
  const float center=.18f+.48f*i/Max(1,a.wheelCount-1),cx=p.left+center*width,cy=p.top-a.axleY*u;
  RotateImage(wf.w,wf.h,wf.x,wf.y,(int)std::lround(gMirror?gMirrorAxis*2-cx:cx),(int)std::lround(cy),
   gMirror,gMirror?-angle:angle,0,0,2*a.radius*u/Max(wf.w,wf.h),cocos2d::Vec2(.5f,.5f),sprite[partsImg],partsImg);
 }
 int weaponCastle=castle,level=CastleVisualPartLevel(castle,3);
 const bool mounted=!IsStageRealtime()||StageBagCannon(&weaponCastle,&level,NULL);
 if(mounted){
  level=Min(5,Max(0,level));const auto& gun=a.guns[level];
  const float z=.23f*width/gun.w,x=p.left+.60f*width,top=p.deckSurface+gun.h*z;
  DrawImage(gun.w,gun.h,gun.x,gun.y,(int)std::lround(MirrorX(x,gun.w*z)),(int)std::lround(top),
    gMirror,0,0,0,0,z,sprite[partsImg],partsImg);
  cannonMuzzleX[castle]=x+gun.w*z*.91f;cannonMuzzleY[castle]=top-gun.h*z*.15f;cannonMuzzleValid[castle]=true;
 }else cannonMuzzleValid[castle]=false;
 cannonBaseY[castle]=p.commanderY;
 const float ax[]={.40f,.38f,.40f,.71f,.42f};
 const float ay[]={a.roof*.5f,(a.roof+a.facadeBottom)*.5f,a.roomY+a.roomH*.5f,a.deckY-40.0f,(float)a.axleY};
 for(int i=0;i<5;++i){partAnchor[castle][i][0]=p.left+ax[i]*width;partAnchor[castle][i][1]=p.top-ay[i]*u;}
 return true;
}
