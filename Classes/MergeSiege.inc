//==========================================================================
// 공성전 (PVP 디버그) — 적의 성에 쳐들어간다
//
// 로비의 [PVP 디버그] 버튼으로 들어온다. 무대는 **상대의 성**이다. 성은
// 거울로 서고(포탑·대포가 오른쪽), 성주가 그 옆에 선다. 내 히어로는 왼쪽에서
// 올라탄다. 판과 룰렛은 내 것 그대로다 - 올라탄 성의 칸을 내 적재함으로 쓴다.
//
// 표본 상대: 높은 성(castle, 기본 10성)의 성주 다이애나. 장비는 그 성에 맞는
// 번호로 만들어 입히고(foeHero.equip), 상대 판의 장비 블록도 그 라인으로
// 그린다(foeEquipment → gearTableOverride). 공격 수치는 foeStats.
//
// 흐름
//   내 차례: 돌리기/합성/공격은 그대로. 공격 피해는 상대 성 체력(run.enemyHp).
//   상대 턴: 내 공격이 끝나면 상대가 aiSpins 번 돌려 자동으로 놓고 합칠 수
//           있는 것은 전부 합친 뒤 판 전체로 한 번 친다. 그 피해는 내 히어로
//           체력(run.lives)에 비례로 들어온다(한 턴 상한 40%).
//   끝:     상대 성 0 = 승리. 내 체력 0 = 기존 패배 화면.
//
// 상대 판은 오른쪽 가장자리에 작게 붙어 있고, 누르면 내 판 위에 같은 칸
// 크기로 펼쳐진다(다시 누르면 닫힘).
//
// 몬스터의 반격(beginEnemyTurn)은 쓰지 않는다. 세이브하지 않는다.
//==========================================================================
namespace Siege {
Run foe;
Stats foeStats;
OBJECT foeHero;
ITEM foeEquipment[GearCount][MaxLevel];
int castle=9;           //무대가 되는 상대의 성(0~9)
int phase=0;            //0 내 차례, 1 상대 턴 연출, 2 승리
int timer=0,turnNo=0,aiSpins=3;
long long foeDamage=0,lifeHit=0;
bool acted=false,expanded=false;
Box panelBox={0,0,0,0};
bool busy(){return phase==1;}
bool blocked(){return phase!=0;}

//---- 상대의 손: 합칠 수 있는 것은 전부 합친다 ----
void aiMergeAll(Run& r){
    for(int guard=0;guard<64;++guard){
        bool merged=false;
        for(int i=0;i<(int)r.board.size()&&!merged;++i)
            for(int j=0;j<(int)r.board.size()&&!merged;++j){
                if(i==j||!r.mergeable(r.board[j],r.board[i]))continue;
                if(r.place(false,i,r.board[j].x,r.board[j].y))merged=true;
            }
        if(!merged)break;
    }
}
void aiTurn(){
    foe.spins=SpinLimit;
    for(int k=0;k<aiSpins;++k){
        if(!foe.canSpin())break;
        foe.spin();
        while(!foe.tray.empty())if(!foe.autoPlace(0)){foe.tray.clear();break;}
        aiMergeAll(foe);
    }
    foeDamage=foe.preview(foeStats);
    lifeHit=foeDamage<=0?0:std::max(1LL,foeDamage*run.maxLives/std::max(1LL,run.enemyMax));
    //한 턴에 체력의 40% 까지. 상대는 합칠 수 있는 것을 다 합치므로 그대로 두면 한 방에 끝난다.
    lifeHit=std::min(lifeHit,std::max(1LL,run.maxLives*2/5));
}
void reset(){foe=Run();phase=0;timer=0;turnNo=0;foeDamage=lifeHit=0;acted=expanded=false;}
//---- 성주 다이애나 ----
//
//성 번호에 맞춰 장비를 만들어 입힌다. 총은 번호가 35까지라 성마다 3씩,
//나머지 부위는 8까지라 둘에 하나씩 오른다. 단은 성 번호의 두 배 + 10.
void dressFoe(){
    foeHero=hero;foeHero.type=1;   //다이애나
    static const int slots[GearCount]={EQUIP_WEAPON,EQUIP_ARMOR,EQUIP_BOOTS,EQUIP_HELM,EQUIP_GLOVE,EQUIP_PANTS};
    static const int types[GearCount]={ITEM_SWORD,ITEM_ARMOR,ITEM_GREAVES,ITEM_HELM,ITEM_GUNTLET,ITEM_KILT};
    const int lv=10+castle*2,grade=castle>=6?GRADE_RARE:GRADE_NORMAL;
    for(int g=0;g<GearCount;++g){
        const int type=types[g]+1;
        const int detail=g==0?std::min(34,castle*3+4):std::min(7,castle/2+2);
        MakeItem(&foeHero.equip[slots[g]],type,lv,grade,detail,0);
        for(int l=0;l<MaxLevel;++l)
            MakeItem(&foeEquipment[g][l],type,lv,grade,MergeTrees::GearDetail(Sword+g,detail,l+1),0);
    }
    foeStats=stats;
    foeStats.weapon=std::max(20LL,std::min(GetEquipPower(&foeHero.equip[EQUIP_WEAPON],lv),100000000LL));
}
void begin(){
    siegeActive=false;
    MergeRouletteBegin(false);
    if(!active)return;
    reset();
    siegeActive=true;
    //무대는 상대의 성. 내 판도 그 성의 칸을 쓴다(올라탔으니까).
    run.stage=castle;run.setShape(castleShape(castle));
    dressFoe();
    foe.roster=&roster;foe.rng=((unsigned)MC_knlCurrentTimeStamp()*2654435761u)|1;
    foe.stage=castle;foe.setShape(castleShape(castle));
    foe.start(pool,treeWeights);
    //양쪽 성의 체력. 그 성 몬스터 한 마리의 세 배 - 공격 서너 번이 오간다.
    run.enemyHp=run.enemyMax=hpFor(castle,0)*3;
    run.enemyAttack=0;
    enemyHealthDisplay=MergeCombat::AnimatedValue();enemyHealthDisplay.set(run.enemyHp);enemyHealthDisplay.advance(1);
    turnNo=1;message="공성전 · 다이애나의 성에 올라탔다";messageTime=3;
}
//내 공격이 끝났다(tick 의 finish 뒤).
void afterPlayerAttack(bool killed){
    if(killed){phase=2;message="공성 승리! 성 함락";messageTime=5;run.spins=0;run.tray.clear();PlayMusic(M_POWERUP);return;}
    phase=1;timer=0;acted=false;message="상대 턴";messageTime=2;
}
//상대 턴 연출. 한 프레임을 삼켰으면 true.
bool advance(){
    if(phase!=1)return false;
    ++timer;
    if(timer==20&&!acted){acted=true;aiTurn();PlayMusic(M_ROULETTEUP);}
    if(timer==80){
        if(lifeHit>0){
            const long long before=run.lives;
            run.lives=std::max(0LL,run.lives-lifeHit);
            floatingDamage(before-run.lives,false);allyFlash=20;PlayMusic(M_SWORDHIT);
            heroHealthDisplay.set(run.lives);
            if(run.lives==0)run.lost=true;
        }else{allyFlash=20;}
    }
    if(timer>=130){
        phase=0;++turnNo;
        run.spins=SpinLimit;
        char text[96];std::snprintf(text,sizeof(text),"%d턴 · 상대 피해 %lld",turnNo,foeDamage);
        message=run.lost?"성에서 밀려났습니다":text;messageTime=3;
    }
    return true;
}
//상대 판 터치: 작은 판을 누르면 펼치고, 펼친 상태에서는 아무 데나 누르면 닫는다.
bool tapPanel(float x,float y){
    if(expanded){expanded=false;return true;}
    if(panelBox.has(x,y)){expanded=true;return true;}
    return false;
}
//---- 그리기 ----
void drawFoe(const Layout& l,int ex,int ey){
    const float s=l.scale;
    const float z=std::max(.35f*s,std::min(.82f*s,(DY-ey-8*s)/80.f))*1.5f;
    if(busy()&&timer>=70&&timer<90)SetColor(0xFFE2A2);
    DrawPlayer(&foeHero,heroNeutralMotion(foeHero),ex,ey,LEFT,z,0,false,true);
    SetColor(0);
    label("성주 디아나",ex,ey+(int)(14*s),.42f,0xFFD0D0);
}
void drawBoardAt(int bx,int by,int cell,bool big){
    gearTableOverride=&foeEquipment[0][0];
    for(int row=0;row<foe.shape.height;++row)for(int col=0;col<foe.shape.width;++col)
        if(foe.shape.contains(col,row))padArt((row+col)%2,{bx+col*cell,by-row*cell,cell,cell});
    for(const Block& b:foe.board)drawBlock(b,{bx+b.x*cell,by-b.y*cell,Wide(b)*cell,Tall(b)*cell});
    gearTableOverride=nullptr;
    (void)big;
}
void drawFoeBoard(const Layout& l){
    const float s=l.scale;
    //작은 판: 오른쪽 가장자리에 붙인다.
    const int cell=std::max(5,(int)(l.cell*.22f));
    const int bw=cell*foe.shape.width,bh=cell*foe.shape.height;
    const int plateH=(int)(70*s);
    const int bx=DX-bw-(int)(8*s),by=l.ground-(int)(4*s)+plateH+(int)(20*s)+bh;
    panelBox={bx-(int)(5*s),by+(int)(5*s),bw+(int)(10*s),bh+(int)(26*s)};
    SetAlpha(busy()?32:26);
    panel(panelBox,0x1E2433,busy()?0xFFC966:0x61718C);
    label("상대 판",bx+bw/2,by-bh-(int)(3*s),.38f,0xFFE6C0);
    drawBoardAt(bx,by,cell,false);
    SetAlpha(32);
}
//펼친 판: 내 판 위에 같은 칸 크기로. 내 블록이 그려진 뒤에 불러야 덮인다(MergeRouletteDraw 끝).
void drawExpanded(const Layout& l){
    if(!expanded)return;
    const float s=l.scale;
    const int big=l.cell,gw=big*foe.shape.width,gh=big*foe.shape.height;
    const int gx=(DX-gw)/2,gy=l.board.y-(l.board.h-gh)/2;
    SetAlpha(30);MemRect(0,0,DX,DY,0x000000);SetAlpha(32);
    panel({gx-(int)(10*s),gy+(int)(10*s),gw+(int)(20*s),gh+(int)(52*s)},0x1E2433,0xFFC966);
    char text[96];std::snprintf(text,sizeof(text),"디아나의 판 · %d칸 · 돌리기 x%d · 예상 피해 %lld",foe.shape.width*foe.shape.height,aiSpins,(long long)foe.preview(foeStats));
    label(text,DX/2,gy-gh-(int)(8*s),.5f,0xFFE6C0);
    drawBoardAt(gx,gy,big,true);
    label("터치하면 닫힙니다",DX/2,gy+(int)(30*s),.42f,0xC9D3E8);
}
void drawHud(const Layout& l){
    const float s=l.scale;
    drawFoeBoard(l);
    char text[96];
    std::snprintf(text,sizeof(text),"공성전 %d턴 · %d성 · 상대 돌리기 x%d",turnNo,castle+1,aiSpins);
    label(text,DX/2,(int)(60*s),.46f,0xFFE6C0);
    if(phase==1){
        const Box banner={DX/2-(int)(120*s),l.ground-(int)(3*s),(int)(240*s),(int)(28*s)};
        panel(banner,0x3A1F28,0xFFC966);
        label(timer<20?"상대 턴":timer<80?"상대가 판을 짭니다":"상대 공격!",DX/2,banner.y-(int)(6*s),.55f,0xFFE2A2);
    }else if(phase==2){
        const Box banner={DX/2-(int)(120*s),l.ground-(int)(3*s),(int)(240*s),(int)(28*s)};
        panel(banner,0x1F3A28,0xFFE066);
        label("공성 승리 · 나가기",DX/2,banner.y-(int)(6*s),.55f,0xFFF0B0);
    }
}
}
