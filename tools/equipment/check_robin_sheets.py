"""Read-only measurements for the generated Robin source strips."""
from pathlib import Path
from PIL import Image

root = Path(__file__).resolve().parents[2] / "content/equipment/pixel_art/robin"
for kind in ("helm", "armor", "pants", "boots", "glove"):
    with Image.open(root / f"{kind}-pixel-sheet.png") as file:
        image = file.convert("RGBA")
    a = image.getchannel("A")
    print(kind, image.size)
    for i in range(8):
        x0 = round(i * image.width / 8)
        x1 = round((i + 1) * image.width / 8)
        region = a.crop((x0, 0, x1, image.height))
        bbox = region.getbbox()
        edges = sum(region.getpixel((x, y)) > 16 for x in (0, x1-x0-1) for y in range(image.height))
        print(i, bbox, 'edge_pixels', edges)
