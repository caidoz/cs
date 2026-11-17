#pragma once
bool MergeRouletteActive();
//합성 전투의 방어막 통. 장비 창의 "방어" 는 옛 PS_ARMOR(힘×3+민첩, 체력 60 에 880)가 아니라 이것을 보여 준다.
long long MergeRouletteHeroShield(const OBJECT* hero);         // 통 최대치 = 체력 × ShieldPct(100%)
long long MergeRouletteHeroShieldRecovery(const OBJECT* hero); // 턴마다 채우는 양 = 낀 투구·갑옷·하체·발 값
// 고유 동료. 64명은 역할마다 두 히어로가 나눠 갖는다(content/merge_tree.tsv hero 열).
int MergeCrewOwnerHero(int crew);          // 0 로빈 · 1 디아나 · 2 맥스, 범위 밖이면 -1
bool MergeCrewAvailable(int crew);         // 주인 히어로를 이미 얻었는가(IsGetHero) - 뽑기·창고 지급이 거른다
void MergeRouletteSetHeartCapacity(int capacity); // Compatibility entry point; displays ten enlarged hearts.
void MergeRouletteBegin(bool resume=false);
void MergeRouletteBeginSiege();   // PVP debug: castle vs castle (MergeSiege.inc)
void MergeRouletteLobbyDraw();
bool MergeRouletteLobbySceneDraw();
void MergeRouletteBottomNavDraw();
int MergeRouletteBottomNavHeight();
bool MergeRouletteOriginalPreview(int castle,int x,int top,int width,int height);
void MergeRouletteDraw();
// phase: 0 begin, 1 drag, 2 release, 3 cancel. Consumes only its own mode.
bool MergeRouletteTouch(int phase,int id,float x,float y);
bool MergeRouletteDebugTouchReview();
