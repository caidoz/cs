#include "../../Classes/PortraitGameLayout.h"
#include "../../Classes/MergeCastleTransition.h"
#include <cassert>
#include <cmath>
#include <iostream>

int main(){
 for(int width:{320,640,768})for(int rows:{4,5,6})for(int cols:{4,6,8}){
  const int shortHeight=width*850/640,tallHeight=width*1408/640;
  const auto a=PortraitGame::battle(width,shortHeight,rows,cols);
  const auto b=PortraitGame::battle(width,tallHeight,rows,cols);
  assert(a.cell==a.cellHeight&&a.cell==64*width/640);
  assert(a.cell==b.cell&&a.boardBottom==b.boardBottom&&a.boardTop==b.boardTop);
  assert(a.slotTop==b.slotTop&&a.slotWidth==b.slotWidth&&a.slotHeight==b.slotHeight);
  assert(a.energyTop==b.energyTop&&a.actionTop==b.actionTop&&a.actionHeight==b.actionHeight);
  assert(std::abs(a.slotWidth*691-a.slotHeight*2064)<=2064);
  assert(a.boardBottom>a.slotTop&&a.slotTop-a.slotHeight>a.energyTop);
  assert(a.energyTop-int(22*a.scale)>a.actionTop&&a.actionTop>a.actionHeight);
  assert(a.statsTop-a.statsHeight>a.boardTop&&a.ground<a.headerBottom);
  assert(a.cell*cols<=width&&a.boardTop-a.boardBottom==rows*a.cell);
 }
 for(int count:{16,20,24,28,32,36,40,44,46,48}){
  for(int i=0;i<count;++i){
   const float start=MergeCastleTransition::TileLaunch(i,count),land=MergeCastleTransition::TileLand(i,count);
   assert(MergeCastleTransition::TileProgress(start-.001f,i,count)==0.f);
   assert(MergeCastleTransition::TileProgress(land+.001f,i,count)==1.f);
   assert(land+.09f<=MergeCastleTransition::Duration);
   if(i)assert(start>MergeCastleTransition::TileLaunch(i-1,count));
  }
 }
 std::cout<<"PASS square cells, fixed bottom stack, source aspect and complete staggered grid assembly\n";
}
