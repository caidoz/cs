// Only the newly authored portrait library supplies surfaces and UI icons.
void portraitSkin(int kind,const Box& b,bool sliced=true){
 const int img=PORTRAIT_UI_FIRST_IMG+kind;
 if(!sprite[img])LoadImg(img);if(!sprite[img]||b.w<=0||b.h<=0)return;
 const auto size=sprite[img]->getTexture()->getContentSizeInPixels();
 const MergeCastleArt::Rect f={0,0,(int)size.width,(int)size.height};
 if(sliced)nineSlice(img,f,b,kind<2?30:48);else artCut(img,f,b);
}
void portraitGlyph(int glyph,const Box& b){
 const int img=PORTRAIT_ICONS_IMG;if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 const auto size=sprite[img]->getTexture()->getContentSizeInPixels();
 const int cw=(int)size.width/4,ch=(int)size.height/3;
 static const int bounds[12][4]={{77,131,323,312},{78,102,291,312},{56,102,270,320},{67,106,247,322},{95,70,303,292},{71,83,297,282},{59,75,264,284},{40,80,277,285},{77,36,324,282},{44,15,296,294},{22,44,296,282},{21,53,292,278}};
 const auto& q=bounds[std::max(0,std::min(11,glyph))];const int w=q[2]-q[0],h=q[3]-q[1];
 const float z=std::min(b.w/(float)w,b.h/(float)h);
 artCut(img,{(glyph%4)*cw+q[0],(glyph/4)*ch+q[1],w,h},
  {b.x+(int)((b.w-w*z)*.5f),b.y-(int)((b.h-h*z)*.5f),(int)(w*z),(int)(h*z)});
}
void portraitTile(const Box& b,float angle){
 const int img=PORTRAIT_UI_FIRST_IMG+1;if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 const auto size=sprite[img]->getTexture()->getContentSizeInPixels();
 const int depth=std::max(2,(int)(3*DX/640.f)),previous=baseColor;
 Box face={b.x+1,b.y-1,b.w-2,b.h-depth-1};
 if(angle!=0){
  const float z=std::min(face.w/size.width,face.h/size.height);
  SetColor(0x24464E);
  RotateImage((int)size.width,(int)size.height,0,0,face.x+face.w/2,face.y-face.h/2-depth,false,angle,0,0,z,cocos2d::Vec2(.5f,.5f),sprite[img],img);
  SetColor(0xD0FFFF);
  RotateImage((int)size.width,(int)size.height,0,0,face.x+face.w/2,face.y-face.h/2,false,angle,0,0,z,cocos2d::Vec2(.5f,.5f),sprite[img],img);
 }else{
  const MergeCastleArt::Rect source={0,0,(int)size.width,(int)size.height};
  SetColor(0x24464E);nineSlice(img,source,{face.x,face.y-depth,face.w,face.h},38);
  SetColor(0xD0FFFF);nineSlice(img,source,face,38);
 }
 SetColor(previous);
}
void portraitCog(const Box& b,float angle){
 const int img=PORTRAIT_ROULETTE_GEAR_IMG;if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 const auto& f=MergeCastleArt::UiFrames[MergeCastleArt::Gear];
 const float z=std::min(b.w/(float)f.w,b.h/(float)f.h);
 const int previous=baseColor;SetColor(0);
 RotateImage(f.w,f.h,f.x,f.y,b.x+b.w/2,b.y-b.h/2,false,angle,0,0,z,cocos2d::Vec2(.5f,.5f),sprite[img],img);
 SetColor(previous);
}
void portraitImage(int img,const Box& b,bool mirror=false){
 if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 const auto size=sprite[img]->getTexture()->getContentSizeInPixels();
 const float z=std::min(b.w/size.width,b.h/size.height);
 DrawImage((int)size.width,(int)size.height,0,0,b.x+(int)((b.w-size.width*z)*.5f),
  b.y-(int)((b.h-size.height*z)*.5f),mirror,0,0,0,0,z,sprite[img],img);
}
void portraitHeroIcon(const Box& b){
 const int cmf=hero.cmf;if(cmf<0||cmf>=MAXCMF)return;
 if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);
 const int pose=GetHeroLoopMotion(cmf,HEROLOOP_NEUTRAL,0);if(pose<0||pose>=cmf_m_cnt[cmf])return;
 const auto* bounds=cmfMotionImgSize[cmf]+pose*4;
 const float z=std::min((b.w-4.f*DX/640.f)/std::max(1,(int)bounds[2]),(b.h-4.f*DX/640.f)/std::max(1,(int)bounds[3]));
 const int x=b.x+b.w/2-(int)((bounds[0]+bounds[2]*.5f)*z);
 const int y=b.y-(int)((b.h-bounds[3]*z)*.5f)+(int)(bounds[1]*z);
 const int cx=clipX,cy=clipY,cx2=clipX2,cy2=clipY2,previous=baseColor;
 SetSectionClip(b.x,b.y,b.w,b.h,false);SetColor(0);
 DrawPlayer(&hero,pose,x,y,RIGHT,z,0,false,true);
 SetColor(previous);clipX=cx;clipY=cy;clipX2=cx2;clipY2=cy2;
}
Box portraitBackdropBox(int ground){
 const float s=DX/640.f;const int fixedGround=ground-(int)portraitCameraY;
 const int img=PORTRAIT_NIGHT_IMG;if(!sprite[img])LoadImg(img);if(!sprite[img])return {0,0,0,0};
 const auto size=sprite[img]->getTexture()->getContentSizeInPixels();
 const float z=std::max(DX/size.width,(DY-70*s-fixedGround)/(.825f*size.height));
 return {-(int)std::fmod(castleScrollSeconds*110.f*s,std::max(1.f,size.width*z-DX+1)),
  fixedGround+(int)(size.height*.825f*z),(int)(size.width*z),(int)(size.height*z)};
}
int portraitBridgeTop=0,portraitBridgeBottom=0;
void portraitArchBridge(int top,int bottom){
 portraitBridgeTop=portraitBridgeBottom=0;if(top<=bottom)return;
 const int region=std::max(0,std::min(14,StageBg::s_region)),img=StageBg::Img(StageBg::SlotRail);
 if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 const auto size=sprite[img]->getTexture()->getContentSizeInPixels();
 const auto& cycle=StageRailArt::Cycles[region];
 const int sourceTop=50,sourceWidth=cycle[1]-cycle[0],sourceHeight=cycle[3]+12-sourceTop;
 const float s=DX/640.f,z=std::max(DX/size.width,(PortraitGame::railLift(DX,DY)+64*s)/sourceHeight);
 const int period=std::max(1,(int)(sourceWidth*z)),offset=(int)std::fmod(castleScrollSeconds*110*s,(float)period);
 const int left=clipX,right=clipX2,upper=clipY,lower=clipY2;
 clipY=std::min(clipY,top);clipY2=std::max(clipY2,bottom);
 for(int x=-offset;x<DX;x+=period)DrawImage(sourceWidth,sourceHeight,cycle[0],sourceTop,x,top,false,0,0,0,0,z,sprite[img],img);
 clipX=left;clipX2=right;clipY=upper;clipY2=lower;
 portraitBridgeTop=top;portraitBridgeBottom=bottom;
}
void portraitNight(int ground,float worldZoom=0,int bridgeBottom=0){
 portraitBridgeTop=portraitBridgeBottom=0;
 const float s=DX/640.f;MemRect(0,DY,DX,DY,0x030A13);
 const int img=PORTRAIT_NIGHT_IMG;const Box bg=portraitBackdropBox(ground);
 if(!sprite[img])return;const auto size=sprite[img]->getTexture()->getContentSizeInPixels();
 DrawImage((int)size.width,(int)size.height,0,0,bg.x,bg.y,false,0,0,0,0,bg.w/size.width,sprite[img],img);
 {
  const bool sample=review&&std::getenv("CS_PORTRAIT_SAMPLE_ASSETS")&&std::getenv("CS_PORTRAIT_SAMPLE_ASSEMBLED")&&std::getenv("CS_PORTRAIT_SAMPLE_GROUND");
  const int road=sample?PORTRAIT_WHEEL_FIRST_IMG:PORTRAIT_RAIL_IMG;if(!sprite[road])LoadImg(road);
  if(sprite[road]){const auto q=sprite[road]->getTexture()->getContentSizeInPixels();const float rz=!sample&&worldZoom>0?worldZoom:DX/q.width;
   const char* rail=sample?std::getenv("CS_PORTRAIT_SAMPLE_RAIL_Y"):nullptr;
   const int top=ground+(int)((rail?std::atof(rail):sample?q.height*.70f:26.f)*rz);
   if(!sample)portraitArchBridge(top-(int)(q.height*rz)+1,bridgeBottom);
   const int period=std::max(1,(int)(q.width*rz));
   const int offset=(int)std::fmod(castleScrollSeconds*110.f*s,(float)period);
   for(int x=-offset;x<DX;x+=period)
    DrawImage((int)q.width,(int)q.height,0,0,x,top,false,0,0,0,0,rz,sprite[road],road);
  }
 }
}
