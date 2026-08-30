# -*- coding: utf-8 -*-
"""동료 스킬의 자리별 종류를 규칙에 맞춘다.

[규칙]

    skill1, skill2   자기 총알(CREWBULLET)
    skill3           소환이나 히어로 스킬

동료마다 자기 총알 그림을 갖게 되면서 정해진 것이다. 슬롯에 한 명이 뜨면
약한 총알, 두 명이면 센 총알, 셋이 다 뜨면 큰 것 하나가 나온다. 앞 두 자리에
소환이나 버프가 섞여 있으면 이 층이 무너진다.

예전에는 이 규칙이 없어서 자리마다 제각각이었다. 소녀는 히어로 스킬 하나에
소환 하나였고, 아저씨와 아주머니는 둘 다 버프였다. 같은 자리인데 캐릭터마다
다른 종류가 나오면 어느 자리가 무엇인지 익힐 수가 없다.

[무엇을 바꾸나]

앞 두 자리가 총알이 아니면 총알로 바꾼다. 총알에 필요 없는 칸(소환할 몬스터,
히어로 번호, 장비 여섯 칸 등)은 지운다. 남겨 두면 다음에 읽는 사람이 그게
쓰이는 값인 줄 안다.

세기(dmg_pct)와 별은 건드리지 않는다. 그건 밸런스라 여기서 정할 것이 아니다.

    python tools/content/crew_skill_norm.py           #무엇이 바뀌는지만
    python tools/content/crew_skill_norm.py --write   #실제로 고친다

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

#총알 스킬이 갖는 값. NPC_BOY_SKILL1 을 본으로 삼았다.
BULLET = {
	'kind': 'CREWBULLET',
	'value': '2',
	'hit_max': '1',
	'cooldown': '0',
	'icon_kind': 'ICONKIND_BULLET',
	'attack_type': 'MAXX_SKILL_SPLIT',
	'bullet_obj': 'ADDOBJ_SLING',
}

#총알에는 쓰지 않는 칸. 옛 값이 남아 있으면 읽는 사람이 헷갈린다.
CLEAR = ['host_obj', 'summon_enemy', 'hero_type', 'hero_skill', 'summon_x',
         'equip1', 'equip2', 'equip3', 'equip4', 'equip5', 'equip6']


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

	by_name = {r[1]: r for r in sr}
	C = {n: i for i, n in enumerate(sc)}
	SK = [cc.index('skill%d' % i) for i in (1, 2, 3)]

	fixed = []
	third = []

	for c in cr:
		cid = int(c[0])

		#---- 앞 두 자리는 총알이어야 한다 ----
		for slot in range(2):
			row = by_name.get(c[SK[slot]])

			if row is None or row[C['kind']] == 'CREWBULLET':
				continue

			was = row[C['kind']]

			for k, v in BULLET.items():
				row[C[k]] = v

			for k in CLEAR:
				row[C[k]] = '0'

			#총알 그림은 bullet_assign 이 이미 자기 자리를 넣어 두었다.
			row[C['icon']] = row[C['bullet_icon']]

			fixed.append((cid, c[1], slot + 1, row[1], was))

		#---- 세 번째는 총알이면 안 된다 ----
		row = by_name.get(c[SK[2]])

		if row is not None and row[C['kind']] == 'CREWBULLET':
			third.append((cid, c[1], row[1]))

	print('총알로 바꾼 칸 %d개' % len(fixed))

	for cid, cn, slot, sn, was in fixed:
		print('   동료 %-3d %-16s skill%d  %-22s %s -> CREWBULLET'
		      % (cid, cn.replace('CREW_', ''), slot, sn, was))

	if third:
		print()
		print('세 번째인데 총알인 것 %d개. 소환이나 히어로 스킬로 바꿔야 한다'
		      % len(third))

		for cid, cn, sn in third:
			print('   동료 %-3d %-16s %s' % (cid, cn.replace('CREW_', ''), sn))

	if not a.write:
		print()
		print('보기만 했다. 고치려면 --write')
		return

	if not fixed:
		print('바꿀 것이 없다')
		return

	p = os.path.join(CONTENT, 'skill.tsv')
	out = shead + ['\t'.join(sc)] + ['\t'.join(r) for r in sr]

	with io.open(p, 'w', encoding='utf-8', newline='') as fp:
		fp.write(snl.join(out) + snl)

	print()
	print('%s 를 고쳤다' % p)


main()
