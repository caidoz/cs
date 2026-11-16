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
//---- 9조각 그리기 ----
//
//정사각 그림을 직사각 상자에 그냥 늘이면 테두리 경사와 모서리가 찌그러진다(1×2 칸의 발판).
//네 모서리는 크기를 지키고, 네 변은 한 방향으로만, 가운데만 양쪽으로 늘인다.
//edge 는 원본 픽셀 기준 모서리 크기. 모서리는 상자가 작아지는 쪽 배율로 같이 줄어든다.
void nineSlice(int img,const MergeCastleArt::Rect& f,const Box& b,int edge){
 if(!sprite[img])LoadImg(img);if(!sprite[img]||b.w<=0||b.h<=0)return;
 const float k=std::min(b.w/(float)f.w,b.h/(float)f.h);
 const int cw=std::max(1,std::min(b.w/2,(int)(edge*k))),ch=std::max(1,std::min(b.h/2,(int)(edge*k)));
 const int sx[4]={f.x,f.x+edge,f.x+f.w-edge,f.x+f.w},sy[4]={f.y,f.y+edge,f.y+f.h-edge,f.y+f.h};
 const int dx[4]={b.x,b.x+cw,b.x+b.w-cw,b.x+b.w},dy[4]={b.y,b.y-ch,b.y-b.h+ch,b.y-b.h};
 //조각 사이에 실금이 서지 않게 가운데 줄·열을 먼저 1픽셀 넓게 깔고, 모서리와 변을 그 위에 얹는다.
 //배율이 정수가 아니면 조각 경계가 반 픽셀씩 비어 밑판이 비친다.
 static const int order[9][2]={{1,1},{0,1},{2,1},{1,0},{1,2},{0,0},{2,0},{0,2},{2,2}};
 for(const auto& rc:order){
  const int r=rc[0],c=rc[1];
  const int w=sx[c+1]-sx[c],h=sy[r+1]-sy[r];
  int x0=dx[c],x1=dx[c+1],y0=dy[r],y1=dy[r+1];
  if(c==1){x0-=1;x1+=1;} if(r==1){y0+=1;y1-=1;}
  const int dw=x1-x0,dh=y0-y1;
  if(w<=0||h<=0||dw<=0||dh<=0)continue;
  DrawImageScale(w,h,sx[c],sy[r],x0,y0,false,0,0,0,0,dw/(float)w,dh/(float)h,sprite[img],img);
 }
}
void padArt(int index,const Box& b,float angle=0){
 const int img=MERGE_REBUILD_UI_IMG+MergeCastleArt::Footpads;
 const auto& f=MergeCastleArt::Pads[std::max(0,std::min(7,index))];
 if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 //정사각이 아닌 칸(1×2 장비 등)은 9조각으로. 돌아가는 중(angle)인 타일은 정사각이라 그대로.
 if(angle==0&&std::abs(b.w-b.h)>1){nineSlice(img,f,b,(int)(f.w*.25f));return;}
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
