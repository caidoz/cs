# -*- coding: utf-8 -*-
"""열거값을 id 표로 박제하고, 데이터 배열의 길이가 맞는지 검증한다.

[왜 필요한가]
지금 콘텐츠의 정체성은 "열거 안에서의 위치"다. 몬스터 하나를 가운데 끼워
넣으면 그 뒤가 전부 한 칸씩 밀리는데, 그 번호는 이미 세이브 파일과 서버 DB에
박혀 있다(crew_slot.crew_type, battle_enemy.enemy_type, inventory.detail).
즉 번호는 이제 되돌릴 수 없는 계약이다.

이 도구는 그 계약을 문서로 고정한다. 여기서 뽑은 표가 기준이 되고,
앞으로는 중간 삽입 금지 / 번호 재사용 금지만 지키면 된다.

[어떻게 값을 아는가]
C 열거는 암묵적 증가, 명시적 대입, 다른 열거 참조, #ifdef 분기가 섞여 있다.
파이썬으로 그 의미론을 흉내내면 언젠가 반드시 어긋난다. 그래서 흉내내지 않고
컴파일러에게 직접 묻는다. 이름만 긁어서 값을 찍는 작은 프로그램을 만들고,
그것을 실제 컴파일러로 빌드해 실행한다. 정의상 틀릴 수가 없다.

    python tools/content/dump_ids.py            # 표 생성 + 검증
    python tools/content/dump_ids.py --check    # 검증만
"""
import argparse
import os
import re
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CLASSES = os.path.join(ROOT, 'Classes')
OUT_DIR = os.path.join(ROOT, 'content', 'ids')

VS_CANDIDATES = [
    r'C:\Program Files\Microsoft Visual Studio\2022\Community',
    r'C:\Program Files\Microsoft Visual Studio\2022\Professional',
    r'C:\Program Files\Microsoft Visual Studio\2022\Enterprise',
    r'C:\Program Files (x86)\Microsoft Visual Studio\2019\Community',
]

# 어떤 구간을 어떤 콘텐츠 그룹으로 볼 것인가.
#
# 값의 범위로 거르면 안 된다. 열거 블록 하나에 여러 갈래가 섞여 있어서
# 값이 겹치는 남남끼리 같은 표에 들어온다(ATTACKTYPE_TILE = TOTALOBJECT 처럼
# 명시적 대입으로 남의 번호대에 끼어드는 것도 있다).
#
# 그래서 "소스에 적힌 순서대로 start부터 end 직전까지"를 한 구간으로 본다.
# 이게 사람이 그 목록을 읽는 방식과 같다.
GROUPS = [
    {'name': 'enemy',  'start': 'ENEMY_SNAIL',         'end': 'TOTALENEMY'},
    {'name': 'crew',   'start': 'CREW_BOY',            'end': 'TOTAL_CREW'},
    {'name': 'castle', 'start': 'CASTLE_TOLEM',        'end': 'TOTALCASTLE'},
    {'name': 'skill',  'start': 'SKILL_COMMON_ROBIN1', 'end': 'TOTAL_SKILL'},
]


def strip_comments(text):
    text = re.sub(r'/\*.*?\*/', '', text, flags=re.S)
    text = re.sub(r'//[^\n]*', '', text)
    return text


def header_files():
    out = []

    for base in [os.path.join(CLASSES, 'Def'), os.path.join(CLASSES, 'Config')]:
        if os.path.isdir(base):
            for n in sorted(os.listdir(base)):
                if n.endswith('.h'):
                    out.append(os.path.join(base, n))

    out.append(os.path.join(CLASSES, 'Def.h'))
    return out


def scan_enums():
    """열거 블록을 찾아 (블록태그, [멤버이름...]) 목록을 돌려준다.

    값은 여기서 계산하지 않는다. 이름만 모은다.
    """
    blocks = []

    for path in header_files():
        with open(path, encoding='utf-8-sig') as fp:
            raw = fp.read()

        text = strip_comments(raw)
        pos = 0

        while True:
            m = re.compile(r'\benum\b\s*(_?\w+)?\s*\{', re.S).search(text, pos)

            if not m:
                break

            tag = m.group(1) or ''
            depth = 1
            i = m.end()

            while i < len(text) and depth:
                if text[i] == '{':
                    depth += 1
                elif text[i] == '}':
                    depth -= 1
                i += 1

            body = text[m.end():i - 1]
            names = []

            # 멤버는 "이름," 또는 "이름 = 식," 꼴이다. 식 안의 이름은 세지 않도록
            # 콤마로 자른 뒤 각 조각의 맨 앞 식별자만 본다.
            for part in re.split(r',', body):
                part = part.strip()

                if not part:
                    continue

                mm = re.match(r'^([A-Za-z_]\w*)\s*(=|$)', part)

                if mm:
                    names.append(mm.group(1))

            blocks.append((tag, names, os.path.basename(path)))
            pos = i

    return blocks


def find_vs():
    #맥/리눅스에는 Visual Studio 가 없다. 왜 안 되는지 분명히 알려준다.
    #조용히 이상한 오류를 뱉는 것보다 낫다.
    #
    #팩을 내는 make_pack.py 는 tools/content/cc.py 를 써서 양쪽에서 돈다.
    #여기를 거치는 도구들(check_pack, content_table, pack_cmf, pack_map,
    #freeze_cmfvar, verify_*)은 아직 윈도우 전용이다. 맥에서 필요해지면
    #cc.py 를 쓰도록 하나씩 옮기면 된다.
    if os.name != 'nt':
        sys.stderr.write(
            '이 도구는 아직 윈도우 전용이다. cl.exe 로 소스를 컴파일해서\n'
            '값을 받아오기 때문이다.\n'
            '팩을 다시 내는 것(build_pack.py)은 맥에서도 된다.\n')
        return None

    for p in VS_CANDIDATES:
        bat = os.path.join(p, r'VC\Auxiliary\Build\vcvars32.bat')

        if os.path.isfile(bat):
            return bat

    return None


def ask_compiler(names):
    """이름 목록의 실제 값을 컴파일러에게 물어본다. {이름: 값} 을 돌려준다."""
    vcvars = find_vs()

    if not vcvars:
        sys.stderr.write('Visual Studio를 못 찾았다. VS_CANDIDATES에 경로를 추가하라.\n')
        return None

    work = tempfile.mkdtemp(prefix='ids_')
    src = os.path.join(work, 'probe.cpp')

    with open(src, 'w', encoding='utf-8') as fp:
        fp.write('#include "Def.h"\n#include <stdio.h>\n')
        fp.write('int main() {\n')

        for n in names:
            # long long로 찍는다. 열거값이 int를 넘는 것이 있을 수 있다.
            fp.write('    printf("%s\\t%%lld\\n", (long long)(%s));\n' % (n, n))

        fp.write('    return 0;\n}\n')

    cmd = ('call "%s" >nul 2>&1 && cl /nologo /EHsc /utf-8 /W0 /I "%s" "%s" '
           '/Fe:"%s" /Fo:"%s" >nul' %
           (vcvars, CLASSES, src, os.path.join(work, 'probe.exe'),
            os.path.join(work, 'probe.obj')))

    r = subprocess.run(cmd, shell=True, cwd=work,
                       stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    exe = os.path.join(work, 'probe.exe')

    if not os.path.isfile(exe):
        sys.stderr.write('probe 빌드 실패:\n%s\n' % r.stdout.decode('utf-8', 'replace'))
        return None

    out = subprocess.run([exe], stdout=subprocess.PIPE).stdout.decode('utf-8', 'replace')
    vals = {}

    for line in out.splitlines():
        if '\t' not in line:
            continue

        k, v = line.split('\t', 1)
        vals[k] = int(v)

    return vals


def count_array_elems(text, decl_name):
    """const 배열의 초기값 개수를 센다. 중첩 중괄호는 한 덩어리로 본다."""
    #split_data.py 가 정의를 옮기면서 이름 뒤에 _builtin 을 붙였다.
    #(포인터가 원래 이름을 쓰고, 내장 기본값이 _builtin 이 된다)
    for nm in (decl_name, decl_name + '_builtin'):
        m = re.search(r'\b%s\s*\[[^;{]*\]\s*(\[[^;{]*\]\s*)?=\s*\{'
                      % re.escape(nm), text)

        if m:
            break

    if not m:
        return None

    i = m.end()
    depth = 1
    count = 0
    seen = False

    while i < len(text) and depth:
        c = text[i]

        if c == '{':
            depth += 1
        elif c == '}':
            depth -= 1

            if depth == 0:
                break
        elif c == ',' and depth == 1:
            count += 1
            seen = False
            i += 1
            continue

        if depth >= 1 and not c.isspace():
            seen = True

        i += 1

    # 마지막 원소 뒤에 콤마가 없으면 하나 더 있다.
    return count + (1 if seen else 0)


def read_table(path):
    """이미 박제된 표를 읽어 {id: 이름} 으로 돌려준다."""
    out = {}

    if not os.path.isfile(path):
        return None

    with open(path, encoding='utf-8') as fp:
        for line in fp:
            line = line.rstrip('\n')

            if not line or line.startswith('#') or line.startswith('id\t'):
                continue

            f = line.split('\t')

            if len(f) >= 2:
                out[int(f[0])] = f[1]

    return out


def compare(old, new):
    """박제된 표와 지금 소스를 비교한다.

    돌려주는 것은 (바뀐 것, 사라진 것, 새로 붙은 것).
    "바뀐 것"이 하나라도 있으면 이미 나간 세이브가 깨진다.
    """
    changed = []
    removed = []
    added = []

    for i in sorted(set(old) | set(new)):
        a = old.get(i)
        b = new.get(i)

        if a is None:
            added.append((i, b))
        elif b is None:
            removed.append((i, a))
        elif a != b:
            changed.append((i, a, b))

    return changed, removed, added


def data_text():
    out = []
    d = os.path.join(CLASSES, 'Data')

    for n in sorted(os.listdir(d)):
        #정의는 split_data.py 가 .cpp 로 옮겼다. 헤더에는 extern 선언만
        #남아 있으므로 .cpp 도 같이 읽어야 원소를 셀 수 있다.
        if n.endswith('.h') or n.endswith('.cpp'):
            with open(os.path.join(d, n), encoding='utf-8-sig') as fp:
                out.append((n, strip_comments(fp.read())))

    return out


# 검증할 배열들. (배열이름, 기대 길이 식)
# 식은 값 사전으로 eval한다.
VERIFY = [
    ('enemyData',          'TOTALENEMY * ENEMYDATASIZE'),
    ('enemyStatInfo',      'TOTALENEMY * 3'),
    ('enemyZoom',          'TOTALENEMY'),
    ('enemyIconZoom',      'TOTALENEMY'),
    ('enemyBossZoom',      'TOTALENEMY'),
    ('enemyAttackPattern', 'TOTALENEMY * (2 + ATTACKPATTERNDATASIZE * 3)'),
    ('crewData',           'TOTAL_CREW * CREWDATASIZE'),
    ('skillData',          'TOTAL_SKILL * SKILLDATASIZE'),
]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--check', action='store_true', help='표를 만들지 않고 검증만')
    ap.add_argument('--accept', action='store_true',
                    help='번호가 바뀐 것을 알면서도 표를 갱신한다')
    args = ap.parse_args()

    drift = 0
    blocks = scan_enums()

    # 각 그룹의 구간을 소스 순서로 잘라낸다.
    for g in GROUPS:
        g['members'] = []
        g['source'] = None

        for tag, names, src in blocks:
            if g['start'] not in names or g['end'] not in names:
                continue

            a = names.index(g['start'])
            b = names.index(g['end'], a)

            if b <= a:
                continue

            g['members'] = names[a:b]
            g['source'] = src
            break

    # 필요한 이름만 컴파일러에 묻는다. 전부 찍으면 probe.cpp가 수만 줄이 된다.
    wanted = set()

    for g in GROUPS:
        wanted.add(g['end'])
        wanted.update(g['members'])

    for _name, expr in VERIFY:
        wanted.update(re.findall(r'[A-Za-z_]\w*', expr))

    wanted = sorted(wanted)
    print('이름 %d개의 값을 컴파일러에게 묻는다...' % len(wanted))

    vals = ask_compiler(wanted)

    if vals is None:
        return 1

    print('받았다: %d개\n' % len(vals))

    # ---- id 표 ----
    if not args.check:
        os.makedirs(OUT_DIR, exist_ok=True)

    for g in GROUPS:
        total = vals.get(g['end'])

        if total is None or not g['members']:
            print('%-8s : 구간을 못 찾았다 (%s .. %s)' % (g['name'], g['start'], g['end']))
            continue

        rows = {}
        alias = {}

        for n in g['members']:
            v = vals.get(n)

            if v is None:
                continue

            if v in rows:
                # 같은 번호를 가리키는 다른 이름. 대표는 소스에서 먼저 나온 것.
                alias.setdefault(v, []).append(n)
            else:
                rows[v] = n

        ids = sorted(rows)
        first = ids[0] if ids else 0
        gap = [v for v in range(first, total) if v not in rows]

        print('%-8s : %s  id %d..%d  이름 %d개  빈 번호 %d개'
              % (g['name'], g['source'], first, total - 1, len(ids), len(gap)))

        if alias:
            for v in sorted(alias):
                print('           별칭 %d : %s (대표 %s)'
                      % (v, ', '.join(alias[v]), rows[v]))

        if gap:
            print('           빈 번호: %s%s'
                  % (', '.join(str(v) for v in gap[:10]),
                     ' ...' if len(gap) > 10 else ''))

        path = os.path.join(OUT_DIR, g['name'] + '.tsv')
        old = read_table(path)

        # ---- 박제된 표와 대조 ----
        # 이 비교가 이 도구의 존재 이유다. 번호가 한 칸이라도 밀리면
        # 이미 나간 세이브와 서버 DB의 값이 다른 콘텐츠를 가리키게 된다.
        if old is not None:
            changed, removed, added = compare(old, rows)

            for i, a, b in changed:
                print('           !! id %d 가 %s 에서 %s 로 바뀌었다' % (i, a, b))
                drift += 1

            for i, a in removed:
                print('           !! id %d (%s) 가 사라졌다' % (i, a))
                drift += 1

            if added:
                lo = min(i for i, _n in added)

                if lo < max(old):
                    # 끝이 아니라 가운데에 끼어들었다. 뒤가 전부 밀린다.
                    print('           !! id %d 가 가운데에 끼어들었다(끝은 %d)'
                          % (lo, max(old)))
                    drift += 1
                else:
                    print('           + 뒤에 %d개 추가됨 (%d..%d) - 안전'
                          % (len(added), lo, max(i for i, _n in added)))

        if args.check:
            continue

        if drift and not args.accept:
            print('           표를 덮어쓰지 않는다. 의도한 것이면 --accept')
            continue

        with open(path, 'w', encoding='utf-8', newline='\n') as fp:
            fp.write('#이 표는 계약이다. 번호를 바꾸거나 재사용하지 말 것.\n')
            fp.write('#세이브 파일과 서버 DB에 이 번호가 그대로 들어 있다.\n')
            fp.write('#새 콘텐츠는 항상 맨 끝에 붙인다. 폐기는 행을 지우지 말고 alive=0으로.\n')
            fp.write('id\tname\talias\talive\n')

            for v in ids:
                fp.write('%d\t%s\t%s\t1\n' % (v, rows[v], ','.join(alias.get(v, []))))

        print('           -> %s' % os.path.relpath(path, ROOT))

    # ---- 배열 길이 검증 ----
    print('\n배열 길이 검증')
    bad = 0

    for name, expr in VERIFY:
        want = None

        try:
            want = eval(expr, {'__builtins__': {}}, vals)
        except Exception:
            print('  %-20s 기대값을 못 구했다 (%s)' % (name, expr))
            continue

        got = None

        for fn, txt in data_text():
            got = count_array_elems(txt, name)

            if got is not None:
                break

        if got is None:
            print('  %-20s 배열을 못 찾았다' % name)
            continue

        ok = (got == want)

        if not ok:
            bad += 1

        print('  %-20s %s  기대 %d  실제 %d%s'
              % (name, 'OK ' if ok else '틀림', want, got,
                 '' if ok else '   <-- %+d' % (got - want)))

    if bad:
        print('\n%d개 배열의 길이가 안 맞는다. 콘텐츠가 밀려 있을 수 있다.' % bad)

    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main())
