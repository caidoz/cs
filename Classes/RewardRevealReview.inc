// Native visual fixtures only; rewards are not granted to inventory.
bool rewardRevealReview(){
 const char* demoCount=std::getenv("CS_REWARD_REVEAL_DEMO");
 if(!review||(!std::getenv("CS_REWARD_REVEAL_REVIEW")&&!demoCount))return false;
 static int sample=0,phase=0;static bool capturedRibbon=false,capturedDeal=false,skipped=false,capturedDrop=false,capturedOpen=false;
 if(sample>=4)return true;
 if(reviewCapturePending)return true;
 const int counts[4]={1,3,12,30};const int n=demoCount?std::max(1,std::min(30,std::atoi(demoCount))):counts[sample];
 const auto capture=[&](const char* state){char name[80];snprintf(name,sizeof(name),"reward-%02d-%s",n,state);reviewCapture(name);};
 if(phase==0){
  if(entering())return true;
  cocos2d::Director::getInstance()->setDisplayStats(false);
  introElapsed=-1;animation=0;run.choosing=false;
  waveTransition.begin();waveTransition.age=MergeCombat::WaveTransition::DefeatFrames;
  std::vector<RewardPopup::Entry> rewards;
  const int types[7]={ITEM_SWORD,ITEM_HELM,ITEM_ARMOR,ITEM_GUNTLET,ITEM_PANTS,ITEM_BOOTS,ITEM_CREW};
  bool mixed[6]={};
  for(int i=0;i<n;++i){RewardPopup::Entry e;e.lv=1;e.count=1;
   if(i==0||i%13==0){e.type=ITEM_GOLD;e.count=10*(i+1);}
   else {const int wanted=(i-1)%6+1;e.type=types[(i-1)%7];bool found=false;
    for(int pass=0;pass<2&&!found;++pass){if(pass)e.type=ITEM_CREW;
     for(int d=0;d<itemStartCnt[e.type+1]-itemStartCnt[e.type];++d)if(GetItemStar(e.type,d,0)==wanted){e.detail=d;found=true;break;}
    }
    if(found)mixed[wanted-1]=true;
   }rewards.push_back(e);
  }
  RewardPopup::drawButton=rewardButton;RewardPopup::show(u8"보상",rewards,u8"확인",DX*.85f,layout().ground+40*DX/640.f);
  if(n==30){bool all=true;for(bool present:mixed)all=all&&present;reviewTrace(all?"PASS sample mixes all six native star tiers":"FAIL missing star tiers");}
  RewardReveal::Layout l(DX,DY,n),one(DX,DY,1);
  reviewTrace(l.zoom==one.zoom&&l.w==one.w&&l.h==one.h?"PASS fixed card size independent of count":"FAIL count-dependent scale");
  if(n==30)reviewTrace((DY>1000?l.maximum==0:l.maximum>0)?"PASS height-dependent scrolling":"FAIL responsive scrolling");
  capturedRibbon=capturedDeal=skipped=capturedDrop=capturedOpen=false;phase=1;return true;
 }
 if(demoCount){
  // Interactive preview: leave reveal/skip/scroll/confirm to the user.
  // Reopen after confirmation so the same sample can be watched repeatedly.
  waveTransition.age=MergeCombat::WaveTransition::DefeatFrames;
  if(!RewardPopup::open())phase=0;
  return true;
 }
 if(phase==1){
  if(n==1&&!capturedDrop&&RewardPopup::ticks()>=12){capturedDrop=true;capture("chest-drop");return true;}
  if(n==1&&!capturedOpen&&RewardPopup::ticks()>=RewardPopup::OpenFrame+4){
   capturedOpen=true;capture("chest-open");
   reviewTrace(RewardPopup::sourceX==DX*.85f&&RewardPopup::ticks()<RewardPopup::CardStart?"PASS chest launches from enemy and opens before cards":"FAIL chest reveal order");return true;
  }
  if(!capturedRibbon&&RewardPopup::ticks()>=RewardPopup::summaryStart()+10){capturedRibbon=true;capture("ribbon");return true;}
  if(!capturedDeal&&RewardPopup::ticks()>=RewardPopup::CardStart+15){capturedDeal=true;capture("dealing");return true;}
  if(n==3&&!skipped&&RewardPopup::ticks()>=RewardPopup::CardStart+40){
   skipped=true;const int x=RewardPopup::bx+RewardPopup::bw/2,y=RewardPopup::by-RewardPopup::bh/2;
   RewardPopup::touch(x,y,0,93);RewardPopup::touch(x,y,2,93);
   reviewTrace(RewardPopup::open()&&RewardPopup::ready()?"PASS skip reveals without dismissing rewards":"FAIL reveal skip");return true;
  }
  if(!RewardPopup::ready())return true;
  capture("complete");phase=2;return true;
 }
 if(phase==2){
  const RewardReveal::Layout l(DX,DY,n);
  if(l.maximum>0){
   RewardPopup::touch(DX*.5f,(l.top+l.bottom)*.5f,0,91);
   RewardPopup::touch(DX*.5f,(l.top+l.bottom)*.5f-2000,1,91);
   RewardPopup::touch(DX*.5f,(l.top+l.bottom)*.5f-2000,2,91);
   reviewTrace(RewardPopup::scroll==0?"PASS drag returns to first row":"FAIL reward scroll top");
   capture("scroll-top");
  }
  phase=3;return true;
 }
 if(phase==3){
  const int x=RewardPopup::bx+RewardPopup::bw/2,y=RewardPopup::by-RewardPopup::bh/2;
  RewardPopup::touch(x,y,0,92);RewardPopup::touch(x,y,2,92);
  reviewTrace(!RewardPopup::open()?"PASS confirm closes revealed rewards":"FAIL confirm");
  if(++sample==4){reviewTrace("DONE reward reveal review");return true;}
  phase=0;return true;
 }
 return true;
}
