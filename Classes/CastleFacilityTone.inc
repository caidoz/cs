// Four-room art already contains its own walls and a free foreground lane.
// A fixed shader keeps native previews and the live interior at the same tone.
static void ApplyCastleFacilityTone(cocos2d::Sprite* target,int image){
 if(image<MERGE_REBUILD_ROOMS_IMG||image>=MERGE_REBUILD_ROOMS_IMG+10)return;
 static cocos2d::GLProgram* program=nullptr;static bool attempted=false;
 if(!attempted){attempted=true;
  const char* fragment=R"(
#ifdef GL_ES
precision mediump float;
#endif
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
uniform float uShade;
uniform vec2 uLogicalGrid;
void main(){
 // Room sprites use a 128x64 logical pixel grid, close to the CMF artwork.
 // This keeps tiny painted texture details from reading sharper than actors.
 vec2 uv=(floor(v_texCoord*uLogicalGrid)+.5)/uLogicalGrid;
 vec4 p=texture2D(CC_Texture0,uv);
 float light=dot(p.rgb,vec3(.299,.587,.114));
 p.rgb=mix(vec3(light),p.rgb,.84)*uShade;
 gl_FragColor=p*v_fragmentColor;
})";
  program=cocos2d::GLProgram::createWithByteArrays(cocos2d::ccPositionTextureColor_noMVP_vert,fragment);
  if(program)program->retain();
 }
 if(program){
  static cocos2d::GLProgramState* states[10]={};
  static const float shade[10]={.92f,.70f,.85f,.92f,.92f,.92f,.92f,.80f,.92f,.90f};
  const int c=image-MERGE_REBUILD_ROOMS_IMG;
  if(!states[c]){
   states[c]=cocos2d::GLProgramState::create(program);states[c]->retain();states[c]->setUniformFloat("uShade",shade[c]);
   auto* texture=target->getTexture();const auto size=texture->getContentSizeInPixels();
   states[c]->setUniformVec2("uLogicalGrid",cocos2d::Vec2(texture->getPixelsWide()*512.f/size.width,texture->getPixelsHigh()*384.f/size.height));
  }
  target->setGLProgramState(states[c]);
 }
}
