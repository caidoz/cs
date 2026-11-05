# Castle upgrade parts

Built-in `image_gen` output, copied unchanged with its alpha channel. The final prompt set is in `prompts.json`.

| Castle | Atlas | Palette / crest |
|---|---|---|
| 1 | parts.png | Golden timber / purple crown |
| 2 | parts-02.png | Sandstone / red boar |
| 3 | parts-03.png | Silver stone / blue crossed swords |
| 4 | parts-04.png | Dark stone / emerald turtle |
| 5 | parts-05.png | Riveted steel / blue lion |
| 6 | parts-06.png | Ivory / teal gear |
| 7 | parts-07.png | Dark stone / crimson phoenix |
| 8 | parts-08.png | Marble / blue silver eagle |
| 9 | parts-09.png | Obsidian / amethyst eye |
| 10 | parts-10.png | Marble / blue golden sun |

Each PNG is 1536×1024: six levels across, four categories down (spire, exterior armor, interior window, wheel). Lv.0 retains the original game art; Lv.1–5 use the corresponding attachment. Cannons reuse the existing six authored cannon levels for each castle.

These are fitted attachments to the approved castle body. They do not replace, rescale or move its hull, outdoor combat deck, hero standing position or wheel axles. Their mounting coordinates use the original castle source pixels. The eighth castle uses its actual dome cap rather than its barrel-vault roof as its spire mount.

`tools/castles/measure_upgrade_cosmetics.py` only measures alpha bounds and emits metadata; it never edits the generated image pixels. Runtime draw calls crop the registered sprite rectangles and preserve uniform scale. `Classes/Data/CastleUpgradeCosmetics.h` is the generated registration table.
