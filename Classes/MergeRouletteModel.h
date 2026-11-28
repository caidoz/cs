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
#include "MonsterPartsModel.h"

namespace MergeRoulette {
enum { Width=12, Height=6, Cells=Width*Height, MaxLevel=BLOCK_LV_MAX, SpinLimit=BOARD_SPINS,
       Roles=4, Sword=4, Armor=5, Boots=6, Helm=7, Gloves=8, Pants=9, FamilyCount=10, GearCount=6, WavesPerStage=15, RosterCell=8, SaveVersion=16 };
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
// Four fixed rows: start at4x4 and add one cell per castle upgrade, capped at9x4.
inline Shape BattleShape(int stage) {
    Shape out;for(auto& row:out.rows)row=0;
    const int extra=std::max(0,std::min(20,stage));
    out.width=4+(extra+3)/4;out.height=4;
    for(int y=0;y<4;++y)out.rows[y]=15;
    for(int i=0;i<extra;++i)out.rows[3-i%4]|=1u<<(4+i/4);
    return out;
}
struct Block {
    int family=-1, level=1, crew=-1, x=-1, y=-1;   // crew: 역할 계열이면 동료 번호, 장비면 -1
    //눕혔는가. 장비는 ★5 가 5x1 이라 세로로 눕혀야 들어가는 자리가 많다.
    //동료는 1x1 이라 눕히나 마나 같다.
    bool rot=false;
    long long ownedId=0,ownedPower=0;
    int ownedDetail=-1,ownedGrade=0,ownedW=0,ownedH=0;
    bool placed() const { return x>=0 && y>=0; }
};
// 동료 블록은 ★ 에 상관없이 1×2. 장비 블록의 칸 모양은 그림이 정한다 -
// configure() 가 GridGearPart 로 재서 MergeBoard::SetGearShape 에 넣는다(계열
// 줄 = family-Sword). 그래서 무기만 크고 투구·갑옷·목걸이는 1×1 에 머문다.
inline int Wide(int family,int level) { return family<Roles?MergeBoard::BlockWOf(LINEAGE_CREW,level):MergeBoard::GearW(family-Sword,level); }
inline int Tall(int family,int level) { return family<Roles?MergeBoard::BlockHOf(LINEAGE_CREW,level):MergeBoard::GearH(family-Sword,level); }
//눕힌 블록은 가로세로가 바뀐다. 크기를 묻는 곳이 전부 이 둘을 거치므로
//여기 두 줄이면 판정·그리기·저장이 같이 따라온다.
inline int Wide(const Block& b) { const int w=b.ownedId?b.ownedW:Wide(b.family,b.level),h=b.ownedId?b.ownedH:Tall(b.family,b.level);return b.rot?h:w; }
inline int Tall(const Block& b) { const int w=b.ownedId?b.ownedW:Wide(b.family,b.level),h=b.ownedId?b.ownedH:Tall(b.family,b.level);return b.rot?w:h; }
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
    long long protect=0;   //이번 턴 판 위 방어구 블록 값의 합(표시·옛 목숨 모드용)
    long long charge=0;    //그 방어구들이 한 턴에 방어막을 채우는 양(= 블록 값 그대로)
    bool half=false;
    long long dot=0;
    int dotTurns=0;
};
struct Run {
    Shape shape;
    unsigned rng=1;
    int families[3]={Sword,Armor,Boots};
    int selected=Sword, spins=SpinLimit;
    enum { BattleEnergyMax=5 };
    //히어로 검 블록의 기준값 = 공격력 × 300% (2026-11-22). 동료 STR 이 ★1 15 → ★6 1500 으로 벌어지는데 검은
    //공격력 27 × 3^(Lv-1) 이라 ★3 동료 한 장에 밀렸다. 300% 면 ★1·2 동료는 검 Lv1 아래, ★3 이 검 Lv1 과
    //비슷, ★4 가 검 Lv2 급 - "히어로가 제일 세고 동료가 다음" 이 ★4 까지 유지된다. ★5·6 은 히어로 궁극기
    //값(공격력×400%)을 쓰므로 무기 강화가 그대로 따라온다. 대포(cannonShell)는 따로 포탑 계수를 쓴다.
    enum { HeroGearPct=300 };
    int battleEnergy=BattleEnergyMax;
    bool spendBattleEnergy(){if(battleEnergy<=0)return false;--battleEnergy;return true;}
    void refillBattleEnergy(){battleEnergy=BattleEnergyMax;}
    // Settle the last action first: a kill or equipment can still refill supply.
    bool finishSupplies(){if(attacking||battleEnergy>0||lost)return false;lost=true;return true;}
    long long lives=5, maxLives=5;
    bool realVitals=false;
    long long baseArmor=0,enemyAttack=1;
    //상대의 방어막. 공성전에서 맞는 쪽(성주 또는 나)의 갑옷 블록 몫이다. 피해가
    //여기부터 깎이고, 바닥나면 체력으로 간다. 일반 웨이브의 몬스터는 0 이라 그대로.
    //세이브에는 넣지 않는다 - 공성전 상태는 어차피 세션 안에서만 산다.
    long long enemyGuard=0,enemyGuardMax=0;
    //---- 내 방어막 통 ----
    //
    //(2026-11-17 개편) 방어막은 피해 숫자를 그대로 받는 통이다. 적이 50 을 치면 통이 50 줄고,
    //통이 바닥나면 남은 피해가 체력으로 간다. 통의 최대치는 히어로 몫 하나다:
    //  guardMax = 최대 체력 × ShieldPct% (100% - 방어막은 체력과 같은 크기. 체력 60 이면 방어막 60).
    //장비는 통을 키우지 않고 **채운다**. 턴이 돌 때마다
    //  회복 = 실제로 낀 투구·갑옷·하체·발의 장비 값(baseArmor) + 판 위 갑옷·투구·하체 블록 값(Effects::charge)
    //만큼 다시 찬다. 장비가 없으면 회복도 없다(최소 1 같은 보정은 두지 않는다). 좋은 장비 = 턴마다
    //많이 차는 통. ★1 갑옷 블록(23)은 1성 1웨이브 반격(12)을 영구히 지우고, 14웨이브(42)에서는 턴당
    //19 씩만 새게 해 통 60 이 세 턴을 버틴다. 최종 보스(84)는 통을 비우고 체력 24 를 깎는다. 스테이지를
    //넘기면 다 찬다. 방어가 체력보다 커지지 않는다 - 둘이 같은 크기여야 "체력 두 통" 으로 읽힌다.
    static const int ShieldPct=100;
    static long long shieldFor(long long hp) {return std::max(0LL,std::min(2000000000000000LL,hp*ShieldPct/100));}
    long long guard=0,guardMax=0;
    void setVitals(long long hp,long long armor) {
        hp=std::max(1LL,std::min(1000000000000000LL,hp));
        const long double ratio=lives/(long double)std::max(1LL,maxLives);
        lives=lives>0?std::max(1LL,(long long)std::llround(hp*ratio)):0;
        //통은 체력에 비례한다. 체력이 바뀌면(장비·레벨) 남은 비율을 지켜 다시 잰다. 처음 들어오면 가득.
        const long double guardRatio=guardMax>0?guard/(long double)guardMax:1.0L;
        maxLives=hp;baseArmor=std::max(0LL,std::min(1000000000000000LL,armor));realVitals=true;
        guardMax=shieldFor(hp);
        guard=std::max(0LL,std::min(guardMax,(long long)std::llround(guardMax*guardRatio)));
    }
    //통의 최대치는 히어로 몫뿐이다. 방어구 블록은 최대치를 바꾸지 않는다 - 공격·대포·턴 넘기기가 모은 뒤
    //불러 범위만 지킨다(옛 판에서는 여기서 블록 값을 최대치에 더했다).
    void settleGuard() {
        if(!realVitals)return;
        guardMax=shieldFor(maxLives);guard=std::max(0LL,std::min(guard,guardMax));
    }
    //턴이 돌 때 장비가 채운다: 낀 방어구 값 + 판 위 방어구 블록 값. 장비가 없으면 0.
    long long guardRecovery() const {return std::max(0LL,std::min(1000000000000000LL,baseArmor+effects.charge));}
    void chargeGuard() {
        if(!realVitals||guardMax<=0||guard>=guardMax)return;
        guard=std::min(guardMax,guard+guardRecovery());
    }
    long long armorOf(const Block& block,const Stats& st) const {
        if(!DefensiveGear(block.family))return 0;
        const long long normal=st.realVitals?st.armor[block.family-Sword][std::max(0,std::min(MaxLevel-1,block.level-1))]:MergeBoard::ArmorGuards(block.level);
        return block.ownedId?std::max(normal,block.ownedPower*MergeBoard::GearMulOf(block.family-Sword,block.level)):normal;
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
    int monsterNpc=-1,monsterActionTurn=0,monsterStage=-1,monsterWave=-1;
    void configureMonster(int npc) {
        if(!MonsterParts::enemy(npc))npc=-1;
        if(monsterNpc!=npc||monsterStage!=stage||monsterWave!=wave)monsterActionTurn=0;
        monsterNpc=npc;monsterStage=stage;monsterWave=wave;
    }
    MonsterParts::Loadout monsterLoadout() const {return MonsterParts::loadout(monsterNpc,wave);}
    const MonsterParts::ActionDef& monsterAction() const {return MonsterParts::action(monsterNpc,0);}
    long long monsterHealing() const {return MonsterParts::healing(enemyHp,enemyMax,monsterLoadout(),monsterActionTurn);}
    long long monsterWeaponDamage(int weapon) const {
        const auto l=monsterLoadout();const long long base=enemyAttack*(BossTier(wave)?2:1);
        const long long value=MonsterParts::weaponDamage(base,l,weapon);
        if(!effects.half)return value;
        long long rounded=0;for(int i=0;i<l.weaponCount;++i)rounded+=MonsterParts::weaponDamage(base,l,i)/2;
        return value/2+(weapon==0?(MonsterParts::attackDamage(base,l)+1)/2-rounded:0);
    }
    long long monsterAbsorption() const {
        if(monsterNpc<0)return std::min(guard,counterHit());
        const auto l=monsterLoadout();long long available=guard,total=0;
        for(int i=0;i<l.weaponCount;++i){const long long hit=monsterWeaponDamage(i);
            const long long amount=std::min(available,hit-hit*MonsterParts::piercePct(l,MonsterParts::action(monsterNpc,i))/100);
            available-=amount;total+=amount;
        }return total;
    }
    bool choosing=true, attacking=false, lost=false, drafted=false, counterResolved=false;
    //공격 없이 턴만 넘기는 중(돌리기). 적의 반격만 받고 finish 가 가볍게 끝낸다. 세이브에는 안 넣는다.
    bool passing=false;
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
    //판 안에 들어가고(allowOverlap 이면 여기까지) 다른 블록과 겹치지 않는가.
    //
    //겹쳐 놓는 것은 허용한다 - 출정 준비의 가방과 같다. 자리를 만들려고 잠깐 포개 두고
    //돌리고 옮기는 것이 배치다. 다만 겹친 채로는(boardResolved 가 거짓) 돌리기(canSpin)가 안 되고,
    //화면은 공격·대포 단추도 막는다(Func_MergeRoulette). 저장도 겹친 채로 된다 - 이어서 풀면 된다.
    bool fits(const Block& b,int ignore=-1,int ignore2=-1,bool allowOverlap=false) const {
        if(b.family<0 || b.family>=FamilyCount || b.level<1 || b.level>MaxLevel
           || b.x<0 || b.y<0 || b.x+Wide(b)>shape.width || b.y+Tall(b)>shape.height) return false;
        for(int y=b.y;y<b.y+Tall(b);++y)for(int x=b.x;x<b.x+Wide(b);++x)if(!shape.contains(x,y))return false;
        if(allowOverlap)return true;
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
        bool same=wanted.width==shape.width&&wanted.height==shape.height;
        for(int y=0;y<Height;++y)same=same&&wanted.rows[y]==shape.rows[y];
        if(same)return true; // Intentional overlaps must survive a no-op configuration refresh.
        const bool keepOverlap=!boardResolved();
        Run next=*this;next.shape=wanted;
        //판은 가운데서 좌우로 자란다(BattleShape). 폭이 바뀌면 블록을 그 차이의
        //반만큼 옮겨야 같은 자리에 남는다. 다 들어가면 그대로 쓰고, 아니면 아래의
        //되놓기로 간다.
        const int dx=(wanted.width-shape.width)/2,dy=wanted.height-shape.height;
        if(dx!=0||dy!=0) {
            Run shifted=next;
            for(Block& b:shifted.board){b.x+=dx;b.y+=dy;}
            bool ok=true;
            for(int i=0;i<(int)shifted.board.size()&&ok;++i)if(!shifted.fits(shifted.board[i],i,-1,keepOverlap))ok=false;
            if(ok){*this=shifted;return true;}
        }
        bool fitsAll=true;
        for(int i=0;i<(int)board.size();++i)if(!next.fits(board[i],i,-1,keepOverlap))fitsAll=false;
        if(!fitsAll) {
            next.board.clear();
            for(Block b:board) {
                bool placed=false;
                for(int y=0;y<wanted.height&&!placed;++y)for(int x=0;x<wanted.width&&!placed;++x) {
                    b.x=x;b.y=y;if(next.fits(b)){next.board.push_back(b);placed=true;}
                }
                if(!placed){
                    b.rot=!b.rot;
                    for(int y=0;y<wanted.height&&!placed;++y)for(int x=0;x<wanted.width&&!placed;++x){
                        b.x=x;b.y=y;if(next.fits(b)){next.board.push_back(b);placed=true;}
                    }
                }
                if(!placed){
                    // A full legacy 4x5 board can always transpose into 5x4,
                    // including saved overlaps and multi-cell item identities.
                    Run turned=*this;turned.shape=wanted;
                    for(Block& item:turned.board){std::swap(item.x,item.y);item.rot=!item.rot;}
                    bool valid=true;
                    for(int i=0;i<(int)turned.board.size();++i)valid=valid&&turned.fits(turned.board[i],i,-1,keepOverlap);
                    if(valid){*this=turned;return true;}
                    return false; // Keep the original state intact if no lossless arrangement fits.
                }
            }
        }
        *this=next;return true;
    }
    //그 칸의 블록. 겹쳐 있으면 맨 위(뒤 번호)를 준다 - 보이는 것이 집히고, 보이는 것 위에 합쳐진다.
    // Shrinking old six-row saves keeps every excess item in the existing result
    // queue. The three visible slots advance as items are placed or discarded.
    bool setBattleShape(int castleStage) {
        const Shape wanted=BattleShape(castleStage);
        if(setShape(wanted))return true;
        if(attacking)return false;
        Run next=*this;next.shape=wanted;next.board.clear();
        auto items=board;
        std::stable_sort(items.begin(),items.end(),[](const Block& a,const Block& b){return Wide(a)*Tall(a)>Wide(b)*Tall(b);});
        for(Block b:items){
            bool placed=false;
            if(next.fits(b)){next.board.push_back(b);continue;}
            for(int turn=0;turn<2&&!placed;++turn){
                for(int y=0;y<wanted.height&&!placed;++y)for(int x=0;x<wanted.width&&!placed;++x){
                    b.x=x;b.y=y;if(next.fits(b)){next.board.push_back(b);placed=true;}
                }
                if(!placed)b.rot=!b.rot;
            }
            if(!placed){b.x=b.y=-1;next.tray.push_back(b);}
        }
        if(next.tray.size()>Cells+3)return false;
        *this=next;return true;
    }
    int at(int x,int y) const {
        for(int i=(int)board.size()-1;i>=0;--i) {
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
        out=t;
        if(moving.ownedId&&moving.ownedPower>out.ownedPower){out=moving;out.x=t.x;out.y=t.y;out.rot=t.rot;}
        ++out.level;
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
    //놓는다. 같은 종류·같은 단계 위에 놓으면 합치고, 못 합치는 자리면 겹쳐서라도 놓는다
    //(allowOverlap). 자동 배치(autoPlace)만 빈 자리에만 놓는다.
    bool place(bool fromTray,int index,int x,int y,bool allowOverlap=true) {
        if(choosing || attacking || lost) return false;
        std::vector<Block>& source=fromTray?tray:board;
        if(index<0 || index>=(int)source.size()) return false;
        Block moving=source[index]; moving.x=x; moving.y=y;
        int target=at(x,y);
        if(!fromTray && target==index) target=-1;
        if(target>=0) {
            Block combined;
            const Block& t=board[target];
            bool merged=false;
            if(t.family!=moving.family) lastFail="family";
            else if(t.level!=moving.level) lastFail="level";
            else if(!canGrow(t.family,t.level)) lastFail="grow";
            else if(!mergedPreview(target,moving,fromTray?-1:index,combined)) lastFail="room";
            else if(combined.family<Roles&&(combined.crew=pickCrew(combined.family,combined.level))<0) lastFail="crew";
            else merged=true;
            if(merged) {
                lastFail="";
                mergeInputs[0]=moving;mergeInputs[1]=t;mergeResult=combined;
                board[target]=combined;
                source.erase(source.begin()+index);

                //연출이 걸릴 자리를 남긴다(그리는 쪽이 읽는다).
                mergeX=combined.x;mergeY=combined.y;
                mergeW=Wide(combined);mergeH=Tall(combined);
                mergeLevel=combined.level;++mergeSeq;
                return true;
            }
            if(!allowOverlap) return false;
            //못 합치면 겹쳐 놓는다 - 까닭은 남겨 두되(lastFail) 놓는 것은 된다.
        }
        if(!fits(moving,fromTray?-1:index,-1,allowOverlap)) {lastFail="spot";return false;}
        if(target<0)lastFail="";
        //방금 놓은 것이 맨 위다 - 판은 번호 순서로 그려지므로 맨 뒤로 보낸다(겹쳤을 때 보이는 쪽).
        if(fromTray) { board.push_back(moving); tray.erase(tray.begin()+index); }
        else { board.erase(board.begin()+index); board.push_back(moving); }
        return true;
    }
    // Plan one merge without changing the live board or its random stream.
    bool automaticMergePlan(Run& out,bool& fromTray,int& source,int& target) const {
        if(choosing||attacking||lost)return false;
        for(int trayPass=0;trayPass<2;++trayPass){
            const auto& items=trayPass?tray:board;
            for(int i=0;i<(int)items.size()&&(!trayPass||i<3);++i)for(int j=0;j<(int)board.size();++j){
                if(!trayPass&&i<=j)continue;
                if(!mergeable(items[i],board[j]))continue;
                Run trial=*this;
                if(!trial.place(trayPass!=0,i,board[j].x,board[j].y,false))continue;
                out=trial;fromTray=trayPass!=0;source=i;target=j;return true;
            }
        }
        return false;
    }
    //톡 치면 돌린다(가로·세로 바꿈). 판 밖으로 나가면 안쪽으로 당겨 넣고, 겹치는 것은 둔다.
    bool rotate(int index) {
        if(choosing || attacking || lost || index<0 || index>=(int)board.size()) return false;
        Block b=board[index];
        if(Wide(b)==Tall(b)) return false;
        b.rot=!b.rot;
        b.x=std::min(b.x,shape.width-Wide(b));b.y=std::min(b.y,shape.height-Tall(b));
        if(b.x<0||b.y<0) return false;
        //모양(사다리꼴)에 안 들어가면 가까운 자리를 찾는다. 겹침은 허용.
        if(!fits(b,index,-1,true)) {
            int bestX=-1,bestY=-1,bestScore=0;
            for(int y=0;y<shape.height;++y)for(int x=0;x<shape.width;++x) {
                Block cand=b;cand.x=x;cand.y=y;
                if(!fits(cand,index,-1,true))continue;
                const int dx=x-b.x,dy=y-b.y,score=dx*dx+dy*dy;
                if(bestX<0||score<bestScore){bestScore=score;bestX=x;bestY=y;}
            }
            if(bestX<0) return false;
            b.x=bestX;b.y=bestY;
        }
        board.erase(board.begin()+index);board.push_back(b);return true;   //돌린 것도 맨 위로
    }
    bool autoPlace(int index) {
        if(index<0 || index>=(int)tray.size()) return false;
        // Reel rewards are separate pieces. Only a deliberate drag may merge.
        for(int y=0;y<shape.height;++y) for(int x=0;x<shape.width;++x)
            if(at(x,y)<0 && place(true,index,x,y,false)) return true;
        return false;
    }
    // Spin rewards still land on a crowded board; the player resolves overlaps.
    bool scatterPlace(int index) {
        if(autoPlace(index))return true;
        if(choosing||attacking||lost||index<0||index>=(int)tray.size())return false;
        Block best;int bestScore=-1;
        for(int turn=0;turn<2;++turn)for(int y=0;y<shape.height;++y)for(int x=0;x<shape.width;++x){
            Block b=tray[index];b.x=x;b.y=y;if(turn)b.rot=!b.rot;
            if(!fits(b,-1,-1,true))continue;
            int score=0;
            for(const Block& old:board){
                const int w=std::max(0,std::min(b.x+Wide(b),old.x+Wide(old))-std::max(b.x,old.x));
                const int h=std::max(0,std::min(b.y+Tall(b),old.y+Tall(old))-std::max(b.y,old.y));
                score+=w*h;
            }
            if(bestScore<0||score<bestScore){best=b;bestScore=score;}
        }
        if(bestScore<0)return false;
        board.push_back(best);tray.erase(tray.begin()+index);return true;
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
    //시작 계열 셋을 고른다. 역할(동료)부터 채우고, 남는 자리에 검, 그다음 장비.
    //
    //전에는 역할과 장비를 한 주머니에서 뽑았는데 장비 가중치가 4 라 세 자리가 전부 장비로
    //잡히는 판이 절반이 넘었다 - 릴을 아무리 돌려도 동료가 안 나왔다(spin 은 families 의
    //역할에서만 동료를 뽑는다). 장비는 어차피 여섯 부위 전부에서 나오므로(spin) 시작 계열이
    //정할 것은 "어느 역할의 동료가 나오는가" 뿐이다. 그래서 역할 둘 + 검이 기본이다.
    void choose(const std::vector<int>& pool,const int* weights=nullptr) {
        drafted=true;
        families[0]=selected;
        std::vector<int> roles,gears;
        for(int f:pool) if(f!=selected) {
            std::vector<int>& bag=f<Roles?roles:gears;
            if(std::find(bag.begin(),bag.end(),f)==bag.end()) bag.push_back(f);
        }
        const auto draw=[&](std::vector<int>& bag)->int{
            unsigned total=0;for(int f:bag)total+=weights?(unsigned)std::max(0,weights[f]):1;
            unsigned pick=random(total);int j=0;
            if(total)for(;j+1<(int)bag.size();++j) {
                unsigned weight=weights?(unsigned)std::max(0,weights[bag[j]]):1;
                if(pick<weight)break;pick-=weight;
            }
            const int f=bag[j];bag.erase(bag.begin()+j);return f;
        };
        for(int i=1;i<3;++i) {
            const auto sword=std::find(gears.begin(),gears.end(),(int)Sword);
            if(!roles.empty()) families[i]=draw(roles);
            else if(sword!=gears.end()) {families[i]=Sword;gears.erase(sword);}
            else if(!gears.empty()) families[i]=draw(gears);
            else families[i]=i==1?Armor:Boots;
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
        else {
            //첫 릴도 역할부터 - 시작 계열은 동료의 역할을 정하는 자리다(choose 참고).
            std::vector<int> firsts;for(int f:unique)if(f<Roles)firsts.push_back(f);
            if(firsts.empty())firsts=unique;
            next.selected=firsts[next.random((unsigned)firsts.size())];
        }
        if(!keepDraft||!next.drafted)next.choose(unique,weights);
        else for(int f:next.families)if(std::find(unique.begin(),unique.end(),f)==unique.end())return false;
        // Keep the selected first reel, but always start with an attack weapon.
        // 검이 없으면 역할이 아닌 자리(장비)를 먼저 내주고, 그런 자리가 없으면 셋째 자리다.
        if(std::find(next.families,next.families+3,Sword)==next.families+3) {
            int slot=2;for(int i=1;i<3;++i)if(next.families[i]>=Roles){slot=i;break;}
            next.families[slot]=Sword;
        }
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
    bool boardResolved() const {
        for(int i=0;i<(int)board.size();++i)if(!fits(board[i],i))return false;
        return true;
    }
    bool discard(bool fromTray,int index){
        if(choosing||attacking||lost)return false;
        auto& source=fromTray?tray:board;
        if(index<0||index>=(int)source.size())return false;
        source.erase(source.begin()+index);return true;
    }
    bool canSpin() const { return !choosing && !attacking && !lost && spins>0 && tray.empty() && boardResolved(); }
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

        //---- 세 칸에 장비와 동료가 하나씩은 선다 ----
        //
        //칸마다 독립으로 동전을 던지면 70:30 이라도 셋 다 장비(34%)·셋 다 동료(3%) 가 흔해서
        //"장비만 몰려 나온다 / 동료만 몰려 나온다" 로 읽혔다. 동전은 그대로 던지되(난수 순서 보존),
        //셋이 한쪽으로 쏠리면 가장 애매했던 칸 하나를 반대쪽으로 돌린다 - 역할이 하나라도 있을 때만.
        if(!rn){   //역할이 없으면 전부 장비 - 옛 난수 순서(동전, 부위, 동전, 부위…)를 그대로 지킨다
            for(int i=0;i<3;++i){random(100);tray.push_back(starter(gear[random((unsigned)gn)]));}
            return true;
        }
        int coin[3];bool wantGear[3];
        for(int i=0;i<3;++i){coin[i]=(int)random(100);wantGear[i]=coin[i]<BOARD_GEAR_PCT;}
        {
            int gears=0;for(int i=0;i<3;++i)gears+=wantGear[i]?1:0;
            if(gears==3){int flip=0;for(int i=1;i<3;++i)if(coin[i]>coin[flip])flip=i;wantGear[flip]=false;}   //동전이 가장 컸던 칸
            else if(gears==0){int flip=0;for(int i=1;i<3;++i)if(coin[i]<coin[flip])flip=i;wantGear[flip]=true;}   //동전이 가장 작았던 칸
        }
        for(int i=0;i<3;++i) {
            int family;
            if(wantGear[i]) family=gear[random((unsigned)gn)];
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
        if(b.family==Boots||b.family==Gloves) return s;
        if(DefensiveGear(b.family)) {
            const long long value=armorOf(b,st);
            e.protect+=value;e.skip+=MergeBoard::ArmorSkipTurns(lv);
            if(st.realVitals)e.charge+=value;   //블록 값이 곧 턴당 회복량. 옛 목숨 모드는 통이 없다(세이브 검사와 맞춘다)
            if(lv==2)e.half=true;
            return s;
        }
        long long raw;Trait trait=Strike;bool summon=false;
        if(b.family<Roles) {
            const CrewStats& c=st.crew[b.crew<0||b.crew>=64?0:b.crew];
            raw=c.power*MergeBoard::CrewMul(lv);trait=c.trait;summon=c.summon;
            if(trait==Chill) {e.skip+=MergeBoard::ChillSkipTurns(lv);if(lv<=2)e.half=true;}
            if(trait==Strike)raw+=raw*MergeBoard::StrikePct(lv)/100;
            if(trait==Volley)raw+=raw*MergeBoard::VolleyPct(lv)/100;   //적이 하나라 탄이 전부 한 놈에게
        } else raw=std::max(st.weapon,b.ownedPower)*HeroGearPct/100*MergeBoard::GearMulOf(b.family-Sword,lv);   //히어로 검은 공격력의 300%
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
        for(const Block& b:ordered())if(b.family!=Gloves)shots.push_back(evaluate(b,st,effects));
        attacking=true; settleGuard(); return true;
    }
    //---- 성의 대포 ----
    //
    //판 밖에서 쏘는 한 발. 블록이 아니라 성의 것이라 shots 에는 계열 없는
    //블록(family -1)으로 선다. 공격과 같은 교환이다 - 반격을 받고 finish 로 끝난다.
    //판이 비어 있어도 쏠 수 있다. 공성 무기라 상대 방어막에는 두 배로 들어간다(step).
    bool fireCannon(long long damage) {
        if(choosing || attacking || lost || damage<=0) return false;
        shots.clear(); nextShot=0; effects=Effects(); damageDone=0;counterResolved=false;
        Shot s;s.block.family=-1;s.block.level=0;s.damage=damage;shots.push_back(s);
        attacking=true; settleGuard(); return true;
    }
    //판의 갑옷·투구·바지가 주는 보호를 effects 에 모은다. 공격 때는 evaluate 가 차례로
    //모으지만, 대포만 쏘거나 돌리기로 턴을 넘길 때도 반격은 오므로 따로 모아야 한다.
    void gatherDefense(const Stats& st) {
        effects=Effects();
        for(const Block& b:ordered()) if(DefensiveGear(b.family)) evaluate(b,st,effects);
    }
    bool fireCannon(const Stats& st,long long damage) {
        if(!fireCannon(damage)) return false;
        gatherDefense(st); settleGuard(); return true;
    }
    //---- 턴 넘기기 ----
    //
    //돌리기도 한 턴이다. 공격 없이 적의 반격만 받는다. 공격과 같은 길(attacking →
    //shouldCounterattack → finish)을 타되, finish 는 보상·돌리기 횟수 초기화를 하지 않는다.
    bool passTurn(const Stats& st) {
        if(choosing || attacking || lost) return false;
        shots.clear(); nextShot=0; damageDone=0; counterResolved=false;
        gatherDefense(st); settleGuard();
        attacking=true; passing=true; return true;
    }
    // One block at a time, in board order, so the adapter can animate every shot.
    bool step() {
        if(!attacking || enemyHp<=0 || nextShot>=(int)shots.size()) return false;
        Shot s=shots[nextShot++];
        damageDone+=s.damage;
        long long dmg=s.damage;
        if(monsterNpc>=0)dmg=MonsterParts::incomingDamage(dmg,monsterLoadout());
        if(s.block.family<0) {   //대포: 방어막은 두 배로 깎고, 남은 몫만 체력으로
            const long long guardHit=std::min(enemyGuard,dmg*2);
            enemyGuard-=guardHit; dmg-=guardHit/2;
        }
        const long long absorbed=std::min(enemyGuard,dmg);
        enemyGuard-=absorbed; enemyHp=std::max(0LL,enemyHp-(dmg-absorbed));
        if(s.summonTurns>0) summons.push_back(s);
        return true;
    }
    bool shouldCounterattack() const {
        return attacking&&nextShot==(int)shots.size()&&enemyHp>0&&!counterResolved&&skipTurns+effects.skip<=0;
    }
    //---- 반격이 얼마나 들어오는가 ----
    //
    //실제 수치(realVitals)에서는 방어막 통(guard)이 먼저 받고 남은 것이 체력으로 간다 -
    //본편 3-2 와 같은 규칙이다. 옛 다섯 목숨 모드는 "보호 1 = 한 방" 그대로.
    long long counterHit() const {
        if(enemyHp<=0||skipTurns+effects.skip>0)return 0;
        long long hit=enemyAttack*(BossTier(wave)?2:1);
        if(monsterNpc>=0)hit=MonsterParts::attackDamage(hit,monsterLoadout());
        if(effects.half)hit=(hit+1)/2;
        return hit;
    }
    long long counterDamage() const {
        const long long hit=counterHit();
        if(realVitals)return std::max(0LL,hit-monsterAbsorption());
        return std::max(0LL,hit-baseArmor-effects.protect);
    }
    //반격을 실제로 받는다: 통을 깎고 남은 것이 체력을 깎는다.
    void takeCounter() {
        const long long hit=counterHit();
        if(realVitals){const long long absorbed=monsterAbsorption();guard-=absorbed;lives=std::max(0LL,lives-(hit-absorbed));}
        else lives=std::max(0LL,lives-counterDamage());
        if(monsterNpc>=0){enemyHp+=monsterHealing();++monsterActionTurn;}
    }
    bool counterattack() {
        if(!shouldCounterattack())return false;
        takeCounter();counterResolved=true;
        return true;
    }
    int finish() {
        if(!attacking || (enemyHp>0 && nextShot<(int)shots.size())) return 0;
        if(passing && enemyHp>0) {
            //턴만 넘긴 것: 반격만 정산한다. 돌리기 횟수·보상·지속 피해는 그대로.
            if(enemyHp>0) {
                if(skipTurns>0) --skipTurns;
                else if(!counterResolved) takeCounter();
            }
            chargeGuard();
            shots.clear();attacking=false;nextShot=0;counterResolved=false;passing=false;
            lost=lives==0; return 0;
        }
        // Resolve equipment effects only once, after the presentation completes.
        int hearts=0, extraSpins=0;
        for(const Shot& s:shots) if(s.block.family==Boots) {
            hearts+=MergeBoard::NeckHearts(s.block.level);extraSpins+=MergeBoard::NeckSpins(s.block.level);
        }
        if(effects.dot>0) {dot=effects.dot;dotTurns=std::max(dotTurns,effects.dotTurns);}
        skipTurns=std::min(100,skipTurns+effects.skip);
        if(enemyHp>0) {
            if(skipTurns>0) --skipTurns;
            else if(!counterResolved)takeCounter();
            chargeGuard();
        } else {
            reward+=10LL*(stage+1)*(BossTier(wave)?10:1);
            if(++wave==WavesPerStage) {wave=0;++stage;lives=maxLives;guard=guardMax;}   //성을 넘기면 방어막도 다 찬다
            else chargeGuard();
            monsterActionTurn=0;monsterStage=stage;monsterWave=wave;
            dot=0;dotTurns=skipTurns=0;summons.clear();
        }
        shots.clear();attacking=false;nextShot=0;counterResolved=false;passing=false;
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
            o<<' '<<list->size(); for(const auto& b:*list) o<<' '<<b.family<<' '<<b.level<<' '<<b.crew<<' '<<b.x<<' '<<b.y<<' '<<(b.rot?1:0)
                <<' '<<b.ownedId<<' '<<b.ownedPower<<' '<<b.ownedDetail<<' '<<b.ownedGrade<<' '<<b.ownedW<<' '<<b.ownedH;
        }
        o<<' '<<summons.size();
        for(const auto& s:summons) o<<' '<<s.block.family<<' '<<s.block.level<<' '<<s.block.crew<<' '<<s.damage<<' '<<s.summonTurns;
        o<<' '<<attacking<<' '<<nextShot<<' '<<reward<<' '<<damageDone
         <<' '<<effects.expose<<' '<<effects.inspire<<' '<<effects.skip<<' '<<effects.protect
         <<' '<<effects.half<<' '<<effects.dot<<' '<<effects.dotTurns<<' '<<shots.size();
        for(const Shot& s:shots)o<<' '<<s.block.family<<' '<<s.block.level<<' '<<s.block.crew<<' '<<s.block.x<<' '<<s.block.y<<' '<<s.damage<<' '<<s.summonTurns;
        o<<' '<<counterResolved<<' '<<realVitals<<' '<<baseArmor<<' '<<enemyAttack;
        o<<' '<<guard<<' '<<guardMax<<' '<<effects.charge;   //v11: 방어막 통 (v13: 최대치 = 체력×ShieldPct, 장비는 회복)
        o<<' '<<monsterNpc<<' '<<monsterActionTurn<<' '<<passing; //v12: action cycle and spin counter turns
        o<<' '<<battleEnergy; //v15: local battle supply, separate from admission energy
        return o.str();
    }
    static bool crewOk(const Block& b) {
        return b.family<Roles?(b.crew>=0&&b.crew<64):b.crew==-1;
    }
    bool decode(const std::string& text) {
        Run r; r.roster=roster; std::istringstream in(text); std::string magic;int version;
        // v7's accessory family (6) becomes boots, preserving the run and utility effects.
        if(!(in>>magic>>version)||magic!="MR3"||(version!=SaveVersion&&version!=15&&version!=14&&version!=13&&version!=12&&version!=11&&version!=10&&version!=9&&version!=8&&version!=7)) return false;
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
            int count;if(!(in>>count)||count<0||count>(list?(version>=16?Cells+3:3):Cells)) return false;
            for(int i=0;i<count;++i) {
                Block b;int rot=0;if(!(in>>b.family>>b.level>>b.crew>>b.x>>b.y>>rot)||b.family<0||b.family>=FamilyCount||b.level<1||b.level>MaxLevel||!crewOk(b)) return false;b.rot=rot!=0;
                if(version>=14){
                    if(!(in>>b.ownedId>>b.ownedPower>>b.ownedDetail>>b.ownedGrade>>b.ownedW>>b.ownedH))return false;
                    if(b.ownedId<0||b.ownedPower<0||b.ownedPower>100000000LL)return false;
                    if(!b.ownedId&&(b.ownedPower||b.ownedDetail!=-1||b.ownedGrade||b.ownedW||b.ownedH))return false;
                    if(b.ownedId&&(b.family<Roles||b.ownedDetail<0||b.ownedDetail>(b.family==Sword?34:7)||b.ownedGrade<0||b.ownedGrade>5||b.ownedW<1||b.ownedW>8||b.ownedH<1||b.ownedH>8))return false;
                }
                //장비는 여섯 부위 어느 것이든 판에 설 수 있다. 역할 블록만 시작 슬롯의 역할이어야 한다.
                if(b.family<Roles&&std::find(r.families,r.families+3,b.family)==r.families+3) return false;
                if(!list) {if(!r.fits(b,-1,-1,true)) return false;r.board.push_back(b);}   //겹친 채로도 저장된다
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
        // Accept both old saves containing glove turns and new passive-only gloves.
        if(count!=(int)sorted.size())sorted.erase(std::remove_if(sorted.begin(),sorted.end(),[](const Block& b){return b.family==Gloves;}),sorted.end());
        for(int i=0;i<count;++i) {
            Shot s;if(!(in>>s.block.family>>s.block.level>>s.block.crew>>s.block.x>>s.block.y>>s.damage>>s.summonTurns)
                ||s.damage<0||s.damage>1000000000000000LL||s.summonTurns<0||s.summonTurns>3)return false;
            if(i>=(int)sorted.size())return false;
            const Block& b=sorted[i];
            if(s.block.family!=b.family||s.block.level!=b.level||s.block.crew!=b.crew||s.block.x!=b.x||s.block.y!=b.y)return false;
            s.block=b;r.shots.push_back(s);
        }
        if(r.attacking?((count!=(int)sorted.size()&&!(version>=12&&count==0))||r.choosing||r.lost):(count!=0||r.nextShot!=0))return false;
        if(version>=9&&!(in>>r.counterResolved))return false;
        if(version>=10) {
            if(!(in>>r.realVitals>>r.baseArmor>>r.enemyAttack)||r.baseArmor<0||r.baseArmor>1000000000000000LL||r.enemyAttack<1||r.enemyAttack>1000000000000000LL)return false;
            if(!r.realVitals&&(r.maxLives>20||r.baseArmor!=0||r.enemyAttack!=1))return false;
        }
        if(version>=11) {
            if(!(in>>r.guard>>r.guardMax>>r.effects.charge)||r.guardMax<0||r.guardMax>2000000000000000LL||r.guard<0||r.guard>r.guardMax
               ||r.effects.charge<0||r.effects.charge>r.effects.protect)return false;
            if(!r.realVitals&&(r.guard!=0||r.guardMax!=0||r.effects.charge!=0))return false;
        } else if(r.realVitals) {
            //v10 까지는 방어를 한 방에서 뺐다. 이어 하는 판은 통을 찬 채로 시작한다.
            r.guardMax=r.baseArmor+r.effects.protect;r.guard=r.guardMax;
        }
        if(version<13&&r.realVitals) {
            //v12 까지는 최대치가 장비 합이었다. 체력 비례 통으로 바꿔 찬 채로 잇는다. 블록 회복량도 100% 로.
            r.guardMax=shieldFor(r.maxLives);r.guard=r.guardMax;r.effects.charge=r.effects.protect;
        }
        if(version>=12){
            if(!(in>>r.monsterNpc>>r.monsterActionTurn>>r.passing)||r.monsterActionTurn<0||r.monsterActionTurn>1000000
               ||(r.monsterNpc!=-1&&!MonsterParts::enemy(r.monsterNpc)))return false;
            r.monsterStage=r.stage;r.monsterWave=r.wave;
            if(r.passing?(!r.attacking||count!=0||r.nextShot!=0):(r.attacking&&count!=(int)sorted.size()))return false;
        }
        if(r.counterResolved&&(!r.attacking||r.nextShot!=count||r.enemyHp<=0))return false;
        if(version>=15&&(!(in>>r.battleEnergy)||r.battleEnergy<0||r.battleEnergy>BattleEnergyMax))return false;
        in>>std::ws;if(!in.eof()) return false;
        if(r.lost&&r.lives>0&&r.battleEnergy>0)return false;
        if(r.lives==0&&!r.lost&&!(r.attacking&&r.counterResolved))return false;
        int passiveBefore=0;
        for(int i=0;i<r.nextShot;++i)if(r.shots[i].block.family==Gloves)++passiveBefore;
        r.shots.erase(std::remove_if(r.shots.begin(),r.shots.end(),[](const Shot& shot){return shot.block.family==Gloves;}),r.shots.end());
        r.nextShot-=passiveBefore;
        *this=r;return true;
    }
};
}
#pragma pack(pop)
