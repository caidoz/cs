#pragma once
bool MergeRouletteActive();
void MergeRouletteSetHeartCapacity(int capacity); // 5..20, same pixel hearts, optional second row
void MergeRouletteBegin(bool resume=false);
void MergeRouletteLobbyDraw();
bool MergeRouletteLobbySceneDraw();
bool MergeRouletteOriginalPreview(int castle,int x,int top,int width,int height);
void MergeRouletteDraw();
// phase: 0 begin, 1 drag, 2 release, 3 cancel. Consumes only its own mode.
bool MergeRouletteTouch(int phase,int id,float x,float y);
