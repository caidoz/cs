# -*- coding: utf-8 -*-
"""조립표대로 성을 그려 본다. 고치고 -> 돌리고 -> 보고 를 빠르게 돌리는 용도.

    python tools/castles/preview_castle.py

content/castles/tier01_layout.json 의 s / dx / dy 를 고친 뒤 이걸 돌리면
output/castle-v3/_preview.png 가 다시 나온다. 게임도 같은 값을 쓴다
(install_sheet_v3.py 가 그 값으로 조립표를 낸다).
"""
import json
import os
from PIL import Image, ImageDraw, ImageFont

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
LAYOUT = os.path.join(ROOT, "content", "castles", "tier01_layout.json")
RES = os.path.join(ROOT, "Resources", "res")
OUT = os.path.join(ROOT, "output", "castle-v3")
SHEETREF = os.path.join(OUT, "ref_%d.png")

FILE = {"body": "castle_body", "gun": "castle_gun", "roof": "castle_roof",
        "wall": "castle_wall", "wheel": "castle_base", "wheel2": "castle_base"}
#깃발은 성벽 뒤다. 게임 쪽도 성벽 그림에 그렇게 구워 넣는다.
ORDER = ["roof", "flag", "wall", "body", "gun", "wheel", "wheel2"]

#깃발은 res 에 따로 없고 성벽 그림에 구워 넣는다. 미리보기는 시트에서
#바로 떠서 보여 준다.
FLAG = os.path.join(ROOT, "output", "castle-v3", "flag_1.png")


def load(part, lv):
    return Image.open(os.path.join(RES, "%s%d.png" % (FILE[part], lv))).convert("RGBA")


def build(lay, lv):
    """합성본 좌상단(0,0) 기준으로 조각을 얹는다. y 는 아래로 +."""
    W, H = lay["size"]
    out = Image.new("RGBA", (W, H), (0, 0, 0, 0))

    for p in ORDER:
        if p not in lay:
            continue
        d = lay[p]
        im = Image.open(FLAG).convert("RGBA") if p == "flag" else load(p, lv)
        z = float(d.get("zoom", 1.0))
        if z != 1.0:
            im = im.resize((max(1, int(round(im.width * z))),
                            max(1, int(round(im.height * z)))), Image.LANCZOS)
        out.alpha_composite(im, (int(d["x"]), int(d["y"])))

    return out


def main():
    lay = json.load(open(LAYOUT, encoding="utf-8"))
    cells = []
    for lv in range(1, 6):
        made = build(lay[str(lv)], lv)
        ref = None
        if os.path.exists(SHEETREF % lv):
            ref = Image.open(SHEETREF % lv).convert("RGBA")
        w = made.width + (ref.width + 16 if ref else 0)
        h = max(made.height, ref.height if ref else 0) + 26
        c = Image.new("RGBA", (w, h), (250, 250, 250, 255))
        c.alpha_composite(made, (0, h - made.height))
        if ref:
            c.alpha_composite(ref, (made.width + 16, h - ref.height))
        cells.append(c)

    W = sum(c.width + 14 for c in cells)
    H = max(c.height for c in cells) + 26
    o = Image.new("RGBA", (W, H), (250, 250, 250, 255))
    d = ImageDraw.Draw(o)
    try:
        f = ImageFont.truetype(r"C:\Windows\Fonts\arialbd.ttf", 17)
    except Exception:
        f = ImageFont.load_default()
    x = 0
    for i, c in enumerate(cells):
        o.alpha_composite(c, (x, 26))
        d.text((x + 6, 4), "Lv%d  조립 | 원본" % (i + 1), font=f, fill=(20, 20, 20, 255))
        x += c.width + 14

    os.makedirs(OUT, exist_ok=True)
    o.convert("RGB").save(os.path.join(OUT, "_preview.png"))
    print("output/castle-v3/_preview.png")


main()
