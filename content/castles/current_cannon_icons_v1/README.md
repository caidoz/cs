# Current cannon icons

Ten transparent weapon cutouts generated with the built-in imagegen tool,
using `../individual_castles_v4/castle-01.png` through `castle-10.png` as the
current visual references. Full prompts are recorded in `prompts.json`.

The 60 runtime item sprites use these ten designs across six grades. Grades
keep their original 2x2 / 3x2 inventory footprints, placement masks and stats;
the base weapon design is shared because the current exterior art also shares
the base weapon across upgrades. Full-color alpha and source proportions are
retained when fitting sprites, without the old 48-color quantization.

Run `tools/castles/register_current_cannon_icons.py` to reproduce the PNGs,
atlas, manifest and C++ frame metadata. The original inventory builder selects
this source set automatically when all ten originals are available; `--legacy`
explicitly rebuilds the previous sheet.

Resources: `Resources/res/inventory_cannon/atlas.png` and
`castle_01_lv_0.png` through `castle_10_lv_5.png`. The existing image ID and
shared draw helpers update storage, placement/drag icons and upgrade menus.
