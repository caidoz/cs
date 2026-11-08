#include "CastleTutorialModel.h"
#include <chrono>
int gCastleTutorialStep=-1;
namespace CastleGuide {
// Temporarily suspend guidance while the menus are being reviewed. Keep saved progress.
static bool DisabledReview(){return !getenv("CS_TUTORIAL_REVIEW");}
static void SaveStep(int step){if(gCastleTutorialStep==step)return;gCastleTutorialStep=step;SaveGame();}
static bool Scene(){return drawHandle==MD_LOBBY||drawHandle==MD_PLAY;}
static int Target(){switch(gCastleTutorialStep){
 case CastleTutorial::Depart:return TOUCH_FUNC_GOTOBATTLE;
 case CastleTutorial::Place:return TOUCH_FUNC_LOADOUT_BAND;
 case CastleTutorial::Ready:return TOUCH_FUNC_LOADOUT_GO;
 case CastleTutorial::Start:case CastleTutorial::Continue:return GridTestOfferOpen()?TOUCH_FUNC_GRIDTEST_SKIP:TOUCH_FUNC_STAGE_AUTOBATTLE;
 case CastleTutorial::Growth:return TOUCH_FUNC_LOBBY_CASTLE;
 default:return -1;}}
static void Button(const char* text,int x,int y,int w,int command){
 DrawPixelPanel(x,y,w,32,0x205363,0xD9B65E);SetFontColor(0xFFE6AC);
 CenterTextStrSolid(text,x+w/2,y-9,.58f);SetRectPoint(x,y,w,32,command);
}

// One full-screen quad; circular holes are feathered in the fragment shader.
// Avoid hundreds of rectangle sprites for the rounded mask on mobile.
static void Spotlight(const float circles[2][3],int count,float fade){
 static cocos2d::GLProgram* program=nullptr;
 if(!program){
  const char* fragment=R"(
#ifdef GL_ES
precision mediump float;
#endif
varying vec2 v_texCoord;
uniform vec2 uUvExtent;
uniform vec2 uScreen;
uniform vec3 uCircle0;
uniform vec3 uCircle1;
uniform float uCount;
uniform float uFade;
void main(){
 vec2 uv=v_texCoord/uUvExtent;
 vec2 p=vec2(uv.x,1.0-uv.y)*uScreen;
 float d=distance(p,uCircle0.xy)-uCircle0.z;
 if(uCount>1.5)d=min(d,distance(p,uCircle1.xy)-uCircle1.z);
 float shade=smoothstep(0.0,8.0,d);
 gl_FragColor=vec4(0.0,0.0,0.0,shade*.76*uFade);
})";
  program=cocos2d::GLProgram::createWithByteArrays(cocos2d::ccPositionTextureColor_noMVP_vert,fragment);
  if(!program)return;program->retain();
 }
 LoadSpriteFromTexture(MEMRECT_IMG);
 auto* target=renderSprite[getSpriteIdx];
 target->setPosition(cocos2d::Vec2(0,DY));
 target->setTextureRect(cocos2d::Rect(0,0,DX,DY));
 target->setColor(cocos2d::Color3B::WHITE);target->setOpacity(255);
 auto* state=cocos2d::GLProgramState::getOrCreateWithGLProgram(program);
 const auto* texture=target->getTexture();
 state->setUniformVec2("uUvExtent",cocos2d::Vec2((float)DX/texture->getPixelsWide(),(float)DY/texture->getPixelsHigh()));
 state->setUniformVec2("uScreen",cocos2d::Vec2(DX,DY));
 state->setUniformVec3("uCircle0",cocos2d::Vec3(circles[0][0],circles[0][1],circles[0][2]));
 state->setUniformVec3("uCircle1",cocos2d::Vec3(circles[1][0],circles[1][1],circles[1][2]));
 state->setUniformFloat("uCount",(float)count);state->setUniformFloat("uFade",fade);
 target->setGLProgramState(state);target->setBlendFunc(cocos2d::BlendFunc::ALPHA_PREMULTIPLIED);
 AfterSpriting(target);
}

static void Caption(const float circles[2][3],int count){
 const char* title="";const char* instruction="";
 switch(gCastleTutorialStep){
 case CastleTutorial::Depart:title="모험 시작";instruction="모험 시작 버튼을 눌러 출정하세요.";break;
 case CastleTutorial::Place:title="전투 준비";instruction="성의 창고에서 동료나 장비를\n전투맵의 밝은 영역에 배치하세요.";break;
 case CastleTutorial::Ready:title="배치 완료";instruction="세팅 완료 버튼을 누르세요.";break;
 case CastleTutorial::Start:title="전투 시작";instruction="전투 시작 버튼을 눌러주세요.";break;
 case CastleTutorial::Shop:title="전투 상점";instruction="상품을 밝은 영역으로 끌어\n구매하고 배치하세요.";break;
 case CastleTutorial::Continue:title="다음 웨이브";instruction="전투를 다시 시작하세요.";break;
 case CastleTutorial::Growth:title="성 성장";instruction="성 메뉴를 열어\n업그레이드를 확인하세요.";break;
 default:return;
 }
 // Twenty full-width glyphs per line at most, also respecting actual width.
 const float zoom=(DX-64)/Max(1.f,(float)StringWidth("가나다라마바사아자차카타파하가나다라마바",1.f));
 std::vector<std::string> lines;std::string line;int glyphs=0;
 for(const unsigned char* p=(const unsigned char*)instruction;*p;){
  if(*p=='\n'){lines.push_back(line);line.clear();glyphs=0;++p;continue;}
  int n=*p<0x80?1:(*p&0xE0)==0xC0?2:(*p&0xF0)==0xE0?3:4;
  const std::string next((const char*)p,n);
  if(!line.empty()&&(glyphs>=20||StringWidth((line+next).c_str(),zoom)>DX-64)){
   lines.push_back(line);line.clear();glyphs=0;
  }
  line+=next;++glyphs;p+=n;
 }
 if(!line.empty())lines.push_back(line);
 const int lineH=(int)(32*zoom)+12,height=lineH*(int)(lines.size()+1)+12;
 const int candidates[]={(int)(DY*.74f),(int)(DY*.54f),(int)(DY*.34f),DY-LOBBY_BAR_H-64};
 int top=candidates[0];float best=-1.e9f;
 for(int y:candidates){
  if(y-height<48)continue;float clearance=1.e9f;
  for(int i=0;i<count;++i)clearance=Min(clearance,fabsf(y-height*.5f-circles[i][1])-circles[i][2]-height*.5f);
  if(clearance>best){best=clearance;top=y;}
 }
 SetFontColor(0xFFE29A);DrawTextStrSystem(title,DX/2,top,zoom,CENTER,false);
 SetFontColor(COLOR_WHITE);int y=top-lineH-12;
 for(const auto& text:lines){DrawTextStrSystem(text.c_str(),DX/2,y,zoom,CENTER,false);y-=lineH;}
}

}
void CastleTutorialLoad(int step){gCastleTutorialStep=CastleTutorial::Clamp(step);}
void CastleTutorialNewGame(){gCastleTutorialStep=CastleTutorial::Welcome;robin.demoSeen[DEMO_TUTORIAL_END]=true;}
void CastleTutorialEvent(int event){
 if(CastleGuide::DisabledReview()||!CastleGuide::Scene())return;
 CastleGuide::SaveStep(CastleTutorial::Advance(gCastleTutorialStep,(CastleTutorial::Event)event));
}
void CastleTutorialUpdate(){
 using namespace CastleTutorial;
 if(CastleGuide::DisabledReview()||!CastleGuide::Scene())return;
 if(gCastleTutorialStep<0){CastleGuide::SaveStep(robin.stage>0||robin.demoSeen[DEMO_TUTORIAL_END]?Done:Welcome);}
 if(gCastleTutorialStep==Welcome)CastleGuide::SaveStep(Depart);
 if(gCastleTutorialStep==Growth&&drawHandle==MD_LOBBY&&curMenu==MENU_CASTLE&&popUpCnt>0)CastleTutorialEvent(Next);
 if(gCastleTutorialStep>=Done)return;
 if(drawHandle==MD_LOBBY&&gCastleTutorialStep>=CastleTutorial::Place&&gCastleTutorialStep<=Continue){CastleGuide::SaveStep(Depart);return;}
 if(gCastleTutorialStep==Depart&&drawHandle==MD_PLAY&&LoadoutOpen())CastleTutorialEvent(Entered);
 else if(gCastleTutorialStep==Ready&&drawHandle==MD_PLAY&&!LoadoutOpen())CastleTutorialEvent(Setup);
 else if((gCastleTutorialStep==Start||gCastleTutorialStep==Continue)&&StageRtAutoOn())CastleTutorialEvent(Started);
}
bool CastleTutorialCommand(int command){
 using namespace CastleTutorial;
 if(command<TOUCH_FUNC_TUTORIAL_NEXT||command>TOUCH_FUNC_TUTORIAL_HELP)return false;
 if(CastleGuide::DisabledReview()||!CastleGuide::Scene())return true;
 if(command==TOUCH_FUNC_TUTORIAL_HELP){CastleGuide::SaveStep(Welcome);return true;}
 if(gCastleTutorialStep<0||gCastleTutorialStep>=Done)return true;
 if(command==TOUCH_FUNC_TUTORIAL_SKIP)CastleGuide::SaveStep(Done);
 else if(command==TOUCH_FUNC_TUTORIAL_SKIP_STEP)CastleGuide::SaveStep(gCastleTutorialStep+1);
 else if(command==TOUCH_FUNC_TUTORIAL_NEXT)CastleTutorialEvent(Next);
 return true;
}
void CastleTutorialDraw(){
 using namespace CastleTutorial;
 if(CastleGuide::DisabledReview()||!CastleGuide::Scene())return;
 if(gCastleTutorialStep>=Done){
  if(drawHandle==MD_LOBBY&&popUpCnt==0&&!LoadoutOpen())CastleGuide::Button("?",DX-48,DY-LOBBY_BAR_H-8,32,TOUCH_FUNC_TUTORIAL_HELP);
  return;
 }
 if(gCastleTutorialStep<0||popUpCnt>0||isDemo)return;
 // No overlay during automatic combat: the player must be able to watch it.
 if(gCastleTutorialStep==Fight)return;
 int holes[2][4]={};int count=CastleTutorialFocus(holes);
 if(!count){
  for(int i=touchIndex-1;i>=0;--i)if(touchRect[i][4]==CastleGuide::Target()){
   for(int k=0;k<4;++k)holes[0][k]=touchRect[i][k];count=1;break;
  }
 }
 if(!count)return; // Wait for the actual target instead of showing a stale hand.
 // Give each newly visible screen time to be read before the focus appears.
 static int shownStep=-1,shownScene=-1;
 static auto appeared=std::chrono::steady_clock::now();
 const auto now=std::chrono::steady_clock::now();
 if(shownStep!=gCastleTutorialStep||shownScene!=drawHandle){shownStep=gCastleTutorialStep;shownScene=drawHandle;appeared=now;}
 const float seconds=std::chrono::duration<float>(now-appeared).count();
 if(seconds<.9f)return;
 const float fade=Min(1.f,(seconds-.9f)/.4f);
 const int savedAlpha=m_lgrpAlpha;
 float circles[2][3]={};
 for(int i=0;i<count;++i){
  const int* r=holes[i];circles[i][0]=r[0]+r[2]*.5f;circles[i][1]=r[1]-r[3]*.5f;
  circles[i][2]=sqrtf(r[2]*r[2]*.25f+r[3]*r[3]*.25f)+12;
 }
 CastleGuide::Spotlight(circles,count,fade);
 SetAlpha(32); // Keep cached per-glyph labels fully legible throughout the mask fade.
 CastleGuide::Caption(circles,count);
 const float phase=(robin.playtime%100)/100.f;
 const float t=count==2?Min(1.f,Max(0.f,(phase-.15f)/.6f)):0.f;
 const float eased=t*t*(3-2*t);
 float hx=holes[0][0]+holes[0][2]*.5f,hy=holes[0][1]-holes[0][3]*.5f;
 if(count==2){
  const float dx=holes[1][0]+holes[1][2]*.5f-hx,dy=holes[1][1]-holes[1][3]*.5f-hy;
  // Keep the entire drag route readable even while the animated hand pauses.
  // A fixed, small number of pooled sprites avoids a growing trail buffer.
  for(int i=1;i<=6;++i){
   const float along=i/7.f;
   const int alpha=Max(4,(int)((6+4*(1-fabsf(along-eased)))*fade));
   SetAlpha(alpha);
   DrawHandAtTarget((int)(hx+dx*along),(int)(hy+dy*along),0,1.8f);
  }
  hx+=dx*eased;hy+=dy*eased;
 }
 SetAlpha(32);
 DrawHandAtTarget((int)hx,(int)hy,robin.playtime/MOTIONDIV,1.8f);
 CastleGuide::Button("X",DX-44,DY-LOBBY_BAR_H-8,32,TOUCH_FUNC_TUTORIAL_SKIP);
 SetAlpha(savedAlpha);
}
