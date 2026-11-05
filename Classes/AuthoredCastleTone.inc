// Material-only treatment of the authored castle assets. Texture coordinates,
// geometry and alpha are unchanged; characters, bosses and other art are excluded.
static bool IsAuthoredCastleImage(int image){
 return (image>=CASTLE_UNARMED_FIRST_IMG&&image<=CASTLE_UNARMED_LAST_IMG)||
  (image>=CASTLE_INDIVIDUAL_V4_FIRST_IMG&&image<=CASTLE_INDIVIDUAL_V4_LAST_IMG)||
  (image>=CASTLE_RECTANGULAR_ROOM_FIRST_IMG&&image<=CASTLE_RECTANGULAR_ROOM_LAST_IMG)||
  (image>=CASTLE_UPGRADE_COSMETICS_IMG&&image<=CASTLE_UPGRADE_COSMETICS_LAST_IMG)||
  image==CANNON_UPGRADE_ATLAS_IMG||image==INVENTORY_CANNON_ATLAS_IMG||
  (image>=CASTLE_SOFT_FIRST_IMG && image<=CASTLE_SOFT_WHEELS_IMG);
}
static void ApplyAuthoredCastleTone(cocos2d::Sprite* target,int image,int sourceY,int sourceX){
 if(!IsAuthoredCastleImage(image)||getenv("CS_CASTLE_SOURCE_TONE")||grayScale||baseColor)return;
 int castle=-1;bool body=false;float interiorGrade=-1;
 if(image>=CASTLE_SOFT_FIRST_IMG && image<=CASTLE_SOFT_LAST_IMG){castle=image-CASTLE_SOFT_FIRST_IMG;body=true;}
 if(image==CASTLE_SOFT_CANNON_IMG)castle=Max(0,Min(9,(int)(sourceY*10/target->getTexture()->getContentSize().height)));
 if(image==CASTLE_SOFT_WHEELS_IMG){const auto size=target->getTexture()->getContentSize();castle=Max(0,Min(9,(sourceY>=size.height*.5f?5:0)+(int)(sourceX*5/size.width)));}
 if(image>=CASTLE_UNARMED_FIRST_IMG&&image<=CASTLE_UNARMED_LAST_IMG){castle=image-CASTLE_UNARMED_FIRST_IMG;body=true;}
 else if(image>=CASTLE_INDIVIDUAL_V4_FIRST_IMG&&image<=CASTLE_INDIVIDUAL_V4_LAST_IMG)castle=(image-CASTLE_INDIVIDUAL_V4_FIRST_IMG)/IndividualCastleV4::Stride;
 else if(image>=CASTLE_UPGRADE_COSMETICS_IMG&&image<=CASTLE_UPGRADE_COSMETICS_LAST_IMG)castle=image-CASTLE_UPGRADE_COSMETICS_IMG;
 else if(image>=CASTLE_RECTANGULAR_ROOM_FIRST_IMG&&image<=CASTLE_RECTANGULAR_ROOM_LAST_IMG){
  castle=(image-CASTLE_RECTANGULAR_ROOM_FIRST_IMG)/6;
  interiorGrade=((image-CASTLE_RECTANGULAR_ROOM_FIRST_IMG)%6)/5.0f;
 }
 else if(image==CANNON_UPGRADE_ATLAS_IMG)castle=Max(0,Min(9,sourceY/256));
 static cocos2d::GLProgram* program=nullptr;
 if(!program){
  const char* fragment=R"(
#ifdef GL_ES
precision mediump float;
#endif
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
uniform sampler2D CC_Texture0;
uniform vec4 uRegion;
uniform vec4 uLevels;
uniform float uClock;
uniform float uBody;
uniform float uInteriorGrade;
uniform float uSoft;
void main(){
 vec4 sampleColor=texture2D(CC_Texture0,v_texCoord);
 float alpha=sampleColor.a;
 vec3 original=sampleColor.rgb/max(alpha,.001);
 vec3 color=(original-.5)*.91+.5;
 float lum=dot(color,vec3(.2126,.7152,.0722));
 color=mix(vec3(lum),color,mix(.92,.84,uSoft))*vec3(1.025,1.012,.985);
 color=mix(color,vec3(.68,.60,.49),.055*uSoft);
 // Roll off hard specular highlights for a softly lit toy-like finish.
 color=mix(color,sqrt(max(color,vec3(0.0))),.055);
 vec2 local=(v_texCoord-uRegion.xy)/uRegion.zw;
 float gold=smoothstep(.08,.28,original.r-original.b)*smoothstep(.01,.12,original.g-original.b)*smoothstep(.32,.65,original.r);
 float grade=mix(uLevels.x,uLevels.y,step(.34,local.y));
 grade=mix(grade,uLevels.z,step(.80,local.y));
 color+=gold*grade*.035*uBody*vec3(1.0,.76,.20);
 // Six material finishes retain the castle's own stone/metal/crystal palette.
 if(uInteriorGrade>=0.0){
  color*=.97+.06*uInteriorGrade;
  color+=gold*uInteriorGrade*.095*vec3(1.0,.75,.2);
 }
 // Royal detailing follows the existing gold inlay; never extends the silhouette.
 float sweep=pow(max(0.0,sin(local.x*13.0-local.y*8.0-uClock*1.4)),18.0);
 color+=uLevels.w*gold*(.015+.035*sweep)*vec3(1.0,.82,.36);
 gl_FragColor=vec4(clamp(color,0.0,1.0)*alpha,alpha)*v_fragmentColor;
})";
  program=cocos2d::GLProgram::createWithByteArrays(cocos2d::ccPositionTextureColor_noMVP_vert,fragment);
  if(!program)return;program->retain();
 }
 auto* state=cocos2d::GLProgramState::create(program);
 const auto size=target->getTexture()->getContentSize();
 const bool soft=image>=CASTLE_SOFT_FIRST_IMG && image<=CASTLE_SOFT_WHEELS_IMG;
 state->setUniformFloat("uSoft",soft?1.0f:0.0f);
 cocos2d::Vec4 region(0,0,1,1),levels(0,0,0,castle==9?1.0f:0.0f);
 if(castle>=0&&castle<10){
  const auto& rig=IndividualCastleV4::Rigs[castle];
  if(body && !soft)region=cocos2d::Vec4(rig.x/size.width,rig.y/size.height,rig.w/size.width,rig.h/size.height);
  levels.x=CastleVisualPartLevel(castle,0)/5.0f;levels.y=CastleVisualPartLevel(castle,1)/5.0f;levels.z=CastleVisualPartLevel(castle,2)/5.0f;
  if(image==CASTLE_SOFT_WHEELS_IMG)levels.x=levels.y=levels.z=CastleVisualPartLevel(castle,4)/5.0f;
 }
 state->setUniformVec4("uRegion",region);state->setUniformVec4("uLevels",levels);
 state->setUniformFloat("uInteriorGrade",interiorGrade);
 state->setUniformFloat("uClock",frame/(float)FPS);state->setUniformFloat("uBody",(body||image==CASTLE_SOFT_WHEELS_IMG)?1.0f:0.0f);
 target->setGLProgramState(state);
}
