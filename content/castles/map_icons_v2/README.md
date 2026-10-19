# Current castle map and PVP entrance icons

Ten new transparent icons generated with built-in imagegen, referencing the
current `individual_castles_v4` base exteriors. Full prompts and references are
in `generation-prompts.json`; untouched generated originals are in `originals`.

The current architectural identities are retained, including the wooden gabled
watchhouse, flat sandstone bastion, blue granite spire, green basalt dome,
armored iron block, turquoise stepped pyramid, red gothic roofs, blue barrel
vault, irregular crystal cluster and asymmetric blue-domed royal palace.

Unlike the previous map icons, these have no ground slabs. Two circular wheels
form the bottom contact line. `register_map_icons_v2.py` fits each original
uniformly into a transparent 1024x1024 canvas and records the measured opaque
wheel contact in `Classes/Data/CastleMapIconLayout.h` and `manifest.json`.
Generated source files are not repainted by the exporter.

Runtime PNGs replace the existing `Resources/res/castle_map_icons/castle_map_01`
through `castle_map_10` resources, keeping their image IDs and boot cache path.
The friend map and selected-castle entrance therefore share the same current
icons. The entrance fits both sides into the same icon box, mirrors the right
icon and aligns both measured wheel contacts. It does not use the assembled
castle renderer or inherit the lobby camera/room/crew state.

`verify_pvp_icon_entrance.ps1` draws ten complementary pairs so every icon is
checked on both sides, with resource IDs, mirroring, equal icon scale, shared
wheel baseline and screen bounds, and captures the completed entrance.
