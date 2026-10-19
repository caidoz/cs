#pragma once
namespace ThirdSdPartsStage3 {
using Piece=StarterSdParts::Piece;
static const int Width=1133,Height=1388;
static const Piece Pieces[9]={
 {20,63,710,427,0,0},
 {280,510,470,530,0,0},
 {33,490,1050,560,0,0},
 {810,51,302,799,0,0},
 {810,850,302,190,0,0},
 {6,1050,1106,85,0,0},
 {21,1135,1074,253,0,0},
 {175,1123,199,199,0,0},
 {625,1123,199,199,199,0},
};
static const Piece Room={280,510,470,530,0,0};
static const int FloorY=1027,DeckY=1082,HeroX=960,HeroY=1082,DeckX=70,DeckW=720,GroundY=1321,WheelRadius=99;
static const float RoomFloorGap=530.0f/3.0f;
static const int StoneX=1095,StoneY=770;
}
