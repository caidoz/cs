#pragma once
namespace TenthSdPartsStage5 {
using Piece=StarterSdParts::Piece;
static const int Width=270,Height=1024;
static const Piece Pieces[9]={
 {82,0,94,160,0,0},
 {75,160,100,740,0,0},
 {17,161,217,739,0,0},
 {190,453,79,287,0,0},
 {190,740,67,160,0,0},
 {30,900,228,35,0,0},
 {31,935,226,89,0,0},
 {33,931,65,64,0,0},
 {143,931,65,64,65,0},
};
static const Piece Room={75,160,100,740,0,0};
static const int FloorY=888,DeckY=900,HeroX=220,HeroY=900,DeckX=45,DeckW=170,GroundY=995,WheelRadius=32;
static const float RoomFloorGap=74.0f;
static const int StoneX=267,StoneY=637,TopVisibleY=4;
}
