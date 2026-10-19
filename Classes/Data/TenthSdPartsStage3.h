#pragma once
namespace TenthSdPartsStage3 {
using Piece=StarterSdParts::Piece;
static const int Width=270,Height=640;
static const Piece Pieces[9]={
 {13,156,150,72,0,0},
 {72,229,83,328,0,0},
 {6,228,172,342,0,0},
 {178,343,87,154,0,0},
 {178,497,76,73,0,0},
 {6,570,248,13,0,0},
 {9,583,245,48,0,0},
 {37,577,53,53,0,0},
 {135,577,53,53,53,0},
};
static const Piece Room={72,229,83,328,0,0};
static const int HeroX=211,HeroY=570,StoneX=263,StoneY=453,DeckX=34,DeckY=570,DeckW=171,FloorY=553,GroundY=628,WheelRadius=24,TopVisibleY=156;
static const float RoomFloorGap=32.800000f;
}
