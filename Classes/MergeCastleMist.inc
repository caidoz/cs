// Ten clean, registered castle skins. Characters and equipment stay native.
namespace MistCastle {
#include "CastleMistWheels.inc"
int image(int castle,int part){return CASTLE_MIST_FIRST_IMG+std::max(0,std::min(9,castle))*9+part;}
void part(int castle,int part,const Box& b,bool mirror=false){
 const int img=image(castle,part);if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 auto* tex=sprite[img]->getTexture();tex->setAliasTexParameters();const auto sz=tex->getContentSizeInPixels();
 DrawImageScale((int)sz.width,(int)sz.height,0,0,mirror?DX-b.x-b.w:b.x,b.y,mirror,0,0,0,0,b.w/sz.width,b.h/sz.height,sprite[img],img);
}
void wheels(int castle,float angle,bool mirror){
 for(int side=0;side<2;++side){const int img=image(castle,6+side);if(!sprite[img])LoadImg(img);if(!sprite[img])continue;
  sprite[img]->getTexture()->setAliasTexParameters();const auto sz=sprite[img]->getTexture()->getContentSizeInPixels();const float z=OriginalCastle::zoom();
  const auto& anchor=wheelAnchors[castle][side];
  int x=(int)(OriginalCastle::left()+OriginalCastle::nativeX((float)anchor[0])*z);if(mirror)x=DX-x;
  RotateImage((int)sz.width,(int)sz.height,0,0,x,(int)((1445-anchor[1])*z+OriginalCastle::lift()),mirror,mirror?-angle:angle,0,0,2*anchor[2]*z/sz.width,cocos2d::Vec2(.5f,.5f),sprite[img],img);
 }
}
int facilityLevels[5]={-1,-1,-1,-1,-1};
int facilityImages[5]={-1,-1,-1,-1,-1};
void facility(int castle,int room,const Box& b,bool mirror){
 const int level=castleRoomLevel(castle,room),img=MERGE_REBUILD_ROOMS_IMG+castle;
 if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 sprite[img]->getTexture()->setAliasTexParameters();
 const auto size=sprite[img]->getTexture()->getContentSizeInPixels();
 const auto f=MergeCastleTransition::RoomFrame(room,level,(int)size.width,(int)size.height);
 // Preserve furniture proportions, anchor the floor, and cover the entire hole.
 const float z=std::max(b.w/(float)f.w,b.h/(float)f.h);
 const int sw=std::max(1,std::min(f.w,(int)std::ceil(b.w/z)));
 const int sh=std::max(1,std::min(f.h,(int)std::ceil(b.h/z)));
 DrawImageScale(sw,sh,f.x+(f.w-sw)/2,f.y+f.h-sh,mirror?DX-b.x-b.w:b.x,b.y,
  mirror,0,0,0,0,b.w/(float)sw,b.h/(float)sh,sprite[img],img);
 facilityLevels[room]=level;facilityImages[room]=img;
}
void removeRoomSigns(int castle,bool mirror){
 // Reuse the same lintel's material instead of leaving blank name plaques.
 const int img=image(castle,0);if(!sprite[img])return;
 const int centres[5]={307,549,791,355,726};
 for(int room=0;room<5;++room){
  const int x=centres[room]-90,y=room<3?529:755;
  const Box b=OriginalCastle::box(x,y,180,38);
  DrawImageScale(180,8,x,y-10,mirror?DX-b.x-b.w:b.x,b.y,mirror,0,0,0,0,
   b.w/180.f,b.h/8.f,sprite[img],img);
 }
}
void hull(int castle,bool closed,float angle,bool mirror,bool drawWheels=true){
 //방 그림은 창 테두리(hull)보다 두 픽셀 크게 깐다. 1089 → 화면 폭으로 줄이며 반올림이 어긋나면
 //방 오른끝과 창틀 사이에 1픽셀 틈이 생겨 뒤의 하늘이 파란 선으로 비쳤다. 창틀이 위에 덮이므로
 //넘친 몫은 보이지 않는다.
 // Opaque backing lives strictly inside the chassis. Tiny alpha/rounding
 // seams expose interior shadow instead of the distant scenery.
 const int shadow=(castleMaterial(castle)&0xFCFCFC)>>2;
 for(const Box b:{OriginalCastle::box(96,430,912,570),OriginalCastle::box(380,369,650,61)})
  MemRect(mirror?DX-b.x-b.w:b.x,b.y,b.w,b.h,shadow);
 for(int i=0;i<5;++i){facilityLevels[i]=-1;facilityImages[i]=-1;}
 if(!closed){const auto rr=OriginalCastle::rooms();const int bleed=std::max(1,DX/640)*2;for(int i=0;i<5;++i){const auto& p=rr[i];
  Box b=OriginalCastle::box((int)p[0].x,(int)p[0].y,(int)(p[1].x-p[0].x),(int)(p[2].y-p[0].y));
  b.x-=bleed;b.w+=2*bleed;b.y+=bleed;b.h+=2*bleed;
  facility(castle,i,b,mirror);}}
 part(castle,0,OriginalCastle::box(0,0,1089,1445),mirror);
 if(!closed)removeRoomSigns(castle,mirror);
 if(drawWheels)wheels(castle,angle,mirror);
}
}
