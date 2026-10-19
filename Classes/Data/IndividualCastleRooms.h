#pragma once
namespace IndividualCastleRooms {
struct Aperture {int x,y,w,h,columns;};
static const float RoomWidth=140.0f,FloorHeight=40.0f,BottomLift=4.0f;
static const Aperture Rooms[10]={
 {250,470,700,240,1},
 {320,360,520,430,1},
 {375,420,400,510,1},
 {390,440,410,580,1},
 {260,470,420,650,1},
 {350,400,400,830,1},
 {300,420,420,815,1},
 {330,390,420,850,1},
 {300,450,360,900,1},
 {325,450,350,890,1},
};
}
