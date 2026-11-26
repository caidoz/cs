#include <cassert>
#include <cstring>
#include "../../Classes/CastleMenuModel.h"
int main(){using namespace CastleMenuModel;static_assert(sizeof(Progress)==108,"raw save layout");Progress p={};p.version=2;p.owned=1023;int old[5]={};Migrate(p,0,old);assert(p.version==3&&p.owned==1);long long gold=1000000000;
for(int c=0;c<19;++c){assert(Current(p)==c);assert(!Advance(p,c,gold));for(int r=0;r<4;++r)while(RoomLevel(p,c,r)<5)assert(Upgrade(p,c,r,true,gold));while(TurretLevel(p,c)<5)assert(Upgrade(p,c,3,false,gold));if(c<18){long long poor=GoldPrice(c+1)-1;assert(!Advance(p,c,poor));assert(Advance(p,c,gold));assert(!Advance(p,c,gold));}}
assert(Current(p)==18);assert(!Advance(p,18,gold));Progress copy=p;Migrate(p,18,old);assert(!memcmp(&p,&copy,sizeof(p)));for(int c=0;c<19;++c)assert(TurretLevel(p,c)==5);return 0;}
