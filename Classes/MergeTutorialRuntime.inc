//---- 합성 전투판 튜토리얼 (docs/기획_튜토리얼_합성.md) ----
//
//Func_MergeRoulette.cpp 가 MergeRouletteTouch 바로 앞에서 포함한다. 상태기는 CastleTutorialModel.h,
//마스크·손·안내판·저장은 CastleTutorialRuntime.inc 다. 여기는 전투판이 아는 것만 둔다:
//  어디를 밝힐지(focus) · 무슨 터치를 막을지(gate) · 두 마리의 체력과 둘째 룰렛 고정(fixture) · 로비 힌트 · 리뷰 운전.
namespace MergeTutorial {
using namespace CastleTutorial;
inline bool live(){return CastleTutorialLive()&&!siegeActive&&gCastleTutorialStep>Welcome&&gCastleTutorialStep<Done;}
inline bool inBattle(){return live()&&active;}
inline int step(){return gCastleTutorialStep;}
inline bool transitioning(){return automaticMerge.active()||entering()||introActive()||spinFlying()||deckArriving()||waveTransition.active()||animation!=0||run.attacking;}
inline void put(int r[4],const Box& b){r[0]=b.x;r[1]=b.y;r[2]=b.w;r[3]=b.h;}
inline Box traySlot(const Layout& l,int i){return {l.slot.x+l.slot.w*i/3,l.slot.y,l.slot.w/3,l.slot.h};}
Box lastAllyPlate={0,0,0,0},lastWaveHeader={0,0,0,0};
bool fixtureFirst=false,fixtureSecond=false;   //두 마리의 체력을 한 번씩만 맞춘다
//판 위에 같은 계열·같은 단의 짝이 있는 트레이 칸. 없으면 -1.
inline int trayMate(int* boardIndex){
    for(int t=0;t<(int)run.tray.size();++t)for(int k=0;k<(int)run.board.size();++k){
        const Block& a=run.tray[t];const Block& b=run.board[k];
        if(a.family==b.family&&a.level==b.level&&(a.family>=Roles||a.crew==b.crew)){if(boardIndex)*boardIndex=k;return t;}
    }
    return -1;
}
//자동 합성이 꺼져 있으면 합성은 판에서 직접 끌어서 한다 - 그때 밝힐 짝(끌 것, 받을 것).
inline bool boardPair(int* from,int* to){
    if(!run.tray.empty()||automaticMergesEnabled())return false;
    Run plan;bool fromTray=false;int a=-1,b=-1;
    if(!run.automaticMergePlan(plan,fromTray,a,b)||fromTray)return false;
    if(from)*from=a;
    if(to)*to=b;
    return true;
}
//---- 어디를 밝힐지 ----
int focus(int rects[2][4]){
    if(!live())return 0;
    const Layout l=layout();
    if(!active){
        if(step()!=Depart||drawHandle!=MD_LOBBY||popUpCnt>0||LoadoutOpen()||resumePromptOpen)return 0;
        put(rects[0],entryChoiceOpen?entryChoiceBox(1):lobbyStart(l));return 1;
    }
    if(step()==Reward){
        if(!RewardPopup::open()||!RewardPopup::ready()||waveTransition.age<MergeCombat::WaveTransition::DefeatFrames)return 0;
        rects[0][0]=RewardPopup::bx;rects[0][1]=RewardPopup::by;rects[0][2]=RewardPopup::bw;rects[0][3]=RewardPopup::bh;return 1;
    }
    if(RewardPopup::open()||quitPromptOpen||transitioning())return 0;
    switch(step()){
    case Spin:put(rects[0],l.spin);return 1;
    case Land:put(rects[0],l.board);return 1;   //결과가 내려앉고 자동 합성이 끝난 판을 2초 본다
    case Merge:{
        if(run.tray.empty()){
            int a=-1,b=-1;
            if(!boardPair(&a,&b)){put(rects[0],l.spin);return 1;}
            if(picked>=0)return 0;
            put(rects[0],blockBox(run.board[a],l));put(rects[1],blockBox(run.board[b],l));return 2;}
        int k=-1;const int t=trayMate(&k);if(t<0||picked>=0)return 0;
        put(rects[0],traySlot(l,t));put(rects[1],blockBox(run.board[k],l));return 2;}
    case Attack:put(rects[0],l.attack);return 1;
    case Energy:put(rects[0],l.heart);return 1;
    case Shield:if(lastAllyPlate.w<=0)return 0;put(rects[0],lastAllyPlate);return 1;
    case Cannon:put(rects[0],l.cannon);return 1;
    case Free:if(lastWaveHeader.w<=0)return 0;put(rects[0],lastWaveHeader);return 1;
    default:return 0;
    }
}
//---- 무슨 터치를 막을지 ----
//
//조작 단계는 그 단계의 네모 안에서 시작한 터치만 통과한다. 관찰 단계는 아무 터치나 Observed 로 넘기고 먹는다.
//true 를 돌려주면 이 터치는 여기서 끝이다. 나가기(exit)는 부르는 쪽이 먼저 처리해 두었다.
bool gate(int phase,float x,float y){
    if(!inBattle())return false;
    if(RewardPopup::open()||quitPromptOpen)return false;
    const Layout l=layout();
    //「건너뛰기」 단추(CastleTutorialDraw 가 그린다). 전투판은 터치를 전부 먹으므로 여기서 직접 받는다.
    if(Skippable(step())&&phase==0){
        const int bx=DX-124,by=DY-LOBBY_BAR_H-8,bw=112,bh=std::max(48,(int)(48*DX/640.f));
        if(x>=bx&&x<bx+bw&&y<=by&&y>by-bh){CastleTutorialCommand(TOUCH_FUNC_TUTORIAL_SKIP);PlayMusic(M_BUTTON);return true;}
    }
    if(Observing(step())){
        if(phase==0&&!transitioning())CastleTutorialEvent(Observed);
        return true;
    }
    if(phase!=0)return false;   //이미 시작한 드래그는 그대로 간다
    switch(step()){
    case Spin:return !l.spin.has(x,y);
    case Merge:{
        if(!run.tray.empty())return !l.slot.has(x,y);
        int a=-1,b=-1;
        if(!boardPair(&a,&b))return !l.spin.has(x,y);
        return !blockBox(run.board[a],l).has(x,y)&&!blockBox(run.board[b],l).has(x,y);}
    case Attack:return !l.attack.has(x,y);
    case Cannon:return !l.cannon.has(x,y);
    default:return false;   //Guard(반격을 기다림)·Reward 는 자유
    }
}
inline bool trashLocked(){return inBattle()&&step()<=Merge;}
//---- 픽스처 ----
//
//첫 몬스터: 공격 단계에 들어서는 순간 체력 = preview × 70% (한 번에 죽는다).
//둘째 몬스터: 첫 공격 직전 체력 = preview + 대포 한 발 × 80% (한 번 견디고, 남은 몫은 대포 안).
//둘째 룰렛: 트레이 한 칸을 판 위 블록과 같은 것으로 바꿔 합성이 반드시 성립하게 한다.
void beginBattle(){fixtureFirst=fixtureSecond=false;}
void onStepEntered(){
    if(!inBattle())return;
    if(step()==Attack&&!fixtureFirst&&!run.attacking){
        fixtureFirst=true;
        const long long hp=std::max(1LL,run.preview(stats)*70/100);
        run.enemyHp=run.enemyMax=hp;enemyHealthDisplay.set(hp);enemyHealthDisplay.advance(1);
    }
}
long long fixtureWant=0;   //리뷰가 본다: 마지막으로 맞춘 체력
void beforeAttack(){
    if(!inBattle())return;
    //첫 몬스터: 단계에 들어설 때 맞춘 값을 공격 직전에 한 번 더 맞춘다 - 그 사이 남은 트레이를 놓거나 자동 합성이 돌아 판이 변했을 수 있다.
    if(step()==Attack){const long long hp=std::max(1LL,run.preview(stats)*70/100);fixtureWant=hp;run.enemyHp=run.enemyMax=hp;enemyHealthDisplay.set(hp);enemyHealthDisplay.advance(1);return;}
    if(fixtureSecond)return;
    if(step()!=Energy&&step()!=Guard)return;
    fixtureSecond=true;
    const long long hp=std::max(1LL,run.preview(stats)+cannonShell()*80/100);
    run.enemyHp=run.enemyMax=hp;enemyHealthDisplay.set(hp);enemyHealthDisplay.advance(1);
}
void afterSpin(){
    if(!inBattle()||step()!=Merge||run.tray.empty())return;
    if(trayMate(nullptr)>=0)return;
    for(int k=0;k<(int)run.board.size();++k){
        const Block& b=run.board[k];
        if(b.level!=1)continue;
        if(b.family<Roles&&(b.crew<0||b.crew>=64))continue;
        Block t=b;t.x=t.y=-1;t.rot=false;run.tray[0]=t;return;
    }
}
void unlockFixture(){   //건너뛰기: 그 자리 몬스터 체력을 실제 값으로
    if(!active||siegeActive)return;
    if(fixtureFirst||fixtureSecond){run.enemyHp=run.enemyMax=waveHp(run.stage,run.wave);enemyHealthDisplay.set(run.enemyHp);enemyHealthDisplay.advance(1);}
    fixtureFirst=fixtureSecond=true;
}
//---- 로비 힌트: 처음 쓸 수 있게 된 순간 한 번 ----
int hintShownThisVisit=0;
void drawLobbyHints(const Layout& l){
    if(!CastleTutorialLive()||gCastleTutorialStep<Done||popUpCnt>0||LoadoutOpen()||entryChoiceOpen||resumePromptOpen||RewardPopup::open())return;
    int hint=0;Box target={0,0,0,0};const char* text="";
    const int castle=std::max(0,std::min(9,(int)robin.castle));
    if(!CastleTutorialHintSeen(HintVault)&&CastleIncomeNow()>0){hint=HintVault;target=CastleVault::box();text=u8"성이 모은 골드를 걷으세요";}
    else if(!CastleTutorialHintSeen(HintExpedition)&&MergeExpedition::affordable(robin.heart)){hint=HintExpedition;target=lobbyStart(l);text=u8"전투 시작 안의 원정: 번개로 바로 정산";}
    else if(!CastleTutorialHintSeen(HintEquip)){
        bool spare=false;
        for(int i=0;i<TOTALINVENTORY&&!spare;++i){const ITEM& it=robin.inven[i];if(it.type==EMPTY||!IsEquipItemType(it.type)||it.lv<=0)continue;
            bool worn=false;for(int e=0;e<TOTALEQUIP&&!worn;++e)worn=ao[PLAYER].equip[e].type!=EMPTY&&ao[PLAYER].equip[e].id==it.id;
            spare=!worn;}
        if(spare){hint=HintEquip;const Box nav=lobbyBottomNav();target={nav.x+nav.w/5,nav.y,nav.w/5,nav.h};text=u8"새 장비를 끼면 히어로가 세집니다";}
    }
    if(!hint&&!CastleTutorialHintSeen(HintCastle)&&robin.gold>=CastleMenuModel::UpgradeCost(castle,0,true)){hint=HintCastle;const Box nav=lobbyBottomNav();target={nav.x+nav.w*4/5,nav.y,nav.w/5,nav.h};text=u8"성을 올리면 생산·공격·활력·방어";}
    if(!hint||(hintShownThisVisit&&hintShownThisVisit!=hint))return;
    if(!hintShownThisVisit){hintShownThisVisit=hint;CastleTutorialHintMark(hint);}
    const float s=l.scale;
    SetAlpha(32);DrawHandAtTarget(target.x+target.w/2,target.y-target.h/2,robin.playtime/MOTIONDIV,1.6f);
    const int w=(int)(360*s),x=std::max((int)(8*s),std::min(DX-w-(int)(8*s),target.x+target.w/2-w/2));
    const int top=target.y+(int)(56*s)>DY-(int)(60*s)?target.y-target.h-(int)(8*s):target.y+(int)(56*s);
    DrawUiPanel(x,top,w,(int)(44*s),0x163C46,0xE4C374);
    DrawUiTextBox(text,x+(int)(8*s),top,w-(int)(16*s),(int)(44*s),0xFFF0CD,.8f);
}
//---- 리뷰 운전 (CS_TUTORIAL_REVIEW=fresh) ----
//
//사람처럼 누르고 끌어서 열 단계를 다 지난다. 한 틱에 한 걸음. 끝나면 true.
int reviewTick=0,reviewPhase=0,reviewWait=0;
inline void tapBox(const Box& b){const float x=b.x+b.w*.5f,y=b.y-b.h*.5f;MergeRouletteTouch(0,777,x,y);MergeRouletteTouch(2,777,x,y);}
inline void dragBox(const Box& a,const Box& b){
    const float x0=a.x+a.w*.5f,y0=a.y-a.h*.5f,x1=b.x+b.w*.5f,y1=b.y-b.h*.5f;
    MergeRouletteTouch(0,778,x0,y0);MergeRouletteTouch(1,778,(x0+x1)*.5f,(y0+y1)*.5f);MergeRouletteTouch(2,778,x1,y1);
}
bool reviewDrive(void (*trace)(const char*),void (*capture)(const char*)){
    int rects[2][4]={};
    if(reviewWait>0){--reviewWait;return false;}
    const int n=focus(rects);
    auto box=[&](int i){return Box{rects[i][0],rects[i][1],rects[i][2],rects[i][3]};};
    switch(reviewPhase){
    //조작 단계는 "밝힌 화면을 찍고(1.6초 뒤) → 100틀 뒤에 누른다". 누르고 찍으면 다음 상태가 찍힌다.
    case 0: if(step()==Spin&&n==1){capture("tutorial-01-spin");reviewPhase=100;reviewWait=110;}return false;
    case 100: if(step()==Spin&&n==1){tapBox(box(0));reviewPhase=1;reviewWait=6;}return false;
    case 1: if(step()==Land&&n==1){capture("tutorial-02-land");reviewPhase=2;reviewWait=150;}   //착지 관찰은 시간으로 지나간다
            return false;
    case 2: if(step()==Merge&&n>=1&&run.tray.empty()){
                trace("PASS landing observation advances by time");
                const Layout l=layout();tapBox(l.attack);   //막힌 단추: 아무 일도 없어야 한다
                if(run.attacking){trace("FAIL tutorial gate let attack through during merge");return true;}
                capture("tutorial-03-merge");reviewPhase=200;reviewWait=110;}
            return false;
    case 200: if(step()==Merge&&n>=1&&run.tray.empty()){if(n==1)tapBox(box(0));reviewPhase=21;reviewWait=6;}return false;
    case 21: if(step()==Merge&&n==2){int k=-1;const bool paired=run.tray.empty()?boardPair(nullptr,nullptr):trayMate(&k)>=0;trace(paired?"PASS second spin carries exactly one merge partner":"FAIL merge fixture");dragBox(box(0),box(1));reviewWait=20;}   //판이 꽉 차 손으로 놓는 경우
             if(step()==Attack){trace("PASS merging the fixed duplicate advances to attack");reviewPhase=3;reviewWait=30;}
             return false;
    case 3: if(step()==Attack&&n==1){capture("tutorial-04-attack");reviewPhase=300;reviewWait=110;}return false;
    case 300: {if(step()!=Attack||n!=1)return false;
            const long long want=std::max(1LL,run.preview(stats)*70/100);   //누르기 직전의 판으로 잰다(공격이 지속 피해 턴을 소모하기 전)
            tapBox(box(0));
            if(run.enemyMax!=want||fixtureWant!=want){char line[160];std::snprintf(line,sizeof(line),"INFO fixture want=%lld max=%lld hp=%lld fixtureWant=%lld attacking=%d",want,run.enemyMax,run.enemyHp,fixtureWant,(int)run.attacking);trace(line);}
            trace(run.enemyMax==want&&fixtureWant==want?"PASS first monster health is seventy percent of the board":"FAIL first monster fixture");
            reviewPhase=4;reviewWait=10;return false;}
    case 4: /*처치 즉시 다음 몬스터 체력이 들어오므로 웨이브 번호로 본다*/ if(step()==Reward&&n==1){trace(run.wave==1?"PASS first attack kills the fixture monster":"FAIL first kill");capture("tutorial-05-reward");reviewPhase=400;reviewWait=110;}return false;
    case 400: if(step()==Reward&&n==1){tapBox(box(0));reviewPhase=5;reviewWait=10;}return false;
    case 5: if(step()==Energy&&n==1){capture("tutorial-06-energy");reviewPhase=6;reviewWait=150;}return false;   //2초 관찰이 스스로 지나간다
    case 6: if(step()==Guard){trace("PASS energy observation advances by time");const Layout l=layout();tapBox(l.attack);reviewPhase=7;reviewWait=10;}return false;
    case 7: if(step()==Shield&&n==1){
                //반격 뒤 턴이 끝나며 방어구가 통을 도로 채울 수 있으므로 통 잔량이 아니라 "살아 있고 체력은 그대로" 를 본다.
                char line[160];std::snprintf(line,sizeof(line),"INFO guard step hp=%lld guard=%lld/%lld lives=%lld/%lld",run.enemyHp,run.guard,run.guardMax,run.lives,run.maxLives);trace(line);
                trace(run.enemyHp>0&&run.lives==run.maxLives?"PASS second monster survives and the counter hits the shield only":"FAIL guard fixture");
                capture("tutorial-07-shield");reviewPhase=8;reviewWait=150;}
            return false;
    case 8: if(step()==Cannon&&n==1){trace(run.enemyHp<=cannonShell()?"PASS remaining health fits one cannon shell":"FAIL cannon fixture");capture("tutorial-08-cannon");reviewPhase=800;reviewWait=110;}return false;
    case 800: if(step()==Cannon&&n==1){tapBox(box(0));reviewPhase=9;reviewWait=10;}return false;
    case 9: if(RewardPopup::open()&&RewardPopup::ready()){tapBox({RewardPopup::bx,RewardPopup::by,RewardPopup::bw,RewardPopup::bh});reviewPhase=10;reviewWait=10;}return false;
    case 10: if(step()==Free&&n==1){capture("tutorial-09-free");reviewPhase=11;reviewWait=150;}return false;
    case 11: if(step()==Done){trace("PASS tutorial reaches done after the free observation");return true;}
            if(++reviewTick%120==0){char line[200];std::snprintf(line,sizeof(line),"INFO free wait step=%d focus=%d transitioning=%d anim=%d wave=%d popup=%d header=%d",step(),n,(int)transitioning(),animation,(int)waveTransition.active(),(int)RewardPopup::open(),lastWaveHeader.w);trace(line);}
            return false;
    }
    return false;
}
}
int MergeTutorialFocus(int rects[2][4]){return MergeTutorial::focus(rects);}
void MergeTutorialBeginBattle(){MergeTutorial::beginBattle();MergeTutorial::hintShownThisVisit=0;}
void MergeTutorialRememberAllyPlate(int x,int y,int w,int h){MergeTutorial::lastAllyPlate={x,y,w,h};}
void MergeTutorialRememberHeader(int x,int y,int w,int h){MergeTutorial::lastWaveHeader={x,y,w,h};}
void MergeTutorialDrawLobbyHints(){MergeTutorial::drawLobbyHints(layout());}
bool MergeTutorialReviewDrive(void (*trace)(const char*),void (*capture)(const char*)){return MergeTutorial::reviewDrive(trace,capture);}
void MergeTutorialUnlock(){MergeTutorial::unlockFixture();}
