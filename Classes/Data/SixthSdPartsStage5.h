#pragma once
namespace SixthSdPartsStage5 {
using Piece=StarterSdParts::Piece;
static const int Width=450,Height=992;
static const Piece Pieces[9]={
 {19,207,248,115,0,0},
 {70,322,125,539,0,0},
 {2,322,442,561,0,0},
 {293,650,152,95,0,0},
 {293,745,147,136,0,0},
 {1,883,439,32,0,0},
 {21,915,407,74,0,0},
 {57,887,95,95,0,0},
 {252,887,95,95,95,0},
};
static const Piece Room={70,322,125,539,0,0};
static const int HeroX=384,HeroY=882,StoneX=440,StoneY=692,DeckX=19,DeckY=882,DeckW=273,FloorY=857,GroundY=980,WheelRadius=46,TopVisibleY=207;
static const float RoomFloorGap=89.833333f;
}
