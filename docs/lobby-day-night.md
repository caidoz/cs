# Lobby day/night preview

The lobby runs a 300-second visual day, starting at 09:00. Time advances using
Core::Run delta seconds while the lobby is active, independent of frame rate.
Leaving the lobby pauses it; returning resumes it. This does not change stage
progression, combat, rewards, or IsStageNight(). The existing DAY/stage UI still
describes gameplay; the small clock near the zoom buttons describes the preview.

The palette now evolves through morning, noon, afternoon and an extended dusk,
without the former 8:00–15:30 near-constant daylight interval. The forest extends
below screen bottom to cover gaps between menu buttons. castle9's baked clouds
were removed with image_gen (backup in output/castles/cloud-removal), and four
separate lobby_cloud.png sprites drift across the background in 2–4 minutes.

`Classes/LobbySkyCycle.h` defines duration, starting hour and smooth color keys.
`Classes/LobbySkyRender.h` draws the gradient, tinted landscape, drifting clouds,
fading moon/stars, flapping birds and a pterosaur. Castle sprites retain their
original lighting, including baked window/torch highlights.

`Resources/res/lobby_landscape.png` is a built-in image_gen transparent mountain
and forest layer. Its resource ID and Text.h entry are loaded at startup.
The sky fills any screen aspect without stretching the landscape. Small parallax
follows castle panning; sky and moon remain anchored to the screen. Landscape
uses the same scale on both axes. High castle levels increase bird count.

Animation defaults: 300 seconds per day; birds flap at 5 radians/sec;
pterosaur traverses in 24 seconds every 36 seconds, visible on lobby entry; slow cloud drift with
independent phases; stars twinkle at differing frequencies. All are procedural
geometry, so no frame atlas or background image swapping is required.

Validation: tools/castles/test_sky_cycle.cpp checks period, palette bounds,
continuity and midnight wrapping. Windows preview build can use
`/p:ForceImportAfterCppTargets=<absolute path to tools/castles/preview.targets>`
on the solution with PreBuildEventUseInBuild=false and PreLinkEventUseInBuild=false to avoid
overwriting an already-running simulator executable or DLLs.

The distant landscape responds to 8% of zoom changes and 6% of camera travel.
The new transparent `lobby_foothills.png` layer responds to 25% and 20%, respectively.
Both layers use uniform scaling, overscan and bounded travel to cover the screen.
Two cloud sprites render behind the castle and two translucent clouds render in
front; birds and the pterosaur render above the castle, below characters and UI.

Lobby navigation is Shop / Equipment / Adventure / Castle / Dungeon. Castle opens
two entries routing to the existing castle management and crew screens. Debug
castle selection is at the lower left, held zoom controls at the lower right.
The blue start button uses win.png (512,272,512,131), with IMG_LIGHTNING and the
existing admission cost. The castle camera reserves space above this footer so
the start button no longer covers characters at the castle base.
