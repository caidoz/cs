#pragma once
// Presentation order is independent of the persisted room indices.
// Artwork is taken from the existing six-stage room/cannon atlases.
namespace CastleUpgradeBlocks {
struct Block { const char* title; int room; };
static const Block Items[5]={
 {"체력 증가",2},{"방어력 증가",3},{"공격력 증가",1},
 {"성 생산력 향상",0},{"대포 공격력 증가",-1}
};
enum { Gap=12, TouchHeight=48 };
inline int CardHeight(int){return 232;}
inline int PreviewHeight(int height){return height*65/100;}
inline int ContentHeight(int height){return PreviewHeight(height)+12+60+5*(CardHeight(height)+Gap)+16;}
}
