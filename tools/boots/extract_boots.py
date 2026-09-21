import os
from PIL import Image, ImageDraw, ImageFont
import numpy as np

def extract_boots():
    root = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
    res_dir = os.path.join(root, "Resources", "res")
    os.makedirs(res_dir, exist_ok=True)
    
    user_uploaded_dir = "C:/Users/polyp/.gemini/antigravity/brain/72bb5645-bbbe-4c05-bdda-08bf1d5a7cdf/.user_uploaded"
    robin_src = os.path.join(user_uploaded_dir, "media_1789953377120.png")
    diana_src = os.path.join(user_uploaded_dir, "media_1789953385093.png")
    maxx_src = os.path.join(user_uploaded_dir, "media_1789953388576.png")

    TARGET_W, TARGET_H = 32, 64
    MAX_FIT_W, MAX_FIT_H = 30, 60

    # -------------------------------------------------------------
    # 1. Robin Greaves (ITEM_GREAVES, 8 boots)
    # -------------------------------------------------------------
    im_r = Image.open(robin_src).convert("RGBA")
    r_cuts = [0, 120, 242, 372, 497, 622, 743, 878, 1024]
    robin_imgs = []

    for i in range(8):
        sub = im_r.crop((r_cuts[i], 0, r_cuts[i+1], im_r.height))
        bbox = sub.getbbox()
        assert bbox is not None, f"Robin {i} bbox is None"
        crop = sub.crop(bbox)
        robin_imgs.append(crop)

    # -------------------------------------------------------------
    # 2. Diana Shoes (ITEM_SHOES, 8 shoes)
    # -------------------------------------------------------------
    im_d = Image.open(diana_src).convert("RGBA")
    arr_d = np.array(im_d)
    d_cuts = [0, 129, 249, 378, 502, 622]
    diana_imgs = []

    for i in range(5):
        sub = im_d.crop((d_cuts[i], 0, d_cuts[i+1], im_d.height))
        bbox = sub.getbbox()
        crop = sub.crop(bbox)
        diana_imgs.append(crop)

    # Diana 5 (622..756, top wing extends to 756)
    mask5 = np.zeros_like(arr_d)
    mask5[:, 622:754] = arr_d[:, 622:754]
    for x in range(754, 765):
        mask5[:160, x] = arr_d[:160, x]
    sub5 = Image.fromarray(mask5).crop((622, 0, 765, im_d.height))
    bbox5 = sub5.getbbox()
    diana_imgs.append(sub5.crop(bbox5))

    # Diana 6 (754..888, toe at 755..765, cuff at 885..888)
    mask6 = np.zeros_like(arr_d)
    for x in range(754, 765):
        mask6[160:, x] = arr_d[160:, x]
    mask6[:, 765:885] = arr_d[:, 765:885]
    for x in range(885, 895):
        mask6[:165, x] = arr_d[:165, x]
    sub6 = Image.fromarray(mask6).crop((750, 0, 895, im_d.height))
    bbox6 = sub6.getbbox()
    diana_imgs.append(sub6.crop(bbox6))

    # Diana 7 (886..1024, heel at 886..895)
    mask7 = np.zeros_like(arr_d)
    for x in range(885, 895):
        mask7[165:, x] = arr_d[165:, x]
    mask7[:, 895:1024] = arr_d[:, 895:1024]
    sub7 = Image.fromarray(mask7).crop((885, 0, 1024, im_d.height))
    bbox7 = sub7.getbbox()
    diana_imgs.append(sub7.crop(bbox7))

    # -------------------------------------------------------------
    # 3. Maxx Boots (ITEM_BOOTS, 8 boots)
    # -------------------------------------------------------------
    im_m = Image.open(maxx_src).convert("RGBA")
    arr_m = np.array(im_m)
    m_cuts = [0, 132, 254, 381]
    maxx_imgs = []

    for i in range(3):
        sub = im_m.crop((m_cuts[i], 0, m_cuts[i+1], im_m.height))
        bbox = sub.getbbox()
        crop = sub.crop(bbox)
        maxx_imgs.append(crop)

    # Maxx 3 (381..515, fur extends to 512)
    mask_m3 = np.zeros_like(arr_m)
    mask_m3[:, 381:510] = arr_m[:, 381:510]
    for x in range(510, 520):
        mask_m3[:160, x] = arr_m[:160, x]
    sub_m3 = Image.fromarray(mask_m3).crop((381, 0, 520, im_m.height))
    bbox_m3 = sub_m3.getbbox()
    maxx_imgs.append(sub_m3.crop(bbox_m3))

    # Maxx 4 (510..645, toe at 510..520, cuff at 636)
    mask_m4 = np.zeros_like(arr_m)
    for x in range(510, 520):
        mask_m4[160:, x] = arr_m[160:, x]
    mask_m4[:, 520:636] = arr_m[:, 520:636]
    for x in range(636, 645):
        mask_m4[:160, x] = arr_m[:160, x]
    sub_m4 = Image.fromarray(mask_m4).crop((505, 0, 645, im_m.height))
    bbox_m4 = sub_m4.getbbox()
    maxx_imgs.append(sub_m4.crop(bbox_m4))

    # Maxx 5 (636..762, toe at 636..645)
    mask_m5 = np.zeros_like(arr_m)
    for x in range(635, 645):
        mask_m5[160:, x] = arr_m[160:, x]
    mask_m5[:, 645:762] = arr_m[:, 645:762]
    sub_m5 = Image.fromarray(mask_m5).crop((635, 0, 762, im_m.height))
    bbox_m5 = sub_m5.getbbox()
    maxx_imgs.append(sub_m5.crop(bbox_m5))

    # Maxx 6 (762..882)
    sub_m6 = im_m.crop((762, 0, 882, im_m.height))
    bbox_m6 = sub_m6.getbbox()
    maxx_imgs.append(sub_m6.crop(bbox_m6))

    # Maxx 7 (882..1024)
    sub_m7 = im_m.crop((882, 0, 1024, im_m.height))
    bbox_m7 = sub_m7.getbbox()
    maxx_imgs.append(sub_m7.crop(bbox_m7))

    # -------------------------------------------------------------
    # 4. Fit into 32x64 transparent canvas & Save to Resources/res
    # -------------------------------------------------------------
    heroes = [
        ("robin", robin_imgs),
        ("diana", diana_imgs),
        ("maxx", maxx_imgs),
    ]

    saved_files = []
    formatted_dict = {}

    for hero_name, boot_list in heroes:
        formatted_dict[hero_name] = []
        for idx, orig in enumerate(boot_list):
            w, h = orig.size
            scale = min(MAX_FIT_W / float(w), MAX_FIT_H / float(h))
            new_w = max(1, int(round(w * scale)))
            new_h = max(1, int(round(h * scale)))
            resized = orig.resize((new_w, new_h), Image.Resampling.LANCZOS)

            canvas = Image.new("RGBA", (TARGET_W, TARGET_H), (0, 0, 0, 0))
            paste_x = (TARGET_W - new_w) // 2
            paste_y = (TARGET_H - new_h) // 2
            canvas.paste(resized, (paste_x, paste_y), resized)

            filename = f"item_boots_{hero_name}{idx}.png"
            target_path = os.path.join(res_dir, filename)
            canvas.save(target_path, optimize=True)
            saved_files.append(target_path)
            formatted_dict[hero_name].append(canvas)
            print(f"Saved: {filename} ({w}x{h} -> {new_w}x{new_h} in 32x64)")

    # -------------------------------------------------------------
    # 5. Generate Visual Contact Sheet Preview Artifact
    # -------------------------------------------------------------
    sheet_w = 8 * 72 + 140
    sheet_h = 3 * 100 + 70
    sheet = Image.new("RGBA", (sheet_w, sheet_h), (24, 26, 32, 255))
    draw = ImageDraw.Draw(sheet)

    font_path = "C:/Windows/Fonts/malgun.ttf"
    font = ImageFont.truetype(font_path, 13) if os.path.exists(font_path) else ImageFont.load_default()
    font_title = ImageFont.truetype(font_path, 15) if os.path.exists(font_path) else ImageFont.load_default()

    draw.text((20, 14), "1:2 Boot / Shoe Items Preview (32x64 Tiles for Bag Grid & Drag-and-Drop)", fill=(255, 220, 100), font=font_title)

    for row_idx, (hero_name, label, color) in enumerate([
        ("robin", "ROBIN (ITEM_GREAVES)", (140, 210, 255)),
        ("diana", "DIANA (ITEM_SHOES)", (255, 170, 210)),
        ("maxx", "MAXX (ITEM_BOOTS)", (255, 220, 140)),
    ]):
        y_base = 50 + row_idx * 100
        draw.text((20, y_base + 32), label, fill=color, font=font)

        for col_idx in range(8):
            x_box = 180 + col_idx * 68
            y_box = y_base
            # 1:2 card background box (similar to bag grid slot)
            draw.rectangle([(x_box, y_box), (x_box + 32 * 1.5, y_box + 64 * 1.5)], fill=(32, 36, 44), outline=(70, 80, 100), width=1)
            # Grid sub-tile lines (1x2 tiles)
            draw.line([(x_box, y_box + 32 * 1.5), (x_box + 32 * 1.5, y_box + 32 * 1.5)], fill=(45, 52, 65), width=1)
            
            boot_img = formatted_dict[hero_name][col_idx]
            # scaled 1.5x for crisp preview
            boot_display = boot_img.resize((int(32 * 1.5), int(64 * 1.5)), Image.Resampling.NEAREST)
            sheet.paste(boot_display, (x_box, y_box), boot_display)
            
            draw.text((x_box + 12, y_box + int(64 * 1.5) + 3), f"#{col_idx}", fill=(180, 180, 180), font=font)

    preview_path = "C:/Users/polyp/.gemini/antigravity/brain/72bb5645-bbbe-4c05-bdda-08bf1d5a7cdf/boots_preview.png"
    sheet.save(preview_path)
    print(f"\nGenerated contact sheet saved to: {preview_path}")

if __name__ == "__main__":
    extract_boots()

