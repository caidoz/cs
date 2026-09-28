"""Split the approved castle-10 master into aligned modular gameplay layers."""
from pathlib import Path
from PIL import Image, ImageEnhance, ImageFilter

ROOT = Path(__file__).resolve().parents[2]
MASTER = ROOT / "content/castles/modular_v3/castle_10_master.png"
OUT = ROOT / "Resources/res/castle_parts"
PREVIEW = ROOT / "content/castles/modular_v3/castle_10_preview.png"
SIZE = (1024, 1536)

ROOM_HOLE = (360, 340, 664, 1220)
CANNONS = (
    (88, 510, 365, 710), (659, 510, 936, 710),
    (45, 790, 360, 1005), (664, 790, 979, 1005),
    (0, 1030, 365, 1215), (659, 1030, 1024, 1215),
)
CROWN = (120, 0, 904, 360)
MOBILITY = (90, 1168, 934, 1536)


def clear_rect(image: Image.Image, box: tuple[int, int, int, int]) -> None:
    image.paste((0, 0, 0, 0), box)


def region_layer(master: Image.Image, boxes) -> Image.Image:
    layer = Image.new("RGBA", SIZE)
    for box in boxes:
        layer.alpha_composite(master.crop(box), (box[0], box[1]))
    return layer


def pack_runtime(image: Image.Image) -> Image.Image:
    """Pack a 1024x1536 layer into a legacy-renderer-safe 2048x768 atlas."""
    atlas = Image.new("RGBA", (2048, 768))
    atlas.alpha_composite(image.crop((0, 0, 1024, 768)), (0, 0))
    atlas.alpha_composite(image.crop((0, 768, 1024, 1536)), (1024, 0))
    return atlas


def grade(image: Image.Image, level: int, alpha_floor: float = .68) -> Image.Image:
    factor = .72 + level * .056
    result = ImageEnhance.Brightness(image).enhance(factor)
    result = ImageEnhance.Color(result).enhance(.76 + level * .048)
    if level < 5:
        a = result.getchannel("A").point(
            lambda value: int(value * (alpha_floor + (1-alpha_floor)*level/5)))
        result.putalpha(a)
    return result


def clean_background(image: Image.Image) -> Image.Image:
    """Remove ImageGen's dark matte while retaining dark painted outlines."""
    rgb = image.convert("RGB")
    mask = Image.new("L", image.size)
    source = rgb.load()
    target = mask.load()
    for y in range(image.height):
        for x in range(image.width):
            r, g, b = source[x, y]
            target[x, y] = 255 if max(r, g, b) > 132 or max(r, g, b)-min(r, g, b) > 58 else 0
    mask = mask.filter(ImageFilter.MaxFilter(11)).filter(ImageFilter.GaussianBlur(1.5))
    original_alpha = image.getchannel("A")
    mask = Image.frombytes("L", image.size,
                           bytes(a*m//255 for a, m in zip(original_alpha.tobytes(), mask.tobytes())))
    result = image.copy()
    result.putalpha(mask)
    return result


def build() -> None:
    OUT.mkdir(parents=True, exist_ok=True)
    master = Image.open(MASTER).convert("RGBA")
    if master.size != SIZE:
        master = master.resize(SIZE, Image.Resampling.LANCZOS)
    master = clean_background(master)

    shell = master.copy()
    clear_rect(shell, ROOM_HOLE)
    clear_rect(shell, CROWN)
    clear_rect(shell, MOBILITY)
    for box in CANNONS:
        clear_rect(shell, box)

    crown = region_layer(master, (CROWN,))
    mobility = region_layer(master, (MOBILITY,))

    for level in range(1, 6):
        pack_runtime(grade(shell, level, .88)).save(OUT / f"c10_roof_l{level}.png", optimize=True)
        pack_runtime(grade(crown, level, .45)).save(OUT / f"c10_trim_l{level}.png", optimize=True)

        # Two, four, then six visible batteries as the artillery is upgraded.
        count = 2 if level == 1 else 4 if level < 4 else 6
        cannon = region_layer(master, CANNONS[:count])
        pack_runtime(grade(cannon, level, .58)).save(OUT / f"c10_cannon_l{level}.png", optimize=True)
        pack_runtime(grade(mobility, level, .55)).save(OUT / f"c10_mobility_l{level}.png", optimize=True)

    preview = grade(shell, 5, .88)
    for floor in range(10, 0, -1):
        room = Image.open(OUT / f"c{floor:02d}_room_l5.png").convert("RGBA")
        room = room.resize((300, 88), Image.Resampling.LANCZOS)
        preview.alpha_composite(room, (362, 346 + (10-floor)*88))
    preview.alpha_composite(grade(crown, 5, .45))
    preview.alpha_composite(grade(region_layer(master, CANNONS), 5, .58))
    preview.alpha_composite(grade(mobility, 5, .55))
    PREVIEW.parent.mkdir(parents=True, exist_ok=True)
    preview.save(PREVIEW, optimize=True)

    print("castle 10 v3: exterior, crown, artillery and propulsion layers built")


if __name__ == "__main__":
    build()
