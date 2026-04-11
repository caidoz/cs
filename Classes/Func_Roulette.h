#pragma once

#ifndef _FUNC_ROULETTE_H_
#define _FUNC_ROULETTE_H_

// Utility 함수들
int GetUnitScore(OBJECT* pObj);
void DecideRouletteResult();
void InitRouletteJump(void);
void RouletteAttackStart(void);
int GetSameRouletteCnt(int objIdx);
int UpgradeSkillIdx(int reelIdx, int count);
void RouletteDraw(int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);

// Crew 관련
int GetHouseFromCrewIdx(int);
int GetCrewDmg(int crewIdx, int lv);
int GetCrewIdxFromType(int);
int GetCrewPrice(int crewIdx);
int GetCrewPositionX(int);
int GetCrewPositionY(int);


#endif