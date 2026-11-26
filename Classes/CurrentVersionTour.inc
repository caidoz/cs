// Explicit, isolated recording account. No normal-game timing or rules change.
static bool CurrentVersionTour(const char* path){
 if(!getenv("CS_CURRENT_VERSION_TOUR"))return false;
 using Clock=std::chrono::steady_clock;
 static bool initialized=false,started=false;static Clock::time_point began;
 static int phase=0,page=0;static Clock::time_point changed;
 if(!initialized){NewGame();robin.demoSeen[DEMO_TUTORIAL_END]=true;CastleTutorialLoad(CastleTutorial::Done);initialized=true;}
 mustRefresh=true;
 if(!started){FILE* f=fopen((std::string(path)+"recording.start").c_str(),"r");if(!f)return true;fclose(f);began=changed=Clock::now();started=true;CastleReviewTrace("TOUR title");}
 const auto now=Clock::now();const double wait=std::chrono::duration<double>(now-changed).count();
 const auto advance=[&](int next,const char* message){phase=next;changed=now;CastleReviewTrace(message);};
 const auto open=[](int command){CastleReviewClick(command);PlayKey(PLAYER);systemKey=0;};
 if(phase==0&&wait>3){open(TOUCH_FUNC_TITLE_LOGIN_GUEST);advance(1,"TOUR guest login");}
 else if(phase==1&&drawHandle==MD_LOBBY&&wait>3){advance(2,"TOUR lobby");}
 else if(phase==2&&wait>2.5){
  const int commands[]={TOUCH_FUNC_SHOP,TOUCH_FUNC_COLLECTIONS,TOUCH_FUNC_POPUP_CREWLIST,TOUCH_FUNC_POPUP_CASTLEMENU,TOUCH_FUNC_SETTING};
  open(commands[page]);advance(3,"TOUR menu opened");
 }
 else if(phase==3&&wait>2.4){while(popUpCnt>0)ClosePopUp();advance(4,"TOUR menu closed");}
 else if(phase==4&&wait>.55){if(++page<5)advance(2,"TOUR next menu");else{open(TOUCH_FUNC_LOBBY_ADVENTURE);advance(5,"TOUR adventure lobby");}}
 else if(phase==5&&wait>1.5){MergeRouletteCurrentTour(0);advance(6,"TOUR prepared boss-finisher resume fixture");}
 else if(phase==6&&wait>.8){MergeRouletteCurrentTour(1);advance(7,"TOUR battle start pressed");}
 else if(phase==7&&wait>1.7){MergeRouletteCurrentTour(2);advance(8,"TOUR resume final boss");}
 else if(phase==8&&wait>2.5){if(MergeRouletteCurrentTour(3))advance(9,"TOUR attack pressed");}
 else if(phase==9&&MergeRouletteCurrentTour(4)){advance(10,"TOUR final reward");}
 else if(phase==10&&wait>5.5){if(MergeRouletteCurrentTour(5))advance(11,"TOUR reward confirmed, back in lobby");}
 else if(phase==11&&wait>2){advance(12,"DONE current version tour");}
 if(std::chrono::duration<double>(now-began).count()>58&&phase<12){CastleReviewTrace("FAIL tour exceeded 58 seconds");phase=12;}
 return true;
}
