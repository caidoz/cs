# Square gear, visible deck plane and triple launcher ports

All 120 one-cell equipment designs (three heroes, eight tiers, five slots) have
independently repainted 256px icon PNGs. `output/square-gear/source` records the
grid-design reference sheets. Icon and grid files remain separate resources;
`DrawGridItemInBox` no longer redirects armor to icon textures. The temporary
shared armor designs were baked into separate grid PNGs before repainting icons.
Weapons keep their upright multi-cell grid artwork.

- Comparison gallery: `output/square-gear/index.html` (grid / new icon).
- Built-in image generation prompts and outputs: `output/square-gear/generation.json`.
- Packaging: run `tools/items/build_square_gear.py` after the legacy item/grid
  builders. Initial references come from `prepare_square_gear.py`; preserve the
  saved reference sheets and `before` backups for repeatable packaging.
- Runtime ID expectations: `Classes/SquareGearIcons.h`; the review checks all
  120 against the live data pack and asserts separate grid/icon textures.

`Resources/res/castle_mist_v2/deck-surfaces.png` contains ten registered top-facing
floor strips matching each castle's material. The overlay adds a 42px
walking plane around the existing character foot baseline without changing the
castle or board scale. It is drawn before characters, mirrored with the hull.

The third castle's source art has three loaded red-nosed missiles. Its attack
remains a three-missile burst. A separate red-nosed missile projectile matches
the loaded ammunition, replacing the unrelated Diana effect sprite for this
launcher. Origins now match the upper, middle and lower
ports at normalized y=0.20, 0.50, 0.80 and x=0.98 of the displayed turret box.
The three projectiles travel forward from those ports toward the target rather
than taking the previous high Diana arc through the header.
Single launchers no longer receive an arbitrary -7px vertical offset. Burst
counts and damage application timing remain intact. Runtime review checks the
three distinct origins and mirrored alignment.

Preview executable: `proj.win32/Debug.win32/cs_square_deck.exe`.
Runtime captures: `output/item-series/runtime/square-gear-catalog`,
`square-deck-*`, and `three-ports-*`.

Deck depth follow-up: the top starts 30 reference pixels above ground and extends 42 pixels down, leaving visible surface around feet at ground + 8. Preview: `proj.win32/Debug.win32/cs_deeper_deck.exe`. Runtime captures: `output/item-series/runtime/deeper-deck-{850,1408}`.
