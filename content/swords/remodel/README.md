# Sword inventory remodel

Each tile is 32×32 pixels. `Ttree` occupies eight cells in a 3×4 canvas: two broad canopy rows and two central trunk cells. The inventory sprite and Robin's held sword use the same PNG; `pivotX/Y` marks the grip and `handScale` preserves the previous approximate combat reach after the canvas changes.

| No. | Original item | Shape | Direction |
|---:|---|---|---|
| 1 | STICK | 1×2 | Short blunt wooden sword |
| 2 | LONG | 1×2 | Simple straight sword |
| 3 | CUTTER | 1×2 | Short curved cutter |
| 4 | RUIN | 2×2 | Broad crystal blade |
| 5 | SEEKER | 1×3 | Long narrow blade |
| 6 | DOUBLE | 2×2 | Broad twin-edge blade |
| 7 | ELVEN | 2×2 | Squat crystal head |
| 8 | ROYAL | 2×2 | Broad royal blade |
| 9 | GHOST | 2×2 | Broad hooked blade |
| 10 | GHOST2 | 2×3 | Long dark blade |
| 11 | FRAME | 2×3 | Wide flame blade |
| 12 | ICE | 2×3 | Wide ice blade |
| 13 | THUNDER | 2×3 | Wide energy blade |
| 14 | EARTH | 2×3 | Long stone blade |
| 15 | LAEVATEINN | 2×3 | Character-shaped wide head |
| 16 | STORMBRINGER | 2×3 | Heavy dark blade |
| 17 | CALADBOLG | 2×3 | Heavy rainbow blade |
| 18 | BALMUNG | 1×4 | Blue spear, artwork 20% longer than the former 96px version |
| 19 | HRUNTING | 2×3 | Curved red blade |
| 20 | GIANT | 2×3 | Broad stone weapon |
| 21 | MISTILTEINN | T, 3×4 | Original 64×128 tree with canopy width enlarged 50%; trunk unchanged |
| 22 | EXCALIBUR | 2×3 | Broad gold blade |
| 23 | HOLY | 2×3 | Broad triangular blade |
| 24 | DARK | 2×3 | Wide hammer head and narrow grip |
| 25 | LEO | 2×3 | Heavy lion-guard blade |
| 26 | DEATH | 2×4 | Red spear, artwork 20% longer than the former 96px version |
| 27 | DRAGONCLOW | 2×3 | Curved claw blade |
| 28 | DRAGONTOOTH | 2×3 | Curved tooth blade |
| 29 | DRAGONGOD | 2×3 | Broad crystal blade |
| 30 | DRAGONSLAYER | 2×4 | Heavy curved blade |
| 31 | ULTIMATE | 2×4 | Heavy green blade |
| 32 | DIMENSIONAL | 2×4 | Centred magical blade |
| 33 | HEAVEN | 2×4 | Wide winged blade |
| 34 | STARDUST | 2×4 | Wide energy blade |
| 35 | KING | 2×4 | Heavy dark blade |

`source-atlas.png` was created with the built-in image-generation tool using the original 35-sword review sheet as its reference. Prompt: “Preserve the order and visual identity of each numbered sword. Redraw each as crisp hand-painted pixel art on transparent background, one full upright sword per isolated cell, with short stout early swords, wide or T-shaped middle swords, and large wide late swords.” Run `tools/swords/build_remodeled_swords.ps1` to bake the 35 game PNGs, `manifest.json`, and `Classes/Data/SwordSprites.h` from that atlas.

Swords 18 and 26 use the original atlas art, stretched vertically from 96px to 115px (20%) within 128px-tall canvases. Sword 21 uses `tree21-original.png`; only its canopy is widened by 50%, tapering back to the untouched trunk from y=45 to y=65.

Dimensions in sword number order (1–35), seven entries per row:

```text
[
  [1x2, 1x2, 1x2, 2x2, 1x3, 2x2, 2x2],
  [2x2, 2x2, 2x3, 2x3, 2x3, 2x3, 2x3],
  [2x3, 2x3, 2x3, 1x4, 2x3, 2x3, 3x4],
  [2x3, 2x3, 2x3, 2x3, 2x4, 2x3, 2x3],
  [2x3, 2x4, 2x4, 2x4, 2x4, 2x4, 2x4]
]
```

Sword 21 uses the only T-shaped mask, occupying eight cells in a 3x4 canvas. Sword 24 occupies a full 2x3 rectangle.
