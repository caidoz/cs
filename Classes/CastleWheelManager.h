#pragma once
// CastleWheelManager.h
// Manages wheel placement, rotation physics, suspension vibration,
// and dust particle effects for Mobile Castles (0~9).

#include <cmath>

namespace CastleWheels {

struct WheelLayout {
	int count;
	float u[6]; // X-ratio relative to castle width (0.0f = left, 1.0f = right)
};

// Wheel configurations tailored to each castle's width and architecture:
static const WheelLayout kWheelLayouts[10] = {
	// Castle 0: 416x448 (Stone keep) - 3 sturdy siege wheels
	{ 3, { 0.20f, 0.50f, 0.80f, 0.0f, 0.0f, 0.0f } },
	// Castle 1: 491x683 (2-Tier Fortress) - 3 wheels
	{ 3, { 0.18f, 0.50f, 0.82f, 0.0f, 0.0f, 0.0f } },
	// Castle 2: 507x818 (Turret Citadel) - 4 wheels
	{ 4, { 0.16f, 0.38f, 0.62f, 0.84f, 0.0f, 0.0f } },
	// Castle 3: 543x943 (Spire Bastion) - 4 wheels
	{ 4, { 0.15f, 0.38f, 0.62f, 0.85f, 0.0f, 0.0f } },
	// Castle 4: 553x1021 (Alchemy Stronghold) - 4 wheels
	{ 4, { 0.15f, 0.38f, 0.62f, 0.85f, 0.0f, 0.0f } },
	// Castle 5: 558x1127 (Clocktower Keep) - 4 wheels
	{ 4, { 0.14f, 0.38f, 0.62f, 0.86f, 0.0f, 0.0f } },
	// Castle 6: 561x1362 (Archmage Tower) - 4 wheels
	{ 4, { 0.14f, 0.38f, 0.62f, 0.86f, 0.0f, 0.0f } },
	// Castle 7: 676x1388 (Cathedral Citadel) - 5 heavy wheels
	{ 5, { 0.12f, 0.31f, 0.50f, 0.69f, 0.88f, 0.0f } },
	// Castle 8: 781x1481 (Grand Royal Palace) - 5 heavy wheels
	{ 5, { 0.10f, 0.30f, 0.50f, 0.70f, 0.90f, 0.0f } },
	// Castle 9: 922x1700 (Celestial High Fortress) - 6 massive siege dreadnought wheels
	{ 6, { 0.10f, 0.26f, 0.42f, 0.58f, 0.74f, 0.90f } },
};

static float s_wheelAngle = 0.0f;
static float s_suspensionY = 0.0f;
static float s_lastScrollDist = 0.0f;

// Dust particle emitter for spinning wheels
struct DustParticle {
	float x, y;
	float vx, vy;
	float size;
	float alpha;
	float life;
	float maxLife;
	bool active;
};

static const int MAX_WHEEL_DUST = 24;
static DustParticle s_dust[MAX_WHEEL_DUST] = {};
static int s_dustSpawnCounter = 0;

inline float GetWheelScale(float castleScale) {
	return 0.50f * (castleScale / 0.35f);
}

inline float GetWheelRadius(float castleScale) {
	// castle_wheel.png is 80x80 px -> radius = 40.0f * scale
	return 40.0f * GetWheelScale(castleScale);
}

inline float GetSuspensionY() {
	return s_suspensionY;
}

inline float GetWheelAngle() {
	return s_wheelAngle;
}

inline void Update(float currentScrollDist, float delta, float scrollSpeed, float castleScale) {
	const float wheelRadius = GetWheelRadius(castleScale);
	const float deltaDist = currentScrollDist - s_lastScrollDist;
	s_lastScrollDist = currentScrollDist;

	// Wheel rotation physically tied to ground travel (v = omega * r)
	if (wheelRadius > 0.0f && std::isfinite(deltaDist)) {
		s_wheelAngle += (deltaDist / wheelRadius) * (180.0f / 3.14159265f);
		s_wheelAngle = std::fmod(s_wheelAngle, 360.0f);
	}

	// Castle chassis suspension vibration (war machine rumble)
	if (scrollSpeed > 0.0f) {
		s_suspensionY = std::sin((float)frame * 0.22f) * 1.5f * (float)_2X;
	} else {
		s_suspensionY = 0.0f;
	}

	// Update dust particles
	for (int i = 0; i < MAX_WHEEL_DUST; ++i) {
		if (!s_dust[i].active) continue;
		s_dust[i].x += s_dust[i].vx * (delta * 60.0f);
		s_dust[i].y += s_dust[i].vy * (delta * 60.0f);
		s_dust[i].size += 0.15f * (delta * 60.0f);
		s_dust[i].life -= delta;
		if (s_dust[i].life <= 0.0f) {
			s_dust[i].active = false;
		} else {
			s_dust[i].alpha = (s_dust[i].life / s_dust[i].maxLife) * 0.65f;
		}
	}
}

inline void SpawnDust(float x, float y) {
	for (int i = 0; i < MAX_WHEEL_DUST; ++i) {
		if (!s_dust[i].active) {
			s_dust[i].active = true;
			s_dust[i].x = x + (float)((rand() % 9) - 4) * (float)_2X;
			s_dust[i].y = y + (float)(rand() % 4) * (float)_2X;
			s_dust[i].vx = -0.8f - (float)(rand() % 10) * 0.1f * (float)_2X;
			s_dust[i].vy = 0.3f + (float)(rand() % 8) * 0.1f * (float)_2X;
			s_dust[i].size = 3.0f * (float)_2X;
			s_dust[i].maxLife = 0.35f + (float)(rand() % 20) * 0.01f;
			s_dust[i].life = s_dust[i].maxLife;
			s_dust[i].alpha = 0.65f;
			break;
		}
	}
}

inline void DrawDust() {
	for (int i = 0; i < MAX_WHEEL_DUST; ++i) {
		if (!s_dust[i].active) continue;
		const int s = (int)s_dust[i].size;
		const int half = s / 2;
		// Soft earthy dust puff
		MemRect((int)s_dust[i].x - half, (int)s_dust[i].y + half, s, s, 0x8C7B65);
		MemRectFrame((int)s_dust[i].x - half, (int)s_dust[i].y + half, s, s, 0x6A5C4A);
	}
}

inline void DrawCastleWheels(int castleIdx, float castleLeft, float castleBottom,
                             float castleW, float castleScale, float groundY,
                             bool isMoving) {
	const int clampedIdx = Max(0, Min(castleIdx, 9));
	const WheelLayout& layout = kWheelLayouts[clampedIdx];
	const float wheelScale = GetWheelScale(castleScale);
	const float wheelRadius = GetWheelRadius(castleScale);

	// Rear wheel dust spawning
	if (isMoving && (++s_dustSpawnCounter % 4 == 0)) {
		float rearX = castleLeft + layout.u[0] * castleW * castleScale - wheelRadius * 0.6f;
		SpawnDust(rearX, groundY + 2.0f * (float)_2X);
	}

	for (int i = 0; i < layout.count; ++i) {
		const float u = layout.u[i];
		const float cx = castleLeft + u * castleW * castleScale;
		const float cy = groundY + wheelRadius;

		// 1. Wheel Ground Shadow
		ShadowImage(32 * _2X, 10 * _2X, 1 * _2X, 1 * _2X,
		            (int)(cx - 16 * _2X * wheelScale),
		            (int)(groundY + 4 * _2X * wheelScale),
		            SHADOW_IMG, wheelScale * 1.1f);

		// 2. Chassis Strut Bracket connecting castle chassis bottom to wheel axle
		const int strutW = 6 * _2X;
		const int strutH = Max(4, (int)(castleBottom - cy + 4 * _2X));
		MemRect((int)(cx - strutW / 2), (int)(castleBottom + 2 * _2X), strutW, strutH, 0x24201C);
		MemRectFrame((int)(cx - strutW / 2), (int)(castleBottom + 2 * _2X), strutW, strutH, 0x4A423A);

		// 3. Rotating Wheel Sprite (centered pivot)
		if (sprite[CASTLE_WHEEL_IMG]) {
			RotateImage(80, 80, 0, 0,
			            (int)cx, (int)cy,
			            false, s_wheelAngle, 0, 0, wheelScale,
			            cocos2d::Vec2(0.5f, 0.5f),
			            sprite[CASTLE_WHEEL_IMG], CASTLE_WHEEL_IMG);
		}

		// 4. Center Bronze Hub Cap with rivet
		const int hubR = Max(2, (int)(4 * _2X * wheelScale));
		MemRect((int)(cx - hubR), (int)(cy + hubR), hubR * 2, hubR * 2, 0xD4A034);
		MemRectFrame((int)(cx - hubR), (int)(cy + hubR), hubR * 2, hubR * 2, 0x6E4A10);
	}

	// Draw active dust puffs
	DrawDust();
}

} // namespace CastleWheels
