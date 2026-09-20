# -*- coding: utf-8 -*-
"""Generate all 35 guns for Diana (w1_1 to w1_35) with unique concepts,
matching palettes, progressive sizing, and precise grip anchoring.
"""
import os
import json
from pathlib import Path
from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[2]
SOURCE_DIR = ROOT / 'content/guns/source'
RES_DIR = ROOT / 'Resources/res'
DEBUG_RES_DIR = ROOT / 'proj.win32/Debug.win32/Resources/res'
RELEASE_RES_DIR = ROOT / 'proj.win32/Release.win32/Resources/res'

# Exact palettes sampled from w1_1..w1_8 and Robin's high-tier weapons
C_OUTLINE = (22, 21, 27, 255)
C_DARK = (30, 31, 41, 255)

STEEL = {
    'deep': (25, 26, 35, 255),
    'shadow': (45, 48, 64, 255),
    'mid': (69, 72, 96, 255),
    'light': (112, 118, 151, 255),
    'bright': (187, 187, 200, 255),
    'shine': (254, 252, 254, 255),
}

SILVER = {
    'deep': (30, 33, 45, 255),
    'shadow': (58, 61, 82, 255),
    'mid': (104, 111, 151, 255),
    'light': (143, 151, 193, 255),
    'bright': (204, 204, 255, 255),
    'shine': (255, 255, 255, 255),
}

BRASS = {
    'deep': (87, 55, 0, 255),
    'shadow': (137, 95, 9, 255),
    'mid': (164, 121, 19, 255),
    'gold': (217, 174, 60, 255),
    'bright': (236, 214, 81, 255),
    'shine': (255, 255, 150, 255),
}

WOOD = {
    'deep': (21, 14, 11, 255),
    'shadow': (48, 25, 16, 255),
    'mid': (74, 54, 44, 255),
    'light': (96, 75, 64, 255),
    'bright': (145, 125, 110, 255),
    'shine': (219, 198, 180, 255),
}

FIRE = {
    'deep': (85, 17, 51, 255),
    'shadow': (121, 36, 52, 255),
    'mid': (157, 54, 53, 255),
    'bright': (204, 52, 52, 255),
    'flame': (255, 102, 76, 255),
    'yellow': (255, 210, 80, 255),
}

FROST = {
    'deep': (10, 28, 56, 255),
    'shadow': (26, 53, 96, 255),
    'mid': (58, 104, 168, 255),
    'light': (100, 148, 166, 255),
    'glow': (126, 234, 229, 255),
    'white': (235, 250, 255, 255),
}

VOLT = {
    'deep': (40, 35, 15, 255),
    'shadow': (100, 85, 20, 255),
    'mid': (180, 160, 35, 255),
    'bright': (235, 215, 60, 255),
    'spark': (255, 255, 102, 255),
    'white': (255, 255, 255, 255),
}

VOID = {
    'deep': (15, 10, 25, 255),
    'shadow': (45, 20, 65, 255),
    'mid': (93, 37, 122, 255),
    'glow': (152, 64, 204, 255),
    'light': (208, 128, 255, 255),
    'white': (250, 235, 255, 255),
}

DRAGON = {
    'deep': (25, 15, 10, 255),
    'shadow': (120, 30, 20, 255),
    'mid': (180, 45, 30, 255),
    'light': (230, 75, 40, 255),
    'scale_dark': (120, 30, 20, 255),
    'scale_mid': (180, 45, 30, 255),
    'scale_light': (230, 75, 40, 255),
    'gold': (220, 180, 50, 255),
    'eye': (255, 240, 90, 255),
}

CELESTIAL = {
    'deep': (35, 30, 45, 255),
    'shadow': (75, 70, 95, 255),
    'mid': (140, 135, 170, 255),
    'light': (215, 210, 240, 255),
    'bright': (215, 210, 240, 255),
    'white': (255, 255, 255, 255),
    'gold': (235, 200, 70, 255),
}


class GunCanvas:
    def __init__(self, w, h, grip_x, grip_y):
        self.w = w
        self.h = h
        self.grip_x = grip_x
        self.grip_y = grip_y
        self.im = Image.new('RGBA', (w, h), (0, 0, 0, 0))
        self.draw = ImageDraw.Draw(self.im)

    def p(self, x, y, col):
        if 0 <= x < self.w and 0 <= y < self.h:
            self.im.putpixel((x, y), col)

    def rect(self, x0, y0, x1, y1, col):
        for y in range(y0, y1 + 1):
            for x in range(x0, x1 + 1):
                self.p(x, y, col)

    def hline(self, x0, x1, y, col):
        for x in range(x0, x1 + 1):
            self.p(x, y, col)

    def vline(self, x, y0, y1, col):
        for y in range(y0, y1 + 1):
            self.p(x, y, col)

    def outline_box(self, x0, y0, x1, y1, border_col, fill_col=None):
        if fill_col:
            self.rect(x0 + 1, y0 + 1, x1 - 1, y1 - 1, fill_col)
        self.hline(x0, x1, y0, border_col)
        self.hline(x0, x1, y1, border_col)
        self.vline(x0, y0, y1, border_col)
        self.vline(x1, y0, y1, border_col)

    def draw_standard_grip(self, gx, gy, ramp, length=8, width=5, curve=-2):
        """Draws a standard ergonomic gun handle pointing down and slightly angled."""
        for i in range(length):
            y = gy + i
            cur_x = gx + int(curve * (i / length))
            # border left/right
            self.p(cur_x - width // 2 - 1, y, C_OUTLINE)
            self.p(cur_x + width // 2 + 1, y, C_OUTLINE)
            # fill with ramp shading
            for wx in range(-width // 2, width // 2 + 1):
                t = (wx + width // 2) / max(1, width)
                if t < 0.25:
                    c = ramp['shadow']
                elif t < 0.75:
                    c = ramp['mid']
                else:
                    c = ramp.get('light', ramp['mid'])
                self.p(cur_x + wx, y, c)
        # bottom cap
        by = gy + length
        bx = gx + int(curve)
        self.hline(bx - width // 2, bx + width // 2, by, C_OUTLINE)


def load_original_gun(idx):
    """Load one of the 8 original guns cropped from source."""
    src_path = SOURCE_DIR / f'w1_{idx}_original.png'
    assert src_path.exists(), f'Missing original source {src_path}'
    orig = Image.open(src_path).convert('RGBA')
    crop = orig.crop((30, 0, 64, 28))
    # find grip approx
    return crop, 17, 20


def make_w1_2_derringer():
    # 2. 더블 데린저 (황동 초소형 쌍열 권총, 30x24, grip=(18, 16))
    c = GunCanvas(30, 24, 18, 16)
    # Upper & lower twin barrels (extending left from x=18 down to x=6)
    # Upper barrel: y=7..10
    c.outline_box(6, 7, 18, 10, C_OUTLINE, BRASS['mid'])
    c.hline(7, 17, 8, BRASS['gold'])
    c.hline(7, 17, 9, BRASS['bright'])
    # Lower barrel: y=11..13
    c.outline_box(7, 11, 18, 13, C_OUTLINE, BRASS['shadow'])
    c.hline(8, 17, 12, BRASS['gold'])
    # Muzzle crown
    c.vline(5, 7, 10, C_OUTLINE)
    c.vline(6, 11, 13, C_OUTLINE)
    # Receiver / frame
    c.outline_box(16, 6, 23, 14, C_OUTLINE, BRASS['mid'])
    c.rect(17, 7, 22, 13, BRASS['gold'])
    c.p(19, 9, BRASS['shine'])
    c.p(20, 9, BRASS['shine'])
    # Hammer
    c.p(23, 5, C_OUTLINE)
    c.p(22, 5, STEEL['mid'])
    # Grip (compact rounded wood)
    c.draw_standard_grip(19, 14, WOOD, length=6, width=5, curve=1)
    # Trigger & guard
    c.p(14, 15, C_OUTLINE)
    c.p(15, 16, C_OUTLINE)
    c.p(16, 15, STEEL['light'])
    return c


def make_w1_3_flint_pincher():
    # 3. 포켓 플린처 (태엽식 톱니 회중 권총, 32x24, grip=(19, 16))
    c = GunCanvas(32, 24, 19, 16)
    # Snub fluted barrel (left to x=5)
    c.outline_box(5, 8, 18, 12, C_OUTLINE, STEEL['shadow'])
    c.hline(6, 17, 9, STEEL['mid'])
    c.hline(6, 17, 10, STEEL['light'])
    c.hline(6, 17, 11, STEEL['bright'])
    # Brass muzzle ring
    c.vline(5, 8, 12, BRASS['gold'])
    c.vline(4, 9, 11, C_OUTLINE)
    # Clockwork circular body / gear chamber
    c.outline_box(16, 6, 25, 15, C_OUTLINE, BRASS['mid'])
    c.rect(17, 7, 24, 14, BRASS['gold'])
    # Gear teeth accents
    c.p(20, 7, BRASS['bright'])
    c.p(21, 7, BRASS['bright'])
    c.p(17, 10, STEEL['deep'])
    c.p(24, 10, STEEL['deep'])
    c.p(20, 10, STEEL['bright'])  # center gear pin
    c.p(21, 10, STEEL['shine'])
    # Spur hammer on top
    c.p(24, 4, C_OUTLINE)
    c.p(25, 5, C_OUTLINE)
    # Walnut grip with brass butt cap
    c.draw_standard_grip(20, 15, WOOD, length=6, width=6, curve=2)
    c.hline(20, 23, 21, BRASS['gold'])
    # Trigger
    c.p(16, 16, STEEL['light'])
    c.p(15, 17, C_OUTLINE)
    return c


def make_w1_5_peacemaker():
    # 5. 피스메이커 (은빛 싱글액션 리볼버, 36x24, grip=(20, 16))
    c = GunCanvas(36, 24, 20, 16)
    # Long silver barrel (x=4 to x=18)
    c.outline_box(4, 8, 18, 11, C_OUTLINE, SILVER['shadow'])
    c.hline(5, 17, 9, SILVER['mid'])
    c.hline(5, 17, 10, SILVER['bright'])
    # Ejector rod underneath barrel
    c.hline(8, 17, 12, SILVER['shadow'])
    c.p(7, 12, C_OUTLINE)
    # Front blade sight
    c.p(5, 7, SILVER['bright'])
    # Cylinder chamber (fluted silver with engraved notches)
    c.outline_box(17, 7, 24, 13, C_OUTLINE, SILVER['shadow'])
    c.rect(18, 8, 23, 12, SILVER['mid'])
    c.hline(18, 23, 9, SILVER['bright'])
    c.hline(18, 23, 11, SILVER['shadow'])
    # Frame and hammer
    c.outline_box(23, 6, 27, 14, C_OUTLINE, SILVER['mid'])
    c.p(26, 5, C_OUTLINE)
    c.p(25, 5, SILVER['bright'])
    # Pearlescent ivory grip
    c.draw_standard_grip(22, 14, {'shadow': (180, 180, 190, 255), 'mid': (225, 225, 235, 255), 'light': (255, 255, 255, 255)}, length=7, width=6, curve=3)
    # Trigger guard
    c.p(18, 15, C_OUTLINE)
    c.p(19, 16, C_OUTLINE)
    c.p(19, 14, SILVER['bright'])
    return c


def make_w1_6_hunting_magnum():
    # 6. 헌팅 매그넘 (헤비 배럴 매그넘 리볼버, 36x26, grip=(20, 17))
    c = GunCanvas(36, 26, 20, 17)
    # Thick heavy barrel with ventilated top rib (x=3 to x=18)
    c.outline_box(3, 7, 18, 12, C_OUTLINE, STEEL['shadow'])
    c.hline(4, 17, 8, STEEL['mid'])
    c.hline(4, 17, 9, STEEL['light'])
    c.hline(4, 17, 10, STEEL['bright'])
    c.hline(4, 17, 11, STEEL['deep'])
    # Vents on top rib
    for vx in (6, 9, 12, 15):
        c.p(vx, 7, C_DARK)
    # Heavy cylinder
    c.outline_box(17, 7, 25, 14, C_OUTLINE, STEEL['shadow'])
    c.rect(18, 8, 24, 13, STEEL['mid'])
    c.hline(18, 24, 9, STEEL['light'])
    c.hline(18, 24, 11, STEEL['deep'])
    c.hline(18, 24, 12, STEEL['shadow'])
    # Rear sight & frame
    c.outline_box(24, 6, 28, 15, C_OUTLINE, STEEL['shadow'])
    c.p(25, 5, STEEL['light'])
    c.p(27, 5, C_OUTLINE)
    # Ergonomic grooved rubber grip
    c.draw_standard_grip(22, 15, {'shadow': (20, 20, 25, 255), 'mid': (38, 40, 50, 255), 'light': (60, 65, 80, 255)}, length=8, width=6, curve=2)
    c.p(22, 17, STEEL['mid'])  # finger groove highlight
    c.p(23, 19, STEEL['mid'])
    # Trigger
    c.p(18, 16, STEEL['bright'])
    c.p(17, 17, C_OUTLINE)
    return c


def make_w1_8_dual_trigger():
    # 8. 듀얼 트리거 (전술 머신피스톨 + 확장탄창, 38x26, grip=(22, 17))
    c = GunCanvas(38, 26, 22, 17)
    # Tactical slide & barrel with front compensator (x=2 to x=22)
    c.outline_box(2, 6, 22, 12, C_OUTLINE, STEEL['deep'])
    c.hline(3, 21, 7, STEEL['mid'])
    c.hline(3, 21, 8, STEEL['light'])
    c.hline(3, 21, 9, STEEL['mid'])
    c.hline(3, 21, 11, STEEL['shadow'])
    # Compensator slots
    c.vline(4, 7, 9, C_DARK)
    c.vline(6, 7, 9, C_DARK)
    # Top picatinny rail notches
    for rx in range(9, 21, 2):
        c.p(rx, 6, STEEL['bright'])
    # Lower receiver & frame
    c.outline_box(12, 12, 26, 16, C_OUTLINE, STEEL['shadow'])
    c.rect(13, 13, 25, 15, STEEL['mid'])
    # Extended magazine protruding below grip
    c.outline_box(22, 16, 27, 24, C_OUTLINE, STEEL['deep'])
    c.rect(23, 17, 26, 23, STEEL['mid'])
    c.hline(23, 26, 20, STEEL['light'])
    c.hline(22, 27, 24, BRASS['gold'])  # bumper plate
    # Textured grip
    c.draw_standard_grip(23, 16, STEEL, length=7, width=5, curve=1)
    # Dual trigger guard
    c.p(17, 17, C_OUTLINE)
    c.p(18, 18, C_OUTLINE)
    c.p(19, 17, STEEL['bright'])
    return c


def make_w1_9_sawed_off():
    # 9. 소드오프 샷건 (단축 이중 산탄총, 38x26, grip=(22, 17))
    c = GunCanvas(38, 26, 22, 17)
    # Twin wide shotgun barrels (x=3 to x=19)
    c.outline_box(3, 7, 19, 13, C_OUTLINE, STEEL['shadow'])
    c.hline(4, 18, 8, STEEL['mid'])
    c.hline(4, 18, 9, STEEL['bright'])
    c.hline(4, 18, 10, C_OUTLINE)  # rib between twin barrels
    c.hline(4, 18, 11, STEEL['mid'])
    c.hline(4, 18, 12, STEEL['light'])
    # Wide muzzle holes
    c.p(3, 8, C_DARK)
    c.p(3, 9, C_DARK)
    c.p(3, 11, C_DARK)
    c.p(3, 12, C_DARK)
    # Wooden forestock underneath barrels
    c.outline_box(9, 13, 18, 15, C_OUTLINE, WOOD['mid'])
    c.hline(10, 17, 14, WOOD['light'])
    # Break-action receiver with engraved steel plate
    c.outline_box(18, 6, 26, 14, C_OUTLINE, STEEL['mid'])
    c.rect(19, 7, 25, 13, STEEL['light'])
    c.p(22, 9, STEEL['shine'])
    c.p(25, 5, C_OUTLINE)  # top lever
    c.p(24, 6, BRASS['gold'])
    # Curved walnut grip
    c.draw_standard_grip(23, 14, WOOD, length=8, width=6, curve=3)
    c.hline(23, 26, 21, WOOD['shine'])
    # Double triggers
    c.p(19, 15, STEEL['mid'])
    c.p(20, 16, STEEL['bright'])
    c.p(18, 17, C_OUTLINE)
    return c


def make_w1_11_royal_musket():
    # 11. 로열 머스킷 (왕실 의장대 장총, 42x26, grip=(24, 17))
    c = GunCanvas(42, 26, 24, 17)
    # Extra long polished blued-steel barrel (x=2 to x=22)
    c.outline_box(2, 8, 22, 11, C_OUTLINE, STEEL['shadow'])
    c.hline(3, 21, 9, STEEL['mid'])
    c.hline(3, 21, 10, STEEL['bright'])
    # Brass muzzle band & mid-barrel bands
    c.vline(3, 8, 11, BRASS['gold'])
    c.vline(11, 8, 11, BRASS['gold'])
    c.vline(18, 8, 11, BRASS['gold'])
    # Full-length polished mahogany wooden stock
    c.outline_box(10, 11, 24, 14, C_OUTLINE, WOOD['mid'])
    c.hline(11, 23, 12, WOOD['light'])
    c.hline(11, 23, 13, WOOD['mid'])
    # Lockplate with golden crown engraving
    c.outline_box(21, 7, 28, 13, C_OUTLINE, BRASS['gold'])
    c.rect(22, 8, 27, 12, BRASS['bright'])
    c.p(24, 9, BRASS['shine'])
    c.p(25, 9, BRASS['shine'])
    # Elegant curved stock / grip
    c.draw_standard_grip(25, 14, WOOD, length=8, width=6, curve=4)
    c.hline(26, 29, 21, BRASS['gold'])  # gold buttplate
    # Trigger guard & curl
    c.p(21, 15, BRASS['gold'])
    c.p(22, 16, C_OUTLINE)
    return c


def make_w1_12_duelling_flint():
    # 12. 듀얼링 플린트 (귀족 결투용 은상감 권총, 38x26, grip=(22, 17))
    c = GunCanvas(38, 26, 22, 17)
    # Octagonal blued barrel (x=4 to x=20)
    c.outline_box(4, 8, 20, 12, C_OUTLINE, STEEL['shadow'])
    c.hline(5, 19, 9, STEEL['mid'])
    c.hline(5, 19, 10, SILVER['bright'])  # silver line inlay
    c.hline(5, 19, 11, STEEL['shadow'])
    # Front bead sight
    c.p(5, 7, BRASS['gold'])
    # Engraved silver lockplate & swan-neck cock
    c.outline_box(19, 7, 27, 13, C_OUTLINE, SILVER['mid'])
    c.rect(20, 8, 26, 12, SILVER['bright'])
    c.p(26, 5, C_OUTLINE)
    c.p(25, 6, SILVER['shine'])
    # Ebony / dark walnut grip with flared silver buttcap
    c.draw_standard_grip(23, 13, WOOD, length=9, width=6, curve=3)
    # Silver buttcap sphere
    c.outline_box(24, 21, 28, 23, C_OUTLINE, SILVER['bright'])
    c.p(26, 22, SILVER['shine'])
    # Trigger & curly spur guard
    c.p(19, 15, C_OUTLINE)
    c.p(20, 16, SILVER['bright'])
    c.p(21, 15, SILVER['shadow'])
    return c


def make_w1_14_frost_ray():
    # 14. 프로스트 레이 (빙설마도총, 40x26, grip=(23, 17))
    c = GunCanvas(40, 26, 23, 17)
    # Twin crystal prongs emitting cold beam (x=2 to x=18)
    c.outline_box(2, 7, 18, 9, C_OUTLINE, FROST['light'])
    c.hline(3, 17, 8, FROST['white'])
    c.outline_box(2, 12, 18, 14, C_OUTLINE, FROST['light'])
    c.hline(3, 17, 13, FROST['white'])
    # Prongs tips
    c.p(2, 6, FROST['glow'])
    c.p(2, 15, FROST['glow'])
    # Central glowing ice-core chamber (x=9 to x=16)
    c.rect(9, 10, 16, 11, FROST['glow'])
    c.p(12, 10, FROST['white'])
    c.p(13, 10, FROST['white'])
    # Receiver / frame (metallic silver with ice runes)
    c.outline_box(17, 6, 26, 15, C_OUTLINE, SILVER['shadow'])
    c.rect(18, 7, 25, 14, SILVER['mid'])
    c.hline(19, 24, 8, FROST['glow'])  # rune line
    c.hline(19, 24, 13, FROST['glow'])
    # Grip (cool midnight blue with frost grip wrap)
    c.draw_standard_grip(24, 15, FROST, length=7, width=6, curve=2)
    # Trigger
    c.p(19, 16, FROST['glow'])
    c.p(20, 17, C_OUTLINE)
    return c


def make_w1_15_voltic_blaster():
    # 15. 볼틱 블래스터 (뇌전마도총, 42x28, grip=(24, 18))
    c = GunCanvas(42, 28, 24, 18)
    # Tesla coil barrel: central rod with copper rings (x=3 to x=21)
    c.outline_box(3, 9, 21, 13, C_OUTLINE, STEEL['shadow'])
    c.hline(4, 20, 10, STEEL['mid'])
    c.hline(4, 20, 11, VOLT['spark'])
    c.hline(4, 20, 12, STEEL['shadow'])
    # Copper coil rings
    for rx in (6, 10, 14, 18):
        c.outline_box(rx, 7, rx + 2, 15, C_OUTLINE, BRASS['gold'])
        c.vline(rx + 1, 8, 14, BRASS['bright'])
    # Sparking emitter electrodes at muzzle
    c.p(2, 8, VOLT['spark'])
    c.p(1, 9, VOLT['white'])
    c.p(2, 14, VOLT['spark'])
    # Heavy capacitor generator receiver
    c.outline_box(21, 6, 30, 16, C_OUTLINE, STEEL['deep'])
    c.rect(22, 7, 29, 15, STEEL['mid'])
    # Glowing energy dial
    c.outline_box(24, 9, 27, 12, C_OUTLINE, VOLT['bright'])
    c.p(25, 10, VOLT['white'])
    # Industrial ribbed grip
    c.draw_standard_grip(25, 16, STEEL, length=8, width=6, curve=2)
    c.p(24, 18, VOLT['spark'])
    c.p(25, 20, VOLT['spark'])
    # Trigger
    c.p(20, 18, VOLT['spark'])
    c.p(19, 19, C_OUTLINE)
    return c


def make_w1_17_eclipse_rifle():
    # 17. 이클립스 라이플 (일식의 흑태양 소총, 46x26, grip=(26, 17))
    c = GunCanvas(46, 26, 26, 17)
    # Long sleek black barrel with integrated suppressor (x=2 to x=24)
    c.outline_box(2, 9, 24, 13, C_OUTLINE, STEEL['deep'])
    c.hline(3, 23, 10, STEEL['shadow'])
    c.hline(3, 23, 11, FIRE['mid'])  # glowing dark-red heat dissipation strip
    c.hline(3, 23, 12, STEEL['deep'])
    # Muzzle crown
    c.vline(2, 8, 14, C_OUTLINE)
    # Top-mounted scope with glowing ruby lens
    c.outline_box(14, 4, 28, 8, C_OUTLINE, STEEL['deep'])
    c.rect(15, 5, 27, 7, STEEL['shadow'])
    c.vline(15, 5, 7, FIRE['bright'])  # front lens
    c.p(15, 6, FIRE['yellow'])
    c.vline(27, 5, 7, FIRE['bright'])  # ocular lens
    # Receiver / frame
    c.outline_box(23, 8, 33, 16, C_OUTLINE, STEEL['deep'])
    c.rect(24, 9, 32, 15, STEEL['shadow'])
    c.p(28, 12, FIRE['bright'])  # eclipse core emblem
    c.p(28, 11, FIRE['yellow'])
    # Extended sniper stock & ergonomic grip
    c.draw_standard_grip(27, 16, STEEL, length=8, width=6, curve=2)
    c.outline_box(32, 10, 39, 15, C_OUTLINE, STEEL['deep'])  # skeleton stock
    c.hline(33, 38, 11, STEEL['shadow'])
    # Trigger
    c.p(22, 17, FIRE['mid'])
    c.p(21, 18, C_OUTLINE)
    return c


def make_w1_18_luminous_cannon():
    # 18. 루미너스 캐넌 (광휘포, 46x28, grip=(26, 18))
    c = GunCanvas(46, 28, 26, 18)
    # Heavy flared trumpet / bell cannon muzzle (x=2 to x=12)
    c.outline_box(2, 6, 8, 16, C_OUTLINE, BRASS['gold'])
    c.rect(3, 7, 7, 15, BRASS['bright'])
    c.vline(2, 5, 17, BRASS['shine'])
    c.vline(8, 7, 15, BRASS['shadow'])
    # Prismatic focusing chamber (x=9 to x=24)
    c.outline_box(8, 8, 24, 14, C_OUTLINE, STEEL['shadow'])
    c.rect(9, 9, 23, 13, BRASS['gold'])
    c.hline(9, 23, 10, BRASS['bright'])
    c.hline(9, 23, 11, BRASS['shine'])
    # Glowing prism core windows
    for cx in (12, 16, 20):
        c.outline_box(cx, 7, cx + 2, 15, C_OUTLINE, FROST['glow'])
        c.p(cx + 1, 11, FROST['white'])
    # Heavy ornate breech
    c.outline_box(24, 6, 33, 17, C_OUTLINE, BRASS['deep'])
    c.rect(25, 7, 32, 16, BRASS['gold'])
    c.p(28, 11, BRASS['shine'])
    # Gilded heavy grip with counterbalance sphere
    c.draw_standard_grip(27, 17, BRASS, length=8, width=7, curve=2)
    c.outline_box(27, 24, 31, 26, C_OUTLINE, BRASS['bright'])
    # Trigger
    c.p(22, 18, BRASS['shine'])
    c.p(21, 19, C_OUTLINE)
    return c


def make_w1_20_abyss_bazooka():
    # 20. 아비스 바주카 (심연의 박격포, 48x30, grip=(27, 19))
    c = GunCanvas(48, 30, 27, 19)
    # Wide heavy mortar barrel (x=2 to x=25, y=7..16)
    c.outline_box(2, 7, 25, 16, C_OUTLINE, VOID['deep'])
    c.rect(3, 8, 24, 15, VOID['shadow'])
    c.hline(3, 24, 9, VOID['mid'])
    c.hline(3, 24, 10, VOID['glow'])
    c.hline(3, 24, 11, VOID['light'])
    c.hline(3, 24, 14, VOID['deep'])
    # Spiky muzzle horn ring
    c.vline(2, 6, 17, C_OUTLINE)
    c.p(1, 5, VOID['glow'])
    c.p(1, 18, VOID['glow'])
    c.p(2, 11, VOID['white'])  # maw center
    # Netherflame venting chambers
    for vx in (8, 14, 20):
        c.outline_box(vx, 5, vx + 3, 7, C_OUTLINE, VOID['glow'])
        c.p(vx + 1, 6, VOID['white'])
    # Massive breach & shoulder rest housing
    c.outline_box(25, 6, 37, 18, C_OUTLINE, VOID['deep'])
    c.rect(26, 7, 36, 17, VOID['shadow'])
    c.p(31, 11, VOID['light'])
    c.p(31, 12, VOID['white'])
    # Demonic horned grip
    c.draw_standard_grip(28, 18, VOID, length=9, width=7, curve=3)
    # Trigger
    c.p(23, 19, VOID['glow'])
    c.p(22, 20, C_OUTLINE)
    return c


def make_w1_21_behemoth_launcher():
    # 21. 베히모스 런처 (거수섬멸포, 50x30, grip=(28, 19))
    c = GunCanvas(50, 30, 28, 19)
    # Heavy bore barrel with bone armor carapace (x=3 to x=22)
    c.outline_box(3, 8, 22, 16, C_OUTLINE, STEEL['deep'])
    c.rect(4, 9, 21, 15, STEEL['mid'])
    c.hline(4, 21, 10, STEEL['light'])
    c.hline(4, 21, 11, STEEL['bright'])
    # Bone plating on top
    c.outline_box(5, 5, 20, 8, C_OUTLINE, WOOD['bright'])
    c.hline(6, 19, 6, WOOD['shine'])
    # Massive rotary cylinder housing (6 chambers)
    c.outline_box(20, 6, 33, 18, C_OUTLINE, STEEL['shadow'])
    c.rect(21, 7, 32, 17, STEEL['mid'])
    for cy in (8, 12, 15):
        c.outline_box(23, cy, 26, cy + 2, C_OUTLINE, BRASS['gold'])
        c.outline_box(28, cy, 31, cy + 2, C_OUTLINE, BRASS['gold'])
    # Heavy recoil compensator frame & grip
    c.outline_box(33, 7, 41, 17, C_OUTLINE, STEEL['deep'])
    c.rect(34, 8, 40, 16, STEEL['shadow'])
    c.draw_standard_grip(29, 18, STEEL, length=9, width=8, curve=2)
    # Trigger
    c.p(23, 19, BRASS['bright'])
    c.p(22, 20, C_OUTLINE)
    return c


def make_w1_23_testament():
    # 23. 테스타먼트 (성약의 십자 성포, 50x30, grip=(28, 19))
    c = GunCanvas(50, 30, 28, 19)
    # Heavy gilded cruciform barrel (x=4 to x=26)
    c.outline_box(4, 9, 26, 15, C_OUTLINE, BRASS['gold'])
    c.rect(5, 10, 25, 14, BRASS['bright'])
    c.hline(5, 25, 11, BRASS['shine'])
    c.hline(5, 25, 12, CELESTIAL['white'])
    # Cross vertical arms (x=12 to x=16, y=3..21)
    c.outline_box(12, 3, 16, 21, C_OUTLINE, BRASS['gold'])
    c.rect(13, 4, 15, 20, BRASS['bright'])
    c.vline(14, 4, 20, BRASS['shine'])
    c.p(14, 3, CELESTIAL['white'])
    c.p(14, 21, CELESTIAL['white'])
    # Holy rune script glowing along barrel
    c.p(7, 12, FROST['glow'])
    c.p(9, 12, FROST['glow'])
    c.p(19, 12, FROST['glow'])
    c.p(22, 12, FROST['glow'])
    # Holy ark breech / reliquary
    c.outline_box(26, 7, 37, 17, C_OUTLINE, CELESTIAL['shadow'])
    c.rect(27, 8, 36, 16, CELESTIAL['bright'])
    c.outline_box(29, 10, 34, 14, C_OUTLINE, BRASS['gold'])
    c.p(31, 12, CELESTIAL['gold'])
    # Gilded marble grip
    c.draw_standard_grip(29, 17, CELESTIAL, length=9, width=7, curve=2)
    # Trigger
    c.p(24, 19, CELESTIAL['gold'])
    c.p(23, 20, C_OUTLINE)
    return c


def make_w1_24_ragnarok():
    # 24. 라그나로크 (종말의 핸드캐넌, 52x30, grip=(29, 19))
    c = GunCanvas(52, 30, 29, 19)
    # Jagged dark-matter barrel with jagged demon horns (x=2 to x=27)
    c.outline_box(2, 8, 27, 16, C_OUTLINE, VOID['deep'])
    c.rect(3, 9, 26, 15, VOID['shadow'])
    c.hline(3, 26, 10, FIRE['mid'])
    c.hline(3, 26, 11, FIRE['bright'])
    c.hline(3, 26, 12, FIRE['yellow'])
    # Top and bottom jagged horns
    c.p(2, 6, FIRE['bright'])
    c.p(3, 7, C_OUTLINE)
    c.p(2, 18, FIRE['bright'])
    c.p(3, 17, C_OUTLINE)
    # Pulsing core sphere in breech
    c.outline_box(27, 5, 39, 19, C_OUTLINE, VOID['deep'])
    c.rect(28, 6, 38, 18, VOID['mid'])
    c.outline_box(30, 8, 36, 16, C_OUTLINE, FIRE['shadow'])
    c.rect(31, 9, 35, 15, FIRE['bright'])
    c.p(33, 12, FIRE['yellow'])
    # Spine-covered demonic grip
    c.draw_standard_grip(30, 18, VOID, length=9, width=8, curve=3)
    c.p(32, 21, FIRE['bright'])
    # Trigger
    c.p(25, 20, FIRE['bright'])
    c.p(24, 21, C_OUTLINE)
    return c


def make_w1_25_dragon_breath():
    # 25. 드래곤 브레스 (신화 고룡포, 54x32, grip=(30, 20))
    c = GunCanvas(54, 32, 30, 20)
    # Dragon skull barrel: upper jaw (y=6..11) & lower jaw (y=14..18)
    # Upper jaw extending to x=2
    c.outline_box(2, 6, 28, 11, C_OUTLINE, DRAGON['scale_dark'])
    c.rect(3, 7, 27, 10, DRAGON['scale_mid'])
    c.hline(4, 26, 8, DRAGON['scale_light'])
    # Lower jaw
    c.outline_box(4, 14, 26, 18, C_OUTLINE, DRAGON['scale_dark'])
    c.rect(5, 15, 25, 17, DRAGON['scale_mid'])
    # Open glowing throat (x=6 to x=22, y=11..14)
    c.rect(6, 11, 24, 14, FIRE['bright'])
    c.hline(8, 22, 12, FIRE['flame'])
    c.hline(8, 22, 13, FIRE['yellow'])
    # Sharp white dragon fangs
    for fx in (5, 9, 13, 17, 21):
        c.p(fx, 11, CELESTIAL['white'])
        c.p(fx + 2, 14, CELESTIAL['white'])
    # Glowing dragon eye on skull side
    c.outline_box(22, 5, 25, 8, C_OUTLINE, DRAGON['gold'])
    c.p(23, 6, DRAGON['eye'])
    # Horned cranium & dragon scale breech
    c.outline_box(28, 5, 42, 20, C_OUTLINE, DRAGON['deep'])
    c.rect(29, 6, 41, 19, DRAGON['scale_mid'])
    # Backward curved horns
    c.hline(36, 44, 4, DRAGON['gold'])
    c.hline(38, 46, 3, DRAGON['gold'])
    # Scale-plated grip
    c.draw_standard_grip(31, 19, DRAGON, length=10, width=8, curve=3)
    # Trigger
    c.p(26, 21, FIRE['yellow'])
    c.p(25, 22, C_OUTLINE)
    return c


def make_w1_26_apocalypse():
    # 26. 묵시록의 나팔 (천상 심판포, 54x32, grip=(30, 20))
    c = GunCanvas(54, 32, 30, 20)
    # Golden trumpet flare muzzle (x=2 to x=10, y=4..20)
    c.outline_box(2, 4, 10, 20, C_OUTLINE, BRASS['gold'])
    c.rect(3, 5, 9, 19, BRASS['bright'])
    c.vline(2, 3, 21, BRASS['shine'])
    c.vline(3, 7, 17, CELESTIAL['white'])
    # Horn tube with spiraling angel wings
    c.outline_box(10, 9, 28, 15, C_OUTLINE, BRASS['gold'])
    c.rect(11, 10, 27, 14, BRASS['bright'])
    c.hline(11, 27, 11, BRASS['shine'])
    c.hline(11, 27, 12, CELESTIAL['white'])
    # Angelic wing plates along barrel
    c.outline_box(14, 4, 24, 9, C_OUTLINE, CELESTIAL['mid'])
    c.rect(15, 5, 23, 8, CELESTIAL['white'])
    c.outline_box(14, 15, 24, 20, C_OUTLINE, CELESTIAL['mid'])
    c.rect(15, 16, 23, 19, CELESTIAL['white'])
    # Holy halo ring above breech
    c.outline_box(28, 1, 36, 5, C_OUTLINE, BRASS['shine'])
    c.rect(29, 2, 35, 4, BRASS['gold'])
    # Breech & ornate handle
    c.outline_box(28, 6, 42, 19, C_OUTLINE, CELESTIAL['shadow'])
    c.rect(29, 7, 41, 18, CELESTIAL['bright'])
    c.draw_standard_grip(31, 19, CELESTIAL, length=10, width=8, curve=2)
    c.p(26, 21, BRASS['shine'])
    c.p(25, 22, C_OUTLINE)
    return c


def make_w1_27_leviathan():
    # 27. 레비아탄 하푼 (심해 마수 작살총, 56x32, grip=(31, 20))
    c = GunCanvas(56, 32, 31, 20)
    # Long barbed steel harpoon spear resting in launch trough (x=2 to x=32, y=6..9)
    c.outline_box(2, 6, 32, 9, C_OUTLINE, STEEL['shadow'])
    c.hline(3, 31, 7, STEEL['bright'])
    c.hline(3, 31, 8, STEEL['shine'])
    # Trident barbed harpoon tip
    c.p(1, 7, STEEL['shine'])
    c.p(4, 5, STEEL['bright'])
    c.p(4, 10, STEEL['bright'])
    # Heavy sea-bronze launch rail & pressure tank (y=10..18)
    c.outline_box(6, 10, 30, 18, C_OUTLINE, BRASS['deep'])
    c.rect(7, 11, 29, 17, BRASS['mid'])
    c.hline(7, 29, 12, BRASS['gold'])
    c.hline(7, 29, 13, FROST['glow'])  # pressure gauge line
    # Tension cable winch wheel
    c.outline_box(22, 15, 28, 21, C_OUTLINE, STEEL['deep'])
    c.rect(23, 16, 27, 20, STEEL['shadow'])
    c.p(25, 18, BRASS['gold'])
    # Heavy naval stock & pressure valve housing
    c.outline_box(30, 8, 44, 20, C_OUTLINE, BRASS['deep'])
    c.rect(31, 9, 43, 19, BRASS['gold'])
    # Heavy reinforced grip
    c.draw_standard_grip(32, 19, WOOD, length=10, width=8, curve=3)
    c.p(27, 21, BRASS['bright'])
    c.p(26, 22, C_OUTLINE)
    return c


def make_w1_28_valkyrie():
    # 28. 발키리 레일건 (초전도 질주포, 58x32, grip=(32, 20))
    c = GunCanvas(58, 32, 32, 20)
    # Dual superconducting rails with central particle track (x=2 to x=32)
    c.outline_box(2, 7, 32, 10, C_OUTLINE, SILVER['shadow'])
    c.hline(3, 31, 8, SILVER['bright'])
    c.hline(3, 31, 9, FROST['white'])
    c.outline_box(2, 14, 32, 17, C_OUTLINE, SILVER['shadow'])
    c.hline(3, 31, 15, SILVER['bright'])
    c.hline(3, 31, 16, FROST['white'])
    # Superconducting particle beam in center
    c.rect(4, 11, 30, 13, FROST['glow'])
    c.hline(6, 28, 12, VOLT['spark'])
    # Valkyrie feather wing plates along upper rail
    c.outline_box(12, 3, 26, 7, C_OUTLINE, SILVER['mid'])
    c.rect(13, 4, 25, 6, SILVER['shine'])
    c.outline_box(12, 17, 26, 21, C_OUTLINE, SILVER['mid'])
    c.rect(13, 18, 25, 20, SILVER['shine'])
    # Accelerator capacitor breech
    c.outline_box(32, 5, 47, 20, C_OUTLINE, SILVER['shadow'])
    c.rect(33, 6, 46, 19, SILVER['mid'])
    c.outline_box(36, 8, 43, 16, C_OUTLINE, FROST['glow'])
    c.rect(37, 9, 42, 15, FROST['white'])
    # Aerodynamic grip
    c.draw_standard_grip(33, 19, SILVER, length=10, width=8, curve=2)
    c.p(28, 21, FROST['glow'])
    c.p(27, 22, C_OUTLINE)
    return c


def make_w1_29_hades():
    # 29. 하데스 익스큐셔너 (명왕의 사신포, 58x34, grip=(32, 21))
    c = GunCanvas(58, 34, 32, 21)
    # Heavy dark scythe blade curved under long barrel (x=2 to x=32)
    c.outline_box(2, 8, 32, 13, C_OUTLINE, VOID['deep'])
    c.rect(3, 9, 31, 12, VOID['shadow'])
    c.hline(3, 31, 10, VOID['glow'])
    c.hline(3, 31, 11, VOID['white'])
    # Curved scythe bayonet under barrel (tip extends down to x=2, y=22)
    for bx in range(2, 24):
        by = 13 + int((24 - bx) * 0.45)
        c.outline_box(bx, by, bx + 1, by + 2, C_OUTLINE, SILVER['bright'])
        c.p(bx, by + 1, SILVER['shine'])
    # Soul orb containment chamber in breech
    c.outline_box(32, 5, 48, 21, C_OUTLINE, VOID['deep'])
    c.rect(33, 6, 47, 20, VOID['shadow'])
    c.outline_box(36, 8, 44, 18, C_OUTLINE, VOID['mid'])
    c.rect(37, 9, 43, 17, VOID['glow'])
    c.p(40, 13, VOID['white'])  # soul face glow
    # Bone-clad grim grip
    c.draw_standard_grip(33, 20, VOID, length=10, width=8, curve=3)
    c.p(28, 22, VOID['light'])
    c.p(27, 23, C_OUTLINE)
    return c


def make_w1_30_dimension():
    # 30. 차원붕괴포 (시공간 왜곡총, 60x34, grip=(33, 21))
    c = GunCanvas(60, 34, 33, 21)
    # Floating segmented dimensional rings rotating around void axis
    c.hline(2, 34, 13, VOID['white'])  # central tachyon beam
    c.hline(2, 34, 14, VOID['glow'])
    # 3 Dimensional rings
    for rx, r_h in ((6, 8), (16, 11), (26, 14)):
        c.outline_box(rx, 13 - r_h // 2, rx + 4, 14 + r_h // 2, C_OUTLINE, FROST['glow'])
        c.rect(rx + 1, 14 - r_h // 2, rx + 3, 13 + r_h // 2, VOID['mid'])
        c.vline(rx + 2, 14 - r_h // 2, 13 + r_h // 2, FROST['white'])
    # Quantum singularity breech housing
    c.outline_box(34, 6, 49, 21, C_OUTLINE, VOID['deep'])
    c.rect(35, 7, 48, 20, VOID['shadow'])
    c.outline_box(38, 9, 45, 18, C_OUTLINE, FROST['glow'])
    c.rect(39, 10, 44, 17, VOID['glow'])
    c.p(41, 13, FROST['white'])
    c.p(42, 13, FROST['white'])
    # Floating crystal grip
    c.draw_standard_grip(34, 20, FROST, length=10, width=8, curve=2)
    c.p(29, 22, FROST['glow'])
    c.p(28, 23, C_OUTLINE)
    return c


def make_w1_31_supernova():
    # 31. 슈퍼노바 블래스터 (성간 플라즈마포, 62x34, grip=(34, 21))
    c = GunCanvas(62, 34, 34, 21)
    # Heavy plasma accelerator tube (x=2 to x=34, y=8..18)
    c.outline_box(2, 8, 34, 18, C_OUTLINE, FIRE['deep'])
    c.rect(3, 9, 33, 17, FIRE['shadow'])
    c.hline(3, 33, 11, FIRE['bright'])
    c.hline(3, 33, 12, FIRE['flame'])
    c.hline(3, 33, 13, FIRE['yellow'])
    c.hline(3, 33, 14, CELESTIAL['white'])
    # Flared corona vents at muzzle
    c.p(1, 7, FIRE['yellow'])
    c.p(1, 19, FIRE['yellow'])
    # Stellar core containment sphere (x=16 to x=26, y=5..21)
    c.outline_box(16, 5, 26, 21, C_OUTLINE, BRASS['gold'])
    c.rect(17, 6, 25, 20, FIRE['flame'])
    c.rect(19, 8, 23, 18, FIRE['yellow'])
    c.p(21, 13, CELESTIAL['white'])
    # Star generator breech & heat sinks
    c.outline_box(34, 5, 51, 21, C_OUTLINE, FIRE['deep'])
    c.rect(35, 6, 50, 20, FIRE['shadow'])
    # Heat sink fins
    for fx in range(37, 49, 3):
        c.vline(fx, 2, 5, FIRE['bright'])
    # Golden reinforced grip
    c.draw_standard_grip(35, 20, BRASS, length=10, width=9, curve=2)
    c.p(30, 22, FIRE['yellow'])
    c.p(29, 23, C_OUTLINE)
    return c


def make_w1_32_judgment():
    # 32. 천상신의 징벌 (신성 중화포, 62x36, grip=(34, 22))
    c = GunCanvas(62, 36, 34, 22)
    # Divine triple-barrel sanctum artillery (x=3 to x=34)
    # Top barrel
    c.outline_box(3, 6, 34, 10, C_OUTLINE, BRASS['gold'])
    c.hline(4, 33, 8, CELESTIAL['white'])
    # Center barrel
    c.outline_box(2, 11, 34, 16, C_OUTLINE, BRASS['gold'])
    c.hline(3, 33, 13, CELESTIAL['white'])
    c.hline(3, 33, 14, BRASS['bright'])
    # Bottom barrel
    c.outline_box(3, 17, 34, 21, C_OUTLINE, BRASS['gold'])
    c.hline(4, 33, 19, CELESTIAL['white'])
    # Divine floating halo rings above & below
    c.outline_box(14, 1, 26, 5, C_OUTLINE, BRASS['shine'])
    c.rect(15, 2, 25, 4, CELESTIAL['gold'])
    c.outline_box(14, 22, 26, 26, C_OUTLINE, BRASS['shine'])
    c.rect(15, 23, 25, 25, CELESTIAL['gold'])
    # Marble & ivory reliquary breech
    c.outline_box(34, 5, 52, 22, C_OUTLINE, CELESTIAL['shadow'])
    c.rect(35, 6, 51, 21, CELESTIAL['bright'])
    c.outline_box(40, 9, 47, 18, C_OUTLINE, BRASS['gold'])
    c.p(43, 13, BRASS['shine'])
    # Holy scepter grip
    c.draw_standard_grip(35, 21, CELESTIAL, length=11, width=9, curve=2)
    c.p(30, 23, BRASS['shine'])
    c.p(29, 24, C_OUTLINE)
    return c


def make_w1_33_astral():
    # 33. 아스트랄 블래스터 (성운 성간포, 64x36, grip=(35, 22))
    c = GunCanvas(64, 36, 35, 22)
    # Deep indigo / starlight gradient crystal barrel (x=2 to x=35, y=7..19)
    c.outline_box(2, 7, 35, 19, C_OUTLINE, VOID['deep'])
    c.rect(3, 8, 34, 18, VOID['shadow'])
    c.hline(3, 34, 10, VOID['mid'])
    c.hline(3, 34, 11, VOID['glow'])
    c.hline(3, 34, 12, FROST['glow'])
    c.hline(3, 34, 13, CELESTIAL['white'])
    c.hline(3, 34, 14, FROST['glow'])
    c.hline(3, 34, 15, VOID['glow'])
    # Embedded twinkling starlight crystals along barrel
    for sx, sy in ((8, 9), (14, 16), (20, 9), (26, 17), (32, 10)):
        c.p(sx, sy, CELESTIAL['white'])
        c.p(sx + 1, sy, FROST['white'])
        c.p(sx, sy + 1, FROST['white'])
    # Spiral galaxy core chamber in breech
    c.outline_box(35, 5, 53, 22, C_OUTLINE, VOID['deep'])
    c.rect(36, 6, 52, 21, VOID['shadow'])
    c.outline_box(40, 8, 48, 19, C_OUTLINE, FROST['glow'])
    c.rect(41, 9, 47, 18, VOID['mid'])
    c.p(44, 13, CELESTIAL['white'])
    c.p(43, 14, FROST['glow'])
    c.p(45, 14, VOID['light'])
    # Star-dusted ergonomic grip
    c.draw_standard_grip(36, 21, VOID, length=11, width=9, curve=3)
    c.p(31, 23, FROST['glow'])
    c.p(30, 24, C_OUTLINE)
    return c


def make_w1_34_singularity():
    # 34. 인피니티 싱귤래리티 (절대중력포, 64x36, grip=(35, 22))
    c = GunCanvas(64, 36, 35, 22)
    # Event-horizon black-hole emitter at muzzle (x=2..10, y=7..19)
    # Black hole center
    c.outline_box(2, 7, 10, 19, C_OUTLINE, (0, 0, 0, 255))
    c.rect(3, 8, 9, 18, (0, 0, 0, 255))
    # Glowing accretion disk ring surrounding black hole
    c.outline_box(0, 5, 12, 21, C_OUTLINE, VOID['light'])
    c.vline(0, 8, 18, FROST['glow'])
    c.vline(12, 8, 18, FROST['glow'])
    c.hline(3, 9, 5, FROST['white'])
    c.hline(3, 9, 21, FROST['white'])
    # Chronon field containment rails (x=10 to x=35)
    c.outline_box(10, 9, 35, 17, C_OUTLINE, STEEL['deep'])
    c.rect(11, 10, 34, 16, STEEL['shadow'])
    c.hline(11, 34, 12, (0, 0, 0, 255))
    c.hline(11, 34, 13, VOID['glow'])
    c.hline(11, 34, 14, FROST['white'])
    # Magnetic containment rings
    for mx in (14, 21, 28):
        c.outline_box(mx, 7, mx + 3, 19, C_OUTLINE, BRASS['gold'])
        c.vline(mx + 1, 8, 18, BRASS['bright'])
    # Massive gravitational stabilizer breech
    c.outline_box(35, 5, 54, 23, C_OUTLINE, STEEL['deep'])
    c.rect(36, 6, 53, 22, STEEL['shadow'])
    c.outline_box(41, 9, 49, 19, C_OUTLINE, VOID['glow'])
    c.rect(42, 10, 48, 18, (0, 0, 0, 255))
    c.p(45, 14, CELESTIAL['white'])
    # Heavy anti-grav grip
    c.draw_standard_grip(36, 22, STEEL, length=11, width=9, curve=2)
    c.p(31, 24, FROST['white'])
    c.p(30, 25, C_OUTLINE)
    return c


def make_w1_35_godslayer():
    # 35. 신살자의 총 (오버로드 결전병기 데이사이드, 66x38, grip=(36, 23))
    c = GunCanvas(66, 38, 36, 23)
    # Immense twin-tier God-Slaying rail barrel (x=2 to x=36, y=6..22)
    c.outline_box(2, 6, 36, 22, C_OUTLINE, STEEL['deep'])
    c.rect(3, 7, 35, 21, (15, 12, 20, 255))
    # Dual particle accelerator channels
    c.hline(3, 35, 9, FIRE['bright'])
    c.hline(3, 35, 10, FIRE['yellow'])
    c.hline(3, 35, 11, CELESTIAL['white'])
    c.hline(3, 35, 14, BRASS['gold'])  # central divider
    c.hline(3, 35, 17, FIRE['bright'])
    c.hline(3, 35, 18, FIRE['yellow'])
    c.hline(3, 35, 19, CELESTIAL['white'])
    # Serrated God-slaying blade spines on top and bottom
    for sx in range(4, 32, 6):
        c.p(sx, 4, BRASS['gold'])
        c.p(sx + 1, 5, BRASS['bright'])
        c.p(sx, 24, BRASS['gold'])
        c.p(sx + 1, 23, BRASS['bright'])
    # Twin frontal focusing crystals
    c.p(1, 8, FIRE['yellow'])
    c.p(0, 9, CELESTIAL['white'])
    c.p(1, 10, FIRE['yellow'])
    c.p(1, 16, FIRE['yellow'])
    c.p(0, 17, CELESTIAL['white'])
    c.p(1, 18, FIRE['yellow'])
    # Cosmic Ruin generator breech
    c.outline_box(36, 4, 56, 24, C_OUTLINE, STEEL['deep'])
    c.rect(37, 5, 55, 23, (25, 20, 32, 255))
    c.outline_box(41, 7, 51, 21, C_OUTLINE, BRASS['gold'])
    c.rect(42, 8, 50, 20, FIRE['mid'])
    c.outline_box(44, 10, 48, 18, C_OUTLINE, FIRE['yellow'])
    c.rect(45, 11, 47, 17, CELESTIAL['white'])
    # Imperial dragon gold engravings on stock
    c.hline(48, 55, 6, BRASS['bright'])
    c.hline(48, 55, 22, BRASS['bright'])
    # Heavy majestic grip
    c.draw_standard_grip(37, 23, BRASS, length=12, width=10, curve=3)
    c.p(32, 25, FIRE['yellow'])
    c.p(31, 26, C_OUTLINE)
    return c


BUILDERS = {
    1: ('발화식 총', lambda: load_original_gun(1)),
    2: ('더블 데린저', make_w1_2_derringer),
    3: ('포켓 플린처', make_w1_3_flint_pincher),
    4: ('리볼버 파이슨', lambda: load_original_gun(2)),
    5: ('피스메이커', make_w1_5_peacemaker),
    6: ('헌팅 매그넘', make_w1_6_hunting_magnum),
    7: ('45구경 오토건', lambda: load_original_gun(3)),
    8: ('듀얼 트리거', make_w1_8_dual_trigger),
    9: ('소드오프 샷건', make_w1_9_sawed_off),
    10: ('고져스 건', lambda: load_original_gun(4)),
    11: ('로열 머스킷', make_w1_11_royal_musket),
    12: ('듀얼링 플린트', make_w1_12_duelling_flint),
    13: ('회천마도총', lambda: load_original_gun(5)),
    14: ('프로스트 레이', make_w1_14_frost_ray),
    15: ('볼틱 블래스터', make_w1_15_voltic_blaster),
    16: ('태양의 총', lambda: load_original_gun(6)),
    17: ('이클립스 라이플', make_w1_17_eclipse_rifle),
    18: ('루미너스 캐넌', make_w1_18_luminous_cannon),
    19: ('헬파이어 건', lambda: load_original_gun(7)),
    20: ('아비스 바주카', make_w1_20_abyss_bazooka),
    21: ('베히모스 런처', make_w1_21_behemoth_launcher),
    22: ('크로스 파이어', lambda: load_original_gun(8)),
    23: ('테스타먼트', make_w1_23_testament),
    24: ('라그나로크', make_w1_24_ragnarok),
    25: ('드래곤 브레스', make_w1_25_dragon_breath),
    26: ('묵시록의 나팔', make_w1_26_apocalypse),
    27: ('레비아탄 하푼', make_w1_27_leviathan),
    28: ('발키리 레일건', make_w1_28_valkyrie),
    29: ('하데스 익스큐셔너', make_w1_29_hades),
    30: ('차원붕괴포', make_w1_30_dimension),
    31: ('슈퍼노바 블래스터', make_w1_31_supernova),
    32: ('천상신의 징벌', make_w1_32_judgment),
    33: ('아스트랄 블래스터', make_w1_33_astral),
    34: ('인피니티 싱귤래리티', make_w1_34_singularity),
    35: ('신살자의 총', make_w1_35_godslayer),
}


def build_all_guns():
    profiles = []
    out_dirs = [RES_DIR, DEBUG_RES_DIR, RELEASE_RES_DIR]
    for d in out_dirs:
        d.mkdir(parents=True, exist_ok=True)

    print(f'Building 35 guns for Diana...')
    for idx in range(1, 36):
        name, builder = BUILDERS[idx]
        res = builder()
        if isinstance(res, tuple):
            im, gx, gy = res
        else:
            im = res.im
            gx = res.grip_x
            gy = res.grip_y

        fn = f'w1_{idx}.png'
        # save to all target dirs
        for d in out_dirs:
            im.save(d / fn)

        profiles.append({
            'id': idx,
            'filename': fn,
            'name': name,
            'width': im.width,
            'height': im.height,
            'grip_x': gx,
            'grip_y': gy,
        })
        print(f'  [{idx:2d}/35] {fn:8s}: {name:16s} ({im.width}x{im.height}) grip=({gx}, {gy})')

    # save profiles json
    profile_path = ROOT / 'content/guns/profiles.json'
    profile_path.parent.mkdir(parents=True, exist_ok=True)
    with open(profile_path, 'w', encoding='utf-8') as f:
        json.dump(profiles, f, ensure_ascii=False, indent=2)
    print(f'Saved profiles to {profile_path}')

    # generate Classes/Data/DianaGunData.h
    header_path = ROOT / 'Classes/Data/DianaGunData.h'
    lines = [
        '#pragma once',
        '// Generated by tools/guns/generate_guns.py.',
        'struct DianaGunInfo {',
        '    int width, height;',
        '    int gripX, gripY;',
        '};',
        '',
        'static const DianaGunInfo kDianaGuns[35] = {'
    ]
    for p in profiles:
        lines.append(f"    {{ {p['width']:2d}, {p['height']:2d}, {p['grip_x']:2d}, {p['grip_y']:2d} }}, // w1_{p['id']}: {p['name']}")
    lines.append('};')
    lines.append('')
    with open(header_path, 'w', encoding='utf-8') as f:
        f.write('\n'.join(lines))
    print(f'Generated {header_path}')


if __name__ == '__main__':
    build_all_guns()
