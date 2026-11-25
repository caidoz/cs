// Resting party is sourced from actual inventory, never the combat-review roster.
int campDrawnCrew[3]={-1,-1,-1},campDrawnCrewCount=0,campFireFrame=0;
int campReviewScenario=-1;
std::vector<LobbyCamp::Owned> portraitCampOwned(){
 std::vector<LobbyCamp::Owned> owned;
 if(titleCampOnly)return owned;
 if(review&&std::getenv("CS_PORTRAIT_CAMP_REVIEW")&&campReviewScenario>=0){
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
void drawPortraitLobbyCamp(const Layout& l){
 campDrawnCrewCount=0;for(int& id:campDrawnCrew)id=-1;
 if(active||nativeTitleIsolate||siegeActive)return;
 const auto selected=LobbyCamp::highestOwned(portraitCampOwned());
 const float s=l.scale;const Box hull=portraitCastleBox(l);
 const int center=std::max((int)(390*s),std::min(DX-(int)(155*s),hull.x+hull.w+(int)(130*s)));
 const int foot=l.ground+(int)(20*s);
 const float fireTime=ticks/60.f;
 DrawLobbyCampFire(center,foot-10*s,s,fireTime,false);
 SetLobbyCampLight(true,center,foot+17*s,150*s,fireTime);
 // Draw original neutral character sprites; everyone faces the fire.
 const int heroX=center-(int)(90*s);
 if(hero.cmf>=0&&hero.cmf<MAXCMF){
  if(cmfLoaded[hero.cmf]!=hero.cmf)CmfRead(hero.cmf,hero.cmf);
  const int motion=heroNeutralMotion(hero);const auto* b=cmfMotionImgSize[hero.cmf]+motion*4;
  const float z=88*s/std::max(1,(int)b[3]);DrawPlayer(&hero,motion,heroX,foot,RIGHT,z,0,false,true);
 }
 const int offsets[3]={-48,65,120};
 for(int i=0;i<(int)selected.size();++i){const int id=selected[i].id,npc=crewData[id*CREWDATASIZE+CREWDATA_TYPE];
  const int cmf=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF];if(cmf<0||cmf>=MAXCMF)continue;
  if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);
  const int idle=crewIdleMotion(id,ticks/8+i*3),motion=idle>=0?idle:crewPos[npc*5];
  if(motion<0||motion>=cmf_m_cnt[cmf])continue;
  const auto* b=cmfMotionImgSize[cmf]+motion*4;const float z=63*s/std::max(1,(int)b[3]);
  const int x=center+(int)((selected.size()==1?65:offsets[i])*s);
  DrawCmfDetailShadow(cmf,motion,x,foot,x<center?RIGHT:LEFT,z);
  campDrawnCrew[campDrawnCrewCount++]=id;
 }
 SetLobbyCampLight(false,0,0,0,0);
 const int img=PORTRAIT_CAMPFIRE_IMG;if(!sprite[img])LoadImg(img);campFireFrame=(ticks/9)%4;
 // Static hearth only: the original painted flames are replaced by the live effect.
 const float z=63*s/64.f;turretPart(img,0,41,64,23,{center-(int)(32*z),foot-(int)(10*s)+(int)(23*z),(int)(64*z),(int)(23*z)});
 DrawLobbyCampFire(center,foot-10*s,s,fireTime,true);
}
