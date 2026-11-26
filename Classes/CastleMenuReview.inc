// Explicit isolated UI review; enabled only with CS_CASTLE_REVIEW_PATH.
#include "Data/InventoryCannonSprites.h"
#include "GoldAmountFormat.h"
#include "Config/ShopConfig.h"
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
#include "MenuRenewalReview.inc"
#include "LobbyMenusPerfReview.inc"
#include "CastleFourFacilityReview.inc"
#include "CastleUpgradeBlockReview.inc"
#include "MenuSceneReview.inc"
#include "QuietMenuReview.inc"
#include "CastleGrowthReview.inc"
#include <chrono>
#include "CurrentVersionTour.inc"
static void CastleMenuReviewStep()
{
    const char* path = getenv("CS_CASTLE_REVIEW_PATH");
    if (!path) return;
    if(CurrentVersionTour(path))return;
    if(getenv("CS_FINAL_BOSS_REWARD_REVIEW")){
        static int tick=0;static bool pending=false;if(pending)return;++tick;
        if(tick==1){NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);}
        const int step=tick==20?0:tick==70?1:tick==90?2:tick==110?3:-1;
        if(step>=0)CastleReviewTrace(MergeRouletteFinalRewardReview(step)?"PASS final boss reward flow":"FAIL final boss reward flow");
        const char* shot=tick==80?"stage-clear-reward.png":tick==120?"castle-income-lobby.png":nullptr;
        if(shot){pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS final reward capture":"FAIL final reward capture");},std::string(path)+shot);}
        if(tick==140)CastleReviewTrace("DONE final boss reward review");
        return;
    }
    if(CastleGrowthReview(path))return;
    if(QuietMenuReview(path))return;
    if(getenv("CS_CASTLE_DEBUG_SELECTION_REVIEW")){
        static int tick=0;static bool pending=false;if(pending)return;++tick;
        static CastleMenuModel::Progress saved;
        if(tick==1){NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);robin.castleProgress.version=2;robin.castleProgress.owned=3;robin.castle=gMobileCastleVisual=1;saved=robin.castleProgress;}
        if(tick==15){DebugControlsToggle();LobbyCastleDebugCommand(TOUCH_FUNC_LOBBY_CASTLE_PREV);LobbyCastleDebugCycle(0,-1);char diag[180];snprintf(diag,sizeof(diag),"DETAIL chosen=%d visual=%d saved=%d owned=%u inventory=%d capacity=%d loadoutcap=%d",LobbyCastleDebugCastle(),gMobileCastleVisual,robin.castle,robin.castleProgress.owned,InventoryUsed(),CastleInventoryCapacity(0),CastleEquipmentCapacity(0));CastleReviewTrace(diag);}
        if(tick==20){DebugControlsToggle();char diag[220];snprintf(diag,sizeof(diag),"DETAIL debug=%d preview=%d departure=%d visual=%d same=%d used=%d cells=%d slots=%d",DebugControlsOpen(),LobbyCastleDebugActive(),robin.castle,gMobileCastleVisual,!memcmp(&saved,&robin.castleProgress,sizeof(saved)),LoadoutUsed(),LoadoutCellUsed(),CastleEquippedCells());CastleReviewTrace(diag);CastleReviewTrace(!DebugControlsOpen()&&!LobbyCastleDebugActive()&&robin.castle==0&&gMobileCastleVisual==0&&!memcmp(&saved,&robin.castleProgress,sizeof(saved))?"PASS closing debug keeps first departure castle without saving preview upgrades":"FAIL debug selection reverted or saved upgrades");}
        if(tick==30){pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS first castle after debug close capture":"FAIL capture");},std::string(path)+"first-castle.png");}
        if(tick==40){DebugControlsToggle();CastleReviewTrace(LobbyCastleDebugCastle()==0?"PASS reopening debug starts at retained first castle":"FAIL reopen selection");LobbyCastleDebugCommand(TOUCH_FUNC_LOBBY_CASTLE_NEXT);DebugControlsToggle();CastleReviewTrace(robin.castle==1&&gMobileCastleVisual==1?"PASS closing debug also retains another owned castle":"FAIL second castle selection");}
        if(tick==50){DebugControlsToggle();gMobileCastleVisual=9;DebugControlsToggle();CastleReviewTrace(robin.castle==1&&!CastleMenuModel::Owned(robin.castleProgress,9)&&!memcmp(&saved,&robin.castleProgress,sizeof(saved))?"PASS debug selection cannot grant unowned castles or upgrades":"FAIL debug grants ownership");}
        if(tick==60){DebugControlsToggle();gMobileCastleVisual=0;DebugControlsToggle();CastleReviewTrace(robin.castle==0&&gMobileCastleVisual==0?"PASS first castle remains selectable after repeated debug close":"FAIL repeated close");CastleReviewTrace("DONE debug selection review");}
        return;
    }
    if(getenv("CS_CENTERED_LOBBY_NAV_REVIEW")){
        static int tick=0;static bool pending=false;if(pending)return;++tick;
        if(tick==1){NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);}
        const int actions[5]={TOUCH_FUNC_SHOP,TOUCH_FUNC_COLLECTIONS,TOUCH_FUNC_POPUP_CREWLIST,TOUCH_FUNC_POPUP_CASTLEMENU,TOUCH_FUNC_LOBBY_ADVENTURE};
        for(int page=0;page<5;++page){
            if(tick==20+page*30){while(popUpCnt>0)ClosePopUp();}
            if(tick==30+page*30){CastleReviewClick(actions[page]);PlayKey(PLAYER);systemKey=0;}
            if(page==0&&tick==36)touchFunc(TOUCH_FUNC_SHOP_MAIN_TAB+2);
            if(tick==45+page*30){
                const int commands[5]={TOUCH_FUNC_SHOP,TOUCH_FUNC_COLLECTIONS,TOUCH_FUNC_LOBBY_ADVENTURE,TOUCH_FUNC_POPUP_CREWLIST,TOUCH_FUNC_POPUP_CASTLEMENU};
                bool valid=page==4?MergeRouletteBottomNavHeight()>0:MergeRouletteBottomNavHeight()==0;
                for(int tab=0;tab<5;++tab){int count=0;for(int i=0;i<touchIndex;++i)count+=touchRect[i][4]==commands[tab];valid=valid&&count==(page==4?1:0);}
                valid=valid&&(MergeRouletteLobbyDockVisible()==(page==4));
                const int types[4]={POPUPTYPE_SHOPINFO,POPUPTYPE_COLLECTIONS,POPUPTYPE_CREWLIST,POPUPTYPE_CASTLEMENU};
                valid=valid&&(page==4?popUpCnt==0:popUpCnt==1&&popUp[0].type==types[page]);
                CastleReviewTrace(valid?"PASS section owns full height with no dock targets; lobby restores five actions":"FAIL section dock ownership");
                char name[40];snprintf(name,sizeof(name),"dock-page-%d.png",page);pending=true;
                cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS dock capture":"FAIL dock capture");},std::string(path)+name);
            }
        }
        if(tick==180){CastleReviewClick(TOUCH_FUNC_SHOP);PlayKey(PLAYER);systemKey=0;}
        if(tick==190){CastleReviewClick(TOUCH_FUNC_SETTING);PlayKey(PLAYER);systemKey=0;}
        if(tick==205){
            bool modal=popUpCnt>=2&&!MergeRouletteLobbyDockVisible()&&MergeRouletteBottomNavHeight()==0;
            for(int i=0;i<touchIndex;++i){for(int a:actions)if(touchRect[i][4]==a)modal=false;if(touchRect[i][4]==TOUCH_FUNC_SETTING)modal=false;}
            CastleReviewTrace(modal?"PASS nested modal owns input above section and resource bar":"FAIL nested modal priority");
            pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS modal capture":"FAIL modal capture");},std::string(path)+"nested-modal.png");
        }
        if(tick==215){while(popUpCnt>0)ClosePopUp();}
        if(tick==230){
            int dock=0;for(int i=0;i<touchIndex;++i)for(int a:actions)dock+=touchRect[i][4]==a;
            CastleReviewTrace(MergeRouletteLobbyDockVisible()&&dock==5?"PASS closing all pages restores exactly five live lobby actions":"FAIL dock restore after modal");
            CastleReviewTrace("DONE centered lobby navigation review");
        }
        return;
    }
    if(getenv("CS_UI_TYPE_REVIEW")){
        static int tick=0;static bool pending=false;if(pending)return;++tick;
        const auto click=[](int command){CastleReviewClick(command);PlayKey(PLAYER);systemKey=0;};
        if(tick==1){NewGame();GotoLobby();while(popUpCnt>0)ClosePopUp();}
        if(tick==12)click(TOUCH_FUNC_SETTING);
        if(tick==30)click(TOUCH_FUNC_OPTION_LANGUAGE);
        if(tick==52){
            bool all=true;for(int i=0;i<TOTALLANGUAGE;++i){bool found=false;for(int n=0;n<touchIndex;++n)found|=touchRect[n][4]==TOUCH_FUNC_OPTION_LANGUAGE_SELECT+i;all&=found;}
            CastleReviewTrace(all?"PASS all language buttons retain touch targets":"FAIL language touch targets");
            click(TOUCH_FUNC_OPTION_LANGUAGE_SELECT+1);
        }
        if(tick==62){CastleReviewTrace(option.language==1?"PASS language selection uses shared buttons":"FAIL language selection");CastleReviewTrace("DONE UI type review");}
        const char* shot=tick==24?"settings.png":tick==46?"languages.png":nullptr;
        if(shot){pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS UI type capture":"FAIL UI type capture");},std::string(path)+shot);}
        return;
    }
    if(MenuSceneReview(path))return;
    if(getenv("CS_EQUIP_STATS_REVIEW")){
        static int tick=0;static bool pending=false;if(pending)return;++tick;
        if(tick==1){
            NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);
            for(int i=0;i<TOTALINVENTORY;++i){memset(&robin.inven[i],0,sizeof(ITEM));robin.inven[i].type=EMPTY;}
            ITEM item;MakeItem(&item,ITEM_SWORD,1,GRADE_NORMAL,1,0);item.cooldown=0;item.value=100;item.id=880002;item.count=1;
            const int options[]={PREFIX_CRITICAL,PREFIX_PIERCE,PREFIX_EXTRA,PREFIX_GOLD,PREFIX_EXP,SUFFIX_CRITICAL,SUFFIX_EVASION,SUFFIX_HP,SUFFIX_MP,SUFFIX_HPDRAIN,SUFFIX_MPDRAIN,SUFFIX_ARMOR};
            for(int n=0;n<12;++n){item.option[n][0]=options[n];item.option[n][1]=5;}
            robin.inven[20]=item;item.id=880001;item.value=10;robin.inven[0]=item;
            robin.charData[ROBIN].equip[EQUIP_WEAPON]=item;SetPlayerHero(ROBIN);
        }
        if(tick==20){touchFunc(TOUCH_FUNC_COLLECTIONS);PlayKey(PLAYER);systemKey=0;curEquipTab=EQUIPTAB_GEAR;menuDepth=1;menuItem=20;}
        const int step=tick==45?0:tick==65?1:tick==95?2:tick==135?3:-1;
        if(step>=0)CastleReviewTrace(EquipmentDetailStatsReview(step)?"PASS equipment stats instance and input":"FAIL equipment stats detail");
        const char* shot=tick==55?"stats.png":tick==80?"stats-scroll.png":tick==115?"equipped.png":tick==150?"duplicate-not-equipped.png":nullptr;
        if(shot){pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS equipment stats capture":"FAIL equipment stats capture");},std::string(path)+shot);}
        if(tick==160)CastleReviewTrace("DONE equipment stats review");
        return;
    }
    if(getenv("CS_ENTRY_CHOICE_REVIEW")){
        static int tick=0;static bool pending=false;if(pending)return;++tick;
        if(tick==1){NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);}
        const int step=tick==30?0:tick==50?6:tick==60?1:tick==80?2:tick==150?3:tick==190?4:tick==300?5:-1;
        if(step>=0)CastleReviewTrace(MergeRouletteEntryChoiceReview(step)?"PASS entry choice input and accounting":"FAIL entry choice flow");
        const char* shot=tick==25?"lobby.png":tick==45?"choice.png":tick==55?"progress.png":tick==130?"expedition-rewards.png":tick==170?"insufficient-energy.png":nullptr;
        if(shot){pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS entry capture":"FAIL entry capture");},std::string(path)+shot);}
        if(tick==305)CastleReviewTrace("DONE entry choice review");
        return;
    }
    if(getenv("CS_VAULT_COLLECT_REVIEW")){
        static int tick=0;static bool pending=false;if(pending)return;++tick;
        if(tick==1){NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);}
        const int step=tick==30?0:tick==50?1:tick==170?2:tick==185?3:tick==200?4:tick==320?5:-1;
        if(step>=0)CastleReviewTrace(MergeRouletteVaultReview(step)?"PASS vault collect accounting and flight":"FAIL vault collect");
        const char* shot=tick==40?"vault-ready.png":tick==64?"vault-flight.png":tick==118?"vault-cards.png":tick==175?"vault-done.png":tick==214?"vault-gold-only.png":nullptr;
        if(shot){pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS vault capture":"FAIL vault capture");},std::string(path)+shot);}
        if(tick==325)CastleReviewTrace("DONE vault collect review");
        return;
    }
    if(CastleUpgradeBlockReview(path))return;
    if(CastleFourFacilityReview(path))return;
    if(getenv("CS_BOX_INFO_REVIEW")){
        static int tick=0;static bool pending=false;static long long beforeGold=0,beforeGems=0;if(pending)return;++tick;
        if(tick==1){NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);robin.gold=110;robin.coin=0;}
        if(tick==20){touchFunc(TOUCH_FUNC_SHOP);PlayKey(PLAYER);systemKey=0;}
        if(tick==22){
            auto savedRects=std::move(touchRect);const int savedIndex=touchIndex;
            const int cx=clipX,cy=clipY,cx2=clipX2,cy2=clipY2;
            const bool savedLock=gTouchRectLocked;
            SetSectionClip(0,DY,DX,DY,true);ResetRectPoint();
            for(int i=0;i<512;++i)SetRectPoint(10,DY-10,20,20,TOTALTOUCHCNT-1-i);
            bool touchOk=touchIndex==512&&GetTouchFunc(15,DY-15)==TOTALTOUCHCNT-512;
            ResetRectPoint();touchOk=touchOk&&GetTouchFunc(15,DY-15)==0;
            SetRectPoint(10,DY-10,20,20,TOUCH_FUNC_SHOP);
            touchOk=touchOk&&touchIndex==1&&GetTouchFunc(15,DY-15)==TOUCH_FUNC_SHOP;
            char storage[160];snprintf(storage,sizeof(storage),"touch storage old_bytes=%llu live_capacity_bytes=%llu",(unsigned long long)TOTALTOUCHCNT*5*sizeof(int),(unsigned long long)touchRect.capacity()*sizeof(touchRect[0]));CastleReviewTrace(storage);
            CastleReviewTrace(touchOk?"PASS sparse commands use live rectangles and reset ignores stale hits":"FAIL touch rectangle storage");
            touchRect=std::move(savedRects);touchIndex=savedIndex;gTouchRectLocked=savedLock;
            clipX=cx;clipY=cy;clipX2=cx2;clipY2=cy2;
            CastleReviewTrace(NetInventoryProtocolSelfTest()?"PASS 750 separate equipment grow sort save and reload beyond legacy storage":"FAIL growing inventory");
            CastleReviewTrace(EquipmentMenuV2ReviewEquipping()?"PASS extended inventory equipment selection for all heroes":"FAIL extended equipment selection");
            CastleReviewTrace(ShopBoxLootReview()?"PASS six loot tiers exact odds weighted variants no energy monotonic gold":"FAIL loot distribution");
        }
        if(tick==80)scY[MENU_SHOP]=scT[MENU_SHOP];
        if(tick==120)scY[MENU_SHOP]=0;
        if(tick==135){robin.gold=99;beforeGold=robin.gold;beforeGems=robin.coin;CastleReviewClick(TOUCH_FUNC_SHOP_BUYBOX1);PlayKey(PLAYER);systemKey=0;}
        if(tick==155)CastleReviewTrace(robin.gold==beforeGold&&robin.coin==beforeGems&&popUpCnt>0?"PASS product opens details without charging":"FAIL detail charged currency");
        const char* shot=tick==60?"boxes-top.png":tick==100?"boxes-bottom.png":tick==160?"box-detail.png":nullptr;
        if(shot){pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS box capture":"FAIL box capture");},std::string(path)+shot);}
        if(tick==170&&!getenv("CS_SHOP_PURCHASE_FLOW_REVIEW"))CastleReviewTrace("DONE box info review");
        if(getenv("CS_SHOP_PURCHASE_FLOW_REVIEW")){
            static int shopScrollBeforeRates=0,shopLimitBeforeRates=0;static bool done=false;if(done)return;
            static bool fell=false,openedChest=false,openedShot=false,summaryShot=false;
            static float previousChestY=0;static std::vector<ITEM> paidInventory;
            if(tick>245&&drawHandle==MD_GACHA){
                if(previousChestY>0&&boxMark[0].motionFrame<0&&boxMark[0].y<previousChestY)fell=true;
                previousChestY=boxMark[0].y;
                if(boxMark[0].motion==BOXSTATUS_OPENED)openedChest=true;
                const char* originalShot=openedChest&&!openedShot?"original-chest-open.png":gachaDepth==GACHA_DEPTH_SUMMARY&&!summaryShot?"original-summary.png":nullptr;
                if(originalShot){
                    if(gachaDepth==GACHA_DEPTH_SUMMARY)summaryShot=true;else openedShot=true;
                    pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS original chest capture":"FAIL original chest capture");},std::string(path)+originalShot);return;
                }
            }

            if(tick==164){shopScrollBeforeRates=scY[MENU_SHOP];shopLimitBeforeRates=scT[MENU_SHOP];}
            if(tick==165){CastleReviewClick(TOUCH_FUNC_SHOP_GACHA_RATES);PlayKey(PLAYER);systemKey=0;}
            if(tick==185){
                Core* layer=nullptr;for(auto node:curScene->getChildren())if((layer=dynamic_cast<Core*>(node)))break;
                const int before=scY[MENU_SHOP];
                if(layer){cocos2d::Touch touch;touch.setTouchInfo(992,DX*.5f,DY*.65f);layer->onTouchBegan(&touch,nullptr);
                    for(int i=1;i<=8;++i){touch.setTouchInfo(992,DX*.5f,DY*(.65f-.3f*i/8));layer->onTouchMoved(&touch,nullptr);}
                    layer->onTouchEnded(&touch,nullptr);
                }
                scAccelY=0;
                CastleReviewTrace(scY[MENU_SHOP]>before?"PASS real touch drag scrolls probability popup":"FAIL probability touch drag");
            }
            if(tick==195){scY[MENU_SHOP]=scT[MENU_SHOP];scAccelY=0;}
            if(tick==205)CastleReviewTrace(GachaRatesScrollAtBottomReview()?"PASS probability last card visible and bottom survives parent render":"FAIL probability bottom clipped");
            if(tick==180||tick==205||tick==270){
                const char* name=tick==180?"rates.png":tick==205?"rates-scroll.png":"purchase-reveal.png";
                pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS box capture":"FAIL box capture");},std::string(path)+name);
            }
            if(tick==215){CastleReviewClick(TOUCH_FUNC_SHOP_IAP_CANCEL);PlayKey(PLAYER);systemKey=0;}
            if(tick==216)CastleReviewTrace(scY[MENU_SHOP]==shopScrollBeforeRates&&scT[MENU_SHOP]==shopLimitBeforeRates?"PASS probability close restores shop scroll":"FAIL shop scroll restoration");
            if(tick==220){
                CastleReviewClick(TOUCH_FUNC_SHOP_IAP_CANCEL);PlayKey(PLAYER);systemKey=0;
                // This isolated review starts with a full character fixture.
                // Reserve room for a valid purchase after the read-only case.
                for(int i=0;i<GetMaxInven();++i){memset(&robin.inven[i],0,sizeof(ITEM));robin.inven[i].type=EMPTY;}
            }
            if(tick==230){robin.gold=1000;CastleReviewClick(TOUCH_FUNC_SHOP_BUYBOX1);PlayKey(PLAYER);systemKey=0;}
            if(tick==245){beforeGold=robin.gold;beforeGems=robin.coin;CastleReviewClick(TOUCH_FUNC_SHOP_IAP_CONFIRM);PlayKey(PLAYER);systemKey=0;}
            if(tick==340){
                bool result=drawHandle==MD_GACHA&&gachaGrantedPresentation;
                char diagnostic[160];snprintf(diagnostic,sizeof(diagnostic),"purchase result=%d gold=%lld before=%lld popups=%d",result,(long long)robin.gold,beforeGold,popUpCnt);CastleReviewTrace(diagnostic);
                pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS box capture":"FAIL box capture");},std::string(path)+"purchase-result.png");
            }
            if(tick==350){
                bool result=drawHandle==MD_GACHA&&gachaGrantedPresentation;
                CastleReviewTrace(result&&robin.gold<=beforeGold-GetBoxPrice(BOX_PAID0,GRADE_NORMAL)+ShopTreasure::LootFor(0).goldMax&&robin.gold>=beforeGold-GetBoxPrice(BOX_PAID0,GRADE_NORMAL)&&robin.coin==beforeGems?"PASS purchase confirms then shows granted rewards":"FAIL purchase result flow");
            }
            if(tick==355){beforeGold=robin.gold;beforeGems=robin.coin;paidInventory.clear();for(int i=0;i<GetMaxInven();++i)paidInventory.push_back(robin.inven[i]);}
            if(tick>355&&drawHandle==MD_GACHA&&tick%8==0)GachaKey();
            if(tick>355&&drawHandle!=MD_GACHA){
                bool inventorySame=paidInventory.size()==(size_t)GetMaxInven();
                for(int i=0;inventorySame&&i<GetMaxInven();++i)inventorySame=!memcmp(&paidInventory[i],&robin.inven[i],sizeof(ITEM));
                CastleReviewTrace(inventorySame?"PASS original reveal preserves all granted item instances and counts":"FAIL duplicate item grant");
                CastleReviewTrace(fell&&openedChest&&summaryShot?"PASS original fall open cards summary flow":"FAIL original chest animation path");

                CastleReviewTrace(!gachaGrantedPresentation&&robin.gold==beforeGold&&robin.coin==beforeGems?"PASS common reveal closes without duplicate grants":"FAIL common reward close");
                CastleReviewTrace("DONE box info review");done=true;
            }
        }
        return;
    }
    if(getenv("CS_CREW_DETAIL_REVIEW")){
        static int tick=0;static bool pending=false;if(pending)return;++tick;
        if(tick==1){NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);ITEM item={};item.type=ITEM_CREW;item.detail=0;item.lv=1;item.count=1;item.id=710000;robin.inven[100]=item;}
        if(tick==20){touchFunc(TOUCH_FUNC_POPUP_CREWLIST);PlayKey(PLAYER);systemKey=0;}
        if(tick==35){menuItem=100;menuDepth=1;}
        if(tick==70){pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"DONE crew detail capture":"FAIL capture");},std::string(path)+"crew-detail.png");}
        return;
    }
    if(LobbyMenusPerfReview(path))return;
    if(getenv("CS_CASTLE_SCROLL_PERF_REVIEW")){
        static int tick=0;static bool pending=false;static double seconds=0,vertices=0,batches=0;
        if(pending)return;++tick;
        if(tick==1){robin.demoSeen[DEMO_TUTORIAL_END]=true;GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);}
        if(tick==20){systemKey=AVK_POPUP_CASTLEMENU;PlayKey(PLAYER);systemKey=0;CastleMenuModuleReviewSet(0,0);CastleMenuCommand(TOUCH_FUNC_RENEW_CASTLE_FACILITIES);}
        if(tick>=60&&tick<180){
            auto* director=cocos2d::Director::getInstance();seconds+=director->getDeltaTime();
            vertices+=director->getRenderer()->getDrawnVertices();batches+=director->getRenderer()->getDrawnBatches();
        }
        if(tick==180){char text[200];snprintf(text,sizeof(text),"PROFILE frame_ms=%.3f vertices=%.0f batches=%.0f",seconds*1000/120,vertices/120,batches/120);CastleReviewTrace(text);}
        const char* shot=nullptr;
        if(tick==190)shot="top.png";
        if(tick==210){
            const int start=DY-(GNBHEIGHT-GNB_INIT_HEIGHT)-LOBBY_BAR_H-80;
            scY[MENU_CASTLE]=0;scDir=SCROLL_NOTHING;
            CastleMenuFinalDrag(120,start,120,start+120,start);
            const bool up=scY[MENU_CASTLE]==120;
            CastleMenuFinalDrag(120,start,120,start+60,start+120);
            const bool down=scY[MENU_CASTLE]==60;
            CastleMenuFinalDrag(120,start,120,start-5000,start+60);
            const bool clampTop=scY[MENU_CASTLE]==0;
            CastleMenuFinalDrag(120,start,120,start+5000,start);
            const bool clampBottom=scY[MENU_CASTLE]==scT[MENU_CASTLE]&&scY[MENU_CASTLE]>0;
            CastleReviewTrace(up&&down&&clampTop&&clampBottom?"PASS finger direction and both scroll bounds":"FAIL finger direction or bounds");
            scY[MENU_CASTLE]=120;scDir=SCROLL_NOTHING;shot="partial.png";
        }
        if(tick==230){scY[MENU_CASTLE]=scT[MENU_CASTLE];shot="bottom.png";}
        if(tick==250){scY[MENU_CASTLE]=0;robin.castleProgress.rooms[0][0]=5;shot="room-upgraded.png";}
        if(tick==270){CastleMenuCommand(TOUCH_FUNC_RENEW_CASTLE_PARTS);scY[MENU_CASTLE]=0;shot="parts.png";}
        if(shot){pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS capture":"FAIL capture");},std::string(path)+shot);}
        if(tick==290)CastleReviewTrace("DONE castle scroll performance review");
        return;
    }
    if(MenuRenewalReviewStep(path))return;
    if(getenv("CS_SHARED_LOBBY_NAV_REVIEW")){
        static int tick=0;static bool pending=false;if(pending)return;++tick;
        if(tick==1){robin.demoSeen[DEMO_TUTORIAL_END]=true;GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);}
        if(tick==30){CastleReviewClick(TOUCH_FUNC_POPUP_CREWLIST);PlayKey(PLAYER);systemKey=0;}
        if(tick==20||tick==50||tick==90){
            const int commands[]={TOUCH_FUNC_SHOP,TOUCH_FUNC_COLLECTIONS,TOUCH_FUNC_LOBBY_ADVENTURE,TOUCH_FUNC_POPUP_CREWLIST,TOUCH_FUNC_POPUP_CASTLEMENU};
            const int margin=(int)(24*DX/640.f),width=DX-2*margin,gap=Max(1,(int)(2*DX/640.f));
            bool correct=true;
            for(int tab=0;tab<5;++tab){int count=0;
                for(int i=0;i<touchIndex;++i)if(touchRect[i][4]==commands[tab]){
                    ++count;correct=correct&&touchRect[i][0]==margin+width*tab/5&&touchRect[i][2]==width*(tab+1)/5-width*tab/5-gap;
                }
                correct=correct&&count==(tick==50?0:1);
            }
            if(tick==50){
                int backButtons=0;for(int i=0;i<touchIndex;++i)backButtons+=touchRect[i][4]==TOUCH_FUNC_POPUP_CLOSE;
                correct=correct&&popUpCnt>0&&popUp[popUpCnt-1].type==POPUPTYPE_CREWLIST&&backButtons==1;
            }
            CastleReviewTrace(correct?"PASS one shared full-width navigation and matching touch rectangles":"FAIL duplicate or mismatched navigation");
            pending=true;const char* name=tick==20?"nav-main.png":tick==50?"nav-companions.png":"nav-return.png";
            cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS nav capture":"FAIL nav capture");},std::string(path)+name);
        }
        if(tick==70){CastleReviewClick(TOUCH_FUNC_POPUP_CLOSE);PlayKey(PLAYER);systemKey=0;}
        if(tick==100)CastleReviewTrace("DONE shared navigation review");
        return;
    }
    if(getenv("CS_SHOP_CURRENCY_REVIEW")){
        static int tick=0;static bool pending=false;if(pending)return;++tick;
        if(tick==1){robin.demoSeen[DEMO_TUTORIAL_END]=true;GotoLobby();while(popUpCnt>0)ClosePopUp();}
        if(tick==20){CastleReviewClick(TOUCH_FUNC_SHOP);PlayKey(PLAYER);systemKey=0;}
        if(tick==35)CastleReviewClick(TOUCH_FUNC_SHOP_MAIN_TAB+2);
        if(tick==60||tick==110){
            CastleReviewTrace(ShopCurrencyReviewChecks()?"PASS twelve currency products visible and unavailable purchases disabled":"FAIL currency catalog");
            pending=true;const char* name=tick==60?"currency-top.png":"currency-bottom.png";
            cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS currency capture":"FAIL currency capture");},std::string(path)+name);
        }
        if(tick==90){scY[MENU_SHOP]=scT[MENU_SHOP];scDir=SCROLL_NOTHING;}
        if(tick==85){robin.coin=10;robin.gold=30;}
        if(tick==100){CastleReviewClick(TOUCH_FUNC_SHOP_GOLD);}
        if(tick==105){
            CastleReviewTrace(robin.coin==0&&robin.gold==1030?"PASS gold purchase spends gems and grants exact gold":"FAIL gold exchange balances");
            ShopCatalogTouch(TOUCH_FUNC_SHOP_GOLD);
            CastleReviewTrace(robin.coin==0&&robin.gold==1030?"PASS insufficient gems never grant gold":"FAIL free gold exchange");
            bool noEnergy=GetStageAdmissionHeart(0)==0&&GetStageAdmissionHeart(100)==0;
            for(int i=0;i<touchIndex;++i)if(touchRect[i][4]==TOUCH_FUNC_HEARTAMOUNT)noEnergy=false;
            CastleReviewTrace(noEnergy?"PASS no lobby energy offer or stage admission cost":"FAIL energy remains");
        }
        if(tick==130)CastleReviewTrace("DONE currency review");
        return;
    }
    if(getenv("CS_ROOM_UPGRADE_REVIEW")){
        static int tick=0;static bool pending=false;if(pending)return;++tick;
        static auto saved=robin.castleProgress;static long long gold=0,hp=0;
        if(tick==20){robin.demoSeen[DEMO_TUTORIAL_END]=true;GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);}
        if(tick==30){CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_DEBUG);saved=robin.castleProgress;gold=robin.gold;hp=ao[PLAYER].hp;}
        if(tick==32&&!getenv("CS_ROOM_UPGRADE_REVIEW_NO_CROWD"))CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_CROWD);
        if(tick==34)CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_HIDE);
        if(tick>=40&&tick<760){
            const int sample=(tick-40)/12,step=(tick-40)%12,c=sample/6,lv=sample%6;
            if(step==0)CastleReviewTrace(CastleRoomUpgradeReview(c,lv,true)?"PASS configure facility visuals":"FAIL configure facility visuals");
            if(step==6){
                CastleReviewTrace(CastleRoomUpgradeReview(c,lv,false)?"PASS facility atlas level and shader":"FAIL facility atlas level or shader");
                CastleReviewTrace(!memcmp(&saved,&robin.castleProgress,sizeof(saved))&&gold==robin.gold&&hp==ao[PLAYER].hp?"PASS facility preview preserves save":"FAIL facility preview mutated save");
                char name[80];sprintf(name,"castle-%02d-level-%d.png",c+1,lv);pending=true;
                cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS facility level capture":"FAIL facility level capture");},std::string(path)+name);
            }
        }
        if(tick>=760&&tick<820){
            const int facility=(tick-760)/12,step=(tick-760)%12;
            if(step==0)CastleReviewTrace(CastleRoomUpgradeReviewOne(facility,true)?"PASS configure final castle facility":"FAIL configure final castle facility");
            if(step==6){
                CastleReviewTrace(CastleRoomUpgradeReviewOne(facility,false)?"PASS final castle independent facility":"FAIL final castle independent facility");
                CastleReviewTrace(!memcmp(&saved,&robin.castleProgress,sizeof(saved))&&gold==robin.gold?"PASS facility preview preserves save":"FAIL facility preview mutated save");
                char name[80];sprintf(name,"castle-10-only-room-%d.png",facility+1);pending=true;
                cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS individual facility capture":"FAIL individual facility capture");},std::string(path)+name);
            }
        }
        if(tick==825){CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_DEBUG);}
        if(tick==827){CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_DEBUG);CastleReviewTrace(!memcmp(&saved,&robin.castleProgress,sizeof(saved))?"PASS facility debug restoration":"FAIL facility debug restoration");CastleReviewTrace("PASS room upgrades complete");}
        return;
    }
    if(const char* mode=getenv("CS_TUTORIAL_REVIEW")){
        //합성 전투판 튜토리얼(docs/기획_튜토리얼_합성.md §8). fresh: 열 단계를 사람처럼 지난다 · resume: 저장된 단계에서 잇는다 · done: 완료 유지와 재실행.
        static int tick=0;static bool pending=false,driven=false,captureArmed=false;
        static std::string capturePath,captureName;
        static auto captureAt=std::chrono::steady_clock::now();
        if(pending)return;
        //캡처는 1.6초 뒤에 찍는다 - 마스크와 손가락은 그 화면이 0.9초 보인 뒤 0.4초에 걸쳐 나타난다.
        static auto focusSince=std::chrono::steady_clock::now();
        {int r[2][4]={};if(MergeTutorialFocus(r)==0)focusSince=std::chrono::steady_clock::now();}   //밝힐 것이 끊기면 안내도 다시 1.3초 뒤에 뜬다
        if(captureArmed){
            const auto now=std::chrono::steady_clock::now();
            if(now<captureAt||std::chrono::duration<float>(now-focusSince).count()<1.5f)return;
            captureArmed=false;pending=true;
            cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS tutorial capture":"FAIL tutorial capture");},capturePath+captureName+".png");
            return;
        }
        ++tick;
        if(tick==1){
            capturePath=path;
            NetBootstrapBegin();NetChooseLogin(LOGIN_GUEST);
            if(!strcmp(mode,"fresh"))NewGame();
            GotoLobby();while(popUpCnt>0)ClosePopUp();
        }
        NetUpdate();
        if(!strcmp(mode,"resume")){
            if(tick==30){char info[80];sprintf(info,"INFO resumed tutorial step %d",gCastleTutorialStep);CastleReviewTrace(info);CastleReviewTrace(gCastleTutorialStep==CastleTutorial::Depart?"PASS tutorial persisted resume":"FAIL tutorial persistence");CastleTutorialCommand(TOUCH_FUNC_TUTORIAL_SKIP);NetFlush();}
            if(tick==130)CastleReviewTrace("PASS tutorial complete");return;
        }
        if(!strcmp(mode,"done")){
            if(tick==30){CastleReviewTrace(gCastleTutorialStep==CastleTutorial::Done?"PASS tutorial completion persists":"FAIL tutorial completion persistence");CastleReviewClick(TOUCH_FUNC_TUTORIAL_HELP);}
            if(tick==40)CastleReviewTrace(gCastleTutorialStep==CastleTutorial::Depart?"PASS tutorial replay without reset":"FAIL tutorial replay");
            if(tick==130)CastleReviewTrace("PASS tutorial complete");return;
        }
        static auto traceFn=[](const char* text){CastleReviewTrace(text);};
        static auto captureFn=[](const char* name){captureName=name;captureAt=std::chrono::steady_clock::now()+std::chrono::milliseconds(1600);captureArmed=true;};
        if(tick==20)CastleReviewTrace(gCastleTutorialStep==CastleTutorial::Depart?"PASS new game tutorial starts at depart":"FAIL tutorial welcome");
        if(tick==40){   //로비: 다른 단추는 안 먹고 전투 시작만 먹는다
            const int before=gCastleTutorialStep;
            MergeRouletteTouch(0,901,DX*.5f,DY*.5f);MergeRouletteTouch(2,901,DX*.5f,DY*.5f);
            CastleReviewTrace(gCastleTutorialStep==before&&!MergeRouletteActive()?"PASS depart ignores other lobby touches":"FAIL depart gate");
        }
        if(tick==60){int r[2][4]={};const int n=MergeTutorialFocus(r);CastleReviewTrace(n==1?"PASS depart focuses the start button":"FAIL depart focus");
            if(n){const float x=r[0][0]+r[0][2]*.5f,y=r[0][1]-r[0][3]*.5f;MergeRouletteTouch(0,902,x,y);MergeRouletteTouch(2,902,x,y);}}
        if(tick==75){captureFn("tutorial-00-depart");}
        if(tick==90){int r[2][4]={};const int n=MergeTutorialFocus(r);   //들어가기 창의 「전투」
            if(n){const float x=r[0][0]+r[0][2]*.5f,y=r[0][1]-r[0][3]*.5f;MergeRouletteTouch(0,903,x,y);MergeRouletteTouch(2,903,x,y);}}
        if(tick==120)CastleReviewTrace(MergeRouletteActive()&&gCastleTutorialStep==CastleTutorial::Spin?"PASS entering the battle advances to spin":"FAIL battle entry");
        //열 단계는 관찰 2초 넷·릴·등장·보상창을 다 합쳐 보통 40~60초다. 9000틀(150초)까지 기다린다.
        if(tick>120&&tick<9000&&!driven){driven=MergeTutorialReviewDrive(traceFn,captureFn);if(driven)tick=9000;}
        if(tick==9010){GotoLobby();CastleTutorialCommand(TOUCH_FUNC_TUTORIAL_HELP);NetFlush();}
        if(tick==9020)CastleReviewTrace(gCastleTutorialStep==CastleTutorial::Depart?"PASS tutorial resume checkpoint":"FAIL tutorial checkpoint");
        if(tick==9060)CastleReviewTrace(driven?"PASS tutorial complete":"FAIL tutorial drive timeout");
        return;
    }
    if(const char* mode=getenv("CS_TITLE_LOGIN_REVIEW")){
        static int tick=0;static bool pending=false;if(pending)return;++tick;
        const bool reset=!strcmp(mode,"reset");
        if(tick==30){
            CastleReviewTrace(MergeRouletteTitleCastlesLayoutReview()?"PASS title shares the parked castle campsite without lobby UI or companions":"FAIL title campsite");
            bool guest=false,start=false,resetButton=false;
            for(int i=0;i<touchIndex;++i){guest|=touchRect[i][4]==TOUCH_FUNC_TITLE_LOGIN_GUEST;start|=touchRect[i][4]==TOUCH_FUNC_GOTOPLAY;resetButton|=touchRect[i][4]==TOUCH_FUNC_TITLE_RESET_SAVE;}
            CastleReviewTrace(drawHandle==MD_TITLE&&guest&&!start&&resetButton&&!TitleLoginBusy()?"PASS manual guest gate with reset button":"FAIL title manual gate");
            CastleReviewTrace(!NetLoginProviderAvailable(LOGIN_GOOGLE)&&!NetLoginProviderAvailable(LOGIN_APPLE)?"PASS social providers do not impersonate guest":"FAIL social provider gating");
            pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS title login capture":"FAIL title login capture");},std::string(path)+mode+"-login.png");
        }
        if(tick==45){
            pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS animated title second frame":"FAIL animated title second frame");},std::string(path)+mode+"-motion.png");
        }
        if(reset&&tick==35){robin.gold=777777;robin.stage=10;CastleReviewClick(TOUCH_FUNC_TITLE_RESET_SAVE);TitleLoginReset();}
        if(reset&&tick==50)CastleReviewTrace(drawHandle==MD_TITLE&&!TitleLoginBusy()&&robin.gold!=777777&&robin.stage==0?"PASS reset progress stays on title":"FAIL reset progress");
        if(tick==55)CastleReviewClick(TOUCH_FUNC_TITLE_LOGIN_GUEST);
        if(tick==58){TitleLoginStart(LOGIN_GUEST);CastleReviewTrace(TitleLoginBusy()?"PASS guest queues loading once":"FAIL guest loading");}
        if(tick==73){
            CastleReviewTrace(drawHandle==MD_TITLE&&TitleLoginBusy()?"PASS title loading bar before lobby":"FAIL title loading state");
            pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS title loading capture":"FAIL title loading capture");},std::string(path)+mode+"-loading.png");
        }
        if(tick==110){
            CastleReviewTrace(drawHandle==MD_LOBBY&&NetHasRememberedGuestLogin()?"PASS manual guest login enters lobby":"FAIL guest lobby entry");
            pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS lobby entry capture":"FAIL lobby entry capture");},std::string(path)+mode+"-lobby.png");
        }
        if(tick==115)CastleReviewTrace("PASS title login review complete");
        return;
    }
    if(getenv("CS_FACILITY_ECONOMY_REVIEW")){
        static int tick=0;static long long expectedGold=0;static bool pending=false;if(pending)return;++tick;
        if(tick==20){robin.demoSeen[DEMO_TUTORIAL_END]=true;GotoLobby();while(popUpCnt>0)ClosePopUp();}
        if(tick==30)CastleReviewTrace(CastleProductionReview()?"PASS production resources upgrades recovery collection and clock rebasing":"FAIL production economy");
        if(tick==40){
            robin.castleProgress.version=2;robin.castleProgress.owned=1023u;robin.gold=1000000;
            for(int c=0;c<10;++c)for(int i=0;i<4;++i)robin.castleProgress.rooms[c][i]=0;
            systemKey=AVK_POPUP_CASTLEMENU;PlayKey(PLAYER);systemKey=0;CastleMenuModuleReviewSet(9,0);
        }
        if(tick==50){scY[MENU_CASTLE]=scT[MENU_CASTLE];scDir=SCROLL_NOTHING;}
        if(tick==65){
            pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS economy capture":"FAIL economy capture");},std::string(path)+"economy.png");
        }
        if(tick==70)CastleReviewClick(TOUCH_FUNC_CASTLE_FACILITY_UPGRADE+0);
        if(tick==80){
            pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS economy capture":"FAIL economy capture");},std::string(path)+"confirm.png");
        }
        if(tick==85){expectedGold=robin.gold-240+CastleIncomeNow();CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_CONFIRM);CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_CONFIRM);}
        if(tick==90){
            CastleReviewTrace(robin.castleProgress.rooms[9][0]==1&&robin.castleProgress.rooms[0][0]==1&&robin.gold==expectedGold?"PASS economy upgrade charges once":"FAIL economy upgrade charge");
            CastleReviewTrace("PASS facility economy complete");
        }
        return;
    }
    if(getenv("CS_FUNCTIONAL_CASTLES_REVIEW")){
        static int tick=0;static long long expectedGold=0;static bool pending=false;if(pending)return;++tick;
        static auto saved=robin.castleProgress;static long long gold=0,hp=0;
        if(tick==20){robin.demoSeen[DEMO_TUTORIAL_END]=true;GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);}
        if(tick==30){CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_DEBUG);saved=robin.castleProgress;gold=robin.gold;hp=ao[PLAYER].hp;}
        if(tick==32)CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_CROWD);
        if(tick==34)CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_CROWD);
        if(tick>=40&&tick<1040){
            const int sample=(tick-40)/100,step=(tick-40)%100;
            if(step==0 && sample>0)CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_NEXT);
            if(step==2)CastleSoftSectorsReview(1);
            if(step==4)CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_FIRE);
            if(step==75)CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_HIDE);
            if(step==90)CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_DEBUG);
            if(step==25 || step==85){
                CastleReviewTrace(LobbyCastleFunctionalReview()?"PASS functional rooms and crowd":"FAIL functional rooms and crowd");
                if(step==85)CastleReviewTrace(LobbyArtilleryDebugHits()>0?"PASS lobby cannon impact":"FAIL lobby cannon impact");
                CastleReviewTrace(!memcmp(&saved,&robin.castleProgress,sizeof(saved))&&gold==robin.gold&&hp==ao[PLAYER].hp?"PASS debug preserves gameplay":"FAIL debug mutation");
                char name[80];sprintf(name,"castle-%02d-%s.png",gMobileCastleVisual+1,step==25?"firing":"crowd");pending=true;
                cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS functional capture":"FAIL functional capture");},std::string(path)+name);
            }
        }
        if(tick==1045){
            CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_DEBUG);
            robin.castleProgress.owned=1023u;robin.gold=1000000;
            systemKey=AVK_POPUP_CASTLEMENU;PlayKey(PLAYER);systemKey=0;
            CastleMenuModuleReviewSet(9,0);
        }
        if(tick==1055){
            CastleReviewTrace(CastleMenuFinalReviewChecks()?"PASS facility upgrade costs levels and production":"FAIL facility model guards");
            scY[MENU_CASTLE]=scT[MENU_CASTLE];scDir=SCROLL_NOTHING;
        }
        if(tick==1065){
            pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS facility menu capture":"FAIL facility menu capture");},std::string(path)+"facilities.png");
        }
        if(tick==1070)CastleReviewClick(TOUCH_FUNC_CASTLE_FACILITY_UPGRADE+4);
        if(tick==1080){
            pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS facility confirmation capture":"FAIL facility confirmation capture");},std::string(path)+"facility-confirm.png");
        }
        if(tick==1085){expectedGold=robin.gold-2400+CastleIncomeNow();CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_CONFIRM);CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_CONFIRM);}
        if(tick==1090){
            CastleReviewTrace(robin.castleProgress.rooms[9][4]==1&&robin.gold==expectedGold?"PASS facility real gold upgrade exactly once":"FAIL facility gold upgrade");
            CastleReviewTrace("PASS functional castles complete");
        }
        return;
    }
    if(getenv("CS_SOFT_SECTORS_REVIEW")){
        static int tick=0;static bool pending=false;if(pending)return;++tick;
        if(tick==1){
            robin.demoSeen[DEMO_TUTORIAL_END]=true;robin.castleProgress.version=1;robin.castleProgress.owned=1023u;
            int crew=0;for(int k=0;k<gTotalCrew&&crew<20;++k){
                if(crewData[k*CREWDATASIZE+CREWDATA_TYPE]==NPC_SHIP)continue;
                MakeItem(&robin.inven[10+crew],ITEM_CREW,1,GRADE_NORMAL,k,0);robin.inven[10+crew].count=1;++crew;
            }
            robin.count=Max(robin.count,30);
        }
        if(tick>=20&&tick<580){
            const int sample=(tick-20)/14,c=sample/4,mode=sample%4,step=(tick-20)%14;
            if(step==0){
                robin.castle=c;gMobileCastleVisual=c;
                for(int p=0;p<5;++p)robin.castleProgress.parts[c][p]=mode>=2?5:0;
                GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);
                CastleSoftSectorsReview(mode%2?1:2);
            }
            if(step==9){
                CastleReviewTrace(CastleSoftSectorsReview(mode%2?3:0)?"PASS soft castle sectors and residents":"FAIL soft castle sectors");
                char name[100];sprintf(name,"castle-%02d-%s-%s.png",c+1,mode>=2?"max":"base",mode%2?"open":"closed");
                pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS soft castle capture":"FAIL soft castle capture");},std::string(path)+name);
            }
        }
        if(tick==585)CastleReviewTrace("PASS soft sectors complete");
        return;
    }
    if(getenv("CS_LOBBY_CASTLE_DEBUG_REVIEW")){
        static int tick=0,previous=0;static bool pending=false;if(pending)return;++tick;
        static auto saved=robin.castleProgress;
        if(tick==20){robin.demoSeen[DEMO_TUTORIAL_END]=true;GotoLobby();while(popUpCnt>0)ClosePopUp();}
        if(tick==25)CastleReviewClick(TOUCH_FUNC_DEBUG_TOGGLE);
        if(tick==30){previous=gMobileCastleVisual;CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_DEBUG);saved=robin.castleProgress;}
        if(tick>=40&&tick<340){
            const int sample=(tick-40)/30,step=(tick-40)%30;
            if(step==0 && sample>0)CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_NEXT);
            if(step>=2&&step<=6)CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_PART+step-2);
            if(step==8)CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_ALL);
            if(step==10)CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_INTERIOR);
            if(step==20){
                const int c=gMobileCastleVisual;
                CastleReviewTrace(LobbyCastleDebugLevel(c,0)>=0 && !memcmp(&saved,&robin.castleProgress,sizeof(saved))?"PASS cosmetic preview preserves save":"FAIL preview changed save");
                char name[80];sprintf(name,"castle-%02d.png",c+1);pending=true;
                cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS castle debug capture":"FAIL castle debug capture");},std::string(path)+name);
            }
        }
        if(tick==345){
            const int selected=gMobileCastleVisual;
            const int expected=CastleMenuModel::Owned(saved,selected)?selected:(int)robin.castle;
            CastleReviewClick(TOUCH_FUNC_LOBBY_CASTLE_DEBUG);
            CastleReviewTrace(gMobileCastleVisual==expected && robin.castle==expected && LobbyCastleDebugLevel(expected,0)==-1 && !memcmp(&saved,&robin.castleProgress,sizeof(saved))?"PASS castle debug restored":"FAIL restore");
            CastleReviewTrace("PASS lobby castle debug complete");
        }
        return;
    }
    if(getenv("CS_ALL_REGION_REVIEW")){
        static int tick=0;static bool pending=false;if(pending)return;++tick;
        if(tick==1){robin.demoSeen[DEMO_TUTORIAL_END]=true;}
        if(tick>=20 && tick<320){
            const int sample=(tick-20)/10,step=(tick-20)%10;
            if(step==0){GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);}
            if(!AllRegionBackgroundReviewAt(sample)){CastleReviewTrace("FAIL region textures missing");return;}
            if(step==7){
                char name[80];sprintf(name,"region-%02d-phase-%d.png",sample/2+1,sample%2);
                pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS region capture":"FAIL region capture");},std::string(path)+name);
            }
        }
        if(tick==325)CastleReviewTrace("PASS all region review complete");
        return;
    }
    if(getenv("CS_SCENE_FIX_REVIEW")){
        static int tick=0;static bool pending=false;if(pending)return;++tick;
        if(tick==1){robin.demoSeen[DEMO_TUTORIAL_END]=true;robin.castleProgress.version=1;robin.castleProgress.owned=1023u;}
        if(tick>=20 && tick<320){
            const int c=(tick-20)/30,step=(tick-20)%30;
            if(step==0){
                robin.castle=c;gMobileCastleVisual=c;GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(true);SceneBackgroundReviewAt(c);
            }
            if(c==0 && step==10)CastleReviewClick(TOUCH_FUNC_DEBUG_TOGGLE);
            if(step==24){
                CastleReviewTrace(SceneGridReviewCheck()?"PASS original castle grid and cell alignment":"FAIL castle grid resource");
                bool debug=false,pvp=false,maximum=false,background=false;
                for(int i=0;i<touchIndex;++i){const int f=touchRect[i][4];debug|=f==TOUCH_FUNC_DEBUG_TOGGLE;pvp|=f==TOUCH_FUNC_PVP_TEST;maximum|=f==TOUCH_FUNC_DEBUG_MAXSTATUS;background|=f==TOUCH_FUNC_DEBUG_STAGEBG;}
                CastleReviewTrace(debug&&pvp&&maximum&&background?"PASS expanded debug controls accessible":"FAIL debug controls missing");
                char name[80];sprintf(name,"scene-%02d.png",c+1);pending=true;
                cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS scene capture":"FAIL scene capture");},std::string(path)+name);
            }
        }
        if(tick==325)CastleReviewTrace("PASS scene fixes review complete");
        return;
    }
    if(getenv("CS_HYBRID_FLEET_REVIEW")) {
        static bool pending=false;if(pending)return;
        static int tick=0;++tick;
        if(tick==1){
            robin.demoSeen[DEMO_TUTORIAL_END]=true;robin.castleProgress.version=1;robin.castleProgress.owned=1023u;
            int crew=0;for(int k=0;k<gTotalCrew&&crew<6;++k){
                if(crewData[k*CREWDATASIZE+CREWDATA_TYPE]==NPC_SHIP)continue;
                MakeItem(&robin.inven[10+crew],ITEM_CREW,1,GRADE_NORMAL,k,0);robin.inven[10+crew].count=1;++crew;
            }
            robin.count=Max(robin.count,16);
        }
        if(tick>=20&&tick<580){
            const int sample=(tick-20)/14,c=sample/4,mode=sample%4,step=(tick-20)%14;
            if(step==0){
                robin.castle=c;gMobileCastleVisual=c;
                for(int p=0;p<5;++p)robin.castleProgress.parts[c][p]=mode>=2?5:0;
                GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);
                CastleHybridFleetReview((mode%2)?1:2);
            }
            if(step==9){
                CastleReviewTrace(CastleHybridFleetReview((mode%2)?3:0)?"PASS fleet lobby sockets and facade":"FAIL fleet lobby placement");
                char name[100];sprintf(name,"castle-%02d-%s-%s.png",c+1,mode>=2?"max":"base",mode%2?"open":"closed");
                pending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){pending=false;CastleReviewTrace(ok?"PASS fleet lobby capture":"FAIL fleet lobby capture");},std::string(path)+name);
            }
        }
        if(tick==585)CastleReviewTrace("PASS fleet lobby review complete");
        return;
    }
    if(getenv("CS_HYBRID_REVIEW")) {
        static bool capturePending=false;
        if(capturePending)return;
        static int tick=0;++tick;
        if(tick==1){
            robin.demoSeen[DEMO_TUTORIAL_END]=true;robin.castle=0;gMobileCastleVisual=0;
            robin.castleProgress.version=1;robin.castleProgress.owned|=1u;
            for(int i=0;i<5;++i)robin.castleProgress.parts[0][i]=0;
            int crew=0;
            for(int k=0;k<gTotalCrew && crew<3;++k){
                if(crewData[k*CREWDATASIZE+CREWDATA_TYPE]==NPC_SHIP)continue;
                MakeItem(&robin.inven[10+crew],ITEM_CREW,1,GRADE_NORMAL,k,0);robin.inven[10+crew].count=1;++crew;
            }
            robin.count=Max(robin.count,13);
            MakeItem(&robin.inven[0],ITEM_SWORD,1,GRADE_NORMAL,0,0);robin.inven[0].count=1;
            GotoLobby();while(popUpCnt>0)ClosePopUp();LoadoutSetOpen(false);
        }
        if(tick==35){
            CastleReviewTrace(CastleHybridReview(0)?"PASS hybrid castle floor and allies behind commander":"FAIL hybrid castle placement");
        }
        if(tick==50)CastleHybridReview(1);
        if(tick==75)CastleReviewTrace(CastleHybridReview(3)?"PASS hybrid interior opens":"FAIL hybrid interior");
        if(tick==90){CastleHybridReview(2);for(int i=0;i<5;++i)robin.castleProgress.parts[0][i]=5;}
        if(tick==120)CastleHybridReview(1);
        if(tick==155){CastleHybridReview(2);CastleReviewClick(TOUCH_FUNC_SHOP);PlayKey(PLAYER);systemKey=0;}
        if(tick==195){while(popUpCnt>0)ClosePopUp();GotoLobby();}
        if(tick==210){CastleReviewClick(TOUCH_FUNC_COLLECTIONS);PlayKey(PLAYER);systemKey=0;curEquipTab=EQUIPTAB_GEAR;}
        if(tick==250){while(popUpCnt>0)ClosePopUp();GotoLobby();}
        if(tick==265){systemKey=AVK_POPUP_CASTLEMENU;PlayKey(PLAYER);systemKey=0;}
        if(tick==305){while(popUpCnt>0)ClosePopUp();GotoLobby();}
        if(tick==320){touchFunc(TOUCH_FUNC_SETTING);PlayKey(PLAYER);systemKey=0;}
        if(tick==365){while(popUpCnt>0)ClosePopUp();GotoLobby();LoadoutClear();LoadoutToggle(0);
            for(int i=10;i<13;++i)LoadoutToggle(i);LoadoutSetOpen(true);}
        if(tick==410){LoadoutSetOpen(false);GotoPlay();StageRtBegin();CastleHybridReview(4);StageRtSetAuto(false);battleStartFrame=0;}
        if(tick>=410 && tick<580){
            ao[PLAYER].active=true;ao[PLAYER].dead=false;ao[PLAYER].hp=ao[PLAYER].maxhp=1000000000;
            for(int i=CREW;i<CREW+MAXCREW;++i)if(ao[i].active){ao[i].dead=false;ao[i].hp=ao[i].maxhp=1000000000;}
            for(int i=ENEMY;i<NEUTRAL;++i)if(ao[i].active){ao[i].dead=false;ao[i].hp=ao[i].maxhp=1000000000;}
        }
        if(tick==500)GridTestSkipOffer();
        if(tick==580){while(popUpCnt>0)ClosePopUp();GotoTitle();}
        const char* shot=tick==40?"lobby-closed.png":tick==80?"lobby-open.png":tick==110?"lobby-max.png":
            tick==145?"lobby-max-open.png":tick==185?"shop.png":tick==240?"equipment.png":
            tick==295?"castle.png":tick==350?"settings.png":tick==395?"loadout.png":
            tick==470?"battle-shop.png":tick==550?"battle.png":tick==630?"title.png":nullptr;
        if(shot){capturePending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){capturePending=false;CastleReviewTrace(ok?"PASS hybrid capture":"FAIL hybrid capture");},std::string(path)+shot);}
        if(tick==650)CastleReviewTrace("PASS hybrid UI review complete");
        return;
    }
    if(getenv("CS_CASTLE_MODULE_REVIEW")) {
        static bool capturePending=false;
        if(capturePending)return;
        static int tick=0;++tick;
        if(tick==1){
            robin.demoSeen[DEMO_TUTORIAL_END]=true;robin.castleProgress.version=1;robin.castleProgress.owned=1023u;
            robin.gold=1000000;GotoLobby();while(popUpCnt>0)ClosePopUp();
            systemKey=AVK_POPUP_CASTLEMENU;PlayKey(PLAYER);systemKey=0;
        }
        if(tick>=20 && tick<1220){
            const int sample=(tick-20)/10,c=sample/12,variant=sample%12;
            if((tick-20)%10==0)CastleMenuModuleReviewSet(c,variant);
            if((tick-20)%10==6){
                CastleReviewTrace(CastlePartsUpgradePlacementStable(c,variant)?"PASS stable hull deck hero and axle placement":"FAIL upgrade moves castle placement");
                char name[80];sprintf(name,"castle-%02d-variant-%02d.png",c+1,variant);
                capturePending=true;
                cocos2d::utils::captureScreen([](bool ok,const std::string&){capturePending=false;CastleReviewTrace(ok?"PASS module capture":"FAIL module capture");},std::string(path)+name);
            }
        }
        if(tick==1225)CastleReviewTrace("PASS 120 castle upgrade combinations complete");
        return;
    }
    if(getenv("CS_CASTLE_FINAL_REVIEW")) {
        static bool capturePending=false;
        // Cocos captureScreen is single-flight until asynchronous PNG saving
        // finishes. Preserve the reviewed state instead of racing the next shot.
        if(capturePending)return;
        static int tick=0,upgradeScroll=0;static long long purchaseGold=0;++tick;
        if(tick==1){
            CastleMenuCommand(TOUCH_FUNC_RENEW_CASTLE_PARTS); // Select this scenario's tab explicitly.
            robin.demoSeen[DEMO_TUTORIAL_END]=true;robin.castle=0;
            robin.castleProgress=CastleMenuModel::Progress();robin.castleProgress.version=1;robin.castleProgress.owned=1;
            robin.gold=1000000;robin.coin=1234;GotoLobby();while(popUpCnt>0)ClosePopUp();
        }
        if(tick==20){systemKey=AVK_POPUP_CASTLEMENU;PlayKey(PLAYER);systemKey=0;}
        if(tick==45){
            int parts=0;bool noFloors=true;for(int i=0;i<touchIndex;++i){
                const int f=touchRect[i][4];if(f==TOUCH_FUNC_CASTLE_NEW_ROOMS)noFloors=false;
                if(f>=TOUCH_FUNC_CASTLE_NEW_ROW && f<TOUCH_FUNC_CASTLE_NEW_ROW_END)++parts;
            }
            CastleReviewTrace(noFloors && curMenu==MENU_CASTLE && parts<=5?"PASS five part castle menu opens":"FAIL castle menu opens");
            CastleReviewTrace(CastleMenuFinalReviewChecks()?"PASS costs confirmation duplicate cancel stale input scroll and room preservation":"FAIL castle data guards");
        }
        if(tick==50){
            int start=DY-GNBHEIGHT-100;
            CastleMenuFinalDrag(100,start,100,start+5000,start);upgradeScroll=scY[MENU_CASTLE];
            CastleReviewTrace(scY[MENU_CASTLE]==scT[MENU_CASTLE]?"PASS full body scroll bottom":"FAIL body scroll bottom");scDir=SCROLL_NOTHING;
        }
        if(tick==63){
            // Production rows extend the body; inspect parts at their own scroll position.
            const int view=DY-(GNBHEIGHT-GNB_INIT_HEIGHT)-LOBBY_BAR_H-6-54-HOMEBAR_HEIGHT-16;
            upgradeScroll=scY[MENU_CASTLE]=Max(0,1022-view);
        }
        if(tick==65) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_ROW+4);
        if(tick==70) CastleReviewTrace(robin.castleProgress.parts[0][4]==0 && robin.gold==1000000 && scY[MENU_CASTLE]==upgradeScroll?"PASS selection changes details without charging or scrolling":"FAIL part selection");
        if(tick==75) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_UPGRADE);
        if(tick==85) {CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_CONFIRM);CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_CONFIRM);}
        if(tick==95) CastleReviewTrace(robin.castleProgress.parts[0][4]==1 && robin.gold==999700 && robin.coin==1234 && CastleVisualPartLevel(0,4)==1 && scY[MENU_CASTLE]==upgradeScroll?"PASS one gold charge upgrade costume level and scroll position":"FAIL real gold upgrade");
        if(tick==105)robin.castleProgress.parts[0][4]=5;
        if(tick==115){robin.gold=0;robin.castleProgress.parts[0][4]=0;}
        if(tick==125){robin.gold=999700;scY[MENU_CASTLE]=0;for(int i=0;i<5;++i)robin.castleProgress.parts[0][i]=5;}
        if(tick==135)CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_NEXT);
        if(tick==145){purchaseGold=robin.gold;CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_SELECT);}
        if(tick==165)CastleReviewTrace(robin.castleProgress.owned==1023u && robin.gold>=purchaseGold?"PASS all castles available without purchase charge":"FAIL all castle availability");
        if(tick==180){for(int i=0;i<8;++i)CastleMenuCommand(TOUCH_FUNC_CASTLE_NEW_NEXT);scY[MENU_CASTLE]=0;}
        const char* shot=tick==40?"top.png":tick==60?"bottom.png":tick==80?"upgrade-confirm.png":tick==100?"upgraded.png":tick==110?"max.png":tick==120?"insufficient.png":tick==150?"purchase.png":tick==170?"second.png":tick==195?"tenth.png":nullptr;
        if(shot){capturePending=true;cocos2d::utils::captureScreen([](bool ok,const std::string&){capturePending=false;CastleReviewTrace(ok?"PASS castle final capture":"FAIL castle final capture");},std::string(path)+shot);}
        if(tick>=210&&tick<410){
            const int c=(tick-210)/20,step=(tick-210)%20;
            if(step==0){CastleMenuModuleReviewSet(c,0);scY[MENU_CASTLE]=0;}
            if(step==2){
                char name[64];sprintf(name,"castle-top-%02d.png",c+1);capturePending=true;
                cocos2d::utils::captureScreen([](bool ok,const std::string&){capturePending=false;CastleReviewTrace(ok?"PASS castle assembled menu capture":"FAIL castle assembled menu capture");},std::string(path)+name);
            }
            if(step==3){CastleMenuCommand(TOUCH_FUNC_RENEW_CASTLE_FACILITIES);}
            if(step==5){scY[MENU_CASTLE]=scT[MENU_CASTLE];scDir=SCROLL_NOTHING;}
            if(step==10){
                bool valid=true,last=false;
                for(int i=0;i<touchIndex;++i){const int f=touchRect[i][4]-TOUCH_FUNC_CASTLE_FACILITY_UPGRADE;
                    if(f>=0&&f<5){valid&=f<CastleFacilities::Counts[c];last|=f==CastleFacilities::Counts[c]-1;}}
                CastleReviewTrace(valid&&last&&CastleMenuModel::Owned(robin.castleProgress,c)?"PASS castle-specific facility count and bottom upgrade button":"FAIL castle facility menu");
                char name[64];sprintf(name,"facilities-%02d.png",c+1);capturePending=true;
                cocos2d::utils::captureScreen([](bool ok,const std::string&){capturePending=false;CastleReviewTrace(ok?"PASS castle facility menu capture":"FAIL castle facility menu capture");},std::string(path)+name);
            }
        }
        if(tick==415){
            CastleReviewClick(TOUCH_FUNC_POPUP_CLOSE);PlayKey(PLAYER);systemKey=0;
            CastleReviewTrace(curMenu!=MENU_CASTLE?"PASS castle final review complete":"FAIL castle close");
        }
        return;
    }
    if(getenv("CS_SHOP_SPEC_REVIEW")) {
        static int tick=0;static long long cancelGold=0;++tick;
        if(tick==2){
            auto zero=GoldAmountFormat::Split(0,true),million=GoldAmountFormat::Split(9995000,true),full=GoldAmountFormat::Split(1000000,false),limit=GoldAmountFormat::Split(GOLD_MAX,true);
            CastleReviewTrace(zero.whole==0&&zero.unit==-1&&million.whole==9&&million.tenth==9&&million.unit==1&&full.whole==1000000&&full.unit==-1&&limit.whole==99&&limit.unit==1?"PASS gold units preserve magnitude":"FAIL gold amount units");
        }
        if(tick==1) {robin.demoSeen[DEMO_TUTORIAL_END]=true;GotoLobby();while(popUpCnt>0)ClosePopUp();robin.gold=9995000;}
        if(tick==20) {CastleReviewClick(TOUCH_FUNC_SHOP);PlayKey(PLAYER);systemKey=0;}
        if(tick==40) CastleReviewTrace(ShopSpecReviewChecks()
            ?"PASS real hero pools grants insufficient gold full storage duplicate purchase and unavailable IAP"
            :"FAIL shop spec runtime checks");
        const char* shot=tick==60?"recommended.png":tick==100?"supplies.png":tick==140?"supply-pool.png":tick==180?"packages.png":tick==240?"supplies-bottom.png":nullptr;
        if(shot) cocos2d::utils::captureScreen([](bool ok,const std::string&) {CastleReviewTrace(ok?"PASS spec capture":"FAIL spec capture");},std::string(path)+shot);
        if(tick==80) CastleReviewClick(TOUCH_FUNC_SHOP_MAIN_TAB+1);
        if(tick==110) CastleReviewClick(TOUCH_FUNC_SHOP_MAIN_TAB+2);
        if(tick==160) CastleReviewClick(TOUCH_FUNC_SHOP_MAIN_TAB+1);
        if(tick==180) {
            bool sale=false,dock=false;
            for(int i=0;i<touchIndex;++i) {
                const int cmd=touchRect[i][4];
                if(cmd>=TOUCH_FUNC_SHOP_IAP&&cmd<=TOUCH_FUNC_SHOP_IAP_END)sale=true;
                if(cmd==TOUCH_FUNC_LOBBY_ADVENTURE||cmd==TOUCH_FUNC_LOBBY_CASTLE)dock=true;
            }
            CastleReviewTrace(!sale&&!dock?"PASS unavailable packages hidden and dock input covered":"FAIL fake package or dock input");
        }
        if(tick==200) {robin.gold=Max(robin.gold,GetBoxPrice(BOX_PAID5,GRADE_NORMAL));CastleReviewClick(TOUCH_FUNC_SHOP_MAIN_TAB);}
        if(tick==220) scY[MENU_SHOP]=scT[MENU_SHOP];
        if(tick==250) {cancelGold=robin.gold;CastleReviewClick(TOUCH_FUNC_SHOP_BUYBOX6);PlayKey(PLAYER);systemKey=0;}
        if(tick==265) {CastleReviewClick(TOUCH_FUNC_SHOP_IAP_CANCEL);PlayKey(PLAYER);systemKey=0;}
        if(tick==275) CastleReviewTrace(robin.gold==cancelGold?"PASS cancellation preserves currency":"FAIL cancellation charged currency");
        if(tick==280) {CastleReviewClick(TOUCH_FUNC_POPUP_CLOSE);PlayKey(PLAYER);systemKey=0;}
        if(tick==290) CastleReviewTrace(popUpCnt==0?"PASS shop spec review complete":"FAIL shop exit");
        return;
    }
    if(getenv("CS_PIXEL_EQUIP_REVIEW")) {
        static int tick=0;++tick;
        if(tick==1) {
            robin.demoSeen[DEMO_TUTORIAL_END]=true;GotoLobby();
            while(popUpCnt>0) ClosePopUp();
            ITEM& item=robin.inven[0];memset(&item,0,sizeof(item));
            item.type=ITEM_SWORD;item.detail=0;item.lv=1;item.count=10;item.id=100000;item.value=100;
            if(getenv("CS_EQUIPMENT_CARDS_REVIEW")){
                for(int i=1;i<25;++i){ITEM copy=item;copy.count=1;copy.id=100000+i;
                    const int desired=(i%6)+1;
                    for(int d=0;d<itemStartCnt[ITEM_SWORD+1]-itemStartCnt[ITEM_SWORD];++d)
                        if(GetItemStar(ITEM_SWORD,d,0)==desired){copy.detail=d;break;}
                    robin.inven[i]=copy;
                }
            }
            for(int h=0;h<TOTALCHAR;++h){
                for(int e=0;e<TOTALEQUIP;++e) robin.charData[h].equip[e].type=EMPTY;
                ITEM starter=item;starter.type=ITEM_SWORD+h;starter.value=19;starter.id=110000+h;
                if(h==ROBIN&&getenv("CS_EQUIPMENT_CARDS_REVIEW"))starter=robin.inven[4];
                robin.charData[h].equip[EQUIP_WEAPON]=starter;
                // This isolated fixture exercises every unlocked hero tab.
                robin.lv=Max(robin.lv,getHeroLv[h]);
            }
            SetPlayerHero(ROBIN);
        }
        if(tick==20) {CastleReviewClick(TOUCH_FUNC_COLLECTIONS);PlayKey(PLAYER);systemKey=0;curEquipTab=EQUIPTAB_GEAR;}
        if(tick==90) {
            if(getenv("CS_EQUIPMENT_CARDS_REVIEW")){
                extern bool EquipmentMenuV2ReviewCards();
                CastleReviewTrace(EquipmentMenuV2ReviewCards()?"PASS six separate equipment cards and native backgrounds":"FAIL equipment card columns or backgrounds");
            }
            CastleReviewTrace(popUpCnt>0 && popUp[popUpCnt-1].type==POPUPTYPE_COLLECTIONS
                ?"PASS equipment opens":"FAIL equipment navigation");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS equipment capture":"FAIL equipment capture");
            },std::string(path)+"equipment.png");
        }
        if(tick==95) CastleReviewTrace(EquipmentMenuV2ReviewChecks()?"PASS equipment V2 scrolling and layout":"FAIL equipment V2 scrolling and layout");
        if(tick==96) {CastleReviewClick(TOUCH_FUNC_SELECT_HERO+DIANA);PlayKey(PLAYER);systemKey=0;CastleReviewTrace(curHero==DIANA?"PASS equipment hero selection":"FAIL equipment hero selection");}
        if(tick==98) CastleReviewTrace(EquipmentMenuV2ReviewEquipping()?"PASS equipment all hero equip and power":"FAIL equipment all hero equip and power");
        if(tick==100) {touchFunc(TOUCH_FUNC_EQUIPMENT_V2_CATEGORY+EQUIP_RING);CastleReviewTrace(menuX==EQUIP_RING?"PASS equipment accessory category":"FAIL equipment accessory category");menuX=0;SetPlayerHero(ROBIN);}
        if(tick==105) {menuItem=0;menuDepth=1;}
        if(tick==145) cocos2d::utils::captureScreen([](bool ok,const std::string&) {
            CastleReviewTrace(ok?"PASS equipment detail capture":"FAIL detail capture");
        },std::string(path)+"equipment-detail.png");
        if(tick==148){CastleReviewClick(TOUCH_FUNC_ITEM_LOCK);PlayKey(PLAYER);systemKey=0;CastleReviewTrace(robin.inven[0].locked?"PASS detail lock touch":"FAIL detail lock touch");}
        if(tick==151){CastleReviewClick(TOUCH_FUNC_ITEM_LOCK);PlayKey(PLAYER);systemKey=0;CastleReviewTrace(!robin.inven[0].locked?"PASS detail unlock touch":"FAIL detail unlock touch");}
        if(tick==155){CastleReviewClick(TOUCH_FUNC_CLOSEALERT);PlayKey(PLAYER);systemKey=0;CastleReviewTrace(menuDepth==0 && curMenu==MENU_COLLECTIONS?"PASS detail closes to equipment":"FAIL detail close touch");}
        if(tick==165) touchFunc(TOUCH_FUNC_EQUIPTAB+EQUIPTAB_STAT);
        if(tick==195) cocos2d::utils::captureScreen([](bool ok,const std::string&) {
            CastleReviewTrace(ok?"PASS equipment stat capture":"FAIL stat capture");
        },std::string(path)+"equipment-stat.png");
        if(tick==215) touchFunc(TOUCH_FUNC_EQUIPTAB+EQUIPTAB_CODEX);
        if(tick==245) cocos2d::utils::captureScreen([](bool ok,const std::string&) {
            CastleReviewTrace(ok?"PASS equipment codex capture":"FAIL codex capture");
        },std::string(path)+"equipment-codex.png");
        if(tick==260) CastleReviewTrace("PASS pixel equipment review complete");
        return;
    }
    if(getenv("CS_PIXEL_SHOP_REVIEW")) {
        static int tick=0;++tick;
        if(tick==1) {
            robin.demoSeen[DEMO_TUTORIAL_END]=true;GotoLobby();
            while(popUpCnt>0) ClosePopUp();
        }
        if(tick==20) {CastleReviewClick(TOUCH_FUNC_SHOP);PlayKey(PLAYER);systemKey=0;}
        if(tick==90) {
            CastleReviewTrace(popUpCnt>0 && popUp[popUpCnt-1].type==POPUPTYPE_SHOPINFO
                ?"PASS shop opened from navigation":"FAIL shop navigation");
            bool dockHit=false;
            for(int i=0;i<touchIndex;++i) {
                const int command=touchRect[i][4];
                if(command==TOUCH_FUNC_LOBBY_ADVENTURE || command==TOUCH_FUNC_LOBBY_DUNGEON
                    || command==TOUCH_FUNC_LOBBY_CASTLE || command==TOUCH_FUNC_COLLECTIONS)
                    dockHit=true;
            }
            CastleReviewTrace(!dockHit?"PASS shop owns dock input layer":"FAIL dock input leaks above shop");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS shop top capture":"FAIL shop capture");
            },std::string(path)+"shop-top.png");
        }
        if(tick==110) scY[MENU_SHOP]=scT[MENU_SHOP];
        if(tick==145) {
            bool usesBottom=false;
            for(int i=0;i<touchIndex;++i) {
                const int command=touchRect[i][4];
                if(command>=TOUCH_FUNC_SHOP_IAP && command<=TOUCH_FUNC_SHOP_IAP_END
                    && touchRect[i][1]-touchRect[i][3]<BOTTOMMENUHEIGHT) usesBottom=true;
            }
            CastleReviewTrace(usesBottom?"PASS products use former dock area":"FAIL shop bottom space unused");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS shop bottom capture":"FAIL shop capture");
            },std::string(path)+"shop-bottom.png");
        }
        if(tick==155) {CastleReviewClick(TOUCH_FUNC_POPUP_CLOSE);PlayKey(PLAYER);systemKey=0;}
        if(tick==165) CastleReviewTrace(popUpCnt==0?"PASS pixel shop review complete":"FAIL shop back");
        return;
    }
    if(getenv("CS_ALLIES_BALANCE_REVIEW")) {
        static int tick=0;++tick;
        if(tick==1) {
            robin.castle=3;robin.castleProgress.version=1;robin.castleProgress.owned=1023u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;robin.bossRoom=0;bossRaidMode=false;
            SetHero();GotoPlay();while(popUpCnt>0) ClosePopUp();
            CastleReviewTrace(StageAlliesBalanceReview()
                ?"PASS 64 placements attack timings 61 unique abilities 183 synergies dedup caps and cleanup"
                :"FAIL 64 ally balance integration");
        }
        if(tick==5) CastleReviewTrace("PASS ally balance review complete");
        return;
    }
    if(getenv("CS_ALLY_LINK_REVIEW")) {
        static int tick=0;static bool pending=false;
        if(pending) return;
        const int hero=tick/560,phase=tick%560;++tick;
        if(hero>=3) {if(tick==1681) CastleReviewTrace("PASS three hero ally links complete");return;}
        if(phase==0) {
            robin.castle=3;robin.castleProgress.version=1;robin.castleProgress.owned=1023u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;robin.bossRoom=0;bossRaidMode=false;
            SetPlayerHero(hero);SetHero();GotoPlay();StageRtBegin();
            CastleReviewTrace(StageAllyLinkReviewSetup(hero)?"PASS three approved companions placed":"FAIL approved companion setup");
            while(popUpCnt>0) ClosePopUp();
            for(int i=ENEMY;i<NEUTRAL;++i) ao[i].active=false;
            OBJECT& foe=ao[ENEMY];foe.type=crewData[CREWDATA_TYPE];SetNpc(&foe);
            foe.mom=ENEMY;foe.active=true;foe.dead=false;foe.moveHandler=0;foe.x=foe.nx=DX-60;
            foe.hp=foe.maxhp=1000000000;foe.shield=foe.shieldMax=0;
            StageArtilleryNotifySpawn(ENEMY);ao[PLAYER].active=true;
            ao[PLAYER].hp=200000000;ao[PLAYER].maxhp=1000000000;ao[PLAYER].shield=0;
        }
        ao[PLAYER].dead=false;
        waveStatus=WAVESTATUS_PLAY;attackSequence=ATTACKSEQUENCE_READY;battleStartFrame=0;
        StageRtSetAuto(phase>=180 && !(phase>=270 && phase<290));
        if(phase==180) {
            ao[PLAYER].hp=200000000;ao[PLAYER].maxhp=1000000000;ao[PLAYER].shield=0;
            CastleReviewTrace(StageAllyLinkReview(0)?"PASS link clocks ready through actual tick model":"FAIL link clock setup");
        }
        if(phase==270) StageAllyLinkReview(2);
        if(phase==289) CastleReviewTrace(StageAllyLinkReview(3)?"PASS paused ally link clocks":"FAIL paused ally clocks");
        if(phase==500) {
            CastleReviewTrace(StageAllyLinkReview(1)?"PASS hero repair heal supply and support projectile impacts":"FAIL hero ally effects");
            CastleReviewTrace(StageAllyLinkReviewUi()?"PASS repair heal link cooldown bars rendered":"FAIL ally ability bars");
            char name[64];sprintf(name,"hero-%d-allies.png",hero);
            pending=true;
            cocos2d::utils::captureScreen([](bool captured,const std::string&) {
                CastleReviewTrace(captured?"PASS hero ally link capture":"FAIL hero ally link capture");pending=false;
            },std::string(path)+name);
        }
        if(phase==550) CastleReviewTrace(StageAllyLinkReview(4)?"PASS run exit clears ally links":"FAIL ally links leaked");
        return;
    }
    if(getenv("CS_HERO_ALLIES_AUDIT")) {
        static int tick=0;static bool pending=false;
        if(pending) return;
        const int page=tick/30,phase=tick%30;++tick;
        if(page>=2) {if(tick==61) CastleReviewTrace("PASS existing 64 allies audit complete");return;}
        const bool ok=HeroAlliesAuditReview(page);
        if(phase==16) CastleReviewTrace(ok?"PASS existing allies IDs and animations":"FAIL ally catalog");
        if(phase==20) {
            char name[64];sprintf(name,"existing-allies-%d.png",page);
            pending=true;
            cocos2d::utils::captureScreen([](bool captured,const std::string&) {
                CastleReviewTrace(captured?"PASS allies audit capture":"FAIL allies audit capture");pending=false;
            },std::string(path)+name);
        }
        return;
    }
    if(getenv("CS_COMPACT_EQUIPMENT_REVIEW")) {
        static int tick=0;static bool pending=false;
        if(pending) return;
        const int page=tick/24,phase=tick%24;++tick;
        if(page>=4) {if(tick==97) CastleReviewTrace("PASS compact equipment complete");return;}
        const bool ok=CompactEquipmentReview(page);
        if(phase==16) CastleReviewTrace(ok?"PASS compact equipment dimensions and rotations":"FAIL compact equipment dimensions");
        if(phase==18) {
            char name[64];sprintf(name,"compact-equipment-%d.png",page);
            pending=true;
            cocos2d::utils::captureScreen([](bool captured,const std::string&) {
                CastleReviewTrace(captured?"PASS compact equipment capture":"FAIL compact equipment capture");pending=false;
            },std::string(path)+name);
        }
        return;
    }
    //---- 히어로 몰빵 개편 ----
    //
    //장비 역할축 · 보석 소켓 · 히어로별 창고 · 상점 줄 갈이 · 동료 체력
    //불가산을 한자리에서 보고, 마지막에 히어로가 쓰러지면 판이 끝나는지
    //살아 있는 판에서 확인한다(CLAUDE.md 3장).
    if(getenv("CS_GEAR_ROLE_REVIEW")) {
        static int tick=0;++tick;
        if(tick==1) {
            robin.castle=0;robin.castleProgress.version=1;robin.castleProgress.owned=1023u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;robin.bossRoom=0;bossRaidMode=false;
            SetPlayerHero(2);SetHero();GotoPlay();
            while(popUpCnt>0) ClosePopUp();
            CastleReviewTrace(GearRoleReview(0)?"PASS gear role axes from bag":"FAIL gear role axes");
            CastleReviewTrace(GearRoleReview(1)?"PASS gem socket amplifies primary axis":"FAIL gem socket");
            CastleReviewTrace(GearRoleReview(2)?"PASS per hero warehouse lines":"FAIL per hero warehouse");
            CastleReviewTrace(GearRoleReview(3)?"PASS run shop swaps to hero line":"FAIL run shop line");
            CastleReviewTrace(GearRoleReview(4)?"PASS crew add no hero hp":"FAIL crew hp still counted");

            //쓰러짐 점검을 위해 적 하나를 세우고 판을 돌린다.
            for(int i=ENEMY;i<NEUTRAL;++i) ao[i].active=false;
            OBJECT& foe=ao[ENEMY];foe.type=crewData[CREWDATA_TYPE];SetNpc(&foe);
            foe.mom=ENEMY;foe.active=true;foe.dead=false;foe.moveHandler=0;foe.x=foe.nx=DX-60;
            foe.hp=foe.maxhp=1000000000;foe.shield=foe.shieldMax=0;
            StageArtilleryNotifySpawn(ENEMY);
            ao[PLAYER].active=true;ao[PLAYER].dead=false;
            StageInitFortressHealthAndArmor();
            CastleReviewTrace(ao[PLAYER].maxhp>0 && ao[PLAYER].shieldMax>=100
                ?"PASS hero dual gauge stands alone":"FAIL hero dual gauge");
            waveStatus=WAVESTATUS_PLAY;attackSequence=ATTACKSEQUENCE_READY;battleStartFrame=0;
            StageRtSetAuto(true);
        }
        //쓰러뜨린다. 다음 프레임의 UpdateStageRealtime 가 끝을 알려야 한다.
        if(tick==30) { ao[PLAYER].shield=0;ao[PLAYER].hp=0; }
        if(tick==34) {
            bool over=false;
            for(int i=0;i<MAXPOPUP;++i) if(popUp[i].active && popUp[i].type==POPUPTYPE_GAMEOVER) over=true;
            CastleReviewTrace(over?"PASS hero down ends the run":"FAIL hero down did not end the run");
            CastleReviewTrace("PASS gear role review complete");
        }
        return;
    }
    if(getenv("CS_MAX_WEAPON_REVIEW")) {
        static int tick=0;static long long before=0,afterManual=0;++tick;
        if(tick==1) {
            robin.castle=0;robin.castleProgress.version=1;robin.castleProgress.owned=1023u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;robin.bossRoom=0;bossRaidMode=false;
            SetPlayerHero(2);SetHero();GotoPlay();
            CastleReviewTrace(MaxWeaponFoundationReview()?"PASS four rewards required weapon optional crew persistent equipment and run cleanup":"FAIL Max foundation");
            CastleReviewTrace(MaxWeaponRuntimeReview(0)?"PASS boomerang hit once return pause target loss and readiness":"FAIL boomerang model");
            while(popUpCnt>0) ClosePopUp();
            for(int i=ENEMY;i<NEUTRAL;++i) ao[i].active=false;
            OBJECT& foe=ao[ENEMY];foe.type=crewData[CREWDATA_TYPE];SetNpc(&foe);
            foe.mom=ENEMY;foe.active=true;foe.dead=false;foe.moveHandler=0;foe.x=foe.nx=DX-60;
            foe.hp=foe.maxhp=1000000000;foe.shield=foe.shieldMax=0;
            StageArtilleryNotifySpawn(ENEMY);ao[PLAYER].active=true;
        }
        ao[PLAYER].hp=ao[PLAYER].maxhp=1000000000;ao[PLAYER].dead=false;
        waveStatus=WAVESTATUS_PLAY;attackSequence=ATTACKSEQUENCE_READY;battleStartFrame=0;
        StageRtSetAuto(tick>=40);
        if(tick==40) {
            before=ao[ENEMY].hp+ao[ENEMY].shield;
            CastleReviewTrace(MaxWeaponRuntimeReview(1)?"PASS live Max throw":"FAIL live Max throw");
        }
        if(tick==65) CastleReviewTrace(MaxWeaponRuntimeReview(2) && ao[ENEMY].hp+ao[ENEMY].shield<before
            ?"PASS live Max contact damage and returning":"FAIL live Max damage or return");
        if(tick==110) CastleReviewTrace(MaxWeaponRuntimeReview(3)?"PASS live Max ready after return":"FAIL live Max stuck");
        if(tick==130) afterManual=ao[ENEMY].hp+ao[ENEMY].shield;
        if(tick==120) cocos2d::utils::captureScreen([](bool ok,const std::string&) {
            CastleReviewTrace(ok?"PASS Max capture":"FAIL Max capture");},std::string(path)+"max-combat.png");
        if(tick==400) {
            CastleReviewTrace(ao[ENEMY].hp+ao[ENEMY].shield<afterManual
                ?"PASS repeated automatic Max basic attack":"FAIL automatic Max basic attack");
            CastleReviewTrace("PASS Max foundation review complete");
        }
        return;
    }
    if(getenv("CS_STAGE_COMBAT_REVIEW")) {
        static int tick=0;++tick;
        if(tick==1) {
            robin.castle=0;robin.castleProgress.version=1;robin.castleProgress.owned=1023u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;robin.bossRoom=0;bossRaidMode=false;
            SetHero();GotoPlay();StageRtBegin();StageCombatReviewSetup();ao[PLAYER].active=true;
            while(popUpCnt>0) ClosePopUp();
            for(int i=ENEMY;i<NEUTRAL;++i) ao[i].active=false;
            OBJECT& foe=ao[ENEMY];foe.type=crewData[CREWDATA_TYPE];SetNpc(&foe);
            foe.mom=ENEMY;foe.active=true;foe.dead=false;foe.moveHandler=0;foe.x=foe.nx=DX-60;
            StageArtilleryNotifySpawn(ENEMY);
        }
        ao[PLAYER].hp=ao[PLAYER].maxhp=1000000000;ao[PLAYER].dead=false;
        ao[ENEMY].hp=ao[ENEMY].maxhp=1000000000;ao[ENEMY].dead=false;
        waveStatus=WAVESTATUS_PLAY;attackSequence=ATTACKSEQUENCE_READY;battleStartFrame=0;
        StageRtSetAuto(tick>45 && !(tick>=850 && tick<880));
        if(tick==40) CastleReviewTrace(StageCombatRuntimeReview(0)?"PASS equipped sword excluded, orbit follows hero head, cannon in grid":"FAIL stage grid or orbit");
        if(tick==180) {
            int visible=0;
            for(int i=0;i<MAXCREW;++i) if(ao[CREW+i].active && !ao[CREW+i].dead) ++visible;
            CastleReviewTrace(visible==2 && StageCombatReviewCrewVisible()
                ?"PASS two loadout crew spawned and drawn on deck":"FAIL loadout crew spawn or deck rendering");
            CastleReviewTrace(StageCombatReviewCooldownVisible()?"PASS crew grid cooldown draws and changes":"FAIL crew grid cooldown not drawn or frozen");
        }
        if(tick==40 || tick==600) cocos2d::utils::captureScreen([](bool,const std::string&) {},std::string(path)+(tick==40?"waiting.png":"attacking.png"));
        if(tick==850) StageCombatRuntimeReview(2);
        if(tick==879) CastleReviewTrace(StageCombatRuntimeReview(3)?"PASS paused combat clocks":"FAIL paused clocks advanced");
        if(tick==900) {
            CastleReviewTrace(StageCombatRuntimeReview(1)?"PASS sword crew cannon impacts and faster monster attacks":"FAIL combat impacts");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {CastleReviewTrace(ok?"PASS stage combat capture":"FAIL stage combat capture");},std::string(path)+"combat.png");
        }
        if(tick==910) CastleReviewTrace("PASS stage combat review complete");
        return;
    }

    if(getenv("CS_CURRENT_CANNON_ICON_REVIEW")) {
        static int tick=0;++tick;
        const int img=CANNON_UPGRADE_ATLAS_IMG;
        if(!sprite[img])LoadImg(img);
        bool ok=sprite[img]!=nullptr;
        MemRect(16,DY-70,608,730,0x16263B);
        SetFontColor(COLOR_WHITE);
        CenterTextStrSolid("CURRENT CANNONS / 10 CASTLES x 6 GRADES",DX/2,DY-91,.7f);
        for(int castle=0;castle<10;++castle) for(int level=0;level<6;++level) {
            const auto& f=MountedCannons::Get(castle,level);
            ok=ok && f.w>0 && f.h>0 && f.x+f.w<=2304 && f.y+f.h<=2560;
            const int x=30+level*96,y=DY-114-castle*66;
            MemRectFrame(x,y,92,62,0x6F849A);
            DrawInventoryCannonIcon(castle,level,x+3,y-3,86,56);
        }
        if(tick==20) {
            CastleReviewTrace(ok?"PASS current cannon sixty registered frames":"FAIL current cannon registration");
            cocos2d::utils::captureScreen([](bool captured,const std::string&) {CastleReviewTrace(captured?"PASS current cannon icon capture":"FAIL current cannon icon capture");},std::string(path)+"current-cannon-icons.png");
        }
        return;
    }
    if(getenv("CS_INDIVIDUAL_V4_REVIEW")) {
        static int tick=0;static bool pending=false;
        if(pending) return;
        const int castle=tick/40,phase=tick%40;++tick;
        if(castle>=10) { if(tick==401) CastleReviewTrace("PASS individual v4 all ten exteriors"); return; }
        if(phase==0) {
            robin.castle=castle;gMobileCastleVisual=castle;robin.castleProgress.version=1;robin.castleProgress.owned|=1023u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            if(getenv("CS_CASTLE_INTERIOR_SYNC_REVIEW")) {
                // Isolated review profile: enough owned companions to detect
                // both the former eight-person cap and decorative-slot loss.
                memset(robin.inven,0,sizeof(robin.inven));robin.maxInven=TOTALINVENTORY;
                int added=0;
                for(int crew=0;crew<gTotalCrew && added<20;++crew) {
                    if(crewData[crew*CREWDATASIZE+CREWDATA_TYPE]==NPC_SHIP) continue;
                    auto& item=robin.inven[added++];item.type=ITEM_CREW;item.detail=crew;item.grade=GRADE_NORMAL;item.count=1;
                }
            }
            GotoLobby();while(popUpCnt>0) ClosePopUp();LoadoutSetOpen(false);
            if(getenv("CS_CASTLE_INTERIOR_SYNC_REVIEW")) {
                gLoadoutCnt=0;
                for(int i=0;i<20 && gLoadoutCnt<3;++i) {
                    const int idx=robin.inven[i].detail;
                    if(idx>=3 && idx<gTotalCrew && enemyData[crewData[idx*CREWDATASIZE+CREWDATA_TYPE]*ENEMYDATASIZE+ENEMYDATA_CMF]>=CREW_CMF_FIRST) gLoadout[gLoadoutCnt++]=i;
                }
            }
        }
        if(phase==16) {
            const bool ok=CastleIndividualReviewCheck(0);
            CastleReviewTrace(CastleIndividualReviewCheck(3)?"PASS visible combat deck and crew foot line":"FAIL combat deck geometry");
            CastleReviewTrace(ok?"PASS individual placement and progression":"FAIL individual placement and progression");
            CastleReviewTrace(CastleIndividualReviewCheck(2)?"PASS uniform room dimensions and floor count":"FAIL uniform room dimensions and floor count");
        }
        if(phase==30) CastleReviewTrace(CastleIndividualReviewCheck(1)?"PASS individual wheels rolling":"FAIL individual wheels rolling");
        if(getenv("CS_CASTLE_INTERIOR_SYNC_REVIEW")) {
            if(phase==19) CastleInteriorSyncReviewCheck(0);
            if(phase==21) CastleReviewTrace(CastleInteriorSyncReviewCheck(1)?"PASS castle zoom out":"FAIL castle zoom out");
            if(phase==24) CastleReviewTrace(CastleInteriorSyncReviewCheck(2)?"PASS castle zoom in":"FAIL castle zoom in");
            if(phase==27) CastleReviewTrace(CastleInteriorSyncReviewCheck(3)?"PASS twenty residents and intact room textures":"FAIL residents or rectangular room textures");
        }
        if(getenv("CS_ROOM_COVER_REVIEW")) {
            if(phase==8) CastleRoomCoverPreview(4);
            if(phase==12) CastleReviewTrace(CastleRoomCoverPreview(3)?"PASS individual outside touch closed":"FAIL individual outside touch closed");
            if(phase==13) CastleRoomCoverPreview(0);
            if(phase==22) CastleRoomCoverPreview(1);
            if(phase==26) CastleReviewTrace(CastleRoomCoverPreview(2)?"PASS individual room reveal":"FAIL individual room reveal");
            if(phase==28) CastleRoomCoverPreview(0);
            if(phase==31) CastleReviewTrace(CastleRoomCoverPreview(2)?"PASS individual room persists after release":"FAIL individual room persists after release");
            if(phase==35) CastleRoomCoverPreview(6);
            if(phase==38) CastleReviewTrace(CastleRoomCoverPreview(3)?"PASS individual room closed":"FAIL individual room closed");
        }
        if(phase==18 || phase==32) {
            char name[80];sprintf(name,"individual-%02d-%d.png",castle+1,phase);
            pending=true;
            cocos2d::utils::captureScreen([](bool ok,const std::string&) { CastleReviewTrace(ok?"PASS individual capture":"FAIL individual capture");pending=false; },std::string(path)+name);
        }
        return;
    }
    if(getenv("CS_UNIFORM_CASTLE_REVIEW")) {
        static bool capturePending=false;
        if(capturePending) return;
        static int tick=0;++tick;
        const int batch=(tick-1)/30,phase=(tick-1)%30;
        if(batch>=35) { if(tick==1051) CastleReviewTrace("PASS all uniform castle stages and mixed parts"); return; }
        const int castle=5+batch/7,variant=batch%7;
        if(phase==0) {
            robin.castle=castle;gMobileCastleVisual=castle;
            robin.castleProgress.version=1;robin.castleProgress.owned|=1023u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            for(int i=0;i<5;++i) robin.castleProgress.parts[castle][i]=variant==6?(i%2?5:0):variant;
            GotoLobby();while(popUpCnt>0) ClosePopUp();LoadoutSetOpen(false);
            CastleRoomCoverPreview(0);
        }
        if(phase==16) CastleReviewTrace(CastleUniformReviewCheck()?"PASS uniform castle placement":"FAIL uniform castle placement");
        if(phase==22) CastleRoomCoverPreview(1);
        if(phase==26) CastleReviewTrace(CastleRoomCoverPreview(2)?"PASS uniform room reveal":"FAIL uniform room reveal");
        if(phase==18 || phase==27) {
            char name[80];sprintf(name,"castle-%02d-stage-%d%s.png",castle+1,variant,phase==18?"":"-open");
            capturePending=true;
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS uniform capture":"FAIL uniform capture");
                capturePending=false;
            },std::string(path)+name);
        }
        if(phase==29) CastleRoomCoverPreview(0);
        return;
    }


    if(getenv("CS_FIXED_WIDTH_REVIEW")) {
        static int tick=0; ++tick;
        const int castle=(tick-1)/40,phase=(tick-1)%40;
        if(castle>=10) { if(tick==401) CastleReviewTrace("PASS all castle widths and heights"); return; }
        if(phase==0) {
            robin.castle=castle;gMobileCastleVisual=castle;
            robin.castleProgress.version=1;robin.castleProgress.owned|=1023u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            for(int i=0;i<5;++i) robin.castleProgress.parts[castle][i]=0;
            GotoLobby();while(popUpCnt>0) ClosePopUp();LoadoutSetOpen(false);
        }
        if(phase==14) CastleReviewTrace(CastleFixedWidthReviewCheck(0)?"PASS fixed width and growing height":"FAIL fixed width or height");
        if(phase==16 || (castle==9 && phase==32)) {
            char name[80];sprintf(name,"castle-%02d-%s.png",castle+1,phase==16?"base":"upper");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS width capture":"FAIL width capture");
            },std::string(path)+name);
        }
        if(castle==9 && phase==20) CastleFixedWidthReviewCheck(1);
        if(castle==9 && phase==30) CastleReviewTrace(CastleFixedWidthReviewCheck(2)?"PASS tall castle vertical pan":"FAIL tall castle vertical pan");
        return;
    }
    if(getenv("CS_TENTH_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) {
            if(tick==721) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type!=NPC_SHIP && StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==790) {
                CastleReviewTrace(TenthSdUpgradeReviewCheck()?"PASS tenth deployed deck positions":"FAIL tenth deployed deck positions");
                cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                    CastleReviewTrace(ok?"PASS deployed capture":"FAIL deployed capture");
                },std::string(path)+"castle-10-companion-deck.png");
            }
            if(tick==810) CastleReviewTrace("PASS all tenth upgrades and mixed assemblies");
            return;
        }
        if(tick==1) {
            robin.castle=9; gMobileCastleVisual=9;
            robin.castleProgress.version=1; robin.castleProgress.owned|=1023u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[9][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(TenthSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&TenthSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        return;
    }
    if(getenv("CS_NINTH_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) {
            if(tick==721) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type!=NPC_SHIP && StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==790) {
                CastleReviewTrace(NinthSdUpgradeReviewCheck()?"PASS ninth deployed deck positions":"FAIL ninth deployed deck positions");
                cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                    CastleReviewTrace(ok?"PASS deployed capture":"FAIL deployed capture");
                },std::string(path)+"castle-9-companion-deck.png");
            }
            if(tick==810) CastleReviewTrace("PASS all ninth upgrades and mixed assemblies");
            return;
        }
        if(tick==1) {
            robin.castle=8; gMobileCastleVisual=8;
            robin.castleProgress.version=1; robin.castleProgress.owned|=511u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[8][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(NinthSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&NinthSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        return;
    }
    if(getenv("CS_EIGHTH_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) {
            if(tick==721) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type!=NPC_SHIP && StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==790) {
                CastleReviewTrace(EighthSdUpgradeReviewCheck()?"PASS eighth deployed deck positions":"FAIL eighth deployed deck positions");
                cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                    CastleReviewTrace(ok?"PASS deployed capture":"FAIL deployed capture");
                },std::string(path)+"castle-8-companion-deck.png");
            }
            if(tick==810) CastleReviewTrace("PASS all eighth upgrades and mixed assemblies");
            return;
        }
        if(tick==1) {
            robin.castle=7; gMobileCastleVisual=7;
            robin.castleProgress.version=1; robin.castleProgress.owned|=255u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[7][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(EighthSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&EighthSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        return;
    }
    if(getenv("CS_SEVENTH_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) {
            if(tick==721) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type!=NPC_SHIP && StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==790) {
                CastleReviewTrace(SeventhSdUpgradeReviewCheck()?"PASS seventh deployed deck positions":"FAIL seventh deployed deck positions");
                cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                    CastleReviewTrace(ok?"PASS deployed capture":"FAIL deployed capture");
                },std::string(path)+"castle-7-companion-deck.png");
            }
            if(tick==810) CastleReviewTrace("PASS all seventh upgrades and mixed assemblies");
            return;
        }
        if(tick==1) {
            robin.castle=6; gMobileCastleVisual=6;
            robin.castleProgress.version=1; robin.castleProgress.owned|=127u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[6][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(SeventhSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&SeventhSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        return;
    }
    if(getenv("CS_SIXTH_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) {
            if(tick==721) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type!=NPC_SHIP && StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==790) {
                CastleReviewTrace(SixthSdUpgradeReviewCheck()?"PASS sixth deployed deck positions":"FAIL sixth deployed deck positions");
                cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                    CastleReviewTrace(ok?"PASS deployed capture":"FAIL deployed capture");
                },std::string(path)+"castle-6-companion-deck.png");
            }
            if(tick==810) CastleReviewTrace("PASS all sixth upgrades and mixed assemblies");
            return;
        }
        if(tick==1) {
            robin.castle=5; gMobileCastleVisual=5;
            robin.castleProgress.version=1; robin.castleProgress.owned|=63u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[5][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(SixthSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&SixthSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        return;
    }
    if(getenv("CS_FIFTH_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) {
            if(tick==721) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type!=NPC_SHIP && StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==790) {
                CastleReviewTrace(FifthSdUpgradeReviewCheck()?"PASS fifth deployed deck positions":"FAIL fifth deployed deck positions");
                cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                    CastleReviewTrace(ok?"PASS deployed capture":"FAIL deployed capture");
                },std::string(path)+"castle-5-companion-deck.png");
            }
            if(tick==810) CastleReviewTrace("PASS all fifth upgrades and mixed assemblies");
            return;
        }
        if(tick==1) {
            robin.castle=4; gMobileCastleVisual=4;
            robin.castleProgress.version=1; robin.castleProgress.owned|=31u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[4][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(FifthSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&FifthSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        return;
    }
    if(getenv("CS_FOURTH_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) {
            if(tick==721) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type!=NPC_SHIP && StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==790) {
                CastleReviewTrace(FourthSdUpgradeReviewCheck()?"PASS fourth deployed deck positions":"FAIL fourth deployed deck positions");
                cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                    CastleReviewTrace(ok?"PASS deployed capture":"FAIL deployed capture");
                },std::string(path)+"castle-4-companion-deck.png");
            }
            if(tick==810) CastleReviewTrace("PASS all fourth upgrades and mixed assemblies");
            return;
        }
        if(tick==1) {
            robin.castle=3; gMobileCastleVisual=3;
            robin.castleProgress.version=1; robin.castleProgress.owned|=15u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[3][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(FourthSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&FourthSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        return;
    }
    if(getenv("CS_THIRD_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) {
            if(tick==721) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type!=NPC_SHIP && StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==790) {
                CastleReviewTrace(ThirdSdUpgradeReviewCheck()?"PASS third deployed deck positions":"FAIL third deployed deck positions");
                cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                    CastleReviewTrace(ok?"PASS deployed capture":"FAIL deployed capture");
                },std::string(path)+"castle-3-companion-deck.png");
            }
            if(tick==810) CastleReviewTrace("PASS all third upgrades and mixed assemblies");
            return;
        }
        if(tick==1) {
            robin.castle=2; gMobileCastleVisual=2;
            robin.castleProgress.version=1; robin.castleProgress.owned|=7u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[2][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(ThirdSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&ThirdSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        return;
    }
    if(getenv("CS_SECOND_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) {
            if(tick==721) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type!=NPC_SHIP && StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==790) {
                CastleReviewTrace(SecondSdUpgradeReviewCheck()?"PASS second deployed deck positions":"FAIL second deployed deck positions");
                cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                    CastleReviewTrace(ok?"PASS deployed capture":"FAIL deployed capture");
                },std::string(path)+"castle-2-companion-deck.png");
            }
            if(tick==810) CastleReviewTrace("PASS all second upgrades and mixed assemblies");
            return;
        }
        if(tick==1) {
            robin.castle=1; gMobileCastleVisual=1;
            robin.castleProgress.version=1; robin.castleProgress.owned|=3u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[1][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(SecondSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&SecondSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        return;
    }
    if(getenv("CS_STARTER_UPGRADE_REVIEW")) {
        static int tick=0; ++tick;
        const int batch=(tick-1)/80, phase=(tick-1)%80;
        if(batch>=9) return;
        if(tick==1) {
            robin.castle=0; gMobileCastleVisual=0;
            robin.castleProgress.version=1; robin.castleProgress.owned|=1u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        if(phase==0) {
            static const int mixed[3][5]={{0,5,2,4,1},{5,0,3,1,4},{2,4,5,0,3}};
            for(int i=0;i<5;++i) robin.castleProgress.parts[0][i]=(unsigned char)(batch<6?batch:mixed[batch-6][i]);
            CastleRoomCoverPreview(0);
        }
        if(phase==20) {
            CastleReviewTrace(StarterSdUpgradeReviewCheck()?"PASS upgrade assets geometry and half width":"FAIL upgrade resource geometry");
            StarterSdWheelReview(true);
        }
        if(phase==24 || phase==54) {
            char name[80]; sprintf(name,"%s-%d-%s.png",batch<6?"stage":"mixed",batch<6?batch:batch-6,phase==24?"closed":"open");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS upgrade capture":"FAIL upgrade capture");
            },std::string(path)+name);
        }
        if(phase==40) CastleRoomCoverPreview(1);
        if(phase==52) CastleReviewTrace(CastleRoomCoverPreview(2)&&StarterSdUpgradeReviewCheck()?"PASS upgrade room reveal":"FAIL upgrade reveal or resident clipping");
        if(phase==65) CastleRoomCoverPreview(0);
        if(phase==72) CastleReviewTrace(StarterSdWheelReview(false)?"PASS upgrade rolling wheels":"FAIL upgrade wheels");
        if(batch==8 && phase==78) CastleReviewTrace("PASS all starter upgrades and mixed assemblies");
        return;
    }
    if(getenv("CS_TENTH_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=9; gMobileCastleVisual=9;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=1023u;
            const char* requested=getenv("CS_TENTH_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[9][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_NINTH_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=8; gMobileCastleVisual=8;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=511u;
            const char* requested=getenv("CS_NINTH_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[8][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_EIGHTH_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=7; gMobileCastleVisual=7;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=255u;
            const char* requested=getenv("CS_EIGHTH_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[7][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_SEVENTH_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=6; gMobileCastleVisual=6;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=127u;
            const char* requested=getenv("CS_SEVENTH_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[6][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_SIXTH_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=5; gMobileCastleVisual=5;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=63u;
            const char* requested=getenv("CS_SIXTH_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[5][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_FIFTH_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=4; gMobileCastleVisual=4;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=31u;
            const char* requested=getenv("CS_FIFTH_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[4][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_FOURTH_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=3; gMobileCastleVisual=3;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=15u;
            const char* requested=getenv("CS_FOURTH_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[3][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_THIRD_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=2; gMobileCastleVisual=2;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=7u;
            const char* requested=getenv("CS_THIRD_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[2][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_SECOND_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=1; gMobileCastleVisual=1;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=3u;
            const char* requested=getenv("CS_SECOND_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[1][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_STARTER_SD_SANDBOX")) {
        static bool started=false;
        if(!started) {
            started=true; robin.castle=0; gMobileCastleVisual=0;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            robin.castleProgress.version=1; robin.castleProgress.owned|=1u;
            const char* requested=getenv("CS_STARTER_SD_STAGE");
            const int level=requested?Max(0,Min(5,atoi(requested))):0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[0][i]=(unsigned char)level;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        return; // Interactive review: no scripted touches, phase changes or captures.
    }
    if(getenv("CS_ROOM_COVER_REVIEW")) {
        static int tick=0; ++tick;
        if(tick==1) {
            robin.castle=0; gMobileCastleVisual=0;
            for(int i=0;i<5;++i) robin.castleProgress.parts[0][i]=0;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(false);
        }
        const int phase=tick;
        if(phase==35) StarterSdWheelReview(true);
        if(phase==45) CastleRoomCoverPreview(1);
        if(phase==80) CastleReviewTrace(CastleRoomCoverPreview(2)?"PASS held circular reveal":"FAIL held circular reveal");
        if(phase==95) CastleRoomCoverPreview(0);
        if(phase==125) CastleReviewTrace(CastleRoomCoverPreview(3)?"PASS released facade restored":"FAIL facade restore");
        if(phase==125) CastleReviewTrace(StarterSdWheelReview(false)?"PASS half-screen width and rolling wheels":"FAIL castle width or wheel rotation");
        if(phase==35 || phase==80 || phase==125) {
            char name[64]; sprintf(name,"castle-%d-%s.png",gMobileCastleVisual+1,
                phase==35?"closed":phase==80?"held":"released");
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS facade capture":"FAIL facade capture");
            },std::string(path)+name);
        }
        if(tick==140 && !getenv("CS_SD_ROOM_DECK_REVIEW")) CastleReviewTrace("PASS room cover review");
        if(getenv("CS_SD_ROOM_DECK_REVIEW")) {
            if(tick==145) {
                StageRtBegin(); GotoPlay(); battleStartFrame=0; StageRtSetAuto(false);
                int added=0;
                for(int k=0;k<gTotalCrew && added<MAXCREW;++k) {
                    const int type=crewData[k*CREWDATASIZE+CREWDATA_TYPE];
                    if(type==NPC_SHIP) continue;
                    if(StageRtAddCrew(type)) ++added;
                }
                for(int k=0;k<MAXCREW;++k) {
                    ao[CREW+k].active=true; ao[CREW+k].dead=false;
                    ao[CREW+k].moveHandler=0; ao[CREW+k].drawHandler=CREWDRAW;
                }
            }
            if(tick==220) CastleReviewTrace(SdRoomDeckReviewCheck()?"PASS companion deck anchors and real positions":"FAIL companion deck positions");
            if(tick==220) cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS deployed companions capture":"FAIL deployed companions capture");
            },std::string(path)+"castle-1-companion-deck.png");
            if(tick==230) CastleRoomCoverPreview(1);
            if(tick==260) cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS deployed cutaway capture":"FAIL deployed cutaway capture");
            },std::string(path)+"castle-1-deployed-interior.png");
            if(tick==275) CastleReviewTrace("PASS SD room and companion deck review");
        }
        return;
    }
    if(getenv("CS_BATTLE_MENU_REVIEW")) {
        static int menuTick=0; ++menuTick;
        static int shopGround=0;
        if(menuTick==1) {
            robin.castle=0; gMobileCastleVisual=0;
            robin.castleProgress.version=1; robin.castleProgress.owned=1023u;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby(); while(popUpCnt>0) ClosePopUp();
        }
        if(menuTick==30) LoadoutSetOpen(true);
        if(menuTick==45) {
            const auto heart = robin.heart;
            const int handle = drawHandle;
            CastleReviewClick(TOUCH_FUNC_LOADOUT_CLOSE);
            systemKey = AVK_CLR; PlayKey(PLAYER);
            CastleReviewTrace(LoadoutOpen() && BattleEntryLocked() &&
                drawHandle==handle && robin.heart==heart ?
                "PASS preparation outside tap and back stay in run":"FAIL preparation exit guard");
        }
        if(menuTick==180) {
            const auto heart = robin.heart;
            BattleAbandonCommand();
            CastleReviewTrace(IsStageRealtime() && BattleEntryLocked() && robin.heart==heart ?
                "PASS precombat abandon blocked":"FAIL precombat abandon guard");
        }
        if(menuTick==60) CastleReviewTrace(BattleMenuPreviewDragCheck()?"PASS warehouse drag into grid":"FAIL warehouse drag into grid");
        if(menuTick==100) CastleReviewTrace(BattleMenuPreviewWarehouseGestureCheck()?
            "PASS star footer button drag tap and cancel":"FAIL warehouse gesture regions");
        if(menuTick==110||menuTick==600) {
            LoadoutSetOpen(false); GotoPlay(); StageRtBegin(); StageRtSetAuto(false);
            battleStartFrame=0;
        }
        if(menuTick==250) GridTestSkipOffer();
        if(menuTick==210) {
            shopGround=GetStageSceneGroundY();
            CastleReviewTrace(GridTestOfferOpen()&&!StageRtAutoOn()?"PASS initial shop before battle":"FAIL initial shop before battle");
        }
        if(menuTick==320) CastleReviewTrace(StageRtAutoOn()&&!GridTestOfferOpen()&&GetStageSceneGroundY()<shopGround?
            "PASS world descends with full battle grid":"FAIL battle layout transition");
        if(menuTick>=250&&menuTick<360) {
            ao[PLAYER].hp=ao[PLAYER].maxhp=1000000000; ao[PLAYER].dead=false;
            for(int i=ENEMY;i<NEUTRAL;++i) if(ao[i].active) { ao[i].hp=ao[i].maxhp=1000000000; ao[i].dead=false; }
        }
        if(menuTick==360) GridTestRefresh();
        if(menuTick==335) StageRtSetAuto(false);
        if(menuTick==345) CastleReviewTrace(GetStageSceneGroundY()<shopGround&&!GridTestOfferOpen()?
            "PASS pause retains compact combat menu":"FAIL pause menu");
        if(menuTick==350) StageRtSetAuto(true);
        if(menuTick==460) CastleReviewTrace(GridTestOfferOpen()&&GetStageSceneGroundY()==shopGround?
            "PASS world returns for shopping":"FAIL return shop layout");
        if(menuTick==500) {
            robin.castle=9; gMobileCastleVisual=9;
            GotoLobby(); while(popUpCnt>0) ClosePopUp(); LoadoutSetOpen(true);
        }
        if(menuTick==585) CastleReviewTrace(BattleMenuPreviewScrollCheck()?
            "PASS centred 48px grid and four warehouse rows":"FAIL 48px inventory scrolling");
        const char* shot=menuTick==70?"01-warehouse-4rows.png":menuTick==210?"02-first-shop.png":
            menuTick==320?"03-battle-grid.png":menuTick==460?"04-return-shop.png":
            menuTick==570?"05-castle10-warehouse.png":menuTick==700?"06-castle10-shop.png":nullptr;
        if(shot) cocos2d::utils::captureScreen([](bool ok,const std::string&) {
            CastleReviewTrace(ok?"PASS battle menu capture":"FAIL battle menu capture");
        },std::string(path)+shot);
        if(menuTick==730) {
            GridTestSkipOffer();
            CastleReviewTrace(!BattleEntryLocked()?"PASS exit unlocks after combat starts":"FAIL combat exit lock");
            BattleAbandonCommand();
            CastleReviewTrace(!IsStageRealtime()?"PASS explicit combat abandon":"FAIL explicit combat abandon");
            CastleReviewTrace("PASS battle menu flow review");
        }
        return;
    }
    if (getenv("CS_CASTLE_LAYOUT_REVIEW")) {
        static int layoutTick=0; ++layoutTick;
        if(layoutTick==1) {
            robin.castle=0; robin.castleProgress=CastleMenuModel::Progress();
            CastleProgressEnsure(); robin.castleProgress.owned=1023u;
            GotoLobby(); touchDisable=false;
            systemKey=AVK_POPUP_CASTLEMENU; PlayKey(PLAYER);
        }
        if(layoutTick==70) for(int i=0;i<9;++i) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_NEXT);
        if(layoutTick==130) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_DETAIL);
        if(layoutTick==190) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_PARTS);
        if(layoutTick==250) CastleReviewTrace(CastleMenuSwipe(DX/2,DY/2,DX/2,DY/2+200)?"PASS vertical castle pan":"FAIL vertical castle pan");
        if(layoutTick==310) CastleReviewTrace(CastleMenuSwipe(DX/2,DY/2,DX/2,DY/2-500)?"PASS reverse castle pan":"FAIL reverse castle pan");
        if(layoutTick==370) CastleReviewTrace("PASS native castle layout review");
        const char* shot=layoutTick==40?"01-native-first.png":layoutTick==100?"02-native-last.png":
            layoutTick==220?"03-part-anchors.png":layoutTick==280?"04-panned-top.png":layoutTick==340?"05-panned-bottom.png":nullptr;
        if(shot) cocos2d::utils::captureScreen([](bool ok,const std::string&) {
            CastleReviewTrace(ok?"PASS native castle capture":"FAIL native castle capture");
        },std::string(path)+shot);
        return;
    }
    if (getenv("CS_CANNON_LOBBY_REVIEW")) {
        static int lobbyTick=0;
        ++lobbyTick;
        if ((lobbyTick-1)%60==0 && lobbyTick<=1200) {
            const int sample=(lobbyTick-1)/60;
            robin.castle=sample/2;
            gMobileCastleVisual=robin.castle;
            robin.castleProgress.version=1;
            robin.castleProgress.owned=1023u;
            robin.castleProgress.parts[robin.castle][3]=(sample%2)*5;
            robin.demoSeen[DEMO_TUTORIAL_END]=true;
            GotoLobby();
            while(popUpCnt>0) ClosePopUp();
        }
        if(lobbyTick%60==40 && lobbyTick<1200) {
            const int sample=lobbyTick/60;
            char name[64]; sprintf(name,"lobby_%02d_lv_%d.png",sample/2+1,(sample%2)*5);
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS lobby cannon capture":"FAIL lobby cannon capture");
            },std::string(path)+name);
        }
        if(lobbyTick==1200) CastleReviewTrace("PASS lobby cannon gallery");
        return;
    }
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
        const bool partsReview=getenv("CS_CANNON_PARTS_REVIEW")!=nullptr;
        if(partsReview && (bridgeTick-1)%60==0 && bridgeTick<=1200) {
            const int sample=(bridgeTick-1)/60;
            robin.castle=sample/2;
            gMobileCastleVisual=robin.castle;
            robin.castleProgress.parts[robin.castle][3]=(sample%2)*5;
            GotoPlay(); StageRtBegin(); StageRtSetAuto(false);
            battleStartFrame=0;
        }
        // Explicit preview samples exercise full, partial and empty health pools.
        ao[PLAYER].maxhp=10000;
        ao[PLAYER].hp=partsReview?10000:bridgeTick<70?10000:bridgeTick<130?6800:0;
        ao[PLAYER].dead=false;
        for(int i=ENEMY;i<NEUTRAL;++i) ao[i].active=false;
        OBJECT& foe=ao[ENEMY];
        if(bridgeTick==1 || (partsReview && (bridgeTick-1)%60==0)) {
            foe.type=crewData[CREWDATA_TYPE];
            SetNpc(&foe);
            foe.mom=ENEMY;
        }
        foe.active=true; foe.dead=false; foe.moveHandler=0;
        foe.maxhp=24000; foe.hp=partsReview?24000:bridgeTick<70?24000:bridgeTick<130?9600:0;
        if(partsReview && getenv("CS_CANNON_SHOT_REVIEW")) StageArtilleryPreviewStep(bridgeTick%60==30);
        if(partsReview && bridgeTick%60==40 && bridgeTick<1200) {
            const int sample=bridgeTick/60;
            float mx=0,my=0;
            CastleReviewTrace(CastlePartsCannonMuzzle(robin.castle+1,&mx,&my) && mx>=0 && mx<=DX && my>=0 && my<=DY?
                "PASS mounted cannon muzzle":"FAIL mounted cannon muzzle bounds");
            char shotName[64]; sprintf(shotName,"castle_%02d_lv_%d.png",sample/2+1,(sample%2)*5);
            cocos2d::utils::captureScreen([](bool ok,const std::string&) {
                CastleReviewTrace(ok?"PASS cannon part capture":"FAIL cannon part capture");
            },std::string(path)+shotName);
        }
        if(partsReview && bridgeTick==1200) CastleReviewTrace("PASS cannon parts gallery");
        if(getenv("CS_SHOP_OFFER_REVIEW") && bridgeTick==20) StageShopPreviewOpen();
        if(getenv("CS_SHOP_OFFER_REVIEW") && bridgeTick==120)
            CastleReviewTrace(StageShopPreviewPurchaseChecks()?"PASS mixed shop purchases and funds guard":"FAIL mixed shop purchases");
        const char* shot=partsReview?nullptr:bridgeTick==40?"bridge-full.png":bridgeTick==100?"bridge-damaged.png":bridgeTick==160?"bridge-empty.png":nullptr;
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
        CastleReviewTrace(sprite[INVENTORY_CANNON_ATLAS_IMG] && texture[INVENTORY_CANNON_ATLAS_IMG] &&
            GetResourceName(RES_IMG,INVENTORY_CANNON_ATLAS_IMG).find("inventory_cannon-atlas.png")!=std::string::npos?
            "PASS cannon atlas registry and loading":"FAIL cannon atlas registry or loading");
    }
    if (tick == 70) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_NEXT);
    if (tick == 80) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_BUY_GOLD);
    if (tick == 130) {
        CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_PREV);
        CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_DETAIL);
    }
    if (tick == 190) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_ROOMS);
    if (tick == 200) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_ROW);
    if (tick == 250) { CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_UPGRADE); }
    if (tick == 310) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_BACK);
    if (tick == 320) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_PARTS);
    if (tick == 330) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_ROW + 3);
    if (tick == 345) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_PAID_UPGRADE);
    if (tick == 355) CastleReviewTrace(robin.castleProgress.parts[0][3]==1 && robin.coin==9997?
        "PASS paid part upgrade":"FAIL paid part upgrade");
    if (tick == 335 && getenv("CS_CANNON_ASSET_REVIEW")) robin.castleProgress.parts[0][3]=2;
    if (tick == 370) {
        for (int i = 0; i < 5; ++i) robin.castleProgress.parts[0][i] = 5;
        CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_BACK);
    }
    if (tick == 380) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_BACK);
    if (tick == 390) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_NEXT);
    if (tick == 395) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_BUY);
    if (tick == 430) { CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_CONFIRM); }
    if(tick==280) CastleReviewTrace(robin.castleProgress.rooms[0][0]==1 && robin.gold==999760?"PASS room upgrade":"FAIL room upgrade");
    if(tick==460) CastleReviewTrace(CastleMenuModel::Owned(robin.castleProgress,1) && robin.coin==9397?"PASS paid purchase":"FAIL paid purchase");
    if(tick==480) CastleReviewClick(TOUCH_FUNC_CASTLE_NEW_BACK);
    if(tick==490) CastleReviewTrace(CastleMenuSwipe(DX*.75f,DY-GNBHEIGHT-100*_2X,DX*.25f,DY-GNBHEIGHT-100*_2X)?"PASS swipe next":"FAIL swipe next");
    if(tick==500) CastleReviewTrace(CastleMenuSwipe(DX*.25f,DY-GNBHEIGHT-100*_2X,DX*.75f,DY-GNBHEIGHT-100*_2X)?"PASS swipe previous":"FAIL swipe previous");
    if(tick==520 && !NetIsBusy()) {
        if(NetRequest(NETREQ_LOAD)) { robin.castleProgress=CastleMenuModel::Progress(); CastleReviewTrace("local server reload requested"); }
        else CastleReviewTrace("FAIL reload request");
    }
    if(tick==600) CastleReviewTrace(NetLastResult()==NETRESULT_OK &&
        CastleMenuModel::Owned(robin.castleProgress,1) && robin.castleProgress.rooms[0][0]==1 &&
        CastleMenuModel::Completed(robin.castleProgress,0)==25 && robin.coin==9397 && robin.gold==999760?
        "PASS local server save and reload":"FAIL local server save and reload");
    const char* shot = tick==40?"01-list.png":tick==100?"02-locked.png":
        tick==160?"03-parts.png":tick==220?"04-room.png":tick==280?"05-room-upgraded.png":
        tick==340?"06-cannon.png":tick==400?"07-purchase.png":tick==460?"08-purchased.png":nullptr;
    if (shot) cocos2d::utils::captureScreen([](bool ok,const std::string& file) {
        FILE* log = fopen((std::string(getenv("CS_CASTLE_REVIEW_PATH"))+"screens.log").c_str(),"a");
        if (log) { fprintf(log,"%s %s\n",ok?"PASS":"FAIL",file.c_str()); fclose(log); }
    },std::string(path)+shot);
}
