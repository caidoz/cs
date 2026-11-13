#pragma once
#include <algorithm>
#include <vector>

namespace MergeCombat {
inline float lobbyCastleLift(float width,float height) {
    const float scale=width/640.f,baseline=850.f*scale,target=2.2f*width;
    // The authored castle spans the roof finial (y=83) to the wheel contact at 96px.
    const float center=((1445.f-83.f)*width/1089.f+40.f*scale+96.f*scale)*.5f;
    return std::max(0.f,(height-baseline)/(target-baseline))*(target*.5f-center);
}
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
struct DeckMergeTimeline {
    enum { GatherFrames=18, Duration=GatherFrames+ResidentReveal::Duration };
    int age=-1;
    void begin() {age=0;}
    void advance(int frames) {if(age>=0)age=std::min((int)Duration,age+std::max(0,frames));}
    bool running() const {return age>=0&&age<Duration;}
    bool converging() const {return age>=0&&age<GatherFrames;}
    float progress() const {
        const float t=std::max(0.f,std::min(1.f,age/(float)GatherFrames));
        return t*t*(3.f-2.f*t);
    }
    float x(float from,float destination) const {return from+(destination-from)*progress();}
};
struct AnimatedValue {
    double value=0,from=0;
    float elapsed=0,duration=.45f;
    long long target=0;
    long long set(long long next) {
        next=std::max(0LL,next);
        if(next==target)return 0;
        const long long delta=next-target;
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
struct EnemyPhases {
    int approach=0,attack=30,recovery=12;
    void begin(int walkFrames,int attackFrames){approach=std::max(0,walkFrames);attack=std::max(30,attackFrames);}
    int returnStart() const {return approach+attack+recovery;}
    int end() const {return returnStart()+approach;}
    int impact() const {return approach+attack/2;}
    bool walkingIn(int elapsed) const {return elapsed<approach;}
    bool walkingBack(int elapsed) const {return approach>0&&elapsed>=returnStart();}
};
inline float walkProgress(const std::vector<float>& distance,float phase){
    if(distance.size()<2||distance.back()<=0)return 0;
    const float position=std::max(0.f,std::min(1.f,phase))*(distance.size()-1);
    const int index=std::min((int)distance.size()-2,(int)position);
    return (distance[index]+(distance[index+1]-distance[index])*(position-index))/distance.back();
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
inline DeckPosition position(int index,int count,float right,float ground,float scale,float availableWidth) {
    const float step=std::min(84.f*scale,std::max(0.f,availableWidth)/std::max(1,count-1));
    return {right-index*step,ground};
}
}
