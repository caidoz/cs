# -*- coding: utf-8 -*-
"""UI 아틀라스에서 조각들의 사각형을 찾아 준다.

    python tools/ui/atlas_rects.py slot win

알파가 이어진 덩어리를 하나씩 끊어 좌표와 크기를 낸다. 코드에 넣을
DrawImage(w, h, xs, ys, ...) 의 네 수를 그대로 쓸 수 있다.

눈대중으로 자르면 한두 픽셀이 어긋나 테두리에 선이 생긴다.
"""
import os
import sys

import numpy as np
from PIL import Image

RES = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(
    os.path.abspath(__file__)))), "Resources", "res")


def blobs(mask):
    """이어진 덩어리를 훑는다. 재귀 대신 스택 - 1024 짜리에서 터진다."""
    h, w = mask.shape
    seen = np.zeros_like(mask, dtype=bool)
    out = []
    for sy in range(h):
        for sx in range(w):
            if not mask[sy, sx] or seen[sy, sx]:
                continue
            x0 = x1 = sx
            y0 = y1 = sy
            n = 0
            stack = [(sy, sx)]
            seen[sy, sx] = True
            while stack:
                y, x = stack.pop()
                n += 1
                x0 = min(x0, x); x1 = max(x1, x)
                y0 = min(y0, y); y1 = max(y1, y)
                for dy, dx in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                    ny, nx = y + dy, x + dx
                    if 0 <= ny < h and 0 <= nx < w and mask[ny, nx] and not seen[ny, nx]:
                        seen[ny, nx] = True
                        stack.append((ny, nx))
            if n >= 400:   #먼지는 버린다
                out.append((x0, y0, x1 - x0 + 1, y1 - y0 + 1, n))
    return out


def main():
    for name in sys.argv[1:]:
        p = os.path.join(RES, name + ".png")
        a = np.array(Image.open(p).convert("RGBA"))
        print("== %s  %dx%d" % (name, a.shape[1], a.shape[0]))
        for x, y, w, h, n in sorted(blobs(a[:, :, 3] > 24), key=lambda b: (b[1], b[0])):
            print("   xs=%4d ys=%4d  w=%4d h=%4d   (화소 %d)" % (x, y, w, h, n))
        print()


main()
