#pragma once
// BattleMobileCastle.h
// Manages the Mobile Fortress Battle Scene in MD_PLAY:
// - Left: Player's Modular Mobile Castle (1~10 floors, drawn via CastlePartsDrawRect)
// - Hero (Robin) and active party members stationed on the castle terraces, facing right
// - Mounted guardian swords from the bag and shimmering Aegis barrier on castle walls
// - Road & Swamp parallax background via StageBg
// - Realtime stage monster (StageRtFoe) standing on the road facing left

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "StageBackground.h"

// Forward declaration of canonical modular castle renderer (defined in CastleModularDebug.h)
void CastlePartsDrawRect(int castleLevel, int x, int yTop, int w, int h);

namespace BattleMobileCastle {

static float s_scrollDist = 0.0f;
static float s_scrollSpeed = 24.0f;
static float s_hitFlash = 0.0f;

inline bool IsMoving() {
	return StageRtAutoOn();
}

inline int VisualGroundY(int layoutGroundY) {
	(void)layoutGroundY;
	return (int)(DY * 0.31f);
}

struct SlotUV { float u, v; };
static const SlotUV kCastleWeaponSlots[10][8] = {
	{ { 0.22f, 0.40f }, { 0.78f, 0.40f }, { 0.35f, 0.60f }, { 0.65f, 0.60f },
	  { 0.50f, 0.30f }, { 0.16f, 0.50f }, { 0.84f, 0.50f }, { 0.50f, 0.80f } },
	{ { 0.20f, 0.42f }, { 0.80f, 0.42f }, { 0.34f, 0.58f }, { 0.66f, 0.58f },
	  { 0.50f, 0.32f }, { 0.15f, 0.52f }, { 0.85f, 0.52f }, { 0.50f, 0.78f } },
	{ { 0.18f, 0.45f }, { 0.82f, 0.45f }, { 0.30f, 0.55f }, { 0.70f, 0.55f },
	  { 0.50f, 0.34f }, { 0.15f, 0.54f }, { 0.85f, 0.54f }, { 0.50f, 0.75f } },
	{ { 0.18f, 0.48f }, { 0.82f, 0.48f }, { 0.30f, 0.55f }, { 0.70f, 0.55f },
	  { 0.50f, 0.36f }, { 0.14f, 0.56f }, { 0.86f, 0.56f }, { 0.50f, 0.72f } },
	{ { 0.18f, 0.50f }, { 0.82f, 0.50f }, { 0.30f, 0.56f }, { 0.70f, 0.56f },
	  { 0.50f, 0.38f }, { 0.14f, 0.58f }, { 0.86f, 0.58f }, { 0.50f, 0.70f } },
	{ { 0.18f, 0.52f }, { 0.82f, 0.52f }, { 0.30f, 0.58f }, { 0.70f, 0.58f },
	  { 0.50f, 0.40f }, { 0.14f, 0.60f }, { 0.86f, 0.60f }, { 0.50f, 0.70f } },
	{ { 0.18f, 0.52f }, { 0.82f, 0.52f }, { 0.30f, 0.58f }, { 0.70f, 0.58f },
	  { 0.50f, 0.40f }, { 0.14f, 0.60f }, { 0.86f, 0.60f }, { 0.50f, 0.70f } },
	{ { 0.16f, 0.54f }, { 0.84f, 0.54f }, { 0.28f, 0.60f }, { 0.72f, 0.60f },
	  { 0.50f, 0.42f }, { 0.12f, 0.62f }, { 0.88f, 0.62f }, { 0.50f, 0.70f } },
	{ { 0.15f, 0.55f }, { 0.85f, 0.55f }, { 0.28f, 0.62f }, { 0.72f, 0.62f },
	  { 0.50f, 0.42f }, { 0.12f, 0.64f }, { 0.88f, 0.64f }, { 0.50f, 0.70f } },
	{ { 0.15f, 0.55f }, { 0.85f, 0.55f }, { 0.28f, 0.62f }, { 0.72f, 0.62f },
	  { 0.50f, 0.42f }, { 0.12f, 0.64f }, { 0.88f, 0.64f }, { 0.50f, 0.70f } },
};

inline int GetSwordColor(int detail) {
	switch (detail) {
	case 10: return 0xE0603C;
	case 11: return 0x4FA3D9;
	case 21: return 0xD9A441;
	case 23: return 0x8A4787;
	}
	return 0xDFD9C0;
}

inline void Update(float delta) {
	if (!std::isfinite(delta) || delta <= 0.0f) return;
	const float dt = (delta > 0.1f) ? 0.1f : delta;
	const bool moving = IsMoving();
	const float currentSpeed = moving ? s_scrollSpeed * (float)_2X : 0.0f;
	if (moving) s_scrollDist += currentSpeed * dt;

	if (s_hitFlash > 0.0f) s_hitFlash = Max(0.0f, s_hitFlash - dt * 3.0f);

	StageBg::SetRegionForStage(robin.stage);
	StageBg::Update(dt, moving);
}

inline void DrawBackground(int groundY, int invenTop) {
	StageBg::Draw(groundY, invenTop);
}

inline void DrawInventoryCastleReflections(int castleIdx, float castleLeft, float castleTop,
                                          float naturalW, float naturalH, float scale) {
	StageSword invenSwords[16];
	const int swordCnt = GridTestSwords(invenSwords, 16);
	const int clampedCastle = Max(0, Min(castleIdx, 9));

	for (int s = 0; s < swordCnt && s < 8; ++s) {
		const SlotUV& slot = kCastleWeaponSlots[clampedCastle][s];
		const float wx = castleLeft + slot.u * naturalW * scale;
		const float wy = castleTop - slot.v * naturalH * scale;
		const int swordColor = GetSwordColor(invenSwords[s].detail);

		const float bobY = std::sin((float)frame * 0.10f + (float)s * 1.2f) * 2.5f * (float)_2X;

		MemRect((int)(wx - 4 * _2X), (int)(wy + 2 * _2X), 8 * _2X, 5 * _2X, 0x2A2420);
		MemRectFrame((int)(wx - 4 * _2X), (int)(wy + 2 * _2X), 8 * _2X, 5 * _2X, 0x584A3E);

		const int bladeH = (int)(20.0f * (float)_2X * (scale / 0.5f));
		const int bladeW = 3 * _2X;
		const int bladeY = (int)(wy + bobY - 4 * _2X);

		MemRect((int)(wx - bladeW), bladeY, bladeW * 2, bladeH, swordColor);
		MemRect((int)(wx - 1 * _2X), bladeY - 2 * _2X, 2 * _2X, bladeH - 4 * _2X, 0xFFFFFF);
		MemRect((int)(wx - 5 * _2X), (int)(bladeY - bladeH + 4 * _2X), 10 * _2X, 2 * _2X, 0xD4A034);
		MemRect((int)(wx - 2 * _2X), (int)(bladeY - bladeH + 2 * _2X), 4 * _2X, 4 * _2X, 0x483218);
	}

	const int totalItems = GridTestTotalItemCount();
	if (totalItems > swordCnt) {
		const int barrierAlpha = 12 + (int)(std::sin((float)frame * 0.08f) * 6.0f);
		SetAlpha(barrierAlpha);
		const int pad = 8 * _2X;
		MemRectFrame((int)(castleLeft - pad), (int)(castleTop + pad),
		             (int)(naturalW * scale + pad * 2),
		             (int)(naturalH * scale + pad * 2), 0x50C8FF);
		MemRectFrame((int)(castleLeft - pad + 1), (int)(castleTop + pad - 1),
		             (int)(naturalW * scale + pad * 2 - 2),
		             (int)(naturalH * scale + pad * 2 - 2), 0x99EEFF);
		SetAlpha(32);
	}
}

inline void DrawCastle(int groundY) {
	const int curCastle = Max(0, Min((int)robin.castle, 9));
	const int floorCount = curCastle + 1;
	const float lowerH = curCastle < 6 ? 104.0f : 240.0f;
	const float naturalW = curCastle == 0 ? 672.0f : 512.0f;
	const float naturalH = (float)floorCount * 128.0f + lowerH;

	const float castleW = 150.0f * (float)_2X;
	const float scale = castleW / naturalW;
	const float castleH = naturalH * scale;

	const float shudderY = (s_hitFlash > 0.0f) ? ((rand() % 5) - 2) * 1.5f * (float)_2X : 0.0f;
	const float rumbleY = IsMoving() ? (std::sin((float)frame * 0.40f) * 1.0f * (float)_2X) : 0.0f;
	const float castleLeft = 6.0f * (float)_2X;
	const float assemblyBottom = (float)groundY - 9.87f * scale + shudderY + rumbleY;
	const float yTop = assemblyBottom + castleH;

	CastlePartsDrawRect(curCastle + 1, (int)castleLeft, (int)yTop, (int)castleW, (int)castleH);

	DrawInventoryCastleReflections(curCastle, castleLeft, yTop, naturalW, naturalH, scale);

	const float bottom = assemblyBottom + lowerH * scale;
	const float charZoom = DIORAMAZOOM * 0.70f * scale * 512.0f / DX;
	const float heroZoom = ao[ROBIN].zoom * charZoom;
	const float heroX = castleLeft + 256.0f * scale;
	const float heroY = bottom + 14.0f * scale;

	if (ao[ROBIN].active) {
		const int heroMotion = (ao[ROBIN].motion >= 0) ? ao[ROBIN].motion : (PO_C0_N0 + (frame / 4) % 4);
		DrawPlayer(&ao[ROBIN], heroMotion, (int)heroX, (int)heroY, RIGHT, heroZoom, 0.0f, false, true);
	}

	static const struct { float u; int floorOffset; } crewSlots[MAXCREW] = {
		{ 0.28f, 0 }, { 0.72f, 0 }, { 0.35f, 1 }, { 0.65f, 1 }
	};
	for (int i = 0; i < MAXCREW; ++i) {
		const OBJECT* crew = &ao[CREW + i];
		if (!crew->active || crew->dead) continue;
		const int crewFloor = Min(crewSlots[i].floorOffset, curCastle);
		const float cx = castleLeft + crewSlots[i].u * naturalW * scale;
		const float cy = bottom + ((float)crewFloor * 128.0f + 14.0f) * scale;
		DrawCmfDetailShadow(crew->cmf, crew->motion, (int)cx, (int)cy, RIGHT,
			enemyIconZoom[crew->type] * CREWZOOM * LOBBY_CREW_ZOOM_SCALE * 0.90f * charZoom);
	}
}

inline void DrawBossMonster(int groundY) {
	const int foe = StageRtFoe();
	if (foe < 0) return;
	const OBJECT* monster = &ao[foe];
	const float bossX = Min((float)DX - 32 * _2X, 256.0f * _2X);
	DrawCmfDetailShadow(monster->cmf, monster->motion, (int)bossX,
		groundY - 3 * _2X,
		LEFT, enemyIconZoom[monster->type] * 1.75f);
}

inline void Draw(int groundY, int invenTop) {
	groundY = VisualGroundY(groundY) + (int)GetStageWorldLift();
	const int arenaBottom = Max(0, groundY - 85 * _2X);
	SetSectionClip(0, DY, DX, DY - arenaBottom, false);

	DrawBackground(groundY, arenaBottom);
	DrawCastle(groundY);
	DrawBossMonster(groundY);

	UnSectionClip(false);
}

} // namespace BattleMobileCastle
