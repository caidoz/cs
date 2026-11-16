# Roulette overflow and discard

Spinning no longer requires three empty cells. It requires no unresolved tray results and a valid board without overlapping or out-of-shape blocks. Existing life/spin/animation/turn guards remain.

A trash target sits to the right of the roulette, above the wheel and away from bottom action buttons. Drag a pending reel result or a placed board block onto it to discard exactly that block. Discarding costs nothing and refunds nothing. Pending results remain individually selectable; empty reel positions clear as results are removed. A normal spin turn completes when all results have been placed or discarded.

When automatic placement fails, results remain in the tray. A second spin is rejected without charging. Attacking no longer silently destroys leftover results: the player must place or explicitly discard them.

Validation: model checks cover full-board spins, unresolved-result blocking, overlap blocking, individual discard, invalid indices and save roundtrip. Live review pays for a spin with zero free cells, attempts a blocked repeat, drags all three results to the trash, and verifies one removal each, unchanged board/heart charge, and normal turn completion, at 640x850 and 640x1408.

Preview: `proj.win32/Debug.win32/cs_roulette_trash.exe`.

The final object is a cute SD silver galvanized tin can matching the user's reference photo, with small eyes, vertical flutes and a domed lid. Two alpha sprites crossfade between closed and open lid poses. Dragging within 16 reference pixels of the object opens it; dropping there swallows one block, briefly bounces the body and closes the lid.

Asset: `Resources/res/roulette/trash-object.png` (512x256 RGBA, two registered frames), generated with built-in imagegen and resized/aligned for runtime.

Prompt:

Use the attached photograph only as the object/material reference: ordinary silver galvanized tin trash can with vertically fluted cylindrical body, round domed removable lid and small loop handle. Create a CUTE SD game sprite sheet with exactly TWO equal panels side by side on truly transparent background. LEFT: closed lid, friendly two small black oval eyes on front below rim, squat rounded chibi proportions. RIGHT: identical tin trash can same body size/base/angle with lid tipped up/back like a mouth opening, dark smooth cavity visible, cheerful eyes. Keep unmistakably SILVER TIN, subtle blue grey metal shadows, broad soft white highlights, simple vertical grooves, little side handles. NO WOOD, no gold or brass, NO teeth, no fangs, no heavy machinery or joints, no scary mimic, no elaborate ornament, no recycle logo, no text. Soft simple hand-painted pixel-edged casual fantasy RPG asset, readable at 64 pixels. Each pose centered in its half, same base height, modest transparent padding, no background no floor no cast shadow, no UI border. Closed and open lid poses only.
