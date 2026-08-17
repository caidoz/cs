# -*- coding: utf-8 -*-
"""링커가 버린 심볼 목록에서 우리 전역 함수만 골라낸다.

/OPT:REF /VERBOSE:REF 로그를 먹는다. 주의할 점이 둘 있다.

1. 헤더에 든 상수 테이블(c0MI 등)은 모든 TU에 복사되어 들어가므로, 실제로
   쓰이더라도 나머지 obj에서는 전부 버려진다. 버려졌다는 사실만으로 죽었다고
   보면 안 된다. 그래서 데이터(@@3)는 아예 제외하고 함수(@@YA)만 본다.
2. 같은 함수가 여러 obj에서 버려졌다면 헤더에 인라인으로 들어간 것이다.
   우리 함수는 .cpp 한 곳에서만 정의되므로, 정의한 그 파일에서 버려진 것만
   후보로 삼는다.

여기서 나온 목록도 그대로 지우면 안 된다. 이름으로 불리는 콜백은 링커가
참조를 못 보기 때문이다. 호출자를 소스에서 한 번 더 확인한다.
"""
import io, os, re, sys, glob, collections

#"사람이 읽는 이름" (망글링된심볼)을(를) 무엇.obj에서 삭제했습니다.
LINE = re.compile(r'"([^"]*)"\s*\((\?[^)]+)\)[^\s]*\s*([\w.]+\.obj)')

#?이름@@YA... 는 전역 스코프의 자유 함수다. 클래스/네임스페이스가 붙으면
#@ 앞에 그 이름이 더 들어가므로 이 모양이 안 나온다.
FREEFUNC = re.compile(r'^\?([A-Za-z_]\w*)@@YA')


def defined(paths):
    """{함수이름: 정의한 파일}. 1열에서 시작하는 정의만 센다."""
    out = {}
    pat = re.compile(r'^[A-Za-z_][\w:<>\*&\s]*?\b([A-Za-z_]\w*)\s*\([^;]*$')

    for path in paths:
        text = io.open(path, encoding='utf-8-sig').read()
        lines = text.split('\n')

        for i, line in enumerate(lines):
            if line.startswith((' ', '\t', '#', '/', '}', '{')):
                continue

            m = pat.match(line)

            if not m:
                continue

            #다음 줄이 { 로 시작하거나 같은 줄이 ) { 로 끝나야 정의다.
            nxt = lines[i + 1].strip() if i + 1 < len(lines) else ''

            if line.rstrip().endswith('{') or nxt.startswith('{'):
                out[m.group(1)] = os.path.basename(path)

    return out


def run(logPath, outPath):
    files = sorted(glob.glob('Classes/*.cpp'))
    defs = defined(files)
    print('정의된 전역 함수 %d개' % len(defs))

    #심볼별로 어느 obj에서 버려졌는지 모은다.
    where = collections.defaultdict(set)
    name = {}

    for line in io.open(logPath, encoding='utf-8', errors='replace'):
        m = LINE.search(line)

        if not m:
            continue

        human, sym, obj = m.groups()
        f = FREEFUNC.match(sym)

        if not f:
            continue

        where[sym].add(obj)
        name[sym] = (f.group(1), human)

    print('버려진 전역 함수 심볼 %d개' % len(where))

    hit = []

    for sym, objs in where.items():
        fn, human = name[sym]

        if fn not in defs:
            continue	#우리가 정의한 함수가 아니다

        src = defs[fn]
        obj = src.replace('.cpp', '.obj')

        #정의한 파일의 obj에서 버려졌을 때만 죽은 것이다.
        if obj in objs:
            hit.append((src, fn, human))

    hit.sort()
    io.open(outPath, 'w', encoding='utf-8').write(
        '\n'.join('%-22s %-34s %s' % h for h in hit))

    print('후보 %d개 -> %s' % (len(hit), outPath))

    per = collections.Counter(h[0] for h in hit)

    for k, v in per.most_common():
        print('  %-24s %d' % (k, v))


if __name__ == '__main__':
    run(sys.argv[1], sys.argv[2])
