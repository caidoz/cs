#pragma once
#include <algorithm>
namespace RewardReveal {
struct Layout {
 float scale,zoom,w,h,gap,top,bottom,view,content,maximum;
 int columns,rows;
 Layout(int width,int height,int count){
  scale=width/640.f;zoom=.42f*scale;w=240*zoom;h=332*zoom;gap=12*scale;
  top=height-154*scale;bottom=110*scale;view=std::max(1.f,top-bottom);
  columns=std::max(1,(int)((width-40*scale+gap)/(w+gap)));
  rows=(count+columns-1)/columns;
  content=rows?rows*h+(rows-1)*gap:0;
  maximum=std::max(0.f,content-view);
 }
 float rowTop(int index,float scroll)const{
  return top-std::max(0.f,(view-content)*.5f)-(index/columns)*(h+gap)+scroll;
 }
 float left(int index,int count,int width)const{
  const int first=index/columns*columns,n=std::min(columns,count-first);
  return (width-(n*w+(n-1)*gap))*.5f+(index%columns)*(w+gap);
 }
};
}
