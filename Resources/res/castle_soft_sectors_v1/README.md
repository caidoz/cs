# Warm SD castles with integrated interior sectors

Ten paired atlases contain the closed and cutaway versions of each castle. Interiors belong to the original towers, wings and vaults; they are not repeated room strips. Counts are **1, 2, 2, 3, 3, 4, 4, 5, 5, 5** (34 distinct sectors). The original ten-castle progression, identities, outdoor deck, equipment, upgrade levels and save schema remain.

`cannons.png` contains six upgrade grades for ten weapon families. The mounted renderer retains the original catapult and three-tier missile launcher and uses the new rounded, thicker guns for the other eight families. Damage, cooldowns, inventory footprints and firing behavior remain driven by existing data. Muzzle coordinates follow the selected render frame.

`wheels.png` contains separate transparent circular wheels so spinning never rotates pieces of the chassis. Existing wheel counts and travel-driven rotation remain.

The built-in image generation tool produced all PNGs. Exact prompts and original generation paths are recorded in `generation.json` and `final-edits.json`; selected final PNGs are copied unchanged. `register_soft_sectors.py` measures crops without editing images. Sector rectangles, floor positions and occupancy caps feed both resident placement and clipping. A maximum of three residents is shown per sector; additional owned companions remain owned and selectable.

Runtime data: `Classes/Data/SoftCastleSectors.h`, `SoftCastleWheelFrames.h`. Integration: `CastleModularDebug.h`, `AuthoredCastleTone.inc`, `Func_Draw.cpp`. Lobby **성 테스트** exposes all castles, saved-level restoration, five part levels and interior reveal. Set `CS_PREVIOUS_CASTLE_ART=1` to compare against the preceding artwork.

Native review: `tools/castles/verify_soft_sectors.ps1`. Gallery: `reports/art_direction/soft-sectors-review.html`. No iOS build is performed on this Windows workspace.
