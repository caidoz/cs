#include "AccountLevelModel.h"
// Fixed-size quiet account page, below the shared resource bar. No card art.
static void DrawAccountLevelMenu(){
 const float s=DX/640.f;const int top=DY-(int)(74*s),left=(int)(28*s),width=DX-2*left;
 const int level=AccountLevel::bounded(robin.lv);const bool maximum=level==AccountLevel::Max;
 SetColor(0);SetAlpha(32);MemRect(0,top,DX,top,0x07121B);
 auto text=[&](const char* value,int y,float zoom=.78f,int color=0xEAE3CF){SetFontColor(color);CenterTextStrSolid(value,DX/2,y,zoom*s);};
 DrawMenuReferencePanel(0,top,DX,(int)(50*s),0,0x10252D,0x40616A);
 text(u8"모험가 레벨",top-(int)(15*s),.90f);
 DrawMenuBackButton((int)(12*s),top-(int)(4*s),TOUCH_FUNC_POPUP_CLOSE);
 int y=top-(int)(82*s);char value[160];
 std::snprintf(value,sizeof(value),"Lv.%d",level+1);text(value,y,1.5f,0xF2D17C);
 text(u8"계정의 누적 모험 기록",y-(int)(51*s),.65f,0x90ACB3);
 y-=(int)(95*s);
 const long long required=maximum?1:AccountLevel::next(level)-AccountLevel::floor(level);
 const long long current=maximum?1:AccountLevel::progress(level,robin.exps);
 MemRect(left,y,width,(int)(16*s),0x20363F);
 MemRect(left+2,y-2,(int)((width-4)*(current/(double)required)),std::max(1,(int)(12*s)),0x63B9AB);
 if(maximum)std::snprintf(value,sizeof(value),u8"최고 레벨 달성");
 else std::snprintf(value,sizeof(value),"EXP %lld / %lld",current,required);
 text(value,y-(int)(29*s),.67f);
 y-=(int)(90*s);text(u8"현재 적용 중",y,.78f);
 y-=(int)(42*s);DrawMenuReferencePanel(left,y,width,(int)(94*s),0,0x0C1C24,0x34505A);
 std::snprintf(value,sizeof(value),u8"계정 레벨 보너스   최대 번개 +%d",AccountLevel::energyBonus(level));
 text(value,y-(int)(20*s),.73f);
 std::snprintf(value,sizeof(value),u8"성 기본 용량 포함   현재 최대 번개 %d",GetInitHeart());
 text(value,y-(int)(57*s),.63f,0x90ACB3);
 y-=(int)(126*s);
 if(maximum)text(u8"모든 계정 레벨 혜택을 달성했습니다",y,.70f,0xF2D17C);
 else {
  std::snprintf(value,sizeof(value),u8"다음 Lv.%d",level+2);text(value,y,.78f);
  text(u8"최대 번개 +1   ·   번개 5 회복",y-(int)(40*s),.75f,0xF2D17C);
 }
 y-=(int)(112*s);text(u8"경험치는 어떻게 얻나요?",y,.75f);
 text(u8"15번째 보스 클리어 때 경험치 획득",y-(int)(38*s),.64f,0x90ACB3);
 text(u8"패배·중도 이탈·즉시 원정에서는 획득하지 않습니다",y-(int)(70*s),.60f,0x90ACB3);
 SetFontColor(COLOR_WHITE);
}
