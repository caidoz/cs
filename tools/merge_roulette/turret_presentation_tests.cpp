#include "../../Classes/TurretAttackPresentation.h"
#include "../../Classes/MergeCombatPresentation.h"
#include <cassert>
#include <cmath>
#include <iostream>

int main() {
    using namespace TurretAttack;
    assert(kind(0)==Stone && kind(2)==Missiles && kind(3)==Rapid && kind(4)==Shell && kind(7)==Magnetic);
    assert(UpgradeVisual(-1).motes==0&&UpgradeVisual(99).level==5);
    for(int lv=0;lv<=5;++lv){
        UpgradeVisual look(lv);
        assert(look.motes>=0&&look.motes<=3&&look.beamScale>=1&&look.beamScale<=1.061f);
        if(lv)assert(look.motes>=UpgradeVisual(lv-1).motes&&look.beamScale>UpgradeVisual(lv-1).beamScale);
        for(int c=0;c<19;++c){Sequence base,up;base.begin(c,0);up.begin(c,lv);
            assert(base.count==up.count&&base.release==up.release&&base.impact()==up.impact()&&base.end()==up.end());}
    }
    for(int castle=0;castle<19;++castle) {
        Sequence shot;shot.begin(castle,5);
        MergeCombat::Timeline time;
        time.begin(shot.end()-14,shot.release,shot.impact()-shot.release,14);
        int hits=0;
        while(!time.finished()) {
            if(time.advance()){++hits;assert(time.elapsed==shot.impact());}
            assert(time.applied==(time.elapsed>=shot.impact()));
        }
        assert(hits==1 && time.end==shot.end());
        assert(shot.count==(castle==2?3:kind(castle)==Rapid?12:1));
        for(int i=0;i<shot.count;++i)assert(shot.launch(i)+shot.flight<=time.impact);
    }
    Sequence rapid;rapid.begin(3,0);
    assert(rapid.launch(10)-rapid.launch(0)==25); // Ten intervals instead of the old five.
    for(int i=1;i<rapid.count;++i) {
        const int gap=rapid.launch(i)-rapid.launch(i-1);
        assert(gap==2||gap==3);
    }
    Point from{50,100},to{500,110};
    for(Kind type:{Stone,Shell,Missiles,Rapid,Magnetic}) {
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
