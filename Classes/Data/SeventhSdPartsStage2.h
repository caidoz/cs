#pragma once
namespace SeventhSdPartsStage2 {
using Piece=StarterSdParts::Piece;
static const int Width=390,Height=670;
static const Piece Pieces[9]={
 {99,102,168,114,0,0},
 {124,301,84,269,0,0},
 {1,216,377,357,0,0},
 {232,384,153,103,0,0},
 {232,487,143,86,0,0},
 {1,573,374,28,0,0},
 {13,601,275,59,0,0},
 {34,580,79,79,0,0},
 {187,580,79,79,79,0},
};
static const Piece Room={124,301,84,269,0,0};
static const int HeroX=297,HeroY=572,StoneX=377,StoneY=454,DeckX=13,DeckY=572,DeckW=255,FloorY=566,GroundY=658,WheelRadius=38,TopVisibleY=102;
static const float RoomFloorGap=38.428571f;
}
