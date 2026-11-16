// Actual bottom-navigation pages, with the legacy render path available for A/B.
static bool LobbyMenusPerfReview(const char* path){
 if(!getenv("CS_LOBBY_MENUS_PERF_REVIEW"))return false;
 static int tick=0;static bool pending=false;static double seconds=0,vertices=0,batches=0;
 if(pending)return true;++tick;
 const auto click=[](int command){CastleReviewClick(command);PlayKey(PLAYER);systemKey=0;};
 const auto has=[](int command){for(int n=0;n<touchIndex;++n)if(touchRect[n][4]==command)return true;return false;};
 if(tick==1){
  NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);
  GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);
  for(int i=0;i<Min(8,gTotalCrew);++i){ITEM item={};item.type=ITEM_CREW;item.detail=i;item.lv=1;item.count=1;item.id=710000+i;robin.inven[100+i]=item;}
 }
 if(tick<20)return true;
 const int sample=(tick-20)/155,step=(tick-20)%155;
 static const int commands[]={TOUCH_FUNC_SHOP,TOUCH_FUNC_COLLECTIONS,TOUCH_FUNC_POPUP_CREWLIST,TOUCH_FUNC_LOBBY_DUNGEON,TOUCH_FUNC_POPUP_CASTLEMENU,TOUCH_FUNC_COLLECTIONS};
 static const char* names[]={"shop","equipment","crew","dungeon","castle","stats"};
 if(sample>=6){if(sample==6&&step==0)CastleReviewTrace("DONE lobby menus performance review");return true;}
 if(step==0){while(popUpCnt>0)ClosePopUp();MenuRenewalCommand(TOUCH_FUNC_RENEW_DUNGEON_CLOSE);GotoLobby();seconds=vertices=batches=0;}
 if(step==5){if(sample==3)MenuRenewalCommand(commands[sample]);else click(commands[sample]);if(sample==1||sample==5)curEquipTab=sample==5?EQUIPTAB_STAT:EQUIPTAB_GEAR;}
 if(step>=30&&step<90){
  auto* director=cocos2d::Director::getInstance();seconds+=director->getDeltaTime();
  vertices+=director->getRenderer()->getDrawnVertices();batches+=director->getRenderer()->getDrawnBatches();
 }
 if(step==90){char text[200];snprintf(text,sizeof(text),"PROFILE %s frame_ms=%.3f vertices=%.0f batches=%.0f",names[sample],seconds*1000/60,vertices/60,batches/60);CastleReviewTrace(text);}
 if(step==96){
  pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS page capture":"FAIL page capture");},std::string(path)+names[sample]+".png");
 }
 if(step==105){touchFunc(TOUCH_FUNC_SETTING);PlayKey(PLAYER);systemKey=0;}
 if(step==116){
  CastleReviewTrace(has(TOUCH_FUNC_OPTION_BGM)?"PASS settings above page and touch controls":"FAIL settings input");
  click(TOUCH_FUNC_POPUP_CLOSE);
 }
 if(step==130){
  const bool correct=sample==3?MenuRenewalDungeonOpen()&&popUpCnt==0:popUpCnt==1;
  CastleReviewTrace(correct?"PASS settings return preserves parent page":"FAIL parent page return");
 }
 return true;
}
