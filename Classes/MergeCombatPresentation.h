#pragma once
#include <algorithm>

namespace MergeCombat {
enum { BulletSpawnFrames=30, BulletGrowthFrames=12 };
struct ResidentReveal {
    enum { Duration=42 };
    int age=-1;
    void update(bool landed) {age=landed?std::min((int)Duration,age<0?0:age+1):-1;}
    bool visible() const {return age>0;}
    bool arriving() const {return age>=0&&age<Duration;}
    float progress() const {return std::max(0.f,std::min(1.f,age/(float)Duration));}
};
inline float companionZoom(float heroZoom) {return heroZoom*.8f;}
struct AnimatedValue {
    float value=0,from=0,elapsed=0,duration=.45f;
    int target=0;
    int set(int next) {
        next=std::max(0,next);
        if(next==target)return 0;
        const int delta=next-target;
        from=value;target=next;elapsed=0;
        return delta;
    }
    void advance(float dt) {
        elapsed=std::min(duration,elapsed+std::max(0.f,dt));
        const float t=elapsed/duration,ease=t*t*(3.f-2.f*t);
        value=from+(target-from)*ease;
    }
};
inline float bulletAppearance(int elapsed,int release) {
    return std::max(0.f,std::min(1.f,(elapsed-(release-BulletSpawnFrames))/(float)BulletGrowthFrames));
}
inline float actorStep(int elapsed,int end) {
    return 12.f*std::max(0.f,std::min(1.f,std::min(elapsed/10.f,(end-elapsed)/12.f)));
}
// Damage is committed once, at impact; the next actor waits for recovery as well.
struct Timeline {
    int elapsed=0,release=0,impact=0,end=0;
    bool applied=false;
    void begin(int motionEnd,int releaseFrame,int flightFrames,int recovery=8) {
        elapsed=0;applied=false;
        release=std::max(1,releaseFrame);
        impact=release+std::max(0,flightFrames);
        end=std::max(motionEnd,impact)+std::max(1,recovery);
    }
    bool advance() {
        ++elapsed;
        if(!applied&&elapsed>=impact){applied=true;return true;}
        return false;
    }
    bool flying() const {return elapsed>=release&&elapsed<impact;}
    bool finished() const {return elapsed>=end;}
};
struct DeckPosition {float x,y;};
inline DeckPosition position(int index,int count,float right,float ground,float scale,float headroom) {
    const int columns=std::min(2,std::max(1,count)),rows=(count+columns-1)/columns;
    const float step=std::min(40.f*scale,std::max(0.f,headroom-150.f*scale)/std::max(1,rows-1));
    return {right-(index%columns)*84.f*scale,ground+(index/columns)*step};
}
}
