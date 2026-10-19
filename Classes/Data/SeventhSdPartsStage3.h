#pragma once
namespace SeventhSdPartsStage3 {
using Piece=StarterSdParts::Piece;
static const int Width=390,Height=670;
static const Piece Pieces[9]={
 {101,135,148,112,0,0},
 {124,301,84,269,0,0},
 {5,247,257,333,0,0},
 {232,427,152,74,0,0},
 {232,501,136,79,0,0},
 {5,580,367,25,0,0},
 {12,605,315,58,0,0},
 {29,583,77,77,0,0},
 {187,583,77,77,77,0},
};
static const Piece Room={124,301,84,269,0,0};
static const int HeroX=297,HeroY=580,StoneX=377,StoneY=470,DeckX=15,DeckY=580,DeckW=252,FloorY=566,GroundY=658,WheelRadius=37,TopVisibleY=135;
static const float RoomFloorGap=38.428571f;
}
