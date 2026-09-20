#pragma once
#include <cmath>

// Optional CMF extension. Rotation and reflection are independent of the packed
// legacy flags. Hand coordinates are actor-local, X right / Y down.
struct CmfSwordPose {
    float handX, handY, angleDegrees, scale, opacity;
    bool flipX;
    bool valid;
};

inline float SwordAngleDelta(float from, float to)
{
    float delta = std::fmod(to - from, 360.0f);
    if (delta > 180.0f) delta -= 360.0f;
    if (delta < -180.0f) delta += 360.0f;
    return delta;
}

inline CmfSwordPose InterpolateSwordPose(const CmfSwordPose& a, const CmfSwordPose& b, float t)
{
    CmfSwordPose p = t < 0.5f ? a : b;
    p.handX = a.handX + (b.handX - a.handX) * t;
    p.handY = a.handY + (b.handY - a.handY) * t;
    p.angleDegrees = a.angleDegrees + SwordAngleDelta(a.angleDegrees, b.angleDegrees) * t;
    p.scale = a.scale + (b.scale - a.scale) * t;
    p.opacity = a.opacity + (b.opacity - a.opacity) * t;
    p.valid = a.valid && b.valid;
    return p;
}

// Legacy DrawImage uses a different corner anchor for each quarter turn.
// Convert that corner-based placement into an explicit hand attachment point.
inline CmfSwordPose DecodeLegacySwordPose(const signed short* part)
{
    CmfSwordPose p = {};
    if (part[0] != 108 && part[0] != 109) return p;
    const bool diagonal = part[0] == 108;
    const float w = diagonal ? 380.0f : 410.0f;
    const float h = diagonal ? 290.0f : 220.0f;
    const float gripX = diagonal ? 18.0f : 16.0f;
    const float gripY = diagonal ? 268.0f : 110.0f;
    const int flags = part[3];
    const int quarter = (flags & 6) >> 1;
    p.flipX = (flags & 1) != 0;
    p.scale = float((flags >> 6) + 1);
    p.opacity = float(4 - ((flags & 0x30) >> 4)) / 4.0f;
    float ax = 0, ay = 0;
    if (quarter == 1) { ax = p.flipX ? w : 0; ay = p.flipX ? 0 : h; }
    if (quarter == 2) { ax = w; ay = h; }
    if (quarter == 3) { ax = p.flipX ? 0 : w; ay = p.flipX ? h : 0; }
    const float radians = (p.flipX ? -1.0f : 1.0f) * quarter * 1.5707963267948966f;
    const float gx = (p.flipX ? w - gripX : gripX) - ax;
    const float gy = gripY - ay;
    p.handX = part[1] + (gx * std::cos(radians) - gy * std::sin(radians)) * p.scale;
    p.handY = part[2] + (gx * std::sin(radians) + gy * std::cos(radians)) * p.scale;
    // The original diagonal drawing is about 30 degrees above horizontal.
    p.angleDegrees = (p.flipX ? -1.0f : 1.0f) * (quarter * 90.0f + (diagonal ? 60.0f : 90.0f));
    p.valid = true;
    return p;
}

inline unsigned int SwordMotionSignature(const signed short* parts, int count)
{
    unsigned int hash = 2166136261u;
    for (int i = 0; i < count * 4; ++i) {
        hash ^= static_cast<unsigned short>(parts[i]);
        hash *= 16777619u;
    }
    return hash;
}
