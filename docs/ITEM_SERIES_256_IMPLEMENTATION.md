# 256px item series

Inventory icons now load individual RGBA textures from `Resources/res/items/item0.png` through `item607.png`. The 543 drawable icons were repainted with the built-in image_gen tool using the original registered icon sheets as edit targets. The original `i0.png` through `i7.png` and actor/costume sprites remain available.

## Identity and layout

| File numbers | Original identity |
| --- | --- |
| 0–447 | i0–i6, 64 row-major cells per atlas |
| 448 | i7 diamond |
| 449–511 | Reserved i7 animation fragments; never substituted by the renderer |
| 512–583 | i7 extended weapon icons, encoded as 0x8000 + local index |
| 584–607 | Native hand equipment, encoded as 0x8100 + hero * 8 + tier |

All 608 files are exactly 256×256. Two empty extended cells stay transparent. Large i7 spinning-coin frames stay on their original atlas; they are not interchangeable with single-cell item icons. Numbering, item tables and saves do not change.

`manifest.json` records each source rectangle, original icon identity, output file, occupied bounds and original-file hashes. `output/item-series/generation.json` contains all generation prompts and the project-local generated sheet paths. The selected sheets are retained under `output/item-series/generated/`. The weapon sheet's irregular row/column spacing is registered using its actual transparent gutters before slicing. Three individually inspected sample repaints are used for item217, item264 and item336.

## Rendering

`ItemSeriesCatalog.h` translates original icon IDs and exact 32px atlas rectangles into series indices. `DrawImageScale` and `RotateImage` substitute textures before source-space clipping and raster rounding. A legacy zoom is multiplied by 32/256, preserving logical dimensions and callers' layout. Partial source crops, pseudo-icons and large animation frames are excluded.

`DrawItemSeriesInBox` fits the occupied bounds using one uniform scale, supports 90-degree rotation and preserves the existing alpha/tint/outline pipeline. Equipment boxes, the warehouse and combat board use the same identity as the reel. Recipe overlays now fit a whole icon instead of sampling its upper-left 20px. The new range uses smooth texture sampling. Missing textures fall back to the original rendering path.

## Reproduction and validation

From the repository root:

```text
python tools/items/build_item_series.py build
python tools/items/build_item_series.py verify
tools\items\test_catalog.cmd
python tools/items/verify_runtime.py
```

The catalog test checks legacy/extended IDs, invalid boundaries, animation exclusions and preserved logical sizes. Asset validation checks dimensions, RGBA, transparency, required artwork and unchanged original hashes. Runtime review loads all 543 textures through the actual DrawIcon path, checks texture identity/dimensions, exercises tinted outlines and rotated/alpha thumbnails, and captures ten catalog pages. Scene review captures twenty castle states and fifteen regional backgrounds at both 640×850 and 640×1408.

The verified build is `proj.win32/Debug.win32/cs_items.exe`. It was built with `PreviewTargetName=cs_items` and `BuildProjectReferences=false` to reuse the existing engine DLL while another game process had it loaded. Full build log: `output-item-series-build.log`. Runtime artifacts: `output/item-series/runtime/`. Side-by-side asset gallery: `output/item-series/index.html`.

The repaints are generated artwork: detailed ornament and contour interpretation can differ from the low-resolution originals. The comparison gallery retains the source beside each result for item-specific review.
