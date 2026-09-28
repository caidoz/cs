# -*- coding: utf-8 -*-
"""성 1 파츠 시트를 잘라 res 에 넣고 조립표를 낸다.

    python tools/castles/install_sheet_v3.py

[시트]

다섯 단계 x 여섯 종(지붕·첨탑 / 상단 성벽 / 실내 / 포대 / 차체 프레임 /
바퀴) 에 공용 깃발 한 장이다. 맨 윗줄 완성도는 눈으로 맞출 때 보는 것이고
잘라 쓰지 않는다.

[조각과 완성도는 픽셀이 다르다]

완성도에 맞춰 자리를 자동으로 찾으려 여러 번 해 봤고 안 된다. 따로 그린
그림이라 실루엣도 색도 맞지 않는다 - 좌우 바퀴가 같은 자리로 나오고,
배율까지 같이 찾게 하면 작게 줄여 빈 곳에 숨는 쪽이 이긴다.

그래서 그림에서 잴 수 있는 것만 잰다. 차체 프레임 양 끝 결합함의 가운데가
바퀴 축이다. 나머지 물림 깊이는 완성도와 나란히 놓고 맞춘 값이다.

[여섯 종을 다섯 자리에]

이미지 번호(MODCASTLE_*)가 스물다섯 개다. 늘 붙어 다니는 것끼리 묶는다.

    armor    <- 실내 + 차체   castle_body1..5
    cannon   <- 포대          castle_gun1..5
    wheel    <- 바퀴          castle_base1..5   (한 장을 두 번 그려 돌린다)
    spire    <- 지붕·첨탑     castle_roof1..5
    interior <- 성벽 + 깃발   castle_wall1..5

차체를 실내에 구워 붙인 것은, 한 그림을 한 프레임에 세 번 서로 다른 조각
사각형으로 그리는 구조를 없애려는 것이다. 차체는 돌지도 따로 움직이지도
않으므로 굽는다고 잃는 것이 없고, 대신 바퀴가 제 칸을 갖는다.
"""
import json
import os
import numpy as np
from PIL import Image

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SHEET = os.path.join(ROOT, "content", "castles", "tier01_sheet_v3.png")
RES = os.path.join(ROOT, "Resources", "res")
HDR = os.path.join(ROOT, "Classes", "CastleModularAssets.h")

#자리와 배율은 이 파일이 정한다. 손으로 고치고 preview_castle.py 로 본다.
LAYOUT = os.path.join(ROOT, "content", "castles", "tier01_layout.json")

COLS = [(140, 375), (376, 655), (656, 945), (946, 1235), (1236, 1535)]
#맨 윗줄 완성도는 잘라 쓰지 않지만, 지붕의 위쪽 경계를 잡으려면 있어야 한다.
BANDS = {"castle": (4, 360), "roof": (361, 467), "wall": (468, 563), "body": (564, 658),
         "gun": (659, 749), "base": (750, 834), "wheel": (835, 922),
         "flag": (923, 1019)}

#---- 물림. 완성도와 나란히 놓고 맞춘 값이다 ----
BODY_ON_BASE = 10    #실내가 차체 위로 내려앉는 깊이
WALL_ON_BODY = 6     #성벽이 실내 위로
ROOF_IN_WALL = 0.55  #지붕 밑동이 성벽 높이의 이만큼 안으로
FLAG_IN_WALL = 0.35  #깃대 밑동
FLAG_X = 0.62        #깃대 왼쪽 끝(차체 폭 대비)
GUN_Y = 0.46         #포신 가운데가 실내 높이의 어디쯤
WHEEL_DROP = 0.55    #바퀴 가운데가 차체 높이의 어디쯤

NAME = {"armor": "castle_body", "cannon": "castle_gun", "wheel": "castle_base",
        "spire": "castle_roof", "interior": "castle_wall"}


def main():
    a = np.array(Image.open(SHEET).convert("RGBA"))
    m = a[:, :, 3] > 128

    def label(mask):
        """이어진 덩어리에 번호를 매긴다. 여덟 방향."""
        h, w = mask.shape
        lab = np.zeros((h, w), np.int32)
        par = [0]

        def find(x):
            while par[x] != x:
                par[x] = par[par[x]]
                x = par[x]
            return x

        nxt = 1
        for y in range(h):
            prev = lab[y - 1] if y else None
            for x in np.nonzero(mask[y])[0]:
                near = []
                if x and lab[y][x - 1]:
                    near.append(lab[y][x - 1])
                if prev is not None:
                    for d in (-1, 0, 1):
                        xx = x + d
                        if 0 <= xx < w and prev[xx]:
                            near.append(prev[xx])
                if near:
                    mn = min(near)
                    lab[y][x] = mn
                    for n in near:
                        ra, rb = find(mn), find(n)
                        if ra != rb:
                            par[max(ra, rb)] = min(ra, rb)
                else:
                    lab[y][x] = nxt
                    par.append(nxt)
                    nxt += 1

        remap = np.array([find(i) for i in range(max(1, nxt))])
        return remap[lab]

    #열마다 한 번만 덩어리를 매겨 두고 모든 행이 나눠 쓴다.
    strips = {}
    cuts = {}

    def strip(ci):
        if ci not in strips:
            x0, x1 = COLS[ci]
            strips[ci] = label(m[:, x0:x1 + 1])
        return strips[ci]

    def cutlines(ci):
        """행과 행 사이를 그 열에서 가장 얇은 줄로 가른다.

        행 경계는 왼쪽 라벨 자리로 어림잡은 값이라 조각과 어긋난다. 바퀴는
        띠보다 커서 위아래가 깎였고, 5단은 지붕과 성벽이 닿아 있어 한
        덩어리로 읽혔다. 경계 언저리에서 픽셀이 가장 적은 줄을 찾아 거기서
        가르면 둘 다 해결된다.
        """
        if ci in cuts:
            return cuts[ci]

        x0, x1 = COLS[ci]
        prof = m[:, x0:x1 + 1].sum(1)
        order = ["castle", "roof", "wall", "body", "gun", "base", "wheel", "flag"]
        line = {}

        for i in range(len(order) - 1):
            edge = (BANDS[order[i]][1] + BANDS[order[i + 1]][0]) // 2
            lo, hi = max(0, edge - 34), min(len(prof) - 1, edge + 34)
            win = prof[lo:hi + 1]
            line[order[i]] = lo + int(np.argmin(win))

        cuts[ci] = line
        return line

    def cut(band, ci):
        """그 칸의 조각을 가져온다. 위아래는 가장 얇은 줄에서 가른다."""
        x0, x1 = COLS[ci]
        lab = strip(ci)
        line = cutlines(ci)
        order = ["castle", "roof", "wall", "body", "gun", "base", "wheel", "flag"]
        k = order.index(band)

        top = line[order[k - 1]] + 1 if k > 0 else 0
        bot = line[band] if band in line else lab.shape[0] - 1

        own = np.zeros(lab.shape, bool)
        own[top:bot + 1] = lab[top:bot + 1] > 0

        #얼룩 버리기. 시트에는 조각 둘레에 점이나 작은 세모 같은 표식이
        #흩어져 있어, 그대로 두면 경계가 그만큼 부푼다.
        sub = np.where(own, lab, 0)
        ids, cnt = np.unique(sub[sub > 0], return_counts=True)
        if len(ids) == 0:
            raise SystemExit("빈 칸: %s 열%d" % (band, ci + 1))
        keep = ids[cnt >= cnt.max() * 0.02]
        own = own & np.isin(lab, keep)

        ys = np.nonzero(own.sum(1))[0]
        xs = np.nonzero(own.sum(0))[0]
        py0, py1 = int(ys.min()), int(ys.max())
        px0, px1 = int(xs.min()), int(xs.max())

        piece = a[py0:py1 + 1, x0 + px0:x0 + px1 + 1].copy()
        piece[:, :, 3] = np.where(own[py0:py1 + 1, px0:px1 + 1], piece[:, :, 3], 0)
        return Image.fromarray(piece)

    def hubs(base):
        b = np.array(base)[:, :, 3] > 128
        h, w = b.shape
        tall = b.sum(0) > h * 0.80
        runs, s = [], None
        for i, v in enumerate(tall):
            if v and s is None:
                s = i
            if (not v or i == len(tall) - 1) and s is not None:
                runs.append((s, i))
                s = None
        runs = [r for r in runs if r[1] - r[0] > 8]
        if len(runs) < 2:
            return [int(w * 0.18), int(w * 0.82)]
        return [(runs[0][0] + runs[0][1]) // 2, (runs[-1][0] + runs[-1][1]) // 2]

    lay = json.load(open(LAYOUT, encoding="utf-8"))
    flag = cut("flag", 0)   #깃발은 공용 한 장이다
    packs, box, whole = {}, {}, {}

    for ci in range(5):
        lv = ci + 1
        bs = cut("base", ci)
        bd = cut("body", ci)
        wa = cut("wall", ci)
        rf = cut("roof", ci)
        gn = cut("gun", ci)
        wh = cut("wheel", ci)

        #자리와 배율은 조립표가 정한다. 눈으로 맞춘 값을 코드에 박아 두면
        #고칠 때마다 빌드해야 하고, 무엇을 얼마나 바꿨는지도 안 남는다.
        L = lay[str(lv)]

        def place(key, im):
            d = L[key]
            k = float(d.get("s", 1.0))
            if k != 1.0:
                im = im.resize((max(1, int(im.width * k)),
                                max(1, int(im.height * k))), Image.LANCZOS)
            return (int(d["dx"]), int(d["dy"]), im)

        pos = {
            "body": place("body", bd),
            "gun": place("gun", gn),
            "wall": place("wall", wa),
            "roof": place("roof", rf),
            "wheelL": place("wheel", wh),
            "wheelR": place("wheel2", wh),
        }

        bs = None   #차체는 이제 실내 조각에 함께 들어 있다

        x0 = min(p[0] for p in pos.values())
        y0 = min(p[1] for p in pos.values())
        x1 = max(p[0] + p[2].width for p in pos.values())
        y1 = max(p[1] + p[2].height for p in pos.values())
        box[lv] = (x0, y0, x1 - x0, y1 - y0)

        #성 한 채를 통째로. 증축 그림이 이걸 쓴다.
        full = Image.new("RGBA", (x1 - x0, y1 - y0), (0, 0, 0, 0))
        for k in ("roof", "wall", "body", "gun", "wheelL", "wheelR"):
            dx, dy, im = pos[k]
            full.alpha_composite(im, (dx - x0, dy - y0))
        whole[lv] = full

        def save(slot, im, dx, dy, extra=None, rect=None):
            im.save(os.path.join(RES, "%s%d.png" % (NAME[slot], lv)))
            x, y, w, h = rect or (0, 0, im.width, im.height)
            packs.setdefault(slot, {})[lv] = dict(
                x=x, y=y, w=w, h=h, dx=dx, dy=dy, extra=extra or [])

        save("armor", pos["body"][2], pos["body"][0], pos["body"][1])
        save("cannon", pos["gun"][2], pos["gun"][0], pos["gun"][1])
        save("spire", pos["roof"][2], pos["roof"][0], pos["roof"][1])

        #성벽 + 깃발을 한 장으로. 깃발은 제 칸이 없어서 성벽에 굽는다 -
        #둘의 자리 차이는 조립표가 정하고 그림 안에 담긴다.
        if "flag" in L:
            fx, fy, fim = place("flag", flag)
            wx, wy, wim = pos["wall"]
            mx, my = min(wx, fx), min(wy, fy)
            mw = max(wx + wim.width, fx + fim.width) - mx
            mh = max(wy + wim.height, fy + fim.height) - my
            merged = Image.new("RGBA", (mw, mh), (0, 0, 0, 0))
            merged.alpha_composite(fim, (fx - mx, fy - my))
            merged.alpha_composite(wim, (wx - mx, wy - my))
            pos["wall"] = (mx, my, merged)

        save("interior", pos["wall"][2], pos["wall"][0], pos["wall"][1])

        #바퀴는 제 칸을 쓴다. 한 장을 두 자리에 그려 돌린다 - 같은 조각
        #사각형이라 한 프레임에 두 번 그려도 서로 어긋날 일이 없다.
        save("wheel", pos["wheelL"][2], pos["wheelL"][0], pos["wheelL"][1], extra=[
            dict(x=0, y=0, w=pos["wheelR"][2].width, h=pos["wheelR"][2].height,
                 dx=pos["wheelR"][0], dy=pos["wheelR"][1]),
        ])

    #---- 조립표 ----
    L = ["#pragma once",
         "// Generated by tools/castles/install_sheet_v3.py",
         "//",
         "// dx,dy place a piece against the castle's own origin: dx right from the",
         "// chassis's left edge, dy up from the ground, so dy is negative.",
         "//",
         "// armor carries the deck: the room with the chassis frame baked under it.",
         "// wheel is one wheel; sub[0] is where the second copy goes.  Both spin.",
         "//",
         "// kBox is what the whole castle takes up, so the viewer can size it to the",
         "// screen instead of carrying a hand-picked zoom.",
         "namespace CastleParts {",
         "struct Sub { int x,y,w,h; int dx,dy; };",
         "struct Asset { int x,y,w,h; int dx,dy; int nsub; Sub sub[2]; };",
         "struct Box { int x,y,w,h; };",
         "static const Asset kAssets[5][5] = {"]

    for slot in ("armor", "cannon", "wheel", "spire", "interior"):
        L.append("  { // %s  (%s)" % (slot, NAME[slot]))
        for lv in range(1, 6):
            p = packs[slot][lv]
            subs = p["extra"]
            row = "{%d,%d,%d,%d,%d,%d,%d,{" % (p["x"], p["y"], p["w"], p["h"],
                                               p["dx"], p["dy"], len(subs))
            row += ",".join("{%d,%d,%d,%d,%d,%d}" % (s["x"], s["y"], s["w"], s["h"],
                                                     s["dx"], s["dy"]) for s in subs)
            if len(subs) < 2:
                row += ("," if subs else "") + ",".join(["{0,0,0,0,0,0}"] * (2 - len(subs)))
            L.append("    " + row + "}},")
        L.append("  },")

    L.append("};")
    L.append("static const Box kBox[5] = {")
    for lv in range(1, 6):
        L.append("  {%d,%d,%d,%d}," % box[lv])
    L.append("};")
    L.append("}")

    with open(HDR, "w", encoding="utf-8", newline="") as f:
        f.write("\n".join(L) + "\n")

    for lv in range(1, 6):
        print("Lv%d 성 %dx%d" % (lv, box[lv][2], box[lv][3]))


main()
