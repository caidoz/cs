# -*- coding: utf-8 -*-
"""성 단계별 가방 테두리를 그린다. Resources/res/grid0 ~ grid9.

    python tools/bag/build_frames.py

grid0 이 1 단계다. 성 번호(0~9)와 짝을 맞춘 것이다.

칸 배치는 Classes/Data/CastleData.cpp 의 castleGridCell 표를 그대로 읽는다.
표가 곧 게임이 쓰는 모양이므로, 표를 고치면 그림도 같이 바뀐다 - 손으로
그려 두면 표와 어긋난다.

[무엇을 그리나]
  1 칸 안쪽   어두운 남색. 위가 조금 밝다.
  2 격자선    칸과 칸 사이에 가는 청록 선.
  3 매듭      격자가 만나는 자리의 작은 밝은 네모.
  4 바깥 테   실루엣을 따라 도는 두꺼운 테. 바깥은 어둡고 안쪽이 밝다.
  5 총안      위가 뚫린 칸마다 얹는 작은 돌기. 성벽처럼 보이게 한다.
  6 발광      밝은 것들만 흐려 겹친다.

[왜 그림 한 장을 늘이지 않나]
단계마다 칸 수도 모양도 다르다. 4x4 짜리 한 장을 12x5 로 늘이면 선 굵기와
매듭 크기가 같이 늘어나 다른 물건이 된다. 조각을 제자리에 찍는 편이 맞다.
"""
import io
import os
import re
import numpy as np
from PIL import Image, ImageDraw, ImageFilter

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SRC = os.path.join(ROOT, "Classes", "Data", "CastleData.cpp")
#res 폴더에 평평하게 넣는다. 성 번호와 짝이라 grid0 이 1 단계다.
OUT = os.path.join(ROOT, "Resources", "res")
SHEET = os.path.join(ROOT, "output", "bag_frames")

CELL = 64          # 칸 한 변
RIM = 22           # 바깥 테 두께
MERLON = 20        # 총안 돌기 높이
MERLON_W = 26      # 총안 돌기 폭
LINE = 3           # 격자선 굵기
NODE = 17          # 매듭 한 변

C_CELL_TOP = (22, 62, 122, 255)
C_CELL_BOT = (12, 36, 82, 255)
C_RIM_EDGE = (16, 92, 196, 255)   # 테 바깥 테두리
C_RIM_MID = (38, 140, 240, 255)   # 테 몸통
C_RIM_IN = (186, 236, 255, 255)   # 테 안쪽 밝은 선
C_LINE = (150, 224, 255, 255)
C_NODE = (238, 252, 255, 255)
C_GLOW = (80, 190, 255, 255)


def read_cells():
    """castleGridCell 표를 성마다의 칸 목록으로 편다."""
    s = open(SRC, encoding="utf-8-sig", errors="replace").read()
    body = s.split("static const signed char castleGridCell_builtin[] = {", 1)[1]
    body = body.split("\n};", 1)[0]
    nums = [int(v) for v in re.findall(r"-?\d+", re.sub(r"//[^\n]*", "", body))]

    def arr(name):
        t = s.split("const int %s[TOTALCASTLE] = {" % name, 1)[1].split("};", 1)[0]
        return [int(v) for v in re.findall(r"-?\d+", re.sub(r"//[^\n]*", "", t))]

    cnt, start = arr("castleGridCellCnt"), arr("castleGridCellStart")
    out = []
    for c in range(10):
        pts = [(nums[(start[c] + i) * 2], nums[(start[c] + i) * 2 + 1])
               for i in range(cnt[c])]
        out.append([p for p in pts if 0 <= p[0] < 12 and 0 <= p[1] < 6])
    return out


def build(cells):
    """칸 목록 하나를 그림 한 장으로."""
    W = max(p[0] for p in cells) + 1
    H = max(p[1] for p in cells) + 1
    pad = RIM + MERLON + 8
    im = Image.new("RGBA", (W * CELL + pad * 2, H * CELL + pad * 2), (0, 0, 0, 0))
    d = ImageDraw.Draw(im)

    #표의 행 0 은 맨 아랫줄이다. 그림은 위에서 아래로 그리므로 뒤집는다.
    filled = set((x, H - 1 - y) for x, y in cells)

    def box(cx, cy, grow=0):
        x = pad + cx * CELL - grow
        y = pad + cy * CELL - grow
        return [x, y, x + CELL + grow * 2, y + CELL + grow * 2]

    #---- 바깥 테. 칸마다 키운 네모를 겹쳐 실루엣을 만든다.
    #     바깥 -> 몸통 -> 안쪽 밝은 선 차례로 덮어 두께를 낸다 ----
    for grow, c in ((RIM, C_RIM_EDGE), (RIM - 4, C_RIM_MID), (6, C_RIM_IN)):
        for cx, cy in filled:
            d.rectangle(box(cx, cy, grow), fill=c)

    #---- 총안. 위가 뚫린 칸마다 한가운데에, 테 위로 솟게 얹는다.
    #     테와 같은 세 겹이라 한 덩어리로 읽힌다 ----
    for cx, cy in filled:
        if (cx, cy - 1) in filled:
            continue
        x0, y0, x1, _ = box(cx, cy, RIM)
        mx = (x0 + x1) // 2
        for inset, c in ((0, C_RIM_EDGE), (4, C_RIM_MID), (9, C_RIM_IN)):
            d.rectangle([mx - MERLON_W // 2 + inset, y0 - MERLON + inset,
                         mx + MERLON_W // 2 - inset, y0 + 12], fill=c)

    #---- 칸 안쪽 ----
    for cx, cy in filled:
        x0, y0, x1, y1 = box(cx, cy)
        for i in range(CELL):
            t = i / float(CELL - 1)
            c = tuple(int(C_CELL_TOP[k] * (1 - t) + C_CELL_BOT[k] * t) for k in range(4))
            d.line([x0, y0 + i, x1, y0 + i], fill=c)

    #---- 격자선. 칸과 칸이 맞닿은 자리에만 ----
    for cx, cy in filled:
        x0, y0, x1, y1 = box(cx, cy)
        d.rectangle([x0, y0, x1, y0 + LINE], fill=C_LINE)
        d.rectangle([x0, y1 - LINE, x1, y1], fill=C_LINE)
        d.rectangle([x0, y0, x0 + LINE, y1], fill=C_LINE)
        d.rectangle([x1 - LINE, y0, x1, y1], fill=C_LINE)

    #---- 매듭. 칸에 닿은 격자점마다 ----
    for gx in range(W + 1):
        for gy in range(H + 1):
            if not any((gx + dx, gy + dy) in filled
                       for dx in (-1, 0) for dy in (-1, 0)):
                continue
            x = pad + gx * CELL
            y = pad + gy * CELL
            #어두운 테를 두르고 속을 밝게 채운다. 격자선 위에 그대로
            #얹으면 선에 묻혀 매듭으로 안 보인다.
            h = NODE // 2
            d.rectangle([x - h, y - h, x + h, y + h], fill=(10, 44, 104, 255))
            d.rectangle([x - h + 2, y - h + 2, x + h - 2, y + h - 2], fill=C_RIM_IN)
            d.rectangle([x - h + 5, y - h + 5, x + h - 5, y + h - 5], fill=C_NODE)

    #---- 발광. 밝은 것만 남겨 흐린 뒤 밑에도 깔고 위에도 옅게 얹는다.
    #     밑에만 깔면 테 바깥으로만 번지고, 위에만 얹으면 선이 뭉갠다 ----
    a = np.array(im).astype(np.float32)
    lum = a[:, :, :3].max(2) * (a[:, :, 3] / 255.0)

    def haze(thr, mul, blur, cap):
        g = np.zeros_like(a)
        g[:, :, :3] = C_GLOW[:3]
        g[:, :, 3] = np.clip((lum - thr) * mul, 0, cap)
        return Image.fromarray(g.astype(np.uint8), "RGBA").filter(
            ImageFilter.GaussianBlur(blur))

    out = Image.alpha_composite(haze(120, 2.2, 18, 255), haze(120, 2.2, 7, 255))
    out = Image.alpha_composite(out, im)
    out = Image.alpha_composite(out, haze(190, 1.4, 5, 110))
    return out


def write_metrics():
    """게임이 그림을 칸에 맞춰 놓으려면 칸 간격과 여백을 알아야 한다.
    숫자를 코드에 따로 적어 두면 여기를 고칠 때 어긋나므로 같이 낸다."""
    pad = RIM + MERLON + 8
    lines = [
        "// tools/bag/build_frames.py 가 낸다. 손으로 고치지 않는다.",
        "// 그림 안에서 칸 하나는 %d 픽셀이고, 칸 바깥 여백이 %d 픽셀이다." % (CELL, pad),
        "enum { GRID_FRAME_CELL = %d, GRID_FRAME_PAD = %d };" % (CELL, pad),
        "",
    ]
    out = os.path.join(ROOT, "Classes", "GridFrameMetrics.inc")
    io.open(out, "w", encoding="utf-8", newline="\n").write("\n".join(lines))
    print("Classes/GridFrameMetrics.inc  칸 %d  여백 %d" % (CELL, pad))


def main():
    os.makedirs(OUT, exist_ok=True)
    write_metrics()
    for i, cells in enumerate(read_cells()):
        im = build(cells)
        p = os.path.join(OUT, "grid%d.png" % i)
        im.save(p)
        print("%s  %dx%d  %d칸" % (os.path.basename(p), im.width, im.height, len(cells)))


main()
