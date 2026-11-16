"""content/merge_tree.tsv (역할 × ★ 표) 를 Classes/Data/MergeTreeData.h 로 굽는다.

합성은 6단 = 성급이다. 같은 역할 ★n 둘 → 그 역할의 ★n+1 동료 중 하나(무작위).
그래서 트리는 '체인'이 아니라 역할군 4개의 ★ 사다리이고, 이 헤더는 64명의
역할·★·특성과 역할×★ 조회만 준다. 장비 계열 단계 폭도 여기 있다.
"""
import argparse
import csv
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / 'content/merge_tree.tsv'
TARGET = ROOT / 'Classes/Data/MergeTreeData.h'
TRAITS = {'표식': 0, '고무': 1, '강타': 2, '연타': 3, '빙결': 4, '지속': 5}
ROLE_NAMES = ['지휘', '포격', '지원', '공격']
EXPECTED = {  # 역할 × ★ 인원. CLAUDE.md 의 64명 분배표와 같아야 한다.
    0: [2, 3, 4, 5, 2, 1], 1: [2, 3, 4, 4, 2, 0], 2: [2, 3, 4, 5, 2, 1], 3: [2, 3, 3, 4, 2, 1]}


def render():
    rows = list(csv.DictReader((line for line in SOURCE.read_text(encoding='utf-8-sig').splitlines()
                               if line and not line.startswith('#')), delimiter='\t'))
    assert len(rows) == 64
    info = {}
    for row in rows:
        crew, role, star = int(row['crew']), int(row['role']), int(row['star'])
        assert 0 <= crew < 64 and crew not in info and 0 <= role < 4 and 1 <= star <= 6
        assert row['role_name'] == ROLE_NAMES[role]
        info[crew] = (role, star, TRAITS[row['trait']], int(row['hero']))
        assert 0 <= info[crew][3] < 3
    assert sorted(info) == list(range(64))
    for role, counts in EXPECTED.items():
        for star in range(1, 7):
            got = sum(1 for r, s, _, _ in info.values() if r == role and s == star)
            assert got == counts[star - 1], (role, star, got)
    # 고유 동료: 히어로가 가진 역할은 ★1 부터 그 역할의 꼭대기 바로 아래까지 끊김이 없어야 한다
    # (Run::canMerge 는 roster 에 ★n+1 이 있어야 합친다). ★6 은 하나뿐이라 한쪽만 갖는다.
    for hero in range(3):
        for role in range(4):
            stars = sorted({s for r, s, _, h in info.values() if r == role and h == hero})
            if not stars:
                continue
            top = max(s for r, s, _, _ in info.values() if r == role)
            assert stars[0] == 1 and stars[-1] >= top - 1 and stars == list(range(1, stars[-1] + 1)), (hero, role, stars)
    lines = ['#pragma once', '// Generated from content/merge_tree.tsv by tools/merge_roulette/build_tree_data.py. Do not edit.',
             '// 합성 6단 = 성급. 같은 역할 ★n 둘 → 그 역할 ★n+1 중 무작위.',
             'namespace MergeTrees {', 'enum { Roles=4, Levels=6, CrewCount=64, MaxPerCell=8 };',
             'struct CrewInfo { int role, star, trait; };',
             'static const CrewInfo Crew[CrewCount]={']
    for crew in range(64):
        role, star, trait, _ = info[crew]
        lines.append(f' {{{role},{star},{trait}}},')
    lines += ['};',
              'static const char* RoleName[Roles]={' + ','.join(f'u8"{n}"' for n in ROLE_NAMES) + '};',
              '// 릴 2·3 가중치. 역할은 전부 ★1 에서 시작하므로 같다. 장비 계열은 호출부가 4 를 준다.',
              'static const int RoleWeight[Roles]={1,1,1,1};',
              'inline int Role(int crew) {return crew>=0&&crew<CrewCount?Crew[crew].role:-1;}',
              'inline int Star(int crew) {return crew>=0&&crew<CrewCount?Crew[crew].star:0;}',
              'inline int Trait(int crew) {return crew>=0&&crew<CrewCount?Crew[crew].trait:2;}',
              'inline int CountAt(int role,int star) {int n=0;for(int c=0;c<CrewCount;++c)if(Crew[c].role==role&&Crew[c].star==star)++n;return n;}',
              'inline int CrewAt(int role,int star,int k) {for(int c=0;c<CrewCount;++c)if(Crew[c].role==role&&Crew[c].star==star&&k--==0)return c;return -1;}',
              'inline int MaxStar(int role) {int m=0;for(int c=0;c<CrewCount;++c)if(Crew[c].role==role&&Crew[c].star>m)m=Crew[c].star;return m;}',
              '// 고유 동료의 주인 히어로(0 로빈 · 1 디아나 · 2 맥스). 역할마다 두 히어로가 ★ 사다리를 나눠 갖는다 -',
              '// 그 히어로의 룰렛에만 나오고, 그 히어로를 얻기 전에는 뽑기·창고 지급에도 안 나온다.',
              'static const signed char Owner[CrewCount]={' + ','.join(str(info[c][3]) for c in range(64)) + '};',
              'inline int OwnerHero(int crew) {return crew>=0&&crew<CrewCount?Owner[crew]:-1;}',
              'inline int OwnedCrewAt(int hero,int role,int star,int k) {for(int c=0;c<CrewCount;++c)if(Crew[c].role==role&&Crew[c].star==star&&(hero<0||Owner[c]==hero)&&k--==0)return c;return -1;}',
              '// 코스튬 6부위의 Lv → detail. 무기는 6칸, 나머지 부위는 1칸씩 성장.',
              'inline int GearDetail(int family,int detail,int level) {',
              ' const int step=family==4?6:1,cap=family==4?34:7;',
              ' return detail<0?0:(detail+(level-1)*step>cap?cap:detail+(level-1)*step);', '}', '}']
    return '\n'.join(lines) + '\n'


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    content = render()
    if args.check:
        assert TARGET.read_text(encoding='utf-8-sig') == content, 'merge tree header is stale'
    else:
        if not TARGET.exists() or TARGET.read_text(encoding='utf-8-sig') != content:
            TARGET.write_text(content, encoding='utf-8-sig')
    print('PASS 64 crew / 4 roles x 6 stars / three heroes own unbroken ladders / six costume slots with gear steps 6-1')
