#pragma once
// Dedicated identities avoid replacing unrelated legacy icons that share a cell.
namespace NativeGearIcons {
enum { GloveFirst=0x8100, Heroes=3, Tiers=8, GloveEnd=GloveFirst+Heroes*Tiers };
inline bool IsGlove(int icon){return icon>=GloveFirst&&icon<GloveEnd;}
inline int Glove(int hero,int tier){return GloveFirst+hero*Tiers+(tier<0?0:tier>=Tiers?Tiers-1:tier);}
inline int Hero(int icon){return (icon-GloveFirst)/Tiers;}
inline int Tier(int icon){return (icon-GloveFirst)%Tiers;}
}
