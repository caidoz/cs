# -*- coding: utf-8 -*-
"""동료 64명의 공격력을 다시 깐다.

[무엇에 맞추는가]
동료의 세기는 혼자 정할 수 없다. "그 시점에 주인공이 들고 있을 무기"의 절반이
되어야 한다. 그래서 무기 표와 짝을 지어 놓고 거기서 값을 끌어온다.

    스테이지 500개마다 무기 한 자루      -> 검 35자루 = 17,500 스테이지
    같은 구간에 동료 64명을 펼친다
    동료 = 그 시점 무기의 절반

    첫 동료  = 첫 검(10) / 2   =   5
    끝 동료  = 끝 검(999) / 2  = 500

[등급 안에서는 미세하게, 등급이 바뀌면 크게]
등급이 곧 뽑기의 값어치다. 그러니 계단은 등급에서 져야 한다. 같은 등급 안에서
뒤 번호가 조금씩 센 것은 "같은 값이면 나중 것이 조금 낫다" 정도의 차이다.

    등급 안 : 첫 -> 끝 이 x1.35 (9~15명에 나눠 지므로 한 명당 3~4%)
    등급 간 : x2.37

    5 * 2.37^5 * 1.35 = 500

[생김새]
같은 등급 같은 자리라도 꼬마와 장군이 같은 값이면 이상하다. 아래 MOD 표가
그 몫이다. 여자/아이/노인은 낮게, 덩치와 전투 직군은 높게 잡았다.

이 표는 이름만 보고 눈대중으로 매긴 것이다. 그림을 보고 고치는 게 맞다.
고친 뒤 이 스크립트를 다시 돌리면 된다.

[레벨]
1~14레벨에 x4. 한 레벨당 +11.3%다. skillData 는 15칸을 들고 있는데 마지막
칸은 안 쓰이므로 14레벨과 같은 값을 넣는다.

[어디에 쓰는가]
동료의 공격력은 crewData 가 아니라 그 동료의 첫 번째 스킬이 들고 있다.

    GetCrewPower(detail, lv)
        -> skillData[ crewData[detail].SKILL1 ][ VALUE_LV1 + lv-1 ]

여러 동료가 같은 스킬을 가리키는 일은 없는지 먼저 확인하고 쓴다. 겹치면
한쪽을 고칠 때 다른 쪽이 딸려 움직인다.

    python tools/content/balance_crew.py
    python tools/content/balance_crew.py --write
"""
import argparse
import io
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import content_table as CT

PATH = os.path.join(CT.CLASSES, 'Data', 'SkillData.cpp')

TOTAL_CREW = 64
SKILLDATASIZE = 29
VALUE_LV1 = 6
VALUE_CNT = 15
MAX_LV = 14

#등급별 인원. 합이 64여야 한다.
TIER = [9, 10, 10, 10, 10, 15]

FIRST = 5.0         #첫 동료
LAST = 500.0        #끝 동료
IN_TIER = 1.35      #등급 안에서 첫 -> 끝
LV_GAIN = 4.0       #1레벨 -> 14레벨

#생김새 보정. 이름만 보고 매긴 첫 판이다.
MOD = [
    #1성
    0.85, 0.88, 0.85, 1.00, 1.12, 0.90, 1.05, 0.90, 1.15,
    #2성
    1.15, 1.18, 0.92, 1.05, 1.05, 0.95, 0.90, 0.95, 1.18, 0.90,
    #3성
    1.20, 0.85, 0.88, 0.88, 1.00, 0.90, 0.88, 1.12, 1.12, 0.90,
    #4성
    0.92, 0.98, 0.90, 1.05, 0.95, 1.08, 1.12, 1.20, 0.88, 1.00,
    #5성
    1.18, 0.92, 1.05, 1.08, 1.00, 1.22, 0.95, 1.08, 1.15, 1.10,
    #6성
    1.00, 1.25, 0.90, 1.05, 1.05, 0.92, 0.90, 1.10, 1.25, 1.20,
    1.10, 1.00, 1.08, 0.88, 1.20,
]


def base_curve():
    """등급과 자리로 정해지는 기본값. 생김새 보정 전이다."""
    #5 * J^5 * IN_TIER = 500
    jump = (LAST / FIRST / IN_TIER) ** (1.0 / (len(TIER) - 1))
    out = []

    for t, n in enumerate(TIER):
        head = FIRST * jump ** t

        for k in range(n):
            ramp = IN_TIER ** (k / float(n - 1)) if n > 1 else 1.0
            out.append(head * ramp)

    return out, jump


def levels(lv1):
    """1레벨 값에서 15칸을 만든다."""
    r = LV_GAIN ** (1.0 / (MAX_LV - 1))
    out = [max(1, int(round(lv1 * r ** i))) for i in range(MAX_LV)]

    #마지막 칸은 쓰이지 않지만 비워둘 수 없다.
    while len(out) < VALUE_CNT:
        out.append(out[-1])

    return out


def crew_skill1():
    """동료마다 첫 번째 스킬 번호.

    소스의 crewData 는 NPC_BOY_SKILL1 같은 이름으로 적혀 있어서 눈으로
    읽을 수 없다. 이미 컴파일러가 풀어 놓은 팩에서 가져온다.
    """
    import struct

    path = os.path.join(CT.ROOT, 'Resources', 'data', 'content.pack')
    buf = open(path, 'rb').read()
    namelen, entry = 32, 48
    _magic, _abi, count, _body = struct.unpack_from('<IIiI', buf, 0)
    dat = 16 + count * entry

    for i in range(count):
        e = 16 + i * entry

        if buf[e:e + namelen].split(b'\0')[0].decode() != 'crewData':
            continue

        cells, off = struct.unpack_from('<II', buf, e + namelen + 4)
        vals = struct.unpack_from('<%di' % cells, buf, dat + off)

        if cells != TOTAL_CREW * 6:
            raise SystemExit('crewData 가 %d개다' % cells)

        return [vals[c * 6 + 2] for c in range(TOTAL_CREW)]

    raise SystemExit('팩에 crewData 가 없다')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--write', action='store_true')
    args = ap.parse_args()

    if sum(TIER) != TOTAL_CREW:
        raise SystemExit('등급 인원 합이 %d다' % sum(TIER))

    if len(MOD) != TOTAL_CREW:
        raise SystemExit('MOD 가 %d개다' % len(MOD))

    base, jump = base_curve()
    skill1 = crew_skill1()

    #같은 스킬을 두 동료가 나눠 쓰면 한쪽만 고칠 수 없다.
    seen = {}

    for c, s in enumerate(skill1):
        if s in seen:
            raise SystemExit('동료 %d 와 %d 가 스킬 %d 를 같이 쓴다'
                             % (seen[s], c, s))
        seen[s] = c

    print('  등급 간 x%.3f, 등급 안 x%.2f' % (jump, IN_TIER))

    text = CT.read(PATH)
    eol = '\r\n' if '\r\n' in text else '\n'
    lines = text.split(eol)

    #skillData 의 몇 번째 줄이 몇 번 스킬인지.
    #
    #한 줄이 스킬 하나다. 그러니 세면 된다. 줄 끝 주석에도 번호가 붙어 있어서
    #센 값과 맞는지 대조한다. 어긋나면 데이터가 한 줄에 두 개 들어 있다는 뜻이라
    #세는 것을 믿을 수 없으므로 멈춘다.
    start = None

    for i, line in enumerate(lines):
        if 'skillData_builtin[]' in line:
            start = i + 1
            break

    if start is None:
        raise SystemExit('skillData_builtin 을 못 찾았다')

    rowline = {}
    row = 0

    for i in range(start, len(lines)):
        line = lines[i]

        if line.strip().startswith('};'):
            break

        if line.count(',') < SKILLDATASIZE - 1:
            continue

        m = re.search(r'//(\d+)\b', line)

        if m and int(m.group(1)) != row:
            raise SystemExit('%d번째 줄인데 주석은 %d번이라 한다 (줄 %d)'
                             % (row, int(m.group(1)), i + 1))

        rowline[row] = i
        row += 1

    print('  skillData %d줄' % row)

    changed = 0

    for c in range(TOTAL_CREW):
        want = base[c] * MOD[c]
        vals = levels(want)
        s = skill1[c]

        if s not in rowline:
            raise SystemExit('스킬 %d 의 줄을 못 찾았다' % s)

        i = rowline[s]
        cells = lines[i].split(',')

        if len(cells) < SKILLDATASIZE:
            raise SystemExit('스킬 %d 줄의 칸이 %d개다' % (s, len(cells)))

        for k in range(VALUE_CNT):
            cells[VALUE_LV1 + k] = ' %d' % vals[k]

        lines[i] = ','.join(cells)
        changed += 1

        if c < 3 or c >= TOTAL_CREW - 3:
            print('    #%-2d skill%-5d lv1=%-4d lv14=%-5d (기본 %.1f x %.2f)'
                  % (c, s, vals[0], vals[MAX_LV - 1], base[c], MOD[c]))
        elif c == 3:
            print('    ...')

    print('  %d명' % changed)

    if not args.write:
        print('  (실제로 쓰려면 --write)')
        return 0

    with io.open(PATH, 'w', encoding='utf-8-sig', newline='') as fp:
        fp.write(eol.join(lines))

    print('  썼다: Classes/Data/SkillData.cpp')
    return 0


if __name__ == '__main__':
    sys.exit(main())
