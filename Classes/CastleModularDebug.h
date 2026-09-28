#pragma once
#include "CastlePartState.h"
#include <cstdlib>

namespace CastleParts {
struct Box { int x,y,w,h; };
static const Box kBox[CastleCount] = {
 {0,0,384,375},{0,0,384,467},{0,0,384,559},{0,0,384,651},{0,0,384,743},
 {0,0,384,835},{0,0,384,927},{0,0,384,1019},{0,0,384,1111},{0,0,384,1203}
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
static void DrawAsset(int castle,int part,int level,float x,float yTop,float scale) {
 const int img=AssetId(castle,part,level);
 if(!sprite[img]) LoadImg(img);
 if(!sprite[img]) { missingAsset=true; return; }
 const int partH=part==Roof?164+(castle+1)*92:(part==Mobility&&castle>=7?176:kPartH[part]);
 DrawImage(kPartW[part],partH,0,0,(int)x,(int)yTop,false,0,0,0,0,scale,sprite[img],img);
}
static void DrawCastle(int castle,int x,int yTop,int w,int h) {
 castle=Max(0,Min(CastleCount-1,castle));
 const int floorCount=castle+1;
 // Assemble at the authored 512x128 grid first, then zoom the whole castle.
 // This keeps every room at 4:1 and every seam at exactly zero pixels.
 const float scale=Min(w/512.0f,h/(128.0f*floorCount));
 const float castleW=512.0f*scale;
 const float castleH=128.0f*floorCount*scale;
 const float left=x+(w-castleW)*.5f;
 const float bottom=yTop-h+(h-castleH)*.5f;
 for(int floor=0;floor<=castle;++floor) {
  const int stage=floor==castle?roomStage[castle]:5;
  DrawRoomV4(floor,stage,left,bottom+(floor+1)*128*scale,scale);
 }
}
static void Button(int x,int y,int w,int h,const char* text,int command,float font) {
 MemRect(x,y,w,h,0x30464D); MemRectFrame(x,y,w,h,0xBD965C); SetFontColor(COLOR_WHITE);
 CenterTextStrSolid(text,x+w/2,y-h/2+7*_2X,font); SetRectPoint(x,y,w,h,command);
}
}

void CastlePartsDrawRect(int castleLevel,int x,int yTop,int w,int h) {
 using namespace CastleParts;
 missingAsset=false; DrawCastle(Max(1,Min(CastleCount,castleLevel))-1,x,yTop,w,h);
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
 CenterTextStrSolid("고정 슬롯 512 x 128 / 아래층은 +5 / 외곽 파츠 숨김",xOffset+DX/2,DY-(int)(116*u),.68f*u);
 const int artTop=DY-(int)(132*u),artBottom=controlsTop+(int)(8*u);
 missingAsset=false; DrawCastle(state.castle,xOffset+(int)(8*u),artTop,DX-(int)(16*u),Max((int)(80*u),artTop-artBottom));
 int y=controlsTop; char roomLabel[96];
 sprintf(roomLabel,"%d층 방   %s%d / +5   +",state.castle+1,roomStage[state.castle]?"+":"기본 ",roomStage[state.castle]);
 Button(buttonX,y,buttonW,rowH,roomLabel,TOUCH_FUNC_TITLE_CASTLE_ARMOR,.86f*u); y-=rowH+gap;
 const int smallW=(buttonW-gap*2)/3;
 Button(buttonX,y,smallW,rowH,"이전 성",TOUCH_FUNC_TITLE_CASTLE_RESET,.72f*u);
 Button(buttonX+smallW+gap,y,smallW,rowH,"다음 성",TOUCH_FUNC_TITLE_CASTLE_PAUSE,.72f*u);
 Button(buttonX+2*(smallW+gap),y,smallW,rowH,"타이틀",TOUCH_FUNC_TITLE_CASTLE_CLOSE,.72f*u);
 SetFontColor(missingAsset?COLOR_RED:COLOR_WHITE);
 CenterTextStrSolid(missingAsset?"누락된 castle_rooms_v4 PNG":"60개 방 / 고정 512 x 128 px / 외곽 OFF",xOffset+DX/2,y-rowH-(int)(7*u),.62f*u);
 SetFontColor(COLOR_WHITE); return true;
}
