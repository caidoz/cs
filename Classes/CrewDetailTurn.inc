// Companion detail uses the same star, skill band and damage rules as the board.
static long long CrewDetailDamage(int crew,int level) {
 const int star=MergeTrees::Star(crew),band=star<=2?0:star<=4?1:2;
 const int skill=crewData[crew*CREWDATASIZE+CREWDATA_SKILL1+band];
 long long power=std::max(10LL,std::min(GetCrewPower(crew,std::max(1,level)),100000000LL));
 power=power*std::max(100,SkillDamagePct(skill))/100;
 if(band==2&&SkillKind(skill)==HEROSKILL){
  ITEM* weapon=&ao[PLAYER].equip[EQUIP_WEAPON];
  if(weapon->type==EMPTY)weapon=&robin.charData[std::max(0,std::min(2,curHero))].equip[EQUIP_WEAPON];
  power=std::max(20LL,std::min(GetEquipPower(weapon,weapon->lv),100000000LL))*std::max(400,SkillDamagePct(skill))/100;
 }
 long long value=power*MergeBoard::CrewMul(star);
 if(MergeTrees::Trait(crew)==2)value+=value*MergeBoard::StrikePct(star)/100;
 if(MergeTrees::Trait(crew)==3)value+=value*MergeBoard::VolleyPct(star)/100;
 return value;
}
void CrewDetailDraw(ITEM* it,int x,int y,float zoom,float winH) {
 const int c=it->detail;
 if(c<0||c>=MergeTrees::CrewCount)return;
 const int star=MergeTrees::Star(c),trait=MergeTrees::Trait(c),role=MergeTrees::Role(c);
 static const char* names[]={u8"표식",u8"고무",u8"강타",u8"연타",u8"빙결",u8"지속 피해"};
 CdBeginBoard();
 // Leave the persistent bottom navigation accessible, including on short windows.
 const float bottom=(float)BOTTOMMENUHEIGHT+12.0f;
 const float top=(float)DY-GNBHEIGHT;
 sCdU=std::min((float)DX/CD_DESIGNW,(top-bottom)/CD_DESIGNH);
 sCdOx=(DX-CD_DESIGNW*sCdU)/2;sCdOy=top;
 CdDrawFrame(TEXT_CREW_DETAIL_TITLE);
 DrawItemCard(ITEM_CREW,c,it->grade,it->lv,it->count,false,Loc(70),LocY(150),false,(360.0f/340)*sCdU,true,false,false,false,0);
 sCrewEquipBtnW=sCrewEquipBtnH=0;
 char line[192];
 sprintf(line,u8"%s · ★%d",MergeTrees::RoleName[role],star);
 CdBody(line,195,570,1.65f,CENTER,CD_UP);
 CdOneLine(TEXTPTR(TEXT_MONSTERNAME_START+crewData[c*CREWDATASIZE+CREWDATA_TYPE]),65,520,290,1.7f,CD_INK);
 DrawPanel(395,158,635,410);
 DrawCdRibbonStr(u8"전투 정보",712,120,500,76,1.95f,-8);
 const int skill=crewData[c*CREWDATASIZE+CREWDATA_SKILL1+(star<=2?0:star<=4?1:2)];
 DrawCrewSkillIconFramed(skill,425,210,110);
 CdBody(u8"한 번 공격 피해",565,218,1.6f,LEFT,CD_INK);
 sprintf(line,"%lld",CrewDetailDamage(c,it->lv));
 CdBody(line,565,269,2.45f,LEFT,CD_UP);
 sprintf(line,u8"특성 · %s",names[trait]);CdBody(line,425,353,1.9f,LEFT,CD_INK);
 switch(trait) {
 case 0:sprintf(line,u8"이후 공격 피해 +%d%%",MergeBoard::ExposePct(star));break;
 case 1:sprintf(line,u8"다음 공격 피해 ×%d",MergeBoard::InspireMul(star));break;
 case 2:sprintf(line,u8"자기 피해 +%d%% · 위 수치에 포함",MergeBoard::StrikePct(star));break;
 case 3:sprintf(line,u8"연타 합산 피해 · 위 수치에 포함");break;
 case 4:if(star<=2)sprintf(line,u8"적의 다음 공격 피해 절반");else sprintf(line,u8"적 공격 %d회 건너뛰기",MergeBoard::ChillSkipTurns(star));break;
 default:sprintf(line,u8"공격 피해의 %d%% · %d턴 지속",MergeBoard::BurnPct(star),MergeBoard::BurnTurns(star));break;
 }
 CdOneLine(line,425,418,570,1.5f,CD_UP);
 CdBody(u8"판에 배치된 동료마다 차례에 공격",425,495,1.35f,LEFT,CD_INK);
 DrawPanel(55,625,980,410);
 DrawCdRibbonStr(u8"레벨 강화",545,587,470,76,1.95f,-8);
 const bool max=it->lv>=GetCrewMaxLevel();
 sprintf(line,u8"현재 Lv.%d",it->lv);CdBody(line,300,700,1.8f,CENTER,CD_INK);
 if(max)sprintf(line,u8"최고 레벨");else sprintf(line,u8"강화 후 Lv.%d",it->lv+1);
 CdBody(line,790,700,1.8f,CENTER,CD_UP);
 sprintf(line,"%lld",CrewDetailDamage(c,it->lv));CdBody(line,300,780,2.7f,CENTER,CD_INK);
 CdBody(u8"→",545,790,2.0f,CENTER,CD_INK);
 if(!max){sprintf(line,"%lld",CrewDetailDamage(c,it->lv+1));CdBody(line,790,780,2.7f,CENTER,CD_UP);}
 CdBody(u8"공격 피해",300,862,1.5f,CENTER,CD_INK);CdBody(u8"공격 피해",790,862,1.5f,CENTER,CD_INK);
 CdBody(u8"장비·표식·고무 등 추가 보정 전 기준",545,947,1.4f,CENTER,CD_INK);
 if(!max)DrawCdCost(GetCrewUpgradeCost(it,0),it->count,GetCrewUpgradeCost(it,1),CanCrewLevelUp(it),TOUCH_FUNC_CREW_LEVELUP);
 else CdBody(u8"최고 레벨에 도달했습니다",545,1150,1.8f,CENTER,CD_INK);
}
