#pragma once

#ifndef _FUNC_OBJECT_H_
#define _FUNC_OBJECT_H_

// Object 그리기 관련
void GetMotionPtr(OBJECT* pObj);
void EraseCmf(OBJECT *);
void DrawObj(OBJECT *);
void DrawPlayer(OBJECT *, int motion, int x, int y, int dirF, float zoom, float rotation, bool center, bool shadow);
void DrawPlayerIcon(int, int, int, int);
void DrawCmf(OBJECT *pObj, float rotation, float zoom, bool center);
void DrawCmfDetail(int cmf, int motion, int x, int y, int dirF, float zoom, float rotation, bool center);
void DrawCommonShadow(int cmf, int x, int y, int dirF, float zoom);
void DrawCmfDetailShadow(int cmf, int motion, int x, int y, int dirF, float zoom);
void DrawEffect(int, int, int, int, float rotation, float zoom);
void DrawNeutral(int idx, int x, int y, int dirF, float zoom);
void DrawBgEffect(int, int, int, int, float zoom);
void DrawBgEffectDetail(int, int, int, int, int);
void DrawEmoticon(int type, int icon, int frame, int x, int y, float zoom);
void PlayerDraw(OBJECT *);
void NormalDraw(OBJECT *);
void BulletLaserDraw(OBJECT *);
void BulletGuidedDraw(OBJECT *);
void BulletSateliteDraw(OBJECT *);
void BulletHealDraw(OBJECT *);
void BulletBoomerangDraw(OBJECT *);
void BulletItemDraw(OBJECT *);
void BulletCrewDraw(OBJECT* pObj);
void EnemyProfileDraw(int x, int y, int enemyIdx, int star, int lv, float zoom);
void EnemyDraw(OBJECT *);
void CloudDraw(OBJECT *);
void SpiderDraw(OBJECT *);
void SkelDraw(OBJECT *);
void MachineDraw(OBJECT *);
void LaserDraw(OBJECT *);
void GhostDraw(OBJECT *);
void VanishDraw(OBJECT *);
void RegenDraw(OBJECT *);
void NeutralDraw(OBJECT *);
void DrawShadowPlayer(OBJECT *);
void DrawShadowCommon(OBJECT *);
int GetTypeFromCmf(int cmf);
int GetDistanceTile(OBJECT* pObj, int dist);
void DianaStoneMove(OBJECT* pObj);

#endif