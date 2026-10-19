#pragma once
namespace TenthSdPartsStage2 {
using Piece=StarterSdParts::Piece;
static const int Width=270,Height=1024;
static const Piece Pieces[9]={
 {21,0,222,160,0,0},
 {75,160,100,740,0,0},
 {0,160,252,740,0,0},
 {190,406,78,334,0,0},
 {190,740,67,160,0,0},
 {28,900,221,35,0,0},
 {30,935,217,89,0,0},
 {33,931,65,65,0,0},
 {143,931,65,65,65,0},
};
static const Piece Room={75,160,100,740,0,0};
static const int FloorY=888,DeckY=900,HeroX=220,HeroY=900,DeckX=45,DeckW=170,GroundY=995,WheelRadius=32;
static const float RoomFloorGap=74.0f;
static const int StoneX=268,StoneY=612,TopVisibleY=5;
}
