# Companion battle decks

Ten additive exterior walkway sprites generated with the built-in imagegen
tool, referencing the current wooden castle for rendering style. The saved
prompts are in `generation-prompts.json`; untouched RGBA outputs are in
`originals`. Material variants follow the ten current castle exteriors.

The registrar copies original files unchanged to `Resources/res/castle_crew_decks`
and records the opaque crop and walking-surface anchor. No generated castle
facade, room, weapon or wheel asset is replaced.

`DrawIndividualCastle` splits the existing exterior just above the axles.
The upper body, its rooms, cannon and commander platform rise by 96 world
pixels at a 640px viewport. The lower chassis and wheel contacts stay fixed.
The companion deck attaches to the chassis in this newly opened space, with
edge support posts and unobstructed headroom. Wheels render in front of the
lower fascia. Both active companions and lobby loadout samples share the same
walking surface. Castle width and body proportions are preserved; the extra
height is included in placement bounds and size queries.

Verification: `verify_individual_v4.ps1` checks all ten castle placements,
rotating wheels, room dimensions, deck sprite availability, the lower tier's headroom
and foot clearance above the wheels and all six companion foot anchors, with runtime screenshots.
