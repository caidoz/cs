#include "../../Classes/PortraitGameLayout.h"
#include "../../Classes/MergeCastleTransition.h"
#include <cassert>
#include <cmath>
#include <iostream>

int main(){
 for(int width:{320,640,768})for(int rows:{4})for(int cols:{4,5,6,7,8,9}){
  const int shortHeight=width*850/640,tallHeight=width*1408/640;
  const auto a=PortraitGame::battle(width,shortHeight,rows,cols);
  const auto b=PortraitGame::battle(width,tallHeight,rows,cols);
  assert(a.cell==a.cellHeight&&a.cell<=64*width/640);
  assert(b.ground>a.ground&&a.statsTop==b.statsTop);
  assert(b.ground-b.statsTop==int(18*b.scale)+PortraitGame::railLift(width,tallHeight));
  assert(a.cell==b.cell&&a.boardBottom==b.boardBottom&&a.boardTop==b.boardTop);
  assert(a.slotTop==b.slotTop&&a.slotWidth==b.slotWidth&&a.slotHeight==b.slotHeight);
  assert(a.energyTop==b.energyTop&&a.actionTop==b.actionTop&&a.actionHeight==b.actionHeight);
  assert(std::abs(a.slotWidth*691-a.slotHeight*2064)<=2064);
  assert(a.boardBottom>a.slotTop&&a.slotTop-a.slotHeight>a.energyTop);
  assert(a.energyTop-int(22*a.scale)>a.actionTop&&a.actionTop>a.actionHeight);
  assert(a.statsTop-a.statsHeight>a.boardTop&&a.ground<a.headerBottom);
  assert(a.cell*cols<=width&&a.boardTop-a.boardBottom==rows*a.cell);
 }
 for(int width:{320,640,768}){
  const float height=533.f+86.f*.58f;
  const float castle=PortraitGame::battleCastleScale(width,height);
  const int referenceHeight=int(width*2.2f+.5f);
  assert(std::abs(castle*height-.90f*(referenceHeight-PortraitGame::battle(width,referenceHeight).ground))<.001f);
  assert(std::abs(PortraitGame::battleActorScale(width,431)-width/(2.f*431)*1.2f/.85f)<.001f);
  const auto base=PortraitGame::lobby(width,width*850/640);int previous=base.ground;
  for(int height=width*850/640;height<=width*1408/640;++height){
   const auto l=PortraitGame::lobby(width,height);
   assert(l.ground>=previous&&l.navTop==base.navTop&&l.startTop==base.startTop&&l.stageTop==base.stageTop);previous=l.ground;
  }
  const float s=width/640.f;
  const auto tall=PortraitGame::lobby(width,width*1408/640);
  const int compactGap=base.ground-int(19*s)-(base.stageTop+int(16*s));
  const int tallGap=tall.ground-int(19*s)-(tall.stageTop+int(16*s));
  assert(std::abs(compactGap/s-21)<3&&tallGap/s>=120&&tallGap/s<=210);
  assert(PortraitGame::railLift(width,width*1800/640)==int(120*s+.5f));
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
 std::cout<<"PASS square cells, fixed bottom stack, resolution-only rail clearances, source aspect and complete staggered grid assembly\n";
}
