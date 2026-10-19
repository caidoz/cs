#pragma once
namespace EighthSdPartsStage2 {
using Piece=StarterSdParts::Piece;
static const int Width=340,Height=448;
static const Piece Pieces[9]={
 {41,138,105,57,0,0},
 {45,223,97,155,0,0},
 {10,195,275,201,0,0},
 {195,293,108,57,0,0},
 {195,350,140,46,0,0},
 {7,396,324,14,0,0},
 {12,410,319,28,0,0},
 {37,399,39,39,0,0},
 {175,399,39,39,39,0},
};
static const Piece Room={45,223,97,155,0,0};
static const int HeroX=270,HeroY=396,StoneX=290,StoneY=312,DeckX=9,DeckY=396,DeckW=226,FloorY=374,GroundY=436,WheelRadius=17,TopVisibleY=138;
static const float RoomFloorGap=19.375000f;
}
