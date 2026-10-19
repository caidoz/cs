#pragma once
namespace NinthSdPartsStage5 {
using Piece=StarterSdParts::Piece;
static const int Width=300,Height=707;
static const Piece Pieces[9]={
 {92,181,117,92,0,0},
 {91,273,85,344,0,0},
 {6,274,186,361,0,0},
 {192,392,102,163,0,0},
 {192,555,94,80,0,0},
 {6,635,279,16,0,0},
 {8,651,277,47,0,0},
 {36,640,57,57,0,0},
 {152,640,57,57,57,0},
};
static const Piece Room={91,273,85,344,0,0};
static const int HeroX=252,HeroY=634,StoneX=293,StoneY=488,DeckX=44,DeckY=634,DeckW=186,FloorY=613,GroundY=695,WheelRadius=26,TopVisibleY=181;
static const float RoomFloorGap=38.222222f;
}
