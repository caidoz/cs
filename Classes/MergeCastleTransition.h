#pragma once
#include <algorithm>
#include <cmath>
// Each fixed-size tile travels independently from the reel center.
namespace MergeCastleTransition {
constexpr float PanicEnd=.65f, CoverEnd=1.20f, Duration=2.30f;
inline float Ease(float elapsed,float begin,float duration) {
 const float t=std::max(0.f,std::min(1.f,(elapsed-begin)/duration));
 return 1.f-std::pow(1.f-t,3.f);
}
inline float LobbyExit(float t){return Ease(t,0,.38f);}
inline float CoverProgress(float t){return Ease(t,PanicEnd,CoverEnd-PanicEnd);}
inline float BoardEnter(float t){return Ease(t,CoverEnd,.75f);}
inline float ControlsEnter(float t){return Ease(t,0,.28f);}
inline float TileLaunch(int index,int count){return CoverEnd+.08f+.64f*index/std::max(1,count-1);}
constexpr float TileTravel=.24f;
inline float TileProgress(float t,int index,int count){return std::max(0.f,std::min(1.f,(t-TileLaunch(index,count))/TileTravel));}
inline float TileLand(int index,int count){return TileLaunch(index,count)+TileTravel;}
struct Crop {int x,y,w,h;};
inline Crop RoomFrame(int room,int level,int width,int height) {
 room=std::max(0,std::min(3,room));level=std::max(0,std::min(5,level));
 const int tile=level*4+room,column=tile%2,row=tile/2;
 const int x=width*column/2,y=height*row/12;
 return {x,y,width*(column+1)/2-x,height*(row+1)/12-y};
}
}
