#include "../../Classes/MergeCombatPresentation.h"
#include <cassert>
#include <iostream>
int main() {
    MergeCombat::EnemyPhases enemy;enemy.begin(24,40);
    assert(enemy.walkingIn(0)&&enemy.walkingIn(23)&&!enemy.walkingIn(24));
    assert(enemy.impact()==44&&enemy.returnStart()==76&&enemy.end()==100);
    assert(!enemy.walkingBack(enemy.impact())&&enemy.walkingBack(76));
    const std::vector<float> steps={0,0,4,4,8};
    assert(MergeCombat::walkProgress(steps,0)==0&&MergeCombat::walkProgress(steps,.25f)==0);
    assert(MergeCombat::walkProgress(steps,.5f)==.5f&&MergeCombat::walkProgress(steps,1)==1);
    enemy.begin(0,30);assert(!enemy.walkingIn(0)&&!enemy.walkingBack(100));
    assert(MergeCombat::lobbyCastleLift(640,850)==0);
    const float baseCenter=((1445.f-83)*640/1089+40+96)*.5f;
    assert(std::abs(baseCenter+MergeCombat::lobbyCastleLift(640,1408)-704)<.001f);
    assert(MergeCombat::lobbyCastleLift(640,1024)>0&&MergeCombat::lobbyCastleLift(640,1024)<MergeCombat::lobbyCastleLift(640,1408));
    assert(std::abs(MergeCombat::lobbyCastleLift(1280,2816)-2*MergeCombat::lobbyCastleLift(640,1408))<.001f);
    MergeCombat::ResidentReveal reveal;
    for(int i=0;i<60;++i){reveal.update(false);assert(!reveal.visible()&&!reveal.arriving());}
    reveal.update(true);assert(!reveal.visible()&&reveal.arriving());
    reveal.update(true);assert(reveal.visible()&&reveal.arriving()&&reveal.progress()>0&&reveal.progress()<1);
    for(int i=0;i<60;++i)reveal.update(true);
    assert(reveal.visible()&&!reveal.arriving()&&reveal.progress()==1);
    reveal.update(false);assert(!reveal.visible());
    assert(MergeCombat::companionZoom(1.5f)>1.1999f&&MergeCombat::companionZoom(1.5f)<1.2001f);
    MergeCombat::DeckMergeTimeline merge;
    assert(!merge.running()&&!merge.converging());merge.begin();
    assert(merge.converging()&&merge.x(300,350)==300);
    merge.advance(9);assert(merge.converging()&&merge.x(300,350)==325);
    merge.advance(9);assert(!merge.converging()&&merge.running()&&merge.x(300,350)==350);
    merge.advance(42);assert(!merge.running());
    MergeCombat::AnimatedValue guard;
    assert(guard.set(3)==3&&guard.value==0);
    guard.advance(.1f);assert(guard.value>0&&guard.value<3);
    const double halfway=guard.value;guard.advance(.1f);assert(guard.value>halfway&&guard.value<3);
    guard.advance(.5f);assert(guard.value==3);
    assert(guard.set(5)==2&&guard.value==3);
    guard.advance(.1f);const double interrupted=guard.value;
    assert(guard.set(1)==-4&&guard.value==interrupted);
    guard.advance(.5f);assert(guard.value==1);
    assert(MergeCombat::bulletAppearance(6,36)==0.f);
    assert(MergeCombat::bulletAppearance(12,36)==.5f);
    assert(MergeCombat::bulletAppearance(18,36)==1.f);
    assert(MergeCombat::bulletAppearance(35,36)==1.f);
    for(int elapsed=0;elapsed<=90;++elapsed)assert(MergeCombat::actorStep(elapsed,90)>=0&&MergeCombat::actorStep(elapsed,90)<=12);
    assert(MergeCombat::actorStep(0,90)==0&&MergeCombat::actorStep(90,90)==0);
    assert(MergeCombat::actorStep(36,90)==12);
    for(int motion:{12,48,180})for(int travel:{0,32,90}) {
        MergeCombat::Timeline t;t.begin(motion,motion/2,travel);
        int hits=0;
        while(!t.finished()) {
            const int before=t.elapsed;
            if(t.advance()){++hits;assert(t.elapsed==t.impact);}
            if(t.elapsed<t.impact)assert(hits==0);
            if(t.flying())assert(t.elapsed>=t.release&&t.elapsed<t.impact);
            assert(t.elapsed==before+1);
        }
        assert(hits==1&&t.elapsed>=motion&&t.elapsed>t.impact);
        assert(!t.advance());
    }
    // A hero request starts only after the companion's entire cast, including long skills.
    MergeCombat::Timeline hero;hero.begin(48+180,48+120,0);
    while(hero.elapsed<168){const bool hit=hero.advance();assert(hit==(hero.elapsed==168));}
    assert(!hero.finished());
    while(!hero.finished())assert(!hero.advance());
    for(int count=1;count<=64;++count)for(int i=0;i<count;++i) {
        const auto p=MergeCombat::position(i,count,384,660,1,84);
        assert(p.x>=300&&p.x<=384&&p.y==660);
        for(int j=0;j<i;++j){const auto q=MergeCombat::position(j,count,384,660,1,84);assert(p.x!=q.x&&p.y==q.y);}
    }
    std::cout<<"PASS impact once, full motion/recovery gating, hero handoff and all 64 deck positions\n";
}
