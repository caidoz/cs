# -*- coding: utf-8 -*-
"""wave[] 를 만든다. 10000 웨이브를 한 번에 깐다.

[왜 생성기인가]
wave[] 는 한 웨이브가 3마리 x 3칸 = 9칸이다. 10000 웨이브면 90000칸이다.
손으로 적을 수 있는 양이 아니고, 적었다 해도 "5번째는 소보스" 같은 규칙이
지켜지고 있는지 눈으로 확인할 방법이 없다. 규칙을 코드로 적어 두면 규칙이
곧 데이터고, 손잡이를 돌려 다시 깔 수 있다.

    python tools/content/make_waves.py            #다시 깐다
    python tools/content/make_waves.py --check    #깔지 않고 요약만 본다

[세기를 무엇으로 정하는가]
세 축이 있다. 바깥에서 안쪽으로.

  1. 컬러  기본 < 레드 < 블루 < 퍼플 < 그린 < 골드 < 블랙   (7단)
  2. 지역  늪 -> ... -> 우주                                 (15곳)
  3. 역할  잡몹 / 소보스(5판) / 중보스(10판) / 대보스(100판)

즉 기본색으로 늪부터 우주까지 한 바퀴 돌고, 그 다음 레드로 다시 늪부터
돈다. 한 바퀴가 10000/7 = 1428 웨이브, 한 지역이 그 안에서 95 웨이브다.

[색은 한꺼번에 갈리지 않는다]
바퀴가 넘어가는 순간 온 세상이 레드가 되면 그건 색이 아니라 그냥 눈금이다.
색은 약방의 감초여야 한다 - 잡몹이 아직 기본색일 때 열 번째 자리에 레드
한 마리가 서 있고, 백 번째에 블루가 서 있는 식이다. 그래서

    잡몹, 소보스  그 바퀴의 색 그대로
    중보스        한 단 위      (COLOR_BUMP_MIDBOSS)
    대보스        두 단 위      (COLOR_BUMP_BIGBOSS)

로 올려 세운다. 플레이어는 다음 색을 보스로 먼저 만나고, 한참 뒤에 그 색이
잡몹으로 내려온다. 마지막 바퀴(블랙)에서는 더 올라갈 데가 없어 그대로 선다.

지역은 CastleDef.h 의 열거 순서를 그대로 쓴다. 그게 게임이 생각하는
"뒤쪽 지역"의 순서다. 몬스터가 어느 지역 출신인지는 crewPos[] 의
home_castle 칸에 이미 적혀 있다(content/enemy.tsv 의 home_castle).

[보스]
IsBigMonster() 가 true 를 돌려주는 놈이 덩치다(Func_Movement.cpp).
지역마다 덩치를 뽑아 10번째 자리에 세운다. 덩치가 없는 지역(하수도, 뇌전)은
바로 앞 지역의 덩치를 빌려 온다.

소보스(5판)는 덩치가 아니라 그 지역에서 가장 단단한 잡몹이다.

자리는 wave[] 세번째 칸에 적는다(Def.h 의 MONSTERTYPE_*). 게임이 이 칸을
보고 체력 배수를 곱하고(BalanceConfig.h 의 WAVE_HP_*_MUL) 하트 보상을
정한다. 잡몹 / 소보스 / 중보스 / 대보스가 각각 다른 값이라야 한다.

[마리 수]
기본 한 마리다. 보스 웨이브는 반드시 한 마리다. 나머지 중에서
  n % MULTI3_EVERY == 0  -> 세 마리
  n % MULTI2_EVERY == 0  -> 두 마리
로 끼워 넣는다. 지금 값이면 두 마리가 20%, 세 마리가 6% 쯤이다.

[튜토리얼]
0~3번 행은 튜토리얼 4연전이 쓴다(TutoralDef.h). 지금 파일에 있는 네 행을
그대로 읽어와서 그대로 다시 쓴다. 여기를 건드리면 튜토리얼이 깨진다.
"""
import argparse
import io
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, '..', '..'))
CLASSES = os.path.join(ROOT, 'Classes')

WAVE_CPP = os.path.join(CLASSES, 'Data', 'WaveData.cpp')
WAVE_H = os.path.join(CLASSES, 'Data', 'WaveData.h')
ENEMY_CPP = os.path.join(CLASSES, 'Data', 'EnemyData.cpp')
UI_CPP = os.path.join(CLASSES, 'Data', 'UIData.cpp')
MOVE_CPP = os.path.join(CLASSES, 'Func_Movement.cpp')

#---- 손잡이 ---------------------------------------------------------------

TOTAL_WAVE = 10000      #깔 웨이브 수
MAXWAVEENEMY = 3        #Def.h 와 같아야 한다
WAVEDATASIZE = 3        #Def.h 와 같아야 한다
TUTORIAL_ROWS = 4       #앞에서 그대로 보존할 행 수

BIGBOSS_EVERY = 100     #대보스 자리
MIDBOSS_EVERY = 10      #중보스 자리
SUBBOSS_EVERY = 5       #소보스 자리

#보스가 제 바퀴보다 몇 단 위의 색으로 서는가. 0 이면 색이 안 섞인다.
COLOR_BUMP_MIDBOSS = 1
COLOR_BUMP_BIGBOSS = 2
MULTI2_EVERY = 4        #두 마리
MULTI3_EVERY = 13       #세 마리

#컬러가 곧 단계다. 열거가 이 순서로 51마리씩 끊겨 있다(Def/EnemyDef.h).
COLORS = ['', '_RED', '_BLUE', '_PURPLE', '_GREEN', '_GOLD', '_BLACK']

#CastleDef.h 의 순서. 몬스터가 사는 곳만 추린다. 앞이 약하고 뒤가 세다.
REGION_ORDER = [
    'CASTLE_SWAMP', 'CASTLE_VALLEY', 'CASTLE_ATLANTICE', 'CASTLE_SEWAGE',
    'CASTLE_PLAIN', 'CASTLE_FLAME', 'CASTLE_FROST', 'CASTLE_THUNDER',
    'CASTLE_LIGHT', 'CASTLE_GOLEMVALLEY', 'CASTLE_DARKNESS', 'CASTLE_DRAGON',
    'CASTLE_GHOST', 'CASTLE_DEVILCASTLE', 'CASTLE_SPACE',
]

REGION_NAME = {
    'CASTLE_SWAMP': '늪', 'CASTLE_VALLEY': '계곡', 'CASTLE_ATLANTICE': '아틀란티스',
    'CASTLE_SEWAGE': '하수도', 'CASTLE_PLAIN': '평원', 'CASTLE_FLAME': '화염',
    'CASTLE_FROST': '빙설', 'CASTLE_THUNDER': '뇌전', 'CASTLE_LIGHT': '빛',
    'CASTLE_GOLEMVALLEY': '골렘계곡', 'CASTLE_DARKNESS': '암흑',
    'CASTLE_DRAGON': '드래곤', 'CASTLE_GHOST': '망령', 'CASTLE_DEVILCASTLE': '마성',
    'CASTLE_SPACE': '우주',
}

COLOR_NAME = {'': '기본', '_RED': '레드', '_BLUE': '블루', '_PURPLE': '퍼플',
              '_GREEN': '그린', '_GOLD': '골드', '_BLACK': '블랙'}

#쓰지 않을 몬스터를 여기 적는다(기본색 이름으로). 지금은 없다.
EXCLUDE = set()


def read(path):
    return io.open(path, encoding='utf-8-sig').read()


def load_monsters():
    """id -> {name, label, addhp, castle} 를 만든다.

    라벨과 add_hp 는 enemyData_builtin 에서, 지역은 crewPos_builtin 에서
    읽는다. content/enemy.tsv 에도 같은 값이 있지만 그 파일은 라벨이
    인코딩 변환 때 깨져 있어서(U+FFFD) 주석을 만들 수가 없다.
    """
    body = re.search(r'static const signed short enemyData_builtin\[\] = \{(.*?)\n\};',
                     read(ENEMY_CPP), re.S).group(1)
    mon = {}
    row = re.compile(r'^\s*(?P<cmf>\w+)\s*,[^,]*,[^,]*,[^,]*,\s*(?P<addhp>-?\d+)\s*,'
                     r'.*?//(?P<id>\d+)\s+(?P<name>ENEMY_\w+)\s+(?P<label>.*?)\s*$')
    for line in body.split('\n'):
        m = row.match(line)
        if m:
            mon[int(m.group('id'))] = {
                'id': int(m.group('id')),
                'name': m.group('name'),
                'label': m.group('label'),
                'addhp': int(m.group('addhp')),
            }

    body = re.search(r'static const signed short crewPos_builtin\[\] = \{(.*?)\n\};',
                     read(UI_CPP), re.S).group(1)
    for m in re.finditer(r'(CASTLE_\w+),\s*//(\d+)\s+(ENEMY_\w+)', body):
        i = int(m.group(2))
        if i in mon:
            assert mon[i]['name'] == m.group(3), (i, mon[i]['name'], m.group(3))
            mon[i]['castle'] = m.group(1)

    return mon


def load_big():
    """IsBigMonster() 가 true 를 주는 이름을 긁는다."""
    src = read(MOVE_CPP)
    body = re.search(r'int IsBigMonster\(int objType\)\s*\{(.*?)\n\}', src, re.S).group(1)
    body = body.split('return true;')[0]
    names = set()
    for line in body.split('\n'):
        line = line.strip()
        if line.startswith('//'):       #주석 처리된 case 는 빼야 한다
            continue
        m = re.match(r'case\s+(ENEMY_\w+)\s*:', line)
        if m:
            names.add(m.group(1))
    return names


def build_pool(mon, big):
    """지역 -> {jaco[], big[], sub, mid[]} (기본색 기준)"""
    pool = {}
    for i in sorted(mon):
        if i > 53:      #기본색 51마리만 본다. 색은 나중에 붙인다.
            continue
        m = mon[i]
        if m['name'] in EXCLUDE:
            continue
        pool.setdefault(m['castle'], {'jaco': [], 'big': []})
        (pool[m['castle']]['big'] if m['name'] in big
         else pool[m['castle']]['jaco']).append(m)

    for castle in REGION_ORDER:
        p = pool[castle]
        assert p['jaco'], castle
        #소보스 : 잡몹 중 제일 단단한 놈. 덧살이 같으면 열거 뒤쪽이 센 놈이다.
        p['sub'] = max(p['jaco'], key=lambda m: (m['addhp'], m['id']))

    #중보스 : 그 지역의 덩치다. 덩치가 없는 지역(하수도, 뇌전)은 바로 앞
    #지역에서 빌려 온다. 그 지역 잡몹 중 하나를 세우면 소보스와 구별이 안
    #되기 때문이다 - 10번째 자리는 눈에 띄게 커야 한다.
    for i, castle in enumerate(REGION_ORDER):
        p = pool[castle]
        if p['big']:
            p['mid'] = p['big']
            continue
        for j in list(range(i - 1, -1, -1)) + list(range(i + 1, len(REGION_ORDER))):
            if pool[REGION_ORDER[j]]['big']:
                p['mid'] = pool[REGION_ORDER[j]]['big']
                break
        else:
            p['mid'] = [p['sub']]
    return pool


def colored(m, tier):
    return m['name'] + COLORS[tier]


def make_waves(pool):
    """(머리주석, [(타입, 보스인가)], [라벨]) 를 TOTAL_WAVE 개 만든다."""
    seg_cnt = len(COLORS) * len(REGION_ORDER)
    waves = []

    for idx in range(TOTAL_WAVE):
        #이 웨이브가 몇 번째 구역에 속하는가. 구역을 고르게 나눈다.
        seg = idx * seg_cnt // TOTAL_WAVE
        tier, ri = divmod(seg, len(REGION_ORDER))
        castle = REGION_ORDER[ri]
        p = pool[castle]

        n = idx + 1     #사람이 세는 번호. "5번째" 는 이쪽이다.
        bump = 0        #보스가 제 바퀴보다 몇 단 위의 색으로 서는가

        if n % BIGBOSS_EVERY == 0:
            role = '대보스'
            picks = [p['mid'][(n // BIGBOSS_EVERY) % len(p['mid'])]]
            bump = COLOR_BUMP_BIGBOSS
            kind = 'MONSTERTYPE_BIGBOSS'
        elif n % MIDBOSS_EVERY == 0:
            role = '중보스'
            picks = [p['mid'][(n // MIDBOSS_EVERY) % len(p['mid'])]]
            bump = COLOR_BUMP_MIDBOSS
            kind = 'MONSTERTYPE_MIDBOSS'
        elif n % SUBBOSS_EVERY == 0:
            role = '소보스'
            picks = [p['sub']]
            kind = 'MONSTERTYPE_BOSS'
        else:
            role = '잡몹'
            kind = 'MONSTERTYPE_JACO'
            if n % MULTI3_EVERY == 0:
                cnt = 3
            elif n % MULTI2_EVERY == 0:
                cnt = 2
            else:
                cnt = 1
            cnt = min(cnt, MAXWAVEENEMY, )
            picks = [p['jaco'][(n + k) % len(p['jaco'])] for k in range(cnt)]

        #마지막 바퀴에서는 더 올라갈 색이 없다.
        wear = min(tier + bump, len(COLORS) - 1)

        slots = [(colored(m, wear), kind) for m in picks]
        head = '%s %s - %d %s%s' % (REGION_NAME[castle], COLOR_NAME[COLORS[tier]],
                                    n, role,
                                    '' if wear == tier else '(%s)' % COLOR_NAME[COLORS[wear]])
        waves.append((head, slots, [m['label'] for m in picks]))

    return waves


def render(waves, tutorial_text):
    out = [tutorial_text.rstrip('\n'), '']
    for head, slots, labels in waves[TUTORIAL_ROWS:]:
        out.append('\t//%s' % head)
        for s in range(MAXWAVEENEMY):
            if s < len(slots):
                typ, kind = slots[s]
                out.append('\t%s, FPS * %d, %s,//%s' % (typ, s + 1, kind, labels[s]))
            else:
                out.append('\tfalse, FPS * %d, MONSTERTYPE_JACO,//%d' % (s + 1, s + 1))
        out.append('')
    return '\n'.join(out)


def grab_tutorial(cpp):
    """지금 파일의 앞 TUTORIAL_ROWS 행을 주석까지 통째로 떼어 온다."""
    body = re.search(r'static const int wave_builtin\[\] = \{(.*?)\n\};', cpp, re.S).group(1)
    kept, rows = [], 0
    for line in body.split('\n'):
        kept.append(line)
        #한 행(웨이브)은 슬롯 MAXWAVEENEMY 개다. 마지막 슬롯을 세면 된다.
        if re.search(r'FPS \* %d\s*,' % MAXWAVEENEMY, re.sub(r'//.*', '', line)):
            rows += 1
            if rows == TUTORIAL_ROWS:
                break
    assert rows == TUTORIAL_ROWS, rows
    return '\n'.join(kept)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--check', action='store_true', help='쓰지 않고 요약만')
    args = ap.parse_args()

    mon = load_monsters()
    big = load_big()
    pool = build_pool(mon, big)
    waves = make_waves(pool)

    total = TOTAL_WAVE * MAXWAVEENEMY * WAVEDATASIZE

    print('지역 %d곳 x 컬러 %d단 = 구역 %d개, 구역당 %.1f 웨이브'
          % (len(REGION_ORDER), len(COLORS), len(COLORS) * len(REGION_ORDER),
             float(TOTAL_WAVE) / (len(COLORS) * len(REGION_ORDER))))
    for castle in REGION_ORDER:
        p = pool[castle]
        print('  %-10s 잡몹 %d  덩치 %d  소보스 %s  중보스 %s'
              % (REGION_NAME[castle], len(p['jaco']), len(p['big']),
                 p['sub']['label'], '/'.join(m['label'] for m in p['mid'])))

    cnt = {1: 0, 2: 0, 3: 0}
    role = {'대보스': 0, '중보스': 0, '소보스': 0, '잡몹': 0}
    for head, slots, _ in waves:
        cnt[len(slots)] += 1
        for k in role:
            if k in head:
                role[k] += 1
                break
    print('웨이브 %d  (한마리 %d, 두마리 %d, 세마리 %d)' % (TOTAL_WAVE, cnt[1], cnt[2], cnt[3]))
    print('대보스 %d  중보스 %d  소보스 %d  잡몹 %d'
          % (role['대보스'], role['중보스'], role['소보스'], role['잡몹']))
    print('wave_COUNT = %d' % total)

    if args.check:
        return 0

    cpp = read(WAVE_CPP)
    text = render(waves, grab_tutorial(cpp))
    cpp = re.sub(r'(static const int wave_builtin\[\] = \{\n).*?(\n\};)',
                 lambda m: m.group(1) + text + m.group(2), cpp, count=1, flags=re.S)
    io.open(WAVE_CPP, 'w', encoding='utf-8-sig', newline='').write(cpp)

    h = read(WAVE_H)
    h = re.sub(r'enum \{ wave_COUNT = \d+ \};',
               'enum { wave_COUNT = %d };' % total, h)
    io.open(WAVE_H, 'w', encoding='utf-8-sig', newline='').write(h)

    print('썼다: %s, %s' % (os.path.relpath(WAVE_CPP, ROOT), os.path.relpath(WAVE_H, ROOT)))
    return 0


if __name__ == '__main__':
    sys.exit(main())
