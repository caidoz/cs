# Grid equipment artwork

The board previously resolved `GetItemIcon` into a square inventory image. This
lost the upright sword/club artwork even though the board still occupied multiple
cells. Grid rendering now uses a separate 225-image series.

- `Resources/res/grid_items/grid0.png` through `grid224.png`: 35 swords, 35 guns,
  35 boomerangs, then 8 tiers for each of the 15 armor types (helmets, torso gear,
  gloves/bracelets, trousers/skirts, boots for three heroes).
- `Classes/GridItemCatalog.h`: maps item type and detail independently of icon IDs.
- `DrawGridItemInBox`: uniformly fits the complete source canvas into the board
  rectangle and rotates around the centre when requested. Board occupancy and
  shaped cell masks still come from the original grid model.
- Ordinary inventory/reel icons continue using the 256px `items/itemN` series.
  Actor weapon sprites and equipped costumes remain their original resources.
- Square equipment now uses matching designs in independent icon and grid PNGs;
  see `SQUARE_GEAR_DECK_AND_PORTS.md`. Armor's temporary icon-texture redirection
  has been removed. Grid cell occupancy and rotation remain unchanged.
- Combat board equipment is raised by 6 pixels at 640px reference width. Its
  ground shadow baseline reserves the full shadow half-height plus bottom padding
  so the shadow remains inside the equipment tile.
- Generated art is stored at four times the original canvas dimensions, retaining
  the original canvas aspect and occupied-area bounds. The draw zoom derives from
  the actual texture dimensions rather than assuming square 256px icons.

Art was repainted with the built-in image generation tool using the original grid
equipment as the edit target and the earlier equipment sample as material style
reference. Complete prompts and selected outputs are in
`output/grid-items/generation.json`; source sheets are in `output/grid-items/source`,
selected repaints in `output/grid-items/generated`. The before/after gallery is
`output/grid-items/index.html`. `tools/items/build_grid_items.py` packages the
selected sheets into registered transparent resources without repainting in code.
Atlas splitting follows transparent gutters near each expected cell edge so long
blade tips cannot leak into the next item. The gloves sheet received a separate
built-in background extraction pass; its prompt is recorded alongside the atlas
prompts. Packaging removes faint matte and small detached atlas fragments.

Validation: `tools/items/verify_grid_items.py` verifies all source hashes, canvas
ratios and transparent gutters, then captures every item through the actual board
renderer, rotated variants, the ordinary icon catalog and both viewport sizes.
The isolated preview executable is `proj.win32/Debug.win32/cs_grid_items.exe`.
