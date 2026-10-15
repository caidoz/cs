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
void CastlePartsNaturalSize(int castleLevel, float* w, float* h);
float CastlePartsWheelSink(void);
float CastlePartsGroundOffset(int castleLevel);
float CastlePartsRoomScale(void);
float CastlePartsLeftInset(int castleLevel);
float CastlePartsFloatOffset(int castleLevel);

namespace BattleMobileCastle {

static float s_scrollDist = 0.0f;
static float s_scrollSpeed = 24.0f;
static float s_hitFlash = 0.0f;

inline bool IsMoving() {
	//달리는 것과 싸우는 것은 별개다. 열차는 웨이브 사이에도 간다.
	//배경이 흐르는 조건(StageBgUpdate)과 같아야 차체 흔들림이 땅과
	//따로 놀지 않는다.
	return drawHandle == MD_PLAY;
}

inline int VisualGroundY(int layoutGroundY) {
	(void)layoutGroundY;
	// The full grid and lower menu determine the shared world position.
	return GetStageSceneGroundY();
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

	//성 보호막은 그리지 않는다.
	//
	//가방에 검 말고 다른 것이 있으면 성의 조립 네모를 따라 테두리를
	//두 겹 그렸다. 성은 열차 모양이라 네모와 안 맞고, 배경 위에 뜬
	//희미한 사각형으로만 보였다 - 이펙트가 아니라 디버그 상자로 읽힌다.
	//보호막을 다시 넣는다면 성 윤곽을 따라가는 그림이어야 한다.
	(void)castleTop;
	(void)naturalW;
	(void)naturalH;
}

inline void DrawCastle(int groundY) {
	//로비가 보여 주는 성을 그대로 쓴다. robin.castle 을 따르면 로비에서
	//1 단계를 보다가 전투에 들어가는 순간 열 층짜리로 바뀐다 - 같은 성이
	//아닌 것으로 읽힌다. 로비 화살표로 단계를 넘기면 전투도 같이 바뀐다.
	//
	//실제 진행을 따르게 하려면 여기와 LobbyCastleLevel 의 한 줄을 같이
	//robin.castle 로 되돌리면 된다.
	const int curCastle = Max(0, Min(gMobileCastleVisual, CASTLE_STAGE_CNT - 1));

	//조립표가 적어 둔 네모. 성 1 은 지붕이 방보다 높아 윗여유가 따로 있다.
	//여기서 빠뜨리면 CastlePartsDrawRect 가 네모 안에서 다시 가운데로
	//맞추면서 성이 땅에서 뜬다.
	float naturalW = 0.0f, naturalH = 0.0f;
	CastlePartsNaturalSize(curCastle + 1, &naturalW, &naturalH);

	//배율은 붙박이다. 방 폭 320 을 지킨다. 화면에 맞춰 줄이면 층이
	//쌓일수록 성이 작아져서, 키운 보람이 화면에서 사라진다. 높은 성은
	//위가 잘린다 - 잘리더라도 방은 제 크기로 보여야 한다.
	const float scale = CastlePartsRoomScale();
	const float castleW = naturalW * scale;
	const float castleH = naturalH * scale;

	const float shudderY = (s_hitFlash > 0.0f) ? ((rand() % 5) - 2) * 1.5f * (float)_2X : 0.0f;
	const float rumbleY = IsMoving() ? (std::sin((float)frame * 0.40f) * 1.0f * (float)_2X) : 0.0f;
	//성 1 의 들여쓰기를 뺀다. 안 빼면 그만큼 왼쪽이 비고, 그 폭이
	//고스란히 몬스터 자리에서 깎인다.
	const float castleLeft = StageBg::kCastleLeft
	                       - CastlePartsLeftInset(curCastle + 1) * scale;
	const float groundOffset = CastlePartsGroundOffset(curCastle + 1);
	const float assemblyBottom = (float)groundY -
		(groundOffset >= 0.0f ? groundOffset * scale : StageBg::kCastleDropPx)
		- StageBg::kCastleGroundingPx
		+ shudderY + rumbleY;
	const float yTop = assemblyBottom + castleH;

	CastlePartsDrawRect(curCastle + 1, (int)castleLeft, (int)yTop, (int)castleW, (int)castleH);

	DrawInventoryCastleReflections(curCastle, castleLeft, yTop, naturalW, naturalH, scale);

	//성 안의 사람은 로비와 똑같이 세운다. 전에는 여기서만 네 자리에
	//party 를 세우고 크기 기준도 달라서(512 대 922), 같은 동료가 두
	//화면에서 두 배 차이로 나왔다. 성이 같으면 안에 있는 사람도 같다.
	//나가는 동료만 이 안에서 1.5 배가 된다.
	CastleCrewDrawAt(castleLeft, yTop + CastlePartsFloatOffset(curCastle + 1) * scale,
	                 naturalW, naturalH, scale, curCastle, true);
}

//다리 옆 체력 패널. 어두운 반투명 틀과 픽셀 하이라이트를 공유한다.
inline void DrawDuelHpBar(int x, int y, int w, long long hp, long long maxHp,
                         const char* title, bool enemy) {
	const int px=Max(1,_2X), h=34*px;
	const bool compact=w<64*px;
	const long long maximum=Max(0LL,maxHp), current=Max(0LL,Min(hp,maximum));
	SetAlpha(20);
	MemRect(x+2*px,y-2*px,w,h,0x050912);
	MemRect(x,y,w,h,0x101D30);
	SetAlpha(ALPHA_MAX);
	MemRectFrame(x+px,y-px,w-2*px,h-2*px,enemy?0xB8836D:0xB5CDE0);
	MemRect(x+4*px,y-2*px,w-8*px,px,enemy?0xEAC1A2:0xDBE9F2);
	const int trackX=x+5*px,trackY=y-(compact?14:17)*px,trackW=w-10*px,trackH=(compact?8:11)*px;
	MemRect(trackX-px,trackY+px,trackW+2*px,trackH+2*px,0x060D19);
	MemRect(trackX,trackY,trackW,trackH,enemy?0x42232B:0x1C3542);
	const int fill=maximum>0?(int)(trackW*((double)current/maximum)):0;
	if(fill>0) {
		MemRect(trackX,trackY,fill,trackH,enemy?0xCB4659:0x2798AF);
		MemRect(trackX,trackY,fill,3*px,enemy?0xFF8C82:0x84E4DB);
		MemRect(trackX,trackY-trackH+2*px,fill,2*px,enemy?0x90334D:0x186479);
		if(fill>2*px) MemRect(trackX+fill-px,trackY-px,px,trackH-2*px,enemy?0xFFC3A3:0xC4FFF0);
	}
	char value[96];
	if(compact) sprintf(value,"%d%%",maximum>0?(int)(100.0*current/maximum):0);
	else sprintf(value,"%lld / %lld",current,maximum);
	SetFontColor(COLOR_WHITE);
	CenterTextStrSolid(value,x+w/2,trackY-px,
		Min((compact?.34f:.43f)*px,(trackW-4.0f*px)/Max(1.0f,StringWidth(value,1.0f))));
	if(compact) {
		char a[32],b[32];
		if(current>=1000000) sprintf(a,"%.3gM",current/1000000.0);
		else if(current>=1000) sprintf(a,"%.3gK",current/1000.0);
		else sprintf(a,"%lld",current);
		if(maximum>=1000000) sprintf(b,"%.3gM",maximum/1000000.0);
		else if(maximum>=1000) sprintf(b,"%.3gK",maximum/1000.0);
		else sprintf(b,"%lld",maximum);
		sprintf(value,"%s / %s",a,b);
		CenterTextStrSolid(value,x+w/2,y-25*px,
			Min(.3f*px,(w-8.0f*px)/Max(1.0f,StringWidth(value,1.0f))));
		sprintf(value,"%s",title);
	} else sprintf(value,"%s   %d%%",title,maximum>0?(int)(100.0*current/maximum):0);
	CenterTextStrSolid(value,x+w/2,y-5*px,
		Min(.5f*px,(w-12.0f*px)/Max(1.0f,StringWidth(value,1.0f))));
}

//다리 기준으로 좌우에 배치한다. 가운데 인벤토리에는 겹치지 않는다.
inline void DrawDuelHpBars(int groundY, int inventoryWidth) {
	// Leave the central inventory fully visible and keep both cards beside the bridge.
	const int gap=8*_2X, w=Max(32,(DX-inventoryWidth)/2-2*gap), y=groundY-8*_2X;
	// The castle's health pool is the player health that receives enemy attacks.
	DrawDuelHpBar(gap,y,w,ao[PLAYER].hp,ao[PLAYER].maxhp,"성 총 체력",false);
	long long hp=0,maximum=0;
	for(int i=ENEMY;i<NEUTRAL;++i) {
		const OBJECT& foe=ao[i];
		if(!foe.active || foe.type<=0 || foe.mom!=i || foe.moveHandler==REGENMOVE) continue;
		maximum+=Max(0LL,foe.maxhp);
		if(!foe.dead) hp+=Max(0LL,Min(foe.hp,foe.maxhp));
	}
	DrawDuelHpBar(DX-gap-w,y,w,hp,maximum,"적 총 체력",true);
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
	// Foreground, rail, castle and combatants follow the same menu transition.
	groundY = VisualGroundY(groundY);
	//장면은 화면 바닥까지 그린다.
	//
	//예전에는 딛는 줄 아래 170 픽셀에서 잘랐다. 그 아래는 아무것도 안
	//그려져 검게 남는데, 인벤토리가 그 위를 덮어 주리라 본 것이다. 판
	//바닥을 걷어내면서 그 검은 자리가 그대로 드러났다. 선로 아래 교각과
	//안개가 화면 끝까지 이어지는 편이 낫다.
	const int arenaBottom = 0;
	SetSectionClip(0, DY, DX, DY - arenaBottom, false);

	DrawBackground(groundY, arenaBottom);
	DrawCastle(groundY);
	DrawBossMonster(groundY);

	UnSectionClip(false);
}

} // namespace BattleMobileCastle
