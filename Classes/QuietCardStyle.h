#pragma once
namespace QuietCard {
inline int Rank(int rank){return rank<1?1:rank>6?6:rank;}
inline int Color(int rank){
 static const int colors[]={0x89969E,0x70B68D,0x70A9D6,0xAC88D1,0xD7AF66,0xDD8480};
 return colors[Rank(rank)-1];
}
}
