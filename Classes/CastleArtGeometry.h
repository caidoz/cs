#pragma once
#include <algorithm>
namespace CastleArtGeometry {
// Opaque hull bounds in the original 1089x1445 canvases (alpha >= 128).
static const int Bounds[10][2]={{71,1037},{79,1036},{58,1038},{61,1034},{79,1037},
 {82,1029},{60,1044},{96,1030},{116,1001},{72,1026}};
// Right edge of the native roof support at y=369; upper silhouettes differ
// even when the complete hulls have the same displayed width.
static const int DeckRight[10]={1037,1026,1015,1006,1001,1012,1034,976,979,1020};
inline int stage(int c){return std::max(0,std::min(9,c));}
inline float width(int c){const auto& b=Bounds[stage(c)];return float(b[1]-b[0]);}
inline float center(int c){const auto& b=Bounds[stage(c)];return (b[0]+b[1])*.5f;}
inline float scale(int screenWidth,int c){return screenWidth*(600.f/640.f)/width(c);}
}
