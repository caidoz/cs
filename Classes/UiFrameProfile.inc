// Opt-in native comparison; does not run or write files in normal gameplay.
#include <chrono>
namespace UiFrameProfile {
using Clock=std::chrono::steady_clock;
struct Sample {
 bool enabled;Clock::time_point start,mark;
 Sample():enabled(getenv("CS_UI_PROFILE_PATH")!=NULL){if(enabled)start=mark=Clock::now();}
 void Mark(const char* name){
  if(!enabled)return;const auto now=Clock::now();
  if(frame%20==0){FILE* f=fopen(getenv("CS_UI_PROFILE_PATH"),"a");if(f){fprintf(f,"phase %s depth=%d ms=%.3f\n",name,menuDepth,std::chrono::duration<double,std::milli>(now-mark).count());fclose(f);}}
  mark=now;
 }
 ~Sample(){
  if(!enabled || drawHandle!=MD_LOBBY)return;
  const int bucket=curMenu==MENU_COLLECTIONS?(menuDepth==1?2:1):0;
  struct Stats {int count=0;double cpu=0,gap=0,sprites=0;};
  static Stats stats[3];static auto previous=start;static int previousBucket=-1;
  const double gap=std::chrono::duration<double,std::milli>(start-previous).count();previous=start;
  if(bucket!=previousBucket){previousBucket=bucket;stats[bucket]=Stats();return;}
  Stats& s=stats[bucket];++s.count;s.cpu+=std::chrono::duration<double,std::milli>(Clock::now()-start).count();
  s.gap+=gap;s.sprites+=curRenderCnt;
  if(s.count==20){
   FILE* f=fopen(getenv("CS_UI_PROFILE_PATH"),"a");
   if(f){fprintf(f,"%s cpu_ms=%.3f frame_ms=%.3f sprites=%.1f\n",bucket==2?"detail":bucket==1?"equipment":"lobby",s.cpu/s.count,s.gap/s.count,s.sprites/s.count);fclose(f);}
   s=Stats();
  }
 }
};
}
