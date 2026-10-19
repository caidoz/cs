#pragma once
namespace FourthSdPartsStage1 {
using Piece=StarterSdParts::Piece;
static const int Width=1024,Height=1536;
static const Piece Pieces[9]={
 {47,47,689,333,0,0},
 {180,380,480,800,0,0},
 {15,380,963,810,0,0},
 {760,271,254,739,0,0},
 {760,1010,263,170,0,0},
 {0,1190,1024,100,0,0},
 {27,1290,965,198,0,0},
 {158,1268,205,205,0,0},
 {588,1268,205,205,205,0},
};
static const Piece Room={180,380,480,800,0,0};
static const int FloorY=1167,DeckY=1220,HeroX=860,HeroY=1220,DeckX=60,DeckW=700,GroundY=1472,WheelRadius=102;
static const float RoomFloorGap=200.0f;
static const int StoneX=995,StoneY=880,TopVisibleY=87;
}
