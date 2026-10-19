#pragma once
namespace SixthSdPartsStage4 {
using Piece=StarterSdParts::Piece;
static const int Width=450,Height=992;
static const Piece Pieces[9]={
 {24,197,206,99,0,0},
 {70,322,125,539,0,0},
 {4,296,438,587,0,0},
 {254,640,193,99,0,0},
 {254,739,155,142,0,0},
 {2,883,408,35,0,0},
 {15,918,383,64,0,0},
 {47,894,89,89,0,0},
 {215,894,89,89,89,0},
};
static const Piece Room={70,322,125,539,0,0};
static const int HeroX=366,HeroY=882,StoneX=438,StoneY=683,DeckX=16,DeckY=882,DeckW=237,FloorY=857,GroundY=980,WheelRadius=42,TopVisibleY=197;
static const float RoomFloorGap=89.833333f;
}
