#pragma once
namespace SixthSdParts {
using Piece=StarterSdParts::Piece;
static const int Width=450,Height=1024;
static const Piece Pieces[9]={
 {26,30,246,120,0,0},
 {68,150,160,732,0,0},
 {6,150,433,734,0,0},
 {295,580,150,124,0,0},
 {295,704,143,178,0,0},
 {6,884,436,41,0,0},
 {13,925,414,81,0,0},
 {55,899,101,101,0,0},
 {252,899,101,101,101,0},
};
static const Piece Room={68,150,160,732,0,0};
static const int FloorY=872,DeckY=884,HeroX=385,HeroY=884,DeckX=15,DeckW=280,GroundY=999,WheelRadius=50;
static const float RoomFloorGap=122.0f;
static const int StoneX=441,StoneY=635,TopVisibleY=35;
}
