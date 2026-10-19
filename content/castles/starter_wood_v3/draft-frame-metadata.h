#pragma once
namespace StarterWoodCastle {
struct Frame { int x,y,w,h,width,height; };
static const Frame Frames[6]={
 {46,0,1018,347,736,256}, // roof
 {64,354,983,306,640,128}, // facade
 {30,683,1056,211,736,144}, // chassis
 {446,894,216,215,128,128}, // wheel
 {341,1110,485,161,192,128}, // command_platform
 {399,1278,358,170,168,104}, // catapult
};
}
