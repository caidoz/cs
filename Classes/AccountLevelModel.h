#pragma once
#include <algorithm>
// Saved levels are zero-based. Account mastery does not increase combat power.
namespace AccountLevel {
constexpr int Max=99;
inline int bounded(int level){return std::max(0,std::min(Max,level));}
inline long long floor(int level){const long long n=bounded(level);return 100*n+25*n*(n-1)/2;}
inline long long next(int level){return floor(std::min(Max,bounded(level)+1));}
inline int bossExp(int stage){return 100+20*std::max(0,std::min(18,stage));}
inline int energyBonus(int level){return bounded(level);}
inline int advance(int level,long long total){int n=bounded(level);while(n<Max&&total>=next(n))++n;return n;}
inline long long normalizedTotal(int level,long long total){return bounded(level)==Max?floor(Max):total<floor(level)||total>=next(level)?floor(level):total;}
inline long long progress(int level,long long total){return bounded(level)==Max?0:normalizedTotal(level,total)-floor(level);}
}
