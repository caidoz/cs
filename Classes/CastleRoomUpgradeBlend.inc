// Softly join the authored room backdrop into the original castle aperture.
// Alpha is premultiplied throughout, including feathered edges.
static bool CastleRoomUpgradeShaderReady=false;
static bool castleRoomFeather=true;
static int castleRoomMaskImage=-1;
static cocos2d::Vec4 castleRoomMaskCrop;
static cocos2d::Vec4 castleRoomMaskSource(0,0,1,1);
void SetCastleRoomSilhouette(int image,float x,float y,float w,float h,float sx,float sy,float sw,float sh){castleRoomMaskImage=image;castleRoomMaskCrop=cocos2d::Vec4(x,y,w,h);castleRoomMaskSource=cocos2d::Vec4(sx,sy,sw,sh);}
void SetCastleRoomFeather(bool enabled){castleRoomFeather=enabled;}
static void ApplyCastleRoomUpgradeBlend(cocos2d::Sprite* target,int image){
 if((image<CASTLE_ROOM_UPGRADE_FIRST_IMG||image>CASTLE_ROOM_UPGRADE_LAST_IMG)&&
    (image<CASTLE_FINAL_ROOM_FIRST_IMG||image>CASTLE_FINAL_ROOM_LAST_IMG)&&castleRoomMaskImage<0)return;
 static cocos2d::GLProgram* program=nullptr;
 if(!program){
  const char* fragment=R"(
#ifdef GL_ES
precision mediump float;
#endif
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
uniform vec4 uCrop;
uniform float uFeather;
uniform sampler2D uSilhouette;
uniform vec4 uSilhouetteCrop;
uniform float uMaskEnabled;
void main(){
 vec2 local=(v_texCoord-uCrop.xy)/uCrop.zw;
 vec2 edge=min(local,1.0-local);
 float coverage=smoothstep(0.0,.045,edge.x)*smoothstep(0.0,.06,edge.y);
 float mask=texture2D(uSilhouette,uSilhouetteCrop.xy+local*uSilhouetteCrop.zw).a;
 float keep=mix(1.0,step(.95,mask),uMaskEnabled);
 gl_FragColor=texture2D(CC_Texture0,v_texCoord)*v_fragmentColor*mix(1.0,coverage,uFeather)*keep;
})";
  program=cocos2d::GLProgram::createWithByteArrays(cocos2d::ccPositionTextureColor_noMVP_vert,fragment);
  if(!program)return;
  program->retain();
 }
 const auto& rect=target->getTextureRect();const auto* texture=target->getTexture();
 auto* state=cocos2d::GLProgramState::create(program);
 state->setUniformVec4("uCrop",cocos2d::Vec4(rect.origin.x/texture->getPixelsWide(),rect.origin.y/texture->getPixelsHigh(),rect.size.width/texture->getPixelsWide(),rect.size.height/texture->getPixelsHigh()));
 state->setUniformFloat("uFeather",castleRoomFeather?1.0f:0.0f);
 const bool masked=castleRoomMaskImage>=0&&sprite[castleRoomMaskImage];
 auto* maskTexture=masked?sprite[castleRoomMaskImage]->getTexture():target->getTexture();
 state->setUniformTexture("uSilhouette",maskTexture);
 state->setUniformFloat("uMaskEnabled",masked?1.0f:0.0f);
 const float maskX=castleRoomMaskCrop.x+(rect.origin.x-castleRoomMaskSource.x)*castleRoomMaskCrop.z/castleRoomMaskSource.z;
 const float maskY=castleRoomMaskCrop.y+(rect.origin.y-castleRoomMaskSource.y)*castleRoomMaskCrop.w/castleRoomMaskSource.w;
 state->setUniformVec4("uSilhouetteCrop",masked?cocos2d::Vec4(maskX/maskTexture->getPixelsWide(),maskY/maskTexture->getPixelsHigh(),rect.size.width*castleRoomMaskCrop.z/castleRoomMaskSource.z/maskTexture->getPixelsWide(),rect.size.height*castleRoomMaskCrop.w/castleRoomMaskSource.w/maskTexture->getPixelsHigh()):cocos2d::Vec4(0,0,1,1));
 target->setGLProgramState(state);target->setBlendFunc(cocos2d::BlendFunc::ALPHA_PREMULTIPLIED);
 CastleRoomUpgradeShaderReady=program->getUniform("uCrop")!=nullptr;
}
bool CastleRoomUpgradeShaderValid(){return CastleRoomUpgradeShaderReady;}
