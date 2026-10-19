#pragma once
namespace EighthSdPartsStage1 {
using Piece=StarterSdParts::Piece;
static const int Width=340,Height=448;
static const Piece Pieces[9]={
 {38,129,268,55,0,0},
 {45,223,97,155,0,0},
 {9,184,220,206,0,0},
 {196,286,122,58,0,0},
 {196,344,137,46,0,0},
 {6,390,327,13,0,0},
 {12,403,320,33,0,0},
 {34,389,49,49,0,0},
 {172,389,49,49,49,0},
};
static const Piece Room={45,223,97,155,0,0};
static const int HeroX=271,HeroY=389,StoneX=291,StoneY=306,DeckX=-3,DeckY=389,DeckW=239,FloorY=374,GroundY=436,WheelRadius=22,TopVisibleY=129;
static const float RoomFloorGap=19.375000f;
}
