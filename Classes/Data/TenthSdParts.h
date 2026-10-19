#pragma once
namespace TenthSdParts {
using Piece=StarterSdParts::Piece;
static const int Width=270,Height=640;
static const Piece Pieces[9]={
 {78,10,86,96,0,0},
 {72,229,83,328,0,0},
 {6,106,174,452,0,0},
 {180,272,73,189,0,0},
 {180,461,84,97,0,0},
 {6,558,258,19,0,0},
 {7,577,255,53,0,0},
 {30,572,57,57,0,0},
 {135,572,57,57,57,0},
};
static const Piece Room={72,229,83,328,0,0};
static const int HeroX=212,HeroY=558,StoneX=251,StoneY=404,DeckX=12,DeckY=558,DeckW=195,FloorY=553,GroundY=628,WheelRadius=27,TopVisibleY=10;
static const float RoomFloorGap=32.800000f;
}
