#pragma once
namespace SecondSdParts {
using Piece=StarterSdParts::Piece;
static const int Width=1254,Height=1254;
static const Piece Pieces[9]={
 {0,31,900,504,0,0},
 {140,535,710,345,0,0},
 {23,535,1216,355,0,0},
 {900,47,342,653,0,0},
 {900,700,338,180,0,0},
 {0,890,1254,90,0,0},
 {0,980,1236,274,0,0},
 {213,958,205,205,0,0},
 {691,958,205,205,205,0},
};
static const Piece Room={140,535,710,345,0,0};
static const int FloorY=865,DeckY=925,HeroX=1060,HeroY=925,DeckX=80,DeckW=790,GroundY=1163;
static const int StoneX=1210,StoneY=610;
}
