# -*- coding: utf-8 -*-
"""성 단계별 가방 칸 표를 만들어 CastleData.cpp 에 써 넣는다.

    python tools/bag/build_grid_table.py

[왜 세로가 늘 4 인가]

검 35 종 가운데 17 종이 2x4 이고, 부메랑은 3x3 과 4x4 다. 세로가 4 보다
낮으면 큰 검은 전부 눕혀야 하고 부메랑은 아예 못 넣는다. 눕히기는 자리가
없을 때 쓰는 수여야지 1 단계 내내 강제되면 안 된다.

예전 표는 1 단계가 12x2, 4 단계까지 3 줄이었다. 가로로 길고 납작해서
세로로 긴 물건이 들어갈 자리가 없었다.

[모양]

네 줄 고정, 아래가 넓고 위로 좁아진다. 늘어나는 것은 폭과 채움이다
(8 -> 12). 칸 수는 예전 그대로 24 -> 48 이라 성을 올리는 보상은 안 바뀐다.
맨 윗줄도 4 칸 이상이라 4x4 부메랑이 1 단계부터 들어간다.
"""
import io
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
SRC = os.path.join(ROOT, "Classes", "Data", "CastleData.cpp")

#줄마다 몇 칸인가. 맨 아랫줄부터 위로.
ROWS = [
    [8, 8, 4, 4],    # 1 단계  24
    [8, 8, 6, 4],    # 2       26
    [8, 8, 7, 6],    # 3       29
    [9, 9, 8, 6],    # 4       32
    [10, 10, 9, 6],  # 5       35
    [11, 11, 10, 6], # 6       38
    [12, 12, 11, 6], # 7       41
    [12, 12, 12, 8], # 8       44
    [12, 12, 12, 10],# 9       46
    [12, 12, 12, 12],# 10      48
]


def cells_of(rows):
    """줄 목록을 (열, 행) 칸 목록으로. 행 0 이 맨 아랫줄, 가운데 맞춤."""
    W = max(rows)
    out = []
    for r, n in enumerate(rows):
        x0 = (W - n) // 2
        for c in range(n):
            out.append((x0 + c, r))
    return out


def main():
    body, cnt, start, at = [], [], [], 0
    for i, rows in enumerate(ROWS):
        cs = cells_of(rows)
        assert max(c[0] for c in cs) < 12 and max(c[1] for c in cs) < 6
        cnt.append(len(cs))
        start.append(at)
        at += len(cs)
        body.append("\t//성 %d - %d칸  (%s)" % (i + 1, len(cs),
                                               " ".join(str(n) for n in rows[::-1])))
        flat = [v for p in cs for v in p]
        for k in range(0, len(flat), 16):
            body.append("\t" + " ".join("%d," % v for v in flat[k:k + 16]))

    s = io.open(SRC, encoding="utf-8-sig").read()
    head = "static const signed char castleGridCell_builtin[] = {"
    a = s.index(head) + len(head)
    b = s.index("\n};", a)
    s = s[:a] + "\n" + "\n".join(body) + "\n" + s[b + 1:]

    def put(name, vals):
        nonlocal s
        h = "const int %s[TOTALCASTLE] = {" % name
        a = s.index(h) + len(h)
        b = s.index("};", a)
        tail = ", ".join(str(vals[-1]) for _ in range(9))
        s = s[:a] + "\n\t" + ", ".join(str(v) for v in vals) + ",\n" + \
            "\t//열 단계 뒤의 성은 쓰지 않는다(gTotalCastle 이 10 이다).\n" + \
            "\t" + tail + ",\n" + s[b:]

    put("castleGridCellCnt", cnt)
    put("castleGridCellStart", start)
    io.open(SRC, "w", encoding="utf-8-sig", newline="").write(s)

    for i, rows in enumerate(ROWS):
        print("%2d 단계  %2d칸  %2d x 4   %s" % (i + 1, sum(rows), max(rows),
                                               " ".join(str(n) for n in rows[::-1])))


main()
