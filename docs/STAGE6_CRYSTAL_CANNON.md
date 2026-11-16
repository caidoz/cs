# Stage six crystal projectile

Castle index 5 uses a translucent teal crystal orb instead of the shared iron ball. The reference diameter remains 38 pixels. Straight flight, rotating facets, pulsing aura and fading copies create a magic trail. At contact the orb expands and fades over 14 ticks while six mint sparks spread radially. Damage timing is unchanged.

Asset: `Resources/res/turret_attack/crystal-orb.png` (256x256 RGBA), generated with built-in imagegen and resized for the game. Registered as `TURRET_CRYSTAL_ORB_IMG`.

Prompt:

Single isolated fantasy game projectile sprite on truly transparent background: a round translucent teal emerald crystal orb, irregular faceted glass/crystal surface, luminous white mint magical core, bright cyan cracks and tiny golden light flecks suspended inside. Nonmetallic, no metal rims, no rivets, no casing. Soft compact turquoise magical aura just outside its circular silhouette, three tiny star sparks, no long tail. Stylized hand painted pixel-edged medieval fantasy game art, rich material shading, reads clearly at 38 pixels. Centered square composition, orb and compact glow occupy 90 percent of canvas. No text, no UI, no scenery, no ground shadow.

Validation: turret presentation unit checks; Debug Win32 `cs_crystal_cannon.exe`; actual render review at 640x850 and 640x1408.

Platform follow-up: stage six uses a 52 reference pixel deep perspective stone floor, spanning ground + 36 to ground - 16 around feet at ground + 8. Built into the normal `proj.win32/Debug.win32/cs.exe`. Verified with `CS_MIST_RESOURCE_REVIEW` at 640x850 and 640x1408; screenshots under `output/item-series/runtime/stage6-platform-*`.
