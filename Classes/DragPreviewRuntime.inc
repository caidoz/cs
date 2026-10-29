// Included after LoadoutDropCell: UI adapter for the read-only model.
namespace {
struct DragInfoLine {std::string text;int color;};
static int dragInfoInspect=-1,dragInfoInspectUntil=0,dragInfoPage=0;
static int dragInfoLastKey=-999,dragInfoLastCol=-999,dragInfoLastRow=-999,dragInfoStill=0;
static int dragInfoRendered=0,dragInfoGains=0,dragInfoLosses=0;
static const int kInfoGain=0x66E5C4,kInfoLoss=0xFFB060,kInfoWait=0xC4B0FA;

static void LoadoutPowerDraw() {
 const long long value=LoadoutCombatPower();
 static long long target=-1,start=0,displayed=0,change=0;
 static int began=0,arrived=-10000,hero=-1,lastDraw=-10000;
 if(target<0 || hero!=curHero || frame-lastDraw>FPS) {
  target=start=displayed=value;change=0;hero=curHero;began=frame;arrived=-10000;
 } else if(value!=target) {
  change=value-target;start=displayed;target=value;began=frame;arrived=-10000;
 }
 lastDraw=frame;
 const float t=Min(1.0f,Max(0.0f,(frame-began)/(float)Max(1,FPS*45/100)));
 const float eased=1-(1-t)*(1-t)*(1-t);
 displayed=t>=1?target:start+(long long)((target-start)*eased);
 if(t>=1 && arrived==-10000 && change!=0) arrived=frame;
 const float pulse=arrived>=0?Max(0.0f,1-(frame-arrived)/(float)Max(1,FPS/2)):0;
 const int color=change>0?kInfoGain:change<0?kInfoLoss:0xEAD18D;
 const int x=DX-170,top=LoadoutFootY()+54,w=160,h=52;
 const int sx=clipX,sy=clipY,sx2=clipX2,sy2=clipY2;
 UnSectionClip(false);SetAlpha(ALPHA_MAX);
 MemRect(x,top,w,h,0x14283D);MemRectFrame(x,top,w,h,pulse>0?color:0xB49B62);
 if(pulse>0) MemRectFrame(x+3,top-3,w-6,h-6,color);
 char text[96];sprintf(text,"전투력 %lld",displayed);
 SetFontColor(t<1||pulse>0?color:COLOR_WHITE);
 CenterTextStrSolid(text,x+w/2,top-7,.8f*(1+pulse*.08f));
 if(change!=0 && (t<1 || pulse>0)) sprintf(text,"%+lld",change);
 else sprintf(text,"현재 편성");
 SetFontColor(change!=0 && (t<1||pulse>0)?color:0xA4B7C9);
 CenterTextStrSolid(text,x+w/2,top-32,.55f);
 SetFontColor(COLOR_WHITE);clipX=sx;clipY=sy;clipX2=sx2;clipY2=sy2;
}

static void LoadoutHeroStatusDraw() {
 const OBJECT& hero=ao[PLAYER];const bool live=IsStageRealtime();
 const long long maximum=Max(1LL,live?hero.maxhp:hero.ps[PS_HP]);
 const long long hp=live?Max(0LL,Min(maximum,hero.hp)):maximum;
 const long long armor=live?hero.shieldMax:Max(1LL,hero.ps[PS_ARMOR]);
 const long long currentArmor=live?hero.shield:armor;
 const int sx=clipX,sy=clipY,sx2=clipX2,sy2=clipY2;
 UnSectionClip(false);SetAlpha(ALPHA_MAX);
 char text[96];sprintf(text,"아군 요새");
 DrawFortressStatusCard(12,gLoadoutGridY+148,120,hp,maximum,currentArmor,armor,text);
 const int boxW=260,boxH=44,bx=DX-boxW-12,by=gLoadoutGridY+80;
 MemRect(bx,by,boxW,boxH,0x0C1A2E);MemRectFrame(bx,by,boxW,boxH,0x6FA8FF);
 SetFontColor(COLOR_WHITE);
 const float zoom=.95f;const int star=18*_2X,gap=4*_2X;
 const int textY=by-(int)((boxH-FONT_HEIGHT*zoom)/2);
 sprintf(text,"%d / %d",LoadoutUsed(),LoadoutPoint());
 const int nameW=(int)StringWidth("보급력",zoom),numW=(int)StringWidth(text,zoom);
 int at=bx+(boxW-nameW-star-numW-gap*2)/2;
 CenterTextStrSolid("보급력",at+nameW/2,textY,zoom);at+=nameW+gap;
 DrawIcon(ICON_STAR,at,by-(boxH-star)/2,(float)star/ITEMICONSIZE,false,false,false,true);at+=star+gap;
 SetFontColor(LoadoutUsed()>LoadoutPoint()?COLOR_RED:COLOR_REALYELLOW);
 CenterTextStrSolid(text,at+numW/2,textY,zoom);SetFontColor(COLOR_WHITE);
 clipX=sx;clipY=sy;clipX2=sx2;clipY2=sy2;
 LoadoutPowerDraw();
}

static const char* DragInfoKindName(int kind) {
 static const char* names[]={"검","총","부메랑","투구","갑옷","장갑","바지","신발","방패","목걸이","반지","포대","정수","작전서","동료","물건"};
 return names[Max(0,Min(15,kind))];
}
static std::string DragInfoName(const DragPreview::Item& p) {
 char name[128];
 if(p.kind==DragPreview::Crew && p.crew>=0 && p.crew<64) return AllyBalance::Profiles[p.crew].name;
 if(p.kind==DragPreview::Crew && p.detail>=0 && p.detail<gTotalEnemy) return textId[TEXT_MONSTERNAME_START+p.detail];
 if(p.type>=ITEM_SWORD && p.type<ITEM_GEM)
  return textId[TEXT_ITEMNAME_START+GetItemName(p.type,p.detail,p.grade)];
 sprintf(name,"%s #%02d",DragInfoKindName(p.kind),p.detail+1);return name;
}
static std::string DragInfoEffect(AllyBalance::Action action,int power) {
 using A=AllyBalance::Action;char text[180];const char* label="";const char* unit="%";
 switch(action) {
 case A::Shield:label="최대 보호막 회복";break;
 case A::Heal:case A::Repair:label="최대 체력 회복";break;
 case A::Supply:label="무기 공격 준비 진행";break;
 case A::Inspire:label="인접 동료 다음 탄 강화";unit="%p (합계 40%p 한도)";break;
 case A::Fortify:label="다음 기본 피격 감소";break;
 case A::Cleanse:return "해로운 효과 하나 제거";
 case A::Volley:label="동료 공격력 기준 추가 사격";break;
 case A::Strike:label="영웅 공격력 기준 타격";break;
 case A::Leech:label="영웅 공격력 50% 타격 + 최대 체력 회복";break;
 case A::Discharge:label="감전 소비 타격 (4중첩 기준)";break;
 case A::Burn:label="화상";unit="중첩 (상한 5)";break;
 case A::Poison:label="중독";unit="중첩 (상한 6)";break;
 case A::Chill:label="냉기";unit="중첩 (상한 3)";break;
 case A::Shock:label="감전";unit="중첩 (상한 4)";break;
 case A::Bleed:label="출혈";unit="중첩 (상한 4)";break;
 case A::Expose:label="취약";unit="중첩 (지정 강타에 소비)";break;
 case A::PrototypeSmith:return "8초마다 최대 체력 5% 수리";
 case A::PrototypeCleric:return "체력 50% 이하: 최대 체력 10% 회복 / 15초";
 case A::PrototypeCaptain:return "영웅 공격에 연계 사격 / 최소 3초";
 }
 sprintf(text,"%s %d%s",label,power,unit);return text;
}
static const char* DragInfoCondition(AllyBalance::Condition c) {
 using C=AllyBalance::Condition;
 switch(c) {
 case C::Front:return "전열: 오른쪽 절반에 배치";
 case C::Back:return "후열: 왼쪽 절반에 배치";
 case C::AdjacentWeapon:return "검·총·부메랑과 인접 필요";
 case C::AdjacentCrew:return "다른 ID 동료와 인접 필요";
 case C::Alone:return "다른 ID 동료와 떨어져 배치";
 case C::LowHp:return "전투 중 성 체력 50% 이하일 때";
 case C::HighHp:return "전투 중 성 체력 50% 초과일 때";
 case C::LowShield:return "전투 중 보호막 50% 이하일 때";
 case C::EnemyLowHp:return "적 체력 50% 이하일 때";
 case C::EnemyHighHp:return "적 체력 50% 초과일 때";
 case C::EnemyDebuffed:return "적에게 상태이상이 있을 때";
 case C::EnemyClean:return "적에게 상태이상이 없을 때";
 case C::EveryThird:return "영웅 원본 공격 이벤트 3회 이후";
 default:return "전투 중 고유 쿨타임에 따라 발동";
 }
}
static DragPreview::Item DragInfoFromPart(const GridPart& p,int key,int c,int r,bool owned,const ITEM* item=NULL) {
 auto v=GridPreviewItem(p,key,c,r);
 if(v.kind==DragPreview::Crew) {
  v.crew=owned && p.detail<gTotalCrew?p.detail:GetCrewIdxFromType(p.detail);
  if(v.crew>=0 && v.crew<64) v.role=(int)GetCrewRole(AllyBalance::Profiles[v.crew].npc);
  else if(p.detail>=0 && p.detail<gTotalEnemy) v.role=(int)GetCrewRole(p.detail);
 }
 v.value=item?item->value:DragPreview::Weapon(v.kind)||DragPreview::Defense(v.kind)||v.kind==DragPreview::Neck||v.kind==DragPreview::Ring?MakeItemValue(p.type,p.detail,p.grade,1):0;
 if(item) v.equipped=item->type==curHero && item->id==robin.charData[Max(0,Min(TOTALPLAYER-1,PlayerHeroType()))].equip[EQUIP_WEAPON].id;
 return v;
}
static void DragInfoBasic(std::vector<DragInfoLine>& lines,const DragPreview::Item& p,bool pvp,bool expanded) {
 char text[220];using namespace DragPreview;
 if(pvp) lines.push_back({"아래 효과 수치는 일반 스테이지 기준",kInfoWait});
 if(p.kind==Crew && p.crew>=0 && p.crew<64) {
  const auto& a=AllyBalance::Profiles[p.crew];
  sprintf(text,"기본 사격 %.1f초 / 기존 공격력 %d%%",a.attackMs/1000.0f,a.attackPercent);lines.push_back({text,COLOR_WHITE});
  sprintf(text,"고유: %s / %.1f초",a.ability,a.abilityMs/1000.0f);lines.push_back({text,COLOR_WHITE});
  lines.push_back({DragInfoEffect(a.action,a.power),COLOR_WHITE});
  lines.push_back({std::string("대기 조건: ")+DragInfoCondition(a.condition),kInfoWait});
  if(p.role==CREW_ROLE_ARTILLERY) {
   sprintf(text,"포격형 · 포대 인접: 준비 -20%%, 탄 크기 +15%%, 추가탄 +%d",p.crew==57?2:1);
   lines.push_back({text,kInfoWait});
  }
  else if(p.role==CREW_ROLE_COMMANDER) lines.push_back({"지휘형 · 포대 직접 강화 없음",kInfoWait});
  const auto& link=a.synergy[Max(0,Min(2,curHero))];
  const char* trigger=curHero==0?"로빈 검 명중":curHero==1?"디아나 총 사격":"맥스 귀환 완료";
  if(curHero==2 && p.crew==36) trigger="맥스 비행 중";
  if(curHero==2 && p.crew==57) trigger="맥스 귀환 시작";
  sprintf(text,"%s 연계 / %.1f초",trigger,link.cooldownMs/1000.0f);lines.push_back({text,kInfoGain});
  lines.push_back({DragInfoEffect(link.action,link.power),kInfoGain});
  if(expanded && dragInfoInspect>=0) for(int hero=0;hero<3;++hero) if(hero!=curHero) {
   const auto& other=a.synergy[hero];
   sprintf(text,"%s 연계: %s / %.1f초",hero==0?"로빈":hero==1?"디아나":"맥스",
    DragInfoEffect(other.action,other.power).c_str(),other.cooldownMs/1000.0f);
   lines.push_back({text,kInfoWait});
  }
  if(link.action==AllyBalance::Action::Supply||a.action==AllyBalance::Action::Supply)
   lines.push_back({"보급: 영웅 공격 한 주기 합계 30% 한도",kInfoWait});
  if(pvp) lines.push_back({"고유 능력·영웅 연계: 일반 스테이지 전용",kInfoLoss});
 } else if(p.kind==Crew) {
  lines.push_back({"포획한 몬스터 / 기본 공격 지원",COLOR_WHITE});
  lines.push_back({"64종 동료의 고유 능력·영웅 연계는 없음",kInfoWait});
 } else if(Weapon(p.kind)) {
  sprintf(text,"기본 공격력 %d / %s",p.value,p.equipped?"히어로 장착 무기":"가방 무기");lines.push_back({text,COLOR_WHITE});
  if(p.kind==Sword) {sprintf(text,"공격 준비 %.2f초",StageSwordCooldown(p.detail)/(float)FPS);lines.push_back({text,COLOR_WHITE});}
  else if(p.kind==Boomerang) lines.push_back({"비행 → 귀환 → 재준비 / 복귀 전 재발사 불가",COLOR_WHITE});
  else lines.push_back({"디아나 기본 총 사격에 사용",COLOR_WHITE});
 } else if(Defense(p.kind)) {
  if(p.kind==Armor) sprintf(text,"가방 방어력 +%d",p.value*3/2);
  else if(p.kind==Glove) sprintf(text,"공격력 +%d / 치명 피해 +%d / 흡혈 +%d",p.value/2,15+p.grade*5,2+p.grade);
  else if(p.kind==Pants) sprintf(text,"기본 체력 +%d / 체력 재생 +%d",p.value*8,5+p.grade*2);
  else if(p.kind==Helm) sprintf(text,"방어력 +%d / 치명·공격 준비 능력 +%d",p.value/2,5+p.grade*2);
  else if(p.kind==Boots) sprintf(text,"방어력 +%d / 회피 +%d / 골드 +%d",p.value/2,5+p.grade*2,10+p.grade*3);
  else sprintf(text,"가방 방어력 +%d",p.value);
  lines.push_back({text,COLOR_WHITE});
  lines.push_back({p.kind==Pants?"성 체력 증가 / 인접 동료 체력 기여 강화":"방어막 기여 / 전투 중 보호막 재충전",COLOR_WHITE});
  if(p.kind==Glove) lines.push_back({"추가 검 인접: 피해 +20%",kInfoWait});
  if(p.kind==Helm) lines.push_back({"검 인접: 준비 −15% / 작전서 인접: −20%",kInfoWait});
  if(p.kind==Boots) lines.push_back({"방어 장비 인접: 재충전 준비 −20%",kInfoWait});
 } else if(p.kind==Cannon) {
  sprintf(text,"성 %d 전용 포대 / 기본 준비 %.2f초",p.detail+1,CastleCannonCooldown(p.detail)/(float)FPS);lines.push_back({text,COLOR_WHITE});
  lines.push_back({"검·방어구·포격 동료·정수와 인접 연계",kInfoWait});
 } else if(p.kind==Recipe) lines.push_back({"궁극기 기본 준비 8초 / 영웅 공격력 400%",COLOR_WHITE});
 else if(p.kind==Essence) {
  static const char* desc[]={"마력: 포대 준비 −15% × 런 레벨","화염: 포탄 크기 +18% × 런 레벨 / 적에게 독 부여",
   "빙결: 포대 준비 −12% × 런 레벨 / 적 둔화","번개: 포대 추가 타격 +런 레벨 / 적 기절"};
  lines.push_back({desc[p.detail%4],COLOR_WHITE});lines.push_back({"포대 인접 필요 / 준비 감소 합계 60% 한도",kInfoWait});
 } else {
  sprintf(text,"공용 장비: 가방 방어력 +%d / 부가 옵션 적용",p.value);lines.push_back({text,COLOR_WHITE});
 }
}
static const char* DragInfoRuleName(int rule) {
 using namespace DragPreview;
 switch(rule) {
 case SwordHaste:return "검 준비 단축 (%)";case SwordPower:return "추가 검 피해 강화 (%)";
 case Temper:return "담금질 공격력 강화 (%)";case Coop:return "협공: 검 공격 N회마다";
 case ArmorPower:return "방어막 펄스 강화 (%)";case ShieldHaste:return "보호막 준비 단축 (%)";
 case TacticHaste:return "궁극기 준비 단축 (%)";case CrewHp:return "동료 체력 기여율 (%)";
 case CannonDamage:return "포대 추가 피해";case CannonScale:return "포탄 크기 증가 (%)";
 case CannonHaste:return "포대 준비 단축 (%) · 최대 60";case CannonHits:return "포대 추가 타격 수";
 case FireAmmo:return "화염 포탄: 독 부여";case IceAmmo:return "빙결 포탄: 둔화";case ThunderAmmo:return "번개 포탄: 기절";
 case Placement:return "고유 능력 배치 조건";case InspireTargets:return "격려: 다음 탄 강화 (%p) · 최대 40";
 case KingTactic:return "왕: 궁극기 준비 단축 (%) / 피해 500%";
 case DurakTactic:return "듀라크: 궁극기 후 무기·동료 준비 완료";
 case ShockChain:return "감전 축적 → 소비 연계 (인접 무관)";
 case ExposeChain:return "취약 → 지정 강타 +25% (인접 무관)";
 case Duplicate:return "동일 동료 능력·시계 공유 (최초 배치 기준)";
 case SupplyPotential:return "보급 연계 가능 (%) · 주기당 합계 최대 30";
 default:return "연계";
 }
}
static const DragPreview::Item* DragInfoFind(const std::vector<DragPreview::Item>& list,int key) {
 for(const auto& p:list) if(p.key==key) return &p;return NULL;
}
static void DragInfoMarkPrimary(std::vector<DragPreview::Item>& items) {
 int best=-1,rank=LOADOUT_MAX+1;
 for(int i=0;i<(int)items.size();++i) if(DragPreview::Weapon(items[i].kind)) {
  items[i].equipped=false;
  if(items[i].type!=curHero) continue;
  const int order=LoadoutFind(items[i].key-1000),r=order>=0?order:gLoadoutCnt;
  if(r<rank) {best=i;rank=r;}
 }
 if(best>=0) items[best].equipped=true;
}
static void DragInfoDotted(int x,int y,int xx,int yy,int color) {
 const int count=Max(1,Max(Abs(xx-x),Abs(yy-y))/7);
 for(int i=0;i<=count;++i) MemRect(x+(xx-x)*i/count,y+(yy-y)*i/count,2,2,color);
}
static void DragInfoDraw(const std::vector<DragPreview::Item>& before,const std::vector<DragPreview::Item>& after,
 const DragPreview::Item& held,const char* invalid,bool removing,bool pvp,const std::string& footer,
 int originX,int originTop,int cell) {
 using namespace DragPreview;
 if(held.key!=dragInfoLastKey||held.col!=dragInfoLastCol||held.row!=dragInfoLastRow) {
  dragInfoStill=frame;dragInfoPage=0;dragInfoLastKey=held.key;dragInfoLastCol=held.col;dragInfoLastRow=held.row;
 }
 const bool expanded=true;
 std::vector<DragInfoLine> lines;
 if(invalid) lines.push_back({std::string("X ")+invalid,kInfoLoss});
 else lines.push_back({removing?"− 가방에서 제거할 때":"+ 이 자리에 배치할 때",removing?kInfoLoss:kInfoGain});
 lines.push_back({footer,COLOR_WHITE});
 std::vector<DragInfoLine> basic;DragInfoBasic(basic,held,pvp,expanded);
 for(int i=0;i<(int)basic.size()&&i<2;++i) {
  auto line=basic[i];if(invalid) line.color=0x8794A3;lines.push_back(line);
 }
 auto changes=Diff(Evaluate(before,gGridW,curHero),Evaluate(after,gGridW,curHero));
 // Losses and conditions take precedence; only unrelated unchanged effects are folded.
 std::stable_sort(changes.begin(),changes.end(),[](const Change& a,const Change& b){return (a.delta<0?0:a.delta>0?1:2)<(b.delta<0?0:b.delta>0?1:2);});
 std::vector<DragInfoLine> effects;
 dragInfoGains=dragInfoLosses=0;
 if(!invalid && !pvp) for(const auto& change:changes) {
  const auto& e=change.after;const auto& old=change.before;
  if((e.value==0 && old.value==0) || (change.delta==0 && e.providers==old.providers)) continue;
  const Item* target=DragInfoFind(after,e.target);if(!target) target=DragInfoFind(before,e.target);
  if(!target) continue;
  const bool loss=change.delta<0 || (e.rule==Duplicate && e.value>0);
  const int color=loss?kInfoLoss:change.delta>0?kInfoGain:kInfoWait;
  char text[320];
  sprintf(text,"%s %s [%d,%d]: %s %d → %d",loss?"-":change.delta>0?"+":"=",
   DragInfoName(*target).c_str(),target->col+1,target->row+1,DragInfoRuleName(e.rule),old.value,e.value);
  if(e.rule==Placement) sprintf(text,"%s %s: 배치 조건 %s → %s",loss?"-":change.delta>0?"+":"=",
   DragInfoName(*target).c_str(),old.value?"충족":"미충족",e.value?"충족":"미충족");
  if(e.rule==CrewHp) sprintf(text,"%s %s: 성 체력 기여 %d%% → %d%%",loss?"-":"+",DragInfoName(*target).c_str(),
   old.value?old.value:DragInfoFind(before,e.target)?50:0,e.value?e.value:DragInfoFind(after,e.target)?50:0);
  effects.push_back({text,color});
  if(e.value==old.value && e.providers!=old.providers) {
   sprintf(text,"제공자 %d → %d명 · 효과 유지/상한",old.providers,e.providers);effects.push_back({text,kInfoWait});
  }
  if(change.delta>0) ++dragInfoGains;if(change.delta<0) ++dragInfoLosses;
  if(change.delta!=0) {
   const int x=originX+target->col*cell,y=originTop-(gGridH-target->row-target->h)*cell;
   MemRectFrame(x+1,y-1,target->w*cell-2,target->h*cell-2,color);
   if(target->key!=held.key) {
    const int hx=originX+(held.col*2+held.w)*cell/2;
    const int hy=originTop-(gGridH-held.row)*cell+held.h*cell/2;
    DragInfoDotted(hx,hy,x+target->w*cell/2,y-target->h*cell/2,color);
   }
  }
 }
 if(invalid) effects.push_back({"놓을 수 없어 예상 연계는 적용되지 않습니다",kInfoLoss});
 else if(pvp) effects.push_back({"일반 스테이지 인접 연계는 이 모드에 합산하지 않음",kInfoWait});
 else if(effects.empty()) effects.push_back({"= 이 위치의 추가 연계 없음 · 기본 기능 유지",kInfoWait});
 const int maxEffects=expanded?8:3;
 const int pages=Max(1,((int)effects.size()+maxEffects-1)/maxEffects);
 const int page=dragInfoPage%pages;
 for(int i=page*maxEffects;i<(int)effects.size()&&i<(page+1)*maxEffects;++i) lines.push_back(effects[i]);
 if(pages>1) {char text[96];sprintf(text,"연계 %d/%d · 상세창의 > 버튼으로 다음 쪽",page+1,pages);lines.push_back({text,kInfoWait});}
 for(int i=2;i<(int)basic.size();++i) {auto line=basic[i];if(invalid) line.color=0x8794A3;lines.push_back(line);}
 const int width=Min(DX-24,520);
 const float zoom=0.85f;
 // UTF-8 wrapping preserves glyph boundaries and applies to every detail line.
 std::vector<DragInfoLine> wrapped;
 for(const auto& line:lines) {
  std::string part;
  for(size_t i=0;i<line.text.size();) {
   const unsigned char c=(unsigned char)line.text[i];const size_t bytes=c<128?1:(c&0xe0)==0xc0?2:(c&0xf0)==0xe0?3:4;
   const std::string next=line.text.substr(i,bytes);
   if(!part.empty() && StringWidth((part+next).c_str(),zoom)>width-24) {wrapped.push_back({part,line.color});part.clear();}
   part+=next;i+=bytes;
  }
  if(!part.empty()) wrapped.push_back({part,line.color});
 }
 const int lineH=30;
 // Fit above the destination grid; overflow is paged, never laid over the cells.
 const int ceiling=DY-48;
 // The temporary detail card may cover the status HUD, but never the grid.
 // Reserving the HUD's entire height left only a single readable line.
 const int bottom=Max(12,originTop+24);
 const int limit=Max(1,Min(16,(ceiling-bottom-58)/lineH));
 const int textPages=Max(1,((int)wrapped.size()+limit-1)/limit);
 const int textPage=dragInfoPage%textPages;
 const int count=Min(limit,(int)wrapped.size()-textPage*limit);
 const int height=58+count*lineH;
 const int x=(DX-width)/2;
 const int top=bottom+height;
 const int savedX=clipX,savedY=clipY,savedX2=clipX2,savedY2=clipY2;
 UnSectionClip(false);SetAlpha(ALPHA_MAX);MemRect(x,top,width,height,0x14283D);
 if(invalid) {
  MemRect(x,top,width,height,0x491F2A);
  const bool overGrid=gLoadoutDrag>=0?LoadoutOverGrid():gGridDragOn&&GridInsideBag(touchX,touchY);
  for(int row=0;overGrid && row<held.h;++row) for(int col=0;col<held.w;++col) if(Cell(held,col,row)) {
   const int c=held.col+col,r=held.row+row;
   if(c<0 || r<0 || c>=gGridW || r>=gGridH || !GridMaskAt(c,r)) continue;
   const int cx=originX+c*cell,cy=originTop-(gGridH-r-1)*cell;
   SetAlpha(16);MemRect(cx+2,cy-2,cell-4,cell-4,0xD3293E);SetAlpha(ALPHA_MAX);
   MemRectFrame(cx+2,cy-2,cell-4,cell-4,0xFF6677);
  }
 }
 MemRectFrame(x,top,width,height,invalid?kInfoLoss:kInfoGain);
 int star=0;
 if(held.kind==Crew && held.crew>=0 && held.crew<64) star=GetItemStar(ITEM_CREW,held.crew,GRADE_NORMAL);
 else if(held.type>=ITEM_SWORD && held.type<ITEM_GEM) star=GetItemStar(held.type,held.detail,held.grade);
 else if(held.kind==Cannon) star=held.detail/2+1;
 char title[180];sprintf(title,"%s  %d성 %dx%d  %s",DragInfoName(held).c_str(),star,held.w,held.h,expanded?"상세":"미리보기");
 if(star<=0) sprintf(title,"%s  %dx%d  %s",DragInfoName(held).c_str(),held.w,held.h,expanded?"상세":"미리보기");
 SetFontColor(COLOR_WHITE);CenterTextStrSolid(title,x+width/2,top-21,.85f);
 for(int i=0;i<count;++i) {
  const auto& line=wrapped[textPage*limit+i];SetFontColor(line.color);
  DrawTextStrSystem(line.text.c_str(),x+12,top-52-i*lineH,zoom,LEFT,true);
 }
 if(textPages>1) {char t[64];sprintf(t,"%d/%d",textPage+1,textPages);SetFontColor(kInfoWait);CenterTextStrSolid(t,x+width-28,top-21,.55f);}
 if(dragInfoInspect>=0 && gLoadoutDrag<0 && !gGridDragOn) {
  SetRectPoint(x,top,width,height,TOUCH_FUNC_LOADOUT_INFO_HOLD);
  DrawUiButton(x+width-34,top-25,28,20,"X",TOUCH_FUNC_LOADOUT_INFO_CLOSE);
  if(textPages>1 || pages>1) DrawUiButton(x+width-72,top-25,34,20,">",TOUCH_FUNC_LOADOUT_INFO_NEXT);
 }
 clipX=savedX;clipY=savedY;clipX2=savedX2;clipY2=savedY2;++dragInfoRendered;
}
static void DragInfoLoadoutDraw() {
 const bool inspecting=gLoadoutDrag<0 && dragInfoInspect>=0 && frame<dragInfoInspectUntil;
 const int inv=inspecting?(dragInfoInspect<gLoadoutCatCnt?gLoadoutOwn[gLoadoutCatType[dragInfoInspect]][gLoadoutCatDetail[dragInfoInspect]]:-1):gLoadoutDrag;
 if(!inspecting && inv<0) return;
 GridPart part;
 if(inv>=0) GridGearPart(&robin.inven[inv],&part);
 else LoadoutPartOf(gLoadoutCatType[dragInfoInspect],gLoadoutCatDetail[dragInfoInspect],&part);
 unsigned char occ[GRIDTEST_H][GRIDTEST_W];GridPart parts[LOADOUT_MAX];int cols[LOADOUT_MAX],rows[LOADOUT_MAX];bool fit[LOADOUT_MAX]={};
 LoadoutPreviewPack(occ,parts,cols,rows,fit);
 std::vector<DragPreview::Item> before;
 for(int i=0;i<gLoadoutCnt;++i) if(fit[i]&&!gLoadoutBad[i]) {
  const int id=gLoadoutPackInven[i];if(id<0) continue;
  before.push_back(DragInfoFromPart(parts[i],1000+id,cols[i],rows[i],true,&robin.inven[id]));
  if(id==inv) part=parts[i];
 }
 DragInfoMarkPrimary(before);
 int col=0,row=0;if(!inspecting) LoadoutDropCell(inv,&part,&col,&row);
 auto held=DragInfoFromPart(part,inv>=0?1000+inv:20000+dragInfoInspect,col,row,true,inv>=0?&robin.inven[inv]:NULL);
 auto after=before;after.erase(std::remove_if(after.begin(),after.end(),[&](const DragPreview::Item& p){return p.key==held.key;}),after.end());
 const bool removing=!inspecting && gLoadoutDragFromBag && !LoadoutOverGrid();
 const char* invalid=NULL;
 if(inspecting && inv<0) invalid="미획득";
 else if(!LoadoutHeroHas(curHero,part.type)) invalid="다른 히어로 전용 · 얼굴의 히어로 선택 필요";
 else if(part.type==ITEM_CANNON && part.detail!=CastleMenuModel::Clamp(robin.castle)) invalid="다른 성 전용 포대";
 else if(!removing && !inspecting && !LoadoutOverGrid()) invalid="가방 안에 놓아야 실립니다";
 else if(!removing && !inspecting) {
  memset(occ,0,sizeof(occ));
  for(const auto& p:after) for(int y=0;y<p.h;++y) for(int x=0;x<p.w;++x) if(DragPreview::Cell(p,x,y))
   if(p.col+x>=0&&p.row+y>=0&&p.col+x<GRIDTEST_W&&p.row+y<GRIDTEST_H) occ[p.row+y][p.col+x]=1;
  if(!LoadoutPreviewCanPlace(&part,col,row,occ)) {
   invalid="배치 불가: 겹친 칸·성의 빈 칸·범위를 확인하세요";
   int cells=GridPartCellCount(&part);for(const auto& p:after) for(int y=0;y<p.h;++y) for(int x=0;x<p.w;++x) cells+=DragPreview::Cell(p,x,y)?1:0;
   if(cells>CastleEquipmentCapacity(GridLayoutCastleStage())) invalid="성의 점유 칸 한도 초과";
  }
  if(LoadoutFind(inv)<0 && LoadoutUsed()+LoadoutCost(&robin.inven[inv])>LoadoutPoint()) invalid="보급력 부족";
 }
 if(!removing && !inspecting && !invalid) after.push_back(held);
 if(inspecting || invalid) after=before;
 DragInfoMarkPrimary(after);
 const auto* actual=DragInfoFind(after,held.key);if(!actual) actual=DragInfoFind(before,held.key);
 if(actual) held.equipped=actual->equipped;
 char footer[180];const int cost=inv>=0?LoadoutCost(&robin.inven[inv]):0;
 const int used=LoadoutUsed(),next=invalid||inspecting?used:removing?used-cost:LoadoutFind(inv)>=0?used:used+cost;
 bool hasWeapon=false;for(const auto& p:after) if(p.type==curHero) hasWeapon=true;
 sprintf(footer,"보급력 %d/%d → %d/%d%s",used,LoadoutPoint(),next,LoadoutPoint(),removing&&!hasWeapon?" · 기본 무기 없음: 출정 불가":"");
 DragInfoDraw(before,after,held,invalid,removing,gLoadoutForPvp,footer,gLoadoutGridX,gLoadoutGridY,gLoadoutCell);
}
static void DragInfoBattleDraw() {
 if(!gGridDragOn) return;
 const GridPart part=gGridDragRot?GridPartRotated(gGridDragDesc):gGridDragDesc;
 auto before=GridPreviewRuntime();
 if(gGridDragFrom>=0 && gGridDragFrom<GRIDTEST_MAXITEM && !DragInfoFind(before,gGridDragFrom)) {
  const auto& slot=gGridItem[gGridDragFrom];
  auto original=DragInfoFromPart(slot.part,gGridDragFrom,slot.col,slot.row,slot.equip>=0,&slot.item);
  original.level=Max(1,slot.level);before.push_back(original);
 }
 auto after=before;
 const int key=gGridDragFrom>=0?gGridDragFrom:20000;
 auto held=DragInfoFromPart(part,key,gGridDragCol,gGridDragRow,false);
 if(const auto* original=DragInfoFind(before,key)) {held=*original;held.col=gGridDragCol;held.row=gGridDragRow;held.w=part.w;held.h=part.h;held.cells=part.cells;}
 after.erase(std::remove_if(after.begin(),after.end(),[&](const DragPreview::Item& p){return p.key==key;}),after.end());
 int bx=0,by=0,bw=0,bh=0;GridStoreBandRect(&bx,&by,&bw,&bh);
 const bool store=GridStoreVisible() && touchX>=bx && touchX<bx+bw && touchY<=by && touchY>by-bh;
 int tx=0,ty=0,tw=0,th=0;GridTrashRect(&tx,&ty,&tw,&th);
 const bool trash=!store && touchX>=tx && touchX<=tx+tw && touchY<=ty && touchY>=ty-th;
 const bool inBag=!store && !trash && GridInsideBag(touchX,touchY);
 const bool removing=gGridDragFrom>=0 && (store||trash);
 const char* invalid=NULL;
 if(!inBag && !store && !trash) invalid="여기서 놓으면 취소 · 원래 자리로 돌아갑니다";
 else if(store && GridStoreFreeSlot()<0) invalid="보관함이 가득 찼습니다";
 else if(trash && gGridDragFrom<0) invalid="구매 전 물건과 보관함 물건은 판매할 수 없습니다";
 else if(trash && gGridItem[gGridDragFrom].equip>=0) invalid="장착 장비는 판매할 수 없습니다";
 else if(inBag) {
  switch(GridPlaceWhy(&part,held.col,held.row,gGridDragFrom)) {
   case GRIDWHY_CAP:invalid="성의 점유 칸 한도 초과";break;
   case GRIDWHY_OUT:invalid="가방 범위 밖";break;
   case GRIDWHY_MASK:invalid="성 확장 필요 · 사용할 수 없는 칸";break;
   case GRIDWHY_BUSY:invalid="다른 아이템과 겹침";break;
  }
 }
 const int cost=gGridDragFrom<0&&gGridDragStore<0?GridShopPrice(part.price):0;
 if(cost>gStageGold) invalid="골드 부족";
 std::string merge;
 if(inBag && !invalid && gGridDragFrom<0 && GridTestFreeSlot()<0) invalid="가방 아이템 개수 한도 초과";
 if(inBag && !invalid && gGridDragFrom<0 && gGridDragStore<0) {
  const int same=GridFindSame(&part,-1);
  if(same>=0) for(auto& p:after) if(p.key==same) {
   ++p.level;
   if(p.level>STAGE_GEAR_EVOLVE && p.grade<TOTALGRADE-1) {
    ++p.grade;p.level=1;p.value=MakeItemValue(part.type,part.detail,p.grade,Max(1,robin.stage+1));
   } else p.value=(int)((long long)p.value*(100+(p.level-1)*STAGE_GEAR_LVUP_PCT)/100);
   char text[160];sprintf(text,"동일 장비 자동 강화: %s Lv%d · 기존 위치 유지",DragInfoName(p).c_str(),p.level);merge=text;break;
  }
 }
 if(inBag && !invalid && merge.empty()) after.push_back(held);
 if(invalid) after=before;
 const int refund=trash && removing && !invalid?Max(1,part.price/2):0;
 char footer[200];sprintf(footer,"골드 %d → %d · 가격 %d%s",gStageGold,gStageGold-cost+refund,cost,store?" · 보관함으로":trash?" · 판매하면 연계 해제":"");
 DragInfoDraw(before,after,held,invalid,removing,false,merge.empty()?footer:merge+" / "+footer,gGridX,gGridBottom+gGridH*gGridCell,gGridCell);
}
}
void LoadoutInspect(int catalog) {
 if(catalog==-1) {dragInfoInspect=-1;dragInfoInspectUntil=0;return;}
 if(catalog==-2) {++dragInfoPage;dragInfoStill=frame-FPS;dragInfoInspectUntil=frame+FPS*30;return;}
 if(catalog<0 || catalog>=gLoadoutCatCnt) return;
 dragInfoInspect=catalog;dragInfoInspectUntil=frame+FPS*30;dragInfoPage=0;dragInfoStill=frame;
}

static bool DragInfoReview(int page) {
 if(!getenv("CS_DRAG_PREVIEW_REVIEW")) return false;
 using namespace DragPreview;
 const int savedW=gGridW,savedH=gGridH,savedHero=curHero;
 gGridW=8;gGridH=4;curHero=0;
 const int ox=40,top=DY-560,cell=64;
 MemRect(0,DY,DX,DY,0x102035);
 for(int y=0;y<4;++y) for(int x=0;x<8;++x) MemRectFrame(ox+x*cell,top-y*cell,cell,cell,0x53728A);
 GridPart sword={ITEM_SWORD,1,GRADE_NORMAL,1,2,6,"검",false,0};
 GridPart crew={ITEM_CREW,36,GRADE_NORMAL,2,2,0,"로키",false,0};
 std::vector<Item> before,after;
 auto a=DragInfoFromPart(sword,1,1,0,false);a.value=100;
 auto b=a;b.key=2;b.col=6;b.value=80;
 auto held=DragInfoFromPart(crew,3,6,2,true);held.col=6;held.row=2;
 before={a,b,held};held.col=2;held.row=2;after={a,b,held};
 const char* invalid=NULL;
 if(page==1) {
  crew.detail=50;held=DragInfoFromPart(crew,3,3,0,true);
  auto other=DragInfoFromPart(crew,4,5,0,true);other.crew=2;other.w=1;
  before={other};after={other,held};
 } else if(page==2) {invalid="다른 아이템과 2칸 겹침";after=before;}
 else if(page==3) {
  GridPart cannon={ITEM_CANNON,0,0,2,2,0,"포대",false,0};
  held=DragInfoFromPart(cannon,3,2,0,false);
  auto e=held;e.key=4;e.kind=Essence;e.col=4;e.w=1;e.h=1;e.level=10;e.detail=0;
  before={held};after={held,e};
 }
 for(const auto& p:after) {
  const int x=ox+p.col*cell,y=top-(4-p.row-p.h)*cell;
  MemRect(x+2,y-2,p.w*cell-4,p.h*cell-4,p.key==held.key?0x24564B:0x243854);
  SetFontColor(COLOR_WHITE);CenterTextStrSolid(DragInfoName(p).c_str(),x+p.w*cell/2,y-20,.4f);
 }
 dragInfoLastKey=held.key;dragInfoLastCol=held.col;dragInfoLastRow=held.row;dragInfoStill=frame-FPS;
 const int rendered=dragInfoRendered;
 DragInfoDraw(before,after,held,invalid,false,false,"검증 시안 · 실제 전투/보유 데이터 변경 없음",ox,top,cell);
 bool ok=dragInfoRendered==rendered+1;
 if(page==0) ok=ok&&dragInfoGains>0&&dragInfoLosses>0;
 if(page==2) ok=ok&&dragInfoGains==0&&dragInfoLosses==0;
 if(page==3) {
  bool cap=false;for(const auto& e:Evaluate(after,8,0)) if(e.rule==CannonHaste) cap=e.value==60;
  ok=ok&&cap;
 }
 gGridW=savedW;gGridH=savedH;curHero=savedHero;
 return ok;
}
