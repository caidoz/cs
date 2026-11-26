#include "CastleTutorialModel.h"
#include <chrono>
int gCastleTutorialStep=-1;
int gCastleTutorialHints=0;   //로비 힌트 비트(CastleTutorial::Hint). 단계와 같은 플래그의 윗 비트에 저장한다
namespace CastleGuide {
// 다른 화면 리뷰(CS_*_REVIEW)가 도는 동안은 안내를 끈다 - 리뷰 캡처에 손가락이 끼면 안 된다.
// CS_TUTORIAL_REVIEW 가 켜져 있으면 리뷰 중에도 안내한다. 보통 플레이에서는 늘 켜져 있다.
static bool DisabledReview(){
 if(getenv("CS_TUTORIAL_REVIEW"))return false;
 static const char* keys[]={"CS_MERGE_REVIEW","CS_CASTLE_REVIEW_PATH","CS_BATTLE_MENU_REVIEW","CS_STAGE_COMBAT_REVIEW","CS_GEAR_ROLE_REVIEW","CS_MAX_WEAPON_REVIEW","CS_ALLY_LINK_REVIEW","CS_ALLIES_BALANCE_REVIEW"};
 for(const char* key:keys)if(getenv(key))return true;
 return false;
}
static int Packed(){return (gCastleTutorialStep<0?0:gCastleTutorialStep)|(gCastleTutorialHints<<8);}
static void SaveStep(int step){if(gCastleTutorialStep==step)return;gCastleTutorialStep=step;MergeTutorialStepChanged();SaveGame();}
static bool Scene(){return drawHandle==MD_LOBBY||drawHandle==MD_PLAY;}
static int Target(){return -1;}   //밝힐 자리는 전부 전투판이 네모로 준다(MergeTutorialFocus)
static void Button(const char* text,int x,int y,int w,int command){
 DrawUiButton(x,y,w,48,text,command);
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
 //한 단계 = 한 줄 = 한 조작. 20자 안(docs/기획_튜토리얼_합성.md §3).
 switch(gCastleTutorialStep){
 case CastleTutorial::Depart:title="출정";instruction="전투 시작을 누르세요";break;
 case CastleTutorial::Spin:title="룰렛";instruction="룰렛을 돌리세요. 번개 1개";break;
 case CastleTutorial::Land:title="착지";instruction="룰렛 결과가 판에 내려앉습니다";break;
 case CastleTutorial::Merge:title="합성";instruction="같은 블록은 저절로 합쳐집니다";break;
 case CastleTutorial::Attack:title="공격";instruction="공격! 판의 블록이 전부 나갑니다";break;
 case CastleTutorial::Reward:title="보상";instruction="잡았습니다. 보상을 받으세요";break;
 case CastleTutorial::Energy:title="번개";instruction="몬스터 하나에 번개 5개";break;
 case CastleTutorial::Shield:title="방어막";instruction="반격은 방어막부터, 비면 체력입니다";break;
 case CastleTutorial::Cannon:title="대포";instruction="대포는 판 없이 바로 때립니다";break;
 case CastleTutorial::Free:title="자유";instruction="이제 자유. 5·10·15번째는 보스";break;
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
//저장 값 = 단계(아래 8비트) | 힌트 비트 << 8. 옛 세이브(단계만)도 그대로 읽힌다.
void CastleTutorialLoad(int packed){
 if(packed<0){gCastleTutorialStep=-1;gCastleTutorialHints=0;return;}
 gCastleTutorialStep=CastleTutorial::Clamp(packed&0xFF);gCastleTutorialHints=(packed>>8)&0xFF;
}
int CastleTutorialPacked(){return CastleGuide::Packed();}
void CastleTutorialNewGame(){gCastleTutorialStep=CastleTutorial::Welcome;gCastleTutorialHints=0;robin.demoSeen[DEMO_TUTORIAL_END]=true;}
bool CastleTutorialLive(){return !CastleGuide::DisabledReview()&&gCastleTutorialStep>=0;}
bool CastleTutorialHintSeen(int bit){return (gCastleTutorialHints&bit)!=0;}
void CastleTutorialHintMark(int bit){if(gCastleTutorialHints&bit)return;gCastleTutorialHints|=bit;SaveGame();}
void CastleTutorialEvent(int event){
 if(CastleGuide::DisabledReview()||!CastleGuide::Scene())return;
 CastleGuide::SaveStep(CastleTutorial::Advance(gCastleTutorialStep,(CastleTutorial::Event)event));
}
//관찰 단계(번개·방어막·자유)는 2초가 지나면 스스로 넘어간다. 단계가 바뀐 시각을 여기서 잰다.
static int sObservedStep=-1;static std::chrono::steady_clock::time_point sObservedAt;
void CastleTutorialUpdate(){
 using namespace CastleTutorial;
 if(CastleGuide::DisabledReview()||!CastleGuide::Scene())return;
 if(gCastleTutorialStep<0){CastleGuide::SaveStep(robin.stage>0||robin.demoSeen[DEMO_TUTORIAL_END]?Done:Welcome);}
 if(gCastleTutorialStep==Welcome)CastleGuide::SaveStep(Depart);
 if(gCastleTutorialStep>=Done)return;
 //전투 밖(로비)에서 전투 단계에 있으면 처음으로 돌린다 - 나갔다 들어오면 새 판이다.
 if(drawHandle==MD_LOBBY&&!MergeRouletteActive()&&gCastleTutorialStep>Depart){CastleGuide::SaveStep(Depart);return;}
 if(Observing(gCastleTutorialStep)){
  int rects[2][4]={};
  if(MergeTutorialFocus(rects)==0){sObservedStep=-1;return;}   //아직 밝힐 것이 안 보이면 시계도 안 돈다
  const auto now=std::chrono::steady_clock::now();
  if(sObservedStep!=gCastleTutorialStep){sObservedStep=gCastleTutorialStep;sObservedAt=now;return;}
  if(std::chrono::duration<float>(now-sObservedAt).count()>=2.0f+1.3f)CastleTutorialEvent(Observed);   //마스크가 뜨는 1.3초 + 2초
 }else sObservedStep=-1;
}
bool CastleTutorialCommand(int command){
 using namespace CastleTutorial;
 if(command<TOUCH_FUNC_TUTORIAL_NEXT||command>TOUCH_FUNC_TUTORIAL_HELP)return false;
 if(CastleGuide::DisabledReview()||!CastleGuide::Scene())return true;
 if(command==TOUCH_FUNC_TUTORIAL_HELP){CastleGuide::SaveStep(Welcome);return true;}
 if(gCastleTutorialStep<0||gCastleTutorialStep>=Done)return true;
 if(command==TOUCH_FUNC_TUTORIAL_SKIP){MergeTutorialUnlock();CastleGuide::SaveStep(Done);}
 else if(command==TOUCH_FUNC_TUTORIAL_SKIP_STEP)CastleGuide::SaveStep(gCastleTutorialStep+1);
 else if(command==TOUCH_FUNC_TUTORIAL_NEXT)CastleTutorialEvent(Next);
 return true;
}
void CastleTutorialDraw(){
 using namespace CastleTutorial;
 if(CastleGuide::DisabledReview()||!CastleGuide::Scene())return;
 if(gCastleTutorialStep>=Done)return;
 if(gCastleTutorialStep<0||popUpCnt>0||isDemo)return;
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
 //건너뛰기는 합성(3단계)을 해 본 뒤부터. 룰렛·배치·합성은 해 보지 않고는 못 나간다.
 if(Skippable(gCastleTutorialStep))CastleGuide::Button("건너뛰기",DX-124,DY-LOBBY_BAR_H-8,112,TOUCH_FUNC_TUTORIAL_SKIP);
 SetAlpha(savedAlpha);
}
