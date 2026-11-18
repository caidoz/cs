// Ten clean, registered castle skins. Characters and equipment stay native.
namespace MistCastle {
#include "CastleMistWheels.inc"
int image(int castle,int part){return CASTLE_MIST_FIRST_IMG+std::max(0,std::min(9,castle))*9+part;}
// Fill a destination by cropping source edges, never by changing its aspect.
void crop(int img,float sx,float sy,float sw,float sh,const Box& b,bool mirror=false,bool floor=false){
 if(!sprite[img])LoadImg(img);if(!sprite[img]||sw<=0||sh<=0||b.w<=0||b.h<=0)return;
 const float z=std::max(b.w/sw,b.h/sh),cw=b.w/z,ch=b.h/z;
 GetSpriteIndex(img);
 if(getSpriteIdx==totalRenderCnt){
  renderSprite[getSpriteIdx]=cocos2d::Sprite::createWithTexture(sprite[img]->getTexture());renderSprite[getSpriteIdx]->retain();renderSpriteIndex[getSpriteIdx]=getSpriteTexture;
  if(sameRenderSpriteCur[img]<3000)sameRenderSpriteArr[img][sameRenderSpriteCur[img]]=totalRenderCnt;
  ++sameRenderSpriteMax[img];++sameRenderSpriteCur[img];++totalRenderCnt;
 }
 auto* sp=renderSprite[getSpriteIdx];sp->setTexture(sprite[img]->getTexture());
 sp->setTextureRect(cocos2d::Rect(sx+(sw-cw)/2,sy+(floor?sh-ch:(sh-ch)/2),cw,ch));
 sp->setAnchorPoint({0,1});sp->setPosition({(float)(mirror?DX-b.x-b.w:b.x),(float)b.y});
 sp->setScale(z);sp->setRotation(0);sp->setFlippedX(mirror);sp->setFlippedY(false);
 sp->setColor(cocos2d::Color3B::WHITE);sp->setOpacity(m_lgrpAlpha*255/32);
 sp->setGLProgram(cocos2d::GLProgramCache::getInstance()->getGLProgram(cocos2d::GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));AfterSpriting(sp);
}
// The blank plaques are baked into each hull, not text labels. Exclude the
// complete plaque and its rim; the existing interior shadow remains behind it.
struct SignRect {int x,y,w,h;};
static const SignRect signs[10][5]={
 {{269,538,107,34},{503,537,106,35},{732,537,107,35},{313,762,107,34},{670,762,108,34}},
 {{276,533,98,35},{510,533,97,35},{745,533,96,35},{324,751,102,36},{679,751,101,36}},
 {{271,535,96,35},{501,535,95,35},{729,535,96,35},{326,763,97,33},{669,763,98,33}},
 {{270,544,100,28},{502,543,100,29},{736,543,97,29},{313,764,110,34},{668,764,115,34}},
 {{275,542,103,30},{503,542,102,30},{726,542,103,30},{312,753,111,31},{654,753,114,31}},
 {{282,533,101,33},{508,533,98,33},{742,533,95,33},{323,735,106,33},{666,735,104,33}},
 {{273,524,102,27},{509,524,101,27},{749,524,93,27},{311,730,112,28},{667,730,114,28}},
 {{309,529,93,30},{524,529,93,29},{737,529,91,30},{338,727,100,31},{666,727,98,31}},
 {{308,545,82,27},{521,547,76,25},{732,545,78,27},{349,754,91,31},{671,754,89,31}},
 {{272,535,100,33},{508,535,100,33},{742,535,99,33},{316,742,112,37},{664,742,122,37}}
};
// Median shadow colors sampled from the pixels immediately around each plaque.
// Matching the surrounding recess avoids replacing the sign with a brown box.
static const int roomShadow[10][5]={
 {0x171214,0x161112,0x171113,0x130F11,0x140F12},
 {0x1C1817,0x1E1918,0x1F1918,0x1C191A,0x1F1A1A},
 {0x17171B,0x161519,0x17161B,0x1F1E22,0x201E21},
 {0x15171C,0x100F10,0x111111,0x1B191B,0x1F1916},
 {0x101118,0x101119,0x0F0F16,0x15151E,0x19161C},
 {0x191819,0x191819,0x1A1919,0x1E1C1D,0x221B1A},
 {0x161516,0x161516,0x171516,0x171314,0x191414},
 {0x171516,0x191515,0x171516,0x1E1C1D,0x221D1D},
 {0x1F1C20,0x181518,0x1F1A1D,0x121214,0x151213},
 {0x251E1C,0x211B19,0x221C1A,0x1B1819,0x201B18}
};
void hullWithoutSigns(int castle,int img,const Box& b,bool mirror){
 struct Mesh {cocos2d::PolygonInfo info;std::vector<cocos2d::V3F_C4B_T2F> vertices;std::vector<unsigned short> indices;bool ready=false;};
 static Mesh meshes[10];auto& mesh=meshes[castle];
 if(!mesh.ready){
  std::vector<int> ys={0,1445};ys.push_back(520);ys.push_back(729);for(auto r:signs[castle]){ys.push_back(r.y);ys.push_back(r.y+r.h);}
  std::sort(ys.begin(),ys.end());ys.erase(std::unique(ys.begin(),ys.end()),ys.end());
  for(size_t row=1;row<ys.size();++row){
   const int top=ys[row-1],bottom=ys[row];std::vector<std::pair<int,int>> cuts;if(top<729&&bottom>520)cuts.push_back({196,902});
   for(auto r:signs[castle])if(r.y<bottom&&r.y+r.h>top)cuts.push_back({r.x,r.x+r.w});
   std::sort(cuts.begin(),cuts.end());cuts.push_back({1089,1089});int left=0;
   for(auto cut:cuts){if(cut.first>left){
    const unsigned short first=(unsigned short)mesh.vertices.size();
    for(auto p:{std::pair<int,int>{left,top},{cut.first,top},{cut.first,bottom},{left,bottom}}){
     cocos2d::V3F_C4B_T2F v;v.vertices={(float)p.first,1445.f-p.second,0};v.colors=cocos2d::Color4B::WHITE;
     v.texCoords={p.first/1089.f,p.second/1445.f};mesh.vertices.push_back(v);
    }
    for(int i:{0,1,2,0,2,3})mesh.indices.push_back(first+i);
   }left=std::max(left,cut.second);}
  }
  cocos2d::TrianglesCommand::Triangles t;t.verts=mesh.vertices.data();t.indices=mesh.indices.data();t.vertCount=(int)mesh.vertices.size();t.indexCount=(int)mesh.indices.size();
  mesh.info.setTriangles(t);mesh.info.setRect(cocos2d::Rect(0,0,1089,1445));mesh.ready=true;
 }
 GetSpriteIndex(img);
 if(getSpriteIdx==totalRenderCnt){
  renderSprite[getSpriteIdx]=cocos2d::Sprite::createWithTexture(sprite[img]->getTexture());renderSprite[getSpriteIdx]->retain();renderSpriteIndex[getSpriteIdx]=getSpriteTexture;
  if(sameRenderSpriteCur[img]<3000)sameRenderSpriteArr[img][sameRenderSpriteCur[img]]=totalRenderCnt;
  ++sameRenderSpriteMax[img];++sameRenderSpriteCur[img];++totalRenderCnt;
 }
 auto* sp=renderSprite[getSpriteIdx];sp->setTexture(sprite[img]->getTexture());sp->setPolygonInfo(mesh.info);sp->Node::setContentSize({1089,1445});
 sp->setAnchorPoint({0,0});sp->setPosition({(float)(mirror?DX-b.x:b.x),(float)(b.y-b.h)});
 const float z=OriginalCastle::zoom();
 sp->setPosition({mirror?DX-OriginalCastle::left():OriginalCastle::left(),OriginalCastle::lift()});
 sp->setScaleX((mirror?-1.f:1.f)*z);sp->setScaleY(z);sp->setRotation(0);sp->setFlippedX(false);sp->setFlippedY(false);
 sp->setColor(cocos2d::Color3B::WHITE);sp->setOpacity(m_lgrpAlpha*255/32);
 sp->setGLProgram(cocos2d::GLProgramCache::getInstance()->getGLProgram(cocos2d::GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));AfterSpriting(sp);
}
void part(int castle,int part,const Box& b,bool mirror=false){
 const int img=image(castle,part);if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 auto* tex=sprite[img]->getTexture();tex->setAliasTexParameters();const auto sz=tex->getContentSizeInPixels();
 if(part==0){hullWithoutSigns(castle,img,b,mirror);return;}
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
 //방 그림은 창 테두리(hull)보다 두 픽셀 크게 깐다. 1089 → 화면 폭으로 줄이며 반올림이 어긋나면
 //방 오른끝과 창틀 사이에 1픽셀 틈이 생겨 뒤의 하늘이 파란 선으로 비쳤다. 창틀이 위에 덮이므로
 //넘친 몫은 보이지 않는다.
 // Opaque backing lives strictly inside the chassis. Tiny alpha/rounding
 // seams expose interior shadow instead of the distant scenery.
 const int shadow=(castleMaterial(castle)&0xFCFCFC)>>2;
 for(const Box b:{OriginalCastle::box(196,520,706,480)})
  MemRect(mirror?DX-b.x-b.w:b.x,b.y,b.w,b.h,shadow);
 for(int i=0;i<5;++i){facilityLevels[i]=-1;facilityImages[i]=-1;}
 if(!closed){const auto rr=OriginalCastle::rooms();const int bleed=std::max(1,DX/640)*2;for(int i=0;i<4;++i){const auto& p=rr[i];
  Box b=OriginalCastle::box((int)p[0].x,(int)p[0].y,(int)(p[1].x-p[0].x),(int)(p[2].y-p[0].y));
  b.x-=bleed;b.w+=2*bleed;b.y+=bleed;b.h+=2*bleed;
  facility(castle,i,b,mirror);}}
 for(int room=3;room<5;++room){const auto r=signs[castle][room];const Box b=OriginalCastle::box(r.x,r.y,r.w,r.h);
  MemRect(mirror?DX-b.x-b.w:b.x,b.y,b.w,b.h,roomShadow[castle][room]);}
 part(castle,0,OriginalCastle::box(0,0,1089,1445),mirror);
 // Reuse native support pixels to turn the upper three bays into two wide bays.
 const int hullImg=image(castle,0);
 const auto support=[&](int sx,int sy,int sw,int sh,int dx,int dy,int dw,int dh){
  const Box b=OriginalCastle::box(dx,dy,dw,dh);
  crop(hullImg,sx,sy,sw,sh,b,mirror);
 };
 support(196,729,706,25,196,520,706,28);
 support(515,795,35,180,515,548,35,181);
 // Turret upgrades reinforce the tower socket and its frame, without adding
 // another upgrade category or changing roof height / castle bounds.
 const int cannonLevel=CastleVisualPartLevel(castle,3);
 if(cannonLevel>=1)support(74,380,92,24,205,332,145,18);
 if(cannonLevel>=2)support(74,380,92,24,205,285,145,18);
 if(cannonLevel>=3)support(74,380,24,46,188,282,18,69);
 if(cannonLevel>=4)support(74,380,24,46,350,282,18,69);
 if(cannonLevel>=5)support(74,380,92,24,205,238,145,18);

 if(drawWheels)wheels(castle,angle,mirror);
}
}
