#pragma once
namespace PortraitCastleArt {
constexpr int Count=19;
static const char* Names[Count]={u8"목재 개척 성",u8"숲의 나무 요새",u8"청록 사막 궁전",u8"황금 해적선",u8"빙하 요새",u8"증기 공업 요새",u8"화산 흑철 성",u8"황동 시계탑",u8"보랏빛 고딕 성",u8"수정 마법 성",u8"산호 해양 궁전",u8"비취 용궁",u8"거대 버섯 성",u8"별빛 천문 성",u8"붉은 용의 성",u8"청강 기사 요새",u8"마왕의 흑요 성",u8"백금 천공 궁전",u8"태양 왕실 궁전"};
struct Size {int w,h;};
static const Size Sizes[Count]={{256,294},{259,341},{262,367},{265,398},{267,480},{270,484},{273,489},{276,496},{279,529},{282,563},{284,571},{287,651},{290,658},{293,679},{296,705},{299,737},{302,760},{304,797},{323,829}};
static constexpr float MaxAssemblyRatio=1.482f;
static const int WheelPixels[Count]={50,56,57,59,62,64,67,69,71,72,76,79,79,82,85,87,89,93,93};
static const int DeckPixels[Count]={47,57,42,32,44,40,35,33,30,31,39,33,36,43,41,48,45,34,35};
inline float WheelSize(int c){return (float)WheelPixels[c];}
inline float FrontWheelAt(int c){return c<5?.80f:.84f;}
inline float CannonBaseFromFloor(int c){return c==18?-42.f:(float)DeckPixels[c]-(c==0?0.f:10.f);}
static const int CannonFootX[Count]={61,25,28,32,35,52,56,61,65,70,74,79,83,88,92,97,101,106,69};
// Authored front-wall strip occludes the royal cannon breech; no separate mounting geometry.
static const int RoyalWallOcclusion[4]={182,716,44,98};
}
