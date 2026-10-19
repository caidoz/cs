#pragma once
namespace ThirdSdPartsStage2 {
using Piece=StarterSdParts::Piece;
static const int Width=1133,Height=1388;
static const Piece Pieces[9]={
 {0,109,799,381,0,0},
 {280,510,470,530,0,0},
 {0,490,1101,560,0,0},
 {810,403,306,447,0,0},
 {810,850,293,190,0,0},
 {0,1050,1117,85,0,0},
 {26,1135,1074,222,0,0},
 {175,1123,199,199,0,0},
 {625,1123,199,199,199,0},
};
static const Piece Room={280,510,470,530,0,0};
static const int FloorY=1027,DeckY=1082,HeroX=960,HeroY=1082,DeckX=70,DeckW=720,GroundY=1321,WheelRadius=99;
static const float RoomFloorGap=530.0f/3.0f;
static const int StoneX=1095,StoneY=770;
}
