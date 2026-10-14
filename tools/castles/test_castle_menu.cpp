#include "../../Classes/CastleMenuModel.h"
#include "../../Classes/CastleArtilleryModel.h"
#include <cassert>
#include <cstdio>
#include <sstream>
using namespace CastleMenuModel;
struct Writer {
    std::stringstream& s;
    template<class T> void operator()(const T& value) { s.write((const char*)&value,sizeof(value)); }
    template<class T,class... Rest> void operator()(const T& value,const Rest&... rest) { (*this)(value); (*this)(rest...); }
};
struct Reader {
    std::stringstream& s;
    template<class T> void operator()(T& value) { s.read((char*)&value,sizeof(value)); }
    template<class T,class... Rest> void operator()(T& value,Rest&... rest) { (*this)(value); (*this)(rest...); }
};
int main() {
    {
        Progress dual={}; dual.version=1; dual.owned=1;
        long long coin=10000,gold=1000000;
        assert(!BuyGold(dual,1,gold)&&gold==1000000);
        assert(!BuyInstant(dual,2,coin)&&coin==10000);
        assert(BuyInstant(dual,1,coin)&&coin==10000-Price(1));
        const long long before=coin;
        assert(UpgradePaid(dual,1,3,false,coin)&&dual.parts[1][3]==1);
        assert(coin==before-PaidUpgradeCost(1,0,false));
        const long long rating=StructuralPower(dual,1,30);
        assert(UpgradePaid(dual,1,1,true,coin)&&StructuralPower(dual,1,30)>rating);
        long long empty=0; assert(!UpgradePaid(dual,1,3,false,empty)&&dual.parts[1][3]==1);
        dual.parts[1][3]=5; assert(!UpgradePaid(dual,1,3,false,coin));
        for(int i=0;i<5;++i) dual.parts[1][i]=5;
        assert(BuyGold(dual,2,gold)&&gold==1000000-GoldPrice(2));
    }
    Progress p={}; int old[]={2,1,0,3}; Migrate(p,2,old);
    assert(p.version==1&&Owned(p,0)&&Owned(p,1)&&Owned(p,2)&&!Owned(p,3));
    assert(Completed(p,0)==25&&p.parts[2][0]==2&&p.parts[2][3]==3);
    auto before=p; Migrate(p,0,old); assert(p.owned==before.owned&&p.parts[2][3]==3);
    long long cash=10000,gold=1000000;
    assert(!Buy(p,-1,cash)&&!Buy(p,10,cash)&&!Buy(p,3,cash)&&cash==10000);
    assert(!Upgrade(p,3,0,false,gold)&&!Upgrade(p,2,-1,false,gold)&&gold==1000000);
    for(int i=0;i<5;++i) while(p.parts[2][i]<5) assert(Upgrade(p,2,i,false,gold));
    assert(Unlocked(p,3)&&Buy(p,3,cash)&&cash==10000-Price(3));
    long long paid=cash; assert(!Buy(p,3,cash)&&cash==paid);
    int cap=Inventory(p,3,40,4,999),equipment=Equipment(p,3,30);
    assert(Upgrade(p,3,0,true,gold)&&Inventory(p,3,40,4,999)==cap+4);
    assert(Equipment(p,3,30)==equipment);
    assert(Upgrade(p,3,1,true,gold)&&Equipment(p,3,30)==equipment+1);
    assert(Upgrade(p,3,2,true,gold)&&Health(p,3)==2);
    assert(Upgrade(p,3,3,true,gold)&&Defense(p,3)==2);
    assert(Upgrade(p,3,4,true,gold)&&Attack(p,3)==2);
    assert(Upgrade(p,3,4,false,gold)&&All(p,3)==1);
    for(int i=0;i<5;++i) while(p.parts[3][i]<5) assert(Upgrade(p,3,i,false,gold));
    paid=gold; assert(!Upgrade(p,3,0,false,gold)&&gold==paid);
    long long empty=0; assert(!Buy(p,4,empty)&&!Upgrade(p,3,0,true,empty)&&empty==0);
    std::stringstream buffer;
    Writer writer={buffer}; p.serialize(writer);
    Progress restored={}; Reader reader={buffer}; restored.serialize(reader);
    assert(restored.version==p.version&&restored.owned==p.owned);
    for(int c=0;c<10;++c) for(int i=0;i<5;++i) assert(restored.parts[c][i]==p.parts[c][i]&&restored.rooms[c][i]==p.rooms[c][i]);
    CastleArtillery::State attack; attack.Reset(3); attack.cooldownOverride=20;
    CastleArtillery::Point from={0,0},to={100,0};
    for(int i=0;i<19;++i) attack.Tick(1,1,from,to);
    assert(attack.charge==0); attack.Tick(1,1,from,to); assert(attack.charge==12&&attack.Progress()==1);
    puts("Castle menu: migration, purchase gates, spending, capacity, team buffs, persistence and cannon cooldown OK");
}
