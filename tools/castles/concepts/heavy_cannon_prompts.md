# Heavy cannon art and six-grade bake

The existing command-post sprites are the visual references for grades 0–4. The built-in image generator produced one transparent grade-5 cannon for each late castle, saved as `castle_07_heavy_cannon_final.png` through `castle_10_heavy_cannon_final.png`.

Prompt mode: `precise-object-edit`. Image 1 was each castle's existing `balcony_stage_5.png`, used for style and identity. The request was a right-facing isolated cannon head with a much thicker bore, a heavy mount, a moderately short barrel, transparent background, and no balcony, room, wheels, scenery, text, or characters. Theme details by castle:

| Castle | Grade-5 weapon |
| --- | --- |
| 7 | Icy blue crystal emitter with a broad silver housing |
| 8 | Amethyst plasma cannon with thick violet energy coils |
| 9 | Obsidian dragon thermal cannon with a wide red muzzle |
| 10 | White-gold celestial sapphire laser cannon |

`build_castle02_10_heavy_cannons.ps1` trims transparent margins and bakes all 54 cannon sprites into a fixed 128x64 canvas. Across the six grades, the visible cannon grows in bore and height more than length. Castles 7–10 use the generated art at grade 5; the lower grades preserve their existing themed cannon details.
