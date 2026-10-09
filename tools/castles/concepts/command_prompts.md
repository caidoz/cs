# Castle 2-10 command posts and defensive cannon

Generated with the built-in image generation tool. The source reference for
each castle was its existing
`Resources/res/castle_exterior/castle_XX_balcony_stage_0.png`.
The generated sheets are `castle_XX_command_sheet.png` in this directory.

Common prompt: six transparent orthographic right-side command post sprites
in a two-column, three-row sheet, stages 0 to 5. Every stage has the same
left castle connector, floor baseline and open left-middle standing space for
one hero. A separately readable defensive cannon sits at the far right and
grows in barrel size, mount armor and mechanical complexity through the six
stages. The cannon must not occupy the hero's standing space. No characters,
room interior, wheels, spires, text or background.

| Castle | Command-post material and cannon progression |
| --- | --- |
| 2 | gray stone, wrought iron to blue-steel fortress gun |
| 3 | red brick and bronze, lion-armored cannon |
| 4 | white limestone and blue-steel eagle gun |
| 5 | teal copper, brass gears and steam cannon |
| 6 | black volcanic iron, scarlet dragon ember cannon |
| 7 | white stone, blue crystal cybernetic coil gun |
| 8 | violet gothic stone, amethyst cybernetic beam emitter |
| 9 | black obsidian, scarlet dragon plasma cannon |
| 10 | white marble, royal blue and gold celestial railgun |

Across castle numbers the cannon becomes larger and more cybernetic, while
each castle keeps its own theme. `build_castle02_10_commands.ps1` bakes the
sheets to 54 exact 192x128 runtime assets without nonuniform scaling.
