#include "../../Classes/StageAllyBalanceModel.h"
#include "../../Classes/Data/AllyBalanceData.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace AllyBalance;
int main() {
    for(int id=0;id<64;++id) {
        const auto& p=Profiles[id];assert(p.id==id && p.npc>=360 && p.name[0] && p.ability[0]);
        assert(p.attackMs>=2400 && p.attackMs<=5200 && p.attackPercent>=75 && p.attackPercent<=130);
        assert(p.cols>=1 && p.cols<=2 && p.rows>=1 && p.rows<=2);
        for(int previous=0;previous<id;++previous) {
            assert(p.npc!=Profiles[previous].npc && std::strcmp(p.ability,Profiles[previous].ability)!=0);
        }
        for(const auto& s:p.synergy) assert(s.cooldownMs>=3000 && s.cooldownMs<=16000);
    }
    assert(!Get(-1) && !Get(64));
    StatusState burn;burn.Apply(Burning,100,60);assert(burn.stacks[Burning]==5);
    int damage=0;for(int t=0;t<240;++t) damage+=burn.Tick(true,60);
    assert(damage==60 && !burn.Any());
    StatusState poison;poison.Apply(Poisoned,20,60);assert(poison.stacks[Poisoned]==6);
    for(int t=0;t<100;++t) poison.Tick(false,60);
    assert(poison.remaining[Poisoned]==480);
    damage=0;for(int t=0;t<480;++t) damage+=poison.Tick(true,60);
    assert(damage==96 && !poison.Any());
    StatusState shock;shock.Apply(Shocked,20,60);
    for(int t=0;t<120;++t) assert(shock.Tick(true,60)==0);
    assert(shock.Consume(Shocked)==4 && shock.Consume(Shocked)==0);
    StatusState frost;
    for(int i=0;i<20;++i) frost.Apply(Chilled,1,60);
    assert(frost.SlowPermille()==150 && frost.chillResistance==60 && frost.remaining[Chilled]==72);
    StatusState bleed;bleed.Apply(Bleeding,100,60);
    assert(bleed.Bleed(1)==12 && bleed.Bleed(1)==0 && bleed.Bleed(2)==12);
    bleed.Apply(Exposed,20,60);assert(bleed.Consume(Exposed)==1 && bleed.Consume(Exposed)==0);
    CompanionState state;
    for(int t=0;t<100;++t) state.Tick(true,true,10,5);
    assert(state.abilityClock==10 && state.linkClock==5);
    assert(state.Observe(0,1,false) && !state.Observe(0,1,false) && !state.Observe(0,2,true));
    state.Tick(false,true,10,5);assert(state.abilityClock==10);
    state.nextShotBonus=40;state.Tick(true,false,10,5);
    assert(!state.abilityClock && !state.linkClock && !state.nextShotBonus);
    std::puts("PASS 64 profiles / 192 synergies / status caps, expiry, DOT, shock consumption, boss resistance, bleed dedup, pause and removal");
}
