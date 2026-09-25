#pragma once

#include <cmath>

namespace CastleWheels {

enum MoveKind { MOVE_WHEEL, MOVE_WALK, MOVE_FLOAT, MOVE_BODY };
struct MoveLayout { MoveKind kind; int partImg; int count; float u[4]; float partScale; };

static const MoveLayout kMove[20] = {
	// The values below describe the authored castle_moveN resources.  partScale
	// is the width of one part as a fraction of the rendered castle width.
	{MOVE_WHEEL, 0, 2,{.22f,.78f},            .15f}, //  0 wooden wheels
	{MOVE_WHEEL, 1, 2,{.20f,.80f},            .15f}, //  1 reinforced wheels
	{MOVE_FLOAT,18, 3,{.25f,.50f,.75f},       .09f}, //  2 hull thrusters
	{MOVE_WHEEL, 3, 3,{.16f,.50f,.84f},       .14f}, //  3 siege wheels
	{MOVE_WALK,  4, 1,{.50f},                 .42f}, //  4 snail foot
	{MOVE_WALK, 14, 4,{.18f,.39f,.61f,.82f},  .13f}, //  5 four stone feet
	{MOVE_WALK, 12, 2,{.31f,.69f},            .13f}, //  6 duck paddles
	{MOVE_WALK,  7, 2,{.40f,.60f},            .17f}, //  7 tree legs
	{MOVE_WALK,  8, 2,{.39f,.61f},            .16f}, //  8 mushroom roots
	{MOVE_WALK,  9, 2,{.40f,.60f},            .15f}, //  9 armoured feet
	{MOVE_WALK, 10, 2,{.35f,.65f},            .19f}, // 10 crab legs
	{MOVE_WALK, 11, 2,{.40f,.60f},            .15f}, // 11 mechanical feet
	{MOVE_WALK, 12, 2,{.40f,.60f},            .14f}, // 12 kettle feet
	{MOVE_WALK, 13, 2,{.40f,.60f},            .16f}, // 13 beast paws
	{MOVE_WALK, 14, 2,{.40f,.60f},            .17f}, // 14 stone legs
	{MOVE_FLOAT,15, 2,{.36f,.64f},            .18f}, // 15 cloud runners
	{MOVE_WALK, 16, 2,{.40f,.60f},            .16f}, // 16 dragon legs
	{MOVE_FLOAT,17, 3,{.25f,.50f,.75f},       .13f}, // 17 crystal engines
	{MOVE_FLOAT,18, 3,{.25f,.50f,.75f},       .11f}, // 18 blue thrusters
	{MOVE_FLOAT,18, 3,{.25f,.50f,.75f},       .10f}, // 19 hull thrusters
};

inline int ClampStage(int stage) { return Max(0, Min(stage, 19)); }
struct CompositeLayout { float bodyScale; int bodyX; int bodyY; };
static const CompositeLayout kComposite[20] = {
	{0.87890625f,62,32}, {0.87890625f,62,32}, {0.80708661f,99,32},
	{0.87890625f,62,32}, {0.80000000f,0,72},  {0.87890625f,62,32},
	{0.87890625f,62,32}, {0.87420043f,64,32}, {0.87890625f,62,32},
	{0.87890625f,62,32}, {0.87890625f,62,32}, {0.87890625f,62,32},
	{0.87890625f,62,32}, {0.87890625f,62,32}, {0.87326944f,65,32},
	{0.87890625f,62,32}, {0.87890625f,62,32}, {0.87890625f,62,32},
	{0.86315789f,70,32}, {0.87890625f,62,32},
};
inline bool IsCompositedMotion(int) { return true; }
inline const CompositeLayout& GetCompositeLayout(int stage) {
	return kComposite[ClampStage(stage)];
}
inline float GetPartScale(int stage, float castleW, float castleScale, float cellW)
{
	return castleW * castleScale * kMove[ClampStage(stage)].partScale / Max(1.0f, cellW);
}
inline float GetWheelRadius(int stage, float castleW, float castleScale)
{
	const int idx = ClampStage(stage);
	if (IsCompositedMotion(idx)) return 0.0f;
	const int img = CASTLE_MOVE0_IMG + kMove[idx].partImg;
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
	if (IsCompositedMotion(idx)) return;
	if (layout.kind == MOVE_BODY) return;
	const int img = CASTLE_MOVE0_IMG + layout.partImg;
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
		// Pin the top of the locomotion cell inside the chassis.  The body is
		// drawn after this pass, hiding the attachment seam and the transparent
		// headroom present in the generated 256x256 cells.
		const float attachTop = castleBottom + partH * .55f + bob;
		DrawImage(cellW, cellH, pose*cellW, 0,
			(int)(cx-partW*.5f), (int)attachTop,
			false, false, false, false, false, scale, sprite[img], img);
	}
	(void)groundY;
}

} // namespace CastleWheels
