#pragma once
namespace NinthSdPartsStage1 {
using Piece=StarterSdParts::Piece;
static const int Width=300,Height=1024;
static const Piece Pieces[9]={
 {49,0,237,180,0,0},
 {95,180,100,720,0,0},
 {0,185,205,715,0,0},
 {205,366,95,374,0,0},
 {205,740,94,160,0,0},
 {39,900,260,35,0,0},
 {40,935,258,88,0,0},
 {34,923,73,73,0,0},
 {159,923,73,73,73,0},
};
static const Piece Room={95,180,100,720,0,0};
static const int FloorY=888,DeckY=900,HeroX=260,HeroY=900,DeckX=55,DeckW=185,GroundY=995,WheelRadius=36;
static const float RoomFloorGap=80.0f;
static const int StoneX=288,StoneY=662,TopVisibleY=6;
}
