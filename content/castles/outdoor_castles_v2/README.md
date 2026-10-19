# Compact outdoor-deck castle exteriors

Ten complete base-stage exterior concepts generated with built-in imagegen.
The untouched final combined PNGs are in `originals`; exact reference paths
and prompts are in `generation-prompts.json`, with targeted wheel/railing
corrections in `correction-prompts.json`.

- Narrow outdoor companion ledge attached to the lower exterior wall.
- No front railing, roof, enclosed gallery or floating upper-body gap.
- Small underside corbels and a thin bowed ledge inside the hull silhouette.
- Wheels target roughly two thirds of the previous artwork's diameter.
- Stages 1–4: two wheels; 5–7: three; 8–10: four.
- Original material, weapon, emblem and asymmetric architectural identities.

All ten final images were visually reviewed for wheel count, clear lower
walking surface and retained architecture. These are generated concept images,
not dimensionally exact production rigs. Wheel diameter and deck anchors will
need measured registration when splitting sprites for runtime animation.

`index.html` compares the complete exteriors on a shared opaque-art bottom
line, with slightly increasing widths. Source PNGs are not resized or cropped
by the packager; trimming for comparison is done only by HTML styling.
`outdoor-castles-10.zip` contains all ten original images and the review page.
These exteriors are now registered in the game. `runtime-registration.json` records measured wheel circles, exterior bounds, deck/hero/muzzle anchors and room apertures. The original PNGs are copied unchanged; circular animation overlays are registered using `tools/castles/register_outdoor_castles_v2.py`. The renderer draws each exterior intact and rotates its 2/3/4 wheel overlays without adding a detached tier or another deck. Current map and PVP entrance icons are packed from the same approved originals. Runtime checks are recorded in `runtime-validation.json`.
