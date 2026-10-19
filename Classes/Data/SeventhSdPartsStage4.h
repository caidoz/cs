#pragma once
namespace SeventhSdPartsStage4 {
using Piece=StarterSdParts::Piece;
static const int Width=390,Height=670;
static const Piece Pieces[9]={
 {24,137,280,106,0,0},
 {124,301,84,269,0,0},
 {9,243,353,335,0,0},
 {223,419,160,79,0,0},
 {223,498,122,80,0,0},
 {6,578,344,27,0,0},
 {16,605,259,55,0,0},
 {28,585,75,75,0,0},
 {179,585,75,75,75,0},
};
static const Piece Room={124,301,84,269,0,0};
static const int HeroX=292,HeroY=578,StoneX=376,StoneY=467,DeckX=10,DeckY=578,DeckW=251,FloorY=566,GroundY=658,WheelRadius=36,TopVisibleY=137;
static const float RoomFloorGap=38.428571f;
}
