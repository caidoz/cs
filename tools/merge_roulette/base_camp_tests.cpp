#include "../../Classes/BaseCampPresentation.h"
#include <cassert>
#include <iostream>
int main(){
 using namespace BaseCamp;
 assert(travel(-1)==0&&closure(-1)==0&&uiExit(-1)==0);
 for(int i=0;i<4;++i)assert(recall(1.15f,i)==1.f);
 assert(closure(1.15f)==0&&closure(1.65f)==1);
 assert(travel(1.65f)==0&&travel(duration())==1);
 assert(uiExit(.4f)==1);
 float previous=0;for(int i=0;i<=285;++i){float q=travel(i/100.f);assert(q>=previous&&q>=0&&q<=1);previous=q;}
 assert(wander(0,1)!=wander(1,1));
 std::cout<<"PASS recall precedes closure, closure precedes travel, UI exits and scale interpolation is bounded\n";
}
