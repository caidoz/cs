# -*- coding: utf-8 -*-
"""cN.h / cNmv 일괄 확장. 인자로 --dry 를 주면 검사만 한다."""
import sys, re, io, os, subprocess
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cmflib import *

DRY = '--dry' in sys.argv
ONLY = [int(a) for a in sys.argv[1:] if a.isdigit()]

# c0~c2 는 주인공/동료라 이동핸들러가 코드에 모션을 직접 박아 쓴다(PlayerMove 계열).
# c3 는 이미 처리했다. c80 은 mv 가 비어 있다.
SKIP = {0, 1, 2}

BASE = '05997da'

#배열을 팩으로 옮긴 뒤의 작업 트리 헤더에는 cNMI/cNmv가 없다. 보간의
#원본은 배열이 남아 있는 기준 커밋에서 읽고, 결과만 현재 데이터로 굽는다.
data = subprocess.check_output(
    ['git', 'show', BASE + ':Classes/Data/CmfData.h']).decode('utf-8-sig')

# 모든 cmf 의 모션 이름 -> 값 (상호참조 해결용)
allEnum = {}
for n in range(123):
    try:
        src = subprocess.check_output(
            ['git', 'show', '%s:Classes/Cmf/c%d.h' % (BASE, n)]).decode('utf-8-sig')
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
        source = subprocess.check_output(
            ['git', 'show', '%s:Classes/Cmf/c%d.h' % (BASE, n)]).decode('utf-8-sig')
        c = Cmf(n, source)
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
        if not DRY and 'source' in locals():
            #상태표가 손상됐거나 정적인 CMF도 팩 재생성에는 원본 배열이 필요하다.
            io.open(os.path.join(CMFDIR, 'c%d.h' % n), 'w',
                    encoding='utf-8-sig', newline='\r\n').write(source)
        skipped.append((n, str(e)))
        continue
    except Exception as e:
        skipped.append((n, '예외 %s: %s' % (type(e).__name__, e)))
        continue

    if not DRY:
        io.open(c.path, 'w', encoding='utf-8-sig', newline='\r\n').write(header)
        data = data[:m.start()] + mvText + data[m.end():]
    done.append((n, c.totalMotion, len(c.newNames), len(states)))

if not DRY and False:
	#현재 CmfData.h는 팩 링크 선언 전용이다. 예전 거대 배열 파일로 되돌리는
	#실수는 막고, 실제 병합은 bake_hero_tweens.py가 담당한다.
	raise SystemExit('쓰기 작업은 bake_hero_tweens.py를 사용해야 한다')

if not DRY:
    data += '\n//pack_cmf.py가 포인터 배열이 아닌 각 이동표의 실제 길이를 읽는다.\n'
    for n in range(123):
        data += 'enum { c%dmv_COUNT = sizeof(c%dmv) / sizeof(c%dmv[0]) };\n' % (n, n, n)
    io.open(CMFDATA, 'w', encoding='utf-8-sig', newline='\r\n').write(data)

print('처리 %d개' % len(done))
for n, a, b, s in done:
    print('  c%-4d 모션 %3d -> %4d   상태 %d' % (n, a, b, s))
print()
print('보류 %d개' % len(skipped))
for n, w in skipped:
    print('  c%-4d %s' % (n, w))
