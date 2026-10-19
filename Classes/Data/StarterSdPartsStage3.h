#pragma once
namespace StarterSdPartsStage3 {
using Piece=StarterSdParts::Piece;
static const int Width=1536,Height=1024;
static const Piece Pieces[9]={
 {73,25,1067,510,0,0},
 {170,535,920,185,0,0},
 {17,535,1123,185,0,0},
 {1100,53,436,497,0,0},
 {1140,550,396,170,0,0},
 {0,720,1520,90,0,0},
 {34,810,1454,184,0,0},
 {189,748,243,243,0,0},
 {860,748,243,243,243,0},
};
static const Piece Room={170,535,920,185,0,0};
static const int FloorY=708,DeckY=728,HeroX=1200,HeroY=728,DeckX=100,DeckW=1020,GroundY=990;
static const int StoneX=1214,StoneY=286;
}
