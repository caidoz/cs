// Included inside CastleParts. Whole authored castles are cut at shared beams;
// every cut uses ONE uniform scale. No component is stretched to fit a box.
static bool HybridImageReady(int img) {
 if(!sprite[img])LoadImg(img);
 if(!sprite[img]){missingAsset=true;return false;}
 sprite[img]->getTexture()->setAntiAliasTexParameters();return true;
}
static void HybridRegisteredCut(int img,int lv,int x,int y,int w,int h) {
 const float u=sdPlacement.width/1024.0f,z=1024.0f/638.0f*u;
 const int sx=20+(lv%3)*658+x,sy=(lv/3)*389+y;
 const float dx=sdPlacement.left+x*z,dy=sdPlacement.top-y*z;
 DrawImage(w,h,sx,sy,(int)std::lround(MirrorX(dx,w*z)),(int)std::lround(dy),
  gMirror,0,0,0,0,z,sprite[img],img);
}
static void DrawHybridFacade() {
 if(!HybridImageReady(HYBRID_CASTLE_CLOSED_V2_IMG))return;
 // The upper and lower horizontal structural beams conceal the shared cuts.
 HybridRegisteredCut(HYBRID_CASTLE_CLOSED_V2_IMG,Min(5,CastleVisualPartLevel(0,1)),0,175,415,140);
}
static bool DrawHybridStarter(float left,float bottom,float scale) {
 if(!HybridImageReady(HYBRID_CASTLE_CLOSED_V2_IMG)||!HybridImageReady(HYBRID_CASTLE_OPEN_V2_IMG)
   ||!HybridImageReady(HYBRID_PARTS_IMG)||!HybridImageReady(HYBRID_WHEELS_IMG))return false;
 const auto& r=IndividualCastleV4::Rigs[0];
 const bool world=!gFreePlace && (drawHandle==MD_PLAY || (drawHandle==MD_LOBBY && popUpCnt==0));
 const float oldUnit=world?DX/640.0f*r.width/r.w*CastlePartsViewZoom():1056.0f/r.w*scale;
 const float width=r.w*oldUnit,u=width/1024.0f;
 const float ground=bottom-252*scale+StarterLegacyGroundOffset()*scale+StageCastleGroundingPx()-kStarterRailOverlapPx;
 auto& p=sdPlacement;p=SdPlacement();p.valid=true;p.castle=0;p.roomCount=1;
 p.left=world?CastlePartsViewLeft(Max(4.0f*DX/640.0f,left)):left;
 p.width=width;p.height=680*u;p.top=ground+p.height;p.sourceWidth=1024;p.scale=width/960.0f;
 p.fitScale=oldUnit/(1056.0f/r.w*scale);
 p.commanderX=p.left+950*u;p.commanderY=p.top-432*u;
 p.deckLeft=p.left+620*u;p.deckWidth=300*u;p.deckSurface=p.commanderY;p.deckTop=p.deckSurface;
 p.interiorLeft=p.left+290*u;p.interiorTop=p.top-300*u;p.interiorWidth=235*u;
 p.interiorFloor=p.commanderY;p.roomFloorGap=150*u;
 auto& cover=roomCover[0];cover=RoomCoverRect();cover.left=(int)(p.left+290*u);cover.top=(int)(p.top-300*u);
 cover.width=(int)(235*u);cover.height=(int)(150*u);cover.material=HYBRID_PARTS_IMG;
 const bool reveal=RoomRevealRequested(0);roomCoverRevealed[0]=reveal;
 HybridRegisteredCut(HYBRID_CASTLE_OPEN_V2_IMG,Min(5,CastleVisualPartLevel(0,2)),0,0,638,389);
 HybridRegisteredCut(HYBRID_CASTLE_CLOSED_V2_IMG,Min(5,CastleVisualPartLevel(0,0)),0,0,638,175);
 if(!reveal)DrawHybridFacade();
 const int wheelLv=Min(5,CastleVisualPartLevel(0,4));const auto& wf=HybridSd3d::Wheels[wheelLv];
 const float angle=WheelAngleNow(70*u);p.wheelAngle=angle;
 for(int i=0;i<2;++i){
  const float cx=p.left+(i?650:180)*u,cy=p.top-610*u;
  RotateImage(wf.w,wf.h,wf.x,wf.y,(int)std::lround(gMirror?gMirrorAxis*2-cx:cx),(int)std::lround(cy),
    gMirror,gMirror?-angle:angle,0,0,140*u/Max(wf.w,wf.h),cocos2d::Vec2(.5f,.5f),sprite[HYBRID_WHEELS_IMG],HYBRID_WHEELS_IMG);
 }
 int gunCastle=0,gunLv=CastleVisualPartLevel(0,3);
 const bool mounted=!IsStageRealtime()||StageBagCannon(&gunCastle,&gunLv,NULL);
 if(mounted){
  gunLv=Min(5,Max(0,gunLv));const auto& f=HybridSd3d::Parts[3][gunLv];
  const float z=210*u/f.w,x=p.left+585*u,y=p.top-270*u;
  DrawImage(f.w,f.h,f.x,f.y,(int)std::lround(MirrorX(x,f.w*z)),(int)std::lround(y),!gMirror,0,0,0,0,z,sprite[HYBRID_PARTS_IMG],HYBRID_PARTS_IMG);
  cannonMuzzleX[0]=p.left+790*u;cannonMuzzleY[0]=p.top-295*u;cannonMuzzleValid[0]=true;
 }else cannonMuzzleValid[0]=false;
 cannonBaseY[0]=p.commanderY;
 const float ax[]={240,290,430,690,410},ay[]={160,380,380,360,610};
 for(int i=0;i<5;++i){partAnchor[0][i][0]=p.left+ax[i]*u;partAnchor[0][i][1]=p.top-ay[i]*u;}
 return true;
}
