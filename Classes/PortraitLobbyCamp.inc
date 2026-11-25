// Resting party is sourced from actual inventory, never the combat-review roster.
int campDrawnCrew[3]={-1,-1,-1},campDrawnCrewCount=0,campFireFrame=0;
int campReviewScenario=-1;
std::vector<LobbyCamp::Owned> portraitCampOwned(){
 std::vector<LobbyCamp::Owned> owned;
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
void drawPortraitLobbyCamp(const Layout& l){
 campDrawnCrewCount=0;for(int& id:campDrawnCrew)id=-1;
 if(active||nativeTitleIsolate||siegeActive)return;
 const auto selected=LobbyCamp::highestOwned(portraitCampOwned());
 const float s=l.scale;const Box hull=portraitCastleBox(l);
 const int center=std::max((int)(150*s),std::min(DX-(int)(94*s),hull.x+hull.w+(int)(80*s)));
 const int foot=l.ground+(int)(3*s);
 // Draw original neutral character sprites; everyone faces the fire.
 const int heroX=center-(int)((selected.empty()?42:54)*s);
 if(hero.cmf>=0&&hero.cmf<MAXCMF){
  if(cmfLoaded[hero.cmf]!=hero.cmf)CmfRead(hero.cmf,hero.cmf);
  const int motion=heroNeutralMotion(hero);const auto* b=cmfMotionImgSize[hero.cmf]+motion*4;
  const float z=44*s/std::max(1,(int)b[3]);DrawPlayer(&hero,motion,heroX,foot,RIGHT,z,0,false,true);
 }
 const int offsets[3]={-26,32,60};
 for(int i=0;i<(int)selected.size();++i){const int id=selected[i].id,npc=crewData[id*CREWDATASIZE+CREWDATA_TYPE];
  const int cmf=enemyData[npc*ENEMYDATASIZE+ENEMYDATA_CMF];if(cmf<0||cmf>=MAXCMF)continue;
  if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);
  const int idle=crewIdleMotion(id,ticks/8+i*3),motion=idle>=0?idle:crewPos[npc*5];
  if(motion<0||motion>=cmf_m_cnt[cmf])continue;
  const auto* b=cmfMotionImgSize[cmf]+motion*4;const float z=42*s/std::max(1,(int)b[3]);
  const int x=center+(int)((selected.size()==1?38:offsets[i])*s);
  DrawCmfDetailShadow(cmf,motion,x,foot,x<center?RIGHT:LEFT,z);
  campDrawnCrew[campDrawnCrewCount++]=id;
 }
 const int img=PORTRAIT_CAMPFIRE_IMG;if(!sprite[img])LoadImg(img);campFireFrame=(ticks/9)%4;
 const int size=(int)(42*s);turretPart(img,campFireFrame*64,0,64,64,{center-size/2,foot+size-(int)(2*s),size,size});
}
