#pragma once
namespace StarterSdPartsStage1 {
using Piece=StarterSdParts::Piece;
static const int Width=1536,Height=1024;
static const Piece Pieces[9]={
 {0,37,1140,498,0,0},
 {170,535,920,185,0,0},
 {24,535,1116,185,0,0},
 {1111,101,416,449,0,0},
 {1140,550,395,170,0,0},
 {0,720,1315,90,0,0},
 {30,810,1382,194,0,0},
 {189,748,243,243,0,0},
 {860,748,243,242,243,0},
};
static const Piece Room={170,535,920,185,0,0};
static const int FloorY=708,DeckY=728,HeroX=1200,HeroY=728,DeckX=100,DeckW=1020,GroundY=990;
static const int StoneX=1201,StoneY=291;
}
