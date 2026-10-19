#pragma once
namespace NinthSdParts {
using Piece=StarterSdParts::Piece;
static const int Width=300,Height=1024;
static const Piece Pieces[9]={
 {14,12,277,168,0,0},
 {95,180,100,720,0,0},
 {7,185,285,715,0,0},
 {205,385,93,355,0,0},
 {205,740,91,160,0,0},
 {45,900,251,35,0,0},
 {65,935,230,66,0,0},
 {34,923,73,73,0,0},
 {159,923,73,73,73,0},
};
static const Piece Room={95,180,100,720,0,0};
static const int FloorY=888,DeckY=900,HeroX=260,HeroY=900,DeckX=55,DeckW=185,GroundY=995,WheelRadius=36;
static const float RoomFloorGap=80.0f;
static const int StoneX=277,StoneY=649,TopVisibleY=17;
}
