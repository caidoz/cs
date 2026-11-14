#pragma once
bool MergeRouletteActive();
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
