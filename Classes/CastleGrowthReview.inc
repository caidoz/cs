// Isolated native review of nineteen-stage growth and natural-size scrolling.
static bool CastleGrowthReview(const char* path){
 if(!getenv("CS_CASTLE_GROWTH_REVIEW"))return false;
 static int tick=0;static bool pending=false;if(pending)return true;++tick;
 if(tick==1){NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);robin.castle=0;robin.castleProgress={};robin.castleProgress.version=3;robin.castleProgress.owned=1;robin.gold=1000000;}
 if(tick==20){CastleReviewClick(TOUCH_FUNC_POPUP_CASTLEMENU);PlayKey(PLAYER);systemKey=0;}
 if(tick>=40&&tick<58)CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_NEXT);
 if(tick==65){CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_NEXT);CastleReviewTrace(CastleMenuGrowthBrowse()==18&&robin.castle==0&&robin.castleProgress.owned==1?"PASS nineteen stages browse without selecting or granting castles":"FAIL stage browsing");CastleReviewTrace(MergeRouletteCastleUpgradeHeight(CastleMenuGrowthBrowse())>1000&&scT[MENU_CASTLE]>0?"PASS largest castle retains native scale and scrolls":"FAIL preview scale");}
 if(tick==80)scY[MENU_CASTLE]=500;
 if(tick==100)scY[MENU_CASTLE]=MergeRouletteCastleUpgradeHeight(CastleMenuGrowthBrowse())+72;
 if(tick==120){for(int i=0;i<18;++i)CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_PREV);scY[MENU_CASTLE]=0;for(int c=0;c<10;++c)for(int i=0;i<4;++i)robin.castleProgress.rooms[c][i]=5;CastleMenuModel::Turret(robin.castleProgress,0)=5;CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_SELECT);CastleReviewTrace(CastleMenuGrowthPending()?"PASS growth requires confirmation":"FAIL growth confirmation");}
 if(tick==140){const long long gold=robin.gold;CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_CONFIRM);CastleReviewTrace(robin.castle==1&&robin.gold==gold-CastleMenuModel::GoldPrice(1)?"PASS upgrade advances current castle once":"FAIL growth transaction");const long long after=robin.gold;CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_CONFIRM);CastleReviewTrace(robin.gold==after?"PASS repeated confirmation cannot charge twice":"FAIL duplicate charge");}
 if(tick==155)CastleReviewTrace("DONE castle growth review");
 const char* shot=tick==30?"castle-first.png":tick==70?"castle-last-top.png":tick==90?"castle-last-scroll.png":tick==110?"castle-interiors.png":tick==130?"castle-growth-confirm.png":nullptr;
 if(shot){pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS growth capture":"FAIL growth capture");},std::string(path)+shot);}
 return true;
}
