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


	//성 안의 사람은 로비와 똑같이 세운다. 전에는 여기서만 네 자리에
	//party 를 세우고 크기 기준도 달라서(512 대 922), 같은 동료가 두
	//화면에서 두 배 차이로 나왔다. 성이 같으면 안에 있는 사람도 같다.
	//나가는 동료만 이 안에서 1.5 배가 된다.
	CastleCrewDrawAt(castleLeft, yTop + CastlePartsFloatOffset(curCastle + 1) * scale,
	                 naturalW, naturalH, scale, curCastle, true);
}

//다리 옆 체력/방어력 패널. 어두운 반투명 틀과 픽셀 하이라이트를 공유한다.
inline void DrawDuelHpBar(int x, int y, int w, long long hp, long long maxHp,
 const char* title, bool enemy, long long shield=0, long long maxShield=0,long long power=-1) {
 const int extra=power>=0?44:0,h=124+extra,trim=enemy?0xD09A65:0xD8BC72;
 const long long maxima[2]={Max(0LL,maxShield),Max(0LL,maxHp)};
 const long long current[2]={Max(0LL,Min(shield,maxima[0])),Max(0LL,Min(hp,maxima[1]))};
 SetAlpha(ALPHA_MAX);
 MemRect(x+3,y-3,w,h,0x07101C);
 MemRect(x,y,w,h,trim);MemRect(x+2,y-2,w-4,h-4,0x142840);
 MemRect(x+5,y-5,w-10,23,0x243A52);
 SetFontColor(0xF8E1A3);
 const char* name=title;
 CenterTextStrSolid(name,x+w/2,y-16,Min(.62f,(w-12.0f)/Max(1.0f,StringWidth(name,1))));
 if(power>=0) {
  char stat[96];sprintf(stat,"총체력 %lld",maxima[1]);
  CenterTextStrSolid(stat,x+w/2,y-35,Min(.5f,(w-10.0f)/Max(1.0f,StringWidth(stat,1))));
  sprintf(stat,"전투력 %lld",power);
  CenterTextStrSolid(stat,x+w/2,y-55,Min(.5f,(w-10.0f)/Max(1.0f,StringWidth(stat,1))));
 }
 for(int row=0;row<2;++row) {
  const int top=y-33-extra-row*43,tx=x+7,tw=w-14;
  SetFontColor(row==0?0x94D8FF:enemy?0xFFB3A2:0xA6EAC2);
  CenterTextStrSolid(row==0?"방어":"체력",x+w/2,top-3,.52f);
  MemRect(tx-1,top-16,tw+2,21,0x091322);
  const int fill=maxima[row]>0?(int)(tw*(double)current[row]/maxima[row]):0;
  if(fill>0) {
   const int color=row==0?0x358DBD:enemy?0xBA4C62:0x268D67;
   MemRect(tx,top-17,fill,18,color);
   MemRect(tx,top-17,fill,3,row==0?0x83D8EF:enemy?0xF99C92:0x7ADBB1);
  }
  char value[80],v[2][24];
  for(int k=0;k<2;++k) {
   const long long number=k==0?current[row]:maxima[row];
   if(number>=1000000) sprintf(v[k],"%.1fM",number/1000000.0);
   else if(number>=10000) sprintf(v[k],"%.1fK",number/1000.0);
   else sprintf(v[k],"%lld",number);
  }
  sprintf(value,"%s / %s",v[0],v[1]);SetFontColor(COLOR_WHITE);
  CenterTextStrSolid(value,x+w/2,top-27,Min(.55f,(tw-2.0f)/Max(1.0f,StringWidth(value,1))));
 }
}

//다리 기준으로 좌우에 배치한다. 가운데 인벤토리에는 겹치지 않는다.
inline void DrawDuelHpBars(int groundY, int inventoryWidth) {
	// Leave the central inventory fully visible and keep both cards beside the bridge.
	const int gap = 8 * _2X, w = Max(32, (DX - inventoryWidth) / 2 - 2 * gap), y = groundY - 8 * _2X;
	// The castle's health pool is the player health that receives enemy attacks.
	const long long playerMaxHp = Max(ao[PLAYER].maxhp, ao[PLAYER].ps[PS_HP]);
	DrawDuelHpBar(gap, y, w, ao[PLAYER].hp, playerMaxHp, "아군 요새", false,
	              ao[PLAYER].shield, ao[PLAYER].shieldMax,GetCombatPower(&ao[PLAYER]));
	//---- 적도 방어력과 체력을 따로 센다 ----
	//
	//체력만 세고 있었다. 성 쪽은 방어력 · 체력 두 단인데 적 쪽은 한 단
	//이라, 나란히 선 두 창이 서로 다른 것을 재고 있었다.
	long long hp = 0, maximum = 0, armor = 0, armorMax = 0,power=0;
	for (int i = ENEMY; i < NEUTRAL; ++i) {
		const OBJECT& foe = ao[i];
		if (!foe.active || foe.type <= 0 || foe.mom != i || foe.moveHandler == REGENMOVE) continue;
		maximum += Max(0LL, foe.maxhp);
		armorMax += Max(0LL, (long long)foe.shieldMax);
		if(!foe.dead) power+=GetCombatPower((OBJECT*)&foe);
		if (!foe.dead) {
			hp += Max(0LL, Min(foe.hp, foe.maxhp));
			armor += Max(0LL, Min((long long)foe.shield, (long long)foe.shieldMax));
		}
	}
	DrawDuelHpBar(DX - gap - w, y, w, hp, maximum, "적 요새", true,
	              armor, armorMax,power);
}

inline void DrawBossMonster(int groundY) {
	int foe = StageRtFoe();
	if(foe<0) for(int obj=ENEMY;obj<NEUTRAL;++obj)
		if(ao[obj].active && ao[obj].moveHandler==REGENMOVE && ao[obj].mom==obj) {foe=obj;break;}
	if (foe < 0) return;
	const OBJECT* monster = &ao[foe];
	const float targetX = Min((float)DX - 32 * _2X, 256.0f * _2X);
	const float entry=monster->moveHandler==REGENMOVE
		? Max(0.0f,Min(1.0f,(float)monster->frame/(FPS/2))) : 1.0f;
	const float bossX=targetX+((float)DX+160*_2X-targetX)*(1.0f-entry);
	StageCombatRecordActor(foe,bossX,groundY-3*_2X,enemyIconZoom[monster->type]*1.75f,true);
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
