#pragma once
namespace IndividualCastleRooms {
// Safe room apertures in original-image pixels. Roofs, weapons, wheels and
// the external walkway stay outside these rectangles.
struct Aperture { int x,y,w,h,columns; };
// Shared room dimensions stay inside the narrower upper bodies as well.
static const float RoomWidth=140.0f,FloorHeight=40.0f,BottomLift=4.0f;
static const Aperture Rooms[10]={
 {300,490,610,220,1}, {260,330,530,460,1},
 {350,460,410,470,1}, {330,460,450,540,1},
 {200,500,500,600,1}, {295,410,410,820,1},
 {240,460,490,760,1}, {240,430,450,830,1},
 {230,480,420,860,1}, {255,500,355,870,1}
};
}
