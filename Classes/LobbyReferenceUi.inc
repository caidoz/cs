// Reference lobby composition. Data and actions remain the live game values.
static void DrawLobbyReferenceTitle(){
 const int top=DY-(GNBHEIGHT-GNB_INIT_HEIGHT)-LOBBY_BAR_H-18;
 const int w=Min(DX-120,(int)(DX*.49f)),x=(DX-w)/2,h=78;
 DrawMenuReferencePanel(x,top,w,h,1,0x10383D,0xEAC58A);
 char line[128];const int region=(robin.stage/STAGE_PER_CYCLE)%STAGEBG_REGION_CNT;
 snprintf(line,sizeof(line),"%s · 스테이지 %d",StageBg::RegionName(region),robin.stage+1);
 SetFontColor(0xFFF0CD);CenterTextStrSolid(line,DX/2,top-13,Min(1.0f,(w-44)/Max(1.f,StringWidth(line,1.f))));
 MemRect(x+30,top-40,w-60,1,0x877B5B);
 char raw[32],grouped[48];snprintf(raw,sizeof(raw),"%.0f",Max(0.0,StageBg::kSpeedRail*StageBg::s_totalTravelSeconds/10.0));
 int at=0,len=(int)strlen(raw);for(int n=0;n<len;++n){if(n>0&&(len-n)%3==0)grouped[at++]=',';grouped[at++]=raw[n];}grouped[at]=0;
 snprintf(line,sizeof(line),"총 이동거리 %s m",grouped);
 CenterTextStrSolid(line,DX/2,top-48,Min(.84f,(w-36)/Max(1.f,StringWidth(line,1.f))));
 SetFontColor(0xEAC58A);CenterTextStrSolid("◆",x+17,top-33,.4f);CenterTextStrSolid("◆",x+w-17,top-33,.4f);
}

static void DrawLobbyReferenceFooter(){
 const int nav=BOTTOMMENUHEIGHT,summaryW=Min(DX-72,420),summaryX=(DX-summaryW)/2;
 DrawMenuReferencePanel(summaryX,nav+170,summaryW,44,2,0x10383D,0xEAC58A);
 const int saved=baseColor;SetColor(0);
 DrawImage(106,98,16,19,summaryX+14,nav+161,false,false,false,false,false,.28f,sprite[LOBBY_NAV_ADVENTURE_IMG],LOBBY_NAV_ADVENTURE_IMG);
 char text[128];snprintf(text,sizeof(text),"전투력 %lld",GetCombatPower(&ao[PLAYER]));
 SetFontColor(0xFFF0CD);DrawTextStrSystem(text,summaryX+50,nav+157,.82f,LEFT,false);
 const int split=summaryX+summaryW/2+4;MemRect(split,nav+160,1,24,0xB49D72);
 int used=0;for(int n=0;n<TOTALINVENTORY;++n)if(robin.inven[n].type!=EMPTY&&robin.inven[n].count>0)++used;
 const int chest=BOX0_IMG+BOX_PAID0-BOX_CASTLE0;if(!sprite[chest])LoadImg(chest);
 DrawImageScale(510,512,0,0,split+12,nav+160,false,0,0,0,0,.055f,.055f,sprite[chest],chest);
 snprintf(text,sizeof(text),"창고 %d / %d",used,CastleInventoryCapacity(robin.castle));
 SetFontColor(0xFFF0CD);DrawTextStrSystem(text,split+48,nav+157,Min(.78f,(summaryX+summaryW-split-58)/Max(1.f,StringWidth(text,1.f))),LEFT,false);
 SetColor(saved);
 const int top=nav+104,left=DX*9/100,pvpW=DX*22/100,gap=16,ctaX=left+pvpW+gap,ctaW=DX-ctaX-24,h=72;
#if SHOW_PVP_TEST_BUTTON
 DrawMenuReferencePanel(left,top,pvpW,h,0,0x10383D,0xEAC58A);
 DrawImage(106,98,16,19,left+14,top-17,false,false,false,false,false,.38f,sprite[LOBBY_NAV_ADVENTURE_IMG],LOBBY_NAV_ADVENTURE_IMG);
 SetFontColor(0xFFF0CD);CenterTextStrSolid("성 격돌",left+pvpW*66/100,top-18,.83f);CenterTextStrSolid("PVP",left+pvpW*66/100,top-43,.64f);
 if(menuPressPossible())SetRectPoint(left,top,pvpW,h,TOUCH_FUNC_PVP_TEST);
#endif
 const float press=GetButtonScale(TOUCH_FUNC_GOTOBATTLE,ctaX,top,ctaW,h);
 const int dw=(int)(ctaW*press),dh=(int)(h*press);
 DrawMenuReferencePanel(ctaX+(ctaW-dw)/2,top+(dh-h)/2,dw,dh,2,0x16613C,0xF2CE8C);
 const long long admission=GetStageAdmissionHeart(robin.stage);snprintf(text,sizeof(text),"%lld 모험 시작",admission);
 const float tz=1.12f*press;const int icon=32,row=(int)StringWidth(text,tz)+icon+10,rx=ctaX+(ctaW-row)/2;
 DrawImage(128,128,0,0,rx,top-20,false,false,false,false,false,icon/128.f,sprite[LOBBY_ENERGY_IMG],LOBBY_ENERGY_IMG);
 SetFontColor(robin.heart>=admission?0xFFF0CD:COLOR_GREY);DrawTextStrSystem(text,rx+icon+10,top-23,tz,LEFT,false);
 SetRectPoint(ctaX,top,ctaW,h,TOUCH_FUNC_GOTOBATTLE);
}
