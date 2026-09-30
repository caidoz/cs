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

//성을 딛는 줄보다 이만큼 내려 놓는다. 화면 픽셀이고, 성 배율이 붙박이라
//층수와 상관없이 같다.
//
//본체와 바퀴가 따로다. 둘 다 같은 만큼 내리면 바퀴가 선로 아래로 그만큼
//파묻힌다. 본체만 더 내려앉혀 무게를 실으면서, 바퀴는 레일에 얹힌 느낌만
//남도록 덜 내린다.
static const float kCastleDropPx = 48.0f;
static const float kWheelDropPx  = 16.0f;

//장면이 딛는 줄의 기준 높이. 화면 아래에서 잰 비율이다. 배율도 여기서
//정한다.
//
//0.31 -> 0.385 -> 0.46 으로 올렸다(64 픽셀씩 두 번). 전투 화면의 아래
//UI - 격자와 상점 줄 - 가 선로와 성 아랫도리를 가렸다.
//
//로비도 이 줄에 성을 세운다(LobbyCamClamp). 두 화면이 같은 값을 봐야
//넘어갈 때 장면이 안 튄다.
//
//로비와 전투가 우연이 아니라 이 값으로 같은 자리에 선다 - 로비 카메라가
//성을 놓는 자리를 세어 보면 화면 높이의 0.31 쯤이고, 전투도 같은 값을
//쓴다(VisualGroundY).
static const float kGroundRef = 0.46f;

// ---- 지역마다 다른 것 ----

// 보스의 눈 연출.
//  Swap - 감은 그림으로 통째로 갈아 끼운다 (늪지대 개구리).
//  Glow - 평소 그림 위에 발광만 옅게서 진하게 얹는다 (계곡 웜, 아틀란티스 아귀).
//  None - 별도 연출 없음 (지하수로 짐승).
enum BossFx { FxSwap, FxGlow, FxNone };

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
	// 아틀란티스 - 심해의 거대 아귀가 유영하며 3.8 초 주기로 초롱불 촉수가 밝아진다.
	{ 0x24536B, 0x26A1C8, 390.0f, 170.0f, 730.0f, 486.667f,
	  4.2f, 0.004f, 0.004f, 3.0f, FxGlow, 3.8f, 0.0f, 0.0f },
	// 지하수로 - 짐승형 가시 갑주 보스가 5.2 초 주기로 숨을 쉰다.
	{ 0x36574D, 0x2D433D, 300.0f, 160.0f, 800.0f, 533.333f,
	  5.2f, 0.005f, 0.005f, 2.0f, FxNone, 1.0f, 0.0f, 0.0f },
	// 아델라인 평원 - 갑주 거인 보스가 5.2 초 주기로 숨을 쉰다.
	{ 0xAFC2AC, 0x64B4F8, 240.0f, 140.0f, 900.0f, 600.0f,
	  5.2f, 0.005f, 0.005f, 2.0f, FxNone, 1.0f, 0.0f, 0.0f },
	// 화염지대 - 화염 정령 보스가 5.2 초 주기로 숨을 쉰다.
	{ 0x66485F, 0x371B3A, 240.0f, 120.0f, 900.0f, 600.0f,
	  5.2f, 0.005f, 0.005f, 2.0f, FxNone, 1.0f, 0.0f, 0.0f },
	// 얼음지대 - 얼음 갑각 보스가 5.2 초 주기로 숨을 쉰다.
	{ 0x8197BD, 0x6D84B6, 260.0f, 140.0f, 850.0f, 566.667f,
	  5.2f, 0.005f, 0.005f, 2.0f, FxNone, 1.0f, 0.0f, 0.0f },
	// 번개지대 - 번개 정령 보스가 5.2 초 주기로 숨을 쉰다.
	{ 0x524861, 0x473851, 270.0f, 130.0f, 850.0f, 566.667f,
	  5.2f, 0.005f, 0.005f, 2.0f, FxNone, 1.0f, 0.0f, 0.0f },
	// 빛의 지대 - 금빛 수호자 보스가 5.2 초 주기로 숨을 쉰다.
	{ 0x69A4AC, 0x577982, 260.0f, 140.0f, 850.0f, 566.667f,
	  5.2f, 0.005f, 0.005f, 2.0f, FxNone, 1.0f, 0.0f, 0.0f },
	// 골렘협곡 - 골렘 보스가 5.2 초 주기로 숨을 쉰다.
	{ 0x9D9895, 0xADB3C3, 270.0f, 150.0f, 820.0f, 546.667f,
	  5.2f, 0.005f, 0.005f, 2.0f, FxNone, 1.0f, 0.0f, 0.0f },
	// 어둠의 협곡 - 거대 어둠 괴수 보스가 5.2 초 주기로 숨을 쉰다.
	{ 0x244D55, 0x0E3C4D, 240.0f, 130.0f, 900.0f, 600.0f,
	  5.2f, 0.005f, 0.005f, 2.0f, FxNone, 1.0f, 0.0f, 0.0f },
	// 드래곤 협곡 - 고대 드래곤 보스가 5.2 초 주기로 숨을 쉰다.
	{ 0x746474, 0x746395, 240.0f, 150.0f, 900.0f, 600.0f,
	  5.2f, 0.005f, 0.005f, 2.0f, FxNone, 1.0f, 0.0f, 0.0f },
	// 망자의 도시 - 거대 사신 보스가 5.2 초 주기로 숨을 쉰다.
	{ 0x625B76, 0x4E2F6D, 230.0f, 130.0f, 900.0f, 600.0f,
	  5.2f, 0.005f, 0.005f, 2.0f, FxNone, 1.0f, 0.0f, 0.0f },
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

//디버그로 고른 지역. -1 이면 판 번호를 따른다.
//
//지역은 판이 정하므로(SetRegionForStage) 그냥은 지금 판의 지역 하나밖에
//못 본다. 다른 지역 그림을 확인하려면 잠시 붙잡아 둘 자리가 필요하다.
extern int   s_regionPick;

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
	s_region = s_regionPick >= 0
	         ? s_regionPick % STAGEBG_REGION_CNT
	         : (stage / STAGE_PER_CYCLE) % STAGEBG_REGION_CNT;
}

//다음 지역으로 넘긴다. 마지막을 지나면 다시 판을 따른다 - 눌러서 한 바퀴
//돌면 원래대로 돌아오므로 고정해 둔 것을 잊고 지나갈 일이 없다.
inline void DebugNextRegion(void) {
	s_regionPick = (s_regionPick + 1 >= STAGEBG_REGION_CNT) ? -1 : s_regionPick + 1;
	if (s_regionPick >= 0)
		s_region = s_regionPick;
}
inline int DebugRegionPick(void) { return s_regionPick; }
inline int CurRegion(void)       { return s_region; }

inline const char* DebugRegionLabel(void) {
	static const char* const kNames[STAGEBG_REGION_CNT] = {
		"1.늪지대", "2.금단의계곡", "3.아틀란티스", "4.지하수로",
		"5.아델라인평원", "6.화염지대", "7.얼음지대", "8.번개지대", "9.빛의지대", "10.골렘협곡",
		"11.어둠의협곡", "12.드래곤협곡", "13.망자의도시"
	};
	if (s_regionPick >= 0 && s_regionPick < STAGEBG_REGION_CNT) {
		return kNames[s_regionPick];
	}
	return "자동(스테이지)";
}
inline void CycleDebugRegion(void) {
	DebugNextRegion();
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

// 카메라. 근경(선로) 기준으로 얼마나 밀렸고 얼마나 커졌는가.
//
// 로비는 성을 잡고 밀거나 키울 수 있다. 전투는 붙박이라 기본값을 쓴다.
struct Camera {
	float panX;     // 근경이 옆으로 밀린 화면 거리
	int   groundY;  // 근경이 딛는 줄
	float zoom;     // 근경 배율. 1 이면 붙박이
};

inline Camera FixedCam(int groundY) {
	Camera c = { 0.0f, groundY, 1.0f };
	return c;
}

// 층마다 카메라를 얼마나 따라가나.
//
// [미는 것은 흐르는 속도 그대로다]
// 원경이 선로의 50 분의 1 로 흐르는 것은 그만큼 멀리 있다는 뜻이다.
// 카메라를 밀 때도 그만큼만 따라와야 앞뒤가 맞는다. 예전에는 모든 층이
// 딛는 줄을 1:1 로 따라가서, 성을 잡고 밀면 하늘이 성만큼 움직였다 -
// 그러면 멀리 있는 것으로 안 보인다.
//
// [키우는 것은 따로 둔다]
// 같은 비로 키우면 원경이 50 분의 1 이라 하늘이 사실상 안 커진다. 성만
// 커지고 배경은 멈춘 그림이 된다. 눈에 보이는 만큼은 따라 커지도록
// 완만한 값을 따로 준다.
struct Depth { float pan, zoom; };
static const Depth kDepthFar  = { kSpeedFar / kSpeedRail, 0.25f };
static const Depth kDepthMid  = { kSpeedMid / kSpeedRail, 0.55f };
static const Depth kDepthRail = { 1.0f,                   1.00f };

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

//기준 높이. 카메라가 안 밀렸을 때 근경이 딛는 줄이다.
inline float GroundRef(void) { return (float)(int)(DY * kGroundRef); }

//이 층이 그려질 배율과 딛는 줄. 깊이만큼만 카메라를 따라간다.
inline float LayerScale(const Camera& cam, const Depth& d) {
	return Scale() * (1.0f + (cam.zoom - 1.0f) * d.zoom);
}
inline int LayerGround(const Camera& cam, const Depth& d) {
	return (int)(GroundRef() + ((float)cam.groundY - GroundRef()) * d.pan);
}

//지금까지 흘려보낸 선로 거리(화면 픽셀). 바퀴가 이만큼 굴러야 한다.
//선로는 깊이 1 이라 카메라 배율을 그대로 받는다.
inline float RailTravelPx(void) {
	return kSpeedRail * s_travel * Scale();
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
                  const Camera& cam, const Depth& d) {
	if (!sprite[img]) LoadImg(img);
	if (!sprite[img]) return;

	const auto sz = sprite[img]->getContentSize();
	if (sz.width < 1.0f) return;

	const float s     = LayerScale(cam, d);
	const float tileW = designW * s;
	const float zoom  = tileW / sz.width;
	//흘러간 거리에서 카메라가 민 만큼을 뺀다. 미는 쪽과 흐르는 쪽이 같은
	//축이라 한 값으로 합쳐 놓아야 타일 이음매가 어긋나지 않는다.
	const float dist  = speed * s_travel * s - cam.panX * d.pan;

	const int   q     = (int)std::floor(dist / tileW);
	const float first = -(dist - q * tileW);
	const int   top   = TopOf(LayerGround(cam, d), designTopY, s);

	for (int j = 0; first + j * tileW < (float)DX; j++) {
		DrawImage((int)sz.width, (int)sz.height, 0, 0,
		          (int)(first + j * tileW), top,
		          WrapEven(q + j) != 0, false, false, false, false,
		          zoom, sprite[img], img);
	}
}

//보스는 원경에 붙어 있다. 한 마리뿐이라 반복하지 않고, 원경 타일 중
//뒤집히지 않은 것 위에만 얹는다. 뒤집힌 타일에 얹으면 얼굴이 돌아간다.
inline void Boss(const Camera& cam) {
	const Region& r = Cur();
	//보스는 원경에 붙어 있다. 원경과 같은 배율 · 같은 깊이로 움직여야
	//붙어 있는 것으로 보인다.
	const float s       = LayerScale(cam, kDepthFar);
	const int   groundY = LayerGround(cam, kDepthFar);

	const int baseImg = Img(SlotBoss);
	const int fxImg   = Img(SlotBossFx);
	if (!sprite[baseImg]) LoadImg(baseImg);
	if (r.fx != FxNone && !sprite[fxImg]) LoadImg(fxImg);
	if (!sprite[baseImg]) return;

	const auto sz = sprite[baseImg]->getContentSize();
	if (sz.width < 1.0f) return;

	//가로 세로를 한 배율로 낸다.
	//
	//따로 내면 스프라이트에 scaleX != scaleY 가 남는다. 숨쉬기 비율이
	//달라서만이 아니라, w/폭 과 h/높이 를 따로 나누면 부동소수 끝자리가
	//어긋나기 때문이다. 그 스프라이트를 나중에 누가 getScale() 로 읽으면
	//엔진이 "어느 쪽을 줘야 하나" 하고 단언에 걸려 게임이 멈춘다
	//(CCNode.cpp 의 getScale).
	//
	//구운 그림은 설계 비율 그대로라(0.75 배) 한 배율로 맞는다. 숨쉬기는
	//가로 세로 평균을 쓴다 - 원본의 0.9% 와 1.8% 차이는 눈에 안 띈다.
	const float swell = Swell(r.motionSec);
	const float grow  = 1.0f + swell * (r.scaleX + r.scaleY) * .5f;
	const float w = r.bossW * s * grow;
	const float h = r.bossH * s * grow;
	const float z = w / sz.width;

	//눈 연출. 감는 쪽은 구간 안에서만 갈아 끼우고, 밝아지는 쪽은 늘
	//얹되 진하기가 오르내린다.
	const float phase = std::fmod(s_clock, r.fxSec);
	const bool  swap  = r.fx == FxSwap && phase > r.fxFrom && phase < r.fxTo;
	const int   glow  = r.fx == FxGlow && sprite[fxImg]
	                  ? 4 + (int)(Swell(r.fxSec) * 28.0f) : 0;

	const int   img   = (swap && sprite[fxImg]) ? fxImg : baseImg;

	const float tileW = kSkyW * s;
	const float dist  = kSpeedFar * s_travel * s - cam.panX * kDepthFar.pan;
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
		               z, z, sprite[img], img);

		if (glow > 0) {
			SetAlpha(glow);
			DrawImageScale((int)sz.width, (int)sz.height, 0, 0, x, y,
			               false, false, false, false, false,
			               z, z, sprite[fxImg], fxImg);
			SetAlpha(32);
		}
	}
}

// 전투 장면 배경 한 판.  groundY 는 성과 적이 딛는 줄, arenaBottom 은
// 아래 인벤토리가 덮기 시작하는 줄이다.
inline void Draw(const Camera& cam, int arenaBottom) {
	//심연색을 먼저 깐다. 원경 아래로 화면이 길어져도 색이 이어진다.
	MemRect(0, DY, DX, Max(1, DY - arenaBottom), Cur().abyss);

	//원경 꼭대기가 화면 위에 못 미치면 - 카메라를 위로 밀어 땅이 기준보다
	//올라간 때다 - 그 위는 하늘색으로 잇는다. 원경 맨 윗줄이 그 색이라
	//이음매가 안 보인다.
	const int farTop = TopOf(LayerGround(cam, kDepthFar), 0.0f,
	                         LayerScale(cam, kDepthFar));
	if (farTop < DY) MemRect(0, DY, DX, DY - farTop, Cur().sky);

	Layer(Img(SlotFar),  kSkyW,  0.0f,      kSpeedFar,  cam, kDepthFar);
	Boss(cam);
	Layer(Img(SlotMid),  kSkyW,  0.0f,      kSpeedMid,  cam, kDepthMid);
	Layer(Img(SlotRail), kRailW, kRailTopY, kSpeedRail, cam, kDepthRail);
}

//카메라를 안 쓰는 화면(전투)용.
inline void Draw(int groundY, int arenaBottom) {
	Draw(FixedCam(groundY), arenaBottom);
}

} // namespace StageBg
