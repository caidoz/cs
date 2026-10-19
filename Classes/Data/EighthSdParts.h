#pragma once
namespace EighthSdParts {
using Piece=StarterSdParts::Piece;
static const int Width=340,Height=448;
static const Piece Pieces[9]={
 {35,11,82,77,0,0},
 {45,223,97,155,0,0},
 {12,88,184,291,0,0},
 {196,235,94,79,0,0},
 {196,314,137,65,0,0},
 {7,379,326,17,0,0},
 {11,396,321,41,0,0},
 {31,381,57,57,0,0},
 {167,381,57,57,57,0},
};
static const Piece Room={45,223,97,155,0,0};
static const int HeroX=272,HeroY=379,StoneX=291,StoneY=259,DeckX=4,DeckY=379,DeckW=232,FloorY=374,GroundY=436,WheelRadius=27,TopVisibleY=11;
static const float RoomFloorGap=19.375000f;
}
