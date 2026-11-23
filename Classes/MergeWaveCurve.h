#pragma once
// 합성 전투의 적 체력·공격 곡선. 게임(Func_MergeRoulette.cpp)과 측정기(tools/merge_roulette/balance_sim.cpp)가
// 같은 식을 쓴다. 상수는 content/balance.tsv → Config/BalanceGenerated.h 에서 난다.
//
//   기준 체력  hpFor(성)            = WAVE_HP_BASE × (WAVE_HP_TIER_MUL/100)^성
//   잡몹 체력  waveHp(성, w, 전력)  = 기준 × MERGE_WAVE_HP_PCT% × (50+10w)% × 보스(소 2·중 2.5·대 3) × 전력 보정
//   적 공격    waveAttack(성, w)    = 기준 × (50+10w)% / 14            (전력 보정 없음 - 히어로 체력은 그만큼 안 큰다)
//   전력 보정  powerFactor(전력)    = sqrt(max(1, 전력 / MERGE_POWER_BASE))
//
// 전력(powerIndex)은 "지금 판에 설 수 있는 가장 센 ★1 블록값" 이다: max(히어로 공격 × HeroGearPct%, 로스터에서
// 가장 센 동료의 power). 동료 STR 이 ★1 15 → ★6 1500 으로 벌어져서, ★4 이상을 들고 1성에 오면 어떤 곡선도
// 무너진다. 그래서 곡선 자체는 ★1~2 로스터·공격 27(블록 81)에 맞추고, 그보다 센 전력은 제곱근만큼만 적을
// 키운다(★4 400 → ×2.2, ★6 1400 → ×4.2). 제곱근이라 강해질수록 여전히 쉬워지되 한 방에 녹지는 않는다.
#include <algorithm>
#include <cmath>
#include "Config/BalanceGenerated.h"
namespace MergeWave {
enum { WavesPerStage=15 };
inline int bossTier(int wave){return wave==4?1:wave==9?2:wave==14?3:0;}
inline long long hpFor(int stage){
    const int tier=std::max(0,std::min(stage,(int)WAVE_HP_MAX_TIER));
    const double hp=WAVE_HP_BASE*std::pow(WAVE_HP_TIER_MUL/100.0,tier);
    return (long long)std::min(hp,1000000000000000.0);
}
inline double powerFactor(long long powerIndex){
    return std::sqrt(std::max(1.0,powerIndex/(double)std::max(1,(int)MERGE_POWER_BASE)));
}
inline long long waveHp(int stage,int wave,long long powerIndex){
    const int w=std::max(0,std::min(WavesPerStage-1,wave)),boss=bossTier(w);
    const long long base=hpFor(stage)*MERGE_WAVE_HP_PCT/100,pct=50+10*w,mul=boss==3?300:boss==2?250:boss==1?200:100;
    const double hp=(double)std::max(1LL,base*pct/100*mul/100)*powerFactor(powerIndex);
    return (long long)std::max(1.0,std::min(hp,1000000000000000.0));
}
inline long long waveAttack(int stage,int wave){
    const int w=std::max(0,std::min(WavesPerStage-1,wave));
    return std::max(1LL,hpFor(stage)*(50+10*w)/100/14);
}
}
