#pragma once
namespace StarterSdPartsStage5 {
using Piece=StarterSdParts::Piece;
static const int Width=1536,Height=1024;
static const Piece Pieces[9]={
 {0,17,1140,518,0,0},
 {170,535,920,185,0,0},
 {0,535,1140,185,0,0},
 {1100,55,436,495,0,0},
 {1140,550,396,170,0,0},
 {13,720,1453,90,0,0},
 {31,810,1435,185,0,0},
 {189,748,243,243,0,0},
 {860,748,243,243,243,0},
};
static const Piece Room={170,535,920,185,0,0};
static const int FloorY=708,DeckY=728,HeroX=1200,HeroY=728,DeckX=100,DeckW=1020,GroundY=990;
static const int StoneX=1208,StoneY=270;
}
