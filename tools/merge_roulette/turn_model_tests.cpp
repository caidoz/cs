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
    // Preserve both actual material identities before replacing/erasing their board entries.
    for(int source:{0,1}){
        Roster roster;roster.add(0,1,1);roster.add(0,1,2);roster.add(0,2,3);
        Run r;r.roster=&roster;r.choosing=false;
        Block a;a.family=0;a.crew=1;a.x=0;a.y=0;
        Block b=a;b.crew=2;b.x=2;r.board={a,b};
        const Block target=r.board[1-source];
        assert(r.place(false,source,target.x,target.y)&&r.board.size()==1);
        assert(r.mergeInputs[0].crew==(source==0?1:2)&&r.mergeInputs[1].crew==(source==0?2:1));
        assert(r.mergeInputs[0].level==1&&r.mergeInputs[1].level==1);
        assert(r.mergeResult.crew==3&&r.mergeResult.level==2&&r.mergeSeq==1);
        Block armor;armor.family=Armor;armor.x=4;armor.y=0;r.board.push_back(armor);
        assert(!r.place(false,1,target.x,target.y)&&r.mergeSeq==1&&r.mergeResult.crew==3);
    }
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
    Run old=armed();std::string legacy=old.encode();legacy.replace(4,2,"8");for(int i=0;i<4;++i)legacy.erase(legacy.find_last_of(' '));
    assert(resumed.decode(legacy)&&!resumed.counterResolved);
    // Native HP and armor use the same units in bars, equipment, and actual hits.
    Run native=armed();native.lives=3;native.setVitals(1800,120);native.enemyAttack=600;
    assert(native.lives==1080&&native.maxLives==1800&&native.baseArmor==120);
    Stats equipped;equipped.realVitals=true;equipped.armor[Armor-Sword][0]=240;
    Block defense;defense.family=Armor;defense.x=1;defense.y=0;native.board.push_back(defense);
    assert(native.attack(equipped)&&native.effects.protect==240);
    while(native.step()){}
    assert(native.counterDamage()==240&&native.counterattack()&&native.lives==840);
    Run nativeResume;assert(nativeResume.decode(native.encode())&&nativeResume.encode()==native.encode());
    assert(nativeResume.baseArmor==120&&nativeResume.enemyAttack==600&&!nativeResume.counterattack());
    nativeResume.finish();assert(nativeResume.lives==840);
    nativeResume.setVitals(3600,180);assert(nativeResume.lives==1680&&nativeResume.baseArmor==180);
    Run legacyNine=armed();legacyNine.lives=2;
    std::string nine=legacyNine.encode();nine.replace(4,2,"9");
    for(int i=0;i<3;++i)nine.erase(nine.find_last_of(' '));
    assert(resumed.decode(nine)&&!resumed.realVitals&&resumed.lives==2);
    resumed.setVitals(1500,75);assert(resumed.lives==600&&resumed.maxLives==1500&&resumed.baseArmor==75);
    nativeResume.wave=14;nativeResume.enemyHp=1;
    assert(nativeResume.attack(equipped));while(nativeResume.step()){}
    nativeResume.finish();assert(nativeResume.stage==1&&nativeResume.lives==nativeResume.maxLives);
    std::cout<<"PASS native HP/armor, fractional v9 migration, equipment mitigation, v10 resume, and stage recovery\n";
    std::cout<<"PASS 15 waves, bosses 5/10/15, counterattack after allies, one hit across resume, block/stun/death and v8 migration\n";
}
