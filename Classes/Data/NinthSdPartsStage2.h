#pragma once
namespace NinthSdPartsStage2 {
using Piece=StarterSdParts::Piece;
static const int Width=300,Height=707;
static const Piece Pieces[9]={
 {94,111,88,103,0,0},
 {91,273,85,344,0,0},
 {6,214,274,410,0,0},
 {198,333,96,202,0,0},
 {198,535,95,89,0,0},
 {6,624,288,19,0,0},
 {7,643,287,55,0,0},
 {34,631,65,65,0,0},
 {155,631,65,65,65,0},
};
static const Piece Room={91,273,85,344,0,0};
static const int HeroX=255,HeroY=624,StoneX=293,StoneY=480,DeckX=41,DeckY=624,DeckW=193,FloorY=613,GroundY=695,WheelRadius=31,TopVisibleY=111;
static const float RoomFloorGap=38.222222f;
}
