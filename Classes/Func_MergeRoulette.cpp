#include "Core.h"
#pragma pack(push, 8)
#include "Data.h"
#include "Func.h"
#include "Text.h"
#include <cstring>
#include "Func_MergeRoulette.h"
#include "MergeRouletteModel.h"
#include "StageBackground.h"
#include "Data/AllyBalanceData.h"
#include "Data/CmfData.h"
#include "Data/CastleData.h"
#include "Data/MergeTreeData.h"
#include "Data/CastleFacilities.h"
#include "MergeCastleTransition.h"
#include "Data/MergeCastleRebuild.h"
#include "2d/CCAutoPolygon.h"
#include "Data/HybridSd3d.h"
#include "Data/HybridCastleFleet.h"
#include <cmath>
#include <fstream>
#include <cstdio>
#include <cstdlib>

namespace {
using namespace MergeRoulette;
Run run;
Stats stats;
Roster roster;
int treeWeights[FamilyCount]={};
ITEM treeEquipment[GearCount][MaxLevel];
bool active=false,review=false;
int oldMode=ACTIONRPG, ticks=0, animation=0, picked=-1, finger=-1;
float gearAngle=0.f,gearStartAngle=0.f;
float reviewAttackGear=0.f;
struct SpinDrop {Block source,target;};
std::vector<SpinDrop> spinDrops;
Run spinLandingPlan;
int spinFlightFrame=-1;
bool spinFlying(){return spinFlightFrame>=0;}
Block reelSymbols[3];
bool hasReelSymbols=false;
bool pickedTray=false;
float pointerX=0,pointerY=0,downX=0,downY=0;
int pickCellX=0,pickCellY=0, flash=0;
std::vector<int> pool;
std::vector<Block> reviewAttackBlocks;
std::string message;
OBJECT hero;
int heartCapacity=20;
float heartBlink=0,messageTime=0;
int heartDisplay=0,spentHeart=-1;
long long observedHearts=0;
float introElapsed=-1;
int reviewCombatTick=-1,introCaptures=0,entryCaptures=0;
bool reviewCapturePending=false,reviewFinalCapture=false,reviewDone=false;
std::vector<std::string> reviewCaptureQueue;
constexpr float IntroDuration=3.8f;
bool introActive() {return introElapsed>=0&&introElapsed<IntroDuration;}
Shape castleShape(int stage) {
    Shape out;out.width=out.height=0;for(auto& row:out.rows)row=0;
    int c=std::max(0,std::min(9,stage)),start=castleGridCellStart[c],count=castleGridCellCnt[c];
    for(int i=0;i<count;++i) {
        int x=castleGridCell[(start+i)*2],y=castleGridCell[(start+i)*2+1];
        if(x>=0&&x<Width&&y>=0&&y<Height){out.width=std::max(out.width,x+1);out.height=std::max(out.height,y+1);}
    }
    for(int i=0;i<count;++i) {
        int x=castleGridCell[(start+i)*2],y=castleGridCell[(start+i)*2+1];
        if(x>=0&&x<out.width&&y>=0&&y<out.height)out.rows[out.height-1-y]|=1u<<x;
    }
    return out;
}
bool usesCastleGrid() {
    Shape expected=castleShape(run.stage);
    if(run.shape.width!=expected.width||run.shape.height!=expected.height)return false;
    for(int y=0;y<Height;++y)if(run.shape.rows[y]!=expected.rows[y])return false;
    return true;
}
struct Box {
    int x,y,w,h;
    bool has(float px,float py) const {return px>=x&&px<x+w&&py<=y&&py>y-h;}
};

//---- 합성 연출 ----
//
//합쳐져도 블록 하나가 조용히 바뀔 뿐이라 "합쳐졌다" 가 안 읽혔다.
//모델이 남긴 번호(run.mergeSeq)가 달라지면 그 자리에서 짧게 터뜨린다.
unsigned mergeSeenSeq=0;
int mergeFlash=0;
Box mergeBox={0,0,0,0};
int mergeShownLevel=0;
struct Layout {
    float scale;
    int cell, cellH, ground, arenaBottom;
    Box board, slot, lever, heart, spin, attack, exit, left, right, reroll, confirm;
};
Layout layout() {
    Layout l; l.scale=DX/640.0f;
    const float s=l.scale;
    // Everything below the scenery is anchored to the 640 x 850 baseline.
    // Taller phones reveal more scenery above; they never stretch the board.
    int margin=(int)(72*s),bottom=(int)(12*s),bh=(int)(56*s);
    l.spin={margin,bottom+bh,(int)(224*s),bh};
    l.attack={DX-margin-(int)(224*s),bottom+bh,(int)(224*s),bh};
    const int heartCols=std::min(10,heartCapacity),heartRows=(heartCapacity+heartCols-1)/heartCols;
    const int heartWidth=(heartCols*27+40)*s;
    l.heart={(DX-heartWidth)/2,(int)(156*s),heartWidth,(int)((heartRows*23+14)*s)};
    // RH's 512 x 218 board at a uniform 0.625 scale, with a right-hand lever.
    l.slot={(int)(132*s),(int)(280*s),(int)(348*s),(int)(116*s)};
    l.lever={l.slot.x+l.slot.w+(int)(4*s),l.slot.y-(int)(3*s),(int)(40*s),(int)(104*s)};
    l.cell=std::max(1,(int)(64*s));l.cellH=l.cell;
    int bw=l.cell*run.shape.width,bhGrid=l.cellH*run.shape.height;
    l.board={(DX-bw)/2,(int)(305*s)+bhGrid,bw,bhGrid};
    l.arenaBottom=l.board.y+(int)(76*s);
    l.ground=(run.stage==0?(int)(1077*DX/1089.f):l.board.y+(int)(90*s))+(int)(40*s);
    l.exit={DX-(int)(76*s),DY-(int)(8*s),(int)(66*s),(int)(28*s)};
    l.left={(int)(48*s),l.slot.y,(int)(36*s),l.slot.h};
    l.right={DX-(int)(84*s),l.slot.y,(int)(36*s),l.slot.h};
    l.reroll=l.spin;l.confirm=l.attack;
    return l;
}
void panel(const Box& b,int color,int border=0x61718C) {
    int p=std::max(1,DX/320);
    MemRect(b.x-p,b.y+p,b.w+2*p,b.h+3*p,0x080E1B);
    MemRect(b.x,b.y,b.w,b.h,border);
    MemRect(b.x+p,b.y-p,b.w-2*p,b.h-2*p,color);
    MemRect(b.x+2*p,b.y-2*p,b.w-4*p,p,0x7B7C80);
    MemRect(b.x+p,b.y-b.h+p,b.w-2*p,p,0x151421);
}
void label(const char* text,int x,int y,float size=0.7f,int color=0xF4E8CC) {
    SetFontColor(color);CenterTextStrSolid(text,x,y,size*DX/640.0f);
}
int blend(int a,int b,float t) {
    int r=(int)(((a>>16)&255)*(1-t)+((b>>16)&255)*t);
    int g=(int)(((a>>8)&255)*(1-t)+((b>>8)&255)*t);
    int c=(int)((a&255)*(1-t)+(b&255)*t);
    return (r<<16)|(g<<8)|c;
}
Box inset(Box b,int n) {return {b.x+n,b.y-n,b.w-2*n,b.h-2*n};}
void bevel(Box b,int color,int corner) {
    if(b.w<=0||b.h<=0)return;
    corner=std::min(corner,std::min(b.w,b.h)/2);
    MemRect(b.x,b.y-corner,b.w,b.h-2*corner,color);
    for(int i=0;i<corner;++i) {
        int trim=corner-i;
        MemRect(b.x+trim,b.y-i,b.w-2*trim,1,color);
        MemRect(b.x+trim,b.y-b.h+i+1,b.w-2*trim,1,color);
    }
}
void mergeGoldFrame(Box b,int topColor,int bottomColor,bool enabled=true) {
    int p=std::max(1,DX/640);
    bevel({b.x,b.y-3*p,b.w,b.h+3*p},0x050916,12*p);
    bevel(b,enabled?0x8B4808:0x4B5369,12*p);
    bevel(inset(b,2*p),enabled?0xFFE48A:0x9EA5B3,10*p);
    bevel(inset(b,5*p),enabled?0xF7B517:0x646E81,7*p);
    bevel(inset(b,7*p),0x53350D,5*p);
    Box inner=inset(b,9*p);
    for(int y=0;y<inner.h;++y) {
        int trim=y<3*p?3*p-y:y>inner.h-3*p?y-inner.h+3*p:0;
        MemRect(inner.x+trim,inner.y-y,inner.w-2*trim,1,blend(topColor,bottomColor,y/(float)inner.h));
    }
    MemRect(b.x+14*p,b.y-3*p,b.w-28*p,p,enabled?0xFFF6B8:0xC1C8D0);
}
void heart(int x,int y,int size,bool filled) {
    static const char* mask[]={
        "00111100111100","01111111111110","11111111111111","11111111111111",
        "11111111111111","11111111111111","01111111111110","00111111111100",
        "00011111111000","00001111110000","00000111100000","00000011000000"};
    float p=size/14.f;
    for(int row=0;row<12;++row) {
        auto colorAt=[&](int col) {
            if(col>=14||mask[row][col]!='1')return -1;
            bool edge=col==0||col==13||row==0||row==11||mask[row][col-1]=='0'||mask[row][col+1]=='0'||(row<11&&mask[row+1][col]=='0');
            return edge?(filled?0x7D1527:0x8A8790):filled?blend(0xFF4B55,0xD71D2D,row/12.f):0x444754;
        };
        for(int col=0;col<14;) {
            int color=colorAt(col),end=col+1;
            while(end<14&&colorAt(end)==color)++end;
            if(color>=0)MemRect(x+(int)(col*p),y-(int)(row*p),std::max(1,(int)std::ceil(end*p)-(int)(col*p)),std::max(1,(int)std::ceil(p)),color);
            col=end;
        }
    }
    if(filled) {MemRect(x+(int)(3*p),y-(int)(2*p),(int)(3*p),(int)(2*p),0xFFF0DC);MemRect(x+(int)(2*p),y-(int)(4*p),(int)(2*p),(int)p,0xFFA6A2);}
}
void pixelStroke(int x,int y,int ax,int ay,int bx,int by,int width,int color,float p) {
    int count=std::max(std::abs(bx-ax),std::abs(by-ay));
    for(int i=0;i<=count;++i) {
        float t=count?i/(float)count:0;
        MemRect(x+(int)((ax+(bx-ax)*t-width*.5f)*p),y-(int)((ay+(by-ay)*t-width*.5f)*p),
            std::max(1,(int)(width*p)),std::max(1,(int)(width*p)),color);
    }
}
void actionIcon(const Box& b,bool attack) {
    float p=b.w/24.f;int x=b.x,y=b.y;
    if(attack) {
        for(int side=0;side<2;++side) {
            int a=side?21:3,z=side?3:21;
            pixelStroke(x,y,a,3,z,21,6,0x070C20,p);
            pixelStroke(x,y,a,3,z,21,4,0xA6ADD4,p);
            pixelStroke(x,y,a,3,z,21,1,0xFFF9F2,p);
            pixelStroke(x,y,side?6:18,17,side?2:22,21,5,0x723300,p);
            pixelStroke(x,y,side?6:18,17,side?2:22,21,3,0xFFB92C,p);
            pixelStroke(x,y,side?4:20,19,side?1:23,23,3,0xD27A10,p);
        }
    } else {
        static const char* mask[]={
            "000000000000000000000000","000000000000001100000000","000000000000001110000000",
            "000000111111111111000000","000011111111111111100000","000111100000001111110000",
            "001111000000001111100000","001110000000001111000000","011100000000001110000000",
            "011100000000001100000000","011100000000000000000000","000000000000000000000000",
            "000000000000000000001110","000000001100000000001110","000000011100000000001110",
            "000000111100000000011100","000001111100000000111100","000011111100000011111000",
            "000001111111111111110000","000000111111111111000000","000000011100000000000000",
            "000000001100000000000000","000000000000000000000000","000000000000000000000000"};
        for(int pass=0;pass<2;++pass)for(int r=0;r<24;++r)for(int c=0;c<24;++c)if(mask[r][c]=='1') {
            int pad=pass?0:1;
            MemRect(x+(int)((c-pad)*p),y-(int)((r-pad)*p),std::max(1,(int)std::ceil((1+2*pad)*p)),std::max(1,(int)std::ceil((1+2*pad)*p)),pass?0x91E7FF:0x071728);
        }
    }
}
void shield(int x,int y,int size) {
    float p=size/10.f;
    for(int r=0;r<12;++r) {
        int trim=r<2?2-r:r<7?0:(r-6)/2;
        MemRect(x+(int)(trim*p),y-(int)(r*p),std::max(1,(int)((10-2*trim)*p)),std::max(1,(int)std::ceil(p)),0xDCE8ED);
        if(r>1&&r<10)MemRect(x+(int)((trim+1)*p),y-(int)(r*p),std::max(1,(int)((8-2*trim)*p)),std::max(1,(int)std::ceil(p)),r<6?0x4EACF8:0x2366BB);
    }
}
// Dedicated art is registered independently of gameplay state.
#include "MergeCastleArt.inc"
//---- 유닛 패 ----
//
//[같은 서식]
//아군은 "목숨 3 / 3", 적은 "330/330" 으로 서식이 달랐다. 둘을 나란히
//놓고 견줄 수가 없었다. 두 패가 같은 함수에서 나오므로 이제 어긋날
//수 없다 - 색만 다르다.
//
//[위가 방어, 아래가 체력]
//맞으면 방어가 먼저 막고 그다음 체력이 깎인다. 깎이는 차례대로 위아래로
//쌓아야 "방패가 먼저 버틴다" 가 그림으로 읽힌다.
//
//[글자 대신 아이콘]
//방패 = 방어, 하트 = 체력. 말을 지운 자리를 바와 숫자가 가져간다.
//
//[방어는 칸으로 센다]
//방어는 "몇 번 막아 준다" 라서 최대치가 없다. 비율 바로 그리면 늘 꽉
//찬 바가 되므로, 한 번 막을 때마다 칸 하나로 센다.
void unitPlate(const Box& plate,long long hp,long long max,int guard,
    int barBg,int barFg,bool hot) {
    const float s=DX/640.f;
    char text[48];

    uiArt(MergeCastleArt::UnitPlate,plate);

    const int pad=std::max(1,(int)(7*s));
    const int mark=(int)(14*s);
    const int barX=plate.x+pad+mark+(int)(5*s);
    const int barW=std::max(1,plate.x+plate.w-pad-barX);
    const int guardH=(int)(13*s),hpH=(int)(17*s);
    const int guardY=plate.y-pad;
    const int hpY=guardY-guardH-(int)(3*s);

    //---- 위: 방어 ----
    shield(plate.x+pad+(int)(2*s),guardY,(int)(12*s));
    MemRect(barX,guardY,barW,guardH,0x2A3344);
    if(guard>0) {
        const int pips=std::min(guard,12);
        const int cell=std::max(1,(barW-(pips-1)*(int)(2*s))/pips);
        for(int k=0;k<pips;++k)
            MemRect(barX+k*(cell+(int)(2*s)),guardY,cell,guardH,0x4EACF8);
        std::snprintf(text,sizeof(text),"%d",guard);
        label(text,barX+barW-(int)(11*s),guardY-(int)(2*s),.55f,0x0A1526);
    }

    //---- 아래: 체력 ----
    heart(plate.x+pad,hpY,mark,hp>0);
    MemRect(barX,hpY,barW,hpH,barBg);
    if(max>0&&hp>0)MemRect(barX,hpY,(int)(barW*(double)hp/(double)max),hpH,barFg);
    std::snprintf(text,sizeof(text),"%lld / %lld",hp,max);
    label(text,barX+barW/2,hpY-(int)(4*s),.6f,hot?0xFFB060:0xFFFFFF);
}
void choice(const Box& b,bool attack,bool enabled) {
    const float s=DX/640.f;
    SetAlpha(32);grayScale=0;SetColor(0);
    mergeGoldFrame(b,attack?0xEC4A13:0x1369D9,attack?0x8D1607:0x073B8D,enabled);
    const int color=enabled?0xFFF7E4:0xC4CBD3;
    label(attack?"지금 공격":"더 돌리기",b.x+(int)(86*s),b.y-(int)(17*s),.80f,color);
    heart(b.x+(int)(151*s),b.y-(int)(17*s),(int)(24*s),enabled);
    label("-1",b.x+(int)(192*s),b.y-(int)(18*s),.77f,color);
}
void button(const Box& b,const char* title,const char* sub,int color,bool enabled=true) {
    float s=DX/640.0f;
    if(b.h>50*s)mergeGoldFrame(b,enabled?color:0x252D3C,enabled?blend(color,0x050A20,.45f):0x1C2534,enabled);
    else panel(b,enabled?color:0x252D3C,enabled?0xD7AE66:0x4C5565);
    int tx=b.x+b.w/2;
    label(title,tx,b.y-b.h*(sub?.32f:.5f),b.h>50*s?.91f:.64f,enabled?0xFFF2D8:0x89909E);
    if(sub) {
        bool cost=std::strncmp(sub,"하트 -1",7)==0;
        if(cost) {
            heart(tx-(int)(26*s),b.y-(int)(b.h*.65f),(int)(21*s),enabled);
            label("-1",tx+(int)(15*s),b.y-(int)(b.h*.73f),.64f,enabled?0xFFB6BC:0x89909E);
        } else label(sub,tx,b.y-b.h*.76f,.5f,enabled?0xE4D6BD:0x89909E);
    }
}
void save() {
    if(review)return;
    std::string encoded=run.encode();
    if(encoded.size()>=sizeof(robin.mergeRouletteRun)) {message="진행 데이터가 저장 한도를 넘었습니다.";return;}
    std::memset(robin.mergeRouletteRun,0,sizeof(robin.mergeRouletteRun));
    std::memcpy(robin.mergeRouletteRun,encoded.data(),encoded.size());
    robin.mergeRouletteHero=curHero;
    // Hearts, rewards and the run are one optimistic-revision server snapshot.
    SaveGame();
}
long long hpFor(int stage,int wave) {
    int tier=std::min(stage,(int)WAVE_HP_MAX_TIER);
    double hp=WAVE_HP_BASE*std::pow(WAVE_HP_TIER_MUL/100.0,tier);
    if((stage*10+wave+1)%100==0)hp*=WAVE_HP_BIGBOSS_MUL;
    else if(wave==9)hp*=WAVE_HP_MIDBOSS_MUL;
    else if(wave==4)hp*=WAVE_HP_SUBBOSS_MUL;
    return (long long)std::min(hp,1000000000000000.0);
}
const char* treeName(int f) {
    if(f>=Sword) {
        static const char* names[GearCount]={"무기","몸통","발","머리","손","하체"};
        return f<FamilyCount?names[f-Sword]:"";
    }
    return f>=0&&f<Roles?MergeTrees::RoleName[f]:"?";
}
void configure() {
    // 계열 = 역할 4 + 코스튬 장비 6. 보유 동료가 역할 × ★ 사다리(roster)에 선다.
    // 같은 역할 ★n 둘을 합치면 roster 의 ★n+1 중 하나가 나온다.
    pool.clear();roster=Roster();bool owned[64]={};int crewLevels[64]={};
    for(int i=0;i<TOTALINVENTORY;++i) {
        const ITEM& it=robin.inven[i];
        if(it.type==ITEM_CREW&&it.lv>0&&it.detail>=0&&it.detail<64) {
            owned[it.detail]=true;crewLevels[it.detail]=std::max(crewLevels[it.detail],(int)it.lv);
        }
    }
    if(review)for(int i=0;i<64;++i){owned[i]=true;crewLevels[i]=1;}
    for(int c=0;c<64;++c)if(owned[c])roster.add(MergeTrees::Role(c),MergeTrees::Star(c),c);
    for(int r=0;r<Roles;++r)if(roster.has(r,1))pool.push_back(r);
    for(int f=Sword;f<FamilyCount;++f)pool.push_back(f);
    hero=ao[PLAYER];hero.type=std::max(0,std::min(2,curHero));
    if(hero.equip[EQUIP_WEAPON].type==EMPTY)
        std::memcpy(hero.equip,robin.charData[hero.type].equip,sizeof(hero.equip));
    static const int gearSlots[GearCount]={EQUIP_WEAPON,EQUIP_ARMOR,EQUIP_BOOTS,EQUIP_HELM,EQUIP_GLOVE,EQUIP_PANTS};
    static const int gearTypes[GearCount]={ITEM_SWORD,ITEM_ARMOR,ITEM_GREAVES,ITEM_HELM,ITEM_GUNTLET,ITEM_KILT};
    for(int g=0;g<GearCount;++g) {
        int family=Sword+g,equip=gearSlots[g];
        ITEM base=hero.equip[equip];

        //---- 종류는 계열이 정한다 ----
        //
        //전에는 끼고 있는 물건의 종류를 그대로 가져왔다(base.type). 그런데
        //hero 는 ao[PLAYER] 라서, 판에서 돌아온 직후면 가방이 입혀 놓은
        //것이 그대로 남아 있다(GridWearLoadout). 갑옷 칸에 검이 들어 있으면
        //갑옷 계열이 검 그림으로 그려진다 - 판에 나무몽둥이가 둘 서는데
        //하나는 검, 하나는 갑옷이라 합쳐지지 않는다.
        //
        //계열이 곧 부위다. 종류는 거기서 받고, 끼고 있는 것은 번호·등급만
        //빌려 온다 - 그것도 부위가 맞을 때만.
        const int type=gearTypes[g]+hero.type;
        const bool sameSlot=base.type==type;
        const int detail=sameSlot?base.detail:0;

        if(!sameSlot) {base.lv=1;base.grade=GRADE_NORMAL;}
        for(int l=0;l<MaxLevel;++l)MakeItem(&treeEquipment[g][l],type,std::max(1,(int)base.lv),base.grade,
            MergeTrees::GearDetail(family,detail,l+1),0);
    }
    long long weapon=std::max(20LL,std::min(GetEquipPower(&hero.equip[EQUIP_WEAPON],hero.equip[EQUIP_WEAPON].lv),100000000LL));
    stats=Stats();stats.weapon=weapon;
    for(int f=0;f<FamilyCount;++f)treeWeights[f]=f<Roles?MergeTrees::RoleWeight[f]:4;
    for(int c=0;c<64;++c) {
        // ★1·2 는 SKILL1, ★3·4 는 SKILL2, ★5·6 은 SKILL3(궁극기/소환). 한 방 = power × 2^(★-1) 은 모델이 곱한다.
        CrewStats& cs=stats.crew[c];int star=MergeTrees::Star(c),band=star<=2?0:star<=4?1:2;
        int skill=crewData[c*CREWDATASIZE+CREWDATA_SKILL1+band];
        long long power=std::max(10LL,std::min(GetCrewPower(c,std::max(1,crewLevels[c])),100000000LL));
        int pct=std::max(100,SkillDamagePct(skill));
        cs.power=power*pct/100;cs.trait=(Trait)MergeTrees::Trait(c);
        int kind=SkillKind(skill);
        cs.summon=band==2&&(kind==SUMMON||kind==CREWSUMMON||kind==SUMMONHERO);
        if(band==2&&kind==HEROSKILL)cs.power=weapon*std::max(400,pct)/100;
    }
}

bool pay() {
    if(robin.heart<1) {message="하트가 부족합니다. 회복 후 다시 시도하세요.";messageTime=3;PlayMusic(M_ERROR);return false;}
    GetItem(ITEM_HEART,false,false,false,-1,false);
    AddBar(&bar[BAR_HEART],-1,BARFRAME);
    spentHeart=heartDisplay-1;heartDisplay=std::max(0,heartDisplay-1);
    observedHearts=robin.heart;heartBlink=.72f;
    return true;
}
void iconGround(const Box& box,int width,int lift=0) {
    int p=std::max(1,(int)(DX/640.f)),cx=box.x+box.w/2;
    const int w=std::max(p,std::min(box.w-4*p,width));
    const float z=w/(float)(24*_2X);
    ShadowImage(24*_2X,16*_2X,1*_2X,1*_2X,cx-w/2,
        box.y-box.h+5*p+lift+(int)(8*_2X*z),SHADOW_IMG,z);
}
//---- 걸을 수 있는 사람인가 ----
//
//전에는 crewPos 의 대기 장수가 둘 이상이면 걷게 했다. 그런데 64명 전원이
//대기 그림을 4장씩 가지고 있어서 아무도 안 걸러졌고, 걷는 그림이 없는
//사람(파도 어인·대장장이·함포선장 등 26명)이 선 채로 옆으로 미끄러졌다.
//
//성 로비와 같은 잣대(CrewWalkMotion - cmf 이동표 State 1)를 쓴다.
//걷는 사람이면 step 번째 걷기 모션 번호를, 아니면 -1 을 준다.
int crewWalkMotion(int crew,int step) {
    if(crew<0||crew>=64)return -1;
    const int npc=crewData[crew*CREWDATASIZE+CREWDATA_TYPE];
    if(npc<0)return -1;
    const int cmf=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF];
    if(cmf<0||cmf>=MAXCMF)return -1;
    if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);
    int frames=0;const signed short* motions=nullptr;
    if(!CrewWalkMotion(cmf,npc,frames,motions)||frames<=0)return -1;
    return motions[std::max(0,step)%frames];
}
//---- 제자리에서 쉬는 자세 ----
//
//걷지 않는 사람도 숨은 쉰다. 대기 그림이 둘 이상이면(crewPos 의 장수)
//step 번째 대기 모션을 주고, 한 장뿐이면 -1 - 그 사람만 멈춰 선다.
int crewIdleMotion(int crew,int step) {
    if(crew<0||crew>=64)return -1;
    const int npc=crewData[crew*CREWDATASIZE+CREWDATA_TYPE];
    if(npc<0)return -1;
    const int frames=crewPos[npc*5+1];
    if(frames<=1)return -1;
    return crewPos[npc*5]+std::max(0,step)%frames;
}
//---- 동료 하나를 칸에 세운다 ----
//
//icon() 의 동료 가지를 떼어낸 것이다. 로비의 방 주민은 걸어 다녀야 해서
//모션 번호(crewWalkMotion)와 보는 쪽을 밖에서 받는다. motion<0 이면
//쉬는 자세 첫 장 - 릴과 판, 그리고 걷는 그림이 없는 주민이 그렇다.
void crewArt(int crew,const Box& box,float fraction,int footLift,int motionIn,int dir) {
    if(crew<0||crew>=64)return;
    int npc=crewData[crew*CREWDATASIZE+CREWDATA_TYPE];
    int cmf=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF];
    if(cmf<0||cmf>=MAXCMF)return;
    if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);
    int motion=motionIn>=0?motionIn:crewPos[npc*5];
    if(motion<0||motion>=cmf_m_cnt[cmf])motion=crewPos[npc*5];
    const auto* bounds=cmfMotionImgSize[cmf]+motion*4;
    int p=std::max(1,(int)(DX/640.f));
    float z=std::min((box.w-2*p)/(float)std::max(1,(int)bounds[2]),(box.h-7*p-footLift)/(float)std::max(1,(int)bounds[3]))*fraction;
    iconGround(box,std::max(box.w/2,(int)(bounds[2]*z*.85f)),footLift);
    DrawCmfDetail(cmf,motion,box.x+box.w/2,box.y-box.h+5*p+footLift+(int)(bounds[3]*z/2),dir,z,0,true);
}
void icon(int family,const Box& box,float fraction=0.96f,bool atlas=false,int level=1,int crew=-1,int footLift=0) {
    if(family<0||family>=FamilyCount)return;
    SetColor(0);grayScale=0;
    if(family<Sword) {
        // 블록이 든 동료. 없으면(릴 회전·계열 카드) 그 역할·★ 의 대표 — 보유분 먼저, 없으면 표의 첫 사람.
        if(crew<0)crew=roster.first(family,std::max(1,std::min((int)MaxLevel,level)));
        if(crew<0)crew=MergeTrees::CrewAt(family,std::max(1,std::min((int)MaxLevel,level)),0);
        crewArt(crew,box,fraction,footLift,-1,RIGHT);
    } else {
        ITEM item=treeEquipment[family-Sword][std::max(0,std::min(MaxLevel-1,level-1))];
        //---- 릴 안은 아이콘, 판 위는 가방 그림 ----
        //
        //릴에서 도는 동안에는 32x32 아이콘 한 칸이 맞다. 가방 그림은
        //칸 바탕색을 같이 들고 오므로, 돌아가는 릴에 네모가 줄줄이 서면
        //룰렛으로 안 보인다.
        //
        //판에 놓인 뒤에는 가방이 쓰는 그림이다. 칸을 차지하는 물건으로
        //보여야 하고, 같은 검이 두 화면에서 다른 물건으로 보이면 안 된다.
        //(atlas 는 부르는 쪽이 "릴인가" 를 넘기는 깃발이다.)
        if(!atlas) {
            const int pad=std::max(1,(int)(DX/640.f))*2;
            const int w=std::max(1,(int)((box.w-pad*2)*fraction));
            const int h=std::max(1,(int)((box.h-pad*2-footLift)*fraction));

            iconGround(box,w*3/4,footLift);
            MergeBoardDrawGear(&item,box.x+(box.w-w)/2,
                box.y-(box.h-h)/2-footLift,w,h,ALPHA_MAX);
        } else {
            const int size=(int)(std::min(box.w-2,box.h-7)*fraction);
            const int idx=item.icon;

            DrawImage(32,32,1+33*(idx&7),1+33*((idx&63)>>3),
                box.x+(box.w-size)/2,box.y-(box.h-size)/2,false,0,0,0,32,
                size/32.0f,sprite[ITEM_IMG+(idx>>6)],ITEM_IMG+(idx>>6));
        }
    }
}
void drawSlotFrame(const Box& b) {
    const int img=MERGE_REBUILD_UI_IMG+MergeCastleArt::Gear;
    const auto& f=MergeCastleArt::UiFrames[MergeCastleArt::Gear];
    const auto& housing=MergeCastleArt::UiFrames[MergeCastleArt::Slot];
    if(!sprite[img])LoadImg(img);
    if(sprite[img])for(int side=0;side<2;++side){
        const float x=b.x+((side?1920:245)-housing.x)*b.w/(float)housing.w;
        const float y=b.y-(425-housing.y)*b.h/(float)housing.h;
        const float z=(470*b.w/(float)housing.w)/std::max(f.w,f.h);
        RotateImage(f.w,f.h,f.x,f.y,(int)x,(int)y,false,side?-gearAngle:gearAngle,0,0,z,cocos2d::Vec2(.5f,.5f),sprite[img],img);
    }
    uiArt(MergeCastleArt::Slot,b);
}
void slotRim(const Box& b) {
    const auto& f=MergeCastleArt::UiFrames[MergeCastleArt::Slot];
    const int cuts[][4]={{54,12,2064,148},{54,560,2064,143},{54,160,446,400},{1690,160,428,400},{845,160,80,400},{1275,160,80,400}};
    for(const auto& c:cuts)artCut(MERGE_REBUILD_UI_IMG+MergeCastleArt::Slot,{c[0],c[1],c[2],c[3]},
        {b.x+(c[0]-f.x)*b.w/f.w,b.y-(c[1]-f.y)*b.h/f.h,c[2]*b.w/f.w,c[3]*b.h/f.h});
}
void drawLever(const Layout& l) {
    Box b=l.lever;bool pulling=finger>=0&&b.has(downX,downY)&&!introActive();
    b.y-=(int)((pulling?20:animation>20?12:0)*l.scale);
    uiArt(MergeCastleArt::Lever,b);
}
void drawBlock(const Block& b,const Box& box,bool ghost=false) {
    int lv=std::max(1,std::min((int)MaxLevel,b.level));
    SetAlpha(ghost?16:32);padArt(lv+1,box);SetAlpha(32);
    icon(b.family,inset(box,std::max(1,(int)(2*DX/640.f))),b.family<Roles?.90f:1.05f,false,b.level,b.crew,b.family<Roles?(int)(6*DX/640.f):0);
}
Box blockBox(const Block& b,const Layout& l) {
    return {l.board.x+b.x*l.cell,l.board.y-b.y*l.cellH,Wide(b)*l.cell,Tall(b)*l.cellH};
}
bool beginSpinLanding(){
    spinLandingPlan=run;spinDrops.clear();
    const auto source=run.tray;
    for(const auto& item:source){
        const auto before=spinLandingPlan.board;
        if(!spinLandingPlan.autoPlace(0)){
            spinDrops.clear();message="결과를 놓을 공간이 부족합니다. 칸을 비워주세요.";messageTime=3;return false;
        }
        Block target=spinLandingPlan.board.back();
        if(before.size()==spinLandingPlan.board.size())for(int i=0;i<(int)before.size();++i){
            const auto& a=before[i];const auto& b=spinLandingPlan.board[i];
            if(a.family!=b.family||a.level!=b.level||a.x!=b.x||a.y!=b.y||a.crew!=b.crew){target=b;break;}
        }
        spinDrops.push_back({item,target});
    }
    if(spinDrops.empty())return false;
    spinFlightFrame=0;return true;
}
void rememberReelSymbols(){
    for(int i=0;i<3;++i){
        if(run.tray.empty()){
            reelSymbols[i]=Block();reelSymbols[i].family=run.families[i];
            // start() has already placed the actual opening results on the board.
            if(introActive()&&i<(int)run.board.size())reelSymbols[i]=run.board[i];
        }
        else if(run.tray.size()==2){
            int match=run.tray[0].level>=run.tray[1].level?0:1;
            reelSymbols[i]=run.tray[i<2?match:1-match];
        }else reelSymbols[i]=run.tray[std::min(i,(int)run.tray.size()-1)];
    }
    hasReelSymbols=true;
}
void drawSpinLanding(const Layout& l){
    if(!spinFlying())return;
    for(int i=0;i<(int)spinDrops.size();++i){
        const float p=std::max(0.f,std::min(1.f,(spinFlightFrame-i*4)/36.f));
        const int reel=spinDrops.size()==1?1:spinDrops.size()==2&&i==1?2:i;
        const auto& drop=spinDrops[i];Box dest=blockBox(drop.target,l),from=slotWindow(l.slot,reel);
        if(p<=0)continue;
        if(p>=1){drawBlock(drop.target,dest);continue;}
        const float ease=1.f-std::pow(1.f-p,3.f);
        int w=(int)(from.w+(dest.w-from.w)*ease),h=(int)(from.h+(dest.h-from.h)*ease);
        int cx=(int)(from.x+from.w*.5f+(dest.x+dest.w*.5f-from.x-from.w*.5f)*ease);
        int cy=(int)(from.y-from.h*.5f+(dest.y-dest.h*.5f-from.y+from.h*.5f)*ease+std::sin(p*3.14159265f)*45*l.scale);
        icon(drop.source.family,{cx-w/2,cy+h/2,w,h},1.f,false,drop.source.level,drop.source.crew);
    }
}
float flightStart(int i) {return 2.05f+i*.22f;}
void drawIntro(const Layout& l) {
    if(!introActive())return;
    float s=l.scale,t=introElapsed;
    SetAlpha(32);
    const Box slot=l.slot;
    if(t<1.9f)label("무료 시작 뽑기",DX/2,slot.y+(int)(17*s),.5f,0xFFF1BD);
    drawSlotFrame(slot);
    for(int i=0;i<3;++i) {
        float stop=1.2f+i*.24f;
        Box reel=slotWindow(slot,i);
        SetSectionClip(reel.x,reel.y,reel.w,reel.h,false);
        int pitch=(int)(108*s),centerY=reel.y-reel.h/2;
        if(t<stop) {
            float distance=t-.375f*t*t/stop;
            int offset=(int)std::fmod(distance*(560+70*i)*s,(float)pitch);
            int index=(int)(t*(18+3*i));
            for(int j=-2;j<=2;++j) {
                int f=pool[(index+j+2+i*7)%pool.size()];
                SetSectionClip(reel.x,reel.y,reel.w,reel.h,false);
                icon(f,{reel.x,centerY+pitch/2+j*pitch-offset,reel.w,pitch},.91f,true);
            }
        } else if(t<flightStart(i)) {
            //릴이 든 사람은 트레이에 떨어질 그 사람이다. 전에는 board[i]
            //의 동료를 가져왔는데, 그 칸은 이 릴과 아무 상관이 없다 -
            //서는 순간 엉뚱한 사람으로 갈렸다.
            icon(run.families[i],{reel.x,centerY+pitch/2,reel.w,pitch},.94f,true,1,
                i<(int)run.board.size()?run.board[i].crew:-1);
        }
        UnSectionClip(false);
    }
    slotRim(slot);SetAlpha(32);
    for(int i=0;i<3&&i<(int)run.board.size();++i) {
        float f=(t-flightStart(i))/.7f;
        if(f<0)continue;
        Box dest=blockBox(run.board[i],l);
        if(f>=1) {
            drawBlock(run.board[i],dest);
            float pulse=std::max(0.f,1-(f-1)*3);
            if(pulse>0) {SetAlpha((int)(32*pulse));MemRectFrameThick(dest.x,dest.y,dest.w,dest.h,0xFFF0A4,std::max(1,(int)(3*s)));SetAlpha(32);}
            continue;
        }
        float ease=1-std::pow(1-f,3.f);
        const Box origin=slotWindow(slot,i);
        float fromX=origin.x+origin.w*.5f,fromY=origin.y-origin.h*.5f;
        int cx=(int)(fromX+(dest.x+dest.w/2.f-fromX)*ease);
        int cy=(int)(fromY+(dest.y-dest.h/2.f-fromY)*ease+std::sin(f*3.14159265f)*60*s);
        int w=(int)(100*s*(1-ease)+dest.w*ease),h=(int)(100*s*(1-ease)+dest.h*ease);
        for(int k=1;k<=3;++k) {
            int px=(int)(cx-(dest.x+dest.w/2.f-fromX)*.018f*k),py=cy-(int)(6*s*k);
            SetAlpha(18/k);MemRect(px,py,std::max(1,(int)(4*s)),std::max(1,(int)(4*s)),0xFFE79A);
        }
        SetAlpha(32);icon(run.board[i].family,{cx-w/2,cy+h/2,w,h},.94f,false,run.board[i].level,run.board[i].crew);
    }
    SetAlpha(32);
}
#include "MergeCastleLobbyRebuild.inc"
//---- 지금 치고 있는 자리 ----
//
//피해는 판이 아니라 **사람에게서** 출발한다. 판에서 날아오면 누가 친
//것인지 안 보인다. 데크에서 한 발 나온 그 자리를 여기 적어 두고,
//날아가는 그림이 그 점에서 시작한다.
int shotFromX=0,shotFromY=0;

//---- 치는 자세 ----
//
//스테이지 전투와 같은 표를 본다(enemyAttackPattern 의 THERE = 원거리
//자세). 자세가 없는 동료는 -1 - 그 자리에서 쉬는 자세로 둔다.
int crewAttackMotion(int npc,int cmf,float t) {
    if(npc<0||cmf<0||cmf>=MAXCMF)return -1;
    const int status=enemyAttackPattern[npc*ATTACKPATTERNTOTALDATASIZE+2+THERE];
    if(status<=0||status>=MAXSTATUS)return -1;
    const signed short* st=cmf_status_data[cmf][status];
    const int cnt=std::max(1,(int)st[0]);
    const int at=std::max(0,std::min(cnt-1,(int)(t*cnt)));
    const int m=st[2+at];
    return (m>=0&&m<cmf_m_cnt[cmf])?m:-1;
}
void drawWorld(const Layout& l,bool combat) {
    const float s=l.scale;
    SetAlpha(32);SetColor(0);grayScale=0;
    castleScrollSeconds+=std::min(.1f,std::max(0.f,cocos2d::Director::getInstance()->getDeltaTime()))*.25f;
    {StageBg::Borrow scroll(StageBg::s_region,castleScrollSeconds);
        castleWheelTravel=DrawCastleLobbyBackground((int)(104*s));}
    drawCastleHull(l);
    //---- 데크의 줄 ----
    //
    //전에는 히어로가 DX*0.57 에 서고 동료가 그 왼쪽으로 늘어섰다. 대포가
    //그 자리에 있어서 줄의 앞머리가 포신에 겹쳐 박혔다.
    //
    //이제 대포 앞(오른쪽)부터가 사람 자리다. 히어로가 맨 앞에 서고 동료가
    //그 뒤로 붙되, 마지막 사람이 포신을 넘지 않도록 간격만 좁힌다.
    const Box gun=castleCannonBox(l);
    const int deckBack=gun.x+gun.w+(int)(12*s);      //대포 바로 앞
    const int hx=std::max(deckBack+(int)(30*s),(int)(DX*.66f));
    const int hy=l.ground,ex=(int)(DX*.85f),ey=l.ground;
    const float deckY=(float)hy;
    SetSectionClip(0,DY,DX,DY-l.board.y,false);
    //히어로는 판의 주인이다. 데크에서 한눈에 찾아야 하므로 동료보다 크다(1.5배).
    float heroZoom=std::max(.35f*s,std::min(.82f*s,(DY-hy-8*s)/80.f))*1.5f;

    //---- 지금 치는 블록 ----
    //
    //차례가 된 블록 하나가 데크의 한 사람과 짝이 된다. 그 사람만 한 발
    //앞으로 나가 치고 제자리로 돌아온다(lunge). 장비 블록은 사람이
    //없으므로 히어로가 대신 휘두른다.
    const Shot* firing=(combat&&run.attacking&&animation>0&&run.nextShot>0
        &&run.nextShot<=(int)run.shots.size())?&run.shots[run.nextShot-1]:NULL;
    const float fireT=firing
        ?1.f-animation/(float)std::min(42,6+6*firing->block.level):0.f;
    const int lunge=firing?(int)(std::sin(fireT*3.14159265f)*22*s):0;
    const bool heroSwing=firing&&firing->block.family>=Sword&&!DefensiveGear(firing->block.family)&&firing->block.family!=Boots;

    shotFromX=hx;shotFromY=hy-(int)(26*s);
    const int heroX=hx+(heroSwing?lunge:0);
    DrawPlayer(&hero,motionData[heroSwing?32+(int)(fireT*31):combat&&run.attacking?32+(ticks%32):0],
        heroX,hy,RIGHT,heroZoom,0,false,true);
    if(firing&&firing->block.family>=Sword)shotFromX=heroX+(int)(18*s);
    //---- 판에 선 동료가 전투 화면에도 선다 ----
    //
    //전에는 계열 표(run.families)에서 대표 한 명을 뽑아 세웠다. 판에
    //무엇을 올렸든 늘 같은 사람이 서 있어서, 칸을 채운 보람이 위에
    //나타나지 않았다.
    //
    //판 위의 동료를 그대로 센다. 같은 사람이 여럿이면 한 번만 세운다 -
    //★ 가 올라도 사람은 하나다.
    {
        int seen[8],shown=0;

        for(int i=0;i<(int)run.board.size()&&shown<8;++i) {
            const Block& b=run.board[i];

            if(b.family>=Roles||b.crew<0||b.crew>=64) continue;

            bool already=false;
            for(int k=0;k<shown;++k) if(seen[k]==b.crew) {already=true;break;}
            if(already) continue;

            seen[shown++]=b.crew;
        }

        //---- 겹치지 않게 ----
        //
        //간격을 숫자로 못박으면 사람마다 폭이 달라 어깨가 겹친다. 그릴
        //때의 실제 폭(cmfMotionImgSize)을 재서 그만큼씩 물러난다.
        //
        //커서는 히어로 어깨 뒤에서 시작해 왼쪽으로 간다. 대포 앞을 넘으면
        //거기서 멈춘다 - 포신에 겹쳐 서느니 안 서는 편이 낫다.
        int cursor=hx-(int)(38*s);
        const int gap=(int)(6*s);

        const int fireCrew=(firing&&firing->block.family<Roles)?firing->block.crew:-1;
        bool fireShown=false;

        for(int k=0;k<shown;++k) {
            const int npc=crewData[seen[k]*CREWDATASIZE+CREWDATA_TYPE];
            const int cmf=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF];

            if(cmf<0||cmf>=MAXCMF) continue;
            if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);

            //동료는 주인공이 아니다. 히어로보다 확실히 작고, 뒤로 갈수록
            //한 번 더 작아져 멀리 있는 것으로 읽힌다.
            const bool mine=(seen[k]==fireCrew);
            float z=std::min(.70f*s,heroZoom*.52f)*(1.0f-k*.05f);
            const int pose=mine?crewAttackMotion(npc,cmf,fireT):-1;
            const int motion=pose>=0?pose:crewPos[npc*5];
            const auto* bound=cmfMotionImgSize[cmf]+motion*4;
            // Keep the first companion visible even on a narrow deck.
            if(k==0)z=std::min(z,std::max(1,cursor-deckBack)/(float)std::max(1,(int)bound[2]));
            const int wide=std::max(1,(int)(bound[2]*z));

            cursor-=wide/2;
            if(cursor-wide/2<deckBack) break;
            const int x=cursor+(mine?lunge:0);

            DrawCmfDetail(cmf,motion,x,(int)deckY,RIGHT,z,0,false);
            cursor-=wide/2+gap;
            if(mine){shotFromX=x+wide/2;shotFromY=(int)deckY-(int)(24*s);fireShown=true;}
        }

        //---- 데크에 못 선 동료 ----
        //
        //판에 아홉 번째가 있으면 줄에는 자리가 없다. 제 차례에만 히어로
        //앞으로 올라와 치고 내려간다 - 안 보이는 사람이 때리면 안 된다.
        if(fireCrew>=0&&!fireShown) {
            const int npc=crewData[fireCrew*CREWDATASIZE+CREWDATA_TYPE];
            const int cmf=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF];

            if(cmf>=0&&cmf<MAXCMF) {
                if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);
                const int x=hx+(int)(34*s)+lunge;
                const int pose=crewAttackMotion(npc,cmf,fireT);

                DrawCmfDetail(cmf,pose>=0?pose:crewPos[npc*5],x,(int)deckY,RIGHT,
                    std::min(.70f*s,heroZoom*.52f),0,false);
                shotFromX=x+(int)(16*s);shotFromY=(int)deckY-(int)(24*s);
            }
        }
    }
    if(combat) {
    int npc=run.wave==9?ENEMY_CASTLE_BOSS1:ENEMY_KNIGHT+run.wave%2;
    int cmf=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF];
    if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);
    const auto* enemyBounds=cmfMotionImgSize[cmf]+crewPos[npc*5]*4;
    const float enemyZoom=std::min((run.wave==9?0.65f:1.35f)*s,std::max(.3f*s,(DY-ey-8*s)/std::max(1,(int)enemyBounds[3])));
    DrawCmfDetail(cmf,crewPos[npc*5],ex,ey,LEFT,enemyZoom,0,false);
    for(int i=0;i<(int)run.summons.size()&&i<3;++i) {
        const Shot& summoned=run.summons[i];
        int crew=summoned.block.crew;
        if(crew<0||crew>=64)continue;
        int skill=crewData[crew*CREWDATASIZE+CREWDATA_SKILL3];
        int kind=SkillKind(skill),x=(int)(DX*(.59f+i*.06f));
        if(kind==SUMMON) {
            int type=SkillSummonEnemy(skill);
            if(type>=0&&type<gTotalEnemy) {
                int c=enemyData[type*ENEMYDATASIZE+ENEMYDATA_CMF];
                if(cmfLoaded[c]!=c)CmfRead(c,c);
                DrawCmfDetail(c,crewPos[type*5],x,l.ground,RIGHT,.35f*s,0,false);
            }
        } else if(kind==SUMMONHERO) {
            OBJECT copy=hero;copy.type=std::max(0,std::min(2,SkillSummonHeroType(skill)));
            DrawPlayer(&copy,motionData[0],x,l.ground,RIGHT,.45f*s,0,false,true);
        } else icon(summoned.block.family,{x-(int)(14*s),l.ground+(int)(35*s),(int)(28*s),(int)(35*s)},.7f,false,summoned.block.level,summoned.block.crew);
    }
    }
    UnSectionClip(false);

}
void close() {
    if(run.attacking) {message="공격 연출이 끝난 뒤 나갈 수 있습니다.";return;}
    save();active=false;option.gameMode=(unsigned char)oldMode;
    picked=-1;finger=-1;systemKey=0;
    is_key_pressed=is_touchkey_pressed=is_key_released=false;
    is_press_finished=is_release_finished=true;
    drawHandle=MD_LOBBY;mustRefresh=true;
}
void tick() {
    ++ticks;++frame;if(flash>0)--flash;
    float dt=std::min(.1f,std::max(.001f,cocos2d::Director::getInstance()->getDeltaTime()));
    heartBlink=std::max(0.f,heartBlink-dt);messageTime=std::max(0.f,messageTime-dt);
    if(robin.heart!=observedHearts) {
        heartDisplay=(int)std::max(0LL,std::min((long long)heartCapacity,heartDisplay+robin.heart-observedHearts));
        observedHearts=robin.heart;
    }
    if(entering()) {
        const float before=entryElapsed;
        entryElapsed=std::min(MergeCastleTransition::Duration,entryElapsed+dt);
        const int count=run.shape.width*run.shape.height;
        for(int i=0;i<count;++i){const float land=MergeCastleTransition::TileLand(i,count);
            if(before<land&&entryElapsed>=land)PlayMusic(M_BUTTON);}
        return;
    }
    if(introActive()) {
        float before=introElapsed;
        introElapsed+=std::min(.1f,std::max(.001f,cocos2d::Director::getInstance()->getDeltaTime()));
        const float phase=std::min(1.f,introElapsed/1.68f);
        gearAngle=450.f*(1.f-std::pow(1.f-phase,3.f));
        for(int i=0;i<3;++i) {
            float stop=1.2f+i*.24f,land=flightStart(i)+.7f;
            if(before<stop&&introElapsed>=stop)PlayMusic(M_ROULETTEUP);
            if(before<land&&introElapsed>=land)PlayMusic(M_POWERUP);
        }
        return;
    }
    if(spinFlying()){
        ++spinFlightFrame;
        for(int i=0;i<(int)spinDrops.size();++i)if(spinFlightFrame==36+i*4)PlayMusic(M_POWERUP);
        if(spinFlightFrame>=48){run=spinLandingPlan;spinFlightFrame=-1;save();}
        return;
    }
    if(animation>0&&!run.attacking){
        const float phase=std::min(1.f,(46-animation)/45.f);
        gearAngle=gearStartAngle+450.f*(1.f-std::pow(1.f-phase,3.f));
    }
    if(animation>0 && --animation==0 && !run.attacking){beginSpinLanding();save();}
    if(!run.attacking)return;
    if(animation>0)return;
    if(run.nextShot<(int)run.shots.size()) {
        run.step();int level=run.shots[run.nextShot-1].block.level;
        animation=std::min(42,6+6*level);
        flash=8;PlayMusic(level>=5?M_POWERUP:M_SWORDHIT);save();return;
    }
    bool killed=run.enemyHp==0;
    long long overkill=std::max(0LL,run.damageDone-run.enemyMax);
    int hearts=run.finish();
    run.setShape(castleShape(run.stage));
    if(hearts)GetItem(ITEM_HEART,false,false,false,hearts,false);
    if(killed) {
        long long gold=run.reward;run.reward=0;
        GetItem(ITEM_GOLD,false,false,false,gold,false);
        message=overkill>0?"오버킬! 다음 웨이브":"처치! 다음 웨이브";
        if(run.wave==0) {
            message="성 클리어! 장비 획득 · 다음 성으로";
            if(!review) {
                int type=ITEM_SWORD+hero.type,lv=std::max(1,std::min(GetEquipMaxLevel(),run.stage+1));
                int detail=MakeItemDetail(type,lv),grade=MakeItemGrade(type,lv,detail);
                GetItem(type,lv,detail,grade,1,0);
            }
        }
        run.enemyHp=run.enemyMax=hpFor(run.stage,run.wave);
    } else message=run.lost?"목숨을 모두 사용했습니다":"적의 반격! 인벤토리를 다시 채우세요.";
    save();
}
void reviewTrace(const char* text) {
    const char* dir=std::getenv("CS_MERGE_REVIEW_PATH");if(!dir)return;
    std::ofstream out(std::string(dir)+"checks.log",std::ios::app);out<<text<<'\n';
}
void reviewCapture(const char* name) {
    const char* dir=std::getenv("CS_MERGE_REVIEW_PATH");if(!dir)return;
    if(reviewCapturePending){reviewCaptureQueue.push_back(name);return;}
    reviewCapturePending=true;
    cocos2d::utils::captureScreen([](bool ok,const std::string& path){
        reviewCapturePending=false;
        reviewTrace(ok?("PASS capture "+path).c_str():"FAIL capture");
    },std::string(dir)+name+".png");
}
void reviewTap(const Box& b) {
    float x=b.x+b.w/2.0f,y=b.y-b.h/2.0f;
    MergeRouletteTouch(0,999,x,y);MergeRouletteTouch(2,999,x,y);
}
void reviewLayout(const Layout& l,const char* name) {
    char line[400];
    std::snprintf(line,sizeof(line),"LAYOUT %s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
        name,l.board.x,l.board.y,l.board.w,l.board.h,l.slot.x,l.slot.y,l.slot.w,l.slot.h,
        l.lever.x,l.lever.y,l.lever.w,l.lever.h,l.heart.x,l.heart.y,l.heart.w,l.heart.h,
        l.spin.x,l.spin.y,l.attack.x,l.attack.y);
    reviewTrace(line);
}
void reviewStep(const Layout& l) {
    if(!review||reviewDone)return;
    if(!reviewCapturePending&&!reviewCaptureQueue.empty()){
        const std::string name=reviewCaptureQueue.front();reviewCaptureQueue.erase(reviewCaptureQueue.begin());
        reviewCapture(name.c_str());
    }
    if(entering()) {
        if(reviewCapturePending)return;
        if(!(entryCaptures&1)&&entryElapsed>.04f){entryCaptures|=1;reviewCapture("00-transition-rooms");}
        else if(!(entryCaptures&2)&&entryElapsed>.45f){entryCaptures|=2;reviewCapture("00-transition-cover");}
        else if(!(entryCaptures&4)&&entryElapsed>1.f){entryCaptures|=4;reviewCapture("00-transition-controls");
            const auto before=run.encode();const auto hearts=robin.heart;
            reviewTap(l.spin);reviewTap(l.attack);
            reviewTrace(run.encode()==before&&robin.heart==hearts?"PASS transition locks inputs without heart cost":"FAIL transition input lock");
        }
        return;
    }
    if(introActive()) {
        if(reviewCapturePending)return;
        if(!(introCaptures&1)&&introElapsed>.3f) {
            introCaptures|=1;
            auto before=run.encode();long long hearts=robin.heart;
            reviewTap(l.spin);reviewTap(l.lever);reviewTap(l.attack);reviewTap(l.exit);
            Box cell={l.board.x,l.board.y,l.cell,l.cellH};reviewTap(cell);
            reviewTrace(active&&run.encode()==before&&robin.heart==hearts?"PASS opening locks all gameplay input":"FAIL opening input lock");
            reviewTrace(run.board.size()==3&&run.tray.empty()&&run.spins==SpinLimit&&robin.heart==20?"PASS three free starters committed once":"FAIL opening reward");
            bool sameStarters=hasReelSymbols&&run.board.size()==3;
            for(int i=0;i<3&&sameStarters;++i)
                sameStarters=reelSymbols[i].family==run.board[i].family&&reelSymbols[i].crew==run.board[i].crew&&reelSymbols[i].level==run.board[i].level;
            reviewTrace(sameStarters?"PASS opening reels match exact grid characters":"FAIL opening character mismatch");
            Run restored;restored.roster=&roster;reviewTrace(restored.decode(before)&&!restored.start(pool)&&restored.encode()==before?"PASS opening reload cannot duplicate starters":"FAIL opening persistence");
            reviewCapture("00-opening-spin");
        }
        if(!(introCaptures&2)&&introElapsed>2.4f) {introCaptures|=2;reviewCapture("00-opening-flight");}
        if(!(introCaptures&4)&&introElapsed>3.2f) {introCaptures|=4;reviewCapture("00-opening-land");}
        return;
    }
    if(reviewCombatTick<0) {
        reviewCombatTick=ticks;
        reviewTrace(introCaptures==7&&run.board.size()==3&&!run.choosing?"PASS opening completes before combat unlocks":"FAIL opening completion");
        bool growth=true;int previous=0;
        for(int c=0;c<10;++c) {
            Shape shape=castleShape(c);int count=0;
            for(int y=0;y<shape.height;++y)for(int x=0;x<shape.width;++x)count+=shape.contains(x,y);
            Run check=run;
            growth=growth&&shape.valid()&&count==castleGridCellCnt[c]&&count==shape.width*shape.height&&count>=previous&&check.setShape(shape)&&check.board.size()==3;
            previous=count;
        }
        reviewTrace(growth&&previous==48?"PASS castle grids grow from 24 to 48 playable cells":"FAIL castle grid growth");
    }
    const int t=ticks-reviewCombatTick;
    if(t==9)MergeRouletteSetHeartCapacity(5);
    if(t==10) {reviewLayout(l,"01-families");reviewCapture("01-families");}
    if(t==16)MergeRouletteSetHeartCapacity(20);
    if(t==30||t==140||t==250||t==360) {
        long long before=robin.heart;int life=run.lives;
        if(t==140) {
            float x=l.lever.x+l.lever.w/2.f,y=l.lever.y-l.lever.h/2.f;
            MergeRouletteTouch(0,999,x,y);MergeRouletteTouch(1,999,x,y-24*l.scale);MergeRouletteTouch(2,999,x,y-36*l.scale);
        } else reviewTap(l.spin);
        reviewTrace(robin.heart==before-1&&run.lives==life&&!run.tray.empty()?"PASS spin costs one heart without enemy turn":"FAIL spin");
        if(t==140)reviewTrace(robin.heart==before-1&&!run.tray.empty()?"PASS right lever pull spins once":"FAIL lever pull");
    }
    if(t==32) {
        long long balance=robin.heart;reviewTap(l.spin);reviewTap(l.attack);
        reviewTrace(heartBlink>0&&spentHeart==heartDisplay&&robin.heart==balance?"PASS one heart blinks and repeat input cannot charge twice":"FAIL heart animation");
        reviewCapture("06-heart-spend");
        reviewTrace(gearAngle>gearStartAngle&&gearAngle<gearStartAngle+450.f?"PASS slot gears rotate during spin":"FAIL slot gear rotation");
    }
    if(t==38)reviewCapture("07-gears-turning");
    if(t==58)reviewCapture("08-gears-slowing");
    if(t==90)reviewTrace(std::abs(gearAngle-gearStartAngle-450.f)<.01f?"PASS slot gears decelerate and stop with reels":"FAIL slot gear stop");
    if(t==130||t==240||t==350||t==460) {
        reviewTrace(run.tray.empty()&&!run.board.empty()&&!spinFlying()?"PASS spin results automatically fly into inventory":"FAIL automatic spin landing");
        bool separate=run.board.size()==(size_t)(6+3*((t-130)/110));
        for(const auto& b:run.board)separate=separate&&b.level==1;
        reviewTrace(separate?"PASS all three reel symbols land separately without automatic merge":"FAIL reel symbols merged automatically");
    }
    if(t==85){
        const auto before=run.encode();const auto hearts=robin.heart;
        reviewTap(l.spin);reviewTap(l.attack);reviewTap(l.exit);
        reviewTrace(spinFlying()&&run.encode()==before&&robin.heart==hearts?"PASS landing locks input without extra heart cost":"FAIL landing input lock");
        reviewCapture("09-spin-flight");
    }
    if(t==470) {
        Run restored;
        reviewTrace(restored.decode(run.encode())&&restored.encode()==run.encode()?"PASS run roundtrip":"FAIL run roundtrip");
        reviewLayout(l,"02-inventory");reviewCapture("02-inventory");
    }
    if(t==465&&!run.board.empty()) {
        Block moving=run.board[0];bool checked=false;
        for(int y=run.shape.height-Tall(moving);y>=0&&!checked;--y)for(int x=run.shape.width-Wide(moving);x>=0&&!checked;--x) {
            if(x==moving.x&&y==moving.y)continue;
            Block target=moving;target.x=x;target.y=y;if(!run.fits(target,0))continue;
            Box a=blockBox(moving,l),b=blockBox(target,l);
            float fx=a.x+l.cell*.3f,fy=a.y-l.cellH*.3f,tx=b.x+l.cell*.3f,ty=b.y-l.cellH*.3f;
            MergeRouletteTouch(0,999,fx,fy);MergeRouletteTouch(1,999,tx,ty);MergeRouletteTouch(2,999,tx,ty);
            reviewTrace(run.board[0].x==x&&run.board[0].y==y?"PASS free drag through input":"FAIL drag");checked=true;
        }
        std::string before=run.encode();Box b=blockBox(run.board[0],l);
        MergeRouletteTouch(0,999,b.x+l.cell*.3f,b.y-l.cellH*.3f);
        MergeRouletteTouch(1,999,0,0);MergeRouletteTouch(3,999,0,0);
        reviewTrace(picked<0&&finger<0&&run.encode()==before?"PASS cancelled drag preserves block":"FAIL cancelled drag");
    }
    if(t==490) {
        reviewAttackGear=gearAngle;
        reviewAttackBlocks=run.board;
        long long before=robin.heart;reviewTap(l.attack);
        reviewTrace(run.attacking&&robin.heart==before-1?"PASS attack costs one heart":"FAIL attack");
    }
    if(t==508){reviewCapture("03-launch");reviewTrace(gearAngle==reviewAttackGear?"PASS slot gears stay still during attack":"FAIL attack moved slot gears");}
    if(t==750) {
        reviewCapture("04-exchange");
        bool retained=run.board.size()==reviewAttackBlocks.size();
        for(int i=0;i<(int)run.board.size()&&retained;++i) {
            const Block& a=run.board[i];const Block& b=reviewAttackBlocks[i];
            retained=a.family==b.family&&a.level==b.level&&a.x==b.x&&a.y==b.y;
        }
        reviewTrace(!run.attacking&&retained&&run.spins>=10?"PASS sequential actions preserve every board element":"FAIL retained inventory");
    }
    if(t==755) {run.stage=4;run.setShape(castleShape(run.stage));run.enemyHp=run.enemyMax=hpFor(run.stage,0);}
    if(t==756){reviewLayout(l,"10-castle5-nine-columns");reviewCapture("10-castle5-nine-columns");
        reviewTrace(l.cell==64&&l.cellH==64&&l.board.w==576?"PASS nine-column castle retains exact 64px cells":"FAIL nine-column cell size");}
    if(t==760) {run.stage=9;run.setShape(castleShape(run.stage));run.enemyHp=run.enemyMax=hpFor(run.stage,0);}
    if(t>=762&&!reviewCapturePending&&!reviewFinalCapture) {
        reviewFinalCapture=true;reviewLayout(l,"05-castle10");reviewCapture("05-castle10");
    } else if(t>=763&&reviewFinalCapture&&!reviewCapturePending&&reviewCaptureQueue.empty()) {
        Run current=run;
        run=Run();run.roster=&roster;run.choosing=false;run.families[0]=Sword;run.families[1]=Armor;run.families[2]=Boots;
        run.setShape(castleShape(0));
        for(int i=0;i<22;++i) {Block b;b.family=Sword;b.x=i%run.shape.width;b.y=i/run.shape.width;run.board.push_back(b);}
        Layout full=layout();long long balance=robin.heart;auto blocked=run.encode();reviewTap(full.spin);reviewTap(full.lever);
        reviewTrace(run.freeCells()==2&&run.encode()==blocked&&robin.heart==balance&&messageTime>0?"PASS fewer than three empty cells logs warning without charging":"FAIL full board guard");
        Box source=blockBox(run.board[0],full);float x=source.x+full.cell/2.f,y=source.y-full.cellH/2.f;
        float tx=DX-47*full.scale,ty=full.slot.y-35*full.scale;
        MergeRouletteTouch(0,999,x,y);MergeRouletteTouch(1,999,tx,ty);MergeRouletteTouch(2,999,tx,ty);
        reviewTrace(run.encode()==blocked&&robin.heart==balance?"PASS dragging outside board preserves block without discard":"FAIL removed discard target");
        run=Run();run.roster=&roster;run.choosing=false;run.setShape(castleShape(0));
        for(int y=0;y<4;++y)for(int x=0;x<6;++x){
            Block b;b.family=Armor;b.x=x;b.y=y;run.board.push_back(b);
        }
        const auto fullBoard=run.board;
        run.board[0].family=run.board[1].family=Sword;
        const auto crowdedMerge=run.encode();
        Layout mergeLayout=layout();Box club=blockBox(run.board[0],mergeLayout),onto=blockBox(run.board[1],mergeLayout);
        const float ax=club.x+club.w*.5f,ay=club.y-club.h*.5f,bx=onto.x+onto.w+2,by=onto.y-onto.h*.5f;
        MergeRouletteTouch(0,999,ax,ay);MergeRouletteTouch(1,999,bx,by);MergeRouletteTouch(2,999,bx,by);
        reviewTrace(run.encode()==crowdedMerge&&messageTime>0&&robin.heart==balance?
            "PASS expanded merge waits for space without changing either piece":"FAIL blocked expanded merge");
        run.board.erase(run.board.begin()+run.at(2,0));
        MergeRouletteTouch(0,999,ax,ay);MergeRouletteTouch(1,999,bx,by);MergeRouletteTouch(2,999,bx,by);
        const int merged=run.at(1,0);
        reviewTrace(merged>=0&&run.board.size()==22&&run.board[merged].level==2&&run.freeCells()==1&&
            blockBox(run.board[merged],mergeLayout).w==128&&run.at(2,0)==merged&&robin.heart==balance?
            "PASS dragging clubs merges into expanded equipment footprint without heart cost":"FAIL expanded club drag merge");
        run.board=fullBoard;
        run.board.erase(run.board.begin()+run.at(5,3));
        run.board.erase(run.board.begin()+run.at(4,3));
        Block large;large.family=Sword;large.level=3;run.tray.push_back(large);
        const auto blockedHand=run.encode();
        const bool heldResult=!beginSpinLanding()&&run.encode()==blockedHand;
        Layout tight=layout();const int index=run.at(3,3);Box remove=blockBox(run.board[index],tight);
        reviewTap(tight.attack);
        const bool noAttack=!run.attacking&&robin.heart==balance;
        run.board.erase(run.board.begin()+index); // Fixture: newly available space.
        beginSpinLanding();
        reviewTrace(heldResult&&noAttack&&spinFlying()&&spinLandingPlan.tray.empty()&&robin.heart==balance?
            "PASS large result waits safely then flies automatically when space is freed":"FAIL large result recovery");
        spinFlightFrame=-1;spinDrops.clear();
        run=current;
        const bool pendingSpin=run.spin();
        const std::string pending=run.encode();
        const bool planned=beginSpinLanding();
        const std::string plannedResult=spinLandingPlan.encode();
        Run reloaded;reloaded.roster=&roster;
        const bool decoded=reloaded.decode(pending);
        run=reloaded;const bool replanned=beginSpinLanding();
        reviewTrace(pendingSpin&&planned&&decoded&&replanned&&run.encode()==pending&&spinLandingPlan.encode()==plannedResult?
            "PASS pending results resume with identical landing and no duplicate reward":"FAIL pending result resume");
        run=current;spinFlightFrame=-1;spinDrops.clear();
        std::string stored=run.encode();
        std::memset(robin.mergeRouletteRun,0,sizeof(robin.mergeRouletteRun));
        std::memcpy(robin.mergeRouletteRun,stored.data(),stored.size());robin.mergeRouletteHero=curHero;
        close();MergeRouletteBegin(true);
        reviewTrace(!introActive()&&run.encode()==stored?"PASS explicit continue preserves run without granting starters":"FAIL continue entry");
        close();MergeRouletteBegin(false);
        reviewTrace(introActive()&&run.board.size()==3&&run.spins==SpinLimit?"PASS new battle always replays three-starter intro":"FAIL fresh entry intro");
        reviewDone=true;reviewTrace("DONE");
    }
}
}

bool MergeRouletteActive() {return active;}
bool MergeRouletteOriginalPreview(int castle,int x,int top,int width,int height){
    if(castle!=0)return false;
    const float z=std::min(width/OriginalCastle::W,height/OriginalCastle::H);
    const float ox=x+(width-OriginalCastle::W*z)*.5f,oy=top-height;
    const int img=MERGE_REBUILD_ROOMS_IMG;if(!sprite[img])LoadImg(img);
    if(sprite[img]){
        const auto size=sprite[img]->getTexture()->getContentSizeInPixels();const auto holes=OriginalCastle::rooms();
        for(int i=0;i<5;++i){const auto& p=holes[i];float w=(p[1].x-p[0].x)*z,h=(p[2].y-p[0].y)*z;
            const auto f=MergeCastleTransition::RoomFrame(i,robin.castleProgress.rooms[0][i],(int)size.width,(int)size.height);
            const float rz=std::max(w/f.w,h/f.h);int sw=std::min(f.w,(int)(w/rz)),sh=std::min(f.h,(int)(h/rz));
            DrawImageScale(sw,sh,f.x+(f.w-sw)/2,f.y+f.h-sh,(int)(ox+p[0].x*z),(int)(oy+(OriginalCastle::H-p[0].y)*z),false,0,0,0,0,rz,rz,sprite[img],img);
        }
    }
    for(int kind:{0,1,2,3,4,6,7,8})OriginalCastle::draw(kind,0,0,z,ox,oy);
    return true;
}
void MergeRouletteSetHeartCapacity(int capacity) {heartCapacity=std::max(5,std::min(20,capacity));heartDisplay=(int)std::min((long long)heartCapacity,robin.heart);}
void MergeRouletteBegin(bool resume) {
    if(active)return;
    review=std::getenv("CS_MERGE_REVIEW")!=nullptr;
    oldMode=option.gameMode;option.gameMode=TURNRPG;
    configure();run=Run();run.roster=&roster;run.rng=(unsigned)MC_knlCurrentTimeStamp()|1;
    run.selected=pool.front();run.stage=std::max(0,(int)robin.castle);
    run.enemyHp=run.enemyMax=hpFor(run.stage,0);
    run.maxLives=run.lives=std::max(3,std::min(10,3+(int)hero.equip[EQUIP_ARMOR].grade));
    if(resume) {
        Run restored;restored.roster=&roster;
        // v6 전 세이브는 읽지 않는다(계열·동료 체계가 다르다) — 새 런.
        if(robin.mergeRouletteHero==curHero&&restored.decode(robin.mergeRouletteRun)) {
            bool owned=true;for(int f:restored.families)if(std::find(pool.begin(),pool.end(),f)==pool.end())owned=false;
            if(owned)run=restored;
        }
    } else if(review) {robin.heart=20;run.rng=12345;}
    run.setShape(castleShape(run.stage));
    bool starting=run.choosing&&run.start(pool,treeWeights);
    entryElapsed=0.f;entryCaptures=0;
    introElapsed=starting?0.f:-1.f;introCaptures=0;reviewCombatTick=-1;
    reviewCapturePending=reviewFinalCapture=false;
    ticks=animation=0;gearAngle=gearStartAngle=0;picked=finger=-1;message="";
    spinFlightFrame=-1;spinDrops.clear();
    rememberReelSymbols();
    if(resume&&!starting&&!run.tray.empty())beginSpinLanding();
    observedHearts=robin.heart;heartDisplay=(int)std::min((long long)heartCapacity,robin.heart);heartBlink=messageTime=0;spentHeart=-1;
    active=true;drawHandle=MD_PLAY;keyHandle=MK_PLAY;curMenu=MENU_PLAY;
    autoPlay=false;autoFrame=-1;touchDisable=false;mustRefresh=true;
    if(!run.choosing)save();
}
bool MergeRouletteLobbySceneDraw() {
    static bool needsConfigure=true;
    if(popUpCnt>0||LoadoutOpen()){needsConfigure=true;return false;}
    static int preparedHero=-1,preparedCastle=-1;
    if(needsConfigure||preparedHero!=curHero||preparedCastle!=robin.castle){configure();preparedHero=curHero;preparedCastle=robin.castle;needsConfigure=false;}
    run.stage=std::max(0,std::min(9,(int)robin.castle));
    run.setShape(castleShape(run.stage));
    ResetRectPoint();SetAlpha(32);SetColor(0);grayScale=0;
    Layout l=layout();drawWorld(l,false);drawLobbyControls(l,0,true);
    mustRefresh=true;++frame;return true;
}
void MergeRouletteLobbyDraw() {}
void MergeRouletteDraw() {
    // Isolated capture reviews hold simulation until asynchronous PNG writing
    // completes. Fixed-tick checks cannot be skipped or captured in a later state.
    const bool holdReview=review&&reviewCapturePending;
    if(!holdReview)tick();ResetRectPoint();mustRefresh=true;
    if(review&&std::getenv("CS_MERGE_ORIGINAL_REVIEW")){
        static int sample=0,hold=0;run.stage=0;run.setShape(castleShape(0));
        if(sample==0)OriginalCastle::draw(9);
        else{Layout l=layout();drawWorld(l,false);drawLobbyControls(l);}
        if(!reviewCapturePending&&++hold>5&&sample<2){reviewCapture(sample==0?"original-uniform-reference":"original-live-lobby");++sample;hold=0;if(sample==2){
            bool uniform=true;for(int c=1;c<10;++c){run.stage=c;run.setShape(castleShape(c));Layout test=layout();const auto m=castleMap(test,c);
                const float z=(m.dx[3]-m.dx[0])/(m.sx[3]-m.sx[0]);for(int i=0;i<3;++i)uniform=uniform&&std::abs((m.dy[i+1]-m.dy[i])/(m.sy[i]-m.sy[i+1])-z)<.00001f;
                uniform=uniform&&test.cell==64&&test.cellH==64;}
            run.stage=0;run.setShape(castleShape(0));reviewTrace(uniform?"PASS all ten castles preserve uniform art scale and 64px cells":"FAIL castle aspect ratio");reviewTrace("DONE original reference review");}}
        return;
    }
    if(review&&std::getenv("CS_MERGE_ROOM_REVIEW")) {
        static int sample=0,hold=0;
        const int c=sample>=60?0:sample/6,level=sample>=60?0:sample%6;
        const auto saved=robin.castleProgress;const int savedCastle=robin.castle;
        robin.castle=c;run.stage=c;run.setShape(castleShape(c));
        for(int i=0;i<5;++i)robin.castleProgress.rooms[c][i]=(unsigned char)level;
        if(sample>=60)robin.castleProgress.rooms[c][4]=5;
        Layout l=layout();drawWorld(l,false);drawLobbyControls(l);
        robin.castleProgress=saved;robin.castle=savedCastle;
        if(!reviewCapturePending&&++hold>4&&sample<61){
            char name[80];std::snprintf(name,sizeof(name),sample>=60?"room-independent-castle-%02d-level-%d":"room-castle-%02d-level-%d",c+1,level);reviewCapture(name);
            hold=0;++sample;if(sample==61)reviewTrace("DONE modular facility review");
        }
        return;
    }
    Layout l=layout();float s=l.scale;char text[160];
    const Layout fixed=layout();
    drawWorld(fixed,true);
    if(entering()){
        drawLobbyControls(fixed,MergeCastleTransition::LobbyExit(entryElapsed));
        const int controlDrop=(int)((1-MergeCastleTransition::ControlsEnter(entryElapsed))*300*s);
        l.slot.y-=controlDrop;l.lever.y-=controlDrop;l.heart.y-=controlDrop;
        l.spin.y-=controlDrop;l.attack.y-=controlDrop;
    }
    const int hx=(int)(DX*.57f),ex=(int)(DX*.85f),ey=l.ground;
    std::snprintf(text,sizeof(text),"%d성 · 웨이브 %d/10",run.stage+1,run.wave+1);
    label(text,DX/2,DY-(int)(17*s),0.55f);
    // Readable unit plates directly beneath the battle, separate from the board title.
    //---- 패의 자리 ----
    //
    //히어로 발밑에 붙어 다니면 사람과 숫자가 서로를 가린다. 화면을 성
    //가운데로 반 가른 뒤, 왼쪽 절반의 절반을 아군이, 오른쪽 절반의
    //절반을 적이 쓴다 - 둘이 같은 폭으로 마주 본다.
    const int plateW=DX/4,plateH=(int)(52*s);
    Box allyPlate={DX/4-plateW/2,l.ground-(int)(4*s),plateW,plateH};
    Box enemyPlate={DX*3/4-plateW/2,l.ground-(int)(4*s),plateW,plateH};
    //방어는 갑옷 블록이 주는 보호 횟수다. 공격 중이면 남은 몫을, 배치
    //중이면 "지금 공격하면 받을" 몫을 보여 준다.
    const int guard=run.attacking?run.effects.protect:run.forecast(stats).protect;
    unitPlate(allyPlate,run.lives,run.maxLives,guard,0x37433B,0x406D39,false);
    unitPlate(enemyPlate,run.enemyHp,run.enemyMax,0,0x493444,0xAA343E,flash!=0);
    button(l.exit,"나가기",nullptr,0x25304A,!run.attacking);
    // No backing board: individual 64px tiles cover the rooms themselves.
    for(int row=0;row<run.shape.height;++row)for(int col=0;col<run.shape.width;++col)
        if(run.shape.contains(col,row)){
            Box tile={l.board.x+col*l.cell,l.board.y-row*l.cellH,l.cell,l.cellH};
            const int index=row*run.shape.width+col,count=run.shape.width*run.shape.height;
            float angle=0;
            if(entering()){
                if(entryElapsed<MergeCastleTransition::TileLaunch(index,count))continue;
                const float p=MergeCastleTransition::TileProgress(entryElapsed,index,count);
                const float q=1-std::pow(1-p,2.f);
                // Use the moving housing's actual center, shared by every shot.
                const float cx=l.slot.x+l.slot.w*.5f,cy=l.slot.y-l.slot.h*.5f;
                tile.x=(int)(cx-l.cell*.5f+(tile.x-cx+l.cell*.5f)*q);
                tile.y=(int)(cy+l.cellH*.5f+(tile.y-cy-l.cellH*.5f)*q+std::sin(p*3.14159265f)*32*s);
                angle=(index%2?1.f:-1.f)*360.f*(1-p);
                const float age=entryElapsed-MergeCastleTransition::TileLand(index,count);
                if(age>=0&&age<.09f)tile.y+=(int)(std::sin(age/.09f*3.14159265f)*4*s);
            }
            padArt((row+col)%2,tile,angle);
        }
    long long predicted=run.preview(stats);
    for(int i=0;i<(int)run.board.size();++i) {
        if(introActive()&&i<3)continue;
        if(picked==i&&!pickedTray)continue;
        drawBlock(run.board[i],blockBox(run.board[i],l));
    }

    //---- 막 합쳐진 자리 ----
    //
    //모델이 번호를 올려 두면(run.mergeSeq) 그 자리에서 테두리가 한 번
    //부풀었다 가라앉는다. 피해를 주는 연출이 아니므로 판을 멈추지 않는다.
    if(run.mergeSeq!=mergeSeenSeq) {
        mergeSeenSeq=run.mergeSeq;
        mergeFlash=MERGE_FLASH_FRAMES;
        mergeShownLevel=run.mergeLevel;

        Block at;at.family=0;at.level=1;at.x=run.mergeX;at.y=run.mergeY;
        mergeBox=blockBox(at,l);
        mergeBox.w=run.mergeW*l.cell;
        mergeBox.h=run.mergeH*l.cellH;
    }
    if(mergeFlash>0) {
        const float t=mergeFlash/(float)MERGE_FLASH_FRAMES;   //1 -> 0
        const int grow=(int)(t*10*s);
        const int thick=std::max(1,(int)((1+t*3)*s));

        SetAlpha((int)(ALPHA_MAX*t));
        MemRectFrameThick(mergeBox.x-grow,mergeBox.y+grow,
            mergeBox.w+grow*2,mergeBox.h+grow*2,0xFFE99E,thick);
        SetAlpha(ALPHA_MAX);

        //가운데에 ★ 를 하나 띄운다. 몇 단이 됐는지가 숫자 없이 읽힌다.
        if(mergeShownLevel>0) {
            const float z=(.6f+t*.5f)*s;
            DrawIcon(ICON_STAR,mergeBox.x+mergeBox.w/2-(int)(8*z),
                mergeBox.y-mergeBox.h/2+(int)(8*z),z,false,false,false,true);
        }
        --mergeFlash;
    }
    if(run.attacking&&run.nextShot>0&&animation>0) {
        const Shot& shot=run.shots[run.nextShot-1];Box from=blockBox(shot.block,l);
        int lv=shot.block.level,duration=std::min(42,6+6*lv);
        float t=1-animation/(float)duration;

        //차례가 된 칸은 판에서 테두리로 밝힌다 - 누가 치는 중인지 판에서도 읽힌다.
        MemRectFrameThick(from.x,from.y,from.w,from.h,0xFFE99E,std::max(1,(int)(3*s)));

        //---- 피해는 사람에게서 나간다 ----
        //
        //데크에서 치고 있는 그 사람의 자리(shotFromX/Y)에서 출발한다.
        //방어·보조 장비는 히어로 위로 떠오른다.
        const bool guard=DefensiveGear(shot.block.family)||shot.block.family==Boots;
        const int toX=guard?shotFromX:ex,toY=guard?(int)(ey+105*s):(int)(ey+45*s);
        int size=(int)((1-t)*28*s+t*32*s);
        Box flying={(int)((1-t)*(shotFromX-size/2)+t*(toX-size/2)),
            (int)((1-t)*shotFromY+t*toY),size,size};
        icon(shot.block.family,flying,0.9f,false,shot.block.level,shot.block.crew);
        std::snprintf(text,sizeof(text),"%lld DAMAGE · %d HIT",run.damageDone,run.nextShot);
        label(text,ex,ey+(int)(65*s),0.6f,0xFFD25A);
        if(lv>=5) {
            label("궁극기!",DX/2,l.arenaBottom+(int)(50*s),1.1f,0xFFD25A);
            if(animation>duration/2) {
                Box cutin={0,(int)(DY*.70f),DX,(int)(140*s)};
                panel(cutin,0x202033,0xE29542);
                icon(shot.block.family,{DX/5,cutin.y,(int)(135*s),cutin.h},.95f,false,lv,shot.block.crew);
                label(treeName(shot.block.family),DX*2/3,cutin.y-(int)(40*s),1.0f,0xFFD36A);
                std::snprintf(text,sizeof(text),"★%d · 궁극기",lv);
                label(text,DX*2/3,cutin.y-(int)(90*s),.7f);
            }
        }
    }
    // The reels scroll inside the rounded housing and settle left-to-right.
    if(entering()||!introActive()){
    drawSlotFrame(l.slot);
    for(int i=0;i<3;++i) {
        int pad=std::max(1,(int)(12*s));
        Box window=slotWindow(l.slot,i);
        bool held=!run.tray.empty()&&i<(int)run.tray.size();
        if(spinFlying()&&spinFlightFrame>i*4)continue;
        const Block symbol=hasReelSymbols?reelSymbols[i]:Block();
        int f=hasReelSymbols?symbol.family:held?run.tray[i].family:run.families[i];
        int lv=hasReelSymbols?symbol.level:held?run.tray[i].level:1,crew=hasReelSymbols?symbol.crew:held?run.tray[i].crew:-1;
        const float phase=std::min(1.f,(45-animation)/(float)(33+6*i));
        if(animation>0&&!run.attacking&&phase<1.f){
            //---- 돌다가 선다 ----
            //
            //마지막 한 바퀴를 지나 조금 넘어갔다가 되돌아온다. 그냥 멈추면
            //"바뀌었다" 로만 보이고 슬롯머신으로 안 읽힌다.
            const int pitch=window.h;
            const float ease=1.f-std::pow(1.f-phase,3.f);
            const float over=std::sin(phase*3.14159265f)*(1.f-phase)*REEL_OVERSHOOT*s;
            const float distance=6*pitch*ease+over;
            const int offset=(int)std::fmod(distance,(float)pitch),turn=(int)(distance/pitch);
            for(int j=-1;j<=1;++j){
                Box symbol=window;symbol.y+=j*pitch-offset;
                SetSectionClip(window.x,window.y,window.w,window.h,false);
                //지나가는 칸의 동료까지 바꿔 가며 보여 주면, 서는 순간
                //사람이 한 번 깜빡이며 갈린다. 설 자리의 계열이면 설 사람을
                //미리 들고 돈다.
                const int rollFamily=run.families[(turn+j+6+i)%3];
                icon(rollFamily,symbol,1.f,true,rollFamily==f?lv:1,
                    rollFamily==f?crew:-1);
            }
        }else{
            SetSectionClip(window.x,window.y,window.w,window.h,false);
            icon(f,window,1.f,true,lv,crew);

            //선 직후 한 번 번쩍인다. 어느 줄이 방금 섰는지가 눈에 걸린다.
            if(animation>0&&!run.attacking) {
                const int left=std::max(0,(int)(REEL_STOP_FLASH-(45-animation)+(33+6*i)));
                if(left>0) {
                    SetAlpha(ALPHA_MAX*left/REEL_STOP_FLASH);
                    MemRectFrameThick(window.x,window.y,window.w,window.h,
                        0xFFE99E,std::max(1,(int)(2*s)));
                    SetAlpha(ALPHA_MAX);
                }
            }
        }
        UnSectionClip(false);
    }
    slotRim(l.slot);
    }
    drawLever(l);
    mergeGoldFrame(l.heart,0x382C31,0x201B25);
    for(int side=0;side<2;++side){Box bolt={l.heart.x+(int)((side?l.heart.w/s-14:6)*s),l.heart.y-l.heart.h/2+(int)(4*s),(int)(8*s),(int)(8*s)};
        bevel(bolt,0xD8D9E4,(int)(2*s));bevel(inset(bolt,std::max(1,(int)s)),0x7B8294,(int)s);}
    int cols=heartCapacity>10?10:heartCapacity;
    int heartSize=(int)(22*s),pitch=(int)(27*s),x0=DX/2-(cols*pitch-(int)(5*s))/2;
    int rows=(heartCapacity+cols-1)/cols;
    int heartTop=l.heart.y-(int)(9*s);
    for(int i=0;i<heartCapacity;++i) {
        bool filled=i<heartDisplay;
        if(i==spentHeart&&heartBlink>0)filled=((int)(heartBlink/.09f)%2)==0;
        heart(x0+(i%cols)*pitch,heartTop-(i/cols)*(int)(23*s),heartSize,filled);
    }
    if(run.lost) {
        button(l.spin,"다시 도전","새 런 시작",0x24578D);button(l.attack,"로비로",nullptr,0x975028);
    } else {
        bool ready=!entering()&&!introActive()&&!spinFlying()&&!run.attacking&&animation==0;
        choice(l.spin,false,ready&&run.canSpin()&&robin.heart>0);
        choice(l.attack,true,ready&&run.tray.empty()&&!run.board.empty()&&robin.heart>0);
        if(ready&&!run.board.empty()&&predicted>=run.enemyHp)
            MemRectFrameThick(l.attack.x,l.attack.y,l.attack.w,l.attack.h,0xFFE36A,std::max(1,(int)(3*s)));
        Box orBadge={DX/2-(int)(21*s),l.spin.y-l.spin.h/2+(int)(14*s),(int)(42*s),(int)(28*s)};
        bevel(orBadge,0x080E20,(int)(6*s));bevel(inset(orBadge,std::max(1,(int)(2*s))),0xF6CE68,(int)(5*s));
        bevel(inset(orBadge,std::max(2,(int)(4*s))),0x26303D,(int)(3*s));
        label("OR",DX/2,orBadge.y-(int)(4*s),.82f,0xFFF0B0);
        // Spin budget is a rule hint, not a slot-machine counter.
        if(run.spins==0&&run.tray.empty())label("이번 적립 종료 · 공격하세요",DX/2,DY-(int)(45*s),0.46f,0xFFD26A);
    }
    if(picked>=0) {
        auto& src=pickedTray?run.tray:run.board;
        if(picked<(int)src.size()) {
            Block b=src[picked];int x=(int)((pointerX-l.board.x)/l.cell)-pickCellX;
            int y=(int)((l.board.y-pointerY)/l.cellH)-pickCellY;
            b.x=x;b.y=y;Box box=blockBox(b,l);
            bool valid=run.fits(b,pickedTray?-1:picked);
            int target=run.at(x,y);
            if(target>=0&&!(target==picked&&!pickedTray)) {
                Block merged;
                if(run.mergedPreview(target,b,pickedTray?-1:picked,merged)){valid=true;box=blockBox(merged,l);}
                else valid=false;
            }
            MemRectFrameThick(box.x,box.y,box.w,box.h,valid?0x58DB9C:0xF35B63,(int)(3*s));
            //---- 손에 든 것도 판에 놓인 그대로 ----
            //
            //한 칸짜리로 줄여 들면 집는 순간 물건이 바뀐 것처럼 보인다.
            //판에서 쓰던 크기·그림 그대로, 쥔 칸만큼 어긋나게 든다.
            Box held={(int)pointerX-pickCellX*l.cell-l.cell/2,
                (int)pointerY+pickCellY*l.cellH+l.cellH/2,
                Wide(b)*l.cell,Tall(b)*l.cellH};
            drawBlock(b,held);
        }
    }
    if(messageTime>0&&!message.empty()) {
        Box toast={(int)(90*s),l.arenaBottom+(int)(53*s),(int)(460*s),(int)(48*s)};
        panel(toast,0x352332,0xDD957B);
        label(message.c_str(),DX/2,toast.y-(int)(6*s),.59f,0xFFE6C0);
        if(run.freeCells()<3)label("같은 블록을 합쳐 칸을 확보하세요",DX/2,toast.y-(int)(28*s),.49f);
    }
    if(messageTime<=0&&!run.choosing&&!message.empty()&&(message.find("없")!=std::string::npos||message.find("부족")!=std::string::npos))
        label(message.c_str(),DX/2,DY-(int)(45*s),0.48f);
    drawSpinLanding(l);
    if(!entering())drawIntro(l);
    if(!holdReview)reviewStep(l);
}

bool MergeRouletteTouch(int phase,int id,float x,float y) {
    if(!active) {
        if(phase==0&&drawHandle==MD_LOBBY&&popUpCnt==0&&!LoadoutOpen()) {
            float s=DX/640.0f;
            Layout l=layout();Box b=lobbyStart(l);
            if(b.has(x,y)) {MergeRouletteBegin();return true;}
            Box keep=lobbyContinue(l);
            if(keep.has(x,y)&&robin.mergeRouletteRun[0]&&robin.mergeRouletteHero==curHero) {MergeRouletteBegin(true);return true;}
            for(int i=0;i<5;++i)if(roomBox(l,i).has(x,y)){
                CastleMenuFocusFacility(i);systemKey=AVK_POPUP_CASTLEMENU;return true;
            }
        }
        return false;
    }
    if(entering()||introActive()||spinFlying()) {picked=finger=-1;return true;}
    if(phase==3) {if(finger==id){picked=-1;finger=-1;}return true;}
    if(phase==0) {
        if(finger>=0)return true;
        finger=id;downX=pointerX=x;downY=pointerY=y;picked=-1;
        if(!run.choosing&&!run.attacking&&!run.lost&&animation==0) {
            Layout l=layout();
            if(l.board.has(x,y)) {
                int cx=(int)(x-l.board.x)/l.cell,cy=(int)(l.board.y-y)/l.cellH;
                picked=run.at(cx,cy);pickedTray=false;
                if(picked>=0){pickCellX=cx-run.board[picked].x;pickCellY=cy-run.board[picked].y;}
            } else if(l.slot.has(x,y)&&!run.tray.empty()) {
                picked=(int)(x-l.slot.x)*3/l.slot.w;pickedTray=true;pickCellX=pickCellY=0;
                if(picked>=(int)run.tray.size())picked=-1;
            }
        }
        return true;
    }
    if(finger!=id)return true;
    pointerX=x;pointerY=y;
    if(phase==1)return true;
    Layout l=layout();finger=-1;
    if(picked>=0) {
        bool ok=false;
        if(pickedTray&&std::abs(x-downX)+std::abs(y-downY)<10*l.scale)ok=run.autoPlace(picked);
        else ok=run.drop(pickedTray,picked,(x-l.board.x)/l.cell,(l.board.y-y)/l.cellH);
        //---- 왜 안 되는지까지 적는다 ----
        //
        //"배치/합성할 수 없습니다" 만으로는 자리가 없어서인지, 다른
        //물건이라서인지, 더 올라갈 데가 없어서인지를 알 수가 없다.
        //모델이 어디서 걸렸는지 남겨 둔다(run.lastFail).
        if(ok) message="";
        else {
            const char* why=run.lastFail;
            const char* text=
                !std::strcmp(why,"spot")?"":
                !std::strcmp(why,"full")?"판에 놓을 자리가 없습니다.":
                !std::strcmp(why,"family")?"같은 종류끼리만 합쳐집니다.":
                !std::strcmp(why,"level")?"같은 단계끼리만 합쳐집니다.":
                !std::strcmp(why,"grow")?"더 올라갈 단계가 없습니다.":
                !std::strcmp(why,"room")?"합친 것이 들어갈 자리가 없습니다.":
                !std::strcmp(why,"crew")?"다음 단계의 동료를 아직 못 가졌습니다.":
                "그 자리에 놓을 수 없습니다.";

            message=text;

            //TODO(diag) 파일로도 남긴다. 화면 글자를 사진으로 주고받는
            //것이 번번이 막혀서다. 원인 잡으면 이 블록은 지운다.
            {
                static int hit=0;

                if(hit<60) {
                    ++hit;

                    FILE* fp=fopen("merge-diag.txt",hit==1?"wb":"ab");

                    if(fp) {
                        const Block& b=pickedTray?run.tray[picked]:run.board[picked];
                        const int cx=(x-l.board.x)/l.cell,cy=(l.board.y-y)/l.cellH;
                        const int tgt=run.at(cx,cy);

                        fprintf(fp,"why=%s tray=%d fam=%d lv=%d rot=%d "
                            "drop=%d,%d target=%d free=%d board=%d",
                            why,(int)pickedTray,b.family,b.level,(int)b.rot,
                            cx,cy,tgt,run.freeCells(),(int)run.board.size());

                        if(tgt>=0) {
                            const Block& t=run.board[tgt];

                            fprintf(fp," t(fam=%d lv=%d rot=%d at=%d,%d)",
                                t.family,t.level,(int)t.rot,t.x,t.y);
                        }
                        fputc(10,fp);
                        fclose(fp);
                    }
                }
            }
        }
        if(!ok)messageTime=3;
        if(ok)PlayMusic(M_POWERUP);
        picked=-1;
        if(ok&&!run.tray.empty())beginSpinLanding();
        save();return true;
    }
    if(l.exit.has(x,y)&&l.exit.has(downX,downY)){close();return true;}
    if(animation>0||run.attacking)return true;
    if(run.lost) {
        if(l.spin.has(x,y)&&l.spin.has(downX,downY)) {active=false;option.gameMode=(unsigned char)oldMode;
            if(!review){robin.mergeRouletteRun[0]=0;robin.mergeRouletteHero=-1;}MergeRouletteBegin();}
        else if(l.attack.has(x,y)&&l.attack.has(downX,downY))close();
        return true;
    }
    bool pull=l.lever.has(downX,downY)&&(l.lever.has(x,y)||downY-y>12*l.scale);
    if((l.spin.has(x,y)&&l.spin.has(downX,downY))||pull) {
        if(run.freeCells()<3) {message="빈칸이 3칸 이상 필요합니다.";messageTime=3;PlayMusic(M_ERROR);return true;}
        if(!run.canSpin()){message="릴의 블록을 모두 놓거나 지금 공격하세요.";messageTime=3;return true;}
        if(pay()){run.spin();rememberReelSymbols();gearStartAngle=gearAngle;animation=45;message="";PlayMusic(M_ROULETTEUP);save();}
    } else if(l.attack.has(x,y)&&l.attack.has(downX,downY)) {
        if(!run.tray.empty()){message="뽑힌 결과가 들어갈 칸을 먼저 비워주세요.";messageTime=3;return true;}
        if(run.board.empty()){message="인벤토리가 비어 있습니다.";return true;}
        if(pay()){run.attack(stats);animation=1;message="출격!";save();}
    }
    return true;
}
#pragma pack(pop)
