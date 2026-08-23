# -*- coding: utf-8 -*-
"""적 스킬 자리(1071개)를 데이터에서 걷어낸다.

[무엇을 지우는가]
skillData 는 히어로 90개 + 적 1071개 + 동료 213개 = 1374줄이었다. 가운데
1071줄은 이름만 ENEMY_IFRIT_BLACK_SKILL3 식으로 붙어 있을 뿐, 팩에서 꺼내
1071줄을 전부 비교해 보면 한 글자도 다르지 않은 같은 값이다. 읽는 코드도
없다(적의 공격은 enemyStatInfo 와 monStr 로 굴러간다).

[같이 지워야 하는 것]
텍스트가 스킬 번호로 색인된다.

    TEXTPTR(TEXT_SKILLNAME_COMMON_ROBIN1 + skillIdx)      Func_Menu

그래서 skillData 만 지우면 동료 스킬 번호가 앞으로 밀리면서 이름이 어긋난다.
네 곳을 같은 폭으로 함께 지운다.

    Classes/Def/SkillDef.h    ENEMY_*_SKILL*            1071줄
    Classes/Data/SkillData.cpp  그 줄들                  1071줄
    Classes/Def/TextDef.h     TEXT_SKILLNAME_ENEMY*     1071줄
                              TEXT_SKILLDESC_ENEMY*     1071줄
    Classes/Text.h            위 둘에 해당하는 문자열    2142개
    Classes/Data/SkillData.h  skillData_COUNT

[밀리는 것]
    스킬 번호  1161~1373 -> 90~302
    텍스트 번호 그 뒤 전부 -> 2142칸 앞으로

번호가 밀리므로 이미 나간 클라이언트는 새 팩을 못 읽는다. 출시 전에만 할 수
있는 정리다.

    python tools/content/drop_enemy_skills.py
    python tools/content/drop_enemy_skills.py --write
"""
import argparse
import io
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT
import relayout_text as RT

ROOT = CT.ROOT
CLASSES = CT.CLASSES

SKILLDEF = os.path.join(CLASSES, 'Def', 'SkillDef.h')
SKILLDATA = os.path.join(CLASSES, 'Data', 'SkillData.cpp')
TEXTDEF = os.path.join(CLASSES, 'Def', 'TextDef.h')
TEXTH = os.path.join(CLASSES, 'Text.h')
#DataList.h 는 make_pack.py 가 생성한다. 개수의 출처는 이쪽 헤더다.
COUNTHDR = os.path.join(CLASSES, 'Data', 'SkillData.h')

SKILLDATASIZE = 29

#컴파일러가 알려준 값. 바뀌면 여기서 멈춘다.
NAME_LO, NAME_HI = 3268, 4338
DESC_LO, DESC_HI = 4642, 5712
DROP_ROWS = 1071
OLD_ROWS = 1374
OLD_TEXT = 10318


def drop_lines(path, pattern, want, out):
    """정규식에 걸리는 줄을 지운다."""
    text = CT.read(path)
    eol = '\r\n' if '\r\n' in text else '\n'
    lines = text.split(eol)
    keep = [L for L in lines if not re.search(pattern, L)]
    gone = len(lines) - len(keep)

    if gone != want:
        raise SystemExit('%s 에서 %d줄이 걸렸다. %d줄이어야 한다.'
                         % (os.path.basename(path), gone, want))

    print('  %-22s %d줄' % (os.path.basename(path), gone))
    out[path] = eol.join(keep)


def drop_skill_rows(out):
    """skillData 의 적 구간 행을 지운다. 줄 끝 주석 번호로 자리를 확인한다."""
    text = CT.read(SKILLDATA)
    eol = '\r\n' if '\r\n' in text else '\n'
    lines = text.split(eol)

    start = next(i for i, L in enumerate(lines) if 'skillData_builtin[]' in L) + 1

    keep = list(lines[:start])
    row = 0
    gone = 0
    tail = start

    for i in range(start, len(lines)):
        if lines[i].strip().startswith('};'):
            tail = i
            break

        if lines[i].count(',') < SKILLDATASIZE - 1:
            keep.append(lines[i])
            continue

        m = re.search(r'//(\d+)\b', lines[i])

        if m and int(m.group(1)) != row:
            raise SystemExit('%d번째 줄인데 주석은 %s' % (row, m.group(1)))

        #히어로 90개 뒤부터 동료 시작 전까지가 적 구간이다.
        if 90 <= row < 90 + DROP_ROWS:
            gone += 1
        else:
            keep.append(lines[i])

        row += 1

    if row != OLD_ROWS:
        raise SystemExit('skillData 가 %d줄이다. %d줄이어야 한다.' % (row, OLD_ROWS))

    if gone != DROP_ROWS:
        raise SystemExit('%d줄만 걸렸다' % gone)

    keep.extend(lines[tail:])
    print('  %-22s %d줄 (남는 줄 %d)'
          % ('SkillData.cpp', gone, row - gone))
    out[SKILLDATA] = eol.join(keep)


def drop_text_elems(out):
    """Text.h 의 textId[] 에서 해당 자리의 문자열을 걷어낸다."""
    text = CT.read(TEXTH)
    m = re.search(r'const\s+char\s*\*\s*const\s+textId\s*\[\s*\]\s*=\s*\{', text)
    starts, close = RT.elem_starts(RT.mask_untaken(text), m.end())

    if len(starts) != OLD_TEXT:
        raise SystemExit('textId 가 %d개다. %d개여야 한다.'
                         % (len(starts), OLD_TEXT))

    bounds = starts + [close]
    out_text = text

    #뒤 구간부터 지워야 앞 구간의 자리가 안 밀린다.
    for lo, hi in ((DESC_LO, DESC_HI), (NAME_LO, NAME_HI)):
        out_text = out_text[:bounds[lo]] + out_text[bounds[hi + 1]:]
        print('  %-22s [%d..%d] %d개' % ('Text.h', lo, hi, hi - lo + 1))

    #다시 세어 확인한다.
    m2 = re.search(r'const\s+char\s*\*\s*const\s+textId\s*\[\s*\]\s*=\s*\{', out_text)
    starts2, _ = RT.elem_starts(RT.mask_untaken(out_text), m2.end())
    want = OLD_TEXT - (NAME_HI - NAME_LO + 1) - (DESC_HI - DESC_LO + 1)

    if len(starts2) != want:
        raise SystemExit('지우고 나니 %d개다. %d개여야 한다.' % (len(starts2), want))

    print('  textId  %d -> %d' % (OLD_TEXT, len(starts2)))
    out[TEXTH] = out_text


def fix_count(out):
    """skillData 의 원소 수를 새 줄 수에 맞춘다.

    DataList.h 를 고쳐도 소용없다. 그 파일은 make_pack.py 가 이 헤더의
    _COUNT 를 읽어 매번 새로 만든다. 고칠 곳은 여기다.
    """
    text = CT.read(COUNTHDR)
    old = OLD_ROWS * SKILLDATASIZE
    new = (OLD_ROWS - DROP_ROWS) * SKILLDATASIZE
    a = 'enum { skillData_COUNT = %d };' % old
    b = 'enum { skillData_COUNT = %d };' % new

    if text.count(a) != 1:
        raise SystemExit('SkillData.h 의 skillData_COUNT 를 못 찾았다')

    print('  %-22s %d -> %d' % ('SkillData.h', old, new))
    out[COUNTHDR] = text.replace(a, b)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--write', action='store_true')
    args = ap.parse_args()

    out = {}

    drop_lines(SKILLDEF, r'^\s*ENEMY_[A-Z0-9_]*_SKILL\d\s*,', DROP_ROWS, out)
    drop_skill_rows(out)
    drop_lines(TEXTDEF, r'^\s*TEXT_SKILLNAME_ENEMY[A-Z0-9_]*\s*,', DROP_ROWS, out)

    #앞 호출이 이미 이름 쪽을 지운 결과를 받아야 설명 쪽 개수가 맞다.
    tmp = {}
    saved = CT.read
    CT.read = lambda p, _o=saved, _b=out: _b[p] if p in _b else _o(p)
    drop_lines(TEXTDEF, r'^\s*TEXT_SKILLDESC_ENEMY[A-Z0-9_]*\s*,', DROP_ROWS, tmp)
    CT.read = saved
    out[TEXTDEF] = tmp[TEXTDEF]

    drop_text_elems(out)
    fix_count(out)

    if not args.write:
        print('  (실제로 쓰려면 --write)')
        return 0

    for path, body in out.items():
        with io.open(path, 'w', encoding='utf-8-sig', newline='') as fp:
            fp.write(body)

    print('  썼다')
    return 0


if __name__ == '__main__':
    sys.exit(main())
