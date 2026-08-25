# -*- coding: utf-8 -*-
"""뽑기 확률표를 소스에서 뽑아 만든다.

    python tools/content/gacha_rates.py

만드는 것
    server/web/rates.html      홈페이지에 올릴 표
    Resources/data/rates.tsv   게임 안에서 보여줄 표

왜 손으로 안 쓰는가
--------------------------------------------------------------------------
확률 표시는 법이 요구하는 것이고, 밸런스를 한 번 고치면 표도 같이 고쳐야
한다. 손으로 적어두면 반드시 어긋난다. 고친 사람은 표가 있다는 것을
잊고, 표는 조용히 거짓말이 된다.

그래서 표를 사람이 쓰지 않는다. 확률이 적힌 그 배열에서 바로 뽑는다.
빌드에 걸어두면 데이터가 바뀔 때마다 표가 저절로 따라온다.

읽는 곳
    Classes/Func_Gacha.h    rewardBoxData - 상자별 확률
    Classes/Func_Gacha.cpp  RollBoxGrade - 천장 규칙
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
GACHA_H = os.path.join(ROOT, 'Classes', 'Func_Gacha.h')
GACHA_CPP = os.path.join(ROOT, 'Classes', 'Func_Gacha.cpp')

#등급은 여섯이고 별 개수는 등급 + 1 이다 (MakeBoxCrewReward 참고).
GRADE_COUNT = 6

#rewardBoxData 한 칸에 든 값의 차례. 구조체 선언과 같아야 한다.
FIELDS = [
    'minCard', 'maxCard',
    'heartMin', 'heartMax',
    'goldMin', 'goldMax', 'goldRate',
    'crewRate', 'equipRate',
]


def strip_comments(text):
    text = re.sub(r'/\*.*?\*/', '', text, flags=re.S)
    text = re.sub(r'//[^\n]*', '', text)

    return text


def read_boxes():
    """rewardBoxData 를 읽어 상자 목록으로 돌려준다."""
    src = strip_comments(open(GACHA_H, encoding='utf-8', errors='replace').read())
    at = src.find('rewardBoxData')

    if at < 0:
        sys.exit('rewardBoxData 를 못 찾았다')

    at = src.index('{', at)
    depth = 0
    end = at

    for i in range(at, len(src)):
        if src[i] == '{':
            depth += 1
        elif src[i] == '}':
            depth -= 1

            if depth == 0:
                end = i
                break

    body = src[at + 1:end]

    #깊이 1 의 { } 하나가 상자 하나다.
    boxes = []
    depth = 0
    start = None

    for i, ch in enumerate(body):
        if ch == '{':
            if depth == 0:
                start = i + 1
            depth += 1
        elif ch == '}':
            depth -= 1

            if depth == 0:
                boxes.append(body[start:i])

    out = []

    for n, chunk in enumerate(boxes):
        nums = [int(x) for x in re.findall(r'-?\d+', chunk)]
        need = len(FIELDS) + GRADE_COUNT * 2 + 1

        if len(nums) < need:
            sys.exit('BOX_REWARD%d: 값이 %d개뿐이다 (%d개 필요)'
                     % (n, len(nums), need))

        box = {'name': 'BOX_REWARD%d' % n}
        at = 0

        for f in FIELDS:
            box[f] = nums[at]
            at += 1

        box['crewGradeRate'] = nums[at:at + GRADE_COUNT]
        at += GRADE_COUNT
        box['equipGradeRate'] = nums[at:at + GRADE_COUNT]
        at += GRADE_COUNT
        box['luckyRate'] = nums[at]

        out.append(box)

    return out


def read_pity():
    """RollBoxGrade 의 천장 규칙을 읽는다.

    코드가 바뀌었는데 표만 옛 규칙을 적고 있으면 안 되므로, 숫자를 여기에
    옮겨 적지 않고 소스에서 확인한다.
    """
    src = strip_comments(open(GACHA_CPP, encoding='utf-8', errors='replace').read())
    at = src.find('int RollBoxGrade')

    if at < 0:
        sys.exit('RollBoxGrade 를 못 찾았다')

    body = src[at:at + 2000]

    m = re.search(r'highGradeMissCount\s*>=\s*(\d+)', body)
    n = re.search(r'highGradeMissCount\s*-\s*(\d+)', body)
    g = re.search(r'weight\[(\d+)\]\s*\+=', body)

    if not (m and n and g):
        sys.exit('천장 규칙을 못 읽었다. RollBoxGrade 가 바뀌었나')

    return {'after': int(m.group(1)), 'minus': int(n.group(1)),
            'grade': int(g.group(1))}


def pct(part, total):
    if total <= 0:
        return 0.0

    return part * 100.0 / total


def grade_table(rate):
    """등급별 확률(천장 없음)."""
    total = sum(rate)

    return [pct(w, total) for w in rate]


def pity_curve(rate, pity, upto):
    """연속 미획득 횟수별로, 그 판의 상위 등급 확률이 어떻게 오르는지."""
    out = []

    for miss in range(0, upto + 1):
        w = list(rate)

        if miss >= pity['after']:
            w[pity['grade']] += miss - pity['minus']

        out.append((miss, pct(w[pity['grade']], sum(w))))

    return out


def fmt(v):
    """확률을 적는 방식. 0 이 아닌데 0.00 으로 보이면 안 된다."""
    if v == 0:
        return '0%'

    if v < 0.01:
        return '0.01%% 미만'

    return '%.2f%%' % v
