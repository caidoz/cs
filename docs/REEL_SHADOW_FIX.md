# Reel shadow clipping

`ShadowImage` compared screen-space clip limits against unscaled texture width
and height. At reel symbol scale this could enlarge the source crop beyond its
atlas cell, or leave enlarged shadows outside the reel window.

The renderer now intersects the scaled destination with the clip rectangle first,
then converts the intersection back to floating-point source coordinates. It
rejects empty intersections and non-positive scales before acquiring a sprite.
Fractional source coordinates avoid truncation at moving reel boundaries.

`tools/items/verify_reel_shadows.py` runs the actual renderer at 640x850 and
640x1408. The review checks nine edge positions at 0.5x, 1x and 2x, asserting both
source atlas bounds and destination clip bounds, including fully clipped and zero
scale cases. It captures three moving/stopped reel states and the existing castle
and battle review scenes. Captures and checks are under
`output/item-series/runtime/reel-shadow-*`.

Build: `proj.win32/Debug.win32/cs_reel_shadow.exe`.
