#pragma once
#include <algorithm>

// All rectangles use the native bottom-up coordinates. Reserve space for the
// maximum inventory before fitting the battlefield, including on 4:3 devices.
namespace PortraitGame {
struct Battle {
    float scale;
    int cell,cellHeight,boardBottom,boardTop,slotTop,slotWidth,slotHeight,energyTop,actionTop,actionHeight;
    int statsTop,statsHeight,ground,headerBottom;
};
inline Battle battle(int width,int height,int rows=6,int columns=8) {
    const float s=width/640.f;
    Battle b={};b.scale=s;
    // Height changes only the battlefield above this bottom-anchored stack.
    b.actionTop=(int)(76*s);b.actionHeight=(int)(64*s);
    b.energyTop=(int)(108*s);
    b.slotWidth=(int)(348*s);
    b.slotHeight=(int)(b.slotWidth*691.f/2064.f+.5f);b.slotTop=(int)(120*s)+b.slotHeight;
    b.boardBottom=b.slotTop+(int)(16*s);
    b.cell=std::max(1,(int)(64*s));
    b.cellHeight=b.cell;
    b.boardTop=b.boardBottom+rows*b.cell;
    b.statsHeight=(int)(48*s);b.statsTop=b.boardTop+(int)(60*s);
    b.ground=b.statsTop+(int)(18*s);b.headerBottom=height-(int)(78*s);
    (void)columns;
    return b;
}
struct Lobby {int navTop,startTop,stageTop,manageTop,statsTop,ground;};
inline Lobby lobby(int width,int height) {
    const float s=width/640.f;
    (void)height;
    return {(int)(84*s),(int)(170*s),(int)(280*s),
            0,(int)(296*s),(int)(336*s)};
}
inline float castleScale(int width,int height,bool inLobby) {
    const float s=width/640.f;
    const float ground=inLobby?(float)lobby(width,height).ground:(float)battle(width,height).ground;
    const float room=std::max(60.f,height-86*s-ground);
    return std::min(width*.31f/916.f,room/1380.f);
}
}
