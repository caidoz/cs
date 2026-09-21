#pragma once
// CastleWheelManager.h
// Draws the visible front wheels as part of each Mobile Castle (0~9).

#include <cmath>

namespace CastleWheels {

struct WheelLayout {
	int count;
	float u[8]; // X-ratio relative to castle width (0.0f = left, 1.0f = right)
};

// Wheel configurations tailored to each castle's width and architecture:
static const WheelLayout kWheelLayouts[10] = {
	// Castle 0: 416x448 (Stone keep) - 3 sturdy siege wheels
	{ 2, { 0.20f, 0.80f } },
	// Castle 1: 491x683 (2-Tier Fortress) - 3 wheels
	{ 2, { 0.18f, 0.82f } },
	// Castle 2: keep the silhouette readable with only a front and rear wheel
	{ 2, { 0.17f, 0.83f } },
	// Castle 3: 543x943 (Spire Bastion) - 4 wheels
	{ 3, { 0.15f, 0.50f, 0.85f } },
	// Castle 4: 553x1021 (Alchemy Stronghold) - 4 wheels
	{ 3, { 0.15f, 0.50f, 0.85f } },
	// Castle 5: 558x1127 (Clocktower Keep) - 4 wheels
	{ 3, { 0.14f, 0.50f, 0.86f } },
	// Castle 6: 561x1362 (Archmage Tower) - 4 wheels
	{ 4, { 0.12f, 0.37f, 0.63f, 0.88f } },
	// Castle 7: 676x1388 (Cathedral Citadel) - 5 heavy wheels
	{ 4, { 0.11f, 0.37f, 0.63f, 0.89f } },
	// Castle 8: 781x1481 (Grand Royal Palace) - 5 heavy wheels
	{ 4, { 0.10f, 0.36f, 0.64f, 0.90f } },
	// Castle 9: 922x1700 (Celestial High Fortress) - 6 massive siege dreadnought wheels
	{ 4, { 0.09f, 0.36f, 0.64f, 0.91f } },
};

static float s_wheelAngle = 0.0f;
static float s_suspensionY = 0.0f;
static float s_lastScrollDist = 0.0f;

inline float GetWheelScale(int castleIdx, float castleScale) {
	// Wheel zoom follows the castle zoom exactly.  The previous reference-scale
	// division cancelled part of the lobby camera zoom and made the wheels look
	// detached from the castle.
	const int tierIdx = Max(0, Min(castleIdx, 9));
	const float tier = 1.0f + tierIdx / 18.0f;
	return 0.38f * tier * castleScale;
}

inline float GetWheelRadius(int castleIdx, float castleScale) {
	// All ten authored resources are normalized to 128x128.
	return 64.0f * GetWheelScale(castleIdx, castleScale);
}

inline float GetSuspensionY() {
	return s_suspensionY;
}

inline float GetWheelAngle() {
	return s_wheelAngle;
}

inline void DrawWheelCentered(int wheelImg, float centerX, float centerY,
	float scale, float angle) {
	if (!sprite[wheelImg]) return;
	// RotateImage positions the supplied anchor at (x,y).  A 0.5/0.5 anchor
	// therefore makes the axle the invariant rotation pivot.
	RotateImage(128, 128, 0, 0,
		(int)centerX, (int)centerY, false, angle, 0, 0, scale,
		cocos2d::Vec2(0.5f, 0.5f), sprite[wheelImg], wheelImg);
}

inline void Update(float currentScrollDist, float delta, float scrollSpeed, int castleIdx, float castleScale) {
	(void)castleIdx;
	(void)castleScale;
	s_lastScrollDist = currentScrollDist;

	// This manager is updated only in MD_PLAY.  Advance unconditionally so UI,
	// offer and auto-battle state can never freeze a wheel that is on screen.
	if (delta > 0.0f) {
		s_wheelAngle += 180.0f * delta;
		s_wheelAngle = std::fmod(s_wheelAngle, 360.0f);
	}

	// Castle chassis suspension vibration (war machine rumble)
	if (scrollSpeed > 0.0f) {
		s_suspensionY = std::sin((float)frame * 0.22f) * 1.5f * (float)_2X;
	} else {
		s_suspensionY = 0.0f;
	}

}

inline void DrawCastleWheels(int castleIdx, float castleLeft, float castleBottom,
                             float castleW, float castleScale, float groundY,
                             bool isMoving) {
	const int clampedIdx = Max(0, Min(castleIdx, 9));
	const WheelLayout& layout = kWheelLayouts[clampedIdx];
	const float wheelScale = GetWheelScale(clampedIdx, castleScale);
	const float wheelRadius = GetWheelRadius(clampedIdx, castleScale);
	const int wheelImg = CASTLE_WHEEL0_IMG + clampedIdx;
	if (!sprite[wheelImg]) LoadImg(wheelImg);
	// MD_PLAY uses the global render frame as the single source of truth.
	// At 30 fps this is 180 degrees/sec and cannot be stopped by combat/UI state.
	const float drawAngle = drawHandle == MD_PLAY
		? std::fmod((float)frame * 6.0f, 360.0f)
		: s_wheelAngle;

	for (int i = 0; i < layout.count; ++i) {
		const float u = layout.u[i];
		const float cx = castleLeft + u * castleW * castleScale;
		const float terrainBob = isMoving
			? std::sin(drawAngle * 3.14159265f / 180.0f + i * 1.7f) * 1.2f * _2X
			: 0.0f;
		const float cy = groundY + wheelRadius + terrainBob;

		// Axle bracket is part of the castle assembly, not a world/tile object.
		const int strutW = 6 * _2X;
		const int strutH = Max(4, (int)(castleBottom - cy + 4 * _2X));
		MemRect((int)(cx - strutW / 2), (int)(castleBottom + 2 * _2X), strutW, strutH, 0x24201C);
		MemRectFrame((int)(cx - strutW / 2), (int)(castleBottom + 2 * _2X), strutW, strutH, 0x4A423A);

		// Front-side wheel sprite. There is intentionally no rear wheel pass.
		DrawWheelCentered(wheelImg, cx, cy, wheelScale, drawAngle);

		// The authored wheels are close to rotationally symmetric.  A small bolt
		// fixed to the wheel face makes the centre-pivot rotation readable.
		const float angleRad = drawAngle * 3.14159265f / 180.0f;
		const float markerR = wheelRadius * 0.56f;
		const int markerSize = Max(2, (int)(3.0f * _2X * wheelScale));
		const int markerX = (int)(cx + std::cos(angleRad) * markerR);
		const int markerY = (int)(cy + std::sin(angleRad) * markerR);
		MemRect(markerX - markerSize / 2, markerY + markerSize / 2,
			markerSize, markerSize, 0xFFF1A0);
		MemRectFrame(markerX - markerSize / 2, markerY + markerSize / 2,
			markerSize, markerSize, 0x8B5A10);

		// 4. Center Bronze Hub Cap with rivet
		const int hubR = Max(2, (int)(4 * _2X * wheelScale));
		const int hubColor = clampedIdx < 3 ? 0x8A6338 : clampedIdx < 7 ? 0xB77A35 : 0xFFD45A;
		const int rimColor = clampedIdx < 3 ? 0x4B3422 : clampedIdx < 7 ? 0x80552A : 0xA86F12;
		MemRect((int)(cx - hubR), (int)(cy + hubR), hubR * 2, hubR * 2, hubColor);
		MemRectFrame((int)(cx - hubR), (int)(cy + hubR), hubR * 2, hubR * 2, rimColor);
	}
}

} // namespace CastleWheels
