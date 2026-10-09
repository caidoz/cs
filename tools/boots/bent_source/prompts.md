Built-in imagegen, precise-object-edit mode. Each of the three original
character footwear rows in `../source/` was used as its own edit target.

Prompt: Preserve the eight footwear designs, left-to-right order, colors,
materials, ornaments, and pixel-art painting style. Make each boot a more
pronounced L shape for a 2x2 inventory grid: ankle/cuff rises on the right,
thick toe and sole extend across the bottom-left tile, heel fills the
bottom-right tile, and the upper-left tile remains empty. Transparent
background, separated sprites, no text or extra items.

`../build_bent_boots.py` crops these edited sheets into 24 transparent
128x128 inventory PNGs and clears the unused upper-left quadrant.
