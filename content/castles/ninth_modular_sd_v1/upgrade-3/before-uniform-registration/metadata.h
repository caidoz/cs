#pragma once
namespace NinthSdPartsStage3 {
using Piece=StarterSdParts::Piece;
static const int Width=300,Height=1024;
static const Piece Pieces[9]={
 {44,6,224,174,0,0},
 {95,180,100,720,0,0},
 {0,203,300,697,0,0},
 {205,365,94,375,0,0},
 {205,740,83,160,0,0},
 {38,900,250,35,0,0},
 {38,935,250,88,0,0},
 {34,923,73,73,0,0},
 {159,923,73,73,73,0},
};
static const Piece Room={95,180,100,720,0,0};
static const int FloorY=888,DeckY=900,HeroX=260,HeroY=900,DeckX=55,DeckW=185,GroundY=995,WheelRadius=36;
static const float RoomFloorGap=80.0f;
static const int StoneX=296,StoneY=634,TopVisibleY=9;
}
