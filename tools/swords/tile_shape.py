# -*- coding: utf-8 -*-
"""검 그림이 실제로 어느 칸을 쓰는지 재서 가방 모양을 다시 잡는다.

    python tools/swords/tile_shape.py

[왜 재나]

지금 검은 칸을 네모로 잡는다(1x2 / 2x3 / 2x4). 그런데 검은 가늘어서
2 칸 폭을 잡아도 가운데 한 줄만 차고 양옆이 빈다. 가방에서 자리가 곧
값인데, 안 쓰는 자리까지 값을 치르고 있다.

그림을 32 픽셀 칸으로 잘라 칸마다 알파가 얼마나 차 있는지 센다. 거의
빈 칸은 빼면 그만큼 자리가 준다.

[무엇을 내나]

칸마다 찬 비율과, 그걸로 뽑은 모양(GridPart 의 w / h / cells)을 낸다.
cells 는 bit(row * 4 + col) 이고 row 0 이 맨 아랫줄이다 - 그림은 위에서
아래로 읽으므로 뒤집어 적는다.
"""
import glob
import os
import re

import numpy as np
from PIL import Image

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
RES = os.path.join(ROOT, "Resources", "res")
TILE = 32

#이 비율보다 적게 찬 칸은 안 쓰는 것으로 본다. 칼끝이 스치는 정도는
#자리를 내줄 값이 못 된다.
KEEP = 0.06


def tiles(path):
    """칸마다 알파가 찬 비율. 그림 위부터 아래로."""
    a = np.array(Image.open(path).convert("RGBA"))
    h, w, _ = a.shape
    m = a[:, :, 3] > 16
    rows, cols = h // TILE, w // TILE
    return rows, cols, [[m[r * TILE:(r + 1) * TILE, c * TILE:(c + 1) * TILE].mean()
                         for c in range(cols)] for r in range(rows)]


def shrink(rows, cols, cov):
    """쓰는 칸만 남기고 테두리를 깎는다. (w, h, 마스크) 를 낸다."""
    use = [[cov[r][c] >= KEEP for c in range(cols)] for r in range(rows)]

    rs = [r for r in range(rows) if any(use[r])]
    cs = [c for c in range(cols) if any(use[r][c] for r in range(rows))]
    if not rs or not cs:
        return 1, 1, 0

    r0, r1 = min(rs), max(rs)
    c0, c1 = min(cs), max(cs)
    w, h = c1 - c0 + 1, r1 - r0 + 1

    #cells 는 row 0 이 맨 아랫줄이다. 그림의 아래가 row 0 이 되도록 뒤집는다.
    bits = 0
    full = True
    for r in range(r0, r1 + 1):
        for c in range(c0, c1 + 1):
            if use[r][c]:
                bits |= 1 << ((r1 - r) * 4 + (c - c0))
            else:
                full = False

    return w, h, (0 if full else bits)


def art(bits, w, h):
    out = []
    for r in range(h - 1, -1, -1):
        out.append("".join("O" if (bits == 0 or (bits >> (r * 4 + c)) & 1) else "."
                           for c in range(w)))
    return out


def main():
    files = sorted(glob.glob(os.path.join(RES, "w0_*.png")),
                   key=lambda p: int(re.search(r"w0_(\d+)", p).group(1)))

    print("검 그림을 %d 픽셀 칸으로 재서 실제 쓰는 자리를 낸다." % TILE)
    print("(칸이 %d%% 미만 차면 안 쓰는 것으로 본다)\n" % int(KEEP * 100))
    print("%-7s %-9s %-9s %6s  %s" % ("번호", "그림", "지금", "칸수", "실제 모양"))
    print("-" * 64)

    saved = 0
    now = 0
    for p in files:
        n = int(re.search(r"w0_(\d+)", p).group(1))
        if n == 0:
            continue

        rows, cols, cov = tiles(p)
        w, h, bits = shrink(rows, cols, cov)
        cnt = bin(bits).count("1") if bits else w * h

        lines = art(bits, w, h)
        print("%-7d %-9s %-9s %4d칸  %s"
              % (n, "%dx%d" % (cols, rows), "%dx%d" % (cols, rows), cnt, lines[0]))
        for l in lines[1:]:
            print("%-7s %-9s %-9s %6s  %s" % ("", "", "", "", l))

        now += cols * rows
        saved += cols * rows - cnt

    print("-" * 64)
    print("지금 쓰는 칸 합 %d -> 재서 뽑으면 %d  (%d칸, %.0f%% 준다)"
          % (now, now - saved, saved, saved * 100.0 / max(1, now)))


main()
