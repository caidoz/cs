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
    
    # InvenTop dividing line: y = 450 in Cocos coordinates (measured from bottom)
    invenTop = 450
    pilInvenTop = DY - invenTop # around 510 px from top
    
    # Ground baseline: lowered to right above bottom inventory! (invenTop + 4 * _2X = 458 Cocos)
    groundY = invenTop + 4 * _2X
    pilGroundY = DY - groundY # 502 px from top
    
    img = Image.new("RGBA", (DX, DY), (0, 0, 0, 255))
    draw = ImageDraw.Draw(img)

    f_title = get_font(15)
    f_sub = get_font(12)
    f_boss = get_font(14)
    f_dmg_crit = get_font(20)
    f_dmg = get_font(15)
    f_hud = get_font(13)
    f_btn = get_font(13)
    f_slot = get_font(10)

    # -------------------------------------------------------------
    # UPPER REGION: BATTLE ARENA (0 <= y < pilInvenTop)
    # -------------------------------------------------------------
    
    # 1. Sky Gradient (Continuous rightward travel sky)
    sky_top = (35, 75, 140)
    sky_horizon = (160, 205, 235)
    for y in range(pilInvenTop):
        ratio = min(1.0, max(0.0, y / float(pilGroundY + 10)))
        r = int(sky_top[0] + (sky_horizon[0] - sky_top[0]) * ratio)
        g = int(sky_top[1] + (sky_horizon[1] - sky_top[1]) * ratio)
        b = int(sky_top[2] + (sky_horizon[2] - sky_top[2]) * ratio)
        draw.line([(0, y), (DX, y)], fill=(r, g, b))

    # Radiant Golden Sun
    sun_x, sun_y = DX - 90, 85
    for r in range(65, 0, -2):
        alpha = int(35 * (1.0 - r / 65.0))
        draw.ellipse([(sun_x - r, sun_y - r), (sun_x + r, sun_y + r)], fill=(255, 245, 210, alpha))

    # 2. Distant Mountains (Layer 1)
    landscape_path = "Resources/res/lobby_landscape.png"
    if os.path.exists(landscape_path):
        ls = Image.open(landscape_path).convert("RGBA")
        ls_scale = (DX * 1.35) / ls.width
        new_w, new_h = int(ls.width * ls_scale), int(ls.height * ls_scale)
        ls = ls.resize((new_w, new_h), Image.Resampling.BILINEAR)
        img.paste(ls, (int(DX * 0.5 - new_w * 0.42), int(pilGroundY - new_h * 0.72)), ls)

    # 3. Drifting Clouds (Layer 2)
    cloud_path = "Resources/res/lobby_cloud.png"
    if os.path.exists(cloud_path):
        cl = Image.open(cloud_path).convert("RGBA")
        cl = cl.resize((int(cl.width * 0.85), int(cl.height * 0.85)), Image.Resampling.BILINEAR)
        img.paste(cl, (25, 45), cl)
        img.paste(cl, (370, 35), cl)

    # 4. Midground Foothills (Layer 3)
    foothills_path = "Resources/res/lobby_foothills.png"
    if os.path.exists(foothills_path):
        fh = Image.open(foothills_path).convert("RGBA")
        fh_scale = (DX * 1.5) / fh.width
        new_w, new_h = int(fh.width * fh_scale), int(fh.height * fh_scale)
        fh = fh.resize((new_w, new_h), Image.Resampling.BILINEAR)
        img.paste(fh, (int(DX * 0.5 - new_w * 0.5), int(pilGroundY - new_h * 0.55)), fh)

    # 5. Battlefield Road / Ground Bed right above inventory (Layer 4)
    road_path = "Resources/res/battle_bg_bottom.png"
    if os.path.exists(road_path):
        road = Image.open(road_path).convert("RGBA")
        road_zoom = DX / road.width
        rw, rh = int(road.width * road_zoom), int(road.height * road_zoom)
        road_scaled = road.resize((rw, rh), Image.Resampling.BILINEAR)
        road_y = pilGroundY - int(rh * 0.18)
        img.paste(road_scaled, (0, road_y), road_scaled)
    else:
        draw.rectangle([(0, pilGroundY - 8), (DX, pilInvenTop)], fill=(55, 48, 38))
        draw.line([(0, pilGroundY - 8), (DX, pilGroundY - 8)], fill=(85, 130, 55), width=3)

    # Road shoulder & cobblestone ground right on top of inventory
    draw.rectangle([(0, pilGroundY - 4), (DX, pilGroundY)], fill=(65, 105, 45))
    draw.line([(0, pilGroundY - 4), (DX, pilGroundY - 4)], fill=(95, 145, 65), width=2)
    for gx in range(8, DX, 20):
        draw.line([(gx, pilGroundY - 4), (gx + 3, pilGroundY - 10)], fill=(110, 160, 70), width=2)
    for rx in range(12, DX, 34):
        draw.rectangle([(rx, pilGroundY + 1), (rx + 20, pilGroundY + 6)], fill=(75, 64, 50), outline=(42, 35, 28))

    # 6. Mobile Castle on the Left (Enlarged ~0.65x, placed directly on groundY)
    castle_idx = 0
    castle_path = f"Resources/res/castle{castle_idx}.png"
    castle = Image.open(castle_path).convert("RGBA")
    cw, ch = castle.size

    # Scale: up to 0.65x (User requested significantly larger castle!)
    c_scale = 0.65
    scw, sch = int(cw * c_scale), int(ch * c_scale) # 416*0.65 = 270, 448*0.65 = 291
    castle_scaled = castle.resize((scw, sch), Image.Resampling.BILINEAR)

    wheel_path = "Resources/res/castle_wheel.png"
    wheel = Image.open(wheel_path).convert("RGBA") if os.path.exists(wheel_path) else None
    wheel_scale = 0.50 * (c_scale / 0.35) # ~0.93x
    wheel_radius = int(40 * wheel_scale) # ~37px
    wheel_diam = wheel_radius * 2 # ~74px

    castle_left = 24
    # Castle bottom is elevated above wheels
    castle_bottom_y = pilGroundY - int(wheel_radius * 1.4)
    castle_top_y = castle_bottom_y - sch

    # Castle Ground Shadow
    draw.ellipse([(castle_left - 20, pilGroundY - 6), (castle_left + scw + 20, pilGroundY + 8)], fill=(12, 10, 8, 195))

    # Trailing Wheel Dust Emitter
    for i in range(16):
        dx = castle_left + int(scw * 0.12) - i * 8 + (i % 3) * 3
        dy = pilGroundY - 6 - (i * 2)
        ds = 8 + i * 2
        alpha = max(15, 190 - i * 12)
        draw.ellipse([(dx, dy), (dx + ds, dy + ds)], fill=(145, 125, 100, alpha))

    # Castle Hull Protective Fortification Aegis Barrier (reflected from inventory shields/armor!)
    barrier_pad = 8
    draw.rectangle([
        (castle_left - barrier_pad, castle_top_y - barrier_pad),
        (castle_left + scw + barrier_pad, castle_bottom_y + barrier_pad)
    ], outline=(80, 200, 255, 160), width=3)
    draw.rectangle([
        (castle_left - barrier_pad + 2, castle_top_y - barrier_pad + 2),
        (castle_left + scw + barrier_pad - 2, castle_bottom_y + barrier_pad - 2)
    ], outline=(160, 240, 255, 100), width=1)

    # Paste Castle Hull
    img.paste(castle_scaled, (castle_left, castle_top_y), castle_scaled)

    # 3 Large Rolling Wheels on the Baseline right above inventory
    u_ratios = [0.20, 0.50, 0.80]
    if wheel:
        wheel_resized = wheel.resize((wheel_diam, wheel_diam), Image.Resampling.BILINEAR)
        for u in u_ratios:
            wx = castle_left + int(u * scw)
            wy = pilGroundY - wheel_radius
            # Heavy Reinforced Iron Chassis Struts connecting castle hull to wheel hubs
            draw.rectangle([(wx - 7, castle_bottom_y - 12), (wx + 7, wy + 6)], fill=(34, 30, 26), outline=(70, 62, 54), width=2)
            # Wheel with Rolling Tread
            img.paste(wheel_resized, (wx - wheel_radius, wy - wheel_radius), wheel_resized)
            # Bronze Axle Hub & Rivet
            draw.ellipse([(wx - 5, wy - 5), (wx + 5, wy + 5)], fill=(220, 168, 55), outline=(120, 80, 20))

    # 7. Inventory Items Reflected onto the Castle!
    # Crenel/Battlement Mounted Weapon Slots: kCastleWeaponSlots[0]
    # Inven Swords mounted along battlements with elemental auras & firing slash waves
    slots_c0 = [
        (0.22, 0.62, "Fire Blade", (255, 80, 50)),
        (0.78, 0.62, "Thunder Edge", (255, 230, 60)),
        (0.35, 0.60, "Ice Rapier", (80, 210, 255)),
        (0.65, 0.60, "Poison Dagger", (100, 255, 120)),
        (0.50, 0.38, "Divine Greatsword", (240, 220, 160)),
    ]
    for su, sv, sname, scolor in slots_c0:
        sx = castle_left + int(su * scw)
        sy = castle_top_y + int(sv * sch)
        # Mounting Pedestal Bracket
        draw.rectangle([(sx - 8, sy + 6), (sx + 8, sy + 12)], fill=(45, 40, 35), outline=(90, 80, 70))
        # Elemental Weapon Aura Glow
        draw.ellipse([(sx - 10, sy - 14), (sx + 10, sy + 6)], fill=(scolor[0], scolor[1], scolor[2], 90))
        # Mounted Blade (pointing forward/upright)
        draw.line([(sx, sy + 6), (sx + 4, sy - 16)], fill=(240, 240, 255), width=3)
        draw.line([(sx, sy + 6), (sx + 4, sy - 16)], fill=scolor, width=1)
        # Hilt guard & pommel
        draw.line([(sx - 4, sy + 3), (sx + 4, sy + 3)], fill=(210, 170, 50), width=2)
        
        # Continuous Energy Slash Waves flying from mounted inventory swords towards Boss!
        wave_x = sx + 50 + int(su * 80)
        wave_y = sy - 6
        draw.arc([(wave_x - 12, wave_y - 12), (wave_x + 12, wave_y + 12)], start=-60, end=60, fill=scolor, width=4)
        draw.line([(wave_x - 10, wave_y), (wave_x + 2, wave_y)], fill=(255, 255, 255), width=2)

    # 8. Hero (Robin) stationed at the EXACT Lobby Position on Castle!
    # kCastleHeroPos[0] = { u = 0.50, v = 0.88 }
    hero_u = 0.50
    hero_v = 0.88
    hero_x = castle_left + int(hero_u * scw)
    hero_y = castle_top_y + int(hero_v * sch)
    hero_zoom = 1.35 # scaled up proportionally

    # Hero Shadow on castle deck
    draw.ellipse([(hero_x - 16, hero_y - 4), (hero_x + 16, hero_y + 6)], fill=(15, 12, 10, 180))

    # Robin Commander Sprite (Facing RIGHT towards Boss!)
    # Cloak / Tunic
    draw.rectangle([(hero_x - 10, hero_y - 34), (hero_x + 10, hero_y)], fill=(32, 98, 48), outline=(18, 54, 26))
    # Head & Face
    draw.rectangle([(hero_x - 7, hero_y - 44), (hero_x + 7, hero_y - 34)], fill=(240, 205, 165))
    # Robin Archer Feathered Cap (Red Feather)
    draw.rectangle([(hero_x - 9, hero_y - 50), (hero_x + 10, hero_y - 44)], fill=(145, 30, 30))
    draw.line([(hero_x + 6, hero_y - 54), (hero_x + 10, hero_y - 46)], fill=(255, 220, 50), width=2)
    # Right Arm wielding Equipped Legendary Sword pointed directly at boss!
    draw.line([(hero_x + 6, hero_y - 25), (hero_x + 16, hero_y - 25)], fill=(240, 205, 165), width=3)
    draw.line([(hero_x + 16, hero_y - 25), (hero_x + 40, hero_y - 25)], fill=(255, 255, 255), width=4)
    draw.line([(hero_x + 40, hero_y - 25), (hero_x + 46, hero_y - 25)], fill=(255, 235, 140), width=2)
    # Radiant Weapon Aura
    draw.ellipse([(hero_x + 18, hero_y - 32), (hero_x + 48, hero_y - 18)], outline=(255, 215, 80, 180), width=2)

    # 9. Giant Boss Monster on the Right (Ancient Stone Golem, standing on baseline, facing LEFT)
    boss_x = DX - 120
    boss_ground_y = pilGroundY

    # Massive Boss Ground Shadow
    draw.ellipse([(boss_x - 65, boss_ground_y - 10), (boss_x + 65, boss_ground_y + 14)], fill=(12, 10, 8, 200))

    # Golem Sturdy Pillar Legs
    draw.rectangle([(boss_x - 48, boss_ground_y - 55), (boss_x - 18, boss_ground_y)], fill=(58, 55, 65), outline=(28, 25, 32), width=3)
    draw.rectangle([(boss_x + 10, boss_ground_y - 58), (boss_x + 42, boss_ground_y - 2)], fill=(52, 50, 60), outline=(25, 22, 28), width=3)

    # Golem Colossal Torso with Glowing Magma Core
    draw.rectangle([(boss_x - 58, boss_ground_y - 150), (boss_x + 48, boss_ground_y - 55)], fill=(72, 68, 80), outline=(32, 28, 38), width=3)
    draw.ellipse([(boss_x - 22, boss_ground_y - 115), (boss_x + 8, boss_ground_y - 85)], fill=(255, 70, 30), outline=(255, 200, 70), width=3)
    draw.ellipse([(boss_x - 14, boss_ground_y - 107), (boss_x, boss_ground_y - 93)], fill=(255, 245, 190))

    # Heavy Pauldrons & Arms (Left arm raised in attack stance)
    draw.rectangle([(boss_x - 74, boss_ground_y - 158), (boss_x - 44, boss_ground_y - 115)], fill=(90, 85, 100), outline=(36, 32, 42), width=3)
    draw.rectangle([(boss_x - 80, boss_ground_y - 115), (boss_x - 52, boss_ground_y - 60)], fill=(64, 60, 72), outline=(30, 26, 36), width=3)
    draw.rectangle([(boss_x + 36, boss_ground_y - 154), (boss_x + 68, boss_ground_y - 110)], fill=(85, 80, 95), outline=(36, 32, 42), width=3)
    draw.rectangle([(boss_x + 45, boss_ground_y - 110), (boss_x + 70, boss_ground_y - 65)], fill=(62, 58, 70), outline=(30, 26, 36), width=3)

    # Golem Horned Head & Menacing Eyes facing LEFT towards Mobile Castle
    draw.rectangle([(boss_x - 38, boss_ground_y - 188), (boss_x + 14, boss_ground_y - 150)], fill=(82, 78, 92), outline=(36, 32, 44), width=3)
    # Fiery Eyes
    draw.rectangle([(boss_x - 30, boss_ground_y - 174), (boss_x - 20, boss_ground_y - 166)], fill=(255, 220, 50))
    draw.rectangle([(boss_x - 10, boss_ground_y - 174), (boss_x - 2, boss_ground_y - 166)], fill=(255, 220, 50))
    # Stone Crest Horns
    draw.polygon([(boss_x - 36, boss_ground_y - 188), (boss_x - 50, boss_ground_y - 215), (boss_x - 22, boss_ground_y - 188)], fill=(170, 45, 45), outline=(60, 15, 15))
    draw.polygon([(boss_x + 10, boss_ground_y - 188), (boss_x + 22, boss_ground_y - 208), (boss_x - 4, boss_ground_y - 188)], fill=(170, 45, 45), outline=(60, 15, 15))

    # 10. Slash Impact, Sparks & Floaters on Boss
    spark_x, spark_y = boss_x - 32, boss_ground_y - 105
    draw.ellipse([(spark_x - 22, spark_y - 22), (spark_x + 22, spark_y + 22)], fill=(255, 230, 140, 240))
    draw.ellipse([(spark_x - 12, spark_y - 12), (spark_x + 12, spark_y + 12)], fill=(255, 255, 255, 255))
    draw.line([(spark_x - 35, spark_y - 25), (spark_x + 35, spark_y + 25)], fill=(255, 255, 200), width=4)

    # Damage Floaters
    draw.text((boss_x - 55, boss_ground_y - 225), "34,800!", fill=(255, 220, 40), font=f_dmg_crit)
    draw.text((boss_x + 6, boss_ground_y - 200), "12,450", fill=(255, 255, 255), font=f_dmg)

    # 11. Top-Right Boss Health Bar HUD
    bar_w, bar_h = 250, 40
    bar_x = DX - bar_w - 16
    bar_y = 16
    draw.rectangle([(bar_x, bar_y), (bar_x + bar_w, bar_y + bar_h)], fill=(20, 16, 24), outline=(100, 28, 28), width=2)
    draw.text((bar_x + 14, bar_y + 4), "[RAID BOSS] Lv.99 고대의 수호 골렘", fill=(255, 130, 130), font=f_boss)
    # HP meter slot
    meter_x, meter_y = bar_x + 12, bar_y + 24
    meter_w, meter_h = bar_w - 24, 10
    draw.rectangle([(meter_x, meter_y), (meter_x + meter_w, meter_y + meter_h)], fill=(48, 12, 12))
    fill_w = int(meter_w * 0.68)
    draw.rectangle([(meter_x, meter_y), (meter_x + fill_w, meter_y + meter_h)], fill=(220, 36, 36), outline=(255, 160, 70))
    draw.line([(meter_x, meter_y + 2), (meter_x + fill_w, meter_y + 2)], fill=(255, 130, 130))

    # Top-Left Stage & Travel Info Banner
    draw.rectangle([(16, 16), (230, 58)], fill=(20, 24, 36, 230), outline=(50, 70, 120), width=2)
    draw.text((28, 22), "STAGE 1 - MOBILE SIEGE", fill=(255, 215, 80), font=f_title)
    draw.text((28, 40), "ADVANCING RIGHTWARD >>", fill=(160, 220, 255), font=f_sub)

    # -------------------------------------------------------------
    # LOWER REGION: BAG INVENTORY (pilInvenTop <= y <= DY)
    # -------------------------------------------------------------
    draw.rectangle([(0, pilInvenTop), (DX, DY)], fill=(24, 20, 18))
    draw.line([(0, pilInvenTop), (DX, pilInvenTop)], fill=(130, 100, 60), width=3)
    draw.line([(0, pilInvenTop + 3), (DX, pilInvenTop + 3)], fill=(65, 50, 30), width=2)

    # HUD Header in Inventory (Bag & Item Reflection status)
    draw.rectangle([(16, pilInvenTop + 10), (DX - 16, pilInvenTop + 40)], fill=(34, 28, 24), outline=(68, 56, 44))
    draw.text((28, pilInvenTop + 16), "GOLD: 1,482,000", fill=(255, 215, 80), font=f_hud)
    draw.text((195, pilInvenTop + 16), "CASTLE FORTRESS: 5 WEAPONS MOUNTED", fill=(160, 230, 255), font=f_hud)
    draw.text((495, pilInvenTop + 16), "GRID: 5 x 4", fill=(180, 255, 180), font=f_hud)

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

    # Place items in grid with indicators showing they are reflected on castle!
    # Sword 1: Legendary Greatsword (reflected on Turret 4)
    s1_x = grid_start_x + 1 * (cell_size + 6)
    s1_y = grid_start_y + 0 * (cell_size + 6)
    draw.rectangle([(s1_x + 4, s1_y + 4), (s1_x + cell_size - 4, s1_y + 3 * (cell_size + 6) - 10)], fill=(36, 50, 75), outline=(90, 130, 190), width=2)
    draw.text((s1_x + 6, s1_y + 10), "GREAT", fill=(255, 215, 80), font=f_slot)
    draw.text((s1_x + 6, s1_y + 24), "SWORD", fill=(255, 255, 255), font=f_slot)
    draw.text((s1_x + 6, s1_y + 45), "[MOUNTED]", fill=(120, 255, 140), font=f_slot)

    # Sword 2: Fire Blade (reflected on Crenel 0)
    s2_x = grid_start_x + 2 * (cell_size + 6)
    s2_y = grid_start_y + 3 * (cell_size + 6)
    draw.rectangle([(s2_x + 4, s2_y + 4), (s2_x + 2 * (cell_size + 6) - 10, s2_y + cell_size - 4)], fill=(65, 35, 30), outline=(190, 90, 70), width=2)
    draw.text((s2_x + 10, s2_y + 12), "FIRE BLADE [MOUNTED]", fill=(255, 180, 140), font=f_btn)
    draw.text((s2_x + 10, s2_y + 32), "Real-time Slash Waves Firing", fill=(255, 240, 180), font=f_slot)

    # Shield Item: Guardian Shield (Fortification Aegis Barrier reflected on castle hull!)
    sh_x = grid_start_x + 0 * (cell_size + 6)
    sh_y = grid_start_y + 0 * (cell_size + 6)
    draw.rectangle([(sh_x + 4, sh_y + 4), (sh_x + cell_size - 4, sh_y + 2 * (cell_size + 6) - 8)], fill=(30, 55, 65), outline=(80, 190, 220), width=2)
    draw.text((sh_x + 6, sh_y + 10), "AEGIS", fill=(100, 220, 255), font=f_slot)
    draw.text((sh_x + 6, sh_y + 24), "SHIELD", fill=(255, 255, 255), font=f_slot)
    draw.text((sh_x + 6, sh_y + 45), "[BARRIER]", fill=(120, 255, 200), font=f_slot)

    # Bottom action buttons
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
