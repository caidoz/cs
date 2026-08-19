# -*- coding: utf-8 -*-
"""textId[] 를 "용량" 기준 좌표로 다시 깐다.

[왜]
텍스트 ID 구간이 원래 콘텐츠 개수에 붙어 있었다.

    TEXT_ITEMNAME_START = TEXT_MONSTERNAME_START + TOTALENEMY,

이러면 몬스터가 하나 늘 때 뒤가 전부 밀려서 옛 클라이언트가 새 팩을 못 읽는다.
그래서 TOTALENEMY 를 CAP_ENEMY 로 바꿨다(Config/Capacity.h). 그만큼 구간이
넓어졌으므로 textId[] 도 같은 자리에 빈칸을 넣어줘야 짝이 맞는다.

[하는 일]
지정한 자리에 빈 문자열을 끼워 넣는다. 원소를 다시 써내지 않고 그 자리에
글자만 밀어 넣는다. 원본의 주석과 줄바꿈이 그대로 남는다.

[검증]
넣은 뒤 원소 수가 TEXT_LENGTH 와 같아야 한다. dump_ids.py 가 그걸 본다.

    python tools/content/relayout_text.py
    python tools/content/relayout_text.py --write
"""
import argparse
import io
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT

PATH = os.path.join(CT.CLASSES, 'Text.h')

#(옛 index, 몇 칸, 무엇을 위한 빈칸인가)
#옛 index 는 "이 원소 바로 앞"에 넣는다는 뜻이다.
GAPS = [
    (558,  81, 'TEXT_MONSTERNAME  CAP_ENEMY(512) - 431'),
    (6532, 81, 'TEXT_MONSTER_DESC   CAP_ENEMY(512) - 431'),
    (6963, 81, 'TEXT_MONSTER_DESC2  CAP_ENEMY(512) - 431'),
    (7394, 81, 'TEXT_MONSTER_GOOD   CAP_ENEMY(512) - 431'),
    (7825, 81, 'TEXT_MONSTER_BAD    CAP_ENEMY(512) - 431'),
    (9754, 87, 'TEXT_MAPNAME        CAP_MAP(512) - 425'),
]

OLD_COUNT = 9817
NEW_COUNT = 10309


def mask_untaken(text):
    """컴파일되지 않는 #ifdef 가지를 공백으로 덮는다.

    content_table.drop_untaken 은 죽은 줄을 빈 줄로 만들어서 글자 위치가
    밀린다. 여기서는 위치를 그대로 써야 하므로 같은 길이의 공백으로 덮는다.
    덕분에 여기서 찾은 위치를 원본에 그대로 쓸 수 있다.
    """
    defined = CT.ask_defined(CT.macro_names(text))
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

            #전처리 줄 자체도 원소로 세지 않도록 덮는다.
            out.append(' ' * len(line))
            continue

        out.append(line if all(on for _k, on in stack) else ' ' * len(line))

    masked = '\n'.join(out)
    assert len(masked) == len(text), '길이가 안 맞는다'
    return masked


def elem_starts(text, start):
    """중괄호 안 원소들의 시작 위치를 돌려준다.

    split_elems 와 같은 규칙으로 훑되, 글자가 아니라 위치를 모은다.
    (문자열/문자/주석/중첩 중괄호를 건너뛴다)
    """
    out = []
    depth = 1
    i = start
    pending = True   #다음 원소의 시작을 아직 못 찾았다

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
            if pending:
                out.append(i)
                pending = False

            q = c
            j = i + 1

            while j < len(text):
                if text[j] == '\\':
                    j += 2
                    continue

                if text[j] == q:
                    break

                j += 1

            i = j + 1
            continue

        if c == '{':
            if pending:
                out.append(i)
                pending = False

            depth += 1
        elif c == '}':
            depth -= 1

            if depth == 0:
                return out, i
        elif c == ',' and depth == 1:
            pending = True
        elif not c.isspace() and pending:
            out.append(i)
            pending = False

        i += 1

    raise SystemExit('닫는 중괄호를 못 찾았다')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--write', action='store_true')
    args = ap.parse_args()

    text = CT.read(PATH)
    eol = '\r\n' if '\r\n' in text else '\n'

    m = re.search(r'const\s+char\s*\*\s*const\s+textId\s*\[\s*\]\s*=\s*\{', text)

    if not m:
        sys.stderr.write('textId 정의를 못 찾았다\n')
        return 1

    #죽은 #ifdef 가지를 빼고 센다. 위치는 원본과 같다.
    masked = mask_untaken(text)
    starts, _close = elem_starts(masked, m.end())
    print('  원소 %d개' % len(starts))

    if len(starts) == NEW_COUNT:
        print('  이미 새 좌표다. 할 일 없음.')
        return 0

    if len(starts) != OLD_COUNT:
        sys.stderr.write('원소가 %d개다. %d개(옛) 나 %d개(새) 여야 한다.\n'
                         % (len(starts), OLD_COUNT, NEW_COUNT))
        return 1

    #뒤에서부터 넣어야 앞쪽 위치가 안 밀린다.
    out = text

    for idx, n, why in sorted(GAPS, reverse=True):
        at = starts[idx]
        pad = [eol, '\t//---- 여기부터 %d칸은 예약이다. %s' % (n, why), eol,
               '\t//     콘텐츠가 늘면 이 자리를 채운다. ID는 안 밀린다.', eol]

        for k in range(n):
            pad.append('\t"",')

            if k % 8 == 7:
                pad.append(eol)

        if not pad[-1].endswith(eol):
            pad.append(eol)

        pad.append(eol)
        out = out[:at] + ''.join(pad) + out[at:]
        print('  %6d 앞에 %2d칸 : %s' % (idx, n, why))

    #다시 세어 확인한다.
    m2 = re.search(r'const\s+char\s*\*\s*const\s+textId\s*\[\s*\]\s*=\s*\{', out)
    starts2, _ = elem_starts(mask_untaken(out), m2.end())

    if len(starts2) != NEW_COUNT:
        sys.stderr.write('넣고 나니 %d개다. %d개여야 한다.\n'
                         % (len(starts2), NEW_COUNT))
        return 1

    print('  -> %d개 (TEXT_LENGTH 와 같아야 한다)' % len(starts2))

    if not args.write:
        print('  (실제로 쓰려면 --write)')
        return 0

    with io.open(PATH, 'w', encoding='utf-8-sig', newline='') as fp:
        fp.write(out)

    print('  썼다: Classes/Text.h')
    return 0


if __name__ == '__main__':
    sys.exit(main())
