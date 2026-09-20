# -*- coding: utf-8 -*-
"""
Maxx Boomerang 35 Generator (tools/boomerangs/generate_boomerangs.py)
Generates 35 boomerangs matching Robin's 35 swords (w0_1..w0_35) and Diana's 35 guns (w1_1..w1_35).
Rule: 8 originals placed at 0, 3, 6, 9, 12, 15, 18, 21 (w2_1, w2_4, w2_7, w2_10, w2_13, w2_16, w2_19, w2_22).
      2 new boomerangs placed behind each original (16 new tier boomerangs).
      11 new god-tier boomerangs at the end (24..34 -> w2_25..w2_35).
Total: 35 boomerangs (w2_1.png ~ w2_35.png).
"""
import os
import math
import json
import shutil
import numpy as np
from PIL import Image, ImageDraw, ImageFilter

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
RES_DIRS = [
    os.path.join(ROOT, "Resources", "res"),
    os.path.join(ROOT, "proj.win32", "Debug.win32", "Resources", "res"),
    os.path.join(ROOT, "proj.win32", "Release.win32", "Resources", "res"),
]
BACKUP_DIR = os.path.join(ROOT, "content", "boomerangs", "backup_8")
CONTENT_DIR = os.path.join(ROOT, "content", "boomerangs")

def clamp(val, min_v=0, max_v=255):
    return max(min_v, min(max_v, int(val)))

def lerp_color(c1, c2, t):
    t = max(0.0, min(1.0, t))
    return (
        clamp(c1[0] + (c2[0] - c1[0]) * t),
        clamp(c1[1] + (c2[1] - c1[1]) * t),
        clamp(c1[2] + (c2[2] - c1[2]) * t),
        clamp(c1[3] + (c2[3] - c1[3]) * t if len(c1) > 3 and len(c2) > 3 else 255)
    )

def apply_shading_and_outline(im, outline_color=(20, 15, 20, 240), light_dir=(-0.6, -0.8)):
    """Applies pixel-art bevel lighting, specular glint, and clean 1px outline."""
    arr = np.array(im, dtype=np.float32)
    h, w, _ = arr.shape
    alpha = arr[:, :, 3] > 20
    
    # Calculate distance transform / normal gradient
    lx, ly = light_dir
    l_len = math.sqrt(lx*lx + ly*ly)
    lx /= l_len
    ly /= l_len
    
    out = np.zeros_like(arr)
    # Copy base colors
    out[:, :, :] = arr[:, :, :]
    
    for y in range(h):
        for x in range(w):
            if not alpha[y, x]:
                # Check for 1px outline
                has_neighbor = False
                for dy, dx in [(-1,0), (1,0), (0,-1), (0,1), (-1,-1), (-1,1), (1,-1), (1,1)]:
                    ny, nx = y + dy, x + dx
                    if 0 <= ny < h and 0 <= nx < w and alpha[ny, nx]:
                        has_neighbor = True
                        break
                if has_neighbor:
                    out[y, x] = outline_color
            else:
                # Inside pixel: calculate directional lighting
                # sample neighboring alpha to see if near top-left edge or bottom-right edge
                tl = alpha[max(0, y-1), max(0, x-1)]
                br = alpha[min(h-1, y+1), min(w-1, x+1)]
                t = alpha[max(0, y-1), x]
                b = alpha[min(h-1, y+1), x]
                l = alpha[y, max(0, x-1)]
                r = alpha[y, min(w-1, x+1)]
                
                # Edge highlight on top/left
                if not (tl and t and l):
                    # Top-left edge highlight
                    out[y, x, :3] = np.clip(out[y, x, :3] * 1.35 + 25, 0, 255)
                elif not (br and b and r):
                    # Bottom-right edge shadow
                    out[y, x, :3] = np.clip(out[y, x, :3] * 0.7 - 10, 0, 255)
                else:
                    # Subtle internal shading based on position
                    pass

    return Image.fromarray(np.uint8(out), "RGBA")

def create_v_boomerang(w, h, angle_deg=105, arm_len=30, arm_w=10, elbow_r=8,
                        colors=((200, 180, 140), (150, 120, 80), (90, 60, 30)),
                        wrap_color=None, serrated=False, gem_color=None):
    """Draws a 2-armed curved V-boomerang."""
    im = Image.new("RGBA", (w, h), (0, 0, 0, 0))
    draw = ImageDraw.Draw(im)
    cx, cy = w / 2.0, h / 2.0
    
    rad = math.radians(angle_deg / 2.0)
    # Left arm direction and right arm direction
    # Pointing upwards: elbow at bottom, wings pointing up-left and up-right
    v_left = (-math.sin(rad), -math.cos(rad))
    v_right = (math.sin(rad), -math.cos(rad))
    
    # Points along left arm
    pts_left = []
    pts_right = []
    
    steps = 16
    for i in range(steps + 1):
        t = i / float(steps)
        d = t * arm_len
        # Width tapers towards tip
        cur_w = arm_w * (1.0 - 0.65 * (t ** 1.2))
        
        # Left arm center and perp
        cur_x = cx + v_left[0] * d
        cur_y = cy + v_left[1] * d
        perp = (v_left[1], -v_left[0])
        
        p_outer = (cur_x + perp[0] * cur_w, cur_y + perp[1] * cur_w)
        p_inner = (cur_x - perp[0] * cur_w, cur_y - perp[1] * cur_w)
        pts_left.append((p_outer, p_inner))
        
        # Right arm
        cur_rx = cx + v_right[0] * d
        cur_ry = cy + v_right[1] * d
        r_perp = (-v_right[1], v_right[0])
        
        pr_outer = (cur_rx + r_perp[0] * cur_w, cur_ry + r_perp[1] * cur_w)
        pr_inner = (cur_rx - r_perp[0] * cur_w, cur_ry - r_perp[1] * cur_w)
        pts_right.append((pr_outer, pr_inner))

    # Construct polygon
    poly = []
    # Left outer from tip to base
    for i in range(steps, -1, -1):
        poly.append(pts_left[i][0])
    # Elbow rounded bottom
    for ang in range(0, 181, 30):
        ar = math.radians(ang)
        poly.append((cx + math.cos(ar) * elbow_r, cy + math.sin(ar) * (elbow_r * 0.8)))
    # Right outer from base to tip
    for i in range(steps + 1):
        poly.append(pts_right[i][0])
    # Right inner from tip to center
    for i in range(steps, -1, -1):
        poly.append(pts_right[i][1])
    # Inner valley
    poly.append((cx, cy - elbow_r * 0.4))
    # Left inner from center to tip
    for i in range(steps + 1):
        poly.append(pts_left[i][1])
        
    # Fill base body
    draw.polygon(poly, fill=colors[1] + (255,))
    
    # Fill upper highlight zone
    poly_hi = [p for i, (p, _) in enumerate(pts_left)] + [(cx, cy)] + [p for i, (p, _) in enumerate(pts_right)]
    # Inner blade highlight
    inner_blade = []
    for i in range(0, steps + 1, 2):
        inner_blade.append(pts_left[i][0])
    draw.line(inner_blade, fill=colors[0] + (255,), width=2)
    inner_blade_r = []
    for i in range(0, steps + 1, 2):
        inner_blade_r.append(pts_right[i][0])
    draw.line(inner_blade_r, fill=colors[0] + (255,), width=2)
    
    # Central elbow shading
    draw.ellipse([cx - elbow_r*0.6, cy - elbow_r*0.4, cx + elbow_r*0.6, cy + elbow_r*0.6], fill=colors[2] + (255,))

    # Leather wrap or bands if requested
    if wrap_color:
        for offset in [-6, -3, 0, 3, 6]:
            draw.line([(cx - 7, cy + offset), (cx + 7, cy + offset - 2)], fill=wrap_color + (255,), width=2)
            
    # Central gem / emblem if requested
    if gem_color:
        gr = 4
        draw.ellipse([cx - gr, cy - gr, cx + gr, cy + gr], fill=gem_color + (255,), outline=(255, 255, 255, 220))

    # Serrated teeth on outer edges
    if serrated:
        for i in range(3, steps, 3):
            p1 = pts_left[i][0]
            draw.polygon([p1, (p1[0] - 3, p1[1] - 2), (p1[0] + 1, p1[1] + 2)], fill=(240, 240, 240, 255))
            pr1 = pts_right[i][0]
            draw.polygon([pr1, (pr1[0] + 3, pr1[1] - 2), (pr1[0] - 1, pr1[1] + 2)], fill=(240, 240, 240, 255))

    return apply_shading_and_outline(im)

def create_crescent_blade(w, h, outer_r=36, inner_r=22, thickness=12,
                         colors=((220, 230, 240), (140, 160, 180), (60, 80, 110)),
                         gem_color=None, wing_feathers=False, scythe_hooks=False):
    """Draws a curved crescent / double-scythe flight blade."""
    im = Image.new("RGBA", (w, h), (0, 0, 0, 0))
    draw = ImageDraw.Draw(im)
    cx, cy = w / 2.0, h / 2.0
    
    # Outer arc and inner arc
    poly = []
    # Outer arc: from -130 deg to +130 deg
    steps = 28
    for i in range(steps + 1):
        ang = math.radians(-130 + (260 * i / steps))
        rx = outer_r * math.cos(ang)
        ry = (outer_r * 0.72) * math.sin(ang)
        poly.append((cx + rx, cy + ry))
        
    # Tips connect to inner arc
    for i in range(steps, -1, -1):
        ang = math.radians(-125 + (250 * i / steps))
        rx = inner_r * math.cos(ang)
        ry = (inner_r * 0.65) * math.sin(ang)
        # Offset inner center slightly down
        poly.append((cx + rx, cy + ry + 4))

    draw.polygon(poly, fill=colors[1] + (255,))
    
    # Blade highlight along outer rim
    outer_edge = []
    for i in range(steps + 1):
        ang = math.radians(-130 + (260 * i / steps))
        rx = outer_r * math.cos(ang)
        ry = (outer_r * 0.72) * math.sin(ang)
        outer_edge.append((cx + rx, cy + ry))
    draw.line(outer_edge, fill=colors[0] + (255,), width=2)
    
    # Inner fuller / groove
    groove = []
    for i in range(4, steps - 3):
        ang = math.radians(-125 + (250 * i / steps))
        rx = (inner_r + outer_r) * 0.5 * math.cos(ang)
        ry = ((inner_r + outer_r) * 0.35) * math.sin(ang) + 2
        groove.append((cx + rx, cy + ry))
    draw.line(groove, fill=colors[2] + (255,), width=2)
    
    # Scythe hooks at tips
    if scythe_hooks:
        tip_l = outer_edge[0]
        tip_r = outer_edge[-1]
        draw.polygon([tip_l, (tip_l[0] - 6, tip_l[1] + 8), (tip_l[0] + 3, tip_l[1] + 4)], fill=colors[0] + (255,))
        draw.polygon([tip_r, (tip_r[0] + 6, tip_r[1] + 8), (tip_r[0] - 3, tip_r[1] + 4)], fill=colors[0] + (255,))

    # Feathers if winged
    if wing_feathers:
        for i in range(2, steps, 4):
            p = outer_edge[i]
            ang = math.radians(-130 + (260 * i / steps))
            fx = p[0] + math.cos(ang) * 5
            fy = p[1] + math.sin(ang) * 5
            draw.polygon([p, (fx, fy), (p[0] + 2, p[1] + 3)], fill=(255, 230, 140, 255))

    # Central core
    cr = 5
    draw.ellipse([cx - cr, cy - cr + 2, cx + cr, cy + cr + 2], fill=colors[2] + (255,))
    if gem_color:
        draw.ellipse([cx - cr*0.7, cy - cr*0.7 + 2, cx + cr*0.7, cy + cr*0.7 + 2], fill=gem_color + (255,), outline=(255, 255, 255, 200))

    return apply_shading_and_outline(im)

def create_tri_blade(w, h, arm_len=30, arm_w=11,
                     colors=((240, 240, 250), (160, 170, 190), (70, 80, 100)),
                     gem_color=(255, 50, 50), curved=True):
    """Draws a 3-bladed aerodynamic tri-edge / throwing star."""
    im = Image.new("RGBA", (w, h), (0, 0, 0, 0))
    draw = ImageDraw.Draw(im)
    cx, cy = w / 2.0, h / 2.0
    
    # 3 arms at -90 deg (up), 30 deg (down-right), 150 deg (down-left)
    angles = [-90, 30, 150]
    
    for ang_deg in angles:
        base_rad = math.radians(ang_deg)
        # Tip coordinate
        tip_x = cx + math.cos(base_rad) * arm_len
        tip_y = cy + math.sin(base_rad) * arm_len
        
        # Perpendicular for width
        perp_rad = base_rad + math.pi / 2.0
        # Blade curvature sweep
        sweep_rad = base_rad + (0.35 if curved else 0.0)
        sw_tip_x = cx + math.cos(sweep_rad) * arm_len
        sw_tip_y = cy + math.sin(sweep_rad) * arm_len
        
        p1 = (cx + math.cos(perp_rad) * (arm_w * 0.7), cy + math.sin(perp_rad) * (arm_w * 0.7))
        p2 = (sw_tip_x, sw_tip_y)
        p3 = (cx - math.cos(perp_rad) * (arm_w * 0.4), cy - math.sin(perp_rad) * (arm_w * 0.4))
        
        draw.polygon([(cx, cy), p1, p2, p3], fill=colors[1] + (255,))
        # Cutting edge highlight
        draw.polygon([(cx, cy), p1, p2], fill=colors[0] + (255,))
        # Shaded bevel
        draw.polygon([(cx, cy), p2, p3], fill=colors[2] + (255,))
        
        # Blade fuller slot
        mid_x = (cx + sw_tip_x) * 0.5
        mid_y = (cy + sw_tip_y) * 0.5
        draw.line([(cx + math.cos(base_rad)*6, cy + math.sin(base_rad)*6), (mid_x, mid_y)], fill=(30, 30, 40, 255), width=2)

    # Center hub
    hr = arm_w * 0.75
    draw.ellipse([cx - hr, cy - hr, cx + hr, cy + hr], fill=colors[2] + (255,), outline=colors[0] + (255,))
    if gem_color:
        gr = hr * 0.6
        draw.ellipse([cx - gr, cy - gr, cx + gr, cy + gr], fill=gem_color + (255,), outline=(255, 255, 255, 220))

    return apply_shading_and_outline(im)

def create_quad_cross(w, h, arm_len=30, arm_w=9,
                      colors=((255, 220, 150), (190, 150, 80), (100, 70, 30)),
                      gem_color=(100, 220, 255), swept=True):
    """Draws a 4-bladed aerodynamic cross blade."""
    im = Image.new("RGBA", (w, h), (0, 0, 0, 0))
    draw = ImageDraw.Draw(im)
    cx, cy = w / 2.0, h / 2.0
    
    angles = [0, 90, 180, 270]
    for ang_deg in angles:
        base_rad = math.radians(ang_deg)
        sweep_rad = base_rad + (0.28 if swept else 0.0)
        
        tip_x = cx + math.cos(sweep_rad) * arm_len
        tip_y = cy + math.sin(sweep_rad) * arm_len
        
        perp_rad = base_rad + math.pi / 2.0
        p1 = (cx + math.cos(perp_rad) * arm_w, cy + math.sin(perp_rad) * arm_w)
        p2 = (tip_x, tip_y)
        p3 = (cx - math.cos(perp_rad) * (arm_w * 0.5), cy - math.sin(perp_rad) * (arm_w * 0.5))
        
        draw.polygon([(cx, cy), p1, p2, p3], fill=colors[1] + (255,))
        draw.polygon([(cx, cy), p1, p2], fill=colors[0] + (255,))
        draw.polygon([(cx, cy), p2, p3], fill=colors[2] + (255,))
        
    # Central ring
    cr = 7
    draw.ellipse([cx - cr, cy - cr, cx + cr, cy + cr], fill=colors[2] + (255,), outline=colors[0] + (255,))
    if gem_color:
        gr = 4
        draw.ellipse([cx - gr, cy - gr, cx + gr, cy + gr], fill=gem_color + (255,), outline=(255, 255, 255, 240))

    return apply_shading_and_outline(im)

def create_chakram_ring(w, h, outer_r=32, inner_r=20, blade_cnt=6,
                        colors=((200, 240, 255), (100, 160, 220), (40, 80, 140)),
                        gem_color=(255, 200, 50)):
    """Draws a circular aerodynamic chakram ring with outer cutting blades."""
    im = Image.new("RGBA", (w, h), (0, 0, 0, 0))
    draw = ImageDraw.Draw(im)
    cx, cy = w / 2.0, h / 2.0
    
    # Outer blades
    for i in range(blade_cnt):
        ang = i * (2 * math.pi / blade_cnt)
        b_tip_x = cx + math.cos(ang) * (outer_r + 8)
        b_tip_y = cy + math.sin(ang) * (outer_r * 0.85 + 7)
        
        ang_left = ang - 0.35
        p1 = (cx + math.cos(ang_left) * outer_r, cy + math.sin(ang_left) * (outer_r * 0.85))
        ang_right = ang + 0.2
        p2 = (cx + math.cos(ang_right) * outer_r, cy + math.sin(ang_right) * (outer_r * 0.85))
        
        draw.polygon([(cx, cy), p1, (b_tip_x, b_tip_y), p2], fill=colors[0] + (255,))
        
    # Outer ring
    draw.ellipse([cx - outer_r, cy - outer_r*0.85, cx + outer_r, cy + outer_r*0.85], fill=colors[1] + (255,))
    # Inner hole
    draw.ellipse([cx - inner_r, cy - inner_r*0.85, cx + inner_r, cy + inner_r*0.85], fill=(0, 0, 0, 0))
    
    # Ring highlight and bevel
    draw.arc([cx - outer_r, cy - outer_r*0.85, cx + outer_r, cy + outer_r*0.85], 180, 360, fill=colors[0] + (255,), width=2)
    draw.arc([cx - inner_r, cy - inner_r*0.85, cx + inner_r, cy + inner_r*0.85], 0, 180, fill=colors[2] + (255,), width=2)
    
    # Crossbars / spokes
    for i in range(3):
        ang = i * (math.pi / 1.5)
        p1 = (cx + math.cos(ang) * inner_r, cy + math.sin(ang) * inner_r * 0.85)
        p2 = (cx - math.cos(ang) * inner_r, cy - math.sin(ang) * inner_r * 0.85)
        draw.line([p1, p2], fill=colors[2] + (255,), width=3)
        
    if gem_color:
        gr = 4
        draw.ellipse([cx - gr, cy - gr, cx + gr, cy + gr], fill=gem_color + (255,), outline=(255, 255, 255, 220))

    return apply_shading_and_outline(im)

def create_divine_orbital(w, h, outer_r=44, colors=((255, 245, 220), (220, 180, 80), (120, 80, 30)),
                          energy_color=(120, 230, 255), halo_type=0):
    """Draws a magnificent divine/cosmic god-tier orbital weapon."""
    im = Image.new("RGBA", (w, h), (0, 0, 0, 0))
    draw = ImageDraw.Draw(im)
    cx, cy = w / 2.0, h / 2.0
    
    # Outer celestial wings / arcs
    wing_cnt = 6 if halo_type == 1 else 4
    for i in range(wing_cnt):
        ang = i * (2 * math.pi / wing_cnt) + (math.pi / wing_cnt if halo_type == 1 else 0)
        tip_x = cx + math.cos(ang) * outer_r
        tip_y = cy + math.sin(ang) * (outer_r * 0.78)
        
        # Curved wing polygon
        tang1 = ang - 0.4
        tang2 = ang + 0.25
        p1 = (cx + math.cos(tang1) * (outer_r * 0.55), cy + math.sin(tang1) * (outer_r * 0.42))
        p2 = (tip_x, tip_y)
        p3 = (cx + math.cos(tang2) * (outer_r * 0.65), cy + math.sin(tang2) * (outer_r * 0.50))
        
        draw.polygon([(cx, cy), p1, p2, p3], fill=colors[1] + (255,))
        draw.polygon([(cx, cy), p1, p2], fill=colors[0] + (255,))
        draw.line([p1, p2], fill=(255, 255, 255, 255), width=2)
        
        # Energy rune feathers
        if halo_type >= 1:
            draw.line([(cx, cy), (tip_x * 0.9 + cx * 0.1, tip_y * 0.9 + cy * 0.1)], fill=energy_color + (200,), width=2)

    # Double orbital rings
    r1 = outer_r * 0.62
    r2 = outer_r * 0.42
    draw.arc([cx - r1, cy - r1*0.75, cx + r1, cy + r1*0.75], 0, 360, fill=colors[0] + (230,), width=2)
    draw.arc([cx - r2, cy - r2*0.75, cx + r2, cy + r2*0.75], 0, 360, fill=energy_color + (240,), width=2)

    # Central Divine Core / Singularity
    cr = 8
    draw.ellipse([cx - cr, cy - cr, cx + cr, cy + cr], fill=energy_color + (255,))
    draw.ellipse([cx - cr*0.6, cy - cr*0.6, cx + cr*0.6, cy + cr*0.6], fill=(255, 255, 255, 255))
    
    # 4 Orbiting satellite crystals
    for i in range(4):
        s_ang = i * (math.pi / 2.0) + 0.4
        sx = cx + math.cos(s_ang) * (r1 * 0.95)
        sy = cy + math.sin(s_ang) * (r1 * 0.72)
        draw.polygon([(sx, sy - 3), (sx + 3, sy), (sx, sy + 3), (sx - 3, sy)], fill=colors[0] + (255,), outline=(255, 255, 255, 240))

    return apply_shading_and_outline(im)

def generate_all_35():
    """Generates all 35 boomerangs and copies them to target directories."""
    print("Generating 35 Boomerangs...")
    
    # List of specifications for all 35 boomerangs
    specs = [
        # 0: w2_1 (Orig 1) - 사냥용 부메랑 (86x70)
        {"id": 0, "fn": "w2_1.png", "orig": 1, "name": "사냥용 부메랑", "tier": 1, "star": 100, "w": 86, "h": 70},
        # 1: w2_2 (New 1) - 본 부메랑 (86x70)
        {"id": 1, "fn": "w2_2.png", "orig": None, "name": "본 부메랑", "tier": 1, "star": 100, "w": 86, "h": 70,
         "gen": lambda w, h: create_v_boomerang(w, h, angle_deg=100, arm_len=30, arm_w=9, elbow_r=7,
                                                colors=((245, 240, 220), (195, 180, 150), (120, 100, 70)),
                                                wrap_color=(90, 50, 20), serrated=True)},
        # 2: w2_3 (New 2) - 플린트 크레센트 (86x70)
        {"id": 2, "fn": "w2_3.png", "orig": None, "name": "플린트 크레센트", "tier": 1, "star": 100, "w": 86, "h": 70,
         "gen": lambda w, h: create_crescent_blade(w, h, outer_r=33, inner_r=19, thickness=11,
                                                   colors=((220, 230, 240), (110, 120, 135), (45, 50, 60)),
                                                   scythe_hooks=True)},
        # 3: w2_4 (Orig 2) - 슬라이서 (86x70)
        {"id": 3, "fn": "w2_4.png", "orig": 2, "name": "슬라이서", "tier": 2, "star": 100, "w": 86, "h": 70},
        # 4: w2_5 (New 3) - 윈드 커터 (86x70)
        {"id": 4, "fn": "w2_5.png", "orig": None, "name": "윈드 커터", "tier": 2, "star": 100, "w": 86, "h": 70,
         "gen": lambda w, h: create_v_boomerang(w, h, angle_deg=115, arm_len=32, arm_w=10, elbow_r=8,
                                                colors=((180, 255, 230), (70, 190, 150), (20, 90, 70)),
                                                gem_color=(255, 255, 255))},
        # 5: w2_6 (New 4) - 팔콘 윙 (86x70)
        {"id": 5, "fn": "w2_6.png", "orig": None, "name": "팔콘 윙", "tier": 2, "star": 200, "w": 86, "h": 70,
         "gen": lambda w, h: create_crescent_blade(w, h, outer_r=35, inner_r=20, thickness=12,
                                                   colors=((255, 220, 150), (180, 130, 60), (90, 60, 20)),
                                                   wing_feathers=True, gem_color=(100, 220, 255))},
        # 6: w2_7 (Orig 3) - 강철 부메랑 (86x70)
        {"id": 6, "fn": "w2_7.png", "orig": 3, "name": "강철 부메랑", "tier": 3, "star": 200, "w": 86, "h": 70},
        # 7: w2_8 (New 5) - 크로스 블레이드 (86x70)
        {"id": 7, "fn": "w2_8.png", "orig": None, "name": "크로스 블레이드", "tier": 3, "star": 200, "w": 86, "h": 70,
         "gen": lambda w, h: create_quad_cross(w, h, arm_len=30, arm_w=9,
                                               colors=((230, 235, 245), (140, 150, 170), (60, 70, 90)),
                                               gem_color=(255, 180, 40))},
        # 8: w2_9 (New 6) - 바브드 팽 (86x70)
        {"id": 8, "fn": "w2_9.png", "orig": None, "name": "바브드 팽", "tier": 3, "star": 200, "w": 86, "h": 70,
         "gen": lambda w, h: create_v_boomerang(w, h, angle_deg=95, arm_len=33, arm_w=11, elbow_r=9,
                                                colors=((255, 180, 160), (190, 70, 60), (100, 30, 30)),
                                                serrated=True, gem_color=(255, 220, 100))},
        # 9: w2_10 (Orig 4) - 트라이 엣지 (86x70)
        {"id": 9, "fn": "w2_10.png", "orig": 4, "name": "트라이 엣지", "tier": 4, "star": 200, "w": 86, "h": 70},
        # 10: w2_11 (New 7) - 쉐도우 차크람 (86x70)
        {"id": 10, "fn": "w2_11.png", "orig": None, "name": "쉐도우 차크람", "tier": 4, "star": 300, "w": 86, "h": 70,
         "gen": lambda w, h: create_chakram_ring(w, h, outer_r=32, inner_r=19, blade_cnt=6,
                                                 colors=((220, 190, 255), (120, 80, 180), (50, 20, 80)),
                                                 gem_color=(255, 80, 180))},
        # 11: w2_12 (New 8) - 플레임 윙 (86x70)
        {"id": 11, "fn": "w2_12.png", "orig": None, "name": "플레임 윙", "tier": 4, "star": 300, "w": 86, "h": 70,
         "gen": lambda w, h: create_crescent_blade(w, h, outer_r=37, inner_r=21, thickness=13,
                                                   colors=((255, 240, 140), (240, 110, 30), (140, 30, 10)),
                                                   scythe_hooks=True, gem_color=(255, 255, 200))},
        # 12: w2_13 (Orig 5) - 라이트닝 엣지 (86x70)
        {"id": 12, "fn": "w2_13.png", "orig": 5, "name": "라이트닝 엣지", "tier": 5, "star": 300, "w": 86, "h": 70},
        # 13: w2_14 (New 9) - 프로스트 팽 (86x70)
        {"id": 13, "fn": "w2_14.png", "orig": None, "name": "프로스트 팽", "tier": 5, "star": 300, "w": 86, "h": 70,
         "gen": lambda w, h: create_tri_blade(w, h, arm_len=32, arm_w=12,
                                              colors=((230, 255, 255), (100, 210, 240), (30, 100, 150)),
                                              gem_color=(255, 255, 255), curved=True)},
        # 14: w2_15 (New 10) - 베놈 스파이크 (86x70)
        {"id": 14, "fn": "w2_15.png", "orig": None, "name": "베놈 스파이크", "tier": 5, "star": 300, "w": 86, "h": 70,
         "gen": lambda w, h: create_v_boomerang(w, h, angle_deg=90, arm_len=35, arm_w=12, elbow_r=9,
                                                colors=((220, 255, 140), (120, 200, 40), (40, 90, 20)),
                                                serrated=True, gem_color=(180, 255, 50))},
        # 15: w2_16 (Orig 6) - 소울 체이서 (86x70)
        {"id": 15, "fn": "w2_16.png", "orig": 6, "name": "소울 체이서", "tier": 6, "star": 400, "w": 86, "h": 70},
        # 16: w2_17 (New 11) - 블러드 리퍼 (86x70)
        {"id": 16, "fn": "w2_17.png", "orig": None, "name": "블러드 리퍼", "tier": 6, "star": 400, "w": 86, "h": 70,
         "gen": lambda w, h: create_crescent_blade(w, h, outer_r=38, inner_r=21, thickness=13,
                                                   colors=((255, 170, 170), (190, 40, 50), (90, 15, 20)),
                                                   scythe_hooks=True, gem_color=(255, 220, 120))},
        # 17: w2_18 (New 12) - 미스틱 룬 (86x70)
        {"id": 17, "fn": "w2_18.png", "orig": None, "name": "미스틱 룬", "tier": 6, "star": 400, "w": 86, "h": 70,
         "gen": lambda w, h: create_chakram_ring(w, h, outer_r=34, inner_r=20, blade_cnt=8,
                                                 colors=((240, 220, 255), (160, 90, 230), (70, 20, 120)),
                                                 gem_color=(120, 240, 255))},
        # 18: w2_19 (Orig 7) - 그리폰 윙 (86x70)
        {"id": 18, "fn": "w2_19.png", "orig": 7, "name": "그리폰 윙", "tier": 7, "star": 400, "w": 86, "h": 70},
        # 19: w2_20 (New 13) - 피닉스 테일 (86x70)
        {"id": 19, "fn": "w2_20.png", "orig": None, "name": "피닉스 테일", "tier": 7, "star": 400, "w": 86, "h": 70,
         "gen": lambda w, h: create_crescent_blade(w, h, outer_r=39, inner_r=22, thickness=14,
                                                   colors=((255, 255, 180), (255, 140, 30), (160, 40, 10)),
                                                   wing_feathers=True, gem_color=(255, 255, 255))},
        # 20: w2_21 (New 14) - 드래곤 크레스트 (86x70)
        {"id": 20, "fn": "w2_21.png", "orig": None, "name": "드래곤 크레스트", "tier": 7, "star": 500, "w": 86, "h": 70,
         "gen": lambda w, h: create_v_boomerang(w, h, angle_deg=105, arm_len=36, arm_w=13, elbow_r=10,
                                                colors=((255, 230, 150), (180, 130, 40), (80, 50, 15)),
                                                serrated=True, gem_color=(100, 255, 180))},
        # 21: w2_22 (Orig 8) - 로커스트 헌트 (86x70)
        {"id": 21, "fn": "w2_22.png", "orig": 8, "name": "로커스트 헌트", "tier": 8, "star": 500, "w": 86, "h": 70},
        # 22: w2_23 (New 15) - 카오스 스파이럴 (88x70)
        {"id": 22, "fn": "w2_23.png", "orig": None, "name": "카오스 스파이럴", "tier": 8, "star": 500, "w": 88, "h": 70,
         "gen": lambda w, h: create_quad_cross(w, h, arm_len=34, arm_w=11,
                                               colors=((255, 180, 240), (190, 50, 160), (90, 15, 80)),
                                               gem_color=(255, 240, 100), swept=True)},
        # 23: w2_24 (New 16) - 타이탄 브레이커 (90x70)
        {"id": 23, "fn": "w2_24.png", "orig": None, "name": "타이탄 브레이커", "tier": 8, "star": 500, "w": 90, "h": 70,
         "gen": lambda w, h: create_v_boomerang(w, h, angle_deg=110, arm_len=37, arm_w=14, elbow_r=11,
                                                colors=((230, 225, 210), (150, 140, 125), (75, 70, 60)),
                                                wrap_color=(180, 120, 40), serrated=True, gem_color=(255, 140, 30))},
        # 24: w2_25 (New 17) - 발키리 크레센트 (90x70)
        {"id": 24, "fn": "w2_25.png", "orig": None, "name": "발키리 크레센트", "tier": 9, "star": 600, "w": 90, "h": 70,
         "gen": lambda w, h: create_crescent_blade(w, h, outer_r=41, inner_r=23, thickness=14,
                                                   colors=((255, 255, 255), (200, 220, 245), (100, 130, 175)),
                                                   wing_feathers=True, gem_color=(100, 210, 255))},
        # 25: w2_26 (New 18) - 보이드 소용돌이 (92x72)
        {"id": 25, "fn": "w2_26.png", "orig": None, "name": "보이드 소용돌이", "tier": 9, "star": 600, "w": 92, "h": 72,
         "gen": lambda w, h: create_chakram_ring(w, h, outer_r=36, inner_r=21, blade_cnt=8,
                                                 colors=((220, 160, 255), (110, 40, 190), (40, 10, 80)),
                                                 gem_color=(255, 50, 160))},
        # 26: w2_27 (New 19) - 솔라 플레어 (92x74)
        {"id": 26, "fn": "w2_27.png", "orig": None, "name": "솔라 플레어", "tier": 9, "star": 600, "w": 92, "h": 74,
         "gen": lambda w, h: create_divine_orbital(w, h, outer_r=42,
                                                   colors=((255, 255, 210), (255, 170, 40), (160, 60, 10)),
                                                   energy_color=(255, 230, 100), halo_type=0)},
        # 27: w2_28 (New 20) - 루나 이클립스 (94x72)
        {"id": 27, "fn": "w2_28.png", "orig": None, "name": "루나 이클립스", "tier": 9, "star": 600, "w": 94, "h": 72,
         "gen": lambda w, h: create_crescent_blade(w, h, outer_r=43, inner_r=24, thickness=15,
                                                   colors=((240, 245, 255), (130, 150, 190), (35, 45, 75)),
                                                   scythe_hooks=True, gem_color=(200, 230, 255))},
        # 28: w2_29 (New 21) - 템페스트 스톰 (94x76)
        {"id": 28, "fn": "w2_29.png", "orig": None, "name": "템페스트 스톰", "tier": 9, "star": 600, "w": 94, "h": 76,
         "gen": lambda w, h: create_tri_blade(w, h, arm_len=36, arm_w=14,
                                              colors=((210, 255, 255), (80, 190, 230), (20, 90, 140)),
                                              gem_color=(255, 240, 80), curved=True)},
        # 29: w2_30 (New 22) - 아비수스 리퍼 (96x76)
        {"id": 29, "fn": "w2_30.png", "orig": None, "name": "아비수스 리퍼", "tier": 9, "star": 600, "w": 96, "h": 76,
         "gen": lambda w, h: create_crescent_blade(w, h, outer_r=44, inner_r=24, thickness=15,
                                                   colors=((255, 140, 160), (170, 20, 40), (70, 5, 15)),
                                                   scythe_hooks=True, gem_color=(255, 70, 20))},
        # 30: w2_31 (New 23) - 세라핌 윙 (98x78)
        {"id": 30, "fn": "w2_31.png", "orig": None, "name": "세라핌 윙", "tier": 9, "star": 600, "w": 98, "h": 78,
         "gen": lambda w, h: create_divine_orbital(w, h, outer_r=45,
                                                   colors=((255, 250, 230), (235, 195, 85), (140, 95, 30)),
                                                   energy_color=(120, 220, 255), halo_type=1)},
        # 31: w2_32 (New 24) - 제네시스 크로스 (98x80)
        {"id": 31, "fn": "w2_32.png", "orig": None, "name": "제네시스 크로스", "tier": 9, "star": 600, "w": 98, "h": 80,
         "gen": lambda w, h: create_quad_cross(w, h, arm_len=37, arm_w=13,
                                               colors=((255, 255, 255), (180, 210, 255), (80, 110, 180)),
                                               gem_color=(255, 160, 230), swept=True)},
        # 32: w2_33 (New 25) - 아마게돈 엣지 (100x80)
        {"id": 32, "fn": "w2_33.png", "orig": None, "name": "아마게돈 엣지", "tier": 9, "star": 600, "w": 100, "h": 80,
         "gen": lambda w, h: create_v_boomerang(w, h, angle_deg=105, arm_len=42, arm_w=15, elbow_r=12,
                                                colors=((255, 200, 100), (200, 60, 20), (80, 15, 10)),
                                                serrated=True, gem_color=(255, 255, 100))},
        # 33: w2_34 (New 26) - 크로노스 스피어 (102x82)
        {"id": 33, "fn": "w2_34.png", "orig": None, "name": "크로노스 스피어", "tier": 9, "star": 600, "w": 102, "h": 82,
         "gen": lambda w, h: create_chakram_ring(w, h, outer_r=41, inner_r=24, blade_cnt=8,
                                                 colors=((220, 255, 245), (100, 200, 190), (30, 95, 90)),
                                                 gem_color=(255, 215, 60))},
        # 34: w2_35 (New 27) - 데우스 엑스 마키나 (106x84)
        {"id": 34, "fn": "w2_35.png", "orig": None, "name": "데우스 엑스 마키나", "tier": 9, "star": 600, "w": 106, "h": 84,
         "gen": lambda w, h: create_divine_orbital(w, h, outer_r=48,
                                                   colors=((255, 255, 255), (240, 210, 110), (150, 100, 30)),
                                                   energy_color=(150, 230, 255), halo_type=1)},
    ]

    os.makedirs(CONTENT_DIR, exist_ok=True)
    generated_images = {}
    profiles = []

    for item in specs:
        idx = item["id"]
        fn = item["fn"]
        w = item["w"]
        h = item["h"]
        orig_id = item["orig"]
        
        if orig_id is not None:
            # Copy from backup_8
            src_path = os.path.join(BACKUP_DIR, f"w2_{orig_id}.png")
            im = Image.open(src_path).convert("RGBA")
            # All originals are 86x70
            cur_w, cur_h = im.size
            print(f"[{idx+1}/35] Remapping Original w2_{orig_id} -> {fn} ({cur_w}x{cur_h})")
        else:
            # Generate new pixel art
            im = item["gen"](w, h)
            cur_w, cur_h = im.size
            print(f"[{idx+1}/35] Synthesized New Boomerang {fn} ({cur_w}x{cur_h}) - {item['name']}")

        generated_images[fn] = im
        profiles.append({
            "id": idx,
            "filename": fn,
            "name": item["name"],
            "tier": item["tier"],
            "star": item["star"],
            "width": cur_w,
            "height": cur_h
        })

    # Save to all res directories
    for d in RES_DIRS:
        os.makedirs(d, exist_ok=True)
        for fn, im in generated_images.items():
            dest = os.path.join(d, fn)
            im.save(dest)

    # Save profiles metadata
    with open(os.path.join(CONTENT_DIR, "profiles.json"), "w", encoding="utf-8") as fp:
        json.dump(profiles, fp, ensure_ascii=False, indent=2)

    print("All 35 boomerangs generated and saved successfully!")
    return profiles, generated_images

if __name__ == "__main__":
    generate_all_35()

