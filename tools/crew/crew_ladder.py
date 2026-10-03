# -*- coding: utf-8 -*-
"""동료를 계열 x 별로 갈라 합성 사다리를 짤 수 있는지 본다.

    python tools/crew/crew_ladder.py

[무엇을 보나]

합성으로 "다른 동료가 된다"를 하려면 사다리가 필요하다. 같은 계열의
별 N 짜리 셋을 합쳐 별 N+1 짜리 하나가 나오려면, 계열마다 별마다
사람이 있어야 한다. 빈 칸이 있으면 그 자리에서 사다리가 끊긴다.

계열은 그 동료의 첫 스킬이 무엇이냐로 본다 - 화면에 실제로 나오는 것이
그것이기 때문이다. 별은 GameConfig.h 의 주석(★)에서 읽는다.
"""
import io
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

LINE = {"CREWBULLET": "원거리", "SUMMON": "소환", "HEROSKILL": "히어로호출",
        "CREWSUMMON": "난입", "SUMMONHERO": "히어로소환",
        "ACTIVE": "액티브", "PASSIVE": "패시브"}


def skill_kind():
    p = os.path.join(ROOT, "Classes", "Data", "SkillData.cpp")
    s = io.open(p, encoding="utf-8-sig", errors="replace").read()
    body = s.split("skillData_builtin[] = {", 1)[1].split("\n};", 1)[0]
    out = {}
    for line in body.split("\n"):
        m = re.search(r"//\s*(\d+)", line)
        if not m:
            continue
        cols = [t.strip() for t in re.sub(r"//.*", "", line).split(",") if t.strip()]
        if cols:
            out[int(m.group(1))] = cols[0]
    return out


def enum_map(path, first):
    s = io.open(os.path.join(ROOT, path), encoding="utf-8-sig", errors="replace").read()
    s = re.sub(r"/\*.*?\*/", "", s, flags=re.S)
    out, val, on = {}, -1, False
    for line in s.split("\n"):
        for part in re.sub(r"//.*", "", line).split(","):
            m = re.match(r"^\s*([A-Z_][A-Z0-9_]*)\s*(?:=\s*(-?\d+))?\s*$", part)
            if not m:
                continue
            name, num = m.group(1), m.group(2)
            if name == first:
                on = True
            if not on:
                continue
            val = int(num) if num is not None else val + 1
            out.setdefault(name, val)
    return out


def crew_stars():
    """GameConfig.h 의 CREW_* 줄에서 ★ 개수를 센다."""
    p = os.path.join(ROOT, "Classes", "Config", "GameConfig.h")
    s = io.open(p, encoding="utf-8-sig", errors="replace").read()
    out = []
    for line in s.split("\n"):
        m = re.match(r"\s*(CREW_[A-Z0-9_]+)\s*(?:=\s*\d+)?\s*,\s*//(.*)$", line)
        if not m:
            continue
        if m.group(1) == "TOTAL_CREW":
            continue
        out.append((m.group(1), m.group(2).count("★")))
    return out


def crew_rows():
    p = os.path.join(ROOT, "Classes", "Data", "HeroData.cpp")
    s = io.open(p, encoding="utf-8-sig", errors="replace").read()
    body = s.split("static const int crewData_builtin[] = {", 1)[1].split("\n};", 1)[0]
    toks = re.findall(r"-?\d+|[A-Za-z_][A-Za-z0-9_]*", re.sub(r"//.*", "", body))
    return [toks[i:i + 7] for i in range(0, len(toks) - 6, 7)]


def main():
    kinds = skill_kind()
    names = enum_map("Classes/Def/SkillDef.h", "SKILL_COMMON_ROBIN1")
    rows = crew_rows()
    stars = crew_stars()

    print("동료 %d 명, 별 주석 %d 줄\n" % (len(rows), len(stars)))

    grid = {}
    for i, r in enumerate(rows):
        v = names.get(r[2])
        line = LINE.get(kinds.get(v, "?"), "?")
        star = stars[i][1] if i < len(stars) else 0
        grid.setdefault(line, {}).setdefault(star, []).append(
            stars[i][0] if i < len(stars) else "?")

    allstars = sorted({s for d in grid.values() for s in d})
    print("계열 x 별  (칸의 수 = 그 자리에 있는 동료 수)")
    print("%-12s %s" % ("", "  ".join("★%d" % s for s in allstars)))
    for line in sorted(grid, key=lambda k: -sum(len(v) for v in grid[k].values())):
        cells = []
        for s in allstars:
            n = len(grid[line].get(s, []))
            cells.append(" . " if n == 0 else "%3d" % n)
        print("%-12s %s   합 %d"
              % (line, " ".join(cells), sum(len(v) for v in grid[line].values())))

    print()
    print("사다리가 끊기는 자리 (그 계열에 그 별이 없다)")
    for line in grid:
        gaps = [s for s in allstars if s and not grid[line].get(s)]
        if gaps:
            print("   %-12s ★ %s" % (line, ", ".join(str(g) for g in gaps)))


main()
