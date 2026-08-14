# -*- coding: utf-8 -*-
"""히어로 스킬 프레임표(robinSkillMotion 등)를 60프레임용으로 2배로 늘린다.

한 행이 한 프레임이다. 행 수를 2배로 늘리면 60프레임에서 원래(30프레임) 속도가 된다.
모션 칸은 c0.h에 미리 만들어 둔 중간모션으로 채우고,
이동/효과/사운드 칸은 일회성 명령이라 짝의 앞 행에만 둔다.
누적형 효과(_DXDECREASE4)는 이 스크립트로 처리하지 않는다. 대시에서 손으로 처리했다.
"""
import io, re, os, sys

ROOT = r'C:\Users\polyp\Desktop\CP\cs'
HERO = os.path.join(ROOT, 'Classes', 'Data', 'HeroData.h')
DEFS = {'ATTACK_INIT_DELAY': True, 'ROBINDEFAULTATTACKSTING': True}

TERMINATOR = ('_END', '_ENDTOFALL')


def activeRows(body):
    """전처리기 분기를 반영해 살아 있는 행만, 원문과 함께 돌려준다."""
    stack, out = [True], []
    for i, line in enumerate(body.split('\n')):
        t = line.strip()
        d = re.match(r'#\s*(\w+)\s*(\w+)?', t)
        if d:
            k = d.group(1)
            if k == 'ifdef':
                stack.append(stack[-1] and DEFS.get(d.group(2), False))
            elif k == 'ifndef':
                stack.append(stack[-1] and not DEFS.get(d.group(2), False))
            elif k == 'else':
                top = stack.pop()
                stack.append(stack[-1] and not top)
            elif k == 'endif':
                stack.pop()
            continue
        if not stack[-1] or not t or t.startswith('//'):
            continue
        out.append((i, t))
    return out


def cells(row):
    """'PO_C0_A0, 0, _END,\t0,//12' -> (['PO_C0_A0','0','_END','0'], '//12')"""
    m = re.match(r'^(.*?),\s*(//.*)?$', row.strip())
    body = row.split('//')[0]
    cmt = ('//' + row.split('//', 1)[1]) if '//' in row else ''
    parts = [p.strip() for p in body.split(',') if p.strip() != '']
    return parts, cmt


def motionNames(path):
    s = io.open(path, encoding='utf-8-sig').read()
    head = re.search(r'typedef enum _C0_DEF \{(.*?)\n\} C0_DEF;', s, re.S).group(1)
    head = head.split('TOTALC0MOTION')[0]
    return set(re.findall(r'\b(PO_C0_[A-Z0-9_]+)\s*=\s*\d+', head))


NAMES = motionNames(os.path.join(ROOT, 'Classes', 'Cmf', 'c0.h'))


def tweenName(a, k):
    """a에서 다음 키모션으로 가는 k/4 지점 중간모션. 없으면 None."""
    nm = '%s_%d' % (a, k)
    return nm if nm in NAMES else None


def expandBlock(rows):
    """rows = [(cells, comment), ...]. 2배로 늘린 새 행 목록을 돌려준다."""
    n = len(rows)
    # 모션이 같은 구간(런)으로 묶는다
    runs = []
    for i, (c, _) in enumerate(rows):
        if runs and runs[-1][0] == c[0]:
            runs[-1][2] = i
        else:
            runs.append([c[0], i, i])

    motions = []          # 새 프레임별 모션 이름
    for ri, (mo, s, e) in enumerate(runs):
        hold = e - s + 1
        H = hold * 2
        nxt = runs[ri + 1][0] if ri + 1 < len(runs) else None
        # 다음 키모션으로 가는 중간모션이 실제로 있을 때만 4등분한다
        tw = [tweenName(mo, k) for k in (1, 2, 3)] if nxt else [None] * 3
        if not all(tw):
            motions += [mo] * H
            continue
        b = [int(k * H / 4.0 + 0.5) for k in range(5)]
        for k in range(4):
            span = b[k + 1] - b[k]
            if span > 0:
                motions += [mo if k == 0 else tw[k - 1]] * span
    assert len(motions) == n * 2, (len(motions), n * 2)

    out = []
    for i, (c, cmt) in enumerate(rows):
        term = c[0] == '0' and len(c) > 2 and c[2] in TERMINATOR
        if term:
            # 종료행은 뒤쪽에 둔다. 앞 행은 직전 모션을 한 프레임 더 잡아 준다.
            prev = motions[i * 2 - 1] if i else '0'
            out.append(([prev, '0', '0', '0'], '//%d' % (i * 2)))
            out.append((list(c), '//%d' % (i * 2 + 1)))
        else:
            out.append(([motions[i * 2]] + c[1:], '//%d' % (i * 2)))
            out.append(([motions[i * 2 + 1], '0', '0', '0'], '//%d' % (i * 2 + 1)))
    assert len(out) == n * 2
    return out


def render(rows):
    return ''.join('\t%s, %s, %s,\t%s,%s\n' % (c[0], c[1], c[2], c[3], cmt) for c, cmt in rows)
