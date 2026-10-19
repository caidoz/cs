#pragma once
namespace SeventhSdPartsStage4 {
using Piece=StarterSdParts::Piece;
static const int Width=390,Height=1024;
static const Piece Pieces[9]={
 {35,16,291,212,0,0},
 {140,228,120,672,0,0},
 {15,228,365,672,0,0},
 {260,585,128,159,0,0},
 {260,744,97,156,0,0},
 {9,900,353,30,0,0},
 {20,930,282,82,0,0},
 {45,905,91,90,0,0},
 {210,905,90,90,91,0},
};
static const Piece Room={140,228,120,672,0,0};
static const int FloorY=888,DeckY=900,HeroX=315,HeroY=900,DeckX=15,DeckW=275,GroundY=995,WheelRadius=45;
static const float RoomFloorGap=96.0f;
static const int StoneX=382,StoneY=682,TopVisibleY=19;
}
