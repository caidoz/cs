# -*- coding: utf-8 -*-
"""히어로 cmf(c0~c2) 확장.

히어로의 대기/걷기/달리기/수영은 mv 데이터가 아니라 코드가
`PO_C0_N0 + walkFrame[frame / 2 % 4]` 처럼 직접 골라 쓴다.
그래서 mv 기준이 아니라 그 식이 실제로 재생하는 순서를 키프레임으로 보고
4등분한 뒤, 결과를 순환표(cNLoop60)로 뽑아준다.
"""
import sys, re, io, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from cmflib import *

HEROLOOP_FRAME = 16

# walkFrame[] = {0, 1, 2, 1} 이 만드는 실제 재생 순서
CHAINS = [
    ('NEUTRAL', ['N0', 'N1', 'N2', 'N1']),
    ('WALK',    ['W0', 'W1', 'W2', 'W1']),
    ('RUN',     ['R0', 'R1', 'R2', 'R1']),
    ('SWIM',    ['SWIM0', 'SWIM1', 'SWIM2', 'SWIM1']),
]


def expandHero(n):
    c = Cmf(n)
    if not c.ok:
        raise Skip('c%d 파싱 실패: %s' % (n, c.why))
    idx = {nm: i for i, nm in enumerate(c.motNames)}
    c.beginExpand()

    tables = []
    for name, keys in CHAINS:
        ks = []
        for k in keys:
            full = 'PO_C%d_%s' % (n, k)
            if full not in idx:
                raise Skip('%s 없음' % full)
            ks.append(idx[full])
        seq = []
        for i, a in enumerate(ks):
            b = ks[(i + 1) % len(ks)]
            seq.append(a)
            if b == a:
                seq += [a] * 3
            else:
                for step in (1, 2, 3):
                    seq.append(c.getTween(a, b, step))
        assert len(seq) == HEROLOOP_FRAME, (name, len(seq))
        tables.append((name, seq))

    c.nameTweens()
    text = c.render()

    # 순환표를 파일 끝(#endif 앞)에 덧붙인다.
    lines = ['', 'enum {', '\tHEROLOOP_FRAME = %d,' % HEROLOOP_FRAME, '',
             '\tHEROLOOP_NEUTRAL = 0,', '\tHEROLOOP_WALK,', '\tHEROLOOP_RUN,', '\tHEROLOOP_SWIM,',
             '', '\tTOTALHEROLOOP', '};', '',
             '//60프레임용 순환표. 한 프레임에 한 칸씩 쓴다.',
             '//원본은 walkFrame[]으로 0,1,2,1 을 두 프레임씩 잡아 8프레임에 3포즈였다.',
             '//같은 0.267초를 16프레임 16포즈로 채운다.',
             'static const unsigned short c%dLoop60[] = {' % n]
    for name, seq in tables:
        lines.append('\t//%s' % name)
        for i in range(0, HEROLOOP_FRAME, 8):
            lines.append('\t' + ', '.join(c.newNames[m] for m in seq[i:i + 8]) + ',')
    lines += ['};', '']

    if 'HEROLOOP_FRAME' in text:
        raise Skip('이미 순환표가 있다')
    text = text.replace('#endif', '\n'.join(lines) + '#endif')
    io.open(c.path, 'w', encoding='utf-8-sig', newline='\r\n').write(text)
    return c, tables


if __name__ == '__main__':
    for n in [int(a) for a in sys.argv[1:]] or [0]:
        c, tables = expandHero(n)
        print('c%d : 모션 %d -> %d' % (n, c.totalMotion, len(c.newNames)))
        for name, seq in tables:
            print('  %-8s %s' % (name, ' '.join(c.newNames[m].replace('PO_C%d_' % n, '') for m in seq)))
