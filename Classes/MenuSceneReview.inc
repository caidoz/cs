static bool MenuSceneReview(const char* path){
 if(getenv("CS_HERO_BACKGROUND_REVIEW")){
  static int step=0;static bool waiting=false;if(waiting)return true;++step;
  cocos2d::Director::getInstance()->setDisplayStats(false);
  if(step==1){NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);}
  if(step==20){touchFunc(TOUCH_FUNC_COLLECTIONS);PlayKey(PLAYER);systemKey=0;curEquipTab=EQUIPTAB_GEAR;}
  if(step>=30&&step<180&&(step-30)%15==0){robin.castle=(step-30)/15;gMobileCastleVisual=robin.castle;}
  if(step>=40&&step<190&&(step-40)%15==0){
   char file[64];snprintf(file,sizeof(file),"hero-castle-%02d.png",(step-40)/15+1);waiting=true;
   cocos2d::utils::captureScreen([](bool ok,const std::string&){waiting=false;CastleReviewTrace(ok?"PASS hero background capture":"FAIL hero background capture");},std::string(path)+file);
  }
  if(step==195)CastleReviewTrace("DONE hero background review");
  return true;
 }
 if(!getenv("CS_MENU_SCENES_REVIEW"))return false;
 cocos2d::Director::getInstance()->setDisplayStats(false);
 static int tick=0;static bool pending=false;if(pending)return true;++tick;
 const auto open=[](int command){touchFunc(command);PlayKey(PLAYER);systemKey=0;};
 const auto close=[](){while(popUpCnt>0)ClosePopUp();};
 if(tick==1){NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);GotoLobby();close();LoadoutSetOpen(false);
  robin.castleProgress={};robin.castleProgress.version=2;robin.castleProgress.owned=1023;robin.gold=1000000;
  for(int i=0;i<18;++i){ITEM it={};it.type=ITEM_SWORD;it.detail=i%Max(1,itemStartCnt[ITEM_SWORD+1]-itemStartCnt[ITEM_SWORD]);it.lv=it.count=1;it.id=120000+i;robin.inven[i]=it;}
  for(int i=0;i<16;++i){ITEM it={};it.type=ITEM_CREW;it.detail=i;it.lv=it.count=1;it.id=130000+i;robin.inven[100+i]=it;}
 }
 if(tick==20){open(TOUCH_FUNC_COLLECTIONS);curEquipTab=EQUIPTAB_GEAR;}
 if(tick==45){robin.castle=9;gMobileCastleVisual=9;}
 if(tick==65){close();open(TOUCH_FUNC_POPUP_CREWLIST);}
 if(tick==90){scY[MENU_CREW]=100;}
 if(tick==110){close();open(TOUCH_FUNC_SHOP);}
 if(tick==140){scY[MENU_SHOP]=90;}
 if(tick==165){close();robin.castle=0;gMobileCastleVisual=0;open(TOUCH_FUNC_POPUP_CASTLEMENU);}
 if(tick==195){scY[MENU_CASTLE]=CastleUpgradeBlocks::PreviewHeight(DY)+72;}
 if(tick==225){scY[MENU_CASTLE]=scT[MENU_CASTLE];}
 if(tick==250){CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_NEXT);}
 if(tick==275){
  bool dock=false;for(int i=0;i<touchIndex;++i){const int cmd=touchRect[i][4];dock|=cmd==TOUCH_FUNC_LOBBY_ADVENTURE||cmd==TOUCH_FUNC_POPUP_CREWLIST||cmd==TOUCH_FUNC_SHOP;}
  CastleReviewTrace(!dock?"PASS full-screen castle has no dock touch targets":"FAIL castle dock");
  CastleReviewTrace("DONE menu scenes review");
 }
 const char* shot=tick==35?"equipment-castle-01.png":tick==55?"equipment-castle-10.png":tick==80?"crew.png":tick==100?"crew-scroll.png":
  tick==130?"shop.png":tick==155?"shop-scroll.png":tick==185?"castle.png":tick==210?"castle-rooms.png":tick==240?"castle-turret.png":tick==265?"castle-02.png":nullptr;
 if(shot){pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS menu scene capture":"FAIL scene capture");},std::string(path)+shot);}
 return true;
}
