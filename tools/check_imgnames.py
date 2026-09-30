# -*- coding: utf-8 -*-
"""그림 번호(ImgDef.h)와 이름표(Text.h)가 같은 차례인지 검사한다.

    python tools/check_imgnames.py

[왜 필요한가]

GetResourceName 은 textId[TEXT_IMGNAME_START + 그림번호] 를 읽는다. 두 표가
한 칸이라도 어긋나면 엉뚱한 파일을 읽고, 그 뒤 번호는 전부 밀린다. 이름표가
모자라면 그림 이름 자리로 일반 문장이 새어 들어온다.

빌드로는 안 잡힌다 - 둘 다 그냥 배열이라 컴파일러가 개수를 안 본다.
"""
import io
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))

# 기존 도구의 enum 계산기를 그대로 쓴다. 두 벌로 두면 결과가 갈린다.
_src = io.open(os.path.join(ROOT, "tools", "eval_text_enums.py"),
               encoding="utf-8").read().split("# We also need")[0]
exec(_src)

STRING = re.compile(r'"((?:[^"\\]|\\.)*)"')
INCLUDE = re.compile(r'\s*#include\s+"([^"]+\.inc)"')


def expand(path):
    """Text.h 가 넣는 .inc 까지 펴서 한 줄씩 낸다."""
    out = []
    for line in io.open(path, encoding="utf-8-sig", errors="ignore"):
        m = INCLUDE.match(line)
        if m:
            out += expand(os.path.join(ROOT, "Classes", m.group(1)))
        else:
            out.append(line)
    return out


def image_names():
    names = []
    started = False
    for line in expand(os.path.join(ROOT, "Classes", "Text.h")):
        if not started:
            if "textId[" in line:
                started = True
            continue
        names += STRING.findall(re.sub(r"//.*", "", line))
    return names


def main():
    d = eval_enums(os.path.join(ROOT, "Classes", "Def.h"))
    img = eval_enums(os.path.join(ROOT, "Classes", "Def", "ImgDef.h"), d)
    all_enums = dict(img)
    all_enums.update(d)
    txt = eval_enums(os.path.join(ROOT, "Classes", "Def", "TextDef.h"), all_enums)
    names = image_names()
    total = img.get("TOTALIMG")
    #그림 이름이 표의 몇 줄째에서 시작하는가.
    #
    #TEXT_IMGNAME_START 를 그대로 쓰면 안 맞는다. 그 값은 textId 배열의
    #첫 줄부터 센 번호인데, 이 스크립트는 Text.h 를 위에서부터 훑으며
    #문자열을 주워서 앞쪽 다른 배열까지 같이 세기 때문이다.
    #
    #그래서 게임이 실제로 찍어 준 짝을 기준점으로 되짚는다. 로그에
    #  LoadImg failed: index=924, file=res/castle17.png
    #라고 나왔으니 castle17 이 있는 줄에서 924 를 빼면 시작 줄이다.
    base = names.index("castle17") - 924 if "castle17" in names else txt.get(
        "TEXT_IMGNAME_START")

    print("이름표 %d 줄, TOTALIMG %s, 그림 이름 시작 %s"
          % (len(names), total, base))
    print()

    #번호를 아는 표식들이 제자리에 있는지 본다.
    marks = [
        ("STAGEBG_FIRST_IMG", "bg1_far"),
        ("GRID_FRAME_FIRST_IMG", "grid0"),
    ]
    bad = 0
    for key, want in marks:
        at = img.get(key)
        if at is None:
            print("%-22s enum 에 없음" % key)
            bad += 1
            continue
        i = base + at
        got = names[i] if i < len(names) else "(표 끝을 넘음)"
        ok = got == want
        bad += 0 if ok else 1
        print("%-22s 그림 %4d 번 = 표 %4d 줄  기대 %-10s 실제 %-20s %s"
              % (key, at, i, want, got, "" if ok else "<-- 어긋남"))

    #어긋났으면 그 이름이 실제로 몇 번째에 있는지 보여 준다. 어느 쪽으로
    #얼마나 밀렸는지가 바로 보여야 고칠 자리를 찾는다.
    print()
    #게임이 실제로 찍은 짝을 기준점으로 삼는다. 로그에 이렇게 나왔다:
    #  LoadImg failed: index=924, file=res/castle17.png
    #이 짝이 맞으면 base 와 세는 법이 맞다는 뜻이다.
    for idx, nm in ((924, "castle17"), (926, "castle19")):
        i = base + idx
        got = names[i] if i < len(names) else "(넘침)"
        print("  기준점 그림 %d 번 = 표 %d 줄 -> %s (%s)"
              % (idx, i, got, "맞음" if got == nm else "틀림, " + nm + " 이어야"))
    print()

    for want in ("bg1_far", "bg7_boss_fx", "grid0", "grid9"):
        if want in names:
            i = names.index(want)
            print("  %-12s 표 %4d 줄 = 그림 %4d 번" % (want, i, i - base))
        else:
            print("  %-12s 이름표에 없음" % want)

    #이름표가 그림 수만큼 있는지. 모자라면 뒤 문장이 그림 이름으로 읽힌다.
    print()
    if total is not None:
        end = base + total
        if len(names) < end:
            print("이름표가 %d 줄 모자란다. 그림 이름 자리로 일반 문장이 샌다."
                  % (end - len(names)))
            bad += 1
        else:
            print("그림 다음 줄(%d): %s  <- 여기가 인벤토리여야 한다"
                  % (end, names[end]))

    print()
    print("어긋난 곳 %d" % bad)
    return 1 if bad else 0


sys.exit(main())
