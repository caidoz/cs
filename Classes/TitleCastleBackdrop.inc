// Title shares the parked lobby world, without any lobby UI or owned companions.
namespace TitleCastleBackdrop {static bool rendered=false;}
bool MergeRouletteTitleCastlesDraw(){
 if(!(review&&reviewCapturePending))titleEntranceClock+=std::min(.1f,std::max(0.f,cocos2d::Director::getInstance()->getDeltaTime()));
 const bool wasActive=active;const int previousHandle=drawHandle;
 active=false;drawHandle=MD_LOBBY;titleCampOnly=true;
 const float camera=portraitCameraY,reveal=starterInteriorReveal;portraitCameraY=0;starterInteriorReveal=0;
 const bool painted=MergeRouletteLobbySceneDraw(true);
 TitleCastleBackdrop::rendered=painted&&touchIndex==0&&campDrawnCrewCount==0&&sprite[PORTRAIT_RAIL_IMG]&&sprite[PORTRAIT_CAMPFIRE_IMG];
 portraitCameraY=camera;starterInteriorReveal=reveal;titleCampOnly=false;active=wasActive;drawHandle=previousHandle;
 return true;
}
bool MergeRouletteTitleCastlesLayoutReview(){return TitleCastleBackdrop::rendered;}
