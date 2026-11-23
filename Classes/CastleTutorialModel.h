#pragma once
// 합성 룰렛 전투판 튜토리얼의 순수 상태기(docs/기획_튜토리얼_합성.md).
// 몬스터 두 마리: 룰렛 → 착지 관찰(결과는 저절로 판에 내려앉는다) → 합성(같은 블록은 저절로 합쳐진다, 둘째 룰렛) → 공격 → 보상
// → (둘째) 번개 관찰 → 반격을 맞는다 → 방어막 관찰 → 대포 → 끝.
// 옛 사건 이름(Entered·Setup·ShopOpened·Bought·Next)은 호출하는 자리가 남아 있어 값만 둔다 - 어디로도 가지 않는다.
namespace CastleTutorial {
enum Step { Welcome, Depart, Spin, Land, Merge, Attack, Reward, Energy, Guard, Shield, Cannon, Free, Done };
enum Event { Next, Entered, Placed, Setup, Started, ShopOpened, Bought, Spun, Merged, Attacked, RewardClosed, Observed, CounterTaken, CannonFired };
inline int Clamp(int step){return step<0?-1:step>Done?Done:step;}
inline bool Observing(int step){return step==Land||step==Energy||step==Shield||step==Free;}   //조작 없이 2초 보는 단계
inline bool Skippable(int step){return step>=Attack&&step<Done;}                 //합성까지 해 본 뒤에만 건너뛴다
inline int Advance(int step,Event event){
 if((step==Welcome&&event==Next)||(step==Depart&&event==Started)||
    (step==Spin&&event==Spun)||(step==Land&&event==Observed)||
    (step==Merge&&event==Merged)||(step==Attack&&event==Attacked)||
    (step==Reward&&event==RewardClosed)||(step==Energy&&event==Observed)||
    (step==Guard&&event==CounterTaken)||(step==Shield&&event==Observed)||
    (step==Cannon&&event==CannonFired)||(step==Free&&event==Observed))return step+1;
 return step;
}
// 로비 힌트(튜토리얼 뒤 처음 쓸 수 있게 된 순간 한 번). 저장은 단계와 같은 플래그의 윗 비트.
enum Hint { HintVault=1, HintExpedition=2, HintEquip=4, HintCastle=8, HintStartEvent=16 };
}
