#pragma once
bool MergeRouletteActive();
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
