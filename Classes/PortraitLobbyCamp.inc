// Resting party is sourced from actual inventory, never the combat-review roster.
int campDrawnCrew[3]={-1,-1,-1},campDrawnCrewCount=0,campFireFrame=0;
int campReviewScenario=-1;
std::vector<LobbyCamp::Owned> portraitCampOwned(){
 std::vector<LobbyCamp::Owned> owned;
 if(titleCampOnly)return owned;
 if(review&&(std::getenv("CS_PORTRAIT_CAMP_REVIEW")||std::getenv("CS_BASE_CAMP_REVIEW"))&&campReviewScenario>=0){
  if(campReviewScenario==1)owned.push_back({0,MergeTrees::Star(0),1});
  if(campReviewScenario>=2)for(int id:{0,5,17,38,63})owned.push_back({id,MergeTrees::Star(id),1});
  return owned;
 }
 for(int i=0;i<GetMaxInven();++i){const ITEM& item=robin.inven[i];
  if(item.type==ITEM_CREW&&item.lv>0&&item.detail>=0&&item.detail<64)owned.push_back({item.detail,MergeTrees::Star(item.detail),(int)item.lv});
 }
 return owned;
}
// The atlas supplies only a pooled render quad; flames, embers and falloff are continuous shader effects.
void DrawLobbyCampFire(float x,float y,float scale,float time,bool foreground){
 const int img=PORTRAIT_CAMPFIRE_IMG;if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 GetSpriteIndex(img);
 if(getSpriteIdx==totalRenderCnt){
  renderSprite[getSpriteIdx]=cocos2d::Sprite::createWithTexture(sprite[img]->getTexture());renderSprite[getSpriteIdx]->retain();renderSpriteIndex[getSpriteIdx]=getSpriteTexture;
  if(sameRenderSpriteCur[img]<3000)sameRenderSpriteArr[img][sameRenderSpriteCur[img]]=totalRenderCnt;
  ++sameRenderSpriteMax[img];++sameRenderSpriteCur[img];++totalRenderCnt;
 }
 auto* sp=renderSprite[getSpriteIdx];sp->setTexture(sprite[img]->getTexture());sp->setTextureRect(cocos2d::Rect(0,0,64,64));
 sp->setAnchorPoint({.5f,0});sp->setPosition({x,y-18*scale});sp->setScaleX(180*scale/64);sp->setScaleY(170*scale/64);
 sp->setFlippedX(false);sp->setFlippedY(false);sp->setRotation(0);sp->setColor(cocos2d::Color3B::WHITE);sp->setOpacity(255);
 sp->setBlendFunc({GL_SRC_ALPHA,GL_ONE});ApplyLobbyFireEffect(sp,time,foreground);AfterSpriting(sp);
}
int campInteriorCount=0,campOutsideCount=0;bool campFireDrawn=false,campHeroInside=false;
float campHeroX=0,campPatrolX[3]={},campPatrolY[3]={};
float lobbyRecallGround=0,lobbyRecallCamera=0,lobbyRecallReveal=1;
float campPatrolAmplitude(const Layout& l){const Box hull=portraitCastleBox(l);const float left=std::min(hull.x+hull.w+18*l.scale,DX-100*l.scale);return std::min(24*l.scale,std::max(20*l.scale,DX-36*l.scale-left)*.12f);}
float campOutsidePosition(const Layout& l,int actor){
 const Box hull=portraitCastleBox(l);const float scale=l.scale;
 const float left=std::min(hull.x+hull.w+18*scale,DX-100*scale),right=DX-36*scale;
 const float fraction=actor==0?.10f:actor==1?.31f:actor==2?.53f:.84f;
 return std::max(left,std::min(right,left+(right-left)*fraction+campPatrolAmplitude(l)*BaseCamp::wander(ticks/60.f,actor)));
}
void captureLobbyDeparture(){
 const Layout l=layout();lobbyRecallGround=l.ground;lobbyRecallCamera=portraitCameraY;lobbyRecallReveal=starterInteriorReveal;
 for(int i=0;i<4;++i){lobbyRecallX[i]=campOutsidePosition(l,i);lobbyRecallY[i]=l.ground+20*l.scale;}
 lobbyRecallX[0]=campHeroX;
 for(int i=0;i<3;++i)if(campPatrolX[i]>0)lobbyRecallX[i+1]=campPatrolX[i];
 starterInteriorReveal=1;
}
bool campRoomClip(const Layout& l,Box& room,int slot){
 const int c=std::max(0,std::min(18,run.stage));const Box window=portraitHabitatBounds(c,portraitCastleBox(l));const int floors=portraitHabitatFloors(c);
 const int floor=slot%floors,rank=slot/floors;
 room={window.x+(int)(window.w*(rank%2?.62f:.30f)),window.y-(floor+1)*window.h/floors+(int)(5*l.scale),window.w,window.h/floors};
 clipX=std::max(clipX,window.x);clipX2=std::min(clipX2,window.x+window.w);
 clipY=std::min(clipY,window.y-window.h+(int)(window.h*starterInteriorReveal));clipY2=std::max(clipY2,window.y-window.h);
 return clipX2>clipX&&clipY>clipY2&&starterInteriorReveal>0;
}
void campCrewSprite(int id,int motion,float x,float foot,float height,int dir){
 const int npc=crewData[id*CREWDATASIZE+CREWDATA_TYPE],cmf=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF];if(cmf<0||cmf>=MAXCMF)return;
 if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);
 if(motion<0||motion>=cmf_m_cnt[cmf])motion=crewPos[npc*5];
 const auto* b=cmfMotionImgSize[cmf]+motion*4;DrawCmfDetailShadow(cmf,motion,(int)x,(int)foot,dir,height/std::max(1,(int)b[3]));
}
void campHeroSprite(float x,float foot,float height,bool running,int dir){
 if(hero.cmf<0||hero.cmf>=MAXCMF)return;if(cmfLoaded[hero.cmf]!=hero.cmf)CmfRead(hero.cmf,hero.cmf);
 int motion=running?GetHeroLoopMotion(hero.cmf,HEROLOOP_RUN,ticks/2):GetHeroLoopMotion(hero.cmf,HEROLOOP_WALK,ticks/5);
 if(motion<0||titleCampOnly||(lobbyDepartureAge>=0&&BaseCamp::recall(lobbyDepartureAge,0)>=.995f))motion=heroNeutralMotion(hero);
 const auto* b=cmfMotionImgSize[hero.cmf]+motion*4;DrawPlayer(&hero,motion,(int)x,(int)foot,dir,height/std::max(1,(int)b[3]),0,false,true);
}
void drawPortraitLobbyCamp(const Layout& l){
 campDrawnCrewCount=campInteriorCount=campOutsideCount=0;campFireDrawn=campHeroInside=false;for(int& id:campDrawnCrew)id=-1;
 if(active||nativeTitleIsolate||siegeActive)return;
 const auto selected=LobbyCamp::highestOwned(portraitCampOwned());const float s=l.scale;const Box hull=portraitCastleBox(l);
 const float foot=l.ground+20*s;const bool departing=lobbyDepartureAge>=0;
 const int indoor=selected.size()>=2?1:0;
 const int cx=clipX,cy=clipY,cx2=clipX2,cy2=clipY2;
 auto restore=[&](){clipX=cx;clipY=cy;clipX2=cx2;clipY2=cy2;};
 if(titleCampOnly){
  const float center=std::max(390*s,std::min(DX-155*s,hull.x+hull.w+130*s));
  DrawLobbyCampFire(center,foot-10*s,s,ticks/60.f,false);
  SetLobbyCampLight(true,center,foot+17*s,150*s,ticks/60.f);campHeroSprite(center-90*s,foot,88*s,false,RIGHT);SetLobbyCampLight(false,0,0,0,0);
  const int img=PORTRAIT_CAMPFIRE_IMG;if(!sprite[img])LoadImg(img);const float z=63*s/64.f;
  turretPart(img,0,41,64,23,{(int)(center-32*z),(int)(foot-10*s+23*z),(int)(64*z),(int)(23*z)});
  DrawLobbyCampFire(center,foot-10*s,s,ticks/60.f,true);campFireDrawn=true;restore();return;
 }
 const float doorX=hull.x+hull.w*.44f,doorFoot=hull.y-hull.h*.79f;
 const float heroRecall=BaseCamp::recall(lobbyDepartureAge,0);
 if(!departing||heroRecall<.995f){
  campHeroX=departing?lobbyRecallX[0]*(1-heroRecall)+doorX*heroRecall:campOutsidePosition(l,0);
  const float y=departing?(lobbyRecallY[0]+l.ground-lobbyRecallGround)*(1-heroRecall)+doorFoot*heroRecall:foot;
  const int dir=departing?(lobbyRecallX[0]>doorX?LEFT:RIGHT):(std::cos(ticks/60.f*.62f)<0?LEFT:RIGHT);
  SetAlpha(departing?(int)(32*(1-BaseCamp::ease(heroRecall,.84f,1.f))):32);
  campHeroSprite(campHeroX,y,88*s*(1-.5f*heroRecall),departing,dir);SetAlpha(32);
 }else{Box room;if(campRoomClip(l,room,3)){campHeroSprite(room.x,room.y,std::min(34*s,room.h*.78f),false,RIGHT);campHeroInside=true;}restore();}
 for(int i=0;i<(int)selected.size();++i){
  const int id=selected[i].id;const bool resident=i<indoor;const float q=resident?1.f:BaseCamp::recall(lobbyDepartureAge,i+1);
  const bool entered=resident||(departing&&q>=.995f);
  if(entered){
   Box room;if(campRoomClip(l,room,i)){
    const float x=room.x+std::sin(ticks/70.f+i)*5*s;
    campCrewSprite(id,crewIdleMotion(id,ticks/8+i*3),x,room.y,std::min(32*s,room.h*.75f),RIGHT);
    ++campInteriorCount;campDrawnCrew[campDrawnCrewCount++]=id;
   }restore();
  }else{
   const int actor=i+1;const float from=departing?lobbyRecallX[actor]:campOutsidePosition(l,actor);
   float x=departing?from*(1-q)+doorX*q:from;
   const float y=departing?(lobbyRecallY[actor]+l.ground-lobbyRecallGround)*(1-q)+doorFoot*q:foot;
   const int walk=crewWalkMotion(id,departing?ticks/2+i*3:ticks/6+i*3);
   const bool walking=walk>=0;
   // Characters without native walking frames rest in place, then hop back on recall.
   if(!walking&&!departing)x=std::max(hull.x+hull.w+28*s,std::min(DX-36*s,from-campPatrolAmplitude(l)*BaseCamp::wander(ticks/60.f,actor)));
   const int dir=departing?(from>doorX?LEFT:RIGHT):(std::cos(ticks/60.f*.62f+actor*2.1f)<0?LEFT:RIGHT);
   SetAlpha(departing?(int)(32*(1-BaseCamp::ease(q,.84f,1.f))):32);
   campCrewSprite(id,walking?walk:crewIdleMotion(id,ticks/8+i*3),x,y+(departing&&!walking?std::abs(std::sin(ticks*.6f))*3*s:0),63*s*(1-.5f*q),dir);SetAlpha(32);
   campPatrolX[i]=x;campPatrolY[i]=y;++campOutsideCount;campDrawnCrew[campDrawnCrewCount++]=id;
  }
 }
 restore();
}
