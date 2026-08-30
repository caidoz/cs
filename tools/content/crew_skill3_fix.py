# -*- coding: utf-8 -*-
"""동료의 세 번째 스킬을 서로 겹치지 않게 고른다.

[왜 겹치면 안 되나]

세 번째 스킬은 슬롯에 그 동료가 셋 다 떴을 때 나오는, 그 동료의 얼굴이다.
둘이 같은 것을 부르면 누구를 키운 보람이 없다. 그래서 소환수는 cmf 가,
히어로 스킬은 스킬 번호가 전부 달라야 한다.

[소환수는 색 변종을 쓴다]

들판에서 그냥 만나는 몹을 그대로 부르면 소환처럼 안 보인다. 몬스터마다
색이 다른 여섯 벌이 있으므로 그중에서 고른다. 색은 동료가 셀수록 뒤쪽
(빨강 -> 파랑 -> 보라 -> 초록 -> 금 -> 검정)을 쓴다. 같은 몬스터를 여럿이
부르더라도 색이 다르면 cmf 가 달라서 서로 다른 그림이 된다.

[히어로 스킬은 셀수록 센 것]

연타수(hit_max)가 그 스킬의 세기다. 동료를 세기순으로 줄 세우고 스킬도
연타수순으로 줄 세워 짝을 짓는다. 약한 동료가 오비탈레이져를 부르면
등급을 올릴 까닭이 없어진다.

    python tools/content/crew_skill3_fix.py           #무엇이 바뀌는지만
    python tools/content/crew_skill3_fix.py --write   #실제로 고친다

고친 뒤에는 소스와 팩을 다시 내라.
    python tools/content/content_table.py skill generate --write
    python tools/content/build_pack.py
"""
import argparse
import io
import os

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, '..', '..'))
CONTENT = os.path.join(ROOT, 'content')

#색 변종은 기본 몬스터에서 51 씩 떨어져 있다. 1 이 빨강, 6 이 검정이다.
COLOR_STEP = 51
COLOR_MAX = 6

#히어로 스킬 후보. 연타수 오름차순이고, 이름이 공격으로 읽히는 것만 골랐다.
#"집중력유지" 같은 것은 ACTIVE 로 적혀 있지만 이름이 버프라 뺐다.
HERO_POOL = [
	'SKILL_ROBIN6',		# 10 에어크래쉬
	'SKILL_ROBIN8',		# 20 부스트슬래쉬
	'SKILL_ROBIN9',		# 25 하이퍼차지
	'SKILL_MAXX7',		# 30 연속공격
	'SKILL_ROBIN7',		# 30 마구찌르기
	'SKILL_ROBIN10',	# 35 소울크래쉬
	'SKILL_DIANA9',		# 40 리플렉션빔
	'SKILL_ROBIN14',	# 40 다크나이트 소환
	'SKILL_DIANA8',		# 50 3웨이
	'SKILL_DIANA10',	# 50 헬파이어
	'SKILL_ROBIN11',	# 50 앱솔루트피어스
	'SKILL_ROBIN13',	# 50 테트라쉐도우 소환
	'SKILL_ROBIN15',	# 50 라베스 소환
	'SKILL_ROBIN16',	# 50 엘케인 소환
	'SKILL_ROBIN17',	# 50 로라공주 소환
	'SKILL_DIANA6',		# 60 활성화
	'SKILL_MAXX9',		# 70 탄력성
	'SKILL_ROBIN12',	# 70 멸살연참
	'SKILL_MAXX10',		# 80 효율적사고
	'SKILL_MAXX11',		# 80 돌려차기
	'SKILL_MAXX12',		# 90 숏헌트
	'SKILL_MAXX8',		#100 회전력상승
	'SKILL_DIANA11',	#100 로켓런쳐
	'SKILL_DIANA13',	#100 킬링존
	'SKILL_DIANA14',	#100 오비탈레이져
	'SKILL_MAXX14',		#100 캠핑헌트
	'SKILL_MAXX15',		#100 호밍헌트
	'SKILL_MAXX16',		#100 써클헌트
	'SKILL_MAXX17',		#100 메가헌트
	'SKILL_DIANA12',	#150 호밍미사일
	'SKILL_MAXX13',		#150 에어헌트
]

#손으로 못 박는 자리. 기획이 정한 것이라 세기순 배치보다 먼저다.
HERO_FIX = {
	42: 'SKILL_ROBIN7',		#세바스찬 - 마구찌르기
}

#색 변종이 없어 그대로 쓸 수 없는 소환수. 비슷한 것으로 바꾼다.
SUMMON_SWAP = {
	'NPC_SHIP': 'ENEMY_SHIP',	#선장이 부르는 배. NPC 판은 색이 하나뿐이다
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
	_h2, ec, er, _n2 = read_tsv('enemy')

	S = {n: i for i, n in enumerate(sc)}
	by_name = {r[1]: r for r in sr}
	SK3 = cc.index('skill3')
	STR = cc.index('str')

	eid = {r[1]: int(r[0]) for r in er}
	ename = {int(r[0]): r[1] for r in er}
	ecmf = {int(r[0]): r[ec.index('cmf')] for r in er}

	#세기 오름차순. 같은 세기면 번호순이라 돌릴 때마다 같은 답이 나온다.
	crew = sorted(cr, key=lambda r: (int(r[STR]), int(r[0])))

	summons = [r for r in crew if by_name[r[SK3]][S['kind']] == 'SUMMON']
	heroes = [r for r in crew if by_name[r[SK3]][S['kind']] == 'HEROSKILL']

	#---- 소환수 : 색을 골라 cmf 를 서로 다르게 ----
	usedCmf = set()
	sLog = []
	sBad = []

	lo = min(int(r[STR]) for r in crew)
	hi = max(int(r[STR]) for r in crew)

	for r in summons:
		row = by_name[r[SK3]]
		cur = row[S['summon_enemy']]
		cur = SUMMON_SWAP.get(cur, cur)

		base = eid.get(cur, -1)

		#이미 색 변종이면 기본으로 되돌려 놓고 다시 고른다.
		while base >= COLOR_STEP + 3:
			base -= COLOR_STEP

		if base < 0:
			sBad.append((r[0], r[1], cur, '적 이름을 못 찾았다'))
			continue

		#세기에 맞는 색을 먼저 본다. 막히면 옆 색으로 옮긴다.
		tier = 1 + (int(r[STR]) - lo) * (COLOR_MAX - 1) // max(1, hi - lo)
		order = [tier] + [k for k in range(1, COLOR_MAX + 1) if k != tier]
		pick = -1

		for k in order:
			e = base + COLOR_STEP * k

			if e not in ename:
				continue

			c = ecmf[e]

			if c in usedCmf:
				continue

			usedCmf.add(c)
			pick = e
			break

		if pick < 0:
			sBad.append((r[0], r[1], cur, '빈 색이 없다'))
			continue

		was = row[S['summon_enemy']]
		row[S['summon_enemy']] = ename[pick]
		row[S['icon']] = ename[pick]
		row[S['icon_kind']] = 'ICONKIND_MONSTER'
		sLog.append((int(r[0]), r[1], was, ename[pick], ecmf[pick]))

	#---- 히어로 스킬 : 세기순으로 짝짓기 ----
	pool = [n for n in HERO_POOL if n not in HERO_FIX.values()]
	hLog = []
	hBad = []

	need = len(heroes) - len(HERO_FIX)

	if need > len(pool):
		hBad.append('스킬 후보가 %d개뿐인데 %d명이 필요하다' % (len(pool), need))

	k = 0

	for r in heroes:
		row = by_name[r[SK3]]
		cid = int(r[0])
		want = HERO_FIX.get(cid)

		if want is None:
			if k >= len(pool):
				continue

			want = pool[k]
			k += 1

		ref = by_name.get(want)

		if ref is None:
			hBad.append('%s 라는 스킬이 없다' % want)
			continue

		was = row[S['hero_skill']]
		row[S['hero_skill']] = want
		row[S['host_obj']] = 'ROBIN'
		row[S['icon']] = ref[S['icon']]
		row[S['icon_kind']] = 'ICONKIND_SKILL'
		hLog.append((cid, r[1], was, want))

	#---- 보고 ----
	print('소환수 %d명' % len(sLog))

	for cid, nm, was, now, cmf in sLog:
		print('   동료 %-3d %-16s %-22s -> %-26s %s'
		      % (cid, nm.replace('CREW_', ''), was, now, cmf))

	print()
	print('히어로 스킬 %d명' % len(hLog))

	for cid, nm, was, now in hLog:
		print('   동료 %-3d %-16s %-18s -> %s'
		      % (cid, nm.replace('CREW_', ''), was, now))

	print()
	print('서로 다른 소환 cmf %d개 / %d명' % (len(usedCmf), len(sLog)))
	print('서로 다른 히어로 스킬 %d개 / %d명'
	      % (len(set(x[3] for x in hLog)), len(hLog)))

	for x in sBad:
		print('   못 정함 : %s' % (x,))

	for x in hBad:
		print('   못 정함 : %s' % x)

	if not a.write:
		print()
		print('보기만 했다. 고치려면 --write')
		return

	p = os.path.join(CONTENT, 'skill.tsv')
	out = shead + ['\t'.join(sc)] + ['\t'.join(r) for r in sr]

	with io.open(p, 'w', encoding='utf-8', newline='') as fp:
		fp.write(snl.join(out) + snl)

	print()
	print('%s 를 고쳤다' % p)


main()
