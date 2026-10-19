#pragma once
namespace ThirdSdParts {
using Piece=StarterSdParts::Piece;
static const int Width=1133,Height=1388;
static const Piece Pieces[9]={
 {25,82,752,408,0,0},
 {280,510,470,530,0,0},
 {33,490,1068,560,0,0},
 {810,19,303,831,0,0},
 {810,850,294,190,0,0},
 {0,1050,1133,85,0,0},
 {0,1135,1104,245,0,0},
 {175,1123,199,198,0,0},
 {625,1123,199,199,199,0},
};
static const Piece Room={280,510,470,530,0,0};
static const int FloorY=1027,DeckY=1082,HeroX=960,HeroY=1082,DeckX=70,DeckW=720,GroundY=1321,WheelRadius=99;
static const float RoomFloorGap=530.0f/3.0f;
static const int StoneX=1095,StoneY=770;
}
