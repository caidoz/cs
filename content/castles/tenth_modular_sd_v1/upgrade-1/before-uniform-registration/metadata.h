#pragma once
namespace TenthSdPartsStage1 {
using Piece=StarterSdParts::Piece;
static const int Width=270,Height=1024;
static const Piece Pieces[9]={
 {84,5,170,155,0,0},
 {75,160,100,740,0,0},
 {12,160,178,740,0,0},
 {190,361,80,379,0,0},
 {190,740,74,160,0,0},
 {29,900,229,35,0,0},
 {30,935,227,89,0,0},
 {33,931,65,65,0,0},
 {143,931,65,65,65,0},
};
static const Piece Room={75,160,100,740,0,0};
static const int FloorY=888,DeckY=900,HeroX=220,HeroY=900,DeckX=45,DeckW=170,GroundY=995,WheelRadius=32;
static const float RoomFloorGap=74.0f;
static const int StoneX=267,StoneY=629,TopVisibleY=8;
}
