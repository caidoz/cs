# Uniform companion zoom on the grid

Grid companions previously derived zoom from each motion's bounding width and height. This made narrow or short characters grow and broad or tall characters shrink.

All 64 grid companions now use native zoom 1.5 multiplied only by the shared UI coordinate scale (DX/640). The character, animation bounds, tile size, grade and caller fraction never change that grid zoom. Bounds still position the character's feet. Authored differences in character stature remain visible. Resident and reel rendering retain their own context-specific sizes.

Validation: `CS_GRID_CREW_SCALE_REVIEW` renders all 64 companions on four pages and checks the zoom recorded by the real grid rendering route, at 640x850 and 640x1408. Preview executable: `proj.win32/Debug.win32/cs_uniform_grid_crew.exe`.
