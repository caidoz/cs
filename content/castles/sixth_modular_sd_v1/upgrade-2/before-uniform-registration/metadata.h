#pragma once
namespace SixthSdPartsStage2 {
using Piece=StarterSdParts::Piece;
static const int Width=450,Height=1024;
static const Piece Pieces[9]={
 {19,17,280,133,0,0},
 {68,150,160,732,0,0},
 {0,150,441,734,0,0},
 {295,580,151,124,0,0},
 {295,704,129,178,0,0},
 {0,884,425,41,0,0},
 {10,925,401,84,0,0},
 {55,900,100,99,0,0},
 {252,900,101,99,100,0},
};
static const Piece Room={68,150,160,732,0,0};
static const int FloorY=872,DeckY=884,HeroX=385,HeroY=884,DeckX=15,DeckW=280,GroundY=999,WheelRadius=50;
static const float RoomFloorGap=122.0f;
static const int StoneX=441,StoneY=635,TopVisibleY=29;
}
