#include "AccountLevelModel.h"
static bool AccountLevelReview(const char* path){
 if(!getenv("CS_ACCOUNT_LEVEL_REVIEW"))return false;
 static int tick=0;static bool pending=false;if(pending)return true;++tick;
 auto check=[](bool ok,const char* name){CastleReviewTrace((std::string(ok?"PASS ":"FAIL ")+name).c_str());};
 if(tick==1){NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);robin.castle=0;robin.lv=0;robin.exps=0;robin.heart=10;}
 if(tick==20){CastleReviewClick(TOUCH_FUNC_POPUP_LVUPREWARD);PlayKey(PLAYER);systemKey=0;}
 if(tick==35){
  bool close=false,legacy=false;for(int i=0;i<touchIndex;++i){close|=touchRect[i][4]==TOUCH_FUNC_POPUP_CLOSE;legacy|=touchRect[i][4]>=TOUCH_FUNC_COLLECTIONS_DETAIL&&touchRect[i][4]<TOUCH_FUNC_COLLECTIONS_DETAIL+TOTAL_LVUPREWARD;}
  check(popUpCnt==1&&popUp[0].type==POPUPTYPE_LEVELUP&&LobbySectionOwnsPopups()&&!MergeRouletteLobbyDockVisible()&&close&&!legacy,"account page owns viewport and removes legacy benefit-card hit areas");
 }
 if(tick==50){AccountLevelGain(100,false);check(robin.lv==1&&robin.exps==100&&robin.heart==15&&GetInitHeart()==36,"first clear threshold grants one capacity and five energy");}
 if(tick==70){AccountLevelGain(225,false);check(robin.lv==2&&robin.exps==325&&robin.heart==20,"EXP carries over without losing remainder");AccountLevelGain(0,false);check(robin.lv==2&&robin.heart==20,"zero EXP cannot repeat level-up rewards");}
 if(tick==75){
  robin.lv=0;RefreshStat(&ao[curHero]);const long long hp=ao[curHero].ps[PS_HP];
  robin.lv=98;robin.exps=AccountLevel::floor(98);AccountLevelGain(2147483647,false);const long long e=robin.exps,h=robin.heart;AccountLevelGain(100,false);
  check(robin.lv==99&&e==AccountLevel::floor(99)&&robin.exps==e&&robin.heart==h,"Lv100 terminates safely and cannot repeat rewards");
  RefreshStat(&ao[curHero]);check(ao[curHero].ps[PS_HP]==hp&&!IsGetHero(ROBIN+1)&&!IsGetHero(ROBIN+2),"account level does not grant combat HP or unreleased heroes");
 }
 if(tick==100){
  robin.lv=25;robin.exps=0;AccountLevelGain(1,false);check(robin.lv==25&&robin.exps==AccountLevel::floor(25)+1,"legacy level is retained when EXP curve changes");
  robin.exps=999999999;AccountLevelGain(1,false);check(robin.lv==25&&robin.exps==AccountLevel::floor(25)+1,"legacy high EXP cannot jump straight to the new level cap");
 }
 if(tick==110){while(popUpCnt>0)ClosePopUp();robin.lv=0;robin.exps=0;robin.heart=10;check(MergeRouletteFinalRewardReview(0)&&robin.lv==1&&robin.exps==100&&robin.heart==15,"only the final boss pays account EXP and energy once");}
 if(tick==125)check(MergeRouletteFinalRewardReview(1),"boss reward opens without replaying account EXP");
 if(tick==150)check(MergeRouletteFinalRewardReview(2)&&robin.exps==100&&robin.heart==15,"closing rewards returns to lobby without duplicate account grants");
 if(tick==170){CastleReviewClick(TOUCH_FUNC_POPUP_LVUPREWARD);PlayKey(PLAYER);systemKey=0;}
 const char* shot=tick==40?"account-lv1.png":tick==60?"account-lv2.png":tick==90?"account-lv100.png":tick==130?"account-boss-reward.png":tick==185?"account-after-clear.png":nullptr;
 if(shot){pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS account capture":"FAIL account capture");},std::string(path)+shot);}
 if(tick==190)CastleReviewTrace("DONE account level review");
 return true;
}
