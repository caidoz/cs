# Castle 2–10 continuous outer armor

Generated with the built-in image generation tool. The user's ten-castle concept image was the reference for each castle. One 1024×1536 portrait sprite pair was generated per castle, then baked into left and right wall resources at each castle's room-stack height.

Prompt template:

> Use case: stylized-concept. Create one production-ready 2D game sprite for castle {number} of the attached concept lineup. A single CONTINUOUS full-height pair of outer armor hulls, LEFT and RIGHT, for a TALL {number}-storey modular castle, not repeated floor frames. Portrait composition 1024x1536. The entire middle vertical space between the sides is CLEAR AND EMPTY for {number} stacked 512x128 interior rooms, while the left and right armored flanks run unbroken from top to bottom. The LEFT flank bears a {animal head}, consistent with the reference art, integrated into the outer armor rather than floating. The right flank has matching buttresses, shields and architectural motifs. Keep each flank relatively slender next to the empty room opening, but full-height massive and coherent. Material theme: {theme}; hand-painted crisp pixel-art inspired fantasy game asset matching the attached concept's material and lighting. No roof or spires, no wheels, no gun, no room, no character, no landscape, no words. Transparent background and genuinely transparent central opening. The flanks must terminate with flat horizontal matching top and bottom attachment edges.

| Castle | Theme | Left sculpture |
| --- | --- | --- |
| 2 | Grey stone and iron keep, blue slate and banner | Stone ram |
| 3 | Red brick royal castle, blue fleur-de-lis | Gold lion |
| 4 | White limestone knight castle, cobalt and gold | White-and-gold eagle |
| 5 | Teal copper and brass clockwork fortress | Bronze clockwork bull |
| 6 | Black iron and crimson dragon fortress | Red-and-black dragon |
| 7 | White and blue ice crystal castle | Faceted ice lion |
| 8 | Dark violet amethyst Gothic castle | Amethyst gargoyle |
| 9 | Black obsidian and crimson dragon castle | Black-and-red dragon |
| 10 | White marble, sapphire and gold celestial castle | Gold celestial lion |

The baked side sprites leave the 512-pixel room area untouched. Each castle has six distinct source illustrations: `castle_XX_wall_pair_stage_0.png` through `_stage_4.png`, plus the original `castle_XX_wall_pair.png` for stage 5. The baker selects the matching source for each grade; it no longer changes wall width or brightness by grade. Castles 9 and 10 have a second upper section because their wall stack exceeds 1024 pixels.


For stages 0 and 3, the image-generation prompt preserved each castle's material theme and transparent middle opening while making stage 0 structurally simple and stage 3 more armored. Stages 1, 2, and 4 used precise-object-edit with adjacent grades as references, adding larger animal sculptures, buttresses, armor, banners, crystals, or machinery. Every source uses a 1024x1536 transparent canvas.
