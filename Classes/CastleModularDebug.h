#pragma once
#include "CastlePartState.h"
#include "Data/UniformCastleAnchors.h"
#include "Data/IndividualCastleV4.h"
#include "Data/IndividualCastleRooms.h"
#include "Data/InventoryCannonSprites.h"
#include "Data/CastleRoomFacade.h"
#include "Data/SdRoomDeck.h"
#include "Data/CastleCrewDeckLayout.h"
#include "Data/StarterSdParts.h"
#include "Data/StarterSdPartsStage1.h"
#include "Data/StarterSdPartsStage2.h"
#include "Data/StarterSdPartsStage3.h"
#include "Data/StarterSdPartsStage4.h"
#include "Data/StarterSdPartsStage5.h"
#include "Data/SecondSdParts.h"
#include "Data/SecondSdPartsStage1.h"
#include "Data/SecondSdPartsStage2.h"
#include "Data/SecondSdPartsStage3.h"
#include "Data/SecondSdPartsStage4.h"
#include "Data/SecondSdPartsStage5.h"
#include "Data/ThirdSdParts.h"
#include "Data/ThirdSdPartsStage1.h"
#include "Data/ThirdSdPartsStage2.h"
#include "Data/ThirdSdPartsStage3.h"
#include "Data/ThirdSdPartsStage4.h"
#include "Data/ThirdSdPartsStage5.h"
#include "Data/FourthSdParts.h"
#include "Data/FourthSdPartsStage1.h"
#include "Data/FourthSdPartsStage2.h"
#include "Data/FourthSdPartsStage3.h"
#include "Data/FourthSdPartsStage4.h"
#include "Data/FourthSdPartsStage5.h"
#include "Data/FifthSdParts.h"
#include "Data/FifthSdPartsStage1.h"
#include "Data/FifthSdPartsStage2.h"
#include "Data/FifthSdPartsStage3.h"
#include "Data/FifthSdPartsStage4.h"
#include "Data/FifthSdPartsStage5.h"
#include "Data/SixthSdParts.h"
#include "Data/SixthSdPartsStage1.h"
#include "Data/SixthSdPartsStage2.h"
#include "Data/SixthSdPartsStage3.h"
#include "Data/SixthSdPartsStage4.h"
#include "Data/SixthSdPartsStage5.h"
#include "Data/SeventhSdParts.h"
#include "Data/SeventhSdPartsStage1.h"
#include "Data/SeventhSdPartsStage2.h"
#include "Data/SeventhSdPartsStage3.h"
#include "Data/SeventhSdPartsStage4.h"
#include "Data/SeventhSdPartsStage5.h"
#include "Data/EighthSdParts.h"
#include "Data/EighthSdPartsStage1.h"
#include "Data/EighthSdPartsStage2.h"
#include "Data/EighthSdPartsStage3.h"
#include "Data/EighthSdPartsStage4.h"
#include "Data/EighthSdPartsStage5.h"
#include "Data/NinthSdParts.h"
#include "Data/NinthSdPartsStage1.h"
#include "Data/NinthSdPartsStage2.h"
#include "Data/NinthSdPartsStage3.h"
#include "Data/NinthSdPartsStage4.h"
#include "Data/NinthSdPartsStage5.h"
#include "Data/TenthSdParts.h"
#include "Data/TenthSdPartsStage1.h"
#include "Data/TenthSdPartsStage2.h"
#include "Data/TenthSdPartsStage3.h"
#include "Data/TenthSdPartsStage4.h"
#include "Data/TenthSdPartsStage5.h"
#include <cstdlib>
#include <cmath>
#include <chrono>

//배경이 지금까지 흘려보낸 거리(화면 픽셀). StageBackground 가 센다.
float StageBgRailTravelPx(void);
float StageCastleGroundingPx(void);
float CastlePartsViewZoom(void);
float CastlePartsViewLeft(float fallback);

namespace CastleParts {
struct Box { int x,y,w,h; };
static const Box kBox[CastleCount] = {
 {0,0,512,128},{0,0,512,256},{0,0,512,384},{0,0,512,512},{0,0,512,640},
 {0,0,512,768},{0,0,512,896},{0,0,512,1024},{0,0,512,1152},{0,0,512,1280}
};
static const int kPartW[PartCount]={384,384,384,168,384};
static const int kPartH[PartCount]={150,72,112,104,144};
static const char* const kLabels[PartCount]={"지붕","성벽","내부","대포","차대/바퀴"};
// Each floor is a place, not a stat.  Bag slots and the like already rise
// with the castle grade, so a floor only has to look like somewhere.
//
// They climb from making a living to living well: soil and iron at the
// bottom, marble and gold at the top.  The castle leaves the ground at the
// science lab, so floors 8 and up are drawn as if airborne.
static const char* const kThemes[CastleCount]={"식량 생산지","대장간","주거 구역","레스토랑","백화점","수영장 · 스파","과학 연구소","생명공학관","도서관 · 미술관","황실"};
static State state;
static const float RoomDrawW=320.0f;
static int roomStage[CastleCount]={0,0,0,0,0,0,0,0,0,0};
static bool active=false;
static bool missingAsset=false;
static float cannonMuzzleX[10]={0},cannonMuzzleY[10]={0};
static bool cannonMuzzleValid[10]={false};
static float cannonBaseY[10]={0};
static float partAnchor[10][5][2]={0};
// Stage-zero preview textures have authored crops. Other assembly modes keep
// their original fixed-size textures through separate retained resource IDs.
static bool useStarterLegacy=false, useSecondLegacy=false, useThirdLegacy=false, useFourthLegacy=false, useFifthLegacy=false, useSixthLegacy=false, useSeventhLegacy=false, useEighthLegacy=false, useNinthLegacy=false, useTenthLegacy=false;
static int StarterAssemblyImage(int img) {
 if(useTenthLegacy) {
  static const int tenth[]={CASTLE_EXTERIOR_03_FIRST_IMG+138,CASTLE_EXTERIOR_03_FIRST_IMG+126,
   CASTLE_10_HOLLOW_FIRST_IMG,CASTLE_HEAVY_CANNON_FIRST_IMG+48,CASTLE_COMMAND_PLATFORM_FIRST_IMG+48,
   CASTLE_02_10_COMBAT_DECK_FIRST_IMG+48,CASTLE_BASE_FIRST_IMG+54,CASTLE_WHEEL_FIRST_IMG+54,CASTLE_ROOM_V4_FIRST_IMG+54};
  for(int i=0;i<9;++i) if(img>=tenth[i] && img<tenth[i]+6)
   return CASTLE_TENTH_LEGACY_FIRST_IMG+(img-tenth[i])*9+i;
 }
 if(useNinthLegacy) {
  static const int ninth[]={CASTLE_EXTERIOR_03_FIRST_IMG+120,CASTLE_EXTERIOR_03_FIRST_IMG+108,
   CASTLE_09_HOLLOW_FIRST_IMG,CASTLE_HEAVY_CANNON_FIRST_IMG+42,CASTLE_COMMAND_PLATFORM_FIRST_IMG+42,
   CASTLE_02_10_COMBAT_DECK_FIRST_IMG+42,CASTLE_BASE_FIRST_IMG+48,CASTLE_WHEEL_FIRST_IMG+48,CASTLE_ROOM_V4_FIRST_IMG+48};
  for(int i=0;i<9;++i) if(img>=ninth[i] && img<ninth[i]+6)
   return CASTLE_NINTH_LEGACY_FIRST_IMG+(img-ninth[i])*9+i;
 }
 if(useEighthLegacy) {
  static const int eighth[]={CASTLE_EXTERIOR_03_FIRST_IMG+102,CASTLE_EXTERIOR_03_FIRST_IMG+90,
   CASTLE_08_HOLLOW_FIRST_IMG,CASTLE_HEAVY_CANNON_FIRST_IMG+36,CASTLE_COMMAND_PLATFORM_FIRST_IMG+36,
   CASTLE_02_10_COMBAT_DECK_FIRST_IMG+36,CASTLE_BASE_FIRST_IMG+42,CASTLE_WHEEL_FIRST_IMG+42,CASTLE_ROOM_V4_FIRST_IMG+42};
  for(int i=0;i<9;++i) if(img>=eighth[i] && img<eighth[i]+6)
   return CASTLE_EIGHTH_LEGACY_FIRST_IMG+(img-eighth[i])*9+i;
 }
 if(useSeventhLegacy) {
  static const int seventh[]={CASTLE_EXTERIOR_03_FIRST_IMG+84,CASTLE_EXTERIOR_03_FIRST_IMG+72,
   CASTLE_07_HOLLOW_FIRST_IMG,CASTLE_HEAVY_CANNON_FIRST_IMG+30,CASTLE_COMMAND_PLATFORM_FIRST_IMG+30,
   CASTLE_02_10_COMBAT_DECK_FIRST_IMG+30,CASTLE_BASE_FIRST_IMG+36,CASTLE_WHEEL_FIRST_IMG+36,CASTLE_ROOM_V4_FIRST_IMG+36};
  for(int i=0;i<9;++i) if(img>=seventh[i] && img<seventh[i]+6)
   return CASTLE_SEVENTH_LEGACY_FIRST_IMG+(img-seventh[i])*9+i;
 }
 if(useSixthLegacy) {
  static const int sixth[]={CASTLE_EXTERIOR_03_FIRST_IMG+66,CASTLE_EXTERIOR_03_FIRST_IMG+54,
   CASTLE_06_HOLLOW_FIRST_IMG,CASTLE_HEAVY_CANNON_FIRST_IMG+24,CASTLE_COMMAND_PLATFORM_FIRST_IMG+24,
   CASTLE_02_10_COMBAT_DECK_FIRST_IMG+24,CASTLE_BASE_FIRST_IMG+30,CASTLE_WHEEL_FIRST_IMG+30,CASTLE_ROOM_V4_FIRST_IMG+30};
  for(int i=0;i<9;++i) if(img>=sixth[i] && img<sixth[i]+6)
   return CASTLE_SIXTH_LEGACY_FIRST_IMG+(img-sixth[i])*9+i;
 }
 if(useFifthLegacy) {
  static const int fifth[]={CASTLE_EXTERIOR_03_FIRST_IMG+48,CASTLE_EXTERIOR_03_FIRST_IMG+36,
   CASTLE_05_HOLLOW_FIRST_IMG,CASTLE_HEAVY_CANNON_FIRST_IMG+18,CASTLE_COMMAND_PLATFORM_FIRST_IMG+18,
   CASTLE_02_10_COMBAT_DECK_FIRST_IMG+18,CASTLE_BASE_FIRST_IMG+24,CASTLE_WHEEL_FIRST_IMG+24,CASTLE_ROOM_V4_FIRST_IMG+24};
  for(int i=0;i<9;++i) if(img>=fifth[i] && img<fifth[i]+6)
   return CASTLE_FIFTH_LEGACY_FIRST_IMG+(img-fifth[i])*9+i;
 }
 if(useFourthLegacy) {
  static const int fourth[]={CASTLE_EXTERIOR_03_FIRST_IMG+30,CASTLE_EXTERIOR_03_FIRST_IMG+18,
   CASTLE_04_HOLLOW_FIRST_IMG,CASTLE_HEAVY_CANNON_FIRST_IMG+12,CASTLE_COMMAND_PLATFORM_FIRST_IMG+12,
   CASTLE_02_10_COMBAT_DECK_FIRST_IMG+12,CASTLE_BASE_FIRST_IMG+18,CASTLE_WHEEL_FIRST_IMG+18,CASTLE_ROOM_V4_FIRST_IMG+18};
  for(int i=0;i<9;++i) if(img>=fourth[i] && img<fourth[i]+6)
   return CASTLE_FOURTH_LEGACY_FIRST_IMG+(img-fourth[i])*9+i;
 }
 if(useThirdLegacy) {
  static const int third[]={CASTLE_EXTERIOR_03_FIRST_IMG+12,CASTLE_EXTERIOR_03_FIRST_IMG,
   CASTLE_03_HOLLOW_FIRST_IMG,CASTLE_HEAVY_CANNON_FIRST_IMG+6,CASTLE_COMMAND_PLATFORM_FIRST_IMG+6,
   CASTLE_02_10_COMBAT_DECK_FIRST_IMG+6,CASTLE_BASE_FIRST_IMG+12,CASTLE_WHEEL_FIRST_IMG+12,CASTLE_ROOM_V4_FIRST_IMG+12};
  for(int i=0;i<9;++i) if(img>=third[i] && img<third[i]+6)
   return CASTLE_THIRD_LEGACY_FIRST_IMG+(img-third[i])*9+i;
 }
 if(useSecondLegacy) {
  static const int second[]={CASTLE_ROOF_02_FIRST_IMG,CASTLE_WALL_02_FIRST_IMG,
   CASTLE_02_HOLLOW_FIRST_IMG,CASTLE_HEAVY_CANNON_FIRST_IMG,CASTLE_COMMAND_PLATFORM_FIRST_IMG,
   CASTLE_02_10_COMBAT_DECK_FIRST_IMG,CASTLE_BASE_FIRST_IMG+6,CASTLE_WHEEL_FIRST_IMG+6,CASTLE_ROOM_V4_FIRST_IMG+6};
  for(int i=0;i<9;++i) if(img>=second[i] && img<second[i]+6)
   return CASTLE_SECOND_LEGACY_FIRST_IMG+(img-second[i])*9+i;
 }
 if(!useStarterLegacy) return img;
 static const int originals[]={CASTLE_ROOF_01_FIRST_IMG,CASTLE_WALL_01_FIRST_IMG,
  CASTLE_01_HOLLOW_FIRST_IMG,CASTLE_01_CANNON_FIRST_IMG,CASTLE_BALCONY_01_FIRST_IMG,
  CASTLE_01_COMBAT_DECK_FIRST_IMG,CASTLE_BASE_FIRST_IMG,CASTLE_WHEEL_FIRST_IMG,CASTLE_ROOM_V4_FIRST_IMG};
 for(int i=0;i<9;++i) if(img>=originals[i] && img<originals[i]+6)
  return CASTLE_STARTER_LEGACY_FIRST_IMG+(img-originals[i])*9+i;
 return img;
}

//옛 모듈러 조각(castle_parts/*)을 집던 AssetId 는 지웠다. 부르는 데가
//없었고, 그림 250 장도 이미 없어서 이름표만 차지하고 있었다. 지금은
//RoomV4 + 외장 파츠로 조립한다.
static int RoomV4AssetId(int floor,int stage) {
 return CASTLE_ROOM_V4_FIRST_IMG+floor*6+stage;
}
//---- 거울 ----
//
//PVP 격돌에서 오른쪽 성은 왼쪽을 봐야 한다. 조립 렌더러는 그림 수십 장을
//제자리에 찍으므로, 찍는 자리를 하나하나 다시 재는 대신 마지막 한 줄에서
//좌표를 세로선 기준으로 접고 그림에 flipX 를 건다.
//
//gMirrorAxis 는 접는 세로선(화면 x)이다. 성의 한가운데를 넣으면 제자리에
//선 채로 방향만 돌아선다.
//
//조립 좌표를 적어 두는 칸(roomCover, cannonMuzzle) 은 접지 않는다. 그
//값을 읽어 다시 그리는 쪽이 저마다 접어야 하고, 접힌 좌표를 또 접으면
//제자리로 돌아온다.
static bool gMirror=false;
static float gMirrorAxis=0.0f;

//---- 부른 쪽이 자리를 정한다 ----
//
//SD 조립은 성 1~3 말고는 왼쪽 끝으로 붙여 버린다(아래 p.left). 로비와
//전투는 성이 화면 왼쪽에 서는 화면이라 그게 맞다.
//
//PVP 격돌은 둘이 좌우에 마주 서고, 들어올 때는 화면 밖에서 밀려 들어
//온다. 왼쪽 끝으로 붙여 버리면 오른쪽 성이 제자리에 못 서고 들어오는
//것도 안 보인다. 이 깃발이 서 있으면 부른 쪽이 준 x 를 그대로 쓴다.
static bool gFreePlace=false;

//접힌 자리. drawW 는 화면에 그려질 폭이다(원본 폭 * 배율).
static inline float MirrorX(float x,float drawW) {
 return gMirror ? (gMirrorAxis*2.0f-x-drawW) : x;
}

static void DrawRoomV4(int floor,int stage,float x,float yTop,float scale) {
 const int img=StarterAssemblyImage(RoomV4AssetId(floor,stage));
 if(!sprite[img]) LoadImg(img);
 if(!sprite[img]) { missingAsset=true; return; }
 DrawImage(512,128,0,0,(int)std::lround(MirrorX(x,512.0f*scale)),(int)std::lround(yTop),gMirror,0,0,0,0,scale,sprite[img],img);
}
static void DrawFixedAsset(int img,int sourceW,int sourceH,float x,float yTop,float scale) {
 img=StarterAssemblyImage(img);
 if(!sprite[img]) LoadImg(img);
 if(!sprite[img]) { missingAsset=true; return; }
 DrawImage(sourceW,sourceH,0,0,(int)std::lround(MirrorX(x,(float)sourceW*scale)),(int)std::lround(yTop),gMirror,0,0,0,0,scale,sprite[img],img);
}
static void DrawFixedAssetRegion(int img,int sourceW,int sourceH,int sourceY,
                                 float x,float yTop,float scale) {
 img=StarterAssemblyImage(img);
 if(!sprite[img]) LoadImg(img);
 if(!sprite[img]) { missingAsset=true; return; }
 DrawImage(sourceW,sourceH,0,sourceY,(int)std::lround(MirrorX(x,(float)sourceW*scale)),(int)std::lround(yTop),
           gMirror,0,0,0,0,scale,sprite[img],img);
}
static void DrawFixedAssetScale(int img,int sourceW,int sourceH,int x,int yTop,float scaleX,float scaleY) {
 img=StarterAssemblyImage(img);
 if(!sprite[img]) LoadImg(img);
 if(!sprite[img]) { missingAsset=true; return; }
 DrawImageScale(sourceW,sourceH,0,0,(int)MirrorX((float)x,(float)sourceW*scaleX),yTop,gMirror,0,0,0,0,scaleX,scaleY,sprite[img],img);
}
static void DrawRoomV4Scale(int floor,int stage,int x,int yTop,float scaleX,float scaleY) {
 const int img=StarterAssemblyImage(RoomV4AssetId(floor,stage));
 if(!sprite[img]) LoadImg(img);
 if(!sprite[img]) { missingAsset=true; return; }
 DrawImageScale(512,128,0,0,(int)MirrorX((float)x,512.0f*scaleX),yTop,gMirror,0,0,0,0,scaleX,scaleY,sprite[img],img);
}
//바퀴 그림 128 칸 안쪽의 투명 여백. 실제 바퀴는 이만큼 작다. 이걸 빼먹고
//칸 크기로 맞추면 바퀴가 땅에서 뜬 채로 돈다.
static const float kWheelPad=7.0f;

//바퀴가 땅을 구르는 각도. 속도를 따로 정하지 않는다.
//
//예전에는 frame*0.5(초당 30도) 였다. 땅은 초당 75 픽셀쯤 흐르는데 지름
//76 픽셀짜리 바퀴가 30 도만 돌면 바퀴가 미끄러진다. 굴러간 거리를
//반지름으로 나누면 각도가 그대로 나온다 - 배율이나 속도를 고쳐도 다시
//맞출 일이 없다.
static float WheelAngleNow(float radiusPx) {
 if(radiusPx<0.5f) return 0.0f;
 float travel=StageBgRailTravelPx();
 // The title castle preview has no scrolling rail, but still needs to roll.
 if(active && drawHandle==MD_TITLE) {
  static const auto started=std::chrono::steady_clock::now();
  const auto now=std::chrono::steady_clock::now();
  travel=std::chrono::duration_cast<std::chrono::milliseconds>(now-started).count()*0.075f;
 }
 return std::fmod(travel/radiusPx*57.29578f,360.0f);
}
static void DrawWheelAsset(int img,float centerX,float centerY,float scale,float angle) {
 img=StarterAssemblyImage(img);
 if(!sprite[img]) LoadImg(img);
 if(!sprite[img]) { missingAsset=true; return; }
 RotateImage(128,128,0,0,(int)centerX,(int)centerY,false,angle,0,0,scale,
             cocos2d::Vec2(.5f,.5f),sprite[img],img);
}
static int BaseAssetId(int castle,int stage) {
 return CASTLE_BASE_FIRST_IMG+castle*6+stage;
}
static int WheelAssetId(int castle,int stage) {
 return CASTLE_WHEEL_FIRST_IMG+castle*6+stage;
}
static int Balcony01AssetId(int stage) {
 return CASTLE_BALCONY_01_FIRST_IMG+stage;
}
static int WallAssetId(int castle,int stage) {
 if(castle==0) return CASTLE_WALL_01_FIRST_IMG+stage;
 if(castle==1) return CASTLE_WALL_02_FIRST_IMG+stage;
 return CASTLE_EXTERIOR_03_FIRST_IMG+(castle-2)*18+stage;
}
static int BalconyAssetId(int castle,int stage) {
 if(castle==0) return CASTLE_BALCONY_01_FIRST_IMG+stage;
 if(castle==1) return CASTLE_BALCONY_02_FIRST_IMG+stage;
 return CASTLE_EXTERIOR_03_FIRST_IMG+(castle-2)*18+6+stage;
}
static int RoofAssetId(int castle,int stage) {
 if(castle==0) return CASTLE_ROOF_01_FIRST_IMG+stage;
 if(castle==1) return CASTLE_ROOF_02_FIRST_IMG+stage;
 return CASTLE_EXTERIOR_03_FIRST_IMG+(castle-2)*18+12+stage;
}
static int HollowAssetId(int castle,int stage) {
 static const int first[9]={
  CASTLE_02_HOLLOW_FIRST_IMG,CASTLE_03_HOLLOW_FIRST_IMG,
  CASTLE_04_HOLLOW_FIRST_IMG,CASTLE_05_HOLLOW_FIRST_IMG,
  CASTLE_06_HOLLOW_FIRST_IMG,CASTLE_07_HOLLOW_FIRST_IMG,
  CASTLE_08_HOLLOW_FIRST_IMG,CASTLE_09_HOLLOW_FIRST_IMG,
  CASTLE_10_HOLLOW_FIRST_IMG
 };
 return first[castle-1]+stage;
}
//옛 모듈러 조각을 그리던 DrawAsset 도 같이 지웠다. AssetId 와 마찬가지로
//부르는 데가 없었다.
// Distance from the assembly origin to the first room. Every castle now
// uses wheels, so the floor/base/wheel seam shares one coordinate system.
static const float kRoomStackLift=172.0f;
static float NaturalLowerH(int castle) { (void)castle; return 236.0f; }
static float NaturalBodyLift(int castle) { (void)castle; return 16.0f; }
static float StarterLegacyGroundOffset(void) {
 return NaturalLowerH(0)+NaturalBodyLift(0)-144.0f-61.0f;
}
static float NaturalUpperH(int castle) {
 static const float heights[10]={256.0f,220.0f,197.0f,340.0f,300.0f,320.0f,320.0f,320.0f,320.0f,330.0f};
 return heights[Max(0,Min(9,castle))];
}
static int LeftArmorW(int castle) {
 return castle==0?160:140+12*(castle+1);
}
static int RightArmorW(int castle) {
 return castle==0?160:110+10*(castle+1);
}
static float CannonGrowth(int castle,int stage) {
 static const float fit[6]={1.75f,1.50f,1.30f,1.16f,1.07f,1.0f};
 return (2.4f+0.09f*castle)*fit[Max(0,Min(5,stage))]*(castle==0?1.30f:1.0f);
}
static float NaturalCastleW(int castle) {
 if(castle==0) return 960.0f;
 // The prow cannon projects farther right as the castle grows. Include it
 // in the camera bounds so the last castle does not lose its muzzle.
 return LeftArmorW(castle)+640.0f+90.0f*CannonGrowth(castle,5);
}
// Room and wall rectangles meet at the same coordinate, but their artwork
// has transparent edge pixels. A narrow material-colored backing closes the
// resulting see-through seam without moving either sprite or covering rooms.
static int WallRoomSeamColor(int castle) {
 static const int colors[9]={
  0x716B63, // stone and iron
  0x864736, // red brick
  0xB7AA8D, // limestone
  0x47786D, // oxidized copper
  0x4C3D3B, // black iron
  0xA0C6D5, // ice
  0x655078, // amethyst
  0x494047, // obsidian
  0xCDBF9D  // celestial marble
 };
 return colors[Max(0,Min(8,castle-1))];
}
static void DrawWallRoomSeamBacking(int castle,float roomLeft,float bottom,
                                    float scale,int wallH) {
 const int yTop=(int)std::lround(bottom+wallH*scale);
 const int yBottom=(int)std::lround(bottom);
 const int roomLeftPx=(int)std::lround(roomLeft);
 const int roomRightPx=(int)std::lround(roomLeft+512.0f*scale);
 const int outer=(int)std::ceil(32.0f*scale);
 const int inner=(int)std::ceil(20.0f*scale);
 const int color=WallRoomSeamColor(castle);
 MemRect((int)MirrorX((float)(roomLeftPx-outer),(float)(outer+inner)),yTop,outer+inner,yTop-yBottom,color);
 MemRect((int)MirrorX((float)(roomRightPx-inner),(float)(outer+inner)),yTop,outer+inner,yTop-yBottom,color);
}
// Debug facade experiment. Geometry comes from the canonical castle draw.
#ifndef CASTLE_DEBUG_ROOM_COVER
#define CASTLE_DEBUG_ROOM_COVER 1
#endif
struct RoomCoverRect { int left=0,top=0,width=0,height=0,material=0,sx=0,sy=0,sw=0,sh=0,roof=0; float scale=1,roofX=0,roofY=0; };
static RoomCoverRect roomCover[CastleCount];
static bool roomCoverRevealed[CastleCount]={};
static bool roomInteriorOpen[CastleCount]={};
struct SdPlacement {
 bool valid=false; int externalCount=0,residentCount=0; float left=0,top=0,width=0,height=0,scale=1;
 int residentDrawCount=0,castle=0,roomCount=1,roomColumns=1,sourceWidth=1536; float roomFloorGap=0;
 float wheelAngle=0,fitScale=1;
 float interiorLeft=0,interiorTop=0,interiorWidth=0,interiorFloor=0;
 float commanderX=0,commanderY=0,deckLeft=0,deckTop=0,deckWidth=0,deckSurface=0;
};
static SdPlacement sdPlacement;
static const float kStarterViewportRatio=.55f; // Latest request: 10% larger than the half-screen sample.
static const float kStarterRailOverlapPx=8.0f;
static bool SdEnabled(int castle) {
 if(!getenv("CS_LEGACY_CASTLE_ART")) return castle>=0 && castle<10;
#if defined(_DEBUG)
 if(castle<0 || castle>9 || active) return false;
 return true;
#else
 return false;
#endif
}
static const StarterSdParts::Piece& SdStagePiece(int part,int level,int castle=0) {
 if(castle==9) {
  static const StarterSdParts::Piece* const tenth[]={TenthSdParts::Pieces,
   TenthSdPartsStage1::Pieces,TenthSdPartsStage2::Pieces,TenthSdPartsStage3::Pieces,
   TenthSdPartsStage4::Pieces,TenthSdPartsStage5::Pieces};
  return tenth[Max(0,Min(5,level))][part];
 }
 if(castle==8) {
  static const StarterSdParts::Piece* const ninth[]={NinthSdParts::Pieces,
   NinthSdPartsStage1::Pieces,NinthSdPartsStage2::Pieces,NinthSdPartsStage3::Pieces,
   NinthSdPartsStage4::Pieces,NinthSdPartsStage5::Pieces};
  return ninth[Max(0,Min(5,level))][part];
 }
 if(castle==7) {
  static const StarterSdParts::Piece* const eighth[]={EighthSdParts::Pieces,
   EighthSdPartsStage1::Pieces,EighthSdPartsStage2::Pieces,EighthSdPartsStage3::Pieces,
   EighthSdPartsStage4::Pieces,EighthSdPartsStage5::Pieces};
  return eighth[Max(0,Min(5,level))][part];
 }
 if(castle==6) {
  static const StarterSdParts::Piece* const seventh[]={SeventhSdParts::Pieces,
   SeventhSdPartsStage1::Pieces,SeventhSdPartsStage2::Pieces,SeventhSdPartsStage3::Pieces,
   SeventhSdPartsStage4::Pieces,SeventhSdPartsStage5::Pieces};
  return seventh[Max(0,Min(5,level))][part];
 }
 if(castle==5) {
  static const StarterSdParts::Piece* const sixth[]={SixthSdParts::Pieces,
   SixthSdPartsStage1::Pieces,SixthSdPartsStage2::Pieces,SixthSdPartsStage3::Pieces,
   SixthSdPartsStage4::Pieces,SixthSdPartsStage5::Pieces};
  return sixth[Max(0,Min(5,level))][part];
 }
 if(castle==4) {
  static const StarterSdParts::Piece* const fifth[]={FifthSdParts::Pieces,
   FifthSdPartsStage1::Pieces,FifthSdPartsStage2::Pieces,FifthSdPartsStage3::Pieces,
   FifthSdPartsStage4::Pieces,FifthSdPartsStage5::Pieces};
  return fifth[Max(0,Min(5,level))][part];
 }
 if(castle==3) {
  static const StarterSdParts::Piece* const fourth[]={FourthSdParts::Pieces,
   FourthSdPartsStage1::Pieces,FourthSdPartsStage2::Pieces,FourthSdPartsStage3::Pieces,
   FourthSdPartsStage4::Pieces,FourthSdPartsStage5::Pieces};
  return fourth[Max(0,Min(5,level))][part];
 }
 if(castle==2) {
  static const StarterSdParts::Piece* const third[]={ThirdSdParts::Pieces,
   ThirdSdPartsStage1::Pieces,ThirdSdPartsStage2::Pieces,ThirdSdPartsStage3::Pieces,
   ThirdSdPartsStage4::Pieces,ThirdSdPartsStage5::Pieces};
  return third[Max(0,Min(5,level))][part];
 }
 if(castle==1) {
  static const StarterSdParts::Piece* const second[]={SecondSdParts::Pieces,
   SecondSdPartsStage1::Pieces,SecondSdPartsStage2::Pieces,SecondSdPartsStage3::Pieces,
   SecondSdPartsStage4::Pieces,SecondSdPartsStage5::Pieces};
  return second[Max(0,Min(5,level))][part];
 }
 static const StarterSdParts::Piece* const stages[]={StarterSdParts::Pieces,
  StarterSdPartsStage1::Pieces,StarterSdPartsStage2::Pieces,StarterSdPartsStage3::Pieces,
  StarterSdPartsStage4::Pieces,StarterSdPartsStage5::Pieces};
 return stages[Max(0,Min(5,level))][part];
}
static void SdPiece(int img,const StarterSdParts::Piece& r,float unit,float left,float top,bool flipX=false) {
 if(!sprite[img]) LoadImg(img);
 if(!sprite[img]) { missingAsset=true; return; }
 const int x=(int)std::lround(left+r.x*unit), y=(int)std::lround(top-r.y*unit);
 const int right=(int)std::lround(left+(r.x+r.w)*unit), bottom=(int)std::lround(top-(r.y+r.h)*unit);
 DrawImageScale(r.w,r.h,r.sx,r.sy,MirrorX(x,r.w*unit),y,flipX!=gMirror,0,0,0,0,
     (right-x)/(float)r.w,(y-bottom)/(float)r.h,sprite[img],img);
}
static int SdTopVisibleY(int castle,int stage) {
 if(castle==9) {
  const int tops[]={TenthSdParts::TopVisibleY,TenthSdPartsStage1::TopVisibleY,
   TenthSdPartsStage2::TopVisibleY,TenthSdPartsStage3::TopVisibleY,
   TenthSdPartsStage4::TopVisibleY,TenthSdPartsStage5::TopVisibleY};
  return tops[Max(0,Min(5,stage))];
 }
 if(castle==8) {
  const int tops[]={NinthSdParts::TopVisibleY,NinthSdPartsStage1::TopVisibleY,
   NinthSdPartsStage2::TopVisibleY,NinthSdPartsStage3::TopVisibleY,
   NinthSdPartsStage4::TopVisibleY,NinthSdPartsStage5::TopVisibleY};
  return tops[Max(0,Min(5,stage))];
 }
 if(castle==7) {
  const int tops[]={EighthSdParts::TopVisibleY,EighthSdPartsStage1::TopVisibleY,
   EighthSdPartsStage2::TopVisibleY,EighthSdPartsStage3::TopVisibleY,
   EighthSdPartsStage4::TopVisibleY,EighthSdPartsStage5::TopVisibleY};
  return tops[Max(0,Min(5,stage))];
 }
 if(castle==6) {
  const int tops[]={SeventhSdParts::TopVisibleY,SeventhSdPartsStage1::TopVisibleY,
   SeventhSdPartsStage2::TopVisibleY,SeventhSdPartsStage3::TopVisibleY,
   SeventhSdPartsStage4::TopVisibleY,SeventhSdPartsStage5::TopVisibleY};
  return tops[Max(0,Min(5,stage))];
 }
 if(castle==5) {
  const int tops[]={SixthSdParts::TopVisibleY,SixthSdPartsStage1::TopVisibleY,
   SixthSdPartsStage2::TopVisibleY,SixthSdPartsStage3::TopVisibleY,
   SixthSdPartsStage4::TopVisibleY,SixthSdPartsStage5::TopVisibleY};
  return tops[Max(0,Min(5,stage))];
 }
 if(castle==4) {
  const int tops[]={FifthSdParts::TopVisibleY,FifthSdPartsStage1::TopVisibleY,
   FifthSdPartsStage2::TopVisibleY,FifthSdPartsStage3::TopVisibleY,
   FifthSdPartsStage4::TopVisibleY,FifthSdPartsStage5::TopVisibleY};
  return tops[Max(0,Min(5,stage))];
 }
 if(castle==3) {
  const int tops[]={FourthSdParts::TopVisibleY,FourthSdPartsStage1::TopVisibleY,
   FourthSdPartsStage2::TopVisibleY,FourthSdPartsStage3::TopVisibleY,
   FourthSdPartsStage4::TopVisibleY,FourthSdPartsStage5::TopVisibleY};
  return tops[Max(0,Min(5,stage))];
 }
 return SdStagePiece(0,stage,castle).y;
}
static cocos2d::Vec2 SdUniformOffset(int castle,int part) {
 if(castle<5) return cocos2d::Vec2::ZERO;
 const auto* stages=UniformCastleAnchors::Stages[castle-5];
 const auto& body=stages[CastleVisualPartLevel(castle,1)];
 const auto& base=stages[CastleVisualPartLevel(castle,4)];
 const auto& roof=stages[CastleVisualPartLevel(castle,0)];
 const auto& gun=stages[CastleVisualPartLevel(castle,3)];
 const cocos2d::Vec2 shift(base.hullX-body.hullX,base.deckY-body.deckY);
 if(part==0) return cocos2d::Vec2(base.hullX-roof.hullX,shift.y+body.roofY-roof.roofY);
 if(part==1 || part==2) return shift;
 if(part==3 || part==4) return cocos2d::Vec2(shift.x+body.gunX-gun.gunX,base.deckY-gun.deckY);
 return cocos2d::Vec2::ZERO;
}
static bool DrawSdCastle(int castle,float left,float bottom,float scale) {
 if(!SdEnabled(castle)) { sdPlacement.valid=false; return false; }
 auto& p=sdPlacement; p.valid=true; p.castle=castle; p.roomCount=castle+1;
 const int sourceW=castle==9?TenthSdParts::Width:castle==8?NinthSdParts::Width:castle==7?EighthSdParts::Width:castle==6?SeventhSdParts::Width:castle==5?SixthSdParts::Width:castle==4?FifthSdParts::Width:castle==3?FourthSdParts::Width:castle==2?ThirdSdParts::Width:castle?SecondSdParts::Width:StarterSdParts::Width;
 const int sourceH=castle==9?TenthSdParts::Height:castle==8?NinthSdParts::Height:castle==7?EighthSdParts::Height:castle==6?SeventhSdParts::Height:castle==5?SixthSdParts::Height:castle==4?FifthSdParts::Height:castle==3?FourthSdParts::Height:castle==2?ThirdSdParts::Height:castle?SecondSdParts::Height:StarterSdParts::Height;
 const int ground=castle==9?TenthSdParts::GroundY:castle==8?NinthSdParts::GroundY:castle==7?EighthSdParts::GroundY:castle==6?SeventhSdParts::GroundY:castle==5?SixthSdParts::GroundY:castle==4?FifthSdParts::GroundY:castle==3?FourthSdParts::GroundY:castle==2?ThirdSdParts::GroundY:castle?SecondSdParts::GroundY:StarterSdParts::GroundY;
 const int floor=castle==9?TenthSdParts::FloorY:castle==8?NinthSdParts::FloorY:castle==7?EighthSdParts::FloorY:castle==6?SeventhSdParts::FloorY:castle==5?SixthSdParts::FloorY:castle==4?FifthSdParts::FloorY:castle==3?FourthSdParts::FloorY:castle==2?ThirdSdParts::FloorY:castle?SecondSdParts::FloorY:StarterSdParts::FloorY;
 const int heroX=castle==9?TenthSdParts::HeroX:castle==8?NinthSdParts::HeroX:castle==7?EighthSdParts::HeroX:castle==6?SeventhSdParts::HeroX:castle==5?SixthSdParts::HeroX:castle==4?FifthSdParts::HeroX:castle==3?FourthSdParts::HeroX:castle==2?ThirdSdParts::HeroX:castle?SecondSdParts::HeroX:StarterSdParts::HeroX;
 const int heroY=castle==9?TenthSdParts::HeroY:castle==8?NinthSdParts::HeroY:castle==7?EighthSdParts::HeroY:castle==6?SeventhSdParts::HeroY:castle==5?SixthSdParts::HeroY:castle==4?FifthSdParts::HeroY:castle==3?FourthSdParts::HeroY:castle==2?ThirdSdParts::HeroY:castle?SecondSdParts::HeroY:StarterSdParts::HeroY;
 const int deckX=castle==9?TenthSdParts::DeckX:castle==8?NinthSdParts::DeckX:castle==7?EighthSdParts::DeckX:castle==6?SeventhSdParts::DeckX:castle==5?SixthSdParts::DeckX:castle==4?FifthSdParts::DeckX:castle==3?FourthSdParts::DeckX:castle==2?ThirdSdParts::DeckX:castle?SecondSdParts::DeckX:StarterSdParts::DeckX;
 const int deckW=castle==9?TenthSdParts::DeckW:castle==8?NinthSdParts::DeckW:castle==7?EighthSdParts::DeckW:castle==6?SeventhSdParts::DeckW:castle==5?SixthSdParts::DeckW:castle==4?FifthSdParts::DeckW:castle==3?FourthSdParts::DeckW:castle==2?ThirdSdParts::DeckW:castle?SecondSdParts::DeckW:StarterSdParts::DeckW;
 const int deckY=castle==9?TenthSdParts::DeckY:castle==8?NinthSdParts::DeckY:castle==7?EighthSdParts::DeckY:castle==6?SeventhSdParts::DeckY:castle==5?SixthSdParts::DeckY:castle==4?FifthSdParts::DeckY:castle==3?FourthSdParts::DeckY:castle==2?ThirdSdParts::DeckY:castle?SecondSdParts::DeckY:StarterSdParts::DeckY;
 const auto& room=castle==9?TenthSdParts::Room:castle==8?NinthSdParts::Room:castle==7?EighthSdParts::Room:castle==6?SeventhSdParts::Room:castle==5?SixthSdParts::Room:castle==4?FifthSdParts::Room:castle==3?FourthSdParts::Room:castle==2?ThirdSdParts::Room:castle?SecondSdParts::Room:StarterSdParts::Room;
 p.sourceWidth=sourceW;
 const float naturalUnit=Min(960.0f*1.10f/sourceW*scale,DX*kStarterViewportRatio/sourceW);
 const float groundLine=bottom-252*scale+(castle?54.0f:StarterLegacyGroundOffset())*scale+StageCastleGroundingPx()-kStarterRailOverlapPx;
 const bool worldView=!gFreePlace
  && (drawHandle==MD_PLAY || (drawHandle==MD_LOBBY && popUpCnt==0));
 // Castle grades share one screen width. Taller art grows above the rail;
 // neither the legacy assembly height nor the viewport roof can shrink it.
 const float unit=worldView?DX*kStarterViewportRatio/sourceW:naturalUnit;
 p.fitScale=unit/naturalUnit;
 p.scale=unit*sourceW/960.0f;
 // The caller has already subtracted the legacy contact offset and grounding.
 // Cancel those once, then place the authored wheel contact on the actual rail.
 p.left=(!gFreePlace && (worldView || castle>=3))?Max(4.0f*DX/640.0f,left):left;
 p.top=groundLine+ground*unit;
 p.width=sourceW*unit; p.height=sourceH*unit;
 // Actual existing resource IDs, not a baked castle or a replacement atlas.
 int images[9]={CASTLE_ROOF_01_FIRST_IMG,CASTLE_WALL_01_FIRST_IMG,
  CASTLE_01_HOLLOW_FIRST_IMG,CASTLE_01_CANNON_FIRST_IMG,CASTLE_BALCONY_01_FIRST_IMG,
  CASTLE_01_COMBAT_DECK_FIRST_IMG,CASTLE_BASE_FIRST_IMG,CASTLE_WHEEL_FIRST_IMG,CASTLE_WHEEL_FIRST_IMG};
 if(castle==1) {
  const int second[]={CASTLE_ROOF_02_FIRST_IMG,CASTLE_WALL_02_FIRST_IMG,CASTLE_02_HOLLOW_FIRST_IMG,
   CASTLE_HEAVY_CANNON_FIRST_IMG,CASTLE_COMMAND_PLATFORM_FIRST_IMG,CASTLE_02_10_COMBAT_DECK_FIRST_IMG,
   CASTLE_BASE_FIRST_IMG+6,CASTLE_WHEEL_FIRST_IMG+6,CASTLE_WHEEL_FIRST_IMG+6};
  for(int i=0;i<9;++i) images[i]=second[i];
 }
 if(castle==2) {
  const int third[]={CASTLE_EXTERIOR_03_FIRST_IMG+12,CASTLE_EXTERIOR_03_FIRST_IMG,CASTLE_03_HOLLOW_FIRST_IMG,
   CASTLE_HEAVY_CANNON_FIRST_IMG+6,CASTLE_COMMAND_PLATFORM_FIRST_IMG+6,CASTLE_02_10_COMBAT_DECK_FIRST_IMG+6,
   CASTLE_BASE_FIRST_IMG+12,CASTLE_WHEEL_FIRST_IMG+12,CASTLE_WHEEL_FIRST_IMG+12};
  for(int i=0;i<9;++i) images[i]=third[i];
 }
 if(castle==9) {
  const int tenth[]={CASTLE_EXTERIOR_03_FIRST_IMG+138,CASTLE_EXTERIOR_03_FIRST_IMG+126,CASTLE_10_HOLLOW_FIRST_IMG,
   CASTLE_HEAVY_CANNON_FIRST_IMG+48,CASTLE_COMMAND_PLATFORM_FIRST_IMG+48,CASTLE_02_10_COMBAT_DECK_FIRST_IMG+48,
   CASTLE_BASE_FIRST_IMG+54,CASTLE_WHEEL_FIRST_IMG+54,CASTLE_WHEEL_FIRST_IMG+54};
  for(int i=0;i<9;++i) images[i]=tenth[i];
 }
 if(castle==8) {
  const int ninth[]={CASTLE_EXTERIOR_03_FIRST_IMG+120,CASTLE_EXTERIOR_03_FIRST_IMG+108,CASTLE_09_HOLLOW_FIRST_IMG,
   CASTLE_HEAVY_CANNON_FIRST_IMG+42,CASTLE_COMMAND_PLATFORM_FIRST_IMG+42,CASTLE_02_10_COMBAT_DECK_FIRST_IMG+42,
   CASTLE_BASE_FIRST_IMG+48,CASTLE_WHEEL_FIRST_IMG+48,CASTLE_WHEEL_FIRST_IMG+48};
  for(int i=0;i<9;++i) images[i]=ninth[i];
 }
 if(castle==7) {
  const int eighth[]={CASTLE_EXTERIOR_03_FIRST_IMG+102,CASTLE_EXTERIOR_03_FIRST_IMG+90,CASTLE_08_HOLLOW_FIRST_IMG,
   CASTLE_HEAVY_CANNON_FIRST_IMG+36,CASTLE_COMMAND_PLATFORM_FIRST_IMG+36,CASTLE_02_10_COMBAT_DECK_FIRST_IMG+36,
   CASTLE_BASE_FIRST_IMG+42,CASTLE_WHEEL_FIRST_IMG+42,CASTLE_WHEEL_FIRST_IMG+42};
  for(int i=0;i<9;++i) images[i]=eighth[i];
 }
 if(castle==6) {
  const int seventh[]={CASTLE_EXTERIOR_03_FIRST_IMG+84,CASTLE_EXTERIOR_03_FIRST_IMG+72,CASTLE_07_HOLLOW_FIRST_IMG,
   CASTLE_HEAVY_CANNON_FIRST_IMG+30,CASTLE_COMMAND_PLATFORM_FIRST_IMG+30,CASTLE_02_10_COMBAT_DECK_FIRST_IMG+30,
   CASTLE_BASE_FIRST_IMG+36,CASTLE_WHEEL_FIRST_IMG+36,CASTLE_WHEEL_FIRST_IMG+36};
  for(int i=0;i<9;++i) images[i]=seventh[i];
 }
 if(castle==5) {
  const int sixth[]={CASTLE_EXTERIOR_03_FIRST_IMG+66,CASTLE_EXTERIOR_03_FIRST_IMG+54,CASTLE_06_HOLLOW_FIRST_IMG,
   CASTLE_HEAVY_CANNON_FIRST_IMG+24,CASTLE_COMMAND_PLATFORM_FIRST_IMG+24,CASTLE_02_10_COMBAT_DECK_FIRST_IMG+24,
   CASTLE_BASE_FIRST_IMG+30,CASTLE_WHEEL_FIRST_IMG+30,CASTLE_WHEEL_FIRST_IMG+30};
  for(int i=0;i<9;++i) images[i]=sixth[i];
 }
 if(castle==3) {
  const int fourth[]={CASTLE_EXTERIOR_03_FIRST_IMG+30,CASTLE_EXTERIOR_03_FIRST_IMG+18,CASTLE_04_HOLLOW_FIRST_IMG,
   CASTLE_HEAVY_CANNON_FIRST_IMG+12,CASTLE_COMMAND_PLATFORM_FIRST_IMG+12,CASTLE_02_10_COMBAT_DECK_FIRST_IMG+12,
   CASTLE_BASE_FIRST_IMG+18,CASTLE_WHEEL_FIRST_IMG+18,CASTLE_WHEEL_FIRST_IMG+18};
  for(int i=0;i<9;++i) images[i]=fourth[i];
 }
 if(castle==4) {
  const int fifth[]={CASTLE_EXTERIOR_03_FIRST_IMG+48,CASTLE_EXTERIOR_03_FIRST_IMG+36,CASTLE_05_HOLLOW_FIRST_IMG,
   CASTLE_HEAVY_CANNON_FIRST_IMG+18,CASTLE_COMMAND_PLATFORM_FIRST_IMG+18,CASTLE_02_10_COMBAT_DECK_FIRST_IMG+18,
   CASTLE_BASE_FIRST_IMG+24,CASTLE_WHEEL_FIRST_IMG+24,CASTLE_WHEEL_FIRST_IMG+24};
  for(int i=0;i<9;++i) images[i]=fifth[i];
 }
 const int levels[9]={CastleVisualPartLevel(castle,0),CastleVisualPartLevel(castle,1),CastleVisualPartLevel(castle,1),
  CastleVisualPartLevel(castle,3),CastleVisualPartLevel(castle,3),CastleVisualPartLevel(castle,4),
  CastleVisualPartLevel(castle,4),CastleVisualPartLevel(castle,4),CastleVisualPartLevel(castle,4)};
 for(int i=0;i<9;++i) images[i]+=levels[i];
 p.wheelAngle=WheelAngleNow((castle==9?TenthSdParts::WheelRadius:castle==8?NinthSdParts::WheelRadius:castle==7?EighthSdParts::WheelRadius:castle==6?SeventhSdParts::WheelRadius:castle==5?SixthSdParts::WheelRadius:castle==4?FifthSdParts::WheelRadius:castle==3?FourthSdParts::WheelRadius:castle==2?ThirdSdParts::WheelRadius:castle?102:121)*unit);
 for(int i=0;i<9;++i) if(i!=1) {
  auto r=SdStagePiece(i,levels[i],castle);
  const auto shift=SdUniformOffset(castle,i);
  r.x+=(int)std::lround(shift.x);r.y+=(int)std::lround(shift.y);
  // Use the authored weapon orientation without runtime mirroring.
  if(i<7) SdPiece(images[i],r,unit,p.left,p.top);
  else {
   if(!sprite[images[i]]) LoadImg(images[i]);
   if(!sprite[images[i]]) { missingAsset=true; continue; }
   RotateImage(r.w,r.h,r.sx,r.sy,(int)std::lround(p.left+(r.x+r.w*.5f)*unit),
    (int)std::lround(p.top-(r.y+r.h*.5f)*unit),false,WheelAngleNow(r.w*unit*.5f),0,0,unit,
    cocos2d::Vec2(.5f,.5f),sprite[images[i]],images[i]);
  }
 }
 auto roomDraw=room;
 const auto bodyShift=SdUniformOffset(castle,1);
 roomDraw.x+=(int)std::lround(bodyShift.x);roomDraw.y+=(int)std::lround(bodyShift.y);
 SdPiece(CASTLE_ROOM_V4_FIRST_IMG+castle*6+CastleVisualPartLevel(castle,2),roomDraw,unit,p.left,p.top);
 auto aperture=SdStagePiece(1,levels[1],castle);
 aperture.x+=(int)std::lround(bodyShift.x);aperture.y+=(int)std::lround(bodyShift.y);
 auto& cover=roomCover[castle];
 cover.left=(int)std::lround(p.left+aperture.x*unit);
 cover.top=(int)std::lround(p.top-aperture.y*unit);
 cover.width=(int)std::lround(p.left+(aperture.x+aperture.w)*unit)-cover.left;
 cover.height=cover.top-(int)std::lround(p.top-(aperture.y+aperture.h)*unit);
 cover.material=images[1]; cover.sx=cover.sy=0;
 cover.sw=aperture.w; cover.sh=aperture.h; cover.roof=0;
 if(!sprite[cover.material]) LoadImg(cover.material);
 // These views do not run the crew/cover pass, so draw the closed facade here.
 if(popUpCnt>0 || (drawHandle!=MD_LOBBY && drawHandle!=MD_PLAY))
  SdPiece(cover.material,aperture,unit,p.left,p.top);
 p.interiorLeft=cover.left; p.interiorTop=cover.top; p.interiorWidth=cover.width;
 p.interiorFloor=p.top-(floor+bodyShift.y)*unit; p.roomFloorGap=castle==9?TenthSdParts::RoomFloorGap*unit:castle==8?NinthSdParts::RoomFloorGap*unit:castle==7?EighthSdParts::RoomFloorGap*unit:castle==6?SeventhSdParts::RoomFloorGap*unit:castle==5?SixthSdParts::RoomFloorGap*unit:castle==4?FifthSdParts::RoomFloorGap*unit:castle==3?FourthSdParts::RoomFloorGap*unit:castle==2?ThirdSdParts::RoomFloorGap*unit:castle?172.5f*unit:0;
 p.commanderX=p.left+heroX*unit;
 p.commanderY=p.top-heroY*unit;
 p.deckLeft=p.left+deckX*unit; p.deckWidth=deckW*unit;
 p.deckSurface=p.top-deckY*unit; p.deckTop=p.deckSurface;
 cannonBaseY[castle]=p.commanderY;
 const int stoneXs[]={StarterSdParts::StoneX,StarterSdPartsStage1::StoneX,StarterSdPartsStage2::StoneX,
  StarterSdPartsStage3::StoneX,StarterSdPartsStage4::StoneX,StarterSdPartsStage5::StoneX};
 const int stoneYs[]={StarterSdParts::StoneY,StarterSdPartsStage1::StoneY,StarterSdPartsStage2::StoneY,
  StarterSdPartsStage3::StoneY,StarterSdPartsStage4::StoneY,StarterSdPartsStage5::StoneY};
 if(castle==9) {
  const int xs[]={TenthSdParts::StoneX,TenthSdPartsStage1::StoneX,TenthSdPartsStage2::StoneX,TenthSdPartsStage3::StoneX,TenthSdPartsStage4::StoneX,TenthSdPartsStage5::StoneX};
  const int ys[]={TenthSdParts::StoneY,TenthSdPartsStage1::StoneY,TenthSdPartsStage2::StoneY,TenthSdPartsStage3::StoneY,TenthSdPartsStage4::StoneY,TenthSdPartsStage5::StoneY};
  cannonMuzzleX[castle]=p.left+xs[levels[3]]*unit;
  cannonMuzzleY[castle]=p.top-ys[levels[3]]*unit; cannonMuzzleValid[castle]=true;
 } else  if(castle==8) {
  const int xs[]={NinthSdParts::StoneX,NinthSdPartsStage1::StoneX,NinthSdPartsStage2::StoneX,NinthSdPartsStage3::StoneX,NinthSdPartsStage4::StoneX,NinthSdPartsStage5::StoneX};
  const int ys[]={NinthSdParts::StoneY,NinthSdPartsStage1::StoneY,NinthSdPartsStage2::StoneY,NinthSdPartsStage3::StoneY,NinthSdPartsStage4::StoneY,NinthSdPartsStage5::StoneY};
  cannonMuzzleX[castle]=p.left+xs[levels[3]]*unit;
  cannonMuzzleY[castle]=p.top-ys[levels[3]]*unit; cannonMuzzleValid[castle]=true;
 } else {
 cannonMuzzleX[castle]=p.left+(castle==9?TenthSdParts::StoneX:castle==8?NinthSdParts::StoneX:castle==7?EighthSdParts::StoneX:castle==6?SeventhSdParts::StoneX:castle==5?SixthSdParts::StoneX:castle==4?FifthSdParts::StoneX:castle==3?FourthSdParts::StoneX:castle==2?ThirdSdParts::StoneX:castle?SecondSdParts::StoneX:stoneXs[levels[3]])*unit;
 cannonMuzzleY[castle]=p.top-(castle==9?TenthSdParts::StoneY:castle==8?NinthSdParts::StoneY:castle==7?EighthSdParts::StoneY:castle==6?SeventhSdParts::StoneY:castle==5?SixthSdParts::StoneY:castle==4?FifthSdParts::StoneY:castle==3?FourthSdParts::StoneY:castle==2?ThirdSdParts::StoneY:castle?SecondSdParts::StoneY:stoneYs[levels[3]])*unit; cannonMuzzleValid[castle]=true;
 }
 if(castle>=5) {
  const auto& hero=UniformCastleAnchors::Stages[castle-5][levels[4]];
  const auto& deck=UniformCastleAnchors::Stages[castle-5][levels[5]];
  const auto& gun=UniformCastleAnchors::Stages[castle-5][levels[3]];
  const auto shift=SdUniformOffset(castle,3);
  p.commanderX=p.left+(hero.heroX+shift.x)*unit; p.commanderY=p.top-(hero.heroY+shift.y)*unit;
  p.deckLeft=p.left+deck.deckX*unit; p.deckWidth=deck.deckW*unit;
  p.deckSurface=p.top-deck.deckY*unit; p.deckTop=p.deckSurface;
  cannonBaseY[castle]=p.commanderY;
  cannonMuzzleX[castle]=p.left+(gun.muzzleX+shift.x)*unit;
  cannonMuzzleY[castle]=p.top-(gun.muzzleY+shift.y)*unit;
 }
 for(int i=0;i<5;++i) {
  partAnchor[castle][i][0]=p.left+(i==3?.89f:.35f)*p.width;
  partAnchor[castle][i][1]=p.top-(i==0?.24f:i==4?.83f:.56f)*p.height;
 }
 return true;
}
static bool RoomRevealRequested(int castle) {
 if(castle<0 || castle>9 || active || popUpCnt>0 || (drawHandle!=MD_LOBBY && drawHandle!=MD_PLAY)) return false;
 const auto& r=roomCover[castle];
 if(r.width<=0 || r.height<=0 || !sprite[r.material]) return false;
 return roomInteriorOpen[castle];
}
struct RoomClipScope {
 int x,y,x2,y2; bool enabled;
 explicit RoomClipScope(bool on,int floor=0):x(clipX),y(clipY),x2(clipX2),y2(clipY2),enabled(on) {
  if(!on) return;
  const auto& r=roomCover[sdPlacement.castle];
  clipX=Max(clipX,r.left); clipX2=Min(clipX2,r.left+r.width);
  clipY=Min(clipY,r.top); clipY2=Max(clipY2,r.top-r.height);
  if(sdPlacement.roomCount>1) {
   const float gap=sdPlacement.roomFloorGap;
   clipY=Min(clipY,(int)std::lround(sdPlacement.interiorFloor+floor*gap+gap-4*sdPlacement.width/sdPlacement.sourceWidth));
   clipY2=Max(clipY2,(int)std::lround(sdPlacement.interiorFloor+floor*gap-10*sdPlacement.width/sdPlacement.sourceWidth));
  }
 }
 ~RoomClipScope() { if(enabled) { clipX=x; clipY=y; clipX2=x2; clipY2=y2; } }
};
static void DrawRoomCover(int castle) {
#if CASTLE_DEBUG_ROOM_COVER
 // Authored SD samples; other castles keep their original open rooms.
 if(castle<0 || castle>9 || active || popUpCnt>0 || (drawHandle!=MD_LOBBY && drawHandle!=MD_PLAY)) return;
 const auto& r=roomCover[castle];
 if(r.width<=0 || r.height<=0 || !sprite[r.material]) return;
 const bool reveal=RoomRevealRequested(castle);
 roomCoverRevealed[castle]=reveal;
 // Complete exteriors already draw the closed facade exactly once.
 if(r.material>=CASTLE_INDIVIDUAL_V4_FIRST_IMG && r.material<=CASTLE_INDIVIDUAL_V4_LAST_IMG && !reveal) return;
 const auto segment=[&](int a,int b,int row,int bh) {
  if(b<=a) return;
  const int sx=r.sx+(int)((a-r.left)*(float)r.sw/r.width);
  const int sy=r.sy+(int)(row*(float)r.sh/r.height);
  const int sw=Max(1,Min(r.sx+r.sw-sx,(int)std::ceil((b-a)*(float)r.sw/r.width)));
  const int sh=Max(1,Min(r.sy+r.sh-sy,(int)std::ceil(bh*(float)r.sh/r.height)));
  DrawImageScale(sw,sh,sx,sy,(int)MirrorX((float)a,(float)(b-a)),r.top-row,gMirror,0,0,0,0,
      (b-a)/(float)sw,bh/(float)sh,sprite[r.material],r.material);
 };
 if(!reveal) segment(r.left,r.left+r.width,0,r.height);
 // Restore the original roof in front of the facade: no wall can cover its spires.
 if(r.roof) DrawFixedAsset(r.roof,736,256,r.roofX,r.roofY,r.scale);
#endif
}
// Complete selected exterior; the legacy modular renderer remains available
// through CS_LEGACY_CASTLE_ART for room/upgrade authoring.
static bool IndividualArtEnabled() { return !getenv("CS_LEGACY_CASTLE_ART"); }
static bool DrawIndividualCastle(int castle,float left,float bottom,float scale) {
 if(!IndividualArtEnabled()) return false;
 const auto& r=IndividualCastleV4::Rigs[castle];
 const int img=CASTLE_INDIVIDUAL_V4_FIRST_IMG+castle*IndividualCastleV4::Stride;
 for(int i=0;i<=r.wheelCount;++i) { if(!sprite[img+i]) { LoadImg(img+i); LoadTexture(img+i); if(sprite[img+i]) sprite[img+i]->getTexture()->setAntiAliasTexParameters(); } if(!sprite[img+i]) { missingAsset=true; return false; } }
 const bool world=!gFreePlace && (drawHandle==MD_PLAY || (drawHandle==MD_LOBBY && popUpCnt==0));
 const float unit=world?DX/640.0f*r.width/r.w*CastlePartsViewZoom():1056.0f*(r.width/342.0f)/r.w*scale;
 const float ground=bottom-252*scale+(castle?54.0f:StarterLegacyGroundOffset())*scale+StageCastleGroundingPx()-kStarterRailOverlapPx;
 auto& p=sdPlacement; p=SdPlacement(); p.valid=true;p.castle=castle;p.roomCount=castle+1;
 p.left=world?CastlePartsViewLeft(Max(4.0f*DX/640.0f,left)):left;p.width=r.w*unit;p.height=r.h*unit;
 p.top=ground+p.height;p.sourceWidth=r.w;p.scale=p.width/960.0f;
 p.fitScale=unit/(1056.0f*(r.width/342.0f)/r.w*scale);
 // The approved image already contains the outdoor ledge and compact chassis.
 // Render it intact; never split/raise the upper body or add another deck.
 DrawImage(r.w,r.h,r.x,r.y,(int)std::lround(MirrorX(p.left,p.width)),
   (int)std::lround(p.top),gMirror,0,0,0,0,unit,sprite[img],img);
 const float angle=WheelAngleNow(r.wheels[0].r*unit);
 p.wheelAngle=angle;
 p.commanderX=p.left+(r.hero-r.x)*unit;p.commanderY=p.top-(r.floor-r.y)*unit;
 p.deckLeft=p.left+(r.deckX-r.x)*unit;p.deckWidth=r.deckW*unit;
 p.deckSurface=p.top-(r.deckY-r.y)*unit;p.deckTop=p.deckSurface;
 roomCover[castle]=RoomCoverRect();roomCoverRevealed[castle]=false;
 if(world && !active) {
  const auto& a=IndividualCastleRooms::Rooms[castle];
  auto& cover=roomCover[castle];
  const float worldZoom=p.width/r.width;
  const int floorPixels=Max(1,(int)std::lround(IndividualCastleRooms::FloorHeight*worldZoom));
  cover.width=Max(1,(int)std::lround(IndividualCastleRooms::RoomWidth*worldZoom));
  cover.height=floorPixels*p.roomCount;
  cover.left=(int)std::lround(p.left+(a.x+a.w*.5f-r.x)*unit-cover.width*.5f);
  cover.top=(int)std::lround(p.top-(a.y+a.h-r.y)*unit+IndividualCastleRooms::BottomLift*worldZoom)+cover.height;
  cover.material=img;
  cover.sx=(int)std::lround(r.x+(cover.left-p.left)/unit);
  cover.sy=(int)std::lround(r.y+(p.top-cover.top)/unit);
  cover.sw=Max(1,(int)std::lround(cover.width/unit));
  cover.sh=Max(1,(int)std::lround(cover.height/unit));
  p.roomColumns=1;
  const int rows=p.roomCount;
  p.interiorLeft=(float)cover.left;p.interiorTop=(float)cover.top;p.interiorWidth=(float)cover.width;
  p.roomFloorGap=cover.height/(float)rows;
  p.interiorFloor=cover.top-cover.height+Max(2.0f,4*unit);
  if(RoomRevealRequested(castle)) {
    // Use intact single-floor originals. Clipped SD stacks have transparent
    // roof cutouts and cannot be sliced back into rectangular rooms.
    for(int room=0;room<p.roomCount;++room) {
     const int roomImg=CASTLE_RECTANGULAR_ROOM_FIRST_IMG+room*6+CastleVisualPartLevel(castle,2);
     if(!sprite[roomImg]) LoadImg(roomImg);
     if(!sprite[roomImg]) {missingAsset=true;continue;}
     const int row=room;
     const int sx=0,sy=0,sw=512,sh=128;
     const int x=cover.left;
     const int x2=cover.left+cover.width;
     const int top=cover.top-cover.height+cover.height*(row+1)/rows;
     const int low=cover.top-cover.height+cover.height*row/rows;
     // Opaque backing prevents transparent room edges exposing the old facade.
     MemRect(x,top,x2-x,top-low,0x21170F);
     DrawImageScale(sw,sh,sx,sy,x,top,false,0,0,0,0,(x2-x)/(float)sw,(top-low)/(float)sh,sprite[roomImg],roomImg);
    }
  }
 }
 // The same wheel centers/radii define the art crops and rotation pivots.
 for(int i=0;i<r.wheelCount;++i) {
  const auto& wheel=r.wheels[i];
  const float cx=p.left+(wheel.x-r.x)*unit;
  const float cy=p.top-(wheel.y-r.y)*unit;
  RotateImage(wheel.r*2,wheel.r*2,0,0,(int)std::lround(gMirror?gMirrorAxis*2-cx:cx),
    (int)std::lround(cy),gMirror,gMirror?-angle:angle,0,0,unit,cocos2d::Vec2(.5f,.5f),sprite[img+1+i],img+1+i);
 }
 cannonBaseY[castle]=p.commanderY;
 cannonMuzzleX[castle]=p.left+(r.mx-r.x)*unit;cannonMuzzleY[castle]=p.top-(r.my-r.y)*unit;cannonMuzzleValid[castle]=true;
 for(int i=0;i<5;++i) {partAnchor[castle][i][0]=p.left+(i==3?.89f:.4f)*p.width;partAnchor[castle][i][1]=p.top-(i==0?.15f:i==4?.9f:.55f)*p.height;}
 return true;
}
static void DrawCastle(int castle,int x,int yTop,int w,int h,float maxDrawW,
                       bool centerOnWheelAxis=false) {
 castle=Max(0,Min(CastleCount-1,castle));
 useStarterLegacy=!SdEnabled(castle); useSecondLegacy=useStarterLegacy; useThirdLegacy=useStarterLegacy; useFourthLegacy=useStarterLegacy; useFifthLegacy=useStarterLegacy; useSixthLegacy=useStarterLegacy; useSeventhLegacy=useStarterLegacy; useEighthLegacy=useStarterLegacy; useNinthLegacy=useStarterLegacy; useTenthLegacy=useStarterLegacy;
 const int floorCount=castle+1;
 const int stage=active?roomStage[castle]:CastleVisualPartLevel(castle,1);
 const int roofStage=active?stage:CastleVisualPartLevel(castle,0);
 const int cannonStage=active?stage:CastleVisualPartLevel(castle,3);
 const int mobilityStage=active?stage:CastleVisualPartLevel(castle,4);
 const float lowerH=NaturalLowerH(castle);
 const float upperH=NaturalUpperH(castle);
 // The 512px room is the shared origin. Its continuous outer armor and the
 // growing cannon determine the camera bounds for each castle.
 const float naturalW=NaturalCastleW(castle);
 const float scaleByW=(float)w/naturalW;
 const float scaleByH=(float)h/(128.0f*floorCount+lowerH+upperH);
 float scale=Min(maxDrawW/512.0f,Min(scaleByW,scaleByH));
 // 배율을 128 분의 1 단위로 맞춘다.
 //
 // 방은 512x128 이다. 128 * 배율이 정수면 512 * 배율도 정수라(네 배),
 // 층이 정수 줄에 딱 쌓이고 방 폭도 정수가 된다. 이음매를 막으려고
 // 가로 세로를 따로 재던 것이 이걸로 필요 없어진다.
 //
 // 따로 재면 두 값이 거의 늘 다르고, 그리는 스프라이트에
 // scaleX != scaleY 가 남는다. 나중에 누가 그 노드를 getScale() 로
 // 읽으면 엔진이 "어느 쪽을 줘야 하나" 하고 단언에 걸려 게임이 멈춘다
 // (CCNode.cpp 의 getScale). 로비에서 전투로 들어갈 때 터지던 것이
 // 이것이었다.
 scale=Max(1.0f,std::floor(scale*128.0f+0.5f))/128.0f;
 const float castleW=naturalW*scale;
 const float castleH=(128.0f*floorCount+lowerH+upperH)*scale;
 // The room midpoint is also the midpoint of the two wheel axles. Keep it
 // fixed while the side armor and prow grow asymmetrically between castles.
 // Lobby/battle pass a world-space assembly origin; the title preview passes
 // a viewport whose center must stay on the same wheel axis at every grade.
 const float left=centerOnWheelAxis
  ? x+w*0.5f-320.0f*scale
  : x+(w-castleW)*0.5f+(castle==0?96.0f:0.0f)*scale;
 const float roomLeft=left+64.0f*scale;
 const float assemblyBottom=yTop-h+(h-castleH)*0.5f;
 // Raise every wheeled hull above its axle without moving the wheels off the rail.
 const float bottom=assemblyBottom+(lowerH+NaturalBodyLift(castle))*scale;
 const float individualWidth=1056.0f*(IndividualCastleV4::Rigs[castle].width/342.0f)*scale;
 const float individualLeft=gFreePlace?x+(w-individualWidth)*.5f:left;
 if(DrawIndividualCastle(castle,individualLeft,bottom,scale)) return;
 if(DrawSdCastle(castle,left,bottom,scale)) return;
 // All castles have the same authored 736x144 combat deck below room 1.
 // Its 512x64 chassis is already baked in, so a second base draw would
 // leave a visible seam or a duplicate rim at different camera zooms.
 const int deckImg=castle==0?CASTLE_01_COMBAT_DECK_FIRST_IMG+stage:
  CASTLE_02_10_COMBAT_DECK_FIRST_IMG+(castle-1)*6+stage;
 DrawFixedAsset(deckImg,736,144,castle==0?left:left-48.0f*scale,bottom,scale);
 // Quantize every shared edge once.  Rooms and side shells then use the same
 // integer floor rectangle, so camera zoom cannot open a one-pixel crack.
 const int shellLeftPx=(int)std::lround(left);
 const int shellRightPx=(int)std::lround(left+640.0f*scale);
 const int roomLeftPx=(int)std::lround(left+64.0f*scale);
 const int roomRightPx=(int)std::lround(left+576.0f*scale);
 // Keep the facade aligned with rooms even while the castle/camera moves.
 auto& cover=roomCover[castle];
 cover.left=roomLeftPx; cover.top=(int)std::lround(bottom+floorCount*128.0f*scale);
 cover.width=roomRightPx-roomLeftPx;
 cover.height=(int)std::lround(floorCount*128.0f*scale);
 cover.scale=scale;
 cover.material=castle==0 ? CASTLE_WALL_01_FIRST_IMG+stage :
     CASTLE_WALL_PAIR_LOWER_FIRST_IMG+(castle-1)*12+stage*2;
 cover.sx=castle==0?16:Max(0,LeftArmorW(castle)/2-16);
 cover.sy=castle==0?40:Max(0,Min(1024,floorCount*128)-48);
 if(castle==0) {
  cover.left=shellLeftPx;
  cover.width=shellRightPx-shellLeftPx;
  cover.material=CASTLE_ROOM_FACADE_01_IMG;
  cover.sx=CastleRoomFacade::X; cover.sy=CastleRoomFacade::Y;
  cover.sw=CastleRoomFacade::W; cover.sh=CastleRoomFacade::H;
  cover.roof=CASTLE_ROOF_01_FIRST_IMG+roofStage;
  cover.roofX=left; cover.roofY=bottom+(128.0f+256.0f)*scale;
 }
 if(!sprite[cover.material]) LoadImg(cover.material);
 if(castle>0)
  DrawWallRoomSeamBacking(castle,roomLeft,bottom,scale,floorCount*128);
 //배율이 128 분의 1 단위라 아래 자리들이 다 정수로 떨어진다. 가로
 //세로를 따로 잴 까닭이 없어졌다.
 (void)shellRightPx;
 (void)roomRightPx;
 for(int floor=0;floor<=castle;++floor) {
  const int floorStage=active?(floor==castle?stage:5):CastleVisualPartLevel(castle,2);
  const int floorTopPx=(int)std::lround(bottom+(floor+1)*128.0f*scale);
  DrawRoomV4Scale(floor,floorStage,roomLeftPx,floorTopPx,scale,scale);
  // The shell owns only the 64px strips beside the room.  Its central
  // 512px is transparent, so no exterior pixel can cover room artwork.
  if(castle==0)
   DrawFixedAsset(CASTLE_WALL_01_FIRST_IMG+stage,736,128,left,floorTopPx,scale);
  else if(castle!=1 && castle!=2 && castle!=3 && castle!=4 && castle!=5 && castle!=6 && castle!=7 && castle!=8 && castle!=9)
   DrawFixedAssetScale(WallAssetId(castle,floorStage),640,128,shellLeftPx,floorTopPx,
                       scale,scale);
 }
 if(castle==0) {
  // A separate, increasingly elaborate timber crown; the room stays 512x128.
  DrawFixedAsset(CASTLE_ROOF_01_FIRST_IMG+roofStage,736,256,left,
                 bottom+(128.0f+256.0f)*scale,scale);
 } else {
  // One continuous flank on either side of the complete room stack. The
  // opening is exactly 512px wide, so no wall pixel covers a room. Long
  // castles use a second image above the first 1024px section.
  const int wallH=floorCount*128;
  const int crownH=(int)upperH;
  const int lowerH=Min(1024,wallH);
  const int upperWallH=wallH-lowerH;
  const int leftWallW=LeftArmorW(castle);
  const int rightWallW=RightArmorW(castle);
  const int wallIndex=(castle-1)*12+stage*2;
  DrawFixedAsset(CASTLE_WALL_PAIR_LOWER_FIRST_IMG+wallIndex,leftWallW,lowerH,
                 roomLeft-leftWallW*scale,bottom+lowerH*scale,scale);
  DrawFixedAsset(CASTLE_WALL_PAIR_LOWER_FIRST_IMG+wallIndex+1,rightWallW,lowerH,
                 roomLeft+512.0f*scale,bottom+lowerH*scale,scale);
  if(upperWallH>0) {
   const int upperIndex=(castle-8)*12+stage*2;
   DrawFixedAsset(CASTLE_WALL_PAIR_UPPER_FIRST_IMG+upperIndex,leftWallW,upperWallH,
                  roomLeft-leftWallW*scale,bottom+wallH*scale,scale);
   DrawFixedAsset(CASTLE_WALL_PAIR_UPPER_FIRST_IMG+upperIndex+1,rightWallW,upperWallH,
                  roomLeft+512.0f*scale,bottom+wallH*scale,scale);
  }
  DrawFixedAsset(RoofAssetId(castle,roofStage),640,crownH,left,
                 bottom+(wallH+crownH)*scale,scale);
  if(castle==8)
   DrawFixedAsset(CASTLE_09_WINGS_IMG,128,1152,left-100.0f*scale,
                  bottom+1152.0f*scale,scale);
 }
 // Draw the wheels last.  The title screen buffer preserves visit order, so
 // this is the foreground pass over the lower hull.
 if(castle==0) {
  // The authored wheel is 128x128; its upper arc overlaps the lower hull.
  const float wheelScale=scale;
  const float radiusPx=58.0f*wheelScale;
  const float wheelY=bottom-147.0f*scale;
  const float wheelAngle=WheelAngleNow(radiusPx);
  DrawWheelAsset(WheelAssetId(castle,mobilityStage),roomLeft+128.0f*scale,wheelY,wheelScale,wheelAngle);
  DrawWheelAsset(WheelAssetId(castle,mobilityStage),roomLeft+384.0f*scale,wheelY,wheelScale,wheelAngle);
 } else {
  //바퀴는 아래쪽 껍데기 밑단에 걸려 땅까지 닿는다. 크기를 숫자로 따로
  //주면 방 높이나 성 배율을 고칠 때마다 다시 맞춰야 하므로, 메워야 할
  //틈에서 거꾸로 구한다. 껍데기 밑단(kRoomStackLift-64)부터 땅(0)까지가
  //그 틈이고, 그 길이가 곧 바퀴의 보이는 지름이다.
  const float gap=kRoomStackLift-64.0f;
  const float wheelPad=castle==5?6.0f:kWheelPad;
  // Castles 7-10 use padded 128px textures with a 108px visible rim.
  const float wheelScale=castle>=6?scale*1.04f:scale*gap/(128.0f-wheelPad*2.0f);
  const float radiusPx=castle>=6?54.0f*wheelScale:(64.0f-wheelPad)*wheelScale;
  // The axle meets the lower edge of the new 144px combat deck.
  const float wheelY=bottom-144.0f*scale;
  const float wheelAngle=WheelAngleNow(radiusPx);
  DrawWheelAsset(WheelAssetId(castle,mobilityStage),roomLeft+128.0f*scale,wheelY,wheelScale,wheelAngle);
  DrawWheelAsset(WheelAssetId(castle,mobilityStage),roomLeft+384.0f*scale,wheelY,wheelScale,wheelAngle);
 }
 // The commander deck projects from the lowest room, at the front of the
 // assembled castle.  Its first 32px attach inside the room edge.
 float artilleryCharge=0,artilleryRecoil=0; int artilleryBurst=0;
 const bool artilleryOn=StageArtilleryVisual(&artilleryCharge,&artilleryRecoil,&artilleryBurst);
 const float recoilPx=artilleryOn?artilleryRecoil*10.0f*scale:0.0f;
 const float balconyLeft=roomLeft+480.0f*scale;
 // All ten artillery themes share the commander's lower combat platform.
 const auto& gun=InventoryCannons::Get(castle,cannonStage);
 const float gunScale=CannonGrowth(castle,cannonStage)*scale;
 // Every cannon sits on the command deck, starting 32 screen pixels in
 // front of the commander's shared local x=600 anchor.
 const float gunLeft=left+600.0f*scale+32.0f-recoilPx;
 const float platformWidth=Max(192.0f,(gunLeft+recoilPx+gun.bw*gunScale-balconyLeft)/scale+8.0f);
 // Platform walking surface matches the combat deck, 72px below room 1.
 if(castle==0) {
  DrawFixedAssetScale(Balcony01AssetId(cannonStage),192,128,
                 balconyLeft,bottom+3.0f*scale,scale*platformWidth/192.0f,scale);
 } else {
  const int commandIndex=(castle-1)*6+cannonStage;
  DrawFixedAssetScale(CASTLE_COMMAND_PLATFORM_FIRST_IMG+commandIndex,192,128,
                 balconyLeft,bottom-12.0f*scale,scale*platformWidth/192.0f,scale);
 }
 const float gunBase=bottom-72.0f*scale;
 const float gunTop=gunBase+gun.bh*gunScale;
 cannonBaseY[castle]=gunBase;
 const int gunImg=INVENTORY_CANNON_ATLAS_IMG;
 if(!sprite[gunImg]) LoadImg(gunImg);
 if(sprite[gunImg]) DrawImage(gun.bw,gun.bh,gun.x+gun.bx,gun.y+gun.by,
     (int)std::lround(MirrorX(gunLeft,gun.bw*gunScale)),(int)std::lround(gunTop),gMirror,0,0,0,0,gunScale,sprite[gunImg],gunImg);
 else missingAsset=true;
 cannonMuzzleX[castle]=gunLeft+(gun.muzzleX-gun.bx)*gunScale;
 cannonMuzzleY[castle]=gunTop-(gun.muzzleY-gun.by)*gunScale;
 cannonMuzzleValid[castle]=true;
 const float anchorX[5]={roomLeft+256*scale,roomLeft-LeftArmorW(castle)*scale*.5f,
                        roomLeft+256*scale,gunLeft+gun.bw*gunScale*.5f,roomLeft+256*scale};
 const float anchorY[5]={bottom+(floorCount*128+upperH*.5f)*scale,bottom+floorCount*64*scale,
                        bottom+floorCount*64*scale,gunTop-gun.bh*gunScale*.5f,bottom-96*scale};
 for(int i=0;i<5;++i) { partAnchor[castle][i][0]=anchorX[i]; partAnchor[castle][i][1]=anchorY[i]; }
}
static void Button(int x,int y,int w,int h,const char* text,int command,float font) {
 MemRect(x,y,w,h,0x30464D); MemRectFrame(x,y,w,h,0xBD965C); SetFontColor(COLOR_WHITE);
 CenterTextStrSolid(text,x+w/2,y-h/2+7*_2X,font); SetRectPoint(x,y,w,h,command);
}
}

bool CastleCrewDeckPoint(int slot,float* x,float* y) {
 const auto& p=CastleParts::sdPlacement;
 if(!p.valid || !CastleParts::SdEnabled(gMobileCastleVisual) || slot<0 || slot>=MAXCREW) return false;
 const float inset=24*p.scale;
 *x=p.deckLeft+inset+(p.deckWidth-2*inset)*slot/Max(1,MAXCREW-1);
 *y=p.deckSurface;
 return true;
}
//---- 성을 돌려 세운다 ----
//
//on 이면 다음 CastlePartsDrawRect 가 axisX 를 축으로 접힌 성을 그린다.
//한 장면 안에서 한쪽만 돌려 세우므로, 그린 뒤에는 반드시 다시 꺼야 한다.
void CastlePartsSetMirror(bool on,float axisX) {
 CastleParts::gMirror=on;
 CastleParts::gMirrorAxis=axisX;
}

//켜면 다음 CastlePartsDrawRect 가 준 네모를 그대로 쓴다. 성이 화면
//왼쪽에 붙지 않아야 하는 화면(PVP 격돌)에서만 켠다.
void CastlePartsSetFreePlace(bool on) {
 CastleParts::gFreePlace=on;
}

//---- 이 배율로 그리면 화면에서 몇 픽셀인가 ----
//
//조립표가 주는 제 크기(CastlePartsNaturalSize)는 옛 조립 좌표계의 값이고,
//실제로 그려지는 것은 SD 그림 한 장이다. 두 비율이 성마다 다르다 - 성 1
//의 그림은 1536x1024(납작)이고 성 10 은 270x1024(홀쭉)이다.
//
//그래서 폭만 맞추면 성 10 은 화면 높이의 네 배가 되어 밑동만 보인다.
//부르는 쪽이 높이도 보고 배율을 정할 수 있어야 한다.
//
//폭은 성과 상관없이 960 * 1.10 * scale 이다. 높이는 그림의 가로세로비를
//따른다. SD 조립이 아닌 성이면 false.
//---- 로비와 전투가 성을 그리는 폭 ----
//
//SD 조립이 세상 화면(worldView)에서 쓰는 값이다. 성 단계와 상관없이
//늘 같아서, 성을 올리면 폭은 그대로고 위로만 자란다.
//
//다른 화면도 "로비에서 보던 그 크기" 로 그리려면 이 값을 물어보면 된다.
float CastlePartsWorldWidth(void) {
 return (float)DX*CastleParts::kStarterViewportRatio;
}

//---- 이 네모로 그리면 바퀴가 어느 줄에 닿는가 ----
//
//조립은 준 네모 안에서 제 배율을 다시 고르고(128 분의 1 단위로 반올림)
//남는 높이를 위아래로 나눠 가운데에 맞춘다. 그래서 네모의 밑변과 바퀴가
//닿는 줄이 성마다 몇 픽셀씩 어긋난다.
//
//두 성이 나란히 서는 화면(PVP 격돌)에서는 그 몇 픽셀이 눈에 띈다 - 한
//쪽만 선로에서 떠 보인다. 그리기 전에 여기서 재 보고 그만큼 올리면 된다.
//
//DrawCastle 과 DrawSdCastle 이 하는 셈을 그대로 따라간다. 둘 중 한쪽을
//고치면 여기도 같이 고쳐야 한다.
float CastlePartsWheelLine(int castleLevel,int yTop,int w,int h) {
 using namespace CastleParts;
 const int castle=Max(1,Min(CastleCount,castleLevel))-1;
 const float lowerH=NaturalLowerH(castle),upperH=NaturalUpperH(castle);
 const int floorCount=castle+1;
 const float naturalH=128.0f*floorCount+lowerH+upperH;
 float scale=Min((float)w/NaturalCastleW(castle),(float)h/naturalH);
 scale=Max(1.0f,std::floor(scale*128.0f+0.5f))/128.0f;
 const float assemblyBottom=(float)yTop-h+(h-naturalH*scale)*0.5f;
 if(!SdEnabled(castle)) return assemblyBottom+CastlePartsGroundOffset(castleLevel)*scale;
 const float bottom=assemblyBottom+(lowerH+NaturalBodyLift(castle))*scale;
 return bottom-252.0f*scale+(castle?54.0f:StarterLegacyGroundOffset())*scale
   +StageCastleGroundingPx()-kStarterRailOverlapPx;
}

bool CastlePartsDrawSize(int castleLevel,float scale,float* w,float* h) {
 using namespace CastleParts;
 const int castle=Max(1,Min(CastleCount,castleLevel))-1;
 if(IndividualArtEnabled()) {
  const auto& r=IndividualCastleV4::Rigs[castle];
  const float width=1056.0f*scale*r.width/342.0f;
  if(w) *w=width;
  if(h) *h=width*r.h/r.w;
  return true;
 }
 if(!SdEnabled(castle)) return false;
 const float sw=(float)(castle==9?TenthSdParts::Width:castle==8?NinthSdParts::Width:castle==7?EighthSdParts::Width:castle==6?SeventhSdParts::Width:castle==5?SixthSdParts::Width:castle==4?FifthSdParts::Width:castle==3?FourthSdParts::Width:castle==2?ThirdSdParts::Width:castle?SecondSdParts::Width:StarterSdParts::Width);
 const float sh=(float)(castle==9?TenthSdParts::Height:castle==8?NinthSdParts::Height:castle==7?EighthSdParts::Height:castle==6?SeventhSdParts::Height:castle==5?SixthSdParts::Height:castle==4?FifthSdParts::Height:castle==3?FourthSdParts::Height:castle==2?ThirdSdParts::Height:castle?SecondSdParts::Height:StarterSdParts::Height);
 const float unit=960.0f*1.10f/sw*scale;
 if(w) *w=sw*unit;
 if(h) *h=sh*unit;
 return true;
}

void CastlePartsDrawRect(int castleLevel,int x,int yTop,int w,int h) {
 using namespace CastleParts;
 missingAsset=false; DrawCastle(Max(1,Min(CastleCount,castleLevel))-1,x,yTop,w,h,100000.0f);
}
bool CastlePartsCannonMuzzle(int castleLevel,float* x,float* y) {
 const int castle=Max(0,Min(9,castleLevel-1));
 if(!CastleParts::cannonMuzzleValid[castle]) return false;
 *x=CastleParts::cannonMuzzleX[castle]; *y=CastleParts::cannonMuzzleY[castle];
 return true;
}
float CastlePartsCannonBaseY(int castleLevel) {
 return CastleParts::cannonBaseY[Max(0,Min(9,castleLevel-1))];
}
void CastlePartsNaturalSize(int castleLevel,float* w,float* h) {
 using namespace CastleParts;
 const int castle=Max(1,Min(CastleCount,castleLevel))-1;
 if(w) *w=NaturalCastleW(castle);
 if(h) *h=(castle+1)*128.0f+NaturalLowerH(castle)+NaturalUpperH(castle);
}
float CastlePartsRoomInset(int castleLevel) {
 using namespace CastleParts;
 return (float)LeftArmorW(Max(1,Min(CastleCount,castleLevel))-1);
}
//성 1 은 조립할 때 왼쪽으로 96 만큼 들여 놓는다(DrawCastle 의 left).
//대포 뱃머리가 오른쪽으로 길어서, 방을 기준으로 삼으려고 왼쪽에 같은
//여유를 둔 것이다. 화면 왼쪽에 붙이려는 쪽에서는 이만큼을 빼야 한다.
//성 그림 기준 픽셀이라 쓰는 쪽에서 배율을 곱한다.
float CastlePartsLeftInset(int castleLevel) {
	using namespace CastleParts;
	return (Max(1, Min(CastleCount, castleLevel)) - 1) == 0 ? 96.0f : 0.0f;
}
//방 그림은 늘 320 픽셀 폭으로 그린다. 화면이 좁다고 줄이면 방 안이
//안 보인다 - 성은 들여다보는 물건이다. 넘치면 잘리거나 카메라로 민다.
//방 더미 위에 얹힌 여유(성 1 의 지붕). 슬롯표는 방 더미 안의 0~1 로
//적혀 있어서, 성 전체 좌표로 옮기려면 이만큼 내려야 한다.
float CastlePartsUpperH(int castleLevel) {
	using namespace CastleParts;
	return NaturalUpperH(Max(1, Min(CastleCount, castleLevel)) - 1);
}
float CastlePartsBodyLift(int castleLevel) {
 using namespace CastleParts;
 return NaturalBodyLift(Max(1,Min(CastleCount,castleLevel))-1);
}
// Authored distance from the assembly origin to the wheel's contact point.
// Keeping this separate from its center lets the stage rail stay put at any zoom.
float CastlePartsGroundOffset(int castleLevel) {
 using namespace CastleParts;
 const int castle=Max(1,Min(CastleCount,castleLevel))-1;
 if(castle==0) return StarterLegacyGroundOffset();
 if(castle>=6) return NaturalLowerH(castle)+NaturalBodyLift(castle)-144.0f-54.0f;
 const float wheelScale=(kRoomStackLift-64.0f)/(128.0f-2.0f*kWheelPad);
 const float radius=(64.0f-kWheelPad)*wheelScale;
 return NaturalLowerH(castle)+NaturalBodyLift(castle)-144.0f-radius;
}
float CastlePartsRoomScale(void) { using namespace CastleParts; return RoomDrawW / 512.0f; }
void CastlePartsVisualBounds(int level,float scale,float* outLeft,float* outRight) {
 using namespace CastleParts;
 const int c=Max(0,Min(9,level-1));
 const int lv=active?roomStage[c]:CastleVisualPartLevel(c,3);
 const auto& gun=InventoryCannons::Get(c,lv);
 float left=c==0?0.0f:64.0f-LeftArmorW(c);
 if(c==8) left=Min(left,-100.0f);
 const float gunRight=600.0f+32.0f/Max(.01f,scale)+gun.bw*CannonGrowth(c,lv);
 const float right=Max(c==0?736.0f:Max(736.0f,576.0f+RightArmorW(c)),gunRight+8.0f);
 if(outLeft) *outLeft=left;
 if(outRight) *outRight=right;
}
void CastlePartsPartAnchor(int level,int part,float* x,float* y) {
 const int c=Max(0,Min(9,level-1)),i=Max(0,Min(4,part));
 if(x) *x=CastleParts::partAnchor[c][i][0];
 if(y) *y=CastleParts::partAnchor[c][i][1];
}
//조립 네모의 밑변이 곧 땅에 닿는 줄이다. 바퀴가 딱 그 자리까지 내려오게
//그려지므로(DrawCastle) 따로 파묻을 값이 없다.
//
//예전에는 작은 바퀴가 아래쪽 껍데기 안에 숨어 있어서 9.87 만큼 내려
//놓아야 했다. 바퀴를 키워 밖으로 꺼내면서 그 보정이 사라졌다.
float CastlePartsWheelSink(void) { return 0.0f; }
float CastlePartsFloatOffset(int castleLevel) {
 (void)castleLevel;
 return 0.0f;
}
bool TitleCastleDebugCommand(int command) {
 using namespace CastleParts;
 if(drawHandle!=MD_TITLE||command<TOUCH_FUNC_TITLE_CASTLE_OPEN||command>TOUCH_FUNC_TITLE_CASTLE_CLOSE) return false;
 if(command==TOUCH_FUNC_TITLE_CASTLE_OPEN) active=true;
 else if(!active) return true;
 else if(command==TOUCH_FUNC_TITLE_CASTLE_ARMOR) roomStage[state.castle]=(roomStage[state.castle]+1)%6;
 else if(command>=TOUCH_FUNC_TITLE_CASTLE_ARMOR&&command<=TOUCH_FUNC_TITLE_CASTLE_INTERIOR) return true;
 else if(command==TOUCH_FUNC_TITLE_CASTLE_RESET) state.previousCastle();
 else if(command==TOUCH_FUNC_TITLE_CASTLE_PAUSE) state.nextCastle();
 else if(command==TOUCH_FUNC_TITLE_CASTLE_CLOSE) active=false;
 return true;
}
void TitleCastleDebugButton() {
 const float u=(float)DX/640.0f;
 CastleParts::Button(xOffset+DX-(int)(190*u),DY-(int)(12*u),(int)(178*u),(int)(40*u),"성 파츠 테스트",TOUCH_FUNC_TITLE_CASTLE_OPEN,.9f*u);
}
bool TitleCastleDebugActive() {
 using namespace CastleParts;
 return active;
}
bool TitleCastleDebugDraw() {
 using namespace CastleParts;
 static bool checked=false;
 //---- 타이틀이 뜨면 바로 이 화면으로 ----
 //
 //로딩(MENU_LOADING)이 끝난 뒤에 연다. 타이틀 화면은 그 동안 한 프레임에
 //그림 한 장씩 올리는데, 처음부터 가로채면 그 일이 아예 안 일어난다.
 //
 //약관 동의와 로그인 선택이 떠 있으면 비켜 준다. 그 창은 타이틀 위에
 //얹혀 있어서, 이 화면이 먼저 덮으면 동의할 길이 없다.
 //
 //한 번만 본다. 아래 "타이틀" 로 닫고 나면 그 판에서는 다시 안 연다.
 if(!checked&&curMenu!=MENU_LOADING
  &&!NetTermsPending()&&!NetLoginChoicePending()) {
  checked=true;
#if OPEN_TITLE_CASTLE_DEBUG
  active=true;
#endif
  const char* requested=std::getenv("CS_CASTLE_DEBUG"); if(requested&&requested[0]=='1') active=true;
 }
 if(!active) return false;
 ResetRectPoint(); touchDisable=false; SetAlpha(32); MemRect(0,DY,DX,DY,0x18292F);
 const float u=(float)DX/640.0f; const int rowH=(int)(36*u),gap=(int)(6*u);
 const int buttonX=xOffset+(int)(18*u),buttonW=DX-(int)(36*u);
 const int controlsH=2*(rowH+gap)+(int)(35*u),controlsTop=controlsH+(int)(12*u);
 char title[128]; sprintf(title,"%d번 성 / %d층 / %s",state.castle+1,state.castle+1,kThemes[state.castle]);
 SetFontColor(COLOR_WHITE); CenterTextStrSolid(title,xOffset+DX/2,DY-(int)(88*u),1.05f*u);
 CenterTextStrSolid("방 512 x 128 / 전투갑판 736 x 144",xOffset+DX/2,DY-(int)(116*u),.68f*u);
 const int artTop=DY-(int)(132*u),artBottom=controlsTop+(int)(8*u);
 missingAsset=false; DrawCastle(state.castle,xOffset+(int)(8*u),artTop,DX-(int)(16*u),Max((int)(80*u),artTop-artBottom),RoomDrawW,true);
 int y=controlsTop; char roomLabel[96];
 sprintf(roomLabel,"%d층 방   %s%d / +5   +",state.castle+1,roomStage[state.castle]?"+":"기본 ",roomStage[state.castle]);
 Button(buttonX,y,buttonW,rowH,roomLabel,TOUCH_FUNC_TITLE_CASTLE_ARMOR,.86f*u); y-=rowH+gap;
 const int smallW=(buttonW-gap*2)/3;
 Button(buttonX,y,smallW,rowH,"이전 성",TOUCH_FUNC_TITLE_CASTLE_RESET,.72f*u);
 Button(buttonX+smallW+gap,y,smallW,rowH,"다음 성",TOUCH_FUNC_TITLE_CASTLE_PAUSE,.72f*u);
 Button(buttonX+2*(smallW+gap),y,smallW,rowH,"타이틀",TOUCH_FUNC_TITLE_CASTLE_CLOSE,.72f*u);
 SetFontColor(missingAsset?COLOR_RED:COLOR_WHITE);
 CenterTextStrSolid(missingAsset?"누락된 성 파츠 PNG":"방 + 외곽 + 첨탑 + 전투갑판 + 포대 + 바퀴 / 6단계",xOffset+DX/2,y-rowH-(int)(7*u),.62f*u);
 SetFontColor(COLOR_WHITE); return true;
}
