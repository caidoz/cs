// Keep the castle's authored interior material behind subdued facility furnishings.
// Apply at the shared atlas renderer so lobby and upgrade previews agree.
static void ApplyCastleFacilityTone(cocos2d::Sprite* target,int image){
 if(image<MERGE_REBUILD_ROOMS_IMG||image>=MERGE_REBUILD_ROOMS_IMG+10)return;
 const auto rect=target->getTextureRect();
 auto* atlas=target->getTexture();
 const int room=std::max(0,std::min(4,(int)(rect.origin.x*5/atlas->getContentSizeInPixels().width)));
 const int baseImage=CASTLE_MIST_FIRST_IMG+(image-MERGE_REBUILD_ROOMS_IMG)*9+room+1;
 if(!sprite[baseImage])LoadImg(baseImage);
 if(!sprite[baseImage])return;
 static cocos2d::GLProgram* program=nullptr;
 if(!program){
  const char* fragment=R"(
#ifdef GL_ES
precision highp float;
#endif
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
uniform vec4 uCrop;
uniform sampler2D uRoomBase;
uniform vec2 uBaseMax;
void main(){
 vec2 local=clamp((v_texCoord-uCrop.xy)/uCrop.zw,0.0,1.0);
 vec4 base=texture2D(uRoomBase,local*uBaseMax);
 vec4 facility=texture2D(CC_Texture0,v_texCoord);
 vec3 rgb=facility.rgb/max(facility.a,.0001);
 float light=dot(rgb,vec3(.299,.587,.114));
 rgb=mix(vec3(light),rgb,.38)*.58;
 // Original walls and windows remain visible; equipment occupies the lower room.
 float furnishings=smoothstep(.35,.68,local.y);
 vec4 toned=vec4(rgb*facility.a,facility.a);
 gl_FragColor=mix(base,toned,furnishings)*v_fragmentColor;
})";
  program=cocos2d::GLProgram::createWithByteArrays(cocos2d::ccPositionTextureColor_noMVP_vert,fragment);
  if(!program)return;
  program->retain();
 }
 auto* base=sprite[baseImage]->getTexture();
 auto* state=cocos2d::GLProgramState::create(program);
 state->setUniformVec4("uCrop",cocos2d::Vec4(rect.origin.x/atlas->getPixelsWide(),rect.origin.y/atlas->getPixelsHigh(),rect.size.width/atlas->getPixelsWide(),rect.size.height/atlas->getPixelsHigh()));
 state->setUniformTexture("uRoomBase",base);
 state->setUniformVec2("uBaseMax",cocos2d::Vec2(base->getMaxS(),base->getMaxT()));
 target->setGLProgramState(state);
 target->setBlendFunc(cocos2d::BlendFunc::ALPHA_PREMULTIPLIED);
}
