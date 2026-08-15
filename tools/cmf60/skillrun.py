# -*- coding: utf-8 -*-
"""히어로 스킬표 전체를 규칙에 맞게 다시 깐다.

skillfix.relayout의 규칙을 모든 블록에 적용하고, 딸린 상수까지 같이 맞춘다.
 - SkillDef.h의 *_CNT (식으로 정의된 것은 마지막 항을 조정)
 - HeroData.h의 *SkillClosingFrame (블록 끝에서 몇 번째인지 다시 계산)

블록 경계는 SkillDef.h의 START/CNT로 잡되, 각 블록의 마지막 행이 종료 명령
(_END, _ENDTOFALL, _ADDMON, _USERING, _ADDBUFF ...)인지 반드시 검사한다.
하나라도 어긋나면 아무것도 쓰지 않고 멈춘다. 어긋난 채로 덮어쓰면
데이터가 통째로 깨진다.
"""
import io, re, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from skillfix import (ROW, HERO, skillEnv, blocks, relayout,
                      arrayRows, parse, hitMotions)

HERO_PATH = 'Classes/Data/HeroData.h'
SKILL_PATH = 'Classes/Def/SkillDef.h'

KEEPLONG = 7	#이만큼 이상 물고 있는 판정은 스킬의 설계라 안 건드린다

#블록이 통째로 2배 가까이 길어져 따로 정해야 하는 것들은 건너뛴다.
SKIP = ('DIANA_SKILL_GUIDEDSHOT',)


def rewriteBlock(lines, rowLines, new, srcOf):
    """블록을 다시 쓰되 데이터 행만 갈아끼운다.

    rowLines는 이 블록 데이터 행들의 줄번호다. 그 사이에 낀 #ifdef/#else/
    #endif와 주석은 손대지 않고 제자리에 남긴다. 줄 범위를 통째로 바꾸면
    지시문이 지워져 #if/#endif 짝이 깨진다(C1070).
    """
    #옛 행 자리별로 새 행을 모은다.
    bucket = {}
    for k, src in enumerate(srcOf):
        bucket.setdefault(src, []).append(new[k])

    rowSet = dict((ln, i) for i, ln in enumerate(rowLines))
    out, num = [], 0
    for ln in range(rowLines[0], rowLines[-1] + 1):
        if ln in rowSet:
            for r in bucket.get(rowSet[ln], []):
                out.append('\t%s, %s, %s,\t%s,//%d' % (r[0], r[1], r[2], r[3], num))
                num += 1
        else:
            out.append(lines[ln])	#지시문/주석/빈 줄은 그대로
    return out


def bumpCnt(sk, cntName, delta, env):
    """CNT 상수를 delta만큼 키운다. 식이면 마지막 항을 조정한다."""
    m = re.search(r'^(\s*%s\s*=\s*)([^,]+)(,.*)$' % cntName, sk, re.M)
    if not m:
        raise KeyError(cntName)
    head, expr, tailPart = m.group(1), m.group(2), m.group(3)
    body = expr.split('//')[0].rstrip()

    lit = re.search(r'(\d+)\s*$', body)
    if lit:
        newBody = body[:lit.start(1)] + str(int(lit.group(1)) + delta)
        return sk[:m.start()] + head + newBody + expr[len(body):] + tailPart + sk[m.end():], None

    sym = re.search(r'([A-Z0-9_]+)\s*$', body)
    if not sym:
        raise ValueError('%s : 식을 못 고침 (%s)' % (cntName, body))
    return sk, sym.group(1)	#심볼 쪽을 대신 고쳐야 한다


def bumpSymbol(sk, name, delta):
    m = re.search(r'^(\s*%s\s*=\s*)(\d+)' % name, sk, re.M)
    if not m:
        raise KeyError(name)
    return sk[:m.start()] + m.group(1) + str(int(m.group(2)) + delta) + sk[m.end():]


def run(dryRun=False):
    env = skillEnv()
    text = io.open(HERO_PATH, encoding='utf-8-sig').read()
    lines = text.split('\n')

    plan = []	#(hero, name, lineFrom, lineTo, newRows, oldCnt, remap)

    for hero, n in HERO:
        hit = hitMotions(n)
        nums = arrayRows(lines, hero + 'SkillMotion')
        rows = parse(lines, nums)

        for name, start, cnt in blocks(env, hero):
            if cnt == 0 or name in SKIP:
                continue
            if start + cnt > len(rows):
                raise ValueError('%s 범위 초과' % name)
            #경계 검증: 마지막 행은 반드시 종료 명령이어야 한다.
            last = rows[start + cnt - 1]
            if not last[2].startswith('_'):
                raise ValueError('%s 경계 어긋남: 끝행 %s %s' % (name, last[0], last[2]))

            seg = rows[start:start + cnt]
            new, remap, lost, srcOf = relayout(seg, hit, KEEPLONG)
            if len(new) == cnt and not lost:
                continue
            plan.append((hero, name, nums[start:start + cnt],
                         new, cnt, remap, lost, srcOf))

    total = 0
    for hero, name, rowLines, new, cnt, remap, lost, srcOf in plan:
        print('  %-40s %4d -> %4d%s' % (name, cnt, len(new),
                                        '   명령손실 %d' % len(lost) if lost else ''))
        total += 1
    print('바꿀 블록 %d개' % total)

    if dryRun:
        return

    #뒤쪽 블록부터 갈아끼워야 앞쪽 줄번호가 안 밀린다.
    for hero, name, rowLines, new, cnt, remap, lost, srcOf in sorted(
            plan, key=lambda p: -p[2][0]):
        lines[rowLines[0]:rowLines[-1] + 1] = rewriteBlock(lines, rowLines, new, srcOf)
    io.open(HERO_PATH, 'w', encoding='utf-8-sig',
            newline='\r\n').write('\n'.join(lines))

    #CNT 상수
    sk = io.open(SKILL_PATH, encoding='utf-8-sig').read()
    for hero, name, rowLines, new, cnt, remap, lost, srcOf in plan:
        delta = len(new) - cnt
        if delta == 0:
            continue
        sk, sym = bumpCnt(sk, name + '_CNT', delta, env)
        if sym:
            sk = bumpSymbol(sk, sym, delta)
    io.open(SKILL_PATH, 'w', encoding='utf-8-sig',
            newline='\r\n').write(sk)

    #ClosingFrame 오프셋
    hd = io.open(HERO_PATH, encoding='utf-8-sig').read()
    for hero, name, rowLines, new, cnt, remap, lost, srcOf in plan:
        pat = re.compile(r'(%s_START\s*\+\s*%s_CNT\s*-\s*)(\d+)' % (name, name))
        m = pat.search(hd)
        if not m:
            continue
        oldN = int(m.group(2))
        oldIdx = cnt - oldN
        newIdx = remap.get(oldIdx, len(new) - 1)
        newN = len(new) - newIdx
        if newN != oldN:
            print('  %s closingFrame -%d -> -%d' % (name, oldN, newN))
        hd = hd[:m.start()] + m.group(1) + str(newN) + hd[m.end():]
    io.open(HERO_PATH, 'w', encoding='utf-8-sig', newline='\r\n').write(hd)


if __name__ == '__main__':
    run('--dry' in sys.argv)
