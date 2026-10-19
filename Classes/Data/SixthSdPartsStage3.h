#pragma once
namespace SixthSdPartsStage3 {
using Piece=StarterSdParts::Piece;
static const int Width=450,Height=992;
static const Piece Pieces[9]={
 {20,174,234,104,0,0},
 {70,322,125,539,0,0},
 {2,278,438,593,0,0},
 {285,626,160,100,0,0},
 {285,726,147,144,0,0},
 {1,871,433,39,0,0},
 {16,910,402,74,0,0},
 {50,883,99,99,0,0},
 {242,883,99,99,99,0},
};
static const Piece Room={70,322,125,539,0,0};
static const int HeroX=380,HeroY=871,StoneX=440,StoneY=670,DeckX=19,DeckY=871,DeckW=265,FloorY=857,GroundY=980,WheelRadius=48,TopVisibleY=174;
static const float RoomFloorGap=89.833333f;
}
