#pragma once
namespace SeventhSdPartsStage5 {
using Piece=StarterSdParts::Piece;
static const int Width=390,Height=670;
static const Piece Pieces[9]={
 {77,204,146,97,0,0},
 {124,301,84,269,0,0},
 {4,301,239,292,0,0},
 {209,439,174,85,0,0},
 {209,524,121,69,0,0},
 {4,593,310,21,0,0},
 {13,614,238,49,0,0},
 {29,595,65,65,0,0},
 {170,595,65,65,65,0},
};
static const Piece Room={124,301,84,269,0,0};
static const int HeroX=284,HeroY=593,StoneX=375,StoneY=497,DeckX=13,DeckY=593,DeckW=236,FloorY=566,GroundY=658,WheelRadius=31,TopVisibleY=204;
static const float RoomFloorGap=38.428571f;
}
