// Included by Func_Menu.cpp.
#include "CastleArtilleryModel.h"
#include "Data/CastleFacilities.h"
#include "Data/InventoryCannonSprites.h"
#include "Data/CastleUpgradeBlocks.h"
namespace {
int castleBrowse=0,castlePage=0,castleCategory=0,castleRow=0,castleModal=0;
bool castleUpgradeIsRoom=false;
int castleUpgradeCastle=0,castleUpgradePart=0,castleUpgradeLevel=0,castleUpgradePrice=0;
int castleMessageUntil=0; float castlePanY=0;
const char* castleMessage="";
int CastleInventoryUsed() { int n=0; for(int i=0;i<GetMaxInven();++i) if(robin.inven[i].type!=EMPTY&&robin.inven[i].count>0) ++n; return n; }
void CastleLabel(const char* s,int x,int y,int width,float z=0.7f) {
    SetFontColor(COLOR_WHITE);
    CenterTextStrSolid(s,x,y,Min(z,width/Max(1.0f,StringWidth(s,1.0f))));
}
void CastlePanel(int x,int y,int w,int h) { MemRect(x,y,w,h,0x111F33); MemRectFrame(x,y,w,h,0xB99343); }
void CastleSaveChanges() {
    gMobileCastleVisual=robin.castle;
    robin.maxInven=(unsigned short)GetMaxInven();
    for(int i=ROBIN;i<TOTALPLAYER;++i) RefreshStat(&ao[i]);
    SaveGame(); PlayMusic(M_COIN);
}
}
void CastleProgressEnsure() {
    CastleMenuModel::Migrate(robin.castleProgress,robin.castle,robin.castlePartLv);
    robin.castle=CastleMenuModel::ClampVisual(robin.castle);
    auto& p=robin.castleProgress;
    p.owned=(p.owned&((1u<<CastleMenuModel::VisualCount)-1))|1u;
    for(int c=0;c<10;++c) for(int i=0;i<5;++i) {
        p.parts[c][i]=(unsigned char)Min(5,(int)p.parts[c][i]);
        p.rooms[c][i]=(unsigned char)Min(5,(int)p.rooms[c][i]);
    }
    robin.castle=CastleMenuModel::Current(p);
}
int CastleInventoryCapacity(int c) { return InventorySlots(); }
int CastleEquipmentCapacity(int c) { CastleProgressEnsure(); return CastleMenuModel::Equipment(robin.castleProgress,c,GridTestCellCnt(c)); }
int CastleCannonDamagePercent(int c) {
    CastleProgressEnsure(); c=CastleMenuModel::ClampVisual(c);
    return CastleArtillery::Of(c).damagePercent*CastleMenuModel::CannonDamageMultiplier(robin.castleProgress,c)/100;
}
int CastleCannonCooldown(int c) {
    CastleProgressEnsure(); c=CastleMenuModel::ClampVisual(c);
    return CastleArtillery::Of(c).cooldown*CastleMenuModel::CannonCooldownMultiplier(robin.castleProgress,c)/100;
}
int CastleVisualPartLevel(int c,int i) {
 const int preview=LobbyCastleDebugLevel(c,i);if(preview>=0)return preview;
 CastleProgressEnsure();return c>=0&&c<CastleMenuModel::VisualCount&&i>=0&&i<5?(i==3?CastleMenuModel::TurretLevel(robin.castleProgress,c):robin.castleProgress.parts[CastleMenuModel::Clamp(c)][i]):0;
}
int CastleTeamBonus(int kind) {
    CastleProgressEnsure(); const auto& p=robin.castleProgress; int c=CastleMenuModel::Clamp(robin.castle);
    return kind==0?CastleMenuModel::Attack(p,c)+CastleMenuModel::All(p,c):
        kind==1?CastleMenuModel::Health(p,c)+CastleMenuModel::All(p,c):
        CastleMenuModel::Defense(p,c)+CastleMenuModel::All(p,c);
}
static int castlePendingFacility=-1;
static bool gCastleFacilityTab=true;
void CastleMenuFocusFacility(int room){castlePendingFacility=Max(0,Min(3,room));}
void CastleMenuOpen() { CastleProgressEnsure();
    if(DebugControlsOpen()&&!LobbyCastleDebugActive())LobbyCastleDebugCommand(TOUCH_FUNC_LOBBY_CASTLE_DEBUG);
    if(DebugControlsOpen())LobbyCastleDebugCommand(TOUCH_FUNC_LOBBY_CASTLE_HIDE);
    castleBrowse=robin.castle;castlePage=castleModal=castleCategory=0;castleRow=3;castleMessage="";castlePanY=0;scY[MENU_CASTLE]=0;scAccelY=0;
    if(castlePendingFacility>=0){
        const int row=castlePendingFacility==2?0:castlePendingFacility==3?1:castlePendingFacility==1?2:3;
        gCastleFacilityTab=true;scY[MENU_CASTLE]=CastleUpgradeBlocks::PreviewHeight(DY)+72+row*(CastleUpgradeBlocks::CardHeight(DY)+CastleUpgradeBlocks::Gap);castlePendingFacility=-1;
    }
}
bool CastleSelectDeparture(int c){
 CastleProgressEnsure();return c==robin.castle; // A grown castle cannot be switched back to a prior stage.
}

bool CastleMenuCommand(int func) {
    if(DebugControlsOpen() && LobbyCastleDebugActive()){
        const bool room=func>=TOUCH_FUNC_CASTLE_FACILITY_UPGRADE&&func<TOUCH_FUNC_CASTLE_FACILITY_UPGRADE+4;
        if(room || func==TOUCH_FUNC_CASTLE_NEW_UPGRADE){
            castleModal=0;LobbyCastleDebugCycle(castleBrowse,room?func-TOUCH_FUNC_CASTLE_FACILITY_UPGRADE:-1);return true;
        }
        if(func==TOUCH_FUNC_CASTLE_NEW_CONFIRM){castleModal=0;return true;}
    }
    if(func>=TOUCH_FUNC_CASTLE_BROWSE_PICK && func<TOUCH_FUNC_CASTLE_BROWSE_PICK_END){
        if(!castleModal){castleBrowse=func-TOUCH_FUNC_CASTLE_BROWSE_PICK;scY[MENU_CASTLE]=0;scAccelY=0;}return true;
    }
    if(func==TOUCH_FUNC_RENEW_CASTLE_PARTS||func==TOUCH_FUNC_RENEW_CASTLE_FACILITIES){
        if(!castleModal){gCastleFacilityTab=func==TOUCH_FUNC_RENEW_CASTLE_FACILITIES;scY[MENU_CASTLE]=0;scAccelY=0;}return true;
    }
    if(func>=TOUCH_FUNC_CASTLE_FACILITY_UPGRADE && func<=TOUCH_FUNC_CASTLE_FACILITY_UPGRADE_END){
        if(castleModal)return true;
        CastleProgressEnsure();const int c=castleBrowse,i=func-TOUCH_FUNC_CASTLE_FACILITY_UPGRADE;if(c!=robin.castle)return true;
        const int lv=CastleMenuModel::RoomLevel(robin.castleProgress,c,i);
        if(i<CastleFacilities::RoomCount && CastleMenuModel::Owned(robin.castleProgress,c) && lv<5 && robin.gold>=CastleMenuModel::UpgradeCost(c,lv,true) && !(NetLastRequest()==NETREQ_SAVE && NetLastResult()==NETRESULT_ERR_CONFLICT)){
            castleUpgradeIsRoom=true;castleUpgradeCastle=c;castleUpgradePart=i;castleUpgradeLevel=lv;
            castleUpgradePrice=CastleMenuModel::UpgradeCost(c,lv,true);castleModal=2;
        }return true;
    }
    if(func>=TOUCH_FUNC_CASTLE_NEW_ROW&&func<TOUCH_FUNC_CASTLE_NEW_ROW_END&&func!=TOUCH_FUNC_CASTLE_NEW_ROW+3)return true;
    if(func<TOUCH_FUNC_CASTLE_NEW_PREV||func>=TOUCH_FUNC_CASTLE_NEW_ROW_END) return false;
    CastleProgressEnsure(); auto& p=robin.castleProgress; int c=castleBrowse;
    const long long oldGoldPerHour=CastleIncomePerHour();
    const long long oldGoldCap=CastleIncomeCap();
    const int oldEnergySeconds=CastleEnergyRecoverySeconds();
    if(castleModal&&func!=TOUCH_FUNC_CASTLE_NEW_CANCEL&&func!=TOUCH_FUNC_CASTLE_NEW_CONFIRM&&func!=TOUCH_FUNC_CASTLE_NEW_CONDITION) return true;
    castleMessage="";
    switch(func) {
    case TOUCH_FUNC_CASTLE_NEW_PREV: castleBrowse=Max(0,c-1); castlePanY=0;scY[MENU_CASTLE]=0; break;
    case TOUCH_FUNC_CASTLE_NEW_NEXT: castleBrowse=Min(CastleMenuModel::VisualCount-1,c+1); castlePanY=0;scY[MENU_CASTLE]=0; break;
    case TOUCH_FUNC_CASTLE_NEW_DETAIL: castlePage=1; break;
    case TOUCH_FUNC_CASTLE_NEW_BACK: castlePage=castlePage==2?1:0; break;
    case TOUCH_FUNC_CASTLE_NEW_ROOMS: break;
    case TOUCH_FUNC_CASTLE_NEW_PARTS: castleCategory=1; break;
    case TOUCH_FUNC_CASTLE_NEW_SELECT:
        if(c==robin.castle&&c+1<CastleMenuModel::VisualCount&&CastleMenuModel::Unlocked(p,c+1)){
            castleUpgradeCastle=c;castleUpgradePrice=CastleMenuModel::GoldPrice(c+1);castleModal=3;
        }else castleMessage=u8"\uD604\uC7AC \uC131\uC758 \uC2DC\uC124\uACFC \uD3EC\uB300\uB97C Lv.5\uAE4C\uC9C0 \uAC15\uD654\uD574\uC8FC\uC138\uC694.";break;
    case TOUCH_FUNC_CASTLE_NEW_BUY:
        if(!CastleMenuModel::Owned(p,c)) {
            if(c==robin.castle+1&&CastleMenuModel::Unlocked(p,c)){castleUpgradeCastle=robin.castle;castleUpgradePrice=CastleMenuModel::GoldPrice(c);castleModal=3;}
            else castleMessage="골드 구매는 이전 성의 모든 파츠 Lv.5가 필요합니다.";
        }
        break;
    case TOUCH_FUNC_CASTLE_NEW_BUY_GOLD:
        if(!CastleMenuModel::Owned(p,c)) {
            if(c==robin.castle+1&&CastleMenuModel::Unlocked(p,c)){castleUpgradeCastle=robin.castle;castleUpgradePrice=CastleMenuModel::GoldPrice(c);castleModal=3;}
            else castleMessage="골드 구매는 이전 성의 모든 파츠 Lv.5가 필요합니다.";
        }
        break;
    case TOUCH_FUNC_CASTLE_NEW_CONFIRM:
        if(castleModal==2) {
            castleModal=0; // Consume this confirmation before charging or saving.
            if(c==castleUpgradeCastle && (castleUpgradeIsRoom || castleRow==castleUpgradePart) &&
               (castleUpgradeIsRoom?CastleMenuModel::RoomLevel(p,c,castleUpgradePart):CastleMenuModel::TurretLevel(p,c))==castleUpgradeLevel &&
               CastleMenuModel::UpgradeCost(c,castleUpgradeLevel,castleUpgradeIsRoom)==castleUpgradePrice &&
               CastleMenuModel::Upgrade(p,c,castleUpgradePart,castleUpgradeIsRoom,robin.gold)) {
                CastleProductionRebase(oldGoldPerHour,oldEnergySeconds,oldGoldCap);CastleSaveChanges();castleMessage="업그레이드 완료 · 저장 요청됨";
            } else castleMessage="레벨 또는 골드가 변경되었습니다. 다시 확인해주세요.";
        }
        else if(castleModal==3) {
            const bool bought=robin.castle==castleUpgradeCastle&&castleUpgradePrice==CastleMenuModel::GoldPrice(robin.castle+1)&&CastleMenuModel::Advance(p,robin.castle,robin.gold);
            if(bought) { robin.castle=CastleMenuModel::Current(p);castleBrowse=robin.castle;castlePanY=0;scY[MENU_CASTLE]=0;gMobileCastleVisual=robin.castle;CastleProductionRebase(oldGoldPerHour,oldEnergySeconds,oldGoldCap);CastleSaveChanges(); castlePage=1; }
            else castleMessage="이전 성 보유 여부와 잔액을 확인해주세요.";
            castleModal=0;
        }
        break;
    case TOUCH_FUNC_CASTLE_NEW_CANCEL: castleModal=0; break;
    case TOUCH_FUNC_CASTLE_NEW_CONDITION:
        castleModal=0; castleMessage="골드 구매는 이전 성의 모든 파츠 Lv.5가 필요합니다."; break;
    case TOUCH_FUNC_CASTLE_NEW_UPGRADE:
        if(c!=robin.castle)return true;
        if(NetLastRequest()==NETREQ_SAVE && NetLastResult()==NETRESULT_ERR_CONFLICT) {castleMessage="저장 충돌 해결 후 다시 시도해주세요.";break;}
        if(CastleMenuModel::Owned(p,c) && CastleMenuModel::TurretLevel(p,c)<CastleMenuModel::MaxLevel &&
           robin.gold>=CastleMenuModel::UpgradeCost(c,CastleMenuModel::TurretLevel(p,c),false)) {
            castleUpgradeIsRoom=false;castleUpgradeCastle=c;castleUpgradePart=castleRow;castleUpgradeLevel=CastleMenuModel::TurretLevel(p,c);
            castleUpgradePrice=CastleMenuModel::UpgradeCost(c,castleUpgradeLevel,false);castleModal=2;
        } else castleMessage="최대 단계이거나 골드가 부족합니다.";
        break;
    case TOUCH_FUNC_CASTLE_NEW_PAID_UPGRADE:
        castleMessage="성 업그레이드는 골드만 사용합니다.";
        break;
    default: castleRow=func-TOUCH_FUNC_CASTLE_NEW_ROW;castleCategory=1;break;
    }
    if(*castleMessage) castleMessageUntil=frame+FPS*3;
    return true;
}
bool CastleMenuSwipe(float,float,float,float) { return false; }

namespace {
void CastleMenuToast(float u) {
    if(!*castleMessage||frame>=castleMessageUntil) return;
    const int width=DX-32*u,top=DY/2+24*u;
    SetAlpha(28); CastlePanel(16*u,top,width,48*u); SetAlpha(ALPHA_MAX);
    CastleLabel(castleMessage,DX/2,top-19*u,width-16*u,.60f*u);
}
}
#include "CastleMenuFinal.inc"
