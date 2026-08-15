# -*- coding: utf-8 -*-
"""히어로 스킬 프레임표를 두 규칙에 맞춘다.

규칙1. 공격판정이 있는 모션은 정확히 1프레임만 나온다.
       플레이어->몬스터 방향은 재타격 가드가 없어 판정 프레임 하나가 1히트다.
       한 방이 여러 대로 들어가면 데미지 예상치가 어긋난다.
       다만 KEEPLONG 이상 길게 물고 있는 판정은 그 자체가 스킬의 설계라
       손대지 않는다. 1프레임으로 줄이면 스킬이 통째로 무력해진다.
규칙2. 판정이 없는 모션은 최소 2프레임을 유지한다.
       60프레임 확장이 보간모션을 한 프레임씩만 끼워 넣어 눈에 안 남고
       동작만 빨라 보이던 것을 되돌린다.

이동/효과/사운드 칸은 한 번만 발동해야 하는 일회성 명령이라
늘린 행에는 복사하지 않고 0으로 둔다.
"""
import io, re, os, sys

HERO = [('robin', 0), ('diana', 1), ('maxx', 2)]

#이동/효과 칸에는 _JUMP2 | _DIROPPOSITE 처럼 OR로 묶은 값이 들어간다.
#\w+ 로 잡으면 그런 행을 통째로 놓쳐 블록 경계가 어긋난다.
ROW = re.compile(r'^(\s*)([A-Za-z_0-9]+)(\s*,\s*)([^,{}]+?)(\s*,\s*)([^,{}]+?)(\s*,\s*)([^,{}]+?)(\s*,)(.*)$')

#BuildConfig.h에서 켜져 있는 매크로. 죽은 #else 가지는 세면 안 된다.
DEFINED = ('ATTACK_INIT_DELAY', 'ROBINDEFAULTATTACKSTING')

#판정을 이만큼 이상 길게 물고 있는 런은 손대지 않는다.
KEEPLONG = 20


def aliveFilter(lines):
    """죽은 #ifdef 가지를 걸러 (줄번호, 줄) 을 흘려보낸다."""
    alive = [True]
    for i, line in enumerate(lines):
        s = line.strip()
        if s.startswith('#if'):
            on = any(d in s for d in DEFINED)
            if s.startswith('#ifndef'):
                on = not on
            alive.append(on)
            continue
        if s.startswith('#else'):
            alive[-1] = not alive[-1]
            continue
        if s.startswith('#endif'):
            if len(alive) > 1:
                alive.pop()
            continue
        if all(alive):
            yield i, line


def hitMotions(n):
    """c{n}.h에서 실제 공격박스(CS[6], CS[7])를 가진 모션 이름을 모은다."""
    txt = io.open('Classes/Cmf/c%d.h' % n, encoding='utf-8-sig').read()

    names = {}
    for m in re.finditer(r'\b(PO_C%d_[A-Za-z_0-9]+)\s*=\s*(\d+)\s*,' % n, txt):
        names[int(m.group(2))] = m.group(1)

    m = re.search(r'static const signed short c%dCS\[\]\s*=\s*\{' % n, txt)
    body = txt[m.end():]
    body = body[:body.index('};')]

    hit, idx = set(), 0
    for line in body.split('\n'):
        vals = [c for c in line.split('//')[0].split(',') if c.strip()]
        if len(vals) != 8:
            continue
        w = re.search(r'(-?\d+)', vals[6])
        h = re.search(r'(-?\d+)', vals[7])
        if (w and int(w.group(1))) or (h and int(h.group(1))):
            if idx in names:
                hit.add(names[idx])
        idx += 1
    return hit


def skillEnv():
    """SkillDef.h의 enum 값을 순서대로 계산한다.

    죽은 #ifdef 가지를 건너뛰어야 한다. ROBIN_ATTACK_DELAY 처럼 #else 쪽에도
    같은 이름이 있으면, 안 그러면 뒤에 나온 값이 앞을 덮어써서 CNT가
    통째로 어긋난다.
    """
    sk = io.open('Classes/Def/SkillDef.h', encoding='utf-8-sig').read()

    env = {}
    for _, line in aliveFilter(sk.split('\n')):
        m = re.match(r'^\s*([A-Z0-9_]+)\s*=\s*([^,]+),', line)
        if not m:
            continue
        expr = m.group(2).split('//')[0].strip()
        try:
            env[m.group(1)] = int(eval(expr, {}, dict(env)))
        except Exception:
            pass
    return env


def blocks(env, hero):
    """스킬 블록을 (이름, START, CNT) 로 뽑아 START 순으로 돌려준다.

    블록 이름은 히어로마다 _ATTACK_ 과 _SKILL_ 두 가지를 쓴다.
    """
    pres = (hero.upper() + '_ATTACK_', hero.upper() + '_SKILL_')
    out = []
    for k in env:
        if k.endswith('_START') and any(k.startswith(p) for p in pres):
            base = k[:-6]
            cnt = base + '_CNT'
            if cnt in env:
                out.append((base, env[k], env[cnt]))
    out.sort(key=lambda t: t[1])
    return out


def relayout(rows, hit, keepLong=KEEPLONG):
    """규칙에 맞게 런 길이를 다시 잡는다. rows는 (모션, xy, eff, snd) 리스트.

    돌려주는 것: 새 행 리스트, 옛 인덱스 -> 새 인덱스 표, 잃은 명령 목록,
    그리고 새 행이 어느 옛 행에서 왔는지 적은 표(srcOf).

    srcOf가 필요한 이유: 블록 안에는 #ifdef 같은 전처리기 줄이 섞여 있어서
    줄 범위를 통째로 갈아끼우면 지시문이 지워진다. 옛 행 자리마다 새 행을
    끼워 넣어야 지시문이 제자리에 남는다.
    """
    new, remap, lost, srcOf = [], {}, [], []
    i = 0
    while i < len(rows):
        j = i
        while j < len(rows) and rows[j][0] == rows[i][0]:
            j += 1
        old = j - i
        name = rows[i][0]

        #런 안에 첫 행 말고도 명령이 붙어 있으면 줄일 수 없다.
        #_WALKTOEND 처럼 매 프레임 상태를 보는 명령은 줄이면 검사가 사라진다.
        hasCmd = any(rows[i + k][1] != '0' or rows[i + k][2] != '0'
                     or rows[i + k][3] != '0' for k in range(1, old))

        if name == '0':
            want = old	#_END 같은 종료행은 그대로 둔다
        elif name in hit:
            #길게 물고 있는 판정은 그 자체가 설계다. 건드리지 않는다.
            want = old if (old >= keepLong or hasCmd) else 1
        else:
            want = max(2, old)

        base = len(new)
        for k in range(want):
            if k < old:
                new.append(list(rows[i + k]))	#원본 행은 명령까지 그대로
                srcOf.append(i + k)
            else:
                #늘린 행은 명령을 비운다. 복사하면 일회성 명령이 두 번 터진다.
                new.append([name, '0', '0', '0'])
                srcOf.append(i + old - 1)	#런의 마지막 원본 행에 붙인다

        #런이 줄어들어 잘려나간 행에 명령이 남아 있으면 조용히 잃으면 안 된다.
        for k in range(want, old):
            r = rows[i + k]
            if r[1] != '0' or r[2] != '0' or r[3] != '0':
                lost.append((i + k, r))

        for k in range(old):
            remap[i + k] = base + min(k, want - 1)
        i = j

    return new, remap, lost, srcOf


def arrayRows(lines, arr):
    """배열의 데이터 행 줄번호를 순서대로 모은다."""
    for k, l in enumerate(lines):
        if arr + '[' in l and '=' in l and '{' in l:
            break
    else:
        raise KeyError(arr)

    out, depth = [], 1
    for i, line in aliveFilter(lines[k + 1:]):
        depth += line.count('{') - line.count('}')
        if depth <= 0:
            break
        if ROW.match(line):
            out.append(k + 1 + i)
    return out


def parse(lines, nums):
    out = []
    for i in nums:
        m = ROW.match(lines[i])
        out.append([m.group(2), m.group(4), m.group(6), m.group(8)])
    return out


def analyze(keepLong=KEEPLONG):
    env = skillEnv()
    lines = io.open('Classes/Data/HeroData.h', encoding='utf-8-sig').read().split('\n')

    for hero, n in HERO:
        hit = hitMotions(n)
        nums = arrayRows(lines, hero + 'SkillMotion')
        rows = parse(lines, nums)
        print('=== %s : 배열 %d행, 판정모션 %d종 ===' % (hero, len(rows), len(hit)))

        grand = 0
        for name, start, cnt in blocks(env, hero):
            if start + cnt > len(rows):
                print('  %-40s 범위 초과 (start=%d cnt=%d)' % (name, start, cnt))
                continue
            seg = rows[start:start + cnt]
            new, remap, lost, srcOf = relayout(seg, hit, keepLong)
            grand += len(new)
            a = sum(1 for r in seg if r[0] in hit)
            b = sum(1 for r in new if r[0] in hit)
            print('  %-40s %4d -> %4d  타수 %3d -> %3d%s'
                  % (name, cnt, len(new), a, b,
                     ('   명령손실 %d' % len(lost)) if lost else ''))
            for idx, r in lost:
                print('        잘린 행 +%d : %s' % (idx, r))
        print('  합계 %d -> %d' % (len(rows), grand))
        print()


if __name__ == '__main__':
    keep = KEEPLONG
    for a in sys.argv[1:]:
        if a.isdigit():
            keep = int(a)
    analyze(keep)
