"""Pack the authored 10x6 pixel-art atlas into existing room resource slots.

Each room uses a 256x64 logical pixel grid, enlarged to 512x128 with nearest
sampling. No image IDs or text-table slots are added.
"""
from pathlib import Path
import json
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "content/castles/pixel_rooms"
RUNTIME = ROOT / "Resources/res"


def build():
    master = Image.open(SOURCE / "master_10x6.png").convert("RGBA")
    preview = Image.new("RGBA", (1536, 640))
    entries = []
    for floor in range(10):
        for stage in range(6):
            box = (round(stage * master.width / 6),
                   round(floor * master.height / 10),
                   round((stage + 1) * master.width / 6),
                   round((floor + 1) * master.height / 10))
            logical = master.crop(box).resize((256, 64), Image.Resampling.NEAREST)
            room = logical.resize((512, 128), Image.Resampling.NEAREST)
            name = f"castle_room_{floor + 1:02d}_{stage}.png"
            room.save(RUNTIME / name, optimize=True)
            preview.alpha_composite(logical, (stage * 256, floor * 64))
            entries.append({"file": name, "floor": floor + 1, "stage": stage,
                            "sourceRect": box, "size": [512, 128]})
    preview.save(SOURCE / "preview_10x6.png", optimize=True)
    (SOURCE / "manifest.json").write_text(json.dumps({
        "source": "master_10x6.png", "logicalSize": [256, 64],
        "sampling": "nearest", "rooms": entries}, indent=2), encoding="utf-8")
    for entry in entries:
        room = Image.open(RUNTIME / entry["file"]).convert("RGBA")
        assert room.size == (512, 128) and room.getbbox() == (0, 0, 512, 128)
        # Every authored logical pixel stays an exact 2x2 block at runtime.
        assert room.tobytes() == room.resize((256, 64), Image.Resampling.NEAREST).resize(
            (512, 128), Image.Resampling.NEAREST).tobytes()
    print("60 rooms packed: existing names, 512x128, exact 2x2 pixel grid OK")


if __name__ == "__main__":
    build()
