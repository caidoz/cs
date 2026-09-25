#pragma once

#include <cmath>

namespace CastleWheels {

enum MoveKind { MOVE_WHEEL, MOVE_WALK, MOVE_FLOAT, MOVE_BODY };
struct MoveLayout { MoveKind kind; int count; float u[4]; float partScale; };

static const MoveLayout kMove[20] = {
	// The values below describe the authored castle_moveN resources.  partScale
	// is the width of one part as a fraction of the rendered castle width.
	{MOVE_WHEEL, 2,{.22f,.78f},            .15f}, //  0 wooden wheels
	{MOVE_WHEEL, 2,{.20f,.80f},            .15f}, //  1 reinforced wheels
	{MOVE_WHEEL, 2,{.19f,.81f},            .15f}, //  2 iron-rim wheels
	{MOVE_WHEEL, 3,{.16f,.50f,.84f},       .14f}, //  3 siege wheels
	{MOVE_WALK,  1,{.50f},                 .42f}, //  4 snail foot
	{MOVE_WHEEL, 3,{.15f,.50f,.85f},       .14f}, //  5 cog wheels
	{MOVE_WHEEL, 3,{.15f,.50f,.85f},       .14f}, //  6 royal wheels
	{MOVE_WALK,  2,{.34f,.66f},            .27f}, //  7 tree legs
	{MOVE_WALK,  2,{.34f,.66f},            .25f}, //  8 mushroom roots
	{MOVE_WALK,  2,{.34f,.66f},            .23f}, //  9 armoured feet
	{MOVE_WALK,  2,{.31f,.69f},            .28f}, // 10 crab legs
	{MOVE_WALK,  2,{.34f,.66f},            .23f}, // 11 mechanical feet
	{MOVE_WALK,  2,{.35f,.65f},            .22f}, // 12 paddle feet
	{MOVE_WALK,  2,{.34f,.66f},            .24f}, // 13 beast paws
	{MOVE_WALK,  2,{.34f,.66f},            .26f}, // 14 stone legs
	{MOVE_FLOAT, 2,{.32f,.68f},            .29f}, // 15 cloud runners
	{MOVE_WALK,  2,{.34f,.66f},            .24f}, // 16 dark iron legs
	{MOVE_FLOAT, 3,{.23f,.50f,.77f},       .20f}, // 17 crystal engines
	{MOVE_FLOAT, 3,{.23f,.50f,.77f},       .18f}, // 18 blue thrusters
	{MOVE_WALK,  2,{.34f,.66f},            .25f}, // 19 celestial legs
};

inline int ClampStage(int stage) { return Max(0, Min(stage, 19)); }
inline float GetPartScale(int stage, float castleW, float castleScale, float cellW)
{
	return castleW * castleScale * kMove[ClampStage(stage)].partScale / Max(1.0f, cellW);
}
inline float GetWheelRadius(int stage, float castleW, float castleScale)
{
	const int idx = ClampStage(stage);
	const int img = CASTLE_MOVE0_IMG + idx;
	if (kMove[idx].kind == MOVE_BODY) return 0.0f;
	if (!sprite[img]) LoadImg(img);
	if (!sprite[img]) return castleW * castleScale * .07f;
	const auto size = sprite[img]->getContentSize();
	const float cellW = kMove[idx].kind == MOVE_WHEEL ? size.width : size.width / 4.0f;
	const float scale = GetPartScale(idx, castleW, castleScale, cellW);
	return size.height * scale * .5f;
}
inline float GetSuspensionY() { return std::sin((float)frame * .22f) * 1.5f * (float)_2X; }
inline float GetWheelAngle() { return std::fmod((float)frame * 6.0f, 360.0f); }
inline void Update(float, float, float, int, float) {}

inline float GetBodyMotionY(int stage, bool moving)
{
	if (!moving) return 0.0f;
	const int idx = ClampStage(stage);
	const bool floating = kMove[idx].kind == MOVE_FLOAT;
	const float amplitude = (floating ? 3.0f : 1.5f) * (float)_2X;
	return std::sin((float)frame * (floating ? .10f : .18f)) * amplitude;
}

inline void DrawCastleWheels(int stage, float castleLeft, float castleBottom,
	float castleW, float castleScale, float groundY, bool isMoving)
{
	const int idx = ClampStage(stage);
	const MoveLayout& layout = kMove[idx];
	if (layout.kind == MOVE_BODY) return;
	const int img = CASTLE_MOVE0_IMG + idx;
	if (!sprite[img]) LoadImg(img);
	if (!sprite[img]) return;
	const auto size = sprite[img]->getContentSize();
	const int cellW = layout.kind == MOVE_WHEEL ? (int)size.width : (int)size.width / 4;
	const float scale = GetPartScale(idx, castleW, castleScale, (float)cellW);

	if (layout.kind == MOVE_WHEEL) {
		for (int n = 0; n < layout.count; ++n) {
			const float cx = castleLeft + layout.u[n] * castleW * castleScale;
			const float radius = size.width * scale * .5f;
			const float bob = isMoving ? std::sin((float)frame*.20f+n*1.7f)*1.2f*_2X : 0.0f;
			RotateImage((int)size.width, (int)size.height, 0, 0,
				(int)cx, (int)(groundY+radius+bob), false, GetWheelAngle(), 0, 0, scale,
				cocos2d::Vec2(.5f,.5f), sprite[img], img);
		}
		return;
	}

	const int cellH = (int)size.height;
	const float partW = cellW * scale;
	const float partH = cellH * scale;
	const float bob = layout.kind == MOVE_FLOAT ? std::sin((float)frame*.12f)*2.0f*_2X : 0.0f;
	for (int n = 0; n < layout.count; ++n) {
		const int pose = isMoving ? ((frame / 5) + n * 2) % 4 : 0;
		const float cx = castleLeft + layout.u[n] * castleW * castleScale;
		DrawImage(cellW, cellH, pose*cellW, 0,
			(int)(cx-partW*.5f), (int)(groundY+partH+bob),
			false, false, false, false, false, scale, sprite[img], img);
	}
	(void)castleBottom;
}

} // namespace CastleWheels
