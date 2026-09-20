# -*- coding: utf-8 -*-
"""
tools/boomerangs/test_maxx_boomerang_poses.py
Visualizes Maxx holding each of the 35 boomerangs (IMG_C2_82 hand scale = 0.58x)
and rotating/flying as a projectile (IMG_C2_83 scale = 1.0x).
"""
import os
import json
from PIL import Image, ImageDraw, ImageFont

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ARTIFACT_DIR = r"C:\Users\polyp\.gemini\antigravity\brain\72bb5645-bbbe-4c05-bdda-08bf1d5a7cdf"
PROFILES_PATH = os.path.join(ROOT, "content", "boomerangs", "profiles.json")

def simulate_hand_poses():
    with open(PROFILES_PATH, "r", encoding="utf-8") as fp:
        profiles = json.load(fp)

    cols = 7
    rows = 5
    cell_w = 170
    cell_h = 160
    header_h = 70
    margin = 16

    total_w = margin * 2 + cols * cell_w
    total_h = header_h + margin + rows * cell_h

    canvas = Image.new("RGBA", (total_w, total_h), (20, 22, 28, 255))
    draw = ImageDraw.Draw(canvas)

    font_title = None
    font_body = None
    for fn in ["malgun.ttf", "gulim.ttc", "arial.ttf"]:
        fp = os.path.join(r"C:\Windows\Fonts", fn)
        if os.path.exists(fp):
            try:
                font_title = ImageFont.truetype(fp, 18)
                font_body = ImageFont.truetype(fp, 12)
                break
            except Exception:
                pass
    if font_title is None:
        font_title = ImageFont.load_default()
        font_body = font_title

    draw.text((margin, 14), "MAXX BOOMERANG HAND POSE & PROJECTILE TEST (0.58x HAND / 1.0x FLY)", fill=(255, 220, 100, 255), font=font_title)
    draw.text((margin, 40), "Left: 0.58x held in hand (red circle = hand pivot) | Right: 1.0x thrown projectile", fill=(170, 180, 200, 255), font=font_body)

    for i, prof in enumerate(profiles):
        r = i // cols
        c = i % cols
        cx = margin + c * cell_w
        cy = header_h + r * cell_h

        is_orig = i in [0, 3, 6, 9, 12, 15, 18, 21]
        border_color = (120, 200, 255, 200) if is_orig else (60, 70, 90, 150)
        draw.rectangle([cx + 4, cy + 4, cx + cell_w - 4, cy + cell_h - 4], fill=(26, 30, 38, 255), outline=border_color, width=1)

        img_path = os.path.join(ROOT, "Resources", "res", prof["filename"])
        if os.path.exists(img_path):
            bim = Image.open(img_path).convert("RGBA")

            # 1. Left side: Hand held (0.58x scale)
            kHandScale = 0.58
            hand_w = max(1, int(bim.width * kHandScale))
            hand_h = max(1, int(bim.height * kHandScale))
            held = bim.resize((hand_w, hand_h), Image.NEAREST)

            held_center_x = cx + 45
            held_center_y = cy + 70

            held_top_left = (held_center_x - hand_w // 2, held_center_y - hand_h // 2)
            canvas.alpha_composite(held, held_top_left)

            # Red pivot dot representing Maxx's hand position
            draw.ellipse([held_center_x - 3, held_center_y - 3, held_center_x + 3, held_center_y + 3], fill=(255, 50, 50, 255), outline=(255, 255, 255, 255))

            # 2. Right side: Thrown projectile (0.8x preview scale)
            proj_scale = 0.8
            pw = max(1, int(bim.width * proj_scale))
            ph = max(1, int(bim.height * proj_scale))
            proj = bim.resize((pw, ph), Image.NEAREST)
            # Rotate slightly (35 degrees) to show flying spin
            proj_rot = proj.rotate(35, resample=Image.NEAREST, expand=True)

            px = cx + 115 - proj_rot.width // 2
            py = cy + 70 - proj_rot.height // 2
            canvas.alpha_composite(proj_rot, (px, py))

        name = prof["name"]
        fn = prof["filename"]
        draw.text((cx + 8, cy + 8), f"#{i+1} {fn}", fill=(180, 200, 220, 255), font=font_body)
        draw.text((cx + 8, cy + cell_h - 22), f"{name}", fill=(255, 255, 255, 255), font=font_body)

    out_path = os.path.join(ARTIFACT_DIR, "maxx_boomerang_hand_test.png")
    canvas.save(out_path)
    print(f"Saved hand pose simulation artifact: {out_path}")

if __name__ == "__main__":
    simulate_hand_poses()

