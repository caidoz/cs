#pragma once
namespace CastleMenuModel {
enum { Count=10, Categories=5, MaxLevel=5 };
struct Progress {
 int version; unsigned int owned;
 unsigned char parts[Count][Categories],rooms[Count][Categories];
 template<class Archive> void serialize(Archive& ar) { ar(version,owned,parts,rooms); }
};
inline int Clamp(int c) { return c<0?0:c>=Count?Count-1:c; }
inline bool Owned(const Progress& p,int c) { return c>=0&&c<Count&&(p.owned&(1u<<c))!=0; }
inline int Completed(const Progress& p,int c) { int n=0; for(int i=0;i<Categories;++i) n+=p.parts[Clamp(c)][i]; return n; }
inline bool Unlocked(const Progress& p,int c) { return c==0||(c>0&&c<Count&&Owned(p,c-1)&&Completed(p,c-1)==25); }
inline int Price(int c) { return 300*(Clamp(c)+1); }
inline int UpgradeCost(int c,int lv,bool room) { return (room?240:300)*(Clamp(c)+1)*(lv+1); }
inline int PaidUpgradeCost(int c,int lv,bool room) { return (UpgradeCost(c,lv,room)+99)/100; }
inline int GoldPrice(int c) { return Price(c)*100; }
inline bool BuyInstant(Progress& p,int c,long long& currency) {
 if(c<=0||c>=Count||Owned(p,c)||!Owned(p,c-1)||currency<Price(c)) return false;
 currency-=Price(c); p.owned|=1u<<c; return true;
}
inline bool BuyGold(Progress& p,int c,long long& gold) {
 if(c<0||c>=Count||Owned(p,c)||!Unlocked(p,c)||gold<GoldPrice(c)) return false;
 gold-=GoldPrice(c); p.owned|=1u<<c; return true;
}
inline bool UpgradePaid(Progress& p,int c,int i,bool room,long long& currency) {
 if(!Owned(p,c)||i<0||i>=Categories) return false;
 unsigned char& lv=room?p.rooms[c][i]:p.parts[c][i];
 if(lv>=MaxLevel||currency<PaidUpgradeCost(c,lv,room)) return false;
 currency-=PaidUpgradeCost(c,lv,room); ++lv; return true;
}
inline bool Buy(Progress& p,int c,long long& currency) {
 if(Owned(p,c)||!Unlocked(p,c)||currency<Price(c)) return false;
 currency-=Price(c); p.owned|=1u<<c; return true;
}
inline bool Upgrade(Progress& p,int c,int i,bool room,long long& gold) {
 if(!Owned(p,c)||i<0||i>=Categories) return false;
 unsigned char& lv=room?p.rooms[c][i]:p.parts[c][i];
 if(lv>=MaxLevel||gold<UpgradeCost(c,lv,room)) return false;
 gold-=UpgradeCost(c,lv,room); ++lv; return true;
}
inline void Migrate(Progress& p,int current,const int* oldLevels) {
 if(p.version==1) return;
 current=Clamp(current); p.owned=(1u<<(current+1))-1;
 for(int c=0;c<Count;++c) for(int i=0;i<Categories;++i) { p.parts[c][i]=c<current?MaxLevel:0; p.rooms[c][i]=0; }
 for(int i=0;i<4;++i) p.parts[current][i]=(unsigned char)(oldLevels[i]<0?0:oldLevels[i]>5?5:oldLevels[i]);
 p.version=1;
}
inline int Inventory(const Progress& p,int c,int base,int per,int maximum) { c=Clamp(c); int n=base+c*per+p.rooms[c][0]*4; return n>maximum?maximum:n; }
inline int Equipment(const Progress& p,int c,int physical) { int n=physical-(MaxLevel-p.rooms[Clamp(c)][1]); return n<1?1:n; }
inline int Attack(const Progress& p,int c) { c=Clamp(c); return p.parts[c][0]+p.parts[c][3]+p.rooms[c][4]*2; }
inline int Health(const Progress& p,int c) { c=Clamp(c); return p.parts[c][2]*2+p.rooms[c][2]*2; }
inline int Defense(const Progress& p,int c) { c=Clamp(c); return p.parts[c][1]*2+p.rooms[c][3]*2; }
inline int All(const Progress& p,int c) { return p.parts[Clamp(c)][4]; }
// Castle rating: chassis baseline, installed upgrades and usable combat cells.
// This score complements hero/crew stats and cannon DPS; it is not damage.
inline long long StructuralPower(const Progress& p,int c,int physical) {
 c=Clamp(c); long long value=(c+1)*1000LL+Equipment(p,c,physical)*25LL;
 for(int i=0;i<Categories;++i) value+=(c+1)*(p.parts[c][i]*100LL+p.rooms[c][i]*80LL);
 return value;
}
}
