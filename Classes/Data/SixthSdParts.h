#pragma once
namespace SixthSdParts {
using Piece=StarterSdParts::Piece;
static const int Width=450,Height=992;
static const Piece Pieces[9]={
 {26,8,245,121,0,0},
 {70,322,125,539,0,0},
 {5,129,434,735,0,0},
 {295,560,150,124,0,0},
 {295,684,143,178,0,0},
 {5,864,437,41,0,0},
 {14,905,413,81,0,0},
 {52,877,105,105,0,0},
 {250,877,105,105,105,0},
};
static const Piece Room={70,322,125,539,0,0};
static const int HeroX=386,HeroY=864,StoneX=443,StoneY=614,DeckX=14,DeckY=864,DeckW=281,FloorY=857,GroundY=980,WheelRadius=50,TopVisibleY=8;
static const float RoomFloorGap=89.833333f;
}
