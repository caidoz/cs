#include "../../Classes/DragPreviewModel.h"
#include "../../Classes/CastleArtilleryModel.h"
#include <cassert>
#include <cstdio>
using namespace DragPreview;
static Item Make(int key,int kind,int col,int row) {Item a;a.key=key;a.kind=kind;a.col=col;a.row=row;return a;}
static int Value(const std::vector<Effect>& e,int key,int rule) {for(const auto& p:e)if(p.target==key&&p.rule==rule)return p.value;return 0;}
int main() {
 auto sword=Make(1,Sword,1,1),helm=Make(2,Helm,2,2);
 assert(Adjacent(sword,helm));helm.col=3;assert(!Adjacent(sword,helm));helm.col=2;
 assert(!Adjacent(sword,sword));
 auto hollow=Make(3,Cannon,0,0);hollow.w=hollow.h=3;hollow.cells=1;
 auto far=Make(4,Helm,3,2);assert(!Adjacent(hollow,far));
 int pairs=0;
 for(int a=Sword;a<=Crew;++a)for(int b=Sword;b<=Crew;++b) {
  auto x=Make(1,a,1,1),y=Make(2,b,2,1);x.crew=y.crew=-1;
  const std::vector<Item> items={x,y};const auto before=items;
  auto e=Evaluate(items,8,0);++pairs;
  assert(items[0].col==before[0].col && items[1].col==before[1].col);
  if(a==Sword && b==Helm) assert(Value(e,1,SwordHaste)==15);
  if(a==Sword && b==Glove) assert(Value(e,1,SwordPower)==20);
  if(a==Gun || a==Boomerang || a==Neck || a==Ring) assert(Value(e,1,SwordHaste)==0 && Value(e,1,SwordPower)==0);
 }
 assert(pairs==225);
 auto captured=Make(40,Crew,2,1);captured.role=1;
 assert(Value(Evaluate({sword,captured},8,0),1,Coop)==3);
 auto glove=Make(3,Glove,0,1),rocky=Make(4,Crew,1,0);rocky.crew=36;
 auto a=Evaluate({sword,helm,glove,rocky},8,0);
 assert(Value(a,1,SwordPower)==20 && Value(a,1,Temper)==25);
 auto secondHelm=helm;secondHelm.key=5;
 assert(Value(Evaluate({sword,helm,secondHelm},8,0),1,SwordHaste)==15);
 auto shifted=rocky;shifted.col=6;
 auto changes=Diff(a,Evaluate({sword,helm,glove,shifted},8,0));bool loss=false;
 for(const auto& c:changes) if(c.after.target==1&&c.after.rule==Temper) loss=c.delta==-25;
 assert(loss);
 auto cannon=Make(8,Cannon,1,1),essence=Make(9,Essence,2,1);essence.level=10;
 assert(Value(Evaluate({cannon,essence},8,0),8,CannonHaste)==60);
 assert(Value(CannonEffects({cannon,essence},8),8,CannonHaste)==60);
 for(int kind=Sword;kind<=Crew;++kind) {
  auto source=Make(90,kind,2,1);source.level=3;source.price=7;source.value=101;
  if(kind==Crew) {source.crew=57;source.role=1;}
  const auto full=Evaluate({cannon,source},8,0),fast=CannonEffects({cannon,source},8);
  for(int rule=SwordHaste;rule<=SupplyPotential;++rule) assert(Value(full,8,rule)==Value(fast,8,rule));
 }
 for(int id=0;id<64;++id) for(int hero=0;hero<3;++hero) {
  auto ally=Make(20,Crew,0,0);ally.crew=id;
  auto p=AllyBalance::Profiles[id];
  ally.w=p.cols;ally.h=p.rows;
  const auto e=Evaluate({ally},8,hero);
  assert(!e.empty());
  auto duplicate=ally;duplicate.key=21;
  assert(Value(Evaluate({ally,duplicate},8,hero),21,Duplicate)==1);
 }
 auto alone=Make(20,Crew,1,1);alone.crew=0;
 assert(PlacementReady({alone,sword},alone,8,AllyBalance::Condition::Alone));
 auto neighbor=Make(21,Crew,2,2);neighbor.crew=1;
 assert(!PlacementReady({alone,neighbor},alone,8,AllyBalance::Condition::Alone));
 assert(PlacementReady({alone,neighbor},alone,8,AllyBalance::Condition::AdjacentCrew));
 auto pants=Make(30,Pants,0,0),crewA=Make(31,Crew,1,0),crewB=Make(32,Crew,6,0);crewA.crew=1;crewB.crew=2;
 const auto hp=Evaluate({pants,crewA,crewB},8,0);
 assert(Value(hp,31,CrewHp)==100&&Value(hp,32,CrewHp)==0);
 auto source=Make(41,Crew,0,0),target=Make(42,Crew,1,0);source.crew=50;target.crew=2;
 assert(Value(Evaluate({source,target},8,0),42,InspireTargets)<=40);
 CastleArtillery::State artillery;artillery.extraHits=2;artillery.charge=1;
 artillery.Tick(1,1,{0,0},{50,0});assert(artillery.pending==CastleArtillery::Of(0).hits+2);
 artillery.Reset(0);assert(artillery.extraHits==0);
 puts("PASS drag preview: 225 pairs, 64 allies x 3 heroes, masks, diagonals, losses, caps, per-crew HP and artillery hits");
}
