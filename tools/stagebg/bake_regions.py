# -*- coding: utf-8 -*-
"""성열차가 달리는 지역의 배경 레이어를 게임 리소스로 굽는다.

    python tools/stagebg/bake_regions.py

원본은 바탕화면 layer 폴더다. 지역마다 layout.json + assets 한 벌이고,
거기서 정한 값을 그대로 쓴다. 지역이 늘면 아래 REGIONS 에 한 줄 더한다.
게임 쪽 조립 규칙은 Classes/StageBackground.h 에 있다.

[무엇을 구워 넣나]

프리뷰는 캔버스에서 매 프레임 합성한다 - 보스에 대기색을 얹고 밑동을
알파로 지우고, 선로 지지대 끝도 지운다. 게임 쪽 DrawImage 에는 그런 것이
없으므로 PNG 에 미리 넣는다. 매 프레임 하던 일이 아니라 늘 같은 결과라서
구워도 손해가 없다.

[보스 연출은 두 장으로 만든다]

늪지대 개구리는 눈을 감았다 뜨고, 금단의 계곡 웜은 눈이 밝아졌다 어두워
진다. 둘 다 '평소' 한 장과 '연출' 한 장을 겹쳐 내면 된다 -
  감는 쪽(swap)  : 연출 장을 통째로 바꿔 그린다.
  밝아지는 쪽(glow): 연출 장을 평소 장 위에 옅게서 진하게 얹는다.
연출 장은 달라지는 자리(눈)만 남기고 다 지운다. 그래야 옅게 얹었을 때
몸통까지 같이 흐려지지 않는다.

[선로는 잘라서 내보낸다]

원본은 양끝에 여백이 있어 그대로 반복하면 이음새가 보인다. layout.json 이
정한 사각형(200,0,1800,724)만 잘라 낸다. 잘린 두 끝은 서로 같은 모양이라
좌우 반전 교대로 이으면 딱 맞는다.

[해상도]

설계 폭 1088 의 0.75 로 내보낸다. 화면 폭이 640 이고 원경은 가장 크게
잡아야 736 폭이라, 0.75(816) 면 늘 줄여 그리게 된다. 늘려 그리면 뭉갠다.
"""
import json
import os
import numpy as np
from PIL import Image, ImageDraw

SRC = r"C:\Users\polyp\Desktop\layer"
RES = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(
    os.path.abspath(__file__)))), "Resources", "res")

EXPORT = 0.75      # 설계 크기 대비 내보내는 배율

# (폴더, 파일 이름 앞머리, 보스 연출)
REGIONS = [
    ("늪지대",                            "bg1", "swap"),
    ("금단의계곡(forbidden_valley_layers)", "bg2", "glow"),
]

# 연출 장을 만드는 법. 프리뷰(preview.html)의 makeFrog 와 같은 값이다.
SWAP_EYES = {   # 감은 그림으로 갈아 끼울 타원 (cx, cy, rx, ry)
    "bg1": [(210, 473, 64, 64), (636, 409, 100, 83)],
}
GLOW = {        # 발광 원 (cx, cy, r) 과 안팎 색
    "bg2": {"circles": [(324, 241, 38), (514, 342, 43)],
            "inner": (230, 255, 145, 0.6), "outer": (170, 255, 40, 0.0),
            #프리뷰가 발광을 오려 내는 타원. 여기 바깥은 평소 그림 그대로다.
            "clip": [(324, 241, 40, 40), (514, 342, 45, 45)]},
}
TINT = {"bg1": 0.25, "bg2": 0.32}   # 보스에 얹는 대기색 비율


def out(name, im):
    im.save(os.path.join(RES, name))
    print("%-20s %dx%d" % (name, im.width, im.height))


def sized(w, h):
    return (max(1, int(round(w * EXPORT))), max(1, int(round(h * EXPORT))))


def hexcol(s):
    return tuple(int(s[i:i + 2], 16) for i in (1, 3, 5))


def fade_alpha(a, y0, y1):
    """y0 에서 1, y1 에서 0 으로 알파를 깎는다. 자른 단면을 안개에 묻는다."""
    y = np.arange(a.shape[0], dtype=np.float32)
    f = np.clip((y1 - y) / float(y1 - y0), 0.0, 1.0)
    a[:, :, 3] = (a[:, :, 3].astype(np.float32) * f[:, None]).astype(np.uint8)
    return a


def ellipse_mask(size, shapes):
    m = Image.new("L", size, 0)
    d = ImageDraw.Draw(m)
    for cx, cy, rx, ry in shapes:
        d.ellipse((cx - rx, cy - ry, cx + rx, cy + ry), fill=255)
    return m


def tinted(im, abyss, ratio):
    a = np.array(im).astype(np.float32)
    for c in range(3):
        a[:, :, c] = a[:, :, c] * (1 - ratio) + abyss[c] * ratio
    return a.astype(np.uint8)


def bake_sky(lay, key, pre, name):
    """원경과 중경. 원경만 아래쪽을 심연색으로 녹인다.

    프리뷰는 원경을 깔고 그 위에 그라디언트를 덮는데, 원경 말고는 덮이는
    것이 없으니 그림에 섞어 두면 결과가 같다."""
    d = lay[key]
    im = Image.open(os.path.join(SRC, d["file"])).convert("RGBA")
    if "fadeY" in d:
        y0, y1 = d["fadeY"]
        a = np.array(im).astype(np.float32)
        t = np.clip((np.arange(im.height, dtype=np.float32) - y0) /
                    float(y1 - y0), 0.0, 1.0)[:, None]
        ab = hexcol(lay["abyssColor"])
        for c in range(3):
            a[:, :, c] = a[:, :, c] * (1 - t) + ab[c] * t
        im = Image.fromarray(a.astype(np.uint8), "RGBA")
    out("%s_%s.png" % (pre, name), im.resize(sized(*d["displaySize"]), Image.LANCZOS))


def bake_rail(lay, pre):
    r = lay["rail"]
    x, y, w, h = r["sourceRect"]
    im = Image.open(os.path.join(SRC, r["file"])).convert("RGBA").crop((x, y, x + w, y + h))
    im = Image.fromarray(fade_alpha(np.array(im), *r["alphaFadeSourceY"]), "RGBA")
    out("%s_rail.png" % pre, im.resize(sized(*r["displaySize"]), Image.LANCZOS))


def bake_boss(lay, pre, fx):
    b = lay["boss"]
    ab = hexcol(lay["abyssColor"])
    base = Image.open(os.path.join(SRC, b["file"])).convert("RGBA")

    def finish(im):
        return Image.fromarray(fade_alpha(tinted(im, ab, TINT[pre]),
                                          *b["alphaFadeSourceY"]), "RGBA")

    out("%s_boss.png" % pre, finish(base).resize(sized(*b["size"]), Image.LANCZOS))

    if fx == "swap":
        #눈 타원 안쪽만 감은 그림으로 바꾼다. 꽃과 몸통은 그대로 둔다.
        blink = Image.open(os.path.join(SRC, b["blinkFile"])).convert("RGBA")
        im = base.copy()
        im.paste(blink, (0, 0), ellipse_mask(im.size, SWAP_EYES[pre]))
        im = finish(im)
    else:
        g = GLOW[pre]
        lit = base.copy()
        halo = Image.new("RGBA", lit.size, (0, 0, 0, 0))
        hd = ImageDraw.Draw(halo)
        ir, ig, ib, ia = g["inner"]
        orr, og, ob, oa = g["outer"]
        for cx, cy, r in g["circles"]:
            #바깥에서 안쪽으로 한 겹씩 채워 방사 그라디언트를 만든다.
            for k in range(r, 0, -1):
                t = k / float(r)
                col = (int(orr * t + ir * (1 - t)), int(og * t + ig * (1 - t)),
                       int(ob * t + ib * (1 - t)),
                       int(255 * (oa * t + ia * (1 - t))))
                hd.ellipse((cx - k, cy - k, cx + k, cy + k), fill=col)
        #source-atop - 몸 위에만 얹는다. 허공으로 새어 나가지 않는다.
        lit.alpha_composite(Image.composite(
            halo, Image.new("RGBA", lit.size, (0, 0, 0, 0)),
            Image.fromarray(np.array(lit)[:, :, 3])))
        #달라진 자리(눈)만 남긴다. 나머지는 평소 그림과 같으므로 지운다.
        im = finish(lit)
        keep = np.array(im)
        keep[:, :, 3] = (keep[:, :, 3].astype(np.float32) *
                         (np.array(ellipse_mask(im.size, g["clip"]))
                          .astype(np.float32) / 255.0)).astype(np.uint8)
        im = Image.fromarray(keep, "RGBA")

    out("%s_boss_fx.png" % pre, im.resize(sized(*b["size"]), Image.LANCZOS))


def main():
    for folder, pre, fx in REGIONS:
        lay = json.load(open(os.path.join(SRC, folder, "layout.json"), encoding="utf-8"))
        #layout 안의 경로는 그 지역 폴더 기준이다.
        for k in ("far", "mid", "rail", "boss"):
            lay[k]["file"] = os.path.join(folder, lay[k]["file"])
            if "blinkFile" in lay[k]:
                lay[k]["blinkFile"] = os.path.join(folder, lay[k]["blinkFile"])
        print("--", pre, folder)
        bake_sky(lay, "far", pre, "far")
        bake_sky(lay, "mid", pre, "mid")
        bake_rail(lay, pre)
        bake_boss(lay, pre, fx)


main()
