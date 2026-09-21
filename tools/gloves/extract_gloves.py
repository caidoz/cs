#!/usr/bin/env python3
"""
Extract 24 gloves/gauntlets/armlets (Robin: ITEM_GUNTLET 0~7, Diana: ITEM_ARMLET 0~7, Maxx: ITEM_GLOVE 0~7)
from uploaded spritesheets into 64x64 transparent RGBA PNG assets (2:2 tile ratio) for the in-game grid/inventory.
"""
import os
from PIL import Image
import numpy as np
from collections import deque

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.abspath(os.path.join(SCRIPT_DIR, '..', '..'))
RES_DIR = os.path.join(PROJECT_ROOT, 'Resources', 'res')

IMAGES = [
    ('robin', r'C:\Users\polyp\.gemini\antigravity\brain\72bb5645-bbbe-4c05-bdda-08bf1d5a7cdf\.user_uploaded\media_1789956462874.png'),
    ('diana', r'C:\Users\polyp\.gemini\antigravity\brain\72bb5645-bbbe-4c05-bdda-08bf1d5a7cdf\.user_uploaded\media_1789956465825.png'),
    ('maxx',  r'C:\Users\polyp\.gemini\antigravity\brain\72bb5645-bbbe-4c05-bdda-08bf1d5a7cdf\.user_uploaded\media_1789956472565.png'),
]

TARGET_W = 64
TARGET_H = 64
FIT_W = 58
FIT_H = 58

def main():
    os.makedirs(RES_DIR, exist_ok=True)
    preview_im = Image.new('RGBA', (TARGET_W * 8 + 9 * 4, TARGET_H * 3 + 4 * 4), (30, 30, 45, 255))

    for row_idx, (char_name, path) in enumerate(IMAGES):
        im = Image.open(path)
        arr = np.array(im)
        alpha = arr[:, :, 3]
        H, W = alpha.shape

        cropped_items = []

        if char_name in ('robin', 'maxx'):
            binary = (alpha > 15)
            visited = np.zeros((H, W), dtype=bool)
            comps = []
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
                            comps.append((min(xs), min(ys), max(xs), max(ys), pts))
            comps.sort(key=lambda c: c[0])
            for xmin, ymin, xmax, ymax, pts in comps:
                item_arr = np.zeros((ymax - ymin + 1, xmax - xmin + 1, 4), dtype=np.uint8)
                for py, px in pts:
                    item_arr[py - ymin, px - xmin] = arr[py, px]
                cropped_items.append(Image.fromarray(item_arr, 'RGBA'))
        else:
            # diana
            splits = [0]
            for i in range(1, 8):
                x_center = int(i * 128)
                sub = alpha[:, x_center - 25 : x_center + 25]
                col_sums = sub.sum(axis=0)
                min_idx = col_sums.argmin()
                actual_x = x_center - 25 + min_idx
                splits.append(actual_x)
            splits.append(W)
            for i in range(8):
                x_start = splits[i]
                x_end = splits[i + 1]
                item_crop = arr[:, x_start:x_end]
                item_alpha = item_crop[:, :, 3]
                mask = item_alpha > 15
                y_indices, x_indices = np.where(mask)
                ymin, ymax = y_indices.min(), y_indices.max()
                xmin, xmax = x_indices.min(), x_indices.max()
                abs_xmin = x_start + xmin
                abs_xmax = x_start + xmax
                cropped = im.crop((abs_xmin, ymin, abs_xmax + 1, ymax + 1))
                cropped_items.append(cropped)

        for i, cropped in enumerate(cropped_items):
            cw, ch = cropped.size
            scale = min(FIT_W / cw, FIT_H / ch)
            scaled_w = int(round(cw * scale))
            scaled_h = int(round(ch * scale))
            scaled_item = cropped.resize((scaled_w, scaled_h), Image.Resampling.LANCZOS)

            out_canvas = Image.new('RGBA', (TARGET_W, TARGET_H), (0, 0, 0, 0))
            paste_x = (TARGET_W - scaled_w) // 2
            paste_y = (TARGET_H - scaled_h) // 2
            out_canvas.paste(scaled_item, (paste_x, paste_y), scaled_item)

            out_filename = os.path.join(RES_DIR, f'item_glove_{char_name}{i}.png')
            out_canvas.save(out_filename, 'PNG')

            prev_x = 4 + i * (TARGET_W + 4)
            prev_y = 4 + row_idx * (TARGET_H + 4)
            preview_im.paste(out_canvas, (prev_x, prev_y), out_canvas)

    preview_path = r'C:\Users\polyp\.gemini\antigravity\brain\72bb5645-bbbe-4c05-bdda-08bf1d5a7cdf\gloves_preview.png'
    preview_im.save(preview_path, 'PNG')
    print('All 24 glove images extracted and preview saved.')

if __name__ == '__main__':
    main()

