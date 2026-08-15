# -*- coding: utf-8 -*-
"""스킬 프레임표에서 한 프레임만 나오는 모션을 두 프레임으로 맞춘다.

60프레임 확장 때 원본 행수를 2배로 늘리면서 그 안에 보간모션 4개를 끼워 넣다
보니, 원본이 3프레임이던 구간은 2,1,2,1 로, 2프레임이던 구간은 1,1,1,1 로
쪼개졌다. 보간모션이 한 프레임만 스쳐 지나가면 눈에 남지 않고 동작만 빨라
보인다. 그래서 1프레임짜리를 전부 2프레임으로 맞춘다. 스킬은 그만큼 길어진다.

늘린 행의 이동/효과/사운드 칸은 0으로 둔다. 그 칸들은 한 번만 발동해야 하는
일회성 명령이라 복사하면 두 번 터진다.
"""
import io, re, sys, os

ROW = re.compile(r'^(\s*)([A-Za-z_0-9]+)(\s*,\s*)(-?\w+)(\s*,\s*)(\w+)(\s*,\s*)(\w+)(\s*,)(.*)$')


def pairUp(path, marker, dryRun=False):
    text = io.open(path, encoding='utf-8-sig').read()
    lines = text.split('\n')

    start = next(k for k, l in enumerate(lines) if marker in l)

    #블록의 행 위치와 모션명을 모은다. _END를 만나면 끝이다.
    idx, mot = [], []
    for k in range(start, len(lines)):
        m = ROW.match(lines[k])
        if not m:
            continue
        idx.append(k)
        mot.append(m.group(2))
        if m.group(6) in ('_END', '_ENDTOFALL'):
            break

    #같은 모션이 몇 번 연속되는지 센다.
    runLen = [0] * len(mot)
    i = 0
    while i < len(mot):
        j = i
        while j < len(mot) and mot[j] == mot[i]:
            j += 1
        for k in range(i, j):
            runLen[k] = j - i
        i = j

    #연속 1회짜리 행을 하나씩 복제한다.
    out, added = [], 0
    for n, k in enumerate(idx):
        out.append((k, None))
        if runLen[n] == 1:
            m = ROW.match(lines[k])
            dup = '%s%s%s0%s0%s0%s' % (m.group(1), m.group(2), m.group(3),
                                       m.group(5), m.group(7), m.group(9))
            out.append((k, dup))
            added += 1

    print('%s : %d행 -> %d행 (+%d)' % (marker, len(idx), len(idx) + added, added))
    if dryRun:
        return len(idx), len(idx) + added

    #뒤에서부터 삽입해야 앞쪽 행번호가 안 밀린다.
    for k, dup in reversed(out):
        if dup is not None:
            lines.insert(k + 1, dup)

    io.open(path, 'w', encoding='utf-8-sig', newline='\r\n').write('\n'.join(lines))
    return len(idx), len(idx) + added


if __name__ == '__main__':
    path = sys.argv[1]
    marker = sys.argv[2]
    dry = '--dry' in sys.argv
    pairUp(path, marker, dry)
