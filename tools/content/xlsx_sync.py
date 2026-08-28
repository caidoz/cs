# -*- coding: utf-8 -*-
"""content/*.tsv <-> content/*.xlsx

밸런스는 엑셀에서 잡고, 값은 tsv 를 거쳐 소스로 간다.

    엑셀  ->  tsv  ->  Data/*.cpp  ->  content.pack
          이 도구      content_table.py   build_pack.py

[왜 tsv 를 거치나]
.cpp 를 쓰는 도구는 content_table.py 하나여야 한다. 그 도구가 6666 칸을
한 칸씩 대조하는 verify 를 들고 있다. 엑셀에서 .cpp 로 바로 쓰면 그 검사를
건너뛰게 되고, 검사 없는 경로가 하나 생기면 없는 것과 같다.

[쓰는 법]
    python tools/content/xlsx_sync.py export          #tsv -> xlsx (전부)
    python tools/content/xlsx_sync.py export unit     #한 묶음만
    python tools/content/xlsx_sync.py import unit     #xlsx -> tsv
    python tools/content/xlsx_sync.py import unit --build
                                                      #tsv -> 소스 -> 팩까지

[정렬 금지]
엑셀에는 정렬 버튼이 있다. 그런데 이 표의 id 는 세이브 파일과 서버 DB 에
이미 나간 번호다(content/README.md). 한 줄이라도 자리가 바뀌면 남의
슬라임이 해골이 된다.

그래서 import 는 값을 쓰기 전에 세 가지를 본다.

    1. id 가 0 부터 하나씩 오르는가   <- 정렬을 잡는다
    2. 열 이름이 그대로인가            <- 열을 끼우거나 지운 것을 잡는다
    3. 줄 수가 그대로인가              <- 줄을 지운 것을 잡는다

하나라도 어긋나면 아무것도 쓰지 않고 멈춘다.
"""
import argparse
import io
import os
import subprocess
import sys

import openpyxl
from openpyxl.styles import Alignment, Border, Font, PatternFill, Side
from openpyxl.utils import get_column_letter
from openpyxl.worksheet.datavalidation import DataValidation

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, '..', '..'))
CONTENT = os.path.join(ROOT, 'content')

#---------------------------------------------------------------- 묶음
#
#한 파일이 질문 하나에 답하게 나눈다. "어느 .cpp 에 있느냐"가 아니라
#"한 번에 같이 잡는 것이냐"가 기준이다.
BOOKS = {
    'unit': {
        'title': '적과 동료와 스킬',
        'tables': ['enemy', 'crew', 'skill'],
        'note': '적이 얼마나 센가. 동료가 무엇을 하는가.',
    },
}

#열 설명. 없는 열은 이름만 나온다.
DESC = {
    'skill': {
        'kind': '종류. 이 값이 나머지 칸의 뜻을 정한다',
        'value': '효능 수치 (히어로 스킬의 버프 % 등)',
        'hit_max': '한 번에 몇 대까지. 1 이면 단발',
        'dmg_pct': '한 대가 기본공격의 몇 %. 100 이 그대로, 300 이 3 배',
        'cooldown': '재사용 대기 (히어로 스킬)',
        'icon': '아이콘 번호',
        'icon_kind': '아이콘이 어느 그림판에서 오는가',
        'star': '카드의 별',
        'attack_type': '어떤 공격으로 나가는가',
        'host_obj': '어느 오브젝트 칸에서 벌어지는가',
        'summon_enemy': '불러낼 몬스터 (SUMMON)',
        'hero_type': '불러낼 히어로 (SUMMONHERO)',
        'hero_skill': '발동시킬 히어로 스킬',
        'summon_x': '소환체가 설 x. 0 이면 화면 중앙',
        'bullet_obj': '총알 오브젝트 (CREWBULLET)',
        'bullet_icon': '총알 그림 (CREWBULLET)',
        'equip1': '소환 히어로에게 입힐 장비 (SUMMONHERO)',
    },
    'crew': {
        'enemy_type': '어느 몬스터 그림을 쓰는가',
        'str': '기본 공격력. 여기에 별 x 레벨 배율이 곱해진다',
        'skill1': '슬롯에 1 개 떴을 때',
        'skill2': '슬롯에 2 개 떴을 때',
        'skill3': '슬롯에 3 개 떴을 때',
        'card_bg': '카드 뒷그림',
    },
    'enemy': {
        'cmf': '그림 묶음',
        'star': '등급',
        'stat_hp': '체력',
        'stat_str': '공격력',
        'stat_def': '방어력. 데미지에서 절대값으로 빠진다',
        'add_exp': '잡았을 때 주는 경험치',
        'home_castle': '어느 지역 출신인가',
    },
}

#칸 이름에 이 말이 들어 있으면 그 색으로 묶어 보여준다
GROUPS = [
    (('id', 'enum_name', 'label'), 'FF1B365D'),      #이름표. 고치면 안 되는 것
    (('star', 'grade', 'kind'), 'FF8E44AD'),         #등급/종류
    (('str', 'stat_', 'value', 'dmg_', 'hit_'), 'FFC0392B'),   #세기
    (('icon', 'cmf', 'pose_', 'zoom', 'bigicon', 'skillicon'), 'FF16A085'),  #그림
    (('skill', 'hero_', 'summon', 'bullet', 'equip'), 'FFD35400'),           #참조
]
DEFCOLOR = 'FF7F8C8D'

FONT_HEAD = Font(name='맑은 고딕', size=10, bold=True, color='FFFFFFFF')
FONT_ID = Font(name='Consolas', size=10, bold=True, color='FF7F8C8D')
FONT_CELL = Font(name='Consolas', size=10)
FONT_NAME = Font(name='맑은 고딕', size=10)
THIN = Side(style='thin', color='FFD0D3D4')
BORDER = Border(left=THIN, right=THIN, top=THIN, bottom=THIN)
FILL_LOCK = PatternFill('solid', start_color='FFF2F3F4', end_color='FFF2F3F4')


def color_of(col):
    for keys, c in GROUPS:
        for k in keys:
            if col == k or col.startswith(k):
                return c
    return DEFCOLOR


def tsv_path(name):
    return os.path.join(CONTENT, name + '.tsv')


def xlsx_path(book):
    return os.path.join(CONTENT, book + '.xlsx')


def read_tsv(name):
    """(주석줄, 열이름, 행들)"""
    with io.open(tsv_path(name), encoding='utf-8', newline='') as fp:
        raw = fp.read()

    nl = '\r\n' if '\r\n' in raw else '\n'
    lines = raw.split(nl)
    head = [l for l in lines if l.startswith('#')]
    body = [l for l in lines if l and not l.startswith('#')]

    return head, body[0].split('\t'), [l.split('\t') for l in body[1:]], nl


def write_tsv(name, head, cols, rows, nl):
    out = head + ['\t'.join(cols)] + ['\t'.join(r) for r in rows]

    with io.open(tsv_path(name), 'w', encoding='utf-8', newline='') as fp:
        fp.write(nl.join(out) + nl)


#---------------------------------------------------------------- 내보내기

def sheet_from(wb, name):
    head, cols, rows, _ = read_tsv(name)
    ws = wb.create_sheet(name)

    for c, col in enumerate(cols, start=1):
        cell = ws.cell(1, c, col)
        cell.font = FONT_HEAD
        cell.fill = PatternFill('solid', start_color=color_of(col),
                                end_color=color_of(col))
        cell.alignment = Alignment(horizontal='center', vertical='center',
                                   wrap_text=True)
        cell.border = BORDER

        d = DESC.get(name, {}).get(col)

        if d:
            cell.comment = openpyxl.comments.Comment(d, 'xlsx_sync')

    for r, row in enumerate(rows, start=2):
        for c, v in enumerate(row, start=1):
            cell = ws.cell(r, c, num(v))
            cell.border = BORDER

            if c <= 3:
                cell.font = FONT_ID if c == 1 else FONT_NAME
                cell.fill = FILL_LOCK
            else:
                cell.font = FONT_CELL

    #머리글과 이름 세 칸을 붙들어 둔다
    ws.freeze_panes = 'D2'
    ws.auto_filter.ref = None       #필터를 달면 정렬을 부른다. 달지 않는다

    #kind 같은 칸은 지금 표에 있는 값만 고르게 한다
    for c, col in enumerate(cols, start=1):
        vals = sorted(set(r[c - 1] for r in rows))

        if col in ('kind', 'icon_kind') and 1 < len(vals) <= 20:
            dv = DataValidation(type='list',
                                formula1='"%s"' % ','.join(vals),
                                allow_blank=False)
            ws.add_data_validation(dv)
            dv.add('%s2:%s%d' % (get_column_letter(c), get_column_letter(c),
                                 len(rows) + 1))

    #열 너비
    for c, col in enumerate(cols, start=1):
        w = max(len(col) + 2,
                max((len(str(r[c - 1])) for r in rows), default=4) + 2)
        ws.column_dimensions[get_column_letter(c)].width = min(w, 30)

    ws.row_dimensions[1].height = 30

    return len(rows), len(cols)


def guide(wb, book):
    ws = wb.create_sheet('읽기', 0)
    L = [
        (BOOKS[book]['title'], True),
        (BOOKS[book]['note'], False),
        ('', False),
        ('[고치는 법]', True),
        ('1. 값을 고친다', False),
        ('2. 저장하고 엑셀을 닫는다', False),
        ('3. python tools/content/xlsx_sync.py import %s --build' % book, False),
        ('', False),
        ('[하면 안 되는 것]', True),
        ('줄을 정렬하지 말 것. id 는 세이브와 서버에 이미 나간 번호라,',
         False),
        ('자리가 바뀌면 남의 슬라임이 해골이 된다.', False),
        ('줄이나 열을 지우거나 끼우지도 말 것.', False),
        ('', False),
        ('import 가 id 순서와 열 이름과 줄 수를 보고, 어긋나면 아무것도',
         False),
        ('쓰지 않고 멈춘다. 그래도 되돌리는 것보다 안 하는 편이 낫다.',
         False),
        ('', False),
        ('[새 줄을 넣으려면]', True),
        ('맨 끝에만 붙인다. 그리고 Def/*.h 의 열거에도 같은 이름을 맨',
         False),
        ('끝에 넣어야 한다. 그건 아직 손으로 한다.', False),
        ('', False),
        ('[열 색]', True),
        ('남색 = 이름표(고치지 말 것)   보라 = 등급/종류', False),
        ('빨강 = 세기                   초록 = 그림', False),
        ('주황 = 다른 표를 가리키는 값', False),
    ]

    for i, (t, b) in enumerate(L, start=1):
        cell = ws.cell(i, 1, t)
        cell.font = Font(name='맑은 고딕', size=11, bold=b)

    ws.column_dimensions['A'].width = 70


def num(v):
    """숫자로 보이면 숫자로. 엑셀에서 계산할 수 있게."""
    try:
        return int(v)
    except (TypeError, ValueError):
        return v


def do_export(book):
    wb = openpyxl.Workbook()
    wb.remove(wb.active)

    for t in BOOKS[book]['tables']:
        r, c = sheet_from(wb, t)
        print('  %-8s %4d행 x %2d열' % (t, r, c))

    guide(wb, book)
    p = xlsx_path(book)

    try:
        wb.save(p)
    except PermissionError:
        sys.exit('%s 를 못 쓴다. 엑셀에서 열려 있으면 닫아라' % p)

    print('%s' % p)


#---------------------------------------------------------------- 들여오기

def do_import(book, build):
    p = xlsx_path(book)

    if not os.path.isfile(p):
        sys.exit('%s 가 없다. 먼저 export 해라' % p)

    wb = openpyxl.load_workbook(p, data_only=True)
    plan = []

    for name in BOOKS[book]['tables']:
        if name not in wb.sheetnames:
            sys.exit('%s 시트가 없다' % name)

        ws = wb[name]
        head, cols, rows, nl = read_tsv(name)

        got = [ws.cell(1, c).value for c in range(1, len(cols) + 1)]

        if got != cols:
            sys.exit('%s : 열 이름이 다르다\n  표 %s\n  엑셀 %s'
                     % (name, cols, got))

        if ws.max_row - 1 != len(rows):
            sys.exit('%s : 줄이 %d개여야 하는데 %d개다'
                     % (name, len(rows), ws.max_row - 1))

        new = []

        for r in range(2, len(rows) + 2):
            vals = []

            for c in range(1, len(cols) + 1):
                v = ws.cell(r, c).value
                vals.append('' if v is None else str(v).strip())

            #id 가 제자리인가. 정렬을 여기서 잡는다.
            if vals[0] != rows[r - 2][0]:
                sys.exit('%s : %d번째 줄의 id 가 %s 여야 하는데 %s 다.\n'
                         '정렬했거나 줄을 옮긴 것 같다. 아무것도 쓰지 않았다.'
                         % (name, r - 1, rows[r - 2][0], vals[0]))

            new.append(vals)

        changed = sum(1 for a, b in zip(rows, new) for x, y in zip(a, b)
                      if x != y)
        plan.append((name, head, cols, new, nl, changed))

    for name, head, cols, new, nl, changed in plan:
        write_tsv(name, head, cols, new, nl)
        print('  %-8s %d칸 바뀜' % (name, changed))

    if build:
        for name in BOOKS[book]['tables']:
            subprocess.check_call([sys.executable,
                                   os.path.join(HERE, 'content_table.py'),
                                   name, 'generate', '--write'])

        subprocess.check_call([sys.executable,
                               os.path.join(HERE, 'build_pack.py')])


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('what', choices=['export', 'import'])
    ap.add_argument('book', nargs='?', default=None,
                    help='묶음 이름. 없으면 전부')
    ap.add_argument('--build', action='store_true',
                    help='import 뒤에 소스와 팩까지 다시 낸다')
    a = ap.parse_args()

    books = [a.book] if a.book else sorted(BOOKS)

    for b in books:
        if b not in BOOKS:
            sys.exit('%s 는 없는 묶음이다. 있는 것 : %s'
                     % (b, ', '.join(sorted(BOOKS))))

        print('[%s]' % b)

        if a.what == 'export':
            do_export(b)
        else:
            do_import(b, a.build)


main()
