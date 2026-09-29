#pragma once
// StageBackground.h
// 성열차가 달리는 지역의 배경. 원경 - 보스 - 중경 - 선로 를 서로 다른
// 속도로 흘려 깊이를 낸다.
//
// [수치의 출처]
// 바탕화면 layer 폴더가 원본이다. 지역마다 layout.json 한 장이 있고,
// 거기서 정한 값을 설계 좌표(폭 1088, y 는 아래로 +)로 그대로 들고 온다.
// 화면에 맞추는 일은 여기서만 한다. 그림은 tools/stagebg/bake_regions.py
// 가 굽는다.
//
// [지역이 달라도 틀은 같다]
// 두 지역의 layout.json 은 레이어 구성 · 화면 좌표 · 흐르는 속도가 같다.
// 다른 것은 그림, 심연색, 그리고 보스가 무엇을 하느냐뿐이다. 그래서 틀은
// 상수로 한 벌만 두고 다른 것만 표로 뺐다. 지역이 늘면 kRegion 에 한 줄,
// ImgDef.h 의 STAGEBG_REGION_CNT 에 하나, 굽는 표에 한 줄이면 된다.
//
// [왜 좌우 반전 교대인가]
// 선로 그림은 한 장을 이어 붙이면 이음새가 보인다. 홀수 번째 장을 좌우로
// 뒤집으면 같은 가장자리끼리 맞닿아 레일 높이와 알파가 이어진다. 원경과
// 중경도 같은 방식이라 반복이 덜 눈에 띈다.
//
// [왜 배율이 하나인가]
// 레이어마다 따로 맞추면 다리와 절벽의 크기 관계가 깨진다. 한 배율로
// 묶고, 화면 위쪽이 비지 않을 만큼만 키운다. 넘치는 폭은 어차피 흐른다.

#include <cmath>

namespace StageBg {

// ---- 지역이 공유하는 설계 좌표 (layer/*/layout.json) ----
static const float kDesignW  = 1088.0f;
static const float kSkyW     = 1088.0f, kSkyH = 1445.0f;     // 원경 · 중경
static const float kRailW    = 1088.0f, kRailH = 438.0f;
static const float kRailTopY =  840.0f;
//선로 그림에서 레일 윗면은 위에서 6.35% 지점이다. 여기가 딛는 줄이다.
static const float kDeckY    = kRailTopY + kRailH * 0.0635f; // 867.8

// 흐르는 속도. 설계 폭 1088 기준 초당 픽셀.
static const float kSpeedFar = 2.2f, kSpeedMid = 15.4f, kSpeedRail = 110.0f;

//성의 왼쪽 여백. 성은 왼쪽에 서고 오른쪽이 싸우는 자리다. 로비와 전투가
//같은 값을 써야 넘어갈 때 성이 옆으로 미끄러지지 않는다.
static const float kCastleLeft = 6.0f * (float)_2X;

//성을 딛는 줄보다 이만큼 내려 놓는다. 조립표대로 바퀴를 줄에 딱 맞추면
//성이 선로 위에 얹힌 것이 아니라 떠 있는 것으로 보인다. 조금 파묻어야
//무게가 실린다. 화면 픽셀이고, 성 배율이 붙박이라 층수와 상관없이 같다.
static const float kCastleDropPx = 32.0f;

//장면이 딛는 줄의 기준 높이. 배율은 여기서만 정한다.
//
//로비와 전투가 우연이 아니라 이 값으로 같은 자리에 선다 - 로비 카메라가
//성을 놓는 자리를 세어 보면 화면 높이의 0.31 쯤이고, 전투도 같은 값을
//쓴다(VisualGroundY).
static const float kGroundRef = 0.31f;

// ---- 지역마다 다른 것 ----

// 보스의 눈 연출.
//  Swap - 감은 그림으로 통째로 갈아 끼운다 (늪지대 개구리).
//  Glow - 평소 그림 위에 발광만 옅게서 진하게 얹는다 (계곡 웜).
enum BossFx { FxSwap, FxGlow };

struct Region {
	int   abyss;                  // 화면 아래를 채우는 색
	int   sky;                    // 원경 위가 모자랄 때 잇는 색
	float bossX, bossY;           // 보스 그림 좌상단 (설계 좌표)
	float bossW, bossH;
	float motionSec;              // 몸이 한 번 부풀었다 가라앉는 데 걸리는 시간
	float scaleX, scaleY;         // 그때 늘어나는 비율
	float riseY;                  // 그때 떠오르는 높이 (설계 픽셀)
	BossFx fx;
	float fxSec;                  // 눈 연출 한 주기
	float fxFrom, fxTo;           // Swap 일 때 감고 있는 구간
};

static const Region kRegion[] = {
	// 늪지대 - 개구리가 숨을 쉬고 6.7 초마다 한 번 눈을 감는다.
	{ 0x81B0BC, 0x4AA1D5, 512.0f, 155.0f, 560.0f, 373.333f,
	  4.2f, 0.009f, 0.018f, 0.0f, FxSwap, 6.7f, 6.40f, 6.62f },
	// 금단의 계곡 - 웜은 거의 움직이지 않고 눈만 3.8 초 주기로 밝아진다.
	{ 0xA68D91, 0xE9CFAF, 350.0f, 125.0f, 780.0f, 520.0f,
	  4.2f, 0.004f, 0.004f, 2.0f, FxGlow, 3.8f, 0.0f, 0.0f },
};

//보스 그림의 기준점. 그림 좌상단에서 잰 비율이라 밑동이 안개에 박힌 채로
//가슴만 오르내린다. 두 지역이 같은 값을 쓴다.
static const float kBossAncU = 0.5f, kBossAncV = 0.85f;

//달린 시간과 흐른 시간을 따로 센다. 성이 멈추면 배경도 멈추지만 보스는
//계속 숨쉬고 눈을 깜빡여야 살아 있어 보인다.
//
//[왜 헤더에 두지 않나]
//static 으로 두면 이 헤더를 넣은 .cpp 마다 제 복사본을 갖는다. 시계를
//굴리는 쪽(Func_Graphics.cpp)과 로비를 그리는 쪽(Func_Draw.cpp)이 서로
//다른 값을 보게 되어, 로비 배경이 영영 0 초에 멈춰 있었다.
//정의는 Func_Graphics.cpp 한 군데다.
extern float s_travel;
extern float s_clock;
extern int   s_region;

inline const Region& Cur(void) {
	return kRegion[Max(0, Min(s_region, STAGEBG_REGION_CNT - 1))];
}

inline int Img(int slot) {
	return STAGEBG_FIRST_IMG +
	       Max(0, Min(s_region, STAGEBG_REGION_CNT - 1)) * STAGEBG_PER_REGION + slot;
}
enum { SlotFar, SlotMid, SlotRail, SlotBoss, SlotBossFx };

//판 다섯 개가 한 주기(3 일)다. 한 주기를 한 지역에서 달리고 다음 주기에
//다음 지역으로 넘어간다. 한 판마다 갈아타면 같은 사흘인데 배경만 바뀌어
//어디까지 왔는지가 안 읽힌다.
inline void SetRegionForStage(int stage) {
	s_region = (stage / STAGE_PER_CYCLE) % STAGEBG_REGION_CNT;
}

inline void Update(float dt, bool moving) {
	if (!std::isfinite(dt) || dt <= 0.0f) return;
	if (dt > 0.1f) dt = 0.1f;
	s_clock += dt;
	if (moving) s_travel += dt;
}

//C 의 % 는 음수에서 음수를 낸다. 타일 번호는 음수로도 계속 이어져야
//하므로 직접 접는다.
inline int WrapEven(int q) { return ((q % 2) + 2) % 2; }

inline float Scale(void) {
	//배율은 붙박이다. 딛는 줄은 출정 준비에서 들리고 로비에서는 카메라를
	//따라 오르내리는데, 배율까지 같이 변하면 성 크기는 그대로인 채 배경만
	//줌해서 어긋나 보인다.
	//
	//폭을 채우되, 기준 높이에서 원경 꼭대기가 화면 위를 넘을 만큼 키운다.
	//땅이 기준보다 올라가 원경 위가 모자라면 배율을 키우는 대신 하늘색을
	//이어 붙인다(Draw). 배율로 메우면 카메라를 밀 때마다 배경이 숨쉰다.
	const float byWidth = (float)DX / kDesignW;
	const float byRef   = (float)Max(1, DY - (int)(DY * kGroundRef)) / kDeckY;

	return byWidth > byRef ? byWidth : byRef;
}

//설계 y 를 화면 y 로 옮긴다. 화면 y 는 사각형의 윗변이고 위로 갈수록 크다.
inline int TopOf(int groundY, float designY, float s) {
	return groundY + (int)((kDeckY - designY) * s);
}

//한 주기 안의 0 -> 1 -> 0. 숨쉬기처럼 끝에서 느려진다.
inline float Swell(float sec) {
	return (1.0f - std::cos(s_clock / sec * 6.2831853f)) * .5f;
}

inline void Layer(int img, float designW, float designTopY, float speed,
                  int groundY, float s) {
	if (!sprite[img]) LoadImg(img);
	if (!sprite[img]) return;

	const auto sz = sprite[img]->getContentSize();
	if (sz.width < 1.0f) return;

	const float tileW = designW * s;
	const float zoom  = tileW / sz.width;
	const float dist  = speed * s_travel * s;

	const int   q     = (int)std::floor(dist / tileW);
	const float first = -(dist - q * tileW);
	const int   top   = TopOf(groundY, designTopY, s);

	for (int j = 0; first + j * tileW < (float)DX; j++) {
		DrawImage((int)sz.width, (int)sz.height, 0, 0,
		          (int)(first + j * tileW), top,
		          WrapEven(q + j) != 0, false, false, false, false,
		          zoom, sprite[img], img);
	}
}

//보스는 원경에 붙어 있다. 한 마리뿐이라 반복하지 않고, 원경 타일 중
//뒤집히지 않은 것 위에만 얹는다. 뒤집힌 타일에 얹으면 얼굴이 돌아간다.
inline void Boss(int groundY, float s) {
	const Region& r = Cur();

	const int baseImg = Img(SlotBoss);
	const int fxImg   = Img(SlotBossFx);
	if (!sprite[baseImg]) LoadImg(baseImg);
	if (!sprite[fxImg])   LoadImg(fxImg);
	if (!sprite[baseImg]) return;

	const auto sz = sprite[baseImg]->getContentSize();
	if (sz.width < 1.0f) return;

	const float swell = Swell(r.motionSec);
	const float w = r.bossW * s * (1.0f + swell * r.scaleX);
	const float h = r.bossH * s * (1.0f + swell * r.scaleY);

	//눈 연출. 감는 쪽은 구간 안에서만 갈아 끼우고, 밝아지는 쪽은 늘
	//얹되 진하기가 오르내린다.
	const float phase = std::fmod(s_clock, r.fxSec);
	const bool  swap  = r.fx == FxSwap && phase > r.fxFrom && phase < r.fxTo;
	const int   glow  = r.fx == FxGlow && sprite[fxImg]
	                  ? 4 + (int)(Swell(r.fxSec) * 28.0f) : 0;

	const int   img   = (swap && sprite[fxImg]) ? fxImg : baseImg;

	const float tileW = kSkyW * s;
	const float dist  = kSpeedFar * s_travel * s;
	const int   q     = (int)std::floor(dist / tileW);
	const float first = -(dist - q * tileW);

	for (int j = 0; first + j * tileW < (float)DX; j++) {
		if (WrapEven(q + j) != 0) continue;

		//기준점을 고정한 채 부풀린다.
		const float ax = first + j * tileW + r.bossX * s + r.bossW * s * kBossAncU;
		const float ay = (float)TopOf(groundY, r.bossY - r.riseY * swell, s)
		               - r.bossH * s * kBossAncV;
		const int   x  = (int)(ax - w * kBossAncU);
		const int   y  = (int)(ay + h * kBossAncV);

		DrawImageScale((int)sz.width, (int)sz.height, 0, 0, x, y,
		               false, false, false, false, false,
		               w / sz.width, h / sz.height, sprite[img], img);

		if (glow > 0) {
			SetAlpha(glow);
			DrawImageScale((int)sz.width, (int)sz.height, 0, 0, x, y,
			               false, false, false, false, false,
			               w / sz.width, h / sz.height, sprite[fxImg], fxImg);
			SetAlpha(32);
		}
	}
}

// 전투 장면 배경 한 판.  groundY 는 성과 적이 딛는 줄, arenaBottom 은
// 아래 인벤토리가 덮기 시작하는 줄이다.
inline void Draw(int groundY, int arenaBottom) {
	const float s = Scale();

	//심연색을 먼저 깐다. 원경 아래로 화면이 길어져도 색이 이어진다.
	MemRect(0, DY, DX, Max(1, DY - arenaBottom), Cur().abyss);

	//원경 꼭대기가 화면 위에 못 미치면 - 카메라를 위로 밀어 땅이 기준보다
	//올라간 때다 - 그 위는 하늘색으로 잇는다. 원경 맨 윗줄이 그 색이라
	//이음매가 안 보인다.
	const int farTop = TopOf(groundY, 0.0f, s);
	if (farTop < DY) MemRect(0, DY, DX, DY - farTop, Cur().sky);

	Layer(Img(SlotFar),  kSkyW,  0.0f,      kSpeedFar,  groundY, s);
	Boss(groundY, s);
	Layer(Img(SlotMid),  kSkyW,  0.0f,      kSpeedMid,  groundY, s);
	Layer(Img(SlotRail), kRailW, kRailTopY, kSpeedRail, groundY, s);
}

} // namespace StageBg
