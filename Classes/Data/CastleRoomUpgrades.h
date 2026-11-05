#pragma once
#include "CastleFacilities.h"
#include "CastleRoomIntegrated.h"
namespace CastleRoomUpgrades {
// Six authored states per facility: base, then upgrades 1..5. Atlas coordinates
// are independent of castle geometry; SoftCastle::Sectors remains authoritative.
struct Crop {int x,y,w,h;};
// Crystal cutaway contains a baked chassis. Register its body above the
// separately animated wheel axle, rather than drawing two complete chassis.
inline float SourceBodyBottom(int castle){return castle==8?.91f:1.0f;}
inline float TargetBodyBottom(int castle){return castle==8?.93f:1.0f;}
inline float InteriorYScale(int castle){return TargetBodyBottom(castle)/SourceBodyBottom(castle);}
inline Crop Frame(int castle,int room,int level,int width,int height){
 castle=castle<0?0:castle>9?9:castle;
 room=room<0?0:room>=CastleFacilities::Counts[castle]?CastleFacilities::Counts[castle]-1:room;
 level=level<0?0:level>5?5:level;
 const auto& b=CastleRoomIntegrated::Bodies[castle][level];
 const auto& s=CastleRoomIntegrated::ArtRegions[castle][CastleFacilities::SectorIndex[castle][room]];
 const float scaleX=(float)width/CastleRoomIntegrated::Sizes[castle][level][0];
 const float scaleY=(float)height/CastleRoomIntegrated::Sizes[castle][level][1];
 const int w=(int)(s.w*b.w*scaleX),h=(int)(s.h*b.h*scaleY);
 return {(int)((b.x+s.x*b.w)*scaleX),(int)((b.y+s.y*b.h)*scaleY),w>0?w:1,h>0?h:1};
}
}
