#include "../../Classes/BattleMenuLayout.h"
#include <cassert>
#include <cstdio>
int main() {
 using namespace BattleMenuLayout;
 for(int width=320;width<=1080;width+=80) {
  const int cell=Cell(width,2);
  assert(cell==48);
  const int pad=37,maximum=ScrollMax(width,12,cell,pad);
  assert(maximum>=0);
  if(maximum) {
   assert(Origin(width,12,cell,pad,0)==8+pad);
   assert(Origin(width,12,cell,pad,maximum)+12*cell+pad==width-8);
   assert(Origin(width,12,cell,pad,maximum+100)==Origin(width,12,cell,pad,maximum));
  }
  if(!maximum) assert(Origin(width,12,cell,pad,0)+12*cell/2==width/2);
  assert(GridHeight(2,cell)==4*cell);
  const int four=Ground(200,200+GridHeight(4,cell),2);
  const int six=Ground(200,200+GridHeight(6,cell),2);
  assert(six-four==2*cell);
  assert(Ground(200,GridHeight(4,cell),2)<four);
 }
 float y=0;
 for(int frame=0;frame<120;++frame) { float before=y; y=Approach(y,200); assert(y>=before&&y<=200); }
 assert(y==200);
 for(int frame=0;frame<120;++frame) y=Approach(y,0);
 assert(y==0);
 assert(ScrollMax(640,8,48,37)==0&&ScrollMax(640,12,48,37)==0);
 puts("Battle menu: literal 48px cells, complete horizontal range, four/six rows and transitions OK");
}
