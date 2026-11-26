#pragma once
namespace PortraitCastleArt {
constexpr int Count=19;
static const char* Names[Count]={u8"\uac1c\ucc99\uc758 \ub098\ubb34\uc9d1",u8"\uc0c8\uc2f9 \uc218\ube44\uc18c",u8"\ud0dc\uc591 \uc0ac\uc790 \ucd08\uc18c",u8"\ub2fb\uc758 \ubcc0\uacbd \uc694\uc0c8",u8"\ubd88\uc0c8 \uc8fc\uc870\uc131",u8"\uc11c\ub9ac \ub098\ubb34 \uc131\ucc44",u8"\uccad\ub3d9 \uc0ac\uc790 \uacf5\ubc29",u8"\ucc38\ub098\ubb34 \uad8c\uc591\uc131",u8"\uc218\uc815 \uc0ac\uc790 \uc131\ucc44",u8"\uccad\ub8e1 \ubcd1\ucc38\uc131",u8"\uae4c\ub9c8\uadc0 \ube44\uc804\uc131",u8"\uace0\ubaa9 \uc218\ud638\uc131",u8"\uc870\uac1c \uc218\ub85c\uc131",u8"\ud0dc\uc591 \uad00\uce21\uc131",u8"\ub1cc\ubaa9 \ub3d9\ub825\uc131",u8"\ud64d\uc5fc \ubd88\uc0c8 \ub300\uc131\ucc44",u8"\ubcc4\uc0ac\uc2b4 \ucc9c\ubb38\uc694\uc0c8",u8"\uc801\ub8e1 \uacf5\uc131\uc131\ucc44",u8"\uc0ac\uc790\uc640 \uc138\uacc4\uc218\uc758 \uac70\uc2e0\uc131"};
struct Size {int w,h;};
static const Size Sizes[Count]={{256,190},{259,329},{262,353},{265,377},{267,447},{270,459},{273,465},{276,483},{279,497},{282,532},{284,537},{287,577},{290,589},{293,601},{296,633},{299,647},{302,698},{304,717},{323,741}};
static constexpr float MaxAssemblyRatio=1.482f;
static const int WheelPixels[Count]={50,56,57,59,62,64,67,69,71,72,76,79,79,82,85,87,89,93,93};
// Measured deck contact above the hull bottom; all coordinates are native pixels.
static const int DeckPixels[Count]={36,55,55,42,64,62,57,48,82,111,61,61,60,89,114,72,84,94,66};
inline float WheelSize(int c){return (float)WheelPixels[c];}
inline float FrontWheelAt(int c){return c<5?.80f:.84f;}
inline float CannonBaseFromFloor(int c){return (float)DeckPixels[c];}
static const int CannonFootX[Count]={61,25,28,32,35,52,56,61,65,70,74,79,83,88,92,97,101,106,150};
}
