#pragma once
// Absolute probability per equipment reel result, in basis points (100 = 1%).
// Missing star/family pools fall back to the ordinary Lv1 result; never reroll.
namespace MergeOwnedGear {
static const int Rate[6]={500,300,160,80,40,20};
inline int starForRoll(unsigned roll){
    unsigned end=0;
    for(int star=1;star<=6;++star){end+=Rate[star-1];if(roll<end)return star;}
    return 0;
}
}
