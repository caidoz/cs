// Scoped light affects only camp actors, never HUD, battle actors or castle artwork.
static bool lobbyCampLightActive=false;
static cocos2d::Vec2 lobbyCampLightPosition;
static float lobbyCampLightRadius=1,lobbyCampLightTime=0;
void SetLobbyCampLight(bool enabled,float x,float y,float radius,float time){
 lobbyCampLightActive=enabled;lobbyCampLightPosition={x,y};lobbyCampLightRadius=radius;lobbyCampLightTime=time;
}
static cocos2d::GLProgramState* CampEffectState(cocos2d::Sprite* target,cocos2d::GLProgram* program){
 if(!program)return nullptr;
 auto* state=target->getGLProgramState();
 if(!state||state->getGLProgram()!=program){state=cocos2d::GLProgramState::create(program);target->setGLProgramState(state);}
 return state;
}
static void ApplyLobbyCampLight(cocos2d::Sprite* target){
 if(!lobbyCampLightActive)return;
 static cocos2d::GLProgram* program=nullptr;
 if(!program){program=cocos2d::GLProgram::createWithByteArrays(cocos2d::ccPositionTextureColor_noMVP_vert,R"(
#ifdef GL_ES
precision mediump float;
#endif
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
uniform vec4 uUv;
uniform vec4 uBounds;
uniform vec4 uLight;
uniform float uFlicker;
void main(){
 vec4 p=texture2D(CC_Texture0,v_texCoord)*v_fragmentColor;
 vec2 uv=(v_texCoord-uUv.xy)/uUv.zw;
 if(uLight.w>0.5)uv.x=1.0-uv.x;
 vec2 world=uBounds.xy+vec2(uv.x,1.0-uv.y)*uBounds.zw;
 vec2 d=world-uLight.xy;
 float falloff=pow(max(0.0,1.0-length(d)/uLight.z),1.35);
 // Warm diffuse lift retains original palette, alpha and sprite outlines.
 float facing=.65+.35*(1.0-abs(uv.x-.5)*2.0);
 p.rgb+=vec3(1.0,.43,.09)*falloff*facing*uFlicker*(.12+.48*p.rgb);
 gl_FragColor=p;
})");if(program)program->retain();}
 auto* state=CampEffectState(target,program);if(!state)return;
 const auto rect=target->getTextureRect();auto* tex=target->getTexture();const auto b=target->getBoundingBox();
 state->setUniformVec4("uUv",{rect.origin.x/tex->getPixelsWide(),rect.origin.y/tex->getPixelsHigh(),rect.size.width/tex->getPixelsWide(),rect.size.height/tex->getPixelsHigh()});
 state->setUniformVec4("uBounds",{b.origin.x,b.origin.y,b.size.width,b.size.height});
 state->setUniformVec4("uLight",{lobbyCampLightPosition.x,lobbyCampLightPosition.y,lobbyCampLightRadius,target->isFlippedX()?1.f:0.f});
 state->setUniformFloat("uFlicker",.70f+.12f*std::sin(lobbyCampLightTime*8.3f)+.08f*std::sin(lobbyCampLightTime*15.7f));
}
void ApplyLobbyFireEffect(cocos2d::Sprite* target,float time,bool foreground){
 static cocos2d::GLProgram* program=nullptr;
 if(!program){program=cocos2d::GLProgram::createWithByteArrays(cocos2d::ccPositionTextureColor_noMVP_vert,R"(
#ifdef GL_ES
precision mediump float;
#endif
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
uniform float uTime;
uniform float uFront;
void main(){
 vec2 q=vec2((v_texCoord.x*4.0-.5)*180.0,(1.0-v_texCoord.y)*170.0-18.0);
 float t=uTime;
 if(uFront<.5){
  float halo=exp(-dot(q-vec2(0.0,30.0),q-vec2(0.0,30.0))/1900.0);
  float ground=exp(-q.x*q.x/3700.0-q.y*q.y/90.0);
  gl_FragColor=vec4(1.0,.31,.035,(halo*.19+ground*.22)*(.9+.1*sin(t*9.0)));return;
 }
 // Layered, curved tongues with a hot core give the flame depth rather than a flat card.
 float h=clamp((q.y-13.0)/52.0,0.0,1.0);
 float sway=sin(t*5.1-h*6.0)*3.0+sin(t*8.7-h*10.0)*1.8;
 float width=(1.0-h)*(13.5+sin(t*6.0-h*14.0)*2.5);
 float body=(1.0-smoothstep(width-3.0,width+2.5,abs(q.x-sway*h)))*smoothstep(10.0,19.0,q.y)*(1.0-smoothstep(59.0,72.0,q.y));
 for(int k=0;k<2;k++){
  float side=k==0?-1.0:1.0;
  float sh=38.0+6.0*sin(t*4.3+side*2.0);
  float sy=clamp((q.y-14.0)/sh,0.0,1.0);
  float sx=side*(7.0-4.0*sy)+sin(t*6.0-sy*8.0+side)*sy*4.0;
  float sw=(1.0-sy)*7.5;
  float tongue=(1.0-smoothstep(sw-2.0,sw+2.0,abs(q.x-sx)))*smoothstep(12.0,20.0,q.y)*(1.0-smoothstep(sh+8.0,sh+16.0,q.y));
  body=max(body,tongue*.85);
 }
 float core=(1.0-smoothstep(width*.18,width*.65+1.0,abs(q.x+sway*.25)))*(1.0-smoothstep(27.0,51.0,q.y));
 vec3 color=mix(vec3(1.0,.18,.015),vec3(1.0,.68,.10),.5+core*.5);
 color=mix(color,vec3(1.0,.94,.58),core*.85);
 float sparks=0.0;
 for(int i=0;i<12;i++){
  float seed=float(i)*1.731;
  float age=fract(t*(.21+fract(seed)*.13)+seed);
  vec2 p=vec2(sin(seed*7.0)*9.0+sin(t*2.0+seed)*age*19.0,22.0+age*113.0);
  float r=mix(2.2,.7,age);
  sparks+=exp(-dot(q-p,q-p)/(r*r))*(1.0-age)*smoothstep(0.0,.1,age);
 }
 gl_FragColor=vec4(color*body+vec3(1.0,.47,.09)*sparks,clamp(body+sparks,0.0,1.0));
})");if(program)program->retain();}
 auto* state=CampEffectState(target,program);if(state){state->setUniformFloat("uTime",time);state->setUniformFloat("uFront",foreground?1.f:0.f);}
}

// Scoped circular cutaway uses native sprite bounds, independent of display density.
static bool castleRevealMaskActive=false,castleRevealMaskExterior=false;
static cocos2d::Vec2 castleRevealMaskCenter;
static float castleRevealMaskRadius=0;
void SetCastleRevealMask(bool enabled,float x,float y,float radius,bool exterior){
 castleRevealMaskActive=enabled;castleRevealMaskCenter={x,y};castleRevealMaskRadius=radius;castleRevealMaskExterior=exterior;
}
static void ApplyCastleRevealMask(cocos2d::Sprite* target){
 if(!castleRevealMaskActive)return;
 static cocos2d::GLProgram* program=nullptr;
 if(!program){program=cocos2d::GLProgram::createWithByteArrays(cocos2d::ccPositionTextureColor_noMVP_vert,R"(
#ifdef GL_ES
precision mediump float;
#endif
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
uniform vec4 uUv;
uniform vec4 uBounds;
uniform vec4 uCircle;
void main(){
 vec2 uv=(v_texCoord-uUv.xy)/uUv.zw;
 vec2 world=uBounds.xy+vec2(uv.x,1.0-uv.y)*uBounds.zw;
 float mask=1.0-smoothstep(uCircle.z-1.0,uCircle.z+1.0,distance(world,uCircle.xy));
 if(uCircle.w>.5)mask=1.0-mask;
 gl_FragColor=texture2D(CC_Texture0,v_texCoord)*v_fragmentColor*mask;
})");if(program)program->retain();}
 auto* state=CampEffectState(target,program);if(!state)return;
 const auto r=target->getTextureRect();auto* t=target->getTexture();const auto b=target->getBoundingBox();
 state->setUniformVec4("uUv",{r.origin.x/t->getPixelsWide(),r.origin.y/t->getPixelsHigh(),r.size.width/t->getPixelsWide(),r.size.height/t->getPixelsHigh()});
 state->setUniformVec4("uBounds",{b.origin.x,b.origin.y,b.size.width,b.size.height});
 state->setUniformVec4("uCircle",{castleRevealMaskCenter.x,castleRevealMaskCenter.y,castleRevealMaskRadius,castleRevealMaskExterior?1.f:0.f});
}
