# -*- coding: utf-8 -*-
"""
Preview all 35 Boomerangs in a 5x7 grid.
"""
import os
import json
from PIL import Image, ImageDraw, ImageFont

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
ARTIFACT_DIR = r"C:\Users\polyp\.gemini\antigravity\brain\72bb5645-bbbe-4c05-bdda-08bf1d5a7cdf"
PROFILES_PATH = os.path.join(ROOT, "content", "boomerangs", "profiles.json")

def create_preview():
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
    font_sub = None
    font_body = None
    for font_name in ["malgun.ttf", "gulim.ttc", "arial.ttf"]:
        fp = os.path.join(r"C:\Windows\Fonts", font_name)
        if os.path.exists(fp):
            try:
                font_title = ImageFont.truetype(fp, 18)
                font_sub = ImageFont.truetype(fp, 13)
                font_body = ImageFont.truetype(fp, 12)
                break
            except Exception:
                pass
    if font_title is None:
        font_title = ImageFont.load_default()
        font_sub = font_title
        font_body = font_title

    # Title
    draw.text((margin, 14), "MAXX ALL 35 BOOMERANGS GALLERY (w2_1 ~ w2_35)", fill=(255, 220, 100, 255), font=font_title)
    draw.text((margin, 40), "Retro 16-bit arcade pixel art styling - Authentic scaling, themes & center pivots", fill=(170, 180, 200, 255), font=font_sub)

    for i, prof in enumerate(profiles):
        r = i // cols
        c = i % cols
        cx = margin + c * cell_w
        cy = header_h + r * cell_h

        # Cell background card
        tier = prof["tier"]
        star = prof["star"] // 100
        star_str = "★" * star
        
        bg_color = (28, 32, 42, 255) if i % 2 == 0 else (34, 38, 50, 255)
        # Highlight original 8
        is_orig = i in [0, 3, 6, 9, 12, 15, 18, 21]
        border_color = (120, 200, 255, 200) if is_orig else (60, 70, 90, 150)
        if star >= 6:
            border_color = (255, 180, 60, 220)

        draw.rectangle([cx + 4, cy + 4, cx + cell_w - 4, cy + cell_h - 4], fill=bg_color, outline=border_color, width=1)

        # Load boomerang image
        img_path = os.path.join(ROOT, "Resources", "res", prof["filename"])
        if os.path.exists(img_path):
            bim = Image.open(img_path).convert("RGBA")
            # Scale slightly for preview
            scale = 1.2
            disp_w = int(bim.width * scale)
            disp_h = int(bim.height * scale)
            scaled = bim.resize((disp_w, disp_h), Image.NEAREST)

            bx = cx + (cell_w - disp_w) // 2
            by = cy + 28 + (84 - disp_h) // 2
            canvas.alpha_composite(scaled, (bx, by))

        # Text info
        tag = "[ORIG]" if is_orig else f"[T{tier}]"
        name = prof["name"]
        fn = prof["filename"]
        dim_str = f"{prof['width']}x{prof['height']}"

        # Top line: id & filename & tag
        draw.text((cx + 8, cy + 8), f"#{i+1} {fn}", fill=(180, 200, 220, 255), font=font_body)
        draw.text((cx + cell_w - 46, cy + 8), tag, fill=(100, 220, 140, 255) if is_orig else (180, 180, 180, 255), font=font_body)

        # Bottom lines: Name & Stars
        draw.text((cx + 8, cy + cell_h - 36), f"{name}", fill=(255, 255, 255, 255), font=font_body)
        draw.text((cx + 8, cy + cell_h - 20), f"{star_str} ({dim_str})", fill=(255, 210, 70, 255), font=font_body)

    out_path = os.path.join(ARTIFACT_DIR, "maxx_all_35_boomerangs_preview.png")
    canvas.save(out_path)
    print(f"Saved preview artifact: {out_path}")

if __name__ == "__main__":
    create_preview()
