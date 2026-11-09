#pragma once
#pragma pack(push, 8)
// TURNRPG run state. No engine globals, persistent equipment or ACTIONRPG data.
//
// 2026-11-09: 합성은 6단 = 성급이다. 계열(family)은 역할군 4 + 장비 3.
// 같은 역할·같은 ★ 블록 둘을 합치면 그 역할의 ★+1 동료 중 하나가 무작위로
// 나온다(운빨존많겜 식). 어느 동료가 나올 수 있는지는 Roster 가 들고 있고,
// 피해·특성은 Stats 가 동료 번호로 들고 있다. 판은 공격해도 비지 않는다.
#include <algorithm>
#include <cstdint>
#include <vector>
#include <sstream>
#include <string>
#include "BoardModel.h"

namespace MergeRoulette {
enum { Width=12, Height=6, Cells=Width*Height, MaxLevel=BLOCK_LV_MAX, SpinLimit=BOARD_SPINS,
       Roles=4, Sword=4, Armor=5, Necklace=6, FamilyCount=7, RosterCell=8, SaveVersion=6 };
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
struct Block {
    int family=-1, level=1, crew=-1, x=-1, y=-1;   // crew: 역할 계열이면 동료 번호, 장비면 -1
    bool placed() const { return x>=0 && y>=0; }
};
inline int Wide(int level) { return MergeBoard::BlockW(level); }
inline int Tall(int level) { return MergeBoard::BlockH(level); }
// 동료마다 한 방의 세기와 특성. 레벨(=★)은 블록이 들고 있으므로 여기엔 없다.
struct CrewStats {
    long long power=20;
    Trait trait=Strike;
    bool summon=false;     // SKILL3 가 소환 계열이면 ★5·6 블록이 소환수를 남긴다
};
struct Stats {
    CrewStats crew[64];
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
    int expose=0, inspire=1, skip=0, protect=0;
    bool half=false;
    long long dot=0;
    int dotTurns=0;
};
struct Run {
    Shape shape;
    unsigned rng=1;
    int families[3]={Sword,Armor,Necklace};
    int selected=Sword, spins=SpinLimit, lives=5, maxLives=5;
    int wave=0, stage=0, skipTurns=0, dotTurns=0, nextShot=0;
    long long enemyHp=330, enemyMax=330, dot=0, reward=0, damageDone=0;
    bool choosing=true, attacking=false, lost=false, drafted=false;
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
           || b.x<0 || b.y<0 || b.x+Wide(b.level)>shape.width || b.y+Tall(b.level)>shape.height) return false;
        for(int y=b.y;y<b.y+Tall(b.level);++y)for(int x=b.x;x<b.x+Wide(b.level);++x)if(!shape.contains(x,y))return false;
        for(int i=0;i<(int)board.size();++i) {
            if(i==ignore||i==ignore2)continue;
            const Block& a=board[i];
            if(b.x<a.x+Wide(a.level)&&a.x<b.x+Wide(b.level)&&b.y<a.y+Tall(a.level)&&a.y<b.y+Tall(b.level))return false;
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
            if(x>=b.x && y>=b.y && x<b.x+Wide(b.level) && y<b.y+Tall(b.level)) return i;
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
        out.x=std::min(out.x,shape.width-Wide(out.level));
        out.y=std::min(out.y,shape.height-Tall(out.level));
        return fits(out,target,ignore);
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
            if(!mergedPreview(target,moving,fromTray?-1:index,combined)) return false;
            if(combined.family<Roles) {
                combined.crew=pickCrew(combined.family,combined.level);
                if(combined.crew<0) return false;
            }
            board[target]=combined;
            source.erase(source.begin()+index);
        } else {
            if(!fits(moving,fromTray?-1:index)) return false;
            if(fromTray) { board.push_back(moving); tray.erase(tray.begin()+index); }
            else board[index]=moving;
        }
        return true;
    }
    bool autoPlace(int index) {
        if(index<0 || index>=(int)tray.size()) return false;
        // Matches first, then scan for free space.
        for(int i=0;i<(int)board.size();++i)
            if(mergeable(board[i],tray[index]) && place(true,index,board[i].x,board[i].y)) return true;
        for(int y=0;y<shape.height;++y) for(int x=0;x<shape.width;++x)
            if(at(x,y)<0 && place(true,index,x,y)) return true;
        return false;
    }
    void choose(const std::vector<int>& pool,const int* weights=nullptr) {
        drafted=true;
        families[0]=selected;
        std::vector<int> remaining;
        for(int f:pool) if(f!=selected && std::find(remaining.begin(),remaining.end(),f)==remaining.end()) remaining.push_back(f);
        for(int i=1;i<3;++i) {
            if(remaining.empty()) { families[i]=i==1?Armor:Necklace; continue; }
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
        if(unique.size()<3)return false;
        Run next=*this;
        if(fixedFirst) {if(std::find(unique.begin(),unique.end(),next.selected)==unique.end())return false;}
        else next.selected=unique[next.random((unsigned)unique.size())];
        if(!keepDraft||!next.drafted)next.choose(unique,weights);
        else for(int f:next.families)if(std::find(unique.begin(),unique.end(),f)==unique.end())return false;
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
        int result[3]; for(int i=0;i<3;++i) result[i]=(int)random(3);
        int levels[3],lineages[3];MergeBoard::HandFromReels(result,levels,lineages);
        for(int i=0;i<3;++i) {
            if(levels[i]==0)continue;
            Block b;b.family=families[lineages[i]];b.level=levels[i];
            // 릴 매치로 ★2·★3 이 바로 나온다. 그 ★ 에 동료가 없으면 ★1 셋으로 깐다.
            if(b.family<Roles) {
                b.crew=pickCrew(b.family,b.level);
                if(b.crew<0) {
                    tray.clear();
                    for(int k=0;k<3;++k) {Block c;c.family=families[result[k]];c.level=1;c.crew=pickCrew(c.family,1);tray.push_back(c);}
                    return true;
                }
            }
            tray.push_back(b);
        }
        return true;
    }
    Shot evaluate(const Block& b,const Stats& st,Effects& e) const {
        Shot s; s.block=b;
        int lv=b.level;
        if(b.family==Necklace) return s;
        if(b.family==Armor) {
            e.protect+=MergeBoard::ArmorGuards(lv);e.skip+=MergeBoard::ArmorSkipTurns(lv);
            if(lv==2)e.half=true;
            return s;
        }
        long long raw;Trait trait=Strike;bool summon=false;
        if(b.family<Roles) {
            const CrewStats& c=st.crew[b.crew<0||b.crew>=64?0:b.crew];
            raw=c.power*MergeBoard::LevelMul(lv);trait=c.trait;summon=c.summon;
            if(trait==Chill) {e.skip+=MergeBoard::ChillSkipTurns(lv);if(lv<=2)e.half=true;}
            if(trait==Strike)raw+=raw*MergeBoard::StrikePct(lv)/100;
        } else raw=st.weapon*MergeBoard::LevelMul(lv);
        s.damage=raw*(100+e.expose)/100*e.inspire;e.inspire=1;
        if(b.family<Roles) {
            if(trait==Expose) e.expose+=MergeBoard::ExposePct(lv);
            if(trait==Inspire) e.inspire=MergeBoard::InspireMul(lv);
            if(trait==Burn) {e.dot+=s.damage*MergeBoard::BurnPct(lv)/100;e.dotTurns=std::max(e.dotTurns,MergeBoard::BurnTurns(lv));}
            if(summon && lv>=5) s.summonTurns=3;
        }
        return s;
    }
    std::vector<Block> ordered() const {
        std::vector<Block> sorted=board;
        std::stable_sort(sorted.begin(),sorted.end(),[](const Block& a,const Block& b){return a.y==b.y?a.x<b.x:a.y<b.y;});
        return sorted;
    }
    long long preview(const Stats& st) const {
        Effects e; long long result=dotTurns>0?dot:0;
        for(const auto& summon:summons) result+=summon.damage;
        for(const Block& b:ordered()) result+=evaluate(b,st,e).damage;
        return result;
    }
    bool attack(const Stats& st) {
        if(choosing || attacking || lost || board.empty()) return false;
        shots.clear(); nextShot=0; effects=Effects(); damageDone=0;
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
    int finish() {
        if(!attacking || nextShot<(int)shots.size()) return 0;
        // Resolve equipment effects only once, after the presentation completes.
        int hearts=0, extraSpins=0;
        for(const Shot& s:shots) if(s.block.family==Necklace) {
            hearts+=MergeBoard::NeckHearts(s.block.level);extraSpins+=MergeBoard::NeckSpins(s.block.level);
        }
        if(effects.dot>0) {dot=effects.dot;dotTurns=std::max(dotTurns,effects.dotTurns);}
        skipTurns=std::min(100,skipTurns+effects.skip);
        if(enemyHp>0) {
            if(skipTurns>0) --skipTurns;
            else {
                int hit=(wave+1)%10==0?2:1;
                if(effects.half) hit=(hit+1)/2;
                hit=std::max(0,hit-effects.protect);
                lives=std::max(0,lives-hit);
            }
        } else {
            reward+=10LL*(stage+1)*((wave+1)%10==0?10:1);
            if(++wave==10) {wave=0;++stage;lives=maxLives;}
            dot=0;dotTurns=skipTurns=0;summons.clear();
        }
        shots.clear();attacking=false;nextShot=0;
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
            o<<' '<<list->size(); for(const auto& b:*list) o<<' '<<b.family<<' '<<b.level<<' '<<b.crew<<' '<<b.x<<' '<<b.y;
        }
        o<<' '<<summons.size();
        for(const auto& s:summons) o<<' '<<s.block.family<<' '<<s.block.level<<' '<<s.block.crew<<' '<<s.damage<<' '<<s.summonTurns;
        o<<' '<<attacking<<' '<<nextShot<<' '<<reward<<' '<<damageDone
         <<' '<<effects.expose<<' '<<effects.inspire<<' '<<effects.skip<<' '<<effects.protect
         <<' '<<effects.half<<' '<<effects.dot<<' '<<effects.dotTurns<<' '<<shots.size();
        for(const Shot& s:shots)o<<' '<<s.block.family<<' '<<s.block.level<<' '<<s.block.crew<<' '<<s.block.x<<' '<<s.block.y<<' '<<s.damage<<' '<<s.summonTurns;
        return o.str();
    }
    static bool crewOk(const Block& b) {
        return b.family<Roles?(b.crew>=0&&b.crew<64):b.crew==-1;
    }
    bool decode(const std::string& text) {
        Run r; r.roster=roster; std::istringstream in(text); std::string magic;int version;
        if(!(in>>magic>>version)||magic!="MR3"||version!=SaveVersion) return false;
        if(!(in>>r.rng>>r.selected>>r.spins>>r.lives>>r.maxLives>>r.wave>>r.stage>>r.enemyHp>>r.enemyMax
             >>r.dot>>r.dotTurns>>r.skipTurns>>r.choosing>>r.lost>>r.drafted)) return false;
        if(!r.rng || r.selected<0 || r.selected>=FamilyCount || r.spins<0 || r.spins>100
           || r.maxLives<1 || r.maxLives>20 || r.lives<0 || r.lives>r.maxLives
           || r.wave<0 || r.wave>=10 || r.stage<0 || r.stage>100000
           || r.enemyMax<1 || r.enemyMax>1000000000000000LL || r.enemyHp<0 || r.enemyHp>r.enemyMax
           || r.dot<0 || r.dot>1000000000000000LL || r.dotTurns<0 || r.dotTurns>4 || r.skipTurns<0 || r.skipTurns>100) return false;
        for(int& f:r.families) if(!(in>>f)||f<0||f>=FamilyCount) return false;
        if(!(in>>r.shape.width>>r.shape.height))return false;
        for(unsigned& row:r.shape.rows)if(!(in>>row))return false;
        if(!r.shape.valid())return false;
        for(int list=0;list<2;++list) {
            int count;if(!(in>>count)||count<0||count>(list?3:Cells)) return false;
            for(int i=0;i<count;++i) {
                Block b;if(!(in>>b.family>>b.level>>b.crew>>b.x>>b.y)||b.family<0||b.family>=FamilyCount||b.level<1||b.level>MaxLevel||!crewOk(b)) return false;
                if(std::find(r.families,r.families+3,b.family)==r.families+3) return false;
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
           ||r.effects.protect<0||r.effects.protect>Cells*2||r.effects.dot<0||r.effects.dot>1000000000000000LL
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
        in>>std::ws;if(!in.eof()) return false;
        if((r.lives==0)!=r.lost) return false;
        *this=r;return true;
    }
};
}
#pragma pack(pop)
