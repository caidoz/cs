#pragma once
#pragma pack(push, 8)
// TURNRPG run state. No engine globals, persistent equipment or ACTIONRPG data.
//
// 합성은 6단 = 성급이다. 계열(family)은 역할군 4 + 코스튬 장비 6.
// 같은 역할·같은 ★ 블록 둘을 합치면 그 역할의 ★+1 동료 중 하나가 무작위로
// 나온다(운빨존많겜 식). 어느 동료가 나올 수 있는지는 Roster 가 들고 있고,
// 피해·특성은 Stats 가 동료 번호로 들고 있다. 판은 공격해도 비지 않는다.
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>
#include <sstream>
#include <string>
#include "BoardModel.h"

namespace MergeRoulette {
enum { Width=12, Height=6, Cells=Width*Height, MaxLevel=BLOCK_LV_MAX, SpinLimit=BOARD_SPINS,
       Roles=4, Sword=4, Armor=5, Boots=6, Helm=7, Gloves=8, Pants=9, FamilyCount=10, GearCount=6, WavesPerStage=15, RosterCell=8, SaveVersion=10 };
inline int BossTier(int wave) {return wave==4?1:wave==9?2:wave==14?3:0;}
inline bool DefensiveGear(int family) {return family==Armor||family==Helm||family==Pants;}
struct Shape {
    int width=BOARD_W,height=BOARD_H;
    unsigned rows[Height]={63,63,63,63,63,63};
    bool valid() const {
        if(width<1||width>Width||height<1||height>Height)return false;
        int count=0;
        for(int y=0;y<Height;++y) {if(rows[y]>>width || (y>=height&&rows[y]))return false;count+=rows[y]!=0;}
        return count>0;
    }
    bool contains(int x,int y) const {return x>=0&&y>=0&&x<width&&y<height&&(rows[y]&(1u<<x));}
};
enum Trait { Expose, Inspire, Strike, Volley, Chill, Burn };
inline Shape BattleShape(int stage) {
    Shape out;out.width=4;out.height=4;
    for(auto& row:out.rows)row=0;
    for(int y=0;y<4;++y)out.rows[y]=15;
    const int extra=2*std::max(0,std::min(9,stage));
    // Add adjacent pairs, preserving every previously unlocked cell.
    // Grow horizontally rather than pushing the fixed-size board into the deck.
    for(int i=0;i<extra;++i){const int x=4+i/4,y=i%4;
        out.rows[y]|=1u<<x;out.width=std::max(out.width,x+1);}
    return out;
}
struct Block {
    int family=-1, level=1, crew=-1, x=-1, y=-1;   // crew: 역할 계열이면 동료 번호, 장비면 -1
    //눕혔는가. 장비는 ★5 가 5x1 이라 세로로 눕혀야 들어가는 자리가 많다.
    //동료는 1x1 이라 눕히나 마나 같다.
    bool rot=false;
    bool placed() const { return x>=0 && y>=0; }
};
// 동료 블록은 ★ 에 상관없이 1×2. 장비 블록의 칸 모양은 그림이 정한다 -
// configure() 가 GridGearPart 로 재서 MergeBoard::SetGearShape 에 넣는다(계열
// 줄 = family-Sword). 그래서 무기만 크고 투구·갑옷·목걸이는 1×1 에 머문다.
inline int Wide(int family,int level) { return family<Roles?MergeBoard::BlockWOf(LINEAGE_CREW,level):MergeBoard::GearW(family-Sword,level); }
inline int Tall(int family,int level) { return family<Roles?MergeBoard::BlockHOf(LINEAGE_CREW,level):MergeBoard::GearH(family-Sword,level); }
//눕힌 블록은 가로세로가 바뀐다. 크기를 묻는 곳이 전부 이 둘을 거치므로
//여기 두 줄이면 판정·그리기·저장이 같이 따라온다.
inline int Wide(const Block& b) { return b.rot?Tall(b.family,b.level):Wide(b.family,b.level); }
inline int Tall(const Block& b) { return b.rot?Wide(b.family,b.level):Tall(b.family,b.level); }
// 동료마다 한 방의 세기와 특성. 레벨(=★)은 블록이 들고 있으므로 여기엔 없다.
struct CrewStats {
    long long power=20;
    Trait trait=Strike;
    bool summon=false;     // SKILL3 가 소환 계열이면 ★5·6 블록이 소환수를 남긴다
};
struct Stats {
    CrewStats crew[64];
    long long armor[GearCount][MaxLevel]={};
    bool realVitals=false;
    long long heroHealth=0,heroArmor=0;
    long long weapon=20;   // 검 블록 Lv1 한 방 = 히어로 평타
};
// 역할 × ★ 에 어떤 동료가 설 수 있는가(보유 기준). 합성 결과·릴 결과가 여기서 뽑힌다.
struct Roster {
    int count[Roles][MaxLevel+1]={};
    int crew[Roles][MaxLevel+1][RosterCell]={};
    bool add(int role,int star,int id) {
        if(role<0||role>=Roles||star<1||star>MaxLevel||id<0||id>=64||count[role][star]>=RosterCell)return false;
        for(int k=0;k<count[role][star];++k)if(crew[role][star][k]==id)return true;
        crew[role][star][count[role][star]++]=id;return true;
    }
    bool has(int role,int star) const {return role>=0&&role<Roles&&star>=1&&star<=MaxLevel&&count[role][star]>0;}
    int first(int role,int star) const {return has(role,star)?crew[role][star][0]:-1;}
};
struct Shot { Block block; long long damage=0; int summonTurns=0; };
struct Effects {
    int expose=0, inspire=1, skip=0;
    long long protect=0;
    bool half=false;
    long long dot=0;
    int dotTurns=0;
};
struct Run {
    Shape shape;
    unsigned rng=1;
    int families[3]={Sword,Armor,Boots};
    int selected=Sword, spins=SpinLimit;
    long long lives=5, maxLives=5;
    bool realVitals=false;
    long long baseArmor=0,enemyAttack=1;
    void setVitals(long long hp,long long armor) {
        hp=std::max(1LL,std::min(1000000000000000LL,hp));
        const long double ratio=lives/(long double)std::max(1LL,maxLives);
        lives=lives>0?std::max(1LL,(long long)std::llround(hp*ratio)):0;
        maxLives=hp;baseArmor=std::max(0LL,std::min(1000000000000000LL,armor));realVitals=true;
    }
    long long armorOf(const Block& block,const Stats& st) const {
        if(!DefensiveGear(block.family))return 0;
        return st.realVitals?st.armor[block.family-Sword][std::max(0,std::min(MaxLevel-1,block.level-1))]:MergeBoard::ArmorGuards(block.level);
    }

    //---- 막 합쳐진 자리 ----
    //
    //그리는 쪽이 연출을 걸 자리다. 저장하지 않는다 - 불러오자마자
    //터지는 연출은 거짓말이다.
    //
    //seq 는 볼 때마다 오르는 번호다. 그리는 쪽이 제가 본 번호와 다르면
    //"새로 합쳐졌다" 로 읽고 연출을 시작한다. 같은 자리에서 연달아
    //합쳐도 번호가 달라 놓치지 않는다.
    int mergeX=-1,mergeY=-1,mergeW=0,mergeH=0,mergeLevel=0;
    unsigned mergeSeq=0;
    Block mergeInputs[2],mergeResult; // Presentation event only; never restored from a save.

    //TODO(diag) 합성이 왜 안 되는지. 원인 잡으면 지운다.
    //마지막으로 시도한 합성이 어디서 걸렸는가.
    const char* lastFail="";
    int wave=0, stage=0, skipTurns=0, dotTurns=0, nextShot=0;
    long long enemyHp=330, enemyMax=330, dot=0, reward=0, damageDone=0;
    bool choosing=true, attacking=false, lost=false, drafted=false, counterResolved=false;
    std::vector<Block> board, tray;
    std::vector<Shot> shots, summons;
    Effects effects;
    const Roster* roster=nullptr;   // 저장하지 않는다. 들어올 때 다시 꽂는다.
    unsigned random(unsigned count) {
        rng^=rng<<13; rng^=rng>>17; rng^=rng<<5;
        return count?rng%count:0;
    }
    // 역할 계열의 ★level 동료 하나를 뽑는다. 없으면 -1. 장비 계열은 -1(동료 없음)이 정상.
    int pickCrew(int family,int level) {
        if(family<0||family>=Roles||!roster||!roster->has(family,level))return -1;
        return roster->crew[family][level][random((unsigned)roster->count[family][level])];
    }
    bool canGrow(int family,int level) const {
        if(level>=MaxLevel)return false;
        if(family>=Roles)return true;
        return roster&&roster->has(family,level+1);
    }
    bool fits(const Block& b,int ignore=-1,int ignore2=-1) const {
        if(b.family<0 || b.family>=FamilyCount || b.level<1 || b.level>MaxLevel
           || b.x<0 || b.y<0 || b.x+Wide(b)>shape.width || b.y+Tall(b)>shape.height) return false;
        for(int y=b.y;y<b.y+Tall(b);++y)for(int x=b.x;x<b.x+Wide(b);++x)if(!shape.contains(x,y))return false;
        for(int i=0;i<(int)board.size();++i) {
            if(i==ignore||i==ignore2)continue;
            const Block& a=board[i];
            if(b.x<a.x+Wide(a)&&a.x<b.x+Wide(b)&&b.y<a.y+Tall(a)&&a.y<b.y+Tall(b))return false;
        }
        return true;
    }
    // Repack legacy rectangular saves without losing or combining any blocks.
    bool setShape(const Shape& wanted) {
        if(!wanted.valid()||attacking)return false;
        Run next=*this;next.shape=wanted;
        bool fitsAll=true;
        for(int i=0;i<(int)board.size();++i)if(!next.fits(board[i],i))fitsAll=false;
        if(!fitsAll) {
            next.board.clear();
            for(Block b:board) {
                bool placed=false;
                for(int y=0;y<wanted.height&&!placed;++y)for(int x=0;x<wanted.width&&!placed;++x) {
                    b.x=x;b.y=y;if(next.fits(b)){next.board.push_back(b);placed=true;}
                }
                if(!placed)return false;
            }
        }
        *this=next;return true;
    }
    int at(int x,int y) const {
        for(int i=0;i<(int)board.size();++i) {
            const Block& b=board[i];
            if(x>=b.x && y>=b.y && x<b.x+Wide(b) && y<b.y+Tall(b)) return i;
        }
        return -1;
    }
    // 합쳐지는가: 같은 계열, 같은 ★, 다음 ★ 이 존재(포격은 ★5 가 끝).
    bool mergeable(const Block& a,const Block& b) const {
        return a.family==b.family && a.level==b.level && canGrow(a.family,a.level);
    }
    // 합친 결과(자리·크기·동료)를 미리 본다. 안 들어가면 false. rng 는 건드리지 않는다.
    bool mergedPreview(int target,const Block& moving,int ignore,Block& out) const {
        if(target<0||target>=(int)board.size())return false;
        const Block& t=board[target];
        if(!mergeable(t,moving))return false;
        out=t;++out.level;
        // Same edge-inward placement policy as the existing BoardModel.
        out.x=std::min(out.x,shape.width-Wide(out));
        out.y=std::min(out.y,shape.height-Tall(out));
        if(fits(out,target,ignore)) return true;

        //---- 그 자리에 안 들어가면 다른 자리를 찾는다 ----
        //
        //여기서 자리 하나만 보고 실패를 돌려주고 있었다. 장비는 ★ 마다
        //칸이 늘어서(★4 2x2 -> ★5 5x1) 합친 결과가 재료가 있던 자리에
        //그대로 들어가는 일이 드물다. 그래서 판이 텅 비어 있어도 합치기가
        //조용히 실패했다 - "동료는 합쳐지는데 검은 안 합쳐진다" 가 이것이다.
        //(동료는 ★ 과 무관하게 1x1 이라 늘 제자리에 들어간다.)
        //
        //재료 둘이 비켜 준 칸까지 포함해 판 전체를 훑는다. 원래 자리에서
        //가까운 쪽을 고른다 - 합친 것이 판 반대편으로 튀면 어디로 갔는지
        //눈으로 쫓을 수가 없다.
        //재료 둘이 덮고 있던 한가운데. 합친 것이 그 자리를 중심으로 앉아야
        //눈으로 쫓을 수 있다 - 판 반대편으로 튀면 어디로 갔는지 모른다.
        const float cx=t.x+Wide(t)*.5f,cy=t.y+Tall(t)*.5f;
        Block best=out;float bestScore=-1.0f;

        //눕혀도 본다. ★5 는 5x1 이라 가로로는 안 들어가도 세로로는 들어가는
        //자리가 많다.
        for(int turn=0;turn<2;++turn) {
            Block form=out;form.rot=(turn!=0);
            if(turn && Wide(form)==Tall(form)) continue;   //정사각은 눕혀도 같다

            for(int y=0;y<shape.height;++y) for(int x=0;x<shape.width;++x) {
                Block cand=form;cand.x=x;cand.y=y;
                if(!fits(cand,target,ignore)) continue;

                const float dx=x+Wide(cand)*.5f-cx,dy=y+Tall(cand)*.5f-cy;
                //가운데에서 먼 만큼 벌점. 눕힌 쪽은 아주 조금 뒤로 민다 -
                //같은 거리면 세워 둔 모양이 읽기 쉽다.
                const float score=dx*dx+dy*dy+(turn?0.25f:0.0f);

                if(bestScore<0.0f||score<bestScore) {bestScore=score;best=cand;}
            }
        }

        if(bestScore<0.0f) return false;
        out=best;
        return true;
    }
    // Validate first: a failed merge/move never loses or changes either block.
    bool place(bool fromTray,int index,int x,int y) {
        if(choosing || attacking || lost) return false;
        std::vector<Block>& source=fromTray?tray:board;
        if(index<0 || index>=(int)source.size()) return false;
        Block moving=source[index]; moving.x=x; moving.y=y;
        int target=at(x,y);
        if(!fromTray && target==index) target=-1;
        if(target>=0) {
            Block combined;
            const Block& t=board[target];

            if(t.family!=moving.family) {lastFail="family";return false;}
            if(t.level!=moving.level) {lastFail="level";return false;}
            if(!canGrow(t.family,t.level)) {lastFail="grow";return false;}
            if(!mergedPreview(target,moving,fromTray?-1:index,combined)) {lastFail="room";return false;}
            if(combined.family<Roles) {
                combined.crew=pickCrew(combined.family,combined.level);
                if(combined.crew<0) {lastFail="crew";return false;}
            }
            lastFail="";
            mergeInputs[0]=moving;mergeInputs[1]=t;mergeResult=combined;
            board[target]=combined;
            source.erase(source.begin()+index);

            //연출이 걸릴 자리를 남긴다(그리는 쪽이 읽는다).
            mergeX=combined.x;mergeY=combined.y;
            mergeW=Wide(combined);mergeH=Tall(combined);
            mergeLevel=combined.level;++mergeSeq;
        } else {
            if(!fits(moving,fromTray?-1:index)) return false;
            if(fromTray) { board.push_back(moving); tray.erase(tray.begin()+index); }
            else board[index]=moving;
        }
        return true;
    }
    bool autoPlace(int index) {
        if(index<0 || index>=(int)tray.size()) return false;
        // Reel rewards are separate pieces. Only a deliberate drag may merge.
        for(int y=0;y<shape.height;++y) for(int x=0;x<shape.width;++x)
            if(at(x,y)<0 && place(true,index,x,y)) return true;
        return false;
    }
    bool drop(bool fromTray,int index,float centerX,float centerY){
        const auto& source=fromTray?tray:board;
        if(index<0||index>=(int)source.size())return false;
        // The dragged sprite is centered on the pointer. Resolve its visible
        // overlap before attempting an empty-cell move, including edge drops.
        const Block& m=source[index];const float mw=(float)Wide(m),mh=(float)Tall(m);
        int target=-1;float best=.20f;
        for(int i=0;i<(int)board.size();++i){
            if((!fromTray&&i==index)||!mergeable(board[i],m))continue;
            const float w=std::max(0.f,std::min(centerX+mw/2,board[i].x+(float)Wide(board[i]))-std::max(centerX-mw/2,(float)board[i].x));
            const float h=std::max(0.f,std::min(centerY+mh/2,board[i].y+(float)Tall(board[i]))-std::max(centerY-mh/2,(float)board[i].y));
            if(w*h>best){best=w*h;target=i;}
        }
        //---- 합칠 상대를 정조준했으면 거기서 끝낸다 ----
        //
        //전에는 합치기가 실패하면 곧바로 "빈 칸에 놓기" 를 다시 시도했다.
        //그 두 번째 시도가 엉뚱한 블록 위에 떨어지면 거기서 또 실패하는데,
        //실패 이유가 그쪽 것으로 덮어써진다 - 자리가 없어서 못 합친 것을
        //"다른 종류끼리는 못 합칩니다" 로 읽게 된다.
        //
        //위에서 고른 target 은 이미 "합쳐지는 상대" 다(mergeable 로 걸렀다).
        //거기를 겨눴는데 안 되면 그 까닭을 그대로 돌려준다. 몰래 다른 칸에
        //옮겨 놓지도 않는다 - 합치려고 끈 것이 엉뚱한 데 가 있으면 더
        //헷갈린다.
        if(target>=0) return place(fromTray,index,board[target].x,board[target].y);

        const int wantX=(int)std::floor(centerX-(mw-1)/2),wantY=(int)std::floor(centerY-(mh-1)/2);
        if(place(fromTray,index,wantX,wantY)) return true;

        //---- 릴에서 꺼낸 것만 가까운 빈 자리로 ----
        //
        //릴에서 막 나온 조각은 돌아갈 자리가 없다. 손이 조금 빗나갔다고
        //트레이에 도로 얹으면 매번 다시 끌어야 한다 - 가장 가까운 빈 칸에
        //넣어 준다.
        //
        //판에 이미 놓인 블록은 다르다. 합치려다 안 되면 **있던 자리로
        //돌아가야** 한다. 엉뚱한 칸으로 옮겨 놓으면 판이 제멋대로 흐트러지고,
        //무엇을 집었다 놓았는지가 안 읽힌다.
        //(place 가 실패하면 아무것도 안 바꾸므로, false 를 돌려주는 것이
        // 곧 제자리로 돌아가는 것이다.)
        if(!fromTray) {lastFail="spot";return false;}
        {
            const Block& b=source[index];
            int bestX=-1,bestY=-1,bestScore=0;

            for(int y=0;y<shape.height;++y) for(int x=0;x<shape.width;++x) {
                Block cand=b;cand.x=x;cand.y=y;
                if(!fits(cand,fromTray?-1:index)) continue;

                const int dx=x-wantX,dy=y-wantY,score=dx*dx+dy*dy;

                if(bestX<0||score<bestScore) {bestScore=score;bestX=x;bestY=y;}
            }

            if(bestX>=0) return place(fromTray,index,bestX,bestY);
        }

        lastFail="full";
        return false;
    }
    void choose(const std::vector<int>& pool,const int* weights=nullptr) {
        drafted=true;
        families[0]=selected;
        std::vector<int> remaining;
        for(int f:pool) if(f!=selected && std::find(remaining.begin(),remaining.end(),f)==remaining.end()) remaining.push_back(f);
        for(int i=1;i<3;++i) {
            if(remaining.empty()) { families[i]=i==1?Armor:Boots; continue; }
            unsigned total=0;for(int f:remaining)total+=weights?(unsigned)std::max(0,weights[f]):1;
            unsigned pick=random(total);int j=0;
            if(total)for(;j+1<(int)remaining.size();++j) {
                unsigned weight=weights?(unsigned)std::max(0,weights[remaining[j]]):1;
                if(pick<weight)break;pick-=weight;
            }
            families[i]=remaining[j];remaining.erase(remaining.begin()+j);
        }
    }
    Block starter(int family) {
        Block b;b.family=family;b.level=1;b.crew=pickCrew(family,1);return b;
    }
    // Free opening draw: three distinct random lineages, one Lv1 of each.
    // Commit as one state so reloading during the presentation cannot duplicate it.
    bool start(const std::vector<int>& pool,const int* weights=nullptr,bool fixedFirst=false,bool keepDraft=false) {
        if(!choosing || !board.empty() || !tray.empty() || attacking || lost)return false;
        std::vector<int> unique;
        for(int f:pool) {
            if(f<0 || f>=FamilyCount)return false;
            if(f<Roles&&!(roster&&roster->has(f,1)))return false;   // ★1 이 없는 역할은 시작할 수 없다
            if(std::find(unique.begin(),unique.end(),f)==unique.end())unique.push_back(f);
        }
        if(unique.size()<3||std::find(unique.begin(),unique.end(),Sword)==unique.end())return false;
        Run next=*this;
        if(fixedFirst) {if(std::find(unique.begin(),unique.end(),next.selected)==unique.end())return false;}
        else next.selected=unique[next.random((unsigned)unique.size())];
        if(!keepDraft||!next.drafted)next.choose(unique,weights);
        else for(int f:next.families)if(std::find(unique.begin(),unique.end(),f)==unique.end())return false;
        // Keep the selected first reel, but always start with an attack weapon.
        if(std::find(next.families,next.families+3,Sword)==next.families+3)next.families[2]=Sword;
        next.choosing=false;
        for(int f:next.families) next.tray.push_back(next.starter(f));
        while(!next.tray.empty())if(!next.autoPlace(0))return false;
        *this=next;return true;
    }
    int freeCells() const {
        int count=0;
        for(int y=0;y<shape.height;++y)for(int x=0;x<shape.width;++x)if(shape.contains(x,y)&&at(x,y)<0)++count;
        return count;
    }
    bool canSpin() const { return !choosing && !attacking && !lost && spins>0 && tray.empty() && freeCells()>=3; }
    bool spin() {
        if(!canSpin()) return false;
        --spins;
        //---- 장비와 동료의 비율을 먼저 정한다 ----
        //
        //전에는 릴 세 줄에서 고르게 뽑았다(random(3)). 그러면 비율이 계열
        //뽑기에 끌려다닌다 - 세 줄이 전부 동료 계열로 잡힌 판에서는 아무리
        //돌려도 장비가 안 나와 합성 트리가 통째로 멈춘다.
        //
        //한 칸마다 "장비냐 동료냐" 를 BOARD_GEAR_PCT 로 먼저 정하고, 그다음
        //그쪽 계열 중에서 고른다. 한쪽이 릴에 없으면 반대쪽으로 간다 -
        //빈손으로 돌아가는 칸은 만들지 않는다.
        //
        //---- 장비는 여섯 부위 전부 ----
        //
        //전에는 시작 슬롯이 정한 계열 셋 안에서만 뽑았다. 장비가 그중 둘이면
        //열 번을 돌려도 같은 두 가지만 나와 빤했고, 같은 것끼리 바로바로
        //합쳐지니 칸이 모자란 느낌도 없었다(2026-11-12). 이제 장비는 검·갑옷·
        //장화·투구·장갑·바지 여섯 부위에서 고르게 뽑는다. 동료는 시작 슬롯이
        //정한 역할 그대로다.
        //
        //릴 차례와 칸 수는 그대로다(쌍·삼중도 그대로 나온다).
        int gear[GearCount],gn=0,role[3],rn=0;

        for(int f=Sword;f<FamilyCount;++f) gear[gn++]=f;
        for(int k=0;k<3;++k) if(families[k]<Roles) role[rn++]=families[k];

        for(int i=0;i<3;++i) {
            const bool wantGear=(int)random(100)<BOARD_GEAR_PCT;
            int family;

            if(wantGear||!rn) family=gear[random((unsigned)gn)];
            else family=role[random((unsigned)rn)];

            tray.push_back(starter(family));
        }
        return true;
    }
    //릴 띠에 도는 계열. spin() 이 고르는 집합과 같다 - 장비 여섯 + 시작 슬롯의 역할.
    int reelFamilies(int* out) const {
        int n=0;
        for(int k=0;k<3;++k) if(families[k]<Roles) out[n++]=families[k];
        for(int f=Sword;f<FamilyCount;++f) out[n++]=f;
        return n;
    }
    Shot evaluate(const Block& b,const Stats& st,Effects& e) const {
        Shot s; s.block=b;
        int lv=b.level;
        if(b.family==Boots) return s;
        if(DefensiveGear(b.family)) {
            e.protect+=armorOf(b,st);e.skip+=MergeBoard::ArmorSkipTurns(lv);
            if(lv==2)e.half=true;
            return s;
        }
        long long raw;Trait trait=Strike;bool summon=false;
        if(b.family<Roles) {
            const CrewStats& c=st.crew[b.crew<0||b.crew>=64?0:b.crew];
            raw=c.power*MergeBoard::CrewMul(lv);trait=c.trait;summon=c.summon;
            if(trait==Chill) {e.skip+=MergeBoard::ChillSkipTurns(lv);if(lv<=2)e.half=true;}
            if(trait==Strike)raw+=raw*MergeBoard::StrikePct(lv)/100;
        } else raw=st.weapon*MergeBoard::GearMulOf(b.family-Sword,lv);   // 칸이 느는 단만 ×3, 그대로인 단은 ×2
        s.damage=raw*(100+e.expose)/100*e.inspire;e.inspire=1;
        if(b.family<Roles) {
            if(trait==Expose) e.expose+=MergeBoard::ExposePct(lv);
            if(trait==Inspire) e.inspire=MergeBoard::InspireMul(lv);
            if(trait==Burn) {e.dot+=s.damage*MergeBoard::BurnPct(lv)/100;e.dotTurns=std::max(e.dotTurns,MergeBoard::BurnTurns(lv));}
            if(summon && lv>=5) s.summonTurns=3;
        }
        return s;
    }
    //---- 치는 차례 ----
    //
    //판의 오른쪽이 전열이다. 적이 오른쪽에 있고 데크의 줄도 오른쪽이
    //앞이므로, 판·데크·적이 한 방향으로 읽힌다.
    //
    //차례는 연출만이 아니다. 표식(Expose)·고무(Inspire)·갑옷은 제 뒤에
    //오는 블록에만 걸리므로, "오른쪽 열에 버퍼를 세우면 뒤가 세진다" 가
    //곧 배치 전술이다. 그래서 규칙은 한 문장으로 외워져야 한다.
    //
    //같은 열은 위에서 아래로 - 한 열 안에서도 순서가 흔들리지 않는다.
    std::vector<Block> ordered() const {
        std::vector<Block> sorted=board;
        std::stable_sort(sorted.begin(),sorted.end(),[](const Block& a,const Block& b){return a.x==b.x?a.y<b.y:a.x>b.x;});
        return sorted;
    }
    //---- 지금 공격하면 생길 효과 ----
    //
    //방어(갑옷) 표시가 쓰는 값이다. 전에는 패가 maxLives-3 을 방어라고
    //보여 줬는데, 그건 방어와 아무 상관이 없어서 늘 0 이었다.
    //
    //진짜 방어는 갑옷 블록이 공격 때 내놓는 e.protect 다. 공격 전에도
    //같은 셈을 미리 돌려, 갑옷을 올리면 바로 눈금이 오르게 한다.
    Effects forecast(const Stats& st) const {
        Effects e;
        for(const Block& b:ordered()) evaluate(b,st,e);
        return e;
    }
    long long preview(const Stats& st) const {
        Effects e; long long result=dotTurns>0?dot:0;
        for(const auto& summon:summons) result+=summon.damage;
        for(const Block& b:ordered()) result+=evaluate(b,st,e).damage;
        return result;
    }
    bool attack(const Stats& st) {
        if(choosing || attacking || lost || board.empty()) return false;
        shots.clear(); nextShot=0; effects=Effects(); damageDone=0;counterResolved=false;
        // Persistent damage ticks on attack exchanges, never while arranging/spinning.
        if(dotTurns>0) { enemyHp=std::max(0LL,enemyHp-dot); --dotTurns; }
        for(auto& s:summons) { enemyHp=std::max(0LL,enemyHp-s.damage); --s.summonTurns; }
        summons.erase(std::remove_if(summons.begin(),summons.end(),[](const Shot& s){return s.summonTurns<=0;}),summons.end());
        for(const Block& b:ordered()) shots.push_back(evaluate(b,st,effects));
        attacking=true; return true;
    }
    // One block at a time, in board order, so the adapter can animate every shot.
    bool step() {
        if(!attacking || nextShot>=(int)shots.size()) return false;
        Shot s=shots[nextShot++];
        damageDone+=s.damage; enemyHp=std::max(0LL,enemyHp-s.damage);
        if(s.summonTurns>0) summons.push_back(s);
        return true;
    }
    bool shouldCounterattack() const {
        return attacking&&nextShot==(int)shots.size()&&enemyHp>0&&!counterResolved&&skipTurns+effects.skip<=0;
    }
    long long counterDamage() const {
        if(enemyHp<=0||skipTurns+effects.skip>0)return 0;
        long long hit=enemyAttack*(BossTier(wave)?2:1);
        if(effects.half)hit=(hit+1)/2;
        return std::max(0LL,hit-baseArmor-effects.protect);
    }
    bool counterattack() {
        if(!shouldCounterattack())return false;
        lives=std::max(0LL,lives-counterDamage());counterResolved=true;
        return true;
    }
    int finish() {
        if(!attacking || nextShot<(int)shots.size()) return 0;
        // Resolve equipment effects only once, after the presentation completes.
        int hearts=0, extraSpins=0;
        for(const Shot& s:shots) if(s.block.family==Boots) {
            hearts+=MergeBoard::NeckHearts(s.block.level);extraSpins+=MergeBoard::NeckSpins(s.block.level);
        }
        if(effects.dot>0) {dot=effects.dot;dotTurns=std::max(dotTurns,effects.dotTurns);}
        skipTurns=std::min(100,skipTurns+effects.skip);
        if(enemyHp>0) {
            if(skipTurns>0) --skipTurns;
            else if(!counterResolved)lives=std::max(0LL,lives-counterDamage());
        } else {
            reward+=10LL*(stage+1)*(BossTier(wave)?10:1);
            if(++wave==WavesPerStage) {wave=0;++stage;lives=maxLives;}
            dot=0;dotTurns=skipTurns=0;summons.clear();
        }
        shots.clear();attacking=false;nextShot=0;counterResolved=false;
        spins=std::min(100,SpinLimit+extraSpins); lost=lives==0;
        return hearts;
    }
    // Versioned sidecar; validation is performed before any state is installed.
    // v6: 계열 = 역할 4 + 장비 3, 블록마다 동료 번호. 그 전 판은 읽지 않는다(새 런).
    std::string encode() const {
        std::ostringstream o;
        o<<"MR3 "<<SaveVersion<<' '<<rng<<' '<<selected<<' '<<spins<<' '<<lives<<' '<<maxLives<<' '
         <<wave<<' '<<stage<<' '<<enemyHp<<' '<<enemyMax<<' '<<dot<<' '<<dotTurns<<' '
         <<skipTurns<<' '<<choosing<<' '<<lost<<' '<<drafted;
        for(int f:families) o<<' '<<f;
        o<<' '<<shape.width<<' '<<shape.height;for(unsigned row:shape.rows)o<<' '<<row;
        for(const auto* list:{&board,&tray}) {
            o<<' '<<list->size(); for(const auto& b:*list) o<<' '<<b.family<<' '<<b.level<<' '<<b.crew<<' '<<b.x<<' '<<b.y<<' '<<(b.rot?1:0);
        }
        o<<' '<<summons.size();
        for(const auto& s:summons) o<<' '<<s.block.family<<' '<<s.block.level<<' '<<s.block.crew<<' '<<s.damage<<' '<<s.summonTurns;
        o<<' '<<attacking<<' '<<nextShot<<' '<<reward<<' '<<damageDone
         <<' '<<effects.expose<<' '<<effects.inspire<<' '<<effects.skip<<' '<<effects.protect
         <<' '<<effects.half<<' '<<effects.dot<<' '<<effects.dotTurns<<' '<<shots.size();
        for(const Shot& s:shots)o<<' '<<s.block.family<<' '<<s.block.level<<' '<<s.block.crew<<' '<<s.block.x<<' '<<s.block.y<<' '<<s.damage<<' '<<s.summonTurns;
        o<<' '<<counterResolved<<' '<<realVitals<<' '<<baseArmor<<' '<<enemyAttack;
        return o.str();
    }
    static bool crewOk(const Block& b) {
        return b.family<Roles?(b.crew>=0&&b.crew<64):b.crew==-1;
    }
    bool decode(const std::string& text) {
        Run r; r.roster=roster; std::istringstream in(text); std::string magic;int version;
        // v7's accessory family (6) becomes boots, preserving the run and utility effects.
        if(!(in>>magic>>version)||magic!="MR3"||(version!=SaveVersion&&version!=9&&version!=8&&version!=7)) return false;
        if(!(in>>r.rng>>r.selected>>r.spins>>r.lives>>r.maxLives>>r.wave>>r.stage>>r.enemyHp>>r.enemyMax
             >>r.dot>>r.dotTurns>>r.skipTurns>>r.choosing>>r.lost>>r.drafted)) return false;
        if(!r.rng || r.selected<0 || r.selected>=FamilyCount || r.spins<0 || r.spins>100
           || r.maxLives<1 || r.maxLives>(version>=10?1000000000000000LL:20LL) || r.lives<0 || r.lives>r.maxLives
           || r.wave<0 || r.wave>=WavesPerStage || r.stage<0 || r.stage>100000
           || r.enemyMax<1 || r.enemyMax>1000000000000000LL || r.enemyHp<0 || r.enemyHp>r.enemyMax
           || r.dot<0 || r.dot>1000000000000000LL || r.dotTurns<0 || r.dotTurns>4 || r.skipTurns<0 || r.skipTurns>100) return false;
        for(int& f:r.families) if(!(in>>f)||f<0||f>=FamilyCount) return false;
        if(!(in>>r.shape.width>>r.shape.height))return false;
        for(unsigned& row:r.shape.rows)if(!(in>>row))return false;
        if(!r.shape.valid())return false;
        for(int list=0;list<2;++list) {
            int count;if(!(in>>count)||count<0||count>(list?3:Cells)) return false;
            for(int i=0;i<count;++i) {
                Block b;int rot=0;if(!(in>>b.family>>b.level>>b.crew>>b.x>>b.y>>rot)||b.family<0||b.family>=FamilyCount||b.level<1||b.level>MaxLevel||!crewOk(b)) return false;b.rot=rot!=0;
                //장비는 여섯 부위 어느 것이든 판에 설 수 있다. 역할 블록만 시작 슬롯의 역할이어야 한다.
                if(b.family<Roles&&std::find(r.families,r.families+3,b.family)==r.families+3) return false;
                if(!list) {if(!r.fits(b)) return false;r.board.push_back(b);}
                else {if(b.x!=-1||b.y!=-1) return false;r.tray.push_back(b);}
            }
        }
        int count;if(!(in>>count)||count<0||count>Cells*3) return false;
        for(int i=0;i<count;++i) {
            Shot s;if(!(in>>s.block.family>>s.block.level>>s.block.crew>>s.damage>>s.summonTurns)
                ||s.block.family<0||s.block.family>=Roles||s.block.level<5||s.block.level>MaxLevel||!crewOk(s.block)
                ||s.damage<0||s.damage>1000000000000000LL||s.summonTurns<1||s.summonTurns>3) return false;
            r.summons.push_back(s);
        }
        if(!(in>>r.attacking>>r.nextShot>>r.reward>>r.damageDone
             >>r.effects.expose>>r.effects.inspire>>r.effects.skip>>r.effects.protect
             >>r.effects.half>>r.effects.dot>>r.effects.dotTurns>>count))return false;
        if(count<0||count>Cells||r.nextShot<0||r.nextShot>count||r.reward<0||r.reward>1000000000000LL
           ||r.damageDone<0||r.damageDone>1000000000000000LL||r.effects.expose<0||r.effects.expose>9000
           ||r.effects.inspire<1||r.effects.inspire>5||r.effects.skip<0||r.effects.skip>200
           ||r.effects.protect<0||r.effects.protect>(version>=10?Cells*1000000000000000LL:Cells*2LL)||r.effects.dot<0||r.effects.dot>1000000000000000LL
           ||r.effects.dotTurns<0||r.effects.dotTurns>4)return false;
        auto sorted=r.ordered();
        for(int i=0;i<count;++i) {
            Shot s;if(!(in>>s.block.family>>s.block.level>>s.block.crew>>s.block.x>>s.block.y>>s.damage>>s.summonTurns)
                ||s.damage<0||s.damage>1000000000000000LL||s.summonTurns<0||s.summonTurns>3)return false;
            if(i>=(int)sorted.size())return false;
            const Block& b=sorted[i];
            if(s.block.family!=b.family||s.block.level!=b.level||s.block.crew!=b.crew||s.block.x!=b.x||s.block.y!=b.y)return false;
            r.shots.push_back(s);
        }
        if(r.attacking?(count!=(int)r.board.size()||count==0||r.choosing||r.lost):(count!=0||r.nextShot!=0))return false;
        if(version>=9&&!(in>>r.counterResolved))return false;
        if(version>=10) {
            if(!(in>>r.realVitals>>r.baseArmor>>r.enemyAttack)||r.baseArmor<0||r.baseArmor>1000000000000000LL||r.enemyAttack<1||r.enemyAttack>1000000000000000LL)return false;
            if(!r.realVitals&&(r.maxLives>20||r.baseArmor!=0||r.enemyAttack!=1))return false;
        }
        if(r.counterResolved&&(!r.attacking||r.nextShot!=count||r.enemyHp<=0))return false;
        in>>std::ws;if(!in.eof()) return false;
        if((r.lives==0)!=r.lost&&!(r.attacking&&r.counterResolved&&r.lives==0&&!r.lost)) return false;
        *this=r;return true;
    }
};
}
#pragma pack(pop)
