#include "../../Classes/MergeCastleTransition.h"
#include "../../Classes/CastleMenuModel.h"
#include <cassert>
#include <iostream>
int main(){
 using namespace MergeCastleTransition;
 assert(LobbyExit(0)==0&&LobbyExit(.4f)==1);
 assert(BoardEnter(CoverEnd)==0&&BoardEnter(CoverEnd+.75f)==1);
 assert(ControlsEnter(0)==0&&ControlsEnter(.28f)==1&&ControlsEnter(Duration)==1);
 float previous=0;
 for(int n=0;n<=230;++n){const float value=BoardEnter(n*.01f);assert(value>=previous&&value<=1);previous=value;}
 for(int count:{20,24,28,32,36,40,45,48,54})for(int i=0;i<count;++i){
  assert(TileProgress(TileLaunch(i,count)-.001f,i,count)==0);
  assert(TileProgress(TileLand(i,count)+.001f,i,count)==1);
  assert(TileLand(i,count)+.09f<=Duration+.0001f);
  if(i)assert(TileLaunch(i,count)>TileLaunch(i-1,count));
 }
 // Four room categories, six ranks: 24 frames partition the two-column atlas exactly.
 int bottom=0;
 for(int row=0;row<12;++row){int edge=0,height=0;
  for(int col=0;col<2;++col){const int tile=row*2+col;const auto f=RoomFrame(tile%4,tile/4,1448,1086);
   assert(f.x==edge&&f.y==bottom&&f.w>0&&f.h>0);edge=f.x+f.w;height=f.h;}
  assert(edge==1448);bottom+=height;
 }
 assert(bottom==1086);
 int count=0;
 for(int c=0;c<CastleMenuModel::Count;++c){assert(CastleFacilities::Counts[c]==4);
  for(int room=0;room<4;++room){
   CastleMenuModel::Progress p={};p.owned=1023;p.version=2;long long gold=100000;
   assert(CastleFacilities::Rooms[c][room].name);
   for(int lv=0;lv<5;++lv){
    assert(CastleFacilities::Output(c,room,lv)<CastleFacilities::Output(c,room,lv+1));
    const auto before=p;const auto balance=gold;
    assert(CastleMenuModel::Upgrade(p,c,room,true,gold));
    assert(balance-gold==CastleMenuModel::UpgradeCost(c,lv,true));
    for(int cc=0;cc<CastleMenuModel::Count;++cc)for(int rr=0;rr<5;++rr){
     assert(p.parts[cc][rr]==before.parts[cc][rr]);
     assert(p.rooms[cc][rr]==(rr==room?lv+1:before.rooms[cc][rr]));
    }
   }
   const auto funds=gold;assert(!CastleMenuModel::Upgrade(p,c,room,true,gold)&&gold==funds);
   assert(!CastleMenuModel::Upgrade(p,c,4,true,gold)&&gold==funds);++count;
  }
 }
 std::cout<<"PASS "<<count<<" shared-category facility upgrades, gold charges, MAX, untouched other categories, atlas partition and tile-flight endpoints\n";
}
