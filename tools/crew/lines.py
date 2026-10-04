# -*- coding: utf-8 -*-
"""동료를 계열로 나눈 표가 성립하는지 검사한다.

    python tools/crew/lines.py            검사만 한다
    python tools/crew/lines.py --emit     검사하고 Classes/CrewLines.inc 를 쓴다

[무엇을 검사하나]

승급은 "재료를 먹이면 같은 계열에서 별이 1 높은 동료 중 하나가 나온다"다.
그러니 계열마다 별이 연속으로 차 있어야 한다. 중간에 빈 별이 있으면 그
자리에서 사다리가 끊겨, 재료를 들고도 올릴 수가 없다.

표는 CREW_LINES 에 손으로 적는다. 64 명을 빠뜨리거나 두 번 적는 것이
가장 흔한 실수라 그것부터 센다.
"""
import io
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

#계열마다 전용 재료. 정수 번호(ITEM_ESSENCE 의 detail)다.
#
#아이콘이 겹치지 않는 것으로만 골랐다 - 보관함에 나란히 놓였을 때
#어느 계열 것인지 그림만으로 갈라져야 한다. 정수 20 과 42 는 아이콘이
#128 로 같아서 둘 다 안 쓴다.
LINE_ESSENCE = {
    "마을": (33, 121, "노란 초승달꼴"),
    "바다": (34, 122, "푸른 삼지창"),
    "엘프": (12, 108, "녹색 잎"),
    "기사": (39,  18, "금빛 문장"),
    "주술": (38, 126, "보라 물약"),
    "상인": ( 8,  21, "주황 호리병"),
}

#계열 이름 -> 그 계열의 동료들. 이름은 GameConfig.h 의 CREW_* 그대로다.
CREW_LINES = {
    "마을": ["BOY", "GIRL", "GRANDMA", "MAN", "WOMAN",
             "TRAVEL", "MILESE",
             "MAID", "BUNNYGIRL", "MONICA",
             "FATMAN", "LUISE", "BISTRO",
             "CHEF", "LORA"],
    "바다": ["UNCLE",
             "SEAUNCLE", "SEASOLDIER", "CREW",
             "SEABOY",
             "SEBASTIAN", "DONALD",
             "FISHING", "CAPTAIN"],
    "엘프": ["ELFBOY", "ELFGIRL", "ELFUNCLE", "ELFAUNT",
             "ELFGRANDFA", "ELFWOMAN", "ELFMAN", "ELFDANCER",
             "ELFMAGIC", "ELFDARK",
             "ELKEIN"],
    "기사": ["ADELKNIGHT",
             "NOBLEMAN", "DOBEL", "GAGEL",
             "KNIGHT", "AUSTIN", "DURAK",
             "ELEIN",
             "EVAN", "KING"],
    "주술": ["ALMA",
             "SCHOLAR", "OWL",
             "WITCH", "DARIAN", "NEZAR", "WOMANGHOST", "MANGHOST",
             "LABETH"],
    "상인": ["GRANDFA", "AUNT",
             "ITEM",
             "MAP", "NETITEM",
             "CRAFTMAN", "USERQUEST", "DOG",
             "FRAUD", "DELPIOS"],
}


def crew_stars():
    """GameConfig.h 의 CREW_* 줄에서 ★ 개수를 센다. 순서가 곧 번호다."""
    p = os.path.join(ROOT, "Classes", "Config", "GameConfig.h")
    s = io.open(p, encoding="utf-8-sig", errors="replace").read()
    out = []
    for line in s.split("\n"):
        m = re.match(r"\s*(CREW_[A-Z0-9_]+)\s*(?:=\s*\d+)?\s*,\s*//(.*)$", line)
        if m and m.group(1) != "TOTAL_CREW":
            out.append((m.group(1)[5:], m.group(2).count("★")))
    return out


def main():
    crew = crew_stars()
    star = dict(crew)
    order = [c for c, _ in crew]

    print("동료 %d 명, 계열 %d 개\n" % (len(crew), len(CREW_LINES)))

    #빠뜨렸거나 두 번 적었거나, 없는 이름을 적었는가
    seen = {}
    for line, members in CREW_LINES.items():
        for m in members:
            seen.setdefault(m, []).append(line)

    bad = False
    missing = [c for c in order if c not in seen]
    if missing:
        bad = True
        print("[표에 없는 동료 %d 명]" % len(missing))
        for m in missing:
            print("   %-14s ★%d" % (m, star[m]))
        print()
    dup = {m: ls for m, ls in seen.items() if len(ls) > 1}
    if dup:
        bad = True
        print("[두 계열에 적힌 동료]")
        for m, ls in dup.items():
            print("   %-14s %s" % (m, ", ".join(ls)))
        print()
    ghost = [m for m in seen if m not in star]
    if ghost:
        bad = True
        print("[GameConfig.h 에 없는 이름]  %s\n" % ", ".join(ghost))

    #별이 연속으로 차 있는가
    allstars = sorted(set(star.values()))
    print("계열 x 별  (칸의 수 = 그 별에 있는 동료 수)")
    print("%-8s %s" % ("", "  ".join("★%d" % s for s in allstars)))
    broken = []
    for line, members in CREW_LINES.items():
        by = {}
        for m in members:
            by.setdefault(star.get(m, 0), []).append(m)
        cells = ["%3d" % len(by[s]) if s in by else " . " for s in allstars]
        print("%-8s %s   합 %d" % (line, " ".join(cells), len(members)))
        if by:
            gaps = [s for s in range(min(by), max(by) + 1) if s not in by]
            if gaps:
                broken.append((line, gaps))

    print()
    if broken:
        bad = True
        print("[사다리가 끊기는 자리 - 그 별에 아무도 없어 올릴 수가 없다]")
        for line, gaps in broken:
            print("   %-8s ★ %s" % (line, ", ".join(str(g) for g in gaps)))
    else:
        print("사다리 이상 없음 - 계열마다 별이 연속으로 차 있다.")

    #계열마다 어디서 끝나는가. 끝에 선 동료는 재료를 먹일 데가 없다
    print()
    print("계열마다 시작과 끝")
    for line, members in CREW_LINES.items():
        ss = sorted({star[m] for m in members if m in star})
        if not ss:
            continue
        top = [m for m in members if star.get(m) == ss[-1]]
        print("   %-8s ★%d -> ★%d   맨 위: %s"
              % (line, ss[0], ss[-1], ", ".join(top)))

    print()
    print("검사 결과: %s" % ("고쳐야 한다" if bad else "통과"))
    if bad:
        return 1

    if "--emit" in sys.argv:
        emit(order, star)
    return 0


def emit(order, star):
    """표를 그대로 C 배열로 뱉는다.

    손으로 적은 표와 코드가 갈라지면 조용히 어긋난다 - 동료 하나가 계열
    없이 남아도 빌드는 통과하고, 그 동료만 승급이 안 된다. 그래서 코드
    쪽에는 사람이 손대지 않는다.
    """
    idx = {name: i for i, name in enumerate(order)}
    lines = list(CREW_LINES)
    of = {m: li for li, name in enumerate(lines) for m in CREW_LINES[name]}

    out = []
    w = out.append
    w("//이 파일은 tools/crew/lines.py --emit 가 만든다. 손으로 고치지 마라.")
    w("//계열을 바꾸려면 그 도구의 CREW_LINES 를 고치고 다시 돌려라.")
    w("")
    w("//동료를 테마로 묶은 것이 계열이다. 승급은 재료를 먹이면 같은")
    w("//계열에서 별이 1 높은 동료 중 하나가 나오는 식이라, 고정 사다리는")
    w("//없고 계열과 별 두 값만 있으면 된다.")
    w("enum {")
    for li, name in enumerate(lines):
        w("	CREWLINE_%d,	//%s" % (li, name))
    w("	CREWLINE_CNT,")
    w("};")
    w("")
    w("//계열마다 전용 재료. ITEM_ESSENCE 의 detail 번호다.")
    w("static const int kCrewLineEssence[CREWLINE_CNT] = {")
    for name in lines:
        n, icon, look = LINE_ESSENCE[name]
        w("	%2d,	//%s - 아이콘 %d, %s" % (n, name, icon, look))
    w("};")
    w("")
    w("//동료 번호 -> 계열. 별은 crewData 가 아니라 GameConfig.h 의 ★ 주석에")
    w("//적혀 있어 같이 낸다.")
    w("static const unsigned char kCrewLine[%d] = {" % len(order))
    for i, name in enumerate(order):
        w("	%-12s //%-2d %-14s ★%d"
          % ("CREWLINE_%d," % of[name], i, name, star[name]))
    w("};")
    w("")
    w("static const unsigned char kCrewStar[%d] = {" % len(order))
    for i in range(0, len(order), 8):
        chunk = order[i:i + 8]
        w("	" + " ".join("%d," % star[n] for n in chunk)
          + "	//%d~%d" % (i, i + len(chunk) - 1))
    w("};")
    w("")

    p = os.path.join(ROOT, "Classes", "CrewLines.inc")
    io.open(p, "w", encoding="utf-8-sig",
            newline=chr(13) + chr(10)).write(chr(10).join(out))
    print()
    print("썼다: %s  (계열 %d, 동료 %d)" % (p, len(lines), len(order)))


raise SystemExit(main())
