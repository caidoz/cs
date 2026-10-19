#pragma once
namespace StarterSdParts {
struct Piece { int x,y,w,h,sx,sy; };
static const int Width=1536,Height=1024;
static const Piece Pieces[9]={
 {81,31,1059,504,0,0},
 {170,535,920,185,0,0},
 {30,535,1110,185,0,0},
 {1114,67,411,483,0,0},
 {1140,550,386,170,0,0},
 {11,720,1506,90,0,0},
 {32,810,1477,182,0,0},
 {189,748,243,242,0,0},
 {860,748,243,243,243,0},
};
static const Piece Room={170,535,920,185,0,0};
static const int FloorY=708,DeckY=728,HeroX=1200,HeroY=728,DeckX=100,DeckW=1020,GroundY=990;
static const int StoneX=1205,StoneY=297;
}
