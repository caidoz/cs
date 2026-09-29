#pragma once
// BattleSiegeFortress.h
// Mobile Fortress vs Fortress Battle Scene in MD_PLAY:
// - Left: Player's Modular Mobile Castle (1~10 floors, hero Robin & party crew, mounted siege weapons, purple royal crown banner)
// - Right: Enemy Mobile Fortress ("검은 해골 성", dark granite keep, skull banners, torches, enemy boss & siege minions, iron cannon)
// - Center: Realtime artillery exchange (burning cannonballs with smoke trails, arrows, magic, explosions, floating damage)
// - Environment: Bright, lush fantasy battlefield (azure sky gradient, drifting clouds, distant landscape, cobblestone road)

#include <cmath>
#include <cstdio>
#include <cstdlib>

namespace BattleSiegeFortress {

struct GiantBossDef {
	int enemyType;
	const char* name;
	const char* title;
	float scale;
	int maxHp;
};

static const GiantBossDef kBosses[] = {
	{ ENEMY_GOLEM,      "고대 골렘",          "Lv.99 고대의 수호 골렘",    1.45f, 1000000 },
	{ ENEMY_DARKGIANT,  "그레이트 아머",      "Lv.120 암흑의 거신병",     1.40f, 1500000 },
	{ ENEMY_DRAGON1,    "진홍의 화룡",        "Lv.150 진홍의 염제 드래곤", 1.45f, 2000000 },
	{ ENEMY_MAMMOTH,    "프로스트 맘모스",    "Lv.110 혹한의 거수",       1.40f, 1200000 },
	{ ENEMY_MACHINE,    "라이스너",          "Lv.135 마도 결전 병기",    1.45f, 1800000 },
	{ ENEMY_KIMERA,     "마도합성수 키메라",  "Lv.125 융합의 마수",       1.45f, 1400000 },
};
static const int kBossCount = sizeof(kBosses) / sizeof(kBosses[0]);

static int s_curBossIdx = 0;
static float s_bossHp = 1000000.0f;
static float s_bossDisplayHp = 1000000.0f;
static int s_attackTimer = 0;
static float s_enemyHitFlash = 0.0f;
static float s_playerHitFlash = 0.0f;

// Continuous horizontal travel distance along the road
static float s_scrollDist = 0.0f;
static float s_scrollSpeed = 24.0f; // mobile-fortress travel speed

inline bool IsMoving() {
	return StageRtAutoOn();
}

inline int VisualGroundY(int layoutGroundY) {
	(void)layoutGroundY;
	return (int)(DY * 0.31f);
}

// Combat Projectile types
enum ProjType {
	PROJ_ARROW = 0,
	PROJ_TRACER,
	PROJ_MAGIC,
	PROJ_SLASH,
	PROJ_PLAYER_CANNON,
	PROJ_ENEMY_FIRE_CANNON, // Burning flaming cannonball with smoke puffs
	PROJ_ENEMY_FIREBALL,
};

struct SmokePuff {
	float x, y;
	float radius;
	float alpha;
	bool active;
};
static const int MAX_SMOKE = 32;
static SmokePuff s_smoke[MAX_SMOKE] = {};

struct Projectile {
	float x, y;
	float vx, vy;
	float gravity;
	int type;
	int color;
	float life;
	float maxLife;
	bool active;
};
static const int MAX_PROJECTILES = 24;
static Projectile s_projectiles[MAX_PROJECTILES] = {};

// Impact Explosion Effect
struct HitExplosion {
	float x, y;
	float life;
	float maxLife;
	float radius;
	int color;
	bool active;
};
static const int MAX_EXPLOSIONS = 16;
static HitExplosion s_explosions[MAX_EXPLOSIONS] = {};

// Floating Damage Numbers
struct DamageText {
	float x, y;
	int damage;
	float life;
	float maxLife;
	bool critical;
	bool isEnemy;
	bool active;
};
static const int MAX_DAMAGE_TEXTS = 16;
static DamageText s_damages[MAX_DAMAGE_TEXTS] = {};

inline void NextBoss() {
	s_curBossIdx = (s_curBossIdx + 1) % kBossCount;
	s_bossHp = (float)kBosses[s_curBossIdx].maxHp;
	s_bossDisplayHp = s_bossHp;
	s_enemyHitFlash = 0.0f;
}

inline const GiantBossDef& GetCurrentBoss() {
	return kBosses[s_curBossIdx];
}

inline void SpawnExplosion(float x, float y, float radius, int color = 0xFFAA22) {
	for (int i = 0; i < MAX_EXPLOSIONS; ++i) {
		if (!s_explosions[i].active) {
			s_explosions[i].active = true;
			s_explosions[i].x = x;
			s_explosions[i].y = y;
			s_explosions[i].radius = radius;
			s_explosions[i].color = color;
			s_explosions[i].maxLife = 0.35f;
			s_explosions[i].life = s_explosions[i].maxLife;
			break;
		}
	}
}

inline void SpawnSmoke(float x, float y, float radius) {
	for (int i = 0; i < MAX_SMOKE; ++i) {
		if (!s_smoke[i].active) {
			s_smoke[i].active = true;
			s_smoke[i].x = x;
			s_smoke[i].y = y;
			s_smoke[i].radius = radius;
			s_smoke[i].alpha = 24.0f;
			break;
		}
	}
}

inline void SpawnDamage(float x, float y, int dmg, bool crit, bool isEnemy = true) {
	for (int i = 0; i < MAX_DAMAGE_TEXTS; ++i) {
		if (!s_damages[i].active) {
			s_damages[i].active = true;
			s_damages[i].x = x + (float)((rand() % 21) - 10) * (float)_2X;
			s_damages[i].y = y + (float)((rand() % 17) - 8) * (float)_2X;
			s_damages[i].damage = dmg;
			s_damages[i].critical = crit;
			s_damages[i].isEnemy = isEnemy;
			s_damages[i].maxLife = 0.75f;
			s_damages[i].life = s_damages[i].maxLife;
			break;
		}
	}
}

inline void SpawnProjectile(float startX, float startY, float vx, float vy, float gravity, int type, int color = 0) {
	for (int i = 0; i < MAX_PROJECTILES; ++i) {
		if (!s_projectiles[i].active) {
			s_projectiles[i].active = true;
			s_projectiles[i].x = startX;
			s_projectiles[i].y = startY;
			s_projectiles[i].vx = vx;
			s_projectiles[i].vy = vy;
			s_projectiles[i].gravity = gravity;
			s_projectiles[i].type = type;
			s_projectiles[i].color = color;
			s_projectiles[i].maxLife = 2.0f;
			s_projectiles[i].life = s_projectiles[i].maxLife;
			break;
		}
	}
}

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
	const bool moving = IsMoving();
	const float currentSpeed = moving ? s_scrollSpeed * (float)_2X : 0.0f;
	if (moving) s_scrollDist += currentSpeed * dt;

	if (s_enemyHitFlash > 0.0f) s_enemyHitFlash = Max(0.0f, s_enemyHitFlash - dt * 3.0f);
	if (s_playerHitFlash > 0.0f) s_playerHitFlash = Max(0.0f, s_playerHitFlash - dt * 3.0f);

	if (s_bossDisplayHp > s_bossHp) {
		s_bossDisplayHp -= (s_bossDisplayHp - s_bossHp) * 0.12f;
	}

	const float groundY = (float)VisualGroundY(0);
	const float castleW = 145.0f * (float)_2X;
	const float castleLeft = 8.0f * (float)_2X;
	const float enemyW = 145.0f * (float)_2X;
	const float enemyLeft = (float)DX - enemyW - 8.0f * (float)_2X;

	// 1. Update Projectiles
	for (int i = 0; i < MAX_PROJECTILES; ++i) {
		if (!s_projectiles[i].active) continue;
		s_projectiles[i].x += s_projectiles[i].vx * dt * 60.0f;
		s_projectiles[i].y += s_projectiles[i].vy * dt * 60.0f;
		s_projectiles[i].vy += s_projectiles[i].gravity * dt * 60.0f;
		s_projectiles[i].life -= dt;

		// Smoke trail for enemy burning cannonball
		if (s_projectiles[i].type == PROJ_ENEMY_FIRE_CANNON && (frame % 3) == 0) {
			SpawnSmoke(s_projectiles[i].x + 8.0f * (float)_2X, s_projectiles[i].y + 4.0f * (float)_2X, 8.0f * (float)_2X);
		}

		// Hit detection on Enemy Fortress
		if (s_projectiles[i].vx > 0.0f && s_projectiles[i].x >= enemyLeft + 16.0f * (float)_2X) {
			s_projectiles[i].active = false;
			SpawnExplosion(s_projectiles[i].x, s_projectiles[i].y, 18.0f * (float)_2X, 0xFFAA22);
			const int dmg = 120 + rand() % 160;
			const bool crit = (rand() % 4 == 0);
			SpawnDamage(s_projectiles[i].x - 10.0f * (float)_2X, s_projectiles[i].y + 20.0f * (float)_2X, crit ? dmg * 2 : dmg, crit, true);
			s_bossHp = Max(0.0f, s_bossHp - (float)(crit ? dmg * 2 : dmg));
			s_enemyHitFlash = 1.0f;
		}
		// Hit detection on Player Castle
		else if (s_projectiles[i].vx < 0.0f && s_projectiles[i].x <= castleLeft + castleW - 16.0f * (float)_2X) {
			s_projectiles[i].active = false;
			SpawnExplosion(s_projectiles[i].x, s_projectiles[i].y, 22.0f * (float)_2X, 0xFF4400);
			const int dmg = 65 + rand() % 95;
			SpawnDamage(s_projectiles[i].x + 10.0f * (float)_2X, s_projectiles[i].y + 15.0f * (float)_2X, dmg, false, false);
			s_playerHitFlash = 1.0f;
		}
		else if (s_projectiles[i].life <= 0.0f || s_projectiles[i].y < groundY - 10.0f * (float)_2X) {
			s_projectiles[i].active = false;
		}
	}

	// 2. Update Smoke puffs
	for (int i = 0; i < MAX_SMOKE; ++i) {
		if (!s_smoke[i].active) continue;
		s_smoke[i].y += dt * 10.0f * (float)_2X;
		s_smoke[i].radius += dt * 12.0f * (float)_2X;
		s_smoke[i].alpha -= dt * 36.0f;
		if (s_smoke[i].alpha <= 0.0f) s_smoke[i].active = false;
	}

	// 3. Update Explosions
	for (int i = 0; i < MAX_EXPLOSIONS; ++i) {
		if (!s_explosions[i].active) continue;
		s_explosions[i].life -= dt;
		if (s_explosions[i].life <= 0.0f) s_explosions[i].active = false;
	}

	// 4. Update Damage texts
	for (int i = 0; i < MAX_DAMAGE_TEXTS; ++i) {
		if (!s_damages[i].active) continue;
		s_damages[i].y += dt * 26.0f * (float)_2X;
		s_damages[i].life -= dt;
		if (s_damages[i].life <= 0.0f) s_damages[i].active = false;
	}

	// 5. Automatic Firing Cycles in Combat
	s_attackTimer++;
	if (s_attackTimer >= 48) {
		s_attackTimer = 0;
		// Player fires projectile right
		const int pType = (rand() % 3 == 0) ? PROJ_PLAYER_CANNON : ((rand() % 2 == 0) ? PROJ_ARROW : PROJ_MAGIC);
		const float pSpeed = (pType == PROJ_PLAYER_CANNON) ? 8.0f : 11.0f;
		const float pGrav = (pType == PROJ_PLAYER_CANNON) ? -0.06f : 0.0f;
		SpawnProjectile(castleLeft + castleW + 4.0f * (float)_2X, groundY + 68.0f * (float)_2X,
			pSpeed * (float)_2X, 1.2f * (float)_2X, pGrav * (float)_2X, pType, 0);

		// Enemy fortress launches burning cannonball arching left!
		SpawnProjectile(enemyLeft - 8.0f * (float)_2X, groundY + 80.0f * (float)_2X,
			-7.2f * (float)_2X, 3.2f * (float)_2X, -0.11f * (float)_2X, PROJ_ENEMY_FIRE_CANNON, 0);
	}
}

// 5-Layer Bright Fantasy Sky & Battlefield Background
inline void DrawBackground(int groundY, int invenTop) {
	// 1. Rich Sky Gradient: 24 smooth bands from top (DY) down to road (groundY)
	const int skyH = DY - groundY;
	const int steps = 24;
	const int bandH = (skyH + steps - 1) / steps;
	for (int i = 0; i < steps; ++i) {
		const float t = (float)i / (float)(steps - 1);
		const int r = (int)(44.0f + (160.0f - 44.0f) * t);
		const int g = (int)(122.0f + (226.0f - 122.0f) * t);
		const int b = (int)(214.0f + (255.0f - 214.0f) * t);
		const int col = (r << 16) | (g << 8) | b;
		const int y = DY - i * bandH;
		MemRect(0, y, DX, bandH + 1, col);
	}

	// 2. Parallax Drifting Clouds (LOBBY_CLOUD_IMG)
	const int cloudImg = LOBBY_CLOUD_IMG;
	if (!sprite[cloudImg]) LoadImg(cloudImg);
	if (sprite[cloudImg]) {
		const auto sz = sprite[cloudImg]->getContentSize();
		const float zoom = (float)DX / sz.width;
		const float tileW = sz.width * zoom;
		const float offX = -std::fmod(s_scrollDist * 0.08f, tileW);
		const int cloudY = DY - (int)(16 * _2X);
		for (float x = offX; x < (float)DX; x += tileW) {
			DrawImage((int)sz.width, (int)sz.height, 0, 0, (int)x, cloudY,
			          false, false, false, false, false, zoom, sprite[cloudImg], cloudImg);
		}
	}

	// 3. Distant Mountains & Castle Landscape (LOBBY_LANDSCAPE_IMG)
	const int lsImg = LOBBY_LANDSCAPE_IMG;
	if (!sprite[lsImg]) LoadImg(lsImg);
	if (sprite[lsImg]) {
		const auto sz = sprite[lsImg]->getContentSize();
		const float zoom = (float)(DX * 1.15f) / sz.width;
		const float tileW = sz.width * zoom;
		const float offX = -std::fmod(s_scrollDist * 0.16f, tileW);
		const int lsY = groundY + (int)(sz.height * zoom * 0.76f);
		for (float x = offX; x < (float)DX; x += tileW) {
			DrawImage((int)sz.width, (int)sz.height, 0, 0, (int)x, lsY,
			          false, false, false, false, false, zoom, sprite[lsImg], lsImg);
		}
	}

	// 4. Midground Rolling Green Foothills (LOBBY_FOOTHILLS_IMG)
	const int fhImg = LOBBY_FOOTHILLS_IMG;
	if (!sprite[fhImg]) LoadImg(fhImg);
	if (sprite[fhImg]) {
		const auto sz = sprite[fhImg]->getContentSize();
		const float zoom = (float)DX / sz.width;
		const float tileW = sz.width * zoom;
		const float offX = -std::fmod(s_scrollDist * 0.32f, tileW);
		const int fhY = groundY + (int)(sz.height * zoom * 0.62f);
		for (float x = offX; x < (float)DX; x += tileW) {
			DrawImage((int)sz.width, (int)sz.height, 0, 0, (int)x, fhY,
			          false, false, false, false, false, zoom, sprite[fhImg], fhImg);
		}
	}

	// 5. Stylized Battlefield Cobblestone Highway & Earth Embankment
	const int roadTop = groundY + 10 * _2X;
	const int roadH = roadTop - invenTop + 10 * _2X;

	// Grass verge along upper road edge
	MemRect(0, roadTop, DX, 12 * _2X, 0x487A28);
	MemRect(0, roadTop - 2 * _2X, DX, 3 * _2X, 0x649C36);

	// Roadbed base layer
	MemRect(0, roadTop - 8 * _2X, DX, roadH, 0x443E38);

	// Lower bedrock foundation down to inventory
	if (groundY - 14 * _2X > invenTop) {
		MemRect(0, groundY - 14 * _2X, DX, (groundY - 14 * _2X) - invenTop + 8 * _2X, 0x2A2420);
	}

	// Scrolling Cobblestone Pavers (moving horizontally with fortress travel)
	const float paverW = 32.0f * (float)_2X;
	const float paverH = 10.0f * (float)_2X;
	const float scrollX = -std::fmod(s_scrollDist * 0.58f, paverW * 2.0f);

	for (int row = 0; row < 5; ++row) {
		const int rowY = roadTop - (12 + row * 10) * _2X;
		const float rowShift = (row % 2 == 1) ? (paverW * 0.5f) : 0.0f;
		const float startX = scrollX - paverW + rowShift;
		const int stoneCol = (row % 2 == 0) ? 0x60584E : 0x564E46;
		const int highlightCol = (row % 2 == 0) ? 0x766C60 : 0x6C6458;

		for (float x = startX; x < (float)DX + paverW; x += paverW) {
			const int px = (int)x;
			const int pw = (int)paverW - 3 * _2X;
			const int ph = (int)paverH - 2 * _2X;
			MemRect(px, rowY, pw, ph, stoneCol);
			MemRect(px + 1 * _2X, rowY - 1 * _2X, pw - 2 * _2X, 2 * _2X, highlightCol);
			MemRectFrame(px, rowY, pw, ph, 0x36302A);
		}
	}

	// Curb stones along top road border
	const float curbW = 20.0f * (float)_2X;
	const float curbShift = -std::fmod(s_scrollDist * 0.58f, curbW);
	for (float cx = curbShift - curbW; cx < (float)DX + curbW; cx += curbW) {
		MemRect((int)cx, roadTop - 8 * _2X, (int)curbW - 2 * _2X, 5 * _2X, 0x7C7468);
		MemRectFrame((int)cx, roadTop - 8 * _2X, (int)curbW - 2 * _2X, 5 * _2X, 0x3A342E);
	}
}

// Rotating Wooden Spoke Siege Wheel
inline void DrawSpokeWheel(float cx, float cy, float radius, float angle, bool dark) {
	const int rimCol = dark ? 0x282420 : 0x583A20;
	const int innerCol = dark ? 0x1A1816 : 0x8C5A34;
	const int ironCol = dark ? 0x141210 : 0x3A2818;
	const int hubCol = dark ? 0x7A7470 : 0xD4A034;
	const int r = (int)radius;

	// Outer iron rim
	MemRect((int)(cx - r), (int)(cy + r), r * 2, r * 2, ironCol);
	MemRectFrame((int)(cx - r), (int)(cy + r), r * 2, r * 2, rimCol);
	// Inner wood tyre
	MemRect((int)(cx - r + 3 * _2X), (int)(cy + r - 3 * _2X), (r - 3 * _2X) * 2, (r - 3 * _2X) * 2, innerCol);

	// Spokes (rotating with angle)
	const float rad = angle * 0.01745329f;
	for (int i = 0; i < 4; ++i) {
		const float a = rad + (float)i * 0.785398f;
		const float cosA = std::cos(a);
		const float sinA = std::sin(a);
		const int x1 = (int)(cx + (radius - 4.0f * _2X) * cosA);
		const int y1 = (int)(cy + (radius - 4.0f * _2X) * sinA);
		const int x2 = (int)(cx - (radius - 4.0f * _2X) * cosA);
		const int y2 = (int)(cy - (radius - 4.0f * _2X) * sinA);
		MemRect(Min(x1, x2), Max(y1, y2), abs(x1 - x2) + 2 * _2X, abs(y1 - y2) + 2 * _2X, ironCol);
	}
	// Center hub
	const int hr = (int)(radius * 0.30f);
	MemRect((int)(cx - hr), (int)(cy + hr), hr * 2, hr * 2, hubCol);
	MemRectFrame((int)(cx - hr), (int)(cy + hr), hr * 2, hr * 2, 0x101010);
}

// Renders inventory items reflected onto the castle
inline void DrawInventoryCastleReflections(int castleIdx, float castleLeft, float castleTop,
                                          float castleW, float castleH, float castleScale) {
	// 1. Swords from the inventory mounted on castle crenels/turrets!
	StageSword invenSwords[16];
	const int swordCnt = GridTestSwords(invenSwords, 16);

	for (int s = 0; s < swordCnt && s < 8; ++s) {
		const float u = 0.16f + 0.09f * (float)s;
		const float wx = castleLeft + u * castleW * castleScale;
		const float wy = castleTop;
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

// Left: Player's Modular Mobile Castle with Hero & Crew
inline void DrawCastle(int groundY) {
	const int curCastle = Max(0, Min(robin.castle, 9));
	const int floorCount = curCastle + 1;
	const float rawW = 512.0f;
	const float rawH = (float)floorCount * 128.0f;
	const float castleW = 145.0f * (float)_2X;
	const float scale = castleW / rawW;

	// Road contact line
	const float shudderY = (s_playerHitFlash > 0.0f) ? ((rand() % 5) - 2) * 1.5f * (float)_2X : 0.0f;
	const float rumbleY = IsMoving() ? (std::sin((float)frame * 0.40f) * 1.0f * (float)_2X) : 0.0f;
	const float castleLeft = 8.0f * (float)_2X;
	const float castleBottom = (float)groundY + shudderY + rumbleY;
	const float castleTop = castleBottom + rawH * scale;

	// 1. Draw modular castle rooms from bottom (floor 0) to top (floor curCastle)
	for (int floor = 0; floor <= curCastle; ++floor) {
		const int stage = (floor == curCastle) ? 0 : 5;
		const int roomImg = CASTLE_ROOM_V4_FIRST_IMG + floor * 6 + stage;
		if (!sprite[roomImg]) LoadImg(roomImg);
		if (sprite[roomImg]) {
			const float roomTop = castleBottom + (float)(floor + 1) * 128.0f * scale;
			DrawImage(512, 128, 0, 0,
				(int)castleLeft, (int)roomTop,
				false, 0, 0, 0, 0,
				scale, sprite[roomImg], roomImg);
		}
	}

	// 2. Wooden Siege Chassis & Wheels at base
	const float wheelAngle = std::fmod(s_scrollDist * 2.5f, 360.0f);
	const float wheelRadius = 14.0f * (float)_2X;
	DrawSpokeWheel(castleLeft + 24.0f * _2X, castleBottom + 6.0f * _2X, wheelRadius, wheelAngle, false);
	DrawSpokeWheel(castleLeft + castleW - 24.0f * _2X, castleBottom + 6.0f * _2X, wheelRadius, wheelAngle, false);

	// 3. Purple Royal Banner with Gold Crown on player castle wall
	const int banW = 28 * _2X;
	const int banH = 46 * _2X;
	const int banX = (int)(castleLeft + 18 * _2X);
	const int banY = (int)(castleBottom + 72 * _2X);
	MemRect(banX, banY, banW, banH, 0x642898);
	MemRectFrame(banX, banY, banW, banH, 0x3C1460);
	MemRect(banX + 3 * _2X, banY - banH + 3 * _2X, banW - 6 * _2X, 6 * _2X, 0x541E80);
	// Gold Crown
	const int crX = banX + banW / 2;
	const int crY = banY - 14 * _2X;
	MemRect(crX - 6 * _2X, crY, 12 * _2X, 8 * _2X, 0xFFD700);
	MemRect(crX - 8 * _2X, crY + 4 * _2X, 4 * _2X, 4 * _2X, 0xFFE680);
	MemRect(crX + 4 * _2X, crY + 4 * _2X, 4 * _2X, 4 * _2X, 0xFFE680);

	// 4. Player Castle Siege Cannon protruding right
	const int cannonW = 20 * _2X;
	const int cannonH = 12 * _2X;
	const int cannonX = (int)(castleLeft + castleW - 4 * _2X);
	const int cannonY = (int)(castleBottom + 70 * _2X);
	MemRect(cannonX, cannonY, cannonW, cannonH, 0x48423A);
	MemRectFrame(cannonX, cannonY, cannonW, cannonH, 0x24201C);
	MemRect(cannonX + cannonW - 2 * _2X, cannonY + 2 * _2X, 4 * _2X, cannonH + 4 * _2X, 0x5C544A);

	// 5. Inventory items reflected on the castle (Mounted weapons & Aegis shield)
	DrawInventoryCastleReflections(curCastle, castleLeft, castleTop, rawW, rawH, scale);

	// 6. Hero (Robin) stationed on the 1st floor room, facing RIGHT!
	const float charZoom = DIORAMAZOOM * 0.70f * scale * 512.0f / DX;
	const float heroZoom = ao[ROBIN].zoom * charZoom;
	const float heroX = castleLeft + 256.0f * scale;
	const float heroY = castleBottom + 14.0f * scale;

	if (ao[ROBIN].active) {
		const int heroMotion = (ao[ROBIN].motion >= 0) ? ao[ROBIN].motion : (PO_C0_N0 + (frame / 4) % 4);
		DrawPlayer(&ao[ROBIN], heroMotion, (int)heroX, (int)heroY, RIGHT, heroZoom, 0.0f, false, true);
	}

	// 7. Draw party members stationed across castle floors
	static const struct { float u; int floorOffset; } crewSlots[MAXCREW] = {
		{ 0.28f, 0 }, { 0.72f, 0 }, { 0.35f, 1 }, { 0.65f, 1 }
	};
	for (int i = 0; i < MAXCREW; ++i) {
		const OBJECT* crew = &ao[CREW + i];
		if (!crew->active || crew->dead) continue;
		const int crewFloor = Min(crewSlots[i].floorOffset, curCastle);
		const float cx = castleLeft + crewSlots[i].u * rawW * scale;
		const float cy = castleBottom + ((float)crewFloor * 128.0f + 14.0f) * scale;
		DrawCmfDetailShadow(crew->cmf, crew->motion, (int)cx, (int)cy, RIGHT,
			enemyIconZoom[crew->type] * CREWZOOM * LOBBY_CREW_ZOOM_SCALE * 0.90f * charZoom);
	}
}

// Right: Enemy Mobile Fortress ("검은 해골 성" - Black Skull Castle)
inline void DrawEnemyFortress(int groundY) {
	const float enemyW = 145.0f * (float)_2X;
	const float enemyH = 165.0f * (float)_2X;
	const float enemyLeft = (float)DX - enemyW - 8.0f * (float)_2X;
	const float shudderY = (s_enemyHitFlash > 0.0f) ? ((rand() % 5) - 2) * 1.5f * (float)_2X : 0.0f;
	const float rumbleY = IsMoving() ? (std::sin((float)frame * 0.35f + 1.2f) * 1.0f * (float)_2X) : 0.0f;
	const float enemyBottom = (float)groundY + shudderY + rumbleY;
	const float enemyTop = enemyBottom + enemyH;

	// Flash tint when hit
	const int bodyBase = (s_enemyHitFlash > 0.0f) ? 0x6A3434 : 0x2E303A;
	const int bodyTrim = (s_enemyHitFlash > 0.0f) ? 0x9A4848 : 0x444856;

	// 1. Lower chassis beam
	MemRect((int)enemyLeft, (int)(enemyBottom + 26 * _2X), (int)enemyW, 26 * _2X, 0x1C1E24);
	MemRectFrame((int)enemyLeft, (int)(enemyBottom + 26 * _2X), (int)enemyW, 26 * _2X, 0x101216);

	// 2. Main Stone Fortress Keep
	MemRect((int)enemyLeft, (int)(enemyTop - 22 * _2X), (int)enemyW, (int)(enemyH - 48 * _2X), bodyBase);
	MemRectFrame((int)enemyLeft, (int)(enemyTop - 22 * _2X), (int)enemyW, (int)(enemyH - 48 * _2X), 0x1A1C22);

	// Horizontal stone masonry courses
	for (int y = (int)(enemyBottom + 44 * _2X); y < (int)(enemyTop - 24 * _2X); y += 18 * _2X) {
		MemRect((int)enemyLeft + 2 * _2X, y, (int)enemyW - 4 * _2X, 1 * _2X, 0x1E2028);
	}

	// Iron-reinforced arch gate
	const int gateW = 34 * _2X;
	const int gateH = 46 * _2X;
	const int gateX = (int)(enemyLeft + (enemyW - gateW) * 0.5f);
	const int gateY = (int)(enemyBottom + gateH + 16 * _2X);
	MemRect(gateX, gateY, gateW, gateH, 0x14161C);
	MemRectFrame(gateX, gateY, gateW, gateH, 0x4A4E5C);
	for (int bx = gateX + 6 * _2X; bx < gateX + gateW; bx += 8 * _2X) {
		MemRect(bx, gateY, 2 * _2X, gateH, 0x2A2E38);
	}

	// 3. Protruding heavy iron siege cannon (facing LEFT!)
	const int cannonW = 22 * _2X;
	const int cannonH = 14 * _2X;
	const int cannonX = (int)(enemyLeft - cannonW + 4 * _2X);
	const int cannonY = (int)(enemyBottom + 78 * _2X);
	MemRect(cannonX, cannonY, cannonW, cannonH, 0x1A1C22);
	MemRectFrame(cannonX, cannonY, cannonW, cannonH, 0x3E4250);
	MemRect(cannonX - 3 * _2X, cannonY + 2 * _2X, 5 * _2X, cannonH + 4 * _2X, 0x14161C); // Muzzle rim
	MemRect(cannonX - 1 * _2X, cannonY + 1 * _2X, 2 * _2X, cannonH + 2 * _2X, 0x0A0A0E); // Dark bore

	// 4. Crimson Skull Banner (검은 해골 깃발)
	const int banW = 34 * _2X;
	const int banH = 58 * _2X;
	const int banX = (int)(enemyLeft + enemyW * 0.38f);
	const int banY = (int)(enemyTop - 26 * _2X);
	MemRect(banX, banY, banW, banH, 0x9E1818);
	MemRectFrame(banX, banY, banW, banH, 0x540C0C);
	MemRect(banX + 4 * _2X, banY - banH + 4 * _2X, banW - 8 * _2X, 8 * _2X, 0x821414);
	// White Skull Crest
	const int skX = banX + banW / 2;
	const int skY = banY - 18 * _2X;
	MemRect(skX - 8 * _2X, skY, 16 * _2X, 14 * _2X, 0xEAE4DC); // Skull dome
	MemRect(skX - 5 * _2X, skY - 14 * _2X, 10 * _2X, 8 * _2X, 0xD4CEBE); // Jaw
	MemRect(skX - 6 * _2X, skY - 4 * _2X, 4 * _2X, 5 * _2X, 0x1C0606); // Left eye
	MemRect(skX + 2 * _2X, skY - 4 * _2X, 4 * _2X, 5 * _2X, 0x1C0606); // Right eye
	MemRect(skX - 1 * _2X, skY - 9 * _2X, 2 * _2X, 3 * _2X, 0x1C0606); // Nose

	// 5. Battlements & Merlons along top deck
	const int merlonW = 16 * _2X;
	const int merlonH = 22 * _2X;
	for (int mx = (int)enemyLeft; mx < (int)(enemyLeft + enemyW); mx += 26 * _2X) {
		MemRect(mx, (int)enemyTop, Min(merlonW, (int)(enemyLeft + enemyW - mx)), merlonH, bodyTrim);
		MemRectFrame(mx, (int)enemyTop, Min(merlonW, (int)(enemyLeft + enemyW - mx)), merlonH, 0x1A1C22);
	}

	// 6. Corner Braziers with animated flickering flames
	for (int i = 0; i < 2; ++i) {
		const int bzX = (int)(i == 0 ? enemyLeft + 3 * _2X : enemyLeft + enemyW - 13 * _2X);
		const int bzY = (int)(enemyTop + 6 * _2X);
		MemRect(bzX, bzY, 10 * _2X, 8 * _2X, 0x1A1A20);
		MemRectFrame(bzX, bzY, 10 * _2X, 8 * _2X, 0x383844);
		const float flameAnim = std::sin((float)frame * 0.3f + (float)i * 2.0f);
		const int flH = (int)((14.0f + flameAnim * 4.0f) * (float)_2X);
		MemRect(bzX - 1 * _2X, bzY + flH, 12 * _2X, flH, 0xFF4400);
		MemRect(bzX + 1 * _2X, bzY + flH - 3 * _2X, 8 * _2X, flH - 4 * _2X, 0xFFAA00);
		MemRect(bzX + 3 * _2X, bzY + flH - 6 * _2X, 4 * _2X, flH - 8 * _2X, 0xFFFF66);
	}

	// 7. Enemy Boss Stationed on the Battlements!
	const int foe = StageRtFoe();
	const int bossMonsterType = (foe >= 0 && ao[foe].active) ? ao[foe].type : kBosses[s_curBossIdx].enemyType;
	const int bossMotion = (foe >= 0 && ao[foe].active) ? ao[foe].motion : (crewPos[bossMonsterType * 5 + 0] + (frame / 4 % Max(1, crewPos[bossMonsterType * 5 + 1])));
	const int bossCmf = (foe >= 0 && ao[foe].active) ? ao[foe].cmf : enemyData[bossMonsterType * ENEMYDATASIZE + ENEMYDATA_CMF];

	const float bX = enemyLeft + enemyW * 0.50f;
	const float bY = enemyTop + 2 * _2X;
	DrawCmfDetailShadow(bossCmf, bossMotion, (int)bX, (int)bY, LEFT, enemyIconZoom[bossMonsterType] * 1.45f);

	// 8. Heavy Dark Siege Wheels
	const float wheelAngle = std::fmod(s_scrollDist * 2.5f, 360.0f);
	const float wheelRadius = 14.0f * (float)_2X;
	DrawSpokeWheel(enemyLeft + 24.0f * _2X, enemyBottom + 6.0f * _2X, wheelRadius, wheelAngle, true);
	DrawSpokeWheel(enemyLeft + enemyW - 24.0f * _2X, enemyBottom + 6.0f * _2X, wheelRadius, wheelAngle, true);
}

// In-flight Combat Projectiles
inline void DrawProjectiles() {
	// Draw Smoke trails first (behind projectiles)
	for (int i = 0; i < MAX_SMOKE; ++i) {
		if (!s_smoke[i].active) continue;
		SetAlpha((int)s_smoke[i].alpha);
		const int r = (int)s_smoke[i].radius;
		MemRect((int)(s_smoke[i].x - r), (int)(s_smoke[i].y + r), r * 2, r * 2, 0x48423E);
	}
	SetAlpha(32);

	for (int i = 0; i < MAX_PROJECTILES; ++i) {
		if (!s_projectiles[i].active) continue;
		const int px = (int)s_projectiles[i].x;
		const int py = (int)s_projectiles[i].y;

		if (s_projectiles[i].type == PROJ_ARROW) {
			// Arrow: wooden shaft with bright fletching
			MemRect(px - 9 * _2X, py, 14 * _2X, 2 * _2X, 0xC49A45);
			MemRect(px + 3 * _2X, py + 1 * _2X, 5 * _2X, 4 * _2X, 0xFFFFFF);
		} else if (s_projectiles[i].type == PROJ_TRACER) {
			// Gunshot: glowing fiery tracer
			MemRect(px - 10 * _2X, py, 18 * _2X, 3 * _2X, 0xFFAA33);
			MemRect(px + 3 * _2X, py + 1 * _2X, 8 * _2X, 4 * _2X, 0xFFFF88);
		} else if (s_projectiles[i].type == PROJ_MAGIC) {
			// Arcane Magic Bolt: glowing sphere with core
			MemRect(px - 5 * _2X, py + 5 * _2X, 10 * _2X, 10 * _2X, 0x33A0FF);
			MemRect(px - 2 * _2X, py + 2 * _2X, 4 * _2X, 4 * _2X, 0xDDFFFF);
		} else if (s_projectiles[i].type == PROJ_PLAYER_CANNON) {
			// Player Cannonball: heavy iron ball
			MemRect(px - 6 * _2X, py + 6 * _2X, 12 * _2X, 12 * _2X, 0x2A2E38);
			MemRectFrame(px - 6 * _2X, py + 6 * _2X, 12 * _2X, 12 * _2X, 0x5C6272);
			MemRect(px - 2 * _2X, py + 4 * _2X, 4 * _2X, 4 * _2X, 0x8E94A4);
		} else if (s_projectiles[i].type == PROJ_ENEMY_FIRE_CANNON) {
			// Burning Flaming Cannonball!
			MemRect(px - 9 * _2X, py + 9 * _2X, 18 * _2X, 18 * _2X, 0xFF3300);
			MemRect(px - 6 * _2X, py + 6 * _2X, 12 * _2X, 12 * _2X, 0xFF9900);
			MemRect(px - 3 * _2X, py + 3 * _2X, 6 * _2X, 6 * _2X, 0xFFFF66);
			MemRect(px - 1 * _2X, py + 1 * _2X, 2 * _2X, 2 * _2X, 0xFFFFFF);
		} else {
			// Default Sword Slash Wave
			const int col = (s_projectiles[i].color != 0) ? s_projectiles[i].color : 0xDFD9C0;
			MemRect(px - 12 * _2X, py + 6 * _2X, 24 * _2X, 12 * _2X, col);
			MemRect(px - 6 * _2X, py + 3 * _2X, 12 * _2X, 6 * _2X, 0xFFFFFF);
		}
	}
}

// Impact Explosion Sparks
inline void DrawExplosions() {
	for (int i = 0; i < MAX_EXPLOSIONS; ++i) {
		if (!s_explosions[i].active) continue;
		const float t = 1.0f - (s_explosions[i].life / s_explosions[i].maxLife);
		const int r = (int)(s_explosions[i].radius * (0.5f + t * 0.8f));
		const int x = (int)s_explosions[i].x;
		const int y = (int)s_explosions[i].y;
		const int alpha = (int)(32.0f * (1.0f - t));
		SetAlpha(alpha);
		MemRect(x - r, y + r, r * 2, r * 2, s_explosions[i].color);
		MemRect(x - r / 2, y + r / 2, r, r, 0xFFFF88);
	}
	SetAlpha(32);
}

// Floating Damage Numbers
inline void DrawDamageTexts() {
	char numStr[32];
	for (int i = 0; i < MAX_DAMAGE_TEXTS; ++i) {
		if (!s_damages[i].active) continue;
		sprintf(numStr, "%d", s_damages[i].damage);
		if (s_damages[i].critical) {
			SetFontColor(COLOR_REALYELLOW);
			CenterTextStrSolid(numStr, (int)s_damages[i].x, (int)s_damages[i].y, 0.70f);
		} else if (s_damages[i].isEnemy) {
			SetFontColor(COLOR_WHITE);
			CenterTextStrSolid(numStr, (int)s_damages[i].x, (int)s_damages[i].y, 0.55f);
		} else {
			SetFontColor(0xFF6666);
			CenterTextStrSolid(numStr, (int)s_damages[i].x, (int)s_damages[i].y, 0.55f);
		}
	}
}

// Top-Right Boss Health Bar HUD
inline void DrawBossUI() {
	const GiantBossDef& def = kBosses[s_curBossIdx];

	const int barW = 186 * _2X;
	const int barH = 26 * _2X;
	const int barX = DX - barW - 10 * _2X;
	const int barY = DY - GNBHEIGHT - 4 * _2X;

	// Dark ornate frame background with skull theme
	MemRect(barX, barY, barW, barH, 0x16121A);
	MemRectFrame(barX, barY, barW, barH, 0x6E1818);
	MemRectFrame(barX + 1, barY - 1, barW - 2, barH - 2, 0x9A2C2C);

	// Red Skull Icon on left of the title
	const int skX = barX + 10 * _2X;
	const int skY = barY - 7 * _2X;
	MemRect(skX - 5 * _2X, skY, 10 * _2X, 8 * _2X, 0xE03030);
	MemRect(skX - 3 * _2X, skY - 8 * _2X, 6 * _2X, 4 * _2X, 0xE03030);
	MemRect(skX - 3 * _2X, skY - 2 * _2X, 2 * _2X, 3 * _2X, 0x180404);
	MemRect(skX + 1 * _2X, skY - 2 * _2X, 2 * _2X, 3 * _2X, 0x180404);

	// Title: [검은 해골 성] (Black Skull Castle)
	char titleBuf[64];
	sprintf(titleBuf, "검은 해골 성  (%s)", def.name);
	SetFontColor(0xFFAAAA);
	LineTextStrSolid(titleBuf, barX + 20 * _2X, barY - 3 * _2X, DX, -1, -1, 0.44f);

	// Health bar slot
	const int innerX = barX + 8 * _2X;
	const int innerY = barY - 14 * _2X;
	const int innerW = barW - 16 * _2X;
	const int innerH = 8 * _2X;

	MemRect(innerX, innerY, innerW, innerH, 0x2A0A0A);

	// Eased Health Meter
	const float fillRatio = Max(0.0f, Min(1.0f, s_bossDisplayHp / (float)def.maxHp));
	const int fillW = (int)((float)innerW * fillRatio);

	if (fillW > 0) {
		MemRect(innerX, innerY, fillW, innerH, 0xD42222);
		MemRect(innerX, innerY, fillW, 2 * _2X, 0xFF6666);
		MemRectFrame(innerX, innerY, fillW, innerH, 0xFF9944);
	}

	// HP numbers: e.g. "4,320 / 5,000"
	char hpBuf[32];
	sprintf(hpBuf, "%d / %d", (int)(fillRatio * 5000.0f), 5000);
	SetFontColor(COLOR_WHITE);
	CenterTextStrSolid(hpBuf, innerX + innerW / 2, innerY - 1 * _2X, 0.36f);
}

// Main Entry Point for MD_PLAY in DrawDiorama
inline void Draw(int groundY, int invenTop) {
	groundY = VisualGroundY(groundY) + (int)GetStageWorldLift();
	const int arenaBottom = Max(0, groundY - 85 * _2X);
	SetSectionClip(0, DY, DX, DY - arenaBottom, false);

	DrawBackground(groundY, arenaBottom);
	DrawCastle(groundY);
	DrawEnemyFortress(groundY);
	DrawProjectiles();
	DrawExplosions();
	DrawDamageTexts();
	DrawBossUI();

	// Realtime combat sound and hit effects
	StageFoeShotDraw();

	UnSectionClip(false);
}

} // namespace BattleSiegeFortress
