#pragma once
#include <algorithm>

// All rectangles use the native bottom-up coordinates. Reserve space for the
// maximum inventory before fitting the battlefield, including on 4:3 devices.
namespace PortraitGame {
// Actor size is independent of the castle camera scale.
inline float battleActorScale(int width,int largestHullWidth){return width/(2.f*largestHullWidth)*1.20f/.85f;}
inline int railLift(int width,int height){
 const float s=width/640.f;
 // Resolution alone fixes the rail. At 640-wide, its lower edge clears the
 // region panel by 21px at 850-high and 141px at 1408-high.
 const float t=std::max(0.f,std::min(1.f,(height/s-850.f)/(1408.f-850.f)));
 return (int)(120.f*s*t+.5f);
}
struct Battle {
    float scale;
    int cell,cellHeight,boardBottom,boardTop,slotTop,slotWidth,slotHeight,energyTop,actionTop,actionHeight;
    int statsTop,statsHeight,ground,headerBottom;
};
inline Battle battle(int width,int height,int rows=4,int columns=9) {
    const float s=width/640.f;
    Battle b={};b.scale=s;
    // Height changes only the battlefield above this bottom-anchored stack.
    b.actionTop=(int)(76*s);b.actionHeight=(int)(64*s);
    b.energyTop=(int)(108*s);
    b.slotWidth=(int)(348*s);
    b.slotHeight=(int)(b.slotWidth*691.f/2064.f+.5f);b.slotTop=(int)(120*s)+b.slotHeight;
    b.boardBottom=b.slotTop+(int)(16*s);
    b.cell=std::max(1,std::min((int)(64*s),(width-(int)(48*s))/std::max(1,columns)));
    b.cellHeight=b.cell;
    b.boardTop=b.boardBottom+rows*b.cell;
    b.statsHeight=(int)(48*s);b.statsTop=b.boardTop+(int)(60*s);
    b.ground=b.statsTop+(int)(18*s);b.headerBottom=height-(int)(78*s);
    b.ground+=std::min(railLift(width,height),std::max(0,b.headerBottom-b.ground-(int)(300*s)));
    (void)columns;
    return b;
}
// Fit the largest castle, including wheel contact, from the battle ground
// to the top at 1:2.2. Other aspect ratios retain this world scale.
inline float battleCastleScale(int width,float largestAssemblyHeight){
 const int referenceHeight=(int)(width*2.2f+.5f);
 return .90f*(referenceHeight-battle(width,referenceHeight).ground)/largestAssemblyHeight;
}
struct Lobby {int navTop,startTop,stageTop,manageTop,statsTop,ground;};
inline Lobby lobby(int width,int height) {
    const float s=width/640.f;
    return {(int)(84*s),(int)(170*s),(int)(280*s),
            0,(int)(296*s),(int)(336*s)+railLift(width,height)+(int)(48*s*std::max(0.f,std::min(1.f,(height/s-850.f)/558.f)))};
}
inline float castleScale(int width,int height,bool inLobby) {
    const float s=width/640.f;
    const float ground=inLobby?(float)lobby(width,height).ground:(float)battle(width,height).ground;
    const float room=std::max(60.f,height-86*s-ground);
    return std::min(width*.31f/916.f,room/1380.f);
}
}
