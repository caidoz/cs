#include "Core.h"
#pragma pack(push, 8)
#include "Data.h"
#include "Func.h"
#include "Text.h"
#include "Func_MergeRoulette.h"
#include "MergeRouletteModel.h"
#include "StageBackground.h"
#include "Data/AllyBalanceData.h"
#include "Data/CmfData.h"
#include "Data/CastleData.h"
#include "Data/MergeTreeData.h"
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
ITEM treeEquipment[3][MaxLevel];
bool active=false,review=false;
int oldMode=ACTIONRPG, ticks=0, animation=0, picked=-1, finger=-1;
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
int reviewCombatTick=-1,introCaptures=0;
bool reviewCapturePending=false,reviewFinalCapture=false,reviewDone=false;
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
struct Layout {
    float scale;
    int cell, cellH, ground, arenaBottom;
    Box board, slot, lever, trash, heart, spin, attack, exit, left, right, reroll, confirm;
};
Layout layout() {
    Layout l; l.scale=DX/640.0f;
    const float s=l.scale;
    // Everything below the scenery is anchored to the 640 x 850 baseline.
    // Taller phones reveal more scenery above; they never stretch the board.
    int margin=(int)(44*s),bottom=(int)(12*s),bh=(int)(64*s);
    l.spin={margin,bottom+bh,(int)(264*s),bh};
    l.attack={DX-margin-(int)(264*s),bottom+bh,(int)(264*s),bh};
    l.heart={(int)(132*s),(int)(126*s),(int)(376*s),(int)(44*s)};
    // RH's 512 x 218 board at a uniform 0.625 scale, with a right-hand lever.
    l.slot={(int)(160*s),(int)(241*s),(int)(256*s),(int)(109*s)};
    l.lever={l.slot.x+l.slot.w+(int)(12*s),l.slot.y-(int)(12*s),(int)(44*s),(int)(88*s)};
    l.trash={DX-(int)(82*s),l.slot.y,(int)(70*s),(int)(70*s)};
    l.cell=std::max(1,(int)(64*s));l.cellH=l.cell;
    int bw=l.cell*run.shape.width,bhGrid=l.cellH*run.shape.height;
    l.board={(DX-bw)/2,l.slot.y+(int)(12*s)+bhGrid,bw,bhGrid};
    l.arenaBottom=std::max((int)(600*s),l.board.y+(int)(36*s));
    l.ground=l.arenaBottom+(int)(34*s);
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
void goldFrame(Box b,int topColor,int bottomColor,bool enabled=true) {
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
void choice(const Box& b,bool attack,bool enabled) {
    float s=DX/640.f,q=std::min(1.f,b.h/(94*s));
    goldFrame(b,attack?0xC94309:0x075BC1,attack?0x862207:0x062E77,enabled);
    int divider=b.x+(int)(b.w*.37f),tx=b.x+(int)(b.w*.685f);
    MemRect(divider,b.y-(int)(16*s),std::max(1,(int)(2*s)),b.h-(int)(32*s),0xFFE8A4);
    actionIcon({b.x+(int)(23*s),b.y-(int)(16*s*q),(int)(61*s*q),(int)(61*s*q)},attack);
    label(attack?"지금 공격":"더 돌리기",tx,b.y-(int)(8*s*q),1.02f*q,enabled?0xFFF2B7:0xA7B0C0);
    label(attack?"순서대로 행동":"동료·장비 추가",tx,b.y-(int)(36*s*q),.65f*q);
    heart(tx-(int)(28*s*q),b.y-(int)(59*s*q),(int)(28*s*q),true);
    label("-1",tx+(int)(18*s*q),b.y-(int)(60*s*q),.91f*q,0xFFF2B7);
}
void button(const Box& b,const char* title,const char* sub,int color,bool enabled=true) {
    float s=DX/640.0f;
    if(b.h>50*s)goldFrame(b,enabled?color:0x252D3C,enabled?blend(color,0x050A20,.45f):0x1C2534,enabled);
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
    if(f>=Sword)return f==Sword?"무기":f==Armor?"방어구":"목걸이";
    return f>=0&&f<Roles?MergeTrees::RoleName[f]:"?";
}
void configure() {
    // 계열 = 역할 4 + 장비 3. 보유 동료가 역할 × ★ 사다리(roster)에 선다.
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
    pool.push_back(Sword);pool.push_back(Armor);pool.push_back(Necklace);
    hero=ao[PLAYER];hero.type=std::max(0,std::min(2,curHero));
    if(hero.equip[EQUIP_WEAPON].type==EMPTY)
        std::memcpy(hero.equip,robin.charData[hero.type].equip,sizeof(hero.equip));
    for(int g=0;g<3;++g) {
        int family=Sword+g,equip=g==0?EQUIP_WEAPON:g==1?EQUIP_ARMOR:EQUIP_NECK;
        ITEM base=hero.equip[equip];
        int type=base.type==EMPTY?(g==0?ITEM_SWORD+hero.type:g==1?ITEM_ARMOR+hero.type:ITEM_NECK):base.type;
        int detail=base.type==EMPTY?0:base.detail;
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
void icon(int family,const Box& box,float fraction=0.7f,bool atlas=false,int level=1,int crew=-1) {
    if(family<0||family>=FamilyCount)return;
    SetColor(0);grayScale=0;
    if(family<Sword) {
        // 블록이 든 동료. 없으면(릴 회전·계열 카드) 그 역할·★ 의 대표 — 보유분 먼저, 없으면 표의 첫 사람.
        if(crew<0)crew=roster.first(family,std::max(1,std::min((int)MaxLevel,level)));
        if(crew<0)crew=MergeTrees::CrewAt(family,std::max(1,std::min((int)MaxLevel,level)),0);
        if(crew<0)return;
        int npc=crewData[crew*CREWDATASIZE+CREWDATA_TYPE];
        int cmf=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF];
        if(cmf<0||cmf>=MAXCMF)return;
        if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);
        int motion=crewPos[npc*5];
        const auto* bounds=cmfMotionImgSize[cmf]+motion*4;
        float z=std::min(box.w/(float)std::max(1,(int)bounds[2]),box.h/(float)std::max(1,(int)bounds[3]))*fraction;
        DrawCmfDetail(cmf,motion,box.x+box.w/2,box.y-box.h/2,RIGHT,z,0,true);
    } else {
        ITEM item=treeEquipment[family-Sword][std::max(0,std::min(MaxLevel-1,level-1))];
        int size=(int)(std::min(box.w,box.h)*fraction);
        if(!atlas&&item.type==ITEM_SWORD && DrawSwordInBox(item.detail,box.x+(box.w-size)/2,box.y-(box.h-size)/2,size,size,32))return;
        // Raw atlas icon avoids inventory stars/count/compatibility overlays.
        int idx=item.icon;
        DrawImage(32,32,1+33*(idx&7),1+33*((idx&63)>>3),
            box.x+(box.w-size)/2,box.y-(box.h-size)/2,false,0,0,0,32,size/32.0f,
            sprite[ITEM_IMG+(idx>>6)],ITEM_IMG+(idx>>6));
    }
}
void drawSlotFrame(const Box& b) {
    DrawImageScale(512,218,0,0,b.x,b.y,false,0,0,0,0,b.w/512.f,b.h/218.f,sprite[SLOT_IMG],SLOT_IMG);
}
void slotRim(const Box& b) {
    const int cuts[][4]={{0,0,512,14},{0,204,512,14},{0,14,14,190},{498,14,14,190},{170,14,10,190},{340,14,10,190}};
    for(const auto& c:cuts)DrawImageScale(c[2],c[3],c[0],c[1],b.x+(int)(c[0]*b.w/512.f),b.y-(int)(c[1]*b.h/218.f),
        false,0,0,0,0,b.w/512.f,b.h/218.f,sprite[SLOT_IMG],SLOT_IMG);
}
void drawLever(const Layout& l) {
    const Box& b=l.lever;float s=l.scale;
    bool pulling=finger>=0&&b.has(downX,downY)&&!introActive();
    int drop=pulling?(int)(24*s):animation>20?(int)(16*s):0;
    panel({b.x,b.y-b.h+(int)(25*s),b.w,(int)(25*s)},0x3F4555,0xD9AE54);
    MemRect(b.x+(int)(16*s),b.y-drop,(int)(10*s),b.h-(int)(18*s)-drop,0x30364A);
    MemRect(b.x+(int)(18*s),b.y-drop,(int)(4*s),b.h-(int)(18*s)-drop,0xCCD8E6);
    Box knob={b.x+(int)(5*s),b.y+(int)(9*s)-drop,(int)(30*s),(int)(28*s)};
    bevel(knob,0x692026,(int)(7*s));bevel(inset(knob,std::max(1,(int)(3*s))),0xE34B4C,(int)(5*s));
    MemRect(knob.x+(int)(7*s),knob.y-(int)(5*s),(int)(9*s),(int)(4*s),0xFFB091);
}
void drawBlock(const Block& b,const Box& box,bool ghost=false) {
    float s=DX/640.f;int pad=std::max(1,(int)(2*s));
    Box tile=inset(box,pad);
    // ★1 구리 · ★2 은 · ★3 금 · ★4 붉은 금 · ★5 보라 · ★6 하늘
    static const int rims[MaxLevel+1]={0,0xBD885A,0xC3CCD9,0xF5CC5B,0xE07A52,0xB06BD9,0x5AC8E8};
    static const int fills[MaxLevel+1]={0,0x382A29,0x303C51,0x67501E,0x5A2A1E,0x3A2252,0x1E3F4C};
    int lv=std::max(1,std::min((int)MaxLevel,b.level));int rim=rims[lv],fill=fills[lv];
    bevel(tile,0x080C1C,pad*2);bevel(inset(tile,pad),rim,pad);bevel(inset(tile,pad*2),ghost?0x33415B:fill,pad);
    Box art=inset(tile,pad);art.h-=std::max(18,(int)(22*s));icon(b.family,art,.96f,false,b.level,b.crew);
    char text[32];std::snprintf(text,sizeof(text),"★%d",b.level);
    label(text,box.x+box.w/2,box.y-box.h+(int)(23*s),std::min(.66f,box.h/(48*s)),0xFFF0B1);
}
Box blockBox(const Block& b,const Layout& l) {
    return {l.board.x+b.x*l.cell,l.board.y-b.y*l.cellH,Wide(b.level)*l.cell,Tall(b.level)*l.cellH};
}
float flightStart(int i) {return 2.05f+i*.22f;}
void drawIntro(const Layout& l) {
    if(!introActive())return;
    float s=l.scale,t=introElapsed;
    float fade=std::max(0.f,(t-3.35f)/.45f);
    SetAlpha((int)(24*(1-fade)));MemRect(0,DY,DX,DY,0x030615);SetAlpha((int)(32*(1-fade)));
    Box slot=l.slot;slot.y=(int)(DY*.52f+slot.h*.5f);
    label(t<1.9f?"시작 동료·장비 소환":"인벤토리에 배치 중",DX/2,
        t<1.9f?slot.y+(int)(52*s):slot.y-slot.h-(int)(12*s),.96f,0xFFE6A1);
    if(t<1.9f)label("시작 보상 · 하트 소모 없음",DX/2,slot.y-slot.h-(int)(12*s),.58f,0xCBD3E6);
    drawSlotFrame(slot);
    for(int i=0;i<3;++i) {
        float stop=1.2f+i*.24f;
        Box reel={slot.x+i*slot.w/3+(int)(8*s),slot.y-(int)(8*s),slot.w/3-(int)(16*s),slot.h-(int)(16*s)};
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
            icon(run.families[i],{reel.x,centerY+pitch/2,reel.w,pitch},.94f,true,1,i<(int)run.board.size()?run.board[i].crew:-1);
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
        float fromX=slot.x+slot.w*(2*i+1)/6.f,fromY=slot.y-slot.h/2.f;
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
    if(introActive()) {
        float before=introElapsed;
        introElapsed+=std::min(.1f,std::max(.001f,cocos2d::Director::getInstance()->getDeltaTime()));
        for(int i=0;i<3;++i) {
            float stop=1.2f+i*.24f,land=flightStart(i)+.7f;
            if(before<stop&&introElapsed>=stop)PlayMusic(M_ROULETTEUP);
            if(before<land&&introElapsed>=land)PlayMusic(M_POWERUP);
        }
        return;
    }
    if(animation>0 && --animation==0 && !run.attacking)save();
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
    if(run.choosing) {
        int selected=run.selected;
        if(!run.drafted){reviewTap(l.confirm);animation=0;}
        reviewTrace(run.drafted&&run.families[0]==selected?"PASS selected first tree retained in weighted draft":"FAIL first tree selection");
        reviewTap(l.confirm);return;
    }
    if(introActive()) {
        if(!(introCaptures&1)&&introElapsed>.3f) {
            introCaptures|=1;
            auto before=run.encode();long long hearts=robin.heart;
            reviewTap(l.spin);reviewTap(l.lever);reviewTap(l.attack);reviewTap(l.exit);
            Box cell={l.board.x,l.board.y,l.cell,l.cellH};reviewTap(cell);
            reviewTrace(active&&run.encode()==before&&robin.heart==hearts?"PASS opening locks all gameplay input":"FAIL opening input lock");
            reviewTrace(run.board.size()==3&&run.tray.empty()&&run.spins==SpinLimit&&robin.heart==20?"PASS three free starters committed once":"FAIL opening reward");
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
    if(t==30||t==100||t==170||t==240) {
        long long before=robin.heart;int life=run.lives;
        if(t==100) {
            float x=l.lever.x+l.lever.w/2.f,y=l.lever.y-l.lever.h/2.f;
            MergeRouletteTouch(0,999,x,y);MergeRouletteTouch(1,999,x,y-24*l.scale);MergeRouletteTouch(2,999,x,y-36*l.scale);
        } else reviewTap(l.spin);
        reviewTrace(robin.heart==before-1&&run.lives==life&&!run.tray.empty()?"PASS spin costs one heart without enemy turn":"FAIL spin");
        if(t==100)reviewTrace(robin.heart==before-1&&!run.tray.empty()?"PASS right lever pull spins once":"FAIL lever pull");
    }
    if(t==32) {
        long long balance=robin.heart;reviewTap(l.spin);reviewTap(l.attack);
        reviewTrace(heartBlink>0&&spentHeart==heartDisplay&&robin.heart==balance?"PASS one heart blinks and repeat input cannot charge twice":"FAIL heart animation");
        reviewCapture("06-heart-spend");
    }
    if(t==90||t==160||t==230||t==300) {
        for(int i=0;i<3&&!run.tray.empty();++i) {
            int count=(int)run.tray.size();
            Box cell={l.slot.x,l.slot.y,l.slot.w/3,l.slot.h};reviewTap(cell);
            if((int)run.tray.size()==count)break;
        }
        reviewTrace(run.tray.empty()&&!run.board.empty()?"PASS tray placed through input":"FAIL tray placement");
    }
    if(t==310) {
        Run restored;
        reviewTrace(restored.decode(run.encode())&&restored.encode()==run.encode()?"PASS run roundtrip":"FAIL run roundtrip");
        reviewLayout(l,"02-inventory");reviewCapture("02-inventory");
    }
    if(t==305&&!run.board.empty()) {
        Block moving=run.board[0];bool checked=false;
        for(int y=run.shape.height-Tall(moving.level);y>=0&&!checked;--y)for(int x=run.shape.width-Wide(moving.level);x>=0&&!checked;--x) {
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
    if(t==330) {
        reviewAttackBlocks=run.board;
        long long before=robin.heart;reviewTap(l.attack);
        reviewTrace(run.attacking&&robin.heart==before-1?"PASS attack costs one heart":"FAIL attack");
    }
    if(t==348)reviewCapture("03-launch");
    if(t==590) {
        reviewCapture("04-exchange");
        bool retained=run.board.size()==reviewAttackBlocks.size();
        for(int i=0;i<(int)run.board.size()&&retained;++i) {
            const Block& a=run.board[i];const Block& b=reviewAttackBlocks[i];
            retained=a.family==b.family&&a.level==b.level&&a.x==b.x&&a.y==b.y;
        }
        reviewTrace(!run.attacking&&retained&&run.spins>=10?"PASS sequential actions preserve every board element":"FAIL retained inventory");
    }
    if(t==600) {run.stage=9;run.setShape(castleShape(run.stage));run.enemyHp=run.enemyMax=hpFor(run.stage,0);}
    if(t>=602&&!reviewCapturePending&&!reviewFinalCapture) {
        reviewFinalCapture=true;reviewLayout(l,"05-castle10");reviewCapture("05-castle10");
    } else if(t>=603&&reviewFinalCapture&&!reviewCapturePending) {
        Run current=run;
        run=Run();run.roster=&roster;run.choosing=false;run.families[0]=Sword;run.families[1]=Armor;run.families[2]=Necklace;
        run.setShape(castleShape(0));
        for(int i=0;i<22;++i) {Block b;b.family=Sword;b.x=i%run.shape.width;b.y=i/run.shape.width;run.board.push_back(b);}
        Layout full=layout();long long balance=robin.heart;auto blocked=run.encode();reviewTap(full.spin);reviewTap(full.lever);
        reviewTrace(run.freeCells()==2&&run.encode()==blocked&&robin.heart==balance&&messageTime>0?"PASS fewer than three empty cells logs warning without charging":"FAIL full board guard");
        Box source=blockBox(run.board[0],full);float x=source.x+full.cell/2.f,y=source.y-full.cellH/2.f;
        float tx=full.trash.x+full.trash.w/2.f,ty=full.trash.y-full.trash.h/2.f;
        MergeRouletteTouch(0,999,x,y);MergeRouletteTouch(1,999,tx,ty);MergeRouletteTouch(2,999,tx,ty);
        reviewTrace(run.freeCells()==3&&run.canSpin()&&robin.heart==balance?"PASS trash drag frees a cell and restores spin":"FAIL discard block");
        run=current;
        std::string stored=run.encode();
        std::memset(robin.mergeRouletteRun,0,sizeof(robin.mergeRouletteRun));
        std::memcpy(robin.mergeRouletteRun,stored.data(),stored.size());robin.mergeRouletteHero=curHero;
        close();MergeRouletteBegin(true);
        reviewTrace(!introActive()&&run.encode()==stored?"PASS explicit continue preserves run without granting starters":"FAIL continue entry");
        close();MergeRouletteBegin(false);
        reviewTap(layout().confirm);animation=0;reviewTap(layout().confirm);
        reviewTrace(introActive()&&run.board.size()==3&&run.spins==SpinLimit?"PASS new battle always replays three-starter intro":"FAIL fresh entry intro");
        reviewDone=true;reviewTrace("DONE");
    }
}
}

bool MergeRouletteActive() {return active;}
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
    if(run.choosing)run.families[0]=run.selected;
    introElapsed=-1.f;introCaptures=0;reviewCombatTick=-1;
    reviewCapturePending=reviewFinalCapture=false;
    ticks=animation=0;picked=finger=-1;message="";
    observedHearts=robin.heart;heartDisplay=(int)std::min((long long)heartCapacity,robin.heart);heartBlink=messageTime=0;spentHeart=-1;
    active=true;drawHandle=MD_PLAY;keyHandle=MK_PLAY;curMenu=MENU_PLAY;
    autoPlay=false;autoFrame=-1;touchDisable=false;mustRefresh=true;
    if(!run.choosing)save();
}
void MergeRouletteLobbyDraw() {
    if(popUpCnt>0||LoadoutOpen())return;
    Box b={DX-(int)(154*DX/640.0f),DY-(int)(120*DX/640.0f),(int)(142*DX/640.0f),(int)(44*DX/640.0f)};
    button(b,"전투 시작","시작 3개 추첨",0x254C7C);
    if(robin.mergeRouletteRun[0]&&robin.mergeRouletteHero==curHero) {
        Box keep=b;keep.y-=(int)(50*DX/640.f);keep.h=(int)(32*DX/640.f);
        button(keep,"이어서",nullptr,0x25394E);
    }
}
void MergeRouletteDraw() {
    tick();ResetRectPoint();mustRefresh=true;
    Layout l=layout();float s=l.scale;char text[160];
    SetAlpha(32);SetColor(0);grayScale=0;
    {StageBg::Borrow sunset(1,0);StageBg::Draw(l.ground,l.arenaBottom,false);}
    int castle=std::max(1,std::min(10,(int)robin.castle+1));
    float nw=1,nh=1;CastlePartsNaturalSize(castle,&nw,&nh);
    int cw=(int)(DX*.55f),ch=(int)(cw*nh/std::max(1.0f,nw));
    int top=l.ground+ch;
    float contact=CastlePartsWheelLine(castle,top,cw,ch);top+=(int)(l.ground-contact);
    SetSectionClip(0,DY,DX,DY-l.arenaBottom,false);
    CastlePartsSetFreePlace(true);CastlePartsDrawRect(castle,0,top,cw,ch);CastlePartsSetFreePlace(false);
    int hx=(int)(DX*.43f),hy=l.ground+(int)(72*s),ex=(int)(DX*.81f),ey=l.ground;
    float commanderX=(float)hx,commanderY=(float)hy,deckY=(float)hy;
    if(CastlePartsCombatAnchors(&commanderX,&commanderY,&deckY)) {hx=(int)commanderX;hy=(int)commanderY;}
    // Short screens keep the hero on the lower combat deck rather than cropping
    // the commander on the upper platform out of the viewport.
    // In this mode the combatants stand on the open deck, as in the reference.
    hy=(int)deckY;hx=(int)(cw*.79f);
    float heroZoom=std::max(.35f*s,std::min(.82f*s,(DY-hy-8*s)/80.f));
    DrawPlayer(&hero,motionData[run.attacking?32+(ticks%32):0],hx,hy,RIGHT,heroZoom,0,false,true);
    for(int i=0,shown=0;i<3&&shown<1;++i)if(run.families[i]<Roles) {
        int crew=roster.first(run.families[i],1);if(crew<0)crew=MergeTrees::CrewAt(run.families[i],1,0);if(crew<0)continue;
        int npc=crewData[crew*CREWDATASIZE+CREWDATA_TYPE];
        int cmf=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF];
        if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);
        DrawCmfDetail(cmf,crewPos[npc*5],hx-(int)(56*s),(int)deckY,RIGHT,std::min(.78f*s,heroZoom),0,false);++shown;
    }
    int npc=run.wave==9?ENEMY_CASTLE_BOSS1:ENEMY_KNIGHT+run.wave%2;
    int cmf=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF];
    if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);
    DrawCmfDetail(cmf,crewPos[npc*5],ex,ey,LEFT,(run.wave==9?0.65f:1.35f)*s,0,false);
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
    UnSectionClip(false);
    for(int y=0;y<l.arenaBottom;y+=8)MemRect(0,l.arenaBottom-y,DX,std::min(8,l.arenaBottom-y),blend(0x101831,0x090E29,y/(float)l.arenaBottom));
    std::snprintf(text,sizeof(text),"%d성 · 웨이브 %d/10",run.stage+1,run.wave+1);
    label(text,DX/2,DY-(int)(17*s),0.55f);
    // Readable unit plates directly beneath the battle, separate from the board title.
    Box allyPlate={hx-(int)(43*s),l.ground+(int)(70*s),(int)(100*s),(int)(43*s)};
    Box enemyPlate={ex-(int)(52*s),l.arenaBottom+(int)(45*s),(int)(106*s),(int)(43*s)};
    bevel(allyPlate,0xAAA694,(int)(5*s));bevel(inset(allyPlate,std::max(1,(int)(2*s))),0x22252B,(int)(3*s));
    bevel(enemyPlate,0xAAA694,(int)(5*s));bevel(inset(enemyPlate,std::max(1,(int)(2*s))),0x22252B,(int)(3*s));
    std::snprintf(text,sizeof(text),"목숨  %d / %d",run.lives,run.maxLives);
    int barPad=std::max(1,(int)(5*s));
    MemRect(allyPlate.x+barPad,allyPlate.y-barPad,allyPlate.w-2*barPad,(int)(14*s),0x37433B);
    MemRect(allyPlate.x+barPad,allyPlate.y-barPad,(allyPlate.w-2*barPad)*run.lives/std::max(1,run.maxLives),(int)(14*s),0x406D39);
    label(text,allyPlate.x+allyPlate.w/2,allyPlate.y-(int)(3*s),.62f);
    std::snprintf(text,sizeof(text),"방어 %d",std::max(0,run.maxLives-3));
    shield(allyPlate.x+(int)(15*s),allyPlate.y-(int)(24*s),(int)(10*s));
    label(text,allyPlate.x+allyPlate.w/2+(int)(7*s),allyPlate.y-(int)(23*s),.59f,0xFFF0B8);
    std::snprintf(text,sizeof(text),"%lld/%lld",run.enemyHp,run.enemyMax);
    int hpWidth=enemyPlate.w-2*barPad,hpY=enemyPlate.y-barPad;
    MemRect(enemyPlate.x+barPad,hpY,hpWidth,(int)(14*s),0x493444);
    MemRect(enemyPlate.x+barPad,hpY,(int)(hpWidth*(double)run.enemyHp/run.enemyMax),(int)(14*s),0xAA343E);
    label(text,enemyPlate.x+enemyPlate.w/2,enemyPlate.y-(int)(3*s),.64f,flash?0xFFB060:0xFFFFFF);
    shield(enemyPlate.x+(int)(17*s),enemyPlate.y-(int)(24*s),(int)(10*s));
    label("방어 0",enemyPlate.x+enemyPlate.w/2+(int)(7*s),enemyPlate.y-(int)(23*s),.59f,0xFFF0B8);
    button(l.exit,"나가기",nullptr,0x25304A,!run.attacking);
    if(usesCastleGrid())CastleInventoryGridDraw(std::max(0,std::min(9,run.stage)),l.board.x,l.board.y,l.cell);
    else for(int row=0;row<run.shape.height;++row)for(int col=0;col<run.shape.width;++col) {
        int pad=std::max(1,(int)(2*s));
        Box tile={l.board.x+col*l.cell+pad,l.board.y-row*l.cellH-pad,l.cell-2*pad,l.cellH-2*pad};
        bevel(tile,0x53658E,pad);bevel(inset(tile,pad),0x0B1229,pad);
    }
    long long predicted=run.preview(stats);
    label("인벤토리",DX/2,l.board.y+(int)(43*s),.94f,0xFFF0B6);
    if(!run.choosing) {
        std::snprintf(text,sizeof(text),"예상 피해 %lld / 적 %lld",predicted,run.enemyHp);
        label(text,DX/2,l.board.y+(int)(16*s),.43f,predicted>=run.enemyHp?0xFFD45E:0xBCC7DE);
    }
    int lineY=l.board.y+(int)(31*s);
    MemRect(l.board.x-(int)(18*s),lineY,l.board.w/2-(int)(42*s),std::max(1,(int)s),0x98A6C0);
    MemRect(DX/2+(int)(61*s),lineY,l.board.w/2-(int)(42*s),std::max(1,(int)s),0x98A6C0);
    for(int i=0;i<(int)run.board.size();++i) {
        if(introActive()&&i<3)continue;
        if(picked==i&&!pickedTray)continue;
        drawBlock(run.board[i],blockBox(run.board[i],l));
    }
    if(run.attacking&&run.nextShot>0&&animation>0) {
        const Shot& shot=run.shots[run.nextShot-1];Box from=blockBox(shot.block,l);
        int lv=shot.block.level,duration=std::min(42,6+6*lv);
        float t=1-animation/(float)duration;
        MemRectFrameThick(from.x,from.y,from.w,from.h,0xFFE99E,std::max(1,(int)(3*s)));
        int size=(int)((1-t)*std::min(from.w,from.h)+t*32*s);
        Box flying={(int)((1-t)*from.x+t*ex),(int)((1-t)*from.y+t*(ey+45*s)),size,size};
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
    // RH's original three-reel board. Keep all symbols inside its windows.
    drawSlotFrame(l.slot);
    for(int i=0;i<3;++i) {
        int pad=std::max(1,(int)(12*s));
        Box window={l.slot.x+i*l.slot.w/3+pad,l.slot.y-pad,l.slot.w/3-2*pad,l.slot.h-2*pad};
        bool held=!run.tray.empty()&&i<(int)run.tray.size();
        int f=held?run.tray[i].family:run.families[i],lv=held?run.tray[i].level:1,crew=held?run.tray[i].crew:-1;
        if(animation>0&&!run.attacking){f=run.families[(ticks/3+i)%3];lv=1;crew=-1;}
        SetSectionClip(window.x,window.y,window.w,window.h,false);
        icon(f,window,.84f,true,lv,crew);
        UnSectionClip(false);
    }
    slotRim(l.slot);drawLever(l);
    bevel(l.heart,0x6C748B,(int)(6*s));
    bevel(inset(l.heart,std::max(1,(int)(2*s))),0x171D32,(int)(5*s));
    int cols=heartCapacity>10?10:heartCapacity;
    int heartSize=(int)(22*s),pitch=(int)(27*s),x0=DX/2-(cols*pitch-(int)(5*s))/2;
    int rows=(heartCapacity+cols-1)/cols;
    int heartTop=l.heart.y-(int)((rows==1?12:4)*s);
    for(int i=0;i<heartCapacity;++i) {
        bool filled=i<heartDisplay;
        if(i==spentHeart&&heartBlink>0)filled=((int)(heartBlink/.09f)%2)==0;
        heart(x0+(i%cols)*pitch,heartTop-(i/cols)*(int)(21*s),heartSize,filled);
    }
    if(run.choosing) {
        button(l.left,"<",nullptr,0x253F61,!run.drafted);button(l.right,">",nullptr,0x253F61,!run.drafted);
        button(l.reroll,run.drafted?"다시 뽑기":"트리 변경",run.drafted?"하트 -1":"첫 릴 직접 선택",0x24578D,(!run.drafted||robin.heart>0)&&animation==0);
        button(l.confirm,run.drafted?"전투 시작":"계열 뽑기",run.drafted?"선택한 편성으로 출발":"나머지 두 트리 무작위",0x975028,animation==0);
    } else if(run.lost) {
        button(l.spin,"다시 도전","새 런 시작",0x24578D);button(l.attack,"로비로",nullptr,0x975028);
    } else {
        bool ready=!introActive()&&!run.attacking&&animation==0;
        choice(l.spin,false,ready&&run.canSpin()&&robin.heart>0);
        choice(l.attack,true,ready&&!run.board.empty()&&robin.heart>0);
        if(ready&&!run.board.empty()&&predicted>=run.enemyHp)
            MemRectFrameThick(l.attack.x,l.attack.y,l.attack.w,l.attack.h,0xFFE36A,std::max(1,(int)(3*s)));
        Box orBadge={DX/2-(int)(21*s),l.spin.y-l.spin.h/2+(int)(14*s),(int)(42*s),(int)(28*s)};
        bevel(orBadge,0x080E20,(int)(6*s));bevel(inset(orBadge,std::max(1,(int)(2*s))),0xF6CE68,(int)(5*s));
        bevel(inset(orBadge,std::max(2,(int)(4*s))),0x26303D,(int)(3*s));
        label("OR",DX/2,orBadge.y-(int)(4*s),.82f,0xFFF0B0);
        if(!run.tray.empty()) {
            for(int i=0;i<(int)run.tray.size();++i) {
                char t[20];std::snprintf(t,sizeof(t),"★%d",run.tray[i].level);
                label(t,l.slot.x+l.slot.w*(2*i+1)/6,l.slot.y-(int)(14*s),0.42f);
            }
        }
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
            icon(b.family,{(int)pointerX-l.cell/2,(int)pointerY+l.cellH/2,l.cell,l.cellH},.7f,false,b.level,b.crew);
        }
    }
    if((picked>=0&&!pickedTray)||run.freeCells()<3) {
        panel(l.trash,0x3D2431,0xD98C79);
        label("×",l.trash.x+l.trash.w/2,l.trash.y-(int)(5*s),1.1f,0xFFDAB3);
        label("버리기",l.trash.x+l.trash.w/2,l.trash.y-(int)(43*s),.54f);
    }
    if(messageTime>0&&!message.empty()) {
        Box toast={(int)(90*s),l.arenaBottom+(int)(53*s),(int)(460*s),(int)(48*s)};
        panel(toast,0x352332,0xDD957B);
        label(message.c_str(),DX/2,toast.y-(int)(6*s),.59f,0xFFE6C0);
        if(run.freeCells()<3)label("블록을 휴지통으로 드래그해 칸을 비워주세요",DX/2,toast.y-(int)(28*s),.49f);
    }
    if(messageTime<=0&&!run.choosing&&!message.empty()&&(message.find("없")!=std::string::npos||message.find("부족")!=std::string::npos))
        label(message.c_str(),DX/2,DY-(int)(45*s),0.48f);
    if(run.choosing) {
        // Drafting does not pretend that the empty board is already playable.
        int cardW=std::min(l.board.w-(int)(24*s),(int)(440*s));
        int cardH=std::min(l.board.h-(int)(20*s),(int)(250*s));
        Box card={(DX-cardW)/2,l.board.y-(l.board.h-cardH)/2,cardW,cardH};
        panel(card,0x192539,0xD3A35D);
        label(run.drafted?"이번 전투의 세 계열":"전투 준비",DX/2,card.y-(int)(28*s),.92f,0xFFD88B);
        int artH=std::max(28,cardH-(int)(116*s));
        for(int i=0;i<3;++i) {
            Box art={card.x+cardW*i/3,card.y-(int)(49*s),cardW/3,artH};
            if(!run.drafted&&i>0)label("?",art.x+art.w/2,art.y-art.h/2,1.5f,0x8F9AAF);
            else icon(run.families[i],art,.82f);
        }
        label(treeName(run.selected),DX/2,card.y-cardH+(int)(48*s),.60f,0xFFD88B);
        label("더 돌리기 / 지금 공격 · 각각 하트 -1",DX/2,card.y-cardH+(int)(22*s),.50f,0xC0C8D6);
    }
    drawIntro(l);
    reviewStep(l);
}

bool MergeRouletteTouch(int phase,int id,float x,float y) {
    if(!active) {
        if(phase==0&&drawHandle==MD_LOBBY&&popUpCnt==0&&!LoadoutOpen()) {
            float s=DX/640.0f;
            Box b={DX-(int)(154*s),DY-(int)(120*s),(int)(142*s),(int)(44*s)};
            if(b.has(x,y)) {MergeRouletteBegin();return true;}
            Box keep=b;keep.y-=(int)(50*s);keep.h=(int)(32*s);
            if(keep.has(x,y)&&robin.mergeRouletteRun[0]&&robin.mergeRouletteHero==curHero) {MergeRouletteBegin(true);return true;}
        }
        return false;
    }
    if(introActive()) {picked=finger=-1;return true;}
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
        else if(l.board.has(x,y))ok=run.place(pickedTray,picked,(int)(x-l.board.x)/l.cell-pickCellX,(int)(l.board.y-y)/l.cellH-pickCellY);
        else if(!pickedTray&&l.trash.has(x,y)) {run.board.erase(run.board.begin()+picked);ok=true;}
        message=ok?"":"그 자리에 배치/합성할 수 없습니다.";
        if(ok)PlayMusic(M_POWERUP);
        picked=-1;save();return true;
    }
    if(l.exit.has(x,y)&&l.exit.has(downX,downY)){close();return true;}
    if(animation>0||run.attacking)return true;
    if(run.lost) {
        if(l.spin.has(x,y)&&l.spin.has(downX,downY)) {active=false;option.gameMode=(unsigned char)oldMode;
            if(!review){robin.mergeRouletteRun[0]=0;robin.mergeRouletteHero=-1;}MergeRouletteBegin();}
        else if(l.attack.has(x,y)&&l.attack.has(downX,downY))close();
        return true;
    }
    if(run.choosing) {
            if(!run.drafted&&((l.left.has(x,y)&&l.left.has(downX,downY))||(l.right.has(x,y)&&l.right.has(downX,downY))||(l.reroll.has(x,y)&&l.reroll.has(downX,downY)))) {
            auto at=std::find(pool.begin(),pool.end(),run.selected);int i=(int)(at-pool.begin());
            i=(i+(l.left.has(x,y)?(int)pool.size()-1:1))%(int)pool.size();
            run.selected=pool[i];run.families[0]=run.selected;
            save();
        } else if(run.drafted&&l.reroll.has(x,y)&&l.reroll.has(downX,downY)&&pay()) {run.choose(pool,treeWeights);animation=45;save();}
        else if(l.confirm.has(x,y)&&l.confirm.has(downX,downY)) {
            if(!run.drafted) {run.choose(pool,treeWeights);animation=45;message="이번 조합을 확인하고 전투를 시작하세요.";}
            else if(run.start(pool,treeWeights,true,true)) {introElapsed=0;message="";PlayMusic(M_ROULETTEUP);}
            save();
        }
        return true;
    }
    bool pull=l.lever.has(downX,downY)&&(l.lever.has(x,y)||downY-y>12*l.scale);
    if((l.spin.has(x,y)&&l.spin.has(downX,downY))||pull) {
        if(run.freeCells()<3) {message="빈칸이 3칸 이상 필요합니다.";messageTime=3;PlayMusic(M_ERROR);return true;}
        if(!run.canSpin()){message="릴의 블록을 모두 놓거나 지금 공격하세요.";messageTime=3;return true;}
        if(pay()){run.spin();animation=45;message="";PlayMusic(M_ROULETTEUP);save();}
    } else if(l.attack.has(x,y)&&l.attack.has(downX,downY)) {
        if(run.board.empty()){message="인벤토리가 비어 있습니다.";return true;}
        if(pay()){run.attack(stats);animation=1;message="출격!";save();}
    }
    return true;
}
#pragma pack(pop)
