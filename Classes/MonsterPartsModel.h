#pragma once
#include <algorithm>
#include "Data/MonsterPartsData.h"

// One attack per active body-part weapon (1..3). Other blocks are passive stats.
namespace MonsterParts {
struct Loadout {
    int species=-1,count=0,level=1,weaponCount=0;
    int part[9]={},weapon[3]={},weight[RoleCount]={};
    Role role[9]={};
};
inline const EnemyDef* enemy(int npc){return npc>=3&&npc<3+EnemyCount?&Enemies[npc-3]:nullptr;}
inline int band(int wave){return wave>=9?2:wave>=4?1:0;}
inline Loadout loadout(int npc,int wave){
    Loadout out;const auto* e=enemy(npc);if(!e)return out;
    out.species=e->species;const auto& s=Species[out.species];
    const int boss=wave==14?2:(wave==4||wave==9?1:0);
    out.level=std::min(6,1+std::max(0,wave)/4+boss);
    out.count=std::max(s.count,band(wave)==2?9:band(wave)==1?6:4);
    int passives[5],passiveCount=0;
    for(int i=0;i<s.count;++i){
        out.part[i]=i;out.role[i]=Parts[s.first+i].role;
        if(out.role[i]==Attack)out.weapon[out.weaponCount++]=i;
        else if(out.role[i]!=Core)passives[passiveCount++]=i;
    }
    for(int i=s.count;i<out.count;++i){
        // Growth copies passive parts only. With no passive artwork, an attack
        // silhouette can be reused as a clearly labelled reinforcement block.
        const int local=passiveCount?passives[(i-s.count)%passiveCount]:out.part[out.weapon[(i-s.count)%out.weaponCount]];
        out.part[i]=local;out.role[i]=passiveCount?Parts[s.first+local].role:Support;
    }
    for(int i=0;i<out.count;++i)out.weight[out.role[i]]+=out.level;
    return out;
}
inline const ActionDef& action(int npc,int weapon){
    static const ActionDef fallback={u8"공격",Strike,0,100,1};
    const auto* e=enemy(npc);if(!e)return fallback;
    const auto& s=Species[e->species];return s.actions[std::max(0,weapon)%s.weaponCount];
}
inline const char* roleName(Role role){
    static const char* names[]={u8"핵",u8"공격",u8"피해 보강",u8"방어 보강",u8"회복 보강"};
    return role>=Core&&role<RoleCount?names[role]:u8"부위";
}
inline int defensePct(const Loadout& l){return std::min(20,l.weight[Guard]*2);}
inline int attackBonusPct(const Loadout& l){return std::min(40,l.weight[Support]);}
inline int piercePct(const Loadout& l,const ActionDef& a){return a.kind==Rush?10+std::min(20,l.weight[Support]*2):0;}
inline long long incomingDamage(long long damage,const Loadout& l){return damage<=0?0:std::max(1LL,damage*(100-defensePct(l))/100);}
inline long long weaponDamage(long long base,const Loadout& l,int weapon){
    if(l.species<0||weapon<0||weapon>=l.weaponCount)return 0;
    const auto& s=Species[l.species];
    // The existing per-turn budget is divided across weapons before action and
    // passive modifiers. More weapons do not multiply the whole turn's budget.
    const long long share=std::max(0LL,base)/l.weaponCount+(weapon==0?std::max(0LL,base)%l.weaponCount:0);
    return share*s.actions[weapon].powerPct/100*(100+attackBonusPct(l))/100;
}
inline long long attackDamage(long long base,const Loadout& l){
    long long total=0;for(int i=0;i<l.weaponCount;++i)total+=weaponDamage(base,l,i);return total;
}
inline long long absorbed(long long base,const Loadout& l,long long guard){
    long long total=0;
    for(int i=0;i<l.weaponCount;++i){
        const long long hit=weaponDamage(base,l,i);
        const long long blocked=std::min(guard,hit-hit*piercePct(l,Species[l.species].actions[i])/100);
        total+=blocked;guard-=blocked;
    }
    return total;
}
inline long long healing(long long hp,long long maximum,const Loadout& l){
    if(l.weight[Recovery]<=0||hp<=0||hp>=maximum)return 0;
    const int pct=1+std::min(2,l.weight[Recovery]/4); // passive regeneration, capped at 3% per turn
    return std::min(maximum-hp,std::max(1LL,maximum*pct/100));
}
inline long long share(long long total,const Loadout& l,int slot){
    if(slot<0||slot>=l.count||l.role[slot]!=Attack||l.weaponCount<=0)return 0;
    for(int i=0;i<l.weaponCount;++i)if(l.weapon[i]==slot)return total/l.weaponCount+(i==0?total%l.weaponCount:0);
    return 0;
}
}
