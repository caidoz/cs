// Ten clean, registered castle skins. Characters and equipment stay native.
namespace MistCastle {
#include "CastleMistWheels.inc"
int image(int castle,int part){return CASTLE_MIST_FIRST_IMG+std::max(0,std::min(9,castle))*9+part;}
// Fill a destination by cropping source edges, never by changing its aspect.
void crop(int img,float sx,float sy,float sw,float sh,const Box& b,bool mirror=false,bool floor=false){
 if(!sprite[img])LoadImg(img);if(!sprite[img]||sw<=0||sh<=0||b.w<=0||b.h<=0)return;
 const float z=std::max(b.w/sw,b.h/sh),cw=b.w/z,ch=b.h/z;
 // This renderer visits sprites directly, so software section clipping must
 // crop both destination and source before submitting the quad.
 const float dx=mirror?DX-b.x-b.w:b.x,dy=(float)b.y;
 const float left=std::max(dx,(float)clipX),right=std::min(dx+b.w,(float)clipX2);
 const float top=std::min(dy,(float)clipY),bottom=std::max(dy-b.h,(float)clipY2);
 if(right<=left||top<=bottom)return;
 const float sourceX=sx+(sw-cw)*.5f+(mirror?dx+b.w-right:left-dx)/z;
 const float sourceY=sy+(floor?sh-ch:(sh-ch)*.5f)+(dy-top)/z;

 GetSpriteIndex(img);
 if(getSpriteIdx==totalRenderCnt){
  renderSprite[getSpriteIdx]=cocos2d::Sprite::createWithTexture(sprite[img]->getTexture());renderSprite[getSpriteIdx]->retain();renderSpriteIndex[getSpriteIdx]=getSpriteTexture;
  if(sameRenderSpriteCur[img]<3000)sameRenderSpriteArr[img][sameRenderSpriteCur[img]]=totalRenderCnt;
  ++sameRenderSpriteMax[img];++sameRenderSpriteCur[img];++totalRenderCnt;
 }
 auto* sp=renderSprite[getSpriteIdx];sp->setTexture(sprite[img]->getTexture());
 sp->setTextureRect(cocos2d::Rect(sourceX,sourceY,(right-left)/z,(top-bottom)/z));
 sp->setAnchorPoint({0,1});sp->setPosition({left,top});
 sp->setScale(z);sp->setRotation(0);sp->setFlippedX(mirror);sp->setFlippedY(false);
 sp->setColor(cocos2d::Color3B::WHITE);sp->setOpacity(m_lgrpAlpha*255/32);
 sp->setGLProgram(cocos2d::GLProgramCache::getInstance()->getGLProgram(cocos2d::GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));AfterSpriting(sp);
}
void part(int castle,int part,const Box& b,bool mirror=false){
 const int img=image(castle,part);if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 auto* tex=sprite[img]->getTexture();tex->setAliasTexParameters();const auto sz=tex->getContentSizeInPixels();
 crop(img,0,0,sz.width,sz.height,b,mirror);
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
 crop(img,f.x,f.y,f.w,f.h,b,mirror,true);
 facilityLevels[room]=level;facilityImages[room]=img;
}
void hull(int castle,bool closed,float angle,bool mirror,bool drawWheels=true){
 // One broad room on each of five floors, from the wheel-level crew room up.
 // Existing four saved facilities keep their effects and upgrade levels.
 for(int i=0;i<5;++i){facilityLevels[i]=-1;facilityImages[i]=-1;}
 for(int floor=0;floor<5;++floor){
  const auto& r=CastleFiveFloors::Rooms[castle][floor];
  Box b=OriginalCastle::box(r.x,r.y,r.w,r.h);
  MemRect(mirror?DX-b.x-b.w:b.x,b.y,b.w,b.h,0x211B28);
  if(closed)continue;
  const int bleed=std::max(1,DX/640)*2;
  b.x-=bleed;b.w+=2*bleed;b.y+=bleed;b.h+=2*bleed;
  if(floor==0){part(castle,5,b,mirror);facilityImages[4]=image(castle,5);facilityLevels[4]=0;}
  else facility(castle,floor-1,b,mirror);
 }
 part(castle,0,OriginalCastle::box(0,0,1089,1445),mirror);
 if(drawWheels)wheels(castle,angle,mirror);
}
}
