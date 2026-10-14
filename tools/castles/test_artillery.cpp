#include "../../Classes/CastleArtilleryModel.h"
#include <cassert>
#include <cstdio>
using namespace CastleArtillery;
int main() {
    Point from={10,50},target={350,100};
    assert(SegmentHits({0,0},{100,0},{50,0},1));
    assert(!SegmentHits({0,0},{100,0},{50,10},1));
    float previousDps=0;
    for(int grade=0;grade<10;++grade) {
        State state; state.Reset(grade);
        const Profile& p=Of(grade);
        const float dps=p.damagePercent*p.hits/(float)(p.cooldown+State::ChargeFrames+p.hits*p.interval);
        assert(dps>previousDps); previousDps=dps;
        assert(state.Progress()==0);
        for(int t=0;t<p.cooldown-1;++t) assert(!state.Tick(1,3,from,target));
        assert(state.charge==0);
        state.Tick(1,3,from,target); assert(state.charge==State::ChargeFrames);
        for(int t=0;t<State::ChargeFrames;++t) state.Tick(1,3,from,target);
        assert(state.pending==p.hits);
        int fired=0,hit=0;
        for(int t=0;t<p.hits*p.interval+p.flight+40;++t) {
            if(state.pending) fired+=state.Tick(1,3,from,target)?1:0;
            for(int i=0;i<State::Capacity;++i) {
                Shot& shot=state.shots[i];
                if(!shot.active) continue;
                if(shot.impact) { if(--shot.impact==0) shot.active=false; continue; }
                // Moving targets still get hit once, never again while exploding.
                Point moving={target.x+t*2,target.y+t};
                if(state.Move(shot,moving,1)) ++hit;
            }
        }
        assert(fired==p.hits && hit==p.hits);
        state.Reset(grade); assert(state.Progress()==0 && state.pending==0);
        // With no foe, full charge waits without starting or consuming a volley.
        for(int t=0;t<p.cooldown+40;++t) state.Tick(-1,0,from,target);
        assert(state.cooldown==p.cooldown && !state.pending && !state.charge);
        Shot a={}; a.active=true;a.flight=p.flight;a.from=from;
        Point end=Position(p.kind,from,target,1,2);
        assert(end.x==target.x && end.y==target.y);
        state.pending=p.hits; state.Tick(-1,0,from,target); assert(state.pending==0);
    }
    State full;
    for(int i=0;i<State::Capacity;++i) assert(full.Spawn(1,1,from,target));
    assert(!full.Spawn(1,1,from,target));
    assert(ClampGrade(-1)==0 && ClampGrade(99)==9);
    for(int level=0;level<6;++level) {
        if(level) assert(ProjectileScale(level)>ProjectileScale(level-1));
        State upgrade; upgrade.upgrade=level;
        assert(upgrade.Spawn(1,1,from,target));
        assert(upgrade.shots[0].upgrade==level);
        upgrade.upgrade=0;
        assert(upgrade.shots[0].upgrade==level); // In-flight visuals retain the launch tier.
    }
    assert(ClampUpgrade(-1)==0 && ClampUpgrade(99)==5);
    std::puts("10 artillery types: timing, burst counts, moving-target collisions, reset and capacity OK");
}
