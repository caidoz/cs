#pragma once

// Save data keeps the original icon encoding. Only texture lookup changes.
namespace ItemSeries {
constexpr int Size=256, LegacyCount=512, WeaponFirst=512, WeaponCount=72;
constexpr int GloveFirst=584, GloveCount=24, Count=608;
inline int FromIcon(int icon) {
    if(icon>=0 && icon<=448)return icon;
    if((icon&0xFF80)==0x8000){const int n=icon&0x7F;return n<WeaponCount?WeaponFirst+n:-1;}
    if(icon>=0x8100 && icon<0x8100+GloveCount)return GloveFirst+icon-0x8100;
    return -1;
}
inline int FromAtlas(int atlas,int w,int h,int x,int y) {
    if(atlas<0 || atlas>7 || w!=32 || h!=32 || x<1 || (x-1)%33)return -1;
    const int column=(x-1)/33;if(column>=8)return -1;
    if(atlas==7 && y>=398 && (y-398)%33==0){
        const int n=(y-398)/33*8+column;return n<WeaponCount?WeaponFirst+n:-1;
    }
    if(y<1 || (y-1)%33)return -1;
    const int row=(y-1)/33;if(row>=8)return -1;
    return FromIcon(atlas*64+row*8+column);
}
inline float Zoom(float legacyZoom){return legacyZoom*32.f/Size;}
}
