#pragma once
// 원정(번개 10개): 전투 없이 바로 정산하는 자동 출정. 템빨용사의 "원정" 과 같은 자리다.
// 보상은 판 상태와 무관하게 히어로 전투력(GetCombatPower) 구간으로 정한 고정표에서 나온다.
// 표만 바꾸면 되도록 순수 함수로 둔다 - 그리는 쪽과 테스트가 같은 식을 쓴다.
namespace MergeExpedition {
enum { Cost=5, Tiers=8 };
struct Row { long long power; long long gold; int cards; int gearLevel; };
// 전투력 하한 · 골드 · 장비 카드 수 · 카드 장비 레벨(합성 전투의 성 클리어 보상과 같은 단위, MakeItemDetail/Grade 의 lv)
// 1성 히어로가 체력 60·전투력 4000 안팎이므로 4000 이 두 번째 칸이다. 골드는 칸마다 두 배 -
// 같은 번개 10개로 치는 일반 전투 10턴의 처치 보상(10×(성+1)×10턴 ≈ 100~1000)보다 조금 후하되 보스 보상은 없다.
static const Row Table[Tiers]={
    {0,      150,  1, 1},
    {4000,   300,  1, 1},
    {8000,   600,  2, 2},
    {16000,  1200, 2, 2},
    {32000,  2400, 3, 3},
    {64000,  4800, 3, 4},
    {128000, 9600, 4, 5},
    {256000, 19200,4, 6},
};
inline int tierFor(long long power){int t=0;for(int i=0;i<Tiers;++i)if(power>=Table[i].power)t=i;return t;}
inline const Row& rowFor(long long power){return Table[tierFor(power)];}
inline bool affordable(long long hearts){return hearts>=Cost;}
}
