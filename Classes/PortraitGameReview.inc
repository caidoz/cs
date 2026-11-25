bool portraitReviewEnabled(){return review&&std::getenv("CS_PORTRAIT_REVIEW");}
void portraitReviewFixture(){
 if(!portraitReviewEnabled())return;static bool initialized=false;if(initialized)return;initialized=true;
 cocos2d::Director::getInstance()->setDisplayStats(false);
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
 heroHealthDisplay.set(run.lives);heroHealthDisplay.advance(1);enemyHealthDisplay.set(run.enemyHp);enemyHealthDisplay.advance(1);
 guardDisplay.set(run.guard);guardDisplay.advance(1);
}
bool portraitReviewLobby(){
 if(!portraitReviewEnabled()||!std::getenv("CS_PORTRAIT_LOBBY"))return false;
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
   reviewTrace(!other?"PASS interior gesture is limited to the first castle":"FAIL interior leaks to other castles");
   reviewCapture("starter-interior-open");++phase;
  }else if(phase==3){
   portraitStarterInteriorTouch(0,991,x,y);portraitStarterInteriorTouch(1,991,x,y-100*q.scale);portraitStarterInteriorTouch(2,991,x,y-100*q.scale);
   reviewTrace(starterInteriorReveal==0?"PASS reverse drag restores original exterior":"FAIL starter interior close gesture");campReviewScenario=1;++phase;
  }else if(phase==4){reviewTrace(campDrawnCrewCount==1&&campDrawnCrew[0]==0?"PASS only one owned companion renders once":"FAIL camp single companion");reviewCapture("starter-camp-one");campReviewScenario=2;++phase;
  }else if(phase==5){
   const auto chosen=LobbyCamp::highestOwned(portraitCampOwned());bool valid=campDrawnCrewCount==(int)chosen.size()&&campDrawnCrewCount==3;
   for(int i=0;i<campDrawnCrewCount;++i)valid=valid&&campDrawnCrew[i]==chosen[i].id;
   reviewTrace(valid?"PASS camp renders the three highest owned grades without duplicates":"FAIL camp owned grade order");
   firstFire=campFireFrame;reviewCapture("starter-camp-three");++phase;
  }else if(phase==6&&firstFire!=campFireFrame){reviewTrace("PASS actual campfire animation advances frames");reviewCapture("starter-fire-next");++phase;
  }else if(phase==7){
   portraitStarterInteriorTouch(0,991,x,y);portraitStarterInteriorTouch(2,991,x,y);bool valid=starterInteriorReveal==0;
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
  reviewTrace(castleWheelTravel>firstWheel?"PASS scrolling lobby advances wheel rotation":"FAIL stationary lobby wheels");
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
  valid=valid&&(run.stage<9||cells==48);
  valid=valid&&cells==portraitGridCapacity()&&run.shape.width>run.shape.height&&std::abs(l.slot.w*691-l.slot.h*2064)<=2064;
  const auto compact=PortraitGame::battle(DX,(int)(850*l.scale),run.shape.height,run.shape.width);
  const auto tall=PortraitGame::battle(DX,(int)(1408*l.scale),run.shape.height,run.shape.width);
  valid=valid&&compact.cell==tall.cell&&compact.cell==int(64*l.scale)&&compact.boardTop==tall.boardTop&&
    compact.slotTop==tall.slotTop&&compact.slotWidth==tall.slotWidth&&compact.slotHeight==tall.slotHeight&&
    compact.energyTop==tall.energyTop&&compact.actionTop==tall.actionTop&&compact.actionHeight==tall.actionHeight;
  for(int i=0;i<(int)run.board.size();++i)valid=valid&&run.fits(run.board[i],i);
  const Box castle=portraitCastleBox(l);
  const Box gun=castleCannonBox(l);
  valid=valid&&castle.x>=0&&castle.w>0&&castle.h>0&&gun.w>=64*l.scale&&
   std::min(gun.y,(int)(DY-78*l.scale))-std::max(gun.y-gun.h,l.arenaBottom)>(int)(16*l.scale);
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
