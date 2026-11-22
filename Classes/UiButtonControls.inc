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
void frame(int x,int top,int w,int h,int func,bool on,bool enabled,const UiButtonStyle& style){
 const int alpha=m_lgrpAlpha,color=baseColor;
 SetAlpha(ALPHA_MAX);SetColor(0);
 if(style.frame)style.frame(x,top,w,h,enabled,style.fill);
 else DrawMenuReferencePanel(x,top,w,h,on?2:0,enabled?style.fill:0x273C43,enabled?style.edge:0x82999E);
 if(func&&enabled)SetRectPoint(x,top,w,h,func);
 SetAlpha(alpha);SetColor(color);
}
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
