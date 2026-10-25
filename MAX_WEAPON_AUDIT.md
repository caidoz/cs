# Max weapon audit and foundation migration

Reference: `C:/Users/polyp/Downloads/MAX_WEAPON_DESIGN.md` (2026-10-24).

## Existing implementation

- `Classes/Func_Movement.cpp`: `PvpHeroStep` performs stage basic attacks;
  `BulletBoomerangMove` contains the existing Max return, camping, homing,
  circle and mega skill paths. Preserve those skills and their identifiers.
- `Classes/Func_Battle.cpp`: stage hero timing currently falls back to the same
  cooldown for gun and boomerang. Sword bag attacks already have separate clocks.
- `Classes/Func_Draw.cpp`: `GridSlot::item` and store entries already copy owned
  items. Stacking mutates those run copies. `GridWearLoadout` equips the copies,
  while `SaveGame` currently copies live equipment back to persistent char data.
  This last boundary needs explicit protection and restoration on run exit.
- `Classes/Def/TouchKeyDef.h`: reward count is 5, not the confirmed 4. Current
  offers use item/crew categories. Essence is a placed item, not an instant buff.
- Loadout catalog filters out other heroes' equipment, completion does not
  require the selected hero's weapon, and defaults auto-fill allies.

## Located resources

- `Resources/res/inventory_boomerang/1.png` through `35.png`, `manifest.json`;
  matching originals in
  `content/equipment/pixel_art/inventory_boomerang/native_sources/inventory_boomerang/`.
- `Resources/res/w2_1.png` through `w2_35.png` are existing weapon art;
  `w2_0.png` is a tiny placeholder, not a verified 36th weapon.
- `Classes/Data/InventoryBoomerangShapes.h`, `content/boomerangs/profiles.json`
  and `tools/boomerangs/` describe and validate 35 gameplay variants.
- No matching 36-icon atlas was located in the repository or the named Downloads
  folder. Do not fabricate #36 or assign it an ultimate/rarity without approval.

## Minimal migration

1. Keep existing item IDs, PNGs, skill IDs, rarity and save schema.
2. Set four offers; retain existing inventory-building categories, without
   introducing provisional pool weights or direct temporary buff rewards.
3. Require the selected hero's sword/gun/boomerang before admission; allow all
   other owned equipment through the normal grid checks. Allies stay optional.
4. Snapshot persistent equipment at run start, protect it on save, restore on
   title/lobby exit, and clear run grid/store copies on exit.
5. Add a small deterministic outbound/return/readiness runtime for Max's stage
   basic attack using existing sprites. Keep legacy active skills intact.
6. Test four choices, required weapon, free optional items, return timing,
   pause, run cleanup and byte-identical persistent equipment preservation.

## Deferred product decisions

Multiple independently firing boomerangs versus a primary/support model, status
rules, final rarity mapping, exact reward pools, overflow staging, and skill
removal/mapping remain undecided. This foundation does not select those policies,
delete skills, infer shock from artwork, or create new art.

## Implemented and verified

- Four offer slots share the existing layout, touch ranges and purchase path.
  The isolated review purchases each of the four categories and checks the
  insufficient-funds case. Existing item definitions and pool weights remain.
- Default preparation selects only an owned weapon matching the selected hero.
  Admission validates that weapon and every selected item's grid placement.
  Other owned equipment and companions remain selectable. Runtime placement
  uses the same preview positions and rotations.
- Persistent equipment is snapshotted before the run. SaveGame reads that
  snapshot instead of temporarily equipped run copies. Lobby/title teardown
  restores it and clears grid/store, crew clocks and pending attacks.
- Max basic attacks use StageBoomerangModel's outbound/contact/return/recovery
  phases and the existing w2 sprite. The old basic projectile is suppressed
  only in stage basic attacks to prevent double damage; active skills retain
  their original path. Basic cooldown is a separate provisional tuning value
  (STAGE_MAX_BASIC_COOLDOWN, 3 seconds), with no final rarity balance implied.
  The equipped gun/boomerang also displays its basic cooldown in the grid.
- Win32 Debug build passed (existing compiler warnings remain).
- `tools/boomerangs/verify_max_foundation.ps1` passed: four purchases, required
  weapon, optional crew, independent item copies, persistent equipment equality,
  run cleanup, deterministic return/pause/target loss, live contact damage,
  readiness and repeated automatic Max basic attacks.
- Existing stage combat regression passed: 12 sword, 8 crew, 2 cannon and
  12 monster impacts; crew rendering, cooldown bars and paused clocks passed.
- Existing battle-menu regression passed at 640x725: setup tap/drag/cancel,
  shopping, combat, pause and abandon; six captured screens.
- Existing inventory artwork validation passed for all 35 located boomerangs.
  The external 36th icon/atlas is still unlocated; no replacement was invented.
