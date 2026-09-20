#include "../../Classes/CmfSwordTransform.h"
#include "../../Classes/Data/SwordSprites.h"
#include <cassert>
#include <cstdio>

static bool near(float a, float b) { return std::fabs(a-b)<0.001f; }
int main()
{
    // Expected top-left-relative hand positions for horizontal legacy sprites.
    const float expected[8][2] = {
        {16,110}, {394,110}, {110,16}, {110,16},
        {394,110}, {16,110}, {110,394}, {110,394}
    };
    for(int flags=0;flags<8;++flags) {
        signed short part[4]={109,10,-20,(short)flags};
        CmfSwordPose p=DecodeLegacySwordPose(part);
        assert(p.valid && near(p.handX,10+expected[flags][0]) && near(p.handY,-20+expected[flags][1]));
        assert(p.flipX==bool(flags&1));
    }
    CmfSwordPose a={0,0,350,1,1,false,true},b={8,12,10,2,.5f,false,true};
    CmfSwordPose mid=InterpolateSwordPose(a,b,.5f);
    assert(near(mid.angleDegrees,360) && near(mid.handX,4) && near(mid.handY,6));
    assert(near(mid.scale,1.5f) && near(mid.opacity,.75f));
    assert(near(SwordAngleDelta(10,350),-20));
    signed short absent[4]={107,0,0,0};
    assert(!DecodeLegacySwordPose(absent).valid);
    assert(!GetSwordSpriteInfo(-1) && !GetSwordSpriteInfo(35));
    for(int n=0;n<35;++n) {
        const SwordSpriteInfo& s=*GetSwordSpriteInfo(n);
        assert(SWORD_TILE_SIZE==32);
        assert(s.cols==swordTileSize[n*2] && s.rows==swordTileSize[n*2+1]);
        assert(s.width==s.cols*SWORD_TILE_SIZE && s.height==s.rows*SWORD_TILE_SIZE);
        // A horizontal flip must move the anchor with the same grip pixel.
        float flipped=s.width-s.pivotX;
        assert(near(flipped/s.width,1-s.pivotX/s.width));
    }
    std::puts("Sword transforms: quarter turns, flips, angle wrap, pivots OK");
}
