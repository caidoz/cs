// 합성 전투 밸런스 측정: 번개 5개(룰렛·공격·대포 각 1개) 안에 몬스터를 잡는지, 히어로 검 / 동료 / 대포의
// 피해 지분이 어떤지를 실제 Run 모델로 돌려 본다. 적 체력·공격 곡선은 Func_MergeRoulette.cpp 의
// hpFor/waveHp/waveAttack 을 그대로 옮겼다(상수 330 · 1.17). 동료 power 는 crewData STR 의 성급 중앙값이다.
//   cl /EHsc /std:c++14 /utf-8 tools\merge_roulette\balance_sim.cpp /Fe:output\merge-roulette\balance-sim.exe
#include "../../Classes/MergeRouletteModel.h"
#include "../../Classes/Data/MergeTreeData.h"
#include "../../Classes/MergeWaveCurve.h"
#include <cmath>
#include <cstdio>
#include <map>
using namespace MergeRoulette;
static int gHpMul=100;   //MERGE_WAVE_HP_PCT 위에 더 곱해 볼 배율(%)
static long long gPower=81;
long long waveHp(int stage,int wave){return MergeWave::waveHp(stage,wave,gPower)*gHpMul/100;}
long long waveAttack(int stage,int wave){return MergeWave::waveAttack(stage,wave);}
// crewData STR 의 성급별 중앙값(★1 15~25, ★2 27~60, ★3 64~180, ★4 194~723, ★5 778~1206, ★6 1295~1498)
static const long long StarPower[7]={0,20,40,110,400,1000,1400};
struct Result { int waves=0; long long hero=0,crew=0,cannon=0; int actions=0; bool died=false,stuck=false; };
Result simulate(int stage,int maxStar,long long weapon,int cannonPct,unsigned seed,bool useCannon){
    Roster roster;for(int c=0;c<64;++c){const int star=MergeTrees::Star(c);if(star>=1&&star<=maxStar)roster.add(MergeTrees::Role(c),star,c);}
    Stats st;st.weapon=weapon;st.realVitals=true;
    for(int c=0;c<64;++c){st.crew[c].power=StarPower[std::max(1,std::min(6,MergeTrees::Star(c)))];st.crew[c].trait=(Trait)MergeTrees::Trait(c);}
    for(int g=0;g<GearCount;++g)for(int l=1;l<=MaxLevel;++l)st.armor[g][l-1]=20*l;
    gPower=std::max(weapon*Run::HeroGearPct/100,StarPower[std::max(1,std::min(6,maxStar))]);   //게임의 rosterPowerIndex 와 같은 식
    Run run;run.roster=&roster;run.rng=seed|1;run.stage=stage;
    std::vector<int> pool;for(int r=0;r<Roles;++r)if(roster.has(r,1))pool.push_back(r);for(int f=Sword;f<FamilyCount;++f)pool.push_back(f);
    int weights[FamilyCount];for(int f=0;f<FamilyCount;++f)weights[f]=f<Roles?1:4;
    if(!run.start(pool,weights)){std::printf("start failed\n");return {};}
    run.setVitals(60,0);
    run.enemyHp=run.enemyMax=waveHp(stage,0);run.enemyAttack=waveAttack(stage,0);
    Result res;
    auto place=[&](){
        while(!run.tray.empty()){if(!run.autoPlace(0))run.tray.erase(run.tray.begin());}
        Run plan;bool fromTray=false;int src=-1,dst=-1;
        while(run.automaticMergePlan(plan,fromTray,src,dst))run=plan;
    };
    place();
    int guard=0;
    while(run.wave<WavesPerStage&&run.stage==stage&&!run.lost&&++guard<2000){
        const long long shell=std::max(1LL,weapon*cannonPct/100);
        const long long preview=run.preview(st);
        bool acted=false;
        if(preview>=run.enemyHp||run.battleEnergy==1||!run.canSpin()){
            if(useCannon&&shell>=run.enemyHp&&preview<run.enemyHp){acted=run.fireCannon(st,shell);if(acted)res.cannon+=std::min(shell,run.enemyHp);}
            else if(useCannon&&shell>preview){acted=run.fireCannon(st,shell);if(acted)res.cannon+=std::min(shell,run.enemyHp);}
            else {
                acted=run.attack(st);
                if(acted)for(const Shot& s:run.shots){const long long d=s.damage;if(s.block.family>=Sword)res.hero+=d;else res.crew+=d;}
            }
            if(!acted){res.stuck=true;break;}
            run.spendBattleEnergy();++res.actions;
            while(run.step()){}
            const bool killed=run.enemyHp==0;
            const int hearts=run.finish();
            run.battleEnergy=std::min((int)Run::BattleEnergyMax,run.battleEnergy+hearts);
            if(killed){run.refillBattleEnergy();++res.waves;if(run.stage==stage){run.enemyHp=run.enemyMax=waveHp(stage,run.wave);run.enemyAttack=waveAttack(stage,run.wave);}}
            else if(run.battleEnergy<=0){res.stuck=true;break;}
        } else {
            if(!run.spendBattleEnergy()){res.stuck=true;break;}
            ++res.actions;
            if(!run.spin()){run.battleEnergy++;res.stuck=true;break;}
            place();
        }
        if(run.lost){res.died=true;break;}
    }
    return res;
}
int main(int argc,char** argv){
    const int widths[]={0,1,2,3,2,5,3},heights[]={0,1,1,1,2,1,2};
    for(int gear=0;gear<GearCount;++gear)for(int lv=1;lv<=MaxLevel;++lv)MergeBoard::SetGearShape(gear,lv,widths[lv],heights[lv]);
    const int cannonPct=argc>1?std::atoi(argv[1]):200;gHpMul=argc>2?std::atoi(argv[2]):100;
    struct Case{const char* name;int stage;int maxStar;long long weapon;};
    const Case cases[]={{"1성 · ★1~2 동료 · 공격 27",0,2,27},{"1성 · ★1~4 동료 · 공격 27",0,4,27},
                        {"3성 · ★1~4 동료 · 공격 60",2,4,60},{"5성 · ★1~6 동료 · 공격 120",4,6,120}};
    std::printf("HeroGearPct=%d cannon Lv0=%d%% curve=%d%% x%d%% powerBase=%d  (평균 20판)\n",(int)Run::HeroGearPct,cannonPct,(int)MERGE_WAVE_HP_PCT,gHpMul,(int)MERGE_POWER_BASE);
    for(const Case& c:cases)for(int useCannon=0;useCannon<2;++useCannon){
        double waves=0,hero=0,crew=0,cannon=0,actions=0;int died=0,stuck=0;const int N=20;
        for(unsigned s=1;s<=N;++s){Result r=simulate(c.stage,c.maxStar,c.weapon,cannonPct,s*7919u,useCannon!=0);
            waves+=r.waves;hero+=r.hero;crew+=r.crew;cannon+=r.cannon;actions+=r.actions;died+=r.died;stuck+=r.stuck;}
        const double total=std::max(1.0,hero+crew+cannon);
        std::printf("%-28s %s | 웨이브 %.1f/15  행동 %.0f  지분 히어로 %2.0f%% 동료 %2.0f%% 대포 %2.0f%%  사망 %d 교착 %d\n",
            c.name,useCannon?"대포 O":"대포 X",waves/N,actions/N,100*hero/total,100*crew/total,100*cannon/total,died,stuck);
    }
    return 0;
}
