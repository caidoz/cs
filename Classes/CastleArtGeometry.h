#pragma once
#include <algorithm>
namespace CastleArtGeometry {
// Registered five-floor hulls have equal visible widths in 1089x1445 canvases.
static const int Bounds[10][2]={{86,1002},{86,1002},{86,1002},{86,1002},{86,1002},
 {86,1002},{86,1002},{86,1002},{86,1002},{86,1002}};
// Clear deck rims share the same width; tower silhouettes retain their themes.
static const int DeckRight[10]={1002,1002,1002,1002,1002,1002,1002,1002,1002,1002};
inline int stage(int c){return std::max(0,std::min(9,c));}
inline float width(int c){const auto& b=Bounds[stage(c)];return float(b[1]-b[0]);}
inline float center(int c){const auto& b=Bounds[stage(c)];return (b[0]+b[1])*.5f;}
inline float scale(int screenWidth,int c){return screenWidth*(600.f/640.f)/width(c);}
}
