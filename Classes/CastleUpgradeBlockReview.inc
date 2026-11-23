// Isolated native hit-testing and transactions for each visible upgrade block.
#include "Data/CastleUpgradeBlocks.h"
bool CastleMenuBlockPending(int room);
static bool CastleUpgradeBlockReview(const char* path){
 if(!getenv("CS_CASTLE_BLOCKS_REVIEW"))return false;
 static int tick=0;static bool pending=false;static long long before=0;
 if(pending)return true;++tick;
 if(tick==1){
  NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);
  GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);
  if(DebugControlsOpen())DebugControlsToggle();
  robin.castleProgress={};robin.castleProgress.version=2;robin.castleProgress.owned=1023;robin.gold=1000000;
 }
 if(tick==20){touchFunc(TOUCH_FUNC_POPUP_CASTLEMENU);PlayKey(PLAYER);systemKey=0;}
 if(tick==25){
  cocos2d::Director::getInstance()->setDisplayStats(false);
  pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS block menu capture":"FAIL menu capture");},std::string(path)+"menu.png");
 }
 if(tick>=30&&tick<130){
  const int index=(tick-30)/20,phase=(tick-30)%20,room=CastleUpgradeBlocks::Items[index].room;
  const int command=room<0?TOUCH_FUNC_CASTLE_NEW_UPGRADE:TOUCH_FUNC_CASTLE_FACILITY_UPGRADE+room;
  if(phase==0){scY[MENU_CASTLE]=Min(scT[MENU_CASTLE],CastleUpgradeBlocks::PreviewHeight(DY)+72+index*(CastleUpgradeBlocks::CardHeight(DY)+CastleUpgradeBlocks::Gap));before=robin.gold;}
  if(phase==3){
   bool largeButton=false;
   for(int i=0;i<touchIndex;++i)if(touchRect[i][4]==command&&touchRect[i][3]==48&&touchRect[i][2]>=100)largeButton=true;
   CastleReviewTrace(largeButton?"PASS upgrade button at least 48 high":"FAIL small upgrade button");
   bool hit=false;
   for(int i=0;i<touchIndex;++i)if(touchRect[i][4]==command&&touchRect[i][2]>200&&touchRect[i][3]>70){
    // Tap the title area, away from the footer button.
    ExecTouchFunc(touchRect[i][0]+20,touchRect[i][1]-14);PlayKey(PLAYER);systemKey=0;hit=true;break;
   }
   CastleReviewTrace(hit&&CastleMenuBlockPending(room)&&robin.gold==before?
    "PASS full block touch opens correct facility without charge":"FAIL block touch or binding");
  }
  if(phase==5){
   pending=true;char file[64];snprintf(file,sizeof(file),"block-%d-confirm.png",index);
   cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS block confirmation capture":"FAIL capture");},std::string(path)+file);
  }
  if(phase==7){
   CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_CANCEL);
   CastleReviewTrace(!CastleMenuBlockPending(room)&&robin.gold==before?"PASS block cancel keeps currency":"FAIL block cancel");
  }
  if(phase==9){
   CastleMenuCommand(command);
   // Production upgrades first settle the old-rate vault into wallet gold.
   const long long expected=robin.gold-CastleMenuModel::UpgradeCost(0,0,room>=0)+(room==CastleFacilities::FoodRoom?CastleIncomeNow():0);
   CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_CONFIRM);
   const long long charged=robin.gold;CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_CONFIRM);
   const int level=room<0?robin.castleProgress.parts[0][3]:robin.castleProgress.rooms[0][room];
   bool ok=level==1&&charged==expected&&robin.gold==charged;
   if(room>=0)for(int c=0;c<10;++c)ok=ok&&robin.castleProgress.rooms[c][room]==1;
   else for(int c=1;c<10;++c)ok=ok&&robin.castleProgress.parts[c][3]==0;
   if(!ok){char message[192];snprintf(message,sizeof(message),"block room=%d before=%lld charged=%lld final=%lld level=%d net=%d/%d",room,before,charged,robin.gold,level,NetLastRequest(),NetLastResult());CastleReviewTrace(message);}
   CastleReviewTrace(ok?"PASS block confirmation charges once and preserves upgrade scope":"FAIL block transaction");
  }
 }
 if(tick==135){
  const auto& p=robin.castleProgress;
  CastleReviewTrace(CastleMenuModel::Health(p,0)==6&&CastleMenuModel::Defense(p,0)==4&&CastleMenuModel::Attack(p,0)==4&&
   CastleFacilities::Bonus(p,0,false)==25&&CastleMenuModel::CannonTurnPercent(p.parts[0][3])==280?
   "PASS five real effects health defense attack cannon production":"FAIL effect mapping");
  CastleReviewTrace("DONE castle block review");
 }
 return true;
}
