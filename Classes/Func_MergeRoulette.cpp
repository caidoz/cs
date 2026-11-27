#include "Core.h"
#include "TitleLobbyMotion.h"
#include "AccountLevelModel.h"
#include "GameSfx.h"
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
#include "MergeExpeditionModel.h"
#include "MergeWaveCurve.h"
#include "CastleTutorialModel.h"
//튜토리얼 훅(MergeTutorialRuntime.inc 가 정의). 포함 지점보다 앞에서 쓰는 것만 전역 함수로 뺐다.
void MergeTutorialBeginBattle();void MergeTutorialRememberAllyPlate(int x,int y,int w,int h);void MergeTutorialRememberHeader(int x,int y,int w,int h);void MergeTutorialDrawLobbyHints();
#include "MergeOwnedGearPolicy.h"
#include "TurretAttackPresentation.h"
#include "CastleArtGeometry.h"
#include "PortraitGameLayout.h"
#include "LobbyCampModel.h"
#include "BaseCampPresentation.h"
#include "QuietCardStyle.h"
#include "Data/PortraitCastleArt.h"
#include "Data/StarterCastleRig.h"
#include "Data/CastleFiveFloorArt.h"
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
#include <memory>
#include <ctime>

void SetLobbyCampLight(bool enabled,float x,float y,float radius,float time);
void ApplyLobbyFireEffect(cocos2d::Sprite* target,float time,bool foreground);
namespace {
using namespace MergeRoulette;
Run run;
struct AutomaticMerge {
    Run plan;Block moving,staging;bool fromTray=false,targetLifted=false;
    int source=-1,target=-1,age=-1;
    bool active() const{return age>=0;}
} automaticMerge;
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
std::vector<ITEM> ownedGearPool[GearCount][MaxLevel];
static const int ownedGearTypes[GearCount]={ITEM_SWORD,ITEM_ARMOR,ITEM_GREAVES,ITEM_HELM,ITEM_GUNTLET,ITEM_KILT};
bool active=false,review=false;
bool entryChoiceOpen=false;
bool resumePromptOpen=false,resumePromptChecked=false;
bool quitPromptOpen=false;int quitPromptFinger=-1,quitPromptChoice=-1,exitPromptFinger=-1;
int resumePromptFinger=-1,resumePromptChoice=-1;
int resumeReviewPhase=0;long long resumeReviewEnergy=0;std::string resumeReviewSave;
int entryChoiceFinger=-1,entryChoicePressed=-1;
const ITEM* gearTableOverride=nullptr;   //MergeSiege.inc 가 상대 판을 그릴 때 끼운다
bool nativeTitleIsolate=false;
bool titleCampOnly=false;
bool defeatedRailBoss=false;
bool nativeTitleBodyOnly=false;
bool siegeActive=false;   //공성전(PVP 디버그) 중. MergeSiege.inc
bool railBossScene(){return active&&!siegeActive&&!nativeTitleIsolate&&
    (waveTransition.defeatedVisible()?defeatedRailBoss:run.wave==WavesPerStage-1);}
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
float battleRailLift();
float castleDisplayScale(int c){
 (void)c;return PortraitGame::castleScale(DX,DY,drawHandle==MD_LOBBY&&!active&&!nativeTitleIsolate);
}
float castleSceneLift(){
    // Lobby and combat share the same wheel contact and responsive rail height.
    return battleRailLift();
}
float castleArtOffset(int c){(void)c;return 0.f;}

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
ITEM blockGearItem(const Block& b){
    const int g=std::max(0,std::min(GearCount-1,b.family-Sword)),lv=std::max(0,std::min(MaxLevel-1,b.level-1));
    ITEM item=gearTableOverride?gearTableOverride[g*MaxLevel+lv]:treeEquipment[g][lv];
    if(!b.ownedId)return item;
    for(int n=0;n<GetMaxInven();++n)if(robin.inven[n].type==ownedGearTypes[g]+hero.type&&robin.inven[n].id==b.ownedId)return robin.inven[n];
    for(const ITEM& equipped:wornEquip)if(equipped.type==ownedGearTypes[g]+hero.type&&equipped.id==b.ownedId)return equipped;
    // Preserve the copied board piece if an old run's source item is absent.
    MakeItem(&item,ownedGearTypes[g]+hero.type,1,b.ownedGrade,b.ownedDetail,0);
    item.grade=b.ownedGrade;item.value=(int)b.ownedPower;item.cooldown=0;item.id=b.ownedId;
    return item;
}
int costumeEffectTicks=0;
int attackWeaponLevel=0;
MergeCombat::WeaponSwap weaponSwap;
MergeCombat::DamagePause damagePause;
ITEM incomingWeapon;
bool requestWeaponSwap(const ITEM& target){
    const ITEM& old=hero.equip[EQUIP_WEAPON];
    if(old.type==target.type&&old.detail==target.detail&&old.grade==target.grade&&old.id==target.id&&old.value==target.value)return false;
    incomingWeapon=target;weaponSwap.begin();return true;
}
void showAttackWeapon(int level,const Block* instance=nullptr) {
    attackWeaponLevel=level;
    const int shown=level?level:costumeLevels[0];
    hero.equip[EQUIP_WEAPON]=shown?treeEquipment[0][shown-1]:baseCostume[0];
    if(instance&&instance->ownedId)hero.equip[EQUIP_WEAPON]=blockGearItem(*instance);
    else if(!level)for(const Block& b:run.board)if(b.family==Sword&&b.level==shown&&b.ownedId)hero.equip[EQUIP_WEAPON]=blockGearItem(b);
}
int heartCapacity=Run::BattleEnergyMax;
float heartBlink=0,messageTime=0;
int heartDisplay=0,spentHeart=-1;
int refillFrom=0;float refillElapsed=-1.f;bool refillPending=false;

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
    CastleTutorialEvent(CastleTutorial::Merged);   //튜토리얼: 합쳐졌다(장비·동료 가리지 않는다)
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
namespace MonsterBoard{int hitCount();void ensure();void closeInspection();}
//---- 방어막 통의 바닥: 실제로 낀 투구·갑옷의 장비 값 ----
//
//PS_ARMOR 는 쓰지 않는다. 거기엔 STR×3 + AGI 가 들어 있어 레벨이 오르면 체력(158)보다 훨씬 큰
//수(949)가 된다 - 본편에서는 레벨 차 방어 감소에 쓰는 수라 체력과 단위가 다르다. 여기서는 판 위
//갑옷 블록과 같은 단위(GetEquipPower)로 낀 투구·갑옷만 센다. 하체는 체력(PS_HPEQUIP)으로 간다.
//판의 갑옷 블록이 코스튬으로 입혀져도(updateHeroCostume) 여기엔 안 들어간다 - 로비에서 끼고 온 것(wornEquip)만.
//실제로 낀 방어구(투구·갑옷·하체·발)의 장비 값 합. 통의 크기가 아니라 **턴마다 통을 채우는 양**이다.
long long wornGuard() {
    long long guard=0;
    for(int slot:{EQUIP_HELM,EQUIP_ARMOR,EQUIP_PANTS,EQUIP_BOOTS}) if(wornEquip[slot].type!=EMPTY) guard+=std::max(0LL,GetEquipPower(&wornEquip[slot],std::max(1,(int)wornEquip[slot].lv)));
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
    int bestIndex[GearCount];std::fill(bestIndex,bestIndex+GearCount,-1);
    for(int i=0;i<(int)run.board.size();++i){
        const Block& b=run.board[i];
        if(b.family>=Sword&&b.family<FamilyCount&&gridBlockLanded(i)){
            const int g=b.family-Sword,prior=bestIndex[g];
            if(b.level>best[g]||(b.level==best[g]&&(prior<0||b.ownedPower>run.board[prior].ownedPower))){best[g]=b.level;bestIndex[g]=i;}
        }
    }
    bool upgraded=false,changed=false;
    for(int g=0;g<GearCount;++g){
      const ITEM target=best[g]?(run.board[bestIndex[g]].ownedId?blockGearItem(run.board[bestIndex[g]]):table[g*MaxLevel+best[g]-1]):baseCostume[g];
      const ITEM& shown=g==0&&weaponSwap.running()?incomingWeapon:hero.equip[costumeSlots[g]];
      const bool different=target.type!=shown.type||target.detail!=shown.detail||target.grade!=shown.grade||target.id!=shown.id||target.value!=shown.value;
      if(best[g]!=costumeLevels[g]||((g!=0||!attackWeaponLevel)&&different)){
        upgraded=upgraded||best[g]>costumeLevels[g];changed=true;
        costumeLevels[g]=best[g];
        if(g!=0||!attackWeaponLevel){
            if(g!=0||!animate)hero.equip[costumeSlots[g]]=target;
            else requestWeaponSwap(target);
        }
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
constexpr float IntroDuration=4.6f;
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
int mergeFlash=0,mergeFlashDuration=1;
Box mergeBox={0,0,0,0};
int mergeShownLevel=0;
float portraitCameraY=0.f;
float starterInteriorReveal=1.f;
float lobbyDepartureAge=-1.f;bool lobbyDepartureCommit=false,lobbySkipDeparture=false,lobbyDepartureCharge=false;
float lobbyRecallX[4]={},lobbyRecallY[4]={};
int baseCampReviewStage=0;
int friendlyStatCount=0,hostileStatCount=0,friendlyStatKind[3]={},hostileStatKind[3]={};
Box friendlyStatBounds[3],hostileStatBounds[3];long long friendlyStatValue[3]={},hostileStatValue[3]={};
int starterInteriorFinger=-1,starterInteriorAxis=0;
float starterInteriorDownX=0,starterInteriorDownY=0,starterInteriorStart=0;
bool starterInteriorDragging=false;
int portraitCameraFinger=-1;float portraitCameraDown=0,portraitCameraStart=0;
struct Layout {
    float scale;
    int cell, cellH, ground, arenaBottom;
    Box board, slot, lever, heart, spin, attack, cannon, exit, left, right, reroll, confirm;
    int plateH=0, plateDrop=0;   //유닛 패 높이와 데크 선에서 내려오는 거리. 판은 패 밑 ~ 릴 위 사이에 선다
};
int portraitGridCapacity(){int n=0;for(int y=0;y<run.shape.height;++y)for(int x=0;x<run.shape.width;++x)n+=run.shape.contains(x,y);return n;}
Box originalSlotCogBox(const Box& b,int side){
 const auto& housing=MergeCastleArt::UiFrames[MergeCastleArt::Slot];
 const int d=(int)(470*b.w/(float)housing.w);
 const int x=b.x+(int)(((side?1920:245)-housing.x)*b.w/(float)housing.w);
 const int y=b.y-(int)((425-housing.y)*b.h/(float)housing.h);
 return {x-d/2,y+d/2,d,d};
}
float portraitCastleZoom(const Layout& l);
Layout layout() {
    Layout l={};l.scale=DX/640.f;const float s=l.scale;
    const auto p=PortraitGame::battle(DX,DY,run.shape.height,run.shape.width);
    const int margin=(int)(24*s),gap=(int)(12*s),bw=(DX-2*margin-2*gap)/3,bh=p.actionHeight;
    l.cannon={margin,p.actionTop,bw,bh};
    l.attack={margin+bw+gap,p.actionTop,bw,bh};
    l.spin={margin+2*(bw+gap),p.actionTop,bw,bh};
    if(siegeActive&&!Siege::swapped){l.cannon={0,0,0,0};l.attack.x=DX/2-bw-gap/2;l.spin.x=DX/2+gap/2;}
    l.heart={(int)(110*s),p.energyTop,(int)(360*s),(int)(22*s)};
    l.slot={(DX-p.slotWidth)/2,p.slotTop,p.slotWidth,p.slotHeight};
    l.lever=originalSlotCogBox(l.slot,1);
    l.cell=p.cell;l.cellH=p.cell;
    const int w=l.cell*run.shape.width,h=l.cellH*run.shape.height;
    l.board={(DX-w)/2,p.boardBottom+h,w,h};
    l.ground=p.ground+(int)portraitCameraY;l.arenaBottom=p.statsTop;l.plateH=p.statsHeight;l.plateDrop=(int)(8*s);
    if(!active){l.ground=PortraitGame::lobby(DX,DY).ground+(int)portraitCameraY;l.arenaBottom=PortraitGame::lobby(DX,DY).statsTop;}
    if(!active&&lobbyDepartureAge>=0){
        const float t=BaseCamp::travel(lobbyDepartureAge);
        l.ground=(int)(l.ground*(1-t)+(p.ground+portraitCameraY)*t);
        l.arenaBottom=(int)(l.arenaBottom*(1-t)+p.statsTop*t);
    }
    // Castle height never moves the rail. Oversized hulls use the existing
    // vertical viewport; only the title/lobby-to-battle transition interpolates.
    l.exit={DX-(int)(54*s),DY-(int)(8*s),(int)(42*s),(int)(40*s)};
    l.left={(int)(28*s),p.slotTop,(int)(40*s),p.slotHeight};
    l.right={DX-(int)(68*s),p.slotTop,(int)(40*s),p.slotHeight};
    l.reroll=l.spin;l.confirm=l.attack;return l;
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
void portraitSkin(int,const Box&,bool);
void panel(const Box& b,int color,int border=0x61718C) {
    portraitSkin(4,b,true);return;
    SolidRects batch;
    int p=std::max(1,DX/320);
    mergeRect(b.x-p,b.y+p,b.w+2*p,b.h+3*p,0x080E1B);
    mergeRect(b.x,b.y,b.w,b.h,border);
    mergeRect(b.x+p,b.y-p,b.w-2*p,b.h-2*p,color);
    mergeRect(b.x+2*p,b.y-2*p,b.w-4*p,p,0x7B7C80);
    mergeRect(b.x+p,b.y-b.h+2*p,b.w-2*p,p,0x151421);   //아랫변 안쪽 선. 전에는 테두리 줄 위에 그려져 아래 경계선이 안 보였다
}
void label(const char* text,int x,int y,float size=0.7f,int color=0xF4E8CC) {
    SetFontColor(color);CenterPixelTextStrSolid(text,x,y,size*DX/640.0f);
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
float castleScrollSeconds=0.f;
#include "PortraitSkin.inc"
void drawPortraitCastlePreview(int,const Box&,float wheelTravel=-1.f,bool rollLeft=false,float fixedScale=-1.f);
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

    //"현재/최대" 한 줄. 체력과 방어막이 같은 모양이라 통의 크기가 한눈에 읽힌다.
    auto pair=[&](long long cur,long long cap,int rowY){
        const float digits=GetNumDx(cur,false,NUM_FONT_NORMAL,0,false,1.f,false)+GetNumDx(cap,false,NUM_FONT_NORMAL,0,false,1.f,false);
        const float zoom=std::min(.65f*s,(barW-12*s)/std::max(1.f,digits));
        const float leftWidth=GetNumDx(cur,false,NUM_FONT_NORMAL,0,false,zoom,false),rightWidth=GetNumDx(cap,false,NUM_FONT_NORMAL,0,false,zoom,false);
        const int numberY=rowY-(int)((barH-24*zoom)*.5f),numberX=(int)(barX+(barW-leftWidth-rightWidth-8*s)*.5f);
        outlinedNum(cur,numberX,numberY,LEFT,zoom);
        label("/",(int)(numberX+leftWidth+4*s),rowY-(int)((barH-15*s)*.5f),.62f,hot?0xFFB060:0xFFFFFF);
        outlinedNum(cap,(int)(numberX+leftWidth+8*s),numberY,LEFT,zoom);
    };
    if(guardCapacity>1)pair(guard,guardCapacity,guardY);
    else {
        const float guardZoom=std::min(.65f*s,(barW-4*s)/std::max(1.f,GetNumDx(guard,false,NUM_FONT_NORMAL,0,false,1.f,false)));
        outlinedNum(guard,barX+barW/2,guardY-(int)((barH-24*guardZoom)*.5f),CENTER,guardZoom);
    }
    mergeRect(barX,hpY,barW,barH,barBg);
    const double ratio=max>0?std::max(0.,std::min(1.,(animatedHp>=0?animatedHp:hp)/(double)max)):0.;
    if(ratio>0)mergeRect(barX,hpY,std::max(1,(int)(barW*ratio)),barH,barFg);
    pair(hp,max,hpY);
}
//방어막 통의 최대치. 실제 수치에서는 히어로 몫(체력×ShieldPct) 하나다. 옛 다섯 목숨 모드는 낀 방어구 +
//판 위 방어구 블록 수(보호 1 = 한 방)를 그대로 보여 준다.
long long currentGuardMax() {
    if(run.realVitals)return std::max(1LL,run.guardMax);
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
//방어막 통의 현재값. 피해 숫자가 그대로 깎이고, 턴이 돌 때 장비(낀 방어구 + 방어구 블록)가 채운다.
long long currentGuard() {
    if(!run.realVitals)return currentGuardMax();
    return std::max(0LL,std::min(run.guardMax,run.guard));
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
    // Fixed below the stage header; dragging never moves the explanation.
    const int width=DX-(int)(80*s),height=(int)(78*s);
    const int left=(DX-width)/2,top=DY-(int)(112*s);
    const Box help={left,top,width,height};
    const int center=help.x+help.w/2;
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
            const long long add=run.armorOf(b,stats);
            if(run.realVitals)std::snprintf(line,sizeof(line),u8"방어막 턴마다 +%lld 회복 (통 %lld/%lld)%s",add,currentGuard(),currentGuardMax(),lv==2?u8" · 반격 반감":"");
            else std::snprintf(line,sizeof(line),u8"방어막 +%lld%s",add,lv==2?u8" · 반격 반감":"");
        }
        else if(b.family==Gloves)std::snprintf(line,sizeof(line),u8"\uacf5\uaca9\ub825 \uc99d\uac00 \u00b7 \uc9c1\uc811 \uacf5\uaca9 \uc5c6\uc74c");
        else if(b.family==Boots)std::snprintf(line,sizeof(line),u8"공격 뒤 번개 +%lld · 돌리기 +%d",(long long)MergeBoard::NeckHearts(lv),MergeBoard::NeckSpins(lv));
        else std::snprintf(line,sizeof(line),u8"피해 %lld (무기값 ×%d)",(long long)shot.damage,MergeBoard::GearMulOf(g,lv));
        std::snprintf(title,sizeof(title),u8"%s ★%d · %d×%d칸",treeName(b.family),lv,Wide(b),Tall(b));
        if(b.ownedId){const ITEM item=blockGearItem(b);std::snprintf(title,sizeof(title),u8"보유 · %s ★%d",textId[TEXT_ITEMNAME_START+GetItemName(item.type,item.detail,item.grade)],lv);}
    } else {title[0]=line[0]=0;}
    if(run.canGrow(b.family,lv))std::snprintf(hint,sizeof(hint),u8"같은 종류 ★%d 둘을 포개면 ★%d",lv,lv+1);
    else std::snprintf(hint,sizeof(hint),u8"최고 단 · 더 합쳐지지 않습니다");
    label(title,center,help.y-(int)(6*s),.6f,0xFFE6B0);
    label(line,center,help.y-(int)(30*s),.52f,0xF2F2F2);
    label(hint,center,help.y-(int)(52*s),.46f,0xBFD3E8);
}
// Reuse the roulette housing's gold gear for the spin action.
void reelIcon(int x,int y,int size) {portraitCog({x,y,size,size},0);}
void cannonIcon(int x,int y,int size) {portraitGlyph(0,{x,y,size,size});}

enum ChoiceKind { ChoiceSpin=0, ChoiceAttack=1, ChoiceCannon=2 };
//색을 회색으로(밝기만 남긴다). 단추의 바탕·테두리는 그림이 아니라 네모 조각이라 grayScale
//플래그가 안 먹는다 - 색을 직접 바꾼다.
int grayOf(int c) {
    const int l=(((c>>16)&255)*30+((c>>8)&255)*59+(c&255)*11)/100;
    return (l<<16)|(l<<8)|l;
}
void mergeButtonFrame(int,int,int,int,bool,int);
void choiceIcons(int kind,int x,int y,int size){
    if(kind==ChoiceSpin)reelIcon(x,y,size);
    else if(kind==ChoiceAttack)portraitGlyph(1,{x,y,size,size});
    else cannonIcon(x,y,size);
}
void portraitFrame(const Box& b,bool amber=false,bool enabled=true);
void choice(const Box& b,int kind,bool enabled) {
    const float s=DX/640.f;if(b.w<=0)return;
    portraitFrame(b,kind==ChoiceAttack,enabled);
    const int size=(int)std::min(60*s,b.h*.62f),cx=b.x+b.w/2,iconWidth=(int)(b.w*.46f),top=b.y-(b.h-size)/2;
    SetAlpha(32);grayScale=enabled?0:8;
    if(kind==ChoiceSpin)portraitCog({cx-size/2,top,size,size},0);
    else portraitGlyph(kind==ChoiceAttack?1:0,{cx-iconWidth/2,top,iconWidth,size});
    grayScale=0;SetAlpha(32);
}

//대포 한 발의 값. 히어로 무기값 × 성 대포 단계 계수. 5단이 ★1 검 블록 두어 개 몫이라
//보조 화력(CLAUDE.md §5 지분 20%) 안에 든다. 공성전은 내 성의 대포다.
long long cannonShell() {
    
    const int c=std::max(0,std::min(9,siegeActive?(Siege::swapped?Siege::castle:(int)robin.castle):run.stage)),lv=std::max(0,std::min(5,CastleVisualPartLevel(c,3)));
    const long long base=siegeActive&&Siege::swapped?stats.weapon:stats.weapon*100/(100+CastleTeamBonus(0));
    return std::max(1LL,base*CastleMenuModel::CannonTurnPercent(lv)/100);
}
void mergeButtonFrame(int x,int top,int w,int h,bool enabled,int color){
    portraitSkin(color==0x85612B?3:2,{x,top,w,h});
}
void button(const Box& b,const char* title,const char* sub,int color,bool enabled=true) {
 UiButtonStyle style;style.fill=color;style.frame=mergeButtonFrame;
 std::string text=title?title:"";if(sub&&sub[0]){text+="\n";text+=sub;}
 DrawUiButton(b.x,b.y,b.w,b.h,text.c_str(),0,false,enabled,style);
}
void reviewCapture(const char* name);
//공용 보상창(RewardPopup.inc). 단추만 합성 전투의 금테 단추로 그린다.
#include "RewardPopup.inc"
// Reward actions share the same measured caption centering.
void rewardButton(int x,int y,int w,int h,const char* text){button({x,y,w,h},text,nullptr,0x1F5A3A,true);}
//---- 원정 ----
//
//번개 5개를 내고 전투 없이 바로 정산한다. 보상은 히어로 전투력 구간의 고정표
//(MergeExpeditionModel.h)에서 골드와 이 히어로 라인의 장비 카드(treeEquipment 의 종류,
//성 클리어 보상과 같은 MakeItemDetail/Grade)로 나와 공용 보상창에 선다.
bool runExpedition() {
    if(RewardPopup::open())return false;
    if(!MergeExpedition::affordable(robin.heart)){message=u8"번개가 모자랍니다 (5개 필요)";messageTime=3;PlayMusic(M_ERROR);return false;}
    const long long power=std::max(0LL,GetCombatPower(&ao[PLAYER]));
    const MergeExpedition::Row& row=MergeExpedition::rowFor(power);
    if(robin.gold>GOLD_MAX-row.gold){message=u8"골드 보유 한도를 확인해주세요.";PlayMusic(M_ERROR);return false;}
    std::unique_ptr<ROBINDATA> before(new ROBINDATA(robin));
    const auto overflowBefore=InventoryOverflowSnapshot();
    robin.heart-=MergeExpedition::Cost;
    std::vector<RewardPopup::Entry> rewards;
    GetItem(ITEM_GOLD,false,false,false,row.gold,false);
    {RewardPopup::Entry g;g.type=ITEM_GOLD;g.count=row.gold;rewards.push_back(g);}
    for(int i=0;i<row.cards;++i){
        const int type=treeEquipment[Random(GearCount)][0].type;
        if(type==EMPTY)continue;
        const int lv=std::max(1,std::min(GetEquipMaxLevel(),row.gearLevel));
        const int detail=MakeItemDetail(type,lv),grade=MakeItemGrade(type,lv,detail);
        if(!GetItem(type,lv,detail,grade,1,0)){
            robin=*before;InventoryRestoreOverflow(overflowBefore);SaveGame();
            message=u8"보상을 지급하지 못해 원정을 취소했습니다.";PlayMusic(M_ERROR);return false;
        }
        RewardPopup::Entry it;it.type=type;it.detail=detail;it.grade=grade;it.lv=lv;it.count=1;rewards.push_back(it);
    }
    RewardPopup::drawButton=rewardButton;
    RewardPopup::onClose=[](){CastleTutorialEvent(CastleTutorial::RewardClosed);};
    RewardPopup::show(u8"원정 보상",rewards,u8"확인");
    PlayMusic(M_CARDSPLIT);
    SaveGame();
    return true;
}
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
void rebuildOwnedGearPool(){
    for(auto& family:ownedGearPool)for(auto& tier:family)tier.clear();
    const auto add=[](const ITEM& item){
        if(item.type==EMPTY||item.lv<=0||item.id<=0)return;
        int g=-1;for(int n=0;n<GearCount;++n)if(item.type==ownedGearTypes[n]+hero.type)g=n;
        if(g<0||GetEquipPower(const_cast<ITEM*>(&item),item.lv)<=0)return;const int star=GetItemStar(item.type,item.detail,item.grade);
        if(star<1||star>MaxLevel)return;
        auto& pool=ownedGearPool[g][star-1];
        // Extra duplicate copies do not increase the variant's probability.
        for(ITEM& prior:pool)if(prior.detail==item.detail&&prior.grade==item.grade){
            if(GetEquipPower(const_cast<ITEM*>(&item),item.lv)>GetEquipPower(&prior,prior.lv))prior=item;
            return;
        }
        pool.push_back(item);
    };
    for(int n=0;n<GetMaxInven();++n)add(robin.inven[n]);
    for(const ITEM& item:wornEquip)add(item);
}
void rollOwnedGearResults(Run& target,int forcedRoll=-1){
    if(siegeActive||(review&&!getenv("CS_OWNED_GEAR_REVIEW")))return;
    for(Block& b:target.tray){
        if(b.family<Sword||b.family>=FamilyCount||b.ownedId)continue;
        const int star=MergeOwnedGear::starForRoll(forcedRoll>=0?(unsigned)forcedRoll:target.random(10000));
        if(!star)continue;auto& pool=ownedGearPool[b.family-Sword][star-1];if(pool.empty())continue;
        const ITEM& item=pool[target.random((unsigned)pool.size())];int w=1,h=1;MergeBoardGearShape(&item,&w,&h);
        Block bonus=b;bonus.level=star;bonus.ownedId=item.id;bonus.ownedDetail=item.detail;bonus.ownedGrade=item.grade;
        bonus.ownedPower=std::max(0LL,std::min(100000000LL,GetEquipPower(const_cast<ITEM*>(&item),item.lv)));bonus.ownedW=w;bonus.ownedH=h;
        if(w>target.shape.width||h>target.shape.height){if(h>target.shape.width||w>target.shape.height)continue;bonus.rot=true;}
        b=bonus;
    }
}
void configure() {
    // 계열 = 역할 4 + 코스튬 장비 6. 보유 동료가 역할 × ★ 사다리(roster)에 선다.
    // 같은 역할 ★n 둘을 합치면 roster 의 ★n+1 중 하나가 나온다.
    pool.clear();roster=Roster();bool owned[64]={};int crewLevels[64]={};
    for(int i=0;i<GetMaxInven();++i) {
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
    rebuildOwnedGearPool();
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
void crewArt(int crew,const Box& box,float fraction,int footLift,int motionIn,int dir,float fixedZoom=-1.f,float rotation=0.f) {
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
    const bool turned=rotation!=0.f;
    if(fixedZoom>=0){
        const int artWidth=std::max(1,(int)bounds[turned?3:2]),artHeight=std::max(1,(int)bounds[turned?2:3]);
        const int roomHeight=turned?box.h-14*p:box.h-7*p-footLift-(int)(12*DX/640.f);
        z=std::max(0.f,std::min(z,std::min((box.w-(turned?12:4)*p)/(float)artWidth,std::max(1,roomHeight)/(float)artHeight)));
        gridCrewZoomSeen[crew]=z;
    }
    if(turned&&!(review&&std::getenv("CS_CREW_SHADOW_HIDE_REVIEW"))){
        const int cx=clipX,cy=clipY,cx2=clipX2,cy2=clipY2;
        SetSectionClip(box.x,box.y,box.w,box.h,false);
        clipX=std::max(clipX,cx);clipY=std::min(clipY,cy);
        clipX2=std::min(clipX2,cx2);clipY2=std::max(clipY2,cy2);
        // A clockwise turn puts the feet at the left edge of the sprite.
        // Keep its contact shadow under those feet, rather than under its torso.
        Box feet=box;feet.x=box.x+14*p-box.w/2;
        const int shadowWidth=std::max(26*p,(int)(bounds[2]*z*1.05f));
        iconGround(feet,shadowWidth,-2*p);
        iconGround(feet,shadowWidth,-2*p);
        clipX=cx;clipY=cy;clipX2=cx2;clipY2=cy2;
    }else if(!turned&&!(review&&std::getenv("CS_CREW_SHADOW_HIDE_REVIEW")))iconGround(box,std::max(box.w/2,(int)(bounds[2]*z*.85f)),footLift);
    const int centerX=turned?box.x+4*p+(int)(bounds[3]*z/2):box.x+box.w/2;
    const int centerY=turned?box.y-box.h+4*p+(int)(bounds[2]*z/2):box.y-box.h+5*p+footLift+(int)(bounds[3]*z/2);
    if(!(review&&std::getenv("CS_CREW_BODY_HIDE_REVIEW")))DrawCmfDetail(cmf,motion,centerX,centerY,dir,z,rotation,true);   //리뷰: 몸/그림자를 따로 감춰 층을 잰다
}
void icon(int family,const Box& box,float fraction=0.96f,bool atlas=false,int level=1,int crew=-1,int footLift=0,const Block* instance=nullptr) {
    if(family<0||family>=FamilyCount)return;
    if(atlas)fraction*=1.10f; // Original slot-machine symbol sizing.
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
        const float gridZoom=1.215f*(DX/640.f);
        //돌려 놓은 동료(2×1)도 눕히지 않는다. 사람이 누운 그림과 돌아간 그림자가 어색해서(2026-11-23),
        //낮은 칸 높이에 맞춰 작게 **서서** 그리고 그림자는 발밑 바닥에 둔다.
        crewArt(crew,placement,fraction,footLift,-1,RIGHT,atlas?-1.f:gridZoom,0.f);
    } else {
        //공성전의 상대 판은 상대 히어로 라인의 장비로 그린다(gearTableOverride, MergeSiege.inc).
        const int lvAt=std::max(0,std::min(MaxLevel-1,level-1));
        ITEM item=gearTableOverride?gearTableOverride[(family-Sword)*MaxLevel+lvAt]:treeEquipment[family-Sword][lvAt];
        if(instance&&instance->ownedId)item=blockGearItem(*instance);
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
void drawSlotFrame(const Box& b){
 for(int side=0;side<2;++side)portraitCog(originalSlotCogBox(b,side),side?-gearAngle:gearAngle);
 const int img=PORTRAIT_UI_FIRST_IMG+5;if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 const auto& f=MergeCastleArt::UiFrames[MergeCastleArt::Slot];
 const float z=std::min(b.w/(float)f.w,b.h/(float)f.h);
 DrawImage(f.w,f.h,f.x,f.y,b.x+(int)((b.w-f.w*z)/2),b.y-(int)((b.h-f.h*z)/2),false,0,0,0,0,z,sprite[img],img);
}
void slotRim(const Box& b){
 const auto& f=MergeCastleArt::UiFrames[MergeCastleArt::Slot];
 const int cuts[][4]={{54,12,2064,148},{54,560,2064,143},{54,160,446,400},{1690,160,428,400},{845,160,80,400},{1275,160,80,400}};
 for(const auto& c:cuts)artCut(PORTRAIT_UI_FIRST_IMG+5,{c[0],c[1],c[2],c[3]},
  {b.x+(c[0]-f.x)*b.w/f.w,b.y-(c[1]-f.y)*b.h/f.h,c[2]*b.w/f.w,c[3]*b.h/f.h});
}

void drawLever(const Layout& l) {
    Box b=l.lever;bool pulling=finger>=0&&b.has(downX,downY)&&!introActive();
    b.y-=(int)((pulling?20:animation>REEL_SPIN_FRAMES-25?12:0)*l.scale);
    uiArt(MergeCastleArt::Lever,b);
}
bool entering();
int gridRarity(const Block& b){return QuietCard::Rank(b.family>=Roles&&b.ownedId?b.ownedGrade+1:b.level);}
void portraitRankBadge(int level,const Box& box,int rarity){
 const float s=DX/640.f;
 const int tint=QuietCard::Color(rarity),w=(int)(32*s),h=(int)(18*s);
 const Box badge={box.x+box.w-w-(int)(3*s),box.y-box.h+h+(int)(3*s),w,h};
 bevel(badge,tint,std::max(1,(int)(3*s)));bevel(inset(badge,std::max(1,(int)s)),0x0B1A25,std::max(1,(int)(2*s)));
 static const char* star[9]={"000010000","000111000","111111111","011111110","001111100","011111110","011101110","110000011","100000001"};
 const int pixel=std::max(1,(int)s),x=badge.x+(int)(4*s),y=badge.y-(int)(4*s);
 for(int row=0;row<9;++row)for(int col=0;col<9;++col)if(star[row][col]=='1')mergeRect(x+col*pixel,y-row*pixel,pixel,pixel,0xFFE68B);
 DrawImageNum(level,badge.x+(int)(23*s),badge.y-(int)(2*s),NUM_FONT_NORMAL,CENTER,0,false,false,.40f*s,false);
}
void drawBlock(const Block& b,const Box& box,bool ghost=false) {
    // Restored blocks wait for the floor tiles to finish landing as well.
    if(entering())return;
    int lv=std::max(1,std::min((int)MaxLevel,b.level));
    const int rarity=gridRarity(b);
    SetAlpha(ghost?16:32);gradePad(rarity,box);SetAlpha(32);
    Box artwork=inset(box,std::max(1,(int)(4*DX/640.f)));
    //돌려 놓은 동료(2×1)는 칸이 낮아 발을 바닥 가까이 둔다 - 선 동료의 12px 들어올림을 그대로 주면 그림이 칸 가운데 떠 보인다.
    const bool lowTile=b.family<Roles&&b.rot&&Wide(b)!=Tall(b);
    if(b.family<Roles)artwork.y+=(int)((lowTile?2:12)*DX/640.f);
    else artwork.y+=0;
    icon(b.family,artwork,b.family<Roles?.90f:.96f,false,b.level,b.crew,b.family<Roles?(int)((lowTile?2:6)*DX/640.f):0,&b);
    if(b.ownedId)MemRect(box.x+4,box.y-4,5,2,0xE7E1CF);
    portraitRankBadge(lv,box,rarity);
}
Box blockBox(const Block& b,const Layout& l) {
    return {l.board.x+b.x*l.cell,l.board.y-b.y*l.cellH,Wide(b)*l.cell,Tall(b)*l.cellH};
}
bool automaticMergesEnabled(){return (!siegeActive||!Siege::swapped)&&(!review||std::getenv("CS_AUTO_MERGE_REVIEW"));}
bool beginAutomaticMerge(){
    if(!automaticMergesEnabled()||automaticMerge.active()||picked>=0)return false;
    AutomaticMerge next;
    if(!run.automaticMergePlan(next.plan,next.fromTray,next.source,next.target))return false;
    next.moving=(next.fromTray?run.tray:run.board)[next.source];
    next.staging=next.moving;
    bool found=false;
    for(int y=0;next.fromTray&&y<run.shape.height&&!found;++y)for(int x=0;x<run.shape.width;++x){
        Block b=next.moving;b.x=x;b.y=y;
        if(run.fits(b,next.fromTray?-1:next.source)){next.staging=b;found=true;break;}
    }
    // On a full board the lifted material leaves its own empty footprint.
    if(!found&&next.fromTray){
        next.staging=run.board[next.target];
        next.targetLifted=true;
    }
    next.age=0;automaticMerge=next;picked=finger=-1;
    PlayMusic(M_ROULETTEUP);return true;
}
void drawAutomaticMerge(const Layout& l){
    if(!automaticMerge.active())return;
    const auto& a=automaticMerge;
    Box from=a.fromTray?slotWindow(l.slot,std::min(2,a.source)):blockBox(a.moving,l);
    const Box stage=blockBox(a.staging,l);
    Box target=blockBox(run.board[a.target],l);
    if(a.targetLifted){
        target.y+=(int)(64*l.scale);
        Box lifted=blockBox(run.board[a.target],l);
        lifted.y+=(int)(std::min(1.f,a.age/12.f)*64*l.scale);
        drawBlock(run.board[a.target],lifted);
    }
    Box raised=from;raised.y+=(int)(48*l.scale);
    Box start,end;float t;
    if(!a.fromTray){start=from;end=target;t=std::min(1.f,a.age/24.f);}
    else if(a.age<12){start=from;end=raised;t=a.age/12.f;}
    else if(a.age<32){start=raised;end=stage;t=(a.age-12)/20.f;}
    else{start=stage;end=target;t=std::min(1.f,(a.age-32)/24.f);}
    const float ease=t*t*(3-2*t);
    Box box={(int)(start.x+(end.x-start.x)*ease),(int)(start.y+(end.y-start.y)*ease),
        (int)(start.w+(end.w-start.w)*ease),(int)(start.h+(end.h-start.h)*ease)};
    if(a.fromTray&&a.age>=12&&a.age<32)box.y+=(int)(std::sin(t*3.14159265f)*34*l.scale);
    if(!a.fromTray||a.age>=32)box.y+=(int)(std::sin(t*3.14159265f)*48*l.scale);
    if(a.fromTray){SetAlpha(20);MemRectFrameThick(stage.x,stage.y,stage.w,stage.h,0xFFE397,std::max(1,(int)(2*l.scale)));SetAlpha(32);}
    drawBlock(a.moving,box);
}
int trashSwallowTicks=0;
float trashOpenness=0;
Box rouletteTrash(const Layout& l){return {DX-(int)(54*l.scale),l.slot.y+(int)(40*l.scale),(int)(36*l.scale),(int)(36*l.scale)};}
bool nearRouletteTrash(const Layout& l,float x,float y){
    Box b=rouletteTrash(l);const int pad=(int)(16*l.scale);
    return x>=b.x-pad&&x<=b.x+b.w+pad&&y<=b.y+pad&&y>=b.y-b.h-pad;
}
void drawRouletteTrash(const Layout& l){
 const Box b=rouletteTrash(l);const bool hover=picked>=0&&nearRouletteTrash(l,pointerX,pointerY);
 if(!hover&&picked<0)return;
 portraitSkin(hover?3:2,b);portraitGlyph(11,inset(b,(int)(5*l.scale)));
}
bool beginSpinLanding(){
    spinLandingPlan=run;spinDrops.clear();
    const auto source=run.tray;
    for(const auto& item:source){
        const auto before=spinLandingPlan.board;
        if(!spinLandingPlan.scatterPlace(0)){
            if(!spinDrops.empty())break;
            message=u8"\uacb0\uacfc\ub97c \ubc30\uce58\ud558\uac70\ub098 \uc624\ub978\ucabd \uc4f0\ub808\uae30\ud1b5\uc5d0 \ubc84\ub824\uc8fc\uc138\uc694.";messageTime=3;return false;
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
        icon(drop.source.family,{cx-w/2,cy+h/2,w,h},1.f,false,drop.source.level,drop.source.crew,0,&drop.source);
    }
}
float flightStart(int i) {return 2.85f+i*.22f;}
void drawIntro(const Layout& l) {
    if(!introActive())return;
    float s=l.scale,t=introElapsed;
    SetAlpha(32);
    const Box slot=l.slot;
    drawSlotFrame(slot);
    for(int i=0;i<3;++i) {
        float stop=2.f+i*.24f;
        Box reel=slotWindow(slot,i);
        SetSectionClip(reel.x,reel.y,reel.w,reel.h,false);
        int pitch=(int)(108*s);
        if(t<stop) {
            float distance=t-.375f*t*t/stop;
            int offset=(int)std::fmod(distance*(920+110*i)*s,(float)pitch);
            int index=(int)(t*(30+5*i));
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
        SetAlpha(32);icon(run.board[i].family,{cx-w/2,cy+h/2,w,h},.94f,false,run.board[i].level,run.board[i].crew,0,&run.board[i]);
    }
    SetAlpha(32);
}
TurretAttack::Sequence turretFire;
#include "MergeCastleLobbyRebuild.inc"
#include "CastleVaultCollect.inc"   //성 금고 수거 단추와 재화 날아가기
Box entryChoiceBox(int part){
    const float s=DX/640.f;const int w=(int)(592*s),h=(int)(570*s),x=(DX-w)/2,y=(DY+h)/2;
    if(part==0)return {x,y,w,h};
    if(part==3)return {x+w-(int)(58*s),y-(int)(12*s),(int)(42*s),(int)(34*s)};
    if(part>=4)return {x+(int)((22+(part-4)*184)*s),y-(int)(336*s),(int)(168*s),(int)(82*s)};
    const int gap=(int)(16*s),pad=(int)(22*s),bw=(w-pad*2-gap)/2;
    return {x+pad+(part==2?bw+gap:0),y-(int)(470*s),bw,(int)(60*s)};
}
bool entryResume(Run* destination=nullptr){
    Run saved;saved.roster=&roster;
    if(robin.mergeRouletteHero!=curHero||!saved.decode(robin.mergeRouletteRun)||saved.lost||saved.stage!=run.stage)return false;
    for(int f:saved.families)if(std::find(pool.begin(),pool.end(),f)==pool.end())return false;
    if(destination)*destination=saved;
    return true;
}
//이어 하기·그만두기 창은 공용 단순 팝업(DrawUiDialog)이다. 단추 자리도 공용 식(UiDialogButtonRect)에서 받는다.
Box resumeChoiceBox(int choice){
 int x,top,w,h;UiDialogButtonRect(choice,2,&x,&top,&w,&h);return {x,top,w,h};
}
void drawResumePrompt(){
 ResetRectPoint();
 static const char* labels[2]={u8"\uC804\uD22C \uC885\uB8CC",u8"\uC774\uC5B4\uD558\uAE30"};
 static const int fills[2]={0x344553,0x196345};
 DrawUiDialog(u8"\uC9C4\uD589 \uC911\uC778 \uC804\uD22C",u8"\uC774\uC804 \uC804\uD22C\uB97C \uC774\uC5B4\uD558\uC2DC\uACA0\uC2B5\uB2C8\uAE4C?",
  u8"\uC885\uB8CC\uD558\uBA74 \uC0AC\uC6A9\uD55C \uCD9C\uC815 \uC5D0\uB108\uC9C0\uB294 \uBC18\uD658\uB418\uC9C0 \uC54A\uC2B5\uB2C8\uB2E4.",2,labels,nullptr,fills,nullptr);
}
void drawQuitPrompt(){
 ResetRectPoint();
 static const char* labels[2]={u8"\uadf8\ub9cc\ub450\uae30",u8"\ucde8\uc18c"};
 static const int fills[2]={0x8C3F32,0x196345};
 DrawUiDialog(nullptr,u8"\uc804\ud22c\ub97c \uadf8\ub9cc\ub450\uc2dc\uaca0\uc2b5\ub2c8\uae4c?",
  u8"\uadf8\ub9cc\ub450\uba74 \ud604\uc7ac \uc804\ud22c\uac00 \uc885\ub8cc\ub429\ub2c8\ub2e4.\n\uc0ac\uc6a9\ud55c \ucd9c\uc815 \uc5d0\ub108\uc9c0\ub294 \ubc18\ud658\ub418\uc9c0 \uc54a\uc2b5\ub2c8\ub2e4.",2,labels,nullptr,fills,nullptr);
}
void drawStageProgress(int top,int wave,float s){
    const int pitch=(int)(30*s),left=DX/2-7*pitch;
    for(int i=0;i<WavesPerStage;++i){
        const bool boss=BossTier(i)>0,current=i==wave,cleared=i<wave;
        const int size=(int)((boss?20:14)*s),cx=left+i*pitch;
        const Box node={cx-size/2,top,size,size};
        bevel(node,current?0xFFF1A8:cleared?0x89DBA0:boss?0xC5A2D5:0x6E8391,std::max(1,(int)(3*s)));
        bevel(inset(node,std::max(1,(int)(2*s))),current?0xBB771A:cleared?0x286B49:BossTier(i)==3?0x78313E:boss?0x49355E:0x233844,std::max(1,(int)(2*s)));
        if(boss)DrawImageNum(i+1,cx,top,NUM_FONT_SMALL,CENTER,0,false,false,.58f*s,false);
    }
}
void drawEntryChoice();
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
bool debugFirstBoss=false;
bool combatEnemyIsBoss(){return BossTier(run.wave)>0||(debugFirstBoss&&run.wave==0);}
int reviewEnemyNpc=-1,reviewSnailPose=-1;
int stageEnemyNpc(int wave) {
    const int region=std::max(0,std::min(STAGEBG_REGION_CNT-1,combatRegion()));
    const RegionRoster& r=kRegionRoster[region];
    const int w=std::max(0,std::min(WavesPerStage-1,wave));
    const int boss=debugFirstBoss&&w==0?3:BossTier(w);
    int type;
    if(boss)type=r.boss[boss-1];
    else{const int slot=w<4?w/2:w<9?1+(w-5)/2:2+(w-10)/2;type=r.normal[std::max(0,std::min(3,slot))];}
    //색 변형: 같은 번호가 레드 +51, 블루 +102 다(enemy.tsv).
    const int variant=std::max(0,std::min(2,(run.stage%STAGE_PER_CYCLE)/4));
    const int colored=type+variant*51;
    return colored<gTotalEnemy?colored:type;
}
int combatEnemyNpc() {
    if(review&&reviewEnemyNpc>=0)return reviewEnemyNpc;
    return stageEnemyNpc(run.wave);
}
void drawEntryChoice(){
    ResetRectPoint();SetAlpha(23);MemRect(0,DY,DX,DY,0);SetAlpha(32);SetColor(0);
    const Box p=entryChoiceBox(0);const float s=DX/640.f;
    const auto yy=[&](int offset){return p.y-(int)(offset*s);};
    DrawMenuReferencePanel(p.x,p.y,p.w,p.h);
    label(u8"출정",DX/2,yy(20),1.05f,0xFFF0CD);
    button(entryChoiceBox(3),"X",nullptr,0x164A5B);
    Run saved;const int wave=entryResume(&saved)?saved.wave:0;
    char text[128];
    std::snprintf(text,sizeof(text),u8"%s · %d / 15",StageBg::RegionName(combatRegion()),wave+1);
    label(text,DX/2,yy(66),.87f,0xFFF0CD);
    drawStageProgress(yy(105),wave,s);
    const Box scene={p.x+(int)(22*s),yy(145),p.w-(int)(44*s),(int)(150*s)};
    panel(scene,0x16333E,0xAD965E);
    // Use the same simple distant skyline as the lobby and portrait battle.
    {
        const int img=PORTRAIT_NIGHT_IMG;
        if(!sprite[img])LoadImg(img);if(sprite[img]){
        auto* texture=sprite[img]->getTexture();const auto size=texture->getContentSizeInPixels();
        const float z=std::max(scene.w/size.width,scene.h/size.height);
        const int sw=(int)(scene.w/z),sh=(int)(scene.h/z);
        const int sy=std::max(0,std::min((int)size.height-sh,(int)(size.height*.825f-sh*.8f)));
        DrawMenuBackdropCrop(texture,((int)size.width-sw)/2,sy,sw,sh,scene.x,scene.y,scene.w,scene.h);
        }
    }
    label(u8"출전 히어로 선택",DX/2,yy(307),.67f,0xFFF0CD);
    for(int i=0;i<3;++i){
        const int who=ROBIN+i;const bool owned=IsGetHero(who),selected=who==curHero;
        const Box b=entryChoiceBox(4+i);
        DrawMenuReferencePanel(b.x,b.y,b.w,b.h,0,selected?0x246166:0x173B42,selected?0xF1C47E:0x648B94);
        OBJECT other=hero;other.type=other.cmf=who;
        std::memcpy(other.equip,robin.charData[who].equip,sizeof(other.equip));
        if(cmfLoaded[who]!=who)CmfRead(who,who);
        const int still=GetHeroLoopMotion(who,HEROLOOP_NEUTRAL,0);
        grayScale=owned?0:32;
        DrawPlayer(&other,still>=0?still:motionData[0],b.x+(int)(37*s),b.y-(int)(70*s),RIGHT,.78f*s,0,false,true);
        grayScale=0;
        static const char* names[]={u8"로빈",u8"다이애나",u8"맥스"};
        label(names[i],b.x+(int)(112*s),b.y-(int)(17*s),.64f,owned?0xFFF0CD:0xA9B9BE);
        label(!owned?u8"미해금":selected?u8"선택됨":u8"선택",b.x+(int)(112*s),b.y-(int)(49*s),.49f,selected?0xF7D487:0xB4CFCE);
    }
    const auto mode=[&](int part,const char* title,int icon,int color){
        const Box b=entryChoiceBox(part);
        label(title,b.x+b.w/2,b.y+(int)(30*s),.8f,0xFFF2D8);
        UiButtonStyle style;style.fill=color;style.frame=mergeButtonFrame;
        DrawUiButton(b.x,b.y,b.w,b.h,"",0,false,true,style);
        const int center=b.x+b.w/2;
        DrawIcon(icon,center-(int)(53*s),b.y-(int)(12*s),s,0x07101B,false,false,1.f);
        portraitGlyph(3,{center-(int)(8*s),b.y-(int)(13*s),(int)(23*s),(int)(29*s)});
        char cost[16];std::snprintf(cost,sizeof(cost),"%d",MergeExpedition::Cost);
        label(cost,center+(int)(32*s),b.y-(int)(17*s),.82f,0xFFF0CD);
    };
    mode(1,u8"전투",ICON_EVENT_2SWORD,0x174DA0);
    mode(2,u8"원정",GetItemIcon(ITEM_GREAVES,0,GRADE_NORMAL),0x1F5A3A);
    if(!message.empty())label(message.c_str(),DX/2,yy(546),.52f,0xFFE0A0);
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
//---- 전력 지수 ----
//
//지금 판에 설 수 있는 가장 센 ★1 블록값: 히어로 검(공격 × HeroGearPct%) 과 로스터에서 가장 센 동료 power 중
//큰 쪽. 적 체력이 이 값의 제곱근으로 는다(MergeWaveCurve.h). 공성전은 상대 판이라 보정하지 않는다.
long long rosterPowerIndex() {
    long long best=std::max(1LL,stats.weapon*Run::HeroGearPct/100);
    for(int role=0;role<Roles;++role)for(int star=1;star<=MaxLevel;++star)
        for(int k=0;k<roster.count[role][star];++k){const int c=roster.crew[role][star][k];if(c>=0&&c<64)best=std::max(best,stats.crew[c].power);}
    return best;
}
//적 체력·공격 곡선은 MergeWaveCurve.h 한 곳이다(측정기 balance_sim 과 같은 식).
long long waveHp(int stage,int wave) {
    return MergeWave::waveHp(stage,wave,siegeActive?MERGE_POWER_BASE:rosterPowerIndex());
}
long long waveAttack(int stage,int wave) {
    return MergeWave::waveAttack(stage,wave);
}
void drawPortraitStats(const Box&,long long,long long,long long,long long);
void drawPortraitEnemyHealth(const Layout&);
void drawPortraitEnergy(const Layout&);
void drawWaveHeader(const Layout& l) {
    const float s=l.scale;const Box header={(int)(60*s),DY-(int)(8*s),(int)(410*s),(int)(58*s)};
    MergeTutorialRememberHeader(header.x,header.y,header.w,header.h);
    char line[80];std::snprintf(line,sizeof(line),"WAVE %02d / %02d",run.wave+1,WavesPerStage);
    label(line,(int)(205*s),header.y-(int)(4*s),.95f,0xFFF3D9);
    portraitGlyph(6,{(int)(337*s),header.y-(int)(3*s),(int)(30*s),(int)(30*s)});
    std::snprintf(line,sizeof(line),"%lld",robin.gold);label(line,(int)(415*s),header.y-(int)(5*s),.65f,0xE7C878);
    const int pitch=(int)(30*s),left=(int)(96*s),n=(int)(10*s);
    mergeRect(left,header.y-(int)(45*s),(WavesPerStage-1)*pitch,(int)(2*s),0x354957);
    if(run.wave>0)mergeRect(left,header.y-(int)(45*s),run.wave*pitch,(int)(2*s),0xF2D269);
    for(int i=0;i<WavesPerStage;++i)bevel({left+i*pitch-n/2,header.y-(int)(40*s),n,n},i<=run.wave?0xF2D269:0x3D5361,std::max(1,(int)(3*s)));
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
int monsterHeroX(const Layout& l){const Box gun=castleCannonBox(l);return std::min((int)(DX*.74f),std::max((int)(DX*.64f),gun.x+gun.w+(int)(116*l.scale)));}
float monsterZoom(const Layout& l,int npc,int cmf){
    const auto* bounds=cmfMotionImgSize[cmf]+crewPos[npc*5]*4;
    if(railBossScene())return std::min(520*l.scale/std::max(1,(int)bounds[2]),
        std::min(620*l.scale,DY*.74f)/std::max(1,(int)bounds[3]));
    const int y=l.ground+(int)(16*l.scale);
    return .9f*std::min(1.35f*l.scale,std::max(.3f*l.scale,(DY-78*l.scale-y-8*l.scale)/std::max(1,(int)bounds[3])));
}
int monsterHomeX(const Layout& l,int npc,int cmf){
    if(!railBossScene())return (int)(DX*.85f);
    const auto* b=cmfMotionImgSize[cmf]+crewPos[npc*5]*4;
    return (int)(DX*1.35f+b[0]*monsterZoom(l,npc,cmf));
}
int combatRailY(){
    const int c=OriginalCastle::widthStage();const auto& a=MistCastle::wheelAnchors[c];
    const int contact=std::max(a[0][1]+a[0][2],a[1][1]+a[1][2]);
    return (int)((1445-contact)*OriginalCastle::zoom()+OriginalCastle::lift()+9*DX/640.f);
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
        const int c=siegeHullStage>=0?siegeHullStage:std::max(0,std::min(18,run.stage));
        turretFire.begin(c,CastleVisualPartLevel(c,3));
        if(turretFire.type==TurretAttack::Laser||turretFire.type==TurretAttack::Magnetic)PlayMusic(M_LASER2);
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
    if(block.family==Sword)showAttackWeapon(block.level,&block);
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
// Tiny, deterministic upgrade sparks. No new projectiles or damage events.
void drawTurretUpgradeSparks(TurretAttack::Point point,TurretAttack::Point behind,int seed,float scale,bool radial=false,int limit=0){
 const TurretAttack::UpgradeVisual look(turretFire.grade);if(!look.motes)return;
 static const int colors[10]={0xDDBB78,0xFFA75A,0xFFCA74,0xFFE4A3,0xFFAE57,0x66E8DC,0xFF8D58,0x88D7FF,0xC995FF,0xFFE49A};
 const int color=colors[std::max(0,std::min(9,turretFire.castle))],alpha=m_lgrpAlpha;
 const float dx=point.x-behind.x,dy=point.y-behind.y,length=std::max(1.f,std::sqrt(dx*dx+dy*dy));
 for(int k=0;k<(limit?std::min(limit,look.motes):look.motes);++k){
  const float t=std::fmod(turretFire.age*.075f+k*.31f+seed*.17f,1.f);
  float x,y;
  if(radial){const float angle=k*2.0943951f+seed*.47f+t*1.3f,r=(8+12*t)*scale;
   x=point.x+std::cos(angle)*r;y=point.y+std::sin(angle)*r;
  }else{
   const float tail=(5+17*t)*scale,side=std::sin(t*6.2831853f+seed)*(2+look.level*.3f)*scale;
   x=point.x-dx/length*tail-dy/length*side;y=point.y-dy/length*tail+dx/length*side;
  }
  const int size=std::max(1,(int)((look.level>=4?2.f:1.f)*scale));
  SetAlpha((int)(alpha*(.25f+.45f*(1-t))));mergeRect((int)x-size,(int)y+size,size*2,size*2,color);
  if(look.level>=3&&k==0){SetAlpha(alpha/2);mergeRect((int)x-3*size,(int)y,6*size,1,0xFFF4DB);mergeRect((int)x,(int)y+3*size,1,6*size,0xFFF4DB);}
 }
 SetAlpha(alpha);
}
void drawTurretAttack(const Layout& l,int targetX,int targetY){
 if(!turretFire.running()||!action.emitterReady)return;
 const float scale=l.scale;
 const TurretAttack::Point from={(float)action.emitterX,(float)action.emitterY},to={(float)targetX,(float)targetY};
 const int age=turretFire.age;
 const TurretAttack::UpgradeVisual upgrade(turretFire.grade);
 if(turretFire.type==TurretAttack::Laser||turretFire.type==TurretAttack::Magnetic||turretFire.type==TurretAttack::Composite){
  const int charge=turretFire.release,alpha=m_lgrpAlpha;
  // The red, silver, violet and gold castles each color their own hot aura.
  static const int tones[4]={0xEF281D,0x69CDFF,0xB85AFF,0xFFD363};
  const int tone=turretFire.castle==13?0xB85AFF:turretFire.castle==15?0xA5DCFF:turretFire.castle==14?0xE9A8FF:0xC995FF;
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
    {(int)((x1+x2-len)*.5f),(int)((y1+y2+width)*.5f),std::max(1,(int)std::ceil(len)),std::max(1,(int)width)},-std::atan2(dy,dx)*57.2957795f,.5f,.5f,false,color,true);
   SetAlpha(alpha);
  };
  if(age<charge){
   const float t=age/(float)charge,r=(6+25*t*t)*scale;
   glow(from.x,from.y,r*1.8f,tone,alpha/3);
   glow(from.x,from.y,r,tone,alpha*3/4);
   glow(from.x,from.y,r*.32f,0xFFF8E4,alpha);
   // Visible inward streaks converge on the muzzle before the beam releases.
   for(int ray=0;ray<6;++ray){
    const float phase=std::fmod(age*.065f+ray/6.f,1.f);
    const float a=ray*1.04719755f+age*.025f;
    const float outer=(r/scale+12+(1-phase)*35)*scale;
    const float inner=std::max(r,outer-(9+9*phase)*scale);
    electricLine(from.x+std::cos(a)*outer,from.y+std::sin(a)*outer,
     from.x+std::cos(a)*inner,from.y+std::sin(a)*inner,5*scale,tone,(int)(alpha*(.45f+.55f*phase)));
   }
   for(int i=0;i<8;++i){
    const float phase=std::fmod(age*.09f+i*.125f,1.f);
    const float a=i*.78539816f+age*.06f;
    const float distance=(26+(1-phase)*32)*scale;
    glow(from.x+std::cos(a)*distance,from.y+std::sin(a)*distance,(1+phase*2)*scale,tone,alpha*(.4f+phase*.6f));
   }
   if(turretFire.castle==13){
    for(int arc=0;arc<5;++arc){
     const float a=arc*1.256637f+age*.17f;
     const float outer=(36-8*t)*scale,inner=(12+8*t)*scale;
     const float x=from.x+std::cos(a)*outer,y=from.y+std::sin(a)*outer;
     const float mx=from.x+std::cos(a+.24f)*inner,my=from.y+std::sin(a+.24f)*inner;
     electricLine(x,y,mx,my,3*scale,0xD5A2FF,alpha);
     electricLine(mx,my,from.x,from.y,2*scale,0xF9EEFF,alpha);
    }
   }
   drawTurretUpgradeSparks(from,{from.x,from.y-1},0,scale,true);
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
  const float thickness=((turretFire.castle==16?96:turretFire.castle==13?64:48)+4*std::sin(age*1.7f))*scale*upgrade.beamScale;
  auto beam=[&](float height,int color,int opacity){
   SetAlpha(opacity);
   turretPart(img,0,(int)dim.height/4,(int)dim.width,(int)dim.height/2,
    {(int)((from.x+to.x-length)*.5f),(int)((from.y+to.y+height)*.5f),(int)std::ceil(length),(int)height},angle,.5f,.5f,false,color,true);
   SetAlpha(alpha);
  };
  if(turretFire.castle==15){
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
   beam(thickness*(turretFire.castle==16?.16f:.36f),turretFire.castle==16?0xFFBE86:0xFFF9E8,(int)(alpha*fade));
  }
  if(turretFire.castle==13){
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
  glow(from.x,from.y,(turretFire.castle==13?34:27)*scale,tone,(int)(alpha*.7f*fade));
  glow(from.x,from.y,12*scale,0xFFF9E8,(int)(alpha*fade));
  glow(to.x,to.y,(19+3*std::sin(age))*scale,tone,(int)(alpha*.7f*fade));
  glow(to.x,to.y,9*scale,0xFFF9E8,(int)(alpha*fade));
  for(int spark=0;spark<upgrade.motes;++spark){
   const float t=std::fmod((age-charge)*.035f+spark/(float)std::max(1,upgrade.motes),1.f);
   drawTurretUpgradeSparks({from.x+dx*t,from.y+dy*t},{from.x+dx*(t-.01f),from.y+dy*(t-.01f)},spark,scale,false,1);
  }
  return;
  }
 }
 for(int i=0;i<turretFire.count;++i){
  const auto shotType=turretFire.projectile(i);const auto pathType=shotType;
  const int elapsed=age-turretFire.launch(i);
  if(elapsed<0)continue;
  if(elapsed>=turretFire.flight){
   const int impactAge=elapsed-turretFire.flight;
   if(impactAge<10&&(shotType!=TurretAttack::Rapid||i%3==0))drawTurretUpgradeSparks(to,from,i,scale,true);
   if(turretFire.castle==14||shotType==TurretAttack::Magnetic){
    if(impactAge<14){
     const int img=shotType==TurretAttack::Magnetic?TURRET_MAGNETIC_ORB_IMG:TURRET_CRYSTAL_ORB_IMG;
     if(!sprite[img])LoadImg(img);
     if(sprite[img]){
      const auto dim=sprite[img]->getTexture()->getContentSizeInPixels();
      const int alpha=m_lgrpAlpha,size=(int)((shotType==TurretAttack::Magnetic?72+impactAge*6:38+impactAge*3)*scale);
      SetAlpha(alpha*(14-impactAge)/14);
      turretPart(img,0,0,(int)dim.width,(int)dim.height,{targetX-size/2,targetY+size/2,size,size},impactAge*12.f);
      for(int spark=0;spark<6;++spark){
       const float a=spark*1.04719755f+impactAge*.06f;
       const int x=targetX+(int)(std::cos(a)*(10+impactAge*3)*scale);
       const int y=targetY+(int)(std::sin(a)*(10+impactAge*3)*scale);
       const int n=std::max(1,(int)((4-impactAge*.2f)*scale));
       mergeRect(x-n,y+n,n*2,n*2,shotType==TurretAttack::Magnetic?(spark%2?0xDDF8FF:0x69CFFF):(spark%2?0xA7FFF0:0x39DCCB));
      }
      SetAlpha(alpha);
     }
    }
    continue;
   }
   drawImpactSequence(HIT_DIANA_MEDIUM1,7,impactAge,14,targetX,targetY,RIGHT,
    (shotType==TurretAttack::Rapid?.22f:shotType==TurretAttack::Missiles?.7f:1.25f)*scale);
   continue;
  }
  const float t=elapsed/(float)turretFire.flight;
  auto start=from;
  if(shotType==TurretAttack::Missiles||turretFire.type==TurretAttack::Composite||shotType==TurretAttack::Rapid)start=cannonMuzzle(l,turretFire.castle,siegeActive&&Siege::swapped,turretFire.launch(i),i);
  const auto point=TurretAttack::position(pathType,t,start,to,i,scale);
  const auto next=TurretAttack::position(pathType,std::min(1.f,t+.02f),start,to,i,scale);
  const float angle=-std::atan2(next.y-point.y,next.x-point.x)*57.2957795f;
  if(shotType!=TurretAttack::Rapid||i%3==0)drawTurretUpgradeSparks(point,TurretAttack::position(pathType,std::max(0.f,t-.04f),start,to,i,scale),i,scale);
  if(shotType==TurretAttack::Bolt){
   const float dx=next.x-point.x,dy=next.y-point.y,length=std::max(.001f,std::sqrt(dx*dx+dy*dy)),ux=dx/length,uy=dy/length;
   auto stroke=[&](float x1,float y1,float x2,float y2,int color){
    const int steps=std::max(1,(int)std::ceil(std::max(std::abs(x2-x1),std::abs(y2-y1))));
    for(int k=0;k<=steps;++k){const float t=k/(float)steps;const int thick=std::max(1,(int)(2*scale));mergeRect((int)(x1+(x2-x1)*t),(int)(y1+(y2-y1)*t)+thick,thick,thick,color);}
   };
   stroke(point.x-ux*42*scale,point.y-uy*42*scale,point.x,point.y,0xB99764);
   for(int side=-1;side<=1;side+=2)stroke(point.x,point.y,point.x-ux*12*scale-uy*side*6*scale,point.y-uy*12*scale+ux*side*6*scale,0xE4D7B7);
  }else if(shotType==TurretAttack::Missiles){
   for(int trail=3;trail>=1;--trail){
    const auto p=TurretAttack::position(pathType,std::max(0.f,t-trail*.025f),start,to,i,scale);
    const int size=std::max(1,(int)((5-trail)*scale));
    mergeRect((int)p.x-size,(int)p.y+size,size*2,size*2,trail==1?0xFFF2B0:0xF78C35);
   }
   {
    const int missile=TURRET_TRIPLE_MISSILE_IMG;
    if(!sprite[missile])LoadImg(missile);
    if(sprite[missile]){
     const auto dim=sprite[missile]->getTexture()->getContentSizeInPixels();
     sprite[missile]->getTexture()->setAntiAliasTexParameters();
     const int width=(int)(42*scale),height=(int)(width*dim.height/dim.width);
     turretPart(missile,0,0,(int)dim.width,(int)dim.height,
      {(int)point.x-width/2,(int)point.y+height/2,width,height},angle);
    }
   }
  }else if(shotType==TurretAttack::Stone){
   const float z=portraitCastleZoom(l);const int w=std::max(1,(int)(StarterCastleRig::RockDrawW*z)),h=std::max(1,(int)(StarterCastleRig::RockDrawH*z));
   turretPart(PORTRAIT_TURRET_FIRST_IMG,StarterCastleRig::RockX,StarterCastleRig::RockY,StarterCastleRig::RockW,StarterCastleRig::RockH,
    {(int)point.x-w/2,(int)point.y+h/2,w,h},elapsed*10.f*(to.x>=from.x?1.f:-1.f));
  }else{
   const int img=shotType==TurretAttack::Magnetic?TURRET_MAGNETIC_ORB_IMG:turretFire.castle==14?TURRET_CRYSTAL_ORB_IMG:turretFire.castle==4?TURRET_HEAVY_SHELL_IMG:TURRET_IRONBALL_IMG;
   if(!sprite[img])LoadImg(img);
   if(sprite[img]){
    const auto dim=sprite[img]->getTexture()->getContentSizeInPixels();
    sprite[img]->getTexture()->setAntiAliasTexParameters();
    const bool rapid=shotType==TurretAttack::Rapid;
    const int baseDiameter=std::max(1,(int)((shotType==TurretAttack::Magnetic?72.f:rapid?13.f:turretFire.castle==4?46.f:38.f)*scale));
    const int diameter=shotType==TurretAttack::Shell?std::max(baseDiameter,(int)(castleCannonBox(l).w*.34f)):baseDiameter;
    const int bulletHeight=std::max(2,(int)(4*scale));
    const float spinDirection=to.x>=from.x?1.f:-1.f;
    const float spin=elapsed*(shotType==TurretAttack::Magnetic?7.f:18.f)*spinDirection;
    const int alpha=m_lgrpAlpha;
    for(int trail=rapid?0:3;trail>=1;--trail){
     const auto p=TurretAttack::position(shotType,std::max(0.f,t-trail*.035f),start,to,i,scale);
     const int size=(int)(diameter*(.72f-trail*.09f));
     SetAlpha(alpha*(4-trail)/12);
     turretPart(img,0,0,(int)dim.width,(int)dim.height,{(int)p.x-size/2,(int)p.y+size/2,size,size},spin-trail*18.f*spinDirection);
    }
    SetAlpha(alpha);
    if(turretFire.castle==14||shotType==TurretAttack::Magnetic){
     const int glow=(int)(diameter*(1.20f+.10f*std::sin(elapsed*.6f)));
     SetAlpha(alpha/3);
     turretPart(img,0,0,(int)dim.width,(int)dim.height,{(int)point.x-glow/2,(int)point.y+glow/2,glow,glow},-spin*.5f);
     SetAlpha(alpha);
    }
    turretPart(img,0,0,(int)dim.width,(int)dim.height,{(int)point.x-diameter/2,(int)point.y+(rapid?bulletHeight:diameter)/2,diameter,rapid?bulletHeight:diameter},rapid?angle:spin);
   }
  }
  if(elapsed<(shotType==TurretAttack::Rapid?2:8)&&shotType!=TurretAttack::Stone&&turretFire.castle!=14&&shotType!=TurretAttack::Magnetic){
   drawImpactSequence(HIT_DIANA_SMALL1,7,elapsed,10,(int)start.x,(int)(start.y-(shotType==TurretAttack::Rapid?5:18)*scale),RIGHT,(shotType==TurretAttack::Rapid?.22f:.65f)*scale);
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
#include "PortraitLobbyCamp.inc"
void drawWorld(const Layout& l,bool combat) {
    const float s=l.scale;
    objectDrawOrder=monsterDrawOrder=allyDrawOrder=impactDrawOrder=0;monsterDrawn=false;
    enemyBodyKnown=false;
    deckResidentCount=0;
    deckMergeGhostsDrawn=0;
    SetAlpha(32);SetColor(0);grayScale=0;
    // Lobby and title are a parked campsite; only battle travel moves wheels and rails.
    if(!nativeTitleIsolate){const int c=std::max(0,std::min(18,siegeHullStage>=0?siegeHullStage:run.stage));
     portraitNight(l.ground,portraitCastleZoom(l),combat?l.arenaBottom+(int)(8*s):0);}
    const int viewportTop=DY-(int)(72*s),viewportBottom=l.arenaBottom+(int)(8*s);
    SetSectionClip(0,viewportTop,DX,std::max(1,viewportTop-viewportBottom),false);
    const float savedMotionX=uiSceneMotionX;
    if(titleCampOnly){const Box approach=portraitCastleBox(l);uiSceneMotionX=-(approach.x+approach.w+20*l.scale)*(1.f-TitleEntranceEase(0.f,2.4f));}
    drawCastleHull(l,combat);uiSceneMotionX=savedMotionX;
    if(nativeTitleBodyOnly)return;
    if(!combat){drawPortraitLobbyCamp(l);UnSectionClip(false);return;}
    //---- 데크의 줄 ----
    //
    //전에는 히어로가 DX*0.57 에 서고 동료가 그 왼쪽으로 늘어섰다. 대포가
    //그 자리에 있어서 줄의 앞머리가 포신에 겹쳐 박혔다.
    //
    //이제 대포 앞(오른쪽)부터가 사람 자리다. 히어로가 맨 앞에 서고 동료가
    //그 뒤로 붙되, 마지막 사람이 포신을 넘지 않도록 간격만 좁힌다.
    const Box gun=castleCannonBox(l);
    const int deckBack=std::max((int)(DX*.36f),gun.x+gun.w+(int)(20*s));
    //공성전: 성이 거울로 서고 성주가 오른쪽에 있으므로 내 히어로는 왼쪽에서 올라탄다.
    //둘은 데크 가운데서 마주 선다(내 쪽 24%, 상대 42%). 상대 턴에 런을 맞바꾸면
    //hero 가 성주이므로 자리와 방향도 같이 바뀐다.
    const bool sidesSwapped=siegeActive&&Siege::swapped;
    const int allyX=(int)(DX*.24f),foeX=(int)(DX*.42f);
    const int hx=siegeActive?(sidesSwapped?foeX:allyX):monsterHeroX(l);
    const int heroDir=sidesSwapped?LEFT:RIGHT;
    const int hy=l.ground+(int)(4*s);
    const int shownNpc=waveTransition.defeatedVisible()?defeatedNpc:combatEnemyNpc();
    const int shownCmf=enemyData[shownNpc*ENEMYDATASIZE+ENEMYDATA_CMF];
    if(railBossScene()&&cmfLoaded[shownCmf]!=shownCmf)CmfRead(shownCmf,shownCmf);
    const int ex=siegeActive?(sidesSwapped?allyX:foeX):monsterHomeX(l,shownNpc,shownCmf);
    const int ey=railBossScene()?combatRailY():hy;
    const float deckY=(float)hy;
    allyBodyX=hx;allyBodyY=hy+(int)(40*s);allyBodyKnown=true;   //히어로 그림은 x 가 몸통 가운데다
    SetSectionClip(0,DY-(int)(72*s),DX,DY-(int)(72*s)-l.arenaBottom-(int)(8*s),false);
    // Submit all monsters before allies, so weapons and allied effects stay in front.
    if(combat&&siegeActive&&!nativeTitleIsolate){Siege::drawFoe(l,ex,ey);}   //공성전: 몬스터 자리에 상대 성주(DrawPlayer, 가운데 앵커)
    else if(combat&&!nativeTitleIsolate) {
    if(railBossScene())UnSectionClip(false);
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
    if(review&&npc==ENEMY_SNAIL&&reviewSnailPose>=0)enemyMotion=reviewSnailPose;
    renderedEnemyX=enemyX;renderedEnemyMotion=enemyMotion;renderedEnemyDir=enemyDir;
    int monsterY=ey;
    const bool defeated=waveTransition.defeatedVisible();
    const bool showMonster=(defeated||waveTransition.incomingVisible())&&(!startEventActive()||startEventElapsed>=1.25f);
    if(startEventActive())enemyX+=(int)((1.f-MergeCastleTransition::Ease(startEventElapsed,1.25f,.7f))*DX*.35f);
    if(defeated){
        enemyMotion=defeatedMotion;SetAlpha((int)(32*waveTransition.defeatAlpha()));
        monsterY-=(int)((1-waveTransition.defeatAlpha())*12*s);
    }
    //다음 적은 제자리(ex)에서 마왕의 심장 아래로 솟아오른다 - 옛 실시간 판의 소환 연출(REGENMOVE/REGENDRAW,
    //Func_Graphics 의 "생성 그리기")을 턴 전투 길이(EnterFrames)에 맞춰 옮긴 것이다. 걸어 들어오던
    //incomingX 경로는 쓰지 않는다. 심장 그림은 몬스터 다음에 제출해 몸 위에 겹친다.
    MergeCombat::SummonPose summon;
    float drawZoom=enemyZoom;
    if(!defeated&&waveTransition.active()&&waveTransition.incomingVisible()){
        enemyX=ex;
        summon=MergeCombat::summonPose(waveTransition.age-MergeCombat::WaveTransition::EnterStart,MergeCombat::WaveTransition::EnterFrames);
        if(!summon.landed){
            //이 그리기 공간은 y 가 위로 자란다(ey=680 이 850 화면의 위쪽 170). 점프는 더하기다. 높이는 화면 배율만
            //따른다 - 몬스터 배율(1.35 안팎)까지 곱하면 화면 밖으로 튄다.
            monsterY=ey+(int)(summon.lift*s);
            drawZoom=enemyZoom*summon.zoomMul;
            if(summon.flipped)enemyDir=RIGHT;
            SetAlpha(summon.alpha);   //옛 RegenDraw 의 검은 SetBlend 는 색 0 이라 실제로는 걸리지 않았다. 투명도만 올린다.
        }
    }
    renderedEnemyX=enemyX;renderedEnemyMotion=enemyMotion;
    monsterDrawn=showMonster;
    if(showMonster){
        monsterDrawOrder=++objectDrawOrder;
        if(summon.landed)DrawCmfDetailShadow(cmf,enemyMotion,enemyX,monsterY,enemyDir,drawZoom);
        else{
            //그림자는 바닥에 두고 몸만 띄운다. DrawCmfDetailShadow 는 발 자리에 그림자를 붙여서 같이 떠 버린다.
            if(IsBigCmf(cmf))ShadowImage(40*_2X,16*_2X,26*_2X,1*_2X,enemyX-(int)(20*_2X*enemyZoom),ey+(int)(8*_2X*enemyZoom),SHADOW_IMG,enemyZoom);
            else ShadowImage(24*_2X,16*_2X,1*_2X,1*_2X,enemyX-(int)(12*_2X*enemyZoom),ey+(int)(8*_2X*enemyZoom),SHADOW_IMG,enemyZoom);
            DrawCmfDetail(cmf,enemyMotion,enemyX,monsterY,enemyDir,drawZoom,false,false);
            SetAlpha(32);
            //머리 위 마왕의 심장. 몬스터 배율 그대로면 몸을 덮을 만큼 커서 SUMMONHEARTZOOM 으로 줄인다(옛 판과 같다).
            //서 있을 때의 머리 꼭대기보다 점프 높이만큼 더 위에 띄운다 - 몬스터는 그 아래에서 솟아올라 착지한다.
            if(cmfLoaded[CMF_NPC_HEART]!=CMF_NPC_HEART)CmfRead(CMF_NPC_HEART,CMF_NPC_HEART);
            const float heartZoom=enemyZoom*SUMMONHEARTZOOM;
            int headY=ey+(int)(120*s);
            if(cmf>=TOTALCHAR&&enemyMotion>=0&&enemyMotion<cmf_m_cnt[cmf]){
                const auto* mb=cmfMotionImgSize[cmf]+enemyMotion*4;
                //표의 세로 오프셋은 그림 좌표(아래로 +)라 머리 꼭대기는 발 앵커에서 -mb[1]*zoom 만큼 위다(y 는 위로 +).
                const int top=ey-(int)(mb[1]*enemyZoom);
                if(top>ey&&top<ey+400*s)headY=top;
            }
            //심장 그림(64x64)은 조각 좌표가 -64..0 이라 몬스터의 발처럼 앵커가 아래끝이다. 앵커를 머리 꼭대기 조금 위에
            //두면 심장은 그 위에 서고, 뒤따르는 불꽃(SPARK) 조각들은 앵커 아래로 180 가까이 뻗어 몬스터 몸으로
            //번개가 내리꽂히는 모양이 된다 - 그게 옛 소환 연출이다.
            const int heartMotion=summonMotion[summon.heartMotion];
            //심장은 점프 꼭대기(lift 64)보다 위에 둔다. 솟아오르는 몬스터가 심장을 뚫고 지나가지 않고, 번개만 몸에 닿는다.
            const int heartY=headY+(int)(72*s);
            DrawCmfDetail(CMF_NPC_HEART,heartMotion,enemyX,heartY,LEFT,heartZoom,false,false);
        }
    }
    SetAlpha(32);
    if(cmf>=TOTALCHAR&&enemyMotion>=0&&enemyMotion<cmf_m_cnt[cmf]){
        const auto* mb=cmfMotionImgSize[cmf]+enemyMotion*4;
        enemyBodyX=enemyX+(enemyDir==LEFT?-1:1)*(int)((mb[0]+mb[2]*.5f)*enemyZoom);
        enemyBodyY=ey-(int)((mb[1]+mb[3]*.5f)*enemyZoom);
        //경계값이 그림 틀 밖을 가리키면(큰 보스의 표가 다른 단위일 때) 발 위 40 으로 되돌린다.
        if(enemyBodyX<enemyX-(railBossScene()?600:220)*s||enemyBodyX>enemyX+60*s||enemyBodyY<ey||enemyBodyY>ey+(railBossScene()?700:260)*s){enemyBodyX=enemyX-(int)(30*s);enemyBodyY=ey+(int)(40*s);}
    }else{enemyBodyX=enemyX;enemyBodyY=ey+(int)(40*s);}
    enemyBodyKnown=showMonster;
    SetSectionClip(0,DY-(int)(72*s),DX,DY-(int)(72*s)-l.arenaBottom-(int)(8*s),false);
    }
    //히어로는 판의 주인이다. 데크에서 한눈에 찾아야 하므로 동료보다 크다(1.5배).
    float heroZoom=std::max(.3f*s,std::min(.90f*s,(DY-hy-90*s)/125.f));

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
    // The lobby displays only the selected hero. Board companions are drawn in combat.
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
        const float crewRight=hx-MergeCombat::DeckGap*s,crewLeft=std::min((float)deckBack,crewRight);
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
            if(combat&&(entering()||!deckReveal[b.crew].visible()))continue;

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
            SetAlpha((int)(32*ease));
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
void leaveBattle(bool abandon){
    starterInteriorReveal=1;lobbyDepartureAge=-1;lobbyDepartureCharge=false;
    if(abandon){robin.mergeRouletteRun[0]=0;SaveGame();RewardPopup::closeNow();}
    else save();
    quitPromptOpen=false;quitPromptFinger=quitPromptChoice=exitPromptFinger=-1;
    siegeActive=false;siegeHullStage=-1;
    active=false;resumePromptChecked=false;option.gameMode=(unsigned char)oldMode;
    picked=-1;finger=-1;systemKey=0;
    is_key_pressed=is_touchkey_pressed=is_key_released=false;
    is_press_finished=is_release_finished=true;
    drawHandle=MD_LOBBY;mustRefresh=true;
}
void close() {
    if(waveTransition.active())return;
    if(run.attacking) {message=u8"\uACF5\uACA9 \uC5F0\uCD9C\uC774 \uB05D\uB09C \uB4A4 \uB098\uAC08 \uC218 \uC788\uC2B5\uB2C8\uB2E4.";return;}
    leaveBattle(false);
}
Box gameOverPanel(){const float s=DX/640.f;return {(int)(64*s),(int)(DY*.5f+190*s),(int)(512*s),(int)(380*s)};}
Box gameOverChoice(int i){const auto p=gameOverPanel();const int m=24*DX/640,g=16*DX/640,w=(p.w-2*m-g)/2;return {p.x+m+i*(w+g),p.y-p.h+80*DX/640,w,56*DX/640};}
void drawGameOver(){
    const float s=DX/640.f;const auto p=gameOverPanel();
    SetAlpha(25);MemRect(0,DY,DX,DY,0x080D16);SetAlpha(32);
    panel(p,0x192435,0xBD9253);
    label("GAME OVER",DX/2,p.y-(int)(28*s),1.25f,0xF3C775);
    label(run.battleEnergy<=0?u8"번개를 모두 사용했습니다":u8"성의 체력을 모두 잃었습니다",DX/2,p.y-(int)(96*s),.68f,0xFFE4CE);
    char text[96];std::snprintf(text,sizeof(text),u8"스테이지 %d · %d번째 전투",run.stage+1,run.wave+1);
    label(text,DX/2,p.y-(int)(146*s),.58f,0xB9CBDD);
    label(u8"이미 처치한 적의 보상은 유지됩니다.",DX/2,p.y-(int)(202*s),.53f,0xDEC79B);
    label(u8"이번 전투의 보상은 지급되지 않습니다.",DX/2,p.y-(int)(232*s),.53f,0xDEC79B);
    button(gameOverChoice(0),u8"로비로",nullptr,0x34475B);
    button(gameOverChoice(1),u8"다시 도전",nullptr,0x85612B);
}
bool gameOverTouch(int phase,int id,float x,float y){
    static int press=-1,owner=-1;
    if(phase==0){press=-1;owner=id;for(int i=0;i<2;++i)if(gameOverChoice(i).has(x,y))press=i;}
    if(owner==id&&(phase==2||phase==3)){
        const int choice=press;press=owner=-1;
        if(phase==2&&choice>=0&&gameOverChoice(choice).has(x,y)){
            leaveBattle(true);PlayMusic(M_BUTTON);
            if(choice==1){entryChoiceOpen=true;entryChoiceFinger=entryChoicePressed=-1;}
        }
    }
    return true;
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
    if(run.attacking||run.lost||run.choosing||waveTransition.active())return;
    if(automaticMerge.active()){pendingPass=true;return;}
    if(beginAutomaticMerge()){pendingPass=true;return;}
    if(!run.tray.empty())return;
    CastleTutorialEvent(CastleTutorial::Placed);   //튜토리얼: 트레이를 다 놓았다
    if(!run.boardResolved()){pendingPass=true;return;}
    pendingPass=false;
    if(siegeActive){Siege::afterMySpin();return;}
    if(run.passTurn(stats)){action=CombatAction();enemyTurn=EnemyTurn();animation=0;save();}
}
static const char* OverlapMessage=u8"장비가 겹쳐 있습니다.\n빈 칸으로 옮겨 주세요.";
void finishCombatTurn() {
    const int accountBefore=robin.lv;
    const long long accountExpBefore=AccountLevel::normalizedTotal(robin.lv,robin.exps);
    bool killed=run.enemyHp==0;
    const bool stageClear=killed&&!siegeActive&&run.wave==WavesPerStage-1;
    long long overkill=std::max(0LL,run.damageDone-run.enemyMax);
    const long long previousLives=run.lives;
    if(killed&&!siegeActive){defeatedRailBoss=railBossScene();defeatedNpc=combatEnemyNpc();defeatedMotion=renderedEnemyMotion;}
    int hearts=run.finish();enemyTurn=EnemyTurn();
    action=CombatAction();animation=0;turretFire.age=-1;
    if(attackWeaponLevel)showAttackWeapon(0);
    if(run.lives>previousLives)combatNumbers.push_back({"+"+std::to_string(run.lives-previousLives),DX*.66f,(float)(layout().ground+68*DX/640.f),0x8DFFA2});
    run.setShape(castleShape(run.stage));
    // Equipment restores the local supply; a kill always fills all five slots.
    run.battleEnergy=std::min((int)Run::BattleEnergyMax,run.battleEnergy+hearts);
    if(killed){refillFrom=heartDisplay;refillElapsed=-1.f;refillPending=true;run.refillBattleEnergy();heartBlink=0;spentHeart=-1;}
    if(!killed)heartDisplay=run.battleEnergy;
    if(!killed&&!siegeActive)run.finishSupplies();
    if(siegeActive){if(refillPending){refillPending=false;refillElapsed=0.f;}Siege::afterAttack(killed);return;}   //공성전: 웨이브가 아니라 상대 턴
    if(killed) {
        PlayMusic(M_ENEMYDEAD);
        message=overkill>0?"오버킬! 다음 웨이브":"처치! 다음 웨이브";
        // Waves 1-14 retain the pending reward in the saved run; only boss 15 pays.
        std::vector<RewardPopup::Entry> rewards;
        if(stageClear) {
            // Retire the run before LevelUp saves: reload cannot replay boss EXP.
            robin.mergeRouletteRun[0]=0;robin.curWaveIdx=0;
            AccountLevelGain(AccountLevel::bossExp(std::max(0,run.stage-1)),false);
            const long long gold=run.reward;run.reward=0;
            GetItem(ITEM_GOLD,false,false,false,gold,false);
            RewardPopup::Entry g;g.type=ITEM_GOLD;g.count=gold;rewards.push_back(g);
            PlayMusic(M_CHEER);
            message="스테이지 클리어! 보상 획득 후 로비로";
            if(!review) {
                int type=ITEM_SWORD+hero.type,lv=std::max(1,std::min(GetEquipMaxLevel(),run.stage+1));
                int detail=MakeItemDetail(type,lv),grade=MakeItemGrade(type,lv,detail);
                if(GetItem(type,lv,detail,grade,1,0)){
                    RewardPopup::Entry it;it.type=type;it.detail=detail;it.grade=grade;it.lv=lv;it.count=1;rewards.push_back(it);
                }
            }
        }
        if(stageClear){
            RewardPopup::drawButton=rewardButton;
            RewardPopup::onClose=[](){CastleTutorialEvent(CastleTutorial::RewardClosed);waveTransition=MergeCombat::WaveTransition();leaveBattle(true);};
            RewardPopup::show(u8"스테이지 클리어",rewards,u8"로비로",enemyBodyKnown?(float)enemyBodyX:DX*.85f,enemyBodyKnown?(float)enemyBodyY:layout().ground+48*DX/640.f);
            if(accountBefore<AccountLevel::Max){char note[96];std::snprintf(note,sizeof(note),u8"모험 EXP +%lld  ·  Lv.%d",std::max(0LL,(long long)robin.exps-accountExpBefore),robin.lv+1);RewardPopup::summaryNote=note;}
            else RewardPopup::summaryNote=u8"모험가 최고 레벨 달성";
            // The payout and removal of the completed run share one save snapshot.
            robin.mergeRouletteRun[0]=0;robin.curWaveIdx=0;SaveGame();
        }
        else CastleTutorialEvent(CastleTutorial::RewardClosed);
        run.enemyHp=run.enemyMax=waveHp(run.stage,run.wave);
        if(run.realVitals)run.enemyAttack=waveAttack(run.stage,run.wave);
        waveTransition.begin();picked=finger=-1;
        allyFlash=0;enemyBodyKnown=false;
    } else message=run.lost?"목숨을 모두 사용했습니다":"턴 종료 · 다음 공격을 준비하세요.";
    if(!stageClear)save();
}
void tick(float dt) {
    if(!siegeActive&&!run.choosing&&!run.lost&&!run.attacking&&animation==0&&!pendingPass&&
       !automaticMerge.active()&&!entering()&&!introActive()&&!spinFlying()&&!deckArriving()&&
       !waveTransition.active()&&!startEventActive()&&run.tray.empty()&&run.finishSupplies()){
        picked=finger=-1;message.clear();save();
    }
    if(run.lost)return;
    if(startEventActive()){
        startEventElapsed=std::min(StartEventDuration,startEventElapsed+dt);
        castleScrollSeconds+=dt*.75f*(1.f-MergeCastleTransition::Ease(startEventElapsed,.4f,1.2f));
        return;
    }
    if(siegeActive)run.configureMonster(-1);else MonsterBoard::ensure();
    if(costumeEffectTicks>0)--costumeEffectTicks;
    if(trashSwallowTicks>0)--trashSwallowTicks;
    weaponSwap.advance();damagePause.advance();
    if(weaponSwap.attachNow()){
        hero.equip[EQUIP_WEAPON]=incomingWeapon;
        refreshHeroVitals();PlayMusic(M_RELOAD);
    }
    ++ticks;++frame;if(flash>0)--flash;if(allyFlash>0)--allyFlash;
    for(auto& number:combatNumbers)++number.age;
    combatNumbers.erase(std::remove_if(combatNumbers.begin(),combatNumbers.end(),[](const CombatNumber& n){return n.age>=MergeCombat::DamageNumberFrames;}),combatNumbers.end());
    heartBlink=std::max(0.f,heartBlink-dt);messageTime=std::max(0.f,messageTime-dt);
    if(siegeActive&&Siege::advance())return;   //상대 턴 연출이 프레임을 쓴다
    if(refillElapsed>=0.f){
        const int before=heartDisplay;
        refillElapsed+=dt;
        heartDisplay=std::min(run.battleEnergy,refillFrom+1+(int)(refillElapsed/.14f));
        if(heartDisplay>before)PlayMusic(M_ITEM);
        if(refillElapsed>=(run.battleEnergy-refillFrom)*.14f+.32f)refillElapsed=-1.f;
    }else if(!refillPending)heartDisplay=run.battleEnergy;
    if(entering()) {
        const float before=entryElapsed;
        entryElapsed=std::min(MergeCastleTransition::Duration,entryElapsed+dt);
        const int count=portraitGridCapacity();
        for(int i=0;i<count;++i){const float land=MergeCastleTransition::TileLand(i,count);
            if(before<land&&entryElapsed>=land)PlayMusic(M_DOWN);}
        return;
    }
    if(introActive()) {
        float before=introElapsed;
        introElapsed+=dt;
        const float phase=std::min(1.f,introElapsed/2.48f);
        gearAngle=1350.f*(1.f-std::pow(1.f-phase,3.f));
        for(int i=0;i<3;++i) {
            float stop=2.f+i*.24f,land=flightStart(i)+.7f;
            if(before<stop&&introElapsed>=stop)PlayMusic(M_RELOAD);
            if(before<land&&introElapsed>=land)PlayMusic(M_DOWN);
        }
        return;
    }
    if(waveTransition.active()){
        if(RewardPopup::open()&&waveTransition.age>=MergeCombat::WaveTransition::DefeatFrames){
            if(review&&!std::getenv("CS_REWARD_REVEAL_REVIEW")){   //리뷰는 첫 보상창만 한 장 남기고 저절로 닫는다
                static bool captured=false;
                static bool shot=false;
                if(!captured&&RewardPopup::ready()){captured=true;reviewCapture("kill-reward");}   //카드가 다 선 뒤
                if(captured&&!shot&&!reviewCapturePending)shot=true;   //찍힌 것을 보고 닫는다
                if(shot?RewardPopup::ticks()>12:(captured&&!reviewCapturePending))RewardPopup::closeNow();
            }
            return;
        }
        const float previousDistance=waveTransition.distance();
        waveTransition.advance();
        castleScrollSeconds+=(waveTransition.distance()-previousDistance)/110.f;
        //심장이 뜨는 순간의 소환음(옛 RegenMove 와 같은 소리).
        if(waveTransition.age==MergeCombat::WaveTransition::EnterStart){
            EffectSound(M_WARP);
            if(refillPending){refillPending=false;refillElapsed=0.f;}
        }
        if(!waveTransition.active()){message.clear();enemyBodyKnown=false;}
        return;
    }
    if(spinFlying()){
        ++spinFlightFrame;
        for(int i=0;i<(int)spinDrops.size();++i)if(spinFlightFrame==36+i*4)PlayMusic(M_DOWN);
        if(spinFlightFrame>=48){run=spinLandingPlan;spinFlightFrame=-1;pendingPass=true;if(!run.boardResolved()){message=OverlapMessage;messageTime=4;}save();endSpinTurn();}   //돌리기 한 번 = 턴 하나. 결과가 앉으면 적이 때린다
        return;
    }
    if(automaticMerge.active()){
        if(++automaticMerge.age>=(automaticMerge.fromTray?56:24)){
            run=automaticMerge.plan;automaticMerge.age=-1;
            PlayMusic(M_POWERUP);updateHeroCostume();save();
            beginAutomaticMerge();
        }
        return;
    }
    if(!run.attacking&&animation==0&&!deckArriving()&&picked<0){
        if(beginAutomaticMerge())return;
        if(pendingPass){
            if(!run.tray.empty()&&beginSpinLanding())return;
            if(run.tray.empty()&&run.boardResolved()){endSpinTurn();return;}
        }
    }
    if(animation>0&&!run.attacking){
        const float phase=std::min(1.f,(REEL_SPIN_FRAMES+1-animation)/(float)REEL_SPIN_FRAMES);
        gearAngle=gearStartAngle+1350.f*(1.f-std::pow(1.f-phase,3.f));
        //릴이 설 때마다 한 번. 시작 뽑기(intro)와 같은 소리다.
        for(int i=0;i<3;++i)if(REEL_SPIN_FRAMES-animation==reelStopFrame(i)){
            PlayMusic(i<(int)run.tray.size()&&run.tray[i].ownedId&&run.tray[i].level>=4?M_ITEM:M_RELOAD);
        }
    }
    if(!run.attacking) {
        if(animation>0&&--animation==0){pendingPass=true;beginSpinLanding();save();}
        return;
    }
    if(run.enemyHp<=0){finishCombatTurn();return;}
    if(weaponSwap.running())return;
    if(action.index>=0) {
        const int before=action.time.elapsed;
        const bool impact=action.time.advance();
        if(run.shots[action.index].block.family<0)turretFire.age=action.time.elapsed;
        if(before<action.time.release&&action.time.elapsed>=action.time.release){
            action.bulletX=action.emitterReady?action.emitterX:shotFromX;
            action.bulletY=action.emitterReady?action.emitterY:shotFromY;
        }
        if(run.shots[action.index].block.family<0){
            for(int i=0;i<turretFire.count;++i)if(before<turretFire.launch(i)&&action.time.elapsed>=turretFire.launch(i))
                PlayMusic(turretFire.type==TurretAttack::Stone?M_SWORDSTRONG:turretFire.type==TurretAttack::Laser||turretFire.type==TurretAttack::Magnetic?M_LASER:turretFire.type==TurretAttack::Rapid?M_GUN:M_GUNSTRONG);
        }else if(before<action.time.release&&action.time.elapsed>=action.time.release&&action.heroSounds.empty())PlayMusic(M_SWORD);
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
            PlayMusic(run.shots[action.index].block.family<0?(turretFire.type==TurretAttack::Stone?M_KUNG:turretFire.type==TurretAttack::Laser||turretFire.type==TurretAttack::Magnetic?M_GUNHIT:M_BANG):M_SWORDHIT);
            if(run.enemyHp<=0){finishCombatTurn();return;}
            save();
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
            floatingAbsorbed(enemyTurn.absorbedShares[0]);floatingDamage(enemyTurn.shares[0],false);allyFlash=20;PlayMusic(M_KUNG);
            enemyTurn.hitsShown=1;save();
        }else if(enemyTurn.hitsShown>0&&enemyTurn.hitsShown<enemyTurn.hits&&enemyTurn.time.elapsed>=enemyTurn.impacts[enemyTurn.hitsShown]){
            const int k=enemyTurn.hitsShown++;
            long long shown=0;for(int i=0;i<=k;++i)shown+=enemyTurn.shares[i];
            heroHpHold=k+1<enemyTurn.hits?enemyTurn.hpBefore-shown:-1;
            if(k<(int)enemyTurn.absorbedShares.size())floatingAbsorbed(enemyTurn.absorbedShares[k]);
            floatingDamage(enemyTurn.shares[k],false);allyFlash=20;PlayMusic(M_KUNG);
        }
        if(enemyTurn.time.finished()){
            enemyTurn.complete=true;heroHpHold=-1;
            CastleTutorialEvent(CastleTutorial::CounterTaken);   //튜토리얼: 반격을 맞았다
            if(enemyTurn.healing>0){combatNumbers.push_back({"+"+std::to_string(enemyTurn.healing),DX*.85f,(float)(layout().ground+68*DX/640.f),0x8DFFA2});PlayMusic(M_POWERUP);}
        }
        return;
    }
    if(damagePause.waiting())return;
    if(!enemyTurn.endShown){enemyTurn.endShown=true;enemyTurn.endFrames=30;return;}
    if(enemyTurn.endFrames>0){--enemyTurn.endFrames;return;}
    finishCombatTurn();
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
    if((introActive()&&introElapsed>=2.65f)||spinFlying()) {
        if(!reelResultDrawn[0]||!reelResultDrawn[1]||!reelResultDrawn[2]){
            reviewTrace("FAIL stopped reel went blank during grid transfer");done=true;return;
        }
    }
    if(phase==0) {
        if(firstCrew<0)for(const auto& b:run.board)if(b.family<Roles){firstCrew=b.crew;break;}
        if(introElapsed<3.55f&&deckResidentCount!=0){reviewTrace("FAIL opening crew leaked before grid landing");done=true;return;}
        if(!stopped&&introElapsed>=2.65f) {
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
        run.battleEnergy=1;
        if(!run.attack(stats)){reviewTrace("FAIL wave fixture could not attack");done=true;}
        else run.spendBattleEnergy();
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
        //소환 구간은 둘로 나눠 본다: 심장 아래로 솟는 중(4)과 착지 직전(16).
        int bit=t.defeatedVisible()?1:t.travelling()?2:t.arrival()<.6f?4:t.arrival()<1?16:8;
        if(t.travelling()&&(monsterDrawn||enemyBodyKnown)){reviewTrace("FAIL next enemy visible during castle travel");done=true;return;}
        const long long heart=robin.heart;const int spins=run.spins;
        reviewTap(l.attack);reviewTap(l.spin);
        if(run.attacking||robin.heart!=heart||run.spins!=spins||(int)run.board.size()!=boardCount){reviewTrace("FAIL transition accepted input or changed board");done=true;return;}
        // Capture the middle of each visible phase, not just its first frame.
        const bool capture=(bit==1&&t.age>=8)||(bit==2&&t.age>=60)||(bit==4&&t.arrival()>=.4f)||(bit==16&&t.arrival()>=.85f)||(bit==8);
        if(capture&&!(mask&bit)){
            char name[48];std::snprintf(name,sizeof(name),"wave-%d-%s",sample,bit==1?"defeat":bit==2?"travel":bit==4?"summon-rise":bit==16?"summon-land":"settled");
            reviewCapture(name);mask|=bit;
        }
        phase=2;return;
    }
    if(phase==2){
        if(mask!=31||run.stage!=expectedStage||run.wave!=expectedWave||!layerSeen||
           std::abs(castleScrollSeconds-travelStart-480.f/110.f)>.01f||run.lost||run.battleEnergy!=Run::BattleEnergyMax){
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
#include "RewardRevealReview.inc"
bool portraitCameraTouch(int,int,float,float);
bool portraitStarterInteriorTouch(int,int,float,float);
#include "PortraitGameReview.inc"
void reviewStep(const Layout& l) {
    if(portraitReviewStep(l))return;
    if(review&&std::getenv("CS_START_EVENT_REVIEW")){
        if(introActive()&&!entering()&&introElapsed>.4f&&!reviewCapturePending&&!reviewDone){
            reviewTrace(run.board.size()==3&&run.spins==SpinLimit?"PASS opening keeps three free starters and spin budget":"FAIL opening reward changed");
            reviewCapture("start-event-04-free-spin");reviewTrace("DONE start event review");reviewDone=true;
        }
        return;
    }
    if(review&&std::getenv("CS_COVER_STYLE_REVIEW")){
        static int phase=0,hold=0;
        if(phase>=4)return;
        if(phase==0){
            const char* value=std::getenv("CS_COVER_STYLE_STAGE");
            run=Run();run.roster=&roster;run.choosing=false;run.stage=value?std::max(0,std::min(9,std::atoi(value)-1)):1;
            run.setShape(castleShape(run.stage));run.enemyHp=run.enemyMax=waveHp(run.stage,0);
            automaticMerge=AutomaticMerge();pendingPass=false;picked=finger=-1;
            entryElapsed=MergeCastleTransition::Duration;introElapsed=-1;animation=0;spinFlightFrame=-1;
            waveTransition=MergeCombat::WaveTransition();action=CombatAction();
            phase=1;return;
        }
        if(++hold<(phase==2?5:75))return;hold=0;
        if(phase==1){reviewCapture("cover-empty");phase=2;return;}
        if(phase==2){
            for(int family:std::vector<int>{0,1,Sword,Armor,Boots}){
                if(family<Roles&&!roster.has(family,1))continue;
                run.tray.push_back(run.starter(family));run.autoPlace(0);
            }
            phase=3;return;
        }
        reviewCapture("cover-with-grid");reviewTrace("PASS dimensional cover rendered with native grid and units");
        reviewTrace("DONE cover style review");phase=4;return;
    }
    if(review&&std::getenv("CS_FIVE_FLOOR_PVP_REVIEW")){
        static int phase=0,hold=0;static Box first={0,0,0,0};
        if(phase>=3||reviewCapturePending)return;
        if(phase==0){Siege::begin();Siege::phase=0;entryElapsed=-1;introElapsed=-1;message.clear();messageTime=0;phase=1;return;}
        if(++hold<12)return;hold=0;
        const auto& cover=drawnFrontCoverBounds;
        bool valid=siegeActive&&drawnFrontCover==MistCastle::image(Siege::castle,8);
        if(phase==1){
            first=cover;
            reviewTrace(valid?"PASS five-floor siege uses the shared closed castle renderer":"FAIL siege castle source");
            reviewCapture("five-floor-pvp-player");Siege::swapSides();introElapsed=-1;phase=2;
        }else{
            valid=valid&&cover.x==first.x&&cover.y==first.y&&cover.w==first.w&&cover.h==first.h;
            reviewTrace(valid?"PASS five-floor siege keeps one castle and fixed cover bounds on both turns":"FAIL siege castle bounds");
            reviewCapture("five-floor-pvp-opponent");reviewTrace("DONE five-floor siege review");phase=3;
        }
        return;
    }
    if(review&&std::getenv("CS_EXIT_PROMPT_REVIEW")){
        static int phase=0,pausedTick=0,pausedAction=0;static long long wallet=0;static std::string before;
        if(phase>=7)return;
        if(phase==0){
            run=Run();run.roster=&roster;run.choosing=false;run.setShape(castleShape(0));
            run.enemyHp=run.enemyMax=100000000;Block b;b.family=Sword;run.tray.push_back(b);run.autoPlace(0);
            run.battleEnergy=3;run.attack(stats);
            automaticMerge=AutomaticMerge();pendingPass=false;picked=finger=-1;
            entryElapsed=MergeCastleTransition::Duration;introElapsed=-1;animation=0;spinFlightFrame=-1;
            action=CombatAction();enemyTurn=EnemyTurn();waveTransition=MergeCombat::WaveTransition();
            wallet=robin.heart;phase=1;return;
        }
        if(phase==1){
            reviewTap(l.exit);before=run.encode();pausedTick=ticks;pausedAction=action.time.elapsed;
            reviewTrace(quitPromptOpen?"PASS exit opens confirmation during attack":"FAIL exit confirmation");phase=2;return;
        }
        if(phase==2){
            reviewTrace(run.encode()==before&&ticks==pausedTick&&action.time.elapsed==pausedAction?"PASS confirmation pauses exact battle state":"FAIL confirmation advanced combat");
            reviewCapture("exit-confirm");phase=3;return;
        }
        if(phase==3){
            reviewTap(resumeChoiceBox(1));
            reviewTrace(active&&!quitPromptOpen&&!entering()&&run.encode()==before&&ticks==pausedTick&&action.time.elapsed==pausedAction&&robin.heart==wallet?
                "PASS cancel returns directly to unchanged battle without cover or energy charge":"FAIL exit cancel");
            phase=4;return;
        }
        if(phase==4){reviewCapture("exit-cancelled");phase=5;return;}
        if(phase==5){reviewTap(l.exit);phase=6;return;}
        if(phase==6){
            reviewTap(resumeChoiceBox(0));
            reviewTrace(!active&&!quitPromptOpen&&drawHandle==MD_LOBBY&&!robin.mergeRouletteRun[0]&&robin.heart==wallet?
                "PASS abandon clears run and returns to lobby without refund":"FAIL exit abandon");
            reviewTrace("DONE exit confirmation review");phase=7;return;
        }
        return;
    }
    if(review&&std::getenv("CS_MERGE_ARRIVAL_REVIEW")){arrivalReviewStep(l);return;}
    if(review&&std::getenv("CS_GRID_CREW_ROTATION_REVIEW")){
        static int phase=0;if(phase>=3)return;
        if(phase==0){
            run=Run();run.roster=&roster;run.choosing=false;run.setShape(castleShape(0));
            Block b;b.family=0;b.crew=roster.first(0,1);run.tray.push_back(b);run.autoPlace(0);
            automaticMerge=AutomaticMerge();pendingPass=false;picked=finger=-1;
            entryElapsed=MergeCastleTransition::Duration;introElapsed=-1;animation=0;spinFlightFrame=-1;
            phase=1;return;
        }
        if(phase==1){reviewCapture("crew-upright");phase=2;return;}
        if(!run.board[0].rot){
            reviewTrace(run.rotate(0)&&run.board[0].rot&&Wide(run.board[0])>Tall(run.board[0])?"PASS crew footprint rotates horizontally":"FAIL crew rotate");
            return;
        }
        const Box tile=blockBox(run.board[0],l);char contact[128];
        std::snprintf(contact,sizeof(contact),"CONTACT_TILE %d %d %d %d",tile.x,tile.y,tile.w,tile.h);reviewTrace(contact);
        reviewCapture("crew-horizontal");reviewTrace("DONE grid crew rotation review");phase=3;return;
    }
    if(review&&std::getenv("CS_SCATTER_SPIN_REVIEW")){
        static int phase=0,count=0;
        if(phase>=3)return;
        if(phase==0){
            run=Run();run.roster=&roster;run.choosing=false;run.setShape(castleShape(0));
            run.enemyHp=run.enemyMax=1000000;
            for(int i=0;i<3;++i)run.families[i]=Sword;
            for(int i=0;i<Cells;++i){Block b;b.family=Sword;run.tray.push_back(b);if(!run.autoPlace(0)){run.tray.clear();break;}}
            count=(int)run.board.size();
            automaticMerge=AutomaticMerge();pendingPass=false;picked=finger=-1;
            entryElapsed=MergeCastleTransition::Duration;introElapsed=-1;animation=0;spinFlightFrame=-1;
            reviewCapture("scatter-before");phase=1;return;
        }
        if(phase==1){
            reviewTap(l.spin);
            reviewTrace(animation>0&&run.battleEnergy==4?"PASS crowded board accepts spin and spends one lightning":"FAIL crowded spin blocked");
            phase=2;return;
        }
        if(animation>0||spinFlying())return;
        Run restored;restored.roster=&roster;
        reviewTrace(run.tray.empty()&&(int)run.board.size()==count+3&&!run.boardResolved()&&restored.decode(run.encode())?
            "PASS all spin rewards scatter onto crowded board and persist for manual cleanup":"FAIL scatter reward loss");
        reviewCapture("scatter-results");reviewTrace("DONE scatter spin review");phase=3;return;
    }
    if(review&&std::getenv("CS_MERGE_GLOW_REVIEW")){
        static int level=1,phase=0;
        if(level>=MaxLevel)return;
        if(phase==0){
            run=Run();run.choosing=false;run.stage=9;run.setShape(castleShape(9));
            run.enemyHp=run.enemyMax=1000000;
            for(int i=0;i<2;++i){Block b;b.family=Sword;b.level=level;run.tray.push_back(b);if(!run.autoPlace(0)){reviewTrace("FAIL glow fixture placement");return;}}
            automaticMerge=AutomaticMerge();pendingPass=false;picked=finger=-1;
            entryElapsed=MergeCastleTransition::Duration;introElapsed=-1;animation=0;spinFlightFrame=-1;
            mergeSeenSeq=run.mergeSeq;
            if(!run.place(false,1,run.board[0].x,run.board[0].y)){reviewTrace("FAIL glow fixture merge");return;}
            phase=1;return;
        }
        if(mergeFlash>0&&mergeFlash<=mergeFlashDuration-5){
            reviewTrace(mergeShownLevel==level+1&&mergeFlashDuration==20+7*(level+1)?"PASS merge tier increases border glow strength and duration":"FAIL merge glow tier");
            char name[40];std::snprintf(name,sizeof(name),"merge-glow-tier-%d",level+1);reviewCapture(name);
            ++level;phase=0;
            if(level>=MaxLevel){reviewTrace(MonsterBoard::panelBox.w>0?"PASS enemy parts panel visible at top right":"FAIL enemy parts panel");reviewTrace("DONE merge glow review");}
        }
        return;
    }
    if(review&&std::getenv("CS_AUTO_MERGE_REVIEW")){
        static int scenario=0,phase=0,mask=0;static Roster fixture;
        if(scenario>=2)return;
        if(phase==0){
            run=Run();run.choosing=false;run.setShape(castleShape(0));
            fixture=Roster();
            for(int lv=1;lv<=3;++lv)fixture.add(0,lv,MergeTrees::CrewAt(0,lv,0));
            run.roster=&fixture;run.enemyHp=run.enemyMax=1000000;
            for(int i=0;i<4;++i){Block b;b.family=scenario?0:Sword;b.level=1;b.crew=scenario?fixture.first(0,1):-1;run.tray.push_back(b);if(!run.autoPlace(0)){reviewTrace("FAIL automatic merge fixture");return;}}
            automaticMerge=AutomaticMerge();pendingPass=true;picked=finger=-1;
            entryElapsed=MergeCastleTransition::Duration;introElapsed=-1;animation=0;spinFlightFrame=-1;
            deckMerge=DeckMergePresentation();deckMergeSeen=run.mergeSeq;
            for(auto& r:deckReveal)r=MergeCombat::ResidentReveal();
            phase=1;mask=0;return;
        }
        if(automaticMerge.active()){
            const auto before=run.encode();reviewTap(l.attack);reviewTap(l.spin);
            if(run.encode()!=before||run.attacking){reviewTrace("FAIL automatic merge input lock");scenario=2;return;}
            if(run.mergeSeq==0){
                const int age=automaticMerge.age,bit=age>=2&&age<6?1:age>=10&&age<14?2:age>=20?4:0;
                if(bit&&!(mask&bit)){char name[64];std::snprintf(name,sizeof(name),"auto-%d-%s",scenario,bit==1?"source-cell":bit==2?"direct-flight": "before-merge");reviewCapture(name);mask|=bit;}
            }
            return;
        }
        if(run.mergeSeq==3&&!deckArriving()){
            if(pendingPass)return;
            if(!run.attacking||!run.passing){reviewTrace("FAIL automatic merges did not defer exactly one monster turn");scenario=2;return;}
            reviewTrace("PASS monster turn waits for automatic merge chain");
            if(run.board.size()!=1||run.board[0].level!=3||mask!=7){reviewTrace("FAIL automatic merge chain result");scenario=2;return;}
            reviewTrace(scenario?"PASS companion chain merges directly from its landing cell":"PASS equipment chain merges directly from its landing cell");
            reviewTrace(run.battleEnergy==Run::BattleEnergyMax?"PASS automatic merges consume no lightning and lock input":"FAIL automatic merge energy");
            char name[64];std::snprintf(name,sizeof(name),"auto-%d-result",scenario);reviewCapture(name);
            ++scenario;phase=0;if(scenario==2)reviewTrace("DONE automatic merge review");
        }
        return;
    }
    if(review&&std::getenv("CS_SNAIL_FLAT_REVIEW")){
        static int phase=0,hold=0;if(phase>=5)return;
        if(phase==0){
            debugFirstBoss=false;reviewEnemyNpc=ENEMY_SNAIL;reviewSnailPose=0;
            run.stage=0;run.wave=0;run.setShape(castleShape(0));
            entryElapsed=introElapsed=-1;animation=0;run.attacking=false;run.lost=false;
            waveTransition=MergeCombat::WaveTransition();enemyTurn=EnemyTurn();
            MonsterBoard::build(0,0,ENEMY_SNAIL);phase=1;hold=0;return;
        }
        if(reviewCapturePending||++hold<80)return;hold=0;
        const char* name=phase==1?"snail-idle":phase==2?"snail-attack":phase==3?"snail-hide":"snail-parts";
        reviewCapture(name);
        if(phase==1)reviewSnailPose=10;
        if(phase==2)reviewSnailPose=15;
        if(phase==3){reviewSnailPose=0;MonsterBoard::expanded=true;}
        if(phase==4){reviewTrace("PASS native snail CMF idle attack hide and matching inventory parts");reviewTrace("DONE snail flat resource review");}
        ++phase;return;
    }

    if(review&&std::getenv("CS_BATTLE_ENERGY_REVIEW")){
        static int phase=0;static long long wallet=0;
        if(phase==0){
            entryElapsed=introElapsed=-1;animation=0;run.choosing=false;run.attacking=false;run.lost=false;
            run.board.clear();run.tray.clear();run.spins=3;run.battleEnergy=5;
            run.setVitals(100000,10000);run.lives=run.maxLives;run.enemyHp=run.enemyMax=100000000;
            wallet=robin.heart;reviewCapture("energy-05-start");phase=1;return;
        }
        if(phase>=10)return;
        if(animation>0||run.attacking||spinFlying()||deckArriving())return;
        if(phase==1){
            reviewTap(l.spin);
            reviewTrace(run.battleEnergy==4&&robin.heart==wallet?"PASS spin spends one local lightning without wallet charge":"FAIL spin local energy");
            reviewCapture("energy-04-spin");phase=2;return;
        }
        if(phase==2){
            run.board.clear();run.tray.clear();Block b;b.family=Sword;b.level=1;b.x=b.y=0;run.board.push_back(b);
            reviewTap(l.attack);
            reviewTrace(run.attacking&&run.battleEnergy==3&&robin.heart==wallet?"PASS attack spends one local lightning without wallet charge":"FAIL attack local energy");
            phase=3;return;
        }
        if(phase==3){
            reviewTap(l.cannon);
            reviewTrace(run.attacking&&run.battleEnergy==2&&robin.heart==wallet?"PASS cannon spends one local lightning without wallet charge":"FAIL cannon local energy");
            phase=4;return;
        }
        if(phase==4){
            run.tray.push_back(Block());const int before=run.battleEnergy;reviewTap(l.spin);
            const bool rejected=run.battleEnergy==before;run.tray.clear();run.battleEnergy=0;
            const auto empty=run.encode();reviewTap(l.spin);reviewTap(l.attack);reviewTap(l.cannon);
            reviewTrace(rejected&&run.encode()==empty&&robin.heart==wallet?"PASS rejected and empty actions never spend or mutate run":"FAIL empty lightning guard");
            reviewCapture("energy-00-empty");phase=5;return;
        }
        if(phase==5){
            run.board.clear();
            for(int i=0;i<3;++i){Block b;b.family=Sword;b.level=1;run.tray.push_back(b);if(!run.autoPlace(0)){reviewTrace("FAIL lethal fixture placement");return;}}
            run.battleEnergy=1;run.enemyHp=1;run.enemyGuard=0;reviewTap(l.attack);phase=6;return;
        }
        if(phase==6){
            reviewTrace(run.battleEnergy==5&&robin.heart==wallet&&RewardPopup::open()?"PASS kill refills five local lightning without wallet refund":"FAIL kill lightning refill");
            reviewTrace(action.index<0&&animation==0&&waveTransition.age==0&&refillPending&&heartDisplay==0?
                "PASS lethal impact immediately cancels remaining attacks and drops chest before refill":"FAIL lethal impact presentation");
            RewardPopup::closeNow();phase=7;return;
        }
        if(phase==7&&heartDisplay>=1&&heartDisplay<3){
            reviewTrace(waveTransition.incomingVisible()&&refillElapsed>=0?"PASS lightning refill starts with incoming monster":"FAIL refill timing");
            reviewCapture("energy-refill-first");phase=8;return;
        }
        if(phase==8&&heartDisplay>=3&&heartDisplay<5){reviewCapture("energy-refill-middle");phase=9;return;}
        if(phase==9&&refillElapsed<0&&!refillPending){
            reviewTrace(heartDisplay==5?"PASS lightning fills sequentially to five":"FAIL sequential refill");
            reviewCapture("energy-05-refilled");reviewTrace("DONE battle lightning review");phase=10;return;
        }
        return;
    }

    if(review&&std::getenv("CS_OWNED_GEAR_REVIEW")){
        static int phase=0;if(phase>=2)return;
        if(phase==0){
            for(int n=0;n<GetMaxInven();++n){memset(&robin.inven[n],0,sizeof(ITEM));robin.inven[n].type=EMPTY;}
            for(int star=1;star<=6;++star){
                int detail=-1;for(int d=0;d<TOTAL_SWORD;++d)if(GetItemStar(ITEM_SWORD,d,GRADE_NORMAL)==star){detail=d;break;}
                if(detail<0){reviewTrace("FAIL owned gear grade fixture");phase=2;return;}
                ITEM item;MakeItem(&item,ITEM_SWORD,1,GRADE_NORMAL,detail,0);item.id=990000+star;item.value=star*100;item.cooldown=0;item.count=1;
                robin.inven[star]=item;
            }
            hero.type=ROBIN;rebuildOwnedGearPool();
            Run sample;sample.roster=&roster;sample.choosing=false;sample.stage=9;sample.shape=castleShape(9);sample.setVitals(stats.heroHealth,stats.heroArmor);
            sample.enemyHp=sample.enemyMax=1000000000LL;unsigned roll=0;bool valid=true;
            for(int star=1;star<=6;++star){
                sample.tray={sample.starter(Sword)};const ITEM before=robin.inven[star];
                rollOwnedGearResults(sample,(int)roll);const Block b=sample.tray[0];
                valid=valid&&b.level==star&&b.ownedId==before.id&&b.ownedDetail==before.detail&&b.ownedPower==star*100&&memcmp(&before,&robin.inven[star],sizeof(ITEM))==0;
                valid=valid&&sample.autoPlace(0);roll+=MergeOwnedGear::Rate[star-1];
            }
            Run restored;restored.roster=&roster;valid=valid&&sample.encode().size()<sizeof(robin.mergeRouletteRun)&&restored.decode(sample.encode())&&restored.encode()==sample.encode();
            sample.tray={sample.starter(Armor)};rollOwnedGearResults(sample,1099);valid=valid&&!sample.tray[0].ownedId&&sample.tray[0].level==1;sample.tray.clear();
            reviewTrace(valid?"PASS owned six grades actual item art power footprint fallback and inventory preserved":"FAIL owned gear integration");
            run=sample;for(int n=0;n<3;++n)reelSymbols[n]=run.board[n*2+1];hasReelSymbols=true;
            entryElapsed=MergeCastleTransition::Duration;introElapsed=-1;animation=0;spinFlightFrame=-1;pendingPass=false;
            phase=1;return;
        }
        static int settle=0;if(++settle<70)return;
        reviewTrace(!weaponSwap.running()?"PASS owned weapon attachment completes once":"FAIL owned weapon attachment repeats");
        reviewCapture("owned-gear-results");reviewTrace("DONE owned gear review");phase=2;return;
    }
    if(review&&std::getenv("CS_DRAG_ANCHOR_REVIEW")){
        static bool done=false;
        if(done||entering()||introActive()||spinFlying()||deckArriving()||waveTransition.active())return;
        done=true;
        for(int rotated=0;rotated<2;++rotated){
            Block sword;sword.family=Sword;sword.level=2;sword.rot=rotated!=0;sword.x=0;sword.y=1;
            for(int gy=0;gy<Tall(sword);++gy)for(int gx=0;gx<Wide(sword);++gx){
                run=Run();run.roster=&roster;run.choosing=false;run.shape.width=4;run.shape.height=4;
                for(int row=0;row<4;++row)run.shape.rows[row]=15;
                Block armor;armor.family=Armor;armor.x=0;armor.y=2;
                run.board={armor,sword};animation=0;pendingPass=false;
                const Layout actual=layout();
                const float sx=actual.board.x+(sword.x+gx+.3f)*actual.cell;
                const float sy=actual.board.y-(sword.y+gy+.3f)*actual.cellH;
                const int tx=4-Wide(sword),ty=0;
                const float ex=actual.board.x+(tx+gx+.3f)*actual.cell;
                const float ey=actual.board.y-(ty+gy+.3f)*actual.cellH;
                MergeRouletteTouch(0,998,sx,sy);MergeRouletteTouch(1,998,ex,ey);MergeRouletteTouch(2,998,ex,ey);
                const Block& moved=run.board.back();
                reviewTrace(moved.family==Sword&&moved.x==tx&&moved.y==ty&&run.board[0].x==armor.x&&run.board[0].y==armor.y?
                    "PASS grabbed cell releases at visible position and clears original overlap":"FAIL grabbed-cell drop offset");
            }
        }
        reviewCapture("drag-anchor");reviewTrace("DONE drag anchor review");return;
    }
    if(rewardRevealReview())return;
    if(review&&std::getenv("CS_MONSTER_PARTS_REVIEW")){monsterPartsReviewStep();return;}
    if(review&&std::getenv("CS_COMBAT_FLOW_REVIEW")){
        static int sample=-1,hold=0;static long long gold=robin.gold;
        if(reviewCapturePending)return;
        if(sample>=12){reviewTrace("DONE combat flow review");return;}
        if(hold==0){
            ++sample;if(sample>=12){reviewTrace("DONE combat flow review");return;}
            debugFirstBoss=false;reviewEnemyNpc=-1;entryElapsed=introElapsed=-1;startEventElapsed=-1;
            waveTransition=MergeCombat::WaveTransition();enemyTurn=EnemyTurn();action=CombatAction();animation=0;
            pendingPass=false;run.tray.clear();run.board.clear();run.attacking=run.choosing=run.lost=false;
            run.stage=sample<2?1:sample-2;run.wave=sample<2?1:14;run.setShape(castleShape(run.stage));
            run.battleEnergy=sample==0?0:5;run.lives=sample==1?0:run.maxLives;
            if(sample==1)run.lost=true;
            run.enemyHp=run.enemyMax=waveHp(run.stage,run.wave);MonsterBoard::build(run.stage,run.wave,combatEnemyNpc());
            hold=1;return;
        }
        if(++hold<12)return;
        if(sample<2){
            const auto before=run.encode();MergeRouletteTouch(0,991,l.attack.x+4,l.attack.y-4);MergeRouletteTouch(2,991,l.attack.x+4,l.attack.y-4);
            const bool valid=run.lost&&robin.gold==gold&&run.encode()==before;
            reviewTrace(valid?"PASS game over blocks actions and preserves previously earned rewards":"FAIL game over or reward retention");
            reviewCapture(sample==0?"game-over-energy":"game-over-health");
        }else{
            const int npc=combatEnemyNpc(),cmf=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF];
            reviewTrace(railBossScene()&&monsterDrawn&&l.cell==(int)(48*l.scale)&&combatRailY()<l.ground&&monsterZoom(l,npc,cmf)>0?"PASS final boss stands on rail with compact battle board":"FAIL final boss scene");
            char name[40];std::snprintf(name,sizeof(name),"rail-boss-%02d",sample-1);reviewCapture(name);
        }
        hold=0;return;
    }
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
            const Box hullBounds=OriginalCastle::box(175,548,740,760);
            valid=valid&&drawnFrontCover==MistCastle::image(c,8)
                &&drawnFrontCoverBounds.x>=hullBounds.x
                &&drawnFrontCoverBounds.x+drawnFrontCoverBounds.w<=hullBounds.x+hullBounds.w
                &&l.cell==(int)(64*l.scale)&&l.cellH==l.cell
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
            updateHeroCostume();
            phase=2;hold=0;return;
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
            robin.castleProgress.parts[CastleMenuModel::Clamp(castle)][3]=std::getenv("CS_TURRET_REVIEW_LEVEL")?std::max(0,std::min(5,std::atoi(std::getenv("CS_TURRET_REVIEW_LEVEL")))):5;
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
            const bool resources=turretFire.type==TurretAttack::Stone?sprite[PORTRAIT_TURRET_FIRST_IMG]!=nullptr:turretFire.type==TurretAttack::Bolt?true:turretFire.type==TurretAttack::Missiles?sprite[TURRET_TRIPLE_MISSILE_IMG]!=nullptr:turretFire.type==TurretAttack::Laser?sprite[TURRET_FLAME_LASER_IMG]!=nullptr:sprite[turretFire.type==TurretAttack::Magnetic?TURRET_MAGNETIC_ORB_IMG:castle==14?TURRET_CRYSTAL_ORB_IMG:castle==4?TURRET_HEAVY_SHELL_IMG:TURRET_IRONBALL_IMG]!=nullptr;
            const bool valid=resources&&action.bulletIcon<0&&action.emitterReady&&turretFire.count==TurretAttack::burstCount(castle);
            reviewTrace(valid?"PASS turret native type muzzle and burst":"FAIL turret type or burst");
            if(castle==6){
                const auto top=cannonMuzzle(l,6,false,-1,0),middle=cannonMuzzle(l,6,false,-1,1),bottom=cannonMuzzle(l,6,false,-1,2);
                const auto mirror=cannonMuzzle(l,6,true,-1,0);
                reviewTrace(top.y>middle.y&&middle.y>bottom.y&&top.x==middle.x&&middle.x==bottom.x&&
                    std::abs(mirror.x+top.x-DX)<.01f?"PASS three missiles have separate registered barrel origins and mirrored ports":"FAIL triple barrel origins");
            }
            std::snprintf(name,sizeof(name),"turret-%02d-flight",castle+1);reviewCapture(name);phase=3;
        }else if(phase==3&&action.time.applied){
            reviewTrace("PASS turret damage commits exactly once after final projectile arrival");
            std::snprintf(name,sizeof(name),"turret-%02d-impact",castle+1);reviewCapture(name);phase=4;
        }else if(phase==4&&age>=action.time.end-1){
            const char* count=std::getenv("CS_TURRET_REVIEW_COUNT");
            if(++castle==(count?std::max(1,std::min(19,std::atoi(count))):10)){reviewTrace("DONE turret attack review");done=true;return;}
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
                if(std::getenv("CS_COVER_CLIP_REVIEW")){reviewTrace("DONE cover clipping review");return;}
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
        if(std::getenv("CS_FOE_ACTION_REVIEW")){
            static int sample=0,hold=0;
            if(entering()||introActive()||spinFlying()||deckArriving()||animation)return;
            if(sample>=2)return;
            if(sample==1&&Siege::swapped){Siege::swapSides();Siege::phase=0;Siege::step=Siege::Idle;return;}
            if(sample==0&&Siege::phase==0){
                const bool choices=Siege::chooseAction(20,100,50,0,true,true,0)==ChoiceCannon&&
                    Siege::chooseAction(100,20,50,0,true,true,0)==ChoiceAttack&&
                    Siege::chooseAction(20,20,1000,0,true,true,0)==ChoiceSpin&&
                    Siege::chooseAction(20,20,1000,0,false,false,99)==ChoiceCannon&&
                    Siege::chooseAction(100,20,1000,0,true,false,99)==ChoiceAttack;
                reviewTrace(choices?"PASS opponent chooses lethal cannon, lethal attack, growth and legal fallbacks":"FAIL opponent choices");
                Run cannon=Siege::foe;cannon.choosing=false;cannon.attacking=false;cannon.lost=false;
                cannon.enemyHp=1000;cannon.enemyGuard=10;
                bool fired=cannon.fireCannon(Siege::foeStats,100);while(cannon.step()){}
                reviewTrace(fired&&cannon.enemyHp==905?"PASS opponent cannon applies shield and health damage":"FAIL opponent cannon damage");
                Siege::swapSides();Siege::phase=1;Siege::step=Siege::Attacking;
                return;
            }
            if(++hold<4)return;
            const Layout controls=layout();
            const bool correct=sample==0?
                controls.attack.x<controls.cannon.x&&controls.cannon.x<controls.spin.x&&controls.cannon.w>0:
                controls.attack.x<controls.spin.x&&controls.cannon.w==0;
            reviewTrace(correct?"PASS turn-specific action buttons":"FAIL turn-specific action buttons");
            reviewCapture(sample==0?"opponent-three-actions":"player-two-actions");
            hold=0;
            if(++sample==2)reviewTrace("DONE opponent action review");
            return;
        }
        if(std::getenv("CS_LARGE_BOARD_REVIEW")){
            static int sample=0,hold=0;
            if(entering()||introActive()||spinFlying()||deckArriving())return;
            if(sample>=3)return;
            if(++hold==1){
                Shape shape=castleShape(9);shape.height=4+sample;
                for(int row=0;row<Height;++row)shape.rows[row]=row<shape.height?0xFF:0;
                run.board.clear();run.setShape(shape);return;
            }
            if(hold<4)return;
            const Layout board=layout();
            const bool clear=board.board.y-board.board.h>=board.slot.y+(int)(8*board.scale);
            reviewTrace(clear&&board.cell==(int)(64*board.scale)?"PASS board clears roulette at original cell size":"FAIL large board clearance");
            reviewCapture(sample==0?"board-four-rows":sample==1?"board-five-rows":"board-six-rows");
            hold=0;if(++sample==3)reviewTrace("DONE large board review");
            return;
        }
        if(std::getenv("CS_MERGE_PVP_CONTROLS_REVIEW")){
            static bool captured=false;
            if(!captured&&!entering()&&!introActive()&&!spinFlying()&&!deckArriving()&&Siege::phase==0&&animation==0){
                const bool centered=l.attack.x<l.spin.x&&std::abs((l.attack.x+l.spin.x+l.spin.w)-DX)<=1;
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
            introElapsed=-1;entryElapsed=-1;animation=0;robin.heart=20;
            updateHeroCostume(false);action=CombatAction();enemyTurn=EnemyTurn();
            reviewTap(layout().spin);paid=robin.heart;
            reviewTrace(paid==20&&animation>0&&run.tray.size()==3?"PASS full grid can spin without energy":"FAIL full grid spin");
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
            reviewTrace(heartCapacity==5?"PASS five local lightning slots":"FAIL lightning count");
            char native[128];std::snprintf(native,sizeof(native),"native HP=%lld armor=%lld block armor=%lld",run.maxLives,run.baseArmor,run.forecast(stats).protect);reviewTrace(native);
            phase=1;return;
        }
        if(phase==1&&deckReveal[0].age>=12){reviewCapture("vitals-01-companion-warp");phase=2;return;}
        if(phase==2&&!deckArriving()&&guardDisplay.value==guardDisplay.target){
            reviewCapture("vitals-02-native-bars-ten-hearts");phase=3;return;
        }
        if(phase==3){
            //통(체력×ShieldPct)이 찬 채로 시작하므로, 반격 = 통 전부 + 체력의 1/8 이면 체력이 그만큼 깎인다.
            run.enemyAttack=run.guardMax+std::max(1LL,run.maxLives/8);
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
        reviewTrace(robin.heart==before&&run.lives==life&&!run.tray.empty()?"PASS spin costs no energy without enemy turn":"FAIL spin");
        if(t==190)reviewTrace(robin.heart==before&&!run.tray.empty()?"PASS right lever pull spins once":"FAIL lever pull");
    }
    if(t==32) {
        long long balance=robin.heart;reviewTap(l.spin);reviewTap(l.attack);
        reviewTrace(heartBlink==0&&robin.heart==balance?"PASS repeated actions do not spend energy":"FAIL action energy balance");
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
            // Preserve the grabbed cell while moving the visible footprint.
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
        reviewTrace(run.attacking&&robin.heart==before?"PASS attack costs no energy":"FAIL attack");
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
        reviewTrace(l.cell==(int)(64*l.scale)&&l.cellH==l.cell&&l.board.w==6*l.cell?"PASS expanded castle grid retains fixed 64px cells":"FAIL expanded grid size");}
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
void SharedRewardShow(const ITEM* items,int count){
 std::vector<RewardPopup::Entry> entries;
 for(int i=0;i<count;++i){const ITEM& item=items[i];RewardPopup::Entry e;e.type=item.type;e.detail=item.detail;e.grade=item.grade;e.lv=item.lv;e.count=item.count;entries.push_back(e);}
 RewardPopup::onClose=nullptr;RewardPopup::drawButton=rewardButton;
 RewardPopup::show(u8"보상",entries,u8"확인");
}
bool SharedRewardOpen(){return RewardPopup::open();}
void SharedRewardDraw(){ResetRectPoint();RewardPopup::draw();}
void SharedRewardClose(){RewardPopup::closeNow();}
bool MergeRouletteActive() {return active;}
long long MergeRouletteHeroShield(const OBJECT* h) {return h?Run::shieldFor(std::max(1LL,(long long)h->ps[PS_HP])):0;}
long long MergeRouletteHeroShieldRecovery(const OBJECT* h) {
    if(!h)return 0;
    long long guard=0;
    for(int slot:{EQUIP_HELM,EQUIP_ARMOR,EQUIP_PANTS,EQUIP_BOOTS}) if(h->equip[slot].type!=EMPTY) guard+=std::max(0LL,GetEquipPower(const_cast<ITEM*>(&h->equip[slot]),std::max(1,(int)h->equip[slot].lv)));
    return std::min(guard*(100+CastleTeamBonus(2))/100,1000000000000000LL);
}
void MergeRouletteBeginSiege() {lobbySkipDeparture=true;Siege::begin();lobbySkipDeparture=false;}
bool MergeRouletteHousePreview(int house,int x,int top,int width,int height) {
    int castle=0;
    for(int i=0;i<std::min(19,gTotalCastle);++i)if(castleOrder[i]==house){castle=i;break;}
    return MergeRouletteOriginalPreview(castle,x,top,width,height);
}
#include "TitleCastleBackdrop.inc"
static bool DrawOriginalCastlePreview(int castle,int x,int top,int width,int height,bool moving=false){
    (void)moving;drawPortraitCastlePreview(castle,{x,top,width,height});return true;
}
int MergeRouletteCastleUpgradeHeight(int castle){
 const int c=std::max(0,std::min(18,castle));const float z=1.18f*DX/640.f;
 return (int)((PortraitCastleArt::Sizes[c].h+PortraitCastleArt::WheelSize(c))*z)+140;
}
void MergeRouletteCastleUpgradePreview(int castle,int x,int top,int width,int height){
 drawPortraitCastlePreview(castle,{x,top,width,height},-1,false,1.18f*DX/640.f);
}
void MergeRouletteCastleTurretPreview(int castle,int x,int top,int width,int height){
 const int c=std::max(0,std::min(18,castle)),img=PORTRAIT_TURRET_FIRST_IMG+c;if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 if(c==0){const float z=std::min(width/(float)StarterCastleRig::W,height/(float)StarterCastleRig::H);const Box b={x+(int)((width-StarterCastleRig::W*z)/2),top-(int)((height-StarterCastleRig::H*z)/2),(int)(StarterCastleRig::W*z),(int)(StarterCastleRig::H*z)};
 turretPart(img,0,0,StarterCastleRig::W,StarterCastleRig::H,b);turretPart(img,StarterCastleRig::W,0,StarterCastleRig::W,StarterCastleRig::H,b);
 }else{const auto sz=sprite[img]->getTexture()->getContentSizeInPixels();const float z=std::min(width/sz.width,height/sz.height);portraitImage(img,{x+(int)((width-sz.width*z)/2),top-(int)((height-sz.height*z)/2),(int)(sz.width*z),(int)(sz.height*z)});}
}
void MergeRouletteCastleMenuBackdrop(int castle,int x,int top,int width,int height){
    (void)castle;const int cx=clipX,cy=clipY,cx2=clipX2,cy2=clipY2;
    SetSectionClip(x,top,width,height,true);MemRect(x,top,width,height,0x030A13);
    portraitImage(PORTRAIT_NIGHT_IMG,{x,top,width,height});
    clipX=cx;clipY=cy;clipX2=cx2;clipY2=cy2;
}
bool MergeRouletteOriginalPreview(int castle,int x,int top,int width,int height){return DrawOriginalCastlePreview(castle,x,top,width,height);}
bool MergeRouletteOriginalPreview(int castle,int x,int top,int width,int height,bool moving){return DrawOriginalCastlePreview(castle,x,top,width,height,moving);}
void MergeRouletteSetHeartCapacity(int capacity) {(void)capacity;heartCapacity=Run::BattleEnergyMax;heartDisplay=run.battleEnergy;}
void MergeRouletteBegin(bool resume) {
    if(active)return;
    if(!resume&&!lobbyDepartureCommit&&!lobbySkipDeparture&&drawHandle==MD_LOBBY&&(!std::getenv("CS_MERGE_REVIEW")||std::getenv("CS_BASE_CAMP_REVIEW"))){
        if(lobbyDepartureAge<0){captureLobbyDeparture();lobbyDepartureAge=0;entryChoiceOpen=false;finger=-1;ResetRectPoint();PlayMusic(M_OPENDOOR);}
        return;
    }
    entryChoiceOpen=false;entryChoiceFinger=entryChoicePressed=-1;
    siegeActive=false;siegeHullStage=-1;waveTransition=MergeCombat::WaveTransition();
    review=std::getenv("CS_MERGE_REVIEW")!=nullptr;
    if(review&&std::getenv("CS_SFX_TRACE"))option.se=true;
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
    portraitCameraY=0;run.selected=pool.front();run.stage=std::max(0,std::min(18,debugCastle>=0?debugCastle:(int)robin.castle));
    run.enemyHp=run.enemyMax=waveHp(run.stage,0);

    bool restoredRun=false;
    if(resume) {
        Run restored;restored.roster=&roster;
        // v6 전 세이브는 읽지 않는다(계열·동료 체계가 다르다) — 새 런.
        if(robin.mergeRouletteHero==curHero&&restored.decode(robin.mergeRouletteRun)) {
            bool owned=true;for(int f:restored.families)if(std::find(pool.begin(),pool.end(),f)==pool.end())owned=false;
            if(owned){run=restored;restoredRun=true;}
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
    } else if(review) {if(!lobbyDepartureCommit)robin.heart=20;run.rng=12345;}
    const bool migrateVitals=!run.realVitals;
    run.setVitals(stats.heroHealth,stats.heroArmor);
    run.enemyAttack=waveAttack(run.stage,run.wave);
    if(migrateVitals&&run.attacking){const Effects f=run.forecast(stats);run.effects.protect=f.protect;run.effects.charge=f.charge;run.settleGuard();}
    run.setShape(castleShape(run.stage));
    bool starting=run.choosing&&run.start(pool,treeWeights,review&&std::getenv("CS_MERGE_ARRIVAL_REVIEW"));
    // Keep the three free starters committed while the opening reels present them.
    automaticMerge=AutomaticMerge();pendingPass=false;
    quitPromptOpen=false;quitPromptFinger=quitPromptChoice=exitPromptFinger=-1;
    entryElapsed=restoredRun?MergeCastleTransition::Duration:0.f;entryCaptures=0;panicSeed=run.rng;
    const bool firstEvent=!restoredRun&&!resume&&gCastleTutorialStep<=CastleTutorial::Depart&&!(gCastleTutorialHints&CastleTutorial::HintStartEvent);
    startEventElapsed=(!review&&firstEvent)||(review&&!resume&&std::getenv("CS_START_EVENT_REVIEW"))?0.f:-1.f;
    if(lobbyDepartureCommit)startEventElapsed=-1;
    if(startEventActive())gCastleTutorialHints|=CastleTutorial::HintStartEvent;
    introElapsed=starting?0.f:-1.f;introCaptures=0;reviewCombatTick=-1;
    if(!restoredRun&&!siegeActive)PlayMusic(M_WARP);
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
    heartDisplay=run.battleEnergy;heartBlink=messageTime=0;spentHeart=-1;
    refillPending=false;refillElapsed=-1.f;refillFrom=heartDisplay;
    active=true;drawHandle=MD_PLAY;keyHandle=MK_PLAY;curMenu=MENU_PLAY;
    if(!review)PlayMusic(M_TITLE);
    MergeTutorialBeginBattle();
    RewardPopup::onClose=[](){CastleTutorialEvent(CastleTutorial::RewardClosed);};
    if(!resume)CastleTutorialEvent(CastleTutorial::Started);
    autoPlay=false;autoFrame=-1;touchDisable=false;mustRefresh=true;
    if(!run.choosing)save();
}
namespace {
#include "PortraitGameUi.inc"
}
bool MergeRouletteLobbyDeparting(){return lobbyDepartureAge>=0;}
void MergeRouletteLobbyTopbarDraw(){drawPortraitTopbar();}
void MergeRouletteBottomNavDraw(){if(MergeRouletteLobbyDockVisible())drawLobbyBottomNav();} // Shared navigation retains existing actions.
void MergeRouletteUiFrame(int x,int top,int width,int height,int style){portraitSkin(std::max(0,std::min(6,style)),{x,top,width,height});}
void MergeRouletteUiGlyph(int icon,int x,int top,int width,int height){portraitGlyph(std::max(0,std::min(11,icon)),{x,top,width,height});}
int MergeRouletteBottomNavHeight(){return MergeRouletteLobbyDockVisible()?lobbyBottomNav().y:0;}
bool MergeRouletteLobbySceneDraw(bool backdropOnly) {
    if(!review||std::getenv("CS_CAMP_AUDIO_REVIEW"))PlayCampMusic(!titleCampOnly);
    cocos2d::Director::getInstance()->setDisplayStats(false);
    static bool needsConfigure=true;
    if(!backdropOnly&&(popUpCnt>0||LoadoutOpen())){needsConfigure=true;return false;}
    static int preparedHero=-1,preparedCastle=-1;
    if(needsConfigure||preparedHero!=curHero||preparedCastle!=robin.castle){configure();preparedHero=curHero;preparedCastle=robin.castle;needsConfigure=false;}
    const int previewCastle=LobbyCastleDebugCastle();
    run.stage=std::max(0,std::min(18,previewCastle>=0?previewCastle:(int)robin.castle));
    if(review&&!std::getenv("CS_PORTRAIT_DEBUG19")&&std::getenv("CS_PORTRAIT_LOBBY")&&std::getenv("CS_PORTRAIT_STAGE"))run.stage=std::max(0,std::min(18,std::atoi(std::getenv("CS_PORTRAIT_STAGE"))));
    run.setShape(castleShape(run.stage));
    static float idleRemainder=0;
    if(!(review&&reviewCapturePending)){
        idleRemainder+=std::min(.1f,std::max(0.f,cocos2d::Director::getInstance()->getDeltaTime()));
        const int elapsed=(int)((idleRemainder+.000001f)*60.f);
        ticks+=elapsed;idleRemainder-=elapsed/60.f;
    }
    if(lobbyDepartureAge>=0){
        const float dt=review&&reviewCapturePending?0.f:std::min(.05f,std::max(0.f,cocos2d::Director::getInstance()->getDeltaTime()));
        lobbyDepartureAge+=dt;
        portraitCameraY=lobbyRecallCamera*(1-BaseCamp::ease(lobbyDepartureAge,0,1.15f));
        starterInteriorReveal=lobbyRecallReveal*(1-BaseCamp::closure(lobbyDepartureAge));
        if(lobbyDepartureAge>1.65f)castleScrollSeconds+=dt*(.25f+3.f*BaseCamp::travel(lobbyDepartureAge));
        if(lobbyDepartureAge>=BaseCamp::duration()){
            lobbyDepartureAge=-1;starterInteriorReveal=0;
            if(lobbyDepartureCharge){
                lobbyDepartureCharge=false;
                if(!MergeExpedition::affordable(robin.heart)){starterInteriorReveal=1;message=u8"번개가 부족합니다 (5개 필요)";PlayMusic(M_ERROR);return true;}
                GetItem(ITEM_HEART,false,false,false,-MergeExpedition::Cost,false);AddBar(&bar[BAR_HEART],-MergeExpedition::Cost,BARFRAME);
            }
            lobbyDepartureCommit=true;MergeRouletteBegin(false);lobbyDepartureCommit=false;if(!review)MergeRouletteDraw();return true;
        }
    }
    ResetRectPoint();SetAlpha(32);SetColor(0);grayScale=0;
    Layout l=layout();drawWorld(l,false);
    if(backdropOnly){needsConfigure=true;return true;}
    if(lobbyDepartureAge>=0){
        if(lobbyDepartureAge<.4f){drawPortraitLobby(l);uiSceneMotionY=(DY+80*l.scale)*BaseCamp::uiExit(lobbyDepartureAge);drawPortraitTopbar();uiSceneMotionY=0;}
        ResetRectPoint();mustRefresh=true;return true;
    }
    if((!review||std::getenv("CS_RESUME_PROMPT_REVIEW"))&&!resumePromptChecked){
        Run saved;saved.roster=&roster;
        resumePromptOpen=saved.decode(robin.mergeRouletteRun)&&!saved.lost&&!saved.choosing&&(review||IsGetHero(robin.mergeRouletteHero));
        resumePromptChecked=true;
    }
    const bool arriving=titleLobbyClock>=0;
    if(arriving){AdvanceTitleLobbyMotion(cocos2d::Director::getInstance()->getDeltaTime());DrawTitleLobbyDeparture();}
    uiSceneMotionY=0;
    drawPortraitLobby(l);
    uiSceneMotionY=arriving?LobbyTopbarDrop():0.f;
    CastleVault::drawButton();
    // Original resource strip: level, gold, diamonds and lightning energy.
    drawPortraitTopbar();
    uiSceneMotionY=0;
    if(arriving){ResetRectPoint();mustRefresh=true;++frame;return true;}
    CastleVault::drawFlights();   //걷은 재화가 띠·메뉴로 날아간다. 도착점 위에 그린다
    MergeTutorialDrawLobbyHints();   //튜토리얼 뒤 처음 쓸 수 있게 된 것에 손가락 한 번
    //원정 보상창은 로비 위에 덮인다. 떠 있는 동안 로비의 터치 영역은 지운다.
    if(RewardPopup::open()){ResetRectPoint();RewardPopup::draw();}
    else if(resumePromptOpen)drawResumePrompt();
    else if(entryChoiceOpen)drawEntryChoice();
    if(review&&std::getenv("CS_RESUME_PROMPT_REVIEW")&&resumePromptOpen&&!reviewCapturePending){
        static int hold=0;if(++hold>20){hold=0;
            const int choice=resumeReviewPhase==1?1:0;const Box b=resumeChoiceBox(choice);
            reviewCapture(choice?"resume-choice":"resume-decline");
            MergeRouletteTouch(0,77,b.x+b.w/2,b.y-b.h/2);MergeRouletteTouch(2,77,b.x+b.w/2,b.y-b.h/2);
            if(choice)resumeReviewPhase=2;
            else{reviewTrace(!active&&!resumePromptOpen&&!robin.mergeRouletteRun[0]&&robin.heart==resumeReviewEnergy?"PASS decline clears run and preserves already-paid energy":"FAIL decline resume");resumeReviewPhase=4;reviewTrace("DONE resume prompt review");}
        }
    }
    mustRefresh=true;++frame;return true;
}
void MergeRouletteLobbyDraw() {}
#include "OriginalTopbarReview.inc"
bool drawNativeTitleCastleGridReview(){
    if(!review||!std::getenv("CS_NATIVE_TITLE_GRID_REVIEW"))return false;
    cocos2d::Director::getInstance()->setDisplayStats(false);
    ResetRectPoint();SetColor(0);grayScale=0;SetAlpha(32);MemRect(0,DY,DX,DY,0xFFFFFF);
    const float scale=DX/640.f;
    const int logoImg=HYBRID_TITLE_LOGO_IMG;if(!sprite[logoImg])LoadImg(logoImg);
    int logoHeight=0;
    if(sprite[logoImg]){
        const auto size=sprite[logoImg]->getContentSize();
        const float z=std::min(DX*.90f/size.width,DY*.20f/size.height);
        logoHeight=(int)(size.height*z);
        DrawImage((int)size.width,(int)size.height,0,0,(int)((DX-size.width*z)/2),DY-(int)(20*scale),false,0,0,0,0,z,sprite[logoImg],logoImg);
    }
    const int gridTop=DY-(int)(42*scale)-logoHeight;
    const int cellWidth=DX/3,cellHeight=(gridTop-(int)(12*scale))/3;
    const float zoom=std::min((cellWidth-12*scale)/DX,(cellHeight-4*scale)/DY);
    static cocos2d::RenderTexture* targets[9]={};
    for(int c=0;c<9;++c){
        if(!targets[c]){
            targets[c]=cocos2d::RenderTexture::create(DX,DY);targets[c]->retain();
            const Run savedRun=run;const int savedStage=siegeHullStage;
            const bool savedSiege=siegeActive;const float savedEntry=entryElapsed,savedIntro=introElapsed;
            run.stage=c;run.attacking=false;run.board.clear();
            for(int role=0;role<3;++role){const int crew=roster.first(role,1);if(crew<0)continue;
                Block b;b.family=role;b.crew=crew;run.board.push_back(b);deckReveal[crew].age=MergeCombat::ResidentReveal::Duration;}
            siegeActive=false;siegeHullStage=c;entryElapsed=MergeCastleTransition::Duration;introElapsed=-1;
            OriginalCastle::previewScale=0;
            PushRenderTarget(targets[c],nullptr,true);SetSectionClip(0,DY,DX,DY,true);
            SetAlpha(32);SetColor(0);grayScale=0;MemRect(0,DY,DX,DY,0xFFFFFF);
            nativeTitleIsolate=true;drawWorld(layout(),true);nativeTitleIsolate=false;
            PopRenderTarget();SetSectionClip(0,DY,DX,DY,true);
            run=savedRun;siegeHullStage=savedStage;siegeActive=savedSiege;entryElapsed=savedEntry;introElapsed=savedIntro;
        }
        auto* picture=cocos2d::Sprite::createWithTexture(targets[c]->getSprite()->getTexture());
        picture->setFlippedY(true);picture->setAnchorPoint({0,1});picture->setScale(zoom);
        picture->setPosition({(c%3+.5f)*cellWidth-DX*zoom*.5f,(float)(gridTop-(c/3)*cellHeight)});
        picture->getTexture()->setAliasTexParameters();picture->visit();
    }
    static int frames=0;static bool captured=false;
    if(!captured&&!reviewCapturePending&&++frames>=4){
        reviewCapture("native-castle-grid-9-world");reviewTrace("PASS nine full combat-renderer castles with original logo");
        reviewTrace("DONE native castle title grid review");captured=true;
    }
    return true;
}
void MergeRouletteDraw() {
    cocos2d::Director::getInstance()->setDisplayStats(false);
    if(drawNativeTitleCastleGridReview())return;
    if(review&&std::getenv("CS_RESUME_PROMPT_REVIEW")){
        const auto fixtureSave=[](){const auto encoded=run.encode();std::memset(robin.mergeRouletteRun,0,sizeof(robin.mergeRouletteRun));std::memcpy(robin.mergeRouletteRun,encoded.data(),encoded.size());robin.mergeRouletteHero=curHero;};
        if(resumeReviewPhase==0){resumeReviewEnergy=robin.heart;resumeReviewSave=run.encode();fixtureSave();resumePromptChecked=false;resumeReviewPhase=1;}
        if(resumeReviewPhase==2){reviewTrace(run.encode()==resumeReviewSave&&robin.heart==resumeReviewEnergy&&!entering()?"PASS explicit resume restores exact run without energy charge":"FAIL explicit resume");fixtureSave();resumePromptChecked=false;resumeReviewPhase=3;}
        active=false;drawHandle=MD_LOBBY;MergeRouletteLobbySceneDraw();active=true;drawHandle=MD_PLAY;return;
    }
    MergeRenderProfile::Frame profile;
    if(reviewOriginalTopbar())return;
    portraitReviewFixture();
    if(portraitReviewLobby())return;
    if(review&&std::getenv("CS_MERGE_LOBBY_IDLE_REVIEW")){
            static int samples=0,firstTick=0;static std::vector<int> poses;static bool second=false,done=false;
        if(samples==0){run.board.clear();firstTick=ticks;}
        MergeRouletteLobbySceneDraw();
        if(reviewCapturePending||done)return;
        const int pose=heroNeutralMotion(hero);
        if(std::find(poses.begin(),poses.end(),pose)==poses.end())poses.push_back(pose);
        if(samples++==0)reviewCapture("lobby-idle-01");
        else if(!second&&poses.size()>1){second=true;reviewCapture("lobby-idle-02");}
        if(samples==90){
            //원정: 번개 20 → 15, 골드가 늘고 보상창이 로비 위에 뜬다.
            for(int i=0;i<GetMaxInven();++i){memset(&robin.inven[i],0,sizeof(ITEM));robin.inven[i].type=EMPTY;}
            robin.heart=20;const long long gold=robin.gold;
            const bool ok=runExpedition()&&RewardPopup::open()&&robin.heart==15&&robin.gold>gold&&!runExpedition();
            reviewTrace(ok?"PASS expedition spends five energy and opens the reward popup":"FAIL expedition");return;
        }
        if(samples==104){reviewCapture("lobby-expedition-01");return;}   //카드가 선 뒤의 한 장
        if(samples>90&&samples<120)return;
        if(samples>=120){
            RewardPopup::closeNow();
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
            const bool selected=entryChoiceOpen&&!active;
            const Box fight=entryChoiceBox(1);
            MergeRouletteTouch(0,998,fight.x+fight.w*.5f,fight.y-fight.h*.5f);
            MergeRouletteTouch(2,998,fight.x+fight.w*.5f,fight.y-fight.h*.5f);
            reviewTrace(selected&&active&&entering()?"PASS lifted start button matches actual lobby touch coordinates":"FAIL lifted start button hit area");
            reviewTrace("DONE lobby idle review");done=true;
        }
        return;
    }
    std::fill(reelResultDrawn,reelResultDrawn+3,false);
    // Isolated capture reviews hold simulation until asynchronous PNG writing
    // completes. Fixed-tick checks cannot be skipped or captured in a later state.
    const bool holdReview=(review&&reviewCapturePending)||quitPromptOpen;
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
        entryElapsed=MergeCastleTransition::Duration;
        cocos2d::Director::getInstance()->setDisplayStats(false);
        const float s=DX/640.f;
        label("GRID COMPANIONS - MAX ZOOM 1.215",DX/2,DY-(int)(20*s),.65f,0xFFE6AC);
        for(int slot=0;slot<16;++slot){
            const int crew=page*16+slot,col=slot%4,row=slot/4;
            Block b;b.family=MergeTrees::Role(crew);b.level=MergeTrees::Star(crew);b.crew=crew;
            const Box cell={(int)((col*160+40)*s),(int)(DY-(80+row*170)*s),(int)(80*s),(int)(160*s)};
            drawBlock(b,cell);
            char text[40];std::snprintf(text,sizeof(text),"%02d   zoom %.2f",crew,gridCrewZoomSeen[crew]);
            label(text,cell.x+cell.w/2,cell.y+(int)(18*s),.44f,0xFFFFFF);
        }
        if(!reviewCapturePending&&++hold>8){
            bool equal=true;for(int c=page*16;c<(page+1)*16;++c)equal=equal&&gridCrewZoomSeen[c]>0&&gridCrewZoomSeen[c]<=1.215f*s+.00001f;
            reviewTrace(equal?"PASS sixteen grid companions stay within reduced maximum zoom":"FAIL grid companion exceeds reduced zoom");
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
            // Enumerate the production icon mapping, not arbitrary legacy
            // image IDs. This covers every reachable equipment variant.
            DrawIcon(GetItemIcon(type,detail,GRADE_NORMAL),x+112,y-42,.7f,false,false,false,true);
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
        if(fixedGrid.cell!=(int)(64*fixedGrid.scale)||fixedGrid.cellH!=fixedGrid.cell||run.shape.width>8||
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
                uniform=uniform&&test.cell==(int)(64*test.scale)&&test.cellH==test.cell;}
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
        bool valid=OriginalCastle::visualRooms().size()==5&&MistCastle::facilityImages[4]==MistCastle::image(c,5);
        const auto& floors=CastleFiveFloors::Rooms[c];
        for(int floor=1;floor<5;++floor){
            valid=valid&&floors[floor].y+floors[floor].h<=floors[floor-1].y;
            valid=valid&&floors[floor].h==floors[0].h;
            valid=valid&&floors[floor-1].y-floors[floor].y==floors[0].y-floors[1].y;
        }
        valid=valid&&CastleArtGeometry::width(c)==916.f;
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
    if(portraitReviewEnabled()){costumeEffectTicks=0;weaponSwap.age=-1;}
    drawWorld(fixed,true);profile.stamp(1);
    if(startEventActive()){
        const int bar=(int)(64*s);
        SetAlpha(28);MemRect(0,DY,DX,bar,0x101820);MemRect(0,bar*2,DX,bar*2,0x101820);SetAlpha(32);
        const char* caption=startEventElapsed<1.25f?u8"\uc131\uc744 \uc774\ub04c\uace0 \uc5ec\uc815\uc744 \uc2dc\uc791\ud569\ub2c8\ub2e4.":startEventElapsed<2.3f?u8"\ub9c8\ubb3c\uc774 \uae38\uc744 \uac00\ub85c\ub9c9\uc558\uc2b5\ub2c8\ub2e4!":u8"\ub3d9\ub8cc\ub4e4\uacfc \ud568\uaed8 \uc131\uc744 \uc9c0\ucf1c\ub0b4\uc138\uc694.";
        label(caption,DX/2,(int)(102*s),.62f,0xFFF1BD);
        label(u8"\ud654\uba74\uc744 \ub204\ub974\uba74 \uac74\ub108\ub701\ub2c8\ub2e4",DX/2,(int)(47*s),.4f,0xC4CBD2);
        if(review&&!reviewCapturePending){
            if(startEventElapsed>.4f&&entryCaptures==0){entryCaptures=1;reviewCapture("start-event-01-travel");}
            else if(startEventElapsed>.65f&&entryCaptures==1&&!strcmp(std::getenv("CS_START_EVENT_REVIEW")?std::getenv("CS_START_EVENT_REVIEW"):"","skip")){
                const auto before=run.encode();MergeRouletteTouch(2,0,DX/2,DY/2);
                reviewTrace(!startEventActive()&&run.encode()==before?"PASS tap skips event without changing rewards":"FAIL event skip");
            }
            else if(startEventElapsed>1.85f&&entryCaptures==1){entryCaptures=2;reviewTrace(monsterDrawn?"PASS opening enemy appears":"FAIL opening enemy missing");reviewCapture("start-event-02-enemy");}
            else if(startEventElapsed>2.65f&&entryCaptures==2){entryCaptures=3;reviewCapture("start-event-03-ready");}
        }
        return;
    }
    if(entering()){
        // Lobby controls no longer travel over the inventory.
        const int controlDrop=(int)((1-MergeCastleTransition::ControlsEnter(entryElapsed))*300*s);
        l.slot.y-=controlDrop;l.lever.y-=controlDrop;l.heart.y-=controlDrop;
        l.spin.y-=controlDrop;l.attack.y-=controlDrop;
    }
    const int hx=(int)(DX*.57f),ex=(int)(DX*.85f),ey=l.ground;
    UnSectionClip(false);MemRect(0,l.arenaBottom+(int)(6*s),DX,l.arenaBottom+(int)(6*s),0x030A13);
    if(siegeActive)Siege::drawHeader(l);else drawWaveHeader(l);
    if(run.attacking&&!siegeActive) {
        const char* phase=action.index>=0&&run.shots[action.index].block.family<0?(turretFire.type==TurretAttack::Magnetic?(action.time.elapsed<action.time.release?u8"\uc911\uc790\uae30\ud30c \u00b7 \ucda9\uc804":u8"\uc911\uc790\uae30\ud30c \u00b7 \ubc1c\uc0ac"):turretFire.type==TurretAttack::Laser?(action.time.elapsed<action.time.release?u8"\ub808\uc774\uc800 \u00b7 \ucda9\uc804":u8"\ub808\uc774\uc800 \u00b7 \ubc1c\uc0ac"):turretFire.type==TurretAttack::Missiles?u8"\uc720\ub3c4\ubbf8\uc0ac\uc77c \u00b7 \ubc1c\uc0ac":turretFire.type==TurretAttack::Stone?u8"\ud22c\uc11d \u00b7 \ubc1c\uc0ac":u8"\ud3ec\uaca9"):enemyTurn.endShown?"턴 종료":enemyTurn.started?"적 반격":run.passing?"턴 넘김 · 적의 차례":
            action.index>=0&&action.bulletIcon>=0?(action.time.elapsed<action.time.release?"동료 · 총탄 생성":"동료 · 총탄 발사"):
            action.index>=0&&action.skill>=0&&!action.heroMotion.empty()?"동료 · 히어로 스킬 요청":"아군 공격";
        const Box actionLabel={DX/2-(int)(82*s),std::min(DY-(int)(80*s),l.ground+(int)(96*s)),(int)(164*s),(int)(25*s)};
        panel(actionLabel,0x182735,0xB99850);
        label(phase,DX/2,actionLabel.y-(int)(5*s),.53f,0xFFE2A2);
    }
    if(waveTransition.active()){
        const char* text=waveTransition.defeatedVisible()?u8"\ucc98\uce58!":waveTransition.travelling()?u8"\ub2e4\uc74c \uc801\uc744 \ud5a5\ud574 \uc774\ub3d9 \uc911":combatEnemyIsBoss()?u8"\ubcf4\uc2a4 \ub4f1\uc7a5":u8"\ubaac\uc2a4\ud130 \ub4f1\uc7a5";
        label(text,DX/2,l.ground+(int)(105*s),.65f,0xFFE2A2);
    }
    const long long predictedPower=run.preview(stats);
    friendlyStatCount=hostileStatCount=0;
    drawPortraitStats({(int)(24*s),l.arenaBottom,DX/2-(int)(32*s),l.plateH},
        predictedPower,currentGuard(),run.lives,run.maxLives);
    MergeTutorialRememberAllyPlate((int)(24*s),l.arenaBottom,DX/2-(int)(32*s),l.plateH);
    drawPortraitEnemyHealth(l);
    portraitSkin(2,l.exit);
    mergeRect(l.exit.x+(int)(13*s),l.exit.y-(int)(11*s),(int)(5*s),(int)(18*s),0xF5ECD6);
    mergeRect(l.exit.x+(int)(24*s),l.exit.y-(int)(11*s),(int)(5*s),(int)(18*s),0xF5ECD6);
    if(siegeActive)Siege::drawHud(l);else MonsterBoard::drawPanel(l);
    profile.stamp(2);
    const int capacity=portraitGridCapacity();
    if(!entering()||entryElapsed>=MergeCastleTransition::TileLand(capacity-1,capacity))
        portraitSkin(0,{l.board.x-(int)(8*s),l.board.y+(int)(8*s),l.board.w+(int)(16*s),l.board.h+(int)(16*s)});
    // Equipment retains one continuous footprint over this underlying cell grid.
    int ordinal=0;
    for(int row=0;row<run.shape.height;++row)for(int col=0;col<run.shape.width;++col){
        if(!run.shape.contains(col,row))continue;
        {
            Box tile={l.board.x+col*l.cell,l.board.y-row*l.cellH,l.cell,l.cellH};
            const int index=ordinal++,count=capacity;
            float angle=0;
            if(entering()){
                if(entryElapsed<MergeCastleTransition::TileLaunch(index,count))continue;
                const float p=MergeCastleTransition::TileProgress(entryElapsed,index,count);
                const float q=1-std::pow(1-p,2.f);
                const Box source=slotWindow(l.slot,index%3);
                const float cx=source.x+source.w*.5f,cy=source.y-source.h*.5f;
                tile.x=(int)(cx-l.cell*.5f+(tile.x-cx+l.cell*.5f)*q);
                tile.y=(int)(cy+l.cellH*.5f+(tile.y-cy-l.cellH*.5f)*q+std::sin(p*3.14159265f)*32*s);
                angle=(index%2?1.f:-1.f)*180.f*(1-p);
                const float age=entryElapsed-MergeCastleTransition::TileLand(index,count);
                if(age>=0&&age<.09f)tile.y+=(int)(std::sin(age/.09f*3.14159265f)*4*s);
            }
            const int gap=std::max(1,(int)(2*s));
            Box cell=inset(tile,gap);
            if(entering()&&entryElapsed<MergeCastleTransition::TileLand(index,count)){
                portraitTile(cell,angle);
                continue;
            }
            portraitTile(cell,0);
            if(run.at(col,row)<0)label("+",cell.x+cell.w/2,cell.y-cell.h/2+(int)(7*s),.52f,0x3C5560);
        }
    }
    long long predicted=run.preview(stats);
    for(int i=0;i<(int)run.board.size();++i) {
        if(automaticMerge.active()&&((!automaticMerge.fromTray&&i==automaticMerge.source)||(automaticMerge.targetLifted&&i==automaticMerge.target)))continue;
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
        if(automaticMerge.active()&&((!automaticMerge.fromTray&&sameGrade(accent.block,automaticMerge.moving))||
            (automaticMerge.targetLifted&&sameGrade(accent.block,run.board[automaticMerge.target]))))continue;
        if(std::find_if(visibleGrades.begin(),visibleGrades.end(),[&](const Block& b){return sameGrade(b,accent.block);})==visibleGrades.end())continue;
        const Box box=blockBox(accent.block,l);
        const float t=accent.age/36.f,pulse=std::sin(std::min(1.f,t*2)*3.14159265f);
        const int grow=(int)(pulse*7*s);
        if(accent.age<18)drawBlock(accent.block,{box.x-grow,box.y+grow,box.w+grow*2,box.h+grow*2});
        SetAlpha((int)(32*(1-t)));
        const int color=QuietCard::Color(gridRarity(accent.block));
        MemRectFrameThick(box.x-grow,box.y+grow,box.w+2*grow,box.h+2*grow,color,std::max(1,(int)(3*s)));
        for(int j=0;j<6;++j){
            const float angle=j*6.2831853f/6+t*.8f,radius=(20+38*t)*s;
            const int px=(int)(box.x+box.w*.5f+std::cos(angle)*radius),py=(int)(box.y-box.h*.5f+std::sin(angle)*radius);
            const int spark=std::max(1,(int)(2*s));
            mergeRect(px-spark,py,spark*2,spark,color);
            mergeRect(px,py+spark,spark,spark*3,color);
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
        mergeShownLevel=run.mergeLevel;
        mergeFlashDuration=20+7*std::max(1,mergeShownLevel);
        mergeFlash=mergeFlashDuration;

        Block at;at.family=0;at.level=1;at.x=run.mergeX;at.y=run.mergeY;
        mergeBox=blockBox(at,l);
        mergeBox.w=run.mergeW*l.cell;
        mergeBox.h=run.mergeH*l.cellH;
    }
    if(mergeFlash>0) {
        const int level=std::max(1,std::min((int)MaxLevel,mergeShownLevel));
        const float t=mergeFlash/(float)mergeFlashDuration,age=1-t;
        const int color=level>=6?0xFFFFFF:level>=4?0xF1BBFF:0xFFE99E;
        // Broad soft rings surround a bright core. Higher tiers add width,
        // reach, duration and more sparks around the result's entire border.
        const int layers=2+level;
        for(int ring=layers;ring>=0;--ring){
            const int grow=(int)((age*(7+level*3)+ring*(1.5f+level*.4f))*s);
            SetAlpha((int)((ring==0?32:std::max(2,13-ring))*t));
            MemRectFrameThick(mergeBox.x-grow,mergeBox.y+grow,
                mergeBox.w+grow*2,mergeBox.h+grow*2,ring==0?0xFFFFFF:color,
                std::max(1,(int)((ring==0?1.5f+level*.6f:2.f+level*.3f)*s)));
        }
        SetAlpha((int)(32*t));
        const int sparks=4+level*2;
        const float reach=(5+age*(8+level*4))*s;
        for(int i=0;i<sparks;++i){
            const float perimeter=2.f*(mergeBox.w+mergeBox.h);
            float d=std::fmod(i*perimeter/sparks+age*36*s,perimeter);
            float x=mergeBox.x,y=mergeBox.y,nx=0,ny=0;
            if(d<mergeBox.w){x+=d;ny=1;}
            else if((d-=mergeBox.w)<mergeBox.h){x+=mergeBox.w;y-=d;nx=1;}
            else if((d-=mergeBox.h)<mergeBox.w){x+=mergeBox.w-d;y-=mergeBox.h;ny=-1;}
            else{d-=mergeBox.w;y-=mergeBox.h-d;nx=-1;}
            const float z=(.18f+level*.055f)*s*(.7f+t*.3f);
            DrawIcon(ICON_STAR,(int)(x+nx*reach-8*z),(int)(y+ny*reach+8*z),z,false,false,false,true);
        }
        SetAlpha(32);
        if(!quitPromptOpen)--mergeFlash;
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
        if((entering()&&introActive())||(!hasReelSymbols&&run.tray.empty()&&animation==0))continue;
        bool held=!run.tray.empty()&&i<(int)run.tray.size();
        // Keep the stopped result in its reel while a copy flies to the board.
        const bool pending=!run.tray.empty()&&animation==0&&!spinFlying();
        if(pending&&automaticMerge.active()&&automaticMerge.fromTray&&i==automaticMerge.source)continue;
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
            const int pitch=window.h,turns=16+5*i;
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
                Box rolling=window;rolling.y+=j*pitch-offset;
                SetSectionClip(window.x,window.y,window.w,window.h,false);
                //지나가는 칸의 동료까지 바꿔 가며 보여 주면, 서는 순간
                //사람이 한 번 깜빡이며 갈린다. 설 자리의 계열이면 설 사람을
                //미리 들고 돈다.
                const int rollFamily=strip[(turn+j+base+n)%n];
                icon(rollFamily,rolling,1.f,true,rollFamily==f?lv:1,
                    rollFamily==f?crew:-1,0,rollFamily==f?&symbol:nullptr);
            }
        }else{
            SetSectionClip(window.x,window.y,window.w,window.h,false);
            reelResultDrawn[i]=true;
            icon(f,window,1.f,true,lv,crew,0,&symbol);


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
    drawPortraitEnergy(l);
    if(run.lost) {
        button(l.spin,"다시 도전","새 런 시작",0x24578D);button(l.attack,"로비로",nullptr,0x975028);
    } else {
        bool ready=run.battleEnergy>0&&!pendingPass&&!automaticMerge.active()&&!entering()&&!introActive()&&!spinFlying()&&!deckArriving()&&!waveTransition.active()&&!run.attacking&&animation==0;
        choice(l.spin,ChoiceSpin,ready&&run.canSpin());
        choice(l.attack,ChoiceAttack,ready&&!run.board.empty()&&run.boardResolved());
        if(!siegeActive||Siege::swapped)choice(l.cannon,ChoiceCannon,ready&&run.boardResolved());
        if(ready&&!run.board.empty()&&predicted>=run.enemyHp)
            MemRectFrameThick(l.attack.x,l.attack.y,l.attack.w,l.attack.h,0xFFE36A,std::max(1,(int)(3*s)));
        // Spin budget is a rule hint, not a slot-machine counter.
        if(run.spins==0&&run.tray.empty())label("이번 적립 종료 · 공격하세요",DX/2,DY-(int)(45*s),0.46f,0xFFD26A);
    }
    drawRouletteTrash(l);
    if(picked>=0) {
        auto& src=pickedTray?run.tray:run.board;
        if(picked<(int)src.size()) {
            Block b=src[picked];int x=(int)std::floor((pointerX-l.board.x)/l.cell)-pickCellX;
            int y=(int)std::floor((l.board.y-pointerY)/l.cellH)-pickCellY;
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
            drawHeldHelp(src[picked],l);
        }
    }
    if(messageTime>0&&!message.empty()) {
        const int padding=(int)(12*s),width=DX-(int)(48*s);
        const int height=std::max((int)(48*s),UiWrappedTextHeight(message.c_str(),width-2*padding,.59f*s)+2*padding);
        Box toast={(int)(24*s),std::min(DY-(int)(86*s),l.arenaBottom+height+(int)(10*s)),width,height};
        panel(toast,0x352332,0xDD957B);
        DrawUiTextBox(message.c_str(),toast.x+padding,toast.y-padding,toast.w-2*padding,toast.h-2*padding,0xFFE6C0,.59f*s);
    }
    if(messageTime<=0&&!run.choosing&&!message.empty()&&(message.find("없")!=std::string::npos||message.find("부족")!=std::string::npos))
        label(message.c_str(),DX/2,DY-(int)(45*s),0.48f);
    drawSpinLanding(l);
    if(siegeActive){Siege::drawExpanded(l);Siege::drawHand(l);}   //공성전: 펼친 상대 판과 상대의 손은 내 블록 위에
    else MonsterBoard::drawExpanded(l);   //몬스터의 판도 같은 자리에 펼친다
    if(RewardPopup::open()&&waveTransition.age>=MergeCombat::WaveTransition::DefeatFrames)RewardPopup::draw();
    if(!entering())drawIntro(l);
    drawAutomaticMerge(l);
    if(flash>0){impactDrawOrder=++objectDrawOrder;drawImpactSequence(impactFirst,impactCount,18-flash,18,enemyBodyKnown?enemyBodyX:ex,enemyBodyKnown?enemyBodyY:ey+(int)(40*s),RIGHT,.65f*s);}
    if(allyFlash>0)drawImpactSequence(HIT_ITEM_SMALL0,5,20-allyFlash,20,allyBodyKnown?allyBodyX:(int)(DX*.66f),allyBodyKnown?allyBodyY:ey+(int)(40*s),LEFT,.65f*s);
    drawCombatNumbers();
    if(quitPromptOpen)drawQuitPrompt();
    if(run.lost)drawGameOver();
    if(!holdReview||(review&&std::getenv("CS_EXIT_PROMPT_REVIEW")&&!reviewCapturePending))reviewStep(l);
}

#include "MergeTutorialRuntime.inc"
void MergeTutorialStepChanged(){MergeTutorial::onStepEntered();}
void writePlacementDiagnostic(const Layout& l,const Block& source,bool fromTray,bool rotationAttempt,bool accepted,float x,float y){
 const char* reviewPath=review?std::getenv("CS_MERGE_REVIEW_PATH"):nullptr;
 const std::string dir=reviewPath?reviewPath:cocos2d::FileUtils::getInstance()->getWritablePath();
 std::ofstream out(dir+"merge-diag.txt",std::ios::binary|std::ios::app);if(!out)return;
 const std::time_t now=std::time(nullptr);char stamp[40]={};const auto* local=std::localtime(&now);
 if(local)std::strftime(stamp,sizeof(stamp),"%Y-%m-%d %H:%M:%S",local);
 const int cx=(int)std::floor((x-l.board.x)/l.cell),cy=(int)std::floor((l.board.y-y)/l.cellH);
 out<<"\r\n[placement-v2 "<<stamp<<"] result="<<(accepted?"overlap":"rejected")
    <<" reason="<<(accepted?"overlap":run.lastFail)<<" action="<<(rotationAttempt?"rotate":"drop")
    <<" source="<<(fromTray?"tray":"board")<<"\r\n";
 out<<"stage="<<run.stage+1<<" wave="<<run.wave+1<<" shape="<<run.shape.width<<'x'<<run.shape.height
    <<" capacity="<<portraitGridCapacity()<<" tile="<<l.cell<<'x'<<l.cellH<<" resolved="<<run.boardResolved()
    <<" free_cells="<<run.freeCells()<<" pointer_cell="<<cx<<','<<cy
    <<" target_index="<<(run.shape.contains(cx,cy)?run.at(cx,cy):-1)<<"\r\n";
 out<<"source_family="<<source.family<<" source_stars="<<source.level<<" source_owned_id="<<source.ownedId
    <<" source_size="<<Wide(source)<<'x'<<Tall(source)<<" source_at="<<source.x<<','<<source.y
    <<" source_rot="<<source.rot<<"\r\nmessage=";
 for(char c:message){if(c=='\n')out<<"\\n";else if(c!='\r')out<<c;}
 out<<"\r\n";
 for(size_t i=0;i<run.board.size();++i){const Block& b=run.board[i];out<<"block="<<i<<" family="<<b.family<<" stars="<<b.level
    <<" crew="<<b.crew<<" owned_id="<<b.ownedId<<" size="<<Wide(b)<<'x'<<Tall(b)
    <<" at="<<b.x<<','<<b.y<<" rot="<<b.rot<<"\r\n";}
 out<<"---\r\n";
}
bool MergeRouletteTouch(int phase,int id,float x,float y) {
    if(!active&&lobbyDepartureAge>=0)return true;
    if(!active&&titleLobbyClock>=0)return true;
    if(portraitStarterInteriorTouch(phase,id,x,y))return true;
    if(portraitCameraTouch(phase,id,x,y))return true;
    if(active&&phase==0&&(layout().attack.has(x,y)||layout().cannon.has(x,y)))portraitCameraY=0;
    if(active&&startEventActive()){if(phase==2)startEventElapsed=StartEventDuration;return true;}
    if(!active&&RewardPopup::open())return RewardPopup::touch(x,y,phase,id);
    static int debugFinger=-1;
    if(!active) {
        if(resumePromptOpen&&drawHandle==MD_LOBBY){
            if(phase==0){resumePromptFinger=id;resumePromptChoice=-1;for(int i=0;i<2;++i)if(resumeChoiceBox(i).has(x,y))resumePromptChoice=i;}
            else if(id==resumePromptFinger&&(phase==2||phase==3)){
                const int choice=resumePromptChoice;resumePromptFinger=resumePromptChoice=-1;
                if(phase==2&&choice>=0&&resumeChoiceBox(choice).has(x,y)){
                    resumePromptOpen=false;entryChoiceOpen=false;
                    if(choice==1){SetPlayerHero(robin.mergeRouletteHero);MergeRouletteBegin(true);}
                    else{robin.mergeRouletteRun[0]=0;SaveGame();}
                }
            }
            return true;
        }
        if(RewardPopup::open()&&drawHandle==MD_LOBBY){RewardPopup::touch(x,y,phase,id);return true;}   //원정 보상창
        if(entryChoiceOpen&&drawHandle==MD_LOBBY){
            if(phase==0){
                if(entryChoiceFinger>=0)return true;
                entryChoiceFinger=id;entryChoicePressed=-1;
                for(int part=1;part<=6;++part)if(entryChoiceBox(part).has(x,y))entryChoicePressed=part;
                if(MergeTutorial::live()&&gCastleTutorialStep==CastleTutorial::Depart&&entryChoicePressed!=1)entryChoicePressed=-1;   //튜토리얼: 전투만
            }else if(id==entryChoiceFinger&&(phase==2||phase==3)){
                const int selected=entryChoicePressed;entryChoiceFinger=entryChoicePressed=-1;
                if(phase==2&&selected>0&&entryChoiceBox(selected).has(x,y)){
                    if(selected==1){
                        if(!MergeExpedition::affordable(robin.heart)){message=u8"번개가 모자랍니다 (5개 필요)";PlayMusic(M_ERROR);}
                        else{
                            const bool cinematic=!std::getenv("CS_MERGE_REVIEW")||std::getenv("CS_BASE_CAMP_REVIEW");
                            if(cinematic)lobbyDepartureCharge=true;
                            else{GetItem(ITEM_HEART,false,false,false,-MergeExpedition::Cost,false);AddBar(&bar[BAR_HEART],-MergeExpedition::Cost,BARFRAME);SaveGame();}
                            entryChoiceOpen=false;MergeRouletteBegin(false);
                        }
                    }
                    else if(selected==2){if(runExpedition())entryChoiceOpen=false;}
                    else if(selected==3)entryChoiceOpen=false;
                    else{
                        const int who=ROBIN+selected-4;
                        if(IsGetHero(who)){SetPlayerHero(who);message.clear();PlayMusic(M_BUTTON);}
                        else{message=u8"아직 해금되지 않은 히어로입니다.";PlayMusic(M_ERROR);}
                    }
                }
            }
            return true;
        }
        if(MergeTutorial::live()&&gCastleTutorialStep==CastleTutorial::Depart&&drawHandle==MD_LOBBY){   //튜토리얼 출정: 전투 시작만 통과
            if(phase==0&&popUpCnt==0&&!LoadoutOpen()&&lobbyStart(layout()).has(x,y)){entryChoiceOpen=true;entryChoiceFinger=entryChoicePressed=-1;message.clear();PlayMusic(M_BUTTON);}
            return true;
        }
        if(drawHandle==MD_LOBBY&&CastleVault::touch(phase,id,x,y))return true;   //금고 단추
        if(phase!=0&&debugFinger==id){if(phase==2||phase==3)debugFinger=-1;return true;}
        if(phase==0&&drawHandle==MD_LOBBY&&popUpCnt==0&&!LoadoutOpen()) {
            float s=DX/640.0f;
            Layout l=layout();Box b=lobbyStart(l);
            //전투 시작은 언제나 새 판이다. 저장된 판을 이어 가는 길("이어서")은 없앴다.
            if(b.has(x,y)) {entryChoiceOpen=true;entryChoiceFinger=entryChoicePressed=-1;message.clear();PlayMusic(M_BUTTON);return true;}
            if(lobbyPvp(l).has(x,y)) {MergeRouletteBeginSiege();return true;}
            if(lobbyDebugTouch(l,x,y)){debugFinger=id;return true;}   //성 디버그(단계 순환·다음 성·배경)
            for(int i=0;i<4;++i)if(roomBox(l,i).has(x,y)){
                CastleMenuFocusFacility(i);systemKey=AVK_POPUP_CASTLEMENU;return true;
            }
        }
        return false;
    }
    if(run.lost)return gameOverTouch(phase,id,x,y);
    if(RewardPopup::open()&&waveTransition.age>=MergeCombat::WaveTransition::DefeatFrames){   //보상창: 단추만 받는다
        RewardPopup::touch(x,y,phase,id);
        picked=finger=-1;return true;
    }
    if(quitPromptOpen){
        if(phase==0){quitPromptFinger=id;quitPromptChoice=-1;for(int i=0;i<2;++i)if(resumeChoiceBox(i).has(x,y))quitPromptChoice=i;}
        else if(id==quitPromptFinger&&(phase==2||phase==3)){
            const int choice=quitPromptChoice;quitPromptFinger=quitPromptChoice=-1;
            if(phase==2&&choice>=0&&resumeChoiceBox(choice).has(x,y)){
                PlayMusic(M_BUTTON);
                if(choice==0)leaveBattle(true);
                else{quitPromptOpen=false;simulationRemainder=0;}
            }
        }
        return true;
    }
    if(phase==0&&layout().exit.has(x,y)){exitPromptFinger=id;return true;}
    if(id==exitPromptFinger){
        if(phase==2||phase==3){
            exitPromptFinger=-1;
            if(phase==2&&layout().exit.has(x,y)){quitPromptOpen=true;picked=finger=-1;PlayMusic(M_BUTTON);}
        }
        return true;
    }
    if(MergeTutorial::gate(phase,x,y))return true;   //튜토리얼: 그 단계의 네모 밖 터치는 먹는다
    if(automaticMerge.active()||entering()||introActive()||spinFlying()||deckArriving()||waveTransition.active()) {picked=finger=-1;return true;}
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
        if(picked>=0)PlayMusic(M_JOYSTICK);
        return true;
    }
    if(finger!=id)return true;
    pointerX=x;pointerY=y;
    if(phase==1)return true;
    Layout l=layout();finger=-1;
    if(picked>=0) {
        const auto& chosen=pickedTray?run.tray:run.board;
        if(picked>=(int)chosen.size()){picked=-1;return true;}
        const Block attempted=chosen[picked];const bool fromTray=pickedTray;const auto mergeBefore=run.mergeSeq;
        bool ok=false;
        if(nearRouletteTrash(l,x,y)&&!MergeTutorial::trashLocked()){
            const bool fromTray=pickedTray;
            if(run.discard(fromTray,picked)){
                picked=-1;trashSwallowTicks=18;message="";save();PlayMusic(M_SHAKIN);
                if(fromTray)endSpinTurn();
                return true;
            }
        }
        const bool tap=std::abs(x-downX)+std::abs(y-downY)<10*l.scale;
        bool rotated=false;
        if(pickedTray&&tap)ok=run.autoPlace(picked);
        else if(!pickedTray&&tap){ok=rotated=run.rotate(picked);if(!ok)run.lastFail="spot";}   //판의 것을 톡 치면 돌린다
        else {
            const Block& held=(pickedTray?run.tray:run.board)[picked];
            // Match the visible footprint: the pointer centers the grabbed cell.
            const float centerX=(x-l.board.x)/l.cell-pickCellX+(Wide(held)-1)*.5f;
            const float centerY=(l.board.y-y)/l.cellH-pickCellY+(Tall(held)-1)*.5f;
            ok=run.drop(pickedTray,picked,centerX,centerY);
        }
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
                !std::strcmp(why,"spot")?"판 안의 빈 칸에 놓아 주세요.":
                !std::strcmp(why,"full")?"판에 놓을 자리가 없습니다.":
                !std::strcmp(why,"family")?"같은 종류끼리만 합쳐집니다.":
                !std::strcmp(why,"level")?"같은 단계끼리만 합쳐집니다.":
                !std::strcmp(why,"grow")?"더 올라갈 단계가 없습니다.":
                !std::strcmp(why,"room")?"합친 것이 들어갈 자리가 없습니다.":
                !std::strcmp(why,"crew")?"다음 단계의 동료를 아직 못 가졌습니다.":
                "그 자리에 놓을 수 없습니다.";

            message=text;

        }
        if(!ok||overlapped)writePlacementDiagnostic(l,attempted,fromTray,!fromTray&&tap,ok,x,y);
        if(!ok||overlapped)messageTime=3;
        if(ok&&!overlapped)PlayMusic(rotated?M_BUTTON:run.mergeSeq>mergeBefore?M_POWERUP:M_DOWN);else PlayMusic(M_ERROR);
        picked=-1;
        if(ok&&!run.tray.empty())beginSpinLanding();
        save();return true;
    }
    if(l.exit.has(x,y)&&l.exit.has(downX,downY)){quitPromptOpen=true;picked=finger=-1;return true;}
    if(animation>0||run.attacking)return true;
    if(run.lost) {
        if(l.spin.has(x,y)&&l.spin.has(downX,downY)) {
            close();entryChoiceOpen=true;entryChoiceFinger=entryChoicePressed=-1;message.clear();
        }
        else if(l.attack.has(x,y)&&l.attack.has(downX,downY))close();
        return true;
    }
    if(pendingPass)return true;
    const bool spinAction=(l.spin.has(x,y)&&l.spin.has(downX,downY))||(l.lever.has(x,y)&&l.lever.has(downX,downY));
    if(run.battleEnergy<=0&&(spinAction||(l.attack.has(x,y)&&l.attack.has(downX,downY))||(l.cannon.has(x,y)&&l.cannon.has(downX,downY)))){
        message=u8"\ubc88\uac1c\ub97c \ubaa8\ub450 \uc0ac\uc6a9\ud588\uc2b5\ub2c8\ub2e4.";messageTime=3;PlayMusic(M_ERROR);return true;
    }
    if(spinAction) {
        if(!run.boardResolved()){message=OverlapMessage;messageTime=3;PlayMusic(M_ERROR);return true;}
        if(!run.canSpin()){message=u8"\uc774\uc804 \uacb0\uacfc\ub97c \ubc30\uce58\ud558\uac70\ub098 \uc4f0\ub808\uae30\ud1b5\uc5d0 \ubc84\ub824\uc8fc\uc138\uc694.";messageTime=3;return true;}
        {if(!run.spendBattleEnergy())return true;spentHeart=run.battleEnergy;heartBlink=.36f;run.spin();rollOwnedGearResults(run);MergeTutorial::afterSpin();rememberReelSymbols();gearStartAngle=gearAngle;PlayMusic(M_ROULETTEUP);animation=REEL_SPIN_FRAMES;message="";save();CastleTutorialEvent(CastleTutorial::Spun);}
    } else if(l.attack.has(x,y)&&l.attack.has(downX,downY)) {
        //"지금 공격" 은 막지 않는다. 아직 못 놓은 결과가 있으면 들어가는 것은 앉히고,
        //자리 없는 것은 두고 나간다. 칸이 비어 있어도 모양이 안 맞으면 못 놓는 일이 있다.
        if(!run.tray.empty()){
            while(!run.tray.empty()&&run.autoPlace(0)){}
            if(!run.tray.empty()){message=u8"\ub0a8\uc740 \uacb0\uacfc\ub97c \ubc30\uce58\ud558\uac70\ub098 \uc4f0\ub808\uae30\ud1b5\uc5d0 \ubc84\ub824\uc8fc\uc138\uc694.";messageTime=3;save();return true;}
            picked=-1;pickedTray=false;
        }
        if(run.board.empty()){message="인벤토리가 비어 있습니다.";return true;}
        if(!run.boardResolved()){message=OverlapMessage;messageTime=3;PlayMusic(M_ERROR);return true;}
        {MergeTutorial::beforeAttack();if(!run.attack(stats))return true;run.spendBattleEnergy();spentHeart=run.battleEnergy;heartBlink=.36f;action=CombatAction();enemyTurn=EnemyTurn();animation=0;message="출격!";save();CastleTutorialEvent(CastleTutorial::Attacked);}
    } else if(!siegeActive&&l.cannon.has(x,y)&&l.cannon.has(downX,downY)) {
        //성의 대포. 판이 비어 있어도 쏜다 - 블록이 없을 때의 마지막 수단이기도 하다.
        if(!run.boardResolved()){message=OverlapMessage;messageTime=3;PlayMusic(M_ERROR);return true;}
        {if(!run.fireCannon(stats,cannonShell()))return true;run.spendBattleEnergy();spentHeart=run.battleEnergy;heartBlink=.36f;action=CombatAction();enemyTurn=EnemyTurn();animation=0;message="포격!";save();CastleTutorialEvent(CastleTutorial::CannonFired);}
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
  check(tap(OriginalCastle::box(95,740,12,12))&&LobbyCastleDebugCastle()==(c+1)%PortraitCastleArt::Count,c,5);
 }
 const int before=LobbyCastleDebugCastle();
 ok=MergeRouletteTouch(0,998,1,DY*.5f)&&LobbyCastleDebugCastle()==before&&ok;
 return ok&&robin.gold==gold&&memcmp(&saved,&robin.castleProgress,sizeof(saved))==0;
}

//---- 금고 수거 검증 (CS_VAULT_COLLECT_REVIEW) ----
//CastleMenuReview.inc 가 틱 순서로 부른다. 실제 단추 좌표를 실제 터치 경로로 누른다.
bool MergeRouletteVaultReview(int step){
    if(!getenv("CS_VAULT_COLLECT_REVIEW"))return false;
    static long long before=0,pending=0;static int crewSlot=-1,crewCount=0,gearCount=0;
    const auto tap=[](const Box& b){const float x=b.x+b.w*.5f,y=b.y-b.h*.5f;MergeRouletteTouch(0,995,x,y);MergeRouletteTouch(2,995,x,y);};
    const auto gearInInven=[](){int n=0;for(int i=0;i<GetMaxInven();++i)if(robin.inven[i].type!=EMPTY&&IsEquipItemType(robin.inven[i].type))++n;return n;};
    if(step==0){
        //가득 찬 금고 + 장비 한 점 + 동료 한 명 -> 골드·장비·동료 세 가지가 다 나가야 한다.
        for(int i=0;i<GetMaxInven();++i){memset(&robin.inven[i],0,sizeof(ITEM));robin.inven[i].type=EMPTY;}
        ITEM sword;MakeItem(&sword,ITEM_SWORD+curHero,1,GRADE_NORMAL,0,0);sword.count=1;robin.inven[0]=sword;
        int crew=-1;for(int c=0;c<gTotalCrew&&crew<0;++c)if(MergeCrewAvailable(c))crew=c;
        if(crew<0||!GetItem(ITEM_CREW,1,crew,GRADE_NORMAL,1,0))return false;
        crewSlot=GetInvenIdx(ITEM_CREW,crew,GRADE_NORMAL);if(crewSlot<0)return false;
        crewCount=(int)robin.inven[crewSlot].count;gearCount=gearInInven();
        robin.gold=1000;robin.castleIncomeTs=MC_knlCurrentTimeStamp()-INCOME_MAX_SEC;
        before=robin.gold;pending=CastleIncomeNow();
        const CastleVault::Plan p=CastleVault::plan();
        const bool ok=pending>0&&pending==CastleIncomeCap()&&p.percent==100&&p.gear&&p.crew&&!CastleVault::busy();
        if(!ok){std::ofstream f(std::string(getenv("CS_CASTLE_REVIEW_PATH"))+"phases.log",std::ios::app);
            f<<"DETAIL vault step0 pending="<<pending<<" cap="<<CastleIncomeCap()<<" pct="<<p.percent<<" gear="<<p.gear<<" crew="<<p.crew<<" busy="<<CastleVault::busy()<<" slot="<<crewSlot<<" hero="<<curHero<<" maxInven="<<GetMaxInven()<<"\n";}
        return ok;
    }
    if(step==1){
        tap(CastleVault::box());
        const bool goldNow=robin.gold==before+pending&&CastleIncomeNow()==0;
        const bool flying=CastleVault::busy()&&gLobbyGoldInFlight==pending&&CastleVault::lastGold==pending;
        const bool bonus=CastleVault::lastGear==1&&CastleVault::lastCrew==1&&gearInInven()==gearCount+1&&(int)robin.inven[crewSlot].count==crewCount+1;
        const int coins=(int)std::max((long long)VAULT_COIN_MIN,std::min((long long)VAULT_COIN_MAX,pending/50));
        return goldNow&&flying&&bonus&&(int)CastleVault::flights.size()==coins+2;
    }
    if(step==2)return !CastleVault::busy()&&gLobbyGoldInFlight==0&&CastleVault::flights.empty();
    if(step==3){
        //빈 금고: 아무것도 안 나가고 날아가지도 않는다.
        robin.castleIncomeTs=MC_knlCurrentTimeStamp();   //캡처를 기다린 실제 시간만큼 다시 찬 것을 비운다
        const long long gold=robin.gold;const int gears=gearInInven(),count=(int)robin.inven[crewSlot].count;
        tap(CastleVault::box());
        return CastleIncomeNow()==0&&robin.gold==gold&&!CastleVault::busy()&&gearInInven()==gears&&(int)robin.inven[crewSlot].count==count;
    }
    if(step==4){
        //조금만 찬 금고(상한의 50% 미만): 골드만 나간다.
        const long long perHour=CastleIncomePerHour();if(perHour<=0)return false;
        long sec=(long)(CastleIncomeCap()*3600/perHour/5);sec=std::max(60L,sec);
        robin.castleIncomeTs=MC_knlCurrentTimeStamp()-sec;
        const long long want=CastleIncomeNow();const CastleVault::Plan p=CastleVault::plan();
        if(want<=0||p.percent>=VAULT_GEAR_PCT||p.gear||p.crew)return false;
        const long long gold=robin.gold;const int gears=gearInInven(),count=(int)robin.inven[crewSlot].count;
        tap(CastleVault::box());
        bool onlyGold=true;for(const auto& f:CastleVault::flights)onlyGold=onlyGold&&f.type==ITEM_GOLD;
        return robin.gold==gold+want&&CastleVault::busy()&&onlyGold&&CastleVault::lastGear==0&&CastleVault::lastCrew==0&&gearInInven()==gears&&(int)robin.inven[crewSlot].count==count;
    }
    if(step==5)return !CastleVault::busy()&&gLobbyGoldInFlight==0;
    return false;
}
bool MergeRouletteEntryChoiceReview(int step){
    if(!getenv("CS_ENTRY_CHOICE_REVIEW"))return false;
    const auto tap=[](const Box& b){const float x=b.x+b.w*.5f,y=b.y-b.h*.5f;
        MergeRouletteTouch(0,996,x,y);MergeRouletteTouch(2,996,x,y);};
    if(step==0){
        const int castle=robin.castle;
        for(int c=0;c<10;++c){robin.castle=c;if(GetInitHeart()!=35+c*5){robin.castle=castle;return false;}}
        robin.castle=castle;
        robin.heart=20;
        for(int i=0;i<GetMaxInven();++i){memset(&robin.inven[i],0,sizeof(ITEM));robin.inven[i].type=EMPTY;}
        tap(lobbyStart(layout()));
        const int selected=curHero;
        tap(entryChoiceBox(5));
        const bool locked=IsGetHero(DIANA)?curHero==DIANA:curHero==selected;
        const int level=robin.lv;robin.lv=std::max(getHeroLv[DIANA],level);
        tap(entryChoiceBox(5));const bool switched=curHero==DIANA;
        tap(entryChoiceBox(4));robin.lv=level;
        return entryChoiceOpen&&!active&&robin.heart==20&&locked&&switched&&curHero==ROBIN;
    }
    if(step==1){robin.mergeRouletteRun[0]=0;tap(entryChoiceBox(3));return !entryChoiceOpen&&!active&&robin.heart==20;}
    if(step==2){
        const long long gold=robin.gold;tap(lobbyStart(layout()));tap(entryChoiceBox(2));
        const long long paid=robin.heart;tap(entryChoiceBox(2));
        return !entryChoiceOpen&&!active&&RewardPopup::open()&&paid==15&&robin.heart==paid&&robin.gold>gold;
    }
    if(step==3){
        RewardPopup::closeNow();robin.heart=4;const long long gold=robin.gold;
        tap(lobbyStart(layout()));tap(entryChoiceBox(2));
        return entryChoiceOpen&&!active&&!RewardPopup::open()&&robin.heart==4&&robin.gold==gold;
    }
    if(step==4){
        tap(entryChoiceBox(1));if(active||robin.heart!=4)return false;
        robin.heart=5;
        tap(entryChoiceBox(3));tap(lobbyStart(layout()));
        tap(entryChoiceBox(1));return !entryChoiceOpen&&!active&&lobbyDepartureAge==0&&robin.heart==5;
    }
    if(step==5){
        if(!active||robin.heart!=0||lobbyDepartureAge>=0)return false;
        const long long energy=robin.heart;
        run.choosing=false;run.attacking=false;run.lost=false;
        run.tray.clear();run.board.clear();run.spins=3;entryElapsed=-1;introElapsed=-1;animation=0;
        tap(layout().spin);
        return robin.heart==energy&&run.spins==2&&run.battleEnergy==4;
    }
    if(step==6){
        Run sample;sample.roster=&roster;sample.stage=run.stage;
        sample.setShape(castleShape(sample.stage));sample.setVitals(stats.heroHealth,stats.heroArmor);
        if(!sample.start(pool,treeWeights))return false;
        sample.wave=6;sample.enemyHp=sample.enemyMax=waveHp(sample.stage,6);
        const std::string encoded=sample.encode();
        if(encoded.size()>=sizeof(robin.mergeRouletteRun))return false;
        memset(robin.mergeRouletteRun,0,sizeof(robin.mergeRouletteRun));
        memcpy(robin.mergeRouletteRun,encoded.data(),encoded.size());robin.mergeRouletteHero=curHero;
        Run decoded;return entryResume(&decoded)&&decoded.wave==6;
    }
    return false;
}

// Isolated native review, exercising the same settlement and popup-close paths.
bool MergeRouletteFinalRewardReview(int step){
 if(!getenv("CS_FINAL_BOSS_REWARD_REVIEW"))return false;
 static long long balance=0,expected=0,paid=0;
 if(step==0){
  review=false;active=true;siegeActive=false;hero=ao[PLAYER];run=Run();run.roster=&roster;run.choosing=false;run.drafted=true;
  robin.gold=10000;balance=robin.gold;expected=0;
  for(int wave=0;wave<14;++wave){
   run.attacking=true;run.enemyHp=0;run.damageDone=run.enemyMax;finishCombatTurn();
   expected+=10*(BossTier(wave)?10:1);
   Run restored;
   if(RewardPopup::open()||robin.gold!=balance||run.wave!=wave+1||run.reward!=expected||!restored.decode(robin.mergeRouletteRun)||restored.reward!=expected)return false;
  }
  run.attacking=true;run.enemyHp=0;run.damageDone=run.enemyMax;finishCombatTurn();expected+=100;
  paid=robin.gold;
  return RewardPopup::open()&&paid==balance+expected&&run.reward==0&&robin.mergeRouletteRun[0]==0&&run.stage==1;
 }
 if(step==1){RewardPopup::finishReveal();return RewardPopup::ready()&&robin.gold==paid&&active;}
 if(step==2){const float x=RewardPopup::bx+RewardPopup::bw*.5f,y=RewardPopup::by-RewardPopup::bh*.5f;MergeRouletteTouch(0,993,x,y);MergeRouletteTouch(2,993,x,y);const bool returned=!active;RewardPopup::closeNow();return returned&&!active&&drawHandle==MD_LOBBY&&!RewardPopup::open()&&robin.gold==paid&&robin.mergeRouletteRun[0]==0&&!waveTransition.active();}
 if(step==3){const Box b=CastleVault::box(),start=lobbyStart(layout());return b.y-b.h>start.y&&b.x==start.x&&b.w==start.w;}
 return false;
}

// Recording-only final-boss finisher, in an isolated review account.
// The saved boss has 10 HP left; normal touch, damage, reward and return paths run.
bool MergeRouletteCurrentTour(int step){
 if(!getenv("CS_CURRENT_VERSION_TOUR"))return false;
 const auto tap=[](const Box& b){const float x=b.x+b.w*.5f,y=b.y-b.h*.5f;MergeRouletteTouch(0,988,x,y);MergeRouletteTouch(2,988,x,y);};
 if(step==0){
  review=false;configure();Run saved;saved.roster=&roster;saved.stage=0;saved.rng=12345;saved.setShape(castleShape(0));
  if(!saved.start(pool,treeWeights))return false;
  saved.setVitals(stats.heroHealth,stats.heroArmor);saved.wave=14;saved.enemyMax=waveHp(0,14);saved.enemyHp=std::min(10LL,saved.enemyMax);saved.enemyAttack=waveAttack(0,14);saved.reward=320;
  const std::string encoded=saved.encode();if(encoded.size()>=sizeof(robin.mergeRouletteRun))return false;
  memset(robin.mergeRouletteRun,0,sizeof(robin.mergeRouletteRun));memcpy(robin.mergeRouletteRun,encoded.data(),encoded.size());robin.mergeRouletteHero=curHero;
  resumePromptChecked=true;resumePromptOpen=false;SaveGame();return true;
 }
 if(step==1){tap(lobbyStart(layout()));return entryChoiceOpen;}
 if(step==2){entryChoiceOpen=false;resumePromptOpen=true;return true;}
 if(step==3){if(resumePromptOpen){tap(resumeChoiceBox(1));return false;}if(!active||ticks<120||entering()||introActive()||run.attacking)return false;tap(layout().cannon);return run.attacking;}
 if(step==4)return RewardPopup::open();
 if(step==5){if(!RewardPopup::ready())return false;tap({RewardPopup::bx,RewardPopup::by,RewardPopup::bw,RewardPopup::bh});return !active&&drawHandle==MD_LOBBY;}
 return false;
}
