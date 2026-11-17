bool reviewOriginalTopbar(){
 if(!review||!std::getenv("CS_ORIGINAL_TOPBAR_REVIEW"))return false;
 static int sample=0,hold=0;static bool captured=false,done=false;
 if(done||reviewCapturePending)return true;
 const long long values[3]={140,1000000,GOLD_MAX};
 robin.gold=values[sample];robin.coin=2500;robin.heart=48;
 const int handle=drawHandle;drawHandle=MD_LOBBY;
 MergeRouletteLobbySceneDraw();drawHandle=handle;
 cocos2d::Director::getInstance()->setDisplayStats(false);
 if(++hold<20)return true;
 if(!captured){
  int level=0,gold=0,cash=0,settings=0;bool collect=false;
  for(int i=0;i<touchIndex;++i)if(touchRect[i][1]>=DY-LOBBY_BAR_H){const int c=touchRect[i][4];
   level+=c==TOUCH_FUNC_POPUP_LVUPREWARD;gold+=c==TOUCH_FUNC_GOTO_GOLD_IAP;
   cash+=c==TOUCH_FUNC_GOTO_RAINBOW_IAP;settings+=c==TOUCH_FUNC_SETTING;collect|=c==TOUCH_FUNC_CASTLE_INCOME;
  }
  reviewTrace(level==1&&gold==1&&cash==1&&settings==1&&!collect?
   "PASS original level gold diamond energy strip with native settings and no collect button":"FAIL original topbar touch targets");
  char name[64];snprintf(name,sizeof(name),"original-topbar-%d",sample);reviewCapture(name);captured=true;return true;
 }
 if(++sample==3){done=true;reviewTrace("DONE original topbar review");}
 hold=0;captured=false;return true;
}
