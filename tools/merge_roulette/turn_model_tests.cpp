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
    // Gloves contribute through the native attack stat, never a separate attack turn.
    {
        Run r=armed();Block glove;glove.family=Gloves;glove.x=2;glove.y=0;r.board.push_back(glove);
        Effects effect;effect.inspire=2;
        assert(r.evaluate(glove,stats,effect).damage==0&&effect.inspire==2);
        const long long prediction=r.preview(stats);
        assert(r.attack(stats)&&r.shots.size()==1&&r.shots[0].block.family==Sword);
        assert(r.shots[0].damage==prediction);
        Run resumed;assert(resumed.decode(r.encode())&&resumed.shots.size()==1);
        assert(resumed.step()&&!resumed.step()&&resumed.nextShot==1);
        // Old in-progress saves may still contain a glove attack. Discard pending glove turns.
        Shot old;old.block=glove;old.damage=77;
        r.shots.insert(r.shots.begin(),old);
        assert(resumed.decode(r.encode())&&resumed.nextShot==0&&resumed.shots.size()==1);
        r.nextShot=1;
        assert(resumed.decode(r.encode())&&resumed.nextShot==0&&resumed.shots.size()==1);
        Run onlyGloves=armed();onlyGloves.board={glove};
        assert(onlyGloves.attack(stats)&&onlyGloves.shots.empty()&&onlyGloves.shouldCounterattack());
        assert(resumed.decode(onlyGloves.encode())&&resumed.shots.empty()&&resumed.shouldCounterattack());
        Stats stronger=stats;stronger.weapon=stats.weapon*2;
        Run base=armed();assert(base.preview(stronger)==base.preview(stats)*2);
    }
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
        //못 합치는 것을 올리면 겹쳐 놓일 뿐 합성 기록은 그대로다. 빈 자리에만 놓으라면(allowOverlap=false) 거부한다.
        assert(!r.place(false,1,target.x,target.y,false)&&r.mergeSeq==1&&r.mergeResult.crew==3);
        assert(r.place(false,1,target.x,target.y)&&!r.boardResolved()&&r.mergeSeq==1&&r.mergeResult.crew==3);
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
    Run old=armed();std::string legacy=old.encode();legacy.replace(4,2,"8");for(int i=0;i<10;++i)legacy.erase(legacy.find_last_of(' '));
    assert(resumed.decode(legacy)&&!resumed.counterResolved);
    // Native HP and armor use the same units in bars, equipment, and actual hits.
    Run native=armed();native.lives=3;native.setVitals(1800,120);native.enemyAttack=600;
    assert(native.lives==1080&&native.maxLives==1800&&native.baseArmor==120);
    Stats equipped;equipped.realVitals=true;equipped.armor[Armor-Sword][0]=240;
    Block defense;defense.family=Armor;defense.x=1;defense.y=0;native.board.push_back(defense);
    assert(native.attack(equipped)&&native.effects.protect==240);
    while(native.step()){}
    // 방어막 통: 실제 장착 120 + 갑옷 블록 240 = 360 이 찬 채로 600 을 받는다 → 통 0, 체력 -240.
    assert(native.guard==360&&native.guardMax==360&&native.effects.charge==72);
    assert(native.counterDamage()==240&&native.counterattack()&&native.lives==840&&native.guard==0);
    Run nativeResume;assert(nativeResume.decode(native.encode())&&nativeResume.encode()==native.encode());
    assert(nativeResume.baseArmor==120&&nativeResume.enemyAttack==600&&!nativeResume.counterattack());
    // 턴이 돌면 방어구가 채운다: 장착분 120 의 30% = 36 + 갑옷 블록 240 의 30% = 72 → 108. 다 차지 않는다.
    nativeResume.finish();assert(nativeResume.lives==840&&nativeResume.guard==108&&nativeResume.guardMax==360);
    {
        //두 번째 턴: 통 108 로 300 을 받으면 체력은 192 만 깎인다. 그 뒤 또 108 이 찬다.
        Run again=nativeResume;again.enemyAttack=300;assert(again.attack(equipped));while(again.step()){}
        assert(again.guard==108&&again.counterDamage()==192&&again.counterattack()&&again.lives==840-192&&again.guard==0);
        again.finish();assert(again.guard==108);
        //방어구가 없으면 통도 없다: 장착분만 36 씩.
        Run bare=armed();bare.setVitals(1800,120);bare.enemyAttack=500;assert(bare.guard==120);
        assert(bare.attack(stats));while(bare.step()){}
        assert(bare.counterattack()&&bare.lives==bare.maxLives-380&&bare.guard==0);bare.finish();assert(bare.guard==36);
    }
    nativeResume.setVitals(3600,180);assert(nativeResume.lives==1680&&nativeResume.baseArmor==180&&nativeResume.guardMax==420&&nativeResume.guard==168);
    Run legacyNine=armed();legacyNine.lives=2;
    std::string nine=legacyNine.encode();nine.replace(4,2,"9");
    for(int i=0;i<9;++i)nine.erase(nine.find_last_of(' '));
    assert(resumed.decode(nine)&&!resumed.realVitals&&resumed.lives==2);
    resumed.setVitals(1500,75);assert(resumed.lives==600&&resumed.maxLives==1500&&resumed.baseArmor==75);
    nativeResume.wave=14;nativeResume.enemyHp=1;
    assert(nativeResume.attack(equipped));while(nativeResume.step()){}
    nativeResume.finish();assert(nativeResume.stage==1&&nativeResume.lives==nativeResume.maxLives&&nativeResume.guard==nativeResume.guardMax&&nativeResume.guardMax==420);
    std::cout<<"PASS native HP/armor, fractional v9 migration, equipment mitigation, v10 resume, and stage recovery\n";
    std::cout<<"PASS 15 waves, bosses 5/10/15, counterattack after allies, one hit across resume, block/stun/death and v8 migration\n";
}
