#pragma once
namespace NinthSdParts {
using Piece=StarterSdParts::Piece;
static const int Width=300,Height=707;
static const Piece Pieces[9]={
 {5,8,283,116,0,0},
 {91,273,85,344,0,0},
 {6,124,187,494,0,0},
 {193,265,99,243,0,0},
 {193,508,101,110,0,0},
 {5,618,288,27,0,0},
 {6,645,287,52,0,0},
 {30,632,65,65,0,0},
 {150,632,65,65,65,0},
};
static const Piece Room={91,273,85,344,0,0};
static const int HeroX=254,HeroY=617,StoneX=273,StoneY=445,DeckX=30,DeckY=617,DeckW=202,FloorY=613,GroundY=695,WheelRadius=30,TopVisibleY=8;
static const float RoomFloorGap=38.222222f;
}
