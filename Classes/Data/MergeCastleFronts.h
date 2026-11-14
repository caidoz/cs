#pragma once
// Alpha bounds of independent exterior covers. Original castle art is unchanged.
namespace MergeCastleFronts {
struct Frame {int x,y,w,h;};
static const Frame Frames[10]={
 {79,246,1477,629}, // Solid wall body; decorative spikes must not expose old signs.
 {28,30,1669,838},
 {36,34,1655,839},
 {38,40,1658,826},
 {23,35,1677,836},
 {42,42,1642,826},
 {29,32,1674,846},
 {36,35,1653,825},
 {33,49,1652,828},
 {30,69,1565,791}
};
inline int Image(int castle){return castle==0?MERGE_WOOD_FRONT_COVER_IMG:
    castle==9?MERGE_GOLD_FRONT_COVER_IMG:MERGE_EXTRA_FRONT_COVER_FIRST_IMG+castle-1;}
}
