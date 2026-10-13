// Explicit isolated UI review; enabled only with CS_CASTLE_REVIEW_PATH.
static void CastleReviewTrace(const char* message) {
    const char* path=getenv("CS_CASTLE_REVIEW_PATH");
    if(!path) return;
    FILE* f=fopen((std::string(path)+"phases.log").c_str(),"a");
    if(f) { fprintf(f,"%s\n",message); fclose(f); }
}
static void CastleReviewClick(int command) {
    for (int i=touchIndex-1;i>=0;--i) if(touchRect[i][4]==command) {
        ExecTouchFunc(touchRect[i][0]+touchRect[i][2]/2,touchRect[i][1]-touchRect[i][3]/2);
        CastleReviewTrace(gTouchHitFunc==command?"PASS touch":"FAIL touch intercepted");
        return;
    }
    CastleReviewTrace("FAIL touch area missing");
}
static void CastleMenuReviewStep()
{
    const char* path = getenv("CS_CASTLE_REVIEW_PATH");
    if (!path) return;
    if (getenv("CS_BRIDGE_HP_REVIEW")) {
        static int bridgeTick=0;
        ++bridgeTick;
        if(bridgeTick==1) {
            robin.castle=CastleMenuModel::Clamp(atoi(getenv("CS_BRIDGE_HP_REVIEW"))-1);
            robin.castleProgress.version=1;
            robin.castleProgress.owned=1023u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.bossRoom=0;
            bossRaidMode=false;
            GotoPlay();
            StageRtBegin();
            StageRtSetAuto(false);
            while(popUpCnt>0) ClosePopUp();
        }
        // Explicit preview samples exercise full, partial and empty health pools.
        ao[PLAYER].maxhp=10000;
        ao[PLAYER].hp=bridgeTick<70?10000:bridgeTick<130?6800:0;
        ao[PLAYER].dead=false;
        for(int i=ENEMY;i<NEUTRAL;++i) ao[i].active=false;
        OBJECT& foe=ao[ENEMY];
        if(bridgeTick==1) {
            foe.type=crewData[CREWDATA_TYPE];
            SetNpc(&foe);
            foe.mom=ENEMY;
        }
        foe.active=true; foe.dead=false; foe.moveHandler=0;
        foe.maxhp=24000; foe.hp=bridgeTick<70?24000:bridgeTick<130?9600:0;
        const char* shot=bridgeTick==40?"bridge-full.png":bridgeTick==100?"bridge-damaged.png":bridgeTick==160?"bridge-empty.png":nullptr;
        if(shot) cocos2d::utils::captureScreen([](bool ok,const std::string&) {
            CastleReviewTrace(ok?"PASS bridge capture":"FAIL bridge capture");
        },std::string(path)+shot);
        if(bridgeTick==180) CastleReviewTrace("PASS bridge health review");
        return;
    }
    static int tick = 0;
    ++tick;
    if (tick == 1) {
        CastleReviewTrace("review setup");
        robin.castle = 0;
        robin.castleProgress = CastleMenuModel::Progress();
        CastleProgressEnsure();
        robin.gold = 1000000;
        robin.coin = 10000;
        GotoLobby();
        touchDisable = false;
        systemKey = AVK_POPUP_CASTLEMENU;
        PlayKey(PLAYER);
        CastleReviewTrace("castle menu opened");
    }
    if (tick == 70) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_NEXT);
    if (tick == 80) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_BUY);
    if (tick == 130) { CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_CONDITION); }
    if (tick == 190) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_ROOMS);
    if (tick == 200) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_ROW);
    if (tick == 250) { CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_UPGRADE); }
    if (tick == 310) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_BACK);
    if (tick == 320) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_PARTS);
    if (tick == 330) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_ROW + 3);
    if (tick == 370) {
        for (int i = 0; i < 5; ++i) robin.castleProgress.parts[0][i] = 5;
        CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_BACK);
    }
    if (tick == 380) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_BACK);
    if (tick == 390) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_NEXT);
    if (tick == 395) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_BUY);
    if (tick == 430) { CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_CONFIRM); }
    if(tick==280) CastleReviewTrace(robin.castleProgress.rooms[0][0]==1 && robin.gold==999760?"PASS room upgrade":"FAIL room upgrade");
    if(tick==460) CastleReviewTrace(CastleMenuModel::Owned(robin.castleProgress,1) && robin.coin==9400?"PASS paid purchase":"FAIL paid purchase");
    if(tick==480) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_BACK);
    if(tick==490) CastleReviewTrace(CastleMenuSwipe(DX*.75f,DY-GNBHEIGHT-100*_2X,DX*.25f,DY-GNBHEIGHT-100*_2X)?"PASS swipe next":"FAIL swipe next");
    if(tick==500) CastleReviewTrace(CastleMenuSwipe(DX*.25f,DY-GNBHEIGHT-100*_2X,DX*.75f,DY-GNBHEIGHT-100*_2X)?"PASS swipe previous":"FAIL swipe previous");
    if(tick==520 && !NetIsBusy()) {
        if(NetRequest(NETREQ_LOAD)) { robin.castleProgress=CastleMenuModel::Progress(); CastleReviewTrace("local server reload requested"); }
        else CastleReviewTrace("FAIL reload request");
    }
    if(tick==600) CastleReviewTrace(NetLastResult()==NETRESULT_OK &&
        CastleMenuModel::Owned(robin.castleProgress,1) && robin.castleProgress.rooms[0][0]==1 &&
        CastleMenuModel::Completed(robin.castleProgress,0)==25 && robin.coin==9400 && robin.gold==999760?
        "PASS local server save and reload":"FAIL local server save and reload");
    const char* shot = tick==40?"01-list.png":tick==100?"02-locked.png":
        tick==160?"03-parts.png":tick==220?"04-room.png":tick==280?"05-room-upgraded.png":
        tick==340?"06-cannon.png":tick==400?"07-purchase.png":tick==460?"08-purchased.png":nullptr;
    if (shot) cocos2d::utils::captureScreen([](bool ok,const std::string& file) {
        FILE* log = fopen((std::string(getenv("CS_CASTLE_REVIEW_PATH"))+"screens.log").c_str(),"a");
        if (log) { fprintf(log,"%s %s\n",ok?"PASS":"FAIL",file.c_str()); fclose(log); }
    },std::string(path)+shot);
}
