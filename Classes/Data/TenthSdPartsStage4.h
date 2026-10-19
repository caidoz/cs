#pragma once
namespace TenthSdPartsStage4 {
using Piece=StarterSdParts::Piece;
static const int Width=270,Height=640;
static const Piece Pieces[9]={
 {14,154,147,74,0,0},
 {72,229,83,328,0,0},
 {6,228,170,340,0,0},
 {176,346,90,150,0,0},
 {176,496,67,72,0,0},
 {6,568,237,13,0,0},
 {9,581,233,50,0,0},
 {36,575,55,55,0,0},
 {132,575,55,55,55,0},
};
static const Piece Room={72,229,83,328,0,0};
static const int HeroX=210,HeroY=568,StoneX=263,StoneY=447,DeckX=33,DeckY=568,DeckW=171,FloorY=553,GroundY=628,WheelRadius=25,TopVisibleY=154;
static const float RoomFloorGap=32.800000f;
}
