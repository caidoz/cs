"""Build the ten-castle, five-part, five-level modular art set.

Source sheets are 1536x1024 RGBA atlases.  Their five columns are upgrade
levels and their five horizontal bands are the authored parts.  Every output
is placed on a fixed-size transparent canvas so attachment points and room
dimensions never change between castles or levels.
"""
from pathlib import Path
import json
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "content" / "castles" / "modular_v2" / "source"
OUTPUT = ROOT / "Resources" / "res" / "castle_parts"
PREVIEW = ROOT / "content" / "castles" / "modular_v2" / "preview.png"
HOVER_SOURCE = ROOT / "content" / "castles" / "modular_v2" / "hover_mobility.png"
NAME_INCLUDE = ROOT / "Classes" / "CastleModularNames.inc"

CASTLE_COUNT = 10
LEVEL_COUNT = 5
SOURCE_SIZE = (1536, 1024)

# Source bands are deliberately separated at the transparent gutters.
PARTS = (
    ("roof",     0, 260, (384, 150), "bottom"),
    ("trim",   260, 410, (384,  72), "stretch"),
    ("room",   410, 595, (384, 112), "stretch"),
    ("cannon", 595, 735, (168, 104), "bottom"),
    ("mobility",735,1024, (384, 144), "assembled"),
)

THEMES = (
    "food production", "armory / forge", "barracks / training",
    "alchemy laboratory", "engineering workshop", "healing infirmary",
    "command room", "crystal reactor", "shadow sanctum",
    "celestial observatory",
)


def alpha_trim(image: Image.Image, padding: int = 2) -> Image.Image:
    box = image.getchannel("A").getbbox()
    if not box:
        raise ValueError("empty atlas cell")
    x0, y0, x1, y1 = box
    return image.crop((max(0, x0-padding), max(0, y0-padding),
                       min(image.width, x1+padding), min(image.height, y1+padding)))


def place_fixed(image: Image.Image, size: tuple[int, int], anchor: str) -> Image.Image:
    if anchor == "assembled":
        # The atlas authors the chassis and one wheel separately. Rebuild the
        # gameplay module with two wheels already sitting on the axle so this
        # fifth part is a single, connected silhouette.
        chassis = alpha_trim(image.crop((0, 0, image.width, 122)))
        wheel = alpha_trim(image.crop((0, 108, image.width, image.height)))
        chassis = chassis.resize((376, 74), Image.Resampling.LANCZOS)
        wheel.thumbnail((92, 92), Image.Resampling.LANCZOS)
        canvas = Image.new("RGBA", size)
        canvas.alpha_composite(chassis, (4, 4))
        wheel_y = 50
        canvas.alpha_composite(wheel, (54, wheel_y))
        canvas.alpha_composite(wheel, (size[0]-54-wheel.width, wheel_y))
        return canvas
    image = alpha_trim(image)
    if anchor == "stretch":
        # Floors must read as long, shallow rooms while keeping identical
        # connection edges across all castles and upgrade levels.
        image = image.resize((size[0]-8, size[1]-8), Image.Resampling.LANCZOS)
        canvas = Image.new("RGBA", size)
        canvas.alpha_composite(image, (4, 4))
        return canvas
    scale = min((size[0]-8) / image.width, (size[1]-8) / image.height)
    image = image.resize((max(1, round(image.width*scale)),
                          max(1, round(image.height*scale))), Image.Resampling.LANCZOS)
    canvas = Image.new("RGBA", size)
    x = (size[0] - image.width) // 2
    y = size[1] - image.height - 4 if anchor == "bottom" else (size[1] - image.height) // 2
    canvas.alpha_composite(image, (x, y))
    return canvas


def build() -> None:
    OUTPUT.mkdir(parents=True, exist_ok=True)
    manifest = {
        "version": 2,
        "castle_count": CASTLE_COUNT,
        "level_count": LEVEL_COUNT,
        "part_count": len(PARTS),
        "source_size": list(SOURCE_SIZE),
        "parts": {name: {"size": list(size), "anchor": anchor}
                  for name, _y0, _y1, size, anchor in PARTS},
        "themes": list(THEMES),
        "rule": "floors below the selected castle are level 5; the selected top floor uses its chosen level",
    }

    built: dict[tuple[int, str, int], Image.Image] = {}
    for castle in range(1, CASTLE_COUNT + 1):
        sheet = Image.open(SOURCE / f"castle_{castle:02d}.png").convert("RGBA")
        if sheet.size != SOURCE_SIZE:
            raise ValueError(f"castle_{castle:02d}: expected {SOURCE_SIZE}, got {sheet.size}")
        for level in range(1, LEVEL_COUNT + 1):
            x0 = round((level - 1) * sheet.width / LEVEL_COUNT)
            x1 = round(level * sheet.width / LEVEL_COUNT)
            for name, y0, y1, size, anchor in PARTS:
                fixed = place_fixed(sheet.crop((x0, y0, x1, y1)), size, anchor)
                path = OUTPUT / f"c{castle:02d}_{name}_l{level}.png"
                fixed.save(path, optimize=True)
                built[(castle, name, level)] = fixed

    # Roof is also the castle's exterior shell.  Its transparent centre leaves
    # every fixed-size room readable while themed pillars preserve the strong
    # outer silhouette from the concept art.
    for castle in range(1, CASTLE_COUNT + 1):
        for level in range(1, LEVEL_COUNT + 1):
            cap = built[(castle, "roof", level)]
            room = built[(castle, "room", level)]
            shell_h = 164 + castle * 92
            shell = Image.new("RGBA", (384, shell_h))
            shell.alpha_composite(cap, (0, 0))
            left = room.crop((0, 0, 42, 112)).resize((50, 96), Image.Resampling.LANCZOS)
            right = room.crop((342, 0, 384, 112)).resize((50, 96), Image.Resampling.LANCZOS)
            for floor in range(castle):
                py = 160 + floor * 92
                shell.alpha_composite(left, (0, py))
                shell.alpha_composite(right, (334, py))
            shell.save(OUTPUT / f"c{castle:02d}_roof_l{level}.png", optimize=True)
            built[(castle, "roof", level)] = shell

    # Castles 8-10 are flying fortresses.  Replace the wheeled base with a
    # true anti-gravity chassis, recoloured for each late-game theme.
    hover = Image.open(HOVER_SOURCE).convert("RGBA")
    for castle in range(8, 11):
        for level in range(1, LEVEL_COUNT + 1):
            x0 = round((level - 1) * hover.width / LEVEL_COUNT)
            x1 = round(level * hover.width / LEVEL_COUNT)
            piece = place_fixed(hover.crop((x0, 0, x1, hover.height)), (384, 176), "stretch")
            if castle == 9:
                px = piece.load()
                for yy in range(piece.height):
                    for xx in range(piece.width):
                        r, g, b, a = px[xx, yy]
                        if a and b > r * 1.15:
                            px[xx, yy] = (min(255, int(b*.72)), int(g*.32), min(255, b), a)
            elif castle == 10:
                px = piece.load()
                for yy in range(piece.height):
                    for xx in range(piece.width):
                        r, g, b, a = px[xx, yy]
                        if a and b > r * 1.15:
                            px[xx, yy] = (min(255, int(b*.92)), min(255, int(b*.72)), int(b*.25), a)
            piece.save(OUTPUT / f"c{castle:02d}_mobility_l{level}.png", optimize=True)
            built[(castle, "mobility", level)] = piece

    # Review image: all ten castles stacked according to the real floor rule.
    canvas = Image.new("RGBA", (CASTLE_COUNT * 424, 1500), (23, 31, 39, 255))
    for castle in range(1, CASTLE_COUNT + 1):
        cx = (castle - 1) * 424 + 20
        ground = 1450
        mobility = built[(castle, "mobility", 5)]
        base_y = ground - mobility.height
        canvas.alpha_composite(mobility, (cx, base_y))
        cannon = built[(castle, "cannon", 5)].resize((131, 81), Image.Resampling.LANCZOS)
        canvas.alpha_composite(cannon, (cx - 58, base_y - 76))
        roof_y = base_y - 136 - castle * 92
        first_room_y = roof_y + 164
        for floor in range(castle, 0, -1):
            room = built[(floor, "room", 5)]
            room_y = first_room_y + (castle - floor) * 92
            canvas.alpha_composite(room, (cx, room_y))
        trim = built[(castle, "trim", 5)]
        canvas.alpha_composite(trim, (cx, roof_y + 112))
        roof = built[(castle, "roof", 5)]
        canvas.alpha_composite(roof, (cx, roof_y))

    PREVIEW.parent.mkdir(parents=True, exist_ok=True)
    canvas.save(PREVIEW, optimize=True)
    (OUTPUT / "manifest.json").write_text(json.dumps(manifest, ensure_ascii=False, indent=2), encoding="utf-8")
    names = ["// Generated by tools/castles/build_modular_v2.py.\n",
             "// Kept as an include so Text.h stays reviewable; entries follow ImgDef order.\n"]
    for castle in range(1, CASTLE_COUNT + 1):
        for name, *_rest in PARTS:
            for level in range(1, LEVEL_COUNT + 1):
                names.append(f'\t"castle_parts/c{castle:02d}_{name}_l{level}",\n')
    NAME_INCLUDE.write_text("".join(names), encoding="utf-8")
    print(f"built {CASTLE_COUNT * LEVEL_COUNT * len(PARTS)} assets -> {OUTPUT}")
    print(f"preview -> {PREVIEW}")


if __name__ == "__main__":
    build()
