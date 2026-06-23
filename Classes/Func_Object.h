#pragma once

#ifndef _FUNC_OBJECT_H_
#define _FUNC_OBJECT_H_

// Object 그리기 관련
void GetMotionPtr(OBJECT* pObj);
void EraseCmf(OBJECT *);
void DrawObj(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void DrawPlayer(OBJECT *, int motion, int x, int y, int dirF, float zoom, float rotation, bool center, bool shadow, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void DrawPlayerIcon(int, int, int, int, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void DrawCmf(OBJECT *pObj, float rotation, float zoom, bool center, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void DrawCmfDetail(int cmf, int motion, int x, int y, int dirF, float zoom, float rotation, bool center, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void DrawCommonShadow(int cmf, int x, int y, int dirF, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void DrawCmfDetailShadow(int cmf, int motion, int x, int y, int dirF, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void DrawEffect(int, int, int, int, float rotation, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void DrawNeutral(int, int, int, int, float, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void DrawBgEffect(int, int, int, int, float zoom, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void DrawBgEffectDetail(int, int, int, int, int, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void DrawEmoticon(int type, int icon, int frame, int x, int y, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void PlayerDraw(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void NormalDraw(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void BulletLaserDraw(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void BulletGuidedDraw(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void BulletSateliteDraw(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void BulletHealDraw(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void BulletBoomerangDraw(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void BulletItemDraw(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void EnemyProfileDraw(int x, int y, int enemyIdx, int star, int lv, float zoom, cocos2d::RenderTexture* cvtDest, cocos2d::Layer* cvtLayer, bool buffering);
void EnemyDraw(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void CloudDraw(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void SpiderDraw(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void SkelDraw(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void MachineDraw(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void LaserDraw(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void GhostDraw(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void VanishDraw(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void RegenDraw(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void NeutralDraw(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void DrawShadowPlayer(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
void DrawShadowCommon(OBJECT *, cocos2d::RenderTexture*, cocos2d::Layer*, bool);
int GetTypeFromCmf(int cmf);
int GetDistanceTile(OBJECT* pObj, int dist);
void DianaStoneMove(OBJECT* pObj);

#endif