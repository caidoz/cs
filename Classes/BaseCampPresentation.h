#pragma once
#include <algorithm>
#include <cmath>
namespace BaseCamp {
inline float ease(float age,float begin,float end){float t=std::max(0.f,std::min(1.f,(age-begin)/(end-begin)));return t*t*(3.f-2.f*t);}
inline float recall(float age,int actor){return age<0?0:ease(age,actor*.08f,.88f+actor*.08f);}
inline float closure(float age){return age<0?0:ease(age,1.15f,1.65f);}
inline float travel(float age){return age<0?0:ease(age,1.65f,2.85f);}
inline float uiExit(float age){return age<0?0:ease(age,0,.40f);}
inline float duration(){return 2.85f;}
inline float wander(float time,int actor){return std::sin(time*.62f+actor*2.1f);}
}
