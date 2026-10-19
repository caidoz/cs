#pragma once
namespace EighthSdPartsStage3 {
using Piece=StarterSdParts::Piece;
static const int Width=340,Height=448;
static const Piece Pieces[9]={
 {34,145,74,54,0,0},
 {45,223,97,155,0,0},
 {10,199,273,192,0,0},
 {192,293,102,55,0,0},
 {192,348,141,43,0,0},
 {8,391,323,14,0,0},
 {14,405,317,31,0,0},
 {38,393,45,45,0,0},
 {169,393,45,45,45,0},
};
static const Piece Room={45,223,97,155,0,0};
static const int HeroX=269,HeroY=391,StoneX=289,StoneY=312,DeckX=10,DeckY=391,DeckW=223,FloorY=374,GroundY=436,WheelRadius=21,TopVisibleY=145;
static const float RoomFloorGap=19.375000f;
}
