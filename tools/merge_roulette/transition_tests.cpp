#include "../../Classes/MergeCastleTransition.h"
#include "../../Classes/CastleMenuModel.h"
#include <cassert>
#include <iostream>
int main(){
 using namespace MergeCastleTransition;
 assert(LobbyExit(0)==0&&LobbyExit(.4f)==1);
 assert(BoardEnter(.2f)==0&&BoardEnter(1.1f)==1);
 assert(ControlsEnter(0)==0&&ControlsEnter(.28f)==1&&ControlsEnter(Duration)==1);
 for(int n=0;n<=125;++n){const float t=n*.01f;assert(BoardEnter(t)>=0&&BoardEnter(t)<=1);}
 // Every castle emits distinct shots; even the largest grid settles before input unlocks.
 for(int count:{24,28,32,36,40,45,48,54})for(int i=0;i<count;++i){
  assert(TileProgress(TileLaunch(i,count)-.001f,i,count)==0);
  assert(TileProgress(TileLand(i,count)+.001f,i,count)==1);
  assert(TileLand(i,count)+.09f<=Duration+.0001f);
  if(i)assert(TileLaunch(i,count)>TileLaunch(i-1,count));
 }
 // Integer crop edges partition every texel, including non-divisible atlases.
 for(int r=0;r<6;++r){int edge=0;for(int c=0;c<5;++c){auto f=RoomFrame(c,r,1448,1086);assert(f.x==edge&&f.w>0&&f.h>0);edge=f.x+f.w;}assert(edge==1448);}
 CastleMenuModel::Progress p={};p.owned=1023;p.version=1;
 int count=0;
 for(int c=0;c<10;++c){assert(CastleFacilities::Counts[c]==5);
  for(int r=0;r<5;++r){assert(CastleFacilities::Rooms[c][r].name&&CastleFacilities::Rooms[c][r].basePerHour>0);
   const auto before=p;long long gold=100000;
   for(int lv=0;lv<5;++lv){assert(CastleMenuModel::Upgrade(p,c,r,true,gold));assert(p.rooms[c][r]==lv+1);}
   const auto funds=gold;assert(!CastleMenuModel::Upgrade(p,c,r,true,gold)&&gold==funds);
   for(int cc=0;cc<10;++cc)for(int rr=0;rr<5;++rr)if(cc!=c||rr!=r)assert(p.rooms[cc][rr]==before.rooms[cc][rr]);
   ++count;
  }
 }
 std::cout<<"PASS "<<count<<" independent facilities, Lv0..5, MAX, unchanged neighbor saves, atlas crops, transition endpoints\n";
}
