#pragma once
#include "CastlePartState.h"
#include <cstdlib>
#include <cmath>

//배경이 지금까지 흘려보낸 거리(화면 픽셀). StageBackground 가 센다.
float StageBgRailTravelPx(void);
//성 본체보다 바퀴를 이만큼 덜 내린다. 둘의 내림값은 StageBackground 에 있다.
float CastleWheelLiftPx(void);

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
 DrawImage(512,128,0,0,(int)x,(int)yTop,false,0,0,0,0,scale,sprite[img],img);
}
static void DrawFixedAsset(int img,int sourceW,int sourceH,float x,float yTop,float scale) {
 if(!sprite[img]) LoadImg(img);
 if(!sprite[img]) { missingAsset=true; return; }
 DrawImage(sourceW,sourceH,0,0,(int)x,(int)yTop,false,0,0,0,0,scale,sprite[img],img);
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
 return std::fmod(StageBgRailTravelPx()/radiusPx*57.29578f,360.0f);
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
static int HoverAssetId(int castle,int stage) {
 return CASTLE_HOVER_FIRST_IMG+(castle-6)*6+stage;
}
static int FlightBaseAssetId(int castle,int stage) {
 return CASTLE_FLIGHTBASE_FIRST_IMG+(castle-6)*6+stage;
}
static int Balcony01AssetId(int stage) {
 return CASTLE_BALCONY_01_FIRST_IMG+stage;
}
static int Wall01AssetId(int stage) { return CASTLE_WALL_01_FIRST_IMG+stage; }
static int Roof01AssetId(int stage) { return CASTLE_ROOF_01_FIRST_IMG+stage; }
static void DrawAsset(int castle,int part,int level,float x,float yTop,float scale) {
 const int img=AssetId(castle,part,level);
 if(!sprite[img]) LoadImg(img);
 if(!sprite[img]) { missingAsset=true; return; }
 const int partH=part==Roof?164+(castle+1)*92:(part==Mobility&&castle>=7?176:kPartH[part]);
 DrawImage(kPartW[part],partH,0,0,(int)x,(int)yTop,false,0,0,0,0,scale,sprite[img],img);
}
//첫 방의 밑변이 조립 밑변에서 얼마나 떠 있나. 바퀴성이든 부유성이든
//같다.
//
//예전에는 바퀴성 104, 부유성 240 으로 갈렸다. 그러면 성 단계를 넘길 때
//첫 방이 오르내려서 같은 성의 같은 층으로 안 읽힌다. 둘의 가운데인
//172 로 모은다. 남는 아래 공간은 바퀴성은 커진 바퀴가, 부유성은 엔진과
//불꽃이 채운다.
static const float kRoomStackLift=172.0f;
static float NaturalLowerH(int castle) { (void)castle; return kRoomStackLift; }
static float NaturalUpperH(int castle) { return castle==0?192.0f:0.0f; }
static float HoverPhase() { return std::fmod((float)frame,180.0f)/180.0f; }
static float HoverLift(int castle) {
 if(castle<6) return 0.0f;
 const float p=HoverPhase();
 return 6.0f-6.0f*std::cos(p*6.2831853f);
}
static float HoverThrust() {
 const float p=HoverPhase();
 return p<0.5f?std::sin(p*6.2831853f):0.10f+0.04f*std::sin(p*25.132741f);
}
static void DrawHoverExhaust(int castle,float x,float yTop,float scale) {
 const int img=castle==9?CASTLE_HOVER_EXHAUST_10_IMG:CASTLE_HOVER_EXHAUST_07_09_IMG;
 if(!sprite[img]) LoadImg(img);
 if(!sprite[img]) { missingAsset=true; return; }
 const float thrust=Max(0.0f,HoverThrust());
 // Keep the effect in the same authored 512x128 coordinate system as the
 // engine hull.  Stretching only Y made the nozzle centers and attachment
 // seam drift whenever the castle zoom changed.
 const int alpha=(int)(18.0f+14.0f*thrust);
 DrawImageScale(512,128,0,0,(int)x,(int)yTop,false,0,0,1,alpha,scale,scale,sprite[img],img);
}
static void DrawCastle(int castle,int x,int yTop,int w,int h,float maxDrawW) {
 castle=Max(0,Min(CastleCount-1,castle));
 const int floorCount=castle+1;
 const int stage=roomStage[castle];
 const float lowerH=NaturalLowerH(castle);
 const float upperH=NaturalUpperH(castle);
 const float naturalW=castle==0?672.0f:512.0f;
 const float scaleByW=(float)w/naturalW;
 const float scaleByH=(float)h/(128.0f*floorCount+lowerH+upperH);
 const float scale=Min(maxDrawW/512.0f,Min(scaleByW,scaleByH));
 const float castleW=naturalW*scale;
 const float castleH=(128.0f*floorCount+lowerH+upperH)*scale;
 const float left=x+(w-castleW)*0.5f;
 const float lift=HoverLift(castle)*scale;
 const float assemblyBottom=yTop-h+(h-castleH)*0.5f+lift;
 const float bottom=assemblyBottom+lowerH*scale;
 if(castle>=6) {
  // The flying castles use one thick hull/engine module.  Its top meets the
  // first room at the same authored 512px seam; only the plume sits behind it.
  // Sink the first 20 authored pixels into the engine mouths.  This removes
  // the transparent seam while retaining a full 1:1 plume below the hull.
  DrawHoverExhaust(castle,left,bottom-108.0f*scale,scale);
  DrawFixedAsset(FlightBaseAssetId(castle,stage),512,128,left,bottom,scale);
 } else {
  DrawFixedAsset(BaseAssetId(castle,stage),512,64,left,bottom,scale);
 }
 for(int floor=0;floor<=castle;++floor) {
  const int floorStage=floor==castle?stage:5;
  DrawRoomV4(floor,floorStage,left,bottom+(floor+1)*128*scale,scale);
 }
 if(castle==0)
  DrawFixedAsset(Wall01AssetId(stage),512,128,left,bottom+128.0f*scale,scale);
 // The first 32 pixels overlap the room frame, so the commander deck stays
 // attached at every zoom while the remaining 160 pixels project right.
 if(castle==0)
  DrawFixedAsset(Balcony01AssetId(stage),192,128,left+480.0f*scale,bottom+128.0f*scale,scale);
 if(castle==0)
  DrawFixedAsset(Roof01AssetId(stage),512,192,left,bottom+320.0f*scale,scale);
 // Draw the wheels last.  The title screen buffer preserves visit order, so
 // this is the foreground pass over the lower hull.
 if(castle<6) {
  //바퀴는 아래쪽 껍데기 밑단에 걸려 땅까지 닿는다. 크기를 숫자로 따로
  //주면 방 높이나 성 배율을 고칠 때마다 다시 맞춰야 하므로, 메워야 할
  //틈에서 거꾸로 구한다. 껍데기 밑단(kRoomStackLift-64)부터 땅(0)까지가
  //그 틈이고, 그 길이가 곧 바퀴의 보이는 지름이다.
  const float gap=kRoomStackLift-64.0f;
  const float wheelScale=scale*gap/(128.0f-kWheelPad*2.0f);
  const float radiusPx=(64.0f-kWheelPad)*wheelScale;
  //본체는 더 내려앉히고 바퀴는 덜 내린다. 같이 내리면 바퀴가 선로
  //아래로 파묻힌다.
  const float wheelY=assemblyBottom+radiusPx+CastleWheelLiftPx();
  const float wheelAngle=WheelAngleNow(radiusPx);
  DrawWheelAsset(WheelAssetId(castle,stage),left+128.0f*scale,wheelY,wheelScale,wheelAngle);
  DrawWheelAsset(WheelAssetId(castle,stage),left+384.0f*scale,wheelY,wheelScale,wheelAngle);
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
 if(w) *w=castle==0?672.0f:512.0f;
 if(h) *h=(castle+1)*128.0f+NaturalLowerH(castle)+NaturalUpperH(castle);
}
//방 그림은 늘 320 픽셀 폭으로 그린다. 화면이 좁다고 줄이면 방 안이
//안 보인다 - 성은 들여다보는 물건이다. 넘치면 잘리거나 카메라로 민다.
//방 더미 위에 얹힌 여유(성 1 의 지붕). 슬롯표는 방 더미 안의 0~1 로
//적혀 있어서, 성 전체 좌표로 옮기려면 이만큼 내려야 한다.
float CastlePartsUpperH(int castleLevel) {
	using namespace CastleParts;
	return NaturalUpperH(Max(1, Min(CastleCount, castleLevel)) - 1);
}
float CastlePartsRoomScale(void) { using namespace CastleParts; return RoomDrawW / 512.0f; }
//조립 네모의 밑변이 곧 땅에 닿는 줄이다. 바퀴가 딱 그 자리까지 내려오게
//그려지므로(DrawCastle) 따로 파묻을 값이 없다.
//
//예전에는 작은 바퀴가 아래쪽 껍데기 안에 숨어 있어서 9.87 만큼 내려
//놓아야 했다. 바퀴를 키워 밖으로 꺼내면서 그 보정이 사라졌다.
float CastlePartsWheelSink(void) { return 0.0f; }
float CastlePartsFloatOffset(int castleLevel) {
 using namespace CastleParts;
 const int castle=Max(1,Min(CastleCount,castleLevel))-1;
 return HoverLift(castle);
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
 CenterTextStrSolid("방 512 x 128 / 성1 지휘관 외장 192 x 128",xOffset+DX/2,DY-(int)(116*u),.68f*u);
 const int artTop=DY-(int)(132*u),artBottom=controlsTop+(int)(8*u);
 missingAsset=false; DrawCastle(state.castle,xOffset+(int)(8*u),artTop,DX-(int)(16*u),Max((int)(80*u),artTop-artBottom),RoomDrawW);
 int y=controlsTop; char roomLabel[96];
 sprintf(roomLabel,"%d층 방   %s%d / +5   +",state.castle+1,roomStage[state.castle]?"+":"기본 ",roomStage[state.castle]);
 Button(buttonX,y,buttonW,rowH,roomLabel,TOUCH_FUNC_TITLE_CASTLE_ARMOR,.86f*u); y-=rowH+gap;
 const int smallW=(buttonW-gap*2)/3;
 Button(buttonX,y,smallW,rowH,"이전 성",TOUCH_FUNC_TITLE_CASTLE_RESET,.72f*u);
 Button(buttonX+smallW+gap,y,smallW,rowH,"다음 성",TOUCH_FUNC_TITLE_CASTLE_PAUSE,.72f*u);
 Button(buttonX+2*(smallW+gap),y,smallW,rowH,"타이틀",TOUCH_FUNC_TITLE_CASTLE_CLOSE,.72f*u);
 SetFontColor(missingAsset?COLOR_RED:COLOR_WHITE);
 CenterTextStrSolid(missingAsset?"누락된 성 파츠 PNG":"방 + 우측 지휘관 발코니 / 6단계",xOffset+DX/2,y-rowH-(int)(7*u),.62f*u);
 SetFontColor(COLOR_WHITE); return true;
}
