#pragma once

// Grid artwork is independent of inventory icons and actor equipment textures.
namespace GridItems {
constexpr int Count = 225;
// One logical canvas for inventory weapons and held swords, in native 32px cells.
constexpr int WeaponCellSize = 32;
inline int WeaponColumns(int type,int detail){return type==2&&detail>=10?2:1;}
inline int WeaponRows(int type,int detail){return type==2?2:detail<10?2:detail<25?3:4;}
inline int FromItem(int type, int detail) {
    if (type < 0 || type > 17 || detail < 0) return -1;
    if (type < 3) return detail < 35 ? type * 35 + detail : -1;
    return detail < 8 ? 105 + (type - 3) * 8 + detail : -1;
}
inline int Type(int id) { return id < 105 ? id / 35 : 3 + (id - 105) / 8; }
inline int Detail(int id) { return id < 105 ? id % 35 : (id - 105) % 8; }
}
