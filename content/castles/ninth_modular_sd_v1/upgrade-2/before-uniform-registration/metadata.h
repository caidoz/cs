#pragma once
namespace NinthSdPartsStage2 {
using Piece=StarterSdParts::Piece;
static const int Width=300,Height=1024;
static const Piece Pieces[9]={
 {47,0,231,180,0,0},
 {95,180,100,720,0,0},
 {0,214,284,686,0,0},
 {205,389,91,351,0,0},
 {205,740,92,160,0,0},
 {35,900,262,35,0,0},
 {34,935,263,89,0,0},
 {34,923,73,73,0,0},
 {159,923,73,73,73,0},
};
static const Piece Room={95,180,100,720,0,0};
static const int FloorY=888,DeckY=900,HeroX=260,HeroY=900,DeckX=55,DeckW=185,GroundY=995,WheelRadius=36;
static const float RoomFloorGap=80.0f;
static const int StoneX=296,StoneY=645,TopVisibleY=6;
}
