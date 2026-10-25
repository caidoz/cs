#include "../../Classes/StageAllyLinkModel.h"
#include <cassert>
#include <cstdio>
using namespace StageAllyLink;
int main() {
    Runtime state;state.Reset(4,60);
    const bool all[EffectCount]={true,true,true,true},none[EffectCount]={};
    for(int i=0;i<1200;++i) state.Tick(true,all);
    assert(state.Progress(Repair)==1 && state.Progress(Heal)==1);
    Event hit={4,10,RobinHit,false};
    assert(state.Accept(Heal,hit,true,true,15));
    assert(!state.Accept(Heal,hit,true,true,15));
    for(int i=0;i<1000;++i) state.Tick(true,all);
    assert(!state.Accept(Heal,hit,true,true,15)); // not replayable after cooldown
    Event derived={4,11,RobinHit,true};
    assert(!state.Accept(Heal,derived,true,true,15));
    Event oldRun={3,12,RobinHit,false};
    assert(!state.Accept(Heal,oldRun,true,true,15));
    Event fullHealth={4,13,RobinHit,false};
    assert(!state.Accept(Heal,fullHealth,true,false,15));
    assert(!state.Accept(Heal,fullHealth,true,true,15));
    Event returned={4,14,MaxReturned,false};
    assert(state.Accept(Heal,returned,true,true,15));
    for(int i=0;i<90;++i) state.Tick(true,all);
    const int elapsed=state.elapsed[Heal],flash=state.flash[Heal];
    for(int i=0;i<100;++i) state.Tick(false,all);
    assert(state.elapsed[Heal]==elapsed && state.flash[Heal]==flash);
    assert(!state.Accept(SupportShot,{4,15,DianaShot,false},false,true,15));
    state.Tick(true,none);
    for(int i=0;i<EffectCount;++i) assert(state.elapsed[i]==0 && state.flash[i]==0);
    state.Reset(5,60);
    for(int i=0;i<EffectCount;++i) {
        assert(state.Progress((Effect)i)==0);
        for(int k=0;k<EventCount;++k) assert(state.seen[i][k]==0);
    }
    std::puts("PASS ally links: cooldown cap, low-health eligibility, dedup, recursion, stale run, pause, removal and reset");
}
