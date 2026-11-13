#include "../../Classes/MergeRouletteModel.h"
#include "../../Classes/Data/MergeTreeData.h"
#include <cassert>
#include <iostream>
using namespace MergeRoulette;
Block block(int f,int lv,int x=-1,int y=-1,int crew=-1) {
    Block b;b.family=f;b.level=lv;b.x=x;b.y=y;
    b.crew=f<Roles?(crew>=0?crew:MergeTrees::CrewAt(f,lv,0)):-1;return b;
}
void finish(Run& r) {while(r.step()){}r.finish();}
Roster fullRoster() {
    Roster ro;for(int c=0;c<64;++c)assert(ro.add(MergeTrees::Role(c),MergeTrees::Star(c),c));return ro;
}
int main(int argc,char**) {
    Shape previous=BattleShape(0);
    for(int stage=0;stage<10;++stage){
        const Shape shape=BattleShape(stage);assert(shape.valid());int cells=0;
        for(int y=0;y<Height;++y)for(int x=0;x<Width;++x){
            cells+=shape.contains(x,y);
            if(stage&&previous.contains(x,y))assert(shape.contains(x,y));
        }
        assert(cells==16+2*stage&&shape.width<=9&&shape.height==4);
        previous=shape;
    }
    //---- 장비 칸 모양은 게임이 그림에서 재서 넣는다. 여기는 그림이 없으니 옛
    //표(★1 1×1 · ★2 2×1 · ★3 3×1 · ★4 2×2 · ★5 5×1 · ★6 3×2)를 손으로 넣어
    //합성·배치 규칙이 큰 블록에서도 서는지 본다.
    {static const int w[]={0,1,2,3,2,5,3},h[]={0,1,1,1,2,1,2};
     for(int g=0;g<GearCount;++g)for(int lv=1;lv<=MaxLevel;++lv)MergeBoard::SetGearShape(g,lv,w[lv],h[lv]);}
    const Roster roster=fullRoster();
    Stats st;
    {
        // All six costume families can start, spin, merge and survive a save roundtrip.
        assert(FamilyCount-Roles==6);
        for(int family=Sword;family<FamilyCount;++family) {
            Run r;r.roster=&roster;r.selected=family;
            assert(r.start({family,Sword,0,1},nullptr,true));
            assert(r.board[0].family==family);
            for(int i=0;i<3;++i) {
                const Block& b=r.board[i];
                assert(b.family==r.families[i]);
                if(b.family<Roles)assert(MergeTrees::Role(b.crew)==b.family);
            }
            Run restored;restored.roster=&roster;
            assert(restored.decode(r.encode())&&restored.encode()==r.encode());
            assert(r.spin()&&r.tray.size()==3);
            Run merged;merged.choosing=false;merged.families[0]=family;
            merged.board={block(family,1,0,0),block(family,1,2,0)};
            assert(merged.place(false,0,2,0)&&merged.board.size()==1&&merged.board[0].level==2);
            merged.enemyHp=merged.enemyMax=100000;
            assert(merged.attack(st));finish(merged);
            assert(MergeTrees::GearDetail(family,0,6)==(family==Sword?30:5));
        }
        Run old;old.choosing=false;old.families[0]=Boots;
        old.board={block(Boots,1,0,0)};
        std::string legacy=old.encode();legacy.replace(4,2,"7");for(int i=0;i<4;++i)legacy.erase(legacy.find_last_of(' '));
        Run upgraded;assert(upgraded.decode(legacy)&&upgraded.board[0].family==Boots);
        std::cout<<"PASS six costume equipment families, opening identities and v7 migration\n";
    }
    if(argc>1)return 0;
    {
        // 동료는 1×2 다: 꽉 찬 판에서도 둘을 합치면 두 칸이 빈다. 장비 칸은 위의 표대로 큰다.
        Run r;r.roster=&roster;r.choosing=false;r.families[0]=0;r.families[1]=Armor;
        r.board.push_back(block(0,1,0,0,3));r.board.push_back(block(0,1,1,0,7));   // (0,0)-(0,1), (1,0)-(1,1)
        for(int y=0;y<r.shape.height;++y)for(int x=0;x<r.shape.width;++x)
            if(x>1||y>1)r.board.push_back(block(Armor,1,x,y));
        assert(r.freeCells()==0&&r.drop(false,0,2.03f,.5f));
        assert(r.freeCells()==2&&r.board[r.at(1,0)].level==2&&MergeTrees::Star(r.board[r.at(1,0)].crew)==2);
        const auto unchanged=r.encode();assert(!r.drop(false,r.at(1,0),3.5f,.5f)&&r.encode()==unchanged);
        // 장비 ★1 + ★1 → ★2 는 2칸. 꽉 찬 판이어도 재료 둘이 비켜 준 두 칸에 들어간다(mergedPreview 가 판 전체를 훑는다)
        Run g;g.choosing=false;g.families[0]=Sword;
        for(int y=0;y<g.shape.height;++y)for(int x=0;x<g.shape.width;++x)g.board.push_back(block(Sword,1,x,y));
        assert(g.drop(false,0,1.5f,.5f)&&g.freeCells()==0&&g.board[g.at(0,0)].level==2&&g.at(1,0)==g.at(0,0)&&Wide(g.board[g.at(0,0)])==2);
        // ★2 + ★2 → ★3 은 3칸. 재료 둘이 비킨 네 칸(한 줄)에 3×1 이 서고 한 칸이 남는다
        g.board[g.at(0,0)].level=2;g.board.erase(g.board.begin()+g.at(2,0));g.board.erase(g.board.begin()+g.at(3,0));
        g.board.push_back(block(Sword,2,2,0));   // (0,0)-(1,0) ★2, (2,0)-(3,0) ★2, 나머지 꽉 참
        assert(g.freeCells()==0&&g.drop(false,g.at(2,0),.5f,.5f)&&g.freeCells()==1&&g.board[g.at(0,0)].level==3&&Wide(g.board[g.at(0,0)])==3);
        Run reward;reward.choosing=false;reward.board={block(Sword,1,0,0)};reward.tray={block(Sword,1)};
        assert(reward.autoPlace(0)&&reward.board.size()==2&&reward.board[0].level==1&&reward.board[1].level==1);
        for(int lv=1;lv<=MaxLevel;++lv)assert(Wide(0,lv)==1&&Tall(0,lv)==2&&Wide(Sword,lv)*Tall(Sword,lv)==lv);
        bool pair=false,triple=false;
        for(unsigned seed=1;seed<1000;++seed){
            Run s;s.choosing=false;s.families[0]=Sword;s.families[1]=Armor;s.families[2]=Boots;s.rng=seed;
            //spin 은 칸마다 "장비냐 동료냐"(random(100) < BOARD_GEAR_PCT) 를 먼저 굴리고, 장비면 여섯 부위
            //전부(Sword..Pants) 에서 고른다. 여기는 역할이 없으니 늘 장비다 - 난수를 같은 순서로 되감는다.
            Run expected=s;int reels[3];for(int i=0;i<3;++i){expected.random(100);reels[i]=Sword+(int)expected.random(GearCount);}
            assert(s.spin());
            assert(s.tray.size()==3);
            for(int i=0;i<3;++i)assert(s.tray[i].family==reels[i]&&s.tray[i].level==1);
            const bool all=reels[0]==reels[1]&&reels[1]==reels[2];
            triple|=all;pair|=!all&&(reels[0]==reels[1]||reels[1]==reels[2]||reels[0]==reels[2]);
            while(!s.tray.empty())assert(s.autoPlace(0));
            assert(s.board.size()==3&&s.freeCells()==33);
            for(int i=0;i<3;++i)assert(s.board[i].level==1&&s.board[i].family==reels[i]);
        }
        assert(pair&&triple);
    }
    {
        // 64명이 역할 × ★ 사다리를 이룬다. 포격만 ★6 이 없다.
        int total=0;
        for(int r=0;r<Roles;++r)for(int s=1;s<=6;++s)total+=roster.count[r][s];
        assert(total==64);
        assert(MergeTrees::MaxStar(1)==5&&MergeTrees::MaxStar(0)==6&&MergeTrees::MaxStar(2)==6&&MergeTrees::MaxStar(3)==6);
        assert(MergeTrees::CountAt(0,4)==5&&MergeTrees::CountAt(3,3)==3&&roster.count[1][6]==0);
        assert(MergeTrees::Role(42)==0&&MergeTrees::Star(42)==4&&MergeTrees::Star(63)==6&&MergeTrees::Role(57)==1);
        assert(MergeTrees::GearDetail(Sword,20,3)==32&&MergeTrees::GearDetail(Sword,30,6)==34);
        assert(MergeTrees::GearDetail(Armor,2,6)==7&&MergeTrees::GearDetail(Boots,3,6)==7);
    }
    {
        // 합성: 같은 역할·같은 ★ 이면 동료가 달라도 합쳐지고, 결과는 그 역할의 ★+1 중 하나.
        Run r;r.roster=&roster;r.choosing=false;r.families[0]=0;r.families[1]=1;r.families[2]=Sword;
        int a=MergeTrees::CrewAt(0,1,0),b=MergeTrees::CrewAt(0,1,1);assert(a>=0&&b>=0&&a!=b);
        r.board={block(0,1,0,0,a),block(0,1,5,4,b)};
        assert(r.place(false,0,5,4));assert(r.board.size()==1&&r.board[0].level==2);
        assert(MergeTrees::Role(r.board[0].crew)==0&&MergeTrees::Star(r.board[0].crew)==2);
        // 다른 역할끼리는 안 된다
        r.board.push_back(block(1,2,0,0));
        auto before=r.encode();assert(!r.place(false,1,5,4));assert(r.encode()==before);
        // ★ 사다리를 끝까지: 지휘는 ★6 국왕(63)까지, 포격은 ★5 에서 멈춘다
        for(int lv=2;lv<6;++lv) {
            Run s;s.roster=&roster;s.choosing=false;s.families[0]=0;s.families[1]=1;s.families[2]=Sword;
            s.board={block(0,lv,0,0),block(0,lv,3,0)};
            assert(s.mergeable(s.board[0],s.board[1]));assert(s.place(false,0,3,0));
            assert(s.board.size()==1&&s.board[0].level==lv+1&&MergeTrees::Star(s.board[0].crew)==lv+1);
        }
        Run king;king.roster=&roster;king.choosing=false;king.families[0]=0;
        king.board={block(0,6,0,0),block(0,6,3,0)};assert(!king.mergeable(king.board[0],king.board[1]));
        Run art;art.roster=&roster;art.choosing=false;art.families[0]=1;
        art.board={block(1,5,0,0),block(1,5,3,0)};
        before=art.encode();assert(!art.mergeable(art.board[0],art.board[1])&&!art.place(false,0,3,0)&&art.encode()==before);
        // 장비는 로스터 없이도 6단까지
        Run gear;gear.choosing=false;gear.families[0]=Sword;
        gear.board={block(Sword,5,0,0),block(Sword,5,0,1)};   // 5×1 둘은 두 줄에 선다
        assert(gear.place(false,0,0,1)&&gear.board[0].level==6&&gear.board[0].crew==-1&&Wide(gear.board[0])==3&&Tall(gear.board[0])==2);
    }
    {
        // 시작·스핀: 역할 블록은 늘 동료를 들고 나온다. ★1 이 없는 역할은 시작할 수 없다.
        Run r;r.roster=&roster;r.rng=12345;
        assert(r.start({0,1,2,3,Sword,Armor,Boots}));
        assert(!r.choosing&&r.board.size()==3&&r.tray.empty());
        for(unsigned seed=1;seed<=5000;++seed){
            Run opening;opening.roster=&roster;opening.rng=seed;
            assert(opening.start({0,1,2,3,Sword,Armor,Boots,Helm,Gloves,Pants}));
            assert(std::any_of(opening.board.begin(),opening.board.end(),[](const Block& b){return b.family==Sword;}));
        }
        Run noWeapon;noWeapon.roster=&roster;assert(!noWeapon.start({0,1,Armor}));
        for(const Block& b:r.board)assert(b.level==1&&(b.family>=Roles||(b.crew>=0&&MergeTrees::Star(b.crew)==1&&MergeTrees::Role(b.crew)==b.family)));
        Roster thin;thin.add(0,2,24);
        Run no;no.roster=&thin;assert(!no.start({0,Sword,Armor}));
        for(int i=0;i<10;++i) {assert(r.spin());assert(!r.spin());
            assert(r.tray.size()==3);
            for(const Block& b:r.tray) {assert(b.level==1);assert(b.family>=Roles||(b.crew>=0&&MergeTrees::Star(b.crew)==b.level));}
            r.tray.clear();}
        assert(r.spins==0&&!r.spin());
        assert(r.lives==r.maxLives);
    }
    {
        // 피해: 동료 = power × 2^(★-1), 장비 = 칸이 느는 단 ×3. 표식 → 고무 → 검 의 타순 효과는 BoardModel 과 같다.
        // 단 차례의 방향이 다르다 - Run 은 오른쪽 열이 전열(ordered: x 큰 쪽 먼저), BoardModel 은 행 우선(x 작은 쪽 먼저).
        // 그래서 같은 줄을 Run 에는 거울로 놓는다.
        Stats d;d.weapon=50;
        d.crew[3].power=100;d.crew[3].trait=Expose;   // 지휘 ★1 원로 촌장
        d.crew[2].power=100;d.crew[2].trait=Inspire;  // 지원 ★1 약초 할머니
        Run r;r.roster=&roster;r.choosing=false;r.enemyHp=r.enemyMax=100000;r.families[0]=0;r.families[1]=2;r.families[2]=Sword;
        r.board={block(0,1,2,0,3),block(2,2,1,0,2),block(Sword,3,0,0)};   // 표식(x=2) → 고무(x=1) → 검(x=0)
        assert(r.preview(d)==100+240+1080);   // 검 Lv3 = 50×9(장비 ×3) ×1.2 ×2
        MergeBoard::Lineage lineages[3]={{LINEAGE_CREW,0,TRAIT_EXPOSE,100,0},{LINEAGE_CREW,2,TRAIT_INSPIRE,100,0},{LINEAGE_SWORD,-1,TRAIT_NONE,50,0}};
        MergeBoard::Board source;MergeBoard::Reset(source,lineages,5);
        MergeBoard::Place(source,0,1,0,0);MergeBoard::Place(source,1,2,1,0);MergeBoard::Place(source,2,3,2,0);
        MergeBoard::AttackPlan plan;MergeBoard::PlanAttack(source,plan);
        assert(plan.damage==r.preview(d));
        long long empowered=r.preview(d);assert(r.attack(d));finish(r);
        assert(r.damageDone==empowered&&r.board.size()==3&&r.lives==4&&r.spins==10); // 판은 남고, 적 턴에 목숨 하나
        Run reversed;reversed.roster=&roster;reversed.choosing=false;reversed.families[0]=0;reversed.families[1]=2;reversed.families[2]=Sword;
        reversed.board={block(Sword,3,3,0),block(2,2,2,0,2),block(0,1,0,0,3)};   // 검이 먼저 나가면 버프를 못 받는다
        assert(reversed.preview(d)<empowered);
    }
    {
        // 갑옷·빙결·목걸이. 소환은 ★5 부터.
        Run r;r.roster=&roster;r.choosing=false;r.enemyHp=r.enemyMax=100000;r.wave=9;r.lives=5;
        r.board={block(Armor,4,0,0),block(Sword,1,3,0)};
        assert(r.attack(st));finish(r);assert(r.lives==5);           // Lv4 갑옷: 적 턴 삭제
        r.board={block(Sword,1,0,0)};assert(r.attack(st));finish(r);assert(r.lives==3);   // 보스 2
        r.board={block(Armor,2,0,0)};assert(r.attack(st));finish(r);assert(r.lives==3);   // 절반 1 → 보호 1
        Stats summ=st;summ.crew[57].summon=true;    // 기함 함포선장 ★5
        Run s;s.roster=&roster;s.choosing=false;s.enemyHp=s.enemyMax=100000;s.families[0]=1;
        s.board={block(1,5,0,0,57)};assert(s.attack(summ));finish(s);assert(s.summons.size()==1&&s.summons[0].summonTurns==3);
        Run n;n.roster=&roster;n.choosing=false;n.enemyHp=1;n.enemyMax=330;n.families[0]=Sword;n.families[1]=Boots;
        n.board={block(Sword,1,0,0),block(Boots,2,2,0),block(Boots,5,0,1)};   // 목걸이 Lv5 는 5×1
        assert(n.attack(st));while(n.step()){}int hearts=n.finish();
        assert(hearts==2&&n.spins==12&&n.wave==1&&n.reward==10&&n.board.size()==3);
    }
    {
        // 저장: v6 만 읽는다. 동료 번호까지 왕복한다. 공격 중에도.
        Run r;r.roster=&roster;r.choosing=false;r.families[0]=0;r.families[1]=Sword;r.families[2]=Boots;
        r.board={block(0,MaxLevel,0,0,63),block(Sword,2,4,3)};r.tray={block(Boots,3)};
        Run copy;copy.roster=&roster;assert(copy.decode(r.encode()));assert(copy.encode()==r.encode()&&copy.board[0].crew==63);
        auto original=copy.encode();
        assert(!copy.decode("MR3 5 1 0"));assert(!copy.decode("MR3 1 junk"));assert(copy.encode()==original);
        Run overlap=r;overlap.board.push_back(block(0,1,0,0,3));assert(!copy.decode(overlap.encode()));
        overlap=r;overlap.board[0].level=99;assert(!copy.decode(overlap.encode()));
        overlap=r;overlap.board[0].crew=-1;assert(!copy.decode(overlap.encode()));     // 역할 블록은 동료가 있어야
        overlap=r;overlap.board[1].crew=3;assert(!copy.decode(overlap.encode()));      // 장비 블록은 없어야
        assert(!copy.decode(r.encode()+" garbage"));
        Run a;a.roster=&roster;a.choosing=false;a.enemyHp=a.enemyMax=100000;a.drafted=true;a.families[0]=0;a.families[1]=Armor;a.families[2]=Boots;
        a.board={block(0,3,0,0),block(Armor,2,3,0),block(Boots,2,0,2)};   // 동료는 1×2(0,0)-(0,1), 장비 Lv2 는 2×1 — 겹치지 않게
        assert(a.attack(st));
        while(a.step()) {Run resumed;resumed.roster=&roster;assert(resumed.decode(a.encode()));assert(resumed.encode()==a.encode());a=resumed;}
        assert(a.finish()==2&&a.board.size()==3&&a.lives==5);
    }
    {
        // 무작위 배치 5000회: 기하 보존, 실패는 원자적, 저장 왕복.
        Run r;r.roster=&roster;r.choosing=false;r.families[0]=0;r.families[1]=3;r.families[2]=Sword;
        for(int n=0;n<5000;++n) {
            if(r.tray.empty()) {r.spins=10;r.spin();}
            int x=r.random(8)-1,y=r.random(8)-1;auto old=r.encode();
            bool ok=r.place(true,0,x,y);if(!ok)assert(r.encode()==old);
            for(int i=0;i<(int)r.board.size();++i) {assert(r.fits(r.board[i],i));assert(Run::crewOk(r.board[i]));
                if(r.board[i].family<Roles)assert(MergeTrees::Star(r.board[i].crew)==r.board[i].level&&MergeTrees::Role(r.board[i].crew)==r.board[i].family);}
            Run restored;restored.roster=&roster;assert(restored.decode(r.encode()));
            if(n%20==0) {r.board.clear();r.tray.clear();}
        }
    }
    std::cout<<"PASS merge roulette v6: role ladders to star 6 (artillery stops at 5), random next-star crew, geometry, reel budget, row order damage, armor/chill/neck, summons from star 5, board persists, v6 save roundtrip, 5000 random operations\n";
}
