# -*- coding: utf-8 -*-
"""동료의 기본 공격력을 검의 세기에 맞춰 다시 깐다.

[왜 검을 기준으로 삼나]

동료의 세기는 그 자체로는 뜻이 없다. 같은 자리에서 주인공이 내는 값과
견줘야 "이 동료를 데려갈 만한가"가 정해진다. 주인공의 세기를 정하는 것은
무기이므로 무기표를 자로 쓴다.

    같은 자리의 검이 100 을 낸다면 동료는 150 을 낸다.

전에는 10~30 이라는 고정값이었다. 무기는 10 에서 999 까지 백 배로 자라는데
동료만 세 배 안에서 움직여서, 뒤로 갈수록 동료가 있으나 마나 했다.

[자리를 어떻게 맞추나]

검은 35 자루이고 동료는 64 명이라 하나씩 짝지을 수가 없다. 그래서 검의
세기 곡선을 동료 수만큼 늘려 편다. 동료 0 은 첫 검, 동료 63 은 마지막 검을
보고, 그 사이는 이웃한 두 검 사이를 비례로 나눈다.

곡선을 새로 만들지 않고 무기표를 그대로 늘려 쓰는 까닭은, 무기 밸런스를
고치면 동료도 저절로 따라오게 하기 위해서다. 두 곡선을 따로 두면 한쪽만
고쳐 놓고 다른 쪽을 잊는다.

    python tools/content/crew_power_fit.py           #무엇이 바뀌는지만
    python tools/content/crew_power_fit.py --write   #실제로 고친다

고친 뒤에는 소스와 팩을 다시 내라.
    python tools/content/content_table.py crew generate --write
    python tools/content/build_pack.py
"""
import argparse
import io
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(HERE, '..', '..'))
CONTENT = os.path.join(ROOT, 'content')

sys.path.insert(0, HERE)

#동료가 같은 자리의 검보다 몇 배 센가.
CREW_OVER_SWORD = 1.50


def read_tsv(name):
	p = os.path.join(CONTENT, name + '.tsv')

	with io.open(p, encoding='utf-8', newline='') as fp:
		raw = fp.read()

	nl = '\r\n' if '\r\n' in raw else '\n'
	lines = raw.split(nl)
	head = [l for l in lines if l.startswith('#')]
	body = [l for l in lines if l and not l.startswith('#')]

	return head, body[0].split('\t'), [l.split('\t') for l in body[1:]], nl


def sword_values():
	"""검 한 자루씩의 세기. 팩에서 그대로 읽는다."""
	import gacha_rates as g

	pack = g.read_pack()
	value = g.cells_of(pack, 'itemValue')
	start = g.cells_of(pack, 'itemStartCnt')

	#itemStartCnt 는 종류마다 itemValue 안에서 어디부터인지다. 검은 0 번이다.
	return value[start[0]:start[1]]


def main():
	ap = argparse.ArgumentParser()
	ap.add_argument('--write', action='store_true')
	a = ap.parse_args()

	sw = sword_values()

	if len(sw) < 2:
		raise SystemExit('검 표를 못 읽었다')

	head, cols, rows, nl = read_tsv('crew')
	STR = cols.index('str')
	n = len(rows)

	print('검 %d자루 (%d ~ %d), 동료 %d명, 배수 %.2f'
	      % (len(sw), sw[0], sw[-1], n, CREW_OVER_SWORD))
	print()

	changed = 0

	for i, r in enumerate(rows):
		#동료 자리를 검 자리로 옮긴다. 0 은 첫 검, 마지막은 마지막 검이다.
		t = i * (len(sw) - 1) / float(n - 1)
		lo = int(t)
		hi = min(lo + 1, len(sw) - 1)
		f = t - lo

		val = sw[lo] + (sw[hi] - sw[lo]) * f
		want = str(int(round(val * CREW_OVER_SWORD)))

		if r[STR] != want:
			changed += 1

		if i % 8 == 0 or i == n - 1:
			print('  %-3s %-16s %-6s -> %-6s   (검 %d 자리, %d)'
			      % (r[0], r[1].replace('CREW_', ''), r[STR], want, lo, sw[lo]))

		r[STR] = want

	print()
	print('바뀐 동료 %d명' % changed)

	if not a.write:
		print('보기만 했다. 고치려면 --write')
		return

	p = os.path.join(CONTENT, 'crew.tsv')
	out = head + ['\t'.join(cols)] + ['\t'.join(r) for r in rows]

	with io.open(p, 'w', encoding='utf-8', newline='') as fp:
		fp.write(nl.join(out) + nl)

	print('%s 를 고쳤다' % p)


main()
