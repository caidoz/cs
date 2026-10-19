#pragma once
namespace StarterSdPartsStage2 {
using Piece=StarterSdParts::Piece;
static const int Width=1536,Height=1024;
static const Piece Pieces[9]={
 {0,55,1140,480,0,0},
 {170,535,920,185,0,0},
 {31,535,1109,185,0,0},
 {1120,21,404,529,0,0},
 {1140,550,386,170,0,0},
 {17,720,1295,90,0,0},
 {30,810,1220,182,0,0},
 {189,748,243,242,0,0},
 {860,748,243,242,243,0},
};
static const Piece Room={170,535,920,185,0,0};
static const int FloorY=708,DeckY=728,HeroX=1200,HeroY=728,DeckX=100,DeckW=1020,GroundY=990;
static const int StoneX=1201,StoneY=288;
}
