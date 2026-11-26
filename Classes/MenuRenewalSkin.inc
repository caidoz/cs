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
float rounded(vec2 p,vec2 halfSize,float radius){
 vec2 q=abs(p)-(halfSize-radius);
 return length(max(q,0.0))+min(max(q.x,q.y),0.0)-radius;
}
float outline(vec2 p){
 vec2 halfSize=uSize*.5-vec2(2.0,3.0);
 return rounded(p,halfSize,uRadius);
}
void main(){
 vec2 uv=v_texCoord/uExtent;
 vec2 screen=uOrigin+vec2(uv.x,-uv.y)*uSize;
 if(screen.x<uClip.x||screen.x>uClip.z||screen.y>uClip.y||screen.y<uClip.w)discard;
 vec2 p=(uv-.5)*uSize;
 float d=outline(p);
 float a=1.0-smoothstep(-.5,.5,d);
 float border=smoothstep(-1.5,-.5,d);
 vec3 body=mix(vec3(.026,.046,.064),uFill*.55,.35);
 vec3 metal=mix(vec3(.16,.22,.25),uEdge,.18);
 vec3 color=mix(body,metal,border);
 float shadow=0.0;
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
 state->setUniformFloat("uRadius",w>=DX-8&&h>200?0.f:(float)Min(5,Min(w,h)/4));
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
 // Deliberate negative space: object art owns the scene.
 (void)x;(void)top;(void)w;(void)h;(void)castle;(void)room;
}

void DrawMenuPlaque(const char* text,int x,int top,int w,int h,float size){
 SetFontColor(0xC8C4B7);
 CenterTextStrSolid(text,x+w/2,top-h/2+10,Min(size,(w-24)/Max(1.f,StringWidth(text,1.f))));
}

// Shared menu navigation: one large, left-aligned back action.
void DrawMenuBackButton(int x,int top,int command){
 DrawUiButton(x,top,84,48,u8"\u2039",command);
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
 (void)x;(void)top;(void)w;(void)h;(void)castle;
}
