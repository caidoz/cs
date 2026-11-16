#include "../../Classes/ItemSeriesCatalog.h"
#include <cassert>
#include <cmath>
#include <iostream>
int main(){
    // Source coordinates are verified against the shipping atlas layout.
    assert(ItemSeries::FromAtlas(3,32,32,34,100)==217);
    assert(ItemSeries::FromAtlas(4,32,32,1,34)==264);
    assert(ItemSeries::FromAtlas(5,32,32,1,67)==336);
    assert(ItemSeries::FromAtlas(7,32,32,1,398)==512);
    assert(ItemSeries::FromAtlas(7,32,32,232,662)==583);
    assert(ItemSeries::FromIcon(0x8100)==584);
    assert(ItemSeries::FromIcon(0x8117)==607);
    // Animation frames, partial crops and unrelated pseudo-icons stay on their old path.
    assert(ItemSeries::FromAtlas(7,64,64,1,199)==-1);
    assert(ItemSeries::FromAtlas(7,32,32,1,34)==-1);
    assert(ItemSeries::FromAtlas(3,20,20,34,100)==-1);
    assert(ItemSeries::FromAtlas(3,32,32,35,100)==-1);
    assert(ItemSeries::FromIcon(0x807F)==-1);
    assert(ItemSeries::FromIcon(13000)==-1);
    assert(ItemSeries::FromIcon(-1)==-1);
    for(float zoom : {0.25f,0.5f,1.f,1.5f,4.f})
        assert(std::fabs(256.f*ItemSeries::Zoom(zoom)-32.f*zoom)<0.001f);
    std::cout<<"PASS atlas identities, extension boundaries, animation exclusions and logical draw sizes\n";
}
