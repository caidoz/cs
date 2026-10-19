#pragma once
namespace NinthSdPartsStage4 {
using Piece=StarterSdParts::Piece;
static const int Width=300,Height=1024;
static const Piece Pieces[9]={
 {46,9,199,171,0,0},
 {95,180,100,720,0,0},
 {0,202,283,698,0,0},
 {205,360,92,380,0,0},
 {205,740,82,160,0,0},
 {35,900,252,35,0,0},
 {36,935,249,89,0,0},
 {34,923,73,73,0,0},
 {159,923,73,73,73,0},
};
static const Piece Room={95,180,100,720,0,0};
static const int FloorY=888,DeckY=900,HeroX=260,HeroY=900,DeckX=55,DeckW=185,GroundY=995,WheelRadius=36;
static const float RoomFloorGap=80.0f;
static const int StoneX=297,StoneY=648,TopVisibleY=10;
}
