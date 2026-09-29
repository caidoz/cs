# -*- coding: utf-8 -*-
"""방 그림을 128 높이에 꽉 차게 맞춘다.

    python tools/castles/fit_rooms.py            검사만
    python tools/castles/fit_rooms.py --fix      고친다

[왜 필요한가]

방은 512x128 로 그려져 층층이 쌓인다. 층 간격도 128 이라 그림이 캔버스를
꽉 채워야 이음매가 0 픽셀로 붙는다. 그런데 몇 장은 아래쪽에 투명 여백이
있었다(2층 8px, 4층 9px, 7층 3px). 그만큼 층 사이가 벌어져 보인다.

여백을 아래로 밀어 없애면 이번엔 위가 빈다. 그래서 내용만 잘라내 세로로
128 이 되게 늘린다. 가장 심한 경우가 118 -> 128 로 8% 남짓이라 실내
그림에서는 눈에 띄지 않는다.

코드가 층마다 실제 높이를 들고 다니게 하는 길도 있지만, 그러면 그림이
바뀔 때마다 표를 같이 고쳐야 한다. 여백은 그림 쪽 일이므로 그림에서
끝낸다.
"""
import sys
import numpy as np
from pathlib import Path
from PIL import Image

RES = Path(__file__).resolve().parents[2] / "Resources" / "res"
H = 128
W = 512


def main():
    fix = "--fix" in sys.argv
    bad = 0

    for f in range(1, 11):
        for s in range(6):
            p = RES / ("castle_room_%02d_%d.png" % (f, s))
            if not p.exists():
                print("없음", p.name)
                continue

            im = Image.open(p).convert("RGBA")
            a = np.array(im)
            rows = np.nonzero((a[:, :, 3] > 16).sum(1))[0]
            if len(rows) == 0:
                print("비었음", p.name)
                continue

            y0, y1 = int(rows.min()), int(rows.max())
            top, bot = y0, im.height - 1 - y1
            if im.size == (W, H) and top == 0 and bot == 0:
                continue

            bad += 1
            print("%s  %dx%d  위여백%d 아래여백%d" % (p.name, im.width, im.height, top, bot))

            if fix:
                cut = im.crop((0, y0, im.width, y1 + 1))
                cut.resize((W, H), Image.LANCZOS).save(p)

    print()
    print("어긋난 그림 %d 장%s" % (bad, " (고침)" if fix else ""))


main()
