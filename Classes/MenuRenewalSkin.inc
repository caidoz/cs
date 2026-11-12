// Lightweight UI skin. One pooled quad per panel; no bitmap mockups in the UI.
#include "Data/CastleRoomUpgrades.h"
static int sReferencePanel=0;
static bool DrawRenewalPanel(int x,int y,int w,int h,int fill,int edge){
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

void DrawMenuReferencePanel(int x,int top,int w,int h,int kind,int fill,int edge){
 const int previous=sReferencePanel;sReferencePanel=kind;
 DrawPixelPanel(x,top,w,h,fill,edge);sReferencePanel=previous;
}

void DrawMenuGear(int x,int top,int size){
 static cocos2d::GLProgram* program=nullptr;
 if(!program){
  const char* fragment=R"(
#ifdef GL_ES
precision mediump float;
#endif
varying vec2 v_texCoord;
uniform vec2 uExtent;
void main(){
 vec2 p=(v_texCoord/uExtent-.5)*2.0;
 float angle=atan(p.y,p.x),r=.72+.17*step(.28,cos(angle*8.0));
 float d=max(length(p)-r,.29-length(p));
 float a=1.0-smoothstep(-.025,.025,d);
 vec3 c=vec3(.96,.90,.76)*(.91+.10*(1.0-p.y));
 gl_FragColor=vec4(c*a,a);
})";
  program=cocos2d::GLProgram::createWithByteArrays(cocos2d::ccPositionTextureColor_noMVP_vert,fragment);if(!program)return;program->retain();
 }
 LoadSpriteFromTexture(MEMRECT_IMG);auto* target=renderSprite[getSpriteIdx];
 target->setPosition(cocos2d::Vec2(x,top));target->setTextureRect(cocos2d::Rect(0,0,size,size));
 auto* state=cocos2d::GLProgramState::getOrCreateWithGLProgram(program);auto* tex=target->getTexture();
 state->setUniformVec2("uExtent",cocos2d::Vec2(size/(float)tex->getPixelsWide(),size/(float)tex->getPixelsHigh()));
 target->setGLProgramState(state);target->setBlendFunc(cocos2d::BlendFunc::ALPHA_PREMULTIPLIED);AfterSpriting(target);
}

void DrawMenuRoomBackdrop(int x,int top,int w,int h,int castle,int room){
 if(w<=0||h<=0)return;
 const int img=MENU_RENEWAL_ROOM_IMG;
 if(!sprite[img])LoadImg(img);if(!sprite[img])return;
 const auto size=sprite[img]->getTexture()->getContentSizeInPixels();
 const int stripH=(int)size.height/3,strip=castle==0?2:room==0?1:0;
 const float scale=Max(w/size.width,h/(float)stripH);
 const int sw=Min((int)size.width,(int)(w/scale)),sh=Min(stripH,(int)(h/scale));
 const int sx=((int)size.width-sw)/2,sy=strip*stripH+(stripH-sh)/2;
 const int color=baseColor,alpha=m_lgrpAlpha;
 SetColor(0);
 DrawImageScale(sw,sh,sx,sy,x,top,false,0,0,0,0,w/(float)sw,h/(float)sh,sprite[img],img);
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
