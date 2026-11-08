# -*- coding: utf-8 -*-
"""밸런스 표를 소스로 낸다.

    content/balance.tsv      -> Classes/Config/BalanceGenerated.h
    content/gear_role.tsv    -> Classes/Data/GearRoleTable.inc
    content/shop_part.tsv    -> Classes/Data/ShopPartTable.inc
    content/hero_allies_balance.tsv -> Classes/Data/AllyBalanceData.h
                                       (tools/crew/build_ally_balance.py)

[왜 생성기인가]
이 넷은 밸런스의 손잡이인데 전부 C++ 리터럴이라 엑셀 경로 밖에 있었다.
곡선을 만지려면 헤더를 열어 숫자를 찾아야 했고, 어떤 값이 어느 곡선에
붙어 있는지는 주석을 읽어야만 알 수 있었다.

표로 빼면 엑셀 한 칸이 곧 곡선이다(tools/content/xlsx_sync.py 의 balance
묶음). note 열이 주석을 대신하므로 설명도 표 안에 남는다.

[값은 C++ 토막 그대로 적는다]
balance.tsv 의 value 는 숫자가 아니라 "그 자리에 들어갈 C++ 글자" 다.
0.82f 도, (64 * _2X) 도 그대로 적는다. 파이썬이 수를 해석하면 float 와
int 가 뒤바뀌거나 식이 평평해져서, 소스에서 보던 것과 다른 값이 된다.

    python tools/content/make_balance.py
    python tools/content/make_balance.py --check   #내지 않고 보기만
"""
import argparse
import io
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
CONTENT = os.path.join(ROOT, 'content')
CLASSES = os.path.join(ROOT, 'Classes')


def read_tsv(name):
    path = os.path.join(CONTENT, name + '.tsv')
    rows = []
    with io.open(path, encoding='utf-8') as fp:
        for line in fp.read().splitlines():
            if not line or line.startswith('#'):
                continue
            rows.append(line.split('\t'))
    return rows[0], rows[1:]


def write(path, text, check):
    old = ''
    if os.path.exists(path):
        with io.open(path, encoding='utf-8-sig') as fp:
            old = fp.read()
    if old == text:
        print('  그대로  %s' % os.path.relpath(path, ROOT))
        return False
    if check:
        print('  바뀜    %s' % os.path.relpath(path, ROOT))
        return True
    with io.open(path, 'w', encoding='utf-8-sig', newline='\r\n') as fp:
        fp.write(text)
    print('  썼다    %s' % os.path.relpath(path, ROOT))
    return True


BANNER = ('//이 파일은 %s 에서 자동으로 났다.\n'
          '//손으로 고치지 마라 - 다음 생성에서 지워진다.\n'
          '//값을 고칠 곳은 content/%s.tsv (또는 content/balance.xlsx) 다.\n'
          '//    python tools/content/make_balance.py\n')


def balance(check):
    head, rows = read_tsv('balance')
    assert head[:3] == ['name', 'value', 'note'], head
    width = max(len(r[0]) for r in rows)
    out = ['#pragma once', '', BANNER % ('content/balance.tsv', 'balance'), '']
    out.append('#ifndef _CONFIG_BALANCE_GENERATED_H_')
    out.append('#define _CONFIG_BALANCE_GENERATED_H_')
    out.append('')
    for name, value, note in ((r + ['', '', ''])[:3] for r in rows):
        if note:
            out.append('//%s' % note)
        out.append('#define %-*s %s' % (width, name, value))
        out.append('')
    out.append('#endif')
    out.append('')
    return write(os.path.join(CLASSES, 'Config', 'BalanceGenerated.h'),
                 '\n'.join(out), check)


def gear_role(check):
    head, rows = read_tsv('gear_role')
    cols = ['type', 'primary', 'second', 'line', 'defPer', 'hpPer', 'atkPct',
            'critPct', 'coolPct', 'dodgePct', 'leechPct', 'hpRegen',
            'shieldRegen', 'gold']
    assert head == cols, head
    widths = [max(len(r[i]) for r in rows) for i in range(len(cols))]
    out = [BANNER % ('content/gear_role.tsv', 'gear_role'), '']
    out.append('static const GearRoleSpec kGearRole[] = {')
    for r in rows:
        cells = ['%-*s' % (widths[i], r[i]) for i in range(4)]
        nums = ['%*s' % (max(3, widths[i]), r[i]) for i in range(4, len(cols))]
        out.append('\t{ %s, %s },' % (', '.join(cells), ', '.join(nums)))
    out.append('};')
    out.append('')
    return write(os.path.join(CLASSES, 'Data', 'GearRoleTable.inc'),
                 '\n'.join(out), check)


def shop_part(check):
    head, rows = read_tsv('shop_part')
    cols = ['type', 'detail', 'grade', 'w', 'h', 'price', 'name', 'rot',
            'cells']
    assert head == cols, head
    widths = [max(len(r[i]) for r in rows) for i in range(len(cols))]
    out = [BANNER % ('content/shop_part.tsv', 'shop_part'), '']
    out.append('static const GridPart kShopPart[GRIDTEST_SHOPCNT+2] = {')
    for r in rows:
        out.append('\t{ %-*s, %*s, %-*s, %s, %s, %*s, "%s", %s, %s },' % (
            widths[0], r[0], widths[1], r[1], widths[2], r[2], r[3], r[4],
            widths[5], r[5], r[6], r[7], r[8]))
    out.append('};')
    out.append('')
    return write(os.path.join(CLASSES, 'Data', 'ShopPartTable.inc'),
                 '\n'.join(out), check)


def allies(check):
    tool = os.path.join(ROOT, 'tools', 'crew', 'build_ally_balance.py')
    if not os.path.exists(tool):
        print('  없음    tools/crew/build_ally_balance.py')
        return False
    if check:
        print('  건너뜀  동료 표는 --check 로 안 본다')
        return False
    subprocess.check_call([sys.executable, tool])
    return True


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--check', action='store_true', help='내지 않고 보기만')
    a = ap.parse_args()

    changed = False
    for step in (balance, gear_role, shop_part, allies):
        changed = step(a.check) or changed

    if a.check:
        print('바뀐 것이 %s' % ('있다' if changed else '없다'))
    return 0


if __name__ == '__main__':
    sys.exit(main())
