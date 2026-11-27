#pragma once
#include "Data/CastleFacilities.h"
namespace CastleMenuModel {
enum { Count=10, VisualCount=19, Categories=5, MaxLevel=5 };
// Count is the immutable on-disk array extent: ROBINDATA is also saved as raw bytes.
// Nine unused fifth-room slots carry the nine additional per-stage turret levels.
struct Progress {
 int version; unsigned int owned;
 unsigned char parts[Count][Categories],rooms[Count][Categories];
 template<class Archive> void serialize(Archive& ar) { ar(version,owned,parts,rooms); }
};
inline int Clamp(int c) { return c<0?0:c>=Count?Count-1:c; }
inline int ClampVisual(int c){return c<0?0:c>=VisualCount?VisualCount-1:c;}
inline unsigned char& Turret(Progress& p,int c){c=ClampVisual(c);return c<Count?p.parts[c][3]:p.rooms[c-Count][4];}
inline int TurretLevel(const Progress& p,int c){c=ClampVisual(c);return c<Count?p.parts[c][3]:p.rooms[c-Count][4];}
inline int RoomLevel(const Progress& p,int c,int i){return p.rooms[Clamp(c)][i];}
inline bool Owned(const Progress& p,int c) { return c>=0&&c<VisualCount&&(p.owned&(1u<<c))!=0; }
inline bool EnableAllCastles(Progress& p) {const unsigned all=(1u<<VisualCount)-1;const bool changed=p.owned!=all;p.owned=all;return changed;}
inline int Current(const Progress& p){int c=0;for(int i=0;i<VisualCount;++i)if(Owned(p,i))c=i;return c;}
inline int Completed(const Progress& p,int c) {int n=TurretLevel(p,c);for(int i=0;i<4;++i)n+=RoomLevel(p,c,i);return n;}
inline bool Unlocked(const Progress& p,int c) { return c==0||(c>0&&c<VisualCount&&Owned(p,c-1)&&Completed(p,c-1)==25); }
inline int Price(int c) { return 300*(ClampVisual(c)+1); }
inline int UpgradeCost(int c,int lv,bool room) { return (room?240:300*(ClampVisual(c)+1))*(lv+1); }
inline int GoldPrice(int c) { return Price(c)*100; }
inline bool BuyGold(Progress& p,int c,long long& gold) {
 if(c<0||c>=VisualCount||Owned(p,c)||!Unlocked(p,c)||gold<GoldPrice(c)) return false;
 gold-=GoldPrice(c); p.owned|=1u<<c; return true;
}
inline bool Buy(Progress& p,int c,long long& currency) {
 if(c<0||c>=VisualCount||Owned(p,c)||!Unlocked(p,c)||currency<Price(c)) return false;
 currency-=Price(c); p.owned|=1u<<c; return true;
}
inline bool Upgrade(Progress& p,int c,int i,bool room,long long& gold) {
 if(!room&&i!=3)return false;
 if(!Owned(p,c)||i<0||i>=(room?CastleFacilities::RoomCount:Categories)) return false;
 unsigned char& lv=room?p.rooms[Clamp(c)][i]:Turret(p,c);
 if(lv>=MaxLevel||gold<UpgradeCost(c,lv,room)) return false;
 gold-=UpgradeCost(c,lv,room); ++lv;
 if(room)for(int k=0;k<Count;++k)p.rooms[k][i]=lv;
 return true;
}
inline void Migrate(Progress& p,int current,const int* oldLevels) {
 if(p.version>=3)return;
 if(p.version<2){
 if(p.version<1){
  current=Clamp(current);p.owned=(1u<<(current+1))-1;
  for(int c=0;c<Count;++c)for(int i=0;i<Categories;++i){p.parts[c][i]=c<current?MaxLevel:0;p.rooms[c][i]=0;}
  for(int i=0;i<4;++i)p.parts[current][i]=(unsigned char)(oldLevels[i]<0?0:oldLevels[i]>5?5:oldLevels[i]);
 }
 unsigned char shared[4]={};
 for(int c=0;c<Count;++c)if(Owned(p,c)){
  for(int i=0;i<4;++i)if(p.rooms[c][i]>shared[i])shared[i]=p.rooms[c][i];
  if(p.parts[c][0]>shared[1])shared[1]=p.parts[c][0];
  if(p.rooms[c][4]>shared[1])shared[1]=p.rooms[c][4];
  if(p.parts[c][2]>shared[2])shared[2]=p.parts[c][2];
  if(p.parts[c][1]>shared[3])shared[3]=p.parts[c][1];
  for(int i=1;i<4;++i)if(p.parts[c][4]>shared[i])shared[i]=p.parts[c][4];
 }
 for(int c=0;c<Count;++c)for(int i=0;i<4;++i)p.rooms[c][i]=shared[i]>5?5:shared[i];
 p.version=2;
 }
 for(int c=0;c<VisualCount-Count;++c)p.rooms[c][4]=0;
 p.owned=(1u<<(ClampVisual(current)+1))-1u;
 p.version=3;
}
inline bool Advance(Progress& p,int current,long long& gold){
 const int next=current+1;if(current!=Current(p)||next>=VisualCount)return false;
 return BuyGold(p,next,gold);
}
inline int Inventory(const Progress& p,int c,int base,int per,int maximum) { c=Clamp(c);int n=base+c*per+20;return n>maximum?maximum:n; }
inline int Equipment(const Progress& p,int c,int physical) { return physical<1?1:physical; }
inline int Attack(const Progress& p,int c) { c=Clamp(c);return CastleFacilities::Output(c,1,p.rooms[c][1]); }
inline int Health(const Progress& p,int c) { c=Clamp(c);return CastleFacilities::Output(c,2,p.rooms[c][2]); }
inline int Defense(const Progress& p,int c) { c=Clamp(c);return CastleFacilities::Output(c,3,p.rooms[c][3]); }
inline int All(const Progress& p,int c) { return 0; }
inline int CannonDamageMultiplier(const Progress& p,int c) { return 100+10*TurretLevel(p,c); }
inline int CannonCooldownMultiplier(const Progress& p,int c) { return 100-3*TurretLevel(p,c); }
//턴 포격 계수(2026-11-22 ×4): 포 한 발 = 히어로 공격력 × 이 값. 번개 1개를 써서 쏘는 것이라 룰렛 한 번(블록 셋)을
//포기하는 값이어야 한다 - Lv0 200% 는 ★1 블록 셋 한 번 공격, Lv5 850% 는 검 Lv2 세 장 값. 옛 50~250% 는 ★1 블록 반 개였다.
inline int CannonTurnPercent(int level){static const int pct[6]={200,280,380,500,650,850};return pct[level<0?0:level>5?5:level];}
}
