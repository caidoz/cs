#include "../../Classes/MergeRouletteModel.h"
#include "../../Classes/MergeExpeditionModel.h"
#include "legacy_snapshot.h"
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
    {
        Run r=armed();r.board.clear();r.shape=Shape();r.shape.width=2;r.shape.height=2;
        for(int y=0;y<Height;++y)r.shape.rows[y]=y<2?3:0;
        for(int y=0;y<2;++y)for(int x=0;x<2;++x){Block b;b.family=Sword;b.x=x;b.y=y;r.board.push_back(b);}
        assert(r.freeCells()==0&&r.canSpin());
        assert(r.spin()&&r.tray.size()==3);
        while(!r.tray.empty())assert(r.scatterPlace(0));
        assert(r.board.size()==7&&!r.boardResolved());
        Run loaded;assert(loaded.decode(r.encode())&&loaded.encode()==r.encode());
        std::cout<<"PASS full board spin scatters all rewards without loss and preserves overlaps across resume\n";
    }

    {
        Run r=armed();r.board.clear();
        for(int i=0;i<4;++i){Block b;b.family=Sword;r.tray.push_back(b);assert(r.autoPlace(0));}
        Run plan;bool tray=false;int source=-1,target=-1,merges=0;
        while(true){
            const auto before=r.encode();const unsigned rng=r.rng;
            if(!r.automaticMergePlan(plan,tray,source,target))break;
            assert(r.encode()==before&&r.rng==rng&&!tray&&source!=target);
            assert(plan.board.size()+1==r.board.size());r=plan;++merges;
        }
        assert(merges==3&&r.board.size()==1&&r.board[0].level==3);
        Run t=armed();t.tray.push_back(t.board[0]);
        assert(t.automaticMergePlan(plan,tray,source,target)&&tray&&plan.tray.empty()&&plan.board[0].level==2);
        t.attacking=true;assert(!t.automaticMergePlan(plan,tray,source,target));
        t.attacking=false;t.board[0].level=MaxLevel;t.tray[0].level=MaxLevel;
        assert(!t.automaticMergePlan(plan,tray,source,target));
        std::cout<<"PASS automatic merge plans preserve live state and RNG, chain, consume tray duplicates, and stop at max level\n";
    }

    {
        Run r=armed();r.enemyHp=r.enemyMax=1;
        Block b=r.board[0];b.x=2;r.board.push_back(b);b.x=4;r.board.push_back(b);
        assert(r.attack(stats)&&r.shots.size()==3);
        for(auto& shot:r.shots)shot.damage=10;
        assert(r.step()&&r.enemyHp==0&&r.nextShot==1);
        assert(!r.step()&&!r.shouldCounterattack());
        Run resumed;assert(resumed.decode(r.encode()));
        for(Run* q:{&r,&resumed}){
            q->finish();assert(!q->attacking&&q->wave==1&&q->reward==10&&q->shots.empty());
            q->finish();assert(q->wave==1&&q->reward==10);
        }
        Run dot=armed();dot.attacking=true;dot.passing=true;dot.enemyHp=0;
        dot.finish();assert(dot.wave==1&&dot.reward==10&&!dot.passing);
        std::cout<<"PASS lethal first hit cancels remaining attacks, rewards once across resume, and resolves lethal pass\n";
    }

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
    Run old=armed();std::string legacy=legacySnapshotV13(old);legacy.replace(4,2,"8");for(int i=0;i<10;++i)legacy.erase(legacy.find_last_of(' '));
    assert(resumed.decode(legacy)&&!resumed.counterResolved);
    // Native HP and armor use the same units in bars, equipment, and actual hits.
    Run native=armed();native.lives=3;native.setVitals(1800,120);native.enemyAttack=600;
    assert(native.lives==1080&&native.maxLives==1800&&native.baseArmor==120);
    // 방어막 통 = 체력 × ShieldPct(100%) 하나. 낀 방어구(120)는 통을 키우지 않는다.
    assert(native.guardMax==1800&&native.guard==1800&&Run::shieldFor(1800)==1800);
    Stats equipped;equipped.realVitals=true;equipped.armor[Armor-Sword][0]=240;
    Block defense;defense.family=Armor;defense.x=1;defense.y=0;native.board.push_back(defense);
    assert(native.attack(equipped)&&native.effects.protect==240&&native.effects.charge==240);
    while(native.step()){}
    // 반격 600 은 통에서 그대로 빠진다(1800 → 1200). 체력은 그대로.
    assert(native.guard==1800&&native.guardMax==1800&&native.guardRecovery()==360);
    assert(native.counterDamage()==0&&native.counterattack()&&native.lives==1080&&native.guard==1200);
    Run nativeResume;assert(nativeResume.decode(native.encode())&&nativeResume.encode()==native.encode());
    assert(nativeResume.baseArmor==120&&nativeResume.enemyAttack==600&&!nativeResume.counterattack());
    // 턴이 돌면 장비가 채운다: 낀 방어구 120 + 갑옷 블록 240 = 360 → 1560. 최대치는 그대로 1800.
    nativeResume.finish();assert(nativeResume.lives==1080&&nativeResume.guard==1560&&nativeResume.guardMax==1800);
    {
        //두 번째 턴: 300 을 받으면 1260, 다시 360 이 차서 1620.
        Run again=nativeResume;again.enemyAttack=300;assert(again.attack(equipped));while(again.step()){}
        assert(again.guard==1560&&again.counterDamage()==0&&again.counterattack()&&again.lives==1080&&again.guard==1260);
        again.finish();assert(again.guard==1620);
        //방어구 블록이 없어도 통은 체력 몫 그대로다. 채우는 것은 낀 방어구 120 뿐.
        Run bare=armed();bare.setVitals(1800,120);bare.enemyAttack=500;assert(bare.guard==1800);
        assert(bare.attack(stats));while(bare.step()){}
        assert(bare.counterattack()&&bare.lives==bare.maxLives&&bare.guard==1300);bare.finish();assert(bare.guard==1420);
        //통을 넘기는 한 방: 2200 이면 1800 은 통이, 400 은 체력이 받는다. 그 뒤 120 이 찬다.
        Run heavy=armed();heavy.setVitals(1800,120);heavy.enemyAttack=2200;
        assert(heavy.attack(stats));while(heavy.step()){}
        assert(heavy.counterDamage()==400&&heavy.counterattack()&&heavy.lives==1400&&heavy.guard==0);heavy.finish();assert(heavy.guard==120);
        //장비가 하나도 없으면 회복도 없다(최소 1 보정 없음).
        Run naked=armed();naked.setVitals(1800,0);naked.enemyAttack=100;
        assert(naked.attack(stats));while(naked.step()){}
        assert(naked.counterattack()&&naked.guard==1700);naked.finish();assert(naked.guard==1700&&naked.guardRecovery()==0);
        //v12 세이브(최대치 = 장비 합)는 체력 비례 통으로 바꿔 찬 채로 잇는다.
        std::string twelve=legacySnapshotV13(again);twelve.replace(4,2,"12");
        Run migrated;assert(migrated.decode(twelve)&&migrated.guardMax==1800&&migrated.guard==1800&&migrated.effects.charge==migrated.effects.protect);
    }
    // 체력이 바뀌면 통도 비례해서 다시 잰다(1560/1800 → 3120/3600). 낀 방어구는 회복량만 바꾼다.
    nativeResume.setVitals(3600,180);assert(nativeResume.lives==2160&&nativeResume.baseArmor==180&&nativeResume.guardMax==3600&&nativeResume.guard==3120);
    Run legacyNine=armed();legacyNine.lives=2;
    std::string nine=legacySnapshotV13(legacyNine);nine.replace(4,2,"9");
    for(int i=0;i<9;++i)nine.erase(nine.find_last_of(' '));
    assert(resumed.decode(nine)&&!resumed.realVitals&&resumed.lives==2);
    resumed.setVitals(1500,75);assert(resumed.lives==600&&resumed.maxLives==1500&&resumed.baseArmor==75);
    nativeResume.wave=14;nativeResume.enemyHp=1;
    assert(nativeResume.attack(equipped));while(nativeResume.step()){}
    nativeResume.finish();assert(nativeResume.stage==1&&nativeResume.lives==nativeResume.maxLives&&nativeResume.guard==nativeResume.guardMax&&nativeResume.guardMax==3600);
    std::cout<<"PASS native HP/armor, HP-sized shield pool refilled by gear, v12 migration, v10 resume, and stage recovery\n";
    // 원정 고정표: 전투력이 오를수록 골드·카드·장비 레벨이 내려가지 않고, 10개 미만이면 못 간다.
    {
        using namespace MergeExpedition;
        assert(Cost==5&&!affordable(4)&&affordable(5));
        assert(tierFor(0)==0&&tierFor(3999)==0&&tierFor(4000)==1&&tierFor(4027)==1&&tierFor(1000000000)==Tiers-1);
        for(int i=1;i<Tiers;++i){
            assert(Table[i].power>Table[i-1].power&&Table[i].gold>=Table[i-1].gold&&Table[i].cards>=Table[i-1].cards&&Table[i].gearLevel>=Table[i-1].gearLevel);
            assert(rowFor(Table[i].power).gold==Table[i].gold&&rowFor(Table[i].power-1).gold==Table[i-1].gold);
        }
        std::cout<<"PASS expedition fixed table by combat power\n";
    }
    // 룰렛 세 칸에는 장비와 동료가 하나씩은 선다(역할이 하나라도 있을 때). 역할이 없으면 셋 다 장비.
    {
        Roster roster;roster.add(0,1,3);
        int mixed=0;
        for(unsigned seed=1;seed<=400;++seed){
            Run s;s.roster=&roster;s.choosing=false;s.families[0]=0;s.families[1]=Sword;s.families[2]=Armor;s.rng=seed;
            assert(s.spin()&&s.tray.size()==3);
            int gears=0;for(const Block& b:s.tray)gears+=b.family>=Sword?1:0;
            assert(gears>=1&&gears<=2);mixed+=gears==2?1:0;
        }
        assert(mixed>100&&mixed<400);   //70:30 동전이라 장비 둘·동료 하나가 흔하되 전부는 아니다
        std::cout<<"PASS every spin mixes gear and crew when a role is available\n";
    }
    std::cout<<"PASS 15 waves, bosses 5/10/15, counterattack after allies, one hit across resume, block/stun/death and v8 migration\n";
}
