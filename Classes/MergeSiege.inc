//==========================================================================
// 공성전 (PVP 디버그) — 적의 성에 쳐들어간다
//
// 로비의 [PVP 디버그] 버튼으로 들어온다. 무대는 **상대의 성**(siegeHullStage,
// 기본 10성)이고 거울로 선다 - 포탑·대포가 오른쪽, 성주가 그 옆. 내 히어로는
// 왼쪽에서 올라탄다. 판은 **내 성의 칸**이다(올라탄 성이 아니라 내 적재함).
//
// 상대는 사람처럼 논다. 상대 턴이 오면 두 런을 통째로 맞바꾼다(swapSides:
// run↔foe, hero↔foeHero, stats↔foeStats). 그러면 릴·착지·끌기·합성·공격의
// 연출 코드가 손댈 것 없이 상대의 판으로 돌아간다. 상대의 손은 handX/handY 에
// 그린다 - 레버를 당기고, 블록을 집어 끌고 가 합치고, 공격 버튼을 누른다.
//
// 흐름
//   시작: 내 시작 뽑기(intro) → 상대 시작 뽑기(intro, 맞바꾼 상태) → 내 차례
//   내 차례: 평소 그대로. 내 공격은 run.enemyHp(상대 성 체력)를 깎는다.
//   상대 턴: aiSpins 번 돌려 착지, 합칠 수 있는 짝을 손으로 끌어 합치고, 공격.
//           상대 공격은 (맞바꾼 상태의) run.enemyHp = 내 성 체력을 깎는다.
//   끝: 상대 성 0 = 승리. 내 성 0 = 패배 화면.
//
// 상대 정보는 세이브(encode 문자열)로 받을 수 있게 loadFoe() 를 둔다. 실제
// 상대 데이터가 없는 동안은 dressFoe() 가 성 번호로 표본(다이애나)을 만든다.
// 몬스터의 반격(beginEnemyTurn)은 쓰지 않는다. 세이브하지 않는다.
//==========================================================================
namespace Siege {
Run foe;
Stats foeStats;
OBJECT foeHero;
ITEM foeEquipment[GearCount][MaxLevel];
const ITEM* foeGear=&foeEquipment[0][0];
int castle=9;            //무대가 되는 상대의 성(0~9)
int refRows=0;           //성 크기를 못 박는 기준 줄 수(내 성의 판)
int region=-1;           //원경. 상대가 가는 지역(세이브에서 받는다). -1 이면 성 번호로
int foeCostumeLevels[GearCount]={};
//phase: 0 내 차례 · 1 상대 턴 · 2 승리 · 3 상대 시작 뽑기 · 4 내 시작 뽑기 대기
int phase=0;
bool swapped=false;      //true 면 run 이 상대의 런이다
int timer=0,turnNo=0,aiSpins=3,spinsDone=0;
bool actedThisTurn=false;   //이번 턴에 하단 버튼을 한 번 눌렀는가 (하트 하나 = 한 번)
long long foeDamage=0;
enum Step{Idle,Pulling,Spinning,Dragging,Pressing,Attacking};
Step step=Idle;
//끌기 연출
int dragFrom=-1,dragTx=0,dragTy=0,dragFrame=0;
float dragX0=0,dragY0=0,dragX1=0,dragY1=0;
//손
bool handVisible=false;float handX=0,handY=0;
bool expanded=false;
Box panelBox={0,0,0,0};
bool busy(){return phase==1||phase==3||phase==4;}
bool blocked(){return phase!=0;}

//---- 두 런을 맞바꾼다 ----
void swapSides(){
    std::swap(run,foe);std::swap(hero,foeHero);std::swap(stats,foeStats);
    std::swap_ranges(costumeLevels,costumeLevels+GearCount,foeCostumeLevels);
    swapped=!swapped;
    gearTableOverride=swapped?foeGear:nullptr;
    hero.dirX=hero.dirF=swapped?LEFT:RIGHT;foeHero.dirX=foeHero.dirF=swapped?RIGHT:LEFT;
    updateHeroCostume(false);
    rememberReelSymbols();
    heroHealthDisplay=MergeCombat::AnimatedValue();heroHealthDisplay.set(run.lives);heroHealthDisplay.advance(1);
    enemyHealthDisplay=MergeCombat::AnimatedValue();enemyHealthDisplay.set(run.enemyHp);enemyHealthDisplay.advance(1);
    picked=finger=-1;
}
//---- 성주 다이애나 (표본) ----
//
//성 번호에 맞춰 장비를 만들어 입힌다. 총은 번호가 35까지라 성마다 3씩,
//나머지 부위는 8까지라 둘에 하나씩 오른다. 단은 성 번호의 두 배 + 10.
void dressFoe(){
    //몸은 cmf 가 고른다(requestHeroAction 과 같다). type 만 바꾸면 로빈 몸에 총을 든다.
    foeHero=hero;foeHero.type=foeHero.cmf=DIANA;
    if(cmfLoaded[DIANA]!=DIANA)CmfRead(DIANA,DIANA);
    static const int slots[GearCount]={EQUIP_WEAPON,EQUIP_ARMOR,EQUIP_BOOTS,EQUIP_HELM,EQUIP_GLOVE,EQUIP_PANTS};
    static const int types[GearCount]={ITEM_SWORD,ITEM_ARMOR,ITEM_GREAVES,ITEM_HELM,ITEM_GUNTLET,ITEM_KILT};
    const int lv=10+castle*2,grade=castle>=6?GRADE_RARE:GRADE_NORMAL;
    for(int g=0;g<GearCount;++g){
        const int type=types[g]+1;
        //총 번호는 성마다 2씩(10성 = 20번). 30번대 총은 그림이 사람보다 커서 표본으로 맞지 않다.
        const int detail=g==0?std::min(34,castle*2+2):std::min(7,castle/2+2);
        for(int l=0;l<MaxLevel;++l)
            MakeItem(&foeEquipment[g][l],type,lv,grade,MergeTrees::GearDetail(Sword+g,detail,l+1),0);
        //성주도 맨몸으로 시작해 판의 블록대로 입는다(updateHeroCostume). 수치는 끼고 있는 총 기준.
        std::memset(&foeHero.equip[slots[g]],0,sizeof(ITEM));foeHero.equip[slots[g]].type=EMPTY;foeHero.equipImg[slots[g]]=0;
    }
    ITEM gun;MakeItem(&gun,ITEM_GUN,lv,grade,std::min(34,castle*2+2),0);
    foeStats=stats;
    foeStats.weapon=std::max(20LL,std::min(GetEquipPower(&gun,lv),100000000LL));
    for(int g=0;g<GearCount;++g)foeCostumeLevels[g]=0;
}
//상대의 세이브(encode 문자열)로 상대 판을 받는다. 실패하면 false - 표본을 쓴다.
bool loadFoe(const std::string& saved){
    Run r;r.roster=&roster;
    if(saved.empty()||!r.decode(saved))return false;
    foe=r;return true;
}
void reset(){
    foe=Run();phase=0;swapped=false;timer=turnNo=spinsDone=0;foeDamage=0;step=Idle;actedThisTurn=false;
    dragFrom=-1;dragFrame=0;handVisible=expanded=false;
}
void begin(){
    siegeActive=false;siegeHullStage=-1;
    MergeRouletteBegin(false);
    if(!active)return;
    reset();
    siegeActive=true;siegeHullStage=castle;refRows=run.shape.height;
    //표본 상대는 다른 지역을 가고 있다고 본다(성 번호에서 한 바퀴 뒤). 실데이터가 오면 그 값.
    region=(castle+5)%STAGEBG_REGION_CNT;
    dressFoe();
    //상대 판은 상대 성의 칸이다(10성 48칸). 상대 턴에 판이 커지는 것이 맞다 -
    //큰 성은 칸이 많다. 실제 상대 데이터가 오면 loadFoe().
    foe.roster=&roster;foe.rng=((unsigned)MC_knlCurrentTimeStamp()*2654435761u)|1;
    foe.stage=castle;foe.setShape(castleShape(castle));
    refRows=std::max(run.shape.height,foe.shape.height);
    foe.start(pool,treeWeights);
    //양쪽 성의 체력 통. 그 성 몬스터 한 마리의 세 배 - 공격 서너 번이 오간다.
    //내 체력(run.lives)이 내 성, run.enemyHp 가 상대 성. 맞바꾸면 반대가 된다.
    const long long pool=hpFor(castle,0)*3;
    run.lives=run.maxLives=pool;run.enemyHp=run.enemyMax=pool;run.enemyAttack=0;
    foe.lives=foe.maxLives=pool;foe.enemyHp=foe.enemyMax=pool;foe.enemyAttack=0;
    heroHealthDisplay=MergeCombat::AnimatedValue();heroHealthDisplay.set(run.lives);heroHealthDisplay.advance(1);
    enemyHealthDisplay=MergeCombat::AnimatedValue();enemyHealthDisplay.set(run.enemyHp);enemyHealthDisplay.advance(1);
    turnNo=1;phase=4;   //내 시작 뽑기가 끝나면 상대 것을 보여 준다
    message="공성전 · 다이애나의 성에 올라탔다";messageTime=3;
}
//---- 상대의 손 ----
bool findMerge(int& from,int& tx,int& ty){
    for(int i=0;i<(int)run.board.size();++i)for(int j=0;j<(int)run.board.size();++j){
        if(i==j||!run.mergeable(run.board[j],run.board[i]))continue;
        Run trial=run;trial.roster=&roster;
        if(trial.place(false,i,run.board[j].x,run.board[j].y)){from=i;tx=run.board[j].x;ty=run.board[j].y;return true;}
    }
    return false;
}
void handTo(const Box& b){handVisible=true;handX=b.x+b.w*.5f;handY=b.y-b.h*.5f;}
//---- 턴 넘기기 ----
//
//하트 하나가 행동 하나다. 돌리기든 공격이든 하단 버튼을 한 번 누르면 턴이
//넘어간다. 합성(끌기)은 공짜라 제 턴 안에서 얼마든지 한다.
void startFoeTurn(){
    foe.lives=run.enemyHp;   //상대 성 체력을 상대 런에도 맞춰 둔다
    swapSides();phase=1;step=Idle;actedThisTurn=false;timer=0;run.spins=std::max(1,run.spins);
    message="상대 턴";messageTime=2;
}
//상대 턴이 끝났다(공격했으면 damage, 돌렸으면 0). 내 성 체력은 (맞바꾼) run.enemyHp 에 있다.
void endFoeTurn(long long damage){
    foeDamage=damage;
    const long long myPool=run.enemyHp;
    swapSides();
    run.lives=myPool;phase=0;++turnNo;step=Idle;handVisible=false;
    heroHealthDisplay=MergeCombat::AnimatedValue();heroHealthDisplay.set(run.lives);heroHealthDisplay.advance(1);
    if(run.lives<=0){run.lives=0;run.lost=true;message="성에서 밀려났습니다";}
    else{char text[96];std::snprintf(text,sizeof(text),damage>0?"%d턴 · 상대 공격 %lld · 내 차례":"%d턴 · 상대가 돌렸다 · 내 차례",turnNo,damage);message=text;}
    messageTime=3;
}
//내 돌리기 결과가 판에 다 앉았다(착지 비행 끝, 또는 트레이를 손으로 다 놓음) - 턴을 넘긴다.
void afterMySpin(){
    if(!siegeActive||swapped||phase!=0||!run.tray.empty()||run.lost)return;
    startFoeTurn();
}
//---- 공격이 끝났다(tick 의 finish 뒤). 누구 공격인지는 swapped 가 안다 ----
void afterAttack(bool killed){
    if(!swapped){
        foe.lives=run.enemyHp;
        if(killed){phase=2;message="공성 승리! 성 함락";messageTime=5;run.spins=0;run.tray.clear();PlayMusic(M_POWERUP);return;}
        startFoeTurn();
        return;
    }
    spinsDone=0;
    endFoeTurn(run.damageDone);
}
//---- 매 프레임. 틱을 막지 않는다(릴·착지·공격은 틱이 돌린다) ----
bool advance(){
    ++timer;
    if(phase==4){if(!introActive()){swapSides();introElapsed=0.f;phase=3;message="상대의 시작 뽑기";messageTime=2;}return false;}
    if(phase==3){if(!introActive()){swapSides();phase=0;message="내 차례";messageTime=2;}return false;}
    if(phase!=1)return false;
    const Layout l=layout();
    switch(step){
    case Idle:{
        if(spinFlying()||animation>0||run.attacking)return false;
        int from,tx,ty;
        //사람처럼: 먼저 합칠 수 있는 것을 다 합치고(공짜), 하단 버튼을 한 번 누르고, 턴을 넘긴다.
        if(findMerge(from,tx,ty)){
            dragFrom=from;dragTx=tx;dragTy=ty;dragFrame=0;
            const Box a=blockBox(run.board[from],l);
            dragX0=a.x+a.w*.5f;dragY0=a.y-a.h*.5f;
            Block target=run.board[from];target.x=tx;target.y=ty;
            const Box b=blockBox(target,l);
            dragX1=b.x+b.w*.5f;dragY1=b.y-b.h*.5f;
            step=Dragging;
        }
        else if(actedThisTurn){endFoeTurn(0);}
        else if(spinsDone<aiSpins&&run.canSpin()){handTo(l.lever);timer=0;step=Pulling;}
        else if(!run.board.empty()){handTo(l.attack);timer=0;step=Pressing;}
        else {endFoeTurn(0);}   //칠 것도 돌릴 자리도 없다 - 턴을 넘긴다
        return false;}
    case Pulling:
        if(timer>=18){
            run.spin();rememberReelSymbols();gearStartAngle=gearAngle;animation=REEL_SPIN_FRAMES;
            ++spinsDone;actedThisTurn=true;handVisible=false;step=Spinning;
        }
        return false;
    case Spinning:
        if(animation>0||spinFlying())return false;
        //자리가 없어 착지 못 한 결과는 상대도 어쩔 수 없다 - 버린다.
        if(!run.tray.empty()){run.tray.clear();}
        step=Idle;return false;
    case Dragging:{
        ++dragFrame;
        const float t=std::min(1.f,dragFrame/36.f),e=1.f-std::pow(1.f-t,3.f);
        pointerX=dragX0+(dragX1-dragX0)*e;pointerY=dragY0+(dragY1-dragY0)*e;
        handVisible=true;handX=pointerX;handY=pointerY;
        if(dragFrame<8){picked=-1;return false;}              //집기 전 잠깐
        picked=dragFrom;pickedTray=false;pickCellX=pickCellY=0;
        if(dragFrame>=44){
            picked=-1;
            if(run.place(false,dragFrom,dragTx,dragTy))observeDeckMerge();
            dragFrom=-1;handVisible=false;step=Idle;
        }
        return false;}
    case Pressing:
        if(timer>=18){
            handVisible=false;
            if(run.attack(stats)){actedThisTurn=true;animation=1;message="상대 공격!";messageTime=2;step=Attacking;}
            else endFoeTurn(0);
        }
        return false;
    case Attacking:
        return false;   //tick 이 공격을 돌리고 끝나면 afterAttack 을 부른다
    }
    return false;
}
//상대 판 터치: 작은 판을 누르면 펼치고, 펼친 상태에서는 아무 데나 누르면 닫는다.
bool tapPanel(float x,float y){
    if(expanded){expanded=false;return true;}
    if(panelBox.has(x,y)){expanded=true;return true;}
    return false;
}
//---- 그리기 ----
//몬스터 자리의 사람. 평소엔 성주, 맞바꾼 동안엔 내 히어로가 여기 선다.
void drawFoe(const Layout& l,int ex,int ey){
    const float s=l.scale;
    const float z=std::max(.35f*s,std::min(.82f*s,(DY-ey-8*s)/80.f))*1.5f;
    //DrawPlayer 의 dirF 는 몸만 돌리고 무기 그림은 객체의 dirX/dirF 를 본다 - 둘 다 맞춘다.
    foeHero.dirX=foeHero.dirF=swapped?RIGHT:LEFT;
    //다이애나의 쉬는 동작은 16장이 매 틱 바뀌어 떨려 보인다. 반 속도로 돌린다.
    DrawPlayer(&foeHero,heroNeutralMotion(foeHero,2),ex,ey,swapped?RIGHT:LEFT,z,0,false,true);
    label(swapped?"내 히어로":"성주 디아나",ex,ey+(int)(14*s),.42f,0xFFD0D0);
}
void drawBoardAt(const Run& r,int bx,int by,int cell){
    const ITEM* keep=gearTableOverride;
    gearTableOverride=swapped?nullptr:foeGear;   //foe 변수에 든 쪽의 장비 라인
    for(int row=0;row<r.shape.height;++row)for(int col=0;col<r.shape.width;++col)
        if(r.shape.contains(col,row))padArt((row+col)%2,{bx+col*cell,by-row*cell,cell,cell});
    for(const Block& b:r.board)drawBlock(b,{bx+b.x*cell,by-b.y*cell,Wide(b)*cell,Tall(b)*cell});
    gearTableOverride=keep;
}
void drawFoeBoard(const Layout& l){
    const float s=l.scale;
    const int cell=std::max(5,(int)(l.cell*.22f));
    const int bw=cell*foe.shape.width,bh=cell*foe.shape.height;
    const int plateH=(int)(70*s);
    const int bx=DX-bw-(int)(8*s),by=l.ground-(int)(4*s)+plateH+(int)(20*s)+bh;
    panelBox={bx-(int)(5*s),by+(int)(5*s),bw+(int)(10*s),bh+(int)(26*s)};
    SetAlpha(26);
    panel(panelBox,0x1E2433,0x61718C);
    label(swapped?"내 판":"상대 판",bx+bw/2,by-bh-(int)(3*s),.38f,0xFFE6C0);
    drawBoardAt(foe,bx,by,cell);
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
    char text[96];std::snprintf(text,sizeof(text),"%s · %d칸 · 예상 피해 %lld",swapped?"내 판":"디아나의 판",foe.shape.width*foe.shape.height,(long long)foe.preview(swapped?stats:foeStats));
    label(text,DX/2,gy-gh-(int)(8*s),.5f,0xFFE6C0);
    drawBoardAt(foe,gx,gy,big);
    label("터치하면 닫힙니다",DX/2,gy+(int)(30*s),.42f,0xC9D3E8);
}
//웨이브 헤더 자리. 맞바꾼 런의 성 번호를 읽어 "스테이지 10" 이 뜨던 것을 공성전 글로 바꾼다.
void drawHeader(const Layout& l){
    const float s=l.scale;
    const Box head={DX/2-(int)(200*s),(int)(70*s),(int)(400*s),(int)(44*s)};
    panel(head,0x182735,0xB99850);
    char text[96];std::snprintf(text,sizeof(text),"공성전 · 다이애나의 %d성 · %d턴",castle+1,turnNo);
    label(text,DX/2,head.y-(int)(8*s),.6f,0xFFE2A2);
}
void drawHud(const Layout& l){
    const float s=l.scale;
    drawFoeBoard(l);
    char text[96];
    const Box banner={DX/2-(int)(130*s),l.ground-(int)(3*s),(int)(260*s),(int)(28*s)};
    if(phase==1){
        const char* what=step==Pulling||step==Spinning?"상대 턴 · 룰렛":step==Dragging?"상대 턴 · 합성":step==Pressing||step==Attacking?"상대 턴 · 공격":"상대 턴";
        char line[96];std::snprintf(line,sizeof(line),"%s · 돌린 횟수 %d/%d",what,spinsDone,aiSpins);
        panel(banner,0x3A1F28,0xFFC966);label(line,DX/2,banner.y-(int)(6*s),.55f,0xFFE2A2);
    }else if(phase==3){
        panel(banner,0x3A1F28,0xFFC966);label("상대의 시작 뽑기",DX/2,banner.y-(int)(6*s),.55f,0xFFE2A2);
    }else if(phase==2){
        panel(banner,0x1F3A28,0xFFE066);label("공성 승리 · 나가기",DX/2,banner.y-(int)(6*s),.55f,0xFFF0B0);
    }
}
//상대의 손. 블록·릴 위에 올라와야 하므로 맨 끝에 그린다(drawExpanded 뒤).
void drawHand(const Layout& l){
    if(!handVisible)return;
    DrawHandAtTarget((int)handX,(int)handY,ticks/4,1.3f*l.scale);
}
}
