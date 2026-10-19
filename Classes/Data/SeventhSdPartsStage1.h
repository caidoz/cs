#pragma once
namespace SeventhSdPartsStage1 {
using Piece=StarterSdParts::Piece;
static const int Width=390,Height=670;
static const Piece Pieces[9]={
 {42,105,207,114,0,0},
 {124,301,84,269,0,0},
 {8,219,344,353,0,0},
 {237,417,133,70,0,0},
 {237,487,145,85,0,0},
 {1,572,383,29,0,0},
 {11,601,283,64,0,0},
 {28,579,81,81,0,0},
 {191,579,81,81,81,0},
};
static const Piece Room={124,301,84,269,0,0};
static const int HeroX=300,HeroY=572,StoneX=378,StoneY=455,DeckX=12,DeckY=572,DeckW=259,FloorY=566,GroundY=658,WheelRadius=38,TopVisibleY=105;
static const float RoomFloorGap=38.428571f;
}
