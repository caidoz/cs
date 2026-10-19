#pragma once
namespace TenthSdPartsStage4 {
using Piece=StarterSdParts::Piece;
static const int Width=270,Height=1024;
static const Piece Pieces[9]={
 {78,0,99,160,0,0},
 {75,160,100,740,0,0},
 {26,160,223,740,0,0},
 {190,397,80,343,0,0},
 {190,740,60,160,0,0},
 {28,900,222,35,0,0},
 {28,935,220,89,0,0},
 {33,931,65,65,0,0},
 {143,931,65,65,65,0},
};
static const Piece Room={75,160,100,740,0,0};
static const int FloorY=888,DeckY=900,HeroX=220,HeroY=900,DeckX=45,DeckW=170,GroundY=995,WheelRadius=32;
static const float RoomFloorGap=74.0f;
static const int StoneX=267,StoneY=635,TopVisibleY=7;
}
