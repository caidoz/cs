// Lightweight UI skin. One pooled quad per panel; no bitmap mockups in the UI.
#include "Data/CastleRoomUpgrades.h"
static int sReferencePanel=0;
static bool DrawRenewalPanelRaw(int x,int y,int w,int h,int fill,int edge){
 static cocos2d::GLProgram* program=nullptr;
 static std::vector<cocos2d::GLProgramState*> states;
 if(!program){
  const char* fragment=R"(
#ifdef GL_ES
precision mediump float;
varying lowp vec4 v_fragmentColor;
#else
varying vec4 v_fragmentColor;
#endif
varying vec2 v_texCoord;
uniform vec2 uExtent;
uniform vec2 uSize;
uniform vec2 uOrigin;
uniform vec4 uClip;
uniform vec3 uFill;
uniform vec3 uEdge;
uniform float uRadius;
uniform float uStyle;
float rounded(vec2 p,vec2 halfSize,float radius){
 vec2 q=abs(p)-(halfSize-radius);
 return length(max(q,0.0))+min(max(q.x,q.y),0.0)-radius;
}
float outline(vec2 p){
 vec2 halfSize=uSize*.5-vec2(2.0,3.0);
 if(uStyle>0.5 && uStyle<1.5){
  return min(rounded(p,halfSize-vec2(0.0,7.0),9.0),rounded(p,halfSize-vec2(12.0,0.0),9.0));
 }
 return rounded(p,halfSize,uRadius);
}
void main(){
 vec2 uv=v_texCoord/uExtent;
 vec2 screen=uOrigin+vec2(uv.x,-uv.y)*uSize;
 if(screen.x<uClip.x||screen.x>uClip.z||screen.y>uClip.y||screen.y<uClip.w)discard;
 vec2 p=(uv-.5)*uSize;
 float d=outline(p);
 float a=1.0-smoothstep(-.5,.5,d);
 float border=smoothstep(-2.4,-1.4,d);
 float light=.83+.24*(1.0-uv.y)+.16*sin(uv.x*3.14159);
 vec3 body=uFill*light;
 // Soft central light, dark recessed corners, and a warm two-tone rim.
 body+=vec3(.012,.035,.032)*sin(uv.x*3.14159)*sin(uv.y*3.14159);
 vec3 metal=mix(uEdge*.64,min(vec3(1.0),uEdge*1.28),1.0-uv.y);
 vec3 color=mix(body,metal,border);
 float inset=(1.0-smoothstep(.0,1.0,abs(d+4.4)))*.16;
 color+=inset*uEdge;
 float shadow=(1.0-smoothstep(-.5,2.0,outline(p-vec2(0.0,2.0))))*.65;
 gl_FragColor=vec4(color*a, a+(1.0-a)*shadow)*v_fragmentColor.a;
})";
  program=cocos2d::GLProgram::createWithByteArrays(cocos2d::ccPositionTextureColor_noMVP_vert,fragment);
  if(!program)return false;program->retain();
 }
 LoadSpriteFromTexture(MEMRECT_IMG);auto* target=renderSprite[getSpriteIdx];
 if(states.size()<=(size_t)getSpriteIdx)states.resize(getSpriteIdx+1,nullptr);
 auto*& state=states[getSpriteIdx];
 if(!state){state=cocos2d::GLProgramState::create(program);state->retain();}
 const auto rgb=[](int c){return cocos2d::Vec3(((c>>16)&255)/255.f,((c>>8)&255)/255.f,(c&255)/255.f);};
 target->setPosition(cocos2d::Vec2(x,y));target->setTextureRect(cocos2d::Rect(0,0,w,h));
 target->setColor(cocos2d::Color3B::WHITE);
 auto* texture=target->getTexture();
 state->setUniformVec2("uExtent",cocos2d::Vec2(w/(float)texture->getPixelsWide(),h/(float)texture->getPixelsHigh()));
 state->setUniformVec2("uSize",cocos2d::Vec2(w,h));
 state->setUniformVec2("uOrigin",cocos2d::Vec2(x,y));
 state->setUniformVec4("uClip",cocos2d::Vec4(clipX,clipY,clipX2,clipY2));
 state->setUniformVec3("uFill",rgb(fill));state->setUniformVec3("uEdge",rgb(edge));
 state->setUniformFloat("uStyle",(float)sReferencePanel);
 state->setUniformFloat("uRadius",w>=DX-8&&h>200?0.f:(float)Min(16,Min(w,h)/4));
 target->setGLProgramState(state);target->setBlendFunc(cocos2d::BlendFunc::ALPHA_PREMULTIPLIED);
 AfterSpriting(target);return true;
}

// Static menu surfaces share a bounded raster cache. Dynamic labels, prices,
// characters and hit regions are still drawn/registered every frame.
static bool DrawRenewalPanel(int x,int y,int w,int h,int fill,int edge){
 if(IsOffscreenTarget()||!LobbySectionOwnsPopups())return DrawRenewalPanelRaw(x,y,w,h,fill,edge);
 if(w<2||h<2||x+w<=clipX||x>=clipX2||y<=clipY2||y-h>=clipY)return true;
 struct Entry {int w=0,h=0,fill=0,edge=0,style=0,used=-1;cocos2d::RenderTexture* target=nullptr;};
 static Entry entries[64];static size_t bytes=0;
 static std::vector<cocos2d::Sprite*> images;static int imageFrame=-1,slot=0;
 Entry* found=nullptr;
 for(auto& e:entries)if(e.target&&e.w==w&&e.h==h&&e.fill==fill&&e.edge==edge&&e.style==sReferencePanel){found=&e;break;}
 const size_t needed=(size_t)w*h*4,limit=8*1024*1024;
 if(!found){
  if(needed>limit)return DrawRenewalPanelRaw(x,y,w,h,fill,edge);
  while(bytes+needed>limit){
   Entry* oldest=nullptr;for(auto& e:entries)if(e.target&&e.used!=frame&&(!oldest||e.used<oldest->used))oldest=&e;
   if(!oldest)return DrawRenewalPanelRaw(x,y,w,h,fill,edge);
   bytes-=(size_t)oldest->w*oldest->h*4;oldest->target->release();*oldest=Entry();
  }
  for(auto& e:entries)if(!e.target){found=&e;break;}
  if(!found){
   for(auto& e:entries)if(e.used!=frame&&(!found||e.used<found->used))found=&e;
   if(!found)return DrawRenewalPanelRaw(x,y,w,h,fill,edge);
   bytes-=(size_t)found->w*found->h*4;found->target->release();*found=Entry();
  }
  found->target=cocos2d::RenderTexture::create(w,h);
  if(!found->target)return DrawRenewalPanelRaw(x,y,w,h,fill,edge);
  found->target->retain();found->w=w;found->h=h;found->fill=fill;found->edge=edge;found->style=sReferencePanel;bytes+=needed;
  const int cx=clipX,cy=clipY,cx2=clipX2,cy2=clipY2,alpha=m_lgrpAlpha;
  PushRenderTarget(found->target,nullptr,true);SetSectionClip(0,h,w,h,true);SetAlpha(ALPHA_MAX);
  const bool ok=DrawRenewalPanelRaw(0,h,w,h,fill,edge);
  PopRenderTarget();clipX=cx;clipY=cy;clipX2=cx2;clipY2=cy2;SetAlpha(alpha);
  if(!ok){bytes-=needed;found->target->release();*found=Entry();return false;}
 }
 found->used=frame;
 if(imageFrame!=frame){imageFrame=frame;slot=0;}
 if(slot>=(int)images.size()){
  auto* image=cocos2d::Sprite::createWithTexture(found->target->getSprite()->getTexture());image->retain();images.push_back(image);
 }
 auto* image=images[slot++];image->setTexture(found->target->getSprite()->getTexture());image->setFlippedY(true);
 const int left=Max(x,clipX),right=Min(x+w,clipX2),top=Min(y,clipY),bottom=Max(y-h,clipY2);
 image->setTextureRect(cocos2d::Rect(left-x,bottom-(y-h),right-left,top-bottom));image->setAnchorPoint({0,1});
 image->setPosition({(float)left,(float)top});image->setOpacity(m_lgrpAlpha*255/32);AuditDrawnTexture(image->getTexture());image->visit();return true;
}

void DrawMenuReferencePanel(int x,int top,int w,int h,int kind,int fill,int edge){
 const int previous=sReferencePanel;sReferencePanel=kind;
 DrawPixelPanel(x,top,w,h,fill,edge);sReferencePanel=previous;
}

void DrawMenuBackdropCrop(cocos2d::Texture2D*,int,int,int,int,int,int,int,int);
void DrawMenuRoomBackdrop(int x,int top,int w,int h,int castle,int room){
 if(w<=0||h<=0)return;
 if(x<=0&&x+w>=DX){x=12;w=DX-24;}
 const int img=MENU_RENEWAL_ROOM_IMG;
 if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 const auto size=sprite[img]->getTexture()->getContentSizeInPixels();
 const int stripH=(int)size.height/3,strip=castle==0?2:room==0?1:0;
 const float scale=Max(w/size.width,h/(float)stripH);
 const int sw=Min((int)size.width,(int)(w/scale)),sh=Min(stripH,(int)(h/scale));
 const int sx=((int)size.width-sw)/2,sy=strip*stripH+(stripH-sh)/2;
 const int color=baseColor,alpha=m_lgrpAlpha;
 SetColor(0);
 DrawMenuBackdropCrop(sprite[img]->getTexture(),sx,sy,sw,sh,x,top,w,h);
 SetColor(color);SetAlpha(4);MemRect(x,top,w,h,0x092B30);SetAlpha(alpha);
}

void DrawMenuPlaque(const char* text,int x,int top,int w,int h,float size){
 DrawMenuReferencePanel(x,top,w,h,1,0x10383D,0xF1C47E);
 SetFontColor(0xF7CF83);
 DrawTextStrSystem("◆",x+14,top-h/2+6,.44f,LEFT,false);
 DrawTextStrSystem("◆",x+w-14,top-h/2+6,.44f,RIGHT,false);
 SetFontColor(0xFFF0C9);
 CenterTextStrSolid(text,x+w/2,top-h/2+10,Min(size,(w-56)/Max(1.f,StringWidth(text,1.f))));
}

// Shared menu navigation: one large, left-aligned back action.
void DrawMenuBackButton(int x,int top,int command){
 DrawMenuReferencePanel(x,top,84,48,0,0x17444A,0xEAC58A);
 SetFontColor(0xFFF0CD);
 CenterTextStrSolid(u8"\u2039",x+42,top-5,1.6f);
 SetRectPoint(x,top,84,48,command);
}
// Rectangular, source-cropped background quads never bleed across window chrome.
void DrawMenuBackdropCrop(cocos2d::Texture2D* texture,int sx,int sy,int sw,int sh,int x,int top,int w,int h){
 if(!texture||w<=0||h<=0||sw<=0||sh<=0)return;
 const int left=Max(x,clipX),right=Min(x+w,clipX2),upper=Min(top,clipY),lower=Max(top-h,clipY2);
 if(left>=right||upper<=lower)return;
 static std::vector<cocos2d::Sprite*> quads;static int stamp=-1,slot=0;
 if(stamp!=frame){stamp=frame;slot=0;}
 if(slot>=(int)quads.size()){auto* q=cocos2d::Sprite::createWithTexture(texture);q->retain();quads.push_back(q);}
 auto* q=quads[slot++];q->setTexture(texture);q->setFlippedY(false);
 const float zx=sw/(float)w,zy=sh/(float)h;
 q->setTextureRect(cocos2d::Rect(sx+(left-x)*zx,sy+(top-upper)*zy,(right-left)*zx,(upper-lower)*zy));
 q->setAnchorPoint({0,1});q->setPosition({(float)left,(float)upper});q->setScaleX(1/zx);q->setScaleY(1/zy);
 q->setOpacity(m_lgrpAlpha*255/32);AuditDrawnTexture(texture);q->visit();
}
void DrawCastleMenuBackdrop(int x,int top,int w,int h,int castle){
 MergeRouletteCastleMenuBackdrop(Max(0,Min(9,castle)),x,top,w,h);
}

// Every castle has its own fitting room, including the painted circular dais.
void DrawHeroCastleBackdrop(int x,int top,int w,int h,int castle){
 castle=Max(0,Min(9,castle));
 static cocos2d::Texture2D* rooms[10]={};
 if(!rooms[castle]){
  char name[128];snprintf(name,sizeof(name),"res/menu_renewal-dressing-v3-castle-%02d.png",castle+1);
  const auto path=cocos2d::FileUtils::getInstance()->fullPathForFilename(name);
  if(!path.empty())rooms[castle]=cocos2d::Director::getInstance()->getTextureCache()->addImage(path);
 }
 auto* room=rooms[castle];
 if(!room){DrawMenuRoomBackdrop(x,top,w,h,1,1);return;}
 room->setAntiAliasTexParameters();
 const auto size=room->getContentSizeInPixels();const int tw=(int)size.width,th=(int)size.height;
 const float scale=Max(w/(float)tw,h/(float)th);
 const int sw=Min(tw,(int)(w/scale)),sh=Min(th,(int)(h/scale));
 DrawMenuBackdropCrop(room,(tw-sw)/2,(th-sh)/2,sw,sh,x,top,w,h);
}
