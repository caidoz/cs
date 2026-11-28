#pragma once
namespace PortraitCastleArt {
constexpr int Count=19;
static const char* Names[Count]={u8"\uc0c8\uc2f9 \ub9c8\ucc28",u8"\ub3cc\ubb38 \uc131\ucc44",u8"\uccad\ub3d9 \ub3d4 \uc131",u8"\uc7a5\uc778\uc758 \uc131",u8"\uc6a9\uad11\ub85c \uc131",u8"\ud30c\uc218\ud0d1 \uc131",u8"\uc99d\uae30\uae30\uad00 \uc131",u8"\uac15\ucca0 \uc131\ucc44",u8"\uc11c\uace0 \uc131",u8"\ubd88\uaf43 \uc694\uc0c8",u8"\uc544\uce58 \uc131\ucc44",u8"\ubc29\ud328 \uc131",u8"\uc790\uc218\uc815 \ub3d9\ub825\uc131",u8"\uccad\ub3d9 \ub3c5\uc218\ub9ac \uc131",u8"\uc655\uc2e4 \uadf9\uc7a5\uc131",u8"\uccad\ub3d9 \uc655\uad81",u8"\ubcc4\ubcf4\uae30 \uc131",u8"\uc655\uad00 \uc131\ucc44",u8"\uc0ac\uc790\uc655\uc758 \uc131"};
struct Size {int w,h;};
static const Size Sizes[Count]={{256,209},{262,297},{270,307},{278,304},{286,336},{294,354},{302,380},{310,384},{318,408},{326,422},{345,461},{351,466},{364,479},{373,498},{379,498},{392,523},{398,487},{407,511},{431,533}};
static constexpr float MaxAssemblyRatio=1.1924f;
static const int WheelPixels[Count]={50,52,54,56,57,59,60,62,64,65,69,70,73,75,76,78,80,81,86};
// Deck-top contact above the hull bottom; all coordinates are native pixels.
static const int DeckPixels[Count]={33,37,27,24,27,25,27,25,25,26,28,28,29,30,30,31,32,33,34};
inline float WheelSize(int c){return (float)WheelPixels[c];}
inline int WheelCount(int c){return c<3?2:c<10?3:4;}
inline float FrontWheelAt(int c){return c<3?.80f:.84f;}
inline float WheelAt(int c,int i){return .15f+(FrontWheelAt(c)-.15f)*i/(WheelCount(c)-1);}
inline float CannonBaseFromFloor(int c){return (float)DeckPixels[c];}
static const int CannonFootX[Count]={61,67,72,76,81,85,90,104,99,118,108,157,138,143,154,170,142,147,152};
}
