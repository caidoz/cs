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


#=========================================================================
# 팩에서 읽기
#
# 별 등급표(itemStar)와 동료 수는 소스가 아니라 content.pack 에 있다.
# 팩이 게임이 실제로 쓰는 값이므로 표도 거기서 뽑는다. 밸런스를 고쳐
# 팩을 다시 만들면 표가 저절로 따라온다.
#=========================================================================
PACK = os.path.join(ROOT, 'Resources', 'data', 'content.pack')
ITEMDEF_H = os.path.join(ROOT, 'Classes', 'Def', 'ItemDef.h')

DPK_MAGIC = 0x314B5049
DPK_NAMELEN = 32
DPK_ENTRYSIZE = 48


def read_pack():
    """content.pack 을 이름 -> 값 목록으로 편다."""
    import struct
    import zlib

    with open(PACK, 'rb') as fp:
        buf = fp.read()

    magic, _abi, count, _body = struct.unpack_from('<IIiI', buf, 0)

    if magic != DPK_MAGIC:
        sys.exit('%s 가 팩이 아니다' % PACK)

    if zlib.crc32(buf[:-4]) & 0xffffffff != struct.unpack_from(
            '<I', buf, len(buf) - 4)[0]:
        sys.exit('팩의 CRC 가 안 맞는다. 다시 만들어야 한다')

    dat = 16 + count * DPK_ENTRYSIZE
    out = {}

    for i in range(count):
        e = 16 + i * DPK_ENTRYSIZE
        name = buf[e:e + DPK_NAMELEN].split(b'\0')[0].decode('ascii')
        sz = buf[e + DPK_NAMELEN]
        kind = buf[e + DPK_NAMELEN + 1]
        cells, off = struct.unpack_from('<II', buf, e + DPK_NAMELEN + 4)

        #쓰는 것만 편다. 팩 전체를 int 로 펴면 느리고 쓸 데도 없다.
        out[name] = (sz, kind, cells, dat + off, buf)

    return out


def cells_of(pack, name):
    """팩의 배열 하나를 정수 목록으로."""
    import struct

    if name not in pack:
        sys.exit('팩에 %s 가 없다' % name)

    sz, kind, cells, at, buf = pack[name]
    code = {1: 'b', 2: 'h', 4: 'i', 8: 'q'}[sz]

    if kind == 1:       #DPK_UINT
        code = code.upper()
    elif kind == 2:     #DPK_FLOAT
        code = {4: 'f', 8: 'd'}[sz]

    return list(struct.unpack_from('<%d%s' % (cells, code), buf, at))


def count_of(pack, name):
    return pack[name][2] if name in pack else 0


def read_item_types():
    """ItemDef.h 의 아이템 종류 이름 -> 번호.

    번호를 여기 옮겨 적으면 종류가 하나 끼어들 때 표가 조용히 어긋난다.
    """
    src = strip_comments(open(ITEMDEF_H, encoding='utf-8',
                              errors='replace').read())
    at = src.find('ITEM_SWORD = 0')

    if at < 0:
        sys.exit('ItemDef.h 에서 ITEM_SWORD 를 못 찾았다')

    end = src.find('TOTALITEMTYPE', at)
    out = {}
    n = 0

    for line in src[at:end].split(','):
        m = re.search(r'(ITEM_[A-Z0-9_]+)', line)

        if m:
            out[m.group(1)] = n
            n += 1

    out['TOTALITEMTYPE'] = n

    return out


#=========================================================================
# 계산
#=========================================================================
#상자에서 나오는 장비 부위. MakeBoxEquipType() 과 같아야 한다.
EQUIP_TYPES = ['ITEM_SWORD', 'ITEM_HELM', 'ITEM_ARMOR',
               'ITEM_GUNTLET', 'ITEM_KILT', 'ITEM_GREAVES']

EQUIP_NAME = {'ITEM_SWORD': '무기', 'ITEM_HELM': '투구', 'ITEM_ARMOR': '갑옷',
              'ITEM_GUNTLET': '장갑', 'ITEM_KILT': '허리', 'ITEM_GREAVES': '신발'}


def read_equip_types():
    """MakeBoxEquipType() 이 뽑는 부위 목록을 소스에서 확인한다.

    표에 적힌 부위와 코드가 뽑는 부위가 다르면 표가 거짓말이 된다.
    한쪽을 고치고 다른 쪽을 잊는 일이 실제로 있었다.
    """
    src = strip_comments(open(GACHA_CPP, encoding='utf-8',
                              errors='replace').read())
    at = src.find('int MakeBoxEquipType')

    if at < 0:
        sys.exit('MakeBoxEquipType 을 못 찾았다')

    body = src[at:src.index('}', src.index('{', src.index('{', at) + 1))]
    got = re.findall(r'ITEM_[A-Z0-9_]+', body)

    if got != EQUIP_TYPES:
        sys.exit('MakeBoxEquipType 이 바뀌었다. EQUIP_TYPES 를 맞춰라\n'
                 '  코드: %s\n  표  : %s' % (', '.join(got), ', '.join(EQUIP_TYPES)))

    return got


def star_counts(pack, types):
    """종류별로 '별 몇 개짜리가 몇 종인지'.

    상자는 별 개수로 후보를 좁힌 뒤 그 안에서 고르게 하나를 뽑는다
    (GetRandomBoxDetailByStar). 그래서 개별 아이템 확률은
    등급 확률 / 그 별의 종류 수 다.
    """
    star = cells_of(pack, 'itemStar')
    start = cells_of(pack, 'itemStartCnt')
    crew = count_of(pack, 'crewData') // 6
    out = {}

    for name, num in types.items():
        if name == 'ITEM_CREW':
            n = crew
        elif name in EQUIP_NAME:
            n = start[num + 1] - start[num]
        else:
            continue

        cnt = [0] * (GRADE_COUNT + 1)

        for d in range(n):
            s = star[start[num] + d] // 100

            if 1 <= s <= GRADE_COUNT:
                cnt[s] += 1

        out[name] = {'total': n, 'byStar': cnt}

    return out


def box_rows(box, pity, stars):
    """상자 하나의 확률을 표로 만든다. (구분, 항목, 확률) 목록."""
    crew = grade_table(box['crewGradeRate'])
    equip = grade_table(box['equipGradeRate'])
    typeTotal = box['crewRate'] + box['equipRate']
    pCrew = pct(box['crewRate'], typeTotal)
    pEquip = pct(box['equipRate'], typeTotal)
    rows = []

    rows.append(('구성', '하트', '항상 1장 (%d~%d개)'
                 % (box['heartMin'], box['heartMax'])))
    rows.append(('구성', '골드', '%d%% 확률로 1장 (%s~%s골드)'
                 % (box['goldRate'], '{:,}'.format(box['goldMin']),
                    '{:,}'.format(box['goldMax']))))
    rows.append(('구성', '카드 장수', '%d~%d장 (럭키 시 1장 추가)'
                 % (box['minCard'], box['maxCard'])))
    rows.append(('구성', '럭키 상자', '%d%%' % box['luckyRate']))

    rows.append(('종류', '동료', fmt(pCrew)))
    rows.append(('종류', '장비', fmt(pEquip)))

    for g in range(GRADE_COUNT):
        n = stars['ITEM_CREW']['byStar'][g + 1]
        rows.append(('동료 등급', '%d성' % (g + 1),
                     '%s (동료 카드 1장 기준, %d종 균등)' % (fmt(crew[g]), n)))

    for g in range(GRADE_COUNT):
        rows.append(('장비 등급', '%d성' % (g + 1),
                     '%s (장비 카드 1장 기준)' % fmt(equip[g])))

    for t in EQUIP_TYPES:
        rows.append(('장비 부위', EQUIP_NAME[t],
                     '%s (%d종)' % (fmt(100.0 / len(EQUIP_TYPES)),
                                    stars[t]['total'])))

    return rows


def item_rows(box, stars, which):
    """카드 한 장이 특정 아이템 하나가 될 확률."""
    typeTotal = box['crewRate'] + box['equipRate']
    rows = []

    if which == 'crew':
        table = grade_table(box['crewGradeRate'])
        share = pct(box['crewRate'], typeTotal)

        for g in range(GRADE_COUNT):
            n = stars['ITEM_CREW']['byStar'][g + 1]
            rows.append(('%d성 동료' % (g + 1), n,
                         share * table[g] / 100.0 / n if n else 0.0))

        return rows

    table = grade_table(box['equipGradeRate'])
    share = pct(box['equipRate'], typeTotal) / len(EQUIP_TYPES)

    for t in EQUIP_TYPES:
        for g in range(GRADE_COUNT):
            n = stars[t]['byStar'][g + 1]
            rows.append(('%d성 %s' % (g + 1, EQUIP_NAME[t]), n,
                         share * table[g] / 100.0 / n if n else 0.0))

    return rows


#=========================================================================
# 내보내기
#=========================================================================
OUT_HTML = os.path.join(ROOT, 'server', 'web', 'rates.html')
OUT_TSV = os.path.join(ROOT, 'Resources', 'data', 'rates.tsv')

#천장 곡선을 어디까지 보여줄지. 끝이 보여야 뜻이 있다.
PITY_SHOW = 60


def esc(s):
    return (s.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;'))


def box_title(n):
    return '보상 상자 %d' % (n + 1)


def write_html(boxes, pity, stars, stamp):
    w = []
    a = w.append

    a('<!--\n  이 파일은 tools/content/gacha_rates.py 가 만든다.\n'
      '  직접 고치지 마라. 다음 실행 때 지워진다.\n'
      '  확률을 바꾸려면 Classes/Func_Gacha.h 를 고치고 다시 돌려라.\n-->')
    a('<!doctype html>')
    a('<html lang="ko">')
    a('<head>')
    a('<meta charset="utf-8">')
    a('<meta name="viewport" content="width=device-width, initial-scale=1">')
    a('<title>인삼남 확률 정보</title>')
    a('<style>')
    a(STYLE)
    a('</style>')
    a('</head>')
    a('<body>')
    a('<div class="wrap">')

    a('<h1>인삼남 확률 정보</h1>')
    a('<div class="meta">주식회사 빅픽셀<br>기준일 %s</div>' % stamp)

    a('<div class="note">')
    a('<p>이 표는 게임에 들어 있는 확률 데이터에서 직접 뽑아 만든 것입니다. '
      '사람이 옮겨 적지 않으므로 게임이 실제로 쓰는 값과 다를 수 없습니다.</p>')
    a('<p>모든 확률은 해당 항목을 한 번 뽑을 때의 값입니다. 소수점 셋째 자리에서 '
      '반올림했으므로 합이 100%가 되지 않을 수 있습니다.</p>')
    a('</div>')

    #---- 뽑기 방식 ----
    a('<h2>상자를 여는 방법</h2>')
    a('<ol class="num">')
    a('<li>상자를 열면 카드가 여러 장 나옵니다. 장수는 상자마다 다릅니다.</li>')
    a('<li>첫 장은 <b>항상 하트</b>입니다.</li>')
    a('<li>정해진 확률로 <b>골드</b>가 한 장 더 나옵니다.</li>')
    a('<li>나머지 장은 <b>동료</b> 또는 <b>장비</b>입니다. 둘 중 무엇이 될지는 '
      '장마다 따로 정해집니다.</li>')
    a('<li>동료·장비는 먼저 <b>등급(성)</b>을 정하고, 그 등급에 해당하는 종류 '
      '가운데 하나를 <b>고르게</b> 뽑습니다.</li>')
    a('<li>장비는 등급을 정하기 전에 여섯 부위 중 하나를 고르게 뽑습니다.</li>')
    a('</ol>')

    #---- 럭키 ----
    a('<h2>럭키 상자</h2>')
    a('<p>상자를 열 때 정해진 확률로 <b>럭키 상자</b>가 됩니다. 럭키 상자는 '
      '카드가 한 장 늘고, 나온 동료·장비 카드 가운데 하나가 <b>한 등급 올라갑니다</b>. '
      '이미 6성인 카드는 대상에서 빠집니다. 아래 등급 확률은 이 승급을 적용하기 '
      '<i>전</i>의 값입니다.</p>')

    #---- 천장 ----
    a('<h2>%d회 연속 미획득 보정 (천장)</h2>' % pity['after'])
    a('<p>5성 이상을 <b>%d회 연속으로 못 얻으면</b>, 그다음 뽑기부터 5성이 나올 '
      '가중치가 1씩 늘어납니다. 5성 이상을 얻으면 횟수가 0으로 돌아갑니다. '
      '동료와 장비는 횟수를 <b>따로</b> 셉니다.</p>' % pity['after'])
    a('<p>일부 상자는 5성의 기본 확률이 0%입니다. 그 상자에서 5성은 이 보정을 '
      '통해서만 나옵니다.</p>')

    a('<div class="scroll"><table>')
    a('<tr><th>연속 미획득</th>%s</tr>'
      % ''.join('<th>%s</th>' % box_title(n) for n in range(len(boxes))))

    curves = [dict(pity_curve(b['crewGradeRate'], pity, PITY_SHOW))
              for b in boxes]

    for miss in [0, pity['after'] - 1, pity['after'], pity['after'] + 5,
                 pity['after'] + 10, pity['after'] + 20, PITY_SHOW]:
        a('<tr><td>%d회</td>%s</tr>'
          % (miss, ''.join('<td>%s</td>' % fmt(c[miss]) for c in curves)))

    a('</table></div>')
    a('<p class="dim">동료 카드 1장이 5성이 될 확률입니다. 장비도 같은 방식으로 '
      '오릅니다.</p>')

    #---- 상자별 ----
    for n, box in enumerate(boxes):
        a('<h2>%s</h2>' % box_title(n))
        a('<div class="scroll"><table>')
        a('<tr><th>구분</th><th>항목</th><th>확률</th></tr>')

        last = None

        for kind, label, value in box_rows(box, pity, stars):
            head = '' if kind == last else esc(kind)
            last = kind
            a('<tr><td class="k">%s</td><td>%s</td><td>%s</td></tr>'
              % (head, esc(label), esc(value)))

        a('</table></div>')

        a('<details><summary>개별 아이템 확률 (카드 1장 기준)</summary>')
        a('<div class="scroll"><table>')
        a('<tr><th>아이템</th><th>종류 수</th><th>1종당 확률</th></tr>')

        for label, cnt, p in (item_rows(box, stars, 'crew')
                              + item_rows(box, stars, 'equip')):
            a('<tr><td>%s</td><td>%d종</td><td>%s</td></tr>'
              % (esc(label), cnt, fmt(p)))

        a('</table></div></details>')

    a('<footer>주식회사 빅픽셀 &middot; 확률 정보는 게임 데이터가 바뀔 때마다 '
      '갱신됩니다.</footer>')
    a('</div>')
    a('</body>')
    a('</html>')

    body = '\n'.join(w) + '\n'

    with open(OUT_HTML, 'w', encoding='utf-8', newline='\n') as fp:
        fp.write(body)

    return len(body)


def write_tsv(boxes, pity, stars, stamp):
    """게임 안에서 보여줄 표.

    화면 쪽이 아직 없으므로 줄을 그대로 찍기만 하면 되게 만든다.
    depth 는 들여쓰기 단계다.
    """
    w = []
    a = w.append

    a('#rates\t1')
    a('#stamp\t%s' % stamp)
    a('#pity\t%d\t%d\t%d' % (pity['after'], pity['minus'], pity['grade']))
    a('#cols\tbox\tdepth\tlabel\tvalue')

    for n, box in enumerate(boxes):
        a('%d\t0\t%s\t' % (n, box_title(n)))

        last = None

        for kind, label, value in box_rows(box, pity, stars):
            if kind != last:
                a('%d\t1\t%s\t' % (n, kind))
                last = kind

            a('%d\t2\t%s\t%s' % (n, label, value))

        a('%d\t1\t%s\t' % (n, '개별 아이템'))

        for label, cnt, p in (item_rows(box, stars, 'crew')
                              + item_rows(box, stars, 'equip')):
            a('%d\t2\t%s\t%s (%d종)' % (n, label, fmt(p), cnt))

    body = '\n'.join(w) + '\n'

    with open(OUT_TSV, 'w', encoding='utf-8', newline='\n') as fp:
        fp.write(body)

    return len(w)


STYLE = """
:root {
  --bg: #ffffff;
  --fg: #1a1a1a;
  --dim: #666666;
  --line: #e2e2e2;
  --accent: #0b5d6b;
  --head: #f4f6f7;
}

@media (prefers-color-scheme: dark) {
  :root {
    --bg: #14171a;
    --fg: #e6e8ea;
    --dim: #9aa0a6;
    --line: #2a2f34;
    --accent: #58b6c4;
    --head: #1c2126;
  }
}

* { box-sizing: border-box; }

body {
  margin: 0;
  padding: 20px 18px 56px;
  background: var(--bg);
  color: var(--fg);
  font-family: -apple-system, BlinkMacSystemFont, "Malgun Gothic",
               "Apple SD Gothic Neo", "Noto Sans KR", sans-serif;
  font-size: 15px;
  line-height: 1.75;
  word-break: keep-all;
  -webkit-text-size-adjust: 100%;
}

.wrap { max-width: 720px; margin: 0 auto; }

h1 { font-size: 21px; margin: 0 0 4px; letter-spacing: -0.02em; }

.meta {
  color: var(--dim);
  font-size: 13px;
  margin-bottom: 28px;
  padding-bottom: 20px;
  border-bottom: 1px solid var(--line);
}

h2 {
  font-size: 16px;
  margin: 34px 0 10px;
  padding-top: 4px;
  letter-spacing: -0.01em;
}

p, li { margin: 8px 0; }

ol, ul { padding-left: 20px; margin: 8px 0; }

ol.num { padding-left: 22px; }

.note {
  border-left: 3px solid var(--accent);
  padding: 10px 14px;
  margin: 16px 0 8px;
  background: color-mix(in srgb, var(--accent) 8%, transparent);
  font-size: 14px;
}

.note p { margin: 6px 0; }

.dim { color: var(--dim); font-size: 13px; }

.scroll { overflow-x: auto; margin: 12px 0; }

table {
  border-collapse: collapse;
  width: 100%;
  font-size: 14px;
  font-variant-numeric: tabular-nums;
}

th, td {
  border-bottom: 1px solid var(--line);
  padding: 7px 10px;
  text-align: left;
  white-space: nowrap;
}

th { background: var(--head); font-weight: 600; }

td.k { color: var(--dim); }

details {
  margin: 10px 0 4px;
  border: 1px solid var(--line);
  border-radius: 6px;
  padding: 0 12px;
}

summary {
  cursor: pointer;
  padding: 9px 0;
  font-size: 14px;
  color: var(--accent);
}

details[open] summary { border-bottom: 1px solid var(--line); }

footer {
  margin-top: 44px;
  padding-top: 20px;
  border-top: 1px solid var(--line);
  color: var(--dim);
  font-size: 13px;
}
"""


def main():
    import datetime

    read_equip_types()

    boxes = read_boxes()
    pity = read_pity()
    pack = read_pack()
    stars = star_counts(pack, read_item_types())
    stamp = datetime.date.today().strftime('%Y년 %m월 %d일')

    n = write_html(boxes, pity, stars, stamp)
    m = write_tsv(boxes, pity, stars, stamp)

    print('상자 %d개, 천장 %d회' % (len(boxes), pity['after']))
    print('  %s  (%s바이트)' % (os.path.relpath(OUT_HTML, ROOT), '{:,}'.format(n)))
    print('  %s  (%d줄)' % (os.path.relpath(OUT_TSV, ROOT), m))

    #5성 기본 확률이 0 인 상자는 눈에 띄게 알린다. 표에는 정직하게 적히지만
    #의도한 것이 아니라면 밸런스 쪽에서 알아야 한다.
    zero = [box_title(i) for i, b in enumerate(boxes)
            if grade_table(b['crewGradeRate'])[pity['grade']] == 0]

    if zero:
        print('\n알림: %s 은(는) 5성 기본 확률이 0%%다.'
              ' 천장으로만 나온다.' % ', '.join(zero))

    return 0


if __name__ == '__main__':
    sys.exit(main())
