# -*- coding: utf-8 -*-
"""Classes/Write.h 에서 blob 으로 옮긴 지도 배열을 지운다.

strip_cmf.py 와 같은 얼개다.

[지우는 것]
ma, mt, mr, mb, mo, mn, me 로 시작하는 맵별 배열 2,982개.
Data/MapBlob.cpp 안에 이어붙여 두었고, MapRelink() 가 표를 채운다.

[남기는 것]
mapDatas : 맵마다 10칸짜리 2차원 배열이다. 접두어가 겹치지만(ma...) 이건
           맵별 배열이 아니라 별개의 표다. 이미 팩에 들어가 있다.

먼저 verify_map.py 로 새 표가 옛 배열과 같은지 확인하고 나서 돌려라.

    python tools/content/strip_map.py
    python tools/content/strip_map.py --write
"""
import argparse
import io
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT

PATH = os.path.join(CT.CLASSES, 'Write.h')

#접두어 + 숫자 로 끝나야 한다. mapDatas 같은 것이 걸리지 않게 한다.
DECL = re.compile(
    r'^const[ \t]+(?:unsigned|signed)[ \t]+(?:char|short)[ \t]+'
    r'(?P<name>m[abemnort])(?P<id>\d+)[ \t]*\[[ \t]*\][ \t]*=[ \t]*\{',
    re.M)


def strip(text):
    n = 0

    while True:
        m = DECL.search(text)

        if not m:
            break

        i = m.end()
        depth = 1

        while i < len(text) and depth:
            if text[i] == '{':
                depth += 1
            elif text[i] == '}':
                depth -= 1

            i += 1

        while i < len(text) and text[i] in ' \t':
            i += 1

        if i < len(text) and text[i] == ';':
            i += 1

        while i < len(text) and text[i] in '\r\n':
            i += 1

        text = text[:m.start()] + text[i:]
        n += 1

    return text, n


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--write', action='store_true')
    args = ap.parse_args()

    text = io.open(PATH, encoding='utf-8-sig', newline='').read()
    before = len(text)
    text, n = strip(text)

    print('배열 %d개 지움' % n)
    print('  Write.h %s -> %s 바이트 (%.1f%%)'
          % (format(before, ','), format(len(text), ','),
             100.0 * len(text) / before))

    if not args.write:
        print('  (실제로 지우려면 --write)')
        return 0

    io.open(PATH, 'w', encoding='utf-8-sig', newline='').write(text)
    print('  지웠다')
    return 0


if __name__ == '__main__':
    sys.exit(main())
