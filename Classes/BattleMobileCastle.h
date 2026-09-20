#pragma once
// BattleMobileCastle.h
// Manages the Mobile Fortress Battle Scene in MD_PLAY:
// - Castle and Giant Monster stand right above the bottom inventory (GetStageGroundY() = invenTop + 4 * _2X)
// - Greatly enlarged, imposing Mobile Castle (0~9) with heavy siege wheels and rumble
// - Hero (Robin) stationed at the exact lobby castle position (kCastleHeroPos), facing right
// - Inventory items actively reflected on the castle:
//   * Bag swords mounted as enchanted guardian blades along castle crenels/battlements
//   * Swords flash and unleash slash waves during real-time combat
//   * Armor, shields, and rings in the bag generate a shimmering Castle Aegis Barrier & arcane runes
//   * Active party crew members stationed on castle terraces
// - Continuous 4-layer horizontal parallax scrolling background
// - Imposing Giant Boss Monster (1.75x) facing left, hit sparks, damage numbers, and Boss Health HUD

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "CastleWheelManager.h"

namespace BattleMobileCastle {

struct GiantBossDef {
	int enemyType;
	const char* name;
	const char* title;
	float scale;
	int maxHp;
};

static const GiantBossDef kBosses[] = {
	{ ENEMY_GOLEM,      "주인잃은 골렘",      "Lv.99 고대의 수호 골렘",    1.75f, 1000000 },
	{ ENEMY_DARKGIANT,  "그레이트 아머",      "Lv.120 암흑의 거신병",     1.65f, 1500000 },
	{ ENEMY_DRAGON1,    "붉은 화룡",          "Lv.150 진홍의 염제 드래곤", 1.70f, 2000000 },
	{ ENEMY_MAMMOTH,    "프로스트 맘모스",    "Lv.110 혹한의 거수",       1.65f, 1200000 },
	{ ENEMY_MACHINE,    "라이스너",          "Lv.135 마도 결전 병기",    1.70f, 1800000 },
	{ ENEMY_KIMERA,     "마도합성수 키메라",  "Lv.125 융합의 마수",       1.70f, 1400000 },
};
static const int kBossCount = sizeof(kBosses) / sizeof(kBosses[0]);

static int s_curBossIdx = 0;
static float s_bossHp = 1000000.0f;
static float s_bossDisplayHp = 1000000.0f;
static int s_attackTimer = 0;
static float s_hitFlash = 0.0f;

// Continuous horizontal travel distance along the road
static float s_scrollDist = 0.0f;
static float s_scrollSpeed = 75.0f; // px/sec at 1x

// Hero Position on Castle (u: horizontal ratio 0~1, v: vertical ratio from top 0~1)
// Exactly matching the lobby hero positions from Func_Draw.cpp:4218
static const struct { float u, v; } kCastleHeroPos[10] = {
	{ 0.50f, 0.88f }, // Castle 0
	{ 0.50f, 0.90f }, // Castle 1
	{ 0.50f, 0.91f }, // Castle 2
	{ 0.50f, 0.92f }, // Castle 3
	{ 0.50f, 0.93f }, // Castle 4
	{ 0.50f, 0.93f }, // Castle 5
	{ 0.50f, 0.94f }, // Castle 6
	{ 0.50f, 0.94f }, // Castle 7
	{ 0.54f, 0.95f }, // Castle 8
	{ 0.52f, 0.95f }, // Castle 9
};

// Castle Battlement Crenel Slots for Weapons in the inventory
struct SlotUV { float u, v; };
static const SlotUV kCastleWeaponSlots[10][8] = {
	// Castle 0: Circular stone keep (416x448)
	{ { 0.22f, 0.62f }, { 0.78f, 0.62f }, { 0.35f, 0.60f }, { 0.65f, 0.60f },
	  { 0.50f, 0.38f }, { 0.16f, 0.76f }, { 0.84f, 0.76f }, { 0.50f, 0.20f } },
	// Castle 1: 2-Tier Fortress (491x683)
	{ { 0.20f, 0.65f }, { 0.80f, 0.65f }, { 0.34f, 0.56f }, { 0.66f, 0.56f },
	  { 0.50f, 0.38f }, { 0.15f, 0.78f }, { 0.85f, 0.78f }, { 0.50f, 0.22f } },
	// Castle 2: Turret Citadel (507x818)
	{ { 0.18f, 0.68f }, { 0.82f, 0.68f }, { 0.30f, 0.50f }, { 0.70f, 0.50f },
	  { 0.50f, 0.36f }, { 0.15f, 0.80f }, { 0.85f, 0.80f }, { 0.50f, 0.18f } },
	// Castle 3: Spire Bastion (543x943)
	{ { 0.18f, 0.70f }, { 0.82f, 0.70f }, { 0.30f, 0.52f }, { 0.70f, 0.52f },
	  { 0.50f, 0.36f }, { 0.14f, 0.82f }, { 0.86f, 0.82f }, { 0.50f, 0.18f } },
	// Castle 4: Alchemy Stronghold (553x1021)
	{ { 0.18f, 0.70f }, { 0.82f, 0.70f }, { 0.30f, 0.52f }, { 0.70f, 0.52f },
	  { 0.50f, 0.36f }, { 0.14f, 0.82f }, { 0.86f, 0.82f }, { 0.50f, 0.18f } },
	// Castle 5: Clocktower Keep (558x1127)
	{ { 0.18f, 0.72f }, { 0.82f, 0.72f }, { 0.30f, 0.54f }, { 0.70f, 0.54f },
	  { 0.50f, 0.38f }, { 0.14f, 0.84f }, { 0.86f, 0.84f }, { 0.50f, 0.18f } },
	// Castle 6: Archmage Tower (561x1362)
	{ { 0.18f, 0.72f }, { 0.82f, 0.72f }, { 0.30f, 0.54f }, { 0.70f, 0.54f },
	  { 0.50f, 0.38f }, { 0.14f, 0.84f }, { 0.86f, 0.84f }, { 0.50f, 0.18f } },
	// Castle 7: Cathedral Citadel (676x1388)
	{ { 0.16f, 0.72f }, { 0.84f, 0.72f }, { 0.28f, 0.54f }, { 0.72f, 0.54f },
	  { 0.50f, 0.38f }, { 0.12f, 0.84f }, { 0.88f, 0.84f }, { 0.50f, 0.18f } },
	// Castle 8: Grand Royal Palace (781x1481)
	{ { 0.15f, 0.74f }, { 0.85f, 0.74f }, { 0.28f, 0.56f }, { 0.72f, 0.56f },
	  { 0.50f, 0.38f }, { 0.12f, 0.85f }, { 0.88f, 0.85f }, { 0.50f, 0.18f } },
	// Castle 9: Celestial High Fortress (922x1700)
	{ { 0.15f, 0.74f }, { 0.85f, 0.74f }, { 0.28f, 0.56f }, { 0.72f, 0.56f },
	  { 0.50f, 0.38f }, { 0.12f, 0.85f }, { 0.88f, 0.85f }, { 0.50f, 0.18f } },
};

// Combat Projectiles (flying from Mobile Castle to Giant Boss)
struct Projectile {
	float x, y;
	float vx, vy;
	int type; // 0: Arrow, 1: Gunshot tracer, 2: Arcane bolt, 3: Sword slash wave
	int color;
	float life;
	bool active;
};
static const int MAX_PROJECTILES = 20;
static Projectile s_projectiles[MAX_PROJECTILES] = {};

// Floating Damage Numbers
struct DamageText {
	float x, y;
	int damage;
	float life;
	float maxLife;
	bool critical;
	bool active;
};
static const int MAX_DAMAGE_TEXTS = 14;
static DamageText s_damages[MAX_DAMAGE_TEXTS] = {};

inline void NextBoss() {
	s_curBossIdx = (s_curBossIdx + 1) % kBossCount;
	s_bossHp = (float)kBosses[s_curBossIdx].maxHp;
	s_bossDisplayHp = s_bossHp;
	s_hitFlash = 0.0f;
}

inline const GiantBossDef& GetCurrentBoss() {
	return kBosses[s_curBossIdx];
}

inline void SpawnProjectile(float startX, float startY, int type, int color = 0) {
	for (int i = 0; i < MAX_PROJECTILES; ++i) {
		if (!s_projectiles[i].active) {
			s_projectiles[i].active = true;
			s_projectiles[i].x = startX;
			s_projectiles[i].y = startY;
			s_projectiles[i].type = type;
			s_projectiles[i].color = color;
			s_projectiles[i].vx = 8.5f + (float)(rand() % 7) * 0.4f;
			s_projectiles[i].vy = ((float)(rand() % 9) - 4.0f) * 0.15f;
			s_projectiles[i].life = 1.3f;
			break;
		}
	}
}

inline void SpawnDamage(float x, float y, int dmg, bool crit) {
	for (int i = 0; i < MAX_DAMAGE_TEXTS; ++i) {
		if (!s_damages[i].active) {
			s_damages[i].active = true;
			s_damages[i].x = x + (float)((rand() % 17) - 8) * (float)_2X;
			s_damages[i].y = y + (float)((rand() % 25) - 10) * (float)_2X;
			s_damages[i].damage = dmg;
			s_damages[i].critical = crit;
			s_damages[i].maxLife = 0.65f;
			s_damages[i].life = s_damages[i].maxLife;
			break;
		}
	}
}

// Elemental trail colors for swords
inline int GetSwordColor(int detail) {
	switch (detail) {
	case 10: return 0xE0603C; // Flame - Red
	case 11: return 0x4FA3D9; // Ice - Blue
	case 21: return 0xD9A441; // Excalibur - Gold
	case 23: return 0x8A4787; // Dark - Purple
	}
	return 0xDFD9C0; // Silver
}

// Per-frame physics and combat update
inline void Update(float delta) {
	if (!std::isfinite(delta) || delta <= 0.0f) return;
	const float dt = (delta > 0.1f) ? 0.1f : delta;

	// 1. Advance horizontal road travel distance
	const float currentSpeed = s_scrollSpeed * (float)_2X;
	s_scrollDist += currentSpeed * dt;

	// Scale for wheel rotation
	const float castleScale = 0.65f;
	CastleWheels::Update(s_scrollDist, dt, currentSpeed, castleScale);

	// 2. Smooth Boss HP easing
	if (s_bossDisplayHp > s_bossHp) {
		s_bossDisplayHp -= (s_bossDisplayHp - s_bossHp) * 0.08f;
	} else if (s_bossDisplayHp < s_bossHp) {
		s_bossDisplayHp = s_bossHp;
	}

	if (s_hitFlash > 0.0f) {
		s_hitFlash -= dt * 3.5f;
		if (s_hitFlash < 0.0f) s_hitFlash = 0.0f;
	}

	// 3. Castle defense projectile firing loop
	s_attackTimer++;
	const float castleRightX = 14.0f * (float)_2X + 270.0f * (float)_2X * 0.65f;
	const float castleCenterY = (float)GetStageGroundY() + 100.0f * (float)_2X;
	const float bossTargetX = (float)DX - 110.0f * (float)_2X;

	// Read swords in the inventory to fire active battlements slashes!
	StageSword invenSwords[16];
	const int swordCnt = GridTestSwords(invenSwords, 16);

	if (s_attackTimer % 24 == 0) {
		// Robin hero attack volley
		SpawnProjectile(castleRightX - 10.0f * (float)_2X, castleCenterY + 20.0f * (float)_2X, 0);
	}
	if (s_attackTimer % 38 == 12) {
		// Castle gunner / turret tracer
		SpawnProjectile(castleRightX - 15.0f * (float)_2X, castleCenterY - 10.0f * (float)_2X, 1);
	}
	if (swordCnt > 0 && (s_attackTimer % 32 == 16)) {
		// Mounted inventory sword slash wave
		const int sIdx = (s_attackTimer / 32) % swordCnt;
		const int sColor = GetSwordColor(invenSwords[sIdx].detail);
		SpawnProjectile(castleRightX - 5.0f * (float)_2X, castleCenterY + 45.0f * (float)_2X, 3, sColor);
	}

	// 4. Update flying projectiles
	for (int i = 0; i < MAX_PROJECTILES; ++i) {
		if (!s_projectiles[i].active) continue;
		s_projectiles[i].x += s_projectiles[i].vx * (float)_2X * (dt * 60.0f);
		s_projectiles[i].y += s_projectiles[i].vy * (float)_2X * (dt * 60.0f);
		s_projectiles[i].life -= dt;

		// Impact on Giant Monster body
		if (s_projectiles[i].x >= bossTargetX - 22.0f * (float)_2X || s_projectiles[i].life <= 0.0f) {
			s_projectiles[i].active = false;
			if (s_projectiles[i].x >= bossTargetX - 50.0f * (float)_2X) {
				const bool crit = (rand() % 4 == 0);
				const int dmg = crit ? (16500 + rand() % 9800) : (6800 + rand() % 4200);
				s_bossHp -= (float)dmg;
				s_hitFlash = 0.55f;

				if (s_bossHp <= 100000.0f) {
					NextBoss();
				}
				SpawnDamage(bossTargetX - 15.0f * (float)_2X, s_projectiles[i].y, dmg, crit);
			}
		}
	}

	// 5. Update floating damage numbers
	for (int i = 0; i < MAX_DAMAGE_TEXTS; ++i) {
		if (!s_damages[i].active) continue;
		s_damages[i].y += 0.85f * (float)_2X * (dt * 60.0f);
		s_damages[i].life -= dt;
		if (s_damages[i].life <= 0.0f) {
			s_damages[i].active = false;
		}
	}
}

// 4-Layer Continuous Horizontal Parallax Background
inline void DrawBackground(int groundY, int invenTop) {
	// Base atmospheric fill for the battle sky
	SetAlpha(32);
	MemRect(0, DY, DX, DY - invenTop, 0x1A1E2E);

	// Layer 1: Distant Mountains / Sky Landscape (slow parallax ~0.15x)
	const int bgImg = LOBBY_LANDSCAPE_IMG;
	if (!sprite[bgImg]) LoadImg(bgImg);
	if (sprite[bgImg]) {
		const auto sz = sprite[bgImg]->getContentSize();
		const float zoom = (float)DX / sz.width;
		const float tileW = sz.width * zoom;
		const float offX = -std::fmod(s_scrollDist * 0.15f, tileW);
		const int topY = DY;

		for (float x = offX; x < (float)DX; x += tileW) {
			DrawImage((int)sz.width, (int)sz.height, 0, 0, (int)x, topY,
			          false, false, false, false, false, zoom, sprite[bgImg], bgImg);
		}
	}

	// Layer 2: Drifting Atmosphere Clouds (parallax ~0.35x + wind)
	const int cloudImg = LOBBY_CLOUD_IMG;
	if (!sprite[cloudImg]) LoadImg(cloudImg);
	if (sprite[cloudImg]) {
		const auto sz = sprite[cloudImg]->getContentSize();
		const float zoom = 1.0f * (float)_2X;
		const float tileW = sz.width * zoom;
		const float offX = -std::fmod(s_scrollDist * 0.35f + (float)frame * 0.25f, tileW);
		const int cloudY = DY - 30 * _2X;

		SetAlpha(22);
		for (float x = offX; x < (float)DX; x += tileW) {
			DrawImage((int)sz.width, (int)sz.height, 0, 0, (int)x, cloudY,
			          false, false, false, false, false, zoom, sprite[cloudImg], cloudImg);
		}
		SetAlpha(32);
	}

	// Layer 3: Midground Foothills / Hills (mid parallax ~0.55x)
	const int footImg = LOBBY_FOOTHILLS_IMG;
	if (!sprite[footImg]) LoadImg(footImg);
	if (sprite[footImg]) {
		const auto sz = sprite[footImg]->getContentSize();
		const float zoom = (float)DX / sz.width;
		const float tileW = sz.width * zoom;
		const float offX = -std::fmod(s_scrollDist * 0.55f, tileW);
		const int footY = groundY + (int)(sz.height * zoom * 0.85f);

		for (float x = offX; x < (float)DX; x += tileW) {
			DrawImage((int)sz.width, (int)sz.height, 0, 0, (int)x, footY,
			          false, false, false, false, false, zoom, sprite[footImg], footImg);
		}
	}

	// Layer 4: Battlefield Road / Ground Bed (1.0x scroll speed along groundY)
	// GroundY is placed right above the bottom inventory (invenTop + 4 * _2X)
	const int roadImg = BATTLE_BG_BOTTOM_IMG;
	if (!sprite[roadImg]) LoadImg(roadImg);
	if (sprite[roadImg]) {
		const auto sz = sprite[roadImg]->getContentSize();
		const float zoom = GetStageGroundZoom();
		const float tileW = sz.width * zoom;
		const float offX = -std::fmod(s_scrollDist, tileW);
		const int topY = groundY + (int)(sz.height * zoom * 0.40f);

		for (float x = offX; x < (float)DX; x += tileW) {
			DrawImage((int)sz.width, (int)sz.height, 0, 0, (int)x, topY,
			          false, false, false, false, false, zoom, sprite[roadImg], roadImg);
		}
	}
}

// Renders inventory items reflected onto the castle
inline void DrawInventoryCastleReflections(int castleIdx, float castleLeft, float castleTop,
                                          float castleW, float castleH, float castleScale) {
	// 1. Swords from the inventory mounted on castle crenels/turrets!
	StageSword invenSwords[16];
	const int swordCnt = GridTestSwords(invenSwords, 16);
	const int clampedCastle = Max(0, Min(castleIdx, 9));

	for (int s = 0; s < swordCnt && s < 8; ++s) {
		const SlotUV& slot = kCastleWeaponSlots[clampedCastle][s];
		const float wx = castleLeft + slot.u * castleW * castleScale;
		const float wy = castleTop - slot.v * castleH * castleScale;
		const int swordColor = GetSwordColor(invenSwords[s].detail);

		// Subtle vertical levitation bobbing
		const float bobY = std::sin((float)frame * 0.10f + (float)s * 1.2f) * 2.5f * (float)_2X;

		// Weapon Battlement Bracket
		MemRect((int)(wx - 4 * _2X), (int)(wy + 2 * _2X), 8 * _2X, 5 * _2X, 0x2A2420);
		MemRectFrame((int)(wx - 4 * _2X), (int)(wy + 2 * _2X), 8 * _2X, 5 * _2X, 0x584A3E);

		// Enchanted Guardian Sword Blade floating upright on castle rampart
		const int bladeH = (int)(22.0f * (float)_2X * (castleScale / 0.45f));
		const int bladeW = 3 * _2X;
		const int bladeY = (int)(wy + bobY - 4 * _2X);

		// Glowing elemental aura
		MemRect((int)(wx - bladeW), bladeY, bladeW * 2, bladeH, swordColor);
		MemRect((int)(wx - 1 * _2X), bladeY - 2 * _2X, 2 * _2X, bladeH - 4 * _2X, 0xFFFFFF); // Bright core
		// Crossguard
		MemRect((int)(wx - 5 * _2X), (int)(bladeY - bladeH + 4 * _2X), 10 * _2X, 2 * _2X, 0xD4A034);
		// Hilt / Pommel
		MemRect((int)(wx - 2 * _2X), (int)(bladeY - bladeH + 2 * _2X), 4 * _2X, 4 * _2X, 0x483218);
	}

	// 2. Fortification Barrier: When defensive gear (armor, shields, rings) is in the bag
	const int totalItems = GridTestTotalItemCount();
	if (totalItems > swordCnt) {
		// Shimmering translucent Castle Aegis Shield
		const int barrierAlpha = 12 + (int)(std::sin((float)frame * 0.08f) * 6.0f);
		SetAlpha(barrierAlpha);
		const int pad = 8 * _2X;
		MemRectFrame((int)(castleLeft - pad), (int)(castleTop + pad),
		             (int)(castleW * castleScale + pad * 2),
		             (int)(castleH * castleScale + pad * 2), 0x50C8FF);
		MemRectFrame((int)(castleLeft - pad + 1), (int)(castleTop + pad - 1),
		             (int)(castleW * castleScale + pad * 2 - 2),
		             (int)(castleH * castleScale + pad * 2 - 2), 0x99EEFF);
		SetAlpha(32);
	}
}

// Greatly enlarged Mobile Castle with wheels and Hero stationed at lobby position
inline void DrawCastle(int groundY) {
	const int castleIdx = castleOrder[robin.castle];
	const int castleImg = MAP_DIORAMA_IMG + castleIdx;
	if (!sprite[castleImg]) LoadImg(castleImg);
	if (!sprite[castleImg]) return;

	const auto sz = sprite[castleImg]->getContentSize();
	const float rawW = sz.width;
	const float rawH = sz.height;

	// Greatly enlarged castle scale: dynamic fit up to ~0.65x
	const float maxH = (float)(DY - groundY - 45 * _2X);
	float scale = Min(0.65f, maxH / rawH);
	if (scale < 0.32f) scale = 0.32f;

	const float castleLeft = 14.0f * (float)_2X;
	const float wheelRadius = CastleWheels::GetWheelRadius(scale);
	const float suspensionY = CastleWheels::GetSuspensionY();
	const float castleBottom = (float)groundY + wheelRadius * 1.4f + suspensionY;
	const float castleTop = castleBottom + rawH * scale;

	// 1. Castle Body Ground Shadow
	ShadowImage((int)(rawW * scale * 1.05f), 18 * _2X, 1 * _2X, 1 * _2X,
	            (int)(castleLeft - 4 * _2X),
	            (int)(groundY + 8 * _2X),
	            SHADOW_IMG, scale * 1.15f);

	// 2. Castle Sprite
	DrawImage((int)rawW, (int)rawH, 0, 0,
	          (int)castleLeft, (int)castleTop,
	          false, false, false, false, false, scale,
	          sprite[castleImg], castleImg);

	// 3. Castle Chassis Wheels with Physical Rotation & Dust Emitter
	CastleWheels::DrawCastleWheels(robin.castle, castleLeft, castleBottom,
	                              rawW, scale, (float)groundY, true);

	// 4. Inventory items reflected on the castle (Mounted weapons & Aegis shield)
	DrawInventoryCastleReflections(castleIdx, castleLeft, castleTop, rawW, rawH, scale);

	// 5. Hero (Robin) stationed at the exact lobby castle position (kCastleHeroPos), facing RIGHT!
	const int curCastle = Max(0, Min(robin.castle, 9));
	const float heroU = kCastleHeroPos[curCastle].u;
	const float heroV = kCastleHeroPos[curCastle].v;
	const float heroX = castleLeft + heroU * rawW * scale;
	const float heroY = castleTop - heroV * rawH * scale;
	const float heroZoom = HEROZOOM * (scale / 0.35f) * 0.70f;

	if (ao[ROBIN].active) {
		const int heroMotion = (ao[ROBIN].motion >= 0) ? ao[ROBIN].motion : (PO_C0_N0 + (frame / 4) % 4);
		DrawPlayer(&ao[ROBIN], heroMotion, (int)heroX, (int)heroY, RIGHT, heroZoom, 0.0f, false, true);
	}
}

// Giant Boss Monster on the right facing left, right above bottom inventory
inline void DrawBossMonster(int groundY) {
	const GiantBossDef& def = kBosses[s_curBossIdx];
	const int cmf = enemyData[def.enemyType * ENEMYDATASIZE + ENEMYDATA_CMF];
	const int idleStart = crewPos[def.enemyType * 5 + 0];
	const int idleCount = Max(1, (int)crewPos[def.enemyType * 5 + 1]);

	// Idle breathing animation
	const int motion = idleStart + ((frame / 6) % idleCount);
	const float breatheY = std::sin((float)frame * 0.08f) * 2.5f * (float)_2X;
	const float bossX = (float)DX - 110.0f * (float)_2X;
	const float finalY = (float)groundY + breatheY;

	// Render Giant Boss facing LEFT towards the Mobile Castle
	DrawCmfDetailShadow(cmf, motion, (int)bossX, (int)finalY, LEFT, def.scale);

	// Hit spark flash when taking damage
	if (s_hitFlash > 0.0f) {
		const int sparkX = (int)(bossX - 18.0f * (float)_2X);
		const int sparkY = (int)(finalY + 45.0f * (float)_2X);
		MemRect(sparkX - 8 * _2X, sparkY + 8 * _2X, 16 * _2X, 16 * _2X, 0xFFE080);
		MemRectFrame(sparkX - 14 * _2X, sparkY + 14 * _2X, 28 * _2X, 28 * _2X, 0xFF8820);
	}
}

// In-flight Combat Projectiles (arrows, gunfire tracers, arcane bolts, slash waves)
inline void DrawProjectiles() {
	for (int i = 0; i < MAX_PROJECTILES; ++i) {
		if (!s_projectiles[i].active) continue;
		const int px = (int)s_projectiles[i].x;
		const int py = (int)s_projectiles[i].y;

		if (s_projectiles[i].type == 0) {
			// Arrow: wooden shaft with bright tip
			MemRect(px - 7 * _2X, py, 14 * _2X, 2 * _2X, 0xC49A45);
			MemRect(px + 5 * _2X, py + 1 * _2X, 5 * _2X, 4 * _2X, 0xFFFFFF);
		} else if (s_projectiles[i].type == 1) {
			// Gunshot: glowing fiery tracer
			MemRect(px - 10 * _2X, py, 18 * _2X, 3 * _2X, 0xFFAA33);
			MemRect(px + 3 * _2X, py + 1 * _2X, 8 * _2X, 4 * _2X, 0xFFFF88);
		} else if (s_projectiles[i].type == 2) {
			// Arcane Magic Bolt: glowing sphere with core
			MemRect(px - 5 * _2X, py + 5 * _2X, 10 * _2X, 10 * _2X, 0x9944FF);
			MemRect(px - 2 * _2X, py + 2 * _2X, 4 * _2X, 4 * _2X, 0x88FFFF);
		} else {
			// Sword Slash Wave from mounted inventory blade
			const int col = (s_projectiles[i].color != 0) ? s_projectiles[i].color : 0xDFD9C0;
			MemRect(px - 12 * _2X, py + 6 * _2X, 24 * _2X, 12 * _2X, col);
			MemRect(px - 6 * _2X, py + 3 * _2X, 12 * _2X, 6 * _2X, 0xFFFFFF);
		}
	}
}

// Floating Combat Damage Numbers
inline void DrawDamageTexts() {
	char numStr[32];
	for (int i = 0; i < MAX_DAMAGE_TEXTS; ++i) {
		if (!s_damages[i].active) continue;
		sprintf(numStr, "%d", s_damages[i].damage);
		if (s_damages[i].critical) {
			SetFontColor(COLOR_YELLOW);
			CenterTextStrSolid(numStr, (int)s_damages[i].x, (int)s_damages[i].y, 0.65f);
		} else {
			SetFontColor(COLOR_WHITE);
			CenterTextStrSolid(numStr, (int)s_damages[i].x, (int)s_damages[i].y, 0.52f);
		}
	}
}

// Top-Right Boss Health Bar HUD
inline void DrawBossUI() {
	const GiantBossDef& def = kBosses[s_curBossIdx];

	const int barW = 180 * _2X;
	const int barH = 24 * _2X;
	const int barX = DX - barW - 12 * _2X;
	const int barY = DY - GNBHEIGHT - 4 * _2X;

	// Dark ornate frame background
	MemRect(barX, barY, barW, barH, 0x141018);
	MemRectFrame(barX, barY, barW, barH, 0x5C1A1A);
	MemRectFrame(barX + 1, barY - 1, barW - 2, barH - 2, 0x8A2A2A);

	// Boss Subtitle & Title
	char titleBuf[64];
	sprintf(titleBuf, "[RAID BOSS] %s", def.name);
	SetFontColor(0xFF6666);
	CenterTextStrSolid(titleBuf, barX + barW / 2, barY - 3 * _2X, 0.38f);

	// Health bar slot
	const int innerX = barX + 6 * _2X;
	const int innerY = barY - 12 * _2X;
	const int innerW = barW - 12 * _2X;
	const int innerH = 7 * _2X;

	MemRect(innerX, innerY, innerW, innerH, 0x2E0B0B);

	// Eased Health Meter
	const float fillRatio = Max(0.0f, Min(1.0f, s_bossDisplayHp / (float)def.maxHp));
	const int fillW = (int)((float)innerW * fillRatio);

	if (fillW > 0) {
		MemRect(innerX, innerY, fillW, innerH, 0xD42222);
		MemRect(innerX, innerY, fillW, 2 * _2X, 0xFF6666);
		MemRectFrame(innerX, innerY, fillW, innerH, 0xFF9944);
	}
}

// Main Entry Point for MD_PLAY in DrawDiorama
inline void Draw(int groundY, int invenTop) {
	// Clip strictly to the upper battle arena so lower inventory is preserved
	SetSectionClip(0, DY, DX, DY - invenTop, false);

	DrawBackground(groundY, invenTop);
	DrawCastle(groundY);
	DrawBossMonster(groundY);
	DrawProjectiles();
	DrawDamageTexts();
	DrawBossUI();

	UnSectionClip(false);
}

} // namespace BattleMobileCastle
