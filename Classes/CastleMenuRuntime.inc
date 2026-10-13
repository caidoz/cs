// Included by Func_Menu.cpp; all resource IDs remain unchanged.
#include "CastleArtilleryModel.h"
namespace {
int castleBrowse=0,castlePage=0,castleCategory=0,castleRow=0,castleModal=0;
const char* castleMessage="";
const char* const castlePartNames[]={"지붕","성벽","내부","대포","차대"};
const char* const castleRoomNames[]={"창고","무기고","병영","공방","지휘실"};
const char* const castleRoomEffects[]={"아이템 적재 한도 +4개 / 단계","장비 배치 한도 +1칸 / 단계","아군 전체 체력 +2% / 단계","아군 전체 방어력 +2% / 단계","아군 전체 공격력 +2% / 단계"};
const char* const castlePartEffects[]={"아군 전체 공격력 +1% / 단계","아군 전체 방어력 +2% / 단계","아군 전체 체력 +2% / 단계","포 피해 +10%, 전체 공격력 +1% / 단계","아군 전체 능력치 +1% / 단계"};
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
void CastleButton(const char* s,int x,int y,int w,int h,int cmd,bool enabled=true) {
    MenuButton(x,y,w,h,s,enabled?BUTTON_COLOR_BLUE:BUTTON_COLOR_BROWN,enabled,enabled?cmd:0,
        Min(0.75f*_2X,(w-8.0f*_2X)/Max(1.0f,StringWidth(s,1.0f))));
}
void CastleSaveChanges() {
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
void CastleMenuOpen() { CastleProgressEnsure(); castleBrowse=robin.castle; castlePage=castleModal=castleCategory=castleRow=0; castleMessage=""; }
bool CastleMenuCommand(int func) {
    if(func<TOUCH_FUNC_CASTLE_NEW_PREV||func>=TOUCH_FUNC_CASTLE_NEW_ROW_END) return false;
    CastleProgressEnsure(); auto& p=robin.castleProgress; int c=castleBrowse;
    if(castleModal&&func!=TOUCH_FUNC_CASTLE_NEW_CANCEL&&func!=TOUCH_FUNC_CASTLE_NEW_CONFIRM&&func!=TOUCH_FUNC_CASTLE_NEW_CONDITION) return true;
    castleMessage="";
    switch(func) {
    case TOUCH_FUNC_CASTLE_NEW_PREV: castleBrowse=Max(0,c-1); break;
    case TOUCH_FUNC_CASTLE_NEW_NEXT: castleBrowse=Min(9,c+1); break;
    case TOUCH_FUNC_CASTLE_NEW_DETAIL: castlePage=1; break;
    case TOUCH_FUNC_CASTLE_NEW_BACK: castlePage=castlePage==2?1:0; break;
    case TOUCH_FUNC_CASTLE_NEW_ROOMS: castleCategory=0; break;
    case TOUCH_FUNC_CASTLE_NEW_PARTS: castleCategory=1; break;
    case TOUCH_FUNC_CASTLE_NEW_SELECT:
        if(!CastleMenuModel::Owned(p,c)) break;
        if(CastleInventoryUsed()>CastleInventoryCapacity(c)||CastleEquippedCells()>CastleEquipmentCapacity(c)||LoadoutCellUsed()>CastleEquipmentCapacity(c)||LoadoutUsed()>LOADOUT_BASE+c+p.rooms[c][1]) {
            castleMessage="용량 초과: 적재 아이템과 배치 장비를 먼저 정리해주세요."; break;
        }
        robin.castle=c; gMobileCastleVisual=c; CastleSaveChanges(); castleMessage="출정 성으로 선택했습니다."; break;
    case TOUCH_FUNC_CASTLE_NEW_BUY:
        if(!CastleMenuModel::Owned(p,c)) castleModal=CastleMenuModel::Unlocked(p,c)?1:2;
        break;
    case TOUCH_FUNC_CASTLE_NEW_CONFIRM:
        if(castleModal==1) {
            if(CastleMenuModel::Buy(p,c,robin.coin)) { CastleSaveChanges(); castlePage=1; }
            else castleMessage="구매 조건 또는 유료화폐 잔액을 확인해주세요.";
            castleModal=0;
        }
        break;
    case TOUCH_FUNC_CASTLE_NEW_CANCEL: castleModal=0; break;
    case TOUCH_FUNC_CASTLE_NEW_CONDITION: castleBrowse=Max(0,c-1); castleCategory=1; castlePage=1; castleModal=0; break;
    case TOUCH_FUNC_CASTLE_NEW_UPGRADE:
        if(CastleMenuModel::Upgrade(p,c,castleRow,castleCategory==0,robin.gold)) CastleSaveChanges();
        else castleMessage="최대 단계이거나 골드가 부족합니다.";
        break;
    default: castleRow=func-TOUCH_FUNC_CASTLE_NEW_ROW; castlePage=2; break;
    }
    return true;
}
bool CastleMenuSwipe(float fx,float fy,float tx,float ty) {
    if(curMenu!=MENU_CASTLE||popUpCnt==0||popUp[popUpCnt-1].type!=POPUPTYPE_CASTLEMENU||castlePage||castleModal) return false;
    if(fy<DY-GNBHEIGHT-230*_2X||fy>DY-GNBHEIGHT-40*_2X||Abs(tx-fx)<40*_2X||Abs(ty-fy)>Abs(tx-fx)*0.6f) return false;
    CastleMenuCommand(tx<fx?TOUCH_FUNC_CASTLE_NEW_NEXT:TOUCH_FUNC_CASTLE_NEW_PREV); return true;
}
void CastleMenuNewDraw() {
    CastleProgressEnsure(); const auto& p=robin.castleProgress;
    const int c=castleBrowse,top=DY-GNBHEIGHT,bottom=BOTTOMMENUHEIGHT+4*_2X;
    const int x=8*_2X,w=DX-16*_2X,available=top-bottom;
    const float u=Min((float)_2X,available/402.0f);
    char s[256];
    MemRect(0,top,DX,available,0x081528);
    CastleLabel(castlePage?"성 상세 · 업그레이드":"성 선택",DX/2,top-8*u,w,0.9f*u);
    if(castlePage) CastleButton("뒤로",x,top-4*u,48*u,22*u,TOUCH_FUNC_CASTLE_NEW_BACK);
    else CastleButton("닫기",x,top-4*u,48*u,22*u,TOUCH_FUNC_POPUP_CLOSE);
    CastleLabel(CastleStageAt(c)->title,DX/2,top-35*u,w,0.8f*u);
    const bool owned=CastleMenuModel::Owned(p,c);
    sprintf(s,"%s  ·  %d / 10",owned?(robin.castle==c?"출정 중":"보유 성"):"미보유",c+1);
    CastleLabel(s,DX/2,top-53*u,w,0.55f*u);
    if(!castlePage) {
        // Neighbor previews are confined to their own rectangles.
        if(c>0) { SetAlpha(12); CastlePartsDrawRect(c,0,top-90*u,48*u,120*u); SetAlpha(ALPHA_MAX); }
        if(c<9) { SetAlpha(12); CastlePartsDrawRect(c+2,DX-48*u,top-90*u,48*u,120*u); SetAlpha(ALPHA_MAX); }
        CastlePartsDrawRect(c+1,48*u,top-70*u,DX-96*u,148*u);
        SetRectPoint(54*u,top-72*u,DX-108*u,145*u,TOUCH_FUNC_CASTLE_NEW_DETAIL);
        CastleButton("<",x,top-135*u,26*u,32*u,TOUCH_FUNC_CASTLE_NEW_PREV,c>0);
        CastleButton(">",DX-x-26*u,top-135*u,26*u,32*u,TOUCH_FUNC_CASTLE_NEW_NEXT,c<9);
        for(int i=0;i<10;++i) MemRect(DX/2+(i-5)*10*u,top-224*u,5*u,4*u,i==c?0x4CD8FF:0x46566A);
        CastlePanel(x,top-241*u,w,106*u);
        sprintf(s,"아이템 적재 %d개     장비 배치 %d칸",CastleInventoryCapacity(c),CastleEquipmentCapacity(c));
        CastleLabel(s,DX/2,top-252*u,w-12*u,0.68f*u);
        sprintf(s,"%s · 창고 Lv.%d / 무기고 Lv.%d",CastleStageAt(c)->title,p.rooms[c][0],p.rooms[c][1]);
        CastleLabel(s,DX/2,top-273*u,w-12*u,0.5f*u);
        sprintf(s,"현재 보유 %d개   배치 %d칸",CastleInventoryUsed(),CastleEquippedCells());
        CastleLabel(s,DX/2,top-294*u,w-12*u,0.55f*u);
        sprintf(s,"포 공격 배율 %d%%  ·  쿨타임 %.1f초",CastleCannonDamagePercent(c),CastleCannonCooldown(c)/(float)FPS);
        CastleLabel(s,DX/2,top-311*u,w-12*u,0.55f*u);
        int shown=0;
        for(int i=0;i<TOTALINVENTORY&&shown<6;++i) {
            const ITEM& it=robin.inven[i];
            if(it.type==EMPTY||it.count<=0) continue;
            const int bx=x+12*u+shown*(w-24*u)/6;
            MemRectFrame(bx,top-325*u,22*u,18*u,0x566C88);
            DrawIcon(GetItemIcon(it.type,it.detail,it.grade),bx+2*u,top-325*u,18*u/ITEMICONSIZE,false,false,false,false);
            ++shown;
        }
        if(owned) {
            CastleButton("상세보기",x,top-352*u,w/2-3*u,30*u,TOUCH_FUNC_CASTLE_NEW_DETAIL);
            CastleButton(robin.castle==c?"출정 중":"출정 성 선택",x+w/2+3*u,top-352*u,w/2-3*u,30*u,TOUCH_FUNC_CASTLE_NEW_SELECT,robin.castle!=c);
        } else {
            if(CastleMenuModel::Unlocked(p,c)) sprintf(s,"유료화폐 %d · 구매하기",CastleMenuModel::Price(c));
            else sprintf(s,"이전 성의 모든 파츠 업그레이드 필요");
            CastleButton(s,x,top-352*u,w,30*u,TOUCH_FUNC_CASTLE_NEW_BUY);
        }
    } else if(castlePage==1) {
        CastlePartsDrawRect(c+1,DX/2-52*u,top-70*u,104*u,80*u);
        CastlePanel(x,top-155*u,w,65*u);
        sprintf(s,"적재 %d개  |  장비 배치 %d칸",CastleInventoryCapacity(c),CastleEquipmentCapacity(c));
        CastleLabel(s,DX/2,top-163*u,w-12*u,0.65f*u);
        sprintf(s,"포 공격력 %lld · %.1f초 · %d연타",Max(1LL,CastleProjectedStat(p,c,PS_DMG)*CastleCannonDamagePercent(c)/100),CastleCannonCooldown(c)/(float)FPS,CastleArtillery::Of(c).hits);
        CastleLabel(s,DX/2,top-183*u,w-12*u,0.55f*u);
        sprintf(s,"영웅 예상 전투력 %lld · 파츠 %d / 25",CastleProjectedPower(p,c),CastleMenuModel::Completed(p,c));
        CastleLabel(s,DX/2,top-202*u,w-12*u,0.5f*u);
        CastleButton("방 5종",x,top-226*u,w/2-2*u,25*u,TOUCH_FUNC_CASTLE_NEW_ROOMS);
        CastleButton("파츠 5종",x+w/2+2*u,top-226*u,w/2-2*u,25*u,TOUCH_FUNC_CASTLE_NEW_PARTS);
        for(int i=0;i<5;++i) {
            int lv=castleCategory?p.parts[c][i]:p.rooms[c][i];
            sprintf(s,"%s  Lv.%d / 5   >",castleCategory?castlePartNames[i]:castleRoomNames[i],lv);
            CastleButton(s,x,top-(257+i*24)*u,w,22*u,TOUCH_FUNC_CASTLE_NEW_ROW+i);
        }
        sprintf(s,"다음 성 구매 조건: 파츠 %d / 25",CastleMenuModel::Completed(p,c));
        CastleLabel(s,DX/2,top-381*u,w,0.53f*u);
    } else {
        bool room=castleCategory==0; int lv=room?p.rooms[c][castleRow]:p.parts[c][castleRow];
        sprintf(s,"%s Lv.%d%s",room?castleRoomNames[castleRow]:castlePartNames[castleRow],lv,lv==5?" · 최대 단계":" → 다음 단계");
        CastleLabel(s,DX/2,top-76*u,w,0.8f*u);
        if(room) {
            const int img=CASTLE_ROOM_V4_FIRST_IMG+Min(9,castleRow)*6+lv;
            if(!sprite[img]) LoadImg(img);
            if(sprite[img]) DrawImageScale(512,128,0,0,x,top-107*u,false,0,0,0,0,w/512.0f,70*u/128.0f,sprite[img],img);
        } else CastlePartsDrawRect(c+1,x,top-105*u,w,85*u);
        CastlePanel(x,top-195*u,w,117*u);
        CastleLabel(room?castleRoomEffects[castleRow]:castlePartEffects[castleRow],DX/2,top-207*u,w-12*u,0.6f*u);
        auto next=p; if(lv<5) { if(room) ++next.rooms[c][castleRow]; else ++next.parts[c][castleRow]; }
        int before=CastleInventoryCapacity(c),after=CastleMenuModel::Inventory(next,c,INVEN_BASE_SLOT,INVEN_PER_CASTLE,TOTALINVENTORY);
        sprintf(s,"적재 한도 %d → %d개",before,after); CastleLabel(s,DX/2,top-232*u,w-12*u,0.62f*u);
        sprintf(s,"장비 배치 %d → %d칸",CastleEquipmentCapacity(c),CastleMenuModel::Equipment(next,c,GridTestCellCnt(c))); CastleLabel(s,DX/2,top-253*u,w-12*u,0.62f*u);
        sprintf(s,"아군 공격 +%d%% → +%d%%",CastleMenuModel::Attack(p,c)+CastleMenuModel::All(p,c),CastleMenuModel::Attack(next,c)+CastleMenuModel::All(next,c)); CastleLabel(s,DX/2,top-274*u,w-12*u,0.62f*u);
        sprintf(s,"체력 +%d%% → +%d%% · 방어 +%d%% → +%d%%",CastleMenuModel::Health(p,c)+CastleMenuModel::All(p,c),CastleMenuModel::Health(next,c)+CastleMenuModel::All(next,c),CastleMenuModel::Defense(p,c)+CastleMenuModel::All(p,c),CastleMenuModel::Defense(next,c)+CastleMenuModel::All(next,c)); CastleLabel(s,DX/2,top-294*u,w-12*u,0.5f*u);
        if(!room&&castleRow==3) { sprintf(s,"포 피해 %lld → %lld / %.1f → %.1f초",Max(1LL,CastleProjectedStat(p,c,PS_DMG)*CastleCannonDamagePercent(c)/100),Max(1LL,CastleProjectedStat(next,c,PS_DMG)*CastleArtillery::Of(c).damagePercent*(100+10*next.parts[c][3])/10000),CastleCannonCooldown(c)/(float)FPS,CastleArtillery::Of(c).cooldown*(100-3*next.parts[c][3])/(100.0f*FPS)); }
        else sprintf(s,"영웅 예상 전투력 %lld → %lld",CastleProjectedPower(p,c),CastleProjectedPower(next,c));
        CastleLabel(s,DX/2,top-326*u,w,0.53f*u);
        sprintf(s,lv==5?"최대 단계":"골드 %d · 업그레이드",CastleMenuModel::UpgradeCost(c,lv,room));
        CastleButton(s,x,top-352*u,w,30*u,TOUCH_FUNC_CASTLE_NEW_UPGRADE,owned&&lv<5);
    }
    if(*castleMessage) CastleLabel(castleMessage,DX/2,bottom+14*u,w,0.5f*u);
    if(castleModal) {
        SetAlpha(24); MemRect(0,top,DX,available,COLOR_BLACK); SetAlpha(ALPHA_MAX);
        SetRectPoint(0,top,DX,available,TOUCH_FUNC_CASTLE_NEW_CANCEL);
        const int mt=top-95*u; CastlePanel(x,mt,w,238*u);
        CastleLabel(castleModal==1?"성 구매 확인":"이전 성 업그레이드 필요",DX/2,mt-14*u,w-10*u,0.8f*u);
        CastleButton("닫기",DX-x-48*u,mt-3*u,44*u,22*u,TOUCH_FUNC_CASTLE_NEW_CANCEL);
        if(castleModal==1) {
            CastleLabel(CastleStageAt(c)->title,DX/2,mt-67*u,w,0.8f*u);
            sprintf(s,"유료화폐 %d / 보유 %lld",CastleMenuModel::Price(c),robin.coin); CastleLabel(s,DX/2,mt-110*u,w,0.7f*u);
            sprintf(s,"구매 후 잔액 %lld",robin.coin-CastleMenuModel::Price(c)); CastleLabel(s,DX/2,mt-145*u,w,0.65f*u);
            CastleButton("구매 확정",x+12*u,mt-192*u,w-24*u,30*u,TOUCH_FUNC_CASTLE_NEW_CONFIRM,robin.coin>=CastleMenuModel::Price(c));
        } else {
            const int prev=Max(0,c-1);
            for(int i=0;i<5;++i) { sprintf(s,"%s  %d / 5  %s",castlePartNames[i],p.parts[prev][i],p.parts[prev][i]==5?"완료":"업그레이드 필요"); CastleLabel(s,DX/2,mt-(55+i*23)*u,w-16*u,0.64f*u); }
            CastleButton("이전 성 업그레이드",x+12*u,mt-192*u,w-24*u,30*u,TOUCH_FUNC_CASTLE_NEW_CONDITION);
        }
    }
}
