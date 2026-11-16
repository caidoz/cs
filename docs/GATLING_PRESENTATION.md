# Stage 4 Gatling presentation

- Castle index 3 fires 12 small metallic rounds per burst instead of six cannonballs.
- Launches alternate every 2 and 3 simulation ticks (24 rounds/second at 60 Hz), twice the previous rate of one round per 5 ticks.
- Rounds follow straight paths and use a 13 x 4 reference-pixel silhouette, without the cannonball's ghost trail.
- Six barrel mouths orbit a projected elliptical front plate; each round starts at its barrel position at release.
- Muzzle flashes and hit effects are reduced for machine-gun fire. Other turret types retain their presentation.
- Damage still commits once, after the last round arrives.

Validation: tools/merge_roulette/test_turret.cmd; Debug Win32 cs_gatling build; CS_MERGE_TURRET_REVIEW at 640x850 and 640x1408 (40 captures each).
