# -*- coding: utf-8 -*-
"""동료의 세 번째 스킬을 히어로 스킬과 몬스터 소환으로 나눠 붙인다.

세 번째 스킬은 슬롯에 그 동료가 셋 다 떴을 때 나온다. 제일 큰 것이므로
총알을 한 발 더 쏘는 것으로는 모자란다. 히어로가 나서거나 무언가를
불러내야 "셋이 떴다"는 느낌이 난다.

[무엇으로 나누나]

    싸우는 쪽    기사 병사 사냥꾼 무사     -> 히어로 스킬
    부리는 쪽    마법사 유령 동물 자연     -> 몬스터 소환

[세기는 별로 정한다]

별이 높을수록 센 것이 나온다. 히어로 스킬은 연타수로, 소환은 몬스터의
체력으로 줄을 세웠다.

    별 1~2   에어크래쉬(10) 부스트슬래쉬(20) / 슬라임 아르곤 같은 것
    별 3~4   마구찌르기(30) 소울크래쉬(35) / 골렘 기사 같은 것
    별 5~6   멸살연참(70) 오비탈레이져(150) / 티어맷 아리만 같은 것

    python tools/content/skill3_match.py           #무엇이 바뀌는지만
    python tools/content/skill3_match.py --write   #실제로 고친다
"""
import argparse
import io
import os

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, '..', '..'))
CONTENT = os.path.join(ROOT, 'content')

#동료 번호 -> ('H', 히어로스킬) 또는 ('S', 몬스터)
#주석은 (별) 동료이름 - 왜 그것인가
MATCH = {
    # ── 별 1~2 : 약한 것 ──
    0:  ('H', 'SKILL_ROBIN6'),        # (1) BOY        소년, 로빈이 대신 나선다
    1:  ('S', 'ENEMY_FAIRY'),         # (1) GIRL       소녀 - 라이트스피릿
    2:  ('S', 'ENEMY_SLIME'),         # (1) GRANDMA    할머니 - 슬라임
    3:  ('H', 'SKILL_ROBIN6'),        # (1) GRANDFA    할아버지
    4:  ('H', 'SKILL_ROBIN8'),        # (1) MAN        아저씨
    5:  ('S', 'ENEMY_FAIRY'),         # (1) WOMAN      아주머니
    6:  ('H', 'SKILL_ROBIN8'),        # (1) UNCLE      아저씨
    7:  ('S', 'ENEMY_SLIME'),         # (1) AUNT       아주머니
    8:  ('H', 'SKILL_MAXX7'),         # (1) SEAUNCLE   뱃사람
    9:  ('H', 'SKILL_ROBIN8'),        # (2) SEASOLDIER 병사
    10: ('H', 'SKILL_ROBIN6'),        # (2) MILESE     소년
    11: ('H', 'SKILL_ROBIN6'),        # (2) ALMA       소년
    12: ('H', 'SKILL_MAXX7'),         # (2) CREW       선원
    13: ('S', 'ENEMY_LARVA'),         # (2) TRAVEL     여행자 - 아르곤
    14: ('H', 'SKILL_DIANA7'),        # (2) ELFBOY     엘프 소년
    15: ('S', 'ENEMY_FAIRY'),         # (2) ELFGIRL    엘프 소녀
    16: ('S', 'ENEMY_LARVA'),         # (2) ITEM       물건 파는 이
    17: ('H', 'SKILL_DIANA7'),        # (2) ELFUNCLE   엘프 아저씨
    18: ('S', 'ENEMY_SLIME'),         # (2) ELFAUNT    엘프 아주머니

    # ── 별 3~4 : 중간 ──
    19: ('H', 'SKILL_ROBIN7'),        # (3) ADELKNIGHT 기사
    20: ('S', 'ENEMY_ANGEL'),         # (3) OWL        부엉이 - 호루스
    21: ('S', 'ENEMY_GHOST'),         # (3) MAID       메이드 - 떠도는 영혼
    22: ('H', 'SKILL_DIANA9'),        # (3) BUNNYGIRL  버니걸
    23: ('S', 'ENEMY_SLING'),         # (3) MAP        지도 - 평원의 도적
    24: ('S', 'ENEMY_CASTLE1'),       # (3) MONICA     책 - 어둠의 마도사
    25: ('S', 'ENEMY_JELLYFISH'),     # (3) SEABOY     바다 소년 - 맹독해파리
    26: ('H', 'SKILL_ROBIN9'),        # (3) DOBEL      갑옷
    27: ('H', 'SKILL_MAXX9'),         # (3) GAGEL      사냥꾼
    28: ('S', 'ENEMY_CASTLE1'),       # (3) ELFGRANDFA 엘프 노인 - 마도사
    29: ('S', 'ENEMY_FLAME'),         # (4) ELFWOMAN   엘프 여자 - 분노의 정령
    30: ('H', 'SKILL_ROBIN10'),       # (4) ELFMAN     엘프 남자
    31: ('H', 'SKILL_DIANA9'),        # (4) ELFDANCER  댄서
    32: ('S', 'ENEMY_KNIGHT'),        # (4) NOBLEMAN   귀족 - 타락한 기사
    33: ('S', 'ENEMY_CASTLE1'),       # (4) SCHOLAR    학자 - 마도사
    34: ('S', 'ENEMY_MACHINE'),       # (4) NETITEM    기계 - 라이오너
    35: ('H', 'SKILL_ROBIN9'),        # (4) FATMAN     뚱보
    36: ('S', 'ENEMY_GOLEM'),         # (4) CRAFTMAN   장인 - 주인잃은 골렘
    37: ('S', 'ENEMY_FAIRY'),         # (4) LUISE      소녀
    38: ('S', 'ENEMY_PUMPKIN'),       # (4) DOG        개 - 무혼의 기사

    # ── 별 5~6 : 센 것 ──
    39: ('H', 'SKILL_ROBIN7'),        # (5) KNIGHT     기사
    40: ('S', 'ENEMY_CASTLE1'),       # (5) WITCH      마녀 - 어둠의 마도사
    41: ('H', 'SKILL_MAXX9'),         # (5) BISTRO     식당
    42: ('H', 'SKILL_ROBIN10'),       # (5) SEBASTIAN  집사
    43: ('S', 'ENEMY_FROG'),          # (5) FISHING    낚시꾼 - 토드뮤턴트
    44: ('S', 'ENEMY_SLING'),         # (5) FRAUD      사기꾼 - 평원의 도적
    45: ('S', 'ENEMY_SALAMANDER'),    # (5) ELFMAGIC   엘프 마법사 - 카툼
    46: ('S', 'ENEMY_GIANT'),         # (5) DARIAN     드루이드 - 고대의 수호자
    47: ('H', 'SKILL_ROBIN10'),       # (5) DONALD     소년
    48: ('H', 'SKILL_DIANA8'),        # (5) ELFDARK    다크 엘프
    49: ('S', 'ENEMY_SPACE2'),        # (5) NEZAR      왕족 - 메탈가우스
    50: ('H', 'SKILL_ROBIN11'),       # (5) DURAK      기사
    51: ('S', 'ENEMY_GHOST'),         # (6) WOMANGHOST 여자 유령
    52: ('S', 'ENEMY_SKELETON'),      # (6) MANGHOST   남자 유령 - 칠흑의 기사
    53: ('S', 'ENEMY_FACE'),          # (6) AUSTIN     석상 - 결빙의 석상
    54: ('S', 'ENEMY_KIMERA'),        # (6) ELEIN      마법사 - 마도합성수
    55: ('H', 'SKILL_ROBIN11'),       # (6) USERQUEST  소년
    56: ('H', 'SKILL_MAXX13'),        # (6) CHEF       요리사
    57: ('H', 'SKILL_DIANA11'),       # (6) CAPTAIN    선장
    58: ('S', 'ENEMY_ELKEIN'),        # (6) ELKEIN     엘케인
    59: ('H', 'SKILL_ROBIN12'),       # (6) DELPIOS    왕자
    60: ('S', 'ENEMY_LABETH'),        # (6) LABETH     라베스
    61: ('H', 'SKILL_DIANA12'),       # (6) EVAN       소년
    62: ('S', 'ENEMY_BAHAMUT'),       # (6) LORA       공주 - 티어맷
    63: ('H', 'SKILL_ROBIN12'),       # (6) KING       왕
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
    ap = argparse.ArgumentParser()
    ap.add_argument('--write', action='store_true')
    a = ap.parse_args()

    shead, sc, sr, snl = read_tsv('skill')
    _h, cc, cr, _n = read_tsv('crew')

    byName = {r[1]: r for r in sr}
    C = {n: i for i, n in enumerate(sc)}
    S3 = cc.index('skill3')

    nH = nS = 0
    keep = []

    for c in cr:
        cid = int(c[0])
        m = MATCH.get(cid)
        row = byName.get(c[S3])

        if m is None or row is None:
            continue

        #이미 특수한 것으로 손봐 둔 줄은 건드리지 않는다.
        #SUMMONHERO 는 히어로를 장비까지 입혀 불러내고, CREWSUMMON 은
        #그 동료 전용 소환이다. 둘 다 여기서 정할 것이 아니다.
        if row[C['kind']] in ('SUMMONHERO', 'CREWSUMMON', 'SUMMON',
                              'HEROSKILL'):
            keep.append((cid, (c[1] or '').replace('CREW_', ''),
                         row[C['kind']]))
            continue

        kind, what = m
        before = '%s %s' % (row[C['kind']],
                            row[C['hero_skill']] if row[C['kind']] == 'HEROSKILL'
                            else row[C['summon_enemy']])

        #쓰던 칸을 먼저 비운다. 종류가 바뀌면 옛 값이 남아 헷갈린다.
        for k in ('summon_enemy', 'hero_type', 'hero_skill', 'bullet_obj',
                  'bullet_icon', 'hit_max'):
            row[C[k]] = '0'

        if kind == 'H':
            #이미 자리에 서 있는 히어로가 자기 스킬을 쓴다.
            row[C['kind']] = 'HEROSKILL'
            row[C['host_obj']] = 'ROBIN'
            row[C['hero_skill']] = what
            row[C['icon_kind']] = 'ICONKIND_SKILL'

            #아이콘은 그 히어로 스킬의 것을 그대로 쓴다.
            ref = byName.get(what)
            row[C['icon']] = ref[C['icon']] if ref else '0'
            nH += 1
        else:
            row[C['kind']] = 'SUMMON'
            row[C['host_obj']] = 'SOLDIER'
            row[C['summon_enemy']] = what
            row[C['icon_kind']] = 'ICONKIND_MONSTER'
            row[C['icon']] = what
            nS += 1

        print('  %-3s %-14s %-22s -> %s %s'
              % (cid, (c[1] or '').replace('CREW_', ''), before,
                 row[C['kind']], what))

    print()
    print('히어로 스킬 %d명, 몬스터 소환 %d명' % (nH, nS))

    if keep:
        print('그대로 둔 것 %d명 (이미 특수 스킬이다)' % len(keep))

        for cid, nm, k in keep:
            print('   %-3s %-14s %s' % (cid, nm, k))

    if not a.write:
        print('보기만 했다. 고치려면 --write')
        return

    p = os.path.join(CONTENT, 'skill.tsv')
    out = shead + ['\t'.join(sc)] + ['\t'.join(r) for r in sr]

    with io.open(p, 'w', encoding='utf-8', newline='') as fp:
        fp.write(snl.join(out) + snl)

    print('%s 를 고쳤다' % p)


main()
