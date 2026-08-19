# -*- coding: utf-8 -*-
"""데이터 배열을 헤더의 정의에서 "헤더 선언 + cpp 정의"로 가른다.

[문제]
데이터 배열이 전부 헤더 안에 이렇게 정의돼 있다.

    const long long monStr[] = { ... };

C++에서 네임스페이스 스코프의 const는 내부 링크다. 그리고 Data.h(데이터
헤더 23개를 전부 include)를 19개 .cpp가 포함한다. 즉 같은 데이터가 19벌
복제된다. 측정하면 obj 86MB 중 74MB가 이 복제분이고, 수학 함수만 든
Func_Math.obj가 3MB다.

런타임 로딩(C단계)을 하려면 이걸 먼저 풀어야 한다. const 배열은 채울 수도
없고, 인스턴스가 19개면 어느 것을 채울지도 정할 수 없다.

[하는 일]
    Data/X.h   : const 정의 -> extern 선언
    Data/X.cpp : 정의를 그대로 옮긴다 (새로 만든다)

크기를 적지 않은 [] 배열은 원소를 세어 [N]으로 적는다. 두 가지 이득이 있다.
  - sizeof(배열)이 그대로 동작한다 (7곳이 쓴다)
  - 선언과 정의의 개수가 어긋나면 컴파일 오류가 난다. 배열 12개 중 하나를
    빠뜨리는 실수가 조용히 지나가지 않는다.

    python tools/content/split_data.py EnemyData.h
    python tools/content/split_data.py EnemyData.h --write
"""
import argparse
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT

ROOT = CT.ROOT
DATA = os.path.join(CT.CLASSES, 'Data')

# const <타입> <이름><차원들> = {
DECL_RE = re.compile(
    r'^[ \t]*const[ \t]+'
    r'(?P<type>[A-Za-z_][A-Za-z0-9_ \t]*?)[ \t]+'
    r'(?P<name>[A-Za-z_][A-Za-z0-9_]*)[ \t]*'
    r'(?P<dims>(?:\[[^\]]*\][ \t]*)+)'
    r'=[ \t]*\{', re.M)


def find_defs(text):
    """최상위 const 배열 정의를 찾는다. [(시작, 끝, 타입, 이름, 차원)]

    끝은 닫는 중괄호 다음의 세미콜론까지다.
    """
    out = []

    for m in DECL_RE.finditer(text):
        line_start = text.rfind('\n', 0, m.start()) + 1

        # 주석 처리된 선언은 건너뛴다.
        if '//' in text[line_start:m.start(0) + len(m.group(0)) - 1].split('const')[0]:
            continue

        head = text[line_start:m.start()]

        if '//' in head:
            continue

        _elems, close = CT.split_elems(text, m.end())

        # 닫는 } 다음의 ; 까지 삼킨다.
        end = close + 1

        while end < len(text) and text[end] in ' \t':
            end += 1

        if end < len(text) and text[end] == ';':
            end += 1

        out.append((line_start, end, m.group('type').strip(),
                    m.group('name'), m.group('dims').strip()))

    return out


def tier_of(text, a, b, dims, name, sizeof_used):
    """이 배열을 어떻게 다룰지 정한다.

    1 = 포인터로 바꾸고 팩에 넣는다 (보통의 1차원 const 배열)
    2 = .cpp로 옮기되 배열 그대로 두고 헤더에는 extern 배열 선언
        - 2차원      : 포인터가 T(*)[N] 이라 색인식이 달라진다
        - 전처리 분기 : 팩으로 옮기면 조건부가 통째로 사라진다
        - sizeof 사용 : 포인터가 되면 sizeof 가 4가 된다

    2번은 팩으로 못 바꾸므로 CDN으로도 못 고친다. 줄여야 할 목록이다.
    """
    if dims.count('[') > 1:
        return 2, '2차원'

    if re.search(r'^[ \t]*#[ \t]*(if|ifdef|ifndef|else|elif|endif)\b',
                 text[a:b], re.M):
        return 2, '전처리 분기'

    if name in sizeof_used:
        return 2, 'sizeof 사용'

    return 1, ''



def sized_dims(text, start_of_body, dims):
    """선언에 쓸 차원. []이면 원소를 세어 [N]으로 바꾼다."""
    parts = re.findall(r'\[([^\]]*)\]', dims)

    if parts and parts[0].strip() == '':
        elems, _end = CT.split_elems(text, start_of_body)
        parts[0] = str(len(elems))

    return ''.join('[%s]' % p for p in parts)


def split_file(fname, write):
    path = os.path.join(DATA, fname)

    if not os.path.isfile(path):
        sys.stderr.write('%s 가 없다\n' % path)
        return 1

    text = CT.read(path)
    eol = '\r\n' if '\r\n' in text else '\n'

    defs = find_defs(text)

    if not defs:
        print('  const 배열 정의를 못 찾았다')
        return 1

    base = os.path.splitext(fname)[0]
    cpp_name = base + '.cpp'

    # ---- cpp : 정의를 그대로 옮긴다 ----
    body = []
    body.append('//이 파일은 %s 에 있던 배열 정의를 옮겨 담은 것이다.' % fname)
    body.append('//')
    body.append('//헤더에 const로 정의하면 내부 링크라, Data.h를 포함하는 .cpp마다')
    body.append('//같은 데이터가 한 벌씩 복제된다. 정의는 여기 한 곳에만 두고')
    body.append('//헤더에는 extern 선언만 남긴다.')
    body.append('//')
    body.append('//tools/content/split_data.py 가 갈랐다.')
    body.append('')
    #자기 헤더만 가져온다. Data.h를 통째로 끌면 UIData.h의 std::string 때문에
    #cocos2d.h가 필요해지고, 그러면 팩 생성기가 이 파일만 따로 컴파일할 수 없다.
    body.append('#include "%s"' % fname)
    body.append('')

    # ---- h : 정의를 extern 선언으로 ----
    newh = []
    at = 0

    for a, b, typ, name, dims in defs:
        newh.append(text[at:a])

        # 정의 본문의 여는 { 위치를 다시 찾아 원소를 센다.
        m = DECL_RE.search(text, a)
        dcl = sized_dims(text, m.end(), dims)

        newh.append('extern const %s %s%s;' % (typ, name, dcl))
        body.append(text[a:b].rstrip())
        body.append('')
        at = b

    newh.append(text[at:])

    htext = ''.join(newh)
    ctext = eol.join(body) + eol

    print('  배열 %d개' % len(defs))
    print('  %-16s %7d -> %7d 바이트' % (fname, len(text), len(htext)))
    print('  %-16s         %7d 바이트 (새로 만듦)' % (cpp_name, len(ctext)))

    if not write:
        print('  (실제로 쓰려면 --write)')
        return 0

    with open(path, 'w', encoding='utf-8-sig', newline='') as fp:
        fp.write(htext)

    with open(os.path.join(DATA, cpp_name), 'w',
              encoding='utf-8-sig', newline='') as fp:
        fp.write(ctext)

    print('  썼다: Classes/Data/%s , Classes/Data/%s' % (fname, cpp_name))
    return 0


def register(cpp_rel):
    """새 .cpp 를 win32/android 빌드에 등록한다."""
    # ---- vcxproj ----
    p = os.path.join(ROOT, 'proj.win32', 'cs.vcxproj')
    t = CT.read(p)
    tag = '<ClCompile Include="..\\Classes\\%s" />' % cpp_rel.replace('/', '\\')

    if tag in t:
        print('  vcxproj : 이미 있음')
    else:
        anchor = '    <ClCompile Include="..\\Classes\\Func_Net.cpp" />'

        if anchor not in t:
            sys.stderr.write('vcxproj 기준 줄을 못 찾았다\n')
            return 1

        t = t.replace(anchor, anchor + '\r\n    ' + tag, 1)

        with open(p, 'w', encoding='utf-8-sig', newline='') as fp:
            fp.write(t)

        print('  vcxproj : 추가')

    # ---- Android.mk ----
    p = os.path.join(ROOT, 'proj.android', 'app', 'jni', 'Android.mk')
    t = CT.read(p)

    if cpp_rel in t:
        print('  Android.mk : 이미 있음')
        return 0

    key = 'Classes/Func_Net.cpp'
    i = t.index(key)
    s = t.rindex('\n', 0, i) + 1
    e = t.index('\n', i) + 1
    line = t[s:e]
    t = t[:s] + line + line.replace('Func_Net.cpp', cpp_rel) + t[e:]

    with open(p, 'w', encoding='utf-8', newline='') as fp:
        fp.write(t)

    print('  Android.mk : 추가')
    return 0


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('files', nargs='+', help='Data/ 안의 헤더 이름')
    ap.add_argument('--write', action='store_true')
    args = ap.parse_args()

    for fname in args.files:
        print('[%s]' % fname)
        r = split_file(fname, args.write)

        if r:
            return r

        if args.write:
            r = register('Data/' + os.path.splitext(fname)[0] + '.cpp')

            if r:
                return r

        print()

    return 0


if __name__ == '__main__':
    sys.exit(main())
