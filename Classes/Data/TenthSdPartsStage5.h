#pragma once
namespace TenthSdPartsStage5 {
using Piece=StarterSdParts::Piece;
static const int Width=270,Height=640;
static const Piece Pieces[9]={
 {76,154,84,74,0,0},
 {72,229,83,328,0,0},
 {7,228,218,344,0,0},
 {177,364,87,135,0,0},
 {177,499,74,73,0,0},
 {6,572,247,13,0,0},
 {6,585,246,43,0,0},
 {35,579,51,51,0,0},
 {134,579,51,51,51,0},
};
static const Piece Room={72,229,83,328,0,0};
static const int HeroX=210,HeroY=572,StoneX=263,StoneY=450,DeckX=30,DeckY=572,DeckW=175,FloorY=553,GroundY=628,WheelRadius=23,TopVisibleY=154;
static const float RoomFloorGap=32.800000f;
}
