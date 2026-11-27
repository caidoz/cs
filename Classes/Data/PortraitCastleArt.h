#pragma once
namespace PortraitCastleArt {
constexpr int Count=19;
static const char* Names[Count]={u8"\uac1c\ucc99\uc758 \ub098\ubb34\uc9d1",u8"\uc0c8\uc2f9 \uc218\ube44\uc18c",u8"\ud0dc\uc591 \uc0ac\uc790 \ucd08\uc18c",u8"\ub2fb\uc758 \ubcc0\uacbd \uc694\uc0c8",u8"\ubd88\uc0c8 \uc8fc\uc870\uc131",u8"\uc11c\ub9ac \ub098\ubb34 \uc131\ucc44",u8"\uccad\ub3d9 \uc0ac\uc790 \uacf5\ubc29",u8"\ucc38\ub098\ubb34 \uad8c\uc591\uc131",u8"\uc218\uc815 \uc0ac\uc790 \uc131\ucc44",u8"\uccad\ub8e1 \ubcd1\ucc38\uc131",u8"\uae4c\ub9c8\uadc0 \ube44\uc804\uc131",u8"\uace0\ubaa9 \uc218\ud638\uc131",u8"\uc870\uac1c \uc218\ub85c\uc131",u8"\ud0dc\uc591 \uad00\uce21\uc131",u8"\ub1cc\ubaa9 \ub3d9\ub825\uc131",u8"\ud64d\uc5fc \ubd88\uc0c8 \ub300\uc131\ucc44",u8"\ubcc4\uc0ac\uc2b4 \ucc9c\ubb38\uc694\uc0c8",u8"\uc801\ub8e1 \uacf5\uc131\uc131\ucc44",u8"\uc0ac\uc790\uc640 \uc138\uacc4\uc218\uc758 \uac70\uc2e0\uc131"};
struct Size {int w,h;};
static const Size Sizes[Count]={{256,190},{262,248},{270,355},{278,406},{286,431},{294,510},{302,555},{310,692},{318,744},{326,767},{345,777},{351,880},{364,890},{373,900},{379,964},{392,974},{398,1052},{407,1062},{431,1072}};
static constexpr float MaxAssemblyRatio=1.1924f;
static const int WheelPixels[Count]={50,53,55,60,64,65,66,70,76,75,79,84,84,85,91,94,107,109,112};
// Measured deck contact above the hull bottom; all coordinates are native pixels.
static const int DeckPixels[Count]={36,32,38,43,46,76,43,43,72,66,49,75,52,40,81,65,80,74,75};
inline float WheelSize(int c){return (float)WheelPixels[c];}
inline float FrontWheelAt(int c){return c<5?.80f:.84f;}
inline float CannonBaseFromFloor(int c){return (float)DeckPixels[c];}
static const int CannonFootX[Count]={61,67,72,76,81,85,90,104,99,118,108,157,138,143,154,170,142,147,152};
}
