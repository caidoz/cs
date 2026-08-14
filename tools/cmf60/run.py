# -*- coding: utf-8 -*-
"""cN.h / cNmv 일괄 확장. 인자로 --dry 를 주면 검사만 한다."""
import sys, re, io, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cmflib import *

DRY = '--dry' in sys.argv
ONLY = [int(a) for a in sys.argv[1:] if a.isdigit()]

# c0~c2 는 주인공/동료라 이동핸들러가 코드에 모션을 직접 박아 쓴다(PlayerMove 계열).
# c3 는 이미 처리했다. c80 은 mv 가 비어 있다.
SKIP = {0, 1, 2, 3}

data = read(CMFDATA)

# 모든 cmf 의 모션 이름 -> 값 (상호참조 해결용)
allEnum = {}
for n in range(123):
    try:
        src = read(os.path.join(CMFDIR, 'c%d.h' % n))
    except Exception:
        continue
    b = re.search(r'typedef enum _C%d_DEF \{(.*?)\n\} C%d_DEF;' % (n, n), src, re.S)
    if not b:
        continue
    head = b.group(1).split('TOTALC%dMOTION' % n)[0]
    for nm, v in re.findall(r'\b(PO_[A-Z0-9_]+)\s*=\s*(\d+)', head):
        allEnum.setdefault(nm, int(v))

done, skipped = [], []
for n in range(123):
    if n in SKIP or (ONLY and n not in ONLY):
        continue
    try:
        c = Cmf(n)
        if not c.ok:
            raise Skip(c.why)
        m = grabMv(n, data)
        if not m:
            raise Skip('cNmv 없음')
        blk = m.group(1)
        states, tail = parseMv(blk, motionIdMap(c, allEnum))
        if not states:
            raise Skip('상태 0개')
        names = stateNames(blk)
        c.beginExpand()
        newStates = expandStates(c, states, loopStates(states, tail))
        c.nameTweens()
        header = c.render()
        mvText = renderMv(n, c, newStates, tail, names)
    except Skip as e:
        skipped.append((n, str(e)))
        continue
    except Exception as e:
        skipped.append((n, '예외 %s: %s' % (type(e).__name__, e)))
        continue

    if not DRY:
        io.open(c.path, 'w', encoding='utf-8-sig', newline='\r\n').write(header)
        data = data[:m.start()] + mvText + data[m.end():]
    done.append((n, c.totalMotion, len(c.newNames), len(states)))

if not DRY:
    io.open(CMFDATA, 'w', encoding='utf-8-sig', newline='\r\n').write(data)

print('처리 %d개' % len(done))
for n, a, b, s in done:
    print('  c%-4d 모션 %3d -> %4d   상태 %d' % (n, a, b, s))
print()
print('보류 %d개' % len(skipped))
for n, w in skipped:
    print('  c%-4d %s' % (n, w))
