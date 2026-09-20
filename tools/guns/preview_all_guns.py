# -*- coding: utf-8 -*-
"""Generate a composite preview image of all 35 guns."""
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont

ROOT = Path(__file__).resolve().parents[2]
RES_DIR = ROOT / 'Resources/res'
PROFILES = ROOT / 'content/guns/profiles.json'
OUT_PNG = Path('C:/Users/polyp/.gemini/antigravity/brain/72bb5645-bbbe-4c05-bdda-08bf1d5a7cdf/diana_all_35_guns_preview.png')

def make_preview():
    import json
    with open(PROFILES, 'r', encoding='utf-8') as f:
        profiles = json.load(f)

    # 5 rows x 7 cols
    cols = 7
    rows = 5
    cell_w = 160
    cell_h = 120
    img = Image.new('RGBA', (cols * cell_w + 20, rows * cell_h + 40), (28, 30, 38, 255))
    draw = ImageDraw.Draw(img)

    try:
        font_title = ImageFont.truetype('C:/Windows/Fonts/malgunbd.ttf', 16)
        font_label = ImageFont.truetype('C:/Windows/Fonts/malgun.ttf', 12)
        font_sub = ImageFont.truetype('C:/Windows/Fonts/malgun.ttf', 10)
    except Exception:
        font_title = font_label = font_sub = None

    draw.text((20, 10), "Diana 35 Guns Lineup Preview (w1_1 ~ w1_35)", fill=(255, 255, 255, 255), font=font_title)

    for p in profiles:
        idx = p['id'] - 1
        col = idx % cols
        row = idx // cols
        cx = 10 + col * cell_w
        cy = 35 + row * cell_h

        # cell box
        draw.rectangle([cx + 2, cy + 2, cx + cell_w - 4, cy + cell_h - 4], outline=(55, 60, 75, 255), fill=(36, 38, 48, 255))

        # load gun image
        gun_im = Image.open(RES_DIR / p['filename']).convert('RGBA')

        # draw 2x scaled gun centered in top part of cell
        scale = 2
        gun_scaled = gun_im.resize((gun_im.width * scale, gun_im.height * scale), Image.Resampling.NEAREST)

        gx = cx + (cell_w - gun_scaled.width) // 2
        gy = cy + 12 + (60 - gun_scaled.height) // 2
        img.paste(gun_scaled, (gx, gy), gun_scaled)

        # text label
        label = f"{p['filename']}: {p['name']}"
        sub = f"({p['width']}x{p['height']}) grip=({p['grip_x']},{p['grip_y']})"
        draw.text((cx + 8, cy + 78), label, fill=(220, 220, 240, 255), font=font_label)
        draw.text((cx + 8, cy + 96), sub, fill=(160, 170, 190, 255), font=font_sub)

    OUT_PNG.parent.mkdir(parents=True, exist_ok=True)
    img.save(OUT_PNG)
    print(f"Saved preview to {OUT_PNG}")

if __name__ == '__main__':
    make_preview()
