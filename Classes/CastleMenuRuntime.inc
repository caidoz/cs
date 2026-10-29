// Included by Func_Menu.cpp.
#include "CastleArtilleryModel.h"
#include "Data/InventoryCannonSprites.h"
namespace {
int castleBrowse=0,castlePage=0,castleCategory=0,castleRow=0,castleModal=0;
int castleMessageUntil=0; float castlePanY=0;
const char* castleMessage="";
const char* const castlePartNames[]={"첨탑","외부장갑","실내","대포","바퀴"};
const char* const castleRoomNames[]={"창고","무기고","병영","공방","지휘실"};
const char* const castleRoomEffects[]={"아이템 적재 한도 +4개 / 단계","장비 배치 한도 +1칸 / 단계","아군 전체 체력 +2% / 단계","아군 전체 방어력 +2% / 단계","아군 전체 공격력 +2% / 단계"};
const char* const castlePartEffects[]={"아군 전체 공격력 +1% / 단계","아군 전체 방어력 +2% / 단계","아군 전체 체력 +2% / 단계","포 피해 +10%, 쿨타임 -3%, 공격력 +1% / 단계","아군 전체 능력치 +1% / 단계"};
int CastleInventoryUsed() { int n=0; for(int i=0;i<TOTALINVENTORY;++i) if(robin.inven[i].type!=EMPTY&&robin.inven[i].count>0) ++n; return n; }
long long CastleProjectedStat(const CastleMenuModel::Progress& p,int c,int stat) {
    const int kind=stat==PS_DMG?0:stat==PS_HP?1:2;
    const int bonus=(kind==0?CastleMenuModel::Attack(p,c):kind==1?CastleMenuModel::Health(p,c):CastleMenuModel::Defense(p,c))+CastleMenuModel::All(p,c);
    return ao[PLAYER].ps[stat]*(100+bonus)/(100+CastleTeamBonus(kind));
}
long long CastleProjectedPower(const CastleMenuModel::Progress& p,int c) {
    return GetCombatPower(&ao[PLAYER])-ao[PLAYER].ps[PS_DMG]-ao[PLAYER].ps[PS_HP]-ao[PLAYER].ps[PS_ARMOR]
        +CastleProjectedStat(p,c,PS_DMG)+CastleProjectedStat(p,c,PS_HP)+CastleProjectedStat(p,c,PS_ARMOR);
}
void CastleLabel(const char* s,int x,int y,int width,float z=0.7f) {
    SetFontColor(COLOR_WHITE);
    CenterTextStrSolid(s,x,y,Min(z,width/Max(1.0f,StringWidth(s,1.0f))));
}
void CastlePanel(int x,int y,int w,int h) { MemRect(x,y,w,h,0x111F33); MemRectFrame(x,y,w,h,0xB99343); }
void CastleButton(const char* s,int x,int y,int w,int h,int cmd,bool enabled=true,int color=BUTTON_COLOR_BLUE) {
    MenuButton(x,y,w,h,s,enabled?color:BUTTON_COLOR_BROWN,enabled,enabled?cmd:0,
        Min(0.75f*_2X,(w-8.0f*_2X)/Max(1.0f,StringWidth(s,1.0f))));
}
void CastleSaveChanges() {
    gMobileCastleVisual=robin.castle;
    robin.maxInven=(unsigned short)GetMaxInven();
    for(int i=ROBIN;i<TOTALPLAYER;++i) RefreshStat(&ao[i]);
    SaveGame(); PlayMusic(M_COIN);
}
}
void CastleProgressEnsure() {
    CastleMenuModel::Migrate(robin.castleProgress,robin.castle,robin.castlePartLv);
    robin.castle=CastleMenuModel::Clamp(robin.castle);
    auto& p=robin.castleProgress;
    p.owned=(p.owned&1023u)|1u;
    for(int c=0;c<10;++c) for(int i=0;i<5;++i) {
        p.parts[c][i]=(unsigned char)Min(5,(int)p.parts[c][i]);
        p.rooms[c][i]=(unsigned char)Min(5,(int)p.rooms[c][i]);
    }
    if(!CastleMenuModel::Owned(p,robin.castle)) robin.castle=0;
}
int CastleInventoryCapacity(int c) { CastleProgressEnsure(); return CastleMenuModel::Inventory(robin.castleProgress,c,INVEN_BASE_SLOT,INVEN_PER_CASTLE,TOTALINVENTORY); }
int CastleEquipmentCapacity(int c) { CastleProgressEnsure(); return CastleMenuModel::Equipment(robin.castleProgress,c,GridTestCellCnt(c)); }
int CastleCannonDamagePercent(int c) {
    CastleProgressEnsure(); c=CastleMenuModel::Clamp(c);
    return CastleArtillery::Of(c).damagePercent*(100+10*robin.castleProgress.parts[c][3])/100;
}
int CastleCannonCooldown(int c) {
    CastleProgressEnsure(); c=CastleMenuModel::Clamp(c);
    return CastleArtillery::Of(c).cooldown*(100-3*robin.castleProgress.parts[c][3])/100;
}
int CastleVisualPartLevel(int c,int i) { CastleProgressEnsure(); return c>=0&&c<10&&i>=0&&i<5?robin.castleProgress.parts[c][i]:0; }
int CastleTeamBonus(int kind) {
    CastleProgressEnsure(); const auto& p=robin.castleProgress; int c=CastleMenuModel::Clamp(robin.castle);
    return kind==0?CastleMenuModel::Attack(p,c)+CastleMenuModel::All(p,c):
        kind==1?CastleMenuModel::Health(p,c)+CastleMenuModel::All(p,c):
        CastleMenuModel::Defense(p,c)+CastleMenuModel::All(p,c);
}
void CastleMenuOpen() { CastleProgressEnsure(); castleBrowse=robin.castle; castlePage=castleModal=castleCategory=castleRow=0; castleMessage=""; castlePanY=0;scY[MENU_CASTLE]=0;scAccelY=0; }
bool CastleMenuCommand(int func) {
    if(func<TOUCH_FUNC_CASTLE_NEW_PREV||func>=TOUCH_FUNC_CASTLE_NEW_ROW_END) return false;
    CastleProgressEnsure(); auto& p=robin.castleProgress; int c=castleBrowse;
    if(castleModal&&func!=TOUCH_FUNC_CASTLE_NEW_CANCEL&&func!=TOUCH_FUNC_CASTLE_NEW_CONFIRM&&func!=TOUCH_FUNC_CASTLE_NEW_CONDITION) return true;
    castleMessage="";
    switch(func) {
    case TOUCH_FUNC_CASTLE_NEW_PREV: castleBrowse=Max(0,c-1); castlePanY=0;scY[MENU_CASTLE]=0; break;
    case TOUCH_FUNC_CASTLE_NEW_NEXT: castleBrowse=Min(9,c+1); castlePanY=0;scY[MENU_CASTLE]=0; break;
    case TOUCH_FUNC_CASTLE_NEW_DETAIL: castlePage=1; break;
    case TOUCH_FUNC_CASTLE_NEW_BACK: castlePage=castlePage==2?1:0; break;
    case TOUCH_FUNC_CASTLE_NEW_ROOMS: break;
    case TOUCH_FUNC_CASTLE_NEW_PARTS: castleCategory=1; break;
    case TOUCH_FUNC_CASTLE_NEW_SELECT:
        if(!CastleMenuModel::Owned(p,c)) break;
        if(CastleInventoryUsed()>CastleInventoryCapacity(c)||CastleEquippedCells()>CastleEquipmentCapacity(c)||LoadoutCellUsed()>CastleEquipmentCapacity(c)||LoadoutUsed()>LOADOUT_BASE+c+p.rooms[c][1]) {
            castleMessage="용량 초과: 적재 아이템과 배치 장비를 먼저 정리해주세요."; break;
        }
        robin.castle=c; gMobileCastleVisual=c; CastleSaveChanges(); castleMessage="출정 성으로 선택했습니다."; break;
    case TOUCH_FUNC_CASTLE_NEW_BUY:
        if(!CastleMenuModel::Owned(p,c)) {
            if(CastleMenuModel::Unlocked(p,c)) castleModal=3;
            else castleMessage="골드 구매는 이전 성의 모든 파츠 Lv.5가 필요합니다.";
        }
        break;
    case TOUCH_FUNC_CASTLE_NEW_BUY_GOLD:
        if(!CastleMenuModel::Owned(p,c)) {
            if(CastleMenuModel::Unlocked(p,c)) castleModal=3;
            else castleMessage="골드 구매는 이전 성의 모든 파츠 Lv.5가 필요합니다.";
        }
        break;
    case TOUCH_FUNC_CASTLE_NEW_CONFIRM:
        if(castleModal==3) {
            const bool bought=CastleMenuModel::BuyGold(p,c,robin.gold);
            if(bought) { robin.castle=c;gMobileCastleVisual=c;CastleSaveChanges(); castlePage=1; }
            else castleMessage="이전 성 보유 여부와 잔액을 확인해주세요.";
            castleModal=0;
        }
        break;
    case TOUCH_FUNC_CASTLE_NEW_CANCEL: castleModal=0; break;
    case TOUCH_FUNC_CASTLE_NEW_CONDITION:
        castleModal=0; castleMessage="골드 구매는 이전 성의 모든 파츠 Lv.5가 필요합니다."; break;
    case TOUCH_FUNC_CASTLE_NEW_UPGRADE:
        if(CastleMenuModel::Upgrade(p,c,castleRow,false,robin.gold)) { CastleSaveChanges(); castleMessage="골드 업그레이드 완료"; }
        else castleMessage="최대 단계이거나 골드가 부족합니다.";
        break;
    case TOUCH_FUNC_CASTLE_NEW_PAID_UPGRADE:
        castleMessage="성 업그레이드는 골드만 사용합니다.";
        break;
    default: castleRow=func-TOUCH_FUNC_CASTLE_NEW_ROW;castleCategory=1;CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_UPGRADE); break;
    }
    if(*castleMessage) castleMessageUntil=frame+FPS*3;
    return true;
}
bool CastleMenuSwipe(float,float,float,float) { return false; }

namespace {
long long CastleTotalPower(const CastleMenuModel::Progress& p,int c) {
    long long total=CastleMenuModel::StructuralPower(p,c,GridTestCellCnt(c))+Max(1LL,CastleProjectedPower(p,c));
    for(int i=CREW;i<CREW+MAXCREW;++i) if(ao[i].active&&!ao[i].dead) {
        long long crew=GetCombatPower(&ao[i]);
        const int stats[3]={PS_DMG,PS_HP,PS_ARMOR};
        const int bonus[3]={CastleMenuModel::Attack(p,c),CastleMenuModel::Health(p,c),CastleMenuModel::Defense(p,c)};
        for(int k=0;k<3;++k) crew+=ao[i].ps[stats[k]]*(100+bonus[k]+CastleMenuModel::All(p,c))/(100+CastleTeamBonus(k))-ao[i].ps[stats[k]];
        total+=Max(0LL,crew);
    }
    const auto& profile=CastleArtillery::Of(c);
    const long long damage=Max(1LL,CastleProjectedStat(p,c,PS_DMG)*profile.damagePercent*(100+10*p.parts[c][3])/10000);
    const int cooldown=Max(1,profile.cooldown*(100-3*p.parts[c][3])/100);
    return total+damage*profile.hits*FPS/cooldown;
}
void CastleMenuGrid(int c,int x,int top,int width,int height,float u) {
    const int start=castleGridCellStart[c],count=GridTestCellCnt(c);
    int cols=0,rows=0;
    for(int i=0;i<count;++i) { cols=Max(cols,(int)castleGridCell[(start+i)*2]+1); rows=Max(rows,(int)castleGridCell[(start+i)*2+1]+1); }
    const float cell=Min(width/(float)Max(1,cols),height/(float)Max(1,rows));
    const int left=x+(width-(int)(cols*cell))/2;
    for(int i=0;i<count;++i) {
        const int gx=left+(int)(castleGridCell[(start+i)*2]*cell);
        const int gy=top-(int)((rows-1-castleGridCell[(start+i)*2+1])*cell);
        // Runtime limits total occupied cells, not individual grid positions.
        MemRect(gx,gy,Max(1,(int)cell-1),Max(1,(int)cell-1),0x163E61);
        MemRectFrame(gx,gy,Max(1,(int)cell-1),Max(1,(int)cell-1),0x5CC9F0);
    }
}
void CastleMenuAssembly(int c,int top,int bottom) {
    float nw,nh; CastlePartsNaturalSize(c+1,&nw,&nh);
    const float scale=CastlePartsRoomScale();
    float visualLeft,visualRight; CastlePartsVisualBounds(c+1,scale,&visualLeft,&visualRight);
    const int x=(int)(DX*.5f-(visualLeft+visualRight)*scale*.5f-CastlePartsLeftInset(c+1)*scale);
    const int y=(int)(DY*.5f+nh*scale*.5f+castlePanY);
    SetSectionClip(0,top,DX,top-bottom,false);
    CastlePartsDrawRect(c+1,x,y,(int)(nw*scale),(int)(nh*scale));
    UnSectionClip(false);
}
void CastleMenuToast(float u) {
    if(!*castleMessage||frame>=castleMessageUntil) return;
    const int width=DX-32*u,top=DY/2+24*u;
    SetAlpha(28); CastlePanel(16*u,top,width,48*u); SetAlpha(ALPHA_MAX);
    CastleLabel(castleMessage,DX/2,top-19*u,width-16*u,.60f*u);
}
}
#include "CastleMenuFinal.inc"
