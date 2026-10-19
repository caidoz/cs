#pragma once
namespace TenthSdPartsStage1 {
using Piece=StarterSdParts::Piece;
static const int Width=270,Height=640;
static const Piece Pieces[9]={
 {77,142,84,74,0,0},
 {72,229,83,328,0,0},
 {4,216,262,352,0,0},
 {177,314,89,179,0,0},
 {177,493,79,75,0,0},
 {1,568,251,13,0,0},
 {7,581,244,48,0,0},
 {34,577,53,53,0,0},
 {133,577,53,53,53,0},
};
static const Piece Room={72,229,83,328,0,0};
static const int HeroX=210,HeroY=568,StoneX=263,StoneY=439,DeckX=31,DeckY=568,DeckW=174,FloorY=553,GroundY=628,WheelRadius=25,TopVisibleY=142;
static const float RoomFloorGap=32.800000f;
}
