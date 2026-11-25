#include "../../Classes/LobbyCampModel.h"
#include <cassert>
#include <iostream>
int main(){
 using namespace LobbyCamp;
 assert(highestOwned({}).empty());
 auto a=highestOwned({{4,1,1}});assert(a.size()==1&&a[0].id==4);
 a=highestOwned({{4,1,0},{-1,6,9},{64,6,9}});assert(a.empty());
 a=highestOwned({{1,2,1},{2,6,1},{3,5,3},{4,6,2},{5,1,99}});
 assert(a.size()==3&&a[0].id==4&&a[1].id==2&&a[2].id==3);
 a=highestOwned({{8,4,1},{8,4,9},{7,4,9},{9,3,50}});
 assert(a.size()==3&&a[0].id==7&&a[1].id==8&&a[1].level==9&&a[2].id==9);
 std::cout<<"PASS empty/limited inventory, grade-first ordering, level ties and unique top-three owned companions\n";
}
