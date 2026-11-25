#pragma once
#include <algorithm>
#include <vector>
#include <cmath>

namespace MergeCombat {
inline float lobbyCastleLift(float width,float height) {
    const float scale=width/640.f,baseline=850.f*scale,target=2.2f*width;
    // The authored castle spans the roof finial (y=83) to the wheel contact at 96px.
    const float center=((1445.f-83.f)*width/1089.f+40.f*scale+96.f*scale)*.5f;
    return std::max(0.f,(height-baseline)/(target-baseline))*(target*.5f-center);
}
enum { BulletSpawnFrames=30, BulletGrowthFrames=12, DamageNumberFrames=72, DamageBreathFrames=12 };
struct WeaponSwap {
    enum { OrbitFrames=36, AttachFrame=46, Duration=54 };
    int age=-1;
    void begin(){age=0;}
    void advance(){if(running())++age;}
    bool running() const {return age>=0&&age<Duration;}
    bool attachNow() const {return age==AttachFrame;}
    float orbit() const {return std::max(0.f,std::min(1.f,age/(float)OrbitFrames));}
    float snap() const {return std::max(0.f,std::min(1.f,(age-OrbitFrames)/(float)(AttachFrame-OrbitFrames)));}
};
struct DamagePause {
    int remaining=0;
    void begin(){remaining=DamageNumberFrames+DamageBreathFrames;}
    void advance(){if(remaining>0)--remaining;}
    bool waiting() const{return remaining>0;}
};
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
// The legacy table stores [idle, cooldown, (approach, attack, return, rest, hits, range) x 3].
struct EnemyPattern {
    int index=-1,approach=0,attack=0,back=0,rest=0,hits=1,range=0;
};
inline EnemyPattern enemyPattern(const signed short* row,int turn,int validMask=7) {
    int available[3],count=0;
    for(int i=0;i<3;++i)if((validMask&(1<<i))&&row[2+i*6+4]>0&&row[2+i*6+5]>0)available[count++]=i;
    EnemyPattern result;
    if(!count)return result;
    result.index=available[std::max(0,turn)%count];
    const signed short* p=row+2+result.index*6;
    result.approach=p[0];result.attack=p[1];result.back=p[2];result.rest=p[3];
    result.hits=p[4];result.range=p[5];
    return result;
}
inline float enemyAttackPosition(float home,float target,int range,float zoom,bool canMove) {
    // Same origin-to-origin distance and zoom as ENEMYMOVETURN. Never move closer
    // when already in range; stationary approach states stay at their home position.
    return canMove?std::min(home,target+std::max(0,range)*zoom):home;
}
// Defeat, travel with an empty deck, incoming monster, then a short ready hold.
struct WaveTransition {
    enum { DefeatFrames=24, TravelFrames=120, TravelDistance=480, EnterFrames=48, SettleFrames=18,
           EnterStart=DefeatFrames+TravelFrames, SettleStart=EnterStart+EnterFrames,
           Duration=SettleStart+SettleFrames };
    int age=-1;
    void begin(){age=0;}
    void advance(){if(active())++age;}
    bool active() const{return age>=0&&age<Duration;}
    bool defeatedVisible() const{return active()&&age<DefeatFrames;}
    bool incomingVisible() const{return !active()||age>=EnterStart;}
    bool travelling() const{return active()&&age>=DefeatFrames&&age<EnterStart;}
    float distance() const{
        const float t=std::max(0.f,std::min(1.f,(age-DefeatFrames)/(float)TravelFrames));
        return TravelDistance*t*t*(3-2*t);
    }
    float arrival() const{return std::max(0.f,std::min(1.f,(age-EnterStart)/(float)EnterFrames));}
    float defeatAlpha() const{return std::max(0.f,1.f-age/(float)DefeatFrames);}
    float speed() const{
        if(travelling())return 3.f*std::min(1.f,(age-DefeatFrames)/18.f);
        if(active()&&age>=EnterStart&&age<SettleStart)return 3.f*(1.f-arrival());
        return 0;
    }
    float incomingX(float offscreen,float home) const{
        const float t=arrival(),ease=1-(1-t)*(1-t);
        return offscreen+(home-offscreen)*ease;
    }
};
// 다음 적 등장: 오른쪽 화면 밖에서 걸어 들어오지 않고, 옛 실시간 판의 소환(REGENMOVE/REGENDRAW)처럼
// 제자리에서 마왕의 심장 아래로 솟아오른다. 투명하던 몸이 또렷해지며 위로 튀어 오르고(zoom 이 부풀었다가
// 착지하며 살짝 줄어든다), 좌우를 빠르게 뒤집다가 착지하며 히어로 쪽을 본다. 머리 위 심장은
// summonMotion(심장 3장 -> 불꽃 8장)을 등장 길이에 맞춰 한 번 돈다.
struct SummonPose {
    float lift=0;        // 발이 바닥에서 떠오른 높이(640 폭 기준 픽셀, 화면 배율 s 를 곱해 쓴다)
    float zoomMul=1;     // 몬스터 배율에 곱하는 값
    int alpha=32;        // 0~32
    bool flipped=false;  // true 면 기본 방향의 반대를 본다
    int heartMotion=0;   // summonMotion 첨자(0~29)
    bool landed=true;
};
inline SummonPose summonPose(int frame,int frames) {
    SummonPose p;
    if(frames<=0||frame>=frames)return p;
    const float t=std::max(0.f,std::min(1.f,frame/(float)std::max(1,frames-1)));
    const float jump=std::max(0.f,std::min(1.f,std::sin(3.14159265f*t)));
    float bounce=0;
    if(t>.75f){const float tb=std::min(1.f,(t-.75f)/.25f);bounce=std::sin(3.14159265f*tb)*(1-tb);}
    p.lift=(float)(64.f*std::pow(jump,.5f)-14.f*bounce);              // 32*_2X 점프, 7*_2X 착지 바운스
    const float zDown=t>.82f?std::min(1.f,(float)std::pow((t-.82f)/.18f,.7f)):0.f;
    p.zoomMul=std::max(1.f,(float)(1+.35f*std::pow(jump,.3f)-.18f*zDown));
    p.alpha=std::max(1,std::min(32,(int)(32*std::min(1.f,t*1.6f))));
    const int flip=frame<frames/4?(frame/2)%2:frame<frames/2?frame%2:(frame/2)%2;
    p.flipped=flip!=0;
    p.heartMotion=std::min(29,frame*30/frames);
    p.landed=false;
    return p;
}
struct EnemyPhases {
    int approach=0,attack=30,recovery=12,returnFrames=0;
    void begin(int walkFrames,int attackFrames,int backFrames=-1,int restFrames=12){
        approach=std::max(0,walkFrames);attack=std::max(30,attackFrames);
        returnFrames=backFrames<0?approach:std::max(0,backFrames);recovery=std::max(0,restFrames);
    }
    int returnStart() const {return approach+attack;}
    int recoveryStart() const {return returnStart()+returnFrames;}
    int end() const {return recoveryStart()+recovery;}
    int impact() const {return approach+attack/2;}
    bool walkingIn(int elapsed) const {return elapsed>=0&&elapsed<approach;}
    bool walkingBack(int elapsed) const {return elapsed>=returnStart()&&elapsed<recoveryStart();}
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
// 데크의 줄 간격. 히어로 뒤 첫 동료까지의 거리(DeckGap)가 동료 사이 간격의 기준이다 -
// 둘이 같아야 "히어로 - 동료 - 동료" 가 한 줄로 고르게 선다. 자리가 모자라면 그만큼 좁힌다.
constexpr float DeckGap=52.f;
inline DeckPosition position(int index,int count,float right,float ground,float scale,float availableWidth) {
    const float step=std::min(DeckGap*scale,std::max(0.f,availableWidth)/std::max(1,count-1));
    return {right-index*step,ground};
}
}
