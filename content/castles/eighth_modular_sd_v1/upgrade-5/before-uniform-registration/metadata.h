#pragma once
namespace EighthSdPartsStage5 {
using Piece=StarterSdParts::Piece;
static const int Width=340,Height=1024;
static const Piece Pieces[9]={
 {68,5,69,191,0,0},
 {60,196,120,704,0,0},
 {19,284,279,616,0,0},
 {220,540,81,200,0,0},
 {220,740,119,160,0,0},
 {17,900,322,35,0,0},
 {23,935,316,88,0,0},
 {40,915,81,81,0,0},
 {180,915,80,81,81,0},
};
static const Piece Room={60,196,120,704,0,0};
static const int FloorY=888,DeckY=900,HeroX=285,HeroY=900,DeckX=15,DeckW=240,GroundY=995,WheelRadius=40;
static const float RoomFloorGap=88.0f;
static const int StoneX=302,StoneY=610,TopVisibleY=14;
}
