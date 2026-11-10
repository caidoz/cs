// The management screen uses the same new assets as the live castle.
static void RebuildCut(int img,const MergeCastleArt::Rect& f,int x,int y,float z){
 if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 DrawImageScale(f.w,f.h,f.x,f.y,x,y,false,0,0,0,0,z,z,sprite[img],img);
}
static void RebuildPreview(int c,int x,int top,int width,int height){
 if(MergeRouletteOriginalPreview(c,x,top,width,height))return;
 const auto& frame=MergeCastleArt::Chassis[c];
 const float z=Min(width/(float)frame.w,height/(float)frame.h);
 const int left=x+(width-frame.w*z)/2,y=top-(height-frame.h*z)/2;
 const int roomImg=MERGE_REBUILD_ROOMS_IMG+c;if(!sprite[roomImg])LoadImg(roomImg);
 if(sprite[roomImg]){
  const auto size=sprite[roomImg]->getTexture()->getContentSizeInPixels();
  for(int i=0;i<5;++i){const auto& h=MergeCastleArt::Holes[c][i];
   const auto f=MergeCastleTransition::RoomFrame(i,robin.castleProgress.rooms[c][i],(int)size.width,(int)size.height);
   const float rz=Max((h.w+4)*z/f.w,(h.h+4)*z/f.h);
   const int sw=Min(f.w,(int)((h.w+4)*z/rz)),sh=Min(f.h,(int)((h.h+4)*z/rz));
   DrawImageScale(sw,sh,f.x+(f.w-sw)/2,f.y+f.h-sh,left+(h.x-frame.x-2)*z,y-(h.y-frame.y-2)*z,false,0,0,0,0,rz,rz,sprite[roomImg],roomImg);
  }
 }
 RebuildCut(MERGE_REBUILD_CHASSIS_IMG+c,frame,left,y,z);
 const int parts=MERGE_REBUILD_PARTS_IMG+c;
 const auto& cannon=MergeCastleArt::Parts[c][0][Min(5,(int)robin.castleProgress.parts[c][3])];
 RebuildCut(parts,cannon,left+400*z,y-(320-frame.y)*z+cannon.h*z*.55f,z*.55f);
 const auto& wheel=MergeCastleArt::Parts[c][1][Min(5,(int)robin.castleProgress.parts[c][4])];
 for(int i=0;i<2;++i)RebuildCut(parts,wheel,left+(i?frame.w-150:0)*z,y-(frame.h-150)*z,z*150/Max(wheel.w,wheel.h));
}
static void PartIcon(int c,int part,int lv,int x,int top,int size){
 c=Min(9,Max(0,c));lv=Min(5,Max(0,lv));
 if(part==2){FacilityIcon(c,0,robin.castleProgress.rooms[c][0],x,top,size);return;}
 if(part==1){RebuildPreview(c,x,top,size,size);return;}
 if(c==0&&part==0){MergeRouletteOriginalPreview(c,x,top,size,size);return;}
 const auto f=part==0?MergeCastleArt::Rect{MergeCastleArt::Chassis[c].x,MergeCastleArt::Chassis[c].y,500,380}:MergeCastleArt::Parts[c][part==4?1:0][lv];
 const float z=Min((size-8)/(float)f.w,(size-8)/(float)f.h);
 RebuildCut((part==0?MERGE_REBUILD_CHASSIS_IMG:MERGE_REBUILD_PARTS_IMG)+c,f,x+(size-f.w*z)/2,top-(size-f.h*z)/2,z);
}
