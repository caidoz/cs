// Preview upgrades stay temporary. Explicitly closing keeps a valid departure selection.
#include "Data/CastleFacilities.h"
namespace LobbyCastleDebug {
static bool open=false;
static bool compact=false;
static bool facilities=false;
static int population=0,rooms[10][5]={},drawn=0;
static int levels[PortraitCastleArt::Count][5]={},previousCastle=0;
static int keptPreview=-1;
static bool interiors[10]={};
static void Close(bool keepSelection=false){
 const int selected=gMobileCastleVisual;
 open=false;gMobileCastleVisual=previousCastle;
 for(int c=0;c<10;++c)CastleParts::roomInteriorOpen[c]=interiors[c];
 if(keepSelection&&selected>=10){keptPreview=selected;gMobileCastleVisual=selected;return;}
 if(keepSelection){
  keptPreview=-1;
  const bool kept=CastleSelectDeparture(selected);gMobileCastleVisual=robin.castle;
  if(const char* path=getenv("CS_CASTLE_REVIEW_PATH"))if(getenv("CS_CASTLE_DEBUG_SELECTION_REVIEW")){
   FILE* f=fopen((std::string(path)+"phases.log").c_str(),"a");if(f){fprintf(f,"DETAIL close selected=%d kept=%d actual=%d\n",selected,kept,robin.castle);fclose(f);}
  }
 }
}
}
//디버그로 고른 성은 로비에서만이 아니라 합성 전투에도 그대로 들고 간다.
//MergeRouletteBegin 이 run.stage 를 이 성으로 잡고, 전투 중(MD_PLAY) 성 그림과
//파츠 단계(CastleVisualPartLevel)도 여기 값을 본다. 세이브는 건드리지 않는다.
bool MergeRouletteActive();
static bool LobbyCastleDebugScreen(){return drawHandle==MD_LOBBY || MergeRouletteActive();}
bool LobbyCastleDebugActive(){
#ifdef GAMEDEBUG
 return LobbyCastleDebugScreen() && LobbyCastleDebug::open;
#else
 return false;
#endif
}
int LobbyCastleDebugLevel(int castle,int part){
#ifdef GAMEDEBUG
 if(LobbyCastleDebugScreen() && LobbyCastleDebug::open && castle>=0&&castle<PortraitCastleArt::Count&&part>=0&&part<5)
  return LobbyCastleDebug::levels[castle][part];
#endif
 return -1;
}
int LobbyCastleDebugCastle(){return LobbyCastleDebugActive()?Max(0,Min(PortraitCastleArt::Count-1,gMobileCastleVisual)):LobbyCastleDebug::keptPreview;}
bool LobbyCastleDebugInterior(){
 const int c=LobbyCastleDebugCastle();return c<0 || c>=10 || CastleParts::roomInteriorOpen[c];
}
int LobbyCastleDebugFacilityLevel(int castle,int room){
#ifdef GAMEDEBUG
 if(LobbyCastleDebugScreen() && LobbyCastleDebug::open && castle>=0&&castle<10&&room>=0&&room<CastleFacilities::Counts[castle])
  return LobbyCastleDebug::rooms[castle][room];
#endif
 return -1;
}
bool LobbyCastleDebugHit(float x,float y){
#ifdef GAMEDEBUG
 const int u=Max(1,(int)_2X);
 if(y<=DY-30*u && y>=DY-54*u && x>=214*u&&x<=288*u)return true;
 if(LobbyCastleDebug::open && !LobbyCastleDebug::compact && x>=DX-160*u && y<=DY-66*u && y>=DY-66*u-(366*u))return true;
#endif
 return false;
}
bool LobbyCastleDebugCycle(int castle,int room){
#ifdef GAMEDEBUG
 if(!LobbyCastleDebugActive() || castle<0 || castle>=10 || room< -1 || room>=4)return false;
 if(room<0)LobbyCastleDebug::levels[castle][3]=(LobbyCastleDebug::levels[castle][3]+1)%6;
 else LobbyCastleDebug::rooms[castle][room]=(LobbyCastleDebug::rooms[castle][room]+1)%6;
 return true;
#else
 return false;
#endif
}
void LobbyCastleDebugEnd(){if(LobbyCastleDebug::open)LobbyCastleDebug::Close(true);}
bool LobbyCastleDebugCommand(int command){
#ifdef GAMEDEBUG
 using namespace LobbyCastleDebug;
 if(drawHandle!=MD_LOBBY || (command!=TOUCH_FUNC_LOBBY_CASTLE_HIDE && (command<TOUCH_FUNC_LOBBY_CASTLE_DEBUG || command>TOUCH_FUNC_LOBBY_CASTLE_ROOM_END)))return false;
 if(command==TOUCH_FUNC_LOBBY_CASTLE_DEBUG){
  if(open){if(compact)compact=false;else Close(true);return true;}
  CastleProgressEnsure();previousCastle=robin.castle;gMobileCastleVisual=keptPreview>=0?keptPreview:robin.castle;
  for(int c=0;c<10;++c){
   interiors[c]=CastleParts::roomInteriorOpen[c];
   for(int p=0;p<5;++p){levels[c][p]=robin.castleProgress.parts[c][p];rooms[c][p]=robin.castleProgress.rooms[c][p];}
  }
  open=true;compact=false;return true;
 }
 if(!open)return true;
 if(command==TOUCH_FUNC_LOBBY_CASTLE_HIDE){compact=true;return true;}
 int c=Max(0,Min(PortraitCastleArt::Count-1,gMobileCastleVisual));
 if(command==TOUCH_FUNC_LOBBY_CASTLE_PREV){gMobileCastleVisual=(c+PortraitCastleArt::Count-1)%PortraitCastleArt::Count;return true;}
 if(command==TOUCH_FUNC_LOBBY_CASTLE_NEXT){gMobileCastleVisual=(c+1)%PortraitCastleArt::Count;return true;}
 if(c>=10){
  if(command>=TOUCH_FUNC_LOBBY_CASTLE_PART&&command<=TOUCH_FUNC_LOBBY_CASTLE_PART_END){const int p=command-TOUCH_FUNC_LOBBY_CASTLE_PART;levels[c][p]=(levels[c][p]+1)%6;}
  else if(command==TOUCH_FUNC_LOBBY_CASTLE_ALL){int lv=0;for(int p=0;p<5;++p)lv=Max(lv,levels[c][p]);for(int p=0;p<5;++p)levels[c][p]=(lv+1)%6;}
  else if(command==TOUCH_FUNC_LOBBY_CASTLE_RESET)for(int p=0;p<5;++p)levels[c][p]=0;
  return true;
 }
 if(command==TOUCH_FUNC_LOBBY_CASTLE_FIRE){LobbyArtilleryDebugFire();return true;}
 if(command==TOUCH_FUNC_LOBBY_CASTLE_CROWD){population=population==0?8:population==8?16:population==16?32:0;CastleParts::roomInteriorOpen[c]=true;return true;}
 if(command==TOUCH_FUNC_LOBBY_CASTLE_FACILITIES){facilities=!facilities;return true;}
 if(command>=TOUCH_FUNC_LOBBY_CASTLE_ROOM && command<=TOUCH_FUNC_LOBBY_CASTLE_ROOM_END){int i=command-TOUCH_FUNC_LOBBY_CASTLE_ROOM;if(i<CastleFacilities::Counts[c]){rooms[c][i]=(rooms[c][i]+1)%6;CastleParts::roomInteriorOpen[c]=true;}return true;}
 if(command==TOUCH_FUNC_LOBBY_CASTLE_PREV)gMobileCastleVisual=(c+9)%10;
 else if(command==TOUCH_FUNC_LOBBY_CASTLE_NEXT)gMobileCastleVisual=(c+1)%10;
 else if(command>=TOUCH_FUNC_LOBBY_CASTLE_PART && command<=TOUCH_FUNC_LOBBY_CASTLE_PART_END){
  const int p=command-TOUCH_FUNC_LOBBY_CASTLE_PART;levels[c][p]=(levels[c][p]+1)%6;
 }
 else if(command==TOUCH_FUNC_LOBBY_CASTLE_ALL){
  if(facilities){
   int level=0;for(int p=0;p<CastleFacilities::Counts[c];++p)level=Max(level,rooms[c][p]);
   for(int p=0;p<CastleFacilities::Counts[c];++p)rooms[c][p]=(level+1)%6;
   CastleParts::roomInteriorOpen[c]=true;
  }else{
   int level=0;for(int p=0;p<5;++p)level=Max(level,levels[c][p]);
   for(int p=0;p<5;++p)levels[c][p]=(level+1)%6;
  }
 }
 else if(command==TOUCH_FUNC_LOBBY_CASTLE_INTERIOR)CastleParts::roomInteriorOpen[c]=!CastleParts::roomInteriorOpen[c];
 else if(command==TOUCH_FUNC_LOBBY_CASTLE_RESET)for(int p=0;p<5;++p){levels[c][p]=robin.castleProgress.parts[c][p];rooms[c][p]=robin.castleProgress.rooms[c][p];}
 return true;
#else
 return false;
#endif
}
void LobbyCastleDebugDraw(){
#ifdef GAMEDEBUG
 using namespace LobbyCastleDebug;
 if(drawHandle!=MD_LOBBY)return;
 LobbyArtilleryDebugDraw();
 //손가락 크기 - 상단 디버그 줄(StageBgDebugDrawButton)과 같은 높이 24단위.
 const int u=Max(1,(int)_2X),h=24*u,gap=3*u;
 DrawUiButton(214*u,DY-30*u,74*u,h,open?(compact?"테스트 펼치기":"성 테스트 닫기"):"성 테스트",TOUCH_FUNC_LOBBY_CASTLE_DEBUG,open);
 if(!open||compact)return;
 const int c=Max(0,Min(PortraitCastleArt::Count-1,gMobileCastleVisual)),w=150*u,x=DX-w-4*u;
 const bool legacy=c<10,showFacilities=facilities&&legacy;
 int y=DY-70*u;const int panelH=13*(h+gap)+14*u;
 SetAlpha(29);MemRect(x-3*u,y+4*u,w+6*u,panelH,0x102333);SetAlpha(32);
 MemRectFrame(x-3*u,y+4*u,w+6*u,panelH,0xB99343);
 char label[100];sprintf(label,u8"\uC131 %d / %d",c+1,PortraitCastleArt::Count);
 SetFontColor(COLOR_WHITE);CenterTextStrSolid(label,x+w/2,y,Min(.65f*u,(w-8.0f*u)/Max(1.0f,StringWidth(label,1.0f))));y-=h+gap;
 const int half=(w-gap)/2;
 DrawUiButton(x,y,half,h,"이전 성",TOUCH_FUNC_LOBBY_CASTLE_PREV);
 DrawUiButton(x+half+gap,y,half,h,"다음 성",TOUCH_FUNC_LOBBY_CASTLE_NEXT);y-=h+gap;
 const char* names[]={"첨탑","외부장갑","실내","대포","바퀴"};
 for(int p=0;p<5;++p){
  if(showFacilities){
   if(p<CastleFacilities::Counts[c])sprintf(label,"%s Lv.%d · +%d%%",CastleFacilities::Rooms[c][p].name,rooms[c][p],CastleFacilities::Output(c,p,rooms[c][p]));
   else sprintf(label,"빈 시설");
  }else sprintf(label,"%s  +%d  → 다음 단계",names[p],levels[c][p]);
  DrawUiButton(x,y,w,h,label,showFacilities?(p<CastleFacilities::Counts[c]?TOUCH_FUNC_LOBBY_CASTLE_ROOM+p:0):TOUCH_FUNC_LOBBY_CASTLE_PART+p);y-=h+gap;
 }
 DrawUiButton(x,y,half,h,facilities?"모든 방 단계 +":"전체 단계 +",TOUCH_FUNC_LOBBY_CASTLE_ALL);
 DrawUiButton(x+half+gap,y,half,h,legacy?(CastleParts::roomInteriorOpen[c]?u8"\uC2E4\uB0B4 \uB2EB\uAE30":u8"\uC2E4\uB0B4 \uC5F4\uAE30"):u8"\uD1B5\uC9DC \uC678\uD615",legacy?TOUCH_FUNC_LOBBY_CASTLE_INTERIOR:0);y-=h+gap;
 DrawUiButton(x,y,w,h,"저장된 강화 단계로 복원",TOUCH_FUNC_LOBBY_CASTLE_RESET);y-=h+gap;
 DrawUiButton(x,y,w,h,facilities?"외형 파츠 보기":"생산 시설·단계 보기",legacy?TOUCH_FUNC_LOBBY_CASTLE_FACILITIES:0);y-=h+gap;
 sprintf(label,"NPC %d명 (표시 %d) · 밀도 +",population,drawn);DrawUiButton(x,y,w,h,label,legacy?TOUCH_FUNC_LOBBY_CASTLE_CROWD:0);y-=h+gap;
 DrawUiButton(x,y,w,h,"대포 시험 발사",legacy?TOUCH_FUNC_LOBBY_CASTLE_FIRE:0);y-=h+gap;
 DrawUiButton(x,y,w,h,"패널 접기 · NPC/발사 유지",TOUCH_FUNC_LOBBY_CASTLE_HIDE);
#endif
}
int LobbyCastleDebugPopulation(){
#ifdef GAMEDEBUG
 return drawHandle==MD_LOBBY && LobbyCastleDebug::open?LobbyCastleDebug::population:0;
#else
 return 0;
#endif
}
void LobbyCastleDebugCrowdDraw(){
#ifdef GAMEDEBUG
  LobbyCastleDebug::drawn=0;
 const int total=LobbyCastleDebugPopulation();if(!total || !SoftCastle::Enabled() || !gTotalCrew)return;
 const auto& p=CastleParts::sdPlacement;const int c=p.castle;
 if(!p.valid || c<0 || c>=10 || !CastleParts::RoomRevealRequested(c))return;
 const float unit=DX/640.0f;
 for(int i=0;i<total;++i){
  const int room=i%p.roomCount,rank=i/p.roomCount,count=(total-1-room)/p.roomCount+1;
  const auto& area=CastleNpcPlacement::Areas[c][room];
  const int type=crewData[(i%gTotalCrew)*CREWDATASIZE+CREWDATA_TYPE];if(type==NPC_SHIP)continue;
  const int cmf=enemyData[type*ENEMYDATASIZE+ENEMYDATA_CMF];
  if(cmf<0||cmf>=TOTALCMF)continue;
  if(cmfLoaded[cmf]!=cmf)CmfRead(cmf,cmf);
  const int motion=crewPos[type*5]+frame/8%Max(1,(int)crewPos[type*5+1]);
  if(motion<0||motion>=cmf_m_cnt[cmf])continue;
  const signed short* bounds=cmfMotionImgSizeBlob+cmfMotionImgSizeSlot[cmf]+motion*4;
  const float height=CastleCompanionHeight(CastleWorldCharZoom());
  const float zoom=CastleCompanionZoom(CastleWorldCharZoom(),type);
  const int columns=Max(1,(int)((area.right-area.left)*p.width/(height*.8f)));
  if(rank>=columns)continue;
  const int row=rank/columns,cols=Min(columns,count-row*columns);
  const float x=p.left+CastleNpcPlacement::SlotX(area,rank%columns,cols)*p.width;
  const float foot=CastleParts::RoomFloorFoot(c,room)+Min(area.depth*p.height,Min(row,2)*height*.12f);
  if(p.gunWidth>0 && x+height*.3f>p.gunLeft && x-height*.3f<p.gunLeft+p.gunWidth && foot<p.gunTop && foot+height>p.gunTop-p.gunHeight)continue;
  CastleParts::RoomClipScope clip(true,room);
  DrawCmfDetailShadow(cmf,motion,(int)x,(int)(foot+CastleCompanionFootOffset(type,zoom)),i%2?LEFT:RIGHT,zoom);
  ++LobbyCastleDebug::drawn;
 }
#endif
}
bool LobbyCastleFunctionalReview(){
#ifdef GAMEDEBUG
 const int c=gMobileCastleVisual;
 if(c<0||c>9||!sprite[CastleParts::FacilityImage(c,0)]||LobbyCastleDebug::drawn<1)return false;
 for(int i=0;i<CastleFacilities::Counts[c];++i)for(int lv=0;lv<5;++lv)
  if(CastleFacilities::Output(c,i,lv)>=CastleFacilities::Output(c,i,lv+1))return false;
 return true;
#else
 return false;
#endif
}
bool CastleRoomUpgradeReviewOne(int facility,bool configure){
#ifdef GAMEDEBUG
 if(!getenv("CS_CASTLE_REVIEW_PATH")||facility<0||facility>=5)return false;
 if(configure){
  if(!CastleRoomUpgradeReview(9,0,true))return false;
  LobbyCastleDebug::rooms[9][facility]=5;return true;
 }
 if(CastleParts::facilityDrawCastle!=9||CastleParts::facilityDrawCount!=5)return false;
 for(int i=0;i<5;++i)if(CastleParts::facilityDrawLevels[i]!=(i==facility?5:0))return false;
 return true;
#else
 return false;
#endif
}
bool CastleRoomUpgradeReview(int castle,int level,bool configure){
#ifdef GAMEDEBUG
 if(!getenv("CS_CASTLE_REVIEW_PATH")||castle<0||castle>=10||level<0||level>5)return false;
 if(configure){
  if(!LobbyCastleDebug::open)return false;
  gMobileCastleVisual=castle;CastleParts::roomInteriorOpen[castle]=true;
  for(int i=0;i<CastleFacilities::Counts[castle];++i)LobbyCastleDebug::rooms[castle][i]=level;
  return true;
 }
 if(!CastleRoomUpgradeShaderValid()||CastleParts::facilityDrawCastle!=castle||CastleParts::facilityDrawCount!=CastleFacilities::Counts[castle])return false;
 // A room level may change furniture, never the castle's placement or size.
 static float bodyWidth[10]={},bodyHeight[10]={};
 const auto& placement=CastleParts::sdPlacement;
 if(level==0){bodyWidth[castle]=placement.width;bodyHeight[castle]=placement.height;}
 else if(fabs(bodyWidth[castle]-placement.width)>.01f||fabs(bodyHeight[castle]-placement.height)>.01f)return false;
 for(int i=0;i<CastleFacilities::Counts[castle];++i){
  if(CastleParts::facilityDrawLevels[i]!=level||LobbyCastleDebugFacilityLevel(castle,i)!=level)return false;
 }
 return true;
#else
 return false;
#endif
}
