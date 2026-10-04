# -*- coding: utf-8 -*-
"""히어로별 장비를 실제 칸 크기로 세어, 도감 인벤토리 판 크기를 가늠한다.

    python tools/bag/inven_plan.py

[무엇을 세나]

도감처럼 "그 성급의 장비가 전부 들어가는 판"을 짜려면 두 가지가 필요하다.
    1. 그 성급에 장비가 몇 개인가
    2. 그 장비들이 각각 몇 칸을 먹는가
칸 수만 더해서는 판이 안 나온다 - 2x4 짜리 검은 세로 4 칸이 없는 판에는
눕히지 않으면 안 들어간다. 그래서 실제로 넣어 보고 판 크기를 낸다.

[히어로]

아이템 종류가 셋씩 묶여 (로빈, 디아나, 맥스) 차례다. 무기도 검 / 총 /
부메랑으로 같은 차례다(Func_Draw.cpp 의 COSTUME_WEAPON_*_IMG).

[칸 크기]

Func_Draw.cpp 의 GridGearPart 와 GridWeaponShape 를 그대로 옮겼다. 두
벌이 되면 갈라지므로, 고칠 일이 생기면 양쪽을 같이 고쳐야 한다.
"""
import io
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

#아이템 종류를 셋씩 묶은 것. 자리가 곧 히어로다.
HERO = ["로빈", "디아나", "맥스"]
SLOT = [
    ("무기", ["SWORD", "GUN", "BOOMERANG"]),
    ("투구", ["HELM", "HAT", "CAP"]),
    ("갑옷", ["ARMOR", "VEST", "COAT"]),
    ("장갑", ["GUNTLET", "ARMLET", "GLOVE"]),
    ("하의", ["KILT", "SKIRT", "PANTS"]),
    ("신발", ["GREAVES", "SHOES", "BOOTS"]),
]
#모두가 같이 쓰는 것
SHARED = ["NECK", "RING"]


def sword_tiles():
    """swordTileSize[] 를 (가로, 세로) 목록으로."""
    p = os.path.join(ROOT, "Classes", "Data", "SwordSprites.h")
    s = io.open(p, encoding="utf-8-sig", errors="replace").read()
    body = s.split("swordTileSize[35 * 2] = {", 1)[1].split("};", 1)[0]
    n = [int(t) for t in re.findall(r"[0-9]+", re.sub(r"//.*", "", body))]
    return [(n[i * 2], n[i * 2 + 1]) for i in range(len(n) // 2)]


def detail_cnt(enums, name):
    """그 종류에 번호가 몇 개인가. 다음 종류가 시작하는 자리까지."""
    order = ["SWORD", "GUN", "BOOMERANG", "HELM", "HAT", "CAP", "ARMOR",
             "VEST", "COAT", "GUNTLET", "ARMLET", "GLOVE", "KILT", "SKIRT",
             "PANTS", "GREAVES", "SHOES", "BOOTS", "NECK", "RING", "GEM"]
    i = order.index(name)
    return enums["ITEM_%s_START" % order[i + 1]] - enums["ITEM_%s_START" % name]


def footprint(name, detail, tiles):
    """GridGearPart / GridWeaponShape 와 같은 식."""
    if name == "SWORD":
        return tiles[detail] if detail < len(tiles) else (1, 2)
    if name == "BOOMERANG":
        w = 3 if detail < 9 else 4
        return (w, w)
    if name == "GUN":
        w = 1 if (detail < 5 and detail not in (1, 2, 4)) else 2
        h = 2 if detail < 5 else 3
        return (w, h)
    #방어구. 번호 5 부터 커진다
    big = detail >= 5
    if name in ("ARMOR", "VEST", "COAT"):
        return (2, 2) if big else (1, 1)
    if name in ("HELM", "HAT", "CAP", "GUNTLET", "ARMLET", "GLOVE",
                "KILT", "SKIRT", "PANTS", "GREAVES", "SHOES", "BOOTS"):
        return (1, 2) if big else (1, 1)
    return (1, 1)       #목걸이 / 반지


def pack(items, width):
    """왼쪽 아래부터 채워 넣어 몇 줄이 드는지 본다.

    가방에서 쓰는 것과 같은 규칙이다 - 아래 줄 왼쪽부터 처음 들어가는
    자리에 놓는다. 최적은 아니지만, 게임이 실제로 하는 방식이라 여기서
    나온 줄 수가 곧 필요한 판 높이다.
    """
    occ = {}
    rows = 0
    #큰 것부터 넣는다. 작은 것부터 넣으면 큰 것이 들어갈 구멍이 사라진다
    for w, h in sorted(items, key=lambda it: (-it[1], -it[0])):
        placed = False
        r = 0
        while not placed:
            for c in range(width - w + 1):
                if all((c + dx, r + dy) not in occ
                       for dx in range(w) for dy in range(h)):
                    for dx in range(w):
                        for dy in range(h):
                            occ[(c + dx, r + dy)] = True
                    rows = max(rows, r + h)
                    placed = True
                    break
            r += 1
            if r > 400:
                break
    return rows


#---- 성급 ----
#
#장비의 성급은 itemStar[] 에 (종류, 번호)마다 박혀 있다. 등급(GRADE_*)과는
#다른 축이다 - GetItemStar 는 grade 를 인자로 받고도 보지 않는다.
#
#    GetItemStar(type, detail, grade) = itemStar[itemStartCnt[type] + detail] / 100
#
#그 표는 content/ 의 tsv 에서 생성되므로 여기서도 생성된 배열을 읽는다.
def item_star_table():
    """itemStar_builtin[] 을 자리 그대로 읽어 성급(값/100)으로 돌려준다."""
    p = os.path.join(ROOT, "Classes", "Data", "ItemData.cpp")
    s = io.open(p, encoding="utf-8-sig", errors="replace").read()
    body = s.split("itemStar_builtin[] = {", 1)[1].split(chr(10) + "};", 1)[0]

    out = []
    for line in body.split(chr(10)):
        code = line.split("//")[0]
        for cell in code.split(","):
            cell = cell.strip()
            if cell:
                out.append(int(cell) // 100)
    return out


def main():
    import sys
    sys.path.insert(0, os.path.join(ROOT, "tools"))
    src = io.open(os.path.join(ROOT, "tools", "eval_text_enums.py"),
                  encoding="utf-8").read().split("# We also need")[0]
    g = {}
    exec(src, g)
    d = g["eval_enums"](os.path.join(ROOT, "Classes", "Def.h"))
    it = g["eval_enums"](os.path.join(ROOT, "Classes", "Def", "ItemDef.h"), d)

    tiles = sword_tiles()
    stars = item_star_table()
    print("itemStar 표 %d 칸" % len(stars))
    print()

    def star_of(name, detail):
        i = it["ITEM_%s_START" % name] + detail
        return stars[i] if 0 <= i < len(stars) else 0

    print("장비를 실제 칸 크기로 센다. 숫자는 (가로 x 세로) 칸.\n")

    for h, hero in enumerate(HERO):
        rows = []
        print("=" * 62)
        print("[%s]" % hero)
        total = 0
        for label, triple in SLOT:
            name = triple[h]
            cnt = detail_cnt(it, name)
            sizes = {}
            for dtl in range(cnt):
                f = footprint(name, dtl, tiles)
                sizes.setdefault(f, 0)
                sizes[f] += 1
                rows.append(f)
                total += f[0] * f[1]
            txt = "  ".join("%dx%d x%d" % (k[0], k[1], v)
                            for k, v in sorted(sizes.items()))
            st = {}
            for dtl in range(cnt):
                st.setdefault(star_of(name, dtl), 0)
                st[star_of(name, dtl)] += 1
            sttxt = " ".join("%d성x%d" % (k, v) for k, v in sorted(st.items()))
            print("   %-5s %-10s %2d 종   %-28s %s"
                  % (label, name, cnt, txt, sttxt))

        for name in SHARED:
            cnt = detail_cnt(it, name)
            for _ in range(cnt):
                rows.append((1, 1))
                total += 1
            st = {}
            for dtl in range(cnt):
                st.setdefault(star_of(name, dtl), 0)
                st[star_of(name, dtl)] += 1
            sttxt = " ".join("%d성x%d" % (k, v) for k, v in sorted(st.items()))
            print("   %-5s %-10s %2d 종   %-28s %s"
                  % ("공용", name, cnt, "1x1 x%d" % cnt, sttxt))

        print("   ----")
        print("   장비 %d 종, 칸 합계 %d" % (len(rows), total))
        print()

        #---- 성급별로 갈라 판을 짠다 ----
        byStar = {}
        for label, triple in SLOT:
            name = triple[h]
            cnt = detail_cnt(it, name)
            for dtl in range(cnt):
                byStar.setdefault(star_of(name, dtl), []).append(
                    footprint(name, dtl, tiles))
        for name in SHARED:
            cnt = detail_cnt(it, name)
            for dtl in range(cnt):
                byStar.setdefault(star_of(name, dtl), []).append((1, 1))

        print("   성급별 판  (itemStar 표 그대로)")
        print("      %-4s %-5s %-6s %s" % ("성", "종수", "칸", "폭 8 / 10 / 12 일 때 줄 수"))
        for st in sorted(byStar):
            items = byStar[st]
            cells = sum(w * hh for w, hh in items)
            fits = "  ".join("%2d줄" % pack(items, wg) for wg in (8, 10, 12))
            print("      ★%-3d %-5d %-6d %s" % (st, len(items), cells, fits))
        print()


main()
