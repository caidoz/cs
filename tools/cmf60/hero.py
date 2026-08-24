# -*- coding: utf-8 -*-
"""히어로 cmf(c0~c2) 확장.

히어로 모션은 mv 데이터가 아니라 코드와 HeroData.h 테이블이 직접 고른다.
그래서 이름 접두어로 그룹을 묶고(PO_C0_A0..A24 -> 그룹 A) 각 그룹을 4배로 늘린다.
모션이 하나뿐인 그룹(SKILLREADY, DIE, DROWN 등)은 보간할 상대가 없어 제외한다.

인덱스는 밀지 않는다. 중간모션은 전부 뒤에 덧붙이고,
대신 '그룹의 n번째 포즈'를 찾아 쓰라고 c0Chain[] 표를 같이 뽑아준다.
"""
import sys, re, io, os, subprocess
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cmflib import *

HEROLOOP_FRAME = 16

# walkFrame[] = {0, 1, 2, 1} 이 만들던 실제 재생 순서. 순환한다.
PINGPONG = [('NEUTRAL', 'N'), ('WALK', 'W'), ('RUN', 'R'), ('SWIM', 'SWIM')]


def groupsOf(c, n):
    """이름 접두어로 모션을 묶는다. 값은 인덱스 순으로 정렬한다."""
    g, order = {}, []
    for i, nm in enumerate(c.motNames):
        m = re.match(r'^PO_C%d_(.*?)(\d*)$' % n, nm)
        if not m:
            continue
        pre, idx = m.group(1), m.group(2)
        if pre not in g:
            g[pre] = []
            order.append(pre)
        g[pre].append((int(idx) if idx else -1, i))
    for k in g:
        g[k].sort()
    return g, order


def applyHeroPartFixes(c, n):
    if n != 0:
        return

    fixes = {
        'PO_C0_A11_1': (-4, -34, 5),
        'PO_C0_A11_2': (-6, -36, 5),
        'PO_C0_A11_3': (-8, -38, 5),
        'PO_C0_CRASH0_1': (-2, -296, 0),
        'PO_C0_CRASH0_2': (-4, -298, 0),
        'PO_C0_CRASH0_3': (-6, -300, 0),
        'PO_C0_CRASH1_1': (-10, -392, 7),
        'PO_C0_CRASH1_2': (-12, -394, 7),
        'PO_C0_CRASH1_3': (-14, -396, 7),
        'PO_C0_CRASH4_1': (-302, -406, 6),
        'PO_C0_CRASH4_2': (-304, -408, 6),
        'PO_C0_CRASH4_3': (-306, -410, 6),
    }
    by_name = dict((name, i) for i, name in enumerate(c.newNames))
    for name, (x, y, typ) in fixes.items():
        idx = by_name[name]
        parts = list(c.newMotions[idx])
        for p, part in enumerate(parts):
            if part[0] in (108, 109):
                parts[p] = (108, x, y, str(typ))
                break
        else:
            parts.insert(0, (108, x, y, str(typ)))
        c.newMotions[idx] = parts
        c.newMiRaw[idx] = [['IMG_C0_%d' % part[0], num(part[1]), num(part[2]), part[3]]
                           for part in parts]


def expandHero(n, source=None, write_output=True):
    c = Cmf(n, source)
    if not c.ok:
        raise Skip('c%d 파싱 실패: %s' % (n, c.why))
    g, order = groupsOf(c, n)
    c.beginExpand()

    # ---- 그룹별 4배 체인 ----
    chains = []
    for pre in order:
        keys = [i for _, i in g[pre]]
        if len(keys) < 2:
            continue
        seq = []
        for i, a in enumerate(keys):
            seq.append(a)
            if i + 1 < len(keys):
                b = keys[i + 1]
                for step in (1, 2, 3):
                    seq.append(c.getTween(a, b, step))
        assert len(seq) == (len(keys) - 1) * 4 + 1
        chains.append((pre, seq))

    # ---- 대기/걷기/달리기/수영은 0,1,2,1 로 순환한다. 되돌아오는 구간도 만들어 준다 ----
    loops = []
    for name, pre in PINGPONG:
        keys = [i for _, i in g[pre]][:3]
        if len(keys) < 3:
            raise Skip('%s 그룹이 3개 미만' % pre)
        ks = [keys[0], keys[1], keys[2], keys[1]]
        seq = []
        for i, a in enumerate(ks):
            b = ks[(i + 1) % len(ks)]
            seq.append(a)
            for step in (1, 2, 3):
                seq.append(a if b == a else c.getTween(a, b, step))
        assert len(seq) == HEROLOOP_FRAME
        loops.append((name, seq))

    c.nameTweens()
    applyHeroPartFixes(c, n)
    text = c.render()

    L = ['', '//60프레임용 4배 확장 체인.',
         '//PO_C%d_A0 + k 처럼 쓰던 자리를 c%dChain[C%dCHAIN_A + k] 로 바꿔 쓴다.' % (n, n, n),
         '//원본 키모션과 중간모션 3개가 번갈아 들어 있고, 마지막 키로 끝난다.',
         'enum {']
    off = 0
    for pre, seq in chains:
        L.append('\tC%dCHAIN_%s = %d,\tC%dCHAIN_%s_CNT = %d,' % (n, pre, off, n, pre, len(seq)))
        off += len(seq)
    L += ['', '\tTOTALC%dCHAIN = %d' % (n, off), '};', '',
          'static const unsigned short c%dChain[] = {' % n]
    for pre, seq in chains:
        L.append('\t//%s' % pre)
        for i in range(0, len(seq), 6):
            L.append('\t' + ', '.join(c.newNames[m] for m in seq[i:i + 6]) + ',')
    L += ['};', '']

    #HEROLOOP_* 상수는 c0.h에만 둔다. c1/c2에도 넣으면 재정의 에러가 난다.
    if n == 0:
        L += ['enum {', '\tHEROLOOP_FRAME = %d,' % HEROLOOP_FRAME, '',
              '\tHEROLOOP_NEUTRAL = 0,', '\tHEROLOOP_WALK,', '\tHEROLOOP_RUN,', '\tHEROLOOP_SWIM,',
              '', '\tTOTALHEROLOOP', '};', '']
    L += ['//대기/걷기/달리기/수영 순환표. 한 프레임에 한 칸씩 쓴다.',
          '//원본은 walkFrame[]으로 0,1,2,1 을 두 프레임씩 잡아 8프레임에 3포즈였다.',
          '//같은 0.267초를 16프레임 16포즈로 채운다.',
          'static const unsigned short c%dLoop60[] = {' % n]
    for name, seq in loops:
        L.append('\t//%s' % name)
        for i in range(0, HEROLOOP_FRAME, 8):
            L.append('\t' + ', '.join(c.newNames[m] for m in seq[i:i + 8]) + ',')
    L += ['};', '']

    text = text.replace('#endif', '\n'.join(L) + '#endif')
    if write_output:
        io.open(c.path, 'w', encoding='utf-8-sig', newline='\r\n').write(text)
    return c, chains, loops


if __name__ == '__main__':
    use_base = '--base' in sys.argv
    for n in [int(a) for a in sys.argv[1:] if a.isdigit()] or [0]:
        source = None
        if use_base:
            source = subprocess.check_output(
                ['git', 'show', '05997da:Classes/Cmf/c%d.h' % n]).decode('utf-8-sig')
        c, chains, loops = expandHero(n, source)
        print('c%d : 모션 %d -> %d, 체인 %d개' % (n, c.totalMotion, len(c.newNames), len(chains)))
        for pre, seq in chains:
            print('   %-18s %3d칸' % (pre, len(seq)))
