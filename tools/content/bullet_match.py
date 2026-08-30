# -*- coding: utf-8 -*-
"""동료 생김새에 맞는 총알 아이콘을 붙인다.

crewBullet.png 은 세 칸이 한 세트다. 같은 물건의 보통/은/금 판이라,
    skill1 -> 3 * 세트 + 0
    skill2 -> 3 * 세트 + 1
로 붙이면 1 번보다 2 번이 좋아 보인다. 남는 +2 는 나중을 위해 비워 둔다.

세트를 고른 기준은 "그 동료가 손에 들고 있을 법한 것"이다. 요리사가
프라이팬을 던지고 선원이 닻을 던지는 식이다. 숫자만 봐서는 밸런스를
못 잡으니 그림이 맞아야 한다.

    python tools/content/bullet_match.py           #무엇이 바뀌는지만 본다
    python tools/content/bullet_match.py --write   #실제로 고친다

고친 뒤에는 소스와 팩을 다시 내야 한다.
    python tools/content/content_table.py skill generate --write
    python tools/content/build_pack.py
"""
import argparse
import io
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, '..', '..'))
CONTENT = os.path.join(ROOT, 'content')

#세트 번호 -> 무엇인가. crewBullet.png 을 눈으로 보고 적었다.
SET_NAME = {
    0: '돌', 3: '구슬', 6: '꽃', 9: '부채', 12: '인형', 15: '지팡이',
    18: '두루마리', 21: '망치', 24: '술병', 27: '만두', 30: '물약',
    33: '닻', 36: '뼈', 39: '단검', 42: '물고기', 45: '소라',
    48: '폭탄', 51: '돈주머니', 54: '하프', 57: '우산', 60: '창',
    63: '프라이팬', 66: '찻잔', 69: '책', 72: '지도', 75: '꽃다발',
}

#동료 번호 -> 세트 번호
MATCH = {
    0: 0,    # BOY          소년           돌
    1: 6,    # GIRL         소녀           꽃
    2: 57,   # GRANDMA      할머니         우산
    3: 15,   # GRANDFA      할아버지       지팡이
    4: 21,   # MAN          아저씨         망치
    5: 75,   # WOMAN        아주머니       꽃다발
    6: 24,   # UNCLE        아저씨         술병
    7: 63,   # AUNT         아주머니       프라이팬
    8: 33,   # SEAUNCLE     뱃사람         닻
    9: 60,   # SEASOLDIER   아틀란 병사    창
    10: 0,   # MILESE       소년           돌
    11: 48,  # ALMA         소년           폭탄
    12: 45,  # CREW         선원           소라
    13: 72,  # TRAVEL       여행자         지도
    14: 39,  # ELFBOY       엘프 소년      단검
    15: 6,   # ELFGIRL      엘프 소녀      꽃
    16: 30,  # ITEM         물건 파는 이   물약
    17: 18,  # ELFUNCLE     엘프 아저씨    두루마리
    18: 66,  # ELFAUNT      엘프 아주머니  찻잔
    19: 60,  # ADELKNIGHT   기사           창
    20: 69,  # OWL          부엉이         책
    21: 66,  # MAID         메이드         찻잔
    22: 9,   # BUNNYGIRL    버니걸         부채
    23: 72,  # MAP          지도           지도
    24: 69,  # MONICA       책 든 여자     책
    25: 42,  # SEABOY       바다 소년      물고기
    26: 39,  # DOBEL        갑옷           단검
    27: 60,  # GAGEL        사냥꾼         창 (화살 대용)
    28: 15,  # ELFGRANDFA   엘프 노인      지팡이
    29: 6,   # ELFWOMAN     엘프 여자      꽃
    30: 39,  # ELFMAN       엘프 남자      단검
    31: 9,   # ELFDANCER    댄서           부채
    32: 51,  # NOBLEMAN     귀족           돈주머니
    33: 18,  # SCHOLAR      학자           두루마리
    34: 30,  # NETITEM      물건           물약
    35: 27,  # FATMAN       뚱보           만두
    36: 21,  # CRAFTMAN     장인           망치
    37: 12,  # LUISE        소녀           인형
    38: 36,  # DOG          개             뼈
    39: 39,  # KNIGHT       기사           단검
    40: 30,  # WITCH        마녀           물약
    41: 63,  # BISTRO       식당           프라이팬
    42: 66,  # SEBASTIAN    집사           찻잔
    43: 42,  # FISHING      낚시꾼         물고기
    44: 51,  # FRAUD        사기꾼         돈주머니
    45: 3,   # ELFMAGIC     엘프 마법사    구슬
    46: 18,  # DARIAN       드루이드       두루마리
    47: 0,   # DONALD       소년           돌
    48: 39,  # ELFDARK      다크 엘프      단검
    49: 51,  # NEZAR        왕족           돈주머니
    50: 60,  # DURAK        기사           창
    51: 54,  # WOMANGHOST   여자 유령      하프
    52: 36,  # MANGHOST     남자 유령      뼈
    53: 0,   # AUSTIN       석상           돌
    54: 3,   # ELEIN        마법사         구슬
    55: 0,   # USERQUEST    소년           돌
    56: 63,  # CHEF         요리사         프라이팬
    57: 33,  # CAPTAIN      선장           닻
    58: 60,  # ELKEIN       보라 갑옷      창
    59: 39,  # DELPIOS      왕자           단검 (검 대용)
    60: 3,   # LABETH       흰옷 마법사    구슬
    61: 48,  # EVAN         소년           폭탄
    62: 12,  # LORA         공주           인형
    63: 3,   # KING         왕             구슬 (보주 대용)
}


def read_tsv(name):
    p = os.path.join(CONTENT, name + '.tsv')

    with io.open(p, encoding='utf-8', newline='') as fp:
        raw = fp.read()

    nl = '\r\n' if '\r\n' in raw else '\n'
    lines = raw.split(nl)
    head = [l for l in lines if l.startswith('#')]
    body = [l for l in lines if l and not l.startswith('#')]

    return head, body[0].split('\t'), [l.split('\t') for l in body[1:]], nl


def main():
	#2026-08-30 부터 동료와 아이콘이 1:1 이다. 시트가 한 사람에 두 칸을
	#갖고 번호가 식으로 떨어지므로 이 손 대응표는 쓰지 않는다. 그대로
	#돌리면 예전 26 벌 기준으로 되돌려 버린다.
	raise SystemExit('이제 bullet_assign.py 를 써라. '
	                 '이 표는 26 벌을 나눠 쓰던 시절의 것이다.')

def _old_main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--write', action='store_true', help='실제로 고친다')
    a = ap.parse_args()

    shead, scols, srows, snl = read_tsv('skill')
    _ch, ccols, crows, _cnl = read_tsv('crew')

    byName = {r[1]: r for r in srows}
    K = scols.index('kind')
    BI = scols.index('bullet_icon')
    IC = scols.index('icon')
    IK = scols.index('icon_kind')
    S = [ccols.index('skill%d' % i) for i in (1, 2)]

    changed = 0
    skipped = []

    for c in crows:
        cid = int(c[0])
        base = MATCH.get(cid)

        if base is None:
            continue

        for slot, si in enumerate(S):
            row = byName.get(c[si])

            if row is None:
                continue

            #총알을 쏘는 스킬만 바꾼다. 소환이나 히어로 스킬은 그림이
            #다른 데서 온다(icon_kind 가 다르다).
            if row[K] != 'CREWBULLET':
                skipped.append((cid, c[1], slot + 1, row[K]))
                continue

            want = str(base + slot)

            if row[BI] != want or row[IC] != want:
                print('  %-3s %-16s skill%d  %s -> %s  (%s)'
                      % (cid, (c[1] or '').replace('CREW_', ''), slot + 1,
                         row[BI], want, SET_NAME.get(base, '?')))
                row[BI] = want
                row[IC] = want
                row[IK] = 'ICONKIND_BULLET'
                changed += 1

    print()
    print('바뀔 칸 %d개' % changed)

    if skipped:
        print('총알이 아니라 건너뛴 것 %d개' % len(skipped))

        for cid, nm, slot, kind in skipped:
            print('   %-3s %-16s skill%d  %s' % (cid, nm.replace('CREW_', ''),
                                                 slot, kind))

    if not a.write:
        print()
        print('보기만 했다. 실제로 고치려면 --write')
        return

    p = os.path.join(CONTENT, 'skill.tsv')
    out = shead + ['\t'.join(scols)] + ['\t'.join(r) for r in srows]

    with io.open(p, 'w', encoding='utf-8', newline='') as fp:
        fp.write(snl.join(out) + snl)

    print()
    print('%s 를 고쳤다' % p)
    print('이제 소스와 팩을 다시 내라:')
    print('  python tools/content/content_table.py skill generate --write')
    print('  python tools/content/build_pack.py')


main()
