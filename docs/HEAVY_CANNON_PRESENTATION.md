# Tower gun placement and heavy iron rounds

Conventional tower guns are registered against the actual opening in each hull's
native 1089x1445 coordinates. Rear flange centres follow `OriginalCastle::box`,
which also positions the tower art. Gun size is capped to retain deck clearance
at higher upgrade levels. The first castle's catapult keeps its existing pivot.
Both the displayed gun and projectile emitter use `castleCannonBox`.

Solid projectiles use a separate shaded iron sphere instead of flat rectangle
strips. At 640px viewport width, standard rounds draw at 38px (previously about
16px), rapid-fire rounds at 30px, and catapult rounds at 44px. Three short fading
echoes reinforce motion without obscuring the sphere. Conventional guns fire in a
straight line; the catapult retains its lob. Solid rounds rotate 18 degrees per
simulation frame in the direction of travel. Muzzle flashes use existing
animated effects, and solid-round impacts are larger. Missile and laser identities,
combat damage, burst counts and damage application timing remain unchanged.

- Asset: `Resources/res/turret_attack/ironball.png` (256px transparent RGBA).
- Built-in image generation prompt and provenance: `output/turret-volume/generation.json`.
- Source atlas inspection: `output/turret-volume/towers-source.jpg`.
- Preview executable: `proj.win32/Debug.win32/cs_heavy_cannon.exe`.
- Runtime checks: `CS_MERGE_TURRET_REVIEW` captures preparation, launch, flight and
  impact for all ten castles, verifies projectile resources and burst counts, and
  checks that damage commits exactly once after arrival. Captures are under
  `output/item-series/runtime/heavy-cannon-*`.
