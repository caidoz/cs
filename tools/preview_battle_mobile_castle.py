import os
import math
from PIL import Image, ImageDraw, ImageFont

def get_font(size):
    font_paths = [
        "C:/Windows/Fonts/malgunbd.ttf",
        "C:/Windows/Fonts/malgun.ttf",
        "C:/Windows/Fonts/gulim.ttc",
        "C:/Windows/Fonts/arial.ttf"
    ]
    for p in font_paths:
        if os.path.exists(p):
            try:
                return ImageFont.truetype(p, size)
            except Exception:
                pass
    return ImageFont.load_default()

def generate_preview():
    DX = 640
    DY = 960
    _2X = 2
    
    # InvenTop dividing line: y = 460 in Cocos coordinates (measured from bottom)
    invenTop = 450
    pilInvenTop = DY - invenTop # around 510 px from top
    
    groundY = invenTop + 16 * _2X + int((DY - invenTop) * 0.22) # around 590 Cocos
    pilGroundY = DY - groundY # around 370 px from top
    
    img = Image.new("RGBA", (DX, DY), (0, 0, 0, 255))
    draw = ImageDraw.Draw(img)

    f_title = get_font(15)
    f_sub = get_font(13)
    f_boss = get_font(14)
    f_dmg_crit = get_font(18)
    f_dmg = get_font(15)
    f_hud = get_font(13)
    f_btn = get_font(13)

    # -------------------------------------------------------------
    # UPPER REGION: BATTLE ARENA (0 <= y < pilInvenTop)
    # -------------------------------------------------------------
    
    # 1. Sky Gradient (Continuous rightward travel sky)
    sky_top = (42, 85, 148)
    sky_horizon = (150, 195, 230)
    for y in range(pilInvenTop):
        ratio = min(1.0, max(0.0, y / float(pilGroundY + 50)))
        r = int(sky_top[0] + (sky_horizon[0] - sky_top[0]) * ratio)
        g = int(sky_top[1] + (sky_horizon[1] - sky_top[1]) * ratio)
        b = int(sky_top[2] + (sky_horizon[2] - sky_top[2]) * ratio)
        draw.line([(0, y), (DX, y)], fill=(r, g, b))

    # Sun radiance
    sun_x, sun_y = DX - 100, 110
    for r in range(65, 0, -2):
        alpha = int(30 * (1.0 - r / 65.0))
        draw.ellipse([(sun_x - r, sun_y - r), (sun_x + r, sun_y + r)], fill=(255, 245, 220, alpha))

    # 2. Distant Landscape / Mountains (Layer 1)
    landscape_path = "Resources/res/lobby_landscape.png"
    if os.path.exists(landscape_path):
        ls = Image.open(landscape_path).convert("RGBA")
        ls_scale = (DX * 1.35) / ls.width
        new_w, new_h = int(ls.width * ls_scale), int(ls.height * ls_scale)
        ls = ls.resize((new_w, new_h), Image.Resampling.BILINEAR)
        img.paste(ls, (int(DX * 0.5 - new_w * 0.42), int(pilGroundY - new_h * 0.70)), ls)

    # 3. Drifting Atmosphere Clouds (Layer 2)
    cloud_path = "Resources/res/lobby_cloud.png"
    if os.path.exists(cloud_path):
        cl = Image.open(cloud_path).convert("RGBA")
        cl = cl.resize((int(cl.width * 0.85), int(cl.height * 0.85)), Image.Resampling.BILINEAR)
        img.paste(cl, (30, 55), cl)
        img.paste(cl, (380, 45), cl)

    # 4. Midground Foothills (Layer 3)
    foothills_path = "Resources/res/lobby_foothills.png"
    if os.path.exists(foothills_path):
        fh = Image.open(foothills_path).convert("RGBA")
        fh_scale = (DX * 1.5) / fh.width
        new_w, new_h = int(fh.width * fh_scale), int(fh.height * fh_scale)
        fh = fh.resize((new_w, new_h), Image.Resampling.BILINEAR)
        img.paste(fh, (int(DX * 0.5 - new_w * 0.5), int(pilGroundY - new_h * 0.58)), fh)

    # 5. Battlefield Road / Ground Bed (Layer 4)
    road_path = "Resources/res/battle_bg_bottom.png"
    if os.path.exists(road_path):
        road = Image.open(road_path).convert("RGBA")
        road_zoom = DX / road.width
        rw, rh = int(road.width * road_zoom), int(road.height * road_zoom)
        road_scaled = road.resize((rw, rh), Image.Resampling.BILINEAR)
        road_y = pilGroundY - int(rh * 0.16)
        img.paste(road_scaled, (0, road_y), road_scaled)
    else:
        draw.rectangle([(0, pilGroundY), (DX, pilInvenTop)], fill=(55, 48, 38))
        draw.line([(0, pilGroundY), (DX, pilGroundY)], fill=(85, 130, 55), width=3)

    # Road shoulder & cobblestone tracks
    draw.rectangle([(0, pilGroundY - 4), (DX, pilGroundY)], fill=(65, 105, 45))
    draw.line([(0, pilGroundY - 4), (DX, pilGroundY - 4)], fill=(90, 140, 60), width=2)
    for gx in range(12, DX, 24):
        draw.line([(gx, pilGroundY - 4), (gx + 3, pilGroundY - 11)], fill=(105, 155, 68), width=2)
    for rx in range(16, DX, 38):
        draw.rectangle([(rx, pilGroundY + 10), (rx + 22, pilGroundY + 18)], fill=(75, 64, 50), outline=(42, 35, 28))
        draw.rectangle([(rx + 26, pilGroundY + 24), (rx + 44, pilGroundY + 31)], fill=(70, 58, 45), outline=(38, 32, 25))

    # 6. Mobile Castle on the Left (Castle 0: Stone Keep Fortress)
    castle_idx = 0
    castle_path = f"Resources/res/castle{castle_idx}.png"
    castle = Image.open(castle_path).convert("RGBA")
    cw, ch = castle.size

    c_scale = 0.35
    scw, sch = int(cw * c_scale), int(ch * c_scale)
    castle_scaled = castle.resize((scw, sch), Image.Resampling.BILINEAR)

    wheel_path = "Resources/res/castle_wheel.png"
    wheel = Image.open(wheel_path).convert("RGBA") if os.path.exists(wheel_path) else None
    wheel_scale = 0.50 * (c_scale / 0.35)
    wheel_radius = int(40 * wheel_scale)
    wheel_diam = wheel_radius * 2

    castle_left = 28
    castle_bottom_y = pilGroundY - int(wheel_radius * 0.70)
    castle_top_y = castle_bottom_y - sch

    # Castle ground shadow
    draw.ellipse([(castle_left - 14, pilGroundY - 3), (castle_left + scw + 14, pilGroundY + 12)], fill=(15, 12, 10, 180))

    # Wheel dust puffs (trailing behind left rear wheel as it rolls)
    for i in range(14):
        dx = castle_left + int(scw * 0.15) - i * 6 + (i % 3) * 2
        dy = pilGroundY - 5 - (i * 2)
        ds = 6 + i * 2
        alpha = max(20, 180 - i * 13)
        draw.ellipse([(dx, dy), (dx + ds, dy + ds)], fill=(140, 122, 100, alpha))

    # Paste Castle Hull
    img.paste(castle_scaled, (castle_left, castle_top_y), castle_scaled)

    # Paste Wheels (3 wheels for castle 0 at u = 0.20, 0.50, 0.80)
    u_ratios = [0.20, 0.50, 0.80]
    if wheel:
        wheel_resized = wheel.resize((wheel_diam, wheel_diam), Image.Resampling.BILINEAR)
        for u in u_ratios:
            wx = castle_left + int(u * scw)
            wy = pilGroundY - wheel_radius
            # Heavy iron axle strut bracket
            draw.rectangle([(wx - 5, castle_bottom_y - 6), (wx + 5, wy + 4)], fill=(32, 28, 24), outline=(64, 56, 48))
            # Wheel
            img.paste(wheel_resized, (wx - wheel_radius, wy - wheel_radius), wheel_resized)
            # Bronze Hub Cap with rivet
            draw.rectangle([(wx - 3, wy - 3), (wx + 3, wy + 3)], fill=(212, 160, 52), outline=(110, 74, 16))

    # 7. Defenders on Castle Deck (Aiming and facing RIGHT!)
    # Robin Commander leading at the front deck
    rx = castle_left + int(0.78 * scw)
    ry = castle_top_y + int(0.82 * sch)
    draw.rectangle([(rx - 7, ry - 24), (rx + 7, ry)], fill=(35, 95, 45))
    draw.rectangle([(rx - 5, ry - 30), (rx + 5, ry - 24)], fill=(235, 195, 155))
    draw.rectangle([(rx - 7, ry - 35), (rx + 8, ry - 30)], fill=(140, 30, 30))
    # Glowing sword blade pointed RIGHT at the boss
    draw.line([(rx + 6, ry - 18), (rx + 24, ry - 18)], fill=(245, 245, 255), width=3)
    draw.line([(rx + 24, ry - 18), (rx + 28, ry - 18)], fill=(255, 255, 180), width=2)

    # Diana Gunner on mid turret
    dx_pos = castle_left + int(0.48 * scw)
    dy_pos = castle_top_y + int(0.54 * sch)
    draw.rectangle([(dx_pos - 6, dy_pos - 22), (dx_pos + 6, dy_pos)], fill=(105, 30, 95))
    draw.rectangle([(dx_pos - 4, dy_pos - 28), (dx_pos + 4, dy_pos - 22)], fill=(235, 195, 155))
    draw.rectangle([(dx_pos - 6, dy_pos - 32), (dx_pos + 6, dy_pos - 28)], fill=(195, 160, 70))
    # Twin gun barrels pointing right with muzzle flash
    draw.line([(dx_pos + 5, dy_pos - 15), (dx_pos + 18, dy_pos - 15)], fill=(180, 180, 195), width=2)
    draw.ellipse([(dx_pos + 18, dy_pos - 19), (dx_pos + 26, dy_pos - 11)], fill=(255, 200, 50, 220))

    # 8. Large Enemy Monster on the Right (Imposing Ancient Golem Boss, facing LEFT)
    boss_x = DX - 110
    boss_ground_y = pilGroundY
    
    # Render Massive Golem Boss Sprite Silhouette
    draw.ellipse([(boss_x - 50, boss_ground_y - 8), (boss_x + 50, boss_ground_y + 14)], fill=(15, 12, 10, 190))
    
    # Golem Heavy Legs & Feet
    draw.rectangle([(boss_x - 38, boss_ground_y - 45), (boss_x - 14, boss_ground_y)], fill=(55, 52, 60), outline=(28, 25, 32), width=2)
    draw.rectangle([(boss_x + 8, boss_ground_y - 48), (boss_x + 32, boss_ground_y - 4)], fill=(50, 48, 55), outline=(25, 22, 28), width=2)
    
    # Golem Massive Stone Torso with Runes
    draw.rectangle([(boss_x - 45, boss_ground_y - 125), (boss_x + 35, boss_ground_y - 45)], fill=(68, 64, 76), outline=(32, 28, 38), width=3)
    # Glowing Arcane Core in Chest
    draw.ellipse([(boss_x - 16, boss_ground_y - 95), (boss_x + 6, boss_ground_y - 73)], fill=(255, 80, 40), outline=(255, 200, 80), width=2)
    draw.ellipse([(boss_x - 10, boss_ground_y - 89), (boss_x, boss_ground_y - 79)], fill=(255, 240, 180))

    # Golem Stone Shoulder Armor & Arms
    draw.rectangle([(boss_x - 58, boss_ground_y - 130), (boss_x - 34, boss_ground_y - 95)], fill=(85, 80, 95), outline=(35, 30, 40), width=2)
    draw.rectangle([(boss_x - 62, boss_ground_y - 95), (boss_x - 40, boss_ground_y - 50)], fill=(60, 56, 68), outline=(28, 24, 34), width=2) # Left arm reaching forward
    draw.rectangle([(boss_x + 25, boss_ground_y - 128), (boss_x + 52, boss_ground_y - 92)], fill=(80, 75, 90), outline=(35, 30, 40), width=2)
    draw.rectangle([(boss_x + 32, boss_ground_y - 92), (boss_x + 54, boss_ground_y - 55)], fill=(58, 54, 65), outline=(28, 24, 34), width=2)

    # Golem Head & Glowing Red Horns/Eyes
    draw.rectangle([(boss_x - 30, boss_ground_y - 155), (boss_x + 10, boss_ground_y - 125)], fill=(78, 74, 88), outline=(35, 30, 42), width=2)
    # Eyes looking LEFT
    draw.rectangle([(boss_x - 24, boss_ground_y - 144), (boss_x - 16, boss_ground_y - 138)], fill=(255, 220, 60))
    draw.rectangle([(boss_x - 8, boss_ground_y - 144), (boss_x, boss_ground_y - 138)], fill=(255, 220, 60))
    # Crest Horns
    draw.polygon([(boss_x - 28, boss_ground_y - 155), (boss_x - 38, boss_ground_y - 175), (boss_x - 18, boss_ground_y - 155)], fill=(160, 45, 45), outline=(60, 15, 15))
    draw.polygon([(boss_x + 8, boss_ground_y - 155), (boss_x + 18, boss_ground_y - 170), (boss_x - 2, boss_ground_y - 155)], fill=(160, 45, 45), outline=(60, 15, 15))

    # 9. Combat Projectiles & Hit Sparks
    # Robin Arrow
    draw.line([(rx + 50, ry - 22), (rx + 85, ry - 20)], fill=(196, 154, 69), width=2)
    draw.rectangle([(rx + 83, ry - 22), (rx + 88, ry - 18)], fill=(255, 255, 255))

    # Diana Gunshot Tracer
    draw.line([(dx_pos + 60, dy_pos - 15), (dx_pos + 115, dy_pos - 13)], fill=(255, 170, 51), width=3)
    draw.rectangle([(dx_pos + 112, dy_pos - 15), (dx_pos + 120, dy_pos - 11)], fill=(255, 255, 136))

    # Arcane Magic Bolt Impact on Boss
    spark_x, spark_y = boss_x - 25, boss_ground_y - 85
    draw.ellipse([(spark_x - 16, spark_y - 16), (spark_x + 16, spark_y + 16)], fill=(255, 224, 128, 230))
    draw.ellipse([(spark_x - 9, spark_y - 9), (spark_x + 9, spark_y + 9)], fill=(255, 255, 255, 255))
    draw.ellipse([(spark_x - 28, spark_y - 4), (spark_x - 12, spark_y + 12)], fill=(153, 68, 255, 200))

    # Floating Damage Texts
    draw.text((boss_x - 45, boss_ground_y - 185), "18,450!", fill=(255, 220, 40), font=f_dmg_crit)
    draw.text((boss_x + 2, boss_ground_y - 165), "6,200", fill=(255, 255, 255), font=f_dmg)

    # 10. Top-Right Boss Health Bar HUD
    bar_w, bar_h = 248, 38
    bar_x = DX - bar_w - 16
    bar_y = 16
    draw.rectangle([(bar_x, bar_y), (bar_x + bar_w, bar_y + bar_h)], fill=(20, 16, 24), outline=(92, 26, 26), width=2)
    draw.text((bar_x + 16, bar_y + 4), "[RAID BOSS] Lv.99 고대의 수호 골렘", fill=(255, 120, 120), font=f_boss)
    # HP meter slot
    meter_x, meter_y = bar_x + 12, bar_y + 22
    meter_w, meter_h = bar_w - 24, 10
    draw.rectangle([(meter_x, meter_y), (meter_x + meter_w, meter_y + meter_h)], fill=(46, 11, 11))
    fill_w = int(meter_w * 0.74)
    draw.rectangle([(meter_x, meter_y), (meter_x + fill_w, meter_y + meter_h)], fill=(212, 34, 34), outline=(255, 153, 68))
    draw.line([(meter_x, meter_y + 2), (meter_x + fill_w, meter_y + 2)], fill=(255, 120, 120))

    # Top-Left Stage & Travel Info Banner
    draw.rectangle([(16, 16), (220, 56)], fill=(20, 24, 36, 220), outline=(50, 70, 110), width=2)
    draw.text((28, 22), "STAGE 1 - MOBILE SIEGE", fill=(255, 215, 80), font=f_title)
    draw.text((28, 38), "ADVANCING FORWARD >>", fill=(160, 220, 255), font=f_sub)

    # -------------------------------------------------------------
    # LOWER REGION: BAG INVENTORY (pilInvenTop <= y <= DY)
    # -------------------------------------------------------------
    # Inventory background
    draw.rectangle([(0, pilInvenTop), (DX, DY)], fill=(24, 20, 18))
    draw.line([(0, pilInvenTop), (DX, pilInvenTop)], fill=(120, 95, 60), width=3)
    draw.line([(0, pilInvenTop + 3), (DX, pilInvenTop + 3)], fill=(60, 48, 30), width=2)

    # HUD Header in Inventory (Coins, Gems, Wave status)
    draw.rectangle([(16, pilInvenTop + 10), (DX - 16, pilInvenTop + 40)], fill=(34, 28, 24), outline=(68, 56, 44))
    draw.text((28, pilInvenTop + 16), "GOLD: 1,482,000", fill=(255, 215, 80), font=f_hud)
    draw.text((200, pilInvenTop + 16), "ROBIN CASTLE FORTRESS", fill=(200, 230, 255), font=f_hud)
    draw.text((450, pilInvenTop + 16), "GRID BAG: 5 x 4", fill=(180, 255, 180), font=f_hud)

    # 5x4 Grid cells
    cell_size = 64
    grid_start_x = (DX - 5 * (cell_size + 6)) // 2
    grid_start_y = pilInvenTop + 52

    for r in range(4):
        for c in range(5):
            cx = grid_start_x + c * (cell_size + 6)
            cy = grid_start_y + r * (cell_size + 6)
            draw.rectangle([(cx, cy), (cx + cell_size, cy + cell_size)], fill=(42, 36, 30), outline=(78, 66, 52), width=2)
            draw.line([(cx + 2, cy + 2), (cx + cell_size - 2, cy + 2)], fill=(60, 52, 42))

    # Place sample weapons/swords in the grid
    # Sword 1 (Vertical 1x3)
    s1_x = grid_start_x + 1 * (cell_size + 6)
    s1_y = grid_start_y + 0 * (cell_size + 6)
    draw.rectangle([(s1_x + 4, s1_y + 4), (s1_x + cell_size - 4, s1_y + 3 * (cell_size + 6) - 10)], fill=(36, 50, 75), outline=(90, 130, 190), width=2)
    draw.text((s1_x + 8, s1_y + 12), "LEGEND", fill=(255, 215, 80), font=f_btn)
    draw.text((s1_x + 8, s1_y + 30), "SWORD", fill=(255, 255, 255), font=f_btn)

    # Sword 2 (Horizontal 2x1)
    s2_x = grid_start_x + 2 * (cell_size + 6)
    s2_y = grid_start_y + 3 * (cell_size + 6)
    draw.rectangle([(s2_x + 4, s2_y + 4), (s2_x + 2 * (cell_size + 6) - 10, s2_y + cell_size - 4)], fill=(65, 35, 30), outline=(190, 90, 70), width=2)
    draw.text((s2_x + 10, s2_y + 20), "FIRE BLADE [AUTO]", fill=(255, 180, 140), font=f_btn)

    # Bottom action buttons (Shop / Auto / Inventory)
    btn_y = DY - 60
    draw.rectangle([(20, btn_y), (140, btn_y + 44)], fill=(50, 70, 110), outline=(100, 140, 210), width=2)
    draw.text((55, btn_y + 14), "SHOP", fill=(255, 255, 255), font=f_btn)

    draw.rectangle([(160, btn_y), (320, btn_y + 44)], fill=(40, 90, 50), outline=(80, 180, 100), width=2)
    draw.text((185, btn_y + 14), "AUTO BATTLE: ON", fill=(255, 255, 255), font=f_btn)

    draw.rectangle([(340, btn_y), (480, btn_y + 44)], fill=(90, 70, 30), outline=(180, 140, 60), width=2)
    draw.text((385, btn_y + 14), "RELOAD", fill=(255, 255, 255), font=f_btn)

    draw.rectangle([(500, btn_y), (620, btn_y + 44)], fill=(80, 35, 45), outline=(160, 70, 90), width=2)
    draw.text((535, btn_y + 14), "RETREAT", fill=(255, 255, 255), font=f_btn)

    # Save output
    out_path = "C:/Users/polyp/.gemini/antigravity/brain/72bb5645-bbbe-4c05-bdda-08bf1d5a7cdf/battle_mobile_castle_preview.png"
    img.save(out_path)
    print(f"Generated preview saved to: {out_path}")

if __name__ == "__main__":
    generate_preview()
