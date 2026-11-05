// Build an opaque periodic far panorama inside the shader. Its first 10% blends
// the previous tail into the new head; both ends sample the same source point.
static cocos2d::Vec2 sFarScroll(1,0);
void SetStageFarScroll(float span,float phase){sFarScroll=cocos2d::Vec2(span,std::fmod(phase,.90f));}
static void ApplyStageBackgroundSeam(cocos2d::Sprite* target,int image){
 const int slot=(image-STAGEBG_FIRST_IMG)%STAGEBG_PER_REGION;
 const bool regional=image>=STAGEBG_FIRST_IMG+STAGEBG_PER_REGION && image<STAGEBG_FIRST_IMG+STAGEBG_PER_REGION*STAGEBG_REGION_CNT && slot<3;
 if(image!=HYBRID_FAR_IMG && image!=HYBRID_MID_IMG && image!=HYBRID_RAIL_IMG && !regional)return;
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
uniform vec2 uFarScroll;
// Work in straight RGB, then restore premultiplied alpha so transparent
// foliage edges retain their original coverage without a pale fringe.
vec4 softenForeground(vec4 color,float saturation,float contrast){
 vec3 rgb=color.rgb/max(color.a,.0001);
 float luminance=dot(rgb,vec3(.299,.587,.114));
 rgb=mix(vec3(luminance),rgb,saturation);
 rgb=(rgb-vec3(.5))*contrast+vec3(.5);
 rgb=mix(rgb,vec3(.55,.61,.62),.06);
 return vec4(clamp(rgb,0.0,1.0)*color.a,color.a);
}
void main(){
 float x=v_texCoord.x/uMaxS;
 if(uMid>.5){
  float fade=smoothstep(0.0,.02,min(x,1.0-x));
  gl_FragColor=softenForeground(texture2D(CC_Texture0,v_texCoord),.65,.86)*v_fragmentColor*fade;
 }else if(uRail>1.5){
  gl_FragColor=softenForeground(texture2D(CC_Texture0,v_texCoord),.75,.90)*v_fragmentColor;
 }else{
  float u=mod(x*uFarScroll.x+uFarScroll.y,.90);
  vec4 color=texture2D(CC_Texture0,vec2(u*uMaxS,v_texCoord.y));
  if(u<.10){
   vec4 tail=texture2D(CC_Texture0,vec2((u+.90)*uMaxS,v_texCoord.y));
   color=mix(tail,color,smoothstep(0.0,.10,u));
  }
  if(uRail>.5)color=softenForeground(color,.75,.90);
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
 state->setUniformFloat("uRail",image==HYBRID_RAIL_IMG?2.0f:((regional && slot==2)?1.0f:0.0f));
 state->setUniformFloat("uMaxS",target->getTexture()->getMaxS());
 state->setUniformVec2("uFarScroll",sFarScroll);
 target->setGLProgramState(state);
 target->setBlendFunc(cocos2d::BlendFunc::ALPHA_PREMULTIPLIED);
}
