// Included by Func_Graphics.cpp. All button captions pass through these two APIs.
namespace UiControls {
float width(const std::string& text){
 static std::unordered_map<std::string,float> cache;
 const auto found=cache.find(text);if(found!=cache.end())return found->second;
 static cocos2d::Label* measure=nullptr;
 if(!measure){measure=cocos2d::Label::createWithTTF("", "fonts/Pretendard-Bold.otf",FONT_HEIGHT+_2X);measure->retain();}
 measure->setString(text);const float result=measure->getContentSize().width;
 if(cache.size()>2048)cache.clear();cache[text]=result;return result;
}
struct Metrics {float height=0,topToInkCenter=0;};
Metrics font(){
 static Metrics value;
 if(!value.height){
  auto* sample=cocos2d::Label::createWithTTF(u8"Ag가", "fonts/Pretendard-Bold.otf",FONT_HEIGHT+_2X);
  value.height=sample->getContentSize().height;
  float lo=value.height,hi=0;
  for(int i=0;i<3;++i)if(auto* glyph=sample->getLetter(i)){
   const auto b=glyph->getBoundingBox();lo=std::min(lo,b.getMinY());hi=std::max(hi,b.getMaxY());
  }
  value.topToInkCenter=value.height-(lo+hi)*.5f;
 }
 return value;
}
std::vector<std::string> lines(const char* text,int width,float zoom){
 std::vector<std::string> result;std::string line;
 if(!text)return result;
 for(const char* p=text;*p;){
  const int n=CharByteLen(p);
  if(*p=='\n'||*p=='@'){result.push_back(line);line.clear();++p;continue;}
  const std::string glyph(p,n);p+=n;
  if(!line.empty()&&UiControls::width(line+glyph)*zoom>width){result.push_back(line);line.clear();}
  if(line.empty()&&glyph==" ")continue;
  line+=glyph;
 }
 if(!line.empty())result.push_back(line);
 return result;
}
int blend(int a,int b,float t){
 const int r=(int)(((a>>16)&255)*(1-t)+((b>>16)&255)*t),g=(int)(((a>>8)&255)*(1-t)+((b>>8)&255)*t),c=(int)((a&255)*(1-t)+(b&255)*t);
 return (r<<16)|(g<<8)|c;
}
// 모서리를 깎은 네모. 합성 전투의 bevel 과 같은 모양이다(위·아래 corner 줄을 한 줄씩 좁혀 그린다).
void bevel(int x,int top,int w,int h,int color,int corner){
 if(w<=0||h<=0)return;
 corner=std::min(corner,std::min(w,h)/2);
 MemRect(x,top-corner,w,h-2*corner,color);
 for(int i=0;i<corner;++i){const int trim=corner-i;MemRect(x+trim,top-i,w-2*trim,1,color);MemRect(x+trim,top-h+i+1,w-2*trim,1,color);}
}
void frame(int x,int top,int w,int h,int func,bool on,bool enabled,const UiButtonStyle& style){
 const int alpha=m_lgrpAlpha,color=baseColor;
 SetAlpha(ALPHA_MAX);SetColor(0);
 if(style.frame)style.frame(x,top,w,h,enabled,style.fill);
 else DrawUiGoldFrame(x,top,w,h,enabled,on?blend(style.fill,0x000000,.3f):style.fill);   //기본 틀 = 금테(2026-11-23 통일)
 if(func&&enabled)SetRectPoint(x,top,w,h,func);
 SetAlpha(alpha);SetColor(color);
}
}
//---- 금테 단추 틀 ----
//
//합성 전투의 단추(mergeGoldFrame)와 같은 모양이다: 그림자 → 갈색 테 → 밝은 금 → 진한 금 → 안쪽 갈색 선 → 속(위가 밝고
//아래가 어두운 그라데이션) → 윗변 하이라이트. 모든 DrawUiButton 의 기본 틀이다. 다른 틀은 UiButtonStyle::frame 으로만 넘긴다.
void DrawUiGoldFrame(int x,int top,int w,int h,bool enabled,int fill){
 const int p=std::max(1,DX/640);
 const int topColor=fill,bottomColor=UiControls::blend(fill,0x050A20,.45f);
 UiControls::bevel(x,top-3*p,w,h+3*p,0x050916,12*p);
 UiControls::bevel(x,top,w,h,enabled?0x8B4808:0x4B5369,12*p);
 UiControls::bevel(x+2*p,top-2*p,w-4*p,h-4*p,enabled?0xFFE48A:0x9EA5B3,10*p);
 UiControls::bevel(x+5*p,top-5*p,w-10*p,h-10*p,enabled?0xF7B517:0x646E81,7*p);
 UiControls::bevel(x+7*p,top-7*p,w-14*p,h-14*p,0x53350D,5*p);
 const int ix=x+9*p,itop=top-9*p,iw=w-18*p,ih=h-18*p;
 if(iw>0&&ih>0){
  const int bands=8;
  UiControls::bevel(ix,itop,iw,ih,topColor,3*p);
  for(int k=0;k<bands;++k){
   const int y0=ih*k/bands,y1=ih*(k+1)/bands;if(y1<=y0)continue;
   const int trim=(k==0||k==bands-1)?3*p:0;
   MemRect(ix+trim,itop-y0,iw-2*trim,y1-y0,UiControls::blend(topColor,bottomColor,(k+.5f)/bands));
  }
 }
 MemRect(x+14*p,top-3*p,w-28*p,p,enabled?0xFFF6B8:0xC1C8D0);
}
//---- 팝업 판 ----
//
//이어 하기 창과 같은 판: 바깥 그림자, 테두리(edge), 속(fill), 윗변 밝은 선, 아랫변 안쪽 어두운 선.
//아랫변의 어두운 선은 테두리 **안쪽**에 둔다 - 전에는 테두리 위에 그려져서 아래 경계선이 안 보였다.
void DrawUiPanel(int x,int top,int w,int h,int fill,int edge){
 const int p=std::max(1,DX/320);
 MemRect(x-p,top+p,w+2*p,h+3*p,0x080E1B);
 MemRect(x,top,w,h,edge);
 MemRect(x+p,top-p,w-2*p,h-2*p,fill);
 MemRect(x+2*p,top-2*p,w-4*p,p,0x7B7C80);
 MemRect(x+p,top-h+2*p,w-2*p,p,0x151421);
}
//---- 단순 팝업(확인 / 예·아니오) ----
//
//게임의 모든 단순 팝업은 이 한 모양이다(2026-11-23 통일): 어두운 청록 판 + 금 테두리, 제목·본문·주의 세 줄, 아래에
//금테 단추 1~3개. 자리는 UiDialogRect / UiDialogButtonRect 가 정하므로 터치를 따로 받는 쪽도 같은 네모를 쓴다.
//funcs 가 null 이거나 0 이면 터치 영역을 잡지 않는다(부르는 쪽이 UiDialogButtonRect 로 직접 받는다).
void UiDialogRect(int* x,int* top,int* w,int* h){
 const float s=DX/640.f;
 if(x)*x=(int)(30*s);if(top)*top=DY/2+(int)(190*s);if(w)*w=(int)(580*s);if(h)*h=(int)(380*s);
}
void UiDialogButtonRect(int index,int count,int* x,int* top,int* w,int* h){
 const float s=DX/640.f;count=std::max(1,count);index=std::max(0,std::min(count-1,index));
 int dx,dtop,dw,dh;UiDialogRect(&dx,&dtop,&dw,&dh);
 const int pad=(int)(20*s),gap=(int)(20*s),bw=(dw-2*pad-gap*(count-1))/count;
 if(x)*x=dx+pad+index*(bw+gap);if(top)*top=DY/2-(int)(100*s);if(w)*w=bw;if(h)*h=(int)(64*s);
}
void DrawUiDialog(const char* title,const char* message,const char* note,int buttonCount,const char* const* labels,const int* funcs,const int* fills,const bool* enabled){
 const float s=DX/640.f;
 const int alpha=m_lgrpAlpha;
 SetAlpha(23);MemRect(0,DY,DX,DY,0);SetAlpha(ALPHA_MAX);
 int x,top,w,h;UiDialogRect(&x,&top,&w,&h);
 DrawUiPanel(x,top,w,h,0x163C46,0xE4C374);
 const int tx=(int)(x+20*s),tw=(int)(w-40*s);
 if(title&&title[0]){
  DrawUiTextBox(title,tx,(int)(top-16*s),tw,(int)(48*s),0xFFF0CD);
  if(message&&message[0])DrawUiTextBox(message,tx,(int)(top-84*s),tw,(int)(64*s),0xFFFFFF);
  if(note&&note[0])DrawUiTextBox(note,tx,(int)(top-158*s),tw,(int)(96*s),0xD6DBD6);
 }else{
  if(message&&message[0])DrawUiTextBox(message,tx,(int)(top-24*s),tw,(int)(64*s),0xFFF0CD);
  if(note&&note[0])DrawUiTextBox(note,tx,(int)(top-112*s),tw,(int)(112*s),0xFFFFFF);
 }
 for(int i=0;i<buttonCount;++i){
  int bx,btop,bw,bh;UiDialogButtonRect(i,buttonCount,&bx,&btop,&bw,&bh);
  UiButtonStyle style;style.fill=fills?fills[i]:0x17444A;
  DrawUiButton(bx,btop,bw,bh,labels&&labels[i]?labels[i]:"",funcs?funcs[i]:0,false,enabled?enabled[i]:true,style);
 }
 SetAlpha(alpha);
}
float UiMinimumTextZoom(){return DX/640.f;}
float UiTextLineHeight(float zoom){return (FONT_HEIGHT+6*_2X)*std::max(zoom,UiMinimumTextZoom());}
void DrawUiTextBox(const char* text,int x,int top,int w,int h,int color,float zoom){
 zoom=std::max(zoom,UiMinimumTextZoom());
 const auto lines=UiControls::lines(text,w,zoom);if(lines.empty())return;
 const float pitch=UiTextLineHeight(zoom),center=top-h*.5f;
 const float first=center+(lines.size()-1)*pitch*.5f+UiControls::font().topToInkCenter*zoom;
 const int previous=fontColor;SetFontColor(color);
 for(size_t i=0;i<lines.size();++i)CenterTextStrSolid(lines[i].c_str(),x+w/2,(int)std::round(first-i*pitch),zoom);
 SetFontColor(previous);
}
void DrawUiButton(int x,int top,int w,int h,const char* text,int func,bool on,bool enabled,const UiButtonStyle& style){
 const float zoom=std::max(UiMinimumTextZoom(),style.zoom*DX/640.f);
 const int pad=std::max(8,(int)(12*DX/640.f));
 const auto lines=UiControls::lines(text,w-2*pad,zoom);
 const int needed=std::max((int)(48*DX/640.f),(int)(lines.size()*UiTextLineHeight(zoom))+pad);
 if(h<needed){top+=(needed-h)/2;h=needed;}
 UiControls::frame(x,top,w,h,func,on,enabled,style);
 DrawUiTextBox(text,x+pad,top,w-2*pad,h,enabled?style.text:0xBDC9C9,zoom);
}
void DrawUiButtonIcon(int x,int top,int w,int h,int icon,const char* text,int func,bool on,bool enabled,const UiButtonStyle& style){
 const float s=DX/640.f,zoom=std::max(UiMinimumTextZoom(),style.zoom*s);
 const int pad=std::max(8,(int)(12*s)),size=(int)(style.iconSize*s),gap=(text&&text[0])?(int)(10*s):0;
 const int textRoom=std::max(1,w-2*pad-(style.stacked?0:size+gap));
 const auto lines=UiControls::lines(text,textRoom,zoom);
 const int captionHeight=(int)(lines.size()*UiTextLineHeight(zoom));
 const int needed=std::max((int)(48*s),captionHeight+pad+(style.stacked?size+gap:0));
 if(h<needed){top+=(needed-h)/2;h=needed;}
 UiControls::frame(x,top,w,h,func,on,enabled,style);
 if(style.stacked){
  const int groupHeight=size+gap+captionHeight,iconTop=top-(h-groupHeight)/2;
  if(style.icon)style.icon(x+(w-size)/2,iconTop,size);
  else DrawIcon(icon,x+(w-size)/2,iconTop,size/(float)ITEMICONSIZE,0x07101B,false,false,1.f);
  if(!lines.empty())DrawUiTextBox(text,x+pad,iconTop-size-gap,w-2*pad,captionHeight,enabled?style.text:0xBDC9C9,zoom);
  return;
 }
 float textWidth=0;for(const auto& line:lines)textWidth=std::max(textWidth,UiControls::width(line)*zoom);
 const int captionWidth=(int)std::ceil(textWidth);
 const int group=size+gap+captionWidth,left=x+(w-group)/2,iconTop=top-(h-size)/2;
 if(style.icon)style.icon(left,iconTop,size);
 else DrawIcon(icon,left,iconTop,size/(float)ITEMICONSIZE,0x07101B,false,false,1.f);
 if(!lines.empty())DrawUiTextBox(text,left+size+gap,top,captionWidth,h,enabled?style.text:0xBDC9C9,zoom);
}
void DrawUiButtonText(int x,int top,int w,int h,int textIdx,int func,bool on,bool enabled){
 DrawUiButton(x,top,w,h,TEXTPTR(textIdx),func,on,enabled);
}
void DrawUiButton(int x,int top,int w,int h,const char* text,int func,bool on,bool enabled){
 DrawUiButton(x,top,w,h,text,func,on,enabled,UiButtonStyle());
}
void DrawUiButtonIcon(int x,int top,int w,int h,int icon,const char* text,int func,bool on,bool enabled){
 DrawUiButtonIcon(x,top,w,h,icon,text,func,on,enabled,UiButtonStyle());
}
