# -*- coding: utf-8 -*-
"""검 그림에서 실제로 쓰는 칸만 골라 마스크 표를 만든다.

    python tools/swords/build_cells.py            무엇이 나오는지 본다
    python tools/swords/build_cells.py --write    Classes/Data/SwordCells.inc 를 쓴다

[왜 필요한가]

검 그림이 다시 그려지면서 T 자 모양이 생겼다(w0_24 는 3x3 인데 윗줄만
가로로 넓고 아래는 가운데 한 줄이다). 칸을 네모로 잡으면 쓰지도 않는
네 귀퉁이에 값을 치른다 - 가방은 자리가 곧 값이다.

그림을 32 픽셀 칸으로 잘라, 칸마다 알파가 얼마나 찼는지 보고 거의 빈
칸은 뺀다. swordTileSize 가 폭과 높이를 주고 이 표가 그 안의 모양을 준다.

[기준]

TILE_MIN 보다 적게 찬 칸은 안 쓰는 것으로 본다. 칼끝이 비스듬히 스치는
정도는 자리를 내줄 값이 못 된다. 0.15 는 다시 그린 검들을 다 훑어 보고
고른 값이다 - T 자의 빈 칸은 0 이고 쓰는 칸은 30 이상이라 사이가 넓다.
"""
import io
import os
import re
import sys

import numpy as np
from PIL import Image

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
TILE = 32
TILE_MIN = 0.15


def tile_sizes():
    """swordTileSize[] 를 (가로, 세로) 목록으로."""
    p = os.path.join(ROOT, "Classes", "Data", "SwordSprites.h")
    s = io.open(p, encoding="utf-8-sig", errors="replace").read()
    body = s.split("swordTileSize[35 * 2] = {", 1)[1].split("};", 1)[0]
    n = [int(t) for t in re.findall(r"[0-9]+", re.sub(r"//.*", "", body))]
    return [(n[i * 2], n[i * 2 + 1]) for i in range(len(n) // 2)]


def mask_of(detail, w, h):
    """그 검이 쓰는 칸. (마스크, 칸수, 그림용 줄) 을 낸다.

    cells 는 bit(row * 4 + col) 이고 row 0 이 맨 아랫줄이다. 그림은 위부터
    읽으므로 뒤집어 적는다. 네모를 다 쓰면 0 을 준다 - 가방 쪽에서 0 은
    "구멍 없음" 이라 그대로 맞는다.
    """
    p = os.path.join(ROOT, "Resources", "res", "w0_%d.png" % (detail + 1))
    a = np.array(Image.open(p).convert("RGBA"))
    m = a[:, :, 3] > 16

    use = [[m[r * TILE:(r + 1) * TILE, c * TILE:(c + 1) * TILE].mean() >= TILE_MIN
            for c in range(w)] for r in range(h)]

    #한 줄이 통째로 비면 그림이 칸을 안 채운 것이다. 그런 줄은 건드리지
    #않는다 - 폭과 높이는 swordTileSize 가 정하고 여기서는 구멍만 본다.
    for r in range(h):
        if not any(use[r]):
            use[r] = [True] * w

    bits = 0
    for r in range(h):
        for c in range(w):
            if use[r][c]:
                bits |= 1 << ((h - 1 - r) * 4 + c)

    cnt = sum(sum(row) for row in use)
    art = ["".join("O" if use[r][c] else "." for c in range(w)) for r in range(h)]

    return (0 if cnt == w * h else bits), cnt, art


def main():
    sizes = tile_sizes()
    out = []
    full = 0
    now = 0
    new = 0

    for d, (w, h) in enumerate(sizes):
        bits, cnt, art = mask_of(d, w, h)
        out.append((d, w, h, bits, cnt, art))
        now += w * h
        new += cnt
        if bits == 0:
            full += 1

    print("검 %d 자루. 칸이 %d%% 미만 차면 안 쓰는 것으로 본다.\n"
          % (len(sizes), int(TILE_MIN * 100)))
    print("구멍이 있는 것만 적는다 (나머지 %d 자루는 네모를 다 쓴다)\n" % full)

    for d, w, h, bits, cnt, art in out:
        if bits == 0:
            continue
        print("  검 %2d  %dx%d -> %d칸   %s" % (d, w, h, cnt, art[0]))
        for line in art[1:]:
            print("                        %s" % line)

    print()
    print("칸 합 %d -> %d  (%d칸, %.0f%% 준다)"
          % (now, new, now - new, (now - new) * 100.0 / max(1, now)))

    if "--write" not in sys.argv:
        print("\n(실제로 쓰려면 --write)")
        return

    lines = []
    lines.append("// tools/swords/build_cells.py 가 만든다. 손으로 고치지 마라.")
    lines.append("// 검 그림이 바뀌면 다시 돌려라.")
    lines.append("//")
    lines.append("// 그 검이 쓰는 칸. bit(row * 4 + col), row 0 이 맨 아랫줄이다.")
    lines.append("// 0 이면 네모를 다 쓴다는 뜻이다.")
    lines.append("static const unsigned short swordTileCells[%d] = {" % len(out))
    for d, w, h, bits, cnt, art in out:
        lines.append("\t0x%03X,\t//w0_%-3d %dx%d %d칸  %s"
                     % (bits, d + 1, w, h, cnt, " ".join(art)))
    lines.append("};")
    lines.append("")

    p = os.path.join(ROOT, "Classes", "Data", "SwordCells.inc")
    io.open(p, "w", encoding="utf-8-sig", newline="\r\n").write("\n".join(lines))
    print("\n썼다: %s" % p)


main()
