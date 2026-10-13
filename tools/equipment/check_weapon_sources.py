"""Read-only checks for regenerated inventory gun and boomerang art."""
from pathlib import Path
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
BASE = ROOT / "content/equipment/pixel_art"


def components(image):
    alpha = image.convert("RGBA").getchannel("A")
    remaining = {(x, y) for y in range(image.height) for x in range(image.width)
                 if alpha.getpixel((x, y)) > 16}
    sizes = []
    while remaining:
        start = remaining.pop()
        stack = [start]
        size = 1
        while stack:
            x, y = stack.pop()
            for dx in (-1, 0, 1):
                for dy in (-1, 0, 1):
                    if dx == dy == 0:
                        continue
                    p = (x + dx, y + dy)
                    if p in remaining:
                        remaining.remove(p)
                        stack.append(p)
                        size += 1
        sizes.append(size)
    return sorted(sizes, reverse=True)


for kind in ("gun", "boomerang"):
    folder = BASE / f"inventory_{kind}/native_sources/inventory_{kind}"
    detached = []
    for n in range(1, 36):
        with Image.open(folder / f"{n}.png") as image:
            sizes = components(image)
            if len(sizes) > 1 and sizes[1] >= 8:
                detached.append((n, sizes[:4]))
    print(kind, "detached_components", detached)
    if detached:
        raise SystemExit(1)
