// Runtime source rectangles refer to original generated PNGs, never screenshot strips.
void artCut(int img,const MergeCastleArt::Rect& r,const Box& b) {
    if(!sprite[img])LoadImg(img);
    if(sprite[img]&&r.w>0&&r.h>0&&b.w>0&&b.h>0)
        DrawImageScale(r.w,r.h,r.x,r.y,b.x,b.y,false,0,0,0,0,b.w/(float)r.w,b.h/(float)r.h,sprite[img],img);
}
//좌우를 뒤집어 그린다(공성전: 적의 성은 거울로 선다). b 는 이미 뒤집힌 자리다.
void artCutFlip(int img,const MergeCastleArt::Rect& r,const Box& b,bool flip) {
    if(!sprite[img])LoadImg(img);
    if(sprite[img]&&r.w>0&&r.h>0&&b.w>0&&b.h>0)
        DrawImageScale(r.w,r.h,r.x,r.y,b.x,b.y,flip,0,0,0,0,b.w/(float)r.w,b.h/(float)r.h,sprite[img],img);
}
void uiArt(int ui,const Box& b){
 const auto& f=MergeCastleArt::UiFrames[ui];
 if(ui==MergeCastleArt::Board){
  const int p=std::max(1,(int)(22*DX/640.f)),edge=100;
  const int sx[4]={f.x,f.x+edge,f.x+f.w-edge,f.x+f.w},sy[4]={f.y,f.y+edge,f.y+f.h-edge,f.y+f.h};
  const int dx[4]={b.x,b.x+p,b.x+b.w-p,b.x+b.w},dy[4]={b.y,b.y-p,b.y-b.h+p,b.y-b.h};
  for(int r=0;r<3;++r)for(int c=0;c<3;++c)artCut(MERGE_REBUILD_UI_IMG+ui,{sx[c],sy[r],sx[c+1]-sx[c],sy[r+1]-sy[r]},
   {dx[c],dy[r],dx[c+1]-dx[c],dy[r]-dy[r+1]});
  return;
 }
 const float z=std::min(b.w/(float)f.w,b.h/(float)f.h);
 const int w=(int)(f.w*z),h=(int)(f.h*z);
 artCut(MERGE_REBUILD_UI_IMG+ui,f,{b.x+(b.w-w)/2,b.y-(b.h-h)/2,w,h});
}
void padArt(int index,const Box& b,float angle=0){
 const int img=MERGE_REBUILD_UI_IMG+MergeCastleArt::Footpads;
 const auto& f=MergeCastleArt::Pads[std::max(0,std::min(7,index))];
 if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 const float a=angle*3.14159265f/180.f;
 const int x=(int)(b.x+b.w*.5f-b.w*.5f*std::cos(a)+b.h*.5f*std::sin(a));
 const int y=(int)(b.y-b.h*.5f+b.w*.5f*std::sin(a)+b.h*.5f*std::cos(a));
 DrawImageScale(f.w,f.h,f.x,f.y,x,y,false,0,angle,0,0,b.w/(float)f.w,b.h/(float)f.h,sprite[img],img);
}
Box slotWindow(const Box& b,int i){
    // Safe interior rectangles follow the actual rounded windows of the new housing.
    const int xs[3]={500,925,1355},ws[3]={330,330,325};
    const auto& f=MergeCastleArt::UiFrames[MergeCastleArt::Slot];
    return {b.x+(xs[i]-f.x)*b.w/f.w,b.y-(170-f.y)*b.h/f.h,ws[i]*b.w/f.w,380*b.h/f.h};
}
