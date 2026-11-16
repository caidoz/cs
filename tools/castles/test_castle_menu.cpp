#include "../../Classes/CastleMenuModel.h"
#include "../../Classes/CastleTutorialModel.h"
#include "../../Classes/CastleArtilleryModel.h"
#include "../../Classes/Data/CastleRoomUpgrades.h"
#include "../../Classes/Data/CastleNpcPlacement.h"
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
        using namespace CastleTutorial;
        int step=Welcome;
        const Event sequence[]={Next,Entered,Placed,Setup,Started,ShopOpened,Bought,Started,Next};
        for(int i=0;i<Done;++i){
            assert(step==i);
            for(int e=Next;e<=Bought;++e)if(e!=sequence[i])assert(Advance(step,(Event)e)==step);
            step=Advance(step,sequence[i]);
            assert(Advance(step,sequence[i])==step);
        }
        assert(step==Done&&Advance(Done,Next)==Done);
        assert(CastleTutorial::Clamp(-100)==-1&&CastleTutorial::Clamp(100)==Done);
    }
    Progress p={};int old[]={2,1,0,3};Migrate(p,2,old);
    assert(p.version==2&&Owned(p,0)&&Owned(p,2)&&!Owned(p,3));
    assert(Completed(p,0)==20&&p.parts[2][3]==3);
    auto before=p;Migrate(p,0,old);assert(p.owned==before.owned&&p.parts[2][3]==3);
    long long cash=10000,gold=1000000;
    assert(!Buy(p,-1,cash)&&!Buy(p,10,cash)&&!Buy(p,3,cash));
    assert(!Upgrade(p,3,3,false,gold)&&!Upgrade(p,2,-1,false,gold));
    while(p.parts[2][3]<5)assert(Upgrade(p,2,3,false,gold));
    while(p.rooms[2][0]<5)assert(Upgrade(p,2,0,true,gold));
    assert(Unlocked(p,3)&&Buy(p,3,cash));
    long long paid=cash;assert(!Buy(p,3,cash)&&cash==paid);
    Progress fresh={};fresh.version=2;fresh.owned=1023;
    const int capacity=Inventory(fresh,3,40,4,999),equipment=Equipment(fresh,3,30);
    assert(Upgrade(fresh,3,0,true,gold)&&Inventory(fresh,3,40,4,999)==capacity);
    assert(Upgrade(fresh,3,1,true,gold)&&Equipment(fresh,3,30)==equipment&&Attack(fresh,3)==4);
    assert(Upgrade(fresh,3,2,true,gold)&&Health(fresh,3)==6);
    assert(Upgrade(fresh,3,3,true,gold)&&Defense(fresh,9)==4);
    paid=gold;assert(!Upgrade(fresh,3,4,true,gold)&&!Upgrade(fresh,3,4,false,gold)&&gold==paid);
    assert(All(fresh,3)==0);
    std::stringstream buffer;Writer writer={buffer};fresh.serialize(writer);
    Progress restored={};Reader reader={buffer};restored.serialize(reader);
    assert(restored.version==fresh.version&&restored.owned==fresh.owned);
    for(int c=0;c<10;++c)for(int i=0;i<5;++i)assert(restored.parts[c][i]==fresh.parts[c][i]&&restored.rooms[c][i]==fresh.rooms[c][i]);
    CastleArtillery::State attack;attack.Reset(3);attack.cooldownOverride=20;
    CastleArtillery::Point from={0,0},to={100,0};
    for(int i=0;i<19;++i)attack.Tick(1,1,from,to);
    assert(attack.charge==0);attack.Tick(1,1,from,to);assert(attack.charge==12&&attack.Progress()==1);
    puts("PASS castle purchase gates, migration, four facilities, unchanged capacity, serialization and artillery cooldown");
}
