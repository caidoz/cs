# Castle 2-10 combat deck sprite sheets

Generated with the built-in image generation tool. Reference:
`Resources/res/castle_exterior/castle_01_combat_deck_stage_0.png` for castle 2,
then the castle 2 sheet for castles 3-10.

Common prompt: six stage-specific transparent game sprites in a two-column,
three-row sheet; straight-on side-view battle deck, approximately six times
wider than tall, consistent alignment; flat open standing surface for allies,
solid chassis fascia above separately rendered wheels; stages 0-5 add
reinforcement, motifs and richer materials within the same castle theme.
No room, roof, wheels, characters, labels, text, perspective tilt, flying
thrusters or flared side walls.

| Castle | Theme |
| --- | --- |
| 2 | gray stone forge fortress, cobalt blue and restrained gold heraldry |
| 3 | red brick lion fortress, timber bracing to iron and gold lion heraldry |
| 4 | white limestone and cobalt blue eagle fortress |
| 5 | teal copper clockwork industrial castle |
| 6 | black iron and red dragon fortress |
| 7 | white stone, icy blue crystal and silver |
| 8 | violet gothic stone, amethyst and black iron |
| 9 | black volcanic stone, scarlet dragon iron and embers |
| 10 | white marble, royal blue steel and gold celestial heraldry |

The source sheets are `castle_XX_combat_deck_sheet.png` in this directory.
`build_castle02_10_combat_decks.ps1` bakes them into exact 736x144 runtime
parts with width-only scaling and the existing 512x64 stage-specific chassis.
