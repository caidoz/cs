# -*- coding: utf-8 -*-
"""60프레임 확장으로 덧붙인 보간모션의 공격판정을 지운다.

cNCS[]는 한 모션당 8칸이고 뒤 4칸이 공격판정 박스다.
확장 때 cmflib.getTween()이 원본 CS 행을 통째로 복사하는 바람에
보간모션까지 원본과 똑같은 공격판정을 갖게 됐다. 보간모션은 원본
사이를 메우는 그림일 뿐이라 판정이 있으면 안 된다. 플레이어->몬스터
방향은 재타격 가드가 없어(Func_Combat.cpp의 attackedFrame 검사는
몬스터->플레이어에만 걸린다) 판정 프레임 하나가 곧 1히트다.
그대로 두면 한 방의 타수가 4배로 부풀어 있다.

보간모션은 전부 원본 뒤에 덧붙였으므로(인덱스를 밀지 않는 방식)
확장 직전 커밋의 TOTALCNMOTION 이상인 인덱스가 곧 보간모션이다.
"""
import io, re, os, sys, subprocess

BASE = '05997da'	#cmf 확장이 시작되기 직전 커밋


def originalTotal(n):
    """확장 직전 커밋에서 c{n}.h의 모션 개수를 읽는다. 파일이 없으면 None."""
    try:
        out = subprocess.check_output(
            ['git', 'show', '%s:Classes/Cmf/c%d.h' % (BASE, n)],
            stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError:
        return None
    txt = out.decode('utf-8', 'replace')
    m = re.search(r'TOTALC%dMOTION\s*=\s*(\d+)' % n, txt)
    return int(m.group(1)) if m else None


def clearTweenAttack(n, dryRun=False):
    path = 'Classes/Cmf/c%d.h' % n
    if not os.path.exists(path):
        return None

    orig = originalTotal(n)
    if orig is None:
        return None

    txt = io.open(path, encoding='utf-8-sig').read()
    m = re.search(r'TOTALC%dMOTION\s*=\s*(\d+)' % n, txt)
    cur = int(m.group(1))
    if cur == orig:
        return (n, orig, cur, 0)	#확장 안 된 파일

    lines = txt.split('\n')
    m = re.search(r'static const signed short c%dCS\[\]\s*=\s*\{' % n, txt)
    if not m:
        return (n, orig, cur, -1)	#CS 배열을 못 찾음

    #CS 배열이 시작되는 줄 번호를 찾는다.
    upto = txt[:m.end()].count('\n')
    idx, changed = 0, 0

    for k in range(upto, len(lines)):
        line = lines[k]
        if '};' in line:
            break
        code, sep, note = line.partition('//')
        cells = [c for c in code.split(',')]
        #마지막 원소는 줄 끝 쓰레기라 값이 있는 칸만 센다.
        vals = [c for c in cells if c.strip()]
        if len(vals) != 8:
            continue

        if idx >= orig:
            #뒤 4칸을 0으로. 앞의 공백/탭은 원래 모양을 지킨다.
            for j in range(4, 8):
                lead = re.match(r'^\s*', vals[j]).group(0)
                vals[j] = lead + '0 * _2X'
            newCode = ', '.join(v.strip() if i == 0 else v
                                for i, v in enumerate(vals))
            #원본 줄의 들여쓰기와 4칸/4칸 사이 간격을 흉내낸다.
            indent = re.match(r'^\s*', code).group(0)
            newCode = (indent
                       + ', '.join(v.strip() for v in vals[:4]) + ',\t\t'
                       + ', '.join(v.strip() for v in vals[4:]) + ',')
            if not dryRun:
                lines[k] = newCode + (sep + note if sep else '')
            changed += 1
        idx += 1

    if not dryRun and changed:
        io.open(path, 'w', encoding='utf-8-sig',
                newline='\r\n').write('\n'.join(lines))

    return (n, orig, cur, changed)


if __name__ == '__main__':
    dry = '--dry' in sys.argv
    nums = [int(a) for a in sys.argv[1:] if a.isdigit()]
    if not nums:
        nums = range(0, 123)

    total = 0
    for n in nums:
        r = clearTweenAttack(n, dry)
        if r is None:
            continue
        n, orig, cur, changed = r
        if changed:
            print('c%-4d 원본 %4d -> 현재 %4d  보간모션 판정 제거 %4d행'
                  % (n, orig, cur, changed))
            total += changed
    print()
    print('%s 총 %d행' % ('[예행] ' if dry else '', total))
