from pathlib import Path
from PIL import Image

SOURCE = Path(r"C:/Users/polyp/.codex/generated_images/01a0ad19-e9c6-79c3-9634-d83b8c4e5d36/exec-fc47a3cb-0bf1-44ab-b8f3-761257b91698.png")
OUT = Path("Resources/res")
PREVIEW = Path("output/castles/wheels/castle_wheels_preview.png")

sheet = Image.open(SOURCE).convert("RGBA")
cell_w = sheet.width / 5.0
cell_h = sheet.height / 2.0
wheels = []

for tier in range(10):
    col, row = tier % 5, tier // 5
    cell = sheet.crop((round(col * cell_w), round(row * cell_h),
                       round((col + 1) * cell_w), round((row + 1) * cell_h)))
    alpha = cell.getchannel("A")
    bbox = alpha.getbbox()
    if bbox is None:
        raise RuntimeError(f"wheel {tier} has no visible pixels")
    wheel = cell.crop(bbox)
    side = max(wheel.size)
    square = Image.new("RGBA", (side, side))
    square.alpha_composite(wheel, ((side-wheel.width)//2, (side-wheel.height)//2))
    square = square.resize((128, 128), Image.Resampling.LANCZOS)
    square.save(OUT / f"castle_wheel{tier}.png", optimize=True)
    wheels.append(square)

PREVIEW.parent.mkdir(parents=True, exist_ok=True)
preview = Image.new("RGBA", (5*160, 2*184), (22, 27, 39, 255))
for tier, wheel in enumerate(wheels):
    x, y = (tier % 5)*160+16, (tier // 5)*184+12
    preview.alpha_composite(wheel, (x, y))
preview.save(PREVIEW, optimize=True)
print(PREVIEW)
