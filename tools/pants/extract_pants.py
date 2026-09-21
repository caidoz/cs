#!/usr/bin/env python3
"""
Extract 24 pants/kilts/skirts (Robin: ITEM_KILT 0~7, Diana: ITEM_SKIRT 0~7, Maxx: ITEM_PANTS 0~7)
from uploaded spritesheets into 64x64 transparent RGBA PNG assets for the in-game grid/inventory.
"""
import os
from PIL import Image
import numpy as np

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.abspath(os.path.join(SCRIPT_DIR, '..', '..'))
RES_DIR = os.path.join(PROJECT_ROOT, 'Resources', 'res')

IMAGES = [
    ('robin', r'C:\Users\polyp\.gemini\antigravity\brain\72bb5645-bbbe-4c05-bdda-08bf1d5a7cdf\.user_uploaded\media_1789955498555.png'),
    ('diana', r'C:\Users\polyp\.gemini\antigravity\brain\72bb5645-bbbe-4c05-bdda-08bf1d5a7cdf\.user_uploaded\media_1789955506505.png'),
    ('maxx',  r'C:\Users\polyp\.gemini\antigravity\brain\72bb5645-bbbe-4c05-bdda-08bf1d5a7cdf\.user_uploaded\media_1789955511838.png'),
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

        splits = [0]
        for i in range(1, 8):
            x_center = int(i * 128)
            sub = alpha[:, x_center - 25 : x_center + 25]
            col_sums = sub.sum(axis=0)
            min_idx = col_sums.argmin()
            actual_x = x_center - 25 + min_idx
            splits.append(actual_x)
        splits.append(im.width)

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

            cw, ch = cropped.size
            scale = min(FIT_W / cw, FIT_H / ch)
            scaled_w = int(round(cw * scale))
            scaled_h = int(round(ch * scale))

            scaled_item = cropped.resize((scaled_w, scaled_h), Image.Resampling.LANCZOS)

            out_canvas = Image.new('RGBA', (TARGET_W, TARGET_H), (0, 0, 0, 0))
            paste_x = (TARGET_W - scaled_w) // 2
            paste_y = (TARGET_H - scaled_h) // 2
            out_canvas.paste(scaled_item, (paste_x, paste_y), scaled_item)

            out_filename = os.path.join(RES_DIR, f'item_pants_{char_name}{i}.png')
            out_canvas.save(out_filename, 'PNG')

            prev_x = 4 + i * (TARGET_W + 4)
            prev_y = 4 + row_idx * (TARGET_H + 4)
            preview_im.paste(out_canvas, (prev_x, prev_y), out_canvas)

    preview_path = r'C:\Users\polyp\.gemini\antigravity\brain\72bb5645-bbbe-4c05-bdda-08bf1d5a7cdf\pants_preview.png'
    preview_im.save(preview_path, 'PNG')
    print('All 24 pants images extracted and preview saved.')

if __name__ == '__main__':
    main()

