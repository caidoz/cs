#pragma once
namespace FourthSdPartsStage5 {
using Piece=StarterSdParts::Piece;
static const int Width=1024,Height=1536;
static const Piece Pieces[9]={
 {17,46,743,334,0,0},
 {180,380,480,800,0,0},
 {0,380,980,810,0,0},
 {760,143,264,867,0,0},
 {760,1010,264,170,0,0},
 {0,1190,1024,100,0,0},
 {0,1290,991,222,0,0},
 {158,1268,205,204,0,0},
 {588,1268,205,204,205,0},
};
static const Piece Room={180,380,480,800,0,0};
static const int FloorY=1167,DeckY=1220,HeroX=860,HeroY=1220,DeckX=60,DeckW=700,GroundY=1472,WheelRadius=102;
static const float RoomFloorGap=200.0f;
static const int StoneX=995,StoneY=880,TopVisibleY=49;
}
