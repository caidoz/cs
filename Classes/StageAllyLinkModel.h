#pragma once
#include <cstdint>

namespace StageAllyLink {
enum EventKind { RobinHit, DianaShot, MaxThrow, MaxHit, MaxReturning, MaxReturned, CombatTick, EventCount };
enum Effect { Repair, SmithLink, Heal, SupportShot, EffectCount };
struct Event {
    unsigned run;
    std::uint64_t id;
    EventKind kind;
    bool derived;
};
struct Runtime {
    unsigned run;
    int cooldown[EffectCount], elapsed[EffectCount], flash[EffectCount];
    std::uint64_t seen[EffectCount][EventCount];
    Runtime() { Reset(0,60); }
    void Reset(unsigned nextRun,int fps) {
        run=nextRun;
        const int seconds[EffectCount]={8,8,15,3};
        for(int e=0;e<EffectCount;++e) {
            cooldown[e]=seconds[e]*fps;elapsed[e]=flash[e]=0;
            for(int k=0;k<EventCount;++k) seen[e][k]=0;
        }
    }
    void Tick(bool running,const bool present[EffectCount]) {
        if(!running) return;
        for(int e=0;e<EffectCount;++e) {
            if(!present[e]) {elapsed[e]=flash[e]=0;continue;}
            if(elapsed[e]<cooldown[e]) ++elapsed[e];
            if(flash[e]>0) --flash[e];
        }
    }
    bool Accept(Effect effect,const Event& event,bool running,bool eligible,int flashFrames) {
        if(!running || event.run!=run || !event.id || event.derived
           || effect<0 || effect>=EffectCount || event.kind<0 || event.kind>=EventCount) return false;
        std::uint64_t& last=seen[effect][event.kind];
        if(event.id<=last) return false;
        // Even an ineligible event cannot be replayed later when a clock is full.
        last=event.id;
        if(!eligible || elapsed[effect]<cooldown[effect]) return false;
        elapsed[effect]=0;flash[effect]=flashFrames;return true;
    }
    float Progress(Effect effect) const {
        return cooldown[effect]>0?(float)elapsed[effect]/cooldown[effect]:0;
    }
};
}
