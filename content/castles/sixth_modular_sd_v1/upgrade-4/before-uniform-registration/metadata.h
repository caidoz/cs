#pragma once
namespace SixthSdPartsStage4 {
using Piece=StarterSdParts::Piece;
static const int Width=450,Height=1024;
static const Piece Pieces[9]={
 {25,25,399,125,0,0},
 {68,150,160,732,0,0},
 {1,150,442,734,0,0},
 {295,580,153,124,0,0},
 {295,704,130,178,0,0},
 {0,884,419,41,0,0},
 {12,925,399,84,0,0},
 {55,899,101,100,0,0},
 {252,899,100,100,101,0},
};
static const Piece Room={68,150,160,732,0,0};
static const int FloorY=872,DeckY=884,HeroX=385,HeroY=884,DeckX=15,DeckW=280,GroundY=999,WheelRadius=50;
static const float RoomFloorGap=122.0f;
static const int StoneX=441,StoneY=635,TopVisibleY=30;
}
