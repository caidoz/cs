# -*- coding: utf-8 -*-
"""동료가 무슨 히어로 스킬을 부르는지 세어 본다.

    python tools/crew/skill_census.py

[왜 세나]

동료는 제 스킬 연출이 없다. 히어로 스킬을 발동시키는 자리다. 그러니
"쓸 수 있는 스킬이 몇 종이고, 64 명이 그걸 어떻게 나눠 들고 있나"가
곧 동료 기획의 바닥이다.

crewData 는 한 줄에 CREWDATASIZE 칸이고 SKILL1/2/3 이 그중 셋이다.
등급이 오르면 윗 스킬을 부르게 할 생각이므로, 세 칸이 다 차 있는지가
중요하다.
"""
import io
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


def enum_values(path, start_name):
    """start_name 부터 시작하는 enum 을 이름 -> 값으로 편다."""
    s = io.open(os.path.join(ROOT, path), encoding="utf-8-sig", errors="replace").read()
    s = re.sub(r"/\*.*?\*/", "", s, flags=re.S)
    out, val, started = {}, -1, False
    for line in s.split("\n"):
        line = re.sub(r"//.*", "", line).strip().rstrip(",")
        if not line:
            continue
        for part in line.split(","):
            part = part.strip()
            m = re.match(r"^([A-Z_][A-Z0-9_]*)\s*(?:=\s*(-?\d+))?$", part)
            if not m:
                continue
            name, num = m.group(1), m.group(2)
            if name == start_name:
                started = True
            if not started:
                continue
            val = int(num) if num is not None else val + 1
            out.setdefault(name, val)
    return out


def crew_rows():
    """crewData_builtin 을 한 명씩 끊어 낸다. 주석의 이름도 같이 챙긴다."""
    p = os.path.join(ROOT, "Classes", "Data", "HeroData.cpp")
    s = io.open(p, encoding="utf-8-sig", errors="replace").read()
    body = s.split("static const int crewData_builtin[] = {", 1)[1].split("\n};", 1)[0]

    rows, cur, note = [], [], []
    for line in body.split("\n"):
        tail = re.search(r"//(.*)$", line)
        if tail:
            note.append(tail.group(1).strip())
        for tok in re.findall(r"-?\d+|[A-Z_][A-Z0-9_]*", re.sub(r"//.*", "", line)):
            cur.append(tok)
        while len(cur) >= 7:                 #CREWDATASIZE
            rows.append((cur[:7], " / ".join(note)))
            cur = cur[7:]
            note = []
    return rows


def main():
    skills = enum_values("Classes/Def/SkillDef.h", "SKILL_NONE")
    byval = {}
    for k, v in skills.items():
        byval.setdefault(v, k)

    rows = crew_rows()
    print("동료 %d 명" % len(rows))
    print()

    used, blanks = {}, [0, 0, 0]
    for cols, note in rows:
        for i in range(3):
            raw = cols[2 + i]
            if raw in ("0", "SKILL_NONE"):
                blanks[i] += 1
                continue
            used[raw] = used.get(raw, 0) + 1

    print("SKILL 칸이 비어 있는 동료 수:  1칸 %d / 2칸 %d / 3칸 %d  (전체 %d)"
          % (blanks[0], blanks[1], blanks[2], len(rows)))
    print()
    print("쓰이는 스킬 %d 종" % len(used))
    for name, n in sorted(used.items(), key=lambda kv: -kv[1]):
        print("   %-34s %2d 명" % (name, n))


main()
