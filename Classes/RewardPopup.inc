// Shared full-screen reward reveal. Existing cards keep their native .42 scale.
#include <functional>
#include <vector>
#include <string>
#include "RewardRevealLayout.h"
namespace RewardPopup {
struct Entry { int type=0,detail=0,grade=0,lv=1; long long count=1; };
enum { PanelFrames=12, DropFrames=38, OpenFrame=60, CardStart=78, CardStep=6, SlideFrames=12, FlipInterval=3, BackFrames=7 };
static bool opened=false;
static int age=0;
static float sourceX=0,sourceY=0;
struct CardCache {cocos2d::RenderTexture* target=nullptr; cocos2d::Sprite* image=nullptr;};
static std::vector<CardCache> cards;
inline void clearCards(){for(auto& c:cards){if(c.image)c.image->release();if(c.target)c.target->release();}cards.clear();}
static std::string title,buttonText;
static std::vector<Entry> entries;
static std::vector<bool> revealed;
static std::vector<int> starts;
static std::function<void(int,int,int,int,const char*)> drawButton;
static std::function<void()> onClose;
static int bx=0,by=0,bw=0,bh=0,pointer=-1;
static float scroll=0,downY=0,previousY=0;
static bool manualScroll=false,dragged=false,buttonDown=false;
inline bool open(){return opened;}
inline int ticks(){return age;}
inline float easeOut(float t){t=std::max(0.f,std::min(1.f,t));return 1-(1-t)*(1-t)*(1-t);}
inline int tier(const Entry& e){return e.type==ITEM_GOLD||e.type==ITEM_HEART?0:GetItemStar(e.type,e.detail,e.grade);}
inline int cardFlipEnd(int i){return starts[i]+SlideFrames+FlipInterval*BackFrames;}
inline int summaryStart(){return entries.empty()?CardStart:cardFlipEnd((int)entries.size()-1)+12;}
inline int endFrame(){return summaryStart()+26;}
inline bool ready(){return opened&&age>=endFrame();}
inline void show(const char*,const std::vector<Entry>& list,const char* button,float originX=-1,float originY=-1){
 clearCards();cards.resize(list.size());opened=true;age=0;title=u8"보상";buttonText=button?button:u8"확인";
 sourceX=originX>=0?originX:DX*.5f;sourceY=originY>=0?originY:DY*.72f;bx=by=bw=bh=0;
 entries=list;revealed.assign(entries.size(),false);starts.clear();
 int start=CardStart;
 for(const auto& e:entries){starts.push_back(start);start+=CardStep+(tier(e)>=5?10:0);}
 scroll=0;pointer=-1;manualScroll=dragged=buttonDown=false;
}
inline void closeNow(){if(!opened)return;opened=false;clearCards();entries.clear();starts.clear();pointer=-1;if(onClose)onClose();}
inline void finishReveal(){age=endFrame();for(size_t i=0;i<revealed.size();++i)revealed[i]=true;}
inline bool touch(float x,float y,int phase=0,int id=0){
 if(!opened)return false;
 const RewardReveal::Layout l(DX,DY,(int)entries.size());
 const bool onButton=x>=bx&&x<bx+bw&&y<=by&&y>by-bh;
 if(phase==0&&pointer<0){pointer=id;downY=previousY=y;dragged=false;buttonDown=onButton;}
 else if(pointer==id&&phase==1){
  if(std::abs(y-downY)>6*l.scale)dragged=true;
  if(!buttonDown&&dragged&&l.maximum>0){manualScroll=true;scroll=std::max(0.f,std::min(l.maximum,scroll+y-previousY));}
  previousY=y;
 }else if(pointer==id&&(phase==2||phase==3)){
  pointer=-1;
  if(phase==2&&!dragged&&buttonDown&&onButton){PlayMusic(M_BUTTON);if(ready())closeNow();else finishReveal();}
 }
 return true;
}
inline void shine(int x,int y,int w,int h,int star,float intensity){
 if(intensity<=0)return;
 const int color=star>=6?0xFFD279:0xD8A3FF;
 SetAlpha((int)(28*intensity));MemRectFrameThick(x-3,y+3,w+6,h+6,color,2);
 const int radius=std::max(3,(int)(7*DX/640.f));
 for(int k=0;k<4;++k){const int sx=x+(k%2?w:0),sy=y-(k/2?h:0);
  MemRect(sx-radius,sy+1,radius*2,2,color);MemRect(sx-1,sy+radius,2,radius*2,0xFFFFFF);
 }
 SetAlpha(32);
}
// Capture each revealed front once. Settled cards are one quad, not repeated
// CMF, outlined text, progress shaders and inventory scans every frame.
inline void front(int i,int x,int y,const RewardReveal::Layout& l){
 auto& c=cards[i];const auto& e=entries[i];
 const int w=(int)std::ceil(l.w+8*l.scale),h=(int)std::ceil(l.h+8*l.scale);
 if(!c.target){
  c.target=cocos2d::RenderTexture::create(w,h);
  if(c.target){
   c.target->retain();const int cx=clipX,cy=clipY,cx2=clipX2,cy2=clipY2,a=m_lgrpAlpha;
   PushRenderTarget(c.target,nullptr,true);SetSectionClip(0,h,w,h,true);SetAlpha(32);
   DrawItemCard(e.type,e.detail,e.grade,e.lv,(long)e.count,false,4*l.scale,h-4*l.scale,false,l.zoom,false,0,0,0,0);
   PopRenderTarget();clipX=cx;clipY=cy;clipX2=cx2;clipY2=cy2;SetAlpha(a);
   c.image=cocos2d::Sprite::createWithTexture(c.target->getSprite()->getTexture());c.image->retain();
   c.image->setFlippedY(true);c.image->setAnchorPoint({0,1});
  }
 }
 if(!c.image){DrawItemCard(e.type,e.detail,e.grade,e.lv,(long)e.count,false,x,y,false,l.zoom,false,0,0,0,0);return;}
 const int px=x-(int)(4*l.scale),py=y+(int)(4*l.scale);
 const int left=std::max(px,clipX),right=std::min(px+w,clipX2);
 const int top=std::min(py,clipY),bottom=std::max(py-h,clipY2);
 if(right<=left||top<=bottom)return;
 c.image->setTextureRect(cocos2d::Rect(left-px,bottom-(py-h),right-left,top-bottom));
 c.image->setFlippedY(true);c.image->setPosition({(float)left,(float)top});c.image->setOpacity(m_lgrpAlpha*255/32);
 AuditDrawnTexture(c.image->getTexture());c.image->visit();
}
inline void draw(){
 if(!opened)return;
 ++age;const RewardReveal::Layout l(DX,DY,(int)entries.size());const float s=l.scale;
 SetAlpha((int)(26*easeOut(age/12.f)));MemRect(0,DY,DX,DY,0x050C19);SetAlpha(32);
 int active=-1,visible=0;
 for(int i=0;i<(int)entries.size();++i){
  if(age>=starts[i])active=i;
  if(age>=cardFlipEnd(i)){++visible;if(!revealed[i]){revealed[i]=true;const int star=tier(entries[i]);PlayMusic(star>=5?M_POWERUP:star?M_CARDSPLIT:M_ITEM);}}
 }
 if(!manualScroll&&active>=0&&l.maximum>0){
  const float target=std::min(l.maximum,std::max(0.f,(active/l.columns+1)*(l.h+l.gap)-l.gap-l.view));
  scroll+=(target-scroll)*.22f;
 }
 scroll=std::max(0.f,std::min(l.maximum,scroll));
 // The shared reward layout remains for expedition and combat drops.
 SetSectionClip(0,(int)l.top,DX,(int)l.view,false);
 for(int i=0;i<(int)entries.size();++i){
  const int elapsed=age-starts[i];if(elapsed<0)continue;
  const auto& e=entries[i];const float slide=easeOut(elapsed/(float)SlideFrames);
  const float destX=l.left(i,(int)entries.size(),DX),destY=l.rowTop(i,scroll);
  const float x=DX*.5f-l.w*.5f+(destX-(DX*.5f-l.w*.5f))*slide;
  const float launch=246*s;
  const float y=launch+(destY-launch)*slide+std::sin(slide*3.14159265f)*24*s;
  int back=1;if(elapsed>=SlideFrames){int f=1+(elapsed-SlideFrames)/FlipInterval;back=f<=BackFrames?f:0;}
  if(y<l.bottom||y-l.h>l.top)continue;
  // No count-dependent zoom and no pop scaling: only native flip frames move.
  if(back)DrawItemCardBack(std::max(1,tier(e)),(int)x,(int)y,l.zoom,back);
  else front(i,(int)x,(int)y,l);
  if(!back&&tier(e)>=5){
   const int since=age-cardFlipEnd(i);
   const float pulse=since<24?std::sin(std::max(0,since)/24.f*3.14159265f):.12f;
   shine((int)x,(int)y,(int)l.w,(int)l.h,tier(e),pulse);
  }
 }
 UnSectionClip(false);
 // The chest is presentation only: rewards were committed by the caller.
 const int summaryAge=age-summaryStart();
 if(summaryAge<18){
  const float t=std::min(1.f,age/(float)DropFrames),q=t*t*(3-2*t);
  const float cx=sourceX+(DX*.5f-sourceX)*q;
  float base=sourceY+(134*s-sourceY)*q+std::sin(t*3.14159265f)*52*s;
  if(age>=DropFrames&&age<DropFrames+14)base+=std::sin((age-DropFrames)/14.f*3.14159265f)*7*s;
  const float size=(30+82*easeOut(t))*s;
  const int img=BOX0_IMG+BOX_PAID0-BOX_CASTLE0;if(!sprite[img])LoadImg(img);
  if(age==DropFrames)PlayMusic(M_BUTTON);
  if(age==OpenFrame)PlayMusic(M_CARDSPLIT);
  SetAlpha(summaryAge<0?32:std::max(0,32-summaryAge*32/18));
  if(sprite[img])DrawImageScale(512,512,age>=OpenFrame?512:0,0,(int)(cx-size*.5f),(int)(base+size),false,0,0,0,0,size/512.f,size/512.f,sprite[img],img);
  SetAlpha(32);
 }
 // Final summary header: reveal native ribbon art through a centered clip.
 if(summaryAge>=0){
  const float reveal=easeOut(summaryAge/22.f),rw=420*s,rh=91*s;
  const int visibleWidth=(int)(rw*reveal);
  if(visibleWidth>0){
   SetSectionClip((DX-visibleWidth)/2,(int)(DY-28*s),visibleWidth,(int)rh,false);
   DrawImageScale(510,111,512,0,(int)(DX*.5f-rw*.5f),(int)(DY-28*s),false,0,0,0,0,rw/510.f,rw/510.f,sprite[WIN_IMG],WIN_IMG);
   UnSectionClip(false);
  }
  SetAlpha((int)(32*easeOut((summaryAge-10)/10.f)));
  DrawUiTextBox(u8"\uBCF4\uC0C1",(int)(DX*.5f-150*s),(int)(DY-44*s),(int)(300*s),(int)(48*s),0xFFFFFF);
  SetAlpha(32);
  const float line=easeOut((summaryAge-8)/18.f);
  const int barWidth=(int)((DX-56*s)*line),barLeft=(DX-barWidth)/2,barY=(int)(DY-113*s),barH=std::max(2,(int)(4*s));
  for(int i=0;i<24&&barWidth>0;++i){
   const float p=1-std::abs((i+.5f)/12.f-1);const int g=(int)(136+119*p),blue=(int)(40+215*p);
   const int x=barLeft+barWidth*i/24,w=barWidth*(i+1)/24-barWidth*i/24;
   MemRect(x,barY,w,barH,(255<<16)|(g<<8)|blue);
  }
  if(barWidth>0)MemRect(barLeft,barY-1,barWidth,1,0xFFFFFF);
 }
 if(l.maximum>0){const int track=(int)l.view,thumb=std::max(24,(int)(l.view*l.view/l.content));
  SetAlpha(18);MemRect(DX-(int)(10*s),(int)l.top,3,track,0x33465B);
  MemRect(DX-(int)(10*s),(int)(l.top-scroll/l.maximum*(track-thumb)),3,thumb,0xFFE2A1);SetAlpha(32);
 }
 if(age<CardStart)return;
 char counter[48];snprintf(counter,sizeof(counter),"%d / %d",visible,(int)entries.size());
 SetFontColor(0xD3E0ED);CenterTextStrSolid(counter,DX/2,(int)(94*s),.58f*s);
 bw=(int)(240*s);bh=(int)(52*s);bx=(DX-bw)/2;by=(int)(70*s);
 const char* label=ready()?buttonText.c_str():u8"모두 보기";
 if(drawButton)drawButton(bx,by,bw,bh,label);else DrawUiButton(bx,by,bw,bh,label,-1,true,true);
}
}
