#pragma once
namespace EighthSdPartsStage5 {
using Piece=StarterSdParts::Piece;
static const int Width=340,Height=448;
static const Piece Pieces[9]={
 {45,176,60,47,0,0},
 {45,223,97,155,0,0},
 {9,228,269,167,0,0},
 {178,308,105,49,0,0},
 {178,357,154,38,0,0},
 {6,395,327,13,0,0},
 {11,408,321,31,0,0},
 {33,396,43,43,0,0},
 {156,396,43,43,43,0},
};
static const Piece Room={45,223,97,155,0,0};
static const int HeroX=262,HeroY=395,StoneX=285,StoneY=324,DeckX=5,DeckY=395,DeckW=218,FloorY=374,GroundY=436,WheelRadius=19,TopVisibleY=176;
static const float RoomFloorGap=19.375000f;
}
