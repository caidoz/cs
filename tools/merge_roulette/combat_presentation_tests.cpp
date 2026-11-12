#include "../../Classes/MergeCombatPresentation.h"
#include <cassert>
#include <iostream>
int main() {
    MergeCombat::ResidentReveal reveal;
    for(int i=0;i<60;++i){reveal.update(false);assert(!reveal.visible()&&!reveal.arriving());}
    reveal.update(true);assert(!reveal.visible()&&reveal.arriving());
    reveal.update(true);assert(reveal.visible()&&reveal.arriving()&&reveal.progress()>0&&reveal.progress()<1);
    for(int i=0;i<60;++i)reveal.update(true);
    assert(reveal.visible()&&!reveal.arriving()&&reveal.progress()==1);
    reveal.update(false);assert(!reveal.visible());
    assert(MergeCombat::companionZoom(1.5f)>1.1999f&&MergeCombat::companionZoom(1.5f)<1.2001f);
    MergeCombat::AnimatedValue guard;
    assert(guard.set(3)==3&&guard.value==0);
    guard.advance(.1f);assert(guard.value>0&&guard.value<3);
    const float halfway=guard.value;guard.advance(.1f);assert(guard.value>halfway&&guard.value<3);
    guard.advance(.5f);assert(guard.value==3);
    assert(guard.set(5)==2&&guard.value==3);
    guard.advance(.1f);const float interrupted=guard.value;
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
        const auto p=MergeCombat::position(i,count,384,660,1,190);
        assert(p.x>=300&&p.x<=384&&p.y>=660&&p.y+150<=850);
        for(int j=0;j<i;++j){const auto q=MergeCombat::position(j,count,384,660,1,190);assert(p.x!=q.x||p.y!=q.y);}
    }
    std::cout<<"PASS impact once, full motion/recovery gating, hero handoff and all 64 deck positions\n";
}
