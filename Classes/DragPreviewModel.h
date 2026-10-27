#pragma once
#include <algorithm>
#include <cstdlib>
#include <vector>
#include "Data/AllyBalanceData.h"

// Read-only inventory graph. No access to actors, cooldowns, RNG or save data.
namespace DragPreview {
enum Kind { Sword, Gun, Boomerang, Helm, Armor, Glove, Pants, Boots, Shield,
 Neck, Ring, Cannon, Essence, Recipe, Crew, Other };
struct Item {
 int key=0,kind=Other,type=-1,grade=0,detail=0,col=0,row=0,w=1,h=1,cells=0;
 int level=1,value=0,price=0,crew=-1,role=-1;
 bool equipped=false;
};
inline bool Cell(const Item& p,int x,int y) {
 return x>=0 && y>=0 && x<p.w && y<p.h && (!p.cells || (p.cells&(1u<<(y*4+x))));
}
inline bool Weapon(int k) {return k==Sword||k==Gun||k==Boomerang;}
inline bool Defense(int k) {return k==Helm||k==Armor||k==Glove||k==Pants||k==Boots||k==Shield;}
inline bool Adjacent(const Item& a,const Item& b) {
 if(a.key==b.key) return false;
 for(int y=0;y<a.h;++y) for(int x=0;x<a.w;++x) if(Cell(a,x,y))
  for(int yy=0;yy<b.h;++yy) for(int xx=0;xx<b.w;++xx) if(Cell(b,xx,yy))
   if(std::abs(a.col+x-b.col-xx)<=1 && std::abs(a.row+y-b.row-yy)<=1) return true;
 return false;
}
enum Rule { SwordHaste, SwordPower, Temper, Coop, ArmorPower, ShieldHaste, TacticHaste,
 CrewHp, CannonDamage, CannonScale, CannonHaste, CannonHits, FireAmmo, IceAmmo, ThunderAmmo,
 Placement, InspireTargets, KingTactic, DurakTactic, ShockChain, ExposeChain, Duplicate, SupplyPotential };
struct Effect {int target,rule,value,providers,source;};
inline void Add(std::vector<Effect>& effects,int target,int rule,int value,int source,bool sum=false) {
 for(auto& e:effects) if(e.target==target && e.rule==rule) {
  e.value=sum?e.value+value:std::max(e.value,value);++e.providers;return;
 }
 effects.push_back({target,rule,value,1,source});
}
inline bool Has(const std::vector<Item>& items,const Item& target,int kind) {
 for(const auto& source:items) if(source.kind==kind && Adjacent(source,target)) return true;
 return false;
}
inline bool FirstCrew(const std::vector<Item>& items,const Item& p) {
 for(const auto& q:items) {if(q.key==p.key) return true;if(q.kind==Crew && q.crew==p.crew) return false;}
 return true;
}
inline bool PlacementReady(const std::vector<Item>& items,const Item& p,int width,AllyBalance::Condition c) {
 using C=AllyBalance::Condition;
 bool crew=false,weapon=false;
 for(const auto& q:items) if(Adjacent(p,q)) {
  crew=crew||(q.kind==Crew && p.crew!=q.crew);weapon=weapon||Weapon(q.kind);
 }
 switch(c) {
 case C::Front:return p.col*2+p.w>=width;
 case C::Back:return p.col*2+p.w<width;
 case C::AdjacentWeapon:return weapon;
 case C::AdjacentCrew:return crew;
 case C::Alone:return !crew;
 default:return true; // Combat conditions are described as waiting by the UI.
 }
}
inline void CannonSource(std::vector<Effect>& out,const Item& p,const Item& q) {
   const int level=std::max(1,q.level);
   if(q.kind==Sword) {
    Add(out,p.key,CannonDamage,q.value*35/100*level,q.key,true);
    Add(out,p.key,CannonScale,12*level,q.key,true);
   } else if(q.kind==Essence) {
    switch(q.detail%4) {
    case 0:Add(out,p.key,CannonHaste,15*level,q.key,true);break;
    case 1:Add(out,p.key,CannonScale,18*level,q.key,true);Add(out,p.key,FireAmmo,level,q.key,true);break;
    case 2:Add(out,p.key,CannonHaste,12*level,q.key,true);Add(out,p.key,IceAmmo,level,q.key,true);break;
    case 3:Add(out,p.key,CannonHits,level,q.key,true);Add(out,p.key,ThunderAmmo,level,q.key,true);break;
    }
   } else if(q.kind==Crew && q.role==1) {
    Add(out,p.key,CannonHaste,20,q.key,true);Add(out,p.key,CannonScale,15,q.key,true);
    Add(out,p.key,CannonHits,q.crew==57?2:1,q.key,true);
   } else if(q.kind==Armor||q.kind==Shield||q.kind==Helm||q.kind==Boots) {
    Add(out,p.key,CannonDamage,q.price*12*level,q.key,true);Add(out,p.key,CannonScale,10,q.key,true);
   }
}
inline std::vector<Effect> CannonEffects(const std::vector<Item>& items,int key) {
 std::vector<Effect> out;const Item* cannon=nullptr;
 for(const auto& p:items) if(p.key==key && p.kind==Cannon) {cannon=&p;break;}
 if(!cannon) return out;
 for(const auto& q:items) {
  if(q.kind==Crew && q.crew>=0 && q.crew<64 && !FirstCrew(items,q)) continue;
  if(Adjacent(*cannon,q)) CannonSource(out,*cannon,q);
 }
 for(auto& e:out) if(e.rule==CannonHaste) e.value=std::min(60,e.value);
 return out;
}
inline std::vector<Effect> Evaluate(const std::vector<Item>& items,int width,int hero) {
 std::vector<Effect> out;
 for(const auto& p:items) {
  if(p.kind==Crew && p.crew>=0 && p.crew<64) {
   if(!FirstCrew(items,p)) {Add(out,p.key,Duplicate,1,p.key);continue;}
   const auto& profile=AllyBalance::Profiles[p.crew];
   Add(out,p.key,Placement,PlacementReady(items,p,width,profile.condition)?1:0,p.key);
   const auto& link=profile.synergy[std::max(0,std::min(2,hero))];using A=AllyBalance::Action;
   if((profile.action==A::Shock && link.action==A::Discharge)||(profile.action==A::Discharge && link.action==A::Shock))
    Add(out,p.key,ShockChain,1,p.key);
   if((profile.action==A::Expose && link.action==A::Strike && link.power>=150)||
      (profile.action==A::Strike && profile.power>=150 && link.action==A::Expose)) Add(out,p.key,ExposeChain,25,p.key);
  }
  for(const auto& q:items) {
   if(p.key==q.key) continue;
   if(q.kind==Crew && q.crew>=0 && q.crew<64 && !FirstCrew(items,q)) continue;
   if(p.kind==Recipe && q.kind==Crew && q.crew==63) Add(out,p.key,KingTactic,25,q.key);
   if(p.kind==Recipe && q.kind==Crew && q.crew==50) Add(out,p.key,DurakTactic,1,q.key);
   if((p.kind==Sword || p.equipped) && q.kind==Crew && q.crew>=0 && q.crew<64) {
    const auto& profile=AllyBalance::Profiles[q.crew];const auto& link=profile.synergy[std::max(0,std::min(2,hero))];
    if(profile.action==AllyBalance::Action::Supply && PlacementReady(items,q,width,profile.condition))
     Add(out,p.key,SupplyPotential,std::min(20,profile.power),q.key,true);
    if(link.action==AllyBalance::Action::Supply) Add(out,p.key,SupplyPotential,std::min(20,link.power),q.key,true);
   }
   if(p.kind==Crew && q.kind==Crew && p.crew>=0 && p.crew<64 && q.crew>=0 && q.crew<64 && FirstCrew(items,p)) {
    const auto& a=AllyBalance::Profiles[p.crew];const auto& b=AllyBalance::Profiles[q.crew];
    const int h=std::max(0,std::min(2,hero));
    using A=AllyBalance::Action;
    if((a.action==A::Discharge||a.synergy[h].action==A::Discharge) && (b.action==A::Shock||b.synergy[h].action==A::Shock))
     Add(out,p.key,ShockChain,1,q.key);
    if((a.action==A::Strike && a.power>=150 || a.synergy[h].action==A::Strike && a.synergy[h].power>=150)
       && (b.action==A::Expose || b.synergy[h].action==A::Expose)) Add(out,p.key,ExposeChain,25,q.key);
   }
   if(!Adjacent(p,q)) continue;
   if(p.kind==Sword) {
    if(q.kind==Helm) Add(out,p.key,SwordHaste,15,q.key);
    if(q.kind==Glove && !p.equipped) Add(out,p.key,SwordPower,20,q.key);
    if(q.kind==Crew && q.crew==36 && !p.equipped) Add(out,p.key,Temper,25,q.key);
    if(q.kind==Crew && !p.equipped) Add(out,p.key,Coop,3,q.key);
   }
   if(p.kind==Armor && (q.kind==Shield||q.kind==Helm||q.kind==Boots||q.kind==Pants)) Add(out,p.key,ArmorPower,15,q.key,true);
   if(Defense(p.kind) && q.kind==Boots) Add(out,p.key,ShieldHaste,20,q.key);
   if(p.kind==Recipe && q.kind==Helm) Add(out,p.key,TacticHaste,20,q.key);
   if(p.kind==Crew && q.kind==Pants) Add(out,p.key,CrewHp,100,q.key);
   if(p.kind==Crew && q.kind==Crew && p.crew!=q.crew && p.crew>=0 && p.crew<64 && q.crew>=0 && q.crew<64) {
    const auto& profile=AllyBalance::Profiles[q.crew];
    const auto& link=profile.synergy[std::max(0,std::min(2,hero))];
    using A=AllyBalance::Action;
    if(profile.action==A::Inspire && PlacementReady(items,q,width,profile.condition))
     Add(out,p.key,InspireTargets,profile.power,q.key,true);
    if(link.action==A::Inspire) Add(out,p.key,InspireTargets,link.power,q.key,true);
   }
   if(p.kind!=Cannon) continue;
   CannonSource(out,p,q);
  }
 }
 for(auto& e:out) {if(e.rule==CannonHaste)e.value=std::min(60,e.value);if(e.rule==InspireTargets)e.value=std::min(40,e.value);if(e.rule==SupplyPotential)e.value=std::min(30,e.value);}
 return out;
}
struct Change {Effect before,after;int delta;};
inline std::vector<Change> Diff(const std::vector<Effect>& a,const std::vector<Effect>& b) {
 std::vector<Change> out;
 for(const auto& old:a) {
  Effect next={old.target,old.rule,0,0,old.source};
  for(const auto& e:b) if(e.target==old.target && e.rule==old.rule) {next=e;break;}
  out.push_back({old,next,next.value-old.value});
 }
 for(const auto& e:b) {
  bool found=false;for(const auto& old:a) if(old.target==e.target&&old.rule==e.rule) {found=true;break;}
  if(!found) out.push_back({{e.target,e.rule,0,0,e.source},e,e.value});
 }
 return out;
}
}
