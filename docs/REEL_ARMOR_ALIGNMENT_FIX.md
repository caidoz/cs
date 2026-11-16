# Armor identity and stopped companion alignment

`DrawGridItemInBox` resolves torso gear through the same `GetItemIcon` and
`DrawItemSeriesInBox` path as inventory/reel icons. This covers all 24 armor tiers
across the three heroes and prevents independently repainted grid art from
changing the item's visual identity. Upright weapon grid resources remain intact.

Reel companions and their ground shadows move up six reference pixels together.
The intro reel previously used its 108px symbol pitch as the drawing box height,
even though the visible window is shorter. Symbol spacing is now independent of
the drawing box: both rolling and stopped symbols use the actual window height.
This keeps their foot baseline consistent when the reel stops.

Validation uses the grid catalog's real draw routes (including every armor tier
and rotation), a stopped companion/armor/weapon fixture at 640x850 and 640x1408,
and the moving reel shadow review. Captures are under
`output/item-series/runtime/reel-match-*`.

Preview: `proj.win32/Debug.win32/cs_reel_match.exe`.
