#include "../../Classes/TurretAttackPresentation.h"
#include "../../Classes/MergeCombatPresentation.h"
#include <cassert>
#include <cmath>
#include <iostream>

int main() {
    using namespace TurretAttack;
    assert(kind(0)==Stone && kind(2)==Missiles && kind(3)==Rapid);
    for(int castle=0;castle<10;++castle) {
        Sequence shot;shot.begin(castle,5);
        MergeCombat::Timeline time;
        time.begin(shot.end()-14,shot.release,shot.impact()-shot.release,14);
        int hits=0;
        while(!time.finished()) {
            if(time.advance()){++hits;assert(time.elapsed==shot.impact());}
            assert(time.applied==(time.elapsed>=shot.impact()));
        }
        assert(hits==1 && time.end==shot.end());
        assert(shot.count==(castle==2?3:castle==3?6:1));
        for(int i=0;i<shot.count;++i)assert(shot.launch(i)+shot.flight<=time.impact);
    }
    Point from{50,100},to{500,110};
    for(Kind type:{Stone,Shell,Missiles,Rapid}) {
        Point start=position(type,0,from,to,0,1),end=position(type,1,from,to,0,1);
        assert(start.x==from.x&&start.y==from.y&&end.x==to.x&&end.y==to.y);
        auto midpoint=position(type,.5f,from,to,0,1);
        assert(std::isfinite(midpoint.x)&&std::isfinite(midpoint.y));
        if(type==Stone||type==Missiles)assert(midpoint.y>to.y);
        auto mirrored=position(type,.5f,{590,100},{140,110},0,1);
        assert(std::abs(midpoint.x+mirrored.x-640)<.001f);
        assert(std::abs(midpoint.y-mirrored.y)<.001f);
    }
    std::cout << "PASS turret types, sequential burst release, flight endpoints, and one damage event after final arrival\n";
}
