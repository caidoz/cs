#include "../../Classes/CastleMenuModel.h"
#include "../../Classes/MergeCastleTransition.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace CastleMenuModel;
int main(){
 int old[5]={};
 // Historical arrays keep their binary dimensions, while the schema migrates once.
 Progress legacy={};legacy.version=1;legacy.owned=7;
 legacy.rooms[0][0]=2;legacy.rooms[1][1]=3;legacy.parts[2][1]=4;
 legacy.parts[0][2]=2;legacy.parts[2][3]=5;legacy.rooms[1][4]=4;
 Migrate(legacy,0,old);assert(legacy.version==2);
 for(int c=0;c<Count;++c){assert(legacy.rooms[c][0]==2&&legacy.rooms[c][1]==4&&legacy.rooms[c][2]==2&&legacy.rooms[c][3]==4);}
 assert(legacy.parts[2][3]==5&&legacy.parts[0][3]==0);
 const auto migrated=legacy;Migrate(legacy,0,old);assert(std::memcmp(&migrated,&legacy,sizeof legacy)==0);
 int transactions=0;
 for(int c=0;c<Count;++c)for(int room=0;room<4;++room){
  Progress p={};p.version=2;p.owned=1023;
  for(int lv=0;lv<5;++lv){
   long long gold=UpgradeCost(c,lv,true)-1;assert(!Upgrade(p,c,room,true,gold)&&p.rooms[c][room]==lv);
   gold=UpgradeCost(c,lv,true);assert(Upgrade(p,c,room,true,gold)&&gold==0);++transactions;
   for(int k=0;k<Count;++k)for(int r=0;r<4;++r)assert(p.rooms[k][r]==(r==room?lv+1:0));
   assert(Attack(p,c)==(room==1?(lv+1)*4:0));
   assert(Health(p,c)==(room==2?(lv+1)*6:0));
   assert(Defense(p,c)==(room==3?(lv+1)*4:0));
   assert(CastleFacilities::Bonus(p,c,false)==(room==0?(lv+1)*25:0));
   assert(CastleFacilities::Bonus(p,c,true)==0);
   auto f=MergeCastleTransition::RoomFrame(room,lv+1,1448,1086);
   assert(f.w==362&&f.h==181&&f.x>=0&&f.y>=0&&f.x+f.w<=1448&&f.y+f.h<=1086);
  }
  long long gold=999999;assert(!Upgrade(p,c,room,true,gold)&&gold==999999);
  assert(!Upgrade(p,c,4,true,gold)&&gold==999999);
 }
 for(int c=0;c<Count;++c){
  Progress p={};p.version=2;p.owned=1023;
  for(int lv=0;lv<5;++lv){long long gold=UpgradeCost(c,lv,false);assert(Upgrade(p,c,3,false,gold)&&gold==0);
   for(int k=0;k<Count;++k)assert(p.parts[k][3]==(k==c?lv+1:0));
   assert(Attack(p,c)==0&&Health(p,c)==0&&Defense(p,c)==0);
   assert(CannonTurnPercent(lv+1)>CannonTurnPercent(lv));
  }
  long long gold=999999;assert(!Upgrade(p,c,0,false,gold)&&gold==999999);
 }
 assert(transactions==200);
 std::puts("PASS 200 shared facility transactions, 50 independent turret upgrades, migration, isolated effects and all atlas bounds");
}
