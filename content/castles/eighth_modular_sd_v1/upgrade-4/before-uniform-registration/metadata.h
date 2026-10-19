#pragma once
namespace EighthSdPartsStage4 {
using Piece=StarterSdParts::Piece;
static const int Width=340,Height=1024;
static const Piece Pieces[9]={
 {72,5,86,191,0,0},
 {60,196,120,704,0,0},
 {17,258,298,642,0,0},
 {220,540,99,200,0,0},
 {220,740,119,160,0,0},
 {14,900,324,35,0,0},
 {0,935,338,89,0,0},
 {40,915,81,81,0,0},
 {180,915,80,81,81,0},
};
static const Piece Room={60,196,120,704,0,0};
static const int FloorY=888,DeckY=900,HeroX=285,HeroY=900,DeckX=15,DeckW=240,GroundY=995,WheelRadius=40;
static const float RoomFloorGap=88.0f;
static const int StoneX=302,StoneY=610,TopVisibleY=14;
}
