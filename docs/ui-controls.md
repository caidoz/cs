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
