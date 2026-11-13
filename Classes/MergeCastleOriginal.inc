// Original reference pixels, clipped by native geometry. No recoloring,
// regenerated silhouettes, or independent horizontal/vertical image scaling.
namespace OriginalCastle {
using Poly=std::vector<cocos2d::Vec2>;
struct Span {float a,b;};
constexpr float W=1089.f,H=1445.f;
float zoom(){return DX/W;}
float lift(){return 40*DX/640.f+castleSceneLift();}
Box box(int x,int y,int w,int h,float drop=0){float z=zoom();return {(int)(x*z),(int)((H-y)*z+lift()-drop),(int)(w*z),(int)(h*z)};}
Poly rect(float x,float y,float w,float h){return {{x,y},{x+w,y},{x+w,y+h},{x,y+h}};}
Poly circle(float x,float y,float r){Poly p;for(int i=0;i<64;++i){float a=i*6.2831853f/64;p.push_back({x+std::cos(a)*r,y+std::sin(a)*r});}return p;}
std::vector<Poly> outline(){return {
 {{48,402},{73,378},{74,296},{98,294},{98,269},{87,248},{142,195},{141,154},{225,154},{227,128},{243,118},{244,94},{254,85},{267,91},{278,109},{279,128},{271,143},{292,149},{320,130},{357,129},{412,144},{395,179},{409,214},{370,213},{332,204},{333,239},{326,253},{320,253},{320,295},{383,295},{383,314},{405,316},{405,348},{449,348},{449,369},{989,369},{989,347},{1030,347},{1035,380},{1047,392},{1047,429},{1028,436},{76,436},{76,451},{49,451}},
 {{63,430},{1030,430},{1030,947},{1044,970},{1044,1027},{1029,1027},{1029,1105},{1041,1120},{1041,1166},{1027,1178},{1027,1335},{65,1335},{65,1178},{54,1165},{54,1118},{65,1106},{65,1027},{52,1025},{52,972},{64,958}}
 ,{{245,83},{250,83},{257,96},{261,102},{269,106},{276,113},{279,122},{276,131},{269,137},{264,143},{262,151},{235,151},{232,143},{222,138},{217,131},{216,120},{220,112},{230,106},{235,99},{239,91}}
 };}
std::vector<Poly> rooms(){return {rect(196,569,222,160),rect(441,569,215,160),rect(681,569,221,160),rect(196,795,319,180),rect(550,795,352,180)};}
std::vector<Poly> patches(){return {rect(337,244,124,133),rect(485,238,100,134),rect(608,231,125,143)};}
Poly start(){return {{294,1090},{315,1063},{516,1063},{514,1047},{539,1057},{548,1037},{558,1057},{583,1047},{577,1063},{779,1063},{800,1085},{800,1165},{778,1187},{316,1187},{294,1165}};}
Poly manage(){return {{404,1024},{424,1005},{660,1005},{680,1026},{660,1054},{424,1054},{404,1036}};}
Poly resume(){return {{411,1212},{431,1196},{665,1196},{685,1217},{665,1248},{431,1248},{411,1230}};}
Poly nav(){return {{76,1314},{101,1297},{460,1297},{483,1284},{530,1284},{531,1275},{550,1285},{574,1284},{596,1297},{984,1297},{1017,1317},{1017,1415},{993,1438},{103,1438},{76,1414}};}
std::vector<Span> spans(const std::vector<Poly>& polys,float y){
 std::vector<Span> out;
 for(const auto& p:polys){std::vector<float> xs;
  for(int i=0,j=(int)p.size()-1;i<(int)p.size();j=i++)if((p[i].y>y)!=(p[j].y>y))xs.push_back(p[i].x+(y-p[i].y)*(p[j].x-p[i].x)/(p[j].y-p[i].y));
  std::sort(xs.begin(),xs.end());for(int i=0;i+1<(int)xs.size();i+=2)out.push_back({xs[i],xs[i+1]});
 }
 std::sort(out.begin(),out.end(),[](Span a,Span b){return a.a<b.a;});std::vector<Span> merged;
 for(auto s:out){if(!merged.empty()&&s.a<=merged.back().b)merged.back().b=std::max(merged.back().b,s.b);else merged.push_back(s);}return merged;
}
struct Mesh {cocos2d::PolygonInfo info;std::vector<cocos2d::V3F_C4B_T2F> vertices;std::vector<unsigned short> indices;bool made=false;};
Mesh meshes[13];
void build(int kind){
 auto& m=meshes[kind];if(m.made)return;m.made=true;
 std::vector<Poly> yes,no;
 if(kind<=1){yes=outline();if(kind==0){no=rooms();auto p=patches();no.insert(no.end(),p.begin(),p.end());no.push_back(start());no.push_back(manage());no.push_back(resume());no.push_back(nav());no.push_back(circle(126,1303,99));no.push_back(circle(966,1301,99));}}
 else if(kind==2)yes={start()};else if(kind==3)yes={manage()};else if(kind==4)yes={resume()};else if(kind==5)yes={nav()};
 else if(kind==6)yes={circle(126,1303,99)};else if(kind==7)yes={circle(966,1301,99)};
 else if(kind==9)yes={rect(0,0,W,H)};
 else if(kind>=10)yes={kind==10?start():kind==11?manage():resume()};
 else yes={{{348,281},{406,255},{436,252},{449,259},{452,286},{437,298},{382,307},{354,300}},{{345,296},{401,296},{417,310},{414,341},{451,344},{453,370},{340,370},{340,350},{359,341},{368,323},{349,316}}};
 for(int y=0;y<(int)H;++y){auto line=spans(yes,y+.5f);
  if(kind==1){auto limits=spans(patches(),y+.5f);std::vector<Span> cut;for(auto a:line)for(auto b:limits)if(std::min(a.b,b.b)>std::max(a.a,b.a))cut.push_back({std::max(a.a,b.a),std::min(a.b,b.b)});line=cut;}
  for(auto hole:spans(no,y+.5f)){std::vector<Span> cut;for(auto a:line){if(hole.b<=a.a||hole.a>=a.b)cut.push_back(a);else{if(hole.a>a.a)cut.push_back({a.a,hole.a});if(hole.b<a.b)cut.push_back({hole.b,a.b});}}line=cut;}
  for(auto a:line){if(a.b-a.a<.01f)continue;unsigned short first=(unsigned short)m.vertices.size();
   const float xy[4][2]={{a.a,(float)y},{a.b,(float)y},{a.b,y+1.f},{a.a,y+1.f}};
   for(auto& v:xy){cocos2d::V3F_C4B_T2F vert;vert.vertices={v[0],H-v[1],0};vert.colors=cocos2d::Color4B::WHITE;
    if(kind>=10){
     const int left=kind==10?294:kind==11?403:410,top=kind==10?1035:kind==11?1003:1194;
     // Repeat the existing wood sample only inside the actual button silhouette.
     vert.texCoords={(300+v[0]-left)/W,(1252+(y-top)%28+v[1]-y)/H};
    }else vert.texCoords={v[0]/W,v[1]/H};m.vertices.push_back(vert);}
   for(int i:{0,1,2,0,2,3})m.indices.push_back(first+i);
  }
 }
 cocos2d::TrianglesCommand::Triangles t;t.verts=m.vertices.data();t.indices=m.indices.data();t.vertCount=(int)m.vertices.size();t.indexCount=(int)m.indices.size();
 m.info.setTriangles(t);m.info.setRect(cocos2d::Rect(0,0,W,H));
}
void draw(int kind,float drop=0,float angle=0,float overrideZoom=0,float originX=0,float originY=0){
 build(kind);int img=kind==1?MERGE_ORIGINAL_REPAIR_IMG:MERGE_ORIGINAL_MESH_IMG;
 if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 GetSpriteIndex(img);
 if(getSpriteIdx==totalRenderCnt){renderSprite[getSpriteIdx]=cocos2d::Sprite::createWithTexture(sprite[img]->getTexture());renderSprite[getSpriteIdx]->retain();renderSpriteIndex[getSpriteIdx]=getSpriteTexture;
  if(sameRenderSpriteCur[img]<3000)sameRenderSpriteArr[img][sameRenderSpriteCur[img]]=totalRenderCnt;
  ++sameRenderSpriteMax[img];++sameRenderSpriteCur[img];++totalRenderCnt;}
 auto* sp=renderSprite[getSpriteIdx];sp->setTexture(sprite[img]->getTexture());sp->setPolygonInfo(meshes[kind].info);sp->setContentSize({W,H});
 const float z=overrideZoom>0?overrideZoom:zoom();
 if(overrideZoom<=0&&kind!=5)originY+=lift();
 sp->setAnchorPoint({0,0});sp->setPosition({originX,originY-drop});sp->setScale(z);sp->setRotation(0);sp->setFlippedX(false);sp->setColor(cocos2d::Color3B::WHITE);sp->setOpacity((int)(m_lgrpAlpha*255/32));
 sp->setGLProgram(cocos2d::GLProgramCache::getInstance()->getGLProgram(cocos2d::GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
 if(kind==6||kind==7){float cx=kind==6?126:966,cy=kind==6?1303:1301;sp->setAnchorPoint({cx/W,(H-cy)/H});sp->setPosition({originX+cx*z,originY+(H-cy)*z-drop});sp->setRotation(angle);}
 AfterSpriting(sp);
}
void cut(int x,int y,int w,int h,int dx,int dy){int img=MERGE_ORIGINAL_REFERENCE_IMG;if(!sprite[img])LoadImg(img);float z=zoom();DrawImageScale(w,h,x,y,(int)(dx*z),(int)((H-dy)*z+lift()),false,0,0,0,0,z,z,sprite[img],img);}
void wood(int x,int y,int w,int h){for(int n=0;n<h;n+=28)cut(300,1252,w,std::min(28,h-n),x,y+n);}
void wheel(int side,float angle){
 const int img=MERGE_ORIGINAL_WHEEL_IMG;if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 const auto size=sprite[img]->getTexture()->getContentSizeInPixels();const float z=zoom();
 RotateImage((int)size.width,(int)size.height,0,0,(int)((side?966:126)*z),(int)(96*DX/640.f+99*z+castleSceneLift()),false,angle,0,0,198*z/1140.f,cocos2d::Vec2(.5f,.5f),sprite[img],img);
}
}
