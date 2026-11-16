#include "Core.h"
#pragma pack(push, 8)
#include "Data.h"
#include "Func.h"
#include "Text.h"
#include <cstring>
#include "Func_MergeRoulette.h"
#include "MergeRouletteModel.h"
#include "NativeGearIcons.h"
#include "ItemSeriesCatalog.h"
#include "GridItemCatalog.h"
#include "Data/SwordSprites.h"
#include "ItemSeriesArt.h"
#include "SquareGearIcons.h"
#include "MergeCombatPresentation.h"
#include "TurretAttackPresentation.h"
#include "MergeRenderProfile.h"
#include "StageBackground.h"
#include "Data/AllyBalanceData.h"
#include "Data/CmfData.h"
#include "Data/CastleData.h"
#include "Data/MergeTreeData.h"
#include "Data/CastleFacilities.h"
#include "MergeCastleTransition.h"
#include "Data/MergeCastleRebuild.h"
#include "Data/MergeCastleFronts.h"
#include "Data/MountedCannonSprites.h" // Turret-mounted artillery and visible grade growth.
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
MergeCombat::AnimatedValue guardDisplay,heroHealthDisplay,enemyHealthDisplay;
MergeCombat::AnimatedValue attackDisplay;
MergeCombat::WaveTransition waveTransition;
int defeatedNpc=-1,defeatedMotion=0;
int objectDrawOrder=0,monsterDrawOrder=0,allyDrawOrder=0,impactDrawOrder=0;
bool monsterDrawn=false;
bool attackDisplayKnown=false;
long long attackGain=0;
float attackGainTime=0;
float simulationRemainder=0;
struct GradeAccent {Block block;int age=0;};
std::vector<GradeAccent> gradeAccents;
std::vector<Block> shownGrades;
struct CombatNumber {std::string text;float x,y;int color,age=0;bool defense=false;};
std::vector<CombatNumber> combatNumbers;
//---- 맞는 자리 ----
//
//적 cmf 의 앵커 x 는 몸통 가운데가 아니라 그림의 등 쪽 끝이다(DrawCmfDetail 의
//center=false). 그래서 탄·타격 효과·피해 숫자를 ex 에 찍으면 전부 몬스터의
//맨 뒤에서 터졌다. 공성전의 성주도 DX*.85 가 아니라 제가 선 자리(foeX)에 있다.
//drawWorld 가 실제로 그린 자리에서 몸통 가운데를 셈해 적어 두고, 셋이 다 이것을
//본다. 재는 식은 Func_Draw 의 StageCombatRecordActor 와 같다.
int enemyBodyX=0,enemyBodyY=0,allyBodyX=0,allyBodyY=0;bool enemyBodyKnown=false,allyBodyKnown=false;
Roster roster;
int treeWeights[FamilyCount]={};
ITEM treeEquipment[GearCount][MaxLevel];
bool active=false,review=false;
const ITEM* gearTableOverride=nullptr;   //MergeSiege.inc 가 상대 판을 그릴 때 끼운다
bool siegeActive=false;   //공성전(PVP 디버그) 중. MergeSiege.inc
int siegeHullStage=-1;    //공성전: 그릴 성(상대의 성). -1 이면 run.stage
namespace Siege{extern bool swapped;extern int castle,refRows,region;}
//성(안쪽 구성요소 전부)과 레일이 같이 쓰는 들어올림. 포대가 보이도록 8픽셀 내려 둔다.
//---- 상대 판(몬스터·공성전)을 어디에 두나 ----
//
//1:1.9 보다 길면 머리글 아래 하늘이 비므로 거기에 붙박이로 깐다(터치로 펼칠 것 없이 늘 보인다).
//그보다 짧으면 오른쪽 위 작은 단추로 두고 터치하면 펼친다. 붙박이 판은 **내 판과 같은 80칸**이라
//(판 규격은 히어로와 같아야 한다) 성 지붕과 겹친다 - 그만큼 성을 덜 올린다(castleSceneLift).
//네 줄 판 320 + 머리글 78 + 이름 줄·틈 46 = 444 가 성 지붕 위에 들어가려면 1:2.0 은 되어야 한다.
bool topBoardPanel(){return DY>=DX*2.0f;}
int topPanelCell(){return std::max(8,(int)(80*DX/640.f));}
int topPanelTop(){return DY-(int)(78*DX/640.f);}   //머리글 바로 아래
//붙박이 판 밑변(GL) - 성 지붕(원본 y=83)이 이 아래로 와야 한다. 머리글(78) + 줄×칸 + 이름 줄(34) + 틈(12).
float topPanelCeiling(int rows){const float s=DX/640.f;return topPanelTop()-rows*topPanelCell()-46*s;}
float castleSceneLift(){
    const float s=DX/640.f;
    // Reveal a strip of track above the fixed navigation on short screens.
    // Fade the correction out by 1:1.6; taller layouts keep their placement.
    //로비와 전투가 같은 자리다. 기준값에서 25 내린 값 - 1:1.33 에서 전투의 하트 바가 하단 세 단추
    //바로 위(6픽셀)에 앉고, 로비의 성도 같은 높이에 선다(바퀴 아랫단은 하단 메뉴가 덮는다).
    const float base=MergeCombat::lobbyCastleLift((float)DX,(float)DY)-25.f*s;
    //전투 중 붙박이 판(긴 화면)이 성 지붕과 겹치면 그만큼 덜 올린다. 로비는 그대로.
    if(active&&topBoardPanel()){
        const int rows=std::max(4,(int)run.shape.height);
        const float roofBase=(1445.f-83.f)*(DX/1089.f*1.04f)+34*s;   //OriginalCastle::box(0,83) 의 윗변, 올림 0 일 때
        //짧은 화면의 기준(-25)보다 더 내리지는 않는다 - 그 밑은 하단 단추 자리다.
        return std::max(-25.f*s,std::min(base,topPanelCeiling(rows)-roofBase));
    }
    return base;
}
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
bool reelResultDrawn[3]={};
bool pickedTray=false;
float pointerX=0,pointerY=0,downX=0,downY=0;
int pickCellX=0,pickCellY=0, flash=0;
std::vector<int> pool;
std::vector<Block> reviewAttackBlocks;
std::string message;
OBJECT hero;
const int costumeSlots[GearCount]={EQUIP_WEAPON,EQUIP_ARMOR,EQUIP_BOOTS,EQUIP_HELM,EQUIP_GLOVE,EQUIP_PANTS};
ITEM baseCostume[GearCount];
int costumeLevels[GearCount]={};
//로비에서 끼고 들어온 장비. 판의 블록이 입히지 않은 부위는 이것으로 센다(refreshHeroVitals).
ITEM wornEquip[TOTALEQUIP];
int costumeEffectTicks=0;
int attackWeaponLevel=0;
MergeCombat::WeaponSwap weaponSwap;
MergeCombat::DamagePause damagePause;
ITEM incomingWeapon;
bool requestWeaponSwap(const ITEM& target){
    const ITEM& old=hero.equip[EQUIP_WEAPON];
    if(old.type==target.type&&old.detail==target.detail&&old.grade==target.grade)return false;
    incomingWeapon=target;weaponSwap.begin();return true;
}
void showAttackWeapon(int level) {
    attackWeaponLevel=level;
    const int shown=level?level:costumeLevels[0];
    hero.equip[EQUIP_WEAPON]=shown?treeEquipment[0][shown-1]:baseCostume[0];
}
int heartCapacity=10;
float heartBlink=0,messageTime=0;
int heartDisplay=0,spentHeart=-1;
long long observedHearts=0;
float introElapsed=-1;
MergeCombat::ResidentReveal deckReveal[64];
struct DeckMergePresentation {
    MergeCombat::DeckMergeTimeline time;
    Block inputs[2],result;
    float fromX[2]={},targetX=0;
    bool hadPosition[2]={},resultWasVisible=false;
} deckMerge;
unsigned deckMergeSeen=0;
float deckCrewX[64]={};
bool deckCrewPositionKnown[64]={};
int deckMergeGhostsDrawn=0;
float deckMergeGhostX[2]={};
void observeDeckMerge() {
    if(deckMergeSeen==run.mergeSeq)return;
    deckMergeSeen=run.mergeSeq;
    if(run.mergeResult.family<0||run.mergeResult.family>=Roles||run.mergeResult.crew<0)return;
    deckMerge=DeckMergePresentation();deckMerge.result=run.mergeResult;
    deckMerge.resultWasVisible=deckReveal[deckMerge.result.crew].visible();
    for(int i=0;i<2;++i){
        deckMerge.inputs[i]=run.mergeInputs[i];const int crew=deckMerge.inputs[i].crew;
        deckMerge.hadPosition[i]=crew>=0&&crew<64&&deckCrewPositionKnown[crew];
        if(deckMerge.hadPosition[i])deckMerge.fromX[i]=deckCrewX[crew];
    }
    if(deckMerge.inputs[0].crew==deckMerge.inputs[1].crew){
        deckMerge.fromX[0]-=14*DX/640.f;deckMerge.fromX[1]+=14*DX/640.f;
    }
    deckMerge.time.begin();
}
float flightStart(int i);
bool gridBlockLanded(int index) {
    return introElapsed<0||index>=3||introElapsed>=flightStart(index)+.7f;
}
//---- 입은 만큼 세진다 ----
//
//판의 블록이 히어로에게 장비를 입히는데(updateHeroCostume), 전에는 그림만
//바뀌고 체력·방어·무기 값은 로비에서 끼고 온 것 그대로였다. 입은 장비로
//다시 센다. 블록이 안 앉은 부위는 끼고 온 것(wornEquip)으로 메우므로, 판이
//비어 있을 때가 바닥이고 블록은 그 위로만 올린다.
//
//공성전 상대 턴(gearTableOverride)은 성주의 몸이라 건드리지 않는다 - 성주의
//체력은 Siege::begin 이 따로 정한다.
//리뷰 픽스처가 체력을 손으로 박아 둘 때는 입은 장비로 다시 세지 않는다.
bool holdVitals=false;
long long heroHpHold=-1;   //반격을 여러 타로 나눠 띄우는 동안 체력 바가 한 번에 떨어지지 않게 잡아 둔다
namespace MonsterBoard{int hitCount();void ensure();}
//---- 방어막 통의 바닥: 실제로 낀 투구·갑옷의 장비 값 ----
//
//PS_ARMOR 는 쓰지 않는다. 거기엔 STR×3 + AGI 가 들어 있어 레벨이 오르면 체력(158)보다 훨씬 큰
//수(949)가 된다 - 본편에서는 레벨 차 방어 감소에 쓰는 수라 체력과 단위가 다르다. 여기서는 판 위
//갑옷 블록과 같은 단위(GetEquipPower)로 낀 투구·갑옷만 센다. 하체는 체력(PS_HPEQUIP)으로 간다.
//판의 갑옷 블록이 코스튬으로 입혀져도(updateHeroCostume) 여기엔 안 들어간다 - 로비에서 끼고 온 것(wornEquip)만.
long long wornGuard() {
    long long guard=0;
    for(int slot:{EQUIP_HELM,EQUIP_ARMOR}) if(wornEquip[slot].type!=EMPTY) guard+=std::max(0LL,GetEquipPower(&wornEquip[slot],std::max(1,(int)wornEquip[slot].lv)));
    return std::min(guard*(100+CastleTeamBonus(2))/100,1000000000000000LL);
}
void refreshHeroVitals() {
    if(holdVitals)return;
    OBJECT probe=hero;
    for(int g=0;g<GearCount;++g){
        const int slot=costumeSlots[g];
        if(!gearTableOverride&&probe.equip[slot].type==EMPTY)probe.equip[slot]=wornEquip[slot];
        //갑옷·투구 블록은 판 위에서 보호(protect)로 이미 센다. 코스튬으로 갈아입힌 것까지 PS_ARMOR 에
        //넣으면 같은 블록이 두 번 더해진다(★1 갑옷 21 이 42 로 보였다). 방어 부위는 실제로 낀 것만.
        if(DefensiveGear(Sword+g))probe.equip[slot]=wornEquip[slot];
    }
    static OBJECT savedPlayer;
    savedPlayer=ao[PLAYER];const int savedArmor=extraArmor;
    ao[PLAYER]=probe;RefreshStat(&ao[PLAYER]);probe=ao[PLAYER];
    ao[PLAYER]=savedPlayer;extraArmor=savedArmor;
    std::memcpy(hero.ps,probe.ps,sizeof(hero.ps));
    const long long hp=std::max(1LL,probe.ps[PS_HP]),armor=wornGuard();
    // Native attack includes the strongest worn glove; gloves have no independent turn.
    const long long weapon=std::max(1LL,std::min(probe.ps[PS_DMG],100000000LL));
    if(gearTableOverride){stats.weapon=weapon;return;}
    if(hp==stats.heroHealth&&armor==stats.heroArmor&&weapon==stats.weapon)return;
    stats.heroHealth=hp;stats.heroArmor=armor;stats.weapon=weapon;
    run.setVitals(hp,armor);
}
void updateHeroCostume(bool animate=true) {
    //공성전에서 런을 맞바꾸면 hero 는 성주이고 판도 성주의 것이다. 장비 표는
    //gearTableOverride 가 성주 라인을 가리키고, 단계 기억(costumeLevels)은
    //swapSides 가 같이 바꿔 준다. 그래서 여기는 누구 차례든 같은 코드다.
    const ITEM* table=gearTableOverride?gearTableOverride:&treeEquipment[0][0];
    int best[GearCount]={};
    for(int i=0;i<(int)run.board.size();++i){
        const Block& b=run.board[i];
        if(b.family>=Sword&&b.family<FamilyCount&&gridBlockLanded(i))
            best[b.family-Sword]=std::max(best[b.family-Sword],b.level);
    }
    bool upgraded=false,changed=false;
    for(int g=0;g<GearCount;++g)if(best[g]!=costumeLevels[g]){
        upgraded=upgraded||best[g]>costumeLevels[g];changed=true;
        costumeLevels[g]=best[g];
        if(g!=0||!attackWeaponLevel){
            const ITEM target=best[g]?table[g*MaxLevel+best[g]-1]:baseCostume[g];
            if(g!=0||!animate)hero.equip[costumeSlots[g]]=target;
            else requestWeaponSwap(target);
        }
    }
    if(upgraded&&animate)costumeEffectTicks=30;
    if(changed)refreshHeroVitals();
}
bool deckArriving() {
    if(deckMerge.time.running())return true;
    for(const auto& reveal:deckReveal)if(reveal.arriving())return true;
    return false;
}
void updateDeckReveal(int steps=1) {
    bool landed[64]={};
    for(int i=0;i<(int)run.board.size();++i) {
        const auto& b=run.board[i];
        if(b.family<MergeRoulette::Roles&&b.crew>=0&&b.crew<64&&gridBlockLanded(i))landed[b.crew]=true;
    }
    if(deckMerge.time.converging()&&!deckMerge.resultWasVisible)landed[deckMerge.result.crew]=false;
    for(int c=0;c<64;++c){
        const bool existing=deckReveal[c].age>=0;
        deckReveal[c].update(landed[c]);
        if(existing&&landed[c])deckReveal[c].age=std::min((int)MergeCombat::ResidentReveal::Duration,deckReveal[c].age+std::max(0,steps-1));
    }
}
int reviewCombatTick=-1,introCaptures=0,entryCaptures=0;
bool reviewCapturePending=false,reviewFinalCapture=false,reviewDone=false;
int mistReviewSample=0,mistReviewHold=0;
std::vector<std::string> reviewCaptureQueue;
constexpr float IntroDuration=3.8f;
bool introActive() {return introElapsed>=0&&introElapsed<IntroDuration;}
Shape castleShape(int stage) {return BattleShape(stage);}
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
    Box board, slot, lever, heart, spin, attack, cannon, exit, left, right, reroll, confirm;
    int plateH=0, plateDrop=0;   //유닛 패 높이와 데크 선에서 내려오는 거리. 판은 패 밑 ~ 릴 위 사이에 선다
};
Layout layout() {
    Layout l; l.scale=DX/640.0f;
    const float s=l.scale;
    // Everything below the scenery is anchored to the 640 x 850 baseline.
    // The castle contents share one responsive lift; bottom action buttons stay anchored.
    //하단은 3지선다 - 왼쪽 대포 · 가운데 공격 · 오른쪽 룰렛. 같은 폭으로 나란히.
    int margin=(int)(26*s),gap=(int)(10*s),bottom=(int)(12*s),bh=(int)(56*1.2f*s);
    const int bw3=(DX-margin*2-gap*2)/3;
    l.cannon={margin,bottom+bh,bw3,bh};
    l.attack={margin+bw3+gap,bottom+bh,bw3,bh};
    l.spin={margin+(bw3+gap)*2,bottom+bh,bw3,bh};
    if(siegeActive){
        const int left=(DX-(2*bw3+gap))/2;
        l.spin.x=left;l.attack.x=left+bw3+gap;
        l.cannon={0,0,0,0};
    }
    const int heartCols=std::min(10,heartCapacity),heartRows=(heartCapacity+heartCols-1)/heartCols;
    const int heartWidth=(heartCols*35+40)*s;
    l.heart={(DX-heartWidth)/2,(int)(156*s),heartWidth,(int)((heartRows*32+14)*s)};
    // RH's 512 x 218 board at a uniform 0.625 scale, with a right-hand lever.
    // 드럼 몸체는 판과 같은 세로축(DX/2)에 둔다. 레버는 오른쪽으로 튀어나오는 부속이라 가운데 계산에 넣지 않는다.
    l.slot={(DX-(int)(348*s))/2,(int)(280*s),(int)(348*s),(int)(116*s)};
    //레버는 없앴다(돌리기는 하단 룰렛 단추뿐). 자리만 남겨 두고 크기 0 - 어디를 눌러도 맞지 않는다.
    l.lever={l.slot.x+l.slot.w,l.slot.y,0,0};
    // Fixed resource scale: an 80-unit square never shrinks for rows or columns.
    // The top pair on castle ten occupies the gap between the health plates.
    l.plateH=(int)(84*s);l.plateDrop=(int)(8*s);
    const int groundBase=(int)(1076*DX/1089.f*1.04f)+(int)(40*s);
    l.cell=(int)(80*s);l.cellH=l.cell;
    const int bw=l.cell*run.shape.width,bhGrid=l.cellH*run.shape.height;
    //판은 릴 위(280)와 패 밑 사이의 가운데. 1:1.33 에서 네 줄 80칸(320)이 위아래 2~3픽셀을 남기고
    //들어가는데, 바닥을 286 에 못 박으면 윗변이 패 밑을 1픽셀 넘는다. 윗변을 패 밑으로 막는다.
    const int slotTop=(int)(280*s),platesBottom=groundBase-l.plateDrop-l.plateH,space=platesBottom-slotTop;
    const int boardBottom=std::min(slotTop+std::max(0,(space-bhGrid)/2),platesBottom-bhGrid);
    l.board={(DX-bw)/2,boardBottom+bhGrid,bw,bhGrid};
    //---- 공성전: 성의 크기는 내 판 기준으로 못 박는다 ----
    //
    //데크 높이(ground)가 판 높이에서 나오고 성은 그 높이로 커진다. 상대 턴에
    //48칸 판이 서면 성이 따라 커졌다. 기준 줄 수(내 성의 판)로만 데크를 잡고,
    //큰 판은 성 밖으로 삐져나가도 그대로 둔다. 성 번호도 무대의 성으로 본다.
    const int refBottom=(int)(561*s);
    l.arenaBottom=refBottom+(int)(76*s);
    l.ground=groundBase;
    const int lift=(int)castleSceneLift();
    l.board.y+=lift;l.arenaBottom+=lift;l.ground+=lift;
    l.slot.y+=lift;l.lever.y+=lift;l.heart.y+=lift;
    l.exit={(int)(10*s),DY-(int)(8*s),(int)(66*s),(int)(28*s)};   //왼쪽 위. 오른쪽 위는 몬스터 판 자리
    l.left={(int)(48*s),l.slot.y,(int)(36*s),l.slot.h};
    l.right={DX-(int)(84*s),l.slot.y,(int)(36*s),l.slot.h};
    l.reroll=l.spin;l.confirm=l.attack;
    return l;
}
// Batch each procedural widget without changing its pixel geometry or draw order.
struct SolidRects;
SolidRects* solidRects=nullptr;
struct SolidRects {
    std::vector<cocos2d::V3F_C4B_T2F> vertices;
    std::vector<unsigned short> indices;
    bool owns=false;
    SolidRects(){
        static const bool disabled=std::getenv("CS_MERGE_SLOW_RECTS")!=nullptr;
        if(!disabled&&!solidRects){solidRects=this;owns=true;vertices.reserve(256);indices.reserve(384);}
    }
    void add(int x,int y,int w,int h,int color){
        if(HitZoomOn()){HitZoomPoint(&x,&y);w=(int)(w*hitZoom);h=(int)(h*hitZoom);}
#ifdef CLIPPING
        if(x<clipX){w+=x-clipX;x=clipX;}if(x+w>clipX2)w=clipX2-x;
        if(y>clipY){h-=y-clipY;y=clipY;}if(y-h<clipY2)h=y-clipY2;
#endif
        if(w<=0||h<=0)return;
        const unsigned short first=(unsigned short)vertices.size();
        const unsigned char alpha=(unsigned char)(m_lgrpAlpha*255/32);
        const float tint=texture[MEMRECT_IMG]->hasPremultipliedAlpha()?alpha/255.f:1.f;
        const cocos2d::Color4B fill((unsigned char)(((color>>16)&255)*tint),(unsigned char)(((color>>8)&255)*tint),(unsigned char)((color&255)*tint),alpha);
        const float xy[4][2]={{(float)x,(float)y},{(float)(x+w),(float)y},{(float)(x+w),(float)(y-h)},{(float)x,(float)(y-h)}};
        const cocos2d::Tex2F uv(.5f/texture[MEMRECT_IMG]->getPixelsWide(),.5f/texture[MEMRECT_IMG]->getPixelsHigh());
        for(const auto& p:xy){cocos2d::V3F_C4B_T2F v;v.vertices={p[0],p[1],0};v.colors=fill;v.texCoords=uv;vertices.push_back(v);}
        for(int i:{0,1,2,0,2,3})indices.push_back(first+i);
    }
    ~SolidRects(){
        if(!owns)return;solidRects=nullptr;if(vertices.empty())return;
        if(!texture[MERGE_SOLID_RECTS_IMG]){texture[MERGE_SOLID_RECTS_IMG]=texture[MEMRECT_IMG];texture[MERGE_SOLID_RECTS_IMG]->retain();}
        LoadSpriteFromTexture(MERGE_SOLID_RECTS_IMG);
        auto* sp=renderSprite[getSpriteIdx];
        sp->setAnchorPoint({0,0});sp->setPosition({0,0});sp->setScale(1);sp->setColor(cocos2d::Color3B::WHITE);sp->setOpacity(255);
        cocos2d::TrianglesCommand::Triangles triangles;
        triangles.verts=vertices.data();triangles.indices=indices.data();triangles.vertCount=(int)vertices.size();triangles.indexCount=(int)indices.size();
        cocos2d::PolygonInfo info;info.setTriangles(triangles);info.setRect(cocos2d::Rect(0,0,(float)DX,(float)DY));
        sp->setPolygonInfo(info);AfterSpriting(sp);
    }
};
void mergeRect(int x,int y,int w,int h,int color){
    if(solidRects)solidRects->add(x,y,w,h,color);else MemRect(x,y,w,h,color);
}
void panel(const Box& b,int color,int border=0x61718C) {
    SolidRects batch;
    int p=std::max(1,DX/320);
    mergeRect(b.x-p,b.y+p,b.w+2*p,b.h+3*p,0x080E1B);
    mergeRect(b.x,b.y,b.w,b.h,border);
    mergeRect(b.x+p,b.y-p,b.w-2*p,b.h-2*p,color);
    mergeRect(b.x+2*p,b.y-2*p,b.w-4*p,p,0x7B7C80);
    mergeRect(b.x+p,b.y-b.h+p,b.w-2*p,p,0x151421);
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
    SolidRects batch;
    if(b.w<=0||b.h<=0)return;
    corner=std::min(corner,std::min(b.w,b.h)/2);
    mergeRect(b.x,b.y-corner,b.w,b.h-2*corner,color);
    for(int i=0;i<corner;++i) {
        int trim=corner-i;
        mergeRect(b.x+trim,b.y-i,b.w-2*trim,1,color);
        mergeRect(b.x+trim,b.y-b.h+i+1,b.w-2*trim,1,color);
    }
}
void mergeGoldFrame(Box b,int topColor,int bottomColor,bool enabled=true) {
    SolidRects batch;
    int p=std::max(1,DX/640);
    bevel({b.x,b.y-3*p,b.w,b.h+3*p},0x050916,12*p);
    bevel(b,enabled?0x8B4808:0x4B5369,12*p);
    bevel(inset(b,2*p),enabled?0xFFE48A:0x9EA5B3,10*p);
    bevel(inset(b,5*p),enabled?0xF7B517:0x646E81,7*p);
    bevel(inset(b,7*p),0x53350D,5*p);
    Box inner=inset(b,9*p);
    for(int y=0;y<inner.h;++y) {
        int trim=y<3*p?3*p-y:y>inner.h-3*p?y-inner.h+3*p:0;
        mergeRect(inner.x+trim,inner.y-y,inner.w-2*trim,1,blend(topColor,bottomColor,y/(float)inner.h));
    }
    mergeRect(b.x+14*p,b.y-3*p,b.w-28*p,p,enabled?0xFFF6B8:0xC1C8D0);
}
int grayOf(int c);
void heart(int x,int y,int size,bool filled,bool gray=false) {
    SolidRects batch;
    static const char* mask[]={
        "00111100111100","01111111111110","11111111111111","11111111111111",
        "11111111111111","11111111111111","01111111111110","00111111111100",
        "00011111111000","00001111110000","00000111100000","00000011000000"};
    float p=size/14.f;
    for(int row=0;row<12;++row) {
        auto colorAt=[&](int col) {
            if(col>=14||mask[row][col]!='1')return -1;
            bool edge=col==0||col==13||row==0||row==11||mask[row][col-1]=='0'||mask[row][col+1]=='0'||(row<11&&mask[row+1][col]=='0');
            const int c=edge?(filled?0x7D1527:0x8A8790):filled?blend(0xFF4B55,0xD71D2D,row/12.f):0x444754;
            return gray?grayOf(c):c;
        };
        for(int col=0;col<14;) {
            int color=colorAt(col),end=col+1;
            while(end<14&&colorAt(end)==color)++end;
            if(color>=0)mergeRect(x+(int)(col*p),y-(int)(row*p),std::max(1,(int)std::ceil(end*p)-(int)(col*p)),std::max(1,(int)std::ceil(p)),color);
            col=end;
        }
    }
    if(filled) {mergeRect(x+(int)(3*p),y-(int)(2*p),(int)(3*p),(int)(2*p),gray?grayOf(0xFFF0DC):0xFFF0DC);mergeRect(x+(int)(2*p),y-(int)(4*p),(int)(2*p),(int)p,gray?grayOf(0xFFA6A2):0xFFA6A2);}
}
void pixelStroke(int x,int y,int ax,int ay,int bx,int by,int width,int color,float p) {
    SolidRects batch;
    int count=std::max(std::abs(bx-ax),std::abs(by-ay));
    for(int i=0;i<=count;++i) {
        float t=count?i/(float)count:0;
        mergeRect(x+(int)((ax+(bx-ax)*t-width*.5f)*p),y-(int)((ay+(by-ay)*t-width*.5f)*p),
            std::max(1,(int)(width*p)),std::max(1,(int)(width*p)),color);
    }
}
void actionIcon(const Box& b,bool attack) {
    SolidRects batch;
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
            mergeRect(x+(int)((c-pad)*p),y-(int)((r-pad)*p),std::max(1,(int)std::ceil((1+2*pad)*p)),std::max(1,(int)std::ceil((1+2*pad)*p)),pass?0x91E7FF:0x071728);
        }
    }
}
void shield(int x,int y,int size) {
    SolidRects batch;
    float p=size/10.f;
    for(int r=0;r<12;++r) {
        int trim=r<2?2-r:r<7?0:(r-6)/2;
        mergeRect(x+(int)(trim*p),y-(int)(r*p),std::max(1,(int)((10-2*trim)*p)),std::max(1,(int)std::ceil(p)),0xDCE8ED);
        if(r>1&&r<10)mergeRect(x+(int)((trim+1)*p),y-(int)(r*p),std::max(1,(int)((8-2*trim)*p)),std::max(1,(int)std::ceil(p)),r<6?0x4EACF8:0x2366BB);
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
//
//[셋째 단은 공격]
//방어 · 체력 · 공격이 한 패에 위에서 아래로 선다. 전에는 공격력만 두 패
//사이에 따로 떠 있어서 누구 것인지 한 번 더 읽어야 했다. 적 패에도 같은
//단이 있어 "저놈이 이번에 얼마나 때리나" 가 같은 자리에서 보인다.
//패의 숫자는 어두운 테두리를 두른다. 바 색 위에 맨 숫자를 놓으면 묻힌다.
void outlinedNum(long long value,int x,int y,int align,float zoom) {
    const int t=std::max(1,(int)(DX/640.f*1.5f)),keep=baseColor;
    SetColor(0x070C20);
    const int dx[4]={-t,t,0,0},dy[4]={0,0,-t,t};
    for(int i=0;i<4;++i)DrawImageNum(value,x+dx[i],y+dy[i],NUM_FONT_NORMAL,align,0,false,false,zoom,false);
    SetColor(keep);
    DrawImageNum(value,x,y,NUM_FONT_NORMAL,align,0,false,false,zoom,false);
}
void unitPlate(const Box& plate,long long hp,long long max,long long guard,
    int barBg,int barFg,bool hot,double animatedGuard=-1,long long guardCapacity=1,double animatedHp=-1,
    long long attack=-1,double animatedAttack=-1,bool attackHot=false) {
    const float s=DX/640.f;

    const auto& f=MergeCastleArt::UiFrames[MergeCastleArt::UnitPlate];
    // Fit both dimensions explicitly so increasing height also thickens the skin and bars.
    artCut(MERGE_REBUILD_UI_IMG+MergeCastleArt::UnitPlate,f,plate);
    const int w=plate.w,h=plate.h,x=plate.x,y=plate.y;
    const int left=x+(int)(w*.075f),windowW=(int)(w*.85f),mark=std::max(14,(int)(20*s));
    const int barX=left+mark+(int)(3*s),barW=std::max(1,windowW-mark-(int)(4*s));
    const bool three=attack>=0;
    const int guardY=y-(int)(h*(three?.11f:.18f)),hpY=y-(int)(h*(three?.41f:.58f)),barH=std::max(1,(int)(h*(three?.2f:.27f)));
    if(three) {
        const int atkY=y-(int)(h*.71f);
        DrawIcon(ICON_EVENT_2SWORD,left-(int)(2*s),atkY+(int)((mark*1.2f-barH)*.5f)+(int)(2*s),mark*1.15f/ITEMICONSIZE,0x070C20,false,false,1.2f);
        mergeRect(barX,atkY,barW,barH,0x3A2222);
        mergeRect(barX,atkY,barW,barH,attackHot?0xE0603C:0xA8432A);
        mergeRect(barX,atkY,barW,std::max(1,(int)(2*s)),attackHot?0xFFD0A0:0xD98A6A);
        const long long shown=animatedAttack>=0?(long long)std::llround(animatedAttack):attack;
        const float atkZoom=std::min(.65f*s,(barW-4*s)/std::max(1.f,GetNumDx(shown,false,NUM_FONT_NORMAL,0,false,1.f,false)));
        outlinedNum(shown,barX+barW/2,atkY-(int)((barH-24*atkZoom)*.5f),CENTER,atkZoom);
    }
    shield(left,guardY+(int)((mark*1.2f-barH)*.5f),mark);
    heart(left,hpY+(int)((mark*12.f/14.f-barH)*.5f),mark,hp>0);
    mergeRect(barX,guardY,barW,barH,0x202938);
    const double visible=animatedGuard>=0?animatedGuard:(double)guard;
    const float fill=std::max(0.,std::min(1.,visible/std::max(1LL,guardCapacity)));
    if(fill>0) {
        const int width=std::max(1,(int)(barW*fill));
        mergeRect(barX,guardY,width,barH,0xE9B349);
        mergeRect(barX,guardY,width,std::max(1,(int)(2*s)),0xFFF0A0);
    }

    const float guardZoom=std::min(.65f*s,(barW-4*s)/std::max(1.f,GetNumDx(guard,false,NUM_FONT_NORMAL,0,false,1.f,false)));
    outlinedNum(guard,barX+barW/2,guardY-(int)((barH-24*guardZoom)*.5f),CENTER,guardZoom);
    mergeRect(barX,hpY,barW,barH,barBg);
    const double ratio=max>0?std::max(0.,std::min(1.,(animatedHp>=0?animatedHp:hp)/(double)max)):0.;
    if(ratio>0)mergeRect(barX,hpY,std::max(1,(int)(barW*ratio)),barH,barFg);
    const float digits=GetNumDx(hp,false,NUM_FONT_NORMAL,0,false,1.f,false)+GetNumDx(max,false,NUM_FONT_NORMAL,0,false,1.f,false);
    const float hpZoom=std::min(.65f*s,(barW-12*s)/std::max(1.f,digits));
    const float leftWidth=GetNumDx(hp,false,NUM_FONT_NORMAL,0,false,hpZoom,false),rightWidth=GetNumDx(max,false,NUM_FONT_NORMAL,0,false,hpZoom,false);
    const int numberY=hpY-(int)((barH-24*hpZoom)*.5f),numberX=(int)(barX+(barW-leftWidth-rightWidth-8*s)*.5f);
    outlinedNum(hp,numberX,numberY,LEFT,hpZoom);
    label("/",(int)(numberX+leftWidth+4*s),hpY-(int)((barH-15*s)*.5f),.62f,hot?0xFFB060:0xFFFFFF);
    outlinedNum(max,(int)(numberX+leftWidth+8*s),numberY,LEFT,hpZoom);
}
//판 위 방어구가 지금 주는 최대치. 공격 중에는 이미 쏜 블록까지만(바가 차례로 차 보이게).
long long currentGuardMax() {
    long long guard=run.baseArmor;
    if(!run.attacking) {
        for(int i=0;i<(int)run.board.size();++i)
            if(gridBlockLanded(i)&&DefensiveGear(run.board[i].family))guard+=run.armorOf(run.board[i],stats);
        return guard;
    }
    for(int i=0;i<run.nextShot&&i<(int)run.shots.size();++i)
        if(DefensiveGear(run.shots[i].block.family))guard+=run.armorOf(run.shots[i].block,stats);
    return guard;
}
//방어막 통의 현재값. 모델은 공격·턴 넘기기 때 새 방어구를 통에 넣으므로(settleGuard), 그 전에
//막 선 블록은 여기서 찬 채로 더해 보인다 - 모델이 곧 그렇게 셈한다.
long long currentGuard() {
    if(!run.realVitals)return currentGuardMax();
    const long long liveMax=currentGuardMax();
    return std::max(0LL,std::min(liveMax,run.guard+std::max(0LL,liveMax-run.guardMax)));
}
void floatingDamage(long long damage,bool enemy) {
    if(damage<=0)return;
    damagePause.begin();
    const float s=DX/640.f;
    const int x=enemy?(enemyBodyKnown?enemyBodyX:(int)(DX*.85f)):(allyBodyKnown?allyBodyX:(int)(DX*.66f));
    combatNumbers.push_back({"-"+std::to_string(damage),(float)x,(float)(layout().ground+68*s),enemy?0xFFE19A:0xFF9E91});
}
//방어막이 받아 낸 몫. 체력 숫자 조금 위, 방어막 색. 무적이나 "BLOCK" 은 없다 -
//막힌 것은 전부 방어막이 받은 것이고 그 수가 보인다.
void floatingAbsorbed(long long absorbed) {
    if(absorbed<=0)return;
    damagePause.begin();
    const float s=DX/640.f;
    const int x=allyBodyKnown?allyBodyX:(int)(DX*.66f);
    combatNumbers.push_back({"-"+std::to_string(absorbed),(float)(x-18*s),(float)(layout().ground+96*s),0x9ED6FF});
}
void updateGuardDisplay(float dt) {
    const long long power=std::max(0LL,hero.ps[PS_DMG]);
    if(!attackDisplayKnown){attackDisplay=MergeCombat::AnimatedValue();attackDisplay.set(power);attackDisplay.advance(1);attackDisplayKnown=true;}
    else {
        const long long increase=attackDisplay.set(power);
        if(increase>0&&!run.attacking){attackGain=increase;attackGainTime=1.5f;}
        attackDisplay.advance(dt);
    }
    attackGainTime=std::max(0.f,attackGainTime-dt);
    //방어막이 차면 뜨는 숫자(새 방어구가 선 몫, 턴이 돌며 채운 몫).
    const long long gained=guardDisplay.set(currentGuard());
    if(gained>0)combatNumbers.push_back({std::string("+")+std::to_string(gained),DX*.25f,(float)(layout().ground+18*DX/640.f),0xFFE795,0,true});
    guardDisplay.advance(dt);
    heroHealthDisplay.set(heroHpHold>=0?std::max(run.lives,heroHpHold):run.lives);heroHealthDisplay.advance(dt);
    enemyHealthDisplay.set(run.enemyHp);enemyHealthDisplay.advance(dt);
}
void imageNumber(long long value,int x,int y,float zoom,bool sign=false) {
    if(!sprite[NUM_IMG])LoadImg(NUM_IMG);
    const float signWidth=sign?24*zoom:0;
    const float width=GetNumDx(value,false,NUM_FONT_LARGE,0,false,zoom,false);
    DrawImageNum(value,x+(int)(signWidth*.5f),y,NUM_FONT_LARGE,CENTER,0,false,false,zoom,false);
    if(sign){
        if(!sprite[EFFECT_IMG])LoadImg(EFFECT_IMG);
        const int left=(int)(x-(width+signWidth)*.5f);
        if(value>=0)DrawImage(12*_2X,12*_2X,227*_2X,134*_2X,left,y-(int)(3*_2X*zoom),false,0,0,0,m_lgrpAlpha,zoom,sprite[EFFECT_IMG],EFFECT_IMG);
        else DrawImage(12*_2X,4*_2X,222*_2X,130*_2X,left,y-(int)(7*_2X*zoom),false,0,0,0,m_lgrpAlpha,zoom,sprite[EFFECT_IMG],EFFECT_IMG);
    }
}
void drawCombatNumbers() {
    const float s=DX/640.f;
    for(const auto& number:combatNumbers) {
        const float life=number.age/(float)MergeCombat::DamageNumberFrames;
        const float rise=(number.defense?25.f:38.f)*life*s;
        const float pop=number.age<8?1.2f-number.age*.025f:1.f;
        SetAlpha(number.age>48?std::max(0,32*(MergeCombat::DamageNumberFrames-number.age)/24):32);
        const float zoom=(number.defense?.90f:1.18f)*pop*s;
        const long long value=std::stoll(number.text);
        const float width=GetNumDx(value,false,NUM_FONT_LARGE,0,false,zoom,false)+24*zoom;
        const int numberX=(int)std::max(width*.5f+8*s,std::min(DX-width*.5f-8*s,number.x));
        SetColor(number.color);
        imageNumber(value,numberX,(int)(number.y+rise+18*zoom),zoom,true);
        SetColor(0);
        if(number.defense)label(u8"방어",numberX,(int)(number.y+rise+46*s),.56f,number.color);
    }
    SetAlpha(32);
}
//---- 쥔 블록의 도움말 ----
//
//판에서 장비나 동료를 집으면 그것이 무엇이고 얼마나 치는지, 무엇과 합쳐지는지를
//릴 자리에 적어 준다. 손가락이 판을 가리는 동안이라 릴이 가려져도 상관없다.
const char* traitName(int trait) {
    static const char* names[6]={u8"표식",u8"고무",u8"강타",u8"연타",u8"빙결",u8"지속"};
    return trait>=0&&trait<6?names[trait]:"";
}
const char* treeName(int f);
void drawHeldHelp(const Block& b,const Layout& l) {
    const float s=l.scale;
    const Box help={(int)(40*s),l.slot.y+(int)(8*s),DX-(int)(80*s),(int)(78*s)};
    panel(help,0x1A2433,0xE2BE74);
    char title[96],line[160],hint[96];
    const int lv=std::max(1,std::min((int)MaxLevel,b.level));
    Effects e;const Shot shot=run.evaluate(b,stats,e);
    if(b.family<Roles&&b.crew>=0&&b.crew<64) {
        const int npc=crewData[b.crew*CREWDATASIZE+CREWDATA_TYPE];
        std::snprintf(title,sizeof(title),u8"%s ★%d · %s형",textId[TEXT_MONSTERNAME_START+npc],lv,MergeTrees::RoleName[b.family]);
        std::snprintf(line,sizeof(line),u8"한 방 %lld · 특성 %s%s",(long long)shot.damage,traitName((int)stats.crew[b.crew].trait),lv>=5?u8" · 궁극기/소환":"");
    } else if(b.family>=Roles) {
        const int g=b.family-Sword;
        if(DefensiveGear(b.family)){
            const long long add=run.armorOf(b,stats),now=currentGuard();
            if(run.realVitals)std::snprintf(line,sizeof(line),u8"방어막 +%lld · 턴마다 +%lld 충전%s",add,std::max(1LL,add*Run::chargePctOf(b.family)/100),lv==2?u8" · 반격 반감":"");
            else std::snprintf(line,sizeof(line),u8"방어막 +%lld%s",add,lv==2?u8" · 반격 반감":"");
            (void)now;
        }
        else if(b.family==Gloves)std::snprintf(line,sizeof(line),u8"\uacf5\uaca9\ub825 \uc99d\uac00 \u00b7 \uc9c1\uc811 \uacf5\uaca9 \uc5c6\uc74c");
        else if(b.family==Boots)std::snprintf(line,sizeof(line),u8"공격 뒤 하트 +%d · 돌리기 +%d",MergeBoard::NeckHearts(lv),MergeBoard::NeckSpins(lv));
        else std::snprintf(line,sizeof(line),u8"피해 %lld (무기값 ×%d)",(long long)shot.damage,MergeBoard::GearMulOf(g,lv));
        std::snprintf(title,sizeof(title),u8"%s ★%d · %d×%d칸",treeName(b.family),lv,Wide(b),Tall(b));
    } else {title[0]=line[0]=0;}
    if(run.canGrow(b.family,lv))std::snprintf(hint,sizeof(hint),u8"같은 종류 ★%d 둘을 포개면 ★%d",lv,lv+1);
    else std::snprintf(hint,sizeof(hint),u8"최고 단 · 더 합쳐지지 않습니다");
    label(title,DX/2,help.y-(int)(6*s),.6f,0xFFE6B0);
    label(line,DX/2,help.y-(int)(30*s),.52f,0xF2F2F2);
    label(hint,DX/2,help.y-(int)(52*s),.46f,0xBFD3E8);
}
// Reuse the roulette housing's gold gear for the spin action.
void reelIcon(int x,int y,int size) {
    const int img=MERGE_REBUILD_UI_IMG+MergeCastleArt::Gear;
    if(!sprite[img])LoadImg(img);if(!sprite[img])return;
    const auto& frame=MergeCastleArt::UiFrames[MergeCastleArt::Gear];
    const float z=Min(size/(float)frame.w,size/(float)frame.h);
    const int px=x+(size-frame.w*z)/2,py=y-(size-frame.h*z)/2;
    const int t=std::max(1,(int)(2*DX/640.f)),keep=baseColor;
    SetColor(0x070C20);
    for(int dx=-1;dx<=1;++dx)for(int dy=-1;dy<=1;++dy)if(dx||dy)
        DrawImageScale(frame.w,frame.h,frame.x,frame.y,px+dx*t,py+dy*t,false,0,0,0,0,z,z,sprite[img],img);
    SetColor(keep);
    DrawImageScale(frame.w,frame.h,frame.x,frame.y,px,py,false,0,0,0,0,z,z,sprite[img],img);
}
void cannonIcon(int x,int y,int size) {
 const int c=std::max(0,std::min(9,siegeActive?(int)robin.castle:run.stage));
 const int lv=std::max(0,std::min(5,CastleVisualPartLevel(c,3)));
 DrawInventoryCannonIcon(c,lv,x-size/10,y+size/12,size*12/10,size*11/10);
}

enum ChoiceKind { ChoiceSpin=0, ChoiceAttack=1, ChoiceCannon=2 };
//색을 회색으로(밝기만 남긴다). 단추의 바탕·테두리는 그림이 아니라 네모 조각이라 grayScale
//플래그가 안 먹는다 - 색을 직접 바꾼다.
int grayOf(int c) {
    const int l=(((c>>16)&255)*30+((c>>8)&255)*59+(c&255)*11)/100;
    return (l<<16)|(l<<8)|l;
}
void choice(const Box& b,int kind,bool enabled) {
    const float s=DX/640.f;
    SetAlpha(32);grayScale=0;SetColor(0);
    static const int top[3]={0x1369D9,0xEC4A13,0x8A6A1E},bottom[3]={0x073B8D,0x8D1607,0x4A3708};
    //못 쓰는 단추는 통째로 회색이다 - 테두리·바탕·아이콘·하트·숫자 전부. 아이콘만 바래면
    //"눌리는데 왜 안 되지" 가 된다.
    mergeGoldFrame(b,enabled?top[kind]:grayOf(top[kind]),enabled?bottom[kind]:grayOf(bottom[kind]),enabled);
    const float center=b.y-b.h*.5f;
    grayScale=enabled?0:32;
    //아이콘 · 하트 · -1 을 단추 폭에 비례해 놓는다(세 단추가 같은 폭이라 같은 자리).
    const int iconSize=(int)(44*s),iconX=b.x+(int)(b.w*.16f),iconY=(int)(center+iconSize/2);
    if(kind==ChoiceAttack)DrawIcon(ICON_EVENT_2SWORD,iconX,(int)(center+23*s),46*s/ITEMICONSIZE,0x070C20,false,false,1.5f);
    else if(kind==ChoiceSpin)reelIcon(iconX,iconY,iconSize);
    else cannonIcon(iconX,iconY,iconSize);
    heart(b.x+(int)(b.w*.56f),(int)(center+15*s),(int)(29*1.2f*s),true,!enabled);
    imageNumber(-1,b.x+(int)(b.w*.86f),(int)(center+10*s),.55f*s,true);
    grayScale=0;
}
//대포 한 발의 값. 히어로 무기값 × 성 대포 단계 계수. 5단이 ★1 검 블록 두어 개 몫이라
//보조 화력(CLAUDE.md §5 지분 20%) 안에 든다. 공성전은 내 성의 대포다.
long long cannonShell() {
    
    const int c=std::max(0,std::min(9,siegeActive?(int)robin.castle:run.stage)),lv=std::max(0,std::min(5,CastleVisualPartLevel(c,3)));
    const long long base=stats.weapon*100/(100+CastleTeamBonus(0));
    return std::max(1LL,base*CastleMenuModel::CannonTurnPercent(lv)/100);
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
            imageNumber(-1,tx+(int)(15*s),b.y-(int)(b.h*.62f),.4f*s,true);
        } else label(sub,tx,b.y-b.h*.76f,.5f,enabled?0xE4D6BD:0x89909E);
    }
}
void reviewCapture(const char* name);
//공용 보상창(RewardPopup.inc). 단추만 합성 전투의 금테 단추로 그린다.
#include "RewardPopup.inc"
void rewardButton(int x,int y,int w,int h,const char* text){button({x,y,w,h},text,nullptr,0x1F5A3A,true);}
void save() {
    if(siegeActive)return;   //공성전은 디버그라 이어하기 저장을 남기지 않는다
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
    if(BossTier(wave)==3)hp*=WAVE_HP_BIGBOSS_MUL;
    else if(BossTier(wave)==2)hp*=WAVE_HP_MIDBOSS_MUL;
    else if(BossTier(wave)==1)hp*=WAVE_HP_SUBBOSS_MUL;
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
    //고유 동료: 지금 히어로의 몫만 사다리에 선다. 다른 히어로의 동료는 창고에 있어도 릴에 안 나온다.
    //리뷰 픽스처는 64명 전원을 전제로 짜여 있어 거르지 않는다.
    const int who=std::max(0,std::min(2,curHero));
    for(int c=0;c<64;++c)if(owned[c]&&(review||MergeTrees::OwnerHero(c)==who))roster.add(MergeTrees::Role(c),MergeTrees::Star(c),c);
    for(int r=0;r<Roles;++r)if(roster.has(r,1))pool.push_back(r);
    for(int f=Sword;f<FamilyCount;++f)pool.push_back(f);
    hero=ao[PLAYER];hero.type=std::max(0,std::min(2,curHero));
    if(hero.equip[EQUIP_WEAPON].type==EMPTY)
        std::memcpy(hero.equip,robin.charData[hero.type].equip,sizeof(hero.equip));
    // Menu entry may not have calculated PS_HP yet. RefreshStat identifies heroes
    // by their ao index, so refresh through the player slot and restore it afterwards.
    static OBJECT savedPlayer;
    savedPlayer=ao[PLAYER];const int savedArmor=extraArmor;
    ao[PLAYER]=hero;RefreshStat(&ao[PLAYER]);hero=ao[PLAYER];
    ao[PLAYER]=savedPlayer;extraArmor=savedArmor;
    std::memcpy(wornEquip,hero.equip,sizeof(wornEquip));
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
    //---- 칸 모양은 그림이 정한다 ----
    //
    //판은 그림을 모르므로 여기서 잰다. 가방이 쓰는 모양(GridGearPart)
    //그대로라 창고·가방·판에서 같은 검이 같은 칸을 차지한다. 투구처럼
    //한 칸짜리 그림은 ★ 이 올라도 한 칸이다.
    MergeBoard::ResetGearShapes();
    for(int g=0;g<GearCount;++g)for(int l=0;l<MaxLevel;++l) {
        int w=1,h=1;MergeBoardGearShape(&treeEquipment[g][l],&w,&h);
        MergeBoard::SetGearShape(g,l+1,w,h);
    }
    long long weapon=std::max(20LL,std::min(GetEquipPower(&hero.equip[EQUIP_WEAPON],hero.equip[EQUIP_WEAPON].lv),100000000LL));
    stats=Stats();stats.weapon=weapon;stats.realVitals=true;
    stats.heroHealth=std::max(1LL,hero.ps[PS_HP]);stats.heroArmor=wornGuard();
    for(int g=0;g<GearCount;++g)for(int level=0;level<MaxLevel;++level)
        if(DefensiveGear(Sword+g))stats.armor[g][level]=std::max(0LL,std::min(1000000000000000LL,GetEquipPower(&treeEquipment[g][level],treeEquipment[g][level].lv)));
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
void iconGround(const Box& box,int width,int lift=0,bool keepInside=false) {
    int p=std::max(1,(int)(DX/640.f)),cx=box.x+box.w/2;
    const int w=std::max(p,std::min(box.w-4*p,width));
    const float z=w/(float)(24*_2X);
    const int halfHeight=(int)std::ceil(8*_2X*z);
    const int baseline=keepInside?std::max(5*p+lift,halfHeight+2*p):5*p+lift;
    ShadowImage(24*_2X,16*_2X,1*_2X,1*_2X,cx-w/2,
        box.y-box.h+baseline+(int)(8*_2X*z),SHADOW_IMG,z);
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
float gridCrewZoomSeen[64]={};
void crewArt(int crew,const Box& box,float fraction,int footLift,int motionIn,int dir,float fixedZoom=-1.f) {
    if(crew<0||crew>=64)return;
    int npc=crewData[crew*CREWDATASIZE+CREWDATA_TYPE];
    int cmf=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF];
    if(cmf<0||cmf>=MAXCMF)return;
    if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);
    int motion=motionIn>=0?motionIn:crewPos[npc*5];
    if(motion<0||motion>=cmf_m_cnt[cmf])motion=crewPos[npc*5];
    const auto* bounds=cmfMotionImgSize[cmf]+motion*4;
    int p=std::max(1,(int)(DX/640.f));
    float z=fixedZoom>=0?fixedZoom:std::min((box.w-2*p)/(float)std::max(1,(int)bounds[2]),(box.h-7*p-footLift)/(float)std::max(1,(int)bounds[3]))*fraction;
    iconGround(box,std::max(box.w/2,(int)(bounds[2]*z*.85f)),footLift);
    DrawCmfDetail(cmf,motion,box.x+box.w/2,box.y-box.h+5*p+footLift+(int)(bounds[3]*z/2),dir,z,0,true);
}
void icon(int family,const Box& box,float fraction=0.96f,bool atlas=false,int level=1,int crew=-1,int footLift=0) {
    if(family<0||family>=FamilyCount)return;
    if(atlas)fraction*=1.10f; // Fill reel windows more; board artwork keeps its scale.
    SetColor(0);grayScale=0;
    if(family<Sword) {
        // 블록이 든 동료. 없으면(릴 회전·계열 카드) 그 역할·★ 의 대표 — 보유분 먼저, 없으면 표의 첫 사람.
        if(crew<0)crew=roster.first(family,std::max(1,std::min((int)MaxLevel,level)));
        if(crew<0)crew=MergeTrees::OwnedCrewAt(std::max(0,std::min(2,curHero)),family,std::max(1,std::min((int)MaxLevel,level)),0);
        if(crew<0)crew=MergeTrees::CrewAt(family,std::max(1,std::min((int)MaxLevel,level)),0);
        Box placement=box;
        if(atlas)placement.y+=std::max(1,(int)(6*DX/640.f));
                // Every grid companion uses one native sprite zoom. Bounds only
        // position its feet; neither character size nor tile shape changes zoom.
        const float gridZoom=1.5f*(DX/640.f);
        if(!atlas&&crew>=0&&crew<64)gridCrewZoomSeen[crew]=gridZoom;
        crewArt(crew,placement,fraction,footLift,-1,RIGHT,atlas?-1.f:gridZoom);
    } else {
        //공성전의 상대 판은 상대 히어로 라인의 장비로 그린다(gearTableOverride, MergeSiege.inc).
        const int lvAt=std::max(0,std::min(MaxLevel-1,level-1));
        ITEM item=gearTableOverride?gearTableOverride[(family-Sword)*MaxLevel+lvAt]:treeEquipment[family-Sword][lvAt];
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

            iconGround(box,w*3/4,footLift,true);
            MergeBoardDrawGear(&item,box.x+(box.w-w)/2,
                box.y-(box.h-h)/2-footLift,w,h,ALPHA_MAX,false);
        } else {
            const int size=(int)(std::min(box.w-2,box.h-7)*fraction);
            const int x=box.x+(box.w-size)/2,y=box.y-(box.h-size)/2;
            // Resolve live item data so old saved atlas IDs cannot replace gloves
            // with bracelets. Reels use icons; the board uses grid artwork.
            DrawIcon(GetItemIcon(item.type,item.detail,item.grade),x,y,size/(float)ITEMICONSIZE,false,false,false,true);
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
    b.y-=(int)((pulling?20:animation>REEL_SPIN_FRAMES-25?12:0)*l.scale);
    uiArt(MergeCastleArt::Lever,b);
}
void drawBlock(const Block& b,const Box& box,bool ghost=false) {
    int lv=std::max(1,std::min((int)MaxLevel,b.level));
    SetAlpha(ghost?16:32);padArt(lv+1,box);SetAlpha(32);
    Box artwork=inset(box,std::max(1,(int)(2*DX/640.f)));
    if(b.family<Roles)artwork.y+=(int)(12*DX/640.f);
    else artwork.y+=std::max(1,(int)(6*DX/640.f));
    icon(b.family,artwork,b.family<Roles?.90f:1.05f,false,b.level,b.crew,b.family<Roles?(int)(6*DX/640.f):0);
}
Box blockBox(const Block& b,const Layout& l) {
    return {l.board.x+b.x*l.cell,l.board.y-b.y*l.cellH,Wide(b)*l.cell,Tall(b)*l.cellH};
}
int trashSwallowTicks=0;
float trashOpenness=0;
Box rouletteTrash(const Layout& l){return {(int)(DX-84*l.scale),l.slot.y-(int)(12*l.scale),(int)(68*l.scale),(int)(76*l.scale)};}
bool nearRouletteTrash(const Layout& l,float x,float y){
    Box b=rouletteTrash(l);const int pad=(int)(16*l.scale);
    return x>=b.x-pad&&x<=b.x+b.w+pad&&y<=b.y+pad&&y>=b.y-b.h-pad;
}
void drawRouletteTrash(const Layout& l){
    const Box b=rouletteTrash(l);
    const bool hover=picked>=0&&nearRouletteTrash(l,pointerX,pointerY);
    const float target=hover||trashSwallowTicks>8?1.f:0.f;
    const float step=std::min(.25f,cocos2d::Director::getInstance()->getDeltaTime()*9);
    trashOpenness+=std::max(-step,std::min(step,target-trashOpenness));
    const int img=ROULETTE_TRASH_OBJECT_IMG;
    if(!sprite[img])LoadImg(img);if(!sprite[img])return;
    sprite[img]->getTexture()->setAntiAliasTexParameters();
    const auto dim=sprite[img]->getTexture()->getContentSizeInPixels();
    const int sw=(int)dim.width/2,sh=(int)dim.height,alpha=m_lgrpAlpha;
    const float pulse=trashSwallowTicks>0?1+.10f*std::sin(trashSwallowTicks/18.f*3.14159265f):1.f;
    Box art={b.x-(int)((pulse-1)*b.w/2),b.y+(int)((pulse-1)*b.h), (int)(b.w*pulse),(int)(b.h*pulse)};
    //외곽선. 아이콘과 같은 방법 - 그림을 한 색으로 네 방향 한 픽셀씩 밀어 찍고 그 위에 본그림.
    //통 그림만 두면 성 벽에 묻혀 어디가 버리는 자리인지 안 읽힌다.
    {
        const int t=std::max(1,(int)(1.5f*l.scale));static const int d[8]={-1,0,1,0,0,-1,0,1};
        const int sxSheet=trashOpenness<.5f?0:sw;
        SetColor(hover?0xFFC966:0x070C20);
        for(int i=0;i<4;++i)DrawImageScale(sw,sh,sxSheet,0,art.x+d[i*2]*t,art.y+d[i*2+1]*t,false,0,0,0,0,art.w/(float)sw,art.h/(float)sh,sprite[img],img);
        SetColor(0);
    }
    if(trashOpenness<1){SetAlpha((int)(alpha*(1-trashOpenness)));DrawImageScale(sw,sh,0,0,art.x,art.y,false,0,0,0,0,art.w/(float)sw,art.h/(float)sh,sprite[img],img);}
    if(trashOpenness>0){SetAlpha((int)(alpha*trashOpenness));DrawImageScale(sw,sh,sw,0,art.x,art.y,false,0,0,0,0,art.w/(float)sw,art.h/(float)sh,sprite[img],img);}
    SetAlpha(alpha);
}
bool beginSpinLanding(){
    spinLandingPlan=run;spinDrops.clear();
    const auto source=run.tray;
    for(const auto& item:source){
        const auto before=spinLandingPlan.board;
        if(!spinLandingPlan.autoPlace(0)){
            spinDrops.clear();message=u8"\uacb0\uacfc\ub97c \ubc30\uce58\ud558\uac70\ub098 \uc624\ub978\ucabd \uc4f0\ub808\uae30\ud1b5\uc5d0 \ubc84\ub824\uc8fc\uc138\uc694.";messageTime=3;return false;
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
//릴 i 가 서는 프레임(돌기 시작부터). 0 · 1 · 2 차례로, 마지막이 REEL_SPIN_FRAMES.
int reelStopFrame(int i){return REEL_SPIN_FRAMES-(2-i)*REEL_STOP_GAP;}
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
        int pitch=(int)(108*s);
        if(t<stop) {
            float distance=t-.375f*t*t/stop;
            int offset=(int)std::fmod(distance*(560+70*i)*s,(float)pitch);
            int index=(int)(t*(18+3*i));
            for(int j=-2;j<=2;++j) {
                int f=pool[(index+j+2+i*7)%pool.size()];
                SetSectionClip(reel.x,reel.y,reel.w,reel.h,false);
                Box symbol=reel;symbol.y+=j*pitch-offset;
                icon(f,symbol,.91f,true);
            }
        } else {
            //릴이 든 사람은 트레이에 떨어질 그 사람이다. 전에는 board[i]
            //의 동료를 가져왔는데, 그 칸은 이 릴과 아무 상관이 없다 -
            //서는 순간 엉뚱한 사람으로 갈렸다.
            reelResultDrawn[i]=true;
            icon(run.families[i],reel,.94f,true,1,
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
            SetAlpha(18/k);mergeRect(px,py,std::max(1,(int)(4*s)),std::max(1,(int)(4*s)),0xFFE79A);
        }
        SetAlpha(32);icon(run.board[i].family,{cx-w/2,cy+h/2,w,h},.94f,false,run.board[i].level,run.board[i].crew);
    }
    SetAlpha(32);
}
TurretAttack::Sequence turretFire;
#include "MergeCastleLobbyRebuild.inc"
//---- 지금 치고 있는 자리 ----
//
//피해는 판이 아니라 **사람에게서** 출발한다. 판에서 날아오면 누가 친
//것인지 안 보인다. 데크에서 한 발 나온 그 자리를 여기 적어 두고,
//날아가는 그림이 그 점에서 시작한다.
int shotFromX=0,shotFromY=0,deckResidentCount=0;

//---- 치는 자세 ----
//
//스테이지 전투와 같은 표를 본다(enemyAttackPattern 의 THERE = 원거리
//자세). 자세가 없는 동료는 -1 - 그 자리에서 쉬는 자세로 둔다.
int combatRegion() {
    if(review&&std::getenv("CS_MIST_RESOURCE_REVIEW")&&mistReviewSample>=20)return std::min(14,mistReviewSample-20);
    //공성전은 상대의 성이 무대라 원경도 상대가 가는 지역이다.
    if(siegeActive&&Siege::region>=0)return Siege::region;
    const int stage=siegeActive?Siege::castle:run.stage;
    return StageBg::DebugRegionPick()>=0?StageBg::DebugRegionPick():(stage/STAGE_PER_CYCLE)%STAGEBG_REGION_CNT;
}
//---- 지역별 적 배치 (15웨이브) ----
//
//한 성은 15웨이브다. 1~4 · 6~9 · 11~14 가 잡몹, 5 · 10 · 15 가 보스. 잡몹은
//지역의 네 종류를 앞에서부터 둘씩 차례로 내보내고(1·2 → A, 3·4 → B, 6·7 → B,
//8·9 → C, 11·12 → C, 13·14 → D), 보스는 지역의 소·중·대 보스다.
//지역은 열 성마다 바뀌므로(STAGE_PER_CYCLE) 같은 지역 안에서는 1~4성 기본색,
//5~8성 레드, 9~10성 블루로 색을 갈아 열 성이 같은 얼굴로 보이지 않게 한다.
//종류는 그림과 덩치만 정한다 - 체력·공격은 waveHp / waveAttack 이 정한다.
struct RegionRoster { short normal[4]; short boss[3]; };
static const RegionRoster kRegionRoster[STAGEBG_REGION_CNT]={
    {{ENEMY_SNAIL,ENEMY_SLIME,ENEMY_JELLYFISH,ENEMY_LARVA},{ENEMY_ONEEYE,ENEMY_TREE,ENEMY_FROG}},              //늪지대
    {{ENEMY_SLING,ENEMY_BOAR,ENEMY_SPIDER,ENEMY_LARVA},{ENEMY_GOLEM,ENEMY_SALAMANDER,ENEMY_DARKDRAGON}},       //금단의 계곡 (웜)
    {{ENEMY_LIZARD,ENEMY_JELLYFISH,ENEMY_FROG,ENEMY_GHOST},{ENEMY_SPACE1,ENEMY_FOGRA,ENEMY_BAHAMUT}},         //아틀란티스
    {{ENEMY_SLIME,ENEMY_SPIDER,ENEMY_SKELETON,ENEMY_LARVA},{ENEMY_GOLEM,ENEMY_KIMERA,ENEMY_MACHINE}},         //지하수로 (가시 갑주 짐승)
    {{ENEMY_SLING,ENEMY_BOAR,ENEMY_KNIGHT,ENEMY_SKELETON},{ENEMY_CASTLE2,ENEMY_DARKGIANT,ENEMY_GIANT}},       //아델라인 평원 (갑주 거인)
    {{ENEMY_FLAME,ENEMY_SALAMANDER,ENEMY_BOAR,ENEMY_SLING},{ENEMY_PHOENIX,ENEMY_DRAGON1,ENEMY_IFRIT}},        //화염지대 (화염 정령)
    {{ENEMY_SNOWMAN,ENEMY_SLIME,ENEMY_JELLYFISH,ENEMY_GHOST},{ENEMY_ICESUN,ENEMY_FACE,ENEMY_MAMMOTH}},        //얼음지대 (얼음 갑각)
    {{ENEMY_LIGHTNING,ENEMY_THUNDER,ENEMY_CRYSTAL,ENEMY_SPACE1},{ENEMY_SPACE2,ENEMY_KIMERA,ENEMY_MACHINE}},   //번개지대
    {{ENEMY_FAIRY,ENEMY_CIRCLE,ENEMY_CRYSTAL,ENEMY_LIGHTNING},{ENEMY_SPACE1,ENEMY_ANGEL,ENEMY_GIANT}},         //빛의지대 (금빛 수호자)
    {{ENEMY_SPIDER,ENEMY_BOAR,ENEMY_SLING,ENEMY_SKELETON},{ENEMY_DARKGIANT,ENEMY_CASTLE2,ENEMY_GOLEM}},       //골렘협곡
    {{ENEMY_THUNDER,ENEMY_GHOST,ENEMY_SKELETON,ENEMY_CIRCLE},{ENEMY_CASTLE1,ENEMY_PUMPKIN,ENEMY_KIMERA}},     //어둠의 협곡 (어둠 괴수)
    {{ENEMY_SALAMANDER,ENEMY_PHOENIX,ENEMY_BOAR,ENEMY_SPIDER},{ENEMY_DRAGON1,ENEMY_DRAGON2,ENEMY_BAHAMUT}},   //드래곤 협곡
    {{ENEMY_GHOST,ENEMY_PUMPKIN,ENEMY_SKELETON,ENEMY_KNIGHT},{ENEMY_CASTLE1,ENEMY_DRAGON2,ENEMY_DEATH}},      //망자의 도시 (사신)
    {{ENEMY_SKELETON,ENEMY_KNIGHT,ENEMY_CASTLE2,ENEMY_CASTLE1},{ENEMY_CASTLE_BOSS1,ENEMY_CASTLE_BOSS2,ENEMY_CASTLE_BOSS4}}, //마왕성
    {{ENEMY_SPACE1,ENEMY_CIRCLE,ENEMY_FAIRY,ENEMY_CRYSTAL},{ENEMY_SPACE2,ENEMY_ANGEL,ENEMY_BAHAMUT}},          //우주 (보이드 레비아탄)
};
//시험용: 첫 웨이브부터 그 지역의 최종 보스를 내보낸다. 보스 그림·덩치·배치를 바로 보려고.
//끄려면 false. 체력과 공격은 1웨이브 값 그대로다(waveHp 는 건드리지 않는다).
bool debugFirstBoss=true;
bool combatEnemyIsBoss(){return BossTier(run.wave)>0||(debugFirstBoss&&run.wave==0);}
int reviewEnemyNpc=-1;
int combatEnemyNpc() {
    if(review&&reviewEnemyNpc>=0)return reviewEnemyNpc;
    const int region=std::max(0,std::min(STAGEBG_REGION_CNT-1,combatRegion()));
    const RegionRoster& r=kRegionRoster[region];
    const int w=std::max(0,std::min(WavesPerStage-1,run.wave));
    const int boss=debugFirstBoss&&w==0?3:BossTier(w);
    int type;
    if(boss)type=r.boss[boss-1];
    else{const int slot=w<4?w/2:w<9?1+(w-5)/2:2+(w-10)/2;type=r.normal[std::max(0,std::min(3,slot))];}
    //색 변형: 같은 번호가 레드 +51, 블루 +102 다(enemy.tsv).
    const int variant=std::max(0,std::min(2,(run.stage%STAGE_PER_CYCLE)/4));
    const int colored=type+variant*51;
    return colored<gTotalEnemy?colored:type;
}
//---- 웨이브마다의 체력과 공격 ----
//
//성의 기준 체력(hpFor(stage,0) = 330 × 1.17^성)에 웨이브 배율을 곱한다.
//  잡몹: 1웨이브 50% → 14웨이브 180% (한 웨이브에 10%p). 판은 성 안에서 이어지므로
//        합성이 쌓이는 속도(한 번 돌리면 ★1 셋, 둘을 포개면 ×2~3)와 같은 기울기다.
//  보스: 그 자리 잡몹의 소 ×2 · 중 ×2.5 · 대 ×3. 룰렛 두세 번 더 돌리고 두세 번
//        치면 넘어가는 크기다. 옛 ×5/×10/×100 은 실시간 전투의 수치라 턴제엔 맞지 않는다.
//공격은 그 웨이브 잡몹 체력의 1/14 - 보스는 counterDamage 가 다시 두 배로 친다.
//1성 기준 잡몹 165 → 594, 보스 594 · 1,155 · 1,881, 공격 12 → 42(최종 보스 반격 84).
long long waveHp(int stage,int wave) {
    const int w=std::max(0,std::min(WavesPerStage-1,wave)),boss=BossTier(w);
    const long long base=hpFor(stage,0),pct=50+10*w,mul=boss==3?300:boss==2?250:boss==1?200:100;
    return std::max(1LL,base*pct/100*mul/100);
}
long long waveAttack(int stage,int wave) {
    const int w=std::max(0,std::min(WavesPerStage-1,wave));
    return std::max(1LL,hpFor(stage,0)*(50+10*w)/100/14);
}
void drawWaveHeader(const Layout& l) {
    const float s=l.scale;
    //제목 한 줄과 웨이브 점 한 줄뿐이다. 아래 설명 글은 뺐고 높이도 그만큼(80 → 58) 줄였다.
    const Box header={DX/2-(int)(205*s),DY-(int)(7*s),(int)(410*s),(int)(58*s)};
    panel(header,0x142B38,0x9E925D);
    char text[128];
    std::snprintf(text,sizeof(text),"%s · 스테이지 %d",StageBg::RegionName(combatRegion()),run.stage%STAGE_PER_CYCLE+1);
    label(text,DX/2,header.y-(int)(7*s),.76f);
    const int pitch=(int)(23*s),left=DX/2-(WavesPerStage-1)*pitch/2;
    for(int i=0;i<WavesPerStage;++i) {
        const bool boss=BossTier(i)>0,current=i==run.wave,cleared=i<run.wave;
        const int size=(int)((boss?20:14)*s),cx=left+i*pitch,top=header.y-(int)(33*s);
        const Box node={cx-size/2,top,size,size};
        bevel(node,current?0xFFF1A8:cleared?0x89DBA0:boss?0xC5A2D5:0x6E8391,std::max(1,(int)(3*s)));
        bevel(inset(node,std::max(1,(int)(2*s))),current?0xBB771A:cleared?0x286B49:BossTier(i)==3?0x78313E:boss?0x49355E:0x233844,std::max(1,(int)(2*s)));
        if(boss){std::snprintf(text,sizeof(text),"%d",i+1);DrawImageNum(i+1,cx,top,NUM_FONT_SMALL,CENTER,0,false,false,.58f*s,false);}
    }
}
struct EnemyTurn {
    bool started=false,complete=false,endShown=false;
    int endFrames=0;
    long long damage=0;
    long long rawDamage=0,healing=0;
    const MonsterParts::ActionDef* definition=nullptr;
    std::vector<const MonsterParts::ActionDef*> weaponActions;
    std::vector<int> weaponStarts;
    std::vector<long long> rawShares;
    std::vector<int> motion;   //공격 동작(패턴의 1열)
    std::vector<int> walk;     //다가가는 동작(패턴의 0열). 비어 있으면 제자리에서 친다(원거리)
    std::vector<int> back;     //돌아오는 동작(패턴의 2열). 비어 있으면 walk 를 거꾸로 쓴다
    std::vector<float> walkDistance,backDistance;
    std::vector<int> rest;
    MergeCombat::EnemyPattern pattern;
    float homeX=0,attackX=0;
    bool moves=false,prepares=false;
    MergeCombat::EnemyPhases phases;
    MergeCombat::Timeline time;
    // Authored action hits: 공격 동작을 hits 번 되풀이하고 impacts[k] 프레임에 k 번째 몫을 띄운다.
    //모델은 첫 타에 한 번만 깎는다(counterattack). 나머지는 보여 주는 몫이다.
    int hits=1,hitsShown=0;std::vector<int> impacts;std::vector<long long> shares,absorbedShares;
    long long hpBefore=0;
} enemyTurn;
int renderedEnemyX=0,renderedEnemyMotion=0,renderedEnemyDir=LEFT;
bool renderedEnemyWalking=false;
int allyFlash=0;
// Legacy pattern columns: approach, attack, return, rest, hit count, attack range.
// Resolve all phases from the table and stop at range * actor zoom, as ENEMYMOVETURN did.
int enemyPatternTurn=0,enemyPatternNpc=-1,enemyPatternStage=-1,enemyPatternWave=-1;
int monsterHeroX(const Layout& l){return std::max((int)(235*l.scale)+(int)(30*l.scale),(int)(DX*.66f))-(int)(32*l.scale);}
float monsterZoom(const Layout& l,int npc,int cmf){
    const auto* bounds=cmfMotionImgSize[cmf]+crewPos[npc*5]*4;
    const int y=l.ground+(int)(8*l.scale);
    return std::min(1.35f*l.scale,std::max(.3f*l.scale,(DY-y-8*l.scale)/std::max(1,(int)bounds[3])));
}
static void statusFrames(int cmf,int status,std::vector<int>& out,std::vector<float>* distance){
    if(status<0||status>=MAXSTATUS)return; // status 0 is a valid authored neutral state.
    const signed short* st=cmf_status_data[cmf][status];
    if(!st||st[0]<=0)return;
    const int frames=st[0];
    if(distance)distance->push_back(0);
    for(int i=0;i<frames;++i){
        if(st[2+i]<0||st[2+i]>=cmf_m_cnt[cmf])continue;
        out.push_back(st[2+i]);
        if(distance)distance->push_back(distance->back()+std::abs((int)st[2+frames+i]));
    }
}
MergeCombat::EnemyPattern nativeEnemyPattern(int npc,int cmf,int turn){
    const auto* row=enemyAttackPattern+npc*ATTACKPATTERNTOTALDATASIZE;
    int validMask=0;
    for(int i=0;i<3;++i){
        std::vector<int> motion;statusFrames(cmf,row[2+i*ATTACKPATTERNDATASIZE+1],motion,nullptr);
        if(!motion.empty())validMask|=1<<i;
    }
    // Some legacy colour variants reference states that their shared CMF does not
    // contain (e.g. MACHINE_RED's centre laser). Only schedule playable patterns.
    return MergeCombat::enemyPattern(row,turn,validMask);
}
#include "MergeMonsterAttack.inc"
int heroNeutralMotion(OBJECT& who,int div=1) {
    // Diana's interpolated in-between poses jitter the gun and hands. Keep the
    // authored neutral key poses with a steady eight-tick hold on both PVP sides.
    const int idleFrame=who.cmf==DIANA?(ticks/8%4)*4:ticks/std::max(1,div);
    const int loop=GetHeroLoopMotion(who.cmf,HEROLOOP_NEUTRAL,idleFrame);
    return loop>=0?loop:motionData[0]+(ticks/6)%4;
}
struct CombatAction {
    int index=-1,skill=-1,kind=-1,crewFrames=0,heroStart=0,heroHit=0;
    int bulletIcon=-1,bulletX=0,bulletY=0,emitterX=0,emitterY=0;
    bool emitterReady=false;
    OBJECT caster;
    std::vector<int> crewMotion,heroMotion,heroEvents,heroSounds;
    MergeCombat::Timeline time;
} action;

int actionSkill(const Block& block) {
    if(block.family>=Roles||block.crew<0||block.crew>=64)return -1;
    const int band=block.level<=2?0:block.level<=4?1:2;
    const int skill=crewData[block.crew*CREWDATASIZE+CREWDATA_SKILL1+band];
    return skill>=0&&skill<gTotalSkill?skill:-1;
}
void requestHeroAction(int requestSkill,bool summoned) {
    action.caster=hero;
    int skill=requestSkill>=0?SkillHeroSkill(requestSkill):-1;
    int type=hero.type;
    if(requestSkill>=0)type=summoned?SkillSummonHeroType(requestSkill):SkillHostObj(requestSkill);
    if(type<ROBIN||type>MAXX)type=hero.type;
    action.caster.type=action.caster.cmf=type;
    if(cmfLoaded[type]!=type)CmfRead(type,type);
    if(type!=hero.type)std::memcpy(action.caster.equip,robin.charData[type].equip,sizeof(action.caster.equip));
    action.caster.currentSkill=skill;
    const int attack=skill>=0?SkillAttackType(skill):ATTACK_NORMAL;
    action.caster.attack=attack;
    // Same skill request and motion script used by the roulette hero's HotKeyPress.
    // Local presentation owns its damage events; it must not mutate the paused ao[] world.
    const auto* oldMotion=skillMotion;const auto* oldStart=skillStartFrame;const auto* oldEnd=skillClosingFrame;
    GetMotionPtr(&action.caster);
    const int count=type==MAXX?22:23;
    if(attack>0&&attack<count) {
        const int first=skillStartFrame[attack],last=skillClosingFrame[attack];
        for(int f=first;f<=last;++f) {
            action.heroMotion.push_back(skillMotion[f*4]);
            action.heroEvents.push_back(skillMotion[f*4+2]);
            action.heroSounds.push_back(skillMotion[f*4+3]);
            if(skillMotion[f*4+2])action.heroHit=(f-first+1)*MOTIONDIV;
        }
    }
    skillMotion=oldMotion;skillStartFrame=oldStart;skillClosingFrame=oldEnd;
    if(action.heroMotion.empty())action.heroMotion.push_back(motionData[32]);
    if(!action.heroHit)action.heroHit=std::max(1,(int)action.heroMotion.size()*MOTIONDIV/2);
}
void beginCombatAction() {
    action=CombatAction();action.index=run.nextShot;
    const Block& block=run.shots[action.index].block;
    if(block.family<0) {
        const int c=siegeHullStage>=0?siegeHullStage:std::max(0,std::min(9,run.stage));
        turretFire.begin(c,CastleVisualPartLevel(c,3));
        const auto muzzle=cannonMuzzle(layout(),c,siegeActive&&Siege::swapped,turretFire.release);
        action.emitterX=(int)muzzle.x;action.emitterY=(int)muzzle.y;
        action.emitterReady=true;
        shotFromX=action.emitterX;shotFromY=action.emitterY;
        action.time.begin(turretFire.end()-14,turretFire.release,turretFire.impact()-turretFire.release,14);
        animation=action.time.end;
        return;
    }
    // Prepare the native attack in the target costume, but display it only at attachment.
    const ITEM previousWeapon=hero.equip[EQUIP_WEAPON];
    if(block.family==Sword)showAttackWeapon(block.level);
    action.skill=actionSkill(block);action.kind=action.skill>=0?SkillKind(action.skill):-1;
    if(block.family<Roles&&block.crew>=0&&block.crew<64) {
        const int npc=crewData[block.crew*CREWDATASIZE+CREWDATA_TYPE];
        const int cmf=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF];
        if(cmf>=0&&cmf<MAXCMF) {
            if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);
            const int band=block.level<=2?0:block.level<=4?1:2;
            int previous=-1;
            for(int phase=HERE;phase<=COMING;++phase) {
                int status=enemyAttackPattern[npc*ATTACKPATTERNTOTALDATASIZE+2+ATTACKPATTERNDATASIZE*band+phase];
                if(!status)status=enemyAttackPattern[npc*ATTACKPATTERNTOTALDATASIZE+2+phase];
                if(status<=0||status>=MAXSTATUS||status==previous)continue;
                const short* st=cmf_status_data[cmf][status];
                if(!st||st[0]<=0)continue;
                for(int i=0;i<st[0];++i)if(st[2+i]>=0&&st[2+i]<cmf_m_cnt[cmf])action.crewMotion.push_back(st[2+i]);
                previous=status;
            }
            if(action.crewMotion.empty())action.crewMotion.assign(24,crewPos[npc*5]);
        }
        action.crewFrames=std::max(24,(int)action.crewMotion.size());
    }
    const bool heroRequest=action.kind==HEROSKILL||action.kind==SUMMONHERO;
    const bool gearAttack=block.family==Sword;
    int release=std::max(1,action.crewFrames/2),motionEnd=action.crewFrames,flight=0;
    if(heroRequest||gearAttack) {
        action.heroStart=action.crewFrames;
        requestHeroAction(heroRequest?action.skill:-1,action.kind==SUMMONHERO);
        motionEnd=action.heroStart+(int)action.heroMotion.size()*MOTIONDIV;
        release=action.heroStart+action.heroHit;
    } else if(block.family<Roles) {
        // Ordinary companion attacks use the same projectile icon/animation as roulette.
        if(action.kind==CREWBULLET||action.kind==CREWSUMMON)action.bulletIcon=SkillBulletIcon(action.skill);
        if(action.bulletIcon>=0)release=std::max(release,MergeCombat::BulletSpawnFrames+6);
        flight=action.bulletIcon>=0?36:0;
    } else motionEnd=release=30;
    action.time.begin(motionEnd,release,flight);
    if(gearAttack){
        const ITEM target=hero.equip[EQUIP_WEAPON];
        hero.equip[EQUIP_WEAPON]=previousWeapon;
        requestWeaponSwap(target);
    }
    animation=action.time.end;
}
int crewAttackMotion(int npc,int cmf,float) {
    if(action.index<0||action.crewMotion.empty()||action.time.elapsed>=(int)action.crewMotion.size())return -1;
    const int at=std::min((int)action.crewMotion.size()-1,action.time.elapsed);
    const int motion=action.crewMotion[at];
    return motion>=0&&motion<cmf_m_cnt[cmf]?motion:-1;
}
void drawDeckShadow(int cmf,int x,int y,float zoom) {
    // Same shadow atlas and large-monster sizing as DrawCmfDetailShadow.
    const bool big=IsBigCmf(cmf);
    ShadowImage((big?40:24)*_2X,16*_2X,(big?26:1)*_2X,1*_2X,
        x-(int)((big?20:12)*_2X*zoom),y+(int)(8*_2X*zoom),SHADOW_IMG,zoom);
}
namespace Siege{void drawFoe(const Layout& l,int ex,int ey);}
// All artillery uses its private textures and mirrored launch/flight/impact sequences.
void drawImpactSequence(int first,int count,int age,int duration,int x,int y,int direction,float scale){
 if(age<0||age>=duration)return;
 const int pose=std::min(count-1,age*count/std::max(1,duration));
 DrawEffect(1000+first+pose,x,y,direction,0,scale);
}
int impactFirst=HIT_ITEM_SMALL0,impactCount=5;
void drawTurretAttack(const Layout& l,int targetX,int targetY){
 if(!turretFire.running()||!action.emitterReady)return;
 const float scale=l.scale;
 const TurretAttack::Point from={(float)action.emitterX,(float)action.emitterY},to={(float)targetX,(float)targetY};
 const int age=turretFire.age;
 if(turretFire.type==TurretAttack::Laser||turretFire.type==TurretAttack::Magnetic){
  const int charge=turretFire.release,alpha=m_lgrpAlpha;
  // The red, silver, violet and gold castles each color their own hot aura.
  static const int tones[4]={0xFF682B,0x69CDFF,0xB85AFF,0xFFD363};
  const int tone=tones[std::max(0,std::min(3,turretFire.castle-6))];
  auto glow=[&](float x,float y,float radius,int color,int opacity){
   SetAlpha(opacity);
   const int r=std::max(1,(int)radius);
   for(int row=-r;row<=r;++row){
    const float q=row/(float)r;
    const int half=std::max(1,(int)(r*std::sqrt(std::max(0.f,1-q*q))));
    mergeRect((int)x-half,(int)y+row,half*2,1,color);
   }
   SetAlpha(alpha);
  };
  auto electricLine=[&](float x1,float y1,float x2,float y2,float width,int color,int opacity){
   const int img=TURRET_FLAME_LASER_IMG;
   if(!sprite[img])LoadImg(img);if(!sprite[img])return;
   const auto dim=sprite[img]->getTexture()->getContentSizeInPixels();
   const float dx=x2-x1,dy=y2-y1,len=std::sqrt(dx*dx+dy*dy);
   SetAlpha(opacity);
   turretPart(img,0,(int)(dim.height*3/8),(int)dim.width,(int)dim.height/4,
    {(int)((x1+x2-len)*.5f),(int)((y1+y2+width)*.5f),std::max(1,(int)std::ceil(len)),std::max(1,(int)width)},-std::atan2(dy,dx)*57.2957795f);
   renderSprite[getSpriteIdx]->setColor(cocos2d::Color3B((color>>16)&255,(color>>8)&255,color&255));
   SetAlpha(alpha);
  };
  if(age<charge){
   const float t=age/(float)charge,r=(4+18*t)*scale;
   glow(from.x,from.y,r*1.55f,tone,alpha/5);
   glow(from.x,from.y,r,tone,alpha*3/4);
   glow(from.x,from.y,r*.48f,0xFFF8E4,alpha);
   for(int i=0;i<8;++i){
    const float phase=std::fmod(age*.09f+i*.125f,1.f);
    const float a=i*.78539816f+age*.06f;
    const float distance=(26+(1-phase)*32)*scale;
    glow(from.x+std::cos(a)*distance,from.y+std::sin(a)*distance,(1+phase*2)*scale,tone,alpha*(.4f+phase*.6f));
   }
   if(turretFire.castle==8){
    for(int arc=0;arc<5;++arc){
     const float a=arc*1.256637f+age*.17f;
     const float outer=(36-8*t)*scale,inner=(12+8*t)*scale;
     const float x=from.x+std::cos(a)*outer,y=from.y+std::sin(a)*outer;
     const float mx=from.x+std::cos(a+.24f)*inner,my=from.y+std::sin(a+.24f)*inner;
     electricLine(x,y,mx,my,3*scale,0xD5A2FF,alpha);
     electricLine(mx,my,from.x,from.y,2*scale,0xF9EEFF,alpha);
    }
   }
   return;
  }
  if(turretFire.type==TurretAttack::Laser){
  const int img=TURRET_FLAME_LASER_IMG;
  if(!sprite[img])LoadImg(img);if(!sprite[img])return;
  const auto dim=sprite[img]->getTexture()->getContentSizeInPixels();
  sprite[img]->getTexture()->setAntiAliasTexParameters();
  const float dx=to.x-from.x,dy=to.y-from.y,length=std::sqrt(dx*dx+dy*dy);
  const float angle=-std::atan2(dy,dx)*57.2957795f;
  const float fade=age<=turretFire.impact()?1.f:std::max(0.f,1-(age-turretFire.impact())/14.f);
  const float thickness=((turretFire.castle==8?64:48)+4*std::sin(age*1.7f))*scale;
  auto beam=[&](float height,int color,int opacity){
   SetAlpha(opacity);
   turretPart(img,0,(int)dim.height/4,(int)dim.width,(int)dim.height/2,
    {(int)((from.x+to.x-length)*.5f),(int)((from.y+to.y+height)*.5f),(int)std::ceil(length),(int)height},angle);
   renderSprite[getSpriteIdx]->setColor(cocos2d::Color3B((color>>16)&255,(color>>8)&255,color&255));
   SetAlpha(alpha);
  };
  if(turretFire.castle==9){
   beam(thickness*1.6f,tone,(int)(alpha*.22f*fade));
   electricLine(from.x,from.y,to.x,to.y,20*scale,0xFFD56A,(int)(alpha*fade));
   electricLine(from.x,from.y,to.x,to.y,9*scale,0xFFFFEE,(int)(alpha*fade));
   const float nx=-dy/std::max(1.f,length),ny=dx/std::max(1.f,length);
   for(int side=-1;side<=1;side+=2){
    float px=from.x,py=from.y;
    for(int segment=1;segment<=24;++segment){
     const float t=segment/24.f;
     const float wave=segment==24?0.f:side*std::sin(t*12.56637f-age*.4f)*18*scale;
     const float x=from.x+dx*t+nx*wave,y=from.y+dy*t+ny*wave;
     electricLine(px,py,x,y,5*scale,0xFFB93E,(int)(alpha*fade));
     electricLine(px,py,x,y,2*scale,0xFFF4BE,(int)(alpha*fade));
     px=x;py=y;
    }
   }
   for(int pulse=0;pulse<3;++pulse){
    const float t=std::fmod((age-charge)*.09f+pulse/3.f,1.f),end=std::min(1.f,t+.13f);
    electricLine(from.x+dx*t,from.y+dy*t,from.x+dx*end,from.y+dy*end,36*scale,0xFFDC78,(int)(alpha*.8f*fade));
    electricLine(from.x+dx*t,from.y+dy*t,from.x+dx*end,from.y+dy*end,18*scale,0xFFFFEF,(int)(alpha*fade));
   }
  }else{
   beam(thickness*1.45f,tone,(int)(alpha*.24f*fade));
   beam(thickness,tone,(int)(alpha*fade));
   beam(thickness*.36f,0xFFF9E8,(int)(alpha*fade));
  }
  if(turretFire.castle==8){
   // Two changing, jagged discharges wrap the beam; small branches flicker out.
   const float nx=-dy/std::max(1.f,length),ny=dx/std::max(1.f,length);
   for(int side=-1;side<=1;side+=2){
    float px=from.x,py=from.y;
    for(int segment=1;segment<=12;++segment){
     const float t=segment/12.f;
     const float wave=segment==12?0.f:side*(15+9*std::sin(segment*2.3f+(age/2)*1.7f))*scale;
     const float x=from.x+dx*t+nx*wave,y=from.y+dy*t+ny*wave;
     electricLine(px,py,x,y,7*scale,0x9B39FF,(int)(alpha*.55f*fade));
     electricLine(px,py,x,y,2.5f*scale,0xF0D6FF,(int)(alpha*fade));
     if(segment%3==0&&segment<12){
      const float bx=x+nx*side*14*scale+dx/std::max(1.f,length)*8*scale;
      const float by=y+ny*side*14*scale+dy/std::max(1.f,length)*8*scale;
      electricLine(x,y,bx,by,2*scale,0xDDACFF,(int)(alpha*fade));
     }
     px=x;py=y;
    }
   }
  }
  glow(from.x,from.y,(turretFire.castle==8?34:27)*scale,tone,(int)(alpha*.7f*fade));
  glow(from.x,from.y,12*scale,0xFFF9E8,(int)(alpha*fade));
  glow(to.x,to.y,(19+3*std::sin(age))*scale,tone,(int)(alpha*.7f*fade));
  glow(to.x,to.y,9*scale,0xFFF9E8,(int)(alpha*fade));
  return;
  }
 }
 const auto pathType=turretFire.castle==2?TurretAttack::Shell:turretFire.type;
 for(int i=0;i<turretFire.count;++i){
  const int elapsed=age-turretFire.launch(i);
  if(elapsed<0)continue;
  if(elapsed>=turretFire.flight){
   const int impactAge=elapsed-turretFire.flight;
   if(turretFire.castle==5||turretFire.type==TurretAttack::Magnetic){
    if(impactAge<14){
     const int img=turretFire.type==TurretAttack::Magnetic?TURRET_MAGNETIC_ORB_IMG:TURRET_CRYSTAL_ORB_IMG;
     if(!sprite[img])LoadImg(img);
     if(sprite[img]){
      const auto dim=sprite[img]->getTexture()->getContentSizeInPixels();
      const int alpha=m_lgrpAlpha,size=(int)((turretFire.type==TurretAttack::Magnetic?72+impactAge*6:38+impactAge*3)*scale);
      SetAlpha(alpha*(14-impactAge)/14);
      turretPart(img,0,0,(int)dim.width,(int)dim.height,{targetX-size/2,targetY+size/2,size,size},impactAge*12.f);
      for(int spark=0;spark<6;++spark){
       const float a=spark*1.04719755f+impactAge*.06f;
       const int x=targetX+(int)(std::cos(a)*(10+impactAge*3)*scale);
       const int y=targetY+(int)(std::sin(a)*(10+impactAge*3)*scale);
       const int n=std::max(1,(int)((4-impactAge*.2f)*scale));
       mergeRect(x-n,y+n,n*2,n*2,turretFire.type==TurretAttack::Magnetic?(spark%2?0xDDF8FF:0x69CFFF):(spark%2?0xA7FFF0:0x39DCCB));
      }
      SetAlpha(alpha);
     }
    }
    continue;
   }
   drawImpactSequence(HIT_DIANA_MEDIUM1,7,impactAge,14,targetX,targetY,RIGHT,
    (turretFire.type==TurretAttack::Rapid?.22f:turretFire.type==TurretAttack::Missiles?.7f:1.25f)*scale);
   continue;
  }
  const float t=elapsed/(float)turretFire.flight;
  auto start=from;
  if(turretFire.castle==2||turretFire.type==TurretAttack::Rapid)start=cannonMuzzle(l,turretFire.castle,siegeActive&&Siege::swapped,turretFire.launch(i),i);
  const auto point=TurretAttack::position(pathType,t,start,to,i,scale);
  const auto next=TurretAttack::position(pathType,std::min(1.f,t+.02f),start,to,i,scale);
  const float angle=-std::atan2(next.y-point.y,next.x-point.x)*57.2957795f;
  if(turretFire.type==TurretAttack::Missiles){
   // Copy of Diana's own missile sprite sheet, under a separate resource identity.
   if(cmfLoaded[DIANA]!=DIANA)CmfRead(DIANA,DIANA);
   int part=IMG_C1_53;
   const int first=cmd_m_cnt[DIANA][PO_C1_MISSILE_SHOT0*2],count=cmd_m_cnt[DIANA][PO_C1_MISSILE_SHOT0*2+1];
   for(int k=0;k<count;++k){const int p=cmd_m_img[DIANA][(first+k)*4];if(p>=IMG_C1_50&&p<IMG_C1_64){part=p;break;}}
   const auto* source=cmd_i_offset[DIANA]+part*4;
   const float z=32*scale/std::max(1,(int)std::max(source[2],source[3]));
   for(int trail=3;trail>=1;--trail){
    const auto p=TurretAttack::position(pathType,std::max(0.f,t-trail*.025f),start,to,i,scale);
    const int size=std::max(1,(int)((5-trail)*scale));
    mergeRect((int)p.x-size,(int)p.y+size,size*2,size*2,trail==1?0xFFF2B0:0xF78C35);
   }
   if(turretFire.castle==2){
    const int missile=TURRET_TRIPLE_MISSILE_IMG;
    if(!sprite[missile])LoadImg(missile);
    if(sprite[missile]){
     const auto dim=sprite[missile]->getTexture()->getContentSizeInPixels();
     sprite[missile]->getTexture()->setAntiAliasTexParameters();
     const int width=(int)(42*scale),height=(int)(width*dim.height/dim.width);
     turretPart(missile,0,0,(int)dim.width,(int)dim.height,
      {(int)point.x-width/2,(int)point.y+height/2,width,height},angle);
    }
   }else turretPart(TURRET_MISSILE_IMG,source[0],source[1],source[2],source[3],
    {(int)(point.x-source[2]*z/2),(int)(point.y+source[3]*z/2),(int)(source[2]*z),(int)(source[3]*z)},angle+90);
  }else{
   const int img=turretFire.type==TurretAttack::Magnetic?TURRET_MAGNETIC_ORB_IMG:turretFire.castle==5?TURRET_CRYSTAL_ORB_IMG:turretFire.castle==4?TURRET_HEAVY_SHELL_IMG:TURRET_IRONBALL_IMG;
   if(!sprite[img])LoadImg(img);
   if(sprite[img]){
    const auto dim=sprite[img]->getTexture()->getContentSizeInPixels();
    sprite[img]->getTexture()->setAntiAliasTexParameters();
    const bool rapid=turretFire.type==TurretAttack::Rapid;
    const int diameter=std::max(1,(int)((turretFire.type==TurretAttack::Magnetic?72.f:rapid?13.f:turretFire.castle==4?46.f:turretFire.type==TurretAttack::Stone?44.f:38.f)*scale));
    const int bulletHeight=std::max(2,(int)(4*scale));
    const float spinDirection=to.x>=from.x?1.f:-1.f;
    const float spin=elapsed*(turretFire.type==TurretAttack::Magnetic?7.f:18.f)*spinDirection;
    const int alpha=m_lgrpAlpha;
    for(int trail=rapid?0:3;trail>=1;--trail){
     const auto p=TurretAttack::position(turretFire.type,std::max(0.f,t-trail*.035f),start,to,i,scale);
     const int size=(int)(diameter*(.72f-trail*.09f));
     SetAlpha(alpha*(4-trail)/12);
     turretPart(img,0,0,(int)dim.width,(int)dim.height,{(int)p.x-size/2,(int)p.y+size/2,size,size},spin-trail*18.f*spinDirection);
    }
    SetAlpha(alpha);
    if(turretFire.castle==5||turretFire.type==TurretAttack::Magnetic){
     const int glow=(int)(diameter*(1.20f+.10f*std::sin(elapsed*.6f)));
     SetAlpha(alpha/3);
     turretPart(img,0,0,(int)dim.width,(int)dim.height,{(int)point.x-glow/2,(int)point.y+glow/2,glow,glow},-spin*.5f);
     SetAlpha(alpha);
    }
    turretPart(img,0,0,(int)dim.width,(int)dim.height,{(int)point.x-diameter/2,(int)point.y+(rapid?bulletHeight:diameter)/2,diameter,rapid?bulletHeight:diameter},rapid?angle:spin);
   }
  }
  if(elapsed<(turretFire.type==TurretAttack::Rapid?2:8)&&turretFire.type!=TurretAttack::Stone&&turretFire.castle!=5&&turretFire.type!=TurretAttack::Magnetic){
   drawImpactSequence(HIT_DIANA_SMALL1,7,elapsed,10,(int)start.x,(int)(start.y-(turretFire.type==TurretAttack::Rapid?5:18)*scale),RIGHT,(turretFire.type==TurretAttack::Rapid?.22f:.65f)*scale);
  }
 }
}
TurretAttack::Point heroTorsoPoint(const OBJECT& who,int motion,int x,int y,int dir,float zoom){
 const int cmf=who.cmf;
 TurretAttack::Point result={(float)x,y+32*zoom};
 if(cmf<ROBIN||cmf>MAXX||motion<0||motion>=cmf_m_cnt[cmf]||!cmd_m_cnt[cmf])return result;
 const int first=cmf==ROBIN?IMG_C0_62:cmf==DIANA?IMG_C1_45:IMG_C2_44;
 const int end=cmf==ROBIN?IMG_C0_65:cmf==DIANA?IMG_C1_48:IMG_C2_47;
 const int start=cmd_m_cnt[cmf][motion*2],count=cmd_m_cnt[cmf][motion*2+1];
 for(int i=0;i<count;++i){
  const auto* part=cmd_m_img[cmf]+(start+i)*4;
  if(part[0]<first||part[0]>=end)continue;
  const auto* rect=cmd_i_offset[cmf]+part[0]*4;
  const int kind=part[3];const float magnify=((kind>>6)+1)*zoom;
  const float width=((kind&6)==2||(kind&6)==6)?rect[3]:rect[2];
  const float height=((kind&6)==2||(kind&6)==6)?rect[2]:rect[3];
  const float localX=part[1]*zoom+width*magnify*.5f;
  result.x=x+(dir==LEFT?localX:-localX);
  result.y=y-part[2]*zoom-height*magnify*.5f;
  break;
 }
 return result;
}
void drawWorld(const Layout& l,bool combat) {
    const float s=l.scale;
    objectDrawOrder=monsterDrawOrder=allyDrawOrder=impactDrawOrder=0;monsterDrawn=false;
    enemyBodyKnown=false;
    deckResidentCount=0;
    deckMergeGhostsDrawn=0;
    SetAlpha(32);SetColor(0);grayScale=0;
    if(!combat)castleScrollSeconds+=std::min(.1f,std::max(0.f,cocos2d::Director::getInstance()->getDeltaTime()))*.25f;
    {StageBg::Borrow scroll(combatRegion(),castleScrollSeconds);
        const int c=siegeHullStage>=0?siegeHullStage:std::max(0,std::min(9,run.stage));
        const auto& wheels=MistCastle::wheelAnchors[c];
        const int contact=std::max(wheels[0][1]+wheels[0][2],wheels[1][1]+wheels[1][2]);
        castleWheelTravel=DrawCastleLobbyBackground((int)((OriginalCastle::H-contact)*OriginalCastle::zoom()+OriginalCastle::lift()+9*s));}
    drawCastleHull(l,combat);
    if(combat){
        drawBattleCover(l);
        const int c=siegeHullStage>=0?siegeHullStage:std::max(0,std::min(9,run.stage));
        MistCastle::wheels(c,castleWheelAngle(92*OriginalCastle::zoom()),siegeActive);
    }
    //---- 데크의 줄 ----
    //
    //전에는 히어로가 DX*0.57 에 서고 동료가 그 왼쪽으로 늘어섰다. 대포가
    //그 자리에 있어서 줄의 앞머리가 포신에 겹쳐 박혔다.
    //
    //이제 대포 앞(오른쪽)부터가 사람 자리다. 히어로가 맨 앞에 서고 동료가
    //그 뒤로 붙되, 마지막 사람이 포신을 넘지 않도록 간격만 좁힌다.
    const Box gun=castleCannonBox(l);
    const int deckBack=(int)(235*s);      //대포 바로 앞
    //공성전: 성이 거울로 서고 성주가 오른쪽에 있으므로 내 히어로는 왼쪽에서 올라탄다.
    //둘은 데크 가운데서 마주 선다(내 쪽 24%, 상대 42%). 상대 턴에 런을 맞바꾸면
    //hero 가 성주이므로 자리와 방향도 같이 바뀐다.
    const bool sidesSwapped=siegeActive&&Siege::swapped;
    const int allyX=(int)(DX*.24f),foeX=(int)(DX*.42f);
    const int hx=siegeActive?(sidesSwapped?foeX:allyX):monsterHeroX(l);
    const int heroDir=sidesSwapped?LEFT:RIGHT;
    const int hy=l.ground+(int)(8*s),ex=siegeActive?(sidesSwapped?allyX:foeX):(int)(DX*.85f),ey=l.ground+(int)(8*s);
    const float deckY=(float)hy;
    allyBodyX=hx;allyBodyY=hy+(int)(40*s);allyBodyKnown=true;   //히어로 그림은 x 가 몸통 가운데다
    SetSectionClip(0,DY,DX,DY-l.board.y,false);
    // Submit all monsters before allies, so weapons and allied effects stay in front.
    if(combat&&siegeActive){Siege::drawFoe(l,ex,ey);}   //공성전: 몬스터 자리에 상대 성주(DrawPlayer, 가운데 앵커)
    else if(combat) {
    int npc=waveTransition.defeatedVisible()?defeatedNpc:combatEnemyNpc();
    int cmf=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF];
    if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);
    //보스도 잡몹과 같은 배율로 선다. 보스 그림은 원래 크게 그려져 있어서 0.65 로 줄이면
    //잡몹보다 작아 보였다. 화면 위(데크 위 여백)에 안 들어갈 때만 거기 맞춰 줄인다.
    const float enemyZoom=monsterZoom(l,npc,cmf);
    const bool striking=enemyTurn.started&&!enemyTurn.complete;
    const int idleFrames=std::max(1,(int)crewPos[npc*5+1]);
    const int idle=crewPos[npc*5]+(ticks/6)%idleFrames;
    int enemyMotion=idle,enemyX=ex,enemyDir=LEFT;
    renderedEnemyWalking=false;
    if(striking){
        const auto& phases=enemyTurn.phases;const int elapsed=enemyTurn.time.elapsed;
        const float target=enemyTurn.attackX;
        enemyX=(int)target;
        const bool inbound=phases.walkingIn(elapsed),outbound=phases.walkingBack(elapsed);
        if(inbound||outbound){
            const int duration=inbound?phases.approach:phases.returnFrames;
            const float progress=std::min(1.f,(elapsed-(outbound?phases.returnStart():0))/(float)std::max(1,duration));
            const auto& poses=outbound&&!enemyTurn.back.empty()?enemyTurn.back:enemyTurn.walk;
            if(!poses.empty())enemyMotion=poses[std::min((int)poses.size()-1,(int)(progress*poses.size()))];
            const auto& distance=outbound&&!enemyTurn.backDistance.empty()&&enemyTurn.backDistance.back()>0?enemyTurn.backDistance:enemyTurn.walkDistance;
            const float movement=MergeCombat::walkProgress(distance,progress);
            if(enemyTurn.moves)enemyX=(int)(outbound?target+(ex-target)*movement:ex-(ex-target)*movement);
            enemyDir=outbound&&enemyTurn.moves?RIGHT:LEFT;renderedEnemyWalking=enemyTurn.moves;
        }else if(elapsed>=phases.recoveryStart()){
            enemyX=ex;
            if(!enemyTurn.rest.empty())enemyMotion=enemyTurn.rest[std::min((int)enemyTurn.rest.size()-1,elapsed-phases.recoveryStart())];
        }else if(!enemyTurn.motion.empty()){
            const int index=std::max(0,std::min((int)enemyTurn.motion.size()-1,elapsed-phases.approach));
            enemyMotion=enemyTurn.motion[index];
        }
    }
    renderedEnemyX=enemyX;renderedEnemyMotion=enemyMotion;renderedEnemyDir=enemyDir;
    int monsterY=ey;
    const bool defeated=waveTransition.defeatedVisible();
    const bool showMonster=defeated||waveTransition.incomingVisible();
    if(defeated){
        enemyMotion=defeatedMotion;SetAlpha((int)(32*waveTransition.defeatAlpha()));
        monsterY-=(int)((1-waveTransition.defeatAlpha())*12*s);
    }else if(waveTransition.active()&&waveTransition.incomingVisible()){
        const auto* bounds=cmfMotionImgSize[cmf]+crewPos[npc*5]*4;
        const float offscreen=DX+(std::abs((int)bounds[0])+bounds[2])*enemyZoom;
        enemyX=(int)waveTransition.incomingX(offscreen,(float)ex);
        int walkFrames=0;const signed short* walk=nullptr;
        if(waveTransition.arrival()<1&&CrewWalkMotion(cmf,npc,walkFrames,walk)&&walkFrames>0)
            enemyMotion=walk[(waveTransition.age-MergeCombat::WaveTransition::EnterStart)%walkFrames];
        SetAlpha((int)(32*std::min(1.f,waveTransition.arrival()*4)));
    }
    renderedEnemyX=enemyX;renderedEnemyMotion=enemyMotion;
    monsterDrawn=showMonster;
    if(showMonster){monsterDrawOrder=++objectDrawOrder;DrawCmfDetailShadow(cmf,enemyMotion,enemyX,monsterY,enemyDir,enemyZoom);}
    SetAlpha(32);
    if(cmf>=TOTALCHAR&&enemyMotion>=0&&enemyMotion<cmf_m_cnt[cmf]){
        const auto* mb=cmfMotionImgSize[cmf]+enemyMotion*4;
        enemyBodyX=enemyX+(enemyDir==LEFT?-1:1)*(int)((mb[0]+mb[2]*.5f)*enemyZoom);
        enemyBodyY=ey-(int)((mb[1]+mb[3]*.5f)*enemyZoom);
        //경계값이 그림 틀 밖을 가리키면(큰 보스의 표가 다른 단위일 때) 발 위 40 으로 되돌린다.
        if(enemyBodyX<enemyX-220*s||enemyBodyX>enemyX+60*s||enemyBodyY<ey||enemyBodyY>ey+260*s){enemyBodyX=enemyX-(int)(30*s);enemyBodyY=ey+(int)(40*s);}
    }else{enemyBodyX=enemyX;enemyBodyY=ey+(int)(40*s);}
    enemyBodyKnown=showMonster;
    }
    //히어로는 판의 주인이다. 데크에서 한눈에 찾아야 하므로 동료보다 크다(1.5배).
    float heroZoom=std::max(.35f*s,std::min(.82f*s,(DY-hy-8*s)/80.f))*1.5f;

    //---- 지금 치는 블록 ----
    //
    //차례가 된 블록 하나가 데크의 한 사람과 짝이 된다. 그 사람만 한 발
    //앞으로 나가 치고 제자리로 돌아온다(lunge). 장비 블록은 사람이
    //없으므로 히어로가 대신 휘두른다.
    const Shot* firing=combat&&run.attacking&&action.index>=0&&action.index<(int)run.shots.size()?&run.shots[action.index]:nullptr;
    const float fireT=firing?std::min(1.f,action.time.elapsed/(float)std::max(1,action.crewFrames)):0.f;
    const int lunge=firing?(int)(MergeCombat::actorStep(action.time.elapsed,action.time.end)*s):0;
    const int heroFrame=firing?action.time.elapsed-action.heroStart:-1;
    const bool heroSwing=firing&&!weaponSwap.running()&&!action.heroMotion.empty()&&heroFrame>=0&&heroFrame<(int)action.heroMotion.size()*MOTIONDIV;
    const int heroX=hx+(heroSwing?(int)(std::sin(heroFrame/(float)std::max(1,(int)action.heroMotion.size()*MOTIONDIV)*3.14159265f)*18*s):0);
    OBJECT* actingHero=heroSwing?&action.caster:&hero;
    const int heroMotion=heroSwing?action.heroMotion[std::min((int)action.heroMotion.size()-1,heroFrame/MOTIONDIV)]:heroNeutralMotion(hero);
    {//몸통 점이 스프라이트 상자를 벗어나면(부위 표의 좌표가 다른 틀일 때) 발 위 36 으로 되돌린다 -
     //안 그러면 피격 효과와 피해 숫자가 첨탑 쪽 엉뚱한 자리에 뜬다.
     auto body=heroTorsoPoint(*actingHero,heroMotion,heroX,hy,heroDir,heroZoom);
     if(std::abs(body.x-heroX)>48*heroZoom||body.y<hy||body.y>hy+140*heroZoom){body.x=(float)heroX;body.y=hy+36*heroZoom;}
     allyBodyX=(int)body.x;allyBodyY=(int)body.y;allyBodyKnown=true;}
    const int costumeFrame=(30-costumeEffectTicks)/3;
    //---- 로비의 데크에는 히어로만 선다 ----
    //
    //동료는 판의 블록이 전투에 데려가는 사람이지 로비 주민이 아니다. 로비에서는
    //지금 고른 히어로가 맨 앞, 나머지 둘이 그 뒤로 48픽셀씩 물러서 선다.
    //아직 얻지 못한 히어로는 회색이다(IsGetHero).
    if(!combat&&!siegeActive) {
        int others[TOTALCHAR],count=0;
        for(int t=ROBIN;t<=MAXX;++t)if(t!=hero.type)others[count++]=t;
        for(int k=count-1;k>=0;--k) {   //먼 사람부터 그려야 앞사람이 덮는다
            const int t=others[k];
            OBJECT other=hero;other.type=other.cmf=t;
            if(cmfLoaded[t]!=t)CmfRead(t,t);
            std::memcpy(other.equip,robin.charData[t].equip,sizeof(other.equip));
            const int x=hx-(int)(48*s)*(k+1);
            //못 얻은 히어로는 회색에 움직이지 않는다 - 쉬는 동작의 첫 장에 멈춰 선다.
            const bool owned=IsGetHero(t);
            const int still=GetHeroLoopMotion(t,HEROLOOP_NEUTRAL,0);
            const int motion=owned?heroNeutralMotion(other):(still>=0?still:motionData[0]);
            grayScale=owned?0:32;
            DrawPlayer(&other,motion,x,hy,RIGHT,heroZoom,0,false,true);
            grayScale=0;
        }
    }
    if(combat&&costumeEffectTicks>0)
        DrawPlayer(actingHero,2000+LEVELUP_BACK0+costumeFrame,heroX,hy,heroDir,heroZoom,0,false,false);
    if(allyFlash>0)SetColor(0xFF9B8A);
    allyDrawOrder=++objectDrawOrder;
    DrawPlayer(actingHero,heroMotion,heroX,hy,heroDir,heroZoom,0,false,true);
    SetColor(0);
    if(combat&&costumeEffectTicks>0)
        DrawPlayer(actingHero,2000+LEVELUP_FRONT0+costumeFrame,heroX,hy,heroDir,heroZoom,0,false,false);
    if(combat&&weaponSwap.running()){
        const int id=ItemSeries::FromIcon(GetItemIcon(incomingWeapon.type,incomingWeapon.detail,incomingWeapon.grade));
        if(id>=0){
            const int img=ITEM_SERIES_FIRST_IMG+id;
            if(!sprite[img])LoadImg(img);
            if(sprite[img]){
                const auto dim=sprite[img]->getTexture()->getContentSizeInPixels();
                const float turn=weaponSwap.orbit(),a=turn*6.2831853f;
                const float snap=weaponSwap.snap(),ease=1-std::pow(1-snap,3.f);
                const float top=std::min(hy+84*heroZoom,DY-110*s);
                const float orbitX=heroX+std::sin(a)*28*s,orbitY=top+std::cos(a)*10*s;
                const float handX=heroX+(heroDir==LEFT?-18:18)*s,handY=hy+35*heroZoom;
                const float x=orbitX+(handX-orbitX)*ease,y=orbitY+(handY-orbitY)*ease;
                const int size=(int)((52-12*ease)*s);
                if(weaponSwap.age<MergeCombat::WeaponSwap::AttachFrame){
                    turretPart(img,0,0,(int)dim.width,(int)dim.height,{(int)x-size/2,(int)y+size/2,size,size},turn*360.f*(heroDir==LEFT?-1:1));
                }else{
                    const int pulse=(int)((18+3*(weaponSwap.age-MergeCombat::WeaponSwap::AttachFrame))*s);
                    SetAlpha(32*(MergeCombat::WeaponSwap::Duration-weaponSwap.age)/8);
                    MemRectFrameThick((int)handX-pulse/2,(int)handY+pulse/2,pulse,pulse,0xFFEBA6,std::max(1,(int)(2*s)));
                    SetAlpha(32);
                }
            }
        }
    }
    shotFromX=heroX+(int)(18*s);shotFromY=hy+(int)(35*s);
    //---- 판에 선 동료가 전투 화면에도 선다 ----
    //
    //전에는 계열 표(run.families)에서 대표 한 명을 뽑아 세웠다. 판에
    //무엇을 올렸든 늘 같은 사람이 서 있어서, 칸을 채운 보람이 위에
    //나타나지 않았다.
    //
    //판 위의 동료를 그대로 센다. 같은 사람이 여럿이면 한 번만 세운다 -
    //★ 가 올라도 사람은 하나다.
    {
        int seen[64],shown=0;
        const float crewRight=hx-MergeCombat::DeckGap*s,crewLeft=std::min((float)deckBack,DX*.44f);   //첫 동료는 히어로 뒤 DeckGap, 그 뒤로 같은 간격
        if(combat&&deckMerge.time.running()) {
            int future[64],count=0,resultIndex=0;
            for(const auto& b:run.board)if(b.family<Roles&&b.crew>=0&&b.crew<64){
                if(std::find(future,future+count,b.crew)!=future+count)continue;
                if(b.crew==deckMerge.result.crew)resultIndex=count;
                future[count++]=b.crew;
            }
            deckMerge.targetX=MergeCombat::position(resultIndex,count,crewRight,deckY,s,std::max(0.f,crewRight-crewLeft)).x;
        }

        for(int i=0;combat&&i<(int)run.board.size()&&shown<64;++i) {   //로비에는 동료가 서지 않는다
            const Block& b=run.board[i];

            if(b.family>=Roles||b.crew<0||b.crew>=64) continue;
            if(combat&&!deckReveal[b.crew].visible())continue;

            bool already=false;
            for(int k=0;k<shown;++k) if(seen[k]==b.crew) {already=true;break;}
            if(already) continue;

            seen[shown++]=b.crew;
        }

        const int fireCrew=(firing&&firing->block.family<Roles)?firing->block.crew:-1;

        // Waiting companions first, active companion last so its action stays visible.
        for(int pass=0;pass<2;++pass)for(int k=shown-1;k>=0;--k) {
            const bool mine=(seen[k]==fireCrew);
            if((mine?1:0)!=pass)continue;
            const int npc=crewData[seen[k]*CREWDATASIZE+CREWDATA_TYPE];
            const int cmf=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF];

            if(cmf<0||cmf>=MAXCMF) continue;
            if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);

            // All companions share the same shadow baseline; only horizontal spacing changes.
            const float z=MergeCombat::companionZoom(heroZoom);
            const int pose=mine?crewAttackMotion(npc,cmf,fireT):-1;
            const int idle=crewIdleMotion(seen[k],ticks/6+k*3);
            const int motion=pose>=0?pose:idle>=0?idle:crewPos[npc*5];
            const auto* idleBounds=cmfMotionImgSize[cmf]+crewPos[npc*5]*4;
            // The cannon's art box includes transparent space to its right.
            // Reserve the visible gun area, rather than letting that padding collapse spacing to zero.
            const auto pos=MergeCombat::position(k,shown,crewRight,deckY,s,std::max(0.f,crewRight-crewLeft));
            const int x=(int)pos.x+(mine?lunge:0),y=(int)pos.y;
            deckCrewX[seen[k]]=(float)x;deckCrewPositionKnown[seen[k]]=true;
            const auto& reveal=deckReveal[seen[k]];
            const float t=combat?reveal.progress():1.f,ease=1.f-std::pow(1.f-t,3.f);
            SetAlpha((int)((firing&&!mine?20:32)*ease));
            // Bodies and shadows share the fixed deck baseline during arrival.
            drawDeckShadow(cmf,x,y,z*(.7f+.3f*ease));
            if(mine) {
                // A small step identifies the caster; it never closes the gap to the enemy.
                bevel({x-(int)(29*s),y+(int)(4*s),(int)(58*s),(int)(8*s)},0xFFDC69,(int)(4*s));
            }
            DrawCmfDetail(cmf,motion,x,y,heroDir,z,0,false);
            const bool mergeWarp=combat&&deckMerge.time.running()&&!deckMerge.time.converging()&&seen[k]==deckMerge.result.crew;
            if(combat&&(reveal.arriving()||mergeWarp)) {
                SetAlpha(32);
                const int age=mergeWarp?deckMerge.time.age-MergeCombat::DeckMergeTimeline::GatherFrames:reveal.age;
                const int warp=std::min(9,age*10/MergeCombat::ResidentReveal::Duration);
                DrawPlayer(&hero,2000+LEVELUP_FRONT0+warp,x,y,RIGHT,z,0,false,false);
            }
            SetAlpha(32);
            ++deckResidentCount;
            if(mine) {
                // RIGHT mirrors the native CMF bounds. Use the neutral head, not the hand or a fixed y offset.
                action.emitterX=x-(int)((idleBounds[0]+idleBounds[2]*.5f)*z);
                action.emitterY=y-(int)(idleBounds[1]*z)+(int)(12*s);
                action.emitterReady=true;
                if(!heroSwing){shotFromX=action.emitterX;shotFromY=action.emitterY;}
            }
        }
        if(combat&&deckMerge.time.running()) {
            const float z=MergeCombat::companionZoom(heroZoom);
            if(deckMerge.time.converging())for(int i=0;i<2;++i){
                const int crew=deckMerge.inputs[i].crew;
                if(crew<0||crew>=64)continue;
                const int npc=crewData[crew*CREWDATASIZE+CREWDATA_TYPE],cmf=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF];
                if(cmf<0||cmf>=MAXCMF)continue;
                if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);
                const float from=deckMerge.hadPosition[i]?deckMerge.fromX[i]:deckMerge.targetX+(i?30:-30)*s;
                const int x=(int)deckMerge.time.x(from,deckMerge.targetX);
                deckMergeGhostX[i]=(float)x;++deckMergeGhostsDrawn;
                const int idle=crewIdleMotion(crew,ticks/6+i*3),motion=idle>=0?idle:crewPos[npc*5];
                SetAlpha((int)(32-12*deckMerge.time.progress()));
                drawDeckShadow(cmf,x,hy,z);
                DrawCmfDetail(cmf,motion,x,hy,RIGHT,z,0,false);
            }
            // Bridge the frame between material convergence and the result's native warp reveal.
            else if(!deckReveal[deckMerge.result.crew].visible()) {
                SetAlpha(32);
                DrawPlayer(&hero,2000+LEVELUP_FRONT0,(int)deckMerge.targetX,hy,RIGHT,z,0,false,false);
            }
            SetAlpha(32);
        }
    }
    if(combat&&!siegeActive) {
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
                DrawCmfDetailShadow(c,crewPos[type*5]+(ticks/6)%std::max(1,(int)crewPos[type*5+1]),x,l.ground,RIGHT,.35f*s);
            }
        } else if(kind==SUMMONHERO) {
            OBJECT copy=hero;copy.type=std::max(0,std::min(2,SkillSummonHeroType(skill)));
            DrawPlayer(&copy,heroNeutralMotion(copy),x,l.ground,RIGHT,.45f*s,0,false,true);
        } else icon(summoned.block.family,{x-(int)(14*s),l.ground+(int)(35*s),(int)(28*s),(int)(35*s)},.7f,false,summoned.block.level,summoned.block.crew);
    }
    }
    UnSectionClip(false);

}
void close() {
    if(waveTransition.active())return;
    siegeActive=false;siegeHullStage=-1;
    if(run.attacking) {message="공격 연출이 끝난 뒤 나갈 수 있습니다.";return;}
    save();active=false;option.gameMode=(unsigned char)oldMode;
    picked=-1;finger=-1;systemKey=0;
    is_key_pressed=is_touchkey_pressed=is_key_released=false;
    is_press_finished=is_release_finished=true;
    drawHandle=MD_LOBBY;mustRefresh=true;
}
#include "MergeSiege.inc"
#include "MergeMonsterParts.inc"
//---- 돌리기도 한 턴 ----
//
//포를 쏘든, 돌리든, 공격하든 한 번 행동하면 적이 한 번 때린다. 공격과 대포는
//attack/fireCannon 이 그 길을 타고, 돌리기는 결과가 판에 다 앉은 순간(자동 착지 끝,
//또는 트레이를 손으로 다 놓음)에 여기서 턴을 넘긴다. 공성전은 상대 턴으로 간다.
//겹친 채로 트레이를 비우면 턴을 바로 넘기지 않는다. 겹침을 푼 순간 넘긴다.
bool pendingPass=false;
void endSpinTurn() {
    if(siegeActive){Siege::afterMySpin();return;}
    if(!run.tray.empty()||run.attacking||run.lost||run.choosing||waveTransition.active())return;
    if(!run.boardResolved()){pendingPass=true;return;}
    pendingPass=false;
    if(run.passTurn(stats)){action=CombatAction();enemyTurn=EnemyTurn();animation=0;save();}
}
static const char* OverlapMessage=u8"겹쳐 놓았습니다. 겹침을 풀어야 룰렛·공격·대포를 쓸 수 있습니다.";
void tick(float dt) {
    if(siegeActive)run.configureMonster(-1);else MonsterBoard::ensure();
    if(costumeEffectTicks>0)--costumeEffectTicks;
    if(trashSwallowTicks>0)--trashSwallowTicks;
    weaponSwap.advance();damagePause.advance();
    if(weaponSwap.attachNow()){
        hero.equip[EQUIP_WEAPON]=incomingWeapon;
        refreshHeroVitals();PlayMusic(M_POWERUP);
    }
    ++ticks;++frame;if(flash>0)--flash;if(allyFlash>0)--allyFlash;
    for(auto& number:combatNumbers)++number.age;
    combatNumbers.erase(std::remove_if(combatNumbers.begin(),combatNumbers.end(),[](const CombatNumber& n){return n.age>=MergeCombat::DamageNumberFrames;}),combatNumbers.end());
    heartBlink=std::max(0.f,heartBlink-dt);messageTime=std::max(0.f,messageTime-dt);
    if(siegeActive&&Siege::advance())return;   //상대 턴 연출이 프레임을 쓴다
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
        introElapsed+=dt;
        const float phase=std::min(1.f,introElapsed/1.68f);
        gearAngle=450.f*(1.f-std::pow(1.f-phase,3.f));
        for(int i=0;i<3;++i) {
            float stop=1.2f+i*.24f,land=flightStart(i)+.7f;
            if(before<stop&&introElapsed>=stop)PlayMusic(M_ROULETTEUP);
            if(before<land&&introElapsed>=land)PlayMusic(M_POWERUP);
        }
        return;
    }
    if(waveTransition.active()){
        if(RewardPopup::open()&&waveTransition.age>=MergeCombat::WaveTransition::DefeatFrames){
            if(review){   //리뷰는 첫 보상창만 한 장 남기고 저절로 닫는다
                static bool captured=false;
                static bool shot=false;
                if(!captured&&RewardPopup::ticks()>=58){captured=true;reviewCapture("kill-reward");}   //카드가 다 선 뒤
                if(captured&&!shot&&!reviewCapturePending)shot=true;   //찍힌 것을 보고 닫는다
                if(shot?RewardPopup::ticks()>12:(captured&&!reviewCapturePending))RewardPopup::closeNow();
            }
            return;
        }
        castleScrollSeconds+=dt*waveTransition.speed();
        waveTransition.advance();
        if(!waveTransition.active()){message.clear();enemyBodyKnown=false;}
        return;
    }
    if(spinFlying()){
        ++spinFlightFrame;
        for(int i=0;i<(int)spinDrops.size();++i)if(spinFlightFrame==36+i*4)PlayMusic(M_POWERUP);
        if(spinFlightFrame>=48){run=spinLandingPlan;spinFlightFrame=-1;save();endSpinTurn();}   //돌리기 한 번 = 턴 하나. 결과가 앉으면 적이 때린다
        return;
    }
    if(animation>0&&!run.attacking){
        const float phase=std::min(1.f,(REEL_SPIN_FRAMES+1-animation)/(float)REEL_SPIN_FRAMES);
        gearAngle=gearStartAngle+450.f*(1.f-std::pow(1.f-phase,3.f));
        //릴이 설 때마다 한 번. 시작 뽑기(intro)와 같은 소리다.
        for(int i=0;i<3;++i)if(REEL_SPIN_FRAMES-animation==reelStopFrame(i))PlayMusic(M_ROULETTEUP);
    }
    if(!run.attacking) {
        if(animation>0&&--animation==0){beginSpinLanding();save();}
        return;
    }
    if(weaponSwap.running())return;
    if(action.index>=0) {
        const int before=action.time.elapsed;
        const bool impact=action.time.advance();
        if(run.shots[action.index].block.family<0)turretFire.age=action.time.elapsed;
        if(before<action.time.release&&action.time.elapsed>=action.time.release){
            action.bulletX=action.emitterReady?action.emitterX:shotFromX;
            action.bulletY=action.emitterReady?action.emitterY:shotFromY;
        }
        const int hf=action.time.elapsed-action.heroStart;
        if(hf>=0&&hf%MOTIONDIV==0&&!action.heroSounds.empty()) {
            const int f=hf/MOTIONDIV;
            if(f<(int)action.heroSounds.size()&&action.heroSounds[f]>0)PlayMusic(action.heroSounds[f]);
        }
        if(impact){
            const long long beforeHp=run.enemyHp;run.step();
            floatingDamage(beforeHp-run.enemyHp,true);
            // A complete authored sequence; never advance across unrelated hit types.
            if(run.shots[action.index].block.family<0)flash=0;
            else{
                impactFirst=HIT_ITEM_SMALL0;impactCount=5;
                if(!action.heroMotion.empty()){
                    impactFirst=action.caster.type==ROBIN?HIT_ROBIN_SMALL1:action.caster.type==DIANA?HIT_DIANA_SMALL1:HIT_MAXX_SMALL1;
                    impactCount=action.caster.type==ROBIN?3:action.caster.type==DIANA?7:4;
                }
                flash=18;
            }
            PlayMusic(M_SWORDHIT);save();
        }
        animation=std::max(0,action.time.end-action.time.elapsed);
        if(!action.time.finished())return;
        action.index=-1;turretFire.age=-1;
        return;
    }
    if(damagePause.waiting()&&!enemyTurn.started)return;
    if(run.nextShot<(int)run.shots.size()) {beginCombatAction();return;}
    if(attackWeaponLevel){
        const ITEM old=hero.equip[EQUIP_WEAPON];showAttackWeapon(0);
        const ITEM target=hero.equip[EQUIP_WEAPON];hero.equip[EQUIP_WEAPON]=old;
        if(requestWeaponSwap(target))return;
    }
    if(!enemyTurn.started&&run.shouldCounterattack()&&!siegeActive){beginEnemyTurn();return;}
    if(enemyTurn.started&&!enemyTurn.complete) {
        if(enemyTurn.time.advance()){
            //첫 타: 모델이 반격을 전부 깎는다. 깎인 양을 조각 수로 나눠 타마다 띄운다.
            const long long beforeHp=run.lives,beforeEnemyHp=run.enemyHp,guardBefore=run.guard;run.counterattack();
            const long long total=beforeHp-run.lives,absorbed=std::max(0LL,guardBefore-run.guard);
            enemyTurn.healing=std::max(0LL,run.enemyHp-beforeEnemyHp);
            enemyTurn.hpBefore=beforeHp;enemyTurn.shares.assign(enemyTurn.hits,0);
            //방어막이 받은 몫도 타마다 나눠 보인다. 무적 시간은 없다 - 0 이 뜨면 전부 방어막이 받은 것이다.
            enemyTurn.absorbedShares.assign(enemyTurn.hits,0);
            long long remaining=total,shield=guardBefore,blockedRemaining=absorbed;
            const auto loadout=run.monsterLoadout();
            for(int i=0;i<enemyTurn.hits;++i){
                const long long raw=i<(int)enemyTurn.rawShares.size()?enemyTurn.rawShares[i]:0;
                const int pierce=MonsterParts::piercePct(loadout,MonsterParts::action(run.monsterNpc,i));
                const long long blocked=run.realVitals?std::min(shield,raw-raw*pierce/100):0;
                enemyTurn.absorbedShares[i]=std::min(blockedRemaining,blocked);
                blockedRemaining-=enemyTurn.absorbedShares[i];shield-=blocked;
                enemyTurn.shares[i]=std::min(remaining,std::max(0LL,raw-blocked));remaining-=enemyTurn.shares[i];
            }
            enemyTurn.shares[0]+=remaining;enemyTurn.absorbedShares[0]+=blockedRemaining;
            if(enemyTurn.hits>1)heroHpHold=beforeHp-enemyTurn.shares[0];
            floatingAbsorbed(enemyTurn.absorbedShares[0]);floatingDamage(enemyTurn.shares[0],false);allyFlash=20;PlayMusic(M_SWORDHIT);
            enemyTurn.hitsShown=1;save();
        }else if(enemyTurn.hitsShown>0&&enemyTurn.hitsShown<enemyTurn.hits&&enemyTurn.time.elapsed>=enemyTurn.impacts[enemyTurn.hitsShown]){
            const int k=enemyTurn.hitsShown++;
            long long shown=0;for(int i=0;i<=k;++i)shown+=enemyTurn.shares[i];
            heroHpHold=k+1<enemyTurn.hits?enemyTurn.hpBefore-shown:-1;
            if(k<(int)enemyTurn.absorbedShares.size())floatingAbsorbed(enemyTurn.absorbedShares[k]);
            floatingDamage(enemyTurn.shares[k],false);allyFlash=20;PlayMusic(M_SWORDHIT);
        }
        if(enemyTurn.time.finished()){
            enemyTurn.complete=true;heroHpHold=-1;
            if(enemyTurn.healing>0){combatNumbers.push_back({"+"+std::to_string(enemyTurn.healing),DX*.85f,(float)(layout().ground+68*DX/640.f),0x8DFFA2});PlayMusic(M_POWERUP);}
        }
        return;
    }
    if(damagePause.waiting())return;
    if(!enemyTurn.endShown){enemyTurn.endShown=true;enemyTurn.endFrames=30;return;}
    if(enemyTurn.endFrames>0){--enemyTurn.endFrames;return;}
    bool killed=run.enemyHp==0;
    long long overkill=std::max(0LL,run.damageDone-run.enemyMax);
    const long long previousLives=run.lives;
    if(killed&&!siegeActive){defeatedNpc=combatEnemyNpc();defeatedMotion=renderedEnemyMotion;}
    int hearts=run.finish();enemyTurn=EnemyTurn();
    if(run.lives>previousLives)combatNumbers.push_back({"+"+std::to_string(run.lives-previousLives),DX*.66f,(float)(layout().ground+68*DX/640.f),0x8DFFA2});
    run.setShape(castleShape(run.stage));
    if(hearts)GetItem(ITEM_HEART,false,false,false,hearts,false);
    if(siegeActive){Siege::afterAttack(killed);return;}   //공성전: 웨이브가 아니라 상대 턴
    if(killed) {
        long long gold=run.reward;run.reward=0;
        GetItem(ITEM_GOLD,false,false,false,gold,false);
        message=overkill>0?"오버킬! 다음 웨이브":"처치! 다음 웨이브";
        //보상창: 골드·하트·(성 클리어면) 장비를 카드로. "다음" 을 눌러야 다음 몬스터가 온다.
        std::vector<RewardPopup::Entry> rewards;
        {RewardPopup::Entry g;g.type=ITEM_GOLD;g.count=gold;rewards.push_back(g);}
        if(hearts>0){RewardPopup::Entry h;h.type=ITEM_HEART;h.count=hearts;rewards.push_back(h);}
        const bool stageClear=run.wave==0;
        if(stageClear) {
            message="성 클리어! 장비 획득 · 다음 성으로";
            if(!review) {
                int type=ITEM_SWORD+hero.type,lv=std::max(1,std::min(GetEquipMaxLevel(),run.stage+1));
                int detail=MakeItemDetail(type,lv),grade=MakeItemGrade(type,lv,detail);
                GetItem(type,lv,detail,grade,1,0);
                RewardPopup::Entry it;it.type=type;it.detail=detail;it.grade=grade;it.lv=lv;it.count=1;rewards.push_back(it);
            }
        }
        {
            char heading[160];
            const char* name=defeatedNpc>=0&&defeatedNpc<gTotalEnemy?textId[TEXT_MONSTERNAME_START+defeatedNpc]:u8"몬스터";
            std::snprintf(heading,sizeof(heading),u8"%s %s",overkill>0?u8"오버킬!":u8"처치!",name);
            RewardPopup::drawButton=rewardButton;
            RewardPopup::show(heading,rewards,stageClear?u8"다음 성으로":u8"다음");
        }
        run.enemyHp=run.enemyMax=waveHp(run.stage,run.wave);
        if(run.realVitals)run.enemyAttack=waveAttack(run.stage,run.wave);
        waveTransition.begin();picked=finger=-1;
        flash=allyFlash=0;enemyBodyKnown=false;
    } else message=run.lost?"목숨을 모두 사용했습니다":"턴 종료 · 다음 공격을 준비하세요.";
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
void turnReviewStep(const Layout& l) {
    static int phase=0,idleTicks=0,crew=-1,bossSample=0;
    static bool counterSeen=false,endSeen=false,finished=false;
    static std::vector<int> heroIdle,crewIdle,enemyIdle;
    static std::vector<int> walkingPoses;
    static bool walkInCaptured=false,walkBackCaptured=false;
    static int previousWalkingX=-1;
    if(finished)return;
    if(phase==0) {
        for(int c=0;c<64;++c) {
            Block b;b.family=MergeTrees::Role(c);b.crew=c;b.level=MergeTrees::Star(c);
            const int skill=actionSkill(b);
            if(crewIdleMotion(c,0)>=0&&skill>=0&&SkillKind(skill)==CREWBULLET){crew=c;break;}
        }
        if(crew<0){reviewTrace("FAIL animated crew fixture");finished=true;return;}
        run=Run();run.roster=&roster;run.choosing=false;run.setShape(castleShape(0));
        debugFirstBoss=false;
        run.lives=run.maxLives=5;run.enemyHp=100000;run.enemyMax=200000;holdVitals=true;
        run.families[0]=MergeTrees::Role(crew);run.families[1]=Sword;run.families[2]=Armor;
        Block b;b.family=MergeTrees::Role(crew);b.crew=crew;b.level=MergeTrees::Star(crew);b.x=b.y=0;
        Block sword;sword.family=Sword;sword.x=2;sword.y=0;run.board={b,sword};
        stats.crew[crew].trait=Strike;stats.crew[crew].power=10;
        entryElapsed=MergeCastleTransition::Duration;introElapsed=-1;spinFlightFrame=-1;
        action=CombatAction();enemyTurn=EnemyTurn();animation=0;phase=1;return;
    }
    if(phase==1) {
        const auto collect=[](std::vector<int>& seen,int motion){if(std::find(seen.begin(),seen.end(),motion)==seen.end())seen.push_back(motion);};
        collect(heroIdle,heroNeutralMotion(hero));collect(crewIdle,crewIdleMotion(crew,ticks/6));
        const int npc=combatEnemyNpc(),frames=std::max(1,(int)crewPos[npc*5+1]);
        collect(enemyIdle,crewPos[npc*5]+(ticks/6)%frames);
        if(++idleTicks<42||deckArriving())return;
        reviewTrace(heroIdle.size()>1&&crewIdle.size()>1&&enemyIdle.size()>1?"PASS hero crew and enemy neutral motions loop":"FAIL frozen neutral motion");
        reviewCapture("turn-01-idle-progress");phase=2;return;
    }
    if(phase==2){reviewTap(l.attack);phase=3;return;}
    if(phase==3) {
        if(!enemyTurn.started&&run.attacking&&run.lives!=5){reviewTrace("FAIL enemy damaged hero during allied actions");finished=true;return;}
        if(enemyTurn.started) {
            if(run.nextShot!=(int)run.shots.size()){reviewTrace("FAIL enemy attacked before allies completed");finished=true;return;}
            const int expected=enemyTurn.time.applied?4:5;
            if(run.lives!=expected){reviewTrace("FAIL counterattack timing or duplicate damage");finished=true;return;}
            if(enemyTurn.phases.approach>0&&!enemyTurn.complete){
                const int elapsed=enemyTurn.time.elapsed;
                const bool walkingIn=enemyTurn.phases.walkingIn(elapsed),walkingBack=enemyTurn.phases.walkingBack(elapsed);
                if(walkingIn||walkingBack){
                    const bool authored=std::find(enemyTurn.walk.begin(),enemyTurn.walk.end(),renderedEnemyMotion)!=enemyTurn.walk.end()
                        ||std::find(enemyTurn.back.begin(),enemyTurn.back.end(),renderedEnemyMotion)!=enemyTurn.back.end();
                    if(!renderedEnemyWalking||!authored){
                        reviewTrace("FAIL enemy slides without authored walking pose");finished=true;return;
                    }
                    if(std::find(walkingPoses.begin(),walkingPoses.end(),renderedEnemyMotion)==walkingPoses.end())walkingPoses.push_back(renderedEnemyMotion);
                    if(walkingIn&&elapsed>=5&&!walkInCaptured){reviewCapture("turn-01a-enemy-walk-in");walkInCaptured=true;}
                    if(walkingBack&&elapsed>=enemyTurn.phases.returnStart()+5&&!walkBackCaptured){
                        reviewTrace(renderedEnemyDir==RIGHT&&walkingPoses.size()>1?"PASS enemy approaches and returns using authored walking animation":"FAIL walking direction or frozen pose");
                        reviewCapture("turn-02a-enemy-walk-back");walkBackCaptured=true;
                    }
                    previousWalkingX=renderedEnemyX;
                }else if(elapsed>=enemyTurn.phases.approach&&elapsed<enemyTurn.phases.returnStart()){
                    const int target=(int)enemyTurn.attackX;
                    if(renderedEnemyWalking||std::abs(renderedEnemyX-target)>1){reviewTrace("FAIL enemy moves during attack motion");finished=true;return;}
                }
            }
            if(enemyTurn.time.applied&&!counterSeen) {
                counterSeen=true;reviewTrace("PASS enemy hits only after all allied actions complete");reviewCapture("turn-02-enemy-counterattack");
            }
            if(enemyTurn.endShown&&!endSeen) {
                endSeen=true;reviewTrace("PASS turn end follows enemy recovery");reviewCapture("turn-03-turn-end");
            }
        }
        if(!run.attacking) {
            reviewTrace(walkInCaptured&&walkBackCaptured?"PASS walk attack recover walk-back phases complete before turn end":"FAIL enemy walking phase coverage");
            reviewTrace(counterSeen&&endSeen&&run.lives==4?"PASS enemy counterattack then turn end unlocks controls":"FAIL turn sequence");
            phase=4;
        }
        return;
    }
    if(phase==5) {
        const char* names[]={"turn-04-wave5-boss","turn-05-wave10-boss","turn-06-wave15-final-boss"};
        reviewCapture(names[bossSample-1]);phase=4;return;
    }
    if(phase==4) {
        if(bossSample<3) {
            run.wave=4+bossSample*5;
            run.enemyHp=run.enemyMax=waveHp(run.stage,run.wave);
            if(run.realVitals)run.enemyAttack=waveAttack(run.stage,run.wave);
            ++bossSample;phase=5;return;
        }
        reviewTrace(BossTier(4)==1&&BossTier(9)==2&&BossTier(14)==3&&waveHp(0,14)>waveHp(0,9)&&waveHp(0,9)>waveHp(0,4)?"PASS real bosses at waves 5 10 15 with increasing health":"FAIL boss progression");
        reviewTrace("DONE merge turn review");finished=true;return;
    }
}
void arrivalReviewStep(const Layout& l) {
    static int phase=0,firstCrew=-1,newCrew=-1;
    static bool stopped=false,landed=false,rotating=false,spinLanded=false,spinRotating=false,done=false;
    if(done||entering())return;
    if((introActive()&&introElapsed>=1.85f)||spinFlying()) {
        if(!reelResultDrawn[0]||!reelResultDrawn[1]||!reelResultDrawn[2]){
            reviewTrace("FAIL stopped reel went blank during grid transfer");done=true;return;
        }
    }
    if(phase==0) {
        if(firstCrew<0)for(const auto& b:run.board)if(b.family<Roles){firstCrew=b.crew;break;}
        if(introElapsed<2.75f&&deckResidentCount!=0){reviewTrace("FAIL opening crew leaked before grid landing");done=true;return;}
        if(!stopped&&introElapsed>=1.85f) {
            stopped=true;reviewTrace(deckResidentCount==0?"PASS stopped reels do not reveal pending crew on deck":"FAIL premature deck reveal");
            reviewTrace("PASS stopped reel symbols remain rendered through transfer");
            reviewCapture("arrival-01-stopped-reels");return;
        }
        if(firstCrew>=0) {
            const auto& reveal=deckReveal[firstCrew];
            if(!landed&&reveal.age==0){landed=true;reviewCapture("arrival-02-grid-landed");}
            if(!rotating&&reveal.age>=14&&reveal.age<=24){rotating=true;reviewCapture("arrival-03-deck-warp");}
        }
        if(!introActive()&&!deckArriving()) {
            reviewTrace(landed&&rotating?"PASS grid landing precedes warp deck arrival":"FAIL missing staged opening arrival");
            reviewCapture("arrival-04-opening-ready");phase=1;
        }
        return;
    }
    if(phase==1) {
        for(unsigned seed=1;seed<1000&&newCrew<0;++seed) {
            Run preview=run;preview.rng=seed;if(!preview.spin())continue;
            for(const auto& result:preview.tray)if(result.family<Roles) {
                bool present=false;for(const auto& b:run.board)if(b.family<Roles&&b.crew==result.crew)present=true;
                if(!present){newCrew=result.crew;run.rng=seed;break;}
            }
        }
        if(newCrew<0){reviewTrace("FAIL no fresh crew spin fixture");done=true;return;}
        reviewTap(l.spin);phase=2;return;
    }
    const auto& reveal=deckReveal[newCrew];
    if((animation>0||spinFlying())&&reveal.visible()) {reviewTrace("FAIL spin crew appeared before result landed");done=true;return;}
    if(!spinLanded&&reveal.age==0){spinLanded=true;reviewCapture("arrival-05-spin-grid-landed");}
    if(!spinRotating&&reveal.age>=14&&reveal.age<=24){spinRotating=true;reviewCapture("arrival-06-spin-deck-warp");}
    if(spinLanded&&!deckArriving()&&!spinFlying()&&animation==0) {
        reviewTrace(spinRotating?"PASS normal spin also lands before warping crew onto deck":"FAIL spin warp arrival");
        reviewCapture("arrival-07-spin-ready");reviewTrace("DONE merge arrival review");done=true;
    }
}
// Exercise the actual counterattack builder and renderer for every roster/colour/pattern.
void enemyPatternReviewStep(const Layout& l){
    static std::vector<int> npcs;
    static int sample=0,patternTurn=0,probe=-1,checked=0,moving=0,stationary=0;
    static bool done=false;
    if(done)return;
    if(npcs.empty()){
        for(const auto& roster:kRegionRoster)for(int variant=0;variant<3;++variant){
            for(int slot=0;slot<7;++slot){
                const int npc=(slot<4?roster.normal[slot]:roster.boss[slot-4])+variant*51;
                if(npc<gTotalEnemy&&std::find(npcs.begin(),npcs.end(),npc)==npcs.end())npcs.push_back(npc);
            }
        }
        run.attacking=false;run.choosing=false;holdVitals=true;
        entryElapsed=MergeCastleTransition::Duration;introElapsed=-1;spinFlightFrame=-1;
    }
    if(probe>=0){
        const int cmf=enemyData[reviewEnemyNpc*ENEMYDATASIZE+ENEMYDATA_CMF];
        const bool atAttack=probe==2,atRest=probe==4;
        if((atAttack&&std::abs(renderedEnemyX-enemyTurn.attackX)>1)
            ||(atRest&&std::abs(renderedEnemyX-enemyTurn.homeX)>1)
            ||(!enemyTurn.moves&&std::abs(renderedEnemyX-enemyTurn.homeX)>1)
            ||(atAttack&&std::find(enemyTurn.motion.begin(),enemyTurn.motion.end(),renderedEnemyMotion)==enemyTurn.motion.end())
            ||(atRest&&!enemyTurn.rest.empty()&&std::find(enemyTurn.rest.begin(),enemyTurn.rest.end(),renderedEnemyMotion)==enemyTurn.rest.end())){
            char msg[160];std::snprintf(msg,sizeof(msg),"FAIL enemy pattern npc=%d pattern=%d probe=%d x=%d target=%.1f cmf=%d",reviewEnemyNpc,enemyTurn.pattern.index,probe,renderedEnemyX,enemyTurn.attackX,cmf);
            reviewTrace(msg);done=true;return;
        }
        if(++probe>=5){++checked;enemyTurn.moves?++moving:++stationary;++patternTurn;probe=-1;}
    }
    if(probe<0){
        while(sample<(int)npcs.size()){
            reviewEnemyNpc=npcs[sample];
            const int cmf=enemyData[reviewEnemyNpc*ENEMYDATASIZE+ENEMYDATA_CMF];
            if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);
            const auto selected=nativeEnemyPattern(reviewEnemyNpc,cmf,patternTurn);
            if(selected.index<0){reviewTrace("FAIL roster enemy has no playable pattern");done=true;return;}
            if(patternTurn>0&&selected.index==nativeEnemyPattern(reviewEnemyNpc,cmf,0).index){++sample;patternTurn=0;continue;}
            beginEnemyTurn();
            if(enemyTurn.pattern.index!=selected.index){reviewTrace("FAIL enemy pattern order or encounter reset");done=true;return;}
            if(enemyTurn.motion.empty()){char msg[160];std::snprintf(msg,sizeof(msg),"FAIL roster enemy has no attack motion npc=%d pattern=%d status=%d cmf=%d",reviewEnemyNpc,enemyTurn.pattern.index,enemyTurn.pattern.attack,enemyData[reviewEnemyNpc*ENEMYDATASIZE+ENEMYDATA_CMF]);reviewTrace(msg);done=true;return;}
            probe=0;break;
        }
        if(sample>=(int)npcs.size()){
            char msg[160];std::snprintf(msg,sizeof(msg),"PASS %d roster monsters, %d patterns, %d moving and %d stationary attacks at native range",(int)npcs.size(),checked,moving,stationary);
            reviewTrace(msg);reviewTrace("DONE enemy pattern review");done=true;return;
        }
    }
    const auto& p=enemyTurn.phases;
    const int times[5]={0,p.approach/2,p.approach,p.returnStart(),p.recoveryStart()};
    enemyTurn.time.elapsed=times[probe];
}
void waveTransitionReviewStep(const Layout& l){
    static int sample=0,phase=0,mask=0,expectedStage=0,expectedWave=0;
    static int boardCount=0;static float travelStart=0,stopTravel=0;
    static bool done=false,layerSeen=false;
    if(done)return;
    if(phase==0){
        run=Run();run.roster=&roster;run.choosing=false;run.stage=0;run.wave=sample==0?0:sample==1?3:14;
        run.lives=run.maxLives=5;run.enemyHp=run.enemyMax=1;holdVitals=true;debugFirstBoss=false;
        run.families[0]=Sword;run.families[1]=Armor;run.families[2]=Boots;
        run.setShape(castleShape(0));Block sword;sword.family=Sword;sword.level=1;run.board={sword};
        boardCount=(int)run.board.size();expectedStage=sample==2?1:0;expectedWave=sample==0?1:sample==1?4:0;
        action=CombatAction();enemyTurn=EnemyTurn();waveTransition=MergeCombat::WaveTransition();
        weaponSwap=MergeCombat::WeaponSwap();damagePause=MergeCombat::DamagePause();attackWeaponLevel=0;
        entryElapsed=MergeCastleTransition::Duration;introElapsed=-1;spinFlightFrame=-1;animation=0;
        updateHeroCostume(false);phase=1;mask=0;travelStart=castleScrollSeconds;
        if(!run.attack(stats)){reviewTrace("FAIL wave fixture could not attack");done=true;}
        return;
    }
    if(monsterDrawn&&!(monsterDrawOrder>0&&allyDrawOrder>monsterDrawOrder)){
        reviewTrace("FAIL monster rendered over allied character");done=true;return;
    }
    if(flash>0&&impactDrawOrder>0){
        if(!(impactDrawOrder>allyDrawOrder&&allyDrawOrder>monsterDrawOrder)){
            reviewTrace("FAIL impact effect drawn under actor");done=true;return;
        }
        if(!layerSeen){reviewTrace("PASS monster then allied character and sword then impact effect");reviewCapture("wave-layer-order");layerSeen=true;}
    }
    if(waveTransition.active()){
        const auto& t=waveTransition;
        int bit=t.defeatedVisible()?1:t.travelling()?2:t.arrival()<1?4:8;
        if(t.travelling()&&(monsterDrawn||enemyBodyKnown)){reviewTrace("FAIL next enemy visible during castle travel");done=true;return;}
        const long long heart=robin.heart;const int spins=run.spins;
        reviewTap(l.attack);reviewTap(l.spin);
        if(run.attacking||robin.heart!=heart||run.spins!=spins||(int)run.board.size()!=boardCount){reviewTrace("FAIL transition accepted input or changed board");done=true;return;}
        // Capture the middle of each visible phase, not just its first frame.
        const bool capture=(bit==1&&t.age>=8)||(bit==2&&t.age>=60)||(bit==4&&t.arrival()>=.7f)||(bit==8);
        if(capture&&!(mask&bit)){
            char name[48];std::snprintf(name,sizeof(name),"wave-%d-%s",sample,bit==1?"defeat":bit==2?"travel":bit==4?"incoming":"settled");
            reviewCapture(name);mask|=bit;
        }
        phase=2;return;
    }
    if(phase==2){
        if(mask!=15||run.stage!=expectedStage||run.wave!=expectedWave||!layerSeen||castleScrollSeconds<=travelStart){
            reviewTrace("FAIL wave phases, progression or castle movement");done=true;return;
        }
        stopTravel=castleScrollSeconds;phase=3;return;
    }
    if(phase==3){
        if(castleScrollSeconds!=stopTravel||!monsterDrawn||renderedEnemyX!=(int)(DX*.85f)){
            reviewTrace("FAIL castle or enemy did not stop before controls unlock");done=true;return;
        }
        reviewTrace("PASS defeat travel incoming settle input lock and preserved board");
        if(++sample==3){reviewTrace("DONE wave transition review");done=true;return;}
        phase=0;
    }
}
#include "MergeMonsterPartsReview.inc"
void reviewStep(const Layout& l) {
    if(review&&std::getenv("CS_MONSTER_PARTS_REVIEW")){monsterPartsReviewStep();return;}
    if(review&&std::getenv("CS_WAVE_TRANSITION_REVIEW")){waveTransitionReviewStep(l);return;}
    if(review&&std::getenv("CS_MERGE_ENEMY_PATTERN_REVIEW")){enemyPatternReviewStep(l);return;}
    if(review&&std::getenv("CS_MIST_RESOURCE_REVIEW")){
        if(mistReviewSample>=35||reviewCapturePending)return;
        if(++mistReviewHold<(mistReviewSample==0?120:12))return;
        const int c=mistReviewSample<20?mistReviewSample/2:(mistReviewSample-20)%10;const bool battle=mistReviewSample>=20||mistReviewSample%2;
        bool valid=sprite[MistCastle::image(c,0)]!=nullptr;
        // Interiors now use the independently upgraded facility atlas, rather
        // than the five unused room images from the original hull partition.
        for(int part=6;part<=7;++part)valid=valid&&sprite[MistCastle::image(c,part)]!=nullptr;
        if(!battle)for(int room=0;room<4;++room)valid=valid&&MistCastle::facilityImages[room]==MERGE_REBUILD_ROOMS_IMG+c
            &&MistCastle::facilityLevels[room]==castleRoomLevel(c,room);
        if(battle){
            const Box hullBounds=OriginalCastle::box(64,430,976,610);
            valid=valid&&drawnFrontCover==MistCastle::image(c,8)
                &&drawnFrontCoverBounds.x>=hullBounds.x
                &&drawnFrontCoverBounds.x+drawnFrontCoverBounds.w<=hullBounds.x+hullBounds.w
                &&l.cell==(int)(80*l.scale)&&l.cellH==l.cell
                &&l.board.w==run.shape.width*l.cell
                &&l.board.h==run.shape.height*l.cellH
                &&l.board.x>=0&&l.board.x+l.board.w<=DX;
        }
        const Box mount=castleCannonBox(l);
        valid=valid&&mount.y-mount.h>l.ground&&mount.x+mount.w<DX*.65f;
        reviewTrace(valid?"PASS mist resource parts, opaque closure and elevated tower socket":"FAIL mist resource registration");
        char name[80];if(mistReviewSample>=20)std::snprintf(name,sizeof(name),"background-%02d",mistReviewSample-19);else std::snprintf(name,sizeof(name),"castle-%02d-%s",c+1,battle?"battle":"interior");reviewCapture(name);
        mistReviewHold=0;if(++mistReviewSample==35)reviewTrace("DONE mist resource review");
        return;
    }
    if(review&&std::getenv("CS_MERGE_ATTACK_STAT_REVIEW")){
        static int phase=0,hold=0;static long long before=0;
        if(phase==0){
            if(entering())return;
            cocos2d::Director::getInstance()->setDisplayStats(false); // Keep the reviewed lever unobscured by the diagnostic HUD.
            introElapsed=-1;animation=0;run.board.clear();run.tray.clear();message.clear();messageTime=0;
            for(int i=0;i<2;++i){Block b;b.family=Gloves;b.level=1;b.x=i;b.y=0;run.board.push_back(b);}
            {Block sword;sword.family=Sword;sword.level=2;sword.x=2;sword.y=0;run.board.push_back(sword);}
            updateHeroCostume(false);attackDisplayKnown=false;attackGainTime=0;phase=1;return;
        }
        if(phase==1&&++hold>=5){
            before=hero.ps[PS_DMG];
            if(!run.drop(false,1,0,0)){reviewTrace("FAIL glove merge fixture");phase=3;return;}
            updateHeroCostume();phase=2;hold=0;return;
        }
        if(phase==2&&++hold>=8){
            const long long after=hero.ps[PS_DMG];
            reviewTrace(after>before&&attackDisplay.target==after?"PASS glove merge raises actual hero attack and status target":"FAIL attack stat did not increase");
            reviewTrace(attackGainTime>0&&attackGain==after-before&&attackDisplay.value>before&&attackDisplay.value<after?"PASS exact attack gain and animated status value":"FAIL attack gain presentation");
            reviewCapture("glove-merge-attack-gain");phase=3;hold=0;
        }
        if(phase==3&&++hold>=45){
            Run probe=run;probe.choosing=false;probe.attacking=false;probe.lost=false;
            const bool started=probe.attack(stats);
            bool passive=started&&probe.shots.size()==1&&probe.shots[0].block.family==Sword;
            for(const auto& shot:probe.shots)passive=passive&&shot.block.family!=Gloves;
            reviewTrace(passive&&stats.weapon==std::max(1LL,std::min(hero.ps[PS_DMG],100000000LL))?
                "PASS gloves are passive and sword uses the actual increased attack stat":"FAIL passive glove attack stat");
            reviewTrace(sprite[MERGE_REBUILD_UI_IMG+MergeCastleArt::Gear]?"PASS gold gear spin icon loaded":"FAIL spin icon asset");
            reviewCapture("glove-passive-sword-lever-ready");reviewTrace("DONE attack stat review");phase=4;
        }
        return;
    }
    if(review&&std::getenv("CS_MERGE_TURRET_REVIEW")){
        static int castle=0,phase=0;static bool done=false,launchCaptured=false;
        static long long expectedHp=1000000;
        if(done)return;
        if(phase==0){
            if(entering())return;
            robin.castleProgress.parts[castle][3]=5;
            introElapsed=-1;animation=0;entryElapsed=MergeCastleTransition::Duration;
            run.stage=castle;run.wave=1;run.board.clear();run.tray.clear();run.choosing=false;run.attacking=false;run.lost=false;
            run.enemyHp=run.enemyMax=1000000;run.enemyGuard=0;run.shots.clear();run.nextShot=0;
            enemyTurn=EnemyTurn();action=CombatAction();turretFire.age=-1;combatNumbers.clear();flash=0;
            MonsterBoard::ensure();
            if(!run.fireCannon(123)){reviewTrace("FAIL turret fixture");done=true;return;}
            expectedHp=1000000-(run.monsterNpc>=0?MonsterParts::incomingDamage(123,run.monsterLoadout()):123);
            beginCombatAction();launchCaptured=false;phase=1;return;
        }
        if(action.index<0)return;
        const int age=action.time.elapsed;
        if(run.nextShot!=(action.time.applied?1:0)||run.enemyHp!=(action.time.applied?expectedHp:1000000)){
            reviewTrace("FAIL turret damage timing or duplicate impact");done=true;return;
        }
        char name[96];
        if(!launchCaptured&&age>=turretFire.release+1){
            launchCaptured=true;std::snprintf(name,sizeof(name),"turret-%02d-launch",castle+1);reviewCapture(name);
        }
        if(phase==1&&age>=turretFire.release-3){
            std::snprintf(name,sizeof(name),"turret-%02d-prepare",castle+1);reviewCapture(name);phase=2;
        }else if(phase==2&&age>=turretFire.release+(turretFire.type==TurretAttack::Laser?5:turretFire.flight/2)){
            const bool resources=turretFire.type==TurretAttack::Missiles?sprite[castle==2?TURRET_TRIPLE_MISSILE_IMG:TURRET_MISSILE_IMG]!=nullptr:turretFire.type==TurretAttack::Laser?sprite[TURRET_FLAME_LASER_IMG]!=nullptr:sprite[castle==7?TURRET_MAGNETIC_ORB_IMG:castle==5?TURRET_CRYSTAL_ORB_IMG:castle==4?TURRET_HEAVY_SHELL_IMG:TURRET_IRONBALL_IMG]!=nullptr;
            const bool valid=resources&&action.bulletIcon<0&&action.emitterReady&&turretFire.count==(castle==2?3:castle==3?12:1);
            reviewTrace(valid?"PASS turret native type muzzle and burst":"FAIL turret type or burst");
            if(castle==2){
                const auto top=cannonMuzzle(l,2,false,-1,0),middle=cannonMuzzle(l,2,false,-1,1),bottom=cannonMuzzle(l,2,false,-1,2);
                const auto mirror=cannonMuzzle(l,2,true,-1,0);
                reviewTrace(top.y>middle.y&&middle.y>bottom.y&&top.x==middle.x&&middle.x==bottom.x&&
                    std::abs(mirror.x+top.x-DX)<.01f?"PASS three missiles have separate registered barrel origins and mirrored ports":"FAIL triple barrel origins");
            }
            std::snprintf(name,sizeof(name),"turret-%02d-flight",castle+1);reviewCapture(name);phase=3;
        }else if(phase==3&&action.time.applied){
            reviewTrace("PASS turret damage commits exactly once after final projectile arrival");
            std::snprintf(name,sizeof(name),"turret-%02d-impact",castle+1);reviewCapture(name);phase=4;
        }else if(phase==4&&age>=action.time.end-1){
            if(++castle==10){reviewTrace("DONE turret attack review");done=true;return;}
            phase=0;
        }
        return;
    }
    if(review&&std::getenv("CS_REEL_ARMOR_MATCH_REVIEW")){
        static int phase=0,hold=0;
        if(phase==0){
            if(entering())return;
            introElapsed=-1;animation=0;run.board.clear();run.tray.clear();message.clear();messageTime=0;
            for(int i=0;i<3;++i){
                Block b;b.family=i==0?1:i==1?Armor:Sword;b.level=1;b.x=i;b.y=0;
                b.crew=i==0?MergeTrees::CrewAt(1,1,0):-1;
                run.board.push_back(b);reelSymbols[i]=b;
            }
            hasReelSymbols=true;phase=1;return;
        }
        if(phase==1&&++hold>=6){
            const ITEM& item=treeEquipment[Armor-Sword][0];
            const int expected=ITEM_SERIES_FIRST_IMG+ItemSeries::FromIcon(GetItemIcon(item.type,item.detail,item.grade));
            const int grid=GRID_ITEM_FIRST_IMG+GridItems::FromItem(item.type,item.detail);
            const bool matching=sprite[expected]!=nullptr&&sprite[grid]!=nullptr&&expected!=grid;
            reviewTrace(matching?"PASS armor reel and board use separate textures with matching designs":"FAIL armor identity");
            reviewCapture("armor-and-stopped-crew");reviewTrace("DONE reel armor match review");phase=2;
        }
        return;
    }
    if(review&&(std::getenv("CS_MERGE_GLOVE_ICON_REVIEW")||std::getenv("CS_MERGE_STAR_PAD_REVIEW"))){
        static int phase=0,hold=0;
        if(phase==0){
            if(entering())return;
            introElapsed=-1;animation=0;run.board.clear();run.tray.clear();message.clear();messageTime=0;
            for(int i=0;i<3;++i){Block b;b.family=Gloves;b.level=i+1;b.x=i;b.y=0;run.board.push_back(b);reelSymbols[i]=b;}
            if(std::getenv("CS_MERGE_STAR_PAD_REVIEW")){
                for(int i=0;i<3;++i){run.board[i].level=1;run.board[i].family=i==0?MergeTrees::Role(2):i==1?Sword:Gloves;run.board[i].crew=i==0?2:-1;reelSymbols[i]=run.board[i];}
            }
            hasReelSymbols=true;phase=1;return;
        }
        if(phase==1&&++hold>=5){
            bool correct=true;
            for(int hero=0;hero<3;++hero)for(int tier=0;tier<8;++tier){
                const int idx=GetItemIcon(ITEM_GUNTLET+hero,tier,GRADE_NORMAL);
                correct=correct&&NativeGearIcons::IsGlove(idx)&&NativeGearIcons::Hero(idx)==hero&&NativeGearIcons::Tier(idx)==tier;
            }
            reviewTrace(correct?"PASS all 24 glove icons resolve to matching native board artwork":"FAIL native glove icon identities");
            reviewCapture(std::getenv("CS_MERGE_STAR_PAD_REVIEW")?"same-star-pads":"glove-icons-match");reviewTrace("DONE glove icon review");phase=2;
        }
        return;
    }
    if(review&&std::getenv("CS_MERGE_COVER_REVIEW")){
        static int phase=0,stage=0,hold=0;static unsigned captures=0;
        if(phase==0){
            if(entryElapsed>.3f&&!(captures&1)){captures|=1;reviewCapture("cover-01-panic");}
            else if(entryElapsed>.85f&&!(captures&2)){captures|=2;reviewCapture("cover-02-closing");}
            else if(entryElapsed>1.21f&&!(captures&4)){captures|=4;
                reviewTrace(MergeCastleTransition::CoverProgress(entryElapsed)==1&&entryElapsed<MergeCastleTransition::TileLaunch(0,16)?"PASS cover closes before any tile launches":"FAIL cover order");
                reviewCapture("cover-03-closed-before-tiles");}
            else if(!entering()){
                phase=1;introElapsed=-1;run.board.clear();animation=0;
                if(std::getenv("CS_MERGE_CANNON_MAX_REVIEW"))for(int c=0;c<10;++c)robin.castleProgress.parts[c][3]=5;
            }
            return;
        }
        if(phase==1){
            run.stage=stage;run.setShape(castleShape(stage));const auto test=layout();
            int count=0;for(int y=0;y<run.shape.height;++y)for(int x=0;x<run.shape.width;++x)count+=run.shape.contains(x,y);
            if(count!=16+stage*2||test.cell<=0||test.cell!=(int)(80*test.scale)||test.cellH!=test.cell||(stage<9&&test.board.y-test.cellH>test.ground-test.plateDrop-test.plateH)||test.board.y-test.board.h<test.slot.y){reviewTrace("FAIL fixed tile size, growth or health bar clearance");phase=3;return;}
            if(++hold<4)return;hold=0;
            const Box commonFront=OriginalCastle::box(96,430,912,875);
            if(drawnFrontCoverBounds.x!=commonFront.x||drawnFrontCoverBounds.y!=commonFront.y||drawnFrontCoverBounds.w!=commonFront.w||drawnFrontCoverBounds.h!=commonFront.h){reviewTrace("FAIL castle exterior dimensions differ by stage");phase=3;return;}
            const auto savedCannon=robin.castleProgress.parts[stage][3];int previousWidth=0,previousHeight=0;
            bool grows=true;
            for(int level=0;level<6;++level){
                robin.castleProgress.parts[stage][3]=(unsigned char)level;
                const Box gun=castleCannonBox(test);
                grows=grows&&gun.w>previousWidth&&gun.h>previousHeight&&gun.y-gun.h>test.ground&&gun.x+gun.w<=DX*.65f;
                grows=grows&&gun.h==(int)((stage==0?90.f+2.f*level:52.f+4.f*stage+3.f*level)*test.scale);
                previousWidth=gun.w;previousHeight=gun.h;
            }
            robin.castleProgress.parts[stage][3]=savedCannon;
            if(!grows){reviewTrace("FAIL cannon upgrade growth or deck anchor");phase=3;return;}
            if(drawnFrontCover!=MistCastle::image(stage,8)||drawnFrontRimParts!=0){reviewTrace("FAIL full exterior front or border occlusion missing");phase=3;return;}
            const auto& o=drawnFrontCoverBounds;const auto& in=drawnFrontInnerBounds;
            char joins[200];std::snprintf(joins,sizeof(joins),"front-join castle=%d outer=%d,%d,%d,%d inner=%d,%d,%d,%d",stage+1,o.x,o.y,o.w,o.h,in.x,in.y,in.w,in.h);reviewTrace(joins);
            char name[60];std::snprintf(name,sizeof(name),"cover-castle-%02d",stage+1);reviewCapture(name);
            if(++stage==10){reviewTrace("PASS all ten castles share exterior dimensions and artillery grows through six levels");reviewTrace("PASS all ten castles add two cells and stay below health bars");reviewTrace("PASS all ten castles cover the full exterior without foreground rim redraw");phase=2;hold=0;
                run.stage=0;run.setShape(castleShape(0));
                Siege::begin();Siege::phase=0;introElapsed=-1;messageTime=0;message.clear();}
            return;
        }
        if(phase==2){
            static Box playerCover={0,0,0,0};
            if(hold==2){playerCover=drawnFrontCoverBounds;
                reviewTrace(drawnFrontCover==MistCastle::image(Siege::castle,8)?"PASS PVP uses dedicated gold front instead of cropped tower":"FAIL PVP facade source");
                reviewCapture("cover-pvp-player");}
            if(++hold==4){Siege::swapSides();introElapsed=-1;}
            if(hold==8){const auto test=layout();reviewTrace(test.board.y<=test.ground-84*test.scale?"PASS maximum PVP opponent board stays below health bars":"FAIL PVP board overlap");
                const auto& cover=drawnFrontCoverBounds;
                reviewTrace(drawnFrontCover==MistCastle::image(Siege::castle,8)&&cover.x==playerCover.x&&cover.y==playerCover.y&&cover.w==playerCover.w&&cover.h==playerCover.h?
                    "PASS gold front stays registered to outer hull across PVP turns":"FAIL PVP facade moved");
                reviewCapture("cover-pvp-opponent");}
            if(hold>=48){
                bool stable=true;for(int t=0;t<64;++t){const int saved=ticks;ticks=t;
                    const int expected=GetHeroLoopMotion(DIANA,HEROLOOP_NEUTRAL,(t/8%4)*4);
                    stable=stable&&heroNeutralMotion(hero)==expected;ticks=saved;}
                reviewTrace(stable?"PASS Diana neutral holds authored poses without jitter frames":"FAIL Diana neutral timing");
                reviewTrace("DONE cover review");phase=3;
            }
        }
        return;
    }
    //---- 공성전 디버그 리뷰 ----
    //
    //내 시작 뽑기 → 상대 시작 뽑기 → 돌리기 세 번 → 공격 → 상대 턴(룰렛·끌기·
    //공격을 손으로) 한 바퀴를 실제 입력으로 돌리고 장면마다 남긴다.
    if(review&&std::getenv("CS_MERGE_SIEGE_REVIEW")){
        if(std::getenv("CS_MERGE_PVP_CONTROLS_REVIEW")){
            static bool captured=false;
            if(!captured&&!entering()&&!introActive()&&!spinFlying()&&!deckArriving()&&Siege::phase==0&&animation==0){
                const bool centered=std::abs((l.spin.x+l.attack.x+l.attack.w)-DX)<=1;
                const long long hearts=robin.heart;
                reviewTap({DX-12,l.spin.y,8,l.spin.h});
                reviewTrace(centered&&l.cannon.w==0&&l.cannon.h==0&&robin.heart==hearts&&!run.attacking?
                    "PASS PVP two centered buttons and no cannon input":"FAIL PVP controls");
                reviewCapture("pvp-two-controls");reviewTrace("DONE PVP controls review");captured=true;
            }
            return;
        }
        static int t=0,stage=0;static long long hpBefore=0,poolBefore=0;static size_t foeBlocks=0;
        static bool reelShot=false,dragShot=false,attackShot=false,introShot=false;
        if(stage>=9)return;
        ++t;
        if(entering()||spinFlying()||deckArriving())return;
        if(stage==0){
            if(!introShot&&Siege::phase==3&&introActive()&&introElapsed>1.5f){introShot=true;reviewCapture("siege-00-foe-intro");}
            if(Siege::phase==0&&!introActive()&&t>10){reviewTrace(siegeActive&&!Siege::foe.board.empty()?"PASS siege starts with an opponent board":"FAIL siege start");reviewCapture("siege-01-start");stage=1;t=0;}
            return;
        }
        const bool ready=animation==0&&!run.attacking&&Siege::phase==0&&!introActive();
        //상대 턴은 내 돌리기마다 온다(버튼 한 번 = 턴 하나). 어느 단계든 상대 턴 장면을 남긴다.
        if(Siege::phase==1){
            if(!reelShot&&Siege::step==Siege::Spinning&&animation>REEL_SPIN_FRAMES/2){reelShot=true;reviewCapture("siege-02-foe-reel");}
            if(!dragShot&&Siege::step==Siege::Dragging&&Siege::dragFrame==24){dragShot=true;reviewCapture("siege-03-foe-drag");}
            if(!attackShot&&Siege::step==Siege::Attacking&&run.attacking&&action.index>=0){attackShot=true;reviewCapture("siege-04-foe-attack");}
        }
        if(stage>=1&&stage<=3){if(ready&&t>20){reviewTap(l.spin);++stage;t=0;}return;}
        if(stage==4){if(ready&&t>20){hpBefore=run.enemyHp;poolBefore=run.lives;foeBlocks=Siege::foe.board.size();reviewTap(l.attack);stage=5;t=0;}return;}
        if(stage==5){
            if(Siege::phase==0&&!run.attacking&&(Siege::foeDamage>0||t>3000)){
                reviewTrace(run.enemyHp<hpBefore?"PASS siege player attack damages the opponent castle":"FAIL siege player damage");
                reviewTrace(reelShot?"PASS siege opponent spins the reels on screen":"FAIL siege opponent reel");
                reviewTrace(dragShot?"PASS siege opponent drags a merge by hand":"FAIL siege opponent drag");
                reviewTrace(Siege::foeDamage>0&&run.lives<poolBefore?"PASS siege opponent attack reaches my castle":"FAIL siege opponent damage");
                reviewTrace(Siege::foe.board.size()>=3?"PASS siege opponent board persists":"FAIL siege opponent board");
                stage=6;t=0;
            }
            return;
        }
        if(stage==6&&t>8){Siege::expanded=true;stage=7;t=0;return;}
        if(stage==7&&t>3){reviewCapture("siege-05-expanded");reviewTrace("DONE siege review");Siege::expanded=false;stage=9;}
        return;
    }
    if(review&&std::getenv("CS_ROULETTE_TRASH_REVIEW")){
        static int phase=0,hold=0,discarded=0;static long long paid=0;
        if(phase==3)return;
        if(phase==0){
            run=Run();run.roster=&roster;run.choosing=false;run.shape=castleShape(0);
            run.families[0]=0;run.families[1]=Sword;run.families[2]=Armor;
            for(int y=0;y<4;++y)for(int x=0;x<4;++x){Block b;b.family=Armor;b.x=x;b.y=y;b.level=1;run.board.push_back(b);}
            introElapsed=-1;entryElapsed=-1;animation=0;robin.heart=20;observedHearts=20;
            updateHeroCostume(false);action=CombatAction();enemyTurn=EnemyTurn();
            reviewTap(layout().spin);paid=robin.heart;
            reviewTrace(paid==19&&animation>0&&run.tray.size()==3?"PASS full grid can spin for one heart":"FAIL full grid spin");
            phase=1;return;
        }
        if(phase==1){
            if(animation>0||spinFlying())return;
            if(run.tray.size()!=3||run.board.size()!=16){reviewTrace("FAIL blocked results were lost or overlapped board");phase=3;return;}
            const int spins=run.spins;reviewTap(layout().spin);
            reviewTrace(robin.heart==paid&&run.spins==spins?"PASS unresolved results block repeated spins without charge":"FAIL unresolved reroll charged");
            reviewCapture("trash-01-full-grid-pending");phase=2;hold=0;return;
        }
        if(++hold<8)return;hold=0;
        if(!run.tray.empty()){
            const Layout test=layout();const Box source=slotWindow(test.slot,0),bin=rouletteTrash(test);
            const int before=(int)run.tray.size();
            static bool dragging=false;
            if(!dragging){
                MergeRouletteTouch(0,997,source.x+source.w/2,source.y-source.h/2);
                MergeRouletteTouch(1,997,bin.x+bin.w/2,bin.y-bin.h/2);
                dragging=true;return;
            }
            reviewTrace(trashOpenness>.5f?"PASS trash opens its mouth near dragged item":"FAIL trash mouth proximity");
            MergeRouletteTouch(2,997,bin.x+bin.w/2,bin.y-bin.h/2);dragging=false;
            ++discarded;
            reviewTrace(run.tray.size()==before-1&&run.board.size()==16&&robin.heart==paid?"PASS drag result to trash removes exactly one with no extra charge":"FAIL trash drop");
            if(discarded==1)reviewCapture("trash-02-discard-one");
        }
        if(run.tray.empty()){
            reviewTrace(discarded==3&&run.attacking?"PASS resolving final result starts the normal enemy turn":"FAIL pending turn completion");
            reviewCapture("trash-03-all-resolved");reviewTrace("DONE roulette trash review");phase=3;
        }
        return;
    }
    if(review&&std::getenv("CS_MERGE_COSTUME_REVIEW")){
        static int phase=0,weaponMask=0;if(phase==2)return;
        if(phase==1){
            static unsigned swapCaptures=0;
            static int pausedShot=-1;
            if(damagePause.remaining==MergeCombat::DamageNumberFrames+MergeCombat::DamageBreathFrames)pausedShot=run.nextShot;
            if(damagePause.waiting()&&pausedShot>=0&&run.nextShot!=pausedShot){reviewTrace("FAIL next action advanced before damage feedback ended");phase=2;return;}
            if(action.index>=0&&weaponSwap.running()){
                if(action.time.elapsed!=0){reviewTrace("FAIL attack started before weapon attached and settled");phase=2;return;}
                const int ages[3]={18,40,48};
                const char* names[3]={"weapon-01-overhead-orbit","weapon-02-snap-to-hand","weapon-03-costume-attached"};
                for(int i=0;i<3;++i)if(!(swapCaptures&(1u<<i))&&weaponSwap.age>=ages[i]){swapCaptures|=1u<<i;reviewCapture(names[i]);}
            }
            if(action.index>=0&&run.shots[action.index].block.family==Sword){
                const int level=run.shots[action.index].block.level;
                const ITEM& expected=treeEquipment[0][level-1];
                if((!weaponSwap.running()&&hero.equip[EQUIP_WEAPON].detail!=expected.detail)||action.caster.equip[EQUIP_WEAPON].detail!=expected.detail||costumeEffectTicks!=0){
                    reviewTrace("FAIL attacking sword costume or unwanted level up");phase=2;return;
                }
                static bool crystalCaptured=false;
                if(level==2&&weaponSwap.age>=MergeCombat::WeaponSwap::AttachFrame&&!crystalCaptured){
                    crystalCaptured=true;reviewCapture("weapon-04-two-cell-crystal-blade");
                }
                weaponMask|=1<<level;
            }
            if(enemyTurn.started){
                reviewTrace(weaponMask==((1<<1)|(1<<2)|(1<<3))&&attackWeaponLevel==0&&hero.equip[EQUIP_WEAPON].detail==treeEquipment[0][2].detail&&costumeEffectTicks==0?
                    "PASS each sword attacks in its own costume and best weapon returns before enemy turn without level up":"FAIL attack weapon restoration");
                reviewTrace(swapCaptures==7?"PASS overhead orbit snap attachment and attack ordering":"FAIL missing weapon swap phases");
                reviewTrace(!damagePause.waiting()?"PASS damage number fade and extra breath precede next turn":"FAIL turn entered during damage feedback");
                reviewCapture("costume-weapon-level-up");reviewTrace("DONE costume review");phase=2;
            }
            return;
        }
        phase=1;
        run.board.clear();introElapsed=-1;entryElapsed=MergeCastleTransition::Duration;
        for(int g=0;g<GearCount;++g){
            Block b;b.family=Sword+g;b.level=2;run.board.push_back(b);
            b.level=4;run.board.push_back(b);
        }
        updateHeroCostume();bool best=true;
        for(int g=0;g<GearCount;++g){
            const ITEM& actual=g==0&&weaponSwap.running()?incomingWeapon:hero.equip[costumeSlots[g]];
            const ITEM& expected=treeEquipment[g][3];
            best=best&&costumeLevels[g]==4&&actual.type==expected.type&&actual.detail==expected.detail;
        }
        reviewTrace(best&&costumeEffectTicks==30?"PASS best landed equipment in all six costume slots triggers level up":"FAIL costume selection");
        costumeEffectTicks=0;std::reverse(run.board.begin(),run.board.end());updateHeroCostume();
        reviewTrace(costumeEffectTicks==0?"PASS rearranging equipment does not repeat level up":"FAIL repeated costume effect");
        run.board.erase(std::find_if(run.board.begin(),run.board.end(),[](const Block& b){return b.family==Sword&&b.level==4;}));updateHeroCostume();
        reviewTrace(costumeLevels[0]==2&&costumeEffectTicks==0?"PASS downgrade does not trigger level up":"FAIL downgrade level up");
        Block upgrade;upgrade.family=Sword;upgrade.level=5;run.board.push_back(upgrade);updateHeroCostume();
        reviewTrace(costumeLevels[0]==5&&costumeEffectTicks==30?"PASS higher grade weapon triggers level up":"FAIL missing upgrade level up");
        run.board.clear();updateHeroCostume();costumeEffectTicks=0;
        Block weapon;weapon.family=Sword;weapon.level=3;run.board.push_back(weapon);
        introElapsed=0;updateHeroCostume();
        const bool hidden=costumeLevels[0]==0&&costumeEffectTicks==0;
        introElapsed=-1;updateHeroCostume();
        reviewTrace(hidden&&costumeLevels[0]==3&&costumeEffectTicks==30?"PASS costume changes only after grid landing":"FAIL premature costume");
        costumeEffectTicks=0;weapon.level=1;run.board.push_back(weapon);updateHeroCostume();
        reviewTrace(costumeEffectTicks==0?"PASS weaker roulette weapon does not trigger level up":"FAIL weaker weapon level up");
        weapon.level=3;run.board.push_back(weapon);updateHeroCostume();
        reviewTrace(costumeEffectTicks==0?"PASS equal roulette weapon does not trigger level up":"FAIL equal weapon level up");
        run.board.pop_back();
        weapon.level=2;weapon.x=2;weapon.y=0;run.board.push_back(weapon);
        run.enemyHp=run.enemyMax=1000000000LL;
        run.setVitals(stats.heroHealth,stats.heroArmor);run.attack(stats);
        action=CombatAction();enemyTurn=EnemyTurn();animation=0;
        return;
    }
    if(review&&!entering()){
        static bool checked=false;
        if(!checked){
            checked=true;const Layout fixed=layout();const float s=DX/640.f;const int lift=(int)castleSceneLift();
            const bool aligned=fixed.board.y-fixed.board.h>=fixed.slot.y&&fixed.board.y-(run.shape.height>4?fixed.cellH:0)<=fixed.ground-fixed.plateDrop-fixed.plateH+(int)(2*s)&&
                fixed.slot.y==(int)(280*s)+lift&&fixed.heart.y==(int)(156*s)+lift&&
                fixed.spin.y==(int)(12*s)+(int)(56*1.2f*s)&&fixed.attack.y==fixed.spin.y;
            //가운데 맞춤은 lobbyCastleLift 가 책임진다(2.2 비율에서 성 중심 = 화면 가운데). 장면 들어올림이
            //그 값에서 포대용 8 만 뺀 것인지만 본다 - 성 중심을 여기서 다시 유도하면 상수가 어긋날 때마다 깨진다.
            //긴 화면은 붙박이 몬스터 판이 성 지붕 위에 들어가도록 덜 올린 값이 기대값이다(castleSceneLift).
            const float wanted=std::max(-25.f*s,std::min(MergeCombat::lobbyCastleLift((float)DX,(float)DY)-25.f*s,topPanelCeiling(std::max(4,(int)run.shape.height))-((1445.f-83.f)*(DX/1089.f*1.04f)+34*s)));
            const bool centered=std::abs(DY-DX*2.2f)>1.f||std::abs(castleSceneLift()-wanted)<1.f;
            if(!(aligned&&centered)){char why[300];std::snprintf(why,sizeof(why),"layout board %d-%d slot %d/%d heart %d/%d spin %d/%d attack %d ground %d plate %d+%d cell %d lift %d DY %d",
                fixed.board.y,fixed.board.y-fixed.board.h,fixed.slot.y,(int)(280*s)+lift,fixed.heart.y,(int)(156*s)+lift,fixed.spin.y,(int)(12*s)+(int)(56*1.2f*s),fixed.attack.y,fixed.ground,fixed.plateDrop,fixed.plateH,fixed.cell,lift,DY);reviewTrace(why);}
            reviewTrace(aligned&&centered?"PASS gameplay shares centered castle lift while bottom actions stay fixed":"FAIL gameplay responsive layout");
        }
    }
    if(review&&std::getenv("CS_MERGE_DECK_MERGE_REVIEW")) {
        static int phase=0,scenario=0;static bool gathered=false,warped=false;
        if(scenario>=2)return;
        const char* prefix=scenario==0?"different":"identical";
        if(phase==0){
            run=Run();run.roster=&roster;run.choosing=false;run.setShape(castleShape(0));run.families[0]=0;
            run.setVitals(stats.heroHealth,stats.heroArmor);
            const int first=roster.first(0,1),second=scenario==0&&roster.count[0][1]>1?roster.crew[0][1][1]:first;
            for(int crew:{first,second}){Block b;b.family=0;b.crew=crew;run.tray.push_back(b);run.autoPlace(0);}
            entryElapsed=MergeCastleTransition::Duration;introElapsed=-1;animation=0;spinFlightFrame=-1;
            deckMerge=DeckMergePresentation();deckMergeSeen=run.mergeSeq;
            for(auto& reveal:deckReveal)reveal=MergeCombat::ResidentReveal();
            for(const auto& b:run.board)deckReveal[b.crew].age=MergeCombat::ResidentReveal::Duration;
            gathered=warped=false;phase=1;return;
        }
        if(phase==1){
            char name[80];std::snprintf(name,sizeof(name),"deck-merge-%s-01-before",prefix);reviewCapture(name);phase=2;return;
        }
        if(phase==2){
            const auto a=blockBox(run.board[0],l),b=blockBox(run.board[1],l);
            const float ax=a.x+a.w*.5f,ay=a.y-a.h*.5f,bx=b.x+b.w*.5f,by=b.y-b.h*.5f;
            MergeRouletteTouch(0,999,ax,ay);MergeRouletteTouch(1,999,bx,by);MergeRouletteTouch(2,999,bx,by);
            reviewTrace(run.mergeSeq==1&&run.board.size()==1&&run.board[0].level==2?"PASS deck merge triggered by actual grid drag":"FAIL deck merge drag");phase=3;return;
        }
        if(phase==3){
            if(deckMerge.time.converging()){
                if(deckMergeGhostsDrawn!=2||deckReveal[deckMerge.result.crew].visible()){
                    reviewTrace("FAIL merge materials or premature result on deck");scenario=2;return;
                }
                if(!gathered&&deckMerge.time.age>=7){
                    const float before=std::abs(deckMerge.fromX[0]-deckMerge.fromX[1]);
                    reviewTrace(std::abs(deckMergeGhostX[0]-deckMergeGhostX[1])<before?"PASS two deck materials converge before result appears":"FAIL deck materials not converging");
                    const auto hearts=robin.heart;reviewTap(l.attack);
                    reviewTrace(robin.heart==hearts&&!run.attacking?"PASS attacks wait for deck merge presentation":"FAIL attack interrupted deck merge");
                    char name[80];std::snprintf(name,sizeof(name),"deck-merge-%s-02-gather",prefix);reviewCapture(name);gathered=true;
                }
            }
            if(!warped&&deckMerge.time.age>=MergeCombat::DeckMergeTimeline::GatherFrames+10){
                reviewTrace(deckMergeGhostsDrawn==0&&deckReveal[deckMerge.result.crew].visible()?"PASS material pair becomes the actual merged crew with native warp":"FAIL deck merge result");
                char name[80];std::snprintf(name,sizeof(name),"deck-merge-%s-03-warp",prefix);reviewCapture(name);warped=true;
            }
            if(!deckArriving()){
                reviewTrace(gathered&&warped&&deckResidentCount==1?"PASS deck merge finishes with one result and no stale materials":"FAIL deck merge cleanup");
                ++scenario;phase=0;if(scenario==2)reviewTrace("DONE deck merge review");
            }
        }
        return;
    }
    if(review&&std::getenv("CS_MERGE_VITALS_REVIEW")) {
        static int phase=0;static long long before=0,expected=0;
        if(phase==0){
            run=Run();run.roster=&roster;run.choosing=false;run.setShape(castleShape(0));
            run.setVitals(stats.heroHealth,stats.heroArmor);
            run.enemyAttack=std::max(1LL,hpFor(0,0)/12);
            run.enemyHp=run.enemyMax=1000000;
            for(int crew:{0,3,5}){Block b;b.family=MergeTrees::Role(crew);b.level=MergeTrees::Star(crew);b.crew=crew;run.tray.push_back(b);run.autoPlace(0);}
            Block armor;armor.family=Armor;run.tray.push_back(armor);run.autoPlace(0);
            entryElapsed=MergeCastleTransition::Duration;introElapsed=-1;animation=0;spinFlightFrame=-1;
            for(auto& reveal:deckReveal)reveal=MergeCombat::ResidentReveal();
            reviewTrace(run.maxLives==hero.ps[PS_HP]&&run.baseArmor==wornGuard()&&run.maxLives>20?
                "PASS native hero HP and armor match actual stats":"FAIL native hero stats");
            reviewTrace(heartCapacity==10?"PASS ten enlarged resource hearts":"FAIL heart count");
            char native[128];std::snprintf(native,sizeof(native),"native HP=%lld armor=%lld block armor=%lld",run.maxLives,run.baseArmor,run.forecast(stats).protect);reviewTrace(native);
            phase=1;return;
        }
        if(phase==1&&deckReveal[0].age>=12){reviewCapture("vitals-01-companion-warp");phase=2;return;}
        if(phase==2&&!deckArriving()&&guardDisplay.value==guardDisplay.target){
            reviewCapture("vitals-02-native-bars-ten-hearts");phase=3;return;
        }
        if(phase==3){
            //첫 공격 때 갑옷 블록이 통에 찬 채로 들어오므로, 반격 = 통 전부 + 체력의 1/8 이면 체력이 그만큼 깎인다.
            run.enemyAttack=run.baseArmor+run.forecast(stats).protect+std::max(1LL,run.maxLives/8);
            before=run.lives;expected=std::max(1LL,run.maxLives/8);
            reviewTap(l.attack);phase=4;return;
        }
        if(phase==4&&enemyTurn.started&&enemyTurn.time.applied){
            reviewTrace(run.lives==before-expected?"PASS actual counter damage uses native armor and equipment":"FAIL native counter damage");
            reviewTrace(heroHealthDisplay.value>run.lives&&heroHealthDisplay.value<=before?"PASS native HP bar animates after impact":"FAIL native HP animation");
            reviewCapture("vitals-03-native-counter-damage");reviewTrace("DONE native vitals review");phase=5;
        }
        return;
    }
    if(review&&std::getenv("CS_MERGE_GRADE_REVIEW")){
        static int phase=0,wait=0;
        if(phase==0){
            run=Run();run.roster=&roster;run.choosing=false;run.setShape(castleShape(0));
            entryElapsed=MergeCastleTransition::Duration;introElapsed=-1;animation=0;spinFlightFrame=-1;
            Block gear;gear.family=Helm;gear.level=4;run.tray.push_back(gear);run.autoPlace(0);
            shownGrades.clear();gradeAccents.clear();phase=1;return;
        }
        if(phase==1&&!gradeAccents.empty()&&gradeAccents[0].age>=8){
            reviewCapture("grade-01-four-star");reviewTrace("PASS four star landing accent");phase=2;return;
        }
        if(phase==2&&++wait>=42){
            Block other=run.board[0];run.tray.push_back(other);
            const bool merged=run.place(true,0,other.x,other.y);
            reviewTrace(merged&&run.board[0].level==5?"PASS actual model merge produces five stars":"FAIL grade merge fixture");phase=3;return;
        }
        if(phase==3&&!gradeAccents.empty()&&gradeAccents.back().block.level==5&&gradeAccents.back().age>=8){
            reviewCapture("grade-02-five-star-merge");reviewTrace("PASS five star merge accent");phase=4;return;
        }
        if(phase==4&&gradeAccents.empty()){reviewTrace("DONE grade accent review");phase=5;}
        return;
    }
    if(review&&std::getenv("CS_MERGE_PROFILE_PATH")) {
        static bool prepared=false;
        if(!prepared) {
            prepared=true;Roster limited;for(int c=0;c<12;++c)limited.add(MergeTrees::Role(c),MergeTrees::Star(c),c);roster=limited;
            run=Run();run.roster=&roster;run.choosing=false;run.setShape(castleShape(0));
            for(int c:{0,3,5}){Block b;b.family=MergeTrees::Role(c);b.crew=c;b.x=(int)run.board.size()*2;b.y=0;run.board.push_back(b);}
            for(int g=Sword;g<FamilyCount;++g){Block b;b.family=g;run.tray.push_back(b);run.autoPlace(0);}
            entryElapsed=MergeCastleTransition::Duration;introElapsed=-1;spinFlightFrame=-1;animation=0;
            if(std::getenv("CS_MERGE_PROFILE_TEXTS")) {
                const int count=std::min(512,std::max(0,std::atoi(std::getenv("CS_MERGE_PROFILE_TEXTS"))));
                for(int i=0;i<count&&totalFontLabelCnt<MAXFONTLABELCNT-100;++i) {
                    char text[32];std::snprintf(text,sizeof(text),"-%d",10000+i);
                    label(text,DX/2,DY/2,.92f);
                }
            }
        }
        return;
    }

    if(review&&std::getenv("CS_MERGE_ARRIVAL_REVIEW")){arrivalReviewStep(l);return;}
    if(review&&std::getenv("CS_MERGE_TURN_REVIEW")){turnReviewStep(l);return;}
    if(review&&std::getenv("CS_MERGE_COMBAT_REVIEW")) {
        static int phase=0,expectedCrew=0,previous=-1;
        static bool bulletSeen=false,spawnSeen=false,heroSeen=false,bulletCapture=false,heroCapture=false,done=false,previousComplete=false,damageCapture=false,guardCapture=false;
        if(done)return;
        if(phase==0) {
            run=Run();run.roster=&roster;run.choosing=false;run.setShape(castleShape(0));
            run.lives=2;run.maxLives=5;run.enemyHp=100000;run.enemyMax=200000;holdVitals=true;
            Block a;a.family=0;a.crew=roster.first(0,1);a.x=0;a.y=0;
            Block b=a;b.x=2;run.board={a,b};
            const bool merged=run.place(false,0,2,0);
            reviewTrace(merged&&run.board.size()==1&&run.board[0].level==2?"PASS actual crew merge fixture":"FAIL crew merge fixture");
            const int mergedCrew=run.board[0].crew;
            int bullet=-1,caller=-1;
            for(int c=0;c<64;++c) {
                Block test;test.family=MergeTrees::Role(c);test.crew=c;test.level=MergeTrees::Star(c);
                const int skill=actionSkill(test),kind=skill>=0?SkillKind(skill):-1;
                if(c!=mergedCrew&&kind==CREWBULLET&&bullet<0)bullet=c;
                if(c!=mergedCrew&&(kind==HEROSKILL||kind==SUMMONHERO)&&caller<0)caller=c;
            }
            reviewTrace(bullet>=0&&caller>=0?"PASS native bullet and hero request fixtures":"FAIL native skill fixtures");
            //겹치지 않는 빈 자리에 세운다 - 겹친 판으로는 공격이 안 나간다(boardResolved).
            const auto seat=[&](Block block){
                for(int y=0;y<run.shape.height;++y)for(int x=0;x<run.shape.width;++x){block.x=x;block.y=y;if(run.fits(block)){run.board.push_back(block);return;}}
            };
            for(int c:{bullet,caller})if(c>=0) {
                Block block;block.family=MergeTrees::Role(c);block.level=MergeTrees::Star(c);block.crew=c;seat(block);
            }
            Block armor;armor.family=Armor;seat(armor);
            expectedCrew=3;entryElapsed=MergeCastleTransition::Duration;introElapsed=-1;
            animation=0;action=CombatAction();spinFlightFrame=-1;phase=1;return;
        }
        if(phase==1) {
            if(deckArriving())return;
            reviewTrace(deckResidentCount==expectedCrew?"PASS every deployed crew including merged crew is drawn":"FAIL missing deck crew");
            reviewCapture("combat-01-formation-bars");phase=2;return;
        }
        if(phase==2){reviewTap(l.attack);phase=3;return;}
        if(phase==3) {
            if(!damageCapture)for(const auto& number:combatNumbers)if(!number.defense&&number.age<10) {
                damageCapture=true;reviewTrace("PASS actual impact damage floats above target");
                reviewCapture("combat-06-damage-number");break;
            }
            bool defenseApplied=false;
            for(int i=0;i<run.nextShot&&i<(int)run.shots.size();++i)
                if(DefensiveGear(run.shots[i].block.family))defenseApplied=true;
            if(!guardCapture&&defenseApplied&&guardDisplay.target>0&&guardDisplay.value>guardDisplay.target*.15f&&guardDisplay.value<guardDisplay.target*.9f) {
                bool gain=false;for(const auto& number:combatNumbers)if(number.defense&&number.age<28)gain=true;
                reviewTrace(gain?"PASS defense gain floats while guard bar animates":"FAIL missing defense gain amount");
                guardCapture=true;reviewCapture("combat-05-guard-charge");
            }
        }
        if(action.index>=0) {
            if(previous!=action.index){
                if(previous>=0&&!previousComplete){reviewTrace("FAIL next actor started before recovery completed");done=true;return;}
                previous=action.index;previousComplete=false;
                reviewTrace("PASS next actor starts after previous completion");
            }
            const int expected=action.time.applied?action.index+1:action.index;
            if(run.nextShot!=expected){reviewTrace("FAIL damage applied before impact or duplicated");done=true;return;}
            if(action.bulletIcon>=0&&MergeCombat::bulletAppearance(action.time.elapsed,action.time.release)>=1.f&&action.time.elapsed<action.time.release&&!spawnSeen) {
                spawnSeen=true;
                reviewTrace(action.emitterReady&&action.emitterY>l.ground?"PASS projectile forms above caster head before launch":"FAIL projectile formation origin");
                reviewCapture("combat-02a-bullet-formation");
            }
            if(action.time.flying()&&action.bulletIcon>=0) {
                if(action.time.elapsed<=action.time.release+1&&
                    (std::abs(action.bulletX-action.emitterX)>2||std::abs(action.bulletY-action.emitterY)>2)) {
                    reviewTrace("FAIL projectile jumped away from its head emitter");done=true;return;
                }
                bulletSeen=true;
                if(!bulletCapture){bulletCapture=true;reviewCapture("combat-02-native-bullet");}
            }
            if(!action.heroMotion.empty()&&action.skill>=0&&action.time.elapsed>=action.heroStart) {
                heroSeen=true;
                if(!heroCapture){heroCapture=true;reviewCapture("combat-03-requested-hero-skill");}
            }
        }
        if(action.index<0&&previous>=0)previousComplete=action.time.finished();
        if(!run.attacking&&phase==3) {
            reviewTrace(bulletSeen?"PASS companion generates native roulette projectile":"FAIL missing native projectile");
            reviewTrace(spawnSeen?"PASS visible formation phase precedes projectile flight":"FAIL skipped projectile formation");
            reviewTrace(damageCapture&&guardCapture?"PASS damage numbers and animated defense gain verified":"FAIL missing hit or defense feedback");
            reviewTrace(heroSeen?"PASS companion requests full native hero skill motion":"FAIL missing hero handoff");
            reviewTrace(deckResidentCount==expectedCrew?"PASS all merged crew remain after combat":"FAIL crew disappeared after combat");
            reviewTrace(run.nextShot==(int)run.shots.size()?"PASS exactly one impact per actor":"FAIL incomplete action sequence");
            reviewCapture("combat-04-complete");reviewTrace("DONE merge combat review");done=true;
        }
        return;
    }

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
            reviewTap(l.spin);reviewTap(l.cannon);reviewTap(l.attack);reviewTap(l.exit);
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
            growth=growth&&shape.valid()&&count==16+2*c&&count>=previous&&check.setShape(shape)&&check.board.size()==3;
            previous=count;
        }
        reviewTrace(growth&&previous==34?"PASS castle grids grow from 16 to 34 playable cells":"FAIL castle grid growth");
    }
    const int t=ticks-reviewCombatTick;
    if(t==9)MergeRouletteSetHeartCapacity(5);
    if(t==10) {reviewLayout(l,"01-families");reviewCapture("01-families");}
    if(t==16)MergeRouletteSetHeartCapacity(20);
    //---- 룰렛은 세 번 ----
    //
    //전에는 네 번 돌렸다. 무기 ★1 이 1×2 가 되면서(칸 모양은 그림이 정한다)
    //24칸 판에 ★1 열다섯이 합치지 않고는 다 서지 못한다 - 넷째 결과가 트레이에
    //남아 "칸을 비워주세요" 가 뜨고, 그 뒤의 공격 검사가 전부 막혔다. 자리가
    //없을 때의 흐름은 t==950 대가 따로 본다.
    if(t==30||t==190||t==350) {
        long long before=robin.heart;long long life=run.lives;
        reviewTap(l.spin);
        reviewTrace(robin.heart==before-1&&run.lives==life&&!run.tray.empty()?"PASS spin costs one heart without enemy turn":"FAIL spin");
        if(t==190)reviewTrace(robin.heart==before-1&&!run.tray.empty()?"PASS right lever pull spins once":"FAIL lever pull");
    }
    if(t==32) {
        long long balance=robin.heart;reviewTap(l.spin);reviewTap(l.attack);
        reviewTrace(heartBlink>0&&spentHeart==heartDisplay&&robin.heart==balance?"PASS one heart blinks and repeat input cannot charge twice":"FAIL heart animation");
        reviewCapture("06-heart-spend");
        reviewTrace(gearAngle>gearStartAngle&&gearAngle<gearStartAngle+450.f?"PASS slot gears rotate during spin":"FAIL slot gear rotation");
    }
    if(t==38)reviewCapture("07-gears-turning");
    if(t==58)reviewCapture("08-gears-slowing");
    if(t==130)reviewTrace(std::abs(gearAngle-gearStartAngle-450.f)<.01f?"PASS slot gears decelerate and stop with reels":"FAIL slot gear stop");
    if(t==180||t==340||t==500) {
        reviewTrace(run.tray.empty()&&!run.board.empty()&&!spinFlying()?"PASS spin results automatically fly into inventory":"FAIL automatic spin landing");
        bool separate=run.board.size()==(size_t)(6+3*((t-180)/160));
        for(const auto& b:run.board)separate=separate&&b.level==1;
        reviewTrace(separate?"PASS all three reel symbols land separately without automatic merge":"FAIL reel symbols merged automatically");
    }
    if(t==150){
        const auto before=run.encode();const auto hearts=robin.heart;
        reviewTap(l.spin);reviewTap(l.attack);reviewTap(l.exit);
        reviewTrace(spinFlying()&&run.encode()==before&&robin.heart==hearts?"PASS landing locks input without extra heart cost":"FAIL landing input lock");
        reviewCapture("09-spin-flight");
    }
    if(t==670) {
        Run restored;
        reviewTrace(restored.decode(run.encode())&&restored.encode()==run.encode()?"PASS run roundtrip":"FAIL run roundtrip");
        reviewLayout(l,"02-inventory");reviewCapture("02-inventory");
    }
    if(t==665&&!run.board.empty()) {
        Block moving=run.board[0];bool checked=false;
        for(int y=run.shape.height-Tall(moving);y>=0&&!checked;--y)for(int x=run.shape.width-Wide(moving);x>=0&&!checked;--x) {
            if(x==moving.x&&y==moving.y)continue;
            Block target=moving;target.x=x;target.y=y;if(!run.fits(target,0))continue;
            //떨어뜨린 자리 주변에 합쳐질 블록이 있으면 drop 은 옮기지 않고 합친다
            //(겹침 .2 칸이면 그쪽을 겨눈 것으로 본다). 장비가 여섯 부위에서 나오니
            //같은 부위 ★1 이 이웃에 서 있는 일이 흔하다 - 그런 자리는 건너뛴다.
            bool nearMerge=false;
            for(int k=1;k<(int)run.board.size()&&!nearMerge;++k) {
                const Block& o=run.board[k];
                if(!run.mergeable(o,moving))continue;
                nearMerge=o.x<x+Wide(target)+1&&o.x+Wide(o)>x-1&&o.y<y+Tall(target)+1&&o.y+Tall(o)>y-1;
            }
            if(nearMerge)continue;
            Box a=blockBox(moving,l),b=blockBox(target,l);
            //drop 은 손가락 자리를 블록의 가운데로 본다(잡은 자리 보정 없음). 왼쪽 위
            //에서 .3 칸 들어간 자리를 쓰면 1×2 블록은 한 줄 위에 떨어진다 - 가운데를 집는다.
            float fx=a.x+a.w*.5f,fy=a.y-a.h*.5f,tx=b.x+b.w*.5f,ty=b.y-b.h*.5f;
            MergeRouletteTouch(0,999,fx,fy);MergeRouletteTouch(1,999,tx,ty);MergeRouletteTouch(2,999,tx,ty);
            reviewTrace(run.board[0].x==x&&run.board[0].y==y?"PASS free drag through input":"FAIL drag");checked=true;
        }
        std::string before=run.encode();Box b=blockBox(run.board[0],l);
        MergeRouletteTouch(0,999,b.x+l.cell*.3f,b.y-l.cellH*.3f);
        MergeRouletteTouch(1,999,0,0);MergeRouletteTouch(3,999,0,0);
        reviewTrace(picked<0&&finger<0&&run.encode()==before?"PASS cancelled drag preserves block":"FAIL cancelled drag");
    }
    if(t==690) {
        reviewAttackGear=gearAngle;
        reviewAttackBlocks=run.board;
        long long before=robin.heart;reviewTap(l.attack);
        reviewTrace(run.attacking&&robin.heart==before-1?"PASS attack costs one heart":"FAIL attack");
    }
    if(t==708){reviewCapture("03-launch");reviewTrace(gearAngle==reviewAttackGear?"PASS slot gears stay still during attack":"FAIL attack moved slot gears");}
    //공격 연출은 블록마다 수십 프레임(동료 탄 생성·비행, 히어로 모션)이라 열두
    //블록이면 1000 프레임을 넘는다. 고정된 프레임에 검사하면 아직 치는 중이다 -
    //공격이 끝난 첫 프레임을 잡아 그때부터 센다.
    static int afterAttack=-1;
    if(t>=1000&&afterAttack<0&&!run.attacking)afterAttack=t;
    const int a=afterAttack<0?-1000:t-afterAttack;
    if(a==0) {

        reviewCapture("04-exchange");
        //차례는 묻지 않는다(연출이 판의 순서를 바꿔도 "같은 블록이 같은 자리에" 면 보존이다).
        bool retained=run.board.size()==reviewAttackBlocks.size();
        for(int i=0;i<(int)run.board.size()&&retained;++i) {
            const Block& k=run.board[i];bool found=false;
            for(const Block& o:reviewAttackBlocks)if(o.family==k.family&&o.level==k.level&&o.x==k.x&&o.y==k.y){found=true;break;}
            retained=found;
        }
        reviewTrace(!run.attacking&&retained&&run.spins>=10?"PASS sequential actions preserve every board element":"FAIL retained inventory");
    }
    if(a==5) {run.stage=4;run.setShape(castleShape(run.stage));run.enemyHp=run.enemyMax=hpFor(run.stage,0);}
    if(a==6){reviewLayout(l,"10-castle5-nine-columns");reviewCapture("10-castle5-nine-columns");
        reviewTrace(l.cell==(int)(80*l.scale)&&l.cellH==l.cell&&l.board.w==6*l.cell?"PASS expanded castle grid retains fixed 80px cells":"FAIL expanded grid size");}
    if(a==10) {run.stage=9;run.setShape(castleShape(run.stage));run.enemyHp=run.enemyMax=hpFor(run.stage,0);}
    if(a>=12&&!reviewCapturePending&&!reviewFinalCapture) {
        reviewFinalCapture=true;reviewLayout(l,"05-castle10");reviewCapture("05-castle10");
    } else if(a>=13&&reviewFinalCapture&&!reviewCapturePending&&reviewCaptureQueue.empty()) {
        Run current=run;
        run=Run();run.roster=&roster;run.choosing=false;run.families[0]=Sword;run.families[1]=Armor;run.families[2]=Boots;
        run.setShape(castleShape(0));
        //갑옷은 ★ 이 올라도 1×1 이라 칸을 셀 때 쓰기 좋다(무기 ★1 은 1×2 다).
        for(int i=0;i<22;++i) {Block b;b.family=Armor;b.x=i%run.shape.width;b.y=i/run.shape.width;run.board.push_back(b);}
        Layout full=layout();long long balance=robin.heart;auto blocked=run.encode();reviewTap(full.spin);
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
        //---- 커지는 합성은 자리를 본다 ----
        //
        //로빈의 몽둥이 사다리는 ★1 1×2 → ★2 1×2 → ★3 1×3 이다(칸 모양은 그림이
        //정한다). ★2 둘을 합치면 1×3 이 되는데, 둘이 비킨 2×2 에는 세로 셋이 안
        //들어간다 - 판이 꽉 차 있으면 합성이 기다린다. 한 칸을 비워 세로 셋이
        //이어지면 그제야 합쳐진다.
        run.board.erase(run.board.begin()+run.at(0,1));run.board.erase(run.board.begin()+run.at(1,1));
        run.board.erase(run.board.begin()+run.at(0,0));run.board.erase(run.board.begin()+run.at(1,0));
        {Block c;c.family=Sword;c.level=2;c.x=0;c.y=0;run.board.insert(run.board.begin(),c);
         c.x=1;run.board.insert(run.board.begin()+1,c);}   // (0,0)-(0,1) ★2, (1,0)-(1,1) ★2, 나머지 갑옷 1×1
        const auto crowdedMerge=run.encode();
        Layout mergeLayout=layout();Box club=blockBox(run.board[0],mergeLayout),onto=blockBox(run.board[1],mergeLayout);
        const float ax=club.x+club.w*.5f,ay=club.y-club.h*.5f,bx=onto.x+onto.w+2,by=onto.y-onto.h*.5f;
        MergeRouletteTouch(0,999,ax,ay);MergeRouletteTouch(1,999,bx,by);MergeRouletteTouch(2,999,bx,by);
        reviewTrace(run.freeCells()==0&&run.encode()==crowdedMerge&&messageTime>0&&robin.heart==balance?
            "PASS expanded merge waits for space without changing either piece":"FAIL blocked expanded merge");
        run.board.erase(run.board.begin()+run.at(0,2));   // 0 열 세로 셋이 빈다
        MergeRouletteTouch(0,999,ax,ay);MergeRouletteTouch(1,999,bx,by);MergeRouletteTouch(2,999,bx,by);
        const int merged=run.at(0,0);
        reviewTrace(merged>=0&&run.board.size()==20&&run.board[merged].level==3&&run.freeCells()==2&&
            blockBox(run.board[merged],mergeLayout).h==3*mergeLayout.cellH&&run.at(0,2)==merged&&robin.heart==balance?
            "PASS dragging clubs merges into expanded equipment footprint without heart cost":"FAIL expanded club drag merge");
        run.board=fullBoard;
        //★3 몽둥이는 1×3 이다. 세로 두 칸만 비면 못 앉고, 셋이 이어지면 앉는다.
        run.board.erase(run.board.begin()+run.at(5,3));
        run.board.erase(run.board.begin()+run.at(5,2));
        Block large;large.family=Sword;large.level=3;run.tray.push_back(large);
        const auto blockedHand=run.encode();
        const bool heldResult=!beginSpinLanding()&&run.encode()==blockedHand;
        Layout tight=layout();const int index=run.at(5,1);Box remove=blockBox(run.board[index],tight);
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

int MergeCrewOwnerHero(int crew) {return MergeTrees::OwnerHero(crew);}
bool MergeCrewAvailable(int crew) {const int h=MergeTrees::OwnerHero(crew);return h<0||IsGetHero(h);}
bool MergeRouletteActive() {return active;}
void MergeRouletteBeginSiege() {Siege::begin();}
static bool DrawOriginalCastlePreview(int castle,int x,int top,int width,int height){
    const float z=std::min(width/OriginalCastle::W,height/OriginalCastle::H);
    const int saved=siegeHullStage;siegeHullStage=castle;
    OriginalCastle::previewScale=z;OriginalCastle::previewLeft=x+(width-OriginalCastle::W*z)*.5f;
    OriginalCastle::previewLift=top-height;
    MistCastle::hull(castle,false,0,false);
    const auto& gun=MountedCannons::Get(castle,CastleVisualPartLevel(castle,3));
    const Box b=OriginalCastle::box(300,210,230,145);
    const float fit=std::min(b.w/(float)gun.w,b.h/(float)gun.h);
    const int img=CANNON_UPGRADE_ATLAS_IMG;if(!sprite[img])LoadImg(img);
    if(sprite[img])DrawImageScale(gun.w,gun.h,gun.x,gun.y,b.x,b.y,false,0,0,0,0,fit,fit,sprite[img],img);
    OriginalCastle::previewScale=0;siegeHullStage=saved;
    return true;
}
bool MergeRouletteOriginalPreview(int castle,int x,int top,int width,int height){
    if(castle<0||castle>=10)return false;
    if(width<=0||height<=0||x+width<=clipX||x>=clipX2||top<=clipY2||top-height>=clipY)return true;
    // Review-only comparison uses the exact previous drawing path.
    if(std::getenv("CS_CASTLE_PREVIEW_UNCACHED"))return DrawOriginalCastlePreview(castle,x,top,width,height);
    struct PreviewCache {
        int width=0,height=0,levels=-1,castle=-1;
        cocos2d::RenderTexture* target=nullptr;
    };
    // The menu has a large preview and two thumbnail sizes. Bound retained GPU
    // storage even if the window is resized repeatedly.
    static PreviewCache cache[12];static int next=0;
    PreviewCache* entry=nullptr;
    for(auto& candidate:cache)if(candidate.width==width&&candidate.height==height&&candidate.castle==castle){entry=&candidate;break;}
    if(!entry){
        entry=&cache[next++%12];
        if(entry->target)entry->target->release();
        *entry=PreviewCache();entry->width=width;entry->height=height;entry->castle=castle;
        entry->target=cocos2d::RenderTexture::create(width,height);
        if(!entry->target){entry->width=entry->height=0;return DrawOriginalCastlePreview(castle,x,top,width,height);}
        entry->target->retain();
        entry->target->getSprite()->getTexture()->setAliasTexParameters();
    }
    int levels=castle;for(int room=0;room<4;++room)levels=levels*6+std::min(5,castleRoomLevel(castle,room));levels=levels*6+CastleVisualPartLevel(castle,3);
    if(entry->levels!=levels){
        const int cx=clipX,cy=clipY,cx2=clipX2,cy2=clipY2,alpha=m_lgrpAlpha;
        PushRenderTarget(entry->target,nullptr,true);
        SetSectionClip(0,height,width,height,true);SetAlpha(ALPHA_MAX);
        DrawOriginalCastlePreview(castle,0,height,width,height);
        PopRenderTarget();clipX=cx;clipY=cy;clipX2=cx2;clipY2=cy2;SetAlpha(alpha);
        entry->levels=levels;
    }
    // Cached sprites still respect the scrolling body's clip, including partial
    // visibility. RenderTexture's texture is upside down relative to source art.
    const int left=std::max(x,clipX),right=std::min(x+width,clipX2);
    const int upper=std::min(top,clipY),lower=std::max(top-height,clipY2);
    // Each visit needs a distinct command: the same 64px preview occurs twice
    // in the part tab. Sharing a Sprite would overwrite its queued draw.
    static std::vector<cocos2d::Sprite*> images;static int imageFrame=-1,imageSlot=0;
    if(imageFrame!=frame){imageFrame=frame;imageSlot=0;}
    if(imageSlot>=(int)images.size()){
        auto* image=cocos2d::Sprite::createWithTexture(entry->target->getSprite()->getTexture());image->retain();images.push_back(image);
    }
    auto* image=images[imageSlot++];image->setTexture(entry->target->getSprite()->getTexture());image->setFlippedY(true);
    image->setTextureRect(cocos2d::Rect(left-x,lower-(top-height),right-left,upper-lower));
    image->setAnchorPoint({0,1});image->setPosition({(float)left,(float)upper});
    image->setOpacity((int)(m_lgrpAlpha*255/32));image->visit();
    return true;
}
void MergeRouletteSetHeartCapacity(int capacity) {(void)capacity;heartCapacity=10;heartDisplay=(int)std::min((long long)heartCapacity,robin.heart);}
void MergeRouletteBegin(bool resume) {
    if(active)return;
    siegeActive=false;siegeHullStage=-1;waveTransition=MergeCombat::WaveTransition();
    review=std::getenv("CS_MERGE_REVIEW")!=nullptr;
    oldMode=option.gameMode;option.gameMode=TURNRPG;
    configure();
    //---- 전투에 들어가면 장비를 벗는다 ----
    //
    //전에는 로비에서 끼고 온 장비를 바탕으로 두고 판의 블록이 그 위에 덧입혀졌다.
    //그러면 판이 비어도 완전무장이라 "판을 채워서 입는다" 가 안 보였다. 바탕은
    //맨몸이고, 블록이 앉는 부위부터 하나씩 입는다. 수치(stats)는 끼고 온 장비
    //그대로다 - 벗는 것은 그림뿐이다.
    for(int g=0;g<GearCount;++g){std::memset(&baseCostume[g],0,sizeof(ITEM));baseCostume[g].type=EMPTY;costumeLevels[g]=0;}
    for(int g=0;g<GearCount;++g){hero.equip[costumeSlots[g]]=baseCostume[g];hero.equipImg[costumeSlots[g]]=0;}
    costumeEffectTicks=0;attackWeaponLevel=0;weaponSwap=MergeCombat::WeaponSwap();damagePause=MergeCombat::DamagePause();
    //디버그로 성을 바꿔 두었으면 그 성으로 들어간다(칸 수·적 체력·대포 단계 전부).
    const int debugCastle=LobbyCastleDebugCastle();
    run=Run();run.roster=&roster;run.rng=(unsigned)MC_knlCurrentTimeStamp()|1;
    run.selected=pool.front();run.stage=std::max(0,std::min(9,debugCastle>=0?debugCastle:(int)robin.castle));
    run.enemyHp=run.enemyMax=waveHp(run.stage,0);

    if(resume) {
        Run restored;restored.roster=&roster;
        // v6 전 세이브는 읽지 않는다(계열·동료 체계가 다르다) — 새 런.
        if(robin.mergeRouletteHero==curHero&&restored.decode(robin.mergeRouletteRun)) {
            bool owned=true;for(int f:restored.families)if(std::find(pool.begin(),pool.end(),f)==pool.end())owned=false;
            if(owned)run=restored;
        }
        //이어 하는 판의 시작 계열이 전부 장비면(옛 뽑기 - 장비 가중치 4) 릴에서 동료가 영영 안 나온다.
        //검은 두고 다른 장비 자리에 이 히어로의 역할을 채운다. 판 위 블록은 그대로다.
        {
            bool hasRole=false;for(int f:run.families)if(f<Roles)hasRole=true;
            if(!hasRole){
                std::vector<int> roles;for(int f:pool)if(f<Roles)roles.push_back(f);
                for(int i=0;i<3&&!roles.empty();++i)if(run.families[i]>=Roles&&run.families[i]!=Sword){run.families[i]=roles.front();roles.erase(roles.begin());}
            }
        }
        if(debugCastle>=0&&run.stage!=debugCastle){run.stage=debugCastle;run.wave=0;run.enemyHp=run.enemyMax=waveHp(run.stage,0);}
    } else if(review) {robin.heart=20;run.rng=12345;}
    const bool migrateVitals=!run.realVitals;
    run.setVitals(stats.heroHealth,stats.heroArmor);
    run.enemyAttack=waveAttack(run.stage,run.wave);
    if(migrateVitals&&run.attacking){const Effects f=run.forecast(stats);run.effects.protect=f.protect;run.effects.charge=f.charge;run.settleGuard();}
    run.setShape(castleShape(run.stage));
    bool starting=run.choosing&&run.start(pool,treeWeights,review&&std::getenv("CS_MERGE_ARRIVAL_REVIEW"));
    entryElapsed=0.f;entryCaptures=0;panicSeed=run.rng;
    introElapsed=starting?0.f:-1.f;introCaptures=0;reviewCombatTick=-1;
    if(!starting)updateHeroCostume(false);
    reviewCapturePending=reviewFinalCapture=false;
    simulationRemainder=0;gradeAccents.clear();shownGrades.clear();
    deckMerge=DeckMergePresentation();deckMergeSeen=run.mergeSeq;
    std::fill(deckCrewPositionKnown,deckCrewPositionKnown+64,false);
    enemyPatternNpc=enemyPatternStage=enemyPatternWave=-1;enemyPatternTurn=0;
    ticks=animation=0;action=CombatAction();enemyTurn=EnemyTurn();allyFlash=0;guardDisplay=MergeCombat::AnimatedValue();
    attackDisplayKnown=false;attackGain=0;attackGainTime=0;
    heroHealthDisplay=MergeCombat::AnimatedValue();heroHealthDisplay.set(run.lives);heroHealthDisplay.advance(1);
    enemyHealthDisplay=MergeCombat::AnimatedValue();enemyHealthDisplay.set(run.enemyHp);enemyHealthDisplay.advance(1);
    combatNumbers.clear();gearAngle=gearStartAngle=0;picked=finger=-1;message="";
    spinFlightFrame=-1;spinDrops.clear();
    for(auto& reveal:deckReveal)reveal=MergeCombat::ResidentReveal();
    if(!starting)for(const auto& block:run.board)
        if(block.family<Roles&&block.crew>=0&&block.crew<64)deckReveal[block.crew].age=MergeCombat::ResidentReveal::Duration;
    rememberReelSymbols();
    if(resume&&!starting&&!run.tray.empty())beginSpinLanding();
    observedHearts=robin.heart;heartDisplay=(int)std::min((long long)heartCapacity,robin.heart);heartBlink=messageTime=0;spentHeart=-1;
    active=true;drawHandle=MD_PLAY;keyHandle=MK_PLAY;curMenu=MENU_PLAY;
    autoPlay=false;autoFrame=-1;touchDisable=false;mustRefresh=true;
    if(!run.choosing)save();
}
void MergeRouletteBottomNavDraw(){drawLobbyBottomNav();} // Active section follows the shared dock and its native artwork.
int MergeRouletteBottomNavHeight(){return lobbyBottomNav().y;}
bool MergeRouletteLobbySceneDraw() {
    static bool needsConfigure=true;
    if(popUpCnt>0||LoadoutOpen()){needsConfigure=true;return false;}
    static int preparedHero=-1,preparedCastle=-1;
    if(needsConfigure||preparedHero!=curHero||preparedCastle!=robin.castle){configure();preparedHero=curHero;preparedCastle=robin.castle;needsConfigure=false;}
    const int previewCastle=LobbyCastleDebugCastle();
    run.stage=std::max(0,std::min(9,previewCastle>=0?previewCastle:(int)robin.castle));
    run.setShape(castleShape(run.stage));
    static float idleRemainder=0;
    if(!(review&&reviewCapturePending)){
        idleRemainder+=std::min(.1f,std::max(0.f,cocos2d::Director::getInstance()->getDeltaTime()));
        const int elapsed=(int)((idleRemainder+.000001f)*60.f);
        ticks+=elapsed;idleRemainder-=elapsed/60.f;
    }
    ResetRectPoint();SetAlpha(32);SetColor(0);grayScale=0;
    Layout l=layout();drawWorld(l,false);drawLobbyControls(l,0,true);
    mustRefresh=true;++frame;return true;
}
void MergeRouletteLobbyDraw() {}
void MergeRouletteDraw() {
    MergeRenderProfile::Frame profile;
    if(review&&std::getenv("CS_MERGE_LOBBY_IDLE_REVIEW")){
            static int samples=0,firstTick=0;static std::vector<int> poses;static bool second=false,done=false;
        if(samples==0){run.board.clear();firstTick=ticks;}
        MergeRouletteLobbySceneDraw();
        if(reviewCapturePending||done)return;
        const int pose=heroNeutralMotion(hero);
        if(std::find(poses.begin(),poses.end(),pose)==poses.end())poses.push_back(pose);
        if(samples++==0)reviewCapture("lobby-idle-01");
        else if(!second&&poses.size()>1){second=true;reviewCapture("lobby-idle-02");}
        if(samples>=90){
            reviewTrace(poses.size()>1&&ticks>firstTick+30?"PASS actual lobby path advances native hero neutral motion":"FAIL frozen lobby hero motion");
            const float s=DX/640.f,lift=castleSceneLift();
            const Box nav=OriginalCastle::box(76,1275,941,163,OriginalCastle::lift());
            const bool centered=std::abs(DY-DX*2.2f)>1.f||std::abs(lift-(MergeCombat::lobbyCastleLift((float)DX,(float)DY)-25.f*s))<1.f;
            reviewTrace(centered&&nav.y==(int)((OriginalCastle::H-1275)*OriginalCastle::zoom())?
                "PASS responsive castle and rail lift with fixed bottom navigation":"FAIL responsive lobby layout");
            char metrics[160];std::snprintf(metrics,sizeof(metrics),"layout height=%d lift=%.2f rail=%.2f navTop=%d",DY,lift,104*s+lift,nav.y);reviewTrace(metrics);
            const Box start=lobbyStart(layout());
            active=false;drawHandle=MD_LOBBY;
            MergeRouletteTouch(0,999,start.x+start.w*.5f,start.y-start.h*.5f);
            reviewTrace(active&&entering()?"PASS lifted start button matches actual lobby touch coordinates":"FAIL lifted start button hit area");
            reviewTrace("DONE lobby idle review");done=true;
        }
        return;
    }
    std::fill(reelResultDrawn,reelResultDrawn+3,false);
    // Isolated capture reviews hold simulation until asynchronous PNG writing
    // completes. Fixed-tick checks cannot be skipped or captured in a later state.
    const bool holdReview=review&&reviewCapturePending;
    const float frameDt=std::min(.1f,std::max(0.f,cocos2d::Director::getInstance()->getDeltaTime()));
    int steps=0;
    if(!holdReview){
        observeDeckMerge();
        simulationRemainder+=frameDt;
        steps=review?1:(int)((simulationRemainder+.000001f)*60.f);
        if(review)simulationRemainder=0;else simulationRemainder-=steps/60.f;
        deckMerge.time.advance(steps);
        for(int i=0;i<steps;++i){tick(1.f/60.f);updateGuardDisplay(1.f/60.f);}
        // Newly landed residents must remain hidden for one rendered frame.
        if(steps>0)updateDeckReveal(steps);
        for(auto& accent:gradeAccents)accent.age+=steps;
    }
    ResetRectPoint();mustRefresh=true;profile.stamp(0);
    if(review&&std::getenv("CS_REEL_SHADOW_REVIEW")){
        static int page=0,hold=0;
        if(page>=6)return;
        cocos2d::Director::getInstance()->setDisplayStats(false);
        SetAlpha(32);SetColor(0);grayScale=0;
        MemRect(0,DY,DX,DY,0x243436);
        bool valid=true;
        if(page<3){
            const float scale=page==0?.5f:page==1?1.f:2.f;
            label("Shadow clipping / small, native, enlarged",DX/2,DY-20,.6f,0xE9D7B5);
            for(int edge=0;edge<9;++edge){
                const int x=25+(edge%3)*205,y=DY-70-(edge/3)*220;
                const int width=150,height=130,sw=24*_2X,sh=16*_2X;
                MemRect(x,y,width,height,0xE0CFB1);
                SetSectionClip(x,y,width,height,false);
                const int dx=(int)(edge%3==0?x-sw*scale/2:edge%3==1?x+width/2-sw*scale/2:x+width-sw*scale/2);
                const int dy=(int)(edge/3==0?y+sh*scale/2:edge/3==1?y-height/2+sh*scale/2:y-height+sh*scale/2);
                ShadowImage(sw,sh,_2X,_2X,dx,dy,SHADOW_IMG,scale);
                const auto rect=renderSprite[getSpriteIdx]->getTextureRect();
                const auto bounds=renderSprite[getSpriteIdx]->getBoundingBox();
                valid=valid&&getSpriteTexture==SHADOW_IMG&&rect.origin.x>=_2X-.01f&&rect.origin.y>=_2X-.01f&&
                    rect.getMaxX()<=_2X+sw+.01f&&rect.getMaxY()<=_2X+sh+.01f&&
                    bounds.getMinX()>=x-.01f&&bounds.getMaxX()<=x+width+.01f&&
                    bounds.getMinY()>=y-height-.01f&&bounds.getMaxY()<=y+.01f;
                const int before=curRenderCnt;
                ShadowImage(sw,sh,_2X,_2X,x,y+height,SHADOW_IMG,scale);
                ShadowImage(sw,sh,_2X,_2X,x,y,SHADOW_IMG,0);
                valid=valid&&before==curRenderCnt;
                UnSectionClip(false);
            }
        }else{
            const Layout l=layout();drawWorld(l,false);drawSlotFrame(l.slot);
            for(int i=0;i<3;++i){
                const Box window=slotWindow(l.slot,i);
                SetSectionClip(window.x,window.y,window.w,window.h,false);
                for(int j=-1;j<=1;++j){
                    Box symbol=window;symbol.y+=j*window.h+(page-4)*window.h*2/3;
                    icon(i%Roles,symbol,1.f,true);
                }
                UnSectionClip(false);
            }
            slotRim(l.slot);
        }
        if(!holdReview&&++hold>8){
            reviewTrace(valid?"PASS scaled shadow source bounds, clip edges and offscreen rejection":"FAIL shadow clipping");
            char name[32];std::snprintf(name,sizeof(name),"reel-shadow-%02d",page+1);reviewCapture(name);
            hold=0;if(++page==6)reviewTrace("DONE reel shadow review");
        }
        return;
    }
    if(review&&std::getenv("CS_SQUARE_GEAR_REVIEW")){
        static int page=0,hold=0;
        if(page>=8)return;
        cocos2d::Director::getInstance()->setDisplayStats(false);
        SetAlpha(32);SetColor(0);grayScale=0;MemRect(0,DY,DX,DY,0x243438);
        label("Grid / independently painted icon",DX/2,DY-18,.6f,0xE9D7B5);
        bool valid=true;
        for(int cell=0;cell<16;++cell){
            const int id=page*16+cell;if(id>=120)break;
            const int type=3+id/8,detail=id%8,x=8+(cell%4)*158,y=DY-56-(cell/4)*180;
            const int grid=GRID_ITEM_FIRST_IMG+GridItems::FromItem(type,detail);
            valid=DrawGridItemInBox(type,detail,x,y,68,68,32,false)&&valid;
            valid=valid&&getSpriteTexture==grid;
            const int icon=GetItemIcon(type,detail,GRADE_NORMAL),series=ItemSeries::FromIcon(icon);
            valid=valid&&series==SquareGear::Icons[id];
            DrawIcon(icon,x+78,y,2.125f,0,false,false,1.f);
            const int texture=ITEM_SERIES_FIRST_IMG+series;
            valid=valid&&getSpriteTexture==texture&&texture!=grid&&sprite[texture]!=sprite[grid];
            char text[48];std::snprintf(text,sizeof(text),"%d:%d / item%d",type,detail,series);
            label(text,x+74,y-94,.34f,0xE5D4BA);
        }
        if(!holdReview&&++hold>6){
            reviewTrace(valid?"PASS separate grid/icon textures and live item identity mapping":"FAIL square gear identity");
            char name[32];std::snprintf(name,sizeof(name),"square-gear-%02d",page+1);reviewCapture(name);
            hold=0;if(++page==8)reviewTrace("DONE square gear review");
        }
        return;
    }
    if(review&&std::getenv("CS_GRID_CREW_SCALE_REVIEW")){
        static int page=0,hold=0;
        if(page>=4)return;
        cocos2d::Director::getInstance()->setDisplayStats(false);
        const float s=DX/640.f;
        label("GRID COMPANIONS - FIXED ZOOM 1.50",DX/2,DY-(int)(20*s),.65f,0xFFE6AC);
        for(int slot=0;slot<16;++slot){
            const int crew=page*16+slot,col=slot%4,row=slot/4;
            Block b;b.family=MergeTrees::Role(crew);b.level=MergeTrees::Star(crew);b.crew=crew;
            const Box cell={(int)((col*160+40)*s),(int)(DY-(80+row*170)*s),(int)(80*s),(int)(160*s)};
            drawBlock(b,cell);
            char text[40];std::snprintf(text,sizeof(text),"%02d   zoom %.2f",crew,gridCrewZoomSeen[crew]);
            label(text,cell.x+cell.w/2,cell.y+(int)(18*s),.44f,0xFFFFFF);
        }
        if(!reviewCapturePending&&++hold>8){
            bool equal=true;for(int c=page*16;c<(page+1)*16;++c)equal=equal&&std::abs(gridCrewZoomSeen[c]-1.5f*s)<.00001f;
            reviewTrace(equal?"PASS sixteen grid companions use identical native zoom":"FAIL grid companion zoom varies");
            char name[40];std::snprintf(name,sizeof(name),"grid-crew-scale-%02d",page+1);reviewCapture(name);
            hold=0;if(++page==4)reviewTrace("DONE grid crew scale review");
        }
        return;
    }
    if(review&&std::getenv("CS_SHARED_SWORD_REVIEW")){
        static int page=0,hold=0;
        cocos2d::Director::getInstance()->setDisplayStats(false);
        if(page>=7)return;
        SetAlpha(32);SetColor(0);grayScale=0;
        MemRect(0,DY,DX,DY,0x263538);
        label("Inventory / held / held mirrored - same texture and canvas",DX/2,DY-20,.5f,0xFFFFFF);
        bool valid=true;
        for(int row=0;row<5;++row){
            const int detail=page*5+row,img=GRID_ITEM_FIRST_IMG+detail;
            const auto* info=GetSwordSpriteInfo(detail);
            const int w=GridItems::WeaponCellSize*GridItems::WeaponColumns(ITEM_SWORD,detail);
            const int h=GridItems::WeaponCellSize*GridItems::WeaponRows(ITEM_SWORD,detail);
            const int y=DY-70-row*145;
            valid=DrawGridItemInBox(ITEM_SWORD,detail,100,y,w,h,32,false)&&valid;
            valid=valid&&getSpriteTexture==img;
            const float gripX=info->pivotX/info->width,gripY=info->pivotY/info->height;
            DrawSwordAtHand(detail,280+w*gripX,y-h*gripY,0,false,1,32,0);
            valid=valid&&getSpriteTexture==img;
            DrawSwordAtHand(detail,440+w*(1-gripX),y-h*gripY,0,true,1,32,0);
            valid=valid&&getSpriteTexture==img;
            char text[24];std::snprintf(text,sizeof(text),"Sword %02d",detail+1);
            label(text,45,y-12,.4f,0xFFFFFF);
        }
        if(!holdReview&&++hold>8){
            reviewTrace(valid?"PASS inventory and held swords share grid textures":"FAIL separate sword texture");
            char name[40];std::snprintf(name,sizeof(name),"shared-sword-%02d",page+1);reviewCapture(name);
            hold=0;if(++page==7)reviewTrace("DONE shared sword review");
        }
        return;
    }
    if(review&&std::getenv("CS_GRID_ITEM_REVIEW")){
        static int page=0,hold=0;
        cocos2d::Director::getInstance()->setDisplayStats(false);
        if(page>=8)return;
        SetAlpha(32);SetColor(0);grayScale=0;
        MemRect(0,DY,DX,DY,0x263538);
        label("Grid equipment / upright and rotated",DX/2,DY-16,.6f,0xE9D7B5);
        bool valid=true;
        for(int cell=0;cell<32;++cell){
            const int id=page*32+cell;if(id>=GridItems::Count)break;
            const int type=GridItems::Type(id),detail=GridItems::Detail(id);
            ITEM item={};item.type=type;item.detail=detail;item.grade=GRADE_NORMAL;
            const int x=8+(cell%4)*158,y=DY-48-(cell/4)*96;
            int cw=1,ch=1;MergeBoardGearShape(&item,&cw,&ch);
            const float fit=std::min(64.f/cw,72.f/ch);
            MergeBoardDrawGear(&item,x,y,(int)(cw*fit),(int)(ch*fit),32,false);
            const int img=GRID_ITEM_FIRST_IMG+id;
            valid=valid&&sprite[img]&&getSpriteTexture==img;
            valid=DrawGridItemInBox(type,detail,x+70,y-12,78,45,24,true)&&valid;
            valid=valid&&getSpriteTexture==img;
            char text[40];std::snprintf(text,sizeof(text),"grid%d / %d:%d",id,type,detail);
            label(text,x+74,y-80,.34f,0xE5D4BA);
        }
        if(!holdReview&&++hold>8){
            char msg[100];std::snprintf(msg,sizeof(msg),"%s grid artwork page %d: actual board routes and rotation",valid?"PASS":"FAIL",page+1);reviewTrace(msg);
            char name[32];std::snprintf(name,sizeof(name),"grid-%02d",page+1);reviewCapture(name);
            hold=0;if(++page==8)reviewTrace("DONE grid item review");
        }
        return;
    }
    if(review&&std::getenv("CS_ITEM_SERIES_REVIEW")){
        static int page=0,hold=0;static bool checked=false;
        cocos2d::Director::getInstance()->setDisplayStats(false);
        if(page>=10)return;
        SetAlpha(32);SetColor(0);grayScale=0;
        MemRect(0,DY,DX,DY,0x18272B);
        char title[80];std::snprintf(title,sizeof(title),"256px item series / page %d",page+1);
        label(title,DX/2,DY-16,.65f,0xE9D7B5);
        bool valid=true;int count=0;
        for(int cell=0;cell<64;++cell){
            const int id=page*64+cell;if(id>=ItemSeries::Count)break;
            if(!ItemSeries::Artwork[id].active)continue;
            const int icon=id<512?id:id<584?0x8000+id-512:0x8100+id-584;
            const int x=8+(cell%8)*78,y=DY-50-(cell/8)*94;
            DrawIcon(icon,x,y,2.f,0,false,false,1.f);
            const int img=ITEM_SERIES_FIRST_IMG+id;
            valid=valid&&sprite[img]&&getSpriteTexture==img;
            if(sprite[img]){const auto sz=sprite[img]->getTexture()->getContentSizeInPixels();valid=valid&&sz.width==256&&sz.height==256;}
            if(cell%8==0){
                DrawItemSeriesInBox(icon,x+54,y-40,22,22,16,true);
                const int color=baseColor;
                DrawIcon(icon,x+56,y,0.5f,0xD7B878,true,false,1.f);
                valid=valid&&baseColor==color;
            }
            char name[24];std::snprintf(name,sizeof(name),"item%d",id);
            label(name,x+32,y-69,.38f,0xE5D4BA);++count;
        }
        if(!holdReview&&++hold>8){
            if(!checked){char msg[100];std::snprintf(msg,sizeof(msg),"%s item series page %d / %d textures, dimensions and render routes",valid?"PASS":"FAIL",page+1,count);reviewTrace(msg);checked=true;}
            char name[32];std::snprintf(name,sizeof(name),"items-%02d",page+1);reviewCapture(name);
            hold=0;checked=false;if(++page==10)reviewTrace("DONE item series review");
        }
        return;
    }

    if(review&&std::getenv("CS_MIST_RESOURCE_REVIEW")){
        if(mistReviewSample>=35)return;
        cocos2d::Director::getInstance()->setDisplayStats(false);
        castleScrollSeconds=mistReviewSample*23.5f; // Inspect different repeat boundaries in live captures.
        run.stage=mistReviewSample<20?mistReviewSample/2:(mistReviewSample-20)%10;run.setShape(castleShape(run.stage));
        run.attacking=false;run.choosing=false;introElapsed=-1;entryElapsed=-1;animation=0;
        const Layout fixedGrid=layout();
        if(fixedGrid.cell!=(int)(80*fixedGrid.scale)||fixedGrid.cellH!=fixedGrid.cell||run.shape.width>8||
           (run.stage==9&&(run.shape.height!=5||run.shape.rows[0]!=0x18))){reviewTrace("FAIL fixed 80-unit grid or top-pair shape");return;}
        if(mistReviewSample<20&&mistReviewSample%2==0){const Layout test=layout();drawWorld(test,false);drawLobbyControls(test);if(!holdReview)reviewStep(test);return;}
    }
    if(review&&std::getenv("CS_PIXEL_CASTLE_REVIEW")){
        static int sample=0,hold=0;
        cocos2d::Director::getInstance()->setDisplayStats(false);
        run.stage=0;run.setShape(castleShape(0));entryElapsed=-1;
        Layout l=layout();drawWorld(l,false);drawLobbyControls(l);
        if(!reviewCapturePending&&++hold>8&&sample==0){reviewCapture("pixel-castle-lobby");++sample;reviewTrace("DONE pixel castle review");}
        return;
    }
    if(review&&std::getenv("CS_MERGE_ORIGINAL_REVIEW")){
        static int sample=0,hold=0;run.stage=0;run.setShape(castleShape(0));
        if(sample==0)OriginalCastle::draw(9);
        else{Layout l=layout();drawWorld(l,false);drawLobbyControls(l);}
        if(!reviewCapturePending&&++hold>5&&sample<2){reviewCapture(sample==0?"original-uniform-reference":"original-live-lobby");++sample;hold=0;if(sample==2){
            bool uniform=true;for(int c=1;c<10;++c){run.stage=c;run.setShape(castleShape(c));Layout test=layout();const auto m=castleMap(test,c);
                const float z=(m.dx[3]-m.dx[0])/(m.sx[3]-m.sx[0]);for(int i=0;i<3;++i)uniform=uniform&&std::abs((m.dy[i+1]-m.dy[i])/(m.sy[i]-m.sy[i+1])-z)<.00001f;
                uniform=uniform&&test.cell==(int)(80*test.scale)&&test.cellH==test.cell;}
            run.stage=0;run.setShape(castleShape(0));reviewTrace(uniform?"PASS all ten castles preserve uniform art scale and fixed 80px cells":"FAIL castle aspect ratio");reviewTrace("DONE original reference review");}}
        return;
    }
    if(review&&std::getenv("CS_FACILITY_ROOMS_REVIEW")){
        static int sample=0,hold=0;
        static bool walkersReady=false;
        if(!walkersReady&&std::getenv("CS_FOUR_ROOM_WALKERS_REVIEW")){
            Roster shown;for(int c=0;c<12;++c)shown.add(MergeTrees::Role(c),MergeTrees::Star(c),c);
            roster=shown;walkersReady=true;
        }
        if(sample>=70)return;
        const int c=sample<60?sample/6:sample-60,level=sample<60?sample%6:0;
        const auto saved=robin.castleProgress;const int previousStage=run.stage;
        run.stage=c;run.setShape(castleShape(c));
        for(int i=0;i<4;++i)robin.castleProgress.rooms[c][i]=(unsigned char)(sample<60?level:i);
        robin.castleProgress.parts[c][3]=(unsigned char)(sample<60?level:5);
        const Layout test=layout();drawWorld(test,false);drawLobbyControls(test);
        bool valid=true;
        for(int i=0;i<4;++i){
            valid=valid&&MistCastle::facilityLevels[i]==(sample<60?level:i)&&MistCastle::facilityImages[i]==MERGE_REBUILD_ROOMS_IMG+c;
            const auto p=OriginalCastle::rooms()[i];
            const int x=(int)p[0].x,y=(int)p[0].y,w=(int)(p[1].x-p[0].x),h=(int)(p[2].y-p[0].y);
            const Box b=OriginalCastle::box(x,y,w,h),right=OriginalCastle::box(x+w,y,10,h),lower=OriginalCastle::box(x,y+h,w,10);
            valid=valid&&b.x+b.w==right.x&&b.y-b.h==lower.y;
        }
        robin.castleProgress=saved;run.stage=previousStage;
        if(!reviewCapturePending&&++hold>5){
            reviewTrace(valid?"PASS four themed rooms use independent saved levels and joined edges":"FAIL facility artwork or registration");
            char name[48];std::snprintf(name,sizeof(name),"facility-c%02d-%s%d",c+1,sample<60?"level-":"independent-",level);reviewCapture(name);
            hold=0;if(++sample==70)reviewTrace("DONE facility rooms review");
        }
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
    Layout l=layout();float s=l.scale;
    const Layout fixed=layout();
    updateHeroCostume();
    drawWorld(fixed,true);profile.stamp(1);
    if(entering()){
        drawLobbyControls(fixed,MergeCastleTransition::LobbyExit(entryElapsed));
        const int controlDrop=(int)((1-MergeCastleTransition::ControlsEnter(entryElapsed))*300*s);
        l.slot.y-=controlDrop;l.lever.y-=controlDrop;l.heart.y-=controlDrop;
        l.spin.y-=controlDrop;l.attack.y-=controlDrop;
    }
    const int hx=(int)(DX*.57f),ex=(int)(DX*.85f),ey=l.ground;
    if(siegeActive)Siege::drawHeader(l);else drawWaveHeader(l);
    if(run.attacking) {
        const char* phase=action.index>=0&&run.shots[action.index].block.family<0?(turretFire.type==TurretAttack::Magnetic?(action.time.elapsed<action.time.release?u8"\uc911\uc790\uae30\ud30c \u00b7 \ucda9\uc804":u8"\uc911\uc790\uae30\ud30c \u00b7 \ubc1c\uc0ac"):turretFire.type==TurretAttack::Laser?(action.time.elapsed<action.time.release?u8"\ub808\uc774\uc800 \u00b7 \ucda9\uc804":u8"\ub808\uc774\uc800 \u00b7 \ubc1c\uc0ac"):turretFire.type==TurretAttack::Missiles?u8"\uc720\ub3c4\ubbf8\uc0ac\uc77c \u00b7 \ubc1c\uc0ac":turretFire.type==TurretAttack::Stone?u8"\ud22c\uc11d \u00b7 \ubc1c\uc0ac":u8"\ud3ec\uaca9"):enemyTurn.endShown?"턴 종료":enemyTurn.started?"적 반격":run.passing?"턴 넘김 · 적의 차례":
            action.index>=0&&action.bulletIcon>=0?(action.time.elapsed<action.time.release?"동료 · 총탄 생성":"동료 · 총탄 발사"):
            action.index>=0&&action.skill>=0&&!action.heroMotion.empty()?"동료 · 히어로 스킬 요청":"아군 공격";
        const Box actionLabel={DX/2-(int)(82*s),l.ground-(int)(3*s),(int)(164*s),(int)(25*s)};
        panel(actionLabel,0x182735,0xB99850);
        label(phase,DX/2,actionLabel.y-(int)(5*s),.53f,0xFFE2A2);
    }
    if(waveTransition.active()){
        const char* text=waveTransition.defeatedVisible()?u8"\ucc98\uce58!":waveTransition.travelling()?u8"\ub2e4\uc74c \uc801\uc744 \ud5a5\ud574 \uc774\ub3d9 \uc911":combatEnemyIsBoss()?u8"\ubcf4\uc2a4 \ub4f1\uc7a5":u8"\ubaac\uc2a4\ud130 \ub4f1\uc7a5";
        label(text,DX/2,l.ground+(int)(105*s),.65f,0xFFE2A2);
    }
    // Readable unit plates directly beneath the battle, separate from the board title.
    //---- 패의 자리 ----
    //
    //히어로 발밑에 붙어 다니면 사람과 숫자가 서로를 가린다. 화면을 성
    //가운데로 반 가른 뒤, 왼쪽 절반의 절반을 아군이, 오른쪽 절반의
    //절반을 적이 쓴다 - 둘이 같은 폭으로 마주 본다.
    const int plateW=DX/4,plateH=l.plateH;   //방어 · 체력 · 공격 세 단. 높이·자리는 layout 이 정한다
    Box allyPlate={DX/4-plateW/2,l.ground-l.plateDrop,plateW,plateH};
    Box enemyPlate={DX*3/4-plateW/2,l.ground-l.plateDrop,plateW,plateH};
    //방어는 갑옷 블록이 주는 보호 횟수다. 공격 중이면 남은 몫을, 배치
    //중이면 "지금 공격하면 받을" 몫을 보여 준다.
    const long long guard=currentGuard();
    if(siegeActive&&Siege::swapped)std::swap(allyPlate,enemyPlate);   //맞바꾼 동안 패도 자리를 바꾼다
    const long long attackPower=attackDisplayKnown?(long long)std::llround(attackDisplay.value):std::max(0LL,hero.ps[PS_DMG]);
    //적의 공격: 일반 웨이브는 반격값(보스는 두 배), 공성전은 상대 판이 지금 때릴 예상치.
    const long long enemyAttack=siegeActive?Siege::foe.preview(Siege::foeStats):MonsterBoard::counterPreview();
    //아군 방어 줄: 방어막 통의 현재값 / 최대치(판 위 방어구 + 실제 장착분).
    unitPlate(allyPlate,run.lives,run.maxLives,guard,0x37433B,0x406D39,allyFlash>0,guardDisplay.value,std::max(1LL,currentGuardMax()),heroHealthDisplay.value,
        std::max(0LL,hero.ps[PS_DMG]),(double)attackPower,attackGainTime>0);
    if(!waveTransition.active()||waveTransition.incomingVisible())unitPlate(enemyPlate,run.enemyHp,run.enemyMax,run.enemyGuard,0x493444,0xAA343E,flash!=0,-1,std::max(1LL,run.enemyGuardMax),enemyHealthDisplay.value,
        std::max(0LL,enemyAttack),-1,false);
    if(attackGainTime>0&&attackGain>0){
        const float rise=(1.5f-attackGainTime)*18*s;
        SetColor(0xFFE18A);imageNumber(attackGain,allyPlate.x+allyPlate.w/2,allyPlate.y+(int)(20*s+rise),.85f*s,true);SetColor(0);
    }
    button(l.exit,"나가기",nullptr,0x25304A,!run.attacking);
    if(siegeActive)Siege::drawHud(l);else MonsterBoard::drawPanel(l);
    profile.stamp(2);
    // No backing board: individual fixed 80px tiles cover the rooms themselves.
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
    //겹친 블록은 붉은 테로 알린다 - 이걸 풀어야 단추가 돌아온다.
    for(int i=0;i<(int)run.board.size();++i) {
        if((picked==i&&!pickedTray)||run.fits(run.board[i],i))continue;
        const Box box=blockBox(run.board[i],l);
        MemRectFrameThick(box.x,box.y,box.w,box.h,((ticks/8)&1)?0xFF5A4A:0xC82E24,std::max(1,(int)(3*s)));
    }
    const auto sameGrade=[](const Block& a,const Block& b){return a.family==b.family&&a.level==b.level&&a.crew==b.crew&&a.x==b.x&&a.y==b.y;};
    std::vector<Block> visibleGrades;
    auto unmatchedGrades=shownGrades;
    for(int i=0;i<(int)run.board.size();++i){
        const auto& b=run.board[i];
        if(b.level<4||!gridBlockLanded(i))continue;
        visibleGrades.push_back(b);
        const auto prior=std::find_if(unmatchedGrades.begin(),unmatchedGrades.end(),[&](const Block& old){return old.family==b.family&&old.level==b.level&&old.crew==b.crew;});
        if(prior==unmatchedGrades.end()){gradeAccents.push_back({b,0});PlayMusic(M_POWERUP);}
        else unmatchedGrades.erase(prior);
    }
    shownGrades=visibleGrades;
    gradeAccents.erase(std::remove_if(gradeAccents.begin(),gradeAccents.end(),[](const GradeAccent& a){return a.age>=36;}),gradeAccents.end());
    for(const auto& accent:gradeAccents){
        if(std::find_if(visibleGrades.begin(),visibleGrades.end(),[&](const Block& b){return sameGrade(b,accent.block);})==visibleGrades.end())continue;
        const Box box=blockBox(accent.block,l);
        const float t=accent.age/36.f,pulse=std::sin(std::min(1.f,t*2)*3.14159265f);
        const int grow=(int)(pulse*7*s);
        if(accent.age<18)drawBlock(accent.block,{box.x-grow,box.y+grow,box.w+grow*2,box.h+grow*2});
        SetAlpha((int)(32*(1-t)));
        const int color=accent.block.level>=5?0xEBC1FF:0xFFE49A;
        MemRectFrameThick(box.x-grow,box.y+grow,box.w+2*grow,box.h+2*grow,color,std::max(1,(int)(3*s)));
        for(int j=0;j<6;++j){
            const float angle=j*6.2831853f/6+t*.8f,radius=(20+38*t)*s;
            const float z=(.45f+.25f*(1-t))*s;
            DrawIcon(ICON_STAR,(int)(box.x+box.w*.5f+std::cos(angle)*radius-8*z),
                (int)(box.y-box.h*.5f+std::sin(angle)*radius+8*z),z,false,false,false,true);
        }
        SetAlpha(32);
    }
    profile.stamp(3);

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
    if(run.attacking&&action.index>=0&&action.index<(int)run.shots.size()) {
        const Shot& shot=run.shots[action.index];
        if(shot.block.family>=0){const Box from=blockBox(shot.block,l);
            MemRectFrameThick(from.x,from.y,from.w,from.h,0xFFE99E,std::max(1,(int)(3*s)));}
        if(shot.block.family<0)drawTurretAttack(l,enemyBodyKnown?enemyBodyX:ex,enemyBodyKnown?enemyBodyY:ey+(int)(40*s));
        const float appearance=MergeCombat::bulletAppearance(action.time.elapsed,action.time.release);
        if(action.bulletIcon>=0&&action.emitterReady&&appearance>0&&!action.time.applied) {
            const bool flying=action.time.flying();
            const float t=flying?(action.time.elapsed-action.time.release)/(float)std::max(1,action.time.impact-action.time.release):0.f;
            if(!sprite[CREWBULLET_IMG])LoadImg(CREWBULLET_IMG);
            const int startX=flying?action.bulletX:action.emitterX,startY=flying?action.bulletY:action.emitterY;
            const float nativeZoom=(CREWBULLETZOOM+.25f*CREWBULLETZOOM*(action.bulletIcon%3))*1.5f;
            const float zoom=std::max(1.2f,nativeZoom)*s*(flying?1.f:appearance);
            const int hitX=enemyBodyKnown?enemyBodyX:ex,hitY=enemyBodyKnown?enemyBodyY:ey+(int)(40*s);
            DrawCrewBulletAni(action.bulletIcon,(int)(startX+(hitX-startX)*t),
                (int)(startY+(hitY-startY)*t),zoom,
                GetCrewBulletAni(action.bulletIcon),action.time.elapsed-action.time.release,RIGHT);
        }
        if(!action.heroMotion.empty()&&action.skill>=0&&action.time.elapsed>=action.heroStart) {
            DrawSkillIcon(action.caster.currentSkill,shotFromX,ey+(int)(105*s),.65f*s);
        }

    }
    // The reels scroll inside the rounded housing and settle left-to-right.
    if(entering()||!introActive()){
    drawSlotFrame(l.slot);
    for(int i=0;i<3;++i) {
        int pad=std::max(1,(int)(12*s));
        Box window=slotWindow(l.slot,i);
        bool held=!run.tray.empty()&&i<(int)run.tray.size();
        // Keep the stopped result in its reel while a copy flies to the board.
        const bool pending=!run.tray.empty()&&animation==0&&!spinFlying();
        const Block symbol=pending?(held?run.tray[i]:Block()):hasReelSymbols?reelSymbols[i]:Block();
        int f=pending?symbol.family:hasReelSymbols?symbol.family:held?run.tray[i].family:run.families[i];
        int lv=pending?(held?symbol.level:1):hasReelSymbols?symbol.level:held?run.tray[i].level:1,crew=pending?symbol.crew:hasReelSymbols?symbol.crew:held?run.tray[i].crew:-1;
        const float phase=std::min(1.f,(REEL_SPIN_FRAMES-animation)/(float)reelStopFrame(i));
        if(animation>0&&!run.attacking&&phase<1.f){
            //---- 돌다가 선다 ----
            //
            //마지막 한 바퀴를 지나 조금 넘어갔다가 되돌아온다. 그냥 멈추면
            //"바뀌었다" 로만 보이고 슬롯머신으로 안 읽힌다.
            //
            //뒤 릴일수록 바퀴 수가 많다 - 같은 빠르기로 출발해 더 오래 돈다.
            const int pitch=window.h,turns=5+3*i;
            const float ease=1.f-std::pow(1.f-phase,3.f);
            const float over=std::sin(phase*3.14159265f)*(1.f-phase)*REEL_OVERSHOOT*s;
            const float distance=turns*pitch*ease+over;
            const int offset=(int)std::fmod(distance,(float)pitch),turn=(int)(distance/pitch);
            //---- 띠의 끝은 결과다 ----
            //
            //전에는 띠가 계열 세 개를 정해진 차례로 돌다가 서는 순간 결과로
            //바뀌었다. 띠가 선 칸과 결과가 다르면 한 장이 확 갈려서 "돌다가
            //선" 게 아니라 "결과로 바뀐" 것으로 보였다. 세 결과가 같은 판에서
            //특히 그랬다. 마지막 바퀴의 가운데가 결과 계열이 되도록 띠의
            //시작을 맞춘다.
            int strip[FamilyCount];const int n=std::max(1,run.reelFamilies(strip));
            int stopAt=0;for(int k=0;k<n;++k)if(strip[k]==f)stopAt=k;
            const int base=(stopAt-turns%n+n)%n;
            for(int j=-1;j<=1;++j){
                Box symbol=window;symbol.y+=j*pitch-offset;
                SetSectionClip(window.x,window.y,window.w,window.h,false);
                //지나가는 칸의 동료까지 바꿔 가며 보여 주면, 서는 순간
                //사람이 한 번 깜빡이며 갈린다. 설 자리의 계열이면 설 사람을
                //미리 들고 돈다.
                const int rollFamily=strip[(turn+j+base+n)%n];
                icon(rollFamily,symbol,1.f,true,rollFamily==f?lv:1,
                    rollFamily==f?crew:-1);
            }
        }else{
            SetSectionClip(window.x,window.y,window.w,window.h,false);
            reelResultDrawn[i]=true;
            icon(f,window,1.f,true,lv,crew);

            //선 직후 한 번 번쩍인다. 어느 줄이 방금 섰는지가 눈에 걸린다.
            if(animation>0&&!run.attacking) {
                const int left=std::max(0,(int)(REEL_STOP_FLASH-(REEL_SPIN_FRAMES-animation)+reelStopFrame(i)));
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
    Box heartPlate=l.heart;
    heartPlate.y+=(int)(4*s);heartPlate.h+=(int)(4*s);
    mergeGoldFrame(heartPlate,0x382C31,0x201B25);
    for(int side=0;side<2;++side){Box bolt={heartPlate.x+(int)((side?heartPlate.w/s-14:6)*s),heartPlate.y-heartPlate.h/2+(int)(4*s),(int)(8*s),(int)(8*s)};
        bevel(bolt,0xD8D9E4,(int)(2*s));bevel(inset(bolt,std::max(1,(int)s)),0x7B8294,(int)s);}
    int cols=heartCapacity>10?10:heartCapacity;
    int heartSize=(int)(30*s),pitch=(int)(35*s),x0=DX/2-(cols*pitch-(int)(5*s))/2;
    int rows=(heartCapacity+cols-1)/cols;
    int heartTop=l.heart.y-(int)((l.heart.h-30*s*12/14)/2);
    for(int i=0;i<heartCapacity;++i) {
        bool filled=i<heartDisplay;
        if(i==spentHeart&&heartBlink>0)filled=((int)(heartBlink/.09f)%2)==0;
        heart(x0+(i%cols)*pitch,heartTop-(i/cols)*(int)(23*s),heartSize,filled);
    }
    if(run.lost) {
        button(l.spin,"다시 도전","새 런 시작",0x24578D);button(l.attack,"로비로",nullptr,0x975028);
    } else {
        bool ready=!entering()&&!introActive()&&!spinFlying()&&!deckArriving()&&!waveTransition.active()&&!run.attacking&&animation==0;
        choice(l.spin,ChoiceSpin,ready&&run.canSpin()&&robin.heart>0);
        choice(l.attack,ChoiceAttack,ready&&!run.board.empty()&&robin.heart>0&&run.boardResolved());
        if(!siegeActive)choice(l.cannon,ChoiceCannon,ready&&robin.heart>0&&run.boardResolved());
        if(ready&&!run.board.empty()&&predicted>=run.enemyHp)
            MemRectFrameThick(l.attack.x,l.attack.y,l.attack.w,l.attack.h,0xFFE36A,std::max(1,(int)(3*s)));
        // Spin budget is a rule hint, not a slot-machine counter.
        if(run.spins==0&&run.tray.empty())label("이번 적립 종료 · 공격하세요",DX/2,DY-(int)(45*s),0.46f,0xFFD26A);
    }
    drawRouletteTrash(l);
    if(picked>=0) {
        auto& src=pickedTray?run.tray:run.board;
        if(picked<(int)src.size()) {
            Block b=src[picked];int x=(int)((pointerX-l.board.x)/l.cell)-pickCellX;
            int y=(int)((l.board.y-pointerY)/l.cellH)-pickCellY;
            b.x=x;b.y=y;Box box=blockBox(b,l);
            //판 안이면 놓인다. 깨끗한 자리는 초록, 겹치는 자리는 주황(놓이긴 하되 풀어야 한다).
            bool valid=run.fits(b,pickedTray?-1:picked,-1,true),clean=run.fits(b,pickedTray?-1:picked);
            int target=run.at(x,y);
            if(target>=0&&!(target==picked&&!pickedTray)) {
                Block merged;
                if(run.mergeable(run.board[target],b)&&run.mergedPreview(target,b,pickedTray?-1:picked,merged)){valid=clean=true;box=blockBox(merged,l);}
            }
            // Only show a placement cue on actual board cells.
            // Invalid/off-board drags never create a ghost grid beside the castle.
            if(valid&&!nearRouletteTrash(l,pointerX,pointerY))
                MemRectFrameThick(box.x,box.y,box.w,box.h,clean?0x58DB9C:0xFF9A3C,(int)(3*s));
            //---- 손에 든 것도 판에 놓인 그대로 ----
            //
            //한 칸짜리로 줄여 들면 집는 순간 물건이 바뀐 것처럼 보인다.
            //판에서 쓰던 크기·그림 그대로, 쥔 칸만큼 어긋나게 든다.
            Box held={(int)pointerX-pickCellX*l.cell-l.cell/2,
                (int)pointerY+pickCellY*l.cellH+l.cellH/2,
                Wide(b)*l.cell,Tall(b)*l.cellH};
            drawBlock(b,held);
            if(!nearRouletteTrash(l,pointerX,pointerY))drawHeldHelp(src[picked],l);
        }
    }
    if(messageTime>0&&!message.empty()) {
        Box toast={(int)(90*s),l.arenaBottom+(int)(53*s),(int)(460*s),(int)(48*s)};
        panel(toast,0x352332,0xDD957B);
        label(message.c_str(),DX/2,toast.y-(int)(6*s),.59f,0xFFE6C0);
    }
    if(messageTime<=0&&!run.choosing&&!message.empty()&&(message.find("없")!=std::string::npos||message.find("부족")!=std::string::npos))
        label(message.c_str(),DX/2,DY-(int)(45*s),0.48f);
    drawSpinLanding(l);
    if(siegeActive){Siege::drawExpanded(l);Siege::drawHand(l);}   //공성전: 펼친 상대 판과 상대의 손은 내 블록 위에
    else MonsterBoard::drawExpanded(l);   //몬스터의 판도 같은 자리에 펼친다
    if(RewardPopup::open()&&waveTransition.age>=MergeCombat::WaveTransition::DefeatFrames)RewardPopup::draw();
    if(!entering())drawIntro(l);
    if(flash>0){impactDrawOrder=++objectDrawOrder;drawImpactSequence(impactFirst,impactCount,18-flash,18,enemyBodyKnown?enemyBodyX:ex,enemyBodyKnown?enemyBodyY:ey+(int)(40*s),RIGHT,.65f*s);}
    if(allyFlash>0)drawImpactSequence(HIT_ITEM_SMALL0,5,20-allyFlash,20,allyBodyKnown?allyBodyX:(int)(DX*.66f),allyBodyKnown?allyBodyY:ey+(int)(40*s),LEFT,.65f*s);
    drawCombatNumbers();
    if(!holdReview)reviewStep(l);
}

bool MergeRouletteTouch(int phase,int id,float x,float y) {
    static int debugFinger=-1;
    if(!active) {
        if(phase!=0&&debugFinger==id){if(phase==2||phase==3)debugFinger=-1;return true;}
        if(phase==0&&drawHandle==MD_LOBBY&&popUpCnt==0&&!LoadoutOpen()) {
            float s=DX/640.0f;
            Layout l=layout();Box b=lobbyStart(l);
            if(b.has(x,y)) {MergeRouletteBegin();return true;}
            if(lobbyPvp(l).has(x,y)) {Siege::begin();return true;}
            Box keep=lobbyContinue(l);
            if(keep.has(x,y)&&robin.mergeRouletteRun[0]&&robin.mergeRouletteHero==curHero) {MergeRouletteBegin(true);return true;}
            if(lobbyDebugTouch(l,x,y)){debugFinger=id;return true;}
            for(int i=0;i<4;++i)if(roomBox(l,i).has(x,y)){
                CastleMenuFocusFacility(i);systemKey=AVK_POPUP_CASTLEMENU;return true;
            }
        }
        return false;
    }
    if(RewardPopup::open()&&waveTransition.age>=MergeCombat::WaveTransition::DefeatFrames){   //보상창: 단추만 받는다
        if(phase==0)RewardPopup::touch(x,y);
        picked=finger=-1;return true;
    }
    if(entering()||introActive()||spinFlying()||deckArriving()||waveTransition.active()) {picked=finger=-1;return true;}
    if(phase==3) {if(finger==id){picked=-1;finger=-1;}return true;}
    if(phase==0) {
        if(finger>=0)return true;
        if(siegeActive&&Siege::blocked()){   //상대 턴·승리 뒤에는 나가기만
            if(layout().exit.has(x,y)){finger=id;downX=pointerX=x;downY=pointerY=y;picked=-1;}
            return true;
        }
        if(siegeActive&&Siege::tapPanel(x,y))return true;   //상대 판 터치 = 크게/닫기
        if(!siegeActive&&MonsterBoard::tapPanel(x,y))return true;   //몬스터 판 터치 = 크게/닫기
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
        if(nearRouletteTrash(l,x,y)){
            const bool fromTray=pickedTray;
            if(run.discard(fromTray,picked)){
                picked=-1;trashSwallowTicks=18;message="";save();PlayMusic(M_BUTTON);
                if(fromTray)endSpinTurn();
                return true;
            }
        }
        const bool tap=std::abs(x-downX)+std::abs(y-downY)<10*l.scale;
        bool rotated=false;
        if(pickedTray&&tap)ok=run.autoPlace(picked);
        else if(!pickedTray&&tap){ok=rotated=run.rotate(picked);if(!ok)run.lastFail="spot";}   //판의 것을 톡 치면 돌린다
        else ok=run.drop(pickedTray,picked,(x-l.board.x)/l.cell,(l.board.y-y)/l.cellH);
        if(ok)observeDeckMerge();
        if(ok&&pickedTray)endSpinTurn();   //트레이를 손으로 다 놓아도 턴이 넘어간다
        if(ok&&!pickedTray&&pendingPass)endSpinTurn();   //겹침을 풀었으면 미뤄 둔 턴을 넘긴다
        const bool overlapped=ok&&!run.boardResolved();
        //---- 왜 안 되는지까지 적는다 ----
        //
        //"배치/합성할 수 없습니다" 만으로는 자리가 없어서인지, 다른
        //물건이라서인지, 더 올라갈 데가 없어서인지를 알 수가 없다.
        //모델이 어디서 걸렸는지 남겨 둔다(run.lastFail).
        if(ok) message=overlapped?OverlapMessage:"";
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
        if(!ok||overlapped)messageTime=3;
        if(ok)PlayMusic(rotated?M_BUTTON:M_POWERUP);
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
    if(l.spin.has(x,y)&&l.spin.has(downX,downY)) {
        if(!run.boardResolved()){message=OverlapMessage;messageTime=3;return true;}
        if(!run.canSpin()){message=u8"\uc774\uc804 \uacb0\uacfc\ub97c \ubc30\uce58\ud558\uac70\ub098 \uc4f0\ub808\uae30\ud1b5\uc5d0 \ubc84\ub824\uc8fc\uc138\uc694.";messageTime=3;return true;}
        if(pay()){run.spin();rememberReelSymbols();gearStartAngle=gearAngle;animation=REEL_SPIN_FRAMES;message="";save();}
    } else if(l.attack.has(x,y)&&l.attack.has(downX,downY)) {
        //"지금 공격" 은 막지 않는다. 아직 못 놓은 결과가 있으면 들어가는 것은 앉히고,
        //자리 없는 것은 두고 나간다. 칸이 비어 있어도 모양이 안 맞으면 못 놓는 일이 있다.
        if(!run.tray.empty()){
            while(!run.tray.empty()&&run.autoPlace(0)){}
            if(!run.tray.empty()){message=u8"\ub0a8\uc740 \uacb0\uacfc\ub97c \ubc30\uce58\ud558\uac70\ub098 \uc4f0\ub808\uae30\ud1b5\uc5d0 \ubc84\ub824\uc8fc\uc138\uc694.";messageTime=3;save();return true;}
            picked=-1;pickedTray=false;
        }
        if(run.board.empty()){message="인벤토리가 비어 있습니다.";return true;}
        if(!run.boardResolved()){message=OverlapMessage;messageTime=3;return true;}
        if(pay()){run.attack(stats);action=CombatAction();enemyTurn=EnemyTurn();animation=0;message="출격!";save();}
    } else if(!siegeActive&&l.cannon.has(x,y)&&l.cannon.has(downX,downY)) {
        //성의 대포. 판이 비어 있어도 쏜다 - 블록이 없을 때의 마지막 수단이기도 하다.
        if(!run.boardResolved()){message=OverlapMessage;messageTime=3;return true;}
        if(pay()){run.fireCannon(stats,cannonShell());action=CombatAction();enemyTurn=EnemyTurn();animation=0;message="포격!";save();}
    }
    return true;
}
#pragma pack(pop)
bool MergeRouletteDebugTouchReview(){
 if(!getenv("CS_CASTLE_FREE_PREVIEW_REVIEW"))return false;
 const auto saved=robin.castleProgress;const auto gold=robin.gold;bool ok=true;
 const auto check=[&](bool pass,int c,int part){if(!pass){std::ofstream f(std::string(getenv("CS_CASTLE_REVIEW_PATH"))+"phases.log",std::ios::app);f<<"DETAIL touch castle="<<c<<" part="<<part<<"\n";}ok=ok&&pass;};
 const auto tap=[](const Box& b){const float x=b.x+b.w*.5f,y=b.y-b.h*.5f;const bool hit=MergeRouletteTouch(0,998,x,y);MergeRouletteTouch(2,998,x,y);return hit;};
 for(int c=0;c<10;++c){
  gMobileCastleVisual=run.stage=c;Layout l=layout();
  for(int r=0;r<4;++r){const int before=LobbyCastleDebugFacilityLevel(c,r);
   check(tap(roomBox(l,r))&&LobbyCastleDebugFacilityLevel(c,r)==(before+1)%6,c,r);
  }
  const int cannon=CastleVisualPartLevel(c,3);
  check(tap(castleCannonBox(l))&&CastleVisualPartLevel(c,3)==(cannon+1)%6,c,4);
  check(tap(OriginalCastle::box(95,740,12,12))&&LobbyCastleDebugCastle()==(c+1)%10,c,5);
 }
 const int before=LobbyCastleDebugCastle();
 ok=MergeRouletteTouch(0,998,1,DY*.5f)&&LobbyCastleDebugCastle()==before&&ok;
 return ok&&robin.gold==gold&&memcmp(&saved,&robin.castleProgress,sizeof(saved))==0;
}
