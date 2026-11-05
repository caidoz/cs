# Functional castle interiors

Ten authored transparent PNG atlases. The game uses only each new right/open panel;
closed exteriors continue using `castle_soft_sectors_v1` to preserve their exact appearance.
No image pixels were edited after generation. Prompts and output provenance are in
`generation.json`; measured alpha bounds are in `registration.json` and
`Classes/Data/FunctionalCastleCrops.h`.

Room order, names, production categories and production bonus ratings are in
`Classes/Data/CastleFacilities.h`. The 34 sectors progress from food and equipment
to medicine, engineering, culture and luxury. Saved `castleProgress.rooms` levels
are reused. Each level adds 25% of the base bonus, up to level 5. Food facilities
add to energy recovery speed; other facilities add to gold output. Only the
selected owned castle applies. Gold accumulates in the existing vault; energy
automatically recovers to the existing cap. No new currency is introduced.
Existing room capacity/combat bonuses are retained for save compatibility.

Lobby **성 테스트** supports room-level previews, 8/16/32 NPC density, interior
visibility and cannon firing. These previews do not charge or persist upgrades.
NPCs use existing animated crew sprites and sector clipping; requested and drawn
counts are shown because cannon clearance can exclude a position. The cannon
uses a separate artillery simulation and cannot damage game objects or grant rewards.

Castle menu production upgrades use the existing gold confirmation/save path.
`tools/castles/verify_functional_castles.ps1` exercises all ten castles, NPCs,
projectile impacts, debug state isolation and a real facility upgrade with duplicate
confirmation protection in an isolated review session.
