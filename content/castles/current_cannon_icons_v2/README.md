# Current inventory cannon icons

Ten transparent weapon cutouts generated with builtin imagegen from the matching
`../outdoor_castles_v2/originals/castle-01.png` through `castle-10.png`.
Exact generation instructions are recorded in `prompts.json`; untouched outputs
are in `originals/`.

Run `tools/castles/register_current_cannon_icons.py` to register all 60 frames in
`Resources/res/inventory_cannon/` and regenerate
`Classes/Data/InventoryCannonSprites.h`. Grades share the current exterior weapon
design. Existing filenames, IDs and footprints remain: grades 0–2 use 2×2 cells,
grades 3–5 use 3×2 cells. Fitting preserves aspect ratio and transparency.

Runtime preview: `output/current-cannon-icons-review/current-cannon-icons.png`.
