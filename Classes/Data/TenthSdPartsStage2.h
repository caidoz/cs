#pragma once
namespace TenthSdPartsStage2 {
using Piece=StarterSdParts::Piece;
static const int Width=270,Height=640;
static const Piece Pieces[9]={
 {78,155,156,74,0,0},
 {72,229,83,328,0,0},
 {6,229,230,341,0,0},
 {173,343,90,154,0,0},
 {173,497,70,73,0,0},
 {6,570,234,11,0,0},
 {8,581,231,48,0,0},
 {33,576,55,55,0,0},
 {128,576,55,55,55,0},
};
static const Piece Room={72,229,83,328,0,0};
static const int HeroX=208,HeroY=569,StoneX=264,StoneY=438,DeckX=31,DeckY=569,DeckW=171,FloorY=553,GroundY=628,WheelRadius=25,TopVisibleY=155;
static const float RoomFloorGap=32.800000f;
}
