# -*- coding: utf-8 -*-
"""동료의 총알 아이콘 번호를 skill.tsv 에 박는다.

시트가 한 사람에 두 칸을 갖게 바뀌었으므로 번호가 식으로 떨어진다.

    동료 n  ->  skill1 = 2n,  skill2 = 2n + 1

예전에는 세 칸이 한 세트고 26 벌을 64 명이 나눠 써서, 누가 어느 벌을 쓰는지
bullet_match.py 에 손으로 적어 두어야 했다. 이제 그 표가 필요 없다.

[세 번째 스킬]

세 번째는 늘 소환이거나 히어로 스킬이라 총알 그림을 안 쓴다. 그래도 칸을
비워 두면 나중에 0 번 아이콘을 가리키는 것과 구별이 안 되므로, 두 번째와
같은 번호를 넣어 둔다. 그리는 쪽에서 kind 를 보고 소환 몬스터나 히어로
스킬 아이콘으로 갈아 끼운다.

    icon / icon_kind 는 세 번째 스킬에서 건드리지 않는다. 거기에는 이미
    불러낼 몬스터나 히어로 스킬의 그림이 들어 있다.

    python tools/content/bullet_assign.py           #무엇이 바뀌는지만
    python tools/content/bullet_assign.py --write   #실제로 고친다
"""
import argparse
import io
import os

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, '..', '..'))
CONTENT = os.path.join(ROOT, 'content')


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

	n = 0
	miss = []
	keep = []

	for c in cr:
		cid = int(c[0])

		for slot in range(3):
			row = by_name.get(c[SK[slot]])

			if row is None:
				miss.append((cid, c[SK[slot]]))
				continue

			#세 번째는 두 번째 것을 그대로 쓴다.
			want = str(cid * 2 + (1 if slot else 0))

			if row[C['bullet_icon']] != want:
				row[C['bullet_icon']] = want
				n += 1

			if slot < 2 and row[C['kind']] != 'CREWBULLET':
				keep.append((cid, row[1], row[C['kind']]))

			#총알을 쏘는 스킬만 그림까지 바꾼다. 첫째 둘째 자리라도
			#소환이나 히어로 스킬인 동료가 있고(63 왕의 skill1 이 그렇다),
			#그 자리의 icon 은 불러낼 것의 그림이라 덮으면 안 된다.
			if slot < 2 and row[C['kind']] == 'CREWBULLET':
				row[C['icon']] = want
				row[C['icon_kind']] = 'ICONKIND_BULLET'

	print('bullet_icon 을 고친 칸 %d개' % n)

	if keep:
		print('첫째/둘째 자리인데 총알이 아니라 그림을 그대로 둔 것 %d개'
		      % len(keep))

		for cid, nm, kind in keep:
			print('   동료 %d : %s (%s)' % (cid, nm, kind))

	if miss:
		print('스킬 이름을 못 찾은 자리 %d개' % len(miss))

		for cid, nm in miss:
			print('   동료 %d : %s' % (cid, nm))

	if not a.write:
		print('보기만 했다. 고치려면 --write')
		return

	p = os.path.join(CONTENT, 'skill.tsv')
	out = shead + ['\t'.join(sc)] + ['\t'.join(r) for r in sr]

	with io.open(p, 'w', encoding='utf-8', newline='') as fp:
		fp.write(snl.join(out) + snl)

	print('%s 를 고쳤다' % p)


main()
