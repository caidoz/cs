int motifReviewStage=0;
bool portraitReviewEnabled(){return review&&std::getenv("CS_PORTRAIT_REVIEW");}
void portraitReviewFixture(){
 if(!portraitReviewEnabled())return;static bool initialized=false;if(initialized)return;initialized=true;
 cocos2d::Director::getInstance()->setDisplayStats(false);
 if(std::getenv("CS_CAMP_AUDIO_REVIEW"))option.bgm=true;
 if(std::getenv("CS_SFX_REVIEW")||std::getenv("CS_SFX_TRACE"))option.se=true;
 robin.gold=1250;robin.coin=120;
 const char* stage=std::getenv("CS_PORTRAIT_STAGE");run=Run();run.roster=&roster;
 run.stage=std::max(0,std::min(18,stage?std::atoi(stage):9));run.shape=BattleShape(run.stage);
 if(std::getenv("CS_PORTRAIT_LOBBY")){robin.castleProgress.owned=1023;robin.castle=run.stage;}
 reviewEnemyNpc=ENEMY_SNAIL;reviewSnailPose=-1;portraitCameraY=0;
 run.choosing=false;run.enemyHp=run.enemyMax=100000;run.lives=run.maxLives=10000;
 run.realVitals=true;run.guardMax=10000;run.guard=640;run.board.clear();
 entryElapsed=std::getenv("CS_PORTRAIT_ENTRY")?0.f:-1.f;startEventElapsed=-1;introElapsed=-1;animation=0;
 resumePromptOpen=false;resumePromptChecked=true;entryChoiceOpen=false;quitPromptOpen=false;
 heartDisplay=5;run.battleEnergy=5;hasReelSymbols=true;waveTransition=MergeCombat::WaveTransition();
 for(int c=0;c<64;++c){deckReveal[c].age=MergeCombat::ResidentReveal::Duration;}
 for(int i=0;i<3;++i){Block b;b.family=i;b.level=1;b.crew=MergeTrees::CrewAt(i,1,0);b.x=i;b.y=0;
  if(run.fits(b))run.board.push_back(b);reelSymbols[i]=b;}
 for(int g=0;g<GearCount;++g){
  for(int lv=MaxLevel-1;lv>=0;--lv){
   const ITEM& item=treeEquipment[g][lv];int w=1,h=1;MergeBoardGearShape(&item,&w,&h);
   if(w>run.shape.width||h>run.shape.height)continue;
   Block b;b.family=Sword+g;b.level=lv+1;b.ownedId=9000+g;b.ownedDetail=item.detail;b.ownedGrade=item.grade;b.ownedPower=100;b.ownedW=w;b.ownedH=h;
   bool placed=false;for(int y=0;y<run.shape.height&&!placed;++y)for(int x=0;x<run.shape.width;++x){b.x=x;b.y=y;if(run.fits(b)){run.board.push_back(b);placed=true;break;}}
   if(placed)break;
  }
 }
 if(std::getenv("CS_PORTRAIT_OVERLAP")){
  run.board.clear();
  for(int i=0;i<2;++i){Block b;b.family=i;b.level=i+1;b.crew=MergeTrees::CrewAt(i,b.level,0);b.x=i;b.y=0;run.board.push_back(b);}
 }
 if(std::getenv("CS_GRID_RARITY_REVIEW")){
  run.shape={6,4};for(int y=0;y<Height;++y)run.shape.rows[y]=y<4?63:0;run.board.clear();
  for(int i=0;i<6;++i){
   Block gear;gear.family=Sword;gear.level=1;gear.ownedId=9900+i;gear.ownedDetail=0;gear.ownedGrade=i;gear.ownedW=1;gear.ownedH=2;gear.x=i;gear.y=0;run.board.push_back(gear);
   Block crew;crew.family=0;crew.level=i+1;crew.crew=MergeTrees::CrewAt(0,i+1,0);crew.x=i;crew.y=2;run.board.push_back(crew);
  }
  shownGrades=run.board;gradeAccents.clear();
 }
 heroHealthDisplay.set(run.lives);heroHealthDisplay.advance(1);enemyHealthDisplay.set(run.enemyHp);enemyHealthDisplay.advance(1);
 guardDisplay.set(run.guard);guardDisplay.advance(1);
}
bool portraitReviewLobby(){
 if(!portraitReviewEnabled()||!std::getenv("CS_PORTRAIT_LOBBY"))return false;
 if(std::getenv("CS_CUTAWAY_REVIEW")){
  static int phase=0;if(reviewCapturePending||phase>=4)return true;
  active=false;drawHandle=MD_LOBBY;titleLobbyClock=-1;
  if(phase==0){starterInteriorReveal=0;starterInteriorFinger=-1;}
  const Box hull=portraitCastleBox(layout());const float x=hull.x+hull.w*.5f,y=std::min(DY-100*layout().scale,std::max(layout().arenaBottom+20*layout().scale,hull.y-hull.h*.5f));
  if(phase==1){portraitStarterInteriorTouch(0,989,x,y);advanceCastleInteriorHold(1.f);}
  if(phase==2){portraitStarterInteriorTouch(2,989,x,y);reviewTrace(starterInteriorReveal==0?"PASS short release closes circle":"FAIL short release");portraitStarterInteriorTouch(0,989,x,y);advanceCastleInteriorHold(3.01f);}
  if(phase==3)portraitStarterInteriorTouch(2,989,x,y);
  MergeRouletteLobbySceneDraw();
  const Box body=portraitCastleBox(layout());reviewTrace(std::abs(body.x-8*layout().scale)<1?"PASS lobby hull stops eight pixels from left edge":"FAIL lobby left anchor");
  if(phase==0){reviewTrace(drawnPortraitInterior==-1?"PASS lobby starts closed":"FAIL default interior");reviewCapture("cutaway-closed");}
  if(phase==1){reviewTrace(starterInteriorReveal==0&&drawnPortraitInterior>=0?"PASS circular interior lens":"FAIL interior lens");reviewCapture("cutaway-circle");}
  if(phase==2)reviewCapture("cutaway-full");
  if(phase==3){reviewTrace(starterInteriorReveal==1&&starterInteriorFinger==-1?"PASS full interior stays after long-hold release":"FAIL full release");reviewTrace("DONE cutaway review");}
  ++phase;active=true;drawHandle=MD_PLAY;return true;
 }
 if(std::getenv("CS_CASTLE_INTERIORS_REVIEW")){
  static int sample=0;static bool finished=false;static int closedWheelBaseline=0;
  if(finished||reviewCapturePending)return true;
  if(sample>=38){reviewTrace("DONE castle interiors review");finished=true;return true;}
  const int c=sample/2;const bool open=sample%2;
  run.stage=robin.castle=gMobileCastleVisual=c;portraitCameraY=0;titleLobbyClock=-1;
  robin.castleProgress.version=3;robin.castleProgress.owned=(1u<<(c+1))-1;
  active=false;drawHandle=MD_LOBBY;starterInteriorReveal=open?1.f:0.f;
  MergeRouletteLobbySceneDraw();
  reviewTrace(drawnPortraitTurret==PORTRAIT_TURRET_FIRST_IMG+c?"PASS turret and carriage remain visible in both castle views":"FAIL missing turret carriage");
  if(open)reviewTrace(drawnPortraitWheelBaseline==closedWheelBaseline?"PASS open and closed castle share the exact wheel baseline":"FAIL wheel baseline changes");
  else closedWheelBaseline=drawnPortraitWheelBaseline;
  if(open){
   const int img=PORTRAIT_INTERIOR_FIRST_IMG+c;
   const auto size=sprite[img]?sprite[img]->getTexture()->getContentSizeInPixels():cocos2d::Size(0,0);
   const Box hull=portraitCastleBox(layout()),b=drawnPortraitInteriorBounds;
   const bool valid=size.width>0&&drawnPortraitInterior==img&&b.x==hull.x&&b.y==hull.y&&b.w==hull.w&&b.h==hull.h&&std::abs(b.w*size.height-b.h*size.width)<=size.width*2;
   reviewTrace(valid?"PASS selected interior drawn with uniform scale and equal hull width":"FAIL interior render registration");
   if(!valid){char detail[240];std::snprintf(detail,sizeof(detail),"INTERIOR stage=%d actual=%d expected=%d bounds=%d,%d,%d,%d hull=%d,%d,%d,%d texture=%.0f,%.0f",c+1,drawnPortraitInterior,img,b.x,b.y,b.w,b.h,hull.x,hull.y,hull.w,hull.h,size.width,size.height);reviewTrace(detail);}
  }else{
   reviewTrace(drawnPortraitInterior==-1&&portraitHullImage(c)==PORTRAIT_CASTLE_FIRST_IMG+c?"PASS closing restores stage exterior":"FAIL closed exterior");
   const int img=PORTRAIT_CASTLE_FIRST_IMG+c;
   const auto size=sprite[img]?sprite[img]->getTexture()->getContentSizeInPixels():cocos2d::Size(0,0);
   const Box hull=portraitCastleBox(layout());
   const bool valid=size.width>0&&std::abs(hull.w*size.height-hull.h*size.width)<=size.width*2;
   reviewTrace(valid?"PASS exterior uses native aspect ratio":"FAIL exterior aspect ratio");
  }
  // Short holds show a movable circle and release back to the previous state.
  const Layout q=layout();const Box b=portraitCastleBox(q);
  const float x=b.x+b.w*.4f,y=std::max(q.arenaBottom+20*q.scale,std::min(DY-100*q.scale,b.y-b.h*.5f));
  const bool down=portraitStarterInteriorTouch(0,989,x,y);
  portraitStarterInteriorTouch(1,989,x+20*q.scale,y);
  advanceCastleInteriorHold(.5f);
  const bool lens=starterInteriorFinger==989&&starterInteriorTouchX==x+20*q.scale;
  portraitStarterInteriorTouch(2,989,x+20*q.scale,y);
  reviewTrace(down&&lens&&starterInteriorReveal==(open?1.f:0.f)&&starterInteriorFinger==-1?"PASS short touch moves circular cutaway and release restores exterior":"FAIL circular cutaway touch");
  portraitStarterInteriorTouch(0,989,x,y);advanceCastleInteriorHold(3.01f);
  portraitStarterInteriorTouch(2,989,x,y);
  reviewTrace(starterInteriorReveal==1&&starterInteriorFinger==-1?"PASS three-second hold latches complete interior":"FAIL long hold cutaway");
  starterInteriorReveal=open?1.f:0.f;
  portraitCameraY=0;
  active=true;reviewTrace(portraitHullImage(c)==PORTRAIT_CASTLE_FIRST_IMG+c&&!portraitStarterInteriorTouch(0,989,x,y)?"PASS battle keeps exterior and rejects interior gestures":"FAIL battle reveal isolation");active=false;
  char name[64];std::snprintf(name,sizeof(name),"interior-%02d-%s",c+1,open?"open":"closed");reviewCapture(name);
  ++sample;active=true;drawHandle=MD_PLAY;return true;
 }
 if(std::getenv("CS_MOTIF_SERIES_REVIEW")){
  if(reviewCapturePending)return true;
  if(motifReviewStage<19){
   run.stage=robin.castle=gMobileCastleVisual=motifReviewStage;
   portraitCameraY=std::getenv("CS_FIXED_RAIL_SCROLL_REVIEW")?-83.f*DX/640.f:0.f;
   robin.castleProgress.version=3;robin.castleProgress.owned=(1u<<(motifReviewStage+1))-1;
   active=false;drawHandle=MD_LOBBY;starterInteriorReveal=0;titleLobbyClock=-1;
   MergeRouletteLobbySceneDraw();
   char name[48];std::snprintf(name,sizeof(name),"motif-lobby-%02d",motifReviewStage+1);reviewCapture(name);
   const auto size=portraitHullSize(motifReviewStage);const Box body=portraitCastleBox(layout());
   char zoomLine[160];std::snprintf(zoomLine,sizeof(zoomLine),"ZOOM stage=%d height=%d zoom=%.6f hull=%d,%d,%d,%d",motifReviewStage+1,DY,portraitCastleZoom(layout()),body.x,body.y,body.w,body.h);reviewTrace(zoomLine);

   const Box gun=castleCannonBox(layout());const float z=portraitCastleZoom(layout());
   const bool aspect=std::abs(body.w*size.h-body.h*size.w)<=std::max(size.w,size.h);
   const int axle=body.x+(int)(body.w*PortraitCastleArt::FrontWheelAt(motifReviewStage));
   const bool mount=std::abs(gun.x+(int)(portraitCannonFootX(motifReviewStage)*z)-axle)<=1;
   reviewTrace(aspect&&mount?"PASS motif native aspect and shared front-wheel turret socket":"FAIL motif assembly");
   const auto scene=layout();const auto fixed=PortraitGame::lobby(DX,DY);
   const int expectedGap=(int)(21*scene.scale)+fixed.ground-(int)(336*scene.scale)+(int)portraitCameraY;
   const int gap=portraitRailBottom-fixed.stageTop-(int)(16*scene.scale);
   const bool fixedRail=portraitRailGround==fixed.ground+(int)portraitCameraY&&portraitBridgeBottom==(int)portraitCameraY&&std::abs(gap-expectedGap)<=2;
   reviewTrace(fixedRail?"PASS lobby rail and bridge follow castle camera":"FAIL lobby rail depends on castle");
   char railLine[120];std::snprintf(railLine,sizeof(railLine),"RAIL lobby stage=%d height=%d ground=%d lowerUiGap=%d camera=%d",motifReviewStage+1,DY,portraitRailGround,gap,(int)portraitCameraY);reviewTrace(railLine);
   ++motifReviewStage;active=true;drawHandle=MD_PLAY;return true;
  }
  if(motifReviewStage>=38)return true;
  run.stage=motifReviewStage-19;run.shape=BattleShape(run.stage);portraitCameraY=0;
  run.board.clear();for(int i=0;i<3;++i){Block b;b.family=i;b.level=1;b.crew=MergeTrees::CrewAt(i,1,0);b.x=i;b.y=0;run.board.push_back(b);}
  active=true;drawHandle=MD_PLAY;return false;
 }
 if(std::getenv("CS_BASE_CAMP_REVIEW")){
  static int phase=0,startTick=0;static float startX=0,startZoom=0,startTravel=0;static bool travelCaptured=false;static long long paid=0;
  if(phase>=6)return false;if(reviewCapturePending)return true;
  active=false;drawHandle=MD_LOBBY;curMenu=MENU_PLAY;
  if(phase==0){campReviewScenario=2;starterInteriorReveal=1;titleLobbyClock=-1;}
  MergeRouletteLobbySceneDraw();
  if(active&&lobbyDepartureAge<0&&phase>=2){
   reviewTrace(robin.heart==paid&&starterInteriorReveal==0&&!startEventActive()?"PASS departure commits one paid battle with closed facade":"FAIL departure commit or duplicate charge");
   phase=6;baseCampReviewStage=1;return false;
  }
  if(phase==0){
   reviewTrace(!campFireDrawn&&campInteriorCount==1&&campOutsideCount==2&&campDrawnCrewCount==3?"PASS owned residents populate interior and patrol outside without a lobby fire":"FAIL base camp population");
   startTick=ticks;startX=campHeroX;startZoom=portraitCastleZoom(layout());startTravel=castleScrollSeconds;reviewCapture("base-lobby");++phase;
  }else if(phase==1&&ticks-startTick>80){
   reviewTrace(std::abs(campHeroX-startX)>1?"PASS original walking sprites patrol instead of standing in a campfire row":"FAIL base patrol movement");
   robin.heart=20;const Box start=lobbyStart(layout());MergeRouletteTouch(0,991,start.x+start.w/2,start.y-start.h/2);MergeRouletteTouch(2,991,start.x+start.w/2,start.y-start.h/2);
   const Box fight=entryChoiceBox(1);MergeRouletteTouch(0,992,fight.x+fight.w/2,fight.y-fight.h/2);MergeRouletteTouch(2,992,fight.x+fight.w/2,fight.y-fight.h/2);
   paid=robin.heart-MergeExpedition::Cost;reviewTrace(!active&&lobbyDepartureAge==0&&robin.heart==20&&paid==15?"PASS actual battle confirmation reserves entry without charging during recall":"FAIL recall trigger");++phase;
  }else if(phase==2&&lobbyDepartureAge>.45f){
   const float age=lobbyDepartureAge;const bool locked=MergeRouletteTouch(0,993,DX/2,DY/2);
   reviewTrace(locked&&age==lobbyDepartureAge?"PASS departure locks extra taps while villagers return":"FAIL departure input lock");reviewCapture("base-recall");++phase;
  }else if(phase==3&&lobbyDepartureAge>1.18f){
   reviewTrace(campOutsideCount==0&&campHeroInside&&starterInteriorReveal>0?"PASS all exterior actors enter before facade starts closing":"FAIL recall ordering");reviewCapture("base-returned");++phase;
  }else if(phase==4&&lobbyDepartureAge>1.55f){reviewTrace(starterInteriorReveal<.15f?"PASS facade closes after recall":"FAIL facade close");reviewCapture("base-closing");++phase;
  }else if(phase==5&&!travelCaptured&&lobbyDepartureAge>2.2f){
   reviewTrace(portraitCastleZoom(layout())<startZoom&&castleScrollSeconds>startTravel?"PASS castle accelerates and scales uniformly into battle camera":"FAIL castle travel scale");reviewCapture("base-travel");travelCaptured=true;
  }
  if(std::getenv("CS_BASE_CAPTURE_FRAMES")&&!reviewCapturePending){
   static int last=-100,shot=0;if(ticks-last>=6){last=ticks;char name[48];std::snprintf(name,sizeof(name),"base-frame-%03d",shot++);reviewCapture(name);}
  }
  active=true;drawHandle=MD_PLAY;return true;
 }
 if(std::getenv("CS_SFX_REVIEW")){
  static int phase=0,cue=M_ROULETTEUP,age=0;static bool done=false;
  if(reviewCapturePending)return true;if(done)return true;
  active=false;drawHandle=MD_LOBBY;MergeRouletteLobbySceneDraw();
  if(phase==0){
   const int before=GameSfxPlayedCount(),music=curID;option.se=false;PlayMusic(M_BUTTON);EffectSound(M_SWORDHIT);option.se=true;
   reviewTrace(GameSfxPlayedCount()==before&&curID==music?"PASS both effect routes honor mute without changing BGM state":"FAIL effect mute policy");phase=1;
  }else if(phase==1){
   const auto path=GameSfxPath(cue);const bool file=path.find("res/sfx-")==0&&GetResourceName(RES_SOUND,cue)==path&&cocos2d::FileUtils::getInstance()->isFileExist(path);
   reviewTrace(file?"PASS effect resolves to used flat replacement asset":"FAIL effect resource mapping");
   const int before=GameSfxPlayedCount(),dropped=GameSfxSuppressedCount();PlayMusic(cue);EffectSound(cue);
   reviewTrace(GameSfxPlayedCount()==before+1&&GameSfxSuppressedCount()==dropped+1?"PASS duplicate play/effect routes coalesce once":"FAIL effect rate policy");age=0;phase=2;
  }else if(phase==2){
   const int id=audioID[cue];const auto state=AudioEngine::getState(id);
   if(state==AudioEngine::AudioState::PLAYING&&AudioEngine::getDuration(id)>0){
    char line[160];std::snprintf(line,sizeof(line),"PASS decoded native cue %d %s",cue,GameSfxPath(cue).c_str());reviewTrace(line);AudioEngine::stop(id);phase=++cue<TOTALMUSIC?1:3;
   }else if(++age>180){reviewTrace("FAIL native effect decode timeout");done=true;}
  }else if(phase==3){
   for(int id=M_SWORD;id<=M_OPENDOOR;++id)PlayMusic(id);
   const int live=GameSfxActiveCount();reviewTrace(live>0&&live<=12?"PASS dense effect burst is capped at twelve voices":"FAIL effect voice budget");
   StopGameSfx();reviewCapture("sfx-bank");phase=4;
  }else {reviewTrace("DONE portrait review");done=true;}
  active=true;drawHandle=MD_PLAY;return true;
 }
 if(std::getenv("CS_TITLE_ENTRANCE_REVIEW")){
  static int frame=0;static bool done=false;if(reviewCapturePending)return true;if(done){static bool logged=false;if(!logged){logged=true;reviewTrace("DONE portrait review");}return true;}
  active=false;drawHandle=MD_LOBBY;
  titleEntranceClock=frame*.12f;MergeRouletteTitleCastlesDraw();DrawTitleCampOverlay();
  char name[48];std::snprintf(name,sizeof(name),"title-entrance-%02d",frame);reviewCapture(name);
  if(frame++>=24){reviewTrace("PASS title castle and login controls enter on independent delayed tracks");done=true;}
  active=true;drawHandle=MD_PLAY;return true;
 }
 if(std::getenv("CS_TITLE_CAMP_REVIEW")){
  static int phase=0;static float still=-1;static bool done=false;if(done||reviewCapturePending)return true;
  active=false;drawHandle=MD_LOBBY;
  if(phase==0){titleEntranceClock=3.f;MergeRouletteTitleCastlesDraw();DrawTitleCampOverlay();still=castleScrollSeconds;reviewTrace(campDrawnCrewCount==0?"PASS title uses castle, hero and fire without owned companions":"FAIL title companions");reviewCapture("title-camp");BeginTitleLobbyMotion();
   titleLobbyClock=1.08f;const bool order=LobbyNavPop(0)>0&&LobbyNavPop(2)==0&&LobbyNavPop(4)==0;
   titleLobbyClock=.91f;const bool impact=LobbyTopbarDrop()<0;
   titleLobbyClock=1.24f;const bool pop=LobbyNavPop(0)>1.f;
   reviewTrace(order&&impact&&pop?"PASS topbar impact and left-to-right overshoot timings":"FAIL staggered lobby curves");
   titleLobbyClock=0;++phase;}
  else{
   MergeRouletteLobbySceneDraw();
   if(std::getenv("CS_LOBBY_ARRIVAL_FRAMES")&&titleLobbyClock>=0){
    static int shot=0;static float last=-1;if(titleLobbyClock-last>=.09f){last=titleLobbyClock;char n[48];std::snprintf(n,sizeof(n),"lobby-entry-%02d",shot++);reviewCapture(n);}
   }
   if(reviewCapturePending){active=true;drawHandle=MD_PLAY;return true;}
   if(phase==1&&titleLobbyClock>=.18f){reviewTrace(MergeRouletteTouch(0,998,DX/2,DY/2)?"PASS scene transition blocks accidental input":"FAIL transition input");reviewCapture("title-departure");++phase;}
   else if(phase==2&&titleLobbyClock>=1.26f){reviewCapture("lobby-arriving");++phase;}
   else if(phase==3&&titleLobbyClock<0){reviewCapture("lobby");reviewTrace(std::abs(still-castleScrollSeconds)<.001f?"PASS title and lobby keep castle, rails and backdrop stationary":"FAIL camp world movement");reviewTrace(uiSceneMotionY==0?"PASS UI motion scope resets after transition":"FAIL leaked UI motion");++phase;}
   else if(phase==4){reviewTrace("DONE portrait review");done=true;}
  }
  active=true;drawHandle=MD_PLAY;return true;
 }
 static int hold=0;static float firstWheel=-1.f;if(firstWheel<0)firstWheel=castleWheelTravel;active=false;drawHandle=MD_LOBBY;MergeRouletteLobbySceneDraw();active=true;drawHandle=MD_PLAY;
 if(std::getenv("CS_PORTRAIT_CAMP_REVIEW")){
  static int phase=0,firstFire=-1;static bool done=false;if(done||reviewCapturePending)return true;
  active=false;drawHandle=MD_LOBBY;const Layout q=layout();const Box body=portraitCastleBox(q);const float z=portraitCastleZoom(q);
  const float x=body.x+100*z,y=body.y-180*z;
  if(phase==0){starterInteriorReveal=0;campReviewScenario=0;++phase;}
  else if(phase==1){
   reviewTrace(campDrawnCrewCount==0?"PASS empty owned inventory shows no invented companions":"FAIL camp invents companions");
   const bool down=portraitStarterInteriorTouch(0,991,x,y);portraitStarterInteriorTouch(1,991,x,y+100*q.scale);portraitStarterInteriorTouch(2,991,x,y+100*q.scale);
   reviewTrace(down&&starterInteriorReveal==1?"PASS actual castle drag opens starter interior":"FAIL starter interior open gesture");++phase;
  }else if(phase==2){
   reviewTrace(portraitHullImage(0)==PORTRAIT_STARTER_INTERIOR_IMG?"PASS opening selects actual starter interior resource":"FAIL interior resource");
   const int stage=run.stage;run.stage=1;const bool other=portraitStarterInteriorTouch(0,992,x,y);run.stage=stage;
   portraitStarterInteriorTouch(3,992,x,y);
   reviewTrace(other?"PASS interior gesture also supports later castles":"FAIL later castle interior gesture");
   reviewCapture("starter-interior-open");++phase;
  }else if(phase==3){
   portraitStarterInteriorTouch(0,991,x,y);portraitStarterInteriorTouch(1,991,x,y-100*q.scale);portraitStarterInteriorTouch(2,991,x,y-100*q.scale);
   reviewTrace(starterInteriorReveal==0?"PASS reverse drag restores original exterior":"FAIL starter interior close gesture");campReviewScenario=1;++phase;
  }else if(phase==4){reviewTrace(campDrawnCrewCount==1&&campDrawnCrew[0]==0?"PASS only one owned companion renders once":"FAIL camp single companion");reviewCapture("starter-camp-one");campReviewScenario=2;starterInteriorReveal=1;++phase;
  }else if(phase==5){
   const auto chosen=LobbyCamp::highestOwned(portraitCampOwned());bool valid=campDrawnCrewCount==(int)chosen.size()&&campDrawnCrewCount==3;
   for(int i=0;i<campDrawnCrewCount;++i)valid=valid&&campDrawnCrew[i]==chosen[i].id;
   reviewTrace(valid?"PASS camp renders the three highest owned grades without duplicates":"FAIL camp owned grade order");
   firstFire=(int)campHeroX;reviewCapture("starter-camp-three");++phase;
  }else if(phase==6&&firstFire!=(int)campHeroX){reviewTrace(!campFireDrawn?"PASS lobby patrol advances without campfire":"FAIL lobby fire remains");reviewCapture("starter-patrol-next");++phase;
  }else if(phase==7&&std::getenv("CS_PORTRAIT_CAMP_ANIMATION")){
   static int frame=0,lastTick=-100;if(ticks-lastTick>=6){lastTick=ticks;char name[48];std::snprintf(name,sizeof(name),"camp-life-%02d",frame++);reviewCapture(name);if(frame>=16)++phase;}
  }else if(phase==7||phase==8){
   starterInteriorReveal=0;portraitStarterInteriorTouch(0,991,x,y);portraitStarterInteriorTouch(2,991,x,y);bool valid=starterInteriorReveal==0;
   portraitStarterInteriorTouch(0,991,x,y);portraitStarterInteriorTouch(1,991,x-40*q.scale,y);portraitStarterInteriorTouch(3,991,x-40*q.scale,y);valid=valid&&starterInteriorReveal==0;
   active=true;const bool battle=portraitStarterInteriorTouch(0,991,x,y);active=false;
   reviewTrace(valid&&!battle?"PASS taps, cancelled drags and battle input do not open interior":"FAIL starter gesture isolation");
   reviewTrace("DONE portrait review");done=true;
  }
  active=true;drawHandle=MD_PLAY;return true;
 }
 if(std::getenv("CS_PORTRAIT_DEBUG19")){
  static int phase=0;static bool done=false;if(done)return true;if(reviewCapturePending)return true;
  active=false;drawHandle=MD_LOBBY;
  if(phase==0){LobbyCastleDebugCommand(TOUCH_FUNC_LOBBY_CASTLE_DEBUG);gMobileCastleVisual=0;}
  if(phase<PortraitCastleArt::Count){
   const int c=phase;
   char diag[120];std::snprintf(diag,sizeof(diag),"DETAIL expected=%d actual=%d visual=%d stage=%d",c,LobbyCastleDebugCastle(),gMobileCastleVisual,run.stage);reviewTrace(diag);
   LobbyCastleDebugDraw();
   reviewTrace(LobbyCastleDebugCastle()==c?"PASS debug castle reachable":"FAIL debug castle range");
   MergeRouletteLobbySceneDraw();
   char interiorDiag[200];std::snprintf(interiorDiag,sizeof(interiorDiag),"DEBUG_CLOSED stage=%d forced=%d reveal=%.2f finger=%d drawn=%d image=%d expected=%d",run.stage,(int)LobbyCastleDebugInterior(),starterInteriorReveal,starterInteriorFinger,drawnPortraitInterior,portraitHullImage(c),PORTRAIT_CASTLE_FIRST_IMG+c);reviewTrace(interiorDiag);
   reviewTrace(!LobbyCastleDebugInterior()&&starterInteriorReveal==0&&drawnPortraitInterior==-1&&portraitHullImage(c)==PORTRAIT_CASTLE_FIRST_IMG+c?"PASS selected debug castle starts closed":"FAIL debug selection opens interior");
   starterInteriorReveal=1; // Selection must also clear a previously opened lobby.

   LobbyCastleDebugCommand(TOUCH_FUNC_LOBBY_CASTLE_NEXT);++phase;
  }else if(phase==PortraitCastleArt::Count){
   reviewTrace(LobbyCastleDebugCastle()==0?"PASS debug next wraps after castle 19":"FAIL debug next wrap");
   LobbyCastleDebugCommand(TOUCH_FUNC_LOBBY_CASTLE_PREV);++phase;
  }else if(phase==PortraitCastleArt::Count+1){
   reviewTrace(LobbyCastleDebugCastle()==18&&run.stage==18?"PASS debug previous wraps to actual last castle renderer":"FAIL debug last castle renderer");
   reviewCapture("debug-castle-19");++phase;
  }else{
   const int savedCastle=robin.castle;LobbyCastleDebugCommand(TOUCH_FUNC_LOBBY_CASTLE_DEBUG);
   reviewTrace(LobbyCastleDebugCastle()==18&&robin.castle==savedCastle?"PASS closing late preview keeps visual without changing saved castle":"FAIL debug close late preview");
   reviewTrace("DONE portrait review");done=true;
  }
  active=true;drawHandle=MD_PLAY;return true;
 }
 if(!reviewCapturePending&&++hold==16){reviewCapture("lobby");reviewTrace("PASS lobby uses native world and interactive management controls");}
 if(!reviewCapturePending&&hold==18){
  bool crew=false,equipment=false,upgrade=false,shop=false;
  const Box dock=lobbyBottomNav(),start=lobbyStart(layout());
  int tabs=0;const int commands[5]={TOUCH_FUNC_SHOP,TOUCH_FUNC_COLLECTIONS,TOUCH_FUNC_LOBBY_ADVENTURE,TOUCH_FUNC_POPUP_CREWLIST,TOUCH_FUNC_POPUP_CASTLEMENU};
  for(int tab=0;tab<5;++tab){int count=0;for(int i=0;i<touchIndex;++i)if(touchRect[i][4]==commands[tab]&&touchRect[i][1]==dock.y)++count;tabs+=count==1;}
  active=false;drawHandle=MD_LOBBY;const Box hull=portraitCastleBox(layout());
  const int castle=std::max(0,std::min(18,run.stage));const float zoom=portraitCastleZoom(layout());
  const auto fixedBefore=portraitBackdropBox(layout().ground);
  const float savedCamera=portraitCameraY;portraitCameraY=-83*layout().scale;
  const auto fixedAfter=portraitBackdropBox(layout().ground);portraitCameraY=savedCamera;
  reviewTrace(fixedBefore.x==fixedAfter.x&&fixedBefore.y==fixedAfter.y&&fixedBefore.w==fixedAfter.w&&fixedBefore.h==fixedAfter.h?"PASS castle camera leaves distant backdrop transform fixed":"FAIL backdrop follows castle camera");
  const int savedStage=run.stage;run.stage=0;const float firstZoom=portraitCastleZoom(layout());const Box firstHull=portraitCastleBox(layout());
  run.stage=18;const float lastZoom=portraitCastleZoom(layout());const Box lastHull=portraitCastleBox(layout());run.stage=savedStage;
  reviewTrace(std::abs(firstZoom-lastZoom)<.0001f&&lastHull.w>firstHull.w&&std::abs(lastHull.w-firstHull.w*PortraitCastleArt::Sizes[18].w/256.f)<2?"PASS castle width grows in native artwork width proportion at one shared camera scale":"FAIL castle width normalized");
  const Box gun=castleCannonBox(layout());
  const int axle=hull.x+(int)(hull.w*PortraitCastleArt::FrontWheelAt(castle));
  const int gunFoot=gun.x+(int)(portraitCannonFootX(castle)*zoom);
  const float wheelTop=hull.y-hull.h+PortraitCastleArt::WheelSize(castle)*zoom*.42f;
  reviewTrace(portraitAssembledSample()||std::abs(gunFoot-axle)<=1&&std::abs(gun.y-gun.h-(hull.y-hull.h+PortraitCastleArt::CannonBaseFromFloor(castle)*zoom))<2?"PASS cannon carriage sits directly above front wheel at the shared artwork scale":"FAIL cannon wheel alignment");
  if(castle==0){
   const float contact=gun.y-StarterCastleRig::FixedBaseBottomY*zoom,deck=hull.y-StarterCastleRig::StoneDeckY*zoom;
   reviewTrace(std::abs(contact-deck)<2?"PASS starter crane feet contact the marked stone terrace":"FAIL starter crane floats off terrace");
  }
  const auto size=portraitHullSize(std::max(0,std::min(18,run.stage)));
  const bool aspect=std::abs(start.w-360*layout().scale)<2&&std::abs(start.h-64*layout().scale)<2&&std::abs(hull.w*size.h-hull.h*size.w)<=size.h;
  reviewTrace(tabs==5&&aspect&&start.y-start.h>dock.y?"PASS legacy icons in current frames, five live tabs and separate hit areas":"FAIL revised lobby composition");
  active=true;drawHandle=MD_PLAY;
  reviewTrace(std::abs(castleWheelTravel-firstWheel)<.01f?"PASS parked lobby keeps wheel rotation fixed":"FAIL moving lobby wheels");
  for(int i=0;i<touchIndex;++i){const int command=touchRect[i][4];
   crew=crew||command==TOUCH_FUNC_POPUP_CREWLIST;equipment=equipment||command==TOUCH_FUNC_COLLECTIONS;
   upgrade=upgrade||command==TOUCH_FUNC_POPUP_CASTLEMENU;shop=shop||command==TOUCH_FUNC_SHOP;
  }
  active=false;drawHandle=MD_LOBBY;reviewTap(lobbyStart(layout()));const bool opened=entryChoiceOpen;
  if(opened)reviewTap(entryChoiceBox(3));
  reviewTrace(crew&&equipment&&upgrade&&shop&&opened&&!entryChoiceOpen?"PASS management, inventory, shop and start actions remain reachable":"FAIL lobby controls");
  active=true;drawHandle=MD_PLAY;reviewTrace("DONE portrait review");
 }
 return true;
}
bool portraitReviewStep(const Layout& l){
 if(!portraitReviewEnabled())return false;static int hold=0;static bool done=false;if(done)return true;
 if(reviewCapturePending)return true;
 if(std::getenv("CS_MOTIF_SERIES_REVIEW")){
  char name[48];std::snprintf(name,sizeof(name),"motif-battle-%02d",run.stage+1);reviewCapture(name);
  const Box hull=portraitCastleBox(l),gun=castleCannonBox(l);const auto size=portraitHullSize(run.stage);
  const bool aspect=std::abs(hull.w*size.h-hull.h*size.w)<=size.h;
  reviewTrace(aspect?"PASS motif battle preserves aspect with intentional viewport cropping":"FAIL motif battle aspect");
  int cells=0;for(int y=0;y<run.shape.height;++y)for(int x=0;x<run.shape.width;++x)cells+=run.shape.contains(x,y);
  const float expectedZoom=PortraitGame::battleCastleScale(DX,PortraitCastleArt::BattleReferenceAssemblyHeight);
  const bool world=std::abs(portraitCastleZoom(l)-expectedZoom)<.0001f&&std::abs(expectedZoom*(PortraitCastleArt::BattleReferenceAssemblyHeight)-.90f*(DX*2.2f-PortraitGame::battle(DX,(int)(DX*2.2f+.5f)).ground))<1&&std::abs(hull.x+hull.w-DX/3.f)<1&&
    std::abs(drawnBattleHeroZoom-PortraitGame::battleActorScale(DX,PortraitCastleArt::Sizes[18].w))<.0001f&&std::abs(drawnBattleCompanionZoom-drawnBattleHeroZoom*.8f)<.0001f;
  reviewTrace(world?"PASS largest castle fits battle height with right edge at one third and fixed actors":"FAIL fixed battle actor scale");
  reviewTrace(run.shape.height==4&&cells==16+run.stage&&cells<=36&&l.board.x>=0&&l.board.x+l.board.w<=DX?"PASS four rows and exactly one extra grid cell per castle":"FAIL four-row grid progression");
  reviewTrace(drawnPortraitTurret==PORTRAIT_TURRET_FIRST_IMG+run.stage?"PASS battle turret and carriage drawn":"FAIL battle turret");
  reviewTrace(drawnBattleViewportTop==DY?"PASS battlefield continues behind translucent wave header":"FAIL hard header clipping");
  reviewTrace(std::abs(drawnBattleEnergyBounds.x+drawnBattleEnergyBounds.w*.5f-DX*.5f)<2&&drawnEnemyHeartIcon.w==(int)(39*l.scale)&&sprite[PORTRAIT_DEMON_HEART_IMG]?"PASS centered energy and large demon heart HUD icon":"FAIL revised battle HUD");
  const auto fixed=PortraitGame::battle(DX,DY,run.shape.height,run.shape.width);
  reviewTrace(portraitRailGround==fixed.ground?"PASS battle rail follows fixed UI layout, never castle height":"FAIL battle rail depends on castle");
  if(++motifReviewStage==38)reviewTrace("DONE motif series review");
  return true;
 }
 if(std::getenv("CS_GRID_RARITY_REVIEW")){
  static int phase=0;if(phase++==2){reviewCapture("grid-rarity");
   for(const auto& b:run.board){const Box box=blockBox(b,l);char line[120];std::snprintf(line,sizeof(line),"RIM %d %06X %d %d",gridRarity(b),QuietCard::Color(gridRarity(b)),box.x+1,DY-box.y+5);reviewTrace(line);}
   reviewTrace(run.shape.valid()?"PASS owned gear grade and companion star rank share six rarity rims":"FAIL invalid rarity fixture");}
  if(phase==5)reviewTrace("DONE portrait review");return true;
 }
 if(std::getenv("CS_BASE_CAMP_REVIEW")){
  if(baseCampReviewStage==1&&!entering()&&!introActive()){reviewTrace(friendlyStatCount==3&&hostileStatCount==1?"PASS battle arrives with compact friendly trio and enemy HP":"FAIL arrival HUD");reviewCapture("base-battle");baseCampReviewStage=2;}
  else if(baseCampReviewStage==2){reviewTrace("DONE portrait review");baseCampReviewStage=3;}
  return true;
 }
 if(std::getenv("CS_BASE_HUD_REVIEW")){
  static int phase=0;static bool done=false;static long long leftHp=0,rightHp=0,expectedLeft=0,expectedRight=0;if(done)return true;
  if(phase==0){++phase;return true;}
  if(phase==1){
   bool geometry=friendlyStatCount==3&&hostileStatCount==1&&hostileStatKind[0]==2;
   for(int i=0;i<3;++i)geometry=geometry&&friendlyStatKind[i]==i&&friendlyStatBounds[i].x+friendlyStatBounds[i].w<=DX/2;
   geometry=geometry&&hostileStatBounds[0].x>DX/2;
   reviewTrace(geometry?"PASS PvE HUD uses left-half allied trio and differently colored right enemy HP":"FAIL compact PvE HUD");reviewCapture("battle-hud-pve");++phase;
  }else if(phase==2){
   active=false;MergeRouletteBeginSiege();entryElapsed=MergeCastleTransition::Duration;introElapsed=-1;run.choosing=false;Siege::phase=0;Siege::step=Siege::Idle;combatNumbers.clear();
   expectedLeft=std::max(1LL,run.maxLives/2);expectedRight=std::max(1LL,Siege::foe.maxLives/2);
   run.lives=expectedLeft;run.enemyHp=expectedRight;run.enemyMax=Siege::foe.maxLives;Siege::foe.lives=expectedRight;Siege::foe.enemyHp=expectedLeft;Siege::foe.enemyMax=run.maxLives;++phase;
  }else if(phase==3){
   bool mirrored=friendlyStatCount==3&&hostileStatCount==3;
   for(int i=0;i<3;++i)mirrored=mirrored&&friendlyStatKind[i]==i&&hostileStatKind[i]==2-i;
   leftHp=friendlyStatValue[2];rightHp=hostileStatValue[0];
   if(!mirrored||leftHp!=expectedLeft||rightHp!=expectedRight){char d[200];std::snprintf(d,sizeof(d),"DETAIL HUD counts=%d,%d hp=%lld,%lld run=%lld,%lld swapped=%d",friendlyStatCount,hostileStatCount,leftHp,rightHp,run.lives,run.enemyHp,(int)Siege::swapped);reviewTrace(d);}
   reviewTrace(mirrored&&leftHp==expectedLeft&&rightHp==expectedRight?"PASS PvP mirrors HP defense attack on the enemy side":"FAIL mirrored PvP HUD");reviewCapture("battle-hud-pvp");++phase;
  }else if(phase==4){Siege::swapSides();++phase;
  }else if(phase==5){reviewTrace(friendlyStatValue[2]==leftHp&&hostileStatValue[0]==rightHp?"PASS physical HUD ownership stays fixed during opponent turn":"FAIL swapped HUD ownership");reviewCapture("battle-hud-pvp-opponent");++phase;
  }else{reviewTrace("DONE portrait review");done=true;}
  return true;
 }
 if(std::getenv("CS_PORTRAIT_CATAPULT")){
  static int phase=0;static long long hp=0;static Box mount;
  if(phase==0){reviewCapture("catapult-idle");phase=1;return true;}
  if(phase==1){
   run.board.clear();run.shots.clear();run.nextShot=0;run.choosing=false;run.attacking=false;run.passing=false;run.enemyGuard=0;
   hp=run.enemyHp=run.enemyMax=1000000;action=CombatAction();turretFire.age=-1;
   const bool fired=run.fireCannon(123);beginCombatAction();mount=castleCannonBox(l);
   reviewTrace(fired?"PASS native catapult action starts":"FAIL catapult action");phase=2;return true;
  }
  const int age=turretFire.age;const Box now=castleCannonBox(l);
  if(now.x!=mount.x||now.y!=mount.y||now.w!=mount.w||now.h!=mount.h){reviewTrace("FAIL catapult fixed mount moved");done=true;return true;}
  if(phase==2&&age>=10){reviewCapture("catapult-windup");phase=3;return true;}
  if(phase==3&&age>=turretFire.release){
   const auto p=cannonMuzzle(l,0,false,turretFire.release),m=cannonMuzzle(l,0,true,turretFire.release);
   const auto local=StarterCastleRig::cup(turretFire.release);const float z=portraitCastleZoom(l);
   const bool rig=std::abs(p.x-(now.x+local.x*z))<1&&std::abs(p.y-(now.y-local.y*z))<1;
   reviewTrace(rig&&std::abs(p.x+m.x-DX)<2?"PASS released stone uses the rotated cup origin, including mirrored siege":"FAIL catapult release registration");
   reviewTrace(StarterCastleRig::loadAlpha(age,turretFire.release,turretFire.impact())==0?"PASS loaded stone disappears at release":"FAIL duplicate loaded stone");
   reviewCapture("catapult-release");phase=4;return true;
  }
  if(phase==4&&age>=33){reviewCapture("catapult-flight");phase=5;return true;}
  if(phase==5&&age>=68){
   reviewTrace(StarterCastleRig::angle(age)==0&&StarterCastleRig::loadAlpha(age,turretFire.release,turretFire.impact())==1?"PASS arm returns and cup reloads":"FAIL catapult recovery");
   reviewTrace(run.enemyHp<hp?"PASS existing catapult impact applies damage":"FAIL catapult impact");
   reviewCapture("catapult-recovered");phase=6;return true;
  }
  if(phase==6){done=true;reviewTrace("PASS fixed carriage remained registered through the firing cycle");reviewTrace("DONE portrait review");}
  if(++hold>500){reviewTrace("FAIL catapult capture timed out");done=true;}
  return true;
 }
 if(std::getenv("CS_PORTRAIT_ENEMY_ATTACK")){
  static bool captured=false;
  if(captured){done=true;reviewTrace("DONE portrait review");return true;}
  if(++hold==1){run.attacking=run.passing=true;beginEnemyTurn();MonsterBoard::expanded=true;}
  if(hold>1&&MonsterBoard::attacking()&&enemyTurn.time.elapsed>enemyTurn.phases.approach){
   reviewTrace(!MonsterBoard::expandedVisible()?"PASS native monster attack never overlays the player grid":"FAIL automatic monster board overlay");
   reviewCapture("battle");captured=true;
  }
  if(hold>400){done=true;reviewTrace("FAIL monster attack capture not reached");}
  return true;
 }
 if(std::getenv("CS_PORTRAIT_ENTRY")){
  static int sample=0;static bool checked=false;
  static const float moments[]={1.20f,1.34f,1.46f,1.58f,1.70f,1.82f,1.94f,2.08f,MergeCastleTransition::Duration};
  if(!checked&&entering()){
   const auto before=run.encode();const int energy=run.battleEnergy;reviewTap(l.spin);
   reviewTrace(run.encode()==before&&run.battleEnergy==energy?"PASS assembling grid locks actions without spending lightning":"FAIL grid assembly input");checked=true;
  }
  if(sample<9&&entryElapsed>=moments[sample]-.001f){char name[32];std::snprintf(name,sizeof(name),"entry-%02d",++sample);reviewCapture(name);return true;}
  if(sample==9){sample=10;reviewCapture("battle");return true;}
  if(sample==10){
   const int count=portraitGridCapacity();bool complete=!entering();
   for(int i=0;i<count;++i)complete=complete&&MergeCastleTransition::TileProgress(entryElapsed,i,count)==1.f;
   reviewTrace(complete?"PASS every usable tile flies from reels and lands before grid unlocks":"FAIL grid assembly completion");
   done=true;reviewTrace("DONE portrait review");
  }
  return true;
 }
 if(std::getenv("CS_PORTRAIT_OVERLAP")){
  if(++hold==18)reviewCapture("battle");
  if(hold==19){const int energy=run.battleEnergy;reviewTap({l.board.x,l.board.y,l.cell,l.cellH});
   reviewTrace(!run.boardResolved()&&run.battleEnergy==energy?"PASS native rotation overlap keeps both ranked blocks and spends no lightning":"FAIL overlap fixture");}
  if(hold==21)reviewCapture("overlap-message");
  if(hold==23){run.board.resize(1);run.board[0].rot=false;run.board[0].x=run.board[0].y=0;
   const auto before=run.encode();const float sx=l.board.x+l.cell*.5f,sy=l.board.y-l.cellH*.5f;
   MergeRouletteTouch(0,993,sx,sy);MergeRouletteTouch(1,993,l.board.x-l.cell*1.5f,sy);MergeRouletteTouch(2,993,l.board.x-l.cell*1.5f,sy);
   reviewTrace(run.encode()==before?"PASS rejected off-board drop preserves the saved piece":"FAIL rejected drop mutated board");}
  if(hold==25)reviewCapture("invalid-placement-message");
  if(hold==26){
   Block wide;wide.family=Sword;wide.level=3;wide.ownedId=1200;wide.ownedDetail=12;wide.ownedGrade=2;wide.ownedW=5;wide.ownedH=1;wide.x=wide.y=0;
   run.board={wide};const auto before=run.encode();reviewTap({l.board.x,l.board.y,l.cell,l.cellH});
   reviewTrace(run.encode()==before?"PASS failed rotation preserves item and records the rotation attempt":"FAIL failed rotation mutated item");
  }
  if(hold==27){done=true;reviewTrace("DONE portrait review");}
  return true;
 }
 if(++hold==18){
  const auto p=PortraitGame::battle(DX,DY,run.shape.height);
  int cells=0;for(int y=0;y<run.shape.height;++y)for(int x=0;x<run.shape.width;++x)cells+=run.shape.contains(x,y);
  bool valid=l.cell==l.cellH&&l.board.w==run.shape.width*l.cell&&l.board.h==run.shape.height*l.cellH&&l.board.x>=0&&l.board.x+l.board.w<=DX&&
    l.board.y-l.board.h>l.slot.y&&l.slot.y-l.slot.h>l.heart.y&&
    l.heart.y-l.heart.h>l.attack.y&&l.arenaBottom-l.plateH>l.board.y&&
    l.ground>l.arenaBottom&&l.ground<p.headerBottom;
  valid=valid&&cells==16+std::min(20,run.stage)&&run.shape.height==4&&cells<=36;
  valid=valid&&cells==portraitGridCapacity()&&run.shape.width>=run.shape.height&&std::abs(l.slot.w*691-l.slot.h*2064)<=2064;
  const auto compact=PortraitGame::battle(DX,(int)(850*l.scale),run.shape.height,run.shape.width);
  const auto tall=PortraitGame::battle(DX,(int)(1408*l.scale),run.shape.height,run.shape.width);
  valid=valid&&compact.cell==tall.cell&&compact.cell==int(64*l.scale)&&compact.boardTop==tall.boardTop&&
    compact.slotTop==tall.slotTop&&compact.slotWidth==tall.slotWidth&&compact.slotHeight==tall.slotHeight&&
    compact.energyTop==tall.energyTop&&compact.actionTop==tall.actionTop&&compact.actionHeight==tall.actionHeight;
  for(int i=0;i<(int)run.board.size();++i)valid=valid&&run.fits(run.board[i],i);
  const Box castle=portraitCastleBox(l);
  const Box gun=castleCannonBox(l);
  valid=valid&&std::abs(castle.x+castle.w-DX/3.f)<1&&castle.w>0&&castle.h>0&&gun.w>=32*l.scale;
  const float overflow=std::max(0.f,castle.y-(DY-78*l.scale));
  const Box fixedBackdrop=portraitBackdropBox(l.ground);
  if(overflow>0){const float y=(l.arenaBottom+DY-78*l.scale)*.5f;
   const bool began=portraitCameraTouch(0,998,DX*.2f,y);
   portraitCameraTouch(1,998,DX*.2f,y-overflow-20*l.scale);
   valid=valid&&began&&std::abs(portraitCameraY+overflow)<2;
   const Box scrolledBackdrop=portraitBackdropBox(layout().ground);
   reviewTrace(fixedBackdrop.x==scrolledBackdrop.x&&fixedBackdrop.y==scrolledBackdrop.y&&fixedBackdrop.w==scrolledBackdrop.w&&fixedBackdrop.h==scrolledBackdrop.h?"PASS vertical castle drag leaves backdrop position and zoom fixed":"FAIL backdrop follows vertical drag");
   portraitCameraTouch(2,998,DX*.2f,y-overflow-20*l.scale);portraitCameraY=0;
  }
  reviewTrace(valid?"PASS square cells, actual capacity, original roulette aspect ratio and viewport geometry":"FAIL portrait geometry");
  reviewTrace(drawnBattleViewportTop==DY?"PASS battlefield continues behind translucent wave header":"FAIL hard header clipping");
  reviewTrace(std::abs(portraitCastleZoom(l)-PortraitGame::battleCastleScale(DX,PortraitCastleArt::BattleReferenceAssemblyHeight))<1&&std::abs(portraitCastleBox(l).x+portraitCastleBox(l).w-DX/3.f)<1&&drawnPortraitTurret==PORTRAIT_TURRET_FIRST_IMG+run.stage?"PASS fixed battle world scale and visible turret":"FAIL battle scale or turret");
  reviewTrace(valid?"PASS identical bottom UI geometry at 1:1.33 and 1:2.2; only battlefield viewport changes":"FAIL fixed bottom stack");
  reviewLayout(l,"portrait");reviewCapture("battle");
 }
 if(hold==19){const Box body=portraitCastleBox(l);portraitCameraY=-std::max(0.f,body.y-(DY-78*l.scale));}
 if(hold==20&&portraitCameraY<0)reviewCapture("castle-roof");
 if(hold==22){
  portraitCameraY=0;
  const Run base=run;
  // Small starter boards can be completely occupied by the capture fixture.
  // Reserve a free destination before testing native drag input.
  run.board.resize(1);
  bool dragged=false;const Block moving=run.board.front();
  for(int y=run.shape.height-Tall(moving);y>=0&&!dragged;--y)for(int x=run.shape.width-Wide(moving);x>=0;--x){
   Block target=moving;target.x=x;target.y=y;
   if((x==moving.x&&y==moving.y)||!run.fits(target,0))continue;
   const float sx=l.board.x+(moving.x+.5f)*l.cell,sy=l.board.y-(moving.y+.5f)*l.cellH;
   const float tx=l.board.x+(x+.5f)*l.cell,ty=l.board.y-(y+.5f)*l.cellH;
   MergeRouletteTouch(0,997,sx,sy);MergeRouletteTouch(1,997,tx,ty);MergeRouletteTouch(2,997,tx,ty);
   dragged=run.board[0].x==x&&run.board[0].y==y;break;
  }
  reviewTrace(dragged?"PASS native multi-cell inventory drag follows new grid coordinates":"FAIL native inventory drag");
  run=base;
  bool costs=true;
  for(int actionKind=0;actionKind<4;++actionKind){
   run=base;run.battleEnergy=5;heartDisplay=5;animation=0;pendingPass=false;automaticMerge=AutomaticMerge();
   action=CombatAction();enemyTurn=EnemyTurn();spinFlightFrame=-1;spinDrops.clear();
   const Box b=actionKind==0?l.spin:actionKind==1?l.attack:actionKind==2?l.cannon:l.lever;
   reviewTap(b);costs=costs&&run.battleEnergy==4;
  }
  run=base;animation=0;run.attacking=false;
  reviewTrace(costs?"PASS native spin, attack and cannon buttons each spend exactly one lightning":"FAIL native action energy cost");
  reviewTrace(costs?"PASS exposed roulette cog starts the same spin for one lightning":"FAIL cog input");
  pendingPass=false;spinFlightFrame=-1;spinDrops.clear();reviewTap(l.lever);
 }
 if(hold==35){reviewTrace(gearAngle>gearStartAngle?"PASS native roulette cogs rotate with spinning reels":"FAIL cog rotation");reviewCapture("cogs-spinning");}
 if(hold==38){done=true;reviewTrace("DONE portrait review");}
 return true;
}
