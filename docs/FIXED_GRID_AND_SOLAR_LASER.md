# Fixed grid and final castle

Grid cells are always 80 reference pixels multiplied only by the shared 640-wide UI coordinate scale. No board-width, available-height, stage, or row-count fit affects cell size. Grid bottom is fixed at 286 reference pixels above the scene origin, above the roulette. The castle/deck remain anchored independently.

Stages 1-9 retain their 16-32 cells, up to 8 columns by 4 rows. Stage 10 is 8 columns by 5 rows: two centered cells on top (`0x18`), then four complete 8-cell rows. Total 34. The top pair occupies the central gap between status plates. Stage changes align blocks to the bottom; legacy 10-wide layouts repack without dropping blocks.

The final gun mount moves from native x=384 to x=352, 32 pixels farther into the tower. Its laser differs from the flame and violet discharge: a straight white/gold core, two intertwined golden rails and three travelling bright pulse packets. Muzzle charge and one damage event are preserved.

Validation: model tests include 9-to-10 bottom alignment, legacy 34-block migration, save roundtrip and 5000 random operations; turret/combat tests; Debug Win32 cs.exe build; actual fixed-grid/platform and turret captures at 640x850 and 640x1408.
