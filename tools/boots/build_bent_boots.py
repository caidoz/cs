"""Bake the authored L-shaped footwear sheets into 128x128 inventory tiles.

Each tile uses the same 2x2 layout as GridGearPart: the upper-left 64x64
quarter is empty, while cuff, toe and heel occupy the other three quarters.
"""

from pathlib import Path
from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[2]
SOURCE = Path(__file__).resolve().parent / "bent_source"
OUTPUT = ROOT / "Resources" / "res"

# Some adjacent boots in the edited reference sheets touch at a few pixels.
# These boundaries were inspected against all three source sheets.
CUTS = {
    "robin": [0, 298, 554, 834, 1110, 1373, 1628, 1898, 2170],
    "diana": [0, 310, 573, 834, 1093, 1358, 1622, 1895, 2172],
    "maxx": [0, 309, 574, 840, 1100, 1360, 1625, 1902, 2170],
}


def visible_bounds(image: Image.Image):
    return image.getchannel("A").point(lambda a: 255 if a > 16 else 0).getbbox()


def discard_neighbor_fragments(icon: Image.Image) -> None:
    """Remove pieces from the adjacent boot where two source silhouettes touch."""
    alpha = icon.getchannel("A")
    remaining = {(x, y) for y in range(128) for x in range(128)
                 if alpha.getpixel((x, y)) > 8}
    components = []
    while remaining:
        stack = [remaining.pop()]
        component = set(stack)
        while stack:
            x, y = stack.pop()
            for point in ((x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)):
                if point in remaining:
                    remaining.remove(point)
                    stack.append(point)
                    component.add(point)
        components.append(component)
    if not components:
        return
    main = max(components, key=len)
    for component in components:
        if component is main:
            continue
        for x, y in component:
            icon.putpixel((x, y), (0, 0, 0, 0))


def bake() -> None:
    preview = Image.new("RGBA", (8 * 132, 3 * 132), (24, 27, 35, 255))
    draw = ImageDraw.Draw(preview)
    for row, hero in enumerate(("robin", "diana", "maxx")):
        with Image.open(SOURCE / f"{hero}.png") as file:
            sheet = file.convert("RGBA")
        cuts = CUTS[hero]
        if cuts[-1] != sheet.width:
            raise ValueError(f"{hero}: sheet width changed; inspect split points")
        for index in range(8):
            region = sheet.crop((cuts[index], 0, cuts[index + 1], sheet.height))
            bounds = visible_bounds(region)
            if bounds is None:
                raise ValueError(f"{hero} {index}: no visible art")
            region = region.crop(bounds)
            # Slightly widen the bent toe while keeping the tall cuff. This
            # gives the lower-left tile a real silhouette rather than only a
            # thin tip, and still leaves four transparent pixels on the right.
            region = region.resize((112, 112), Image.Resampling.LANCZOS)
            icon = Image.new("RGBA", (128, 128), (0, 0, 0, 0))
            icon.alpha_composite(region, (12, 8))
            icon.paste((0, 0, 0, 0), (0, 0, 64, 64))
            discard_neighbor_fragments(icon)
            path = OUTPUT / f"item_boots_{hero}{index}.png"
            icon.save(path, optimize=True)
            preview.alpha_composite(icon, (index * 132, row * 132))
            draw.rectangle((index * 132, row * 132, index * 132 + 63,
                            row * 132 + 63), outline=(90, 110, 130, 255))
    preview.save(Path(__file__).resolve().parent / "bent_boots_preview.png")


if __name__ == "__main__":
    bake()
