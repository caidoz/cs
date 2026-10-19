#pragma once
namespace SixthSdPartsStage2 {
using Piece=StarterSdParts::Piece;
static const int Width=450,Height=992;
static const Piece Pieces[9]={
 {19,168,241,109,0,0},
 {70,322,125,539,0,0},
 {2,277,432,603,0,0},
 {257,630,188,102,0,0},
 {257,732,161,146,0,0},
 {2,880,417,35,0,0},
 {12,915,390,67,0,0},
 {45,890,93,93,0,0},
 {216,890,93,93,93,0},
};
static const Piece Room={70,322,125,539,0,0};
static const int HeroX=368,HeroY=879,StoneX=439,StoneY=675,DeckX=15,DeckY=879,DeckW=241,FloorY=857,GroundY=980,WheelRadius=44,TopVisibleY=168;
static const float RoomFloorGap=89.833333f;
}
