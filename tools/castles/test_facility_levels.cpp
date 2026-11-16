#include "../../Classes/CastleMenuModel.h"
#include "../../Classes/MergeCastleTransition.h"
#include <cassert>
#include <cstdio>

int main(){
    using namespace CastleMenuModel;
    int purchases=0;
    for(int castle=0;castle<Count;++castle)for(int room=0;room<CastleFacilities::RoomCount;++room){
        Progress p={};p.version=2;p.owned=1023;
        for(int level=0;level<MaxLevel;++level){
            long long gold=UpgradeCost(castle,level,true)-1;
            assert(!Upgrade(p,castle,room,true,gold)&&p.rooms[castle][room]==level);
            gold=UpgradeCost(castle,level,true);
            assert(Upgrade(p,castle,room,true,gold)&&gold==0);
            ++purchases;
            for(int c=0;c<Count;++c)for(int r=0;r<CastleFacilities::RoomCount;++r)
                assert(p.rooms[c][r]==(r==room?level+1:0));
            assert(CastleFacilities::Output(castle,room,level+1)>CastleFacilities::Output(castle,room,level));
            auto frame=MergeCastleTransition::RoomFrame(room,level+1,1405,1152);
            assert(frame.w>0&&frame.h>0&&frame.x>=0&&frame.y>=0&&frame.x+frame.w<=1405&&frame.y+frame.h<=1152);
        }
        long long gold=1000000;
        assert(!Upgrade(p,castle,room,true,gold)&&gold==1000000&&p.rooms[castle][room]==5);
    }
    assert(purchases==200);
    std::puts("PASS all 40 themed facilities: five paid upgrades, shared levels, increasing output and max-level cap");
}
