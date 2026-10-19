#pragma once
namespace SeventhSdParts {
using Piece=StarterSdParts::Piece;
static const int Width=390,Height=670;
static const Piece Pieces[9]={
 {38,11,246,135,0,0},
 {124,301,84,269,0,0},
 {7,146,276,425,0,0},
 {252,389,129,82,0,0},
 {252,471,128,100,0,0},
 {2,571,382,28,0,0},
 {5,599,310,63,0,0},
 {28,575,85,85,0,0},
 {204,575,85,85,85,0},
};
static const Piece Room={124,301,84,269,0,0};
static const int HeroX=309,HeroY=571,StoneX=380,StoneY=431,DeckX=4,DeckY=571,DeckW=279,FloorY=566,GroundY=658,WheelRadius=41,TopVisibleY=11;
static const float RoomFloorGap=38.428571f;
}
