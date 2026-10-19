# Inventory equipment pixel art

The castle inventory and warehouse load the PNGs in `Resources/res` directly.
The 35 Robin weapons include the previously approved wooden club (`w0_1.png`)
and final sword (`w0_35.png`). The remaining 223 newly generated equipment
sprites are rebuilt with `tools/equipment/build_pixel_art_inventory.ps1`.

The original PNGs in `originals/` are preserved so the conversion is
repeatable. The conversion keeps each image's dimensions and alpha channel
unchanged, which also keeps the existing inventory cell masks intact. Run
`tools/equipment/check_pixel_art_inventory.py` to validate every output.

The Robin sword atlas was edited with the built-in image generation tool using
this prompt: "Restyle this exact 35-sword transparent atlas as detailed crisp
2D pixel art, preserving all 35 objects in exact grid positions and colors."
`tools/swords/build_remodeled_swords.ps1` uses the edited atlas while retaining
the two approved per-sword overrides.

After another source-art regeneration, run the pixel-art builder again before
building the game. It restores the reviewed inventory style from `originals/`.

Robin, Diana and Maxx each have eight tiers of helmets, armor/vests/coats,
pants, boots and gloves, redrawn in five transparent pixel-art sheets per hero.
The image-generation prompts preserved each item's color, silhouette and tier
order while requesting visible pixel clusters, stepped shading and dark
outlines. Run `tools/equipment/extract_hero_pixel_sheets.ps1` to sample the
sheets onto the native half-resolution pixel grid. This creates 120 native
sources; the general pixel-art builder picks them up automatically. Boots
retain their empty upper-left inventory cell. Armor/vest/coat tiers 1–6 are
64x64 (2x2 cells), while tiers 7–8 are 64x96 (2x3 cells) with longer hems.

Diana's 35 inventory guns and Maxx's 35 inventory boomerangs were edited from
seven-item transparent strips. The edit prompt asked for one connected gun per
slot, visible boomerang arcs, stronger pixel clusters and the original tier
colors. `tools/equipment/extract_weapon_pixel_strips.ps1` samples each edited
strip onto a half-resolution grid, then restores the exact native image size.
It also clips boomerangs to their existing occupied cells and removes any
disconnected crop fragments. Combat-only weapon sprites remain separate.

Robin's tree weapon (`w0_21.png`) uses a 96x96 three-row sprite and a 0x772
tile mask. The top row of the four-row inventory area stays available when the
tree sits on the bottom three rows. Its held-weapon scale stays at 1.0.
