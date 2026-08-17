# -*- coding: utf-8 -*-
"""죽은 전역변수의 정의와 extern 선언을 지운다.

한 줄에 여럿 선언한 경우(signed int frame, demoFrame, ...)는 그 이름만 빼낸다.
줄째로 지우면 살아 있는 이웃까지 날아간다. 모양을 못 읽으면 손대지 않고 남긴다.
"""
import io, os, re, sys, glob


def dropName(text, var):
    """선언 목록에서 var만 뺀다. 하나뿐이면 '', 못 읽으면 None."""
    m = re.match(r'^([\w:<>\*&\s]+?)\s+(.+);(\s*(?://.*)?)$', text.rstrip('\r'))

    if not m:
        return None

    decl, body, tail = m.groups()

    parts, depth, cur = [], 0, ''

    for c in body:
        if c in '([{':
            depth += 1
        elif c in ')]}':
            depth -= 1

        if c == ',' and depth == 0:
            parts.append(cur)
            cur = ''
        else:
            cur += c

    parts.append(cur)

    #조각 앞에 타입이 붙어 있을 수 있다("extern int x" 는 decl이 extern까지만
    #끊겨서 첫 조각이 "int x"가 된다). 그래서 맨 앞에 고정하지 않고 찾는다.
    idx = [i for i, p in enumerate(parts)
           if re.search(r'\b%s\s*(=|\[|$)' % re.escape(var), p)]

    if not idx:
        return None

    if len(parts) == 1:
        return ''	#선언이 하나뿐이라 줄째로 버린다

    #첫 조각에는 타입이 얹혀 있다. 그것만 빼면 "extern summonMidY;" 처럼
    #타입이 사라진 줄이 남는다. 그 경우는 손대지 않고 사람에게 넘긴다.
    if idx[0] == 0:
        return None

    keep = [p for i, p in enumerate(parts) if i not in idx]

    return '%s %s;%s' % (decl, ','.join(keep).strip(), tail)


def strip(path, names, dryRun):
    lines = io.open(path, encoding='utf-8-sig').read().split('\n')
    out = []
    hit, missed = 0, []

    for line in lines:
        bare = line.strip()
        target = None

        for n in names:
            #정의(1열) 또는 extern 선언에서 그 이름이 선언되는 줄인가.
            if re.search(r'\b%s\s*(=|\[|;|,)' % re.escape(n), bare) \
                    and '(' not in bare.split(';')[0]:
                target = n
                break

        if target is None:
            out.append(line)
            continue

        new = dropName(bare, target)

        if new is None:
            missed.append('%s: %s' % (os.path.basename(path), bare[:70]))
            out.append(line)
        elif new == '':
            hit += 1	#줄째로 버린다
        else:
            out.append(re.match(r'^(\s*)', line).group(1) + new)
            hit += 1

    if hit and not dryRun:
        io.open(path, 'w', encoding='utf-8-sig',
            newline='\r\n').write('\n'.join(out))

    return hit, missed


def run(listPath, dryRun=False):
    names = []
    on = False

    for line in io.open(listPath, encoding='utf-8'):
        if line.startswith('==='):
            on = '지워도 되는 것' in line
            continue

        if not on:
            continue

        parts = line.split()

        if len(parts) >= 2:
            names.append(parts[1])

    print('대상 %d개' % len(names))

    total, missed = 0, []

    for path in sorted(glob.glob('Classes/*.cpp')) + sorted(glob.glob('Classes/*.h')):
        h, m = strip(path, names, dryRun)
        total += h
        missed += m

        if h:
            print('  %-24s %d줄' % (os.path.basename(path), h))

    print('지운 줄 %d' % total)

    for m in missed:
        print('  못 읽음: ' + m)


if __name__ == '__main__':
    run(sys.argv[1], '--dry' in sys.argv)
