# -*- coding: utf-8 -*-
"""링커가 뽑은 죽은 함수 후보를 소스로 교차검증한다.

링커는 지금 빌드 구성에서 실제로 링크된 것만 본다. 그래서 아래 둘을 못 잡는다.
 - 꺼진 #ifdef 가지 안의 호출 (안드로이드/iOS/리눅스 빌드에서는 살아 있을 수 있다)
 - 이름으로만 부르는 자리 (콜백 등록 등)

그래서 주석을 걷어낸 본문에서 이름을 다시 세고, 정의와 선언 말고도 등장하면
"보류"로 돌린다. 보류가 많더라도 그쪽이 안전하다.
"""
import io, os, re, sys, glob

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from deadcomment import spans


def liveText(path):
    text = io.open(path, encoding='utf-8-sig').read()
    out, prev = [], 0

    for a, b, _ in spans(text):
        out.append(text[prev:a])
        prev = b

    out.append(text[prev:])
    return ''.join(out)


def run(candPath, outPath):
    cand = []

    for line in io.open(candPath, encoding='utf-8'):
        parts = line.split()

        if len(parts) >= 2:
            cand.append((parts[0], parts[1]))

    files = sorted(glob.glob('Classes/*.cpp')) + sorted(glob.glob('Classes/*.h'))
    body = {}

    for path in files:
        body[os.path.basename(path)] = liveText(path)

    dead, hold = [], []

    for src, fn in cand:
        pat = re.compile(r'\b%s\b' % re.escape(fn))
        code = 0	#.cpp에서의 등장 횟수
        seen = []

        for name, text in body.items():
            n = len(pat.findall(text))

            if not n:
                continue

            seen.append('%s:%d' % (name, n))

            if name.endswith('.cpp'):
                code += n

        #.cpp에는 정의 한 줄만 있어야 한다. 헤더 선언은 몇 개가 있든 상관없다.
        #예전에는 전체 등장 수가 2 이하면 죽은 것으로 봤는데, 헤더 선언이 없는
        #함수는 "정의 + 진짜 호출"이 2가 되어 살아 있는 것을 지웠다.
        #호출하는 쪽이 죽은 static 함수라 링커에는 안 보이던 경우다.
        if code <= 1:
            dead.append((src, fn, code))
        else:
            hold.append((src, fn, code, ' '.join(seen)))

    dead.sort()
    hold.sort()

    with io.open(outPath, 'w', encoding='utf-8') as f:
        f.write('=== 지워도 되는 것 %d개 (정의/선언 말고는 등장하지 않음) ===\n' % len(dead))

        for src, fn, n in dead:
            f.write('%-22s %s\n' % (src, fn))

        f.write('\n=== 보류 %d개 (소스 어딘가에서 이름이 보인다) ===\n' % len(hold))

        for src, fn, n, where in hold:
            f.write('%-22s %-32s %d회  %s\n' % (src, fn, n, where))

    print('지워도 되는 것 %d개 / 보류 %d개' % (len(dead), len(hold)))


if __name__ == '__main__':
    run(sys.argv[1], sys.argv[2])
