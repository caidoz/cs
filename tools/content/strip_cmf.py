# -*- coding: utf-8 -*-
"""Classes/Cmf/c*.h 에서 blob 으로 옮긴 배열을 지운다.

[지우는 것]
Off, MI, MIC, MIS, CS, Loop60. Data/CmfBlob.cpp 안에 이어붙여 두었고,
CmfRelink() 가 표를 채운다. 여기 남겨두면 exe 에 같은 자료가 두 벌 들어간다.
게다가 static const 라 이 헤더를 포함하는 .cpp 마다 한 벌씩 복제된다.

[남기는 것]
  enum       : PO_C0_N0, IMG_C0_152, TOTALC0OFF 같은 모션/이미지 번호.
               코드가 이름으로 쓰므로 컴파일 상수로 있어야 한다.
  Chain      : 읽는 곳이 없다. 주석에 "이렇게 쓸 것"이라고만 적혀 있다.
               작아서 그냥 둔다.
  Shot60     : c31Shot60 을 Func_Movement.cpp 가 이름으로 직접 쓴다.

먼저 verify_cmf.py 로 새 표가 옛 배열과 같은지 확인하고 나서 돌려라.
지우고 나면 맞춰볼 상대가 없다.

    python tools/content/strip_cmf.py
    python tools/content/strip_cmf.py --write
"""
import argparse
import io
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT

CMFDIR = os.path.join(CT.CLASSES, 'Cmf')

#blob 으로 옮긴 것들. 이 접미어를 가진 배열만 지운다.
DROP = ('Off', 'MI', 'MIC', 'MIS', 'CS', 'Loop60')

#접미어가 겹친다. MI 와 MIC 와 MIS 를 구분하려면 정확히 맞춰야 한다.
DECL = re.compile(
    r'^static[ \t]+const[ \t]+(?:un)?signed[ \t]+short[ \t]+'
    r'c(?P<id>\d+)(?P<suf>Off|MIC|MIS|MI|CS|Loop60)[ \t]*\[[ \t]*\][ \t]*=[ \t]*\{',
    re.M)


def strip_one(path):
    text = io.open(path, encoding='utf-8-sig', newline='').read()
    before = len(text)
    n = 0

    while True:
        m = DECL.search(text)

        if not m:
            break

        if m.group('suf') not in DROP:
            raise SystemExit('%s: 예상 못 한 접미어 %s' % (path, m.group('suf')))

        #여는 { 부터 짝이 맞는 } 를 찾고, 그 뒤 ; 까지 지운다.
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

    return text, n, before


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--write', action='store_true')
    args = ap.parse_args()

    files = sorted((f for f in os.listdir(CMFDIR) if re.match(r'^c\d+\.h$', f)),
                   key=lambda f: int(f[1:-2]))

    total_before = total_after = total_n = 0

    for f in files:
        p = os.path.join(CMFDIR, f)
        text, n, before = strip_one(p)
        total_before += before
        total_after += len(text)
        total_n += n

        if args.write:
            io.open(p, 'w', encoding='utf-8-sig', newline='').write(text)

    print('파일 %d개, 배열 %d개 지움' % (len(files), total_n))
    print('  %s -> %s 바이트 (%.1f%%)'
          % (format(total_before, ','), format(total_after, ','),
             100.0 * total_after / total_before))

    if not args.write:
        print('  (실제로 지우려면 --write)')

    return 0


if __name__ == '__main__':
    sys.exit(main())
