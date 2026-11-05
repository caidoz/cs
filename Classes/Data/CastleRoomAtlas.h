#pragma once
// Dedicated continuous cutaway modules. Castle 1 and 10 have separate base/max
// textures; castles 2..9 pack the two complete modules side by side.
// Grades 0..2 use the base furnishing, 3..5 the advanced furnishing. Every grade
// retains its saved level and receives its own material finish in the shader.
namespace CastleRoomAtlas {
struct Crop { int x,y,w,h; };
static const int Edges[2][10][11]={
 {
  {0,10000,0,0,0,0,0,0,0,0,0},
  {0,5236,10000,0,0,0,0,0,0,0,0},
  {0,3263,6687,10000,0,0,0,0,0,0,0},
  {0,2652,4972,7330,10000,0,0,0,0,0,0},
  {0,2067,3880,5802,7770,10000,0,0,0,0,0},
  {0,1698,3599,5274,6917,8466,10000,0,0,0,0},
  {0,1626,3115,4604,6068,7460,8762,10000,0,0,0},
  {0,1576,2886,4188,5514,6825,8006,9220,10000,0,0},
  {0,1170,2325,3495,4643,5813,6961,8096,9108,10000,0},
  {0,910,1851,2781,3722,4802,5783,6753,7639,8639,10000},
 },
 {
  {0,10000,0,0,0,0,0,0,0,0,0},
  {0,5149,10000,0,0,0,0,0,0,0,0},
  {0,3263,6377,10000,0,0,0,0,0,0,0},
  {0,2652,4972,7330,10000,0,0,0,0,0,0},
  {0,2067,4016,5802,7743,10000,0,0,0,0,0},
  {0,1706,3466,5149,6917,8333,10000,0,0,0,0},
  {0,1634,3131,4604,6068,7476,8762,10000,0,0,0},
  {0,1576,2805,4108,5514,6744,7934,9140,10000,0,0},
  {0,1177,2332,3502,4658,5813,6969,8096,9108,10000,0},
  {0,1021,2021,3037,3907,4987,5973,6963,7854,8944,10000},
 },
};
inline int Advanced(int level){return level>=3?1:0;}
inline float Edge(int castle,int level,int index){return Edges[Advanced(level)][castle][index]/10000.0f;}
inline Crop Panel(int castle,int level,int width,int height){
 if(castle==0 || castle==9)return {0,0,width,height};
 const int left=Advanced(level)?width/2:0;
 return {left,0,(Advanced(level)?width:width/2)-left,height};
}
inline Crop Floor(int castle,int level,int floor,int width,int height){
 const auto p=Panel(castle,level,width,height);
 const int topIndex=castle-floor;
 const int top=(int)(Edge(castle,level,topIndex)*height+.5f);
 const int bottom=(int)(Edge(castle,level,topIndex+1)*height+.5f);
 return {p.x,top,p.w,bottom-top};
}
}
