#pragma once

// Basic throw only. Legacy Max skills and weapon definitions stay unchanged.
namespace StageBoomerangModel {
enum Phase { Ready, Outbound, Returning, Recovering };
struct Point { float x, y; };
struct Runtime {
    Phase phase;
    Point position, start;
    int elapsed;
    Runtime() : phase(Ready), position{0,0}, start{0,0}, elapsed(0) {}
    bool Busy() const { return phase != Ready; }
    bool Throw(Point owner) {
        if(Busy()) return false;
        start=position=owner;elapsed=0;phase=Outbound;return true;
    }
    // Returns true once, on outbound contact. An invalid target still returns home.
    bool Step(bool running, bool targetValid, Point target, Point owner,
              int outboundFrames, int returnFrames, int recoveryFrames) {
        if(!running || phase==Ready) return false;
        if(phase==Outbound) {
            if(!targetValid) { start=position;elapsed=0;phase=Returning;return false; }
            const float t=float(++elapsed)/outboundFrames;
            position={start.x+(target.x-start.x)*t,start.y+(target.y-start.y)*t};
            if(elapsed>=outboundFrames) {
                start=position;elapsed=0;phase=Returning;return true;
            }
        } else if(phase==Returning) {
            const float t=float(++elapsed)/returnFrames;
            position={start.x+(owner.x-start.x)*t,start.y+(owner.y-start.y)*t};
            if(elapsed>=returnFrames) {position=owner;elapsed=0;phase=Recovering;}
        } else if(++elapsed>=recoveryFrames) {phase=Ready;elapsed=0;}
        return false;
    }
};
}
