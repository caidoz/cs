Castle mist v2 — runtime resources, 2026-11-15

Ten approved castle identities: timber/crown, boar, knight, turtle, lion,
sun/teal, phoenix, eagle, amethyst eye, royal sun/blue.

Each numbered directory contains the chassis, five empty rooms, two rotating
spoke discs, a fully opaque shallow-convex combat facade, and a tower-mounted
weapon. Castle 01 also has the empty catapult arm used after stone release.
101 runtime PNGs total. Characters, equipment and damage fonts remain native.

The source directory preserves the generated clean sprite masters.
Repartition with tools/art/partition_mist_castles.py (Pillow and numpy).
Registration uses the existing 1089 x 1445 castle canvas and fixed screen
anchors. Castle size does not grow when a skin or artillery upgrade changes.
Wheel tyres and chassis joints stay fixed; only the inner spoke discs rotate.

Turret rear collars are seated in the tower sockets. Each castle uses its own
weapon image; six artillery upgrade levels grow its width and bore in engine.
Stone, shell, guided missile, rapid fire and laser keep their dedicated attack
resources and damage timelines. The loaded cup starts below-left of its pivot.

Backgrounds retain all fifteen original regional resource sets and parallax.
Classes/StageBackgroundSeam.inc applies background-only matte grading:
far saturation .24 / contrast .64, middle .30 / .70, rail .48 / .80,
distant boss .30 / .68, with gray-blue atmospheric mixing.
These are rendering values, not a destructive overwrite of the source PNGs.
They do not apply to player/companion sprites, equipment or foreground enemies.

Runtime registration: CastleMistNames.inc, CastleMistTurretNames.inc,
CastleMistWheels.inc, MergeCastleMist.inc, MergeCastleLobbyRebuild.inc.
Review: tools/art/verify_mist_resources.py captures all ten lobby/combat pairs
and all fifteen regional backgrounds at 640x850 and 640x1408.
The HTML gallery is output/mist-live-review/index.html.
