# -*- coding: utf-8 -*-
"""데이터 헤더를 "헤더 선언 + cpp 정의"로 가르고, 가능한 것은 포인터로 바꾼다.

한 번에 두 가지를 한다.

  1. 정의를 Data/X.cpp 로 옮기고 헤더에는 선언만 남긴다
     헤더에 const로 정의하면 내부 링크라 포함하는 .cpp마다 복제되고,
     무엇보다 런타임에 채울 수가 없다.

  2. 채울 수 있는 것은 포인터로 바꾼다
        extern const short* enemyData;
        enum { enemyData_COUNT = 3448 };
     호출부의 enemyData[i] 는 그대로 동작한다. 부팅 때 포인터를 팩으로 옮긴다.

바꾸지 못하는 것은 배열 그대로 두고 extern 배열로만 선언한다(티어 2).
  - 2차원      : 포인터가 T(*)[N] 이라 색인식이 달라진다
  - 전처리 분기 : 팩으로 옮기면 조건부가 통째로 사라진다
  - sizeof 사용 : 포인터가 되면 sizeof 가 4가 된다

티어 2는 CDN으로 못 고친다. 줄여야 할 목록이므로 끝에 모아서 보여준다.

    python tools/content/datafiles.py --list
    python tools/content/datafiles.py QuestData ItemData --write
    python tools/content/datafiles.py --all --write
"""
import argparse
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT
import split_data as SD

ROOT = SD.ROOT
DATA = SD.DATA

#포인터로 바꾸면 sizeof 가 깨지는 배열들. 호출부를 _COUNT 로 고치면 여기서 뺀다.
SIZEOF_USED = {
    #upgradeCostCrew 는 2차원이라 어차피 티어 2다. sizeof 도 그대로 동작한다.
    'upgradeCostCrew',
}

SKIP = {'DataPack.h', 'DataList.h'}


def headers():
    out = []

    for n in sorted(os.listdir(DATA)):
        if n.endswith('.h') and n not in SKIP:
            out.append(n)

    return out


def strip_directives(chunk):
    """정의와 정의 사이의 텍스트에서 전처리 지시문 줄만 뺀다.

    헤더에서 .cpp로 옮길 때 주변 주석은 살리고 싶지만, 그대로 옮기면
    include 가드까지 딸려간다. 그러면 이런 꼴이 된다.

        #include "WaveData.h"    <- 여기서 _DATA_WAVE_H_ 가 정의되고
        #ifndef _DATA_WAVE_H_    <- 이미 정의됐으니 이하가 통째로 사라진다
        static const int boss_builtin[] = { ... };

    정의 안(text[a:b])의 #ifdef 는 건드리지 않는다. 그건 값의 일부다.
    """
    out = []

    for line in chunk.split('\n'):
        if re.match(r'^[ \t]*#', line):
            continue

        out.append(line)

    return '\n'.join(out)


def in_conditional(text, at):
    """이 자리가 #if/#ifdef 블록 안인지.

    ItemData.h 에는 #ifdef IRON / #else / #ifdef SETITEM 처럼 분기마다 같은
    이름의 배열을 다시 정의하는 곳이 있다. 셋 다 최상위 const 정의라 그냥
    긁으면 한 파일에 같은 이름이 세 번 들어가 재정의 오류가 난다.

    이런 것은 옮기지도 바꾸지도 않고 헤더에 그대로 둔다(티어 3). 정의만
    옮기면 감싸던 #ifdef 가 헤더에 남아 짝이 깨진다.
    """
    depth = 0

    for line in text[:at].split('\n'):
        m = re.match(r'^[ \t]*#[ \t]*(if|ifdef|ifndef|endif)\b', line)

        if not m:
            continue

        if m.group(1) == 'endif':
            depth -= 1
        else:
            depth += 1

    #파일 전체를 감싸는 include 가드 한 겹은 빼고 센다.
    return depth > 1


def analyze(fname):
    """이 파일의 배열들을 티어별로 나눈다. 이미 갈라졌으면 .cpp 를 본다."""
    base = os.path.splitext(fname)[0]
    cpp = os.path.join(DATA, base + '.cpp')
    already = os.path.isfile(cpp)
    src = cpp if already else os.path.join(DATA, fname)

    text = CT.read(src)
    defs = SD.find_defs(text)
    rows = []

    for a, b, typ, name, dims in defs:
        #.cpp 에는 include 가드가 없으므로 한 겹 차이를 보정한다.
        depth_at = a if already else a

        if in_conditional(text, depth_at) if not already else False:
            rows.append((a, b, typ, name, dims, 3, '전처리 블록 안', 0, ''))
            continue

        tier, why = SD.tier_of(text, a, b, dims, name, SIZEOF_USED)
        m = SD.DECL_RE.search(text, a)
        elems, _e = CT.split_elems(text, m.end())
        rows.append((a, b, typ, name, dims, tier, why, len(elems), m.group(0)))

    return src, text, rows


def convert(fname, write):
    base = os.path.splitext(fname)[0]
    hp = os.path.join(DATA, fname)
    cp = os.path.join(DATA, base + '.cpp')
    already = os.path.isfile(cp)

    src, text, rows = analyze(fname)

    if not rows:
        return 0, [], []

    eol = '\r\n' if '\r\n' in text else '\n'
    htext = CT.read(hp)

    # ---- cpp 본문 ----
    out = []
    at = 0
    decls = []

    for a, b, typ, name, dims, tier, why, cnt, head in rows:
        if tier == 3:
            # 전처리 블록 안이라 손대지 않는다. 헤더에 그대로 남는다.
            at = b
            continue

        # 정의 사이의 텍스트는 옮기지 않는다.
        #
        # 처음에는 주석을 살리려고 통째로 옮겼는데, 그러면 헤더의 다른 것까지
        # 딸려간다. include 가드가 따라와 정의가 전처리로 사라졌고,
        # UIData.h의 static std::string fontList[] 같은 const가 아닌 정의도
        # 복사되어 컴파일이 깨졌다.
        #
        # 주석은 헤더에 그대로 둔다. 사람이 읽는 것은 선언 쪽이라 거기 있는
        # 편이 낫다. 이미 갈라진 .cpp를 다시 다룰 때는 그 안의 텍스트가
        # 전부 정의뿐이므로 그대로 옮긴다.
        if already:
            out.append(text[at:a])

        body = text[a:b]

        if tier == 1:
            body = body.replace(
                head, 'static const %s %s_builtin[] = {' % (typ, name), 1)
            decls.append(('ptr', typ, name, cnt))
        elif tier == 4:
            # 2차원. 안쪽 크기를 남겨야 const T (*p)[COLS] 와 짝이 맞는다.
            cols = re.findall(r'\[([^\]]*)\]', dims)[1]
            body = body.replace(
                head,
                'static const %s %s_builtin[][%s] = {' % (typ, name, cols), 1)
            decls.append(('ptr2', typ, name, cnt, cols))
        else:
            decls.append(('arr', typ, name, cnt, dims))

        out.append(body.rstrip())
        out.append(eol)
        at = b

    out.append(text[at:] if already else '')
    ctext = ''.join(out).rstrip()

    ptrs = [d for d in decls if d[0] in ('ptr', 'ptr2')]

    if ptrs:
        tail = ['', '',
                '//게임이 읽는 포인터. 처음에는 내장 기본값을 가리키고, 부팅 때',
                '//팩을 읽으면 그쪽으로 옮겨간다. const는 가리키는 대상에 붙으므로',
                '//게임 코드는 대상을 못 건드리고, 로더만 자기 버퍼를 채워 넘긴다.',
                '']

        for d in ptrs:
            if d[0] == 'ptr':
                tail.append('const %s* %s = %s_builtin;' % (d[1], d[2], d[2]))
            else:
                tail.append('const %s (*%s)[%s] = %s_builtin;'
                            % (d[1], d[2], d[4], d[2]))

        ctext += eol.join(tail)

    ctext += eol

    if not already:
        head = [
            '//이 파일은 %s 에 있던 배열 정의를 옮겨 담은 것이다.' % fname,
            '//',
            '//헤더에 const로 정의하면 내부 링크라 포함하는 .cpp마다 복제되고,',
            '//무엇보다 런타임에 채울 수가 없다. 정의는 여기 한 곳에만 둔다.',
            '//',
            '//자기 헤더만 가져온다. Data.h를 통째로 끌면 UIData.h의 std::string',
            '//때문에 cocos2d.h가 필요해지고, 그러면 팩 생성기가 이 파일만 따로',
            '//컴파일할 수 없다.',
            '//',
            '//tools/content/datafiles.py 가 갈랐다.',
            '',
            '#include "%s"' % fname,
            #예전에는 Data.h 가 헤더 23개를 순서대로 끌어서, 앞선 헤더가
            #가져온 것에 뒤 헤더가 얹혀 가는 의존이 있었다. 이제 파일마다
            #따로 컴파일되므로 그 암묵적 의존이 끊긴다. 둘 다 cocos에서
            #자유로우니 명시해 둔다.
            '#include "../Def.h"',
            '#include "../Cmf.h"',
            '',
            '',
        ]
        ctext = eol.join(head) + ctext

    # ---- 헤더 ----
    if already:
        # 이미 extern 선언이 들어 있다. 포인터로 바꿀 것만 교체한다.
        for d in decls:
            if d[0] not in ('ptr', 'ptr2'):
                continue

            typ, name, cnt = d[1], d[2], d[3]

            if d[0] == 'ptr':
                pat = re.compile(
                    r'extern[ \t]+const[ \t]+%s[ \t]+%s\s*\[[^\]]*\]\s*;'
                    % (re.escape(typ), re.escape(name)))
                rep = ('extern const %s* %s;%senum { %s_COUNT = %d };'
                       % (typ, name, eol, name, cnt))
            else:
                cols = d[4]
                pat = re.compile(
                    r'extern[ \t]+const[ \t]+%s[ \t]+%s\s*(?:\[[^\]]*\]\s*)+;'
                    % (re.escape(typ), re.escape(name)))
                rep = ('extern const %s (*%s)[%s];%s'
                       'enum { %s_ROWS = %d, %s_COLS = (%s),%s'
                       '	   %s_COUNT = %s_ROWS * %s_COLS };'
                       % (typ, name, cols, eol,
                          name, cnt, name, cols, eol, name, name, name))
            htext, n = pat.subn(rep, htext, count=1)

            if n != 1:
                sys.stderr.write('%s : 헤더에서 %s 선언을 못 찾았다\n' % (fname, name))
                return -1, [], []
    else:
        parts = []
        at = 0

        for a, b, typ, name, dims, tier, why, cnt, head in rows:
            if tier == 3:
                continue

            parts.append(htext[at:a])

            if tier == 1:
                parts.append('extern const %s* %s;%senum { %s_COUNT = %d };'
                             % (typ, name, eol, name, cnt))
            elif tier == 4:
                cols = re.findall(r'\[([^\]]*)\]', dims)[1]
                #cnt 는 바깥 차원(행 수)이다. 팩은 전체 원소 수를 쓰므로
                #_COUNT 는 행 x 열로 둔다. 행 수는 _ROWS 로 따로 낸다.
                parts.append(
                    'extern const %s (*%s)[%s];%s'
                    'enum { %s_ROWS = %d, %s_COLS = (%s),%s'
                    '	   %s_COUNT = %s_ROWS * %s_COLS };'
                    % (typ, name, cols, eol,
                       name, cnt, name, cols, eol, name, name, name))
            else:
                parts.append('extern const %s %s%s;'
                             % (typ, name, SD.sized_dims(
                                 htext, htext.index('{', a) + 1, dims)))

            at = b

        parts.append(htext[at:])
        htext = ''.join(parts)

    t1 = [r for r in rows if r[5] in (1, 4)]
    t2 = [(fname, r[3], r[6]) for r in rows if r[5] in (2, 3)]

    if write:
        with open(hp, 'w', encoding='utf-8-sig', newline='') as fp:
            fp.write(htext)

        with open(cp, 'w', encoding='utf-8-sig', newline='') as fp:
            fp.write(ctext)

        if not already:
            SD.register('Data/' + base + '.cpp')

    return len(t1), t2, rows


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('files', nargs='*')
    ap.add_argument('--all', action='store_true')
    ap.add_argument('--list', action='store_true', help='분류만 보여준다')
    ap.add_argument('--write', action='store_true')
    args = ap.parse_args()

    names = headers() if (args.all or args.list) else [f + '.h' for f in args.files]

    total1 = 0
    tier2 = []

    for fname in names:
        if args.list:
            _src, _t, rows = analyze(fname)

            if not rows:
                continue

            a = sum(1 for r in rows if r[5] in (1, 4))
            b = [(fname, r[3], r[6]) for r in rows if r[5] in (2, 3)]
            print('%-18s 포인터 %3d  그대로 %d' % (fname, a, len(b)))
            total1 += a
            tier2 += b
            continue

        n, t2, _rows = convert(fname, args.write)

        if n < 0:
            return 1

        if n or t2:
            print('%-18s 포인터 %3d  그대로 %d' % (fname, n, len(t2)))

        total1 += n
        tier2 += t2

    print()
    print('팩에 들어갈 배열 %d개' % total1)

    if tier2:
        print('팩에 못 넣는 배열 %d개 (CDN으로 못 고친다):' % len(tier2))

        for f, n, why in tier2:
            print('    %-18s %-26s %s' % (f, n, why))

    return 0


if __name__ == '__main__':
    sys.exit(main())
