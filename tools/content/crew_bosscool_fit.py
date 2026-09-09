# -*- coding: utf-8 -*-
"""동료의 보스전 쿨타임을 몸집에 맞춰 다시 깐다.

[왜 몸집인가]

보스전은 턴이 없다. 여섯이 저마다 제 시계로 돌아가므로, 그 시계가 같으면
같은 순간에 우르르 나가고 화면이 정신없어진다. 값이 흩어져 있어야 한 명씩
차례로 나가는 것처럼 보인다.

그냥 흩기만 하면 규칙이 없어서 다음에 동료가 늘 때 또 손으로 정해야 한다.
몸집을 자로 쓰면 저절로 정해진다.

    작은 동료일수록 자주 쏘고, 큰 동료일수록 뜸하게 쏜다.

큰 놈이 자주 치면 화면을 혼자 덮는다. 작은 놈은 여러 번 쳐야 존재가 보인다.
눈에 보이는 크기와 체감 빈도가 반대로 가야 여섯이 고르게 읽힌다.

[몸집을 어떻게 재나]

동료는 몬스터 그림을 그대로 쓴다. 그래서 그 몬스터 cmf 의 중립 모션 그림
높이에 enemyIconZoom 을 곱한 값이 화면에서 차지하는 세로 크기다.

    python tools/content/crew_bosscool_fit.py           #무엇이 바뀌는지만
    python tools/content/crew_bosscool_fit.py --write   #실제로 고친다

고친 뒤에는 소스와 팩을 다시 내라.
    python tools/content/content_table.py crew generate --write
    python tools/content/build_pack.py
"""
import argparse
import io
import os
import re

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, '..', '..'))
CONTENT = os.path.join(ROOT, 'content')
DATA = os.path.join(ROOT, 'Classes', 'Data')

#가장 작은 동료와 가장 큰 동료의 쿨타임. 60프레임이 1초다.
COOL_FAST = 210
COOL_SLOW = 480


def read_tsv(name):
	p = os.path.join(CONTENT, name + '.tsv')

	with io.open(p, encoding='utf-8', newline='') as fp:
		raw = fp.read()

	nl = '\r\n' if '\r\n' in raw else '\n'
	lines = raw.split(nl)
	head = [l for l in lines if l.startswith('#')]
	body = [l for l in lines if l and not l.startswith('#')]

	return head, body[0].split('\t'), [l.split('\t') for l in body[1:]], nl


def blob(fname, name):
	"""생성된 배열 하나를 숫자 목록으로 읽는다."""
	p = os.path.join(DATA, fname)

	with io.open(p, encoding='utf-8-sig', errors='replace') as fp:
		s = fp.read()

	m = re.search(r'\b%s_builtin\[\]\s*=\s*\{' % name, s)

	if m is None:
		raise SystemExit('%s 를 %s 에서 못 찾았다' % (name, fname))

	b = s[m.end():]
	b = b[:b.index('\n};')]

	#주석 속 숫자를 같이 긁으면(//35 ENEMY_FROG 같은) 배열이 통째로
	#어긋난다. 먼저 걷어낸다.
	b = re.sub(r'/\*.*?\*/', ' ', b, flags=re.S)
	b = re.sub(r'//[^\n]*', ' ', b)

	return [float(x) for x in re.findall(r'-?\d+\.?\d*', b)]


def sprite_height(cmf, motion, slot, size):
	"""그 cmf 의 그 모션 그림이 원본에서 몇 픽셀 높이인가."""
	off = int(slot[cmf])

	return size[off + motion * 4 + 3]


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument('--write', action='store_true')
	a = ap.parse_args()

	_h, cc, cr, cnl = read_tsv('crew')
	_h2, ec, er, _n = read_tsv('enemy')

	COOL = cc.index('boss_cool')
	TYPE = cc.index('enemy_type')

	#적 이름 -> 행
	eByName = {r[ec.index('enum_name')]: r for r in er}
	ECMF = ec.index('cmf')

	#cmf 이름 -> 번호
	cmfNo = {}
	p = os.path.join(ROOT, 'Classes', 'Def', 'CmfDef.h')

	with io.open(p, encoding='utf-8-sig', errors='replace') as fp:
		cur = -1

		for ln in fp:
			m = re.match(r'\s*(CMF_\w+)\s*(?:=\s*(\d+))?\s*,', ln)

			if m:
				cur = int(m.group(2)) if m.group(2) else cur + 1
				cmfNo[m.group(1)] = cur

	slot = blob('CmfBlob.cpp', 'cmfMotionImgSizeSlot')
	size = blob('CmfBlob.cpp', 'cmfMotionImgSizeBlob')
	iconZoom = blob('EnemyData.cpp', 'enemyIconZoom')

	#적 이름 -> 번호(enemyIconZoom 의 색인)
	eNo = {r[ec.index('enum_name')]: int(r[0]) for r in er}

	tall = []
	bad = []

	for r in cr:
		name = r[TYPE]
		e = eByName.get(name)

		if e is None:
			bad.append((r[0], r[1], name, '적 이름을 못 찾았다'))
			tall.append(None)
			continue

		cmf = cmfNo.get(e[ECMF], -1)

		if cmf < 0:
			bad.append((r[0], r[1], e[ECMF], 'cmf 를 못 찾았다'))
			tall.append(None)
			continue

		#중립 모션은 0 번이다. 그 그림 높이가 서 있을 때의 세로다.
		h = sprite_height(cmf, 0, slot, size)
		z = iconZoom[eNo[name]] if eNo[name] < len(iconZoom) else 1.0

		tall.append(h * z)

	seen = [t for t in tall if t is not None]

	if not seen:
		raise SystemExit('몸집을 하나도 못 쟀다')

	lo = min(seen)
	hi = max(seen)

	print('몸집 %.1f ~ %.1f, 쿨타임 %d ~ %d 프레임 (%.1f ~ %.1f초)'
	      % (lo, hi, COOL_FAST, COOL_SLOW, COOL_FAST / 60.0, COOL_SLOW / 60.0))
	print()

	changed = 0

	for i, r in enumerate(cr):
		if tall[i] is None:
			continue

		#작을수록 0, 클수록 1.
		t = 0.0 if hi <= lo else (tall[i] - lo) / (hi - lo)
		want = str(int(round(COOL_FAST + (COOL_SLOW - COOL_FAST) * t)))

		if r[COOL] != want:
			changed += 1

		if i % 8 == 0 or i == len(cr) - 1:
			print('  %-3s %-16s 높이 %6.1f -> %s (%.1f초)'
			      % (r[0], r[1].replace('CREW_', ''), tall[i], want,
			         int(want) / 60.0))

		r[COOL] = want

	print()
	print('바뀐 동료 %d명' % changed)

	for x in bad:
		print('   못 정함 : %s' % (x,))

	if not a.write:
		print('보기만 했다. 고치려면 --write')
		return

	p = os.path.join(CONTENT, 'crew.tsv')
	out = _h + ['\t'.join(cc)] + ['\t'.join(r) for r in cr]

	with io.open(p, 'w', encoding='utf-8', newline='') as fp:
		fp.write(cnl.join(out) + cnl)

	print('%s 를 고쳤다' % p)


main()
