# -*- coding: utf-8 -*-
"""
tools/castles/generate_wheel.py
Generates a retro 16-bit arcade pixel-art war wheel for the Mobile Castle.
Size: 80x80 px (center pivot at 40, 40).
"""
import os
import math
import numpy as np
from PIL import Image, ImageDraw

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
RES_DIRS = [
    os.path.join(ROOT, "Resources", "res"),
    os.path.join(ROOT, "proj.win32", "Debug.win32", "Resources", "res"),
    os.path.join(ROOT, "proj.win32", "Release.win32", "Resources", "res"),
]

def clamp(v, min_v=0, max_v=255):
    return max(min_v, min(max_v, int(v)))

def generate_castle_wheel():
    size = 80
    cx, cy = size / 2.0, size / 2.0
    im = Image.new("RGBA", (size, size), (0, 0, 0, 0))
    draw = ImageDraw.Draw(im)

    r_outer = 37.0
    r_rim_inner = 30.0
    r_wood_inner = 24.0
    r_hub_outer = 13.0
    r_hub_inner = 7.0

    # 1. Outer iron tire / rim (30..37)
    draw.ellipse([cx - r_outer, cy - r_outer, cx + r_outer, cy + r_outer], fill=(70, 75, 85, 255))
    # Bevel on iron tire
    draw.arc([cx - r_outer, cy - r_outer, cx + r_outer, cy + r_outer], 135, 315, fill=(160, 175, 195, 255), width=2)
    draw.arc([cx - r_outer, cy - r_outer, cx + r_outer, cy + r_outer], 315, 135, fill=(35, 38, 45, 255), width=2)

    # 2. Wood / Bronze inner band (24..30)
    draw.ellipse([cx - r_rim_inner, cy - r_rim_inner, cx + r_rim_inner, cy + r_rim_inner], fill=(130, 85, 45, 255))
    draw.ellipse([cx - r_wood_inner, cy - r_wood_inner, cx + r_wood_inner, cy + r_wood_inner], fill=(18, 16, 22, 255))

    # Wood band bevel
    draw.arc([cx - r_rim_inner, cy - r_rim_inner, cx + r_rim_inner, cy + r_rim_inner], 135, 315, fill=(190, 135, 75, 255), width=1)
    draw.arc([cx - r_wood_inner, cy - r_wood_inner, cx + r_wood_inner, cy + r_wood_inner], 315, 135, fill=(60, 35, 18, 255), width=1)

    # 3. 8 Heavy spokes from hub to rim
    spoke_cnt = 8
    for i in range(spoke_cnt):
        ang = i * (2.0 * math.pi / spoke_cnt)
        cos_a = math.cos(ang)
        sin_a = math.sin(ang)
        perp_cos = -sin_a
        perp_sin = cos_a

        # Spoke vertices
        sw = 2.8
        p1 = (cx + cos_a * r_hub_outer + perp_cos * sw, cy + sin_a * r_hub_outer + perp_sin * sw)
        p2 = (cx + cos_a * r_wood_inner + perp_cos * (sw * 1.3), cy + sin_a * r_wood_inner + perp_sin * (sw * 1.3))
        p3 = (cx + cos_a * r_wood_inner - perp_cos * (sw * 1.3), cy + sin_a * r_wood_inner - perp_sin * (sw * 1.3))
        p4 = (cx + cos_a * r_hub_outer - perp_cos * sw, cy + sin_a * r_hub_outer - perp_sin * sw)

        # Base spoke wood/iron
        draw.polygon([p1, p2, p3, p4], fill=(145, 100, 55, 255))
        # Spoke highlight edge
        draw.line([p1, p2], fill=(210, 165, 100, 255), width=1)
        # Spoke shadow edge
        draw.line([p4, p3], fill=(65, 40, 20, 255), width=1)
        # Center rib reinforcement
        draw.line([(cx + cos_a * r_hub_outer, cy + sin_a * r_hub_outer),
                   (cx + cos_a * r_wood_inner, cy + sin_a * r_wood_inner)], fill=(90, 95, 105, 255), width=1)

    # 4. Center hub (heavy bronze & steel cap)
    draw.ellipse([cx - r_hub_outer, cy - r_hub_outer, cx + r_hub_outer, cy + r_hub_outer], fill=(175, 125, 45, 255), outline=(60, 40, 15, 255))
    draw.arc([cx - r_hub_outer, cy - r_hub_outer, cx + r_hub_outer, cy + r_hub_outer], 135, 315, fill=(245, 205, 110, 255), width=2)
    draw.arc([cx - r_hub_outer, cy - r_hub_outer, cx + r_hub_outer, cy + r_hub_outer], 315, 135, fill=(90, 60, 20, 255), width=2)

    # Inner steel hub
    draw.ellipse([cx - r_hub_inner, cy - r_hub_inner, cx + r_hub_inner, cy + r_hub_inner], fill=(80, 85, 95, 255), outline=(30, 32, 38, 255))
    # Central bolt / axel pin
    r_bolt = 3.5
    draw.ellipse([cx - r_bolt, cy - r_bolt, cx + r_bolt, cy + r_bolt], fill=(220, 230, 245, 255))
    draw.point([int(cx - 1), int(cy - 1)], fill=(255, 255, 255, 255))

    # 5. 12 Outer rim rivets / studs
    rivet_cnt = 12
    r_rivet_ring = (r_outer + r_rim_inner) * 0.5
    for i in range(rivet_cnt):
        ang = i * (2.0 * math.pi / rivet_cnt)
        rx = cx + math.cos(ang) * r_rivet_ring
        ry = cy + math.sin(ang) * r_rivet_ring
        # Rivet dot
        draw.ellipse([rx - 1.8, ry - 1.8, rx + 1.8, ry + 1.8], fill=(220, 230, 245, 255))
        draw.point([int(rx - 0.5), int(ry - 0.5)], fill=(255, 255, 255, 255))
        draw.point([int(rx + 1), int(ry + 1)], fill=(40, 42, 50, 255))

    # 6. Outer border outline
    arr = np.array(im)
    alpha = arr[:, :, 3] > 20
    h, w, _ = arr.shape
    out = np.copy(arr)
    outline_color = (25, 26, 32, 255)

    for y in range(h):
        for x in range(w):
            if not alpha[y, x]:
                # Check for neighbor
                has_n = False
                for dy, dx in [(-1,0),(1,0),(0,-1),(0,1),(-1,-1),(-1,1),(1,-1),(1,1)]:
                    ny, nx = y + dy, x + dx
                    if 0 <= ny < h and 0 <= nx < w and alpha[ny, nx]:
                        has_n = True
                        break
                if has_n:
                    out[y, x] = outline_color

    wheel_img = Image.fromarray(out, "RGBA")

    # Save to all res folders
    for d in RES_DIRS:
        os.makedirs(d, exist_ok=True)
        dest = os.path.join(d, "castle_wheel.png")
        wheel_img.save(dest)
        print(f"Saved: {dest}")

    # Also save preview in brain artifact dir
    artifact_path = r"C:\Users\polyp\.gemini\antigravity\brain\72bb5645-bbbe-4c05-bdda-08bf1d5a7cdf\castle_wheel_preview.png"
    wheel_img.resize((240, 240), Image.NEAREST).save(artifact_path)
    print(f"Saved artifact preview: {artifact_path}")

if __name__ == "__main__":
    generate_castle_wheel()

