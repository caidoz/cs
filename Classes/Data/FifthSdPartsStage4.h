#pragma once
namespace FifthSdPartsStage4 {
using Piece=StarterSdParts::Piece;
static const int Width=887,Height=1774;
static const Piece Pieces[9]={
 {41,37,653,363,0,0},
 {290,400,330,1030,0,0},
 {0,400,875,1040,0,0},
 {660,1040,227,160,0,0},
 {660,1200,209,230,0,0},
 {0,1440,887,75,0,0},
 {17,1515,869,211,0,0},
 {116,1484,205,204,0,0},
 {516,1484,205,205,205,0},
};
static const Piece Room={290,400,330,1030,0,0};
static const int FloorY=1417,DeckY=1440,HeroX=780,HeroY=1440,DeckX=45,DeckW=625,GroundY=1688,WheelRadius=102;
static const float RoomFloorGap=206.0f;
static const int StoneX=875,StoneY=1115,TopVisibleY=70;
}
