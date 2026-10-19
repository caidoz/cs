# Pixel castle interiors

The built-in image generation tool edited `modular_v5/rooms_10x6_catalog.png`
into `master_10x6.png`. This authored atlas replaces all ten room themes and
their six upgrade stages. The earlier illustrated masters remain available
under `modular_v5`.

Prompt specification: retain the six-column, ten-row layout, basic-to-ornate
upgrade progression, room themes and lower walking strips. Use classic
16-bit fantasy RPG pixel art with clear stepped silhouettes, clustered
shading, restrained palettes and dark outlines; remove painterly realism and
smooth gradients. Preserve rectangular room frames without labels or gutters.

Run `python tools/castles/build_pixel_rooms.py` to pack the atlas. Each panel
uses a 256x64 logical grid enlarged with nearest sampling to the existing
512x128 runtime contract. Files keep the names `castle_room_01_0.png` through
`castle_room_10_5.png`; existing IDs, resource names and loading paths apply.

The packer validates all 60 dimensions and exact 2x2 pixel blocks. Copy the
runtime assets into the executable's Resources folder when testing an existing
build. Restart the game to reload cached textures.
