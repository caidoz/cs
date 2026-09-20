#pragma once
// BattleMobileCastle.h
// Manages the Mobile Fortress Battle Scene in MD_PLAY:
// - Continuous horizontal parallax scrolling background (landscape, clouds, foothills, road)
// - Scaled Mobile Castle (0~9) with attached rotating wheels, suspension rumble, and dust particles
// - Giant Enemy Monster positioned on the right facing left in real-time combat
// - Projectiles (arrows, bullets, magic bolts), impact sparks, damage numbers, and Boss HP HUD
// - Viewport clipping ensuring the lower bag inventory remains 100% pristine and functional

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
	{ ENEMY_GOLEM,      "주인잃은 골렘",      "Lv.99 고대의 수호 골렘",    1.40f, 1000000 },
	{ ENEMY_DARKGIANT,  "그레이트 아머",      "Lv.120 암흑의 거신병",     1.30f, 1500000 },
	{ ENEMY_DRAGON1,    "붉은 화룡",          "Lv.150 진홍의 염제 드래곤", 1.35f, 2000000 },
	{ ENEMY_MAMMOTH,    "프로스트 맘모스",    "Lv.110 혹한의 거수",       1.30f, 1200000 },
	{ ENEMY_MACHINE,    "라이스너",          "Lv.135 마도 결전 병기",    1.35f, 1800000 },
	{ ENEMY_KIMERA,     "마도합성수 키메라",  "Lv.125 융합의 마수",       1.35f, 1400000 },
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

// Combat Projectiles (flying from Mobile Castle to Giant Boss)
struct Projectile {
	float x, y;
	float vx, vy;
	int type; // 0: Arrow, 1: Gunshot tracer, 2: Arcane bolt
	float life;
	bool active;
};
static const int MAX_PROJECTILES = 16;
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
static const int MAX_DAMAGE_TEXTS = 12;
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

inline void SpawnProjectile(float startX, float startY, int type) {
	for (int i = 0; i < MAX_PROJECTILES; ++i) {
		if (!s_projectiles[i].active) {
			s_projectiles[i].active = true;
			s_projectiles[i].x = startX;
			s_projectiles[i].y = startY;
			s_projectiles[i].type = type;
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

// Per-frame physics and combat update
inline void Update(float delta) {
	if (!std::isfinite(delta) || delta <= 0.0f) return;
	const float dt = (delta > 0.1f) ? 0.1f : delta;

	// 1. Advance horizontal road travel distance
	const float currentSpeed = s_scrollSpeed * (float)_2X;
	s_scrollDist += currentSpeed * dt;

	// Calculate approximate castle scale for wheel physics
	const float castleScale = 0.35f;
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
	const float castleRightX = 14.0f * (float)_2X + 180.0f * (float)_2X * 0.35f;
	const float castleCenterY = (float)GetStageGroundY() + 60.0f * (float)_2X;
	const float bossTargetX = (float)DX - 95.0f * (float)_2X;

	if (s_attackTimer % 26 == 0) {
		// Archer/Robin volley
		SpawnProjectile(castleRightX - 5.0f * (float)_2X, castleCenterY + 18.0f * (float)_2X, 0);
	}
	if (s_attackTimer % 42 == 14) {
		// Gunner/Diana firearm burst
		SpawnProjectile(castleRightX - 12.0f * (float)_2X, castleCenterY - 6.0f * (float)_2X, 1);
	}
	if (s_attackTimer % 64 == 32) {
		// Mage tower arcane orb
		SpawnProjectile(castleRightX - 20.0f * (float)_2X, castleCenterY + 42.0f * (float)_2X, 2);
	}

	// 4. Update flying projectiles
	for (int i = 0; i < MAX_PROJECTILES; ++i) {
		if (!s_projectiles[i].active) continue;
		s_projectiles[i].x += s_projectiles[i].vx * (float)_2X * (dt * 60.0f);
		s_projectiles[i].y += s_projectiles[i].vy * (float)_2X * (dt * 60.0f);
		s_projectiles[i].life -= dt;

		// Impact on Giant Monster body
		if (s_projectiles[i].x >= bossTargetX - 18.0f * (float)_2X || s_projectiles[i].life <= 0.0f) {
			s_projectiles[i].active = false;
			if (s_projectiles[i].x >= bossTargetX - 45.0f * (float)_2X) {
				const bool crit = (rand() % 4 == 0);
				const int dmg = crit ? (14000 + rand() % 9500) : (5200 + rand() % 3600);
				s_bossHp -= (float)dmg;
				s_hitFlash = 0.5f;

				if (s_bossHp <= 100000.0f) {
					NextBoss();
				}
				SpawnDamage(bossTargetX - 12.0f * (float)_2X, s_projectiles[i].y, dmg, crit);
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
	// Base dark atmospheric fill for the battle sky
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
	const int roadImg = BATTLE_BG_BOTTOM_IMG;
	if (!sprite[roadImg]) LoadImg(roadImg);
	if (sprite[roadImg]) {
		const auto sz = sprite[roadImg]->getContentSize();
		const float zoom = GetStageGroundZoom();
		const float tileW = sz.width * zoom;
		const float offX = -std::fmod(s_scrollDist, tileW);
		const int topY = groundY + (int)(sz.height * zoom * 0.5f);

		for (float x = offX; x < (float)DX; x += tileW) {
			DrawImage((int)sz.width, (int)sz.height, 0, 0, (int)x, topY,
			          false, false, false, false, false, zoom, sprite[roadImg], roadImg);
		}
	}
}

// Scaled Mobile Castle on the left with wheels attached
inline void DrawCastle(int groundY) {
	const int castleIdx = castleOrder[robin.castle];
	const int castleImg = MAP_DIORAMA_IMG + castleIdx;
	if (!sprite[castleImg]) LoadImg(castleImg);
	if (!sprite[castleImg]) return;

	const auto sz = sprite[castleImg]->getContentSize();
	const float rawW = sz.width;
	const float rawH = sz.height;

	// Scale down castle so it fits comfortably within the upper arena
	const float maxH = (float)(DY - groundY - 35 * _2X);
	float scale = Min(0.35f, maxH / rawH);
	if (scale < 0.22f) scale = 0.22f;

	const float castleLeft = 14.0f * (float)_2X;
	const float wheelRadius = CastleWheels::GetWheelRadius(scale);
	const float suspensionY = CastleWheels::GetSuspensionY();
	const float castleBottom = (float)groundY + wheelRadius * 1.5f + suspensionY;
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
}

// Giant Boss Monster on the right facing left
inline void DrawBossMonster(int groundY) {
	const GiantBossDef& def = kBosses[s_curBossIdx];
	const int cmf = enemyData[def.enemyType * ENEMYDATASIZE + ENEMYDATA_CMF];
	const int idleStart = crewPos[def.enemyType * 5 + 0];
	const int idleCount = Max(1, (int)crewPos[def.enemyType * 5 + 1]);

	// Idle breathing animation
	const int motion = idleStart + ((frame / 6) % idleCount);
	const float breatheY = std::sin((float)frame * 0.08f) * 2.5f * (float)_2X;
	const float bossX = (float)DX - 95.0f * (float)_2X;
	const float finalY = (float)groundY + breatheY;

	// Render Giant Boss facing LEFT towards the Mobile Castle
	DrawCmfDetailShadow(cmf, motion, (int)bossX, (int)finalY, LEFT, def.scale);

	// Hit spark flash when taking damage
	if (s_hitFlash > 0.0f) {
		const int sparkX = (int)(bossX - 15.0f * (float)_2X);
		const int sparkY = (int)(finalY + 32.0f * (float)_2X);
		MemRect(sparkX - 6 * _2X, sparkY + 6 * _2X, 12 * _2X, 12 * _2X, 0xFFE080);
		MemRectFrame(sparkX - 10 * _2X, sparkY + 10 * _2X, 20 * _2X, 20 * _2X, 0xFF8820);
	}
}

// In-flight Combat Projectiles (arrows, gunfire tracers, arcane bolts)
inline void DrawProjectiles() {
	for (int i = 0; i < MAX_PROJECTILES; ++i) {
		if (!s_projectiles[i].active) continue;
		const int px = (int)s_projectiles[i].x;
		const int py = (int)s_projectiles[i].y;

		if (s_projectiles[i].type == 0) {
			// Arrow: wooden shaft with bright tip
			MemRect(px - 6 * _2X, py, 12 * _2X, 2 * _2X, 0xC49A45);
			MemRect(px + 4 * _2X, py + 1 * _2X, 4 * _2X, 4 * _2X, 0xFFFFFF);
		} else if (s_projectiles[i].type == 1) {
			// Gunshot: glowing fiery tracer
			MemRect(px - 8 * _2X, py, 14 * _2X, 3 * _2X, 0xFFAA33);
			MemRect(px + 2 * _2X, py + 1 * _2X, 6 * _2X, 4 * _2X, 0xFFFF88);
		} else {
			// Arcane Magic Bolt: glowing sphere with core
			MemRect(px - 4 * _2X, py + 4 * _2X, 8 * _2X, 8 * _2X, 0x9944FF);
			MemRect(px - 2 * _2X, py + 2 * _2X, 4 * _2X, 4 * _2X, 0x88FFFF);
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
			CenterTextStrSolid(numStr, (int)s_damages[i].x, (int)s_damages[i].y, 0.60f);
		} else {
			SetFontColor(COLOR_WHITE);
			CenterTextStrSolid(numStr, (int)s_damages[i].x, (int)s_damages[i].y, 0.48f);
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
