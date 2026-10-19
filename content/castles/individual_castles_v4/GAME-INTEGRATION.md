# Game integration

The ten selected complete exterior PNGs are registered in
`Resources/res/castle_individual_v4`. Original images are retained without
nonuniform stretching. Circular inner wheel overlays rotate with rail travel;
the original outer wheel rim remains in the complete exterior.

`tools/castles/register_individual_v4.py` reproduces resource registration,
wheel crops, image names and measured actor/muzzle anchors. It checks strictly
increasing display widths/heights and a maximum reference height of 761 pixels.
Widths run from 342 to 411, heights from 293.8 to 760.2. Overall width growth is
14.8% of height growth. Viewport scale uses the 640-pixel design width.

The complete exterior renderer is the default in lobby, battle and PVP.
`CS_LEGACY_CASTLE_ART=1` restores the previous modular renderer for authoring.
Existing upgrade stats are preserved; all upgrade levels currently share the
new base exterior. Separate upgraded artwork is pending. Existing room assets
are restored behind measured apertures. A completed tap on the castle toggles
the whole room stack open/closed; release keeps the selected state. UI controls,
camera drags and pinches do not toggle the interior. State is kept per castle
for the current process and is not saved to player progress.
All castles use one room column: castle one has one floor, castle ten has ten
vertical floors. Room width is 140 and floor height 40 in shared 640px-world
units; the viewport/camera applies a common scale. Rooms are centered within
the measured safe body apertures, raised 4 world pixels above their bottom, without fitting
their dimensions separately to each exterior.

The hero presentation multiplier is doubled (1.5 to 3.0) for lobby/VS renders.
Indoor residents are enlarged by 2.25 relative to the original presentation
(another 1.5 over the previous 1.5); deployed crew retain their existing scale.
The compact common room geometry and its authored aperture bounds were checked for
all ten castles, including the final ten-floor stack, with open/closed captures.
Residents remain concealed until opened; deployed crew use the front walkway and the hero
uses the right terrace. The original narrow-screen vertical camera remains.

Rooms now use the intact 512x128 originals registered by
`tools/castles/register_rectangular_rooms.py`, via separate rectangular-room
resource IDs. Each floor uses its own theme/upgrade texture; silhouette-cut
stack textures remain exclusive to the legacy renderer. Their central walls
are checked for full opacity across all 60 source files.

The individual renderer now follows the quantized lobby camera zoom and its
screen anchor, including room/hero/crew coordinates. Lobby zoom range is 0.5–2.
Owned companions are assigned directly to room slots (up to the existing
64-person rendering capacity); the old eight-person cap and decorative-slot
assignment limit no longer discard residents. Unowned filler characters are
kept only for the legacy decorative renderer.

`verify_individual_v4.ps1 -Height 1400 -RoomReveal -InteriorSync` checks all ten
castles with twenty owned residents, intact room resources, zoom out/in,
uniform floor dimensions and open/closed behavior in an isolated profile.

Validation: Debug Win32 build; `verify_individual_v4.ps1` at 900 and 1400 window
heights (ten placement/progression checks, ten wheel rotation checks and twenty
captures per run). PVP was captured separately to inspect mirroring and layout.
The normal game binary is `proj.win32/Debug.win32/cs.exe`.

VS uses the same per-castle width/height ratios as the lobby, with one common
camera reduction to fit both castles. It no longer normalizes both hull widths.
In Debug builds, Q/A select next/previous left exterior and W/S select
next/previous right exterior (01 through 10, wrapping). The overlay lists the
selected IDs. Overrides are visual only and reset on entering a new PVP match;
saved ownership, upgrades, equipment and combat stats remain unchanged.
