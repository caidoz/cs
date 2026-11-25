#pragma once
#include <algorithm>
#include <cmath>

namespace TurretAttack {
enum Kind { Stone, Shell, Missiles, Rapid, Laser, Magnetic };
struct UpgradeVisual {
    int level,motes;
    float beamScale;
    explicit UpgradeVisual(int grade):level(std::max(0,std::min(5,grade))),motes(level?1+(level-1)/2:0),beamScale(1.f+level*.012f){}
};
inline Kind kind(int castle) {
    static const Kind types[19]={Stone,Shell,Missiles,Rapid,Shell,Shell,Laser,Magnetic,Laser,Laser,Laser,Shell,Shell,Missiles,Magnetic,Rapid,Laser,Shell,Shell};
    return types[std::max(0,std::min(18,castle))];
}
struct Sequence {
    Kind type=Stone;
    int castle=0,grade=0,age=-1,count=1,release=18,flight=40,spacing=8;
    void begin(int c,int g) {
        castle=c;grade=std::max(0,std::min(5,g));type=kind(c);age=0;
        count=type==Missiles?(c==2?3:1):type==Rapid?12:1;
        release=(type==Laser||type==Magnetic)?26:18;
        flight=type==Magnetic?22:type==Laser?12:type==Missiles?42:type==Stone?42:28;
        spacing=type==Rapid?5:8;
    }
    int launch(int index) const {return release+(type==Rapid?index*spacing/2:index*spacing);}
    int impact() const {return launch(count-1)+flight;}
    int end() const {return impact()+14;}
    bool running() const {return age>=0&&age<end();}
    float recoil() const {
        float value=0;
        for(int i=0;i<count;++i){const int t=age-launch(i);if(t>=0&&t<12)value=std::max(value,std::sin(t/12.f*3.14159265f));}
        return value;
    }
};
struct Point {float x,y;};
inline Point position(Kind type,float t,Point from,Point to,int index,float scale) {
    t=std::max(0.f,std::min(1.f,t));
    if(type==Missiles) {
        // Diana's launch first turns upward, then accelerates toward its target.
        const float a=1-t;
        const float direction=to.x>=from.x?1.f:-1.f;
        const Point c1={from.x+24*scale*direction,from.y+(90+index*22)*scale};
        const Point c2={to.x-65*scale*direction,to.y+(65+index*12)*scale};
        return {a*a*a*from.x+3*a*a*t*c1.x+3*a*t*t*c2.x+t*t*t*to.x,
                a*a*a*from.y+3*a*a*t*c1.y+3*a*t*t*c2.y+t*t*t*to.y};
    }
    // Only the catapult lobs its load; conventional cannons fire straight.
    const float rise=type==Stone?130.f:0.f;
    return {from.x+(to.x-from.x)*t,from.y+(to.y-from.y)*t+rise*scale*4*t*(1-t)};
}
}
