//---- 공용 보상창 ----
//
//템빨용사의 보상 화면(win.png 창 + 보라 리본 + 카드 뒤집기)을 작게 떼어 낸 것이다.
//어느 모드에서든 쓴다: show(제목, 보상 목록, 단추 글자) → 매 프레임 draw() → 터치는 touch().
//  · 창이 가운데서 커지며 뜨고(12틀), 카드가 리본에서 한 장씩 미끄러져 내려와(12틀 간격)
//    뒷면(CARDBACK 7장)을 넘기고 앞면이 선다. 앞면이 설 때 소리 한 번.
//  · 카드가 다 서면 단추가 뜬다. 단추를 누르면 닫힌다(onClose 가 있으면 부른다).
//  · 그림·카드·소리는 전부 본편의 것(WIN_IMG, DrawItemCard, M_CARDSPLIT)이라 따로 그릴 것이 없다.
//좌표는 화면 640 기준 좌표계(DX/DY, GL 방향: y 가 클수록 위)다. 이 파일을 포함하는 쪽이
//drawButton 을 넘기면 그 단추로 그린다(합성 전투는 금테 단추). 없으면 DrawUiButton.
#include <functional>
#include <vector>
#include <string>
namespace RewardPopup {
struct Entry { int type=0,detail=0,grade=0,lv=1; long long count=1; };
enum { PanelFrames=12, CardStart=14, CardStep=12, SlideFrames=10, FlipInterval=4, BackFrames=7 };
static bool opened=false;
static int age=0;
static std::string title,buttonText;
static std::vector<Entry> entries;
static std::vector<bool> revealed;
static std::function<void(int,int,int,int,const char*)> drawButton;
static std::function<void()> onClose;
static int bx=0,by=0,bw=0,bh=0;   //단추 자리(터치용)
inline bool open(){return opened;}
inline int ticks(){return age;}
inline float easeOut(float t){t=std::max(0.f,std::min(1.f,t));return 1-(1-t)*(1-t)*(1-t);}
inline int cardFlipEnd(int i){return CardStart+i*CardStep+SlideFrames+FlipInterval*BackFrames;}
inline bool ready(){return opened&&!entries.empty()&&age>=cardFlipEnd((int)entries.size()-1)+6;}
inline void show(const char* heading,const std::vector<Entry>& list,const char* button){
    opened=true;age=0;title=heading?heading:"";buttonText=button?button:u8"확인";
    entries=list;revealed.assign(entries.size(),false);
}
inline void closeNow(){if(!opened)return;opened=false;entries.clear();if(onClose)onClose();}
//단추 자리. draw 가 계산해 두고 touch 가 읽는다.
inline bool touch(float x,float y){
    if(!opened)return false;
    if(ready()&&x>=bx&&x<bx+bw&&y<=by&&y>by-bh){PlayMusic(M_BUTTON);closeNow();}
    return true;   //열려 있는 동안은 다른 터치를 삼킨다
}
inline void draw(){
    if(!opened)return;
    const float s=DX/640.f;
    ++age;
    const float pop=easeOut(age/(float)PanelFrames);
    const float zoom=.72f+.28f*pop;
    //어둡게 깔고 창을 세운다.
    SetAlpha((int)(22*pop));MemRect(0,0,DX,DY,0x000000);SetAlpha(32);
    const int cols=std::max(1,std::min(4,(int)entries.size()));
    const float cardZoom=(cols>=4?.36f:.42f)*s;
    const float cardW=240*cardZoom,cardH=332*cardZoom,gap=8*s;
    const float w=std::max(300*s,std::min(DX-24*s,cols*cardW+(cols-1)*gap+80*s))*zoom;
    const float h=(cardH+176*s)*zoom;
    const float cx=DX*.5f,cy=DY*.5f+10*s;
    const float top=cy+h/2;
    DrawImageScale(512,507,0,0,(int)(cx-w/2),(int)top,false,false,false,false,false,w/512.f,h/507.f,sprite[WIN_IMG],WIN_IMG);
    const float ribbonW=w*.78f,ribbonZoom=ribbonW/510.f,ribbonH=111*ribbonZoom;
    DrawImageScale(510,111,512,0,(int)(cx-ribbonW/2),(int)(top-h*.058f+ribbonH/2),false,false,false,false,false,ribbonZoom,ribbonZoom,sprite[WIN_IMG],WIN_IMG);
    if(pop<.6f)return;   //창이 반쯤 커진 뒤부터 글자·카드
    //리본 제목. 리본을 넘치면 줄인다.
    {
        float tz=.78f*s*zoom;const float tw=StringWidth(title.c_str(),tz),maxW=ribbonW*.7f;
        if(tw>maxW&&tw>0)tz*=maxW/tw;
        SetFontColor(0xFFFFFF);CenterTextStrSolid(title.c_str(),(int)cx,(int)(top-h*.058f+FONT_HEIGHT*tz*.5f),tz);
    }
    //카드. 리본 아래 가운데서 제 자리로 미끄러져 내려오며 뒤집힌다.
    const float rowY=top-h*.20f;
    const float startX=cx-(cols*cardW+(cols-1)*gap)/2;
    for(int i=0;i<(int)entries.size();++i){
        const int t=age-(CardStart+i*CardStep);
        if(t<0)break;
        const Entry& e=entries[i];
        const float slide=easeOut(t/(float)SlideFrames);
        const float destX=startX+i*(cardW+gap),destY=rowY;
        const float fromX=cx-cardW/2,fromY=top-h*.06f;
        const float x=fromX+(destX-fromX)*slide,y=fromY+(destY-fromY)*slide;
        const float z=cardZoom*(.55f+.45f*slide);
        int back=1;
        if(t>=SlideFrames){
            const int f=1+(t-SlideFrames)/FlipInterval;
            back=f<=BackFrames?f:0;
        }
        float popZ=1.f;
        if(back==0){
            if(!revealed[i]){revealed[i]=true;PlayMusic(e.type==ITEM_GOLD||e.type==ITEM_HEART?M_ITEM:M_CARDSPLIT);}
            const int since=t-SlideFrames-FlipInterval*BackFrames;
            popZ=1.f+.08f*std::sin(std::max(0,std::min(10,since))/10.f*3.14159265f);   //앞면이 서며 한 번 부푼다
        }
        const float dz=z*popZ,dx=x-(dz-z)*120,dy=y+(dz-z)*166;
        DrawItemCard(e.type,e.detail,e.grade,e.lv,(long)e.count,false,(int)dx,(int)dy,false,dz,false,0,0,true,back);
    }
    //단추. 카드가 다 선 뒤에.
    if(ready()){
        bw=(int)(190*s);bh=(int)(52*s);bx=(int)(cx-bw/2);by=(int)(top-h+bh+22*s);
        if(drawButton)drawButton(bx,by,bw,bh,buttonText.c_str());
        else DrawUiButton(bx,by,bw,bh,buttonText.c_str(),-1,true,true);
    }
}
}
