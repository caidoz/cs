bool reviewOriginalTopbar(){
 if(review&&std::getenv("CS_CASTLE_PROPORTIONS_REVIEW")){
  static int sample=0,hold=0;static bool done=false;
  if(done||reviewCapturePending)return true;
  robin.castle=sample;gMobileCastleVisual=sample;run.stage=sample;
  const int handle=drawHandle;drawHandle=MD_LOBBY;
  const Layout l=layout();drawWorld(l,false);drawLobbyControls(l,0,true);
  LobbyResourceBarsDraw(DY-(int)(2*l.scale));GNBDraw(0,DY-(int)(2*l.scale));drawHandle=handle;
  cocos2d::Director::getInstance()->setDisplayStats(false);
  if(++hold<12)return true;
  bool valid=std::abs(CastleArtGeometry::width(sample)*OriginalCastle::zoom()-DX*600.f/640.f)<.01f;
  const Box roof=OriginalCastle::box(380,0,CastleArtGeometry::DeckRight[sample]-380,0);
  const Box support=OriginalCastle::box(CastleArtGeometry::DeckRight[sample],0,0,0);
  valid=valid&&roof.x+roof.w==support.x;
  const int img=MistCastle::image(sample,0);
  for(int i=0;i<curRenderCnt;++i){auto* sp=renderSprite[curRenderSpriteArr[i]];
   for(int artwork:{img,(int)BATTLE_DECK_SURFACE_IMG,(int)CANNON_UPGRADE_ATLAS_IMG,CASTLE_MIST_TURRET_FIRST_IMG+sample})
    if(sp&&sprite[artwork]&&sp->getTexture()==sprite[artwork]->getTexture()){
     const bool uniform=std::abs(std::abs(sp->getScaleX())-std::abs(sp->getScaleY()))<.00001f;
     if(!uniform){char detail[128];snprintf(detail,sizeof(detail),"DETAIL aspect image=%d sx=%.5f sy=%.5f",artwork,sp->getScaleX(),sp->getScaleY());reviewTrace(detail);}
     valid=valid&&uniform;
    }
  }
  reviewTrace(valid?"PASS castle equal visible width and uniform hull scale":"FAIL castle dimensions");
  char name[64];snprintf(name,sizeof(name),"castle-proportions-%02d",sample+1);reviewCapture(name);
  if(++sample==10){done=true;reviewTrace("DONE castle proportions review");}
  hold=0;return true;
 }
 if(!review||!std::getenv("CS_ORIGINAL_TOPBAR_REVIEW"))return false;
 static int sample=0,hold=0;static bool captured=false,done=false;
 if(done||reviewCapturePending)return true;
 const long long values[3]={140,1000000,GOLD_MAX};
 robin.gold=values[sample];robin.coin=sample==0?0:2500;robin.heart=sample==0?99:48;
 const int handle=drawHandle;drawHandle=MD_LOBBY;
 MergeRouletteLobbySceneDraw();drawHandle=handle;
 cocos2d::Director::getInstance()->setDisplayStats(false);
 if(++hold<20)return true;
 if(!captured){
  int level=0,gold=0,cash=0,energy=0,settings=0;bool collect=false;
  for(int i=0;i<touchIndex;++i)if(touchRect[i][1]>=DY-LOBBY_BAR_H){const int c=touchRect[i][4];
   level+=c==TOUCH_FUNC_POPUP_LVUPREWARD;gold+=c==TOUCH_FUNC_GOTO_GOLD_IAP;
   cash+=c==TOUCH_FUNC_GOTO_RAINBOW_IAP;energy+=c==TOUCH_FUNC_GOTO_ENERGY_IAP;settings+=c==TOUCH_FUNC_SETTING;collect|=c==TOUCH_FUNC_CASTLE_INCOME;
  }
  reviewTrace(level==1&&gold==1&&cash==1&&energy==1&&settings==1&&!collect?
   "PASS original level gold diamond energy strip with native settings and no collect button":"FAIL original topbar touch targets");
  char name[64];snprintf(name,sizeof(name),"original-topbar-%d",sample);reviewCapture(name);captured=true;return true;
 }
 if(++sample==3){done=true;reviewTrace("DONE original topbar review");}
 hold=0;captured=false;return true;
}
