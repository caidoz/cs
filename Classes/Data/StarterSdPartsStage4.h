#pragma once
namespace StarterSdPartsStage4 {
using Piece=StarterSdParts::Piece;
static const int Width=1536,Height=1024;
static const Piece Pieces[9]={
 {81,29,1059,506,0,0},
 {170,535,920,185,0,0},
 {28,535,1112,185,0,0},
 {1100,97,436,453,0,0},
 {1140,550,396,170,0,0},
 {16,720,1297,90,0,0},
 {35,810,1307,196,0,0},
 {189,748,243,243,0,0},
 {860,748,243,243,243,0},
};
static const Piece Room={170,535,920,185,0,0};
static const int FloorY=708,DeckY=728,HeroX=1200,HeroY=728,DeckX=100,DeckW=1020,GroundY=990;
static const int StoneX=1204,StoneY=286;
}
