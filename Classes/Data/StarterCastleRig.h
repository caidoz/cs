#pragma once
#include <algorithm>
#include <cmath>

// Native pixels. The three atlas cells share one registered canvas and scale.
namespace StarterCastleRig {
constexpr int W=112,H=96,PivotX=77,PivotY=48,CupX=23,CupY=31;
constexpr int RockX=W*2+1,RockY=1,RockW=14,RockH=13;
constexpr float RockScale=1.8f,RockDrawW=RockW*RockScale,RockDrawH=RockH*RockScale;
constexpr int StoneDeckY=235,FixedBaseBottomY=84;
constexpr int Wheel=50,BaseFromFloor=47,FootX=61;
// Far axle follows the chassis' receding right face and the second rail.
constexpr int FarWheelDx=26,FarWheelDy=10;
inline float angle(int age,int release=18){
 if(age<0)return 0;
 const int wind=std::max(1,release-6);
 if(age<wind)return -12.f*std::sin(age/(float)wind*1.570796327f);
 if(age<release)return -12.f+107.f*(age-wind)/(release-wind);
 if(age<release+4)return 95.f+15.f*(age-release)/4.f;
 if(age<release+22){const float t=(age-release-4)/18.f;return 110.f*(1-t)*(1-t);}
 return 0;
}
struct Point {float x,y;};
inline Point cup(int age,int release=18){
 const float a=angle(age,release)*.01745329252f,dx=CupX-PivotX,dy=CupY-PivotY;
 return {PivotX+dx*std::cos(a)-dy*std::sin(a),PivotY+dx*std::sin(a)+dy*std::cos(a)};
}
inline float loadAlpha(int age,int release,int impact){
 if(age<0||age<release)return 1;
 return std::max(0.f,std::min(1.f,(age-impact)/8.f));
}
}
