static bool CastleFourFacilityReview(const char* path){
 if(getenv("CS_CASTLE_FREE_PREVIEW_REVIEW")){
  static int tick=0;++tick;
  if(tick==1){NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);
   robin.castleProgress={};robin.castleProgress.version=2;robin.castleProgress.owned=1023;robin.gold=0;DebugControlsToggle();
  }
  if(tick==20){touchFunc(TOUCH_FUNC_POPUP_CASTLEMENU);PlayKey(PLAYER);systemKey=0;}
  if(tick==35){
   const auto saved=robin.castleProgress;bool ok=DebugControlsOpen()&&LobbyCastleDebugActive();
   for(int c=0;c<10;++c){CastleMenuCommand(TOUCH_FUNC_CASTLE_BROWSE_PICK+c);
    for(int lv=1;lv<=6;++lv){for(int r=0;r<4;++r)CastleMenuCommand(TOUCH_FUNC_CASTLE_FACILITY_UPGRADE+r);CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_UPGRADE);
     for(int r=0;r<4;++r)ok=ok&&LobbyCastleDebugFacilityLevel(c,r)==lv%6;
     ok=ok&&CastleVisualPartLevel(c,3)==lv%6;
    }
   }
   ok=ok&&robin.gold==0&&memcmp(&saved,&robin.castleProgress,sizeof(saved))==0;
   CastleReviewTrace(ok?"PASS free preview ten castles five facilities six stages save unchanged":"FAIL free preview");
   DebugControlsToggle();CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_UPGRADE);CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_CONFIRM);
   CastleMenuCommand(TOUCH_FUNC_CASTLE_FACILITY_UPGRADE+1);CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_CONFIRM);
   CastleReviewTrace(!LobbyCastleDebugActive()&&robin.gold==0&&memcmp(&saved,&robin.castleProgress,sizeof(saved))==0?"PASS normal upgrades still require gold and debug closes":"FAIL normal upgrade guards");
   DebugControlsToggle();CastleMenuOpen();CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_UPGRADE);
  }
  if(tick==50)cocos2d::utils::captureScreen([](bool ok,const std::string&){CastleReviewTrace(ok?"PASS debug preview capture":"FAIL debug capture");},std::string(path)+"debug-free-preview.png");
  if(tick==60){while(popUpCnt>0)ClosePopUp();CastleReviewTrace(MergeRouletteDebugTouchReview()?"PASS direct room turret castle and background touches without payment":"FAIL direct debug touches");}
  if(tick==75)cocos2d::utils::captureScreen([](bool ok,const std::string&){CastleReviewTrace(ok?"PASS direct debug capture":"FAIL direct capture");CastleReviewTrace("DONE debug preview review");},std::string(path)+"debug-direct-preview.png");
  return true;
 }
 if(!getenv("CS_FOUR_FACILITY_MENU_REVIEW"))return false;
 static int tick=0;static bool pending=false;static long long funds=0;static double seconds=0;
 if(pending)return true;++tick;
 const auto click=[](int command){CastleReviewClick(command);PlayKey(PLAYER);systemKey=0;};
 if(tick==1){NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);
  robin.castleProgress={};robin.castleProgress.version=2;robin.castleProgress.owned=1023;robin.gold=1000000;
 }
 if(tick==20){touchFunc(TOUCH_FUNC_POPUP_CASTLEMENU);PlayKey(PLAYER);systemKey=0;}
 if(tick==35)CastleReviewTrace(CastleMenuFinalReviewChecks()?"PASS facility costs confirm cancel stale and duplicate guards":"FAIL facility model guards");
 if(tick==60)scY[MENU_CASTLE]=Min(scT[MENU_CASTLE],560);
 if(tick==80){funds=robin.gold;click(TOUCH_FUNC_CASTLE_FACILITY_UPGRADE+1);}
 if(tick==94){click(TOUCH_FUNC_CASTLE_NEW_CONFIRM);CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_CONFIRM);
  bool shared=robin.gold==funds-240;for(int c=0;c<10;++c)shared=shared&&robin.castleProgress.rooms[c][1]==1;
  CastleReviewTrace(shared?"PASS shared weapon upgrade charges once across ten castles":"FAIL shared upgrade transaction");
 }
 if(tick==105){CastleMenuCommand(TOUCH_FUNC_CASTLE_BROWSE_PICK+9);scY[MENU_CASTLE]=0;
  CastleReviewTrace(robin.castleProgress.rooms[9][1]==1?"PASS castle switch keeps facility level":"FAIL switched facility level");
 }
 if(tick==120){for(int c=0;c<10;++c)for(int r=0;r<4;++r)robin.castleProgress.rooms[c][r]=5;robin.castleProgress.parts[9][3]=5;}
 if(tick==140)scY[MENU_CASTLE]=scT[MENU_CASTLE];
 if(tick>=170&&tick<230)seconds+=cocos2d::Director::getInstance()->getDeltaTime();
 if(tick==235){char line[100];snprintf(line,sizeof(line),"PROFILE four-facility-menu frame_ms=%.3f",seconds*1000/60);CastleReviewTrace(line);}
 const char* shot=tick==50?"castle-01-menu.png":tick==70?"facilities.png":tick==88?"upgrade-confirm.png":tick==130?"castle-10-max-menu.png":tick==155?"castle-10-rooms.png":nullptr;
 if(shot){pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS four-facility menu capture":"FAIL menu capture");},std::string(path)+shot);}
 if(tick==240)CastleReviewTrace("DONE four-facility menu review");
 return true;
}
