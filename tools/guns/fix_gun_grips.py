# -*- coding: utf-8 -*-
"""손잡이 좌표를 총 그림 안으로 옮긴다.

Classes/Data/DianaGunData.h 의 grip 은 크기별 공식으로 매겨져 있어서, 그
자리에 그림이 없는 총이 많다. 손은 그 점에 붙으므로 그림 밖에 점이 있으면
총이 손에서 좌하단으로 빠져 보인다.

여기서는 모양을 바꾸지 않는다. 점만 그림 안으로 당긴다:
    - 그 줄에 그림이 있으면 x 만 그림 폭 안으로 당긴다
    - 그 줄이 비어 있으면 그림이 있는 가장 가까운 줄로 옮기고, 그 줄에서
      원래 x 와 가장 가까운 자리를 고른다
원래 의도(총마다 정한 손잡이 위치)를 최대한 남기려고 "가장 가까운" 자리를 쓴다.
"""
from pathlib import Path
import re
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
HEADER = ROOT / 'Classes/Data/DianaGunData.h'
RES = ROOT / 'Resources/res'

ROW = re.compile(r'(\{\s*)(\d+)(,\s*)(\d+)(,\s*)(\d+)(,\s*)(\d+)(\s*\}, // w1_)(\d+)')


def content_rows(alpha, w, h):
    """줄마다 그림이 있는 x 범위. 없으면 None."""
    out = []
    for y in range(h):
        box = alpha.crop((0, y, w, y + 1)).getbbox()
        out.append(None if box is None else (box[0], box[2]))
    return out


def fix(n, gx, gy):
    with Image.open(RES / ('w1_%d.png' % n)) as im:
        im = im.convert('RGBA')
        alpha = im.getchannel('A')
        w, h = im.size
        rows = content_rows(alpha, w, h)

    gy = max(0, min(h - 1, gy))

    if rows[gy] is None:
        # 그림이 있는 가장 가까운 줄로. 같은 거리면 아래(손잡이 끝) 쪽을 쓴다.
        near = [y for y, r in enumerate(rows) if r]
        if not near:
            return gx, gy, 'empty'
        gy = min(near, key=lambda y: (abs(y - gy), -y))

    left, right = rows[gy]
    newx = max(left, min(right - 1, gx))
    return newx, gy, 'ok'


def main():
    text = HEADER.read_text(encoding='utf-8')
    changed = []

    def repl(m):
        n = int(m.group(10))
        gx, gy = int(m.group(6)), int(m.group(8))
        nx, ny, _ = fix(n, gx, gy)
        if (nx, ny) != (gx, gy):
            changed.append((n, gx, gy, nx, ny))
        return (m.group(1) + m.group(2) + m.group(3) + m.group(4) + m.group(5)
                + '%3d' % nx + m.group(7) + '%3d' % ny + m.group(9) + m.group(10))

    HEADER.write_text(ROW.sub(repl, text), encoding='utf-8')

    for n, gx, gy, nx, ny in changed:
        print('w1_%-2d grip (%3d,%3d) -> (%3d,%3d)' % (n, gx, gy, nx, ny))
    print('%d개 고침' % len(changed))


if __name__ == '__main__':
    main()
