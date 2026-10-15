#pragma once
// Coordinates are measured upward from the bottom of the game viewport.
// Keep every physical row; menu content changes the world position, not cell size.
namespace BattleMenuLayout {
inline int Rows(int rows) { return rows<4?4:rows; }
inline int Cell(int width,int unit) {
 (void)width; (void)unit; return 48;
}
inline int ScrollMax(int width,int cols,int cell,int pad) {
 // Decorative frame padding must not push a fitting grid off centre.
 if(cols*cell<=width-16) return 0;
 const int overflow=cols*cell+2*pad+16-width;
 return overflow>0?overflow:0;
}
inline int Origin(int width,int cols,int cell,int pad,int scroll) {
 const int maximum=ScrollMax(width,cols,cell,pad);
 if(!maximum) return (width-cols*cell)/2;
 scroll=scroll<0?0:scroll>maximum?maximum:scroll;
 return 8+pad-scroll;
}
inline int GridHeight(int rows,int cell) { return Rows(rows)*cell; }
inline int Ground(int baseline,int gridTop,int unit) {
 const int required=gridTop+8*unit;
 return required>baseline?required:baseline;
}
inline float Approach(float current,float target) {
 const float next=current+(target-current)*.14f;
 return next-target<.5f&&next-target>-.5f?target:next;
}
}
