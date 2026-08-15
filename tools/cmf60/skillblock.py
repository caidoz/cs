# -*- coding: utf-8 -*-
"""스킬 블록 하나를 주석 마커 기준으로 잡아 규칙에 맞게 다시 깐다.

규칙1. 공격판정이 있는 모션은 정확히 1프레임.
       플레이어->몬스터는 재타격 가드가 없어 판정 프레임 하나가 곧 1히트다.
규칙2. 판정이 없는 모션은 최소 2프레임.
       보간모션이 한 프레임만 스쳐 가면 눈에 안 남고 동작만 빨라 보인다.

블록 경계는 SkillDef.h의 START/CNT로 계산하지 않고 소스의 주석 마커와
_END 종료행으로 잡는다. 계산으로 자르면 죽은 #ifdef 가지 때문에 몇 행씩
어긋나고, 그 상태로 덮어쓰면 데이터가 깨진다.
"""
import io, re, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from skillfix import ROW, relayout, hitMotions

HERO_PATH = 'Classes/Data/HeroData.h'
SKILL_PATH = 'Classes/Def/SkillDef.h'


def findBlock(lines, marker):
    """마커 다음의 데이터 행을 _END까지 모은다. (줄번호 리스트, 행 리스트)"""
    start = next(k for k, l in enumerate(lines) if marker in l)
    nums, rows = [], []
    for k in range(start, len(lines)):
        m = ROW.match(lines[k])
        if not m:
            continue
        nums.append(k)
        rows.append([m.group(2), m.group(4), m.group(6), m.group(8)])
        if m.group(6) in ('_END', '_ENDTOFALL'):
            break
    return nums, rows


def render(rows):
    out = []
    for i, r in enumerate(rows):
        out.append('\t%s, %s, %s,\t%s,//%d' % (r[0], r[1], r[2], r[3], i))
    return out


def apply(marker, cmfNum, cntName, dryRun=False):
    lines = io.open(HERO_PATH, encoding='utf-8-sig').read().split('\n')
    hit = hitMotions(cmfNum)

    nums, rows = findBlock(lines, marker)
    new, remap, lost = relayout(rows, hit)

    hitsOld = sum(1 for r in rows if r[0] in hit)
    hitsNew = sum(1 for r in new if r[0] in hit)
    print('%s : %d행 -> %d행,  타수 %d -> %d,  명령손실 %d'
          % (marker, len(rows), len(new), hitsOld, hitsNew, len(lost)))
    for idx, r in lost:
        print('   잘린 행 +%d 의 명령을 잃음 : %s' % (idx, r))

    #꼬리 길이가 그대로여야 skillClosingFrame의 오프셋을 안 건드린다.
    def tail(rs):
        n = 0
        for r in reversed(rs):
            if r[0] != rs[-1][0] and n:
                break
            n += 1
        return n
    print('   꼬리(마지막 런) %d -> %d' % (tail(rows), tail(new)))

    if dryRun:
        return

    lines[nums[0]:nums[-1] + 1] = render(new)
    io.open(HERO_PATH, 'w', encoding='utf-8-sig',
            newline='\r\n').write('\n'.join(lines))

    #CNT 상수를 새 행수로 맞춘다.
    sk = io.open(SKILL_PATH, encoding='utf-8-sig').read()
    pat = re.compile(r'(\b%s\s*=\s*)(\d+)' % cntName)
    m = pat.search(sk)
    if not m:
        raise KeyError(cntName)
    print('   %s %s -> %d' % (cntName, m.group(2), len(new)))
    sk = pat.sub(lambda mm: mm.group(1) + str(len(new)), sk, count=1)
    io.open(SKILL_PATH, 'w', encoding='utf-8-sig',
            newline='\r\n').write(sk)


if __name__ == '__main__':
    dry = '--dry' in sys.argv
    apply(sys.argv[1], int(sys.argv[2]), sys.argv[3], dry)
