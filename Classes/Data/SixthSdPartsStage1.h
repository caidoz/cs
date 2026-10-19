#pragma once
namespace SixthSdPartsStage1 {
using Piece=StarterSdParts::Piece;
static const int Width=450,Height=992;
static const Piece Pieces[9]={
 {24,97,246,109,0,0},
 {70,322,125,539,0,0},
 {2,206,429,663,0,0},
 {281,594,164,112,0,0},
 {281,706,149,161,0,0},
 {2,869,429,38,0,0},
 {16,907,398,75,0,0},
 {49,878,103,103,0,0},
 {236,878,103,103,103,0},
};
static const Piece Room={70,322,125,539,0,0};
static const int HeroX=379,HeroY=868,StoneX=441,StoneY=643,DeckX=17,DeckY=868,DeckW=264,FloorY=857,GroundY=980,WheelRadius=50,TopVisibleY=97;
static const float RoomFloorGap=89.833333f;
}
