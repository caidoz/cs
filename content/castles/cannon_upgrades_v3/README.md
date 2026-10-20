# Cannon upgrade art, revision 3

Ten weapon families, each with six distinct appearances (base plus five upgrades).
The ten previously generated base weapons are retained; fifty new upgrades add
reinforcement ribs, recoil mechanisms, armor, power chambers and legendary cores.
Generated with builtin imagegen. `prompts.json` records upgrade prompts and
`clean-castle-prompts.json` records the edits removing baked weapons from castles.
Untouched generated images are saved in `originals/` and `clean_castles/`.

`tools/castles/register_cannon_upgrades.py` exports the same grade source twice:

- `Resources/res/inventory_cannon/`: 60 inventory PNGs and the existing atlas.
  Existing item/resource IDs and 2×2 / 3×2 cell footprints are preserved.
- `Resources/res/castle_cannon_v2/`: 60 high-resolution mounted PNGs and atlas,
  plus ten weapon-free bases. Only the weapon aperture is registered from each
  edited castle; original pixels outside that aperture are preserved.

`Classes/Data/MountedCannonSprites.h` records independent high-resolution crop,
muzzle and mounting geometry. The renderer anchors each weapon to its existing
balcony, applies the current cannon part grade, recoil and mirrored placement.
Castles retain original room, deck, wheel and commander geometry.

Preview: `preview.png`. Runtime inventory capture:
`output/current-cannon-icons-review/current-cannon-icons.png`.
Runtime mounted captures: `output/cannon-upgrades-review/grade-0/` through
`grade-5/` (10 castles per grade, 2 captures per castle).

Rebuild: `tools/castles/build_inventory_cannons.py` automatically selects this
complete set. Verify with `tools/castles/verify_cannon_upgrades.ps1`.
