#pragma once
namespace TenthSdPartsStage3 {
using Piece=StarterSdParts::Piece;
static const int Width=270,Height=1024;
static const Piece Pieces[9]={
 {31,5,218,155,0,0},
 {75,160,100,740,0,0},
 {9,160,250,740,0,0},
 {190,367,79,373,0,0},
 {190,740,70,160,0,0},
 {26,900,234,35,0,0},
 {28,935,231,89,0,0},
 {33,931,64,65,0,0},
 {143,931,65,65,64,0},
};
static const Piece Room={75,160,100,740,0,0};
static const int FloorY=888,DeckY=900,HeroX=220,HeroY=900,DeckX=45,DeckW=170,GroundY=995,WheelRadius=32;
static const float RoomFloorGap=74.0f;
static const int StoneX=267,StoneY=646,TopVisibleY=7;
}
