#pragma once
namespace NinthSdPartsStage3 {
using Piece=StarterSdParts::Piece;
static const int Width=300,Height=707;
static const Piece Pieces[9]={
 {38,110,222,100,0,0},
 {91,273,85,344,0,0},
 {2,210,295,416,0,0},
 {190,323,105,211,0,0},
 {190,534,93,92,0,0},
 {6,626,277,22,0,0},
 {7,648,276,51,0,0},
 {32,636,61,61,0,0},
 {148,636,61,61,61,0},
};
static const Piece Room={91,273,85,344,0,0};
static const int HeroX=252,HeroY=626,StoneX=293,StoneY=472,DeckX=36,DeckY=626,DeckW=193,FloorY=613,GroundY=695,WheelRadius=28,TopVisibleY=110;
static const float RoomFloorGap=38.222222f;
}
