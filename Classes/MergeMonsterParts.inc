// Semantic CMF parts, roles and one authored monster action per player turn.
// Included inside Func_MergeRoulette.cpp's private presentation namespace.
namespace MonsterBoard {
static_assert(MonsterParts::AtlasCount==MONSTER_PARTS_LAST_IMG-MONSTER_PARTS_FIRST_IMG+1,"Register every monster part atlas");
struct Part {int slot=0,local=0,cx=0,cy=0,cw=1,ch=1,level=1;};
std::vector<Part> parts;Shape shape;
bool expanded=false;Box panelBox={0,0,0,0};
int builtStage=-1,builtWave=-1,builtNpc=-1,selected=-1;
int boardX=0,boardY=0,boardCell=0;
int partCount(){return (int)parts.size();}
const MonsterParts::PartDef& definition(const Part& p){
    const auto* enemy=MonsterParts::enemy(builtNpc);
    return MonsterParts::Parts[MonsterParts::Species[enemy->species].first+p.local];
}
static bool freeAt(int x,int y,int w,int h){
    for(int yy=y;yy<y+h;++yy)for(int xx=x;xx<x+w;++xx)if(!shape.contains(xx,yy))return false;
    for(const Part& p:parts)if(x<p.cx+p.cw&&p.cx<x+w&&y<p.cy+p.ch&&p.cy<y+h)return false;
    return true;
}
void build(int stage,int wave,int npc){
    builtStage=stage;builtWave=wave;builtNpc=npc;selected=-1;expanded=false;
    shape=castleShape(stage);parts.clear();
    const auto l=MonsterParts::loadout(npc,wave);
    if(l.species<0)return;
    const auto& species=MonsterParts::Species[l.species];
    for(int i=0;i<l.count;++i){
        Part p;p.slot=i;p.local=l.part[i];p.level=l.level;
        const auto& d=MonsterParts::Parts[species.first+p.local];p.cw=d.width;p.ch=d.height;
        int freeCells=0;
        for(int y=0;y<shape.height;++y)for(int x=0;x<shape.width;++x)freeCells+=shape.contains(x,y);
        for(const auto& placed:parts)freeCells-=placed.cw*placed.ch;
        bool placed=false;
        for(int attempt=0;attempt<2&&!placed;++attempt){
            // Reserve one cell per remaining accessory before spending cells on a long footprint.
            if(freeCells-p.cw*p.ch>=l.count-i-1)
              for(int y=0;y+p.ch<=shape.height&&!placed;++y)for(int x=0;x+p.cw<=shape.width&&!placed;++x)
                if(freeAt(x,y,p.cw,p.ch)){p.cx=x;p.cy=y;placed=true;}
            if(!placed)p.cw=p.ch=1;
        }
        if(placed)parts.push_back(p);
    }
}
void ensure(){
    if(siegeActive)return;
    const int npc=combatEnemyNpc();run.configureMonster(npc);
    if(builtStage!=run.stage||builtWave!=run.wave||builtNpc!=npc)build(run.stage,run.wave,npc);
}
int hitCount(){ensure();return run.monsterLoadout().weaponCount;}
bool attacking(){return !siegeActive&&enemyTurn.started&&!enemyTurn.complete;}
int activeWeapon(){
    if(!attacking())return 0;const int phase=enemyTurn.time.elapsed-enemyTurn.phases.approach;
    for(int i=(int)enemyTurn.weaponStarts.size()-1;i>=0;--i)if(phase>=enemyTurn.weaponStarts[i])return i;
    return 0;
}
const MonsterParts::ActionDef& shownAction(){
    const int i=activeWeapon();return attacking()&&i<(int)enemyTurn.weaponActions.size()?*enemyTurn.weaponActions[i]:run.monsterAction();
}
MonsterParts::Role effectiveRole(const Part& p){return run.monsterLoadout().role[p.slot];}
bool contributes(const Part& p){
    const auto l=run.monsterLoadout();const int weapon=activeWeapon();
    return effectiveRole(p)==MonsterParts::Attack&&weapon<l.weaponCount&&l.weapon[weapon]==p.slot;
}
int roleColor(MonsterParts::Role role){
    static const int colors[]={0xFFD59A,0xF07B72,0xC7A2F0,0x80B6E8,0x83D9AC};return colors[role];
}
void drawPartBlock(const Part& p,const Box& box){
    const auto* enemy=MonsterParts::enemy(builtNpc);if(!enemy)return;
    const auto& art=MonsterParts::Art[enemy->firstArt+p.local];const auto role=effectiveRole(p);
    const int image=MONSTER_PARTS_FIRST_IMG+art.page;if(!sprite[image])LoadImg(image);
    padArt(std::max(1,std::min((int)MaxLevel,p.level))+1,box);
    MemRectFrameThick(box.x,box.y,box.w,box.h,roleColor(role),std::max(1,(int)(DX/640.f)));
    if(!sprite[image])return;
    const int pad=std::max(1,(int)(4*DX/640.f));
    const float z=std::min((box.w-2*pad)/(float)art.w,(box.h-2*pad)/(float)art.h);
    const int dw=(int)(art.w*z),dh=(int)(art.h*z);
    DrawImageScale(art.w,art.h,art.x,art.y,box.x+(box.w-dw)/2,box.y-(box.h-dh)/2,false,0,0,0,0,z,z,sprite[image],image);
    if(box.w>=40*DX/640.f)label(MonsterParts::roleName(role),box.x+box.w/2,box.y-box.h+12*DX/640.f,.34f,roleColor(role));
}
void drawBoardAt(int bx,int by,int cell){
    boardX=bx;boardY=by;boardCell=cell;
    for(int row=0;row<shape.height;++row)for(int col=0;col<shape.width;++col)
        if(shape.contains(col,row))padArt((row+col)%2,{bx+col*cell,by-row*cell,cell,cell});
    for(int i=0;i<(int)parts.size();++i){
        const Part& p=parts[i];const bool lit=attacking()&&contributes(p);
        if(attacking()&&!lit)SetAlpha(22);
        const Box box={bx+p.cx*cell,by-p.cy*cell,p.cw*cell,p.ch*cell};drawPartBlock(p,box);SetAlpha(32);
        if(lit||selected==i)MemRectFrameThick(box.x,box.y,box.w,box.h,lit?0xFFE066:0xFFFFFF,std::max(2,cell/18));
    }
}
bool tapPanel(float x,float y){
    if(siegeActive)return false;
    if(topBoardPanel()||expanded){
        for(int i=0;i<(int)parts.size();++i){const auto& p=parts[i];
            if(Box{boardX+p.cx*boardCell,boardY-p.cy*boardCell,p.cw*boardCell,p.ch*boardCell}.has(x,y)){selected=i;return true;}
        }
    }
    if(topBoardPanel())return false;
    if(expanded){expanded=false;selected=-1;return true;}
    if(panelBox.has(x,y)){expanded=true;return true;}return false;
}
long long counterPreview(){return attacking()?enemyTurn.rawDamage:run.counterHit();}
void summary(char* text,size_t size){
    const auto& a=shownAction();const auto l=run.monsterLoadout();
    std::snprintf(text,size,u8"%s · 총 피해 %lld · 공격 %d개 · 부위 %d",a.name,counterPreview(),l.weaponCount,partCount());
}
void detail(char* text,size_t size){
    if(selected<0||selected>=(int)parts.size()){
        const auto l=run.monsterLoadout();
        std::snprintf(text,size,u8"피해 +%d%% · 방어 %d%% · 공격 후 재생 +%lld",MonsterParts::attackBonusPct(l),MonsterParts::defensePct(l),run.monsterHealing());return;
    }
    const auto& p=parts[selected];const auto& d=definition(p);const auto l=run.monsterLoadout();
    const auto role=effectiveRole(p);
    if(role==MonsterParts::Core)std::snprintf(text,size,u8"%s · 핵 · 몬스터 체력 %lld",d.name,run.enemyMax);
    else if(role==MonsterParts::Guard)std::snprintf(text,size,u8"%s · 방어 보강 · 전체 피해 경감 %d%%",d.name,MonsterParts::defensePct(l));
    else if(role==MonsterParts::Recovery){
        if(run.monsterActionTurn>=12)std::snprintf(text,size,u8"%s · 회복 보강 · 재생 소진",d.name);
        else std::snprintf(text,size,u8"%s · 공격 후 재생 +%lld · 잔여 %d회",d.name,attacking()?enemyTurn.healing:run.monsterHealing(),12-run.monsterActionTurn);
    }
    else if(role==MonsterParts::Support)std::snprintf(text,size,u8"%s 보강 · 전체 공격 피해 +%d%%",d.name,MonsterParts::attackBonusPct(l));
    else{int weapon=0;while(weapon<l.weaponCount&&l.weapon[weapon]!=p.slot)++weapon;
        const long long damage=attacking()&&weapon<(int)enemyTurn.rawShares.size()?enemyTurn.rawShares[weapon]:run.monsterWeaponDamage(weapon);
        std::snprintf(text,size,u8"%s · 1회 공격 · 피해 %lld",d.name,damage);}
}
void drawPanel(const Layout& l){
    if(siegeActive)return;ensure();const float s=l.scale;
    if(topBoardPanel()){
        const int cell=topPanelCell(),bw=cell*shape.width,bh=cell*shape.height;
        const int bx=(DX-bw)/2,by=topPanelTop();
        panelBox={bx-(int)(8*s),by+(int)(8*s),bw+(int)(16*s),bh+(int)(49*s)};
        SetAlpha(28);panel(panelBox,0x2A1E24,0x8C6170);SetAlpha(32);drawBoardAt(bx,by,cell);
        char text[192];summary(text,sizeof(text));label(text,DX/2,by-bh-(int)(4*s),.40f,0xFFD6C0);
        detail(text,sizeof(text));label(text,DX/2,by-bh-(int)(21*s),.31f,0xC9D3E8);return;
    }
    const int cell=std::max(5,(int)(l.cell*.22f)),bw=cell*shape.width,bh=cell*shape.height;
    const int bx=DX-bw-(int)(12*s),by=DY-(int)(12*s);
    panelBox={bx-(int)(5*s),by+(int)(5*s),bw+(int)(10*s),bh+(int)(26*s)};
    SetAlpha(26);panel(panelBox,0x2A1E24,0x8C6170);SetAlpha(32);drawBoardAt(bx,by,cell);
    label(shownAction().name,bx+bw/2,by-bh-(int)(3*s),.36f,0xFFD6C0);
}
void drawExpanded(const Layout& l){
    if(siegeActive||topBoardPanel())return;const bool live=attacking();if(!expanded&&!live)return;
    ensure();const float s=l.scale;const int cell=l.cell,gw=cell*shape.width,gh=cell*shape.height;
    const int gx=(DX-gw)/2,gy=l.board.y-(l.board.h-gh)/2;
    SetAlpha(live?14:30);MemRect(0,0,DX,DY,0x000000);SetAlpha(32);
    panel({gx-(int)(10*s),gy+(int)(10*s),gw+(int)(20*s),gh+(int)(66*s)},0x2A1E24,0xFFB08A);
    char text[192];summary(text,sizeof(text));label(text,DX/2,gy-gh-(int)(8*s),.43f,0xFFE6C0);
    detail(text,sizeof(text));label(text,DX/2,gy-gh-(int)(29*s),.33f,0xC9D3E8);
    drawBoardAt(gx,gy,cell);if(!live)label(u8"부위 터치: 역할 확인 · 바깥 터치: 닫기",DX/2,gy+(int)(28*s),.36f,0xC9D3E8);
}
}
