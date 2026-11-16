#include "../../Classes/MergeRouletteModel.h"
#include <cassert>
#include <cstdio>
#include <cmath>
#include <climits>
using namespace MonsterParts;
int main(){
    FILE* report=nullptr;fopen_s(&report,"output/monster-parts-balance.csv","w");assert(report);
    std::fprintf(report,"npc,cmf,wave,weapons,parts,attack_pct,defense_pct,regen_basis_points,turns_fast,turns_standard,turns_weak\n");
    int cases=0,minAttack=200,maxAttack=0,maxTurns[3]={},maxRegen=0,oldMaxAttack=0;
    for(int npc=3;npc<360;++npc)for(int wave=0;wave<15;++wave){
        const auto l=loadout(npc,wave);const long long hp=1000000;
        const int atk=turnPowerPct(l);minAttack=std::min(minAttack,atk);maxAttack=std::max(maxAttack,atk);
        long long oldDamage=0;
        for(int weapon=0;weapon<l.weaponCount;++weapon){
            const long long share=hp/l.weaponCount+(weapon==0?hp%l.weaponCount:0);
            oldDamage+=share*Species[l.species].actions[weapon].powerPct/100*(100+std::min(40,l.weight[Support]))/100;
        }
        oldMaxAttack=std::max(oldMaxAttack,int(oldDamage*100/hp));
        assert(atk>=88&&atk<=128&&defensePct(l)<=12&&attackBonusPct(l)<=18);
        long long regen=0;for(int turn=0;turn<30;++turn)regen+=healing(1,hp,l,turn);
        assert(regen<=hp*15/100&&healing(1,hp,l,12)==0);
        maxRegen=std::max(maxRegen,int(regen*10000/hp));
        int turns[3];int index=0;
        for(int divisor:{3,6,12}){
            long long current=hp;int turn=0;
            while(current>0&&turn<40){
                current=std::max(0LL,current-incomingDamage(hp/divisor,l));
                if(current>0)current+=healing(current,hp,l,turn);
                ++turn;
            }
            assert(current==0&&turn<=16);turns[index]=turn;maxTurns[index]=std::max(maxTurns[index],turn);++index;
        }
        // More weapons never multiply the turn budget, including tiny integers.
        for(long long base:{1LL,7LL,100LL,1000000000000000LL})
            assert(attackDamage(base,l)==base*atk/100);
        std::fprintf(report,"%d,%d,%d,%d,%d,%d,%d,%lld,%d,%d,%d\n",npc,enemy(npc)->cmf,wave+1,l.weaponCount,l.count,atk,defensePct(l),healing(1,hp,l)*10000/hp,turns[0],turns[1],turns[2]);
        ++cases;
    }
    std::fclose(report);
    std::printf("PASS %d monster/wave cases: attack %d..%d%%, lifetime regen <= %.2f%%, max kill turns %d/%d/%d (reference 3/6/12 turns); exact budgets through 10^15\n",cases,minAttack,maxAttack,maxRegen/100.0,maxTurns[0],maxTurns[1],maxTurns[2]);
    std::printf("Previous maximum attack multiplier: %d%%; adjusted: %d%%\n",oldMaxAttack,maxAttack);
}
