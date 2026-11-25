// 제목 화면 뒤의 성 행렬(2026-11-25). 성 18개를 한 줄에 3개씩(3열 × 6행) 놓은 큰 판 하나를 가로세로로 이어 붙여
// (3×3 = 9장) 대각선으로 천천히 흘린다. 바닥·밤 배경은 없고 어두운 한 색 위에 성만 지나간다. 바퀴는 흘러간 거리만큼 구른다.
namespace TitleCastleBackdrop {static int drawn=0;static float travel=0.f;}
bool MergeRouletteTitleCastlesDraw(){
 using namespace TitleCastleBackdrop;
 const float s=DX/640.f;SetAlpha(32);SetColor(0);grayScale=0;
 MemRect(0,DY,DX,DY,0x030A13);
 travel+=std::min(.1f,std::max(0.f,cocos2d::Director::getInstance()->getDeltaTime()))*14.f*s;   //초당 14px(640 기준)
 const int column=DX/3,row=(int)(column*.82f);
 const int panelW=column*3,panelH=row*6;
 const float dx=std::fmod(travel,(float)panelW),dy=std::fmod(travel*.6f,(float)panelH);   //왼쪽 아래로
 drawn=0;
 for(int py=-1;py<=1;++py)for(int px=-1;px<=1;++px){
  const int ox=-(int)dx+px*panelW,oy=-(int)dy+py*panelH;   //판의 왼쪽 위 (그림 좌표는 위가 +). 판은 왼쪽 아래로 흐른다
  if(ox>=DX||ox+panelW<=0)continue;
  for(int i=0;i<18;++i){
   const Box b={ox+(i%3)*column+(int)(8*s),DY+oy-(i/3)*row,column-(int)(16*s),row-(int)(10*s)};
   if(b.y<=0||b.y-b.h>=DY||b.x>=DX||b.x+b.w<=0)continue;
   drawPortraitCastlePreview(i,b,travel,true);++drawn;   //왼쪽으로 가니 바퀴는 반대로 돈다
  }
 }
 return true;
}
//한 프레임에 서로 다른 성 18개가 모두 보이지는 않을 수 있지만, 판 9장을 겹쳐 깔면 화면은 늘 성으로 차야 한다.
bool MergeRouletteTitleCastlesLayoutReview(){return TitleCastleBackdrop::drawn>=9;}
