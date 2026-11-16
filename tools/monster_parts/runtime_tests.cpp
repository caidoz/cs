#include "../../Classes/MergeRouletteModel.h"
#include <cassert>
#include <iostream>
using MergeRoulette::Run;
Run fixture(int npc){
    Run r;r.choosing=false;r.realVitals=true;r.lives=r.maxLives=10000;
    r.guard=r.guardMax=500;r.enemyHp=6000;r.enemyMax=10000;r.enemyAttack=100;
    r.configureMonster(npc);r.attacking=true;return r;
}
int main(){
    for(int npc=3;npc<360;++npc){
        int previousCount=0,weaponCount=0;
        for(int wave:{0,4,9,14}){
            const auto l=MonsterParts::loadout(npc,wave);
            assert(l.species>=0&&l.count>=4&&l.count<=9&&l.count>=previousCount);previousCount=l.count;
            int cores=0,weapons=0;for(int i=0;i<l.count;++i){cores+=l.role[i]==MonsterParts::Core;weapons+=l.role[i]==MonsterParts::Attack;}
            assert(cores==1&&weapons==l.weaponCount&&weapons>=1&&weapons<=3);
            if(weaponCount)assert(weaponCount==weapons);weaponCount=weapons;
            assert(MonsterParts::defensePct(l)<=20&&MonsterParts::attackBonusPct(l)<=40);
            for(long long base:{0LL,1LL,1007LL,1000000000000000LL}){
                long long total=0;
                for(int weapon=0;weapon<weapons;++weapon){
                    const auto& a=MonsterParts::action(npc,weapon);assert((a.kind==MonsterParts::Strike||a.kind==MonsterParts::Rush)&&a.hits==1);
                    total+=MonsterParts::weaponDamage(base,l,weapon);
                }
                assert(total==MonsterParts::attackDamage(base,l));
            }
            for(bool half:{false,true}){
                Run r=fixture(npc);r.wave=wave;r.configureMonster(npc);r.effects.half=half;
                long long total=0;for(int weapon=0;weapon<weapons;++weapon)total+=r.monsterWeaponDamage(weapon);
                assert(total==r.counterHit());const auto hp=r.lives,expected=r.counterDamage();
                assert(r.counterattack()&&r.lives==hp-expected);assert(!r.counterattack());
            }
        }
    }
    for(int npc:{4,10,14,21}){
        Run r=fixture(npc);const auto hp=r.enemyHp,lives=r.lives,guard=r.guard,heal=r.monsterHealing();
        assert(heal>0&&heal<=r.enemyMax*3/100&&r.counterHit()>0);
        assert(r.counterattack()&&r.enemyHp==hp+heal&&(r.lives<lives||r.guard<guard)&&r.monsterActionTurn==1);
        assert(!r.counterattack()&&r.enemyHp==hp+heal);
        Run resumed;assert(resumed.decode(r.encode())&&resumed.counterResolved);resumed.finish();assert(resumed.enemyHp==hp+heal);
        r=fixture(npc);r.enemyHp=r.enemyMax-1;assert(r.monsterHealing()==1);r.counterattack();assert(r.enemyHp==r.enemyMax);
        r=fixture(npc);r.skipTurns=1;r.finish();assert(r.enemyHp==6000&&r.monsterActionTurn==0);
        r=fixture(npc);r.enemyHp=0;r.finish();assert(r.wave==1&&r.enemyHp==0&&r.monsterActionTurn==0);
        assert(resumed.decode(r.encode()));resumed.configureMonster(npc);assert(resumed.monsterActionTurn==0);
    }
    Run boar=fixture(12);const auto loadout=boar.monsterLoadout();assert(loadout.weaponCount==2);
    assert(MonsterParts::action(12,0).nativePattern==1&&MonsterParts::action(12,1).nativePattern==0);
    assert(MonsterParts::action(12,1).kind==MonsterParts::Rush);
    const auto hp=boar.lives,predicted=boar.counterDamage();assert(predicted>0);boar.counterattack();assert(boar.lives==hp-predicted&&boar.guard>0);
    boar=fixture(12);boar.passing=true;Run resumed;
    assert(resumed.decode(boar.encode())&&resumed.passing);resumed.counterattack();resumed.finish();assert(resumed.monsterActionTurn==1&&!resumed.passing);
    resumed.wave++;resumed.configureMonster(12);assert(resumed.monsterActionTurn==0);
    std::string old=boar.encode();old.replace(4,2,"11");for(int i=0;i<3;++i)old.erase(old.find_last_of(' '));assert(resumed.decode(old)&&resumed.monsterNpc==-1);
    std::cout<<"PASS 357 monsters: 1..3 active weapons, passive growth, exact damage/absorption, capped passive regeneration, stun/death and save migration\n";
}
