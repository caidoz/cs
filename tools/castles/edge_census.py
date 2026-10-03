# -*- coding: utf-8 -*-
"""성 조각들의 왼쪽 투명 여백을 잰다.

    python tools/castles/edge_census.py

성을 화면 왼쪽에 붙이려는데, 좌표를 0 으로 줘도 그림 자체에 투명
여백이 있으면 그만큼 뜬다. 조각마다 여백이 다르면 성 단계를 넘길 때
붙는 정도가 달라진다 - 그래서 가장 왼쪽에 오는 조각들을 다 재 본다.

외장(wall)은 640 폭이고 방은 512 폭이며 방은 로컬 x=64 에서 시작한다.
그러니 화면 맨 왼쪽에 오는 것은 외장이다.
"""
import glob
import os
import re

import numpy as np
from PIL import Image

RES = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(
    os.path.abspath(__file__)))), "Resources", "res")


def left_pad(path):
    a = np.array(Image.open(path).convert("RGBA"))
    m = a[:, :, 3] > 16
    if not m.any():
        return None, a.shape[1]
    xs = np.nonzero(m.sum(0))[0]
    return int(xs.min()), a.shape[1]


def main():
    print("조각마다 왼쪽 투명 여백 (0 이면 그림이 왼쪽 끝까지 차 있다)\n")

    for pat, label in (("castle_exterior/castle_*_wall_stage_0.png", "외장"),
                       ("castle_room_*_0.png", "방"),
                       ("castle_mobility/castle_*_base_stage_0.png", "바닥")):
        rows = []
        for p in sorted(glob.glob(os.path.join(RES, pat))):
            pad, w = left_pad(p)
            rows.append((os.path.basename(p), pad, w))
        if not rows:
            continue
        print("[%s]" % label)
        for name, pad, w in rows:
            print("   %-38s 폭 %4d  왼쪽여백 %s" % (name, w, pad))
        pads = [r[1] for r in rows if r[1] is not None]
        if pads:
            print("   -> 최소 %d  최대 %d\n" % (min(pads), max(pads)))


main()
