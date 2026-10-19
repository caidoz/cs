#pragma once
namespace NinthSdPartsStage4 {
using Piece=StarterSdParts::Piece;
static const int Width=300,Height=707;
static const Piece Pieces[9]={
 {89,146,162,95,0,0},
 {91,273,85,344,0,0},
 {6,241,267,392,0,0},
 {189,339,105,208,0,0},
 {189,547,93,86,0,0},
 {6,633,276,19,0,0},
 {7,652,273,46,0,0},
 {35,640,57,57,0,0},
 {149,640,57,57,57,0},
};
static const Piece Room={91,273,85,344,0,0};
static const int HeroX=251,HeroY=633,StoneX=293,StoneY=496,DeckX=40,DeckY=633,DeckW=189,FloorY=613,GroundY=695,WheelRadius=26,TopVisibleY=146;
static const float RoomFloorGap=38.222222f;
}
