#pragma once
#include <cmath>

namespace LobbySkyCycle {
constexpr double PeriodSeconds = 300.0;
constexpr double StartHour = 9.0;
struct RGB { float r, g, b; };
struct Palette { RGB top, horizon, land; float night; };
inline float smooth(float t) { return t*t*(3.0f-2.0f*t); }
inline RGB mix(RGB a, RGB b, float t) {
    return {a.r+(b.r-a.r)*t,a.g+(b.g-a.g)*t,a.b+(b.b-a.b)*t};
}
inline double hour(double seconds) {
    return std::fmod(StartHour + seconds*24.0/PeriodSeconds,24.0);
}
inline Palette sample(double h) {
    struct Key { double hour; Palette p; };
    static const Key keys[] = {
        {0, {{12,21,61},{49,66,115},{74,92,145},1}},
        {4, {{42,47,102},{133,109,154},{123,124,169},0.85f}},
        {7, {{115,140,199},{249,200,172},{227,207,214},0.15f}},
        {10, {{63,147,225},{190,225,243},{250,250,254},0}},
        {13, {{58,144,229},{181,224,246},{250,250,254},0}},
        {16, {{106,118,194},{249,195,157},{255,219,198},0.02f}},
        {18.5, {{94,70,150},{244,155,133},{222,171,174},0.3f}},
        {21, {{28,32,88},{96,80,137},{108,108,163},0.85f}},
        {24, {{12,21,61},{49,66,115},{74,92,145},1}}
    };
    h = std::fmod(h+24.0,24.0);
    for (int i=1;i<int(sizeof(keys)/sizeof(keys[0]));++i) if (h<=keys[i].hour) {
        const auto& a=keys[i-1]; const auto& b=keys[i];
        const float t=smooth(float((h-a.hour)/(b.hour-a.hour)));
        return {mix(a.p.top,b.p.top,t),mix(a.p.horizon,b.p.horizon,t),
            mix(a.p.land,b.p.land,t),a.p.night+(b.p.night-a.p.night)*t};
    }
    return keys[0].p;
}
}
