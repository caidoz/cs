#pragma once
#include <cstdint>

namespace AllyBalance {
enum Status { Burning, Poisoned, Chilled, Shocked, Bleeding, Exposed, StatusCount };
struct StatusState {
    int stacks[StatusCount]={},remaining[StatusCount]={};
    int dotClock=0,chillResistance=0;
    std::uint64_t bleedEvent=0;
    static int Cap(Status s) {const int cap[]={5,6,3,4,4,1};return cap[s];}
    static int Seconds(Status s) {const int seconds[]={4,8,3,5,6,5};return seconds[s];}
    bool Any() const {for(int i=0;i<StatusCount;++i) if(stacks[i]) return true;return false;}
    void Apply(Status s,int count,int fps) {
        if(count<=0) return;
        stacks[s]+=count;if(stacks[s]>Cap(s)) stacks[s]=Cap(s);
        int duration=Seconds(s)*fps;
        if(s==Chilled) {
            duration=duration*(100-chillResistance)/100;
            if(chillResistance<60) chillResistance+=10;
        }
        remaining[s]=duration;
    }
    int Consume(Status s) {const int count=stacks[s];stacks[s]=remaining[s]=0;return count;}
    int SlowPermille() const {return stacks[Chilled]*50;} // boss slow <= 15%
    int Bleed(std::uint64_t root) {
        if(!root || root<=bleedEvent) return 0;
        bleedEvent=root;return stacks[Bleeding]*3;
    }
    int Tick(bool running,int fps) {
        if(!running) return 0;
        int damage=0;
        if(++dotClock>=fps) {dotClock=0;damage=stacks[Burning]*3+stacks[Poisoned]*2;}
        for(int i=0;i<StatusCount;++i) if(remaining[i]>0 && --remaining[i]==0) stacks[i]=0;
        return damage;
    }
};
struct CompanionState {
    int abilityClock=0,linkClock=0,flash=0,heroAttacks=0,nextShotBonus=0;
    std::uint64_t seen[7]={};
    void Tick(bool running,bool present,int abilityMax,int linkMax) {
        if(!running) return;
        if(!present) {*this=CompanionState();return;}
        if(abilityClock<abilityMax) ++abilityClock;
        if(linkClock<linkMax) ++linkClock;
        if(flash>0) --flash;
    }
    bool Observe(int kind,std::uint64_t id,bool derived) {
        if(derived || kind<0 || kind>=7 || !id || id<=seen[kind]) return false;
        seen[kind]=id;return true;
    }
};
}
