#pragma once
#include <cmath>

// Engine-independent simulation. One shot owns one target and can hit once.
namespace CastleArtillery {
enum Kind { Rock, Flame, Rockets, Gatling, Homing, Heavy, Ice, Laser, Electric, Gravity };
struct Profile {
    const char* name;
    Kind kind;
    int cooldown, hits, interval, flight, damagePercent, color;
    float size;
};
#include "Data/CastleArtilleryProfiles.inc"
inline int ClampGrade(int grade) { return grade < 0 ? 0 : grade > 9 ? 9 : grade; }
inline const Profile& Of(int grade) { return kProfiles[ClampGrade(grade)]; }
struct Point { float x,y; };
inline Point Position(Kind kind, Point from, Point target, float t, int lane) {
    t=t<0?0:t>1?1:t;
    const float curve=4*t*(1-t);
    Point p={from.x+(target.x-from.x)*t,from.y+(target.y-from.y)*t};
    if(kind==Rock) p.y+=90*curve;
    if(kind==Rockets) p.y+=(28+lane*12)*curve;
    if(kind==Homing) { p.x-=35*curve*(1-t); p.y+=(100+lane*16)*curve; }
    if(kind==Gravity) p.y+=12*std::sin(t*6.2831853f)*curve;
    return p;
}
inline bool SegmentHits(Point a, Point b, Point target, float radius) {
    const float dx=b.x-a.x,dy=b.y-a.y,length=dx*dx+dy*dy;
    float t=length>0?((target.x-a.x)*dx+(target.y-a.y)*dy)/length:0;
    t=t<0?0:t>1?1:t;
    const float x=a.x+dx*t-target.x,y=a.y+dy*t-target.y;
    return x*x+y*y<=radius*radius;
}
struct Shot {
    bool active;
    int target,generation,lane,age,flight,impact;
    Point from,position,previous,destination;
};
struct State {
    enum { Capacity=32, ChargeFrames=12, ImpactFrames=18 };
    int grade,cooldown,charge,pending,burstClock,lane,recoil,cooldownOverride;
    Shot shots[Capacity];
    State() { Reset(0); }
    void Reset(int g) {
        grade=ClampGrade(g); cooldown=charge=pending=burstClock=lane=recoil=0; cooldownOverride=0;
        for(int i=0;i<Capacity;++i) shots[i]=Shot();
    }
    bool Spawn(int target,int generation,Point from,Point destination) {
        for(int i=0;i<Capacity;++i) if(!shots[i].active) {
            Shot& s=shots[i]; s=Shot(); s.active=true; s.target=target;
            s.generation=generation; s.lane=lane++;
            s.from=s.position=s.previous=from; s.destination=destination;
            s.flight=Of(grade).flight; return true;
        }
        return false;
    }
    // Called only while combat runs. Wait at full charge between enemies.
    bool Tick(int target,int generation,Point from,Point destination) {
        const Profile& p=Of(grade);
        if(recoil>0) --recoil;
        if(pending>0) {
            if(target<0) { pending=0; charge=0; return false; }
            if(burstClock>0) { --burstClock; return false; }
            if(!Spawn(target,generation,from,destination)) return false;
            --pending; burstClock=p.interval-1; recoil=8; return true;
        }
        if(charge>0) {
            if(target<0) return false;
            if(--charge==0) { pending=p.hits; burstClock=lane=0; cooldown=0; }
            return false;
        }
        const int limit=cooldownOverride>0?cooldownOverride:p.cooldown;
        if(cooldown<limit) ++cooldown;
        if(cooldown>=limit && target>=0) charge=ChargeFrames;
        return false;
    }
    // Tracking is deterministic: endpoint arrival guarantees a collision even
    // when the target moves. Generation checks belong to the game adapter.
    bool Move(Shot& s,Point target,float radius) {
        if(!s.active || s.impact) return false;
        s.previous=s.position; s.destination=target; ++s.age;
        s.position=Position(Of(grade).kind,s.from,target,(float)s.age/s.flight,s.lane%3);
        const bool hit=s.age>=s.flight ||
            (s.age>s.flight/2 && SegmentHits(s.previous,s.position,target,radius));
        if(hit) { s.position=target; s.impact=ImpactFrames; }
        return hit;
    }
    float Progress() const {
        return charge||pending?1.0f:(float)cooldown/(cooldownOverride>0?cooldownOverride:Of(grade).cooldown);
    }
};
}
