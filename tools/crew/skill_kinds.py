# -*- coding: utf-8 -*-
"""동료 스킬 192 개가 실제로 어떤 종류인지 센다.

    python tools/crew/skill_kinds.py

[무엇을 보나]

skillData 의 첫 칸(SKILLDATA_KIND)이 그 스킬이 무엇인지를 말한다.
  CREWBULLET   총탄을 쏜다
  SUMMON       몬스터를 부른다
  HEROSKILL    히어로 스킬을 호출한다   <- 연출이 히어로 것
  SUMMONHERO   다른 히어로를 불러낸다
  CREWSUMMON   동료가 난입해 직접 친다

"동료는 제 연출이 없고 히어로 스킬만 부른다"가 맞으려면 HEROSKILL 이
대부분이어야 한다. 아니면 동료마다 제 연출이 따로 있다는 뜻이다.

[줄 단위로 읽는다]

skillData 는 한 줄이 한 스킬이고 줄 끝 주석에 번호가 적혀 있다. 토큰을
폭으로 끊으면 줄마다 토큰 수가 달라 어긋난다 - 주석의 번호를 믿는다.
"""
import io
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

KIND = {"PASSIVE": "패시브", "ACTIVE": "액티브", "CREWBULLET": "총탄",
        "SUMMON": "몬스터 소환", "HEROSKILL": "히어로 스킬 호출",
        "SUMMONHERO": "히어로 소환", "CREWSUMMON": "동료 난입"}


def skill_rows():
    """번호 -> (첫 칸, 칸 목록, 주석에 적힌 이름)."""
    p = os.path.join(ROOT, "Classes", "Data", "SkillData.cpp")
    s = io.open(p, encoding="utf-8-sig", errors="replace").read()
    body = s.split("skillData_builtin[] = {", 1)[1].split("\n};", 1)[0]

    out = {}
    for line in body.split("\n"):
        m = re.search(r"//\s*(\d+)\s*(.*)$", line)
        if not m:
            continue
        cols = [t.strip() for t in re.sub(r"//.*", "", line).split(",") if t.strip()]
        if not cols:
            continue
        out[int(m.group(1))] = (cols[0], cols, m.group(2).strip())
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


def crew_rows():
    p = os.path.join(ROOT, "Classes", "Data", "HeroData.cpp")
    s = io.open(p, encoding="utf-8-sig", errors="replace").read()
    body = s.split("static const int crewData_builtin[] = {", 1)[1].split("\n};", 1)[0]
    toks = re.findall(r"-?\d+|[A-Za-z_][A-Za-z0-9_]*", re.sub(r"//.*", "", body))
    return [toks[i:i + 7] for i in range(0, len(toks) - 6, 7)]


def main():
    rows = skill_rows()
    names = enum_map("Classes/Def/SkillDef.h", "SKILL_COMMON_ROBIN1")
    crew = crew_rows()

    print("skillData %d 줄, 동료 %d 명\n" % (len(rows), len(crew)))

    tally, hero, missing = {}, {}, []
    for c in crew:
        for i in range(3):
            sym = c[2 + i]
            v = names.get(sym)
            if v is None or v not in rows:
                missing.append(sym)
                continue
            kind, cols, _ = rows[v]
            tally[kind] = tally.get(kind, 0) + 1
            if kind == "HEROSKILL" and len(cols) > 11:
                hero[cols[11]] = hero.get(cols[11], 0) + 1

    print("동료 스킬 %d 개의 종류" % (len(crew) * 3))
    for k, n in sorted(tally.items(), key=lambda kv: -kv[1]):
        print("   %-14s %-16s %3d" % (k, KIND.get(k, ""), n))
    if missing:
        print("   %-31s %3d  (표에 그 번호가 없음)" % ("표 밖", len(missing)))
        print("      예: %s" % ", ".join(missing[:5]))

    if hero:
        print("\n히어로 스킬 호출이 가리키는 실제 스킬 %d 종" % len(hero))
        for h, n in sorted(hero.items(), key=lambda kv: -kv[1]):
            print("   %-30s %3d 번" % (h, n))


main()
