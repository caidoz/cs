# -*- coding: utf-8 -*-
"""콘텐츠 데이터를 한 행으로 모으고, 헤더를 그 표에서 생성한다.

[문제]
콘텐츠 하나의 정보가 여러 파일 여러 배열에 흩어져 있다. 몬스터 한 마리를
추가하려면 10곳에 같은 순서로 값을 끼워 넣어야 하는데, 하나를 빠뜨려도
컴파일은 그냥 된다. 그 상태로 나가면 그 배열부터 전부 한 칸씩 밀린 값을 읽는다.

[하는 일]
    extract  : 흩어진 값을 긁어 content/<이름>.tsv 한 장으로 만든다 (이주용)
    verify   : 헤더가 tsv와 맞는지 대조하고 값 규칙도 본다 (CI용)
    generate : tsv에서 헤더의 배열 본문을 다시 만든다

값은 계산하지 않고 소스에 적힌 글자 그대로 옮긴다. NPC_BOY_SKILL1 이나
TSIZE * 3 이 숫자로 바뀌면 사람이 못 읽는다.

배열 크기나 텍스트 시작 번호 같은 상수는 하드코딩하지 않는다. C 열거는
암묵적 증가와 명시적 대입이 섞여 있어서 손으로 적으면 언젠가 어긋난다.
컴파일러에게 물어본다(dump_ids.ask_compiler).

    python tools/content/content_table.py enemy verify
    python tools/content/content_table.py skill generate --write
    python tools/content/content_table.py --all verify
"""
import argparse
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import dump_ids

ROOT = dump_ids.ROOT
CLASSES = dump_ids.CLASSES

NULL = '\\N'        # 덤프 형식과 같다. "이 배열에 이 번호는 없다"

ZERO_RE = re.compile(r'^\s*(0|0\s*\*\s*_2X|false)\s*$')


def lv_cols(n):
    return ['lv%d' % (i + 1) for i in range(n)]


# 엔티티별 명세.
#   total      : 개수 상수 이름 (컴파일러에게 묻는다)
#   label_base : 이름 문자열이 textId 어디서 시작하는지 (없으면 라벨 없음)
#   id_table   : content/ids/*.tsv (열거 이름)
#   layout     : (배열이름, 파일, 한 개가 쓰는 칸수, 시작번호, 컬럼이름들)
#                시작번호는 정수이거나 상수 이름. 그 번호부터 배열이 시작한다.
#   rules      : (컬럼, 판정, 왜) - 어긋나면 게임이 죽거나 눈에 띄게 망가지는 것
SPECS = {
    # 몬스터. 이 배열들의 색인은 OBJECT.type 이라 0~2번은 히어로가 쓴다.
    'enemy': {
        'total': 'TOTALENEMY',
        'label_base': 'TEXT_MONSTERNAME_START',
        'id_table': 'enemy',
        'layout': [
            ('enemyData', 'EnemyData.h', 8, 0,
             ['cmf', 'star', 'move_handler', 'draw_handler',
              'add_hp', 'add_exp', 'xpos', 'ypos']),
            ('enemyStatInfo', 'EnemyData.h', 3, 0,
             ['stat_hp', 'stat_str', 'stat_def']),
            ('enemyZoom', 'EnemyData.h', 1, 0, ['zoom']),
            ('enemyIconZoom', 'EnemyData.h', 1, 0, ['icon_zoom']),
            ('enemyBossZoom', 'EnemyData.h', 1, 0, ['boss_zoom']),
            ('enemyAttackPattern', 'EnemyData.h', 20, 0,
             ['ap_kind', 'ap_cnt']
             + ['ap%d_%d' % (s, c) for s in range(3) for c in range(6)]),
            # crewPos의 5칸 중 코드가 읽는 것은 0번(대기 모션)과 1번(모션 장수)뿐이다.
            # 2, 3번은 전부 0이고 4번은 CASTLE_* 인데 읽는 곳이 없다. 칸을 줄이지는
            # 않는다. 줄이면 stride가 바뀌어 색인식을 전부 손대야 한다.
            ('crewPos', 'UIData.h', 5, 0,
             ['pose_motion', 'pose_frames', 'pose_x', 'pose_y', 'home_castle']),
            ('enemyBigIconPos', 'UIData.h', 3, 0,
             ['bigicon_motion', 'bigicon_x', 'bigicon_y']),
            ('enemySkillIconPos', 'UIData.h', 3, 0,
             ['skillicon_motion', 'skillicon_x', 'skillicon_y']),
            # 이것만 3번부터다. 몬스터 번호가 3부터라 그만큼 당겨 쓴다.
            ('monXYGap', 'HeroData.h', 2, 'ENEMY_SNAIL', ['gap_x', 'gap_y']),
        ],
        'rules': [
            ('pose_frames', lambda v: not ZERO_RE.match(v),
             '0이면 안 된다. "frame % crewPos[type*5+1]" 로 나눗셈에 쓰여서 0이면 죽는다'),
        ],
    },

    # 동료. 배열 하나뿐이지만 몬스터/스킬을 가리키는 표라 한눈에 봐야 한다.
    'crew': {
        'total': 'TOTAL_CREW',
        'label_base': None,
        'id_table': 'crew',
        'layout': [
            ('crewData', 'HeroData.h', 6, 0,
             ['enemy_type', 'str', 'skill1', 'skill2', 'skill3', 'card_bg']),
        ],
        'rules': [],
    },

    # 스킬. 몬스터 한 마리가 3개씩 쓰므로 몬스터를 추가하면 여기도 늘어난다.
    'skill': {
        'total': 'TOTAL_SKILL',
        'label_base': 'TEXT_SKILLNAME_COMMON_ROBIN1',
        'id_table': 'skill',
        'layout': [
            ('skillData', 'SkillData.h', 29, 0,
             ['kind', 'target', 'obj_info', 'obj_detail', 'r1', 'r2']
             + lv_cols(15)
             + ['r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'icon', 'grade']),
        ],
        'rules': [],
    },
}


# ---------------------------------------------------------------- 소스 읽기

def read(path):
    # newline=''를 빼면 파이썬이 읽을 때 CRLF를 LF로 바꾼다. 그대로 다시 쓰면
    # 파일 전체의 줄바꿈이 바뀌어서, 값은 그대로인데 diff가 통째로 뒤집힌다.
    with open(path, encoding='utf-8-sig', newline='') as fp:
        return fp.read()


def split_elems(text, start):
    """중괄호 하나의 내용을 원소 목록으로 자른다.

    문자열, 문자, 주석, 중첩 중괄호를 건너뛴다. 글자 그대로 돌려준다.
    """
    out = []
    cur = []
    depth = 1
    i = start

    while i < len(text):
        c = text[i]

        if c == '/' and i + 1 < len(text) and text[i + 1] == '/':
            j = text.find('\n', i)
            i = len(text) if j < 0 else j
            continue

        if c == '/' and i + 1 < len(text) and text[i + 1] == '*':
            j = text.find('*/', i)
            i = len(text) if j < 0 else j + 2
            continue

        if c in '"\'':
            q = c
            j = i + 1

            while j < len(text):
                if text[j] == '\\':
                    j += 2
                    continue

                if text[j] == q:
                    break

                j += 1

            cur.append(text[i:j + 1])
            i = j + 1
            continue

        if c == '{':
            depth += 1
        elif c == '}':
            depth -= 1

            if depth == 0:
                break
        elif c == ',' and depth == 1:
            out.append(''.join(cur).strip())
            cur = []
            i += 1
            continue

        cur.append(c)
        i += 1

    tail = ''.join(cur).strip()

    if tail:
        out.append(tail)

    return out, i


def find_decl(text, name):
    """배열 선언의 여는 중괄호 바로 뒤 위치. 없으면 None.

    주석 처리된 선언을 물면 안 된다. HeroData.h에는 crewData의 옛 선언이
    //const int crewData[TOTAL_CREW * CREWDATASIZE] = { 로 남아 있는데,
    그걸 물면 닫는 중괄호를 못 찾아 뒤에 오는 배열들까지 통째로 삼킨다.
    """
    pat = re.compile(r'\b%s\s*\[[^;{]*\]\s*(\[[^;{]*\]\s*)?=\s*\{' % re.escape(name))

    for m in pat.finditer(text):
        line_start = text.rfind('\n', 0, m.start()) + 1

        if '//' in text[line_start:m.start()]:
            continue

        return m.end()

    return None


def parse_array(text, name):
    at = find_decl(text, name)

    if at is None:
        return None

    elems, _end = split_elems(text, at)
    return elems


def find_body(text, name):
    at = find_decl(text, name)

    if at is None:
        return None

    _elems, end = split_elems(text, at)
    return at, end


# ------------------------------------------------------- 전처리 분기 걷어내기

def macro_names(text):
    return sorted(set(re.findall(r'^\s*#\s*if(?:n)?def\s+(\w+)', text, re.M)))


def ask_defined(names):
    """각 매크로가 실제로 정의돼 있는지 컴파일러에게 묻는다.

    Text.h에는 #ifdef 분기가 70곳 넘게 있다. 양쪽 가지를 다 세면 원소 번호가
    통째로 밀려서 엉뚱한 문자열을 집는다.
    """
    if not names:
        return {}

    vcvars = dump_ids.find_vs()

    if not vcvars:
        return {}

    import subprocess
    import tempfile

    work = tempfile.mkdtemp(prefix='defs_')
    src = os.path.join(work, 'probe.cpp')

    with open(src, 'w', encoding='utf-8') as fp:
        fp.write('#include "Def.h"\n#include <stdio.h>\nint main(){\n')

        for n in names:
            fp.write('#ifdef %s\n    printf("%s\\t1\\n");\n#else\n'
                     '    printf("%s\\t0\\n");\n#endif\n' % (n, n, n))

        fp.write('    return 0;\n}\n')

    cmd = ('call "%s" >nul 2>&1 && cl /nologo /EHsc /utf-8 /W0 /I "%s" "%s" '
           '/Fe:"%s" /Fo:"%s" >nul'
           % (vcvars, CLASSES, src, os.path.join(work, 'probe.exe'),
              os.path.join(work, 'probe.obj')))

    subprocess.run(cmd, shell=True, cwd=work,
                   stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    exe = os.path.join(work, 'probe.exe')

    if not os.path.isfile(exe):
        sys.stderr.write('매크로 확인용 probe 빌드 실패\n')
        return {}

    out = subprocess.run([exe], stdout=subprocess.PIPE).stdout.decode('utf-8', 'replace')
    got = {}

    for line in out.splitlines():
        if '\t' in line:
            k, v = line.split('\t', 1)
            got[k] = (v.strip() == '1')

    return got


def drop_untaken(text, defined):
    """#ifdef 분기 중 실제로 컴파일되지 않는 쪽을 지운다. 중첩도 처리한다."""
    out = []
    stack = []

    for line in text.split('\n'):
        m = re.match(r'^#\s*(ifdef|ifndef|else|endif)\b\s*(\w*)', line.strip())

        if m:
            kind, name = m.group(1), m.group(2)

            if kind in ('ifdef', 'ifndef'):
                if name in defined:
                    on = defined[name] if kind == 'ifdef' else not defined[name]
                    stack.append((True, on))
                else:
                    stack.append((False, True))
            elif kind == 'else':
                if stack:
                    known, on = stack[-1]
                    stack[-1] = (known, (not on) if known else True)
            elif kind == 'endif':
                if stack:
                    stack.pop()

            out.append('')
            continue

        out.append(line if all(on for _k, on in stack) else '')

    return '\n'.join(out)


# ------------------------------------------------------------------- 표 만들기

def out_path(entity):
    return os.path.join(ROOT, 'content', entity + '.tsv')


def resolve(spec):
    """명세에 나오는 상수 이름들의 실제 값을 컴파일러에게 받는다."""
    want = {spec['total']}

    if spec['label_base']:
        want.add(spec['label_base'])

    for _n, _f, _s, base, _c in spec['layout']:
        if isinstance(base, str):
            want.add(base)

    vals = dump_ids.ask_compiler(sorted(want))

    if vals is None:
        return None

    return vals


def base_of(base, vals):
    return vals[base] if isinstance(base, str) else base


def data_file(fn):
    """배열 정의가 실제로 들어 있는 파일.

    split_data.py 로 가른 뒤에는 정의가 .cpp 로 옮겨가고 헤더에는 extern
    선언만 남는다. 갈라진 것과 안 갈라진 것이 섞여 있으므로 둘 다 본다.
    """
    cpp = os.path.join(CLASSES, 'Data', os.path.splitext(fn)[0] + '.cpp')

    if os.path.isfile(cpp):
        return cpp

    return os.path.join(CLASSES, 'Data', fn)


def load_arrays(spec, vals):
    cache = {}
    out = {}
    total = vals[spec['total']]

    for name, fn, stride, base, _cols in spec['layout']:
        if fn not in cache:
            cache[fn] = read(data_file(fn))

        elems = parse_array(cache[fn], name)

        if elems is None:
            sys.stderr.write('%s 배열을 %s 에서 못 찾았다\n' % (name, fn))
            return None

        want = (total - base_of(base, vals)) * stride

        if len(elems) != want:
            sys.stderr.write('%s : 원소가 %d개여야 하는데 %d개다\n'
                             % (name, want, len(elems)))
            return None

        out[name] = elems

    return out


def load_labels(spec, vals):
    """textId[label_base + id] 에서 이름을 긁는다."""
    if not spec['label_base']:
        return {}

    text = read(os.path.join(CLASSES, 'Text.h'))
    text = drop_untaken(text, ask_defined(macro_names(text)))

    at = find_decl(text, 'textId')

    if at is None:
        return {}

    elems, _end = split_elems(text, at)
    base = vals[spec['label_base']]
    out = {}

    for t in range(vals[spec['total']]):
        k = base + t
        s = elems[k].strip() if k < len(elems) else ''

        if s.startswith('"') and s.endswith('"') and s.count('"') == 2:
            s = s[1:-1]

        out[t] = s

    return out


def id_names(spec):
    path = os.path.join(ROOT, 'content', 'ids', spec['id_table'] + '.tsv')
    out = {}

    if not os.path.isfile(path):
        return out

    with open(path, encoding='utf-8') as fp:
        for line in fp:
            if line.startswith('#') or line.startswith('id\t'):
                continue

            f = line.rstrip('\n').split('\t')

            if len(f) >= 2:
                out[int(f[0])] = f[1]

    return out


def columns(spec):
    cols = ['id', 'enum_name', 'label']

    for _n, _f, _s, _b, cs in spec['layout']:
        cols.extend(cs)

    return cols


def esc(s):
    return (s.replace('\\', '\\\\').replace('\t', '\\t')
             .replace('\r', '\\r').replace('\n', '\\n'))


def unesc(s):
    return (s.replace('\\t', '\t').replace('\\r', '\r')
             .replace('\\n', '\n').replace('\\\\', '\\'))


def read_tsv(entity, spec):
    path = out_path(entity)

    if not os.path.isfile(path):
        sys.stderr.write('%s 가 없다. 먼저 extract 하라\n' % path)
        return None, None

    with open(path, encoding='utf-8') as fp:
        lines = [l.rstrip('\n') for l in fp if not l.startswith('#')]

    head = lines[0].split('\t')

    if head != columns(spec):
        sys.stderr.write('tsv의 컬럼이 지금 명세와 다르다\n')
        return None, None

    return head, [l.split('\t') for l in lines[1:]]


# --------------------------------------------------------------------- 명령

def cmd_extract(entity, spec, vals):
    arrays = load_arrays(spec, vals)

    if arrays is None:
        return 1

    labels = load_labels(spec, vals)
    enums = id_names(spec)
    total = vals[spec['total']]

    rows = []

    for t in range(total):
        row = [str(t), enums.get(t, ''), labels.get(t, '')]

        for name, _fn, stride, base, _cols in spec['layout']:
            b = base_of(base, vals)

            if t < b:
                row.extend([NULL] * stride)
                continue

            off = (t - b) * stride
            row.extend(arrays[name][off:off + stride])

        rows.append(row)

    path = out_path(entity)
    os.makedirs(os.path.dirname(path), exist_ok=True)
    cols = columns(spec)

    with open(path, 'w', encoding='utf-8', newline='\n') as fp:
        fp.write('#한 행이 하나다. 여러 파일 여러 배열에 흩어져 있던 것을 모은 것.\n')
        fp.write('#값은 소스에 적힌 글자 그대로다. 이름을 숫자로 바꾸지 않는다.\n')
        fp.write('#id는 계약이다. 중간에 끼우지 말고 항상 맨 끝에 (content/README.md).\n')
        fp.write('#\\N은 그 배열에 이 번호가 없다는 뜻이다.\n')
        fp.write('\t'.join(cols) + '\n')

        for r in rows:
            fp.write('\t'.join(x if x == NULL else esc(x) for x in r) + '\n')

    print('  %s  (%d행 x %d컬럼)'
          % (os.path.relpath(path, ROOT), len(rows), len(cols)))
    return 0


def rebuild(spec, head, rows, name, stride):
    """tsv에서 한 배열의 원소 목록을 되만든다."""
    at = 3

    for n, _f, s, _b, _c in spec['layout']:
        if n == name:
            break

        at += s

    out = []

    for r in rows:
        if r[at] == NULL:
            continue

        out.extend(unesc(x) for x in r[at:at + stride])

    return out


def check_rules(spec, head, rows):
    bad = 0

    for col, ok, why in spec['rules']:
        if col not in head:
            continue

        at = head.index(col)
        hits = [r for r in rows if not ok(r[at])]

        if hits:
            print('  %-16s %d행 위반 : %s' % (col, len(hits), why))

            for r in hits[:5]:
                print('      id %-4s %-24s = %r' % (r[0], r[1] or '(무명)', r[at]))

            bad += 1
        else:
            print('  %-16s OK  %d행' % (col, len(rows)))

    return bad


def cmd_verify(entity, spec, vals):
    arrays = load_arrays(spec, vals)

    if arrays is None:
        return 1

    head, rows = read_tsv(entity, spec)

    if head is None:
        return 1

    total = vals[spec['total']]

    if len(rows) != total:
        sys.stderr.write('tsv 행이 %d개여야 하는데 %d개다\n' % (total, len(rows)))
        return 1

    bad = 0

    for name, _fn, stride, _base, _cols in spec['layout']:
        got = rebuild(spec, head, rows, name, stride)
        orig = arrays[name]

        if len(got) != len(orig):
            print('  %-20s 개수 다름 : 원본 %d  복원 %d' % (name, len(orig), len(got)))
            bad += 1
            continue

        diff = [i for i in range(len(orig)) if orig[i] != got[i]]

        if diff:
            print('  %-20s 값 %d곳 다름 (첫 곳 %d: 원본 %r 복원 %r)'
                  % (name, len(diff), diff[0], orig[diff[0]], got[diff[0]]))
            bad += 1
        else:
            print('  %-20s OK  %d칸' % (name, len(orig)))

    if bad:
        print('  -> %d개 배열이 tsv와 다르다.' % bad)
        return 1

    if spec['rules']:
        bad = check_rules(spec, head, rows)

        if bad:
            print('  -> %d개 규칙을 어겼다.' % bad)
            return 1

    return 0


def make_body(spec, name, stride, base, rows, eol):
    at = 3

    for n, _f, s, _b, _c in spec['layout']:
        if n == name:
            break

        at += s

    out = ['',
           '\t//이 배열은 content/ 의 tsv에서 생성된다. 직접 고치지 말 것.',
           '\t//고치려면 tsv를 고치고 tools/content/content_table.py 를 돌린다.',
           '']

    for r in rows:
        if r[at] == NULL:
            continue

        label = r[2].strip()
        who = r[1] or '(무명)'

        out.append('\t%s,\t//%s %s%s'
                   % (', '.join(r[at:at + stride]), r[0], who,
                      ' ' + label if label else ''))

    return eol.join(out) + eol


def cmd_generate(entity, spec, vals, write):
    orig = load_arrays(spec, vals)

    if orig is None:
        return 1

    head, rows = read_tsv(entity, spec)

    if head is None:
        return 1

    byfile = {}

    for name, fn, stride, base, _cols in spec['layout']:
        byfile.setdefault(fn, []).append((name, stride, base))

    changed = 0
    newtext = {}

    for fn, arrays in byfile.items():
        path = data_file(fn)
        text = read(path)
        eol = '\r\n' if '\r\n' in text else '\n'

        spans = []

        for name, stride, base in arrays:
            span = find_body(text, name)

            if span is None:
                sys.stderr.write('%s 를 %s 에서 못 찾았다\n' % (name, fn))
                return 1

            # 배열 안에 전처리 분기가 있으면 생성하면 안 된다. 조건부가 통째로
            # 사라진다. 지금 대상 배열들에는 없지만 나중에 생길 수 있다.
            body = text[span[0]:span[1]]

            if re.search(r'^\s*#\s*(if|ifdef|ifndef|else|elif|endif)\b', body, re.M):
                sys.stderr.write('%s 안에 전처리 분기가 있어 생성할 수 없다\n' % name)
                return 1

            spans.append((span, name, stride, base))

        # 뒤에서부터 바꿔야 앞쪽 위치가 안 밀린다.
        spans.sort(key=lambda s: s[0][0], reverse=True)

        for (a, b), name, stride, base in spans:
            text = text[:a] + make_body(spec, name, stride, base, rows, eol) + text[b:]

        newtext[fn] = text

        for name, stride, base in arrays:
            got = parse_array(text, name)
            old = orig[name]

            if got is None:
                print('  %-20s 생성 결과를 다시 읽지 못했다' % name)
                return 1

            if len(got) != len(old):
                print('  %-20s 칸수 %d -> %d' % (name, len(old), len(got)))
                changed += 1
                continue

            diff = [i for i in range(len(old)) if old[i] != got[i]]

            if diff:
                print('  %-20s %d칸 중 %d칸 바뀜 (첫 곳 %d: %r -> %r)'
                      % (name, len(old), len(diff), diff[0],
                         old[diff[0]], got[diff[0]]))
                changed += 1
            else:
                print('  %-20s 그대로  %d칸' % (name, len(got)))

    if changed:
        print('  -> %d개 배열이 지금 헤더와 다르다. tsv를 고쳤다면 정상이다.' % changed)

    if not write:
        print('  (실제로 쓰려면 --write)')
        return 0

    for fn, text in newtext.items():
        path = data_file(fn)

        with open(path, 'w', encoding='utf-8-sig', newline='') as fp:
            fp.write(text)

        print('  썼다: %s' % os.path.relpath(path, ROOT))

    return 0


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('entity', nargs='?', choices=sorted(SPECS))
    ap.add_argument('cmd', choices=['extract', 'verify', 'generate'])
    ap.add_argument('--all', action='store_true', help='모든 엔티티에 대해')
    ap.add_argument('--write', action='store_true',
                    help='generate: 확인만 하지 말고 실제로 헤더를 고친다')
    args = ap.parse_args()

    if args.all:
        targets = sorted(SPECS)
    elif args.entity:
        targets = [args.entity]
    else:
        sys.stderr.write('엔티티를 주거나 --all 을 쓰라\n')
        return 2

    rc = 0

    for name in targets:
        spec = SPECS[name]
        print('[%s]' % name)

        vals = resolve(spec)

        if vals is None:
            return 1

        if args.cmd == 'extract':
            r = cmd_extract(name, spec, vals)
        elif args.cmd == 'verify':
            r = cmd_verify(name, spec, vals)
        else:
            r = cmd_generate(name, spec, vals, args.write)

        if r == 0 and args.cmd == 'verify':
            print('  통과')

        rc = rc or r
        print()

    return rc


if __name__ == '__main__':
    sys.exit(main())
