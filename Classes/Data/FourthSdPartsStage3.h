#pragma once
namespace FourthSdPartsStage3 {
using Piece=StarterSdParts::Piece;
static const int Width=1024,Height=1536;
static const Piece Pieces[9]={
 {48,51,704,329,0,0},
 {180,380,480,800,0,0},
 {0,380,978,810,0,0},
 {760,113,264,897,0,0},
 {760,1010,264,170,0,0},
 {0,1190,1024,100,0,0},
 {33,1290,961,236,0,0},
 {158,1268,205,204,0,0},
 {588,1268,205,204,205,0},
};
static const Piece Room={180,380,480,800,0,0};
static const int FloorY=1167,DeckY=1220,HeroX=860,HeroY=1220,DeckX=60,DeckW=700,GroundY=1472,WheelRadius=102;
static const float RoomFloorGap=200.0f;
static const int StoneX=995,StoneY=880,TopVisibleY=80;
}
