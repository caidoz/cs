# Castle 2-10 spire sheets

Generated with the built-in image generation tool. Each castle's
`Resources/res/castle_exterior/castle_XX_hollow_stage_0.png` was used as a
structural and style reference. The output sheets are
`castle_XX_spire_sheet.png` in this directory.

Common prompt: six transparent front-orthographic roof crowns in a two-column,
three-row sheet, stages 0 through 5. Every stage retains the same horizontal
baseline and a full-width lower parapet to meet the 640px castle shell.
Stage 0 is a modest single or few-tower crown; each later stage adds towers,
height, reinforcement and theme-specific ornament. Preserve each castle's
materials and avoid rooms, vertical walls, wheels, battle decks, people,
labels, perspective and stretched towers.

| Castle | Theme |
| --- | --- |
| 2 | gray stone forge fortress with royal blue roofs and banners |
| 3 | red brick and terracotta lion battlements |
| 4 | white limestone and cobalt blue eagle fortress |
| 5 | teal copper clockwork domes, brass gears and smokestacks |
| 6 | black volcanic iron and scarlet dragon fortress |
| 7 | white stone, blue-and-gold crystal fortress |
| 8 | violet gothic stone, amethyst and pointed arches |
| 9 | black obsidian, red lava and dragon-wing roof projections |
| 10 | white marble royal palace, blue roofs and gold celestial heraldry |

`build_castle02_10_spires.ps1` bakes each sheet to six exact 640px-wide
roof assets at its castle-specific height. The scale is uniform within each
castle's six stages; the original hollow crown's lower 48px closes the seam.
