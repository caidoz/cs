// Foliage reflects at its edges; bridges repeat from pillar centre to pillar
// centre, excluding the incomplete arches at the PNG edges.
#include "StageRailCycles.h"
static cocos2d::Vec2 sFarScroll(1,0);
void SetStageFarScroll(float span,float phase){sFarScroll=cocos2d::Vec2(span,phase);}
static void ApplyStageBackgroundSeam(cocos2d::Sprite* target,int image){
 const bool authored=image>=STAGE_MIST_FIRST_IMG&&image<=STAGE_MIST_LAST_IMG;
 const int slot=authored?(image-STAGE_MIST_FIRST_IMG)%3:(image-STAGEBG_FIRST_IMG)%STAGEBG_PER_REGION;
 const bool background=image>=STAGEBG_FIRST_IMG && image<STAGEBG_FIRST_IMG+STAGEBG_PER_REGION*STAGEBG_REGION_CNT;
 const bool regional=authored||(background && slot<3);
 const bool boss=background && slot>=3;
 if(image!=HYBRID_FAR_IMG && image!=HYBRID_MID_IMG && image!=HYBRID_RAIL_IMG && !regional && !boss)return;
 static cocos2d::GLProgram* program=nullptr;
 if(!program){
  const char* fragment=R"(
#ifdef GL_ES
precision highp float;
#endif
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
// CC_Texture0 is injected by GLProgram; redeclaring it fails on desktop GLSL.
uniform float uMid;
uniform float uRail;
uniform float uMaxS;
uniform float uBoss;
uniform float uAuthored;
uniform vec2 uFarScroll;
uniform vec2 uRailCycle;
// Work in straight RGB, then restore premultiplied alpha so transparent
// foliage edges retain their original coverage without a pale fringe.
vec4 softenForeground(vec4 color,float saturation,float contrast){
 if(uAuthored>.5)return color;
 vec3 rgb=color.rgb/max(color.a,.0001);
 float luminance=dot(rgb,vec3(.299,.587,.114));
 rgb=mix(vec3(luminance),rgb,saturation);
 rgb=(rgb-vec3(.5))*contrast+vec3(.5);
 rgb=mix(rgb,vec3(.40,.48,.50),uRail>.5?.10:.25);
 return vec4(clamp(rgb,0.0,1.0)*color.a,color.a);
}
void main(){
 float x=v_texCoord.x/uMaxS;
 if(uAuthored>.5 && uRail>.5){
  float phase=x*uFarScroll.x+uFarScroll.y;
  float u=uRailCycle.x+mod(phase/uRailCycle.y,1.0)*uRailCycle.y;
  gl_FragColor=texture2D(CC_Texture0,vec2(u*uMaxS,v_texCoord.y))*v_fragmentColor;
 }else if(uAuthored>.5){
  float u=mod(x*uFarScroll.x+uFarScroll.y,2.0);
  u=u>1.0?2.0-u:u;
  gl_FragColor=texture2D(CC_Texture0,vec2(u*uMaxS,v_texCoord.y))*v_fragmentColor;
 }else if(uBoss>.5){
  gl_FragColor=softenForeground(texture2D(CC_Texture0,v_texCoord),.30,.68)*v_fragmentColor;
 }else if(uMid>.5){
  float fade=uAuthored>.5?1.0:smoothstep(0.0,.02,min(x,1.0-x));
  gl_FragColor=softenForeground(texture2D(CC_Texture0,v_texCoord),.30,.70)*v_fragmentColor*fade;
 }else if(uRail>1.5 || (uAuthored>.5 && uRail>.5)){
  gl_FragColor=softenForeground(texture2D(CC_Texture0,v_texCoord),.48,.80)*v_fragmentColor;
 }else{
  float phase=x*uFarScroll.x+uFarScroll.y;
  float u=mod(phase,.90);
  if(uAuthored>.5){u=mod(phase,2.0);u=u>1.0?2.0-u:u;}
  vec4 color=texture2D(CC_Texture0,vec2(u*uMaxS,v_texCoord.y));
  if(uAuthored<.5 && u<.10){
   vec4 tail=texture2D(CC_Texture0,vec2((u+.90)*uMaxS,v_texCoord.y));
   color=mix(tail,color,smoothstep(0.0,.10,u));
  }
  color=softenForeground(color,uRail>.5?.48:.24,uRail>.5?.80:.64);
  gl_FragColor=color*v_fragmentColor;
 }
})";
  program=cocos2d::GLProgram::createWithByteArrays(cocos2d::ccPositionTextureColor_noMVP_vert,fragment);
  if(!program)return;program->retain();
 }
 auto* state=cocos2d::GLProgramState::create(program);
 if(getenv("CS_ALL_REGION_REVIEW")){
  static bool logged=false;
  if(!logged && image==HYBRID_MID_IMG){
   logged=true;
   std::string path=std::string(getenv("CS_CASTLE_REVIEW_PATH"))+"tone-shader.txt";
   FILE* f=fopen(path.c_str(),"w");
   if(f){fprintf(f,"%s foreground shader\n",program->getUniform("uMid") && program->getUniform("uRail")?"PASS":"FAIL");fclose(f);}
  }
 }
 state->setUniformFloat("uMid",(image==HYBRID_MID_IMG || (regional && slot==1))?1.0f:0.0f);
 state->setUniformFloat("uBoss",boss?1.0f:0.0f);
 state->setUniformFloat("uAuthored",authored?1.0f:0.0f);
 state->setUniformFloat("uRail",image==HYBRID_RAIL_IMG?2.0f:((regional && slot==2)?1.0f:0.0f));
 state->setUniformFloat("uMaxS",target->getTexture()->getMaxS());
 state->setUniformVec2("uFarScroll",sFarScroll);
 const int region=authored?(image-STAGE_MIST_FIRST_IMG)/3:0;
 const auto& cycle=StageRailArt::Cycles[region];
 state->setUniformVec2("uRailCycle",cocos2d::Vec2(cycle[0]/1088.f,(cycle[1]-cycle[0])/1088.f));
 target->setGLProgramState(state);
 target->setBlendFunc(cocos2d::BlendFunc::ALPHA_PREMULTIPLIED);
}
