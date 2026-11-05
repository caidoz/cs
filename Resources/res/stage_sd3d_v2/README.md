# Regional SD 3D environment set

Regions 02–15 each have a dedicated far panorama, transparent midground, and transparent railway: 42 PNGs. Region 01 keeps the approved `hybrid_sd3d` assets. Original `bgN_boss` and `bgN_boss_fx` pixel artwork and animation data remain in use.

Assets were created with the built-in image generation tool. Exact prompts and original output paths are in [generation.json](generation.json). Selected output files were copied unchanged; no offline raster resizing, recoloring, alpha processing, or compositing was applied. [asset-audit.json](asset-audit.json) records dimensions, alpha validation, SHA-256 hashes and measured rail contact rows.

`Classes/Text.h` maps the existing image IDs to these files. `StageBackground.h` uses nonmirrored scenery, full-height sky coverage, and measured rail registration. `StageBackgroundSeam.inc` draws periodic far/rail textures with an edge crossfade and softens transparent midground edges. Boss slots retain nearest-neighbor filtering.

Native review: `tools/castles/verify_all_regions.ps1` captures all 15 regions at two scrolling positions. Tested viewport sizes: 640×850, 640×1136, 640×1280, 640×1408. The gallery is `reports/art_direction/all-regions-review.html`. These are Windows native checks; no iOS build was performed here.
