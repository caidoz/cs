# Battle menu implementation

The lower menu preserves the full physical inventory grid. Current castles use four rows (24 to 48 cells); the row-based layout also supports six-row grids without shrinking cells vertically. A cell is exactly 48x48 screen pixels in both the combat grid and warehouse. No width/height fallback shrinks cells. Twelve columns span 576px; grids whose cells fit the viewport remain centred regardless of decorative frame padding. Wider cell areas retain horizontal controls and edge panning. The same pan offset carries between preparation and battle. The warehouse always reserves four complete rows (192px); packing and visible height use the same four-row limit. Available screen height never compresses the warehouse; the castle and rail rise instead.

## Flow

1. Lobby defaults to the lower world position.
2. Starting opens warehouse preparation below the world. The inventory grid sits above the warehouse items; drag/drop uses the same displayed cell size. The foreground, rail and castle rise together.
3. Completing setup enters the first five-choice shop before combat. The preparation world height is shared with the warehouse layout.
4. Starting combat slides the shop out and lowers the full grid above a compact combat control. The world descends with it. Pausing keeps this compact layout.
5. A new offer raises the menu and world again. The existing wave/offer/purchase paths remain responsible for advancing combat.

`BattleMenuLayout.h` defines cell, row, ground clearance and interpolation rules. `GetStageSceneGroundY()` combines the actual grid height and menu state. The native castle drawing, rail background, HP cards, part anchors and artillery muzzle follow the resulting world position. Menu movement affects foreground layers, while the distant background remains fixed. No full-width rectangular backdrop covers the lower menu. The scenery remains visible behind the individual grid cells, item cards and buttons. Warehouse preparation hides the world-map distance ornament and the five main navigation tabs.

## Validation

- `tools/castles/test_battle_menu_layout.cpp`: minimum four rows, literal 48px cells across widths and complete horizontal scroll bounds, six-row height growth and reversible interpolation.
- `tools/castles/verify_battle_menu.ps1`: isolated account, actual warehouse pickup/drop coordinates, initial shop, compact combat, pause, shop return, castle-10 warehouse/shop and six captures.
- The review-only window defaults to 640x725; -ScreenHeight 900 tests a taller viewport. The normal window configuration is unchanged.

Build the preview and run:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File tools/castles/verify_battle_menu.ps1
```

Captures and checks are written to `output/battle-menu-flow-review/`.

The 48px UI review verifies the castle-10 grid centre, both cell sizes and four fully visible warehouse rows, and checks item hit areas against the warehouse bounds.

Preparation is modal: outside taps are consumed without closing, and back/lobby navigation is blocked before combat. The option menu cannot abandon a run until combat has started. The isolated review verifies both blocked exits, unchanged energy, and an explicit abandon after combat starts.

Debug builds default BATTLE_DEBUG_MAX_GRID to 1 in Func_Draw.cpp: grid masks, frames and displayed cell totals use the final castle layout for every selected castle. Castle visuals, cannon theme and progression still use the selected castle. Set the flag to 0 to restore castle-specific layout; non-debug builds use normal layouts.
Warehouse dragging covers the star header and the full footer, including the setup button. Setup queues admission only after a short release inside the button; horizontal drags and cancelled touches do not activate it. The isolated review exercises header/footer/button swipes, a button tap and touch cancellation.
