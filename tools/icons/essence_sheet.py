# -*- coding: utf-8 -*-
"""정수 45종의 이름과 아이콘을 뽑아, 한 장으로 붙여 눈으로 고르게 한다.

    python tools/icons/essence_sheet.py

[왜 필요한가]

동료 승급 재료를 정수에서 고르려는데, ItemDef.h 의 정수 이름 주석이
인코딩 사고로 글자를 잃어 읽을 수가 없다(단단한 껍질 -> ?단??껍질).

그런데 같은 이름이 ItemData.cpp 의 아이콘 표 주석에는 멀쩡히 남아 있다.
이름은 거기서 읽고, 그림은 아이콘 번호로 떼어 온다.

[아이콘 좌표]

Func_Graphics.cpp 의 DrawIcon 이 쓰는 식 그대로다. 번호 64 개가 한 장이고
그 안은 8x8 이며 칸 간격이 33 이다.
    장   = ITEM_IMG + (번호 >> 6)
    칸   = 가로 번호 & 7, 세로 (번호 & 63) >> 3
    사각 = (1 + 가로*33, 1 + 세로*33, 32, 32)

[표를 읽는 법]

칸이 숫자가 아니라 식이다 - 64 * 3 + 24 + 0 처럼 적혀 있고 IconDef.h 의
이름이 섞인 칸도 있다. 그래서 칸마다 계산한다.

그리고 한 줄에 여러 칸이 오고 주석은 줄 끝에 하나 붙는다. 쉼표로 먼저
끊으면 그 주석이 다음 칸의 앞머리로 넘어가 칸이 밀린다. 줄 단위로 먼저
주석을 떼고, 떼어 둔 주석은 그 줄의 마지막 칸에 붙인다.
"""
import io
import os
import re
import sys

from PIL import Image, ImageDraw

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "tools"))

_src = io.open(os.path.join(ROOT, "tools", "eval_text_enums.py"),
               encoding="utf-8").read().split("# We also need")[0]
exec(_src)

QUOTED = re.compile(chr(34) + "([^" + chr(34) + "]*)" + chr(34))

CELL = 32
STEP = 33


def expand(path):
    """Text.h 가 끌어들이는 .inc 까지 한 줄씩 이어 낸다."""
    for line in io.open(path, encoding="utf-8-sig", errors="replace"):
        t = line.strip()
        if t.startswith("#include") and ".inc" in t and chr(34) in t:
            p = os.path.join(os.path.dirname(path), t.split(chr(34))[1])
            if os.path.exists(p):
                for sub in expand(p):
                    yield sub
                continue
        yield line


def image_names():
    names = []
    started = False
    for line in expand(os.path.join(ROOT, "Classes", "Text.h")):
        if not started:
            if "textId[" in line:
                started = True
            continue
        names += QUOTED.findall(line.split("//")[0])
    return names


def icon_table(env):
    """아이콘 표를 (번호, 이름) 목록으로 낸다. 자리가 곧 아이템 번호다."""
    s = io.open(os.path.join(ROOT, "Classes", "Data", "ItemData.cpp"),
                encoding="utf-8-sig", errors="replace").read()
    body = s.split("itemIconTable_builtin[]", 1)[1]
    body = body.split("{", 1)[1].split(chr(10) + "};", 1)[0]

    out = []
    for line in body.split(chr(10)):
        code, _, note = line.partition("//")
        note = note.strip()
        first = len(out)
        for cell in code.split(","):
            cell = cell.strip()
            if not cell:
                continue
            try:
                out.append([eval(cell, {}, env), ""])
            except Exception:
                #못 읽은 칸도 자리는 지켜야 뒤가 안 밀린다
                out.append([-1, ""])
        #줄 끝 주석은 그 줄의 마지막 칸 것이다
        if note and len(out) > first:
            out[-1][1] = note
    return out


def main():
    d = eval_enums(os.path.join(ROOT, "Classes", "Def.h"))
    env = dict(d)
    env.update(eval_enums(os.path.join(ROOT, "Classes", "Def", "IconDef.h"), d))
    it = eval_enums(os.path.join(ROOT, "Classes", "Def", "ItemDef.h"), d)
    env.update(it)
    img = eval_enums(os.path.join(ROOT, "Classes", "Def", "ImgDef.h"), d)

    table = icon_table(env)
    base = it["ITEM_ESSENCE_START"]
    total = it["TOTAL_ESSENCE"]
    print("아이콘 표 %d 칸, 정수는 %d 번부터 %d 종" % (len(table), base, total))
    if base + total > len(table):
        print("표가 모자란다 - 정수 자리까지 못 미친다. 읽는 식을 다시 봐야 한다.")
        return

    names = image_names()
    nameBase = names.index("castle17") - 924
    first = img["ITEM_IMG"]

    print()
    pairs = [(n, table[base + n][0], table[base + n][1]) for n in range(total)]
    for n, icon, note in pairs:
        print("   정수 %-3d 아이콘 %-6d %s" % (n, icon, note))

    #---- 한 장으로 붙이기 ----
    cols, pad = 9, 6
    tile = CELL + pad * 2 + 10
    rows = (total + cols - 1) // cols
    sheet = Image.new("RGBA", (cols * tile, rows * tile), (24, 24, 28, 255))
    dr = ImageDraw.Draw(sheet)

    pages = {}
    for n, icon, note in pairs:
        if icon < 0:
            continue
        page = first + (icon >> 6)
        if page not in pages:
            fn = os.path.join(ROOT, "Resources", "res",
                              names[nameBase + page] + ".png")
            pages[page] = Image.open(fn).convert("RGBA") if os.path.exists(fn) else None

        src = pages[page]
        ox = (n % cols) * tile + pad
        oy = (n // cols) * tile + pad
        if src is not None:
            sx = 1 + (icon & 0x07) * STEP
            sy = 1 + ((icon & 0x3F) >> 3) * STEP
            if sx + CELL <= src.width and sy + CELL <= src.height:
                cut = src.crop((sx, sy, sx + CELL, sy + CELL))
                sheet.paste(cut, (ox, oy), cut)
        dr.text((ox, oy + CELL + 1), str(n), fill=(190, 190, 200, 255))

    print()
    for page in sorted(pages):
        print("   장 %-4d %-24s %s"
              % (page, names[nameBase + page], "없음" if pages[page] is None else "열림"))

    out = os.path.join(ROOT, "tools", "icons", "essence_sheet.png")
    sheet.resize((sheet.width * 2, sheet.height * 2), Image.NEAREST).save(out)
    print()
    print("%s  (칸 아래 숫자가 정수 번호)" % out)


main()
