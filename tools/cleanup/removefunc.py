# -*- coding: utf-8 -*-
"""죽은 전역 함수의 본문과 헤더 선언을 지운다.

deadfunc_check.py가 뽑아 검증한 목록을 먹는다.

이 코드베이스는 함수가 1열에서 시작하고 1열의 '}'로 끝난다. 중첩 블록은 항상
들여쓰기가 되어 있으므로 그 규칙으로 범위를 잡는다. 규칙에서 벗어나는 것은
건드리지 않고 보류로 남긴다 - 잘못 자르면 뒤따르는 함수가 통째로 날아간다.

함수 바로 위에 빈 줄 없이 붙어 있는 주석은 그 함수의 설명이므로 같이 지운다.
"""
import io, os, re, sys, glob


def findDef(lines, name):
    """(시작줄, 끝줄). 못 찾으면 None."""
    head = re.compile(r'^[A-Za-z_][\w:<>\*&\s]*?\b%s\s*\(' % re.escape(name))

    for i, line in enumerate(lines):
        if not head.match(line):
            continue

        #선언(세미콜론으로 끝남)은 건너뛴다. 정의는 '{'가 따라온다.
        j = i

        while j < len(lines) and '{' not in lines[j]:
            if ';' in lines[j]:
                break
            j += 1

        if j >= len(lines) or '{' not in lines[j]:
            continue

        #1열의 '}'를 찾는다.
        for k in range(j, len(lines)):
            if lines[k].rstrip('\r') == '}':
                return i, k

        return None

    return None


def attachedComment(lines, start):
    """함수 바로 위에 빈 줄 없이 붙은 주석의 시작 줄."""
    i = start

    while i > 0:
        prev = lines[i - 1].strip()

        if prev.startswith('//'):
            i -= 1
            continue

        if prev.endswith('*/'):
            #블록 주석의 시작까지 거슬러 올라간다.
            j = i - 1

            while j > 0 and '/*' not in lines[j]:
                j -= 1

            if '/*' in lines[j]:
                i = j
                continue

        break

    return i


def run(listPath, dryRun=False):
    want = {}

    #"지워도 되는 것" 구획만 읽는다.
    on = False

    for line in io.open(listPath, encoding='utf-8'):
        if line.startswith('==='):
            on = '지워도 되는 것' in line
            continue

        if not on:
            continue

        parts = line.split()

        if len(parts) == 2:
            want.setdefault(parts[0], []).append(parts[1])

    gone = []
    missed = []
    removedLines = 0

    for src in sorted(want):
        path = os.path.join('Classes', src)
        lines = io.open(path, encoding='utf-8-sig').read().split('\n')

        #뒤에서부터 지워야 줄번호가 안 밀린다.
        spots = []

        for name in want[src]:
            r = findDef(lines, name)

            if r is None:
                missed.append('%s %s' % (src, name))
                continue

            a = attachedComment(lines, r[0])
            spots.append((a, r[1], name))

        spots.sort(reverse=True)

        for a, b, name in spots:
            #뒤에 붙은 빈 줄 하나까지 같이 걷어낸다.
            end = b

            while end + 1 < len(lines) and lines[end + 1].strip() == '':
                end += 1
                break

            del lines[a:end + 1]
            removedLines += end + 1 - a
            gone.append('%s %s' % (src, name))

        if spots and not dryRun:
            io.open(path, 'w', encoding='utf-8-sig',
                newline='\r\n').write('\n'.join(lines))

    #헤더 선언
    decl = 0

    for path in sorted(glob.glob('Classes/*.h')):
        lines = io.open(path, encoding='utf-8-sig').read().split('\n')
        keep = []
        hit = 0

        allNames = set()

        for src in want:
            allNames.update(want[src])

        for line in lines:
            m = re.match(r'^\s*[A-Za-z_][\w:<>\*&\s]*?\b(\w+)\s*\([^;{]*\)\s*;\s*$', line)

            if m and m.group(1) in allNames:
                hit += 1
                continue

            keep.append(line)

        if hit:
            decl += hit

            if not dryRun:
                io.open(path, 'w', encoding='utf-8-sig',
                    newline='\r\n').write('\n'.join(keep))

    print('지운 함수 %d개 (%d줄), 헤더 선언 %d개' % (len(gone), removedLines, decl))

    if missed:
        print('못 찾은 것 %d개:' % len(missed))

        for m in missed:
            print('  ' + m)


if __name__ == '__main__':
    run(sys.argv[1], '--dry' in sys.argv)
