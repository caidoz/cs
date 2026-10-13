"""Read-only validation of the inventory pixel-art resource conversion."""

from pathlib import Path
import json
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
originals = ROOT / "content/equipment/pixel_art/originals"
resources = ROOT / "Resources/res"
hero_sources = [ROOT / f"content/equipment/pixel_art/{hero}/native_sources"
                for hero in ("robin", "diana", "maxx")]
hero_sources += [ROOT / f"content/equipment/pixel_art/inventory_{weapon}/native_sources"
                 for weapon in ("gun", "boomerang")]
hero_sources.append(ROOT / "content/swords/remodel/pixel_overrides")
files = sorted(originals.rglob("*.png"))
mismatches = []
before = after = reduced = 0
redrawn_count = 0
for original in files:
    relative = original.relative_to(originals)
    target = resources / relative
    redrawn = next((folder / relative for folder in hero_sources
                    if (folder / relative).exists()), None)
    expected = redrawn or original
    redrawn_count += redrawn is not None
    with Image.open(expected) as source, Image.open(target) as result:
        a = source.convert("RGBA")
        b = result.convert("RGBA")
        if a.size != b.size or a.getchannel("A").tobytes() != b.getchannel("A").tobytes():
            mismatches.append(str(target))
        ca = len(a.getcolors(a.width * a.height) or [])
        cb = len(b.getcolors(b.width * b.height) or [])
        before += ca
        after += cb
        reduced += cb < ca

print(f"sprites={len(files)}, palette_reduced={reduced}, rgba_colors={before}->{after}")
print(f"overridden_pixel_sources={redrawn_count}")
print(f"dimension_or_alpha_mismatches={len(mismatches)}")
for name in mismatches[:10]:
    print(name)
if len(files) != 223 or redrawn_count != 191 or mismatches:
    raise SystemExit(1)

for hero, armor in (("robin", "armor"), ("diana", "vest"), ("maxx", "coat")):
    for tier in range(8):
        with Image.open(resources / f"item_{armor}_{hero}{tier}.png") as body:
            expected_size = (64, 96) if tier >= 6 else (64, 64)
            if body.size != expected_size:
                raise SystemExit(f"{hero} armor {tier} is {body.size}, expected {expected_size}")
            if tier >= 6 and body.convert("RGBA").getchannel("A").crop((0, 64, 64, 96)).getbbox() is None:
                raise SystemExit(f"{hero} armor {tier} has an empty third tile")
        with Image.open(resources / f"item_boots_{hero}{tier}.png") as boot:
            alpha = boot.convert("RGBA").getchannel("A")
            if alpha.crop((0, 0, 64, 64)).getbbox() is not None:
                raise SystemExit(f"{hero} boot {tier} occupies the reserved empty tile")
print("armor_tier_7_8_size=64x96; boot_empty_corners=ok")

manifest = json.loads((resources / "inventory_boomerang/manifest.json").read_text(encoding="utf-8-sig"))
for record in manifest:
    with Image.open(resources / f"inventory_boomerang/{record['id']}.png") as image:
        alpha = image.convert("RGBA").getchannel("A")
        for top_row in range(record["rows"]):
            for col in range(record["cols"]):
                bit = 1 << ((record["rows"] - 1 - top_row) * 4 + col)
                if record["cells"] & bit:
                    continue
                rect = (col * 32, top_row * 32, (col + 1) * 32, (top_row + 1) * 32)
                if alpha.crop(rect).getbbox() is not None:
                    raise SystemExit(f"boomerang {record['id']} occupies empty cell {col},{top_row}")
print("boomerang_empty_cells=ok")
