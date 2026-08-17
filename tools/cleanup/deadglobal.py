# -*- coding: utf-8 -*-
"""링커가 버린 심볼에서 우리 전역변수만 골라낸다.

deadfunc.py와 같은 구조인데 데이터(@@3)를 본다. 함수보다 오탐 위험이 크다.

 - 헤더에 든 const 테이블은 모든 TU에 복사되어 나머지에서 전부 버려진다.
   그래서 "우리 .cpp에서 1열에 정의된 이름"만 후보로 삼는다. 헤더에만 있는
   것은 애초에 대상이 아니다.
 - 세이브 파일로 나가는 구조체(robin 등)는 필드를 빼면 세이브가 깨진다.
   전역 자체를 지우는 것은 다른 문제지만, 저장/적재에 쓰이는 이름은
   memcpy/fwrite 인자로만 등장할 수 있어 따로 확인한다.
"""
import io, os, re, sys, glob, collections

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from deadcomment import spans

LINE = re.compile(r'"([^"]*)"\s*\((\?[^)]+)\)[^\s]*\s*([\w.]+\.obj)')
DATASYM = re.compile(r'^\?([A-Za-z_]\w*)@@3')

#1열에서 시작하고 괄호 없이 세미콜론으로 끝나면 전역변수 정의다.
#함수 정의/선언, 전처리기, 라벨은 걸러진다.
GLOBAL = re.compile(
    r'^(?!extern\b|typedef\b|using\b|return\b)'
    r'[A-Za-z_][\w:<>\*&\s]*?\b([A-Za-z_]\w*)\s*(\[[^;]*\])?\s*(=[^;]*)?;\s*$')


def liveText(path):
    text = io.open(path, encoding='utf-8-sig').read()
    out, prev = [], 0

    for a, b, _ in spans(text):
        out.append(text[prev:a])
        prev = b

    out.append(text[prev:])
    return ''.join(out)


def globalsIn(paths):
    """{이름: 정의한 파일}"""
    out = {}

    for path in paths:
        for line in liveText(path).split('\n'):
            if not line or line[0] in ' \t#/}{':
                continue

            if '(' in line.split(';')[0]:
                continue	#함수다

            m = GLOBAL.match(line.strip('\r'))

            if m:
                out[m.group(1)] = os.path.basename(path)

    return out


def run(logPath, outPath):
    files = sorted(glob.glob('Classes/*.cpp'))
    defs = globalsIn(files)
    print('.cpp에 정의된 전역 %d개' % len(defs))

    where = collections.defaultdict(set)
    human = {}

    for line in io.open(logPath, encoding='utf-8', errors='replace'):
        m = LINE.search(line)

        if not m:
            continue

        text, sym, obj = m.groups()
        d = DATASYM.match(sym)

        if not d:
            continue

        where[d.group(1)].add(obj)
        human[d.group(1)] = text

    #본문에서 이름을 다시 센다. 꺼진 #ifdef 안의 사용을 링커는 못 본다.
    body = {}

    for path in files + sorted(glob.glob('Classes/*.h')):
        body[os.path.basename(path)] = liveText(path)

    dead, hold = [], []

    for name, src in sorted(defs.items()):
        obj = src.replace('.cpp', '.obj')

        if name not in where or obj not in where[name]:
            continue	#링커가 살려둔 것

        pat = re.compile(r'\b%s\b' % re.escape(name))
        code = 0
        seen = []

        for fname, text in body.items():
            n = len(pat.findall(text))

            if not n:
                continue

            seen.append('%s:%d' % (fname, n))

            if fname.endswith('.cpp'):
                code += n

        if code <= 1:
            dead.append((src, name, human.get(name, '')))
        else:
            hold.append((src, name, code, ' '.join(seen)))

    with io.open(outPath, 'w', encoding='utf-8') as f:
        f.write('=== 지워도 되는 것 %d개 ===\n' % len(dead))

        for src, name, t in dead:
            f.write('%-22s %-30s %s\n' % (src, name, t))

        f.write('\n=== 보류 %d개 ===\n' % len(hold))

        for src, name, n, w in hold:
            f.write('%-22s %-30s %d회  %s\n' % (src, name, n, w))

    print('지워도 되는 것 %d개 / 보류 %d개 -> %s' % (len(dead), len(hold), outPath))


if __name__ == '__main__':
    run(sys.argv[1], sys.argv[2])
