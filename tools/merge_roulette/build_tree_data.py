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
        info[crew] = (role, star, TRAITS[row['trait']])
    assert sorted(info) == list(range(64))
    for role, counts in EXPECTED.items():
        for star in range(1, 7):
            got = sum(1 for r, s, _ in info.values() if r == role and s == star)
            assert got == counts[star - 1], (role, star, got)
    lines = ['#pragma once', '// Generated from content/merge_tree.tsv by tools/merge_roulette/build_tree_data.py. Do not edit.',
             '// 합성 6단 = 성급. 같은 역할 ★n 둘 → 그 역할 ★n+1 중 무작위.',
             'namespace MergeTrees {', 'enum { Roles=4, Levels=6, CrewCount=64, MaxPerCell=8 };',
             'struct CrewInfo { int role, star, trait; };',
             'static const CrewInfo Crew[CrewCount]={']
    for crew in range(64):
        role, star, trait = info[crew]
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
              '// 장비 계열(4 검 · 5 갑옷 · 6 목걸이) 의 Lv → detail. 35자루는 6칸, 8벌은 1칸, 28개는 5칸 위.',
              'inline int GearDetail(int family,int detail,int level) {',
              ' const int step=family==4?6:family==5?1:5,cap=family==4?34:family==5?7:27;',
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
    print('PASS 64 crew / 4 roles x 6 stars match the balance table / gear steps 6-1-5')
