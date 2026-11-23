# UI text and buttons

The minimum text size is the resume dialog title at font zoom `1.0` on a
640-pixel-wide canvas (Pretendard Bold, 24-pixel font size). Scale it uniformly
with `DX / 640`; do not reduce the horizontal scale independently.
`DrawTextStrSystem` enforces this floor, including legacy text callers.

There are two button types, declared in `Classes/Func_Graphics.h` and implemented
in `Classes/UiButtonControls.inc`:

- `DrawUiButton`: text only.
- `DrawUiButtonIcon`: icon and text as one centered group; empty text centers the icon.

Both own the frame, caption, minimum size, wrapping, disabled appearance and
touch rectangle. Use `UiButtonStyle` for colors and an optional existing frame
or icon renderer. Do not add a new button renderer for a color or icon variant.
The existing overloads remain compatibility adapters for older callers.
The style has an explicit 4-byte packing contract: legacy game headers change
packing, so its callback layout must not depend on the including source file.

Caption width comes from the actual TTF font. Vertical placement uses measured
glyph bounds rather than caller-specific baseline offsets. Long text wraps at
the minimum size; a button grows vertically when needed, and its registered
touch rectangle grows with it. Callers must reserve enough row spacing for the
result. Reserve at least 48 logical pixels for either type. The icon type also
supports `style.stacked` for collection widgets, using the same measured caption
layout and minimum size.

## Default frame and simple dialogs (2026-11-23)

Every `DrawUiButton` / `DrawUiButtonIcon` now draws the gold frame
(`DrawUiGoldFrame`: shadow, brown rim, bright gold, deep gold, inner brown line,
gradient body, top highlight) unless the style passes its own `frame`. This is
the same look as the merge-battle buttons and the resume dialog. Do not draw
teal reference panels or image buttons for new UI.

Simple popups (OK, YES/NO) are one shape: `DrawUiDialog(title, message, note,
buttonCount, labels, funcs, fills, enabled)`. It dims the screen, draws
`DrawUiPanel` (dark teal fill 0x163C46, gold edge 0xE4C374, bottom inner line
inside the edge), the three text rows, and 1..3 gold buttons at
`UiDialogButtonRect(i, count)`. Pass `funcs` to register touch; pass null and
read `UiDialogButtonRect` yourself when the caller handles touches (the merge
resume/quit prompts do). The legacy `AlertDraw` (`SetAlert`) renders through it,
so inventory-full, sell, exit and notice alerts share the shape. Card-style
boards (`CdDrawFrame`, IAP/treasure purchase) are not simple popups and keep
their own frame.

Use `DrawUiTextBox` for explanatory text in a known rectangle. A paragraph is
separate from its button; do not draw an extra label over a button or compensate
with a local `titleLift`/Y offset. The resume popup reserves explicit space for
its title, question, warning and two actions.

Native reviews:

```powershell
python tools/lobby/verify_resume_prompt.py --exe cs.exe
python tools/lobby/verify_entry_choice.py --exe cs.exe
python tools/lobby/verify_box_info.py --exe cs.exe --purchase-flow
python tools/lobby/verify_equipment_stats.py --exe cs.exe
```
