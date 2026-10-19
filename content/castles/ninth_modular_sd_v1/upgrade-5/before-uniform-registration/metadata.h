#pragma once
namespace NinthSdPartsStage5 {
using Piece=StarterSdParts::Piece;
static const int Width=300,Height=1024;
static const Piece Pieces[9]={
 {36,0,186,180,0,0},
 {95,180,100,720,0,0},
 {0,246,271,654,0,0},
 {205,417,92,323,0,0},
 {205,740,85,160,0,0},
 {28,900,263,35,0,0},
 {29,935,260,89,0,0},
 {34,923,73,73,0,0},
 {159,923,73,73,73,0},
};
static const Piece Room={95,180,100,720,0,0};
static const int FloorY=888,DeckY=900,HeroX=260,HeroY=900,DeckX=55,DeckW=185,GroundY=995,WheelRadius=36;
static const float RoomFloorGap=80.0f;
static const int StoneX=297,StoneY=608,TopVisibleY=6;
}
