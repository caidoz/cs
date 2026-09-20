#pragma once
#include <cmath>
namespace LobbyParallax {
struct Depth { float zoom, scroll; };
constexpr Depth Far = {.08f,.06f};
constexpr Depth Near = {.25f,.20f};
constexpr Depth CloudBack = {.12f,.10f};
constexpr Depth CloudFront = {.18f,.15f};
inline float clamp(float v,float lo,float hi) { return v<lo?lo:(v>hi?hi:v); }
inline float scale(float zoom,Depth depth) { return 1+(zoom-1)*depth.zoom; }
inline float offset(float travel,Depth depth,float limit) {
    return clamp(travel*depth.scroll,-limit,limit);
}
}
