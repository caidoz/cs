#!/usr/bin/env python3
"""
Extract Robin's 8 armors (ITEM_ARMOR 0~7) from the uploaded spritesheet.
Armors 0~3: 2x2 tiles (64x64 RGBA PNG)
Armors 4~7: 2x3 tiles (64x96 RGBA PNG)
"""
import os
from PIL import Image
import numpy as np
from collections import deque

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.abspath(os.path.join(SCRIPT_DIR, '..', '..'))
RES_DIR = os.path.join(PROJECT_ROOT, 'Resources', 'res')

IMAGE_PATH = r'C:\Users\polyp\.gemini\antigravity\brain\72bb5645-bbbe-4c05-bdda-08bf1d5a7cdf\.user_uploaded\media_1789959134574.png'

def main():
    os.makedirs(RES_DIR, exist_ok=True)

    im = Image.open(IMAGE_PATH)
    arr = np.array(im)
    alpha = arr[:, :, 3]
    H, W = alpha.shape

    binary = (alpha > 15)
    visited = np.zeros((H, W), dtype=bool)
    components = []

    for y in range(H):
        for x in range(W):
            if binary[y, x] and not visited[y, x]:
                q = deque([(y, x)])
                visited[y, x] = True
                pts = []
                while q:
                    cy, cx = q.popleft()
                    pts.append((cy, cx))
                    for dy, dx in ((-1, 0), (1, 0), (0, -1), (0, 1), (-1, -1), (-1, 1), (1, -1), (1, 1)):
                        ny, nx = cy + dy, cx + dx
                        if 0 <= ny < H and 0 <= nx < W and binary[ny, nx] and not visited[ny, nx]:
                            visited[ny, nx] = True
                            q.append((ny, nx))
                if len(pts) > 500:
                    ys = [p[0] for p in pts]
                    xs = [p[1] for p in pts]
                    components.append((min(xs), min(ys), max(xs), max(ys), pts))

    # Top row (center Y < 210), Bottom row (center Y >= 210)
    top = [c for c in components if (c[1] + c[3]) // 2 < 210]
    bot = [c for c in components if (c[1] + c[3]) // 2 >= 210]
    top.sort(key=lambda c: c[0])
    bot.sort(key=lambda c: c[0])
    all_armors = top + bot

    prev_im = Image.new('RGBA', (4 * 70 + 10, 70 + 104 + 16), (30, 30, 45, 255))

    for i, (xmin, ymin, xmax, ymax, pts) in enumerate(all_armors):
        item_arr = np.zeros((ymax - ymin + 1, xmax - xmin + 1, 4), dtype=np.uint8)
        for py, px in pts:
            item_arr[py - ymin, px - xmin] = arr[py, px]
        cropped = Image.fromarray(item_arr, 'RGBA')
        cw, ch = cropped.size

        if i < 4:
            # 2x2 -> 64x64
            tw, th = 64, 64
            fit_w, fit_h = 58, 58
        else:
            # 2x3 -> 64x96
            tw, th = 64, 96
            fit_w, fit_h = 58, 90

        scale = min(fit_w / cw, fit_h / ch)
        sw = int(round(cw * scale))
        sh = int(round(ch * scale))
        scaled = cropped.resize((sw, sh), Image.Resampling.LANCZOS)

        canvas = Image.new('RGBA', (tw, th), (0, 0, 0, 0))
        canvas.paste(scaled, ((tw - sw) // 2, (th - sh) // 2), scaled)

        out_name = os.path.join(RES_DIR, f'item_armor_robin{i}.png')
        canvas.save(out_name, 'PNG')

        col = i % 4
        px = 6 + col * 70
        py = 6 if i < 4 else (6 + 70 + 8)
        prev_im.paste(canvas, (px, py), canvas)

    prev_path = r'C:\Users\polyp\.gemini\antigravity\brain\72bb5645-bbbe-4c05-bdda-08bf1d5a7cdf\armor_preview.png'
    prev_im.save(prev_path, 'PNG')
    print('All 8 armors extracted and preview saved.')

if __name__ == '__main__':
    main()
