#pragma once
#include "CastlePartState.h"
#include <cstdlib>
#include <cmath>
#include <chrono>

//배경이 지금까지 흘려보낸 거리(화면 픽셀). StageBackground 가 센다.
float StageBgRailTravelPx(void);

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

static int AssetId(int castle,int part,int level) {
 return MODCASTLE_V2_FIRST_IMG+castle*PartCount*LevelCount+part*LevelCount+level;
}
static int RoomV4AssetId(int floor,int stage) {
 return CASTLE_ROOM_V4_FIRST_IMG+floor*6+stage;
}
static void DrawRoomV4(int floor,int stage,float x,float yTop,float scale) {
 const int img=RoomV4AssetId(floor,stage);
 if(!sprite[img]) LoadImg(img);
 if(!sprite[img]) { missingAsset=true; return; }
 DrawImage(512,128,0,0,(int)std::lround(x),(int)std::lround(yTop),false,0,0,0,0,scale,sprite[img],img);
}
static void DrawFixedAsset(int img,int sourceW,int sourceH,float x,float yTop,float scale) {
 if(!sprite[img]) LoadImg(img);
 if(!sprite[img]) { missingAsset=true; return; }
 DrawImage(sourceW,sourceH,0,0,(int)std::lround(x),(int)std::lround(yTop),false,0,0,0,0,scale,sprite[img],img);
}
static void DrawFixedAssetRegion(int img,int sourceW,int sourceH,int sourceY,
                                 float x,float yTop,float scale) {
 if(!sprite[img]) LoadImg(img);
 if(!sprite[img]) { missingAsset=true; return; }
 DrawImage(sourceW,sourceH,0,sourceY,(int)std::lround(x),(int)std::lround(yTop),
           false,0,0,0,0,scale,sprite[img],img);
}
static void DrawFixedAssetScale(int img,int sourceW,int sourceH,int x,int yTop,float scaleX,float scaleY) {
 if(!sprite[img]) LoadImg(img);
 if(!sprite[img]) { missingAsset=true; return; }
 DrawImageScale(sourceW,sourceH,0,0,x,yTop,false,0,0,0,0,scaleX,scaleY,sprite[img],img);
}
static void DrawRoomV4Scale(int floor,int stage,int x,int yTop,float scaleX,float scaleY) {
 const int img=RoomV4AssetId(floor,stage);
 if(!sprite[img]) LoadImg(img);
 if(!sprite[img]) { missingAsset=true; return; }
 DrawImageScale(512,128,0,0,x,yTop,false,0,0,0,0,scaleX,scaleY,sprite[img],img);
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
static void DrawAsset(int castle,int part,int level,float x,float yTop,float scale) {
 const int img=AssetId(castle,part,level);
 if(!sprite[img]) LoadImg(img);
 if(!sprite[img]) { missingAsset=true; return; }
 const int partH=part==Roof?164+(castle+1)*92:(part==Mobility&&castle>=7?176:kPartH[part]);
 DrawImage(kPartW[part],partH,0,0,(int)x,(int)yTop,false,0,0,0,0,scale,sprite[img],img);
}
// Distance from the assembly origin to the first room. Every castle now
// uses wheels, so the floor/base/wheel seam shares one coordinate system.
static const float kRoomStackLift=172.0f;
static float NaturalLowerH(int castle) { (void)castle; return 236.0f; }
static float NaturalBodyLift(int castle) { (void)castle; return 16.0f; }
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
 return (1.0f+0.135f*castle)*(0.82f+0.036f*stage);
}
static float NaturalCastleW(int castle) {
 if(castle==0) return 832.0f;
 // The prow cannon projects farther right as the castle grows. Include it
 // in the camera bounds so the last castle does not lose its muzzle.
 return LeftArmorW(castle)+544.0f+128.0f*CannonGrowth(castle,5);
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
 MemRect(roomLeftPx-outer,yTop,outer+inner,yTop-yBottom,color);
 MemRect(roomRightPx-inner,yTop,outer+inner,yTop-yBottom,color);
}
static void DrawCastle(int castle,int x,int yTop,int w,int h,float maxDrawW,
                       bool centerOnWheelAxis=false) {
 castle=Max(0,Min(CastleCount-1,castle));
 const int floorCount=castle+1;
 const int stage=roomStage[castle];
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
 if(castle>0)
  DrawWallRoomSeamBacking(castle,roomLeft,bottom,scale,floorCount*128);
 //배율이 128 분의 1 단위라 아래 자리들이 다 정수로 떨어진다. 가로
 //세로를 따로 잴 까닭이 없어졌다.
 (void)shellRightPx;
 (void)roomRightPx;
 for(int floor=0;floor<=castle;++floor) {
  const int floorStage=floor==castle?stage:5;
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
  DrawFixedAsset(CASTLE_ROOF_01_FIRST_IMG+stage,736,256,left,
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
  DrawFixedAsset(RoofAssetId(castle,stage),640,crownH,left,
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
  DrawWheelAsset(WheelAssetId(castle,stage),roomLeft+128.0f*scale,wheelY,wheelScale,wheelAngle);
  DrawWheelAsset(WheelAssetId(castle,stage),roomLeft+384.0f*scale,wheelY,wheelScale,wheelAngle);
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
  DrawWheelAsset(WheelAssetId(castle,stage),roomLeft+128.0f*scale,wheelY,wheelScale,wheelAngle);
  DrawWheelAsset(WheelAssetId(castle,stage),roomLeft+384.0f*scale,wheelY,wheelScale,wheelAngle);
 }
 // The commander deck projects from the lowest room, at the front of the
 // assembled castle.  Its first 32px attach inside the room edge.
 if(castle==0)
  DrawFixedAsset(CASTLE_01_CANNON_FIRST_IMG+stage,160,128,left+576.0f*scale,
                 bottom+64.0f*scale,scale);
 else {
  const float balconyLeft=roomLeft+480.0f*scale;
  const float balconyTop=bottom+128.0f*scale;
  const int commandIndex=(castle-1)*6+stage;
  DrawFixedAsset(CASTLE_COMMAND_PLATFORM_FIRST_IMG+commandIndex,192,128,
                 balconyLeft,balconyTop,scale);
  const float gunScale=CannonGrowth(castle,stage);
  DrawFixedAsset(CASTLE_HEAVY_CANNON_FIRST_IMG+commandIndex,128,64,
                 balconyLeft+64.0f*scale,
                 balconyTop+(gunScale-1.0f)*64.0f*scale,scale*gunScale);
 }
}
static void Button(int x,int y,int w,int h,const char* text,int command,float font) {
 MemRect(x,y,w,h,0x30464D); MemRectFrame(x,y,w,h,0xBD965C); SetFontColor(COLOR_WHITE);
 CenterTextStrSolid(text,x+w/2,y-h/2+7*_2X,font); SetRectPoint(x,y,w,h,command);
}
}

void CastlePartsDrawRect(int castleLevel,int x,int yTop,int w,int h) {
 using namespace CastleParts;
 missingAsset=false; DrawCastle(Max(1,Min(CastleCount,castleLevel))-1,x,yTop,w,h,100000.0f);
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
 if(castle==0) return NaturalLowerH(castle)+NaturalBodyLift(castle)-144.0f-61.0f;
 if(castle>=6) return NaturalLowerH(castle)+NaturalBodyLift(castle)-144.0f-54.0f;
 const float wheelScale=(kRoomStackLift-64.0f)/(128.0f-2.0f*kWheelPad);
 const float radius=(64.0f-kWheelPad)*wheelScale;
 return NaturalLowerH(castle)+NaturalBodyLift(castle)-144.0f-radius;
}
float CastlePartsRoomScale(void) { using namespace CastleParts; return RoomDrawW / 512.0f; }
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
 if(!checked) { checked=true; const char* requested=std::getenv("CS_CASTLE_DEBUG"); if(requested&&requested[0]=='1') active=true; }
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
