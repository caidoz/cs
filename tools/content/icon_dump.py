# -*- coding: utf-8 -*-
"""아이콘 시트에서 쓰는 칸만 잘라 낱장 PNG 로 떨군다.

엑셀에 그림을 넣으려면 낱장 파일이 있어야 한다. 게임은 1024x1024 시트에서
64x64 한 칸을 잘라 쓰므로, 여기서도 같은 자리를 같은 식으로 자른다.

    sIcon.png       스킬 아이콘    (idx%16)*64, (idx/16)*64
    crewBullet.png  총알 아이콘    같은 식

게임 코드(Func_Graphics.cpp 의 DrawSkillIcon / DrawCrewBulletIcon)와 자르는
식이 같아야 한다. 다르면 엑셀에서 본 그림과 게임에서 나오는 그림이 달라지고,
그건 없느니만 못하다.

    python tools/content/icon_dump.py            #쓰는 칸만
    python tools/content/icon_dump.py --all      #시트 전체

몬스터(ICONKIND_MONSTER)는 여기서 못 뽑는다. 그건 조각을 겹쳐 그리는
것이라 게임이 직접 그려 줘야 한다. 2 단계에서 한다.
"""
import argparse
import io
import os
import sys

from PIL import Image

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, '..', '..'))
RES = os.path.join(ROOT, 'Resources', 'res')
OUT = os.path.join(ROOT, 'content', 'icon')

TILE = 64          #한 칸의 크기
PER_LINE = 16      #한 줄에 몇 칸

#엑셀에 넣을 크기. 원본 64 를 그대로 넣으면 행이 너무 높아진다.
THUMB = 32

SHEETS = {
    'skill': 'sIcon.png',
    'bullet': 'crewBullet.png',
}

KIND_TO_SHEET = {
    'ICONKIND_SKILL': 'skill',
    'ICONKIND_BULLET': 'bullet',
}


def used_icons():
    """skill.tsv 가 실제로 가리키는 (시트, 번호) 를 모은다."""
    p = os.path.join(ROOT, 'content', 'skill.tsv')

    with io.open(p, encoding='utf-8') as fp:
        lines = [l for l in fp.read().splitlines()
                 if l and not l.startswith('#')]

    cols = lines[0].split('\t')
    ki = cols.index('icon_kind')
    ii = cols.index('icon')

    out = set()
    skipped = 0

    for l in lines[1:]:
        f = l.split('\t')
        sheet = KIND_TO_SHEET.get(f[ki])

        if sheet is None:
            skipped += 1
            continue

        try:
            out.add((sheet, int(f[ii])))
        except ValueError:
            skipped += 1

    return out, skipped


def tile_of(im, idx):
    x = (idx % PER_LINE) * TILE
    y = (idx // PER_LINE) * TILE

    if x + TILE > im.width or y + TILE > im.height:
        return None

    return im.crop((x, y, x + TILE, y + TILE))


def is_blank(im):
    """다 비었는가. 알파가 전부 0 이면 그린 것이 없다."""
    a = im.getchannel('A') if im.mode == 'RGBA' else None

    return a is not None and a.getbbox() is None


def collect_dump():
    """게임이 떨군 캐릭터 PNG 를 content/icon 으로 옮긴다.

    BuildConfig.h 의 DUMP_CMF_PNG 를 1 로 두고 한 번 실행하면 게임이
    쓰기 가능 경로의 dump/ 에 crew_N.png / enemy_N.png 를 떨군다.
    그걸 엑셀에 넣을 크기로 줄여 옮긴다.
    """
    import glob

    cands = []

    for base in (os.environ.get('LOCALAPPDATA', ''), os.path.expanduser('~')):
        if base:
            cands.append(os.path.join(base, 'cs', 'dump'))

    cands.append(os.path.join(ROOT, 'proj.win32', 'Debug.win32', 'dump'))
    cands.append(os.path.join(ROOT, 'dump'))

    src = None

    for c in cands:
        if os.path.isdir(c) and glob.glob(os.path.join(c, '*.png')):
            src = c
            break

    if src is None:
        print('게임이 떨군 dump 폴더를 못 찾았다. 찾아본 곳:')

        for c in cands:
            print('   ' + c)

        print('게임 로그의 "[DUMP] 시작. 저장 위치" 줄을 보고 그 폴더를')
        print('content/icon 으로 직접 옮겨도 된다.')
        return 0

    n = 0

    for p in sorted(glob.glob(os.path.join(src, '*.png'))):
        im = Image.open(p).convert('RGBA')

        #투명한 여백을 잘라낸다. 128 짜리 판에 그린 것이라 대개 남는다.
        box = im.getchannel('A').getbbox()

        if box is None:
            continue

        im = im.crop(box)
        im.thumbnail((THUMB, THUMB), Image.LANCZOS)
        im.save(os.path.join(OUT, os.path.basename(p)))
        n += 1

    print('  %s 에서 %d장 옮김' % (src, n))

    return n


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--collect', action='store_true',
                    help='게임이 떨군 캐릭터 PNG 를 거둬 온다')
    ap.add_argument('--all', action='store_true',
                    help='쓰는 칸만이 아니라 시트를 통째로 자른다')
    a = ap.parse_args()

    if not os.path.isdir(OUT):
        os.makedirs(OUT)

    if a.collect:
        collect_dump()
        return

    if a.all:
        want = None
    else:
        want, skipped = used_icons()
        print('skill.tsv 가 가리키는 칸 %d개 (몬스터 등 %d행은 여기서 못 뽑는다)'
              % (len(want), skipped))

    total = 0
    blank = 0

    for name, fname in sorted(SHEETS.items()):
        p = os.path.join(RES, fname)

        if not os.path.isfile(p):
            sys.exit('%s 가 없다' % p)

        im = Image.open(p).convert('RGBA')
        cnt = (im.width // TILE) * (im.height // TILE)
        made = 0

        for idx in range(cnt):
            if want is not None and (name, idx) not in want:
                continue

            t = tile_of(im, idx)

            if t is None:
                continue

            if is_blank(t):
                blank += 1
                continue

            t = t.resize((THUMB, THUMB), Image.LANCZOS)
            t.save(os.path.join(OUT, '%s_%d.png' % (name, idx)))
            made += 1

        print('  %-14s %s  %d장' % (fname, '%dx%d' % (im.width, im.height), made))
        total += made

    print('%s 에 %d장 (빈 칸 %d개는 건너뜀)' % (OUT, total, blank))


main()
