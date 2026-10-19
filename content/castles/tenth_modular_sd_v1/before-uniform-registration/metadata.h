#pragma once
namespace TenthSdParts {
using Piece=StarterSdParts::Piece;
static const int Width=270,Height=1024;
static const Piece Pieces[9]={
 {15,5,162,155,0,0},
 {75,160,100,740,0,0},
 {43,225,184,675,0,0},
 {190,431,67,309,0,0},
 {190,740,76,160,0,0},
 {43,900,223,35,0,0},
 {44,935,221,68,0,0},
 {34,931,63,65,0,0},
 {144,931,63,65,63,0},
};
static const Piece Room={75,160,100,740,0,0};
static const int FloorY=888,DeckY=900,HeroX=220,HeroY=900,DeckX=45,DeckW=170,GroundY=995,WheelRadius=32;
static const float RoomFloorGap=74.0f;
static const int StoneX=255,StoneY=647,TopVisibleY=7;
}
