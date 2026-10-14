// Included by Func_Menu.cpp.
#include "CastleArtilleryModel.h"
#include "Data/InventoryCannonSprites.h"
namespace {
int castleBrowse=0,castlePage=0,castleCategory=0,castleRow=0,castleModal=0;
int castleMessageUntil=0; float castlePanY=0;
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
void CastleButton(const char* s,int x,int y,int w,int h,int cmd,bool enabled=true,int color=BUTTON_COLOR_BLUE) {
    MenuButton(x,y,w,h,s,enabled?color:BUTTON_COLOR_BROWN,enabled,enabled?cmd:0,
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
void CastleMenuOpen() { CastleProgressEnsure(); castleBrowse=robin.castle; castlePage=castleModal=castleCategory=castleRow=0; castleMessage=""; castlePanY=0; }
bool CastleMenuCommand(int func) {
    if(func<TOUCH_FUNC_CASTLE_NEW_PREV||func>=TOUCH_FUNC_CASTLE_NEW_ROW_END) return false;
    CastleProgressEnsure(); auto& p=robin.castleProgress; int c=castleBrowse;
    if(castleModal&&func!=TOUCH_FUNC_CASTLE_NEW_CANCEL&&func!=TOUCH_FUNC_CASTLE_NEW_CONFIRM&&func!=TOUCH_FUNC_CASTLE_NEW_CONDITION) return true;
    castleMessage="";
    switch(func) {
    case TOUCH_FUNC_CASTLE_NEW_PREV: castleBrowse=Max(0,c-1); castlePanY=0; break;
    case TOUCH_FUNC_CASTLE_NEW_NEXT: castleBrowse=Min(9,c+1); castlePanY=0; break;
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
        if(!CastleMenuModel::Owned(p,c)) {
            if(c>0 && CastleMenuModel::Owned(p,c-1)) castleModal=1;
            else castleMessage="이전 성을 먼저 구매해주세요.";
        }
        break;
    case TOUCH_FUNC_CASTLE_NEW_BUY_GOLD:
        if(!CastleMenuModel::Owned(p,c)) {
            if(CastleMenuModel::Unlocked(p,c)) castleModal=3;
            else castleMessage="골드 구매는 이전 성의 모든 파츠 Lv.5가 필요합니다.";
        }
        break;
    case TOUCH_FUNC_CASTLE_NEW_CONFIRM:
        if(castleModal==1||castleModal==3) {
            const bool bought=castleModal==3?CastleMenuModel::BuyGold(p,c,robin.gold):CastleMenuModel::BuyInstant(p,c,robin.coin);
            if(bought) { CastleSaveChanges(); castlePage=1; }
            else castleMessage="이전 성 보유 여부와 잔액을 확인해주세요.";
            castleModal=0;
        }
        break;
    case TOUCH_FUNC_CASTLE_NEW_CANCEL: castleModal=0; break;
    case TOUCH_FUNC_CASTLE_NEW_CONDITION:
        castleModal=0; castleMessage="골드 구매는 이전 성의 모든 파츠 Lv.5가 필요합니다."; break;
    case TOUCH_FUNC_CASTLE_NEW_UPGRADE:
        if(CastleMenuModel::Upgrade(p,c,castleRow,castleCategory==0,robin.gold)) { CastleSaveChanges(); castleMessage="골드 업그레이드 완료"; }
        else castleMessage="최대 단계이거나 골드가 부족합니다.";
        break;
    case TOUCH_FUNC_CASTLE_NEW_PAID_UPGRADE:
        if(CastleMenuModel::UpgradePaid(p,c,castleRow,castleCategory==0,robin.coin)) { CastleSaveChanges(); castleMessage="즉시 업그레이드 완료"; }
        else castleMessage="최대 단계이거나 유료화폐가 부족합니다.";
        break;
    default: castleRow=func-TOUCH_FUNC_CASTLE_NEW_ROW; castlePage=2; break;
    }
    if(*castleMessage) castleMessageUntil=frame+FPS*3;
    return true;
}
bool CastleMenuSwipe(float fx,float fy,float tx,float ty) {
    if(curMenu!=MENU_CASTLE||popUpCnt==0||popUp[popUpCnt-1].type!=POPUPTYPE_CASTLEMENU||castlePage==2||castleModal) return false;
    const float unit=Min((float)_2X,(DY-GNBHEIGHT)/430.0f);
    if(fy<DY-GNBHEIGHT-260*unit||fy>DY-GNBHEIGHT-86*unit) return false;
    if(Abs(ty-fy)>Abs(tx-fx) && Abs(ty-fy)>12*_2X) {
        float cw,ch; CastlePartsNaturalSize(castleBrowse+1,&cw,&ch);
        const float limit=Max(0.0f,(ch*CastlePartsRoomScale()-174*unit)/2);
        castlePanY=Max(-limit,Min(limit,castlePanY+ty-fy)); return true;
    }
    if(castlePage||Abs(tx-fx)<40*_2X||Abs(ty-fy)>Abs(tx-fx)*0.6f) return false;
    CastleMenuCommand(tx<fx?TOUCH_FUNC_CASTLE_NEW_NEXT:TOUCH_FUNC_CASTLE_NEW_PREV); return true;
}
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
void CastleMenuNewDraw() {
    CastleProgressEnsure(); const auto& p=robin.castleProgress;
    const int c=castleBrowse,top=DY-GNBHEIGHT,x=8*_2X,w=DX-16*_2X;
    const float u=Min((float)_2X,top/430.0f);
    const bool owned=CastleMenuModel::Owned(p,c);
    char s[256];
    // A modal owns the full area below the top currency bar, including main tabs.
    ResetRectPoint(); SetAlpha(ALPHA_MAX);
    MemRect(0,top,DX,top,0x081528);
    SetRectPoint(0,top,DX,top,TOUCH_FUNC_CASTLE_NEW_CANCEL);
    CastleLabel(castlePage?"성 상세 · 업그레이드":"성 선택",DX/2,top-8*u,w,.9f*u);
    CastleButton(castlePage?"뒤로":"닫기",x,top-4*u,48*u,22*u,castlePage?TOUCH_FUNC_CASTLE_NEW_BACK:TOUCH_FUNC_POPUP_CLOSE);
    CastleLabel(CastleStageAt(c)->title,DX/2,top-34*u,w,.8f*u);
    sprintf(s,"%s · %d / 10",owned?(robin.castle==c?"출정 중":"보유 중"):"미보유",c+1);
    CastleLabel(s,DX/2,top-52*u,w,.48f*u);
    sprintf(s,"성 전체 전투력  %lld",CastleTotalPower(p,c));
    SetFontColor(COLOR_YELLOW); CenterTextStrSolid(s,DX/2,top-75*u,Min(.9f*u,(w-12*u)/Max(1.0f,StringWidth(s,1))));
    if(castlePage<2) {
        const int viewTop=top-104*u,viewBottom=top-274*u;
        CastleMenuAssembly(c,viewTop,viewBottom);
        if(!castlePage) {
            SetRectPoint(44*u,viewTop,DX-88*u,viewTop-viewBottom,TOUCH_FUNC_CASTLE_NEW_DETAIL);
            CastleButton("<",x,top-154*u,26*u,32*u,TOUCH_FUNC_CASTLE_NEW_PREV,c>0);
            CastleButton(">",DX-x-26*u,top-154*u,26*u,32*u,TOUCH_FUNC_CASTLE_NEW_NEXT,c<9);
        } else {
            // Five actionable labels surround the centered castle and point inward.
            const int bw=76*u,bh=23*u;
            for(int i=0;i<5;++i) {
                const bool right=i==3||i==4;
                const int bx=right?DX-x-bw:x,by=top-(100+(right?i-3:i)*48)*u;
                float anchorX,anchorY; CastlePartsPartAnchor(c+1,castleCategory?i:2,&anchorX,&anchorY);
                const int px=Max((int)(92*u),Min((int)(DX-92*u),(int)anchorX));
                const int py=Max(viewBottom+(int)(12*u),Min(viewTop-(int)(4*u),(int)anchorY));
                const int start=right?bx:bx+bw,midY=by-bh/2;
                MemRect(Min(start,px),midY,Max(1,Abs(px-start)),Max(1,(int)u),0xD2AB58);
                MemRect(px,Max(midY,py),Max(1,(int)u),Max(1,Abs(py-midY)),0xD2AB58);
                MemRect(px-2*u,py+2*u,4*u,4*u,0xFFD777);
                sprintf(s,"%s Lv.%d +",castleCategory?castlePartNames[i]:castleRoomNames[i],castleCategory?p.parts[c][i]:p.rooms[c][i]);
                CastleButton(s,bx,by,bw,bh,TOUCH_FUNC_CASTLE_NEW_ROW+i);
            }
        }
        CastleLabel("위아래로 밀어 성 전체 보기",DX/2,top-276*u,w,.42f*u);
        CastlePanel(x,top-285*u,w,75*u);
        sprintf(s,"전투 인벤토리 %d칸 · 배치 한도 %d칸",GridTestCellCnt(c),CastleEquipmentCapacity(c));
        CastleLabel(s,DX/2,top-294*u,w-12*u,.62f*u);
        CastleMenuGrid(c,x+6*u,top-311*u,w/2-12*u,44*u,u);
        sprintf(s,"아이템 적재 %d개",CastleInventoryCapacity(c));
        CastleLabel(s,x+w*3/4,top-311*u,w/2-12*u,.52f*u);
        sprintf(s,"포 공격력 %lld · %d연타",Max(1LL,CastleProjectedStat(p,c,PS_DMG)*CastleCannonDamagePercent(c)/100),CastleArtillery::Of(c).hits);
        CastleLabel(s,x+w*3/4,top-328*u,w/2-12*u,.49f*u);
        sprintf(s,"쿨타임 %.1f초",CastleCannonCooldown(c)/(float)FPS);
        CastleLabel(s,x+w*3/4,top-345*u,w/2-12*u,.48f*u);
        if(!castlePage) {
            int shown=0;
            for(int i=0;i<TOTALINVENTORY&&shown<6;++i) {
                const ITEM& it=robin.inven[i]; if(it.type==EMPTY||it.count<=0) continue;
                DrawIcon(GetItemIcon(it.type,it.detail,it.grade),x+8*u+shown*24*u,top-365*u,18*u/ITEMICONSIZE,false,false,false,false); ++shown;
            }
            if(owned) {
                CastleButton("상세보기",x,top-390*u,w/2-3*u,30*u,TOUCH_FUNC_CASTLE_NEW_DETAIL);
                CastleButton(robin.castle==c?"출정 중":"출정 성 선택",x+w/2+3*u,top-390*u,w/2-3*u,30*u,TOUCH_FUNC_CASTLE_NEW_SELECT,robin.castle!=c);
            } else {
                sprintf(s,"골드 %d · 구매",CastleMenuModel::GoldPrice(c));
                CastleButton(s,x,top-390*u,w/2-3*u,30*u,TOUCH_FUNC_CASTLE_NEW_BUY_GOLD,true,BUTTON_COLOR_BEIGE);
                sprintf(s,"유료화폐 %d · 즉시 구매",CastleMenuModel::Price(c));
                CastleButton(s,x+w/2+3*u,top-390*u,w/2-3*u,30*u,TOUCH_FUNC_CASTLE_NEW_BUY,true,BUTTON_COLOR_PURPLE);
            }
        } else {
            CastleButton("방 업그레이드 5종",x,top-369*u,w/2-3*u,26*u,TOUCH_FUNC_CASTLE_NEW_ROOMS);
            CastleButton("파츠 업그레이드 5종",x+w/2+3*u,top-369*u,w/2-3*u,26*u,TOUCH_FUNC_CASTLE_NEW_PARTS);
            CastleLabel(castleCategory?"지붕 · 성벽 · 내부 · 대포 · 차대":"창고 · 무기고 · 병영 · 공방 · 지휘실",DX/2,top-407*u,w,.53f*u);
        }
    } else {
        const bool room=castleCategory==0; const int lv=room?p.rooms[c][castleRow]:p.parts[c][castleRow];
        sprintf(s,"%s  Lv.%d / 5",room?castleRoomNames[castleRow]:castleRow==3?CastleArtillery::Of(c).name:castlePartNames[castleRow],lv);
        CastleLabel(s,DX/2,top-104*u,w,.8f*u);
        if(room) {
            const int img=CASTLE_ROOM_V4_FIRST_IMG+castleRow*6+lv;
            if(!sprite[img]) LoadImg(img);
            if(sprite[img]) DrawImageScale(512,128,0,0,x,top-126*u,false,0,0,0,0,w/512.0f,65*u/128.0f,sprite[img],img);
        } else if(castleRow==3) {
            DrawInventoryCannonIcon(c,lv,x,top-126*u,w/2-4*u,65*u);
            DrawInventoryCannonIcon(c,Min(5,lv+1),x+w/2,top-126*u,w/2-4*u,65*u);
        } else {
            SetSectionClip(x,top-126*u,w,65*u,false);
            CastlePartsDrawRect(c+1,x,top-126*u,w,65*u); UnSectionClip(false);
        }
        CastleLabel(room?castleRoomEffects[castleRow]:castlePartEffects[castleRow],DX/2,top-204*u,w,.57f*u);
        auto next=p; if(lv<5) { if(room) ++next.rooms[c][castleRow]; else ++next.parts[c][castleRow]; }
        sprintf(s,"성 전체 전투력 %lld → %lld",CastleTotalPower(p,c),CastleTotalPower(next,c));
        CastleLabel(s,DX/2,top-230*u,w,.7f*u);
        sprintf(s,"장비 배치 %d → %d칸 · 아이템 적재 %d → %d개",CastleEquipmentCapacity(c),CastleMenuModel::Equipment(next,c,GridTestCellCnt(c)),CastleInventoryCapacity(c),CastleMenuModel::Inventory(next,c,INVEN_BASE_SLOT,INVEN_PER_CASTLE,TOTALINVENTORY));
        CastleLabel(s,DX/2,top-255*u,w,.51f*u);
        CastleMenuGrid(c,x,top-276*u,w,67*u,u);
        sprintf(s,lv==5?"최대 단계":"골드 %d · 업그레이드",CastleMenuModel::UpgradeCost(c,lv,room));
        CastleButton(s,x,top-378*u,w/2-3*u,32*u,TOUCH_FUNC_CASTLE_NEW_UPGRADE,owned&&lv<5,BUTTON_COLOR_BEIGE);
        sprintf(s,lv==5?"최대 단계":"유료화폐 %d · 즉시 업그레이드",CastleMenuModel::PaidUpgradeCost(c,lv,room));
        CastleButton(s,x+w/2+3*u,top-378*u,w/2-3*u,32*u,TOUCH_FUNC_CASTLE_NEW_PAID_UPGRADE,owned&&lv<5,BUTTON_COLOR_PURPLE);
    }
    if(castleModal) {
        SetAlpha(24); MemRect(0,top,DX,top,COLOR_BLACK); SetAlpha(ALPHA_MAX);
        SetRectPoint(0,top,DX,top,TOUCH_FUNC_CASTLE_NEW_CANCEL);
        const int mt=DY/2+90*u; CastlePanel(x,mt,w,180*u);
        CastleLabel("성 구매 확인",DX/2,mt-12*u,w,.85f*u);
        CastleLabel(CastleStageAt(c)->title,DX/2,mt-43*u,w,.75f*u);
        const bool gold=castleModal==3;
        const int cost=gold?CastleMenuModel::GoldPrice(c):CastleMenuModel::Price(c);
        const long long balance=gold?robin.gold:robin.coin;
        sprintf(s,"%s %d · 보유 %lld",gold?"골드":"유료화폐",cost,balance);
        CastleLabel(s,DX/2,mt-78*u,w,.63f*u);
        CastleButton("취소",x+8*u,mt-124*u,w/2-12*u,30*u,TOUCH_FUNC_CASTLE_NEW_CANCEL);
        CastleButton("구매 확정",x+w/2+4*u,mt-124*u,w/2-12*u,30*u,TOUCH_FUNC_CASTLE_NEW_CONFIRM,balance>=cost);
    }
    CastleMenuToast(u);
}
