#pragma once
namespace EighthSdPartsStage4 {
using Piece=StarterSdParts::Piece;
static const int Width=340,Height=448;
static const Piece Pieces[9]={
 {50,146,81,52,0,0},
 {45,223,97,155,0,0},
 {8,198,297,195,0,0},
 {193,293,116,55,0,0},
 {193,348,140,45,0,0},
 {7,393,325,14,0,0},
 {13,407,319,31,0,0},
 {35,395,43,43,0,0},
 {171,395,43,43,43,0},
};
static const Piece Room={45,223,97,155,0,0};
static const int HeroX=269,HeroY=392,StoneX=289,StoneY=312,DeckX=7,DeckY=392,DeckW=226,FloorY=374,GroundY=436,WheelRadius=19,TopVisibleY=146;
static const float RoomFloorGap=19.375000f;
}
