# Crystal weapon proportions

The blue crystal sword (detail 6) has a square legacy image but a one-column, two-row gameplay footprint. Uniform fitting to the narrow column made the grid artwork only about one cell high.

Weapon grid artwork now fills its declared cell rectangle rather than using a minimum width/height fit. Rotation preserves the same occupied dimensions. Grid cells remain fixed at 80 reference pixels.

Early crystal costume swords authored on square canvases keep their original hand anchor and rotation, with local width multiplied by 0.65 and length by 1.35. Their length increases instead of shrinking the weapon to hide the mismatch. Inventory/reel icons remain independent.

Validation: grid catalog including rotated weapons (8 live pages), costume/weapon orbit/attachment checks at 640x850 and 640x1408 (5 captures each). Preview executable: `proj.win32/Debug.win32/cs_two_cell_weapon.exe`; the user's running cs.exe was left running.

Rendering follow-up: `AfterSpriting` immediately visits sprites when rendering to a texture. Applying local scale after `RotateImage` returned therefore missed that frame's output. `RotateImageAxes` now establishes both axes before submission; the existing public `RotateImage` keeps its original uniform behavior. Costume crystals use 0.65 width and 1.35 length before drawing, retaining the hand anchor. Rotated grid weapon sizing uses the same correction. Verified with actual costume captures and all eight rotated grid catalog pages. Updated preview: `proj.win32/Debug.win32/cs_long_crystal_sword.exe`.
