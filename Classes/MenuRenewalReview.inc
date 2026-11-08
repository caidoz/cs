#include "CastleTutorialModel.h"
static bool MenuRenewalReviewStep(const char* path){
 if(!getenv("CS_MENU_RENEWAL_REVIEW"))return false;
 static int tick=0;static bool pending=false;static bool savedBgm=false;if(pending)return true;++tick;
 const auto click=[](int command){CastleReviewClick(command);PlayKey(PLAYER);systemKey=0;};
 const auto has=[](int command){for(int n=0;n<touchIndex;++n)if(touchRect[n][4]==command)return true;return false;};
 if(tick==1){
  NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);
  GotoLobby();while(popUpCnt>0)ClosePopUp();robin.gold=9995000;robin.coin=1000;
  for(int i=0;i<Min(8,gTotalCrew);++i){ITEM item={};item.type=ITEM_CREW;item.detail=i;item.grade=0;item.lv=1;item.count=1;item.id=700000+i;robin.inven[100+i]=item;}
 }
 if(tick==30)click(TOUCH_FUNC_LOBBY_DUNGEON);
 if(tick==40)CastleReviewTrace(MenuRenewalDungeonOpen()&&has(TOUCH_FUNC_RENEW_DUNGEON_CLOSE)?"PASS dungeon preview and return target":"FAIL dungeon preview");
 if(tick==41)click(TOUCH_FUNC_SETTING);
 if(tick==43)CastleReviewTrace(MenuRenewalDungeonOpen()&&has(TOUCH_FUNC_OPTION_BGM)?"PASS settings above dungeon without intercepted input":"FAIL dungeon modal layering");
 if(tick==44)click(TOUCH_FUNC_POPUP_CLOSE);
 if(tick==50)click(TOUCH_FUNC_RENEW_DUNGEON_CLOSE);
 if(tick==55)CastleReviewTrace(!MenuRenewalDungeonOpen()?"PASS dungeon closes":"FAIL dungeon closes");
 if(tick==60){click(TOUCH_FUNC_COLLECTIONS);curEquipTab=EQUIPTAB_GEAR;}
 if(tick==75)CastleReviewTrace(EquipmentMenuV2ReviewChecks()&&EquipmentMenuV2ReviewEquipping()?"PASS equipment actual equip power and scroll":"FAIL equipment regression");
 if(tick==80)touchFunc(TOUCH_FUNC_EQUIPTAB+EQUIPTAB_CREW);
 if(tick==92){bool crewTouch=false;for(int n=0;n<touchIndex;++n){int inv=touchRect[n][4]-TOUCH_FUNC_ITEMDETAIL;if(inv>=0&&inv<TOTALINVENTORY&&robin.inven[inv].type==ITEM_CREW)crewTouch=true;}CastleReviewTrace(curEquipTab==EQUIPTAB_CREW&&crewTouch?"PASS companion inventory touch":"FAIL companion inventory touch");}
 if(tick==100)touchFunc(TOUCH_FUNC_EQUIPTAB+EQUIPTAB_STAT);
 if(tick==112){const int y=DY-(GNBHEIGHT-GNB_INIT_HEIGHT)-LOBBY_BAR_H-370;const int before=scY[MENU_COLLECTIONS];EquipmentMenuV2Drag(100,y,100,y-100,100,y);CastleReviewTrace(scT[MENU_COLLECTIONS]>0&&scY[MENU_COLLECTIONS]>before?"PASS full stat and resistance list scroll":"FAIL stat list scroll");scY[MENU_COLLECTIONS]=0;scDir=SCROLL_NOTHING;}
 if(tick==120)touchFunc(TOUCH_FUNC_EQUIPTAB+EQUIPTAB_CODEX);
 if(tick==140)click(TOUCH_FUNC_POPUP_CLOSE);
 if(tick==150)click(TOUCH_FUNC_LOBBY_CASTLE);
 if(tick==162)CastleReviewTrace(has(TOUCH_FUNC_RENEW_CASTLE_PARTS)&&has(TOUCH_FUNC_RENEW_CASTLE_FACILITIES)?"PASS castle tabs reachable":"FAIL castle tabs");
 if(tick==180)click(TOUCH_FUNC_RENEW_CASTLE_FACILITIES);
 if(tick==195)scY[MENU_CASTLE]=scT[MENU_CASTLE];
 if(tick==205){
  bool extra=false;for(int n=1;n<5;++n)extra|=has(TOUCH_FUNC_CASTLE_FACILITY_UPGRADE+n);
  CastleReviewTrace(has(TOUCH_FUNC_CASTLE_FACILITY_UPGRADE)&&!extra?"PASS first castle one facility":"FAIL first castle facility count");
 }
 if(tick==220){for(int i=0;i<8;++i)CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_NEXT);}
 if(tick==235)scY[MENU_CASTLE]=scT[MENU_CASTLE];
 if(tick==245)CastleReviewTrace(has(TOUCH_FUNC_CASTLE_FACILITY_UPGRADE+4)?"PASS ninth castle fifth facility reachable":"FAIL ninth castle facility");
 if(tick==255){CastleMenuModuleReviewSet(8,0);CastleReviewTrace(CastleMenuFinalReviewChecks()?"PASS all castles upgrade spending MAX and persistence":"FAIL castle model regression");}
 if(tick==260)click(TOUCH_FUNC_POPUP_CLOSE);
 if(tick==270)click(TOUCH_FUNC_SHOP);
 if(tick==285)CastleReviewTrace(ShopSpecReviewChecks()?"PASS shop grants full storage insufficient duplicate guards":"FAIL shop regression");
 if(tick==290)click(TOUCH_FUNC_SHOP_MAIN_TAB+2);
 if(tick==300){bool dock=false,paid=false;for(int n=0;n<touchIndex;++n){const int c=touchRect[n][4];dock|=c==TOUCH_FUNC_LOBBY_ADVENTURE||c==TOUCH_FUNC_LOBBY_CASTLE;paid|=c>=TOUCH_FUNC_SHOP_IAP&&c<=TOUCH_FUNC_SHOP_IAP_END;}CastleReviewTrace(!dock&&!paid?"PASS shop covers dock and no disconnected cash purchase":"FAIL shop isolation");}
 if(tick==310)click(TOUCH_FUNC_POPUP_CLOSE);
 if(tick==320)click(TOUCH_FUNC_SETTING);
 if(tick==332){savedBgm=option.bgm!=0;click(TOUCH_FUNC_OPTION_BGM);}
 if(tick==334){CastleReviewTrace((option.bgm!=0)!=savedBgm?"PASS settings music command":"FAIL settings music command");click(TOUCH_FUNC_OPTION_BGM);}
 if(tick==340)click(TOUCH_FUNC_POPUP_CLOSE);
 if(tick==342)click(TOUCH_FUNC_LOBBY_CASTLE);
 if(tick>=345&&tick<=435&&(tick-345)%10==0){
  const int c=(tick-345)/10;CastleMenuModuleReviewSet(c,0);
  CastleMenuCommand(TOUCH_FUNC_CASTLE_BROWSE_PICK+c);
  CastleReviewTrace(gCastleTutorialStep==CastleTutorial::Done?"PASS menu review without tutorial overlay":"FAIL tutorial unexpectedly enabled");
 }
 if(tick==450)CastleReviewTrace("PASS menu renewal complete");
 const char* name=tick==20?"01-lobby.png":tick==45?"05-dungeon.png":tick==70?"02-equipment.png":tick==95?"06-companions.png":tick==110?"09-stats.png":tick==130?"10-codex.png":tick==165?"04-castle-parts.png":tick==210?"04-castle-facility.png":tick==250?"08-castle-advanced.png":tick==280?"03-shop.png":tick==305?"03-packages.png":tick==330?"11-settings.png":nullptr;
 char castleCapture[64];if(tick>=349&&tick<=439&&(tick-349)%10==0){sprintf(castleCapture,"castle-%02d-overview.png",(tick-349)/10+1);name=castleCapture;}
 if(name){pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS menu capture":"FAIL menu capture");},std::string(path)+name);}
 return true;
}
