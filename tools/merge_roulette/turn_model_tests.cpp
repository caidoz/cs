#include "../../Classes/MergeRouletteModel.h"
#include <cassert>
#include <iostream>
using namespace MergeRoulette;
Run armed() {
    Run r;r.choosing=false;r.enemyHp=r.enemyMax=100000;
    Block b;b.family=Sword;b.x=b.y=0;r.board.push_back(b);
    return r;
}
int main() {
    const int widths[]={0,1,2,3,2,5,3},heights[]={0,1,1,1,2,1,2};
    for(int gear=0;gear<GearCount;++gear)for(int lv=1;lv<=MaxLevel;++lv)
        MergeBoard::SetGearShape(gear,lv,widths[lv],heights[lv]);
    Stats stats;
    for(int wave=0;wave<WavesPerStage;++wave) {
        Run r=armed();r.wave=wave;
        assert(r.attack(stats)&&!r.shouldCounterattack()&&!r.counterattack());
        while(r.step()){}
        assert(r.lives==5&&r.shouldCounterattack());
        const int expected=BossTier(wave)?2:1;
        assert(r.counterDamage()==expected&&r.counterattack()&&r.lives==5-expected);
        assert(!r.counterattack());
        Run resumed;assert(resumed.decode(r.encode())&&resumed.counterResolved&&!resumed.shouldCounterattack());
        resumed.finish();assert(resumed.lives==5-expected&&!resumed.attacking);
    }
    Run stage=armed();
    for(int wave=0;wave<WavesPerStage;++wave) {
        assert(stage.stage==0&&stage.wave==wave);
        stage.enemyHp=1;assert(stage.attack(stats));while(stage.step()){}
        assert(!stage.shouldCounterattack()&&!stage.counterattack());stage.finish();
    }
    assert(stage.stage==1&&stage.wave==0);
    assert(BossTier(4)==1&&BossTier(9)==2&&BossTier(14)==3&&BossTier(13)==0);
    Run skipped=armed();assert(skipped.attack(stats));while(skipped.step()){}
    skipped.effects.skip=1;assert(!skipped.shouldCounterattack());skipped.finish();assert(skipped.lives==5&&skipped.skipTurns==0);
    Run blocked=armed();assert(blocked.attack(stats));while(blocked.step()){}
    blocked.effects.protect=1;assert(blocked.shouldCounterattack()&&blocked.counterDamage()==0);
    assert(blocked.counterattack());blocked.finish();assert(blocked.lives==5);
    Run lethal=armed();lethal.lives=1;assert(lethal.attack(stats));while(lethal.step()){}
    assert(lethal.counterattack()&&lethal.lives==0);
    Run resumed;assert(resumed.decode(lethal.encode()));resumed.finish();assert(resumed.lost);
    Run old=armed();std::string legacy=old.encode();legacy.replace(4,1,"8");legacy.erase(legacy.find_last_of(' '));
    assert(resumed.decode(legacy)&&!resumed.counterResolved);
    std::cout<<"PASS 15 waves, bosses 5/10/15, counterattack after allies, one hit across resume, block/stun/death and v8 migration\n";
}
