#pragma once
namespace NinthSdPartsStage1 {
using Piece=StarterSdParts::Piece;
static const int Width=300,Height=707;
static const Piece Pieces[9]={
 {19,102,154,106,0,0},
 {91,273,85,344,0,0},
 {0,208,190,420,0,0},
 {190,330,109,205,0,0},
 {190,535,105,93,0,0},
 {6,628,289,21,0,0},
 {7,649,287,49,0,0},
 {33,638,59,59,0,0},
 {150,638,59,59,59,0},
};
static const Piece Room={91,273,85,344,0,0};
static const int HeroX=252,HeroY=627,StoneX=283,StoneY=489,DeckX=36,DeckY=627,DeckW=193,FloorY=613,GroundY=695,WheelRadius=27,TopVisibleY=102;
static const float RoomFloorGap=38.222222f;
}
