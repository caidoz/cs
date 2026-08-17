# -*- coding: utf-8 -*-
"""지금은 없는 함수를 부르는 주석을 찾는다.

deadcomment.py와 같은 기준이다. 주석을 풀었을 때 컴파일이 안 되는 것만 지운다.
여기서는 "주석이 부르는 이름이 살아 있는 코드 어디에도 없다"를 근거로 삼는다.
이름이 아예 없으면 인자 개수를 따질 것도 없이 컴파일이 안 된다.

살아 있는 이름은 Classes 전체(데이터 헤더 포함)의 주석 바깥에서 모은다.
enum이나 매크로로만 존재하는 이름도 살아 있는 것으로 친다.
"""
import io, os, re, sys, glob

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from deadcomment import spans

WORD = re.compile(r'\b[A-Za-z_]\w*\b')

#주석 몸통이 "함수 호출 문장" 모양일 때만 후보로 본다.
#이름만 보고 지우면 산문이 통째로 날아간다 - Net.h의 "//byte(1)" 같은 프로토콜
#설명이나 "//CP949(2바이트)보다 크다" 같은 문장이 전부 걸린다.
#세미콜론으로 끝나는 한 줄짜리 호출문만 남긴다.
CALLSTMT = re.compile(
    r'^\s*(?:[\w\[\]\.\s\*>-]+=\s*)?([A-Za-z_]\w*)\s*\(.*\)\s*;\s*$')

#언어 키워드는 함수가 아니다.
KEYWORD = set('''if else for while switch case do return sizeof new delete
    static const void int float bool char short long unsigned signed struct
    enum typedef break continue default goto union class public private
    protected virtual inline extern register volatile true false null NULL
    and or not defined'''.split())


def liveText(path):
    """주석을 걷어낸 본문."""
    text = io.open(path, encoding='utf-8-sig').read()
    out = []
    prev = 0

    for a, b, _ in spans(text):
        out.append(text[prev:a])
        prev = b

    out.append(text[prev:])
    return ''.join(out)


def collectLive(paths):
    live = set()

    for path in paths:
        live.update(WORD.findall(liveText(path)))

    return live


def deadSpans(path, live):
    """(시작, 끝, 없는이름들) 목록."""
    text = io.open(path, encoding='utf-8-sig').read()
    out = []

    for a, b, _ in spans(text):
        body = text[a:b]

        #주석 표시를 걷어낸 몸통. 여러 줄짜리는 대상이 아니다.
        if body.startswith('//'):
            body = body[2:]
        elif body.startswith('/*') and body.endswith('*/'):
            body = body[2:-2]
        else:
            continue

        if '\n' in body.strip():
            continue

        m = CALLSTMT.match(body)

        if not m:
            continue

        name = m.group(1)

        if name in KEYWORD or name in live:
            continue

        out.append((a, b, [name]))

    return out, text


def run(dryRun=False, show=0):
    files = sorted(glob.glob('Classes/*.cpp')) + sorted(glob.glob('Classes/*.h'))
    scan = files + sorted(glob.glob('Classes/*/*.h'))

    live = collectLive(scan)
    print('살아 있는 이름 %d개' % len(live))

    total = 0
    lines = 0
    samples = []

    for path in files:
        kill, text = deadSpans(path, live)

        if not kill:
            continue

        for a, b, missing in kill[:show]:
            samples.append('  %s: %s' % (os.path.basename(path),
                text[a:b].strip().replace('\r', '').replace('\n', ' ')[:110]))

        new = text
        gone = 0

        for a, b, _ in reversed(kill):
            head = new[:a]
            tail = new[b:]
            lineStart = head.rfind('\n') + 1

            if head[lineStart:].strip() == '':
                m = re.match(r'[ \t]*\r?\n', tail)
                if m:
                    head = head[:lineStart]
                    tail = tail[m.end():]
            else:
                head = head.rstrip(' \t')

            new = head + tail

        gone = text.count('\n') - new.count('\n')
        total += len(kill)
        lines += gone
        print('  %-34s 주석 %3d개, %4d줄' % (os.path.basename(path), len(kill), gone))

        if not dryRun:
            io.open(path, 'w', encoding='utf-8-sig', newline='\r\n').write(new)

    print('합계 주석 %d개, %d줄' % (total, lines))

    if samples:
        print('\n--- 표본 ---')
        for s in samples:
            print(s)


if __name__ == '__main__':
    show = 0

    for a in sys.argv[1:]:
        if a.isdigit():
            show = int(a)

    run('--dry' in sys.argv, show)
