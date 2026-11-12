#pragma once
#include <chrono>
#include <cstdio>
#include <cstdlib>
namespace MergeRenderProfile {
using Clock=std::chrono::steady_clock;
struct Samples {
    int frames=0,count=0;
    double parts[5]={},interval=0,maxInterval=0;
    Clock::time_point previous;
};
inline Samples& samples(){static Samples value;return value;}
struct Frame {
    const char* path=std::getenv("CS_MERGE_PROFILE_PATH");
    Clock::time_point start=Clock::now(),mark=start;
    double parts[5]={};
    bool collecting=false;
    Frame() {
        if(!path)return;
        auto& s=samples();
        collecting=s.frames++>=90;
        if(collecting) {
            const double ms=std::chrono::duration<double,std::milli>(start-s.previous).count();
            s.interval+=ms;s.maxInterval=std::max(s.maxInterval,ms);
        }
        s.previous=start;
    }
    void stamp(int part) {
        if(!path)return;
        auto now=Clock::now();parts[part]=std::chrono::duration<double,std::milli>(now-mark).count();mark=now;
    }
    ~Frame() {
        if(!path||!collecting)return;
        stamp(4);auto& s=samples();++s.count;
        for(int i=0;i<5;++i)s.parts[i]+=parts[i];
        if(s.count%240)return;
        FILE* file=std::fopen(path,"w");if(!file)return;
        std::fprintf(file,"samples=%d frame_ms=%.3f max_frame_ms=%.3f simulation_ms=%.3f world_ms=%.3f hud_ms=%.3f grid_ms=%.3f effects_controls_ms=%.3f\n",
            s.count,s.interval/s.count,s.maxInterval,s.parts[0]/s.count,s.parts[1]/s.count,s.parts[2]/s.count,s.parts[3]/s.count,s.parts[4]/s.count);
        std::fclose(file);
    }
};
}
