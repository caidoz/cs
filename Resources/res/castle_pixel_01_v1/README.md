# Muted pixel castle, stage 1

`source.png` is the toned built-in image_gen edit of the approved castle study.
The architecture stays detailed; walnut, ochre and violet replace the brighter palette.

`tools/art/partition_pixel_castle.py` aligns the source with the existing 1089x1445
castle coordinates and extracts the transparent hull, five rooms, two independent
rotating wheels and an opaque timber closure. The closure is a flat rectangular
wall replaced by `cover-convex-source.png`: a shallow convex fortified wall with
receding side faces and integrated reinforcement, generated with built-in image_gen.
Nearest sampling keeps the pixel edges sharp.

Only castle 1 uses these parts. The original reference assets, UI, characters,
native turret animation and other castle stages remain available and unchanged.
Rendering is in `OriginalCastle::pixelHull` and `drawBattleCover`.

## Turrets

`turret-source.png` is a separate built-in image_gen pixel shading edit of the
original turret atlas. `partition_pixel_turrets.py` packs its 60 upgrade parts
into the existing frame coordinates in `turret-atlas.png`. All ten turret types
and their six upgrades use this muted atlas in world rendering and action icons.
Existing muzzle coordinates, articulated animation and attack timings are retained.
